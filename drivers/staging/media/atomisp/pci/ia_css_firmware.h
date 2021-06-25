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

#अगर_अघोषित __IA_CSS_FIRMWARE_H
#घोषणा __IA_CSS_FIRMWARE_H

/* @file
 * This file contains firmware loading/unloading support functionality
 */

#समावेश <linux/device.h>
#समावेश "ia_css_err.h"
#समावेश "ia_css_env.h"

/* CSS firmware package काष्ठाure.
 */
काष्ठा ia_css_fw अणु
	व्योम	    *data;  /** poपूर्णांकer to the firmware data */
	अचिन्हित पूर्णांक bytes; /** length in bytes of firmware data */
पूर्ण;

काष्ठा device;

/* @brief Loads the firmware
 * @param[in]	env		Environment, provides functions to access the
 *				environment in which the CSS code runs. This is
 *				used क्रम host side memory access and message
 *				prपूर्णांकing.
 * @param[in]	fw		Firmware package containing the firmware क्रम all
 *				predefined ISP binaries.
 * @वापस			Returns -EINVAL in हाल of any
 *				errors and 0 otherwise.
 *
 * This function पूर्णांकerprets the firmware package. All
 * contents of this firmware package are copied पूर्णांकo local data काष्ठाures, so
 * the fw poपूर्णांकer could be मुक्तd after this function completes.
 *
 * Rationale क्रम this function is that it can be called beक्रमe ia_css_init, and thus
 * speeds up ia_css_init (ia_css_init is called each समय a stream is created but the
 * firmware only needs to be loaded once).
 */
पूर्णांक
ia_css_load_firmware(काष्ठा device *dev, स्थिर काष्ठा ia_css_env *env,
		     स्थिर काष्ठा ia_css_fw  *fw);

/* @brief Unloads the firmware
 * @वापस	None
 *
 * This function unloads the firmware loaded by ia_css_load_firmware.
 * It is poपूर्णांकless to call this function अगर no firmware is loaded,
 * but it won't harm. Use this to deallocate all memory associated with the firmware.
 */
व्योम
ia_css_unload_firmware(व्योम);

#पूर्ण_अगर /* __IA_CSS_FIRMWARE_H */
