/*   SCE CONFIDENTIAL                                       */
/*   PlayStation(R)3 Programmer Tool Runtime Library 370.001 */
/*   Copyright (C) 2007 Sony Computer Entertainment Inc.    */
/*   All Rights Reserved.                                   */

#pragma once

#define __DEBUG

extern "C" /*liblv2 functions*/ {
	void* _sys_malloc(size_t);
	void _sys_free(void*);
	int _sys_sprintf(char*, const char*, ...);
	int _sys_v_sys_sprintf(char*, const char*, va_list);
	int _sys_printf(const char*, ...);
}

//toggle Debug Printf by __DEBUG
#ifdef __DEBUG 
#define printf _sys_printf
#else
#define printf
#endif

#if !defined(_SCENET_SAMPLE_TOOLS_H)
#define _SCENET_SAMPLE_TOOLS_H

#if defined(__cplusplus)
extern "C" {
#endif

	int if_up(void);
	int if_up_with(int index);
	int if_down(int sid);
	int dump_start(void);
	int dump_print(void);
	int dump_stop(void);

	int show_route(void);
	int show_netstat(void);
	int show_netstat_ex(void);
	int show_nameserver(void);
	int show_ifconfig(void);

	char **fake_argv(int *argc, char *args);
	char **fake_argv1(int *argc, char *arg0);

#if defined(__cplusplus)
}
#endif

#endif	/* _SCENET_SAMPLE_TOOLS_H */

