<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
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

#अगर_अघोषित __IBUF_CTRL_RMGR_H_INCLUDED__
#घोषणा __IBUF_CTRL_RMGR_H_INCLUDED__

#घोषणा MAX_IBUF_HANDLES	24
#घोषणा MAX_INPUT_BUFFER_SIZE	(64 * 1024)
#घोषणा IBUF_ALIGN		8

प्रकार काष्ठा ibuf_handle_s ibuf_handle_t;
काष्ठा ibuf_handle_s अणु
	u32	start_addr;
	u32	size;
	bool		active;
पूर्ण;

प्रकार काष्ठा ibuf_rsrc_s ibuf_rsrc_t;
काष्ठा ibuf_rsrc_s अणु
	u32	मुक्त_start_addr;
	u32	मुक्त_size;
	u16	num_active;
	u16	num_allocated;
	ibuf_handle_t	handles[MAX_IBUF_HANDLES];
पूर्ण;

#पूर्ण_अगर /* __IBUF_CTRL_RMGR_H_INCLUDED */
