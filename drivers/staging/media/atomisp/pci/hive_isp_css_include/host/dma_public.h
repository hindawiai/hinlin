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

#अगर_अघोषित __DMA_PUBLIC_H_INCLUDED__
#घोषणा __DMA_PUBLIC_H_INCLUDED__

#समावेश "system_local.h"

प्रकार काष्ठा dma_state_s		dma_state_t;

/*! Read the control रेजिस्टरs of DMA[ID]

 \param	ID[in]				DMA identअगरier
 \param	state[out]			input क्रमmatter state काष्ठाure

 \लeturn none, state = DMA[ID].state
 */
व्योम dma_get_state(
    स्थिर dma_ID_t		ID,
    dma_state_t			*state);

/*! Write to a control रेजिस्टर of DMA[ID]

 \param	ID[in]				DMA identअगरier
 \param	reg[in]				रेजिस्टर index
 \param value[in]			The data to be written

 \लeturn none, DMA[ID].ctrl[reg] = value
 */
STORAGE_CLASS_DMA_H व्योम dma_reg_store(
    स्थिर dma_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक	reg,
    स्थिर hrt_data		value);

/*! Read from a control रेजिस्टर of DMA[ID]

 \param	ID[in]				DMA identअगरier
 \param	reg[in]				रेजिस्टर index
 \param value[in]			The data to be written

 \लeturn DMA[ID].ctrl[reg]
 */
STORAGE_CLASS_DMA_H hrt_data dma_reg_load(
    स्थिर dma_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक	reg);

/*! Set maximum burst size of DMA[ID]

 \param ID[in]				DMA identअगरier
 \param conn[in]			Connection to set max burst size क्रम
 \param max_burst_size[in]		Maximum burst size in words

 \लeturn none
*/
व्योम
dma_set_max_burst_size(
    dma_ID_t		ID,
    dma_connection		conn,
    uपूर्णांक32_t		max_burst_size);

#पूर्ण_अगर /* __DMA_PUBLIC_H_INCLUDED__ */
