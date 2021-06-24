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

#अगर_अघोषित __PIXELGEN_PUBLIC_H_INCLUDED__
#घोषणा __PIXELGEN_PUBLIC_H_INCLUDED__

#अगर_घोषित ISP2401
/*****************************************************
 *
 * Native command पूर्णांकerface (NCI).
 *
 *****************************************************/
/**
 * @brief Get the pixelgen state.
 * Get the state of the pixelgen regiester-set.
 *
 * @param[in]	id	The global unique ID of the pixelgen controller.
 * @param[out]	state	Poपूर्णांक to the रेजिस्टर-state.
 */
STORAGE_CLASS_PIXELGEN_H व्योम pixelgen_ctrl_get_state(
    स्थिर pixelgen_ID_t ID,
    pixelgen_ctrl_state_t *state);
/**
 * @brief Dump the pixelgen state.
 * Dump the state of the pixelgen regiester-set.
 *
 * @param[in]	id	The global unique ID of the pixelgen controller.
 * @param[in]	state	Poपूर्णांक to the रेजिस्टर-state.
 */
STORAGE_CLASS_PIXELGEN_H व्योम pixelgen_ctrl_dump_state(
    स्थिर pixelgen_ID_t ID,
    pixelgen_ctrl_state_t *state);
/* end of NCI */

/*****************************************************
 *
 * Device level पूर्णांकerface (DLI).
 *
 *****************************************************/
/**
 * @brief Load the रेजिस्टर value.
 * Load the value of the रेजिस्टर of the pixelgen
 *
 * @param[in]	ID	The global unique ID क्रम the pixelgen instance.
 * @param[in]	reg	The offset address of the रेजिस्टर.
 *
 * @वापस the value of the रेजिस्टर.
 */
STORAGE_CLASS_PIXELGEN_H hrt_data pixelgen_ctrl_reg_load(
    स्थिर pixelgen_ID_t ID,
    स्थिर hrt_address reg);
/**
 * @brief Store a value to the रेजिस्टर.
 * Store a value to the registe of the pixelgen
 *
 * @param[in]	ID		The global unique ID क्रम the pixelgen.
 * @param[in]	reg		The offset address of the रेजिस्टर.
 * @param[in]	value	The value to be stored.
 *
 */
STORAGE_CLASS_PIXELGEN_H व्योम pixelgen_ctrl_reg_store(
    स्थिर pixelgen_ID_t ID,
    स्थिर hrt_address reg,
    स्थिर hrt_data value);
/* end of DLI */

#पूर्ण_अगर /* ISP2401 */
#पूर्ण_अगर /* __PIXELGEN_PUBLIC_H_INCLUDED__ */
