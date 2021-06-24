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

#अगर_अघोषित __INPUT_SYSTEM_PRIVATE_H_INCLUDED__
#घोषणा __INPUT_SYSTEM_PRIVATE_H_INCLUDED__

#समावेश "input_system_public.h"

#समावेश "device_access.h"

#समावेश "assert_support.h"

STORAGE_CLASS_INPUT_SYSTEM_C व्योम input_प्रणाली_reg_store(
    स्थिर input_प्रणाली_ID_t			ID,
    स्थिर hrt_address			reg,
    स्थिर hrt_data				value)
अणु
	निश्चित(ID < N_INPUT_SYSTEM_ID);
	निश्चित(INPUT_SYSTEM_BASE[ID] != (hrt_address)-1);
	ia_css_device_store_uपूर्णांक32(INPUT_SYSTEM_BASE[ID] + reg * माप(hrt_data),
				   value);
	वापस;
पूर्ण

STORAGE_CLASS_INPUT_SYSTEM_C hrt_data input_प्रणाली_reg_load(
    स्थिर input_प्रणाली_ID_t			ID,
    स्थिर hrt_address			reg)
अणु
	निश्चित(ID < N_INPUT_SYSTEM_ID);
	निश्चित(INPUT_SYSTEM_BASE[ID] != (hrt_address)-1);
	वापस ia_css_device_load_uपूर्णांक32(INPUT_SYSTEM_BASE[ID] + reg * माप(
					     hrt_data));
पूर्ण

STORAGE_CLASS_INPUT_SYSTEM_C व्योम receiver_reg_store(
    स्थिर rx_ID_t				ID,
    स्थिर hrt_address			reg,
    स्थिर hrt_data				value)
अणु
	निश्चित(ID < N_RX_ID);
	निश्चित(RX_BASE[ID] != (hrt_address)-1);
	ia_css_device_store_uपूर्णांक32(RX_BASE[ID] + reg * माप(hrt_data), value);
	वापस;
पूर्ण

STORAGE_CLASS_INPUT_SYSTEM_C hrt_data receiver_reg_load(
    स्थिर rx_ID_t				ID,
    स्थिर hrt_address			reg)
अणु
	निश्चित(ID < N_RX_ID);
	निश्चित(RX_BASE[ID] != (hrt_address)-1);
	वापस ia_css_device_load_uपूर्णांक32(RX_BASE[ID] + reg * माप(hrt_data));
पूर्ण

STORAGE_CLASS_INPUT_SYSTEM_C व्योम receiver_port_reg_store(
    स्थिर rx_ID_t				ID,
    स्थिर क्रमागत mipi_port_id			port_ID,
    स्थिर hrt_address			reg,
    स्थिर hrt_data				value)
अणु
	निश्चित(ID < N_RX_ID);
	निश्चित(port_ID < N_MIPI_PORT_ID);
	निश्चित(RX_BASE[ID] != (hrt_address)-1);
	निश्चित(MIPI_PORT_OFFSET[port_ID] != (hrt_address)-1);
	ia_css_device_store_uपूर्णांक32(RX_BASE[ID] + MIPI_PORT_OFFSET[port_ID] + reg *
				   माप(hrt_data), value);
	वापस;
पूर्ण

STORAGE_CLASS_INPUT_SYSTEM_C hrt_data receiver_port_reg_load(
    स्थिर rx_ID_t				ID,
    स्थिर क्रमागत mipi_port_id			port_ID,
    स्थिर hrt_address			reg)
अणु
	निश्चित(ID < N_RX_ID);
	निश्चित(port_ID < N_MIPI_PORT_ID);
	निश्चित(RX_BASE[ID] != (hrt_address)-1);
	निश्चित(MIPI_PORT_OFFSET[port_ID] != (hrt_address)-1);
	वापस ia_css_device_load_uपूर्णांक32(RX_BASE[ID] + MIPI_PORT_OFFSET[port_ID] + reg *
					 माप(hrt_data));
पूर्ण

STORAGE_CLASS_INPUT_SYSTEM_C व्योम input_प्रणाली_sub_प्रणाली_reg_store(
    स्थिर input_प्रणाली_ID_t			ID,
    स्थिर sub_प्रणाली_ID_t			sub_ID,
    स्थिर hrt_address			reg,
    स्थिर hrt_data				value)
अणु
	निश्चित(ID < N_INPUT_SYSTEM_ID);
	निश्चित(sub_ID < N_SUB_SYSTEM_ID);
	निश्चित(INPUT_SYSTEM_BASE[ID] != (hrt_address)-1);
	निश्चित(SUB_SYSTEM_OFFSET[sub_ID] != (hrt_address)-1);
	ia_css_device_store_uपूर्णांक32(INPUT_SYSTEM_BASE[ID] + SUB_SYSTEM_OFFSET[sub_ID] +
				   reg * माप(hrt_data), value);
	वापस;
पूर्ण

STORAGE_CLASS_INPUT_SYSTEM_C hrt_data input_प्रणाली_sub_प्रणाली_reg_load(
    स्थिर input_प्रणाली_ID_t			ID,
    स्थिर sub_प्रणाली_ID_t			sub_ID,
    स्थिर hrt_address			reg)
अणु
	निश्चित(ID < N_INPUT_SYSTEM_ID);
	निश्चित(sub_ID < N_SUB_SYSTEM_ID);
	निश्चित(INPUT_SYSTEM_BASE[ID] != (hrt_address)-1);
	निश्चित(SUB_SYSTEM_OFFSET[sub_ID] != (hrt_address)-1);
	वापस ia_css_device_load_uपूर्णांक32(INPUT_SYSTEM_BASE[ID] +
					 SUB_SYSTEM_OFFSET[sub_ID] + reg * माप(hrt_data));
पूर्ण

#पूर्ण_अगर /* __INPUT_SYSTEM_PRIVATE_H_INCLUDED__ */
