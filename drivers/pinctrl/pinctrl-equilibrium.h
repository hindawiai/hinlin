<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Copyright(c) 2019 Intel Corporation.
 */

#अगर_अघोषित __PINCTRL_EQUILIBRIUM_H
#घोषणा __PINCTRL_EQUILIBRIUM_H

/* PINPAD रेजिस्टर offset */
#घोषणा REG_PMX_BASE	0x0	/* Port Multiplexer Control Register */
#घोषणा REG_PUEN	0x80	/* PULL UP Enable Register */
#घोषणा REG_PDEN	0x84	/* PULL DOWN Enable Register */
#घोषणा REG_SRC		0x88	/* Slew Rate Control Register */
#घोषणा REG_DCC0	0x8C	/* Drive Current Control Register 0 */
#घोषणा REG_DCC1	0x90	/* Drive Current Control Register 1 */
#घोषणा REG_OD		0x94	/* Open Drain Enable Register */
#घोषणा REG_AVAIL	0x98	/* Pad Control Availability Register */
#घोषणा DRV_CUR_PINS	16	/* Drive Current pin number per रेजिस्टर */
#घोषणा REG_DRCC(x)	(REG_DCC0 + (x) * 4) /* Driver current macro */

/* GPIO रेजिस्टर offset */
#घोषणा GPIO_OUT	0x0	/* Data Output Register */
#घोषणा GPIO_IN		0x4	/* Data Input Register */
#घोषणा GPIO_सूची	0x8	/* Direction Register */
#घोषणा GPIO_EXINTCR0	0x18	/* External Interrupt Control Register 0 */
#घोषणा GPIO_EXINTCR1	0x1C	/* External Interrupt Control Register 1 */
#घोषणा GPIO_IRNCR	0x20	/* IRN Capture Register */
#घोषणा GPIO_IRNICR	0x24	/* IRN Interrupt Control Register */
#घोषणा GPIO_IRNEN	0x28	/* IRN Interrupt Enable Register */
#घोषणा GPIO_IRNCFG	0x2C	/* IRN Interrupt Configuration Register */
#घोषणा GPIO_IRNRNSET	0x30	/* IRN Interrupt Enable Set Register */
#घोषणा GPIO_IRNENCLR	0x34	/* IRN Interrupt Enable Clear Register */
#घोषणा GPIO_OUTSET	0x40	/* Output Set Register */
#घोषणा GPIO_OUTCLR	0x44	/* Output Clear Register */
#घोषणा GPIO_सूचीSET	0x48	/* Direction Set Register */
#घोषणा GPIO_सूचीCLR	0x4C	/* Direction Clear Register */

/* parse given pin's driver current value */
#घोषणा PARSE_DRV_CURRENT(val, pin) (((val) >> ((pin) * 2)) & 0x3)

#घोषणा GPIO_EDGE_TRIG		0
#घोषणा GPIO_LEVEL_TRIG		1
#घोषणा GPIO_SINGLE_EDGE	0
#घोषणा GPIO_BOTH_EDGE		1
#घोषणा GPIO_POSITIVE_TRIG	0
#घोषणा GPIO_NEGATIVE_TRIG	1

#घोषणा EQBR_GPIO_MODE		0

प्रकार क्रमागत अणु
	OP_COUNT_NR_FUNCS,
	OP_ADD_FUNCS,
	OP_COUNT_NR_FUNC_GRPS,
	OP_ADD_FUNC_GRPS,
	OP_NONE,
पूर्ण funcs_util_ops;

/**
 * काष्ठा gpio_irq_type: gpio irq configuration
 * @trig_type: level trigger or edge trigger
 * @edge_type: sigle edge or both edge
 * @logic_type: positive trigger or negative trigger
 */
काष्ठा gpio_irq_type अणु
	अचिन्हित पूर्णांक trig_type;
	अचिन्हित पूर्णांक edge_type;
	अचिन्हित पूर्णांक logic_type;
पूर्ण;

/**
 * काष्ठा eqbr_pmx_func: represent a pin function.
 * @name: name of the pin function, used to lookup the function.
 * @groups: one or more names of pin groups that provide this function.
 * @nr_groups: number of groups included in @groups.
 */
काष्ठा eqbr_pmx_func अणु
	स्थिर अक्षर		*name;
	स्थिर अक्षर		**groups;
	अचिन्हित पूर्णांक		nr_groups;
पूर्ण;

/**
 * काष्ठा eqbr_pin_bank: represent a pin bank.
 * @membase: base address of the pin bank रेजिस्टर.
 * @id: bank id, to idenअगरy the unique bank.
 * @pin_base: starting pin number of the pin bank.
 * @nr_pins: number of the pins of the pin bank.
 * @aval_pinmap: available pin biपंचांगap of the pin bank.
 */
काष्ठा eqbr_pin_bank अणु
	व्योम __iomem		*membase;
	अचिन्हित पूर्णांक		id;
	अचिन्हित पूर्णांक		pin_base;
	अचिन्हित पूर्णांक		nr_pins;
	u32			aval_pinmap;
पूर्ण;

/**
 * काष्ठा eqbr_gpio_ctrl: represent a gpio controller.
 * @node: device node of gpio controller.
 * @bank: poपूर्णांकer to corresponding pin bank.
 * @membase: base address of the gpio controller.
 * @chip: gpio chip.
 * @ic:   irq chip.
 * @name: gpio chip name.
 * @virq: irq number of the gpio chip to parent's irq करोमुख्य.
 * @lock: spin lock to protect gpio रेजिस्टर ग_लिखो.
 */
काष्ठा eqbr_gpio_ctrl अणु
	काष्ठा device_node	*node;
	काष्ठा eqbr_pin_bank	*bank;
	व्योम __iomem		*membase;
	काष्ठा gpio_chip	chip;
	काष्ठा irq_chip		ic;
	स्थिर अक्षर		*name;
	अचिन्हित पूर्णांक		virq;
	raw_spinlock_t		lock; /* protect gpio रेजिस्टर */
पूर्ण;

/**
 * काष्ठा eqbr_pinctrl_drv_data:
 * @dev: device instance representing the controller.
 * @pctl_desc: pin controller descriptor.
 * @pctl_dev: pin control class device
 * @membase: base address of pin controller
 * @pin_banks: list of pin banks of the driver.
 * @nr_banks: number of pin banks.
 * @gpio_ctrls: list of gpio controllers.
 * @nr_gpio_ctrls: number of gpio controllers.
 * @lock: protect pinctrl रेजिस्टर ग_लिखो
 */
काष्ठा eqbr_pinctrl_drv_data अणु
	काष्ठा device			*dev;
	काष्ठा pinctrl_desc		pctl_desc;
	काष्ठा pinctrl_dev		*pctl_dev;
	व्योम __iomem			*membase;
	काष्ठा eqbr_pin_bank		*pin_banks;
	अचिन्हित पूर्णांक			nr_banks;
	काष्ठा eqbr_gpio_ctrl		*gpio_ctrls;
	अचिन्हित पूर्णांक			nr_gpio_ctrls;
	raw_spinlock_t			lock; /* protect pinpad रेजिस्टर */
पूर्ण;

#पूर्ण_अगर /* __PINCTRL_EQUILIBRIUM_H */
