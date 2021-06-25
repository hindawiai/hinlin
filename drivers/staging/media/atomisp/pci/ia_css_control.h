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

#अगर_अघोषित __IA_CSS_CONTROL_H
#घोषणा __IA_CSS_CONTROL_H

/* @file
 * This file contains functionality क्रम starting and controlling CSS
 */

#समावेश <type_support.h>
#समावेश <ia_css_env.h>
#समावेश <ia_css_firmware.h>
#समावेश <ia_css_irq.h>

/* @brief Initialize the CSS API.
 * @param[in]	env		Environment, provides functions to access the
 *				environment in which the CSS code runs. This is
 *				used क्रम host side memory access and message
 *				prपूर्णांकing. May not be शून्य.
 * @param[in]	fw		Firmware package containing the firmware क्रम all
 *				predefined ISP binaries.
 *				अगर fw is शून्य the firmware must be loaded beक्रमe
 *				through a call of ia_css_load_firmware
 * @param[in]	l1_base         Base index (isp2400)
 *                              of the L1 page table. This is a physical
 *                              address or index.
 * @param[in]	irq_type	The type of पूर्णांकerrupt to be used (edge or level)
 * @वापस				Returns -EINVAL in हाल of any
 *				errors and 0 otherwise.
 *
 * This function initializes the API which includes allocating and initializing
 * पूर्णांकernal data काष्ठाures. This also पूर्णांकerprets the firmware package. All
 * contents of this firmware package are copied पूर्णांकo local data काष्ठाures, so
 * the fw poपूर्णांकer could be मुक्तd after this function completes.
 */
पूर्णांक ia_css_init(काष्ठा device           *dev,
			    स्थिर काष्ठा ia_css_env *env,
			    स्थिर काष्ठा ia_css_fw  *fw,
			    u32                     l1_base,
			    क्रमागत ia_css_irq_type    irq_type);

/* @brief Un-initialize the CSS API.
 * @वापस	None
 *
 * This function deallocates all memory that has been allocated by the CSS API
 * Exception: अगर you explicitly loaded firmware through ia_css_load_firmware
 * you need to call ia_css_unload_firmware to deallocate the memory reserved
 * क्रम the firmware.
 * After this function is called, no other CSS functions should be called
 * with the exception of ia_css_init which will re-initialize the CSS code,
 * ia_css_unload_firmware to unload the firmware or ia_css_load_firmware
 * to load new firmware
 */
व्योम
ia_css_uninit(व्योम);

/* @brief Enable use of a separate queue क्रम ISYS events.
 *
 * @param[in]	enable: enable or disable use of separate ISYS event queues.
 * @वापस		error अगर called when SP is running.
 *
 * @deprecatedअणुThis is a temporary function that allows drivers to migrate to
 * the use of the separate ISYS event queue. Once all drivers supports this, it
 * will be made the शेष and this function will be हटाओd.
 * This function should only be called when the SP is not running, calling it
 * when the SP is running will result in an error value being वापसed. पूर्ण
 */
पूर्णांक
ia_css_enable_isys_event_queue(bool enable);

/* @brief Test whether the ISP has started.
 *
 * @वापस	Boolean flag true अगर the ISP has started or false otherwise.
 *
 * Temporary function to poll whether the ISP has been started. Once it has,
 * the sensor can also be started. */
bool
ia_css_isp_has_started(व्योम);

/* @brief Test whether the SP has initialized.
 *
 * @वापस	Boolean flag true अगर the SP has initialized or false otherwise.
 *
 * Temporary function to poll whether the SP has been initialized. Once it has,
 * we can enqueue buffers. */
bool
ia_css_sp_has_initialized(व्योम);

/* @brief Test whether the SP has terminated.
 *
 * @वापस	Boolean flag true अगर the SP has terminated or false otherwise.
 *
 * Temporary function to poll whether the SP has been terminated. Once it has,
 * we can चयन mode. */
bool
ia_css_sp_has_terminated(व्योम);

/* @brief start SP hardware
 *
 * @वापस			0 or error code upon error.
 *
 * It will boot the SP hardware and start multi-thपढ़ोing infraकाष्ठाure.
 * All thपढ़ोs will be started and blocked by semaphore. This function should
 * be called beक्रमe any ia_css_stream_start().
 */
पूर्णांक
ia_css_start_sp(व्योम);

/* @brief stop SP hardware
 *
 * @वापस			0 or error code upon error.
 *
 * This function will terminate all thपढ़ोs and shut करोwn SP. It should be
 * called after all ia_css_stream_stop().
 */
पूर्णांक
ia_css_stop_sp(व्योम);

#पूर्ण_अगर /* __IA_CSS_CONTROL_H */
