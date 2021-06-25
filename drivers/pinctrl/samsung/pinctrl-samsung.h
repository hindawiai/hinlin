<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * pin-controller/pin-mux/pin-config/gpio-driver क्रम Samsung's SoC's.
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 * Copyright (c) 2012 Linaro Ltd
 *		http://www.linaro.org
 *
 * Author: Thomas Abraham <thomas.ab@samsung.com>
 */

#अगर_अघोषित __PINCTRL_SAMSUNG_H
#घोषणा __PINCTRL_SAMSUNG_H

#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pinctrl/machine.h>

#समावेश <linux/gpio/driver.h>

/**
 * क्रमागत pincfg_type - possible pin configuration types supported.
 * @PINCFG_TYPE_FUNC: Function configuration.
 * @PINCFG_TYPE_DAT: Pin value configuration.
 * @PINCFG_TYPE_PUD: Pull up/करोwn configuration.
 * @PINCFG_TYPE_DRV: Drive strength configuration.
 * @PINCFG_TYPE_CON_PDN: Pin function in घातer करोwn mode.
 * @PINCFG_TYPE_PUD_PDN: Pull up/करोwn configuration in घातer करोwn mode.
 */
क्रमागत pincfg_type अणु
	PINCFG_TYPE_FUNC,
	PINCFG_TYPE_DAT,
	PINCFG_TYPE_PUD,
	PINCFG_TYPE_DRV,
	PINCFG_TYPE_CON_PDN,
	PINCFG_TYPE_PUD_PDN,

	PINCFG_TYPE_NUM
पूर्ण;

/*
 * pin configuration (pull up/करोwn and drive strength) type and its value are
 * packed together पूर्णांकo a 16-bits. The upper 8-bits represent the configuration
 * type and the lower 8-bits hold the value of the configuration type.
 */
#घोषणा PINCFG_TYPE_MASK		0xFF
#घोषणा PINCFG_VALUE_SHIFT		8
#घोषणा PINCFG_VALUE_MASK		(0xFF << PINCFG_VALUE_SHIFT)
#घोषणा PINCFG_PACK(type, value)	(((value) << PINCFG_VALUE_SHIFT) | type)
#घोषणा PINCFG_UNPACK_TYPE(cfg)		((cfg) & PINCFG_TYPE_MASK)
#घोषणा PINCFG_UNPACK_VALUE(cfg)	(((cfg) & PINCFG_VALUE_MASK) >> \
						PINCFG_VALUE_SHIFT)
/**
 * क्रमागत eपूर्णांक_type - possible बाह्यal पूर्णांकerrupt types.
 * @EINT_TYPE_NONE: bank करोes not support बाह्यal पूर्णांकerrupts
 * @EINT_TYPE_GPIO: bank supportes बाह्यal gpio पूर्णांकerrupts
 * @EINT_TYPE_WKUP: bank supportes बाह्यal wakeup पूर्णांकerrupts
 * @EINT_TYPE_WKUP_MUX: bank supports multiplexed बाह्यal wakeup पूर्णांकerrupts
 *
 * Samsung GPIO controller groups all the available pins पूर्णांकo banks. The pins
 * in a pin bank can support बाह्यal gpio पूर्णांकerrupts or बाह्यal wakeup
 * पूर्णांकerrupts or no पूर्णांकerrupts at all. From a software perspective, the only
 * dअगरference between बाह्यal gpio and बाह्यal wakeup पूर्णांकerrupts is that
 * the wakeup पूर्णांकerrupts can additionally wakeup the प्रणाली अगर it is in
 * suspended state.
 */
क्रमागत eपूर्णांक_type अणु
	EINT_TYPE_NONE,
	EINT_TYPE_GPIO,
	EINT_TYPE_WKUP,
	EINT_TYPE_WKUP_MUX,
पूर्ण;

/* maximum length of a pin in pin descriptor (example: "gpa0-0") */
#घोषणा PIN_NAME_LENGTH	10

#घोषणा PIN_GROUP(n, p, f)				\
	अणु						\
		.name		= n,			\
		.pins		= p,			\
		.num_pins	= ARRAY_SIZE(p),	\
		.func		= f			\
	पूर्ण

#घोषणा PMX_FUNC(n, g)					\
	अणु						\
		.name		= n,			\
		.groups		= g,			\
		.num_groups	= ARRAY_SIZE(g),	\
	पूर्ण

काष्ठा samsung_pinctrl_drv_data;

/**
 * काष्ठा samsung_pin_bank_type: pin bank type description
 * @fld_width: widths of configuration bitfields (0 अगर unavailable)
 * @reg_offset: offsets of configuration रेजिस्टरs (करोn't care of width is 0)
 */
काष्ठा samsung_pin_bank_type अणु
	u8 fld_width[PINCFG_TYPE_NUM];
	u8 reg_offset[PINCFG_TYPE_NUM];
पूर्ण;

/**
 * काष्ठा samsung_pin_bank_data: represent a controller pin-bank (init data).
 * @type: type of the bank (रेजिस्टर offsets and bitfield widths)
 * @pctl_offset: starting offset of the pin-bank रेजिस्टरs.
 * @pctl_res_idx: index of base address क्रम pin-bank रेजिस्टरs.
 * @nr_pins: number of pins included in this bank.
 * @eपूर्णांक_func: function to set in CON रेजिस्टर to configure pin as EINT.
 * @eपूर्णांक_type: type of the बाह्यal पूर्णांकerrupt supported by the bank.
 * @eपूर्णांक_mask: bit mask of pins which support EINT function.
 * @eपूर्णांक_offset: SoC-specअगरic EINT रेजिस्टर or पूर्णांकerrupt offset of bank.
 * @name: name to be prefixed क्रम each pin in this pin bank.
 */
काष्ठा samsung_pin_bank_data अणु
	स्थिर काष्ठा samsung_pin_bank_type *type;
	u32		pctl_offset;
	u8		pctl_res_idx;
	u8		nr_pins;
	u8		eपूर्णांक_func;
	क्रमागत eपूर्णांक_type	eपूर्णांक_type;
	u32		eपूर्णांक_mask;
	u32		eपूर्णांक_offset;
	स्थिर अक्षर	*name;
पूर्ण;

/**
 * काष्ठा samsung_pin_bank: represent a controller pin-bank.
 * @type: type of the bank (रेजिस्टर offsets and bitfield widths)
 * @pctl_base: base address of the pin-bank रेजिस्टरs
 * @pctl_offset: starting offset of the pin-bank रेजिस्टरs.
 * @nr_pins: number of pins included in this bank.
 * @eपूर्णांक_base: base address of the pin-bank EINT रेजिस्टरs.
 * @eपूर्णांक_func: function to set in CON रेजिस्टर to configure pin as EINT.
 * @eपूर्णांक_type: type of the बाह्यal पूर्णांकerrupt supported by the bank.
 * @eपूर्णांक_mask: bit mask of pins which support EINT function.
 * @eपूर्णांक_offset: SoC-specअगरic EINT रेजिस्टर or पूर्णांकerrupt offset of bank.
 * @name: name to be prefixed क्रम each pin in this pin bank.
 * @pin_base: starting pin number of the bank.
 * @soc_priv: per-bank निजी data क्रम SoC-specअगरic code.
 * @of_node: OF node of the bank.
 * @drvdata: link to controller driver data
 * @irq_करोमुख्य: IRQ करोमुख्य of the bank.
 * @gpio_chip: GPIO chip of the bank.
 * @grange: linux gpio pin range supported by this bank.
 * @irq_chip: link to irq chip क्रम बाह्यal gpio and wakeup पूर्णांकerrupts.
 * @slock: spinlock protecting bank रेजिस्टरs
 * @pm_save: saved रेजिस्टर values during suspend
 */
काष्ठा samsung_pin_bank अणु
	स्थिर काष्ठा samsung_pin_bank_type *type;
	व्योम __iomem	*pctl_base;
	u32		pctl_offset;
	u8		nr_pins;
	व्योम __iomem	*eपूर्णांक_base;
	u8		eपूर्णांक_func;
	क्रमागत eपूर्णांक_type	eपूर्णांक_type;
	u32		eपूर्णांक_mask;
	u32		eपूर्णांक_offset;
	स्थिर अक्षर	*name;

	u32		pin_base;
	व्योम		*soc_priv;
	काष्ठा device_node *of_node;
	काष्ठा samsung_pinctrl_drv_data *drvdata;
	काष्ठा irq_करोमुख्य *irq_करोमुख्य;
	काष्ठा gpio_chip gpio_chip;
	काष्ठा pinctrl_gpio_range grange;
	काष्ठा exynos_irq_chip *irq_chip;
	raw_spinlock_t slock;

	u32 pm_save[PINCFG_TYPE_NUM + 1]; /* +1 to handle द्विगुन CON रेजिस्टरs*/
पूर्ण;

/**
 * काष्ठा samsung_retention_data: runसमय pin-bank retention control data.
 * @regs: array of PMU रेजिस्टरs to control pad retention.
 * @nr_regs: number of रेजिस्टरs in @regs array.
 * @value: value to store to रेजिस्टरs to turn off retention.
 * @refcnt: atomic counter अगर retention control affects more than one bank.
 * @priv: retention control code निजी data
 * @enable: platक्रमm specअगरic callback to enter retention mode.
 * @disable: platक्रमm specअगरic callback to निकास retention mode.
 **/
काष्ठा samsung_retention_ctrl अणु
	स्थिर u32	*regs;
	पूर्णांक		nr_regs;
	u32		value;
	atomic_t	*refcnt;
	व्योम		*priv;
	व्योम		(*enable)(काष्ठा samsung_pinctrl_drv_data *);
	व्योम		(*disable)(काष्ठा samsung_pinctrl_drv_data *);
पूर्ण;

/**
 * काष्ठा samsung_retention_data: represent a pin-bank retention control data.
 * @regs: array of PMU रेजिस्टरs to control pad retention.
 * @nr_regs: number of रेजिस्टरs in @regs array.
 * @value: value to store to रेजिस्टरs to turn off retention.
 * @refcnt: atomic counter अगर retention control affects more than one bank.
 * @init: platक्रमm specअगरic callback to initialize retention control.
 **/
काष्ठा samsung_retention_data अणु
	स्थिर u32	*regs;
	पूर्णांक		nr_regs;
	u32		value;
	atomic_t	*refcnt;
	काष्ठा samsung_retention_ctrl *(*init)(काष्ठा samsung_pinctrl_drv_data *,
					स्थिर काष्ठा samsung_retention_data *);
पूर्ण;

/**
 * काष्ठा samsung_pin_ctrl: represent a pin controller.
 * @pin_banks: list of pin banks included in this controller.
 * @nr_banks: number of pin banks.
 * @nr_ext_resources: number of the extra base address क्रम pin banks.
 * @retention_data: configuration data क्रम retention control.
 * @eपूर्णांक_gpio_init: platक्रमm specअगरic callback to setup the बाह्यal gpio
 *	पूर्णांकerrupts क्रम the controller.
 * @eपूर्णांक_wkup_init: platक्रमm specअगरic callback to setup the बाह्यal wakeup
 *	पूर्णांकerrupts क्रम the controller.
 * @suspend: platक्रमm specअगरic suspend callback, executed during pin controller
 *	device suspend, see samsung_pinctrl_suspend()
 * @resume: platक्रमm specअगरic resume callback, executed during pin controller
 *	device suspend, see samsung_pinctrl_resume()
 *
 * External wakeup पूर्णांकerrupts must define at least eपूर्णांक_wkup_init,
 * retention_data and suspend in order क्रम proper suspend/resume to work.
 */
काष्ठा samsung_pin_ctrl अणु
	स्थिर काष्ठा samsung_pin_bank_data *pin_banks;
	अचिन्हित पूर्णांक	nr_banks;
	अचिन्हित पूर्णांक	nr_ext_resources;
	स्थिर काष्ठा samsung_retention_data *retention_data;

	पूर्णांक		(*eपूर्णांक_gpio_init)(काष्ठा samsung_pinctrl_drv_data *);
	पूर्णांक		(*eपूर्णांक_wkup_init)(काष्ठा samsung_pinctrl_drv_data *);
	व्योम		(*suspend)(काष्ठा samsung_pinctrl_drv_data *);
	व्योम		(*resume)(काष्ठा samsung_pinctrl_drv_data *);
पूर्ण;

/**
 * काष्ठा samsung_pinctrl_drv_data: wrapper क्रम holding driver data together.
 * @node: global list node
 * @virt_base: रेजिस्टर base address of the controller; this will be equal
 *             to each bank samsung_pin_bank->pctl_base and used on legacy
 *             platक्रमms (like S3C24XX or S3C64XX) which has to access the base
 *             through samsung_pinctrl_drv_data, not samsung_pin_bank).
 * @dev: device instance representing the controller.
 * @irq: पूर्णांकerrpt number used by the controller to notअगरy gpio पूर्णांकerrupts.
 * @ctrl: pin controller instance managed by the driver.
 * @pctl: pin controller descriptor रेजिस्टरed with the pinctrl subप्रणाली.
 * @pctl_dev: cookie representing pinctrl device instance.
 * @pin_groups: list of pin groups available to the driver.
 * @nr_groups: number of such pin groups.
 * @pmx_functions: list of pin functions available to the driver.
 * @nr_function: number of such pin functions.
 * @pin_base: starting प्रणाली wide pin number.
 * @nr_pins: number of pins supported by the controller.
 * @retention_ctrl: retention control runसमय data.
 * @suspend: platक्रमm specअगरic suspend callback, executed during pin controller
 *	device suspend, see samsung_pinctrl_suspend()
 * @resume: platक्रमm specअगरic resume callback, executed during pin controller
 *	device suspend, see samsung_pinctrl_resume()
 */
काष्ठा samsung_pinctrl_drv_data अणु
	काष्ठा list_head		node;
	व्योम __iomem			*virt_base;
	काष्ठा device			*dev;
	पूर्णांक				irq;

	काष्ठा pinctrl_desc		pctl;
	काष्ठा pinctrl_dev		*pctl_dev;

	स्थिर काष्ठा samsung_pin_group	*pin_groups;
	अचिन्हित पूर्णांक			nr_groups;
	स्थिर काष्ठा samsung_pmx_func	*pmx_functions;
	अचिन्हित पूर्णांक			nr_functions;

	काष्ठा samsung_pin_bank		*pin_banks;
	अचिन्हित पूर्णांक			nr_banks;
	अचिन्हित पूर्णांक			pin_base;
	अचिन्हित पूर्णांक			nr_pins;

	काष्ठा samsung_retention_ctrl	*retention_ctrl;

	व्योम (*suspend)(काष्ठा samsung_pinctrl_drv_data *);
	व्योम (*resume)(काष्ठा samsung_pinctrl_drv_data *);
पूर्ण;

/**
 * काष्ठा samsung_pinctrl_of_match_data: OF match device specअगरic configuration data.
 * @ctrl: array of pin controller data.
 * @num_ctrl: size of array @ctrl.
 */
काष्ठा samsung_pinctrl_of_match_data अणु
	स्थिर काष्ठा samsung_pin_ctrl	*ctrl;
	अचिन्हित पूर्णांक			num_ctrl;
पूर्ण;

/**
 * काष्ठा samsung_pin_group: represent group of pins of a pinmux function.
 * @name: name of the pin group, used to lookup the group.
 * @pins: the pins included in this group.
 * @num_pins: number of pins included in this group.
 * @func: the function number to be programmed when selected.
 */
काष्ठा samsung_pin_group अणु
	स्थिर अक्षर		*name;
	स्थिर अचिन्हित पूर्णांक	*pins;
	u8			num_pins;
	u8			func;
पूर्ण;

/**
 * काष्ठा samsung_pmx_func: represent a pin function.
 * @name: name of the pin function, used to lookup the function.
 * @groups: one or more names of pin groups that provide this function.
 * @num_groups: number of groups included in @groups.
 */
काष्ठा samsung_pmx_func अणु
	स्थिर अक्षर		*name;
	स्थिर अक्षर		**groups;
	u8			num_groups;
	u32			val;
पूर्ण;

/* list of all exported SoC specअगरic data */
बाह्य स्थिर काष्ठा samsung_pinctrl_of_match_data exynos3250_of_data;
बाह्य स्थिर काष्ठा samsung_pinctrl_of_match_data exynos4210_of_data;
बाह्य स्थिर काष्ठा samsung_pinctrl_of_match_data exynos4x12_of_data;
बाह्य स्थिर काष्ठा samsung_pinctrl_of_match_data exynos5250_of_data;
बाह्य स्थिर काष्ठा samsung_pinctrl_of_match_data exynos5260_of_data;
बाह्य स्थिर काष्ठा samsung_pinctrl_of_match_data exynos5410_of_data;
बाह्य स्थिर काष्ठा samsung_pinctrl_of_match_data exynos5420_of_data;
बाह्य स्थिर काष्ठा samsung_pinctrl_of_match_data exynos5433_of_data;
बाह्य स्थिर काष्ठा samsung_pinctrl_of_match_data exynos7_of_data;
बाह्य स्थिर काष्ठा samsung_pinctrl_of_match_data s3c64xx_of_data;
बाह्य स्थिर काष्ठा samsung_pinctrl_of_match_data s3c2412_of_data;
बाह्य स्थिर काष्ठा samsung_pinctrl_of_match_data s3c2416_of_data;
बाह्य स्थिर काष्ठा samsung_pinctrl_of_match_data s3c2440_of_data;
बाह्य स्थिर काष्ठा samsung_pinctrl_of_match_data s3c2450_of_data;
बाह्य स्थिर काष्ठा samsung_pinctrl_of_match_data s5pv210_of_data;

#पूर्ण_अगर /* __PINCTRL_SAMSUNG_H */
