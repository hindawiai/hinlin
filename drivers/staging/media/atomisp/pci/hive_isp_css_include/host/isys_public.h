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

#अगर_अघोषित __ISYS_PUBLIC_H_INCLUDED__
#घोषणा __ISYS_PUBLIC_H_INCLUDED__

#अगर_घोषित ISP2401
/*! Read the state of INPUT_SYSTEM[ID]
 \param ID[in]		INPUT_SYSTEM identअगरier
 \param state[out]	poपूर्णांकer to input प्रणाली state काष्ठाure
 \लeturn none, state = INPUT_SYSTEM[ID].state
 */
STORAGE_CLASS_INPUT_SYSTEM_H input_प्रणाली_err_t input_प्रणाली_get_state(
    स्थिर input_प्रणाली_ID_t	ID,
    input_प्रणाली_state_t *state);
/*! Dump the state of INPUT_SYSTEM[ID]
 \param ID[in]		INPUT_SYSTEM identअगरier
 \param state[in]	poपूर्णांकer to input प्रणाली state काष्ठाure
 \लeturn none
 \depends on host supplied prपूर्णांक function as part of ia_css_init()
 */
STORAGE_CLASS_INPUT_SYSTEM_H व्योम input_प्रणाली_dump_state(
    स्थिर input_प्रणाली_ID_t	ID,
    input_प्रणाली_state_t *state);
#पूर्ण_अगर /* ISP2401 */
#पूर्ण_अगर /* __ISYS_PUBLIC_H_INCLUDED__ */
