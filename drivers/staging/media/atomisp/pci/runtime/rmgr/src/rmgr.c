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

#समावेश "ia_css_rmgr.h"

पूर्णांक ia_css_rmgr_init(व्योम)
अणु
	पूर्णांक err = 0;

	err = ia_css_rmgr_init_vbuf(vbuf_ref);
	अगर (!err)
		err = ia_css_rmgr_init_vbuf(vbuf_ग_लिखो);
	अगर (!err)
		err = ia_css_rmgr_init_vbuf(hmm_buffer_pool);
	अगर (err)
		ia_css_rmgr_uninit();
	वापस err;
पूर्ण

/*
 * @brief Uninitialize resource pool (host)
 */
व्योम ia_css_rmgr_uninit(व्योम)
अणु
	ia_css_rmgr_uninit_vbuf(hmm_buffer_pool);
	ia_css_rmgr_uninit_vbuf(vbuf_ग_लिखो);
	ia_css_rmgr_uninit_vbuf(vbuf_ref);
पूर्ण
