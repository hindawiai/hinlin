<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR MIT) */
/*
 * Driver क्रम Microsemi VSC85xx PHYs
 *
 * Copyright (c) 2021 Microsemi Corporation
 */

#अगर_अघोषित _MSCC_SERDES_PHY_H_
#घोषणा _MSCC_SERDES_PHY_H_

#घोषणा PHY_S6G_PLL5G_CFG2_GAIN_MASK      GENMASK(9, 5)
#घोषणा PHY_S6G_PLL5G_CFG2_ENA_GAIN       1

#घोषणा PHY_S6G_DES_PHY_CTRL_POS	  13
#घोषणा PHY_S6G_DES_MBTR_CTRL_POS	  10
#घोषणा PHY_S6G_DES_CPMD_SEL_POS	  8
#घोषणा PHY_S6G_DES_BW_HYST_POS		  5
#घोषणा PHY_S6G_DES_BW_ANA_POS		  1
#घोषणा PHY_S6G_DES_CFG			  0x21
#घोषणा PHY_S6G_IB_CFG0			  0x22
#घोषणा PHY_S6G_IB_CFG1			  0x23
#घोषणा PHY_S6G_IB_CFG2			  0x24
#घोषणा PHY_S6G_IB_CFG3			  0x25
#घोषणा PHY_S6G_IB_CFG4			  0x26
#घोषणा PHY_S6G_GP_CFG			  0x2E
#घोषणा PHY_S6G_DFT_CFG0		  0x35
#घोषणा PHY_S6G_IB_DFT_CFG2		  0x37

पूर्णांक vsc85xx_sd6g_config_v2(काष्ठा phy_device *phydev);

#पूर्ण_अगर /* _MSCC_PHY_SERDES_H_ */
