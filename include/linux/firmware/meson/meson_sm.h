<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2016 Endless Mobile, Inc.
 * Author: Carlo Caione <carlo@endlessm.com>
 */

#अगर_अघोषित _MESON_SM_FW_H_
#घोषणा _MESON_SM_FW_H_

क्रमागत अणु
	SM_EFUSE_READ,
	SM_EFUSE_WRITE,
	SM_EFUSE_USER_MAX,
	SM_GET_CHIP_ID,
	SM_A1_PWRC_SET,
	SM_A1_PWRC_GET,
पूर्ण;

काष्ठा meson_sm_firmware;

पूर्णांक meson_sm_call(काष्ठा meson_sm_firmware *fw, अचिन्हित पूर्णांक cmd_index,
		  u32 *ret, u32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4);
पूर्णांक meson_sm_call_ग_लिखो(काष्ठा meson_sm_firmware *fw, व्योम *buffer,
			अचिन्हित पूर्णांक b_size, अचिन्हित पूर्णांक cmd_index, u32 arg0,
			u32 arg1, u32 arg2, u32 arg3, u32 arg4);
पूर्णांक meson_sm_call_पढ़ो(काष्ठा meson_sm_firmware *fw, व्योम *buffer,
		       अचिन्हित पूर्णांक bsize, अचिन्हित पूर्णांक cmd_index, u32 arg0,
		       u32 arg1, u32 arg2, u32 arg3, u32 arg4);
काष्ठा meson_sm_firmware *meson_sm_get(काष्ठा device_node *firmware_node);

#पूर्ण_अगर /* _MESON_SM_FW_H_ */
