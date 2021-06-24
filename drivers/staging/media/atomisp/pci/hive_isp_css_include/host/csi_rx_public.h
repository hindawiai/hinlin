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

#अगर_अघोषित __CSI_RX_PUBLIC_H_INCLUDED__
#घोषणा __CSI_RX_PUBLIC_H_INCLUDED__

#अगर_घोषित ISP2401
/*****************************************************
 *
 * Native command पूर्णांकerface (NCI).
 *
 *****************************************************/
/**
 * @brief Get the csi rx frontend state.
 * Get the state of the csi rx frontend regiester-set.
 *
 * @param[in]	id	The global unique ID of the csi rx fe controller.
 * @param[out]	state	Poपूर्णांक to the रेजिस्टर-state.
 */
व्योम csi_rx_fe_ctrl_get_state(
    स्थिर csi_rx_frontend_ID_t ID,
    csi_rx_fe_ctrl_state_t *state);
/**
 * @brief Dump the csi rx frontend state.
 * Dump the state of the csi rx frontend regiester-set.
 *
 * @param[in]	id	The global unique ID of the csi rx fe controller.
 * @param[in]	state	Poपूर्णांक to the रेजिस्टर-state.
 */
व्योम csi_rx_fe_ctrl_dump_state(
    स्थिर csi_rx_frontend_ID_t ID,
    csi_rx_fe_ctrl_state_t *state);
/**
 * @brief Get the state of the csi rx fe dlane.
 * Get the state of the रेजिस्टर set per dlane process.
 *
 * @param[in]	id			The global unique ID of the input-buffer controller.
 * @param[in]	lane		The lane ID.
 * @param[out]	state		Poपूर्णांक to the dlane state.
 */
व्योम csi_rx_fe_ctrl_get_dlane_state(
    स्थिर csi_rx_frontend_ID_t ID,
    स्थिर u32 lane,
    csi_rx_fe_ctrl_lane_t *dlane_state);
/**
 * @brief Get the csi rx backend state.
 * Get the state of the csi rx backend regiester-set.
 *
 * @param[in]	id	The global unique ID of the csi rx be controller.
 * @param[out]	state	Poपूर्णांक to the रेजिस्टर-state.
 */
व्योम csi_rx_be_ctrl_get_state(
    स्थिर csi_rx_backend_ID_t ID,
    csi_rx_be_ctrl_state_t *state);
/**
 * @brief Dump the csi rx backend state.
 * Dump the state of the csi rx backend regiester-set.
 *
 * @param[in]	id	The global unique ID of the csi rx be controller.
 * @param[in]	state	Poपूर्णांक to the रेजिस्टर-state.
 */
व्योम csi_rx_be_ctrl_dump_state(
    स्थिर csi_rx_backend_ID_t ID,
    csi_rx_be_ctrl_state_t *state);
/* end of NCI */

/*****************************************************
 *
 * Device level पूर्णांकerface (DLI).
 *
 *****************************************************/
/**
 * @brief Load the रेजिस्टर value.
 * Load the value of the रेजिस्टर of the csi rx fe.
 *
 * @param[in]	ID	The global unique ID क्रम the ibuf-controller instance.
 * @param[in]	reg	The offset address of the रेजिस्टर.
 *
 * @वापस the value of the रेजिस्टर.
 */
hrt_data csi_rx_fe_ctrl_reg_load(
    स्थिर csi_rx_frontend_ID_t ID,
    स्थिर hrt_address reg);
/**
 * @brief Store a value to the रेजिस्टर.
 * Store a value to the registe of the csi rx fe.
 *
 * @param[in]	ID		The global unique ID क्रम the ibuf-controller instance.
 * @param[in]	reg		The offset address of the रेजिस्टर.
 * @param[in]	value	The value to be stored.
 *
 */
व्योम csi_rx_fe_ctrl_reg_store(
    स्थिर csi_rx_frontend_ID_t ID,
    स्थिर hrt_address reg,
    स्थिर hrt_data value);
/**
 * @brief Load the रेजिस्टर value.
 * Load the value of the रेजिस्टर of the csirx be.
 *
 * @param[in]	ID	The global unique ID क्रम the ibuf-controller instance.
 * @param[in]	reg	The offset address of the रेजिस्टर.
 *
 * @वापस the value of the रेजिस्टर.
 */
hrt_data csi_rx_be_ctrl_reg_load(
    स्थिर csi_rx_backend_ID_t ID,
    स्थिर hrt_address reg);
/**
 * @brief Store a value to the रेजिस्टर.
 * Store a value to the registe of the csi rx be.
 *
 * @param[in]	ID		The global unique ID क्रम the ibuf-controller instance.
 * @param[in]	reg		The offset address of the रेजिस्टर.
 * @param[in]	value	The value to be stored.
 *
 */
व्योम csi_rx_be_ctrl_reg_store(
    स्थिर csi_rx_backend_ID_t ID,
    स्थिर hrt_address reg,
    स्थिर hrt_data value);
/* end of DLI */
#पूर्ण_अगर /* ISP2401 */
#पूर्ण_अगर /* __CSI_RX_PUBLIC_H_INCLUDED__ */
