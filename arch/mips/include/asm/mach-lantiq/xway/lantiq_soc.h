<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 *  Copyright (C) 2010 John Crispin <john@phrozen.org>
 */

#अगर_अघोषित _LTQ_XWAY_H__
#घोषणा _LTQ_XWAY_H__

#अगर_घोषित CONFIG_SOC_TYPE_XWAY

#समावेश <lantiq.h>

/* Chip IDs */
#घोषणा SOC_ID_DANUBE1		0x129
#घोषणा SOC_ID_DANUBE2		0x12B
#घोषणा SOC_ID_TWINPASS		0x12D
#घोषणा SOC_ID_AMAZON_SE_1	0x152 /* 50601 */
#घोषणा SOC_ID_AMAZON_SE_2	0x153 /* 50600 */
#घोषणा SOC_ID_ARX188		0x16C
#घोषणा SOC_ID_ARX168_1		0x16D
#घोषणा SOC_ID_ARX168_2		0x16E
#घोषणा SOC_ID_ARX182		0x16F
#घोषणा SOC_ID_GRX188		0x170
#घोषणा SOC_ID_GRX168		0x171

#घोषणा SOC_ID_VRX288		0x1C0 /* v1.1 */
#घोषणा SOC_ID_VRX282		0x1C1 /* v1.1 */
#घोषणा SOC_ID_VRX268		0x1C2 /* v1.1 */
#घोषणा SOC_ID_GRX268		0x1C8 /* v1.1 */
#घोषणा SOC_ID_GRX288		0x1C9 /* v1.1 */
#घोषणा SOC_ID_VRX288_2		0x00B /* v1.2 */
#घोषणा SOC_ID_VRX268_2		0x00C /* v1.2 */
#घोषणा SOC_ID_GRX288_2		0x00D /* v1.2 */
#घोषणा SOC_ID_GRX282_2		0x00E /* v1.2 */
#घोषणा SOC_ID_VRX220		0x000

#घोषणा SOC_ID_ARX362		0x004
#घोषणा SOC_ID_ARX368		0x005
#घोषणा SOC_ID_ARX382		0x007
#घोषणा SOC_ID_ARX388		0x008
#घोषणा SOC_ID_URX388		0x009
#घोषणा SOC_ID_GRX383		0x010
#घोषणा SOC_ID_GRX369		0x011
#घोषणा SOC_ID_GRX387		0x00F
#घोषणा SOC_ID_GRX389		0x012

 /* SoC Types */
#घोषणा SOC_TYPE_DANUBE		0x01
#घोषणा SOC_TYPE_TWINPASS	0x02
#घोषणा SOC_TYPE_AR9		0x03
#घोषणा SOC_TYPE_VR9		0x04 /* v1.1 */
#घोषणा SOC_TYPE_VR9_2		0x05 /* v1.2 */
#घोषणा SOC_TYPE_AMAZON_SE	0x06
#घोषणा SOC_TYPE_AR10		0x07
#घोषणा SOC_TYPE_GRX390		0x08
#घोषणा SOC_TYPE_VRX220		0x09

/* BOOT_SEL - find what boot media we have */
#घोषणा BS_EXT_ROM		0x0
#घोषणा BS_FLASH		0x1
#घोषणा BS_MII0			0x2
#घोषणा BS_PCI			0x3
#घोषणा BS_UART1		0x4
#घोषणा BS_SPI			0x5
#घोषणा BS_न_अंकD			0x6
#घोषणा BS_RMII0		0x7

/* helpers used to access the cgu */
#घोषणा ltq_cgu_w32(x, y)	ltq_w32((x), ltq_cgu_membase + (y))
#घोषणा ltq_cgu_r32(x)		ltq_r32(ltq_cgu_membase + (x))
बाह्य __iomem व्योम *ltq_cgu_membase;

/*
 * during early_prपूर्णांकk no ioremap is possible
 * let's use KSEG1 instead
 */
#घोषणा LTQ_ASC1_BASE_ADDR	0x1E100C00
#घोषणा LTQ_EARLY_ASC		KSEG1ADDR(LTQ_ASC1_BASE_ADDR)

/* EBU - बाह्यal bus unit */
#घोषणा LTQ_EBU_BUSCON0		0x0060
#घोषणा LTQ_EBU_PCC_CON		0x0090
#घोषणा LTQ_EBU_PCC_IEN		0x00A4
#घोषणा LTQ_EBU_PCC_ISTAT	0x00A0
#घोषणा LTQ_EBU_BUSCON1		0x0064
#घोषणा LTQ_EBU_ADDRSEL1	0x0024
#घोषणा EBU_WRDIS		0x80000000

/* WDT */
#घोषणा LTQ_RST_CAUSE_WDTRST	0x20

/* MPS - multi processor unit (voice) */
#घोषणा LTQ_MPS_BASE_ADDR	(KSEG1 + 0x1F107000)
#घोषणा LTQ_MPS_CHIPID		((u32 *)(LTQ_MPS_BASE_ADDR + 0x0344))

/* allow booting xrx200 phys */
पूर्णांक xrx200_gphy_boot(काष्ठा device *dev, अचिन्हित पूर्णांक id, dma_addr_t dev_addr);

/* request a non-gpio and set the PIO config */
#घोषणा PMU_PPE			 BIT(13)
बाह्य व्योम ltq_pmu_enable(अचिन्हित पूर्णांक module);
बाह्य व्योम ltq_pmu_disable(अचिन्हित पूर्णांक module);

#पूर्ण_अगर /* CONFIG_SOC_TYPE_XWAY */
#पूर्ण_अगर /* _LTQ_XWAY_H__ */
