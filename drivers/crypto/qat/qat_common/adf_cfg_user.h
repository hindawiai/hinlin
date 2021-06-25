<शैली गुरु>
/* SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only) */
/* Copyright(c) 2014 - 2020 Intel Corporation */
#अगर_अघोषित ADF_CFG_USER_H_
#घोषणा ADF_CFG_USER_H_

#समावेश "adf_cfg_common.h"
#समावेश "adf_cfg_strings.h"

काष्ठा adf_user_cfg_key_val अणु
	अक्षर key[ADF_CFG_MAX_KEY_LEN_IN_BYTES];
	अक्षर val[ADF_CFG_MAX_VAL_LEN_IN_BYTES];
	जोड़ अणु
		काष्ठा adf_user_cfg_key_val *next;
		__u64 padding3;
	पूर्ण;
	क्रमागत adf_cfg_val_type type;
पूर्ण __packed;

काष्ठा adf_user_cfg_section अणु
	अक्षर name[ADF_CFG_MAX_SECTION_LEN_IN_BYTES];
	जोड़ अणु
		काष्ठा adf_user_cfg_key_val *params;
		__u64 padding1;
	पूर्ण;
	जोड़ अणु
		काष्ठा adf_user_cfg_section *next;
		__u64 padding3;
	पूर्ण;
पूर्ण __packed;

काष्ठा adf_user_cfg_ctl_data अणु
	जोड़ अणु
		काष्ठा adf_user_cfg_section *config_section;
		__u64 padding;
	पूर्ण;
	__u8 device_id;
पूर्ण __packed;
#पूर्ण_अगर
