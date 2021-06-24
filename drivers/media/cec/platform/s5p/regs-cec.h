<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* drivers/media/platक्रमm/s5p-cec/regs-cec.h
 *
 * Copyright (c) 2010 Samsung Electronics
 *		http://www.samsung.com/
 *
 *  रेजिस्टर header file क्रम Samsung TVOUT driver
 */

#अगर_अघोषित __EXYNOS_REGS__H
#घोषणा __EXYNOS_REGS__H

/*
 * Register part
 */
#घोषणा S5P_CEC_STATUS_0			(0x0000)
#घोषणा S5P_CEC_STATUS_1			(0x0004)
#घोषणा S5P_CEC_STATUS_2			(0x0008)
#घोषणा S5P_CEC_STATUS_3			(0x000C)
#घोषणा S5P_CEC_IRQ_MASK			(0x0010)
#घोषणा S5P_CEC_IRQ_CLEAR			(0x0014)
#घोषणा S5P_CEC_LOGIC_ADDR			(0x0020)
#घोषणा S5P_CEC_DIVISOR_0			(0x0030)
#घोषणा S5P_CEC_DIVISOR_1			(0x0034)
#घोषणा S5P_CEC_DIVISOR_2			(0x0038)
#घोषणा S5P_CEC_DIVISOR_3			(0x003C)

#घोषणा S5P_CEC_TX_CTRL				(0x0040)
#घोषणा S5P_CEC_TX_BYTES			(0x0044)
#घोषणा S5P_CEC_TX_STAT0			(0x0060)
#घोषणा S5P_CEC_TX_STAT1			(0x0064)
#घोषणा S5P_CEC_TX_BUFF0			(0x0080)
#घोषणा S5P_CEC_TX_BUFF1			(0x0084)
#घोषणा S5P_CEC_TX_BUFF2			(0x0088)
#घोषणा S5P_CEC_TX_BUFF3			(0x008C)
#घोषणा S5P_CEC_TX_BUFF4			(0x0090)
#घोषणा S5P_CEC_TX_BUFF5			(0x0094)
#घोषणा S5P_CEC_TX_BUFF6			(0x0098)
#घोषणा S5P_CEC_TX_BUFF7			(0x009C)
#घोषणा S5P_CEC_TX_BUFF8			(0x00A0)
#घोषणा S5P_CEC_TX_BUFF9			(0x00A4)
#घोषणा S5P_CEC_TX_BUFF10			(0x00A8)
#घोषणा S5P_CEC_TX_BUFF11			(0x00AC)
#घोषणा S5P_CEC_TX_BUFF12			(0x00B0)
#घोषणा S5P_CEC_TX_BUFF13			(0x00B4)
#घोषणा S5P_CEC_TX_BUFF14			(0x00B8)
#घोषणा S5P_CEC_TX_BUFF15			(0x00BC)

#घोषणा S5P_CEC_RX_CTRL				(0x00C0)
#घोषणा S5P_CEC_RX_STAT0			(0x00E0)
#घोषणा S5P_CEC_RX_STAT1			(0x00E4)
#घोषणा S5P_CEC_RX_BUFF0			(0x0100)
#घोषणा S5P_CEC_RX_BUFF1			(0x0104)
#घोषणा S5P_CEC_RX_BUFF2			(0x0108)
#घोषणा S5P_CEC_RX_BUFF3			(0x010C)
#घोषणा S5P_CEC_RX_BUFF4			(0x0110)
#घोषणा S5P_CEC_RX_BUFF5			(0x0114)
#घोषणा S5P_CEC_RX_BUFF6			(0x0118)
#घोषणा S5P_CEC_RX_BUFF7			(0x011C)
#घोषणा S5P_CEC_RX_BUFF8			(0x0120)
#घोषणा S5P_CEC_RX_BUFF9			(0x0124)
#घोषणा S5P_CEC_RX_BUFF10			(0x0128)
#घोषणा S5P_CEC_RX_BUFF11			(0x012C)
#घोषणा S5P_CEC_RX_BUFF12			(0x0130)
#घोषणा S5P_CEC_RX_BUFF13			(0x0134)
#घोषणा S5P_CEC_RX_BUFF14			(0x0138)
#घोषणा S5P_CEC_RX_BUFF15			(0x013C)

#घोषणा S5P_CEC_RX_FILTER_CTRL			(0x0180)
#घोषणा S5P_CEC_RX_FILTER_TH			(0x0184)

/*
 * Bit definition part
 */
#घोषणा S5P_CEC_IRQ_TX_DONE			(1<<0)
#घोषणा S5P_CEC_IRQ_TX_ERROR			(1<<1)
#घोषणा S5P_CEC_IRQ_RX_DONE			(1<<4)
#घोषणा S5P_CEC_IRQ_RX_ERROR			(1<<5)

#घोषणा S5P_CEC_TX_CTRL_START			(1<<0)
#घोषणा S5P_CEC_TX_CTRL_BCAST			(1<<1)
#घोषणा S5P_CEC_TX_CTRL_RETRY			(0x04<<4)
#घोषणा S5P_CEC_TX_CTRL_RESET			(1<<7)

#घोषणा S5P_CEC_RX_CTRL_ENABLE			(1<<0)
#घोषणा S5P_CEC_RX_CTRL_RESET			(1<<7)

#घोषणा S5P_CEC_LOGIC_ADDR_MASK			(0xF)

/* PMU Registers क्रम PHY */
#घोषणा EXYNOS_HDMI_PHY_CONTROL			0x700

#पूर्ण_अगर	/* __EXYNOS_REGS__H	*/
