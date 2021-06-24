<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * GPIO driver क्रम LPC32xx SoC
 *
 * Author: Kevin Wells <kevin.wells@nxp.com>
 *
 * Copyright (C) 2010 NXP Semiconductors
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>

#घोषणा LPC32XX_GPIO_P3_INP_STATE		(0x000)
#घोषणा LPC32XX_GPIO_P3_OUTP_SET		(0x004)
#घोषणा LPC32XX_GPIO_P3_OUTP_CLR		(0x008)
#घोषणा LPC32XX_GPIO_P3_OUTP_STATE		(0x00C)
#घोषणा LPC32XX_GPIO_P2_सूची_SET			(0x010)
#घोषणा LPC32XX_GPIO_P2_सूची_CLR			(0x014)
#घोषणा LPC32XX_GPIO_P2_सूची_STATE		(0x018)
#घोषणा LPC32XX_GPIO_P2_INP_STATE		(0x01C)
#घोषणा LPC32XX_GPIO_P2_OUTP_SET		(0x020)
#घोषणा LPC32XX_GPIO_P2_OUTP_CLR		(0x024)
#घोषणा LPC32XX_GPIO_P2_MUX_SET			(0x028)
#घोषणा LPC32XX_GPIO_P2_MUX_CLR			(0x02C)
#घोषणा LPC32XX_GPIO_P2_MUX_STATE		(0x030)
#घोषणा LPC32XX_GPIO_P0_INP_STATE		(0x040)
#घोषणा LPC32XX_GPIO_P0_OUTP_SET		(0x044)
#घोषणा LPC32XX_GPIO_P0_OUTP_CLR		(0x048)
#घोषणा LPC32XX_GPIO_P0_OUTP_STATE		(0x04C)
#घोषणा LPC32XX_GPIO_P0_सूची_SET			(0x050)
#घोषणा LPC32XX_GPIO_P0_सूची_CLR			(0x054)
#घोषणा LPC32XX_GPIO_P0_सूची_STATE		(0x058)
#घोषणा LPC32XX_GPIO_P1_INP_STATE		(0x060)
#घोषणा LPC32XX_GPIO_P1_OUTP_SET		(0x064)
#घोषणा LPC32XX_GPIO_P1_OUTP_CLR		(0x068)
#घोषणा LPC32XX_GPIO_P1_OUTP_STATE		(0x06C)
#घोषणा LPC32XX_GPIO_P1_सूची_SET			(0x070)
#घोषणा LPC32XX_GPIO_P1_सूची_CLR			(0x074)
#घोषणा LPC32XX_GPIO_P1_सूची_STATE		(0x078)

#घोषणा GPIO012_PIN_TO_BIT(x)			(1 << (x))
#घोषणा GPIO3_PIN_TO_BIT(x)			(1 << ((x) + 25))
#घोषणा GPO3_PIN_TO_BIT(x)			(1 << (x))
#घोषणा GPIO012_PIN_IN_SEL(x, y)		(((x) >> (y)) & 1)
#घोषणा GPIO3_PIN_IN_SHIFT(x)			((x) == 5 ? 24 : 10 + (x))
#घोषणा GPIO3_PIN_IN_SEL(x, y)			(((x) >> GPIO3_PIN_IN_SHIFT(y)) & 1)
#घोषणा GPIO3_PIN5_IN_SEL(x)			(((x) >> 24) & 1)
#घोषणा GPI3_PIN_IN_SEL(x, y)			(((x) >> (y)) & 1)
#घोषणा GPO3_PIN_IN_SEL(x, y)			(((x) >> (y)) & 1)

#घोषणा LPC32XX_GPIO_P0_MAX	8
#घोषणा LPC32XX_GPIO_P1_MAX	24
#घोषणा LPC32XX_GPIO_P2_MAX	13
#घोषणा LPC32XX_GPIO_P3_MAX	6
#घोषणा LPC32XX_GPI_P3_MAX	29
#घोषणा LPC32XX_GPO_P3_MAX	24

#घोषणा LPC32XX_GPIO_P0_GRP	0
#घोषणा LPC32XX_GPIO_P1_GRP	(LPC32XX_GPIO_P0_GRP + LPC32XX_GPIO_P0_MAX)
#घोषणा LPC32XX_GPIO_P2_GRP	(LPC32XX_GPIO_P1_GRP + LPC32XX_GPIO_P1_MAX)
#घोषणा LPC32XX_GPIO_P3_GRP	(LPC32XX_GPIO_P2_GRP + LPC32XX_GPIO_P2_MAX)
#घोषणा LPC32XX_GPI_P3_GRP	(LPC32XX_GPIO_P3_GRP + LPC32XX_GPIO_P3_MAX)
#घोषणा LPC32XX_GPO_P3_GRP	(LPC32XX_GPI_P3_GRP + LPC32XX_GPI_P3_MAX)

काष्ठा gpio_regs अणु
	अचिन्हित दीर्घ inp_state;
	अचिन्हित दीर्घ outp_state;
	अचिन्हित दीर्घ outp_set;
	अचिन्हित दीर्घ outp_clr;
	अचिन्हित दीर्घ dir_set;
	अचिन्हित दीर्घ dir_clr;
पूर्ण;

/*
 * GPIO names
 */
अटल स्थिर अक्षर *gpio_p0_names[LPC32XX_GPIO_P0_MAX] = अणु
	"p0.0", "p0.1", "p0.2", "p0.3",
	"p0.4", "p0.5", "p0.6", "p0.7"
पूर्ण;

अटल स्थिर अक्षर *gpio_p1_names[LPC32XX_GPIO_P1_MAX] = अणु
	"p1.0", "p1.1", "p1.2", "p1.3",
	"p1.4", "p1.5", "p1.6", "p1.7",
	"p1.8", "p1.9", "p1.10", "p1.11",
	"p1.12", "p1.13", "p1.14", "p1.15",
	"p1.16", "p1.17", "p1.18", "p1.19",
	"p1.20", "p1.21", "p1.22", "p1.23",
पूर्ण;

अटल स्थिर अक्षर *gpio_p2_names[LPC32XX_GPIO_P2_MAX] = अणु
	"p2.0", "p2.1", "p2.2", "p2.3",
	"p2.4", "p2.5", "p2.6", "p2.7",
	"p2.8", "p2.9", "p2.10", "p2.11",
	"p2.12"
पूर्ण;

अटल स्थिर अक्षर *gpio_p3_names[LPC32XX_GPIO_P3_MAX] = अणु
	"gpio00", "gpio01", "gpio02", "gpio03",
	"gpio04", "gpio05"
पूर्ण;

अटल स्थिर अक्षर *gpi_p3_names[LPC32XX_GPI_P3_MAX] = अणु
	"gpi00", "gpi01", "gpi02", "gpi03",
	"gpi04", "gpi05", "gpi06", "gpi07",
	"gpi08", "gpi09",  शून्य,    शून्य,
	 शून्य,    शून्य,    शून्य,   "gpi15",
	"gpi16", "gpi17", "gpi18", "gpi19",
	"gpi20", "gpi21", "gpi22", "gpi23",
	"gpi24", "gpi25", "gpi26", "gpi27",
	"gpi28"
पूर्ण;

अटल स्थिर अक्षर *gpo_p3_names[LPC32XX_GPO_P3_MAX] = अणु
	"gpo00", "gpo01", "gpo02", "gpo03",
	"gpo04", "gpo05", "gpo06", "gpo07",
	"gpo08", "gpo09", "gpo10", "gpo11",
	"gpo12", "gpo13", "gpo14", "gpo15",
	"gpo16", "gpo17", "gpo18", "gpo19",
	"gpo20", "gpo21", "gpo22", "gpo23"
पूर्ण;

अटल काष्ठा gpio_regs gpio_grp_regs_p0 = अणु
	.inp_state	= LPC32XX_GPIO_P0_INP_STATE,
	.outp_set	= LPC32XX_GPIO_P0_OUTP_SET,
	.outp_clr	= LPC32XX_GPIO_P0_OUTP_CLR,
	.dir_set	= LPC32XX_GPIO_P0_सूची_SET,
	.dir_clr	= LPC32XX_GPIO_P0_सूची_CLR,
पूर्ण;

अटल काष्ठा gpio_regs gpio_grp_regs_p1 = अणु
	.inp_state	= LPC32XX_GPIO_P1_INP_STATE,
	.outp_set	= LPC32XX_GPIO_P1_OUTP_SET,
	.outp_clr	= LPC32XX_GPIO_P1_OUTP_CLR,
	.dir_set	= LPC32XX_GPIO_P1_सूची_SET,
	.dir_clr	= LPC32XX_GPIO_P1_सूची_CLR,
पूर्ण;

अटल काष्ठा gpio_regs gpio_grp_regs_p2 = अणु
	.inp_state	= LPC32XX_GPIO_P2_INP_STATE,
	.outp_set	= LPC32XX_GPIO_P2_OUTP_SET,
	.outp_clr	= LPC32XX_GPIO_P2_OUTP_CLR,
	.dir_set	= LPC32XX_GPIO_P2_सूची_SET,
	.dir_clr	= LPC32XX_GPIO_P2_सूची_CLR,
पूर्ण;

अटल काष्ठा gpio_regs gpio_grp_regs_p3 = अणु
	.inp_state	= LPC32XX_GPIO_P3_INP_STATE,
	.outp_state	= LPC32XX_GPIO_P3_OUTP_STATE,
	.outp_set	= LPC32XX_GPIO_P3_OUTP_SET,
	.outp_clr	= LPC32XX_GPIO_P3_OUTP_CLR,
	.dir_set	= LPC32XX_GPIO_P2_सूची_SET,
	.dir_clr	= LPC32XX_GPIO_P2_सूची_CLR,
पूर्ण;

काष्ठा lpc32xx_gpio_chip अणु
	काष्ठा gpio_chip	chip;
	काष्ठा gpio_regs	*gpio_grp;
	व्योम __iomem		*reg_base;
पूर्ण;

अटल अंतरभूत u32 gpreg_पढ़ो(काष्ठा lpc32xx_gpio_chip *group, अचिन्हित दीर्घ offset)
अणु
	वापस __raw_पढ़ोl(group->reg_base + offset);
पूर्ण

अटल अंतरभूत व्योम gpreg_ग_लिखो(काष्ठा lpc32xx_gpio_chip *group, u32 val, अचिन्हित दीर्घ offset)
अणु
	__raw_ग_लिखोl(val, group->reg_base + offset);
पूर्ण

अटल व्योम __set_gpio_dir_p012(काष्ठा lpc32xx_gpio_chip *group,
	अचिन्हित pin, पूर्णांक input)
अणु
	अगर (input)
		gpreg_ग_लिखो(group, GPIO012_PIN_TO_BIT(pin),
			group->gpio_grp->dir_clr);
	अन्यथा
		gpreg_ग_लिखो(group, GPIO012_PIN_TO_BIT(pin),
			group->gpio_grp->dir_set);
पूर्ण

अटल व्योम __set_gpio_dir_p3(काष्ठा lpc32xx_gpio_chip *group,
	अचिन्हित pin, पूर्णांक input)
अणु
	u32 u = GPIO3_PIN_TO_BIT(pin);

	अगर (input)
		gpreg_ग_लिखो(group, u, group->gpio_grp->dir_clr);
	अन्यथा
		gpreg_ग_लिखो(group, u, group->gpio_grp->dir_set);
पूर्ण

अटल व्योम __set_gpio_level_p012(काष्ठा lpc32xx_gpio_chip *group,
	अचिन्हित pin, पूर्णांक high)
अणु
	अगर (high)
		gpreg_ग_लिखो(group, GPIO012_PIN_TO_BIT(pin),
			group->gpio_grp->outp_set);
	अन्यथा
		gpreg_ग_लिखो(group, GPIO012_PIN_TO_BIT(pin),
			group->gpio_grp->outp_clr);
पूर्ण

अटल व्योम __set_gpio_level_p3(काष्ठा lpc32xx_gpio_chip *group,
	अचिन्हित pin, पूर्णांक high)
अणु
	u32 u = GPIO3_PIN_TO_BIT(pin);

	अगर (high)
		gpreg_ग_लिखो(group, u, group->gpio_grp->outp_set);
	अन्यथा
		gpreg_ग_लिखो(group, u, group->gpio_grp->outp_clr);
पूर्ण

अटल व्योम __set_gpo_level_p3(काष्ठा lpc32xx_gpio_chip *group,
	अचिन्हित pin, पूर्णांक high)
अणु
	अगर (high)
		gpreg_ग_लिखो(group, GPO3_PIN_TO_BIT(pin), group->gpio_grp->outp_set);
	अन्यथा
		gpreg_ग_लिखो(group, GPO3_PIN_TO_BIT(pin), group->gpio_grp->outp_clr);
पूर्ण

अटल पूर्णांक __get_gpio_state_p012(काष्ठा lpc32xx_gpio_chip *group,
	अचिन्हित pin)
अणु
	वापस GPIO012_PIN_IN_SEL(gpreg_पढ़ो(group, group->gpio_grp->inp_state),
		pin);
पूर्ण

अटल पूर्णांक __get_gpio_state_p3(काष्ठा lpc32xx_gpio_chip *group,
	अचिन्हित pin)
अणु
	पूर्णांक state = gpreg_पढ़ो(group, group->gpio_grp->inp_state);

	/*
	 * P3 GPIO pin input mapping is not contiguous, GPIOP3-0..4 is mapped
	 * to bits 10..14, जबतक GPIOP3-5 is mapped to bit 24.
	 */
	वापस GPIO3_PIN_IN_SEL(state, pin);
पूर्ण

अटल पूर्णांक __get_gpi_state_p3(काष्ठा lpc32xx_gpio_chip *group,
	अचिन्हित pin)
अणु
	वापस GPI3_PIN_IN_SEL(gpreg_पढ़ो(group, group->gpio_grp->inp_state), pin);
पूर्ण

अटल पूर्णांक __get_gpo_state_p3(काष्ठा lpc32xx_gpio_chip *group,
	अचिन्हित pin)
अणु
	वापस GPO3_PIN_IN_SEL(gpreg_पढ़ो(group, group->gpio_grp->outp_state), pin);
पूर्ण

/*
 * GPIO primitives.
 */
अटल पूर्णांक lpc32xx_gpio_dir_input_p012(काष्ठा gpio_chip *chip,
	अचिन्हित pin)
अणु
	काष्ठा lpc32xx_gpio_chip *group = gpiochip_get_data(chip);

	__set_gpio_dir_p012(group, pin, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc32xx_gpio_dir_input_p3(काष्ठा gpio_chip *chip,
	अचिन्हित pin)
अणु
	काष्ठा lpc32xx_gpio_chip *group = gpiochip_get_data(chip);

	__set_gpio_dir_p3(group, pin, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc32xx_gpio_dir_in_always(काष्ठा gpio_chip *chip,
	अचिन्हित pin)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक lpc32xx_gpio_get_value_p012(काष्ठा gpio_chip *chip, अचिन्हित pin)
अणु
	काष्ठा lpc32xx_gpio_chip *group = gpiochip_get_data(chip);

	वापस !!__get_gpio_state_p012(group, pin);
पूर्ण

अटल पूर्णांक lpc32xx_gpio_get_value_p3(काष्ठा gpio_chip *chip, अचिन्हित pin)
अणु
	काष्ठा lpc32xx_gpio_chip *group = gpiochip_get_data(chip);

	वापस !!__get_gpio_state_p3(group, pin);
पूर्ण

अटल पूर्णांक lpc32xx_gpi_get_value(काष्ठा gpio_chip *chip, अचिन्हित pin)
अणु
	काष्ठा lpc32xx_gpio_chip *group = gpiochip_get_data(chip);

	वापस !!__get_gpi_state_p3(group, pin);
पूर्ण

अटल पूर्णांक lpc32xx_gpio_dir_output_p012(काष्ठा gpio_chip *chip, अचिन्हित pin,
	पूर्णांक value)
अणु
	काष्ठा lpc32xx_gpio_chip *group = gpiochip_get_data(chip);

	__set_gpio_level_p012(group, pin, value);
	__set_gpio_dir_p012(group, pin, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc32xx_gpio_dir_output_p3(काष्ठा gpio_chip *chip, अचिन्हित pin,
	पूर्णांक value)
अणु
	काष्ठा lpc32xx_gpio_chip *group = gpiochip_get_data(chip);

	__set_gpio_level_p3(group, pin, value);
	__set_gpio_dir_p3(group, pin, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc32xx_gpio_dir_out_always(काष्ठा gpio_chip *chip, अचिन्हित pin,
	पूर्णांक value)
अणु
	काष्ठा lpc32xx_gpio_chip *group = gpiochip_get_data(chip);

	__set_gpo_level_p3(group, pin, value);
	वापस 0;
पूर्ण

अटल व्योम lpc32xx_gpio_set_value_p012(काष्ठा gpio_chip *chip, अचिन्हित pin,
	पूर्णांक value)
अणु
	काष्ठा lpc32xx_gpio_chip *group = gpiochip_get_data(chip);

	__set_gpio_level_p012(group, pin, value);
पूर्ण

अटल व्योम lpc32xx_gpio_set_value_p3(काष्ठा gpio_chip *chip, अचिन्हित pin,
	पूर्णांक value)
अणु
	काष्ठा lpc32xx_gpio_chip *group = gpiochip_get_data(chip);

	__set_gpio_level_p3(group, pin, value);
पूर्ण

अटल व्योम lpc32xx_gpo_set_value(काष्ठा gpio_chip *chip, अचिन्हित pin,
	पूर्णांक value)
अणु
	काष्ठा lpc32xx_gpio_chip *group = gpiochip_get_data(chip);

	__set_gpo_level_p3(group, pin, value);
पूर्ण

अटल पूर्णांक lpc32xx_gpo_get_value(काष्ठा gpio_chip *chip, अचिन्हित pin)
अणु
	काष्ठा lpc32xx_gpio_chip *group = gpiochip_get_data(chip);

	वापस !!__get_gpo_state_p3(group, pin);
पूर्ण

अटल पूर्णांक lpc32xx_gpio_request(काष्ठा gpio_chip *chip, अचिन्हित pin)
अणु
	अगर (pin < chip->ngpio)
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक lpc32xx_gpio_to_irq_p01(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस -ENXIO;
पूर्ण

अटल पूर्णांक lpc32xx_gpio_to_irq_gpio_p3(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस -ENXIO;
पूर्ण

अटल पूर्णांक lpc32xx_gpio_to_irq_gpi_p3(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस -ENXIO;
पूर्ण

अटल काष्ठा lpc32xx_gpio_chip lpc32xx_gpiochip[] = अणु
	अणु
		.chip = अणु
			.label			= "gpio_p0",
			.direction_input	= lpc32xx_gpio_dir_input_p012,
			.get			= lpc32xx_gpio_get_value_p012,
			.direction_output	= lpc32xx_gpio_dir_output_p012,
			.set			= lpc32xx_gpio_set_value_p012,
			.request		= lpc32xx_gpio_request,
			.to_irq			= lpc32xx_gpio_to_irq_p01,
			.base			= LPC32XX_GPIO_P0_GRP,
			.ngpio			= LPC32XX_GPIO_P0_MAX,
			.names			= gpio_p0_names,
			.can_sleep		= false,
		पूर्ण,
		.gpio_grp = &gpio_grp_regs_p0,
	पूर्ण,
	अणु
		.chip = अणु
			.label			= "gpio_p1",
			.direction_input	= lpc32xx_gpio_dir_input_p012,
			.get			= lpc32xx_gpio_get_value_p012,
			.direction_output	= lpc32xx_gpio_dir_output_p012,
			.set			= lpc32xx_gpio_set_value_p012,
			.request		= lpc32xx_gpio_request,
			.to_irq			= lpc32xx_gpio_to_irq_p01,
			.base			= LPC32XX_GPIO_P1_GRP,
			.ngpio			= LPC32XX_GPIO_P1_MAX,
			.names			= gpio_p1_names,
			.can_sleep		= false,
		पूर्ण,
		.gpio_grp = &gpio_grp_regs_p1,
	पूर्ण,
	अणु
		.chip = अणु
			.label			= "gpio_p2",
			.direction_input	= lpc32xx_gpio_dir_input_p012,
			.get			= lpc32xx_gpio_get_value_p012,
			.direction_output	= lpc32xx_gpio_dir_output_p012,
			.set			= lpc32xx_gpio_set_value_p012,
			.request		= lpc32xx_gpio_request,
			.base			= LPC32XX_GPIO_P2_GRP,
			.ngpio			= LPC32XX_GPIO_P2_MAX,
			.names			= gpio_p2_names,
			.can_sleep		= false,
		पूर्ण,
		.gpio_grp = &gpio_grp_regs_p2,
	पूर्ण,
	अणु
		.chip = अणु
			.label			= "gpio_p3",
			.direction_input	= lpc32xx_gpio_dir_input_p3,
			.get			= lpc32xx_gpio_get_value_p3,
			.direction_output	= lpc32xx_gpio_dir_output_p3,
			.set			= lpc32xx_gpio_set_value_p3,
			.request		= lpc32xx_gpio_request,
			.to_irq			= lpc32xx_gpio_to_irq_gpio_p3,
			.base			= LPC32XX_GPIO_P3_GRP,
			.ngpio			= LPC32XX_GPIO_P3_MAX,
			.names			= gpio_p3_names,
			.can_sleep		= false,
		पूर्ण,
		.gpio_grp = &gpio_grp_regs_p3,
	पूर्ण,
	अणु
		.chip = अणु
			.label			= "gpi_p3",
			.direction_input	= lpc32xx_gpio_dir_in_always,
			.get			= lpc32xx_gpi_get_value,
			.request		= lpc32xx_gpio_request,
			.to_irq			= lpc32xx_gpio_to_irq_gpi_p3,
			.base			= LPC32XX_GPI_P3_GRP,
			.ngpio			= LPC32XX_GPI_P3_MAX,
			.names			= gpi_p3_names,
			.can_sleep		= false,
		पूर्ण,
		.gpio_grp = &gpio_grp_regs_p3,
	पूर्ण,
	अणु
		.chip = अणु
			.label			= "gpo_p3",
			.direction_output	= lpc32xx_gpio_dir_out_always,
			.set			= lpc32xx_gpo_set_value,
			.get			= lpc32xx_gpo_get_value,
			.request		= lpc32xx_gpio_request,
			.base			= LPC32XX_GPO_P3_GRP,
			.ngpio			= LPC32XX_GPO_P3_MAX,
			.names			= gpo_p3_names,
			.can_sleep		= false,
		पूर्ण,
		.gpio_grp = &gpio_grp_regs_p3,
	पूर्ण,
पूर्ण;

अटल पूर्णांक lpc32xx_of_xlate(काष्ठा gpio_chip *gc,
			    स्थिर काष्ठा of_phandle_args *gpiospec, u32 *flags)
अणु
	/* Is this the correct bank? */
	u32 bank = gpiospec->args[0];
	अगर ((bank >= ARRAY_SIZE(lpc32xx_gpiochip) ||
	    (gc != &lpc32xx_gpiochip[bank].chip)))
		वापस -EINVAL;

	अगर (flags)
		*flags = gpiospec->args[2];
	वापस gpiospec->args[1];
पूर्ण

अटल पूर्णांक lpc32xx_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i;
	व्योम __iomem *reg_base;

	reg_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(reg_base))
		वापस PTR_ERR(reg_base);

	क्रम (i = 0; i < ARRAY_SIZE(lpc32xx_gpiochip); i++) अणु
		अगर (pdev->dev.of_node) अणु
			lpc32xx_gpiochip[i].chip.of_xlate = lpc32xx_of_xlate;
			lpc32xx_gpiochip[i].chip.of_gpio_n_cells = 3;
			lpc32xx_gpiochip[i].chip.of_node = pdev->dev.of_node;
			lpc32xx_gpiochip[i].reg_base = reg_base;
		पूर्ण
		devm_gpiochip_add_data(&pdev->dev, &lpc32xx_gpiochip[i].chip,
				  &lpc32xx_gpiochip[i]);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id lpc32xx_gpio_of_match[] = अणु
	अणु .compatible = "nxp,lpc3220-gpio", पूर्ण,
	अणु पूर्ण,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver lpc32xx_gpio_driver = अणु
	.driver		= अणु
		.name	= "lpc32xx-gpio",
		.of_match_table = of_match_ptr(lpc32xx_gpio_of_match),
	पूर्ण,
	.probe		= lpc32xx_gpio_probe,
पूर्ण;

module_platक्रमm_driver(lpc32xx_gpio_driver);

MODULE_AUTHOR("Kevin Wells <kevin.wells@nxp.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("GPIO driver for LPC32xx SoC");
