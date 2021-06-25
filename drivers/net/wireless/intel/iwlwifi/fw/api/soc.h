<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2012-2014, 2019-2020 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fw_api_soc_h__
#घोषणा __iwl_fw_api_soc_h__

#घोषणा SOC_CONFIG_CMD_FLAGS_DISCRETE		BIT(0)
#घोषणा SOC_CONFIG_CMD_FLAGS_LOW_LATENCY	BIT(1)

#घोषणा SOC_FLAGS_LTR_APPLY_DELAY_MASK		0xc
#घोषणा SOC_FLAGS_LTR_APPLY_DELAY_NONE		0
#घोषणा SOC_FLAGS_LTR_APPLY_DELAY_200		1
#घोषणा SOC_FLAGS_LTR_APPLY_DELAY_2500		2
#घोषणा SOC_FLAGS_LTR_APPLY_DELAY_1820		3

/**
 * काष्ठा iwl_soc_configuration_cmd - Set device stabilization latency
 *
 * @flags: soc settings flags.  In VER_1, we can only set the DISCRETE
 *	flag, because the FW treats the whole value as an पूर्णांकeger. In
 *	VER_2, we can set the bits independently.
 * @latency: समय क्रम SOC to ensure stable घातer & XTAL
 */
काष्ठा iwl_soc_configuration_cmd अणु
	__le32 flags;
	__le32 latency;
पूर्ण __packed; /*
	     * SOC_CONFIGURATION_CMD_S_VER_1 (see description above)
	     * SOC_CONFIGURATION_CMD_S_VER_2
	     */

#पूर्ण_अगर /* __iwl_fw_api_soc_h__ */
