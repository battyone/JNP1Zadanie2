/* JNP1 - Projekt 2 -
 * Autorzy : Michał Graczykowski graczykowskimichal@gmail.com;
 Marcin Możejko mmozejko1988@gmail.com
 */

#ifdef __cplusplus
extern "C" {
#endif
    
const size_t TEL_NUM_MAX_LEN = 22;

unsigned long maptel_create();
void maptel_erase(unsigned long id, char const *tel_src);
void maptel_transform(unsigned long id, char const *tel_src, char *tel_dst, size_t len);
void maptel_insert(unsigned long id, char const *tel_src, char const *tel_dst);
void maptel_delete(unsigned long id);
    
#ifdef __cplusplus
}
#endif
