<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/drivers/pinctrl/pinctrl-lantiq.h
 *  based on linux/drivers/pinctrl/pinctrl-pxa3xx.h
 *
 *  Copyright (C) 2012 John Crispin <john@phrozen.org>
 */

#अगर_अघोषित __PINCTRL_LANTIQ_H
#घोषणा __PINCTRL_LANTIQ_H

#समावेश <linux/clkdev.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pinctrl/machine.h>

#समावेश "core.h"

#घोषणा ARRAY_AND_SIZE(x)	(x), ARRAY_SIZE(x)

#घोषणा LTQ_MAX_MUX		4
#घोषणा MFPR_FUNC_MASK		0x3

#घोषणा LTQ_PINCONF_PACK(param, arg)		((param) << 16 | (arg))
#घोषणा LTQ_PINCONF_UNPACK_PARAM(conf)		((conf) >> 16)
#घोषणा LTQ_PINCONF_UNPACK_ARG(conf)		((conf) & 0xffff)

क्रमागत ltq_pinconf_param अणु
	LTQ_PINCONF_PARAM_PULL,
	LTQ_PINCONF_PARAM_OPEN_DRAIN,
	LTQ_PINCONF_PARAM_DRIVE_CURRENT,
	LTQ_PINCONF_PARAM_SLEW_RATE,
	LTQ_PINCONF_PARAM_OUTPUT,
पूर्ण;

काष्ठा ltq_cfg_param अणु
	स्थिर अक्षर *property;
	क्रमागत ltq_pinconf_param param;
पूर्ण;

काष्ठा ltq_mfp_pin अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित पूर्णांक pin;
	स्थिर अचिन्हित लघु func[LTQ_MAX_MUX];
पूर्ण;

काष्ठा ltq_pin_group अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित mux;
	स्थिर अचिन्हित *pins;
	स्थिर अचिन्हित npins;
पूर्ण;

काष्ठा ltq_pmx_func अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *groups;
	स्थिर अचिन्हित num_groups;
पूर्ण;

काष्ठा ltq_pinmux_info अणु
	काष्ठा device *dev;
	काष्ठा pinctrl_dev *pctrl;

	/* we need to manage up to 5 pad controllers */
	व्योम __iomem *membase[5];

	/* the descriptor क्रम the subप्रणाली */
	काष्ठा pinctrl_desc *desc;

	/* we expose our pads to the subप्रणाली */
	काष्ठा pinctrl_pin_desc *pads;

	/* the number of pads. this varies between socs */
	अचिन्हित पूर्णांक num_pads;

	/* these are our multअगरunction pins */
	स्थिर काष्ठा ltq_mfp_pin *mfp;
	अचिन्हित पूर्णांक num_mfp;

	/* a number of multअगरunction pins can be grouped together */
	स्थिर काष्ठा ltq_pin_group *grps;
	अचिन्हित पूर्णांक num_grps;

	/* a mapping between function string and id */
	स्थिर काष्ठा ltq_pmx_func *funcs;
	अचिन्हित पूर्णांक num_funcs;

	/* the pinconf options that we are able to पढ़ो from the DT */
	स्थिर काष्ठा ltq_cfg_param *params;
	अचिन्हित पूर्णांक num_params;

	/* the pad controller can have a irq mapping  */
	स्थिर अचिन्हित *exin;
	अचिन्हित पूर्णांक num_exin;

	/* we need 5 घड़ीs max */
	काष्ठा clk *clk[5];

	/* soc specअगरic callback used to apply muxing */
	पूर्णांक (*apply_mux)(काष्ठा pinctrl_dev *pctrldev, पूर्णांक pin, पूर्णांक mux);
पूर्ण;

क्रमागत ltq_pin अणु
	GPIO0 = 0,
	GPIO1,
	GPIO2,
	GPIO3,
	GPIO4,
	GPIO5,
	GPIO6,
	GPIO7,
	GPIO8,
	GPIO9,
	GPIO10, /* 10 */
	GPIO11,
	GPIO12,
	GPIO13,
	GPIO14,
	GPIO15,
	GPIO16,
	GPIO17,
	GPIO18,
	GPIO19,
	GPIO20, /* 20 */
	GPIO21,
	GPIO22,
	GPIO23,
	GPIO24,
	GPIO25,
	GPIO26,
	GPIO27,
	GPIO28,
	GPIO29,
	GPIO30, /* 30 */
	GPIO31,
	GPIO32,
	GPIO33,
	GPIO34,
	GPIO35,
	GPIO36,
	GPIO37,
	GPIO38,
	GPIO39,
	GPIO40, /* 40 */
	GPIO41,
	GPIO42,
	GPIO43,
	GPIO44,
	GPIO45,
	GPIO46,
	GPIO47,
	GPIO48,
	GPIO49,
	GPIO50, /* 50 */
	GPIO51,
	GPIO52,
	GPIO53,
	GPIO54,
	GPIO55,
	GPIO56,
	GPIO57,
	GPIO58,
	GPIO59,
	GPIO60, /* 60 */
	GPIO61,
	GPIO62,
	GPIO63,

	GPIO64,
	GPIO65,
	GPIO66,
	GPIO67,
	GPIO68,
	GPIO69,
	GPIO70,
	GPIO71,
	GPIO72,
	GPIO73,
	GPIO74,
	GPIO75,
	GPIO76,
	GPIO77,
	GPIO78,
	GPIO79,
	GPIO80,
	GPIO81,
	GPIO82,
	GPIO83,
	GPIO84,
	GPIO85,
	GPIO86,
	GPIO87,
	GPIO88,
पूर्ण;

बाह्य पूर्णांक ltq_pinctrl_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
				   काष्ठा ltq_pinmux_info *info);
बाह्य पूर्णांक ltq_pinctrl_unरेजिस्टर(काष्ठा platक्रमm_device *pdev);
#पूर्ण_अगर	/* __PINCTRL_LANTIQ_H */
