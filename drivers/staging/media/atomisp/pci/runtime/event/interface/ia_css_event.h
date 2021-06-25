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

#अगर_अघोषित _IA_CSS_EVENT_H
#घोषणा _IA_CSS_EVENT_H

#समावेश <type_support.h>
#समावेश "sw_event_global.h"    /*event macros.TODO : Change File Name..???*/

bool ia_css_event_encode(
    u8	*in,
    u8	nr,
    uपूर्णांक32_t	*out);

व्योम ia_css_event_decode(
    u32 event,
    uपूर्णांक8_t *payload);

#पूर्ण_अगर /*_IA_CSS_EVENT_H*/
