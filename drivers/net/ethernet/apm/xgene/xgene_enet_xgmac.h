<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Applied Micro X-Gene SoC Ethernet Driver
 *
 * Copyright (c) 2014, Applied Micro Circuits Corporation
 * Authors: Iyappan Subramanian <isubramanian@apm.com>
 *	    Keyur Chudgar <kchudgar@apm.com>
 */

#अगर_अघोषित __XGENE_ENET_XGMAC_H__
#घोषणा __XGENE_ENET_XGMAC_H__

#घोषणा X2_BLOCK_ETH_MAC_CSR_OFFSET	0x3000
#घोषणा BLOCK_AXG_MAC_OFFSET		0x0800
#घोषणा BLOCK_AXG_STATS_OFFSET		0x0800
#घोषणा BLOCK_AXG_MAC_CSR_OFFSET	0x2000
#घोषणा BLOCK_PCS_OFFSET		0x3800

#घोषणा XGENET_CONFIG_REG_ADDR		0x20
#घोषणा XGENET_SRST_ADDR		0x00
#घोषणा XGENET_CLKEN_ADDR		0x08

#घोषणा CSR_CLK		BIT(0)
#घोषणा XGENET_CLK	BIT(1)
#घोषणा PCS_CLK		BIT(3)
#घोषणा AN_REF_CLK	BIT(4)
#घोषणा AN_CLK		BIT(5)
#घोषणा AD_CLK		BIT(6)

#घोषणा CSR_RST		BIT(0)
#घोषणा XGENET_RST	BIT(1)
#घोषणा PCS_RST		BIT(3)
#घोषणा AN_REF_RST	BIT(4)
#घोषणा AN_RST		BIT(5)
#घोषणा AD_RST		BIT(6)

#घोषणा AXGMAC_CONFIG_0			0x0000
#घोषणा AXGMAC_CONFIG_1			0x0004
#घोषणा HSTMACRST			BIT(31)
#घोषणा HSTTCTLEN			BIT(31)
#घोषणा HSTTFEN				BIT(30)
#घोषणा HSTRCTLEN			BIT(29)
#घोषणा HSTRFEN				BIT(28)
#घोषणा HSTPPEN				BIT(7)
#घोषणा HSTDRPLT64			BIT(5)
#घोषणा HSTLENCHK			BIT(3)
#घोषणा HSTMACADR_LSW_ADDR		0x0010
#घोषणा HSTMACADR_MSW_ADDR		0x0014
#घोषणा HSTMAXFRAME_LENGTH_ADDR		0x0020

#घोषणा XG_MCX_RX_DV_GATE_REG_0_ADDR	0x0004
#घोषणा XG_MCX_ECM_CFG_0_ADDR		0x0074
#घोषणा XG_MCX_MULTI_DPF0_ADDR		0x007c
#घोषणा XG_MCX_MULTI_DPF1_ADDR		0x0080
#घोषणा XG_DEF_PAUSE_THRES		0x390
#घोषणा XG_DEF_PAUSE_OFF_THRES		0x2c0
#घोषणा XG_RSIF_CONFIG_REG_ADDR		0x00a0
#घोषणा XG_RSIF_CLE_BUFF_THRESH                0x3
#घोषणा RSIF_CLE_BUFF_THRESH_SET(dst, val)     xgene_set_bits(dst, val, 0, 3)
#घोषणा XG_RSIF_CONFIG1_REG_ADDR       0x00b8
#घोषणा XG_RSIF_PLC_CLE_BUFF_THRESH    0x1
#घोषणा RSIF_PLC_CLE_BUFF_THRESH_SET(dst, val) xgene_set_bits(dst, val, 0, 2)
#घोषणा XG_MCX_ECM_CONFIG0_REG_0_ADDR          0x0070
#घोषणा XG_MCX_ICM_ECM_DROP_COUNT_REG0_ADDR    0x0124
#घोषणा XCLE_BYPASS_REG0_ADDR           0x0160
#घोषणा XCLE_BYPASS_REG1_ADDR           0x0164
#घोषणा XG_CFG_BYPASS_ADDR		0x0204
#घोषणा XG_CFG_LINK_AGGR_RESUME_0_ADDR	0x0214
#घोषणा XG_LINK_STATUS_ADDR		0x0228
#घोषणा XG_TSIF_MSS_REG0_ADDR		0x02a4
#घोषणा XG_DEBUG_REG_ADDR		0x0400
#घोषणा XG_ENET_SPARE_CFG_REG_ADDR	0x040c
#घोषणा XG_ENET_SPARE_CFG_REG_1_ADDR	0x0410
#घोषणा XGENET_RX_DV_GATE_REG_0_ADDR	0x0804
#घोषणा XGENET_ECM_CONFIG0_REG_0	0x0870
#घोषणा XGENET_ICM_ECM_DROP_COUNT_REG0	0x0924
#घोषणा XGENET_CSR_ECM_CFG_0_ADDR	0x0880
#घोषणा XGENET_CSR_MULTI_DPF0_ADDR	0x0888
#घोषणा XGENET_CSR_MULTI_DPF1_ADDR	0x088c
#घोषणा XG_RXBUF_PAUSE_THRESH		0x0020
#घोषणा XG_MCX_ICM_CONFIG0_REG_0_ADDR	0x00e0
#घोषणा XG_MCX_ICM_CONFIG2_REG_0_ADDR	0x00e8

#घोषणा PCS_CONTROL_1			0x0000
#घोषणा PCS_CTRL_PCS_RST		BIT(15)

बाह्य स्थिर काष्ठा xgene_mac_ops xgene_xgmac_ops;
बाह्य स्थिर काष्ठा xgene_port_ops xgene_xgport_ops;

#पूर्ण_अगर /* __XGENE_ENET_XGMAC_H__ */
