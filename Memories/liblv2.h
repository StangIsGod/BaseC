#pragma once

#define __DEBUG

extern "C" /*liblv2 functions*/ {
	void* _sys_malloc(size_t);
	void _sys_free(void*);
	int sprintf(char*, const char*, ...);
	int _sys_vsprintf(char*, const char*, va_list);
	int _sys_printf(const char*, ...);
}

//toggle Debug Printf by __DEBUG
#ifdef __DEBUG 
#define printf _sys_printf
#else
#define printf
#endif