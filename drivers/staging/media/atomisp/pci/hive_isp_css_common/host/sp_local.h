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

#अगर_अघोषित __SP_LOCAL_H_INCLUDED__
#घोषणा __SP_LOCAL_H_INCLUDED__

#समावेश <type_support.h>
#समावेश "sp_global.h"

काष्ठा sp_state_s अणु
	पूर्णांक		pc;
	पूर्णांक		status_रेजिस्टर;
	bool	is_broken;
	bool	is_idle;
	bool	is_sleeping;
	bool	is_stalling;
पूर्ण;

काष्ठा sp_stall_s अणु
	bool	fअगरo0;
	bool	fअगरo1;
	bool	fअगरo2;
	bool	fअगरo3;
	bool	fअगरo4;
	bool	fअगरo5;
	bool	fअगरo6;
	bool	fअगरo7;
	bool	fअगरo8;
	bool	fअगरo9;
	bool	fअगरoa;
	bool	dmem;
	bool	control_master;
	bool	icache_master;
पूर्ण;

#घोषणा sp_address_of(var)	(HIVE_ADDR_ ## var)

/*
 * deprecated
 */
#घोषणा store_sp_पूर्णांक(var, value) \
	sp_dmem_store_uपूर्णांक32(SP0_ID, (अचिन्हित पूर्णांक)sp_address_of(var), \
		(uपूर्णांक32_t)(value))

#घोषणा store_sp_ptr(var, value) \
	sp_dmem_store_uपूर्णांक32(SP0_ID, (अचिन्हित पूर्णांक)sp_address_of(var), \
		(uपूर्णांक32_t)(value))

#घोषणा load_sp_uपूर्णांक(var) \
	sp_dmem_load_uपूर्णांक32(SP0_ID, (अचिन्हित पूर्णांक)sp_address_of(var))

#घोषणा load_sp_array_uपूर्णांक8(array_name, index) \
	sp_dmem_load_uपूर्णांक8(SP0_ID, (अचिन्हित पूर्णांक)sp_address_of(array_name) + \
		(index) * माप(uपूर्णांक8_t))

#घोषणा load_sp_array_uपूर्णांक16(array_name, index) \
	sp_dmem_load_uपूर्णांक16(SP0_ID, (अचिन्हित पूर्णांक)sp_address_of(array_name) + \
		(index) * माप(uपूर्णांक16_t))

#घोषणा load_sp_array_uपूर्णांक(array_name, index) \
	sp_dmem_load_uपूर्णांक32(SP0_ID, (अचिन्हित पूर्णांक)sp_address_of(array_name) + \
		(index) * माप(uपूर्णांक32_t))

#घोषणा store_sp_var(var, data, bytes) \
	sp_dmem_store(SP0_ID, (अचिन्हित पूर्णांक)sp_address_of(var), data, bytes)

#घोषणा store_sp_array_uपूर्णांक8(array_name, index, value) \
	sp_dmem_store_uपूर्णांक8(SP0_ID, (अचिन्हित पूर्णांक)sp_address_of(array_name) + \
		(index) * माप(uपूर्णांक8_t), value)

#घोषणा store_sp_array_uपूर्णांक16(array_name, index, value) \
	sp_dmem_store_uपूर्णांक16(SP0_ID, (अचिन्हित पूर्णांक)sp_address_of(array_name) + \
		(index) * माप(uपूर्णांक16_t), value)

#घोषणा store_sp_array_uपूर्णांक(array_name, index, value) \
	sp_dmem_store_uपूर्णांक32(SP0_ID, (अचिन्हित पूर्णांक)sp_address_of(array_name) + \
		(index) * माप(uपूर्णांक32_t), value)

#घोषणा store_sp_var_with_offset(var, offset, data, bytes) \
	sp_dmem_store(SP0_ID, (अचिन्हित पूर्णांक)sp_address_of(var) + \
		offset, data, bytes)

#घोषणा load_sp_var(var, data, bytes) \
	sp_dmem_load(SP0_ID, (अचिन्हित पूर्णांक)sp_address_of(var), data, bytes)

#घोषणा load_sp_var_with_offset(var, offset, data, bytes) \
	sp_dmem_load(SP0_ID, (अचिन्हित पूर्णांक)sp_address_of(var) + offset, \
		data, bytes)

#पूर्ण_अगर /* __SP_LOCAL_H_INCLUDED__ */
