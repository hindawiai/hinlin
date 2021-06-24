<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2016 IBM Corp.
 */

#अगर_अघोषित PINCTRL_ASPEED
#घोषणा PINCTRL_ASPEED

#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/regmap.h>

#समावेश "pinmux-aspeed.h"

/**
 * @param The pinconf parameter type
 * @pins The pin range this config काष्ठा covers, [low, high]
 * @reg The रेजिस्टर housing the configuration bits
 * @mask The mask to select the bits of पूर्णांकerest in @reg
 */
काष्ठा aspeed_pin_config अणु
	क्रमागत pin_config_param param;
	अचिन्हित पूर्णांक pins[2];
	अचिन्हित पूर्णांक reg;
	u32 mask;
पूर्ण;

#घोषणा ASPEED_PINCTRL_PIN(name_) \
	[name_] = अणु \
		.number = name_, \
		.name = #name_, \
		.drv_data = (व्योम *) &(PIN_SYM(name_)) \
	पूर्ण

#घोषणा ASPEED_SB_PINCONF(param_, pin0_, pin1_, reg_, bit_) अणु \
	.param = param_, \
	.pins = अणुpin0_, pin1_पूर्ण, \
	.reg = reg_, \
	.mask = BIT_MASK(bit_) \
पूर्ण

#घोषणा ASPEED_PULL_DOWN_PINCONF(pin_, reg_, bit_) \
	ASPEED_SB_PINCONF(PIN_CONFIG_BIAS_PULL_DOWN, pin_, pin_, reg_, bit_), \
	ASPEED_SB_PINCONF(PIN_CONFIG_BIAS_DISABLE,   pin_, pin_, reg_, bit_)

#घोषणा ASPEED_PULL_UP_PINCONF(pin_, reg_, bit_) \
	ASPEED_SB_PINCONF(PIN_CONFIG_BIAS_PULL_UP, pin_, pin_, reg_, bit_), \
	ASPEED_SB_PINCONF(PIN_CONFIG_BIAS_DISABLE, pin_, pin_, reg_, bit_)
/*
 * Aspeed pin configuration description.
 *
 * @param: pinconf configuration parameter
 * @arg: The supported argument क्रम @param, or -1 अगर any value is supported
 * @val: The रेजिस्टर value to ग_लिखो to configure @arg क्रम @param
 * @mask: The bitfield mask क्रम @val
 *
 * The map is to be used in conjunction with the configuration array supplied
 * by the driver implementation.
 */
काष्ठा aspeed_pin_config_map अणु
	क्रमागत pin_config_param param;
	s32 arg;
	u32 val;
	u32 mask;
पूर्ण;

काष्ठा aspeed_pinctrl_data अणु
	काष्ठा regmap *scu;

	स्थिर काष्ठा pinctrl_pin_desc *pins;
	स्थिर अचिन्हित पूर्णांक npins;

	स्थिर काष्ठा aspeed_pin_config *configs;
	स्थिर अचिन्हित पूर्णांक nconfigs;

	काष्ठा aspeed_pinmux_data pinmux;

	स्थिर काष्ठा aspeed_pin_config_map *confmaps;
	स्थिर अचिन्हित पूर्णांक nconfmaps;
पूर्ण;

/* Aspeed pinctrl helpers */
पूर्णांक aspeed_pinctrl_get_groups_count(काष्ठा pinctrl_dev *pctldev);
स्थिर अक्षर *aspeed_pinctrl_get_group_name(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित पूर्णांक group);
पूर्णांक aspeed_pinctrl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित पूर्णांक group, स्थिर अचिन्हित पूर्णांक **pins,
		अचिन्हित पूर्णांक *npins);
व्योम aspeed_pinctrl_pin_dbg_show(काष्ठा pinctrl_dev *pctldev,
		काष्ठा seq_file *s, अचिन्हित पूर्णांक offset);
पूर्णांक aspeed_pinmux_get_fn_count(काष्ठा pinctrl_dev *pctldev);
स्थिर अक्षर *aspeed_pinmux_get_fn_name(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित पूर्णांक function);
पूर्णांक aspeed_pinmux_get_fn_groups(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित पूर्णांक function, स्थिर अक्षर * स्थिर **groups,
		अचिन्हित पूर्णांक * स्थिर num_groups);
पूर्णांक aspeed_pinmux_set_mux(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक function,
		अचिन्हित पूर्णांक group);
पूर्णांक aspeed_gpio_request_enable(काष्ठा pinctrl_dev *pctldev,
		काष्ठा pinctrl_gpio_range *range,
		अचिन्हित पूर्णांक offset);
पूर्णांक aspeed_pinctrl_probe(काष्ठा platक्रमm_device *pdev,
		काष्ठा pinctrl_desc *pdesc,
		काष्ठा aspeed_pinctrl_data *pdata);
पूर्णांक aspeed_pin_config_get(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक offset,
		अचिन्हित दीर्घ *config);
पूर्णांक aspeed_pin_config_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक offset,
		अचिन्हित दीर्घ *configs, अचिन्हित पूर्णांक num_configs);
पूर्णांक aspeed_pin_config_group_get(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित पूर्णांक selector,
		अचिन्हित दीर्घ *config);
पूर्णांक aspeed_pin_config_group_set(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित पूर्णांक selector,
		अचिन्हित दीर्घ *configs,
		अचिन्हित पूर्णांक num_configs);

#पूर्ण_अगर /* PINCTRL_ASPEED */
