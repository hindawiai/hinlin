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

#अगर_अघोषित _SH_CSS_FIRMWARE_H_
#घोषणा _SH_CSS_FIRMWARE_H_

#समावेश <प्रणाली_local.h>

#समावेश <ia_css_err.h>
#समावेश <ia_css_acc_types.h>

/* This is क्रम the firmware loaded from user space */
काष्ठा  sh_css_fw_bi_file_h अणु
	अक्षर version[64];		/* branch tag + week day + समय */
	पूर्णांक binary_nr;			/* Number of binaries */
	अचिन्हित पूर्णांक h_size;		/* माप(काष्ठा sh_css_fw_bi_file_h) */
पूर्ण;

बाह्य काष्ठा ia_css_fw_info     sh_css_sp_fw;
#अगर defined(HAS_BL)
बाह्य काष्ठा ia_css_fw_info     sh_css_bl_fw;
#पूर्ण_अगर /* HAS_BL */
बाह्य काष्ठा ia_css_blob_descr *sh_css_blob_info;
बाह्य अचिन्हित पूर्णांक sh_css_num_binaries;

अक्षर
*sh_css_get_fw_version(व्योम);

काष्ठा device;
bool
sh_css_check_firmware_version(काष्ठा device *dev, स्थिर अक्षर *fw_data);

पूर्णांक
sh_css_load_firmware(काष्ठा device *dev, स्थिर अक्षर *fw_data,
		     अचिन्हित पूर्णांक fw_size);

व्योम sh_css_unload_firmware(व्योम);

ia_css_ptr sh_css_load_blob(स्थिर अचिन्हित अक्षर *blob, अचिन्हित पूर्णांक size);

पूर्णांक
sh_css_load_blob_info(स्थिर अक्षर *fw, स्थिर काष्ठा ia_css_fw_info *bi,
		      काष्ठा ia_css_blob_descr *bd, अचिन्हित पूर्णांक i);

#पूर्ण_अगर /* _SH_CSS_FIRMWARE_H_ */
