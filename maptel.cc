#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <cassert>
#include "maptel.h"

using namespace std;

typedef std::unordered_map<string, string> langOfChangesType;
typedef std::unordered_map<unsigned long, langOfChangesType> mapOfLangsType;

static unsigned long currentlyAddedLang = 0;
static mapOfLangsType mapOfLangs;

unsigned long maptel_create() {
    mapOfLangs.insert(make_pair(currentlyAddedLang, langOfChangesType()));
    return currentlyAddedLang++;
}

void maptel_erase(unsigned long id, char const *tel_src) {
    auto tempLangIterator = mapOfLangs.find(id);
    if (tempLangIterator != mapOfLangs.end()) {
        auto tempPhoneNrIterator = tempLangIterator->second.find(string(tel_src));
        if (tempPhoneNrIterator != tempLangIterator->second.end())
            tempLangIterator->second.erase(tempPhoneNrIterator);
    }
}

void maptel_transform(unsigned long id, char const *tel_src, char *tel_dst, size_t len) {
    auto tempLangIterator = mapOfLangs.find(id);
    if (tempLangIterator != mapOfLangs.end()) {  //langOfChanges found
        unordered_set<string> path;
        string telSrcCPPString = string(tel_src);
        path.insert(telSrcCPPString);
        auto tempPhoneNrIterator = tempLangIterator->second.find(telSrcCPPString);
        if (tempPhoneNrIterator != tempLangIterator->second.end()){ //number found
            while (true){
                string currentChangeCPPString = tempPhoneNrIterator->second;
                
                auto pathIterator = path.find(currentChangeCPPString);
                if (pathIterator != path.end()){ //cycle found
                    strncpy(tel_dst, tel_src, len);
                    break;
                }

                auto newPhoneNrIterator = tempLangIterator->second.find(currentChangeCPPString);
                if (newPhoneNrIterator == tempLangIterator->second.end()){ //change found
                    strncpy(tel_dst, currentChangeCPPString.c_str(), len);
                    break;
                }
                
                path.insert(currentChangeCPPString);
                tempPhoneNrIterator = newPhoneNrIterator;
            }
        } else { //number not found
            strncpy(tel_dst, tel_src, len);
        }
    }
}

void maptel_insert(unsigned long id, char const *tel_src, char const *tel_dst) {
    auto tempLangIterator = mapOfLangs.find(id);
    if (tempLangIterator != mapOfLangs.end())
        tempLangIterator->second[string(tel_src)] = string(tel_dst);
}

void maptel_delete(unsigned long id){
    auto tempLangIterator = mapOfLangs.find(id);
    if (tempLangIterator != mapOfLangs.end())
        mapOfLangs.erase(tempLangIterator);
}

//static void print_module_name(){
//    cerr<<"maptel: ";
//}
//
//static void print_create_call(){
//    print_module_name();
//    cerr<<"maptel_create()"<<endl;
//}
//
//static void print_create_result(unsigned long new_map_id){
//    print_module_name();
//    cerr<<"maptel_create: new map id = "<<id<<endl;
//}
//
//static void print_erase_call(unsigned long id, char const *tel_src){
//    print_module_name();
//    cerr<<"maptel_erase("<<id<<", "<<string(tel_src)<<")"<<endl;
//}
//
//static void print_erase_result(bool result){
//    print_module_name();
//    cerr<<"maptel_erase: ";
//    if (result)
//        cerr<<"erased"<<endl;
//    else
//        cerr<<"nothing to erase"<<endl;
//}
