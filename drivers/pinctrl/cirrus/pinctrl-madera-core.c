<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Pinctrl क्रम Cirrus Logic Madera codecs
 *
 * Copyright (C) 2016-2018 Cirrus Logic
 */

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/pinctrl/machine.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>

#समावेश <linux/mfd/madera/core.h>
#समावेश <linux/mfd/madera/रेजिस्टरs.h>

#समावेश "../pinctrl-utils.h"

#समावेश "pinctrl-madera.h"

/*
 * Use pin GPIO names क्रम consistency
 * NOTE: IDs are zero-indexed क्रम coding convenience
 */
अटल स्थिर काष्ठा pinctrl_pin_desc madera_pins[] = अणु
	PINCTRL_PIN(0, "gpio1"),
	PINCTRL_PIN(1, "gpio2"),
	PINCTRL_PIN(2, "gpio3"),
	PINCTRL_PIN(3, "gpio4"),
	PINCTRL_PIN(4, "gpio5"),
	PINCTRL_PIN(5, "gpio6"),
	PINCTRL_PIN(6, "gpio7"),
	PINCTRL_PIN(7, "gpio8"),
	PINCTRL_PIN(8, "gpio9"),
	PINCTRL_PIN(9, "gpio10"),
	PINCTRL_PIN(10, "gpio11"),
	PINCTRL_PIN(11, "gpio12"),
	PINCTRL_PIN(12, "gpio13"),
	PINCTRL_PIN(13, "gpio14"),
	PINCTRL_PIN(14, "gpio15"),
	PINCTRL_PIN(15, "gpio16"),
	PINCTRL_PIN(16, "gpio17"),
	PINCTRL_PIN(17, "gpio18"),
	PINCTRL_PIN(18, "gpio19"),
	PINCTRL_PIN(19, "gpio20"),
	PINCTRL_PIN(20, "gpio21"),
	PINCTRL_PIN(21, "gpio22"),
	PINCTRL_PIN(22, "gpio23"),
	PINCTRL_PIN(23, "gpio24"),
	PINCTRL_PIN(24, "gpio25"),
	PINCTRL_PIN(25, "gpio26"),
	PINCTRL_PIN(26, "gpio27"),
	PINCTRL_PIN(27, "gpio28"),
	PINCTRL_PIN(28, "gpio29"),
	PINCTRL_PIN(29, "gpio30"),
	PINCTRL_PIN(30, "gpio31"),
	PINCTRL_PIN(31, "gpio32"),
	PINCTRL_PIN(32, "gpio33"),
	PINCTRL_PIN(33, "gpio34"),
	PINCTRL_PIN(34, "gpio35"),
	PINCTRL_PIN(35, "gpio36"),
	PINCTRL_PIN(36, "gpio37"),
	PINCTRL_PIN(37, "gpio38"),
	PINCTRL_PIN(38, "gpio39"),
	PINCTRL_PIN(39, "gpio40"),
पूर्ण;

/*
 * All single-pin functions can be mapped to any GPIO, however pinmux applies
 * functions to pin groups and only those groups declared as supporting that
 * function. To make this work we must put each pin in its own dummy group so
 * that the functions can be described as applying to all pins.
 * Since these करो not correspond to anything in the actual hardware - they are
 * merely an adaptation to pinctrl's view of the world - we use the same name
 * as the pin to aव्योम confusion when comparing with datasheet inकाष्ठाions
 */
अटल स्थिर अक्षर * स्थिर madera_pin_single_group_names[] = अणु
	"gpio1",  "gpio2",  "gpio3",  "gpio4",  "gpio5",  "gpio6",  "gpio7",
	"gpio8",  "gpio9",  "gpio10", "gpio11", "gpio12", "gpio13", "gpio14",
	"gpio15", "gpio16", "gpio17", "gpio18", "gpio19", "gpio20", "gpio21",
	"gpio22", "gpio23", "gpio24", "gpio25", "gpio26", "gpio27", "gpio28",
	"gpio29", "gpio30", "gpio31", "gpio32", "gpio33", "gpio34", "gpio35",
	"gpio36", "gpio37", "gpio38", "gpio39", "gpio40",
पूर्ण;

/* set of pin numbers क्रम single-pin groups, zero-indexed */
अटल स्थिर अचिन्हित पूर्णांक madera_pin_single_group_pins[] = अणु
	  0,  1,  2,  3,  4,  5,  6,
	  7,  8,  9, 10, 11, 12, 13,
	 14, 15, 16, 17, 18, 19, 20,
	 21, 22, 23, 24, 25, 26, 27,
	 28, 29, 30, 31, 32, 33, 34,
	 35, 36, 37, 38, 39,
पूर्ण;

अटल स्थिर अक्षर * स्थिर madera_aअगर1_group_names[] = अणु "aif1" पूर्ण;
अटल स्थिर अक्षर * स्थिर madera_aअगर2_group_names[] = अणु "aif2" पूर्ण;
अटल स्थिर अक्षर * स्थिर madera_aअगर3_group_names[] = अणु "aif3" पूर्ण;
अटल स्थिर अक्षर * स्थिर madera_aअगर4_group_names[] = अणु "aif4" पूर्ण;
अटल स्थिर अक्षर * स्थिर madera_mअगर1_group_names[] = अणु "mif1" पूर्ण;
अटल स्थिर अक्षर * स्थिर madera_mअगर2_group_names[] = अणु "mif2" पूर्ण;
अटल स्थिर अक्षर * स्थिर madera_mअगर3_group_names[] = अणु "mif3" पूर्ण;
अटल स्थिर अक्षर * स्थिर madera_dmic3_group_names[] = अणु "dmic3" पूर्ण;
अटल स्थिर अक्षर * स्थिर madera_dmic4_group_names[] = अणु "dmic4" पूर्ण;
अटल स्थिर अक्षर * स्थिर madera_dmic5_group_names[] = अणु "dmic5" पूर्ण;
अटल स्थिर अक्षर * स्थिर madera_dmic6_group_names[] = अणु "dmic6" पूर्ण;
अटल स्थिर अक्षर * स्थिर madera_spk1_group_names[] = अणु "pdmspk1" पूर्ण;
अटल स्थिर अक्षर * स्थिर madera_spk2_group_names[] = अणु "pdmspk2" पूर्ण;

/*
 * alt-functions always apply to a single pin group, other functions always
 * apply to all pins
 */
अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *group_names;
	u32 func;
पूर्ण madera_mux_funcs[] = अणु
	अणु
		.name = "aif1",
		.group_names = madera_aअगर1_group_names,
		.func = 0x000
	पूर्ण,
	अणु
		.name = "aif2",
		.group_names = madera_aअगर2_group_names,
		.func = 0x000
	पूर्ण,
	अणु
		.name = "aif3",
		.group_names = madera_aअगर3_group_names,
		.func = 0x000
	पूर्ण,
	अणु
		.name = "aif4",
		.group_names = madera_aअगर4_group_names,
		.func = 0x000
	पूर्ण,
	अणु
		.name = "mif1",
		.group_names = madera_mअगर1_group_names,
		.func = 0x000
	पूर्ण,
	अणु
		.name = "mif2",
		.group_names = madera_mअगर2_group_names,
		.func = 0x000
	पूर्ण,
	अणु
		.name = "mif3",
		.group_names = madera_mअगर3_group_names,
		.func = 0x000
	पूर्ण,
	अणु
		.name = "dmic3",
		.group_names = madera_dmic3_group_names,
		.func = 0x000
	पूर्ण,
	अणु
		.name = "dmic4",
		.group_names = madera_dmic4_group_names,
		.func = 0x000
	पूर्ण,
	अणु
		.name = "dmic5",
		.group_names = madera_dmic5_group_names,
		.func = 0x000
	पूर्ण,
	अणु
		.name = "dmic6",
		.group_names = madera_dmic6_group_names,
		.func = 0x000
	पूर्ण,
	अणु
		.name = "pdmspk1",
		.group_names = madera_spk1_group_names,
		.func = 0x000
	पूर्ण,
	अणु
		.name = "pdmspk2",
		.group_names = madera_spk2_group_names,
		.func = 0x000
	पूर्ण,
	अणु
		.name = "io",
		.group_names = madera_pin_single_group_names,
		.func = 0x001
	पूर्ण,
	अणु
		.name = "dsp-gpio",
		.group_names = madera_pin_single_group_names,
		.func = 0x002
	पूर्ण,
	अणु
		.name = "irq1",
		.group_names = madera_pin_single_group_names,
		.func = 0x003
	पूर्ण,
	अणु
		.name = "irq2",
		.group_names = madera_pin_single_group_names,
		.func = 0x004
	पूर्ण,
	अणु
		.name = "fll1-clk",
		.group_names = madera_pin_single_group_names,
		.func = 0x010
	पूर्ण,
	अणु
		.name = "fll2-clk",
		.group_names = madera_pin_single_group_names,
		.func = 0x011
	पूर्ण,
	अणु
		.name = "fll3-clk",
		.group_names = madera_pin_single_group_names,
		.func = 0x012
	पूर्ण,
	अणु
		.name = "fllao-clk",
		.group_names = madera_pin_single_group_names,
		.func = 0x013
	पूर्ण,
	अणु
		.name = "fll1-lock",
		.group_names = madera_pin_single_group_names,
		.func = 0x018
	पूर्ण,
	अणु
		.name = "fll2-lock",
		.group_names = madera_pin_single_group_names,
		.func = 0x019
	पूर्ण,
	अणु
		.name = "fll3-lock",
		.group_names = madera_pin_single_group_names,
		.func = 0x01a
	पूर्ण,
	अणु
		.name = "fllao-lock",
		.group_names = madera_pin_single_group_names,
		.func = 0x01b
	पूर्ण,
	अणु
		.name = "opclk",
		.group_names = madera_pin_single_group_names,
		.func = 0x040
	पूर्ण,
	अणु
		.name = "opclk-async",
		.group_names = madera_pin_single_group_names,
		.func = 0x041
	पूर्ण,
	अणु
		.name = "pwm1",
		.group_names = madera_pin_single_group_names,
		.func = 0x048
	पूर्ण,
	अणु
		.name = "pwm2",
		.group_names = madera_pin_single_group_names,
		.func = 0x049
	पूर्ण,
	अणु
		.name = "spdif",
		.group_names = madera_pin_single_group_names,
		.func = 0x04c
	पूर्ण,
	अणु
		.name = "asrc1-in1-lock",
		.group_names = madera_pin_single_group_names,
		.func = 0x088
	पूर्ण,
	अणु
		.name = "asrc1-in2-lock",
		.group_names = madera_pin_single_group_names,
		.func = 0x089
	पूर्ण,
	अणु
		.name = "asrc2-in1-lock",
		.group_names = madera_pin_single_group_names,
		.func = 0x08a
	पूर्ण,
	अणु
		.name = "asrc2-in2-lock",
		.group_names = madera_pin_single_group_names,
		.func = 0x08b
	पूर्ण,
	अणु
		.name = "spkl-short-circuit",
		.group_names = madera_pin_single_group_names,
		.func = 0x0b6
	पूर्ण,
	अणु
		.name = "spkr-short-circuit",
		.group_names = madera_pin_single_group_names,
		.func = 0x0b7
	पूर्ण,
	अणु
		.name = "spk-shutdown",
		.group_names = madera_pin_single_group_names,
		.func = 0x0e0
	पूर्ण,
	अणु
		.name = "spk-overheat-shutdown",
		.group_names = madera_pin_single_group_names,
		.func = 0x0e1
	पूर्ण,
	अणु
		.name = "spk-overheat-warn",
		.group_names = madera_pin_single_group_names,
		.func = 0x0e2
	पूर्ण,
	अणु
		.name = "timer1-sts",
		.group_names = madera_pin_single_group_names,
		.func = 0x140
	पूर्ण,
	अणु
		.name = "timer2-sts",
		.group_names = madera_pin_single_group_names,
		.func = 0x141
	पूर्ण,
	अणु
		.name = "timer3-sts",
		.group_names = madera_pin_single_group_names,
		.func = 0x142
	पूर्ण,
	अणु
		.name = "timer4-sts",
		.group_names = madera_pin_single_group_names,
		.func = 0x143
	पूर्ण,
	अणु
		.name = "timer5-sts",
		.group_names = madera_pin_single_group_names,
		.func = 0x144
	पूर्ण,
	अणु
		.name = "timer6-sts",
		.group_names = madera_pin_single_group_names,
		.func = 0x145
	पूर्ण,
	अणु
		.name = "timer7-sts",
		.group_names = madera_pin_single_group_names,
		.func = 0x146
	पूर्ण,
	अणु
		.name = "timer8-sts",
		.group_names = madera_pin_single_group_names,
		.func = 0x147
	पूर्ण,
	अणु
		.name = "log1-fifo-ne",
		.group_names = madera_pin_single_group_names,
		.func = 0x150
	पूर्ण,
	अणु
		.name = "log2-fifo-ne",
		.group_names = madera_pin_single_group_names,
		.func = 0x151
	पूर्ण,
	अणु
		.name = "log3-fifo-ne",
		.group_names = madera_pin_single_group_names,
		.func = 0x152
	पूर्ण,
	अणु
		.name = "log4-fifo-ne",
		.group_names = madera_pin_single_group_names,
		.func = 0x153
	पूर्ण,
	अणु
		.name = "log5-fifo-ne",
		.group_names = madera_pin_single_group_names,
		.func = 0x154
	पूर्ण,
	अणु
		.name = "log6-fifo-ne",
		.group_names = madera_pin_single_group_names,
		.func = 0x155
	पूर्ण,
	अणु
		.name = "log7-fifo-ne",
		.group_names = madera_pin_single_group_names,
		.func = 0x156
	पूर्ण,
	अणु
		.name = "log8-fifo-ne",
		.group_names = madera_pin_single_group_names,
		.func = 0x157
	पूर्ण,
	अणु
		.name = "aux-pdm-clk",
		.group_names = madera_pin_single_group_names,
		.func = 0x280
	पूर्ण,
	अणु
		.name = "aux-pdm-dat",
		.group_names = madera_pin_single_group_names,
		.func = 0x281
	पूर्ण,
पूर्ण;

अटल u16 madera_pin_make_drv_str(काष्ठा madera_pin_निजी *priv,
				      अचिन्हित पूर्णांक milliamps)
अणु
	चयन (milliamps) अणु
	हाल 4:
		वापस 0;
	हाल 8:
		वापस 2 << MADERA_GP1_DRV_STR_SHIFT;
	शेष:
		अवरोध;
	पूर्ण

	dev_warn(priv->dev, "%u mA not a valid drive strength", milliamps);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक madera_pin_unmake_drv_str(काष्ठा madera_pin_निजी *priv,
					      u16 regval)
अणु
	regval = (regval & MADERA_GP1_DRV_STR_MASK) >> MADERA_GP1_DRV_STR_SHIFT;

	चयन (regval) अणु
	हाल 0:
		वापस 4;
	हाल 2:
		वापस 8;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक madera_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा madera_pin_निजी *priv = pinctrl_dev_get_drvdata(pctldev);

	/* Number of alt function groups plus number of single-pin groups */
	वापस priv->chip->n_pin_groups + priv->chip->n_pins;
पूर्ण

अटल स्थिर अक्षर *madera_get_group_name(काष्ठा pinctrl_dev *pctldev,
					 अचिन्हित पूर्णांक selector)
अणु
	काष्ठा madera_pin_निजी *priv = pinctrl_dev_get_drvdata(pctldev);

	अगर (selector < priv->chip->n_pin_groups)
		वापस priv->chip->pin_groups[selector].name;

	selector -= priv->chip->n_pin_groups;
	वापस madera_pin_single_group_names[selector];
पूर्ण

अटल पूर्णांक madera_get_group_pins(काष्ठा pinctrl_dev *pctldev,
				 अचिन्हित पूर्णांक selector,
				 स्थिर अचिन्हित पूर्णांक **pins,
				 अचिन्हित पूर्णांक *num_pins)
अणु
	काष्ठा madera_pin_निजी *priv = pinctrl_dev_get_drvdata(pctldev);

	अगर (selector < priv->chip->n_pin_groups) अणु
		*pins = priv->chip->pin_groups[selector].pins;
		*num_pins = priv->chip->pin_groups[selector].n_pins;
	पूर्ण अन्यथा अणु
		/* वापस the dummy group क्रम a single pin */
		selector -= priv->chip->n_pin_groups;
		*pins = &madera_pin_single_group_pins[selector];
		*num_pins = 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम madera_pin_dbg_show_fn(काष्ठा madera_pin_निजी *priv,
				   काष्ठा seq_file *s,
				   अचिन्हित पूर्णांक pin, अचिन्हित पूर्णांक fn)
अणु
	स्थिर काष्ठा madera_pin_chip *chip = priv->chip;
	पूर्णांक i, g_pin;

	अगर (fn != 0) अणु
		क्रम (i = 0; i < ARRAY_SIZE(madera_mux_funcs); ++i) अणु
			अगर (madera_mux_funcs[i].func == fn) अणु
				seq_म_लिखो(s, " FN=%s",
					   madera_mux_funcs[i].name);
				वापस;
			पूर्ण
		पूर्ण
		वापस;	/* ignore unknown function values */
	पूर्ण

	/* alt function */
	क्रम (i = 0; i < chip->n_pin_groups; ++i) अणु
		क्रम (g_pin = 0; g_pin < chip->pin_groups[i].n_pins; ++g_pin) अणु
			अगर (chip->pin_groups[i].pins[g_pin] == pin) अणु
				seq_म_लिखो(s, " FN=%s",
					   chip->pin_groups[i].name);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __maybe_unused madera_pin_dbg_show(काष्ठा pinctrl_dev *pctldev,
					       काष्ठा seq_file *s,
					       अचिन्हित पूर्णांक pin)
अणु
	काष्ठा madera_pin_निजी *priv = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित पूर्णांक conf[2];
	अचिन्हित पूर्णांक reg = MADERA_GPIO1_CTRL_1 + (2 * pin);
	अचिन्हित पूर्णांक fn;
	पूर्णांक ret;

	ret = regmap_पढ़ो(priv->madera->regmap, reg, &conf[0]);
	अगर (ret)
		वापस;

	ret = regmap_पढ़ो(priv->madera->regmap, reg + 1, &conf[1]);
	अगर (ret)
		वापस;

	seq_म_लिखो(s, "%04x:%04x", conf[0], conf[1]);

	fn = (conf[0] & MADERA_GP1_FN_MASK) >> MADERA_GP1_FN_SHIFT;
	madera_pin_dbg_show_fn(priv, s, pin, fn);

	/* State of direction bit is only relevant अगर function==1 */
	अगर (fn == 1) अणु
		अगर (conf[1] & MADERA_GP1_सूची_MASK)
			seq_माला_दो(s, " IN");
		अन्यथा
			seq_माला_दो(s, " OUT");
	पूर्ण

	अगर (conf[1] & MADERA_GP1_PU_MASK)
		seq_माला_दो(s, " PU");

	अगर (conf[1] & MADERA_GP1_PD_MASK)
		seq_माला_दो(s, " PD");

	अगर (conf[0] & MADERA_GP1_DB_MASK)
		seq_माला_दो(s, " DB");

	अगर (conf[0] & MADERA_GP1_OP_CFG_MASK)
		seq_माला_दो(s, " OD");
	अन्यथा
		seq_माला_दो(s, " CMOS");

	seq_म_लिखो(s, " DRV=%umA", madera_pin_unmake_drv_str(priv, conf[1]));

	अगर (conf[0] & MADERA_GP1_IP_CFG_MASK)
		seq_माला_दो(s, " SCHMITT");
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops madera_pin_group_ops = अणु
	.get_groups_count = madera_get_groups_count,
	.get_group_name = madera_get_group_name,
	.get_group_pins = madera_get_group_pins,
#अगर IS_ENABLED(CONFIG_OF)
	.dt_node_to_map = pinconf_generic_dt_node_to_map_all,
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_DEBUG_FS)
	.pin_dbg_show = madera_pin_dbg_show,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक madera_mux_get_funcs_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस ARRAY_SIZE(madera_mux_funcs);
पूर्ण

अटल स्थिर अक्षर *madera_mux_get_func_name(काष्ठा pinctrl_dev *pctldev,
					    अचिन्हित पूर्णांक selector)
अणु
	वापस madera_mux_funcs[selector].name;
पूर्ण

अटल पूर्णांक madera_mux_get_groups(काष्ठा pinctrl_dev *pctldev,
				 अचिन्हित पूर्णांक selector,
				 स्थिर अक्षर * स्थिर **groups,
				 अचिन्हित पूर्णांक * स्थिर num_groups)
अणु
	काष्ठा madera_pin_निजी *priv = pinctrl_dev_get_drvdata(pctldev);

	*groups = madera_mux_funcs[selector].group_names;

	अगर (madera_mux_funcs[selector].func == 0) अणु
		/* alt func always maps to a single group */
		*num_groups = 1;
	पूर्ण अन्यथा अणु
		/* other funcs map to all available gpio pins */
		*num_groups = priv->chip->n_pins;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक madera_mux_set_mux(काष्ठा pinctrl_dev *pctldev,
			      अचिन्हित पूर्णांक selector,
			      अचिन्हित पूर्णांक group)
अणु
	काष्ठा madera_pin_निजी *priv = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा madera *madera = priv->madera;
	स्थिर काष्ठा madera_pin_groups *pin_group = priv->chip->pin_groups;
	अचिन्हित पूर्णांक n_chip_groups = priv->chip->n_pin_groups;
	स्थिर अक्षर *func_name = madera_mux_funcs[selector].name;
	अचिन्हित पूर्णांक reg;
	पूर्णांक i, ret = 0;

	dev_dbg(priv->dev, "%s selecting %u (%s) for group %u (%s)\n",
		__func__, selector, func_name, group,
		madera_get_group_name(pctldev, group));

	अगर (madera_mux_funcs[selector].func == 0) अणु
		/* alt func pin assignments are codec-specअगरic */
		क्रम (i = 0; i < n_chip_groups; ++i) अणु
			अगर (म_भेद(func_name, pin_group->name) == 0)
				अवरोध;

			++pin_group;
		पूर्ण

		अगर (i == n_chip_groups)
			वापस -EINVAL;

		क्रम (i = 0; i < pin_group->n_pins; ++i) अणु
			reg = MADERA_GPIO1_CTRL_1 + (2 * pin_group->pins[i]);

			dev_dbg(priv->dev, "%s setting 0x%x func bits to 0\n",
				__func__, reg);

			ret = regmap_update_bits(madera->regmap, reg,
						 MADERA_GP1_FN_MASK, 0);
			अगर (ret)
				अवरोध;

		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * क्रम other funcs the group will be the gpio number and will
		 * be offset by the number of chip-specअगरic functions at the
		 * start of the group list
		 */
		group -= n_chip_groups;
		reg = MADERA_GPIO1_CTRL_1 + (2 * group);

		dev_dbg(priv->dev, "%s setting 0x%x func bits to 0x%x\n",
			__func__, reg, madera_mux_funcs[selector].func);

		ret = regmap_update_bits(madera->regmap,
					 reg,
					 MADERA_GP1_FN_MASK,
					 madera_mux_funcs[selector].func);
	पूर्ण

	अगर (ret)
		dev_err(priv->dev, "Failed to write to 0x%x (%d)\n", reg, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक madera_gpio_set_direction(काष्ठा pinctrl_dev *pctldev,
				     काष्ठा pinctrl_gpio_range *range,
				     अचिन्हित पूर्णांक offset,
				     bool input)
अणु
	काष्ठा madera_pin_निजी *priv = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा madera *madera = priv->madera;
	अचिन्हित पूर्णांक reg = MADERA_GPIO1_CTRL_2 + (2 * offset);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	अगर (input)
		val = MADERA_GP1_सूची;
	अन्यथा
		val = 0;

	ret = regmap_update_bits(madera->regmap, reg, MADERA_GP1_सूची_MASK, val);
	अगर (ret)
		dev_err(priv->dev, "Failed to write to 0x%x (%d)\n", reg, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक madera_gpio_request_enable(काष्ठा pinctrl_dev *pctldev,
				      काष्ठा pinctrl_gpio_range *range,
				      अचिन्हित पूर्णांक offset)
अणु
	काष्ठा madera_pin_निजी *priv = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा madera *madera = priv->madera;
	अचिन्हित पूर्णांक reg = MADERA_GPIO1_CTRL_1 + (2 * offset);
	पूर्णांक ret;

	/* put the pin पूर्णांकo GPIO mode */
	ret = regmap_update_bits(madera->regmap, reg, MADERA_GP1_FN_MASK, 1);
	अगर (ret)
		dev_err(priv->dev, "Failed to write to 0x%x (%d)\n", reg, ret);

	वापस ret;
पूर्ण

अटल व्योम madera_gpio_disable_मुक्त(काष्ठा pinctrl_dev *pctldev,
				     काष्ठा pinctrl_gpio_range *range,
				     अचिन्हित पूर्णांक offset)
अणु
	काष्ठा madera_pin_निजी *priv = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा madera *madera = priv->madera;
	अचिन्हित पूर्णांक reg = MADERA_GPIO1_CTRL_1 + (2 * offset);
	पूर्णांक ret;

	/* disable GPIO by setting to GPIO IN */
	madera_gpio_set_direction(pctldev, range, offset, true);

	ret = regmap_update_bits(madera->regmap, reg, MADERA_GP1_FN_MASK, 1);
	अगर (ret)
		dev_err(priv->dev, "Failed to write to 0x%x (%d)\n", reg, ret);
पूर्ण

अटल स्थिर काष्ठा pinmux_ops madera_pin_mux_ops = अणु
	.get_functions_count = madera_mux_get_funcs_count,
	.get_function_name = madera_mux_get_func_name,
	.get_function_groups = madera_mux_get_groups,
	.set_mux = madera_mux_set_mux,
	.gpio_request_enable = madera_gpio_request_enable,
	.gpio_disable_मुक्त = madera_gpio_disable_मुक्त,
	.gpio_set_direction = madera_gpio_set_direction,
	.strict = true, /* GPIO and other functions are exclusive */
पूर्ण;

अटल पूर्णांक madera_pin_conf_get(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
			       अचिन्हित दीर्घ *config)
अणु
	काष्ठा madera_pin_निजी *priv = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित पूर्णांक param = pinconf_to_config_param(*config);
	अचिन्हित पूर्णांक result = 0;
	अचिन्हित पूर्णांक reg = MADERA_GPIO1_CTRL_1 + (2 * pin);
	अचिन्हित पूर्णांक conf[2];
	पूर्णांक ret;

	ret = regmap_पढ़ो(priv->madera->regmap, reg, &conf[0]);
	अगर (!ret)
		ret = regmap_पढ़ो(priv->madera->regmap, reg + 1, &conf[1]);

	अगर (ret) अणु
		dev_err(priv->dev, "Failed to read GP%d conf (%d)\n",
			pin + 1, ret);
		वापस ret;
	पूर्ण

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_BUS_HOLD:
		conf[1] &= MADERA_GP1_PU_MASK | MADERA_GP1_PD_MASK;
		अगर (conf[1] == (MADERA_GP1_PU | MADERA_GP1_PD))
			result = 1;
		अवरोध;
	हाल PIN_CONFIG_BIAS_DISABLE:
		conf[1] &= MADERA_GP1_PU_MASK | MADERA_GP1_PD_MASK;
		अगर (!conf[1])
			result = 1;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		conf[1] &= MADERA_GP1_PU_MASK | MADERA_GP1_PD_MASK;
		अगर (conf[1] == MADERA_GP1_PD_MASK)
			result = 1;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_UP:
		conf[1] &= MADERA_GP1_PU_MASK | MADERA_GP1_PD_MASK;
		अगर (conf[1] == MADERA_GP1_PU_MASK)
			result = 1;
		अवरोध;
	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		अगर (conf[0] & MADERA_GP1_OP_CFG_MASK)
			result = 1;
		अवरोध;
	हाल PIN_CONFIG_DRIVE_PUSH_PULL:
		अगर (!(conf[0] & MADERA_GP1_OP_CFG_MASK))
			result = 1;
		अवरोध;
	हाल PIN_CONFIG_DRIVE_STRENGTH:
		result = madera_pin_unmake_drv_str(priv, conf[1]);
		अवरोध;
	हाल PIN_CONFIG_INPUT_DEBOUNCE:
		अगर (conf[0] & MADERA_GP1_DB_MASK)
			result = 1;
		अवरोध;
	हाल PIN_CONFIG_INPUT_ENABLE:
		अगर (conf[0] & MADERA_GP1_सूची_MASK)
			result = 1;
		अवरोध;
	हाल PIN_CONFIG_INPUT_SCHMITT:
	हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		अगर (conf[0] & MADERA_GP1_IP_CFG_MASK)
			result = 1;
		अवरोध;
	हाल PIN_CONFIG_OUTPUT:
		अगर ((conf[1] & MADERA_GP1_सूची_MASK) &&
		    (conf[0] & MADERA_GP1_LVL_MASK))
			result = 1;
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	*config = pinconf_to_config_packed(param, result);

	वापस 0;
पूर्ण

अटल पूर्णांक madera_pin_conf_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
			       अचिन्हित दीर्घ *configs, अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा madera_pin_निजी *priv = pinctrl_dev_get_drvdata(pctldev);
	u16 conf[2] = अणु0, 0पूर्ण;
	u16 mask[2] = अणु0, 0पूर्ण;
	अचिन्हित पूर्णांक reg = MADERA_GPIO1_CTRL_1 + (2 * pin);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	जबतक (num_configs) अणु
		dev_dbg(priv->dev, "%s config 0x%lx\n", __func__, *configs);

		चयन (pinconf_to_config_param(*configs)) अणु
		हाल PIN_CONFIG_BIAS_BUS_HOLD:
			mask[1] |= MADERA_GP1_PU_MASK | MADERA_GP1_PD_MASK;
			conf[1] |= MADERA_GP1_PU | MADERA_GP1_PD;
			अवरोध;
		हाल PIN_CONFIG_BIAS_DISABLE:
			mask[1] |= MADERA_GP1_PU_MASK | MADERA_GP1_PD_MASK;
			conf[1] &= ~(MADERA_GP1_PU | MADERA_GP1_PD);
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			mask[1] |= MADERA_GP1_PU_MASK | MADERA_GP1_PD_MASK;
			conf[1] |= MADERA_GP1_PD;
			conf[1] &= ~MADERA_GP1_PU;
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_UP:
			mask[1] |= MADERA_GP1_PU_MASK | MADERA_GP1_PD_MASK;
			conf[1] |= MADERA_GP1_PU;
			conf[1] &= ~MADERA_GP1_PD;
			अवरोध;
		हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
			mask[0] |= MADERA_GP1_OP_CFG_MASK;
			conf[0] |= MADERA_GP1_OP_CFG;
			अवरोध;
		हाल PIN_CONFIG_DRIVE_PUSH_PULL:
			mask[0] |= MADERA_GP1_OP_CFG_MASK;
			conf[0] &= ~MADERA_GP1_OP_CFG;
			अवरोध;
		हाल PIN_CONFIG_DRIVE_STRENGTH:
			val = pinconf_to_config_argument(*configs);
			mask[1] |= MADERA_GP1_DRV_STR_MASK;
			conf[1] &= ~MADERA_GP1_DRV_STR_MASK;
			conf[1] |= madera_pin_make_drv_str(priv, val);
			अवरोध;
		हाल PIN_CONFIG_INPUT_DEBOUNCE:
			mask[0] |= MADERA_GP1_DB_MASK;

			/*
			 * we can't configure debounce समय per-pin so value
			 * is just a flag
			 */
			val = pinconf_to_config_argument(*configs);
			अगर (val)
				conf[0] |= MADERA_GP1_DB;
			अन्यथा
				conf[0] &= ~MADERA_GP1_DB;
			अवरोध;
		हाल PIN_CONFIG_INPUT_ENABLE:
			val = pinconf_to_config_argument(*configs);
			mask[1] |= MADERA_GP1_सूची_MASK;
			अगर (val)
				conf[1] |= MADERA_GP1_सूची;
			अन्यथा
				conf[1] &= ~MADERA_GP1_सूची;
			अवरोध;
		हाल PIN_CONFIG_INPUT_SCHMITT:
			val = pinconf_to_config_argument(*configs);
			mask[0] |= MADERA_GP1_IP_CFG;
			अगर (val)
				conf[0] |= MADERA_GP1_IP_CFG;
			अन्यथा
				conf[0] &= ~MADERA_GP1_IP_CFG;

			mask[1] |= MADERA_GP1_सूची_MASK;
			conf[1] |= MADERA_GP1_सूची;
			अवरोध;
		हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
			mask[0] |= MADERA_GP1_IP_CFG;
			conf[0] |= MADERA_GP1_IP_CFG;
			mask[1] |= MADERA_GP1_सूची_MASK;
			conf[1] |= MADERA_GP1_सूची;
			अवरोध;
		हाल PIN_CONFIG_OUTPUT:
			val = pinconf_to_config_argument(*configs);
			mask[0] |= MADERA_GP1_LVL_MASK;
			अगर (val)
				conf[0] |= MADERA_GP1_LVL;
			अन्यथा
				conf[0] &= ~MADERA_GP1_LVL;

			mask[1] |= MADERA_GP1_सूची_MASK;
			conf[1] &= ~MADERA_GP1_सूची;
			अवरोध;
		शेष:
			वापस -ENOTSUPP;
		पूर्ण

		++configs;
		--num_configs;
	पूर्ण

	dev_dbg(priv->dev,
		"%s gpio%d 0x%x:0x%x 0x%x:0x%x\n",
		__func__, pin + 1, reg, conf[0], reg + 1, conf[1]);

	ret = regmap_update_bits(priv->madera->regmap, reg, mask[0], conf[0]);
	अगर (ret)
		जाओ err;

	++reg;
	ret = regmap_update_bits(priv->madera->regmap, reg, mask[1], conf[1]);
	अगर (ret)
		जाओ err;

	वापस 0;

err:
	dev_err(priv->dev,
		"Failed to write GPIO%d conf (%d) reg 0x%x\n",
		pin + 1, ret, reg);

	वापस ret;
पूर्ण

अटल पूर्णांक madera_pin_conf_group_set(काष्ठा pinctrl_dev *pctldev,
				     अचिन्हित पूर्णांक selector,
				     अचिन्हित दीर्घ *configs,
				     अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा madera_pin_निजी *priv = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा madera_pin_groups *pin_group;
	अचिन्हित पूर्णांक n_groups = priv->chip->n_pin_groups;
	पूर्णांक i, ret;

	dev_dbg(priv->dev, "%s setting group %s\n", __func__,
		madera_get_group_name(pctldev, selector));

	अगर (selector >= n_groups) अणु
		/* group is a single pin, convert to pin number and set */
		वापस madera_pin_conf_set(pctldev,
					   selector - n_groups,
					   configs,
					   num_configs);
	पूर्ण अन्यथा अणु
		pin_group = &priv->chip->pin_groups[selector];

		क्रम (i = 0; i < pin_group->n_pins; ++i) अणु
			ret = madera_pin_conf_set(pctldev,
						  pin_group->pins[i],
						  configs,
						  num_configs);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops madera_pin_conf_ops = अणु
	.is_generic = true,
	.pin_config_get = madera_pin_conf_get,
	.pin_config_set = madera_pin_conf_set,
	.pin_config_group_set = madera_pin_conf_group_set,
पूर्ण;

अटल काष्ठा pinctrl_desc madera_pin_desc = अणु
	.name = "madera-pinctrl",
	.pins = madera_pins,
	.pctlops = &madera_pin_group_ops,
	.pmxops = &madera_pin_mux_ops,
	.confops = &madera_pin_conf_ops,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक madera_pin_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा madera *madera = dev_get_drvdata(pdev->dev.parent);
	स्थिर काष्ठा madera_pdata *pdata = &madera->pdata;
	काष्ठा madera_pin_निजी *priv;
	पूर्णांक ret;

	BUILD_BUG_ON(ARRAY_SIZE(madera_pin_single_group_names) !=
		     ARRAY_SIZE(madera_pin_single_group_pins));

	dev_dbg(&pdev->dev, "%s\n", __func__);

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = &pdev->dev;
	priv->madera = madera;
	pdev->dev.of_node = madera->dev->of_node;

	चयन (madera->type) अणु
	हाल CS47L15:
		अगर (IS_ENABLED(CONFIG_PINCTRL_CS47L15))
			priv->chip = &cs47l15_pin_chip;
		अवरोध;
	हाल CS47L35:
		अगर (IS_ENABLED(CONFIG_PINCTRL_CS47L35))
			priv->chip = &cs47l35_pin_chip;
		अवरोध;
	हाल CS47L85:
	हाल WM1840:
		अगर (IS_ENABLED(CONFIG_PINCTRL_CS47L85))
			priv->chip = &cs47l85_pin_chip;
		अवरोध;
	हाल CS47L90:
	हाल CS47L91:
		अगर (IS_ENABLED(CONFIG_PINCTRL_CS47L90))
			priv->chip = &cs47l90_pin_chip;
		अवरोध;
	हाल CS42L92:
	हाल CS47L92:
	हाल CS47L93:
		अगर (IS_ENABLED(CONFIG_PINCTRL_CS47L92))
			priv->chip = &cs47l92_pin_chip;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (!priv->chip)
		वापस -ENODEV;

	madera_pin_desc.npins = priv->chip->n_pins;

	ret = devm_pinctrl_रेजिस्टर_and_init(&pdev->dev,
					     &madera_pin_desc,
					     priv,
					     &priv->pctl);
	अगर (ret) अणु
		dev_err(priv->dev, "Failed pinctrl register (%d)\n", ret);
		वापस ret;
	पूर्ण

	/* अगर the configuration is provided through pdata, apply it */
	अगर (pdata->gpio_configs) अणु
		ret = pinctrl_रेजिस्टर_mappings(pdata->gpio_configs,
						pdata->n_gpio_configs);
		अगर (ret) अणु
			dev_err(priv->dev,
				"Failed to register pdata mappings (%d)\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = pinctrl_enable(priv->pctl);
	अगर (ret) अणु
		dev_err(priv->dev, "Failed to enable pinctrl (%d)\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv);

	dev_dbg(priv->dev, "pinctrl probed ok\n");

	वापस 0;
पूर्ण

अटल पूर्णांक madera_pin_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा madera_pin_निजी *priv = platक्रमm_get_drvdata(pdev);

	अगर (priv->madera->pdata.gpio_configs)
		pinctrl_unरेजिस्टर_mappings(priv->madera->pdata.gpio_configs);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver madera_pin_driver = अणु
	.probe = madera_pin_probe,
	.हटाओ = madera_pin_हटाओ,
	.driver = अणु
		.name = "madera-pinctrl",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(madera_pin_driver);

MODULE_DESCRIPTION("Madera pinctrl driver");
MODULE_AUTHOR("Richard Fitzgerald <rf@opensource.cirrus.com>");
MODULE_LICENSE("GPL v2");
