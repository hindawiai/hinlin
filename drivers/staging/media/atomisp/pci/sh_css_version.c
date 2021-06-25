<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
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

#समावेश "../../include/linux/atomisp.h"
#समावेश "../../include/linux/atomisp_platform.h"
#समावेश "ia_css_version.h"
#समावेश "ia_css_version_data.h"
#समावेश "ia_css_err.h"
#समावेश "sh_css_firmware.h"

पूर्णांक
ia_css_get_version(अक्षर *version, पूर्णांक max_size) अणु
	अक्षर *css_version;

	अगर (!IS_ISP2401)
		css_version = ISP2400_CSS_VERSION_STRING;
	अन्यथा
		css_version = ISP2401_CSS_VERSION_STRING;

	अगर (max_size <= (पूर्णांक)म_माप(css_version) + (पूर्णांक)म_माप(sh_css_get_fw_version()) + 5)
		वापस -EINVAL;
	strscpy(version, css_version, max_size);
	म_जोड़ो(version, "FW:");
	म_जोड़ो(version, sh_css_get_fw_version());
	म_जोड़ो(version, "; ");
	वापस 0;
पूर्ण
