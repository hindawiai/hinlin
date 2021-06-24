<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2019 MediaTek Inc.
 */
#अगर_अघोषित __MTK_SIP_SVC_H
#घोषणा __MTK_SIP_SVC_H

/* Error Code */
#घोषणा SIP_SVC_E_SUCCESS               0
#घोषणा SIP_SVC_E_NOT_SUPPORTED         -1
#घोषणा SIP_SVC_E_INVALID_PARAMS        -2
#घोषणा SIP_SVC_E_INVALID_RANGE         -3
#घोषणा SIP_SVC_E_PERMISSION_DENIED     -4

#अगर_घोषित CONFIG_ARM64
#घोषणा MTK_SIP_SMC_CONVENTION          ARM_SMCCC_SMC_64
#अन्यथा
#घोषणा MTK_SIP_SMC_CONVENTION          ARM_SMCCC_SMC_32
#पूर्ण_अगर

#घोषणा MTK_SIP_SMC_CMD(fn_id) \
	ARM_SMCCC_CALL_VAL(ARM_SMCCC_FAST_CALL, MTK_SIP_SMC_CONVENTION, \
			   ARM_SMCCC_OWNER_SIP, fn_id)

#पूर्ण_अगर
