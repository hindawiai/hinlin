<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * IMX pinmux core definitions
 *
 * Copyright (C) 2012 Freescale Semiconductor, Inc.
 * Copyright (C) 2012 Linaro Ltd.
 *
 * Author: Dong Aisheng <करोng.aisheng@linaro.org>
 */

#अगर_अघोषित __DRIVERS_PINCTRL_IMX_H
#घोषणा __DRIVERS_PINCTRL_IMX_H

#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinmux.h>

काष्ठा platक्रमm_device;

बाह्य काष्ठा pinmux_ops imx_pmx_ops;
बाह्य स्थिर काष्ठा dev_pm_ops imx_pinctrl_pm_ops;

/**
 * काष्ठा imx_pin_mmio - MMIO pin configurations
 * @mux_mode: the mux mode क्रम this pin.
 * @input_reg: the select input रेजिस्टर offset क्रम this pin अगर any
 *	0 अगर no select input setting needed.
 * @input_val: the select input value क्रम this pin.
 * @configs: the config क्रम this pin.
 */
काष्ठा imx_pin_mmio अणु
	अचिन्हित पूर्णांक mux_mode;
	u16 input_reg;
	अचिन्हित पूर्णांक input_val;
	अचिन्हित दीर्घ config;
पूर्ण;

/**
 * काष्ठा imx_pin_scu - SCU pin configurations
 * @mux: the mux mode क्रम this pin.
 * @configs: the config क्रम this pin.
 */
काष्ठा imx_pin_scu अणु
	अचिन्हित पूर्णांक mux_mode;
	अचिन्हित दीर्घ config;
पूर्ण;

/**
 * काष्ठा imx_pin - describes a single i.MX pin
 * @pin: the pin_id of this pin
 * @conf: config type of this pin, either mmio or scu
 */
काष्ठा imx_pin अणु
	अचिन्हित पूर्णांक pin;
	जोड़ अणु
		काष्ठा imx_pin_mmio mmio;
		काष्ठा imx_pin_scu scu;
	पूर्ण conf;
पूर्ण;

/**
 * काष्ठा imx_pin_reg - describe a pin reg map
 * @mux_reg: mux रेजिस्टर offset
 * @conf_reg: config रेजिस्टर offset
 */
काष्ठा imx_pin_reg अणु
	s16 mux_reg;
	s16 conf_reg;
पूर्ण;

/* decode a generic config पूर्णांकo raw रेजिस्टर value */
काष्ठा imx_cfg_params_decode अणु
	क्रमागत pin_config_param param;
	u32 mask;
	u8 shअगरt;
	bool invert;
पूर्ण;

/**
 * @dev: a poपूर्णांकer back to containing device
 * @base: the offset to the controller in भव memory
 */
काष्ठा imx_pinctrl अणु
	काष्ठा device *dev;
	काष्ठा pinctrl_dev *pctl;
	व्योम __iomem *base;
	व्योम __iomem *input_sel_base;
	स्थिर काष्ठा imx_pinctrl_soc_info *info;
	काष्ठा imx_pin_reg *pin_regs;
	अचिन्हित पूर्णांक group_index;
	काष्ठा mutex mutex;
पूर्ण;

काष्ठा imx_pinctrl_soc_info अणु
	स्थिर काष्ठा pinctrl_pin_desc *pins;
	अचिन्हित पूर्णांक npins;
	अचिन्हित पूर्णांक flags;
	स्थिर अक्षर *gpr_compatible;

	/* MUX_MODE shअगरt and mask in हाल SHARE_MUX_CONF_REG */
	अचिन्हित पूर्णांक mux_mask;
	u8 mux_shअगरt;

	/* generic pinconf */
	bool generic_pinconf;
	स्थिर काष्ठा pinconf_generic_params *custom_params;
	अचिन्हित पूर्णांक num_custom_params;
	स्थिर काष्ठा imx_cfg_params_decode *decodes;
	अचिन्हित पूर्णांक num_decodes;
	व्योम (*fixup)(अचिन्हित दीर्घ *configs, अचिन्हित पूर्णांक num_configs,
		      u32 *raw_config);

	पूर्णांक (*gpio_set_direction)(काष्ठा pinctrl_dev *pctldev,
				  काष्ठा pinctrl_gpio_range *range,
				  अचिन्हित offset,
				  bool input);
	पूर्णांक (*imx_pinconf_get)(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin_id,
			       अचिन्हित दीर्घ *config);
	पूर्णांक (*imx_pinconf_set)(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin_id,
			       अचिन्हित दीर्घ *configs, अचिन्हित पूर्णांक num_configs);
	व्योम (*imx_pinctrl_parse_pin)(काष्ठा imx_pinctrl *ipctl,
				      अचिन्हित पूर्णांक *pin_id, काष्ठा imx_pin *pin,
				      स्थिर __be32 **list_p);
पूर्ण;

#घोषणा IMX_CFG_PARAMS_DECODE(p, m, o) \
	अणु .param = p, .mask = m, .shअगरt = o, .invert = false, पूर्ण

#घोषणा IMX_CFG_PARAMS_DECODE_INVERT(p, m, o) \
	अणु .param = p, .mask = m, .shअगरt = o, .invert = true, पूर्ण

#घोषणा SHARE_MUX_CONF_REG	BIT(0)
#घोषणा ZERO_OFFSET_VALID	BIT(1)
#घोषणा IMX_USE_SCU		BIT(2)

#घोषणा NO_MUX		0x0
#घोषणा NO_PAD		0x0

#घोषणा IMX_PINCTRL_PIN(pin) PINCTRL_PIN(pin, #pin)

#घोषणा PAD_CTL_MASK(len)	((1 << len) - 1)
#घोषणा IMX_MUX_MASK	0x7
#घोषणा IOMUXC_CONFIG_SION	(0x1 << 4)

पूर्णांक imx_pinctrl_probe(काष्ठा platक्रमm_device *pdev,
			स्थिर काष्ठा imx_pinctrl_soc_info *info);

#घोषणा BM_PAD_CTL_GP_ENABLE		BIT(30)
#घोषणा BM_PAD_CTL_IFMUX_ENABLE		BIT(31)
#घोषणा BP_PAD_CTL_IFMUX		27

पूर्णांक imx_pinctrl_sc_ipc_init(काष्ठा platक्रमm_device *pdev);
पूर्णांक imx_pinconf_get_scu(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin_id,
			अचिन्हित दीर्घ *config);
पूर्णांक imx_pinconf_set_scu(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin_id,
			अचिन्हित दीर्घ *configs, अचिन्हित num_configs);
व्योम imx_pinctrl_parse_pin_scu(काष्ठा imx_pinctrl *ipctl,
			       अचिन्हित पूर्णांक *pin_id, काष्ठा imx_pin *pin,
			       स्थिर __be32 **list_p);
#पूर्ण_अगर /* __DRIVERS_PINCTRL_IMX_H */
