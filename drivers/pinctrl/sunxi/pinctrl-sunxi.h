<शैली गुरु>
/*
 * Allwinner A1X SoCs pinctrl driver.
 *
 * Copyright (C) 2012 Maxime Ripard
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __PINCTRL_SUNXI_H
#घोषणा __PINCTRL_SUNXI_H

#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>

#घोषणा PA_BASE	0
#घोषणा PB_BASE	32
#घोषणा PC_BASE	64
#घोषणा PD_BASE	96
#घोषणा PE_BASE	128
#घोषणा PF_BASE	160
#घोषणा PG_BASE	192
#घोषणा PH_BASE	224
#घोषणा PI_BASE	256
#घोषणा PL_BASE	352
#घोषणा PM_BASE	384
#घोषणा PN_BASE	416

#घोषणा SUNXI_PINCTRL_PIN(bank, pin)		\
	PINCTRL_PIN(P ## bank ## _BASE + (pin), "P" #bank #pin)

#घोषणा SUNXI_PIN_NAME_MAX_LEN	5

#घोषणा BANK_MEM_SIZE		0x24
#घोषणा MUX_REGS_OFFSET		0x0
#घोषणा DATA_REGS_OFFSET	0x10
#घोषणा DLEVEL_REGS_OFFSET	0x14
#घोषणा PULL_REGS_OFFSET	0x1c

#घोषणा PINS_PER_BANK		32
#घोषणा MUX_PINS_PER_REG	8
#घोषणा MUX_PINS_BITS		4
#घोषणा MUX_PINS_MASK		0x0f
#घोषणा DATA_PINS_PER_REG	32
#घोषणा DATA_PINS_BITS		1
#घोषणा DATA_PINS_MASK		0x01
#घोषणा DLEVEL_PINS_PER_REG	16
#घोषणा DLEVEL_PINS_BITS	2
#घोषणा DLEVEL_PINS_MASK	0x03
#घोषणा PULL_PINS_PER_REG	16
#घोषणा PULL_PINS_BITS		2
#घोषणा PULL_PINS_MASK		0x03

#घोषणा IRQ_PER_BANK		32

#घोषणा IRQ_CFG_REG		0x200
#घोषणा IRQ_CFG_IRQ_PER_REG		8
#घोषणा IRQ_CFG_IRQ_BITS		4
#घोषणा IRQ_CFG_IRQ_MASK		((1 << IRQ_CFG_IRQ_BITS) - 1)
#घोषणा IRQ_CTRL_REG		0x210
#घोषणा IRQ_CTRL_IRQ_PER_REG		32
#घोषणा IRQ_CTRL_IRQ_BITS		1
#घोषणा IRQ_CTRL_IRQ_MASK		((1 << IRQ_CTRL_IRQ_BITS) - 1)
#घोषणा IRQ_STATUS_REG		0x214
#घोषणा IRQ_STATUS_IRQ_PER_REG		32
#घोषणा IRQ_STATUS_IRQ_BITS		1
#घोषणा IRQ_STATUS_IRQ_MASK		((1 << IRQ_STATUS_IRQ_BITS) - 1)

#घोषणा IRQ_DEBOUNCE_REG	0x218

#घोषणा IRQ_MEM_SIZE		0x20

#घोषणा IRQ_EDGE_RISING		0x00
#घोषणा IRQ_EDGE_FALLING	0x01
#घोषणा IRQ_LEVEL_HIGH		0x02
#घोषणा IRQ_LEVEL_LOW		0x03
#घोषणा IRQ_EDGE_BOTH		0x04

#घोषणा GRP_CFG_REG		0x300

#घोषणा IO_BIAS_MASK		GENMASK(3, 0)

#घोषणा SUN4I_FUNC_INPUT	0
#घोषणा SUN4I_FUNC_IRQ		6

#घोषणा PINCTRL_SUN5I_A10S	BIT(1)
#घोषणा PINCTRL_SUN5I_A13	BIT(2)
#घोषणा PINCTRL_SUN5I_GR8	BIT(3)
#घोषणा PINCTRL_SUN6I_A31	BIT(4)
#घोषणा PINCTRL_SUN6I_A31S	BIT(5)
#घोषणा PINCTRL_SUN4I_A10	BIT(6)
#घोषणा PINCTRL_SUN7I_A20	BIT(7)
#घोषणा PINCTRL_SUN8I_R40	BIT(8)
#घोषणा PINCTRL_SUN8I_V3	BIT(9)
#घोषणा PINCTRL_SUN8I_V3S	BIT(10)

#घोषणा PIO_POW_MOD_SEL_REG	0x340

क्रमागत sunxi_desc_bias_voltage अणु
	BIAS_VOLTAGE_NONE,
	/*
	 * Bias voltage configuration is करोne through
	 * Pn_GRP_CONFIG रेजिस्टरs, as seen on A80 SoC.
	 */
	BIAS_VOLTAGE_GRP_CONFIG,
	/*
	 * Bias voltage is set through PIO_POW_MOD_SEL_REG
	 * रेजिस्टर, as seen on H6 SoC, क्रम example.
	 */
	BIAS_VOLTAGE_PIO_POW_MODE_SEL,
पूर्ण;

काष्ठा sunxi_desc_function अणु
	अचिन्हित दीर्घ	variant;
	स्थिर अक्षर	*name;
	u8		muxval;
	u8		irqbank;
	u8		irqnum;
पूर्ण;

काष्ठा sunxi_desc_pin अणु
	काष्ठा pinctrl_pin_desc		pin;
	अचिन्हित दीर्घ			variant;
	काष्ठा sunxi_desc_function	*functions;
पूर्ण;

काष्ठा sunxi_pinctrl_desc अणु
	स्थिर काष्ठा sunxi_desc_pin	*pins;
	पूर्णांक				npins;
	अचिन्हित			pin_base;
	अचिन्हित			irq_banks;
	स्थिर अचिन्हित पूर्णांक		*irq_bank_map;
	bool				irq_पढ़ो_needs_mux;
	bool				disable_strict_mode;
	क्रमागत sunxi_desc_bias_voltage	io_bias_cfg_variant;
पूर्ण;

काष्ठा sunxi_pinctrl_function अणु
	स्थिर अक्षर	*name;
	स्थिर अक्षर	**groups;
	अचिन्हित	ngroups;
पूर्ण;

काष्ठा sunxi_pinctrl_group अणु
	स्थिर अक्षर	*name;
	अचिन्हित	pin;
पूर्ण;

काष्ठा sunxi_pinctrl_regulator अणु
	काष्ठा regulator	*regulator;
	refcount_t		refcount;
पूर्ण;

काष्ठा sunxi_pinctrl अणु
	व्योम __iomem			*membase;
	काष्ठा gpio_chip		*chip;
	स्थिर काष्ठा sunxi_pinctrl_desc	*desc;
	काष्ठा device			*dev;
	काष्ठा sunxi_pinctrl_regulator	regulators[9];
	काष्ठा irq_करोमुख्य		*करोमुख्य;
	काष्ठा sunxi_pinctrl_function	*functions;
	अचिन्हित			nfunctions;
	काष्ठा sunxi_pinctrl_group	*groups;
	अचिन्हित			ngroups;
	पूर्णांक				*irq;
	अचिन्हित			*irq_array;
	raw_spinlock_t			lock;
	काष्ठा pinctrl_dev		*pctl_dev;
	अचिन्हित दीर्घ			variant;
पूर्ण;

#घोषणा SUNXI_PIN(_pin, ...)					\
	अणु							\
		.pin = _pin,					\
		.functions = (काष्ठा sunxi_desc_function[])अणु	\
			__VA_ARGS__, अणु पूर्ण पूर्ण,			\
	पूर्ण

#घोषणा SUNXI_PIN_VARIANT(_pin, _variant, ...)			\
	अणु							\
		.pin = _pin,					\
		.variant = _variant,				\
		.functions = (काष्ठा sunxi_desc_function[])अणु	\
			__VA_ARGS__, अणु पूर्ण पूर्ण,			\
	पूर्ण

#घोषणा SUNXI_FUNCTION(_val, _name)				\
	अणु							\
		.name = _name,					\
		.muxval = _val,					\
	पूर्ण

#घोषणा SUNXI_FUNCTION_VARIANT(_val, _name, _variant)		\
	अणु							\
		.name = _name,					\
		.muxval = _val,					\
		.variant = _variant,				\
	पूर्ण

#घोषणा SUNXI_FUNCTION_IRQ(_val, _irq)				\
	अणु							\
		.name = "irq",					\
		.muxval = _val,					\
		.irqnum = _irq,					\
	पूर्ण

#घोषणा SUNXI_FUNCTION_IRQ_BANK(_val, _bank, _irq)		\
	अणु							\
		.name = "irq",					\
		.muxval = _val,					\
		.irqbank = _bank,				\
		.irqnum = _irq,					\
	पूर्ण

/*
 * The sunXi PIO रेजिस्टरs are organized as is:
 * 0x00 - 0x0c	Muxing values.
 *		8 pins per रेजिस्टर, each pin having a 4bits value
 * 0x10		Pin values
 *		32 bits per रेजिस्टर, each pin corresponding to one bit
 * 0x14 - 0x18	Drive level
 *		16 pins per रेजिस्टर, each pin having a 2bits value
 * 0x1c - 0x20	Pull-Up values
 *		16 pins per रेजिस्टर, each pin having a 2bits value
 *
 * This is क्रम the first bank. Each bank will have the same layout,
 * with an offset being a multiple of 0x24.
 *
 * The following functions calculate from the pin number the रेजिस्टर
 * and the bit offset that we should access.
 */
अटल अंतरभूत u32 sunxi_mux_reg(u16 pin)
अणु
	u8 bank = pin / PINS_PER_BANK;
	u32 offset = bank * BANK_MEM_SIZE;
	offset += MUX_REGS_OFFSET;
	offset += pin % PINS_PER_BANK / MUX_PINS_PER_REG * 0x04;
	वापस round_करोwn(offset, 4);
पूर्ण

अटल अंतरभूत u32 sunxi_mux_offset(u16 pin)
अणु
	u32 pin_num = pin % MUX_PINS_PER_REG;
	वापस pin_num * MUX_PINS_BITS;
पूर्ण

अटल अंतरभूत u32 sunxi_data_reg(u16 pin)
अणु
	u8 bank = pin / PINS_PER_BANK;
	u32 offset = bank * BANK_MEM_SIZE;
	offset += DATA_REGS_OFFSET;
	offset += pin % PINS_PER_BANK / DATA_PINS_PER_REG * 0x04;
	वापस round_करोwn(offset, 4);
पूर्ण

अटल अंतरभूत u32 sunxi_data_offset(u16 pin)
अणु
	u32 pin_num = pin % DATA_PINS_PER_REG;
	वापस pin_num * DATA_PINS_BITS;
पूर्ण

अटल अंतरभूत u32 sunxi_dlevel_reg(u16 pin)
अणु
	u8 bank = pin / PINS_PER_BANK;
	u32 offset = bank * BANK_MEM_SIZE;
	offset += DLEVEL_REGS_OFFSET;
	offset += pin % PINS_PER_BANK / DLEVEL_PINS_PER_REG * 0x04;
	वापस round_करोwn(offset, 4);
पूर्ण

अटल अंतरभूत u32 sunxi_dlevel_offset(u16 pin)
अणु
	u32 pin_num = pin % DLEVEL_PINS_PER_REG;
	वापस pin_num * DLEVEL_PINS_BITS;
पूर्ण

अटल अंतरभूत u32 sunxi_pull_reg(u16 pin)
अणु
	u8 bank = pin / PINS_PER_BANK;
	u32 offset = bank * BANK_MEM_SIZE;
	offset += PULL_REGS_OFFSET;
	offset += pin % PINS_PER_BANK / PULL_PINS_PER_REG * 0x04;
	वापस round_करोwn(offset, 4);
पूर्ण

अटल अंतरभूत u32 sunxi_pull_offset(u16 pin)
अणु
	u32 pin_num = pin % PULL_PINS_PER_REG;
	वापस pin_num * PULL_PINS_BITS;
पूर्ण

अटल अंतरभूत u32 sunxi_irq_hw_bank_num(स्थिर काष्ठा sunxi_pinctrl_desc *desc, u8 bank)
अणु
	अगर (!desc->irq_bank_map)
		वापस bank;
	अन्यथा
		वापस desc->irq_bank_map[bank];
पूर्ण

अटल अंतरभूत u32 sunxi_irq_cfg_reg(स्थिर काष्ठा sunxi_pinctrl_desc *desc,
				    u16 irq)
अणु
	u8 bank = irq / IRQ_PER_BANK;
	u8 reg = (irq % IRQ_PER_BANK) / IRQ_CFG_IRQ_PER_REG * 0x04;

	वापस IRQ_CFG_REG +
	       sunxi_irq_hw_bank_num(desc, bank) * IRQ_MEM_SIZE + reg;
पूर्ण

अटल अंतरभूत u32 sunxi_irq_cfg_offset(u16 irq)
अणु
	u32 irq_num = irq % IRQ_CFG_IRQ_PER_REG;
	वापस irq_num * IRQ_CFG_IRQ_BITS;
पूर्ण

अटल अंतरभूत u32 sunxi_irq_ctrl_reg_from_bank(स्थिर काष्ठा sunxi_pinctrl_desc *desc, u8 bank)
अणु
	वापस IRQ_CTRL_REG + sunxi_irq_hw_bank_num(desc, bank) * IRQ_MEM_SIZE;
पूर्ण

अटल अंतरभूत u32 sunxi_irq_ctrl_reg(स्थिर काष्ठा sunxi_pinctrl_desc *desc,
				     u16 irq)
अणु
	u8 bank = irq / IRQ_PER_BANK;

	वापस sunxi_irq_ctrl_reg_from_bank(desc, bank);
पूर्ण

अटल अंतरभूत u32 sunxi_irq_ctrl_offset(u16 irq)
अणु
	u32 irq_num = irq % IRQ_CTRL_IRQ_PER_REG;
	वापस irq_num * IRQ_CTRL_IRQ_BITS;
पूर्ण

अटल अंतरभूत u32 sunxi_irq_debounce_reg_from_bank(स्थिर काष्ठा sunxi_pinctrl_desc *desc, u8 bank)
अणु
	वापस IRQ_DEBOUNCE_REG +
	       sunxi_irq_hw_bank_num(desc, bank) * IRQ_MEM_SIZE;
पूर्ण

अटल अंतरभूत u32 sunxi_irq_status_reg_from_bank(स्थिर काष्ठा sunxi_pinctrl_desc *desc, u8 bank)
अणु
	वापस IRQ_STATUS_REG +
	       sunxi_irq_hw_bank_num(desc, bank) * IRQ_MEM_SIZE;
पूर्ण

अटल अंतरभूत u32 sunxi_irq_status_reg(स्थिर काष्ठा sunxi_pinctrl_desc *desc,
				       u16 irq)
अणु
	u8 bank = irq / IRQ_PER_BANK;

	वापस sunxi_irq_status_reg_from_bank(desc, bank);
पूर्ण

अटल अंतरभूत u32 sunxi_irq_status_offset(u16 irq)
अणु
	u32 irq_num = irq % IRQ_STATUS_IRQ_PER_REG;
	वापस irq_num * IRQ_STATUS_IRQ_BITS;
पूर्ण

अटल अंतरभूत u32 sunxi_grp_config_reg(u16 pin)
अणु
	u8 bank = pin / PINS_PER_BANK;

	वापस GRP_CFG_REG + bank * 0x4;
पूर्ण

पूर्णांक sunxi_pinctrl_init_with_variant(काष्ठा platक्रमm_device *pdev,
				    स्थिर काष्ठा sunxi_pinctrl_desc *desc,
				    अचिन्हित दीर्घ variant);

#घोषणा sunxi_pinctrl_init(_dev, _desc) \
	sunxi_pinctrl_init_with_variant(_dev, _desc, 0)

#पूर्ण_अगर /* __PINCTRL_SUNXI_H */
