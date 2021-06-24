<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/mach-pxa/include/mach/idp.h
 *
 * Copyright (c) 2001 Clअगरf Brake, Accelent Systems Inc.
 *
 * 2001-09-13: Clअगरf Brake <cbrake@accelent.com>
 *             Initial code
 *
 * 2005-02-15: Clअगरf Brake <clअगरf.brake@gmail.com>
 *             <http://www.vibren.com> <http://bec-प्रणालीs.com>
 *             Changes क्रम 2.6 kernel.
 */


/*
 * Note: this file must be safe to include in assembly files
 *
 * Support क्रम the Vibren PXA255 IDP requires rev04 or later
 * IDP hardware.
 */

#समावेश <mach/irqs.h> /* PXA_GPIO_TO_IRQ */

#घोषणा IDP_FLASH_PHYS		(PXA_CS0_PHYS)
#घोषणा IDP_ALT_FLASH_PHYS	(PXA_CS1_PHYS)
#घोषणा IDP_MEDIAQ_PHYS		(PXA_CS3_PHYS)
#घोषणा IDP_IDE_PHYS		(PXA_CS5_PHYS + 0x03000000)
#घोषणा IDP_ETH_PHYS		(PXA_CS5_PHYS + 0x03400000)
#घोषणा IDP_COREVOLT_PHYS	(PXA_CS5_PHYS + 0x03800000)
#घोषणा IDP_CPLD_PHYS		(PXA_CS5_PHYS + 0x03C00000)


/*
 * भव memory map
 */

#घोषणा IDP_COREVOLT_VIRT	(0xf0000000)
#घोषणा IDP_COREVOLT_SIZE	(1*1024*1024)

#घोषणा IDP_CPLD_VIRT		(IDP_COREVOLT_VIRT + IDP_COREVOLT_SIZE)
#घोषणा IDP_CPLD_SIZE		(1*1024*1024)

#अगर (IDP_CPLD_VIRT + IDP_CPLD_SIZE) > 0xfc000000
#त्रुटि Your custom IO space is getting a bit large !!
#पूर्ण_अगर

#घोषणा CPLD_P2V(x)		((x) - IDP_CPLD_PHYS + IDP_CPLD_VIRT)
#घोषणा CPLD_V2P(x)		((x) - IDP_CPLD_VIRT + IDP_CPLD_PHYS)

#अगर_अघोषित __ASSEMBLY__
#  define __CPLD_REG(x)		(*((अस्थिर अचिन्हित दीर्घ *)CPLD_P2V(x)))
#अन्यथा
#  define __CPLD_REG(x)		CPLD_P2V(x)
#पूर्ण_अगर

/* board level रेजिस्टरs in the CPLD: (offsets from CPLD_VIRT) */

#घोषणा _IDP_CPLD_REV			(IDP_CPLD_PHYS + 0x00)
#घोषणा _IDP_CPLD_PERIPH_PWR		(IDP_CPLD_PHYS + 0x04)
#घोषणा _IDP_CPLD_LED_CONTROL		(IDP_CPLD_PHYS + 0x08)
#घोषणा _IDP_CPLD_KB_COL_HIGH		(IDP_CPLD_PHYS + 0x0C)
#घोषणा _IDP_CPLD_KB_COL_LOW		(IDP_CPLD_PHYS + 0x10)
#घोषणा _IDP_CPLD_PCCARD_EN		(IDP_CPLD_PHYS + 0x14)
#घोषणा _IDP_CPLD_GPIOH_सूची		(IDP_CPLD_PHYS + 0x18)
#घोषणा _IDP_CPLD_GPIOH_VALUE		(IDP_CPLD_PHYS + 0x1C)
#घोषणा _IDP_CPLD_GPIOL_सूची		(IDP_CPLD_PHYS + 0x20)
#घोषणा _IDP_CPLD_GPIOL_VALUE		(IDP_CPLD_PHYS + 0x24)
#घोषणा _IDP_CPLD_PCCARD_PWR		(IDP_CPLD_PHYS + 0x28)
#घोषणा _IDP_CPLD_MISC_CTRL		(IDP_CPLD_PHYS + 0x2C)
#घोषणा _IDP_CPLD_LCD			(IDP_CPLD_PHYS + 0x30)
#घोषणा _IDP_CPLD_FLASH_WE		(IDP_CPLD_PHYS + 0x34)

#घोषणा _IDP_CPLD_KB_ROW		(IDP_CPLD_PHYS + 0x50)
#घोषणा _IDP_CPLD_PCCARD0_STATUS	(IDP_CPLD_PHYS + 0x54)
#घोषणा _IDP_CPLD_PCCARD1_STATUS	(IDP_CPLD_PHYS + 0x58)
#घोषणा _IDP_CPLD_MISC_STATUS		(IDP_CPLD_PHYS + 0x5C)

/* FPGA रेजिस्टर भव addresses */

#घोषणा IDP_CPLD_REV			__CPLD_REG(_IDP_CPLD_REV)
#घोषणा IDP_CPLD_PERIPH_PWR		__CPLD_REG(_IDP_CPLD_PERIPH_PWR)
#घोषणा IDP_CPLD_LED_CONTROL		__CPLD_REG(_IDP_CPLD_LED_CONTROL)
#घोषणा IDP_CPLD_KB_COL_HIGH		__CPLD_REG(_IDP_CPLD_KB_COL_HIGH)
#घोषणा IDP_CPLD_KB_COL_LOW		__CPLD_REG(_IDP_CPLD_KB_COL_LOW)
#घोषणा IDP_CPLD_PCCARD_EN		__CPLD_REG(_IDP_CPLD_PCCARD_EN)
#घोषणा IDP_CPLD_GPIOH_सूची		__CPLD_REG(_IDP_CPLD_GPIOH_सूची)
#घोषणा IDP_CPLD_GPIOH_VALUE		__CPLD_REG(_IDP_CPLD_GPIOH_VALUE)
#घोषणा IDP_CPLD_GPIOL_सूची		__CPLD_REG(_IDP_CPLD_GPIOL_सूची)
#घोषणा IDP_CPLD_GPIOL_VALUE		__CPLD_REG(_IDP_CPLD_GPIOL_VALUE)
#घोषणा IDP_CPLD_PCCARD_PWR		__CPLD_REG(_IDP_CPLD_PCCARD_PWR)
#घोषणा IDP_CPLD_MISC_CTRL		__CPLD_REG(_IDP_CPLD_MISC_CTRL)
#घोषणा IDP_CPLD_LCD			__CPLD_REG(_IDP_CPLD_LCD)
#घोषणा IDP_CPLD_FLASH_WE		__CPLD_REG(_IDP_CPLD_FLASH_WE)

#घोषणा IDP_CPLD_KB_ROW		        __CPLD_REG(_IDP_CPLD_KB_ROW)
#घोषणा IDP_CPLD_PCCARD0_STATUS	        __CPLD_REG(_IDP_CPLD_PCCARD0_STATUS)
#घोषणा IDP_CPLD_PCCARD1_STATUS	        __CPLD_REG(_IDP_CPLD_PCCARD1_STATUS)
#घोषणा IDP_CPLD_MISC_STATUS		__CPLD_REG(_IDP_CPLD_MISC_STATUS)


/*
 * Bit masks क्रम various रेजिस्टरs
 */

// IDP_CPLD_PCCARD_PWR
#घोषणा PCC0_PWR0	(1 << 0)
#घोषणा PCC0_PWR1	(1 << 1)
#घोषणा PCC0_PWR2	(1 << 2)
#घोषणा PCC0_PWR3	(1 << 3)
#घोषणा PCC1_PWR0	(1 << 4)
#घोषणा PCC1_PWR1	(1 << 5)
#घोषणा PCC1_PWR2	(1 << 6)
#घोषणा PCC1_PWR3	(1 << 7)

// IDP_CPLD_PCCARD_EN
#घोषणा PCC0_RESET	(1 << 6)
#घोषणा PCC1_RESET	(1 << 7)
#घोषणा PCC0_ENABLE	(1 << 0)
#घोषणा PCC1_ENABLE	(1 << 1)

// IDP_CPLD_PCCARDx_STATUS
#घोषणा _PCC_WRPROT	(1 << 7) // 7-4 पढ़ो as low true
#घोषणा _PCC_RESET	(1 << 6)
#घोषणा _PCC_IRQ	(1 << 5)
#घोषणा _PCC_INPACK	(1 << 4)
#घोषणा PCC_BVD2	(1 << 3)
#घोषणा PCC_BVD1	(1 << 2)
#घोषणा PCC_VS2		(1 << 1)
#घोषणा PCC_VS1		(1 << 0)

/* A listing of पूर्णांकerrupts used by बाह्यal hardware devices */

#घोषणा TOUCH_PANEL_IRQ			PXA_GPIO_TO_IRQ(5)
#घोषणा IDE_IRQ				PXA_GPIO_TO_IRQ(21)

#घोषणा TOUCH_PANEL_IRQ_EDGE		IRQ_TYPE_EDGE_FALLING

#घोषणा ETHERNET_IRQ			PXA_GPIO_TO_IRQ(4)
#घोषणा ETHERNET_IRQ_EDGE		IRQ_TYPE_EDGE_RISING

#घोषणा IDE_IRQ_EDGE			IRQ_TYPE_EDGE_RISING

#घोषणा PCMCIA_S0_CD_VALID		PXA_GPIO_TO_IRQ(7)
#घोषणा PCMCIA_S0_CD_VALID_EDGE		IRQ_TYPE_EDGE_BOTH

#घोषणा PCMCIA_S1_CD_VALID		PXA_GPIO_TO_IRQ(8)
#घोषणा PCMCIA_S1_CD_VALID_EDGE		IRQ_TYPE_EDGE_BOTH

#घोषणा PCMCIA_S0_RDYINT		PXA_GPIO_TO_IRQ(19)
#घोषणा PCMCIA_S1_RDYINT		PXA_GPIO_TO_IRQ(22)


/*
 * Macros क्रम LED Driver
 */

/* leds 0 = ON */
#घोषणा IDP_HB_LED	(1<<5)
#घोषणा IDP_BUSY_LED	(1<<6)

#घोषणा IDP_LEDS_MASK	(IDP_HB_LED | IDP_BUSY_LED)

/*
 * macros क्रम MTD driver
 */

#घोषणा FLASH_WRITE_PROTECT_DISABLE()	((IDP_CPLD_FLASH_WE) &= ~(0x1))
#घोषणा FLASH_WRITE_PROTECT_ENABLE()	((IDP_CPLD_FLASH_WE) |= (0x1))

/*
 * macros क्रम matrix keyboard driver
 */

#घोषणा KEYBD_MATRIX_NUMBER_INPUTS	7
#घोषणा KEYBD_MATRIX_NUMBER_OUTPUTS	14

#घोषणा KEYBD_MATRIX_INVERT_OUTPUT_LOGIC	FALSE
#घोषणा KEYBD_MATRIX_INVERT_INPUT_LOGIC		FALSE

#घोषणा KEYBD_MATRIX_SETTLING_TIME_US			100
#घोषणा KEYBD_MATRIX_KEYSTATE_DEBOUNCE_CONSTANT		2

#घोषणा KEYBD_MATRIX_SET_OUTPUTS(outमाला_दो) \
अणु\
	IDP_CPLD_KB_COL_LOW = outमाला_दो;\
	IDP_CPLD_KB_COL_HIGH = outमाला_दो >> 7;\
पूर्ण

#घोषणा KEYBD_MATRIX_GET_INPUTS(inमाला_दो) \
अणु\
	inमाला_दो = (IDP_CPLD_KB_ROW & 0x7f);\
पूर्ण


