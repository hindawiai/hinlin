<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2006,2007 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2006,2007 Eugene Konev <ejka@खोलोwrt.org>
 */

#अगर_अघोषित __AR7_H__
#घोषणा __AR7_H__

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/त्रुटिसं.स>

#समावेश <यंत्र/addrspace.h>

#घोषणा AR7_SDRAM_BASE	0x14000000

#घोषणा AR7_REGS_BASE	0x08610000

#घोषणा AR7_REGS_MAC0	(AR7_REGS_BASE + 0x0000)
#घोषणा AR7_REGS_GPIO	(AR7_REGS_BASE + 0x0900)
/* 0x08610A00 - 0x08610BFF (512 bytes, 128 bytes / घड़ी) */
#घोषणा AR7_REGS_POWER	(AR7_REGS_BASE + 0x0a00)
#घोषणा AR7_REGS_CLOCKS (AR7_REGS_POWER + 0x80)
#घोषणा UR8_REGS_CLOCKS (AR7_REGS_POWER + 0x20)
#घोषणा AR7_REGS_UART0	(AR7_REGS_BASE + 0x0e00)
#घोषणा AR7_REGS_USB	(AR7_REGS_BASE + 0x1200)
#घोषणा AR7_REGS_RESET	(AR7_REGS_BASE + 0x1600)
#घोषणा AR7_REGS_PINSEL (AR7_REGS_BASE + 0x160C)
#घोषणा AR7_REGS_VLYNQ0 (AR7_REGS_BASE + 0x1800)
#घोषणा AR7_REGS_DCL	(AR7_REGS_BASE + 0x1a00)
#घोषणा AR7_REGS_VLYNQ1 (AR7_REGS_BASE + 0x1c00)
#घोषणा AR7_REGS_MDIO	(AR7_REGS_BASE + 0x1e00)
#घोषणा AR7_REGS_IRQ	(AR7_REGS_BASE + 0x2400)
#घोषणा AR7_REGS_MAC1	(AR7_REGS_BASE + 0x2800)

#घोषणा AR7_REGS_WDT	(AR7_REGS_BASE + 0x1f00)
#घोषणा UR8_REGS_WDT	(AR7_REGS_BASE + 0x0b00)
#घोषणा UR8_REGS_UART1	(AR7_REGS_BASE + 0x0f00)

/* Titan रेजिस्टरs */
#घोषणा TITAN_REGS_ESWITCH_BASE (0x08640000)
#घोषणा TITAN_REGS_MAC0		(TITAN_REGS_ESWITCH_BASE)
#घोषणा TITAN_REGS_MAC1		(TITAN_REGS_ESWITCH_BASE + 0x0800)
#घोषणा TITAN_REGS_MDIO		(TITAN_REGS_ESWITCH_BASE + 0x02000)
#घोषणा TITAN_REGS_VLYNQ0	(AR7_REGS_BASE + 0x1c00)
#घोषणा TITAN_REGS_VLYNQ1	(AR7_REGS_BASE + 0x1300)

#घोषणा AR7_RESET_PERIPHERAL	0x0
#घोषणा AR7_RESET_SOFTWARE	0x4
#घोषणा AR7_RESET_STATUS	0x8

#घोषणा AR7_RESET_BIT_CPMAC_LO	17
#घोषणा AR7_RESET_BIT_CPMAC_HI	21
#घोषणा AR7_RESET_BIT_MDIO	22
#घोषणा AR7_RESET_BIT_EPHY	26

#घोषणा TITAN_RESET_BIT_EPHY1	28

/* GPIO control रेजिस्टरs */
#घोषणा AR7_GPIO_INPUT	0x0
#घोषणा AR7_GPIO_OUTPUT 0x4
#घोषणा AR7_GPIO_सूची	0x8
#घोषणा AR7_GPIO_ENABLE 0xc
#घोषणा TITAN_GPIO_INPUT_0	0x0
#घोषणा TITAN_GPIO_INPUT_1	0x4
#घोषणा TITAN_GPIO_OUTPUT_0	0x8
#घोषणा TITAN_GPIO_OUTPUT_1	0xc
#घोषणा TITAN_GPIO_सूची_0	0x10
#घोषणा TITAN_GPIO_सूची_1	0x14
#घोषणा TITAN_GPIO_ENBL_0	0x18
#घोषणा TITAN_GPIO_ENBL_1	0x1c

#घोषणा AR7_CHIP_7100	0x18
#घोषणा AR7_CHIP_7200	0x2b
#घोषणा AR7_CHIP_7300	0x05
#घोषणा AR7_CHIP_TITAN	0x07
#घोषणा TITAN_CHIP_1050 0x0f
#घोषणा TITAN_CHIP_1055 0x0e
#घोषणा TITAN_CHIP_1056 0x0d
#घोषणा TITAN_CHIP_1060 0x07

/* Interrupts */
#घोषणा AR7_IRQ_UART0	15
#घोषणा AR7_IRQ_UART1	16

/* Clocks */
#घोषणा AR7_AFE_CLOCK	35328000
#घोषणा AR7_REF_CLOCK	25000000
#घोषणा AR7_XTAL_CLOCK	24000000

/* DCL */
#घोषणा AR7_WDT_HW_ENA	0x10

काष्ठा plat_cpmac_data अणु
	पूर्णांक reset_bit;
	पूर्णांक घातer_bit;
	u32 phy_mask;
	अक्षर dev_addr[6];
पूर्ण;

काष्ठा plat_dsl_data अणु
	पूर्णांक reset_bit_dsl;
	पूर्णांक reset_bit_sar;
पूर्ण;

बाह्य पूर्णांक ar7_cpu_घड़ी, ar7_bus_घड़ी, ar7_dsp_घड़ी;

अटल अंतरभूत पूर्णांक ar7_is_titan(व्योम)
अणु
	वापस (पढ़ोl((व्योम *)KSEG1ADDR(AR7_REGS_GPIO + 0x24)) & 0xffff) ==
		AR7_CHIP_TITAN;
पूर्ण

अटल अंतरभूत u16 ar7_chip_id(व्योम)
अणु
	वापस ar7_is_titan() ? AR7_CHIP_TITAN : (पढ़ोl((व्योम *)
		KSEG1ADDR(AR7_REGS_GPIO + 0x14)) & 0xffff);
पूर्ण

अटल अंतरभूत u16 titan_chip_id(व्योम)
अणु
	अचिन्हित पूर्णांक val = पढ़ोl((व्योम *)KSEG1ADDR(AR7_REGS_GPIO +
						TITAN_GPIO_INPUT_1));
	वापस ((val >> 12) & 0x0f);
पूर्ण

अटल अंतरभूत u8 ar7_chip_rev(व्योम)
अणु
	वापस (पढ़ोl((व्योम *)KSEG1ADDR(AR7_REGS_GPIO + (ar7_is_titan() ? 0x24 :
		0x14))) >> 16) & 0xff;
पूर्ण

काष्ठा clk अणु
	अचिन्हित पूर्णांक	rate;
पूर्ण;

अटल अंतरभूत पूर्णांक ar7_has_high_cpmac(व्योम)
अणु
	u16 chip_id = ar7_chip_id();
	चयन (chip_id) अणु
	हाल AR7_CHIP_7100:
	हाल AR7_CHIP_7200:
		वापस 0;
	हाल AR7_CHIP_7300:
		वापस 1;
	शेष:
		वापस -ENXIO;
	पूर्ण
पूर्ण
#घोषणा ar7_has_high_vlynq ar7_has_high_cpmac
#घोषणा ar7_has_second_uart ar7_has_high_cpmac

अटल अंतरभूत व्योम ar7_device_enable(u32 bit)
अणु
	व्योम *reset_reg =
		(व्योम *)KSEG1ADDR(AR7_REGS_RESET + AR7_RESET_PERIPHERAL);
	ग_लिखोl(पढ़ोl(reset_reg) | (1 << bit), reset_reg);
	msleep(20);
पूर्ण

अटल अंतरभूत व्योम ar7_device_disable(u32 bit)
अणु
	व्योम *reset_reg =
		(व्योम *)KSEG1ADDR(AR7_REGS_RESET + AR7_RESET_PERIPHERAL);
	ग_लिखोl(पढ़ोl(reset_reg) & ~(1 << bit), reset_reg);
	msleep(20);
पूर्ण

अटल अंतरभूत व्योम ar7_device_reset(u32 bit)
अणु
	ar7_device_disable(bit);
	ar7_device_enable(bit);
पूर्ण

अटल अंतरभूत व्योम ar7_device_on(u32 bit)
अणु
	व्योम *घातer_reg = (व्योम *)KSEG1ADDR(AR7_REGS_POWER);
	ग_लिखोl(पढ़ोl(घातer_reg) | (1 << bit), घातer_reg);
	msleep(20);
पूर्ण

अटल अंतरभूत व्योम ar7_device_off(u32 bit)
अणु
	व्योम *घातer_reg = (व्योम *)KSEG1ADDR(AR7_REGS_POWER);
	ग_लिखोl(पढ़ोl(घातer_reg) & ~(1 << bit), घातer_reg);
	msleep(20);
पूर्ण

पूर्णांक __init ar7_gpio_init(व्योम);
व्योम __init ar7_init_घड़ीs(व्योम);

/* Board specअगरic GPIO functions */
पूर्णांक ar7_gpio_enable(अचिन्हित gpio);
पूर्णांक ar7_gpio_disable(अचिन्हित gpio);

#पूर्ण_अगर /* __AR7_H__ */
