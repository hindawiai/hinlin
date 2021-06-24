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

#अगर_अघोषित __ISYS_STREAM2MMIO_PUBLIC_H_INCLUDED__
#घोषणा __ISYS_STREAM2MMIO_PUBLIC_H_INCLUDED__

/*****************************************************
 *
 * Native command पूर्णांकerface (NCI).
 *
 *****************************************************/
/**
 * @brief Get the stream2mmio-controller state.
 * Get the state of the stream2mmio-controller regiester-set.
 *
 * @param[in]	id		The global unique ID of the steeam2mmio controller.
 * @param[out]	state	Poपूर्णांक to the रेजिस्टर-state.
 */
STORAGE_CLASS_STREAM2MMIO_H व्योम stream2mmio_get_state(
    स्थिर stream2mmio_ID_t ID,
    stream2mmio_state_t *state);

/**
 * @brief Get the state of the stream2mmio-controller sidess.
 * Get the state of the रेजिस्टर set per buf-controller sidess.
 *
 * @param[in]	id		The global unique ID of the steeam2mmio controller.
 * @param[in]	sid_id		The sid ID.
 * @param[out]	state		Poपूर्णांक to the sid state.
 */
STORAGE_CLASS_STREAM2MMIO_H व्योम stream2mmio_get_sid_state(
    स्थिर stream2mmio_ID_t ID,
    स्थिर stream2mmio_sid_ID_t sid_id,
    stream2mmio_sid_state_t *state);
/* end of NCI */

/*****************************************************
 *
 * Device level पूर्णांकerface (DLI).
 *
 *****************************************************/
/**
 * @brief Load the रेजिस्टर value.
 * Load the value of the रेजिस्टर of the stream2mmio-controller.
 *
 * @param[in]	ID	The global unique ID क्रम the stream2mmio-controller instance.
 * @param[in]	sid_id	The SID in question.
 * @param[in]	reg_idx	The offset address of the रेजिस्टर.
 *
 * @वापस the value of the रेजिस्टर.
 */
STORAGE_CLASS_STREAM2MMIO_H hrt_data stream2mmio_reg_load(
    स्थिर stream2mmio_ID_t ID,
    स्थिर stream2mmio_sid_ID_t sid_id,
    स्थिर uपूर्णांक32_t reg_idx);

/**
 * @brief Dump the SID processor state.
 * Dump the state of the sid regiester-set.
 *
 * @param[in]	state		Poपूर्णांकer to the रेजिस्टर-state.
 */
STORAGE_CLASS_STREAM2MMIO_H व्योम stream2mmio_prपूर्णांक_sid_state(
    stream2mmio_sid_state_t	*state);
/**
 * @brief Dump the stream2mmio state.
 * Dump the state of the ibuf-controller regiester-set.
 *
 * @param[in]	id		The global unique ID of the st2mmio
 * @param[in]	state		Poपूर्णांकer to the रेजिस्टर-state.
 */
STORAGE_CLASS_STREAM2MMIO_H व्योम stream2mmio_dump_state(
    स्थिर stream2mmio_ID_t ID,
    stream2mmio_state_t *state);
/**
 * @brief Store a value to the रेजिस्टर.
 * Store a value to the registe of the stream2mmio-controller.
 *
 * @param[in]	ID		The global unique ID क्रम the stream2mmio-controller instance.
 * @param[in]	reg		The offset address of the रेजिस्टर.
 * @param[in]	value	The value to be stored.
 *
 */
STORAGE_CLASS_STREAM2MMIO_H व्योम stream2mmio_reg_store(
    स्थिर stream2mmio_ID_t ID,
    स्थिर hrt_address reg,
    स्थिर hrt_data value);
/* end of DLI */

#पूर्ण_अगर /* __ISYS_STREAM2MMIO_PUBLIC_H_INCLUDED__ */
