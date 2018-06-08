#ifndef _LZUTILS_H_
#define _LZUTILS_H_

#include "lua.h"
#include "lauxlib.h"

#if LUA_VERSION_NUM >= 502 

# define luazmq_rawgetp  lua_rawgetp
# define luazmq_rawsetp  lua_rawsetp
# define luazmq_setfuncs luaL_setfuncs
# define luazmq_absindex lua_absindex
# define lua_objlen      lua_rawlen

int   luazmq_typerror (lua_State *L, int narg, const char *tname);

#else 

# define luazmq_absindex(L, i) (((i)>0)?(i):((i)<=LUA_REGISTRYINDEX?(i):(lua_gettop(L)+(i)+1)))
# define lua_rawlen      lua_objlen
# define luazmq_typerror luaL_typerror

void  luazmq_rawgetp   (lua_State *L, int index, const void *p);
void  luazmq_rawsetp   (lua_State *L, int index, const void *p);
void  luazmq_setfuncs  (lua_State *L, const luaL_Reg *l, int nup);

#endif

int   luazmq_newmetatablep (lua_State *L, const void *p);
void  luazmq_getmetatablep (lua_State *L, const void *p);
int   luazmq_isudatap      (lua_State *L, int ud, const void *p);
void *luazmq_checkudatap   (lua_State *L, int ud, const void *p);

int   luazmq_createmeta    (lua_State *L, const char *name, const luaL_Reg *methods);
void  luazmq_setmeta       (lua_State *L, const char *name);

void *luazmq_newudata_     (lua_State *L, size_t size, const char *name);

#define luazmq_newudata(L, TTYPE, TNAME) (TTYPE *)luazmq_newudata_(L, sizeof(TTYPE), TNAME)

#define LUAZMQ_STATIC_ASSERT(A) {(int(*)[(A)?1:0])0;}

typedef struct {
  const char *name;
  int value;
}luazmq_int_const;

#define DEFINE_ZMQ_CONST(NAME) {#NAME, ZMQ_##NAME}
#define DEFINE_INT_CONST(NAME) {#NAME, NAME}


void luazmq_register_consts(lua_State *L, const luazmq_int_const *c);

void luazmq_register_consts_invers(lua_State *L, const luazmq_int_const *c);

#endif
