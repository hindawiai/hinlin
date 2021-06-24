<शैली गुरु>
/*
 *  Copyright (c) 2008 Silicon Graphics, Inc.  All Rights Reserved.
 *
 *  This program is मुक्त software; you can redistribute it and/or modअगरy
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; either version 2.1 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License क्रम more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */

#अगर_अघोषित __GRULIB_H__
#घोषणा __GRULIB_H__

#घोषणा GRU_BASENAME		"gru"
#घोषणा GRU_FULLNAME		"/dev/gru"
#घोषणा GRU_IOCTL_NUM 		 'G'

/*
 * Maximum number of GRU segments that a user can have खोलो
 * ZZZ temp - set high क्रम testing. Revisit.
 */
#घोषणा GRU_MAX_OPEN_CONTEXTS		32

/* Set Number of Request Blocks */
#घोषणा GRU_CREATE_CONTEXT		_IOWR(GRU_IOCTL_NUM, 1, व्योम *)

/*  Set Context Options */
#घोषणा GRU_SET_CONTEXT_OPTION		_IOWR(GRU_IOCTL_NUM, 4, व्योम *)

/* Fetch exception detail */
#घोषणा GRU_USER_GET_EXCEPTION_DETAIL	_IOWR(GRU_IOCTL_NUM, 6, व्योम *)

/* For user call_os handling - normally a TLB fault */
#घोषणा GRU_USER_CALL_OS		_IOWR(GRU_IOCTL_NUM, 8, व्योम *)

/* For user unload context */
#घोषणा GRU_USER_UNLOAD_CONTEXT		_IOWR(GRU_IOCTL_NUM, 9, व्योम *)

/* For dumpping GRU chiplet state */
#घोषणा GRU_DUMP_CHIPLET_STATE		_IOWR(GRU_IOCTL_NUM, 11, व्योम *)

/* For getting gseg statistics */
#घोषणा GRU_GET_GSEG_STATISTICS		_IOWR(GRU_IOCTL_NUM, 12, व्योम *)

/* For user TLB flushing (primarily क्रम tests) */
#घोषणा GRU_USER_FLUSH_TLB		_IOWR(GRU_IOCTL_NUM, 50, व्योम *)

/* Get some config options (primarily क्रम tests & emulator) */
#घोषणा GRU_GET_CONFIG_INFO		_IOWR(GRU_IOCTL_NUM, 51, व्योम *)

/* Various kernel self-tests */
#घोषणा GRU_KTEST			_IOWR(GRU_IOCTL_NUM, 52, व्योम *)

#घोषणा CONTEXT_WINDOW_BYTES(th)        (GRU_GSEG_PAGESIZE * (th))
#घोषणा THREAD_POINTER(p, th)		(p + GRU_GSEG_PAGESIZE * (th))
#घोषणा GSEG_START(cb)			((व्योम *)((अचिन्हित दीर्घ)(cb) & ~(GRU_GSEG_PAGESIZE - 1)))

काष्ठा gru_get_gseg_statistics_req अणु
	अचिन्हित दीर्घ			gseg;
	काष्ठा gru_gseg_statistics	stats;
पूर्ण;

/*
 * Structure used to pass TLB flush parameters to the driver
 */
काष्ठा gru_create_context_req अणु
	अचिन्हित दीर्घ		gseg;
	अचिन्हित पूर्णांक		data_segment_bytes;
	अचिन्हित पूर्णांक		control_blocks;
	अचिन्हित पूर्णांक		maximum_thपढ़ो_count;
	अचिन्हित पूर्णांक		options;
	अचिन्हित अक्षर		tlb_preload_count;
पूर्ण;

/*
 * Structure used to pass unload context parameters to the driver
 */
काष्ठा gru_unload_context_req अणु
	अचिन्हित दीर्घ	gseg;
पूर्ण;

/*
 * Structure used to set context options
 */
क्रमागत अणुsco_gseg_owner, sco_cch_req_slice, sco_blade_chipletपूर्ण;
काष्ठा gru_set_context_option_req अणु
	अचिन्हित दीर्घ	gseg;
	पूर्णांक		op;
	पूर्णांक		val0;
	दीर्घ		val1;
पूर्ण;

/*
 * Structure used to pass TLB flush parameters to the driver
 */
काष्ठा gru_flush_tlb_req अणु
	अचिन्हित दीर्घ	gseg;
	अचिन्हित दीर्घ	vaddr;
	माप_प्रकार		len;
पूर्ण;

/*
 * Structure used to pass TLB flush parameters to the driver
 */
क्रमागत अणुdcs_pid, dcs_gidपूर्ण;
काष्ठा gru_dump_chiplet_state_req अणु
	अचिन्हित पूर्णांक	op;
	अचिन्हित पूर्णांक	gid;
	पूर्णांक		ctxnum;
	अक्षर		data_opt;
	अक्षर		lock_cch;
	अक्षर		flush_cbrs;
	अक्षर		fill[10];
	pid_t		pid;
	व्योम		*buf;
	माप_प्रकार		buflen;
	/* ---- output --- */
	अचिन्हित पूर्णांक	num_contexts;
पूर्ण;

#घोषणा GRU_DUMP_MAGIC	0x3474ab6c
काष्ठा gru_dump_context_header अणु
	अचिन्हित पूर्णांक	magic;
	अचिन्हित पूर्णांक	gid;
	अचिन्हित अक्षर	ctxnum;
	अचिन्हित अक्षर	cbrcnt;
	अचिन्हित अक्षर	dsrcnt;
	pid_t		pid;
	अचिन्हित दीर्घ	vaddr;
	पूर्णांक		cch_locked;
	अचिन्हित दीर्घ	data[];
पूर्ण;

/*
 * GRU configuration info (temp - क्रम testing)
 */
काष्ठा gru_config_info अणु
	पूर्णांक		cpus;
	पूर्णांक		blades;
	पूर्णांक		nodes;
	पूर्णांक		chiplets;
	पूर्णांक		fill[16];
पूर्ण;

#पूर्ण_अगर /* __GRULIB_H__ */
