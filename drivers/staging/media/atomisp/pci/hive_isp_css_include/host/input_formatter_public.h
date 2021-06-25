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

#अगर_अघोषित __INPUT_FORMATTER_PUBLIC_H_INCLUDED__
#घोषणा __INPUT_FORMATTER_PUBLIC_H_INCLUDED__

#समावेश <type_support.h>
#समावेश "system_local.h"

/*! Reset INPUT_FORMATTER[ID]

 \param	ID[in]				INPUT_FORMATTER identअगरier

 \लeturn none, reset(INPUT_FORMATTER[ID])
 */
व्योम input_क्रमmatter_rst(
    स्थिर input_क्रमmatter_ID_t		ID);

/*! Set the blocking mode of INPUT_FORMATTER[ID]

 \param	ID[in]				INPUT_FORMATTER identअगरier
 \param	enable[in]			blocking enable flag

 \use
	- In HW, the capture unit will deliver an infinite stream of frames,
	  the input क्रमmatter will synchronise on the first SOF. In simulation
	  there are only a fixed number of frames, presented only once. By
	  enabling blocking the inputक्रमmatter will रुको on the first presented
	  frame, thus aव्योमing race in the simulation setup.

 \लeturn none, INPUT_FORMATTER[ID].blocking_mode = enable
 */
व्योम input_क्रमmatter_set_fअगरo_blocking_mode(
    स्थिर input_क्रमmatter_ID_t		ID,
    स्थिर bool						enable);

/*! Return the data alignment of INPUT_FORMATTER[ID]

 \param	ID[in]				INPUT_FORMATTER identअगरier

 \लeturn alignment(INPUT_FORMATTER[ID].data)
 */
अचिन्हित पूर्णांक input_क्रमmatter_get_alignment(
    स्थिर input_क्रमmatter_ID_t		ID);

/*! Read the source चयन state पूर्णांकo INPUT_FORMATTER[ID]

 \param	ID[in]				INPUT_FORMATTER identअगरier
 \param	state[out]			input क्रमmatter चयन state काष्ठाure

 \लeturn none, state = INPUT_FORMATTER[ID].चयन_state
 */
व्योम input_क्रमmatter_get_चयन_state(
    स्थिर input_क्रमmatter_ID_t		ID,
    input_क्रमmatter_चयन_state_t	*state);

/*! Read the control रेजिस्टरs of INPUT_FORMATTER[ID]

 \param	ID[in]				INPUT_FORMATTER identअगरier
 \param	state[out]			input क्रमmatter state काष्ठाure

 \लeturn none, state = INPUT_FORMATTER[ID].state
 */
व्योम input_क्रमmatter_get_state(
    स्थिर input_क्रमmatter_ID_t		ID,
    input_क्रमmatter_state_t			*state);

/*! Read the control रेजिस्टरs of bin copy INPUT_FORMATTER[ID]

 \param	ID[in]				INPUT_FORMATTER identअगरier
 \param	state[out]			input क्रमmatter state काष्ठाure

 \लeturn none, state = INPUT_FORMATTER[ID].state
 */
व्योम input_क्रमmatter_bin_get_state(
    स्थिर input_क्रमmatter_ID_t		ID,
    input_क्रमmatter_bin_state_t		*state);

/*! Write to a control रेजिस्टर of INPUT_FORMATTER[ID]

 \param	ID[in]				INPUT_FORMATTER identअगरier
 \param	reg_addr[in]		रेजिस्टर byte address
 \param value[in]			The data to be written

 \लeturn none, INPUT_FORMATTER[ID].ctrl[reg] = value
 */
STORAGE_CLASS_INPUT_FORMATTER_H व्योम input_क्रमmatter_reg_store(
    स्थिर input_क्रमmatter_ID_t	ID,
    स्थिर hrt_address		reg_addr,
    स्थिर hrt_data				value);

/*! Read from a control रेजिस्टर of INPUT_FORMATTER[ID]

 \param	ID[in]				INPUT_FORMATTER identअगरier
 \param	reg_addr[in]		रेजिस्टर byte address
 \param value[in]			The data to be written

 \लeturn INPUT_FORMATTER[ID].ctrl[reg]
 */
STORAGE_CLASS_INPUT_FORMATTER_H hrt_data input_क्रमmatter_reg_load(
    स्थिर input_क्रमmatter_ID_t	ID,
    स्थिर अचिन्हित पूर्णांक			reg_addr);

#पूर्ण_अगर /* __INPUT_FORMATTER_PUBLIC_H_INCLUDED__ */
