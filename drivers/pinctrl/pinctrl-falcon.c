<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/pinctrl/pinmux-falcon.c
 *  based on linux/drivers/pinctrl/pinmux-pxa910.c
 *
 *  Copyright (C) 2012 Thomas Langer <thomas.langer@lantiq.com>
 *  Copyright (C) 2012 John Crispin <john@phrozen.org>
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/platक्रमm_device.h>

#समावेश "pinctrl-lantiq.h"

#समावेश <lantiq_soc.h>

/* Multiplexer Control Register */
#घोषणा LTQ_PADC_MUX(x)         (x * 0x4)
/* Pull Up Enable Register */
#घोषणा LTQ_PADC_PUEN		0x80
/* Pull Down Enable Register */
#घोषणा LTQ_PADC_PDEN		0x84
/* Slew Rate Control Register */
#घोषणा LTQ_PADC_SRC		0x88
/* Drive Current Control Register */
#घोषणा LTQ_PADC_DCC		0x8C
/* Pad Control Availability Register */
#घोषणा LTQ_PADC_AVAIL          0xF0

#घोषणा pad_r32(p, reg)		ltq_r32(p + reg)
#घोषणा pad_w32(p, val, reg)	ltq_w32(val, p + reg)
#घोषणा pad_w32_mask(c, clear, set, reg) \
		pad_w32(c, (pad_r32(c, reg) & ~(clear)) | (set), reg)

#घोषणा pad_getbit(m, r, p)	(!!(ltq_r32(m + r) & (1 << p)))

#घोषणा PORTS			5
#घोषणा PINS			32
#घोषणा PORT(x)                 (x / PINS)
#घोषणा PORT_PIN(x)             (x % PINS)

#घोषणा MFP_FALCON(a, f0, f1, f2, f3)		\
अणु						\
	.name = #a,				\
	.pin = a,				\
	.func = अणु				\
		FALCON_MUX_##f0,		\
		FALCON_MUX_##f1,		\
		FALCON_MUX_##f2,		\
		FALCON_MUX_##f3,		\
	पूर्ण,					\
पूर्ण

#घोषणा GRP_MUX(a, m, p)	\
अणु				\
	.name = a,		\
	.mux = FALCON_MUX_##m,	\
	.pins = p,		\
	.npins = ARRAY_SIZE(p),	\
पूर्ण

क्रमागत falcon_mux अणु
	FALCON_MUX_GPIO = 0,
	FALCON_MUX_RST,
	FALCON_MUX_NTR,
	FALCON_MUX_PPS,
	FALCON_MUX_MDIO,
	FALCON_MUX_LED,
	FALCON_MUX_SPI,
	FALCON_MUX_ASC,
	FALCON_MUX_I2C,
	FALCON_MUX_HOSTIF,
	FALCON_MUX_SLIC,
	FALCON_MUX_JTAG,
	FALCON_MUX_PCM,
	FALCON_MUX_MII,
	FALCON_MUX_PHY,
	FALCON_MUX_NONE = 0xffff,
पूर्ण;

अटल काष्ठा pinctrl_pin_desc falcon_pads[PORTS * PINS];
अटल पूर्णांक pad_count[PORTS];

अटल व्योम lantiq_load_pin_desc(काष्ठा pinctrl_pin_desc *d, पूर्णांक bank, पूर्णांक len)
अणु
	पूर्णांक base = bank * PINS;
	पूर्णांक i;

	क्रम (i = 0; i < len; i++) अणु
		d[i].number = base + i;
		d[i].name = kaप्र_लिखो(GFP_KERNEL, "io%d", base + i);
	पूर्ण
	pad_count[bank] = len;
पूर्ण

अटल काष्ठा ltq_mfp_pin falcon_mfp[] = अणु
	/*	pin		f0	f1	f2	f3 */
	MFP_FALCON(GPIO0,	RST,	GPIO,   NONE,   NONE),
	MFP_FALCON(GPIO1,	GPIO,	GPIO,   NONE,   NONE),
	MFP_FALCON(GPIO2,	GPIO,	GPIO,   NONE,   NONE),
	MFP_FALCON(GPIO3,	GPIO,	GPIO,   NONE,   NONE),
	MFP_FALCON(GPIO4,	NTR,	GPIO,   NONE,   NONE),
	MFP_FALCON(GPIO5,	NTR,	GPIO,   PPS,    NONE),
	MFP_FALCON(GPIO6,	RST,	GPIO,   NONE,   NONE),
	MFP_FALCON(GPIO7,	MDIO,	GPIO,   NONE,   NONE),
	MFP_FALCON(GPIO8,	MDIO,	GPIO,   NONE,   NONE),
	MFP_FALCON(GPIO9,	LED,	GPIO,   NONE,   NONE),
	MFP_FALCON(GPIO10,	LED,	GPIO,   NONE,   NONE),
	MFP_FALCON(GPIO11,	LED,	GPIO,   NONE,   NONE),
	MFP_FALCON(GPIO12,	LED,	GPIO,   NONE,   NONE),
	MFP_FALCON(GPIO13,	LED,	GPIO,   NONE,   NONE),
	MFP_FALCON(GPIO14,	LED,	GPIO,   NONE,   NONE),
	MFP_FALCON(GPIO32,	ASC,	GPIO,   NONE,   NONE),
	MFP_FALCON(GPIO33,	ASC,	GPIO,   NONE,   NONE),
	MFP_FALCON(GPIO34,	SPI,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO35,	SPI,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO36,	SPI,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO37,	SPI,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO38,	SPI,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO39,	I2C,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO40,	I2C,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO41,	HOSTIF,	GPIO,	HOSTIF,	JTAG),
	MFP_FALCON(GPIO42,	HOSTIF,	GPIO,	HOSTIF,	NONE),
	MFP_FALCON(GPIO43,	SLIC,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO44,	SLIC,	GPIO,	PCM,	ASC),
	MFP_FALCON(GPIO45,	SLIC,	GPIO,	PCM,	ASC),
	MFP_FALCON(GPIO64,	MII,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO65,	MII,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO66,	MII,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO67,	MII,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO68,	MII,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO69,	MII,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO70,	MII,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO71,	MII,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO72,	MII,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO73,	MII,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO74,	MII,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO75,	MII,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO76,	MII,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO77,	MII,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO78,	MII,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO79,	MII,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO80,	MII,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO81,	MII,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO82,	MII,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO83,	MII,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO84,	MII,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO85,	MII,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO86,	MII,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO87,	MII,	GPIO,	NONE,	NONE),
	MFP_FALCON(GPIO88,	PHY,	GPIO,	NONE,	NONE),
पूर्ण;

अटल स्थिर अचिन्हित pins_por[] = अणुGPIO0पूर्ण;
अटल स्थिर अचिन्हित pins_ntr[] = अणुGPIO4पूर्ण;
अटल स्थिर अचिन्हित pins_ntr8k[] = अणुGPIO5पूर्ण;
अटल स्थिर अचिन्हित pins_pps[] = अणुGPIO5पूर्ण;
अटल स्थिर अचिन्हित pins_hrst[] = अणुGPIO6पूर्ण;
अटल स्थिर अचिन्हित pins_mdio[] = अणुGPIO7, GPIO8पूर्ण;
अटल स्थिर अचिन्हित pins_bled[] = अणुGPIO9, GPIO10, GPIO11,
					GPIO12, GPIO13, GPIO14पूर्ण;
अटल स्थिर अचिन्हित pins_asc0[] = अणुGPIO32, GPIO33पूर्ण;
अटल स्थिर अचिन्हित pins_spi[] = अणुGPIO34, GPIO35, GPIO36पूर्ण;
अटल स्थिर अचिन्हित pins_spi_cs0[] = अणुGPIO37पूर्ण;
अटल स्थिर अचिन्हित pins_spi_cs1[] = अणुGPIO38पूर्ण;
अटल स्थिर अचिन्हित pins_i2c[] = अणुGPIO39, GPIO40पूर्ण;
अटल स्थिर अचिन्हित pins_jtag[] = अणुGPIO41पूर्ण;
अटल स्थिर अचिन्हित pins_slic[] = अणुGPIO43, GPIO44, GPIO45पूर्ण;
अटल स्थिर अचिन्हित pins_pcm[] = अणुGPIO44, GPIO45पूर्ण;
अटल स्थिर अचिन्हित pins_asc1[] = अणुGPIO44, GPIO45पूर्ण;

अटल काष्ठा ltq_pin_group falcon_grps[] = अणु
	GRP_MUX("por", RST, pins_por),
	GRP_MUX("ntr", NTR, pins_ntr),
	GRP_MUX("ntr8k", NTR, pins_ntr8k),
	GRP_MUX("pps", PPS, pins_pps),
	GRP_MUX("hrst", RST, pins_hrst),
	GRP_MUX("mdio", MDIO, pins_mdio),
	GRP_MUX("bootled", LED, pins_bled),
	GRP_MUX("asc0", ASC, pins_asc0),
	GRP_MUX("spi", SPI, pins_spi),
	GRP_MUX("spi cs0", SPI, pins_spi_cs0),
	GRP_MUX("spi cs1", SPI, pins_spi_cs1),
	GRP_MUX("i2c", I2C, pins_i2c),
	GRP_MUX("jtag", JTAG, pins_jtag),
	GRP_MUX("slic", SLIC, pins_slic),
	GRP_MUX("pcm", PCM, pins_pcm),
	GRP_MUX("asc1", ASC, pins_asc1),
पूर्ण;

अटल स्थिर अक्षर * स्थिर ltq_rst_grps[] = अणु"por", "hrst"पूर्ण;
अटल स्थिर अक्षर * स्थिर ltq_ntr_grps[] = अणु"ntr", "ntr8k", "pps"पूर्ण;
अटल स्थिर अक्षर * स्थिर ltq_mdio_grps[] = अणु"mdio"पूर्ण;
अटल स्थिर अक्षर * स्थिर ltq_bled_grps[] = अणु"bootled"पूर्ण;
अटल स्थिर अक्षर * स्थिर ltq_asc_grps[] = अणु"asc0", "asc1"पूर्ण;
अटल स्थिर अक्षर * स्थिर ltq_spi_grps[] = अणु"spi", "spi cs0", "spi cs1"पूर्ण;
अटल स्थिर अक्षर * स्थिर ltq_i2c_grps[] = अणु"i2c"पूर्ण;
अटल स्थिर अक्षर * स्थिर ltq_jtag_grps[] = अणु"jtag"पूर्ण;
अटल स्थिर अक्षर * स्थिर ltq_slic_grps[] = अणु"slic"पूर्ण;
अटल स्थिर अक्षर * स्थिर ltq_pcm_grps[] = अणु"pcm"पूर्ण;

अटल काष्ठा ltq_pmx_func falcon_funcs[] = अणु
	अणु"rst",		ARRAY_AND_SIZE(ltq_rst_grps)पूर्ण,
	अणु"ntr",		ARRAY_AND_SIZE(ltq_ntr_grps)पूर्ण,
	अणु"mdio",	ARRAY_AND_SIZE(ltq_mdio_grps)पूर्ण,
	अणु"led",		ARRAY_AND_SIZE(ltq_bled_grps)पूर्ण,
	अणु"asc",		ARRAY_AND_SIZE(ltq_asc_grps)पूर्ण,
	अणु"spi",		ARRAY_AND_SIZE(ltq_spi_grps)पूर्ण,
	अणु"i2c",		ARRAY_AND_SIZE(ltq_i2c_grps)पूर्ण,
	अणु"jtag",	ARRAY_AND_SIZE(ltq_jtag_grps)पूर्ण,
	अणु"slic",	ARRAY_AND_SIZE(ltq_slic_grps)पूर्ण,
	अणु"pcm",		ARRAY_AND_SIZE(ltq_pcm_grps)पूर्ण,
पूर्ण;




/* ---------  pinconf related code --------- */
अटल पूर्णांक falcon_pinconf_group_get(काष्ठा pinctrl_dev *pctrldev,
				अचिन्हित group, अचिन्हित दीर्घ *config)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक falcon_pinconf_group_set(काष्ठा pinctrl_dev *pctrldev,
				अचिन्हित group, अचिन्हित दीर्घ *configs,
				अचिन्हित num_configs)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक falcon_pinconf_get(काष्ठा pinctrl_dev *pctrldev,
				अचिन्हित pin, अचिन्हित दीर्घ *config)
अणु
	काष्ठा ltq_pinmux_info *info = pinctrl_dev_get_drvdata(pctrldev);
	क्रमागत ltq_pinconf_param param = LTQ_PINCONF_UNPACK_PARAM(*config);
	व्योम __iomem *mem = info->membase[PORT(pin)];

	चयन (param) अणु
	हाल LTQ_PINCONF_PARAM_DRIVE_CURRENT:
		*config = LTQ_PINCONF_PACK(param,
			!!pad_getbit(mem, LTQ_PADC_DCC, PORT_PIN(pin)));
		अवरोध;

	हाल LTQ_PINCONF_PARAM_SLEW_RATE:
		*config = LTQ_PINCONF_PACK(param,
			!!pad_getbit(mem, LTQ_PADC_SRC, PORT_PIN(pin)));
		अवरोध;

	हाल LTQ_PINCONF_PARAM_PULL:
		अगर (pad_getbit(mem, LTQ_PADC_PDEN, PORT_PIN(pin)))
			*config = LTQ_PINCONF_PACK(param, 1);
		अन्यथा अगर (pad_getbit(mem, LTQ_PADC_PUEN, PORT_PIN(pin)))
			*config = LTQ_PINCONF_PACK(param, 2);
		अन्यथा
			*config = LTQ_PINCONF_PACK(param, 0);

		अवरोध;

	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक falcon_pinconf_set(काष्ठा pinctrl_dev *pctrldev,
			अचिन्हित pin, अचिन्हित दीर्घ *configs,
			अचिन्हित num_configs)
अणु
	क्रमागत ltq_pinconf_param param;
	पूर्णांक arg;
	काष्ठा ltq_pinmux_info *info = pinctrl_dev_get_drvdata(pctrldev);
	व्योम __iomem *mem = info->membase[PORT(pin)];
	u32 reg;
	पूर्णांक i;

	क्रम (i = 0; i < num_configs; i++) अणु
		param = LTQ_PINCONF_UNPACK_PARAM(configs[i]);
		arg = LTQ_PINCONF_UNPACK_ARG(configs[i]);

		चयन (param) अणु
		हाल LTQ_PINCONF_PARAM_DRIVE_CURRENT:
			reg = LTQ_PADC_DCC;
			अवरोध;

		हाल LTQ_PINCONF_PARAM_SLEW_RATE:
			reg = LTQ_PADC_SRC;
			अवरोध;

		हाल LTQ_PINCONF_PARAM_PULL:
			अगर (arg == 1)
				reg = LTQ_PADC_PDEN;
			अन्यथा
				reg = LTQ_PADC_PUEN;
			अवरोध;

		शेष:
			pr_err("%s: Invalid config param %04x\n",
			pinctrl_dev_get_name(pctrldev), param);
			वापस -ENOTSUPP;
		पूर्ण

		pad_w32(mem, BIT(PORT_PIN(pin)), reg);
		अगर (!(pad_r32(mem, reg) & BIT(PORT_PIN(pin))))
			वापस -ENOTSUPP;
	पूर्ण /* क्रम each config */

	वापस 0;
पूर्ण

अटल व्योम falcon_pinconf_dbg_show(काष्ठा pinctrl_dev *pctrldev,
			काष्ठा seq_file *s, अचिन्हित offset)
अणु
	अचिन्हित दीर्घ config;
	काष्ठा pin_desc *desc;

	काष्ठा ltq_pinmux_info *info = pinctrl_dev_get_drvdata(pctrldev);
	पूर्णांक port = PORT(offset);

	seq_म_लिखो(s, " (port %d) mux %d -- ", port,
		pad_r32(info->membase[port], LTQ_PADC_MUX(PORT_PIN(offset))));

	config = LTQ_PINCONF_PACK(LTQ_PINCONF_PARAM_PULL, 0);
	अगर (!falcon_pinconf_get(pctrldev, offset, &config))
		seq_म_लिखो(s, "pull %d ",
			(पूर्णांक)LTQ_PINCONF_UNPACK_ARG(config));

	config = LTQ_PINCONF_PACK(LTQ_PINCONF_PARAM_DRIVE_CURRENT, 0);
	अगर (!falcon_pinconf_get(pctrldev, offset, &config))
		seq_म_लिखो(s, "drive-current %d ",
			(पूर्णांक)LTQ_PINCONF_UNPACK_ARG(config));

	config = LTQ_PINCONF_PACK(LTQ_PINCONF_PARAM_SLEW_RATE, 0);
	अगर (!falcon_pinconf_get(pctrldev, offset, &config))
		seq_म_लिखो(s, "slew-rate %d ",
			(पूर्णांक)LTQ_PINCONF_UNPACK_ARG(config));

	desc = pin_desc_get(pctrldev, offset);
	अगर (desc) अणु
		अगर (desc->gpio_owner)
			seq_म_लिखो(s, " owner: %s", desc->gpio_owner);
	पूर्ण अन्यथा अणु
		seq_म_लिखो(s, " not registered");
	पूर्ण
पूर्ण

अटल व्योम falcon_pinconf_group_dbg_show(काष्ठा pinctrl_dev *pctrldev,
			काष्ठा seq_file *s, अचिन्हित selector)
अणु
पूर्ण

अटल स्थिर काष्ठा pinconf_ops falcon_pinconf_ops = अणु
	.pin_config_get			= falcon_pinconf_get,
	.pin_config_set			= falcon_pinconf_set,
	.pin_config_group_get		= falcon_pinconf_group_get,
	.pin_config_group_set		= falcon_pinconf_group_set,
	.pin_config_dbg_show		= falcon_pinconf_dbg_show,
	.pin_config_group_dbg_show	= falcon_pinconf_group_dbg_show,
पूर्ण;

अटल काष्ठा pinctrl_desc falcon_pctrl_desc = अणु
	.owner		= THIS_MODULE,
	.pins		= falcon_pads,
	.confops	= &falcon_pinconf_ops,
पूर्ण;

अटल अंतरभूत पूर्णांक falcon_mux_apply(काष्ठा pinctrl_dev *pctrldev,
			पूर्णांक mfp, पूर्णांक mux)
अणु
	काष्ठा ltq_pinmux_info *info = pinctrl_dev_get_drvdata(pctrldev);
	पूर्णांक port = PORT(info->mfp[mfp].pin);

	अगर ((port >= PORTS) || (!info->membase[port]))
		वापस -ENODEV;

	pad_w32(info->membase[port], mux,
		LTQ_PADC_MUX(PORT_PIN(info->mfp[mfp].pin)));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ltq_cfg_param falcon_cfg_params[] = अणु
	अणु"lantiq,pull",			LTQ_PINCONF_PARAM_PULLपूर्ण,
	अणु"lantiq,drive-current",	LTQ_PINCONF_PARAM_DRIVE_CURRENTपूर्ण,
	अणु"lantiq,slew-rate",		LTQ_PINCONF_PARAM_SLEW_RATEपूर्ण,
पूर्ण;

अटल काष्ठा ltq_pinmux_info falcon_info = अणु
	.desc		= &falcon_pctrl_desc,
	.apply_mux	= falcon_mux_apply,
	.params		= falcon_cfg_params,
	.num_params	= ARRAY_SIZE(falcon_cfg_params),
पूर्ण;




/* --------- रेजिस्टर the pinctrl layer --------- */

पूर्णांक pinctrl_falcon_get_range_size(पूर्णांक id)
अणु
	u32 avail;

	अगर ((id >= PORTS) || (!falcon_info.membase[id]))
		वापस -EINVAL;

	avail = pad_r32(falcon_info.membase[id], LTQ_PADC_AVAIL);

	वापस fls(avail);
पूर्ण

व्योम pinctrl_falcon_add_gpio_range(काष्ठा pinctrl_gpio_range *range)
अणु
	pinctrl_add_gpio_range(falcon_info.pctrl, range);
पूर्ण

अटल पूर्णांक pinctrl_falcon_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np;
	पूर्णांक pad_count = 0;
	पूर्णांक ret = 0;

	/* load and remap the pad resources of the dअगरferent banks */
	क्रम_each_compatible_node(np, शून्य, "lantiq,pad-falcon") अणु
		स्थिर __be32 *bank = of_get_property(np, "lantiq,bank", शून्य);
		काष्ठा resource res;
		काष्ठा platक्रमm_device *ppdev;
		u32 avail;
		पूर्णांक pins;

		अगर (!of_device_is_available(np))
			जारी;

		अगर (!bank || *bank >= PORTS)
			जारी;
		अगर (of_address_to_resource(np, 0, &res))
			जारी;

		ppdev = of_find_device_by_node(np);
		अगर (!ppdev) अणु
			dev_err(&pdev->dev, "failed to find pad pdev\n");
			जारी;
		पूर्ण

		falcon_info.clk[*bank] = clk_get(&ppdev->dev, शून्य);
		put_device(&ppdev->dev);
		अगर (IS_ERR(falcon_info.clk[*bank])) अणु
			dev_err(&ppdev->dev, "failed to get clock\n");
			of_node_put(np);
			वापस PTR_ERR(falcon_info.clk[*bank]);
		पूर्ण
		falcon_info.membase[*bank] = devm_ioremap_resource(&pdev->dev,
								   &res);
		अगर (IS_ERR(falcon_info.membase[*bank])) अणु
			of_node_put(np);
			वापस PTR_ERR(falcon_info.membase[*bank]);
		पूर्ण

		avail = pad_r32(falcon_info.membase[*bank],
					LTQ_PADC_AVAIL);
		pins = fls(avail);
		lantiq_load_pin_desc(&falcon_pads[pad_count], *bank, pins);
		pad_count += pins;
		clk_enable(falcon_info.clk[*bank]);
		dev_dbg(&pdev->dev, "found %s with %d pads\n",
				res.name, pins);
	पूर्ण
	dev_dbg(&pdev->dev, "found a total of %d pads\n", pad_count);
	falcon_pctrl_desc.name	= dev_name(&pdev->dev);
	falcon_pctrl_desc.npins	= pad_count;

	falcon_info.mfp		= falcon_mfp;
	falcon_info.num_mfp	= ARRAY_SIZE(falcon_mfp);
	falcon_info.grps	= falcon_grps;
	falcon_info.num_grps	= ARRAY_SIZE(falcon_grps);
	falcon_info.funcs	= falcon_funcs;
	falcon_info.num_funcs	= ARRAY_SIZE(falcon_funcs);

	ret = ltq_pinctrl_रेजिस्टर(pdev, &falcon_info);
	अगर (!ret)
		dev_info(&pdev->dev, "Init done\n");
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id falcon_match[] = अणु
	अणु .compatible = "lantiq,pinctrl-falcon" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, falcon_match);

अटल काष्ठा platक्रमm_driver pinctrl_falcon_driver = अणु
	.probe = pinctrl_falcon_probe,
	.driver = अणु
		.name = "pinctrl-falcon",
		.of_match_table = falcon_match,
	पूर्ण,
पूर्ण;

पूर्णांक __init pinctrl_falcon_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&pinctrl_falcon_driver);
पूर्ण

core_initcall_sync(pinctrl_falcon_init);
