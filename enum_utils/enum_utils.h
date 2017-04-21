#ifndef _ENUM_UTILS_H
#define _ENUM_UTILS_H

#include<string.h>

template <typename T> T str2enum(const char* str);
template <typename T> const char* enum2str(T v);

#define STR2ENUM(TYPE,ARRAY) \
template <> \
TYPE str2enum<TYPE>( const char* str ) \
    { \
    for( unsigned i = 0; i < (sizeof(ARRAY)/sizeof(ARRAY[0])); i++ ) \
        if( !strcmp( ARRAY[i], str ) ) \
            return TYPE(i); \
    return TYPE(1000000); \
    }

#define ENUM2STR(TYPE,ARRAY) \
template <> \
const char* enum2str( TYPE v ) \
    { \
    return v >= TYPE##_size ? "null" : ARRAY[v]; \
    }

#define ENUMANDSTR(TYPE)\
    STR2ENUM(TYPE,TYPE##_name) \
    ENUM2STR(TYPE,TYPE##_name)

#define ENUMNAMECLS(TYPE, CLASS) \
  const char* const CLASS::TYPE##_name[CLASS::TYPE##_size + 1]

#define ENUMNAME(TYPE) \
  const char* const TYPE##_name[TYPE##_size + 1]

#endif // for #ifndef _ENUM_UTILS_H
