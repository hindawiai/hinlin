<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support Camera Imaging tracer core.
 *
 * Copyright (c) 2013 Intel Corporation. All Rights Reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 *
 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM atomisp

#अगर !defined(ATOMISP_TRACE_EVENT_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा ATOMISP_TRACE_EVENT_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/माला.स>
TRACE_EVENT(camera_meminfo,

	    TP_PROTO(स्थिर अक्षर *name, पूर्णांक uptr_size, पूर्णांक counter, पूर्णांक sys_size,
		     पूर्णांक sys_res_size, पूर्णांक cam_sys_use, पूर्णांक cam_dyc_use,
		     पूर्णांक cam_res_use),

	    TP_ARGS(name, uptr_size, counter, sys_size, sys_res_size, cam_sys_use,
		    cam_dyc_use, cam_res_use),

	    TP_STRUCT__entry(
		__array(अक्षर, name, 24)
		__field(पूर्णांक, uptr_size)
		__field(पूर्णांक, counter)
		__field(पूर्णांक, sys_size)
		__field(पूर्णांक, sys_res_size)
		__field(पूर्णांक, cam_res_use)
		__field(पूर्णांक, cam_dyc_use)
		__field(पूर्णांक, cam_sys_use)
	    ),

	    TP_fast_assign(
		strscpy(__entry->name, name, 24);
		__entry->uptr_size = uptr_size;
		__entry->counter = counter;
		__entry->sys_size = sys_size;
		__entry->sys_res_size = sys_res_size;
		__entry->cam_res_use = cam_res_use;
		__entry->cam_dyc_use = cam_dyc_use;
		__entry->cam_sys_use = cam_sys_use;
	    ),

	    TP_prपूर्णांकk(
		"<%s> User ptr memory:%d pages,\tISP private memory used:%d pages:\tsysFP system size:%d,\treserved size:%d\tcamFP sysUse:%d,\tdycUse:%d,\tresUse:%d.\n",
		__entry->name, __entry->uptr_size, __entry->counter,
		__entry->sys_size, __entry->sys_res_size, __entry->cam_sys_use,
		__entry->cam_dyc_use, __entry->cam_res_use)
	   );

TRACE_EVENT(camera_debug,

	    TP_PROTO(स्थिर अक्षर *name, अक्षर *info, स्थिर पूर्णांक line),

	    TP_ARGS(name, info, line),

	    TP_STRUCT__entry(
		__array(अक्षर, name, 24)
		__array(अक्षर, info, 24)
		__field(पूर्णांक, line)
	    ),

	    TP_fast_assign(
		strscpy(__entry->name, name, 24);
		strscpy(__entry->info, info, 24);
		__entry->line = line;
	    ),

	    TP_prपूर्णांकk("<%s>-<%d> %s\n", __entry->name, __entry->line,
		      __entry->info)
	   );

TRACE_EVENT(ipu_cstate,

	    TP_PROTO(पूर्णांक cstate),

	    TP_ARGS(cstate),

	    TP_STRUCT__entry(
		__field(पूर्णांक, cstate)
	    ),

	    TP_fast_assign(
		__entry->cstate = cstate;
	    ),

	    TP_prपूर्णांकk("cstate=%d", __entry->cstate)
	   );

TRACE_EVENT(ipu_pstate,

	    TP_PROTO(पूर्णांक freq, पूर्णांक util),

	    TP_ARGS(freq, util),

	    TP_STRUCT__entry(
		__field(पूर्णांक, freq)
		__field(पूर्णांक, util)
	    ),

	    TP_fast_assign(
		__entry->freq = freq;
		__entry->util = util;
	    ),

	    TP_prपूर्णांकk("freq=%d util=%d", __entry->freq, __entry->util)
	   );
#पूर्ण_अगर

#अघोषित TRACE_INCLUDE_PATH
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता   atomisp_trace_event
/* This part must be outside protection */
#समावेश <trace/define_trace.h>
