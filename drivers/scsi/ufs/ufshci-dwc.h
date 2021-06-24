<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * UFS Host driver क्रम Synopsys Designware Core
 *
 * Copyright (C) 2015-2016 Synopsys, Inc. (www.synopsys.com)
 *
 * Authors: Joao Pपूर्णांकo <jpपूर्णांकo@synopsys.com>
 */

#अगर_अघोषित _UFSHCI_DWC_H
#घोषणा _UFSHCI_DWC_H

/* DWC HC UFSHCI specअगरic Registers */
क्रमागत dwc_specअगरic_रेजिस्टरs अणु
	DWC_UFS_REG_HCLKDIV	= 0xFC,
पूर्ण;

/* Clock Divider Values: Hex equivalent of frequency in MHz */
क्रमागत clk_भाग_values अणु
	DWC_UFS_REG_HCLKDIV_DIV_62_5	= 0x3e,
	DWC_UFS_REG_HCLKDIV_DIV_125	= 0x7d,
	DWC_UFS_REG_HCLKDIV_DIV_200	= 0xc8,
पूर्ण;

/* Selector Index */
क्रमागत selector_index अणु
	SELIND_LN0_TX		= 0x00,
	SELIND_LN1_TX		= 0x01,
	SELIND_LN0_RX		= 0x04,
	SELIND_LN1_RX		= 0x05,
पूर्ण;

#पूर्ण_अगर /* End of Header */
