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

#अगर_अघोषित __ISP_PUBLIC_H_INCLUDED__
#घोषणा __ISP_PUBLIC_H_INCLUDED__

#समावेश <type_support.h>
#समावेश "system_local.h"

/*! Enable or disable the program complete irq संकेत of ISP[ID]

 \param	ID[in]				SP identअगरier
 \param	cnd[in]				predicate

 \लeturn none, अगर(cnd) enable(ISP[ID].irq) अन्यथा disable(ISP[ID].irq)
 */
व्योम cnd_isp_irq_enable(
    स्थिर isp_ID_t		ID,
    स्थिर bool			cnd);

/*! Read the state of cell ISP[ID]

 \param	ID[in]				ISP identअगरier
 \param	state[out]			isp state काष्ठाure
 \param	stall[out]			isp stall conditions

 \लeturn none, state = ISP[ID].state, stall = ISP[ID].stall
 */
व्योम isp_get_state(
    स्थिर isp_ID_t		ID,
    isp_state_t			*state,
    isp_stall_t			*stall);

/*! Write to the status and control रेजिस्टर of ISP[ID]

 \param	ID[in]				ISP identअगरier
 \param	reg[in]				रेजिस्टर index
 \param value[in]			The data to be written

 \लeturn none, ISP[ID].sc[reg] = value
 */
STORAGE_CLASS_ISP_H व्योम isp_ctrl_store(
    स्थिर isp_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक	reg,
    स्थिर hrt_data		value);

/*! Read from the status and control रेजिस्टर of ISP[ID]

 \param	ID[in]				ISP identअगरier
 \param	reg[in]				रेजिस्टर index
 \param value[in]			The data to be written

 \लeturn ISP[ID].sc[reg]
 */
STORAGE_CLASS_ISP_H hrt_data isp_ctrl_load(
    स्थिर isp_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक	reg);

/*! Get the status of a bitfield in the control रेजिस्टर of ISP[ID]

 \param	ID[in]				ISP identअगरier
 \param	reg[in]				रेजिस्टर index
 \param bit[in]				The bit index to be checked

 \लeturn  (ISP[ID].sc[reg] & (1<<bit)) != 0
 */
STORAGE_CLASS_ISP_H bool isp_ctrl_getbit(
    स्थिर isp_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक	reg,
    स्थिर अचिन्हित पूर्णांक	bit);

/*! Set a bitfield in the control रेजिस्टर of ISP[ID]

 \param	ID[in]				ISP identअगरier
 \param	reg[in]				रेजिस्टर index
 \param bit[in]				The bit index to be set

 \लeturn none, ISP[ID].sc[reg] |= (1<<bit)
 */
STORAGE_CLASS_ISP_H व्योम isp_ctrl_setbit(
    स्थिर isp_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक	reg,
    स्थिर अचिन्हित पूर्णांक	bit);

/*! Clear a bitfield in the control रेजिस्टर of ISP[ID]

 \param	ID[in]				ISP identअगरier
 \param	reg[in]				रेजिस्टर index
 \param bit[in]				The bit index to be set

 \लeturn none, ISP[ID].sc[reg] &= ~(1<<bit)
 */
STORAGE_CLASS_ISP_H व्योम isp_ctrl_clearbit(
    स्थिर isp_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक	reg,
    स्थिर अचिन्हित पूर्णांक	bit);

/*! Write to the DMEM of ISP[ID]

 \param	ID[in]				ISP identअगरier
 \param	addr[in]			the address in DMEM
 \param data[in]			The data to be written
 \param size[in]			The size(in bytes) of the data to be written

 \लeturn none, ISP[ID].dmem[addr...addr+size-1] = data
 */
STORAGE_CLASS_ISP_H व्योम isp_dmem_store(
    स्थिर isp_ID_t		ID,
    अचिन्हित पूर्णांक		addr,
    स्थिर व्योम			*data,
    स्थिर माप_प्रकार		size);

/*! Read from the DMEM of ISP[ID]

 \param	ID[in]				ISP identअगरier
 \param	addr[in]			the address in DMEM
 \param data[in]			The data to be पढ़ो
 \param size[in]			The size(in bytes) of the data to be पढ़ो

 \लeturn none, data = ISP[ID].dmem[addr...addr+size-1]
 */
STORAGE_CLASS_ISP_H व्योम isp_dmem_load(
    स्थिर isp_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक	addr,
    व्योम				*data,
    स्थिर माप_प्रकार		size);

/*! Write a 32-bit datum to the DMEM of ISP[ID]

 \param	ID[in]				ISP identअगरier
 \param	addr[in]			the address in DMEM
 \param data[in]			The data to be written
 \param size[in]			The size(in bytes) of the data to be written

 \लeturn none, ISP[ID].dmem[addr] = data
 */
STORAGE_CLASS_ISP_H व्योम isp_dmem_store_uपूर्णांक32(
    स्थिर isp_ID_t		ID,
    अचिन्हित पूर्णांक		addr,
    स्थिर uपूर्णांक32_t		data);

/*! Load a 32-bit datum from the DMEM of ISP[ID]

 \param	ID[in]				ISP identअगरier
 \param	addr[in]			the address in DMEM
 \param data[in]			The data to be पढ़ो
 \param size[in]			The size(in bytes) of the data to be पढ़ो

 \लeturn none, data = ISP[ID].dmem[addr]
 */
STORAGE_CLASS_ISP_H uपूर्णांक32_t isp_dmem_load_uपूर्णांक32(
    स्थिर isp_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक	addr);

/*! Concatenate the LSW and MSW पूर्णांकo a द्विगुन precision word

 \param	x0[in]				Integer containing the LSW
 \param	x1[in]				Integer containing the MSW

 \लeturn x0 | (x1 << bits_per_vector_element)
 */
STORAGE_CLASS_ISP_H uपूर्णांक32_t isp_2w_cat_1w(
    स्थिर u16		x0,
    स्थिर uपूर्णांक16_t		x1);

अचिन्हित पूर्णांक isp_is_पढ़ोy(isp_ID_t ID);

अचिन्हित पूर्णांक isp_is_sleeping(isp_ID_t ID);

व्योम isp_start(isp_ID_t ID);

व्योम isp_wake(isp_ID_t ID);

#पूर्ण_अगर /* __ISP_PUBLIC_H_INCLUDED__ */
