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

#अगर_अघोषित __SP_PUBLIC_H_INCLUDED__
#घोषणा __SP_PUBLIC_H_INCLUDED__

#समावेश <type_support.h>
#समावेश "system_local.h"

प्रकार काष्ठा sp_state_s		sp_state_t;
प्रकार काष्ठा sp_stall_s		sp_stall_t;

/*! Enable or disable the program complete irq संकेत of SP[ID]

 \param	ID[in]				SP identअगरier
 \param	cnd[in]				predicate

 \लeturn none, अगर(cnd) enable(SP[ID].irq) अन्यथा disable(SP[ID].irq)
 */
व्योम cnd_sp_irq_enable(
    स्थिर sp_ID_t		ID,
    स्थिर bool			cnd);

/*! Read the state of cell SP[ID]

 \param	ID[in]				SP identअगरier
 \param	state[out]			sp state काष्ठाure
 \param	stall[out]			isp stall conditions

 \लeturn none, state = SP[ID].state, stall = SP[ID].stall
 */
व्योम sp_get_state(
    स्थिर sp_ID_t		ID,
    sp_state_t			*state,
    sp_stall_t			*stall);

/*! Write to the status and control रेजिस्टर of SP[ID]

 \param	ID[in]				SP identअगरier
 \param	reg[in]				रेजिस्टर index
 \param value[in]			The data to be written

 \लeturn none, SP[ID].sc[reg] = value
 */
STORAGE_CLASS_SP_H व्योम sp_ctrl_store(
    स्थिर sp_ID_t		ID,
    स्थिर hrt_address	reg,
    स्थिर hrt_data		value);

/*! Read from the status and control रेजिस्टर of SP[ID]

 \param	ID[in]				SP identअगरier
 \param	reg[in]				रेजिस्टर index
 \param value[in]			The data to be written

 \लeturn SP[ID].sc[reg]
 */
STORAGE_CLASS_SP_H hrt_data sp_ctrl_load(
    स्थिर sp_ID_t		ID,
    स्थिर hrt_address	reg);

/*! Get the status of a bitfield in the control रेजिस्टर of SP[ID]

 \param	ID[in]				SP identअगरier
 \param	reg[in]				रेजिस्टर index
 \param bit[in]				The bit index to be checked

 \लeturn  (SP[ID].sc[reg] & (1<<bit)) != 0
 */
STORAGE_CLASS_SP_H bool sp_ctrl_getbit(
    स्थिर sp_ID_t		ID,
    स्थिर hrt_address	reg,
    स्थिर अचिन्हित पूर्णांक	bit);

/*! Set a bitfield in the control रेजिस्टर of SP[ID]

 \param	ID[in]				SP identअगरier
 \param	reg[in]				रेजिस्टर index
 \param bit[in]				The bit index to be set

 \लeturn none, SP[ID].sc[reg] |= (1<<bit)
 */
STORAGE_CLASS_SP_H व्योम sp_ctrl_setbit(
    स्थिर sp_ID_t		ID,
    स्थिर hrt_address	reg,
    स्थिर अचिन्हित पूर्णांक	bit);

/*! Clear a bitfield in the control रेजिस्टर of SP[ID]

 \param	ID[in]				SP identअगरier
 \param	reg[in]				रेजिस्टर index
 \param bit[in]				The bit index to be set

 \लeturn none, SP[ID].sc[reg] &= ~(1<<bit)
 */
STORAGE_CLASS_SP_H व्योम sp_ctrl_clearbit(
    स्थिर sp_ID_t		ID,
    स्थिर hrt_address	reg,
    स्थिर अचिन्हित पूर्णांक	bit);

/*! Write to the DMEM of SP[ID]

 \param	ID[in]				SP identअगरier
 \param	addr[in]			the address in DMEM
 \param data[in]			The data to be written
 \param size[in]			The size(in bytes) of the data to be written

 \लeturn none, SP[ID].dmem[addr...addr+size-1] = data
 */
STORAGE_CLASS_SP_H व्योम sp_dmem_store(
    स्थिर sp_ID_t		ID,
    hrt_address		addr,
    स्थिर व्योम			*data,
    स्थिर माप_प्रकार		size);

/*! Read from the DMEM of SP[ID]

 \param	ID[in]				SP identअगरier
 \param	addr[in]			the address in DMEM
 \param data[in]			The data to be पढ़ो
 \param size[in]			The size(in bytes) of the data to be पढ़ो

 \लeturn none, data = SP[ID].dmem[addr...addr+size-1]
 */
STORAGE_CLASS_SP_H व्योम sp_dmem_load(
    स्थिर sp_ID_t		ID,
    स्थिर hrt_address	addr,
    व्योम			*data,
    स्थिर माप_प्रकार		size);

/*! Write a 8-bit datum to the DMEM of SP[ID]

 \param	ID[in]				SP identअगरier
 \param	addr[in]			the address in DMEM
 \param data[in]			The data to be written
 \param size[in]			The size(in bytes) of the data to be written

 \लeturn none, SP[ID].dmem[addr...addr+size-1] = data
 */
STORAGE_CLASS_SP_H व्योम sp_dmem_store_uपूर्णांक8(
    स्थिर sp_ID_t		ID,
    hrt_address		addr,
    स्थिर uपूर्णांक8_t		data);

/*! Write a 16-bit datum to the DMEM of SP[ID]

 \param	ID[in]				SP identअगरier
 \param	addr[in]			the address in DMEM
 \param data[in]			The data to be written
 \param size[in]			The size(in bytes) of the data to be written

 \लeturn none, SP[ID].dmem[addr...addr+size-1] = data
 */
STORAGE_CLASS_SP_H व्योम sp_dmem_store_uपूर्णांक16(
    स्थिर sp_ID_t		ID,
    hrt_address		addr,
    स्थिर uपूर्णांक16_t		data);

/*! Write a 32-bit datum to the DMEM of SP[ID]

 \param	ID[in]				SP identअगरier
 \param	addr[in]			the address in DMEM
 \param data[in]			The data to be written
 \param size[in]			The size(in bytes) of the data to be written

 \लeturn none, SP[ID].dmem[addr...addr+size-1] = data
 */
STORAGE_CLASS_SP_H व्योम sp_dmem_store_uपूर्णांक32(
    स्थिर sp_ID_t		ID,
    hrt_address		addr,
    स्थिर uपूर्णांक32_t		data);

/*! Load a 8-bit datum from the DMEM of SP[ID]

 \param	ID[in]				SP identअगरier
 \param	addr[in]			the address in DMEM
 \param data[in]			The data to be पढ़ो
 \param size[in]			The size(in bytes) of the data to be पढ़ो

 \लeturn none, data = SP[ID].dmem[addr...addr+size-1]
 */
STORAGE_CLASS_SP_H uपूर्णांक8_t sp_dmem_load_uपूर्णांक8(
    स्थिर sp_ID_t		ID,
    स्थिर hrt_address	addr);

/*! Load a 16-bit datum from the DMEM of SP[ID]

 \param	ID[in]				SP identअगरier
 \param	addr[in]			the address in DMEM
 \param data[in]			The data to be पढ़ो
 \param size[in]			The size(in bytes) of the data to be पढ़ो

 \लeturn none, data = SP[ID].dmem[addr...addr+size-1]
 */
STORAGE_CLASS_SP_H uपूर्णांक16_t sp_dmem_load_uपूर्णांक16(
    स्थिर sp_ID_t		ID,
    स्थिर hrt_address	addr);

/*! Load a 32-bit datum from the DMEM of SP[ID]

 \param	ID[in]				SP identअगरier
 \param	addr[in]			the address in DMEM
 \param data[in]			The data to be पढ़ो
 \param size[in]			The size(in bytes) of the data to be पढ़ो

 \लeturn none, data = SP[ID].dmem[addr...addr+size-1]
 */
STORAGE_CLASS_SP_H uपूर्णांक32_t sp_dmem_load_uपूर्णांक32(
    स्थिर sp_ID_t		ID,
    स्थिर hrt_address	addr);

#पूर्ण_अगर /* __SP_PUBLIC_H_INCLUDED__ */
