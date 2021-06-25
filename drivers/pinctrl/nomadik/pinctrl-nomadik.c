<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic GPIO driver क्रम logic cells found in the Nomadik SoC
 *
 * Copyright (C) 2008,2009 STMicroelectronics
 * Copyright (C) 2009 Alessandro Rubini <rubini@unipv.it>
 *   Rewritten based on work by Prafulla WADASKAR <prafulla.wadaskar@st.com>
 * Copyright (C) 2011-2013 Linus Walleij <linus.walleij@linaro.org>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/bitops.h>
#समावेश <linux/pinctrl/machine.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/pinconf.h>
/* Since we request GPIOs from ourself */
#समावेश <linux/pinctrl/consumer.h>
#समावेश "pinctrl-nomadik.h"
#समावेश "../core.h"
#समावेश "../pinctrl-utils.h"

/*
 * The GPIO module in the Nomadik family of Systems-on-Chip is an
 * AMBA device, managing 32 pins and alternate functions.  The logic block
 * is currently used in the Nomadik and ux500.
 *
 * Symbols in this file are called "nmk_gpio" क्रम "nomadik gpio"
 */

/*
 * pin configurations are represented by 32-bit पूर्णांकegers:
 *
 *	bit  0.. 8 - Pin Number (512 Pins Maximum)
 *	bit  9..10 - Alternate Function Selection
 *	bit 11..12 - Pull up/करोwn state
 *	bit     13 - Sleep mode behaviour
 *	bit     14 - Direction
 *	bit     15 - Value (अगर output)
 *	bit 16..18 - SLPM pull up/करोwn state
 *	bit 19..20 - SLPM direction
 *	bit 21..22 - SLPM Value (अगर output)
 *	bit 23..25 - PDIS value (अगर input)
 *	bit	26 - Gpio mode
 *	bit	27 - Sleep mode
 *
 * to facilitate the definition, the following macros are provided
 *
 * PIN_CFG_DEFAULT - शेष config (0):
 *		     pull up/करोwn = disabled
 *		     sleep mode = input/wakeup
 *		     direction = input
 *		     value = low
 *		     SLPM direction = same as normal
 *		     SLPM pull = same as normal
 *		     SLPM value = same as normal
 *
 * PIN_CFG	   - शेष config with alternate function
 */

प्रकार अचिन्हित दीर्घ pin_cfg_t;

#घोषणा PIN_NUM_MASK		0x1ff
#घोषणा PIN_NUM(x)		((x) & PIN_NUM_MASK)

#घोषणा PIN_ALT_SHIFT		9
#घोषणा PIN_ALT_MASK		(0x3 << PIN_ALT_SHIFT)
#घोषणा PIN_ALT(x)		(((x) & PIN_ALT_MASK) >> PIN_ALT_SHIFT)
#घोषणा PIN_GPIO		(NMK_GPIO_ALT_GPIO << PIN_ALT_SHIFT)
#घोषणा PIN_ALT_A		(NMK_GPIO_ALT_A << PIN_ALT_SHIFT)
#घोषणा PIN_ALT_B		(NMK_GPIO_ALT_B << PIN_ALT_SHIFT)
#घोषणा PIN_ALT_C		(NMK_GPIO_ALT_C << PIN_ALT_SHIFT)

#घोषणा PIN_PULL_SHIFT		11
#घोषणा PIN_PULL_MASK		(0x3 << PIN_PULL_SHIFT)
#घोषणा PIN_PULL(x)		(((x) & PIN_PULL_MASK) >> PIN_PULL_SHIFT)
#घोषणा PIN_PULL_NONE		(NMK_GPIO_PULL_NONE << PIN_PULL_SHIFT)
#घोषणा PIN_PULL_UP		(NMK_GPIO_PULL_UP << PIN_PULL_SHIFT)
#घोषणा PIN_PULL_DOWN		(NMK_GPIO_PULL_DOWN << PIN_PULL_SHIFT)

#घोषणा PIN_SLPM_SHIFT		13
#घोषणा PIN_SLPM_MASK		(0x1 << PIN_SLPM_SHIFT)
#घोषणा PIN_SLPM(x)		(((x) & PIN_SLPM_MASK) >> PIN_SLPM_SHIFT)
#घोषणा PIN_SLPM_MAKE_INPUT	(NMK_GPIO_SLPM_INPUT << PIN_SLPM_SHIFT)
#घोषणा PIN_SLPM_NOCHANGE	(NMK_GPIO_SLPM_NOCHANGE << PIN_SLPM_SHIFT)
/* These two replace the above in DB8500v2+ */
#घोषणा PIN_SLPM_WAKEUP_ENABLE	(NMK_GPIO_SLPM_WAKEUP_ENABLE << PIN_SLPM_SHIFT)
#घोषणा PIN_SLPM_WAKEUP_DISABLE	(NMK_GPIO_SLPM_WAKEUP_DISABLE << PIN_SLPM_SHIFT)
#घोषणा PIN_SLPM_USE_MUX_SETTINGS_IN_SLEEP PIN_SLPM_WAKEUP_DISABLE

#घोषणा PIN_SLPM_GPIO  PIN_SLPM_WAKEUP_ENABLE /* In SLPM, pin is a gpio */
#घोषणा PIN_SLPM_ALTFUNC PIN_SLPM_WAKEUP_DISABLE /* In SLPM, pin is altfunc */

#घोषणा PIN_सूची_SHIFT		14
#घोषणा PIN_सूची_MASK		(0x1 << PIN_सूची_SHIFT)
#घोषणा PIN_सूची(x)		(((x) & PIN_सूची_MASK) >> PIN_सूची_SHIFT)
#घोषणा PIN_सूची_INPUT		(0 << PIN_सूची_SHIFT)
#घोषणा PIN_सूची_OUTPUT		(1 << PIN_सूची_SHIFT)

#घोषणा PIN_VAL_SHIFT		15
#घोषणा PIN_VAL_MASK		(0x1 << PIN_VAL_SHIFT)
#घोषणा PIN_VAL(x)		(((x) & PIN_VAL_MASK) >> PIN_VAL_SHIFT)
#घोषणा PIN_VAL_LOW		(0 << PIN_VAL_SHIFT)
#घोषणा PIN_VAL_HIGH		(1 << PIN_VAL_SHIFT)

#घोषणा PIN_SLPM_PULL_SHIFT	16
#घोषणा PIN_SLPM_PULL_MASK	(0x7 << PIN_SLPM_PULL_SHIFT)
#घोषणा PIN_SLPM_PULL(x)	\
	(((x) & PIN_SLPM_PULL_MASK) >> PIN_SLPM_PULL_SHIFT)
#घोषणा PIN_SLPM_PULL_NONE	\
	((1 + NMK_GPIO_PULL_NONE) << PIN_SLPM_PULL_SHIFT)
#घोषणा PIN_SLPM_PULL_UP	\
	((1 + NMK_GPIO_PULL_UP) << PIN_SLPM_PULL_SHIFT)
#घोषणा PIN_SLPM_PULL_DOWN	\
	((1 + NMK_GPIO_PULL_DOWN) << PIN_SLPM_PULL_SHIFT)

#घोषणा PIN_SLPM_सूची_SHIFT	19
#घोषणा PIN_SLPM_सूची_MASK	(0x3 << PIN_SLPM_सूची_SHIFT)
#घोषणा PIN_SLPM_सूची(x)		\
	(((x) & PIN_SLPM_सूची_MASK) >> PIN_SLPM_सूची_SHIFT)
#घोषणा PIN_SLPM_सूची_INPUT	((1 + 0) << PIN_SLPM_सूची_SHIFT)
#घोषणा PIN_SLPM_सूची_OUTPUT	((1 + 1) << PIN_SLPM_सूची_SHIFT)

#घोषणा PIN_SLPM_VAL_SHIFT	21
#घोषणा PIN_SLPM_VAL_MASK	(0x3 << PIN_SLPM_VAL_SHIFT)
#घोषणा PIN_SLPM_VAL(x)		\
	(((x) & PIN_SLPM_VAL_MASK) >> PIN_SLPM_VAL_SHIFT)
#घोषणा PIN_SLPM_VAL_LOW	((1 + 0) << PIN_SLPM_VAL_SHIFT)
#घोषणा PIN_SLPM_VAL_HIGH	((1 + 1) << PIN_SLPM_VAL_SHIFT)

#घोषणा PIN_SLPM_PDIS_SHIFT		23
#घोषणा PIN_SLPM_PDIS_MASK		(0x3 << PIN_SLPM_PDIS_SHIFT)
#घोषणा PIN_SLPM_PDIS(x)	\
	(((x) & PIN_SLPM_PDIS_MASK) >> PIN_SLPM_PDIS_SHIFT)
#घोषणा PIN_SLPM_PDIS_NO_CHANGE		(0 << PIN_SLPM_PDIS_SHIFT)
#घोषणा PIN_SLPM_PDIS_DISABLED		(1 << PIN_SLPM_PDIS_SHIFT)
#घोषणा PIN_SLPM_PDIS_ENABLED		(2 << PIN_SLPM_PDIS_SHIFT)

#घोषणा PIN_LOWEMI_SHIFT	25
#घोषणा PIN_LOWEMI_MASK		(0x1 << PIN_LOWEMI_SHIFT)
#घोषणा PIN_LOWEMI(x)		(((x) & PIN_LOWEMI_MASK) >> PIN_LOWEMI_SHIFT)
#घोषणा PIN_LOWEMI_DISABLED	(0 << PIN_LOWEMI_SHIFT)
#घोषणा PIN_LOWEMI_ENABLED	(1 << PIN_LOWEMI_SHIFT)

#घोषणा PIN_GPIOMODE_SHIFT	26
#घोषणा PIN_GPIOMODE_MASK	(0x1 << PIN_GPIOMODE_SHIFT)
#घोषणा PIN_GPIOMODE(x)		(((x) & PIN_GPIOMODE_MASK) >> PIN_GPIOMODE_SHIFT)
#घोषणा PIN_GPIOMODE_DISABLED	(0 << PIN_GPIOMODE_SHIFT)
#घोषणा PIN_GPIOMODE_ENABLED	(1 << PIN_GPIOMODE_SHIFT)

#घोषणा PIN_SLEEPMODE_SHIFT	27
#घोषणा PIN_SLEEPMODE_MASK	(0x1 << PIN_SLEEPMODE_SHIFT)
#घोषणा PIN_SLEEPMODE(x)	(((x) & PIN_SLEEPMODE_MASK) >> PIN_SLEEPMODE_SHIFT)
#घोषणा PIN_SLEEPMODE_DISABLED	(0 << PIN_SLEEPMODE_SHIFT)
#घोषणा PIN_SLEEPMODE_ENABLED	(1 << PIN_SLEEPMODE_SHIFT)


/* Shortcuts.  Use these instead of separate सूची, PULL, and VAL.  */
#घोषणा PIN_INPUT_PULLDOWN	(PIN_सूची_INPUT | PIN_PULL_DOWN)
#घोषणा PIN_INPUT_PULLUP	(PIN_सूची_INPUT | PIN_PULL_UP)
#घोषणा PIN_INPUT_NOPULL	(PIN_सूची_INPUT | PIN_PULL_NONE)
#घोषणा PIN_OUTPUT_LOW		(PIN_सूची_OUTPUT | PIN_VAL_LOW)
#घोषणा PIN_OUTPUT_HIGH		(PIN_सूची_OUTPUT | PIN_VAL_HIGH)

#घोषणा PIN_SLPM_INPUT_PULLDOWN	(PIN_SLPM_सूची_INPUT | PIN_SLPM_PULL_DOWN)
#घोषणा PIN_SLPM_INPUT_PULLUP	(PIN_SLPM_सूची_INPUT | PIN_SLPM_PULL_UP)
#घोषणा PIN_SLPM_INPUT_NOPULL	(PIN_SLPM_सूची_INPUT | PIN_SLPM_PULL_NONE)
#घोषणा PIN_SLPM_OUTPUT_LOW	(PIN_SLPM_सूची_OUTPUT | PIN_SLPM_VAL_LOW)
#घोषणा PIN_SLPM_OUTPUT_HIGH	(PIN_SLPM_सूची_OUTPUT | PIN_SLPM_VAL_HIGH)

#घोषणा PIN_CFG_DEFAULT		(0)

#घोषणा PIN_CFG(num, alt)		\
	(PIN_CFG_DEFAULT |\
	 (PIN_NUM(num) | PIN_##alt))

#घोषणा PIN_CFG_INPUT(num, alt, pull)		\
	(PIN_CFG_DEFAULT |\
	 (PIN_NUM(num) | PIN_##alt | PIN_INPUT_##pull))

#घोषणा PIN_CFG_OUTPUT(num, alt, val)		\
	(PIN_CFG_DEFAULT |\
	 (PIN_NUM(num) | PIN_##alt | PIN_OUTPUT_##val))

/*
 * "nmk_gpio" and "NMK_GPIO" stand क्रम "Nomadik GPIO", leaving
 * the "gpio" namespace क्रम generic and cross-machine functions
 */

#घोषणा GPIO_BLOCK_SHIFT 5
#घोषणा NMK_GPIO_PER_CHIP (1 << GPIO_BLOCK_SHIFT)
#घोषणा NMK_MAX_BANKS DIV_ROUND_UP(512, NMK_GPIO_PER_CHIP)

/* Register in the logic block */
#घोषणा NMK_GPIO_DAT	0x00
#घोषणा NMK_GPIO_DATS	0x04
#घोषणा NMK_GPIO_DATC	0x08
#घोषणा NMK_GPIO_PDIS	0x0c
#घोषणा NMK_GPIO_सूची	0x10
#घोषणा NMK_GPIO_सूचीS	0x14
#घोषणा NMK_GPIO_सूचीC	0x18
#घोषणा NMK_GPIO_SLPC	0x1c
#घोषणा NMK_GPIO_AFSLA	0x20
#घोषणा NMK_GPIO_AFSLB	0x24
#घोषणा NMK_GPIO_LOWEMI	0x28

#घोषणा NMK_GPIO_RIMSC	0x40
#घोषणा NMK_GPIO_FIMSC	0x44
#घोषणा NMK_GPIO_IS	0x48
#घोषणा NMK_GPIO_IC	0x4c
#घोषणा NMK_GPIO_RWIMSC	0x50
#घोषणा NMK_GPIO_FWIMSC	0x54
#घोषणा NMK_GPIO_WKS	0x58
/* These appear in DB8540 and later ASICs */
#घोषणा NMK_GPIO_EDGELEVEL 0x5C
#घोषणा NMK_GPIO_LEVEL	0x60


/* Pull up/करोwn values */
क्रमागत nmk_gpio_pull अणु
	NMK_GPIO_PULL_NONE,
	NMK_GPIO_PULL_UP,
	NMK_GPIO_PULL_DOWN,
पूर्ण;

/* Sleep mode */
क्रमागत nmk_gpio_slpm अणु
	NMK_GPIO_SLPM_INPUT,
	NMK_GPIO_SLPM_WAKEUP_ENABLE = NMK_GPIO_SLPM_INPUT,
	NMK_GPIO_SLPM_NOCHANGE,
	NMK_GPIO_SLPM_WAKEUP_DISABLE = NMK_GPIO_SLPM_NOCHANGE,
पूर्ण;

काष्ठा nmk_gpio_chip अणु
	काष्ठा gpio_chip chip;
	काष्ठा irq_chip irqchip;
	व्योम __iomem *addr;
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक bank;
	व्योम (*set_ioक्रमce)(bool enable);
	spinlock_t lock;
	bool sleepmode;
	/* Keep track of configured edges */
	u32 edge_rising;
	u32 edge_falling;
	u32 real_wake;
	u32 rwimsc;
	u32 fwimsc;
	u32 rimsc;
	u32 fimsc;
	u32 pull_up;
	u32 lowemi;
पूर्ण;

/**
 * काष्ठा nmk_pinctrl - state container क्रम the Nomadik pin controller
 * @dev: containing device poपूर्णांकer
 * @pctl: corresponding pin controller device
 * @soc: SoC data क्रम this specअगरic chip
 * @prcm_base: PRCM रेजिस्टर range भव base
 */
काष्ठा nmk_pinctrl अणु
	काष्ठा device *dev;
	काष्ठा pinctrl_dev *pctl;
	स्थिर काष्ठा nmk_pinctrl_soc_data *soc;
	व्योम __iomem *prcm_base;
पूर्ण;

अटल काष्ठा nmk_gpio_chip *nmk_gpio_chips[NMK_MAX_BANKS];

अटल DEFINE_SPINLOCK(nmk_gpio_slpm_lock);

#घोषणा NUM_BANKS ARRAY_SIZE(nmk_gpio_chips)

अटल व्योम __nmk_gpio_set_mode(काष्ठा nmk_gpio_chip *nmk_chip,
				अचिन्हित offset, पूर्णांक gpio_mode)
अणु
	u32 afunc, bfunc;

	afunc = पढ़ोl(nmk_chip->addr + NMK_GPIO_AFSLA) & ~BIT(offset);
	bfunc = पढ़ोl(nmk_chip->addr + NMK_GPIO_AFSLB) & ~BIT(offset);
	अगर (gpio_mode & NMK_GPIO_ALT_A)
		afunc |= BIT(offset);
	अगर (gpio_mode & NMK_GPIO_ALT_B)
		bfunc |= BIT(offset);
	ग_लिखोl(afunc, nmk_chip->addr + NMK_GPIO_AFSLA);
	ग_लिखोl(bfunc, nmk_chip->addr + NMK_GPIO_AFSLB);
पूर्ण

अटल व्योम __nmk_gpio_set_slpm(काष्ठा nmk_gpio_chip *nmk_chip,
				अचिन्हित offset, क्रमागत nmk_gpio_slpm mode)
अणु
	u32 slpm;

	slpm = पढ़ोl(nmk_chip->addr + NMK_GPIO_SLPC);
	अगर (mode == NMK_GPIO_SLPM_NOCHANGE)
		slpm |= BIT(offset);
	अन्यथा
		slpm &= ~BIT(offset);
	ग_लिखोl(slpm, nmk_chip->addr + NMK_GPIO_SLPC);
पूर्ण

अटल व्योम __nmk_gpio_set_pull(काष्ठा nmk_gpio_chip *nmk_chip,
				अचिन्हित offset, क्रमागत nmk_gpio_pull pull)
अणु
	u32 pdis;

	pdis = पढ़ोl(nmk_chip->addr + NMK_GPIO_PDIS);
	अगर (pull == NMK_GPIO_PULL_NONE) अणु
		pdis |= BIT(offset);
		nmk_chip->pull_up &= ~BIT(offset);
	पूर्ण अन्यथा अणु
		pdis &= ~BIT(offset);
	पूर्ण

	ग_लिखोl(pdis, nmk_chip->addr + NMK_GPIO_PDIS);

	अगर (pull == NMK_GPIO_PULL_UP) अणु
		nmk_chip->pull_up |= BIT(offset);
		ग_लिखोl(BIT(offset), nmk_chip->addr + NMK_GPIO_DATS);
	पूर्ण अन्यथा अगर (pull == NMK_GPIO_PULL_DOWN) अणु
		nmk_chip->pull_up &= ~BIT(offset);
		ग_लिखोl(BIT(offset), nmk_chip->addr + NMK_GPIO_DATC);
	पूर्ण
पूर्ण

अटल व्योम __nmk_gpio_set_lowemi(काष्ठा nmk_gpio_chip *nmk_chip,
				  अचिन्हित offset, bool lowemi)
अणु
	bool enabled = nmk_chip->lowemi & BIT(offset);

	अगर (lowemi == enabled)
		वापस;

	अगर (lowemi)
		nmk_chip->lowemi |= BIT(offset);
	अन्यथा
		nmk_chip->lowemi &= ~BIT(offset);

	ग_लिखोl_relaxed(nmk_chip->lowemi,
		       nmk_chip->addr + NMK_GPIO_LOWEMI);
पूर्ण

अटल व्योम __nmk_gpio_make_input(काष्ठा nmk_gpio_chip *nmk_chip,
				  अचिन्हित offset)
अणु
	ग_लिखोl(BIT(offset), nmk_chip->addr + NMK_GPIO_सूचीC);
पूर्ण

अटल व्योम __nmk_gpio_set_output(काष्ठा nmk_gpio_chip *nmk_chip,
				  अचिन्हित offset, पूर्णांक val)
अणु
	अगर (val)
		ग_लिखोl(BIT(offset), nmk_chip->addr + NMK_GPIO_DATS);
	अन्यथा
		ग_लिखोl(BIT(offset), nmk_chip->addr + NMK_GPIO_DATC);
पूर्ण

अटल व्योम __nmk_gpio_make_output(काष्ठा nmk_gpio_chip *nmk_chip,
				  अचिन्हित offset, पूर्णांक val)
अणु
	ग_लिखोl(BIT(offset), nmk_chip->addr + NMK_GPIO_सूचीS);
	__nmk_gpio_set_output(nmk_chip, offset, val);
पूर्ण

अटल व्योम __nmk_gpio_set_mode_safe(काष्ठा nmk_gpio_chip *nmk_chip,
				     अचिन्हित offset, पूर्णांक gpio_mode,
				     bool glitch)
अणु
	u32 rwimsc = nmk_chip->rwimsc;
	u32 fwimsc = nmk_chip->fwimsc;

	अगर (glitch && nmk_chip->set_ioक्रमce) अणु
		u32 bit = BIT(offset);

		/* Prevent spurious wakeups */
		ग_लिखोl(rwimsc & ~bit, nmk_chip->addr + NMK_GPIO_RWIMSC);
		ग_लिखोl(fwimsc & ~bit, nmk_chip->addr + NMK_GPIO_FWIMSC);

		nmk_chip->set_ioक्रमce(true);
	पूर्ण

	__nmk_gpio_set_mode(nmk_chip, offset, gpio_mode);

	अगर (glitch && nmk_chip->set_ioक्रमce) अणु
		nmk_chip->set_ioक्रमce(false);

		ग_लिखोl(rwimsc, nmk_chip->addr + NMK_GPIO_RWIMSC);
		ग_लिखोl(fwimsc, nmk_chip->addr + NMK_GPIO_FWIMSC);
	पूर्ण
पूर्ण

अटल व्योम
nmk_gpio_disable_lazy_irq(काष्ठा nmk_gpio_chip *nmk_chip, अचिन्हित offset)
अणु
	u32 falling = nmk_chip->fimsc & BIT(offset);
	u32 rising = nmk_chip->rimsc & BIT(offset);
	पूर्णांक gpio = nmk_chip->chip.base + offset;
	पूर्णांक irq = irq_find_mapping(nmk_chip->chip.irq.करोमुख्य, offset);
	काष्ठा irq_data *d = irq_get_irq_data(irq);

	अगर (!rising && !falling)
		वापस;

	अगर (!d || !irqd_irq_disabled(d))
		वापस;

	अगर (rising) अणु
		nmk_chip->rimsc &= ~BIT(offset);
		ग_लिखोl_relaxed(nmk_chip->rimsc,
			       nmk_chip->addr + NMK_GPIO_RIMSC);
	पूर्ण

	अगर (falling) अणु
		nmk_chip->fimsc &= ~BIT(offset);
		ग_लिखोl_relaxed(nmk_chip->fimsc,
			       nmk_chip->addr + NMK_GPIO_FIMSC);
	पूर्ण

	dev_dbg(nmk_chip->chip.parent, "%d: clearing interrupt mask\n", gpio);
पूर्ण

अटल व्योम nmk_ग_लिखो_masked(व्योम __iomem *reg, u32 mask, u32 value)
अणु
	u32 val;

	val = पढ़ोl(reg);
	val = ((val & ~mask) | (value & mask));
	ग_लिखोl(val, reg);
पूर्ण

अटल व्योम nmk_prcm_altcx_set_mode(काष्ठा nmk_pinctrl *npct,
	अचिन्हित offset, अचिन्हित alt_num)
अणु
	पूर्णांक i;
	u16 reg;
	u8 bit;
	u8 alt_index;
	स्थिर काष्ठा prcm_gpiocr_altcx_pin_desc *pin_desc;
	स्थिर u16 *gpiocr_regs;

	अगर (!npct->prcm_base)
		वापस;

	अगर (alt_num > PRCM_IDX_GPIOCR_ALTC_MAX) अणु
		dev_err(npct->dev, "PRCM GPIOCR: alternate-C%i is invalid\n",
			alt_num);
		वापस;
	पूर्ण

	क्रम (i = 0 ; i < npct->soc->npins_altcx ; i++) अणु
		अगर (npct->soc->altcx_pins[i].pin == offset)
			अवरोध;
	पूर्ण
	अगर (i == npct->soc->npins_altcx) अणु
		dev_dbg(npct->dev, "PRCM GPIOCR: pin %i is not found\n",
			offset);
		वापस;
	पूर्ण

	pin_desc = npct->soc->altcx_pins + i;
	gpiocr_regs = npct->soc->prcm_gpiocr_रेजिस्टरs;

	/*
	 * If alt_num is शून्य, just clear current ALTCx selection
	 * to make sure we come back to a pure ALTC selection
	 */
	अगर (!alt_num) अणु
		क्रम (i = 0 ; i < PRCM_IDX_GPIOCR_ALTC_MAX ; i++) अणु
			अगर (pin_desc->altcx[i].used == true) अणु
				reg = gpiocr_regs[pin_desc->altcx[i].reg_index];
				bit = pin_desc->altcx[i].control_bit;
				अगर (पढ़ोl(npct->prcm_base + reg) & BIT(bit)) अणु
					nmk_ग_लिखो_masked(npct->prcm_base + reg, BIT(bit), 0);
					dev_dbg(npct->dev,
						"PRCM GPIOCR: pin %i: alternate-C%i has been disabled\n",
						offset, i+1);
				पूर्ण
			पूर्ण
		पूर्ण
		वापस;
	पूर्ण

	alt_index = alt_num - 1;
	अगर (pin_desc->altcx[alt_index].used == false) अणु
		dev_warn(npct->dev,
			"PRCM GPIOCR: pin %i: alternate-C%i does not exist\n",
			offset, alt_num);
		वापस;
	पूर्ण

	/*
	 * Check अगर any other ALTCx functions are activated on this pin
	 * and disable it first.
	 */
	क्रम (i = 0 ; i < PRCM_IDX_GPIOCR_ALTC_MAX ; i++) अणु
		अगर (i == alt_index)
			जारी;
		अगर (pin_desc->altcx[i].used == true) अणु
			reg = gpiocr_regs[pin_desc->altcx[i].reg_index];
			bit = pin_desc->altcx[i].control_bit;
			अगर (पढ़ोl(npct->prcm_base + reg) & BIT(bit)) अणु
				nmk_ग_लिखो_masked(npct->prcm_base + reg, BIT(bit), 0);
				dev_dbg(npct->dev,
					"PRCM GPIOCR: pin %i: alternate-C%i has been disabled\n",
					offset, i+1);
			पूर्ण
		पूर्ण
	पूर्ण

	reg = gpiocr_regs[pin_desc->altcx[alt_index].reg_index];
	bit = pin_desc->altcx[alt_index].control_bit;
	dev_dbg(npct->dev, "PRCM GPIOCR: pin %i: alternate-C%i has been selected\n",
		offset, alt_index+1);
	nmk_ग_लिखो_masked(npct->prcm_base + reg, BIT(bit), BIT(bit));
पूर्ण

/*
 * Safe sequence used to चयन IOs between GPIO and Alternate-C mode:
 *  - Save SLPM रेजिस्टरs
 *  - Set SLPM=0 क्रम the IOs you want to चयन and others to 1
 *  - Configure the GPIO रेजिस्टरs क्रम the IOs that are being चयनed
 *  - Set IOFORCE=1
 *  - Modअगरy the AFLSA/B रेजिस्टरs क्रम the IOs that are being चयनed
 *  - Set IOFORCE=0
 *  - Restore SLPM रेजिस्टरs
 *  - Any spurious wake up event during चयन sequence to be ignored and
 *    cleared
 */
अटल व्योम nmk_gpio_glitch_slpm_init(अचिन्हित पूर्णांक *slpm)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_BANKS; i++) अणु
		काष्ठा nmk_gpio_chip *chip = nmk_gpio_chips[i];
		अचिन्हित पूर्णांक temp = slpm[i];

		अगर (!chip)
			अवरोध;

		clk_enable(chip->clk);

		slpm[i] = पढ़ोl(chip->addr + NMK_GPIO_SLPC);
		ग_लिखोl(temp, chip->addr + NMK_GPIO_SLPC);
	पूर्ण
पूर्ण

अटल व्योम nmk_gpio_glitch_slpm_restore(अचिन्हित पूर्णांक *slpm)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_BANKS; i++) अणु
		काष्ठा nmk_gpio_chip *chip = nmk_gpio_chips[i];

		अगर (!chip)
			अवरोध;

		ग_लिखोl(slpm[i], chip->addr + NMK_GPIO_SLPC);

		clk_disable(chip->clk);
	पूर्ण
पूर्ण

अटल पूर्णांक __maybe_unused nmk_prcm_gpiocr_get_mode(काष्ठा pinctrl_dev *pctldev, पूर्णांक gpio)
अणु
	पूर्णांक i;
	u16 reg;
	u8 bit;
	काष्ठा nmk_pinctrl *npct = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा prcm_gpiocr_altcx_pin_desc *pin_desc;
	स्थिर u16 *gpiocr_regs;

	अगर (!npct->prcm_base)
		वापस NMK_GPIO_ALT_C;

	क्रम (i = 0; i < npct->soc->npins_altcx; i++) अणु
		अगर (npct->soc->altcx_pins[i].pin == gpio)
			अवरोध;
	पूर्ण
	अगर (i == npct->soc->npins_altcx)
		वापस NMK_GPIO_ALT_C;

	pin_desc = npct->soc->altcx_pins + i;
	gpiocr_regs = npct->soc->prcm_gpiocr_रेजिस्टरs;
	क्रम (i = 0; i < PRCM_IDX_GPIOCR_ALTC_MAX; i++) अणु
		अगर (pin_desc->altcx[i].used == true) अणु
			reg = gpiocr_regs[pin_desc->altcx[i].reg_index];
			bit = pin_desc->altcx[i].control_bit;
			अगर (पढ़ोl(npct->prcm_base + reg) & BIT(bit))
				वापस NMK_GPIO_ALT_C+i+1;
		पूर्ण
	पूर्ण
	वापस NMK_GPIO_ALT_C;
पूर्ण

/* IRQ functions */

अटल व्योम nmk_gpio_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(d);
	काष्ठा nmk_gpio_chip *nmk_chip = gpiochip_get_data(chip);

	clk_enable(nmk_chip->clk);
	ग_लिखोl(BIT(d->hwirq), nmk_chip->addr + NMK_GPIO_IC);
	clk_disable(nmk_chip->clk);
पूर्ण

क्रमागत nmk_gpio_irq_type अणु
	NORMAL,
	WAKE,
पूर्ण;

अटल व्योम __nmk_gpio_irq_modअगरy(काष्ठा nmk_gpio_chip *nmk_chip,
				  पूर्णांक offset, क्रमागत nmk_gpio_irq_type which,
				  bool enable)
अणु
	u32 *rimscval;
	u32 *fimscval;
	u32 rimscreg;
	u32 fimscreg;

	अगर (which == NORMAL) अणु
		rimscreg = NMK_GPIO_RIMSC;
		fimscreg = NMK_GPIO_FIMSC;
		rimscval = &nmk_chip->rimsc;
		fimscval = &nmk_chip->fimsc;
	पूर्ण अन्यथा  अणु
		rimscreg = NMK_GPIO_RWIMSC;
		fimscreg = NMK_GPIO_FWIMSC;
		rimscval = &nmk_chip->rwimsc;
		fimscval = &nmk_chip->fwimsc;
	पूर्ण

	/* we must inभागidually set/clear the two edges */
	अगर (nmk_chip->edge_rising & BIT(offset)) अणु
		अगर (enable)
			*rimscval |= BIT(offset);
		अन्यथा
			*rimscval &= ~BIT(offset);
		ग_लिखोl(*rimscval, nmk_chip->addr + rimscreg);
	पूर्ण
	अगर (nmk_chip->edge_falling & BIT(offset)) अणु
		अगर (enable)
			*fimscval |= BIT(offset);
		अन्यथा
			*fimscval &= ~BIT(offset);
		ग_लिखोl(*fimscval, nmk_chip->addr + fimscreg);
	पूर्ण
पूर्ण

अटल व्योम __nmk_gpio_set_wake(काष्ठा nmk_gpio_chip *nmk_chip,
				पूर्णांक offset, bool on)
अणु
	/*
	 * Ensure WAKEUP_ENABLE is on.  No need to disable it अगर wakeup is
	 * disabled, since setting SLPM to 1 increases घातer consumption, and
	 * wakeup is anyhow controlled by the RIMSC and FIMSC रेजिस्टरs.
	 */
	अगर (nmk_chip->sleepmode && on) अणु
		__nmk_gpio_set_slpm(nmk_chip, offset,
				    NMK_GPIO_SLPM_WAKEUP_ENABLE);
	पूर्ण

	__nmk_gpio_irq_modअगरy(nmk_chip, offset, WAKE, on);
पूर्ण

अटल पूर्णांक nmk_gpio_irq_maskunmask(काष्ठा irq_data *d, bool enable)
अणु
	काष्ठा nmk_gpio_chip *nmk_chip;
	अचिन्हित दीर्घ flags;

	nmk_chip = irq_data_get_irq_chip_data(d);
	अगर (!nmk_chip)
		वापस -EINVAL;

	clk_enable(nmk_chip->clk);
	spin_lock_irqsave(&nmk_gpio_slpm_lock, flags);
	spin_lock(&nmk_chip->lock);

	__nmk_gpio_irq_modअगरy(nmk_chip, d->hwirq, NORMAL, enable);

	अगर (!(nmk_chip->real_wake & BIT(d->hwirq)))
		__nmk_gpio_set_wake(nmk_chip, d->hwirq, enable);

	spin_unlock(&nmk_chip->lock);
	spin_unlock_irqrestore(&nmk_gpio_slpm_lock, flags);
	clk_disable(nmk_chip->clk);

	वापस 0;
पूर्ण

अटल व्योम nmk_gpio_irq_mask(काष्ठा irq_data *d)
अणु
	nmk_gpio_irq_maskunmask(d, false);
पूर्ण

अटल व्योम nmk_gpio_irq_unmask(काष्ठा irq_data *d)
अणु
	nmk_gpio_irq_maskunmask(d, true);
पूर्ण

अटल पूर्णांक nmk_gpio_irq_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक on)
अणु
	काष्ठा nmk_gpio_chip *nmk_chip;
	अचिन्हित दीर्घ flags;

	nmk_chip = irq_data_get_irq_chip_data(d);
	अगर (!nmk_chip)
		वापस -EINVAL;

	clk_enable(nmk_chip->clk);
	spin_lock_irqsave(&nmk_gpio_slpm_lock, flags);
	spin_lock(&nmk_chip->lock);

	अगर (irqd_irq_disabled(d))
		__nmk_gpio_set_wake(nmk_chip, d->hwirq, on);

	अगर (on)
		nmk_chip->real_wake |= BIT(d->hwirq);
	अन्यथा
		nmk_chip->real_wake &= ~BIT(d->hwirq);

	spin_unlock(&nmk_chip->lock);
	spin_unlock_irqrestore(&nmk_gpio_slpm_lock, flags);
	clk_disable(nmk_chip->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक nmk_gpio_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	bool enabled = !irqd_irq_disabled(d);
	bool wake = irqd_is_wakeup_set(d);
	काष्ठा nmk_gpio_chip *nmk_chip;
	अचिन्हित दीर्घ flags;

	nmk_chip = irq_data_get_irq_chip_data(d);
	अगर (!nmk_chip)
		वापस -EINVAL;
	अगर (type & IRQ_TYPE_LEVEL_HIGH)
		वापस -EINVAL;
	अगर (type & IRQ_TYPE_LEVEL_LOW)
		वापस -EINVAL;

	clk_enable(nmk_chip->clk);
	spin_lock_irqsave(&nmk_chip->lock, flags);

	अगर (enabled)
		__nmk_gpio_irq_modअगरy(nmk_chip, d->hwirq, NORMAL, false);

	अगर (enabled || wake)
		__nmk_gpio_irq_modअगरy(nmk_chip, d->hwirq, WAKE, false);

	nmk_chip->edge_rising &= ~BIT(d->hwirq);
	अगर (type & IRQ_TYPE_EDGE_RISING)
		nmk_chip->edge_rising |= BIT(d->hwirq);

	nmk_chip->edge_falling &= ~BIT(d->hwirq);
	अगर (type & IRQ_TYPE_EDGE_FALLING)
		nmk_chip->edge_falling |= BIT(d->hwirq);

	अगर (enabled)
		__nmk_gpio_irq_modअगरy(nmk_chip, d->hwirq, NORMAL, true);

	अगर (enabled || wake)
		__nmk_gpio_irq_modअगरy(nmk_chip, d->hwirq, WAKE, true);

	spin_unlock_irqrestore(&nmk_chip->lock, flags);
	clk_disable(nmk_chip->clk);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक nmk_gpio_irq_startup(काष्ठा irq_data *d)
अणु
	काष्ठा nmk_gpio_chip *nmk_chip = irq_data_get_irq_chip_data(d);

	clk_enable(nmk_chip->clk);
	nmk_gpio_irq_unmask(d);
	वापस 0;
पूर्ण

अटल व्योम nmk_gpio_irq_shutकरोwn(काष्ठा irq_data *d)
अणु
	काष्ठा nmk_gpio_chip *nmk_chip = irq_data_get_irq_chip_data(d);

	nmk_gpio_irq_mask(d);
	clk_disable(nmk_chip->clk);
पूर्ण

अटल व्योम nmk_gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *host_chip = irq_desc_get_chip(desc);
	काष्ठा gpio_chip *chip = irq_desc_get_handler_data(desc);
	काष्ठा nmk_gpio_chip *nmk_chip = gpiochip_get_data(chip);
	u32 status;

	chained_irq_enter(host_chip, desc);

	clk_enable(nmk_chip->clk);
	status = पढ़ोl(nmk_chip->addr + NMK_GPIO_IS);
	clk_disable(nmk_chip->clk);

	जबतक (status) अणु
		पूर्णांक bit = __ffs(status);

		generic_handle_irq(irq_find_mapping(chip->irq.करोमुख्य, bit));
		status &= ~BIT(bit);
	पूर्ण

	chained_irq_निकास(host_chip, desc);
पूर्ण

/* I/O Functions */

अटल पूर्णांक nmk_gpio_get_dir(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा nmk_gpio_chip *nmk_chip = gpiochip_get_data(chip);
	पूर्णांक dir;

	clk_enable(nmk_chip->clk);

	dir = पढ़ोl(nmk_chip->addr + NMK_GPIO_सूची) & BIT(offset);

	clk_disable(nmk_chip->clk);

	अगर (dir)
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक nmk_gpio_make_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा nmk_gpio_chip *nmk_chip = gpiochip_get_data(chip);

	clk_enable(nmk_chip->clk);

	ग_लिखोl(BIT(offset), nmk_chip->addr + NMK_GPIO_सूचीC);

	clk_disable(nmk_chip->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक nmk_gpio_get_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा nmk_gpio_chip *nmk_chip = gpiochip_get_data(chip);
	पूर्णांक value;

	clk_enable(nmk_chip->clk);

	value = !!(पढ़ोl(nmk_chip->addr + NMK_GPIO_DAT) & BIT(offset));

	clk_disable(nmk_chip->clk);

	वापस value;
पूर्ण

अटल व्योम nmk_gpio_set_output(काष्ठा gpio_chip *chip, अचिन्हित offset,
				पूर्णांक val)
अणु
	काष्ठा nmk_gpio_chip *nmk_chip = gpiochip_get_data(chip);

	clk_enable(nmk_chip->clk);

	__nmk_gpio_set_output(nmk_chip, offset, val);

	clk_disable(nmk_chip->clk);
पूर्ण

अटल पूर्णांक nmk_gpio_make_output(काष्ठा gpio_chip *chip, अचिन्हित offset,
				पूर्णांक val)
अणु
	काष्ठा nmk_gpio_chip *nmk_chip = gpiochip_get_data(chip);

	clk_enable(nmk_chip->clk);

	__nmk_gpio_make_output(nmk_chip, offset, val);

	clk_disable(nmk_chip->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक nmk_gpio_get_mode(काष्ठा nmk_gpio_chip *nmk_chip, पूर्णांक offset)
अणु
	u32 afunc, bfunc;

	clk_enable(nmk_chip->clk);

	afunc = पढ़ोl(nmk_chip->addr + NMK_GPIO_AFSLA) & BIT(offset);
	bfunc = पढ़ोl(nmk_chip->addr + NMK_GPIO_AFSLB) & BIT(offset);

	clk_disable(nmk_chip->clk);

	वापस (afunc ? NMK_GPIO_ALT_A : 0) | (bfunc ? NMK_GPIO_ALT_B : 0);
पूर्ण

#समावेश <linux/seq_file.h>

अटल व्योम nmk_gpio_dbg_show_one(काष्ठा seq_file *s,
	काष्ठा pinctrl_dev *pctldev, काष्ठा gpio_chip *chip,
	अचिन्हित offset, अचिन्हित gpio)
अणु
	स्थिर अक्षर *label = gpiochip_is_requested(chip, offset);
	काष्ठा nmk_gpio_chip *nmk_chip = gpiochip_get_data(chip);
	पूर्णांक mode;
	bool is_out;
	bool data_out;
	bool pull;
	स्थिर अक्षर *modes[] = अणु
		[NMK_GPIO_ALT_GPIO]	= "gpio",
		[NMK_GPIO_ALT_A]	= "altA",
		[NMK_GPIO_ALT_B]	= "altB",
		[NMK_GPIO_ALT_C]	= "altC",
		[NMK_GPIO_ALT_C+1]	= "altC1",
		[NMK_GPIO_ALT_C+2]	= "altC2",
		[NMK_GPIO_ALT_C+3]	= "altC3",
		[NMK_GPIO_ALT_C+4]	= "altC4",
	पूर्ण;

	clk_enable(nmk_chip->clk);
	is_out = !!(पढ़ोl(nmk_chip->addr + NMK_GPIO_सूची) & BIT(offset));
	pull = !(पढ़ोl(nmk_chip->addr + NMK_GPIO_PDIS) & BIT(offset));
	data_out = !!(पढ़ोl(nmk_chip->addr + NMK_GPIO_DAT) & BIT(offset));
	mode = nmk_gpio_get_mode(nmk_chip, offset);
	अगर ((mode == NMK_GPIO_ALT_C) && pctldev)
		mode = nmk_prcm_gpiocr_get_mode(pctldev, gpio);

	अगर (is_out) अणु
		seq_म_लिखो(s, " gpio-%-3d (%-20.20s) out %s           %s",
			   gpio,
			   label ?: "(none)",
			   data_out ? "hi" : "lo",
			   (mode < 0) ? "unknown" : modes[mode]);
	पूर्ण अन्यथा अणु
		पूर्णांक irq = chip->to_irq(chip, offset);
		स्थिर पूर्णांक pullidx = pull ? 1 : 0;
		पूर्णांक val;
		अटल स्थिर अक्षर * स्थिर pulls[] = अणु
			"none        ",
			"pull enabled",
		पूर्ण;

		seq_म_लिखो(s, " gpio-%-3d (%-20.20s) in  %s %s",
			   gpio,
			   label ?: "(none)",
			   pulls[pullidx],
			   (mode < 0) ? "unknown" : modes[mode]);

		val = nmk_gpio_get_input(chip, offset);
		seq_म_लिखो(s, " VAL %d", val);

		/*
		 * This races with request_irq(), set_irq_type(),
		 * and set_irq_wake() ... but those are "rare".
		 */
		अगर (irq > 0 && irq_has_action(irq)) अणु
			अक्षर *trigger;
			bool wake;

			अगर (nmk_chip->edge_rising & BIT(offset))
				trigger = "edge-rising";
			अन्यथा अगर (nmk_chip->edge_falling & BIT(offset))
				trigger = "edge-falling";
			अन्यथा
				trigger = "edge-undefined";

			wake = !!(nmk_chip->real_wake & BIT(offset));

			seq_म_लिखो(s, " irq-%d %s%s",
				   irq, trigger, wake ? " wakeup" : "");
		पूर्ण
	पूर्ण
	clk_disable(nmk_chip->clk);
पूर्ण

अटल व्योम nmk_gpio_dbg_show(काष्ठा seq_file *s, काष्ठा gpio_chip *chip)
अणु
	अचिन्हित		i;
	अचिन्हित		gpio = chip->base;

	क्रम (i = 0; i < chip->ngpio; i++, gpio++) अणु
		nmk_gpio_dbg_show_one(s, शून्य, chip, i, gpio);
		seq_म_लिखो(s, "\n");
	पूर्ण
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम nmk_gpio_dbg_show_one(काष्ठा seq_file *s,
					 काष्ठा pinctrl_dev *pctldev,
					 काष्ठा gpio_chip *chip,
					 अचिन्हित offset, अचिन्हित gpio)
अणु
पूर्ण
#घोषणा nmk_gpio_dbg_show	शून्य
#पूर्ण_अगर

/*
 * We will allocate memory क्रम the state container using devm* allocators
 * binding to the first device reaching this poपूर्णांक, it करोesn't matter अगर
 * it is the pin controller or GPIO driver. However we need to use the right
 * platक्रमm device when looking up resources so pay attention to pdev.
 */
अटल काष्ठा nmk_gpio_chip *nmk_gpio_populate_chip(काष्ठा device_node *np,
						काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा nmk_gpio_chip *nmk_chip;
	काष्ठा platक्रमm_device *gpio_pdev;
	काष्ठा gpio_chip *chip;
	काष्ठा resource *res;
	काष्ठा clk *clk;
	व्योम __iomem *base;
	u32 id;

	gpio_pdev = of_find_device_by_node(np);
	अगर (!gpio_pdev) अणु
		pr_err("populate \"%pOFn\": device not found\n", np);
		वापस ERR_PTR(-ENODEV);
	पूर्ण
	अगर (of_property_पढ़ो_u32(np, "gpio-bank", &id)) अणु
		dev_err(&pdev->dev, "populate: gpio-bank property not found\n");
		platक्रमm_device_put(gpio_pdev);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* Alपढ़ोy populated? */
	nmk_chip = nmk_gpio_chips[id];
	अगर (nmk_chip) अणु
		platक्रमm_device_put(gpio_pdev);
		वापस nmk_chip;
	पूर्ण

	nmk_chip = devm_kzalloc(&pdev->dev, माप(*nmk_chip), GFP_KERNEL);
	अगर (!nmk_chip) अणु
		platक्रमm_device_put(gpio_pdev);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	nmk_chip->bank = id;
	chip = &nmk_chip->chip;
	chip->base = id * NMK_GPIO_PER_CHIP;
	chip->ngpio = NMK_GPIO_PER_CHIP;
	chip->label = dev_name(&gpio_pdev->dev);
	chip->parent = &gpio_pdev->dev;

	res = platक्रमm_get_resource(gpio_pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base)) अणु
		platक्रमm_device_put(gpio_pdev);
		वापस ERR_CAST(base);
	पूर्ण
	nmk_chip->addr = base;

	clk = clk_get(&gpio_pdev->dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		platक्रमm_device_put(gpio_pdev);
		वापस (व्योम *) clk;
	पूर्ण
	clk_prepare(clk);
	nmk_chip->clk = clk;

	BUG_ON(nmk_chip->bank >= ARRAY_SIZE(nmk_gpio_chips));
	nmk_gpio_chips[id] = nmk_chip;
	वापस nmk_chip;
पूर्ण

अटल पूर्णांक nmk_gpio_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा device_node *np = dev->dev.of_node;
	काष्ठा nmk_gpio_chip *nmk_chip;
	काष्ठा gpio_chip *chip;
	काष्ठा gpio_irq_chip *girq;
	काष्ठा irq_chip *irqchip;
	bool supports_sleepmode;
	पूर्णांक irq;
	पूर्णांक ret;

	nmk_chip = nmk_gpio_populate_chip(np, dev);
	अगर (IS_ERR(nmk_chip)) अणु
		dev_err(&dev->dev, "could not populate nmk chip struct\n");
		वापस PTR_ERR(nmk_chip);
	पूर्ण

	supports_sleepmode =
		of_property_पढ़ो_bool(np, "st,supports-sleepmode");

	/* Correct platक्रमm device ID */
	dev->id = nmk_chip->bank;

	irq = platक्रमm_get_irq(dev, 0);
	अगर (irq < 0)
		वापस irq;

	/*
	 * The virt address in nmk_chip->addr is in the nomadik रेजिस्टर space,
	 * so we can simply convert the resource address, without remapping
	 */
	nmk_chip->sleepmode = supports_sleepmode;
	spin_lock_init(&nmk_chip->lock);

	chip = &nmk_chip->chip;
	chip->request = gpiochip_generic_request;
	chip->मुक्त = gpiochip_generic_मुक्त;
	chip->get_direction = nmk_gpio_get_dir;
	chip->direction_input = nmk_gpio_make_input;
	chip->get = nmk_gpio_get_input;
	chip->direction_output = nmk_gpio_make_output;
	chip->set = nmk_gpio_set_output;
	chip->dbg_show = nmk_gpio_dbg_show;
	chip->can_sleep = false;
	chip->owner = THIS_MODULE;

	irqchip = &nmk_chip->irqchip;
	irqchip->irq_ack = nmk_gpio_irq_ack;
	irqchip->irq_mask = nmk_gpio_irq_mask;
	irqchip->irq_unmask = nmk_gpio_irq_unmask;
	irqchip->irq_set_type = nmk_gpio_irq_set_type;
	irqchip->irq_set_wake = nmk_gpio_irq_set_wake;
	irqchip->irq_startup = nmk_gpio_irq_startup;
	irqchip->irq_shutकरोwn = nmk_gpio_irq_shutकरोwn;
	irqchip->flags = IRQCHIP_MASK_ON_SUSPEND;
	irqchip->name = kaप्र_लिखो(GFP_KERNEL, "nmk%u-%u-%u",
				  dev->id,
				  chip->base,
				  chip->base + chip->ngpio - 1);

	girq = &chip->irq;
	girq->chip = irqchip;
	girq->parent_handler = nmk_gpio_irq_handler;
	girq->num_parents = 1;
	girq->parents = devm_kसुस्मृति(&dev->dev, 1,
				     माप(*girq->parents),
				     GFP_KERNEL);
	अगर (!girq->parents)
		वापस -ENOMEM;
	girq->parents[0] = irq;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_edge_irq;

	clk_enable(nmk_chip->clk);
	nmk_chip->lowemi = पढ़ोl_relaxed(nmk_chip->addr + NMK_GPIO_LOWEMI);
	clk_disable(nmk_chip->clk);
	chip->of_node = np;

	ret = gpiochip_add_data(chip, nmk_chip);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(dev, nmk_chip);

	dev_info(&dev->dev, "chip registered\n");

	वापस 0;
पूर्ण

अटल पूर्णांक nmk_get_groups_cnt(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा nmk_pinctrl *npct = pinctrl_dev_get_drvdata(pctldev);

	वापस npct->soc->ngroups;
पूर्ण

अटल स्थिर अक्षर *nmk_get_group_name(काष्ठा pinctrl_dev *pctldev,
				       अचिन्हित selector)
अणु
	काष्ठा nmk_pinctrl *npct = pinctrl_dev_get_drvdata(pctldev);

	वापस npct->soc->groups[selector].name;
पूर्ण

अटल पूर्णांक nmk_get_group_pins(काष्ठा pinctrl_dev *pctldev, अचिन्हित selector,
			      स्थिर अचिन्हित **pins,
			      अचिन्हित *num_pins)
अणु
	काष्ठा nmk_pinctrl *npct = pinctrl_dev_get_drvdata(pctldev);

	*pins = npct->soc->groups[selector].pins;
	*num_pins = npct->soc->groups[selector].npins;
	वापस 0;
पूर्ण

अटल काष्ठा nmk_gpio_chip *find_nmk_gpio_from_pin(अचिन्हित pin)
अणु
	पूर्णांक i;
	काष्ठा nmk_gpio_chip *nmk_gpio;

	क्रम(i = 0; i < NMK_MAX_BANKS; i++) अणु
		nmk_gpio = nmk_gpio_chips[i];
		अगर (!nmk_gpio)
			जारी;
		अगर (pin >= nmk_gpio->chip.base &&
			pin < nmk_gpio->chip.base + nmk_gpio->chip.ngpio)
			वापस nmk_gpio;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा gpio_chip *find_gc_from_pin(अचिन्हित pin)
अणु
	काष्ठा nmk_gpio_chip *nmk_gpio = find_nmk_gpio_from_pin(pin);

	अगर (nmk_gpio)
		वापस &nmk_gpio->chip;
	वापस शून्य;
पूर्ण

अटल व्योम nmk_pin_dbg_show(काष्ठा pinctrl_dev *pctldev, काष्ठा seq_file *s,
		   अचिन्हित offset)
अणु
	काष्ठा gpio_chip *chip = find_gc_from_pin(offset);

	अगर (!chip) अणु
		seq_म_लिखो(s, "invalid pin offset");
		वापस;
	पूर्ण
	nmk_gpio_dbg_show_one(s, pctldev, chip, offset - chip->base, offset);
पूर्ण

अटल पूर्णांक nmk_dt_add_map_mux(काष्ठा pinctrl_map **map, अचिन्हित *reserved_maps,
		अचिन्हित *num_maps, स्थिर अक्षर *group,
		स्थिर अक्षर *function)
अणु
	अगर (*num_maps == *reserved_maps)
		वापस -ENOSPC;

	(*map)[*num_maps].type = PIN_MAP_TYPE_MUX_GROUP;
	(*map)[*num_maps].data.mux.group = group;
	(*map)[*num_maps].data.mux.function = function;
	(*num_maps)++;

	वापस 0;
पूर्ण

अटल पूर्णांक nmk_dt_add_map_configs(काष्ठा pinctrl_map **map,
		अचिन्हित *reserved_maps,
		अचिन्हित *num_maps, स्थिर अक्षर *group,
		अचिन्हित दीर्घ *configs, अचिन्हित num_configs)
अणु
	अचिन्हित दीर्घ *dup_configs;

	अगर (*num_maps == *reserved_maps)
		वापस -ENOSPC;

	dup_configs = kmemdup(configs, num_configs * माप(*dup_configs),
			      GFP_KERNEL);
	अगर (!dup_configs)
		वापस -ENOMEM;

	(*map)[*num_maps].type = PIN_MAP_TYPE_CONFIGS_PIN;

	(*map)[*num_maps].data.configs.group_or_pin = group;
	(*map)[*num_maps].data.configs.configs = dup_configs;
	(*map)[*num_maps].data.configs.num_configs = num_configs;
	(*num_maps)++;

	वापस 0;
पूर्ण

#घोषणा NMK_CONFIG_PIN(x, y) अणु .property = x, .config = y, पूर्ण
#घोषणा NMK_CONFIG_PIN_ARRAY(x, y) अणु .property = x, .choice = y, \
	.size = ARRAY_SIZE(y), पूर्ण

अटल स्थिर अचिन्हित दीर्घ nmk_pin_input_modes[] = अणु
	PIN_INPUT_NOPULL,
	PIN_INPUT_PULLUP,
	PIN_INPUT_PULLDOWN,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ nmk_pin_output_modes[] = अणु
	PIN_OUTPUT_LOW,
	PIN_OUTPUT_HIGH,
	PIN_सूची_OUTPUT,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ nmk_pin_sleep_modes[] = अणु
	PIN_SLEEPMODE_DISABLED,
	PIN_SLEEPMODE_ENABLED,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ nmk_pin_sleep_input_modes[] = अणु
	PIN_SLPM_INPUT_NOPULL,
	PIN_SLPM_INPUT_PULLUP,
	PIN_SLPM_INPUT_PULLDOWN,
	PIN_SLPM_सूची_INPUT,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ nmk_pin_sleep_output_modes[] = अणु
	PIN_SLPM_OUTPUT_LOW,
	PIN_SLPM_OUTPUT_HIGH,
	PIN_SLPM_सूची_OUTPUT,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ nmk_pin_sleep_wakeup_modes[] = अणु
	PIN_SLPM_WAKEUP_DISABLE,
	PIN_SLPM_WAKEUP_ENABLE,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ nmk_pin_gpio_modes[] = अणु
	PIN_GPIOMODE_DISABLED,
	PIN_GPIOMODE_ENABLED,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ nmk_pin_sleep_pdis_modes[] = अणु
	PIN_SLPM_PDIS_DISABLED,
	PIN_SLPM_PDIS_ENABLED,
पूर्ण;

काष्ठा nmk_cfg_param अणु
	स्थिर अक्षर *property;
	अचिन्हित दीर्घ config;
	स्थिर अचिन्हित दीर्घ *choice;
	पूर्णांक size;
पूर्ण;

अटल स्थिर काष्ठा nmk_cfg_param nmk_cfg_params[] = अणु
	NMK_CONFIG_PIN_ARRAY("ste,input",		nmk_pin_input_modes),
	NMK_CONFIG_PIN_ARRAY("ste,output",		nmk_pin_output_modes),
	NMK_CONFIG_PIN_ARRAY("ste,sleep",		nmk_pin_sleep_modes),
	NMK_CONFIG_PIN_ARRAY("ste,sleep-input",		nmk_pin_sleep_input_modes),
	NMK_CONFIG_PIN_ARRAY("ste,sleep-output",	nmk_pin_sleep_output_modes),
	NMK_CONFIG_PIN_ARRAY("ste,sleep-wakeup",	nmk_pin_sleep_wakeup_modes),
	NMK_CONFIG_PIN_ARRAY("ste,gpio",		nmk_pin_gpio_modes),
	NMK_CONFIG_PIN_ARRAY("ste,sleep-pull-disable",	nmk_pin_sleep_pdis_modes),
पूर्ण;

अटल पूर्णांक nmk_dt_pin_config(पूर्णांक index, पूर्णांक val, अचिन्हित दीर्घ *config)
अणु
	अगर (nmk_cfg_params[index].choice == शून्य)
		*config = nmk_cfg_params[index].config;
	अन्यथा अणु
		/* test अगर out of range */
		अगर  (val < nmk_cfg_params[index].size) अणु
			*config = nmk_cfg_params[index].config |
				nmk_cfg_params[index].choice[val];
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर अक्षर *nmk_find_pin_name(काष्ठा pinctrl_dev *pctldev, स्थिर अक्षर *pin_name)
अणु
	पूर्णांक i, pin_number;
	काष्ठा nmk_pinctrl *npct = pinctrl_dev_get_drvdata(pctldev);

	अगर (माला_पूछो((अक्षर *)pin_name, "GPIO%d", &pin_number) == 1)
		क्रम (i = 0; i < npct->soc->npins; i++)
			अगर (npct->soc->pins[i].number == pin_number)
				वापस npct->soc->pins[i].name;
	वापस शून्य;
पूर्ण

अटल bool nmk_pinctrl_dt_get_config(काष्ठा device_node *np,
		अचिन्हित दीर्घ *configs)
अणु
	bool has_config = 0;
	अचिन्हित दीर्घ cfg = 0;
	पूर्णांक i, val, ret;

	क्रम (i = 0; i < ARRAY_SIZE(nmk_cfg_params); i++) अणु
		ret = of_property_पढ़ो_u32(np,
				nmk_cfg_params[i].property, &val);
		अगर (ret != -EINVAL) अणु
			अगर (nmk_dt_pin_config(i, val, &cfg) == 0) अणु
				*configs |= cfg;
				has_config = 1;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस has_config;
पूर्ण

अटल पूर्णांक nmk_pinctrl_dt_subnode_to_map(काष्ठा pinctrl_dev *pctldev,
		काष्ठा device_node *np,
		काष्ठा pinctrl_map **map,
		अचिन्हित *reserved_maps,
		अचिन्हित *num_maps)
अणु
	पूर्णांक ret;
	स्थिर अक्षर *function = शून्य;
	अचिन्हित दीर्घ configs = 0;
	bool has_config = 0;
	काष्ठा property *prop;
	काष्ठा device_node *np_config;

	ret = of_property_पढ़ो_string(np, "function", &function);
	अगर (ret >= 0) अणु
		स्थिर अक्षर *group;

		ret = of_property_count_strings(np, "groups");
		अगर (ret < 0)
			जाओ निकास;

		ret = pinctrl_utils_reserve_map(pctldev, map,
						reserved_maps,
						num_maps, ret);
		अगर (ret < 0)
			जाओ निकास;

		of_property_क्रम_each_string(np, "groups", prop, group) अणु
			ret = nmk_dt_add_map_mux(map, reserved_maps, num_maps,
					  group, function);
			अगर (ret < 0)
				जाओ निकास;
		पूर्ण
	पूर्ण

	has_config = nmk_pinctrl_dt_get_config(np, &configs);
	np_config = of_parse_phandle(np, "ste,config", 0);
	अगर (np_config)
		has_config |= nmk_pinctrl_dt_get_config(np_config, &configs);
	अगर (has_config) अणु
		स्थिर अक्षर *gpio_name;
		स्थिर अक्षर *pin;

		ret = of_property_count_strings(np, "pins");
		अगर (ret < 0)
			जाओ निकास;
		ret = pinctrl_utils_reserve_map(pctldev, map,
						reserved_maps,
						num_maps, ret);
		अगर (ret < 0)
			जाओ निकास;

		of_property_क्रम_each_string(np, "pins", prop, pin) अणु
			gpio_name = nmk_find_pin_name(pctldev, pin);

			ret = nmk_dt_add_map_configs(map, reserved_maps,
						     num_maps,
						     gpio_name, &configs, 1);
			अगर (ret < 0)
				जाओ निकास;
		पूर्ण
	पूर्ण

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक nmk_pinctrl_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
				 काष्ठा device_node *np_config,
				 काष्ठा pinctrl_map **map, अचिन्हित *num_maps)
अणु
	अचिन्हित reserved_maps;
	काष्ठा device_node *np;
	पूर्णांक ret;

	reserved_maps = 0;
	*map = शून्य;
	*num_maps = 0;

	क्रम_each_child_of_node(np_config, np) अणु
		ret = nmk_pinctrl_dt_subnode_to_map(pctldev, np, map,
				&reserved_maps, num_maps);
		अगर (ret < 0) अणु
			pinctrl_utils_मुक्त_map(pctldev, *map, *num_maps);
			of_node_put(np);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops nmk_pinctrl_ops = अणु
	.get_groups_count = nmk_get_groups_cnt,
	.get_group_name = nmk_get_group_name,
	.get_group_pins = nmk_get_group_pins,
	.pin_dbg_show = nmk_pin_dbg_show,
	.dt_node_to_map = nmk_pinctrl_dt_node_to_map,
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
पूर्ण;

अटल पूर्णांक nmk_pmx_get_funcs_cnt(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा nmk_pinctrl *npct = pinctrl_dev_get_drvdata(pctldev);

	वापस npct->soc->nfunctions;
पूर्ण

अटल स्थिर अक्षर *nmk_pmx_get_func_name(काष्ठा pinctrl_dev *pctldev,
					 अचिन्हित function)
अणु
	काष्ठा nmk_pinctrl *npct = pinctrl_dev_get_drvdata(pctldev);

	वापस npct->soc->functions[function].name;
पूर्ण

अटल पूर्णांक nmk_pmx_get_func_groups(काष्ठा pinctrl_dev *pctldev,
				   अचिन्हित function,
				   स्थिर अक्षर * स्थिर **groups,
				   अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा nmk_pinctrl *npct = pinctrl_dev_get_drvdata(pctldev);

	*groups = npct->soc->functions[function].groups;
	*num_groups = npct->soc->functions[function].ngroups;

	वापस 0;
पूर्ण

अटल पूर्णांक nmk_pmx_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित function,
		       अचिन्हित group)
अणु
	काष्ठा nmk_pinctrl *npct = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा nmk_pingroup *g;
	अटल अचिन्हित पूर्णांक slpm[NUM_BANKS];
	अचिन्हित दीर्घ flags = 0;
	bool glitch;
	पूर्णांक ret = -EINVAL;
	पूर्णांक i;

	g = &npct->soc->groups[group];

	अगर (g->altsetting < 0)
		वापस -EINVAL;

	dev_dbg(npct->dev, "enable group %s, %u pins\n", g->name, g->npins);

	/*
	 * If we're setting altfunc C by setting both AFSLA and AFSLB to 1,
	 * we may pass through an undesired state. In this हाल we take
	 * some extra care.
	 *
	 * Safe sequence used to चयन IOs between GPIO and Alternate-C mode:
	 *  - Save SLPM रेजिस्टरs (since we have a shaकरोw रेजिस्टर in the
	 *    nmk_chip we're using that as backup)
	 *  - Set SLPM=0 क्रम the IOs you want to चयन and others to 1
	 *  - Configure the GPIO रेजिस्टरs क्रम the IOs that are being चयनed
	 *  - Set IOFORCE=1
	 *  - Modअगरy the AFLSA/B रेजिस्टरs क्रम the IOs that are being चयनed
	 *  - Set IOFORCE=0
	 *  - Restore SLPM रेजिस्टरs
	 *  - Any spurious wake up event during चयन sequence to be ignored
	 *    and cleared
	 *
	 * We REALLY need to save ALL slpm रेजिस्टरs, because the बाह्यal
	 * IOFORCE will चयन *all* ports to their sleepmode setting to as
	 * to aव्योम glitches. (Not just one port!)
	 */
	glitch = ((g->altsetting & NMK_GPIO_ALT_C) == NMK_GPIO_ALT_C);

	अगर (glitch) अणु
		spin_lock_irqsave(&nmk_gpio_slpm_lock, flags);

		/* Initially करोn't put any pins to sleep when चयनing */
		स_रखो(slpm, 0xff, माप(slpm));

		/*
		 * Then mask the pins that need to be sleeping now when we're
		 * चयनing to the ALT C function.
		 */
		क्रम (i = 0; i < g->npins; i++)
			slpm[g->pins[i] / NMK_GPIO_PER_CHIP] &= ~BIT(g->pins[i]);
		nmk_gpio_glitch_slpm_init(slpm);
	पूर्ण

	क्रम (i = 0; i < g->npins; i++) अणु
		काष्ठा nmk_gpio_chip *nmk_chip;
		अचिन्हित bit;

		nmk_chip = find_nmk_gpio_from_pin(g->pins[i]);
		अगर (!nmk_chip) अणु
			dev_err(npct->dev,
				"invalid pin offset %d in group %s at index %d\n",
				g->pins[i], g->name, i);
			जाओ out_glitch;
		पूर्ण
		dev_dbg(npct->dev, "setting pin %d to altsetting %d\n", g->pins[i], g->altsetting);

		clk_enable(nmk_chip->clk);
		bit = g->pins[i] % NMK_GPIO_PER_CHIP;
		/*
		 * If the pin is चयनing to altfunc, and there was an
		 * पूर्णांकerrupt installed on it which has been lazy disabled,
		 * actually mask the पूर्णांकerrupt to prevent spurious पूर्णांकerrupts
		 * that would occur जबतक the pin is under control of the
		 * peripheral. Only SKE करोes this.
		 */
		nmk_gpio_disable_lazy_irq(nmk_chip, bit);

		__nmk_gpio_set_mode_safe(nmk_chip, bit,
			(g->altsetting & NMK_GPIO_ALT_C), glitch);
		clk_disable(nmk_chip->clk);

		/*
		 * Call PRCM GPIOCR config function in हाल ALTC
		 * has been selected:
		 * - If selection is a ALTCx, some bits in PRCM GPIOCR रेजिस्टरs
		 *   must be set.
		 * - If selection is pure ALTC and previous selection was ALTCx,
		 *   then some bits in PRCM GPIOCR रेजिस्टरs must be cleared.
		 */
		अगर ((g->altsetting & NMK_GPIO_ALT_C) == NMK_GPIO_ALT_C)
			nmk_prcm_altcx_set_mode(npct, g->pins[i],
				g->altsetting >> NMK_GPIO_ALT_CX_SHIFT);
	पूर्ण

	/* When all pins are successfully reconfigured we get here */
	ret = 0;

out_glitch:
	अगर (glitch) अणु
		nmk_gpio_glitch_slpm_restore(slpm);
		spin_unlock_irqrestore(&nmk_gpio_slpm_lock, flags);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक nmk_gpio_request_enable(काष्ठा pinctrl_dev *pctldev,
				   काष्ठा pinctrl_gpio_range *range,
				   अचिन्हित offset)
अणु
	काष्ठा nmk_pinctrl *npct = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा nmk_gpio_chip *nmk_chip;
	काष्ठा gpio_chip *chip;
	अचिन्हित bit;

	अगर (!range) अणु
		dev_err(npct->dev, "invalid range\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!range->gc) अणु
		dev_err(npct->dev, "missing GPIO chip in range\n");
		वापस -EINVAL;
	पूर्ण
	chip = range->gc;
	nmk_chip = gpiochip_get_data(chip);

	dev_dbg(npct->dev, "enable pin %u as GPIO\n", offset);

	clk_enable(nmk_chip->clk);
	bit = offset % NMK_GPIO_PER_CHIP;
	/* There is no glitch when converting any pin to GPIO */
	__nmk_gpio_set_mode(nmk_chip, bit, NMK_GPIO_ALT_GPIO);
	clk_disable(nmk_chip->clk);

	वापस 0;
पूर्ण

अटल व्योम nmk_gpio_disable_मुक्त(काष्ठा pinctrl_dev *pctldev,
				  काष्ठा pinctrl_gpio_range *range,
				  अचिन्हित offset)
अणु
	काष्ठा nmk_pinctrl *npct = pinctrl_dev_get_drvdata(pctldev);

	dev_dbg(npct->dev, "disable pin %u as GPIO\n", offset);
	/* Set the pin to some शेष state, GPIO is usually शेष */
पूर्ण

अटल स्थिर काष्ठा pinmux_ops nmk_pinmux_ops = अणु
	.get_functions_count = nmk_pmx_get_funcs_cnt,
	.get_function_name = nmk_pmx_get_func_name,
	.get_function_groups = nmk_pmx_get_func_groups,
	.set_mux = nmk_pmx_set,
	.gpio_request_enable = nmk_gpio_request_enable,
	.gpio_disable_मुक्त = nmk_gpio_disable_मुक्त,
	.strict = true,
पूर्ण;

अटल पूर्णांक nmk_pin_config_get(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin,
			      अचिन्हित दीर्घ *config)
अणु
	/* Not implemented */
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक nmk_pin_config_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin,
			      अचिन्हित दीर्घ *configs, अचिन्हित num_configs)
अणु
	अटल स्थिर अक्षर *pullnames[] = अणु
		[NMK_GPIO_PULL_NONE]	= "none",
		[NMK_GPIO_PULL_UP]	= "up",
		[NMK_GPIO_PULL_DOWN]	= "down",
		[3] /* illegal */	= "??"
	पूर्ण;
	अटल स्थिर अक्षर *slpmnames[] = अणु
		[NMK_GPIO_SLPM_INPUT]		= "input/wakeup",
		[NMK_GPIO_SLPM_NOCHANGE]	= "no-change/no-wakeup",
	पूर्ण;
	काष्ठा nmk_pinctrl *npct = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा nmk_gpio_chip *nmk_chip;
	अचिन्हित bit;
	pin_cfg_t cfg;
	पूर्णांक pull, slpm, output, val, i;
	bool lowemi, gpiomode, sleep;

	nmk_chip = find_nmk_gpio_from_pin(pin);
	अगर (!nmk_chip) अणु
		dev_err(npct->dev,
			"invalid pin offset %d\n", pin);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < num_configs; i++) अणु
		/*
		 * The pin config contains pin number and altfunction fields,
		 * here we just ignore that part. It's being handled by the
		 * framework and pinmux callback respectively.
		 */
		cfg = (pin_cfg_t) configs[i];
		pull = PIN_PULL(cfg);
		slpm = PIN_SLPM(cfg);
		output = PIN_सूची(cfg);
		val = PIN_VAL(cfg);
		lowemi = PIN_LOWEMI(cfg);
		gpiomode = PIN_GPIOMODE(cfg);
		sleep = PIN_SLEEPMODE(cfg);

		अगर (sleep) अणु
			पूर्णांक slpm_pull = PIN_SLPM_PULL(cfg);
			पूर्णांक slpm_output = PIN_SLPM_सूची(cfg);
			पूर्णांक slpm_val = PIN_SLPM_VAL(cfg);

			/* All pins go पूर्णांकo GPIO mode at sleep */
			gpiomode = true;

			/*
			 * The SLPM_* values are normal values + 1 to allow zero
			 * to mean "same as normal".
			 */
			अगर (slpm_pull)
				pull = slpm_pull - 1;
			अगर (slpm_output)
				output = slpm_output - 1;
			अगर (slpm_val)
				val = slpm_val - 1;

			dev_dbg(nmk_chip->chip.parent,
				"pin %d: sleep pull %s, dir %s, val %s\n",
				pin,
				slpm_pull ? pullnames[pull] : "same",
				slpm_output ? (output ? "output" : "input")
				: "same",
				slpm_val ? (val ? "high" : "low") : "same");
		पूर्ण

		dev_dbg(nmk_chip->chip.parent,
			"pin %d [%#lx]: pull %s, slpm %s (%s%s), lowemi %s\n",
			pin, cfg, pullnames[pull], slpmnames[slpm],
			output ? "output " : "input",
			output ? (val ? "high" : "low") : "",
			lowemi ? "on" : "off");

		clk_enable(nmk_chip->clk);
		bit = pin % NMK_GPIO_PER_CHIP;
		अगर (gpiomode)
			/* No glitch when going to GPIO mode */
			__nmk_gpio_set_mode(nmk_chip, bit, NMK_GPIO_ALT_GPIO);
		अगर (output)
			__nmk_gpio_make_output(nmk_chip, bit, val);
		अन्यथा अणु
			__nmk_gpio_make_input(nmk_chip, bit);
			__nmk_gpio_set_pull(nmk_chip, bit, pull);
		पूर्ण
		/* TODO: isn't this only applicable on output pins? */
		__nmk_gpio_set_lowemi(nmk_chip, bit, lowemi);

		__nmk_gpio_set_slpm(nmk_chip, bit, slpm);
		clk_disable(nmk_chip->clk);
	पूर्ण /* क्रम each config */

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops nmk_pinconf_ops = अणु
	.pin_config_get = nmk_pin_config_get,
	.pin_config_set = nmk_pin_config_set,
पूर्ण;

अटल काष्ठा pinctrl_desc nmk_pinctrl_desc = अणु
	.name = "pinctrl-nomadik",
	.pctlops = &nmk_pinctrl_ops,
	.pmxops = &nmk_pinmux_ops,
	.confops = &nmk_pinconf_ops,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id nmk_pinctrl_match[] = अणु
	अणु
		.compatible = "stericsson,stn8815-pinctrl",
		.data = (व्योम *)PINCTRL_NMK_STN8815,
	पूर्ण,
	अणु
		.compatible = "stericsson,db8500-pinctrl",
		.data = (व्योम *)PINCTRL_NMK_DB8500,
	पूर्ण,
	अणु
		.compatible = "stericsson,db8540-pinctrl",
		.data = (व्योम *)PINCTRL_NMK_DB8540,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक nmk_pinctrl_suspend(काष्ठा device *dev)
अणु
	काष्ठा nmk_pinctrl *npct;

	npct = dev_get_drvdata(dev);
	अगर (!npct)
		वापस -EINVAL;

	वापस pinctrl_क्रमce_sleep(npct->pctl);
पूर्ण

अटल पूर्णांक nmk_pinctrl_resume(काष्ठा device *dev)
अणु
	काष्ठा nmk_pinctrl *npct;

	npct = dev_get_drvdata(dev);
	अगर (!npct)
		वापस -EINVAL;

	वापस pinctrl_क्रमce_शेष(npct->pctl);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक nmk_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *prcm_np;
	काष्ठा nmk_pinctrl *npct;
	अचिन्हित पूर्णांक version = 0;
	पूर्णांक i;

	npct = devm_kzalloc(&pdev->dev, माप(*npct), GFP_KERNEL);
	अगर (!npct)
		वापस -ENOMEM;

	match = of_match_device(nmk_pinctrl_match, &pdev->dev);
	अगर (!match)
		वापस -ENODEV;
	version = (अचिन्हित पूर्णांक) match->data;

	/* Poke in other ASIC variants here */
	अगर (version == PINCTRL_NMK_STN8815)
		nmk_pinctrl_stn8815_init(&npct->soc);
	अगर (version == PINCTRL_NMK_DB8500)
		nmk_pinctrl_db8500_init(&npct->soc);
	अगर (version == PINCTRL_NMK_DB8540)
		nmk_pinctrl_db8540_init(&npct->soc);

	/*
	 * Since we depend on the GPIO chips to provide घड़ी and रेजिस्टर base
	 * क्रम the pin control operations, make sure that we have these
	 * populated beक्रमe we जारी. Follow the phandles to instantiate
	 * them. The GPIO portion of the actual hardware may be probed beक्रमe
	 * or after this poपूर्णांक: it shouldn't matter as the APIs are orthogonal.
	 */
	क्रम (i = 0; i < NMK_MAX_BANKS; i++) अणु
		काष्ठा device_node *gpio_np;
		काष्ठा nmk_gpio_chip *nmk_chip;

		gpio_np = of_parse_phandle(np, "nomadik-gpio-chips", i);
		अगर (gpio_np) अणु
			dev_info(&pdev->dev,
				 "populate NMK GPIO %d \"%pOFn\"\n",
				 i, gpio_np);
			nmk_chip = nmk_gpio_populate_chip(gpio_np, pdev);
			अगर (IS_ERR(nmk_chip))
				dev_err(&pdev->dev,
					"could not populate nmk chip struct "
					"- continue anyway\n");
			of_node_put(gpio_np);
		पूर्ण
	पूर्ण

	prcm_np = of_parse_phandle(np, "prcm", 0);
	अगर (prcm_np)
		npct->prcm_base = of_iomap(prcm_np, 0);
	अगर (!npct->prcm_base) अणु
		अगर (version == PINCTRL_NMK_STN8815) अणु
			dev_info(&pdev->dev,
				 "No PRCM base, "
				 "assuming no ALT-Cx control is available\n");
		पूर्ण अन्यथा अणु
			dev_err(&pdev->dev, "missing PRCM base address\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	nmk_pinctrl_desc.pins = npct->soc->pins;
	nmk_pinctrl_desc.npins = npct->soc->npins;
	npct->dev = &pdev->dev;

	npct->pctl = devm_pinctrl_रेजिस्टर(&pdev->dev, &nmk_pinctrl_desc, npct);
	अगर (IS_ERR(npct->pctl)) अणु
		dev_err(&pdev->dev, "could not register Nomadik pinctrl driver\n");
		वापस PTR_ERR(npct->pctl);
	पूर्ण

	platक्रमm_set_drvdata(pdev, npct);
	dev_info(&pdev->dev, "initialized Nomadik pin control driver\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id nmk_gpio_match[] = अणु
	अणु .compatible = "st,nomadik-gpio", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver nmk_gpio_driver = अणु
	.driver = अणु
		.name = "gpio",
		.of_match_table = nmk_gpio_match,
	पूर्ण,
	.probe = nmk_gpio_probe,
पूर्ण;

अटल SIMPLE_DEV_PM_OPS(nmk_pinctrl_pm_ops,
			nmk_pinctrl_suspend,
			nmk_pinctrl_resume);

अटल काष्ठा platक्रमm_driver nmk_pinctrl_driver = अणु
	.driver = अणु
		.name = "pinctrl-nomadik",
		.of_match_table = nmk_pinctrl_match,
		.pm = &nmk_pinctrl_pm_ops,
	पूर्ण,
	.probe = nmk_pinctrl_probe,
पूर्ण;

अटल पूर्णांक __init nmk_gpio_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&nmk_gpio_driver);
पूर्ण
subsys_initcall(nmk_gpio_init);

अटल पूर्णांक __init nmk_pinctrl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&nmk_pinctrl_driver);
पूर्ण
core_initcall(nmk_pinctrl_init);
