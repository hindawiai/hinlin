<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Applied Micro X-Gene SoC Ethernet Driver
 *
 * Copyright (c) 2014, Applied Micro Circuits Corporation
 * Authors: Iyappan Subramanian <isubramanian@apm.com>
 *	    Keyur Chudgar <kchudgar@apm.com>
 */

#अगर_अघोषित __XGENE_ENET_SGMAC_H__
#घोषणा __XGENE_ENET_SGMAC_H__

#घोषणा PHY_ADDR(src)		(((src)<<8) & GENMASK(12, 8))
#घोषणा REG_ADDR(src)		((src) & GENMASK(4, 0))
#घोषणा PHY_CONTROL(src)	((src) & GENMASK(15, 0))
#घोषणा LINK_SPEED(src)		(((src) & GENMASK(11, 10)) >> 10)
#घोषणा INT_PHY_ADDR			0x1e
#घोषणा SGMII_TBI_CONTROL_ADDR		0x44
#घोषणा SGMII_CONTROL_ADDR		0x00
#घोषणा SGMII_STATUS_ADDR		0x04
#घोषणा SGMII_BASE_PAGE_ABILITY_ADDR	0x14
#घोषणा AUTO_NEG_COMPLETE		BIT(5)
#घोषणा LINK_STATUS			BIT(2)
#घोषणा LINK_UP				BIT(15)
#घोषणा MPA_IDLE_WITH_QMI_EMPTY		BIT(12)
#घोषणा SG_RX_DV_GATE_REG_0_ADDR	0x05fc
#घोषणा SGMII_EN			0x1

क्रमागत xgene_phy_speed अणु
	PHY_SPEED_10,
	PHY_SPEED_100,
	PHY_SPEED_1000
पूर्ण;

बाह्य स्थिर काष्ठा xgene_mac_ops xgene_sgmac_ops;
बाह्य स्थिर काष्ठा xgene_port_ops xgene_sgport_ops;

#पूर्ण_अगर  /* __XGENE_ENET_SGMAC_H__ */
