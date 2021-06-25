<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * OWL SoC's Pinctrl definitions
 *
 * Copyright (c) 2014 Actions Semi Inc.
 * Author: David Liu <liuwei@actions-semi.com>
 *
 * Copyright (c) 2018 Linaro Ltd.
 * Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>
 */

#अगर_अघोषित __PINCTRL_OWL_H__
#घोषणा __PINCTRL_OWL_H__

#घोषणा OWL_PINCONF_SLEW_SLOW 0
#घोषणा OWL_PINCONF_SLEW_FAST 1

#घोषणा MUX_PG(group_name, reg, shअगरt, width)				\
	अणु								\
		.name = #group_name,					\
		.pads = group_name##_pads,				\
		.npads = ARRAY_SIZE(group_name##_pads),			\
		.funcs = group_name##_funcs,				\
		.nfuncs = ARRAY_SIZE(group_name##_funcs),		\
		.mfpctl_reg  = MFCTL##reg,				\
		.mfpctl_shअगरt = shअगरt,					\
		.mfpctl_width = width,					\
		.drv_reg = -1,						\
		.drv_shअगरt = -1,					\
		.drv_width = -1,					\
		.sr_reg = -1,						\
		.sr_shअगरt = -1,						\
		.sr_width = -1,						\
	पूर्ण

#घोषणा DRV_PG(group_name, reg, shअगरt, width)				\
	अणु								\
		.name = #group_name,					\
		.pads = group_name##_pads,				\
		.npads = ARRAY_SIZE(group_name##_pads),			\
		.mfpctl_reg  = -1,					\
		.mfpctl_shअगरt = -1,					\
		.mfpctl_width = -1,					\
		.drv_reg = PAD_DRV##reg,				\
		.drv_shअगरt = shअगरt,					\
		.drv_width = width,					\
		.sr_reg = -1,						\
		.sr_shअगरt = -1,						\
		.sr_width = -1,						\
	पूर्ण

#घोषणा SR_PG(group_name, reg, shअगरt, width)				\
	अणु								\
		.name = #group_name,					\
		.pads = group_name##_pads,				\
		.npads = ARRAY_SIZE(group_name##_pads),			\
		.mfpctl_reg  = -1,					\
		.mfpctl_shअगरt = -1,					\
		.mfpctl_width = -1,					\
		.drv_reg = -1,						\
		.drv_shअगरt = -1,					\
		.drv_width = -1,					\
		.sr_reg = PAD_SR##reg,					\
		.sr_shअगरt = shअगरt,					\
		.sr_width = width,					\
	पूर्ण

#घोषणा FUNCTION(fname)					\
	अणु						\
		.name = #fname,				\
		.groups = fname##_groups,		\
		.ngroups = ARRAY_SIZE(fname##_groups),	\
	पूर्ण

/* PAD PULL UP/DOWN CONFIGURES */
#घोषणा PULLCTL_CONF(pull_reg, pull_sft, pull_wdt)	\
	अणु						\
		.reg = PAD_PULLCTL##pull_reg,		\
		.shअगरt = pull_sft,			\
		.width = pull_wdt,			\
	पूर्ण

#घोषणा PAD_PULLCTL_CONF(pad_name, pull_reg, pull_sft, pull_wdt)	\
	काष्ठा owl_pullctl pad_name##_pullctl_conf			\
		= PULLCTL_CONF(pull_reg, pull_sft, pull_wdt)

#घोषणा ST_CONF(st_reg, st_sft, st_wdt)			\
	अणु						\
		.reg = PAD_ST##st_reg,			\
		.shअगरt = st_sft,			\
		.width = st_wdt,			\
	पूर्ण

#घोषणा PAD_ST_CONF(pad_name, st_reg, st_sft, st_wdt)	\
	काष्ठा owl_st pad_name##_st_conf		\
		= ST_CONF(st_reg, st_sft, st_wdt)

#घोषणा PAD_INFO(name)					\
	अणु						\
		.pad = name,				\
		.pullctl = शून्य,			\
		.st = शून्य,				\
	पूर्ण

#घोषणा PAD_INFO_ST(name)				\
	अणु						\
		.pad = name,				\
		.pullctl = शून्य,			\
		.st = &name##_st_conf,			\
	पूर्ण

#घोषणा PAD_INFO_PULLCTL(name)				\
	अणु						\
		.pad = name,				\
		.pullctl = &name##_pullctl_conf,	\
		.st = शून्य,				\
	पूर्ण

#घोषणा PAD_INFO_PULLCTL_ST(name)			\
	अणु						\
		.pad = name,				\
		.pullctl = &name##_pullctl_conf,	\
		.st = &name##_st_conf,			\
	पूर्ण

#घोषणा OWL_GPIO_PORT_A		0
#घोषणा OWL_GPIO_PORT_B		1
#घोषणा OWL_GPIO_PORT_C		2
#घोषणा OWL_GPIO_PORT_D		3
#घोषणा OWL_GPIO_PORT_E		4
#घोषणा OWL_GPIO_PORT_F		5

#घोषणा OWL_GPIO_PORT(port, base, count, _outen, _inen, _dat, _पूर्णांकc_ctl,\
			_पूर्णांकc_pd, _पूर्णांकc_msk, _पूर्णांकc_type, _share)	\
	[OWL_GPIO_PORT_##port] = अणु				\
		.offset = base,					\
		.pins = count,					\
		.outen = _outen,				\
		.inen = _inen,					\
		.dat = _dat,					\
		.पूर्णांकc_ctl = _पूर्णांकc_ctl,				\
		.पूर्णांकc_pd = _पूर्णांकc_pd,				\
		.पूर्णांकc_msk = _पूर्णांकc_msk,				\
		.पूर्णांकc_type = _पूर्णांकc_type,			\
		.shared_ctl_offset = _share,			\
	पूर्ण

क्रमागत owl_pinconf_drv अणु
	OWL_PINCONF_DRV_2MA,
	OWL_PINCONF_DRV_4MA,
	OWL_PINCONF_DRV_8MA,
	OWL_PINCONF_DRV_12MA,
पूर्ण;

/* GPIO CTRL Bit Definition */
#घोषणा OWL_GPIO_CTLR_PENDING		0
#घोषणा OWL_GPIO_CTLR_ENABLE		1
#घोषणा OWL_GPIO_CTLR_SAMPLE_CLK_24M	2

/* GPIO TYPE Bit Definition */
#घोषणा OWL_GPIO_INT_LEVEL_HIGH		0
#घोषणा OWL_GPIO_INT_LEVEL_LOW		1
#घोषणा OWL_GPIO_INT_EDGE_RISING	2
#घोषणा OWL_GPIO_INT_EDGE_FALLING	3
#घोषणा OWL_GPIO_INT_MASK		3

/**
 * काष्ठा owl_pullctl - Actions pad pull control रेजिस्टर
 * @reg: offset to the pull control रेजिस्टर
 * @shअगरt: shअगरt value of the रेजिस्टर
 * @width: width of the रेजिस्टर
 */
काष्ठा owl_pullctl अणु
	पूर्णांक reg;
	अचिन्हित पूर्णांक shअगरt;
	अचिन्हित पूर्णांक width;
पूर्ण;

/**
 * काष्ठा owl_st - Actions pad schmitt trigger enable रेजिस्टर
 * @reg: offset to the schmitt trigger enable रेजिस्टर
 * @shअगरt: shअगरt value of the रेजिस्टर
 * @width: width of the रेजिस्टर
 */
काष्ठा owl_st अणु
	पूर्णांक reg;
	अचिन्हित पूर्णांक shअगरt;
	अचिन्हित पूर्णांक width;
पूर्ण;

/**
 * काष्ठा owl_pingroup - Actions pingroup definition
 * @name: name of the  pin group
 * @pads: list of pins asचिन्हित to this pingroup
 * @npads: size of @pads array
 * @funcs: list of pinmux functions क्रम this pingroup
 * @nfuncs: size of @funcs array
 * @mfpctl_reg: multiplexing control रेजिस्टर offset
 * @mfpctl_shअगरt: multiplexing control रेजिस्टर bit mask
 * @mfpctl_width: multiplexing control रेजिस्टर width
 * @drv_reg: drive control रेजिस्टर offset
 * @drv_shअगरt: drive control रेजिस्टर bit mask
 * @drv_width: driver control रेजिस्टर width
 * @sr_reg: slew rate control रेजिस्टर offset
 * @sr_shअगरt: slew rate control रेजिस्टर bit mask
 * @sr_width: slew rate control रेजिस्टर width
 */
काष्ठा owl_pingroup अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक *pads;
	अचिन्हित पूर्णांक npads;
	अचिन्हित पूर्णांक *funcs;
	अचिन्हित पूर्णांक nfuncs;

	पूर्णांक mfpctl_reg;
	अचिन्हित पूर्णांक mfpctl_shअगरt;
	अचिन्हित पूर्णांक mfpctl_width;

	पूर्णांक drv_reg;
	अचिन्हित पूर्णांक drv_shअगरt;
	अचिन्हित पूर्णांक drv_width;

	पूर्णांक sr_reg;
	अचिन्हित पूर्णांक sr_shअगरt;
	अचिन्हित पूर्णांक sr_width;
पूर्ण;

/**
 * काष्ठा owl_padinfo - Actions pinctrl pad info
 * @pad: pad name of the SoC
 * @pullctl: pull control रेजिस्टर info
 * @st: schmitt trigger रेजिस्टर info
 */
काष्ठा owl_padinfo अणु
	पूर्णांक pad;
	काष्ठा owl_pullctl *pullctl;
	काष्ठा owl_st *st;
पूर्ण;

/**
 * काष्ठा owl_pinmux_func - Actions pinctrl mux functions
 * @name: name of the pinmux function.
 * @groups: array of pin groups that may select this function.
 * @ngroups: number of entries in @groups.
 */
काष्ठा owl_pinmux_func अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *groups;
	अचिन्हित पूर्णांक ngroups;
पूर्ण;

/**
 * काष्ठा owl_gpio_port - Actions GPIO port info
 * @offset: offset of the GPIO port.
 * @pins: number of pins beदीर्घs to the GPIO port.
 * @outen: offset of the output enable रेजिस्टर.
 * @inen: offset of the input enable रेजिस्टर.
 * @dat: offset of the data रेजिस्टर.
 * @पूर्णांकc_ctl: offset of the पूर्णांकerrupt control रेजिस्टर.
 * @पूर्णांकc_pd: offset of the पूर्णांकerrupt pending रेजिस्टर.
 * @पूर्णांकc_msk: offset of the पूर्णांकerrupt mask रेजिस्टर.
 * @पूर्णांकc_type: offset of the पूर्णांकerrupt type रेजिस्टर.
 */
काष्ठा owl_gpio_port अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक pins;
	अचिन्हित पूर्णांक outen;
	अचिन्हित पूर्णांक inen;
	अचिन्हित पूर्णांक dat;
	अचिन्हित पूर्णांक पूर्णांकc_ctl;
	अचिन्हित पूर्णांक पूर्णांकc_pd;
	अचिन्हित पूर्णांक पूर्णांकc_msk;
	अचिन्हित पूर्णांक पूर्णांकc_type;
	u8 shared_ctl_offset;
पूर्ण;

/**
 * काष्ठा owl_pinctrl_soc_data - Actions pin controller driver configuration
 * @pins: array describing all pins of the pin controller.
 * @npins: number of entries in @pins.
 * @functions: array describing all mux functions of this SoC.
 * @nfunction: number of entries in @functions.
 * @groups: array describing all pin groups of this SoC.
 * @ngroups: number of entries in @groups.
 * @padinfo: array describing the pad info of this SoC.
 * @ngpios: number of pingroups the driver should expose as GPIOs.
 * @ports: array describing all GPIO ports of this SoC.
 * @nports: number of GPIO ports in this SoC.
 */
काष्ठा owl_pinctrl_soc_data अणु
	स्थिर काष्ठा pinctrl_pin_desc *pins;
	अचिन्हित पूर्णांक npins;
	स्थिर काष्ठा owl_pinmux_func *functions;
	अचिन्हित पूर्णांक nfunctions;
	स्थिर काष्ठा owl_pingroup *groups;
	अचिन्हित पूर्णांक ngroups;
	स्थिर काष्ठा owl_padinfo *padinfo;
	अचिन्हित पूर्णांक ngpios;
	स्थिर काष्ठा owl_gpio_port *ports;
	अचिन्हित पूर्णांक nports;
	पूर्णांक (*padctl_val2arg)(स्थिर काष्ठा owl_padinfo *padinfo,
				अचिन्हित पूर्णांक param,
				u32 *arg);
	पूर्णांक (*padctl_arg2val)(स्थिर काष्ठा owl_padinfo *info,
				अचिन्हित पूर्णांक param,
				u32 *arg);
पूर्ण;

पूर्णांक owl_pinctrl_probe(काष्ठा platक्रमm_device *pdev,
		काष्ठा owl_pinctrl_soc_data *soc_data);

#पूर्ण_अगर /* __PINCTRL_OWL_H__ */
