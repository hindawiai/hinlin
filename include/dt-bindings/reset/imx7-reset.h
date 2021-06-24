<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2017 Impinj, Inc.
 *
 * Author: Andrey Smirnov <andrew.smirnov@gmail.com>
 */

#अगर_अघोषित DT_BINDING_RESET_IMX7_H
#घोषणा DT_BINDING_RESET_IMX7_H

#घोषणा IMX7_RESET_A7_CORE_POR_RESET0	0
#घोषणा IMX7_RESET_A7_CORE_POR_RESET1	1
#घोषणा IMX7_RESET_A7_CORE_RESET0	2
#घोषणा IMX7_RESET_A7_CORE_RESET1	3
#घोषणा IMX7_RESET_A7_DBG_RESET0	4
#घोषणा IMX7_RESET_A7_DBG_RESET1	5
#घोषणा IMX7_RESET_A7_ETM_RESET0	6
#घोषणा IMX7_RESET_A7_ETM_RESET1	7
#घोषणा IMX7_RESET_A7_SOC_DBG_RESET	8
#घोषणा IMX7_RESET_A7_L2RESET		9
#घोषणा IMX7_RESET_SW_M4C_RST		10
#घोषणा IMX7_RESET_SW_M4P_RST		11
#घोषणा IMX7_RESET_EIM_RST		12
#घोषणा IMX7_RESET_HSICPHY_PORT_RST	13
#घोषणा IMX7_RESET_USBPHY1_POR		14
#घोषणा IMX7_RESET_USBPHY1_PORT_RST	15
#घोषणा IMX7_RESET_USBPHY2_POR		16
#घोषणा IMX7_RESET_USBPHY2_PORT_RST	17
#घोषणा IMX7_RESET_MIPI_PHY_MRST	18
#घोषणा IMX7_RESET_MIPI_PHY_SRST	19

/*
 * IMX7_RESET_PCIEPHY is a logical reset line combining PCIEPHY_BTN
 * and PCIEPHY_G_RST
 */
#घोषणा IMX7_RESET_PCIEPHY		20
#घोषणा IMX7_RESET_PCIEPHY_PERST	21

/*
 * IMX7_RESET_PCIE_CTRL_APPS_EN is not strictly a reset line, but it
 * can be used to inhibit PCIe LTTSM, so, in a way, it can be thoguht
 * of as one
 */
#घोषणा IMX7_RESET_PCIE_CTRL_APPS_EN	22
#घोषणा IMX7_RESET_DDRC_PRST		23
#घोषणा IMX7_RESET_DDRC_CORE_RST	24

#घोषणा IMX7_RESET_PCIE_CTRL_APPS_TURNOFF 25

#घोषणा IMX7_RESET_NUM			26

#पूर्ण_अगर

