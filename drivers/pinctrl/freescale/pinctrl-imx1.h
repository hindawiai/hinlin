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

#अगर_अघोषित __DRIVERS_PINCTRL_IMX1_H
#घोषणा __DRIVERS_PINCTRL_IMX1_H

काष्ठा platक्रमm_device;

/**
 * काष्ठा imx1_pin - describes an IMX1/21/27 pin.
 * @pin_id: ID of the described pin.
 * @mux_id: ID of the mux setup.
 * @config: Configuration of the pin (currently only pullup-enable).
 */
काष्ठा imx1_pin अणु
	अचिन्हित पूर्णांक pin_id;
	अचिन्हित पूर्णांक mux_id;
	अचिन्हित दीर्घ config;
पूर्ण;

/**
 * काष्ठा imx1_pin_group - describes an IMX pin group
 * @name: the name of this specअगरic pin group
 * @pins: an array of imx1_pin काष्ठाs used in this group
 * @npins: the number of pins in this group array, i.e. the number of
 *	elements in .pins so we can iterate over that array
 */
काष्ठा imx1_pin_group अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक *pin_ids;
	काष्ठा imx1_pin *pins;
	अचिन्हित npins;
पूर्ण;

/**
 * काष्ठा imx1_pmx_func - describes IMX pinmux functions
 * @name: the name of this specअगरic function
 * @groups: corresponding pin groups
 * @num_groups: the number of groups
 */
काष्ठा imx1_pmx_func अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर **groups;
	अचिन्हित num_groups;
पूर्ण;

काष्ठा imx1_pinctrl_soc_info अणु
	काष्ठा device *dev;
	स्थिर काष्ठा pinctrl_pin_desc *pins;
	अचिन्हित पूर्णांक npins;
	काष्ठा imx1_pin_group *groups;
	अचिन्हित पूर्णांक ngroups;
	काष्ठा imx1_pmx_func *functions;
	अचिन्हित पूर्णांक nfunctions;
पूर्ण;

#घोषणा IMX_PINCTRL_PIN(pin) PINCTRL_PIN(pin, #pin)

पूर्णांक imx1_pinctrl_core_probe(काष्ठा platक्रमm_device *pdev,
			काष्ठा imx1_pinctrl_soc_info *info);
#पूर्ण_अगर /* __DRIVERS_PINCTRL_IMX1_H */
