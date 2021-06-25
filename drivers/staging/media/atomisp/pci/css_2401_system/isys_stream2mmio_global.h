<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
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

#अगर_अघोषित __ISYS_STREAM2MMIO_GLOBAL_H_INCLUDED__
#घोषणा __ISYS_STREAM2MMIO_GLOBAL_H_INCLUDED__

#समावेश <type_support.h>

प्रकार काष्ठा stream2mmio_cfg_s stream2mmio_cfg_t;
काष्ठा stream2mmio_cfg_s अणु
	u32				bits_per_pixel;
	u32				enable_blocking;
पूर्ण;

/* Stream2MMIO limits  per ID*/
/*
 * Stream2MMIO 0 has 8 SIDs that are indexed by
 * [STREAM2MMIO_SID0_ID...STREAM2MMIO_SID7_ID].
 *
 * Stream2MMIO 1 has 4 SIDs that are indexed by
 * [STREAM2MMIO_SID0_ID...TREAM2MMIO_SID3_ID].
 *
 * Stream2MMIO 2 has 4 SIDs that are indexed by
 * [STREAM2MMIO_SID0_ID...STREAM2MMIO_SID3_ID].
 */
बाह्य स्थिर stream2mmio_sid_ID_t N_STREAM2MMIO_SID_PROCS[N_STREAM2MMIO_ID];

#पूर्ण_अगर /* __ISYS_STREAM2MMIO_GLOBAL_H_INCLUDED__ */
