<शैली गुरु>
/* Copyright (C) 2015 Broadcom Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * This file contains the Northstar plus (NSP) IOMUX driver that supports
 * group based PINMUX configuration. The Northstar plus IOMUX controller
 * allows pins to be inभागidually muxed to GPIO function. The न_अंकD and MMC is
 * a group based selection. The gpio_a 8 - 11 are muxed with gpio_b and pwm.
 * To select PWM, one need to enable the corresponding gpio_b as well.
 *
 *				gpio_a (8 - 11)
 *				+----------
 *				|
 *		gpio_a (8-11)	|	gpio_b (0 - 3)
 *	------------------------+-------+----------
 *					|
 *					|	pwm (0 - 3)
 *					+----------
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "../core.h"
#समावेश "../pinctrl-utils.h"

#घोषणा NSP_MUX_BASE0	0x00
#घोषणा NSP_MUX_BASE1	0x01
#घोषणा NSP_MUX_BASE2	0x02
/*
 * nsp IOMUX रेजिस्टर description
 *
 * @base: base 0 or base 1
 * @shअगरt: bit shअगरt क्रम mux configuration of a group
 * @mask: bit mask of the function
 * @alt: alternate function to set to
 */
काष्ठा nsp_mux अणु
	अचिन्हित पूर्णांक base;
	अचिन्हित पूर्णांक shअगरt;
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक alt;
पूर्ण;

/*
 * Keep track of nsp IOMUX configuration and prevent द्विगुन configuration
 *
 * @nsp_mux: nsp IOMUX रेजिस्टर description
 * @is_configured: flag to indicate whether a mux setting has alपढ़ोy been
 * configured
 */
काष्ठा nsp_mux_log अणु
	काष्ठा nsp_mux mux;
	bool is_configured;
पूर्ण;

/*
 * Group based IOMUX configuration
 *
 * @name: name of the group
 * @pins: array of pins used by this group
 * @num_pins: total number of pins used by this group
 * @mux: nsp group based IOMUX configuration
 */
काष्ठा nsp_pin_group अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित पूर्णांक *pins;
	स्थिर अचिन्हित पूर्णांक num_pins;
	स्थिर काष्ठा nsp_mux mux;
पूर्ण;

/*
 * nsp mux function and supported pin groups
 *
 * @name: name of the function
 * @groups: array of groups that can be supported by this function
 * @num_groups: total number of groups that can be supported by this function
 */
काष्ठा nsp_pin_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *groups;
	स्थिर अचिन्हित पूर्णांक num_groups;
पूर्ण;

/*
 * nsp IOMUX pinctrl core
 *
 * @pctl: poपूर्णांकer to pinctrl_dev
 * @dev: poपूर्णांकer to device
 * @base0: first mux रेजिस्टर
 * @base1: second mux रेजिस्टर
 * @base2: third mux रेजिस्टर
 * @groups: poपूर्णांकer to array of groups
 * @num_groups: total number of groups
 * @functions: poपूर्णांकer to array of functions
 * @num_functions: total number of functions
 * @mux_log: poपूर्णांकer to the array of mux logs
 * @lock: lock to protect रेजिस्टर access
 */
काष्ठा nsp_pinctrl अणु
	काष्ठा pinctrl_dev *pctl;
	काष्ठा device *dev;
	व्योम __iomem *base0;
	व्योम __iomem *base1;
	व्योम __iomem *base2;
	स्थिर काष्ठा nsp_pin_group *groups;
	अचिन्हित पूर्णांक num_groups;
	स्थिर काष्ठा nsp_pin_function *functions;
	अचिन्हित पूर्णांक num_functions;
	काष्ठा nsp_mux_log *mux_log;
	spinlock_t lock;
पूर्ण;

/*
 * Description of a pin in nsp
 *
 * @pin: pin number
 * @name: pin name
 * @gpio_select: reg data to select GPIO
 */
काष्ठा nsp_pin अणु
	अचिन्हित पूर्णांक pin;
	अक्षर *name;
	अचिन्हित पूर्णांक gpio_select;
पूर्ण;

#घोषणा NSP_PIN_DESC(p, n, g)		\
अणु					\
	.pin = p,			\
	.name = n,			\
	.gpio_select = g,		\
पूर्ण

/*
 * List of muxable pins in nsp
 */
अटल काष्ठा nsp_pin nsp_pins[] = अणु
	NSP_PIN_DESC(0, "spi_clk", 1),
	NSP_PIN_DESC(1, "spi_ss", 1),
	NSP_PIN_DESC(2, "spi_mosi", 1),
	NSP_PIN_DESC(3, "spi_miso", 1),
	NSP_PIN_DESC(4, "scl", 1),
	NSP_PIN_DESC(5, "sda", 1),
	NSP_PIN_DESC(6, "mdc", 1),
	NSP_PIN_DESC(7, "mdio", 1),
	NSP_PIN_DESC(8, "pwm0", 1),
	NSP_PIN_DESC(9, "pwm1", 1),
	NSP_PIN_DESC(10, "pwm2", 1),
	NSP_PIN_DESC(11, "pwm3", 1),
	NSP_PIN_DESC(12, "uart1_rx", 1),
	NSP_PIN_DESC(13, "uart1_tx", 1),
	NSP_PIN_DESC(14, "uart1_cts", 1),
	NSP_PIN_DESC(15, "uart1_rts", 1),
	NSP_PIN_DESC(16, "uart2_rx", 1),
	NSP_PIN_DESC(17, "uart2_tx", 1),
	NSP_PIN_DESC(18, "synce", 0),
	NSP_PIN_DESC(19, "sata0_led", 0),
	NSP_PIN_DESC(20, "sata1_led", 0),
	NSP_PIN_DESC(21, "xtal_out", 1),
	NSP_PIN_DESC(22, "sdio_pwr", 1),
	NSP_PIN_DESC(23, "sdio_en_1p8v", 1),
	NSP_PIN_DESC(24, "gpio_24", 1),
	NSP_PIN_DESC(25, "gpio_25", 1),
	NSP_PIN_DESC(26, "p5_led0", 0),
	NSP_PIN_DESC(27, "p5_led1", 0),
	NSP_PIN_DESC(28, "gpio_28", 1),
	NSP_PIN_DESC(29, "gpio_29", 1),
	NSP_PIN_DESC(30, "gpio_30", 1),
	NSP_PIN_DESC(31, "gpio_31", 1),
	NSP_PIN_DESC(32, "nand_ale", 0),
	NSP_PIN_DESC(33, "nand_ce0", 0),
	NSP_PIN_DESC(34, "nand_r/b", 0),
	NSP_PIN_DESC(35, "nand_dq0", 0),
	NSP_PIN_DESC(36, "nand_dq1", 0),
	NSP_PIN_DESC(37, "nand_dq2", 0),
	NSP_PIN_DESC(38, "nand_dq3", 0),
	NSP_PIN_DESC(39, "nand_dq4", 0),
	NSP_PIN_DESC(40, "nand_dq5", 0),
	NSP_PIN_DESC(41, "nand_dq6", 0),
	NSP_PIN_DESC(42, "nand_dq7", 0),
पूर्ण;

/*
 * List of groups of pins
 */

अटल स्थिर अचिन्हित पूर्णांक spi_pins[] = अणु0, 1, 2, 3पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c_pins[] = अणु4, 5पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक mdio_pins[] = अणु6, 7पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm0_pins[] = अणु8पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio_b_0_pins[] = अणु8पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm1_pins[] = अणु9पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio_b_1_pins[] = अणु9पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm2_pins[] = अणु10पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio_b_2_pins[] = अणु10पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm3_pins[] = अणु11पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio_b_3_pins[] = अणु11पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart1_pins[] = अणु12, 13, 14, 15पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart2_pins[] = अणु16, 17पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक synce_pins[] = अणु18पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sata0_led_pins[] = अणु19पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sata1_led_pins[] = अणु20पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक xtal_out_pins[] = अणु21पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdio_pwr_pins[] = अणु22पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdio_1p8v_pins[] = अणु23पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक चयन_p05_led0_pins[] = अणु26पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक चयन_p05_led1_pins[] = अणु27पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nand_pins[] = अणु32, 33, 34, 35, 36, 37, 38, 39,
							40, 41, 42पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक emmc_pins[] = अणु32, 33, 34, 35, 36, 37, 38, 39,
							40, 41, 42पूर्ण;

#घोषणा NSP_PIN_GROUP(group_name, ba, sh, ma, al)	\
अणु							\
	.name = __stringअगरy(group_name) "_grp",		\
	.pins = group_name ## _pins,			\
	.num_pins = ARRAY_SIZE(group_name ## _pins),	\
	.mux = अणु					\
		.base = ba,				\
		.shअगरt = sh,				\
		.mask = ma,				\
		.alt = al,				\
	पूर्ण						\
पूर्ण

/*
 * List of nsp pin groups
 */
अटल स्थिर काष्ठा nsp_pin_group nsp_pin_groups[] = अणु
	NSP_PIN_GROUP(spi, NSP_MUX_BASE0, 0, 0x0f, 0x00),
	NSP_PIN_GROUP(i2c, NSP_MUX_BASE0, 3, 0x03, 0x00),
	NSP_PIN_GROUP(mdio, NSP_MUX_BASE0, 5, 0x03, 0x00),
	NSP_PIN_GROUP(gpio_b_0, NSP_MUX_BASE0, 7, 0x01, 0x00),
	NSP_PIN_GROUP(pwm0, NSP_MUX_BASE1, 0, 0x01, 0x01),
	NSP_PIN_GROUP(gpio_b_1, NSP_MUX_BASE0, 8, 0x01, 0x00),
	NSP_PIN_GROUP(pwm1, NSP_MUX_BASE1, 1, 0x01, 0x01),
	NSP_PIN_GROUP(gpio_b_2, NSP_MUX_BASE0, 9, 0x01, 0x00),
	NSP_PIN_GROUP(pwm2, NSP_MUX_BASE1, 2, 0x01, 0x01),
	NSP_PIN_GROUP(gpio_b_3, NSP_MUX_BASE0, 10, 0x01, 0x00),
	NSP_PIN_GROUP(pwm3, NSP_MUX_BASE1, 3, 0x01, 0x01),
	NSP_PIN_GROUP(uart1, NSP_MUX_BASE0, 11, 0x0f, 0x00),
	NSP_PIN_GROUP(uart2, NSP_MUX_BASE0, 15, 0x03, 0x00),
	NSP_PIN_GROUP(synce, NSP_MUX_BASE0, 17, 0x01, 0x01),
	NSP_PIN_GROUP(sata0_led, NSP_MUX_BASE0, 18, 0x01, 0x01),
	NSP_PIN_GROUP(sata1_led, NSP_MUX_BASE0, 19, 0x01, 0x01),
	NSP_PIN_GROUP(xtal_out, NSP_MUX_BASE0, 20, 0x01, 0x00),
	NSP_PIN_GROUP(sdio_pwr, NSP_MUX_BASE0, 21, 0x01, 0x00),
	NSP_PIN_GROUP(sdio_1p8v, NSP_MUX_BASE0, 22, 0x01, 0x00),
	NSP_PIN_GROUP(चयन_p05_led0, NSP_MUX_BASE0, 26, 0x01, 0x01),
	NSP_PIN_GROUP(चयन_p05_led1, NSP_MUX_BASE0, 27, 0x01, 0x01),
	NSP_PIN_GROUP(nand, NSP_MUX_BASE2, 0, 0x01, 0x00),
	NSP_PIN_GROUP(emmc, NSP_MUX_BASE2, 0, 0x01, 0x01)
पूर्ण;

/*
 * List of groups supported by functions
 */

अटल स्थिर अक्षर * स्थिर spi_grps[] = अणु"spi_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर i2c_grps[] = अणु"i2c_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर mdio_grps[] = अणु"mdio_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर pwm_grps[] = अणु"pwm0_grp", "pwm1_grp", "pwm2_grp"
						, "pwm3_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर gpio_b_grps[] = अणु"gpio_b_0_grp", "gpio_b_1_grp",
					"gpio_b_2_grp", "gpio_b_3_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर uart1_grps[] = अणु"uart1_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर uart2_grps[] = अणु"uart2_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर synce_grps[] = अणु"synce_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर sata_led_grps[] = अणु"sata0_led_grp", "sata1_led_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर xtal_out_grps[] = अणु"xtal_out_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर sdio_grps[] = अणु"sdio_pwr_grp", "sdio_1p8v_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर चयन_led_grps[] = अणु"switch_p05_led0_grp",
						"switch_p05_led1_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर nand_grps[] = अणु"nand_grp"पूर्ण;
अटल स्थिर अक्षर * स्थिर emmc_grps[] = अणु"emmc_grp"पूर्ण;

#घोषणा NSP_PIN_FUNCTION(func)				\
अणु							\
	.name = #func,					\
	.groups = func ## _grps,			\
	.num_groups = ARRAY_SIZE(func ## _grps),	\
पूर्ण

/*
 * List of supported functions in nsp
 */
अटल स्थिर काष्ठा nsp_pin_function nsp_pin_functions[] = अणु
	NSP_PIN_FUNCTION(spi),
	NSP_PIN_FUNCTION(i2c),
	NSP_PIN_FUNCTION(mdio),
	NSP_PIN_FUNCTION(pwm),
	NSP_PIN_FUNCTION(gpio_b),
	NSP_PIN_FUNCTION(uart1),
	NSP_PIN_FUNCTION(uart2),
	NSP_PIN_FUNCTION(synce),
	NSP_PIN_FUNCTION(sata_led),
	NSP_PIN_FUNCTION(xtal_out),
	NSP_PIN_FUNCTION(sdio),
	NSP_PIN_FUNCTION(चयन_led),
	NSP_PIN_FUNCTION(nand),
	NSP_PIN_FUNCTION(emmc)
पूर्ण;

अटल पूर्णांक nsp_get_groups_count(काष्ठा pinctrl_dev *pctrl_dev)
अणु
	काष्ठा nsp_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	वापस pinctrl->num_groups;
पूर्ण

अटल स्थिर अक्षर *nsp_get_group_name(काष्ठा pinctrl_dev *pctrl_dev,
				      अचिन्हित पूर्णांक selector)
अणु
	काष्ठा nsp_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	वापस pinctrl->groups[selector].name;
पूर्ण

अटल पूर्णांक nsp_get_group_pins(काष्ठा pinctrl_dev *pctrl_dev,
			      अचिन्हित पूर्णांक selector, स्थिर अचिन्हित पूर्णांक **pins,
			      अचिन्हित पूर्णांक *num_pins)
अणु
	काष्ठा nsp_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	*pins = pinctrl->groups[selector].pins;
	*num_pins = pinctrl->groups[selector].num_pins;

	वापस 0;
पूर्ण

अटल व्योम nsp_pin_dbg_show(काष्ठा pinctrl_dev *pctrl_dev,
			     काष्ठा seq_file *s, अचिन्हित पूर्णांक offset)
अणु
	seq_म_लिखो(s, " %s", dev_name(pctrl_dev->dev));
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops nsp_pinctrl_ops = अणु
	.get_groups_count = nsp_get_groups_count,
	.get_group_name = nsp_get_group_name,
	.get_group_pins = nsp_get_group_pins,
	.pin_dbg_show = nsp_pin_dbg_show,
	.dt_node_to_map = pinconf_generic_dt_node_to_map_group,
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
पूर्ण;

अटल पूर्णांक nsp_get_functions_count(काष्ठा pinctrl_dev *pctrl_dev)
अणु
	काष्ठा nsp_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	वापस pinctrl->num_functions;
पूर्ण

अटल स्थिर अक्षर *nsp_get_function_name(काष्ठा pinctrl_dev *pctrl_dev,
					 अचिन्हित पूर्णांक selector)
अणु
	काष्ठा nsp_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	वापस pinctrl->functions[selector].name;
पूर्ण

अटल पूर्णांक nsp_get_function_groups(काष्ठा pinctrl_dev *pctrl_dev,
				   अचिन्हित पूर्णांक selector,
				   स्थिर अक्षर * स्थिर **groups,
				   अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा nsp_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	*groups = pinctrl->functions[selector].groups;
	*num_groups = pinctrl->functions[selector].num_groups;

	वापस 0;
पूर्ण

अटल पूर्णांक nsp_pinmux_set(काष्ठा nsp_pinctrl *pinctrl,
			  स्थिर काष्ठा nsp_pin_function *func,
			  स्थिर काष्ठा nsp_pin_group *grp,
			  काष्ठा nsp_mux_log *mux_log)
अणु
	स्थिर काष्ठा nsp_mux *mux = &grp->mux;
	पूर्णांक i;
	u32 val, mask;
	अचिन्हित दीर्घ flags;
	व्योम __iomem *base_address;

	क्रम (i = 0; i < pinctrl->num_groups; i++) अणु
		अगर ((mux->shअगरt != mux_log[i].mux.shअगरt) ||
			(mux->base != mux_log[i].mux.base))
			जारी;

		/* अगर this is a new configuration, just करो it! */
		अगर (!mux_log[i].is_configured)
			अवरोध;

		/*
		 * IOMUX has been configured previously and one is trying to
		 * configure it to a dअगरferent function
		 */
		अगर (mux_log[i].mux.alt != mux->alt) अणु
			dev_err(pinctrl->dev,
				"double configuration error detected!\n");
			dev_err(pinctrl->dev, "func:%s grp:%s\n",
				func->name, grp->name);
			वापस -EINVAL;
		पूर्ण

		वापस 0;
	पूर्ण
	अगर (i == pinctrl->num_groups)
		वापस -EINVAL;

	mask = mux->mask;
	mux_log[i].mux.alt = mux->alt;
	mux_log[i].is_configured = true;

	चयन (mux->base) अणु
	हाल NSP_MUX_BASE0:
		base_address = pinctrl->base0;
		अवरोध;

	हाल NSP_MUX_BASE1:
		base_address = pinctrl->base1;
		अवरोध;

	हाल NSP_MUX_BASE2:
		base_address = pinctrl->base2;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&pinctrl->lock, flags);
	val = पढ़ोl(base_address);
	val &= ~(mask << grp->mux.shअगरt);
	val |= grp->mux.alt << grp->mux.shअगरt;
	ग_लिखोl(val, base_address);
	spin_unlock_irqrestore(&pinctrl->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक nsp_pinmux_enable(काष्ठा pinctrl_dev *pctrl_dev,
			     अचिन्हित पूर्णांक func_select, अचिन्हित पूर्णांक grp_select)
अणु
	काष्ठा nsp_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);
	स्थिर काष्ठा nsp_pin_function *func;
	स्थिर काष्ठा nsp_pin_group *grp;

	अगर (grp_select >= pinctrl->num_groups ||
	    func_select >= pinctrl->num_functions)
		वापस -EINVAL;

	func = &pinctrl->functions[func_select];
	grp = &pinctrl->groups[grp_select];

	dev_dbg(pctrl_dev->dev, "func:%u name:%s grp:%u name:%s\n",
		func_select, func->name, grp_select, grp->name);

	dev_dbg(pctrl_dev->dev, "shift:%u alt:%u\n", grp->mux.shअगरt,
		grp->mux.alt);

	वापस nsp_pinmux_set(pinctrl, func, grp, pinctrl->mux_log);
पूर्ण


अटल पूर्णांक nsp_gpio_request_enable(काष्ठा pinctrl_dev *pctrl_dev,
				   काष्ठा pinctrl_gpio_range *range,
				   अचिन्हित पूर्णांक pin)
अणु
	काष्ठा nsp_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);
	u32 *gpio_select = pctrl_dev->desc->pins[pin].drv_data;
	u32 val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pinctrl->lock, flags);
	val = पढ़ोl(pinctrl->base0);
	अगर ((val & BIT(pin)) != (*gpio_select << pin)) अणु
		val &= ~BIT(pin);
		val |= *gpio_select << pin;
		ग_लिखोl(val, pinctrl->base0);
	पूर्ण
	spin_unlock_irqrestore(&pinctrl->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम nsp_gpio_disable_मुक्त(काष्ठा pinctrl_dev *pctrl_dev,
				  काष्ठा pinctrl_gpio_range *range,
				  अचिन्हित पूर्णांक pin)
अणु
	काष्ठा nsp_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);
	u32 *gpio_select = pctrl_dev->desc->pins[pin].drv_data;
	u32 val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pinctrl->lock, flags);
	val = पढ़ोl(pinctrl->base0);
	अगर ((val & (1 << pin)) == (*gpio_select << pin)) अणु
		val &= ~(1 << pin);
		अगर (!(*gpio_select))
			val |= (1 << pin);
		ग_लिखोl(val, pinctrl->base0);
	पूर्ण
	spin_unlock_irqrestore(&pinctrl->lock, flags);
पूर्ण

अटल स्थिर काष्ठा pinmux_ops nsp_pinmux_ops = अणु
	.get_functions_count = nsp_get_functions_count,
	.get_function_name = nsp_get_function_name,
	.get_function_groups = nsp_get_function_groups,
	.set_mux = nsp_pinmux_enable,
	.gpio_request_enable = nsp_gpio_request_enable,
	.gpio_disable_मुक्त = nsp_gpio_disable_मुक्त,
पूर्ण;

अटल काष्ठा pinctrl_desc nsp_pinctrl_desc = अणु
	.name = "nsp-pinmux",
	.pctlops = &nsp_pinctrl_ops,
	.pmxops = &nsp_pinmux_ops,
पूर्ण;

अटल पूर्णांक nsp_mux_log_init(काष्ठा nsp_pinctrl *pinctrl)
अणु
	काष्ठा nsp_mux_log *log;
	अचिन्हित पूर्णांक i;
	u32 no_of_groups = ARRAY_SIZE(nsp_pin_groups);

	pinctrl->mux_log = devm_kसुस्मृति(pinctrl->dev, no_of_groups,
					माप(काष्ठा nsp_mux_log),
					GFP_KERNEL);
	अगर (!pinctrl->mux_log)
		वापस -ENOMEM;

	क्रम (i = 0; i < no_of_groups; i++) अणु
		log = &pinctrl->mux_log[i];
		log->mux.base = nsp_pin_groups[i].mux.base;
		log->mux.shअगरt = nsp_pin_groups[i].mux.shअगरt;
		log->mux.alt = 0;
		log->is_configured = false;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nsp_pinmux_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा nsp_pinctrl *pinctrl;
	काष्ठा resource *res;
	पूर्णांक i, ret;
	काष्ठा pinctrl_pin_desc *pins;
	अचिन्हित पूर्णांक num_pins = ARRAY_SIZE(nsp_pins);

	pinctrl = devm_kzalloc(&pdev->dev, माप(*pinctrl), GFP_KERNEL);
	अगर (!pinctrl)
		वापस -ENOMEM;
	pinctrl->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, pinctrl);
	spin_lock_init(&pinctrl->lock);

	pinctrl->base0 = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pinctrl->base0))
		वापस PTR_ERR(pinctrl->base0);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (!res)
		वापस -EINVAL;
	pinctrl->base1 = devm_ioremap(&pdev->dev, res->start,
					      resource_size(res));
	अगर (!pinctrl->base1) अणु
		dev_err(&pdev->dev, "unable to map I/O space\n");
		वापस -ENOMEM;
	पूर्ण

	pinctrl->base2 = devm_platक्रमm_ioremap_resource(pdev, 2);
	अगर (IS_ERR(pinctrl->base2))
		वापस PTR_ERR(pinctrl->base2);

	ret = nsp_mux_log_init(pinctrl);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to initialize IOMUX log\n");
		वापस ret;
	पूर्ण

	pins = devm_kसुस्मृति(&pdev->dev, num_pins, माप(*pins), GFP_KERNEL);
	अगर (!pins)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_pins; i++) अणु
		pins[i].number = nsp_pins[i].pin;
		pins[i].name = nsp_pins[i].name;
		pins[i].drv_data = &nsp_pins[i].gpio_select;
	पूर्ण

	pinctrl->groups = nsp_pin_groups;
	pinctrl->num_groups = ARRAY_SIZE(nsp_pin_groups);
	pinctrl->functions = nsp_pin_functions;
	pinctrl->num_functions = ARRAY_SIZE(nsp_pin_functions);
	nsp_pinctrl_desc.pins = pins;
	nsp_pinctrl_desc.npins = num_pins;

	pinctrl->pctl = devm_pinctrl_रेजिस्टर(&pdev->dev, &nsp_pinctrl_desc,
					 pinctrl);
	अगर (IS_ERR(pinctrl->pctl)) अणु
		dev_err(&pdev->dev, "unable to register nsp IOMUX pinctrl\n");
		वापस PTR_ERR(pinctrl->pctl);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id nsp_pinmux_of_match[] = अणु
	अणु .compatible = "brcm,nsp-pinmux" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver nsp_pinmux_driver = अणु
	.driver = अणु
		.name = "nsp-pinmux",
		.of_match_table = nsp_pinmux_of_match,
	पूर्ण,
	.probe = nsp_pinmux_probe,
पूर्ण;

अटल पूर्णांक __init nsp_pinmux_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&nsp_pinmux_driver);
पूर्ण
arch_initcall(nsp_pinmux_init);
