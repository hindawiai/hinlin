<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * arch/arm/mach-ixp4xx/include/mach/platक्रमm.h
 *
 * Constants and functions that are useful to IXP4xx platक्रमm-specअगरic code
 * and device drivers.
 *
 * Copyright (C) 2004 MontaVista Software, Inc.
 */

#अगर_अघोषित __ASM_ARCH_HARDWARE_H__
#त्रुटि "Do not include this directly, instead #include <mach/hardware.h>"
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/reboot.h>
#समावेश <linux/platक्रमm_data/eth_ixp4xx.h>

#समावेश <यंत्र/types.h>

#अगर_अघोषित	__ARMEB__
#घोषणा	REG_OFFSET	0
#अन्यथा
#घोषणा	REG_OFFSET	3
#पूर्ण_अगर

/*
 * Expansion bus memory regions
 */
#घोषणा IXP4XX_EXP_BUS_BASE_PHYS	(0x50000000)

/*
 * The expansion bus on the IXP4xx can be configured क्रम either 16 or
 * 32MB winकरोws and the CS offset क्रम each region changes based on the
 * current configuration. This means that we cannot simply hardcode
 * each offset. ixp4xx_sys_init() looks at the expansion bus configuration
 * as setup by the bootloader to determine our winकरोw size.
 */
बाह्य अचिन्हित दीर्घ ixp4xx_exp_bus_size;

#घोषणा	IXP4XX_EXP_BUS_BASE(region)\
		(IXP4XX_EXP_BUS_BASE_PHYS + ((region) * ixp4xx_exp_bus_size))

#घोषणा IXP4XX_EXP_BUS_END(region)\
		(IXP4XX_EXP_BUS_BASE(region) + ixp4xx_exp_bus_size - 1)

/* Those macros can be used to adjust timing and configure
 * other features क्रम each region.
 */

#घोषणा IXP4XX_EXP_BUS_RECOVERY_T(x)	(((x) & 0x0f) << 16)
#घोषणा IXP4XX_EXP_BUS_HOLD_T(x)	(((x) & 0x03) << 20)
#घोषणा IXP4XX_EXP_BUS_STROBE_T(x)	(((x) & 0x0f) << 22)
#घोषणा IXP4XX_EXP_BUS_SETUP_T(x)	(((x) & 0x03) << 26)
#घोषणा IXP4XX_EXP_BUS_ADDR_T(x)	(((x) & 0x03) << 28)
#घोषणा IXP4XX_EXP_BUS_SIZE(x)		(((x) & 0x0f) << 10)
#घोषणा IXP4XX_EXP_BUS_CYCLES(x)	(((x) & 0x03) << 14)

#घोषणा IXP4XX_EXP_BUS_CS_EN		(1L << 31)
#घोषणा IXP4XX_EXP_BUS_BYTE_RD16	(1L << 6)
#घोषणा IXP4XX_EXP_BUS_HRDY_POL		(1L << 5)
#घोषणा IXP4XX_EXP_BUS_MUX_EN		(1L << 4)
#घोषणा IXP4XX_EXP_BUS_SPLT_EN		(1L << 3)
#घोषणा IXP4XX_EXP_BUS_WR_EN		(1L << 1)
#घोषणा IXP4XX_EXP_BUS_BYTE_EN		(1L << 0)

#घोषणा IXP4XX_EXP_BUS_CYCLES_INTEL	0x00
#घोषणा IXP4XX_EXP_BUS_CYCLES_MOTOROLA	0x01
#घोषणा IXP4XX_EXP_BUS_CYCLES_HPI	0x02

#घोषणा IXP4XX_FLASH_WRITABLE	(0x2)
#घोषणा IXP4XX_FLASH_DEFAULT	(0xbcd23c40)
#घोषणा IXP4XX_FLASH_WRITE	(0xbcd23c42)

/*
 * Clock Speed Definitions.
 */
#घोषणा IXP4XX_PERIPHERAL_BUS_CLOCK 	(66) /* 66MHzi APB BUS   */ 
#घोषणा IXP4XX_UART_XTAL        	14745600

/*
 * This काष्ठाure provide a means क्रम the board setup code
 * to give inक्रमmation to th pata_ixp4xx driver. It is
 * passed as platक्रमm_data.
 */
काष्ठा ixp4xx_pata_data अणु
	अस्थिर u32	*cs0_cfg;
	अस्थिर u32	*cs1_cfg;
	अचिन्हित दीर्घ	cs0_bits;
	अचिन्हित दीर्घ	cs1_bits;
	व्योम __iomem	*cs0;
	व्योम __iomem	*cs1;
पूर्ण;

/*
 * Frequency of घड़ी used क्रम primary घड़ीsource
 */
बाह्य अचिन्हित दीर्घ ixp4xx_समयr_freq;

/*
 * Functions used by platक्रमm-level setup code
 */
बाह्य व्योम ixp4xx_map_io(व्योम);
बाह्य व्योम ixp4xx_init_early(व्योम);
बाह्य व्योम ixp4xx_init_irq(व्योम);
बाह्य व्योम ixp4xx_sys_init(व्योम);
बाह्य व्योम ixp4xx_समयr_init(व्योम);
बाह्य व्योम ixp4xx_restart(क्रमागत reboot_mode, स्थिर अक्षर *);
बाह्य व्योम ixp4xx_pci_preinit(व्योम);
काष्ठा pci_sys_data;
बाह्य पूर्णांक ixp4xx_setup(पूर्णांक nr, काष्ठा pci_sys_data *sys);
बाह्य काष्ठा pci_ops ixp4xx_ops;

#पूर्ण_अगर // __ASSEMBLY__

