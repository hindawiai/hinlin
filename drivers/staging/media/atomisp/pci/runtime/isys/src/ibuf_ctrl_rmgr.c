<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
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

#समावेश "assert_support.h"
#समावेश "platform_support.h"
#समावेश "ia_css_isys.h"
#समावेश "ibuf_ctrl_rmgr.h"

अटल ibuf_rsrc_t	ibuf_rsrc;

अटल ibuf_handle_t *getHandle(uपूर्णांक16_t index)
अणु
	ibuf_handle_t *handle = शून्य;

	अगर (index < MAX_IBUF_HANDLES)
		handle = &ibuf_rsrc.handles[index];
	वापस handle;
पूर्ण

व्योम ia_css_isys_ibuf_rmgr_init(व्योम)
अणु
	स_रखो(&ibuf_rsrc, 0, माप(ibuf_rsrc));
	ibuf_rsrc.मुक्त_size = MAX_INPUT_BUFFER_SIZE;
पूर्ण

व्योम ia_css_isys_ibuf_rmgr_uninit(व्योम)
अणु
	स_रखो(&ibuf_rsrc, 0, माप(ibuf_rsrc));
	ibuf_rsrc.मुक्त_size = MAX_INPUT_BUFFER_SIZE;
पूर्ण

bool ia_css_isys_ibuf_rmgr_acquire(
    u32	size,
    uपूर्णांक32_t	*start_addr)
अणु
	bool retval = false;
	bool input_buffer_found = false;
	u32 aligned_size;
	ibuf_handle_t *handle = शून्य;
	u16 i;

	निश्चित(start_addr);
	निश्चित(size > 0);

	aligned_size = (size + (IBUF_ALIGN - 1)) & ~(IBUF_ALIGN - 1);

	/* Check अगर there is an available un-used handle with the size
	 * that will fulfill the request.
	 */
	अगर (ibuf_rsrc.num_active < ibuf_rsrc.num_allocated) अणु
		क्रम (i = 0; i < ibuf_rsrc.num_allocated; i++) अणु
			handle = getHandle(i);
			अगर (!handle->active) अणु
				अगर (handle->size >= aligned_size) अणु
					handle->active = true;
					input_buffer_found = true;
					ibuf_rsrc.num_active++;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!input_buffer_found) अणु
		/* There were no available handles that fulfilled the
		 * request. Allocate a new handle with the requested size.
		 */
		अगर ((ibuf_rsrc.num_allocated < MAX_IBUF_HANDLES) &&
		    (ibuf_rsrc.मुक्त_size >= aligned_size)) अणु
			handle = getHandle(ibuf_rsrc.num_allocated);
			handle->start_addr	= ibuf_rsrc.मुक्त_start_addr;
			handle->size		= aligned_size;
			handle->active		= true;

			ibuf_rsrc.मुक्त_start_addr += aligned_size;
			ibuf_rsrc.मुक्त_size -= aligned_size;
			ibuf_rsrc.num_active++;
			ibuf_rsrc.num_allocated++;

			input_buffer_found = true;
		पूर्ण
	पूर्ण

	अगर (input_buffer_found && handle) अणु
		*start_addr = handle->start_addr;
		retval = true;
	पूर्ण

	वापस retval;
पूर्ण

व्योम ia_css_isys_ibuf_rmgr_release(
    uपूर्णांक32_t	*start_addr)
अणु
	u16 i;
	ibuf_handle_t *handle = शून्य;

	निश्चित(start_addr);

	क्रम (i = 0; i < ibuf_rsrc.num_allocated; i++) अणु
		handle = getHandle(i);
		अगर (handle->active && handle->start_addr == *start_addr) अणु
			handle->active = false;
			ibuf_rsrc.num_active--;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण
