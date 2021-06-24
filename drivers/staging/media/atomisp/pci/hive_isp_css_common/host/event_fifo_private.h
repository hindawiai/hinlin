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

#अगर_अघोषित __EVENT_FIFO_PRIVATE_H
#घोषणा __EVENT_FIFO_PRIVATE_H

#समावेश "event_fifo_public.h"

#समावेश "device_access.h"

#समावेश "assert_support.h"

#समावेश <bits.h>			/* _hrt_get_bits() */

STORAGE_CLASS_EVENT_C व्योम event_रुको_क्रम(स्थिर event_ID_t ID)
अणु
	निश्चित(ID < N_EVENT_ID);
	निश्चित(event_source_addr[ID] != ((hrt_address) - 1));
	(व्योम)ia_css_device_load_uपूर्णांक32(event_source_addr[ID]);
	वापस;
पूर्ण

STORAGE_CLASS_EVENT_C व्योम cnd_event_रुको_क्रम(स्थिर event_ID_t ID,
	स्थिर bool cnd)
अणु
	अगर (cnd) अणु
		event_रुको_क्रम(ID);
	पूर्ण
पूर्ण

STORAGE_CLASS_EVENT_C hrt_data event_receive_token(स्थिर event_ID_t ID)
अणु
	निश्चित(ID < N_EVENT_ID);
	निश्चित(event_source_addr[ID] != ((hrt_address) - 1));
	वापस ia_css_device_load_uपूर्णांक32(event_source_addr[ID]);
पूर्ण

STORAGE_CLASS_EVENT_C व्योम event_send_token(स्थिर event_ID_t ID,
	स्थिर hrt_data token)
अणु
	निश्चित(ID < N_EVENT_ID);
	निश्चित(event_sink_addr[ID] != ((hrt_address) - 1));
	ia_css_device_store_uपूर्णांक32(event_sink_addr[ID], token);
पूर्ण

STORAGE_CLASS_EVENT_C bool is_event_pending(स्थिर event_ID_t ID)
अणु
	hrt_data	value;

	निश्चित(ID < N_EVENT_ID);
	निश्चित(event_source_query_addr[ID] != ((hrt_address) - 1));
	value = ia_css_device_load_uपूर्णांक32(event_source_query_addr[ID]);
	वापस !_hrt_get_bit(value, EVENT_QUERY_BIT);
पूर्ण

STORAGE_CLASS_EVENT_C bool can_event_send_token(स्थिर event_ID_t ID)
अणु
	hrt_data	value;

	निश्चित(ID < N_EVENT_ID);
	निश्चित(event_sink_query_addr[ID] != ((hrt_address) - 1));
	value = ia_css_device_load_uपूर्णांक32(event_sink_query_addr[ID]);
	वापस !_hrt_get_bit(value, EVENT_QUERY_BIT);
पूर्ण

#पूर्ण_अगर /* __EVENT_FIFO_PRIVATE_H */
