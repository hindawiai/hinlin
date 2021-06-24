<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2010-2015, Intel Corporation.
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

#अगर_अघोषित __FIFO_MONITOR_PRIVATE_H_INCLUDED__
#घोषणा __FIFO_MONITOR_PRIVATE_H_INCLUDED__

#समावेश "fifo_monitor_public.h"

#घोषणा __INLINE_GP_DEVICE__
#समावेश "gp_device.h"

#समावेश "device_access.h"

#समावेश "assert_support.h"

#अगर_घोषित __INLINE_FIFO_MONITOR__
बाह्य स्थिर अचिन्हित पूर्णांक FIFO_SWITCH_ADDR[N_FIFO_SWITCH];
#पूर्ण_अगर

STORAGE_CLASS_FIFO_MONITOR_C व्योम fअगरo_चयन_set(
    स्थिर fअगरo_monitor_ID_t		ID,
    स्थिर fअगरo_चयन_t			चयन_id,
    स्थिर hrt_data				sel)
अणु
	निश्चित(ID == FIFO_MONITOR0_ID);
	निश्चित(FIFO_MONITOR_BASE[ID] != (hrt_address) - 1);
	निश्चित(चयन_id < N_FIFO_SWITCH);
	(व्योम)ID;

	gp_device_reg_store(GP_DEVICE0_ID, FIFO_SWITCH_ADDR[चयन_id], sel);

	वापस;
पूर्ण

STORAGE_CLASS_FIFO_MONITOR_C hrt_data fअगरo_चयन_get(
    स्थिर fअगरo_monitor_ID_t		ID,
    स्थिर fअगरo_चयन_t			चयन_id)
अणु
	निश्चित(ID == FIFO_MONITOR0_ID);
	निश्चित(FIFO_MONITOR_BASE[ID] != (hrt_address) - 1);
	निश्चित(चयन_id < N_FIFO_SWITCH);
	(व्योम)ID;

	वापस gp_device_reg_load(GP_DEVICE0_ID, FIFO_SWITCH_ADDR[चयन_id]);
पूर्ण

STORAGE_CLASS_FIFO_MONITOR_C व्योम fअगरo_monitor_reg_store(
    स्थिर fअगरo_monitor_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक			reg,
    स्थिर hrt_data				value)
अणु
	निश्चित(ID < N_FIFO_MONITOR_ID);
	निश्चित(FIFO_MONITOR_BASE[ID] != (hrt_address) - 1);
	ia_css_device_store_uपूर्णांक32(FIFO_MONITOR_BASE[ID] + reg * माप(hrt_data),
				   value);
	वापस;
पूर्ण

STORAGE_CLASS_FIFO_MONITOR_C hrt_data fअगरo_monitor_reg_load(
    स्थिर fअगरo_monitor_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक			reg)
अणु
	निश्चित(ID < N_FIFO_MONITOR_ID);
	निश्चित(FIFO_MONITOR_BASE[ID] != (hrt_address) - 1);
	वापस ia_css_device_load_uपूर्णांक32(FIFO_MONITOR_BASE[ID] + reg * माप(
					     hrt_data));
पूर्ण

#पूर्ण_अगर /* __FIFO_MONITOR_PRIVATE_H_INCLUDED__ */
