<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#अगर_अघोषित _E1000E_80003ES2LAN_H_
#घोषणा _E1000E_80003ES2LAN_H_

#घोषणा E1000_KMRNCTRLSTA_OFFSET_FIFO_CTRL	0x00
#घोषणा E1000_KMRNCTRLSTA_OFFSET_INB_CTRL	0x02
#घोषणा E1000_KMRNCTRLSTA_OFFSET_HD_CTRL	0x10
#घोषणा E1000_KMRNCTRLSTA_OFFSET_MAC2PHY_OPMODE	0x1F

#घोषणा E1000_KMRNCTRLSTA_FIFO_CTRL_RX_BYPASS	0x0008
#घोषणा E1000_KMRNCTRLSTA_FIFO_CTRL_TX_BYPASS	0x0800
#घोषणा E1000_KMRNCTRLSTA_INB_CTRL_DIS_PADDING	0x0010

#घोषणा E1000_KMRNCTRLSTA_HD_CTRL_10_100_DEFAULT 0x0004
#घोषणा E1000_KMRNCTRLSTA_HD_CTRL_1000_DEFAULT	0x0000
#घोषणा E1000_KMRNCTRLSTA_OPMODE_E_IDLE		0x2000

#घोषणा E1000_KMRNCTRLSTA_OPMODE_MASK		0x000C
#घोषणा E1000_KMRNCTRLSTA_OPMODE_INBAND_MDIO	0x0004

#घोषणा E1000_TCTL_EXT_GCEX_MASK 0x000FFC00	/* Gig Carry Extend Padding */
#घोषणा DEFAULT_TCTL_EXT_GCEX_80003ES2LAN	0x00010000

#घोषणा DEFAULT_TIPG_IPGT_1000_80003ES2LAN	0x8
#घोषणा DEFAULT_TIPG_IPGT_10_100_80003ES2LAN	0x9

/* GG82563 PHY Specअगरic Status Register (Page 0, Register 16 */
#घोषणा GG82563_PSCR_POLARITY_REVERSAL_DISABLE	0x0002	/* 1=Reversal Dis */
#घोषणा GG82563_PSCR_CROSSOVER_MODE_MASK	0x0060
#घोषणा GG82563_PSCR_CROSSOVER_MODE_MDI		0x0000	/* 00=Manual MDI */
#घोषणा GG82563_PSCR_CROSSOVER_MODE_MDIX	0x0020	/* 01=Manual MDIX */
#घोषणा GG82563_PSCR_CROSSOVER_MODE_AUTO	0x0060	/* 11=Auto crossover */

/* PHY Specअगरic Control Register 2 (Page 0, Register 26) */
#घोषणा GG82563_PSCR2_REVERSE_AUTO_NEG		0x2000	/* 1=Reverse Auto-Neg */

/* MAC Specअगरic Control Register (Page 2, Register 21) */
/* Tx घड़ी speed क्रम Link Down and 1000BASE-T क्रम the following speeds */
#घोषणा GG82563_MSCR_TX_CLK_MASK		0x0007
#घोषणा GG82563_MSCR_TX_CLK_10MBPS_2_5		0x0004
#घोषणा GG82563_MSCR_TX_CLK_100MBPS_25		0x0005
#घोषणा GG82563_MSCR_TX_CLK_1000MBPS_25		0x0007

#घोषणा GG82563_MSCR_ASSERT_CRS_ON_TX		0x0010	/* 1=Assert */

/* DSP Distance Register (Page 5, Register 26)
 * 0 = <50M
 * 1 = 50-80M
 * 2 = 80-100M
 * 3 = 110-140M
 * 4 = >140M
 */
#घोषणा GG82563_DSPD_CABLE_LENGTH		0x0007

/* Kumeran Mode Control Register (Page 193, Register 16) */
#घोषणा GG82563_KMCR_PASS_FALSE_CARRIER		0x0800

/* Max number of बार Kumeran पढ़ो/ग_लिखो should be validated */
#घोषणा GG82563_MAX_KMRN_RETRY			0x5

/* Power Management Control Register (Page 193, Register 20) */
/* 1=Enable SERDES Electrical Idle */
#घोषणा GG82563_PMCR_ENABLE_ELECTRICAL_IDLE	0x0001

/* In-Band Control Register (Page 194, Register 18) */
#घोषणा GG82563_ICR_DIS_PADDING			0x0010	/* Disable Padding */

#पूर्ण_अगर
