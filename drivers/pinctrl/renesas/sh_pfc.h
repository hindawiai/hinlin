<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * SuperH Pin Function Controller Support
 *
 * Copyright (c) 2008 Magnus Damm
 */

#अगर_अघोषित __SH_PFC_H
#घोषणा __SH_PFC_H

#समावेश <linux/bug.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/stringअगरy.h>

क्रमागत अणु
	PINMUX_TYPE_NONE,
	PINMUX_TYPE_FUNCTION,
	PINMUX_TYPE_GPIO,
	PINMUX_TYPE_OUTPUT,
	PINMUX_TYPE_INPUT,
पूर्ण;

#घोषणा SH_PFC_PIN_NONE			U16_MAX

#घोषणा SH_PFC_PIN_CFG_INPUT		(1 << 0)
#घोषणा SH_PFC_PIN_CFG_OUTPUT		(1 << 1)
#घोषणा SH_PFC_PIN_CFG_PULL_UP		(1 << 2)
#घोषणा SH_PFC_PIN_CFG_PULL_DOWN	(1 << 3)
#घोषणा SH_PFC_PIN_CFG_PULL_UP_DOWN	(SH_PFC_PIN_CFG_PULL_UP | \
					 SH_PFC_PIN_CFG_PULL_DOWN)
#घोषणा SH_PFC_PIN_CFG_IO_VOLTAGE	(1 << 4)
#घोषणा SH_PFC_PIN_CFG_DRIVE_STRENGTH	(1 << 5)

#घोषणा SH_PFC_PIN_VOLTAGE_18_33	(0 << 6)
#घोषणा SH_PFC_PIN_VOLTAGE_25_33	(1 << 6)

#घोषणा SH_PFC_PIN_CFG_IO_VOLTAGE_18_33	(SH_PFC_PIN_CFG_IO_VOLTAGE | \
					 SH_PFC_PIN_VOLTAGE_18_33)
#घोषणा SH_PFC_PIN_CFG_IO_VOLTAGE_25_33	(SH_PFC_PIN_CFG_IO_VOLTAGE | \
					 SH_PFC_PIN_VOLTAGE_25_33)

#घोषणा SH_PFC_PIN_CFG_NO_GPIO		(1 << 31)

काष्ठा sh_pfc_pin अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक configs;
	u16 pin;
	u16 क्रमागत_id;
पूर्ण;

#घोषणा SH_PFC_PIN_GROUP_ALIAS(alias, n)		\
	अणु						\
		.name = #alias,				\
		.pins = n##_pins,			\
		.mux = n##_mux,				\
		.nr_pins = ARRAY_SIZE(n##_pins) +	\
		BUILD_BUG_ON_ZERO(माप(n##_pins) != माप(n##_mux)), \
	पूर्ण
#घोषणा SH_PFC_PIN_GROUP(n)	SH_PFC_PIN_GROUP_ALIAS(n, n)

काष्ठा sh_pfc_pin_group अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित पूर्णांक *pins;
	स्थिर अचिन्हित पूर्णांक *mux;
	अचिन्हित पूर्णांक nr_pins;
पूर्ण;

/*
 * Using जोड़ vin_dataअणु,12,16पूर्ण saves memory occupied by the VIN data pins.
 * VIN_DATA_PIN_GROUP() is a macro used to describe the VIN pin groups
 * in this हाल. It accepts an optional 'version' argument used when the
 * same group can appear on a dअगरferent set of pins.
 */
#घोषणा VIN_DATA_PIN_GROUP(n, s, ...)					\
	अणु								\
		.name = #n#s#__VA_ARGS__,				\
		.pins = n##__VA_ARGS__##_pins.data##s,			\
		.mux = n##__VA_ARGS__##_mux.data##s,			\
		.nr_pins = ARRAY_SIZE(n##__VA_ARGS__##_pins.data##s),	\
	पूर्ण

जोड़ vin_data12 अणु
	अचिन्हित पूर्णांक data12[12];
	अचिन्हित पूर्णांक data10[10];
	अचिन्हित पूर्णांक data8[8];
पूर्ण;

जोड़ vin_data16 अणु
	अचिन्हित पूर्णांक data16[16];
	अचिन्हित पूर्णांक data12[12];
	अचिन्हित पूर्णांक data10[10];
	अचिन्हित पूर्णांक data8[8];
पूर्ण;

जोड़ vin_data अणु
	अचिन्हित पूर्णांक data24[24];
	अचिन्हित पूर्णांक data20[20];
	अचिन्हित पूर्णांक data16[16];
	अचिन्हित पूर्णांक data12[12];
	अचिन्हित पूर्णांक data10[10];
	अचिन्हित पूर्णांक data8[8];
	अचिन्हित पूर्णांक data4[4];
पूर्ण;

#घोषणा SH_PFC_FUNCTION(n)				\
	अणु						\
		.name = #n,				\
		.groups = n##_groups,			\
		.nr_groups = ARRAY_SIZE(n##_groups),	\
	पूर्ण

काष्ठा sh_pfc_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *groups;
	अचिन्हित पूर्णांक nr_groups;
पूर्ण;

काष्ठा pinmux_func अणु
	u16 क्रमागत_id;
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा pinmux_cfg_reg अणु
	u32 reg;
	u8 reg_width, field_width;
#अगर_घोषित DEBUG
	u16 nr_क्रमागत_ids;	/* क्रम variable width regs only */
#घोषणा SET_NR_ENUM_IDS(n)	.nr_क्रमागत_ids = n,
#अन्यथा
#घोषणा SET_NR_ENUM_IDS(n)
#पूर्ण_अगर
	स्थिर u16 *क्रमागत_ids;
	स्थिर u8 *var_field_width;
पूर्ण;

#घोषणा GROUP(...)	__VA_ARGS__

/*
 * Describe a config रेजिस्टर consisting of several fields of the same width
 *   - name: Register name (unused, क्रम करोcumentation purposes only)
 *   - r: Physical रेजिस्टर address
 *   - r_width: Width of the रेजिस्टर (in bits)
 *   - f_width: Width of the fixed-width रेजिस्टर fields (in bits)
 *   - ids: For each रेजिस्टर field (from left to right, i.e. MSB to LSB),
 *          2^f_width क्रमागत IDs must be specअगरied, one क्रम each possible
 *          combination of the रेजिस्टर field bit values, all wrapped using
 *          the GROUP() macro.
 */
#घोषणा PINMUX_CFG_REG(name, r, r_width, f_width, ids)			\
	.reg = r, .reg_width = r_width,					\
	.field_width = f_width + BUILD_BUG_ON_ZERO(r_width % f_width) +	\
	BUILD_BUG_ON_ZERO(माप((स्थिर u16 []) अणु ids पूर्ण) / माप(u16) != \
			  (r_width / f_width) * (1 << f_width)),	\
	.क्रमागत_ids = (स्थिर u16 [(r_width / f_width) * (1 << f_width)])	\
		अणु ids पूर्ण

/*
 * Describe a config रेजिस्टर consisting of several fields of dअगरferent widths
 *   - name: Register name (unused, क्रम करोcumentation purposes only)
 *   - r: Physical रेजिस्टर address
 *   - r_width: Width of the रेजिस्टर (in bits)
 *   - f_widths: List of widths of the रेजिस्टर fields (in bits), from left
 *               to right (i.e. MSB to LSB), wrapped using the GROUP() macro.
 *   - ids: For each रेजिस्टर field (from left to right, i.e. MSB to LSB),
 *          2^f_widths[i] क्रमागत IDs must be specअगरied, one क्रम each possible
 *          combination of the रेजिस्टर field bit values, all wrapped using
 *          the GROUP() macro.
 */
#घोषणा PINMUX_CFG_REG_VAR(name, r, r_width, f_widths, ids)		\
	.reg = r, .reg_width = r_width,					\
	.var_field_width = (स्थिर u8 []) अणु f_widths, 0 पूर्ण,		\
	SET_NR_ENUM_IDS(माप((स्थिर u16 []) अणु ids पूर्ण) / माप(u16))	\
	.क्रमागत_ids = (स्थिर u16 []) अणु ids पूर्ण

काष्ठा pinmux_drive_reg_field अणु
	u16 pin;
	u8 offset;
	u8 size;
पूर्ण;

काष्ठा pinmux_drive_reg अणु
	u32 reg;
	स्थिर काष्ठा pinmux_drive_reg_field fields[8];
पूर्ण;

#घोषणा PINMUX_DRIVE_REG(name, r) \
	.reg = r, \
	.fields =

काष्ठा pinmux_bias_reg अणु	/* At least one of puen/pud must exist */
	u32 puen;		/* Pull-enable or pull-up control रेजिस्टर */
	u32 pud;		/* Pull-up/करोwn or pull-करोwn control रेजिस्टर */
	स्थिर u16 pins[32];
पूर्ण;

#घोषणा PINMUX_BIAS_REG(name1, r1, name2, r2) \
	.puen = r1,	\
	.pud = r2,	\
	.pins =

काष्ठा pinmux_ioctrl_reg अणु
	u32 reg;
पूर्ण;

काष्ठा pinmux_data_reg अणु
	u32 reg;
	u8 reg_width;
	स्थिर u16 *क्रमागत_ids;
पूर्ण;

/*
 * Describe a data रेजिस्टर
 *   - name: Register name (unused, क्रम करोcumentation purposes only)
 *   - r: Physical रेजिस्टर address
 *   - r_width: Width of the रेजिस्टर (in bits)
 *   - ids: For each रेजिस्टर bit (from left to right, i.e. MSB to LSB), one
 *          क्रमागत ID must be specअगरied, all wrapped using the GROUP() macro.
 */
#घोषणा PINMUX_DATA_REG(name, r, r_width, ids)				\
	.reg = r, .reg_width = r_width +				\
	BUILD_BUG_ON_ZERO(माप((स्थिर u16 []) अणु ids पूर्ण) / माप(u16) != \
			  r_width),					\
	.क्रमागत_ids = (स्थिर u16 [r_width]) अणु ids पूर्ण

काष्ठा pinmux_irq अणु
	स्थिर लघु *gpios;
पूर्ण;

/*
 * Describe the mapping from GPIOs to a single IRQ
 *   - ids...: List of GPIOs that are mapped to the same IRQ
 */
#घोषणा PINMUX_IRQ(ids...)			   \
	अणु .gpios = (स्थिर लघु []) अणु ids, -1 पूर्ण पूर्ण

काष्ठा pinmux_range अणु
	u16 begin;
	u16 end;
	u16 क्रमce;
पूर्ण;

काष्ठा sh_pfc_winकरोw अणु
	phys_addr_t phys;
	व्योम __iomem *virt;
	अचिन्हित दीर्घ size;
पूर्ण;

काष्ठा sh_pfc_pin_range;

काष्ठा sh_pfc अणु
	काष्ठा device *dev;
	स्थिर काष्ठा sh_pfc_soc_info *info;
	spinlock_t lock;

	अचिन्हित पूर्णांक num_winकरोws;
	काष्ठा sh_pfc_winकरोw *winकरोws;
	अचिन्हित पूर्णांक num_irqs;
	अचिन्हित पूर्णांक *irqs;

	काष्ठा sh_pfc_pin_range *ranges;
	अचिन्हित पूर्णांक nr_ranges;

	अचिन्हित पूर्णांक nr_gpio_pins;

	काष्ठा sh_pfc_chip *gpio;
	u32 *saved_regs;
पूर्ण;

काष्ठा sh_pfc_soc_operations अणु
	पूर्णांक (*init)(काष्ठा sh_pfc *pfc);
	अचिन्हित पूर्णांक (*get_bias)(काष्ठा sh_pfc *pfc, अचिन्हित पूर्णांक pin);
	व्योम (*set_bias)(काष्ठा sh_pfc *pfc, अचिन्हित पूर्णांक pin,
			 अचिन्हित पूर्णांक bias);
	पूर्णांक (*pin_to_pocctrl)(काष्ठा sh_pfc *pfc, अचिन्हित पूर्णांक pin, u32 *pocctrl);
	व्योम __iomem * (*pin_to_portcr)(काष्ठा sh_pfc *pfc, अचिन्हित पूर्णांक pin);
पूर्ण;

काष्ठा sh_pfc_soc_info अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा sh_pfc_soc_operations *ops;

#अगर_घोषित CONFIG_PINCTRL_SH_PFC_GPIO
	काष्ठा pinmux_range input;
	काष्ठा pinmux_range output;
	स्थिर काष्ठा pinmux_irq *gpio_irq;
	अचिन्हित पूर्णांक gpio_irq_size;
#पूर्ण_अगर

	काष्ठा pinmux_range function;

	स्थिर काष्ठा sh_pfc_pin *pins;
	अचिन्हित पूर्णांक nr_pins;
	स्थिर काष्ठा sh_pfc_pin_group *groups;
	अचिन्हित पूर्णांक nr_groups;
	स्थिर काष्ठा sh_pfc_function *functions;
	अचिन्हित पूर्णांक nr_functions;

#अगर_घोषित CONFIG_PINCTRL_SH_FUNC_GPIO
	स्थिर काष्ठा pinmux_func *func_gpios;
	अचिन्हित पूर्णांक nr_func_gpios;
#पूर्ण_अगर

	स्थिर काष्ठा pinmux_cfg_reg *cfg_regs;
	स्थिर काष्ठा pinmux_drive_reg *drive_regs;
	स्थिर काष्ठा pinmux_bias_reg *bias_regs;
	स्थिर काष्ठा pinmux_ioctrl_reg *ioctrl_regs;
	स्थिर काष्ठा pinmux_data_reg *data_regs;

	स्थिर u16 *pinmux_data;
	अचिन्हित पूर्णांक pinmux_data_size;

	u32 unlock_reg;		/* can be literal address or mask */
पूर्ण;

बाह्य स्थिर काष्ठा sh_pfc_soc_info emev2_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info r8a73a4_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info r8a7740_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info r8a7742_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info r8a7743_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info r8a7744_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info r8a7745_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info r8a77470_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info r8a774a1_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info r8a774b1_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info r8a774c0_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info r8a774e1_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info r8a7778_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info r8a7779_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info r8a7790_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info r8a7791_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info r8a7792_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info r8a7793_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info r8a7794_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info r8a77950_pinmux_info __weak;
बाह्य स्थिर काष्ठा sh_pfc_soc_info r8a77951_pinmux_info __weak;
बाह्य स्थिर काष्ठा sh_pfc_soc_info r8a77960_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info r8a77961_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info r8a77965_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info r8a77970_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info r8a77980_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info r8a77990_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info r8a77995_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info r8a779a0_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info sh7203_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info sh7264_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info sh7269_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info sh73a0_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info sh7720_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info sh7722_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info sh7723_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info sh7724_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info sh7734_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info sh7757_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info sh7785_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info sh7786_pinmux_info;
बाह्य स्थिर काष्ठा sh_pfc_soc_info shx3_pinmux_info;

/* -----------------------------------------------------------------------------
 * Helper macros to create pin and port lists
 */

/*
 * sh_pfc_soc_info pinmux_data array macros
 */

/*
 * Describe generic pinmux data
 *   - data_or_mark: *_DATA or *_MARK क्रमागत ID
 *   - ids...: List of क्रमागत IDs to associate with data_or_mark
 */
#घोषणा PINMUX_DATA(data_or_mark, ids...)	data_or_mark, ids, 0

/*
 * Describe a pinmux configuration without GPIO function that needs
 * configuration in a Peripheral Function Select Register (IPSR)
 *   - ipsr: IPSR field (unused, क्रम करोcumentation purposes only)
 *   - fn: Function name, referring to a field in the IPSR
 */
#घोषणा PINMUX_IPSR_NOGP(ipsr, fn)					\
	PINMUX_DATA(fn##_MARK, FN_##fn)

/*
 * Describe a pinmux configuration with GPIO function that needs configuration
 * in both a Peripheral Function Select Register (IPSR) and in a
 * GPIO/Peripheral Function Select Register (GPSR)
 *   - ipsr: IPSR field
 *   - fn: Function name, also referring to the IPSR field
 */
#घोषणा PINMUX_IPSR_GPSR(ipsr, fn)					\
	PINMUX_DATA(fn##_MARK, FN_##fn, FN_##ipsr)

/*
 * Describe a pinmux configuration without GPIO function that needs
 * configuration in a Peripheral Function Select Register (IPSR), and where the
 * pinmux function has a representation in a Module Select Register (MOD_SEL).
 *   - ipsr: IPSR field (unused, क्रम करोcumentation purposes only)
 *   - fn: Function name, also referring to the IPSR field
 *   - msel: Module selector
 */
#घोषणा PINMUX_IPSR_NOGM(ipsr, fn, msel)				\
	PINMUX_DATA(fn##_MARK, FN_##fn, FN_##msel)

/*
 * Describe a pinmux configuration with GPIO function where the pinmux function
 * has no representation in a Peripheral Function Select Register (IPSR), but
 * instead solely depends on a group selection.
 *   - gpsr: GPSR field
 *   - fn: Function name, also referring to the GPSR field
 *   - gsel: Group selector
 */
#घोषणा PINMUX_IPSR_NOFN(gpsr, fn, gsel)				\
	PINMUX_DATA(fn##_MARK, FN_##gpsr, FN_##gsel)

/*
 * Describe a pinmux configuration with GPIO function that needs configuration
 * in both a Peripheral Function Select Register (IPSR) and a GPIO/Peripheral
 * Function Select Register (GPSR), and where the pinmux function has a
 * representation in a Module Select Register (MOD_SEL).
 *   - ipsr: IPSR field
 *   - fn: Function name, also referring to the IPSR field
 *   - msel: Module selector
 */
#घोषणा PINMUX_IPSR_MSEL(ipsr, fn, msel)				\
	PINMUX_DATA(fn##_MARK, FN_##msel, FN_##fn, FN_##ipsr)

/*
 * Describe a pinmux configuration similar to PINMUX_IPSR_MSEL, but with
 * an additional select रेजिस्टर that controls physical multiplexing
 * with another pin.
 *   - ipsr: IPSR field
 *   - fn: Function name, also referring to the IPSR field
 *   - psel: Physical multiplexing selector
 *   - msel: Module selector
 */
#घोषणा PINMUX_IPSR_PHYS_MSEL(ipsr, fn, psel, msel) \
	PINMUX_DATA(fn##_MARK, FN_##psel, FN_##msel, FN_##fn, FN_##ipsr)

/*
 * Describe a pinmux configuration in which a pin is physically multiplexed
 * with other pins.
 *   - ipsr: IPSR field
 *   - fn: Function name
 *   - psel: Physical multiplexing selector
 */
#घोषणा PINMUX_IPSR_PHYS(ipsr, fn, psel) \
	PINMUX_DATA(fn##_MARK, FN_##psel, FN_##ipsr)

/*
 * Describe a pinmux configuration क्रम a single-function pin with GPIO
 * capability.
 *   - fn: Function name
 */
#घोषणा PINMUX_SINGLE(fn)						\
	PINMUX_DATA(fn##_MARK, FN_##fn)

/*
 * GP port style (32 ports banks)
 */

#घोषणा PORT_GP_CFG_1(bank, pin, fn, sfx, cfg)				\
	fn(bank, pin, GP_##bank##_##pin, sfx, cfg)
#घोषणा PORT_GP_1(bank, pin, fn, sfx)	PORT_GP_CFG_1(bank, pin, fn, sfx, 0)

#घोषणा PORT_GP_CFG_2(bank, fn, sfx, cfg)				\
	PORT_GP_CFG_1(bank, 0,  fn, sfx, cfg),				\
	PORT_GP_CFG_1(bank, 1,  fn, sfx, cfg)
#घोषणा PORT_GP_2(bank, fn, sfx)	PORT_GP_CFG_2(bank, fn, sfx, 0)

#घोषणा PORT_GP_CFG_4(bank, fn, sfx, cfg)				\
	PORT_GP_CFG_2(bank, fn, sfx, cfg),				\
	PORT_GP_CFG_1(bank, 2,  fn, sfx, cfg),				\
	PORT_GP_CFG_1(bank, 3,  fn, sfx, cfg)
#घोषणा PORT_GP_4(bank, fn, sfx)	PORT_GP_CFG_4(bank, fn, sfx, 0)

#घोषणा PORT_GP_CFG_6(bank, fn, sfx, cfg)				\
	PORT_GP_CFG_4(bank, fn, sfx, cfg),				\
	PORT_GP_CFG_1(bank, 4,  fn, sfx, cfg),				\
	PORT_GP_CFG_1(bank, 5,  fn, sfx, cfg)
#घोषणा PORT_GP_6(bank, fn, sfx)	PORT_GP_CFG_6(bank, fn, sfx, 0)

#घोषणा PORT_GP_CFG_7(bank, fn, sfx, cfg)				\
	PORT_GP_CFG_6(bank, fn, sfx, cfg),				\
	PORT_GP_CFG_1(bank, 6,  fn, sfx, cfg)
#घोषणा PORT_GP_7(bank, fn, sfx)	PORT_GP_CFG_7(bank, fn, sfx, 0)

#घोषणा PORT_GP_CFG_8(bank, fn, sfx, cfg)				\
	PORT_GP_CFG_7(bank, fn, sfx, cfg),				\
	PORT_GP_CFG_1(bank, 7,  fn, sfx, cfg)
#घोषणा PORT_GP_8(bank, fn, sfx)	PORT_GP_CFG_8(bank, fn, sfx, 0)

#घोषणा PORT_GP_CFG_9(bank, fn, sfx, cfg)				\
	PORT_GP_CFG_8(bank, fn, sfx, cfg),				\
	PORT_GP_CFG_1(bank, 8,  fn, sfx, cfg)
#घोषणा PORT_GP_9(bank, fn, sfx)	PORT_GP_CFG_9(bank, fn, sfx, 0)

#घोषणा PORT_GP_CFG_10(bank, fn, sfx, cfg)				\
	PORT_GP_CFG_9(bank, fn, sfx, cfg),				\
	PORT_GP_CFG_1(bank, 9,  fn, sfx, cfg)
#घोषणा PORT_GP_10(bank, fn, sfx)	PORT_GP_CFG_10(bank, fn, sfx, 0)

#घोषणा PORT_GP_CFG_11(bank, fn, sfx, cfg)				\
	PORT_GP_CFG_10(bank, fn, sfx, cfg),				\
	PORT_GP_CFG_1(bank, 10, fn, sfx, cfg)
#घोषणा PORT_GP_11(bank, fn, sfx)	PORT_GP_CFG_11(bank, fn, sfx, 0)

#घोषणा PORT_GP_CFG_12(bank, fn, sfx, cfg)				\
	PORT_GP_CFG_11(bank, fn, sfx, cfg),				\
	PORT_GP_CFG_1(bank, 11, fn, sfx, cfg)
#घोषणा PORT_GP_12(bank, fn, sfx)	PORT_GP_CFG_12(bank, fn, sfx, 0)

#घोषणा PORT_GP_CFG_14(bank, fn, sfx, cfg)				\
	PORT_GP_CFG_12(bank, fn, sfx, cfg),				\
	PORT_GP_CFG_1(bank, 12, fn, sfx, cfg),				\
	PORT_GP_CFG_1(bank, 13, fn, sfx, cfg)
#घोषणा PORT_GP_14(bank, fn, sfx)	PORT_GP_CFG_14(bank, fn, sfx, 0)

#घोषणा PORT_GP_CFG_15(bank, fn, sfx, cfg)				\
	PORT_GP_CFG_14(bank, fn, sfx, cfg),				\
	PORT_GP_CFG_1(bank, 14, fn, sfx, cfg)
#घोषणा PORT_GP_15(bank, fn, sfx)	PORT_GP_CFG_15(bank, fn, sfx, 0)

#घोषणा PORT_GP_CFG_16(bank, fn, sfx, cfg)				\
	PORT_GP_CFG_15(bank, fn, sfx, cfg),				\
	PORT_GP_CFG_1(bank, 15, fn, sfx, cfg)
#घोषणा PORT_GP_16(bank, fn, sfx)	PORT_GP_CFG_16(bank, fn, sfx, 0)

#घोषणा PORT_GP_CFG_17(bank, fn, sfx, cfg)				\
	PORT_GP_CFG_16(bank, fn, sfx, cfg),				\
	PORT_GP_CFG_1(bank, 16, fn, sfx, cfg)
#घोषणा PORT_GP_17(bank, fn, sfx)	PORT_GP_CFG_17(bank, fn, sfx, 0)

#घोषणा PORT_GP_CFG_18(bank, fn, sfx, cfg)				\
	PORT_GP_CFG_17(bank, fn, sfx, cfg),				\
	PORT_GP_CFG_1(bank, 17, fn, sfx, cfg)
#घोषणा PORT_GP_18(bank, fn, sfx)	PORT_GP_CFG_18(bank, fn, sfx, 0)

#घोषणा PORT_GP_CFG_20(bank, fn, sfx, cfg)				\
	PORT_GP_CFG_18(bank, fn, sfx, cfg),				\
	PORT_GP_CFG_1(bank, 18, fn, sfx, cfg),				\
	PORT_GP_CFG_1(bank, 19, fn, sfx, cfg)
#घोषणा PORT_GP_20(bank, fn, sfx)	PORT_GP_CFG_20(bank, fn, sfx, 0)

#घोषणा PORT_GP_CFG_21(bank, fn, sfx, cfg)				\
	PORT_GP_CFG_20(bank, fn, sfx, cfg),				\
	PORT_GP_CFG_1(bank, 20, fn, sfx, cfg)
#घोषणा PORT_GP_21(bank, fn, sfx)	PORT_GP_CFG_21(bank, fn, sfx, 0)

#घोषणा PORT_GP_CFG_22(bank, fn, sfx, cfg)				\
	PORT_GP_CFG_21(bank, fn, sfx, cfg),				\
	PORT_GP_CFG_1(bank, 21, fn, sfx, cfg)
#घोषणा PORT_GP_22(bank, fn, sfx)	PORT_GP_CFG_22(bank, fn, sfx, 0)

#घोषणा PORT_GP_CFG_23(bank, fn, sfx, cfg)				\
	PORT_GP_CFG_22(bank, fn, sfx, cfg),				\
	PORT_GP_CFG_1(bank, 22, fn, sfx, cfg)
#घोषणा PORT_GP_23(bank, fn, sfx)	PORT_GP_CFG_23(bank, fn, sfx, 0)

#घोषणा PORT_GP_CFG_24(bank, fn, sfx, cfg)				\
	PORT_GP_CFG_23(bank, fn, sfx, cfg),				\
	PORT_GP_CFG_1(bank, 23, fn, sfx, cfg)
#घोषणा PORT_GP_24(bank, fn, sfx)	PORT_GP_CFG_24(bank, fn, sfx, 0)

#घोषणा PORT_GP_CFG_25(bank, fn, sfx, cfg)				\
	PORT_GP_CFG_24(bank, fn, sfx, cfg),				\
	PORT_GP_CFG_1(bank, 24, fn, sfx, cfg)
#घोषणा PORT_GP_25(bank, fn, sfx)	PORT_GP_CFG_25(bank, fn, sfx, 0)

#घोषणा PORT_GP_CFG_26(bank, fn, sfx, cfg)				\
	PORT_GP_CFG_25(bank, fn, sfx, cfg),				\
	PORT_GP_CFG_1(bank, 25, fn, sfx, cfg)
#घोषणा PORT_GP_26(bank, fn, sfx)	PORT_GP_CFG_26(bank, fn, sfx, 0)

#घोषणा PORT_GP_CFG_27(bank, fn, sfx, cfg)				\
	PORT_GP_CFG_26(bank, fn, sfx, cfg),				\
	PORT_GP_CFG_1(bank, 26, fn, sfx, cfg)
#घोषणा PORT_GP_27(bank, fn, sfx)	PORT_GP_CFG_27(bank, fn, sfx, 0)

#घोषणा PORT_GP_CFG_28(bank, fn, sfx, cfg)				\
	PORT_GP_CFG_27(bank, fn, sfx, cfg),				\
	PORT_GP_CFG_1(bank, 27, fn, sfx, cfg)
#घोषणा PORT_GP_28(bank, fn, sfx)	PORT_GP_CFG_28(bank, fn, sfx, 0)

#घोषणा PORT_GP_CFG_29(bank, fn, sfx, cfg)				\
	PORT_GP_CFG_28(bank, fn, sfx, cfg),				\
	PORT_GP_CFG_1(bank, 28, fn, sfx, cfg)
#घोषणा PORT_GP_29(bank, fn, sfx)	PORT_GP_CFG_29(bank, fn, sfx, 0)

#घोषणा PORT_GP_CFG_30(bank, fn, sfx, cfg)				\
	PORT_GP_CFG_29(bank, fn, sfx, cfg),				\
	PORT_GP_CFG_1(bank, 29, fn, sfx, cfg)
#घोषणा PORT_GP_30(bank, fn, sfx)	PORT_GP_CFG_30(bank, fn, sfx, 0)

#घोषणा PORT_GP_CFG_31(bank, fn, sfx, cfg)				\
	PORT_GP_CFG_30(bank, fn, sfx, cfg),				\
	PORT_GP_CFG_1(bank, 30, fn, sfx, cfg)
#घोषणा PORT_GP_31(bank, fn, sfx)	PORT_GP_CFG_31(bank, fn, sfx, 0)

#घोषणा PORT_GP_CFG_32(bank, fn, sfx, cfg)				\
	PORT_GP_CFG_31(bank, fn, sfx, cfg),				\
	PORT_GP_CFG_1(bank, 31, fn, sfx, cfg)
#घोषणा PORT_GP_32(bank, fn, sfx)	PORT_GP_CFG_32(bank, fn, sfx, 0)

#घोषणा PORT_GP_32_REV(bank, fn, sfx)					\
	PORT_GP_1(bank, 31, fn, sfx), PORT_GP_1(bank, 30, fn, sfx),	\
	PORT_GP_1(bank, 29, fn, sfx), PORT_GP_1(bank, 28, fn, sfx),	\
	PORT_GP_1(bank, 27, fn, sfx), PORT_GP_1(bank, 26, fn, sfx),	\
	PORT_GP_1(bank, 25, fn, sfx), PORT_GP_1(bank, 24, fn, sfx),	\
	PORT_GP_1(bank, 23, fn, sfx), PORT_GP_1(bank, 22, fn, sfx),	\
	PORT_GP_1(bank, 21, fn, sfx), PORT_GP_1(bank, 20, fn, sfx),	\
	PORT_GP_1(bank, 19, fn, sfx), PORT_GP_1(bank, 18, fn, sfx),	\
	PORT_GP_1(bank, 17, fn, sfx), PORT_GP_1(bank, 16, fn, sfx),	\
	PORT_GP_1(bank, 15, fn, sfx), PORT_GP_1(bank, 14, fn, sfx),	\
	PORT_GP_1(bank, 13, fn, sfx), PORT_GP_1(bank, 12, fn, sfx),	\
	PORT_GP_1(bank, 11, fn, sfx), PORT_GP_1(bank, 10, fn, sfx),	\
	PORT_GP_1(bank, 9,  fn, sfx), PORT_GP_1(bank, 8,  fn, sfx),	\
	PORT_GP_1(bank, 7,  fn, sfx), PORT_GP_1(bank, 6,  fn, sfx),	\
	PORT_GP_1(bank, 5,  fn, sfx), PORT_GP_1(bank, 4,  fn, sfx),	\
	PORT_GP_1(bank, 3,  fn, sfx), PORT_GP_1(bank, 2,  fn, sfx),	\
	PORT_GP_1(bank, 1,  fn, sfx), PORT_GP_1(bank, 0,  fn, sfx)

/* GP_ALL(suffix) - Expand to a list of GP_#_#_suffix */
#घोषणा _GP_ALL(bank, pin, name, sfx, cfg)	name##_##sfx
#घोषणा GP_ALL(str)			CPU_ALL_GP(_GP_ALL, str)

/* PINMUX_GPIO_GP_ALL - Expand to a list of sh_pfc_pin entries */
#घोषणा _GP_GPIO(bank, _pin, _name, sfx, cfg)				\
	अणु								\
		.pin = (bank * 32) + _pin,				\
		.name = __stringअगरy(_name),				\
		.क्रमागत_id = _name##_DATA,				\
		.configs = cfg,						\
	पूर्ण
#घोषणा PINMUX_GPIO_GP_ALL()		CPU_ALL_GP(_GP_GPIO, unused)

/* PINMUX_DATA_GP_ALL -  Expand to a list of name_DATA, name_FN marks */
#घोषणा _GP_DATA(bank, pin, name, sfx, cfg)	PINMUX_DATA(name##_DATA, name##_FN)
#घोषणा PINMUX_DATA_GP_ALL()		CPU_ALL_GP(_GP_DATA, unused)

/*
 * GP_ASSIGN_LAST() - Expand to an क्रमागत definition क्रम the last GP pin
 *
 * The largest GP pin index is obtained by taking the size of a जोड़,
 * containing one array per GP pin, sized by the corresponding pin index.
 * As the fields in the CPU_ALL_GP() macro definition are separated by commas,
 * जबतक the members of a जोड़ must be terminated by semicolons, the commas
 * are असलorbed by wrapping them inside dummy attributes.
 */
#घोषणा _GP_ENTRY(bank, pin, name, sfx, cfg)				\
	deprecated)); अक्षर name[(bank * 32) + pin] __attribute__((deprecated
#घोषणा GP_ASSIGN_LAST()						\
	GP_LAST = माप(जोड़ अणु					\
		अक्षर dummy[0] __attribute__((deprecated,		\
		CPU_ALL_GP(_GP_ENTRY, unused),				\
		deprecated));						\
	पूर्ण)

/*
 * PORT style (linear pin space)
 */

#घोषणा PORT_1(pn, fn, pfx, sfx) fn(pn, pfx, sfx)

#घोषणा PORT_10(pn, fn, pfx, sfx)					  \
	PORT_1(pn,   fn, pfx##0, sfx), PORT_1(pn+1, fn, pfx##1, sfx),	  \
	PORT_1(pn+2, fn, pfx##2, sfx), PORT_1(pn+3, fn, pfx##3, sfx),	  \
	PORT_1(pn+4, fn, pfx##4, sfx), PORT_1(pn+5, fn, pfx##5, sfx),	  \
	PORT_1(pn+6, fn, pfx##6, sfx), PORT_1(pn+7, fn, pfx##7, sfx),	  \
	PORT_1(pn+8, fn, pfx##8, sfx), PORT_1(pn+9, fn, pfx##9, sfx)

#घोषणा PORT_90(pn, fn, pfx, sfx)					  \
	PORT_10(pn+10, fn, pfx##1, sfx), PORT_10(pn+20, fn, pfx##2, sfx), \
	PORT_10(pn+30, fn, pfx##3, sfx), PORT_10(pn+40, fn, pfx##4, sfx), \
	PORT_10(pn+50, fn, pfx##5, sfx), PORT_10(pn+60, fn, pfx##6, sfx), \
	PORT_10(pn+70, fn, pfx##7, sfx), PORT_10(pn+80, fn, pfx##8, sfx), \
	PORT_10(pn+90, fn, pfx##9, sfx)

/* PORT_ALL(suffix) - Expand to a list of PORT_#_suffix */
#घोषणा _PORT_ALL(pn, pfx, sfx)		pfx##_##sfx
#घोषणा PORT_ALL(str)			CPU_ALL_PORT(_PORT_ALL, PORT, str)

/* PINMUX_GPIO - Expand to a sh_pfc_pin entry */
#घोषणा PINMUX_GPIO(_pin)						\
	[GPIO_##_pin] = अणु						\
		.pin = (u16)-1,						\
		.name = __stringअगरy(GPIO_##_pin),			\
		.क्रमागत_id = _pin##_DATA,					\
	पूर्ण

/* SH_PFC_PIN_CFG - Expand to a sh_pfc_pin entry (named PORT#) with config */
#घोषणा SH_PFC_PIN_CFG(_pin, cfgs)					\
	अणु								\
		.pin = _pin,						\
		.name = __stringअगरy(PORT##_pin),			\
		.क्रमागत_id = PORT##_pin##_DATA,				\
		.configs = cfgs,					\
	पूर्ण

/* PINMUX_DATA_ALL - Expand to a list of PORT_name_DATA, PORT_name_FN0,
 *		     PORT_name_OUT, PORT_name_IN marks
 */
#घोषणा _PORT_DATA(pn, pfx, sfx)					\
	PINMUX_DATA(PORT##pfx##_DATA, PORT##pfx##_FN0,			\
		    PORT##pfx##_OUT, PORT##pfx##_IN)
#घोषणा PINMUX_DATA_ALL()		CPU_ALL_PORT(_PORT_DATA, , unused)

/*
 * PORT_ASSIGN_LAST() - Expand to an क्रमागत definition क्रम the last PORT pin
 *
 * The largest PORT pin index is obtained by taking the size of a जोड़,
 * containing one array per PORT pin, sized by the corresponding pin index.
 * As the fields in the CPU_ALL_PORT() macro definition are separated by
 * commas, जबतक the members of a जोड़ must be terminated by semicolons, the
 * commas are असलorbed by wrapping them inside dummy attributes.
 */
#घोषणा _PORT_ENTRY(pn, pfx, sfx)					\
	deprecated)); अक्षर pfx[pn] __attribute__((deprecated
#घोषणा PORT_ASSIGN_LAST()						\
	PORT_LAST = माप(जोड़ अणु					\
		अक्षर dummy[0] __attribute__((deprecated,		\
		CPU_ALL_PORT(_PORT_ENTRY, PORT, unused),		\
		deprecated));						\
	पूर्ण)

/* GPIO_FN(name) - Expand to a sh_pfc_pin entry क्रम a function GPIO */
#घोषणा PINMUX_GPIO_FN(gpio, base, data_or_mark)			\
	[gpio - (base)] = अणु						\
		.name = __stringअगरy(gpio),				\
		.क्रमागत_id = data_or_mark,				\
	पूर्ण
#घोषणा GPIO_FN(str)							\
	PINMUX_GPIO_FN(GPIO_FN_##str, PINMUX_FN_BASE, str##_MARK)

/*
 * Pins not associated with a GPIO port
 */

#घोषणा PIN_NOGP_CFG(pin, name, fn, cfg)	fn(pin, name, cfg)
#घोषणा PIN_NOGP(pin, name, fn)			fn(pin, name, 0)

/* NOGP_ALL - Expand to a list of PIN_id */
#घोषणा _NOGP_ALL(pin, name, cfg)		PIN_##pin
#घोषणा NOGP_ALL()				CPU_ALL_NOGP(_NOGP_ALL)

/* PINMUX_NOGP_ALL - Expand to a list of sh_pfc_pin entries */
#घोषणा _NOGP_PINMUX(_pin, _name, cfg)					\
	अणु								\
		.pin = PIN_##_pin,					\
		.name = "PIN_" _name,					\
		.configs = SH_PFC_PIN_CFG_NO_GPIO | cfg,		\
	पूर्ण
#घोषणा PINMUX_NOGP_ALL()		CPU_ALL_NOGP(_NOGP_PINMUX)

/*
 * PORTnCR helper macro क्रम SH-Mobile/R-Mobile
 */
#घोषणा PORTCR(nr, reg)							\
	अणु								\
		PINMUX_CFG_REG_VAR("PORT" nr "CR", reg, 8,		\
				   GROUP(2, 2, 1, 3),			\
				   GROUP(				\
			/* PULMD[1:0], handled by .set_bias() */	\
			0, 0, 0, 0,					\
			/* IE and OE */					\
			0, PORT##nr##_OUT, PORT##nr##_IN, 0,		\
			/* SEC, not supported */			\
			0, 0,						\
			/* PTMD[2:0] */					\
			PORT##nr##_FN0, PORT##nr##_FN1,			\
			PORT##nr##_FN2, PORT##nr##_FN3,			\
			PORT##nr##_FN4, PORT##nr##_FN5,			\
			PORT##nr##_FN6, PORT##nr##_FN7			\
		))							\
	पूर्ण

/*
 * GPIO number helper macro क्रम R-Car
 */
#घोषणा RCAR_GP_PIN(bank, pin)		(((bank) * 32) + (pin))

/*
 * Bias helpers
 */
अचिन्हित पूर्णांक rcar_pinmux_get_bias(काष्ठा sh_pfc *pfc, अचिन्हित पूर्णांक pin);
व्योम rcar_pinmux_set_bias(काष्ठा sh_pfc *pfc, अचिन्हित पूर्णांक pin,
			  अचिन्हित पूर्णांक bias);

अचिन्हित पूर्णांक rmobile_pinmux_get_bias(काष्ठा sh_pfc *pfc, अचिन्हित पूर्णांक pin);
व्योम rmobile_pinmux_set_bias(काष्ठा sh_pfc *pfc, अचिन्हित पूर्णांक pin,
			     अचिन्हित पूर्णांक bias);

#पूर्ण_अगर /* __SH_PFC_H */
