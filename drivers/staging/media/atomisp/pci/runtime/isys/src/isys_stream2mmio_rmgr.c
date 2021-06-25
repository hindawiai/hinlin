<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2010 - 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#समावेश "system_global.h"

#अगर_घोषित ISP2401

#समावेश "assert_support.h"
#समावेश "platform_support.h"
#समावेश "ia_css_isys.h"
#समावेश "bitop_support.h"
#समावेश "isys_stream2mmio_rmgr.h"

अटल isys_stream2mmio_rsrc_t	isys_stream2mmio_rsrc[N_STREAM2MMIO_ID];

व्योम ia_css_isys_stream2mmio_sid_rmgr_init(व्योम)
अणु
	स_रखो(isys_stream2mmio_rsrc, 0, माप(isys_stream2mmio_rsrc));
पूर्ण

व्योम ia_css_isys_stream2mmio_sid_rmgr_uninit(व्योम)
अणु
	स_रखो(isys_stream2mmio_rsrc, 0, माप(isys_stream2mmio_rsrc));
पूर्ण

bool ia_css_isys_stream2mmio_sid_rmgr_acquire(
    stream2mmio_ID_t	stream2mmio,
    stream2mmio_sid_ID_t	*sid)
अणु
	bool retval = false;
	stream2mmio_sid_ID_t max_sid;
	isys_stream2mmio_rsrc_t *cur_rsrc = शून्य;
	stream2mmio_sid_ID_t	i;

	निश्चित(stream2mmio < N_STREAM2MMIO_ID);
	निश्चित(sid);

	अगर ((stream2mmio < N_STREAM2MMIO_ID) && (sid)) अणु
		max_sid = N_STREAM2MMIO_SID_PROCS[stream2mmio];
		cur_rsrc = &isys_stream2mmio_rsrc[stream2mmio];

		अगर (cur_rsrc->num_active < max_sid) अणु
			क्रम (i = STREAM2MMIO_SID0_ID; i < max_sid; i++) अणु
				अगर (bitop_getbit(cur_rsrc->active_table, i) == 0) अणु
					bitop_setbit(cur_rsrc->active_table, i);
					*sid = i;
					cur_rsrc->num_active++;
					retval = true;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस retval;
पूर्ण

व्योम ia_css_isys_stream2mmio_sid_rmgr_release(
    stream2mmio_ID_t	stream2mmio,
    stream2mmio_sid_ID_t	*sid)
अणु
	stream2mmio_sid_ID_t max_sid;
	isys_stream2mmio_rsrc_t *cur_rsrc = शून्य;

	निश्चित(stream2mmio < N_STREAM2MMIO_ID);
	निश्चित(sid);

	अगर ((stream2mmio < N_STREAM2MMIO_ID) && (sid)) अणु
		max_sid = N_STREAM2MMIO_SID_PROCS[stream2mmio];
		cur_rsrc = &isys_stream2mmio_rsrc[stream2mmio];
		अगर ((*sid < max_sid) && (cur_rsrc->num_active > 0)) अणु
			अगर (bitop_getbit(cur_rsrc->active_table, *sid) == 1) अणु
				bitop_clearbit(cur_rsrc->active_table, *sid);
				cur_rsrc->num_active--;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर
