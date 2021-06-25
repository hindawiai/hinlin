<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2016 Freescale Semiconductor, Inc.
 * Copyright 2017~2018 NXP
 *
 * Header file containing the खुला API क्रम the System Controller (SC)
 * Miscellaneous (MISC) function.
 *
 * MISC_SVC (SVC) Miscellaneous Service
 *
 * Module क्रम the Miscellaneous (MISC) service.
 */

#अगर_अघोषित _SC_MISC_API_H
#घोषणा _SC_MISC_API_H

#समावेश <linux/firmware/imx/sci.h>

/*
 * This type is used to indicate RPC MISC function calls.
 */
क्रमागत imx_misc_func अणु
	IMX_SC_MISC_FUNC_UNKNOWN = 0,
	IMX_SC_MISC_FUNC_SET_CONTROL = 1,
	IMX_SC_MISC_FUNC_GET_CONTROL = 2,
	IMX_SC_MISC_FUNC_SET_MAX_DMA_GROUP = 4,
	IMX_SC_MISC_FUNC_SET_DMA_GROUP = 5,
	IMX_SC_MISC_FUNC_SECO_IMAGE_LOAD = 8,
	IMX_SC_MISC_FUNC_SECO_AUTHENTICATE = 9,
	IMX_SC_MISC_FUNC_DEBUG_OUT = 10,
	IMX_SC_MISC_FUNC_WAVEFORM_CAPTURE = 6,
	IMX_SC_MISC_FUNC_BUILD_INFO = 15,
	IMX_SC_MISC_FUNC_UNIQUE_ID = 19,
	IMX_SC_MISC_FUNC_SET_ARI = 3,
	IMX_SC_MISC_FUNC_BOOT_STATUS = 7,
	IMX_SC_MISC_FUNC_BOOT_DONE = 14,
	IMX_SC_MISC_FUNC_OTP_FUSE_READ = 11,
	IMX_SC_MISC_FUNC_OTP_FUSE_WRITE = 17,
	IMX_SC_MISC_FUNC_SET_TEMP = 12,
	IMX_SC_MISC_FUNC_GET_TEMP = 13,
	IMX_SC_MISC_FUNC_GET_BOOT_DEV = 16,
	IMX_SC_MISC_FUNC_GET_BUTTON_STATUS = 18,
पूर्ण;

/*
 * Control Functions
 */

#अगर_घोषित CONFIG_IMX_SCU
पूर्णांक imx_sc_misc_set_control(काष्ठा imx_sc_ipc *ipc, u32 resource,
			    u8 ctrl, u32 val);

पूर्णांक imx_sc_misc_get_control(काष्ठा imx_sc_ipc *ipc, u32 resource,
			    u8 ctrl, u32 *val);

पूर्णांक imx_sc_pm_cpu_start(काष्ठा imx_sc_ipc *ipc, u32 resource,
			bool enable, u64 phys_addr);
#अन्यथा
अटल अंतरभूत पूर्णांक imx_sc_misc_set_control(काष्ठा imx_sc_ipc *ipc,
					  u32 resource, u8 ctrl, u32 val)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक imx_sc_misc_get_control(काष्ठा imx_sc_ipc *ipc,
					  u32 resource, u8 ctrl, u32 *val)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक imx_sc_pm_cpu_start(काष्ठा imx_sc_ipc *ipc, u32 resource,
				      bool enable, u64 phys_addr)
अणु
	वापस -ENOTSUPP;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* _SC_MISC_API_H */
