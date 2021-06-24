<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel Lynxpoपूर्णांक PCH pinctrl/GPIO driver
 *
 * Copyright (c) 2012, 2019, Intel Corporation
 * Authors: Mathias Nyman <mathias.nyman@linux.पूर्णांकel.com>
 *          Andy Shevchenko <andriy.shevchenko@linux.पूर्णांकel.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/bitops.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>

#समावेश "pinctrl-intel.h"

#घोषणा COMMUNITY(p, n)			\
	अणु				\
		.pin_base	= (p),	\
		.npins		= (n),	\
	पूर्ण

अटल स्थिर काष्ठा pinctrl_pin_desc lptlp_pins[] = अणु
	PINCTRL_PIN(0, "GP0_UART1_RXD"),
	PINCTRL_PIN(1, "GP1_UART1_TXD"),
	PINCTRL_PIN(2, "GP2_UART1_RTSB"),
	PINCTRL_PIN(3, "GP3_UART1_CTSB"),
	PINCTRL_PIN(4, "GP4_I2C0_SDA"),
	PINCTRL_PIN(5, "GP5_I2C0_SCL"),
	PINCTRL_PIN(6, "GP6_I2C1_SDA"),
	PINCTRL_PIN(7, "GP7_I2C1_SCL"),
	PINCTRL_PIN(8, "GP8"),
	PINCTRL_PIN(9, "GP9"),
	PINCTRL_PIN(10, "GP10"),
	PINCTRL_PIN(11, "GP11_SMBALERTB"),
	PINCTRL_PIN(12, "GP12_LANPHYPC"),
	PINCTRL_PIN(13, "GP13"),
	PINCTRL_PIN(14, "GP14"),
	PINCTRL_PIN(15, "GP15"),
	PINCTRL_PIN(16, "GP16_MGPIO9"),
	PINCTRL_PIN(17, "GP17_MGPIO10"),
	PINCTRL_PIN(18, "GP18_SRC0CLKRQB"),
	PINCTRL_PIN(19, "GP19_SRC1CLKRQB"),
	PINCTRL_PIN(20, "GP20_SRC2CLKRQB"),
	PINCTRL_PIN(21, "GP21_SRC3CLKRQB"),
	PINCTRL_PIN(22, "GP22_SRC4CLKRQB_TRST2"),
	PINCTRL_PIN(23, "GP23_SRC5CLKRQB_TDI2"),
	PINCTRL_PIN(24, "GP24_MGPIO0"),
	PINCTRL_PIN(25, "GP25_USBWAKEOUTB"),
	PINCTRL_PIN(26, "GP26_MGPIO5"),
	PINCTRL_PIN(27, "GP27_MGPIO6"),
	PINCTRL_PIN(28, "GP28_MGPIO7"),
	PINCTRL_PIN(29, "GP29_SLP_WLANB_MGPIO3"),
	PINCTRL_PIN(30, "GP30_SUSWARNB_SUSPWRDNACK_MGPIO1"),
	PINCTRL_PIN(31, "GP31_ACPRESENT_MGPIO2"),
	PINCTRL_PIN(32, "GP32_CLKRUNB"),
	PINCTRL_PIN(33, "GP33_DEVSLP0"),
	PINCTRL_PIN(34, "GP34_SATA0XPCIE6L3B_SATA0GP"),
	PINCTRL_PIN(35, "GP35_SATA1XPCIE6L2B_SATA1GP"),
	PINCTRL_PIN(36, "GP36_SATA2XPCIE6L1B_SATA2GP"),
	PINCTRL_PIN(37, "GP37_SATA3XPCIE6L0B_SATA3GP"),
	PINCTRL_PIN(38, "GP38_DEVSLP1"),
	PINCTRL_PIN(39, "GP39_DEVSLP2"),
	PINCTRL_PIN(40, "GP40_OC0B"),
	PINCTRL_PIN(41, "GP41_OC1B"),
	PINCTRL_PIN(42, "GP42_OC2B"),
	PINCTRL_PIN(43, "GP43_OC3B"),
	PINCTRL_PIN(44, "GP44"),
	PINCTRL_PIN(45, "GP45_TMS2"),
	PINCTRL_PIN(46, "GP46_TDO2"),
	PINCTRL_PIN(47, "GP47"),
	PINCTRL_PIN(48, "GP48"),
	PINCTRL_PIN(49, "GP49"),
	PINCTRL_PIN(50, "GP50"),
	PINCTRL_PIN(51, "GP51_GSXDOUT"),
	PINCTRL_PIN(52, "GP52_GSXSLOAD"),
	PINCTRL_PIN(53, "GP53_GSXDIN"),
	PINCTRL_PIN(54, "GP54_GSXSRESETB"),
	PINCTRL_PIN(55, "GP55_GSXCLK"),
	PINCTRL_PIN(56, "GP56"),
	PINCTRL_PIN(57, "GP57"),
	PINCTRL_PIN(58, "GP58"),
	PINCTRL_PIN(59, "GP59"),
	PINCTRL_PIN(60, "GP60_SML0ALERTB_MGPIO4"),
	PINCTRL_PIN(61, "GP61_SUS_STATB"),
	PINCTRL_PIN(62, "GP62_SUSCLK"),
	PINCTRL_PIN(63, "GP63_SLP_S5B"),
	PINCTRL_PIN(64, "GP64_SDIO_CLK"),
	PINCTRL_PIN(65, "GP65_SDIO_CMD"),
	PINCTRL_PIN(66, "GP66_SDIO_D0"),
	PINCTRL_PIN(67, "GP67_SDIO_D1"),
	PINCTRL_PIN(68, "GP68_SDIO_D2"),
	PINCTRL_PIN(69, "GP69_SDIO_D3"),
	PINCTRL_PIN(70, "GP70_SDIO_POWER_EN"),
	PINCTRL_PIN(71, "GP71_MPHYPC"),
	PINCTRL_PIN(72, "GP72_BATLOWB"),
	PINCTRL_PIN(73, "GP73_SML1ALERTB_PCHHOTB_MGPIO8"),
	PINCTRL_PIN(74, "GP74_SML1DATA_MGPIO12"),
	PINCTRL_PIN(75, "GP75_SML1CLK_MGPIO11"),
	PINCTRL_PIN(76, "GP76_BMBUSYB"),
	PINCTRL_PIN(77, "GP77_PIRQAB"),
	PINCTRL_PIN(78, "GP78_PIRQBB"),
	PINCTRL_PIN(79, "GP79_PIRQCB"),
	PINCTRL_PIN(80, "GP80_PIRQDB"),
	PINCTRL_PIN(81, "GP81_SPKR"),
	PINCTRL_PIN(82, "GP82_RCINB"),
	PINCTRL_PIN(83, "GP83_GSPI0_CSB"),
	PINCTRL_PIN(84, "GP84_GSPI0_CLK"),
	PINCTRL_PIN(85, "GP85_GSPI0_MISO"),
	PINCTRL_PIN(86, "GP86_GSPI0_MOSI"),
	PINCTRL_PIN(87, "GP87_GSPI1_CSB"),
	PINCTRL_PIN(88, "GP88_GSPI1_CLK"),
	PINCTRL_PIN(89, "GP89_GSPI1_MISO"),
	PINCTRL_PIN(90, "GP90_GSPI1_MOSI"),
	PINCTRL_PIN(91, "GP91_UART0_RXD"),
	PINCTRL_PIN(92, "GP92_UART0_TXD"),
	PINCTRL_PIN(93, "GP93_UART0_RTSB"),
	PINCTRL_PIN(94, "GP94_UART0_CTSB"),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_community lptlp_communities[] = अणु
	COMMUNITY(0, 95),
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data lptlp_soc_data = अणु
	.pins		= lptlp_pins,
	.npins		= ARRAY_SIZE(lptlp_pins),
	.communities	= lptlp_communities,
	.ncommunities	= ARRAY_SIZE(lptlp_communities),
पूर्ण;

/* LynxPoपूर्णांक chipset has support क्रम 95 GPIO pins */

#घोषणा LP_NUM_GPIO	95

/* Biपंचांगapped रेजिस्टर offsets */
#घोषणा LP_ACPI_OWNED	0x00 /* Biपंचांगap, set by bios, 0: pin reserved क्रम ACPI */
#घोषणा LP_IRQ2IOXAPIC	0x10 /* Biपंचांगap, set by bios, 1: pin routed to IOxAPIC */
#घोषणा LP_GC		0x7C /* set APIC IRQ to IRQ14 or IRQ15 क्रम all pins */
#घोषणा LP_INT_STAT	0x80
#घोषणा LP_INT_ENABLE	0x90

/* Each pin has two 32 bit config रेजिस्टरs, starting at 0x100 */
#घोषणा LP_CONFIG1	0x100
#घोषणा LP_CONFIG2	0x104

/* LP_CONFIG1 reg bits */
#घोषणा OUT_LVL_BIT	BIT(31)
#घोषणा IN_LVL_BIT	BIT(30)
#घोषणा TRIG_SEL_BIT	BIT(4) /* 0: Edge, 1: Level */
#घोषणा INT_INV_BIT	BIT(3) /* Invert पूर्णांकerrupt triggering */
#घोषणा सूची_BIT		BIT(2) /* 0: Output, 1: Input */
#घोषणा USE_SEL_MASK	GENMASK(1, 0)	/* 0: Native, 1: GPIO, ... */
#घोषणा USE_SEL_NATIVE	(0 << 0)
#घोषणा USE_SEL_GPIO	(1 << 0)

/* LP_CONFIG2 reg bits */
#घोषणा GPINDIS_BIT	BIT(2) /* disable input sensing */
#घोषणा GPIWP_MASK	GENMASK(1, 0)	/* weak pull options */
#घोषणा GPIWP_NONE	0		/* none */
#घोषणा GPIWP_DOWN	1		/* weak pull करोwn */
#घोषणा GPIWP_UP	2		/* weak pull up */

/*
 * Lynxpoपूर्णांक gpios are controlled through both biपंचांगapped रेजिस्टरs and
 * per gpio specअगरic रेजिस्टरs. The biपंचांगapped रेजिस्टरs are in chunks of
 * 3 x 32bit रेजिस्टरs to cover all 95 GPIOs
 *
 * per gpio specअगरic रेजिस्टरs consist of two 32bit रेजिस्टरs per gpio
 * (LP_CONFIG1 and LP_CONFIG2), with 95 GPIOs there's a total of
 * 190 config रेजिस्टरs.
 *
 * A simplअगरied view of the रेजिस्टर layout look like this:
 *
 * LP_ACPI_OWNED[31:0] gpio ownerships क्रम gpios 0-31  (biपंचांगapped रेजिस्टरs)
 * LP_ACPI_OWNED[63:32] gpio ownerships क्रम gpios 32-63
 * LP_ACPI_OWNED[94:64] gpio ownerships क्रम gpios 63-94
 * ...
 * LP_INT_ENABLE[31:0] ...
 * LP_INT_ENABLE[63:32] ...
 * LP_INT_ENABLE[94:64] ...
 * LP0_CONFIG1 (gpio 0) config1 reg क्रम gpio 0 (per gpio रेजिस्टरs)
 * LP0_CONFIG2 (gpio 0) config2 reg क्रम gpio 0
 * LP1_CONFIG1 (gpio 1) config1 reg क्रम gpio 1
 * LP1_CONFIG2 (gpio 1) config2 reg क्रम gpio 1
 * LP2_CONFIG1 (gpio 2) ...
 * LP2_CONFIG2 (gpio 2) ...
 * ...
 * LP94_CONFIG1 (gpio 94) ...
 * LP94_CONFIG2 (gpio 94) ...
 *
 * IOxAPIC redirection map applies only क्रम gpio 8-10, 13-14, 45-55.
 */

अटल काष्ठा पूर्णांकel_community *lp_get_community(काष्ठा पूर्णांकel_pinctrl *lg,
						अचिन्हित पूर्णांक pin)
अणु
	काष्ठा पूर्णांकel_community *comm;
	पूर्णांक i;

	क्रम (i = 0; i < lg->ncommunities; i++) अणु
		comm = &lg->communities[i];
		अगर (pin < comm->pin_base + comm->npins && pin >= comm->pin_base)
			वापस comm;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम __iomem *lp_gpio_reg(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
				 पूर्णांक reg)
अणु
	काष्ठा पूर्णांकel_pinctrl *lg = gpiochip_get_data(chip);
	काष्ठा पूर्णांकel_community *comm;
	पूर्णांक reg_offset;

	comm = lp_get_community(lg, offset);
	अगर (!comm)
		वापस शून्य;

	offset -= comm->pin_base;

	अगर (reg == LP_CONFIG1 || reg == LP_CONFIG2)
		/* per gpio specअगरic config रेजिस्टरs */
		reg_offset = offset * 8;
	अन्यथा
		/* biपंचांगapped रेजिस्टरs */
		reg_offset = (offset / 32) * 4;

	वापस comm->regs + reg_offset + reg;
पूर्ण

अटल bool lp_gpio_acpi_use(काष्ठा पूर्णांकel_pinctrl *lg, अचिन्हित पूर्णांक pin)
अणु
	व्योम __iomem *acpi_use;

	acpi_use = lp_gpio_reg(&lg->chip, pin, LP_ACPI_OWNED);
	अगर (!acpi_use)
		वापस true;

	वापस !(ioपढ़ो32(acpi_use) & BIT(pin % 32));
पूर्ण

अटल bool lp_gpio_ioxapic_use(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	व्योम __iomem *ioxapic_use = lp_gpio_reg(chip, offset, LP_IRQ2IOXAPIC);
	u32 value;

	value = ioपढ़ो32(ioxapic_use);

	अगर (offset >= 8 && offset <= 10)
		वापस !!(value & BIT(offset -  8 + 0));
	अगर (offset >= 13 && offset <= 14)
		वापस !!(value & BIT(offset - 13 + 3));
	अगर (offset >= 45 && offset <= 55)
		वापस !!(value & BIT(offset - 45 + 5));

	वापस false;
पूर्ण

अटल पूर्णांक lp_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा पूर्णांकel_pinctrl *lg = pinctrl_dev_get_drvdata(pctldev);

	वापस lg->soc->ngroups;
पूर्ण

अटल स्थिर अक्षर *lp_get_group_name(काष्ठा pinctrl_dev *pctldev,
				     अचिन्हित पूर्णांक selector)
अणु
	काष्ठा पूर्णांकel_pinctrl *lg = pinctrl_dev_get_drvdata(pctldev);

	वापस lg->soc->groups[selector].name;
पूर्ण

अटल पूर्णांक lp_get_group_pins(काष्ठा pinctrl_dev *pctldev,
			     अचिन्हित पूर्णांक selector,
			     स्थिर अचिन्हित पूर्णांक **pins,
			     अचिन्हित पूर्णांक *num_pins)
अणु
	काष्ठा पूर्णांकel_pinctrl *lg = pinctrl_dev_get_drvdata(pctldev);

	*pins		= lg->soc->groups[selector].pins;
	*num_pins	= lg->soc->groups[selector].npins;

	वापस 0;
पूर्ण

अटल व्योम lp_pin_dbg_show(काष्ठा pinctrl_dev *pctldev, काष्ठा seq_file *s,
			    अचिन्हित पूर्णांक pin)
अणु
	काष्ठा पूर्णांकel_pinctrl *lg = pinctrl_dev_get_drvdata(pctldev);
	व्योम __iomem *reg = lp_gpio_reg(&lg->chip, pin, LP_CONFIG1);
	व्योम __iomem *conf2 = lp_gpio_reg(&lg->chip, pin, LP_CONFIG2);
	u32 value, mode;

	value = ioपढ़ो32(reg);

	mode = value & USE_SEL_MASK;
	अगर (mode == USE_SEL_GPIO)
		seq_माला_दो(s, "GPIO ");
	अन्यथा
		seq_म_लिखो(s, "mode %d ", mode);

	seq_म_लिखो(s, "0x%08x 0x%08x", value, ioपढ़ो32(conf2));

	अगर (lp_gpio_acpi_use(lg, pin))
		seq_माला_दो(s, " [ACPI]");
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops lptlp_pinctrl_ops = अणु
	.get_groups_count	= lp_get_groups_count,
	.get_group_name		= lp_get_group_name,
	.get_group_pins		= lp_get_group_pins,
	.pin_dbg_show		= lp_pin_dbg_show,
पूर्ण;

अटल पूर्णांक lp_get_functions_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा पूर्णांकel_pinctrl *lg = pinctrl_dev_get_drvdata(pctldev);

	वापस lg->soc->nfunctions;
पूर्ण

अटल स्थिर अक्षर *lp_get_function_name(काष्ठा pinctrl_dev *pctldev,
					अचिन्हित पूर्णांक selector)
अणु
	काष्ठा पूर्णांकel_pinctrl *lg = pinctrl_dev_get_drvdata(pctldev);

	वापस lg->soc->functions[selector].name;
पूर्ण

अटल पूर्णांक lp_get_function_groups(काष्ठा pinctrl_dev *pctldev,
				  अचिन्हित पूर्णांक selector,
				  स्थिर अक्षर * स्थिर **groups,
				  अचिन्हित पूर्णांक *num_groups)
अणु
	काष्ठा पूर्णांकel_pinctrl *lg = pinctrl_dev_get_drvdata(pctldev);

	*groups		= lg->soc->functions[selector].groups;
	*num_groups	= lg->soc->functions[selector].ngroups;

	वापस 0;
पूर्ण

अटल पूर्णांक lp_pinmux_set_mux(काष्ठा pinctrl_dev *pctldev,
			     अचिन्हित पूर्णांक function, अचिन्हित पूर्णांक group)
अणु
	काष्ठा पूर्णांकel_pinctrl *lg = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा पूर्णांकel_pingroup *grp = &lg->soc->groups[group];
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	raw_spin_lock_irqsave(&lg->lock, flags);

	/* Now enable the mux setting क्रम each pin in the group */
	क्रम (i = 0; i < grp->npins; i++) अणु
		व्योम __iomem *reg = lp_gpio_reg(&lg->chip, grp->pins[i], LP_CONFIG1);
		u32 value;

		value = ioपढ़ो32(reg);

		value &= ~USE_SEL_MASK;
		अगर (grp->modes)
			value |= grp->modes[i];
		अन्यथा
			value |= grp->mode;

		ioग_लिखो32(value, reg);
	पूर्ण

	raw_spin_unlock_irqrestore(&lg->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम lp_gpio_enable_input(व्योम __iomem *reg)
अणु
	ioग_लिखो32(ioपढ़ो32(reg) & ~GPINDIS_BIT, reg);
पूर्ण

अटल व्योम lp_gpio_disable_input(व्योम __iomem *reg)
अणु
	ioग_लिखो32(ioपढ़ो32(reg) | GPINDIS_BIT, reg);
पूर्ण

अटल पूर्णांक lp_gpio_request_enable(काष्ठा pinctrl_dev *pctldev,
				  काष्ठा pinctrl_gpio_range *range,
				  अचिन्हित पूर्णांक pin)
अणु
	काष्ठा पूर्णांकel_pinctrl *lg = pinctrl_dev_get_drvdata(pctldev);
	व्योम __iomem *reg = lp_gpio_reg(&lg->chip, pin, LP_CONFIG1);
	व्योम __iomem *conf2 = lp_gpio_reg(&lg->chip, pin, LP_CONFIG2);
	अचिन्हित दीर्घ flags;
	u32 value;

	pm_runसमय_get(lg->dev);

	raw_spin_lock_irqsave(&lg->lock, flags);

	/*
	 * Reconfigure pin to GPIO mode अगर needed and issue a warning,
	 * since we expect firmware to configure it properly.
	 */
	value = ioपढ़ो32(reg);
	अगर ((value & USE_SEL_MASK) != USE_SEL_GPIO) अणु
		ioग_लिखो32((value & USE_SEL_MASK) | USE_SEL_GPIO, reg);
		dev_warn(lg->dev, FW_BUG "pin %u forcibly reconfigured as GPIO\n", pin);
	पूर्ण

	/* Enable input sensing */
	lp_gpio_enable_input(conf2);

	raw_spin_unlock_irqrestore(&lg->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम lp_gpio_disable_मुक्त(काष्ठा pinctrl_dev *pctldev,
				 काष्ठा pinctrl_gpio_range *range,
				 अचिन्हित पूर्णांक pin)
अणु
	काष्ठा पूर्णांकel_pinctrl *lg = pinctrl_dev_get_drvdata(pctldev);
	व्योम __iomem *conf2 = lp_gpio_reg(&lg->chip, pin, LP_CONFIG2);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&lg->lock, flags);

	/* Disable input sensing */
	lp_gpio_disable_input(conf2);

	raw_spin_unlock_irqrestore(&lg->lock, flags);

	pm_runसमय_put(lg->dev);
पूर्ण

अटल पूर्णांक lp_gpio_set_direction(काष्ठा pinctrl_dev *pctldev,
				 काष्ठा pinctrl_gpio_range *range,
				 अचिन्हित पूर्णांक pin, bool input)
अणु
	काष्ठा पूर्णांकel_pinctrl *lg = pinctrl_dev_get_drvdata(pctldev);
	व्योम __iomem *reg = lp_gpio_reg(&lg->chip, pin, LP_CONFIG1);
	अचिन्हित दीर्घ flags;
	u32 value;

	raw_spin_lock_irqsave(&lg->lock, flags);

	value = ioपढ़ो32(reg);
	value &= ~सूची_BIT;
	अगर (input) अणु
		value |= सूची_BIT;
	पूर्ण अन्यथा अणु
		/*
		 * Beक्रमe making any direction modअगरications, करो a check अगर GPIO
		 * is set क्रम direct IRQ. On Lynxpoपूर्णांक, setting GPIO to output
		 * करोes not make sense, so let's at least warn the caller beक्रमe
		 * they shoot themselves in the foot.
		 */
		WARN(lp_gpio_ioxapic_use(&lg->chip, pin),
		     "Potential Error: Setting GPIO to output with IOxAPIC redirection");
	पूर्ण
	ioग_लिखो32(value, reg);

	raw_spin_unlock_irqrestore(&lg->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops lptlp_pinmux_ops = अणु
	.get_functions_count	= lp_get_functions_count,
	.get_function_name	= lp_get_function_name,
	.get_function_groups	= lp_get_function_groups,
	.set_mux		= lp_pinmux_set_mux,
	.gpio_request_enable	= lp_gpio_request_enable,
	.gpio_disable_मुक्त	= lp_gpio_disable_मुक्त,
	.gpio_set_direction	= lp_gpio_set_direction,
पूर्ण;

अटल पूर्णांक lp_pin_config_get(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
			     अचिन्हित दीर्घ *config)
अणु
	काष्ठा पूर्णांकel_pinctrl *lg = pinctrl_dev_get_drvdata(pctldev);
	व्योम __iomem *conf2 = lp_gpio_reg(&lg->chip, pin, LP_CONFIG2);
	क्रमागत pin_config_param param = pinconf_to_config_param(*config);
	अचिन्हित दीर्घ flags;
	u32 value, pull;
	u16 arg;

	raw_spin_lock_irqsave(&lg->lock, flags);
	value = ioपढ़ो32(conf2);
	raw_spin_unlock_irqrestore(&lg->lock, flags);

	pull = value & GPIWP_MASK;

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		अगर (pull != GPIWP_NONE)
			वापस -EINVAL;
		arg = 0;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		अगर (pull != GPIWP_DOWN)
			वापस -EINVAL;

		arg = 1;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_UP:
		अगर (pull != GPIWP_UP)
			वापस -EINVAL;

		arg = 1;
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	*config = pinconf_to_config_packed(param, arg);

	वापस 0;
पूर्ण

अटल पूर्णांक lp_pin_config_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
			     अचिन्हित दीर्घ *configs, अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा पूर्णांकel_pinctrl *lg = pinctrl_dev_get_drvdata(pctldev);
	व्योम __iomem *conf2 = lp_gpio_reg(&lg->chip, pin, LP_CONFIG2);
	क्रमागत pin_config_param param;
	अचिन्हित दीर्घ flags;
	पूर्णांक i, ret = 0;
	u32 value;

	raw_spin_lock_irqsave(&lg->lock, flags);

	value = ioपढ़ो32(conf2);

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_DISABLE:
			value &= ~GPIWP_MASK;
			value |= GPIWP_NONE;
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			value &= ~GPIWP_MASK;
			value |= GPIWP_DOWN;
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_UP:
			value &= ~GPIWP_MASK;
			value |= GPIWP_UP;
			अवरोध;
		शेष:
			ret = -ENOTSUPP;
		पूर्ण

		अगर (ret)
			अवरोध;
	पूर्ण

	अगर (!ret)
		ioग_लिखो32(value, conf2);

	raw_spin_unlock_irqrestore(&lg->lock, flags);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops lptlp_pinconf_ops = अणु
	.is_generic	= true,
	.pin_config_get	= lp_pin_config_get,
	.pin_config_set	= lp_pin_config_set,
पूर्ण;

अटल स्थिर काष्ठा pinctrl_desc lptlp_pinctrl_desc = अणु
	.pctlops	= &lptlp_pinctrl_ops,
	.pmxops		= &lptlp_pinmux_ops,
	.confops	= &lptlp_pinconf_ops,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक lp_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	व्योम __iomem *reg = lp_gpio_reg(chip, offset, LP_CONFIG1);
	वापस !!(ioपढ़ो32(reg) & IN_LVL_BIT);
पूर्ण

अटल व्योम lp_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा पूर्णांकel_pinctrl *lg = gpiochip_get_data(chip);
	व्योम __iomem *reg = lp_gpio_reg(chip, offset, LP_CONFIG1);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&lg->lock, flags);

	अगर (value)
		ioग_लिखो32(ioपढ़ो32(reg) | OUT_LVL_BIT, reg);
	अन्यथा
		ioग_लिखो32(ioपढ़ो32(reg) & ~OUT_LVL_BIT, reg);

	raw_spin_unlock_irqrestore(&lg->lock, flags);
पूर्ण

अटल पूर्णांक lp_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	वापस pinctrl_gpio_direction_input(chip->base + offset);
पूर्ण

अटल पूर्णांक lp_gpio_direction_output(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
				    पूर्णांक value)
अणु
	lp_gpio_set(chip, offset, value);

	वापस pinctrl_gpio_direction_output(chip->base + offset);
पूर्ण

अटल पूर्णांक lp_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	व्योम __iomem *reg = lp_gpio_reg(chip, offset, LP_CONFIG1);

	अगर (ioपढ़ो32(reg) & सूची_BIT)
		वापस GPIO_LINE_सूचीECTION_IN;

	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल व्योम lp_gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_data *data = irq_desc_get_irq_data(desc);
	काष्ठा gpio_chip *gc = irq_desc_get_handler_data(desc);
	काष्ठा पूर्णांकel_pinctrl *lg = gpiochip_get_data(gc);
	काष्ठा irq_chip *chip = irq_data_get_irq_chip(data);
	व्योम __iomem *reg, *ena;
	अचिन्हित दीर्घ pending;
	u32 base, pin;

	/* check from GPIO controller which pin triggered the पूर्णांकerrupt */
	क्रम (base = 0; base < lg->chip.ngpio; base += 32) अणु
		reg = lp_gpio_reg(&lg->chip, base, LP_INT_STAT);
		ena = lp_gpio_reg(&lg->chip, base, LP_INT_ENABLE);

		/* Only पूर्णांकerrupts that are enabled */
		pending = ioपढ़ो32(reg) & ioपढ़ो32(ena);

		क्रम_each_set_bit(pin, &pending, 32) अणु
			अचिन्हित पूर्णांक irq;

			irq = irq_find_mapping(lg->chip.irq.करोमुख्य, base + pin);
			generic_handle_irq(irq);
		पूर्ण
	पूर्ण
	chip->irq_eoi(data);
पूर्ण

अटल व्योम lp_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा पूर्णांकel_pinctrl *lg = gpiochip_get_data(gc);
	u32 hwirq = irqd_to_hwirq(d);
	व्योम __iomem *reg = lp_gpio_reg(&lg->chip, hwirq, LP_INT_STAT);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&lg->lock, flags);
	ioग_लिखो32(BIT(hwirq % 32), reg);
	raw_spin_unlock_irqrestore(&lg->lock, flags);
पूर्ण

अटल व्योम lp_irq_unmask(काष्ठा irq_data *d)
अणु
पूर्ण

अटल व्योम lp_irq_mask(काष्ठा irq_data *d)
अणु
पूर्ण

अटल व्योम lp_irq_enable(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा पूर्णांकel_pinctrl *lg = gpiochip_get_data(gc);
	u32 hwirq = irqd_to_hwirq(d);
	व्योम __iomem *reg = lp_gpio_reg(&lg->chip, hwirq, LP_INT_ENABLE);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&lg->lock, flags);
	ioग_लिखो32(ioपढ़ो32(reg) | BIT(hwirq % 32), reg);
	raw_spin_unlock_irqrestore(&lg->lock, flags);
पूर्ण

अटल व्योम lp_irq_disable(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा पूर्णांकel_pinctrl *lg = gpiochip_get_data(gc);
	u32 hwirq = irqd_to_hwirq(d);
	व्योम __iomem *reg = lp_gpio_reg(&lg->chip, hwirq, LP_INT_ENABLE);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&lg->lock, flags);
	ioग_लिखो32(ioपढ़ो32(reg) & ~BIT(hwirq % 32), reg);
	raw_spin_unlock_irqrestore(&lg->lock, flags);
पूर्ण

अटल पूर्णांक lp_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा पूर्णांकel_pinctrl *lg = gpiochip_get_data(gc);
	u32 hwirq = irqd_to_hwirq(d);
	व्योम __iomem *reg = lp_gpio_reg(&lg->chip, hwirq, LP_CONFIG1);
	अचिन्हित दीर्घ flags;
	u32 value;

	अगर (hwirq >= lg->chip.ngpio)
		वापस -EINVAL;

	/* Fail अगर BIOS reserved pin क्रम ACPI use */
	अगर (lp_gpio_acpi_use(lg, hwirq)) अणु
		dev_err(lg->dev, "pin %u can't be used as IRQ\n", hwirq);
		वापस -EBUSY;
	पूर्ण

	raw_spin_lock_irqsave(&lg->lock, flags);
	value = ioपढ़ो32(reg);

	/* set both TRIG_SEL and INV bits to 0 क्रम rising edge */
	अगर (type & IRQ_TYPE_EDGE_RISING)
		value &= ~(TRIG_SEL_BIT | INT_INV_BIT);

	/* TRIG_SEL bit 0, INV bit 1 क्रम falling edge */
	अगर (type & IRQ_TYPE_EDGE_FALLING)
		value = (value | INT_INV_BIT) & ~TRIG_SEL_BIT;

	/* TRIG_SEL bit 1, INV bit 0 क्रम level low */
	अगर (type & IRQ_TYPE_LEVEL_LOW)
		value = (value | TRIG_SEL_BIT) & ~INT_INV_BIT;

	/* TRIG_SEL bit 1, INV bit 1 क्रम level high */
	अगर (type & IRQ_TYPE_LEVEL_HIGH)
		value |= TRIG_SEL_BIT | INT_INV_BIT;

	ioग_लिखो32(value, reg);

	अगर (type & IRQ_TYPE_EDGE_BOTH)
		irq_set_handler_locked(d, handle_edge_irq);
	अन्यथा अगर (type & IRQ_TYPE_LEVEL_MASK)
		irq_set_handler_locked(d, handle_level_irq);

	raw_spin_unlock_irqrestore(&lg->lock, flags);

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip lp_irqchip = अणु
	.name = "LP-GPIO",
	.irq_ack = lp_irq_ack,
	.irq_mask = lp_irq_mask,
	.irq_unmask = lp_irq_unmask,
	.irq_enable = lp_irq_enable,
	.irq_disable = lp_irq_disable,
	.irq_set_type = lp_irq_set_type,
	.flags = IRQCHIP_SKIP_SET_WAKE,
पूर्ण;

अटल पूर्णांक lp_gpio_irq_init_hw(काष्ठा gpio_chip *chip)
अणु
	काष्ठा पूर्णांकel_pinctrl *lg = gpiochip_get_data(chip);
	व्योम __iomem *reg;
	अचिन्हित पूर्णांक base;

	क्रम (base = 0; base < lg->chip.ngpio; base += 32) अणु
		/* disable gpio pin पूर्णांकerrupts */
		reg = lp_gpio_reg(&lg->chip, base, LP_INT_ENABLE);
		ioग_लिखो32(0, reg);
		/* Clear पूर्णांकerrupt status रेजिस्टर */
		reg = lp_gpio_reg(&lg->chip, base, LP_INT_STAT);
		ioग_लिखो32(0xffffffff, reg);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lp_gpio_add_pin_ranges(काष्ठा gpio_chip *chip)
अणु
	काष्ठा पूर्णांकel_pinctrl *lg = gpiochip_get_data(chip);
	काष्ठा device *dev = lg->dev;
	पूर्णांक ret;

	ret = gpiochip_add_pin_range(chip, dev_name(dev), 0, 0, lg->soc->npins);
	अगर (ret)
		dev_err(dev, "failed to add GPIO pin range\n");

	वापस ret;
पूर्ण

अटल पूर्णांक lp_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data *soc;
	काष्ठा पूर्णांकel_pinctrl *lg;
	काष्ठा gpio_chip *gc;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *io_rc;
	व्योम __iomem *regs;
	अचिन्हित पूर्णांक i;
	पूर्णांक irq, ret;

	soc = (स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data *)device_get_match_data(dev);
	अगर (!soc)
		वापस -ENODEV;

	lg = devm_kzalloc(dev, माप(*lg), GFP_KERNEL);
	अगर (!lg)
		वापस -ENOMEM;

	lg->dev = dev;
	lg->soc = soc;

	lg->ncommunities = lg->soc->ncommunities;
	lg->communities = devm_kसुस्मृति(dev, lg->ncommunities,
				       माप(*lg->communities), GFP_KERNEL);
	अगर (!lg->communities)
		वापस -ENOMEM;

	lg->pctldesc           = lptlp_pinctrl_desc;
	lg->pctldesc.name      = dev_name(dev);
	lg->pctldesc.pins      = lg->soc->pins;
	lg->pctldesc.npins     = lg->soc->npins;

	lg->pctldev = devm_pinctrl_रेजिस्टर(dev, &lg->pctldesc, lg);
	अगर (IS_ERR(lg->pctldev)) अणु
		dev_err(dev, "failed to register pinctrl driver\n");
		वापस PTR_ERR(lg->pctldev);
	पूर्ण

	platक्रमm_set_drvdata(pdev, lg);

	io_rc = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (!io_rc) अणु
		dev_err(dev, "missing IO resources\n");
		वापस -EINVAL;
	पूर्ण

	regs = devm_ioport_map(dev, io_rc->start, resource_size(io_rc));
	अगर (!regs) अणु
		dev_err(dev, "failed mapping IO region %pR\n", &io_rc);
		वापस -EBUSY;
	पूर्ण

	क्रम (i = 0; i < lg->soc->ncommunities; i++) अणु
		काष्ठा पूर्णांकel_community *comm = &lg->communities[i];

		*comm = lg->soc->communities[i];

		comm->regs = regs;
		comm->pad_regs = regs + 0x100;
	पूर्ण

	raw_spin_lock_init(&lg->lock);

	gc = &lg->chip;
	gc->label = dev_name(dev);
	gc->owner = THIS_MODULE;
	gc->request = gpiochip_generic_request;
	gc->मुक्त = gpiochip_generic_मुक्त;
	gc->direction_input = lp_gpio_direction_input;
	gc->direction_output = lp_gpio_direction_output;
	gc->get = lp_gpio_get;
	gc->set = lp_gpio_set;
	gc->set_config = gpiochip_generic_config;
	gc->get_direction = lp_gpio_get_direction;
	gc->base = -1;
	gc->ngpio = LP_NUM_GPIO;
	gc->can_sleep = false;
	gc->add_pin_ranges = lp_gpio_add_pin_ranges;
	gc->parent = dev;

	/* set up पूर्णांकerrupts  */
	irq = platक्रमm_get_irq_optional(pdev, 0);
	अगर (irq > 0) अणु
		काष्ठा gpio_irq_chip *girq;

		girq = &gc->irq;
		girq->chip = &lp_irqchip;
		girq->init_hw = lp_gpio_irq_init_hw;
		girq->parent_handler = lp_gpio_irq_handler;
		girq->num_parents = 1;
		girq->parents = devm_kसुस्मृति(dev, girq->num_parents,
					     माप(*girq->parents),
					     GFP_KERNEL);
		अगर (!girq->parents)
			वापस -ENOMEM;
		girq->parents[0] = irq;
		girq->शेष_type = IRQ_TYPE_NONE;
		girq->handler = handle_bad_irq;
	पूर्ण

	ret = devm_gpiochip_add_data(dev, gc, lg);
	अगर (ret) अणु
		dev_err(dev, "failed adding lp-gpio chip\n");
		वापस ret;
	पूर्ण

	pm_runसमय_enable(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक lp_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक lp_gpio_runसमय_suspend(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक lp_gpio_runसमय_resume(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक lp_gpio_resume(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_pinctrl *lg = dev_get_drvdata(dev);
	काष्ठा gpio_chip *chip = &lg->chip;
	स्थिर अक्षर *dummy;
	पूर्णांक i;

	/* on some hardware suspend clears input sensing, re-enable it here */
	क्रम_each_requested_gpio(chip, i, dummy)
		lp_gpio_enable_input(lp_gpio_reg(chip, i, LP_CONFIG2));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops lp_gpio_pm_ops = अणु
	.runसमय_suspend = lp_gpio_runसमय_suspend,
	.runसमय_resume = lp_gpio_runसमय_resume,
	.resume = lp_gpio_resume,
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id lynxpoपूर्णांक_gpio_acpi_match[] = अणु
	अणु "INT33C7", (kernel_uदीर्घ_t)&lptlp_soc_data पूर्ण,
	अणु "INT3437", (kernel_uदीर्घ_t)&lptlp_soc_data पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, lynxpoपूर्णांक_gpio_acpi_match);

अटल काष्ठा platक्रमm_driver lp_gpio_driver = अणु
	.probe          = lp_gpio_probe,
	.हटाओ         = lp_gpio_हटाओ,
	.driver         = अणु
		.name   = "lp_gpio",
		.pm	= &lp_gpio_pm_ops,
		.acpi_match_table = lynxpoपूर्णांक_gpio_acpi_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init lp_gpio_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&lp_gpio_driver);
पूर्ण
subsys_initcall(lp_gpio_init);

अटल व्योम __निकास lp_gpio_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&lp_gpio_driver);
पूर्ण
module_निकास(lp_gpio_निकास);

MODULE_AUTHOR("Mathias Nyman (Intel)");
MODULE_AUTHOR("Andy Shevchenko (Intel)");
MODULE_DESCRIPTION("Intel Lynxpoint pinctrl driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:lp_gpio");
