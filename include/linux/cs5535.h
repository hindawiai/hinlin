<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AMD CS5535/CS5536 definitions
 * Copyright (C) 2006  Advanced Micro Devices, Inc.
 * Copyright (C) 2009  Andres Salomon <dilinger@collabora.co.uk>
 */

#अगर_अघोषित _CS5535_H
#घोषणा _CS5535_H

#समावेश <यंत्र/msr.h>

/* MSRs */
#घोषणा MSR_GLIU_P2D_RO0	0x10000029

#घोषणा MSR_LX_GLD_MSR_CONFIG	0x48002001
#घोषणा MSR_LX_MSR_PADSEL	0x48002011	/* NOT 0x48000011; the data
						 * sheet has the wrong value */
#घोषणा MSR_GLCP_SYS_RSTPLL	0x4C000014
#घोषणा MSR_GLCP_DOTPLL		0x4C000015

#घोषणा MSR_LBAR_SMB		0x5140000B
#घोषणा MSR_LBAR_GPIO		0x5140000C
#घोषणा MSR_LBAR_MFGPT		0x5140000D
#घोषणा MSR_LBAR_ACPI		0x5140000E
#घोषणा MSR_LBAR_PMS		0x5140000F

#घोषणा MSR_DIVIL_SOFT_RESET	0x51400017

#घोषणा MSR_PIC_YSEL_LOW	0x51400020
#घोषणा MSR_PIC_YSEL_HIGH	0x51400021
#घोषणा MSR_PIC_ZSEL_LOW	0x51400022
#घोषणा MSR_PIC_ZSEL_HIGH	0x51400023
#घोषणा MSR_PIC_IRQM_LPC	0x51400025

#घोषणा MSR_MFGPT_IRQ		0x51400028
#घोषणा MSR_MFGPT_NR		0x51400029
#घोषणा MSR_MFGPT_SETUP		0x5140002B

#घोषणा MSR_RTC_DOMA_OFFSET	0x51400055
#घोषणा MSR_RTC_MONA_OFFSET	0x51400056
#घोषणा MSR_RTC_CEN_OFFSET	0x51400057

#घोषणा MSR_LX_SPARE_MSR	0x80000011	/* DC-specअगरic */

#घोषणा MSR_GX_GLD_MSR_CONFIG	0xC0002001
#घोषणा MSR_GX_MSR_PADSEL	0xC0002011

अटल अंतरभूत पूर्णांक cs5535_pic_unreqz_select_high(अचिन्हित पूर्णांक group,
						अचिन्हित पूर्णांक irq)
अणु
	uपूर्णांक32_t lo, hi;

	rdmsr(MSR_PIC_ZSEL_HIGH, lo, hi);
	lo &= ~(0xF << (group * 4));
	lo |= (irq & 0xF) << (group * 4);
	wrmsr(MSR_PIC_ZSEL_HIGH, lo, hi);
	वापस 0;
पूर्ण

/* PIC रेजिस्टरs */
#घोषणा CS5536_PIC_INT_SEL1	0x4d0
#घोषणा CS5536_PIC_INT_SEL2	0x4d1

/* resource sizes */
#घोषणा LBAR_GPIO_SIZE		0xFF
#घोषणा LBAR_MFGPT_SIZE		0x40
#घोषणा LBAR_ACPI_SIZE		0x40
#घोषणा LBAR_PMS_SIZE		0x80

/*
 * PMC रेजिस्टरs (PMS block)
 * It is only safe to access these रेजिस्टरs as dword accesses.
 * See CS5536 Specअगरication Update erratas 17 & 18
 */
#घोषणा CS5536_PM_SCLK		0x10
#घोषणा CS5536_PM_IN_SLPCTL	0x20
#घोषणा CS5536_PM_WKXD		0x34
#घोषणा CS5536_PM_WKD		0x30
#घोषणा CS5536_PM_SSC		0x54

/*
 * PM रेजिस्टरs (ACPI block)
 * It is only safe to access these रेजिस्टरs as dword accesses.
 * See CS5536 Specअगरication Update erratas 17 & 18
 */
#घोषणा CS5536_PM1_STS		0x00
#घोषणा CS5536_PM1_EN		0x02
#घोषणा CS5536_PM1_CNT		0x08
#घोषणा CS5536_PM_GPE0_STS	0x18
#घोषणा CS5536_PM_GPE0_EN	0x1c

/* CS5536_PM1_STS bits */
#घोषणा CS5536_WAK_FLAG		(1 << 15)
#घोषणा CS5536_RTC_FLAG		(1 << 10)
#घोषणा CS5536_PWRBTN_FLAG	(1 << 8)

/* CS5536_PM1_EN bits */
#घोषणा CS5536_PM_PWRBTN	(1 << 8)
#घोषणा CS5536_PM_RTC		(1 << 10)

/* CS5536_PM_GPE0_STS bits */
#घोषणा CS5536_GPIOM7_PME_FLAG	(1 << 31)
#घोषणा CS5536_GPIOM6_PME_FLAG	(1 << 30)

/* CS5536_PM_GPE0_EN bits */
#घोषणा CS5536_GPIOM7_PME_EN	(1 << 31)
#घोषणा CS5536_GPIOM6_PME_EN	(1 << 30)

/* VSA2 magic values */
#घोषणा VSA_VRC_INDEX		0xAC1C
#घोषणा VSA_VRC_DATA		0xAC1E
#घोषणा VSA_VR_UNLOCK		0xFC53  /* unlock भव रेजिस्टर */
#घोषणा VSA_VR_SIGNATURE	0x0003
#घोषणा VSA_VR_MEM_SIZE		0x0200
#घोषणा AMD_VSA_SIG		0x4132  /* signature is ascii 'VSA2' */
#घोषणा GSW_VSA_SIG		0x534d  /* General Software signature */

#समावेश <linux/पन.स>

अटल अंतरभूत पूर्णांक cs5535_has_vsa2(व्योम)
अणु
	अटल पूर्णांक has_vsa2 = -1;

	अगर (has_vsa2 == -1) अणु
		uपूर्णांक16_t val;

		/*
		 * The VSA has भव रेजिस्टरs that we can query क्रम a
		 * signature.
		 */
		outw(VSA_VR_UNLOCK, VSA_VRC_INDEX);
		outw(VSA_VR_SIGNATURE, VSA_VRC_INDEX);

		val = inw(VSA_VRC_DATA);
		has_vsa2 = (val == AMD_VSA_SIG || val == GSW_VSA_SIG);
	पूर्ण

	वापस has_vsa2;
पूर्ण

/* GPIOs */
#घोषणा GPIO_OUTPUT_VAL		0x00
#घोषणा GPIO_OUTPUT_ENABLE	0x04
#घोषणा GPIO_OUTPUT_OPEN_DRAIN	0x08
#घोषणा GPIO_OUTPUT_INVERT	0x0C
#घोषणा GPIO_OUTPUT_AUX1	0x10
#घोषणा GPIO_OUTPUT_AUX2	0x14
#घोषणा GPIO_PULL_UP		0x18
#घोषणा GPIO_PULL_DOWN		0x1C
#घोषणा GPIO_INPUT_ENABLE	0x20
#घोषणा GPIO_INPUT_INVERT	0x24
#घोषणा GPIO_INPUT_FILTER	0x28
#घोषणा GPIO_INPUT_EVENT_COUNT	0x2C
#घोषणा GPIO_READ_BACK		0x30
#घोषणा GPIO_INPUT_AUX1		0x34
#घोषणा GPIO_EVENTS_ENABLE	0x38
#घोषणा GPIO_LOCK_ENABLE	0x3C
#घोषणा GPIO_POSITIVE_EDGE_EN	0x40
#घोषणा GPIO_NEGATIVE_EDGE_EN	0x44
#घोषणा GPIO_POSITIVE_EDGE_STS	0x48
#घोषणा GPIO_NEGATIVE_EDGE_STS	0x4C

#घोषणा GPIO_FLTR7_AMOUNT	0xD8

#घोषणा GPIO_MAP_X		0xE0
#घोषणा GPIO_MAP_Y		0xE4
#घोषणा GPIO_MAP_Z		0xE8
#घोषणा GPIO_MAP_W		0xEC

#घोषणा GPIO_FE7_SEL		0xF7

व्योम cs5535_gpio_set(अचिन्हित offset, अचिन्हित पूर्णांक reg);
व्योम cs5535_gpio_clear(अचिन्हित offset, अचिन्हित पूर्णांक reg);
पूर्णांक cs5535_gpio_isset(अचिन्हित offset, अचिन्हित पूर्णांक reg);
पूर्णांक cs5535_gpio_set_irq(अचिन्हित group, अचिन्हित irq);
व्योम cs5535_gpio_setup_event(अचिन्हित offset, पूर्णांक pair, पूर्णांक pme);

/* MFGPTs */

#घोषणा MFGPT_MAX_TIMERS	8
#घोषणा MFGPT_TIMER_ANY		(-1)

#घोषणा MFGPT_DOMAIN_WORKING	1
#घोषणा MFGPT_DOMAIN_STANDBY	2
#घोषणा MFGPT_DOMAIN_ANY	(MFGPT_DOMAIN_WORKING | MFGPT_DOMAIN_STANDBY)

#घोषणा MFGPT_CMP1		0
#घोषणा MFGPT_CMP2		1

#घोषणा MFGPT_EVENT_IRQ		0
#घोषणा MFGPT_EVENT_NMI		1
#घोषणा MFGPT_EVENT_RESET	3

#घोषणा MFGPT_REG_CMP1		0
#घोषणा MFGPT_REG_CMP2		2
#घोषणा MFGPT_REG_COUNTER	4
#घोषणा MFGPT_REG_SETUP		6

#घोषणा MFGPT_SETUP_CNTEN	(1 << 15)
#घोषणा MFGPT_SETUP_CMP2	(1 << 14)
#घोषणा MFGPT_SETUP_CMP1	(1 << 13)
#घोषणा MFGPT_SETUP_SETUP	(1 << 12)
#घोषणा MFGPT_SETUP_STOPEN	(1 << 11)
#घोषणा MFGPT_SETUP_EXTEN	(1 << 10)
#घोषणा MFGPT_SETUP_REVEN	(1 << 5)
#घोषणा MFGPT_SETUP_CLKSEL	(1 << 4)

काष्ठा cs5535_mfgpt_समयr;

बाह्य uपूर्णांक16_t cs5535_mfgpt_पढ़ो(काष्ठा cs5535_mfgpt_समयr *समयr,
		uपूर्णांक16_t reg);
बाह्य व्योम cs5535_mfgpt_ग_लिखो(काष्ठा cs5535_mfgpt_समयr *समयr, uपूर्णांक16_t reg,
		uपूर्णांक16_t value);

बाह्य पूर्णांक cs5535_mfgpt_toggle_event(काष्ठा cs5535_mfgpt_समयr *समयr, पूर्णांक cmp,
		पूर्णांक event, पूर्णांक enable);
बाह्य पूर्णांक cs5535_mfgpt_set_irq(काष्ठा cs5535_mfgpt_समयr *समयr, पूर्णांक cmp,
		पूर्णांक *irq, पूर्णांक enable);
बाह्य काष्ठा cs5535_mfgpt_समयr *cs5535_mfgpt_alloc_समयr(पूर्णांक समयr,
		पूर्णांक करोमुख्य);
बाह्य व्योम cs5535_mfgpt_मुक्त_समयr(काष्ठा cs5535_mfgpt_समयr *समयr);

अटल अंतरभूत पूर्णांक cs5535_mfgpt_setup_irq(काष्ठा cs5535_mfgpt_समयr *समयr,
		पूर्णांक cmp, पूर्णांक *irq)
अणु
	वापस cs5535_mfgpt_set_irq(समयr, cmp, irq, 1);
पूर्ण

अटल अंतरभूत पूर्णांक cs5535_mfgpt_release_irq(काष्ठा cs5535_mfgpt_समयr *समयr,
		पूर्णांक cmp, पूर्णांक *irq)
अणु
	वापस cs5535_mfgpt_set_irq(समयr, cmp, irq, 0);
पूर्ण

#पूर्ण_अगर
