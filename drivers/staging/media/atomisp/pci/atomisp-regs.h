<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Medअगरield PNW Camera Imaging ISP subप्रणाली.
 *
 * Copyright (c) 2012 Intel Corporation. All Rights Reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 *
 */

#अगर_अघोषित ATOMISP_REGS_H
#घोषणा ATOMISP_REGS_H

/* common रेजिस्टर definitions */
#घोषणा PCICMDSTS		0x01
#घोषणा INTR			0x0f
#घोषणा MSI_CAPID		0x24
#घोषणा MSI_ADDRESS		0x25
#घोषणा MSI_DATA		0x26
#घोषणा INTR_CTL		0x27

#घोषणा PCI_MSI_CAPID		0x90
#घोषणा PCI_MSI_ADDR		0x94
#घोषणा PCI_MSI_DATA		0x98
#घोषणा PCI_INTERRUPT_CTRL	0x9C
#घोषणा PCI_I_CONTROL		0xfc

/* MRFLD specअगरic रेजिस्टर definitions */
#घोषणा MRFLD_CSI_AFE		0x39
#घोषणा MRFLD_CSI_CONTROL	0x3a
#घोषणा MRFLD_CSI_RCOMP		0x3d

#घोषणा MRFLD_PCI_PMCS		0x84
#घोषणा MRFLD_PCI_CSI_ACCESS_CTRL_VIOL	0xd4
#घोषणा MRFLD_PCI_CSI_AFE_HS_CONTROL	0xdc
#घोषणा MRFLD_PCI_CSI_AFE_RCOMP_CONTROL	0xe0
#घोषणा MRFLD_PCI_CSI_CONTROL		0xe8
#घोषणा MRFLD_PCI_CSI_AFE_TRIM_CONTROL	0xe4
#घोषणा MRFLD_PCI_CSI_DEADLINE_CONTROL	0xec
#घोषणा MRFLD_PCI_CSI_RCOMP_CONTROL	0xf4

/* Select Arasan (legacy)/Intel input प्रणाली */
#घोषणा MRFLD_PCI_CSI_CONTROL_PARPATHEN	BIT(24)
/* Enable CSI पूर्णांकerface (ANN B0/K0) */
#घोषणा MRFLD_PCI_CSI_CONTROL_CSI_READY	BIT(25)

/*
 * Enables the combining of adjacent 32-byte पढ़ो requests to the same
 * cache line. When cleared, each 32-byte पढ़ो request is sent as a
 * separate request on the IB पूर्णांकerface.
 */
#घोषणा MRFLD_PCI_I_CONTROL_ENABLE_READ_COMBINING	0x1

/*
 * Register: MRFLD_PCI_CSI_RCOMP_CONTROL
 * If cleared, the high speed घड़ी going to the digital logic is gated when
 * RCOMP update is happening. The घड़ी is gated क्रम a minimum of 100 nsec.
 * If this bit is set, then the high speed घड़ी is not gated during the
 * update cycle.
 */
#घोषणा MRFLD_PCI_CSI_HS_OVR_CLK_GATE_ON_UPDATE		0x800000

/*
 * Enables the combining of adjacent 32-byte ग_लिखो requests to the same
 * cache line. When cleared, each 32-byte ग_लिखो request is sent as a
 * separate request on the IB पूर्णांकerface.
 */
#घोषणा MRFLD_PCI_I_CONTROL_ENABLE_WRITE_COMBINING	0x2

#घोषणा MRFLD_PCI_I_CONTROL_SRSE_RESET_MASK		0xc

#घोषणा MRFLD_PCI_CSI1_HSRXCLKTRIM		0x2
#घोषणा MRFLD_PCI_CSI1_HSRXCLKTRIM_SHIFT	16
#घोषणा MRFLD_PCI_CSI2_HSRXCLKTRIM		0x3
#घोषणा MRFLD_PCI_CSI2_HSRXCLKTRIM_SHIFT	24
#घोषणा MRFLD_PCI_CSI3_HSRXCLKTRIM		0x2
#घोषणा MRFLD_PCI_CSI3_HSRXCLKTRIM_SHIFT	28
#घोषणा MRFLD_PCI_CSI_HSRXCLKTRIM_MASK		0xf

/*
 * This रेजिस्टर is IUINT MMIO रेजिस्टर, it is used to select the CSI
 * receiver backend.
 * 1: SH CSI backend
 * 0: Arasan CSI backend
 */
#घोषणा MRFLD_CSI_RECEIVER_SELECTION_REG       0x8081c

#घोषणा MRFLD_INTR_CLEAR_REG		       0x50c
#घोषणा MRFLD_INTR_STATUS_REG		       0x508
#घोषणा MRFLD_INTR_ENABLE_REG		       0x510

#घोषणा MRFLD_MAX_ZOOM_FACTOR	1024

/* MRFLD ISP POWER related */
#घोषणा MRFLD_ISPSSPM0         0x39
#घोषणा MRFLD_ISPSSPM0_ISPSSC_OFFSET   0
#घोषणा MRFLD_ISPSSPM0_ISPSSS_OFFSET   24
#घोषणा MRFLD_ISPSSPM0_ISPSSC_MASK     0x3
#घोषणा MRFLD_ISPSSPM0_IUNIT_POWER_ON  0
#घोषणा MRFLD_ISPSSPM0_IUNIT_POWER_OFF 0x3
#घोषणा MRFLD_ISPSSDVFS			0x13F
#घोषणा MRFLD_BIT0			0x0001
#घोषणा MRFLD_BIT1			0x0002

/* MRFLD CSI lane configuration related */
#घोषणा MRFLD_PORT_CONFIG_NUM  8
#घोषणा MRFLD_PORT_NUM         3
#घोषणा MRFLD_PORT1_ENABLE_SHIFT       0
#घोषणा MRFLD_PORT2_ENABLE_SHIFT       1
#घोषणा MRFLD_PORT3_ENABLE_SHIFT       2
#घोषणा MRFLD_PORT1_LANES_SHIFT        3
#घोषणा MRFLD_PORT2_LANES_SHIFT        7
#घोषणा MRFLD_PORT3_LANES_SHIFT        8
#घोषणा MRFLD_PORT_CONFIG_MASK 0x000f03ff
#घोषणा MRFLD_PORT_CONFIGCODE_SHIFT    16
#घोषणा MRFLD_ALL_CSI_PORTS_OFF_MASK   0x7

#घोषणा CHV_PORT3_LANES_SHIFT		9
#घोषणा CHV_PORT_CONFIG_MASK		0x1f07ff

#घोषणा ISPSSPM1				0x3a
#घोषणा ISP_FREQ_STAT_MASK			(0x1f << ISP_FREQ_STAT_OFFSET)
#घोषणा ISP_REQ_FREQ_MASK			0x1f
#घोषणा ISP_FREQ_VALID_MASK			(0x1 << ISP_FREQ_VALID_OFFSET)
#घोषणा ISP_FREQ_STAT_OFFSET			0x18
#घोषणा ISP_REQ_GUAR_FREQ_OFFSET		0x8
#घोषणा ISP_REQ_FREQ_OFFSET			0x0
#घोषणा ISP_FREQ_VALID_OFFSET			0x7
#घोषणा ISP_FREQ_RULE_ANY			0x0

#घोषणा ISP_FREQ_457MHZ				0x1C9
#घोषणा ISP_FREQ_400MHZ				0x190
#घोषणा ISP_FREQ_356MHZ				0x164
#घोषणा ISP_FREQ_320MHZ				0x140
#घोषणा ISP_FREQ_266MHZ				0x10a
#घोषणा ISP_FREQ_200MHZ				0xc8
#घोषणा ISP_FREQ_100MHZ				0x64

#घोषणा HPLL_FREQ_800MHZ			0x320
#घोषणा HPLL_FREQ_1600MHZ			0x640
#घोषणा HPLL_FREQ_2000MHZ			0x7D0

#घोषणा CCK_FUSE_REG_0			0x08
#घोषणा CCK_FUSE_HPLL_FREQ_MASK		0x03

/* ISP2401 CSI2+ receiver delay settings */
#घोषणा CSI2_PORT_A_BASE					0xC0000
#घोषणा CSI2_PORT_B_BASE					0xC2000
#घोषणा CSI2_PORT_C_BASE					0xC4000

#घोषणा CSI2_LANE_CL_BASE					0x418
#घोषणा CSI2_LANE_D0_BASE					0x420
#घोषणा CSI2_LANE_D1_BASE					0x428
#घोषणा CSI2_LANE_D2_BASE					0x430
#घोषणा CSI2_LANE_D3_BASE					0x438

#घोषणा CSI2_REG_RX_CSI_DLY_CNT_TERMEN				0
#घोषणा CSI2_REG_RX_CSI_DLY_CNT_SETTLE				0x4

#घोषणा CSI2_PORT_A_RX_CSI_DLY_CNT_TERMEN_CLANE			0xC0418
#घोषणा CSI2_PORT_A_RX_CSI_DLY_CNT_SETTLE_CLANE			0xC041C
#घोषणा CSI2_PORT_A_RX_CSI_DLY_CNT_TERMEN_DLANE0		0xC0420
#घोषणा CSI2_PORT_A_RX_CSI_DLY_CNT_SETTLE_DLANE0		0xC0424
#घोषणा CSI2_PORT_A_RX_CSI_DLY_CNT_TERMEN_DLANE1		0xC0428
#घोषणा CSI2_PORT_A_RX_CSI_DLY_CNT_SETTLE_DLANE1		0xC042C
#घोषणा CSI2_PORT_A_RX_CSI_DLY_CNT_TERMEN_DLANE2		0xC0430
#घोषणा CSI2_PORT_A_RX_CSI_DLY_CNT_SETTLE_DLANE2		0xC0434
#घोषणा CSI2_PORT_A_RX_CSI_DLY_CNT_TERMEN_DLANE3		0xC0438
#घोषणा CSI2_PORT_A_RX_CSI_DLY_CNT_SETTLE_DLANE3		0xC043C

#घोषणा CSI2_PORT_B_RX_CSI_DLY_CNT_TERMEN_CLANE			0xC2418
#घोषणा CSI2_PORT_B_RX_CSI_DLY_CNT_SETTLE_CLANE			0xC241C
#घोषणा CSI2_PORT_B_RX_CSI_DLY_CNT_TERMEN_DLANE0		0xC2420
#घोषणा CSI2_PORT_B_RX_CSI_DLY_CNT_SETTLE_DLANE0		0xC2424
#घोषणा CSI2_PORT_B_RX_CSI_DLY_CNT_TERMEN_DLANE1		0xC2428
#घोषणा CSI2_PORT_B_RX_CSI_DLY_CNT_SETTLE_DLANE1		0xC242C

#घोषणा CSI2_PORT_C_RX_CSI_DLY_CNT_TERMEN_CLANE			0xC4418
#घोषणा CSI2_PORT_C_RX_CSI_DLY_CNT_SETTLE_CLANE			0xC441C
#घोषणा CSI2_PORT_C_RX_CSI_DLY_CNT_TERMEN_DLANE0		0xC4420
#घोषणा CSI2_PORT_C_RX_CSI_DLY_CNT_SETTLE_DLANE0		0xC4424
#घोषणा CSI2_PORT_C_RX_CSI_DLY_CNT_TERMEN_DLANE1		0xC4428
#घोषणा CSI2_PORT_C_RX_CSI_DLY_CNT_SETTLE_DLANE1		0xC442C

#घोषणा DMA_BURST_SIZE_REG					0xCD408

#घोषणा ISP_DFS_TRY_TIMES	2

#पूर्ण_अगर /* ATOMISP_REGS_H */
