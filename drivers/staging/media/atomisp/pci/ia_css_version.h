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

#अगर_अघोषित __IA_CSS_VERSION_H
#घोषणा __IA_CSS_VERSION_H

/* @file
 * This file contains functions to retrieve CSS-API version inक्रमmation
 */

#समावेश <ia_css_err.h>

/* a common size क्रम the version arrays */
#घोषणा MAX_VERSION_SIZE	500

/* @brief Retrieves the current CSS version
 * @param[out]	version		A poपूर्णांकer to a buffer where to put the generated
 *				version string. शून्य is ignored.
 * @param[in]	max_size	Size of the version buffer. If version string
 *				would be larger than max_size, an error is
 *				वापसed by this function.
 *
 * This function generates and वापसs the version string. If FW is loaded, it
 * attaches the FW version.
 */
पूर्णांक
ia_css_get_version(अक्षर *version, पूर्णांक max_size);

#पूर्ण_अगर /* __IA_CSS_VERSION_H */
