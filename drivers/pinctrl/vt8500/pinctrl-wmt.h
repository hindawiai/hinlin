<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Pinctrl driver क्रम the Wondermedia SoC's
 *
 * Copyright (c) 2013 Tony Prisk <linux@prisktech.co.nz>
 */

#समावेश <linux/gpio/driver.h>

/* VT8500 has no enable रेजिस्टर in the extgpio bank. */
#घोषणा NO_REG	0xFFFF

#घोषणा WMT_PINCTRL_BANK(__en, __dir, __करोut, __din, __pen, __pcfg)	\
अणु									\
	.reg_en		= __en,						\
	.reg_dir	= __dir,					\
	.reg_data_out	= __करोut,					\
	.reg_data_in	= __din,					\
	.reg_pull_en	= __pen,					\
	.reg_pull_cfg	= __pcfg,					\
पूर्ण

/* Encode/decode the bank/bit pairs पूर्णांकo a pin value */
#घोषणा WMT_PIN(__bank, __offset)	((__bank << 5) | __offset)
#घोषणा WMT_BANK_FROM_PIN(__pin)	(__pin >> 5)
#घोषणा WMT_BIT_FROM_PIN(__pin)		(__pin & 0x1f)

#घोषणा WMT_GROUP(__name, __data)		\
अणु						\
	.name = __name,				\
	.pins = __data,				\
	.npins = ARRAY_SIZE(__data),		\
पूर्ण

काष्ठा wmt_pinctrl_bank_रेजिस्टरs अणु
	u32	reg_en;
	u32	reg_dir;
	u32	reg_data_out;
	u32	reg_data_in;

	u32	reg_pull_en;
	u32	reg_pull_cfg;
पूर्ण;

काष्ठा wmt_pinctrl_group अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित पूर्णांक *pins;
	स्थिर अचिन्हित npins;
पूर्ण;

काष्ठा wmt_pinctrl_data अणु
	काष्ठा device *dev;
	काष्ठा pinctrl_dev *pctl_dev;

	/* must be initialized beक्रमe calling wmt_pinctrl_probe */
	व्योम __iomem *base;
	स्थिर काष्ठा wmt_pinctrl_bank_रेजिस्टरs *banks;
	स्थिर काष्ठा pinctrl_pin_desc *pins;
	स्थिर अक्षर * स्थिर *groups;

	u32 nbanks;
	u32 npins;
	u32 ngroups;

	काष्ठा gpio_chip gpio_chip;
	काष्ठा pinctrl_gpio_range gpio_range;
पूर्ण;

पूर्णांक wmt_pinctrl_probe(काष्ठा platक्रमm_device *pdev,
		      काष्ठा wmt_pinctrl_data *data);
