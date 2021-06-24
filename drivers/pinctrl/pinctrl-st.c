<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 STMicroelectronics (R&D) Limited.
 * Authors:
 *	Srinivas Kandagatla <srinivas.kandagatla@st.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_gpपन.स> /* of_get_named_gpio() */
#समावेश <linux/of_address.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश "core.h"

/* PIO Block रेजिस्टरs */
/* PIO output */
#घोषणा REG_PIO_POUT			0x00
/* Set bits of POUT */
#घोषणा REG_PIO_SET_POUT		0x04
/* Clear bits of POUT */
#घोषणा REG_PIO_CLR_POUT		0x08
/* PIO input */
#घोषणा REG_PIO_PIN			0x10
/* PIO configuration */
#घोषणा REG_PIO_PC(n)			(0x20 + (n) * 0x10)
/* Set bits of PC[2:0] */
#घोषणा REG_PIO_SET_PC(n)		(0x24 + (n) * 0x10)
/* Clear bits of PC[2:0] */
#घोषणा REG_PIO_CLR_PC(n)		(0x28 + (n) * 0x10)
/* PIO input comparison */
#घोषणा REG_PIO_PCOMP			0x50
/* Set bits of PCOMP */
#घोषणा REG_PIO_SET_PCOMP		0x54
/* Clear bits of PCOMP */
#घोषणा REG_PIO_CLR_PCOMP		0x58
/* PIO input comparison mask */
#घोषणा REG_PIO_PMASK			0x60
/* Set bits of PMASK */
#घोषणा REG_PIO_SET_PMASK		0x64
/* Clear bits of PMASK */
#घोषणा REG_PIO_CLR_PMASK		0x68

#घोषणा ST_GPIO_सूचीECTION_BIसूची	0x1
#घोषणा ST_GPIO_सूचीECTION_OUT	0x2
#घोषणा ST_GPIO_सूचीECTION_IN	0x4

/**
 *  Packed style reसमय configuration.
 *  There are two रेजिस्टरs cfg0 and cfg1 in this style क्रम each bank.
 *  Each field in this रेजिस्टर is 8 bit corresponding to 8 pins in the bank.
 */
#घोषणा RT_P_CFGS_PER_BANK			2
#घोषणा RT_P_CFG0_CLK1NOTCLK0_FIELD(reg)	REG_FIELD(reg, 0, 7)
#घोषणा RT_P_CFG0_DELAY_0_FIELD(reg)		REG_FIELD(reg, 16, 23)
#घोषणा RT_P_CFG0_DELAY_1_FIELD(reg)		REG_FIELD(reg, 24, 31)
#घोषणा RT_P_CFG1_INVERTCLK_FIELD(reg)		REG_FIELD(reg, 0, 7)
#घोषणा RT_P_CFG1_RETIME_FIELD(reg)		REG_FIELD(reg, 8, 15)
#घोषणा RT_P_CFG1_CLKNOTDATA_FIELD(reg)		REG_FIELD(reg, 16, 23)
#घोषणा RT_P_CFG1_DOUBLE_EDGE_FIELD(reg)	REG_FIELD(reg, 24, 31)

/**
 * Dedicated style reसमय Configuration रेजिस्टर
 * each रेजिस्टर is dedicated per pin.
 */
#घोषणा RT_D_CFGS_PER_BANK		8
#घोषणा RT_D_CFG_CLK_SHIFT		0
#घोषणा RT_D_CFG_CLK_MASK		(0x3 << 0)
#घोषणा RT_D_CFG_CLKNOTDATA_SHIFT	2
#घोषणा RT_D_CFG_CLKNOTDATA_MASK	BIT(2)
#घोषणा RT_D_CFG_DELAY_SHIFT		3
#घोषणा RT_D_CFG_DELAY_MASK		(0xf << 3)
#घोषणा RT_D_CFG_DELAY_INNOTOUT_SHIFT	7
#घोषणा RT_D_CFG_DELAY_INNOTOUT_MASK	BIT(7)
#घोषणा RT_D_CFG_DOUBLE_EDGE_SHIFT	8
#घोषणा RT_D_CFG_DOUBLE_EDGE_MASK	BIT(8)
#घोषणा RT_D_CFG_INVERTCLK_SHIFT	9
#घोषणा RT_D_CFG_INVERTCLK_MASK		BIT(9)
#घोषणा RT_D_CFG_RETIME_SHIFT		10
#घोषणा RT_D_CFG_RETIME_MASK		BIT(10)

/*
 * Pinconf is represented in an opaque अचिन्हित दीर्घ variable.
 * Below is the bit allocation details क्रम each possible configuration.
 * All the bit fields can be encapsulated पूर्णांकo four variables
 * (direction, reसमय-type, reसमय-clk, reसमय-delay)
 *
 *	 +----------------+
 *[31:28]| reserved-3     |
 *	 +----------------+-------------
 *[27]   |	oe	  |		|
 *	 +----------------+		v
 *[26]   |	pu	  |	[Direction	]
 *	 +----------------+		^
 *[25]   |	od	  |		|
 *	 +----------------+-------------
 *[24]   | reserved-2     |
 *	 +----------------+-------------
 *[23]   |    reसमय      |		|
 *	 +----------------+		|
 *[22]   | reसमय-invclk  |		|
 *	 +----------------+		v
 *[21]   |reसमय-clknotdat|	[Reसमय-type	]
 *	 +----------------+		^
 *[20]   | reसमय-de      |		|
 *	 +----------------+-------------
 *[19:18]| reसमय-clk     |------>[Reसमय-Clk	]
 *	 +----------------+
 *[17:16]|  reserved-1    |
 *	 +----------------+
 *[15..0]| reसमय-delay   |------>[Reसमय Delay]
 *	 +----------------+
 */

#घोषणा ST_PINCONF_UNPACK(conf, param)\
				((conf >> ST_PINCONF_ ##param ##_SHIFT) \
				& ST_PINCONF_ ##param ##_MASK)

#घोषणा ST_PINCONF_PACK(conf, val, param)	(conf |=\
				((val & ST_PINCONF_ ##param ##_MASK) << \
					ST_PINCONF_ ##param ##_SHIFT))

/* Output enable */
#घोषणा ST_PINCONF_OE_MASK		0x1
#घोषणा ST_PINCONF_OE_SHIFT		27
#घोषणा ST_PINCONF_OE			BIT(27)
#घोषणा ST_PINCONF_UNPACK_OE(conf)	ST_PINCONF_UNPACK(conf, OE)
#घोषणा ST_PINCONF_PACK_OE(conf)	ST_PINCONF_PACK(conf, 1, OE)

/* Pull Up */
#घोषणा ST_PINCONF_PU_MASK		0x1
#घोषणा ST_PINCONF_PU_SHIFT		26
#घोषणा ST_PINCONF_PU			BIT(26)
#घोषणा ST_PINCONF_UNPACK_PU(conf)	ST_PINCONF_UNPACK(conf, PU)
#घोषणा ST_PINCONF_PACK_PU(conf)	ST_PINCONF_PACK(conf, 1, PU)

/* Open Drain */
#घोषणा ST_PINCONF_OD_MASK		0x1
#घोषणा ST_PINCONF_OD_SHIFT		25
#घोषणा ST_PINCONF_OD			BIT(25)
#घोषणा ST_PINCONF_UNPACK_OD(conf)	ST_PINCONF_UNPACK(conf, OD)
#घोषणा ST_PINCONF_PACK_OD(conf)	ST_PINCONF_PACK(conf, 1, OD)

#घोषणा ST_PINCONF_RT_MASK		0x1
#घोषणा ST_PINCONF_RT_SHIFT		23
#घोषणा ST_PINCONF_RT			BIT(23)
#घोषणा ST_PINCONF_UNPACK_RT(conf)	ST_PINCONF_UNPACK(conf, RT)
#घोषणा ST_PINCONF_PACK_RT(conf)	ST_PINCONF_PACK(conf, 1, RT)

#घोषणा ST_PINCONF_RT_INVERTCLK_MASK	0x1
#घोषणा ST_PINCONF_RT_INVERTCLK_SHIFT	22
#घोषणा ST_PINCONF_RT_INVERTCLK		BIT(22)
#घोषणा ST_PINCONF_UNPACK_RT_INVERTCLK(conf) \
			ST_PINCONF_UNPACK(conf, RT_INVERTCLK)
#घोषणा ST_PINCONF_PACK_RT_INVERTCLK(conf) \
			ST_PINCONF_PACK(conf, 1, RT_INVERTCLK)

#घोषणा ST_PINCONF_RT_CLKNOTDATA_MASK	0x1
#घोषणा ST_PINCONF_RT_CLKNOTDATA_SHIFT	21
#घोषणा ST_PINCONF_RT_CLKNOTDATA	BIT(21)
#घोषणा ST_PINCONF_UNPACK_RT_CLKNOTDATA(conf)	\
				ST_PINCONF_UNPACK(conf, RT_CLKNOTDATA)
#घोषणा ST_PINCONF_PACK_RT_CLKNOTDATA(conf) \
				ST_PINCONF_PACK(conf, 1, RT_CLKNOTDATA)

#घोषणा ST_PINCONF_RT_DOUBLE_EDGE_MASK	0x1
#घोषणा ST_PINCONF_RT_DOUBLE_EDGE_SHIFT	20
#घोषणा ST_PINCONF_RT_DOUBLE_EDGE	BIT(20)
#घोषणा ST_PINCONF_UNPACK_RT_DOUBLE_EDGE(conf) \
				ST_PINCONF_UNPACK(conf, RT_DOUBLE_EDGE)
#घोषणा ST_PINCONF_PACK_RT_DOUBLE_EDGE(conf) \
				ST_PINCONF_PACK(conf, 1, RT_DOUBLE_EDGE)

#घोषणा ST_PINCONF_RT_CLK_MASK		0x3
#घोषणा ST_PINCONF_RT_CLK_SHIFT		18
#घोषणा ST_PINCONF_RT_CLK		BIT(18)
#घोषणा ST_PINCONF_UNPACK_RT_CLK(conf)	ST_PINCONF_UNPACK(conf, RT_CLK)
#घोषणा ST_PINCONF_PACK_RT_CLK(conf, val) ST_PINCONF_PACK(conf, val, RT_CLK)

/* RETIME_DELAY in Pico Secs */
#घोषणा ST_PINCONF_RT_DELAY_MASK	0xffff
#घोषणा ST_PINCONF_RT_DELAY_SHIFT	0
#घोषणा ST_PINCONF_UNPACK_RT_DELAY(conf) ST_PINCONF_UNPACK(conf, RT_DELAY)
#घोषणा ST_PINCONF_PACK_RT_DELAY(conf, val) \
				ST_PINCONF_PACK(conf, val, RT_DELAY)

#घोषणा ST_GPIO_PINS_PER_BANK	(8)
#घोषणा OF_GPIO_ARGS_MIN	(4)
#घोषणा OF_RT_ARGS_MIN		(2)

#घोषणा gpio_range_to_bank(chip) \
		container_of(chip, काष्ठा st_gpio_bank, range)

#घोषणा pc_to_bank(pc) \
		container_of(pc, काष्ठा st_gpio_bank, pc)

क्रमागत st_reसमय_style अणु
	st_reसमय_style_none,
	st_reसमय_style_packed,
	st_reसमय_style_dedicated,
पूर्ण;

काष्ठा st_reसमय_dedicated अणु
	काष्ठा regmap_field *rt[ST_GPIO_PINS_PER_BANK];
पूर्ण;

काष्ठा st_reसमय_packed अणु
	काष्ठा regmap_field *clk1notclk0;
	काष्ठा regmap_field *delay_0;
	काष्ठा regmap_field *delay_1;
	काष्ठा regmap_field *invertclk;
	काष्ठा regmap_field *reसमय;
	काष्ठा regmap_field *clknotdata;
	काष्ठा regmap_field *द्विगुन_edge;
पूर्ण;

काष्ठा st_pio_control अणु
	u32 rt_pin_mask;
	काष्ठा regmap_field *alt, *oe, *pu, *od;
	/* retiming */
	जोड़ अणु
		काष्ठा st_reसमय_packed		rt_p;
		काष्ठा st_reसमय_dedicated	rt_d;
	पूर्ण rt;
पूर्ण;

काष्ठा st_pctl_data अणु
	स्थिर क्रमागत st_reसमय_style	rt_style;
	स्थिर अचिन्हित पूर्णांक		*input_delays;
	स्थिर पूर्णांक			ninput_delays;
	स्थिर अचिन्हित पूर्णांक		*output_delays;
	स्थिर पूर्णांक			noutput_delays;
	/* रेजिस्टर offset inक्रमmation */
	स्थिर पूर्णांक alt, oe, pu, od, rt;
पूर्ण;

काष्ठा st_pinconf अणु
	पूर्णांक		pin;
	स्थिर अक्षर	*name;
	अचिन्हित दीर्घ	config;
	पूर्णांक		altfunc;
पूर्ण;

काष्ठा st_pmx_func अणु
	स्थिर अक्षर	*name;
	स्थिर अक्षर	**groups;
	अचिन्हित	ngroups;
पूर्ण;

काष्ठा st_pctl_group अणु
	स्थिर अक्षर		*name;
	अचिन्हित पूर्णांक		*pins;
	अचिन्हित		npins;
	काष्ठा st_pinconf	*pin_conf;
पूर्ण;

/*
 * Edge triggers are not supported at hardware level, it is supported by
 * software by exploiting the level trigger support in hardware.
 * Software uses a भव रेजिस्टर (EDGE_CONF) क्रम edge trigger configuration
 * of each gpio pin in a GPIO bank.
 *
 * Each bank has a 32 bit EDGE_CONF रेजिस्टर which is भागided in to 8 parts of
 * 4-bits. Each 4-bit space is allocated क्रम each pin in a gpio bank.
 *
 * bit allocation per pin is:
 * Bits:  [0 - 3] | [4 - 7]  [8 - 11] ... ... ... ...  [ 28 - 31]
 *       --------------------------------------------------------
 *       |  pin-0  |  pin-2 | pin-3  | ... ... ... ... | pin -7 |
 *       --------------------------------------------------------
 *
 *  A pin can have one of following the values in its edge configuration field.
 *
 *	-------   ----------------------------
 *	[0-3]	- Description
 *	-------   ----------------------------
 *	0000	- No edge IRQ.
 *	0001	- Falling edge IRQ.
 *	0010	- Rising edge IRQ.
 *	0011	- Rising and Falling edge IRQ.
 *	-------   ----------------------------
 */

#घोषणा ST_IRQ_EDGE_CONF_BITS_PER_PIN	4
#घोषणा ST_IRQ_EDGE_MASK		0xf
#घोषणा ST_IRQ_EDGE_FALLING		BIT(0)
#घोषणा ST_IRQ_EDGE_RISING		BIT(1)
#घोषणा ST_IRQ_EDGE_BOTH		(BIT(0) | BIT(1))

#घोषणा ST_IRQ_RISING_EDGE_CONF(pin) \
	(ST_IRQ_EDGE_RISING << (pin * ST_IRQ_EDGE_CONF_BITS_PER_PIN))

#घोषणा ST_IRQ_FALLING_EDGE_CONF(pin) \
	(ST_IRQ_EDGE_FALLING << (pin * ST_IRQ_EDGE_CONF_BITS_PER_PIN))

#घोषणा ST_IRQ_BOTH_EDGE_CONF(pin) \
	(ST_IRQ_EDGE_BOTH << (pin * ST_IRQ_EDGE_CONF_BITS_PER_PIN))

#घोषणा ST_IRQ_EDGE_CONF(conf, pin) \
	(conf >> (pin * ST_IRQ_EDGE_CONF_BITS_PER_PIN) & ST_IRQ_EDGE_MASK)

काष्ठा st_gpio_bank अणु
	काष्ठा gpio_chip		gpio_chip;
	काष्ठा pinctrl_gpio_range	range;
	व्योम __iomem			*base;
	काष्ठा st_pio_control		pc;
	अचिन्हित दीर्घ			irq_edge_conf;
	spinlock_t                      lock;
पूर्ण;

काष्ठा st_pinctrl अणु
	काष्ठा device			*dev;
	काष्ठा pinctrl_dev		*pctl;
	काष्ठा st_gpio_bank		*banks;
	पूर्णांक				nbanks;
	काष्ठा st_pmx_func		*functions;
	पूर्णांक				nfunctions;
	काष्ठा st_pctl_group		*groups;
	पूर्णांक				ngroups;
	काष्ठा regmap			*regmap;
	स्थिर काष्ठा st_pctl_data	*data;
	व्योम __iomem			*irqmux_base;
पूर्ण;

/* SOC specअगरic data */

अटल स्थिर अचिन्हित पूर्णांक stih407_delays[] = अणु0, 300, 500, 750, 1000, 1250,
			1500, 1750, 2000, 2250, 2500, 2750, 3000, 3250 पूर्ण;

अटल स्थिर काष्ठा st_pctl_data  stih407_data = अणु
	.rt_style       = st_reसमय_style_dedicated,
	.input_delays   = stih407_delays,
	.ninput_delays  = ARRAY_SIZE(stih407_delays),
	.output_delays  = stih407_delays,
	.noutput_delays = ARRAY_SIZE(stih407_delays),
	.alt = 0, .oe = 40, .pu = 50, .od = 60, .rt = 100,
पूर्ण;

अटल स्थिर काष्ठा st_pctl_data stih407_flashdata = अणु
	.rt_style	= st_reसमय_style_none,
	.input_delays	= stih407_delays,
	.ninput_delays	= ARRAY_SIZE(stih407_delays),
	.output_delays	= stih407_delays,
	.noutput_delays = ARRAY_SIZE(stih407_delays),
	.alt = 0,
	.oe = -1, /* Not Available */
	.pu = -1, /* Not Available */
	.od = 60,
	.rt = 100,
पूर्ण;

अटल काष्ठा st_pio_control *st_get_pio_control(
			काष्ठा pinctrl_dev *pctldev, पूर्णांक pin)
अणु
	काष्ठा pinctrl_gpio_range *range =
			 pinctrl_find_gpio_range_from_pin(pctldev, pin);
	काष्ठा st_gpio_bank *bank = gpio_range_to_bank(range);

	वापस &bank->pc;
पूर्ण

/* Low level functions.. */
अटल अंतरभूत पूर्णांक st_gpio_bank(पूर्णांक gpio)
अणु
	वापस gpio/ST_GPIO_PINS_PER_BANK;
पूर्ण

अटल अंतरभूत पूर्णांक st_gpio_pin(पूर्णांक gpio)
अणु
	वापस gpio%ST_GPIO_PINS_PER_BANK;
पूर्ण

अटल व्योम st_pinconf_set_config(काष्ठा st_pio_control *pc,
				पूर्णांक pin, अचिन्हित दीर्घ config)
अणु
	काष्ठा regmap_field *output_enable = pc->oe;
	काष्ठा regmap_field *pull_up = pc->pu;
	काष्ठा regmap_field *खोलो_drain = pc->od;
	अचिन्हित पूर्णांक oe_value, pu_value, od_value;
	अचिन्हित दीर्घ mask = BIT(pin);

	अगर (output_enable) अणु
		regmap_field_पढ़ो(output_enable, &oe_value);
		oe_value &= ~mask;
		अगर (config & ST_PINCONF_OE)
			oe_value |= mask;
		regmap_field_ग_लिखो(output_enable, oe_value);
	पूर्ण

	अगर (pull_up) अणु
		regmap_field_पढ़ो(pull_up, &pu_value);
		pu_value &= ~mask;
		अगर (config & ST_PINCONF_PU)
			pu_value |= mask;
		regmap_field_ग_लिखो(pull_up, pu_value);
	पूर्ण

	अगर (खोलो_drain) अणु
		regmap_field_पढ़ो(खोलो_drain, &od_value);
		od_value &= ~mask;
		अगर (config & ST_PINCONF_OD)
			od_value |= mask;
		regmap_field_ग_लिखो(खोलो_drain, od_value);
	पूर्ण
पूर्ण

अटल व्योम st_pctl_set_function(काष्ठा st_pio_control *pc,
				पूर्णांक pin_id, पूर्णांक function)
अणु
	काष्ठा regmap_field *alt = pc->alt;
	अचिन्हित पूर्णांक val;
	पूर्णांक pin = st_gpio_pin(pin_id);
	पूर्णांक offset = pin * 4;

	अगर (!alt)
		वापस;

	regmap_field_पढ़ो(alt, &val);
	val &= ~(0xf << offset);
	val |= function << offset;
	regmap_field_ग_लिखो(alt, val);
पूर्ण

अटल अचिन्हित पूर्णांक st_pctl_get_pin_function(काष्ठा st_pio_control *pc, पूर्णांक pin)
अणु
	काष्ठा regmap_field *alt = pc->alt;
	अचिन्हित पूर्णांक val;
	पूर्णांक offset = pin * 4;

	अगर (!alt)
		वापस 0;

	regmap_field_पढ़ो(alt, &val);

	वापस (val >> offset) & 0xf;
पूर्ण

अटल अचिन्हित दीर्घ st_pinconf_delay_to_bit(अचिन्हित पूर्णांक delay,
	स्थिर काष्ठा st_pctl_data *data, अचिन्हित दीर्घ config)
अणु
	स्थिर अचिन्हित पूर्णांक *delay_बार;
	पूर्णांक num_delay_बार, i, बंदst_index = -1;
	अचिन्हित पूर्णांक बंदst_भागergence = अच_पूर्णांक_उच्च;

	अगर (ST_PINCONF_UNPACK_OE(config)) अणु
		delay_बार = data->output_delays;
		num_delay_बार = data->noutput_delays;
	पूर्ण अन्यथा अणु
		delay_बार = data->input_delays;
		num_delay_बार = data->ninput_delays;
	पूर्ण

	क्रम (i = 0; i < num_delay_बार; i++) अणु
		अचिन्हित पूर्णांक भागergence = असल(delay - delay_बार[i]);

		अगर (भागergence == 0)
			वापस i;

		अगर (भागergence < बंदst_भागergence) अणु
			बंदst_भागergence = भागergence;
			बंदst_index = i;
		पूर्ण
	पूर्ण

	pr_warn("Attempt to set delay %d, closest available %d\n",
	     delay, delay_बार[बंदst_index]);

	वापस बंदst_index;
पूर्ण

अटल अचिन्हित दीर्घ st_pinconf_bit_to_delay(अचिन्हित पूर्णांक index,
	स्थिर काष्ठा st_pctl_data *data, अचिन्हित दीर्घ output)
अणु
	स्थिर अचिन्हित पूर्णांक *delay_बार;
	पूर्णांक num_delay_बार;

	अगर (output) अणु
		delay_बार = data->output_delays;
		num_delay_बार = data->noutput_delays;
	पूर्ण अन्यथा अणु
		delay_बार = data->input_delays;
		num_delay_बार = data->ninput_delays;
	पूर्ण

	अगर (index < num_delay_बार) अणु
		वापस delay_बार[index];
	पूर्ण अन्यथा अणु
		pr_warn("Delay not found in/out delay list\n");
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम st_regmap_field_bit_set_clear_pin(काष्ठा regmap_field *field,
	पूर्णांक enable, पूर्णांक pin)
अणु
	अचिन्हित पूर्णांक val = 0;

	regmap_field_पढ़ो(field, &val);
	अगर (enable)
		val |= BIT(pin);
	अन्यथा
		val &= ~BIT(pin);
	regmap_field_ग_लिखो(field, val);
पूर्ण

अटल व्योम st_pinconf_set_reसमय_packed(काष्ठा st_pinctrl *info,
	काष्ठा st_pio_control *pc,	अचिन्हित दीर्घ config, पूर्णांक pin)
अणु
	स्थिर काष्ठा st_pctl_data *data = info->data;
	काष्ठा st_reसमय_packed *rt_p = &pc->rt.rt_p;
	अचिन्हित पूर्णांक delay;

	st_regmap_field_bit_set_clear_pin(rt_p->clk1notclk0,
				ST_PINCONF_UNPACK_RT_CLK(config), pin);

	st_regmap_field_bit_set_clear_pin(rt_p->clknotdata,
				ST_PINCONF_UNPACK_RT_CLKNOTDATA(config), pin);

	st_regmap_field_bit_set_clear_pin(rt_p->द्विगुन_edge,
				ST_PINCONF_UNPACK_RT_DOUBLE_EDGE(config), pin);

	st_regmap_field_bit_set_clear_pin(rt_p->invertclk,
				ST_PINCONF_UNPACK_RT_INVERTCLK(config), pin);

	st_regmap_field_bit_set_clear_pin(rt_p->reसमय,
				ST_PINCONF_UNPACK_RT(config), pin);

	delay = st_pinconf_delay_to_bit(ST_PINCONF_UNPACK_RT_DELAY(config),
					data, config);
	/* 2 bit delay, lsb */
	st_regmap_field_bit_set_clear_pin(rt_p->delay_0, delay & 0x1, pin);
	/* 2 bit delay, msb */
	st_regmap_field_bit_set_clear_pin(rt_p->delay_1, delay & 0x2, pin);
पूर्ण

अटल व्योम st_pinconf_set_reसमय_dedicated(काष्ठा st_pinctrl *info,
	काष्ठा st_pio_control *pc, अचिन्हित दीर्घ config, पूर्णांक pin)
अणु
	पूर्णांक input	= ST_PINCONF_UNPACK_OE(config) ? 0 : 1;
	पूर्णांक clk		= ST_PINCONF_UNPACK_RT_CLK(config);
	पूर्णांक clknotdata	= ST_PINCONF_UNPACK_RT_CLKNOTDATA(config);
	पूर्णांक द्विगुन_edge	= ST_PINCONF_UNPACK_RT_DOUBLE_EDGE(config);
	पूर्णांक invertclk	= ST_PINCONF_UNPACK_RT_INVERTCLK(config);
	पूर्णांक reसमय	= ST_PINCONF_UNPACK_RT(config);

	अचिन्हित दीर्घ delay = st_pinconf_delay_to_bit(
			ST_PINCONF_UNPACK_RT_DELAY(config),
			info->data, config);
	काष्ठा st_reसमय_dedicated *rt_d = &pc->rt.rt_d;

	अचिन्हित दीर्घ reसमय_config =
		((clk) << RT_D_CFG_CLK_SHIFT) |
		((delay) << RT_D_CFG_DELAY_SHIFT) |
		((input) << RT_D_CFG_DELAY_INNOTOUT_SHIFT) |
		((reसमय) << RT_D_CFG_RETIME_SHIFT) |
		((clknotdata) << RT_D_CFG_CLKNOTDATA_SHIFT) |
		((invertclk) << RT_D_CFG_INVERTCLK_SHIFT) |
		((द्विगुन_edge) << RT_D_CFG_DOUBLE_EDGE_SHIFT);

	regmap_field_ग_लिखो(rt_d->rt[pin], reसमय_config);
पूर्ण

अटल व्योम st_pinconf_get_direction(काष्ठा st_pio_control *pc,
	पूर्णांक pin, अचिन्हित दीर्घ *config)
अणु
	अचिन्हित पूर्णांक oe_value, pu_value, od_value;

	अगर (pc->oe) अणु
		regmap_field_पढ़ो(pc->oe, &oe_value);
		अगर (oe_value & BIT(pin))
			ST_PINCONF_PACK_OE(*config);
	पूर्ण

	अगर (pc->pu) अणु
		regmap_field_पढ़ो(pc->pu, &pu_value);
		अगर (pu_value & BIT(pin))
			ST_PINCONF_PACK_PU(*config);
	पूर्ण

	अगर (pc->od) अणु
		regmap_field_पढ़ो(pc->od, &od_value);
		अगर (od_value & BIT(pin))
			ST_PINCONF_PACK_OD(*config);
	पूर्ण
पूर्ण

अटल पूर्णांक st_pinconf_get_reसमय_packed(काष्ठा st_pinctrl *info,
	काष्ठा st_pio_control *pc,	पूर्णांक pin, अचिन्हित दीर्घ *config)
अणु
	स्थिर काष्ठा st_pctl_data *data = info->data;
	काष्ठा st_reसमय_packed *rt_p = &pc->rt.rt_p;
	अचिन्हित पूर्णांक delay_bits, delay, delay0, delay1, val;
	पूर्णांक output = ST_PINCONF_UNPACK_OE(*config);

	अगर (!regmap_field_पढ़ो(rt_p->reसमय, &val) && (val & BIT(pin)))
		ST_PINCONF_PACK_RT(*config);

	अगर (!regmap_field_पढ़ो(rt_p->clk1notclk0, &val) && (val & BIT(pin)))
		ST_PINCONF_PACK_RT_CLK(*config, 1);

	अगर (!regmap_field_पढ़ो(rt_p->clknotdata, &val) && (val & BIT(pin)))
		ST_PINCONF_PACK_RT_CLKNOTDATA(*config);

	अगर (!regmap_field_पढ़ो(rt_p->द्विगुन_edge, &val) && (val & BIT(pin)))
		ST_PINCONF_PACK_RT_DOUBLE_EDGE(*config);

	अगर (!regmap_field_पढ़ो(rt_p->invertclk, &val) && (val & BIT(pin)))
		ST_PINCONF_PACK_RT_INVERTCLK(*config);

	regmap_field_पढ़ो(rt_p->delay_0, &delay0);
	regmap_field_पढ़ो(rt_p->delay_1, &delay1);
	delay_bits = (((delay1 & BIT(pin)) ? 1 : 0) << 1) |
			(((delay0 & BIT(pin)) ? 1 : 0));
	delay =  st_pinconf_bit_to_delay(delay_bits, data, output);
	ST_PINCONF_PACK_RT_DELAY(*config, delay);

	वापस 0;
पूर्ण

अटल पूर्णांक st_pinconf_get_reसमय_dedicated(काष्ठा st_pinctrl *info,
	काष्ठा st_pio_control *pc,	पूर्णांक pin, अचिन्हित दीर्घ *config)
अणु
	अचिन्हित पूर्णांक value;
	अचिन्हित दीर्घ delay_bits, delay, rt_clk;
	पूर्णांक output = ST_PINCONF_UNPACK_OE(*config);
	काष्ठा st_reसमय_dedicated *rt_d = &pc->rt.rt_d;

	regmap_field_पढ़ो(rt_d->rt[pin], &value);

	rt_clk = (value & RT_D_CFG_CLK_MASK) >> RT_D_CFG_CLK_SHIFT;
	ST_PINCONF_PACK_RT_CLK(*config, rt_clk);

	delay_bits = (value & RT_D_CFG_DELAY_MASK) >> RT_D_CFG_DELAY_SHIFT;
	delay =  st_pinconf_bit_to_delay(delay_bits, info->data, output);
	ST_PINCONF_PACK_RT_DELAY(*config, delay);

	अगर (value & RT_D_CFG_CLKNOTDATA_MASK)
		ST_PINCONF_PACK_RT_CLKNOTDATA(*config);

	अगर (value & RT_D_CFG_DOUBLE_EDGE_MASK)
		ST_PINCONF_PACK_RT_DOUBLE_EDGE(*config);

	अगर (value & RT_D_CFG_INVERTCLK_MASK)
		ST_PINCONF_PACK_RT_INVERTCLK(*config);

	अगर (value & RT_D_CFG_RETIME_MASK)
		ST_PINCONF_PACK_RT(*config);

	वापस 0;
पूर्ण

/* GPIO related functions */

अटल अंतरभूत व्योम __st_gpio_set(काष्ठा st_gpio_bank *bank,
	अचिन्हित offset, पूर्णांक value)
अणु
	अगर (value)
		ग_लिखोl(BIT(offset), bank->base + REG_PIO_SET_POUT);
	अन्यथा
		ग_लिखोl(BIT(offset), bank->base + REG_PIO_CLR_POUT);
पूर्ण

अटल व्योम st_gpio_direction(काष्ठा st_gpio_bank *bank,
		अचिन्हित पूर्णांक gpio, अचिन्हित पूर्णांक direction)
अणु
	पूर्णांक offset = st_gpio_pin(gpio);
	पूर्णांक i = 0;
	/**
	 * There are three configuration रेजिस्टरs (PIOn_PC0, PIOn_PC1
	 * and PIOn_PC2) क्रम each port. These are used to configure the
	 * PIO port pins. Each pin can be configured as an input, output,
	 * bidirectional, or alternative function pin. Three bits, one bit
	 * from each of the three रेजिस्टरs, configure the corresponding bit of
	 * the port. Valid bit settings is:
	 *
	 * PC2		PC1		PC0	Direction.
	 * 0		0		0	[Input Weak pull-up]
	 * 0		0 or 1		1	[Bidirection]
	 * 0		1		0	[Output]
	 * 1		0		0	[Input]
	 *
	 * PIOn_SET_PC and PIOn_CLR_PC रेजिस्टरs are used to set and clear bits
	 * inभागidually.
	 */
	क्रम (i = 0; i <= 2; i++) अणु
		अगर (direction & BIT(i))
			ग_लिखोl(BIT(offset), bank->base + REG_PIO_SET_PC(i));
		अन्यथा
			ग_लिखोl(BIT(offset), bank->base + REG_PIO_CLR_PC(i));
	पूर्ण
पूर्ण

अटल पूर्णांक st_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा st_gpio_bank *bank = gpiochip_get_data(chip);

	वापस !!(पढ़ोl(bank->base + REG_PIO_PIN) & BIT(offset));
पूर्ण

अटल व्योम st_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा st_gpio_bank *bank = gpiochip_get_data(chip);
	__st_gpio_set(bank, offset, value);
पूर्ण

अटल पूर्णांक st_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	pinctrl_gpio_direction_input(chip->base + offset);

	वापस 0;
पूर्ण

अटल पूर्णांक st_gpio_direction_output(काष्ठा gpio_chip *chip,
	अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा st_gpio_bank *bank = gpiochip_get_data(chip);

	__st_gpio_set(bank, offset, value);
	pinctrl_gpio_direction_output(chip->base + offset);

	वापस 0;
पूर्ण

अटल पूर्णांक st_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा st_gpio_bank *bank = gpiochip_get_data(chip);
	काष्ठा st_pio_control pc = bank->pc;
	अचिन्हित दीर्घ config;
	अचिन्हित पूर्णांक direction = 0;
	अचिन्हित पूर्णांक function;
	अचिन्हित पूर्णांक value;
	पूर्णांक i = 0;

	/* Alternate function direction is handled by Pinctrl */
	function = st_pctl_get_pin_function(&pc, offset);
	अगर (function) अणु
		st_pinconf_get_direction(&pc, offset, &config);
		अगर (ST_PINCONF_UNPACK_OE(config))
			वापस GPIO_LINE_सूचीECTION_OUT;

		वापस GPIO_LINE_सूचीECTION_IN;
	पूर्ण

	/*
	 * GPIO direction is handled dअगरferently
	 * - See st_gpio_direction() above क्रम an explanation
	 */
	क्रम (i = 0; i <= 2; i++) अणु
		value = पढ़ोl(bank->base + REG_PIO_PC(i));
		direction |= ((value >> offset) & 0x1) << i;
	पूर्ण

	अगर (direction == ST_GPIO_सूचीECTION_IN)
		वापस GPIO_LINE_सूचीECTION_IN;

	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

/* Pinctrl Groups */
अटल पूर्णांक st_pctl_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा st_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);

	वापस info->ngroups;
पूर्ण

अटल स्थिर अक्षर *st_pctl_get_group_name(काष्ठा pinctrl_dev *pctldev,
				       अचिन्हित selector)
अणु
	काष्ठा st_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);

	वापस info->groups[selector].name;
पूर्ण

अटल पूर्णांक st_pctl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
	अचिन्हित selector, स्थिर अचिन्हित **pins, अचिन्हित *npins)
अणु
	काष्ठा st_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);

	अगर (selector >= info->ngroups)
		वापस -EINVAL;

	*pins = info->groups[selector].pins;
	*npins = info->groups[selector].npins;

	वापस 0;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा st_pctl_group *st_pctl_find_group_by_name(
	स्थिर काष्ठा st_pinctrl *info, स्थिर अक्षर *name)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < info->ngroups; i++) अणु
		अगर (!म_भेद(info->groups[i].name, name))
			वापस &info->groups[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक st_pctl_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
	काष्ठा device_node *np, काष्ठा pinctrl_map **map, अचिन्हित *num_maps)
अणु
	काष्ठा st_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा st_pctl_group *grp;
	काष्ठा pinctrl_map *new_map;
	काष्ठा device_node *parent;
	पूर्णांक map_num, i;

	grp = st_pctl_find_group_by_name(info, np->name);
	अगर (!grp) अणु
		dev_err(info->dev, "unable to find group for node %pOFn\n",
			np);
		वापस -EINVAL;
	पूर्ण

	map_num = grp->npins + 1;
	new_map = devm_kसुस्मृति(pctldev->dev,
				map_num, माप(*new_map), GFP_KERNEL);
	अगर (!new_map)
		वापस -ENOMEM;

	parent = of_get_parent(np);
	अगर (!parent) अणु
		devm_kमुक्त(pctldev->dev, new_map);
		वापस -EINVAL;
	पूर्ण

	*map = new_map;
	*num_maps = map_num;
	new_map[0].type = PIN_MAP_TYPE_MUX_GROUP;
	new_map[0].data.mux.function = parent->name;
	new_map[0].data.mux.group = np->name;
	of_node_put(parent);

	/* create config map per pin */
	new_map++;
	क्रम (i = 0; i < grp->npins; i++) अणु
		new_map[i].type = PIN_MAP_TYPE_CONFIGS_PIN;
		new_map[i].data.configs.group_or_pin =
				pin_get_name(pctldev, grp->pins[i]);
		new_map[i].data.configs.configs = &grp->pin_conf[i].config;
		new_map[i].data.configs.num_configs = 1;
	पूर्ण
	dev_info(pctldev->dev, "maps: function %s group %s num %d\n",
		(*map)->data.mux.function, grp->name, map_num);

	वापस 0;
पूर्ण

अटल व्योम st_pctl_dt_मुक्त_map(काष्ठा pinctrl_dev *pctldev,
			काष्ठा pinctrl_map *map, अचिन्हित num_maps)
अणु
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops st_pctlops = अणु
	.get_groups_count	= st_pctl_get_groups_count,
	.get_group_pins		= st_pctl_get_group_pins,
	.get_group_name		= st_pctl_get_group_name,
	.dt_node_to_map		= st_pctl_dt_node_to_map,
	.dt_मुक्त_map		= st_pctl_dt_मुक्त_map,
पूर्ण;

/* Pinmux */
अटल पूर्णांक st_pmx_get_funcs_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा st_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);

	वापस info->nfunctions;
पूर्ण

अटल स्थिर अक्षर *st_pmx_get_fname(काष्ठा pinctrl_dev *pctldev,
	अचिन्हित selector)
अणु
	काष्ठा st_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);

	वापस info->functions[selector].name;
पूर्ण

अटल पूर्णांक st_pmx_get_groups(काष्ठा pinctrl_dev *pctldev,
	अचिन्हित selector, स्थिर अक्षर * स्थिर **grps, अचिन्हित * स्थिर ngrps)
अणु
	काष्ठा st_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);
	*grps = info->functions[selector].groups;
	*ngrps = info->functions[selector].ngroups;

	वापस 0;
पूर्ण

अटल पूर्णांक st_pmx_set_mux(काष्ठा pinctrl_dev *pctldev, अचिन्हित fselector,
			अचिन्हित group)
अणु
	काष्ठा st_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा st_pinconf *conf = info->groups[group].pin_conf;
	काष्ठा st_pio_control *pc;
	पूर्णांक i;

	क्रम (i = 0; i < info->groups[group].npins; i++) अणु
		pc = st_get_pio_control(pctldev, conf[i].pin);
		st_pctl_set_function(pc, conf[i].pin, conf[i].altfunc);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक st_pmx_set_gpio_direction(काष्ठा pinctrl_dev *pctldev,
			काष्ठा pinctrl_gpio_range *range, अचिन्हित gpio,
			bool input)
अणु
	काष्ठा st_gpio_bank *bank = gpio_range_to_bank(range);
	/*
	 * When a PIO bank is used in its primary function mode (altfunc = 0)
	 * Output Enable (OE), Open Drain(OD), and Pull Up (PU)
	 * क्रम the primary PIO functions are driven by the related PIO block
	 */
	st_pctl_set_function(&bank->pc, gpio, 0);
	st_gpio_direction(bank, gpio, input ?
		ST_GPIO_सूचीECTION_IN : ST_GPIO_सूचीECTION_OUT);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops st_pmxops = अणु
	.get_functions_count	= st_pmx_get_funcs_count,
	.get_function_name	= st_pmx_get_fname,
	.get_function_groups	= st_pmx_get_groups,
	.set_mux		= st_pmx_set_mux,
	.gpio_set_direction	= st_pmx_set_gpio_direction,
	.strict			= true,
पूर्ण;

/* Pinconf  */
अटल व्योम st_pinconf_get_reसमय(काष्ठा st_pinctrl *info,
	काष्ठा st_pio_control *pc, पूर्णांक pin, अचिन्हित दीर्घ *config)
अणु
	अगर (info->data->rt_style == st_reसमय_style_packed)
		st_pinconf_get_reसमय_packed(info, pc, pin, config);
	अन्यथा अगर (info->data->rt_style == st_reसमय_style_dedicated)
		अगर ((BIT(pin) & pc->rt_pin_mask))
			st_pinconf_get_reसमय_dedicated(info, pc,
					pin, config);
पूर्ण

अटल व्योम st_pinconf_set_reसमय(काष्ठा st_pinctrl *info,
	काष्ठा st_pio_control *pc, पूर्णांक pin, अचिन्हित दीर्घ config)
अणु
	अगर (info->data->rt_style == st_reसमय_style_packed)
		st_pinconf_set_reसमय_packed(info, pc, config, pin);
	अन्यथा अगर (info->data->rt_style == st_reसमय_style_dedicated)
		अगर ((BIT(pin) & pc->rt_pin_mask))
			st_pinconf_set_reसमय_dedicated(info, pc,
							config, pin);
पूर्ण

अटल पूर्णांक st_pinconf_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin_id,
			अचिन्हित दीर्घ *configs, अचिन्हित num_configs)
अणु
	पूर्णांक pin = st_gpio_pin(pin_id);
	काष्ठा st_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा st_pio_control *pc = st_get_pio_control(pctldev, pin_id);
	पूर्णांक i;

	क्रम (i = 0; i < num_configs; i++) अणु
		st_pinconf_set_config(pc, pin, configs[i]);
		st_pinconf_set_reसमय(info, pc, pin, configs[i]);
	पूर्ण /* क्रम each config */

	वापस 0;
पूर्ण

अटल पूर्णांक st_pinconf_get(काष्ठा pinctrl_dev *pctldev,
			     अचिन्हित pin_id, अचिन्हित दीर्घ *config)
अणु
	पूर्णांक pin = st_gpio_pin(pin_id);
	काष्ठा st_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा st_pio_control *pc = st_get_pio_control(pctldev, pin_id);

	*config = 0;
	st_pinconf_get_direction(pc, pin, config);
	st_pinconf_get_reसमय(info, pc, pin, config);

	वापस 0;
पूर्ण

अटल व्योम st_pinconf_dbg_show(काष्ठा pinctrl_dev *pctldev,
				   काष्ठा seq_file *s, अचिन्हित pin_id)
अणु
	काष्ठा st_pio_control *pc;
	अचिन्हित दीर्घ config;
	अचिन्हित पूर्णांक function;
	पूर्णांक offset = st_gpio_pin(pin_id);
	अक्षर f[16];
	पूर्णांक oe;

	mutex_unlock(&pctldev->mutex);
	pc = st_get_pio_control(pctldev, pin_id);
	st_pinconf_get(pctldev, pin_id, &config);
	mutex_lock(&pctldev->mutex);

	function = st_pctl_get_pin_function(pc, offset);
	अगर (function)
		snम_लिखो(f, 10, "Alt Fn %u", function);
	अन्यथा
		snम_लिखो(f, 5, "GPIO");

	oe = st_gpio_get_direction(&pc_to_bank(pc)->gpio_chip, offset);
	seq_म_लिखो(s, "[OE:%d,PU:%ld,OD:%ld]\t%s\n"
		"\t\t[retime:%ld,invclk:%ld,clknotdat:%ld,"
		"de:%ld,rt-clk:%ld,rt-delay:%ld]",
		(oe == GPIO_LINE_सूचीECTION_OUT),
		ST_PINCONF_UNPACK_PU(config),
		ST_PINCONF_UNPACK_OD(config),
		f,
		ST_PINCONF_UNPACK_RT(config),
		ST_PINCONF_UNPACK_RT_INVERTCLK(config),
		ST_PINCONF_UNPACK_RT_CLKNOTDATA(config),
		ST_PINCONF_UNPACK_RT_DOUBLE_EDGE(config),
		ST_PINCONF_UNPACK_RT_CLK(config),
		ST_PINCONF_UNPACK_RT_DELAY(config));
पूर्ण

अटल स्थिर काष्ठा pinconf_ops st_confops = अणु
	.pin_config_get		= st_pinconf_get,
	.pin_config_set		= st_pinconf_set,
	.pin_config_dbg_show	= st_pinconf_dbg_show,
पूर्ण;

अटल व्योम st_pctl_dt_child_count(काष्ठा st_pinctrl *info,
				     काष्ठा device_node *np)
अणु
	काष्ठा device_node *child;
	क्रम_each_child_of_node(np, child) अणु
		अगर (of_property_पढ़ो_bool(child, "gpio-controller")) अणु
			info->nbanks++;
		पूर्ण अन्यथा अणु
			info->nfunctions++;
			info->ngroups += of_get_child_count(child);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक st_pctl_dt_setup_reसमय_packed(काष्ठा st_pinctrl *info,
	पूर्णांक bank, काष्ठा st_pio_control *pc)
अणु
	काष्ठा device *dev = info->dev;
	काष्ठा regmap *rm = info->regmap;
	स्थिर काष्ठा st_pctl_data *data = info->data;
	/* 2 रेजिस्टरs per bank */
	पूर्णांक reg = (data->rt + bank * RT_P_CFGS_PER_BANK) * 4;
	काष्ठा st_reसमय_packed *rt_p = &pc->rt.rt_p;
	/* cfg0 */
	काष्ठा reg_field clk1notclk0 = RT_P_CFG0_CLK1NOTCLK0_FIELD(reg);
	काष्ठा reg_field delay_0 = RT_P_CFG0_DELAY_0_FIELD(reg);
	काष्ठा reg_field delay_1 = RT_P_CFG0_DELAY_1_FIELD(reg);
	/* cfg1 */
	काष्ठा reg_field invertclk = RT_P_CFG1_INVERTCLK_FIELD(reg + 4);
	काष्ठा reg_field reसमय = RT_P_CFG1_RETIME_FIELD(reg + 4);
	काष्ठा reg_field clknotdata = RT_P_CFG1_CLKNOTDATA_FIELD(reg + 4);
	काष्ठा reg_field द्विगुन_edge = RT_P_CFG1_DOUBLE_EDGE_FIELD(reg + 4);

	rt_p->clk1notclk0 = devm_regmap_field_alloc(dev, rm, clk1notclk0);
	rt_p->delay_0	= devm_regmap_field_alloc(dev, rm, delay_0);
	rt_p->delay_1 = devm_regmap_field_alloc(dev, rm, delay_1);
	rt_p->invertclk = devm_regmap_field_alloc(dev, rm, invertclk);
	rt_p->reसमय = devm_regmap_field_alloc(dev, rm, reसमय);
	rt_p->clknotdata = devm_regmap_field_alloc(dev, rm, clknotdata);
	rt_p->द्विगुन_edge = devm_regmap_field_alloc(dev, rm, द्विगुन_edge);

	अगर (IS_ERR(rt_p->clk1notclk0) || IS_ERR(rt_p->delay_0) ||
		 IS_ERR(rt_p->delay_1) || IS_ERR(rt_p->invertclk) ||
		 IS_ERR(rt_p->reसमय) || IS_ERR(rt_p->clknotdata) ||
		 IS_ERR(rt_p->द्विगुन_edge))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक st_pctl_dt_setup_reसमय_dedicated(काष्ठा st_pinctrl *info,
	पूर्णांक bank, काष्ठा st_pio_control *pc)
अणु
	काष्ठा device *dev = info->dev;
	काष्ठा regmap *rm = info->regmap;
	स्थिर काष्ठा st_pctl_data *data = info->data;
	/* 8 रेजिस्टरs per bank */
	पूर्णांक reg_offset = (data->rt + bank * RT_D_CFGS_PER_BANK) * 4;
	काष्ठा st_reसमय_dedicated *rt_d = &pc->rt.rt_d;
	अचिन्हित पूर्णांक j;
	u32 pin_mask = pc->rt_pin_mask;

	क्रम (j = 0; j < RT_D_CFGS_PER_BANK; j++) अणु
		अगर (BIT(j) & pin_mask) अणु
			काष्ठा reg_field reg = REG_FIELD(reg_offset, 0, 31);
			rt_d->rt[j] = devm_regmap_field_alloc(dev, rm, reg);
			अगर (IS_ERR(rt_d->rt[j]))
				वापस -EINVAL;
			reg_offset += 4;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक st_pctl_dt_setup_reसमय(काष्ठा st_pinctrl *info,
	पूर्णांक bank, काष्ठा st_pio_control *pc)
अणु
	स्थिर काष्ठा st_pctl_data *data = info->data;
	अगर (data->rt_style  == st_reसमय_style_packed)
		वापस st_pctl_dt_setup_reसमय_packed(info, bank, pc);
	अन्यथा अगर (data->rt_style == st_reसमय_style_dedicated)
		वापस st_pctl_dt_setup_reसमय_dedicated(info, bank, pc);

	वापस -EINVAL;
पूर्ण


अटल काष्ठा regmap_field *st_pc_get_value(काष्ठा device *dev,
					    काष्ठा regmap *regmap, पूर्णांक bank,
					    पूर्णांक data, पूर्णांक lsb, पूर्णांक msb)
अणु
	काष्ठा reg_field reg = REG_FIELD((data + bank) * 4, lsb, msb);

	अगर (data < 0)
		वापस शून्य;

	वापस devm_regmap_field_alloc(dev, regmap, reg);
पूर्ण

अटल व्योम st_parse_syscfgs(काष्ठा st_pinctrl *info, पूर्णांक bank,
			     काष्ठा device_node *np)
अणु
	स्थिर काष्ठा st_pctl_data *data = info->data;
	/**
	 * For a given shared रेजिस्टर like OE/PU/OD, there are 8 bits per bank
	 * 0:7 beदीर्घs to bank0, 8:15 beदीर्घs to bank1 ...
	 * So each रेजिस्टर is shared across 4 banks.
	 */
	पूर्णांक lsb = (bank%4) * ST_GPIO_PINS_PER_BANK;
	पूर्णांक msb = lsb + ST_GPIO_PINS_PER_BANK - 1;
	काष्ठा st_pio_control *pc = &info->banks[bank].pc;
	काष्ठा device *dev = info->dev;
	काष्ठा regmap *regmap  = info->regmap;

	pc->alt = st_pc_get_value(dev, regmap, bank, data->alt, 0, 31);
	pc->oe = st_pc_get_value(dev, regmap, bank/4, data->oe, lsb, msb);
	pc->pu = st_pc_get_value(dev, regmap, bank/4, data->pu, lsb, msb);
	pc->od = st_pc_get_value(dev, regmap, bank/4, data->od, lsb, msb);

	/* reसमय avaiable क्रम all pins by शेष */
	pc->rt_pin_mask = 0xff;
	of_property_पढ़ो_u32(np, "st,retime-pin-mask", &pc->rt_pin_mask);
	st_pctl_dt_setup_reसमय(info, bank, pc);

	वापस;
पूर्ण

/*
 * Each pin is represented in of the below क्रमms.
 * <bank offset mux direction rt_type rt_delay rt_clk>
 */
अटल पूर्णांक st_pctl_dt_parse_groups(काष्ठा device_node *np,
	काष्ठा st_pctl_group *grp, काष्ठा st_pinctrl *info, पूर्णांक idx)
अणु
	/* bank pad direction val altfunction */
	स्थिर __be32 *list;
	काष्ठा property *pp;
	काष्ठा st_pinconf *conf;
	काष्ठा device_node *pins;
	पूर्णांक i = 0, npins = 0, nr_props, ret = 0;

	pins = of_get_child_by_name(np, "st,pins");
	अगर (!pins)
		वापस -ENODATA;

	क्रम_each_property_of_node(pins, pp) अणु
		/* Skip those we करो not want to proceed */
		अगर (!म_भेद(pp->name, "name"))
			जारी;

		अगर (pp->length / माप(__be32) >= OF_GPIO_ARGS_MIN) अणु
			npins++;
		पूर्ण अन्यथा अणु
			pr_warn("Invalid st,pins in %pOFn node\n", np);
			ret = -EINVAL;
			जाओ out_put_node;
		पूर्ण
	पूर्ण

	grp->npins = npins;
	grp->name = np->name;
	grp->pins = devm_kसुस्मृति(info->dev, npins, माप(u32), GFP_KERNEL);
	grp->pin_conf = devm_kसुस्मृति(info->dev,
					npins, माप(*conf), GFP_KERNEL);

	अगर (!grp->pins || !grp->pin_conf) अणु
		ret = -ENOMEM;
		जाओ out_put_node;
	पूर्ण

	/* <bank offset mux direction rt_type rt_delay rt_clk> */
	क्रम_each_property_of_node(pins, pp) अणु
		अगर (!म_भेद(pp->name, "name"))
			जारी;
		nr_props = pp->length/माप(u32);
		list = pp->value;
		conf = &grp->pin_conf[i];

		/* bank & offset */
		be32_to_cpup(list++);
		be32_to_cpup(list++);
		conf->pin = of_get_named_gpio(pins, pp->name, 0);
		conf->name = pp->name;
		grp->pins[i] = conf->pin;
		/* mux */
		conf->altfunc = be32_to_cpup(list++);
		conf->config = 0;
		/* direction */
		conf->config |= be32_to_cpup(list++);
		/* rt_type rt_delay rt_clk */
		अगर (nr_props >= OF_GPIO_ARGS_MIN + OF_RT_ARGS_MIN) अणु
			/* rt_type */
			conf->config |= be32_to_cpup(list++);
			/* rt_delay */
			conf->config |= be32_to_cpup(list++);
			/* rt_clk */
			अगर (nr_props > OF_GPIO_ARGS_MIN + OF_RT_ARGS_MIN)
				conf->config |= be32_to_cpup(list++);
		पूर्ण
		i++;
	पूर्ण

out_put_node:
	of_node_put(pins);

	वापस ret;
पूर्ण

अटल पूर्णांक st_pctl_parse_functions(काष्ठा device_node *np,
			काष्ठा st_pinctrl *info, u32 index, पूर्णांक *grp_index)
अणु
	काष्ठा device_node *child;
	काष्ठा st_pmx_func *func;
	काष्ठा st_pctl_group *grp;
	पूर्णांक ret, i;

	func = &info->functions[index];
	func->name = np->name;
	func->ngroups = of_get_child_count(np);
	अगर (func->ngroups == 0) अणु
		dev_err(info->dev, "No groups defined\n");
		वापस -EINVAL;
	पूर्ण
	func->groups = devm_kसुस्मृति(info->dev,
			func->ngroups, माप(अक्षर *), GFP_KERNEL);
	अगर (!func->groups)
		वापस -ENOMEM;

	i = 0;
	क्रम_each_child_of_node(np, child) अणु
		func->groups[i] = child->name;
		grp = &info->groups[*grp_index];
		*grp_index += 1;
		ret = st_pctl_dt_parse_groups(child, grp, info, i++);
		अगर (ret) अणु
			of_node_put(child);
			वापस ret;
		पूर्ण
	पूर्ण
	dev_info(info->dev, "Function[%d\t name:%s,\tgroups:%d]\n",
				index, func->name, func->ngroups);

	वापस 0;
पूर्ण

अटल व्योम st_gpio_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा st_gpio_bank *bank = gpiochip_get_data(gc);

	ग_लिखोl(BIT(d->hwirq), bank->base + REG_PIO_CLR_PMASK);
पूर्ण

अटल व्योम st_gpio_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा st_gpio_bank *bank = gpiochip_get_data(gc);

	ग_लिखोl(BIT(d->hwirq), bank->base + REG_PIO_SET_PMASK);
पूर्ण

अटल पूर्णांक st_gpio_irq_request_resources(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);

	st_gpio_direction_input(gc, d->hwirq);

	वापस gpiochip_lock_as_irq(gc, d->hwirq);
पूर्ण

अटल व्योम st_gpio_irq_release_resources(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);

	gpiochip_unlock_as_irq(gc, d->hwirq);
पूर्ण

अटल पूर्णांक st_gpio_irq_set_type(काष्ठा irq_data *d, अचिन्हित type)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा st_gpio_bank *bank = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;
	पूर्णांक comp, pin = d->hwirq;
	u32 val;
	u32 pin_edge_conf = 0;

	चयन (type) अणु
	हाल IRQ_TYPE_LEVEL_HIGH:
		comp = 0;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		comp = 0;
		pin_edge_conf = ST_IRQ_FALLING_EDGE_CONF(pin);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		comp = 1;
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		comp = 1;
		pin_edge_conf = ST_IRQ_RISING_EDGE_CONF(pin);
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		comp = st_gpio_get(&bank->gpio_chip, pin);
		pin_edge_conf = ST_IRQ_BOTH_EDGE_CONF(pin);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&bank->lock, flags);
	bank->irq_edge_conf &=  ~(ST_IRQ_EDGE_MASK << (
				pin * ST_IRQ_EDGE_CONF_BITS_PER_PIN));
	bank->irq_edge_conf |= pin_edge_conf;
	spin_unlock_irqrestore(&bank->lock, flags);

	val = पढ़ोl(bank->base + REG_PIO_PCOMP);
	val &= ~BIT(pin);
	val |= (comp << pin);
	ग_लिखोl(val, bank->base + REG_PIO_PCOMP);

	वापस 0;
पूर्ण

/*
 * As edge triggers are not supported at hardware level, it is supported by
 * software by exploiting the level trigger support in hardware.
 *
 * Steps क्रम detection raising edge पूर्णांकerrupt in software.
 *
 * Step 1: CONFIGURE pin to detect level LOW पूर्णांकerrupts.
 *
 * Step 2: DETECT level LOW पूर्णांकerrupt and in irqmux/gpio bank पूर्णांकerrupt handler,
 * अगर the value of pin is low, then CONFIGURE pin क्रम level HIGH पूर्णांकerrupt.
 * IGNORE calling the actual पूर्णांकerrupt handler क्रम the pin at this stage.
 *
 * Step 3: DETECT level HIGH पूर्णांकerrupt and in irqmux/gpio-bank पूर्णांकerrupt handler
 * अगर the value of pin is HIGH, CONFIGURE pin क्रम level LOW पूर्णांकerrupt and then
 * DISPATCH the पूर्णांकerrupt to the पूर्णांकerrupt handler of the pin.
 *
 *		 step-1  ________     __________
 *				|     | step - 3
 *			        |     |
 *			step -2 |_____|
 *
 * falling edge is also detected पूर्णांक the same way.
 *
 */
अटल व्योम __gpio_irq_handler(काष्ठा st_gpio_bank *bank)
अणु
	अचिन्हित दीर्घ port_in, port_mask, port_comp, active_irqs;
	अचिन्हित दीर्घ bank_edge_mask, flags;
	पूर्णांक n, val, ecfg;

	spin_lock_irqsave(&bank->lock, flags);
	bank_edge_mask = bank->irq_edge_conf;
	spin_unlock_irqrestore(&bank->lock, flags);

	क्रम (;;) अणु
		port_in = पढ़ोl(bank->base + REG_PIO_PIN);
		port_comp = पढ़ोl(bank->base + REG_PIO_PCOMP);
		port_mask = पढ़ोl(bank->base + REG_PIO_PMASK);

		active_irqs = (port_in ^ port_comp) & port_mask;

		अगर (active_irqs == 0)
			अवरोध;

		क्रम_each_set_bit(n, &active_irqs, BITS_PER_LONG) अणु
			/* check अगर we are detecting fake edges ... */
			ecfg = ST_IRQ_EDGE_CONF(bank_edge_mask, n);

			अगर (ecfg) अणु
				/* edge detection. */
				val = st_gpio_get(&bank->gpio_chip, n);

				ग_लिखोl(BIT(n),
					val ? bank->base + REG_PIO_SET_PCOMP :
					bank->base + REG_PIO_CLR_PCOMP);

				अगर (ecfg != ST_IRQ_EDGE_BOTH &&
					!((ecfg & ST_IRQ_EDGE_FALLING) ^ val))
					जारी;
			पूर्ण

			generic_handle_irq(irq_find_mapping(bank->gpio_chip.irq.करोमुख्य, n));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम st_gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	/* पूर्णांकerrupt dedicated per bank */
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा gpio_chip *gc = irq_desc_get_handler_data(desc);
	काष्ठा st_gpio_bank *bank = gpiochip_get_data(gc);

	chained_irq_enter(chip, desc);
	__gpio_irq_handler(bank);
	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम st_gpio_irqmux_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा st_pinctrl *info = irq_desc_get_handler_data(desc);
	अचिन्हित दीर्घ status;
	पूर्णांक n;

	chained_irq_enter(chip, desc);

	status = पढ़ोl(info->irqmux_base);

	क्रम_each_set_bit(n, &status, info->nbanks)
		__gpio_irq_handler(&info->banks[n]);

	chained_irq_निकास(chip, desc);
पूर्ण

अटल स्थिर काष्ठा gpio_chip st_gpio_ढाँचा = अणु
	.request		= gpiochip_generic_request,
	.मुक्त			= gpiochip_generic_मुक्त,
	.get			= st_gpio_get,
	.set			= st_gpio_set,
	.direction_input	= st_gpio_direction_input,
	.direction_output	= st_gpio_direction_output,
	.get_direction		= st_gpio_get_direction,
	.ngpio			= ST_GPIO_PINS_PER_BANK,
पूर्ण;

अटल काष्ठा irq_chip st_gpio_irqchip = अणु
	.name			= "GPIO",
	.irq_request_resources	= st_gpio_irq_request_resources,
	.irq_release_resources	= st_gpio_irq_release_resources,
	.irq_disable		= st_gpio_irq_mask,
	.irq_mask		= st_gpio_irq_mask,
	.irq_unmask		= st_gpio_irq_unmask,
	.irq_set_type		= st_gpio_irq_set_type,
	.flags			= IRQCHIP_SKIP_SET_WAKE,
पूर्ण;

अटल पूर्णांक st_gpiolib_रेजिस्टर_bank(काष्ठा st_pinctrl *info,
	पूर्णांक bank_nr, काष्ठा device_node *np)
अणु
	काष्ठा st_gpio_bank *bank = &info->banks[bank_nr];
	काष्ठा pinctrl_gpio_range *range = &bank->range;
	काष्ठा device *dev = info->dev;
	पूर्णांक bank_num = of_alias_get_id(np, "gpio");
	काष्ठा resource res, irq_res;
	पूर्णांक err;

	अगर (of_address_to_resource(np, 0, &res))
		वापस -ENODEV;

	bank->base = devm_ioremap_resource(dev, &res);
	अगर (IS_ERR(bank->base))
		वापस PTR_ERR(bank->base);

	bank->gpio_chip = st_gpio_ढाँचा;
	bank->gpio_chip.base = bank_num * ST_GPIO_PINS_PER_BANK;
	bank->gpio_chip.ngpio = ST_GPIO_PINS_PER_BANK;
	bank->gpio_chip.of_node = np;
	bank->gpio_chip.parent = dev;
	spin_lock_init(&bank->lock);

	of_property_पढ़ो_string(np, "st,bank-name", &range->name);
	bank->gpio_chip.label = range->name;

	range->id = bank_num;
	range->pin_base = range->base = range->id * ST_GPIO_PINS_PER_BANK;
	range->npins = bank->gpio_chip.ngpio;
	range->gc = &bank->gpio_chip;

	/**
	 * GPIO bank can have one of the two possible types of
	 * पूर्णांकerrupt-wirings.
	 *
	 * First type is via irqmux, single पूर्णांकerrupt is used by multiple
	 * gpio banks. This reduces number of overall पूर्णांकerrupts numbers
	 * required. All these banks beदीर्घ to a single pincontroller.
	 *		  _________
	 *		 |	   |----> [gpio-bank (n)    ]
	 *		 |	   |----> [gpio-bank (n + 1)]
	 *	[irqN]-- | irq-mux |----> [gpio-bank (n + 2)]
	 *		 |	   |----> [gpio-bank (...  )]
	 *		 |_________|----> [gpio-bank (n + 7)]
	 *
	 * Second type has a dedicated पूर्णांकerrupt per each gpio bank.
	 *
	 *	[irqN]----> [gpio-bank (n)]
	 */

	अगर (of_irq_to_resource(np, 0, &irq_res) > 0) अणु
		काष्ठा gpio_irq_chip *girq;
		पूर्णांक gpio_irq = irq_res.start;

		/* This is not a valid IRQ */
		अगर (gpio_irq <= 0) अणु
			dev_err(dev, "invalid IRQ for %pOF bank\n", np);
			जाओ skip_irq;
		पूर्ण
		/* We need to have a mux as well */
		अगर (!info->irqmux_base) अणु
			dev_err(dev, "no irqmux for %pOF bank\n", np);
			जाओ skip_irq;
		पूर्ण

		girq = &bank->gpio_chip.irq;
		girq->chip = &st_gpio_irqchip;
		girq->parent_handler = st_gpio_irq_handler;
		girq->num_parents = 1;
		girq->parents = devm_kसुस्मृति(dev, 1, माप(*girq->parents),
					     GFP_KERNEL);
		अगर (!girq->parents)
			वापस -ENOMEM;
		girq->parents[0] = gpio_irq;
		girq->शेष_type = IRQ_TYPE_NONE;
		girq->handler = handle_simple_irq;
	पूर्ण

skip_irq:
	err  = gpiochip_add_data(&bank->gpio_chip, bank);
	अगर (err) अणु
		dev_err(dev, "Failed to add gpiochip(%d)!\n", bank_num);
		वापस err;
	पूर्ण
	dev_info(dev, "%s bank added.\n", range->name);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id st_pctl_of_match[] = अणु
	अणु .compatible = "st,stih407-sbc-pinctrl", .data = &stih407_dataपूर्ण,
	अणु .compatible = "st,stih407-front-pinctrl", .data = &stih407_dataपूर्ण,
	अणु .compatible = "st,stih407-rear-pinctrl", .data = &stih407_dataपूर्ण,
	अणु .compatible = "st,stih407-flash-pinctrl", .data = &stih407_flashdataपूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक st_pctl_probe_dt(काष्ठा platक्रमm_device *pdev,
	काष्ठा pinctrl_desc *pctl_desc, काष्ठा st_pinctrl *info)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i = 0, j = 0, k = 0, bank;
	काष्ठा pinctrl_pin_desc *pdesc;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *child;
	पूर्णांक grp_index = 0;
	पूर्णांक irq = 0;
	काष्ठा resource *res;

	st_pctl_dt_child_count(info, np);
	अगर (!info->nbanks) अणु
		dev_err(&pdev->dev, "you need atleast one gpio bank\n");
		वापस -EINVAL;
	पूर्ण

	dev_info(&pdev->dev, "nbanks = %d\n", info->nbanks);
	dev_info(&pdev->dev, "nfunctions = %d\n", info->nfunctions);
	dev_info(&pdev->dev, "ngroups = %d\n", info->ngroups);

	info->functions = devm_kसुस्मृति(&pdev->dev,
		info->nfunctions, माप(*info->functions), GFP_KERNEL);

	info->groups = devm_kसुस्मृति(&pdev->dev,
			info->ngroups, माप(*info->groups),
			GFP_KERNEL);

	info->banks = devm_kसुस्मृति(&pdev->dev,
			info->nbanks, माप(*info->banks), GFP_KERNEL);

	अगर (!info->functions || !info->groups || !info->banks)
		वापस -ENOMEM;

	info->regmap = syscon_regmap_lookup_by_phandle(np, "st,syscfg");
	अगर (IS_ERR(info->regmap)) अणु
		dev_err(info->dev, "No syscfg phandle specified\n");
		वापस PTR_ERR(info->regmap);
	पूर्ण
	info->data = of_match_node(st_pctl_of_match, np)->data;

	irq = platक्रमm_get_irq(pdev, 0);

	अगर (irq > 0) अणु
		res = platक्रमm_get_resource_byname(pdev,
					IORESOURCE_MEM, "irqmux");
		info->irqmux_base = devm_ioremap_resource(&pdev->dev, res);

		अगर (IS_ERR(info->irqmux_base))
			वापस PTR_ERR(info->irqmux_base);

		irq_set_chained_handler_and_data(irq, st_gpio_irqmux_handler,
						 info);

	पूर्ण

	pctl_desc->npins = info->nbanks * ST_GPIO_PINS_PER_BANK;
	pdesc =	devm_kसुस्मृति(&pdev->dev,
			pctl_desc->npins, माप(*pdesc), GFP_KERNEL);
	अगर (!pdesc)
		वापस -ENOMEM;

	pctl_desc->pins = pdesc;

	bank = 0;
	क्रम_each_child_of_node(np, child) अणु
		अगर (of_property_पढ़ो_bool(child, "gpio-controller")) अणु
			स्थिर अक्षर *bank_name = शून्य;
			ret = st_gpiolib_रेजिस्टर_bank(info, bank, child);
			अगर (ret) अणु
				of_node_put(child);
				वापस ret;
			पूर्ण

			k = info->banks[bank].range.pin_base;
			bank_name = info->banks[bank].range.name;
			क्रम (j = 0; j < ST_GPIO_PINS_PER_BANK; j++, k++) अणु
				pdesc->number = k;
				pdesc->name = kaप्र_लिखो(GFP_KERNEL, "%s[%d]",
							bank_name, j);
				pdesc++;
			पूर्ण
			st_parse_syscfgs(info, bank, child);
			bank++;
		पूर्ण अन्यथा अणु
			ret = st_pctl_parse_functions(child, info,
							i++, &grp_index);
			अगर (ret) अणु
				dev_err(&pdev->dev, "No functions found.\n");
				of_node_put(child);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक st_pctl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा st_pinctrl *info;
	काष्ठा pinctrl_desc *pctl_desc;
	पूर्णांक ret, i;

	अगर (!pdev->dev.of_node) अणु
		dev_err(&pdev->dev, "device node not found.\n");
		वापस -EINVAL;
	पूर्ण

	pctl_desc = devm_kzalloc(&pdev->dev, माप(*pctl_desc), GFP_KERNEL);
	अगर (!pctl_desc)
		वापस -ENOMEM;

	info = devm_kzalloc(&pdev->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, info);
	ret = st_pctl_probe_dt(pdev, pctl_desc, info);
	अगर (ret)
		वापस ret;

	pctl_desc->owner	= THIS_MODULE;
	pctl_desc->pctlops	= &st_pctlops;
	pctl_desc->pmxops	= &st_pmxops;
	pctl_desc->confops	= &st_confops;
	pctl_desc->name		= dev_name(&pdev->dev);

	info->pctl = devm_pinctrl_रेजिस्टर(&pdev->dev, pctl_desc, info);
	अगर (IS_ERR(info->pctl)) अणु
		dev_err(&pdev->dev, "Failed pinctrl registration\n");
		वापस PTR_ERR(info->pctl);
	पूर्ण

	क्रम (i = 0; i < info->nbanks; i++)
		pinctrl_add_gpio_range(info->pctl, &info->banks[i].range);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver st_pctl_driver = अणु
	.driver = अणु
		.name = "st-pinctrl",
		.of_match_table = st_pctl_of_match,
	पूर्ण,
	.probe = st_pctl_probe,
पूर्ण;

अटल पूर्णांक __init st_pctl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&st_pctl_driver);
पूर्ण
arch_initcall(st_pctl_init);
