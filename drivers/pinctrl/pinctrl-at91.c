<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * at91 pinctrl driver based on at91 pinmux core
 *
 * Copyright (C) 2011-2012 Jean-Christophe PLAGNIOL-VILLARD <plagnioj@jcrosoft.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/pinctrl/machine.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
/* Since we request GPIOs from ourself */
#समावेश <linux/pinctrl/consumer.h>

#समावेश <soc/at91/pm.h>

#समावेश "pinctrl-at91.h"
#समावेश "core.h"

#घोषणा MAX_GPIO_BANKS		5
#घोषणा MAX_NB_GPIO_PER_BANK	32

काष्ठा at91_pinctrl_mux_ops;

काष्ठा at91_gpio_chip अणु
	काष्ठा gpio_chip	chip;
	काष्ठा pinctrl_gpio_range range;
	काष्ठा at91_gpio_chip	*next;		/* Bank sharing same घड़ी */
	पूर्णांक			pioc_hwirq;	/* PIO bank पूर्णांकerrupt identअगरier on AIC */
	पूर्णांक			pioc_virq;	/* PIO bank Linux भव पूर्णांकerrupt */
	पूर्णांक			pioc_idx;	/* PIO bank index */
	व्योम __iomem		*regbase;	/* PIO bank भव address */
	काष्ठा clk		*घड़ी;		/* associated घड़ी */
	काष्ठा at91_pinctrl_mux_ops *ops;	/* ops */
पूर्ण;

अटल काष्ठा at91_gpio_chip *gpio_chips[MAX_GPIO_BANKS];

अटल पूर्णांक gpio_banks;

#घोषणा PULL_UP		(1 << 0)
#घोषणा MULTI_DRIVE	(1 << 1)
#घोषणा DEGLITCH	(1 << 2)
#घोषणा PULL_DOWN	(1 << 3)
#घोषणा DIS_SCHMIT	(1 << 4)
#घोषणा DRIVE_STRENGTH_SHIFT	5
#घोषणा DRIVE_STRENGTH_MASK		0x3
#घोषणा DRIVE_STRENGTH   (DRIVE_STRENGTH_MASK << DRIVE_STRENGTH_SHIFT)
#घोषणा OUTPUT		(1 << 7)
#घोषणा OUTPUT_VAL_SHIFT	8
#घोषणा OUTPUT_VAL	(0x1 << OUTPUT_VAL_SHIFT)
#घोषणा SLEWRATE_SHIFT	9
#घोषणा SLEWRATE_MASK	0x1
#घोषणा SLEWRATE	(SLEWRATE_MASK << SLEWRATE_SHIFT)
#घोषणा DEBOUNCE	(1 << 16)
#घोषणा DEBOUNCE_VAL_SHIFT	17
#घोषणा DEBOUNCE_VAL	(0x3fff << DEBOUNCE_VAL_SHIFT)

/*
 * These defines will translated the dt binding settings to our पूर्णांकernal
 * settings. They are not necessarily the same value as the रेजिस्टर setting.
 * The actual drive strength current of low, medium and high must be looked up
 * from the corresponding device datasheet. This value is dअगरferent क्रम pins
 * that are even in the same banks. It is also dependent on VCC.
 * DRIVE_STRENGTH_DEFAULT is just a placeholder to aव्योम changing the drive
 * strength when there is no dt config क्रम it.
 */
क्रमागत drive_strength_bit अणु
	DRIVE_STRENGTH_BIT_DEF,
	DRIVE_STRENGTH_BIT_LOW,
	DRIVE_STRENGTH_BIT_MED,
	DRIVE_STRENGTH_BIT_HI,
पूर्ण;

#घोषणा DRIVE_STRENGTH_BIT_MSK(name)	(DRIVE_STRENGTH_BIT_##name << \
					 DRIVE_STRENGTH_SHIFT)

क्रमागत slewrate_bit अणु
	SLEWRATE_BIT_ENA,
	SLEWRATE_BIT_DIS,
पूर्ण;

#घोषणा SLEWRATE_BIT_MSK(name)		(SLEWRATE_BIT_##name << SLEWRATE_SHIFT)

/**
 * काष्ठा at91_pmx_func - describes AT91 pinmux functions
 * @name: the name of this specअगरic function
 * @groups: corresponding pin groups
 * @ngroups: the number of groups
 */
काष्ठा at91_pmx_func अणु
	स्थिर अक्षर	*name;
	स्थिर अक्षर	**groups;
	अचिन्हित	ngroups;
पूर्ण;

क्रमागत at91_mux अणु
	AT91_MUX_GPIO = 0,
	AT91_MUX_PERIPH_A = 1,
	AT91_MUX_PERIPH_B = 2,
	AT91_MUX_PERIPH_C = 3,
	AT91_MUX_PERIPH_D = 4,
पूर्ण;

/**
 * काष्ठा at91_pmx_pin - describes an At91 pin mux
 * @bank: the bank of the pin
 * @pin: the pin number in the @bank
 * @mux: the mux mode : gpio or periph_x of the pin i.e. alternate function.
 * @conf: the configuration of the pin: PULL_UP, MULTIDRIVE etc...
 */
काष्ठा at91_pmx_pin अणु
	uपूर्णांक32_t	bank;
	uपूर्णांक32_t	pin;
	क्रमागत at91_mux	mux;
	अचिन्हित दीर्घ	conf;
पूर्ण;

/**
 * काष्ठा at91_pin_group - describes an At91 pin group
 * @name: the name of this specअगरic pin group
 * @pins_conf: the mux mode क्रम each pin in this group. The size of this
 *	array is the same as pins.
 * @pins: an array of discrete physical pins used in this group, taken
 *	from the driver-local pin क्रमागतeration space
 * @npins: the number of pins in this group array, i.e. the number of
 *	elements in .pins so we can iterate over that array
 */
काष्ठा at91_pin_group अणु
	स्थिर अक्षर		*name;
	काष्ठा at91_pmx_pin	*pins_conf;
	अचिन्हित पूर्णांक		*pins;
	अचिन्हित		npins;
पूर्ण;

/**
 * काष्ठा at91_pinctrl_mux_ops - describes an AT91 mux ops group
 * on new IP with support क्रम periph C and D the way to mux in
 * periph A and B has changed
 * So provide the right call back
 * अगर not present means the IP करोes not support it
 * @get_periph: वापस the periph mode configured
 * @mux_A_periph: mux as periph A
 * @mux_B_periph: mux as periph B
 * @mux_C_periph: mux as periph C
 * @mux_D_periph: mux as periph D
 * @get_deglitch: get deglitch status
 * @set_deglitch: enable/disable deglitch
 * @get_debounce: get debounce status
 * @set_debounce: enable/disable debounce
 * @get_pullकरोwn: get pullकरोwn status
 * @set_pullकरोwn: enable/disable pullकरोwn
 * @get_schmitt_trig: get schmitt trigger status
 * @disable_schmitt_trig: disable schmitt trigger
 * @get_drivestrength: get driver strength
 * @set_drivestrength: set driver strength
 * @get_slewrate: get slew rate
 * @set_slewrate: set slew rate
 * @irq_type: वापस irq type
 */
काष्ठा at91_pinctrl_mux_ops अणु
	क्रमागत at91_mux (*get_periph)(व्योम __iomem *pio, अचिन्हित mask);
	व्योम (*mux_A_periph)(व्योम __iomem *pio, अचिन्हित mask);
	व्योम (*mux_B_periph)(व्योम __iomem *pio, अचिन्हित mask);
	व्योम (*mux_C_periph)(व्योम __iomem *pio, अचिन्हित mask);
	व्योम (*mux_D_periph)(व्योम __iomem *pio, अचिन्हित mask);
	bool (*get_deglitch)(व्योम __iomem *pio, अचिन्हित pin);
	व्योम (*set_deglitch)(व्योम __iomem *pio, अचिन्हित mask, bool is_on);
	bool (*get_debounce)(व्योम __iomem *pio, अचिन्हित pin, u32 *भाग);
	व्योम (*set_debounce)(व्योम __iomem *pio, अचिन्हित mask, bool is_on, u32 भाग);
	bool (*get_pullकरोwn)(व्योम __iomem *pio, अचिन्हित pin);
	व्योम (*set_pullकरोwn)(व्योम __iomem *pio, अचिन्हित mask, bool is_on);
	bool (*get_schmitt_trig)(व्योम __iomem *pio, अचिन्हित pin);
	व्योम (*disable_schmitt_trig)(व्योम __iomem *pio, अचिन्हित mask);
	अचिन्हित (*get_drivestrength)(व्योम __iomem *pio, अचिन्हित pin);
	व्योम (*set_drivestrength)(व्योम __iomem *pio, अचिन्हित pin,
					u32 strength);
	अचिन्हित (*get_slewrate)(व्योम __iomem *pio, अचिन्हित pin);
	व्योम (*set_slewrate)(व्योम __iomem *pio, अचिन्हित pin, u32 slewrate);
	/* irq */
	पूर्णांक (*irq_type)(काष्ठा irq_data *d, अचिन्हित type);
पूर्ण;

अटल पूर्णांक gpio_irq_type(काष्ठा irq_data *d, अचिन्हित type);
अटल पूर्णांक alt_gpio_irq_type(काष्ठा irq_data *d, अचिन्हित type);

काष्ठा at91_pinctrl अणु
	काष्ठा device		*dev;
	काष्ठा pinctrl_dev	*pctl;

	पूर्णांक			nactive_banks;

	uपूर्णांक32_t		*mux_mask;
	पूर्णांक			nmux;

	काष्ठा at91_pmx_func	*functions;
	पूर्णांक			nfunctions;

	काष्ठा at91_pin_group	*groups;
	पूर्णांक			ngroups;

	काष्ठा at91_pinctrl_mux_ops *ops;
पूर्ण;

अटल अंतरभूत स्थिर काष्ठा at91_pin_group *at91_pinctrl_find_group_by_name(
				स्थिर काष्ठा at91_pinctrl *info,
				स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा at91_pin_group *grp = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < info->ngroups; i++) अणु
		अगर (म_भेद(info->groups[i].name, name))
			जारी;

		grp = &info->groups[i];
		dev_dbg(info->dev, "%s: %d 0:%d\n", name, grp->npins, grp->pins[0]);
		अवरोध;
	पूर्ण

	वापस grp;
पूर्ण

अटल पूर्णांक at91_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा at91_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);

	वापस info->ngroups;
पूर्ण

अटल स्थिर अक्षर *at91_get_group_name(काष्ठा pinctrl_dev *pctldev,
				       अचिन्हित selector)
अणु
	काष्ठा at91_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);

	वापस info->groups[selector].name;
पूर्ण

अटल पूर्णांक at91_get_group_pins(काष्ठा pinctrl_dev *pctldev, अचिन्हित selector,
			       स्थिर अचिन्हित **pins,
			       अचिन्हित *npins)
अणु
	काष्ठा at91_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);

	अगर (selector >= info->ngroups)
		वापस -EINVAL;

	*pins = info->groups[selector].pins;
	*npins = info->groups[selector].npins;

	वापस 0;
पूर्ण

अटल व्योम at91_pin_dbg_show(काष्ठा pinctrl_dev *pctldev, काष्ठा seq_file *s,
		   अचिन्हित offset)
अणु
	seq_म_लिखो(s, "%s", dev_name(pctldev->dev));
पूर्ण

अटल पूर्णांक at91_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
			काष्ठा device_node *np,
			काष्ठा pinctrl_map **map, अचिन्हित *num_maps)
अणु
	काष्ठा at91_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा at91_pin_group *grp;
	काष्ठा pinctrl_map *new_map;
	काष्ठा device_node *parent;
	पूर्णांक map_num = 1;
	पूर्णांक i;

	/*
	 * first find the group of this node and check अगर we need to create
	 * config maps क्रम pins
	 */
	grp = at91_pinctrl_find_group_by_name(info, np->name);
	अगर (!grp) अणु
		dev_err(info->dev, "unable to find group for node %pOFn\n",
			np);
		वापस -EINVAL;
	पूर्ण

	map_num += grp->npins;
	new_map = devm_kसुस्मृति(pctldev->dev, map_num, माप(*new_map),
			       GFP_KERNEL);
	अगर (!new_map)
		वापस -ENOMEM;

	*map = new_map;
	*num_maps = map_num;

	/* create mux map */
	parent = of_get_parent(np);
	अगर (!parent) अणु
		devm_kमुक्त(pctldev->dev, new_map);
		वापस -EINVAL;
	पूर्ण
	new_map[0].type = PIN_MAP_TYPE_MUX_GROUP;
	new_map[0].data.mux.function = parent->name;
	new_map[0].data.mux.group = np->name;
	of_node_put(parent);

	/* create config map */
	new_map++;
	क्रम (i = 0; i < grp->npins; i++) अणु
		new_map[i].type = PIN_MAP_TYPE_CONFIGS_PIN;
		new_map[i].data.configs.group_or_pin =
				pin_get_name(pctldev, grp->pins[i]);
		new_map[i].data.configs.configs = &grp->pins_conf[i].conf;
		new_map[i].data.configs.num_configs = 1;
	पूर्ण

	dev_dbg(pctldev->dev, "maps: function %s group %s num %d\n",
		(*map)->data.mux.function, (*map)->data.mux.group, map_num);

	वापस 0;
पूर्ण

अटल व्योम at91_dt_मुक्त_map(काष्ठा pinctrl_dev *pctldev,
				काष्ठा pinctrl_map *map, अचिन्हित num_maps)
अणु
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops at91_pctrl_ops = अणु
	.get_groups_count	= at91_get_groups_count,
	.get_group_name		= at91_get_group_name,
	.get_group_pins		= at91_get_group_pins,
	.pin_dbg_show		= at91_pin_dbg_show,
	.dt_node_to_map		= at91_dt_node_to_map,
	.dt_मुक्त_map		= at91_dt_मुक्त_map,
पूर्ण;

अटल व्योम __iomem *pin_to_controller(काष्ठा at91_pinctrl *info,
				 अचिन्हित पूर्णांक bank)
अणु
	अगर (!gpio_chips[bank])
		वापस शून्य;

	वापस gpio_chips[bank]->regbase;
पूर्ण

अटल अंतरभूत पूर्णांक pin_to_bank(अचिन्हित pin)
अणु
	वापस pin /= MAX_NB_GPIO_PER_BANK;
पूर्ण

अटल अचिन्हित pin_to_mask(अचिन्हित पूर्णांक pin)
अणु
	वापस 1 << pin;
पूर्ण

अटल अचिन्हित two_bit_pin_value_shअगरt_amount(अचिन्हित पूर्णांक pin)
अणु
	/* वापस the shअगरt value क्रम a pin क्रम "two bit" per pin रेजिस्टरs,
	 * i.e. drive strength */
	वापस 2*((pin >= MAX_NB_GPIO_PER_BANK/2)
			? pin - MAX_NB_GPIO_PER_BANK/2 : pin);
पूर्ण

अटल अचिन्हित sama5d3_get_drive_रेजिस्टर(अचिन्हित पूर्णांक pin)
अणु
	/* drive strength is split between two रेजिस्टरs
	 * with two bits per pin */
	वापस (pin >= MAX_NB_GPIO_PER_BANK/2)
			? SAMA5D3_PIO_DRIVER2 : SAMA5D3_PIO_DRIVER1;
पूर्ण

अटल अचिन्हित at91sam9x5_get_drive_रेजिस्टर(अचिन्हित पूर्णांक pin)
अणु
	/* drive strength is split between two रेजिस्टरs
	 * with two bits per pin */
	वापस (pin >= MAX_NB_GPIO_PER_BANK/2)
			? AT91SAM9X5_PIO_DRIVER2 : AT91SAM9X5_PIO_DRIVER1;
पूर्ण

अटल व्योम at91_mux_disable_पूर्णांकerrupt(व्योम __iomem *pio, अचिन्हित mask)
अणु
	ग_लिखोl_relaxed(mask, pio + PIO_IDR);
पूर्ण

अटल अचिन्हित at91_mux_get_pullup(व्योम __iomem *pio, अचिन्हित pin)
अणु
	वापस !((पढ़ोl_relaxed(pio + PIO_PUSR) >> pin) & 0x1);
पूर्ण

अटल व्योम at91_mux_set_pullup(व्योम __iomem *pio, अचिन्हित mask, bool on)
अणु
	अगर (on)
		ग_लिखोl_relaxed(mask, pio + PIO_PPDDR);

	ग_लिखोl_relaxed(mask, pio + (on ? PIO_PUER : PIO_PUDR));
पूर्ण

अटल bool at91_mux_get_output(व्योम __iomem *pio, अचिन्हित पूर्णांक pin, bool *val)
अणु
	*val = (पढ़ोl_relaxed(pio + PIO_ODSR) >> pin) & 0x1;
	वापस (पढ़ोl_relaxed(pio + PIO_OSR) >> pin) & 0x1;
पूर्ण

अटल व्योम at91_mux_set_output(व्योम __iomem *pio, अचिन्हित पूर्णांक mask,
				bool is_on, bool val)
अणु
	ग_लिखोl_relaxed(mask, pio + (val ? PIO_SODR : PIO_CODR));
	ग_लिखोl_relaxed(mask, pio + (is_on ? PIO_OER : PIO_ODR));
पूर्ण

अटल अचिन्हित at91_mux_get_multidrive(व्योम __iomem *pio, अचिन्हित pin)
अणु
	वापस (पढ़ोl_relaxed(pio + PIO_MDSR) >> pin) & 0x1;
पूर्ण

अटल व्योम at91_mux_set_multidrive(व्योम __iomem *pio, अचिन्हित mask, bool on)
अणु
	ग_लिखोl_relaxed(mask, pio + (on ? PIO_MDER : PIO_MDDR));
पूर्ण

अटल व्योम at91_mux_set_A_periph(व्योम __iomem *pio, अचिन्हित mask)
अणु
	ग_लिखोl_relaxed(mask, pio + PIO_ASR);
पूर्ण

अटल व्योम at91_mux_set_B_periph(व्योम __iomem *pio, अचिन्हित mask)
अणु
	ग_लिखोl_relaxed(mask, pio + PIO_BSR);
पूर्ण

अटल व्योम at91_mux_pio3_set_A_periph(व्योम __iomem *pio, अचिन्हित mask)
अणु

	ग_लिखोl_relaxed(पढ़ोl_relaxed(pio + PIO_ABCDSR1) & ~mask,
						pio + PIO_ABCDSR1);
	ग_लिखोl_relaxed(पढ़ोl_relaxed(pio + PIO_ABCDSR2) & ~mask,
						pio + PIO_ABCDSR2);
पूर्ण

अटल व्योम at91_mux_pio3_set_B_periph(व्योम __iomem *pio, अचिन्हित mask)
अणु
	ग_लिखोl_relaxed(पढ़ोl_relaxed(pio + PIO_ABCDSR1) | mask,
						pio + PIO_ABCDSR1);
	ग_लिखोl_relaxed(पढ़ोl_relaxed(pio + PIO_ABCDSR2) & ~mask,
						pio + PIO_ABCDSR2);
पूर्ण

अटल व्योम at91_mux_pio3_set_C_periph(व्योम __iomem *pio, अचिन्हित mask)
अणु
	ग_लिखोl_relaxed(पढ़ोl_relaxed(pio + PIO_ABCDSR1) & ~mask, pio + PIO_ABCDSR1);
	ग_लिखोl_relaxed(पढ़ोl_relaxed(pio + PIO_ABCDSR2) | mask, pio + PIO_ABCDSR2);
पूर्ण

अटल व्योम at91_mux_pio3_set_D_periph(व्योम __iomem *pio, अचिन्हित mask)
अणु
	ग_लिखोl_relaxed(पढ़ोl_relaxed(pio + PIO_ABCDSR1) | mask, pio + PIO_ABCDSR1);
	ग_लिखोl_relaxed(पढ़ोl_relaxed(pio + PIO_ABCDSR2) | mask, pio + PIO_ABCDSR2);
पूर्ण

अटल क्रमागत at91_mux at91_mux_pio3_get_periph(व्योम __iomem *pio, अचिन्हित mask)
अणु
	अचिन्हित select;

	अगर (पढ़ोl_relaxed(pio + PIO_PSR) & mask)
		वापस AT91_MUX_GPIO;

	select = !!(पढ़ोl_relaxed(pio + PIO_ABCDSR1) & mask);
	select |= (!!(पढ़ोl_relaxed(pio + PIO_ABCDSR2) & mask) << 1);

	वापस select + 1;
पूर्ण

अटल क्रमागत at91_mux at91_mux_get_periph(व्योम __iomem *pio, अचिन्हित mask)
अणु
	अचिन्हित select;

	अगर (पढ़ोl_relaxed(pio + PIO_PSR) & mask)
		वापस AT91_MUX_GPIO;

	select = पढ़ोl_relaxed(pio + PIO_ABSR) & mask;

	वापस select + 1;
पूर्ण

अटल bool at91_mux_get_deglitch(व्योम __iomem *pio, अचिन्हित pin)
अणु
	वापस (पढ़ोl_relaxed(pio + PIO_IFSR) >> pin) & 0x1;
पूर्ण

अटल व्योम at91_mux_set_deglitch(व्योम __iomem *pio, अचिन्हित mask, bool is_on)
अणु
	ग_लिखोl_relaxed(mask, pio + (is_on ? PIO_IFER : PIO_IFDR));
पूर्ण

अटल bool at91_mux_pio3_get_deglitch(व्योम __iomem *pio, अचिन्हित pin)
अणु
	अगर ((पढ़ोl_relaxed(pio + PIO_IFSR) >> pin) & 0x1)
		वापस !((पढ़ोl_relaxed(pio + PIO_IFSCSR) >> pin) & 0x1);

	वापस false;
पूर्ण

अटल व्योम at91_mux_pio3_set_deglitch(व्योम __iomem *pio, अचिन्हित mask, bool is_on)
अणु
	अगर (is_on)
		ग_लिखोl_relaxed(mask, pio + PIO_IFSCDR);
	at91_mux_set_deglitch(pio, mask, is_on);
पूर्ण

अटल bool at91_mux_pio3_get_debounce(व्योम __iomem *pio, अचिन्हित pin, u32 *भाग)
अणु
	*भाग = पढ़ोl_relaxed(pio + PIO_SCDR);

	वापस ((पढ़ोl_relaxed(pio + PIO_IFSR) >> pin) & 0x1) &&
	       ((पढ़ोl_relaxed(pio + PIO_IFSCSR) >> pin) & 0x1);
पूर्ण

अटल व्योम at91_mux_pio3_set_debounce(व्योम __iomem *pio, अचिन्हित mask,
				bool is_on, u32 भाग)
अणु
	अगर (is_on) अणु
		ग_लिखोl_relaxed(mask, pio + PIO_IFSCER);
		ग_लिखोl_relaxed(भाग & PIO_SCDR_DIV, pio + PIO_SCDR);
		ग_लिखोl_relaxed(mask, pio + PIO_IFER);
	पूर्ण अन्यथा
		ग_लिखोl_relaxed(mask, pio + PIO_IFSCDR);
पूर्ण

अटल bool at91_mux_pio3_get_pullकरोwn(व्योम __iomem *pio, अचिन्हित pin)
अणु
	वापस !((पढ़ोl_relaxed(pio + PIO_PPDSR) >> pin) & 0x1);
पूर्ण

अटल व्योम at91_mux_pio3_set_pullकरोwn(व्योम __iomem *pio, अचिन्हित mask, bool is_on)
अणु
	अगर (is_on)
		ग_लिखोl_relaxed(mask, pio + PIO_PUDR);

	ग_लिखोl_relaxed(mask, pio + (is_on ? PIO_PPDER : PIO_PPDDR));
पूर्ण

अटल व्योम at91_mux_pio3_disable_schmitt_trig(व्योम __iomem *pio, अचिन्हित mask)
अणु
	ग_लिखोl_relaxed(पढ़ोl_relaxed(pio + PIO_SCHMITT) | mask, pio + PIO_SCHMITT);
पूर्ण

अटल bool at91_mux_pio3_get_schmitt_trig(व्योम __iomem *pio, अचिन्हित pin)
अणु
	वापस (पढ़ोl_relaxed(pio + PIO_SCHMITT) >> pin) & 0x1;
पूर्ण

अटल अंतरभूत u32 पढ़ो_drive_strength(व्योम __iomem *reg, अचिन्हित pin)
अणु
	अचिन्हित पंचांगp = पढ़ोl_relaxed(reg);

	पंचांगp = पंचांगp >> two_bit_pin_value_shअगरt_amount(pin);

	वापस पंचांगp & DRIVE_STRENGTH_MASK;
पूर्ण

अटल अचिन्हित at91_mux_sama5d3_get_drivestrength(व्योम __iomem *pio,
							अचिन्हित pin)
अणु
	अचिन्हित पंचांगp = पढ़ो_drive_strength(pio +
					sama5d3_get_drive_रेजिस्टर(pin), pin);

	/* SAMA5 strength is 1:1 with our defines,
	 * except 0 is equivalent to low per datasheet */
	अगर (!पंचांगp)
		पंचांगp = DRIVE_STRENGTH_BIT_MSK(LOW);

	वापस पंचांगp;
पूर्ण

अटल अचिन्हित at91_mux_sam9x5_get_drivestrength(व्योम __iomem *pio,
							अचिन्हित pin)
अणु
	अचिन्हित पंचांगp = पढ़ो_drive_strength(pio +
				at91sam9x5_get_drive_रेजिस्टर(pin), pin);

	/* strength is inverse in SAM9x5s hardware with the pinctrl defines
	 * hardware: 0 = hi, 1 = med, 2 = low, 3 = rsvd */
	पंचांगp = DRIVE_STRENGTH_BIT_MSK(HI) - पंचांगp;

	वापस पंचांगp;
पूर्ण

अटल अचिन्हित at91_mux_sam9x60_get_drivestrength(व्योम __iomem *pio,
						   अचिन्हित pin)
अणु
	अचिन्हित पंचांगp = पढ़ोl_relaxed(pio + SAM9X60_PIO_DRIVER1);

	अगर (पंचांगp & BIT(pin))
		वापस DRIVE_STRENGTH_BIT_HI;

	वापस DRIVE_STRENGTH_BIT_LOW;
पूर्ण

अटल अचिन्हित at91_mux_sam9x60_get_slewrate(व्योम __iomem *pio, अचिन्हित pin)
अणु
	अचिन्हित पंचांगp = पढ़ोl_relaxed(pio + SAM9X60_PIO_SLEWR);

	अगर ((पंचांगp & BIT(pin)))
		वापस SLEWRATE_BIT_ENA;

	वापस SLEWRATE_BIT_DIS;
पूर्ण

अटल व्योम set_drive_strength(व्योम __iomem *reg, अचिन्हित pin, u32 strength)
अणु
	अचिन्हित पंचांगp = पढ़ोl_relaxed(reg);
	अचिन्हित shअगरt = two_bit_pin_value_shअगरt_amount(pin);

	पंचांगp &= ~(DRIVE_STRENGTH_MASK  <<  shअगरt);
	पंचांगp |= strength << shअगरt;

	ग_लिखोl_relaxed(पंचांगp, reg);
पूर्ण

अटल व्योम at91_mux_sama5d3_set_drivestrength(व्योम __iomem *pio, अचिन्हित pin,
						u32 setting)
अणु
	/* करो nothing अगर setting is zero */
	अगर (!setting)
		वापस;

	/* strength is 1 to 1 with setting क्रम SAMA5 */
	set_drive_strength(pio + sama5d3_get_drive_रेजिस्टर(pin), pin, setting);
पूर्ण

अटल व्योम at91_mux_sam9x5_set_drivestrength(व्योम __iomem *pio, अचिन्हित pin,
						u32 setting)
अणु
	/* करो nothing अगर setting is zero */
	अगर (!setting)
		वापस;

	/* strength is inverse on SAM9x5s with our defines
	 * 0 = hi, 1 = med, 2 = low, 3 = rsvd */
	setting = DRIVE_STRENGTH_BIT_MSK(HI) - setting;

	set_drive_strength(pio + at91sam9x5_get_drive_रेजिस्टर(pin), pin,
				setting);
पूर्ण

अटल व्योम at91_mux_sam9x60_set_drivestrength(व्योम __iomem *pio, अचिन्हित pin,
					       u32 setting)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	अगर (setting <= DRIVE_STRENGTH_BIT_DEF ||
	    setting == DRIVE_STRENGTH_BIT_MED ||
	    setting > DRIVE_STRENGTH_BIT_HI)
		वापस;

	पंचांगp = पढ़ोl_relaxed(pio + SAM9X60_PIO_DRIVER1);

	/* Strength is 0: low, 1: hi */
	अगर (setting == DRIVE_STRENGTH_BIT_LOW)
		पंचांगp &= ~BIT(pin);
	अन्यथा
		पंचांगp |= BIT(pin);

	ग_लिखोl_relaxed(पंचांगp, pio + SAM9X60_PIO_DRIVER1);
पूर्ण

अटल व्योम at91_mux_sam9x60_set_slewrate(व्योम __iomem *pio, अचिन्हित pin,
					  u32 setting)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	अगर (setting < SLEWRATE_BIT_ENA || setting > SLEWRATE_BIT_DIS)
		वापस;

	पंचांगp = पढ़ोl_relaxed(pio + SAM9X60_PIO_SLEWR);

	अगर (setting == SLEWRATE_BIT_DIS)
		पंचांगp &= ~BIT(pin);
	अन्यथा
		पंचांगp |= BIT(pin);

	ग_लिखोl_relaxed(पंचांगp, pio + SAM9X60_PIO_SLEWR);
पूर्ण

अटल काष्ठा at91_pinctrl_mux_ops at91rm9200_ops = अणु
	.get_periph	= at91_mux_get_periph,
	.mux_A_periph	= at91_mux_set_A_periph,
	.mux_B_periph	= at91_mux_set_B_periph,
	.get_deglitch	= at91_mux_get_deglitch,
	.set_deglitch	= at91_mux_set_deglitch,
	.irq_type	= gpio_irq_type,
पूर्ण;

अटल काष्ठा at91_pinctrl_mux_ops at91sam9x5_ops = अणु
	.get_periph	= at91_mux_pio3_get_periph,
	.mux_A_periph	= at91_mux_pio3_set_A_periph,
	.mux_B_periph	= at91_mux_pio3_set_B_periph,
	.mux_C_periph	= at91_mux_pio3_set_C_periph,
	.mux_D_periph	= at91_mux_pio3_set_D_periph,
	.get_deglitch	= at91_mux_pio3_get_deglitch,
	.set_deglitch	= at91_mux_pio3_set_deglitch,
	.get_debounce	= at91_mux_pio3_get_debounce,
	.set_debounce	= at91_mux_pio3_set_debounce,
	.get_pullकरोwn	= at91_mux_pio3_get_pullकरोwn,
	.set_pullकरोwn	= at91_mux_pio3_set_pullकरोwn,
	.get_schmitt_trig = at91_mux_pio3_get_schmitt_trig,
	.disable_schmitt_trig = at91_mux_pio3_disable_schmitt_trig,
	.get_drivestrength = at91_mux_sam9x5_get_drivestrength,
	.set_drivestrength = at91_mux_sam9x5_set_drivestrength,
	.irq_type	= alt_gpio_irq_type,
पूर्ण;

अटल स्थिर काष्ठा at91_pinctrl_mux_ops sam9x60_ops = अणु
	.get_periph	= at91_mux_pio3_get_periph,
	.mux_A_periph	= at91_mux_pio3_set_A_periph,
	.mux_B_periph	= at91_mux_pio3_set_B_periph,
	.mux_C_periph	= at91_mux_pio3_set_C_periph,
	.mux_D_periph	= at91_mux_pio3_set_D_periph,
	.get_deglitch	= at91_mux_pio3_get_deglitch,
	.set_deglitch	= at91_mux_pio3_set_deglitch,
	.get_debounce	= at91_mux_pio3_get_debounce,
	.set_debounce	= at91_mux_pio3_set_debounce,
	.get_pullकरोwn	= at91_mux_pio3_get_pullकरोwn,
	.set_pullकरोwn	= at91_mux_pio3_set_pullकरोwn,
	.get_schmitt_trig = at91_mux_pio3_get_schmitt_trig,
	.disable_schmitt_trig = at91_mux_pio3_disable_schmitt_trig,
	.get_drivestrength = at91_mux_sam9x60_get_drivestrength,
	.set_drivestrength = at91_mux_sam9x60_set_drivestrength,
	.get_slewrate   = at91_mux_sam9x60_get_slewrate,
	.set_slewrate   = at91_mux_sam9x60_set_slewrate,
	.irq_type	= alt_gpio_irq_type,
पूर्ण;

अटल काष्ठा at91_pinctrl_mux_ops sama5d3_ops = अणु
	.get_periph	= at91_mux_pio3_get_periph,
	.mux_A_periph	= at91_mux_pio3_set_A_periph,
	.mux_B_periph	= at91_mux_pio3_set_B_periph,
	.mux_C_periph	= at91_mux_pio3_set_C_periph,
	.mux_D_periph	= at91_mux_pio3_set_D_periph,
	.get_deglitch	= at91_mux_pio3_get_deglitch,
	.set_deglitch	= at91_mux_pio3_set_deglitch,
	.get_debounce	= at91_mux_pio3_get_debounce,
	.set_debounce	= at91_mux_pio3_set_debounce,
	.get_pullकरोwn	= at91_mux_pio3_get_pullकरोwn,
	.set_pullकरोwn	= at91_mux_pio3_set_pullकरोwn,
	.get_schmitt_trig = at91_mux_pio3_get_schmitt_trig,
	.disable_schmitt_trig = at91_mux_pio3_disable_schmitt_trig,
	.get_drivestrength = at91_mux_sama5d3_get_drivestrength,
	.set_drivestrength = at91_mux_sama5d3_set_drivestrength,
	.irq_type	= alt_gpio_irq_type,
पूर्ण;

अटल व्योम at91_pin_dbg(स्थिर काष्ठा device *dev, स्थिर काष्ठा at91_pmx_pin *pin)
अणु
	अगर (pin->mux) अणु
		dev_dbg(dev, "pio%c%d configured as periph%c with conf = 0x%lx\n",
			pin->bank + 'A', pin->pin, pin->mux - 1 + 'A', pin->conf);
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "pio%c%d configured as gpio with conf = 0x%lx\n",
			pin->bank + 'A', pin->pin, pin->conf);
	पूर्ण
पूर्ण

अटल पूर्णांक pin_check_config(काष्ठा at91_pinctrl *info, स्थिर अक्षर *name,
			    पूर्णांक index, स्थिर काष्ठा at91_pmx_pin *pin)
अणु
	पूर्णांक mux;

	/* check अगर it's a valid config */
	अगर (pin->bank >= gpio_banks) अणु
		dev_err(info->dev, "%s: pin conf %d bank_id %d >= nbanks %d\n",
			name, index, pin->bank, gpio_banks);
		वापस -EINVAL;
	पूर्ण

	अगर (!gpio_chips[pin->bank]) अणु
		dev_err(info->dev, "%s: pin conf %d bank_id %d not enabled\n",
			name, index, pin->bank);
		वापस -ENXIO;
	पूर्ण

	अगर (pin->pin >= MAX_NB_GPIO_PER_BANK) अणु
		dev_err(info->dev, "%s: pin conf %d pin_bank_id %d >= %d\n",
			name, index, pin->pin, MAX_NB_GPIO_PER_BANK);
		वापस -EINVAL;
	पूर्ण

	अगर (!pin->mux)
		वापस 0;

	mux = pin->mux - 1;

	अगर (mux >= info->nmux) अणु
		dev_err(info->dev, "%s: pin conf %d mux_id %d >= nmux %d\n",
			name, index, mux, info->nmux);
		वापस -EINVAL;
	पूर्ण

	अगर (!(info->mux_mask[pin->bank * info->nmux + mux] & 1 << pin->pin)) अणु
		dev_err(info->dev, "%s: pin conf %d mux_id %d not supported for pio%c%d\n",
			name, index, mux, pin->bank + 'A', pin->pin);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम at91_mux_gpio_disable(व्योम __iomem *pio, अचिन्हित mask)
अणु
	ग_लिखोl_relaxed(mask, pio + PIO_PDR);
पूर्ण

अटल व्योम at91_mux_gpio_enable(व्योम __iomem *pio, अचिन्हित mask, bool input)
अणु
	ग_लिखोl_relaxed(mask, pio + PIO_PER);
	ग_लिखोl_relaxed(mask, pio + (input ? PIO_ODR : PIO_OER));
पूर्ण

अटल पूर्णांक at91_pmx_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित selector,
			अचिन्हित group)
अणु
	काष्ठा at91_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा at91_pmx_pin *pins_conf = info->groups[group].pins_conf;
	स्थिर काष्ठा at91_pmx_pin *pin;
	uपूर्णांक32_t npins = info->groups[group].npins;
	पूर्णांक i, ret;
	अचिन्हित mask;
	व्योम __iomem *pio;

	dev_dbg(info->dev, "enable function %s group %s\n",
		info->functions[selector].name, info->groups[group].name);

	/* first check that all the pins of the group are valid with a valid
	 * parameter */
	क्रम (i = 0; i < npins; i++) अणु
		pin = &pins_conf[i];
		ret = pin_check_config(info, info->groups[group].name, i, pin);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < npins; i++) अणु
		pin = &pins_conf[i];
		at91_pin_dbg(info->dev, pin);
		pio = pin_to_controller(info, pin->bank);

		अगर (!pio)
			जारी;

		mask = pin_to_mask(pin->pin);
		at91_mux_disable_पूर्णांकerrupt(pio, mask);
		चयन (pin->mux) अणु
		हाल AT91_MUX_GPIO:
			at91_mux_gpio_enable(pio, mask, 1);
			अवरोध;
		हाल AT91_MUX_PERIPH_A:
			info->ops->mux_A_periph(pio, mask);
			अवरोध;
		हाल AT91_MUX_PERIPH_B:
			info->ops->mux_B_periph(pio, mask);
			अवरोध;
		हाल AT91_MUX_PERIPH_C:
			अगर (!info->ops->mux_C_periph)
				वापस -EINVAL;
			info->ops->mux_C_periph(pio, mask);
			अवरोध;
		हाल AT91_MUX_PERIPH_D:
			अगर (!info->ops->mux_D_periph)
				वापस -EINVAL;
			info->ops->mux_D_periph(pio, mask);
			अवरोध;
		पूर्ण
		अगर (pin->mux)
			at91_mux_gpio_disable(pio, mask);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक at91_pmx_get_funcs_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा at91_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);

	वापस info->nfunctions;
पूर्ण

अटल स्थिर अक्षर *at91_pmx_get_func_name(काष्ठा pinctrl_dev *pctldev,
					  अचिन्हित selector)
अणु
	काष्ठा at91_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);

	वापस info->functions[selector].name;
पूर्ण

अटल पूर्णांक at91_pmx_get_groups(काष्ठा pinctrl_dev *pctldev, अचिन्हित selector,
			       स्थिर अक्षर * स्थिर **groups,
			       अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा at91_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);

	*groups = info->functions[selector].groups;
	*num_groups = info->functions[selector].ngroups;

	वापस 0;
पूर्ण

अटल पूर्णांक at91_gpio_request_enable(काष्ठा pinctrl_dev *pctldev,
				    काष्ठा pinctrl_gpio_range *range,
				    अचिन्हित offset)
अणु
	काष्ठा at91_pinctrl *npct = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा at91_gpio_chip *at91_chip;
	काष्ठा gpio_chip *chip;
	अचिन्हित mask;

	अगर (!range) अणु
		dev_err(npct->dev, "invalid range\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!range->gc) अणु
		dev_err(npct->dev, "missing GPIO chip in range\n");
		वापस -EINVAL;
	पूर्ण
	chip = range->gc;
	at91_chip = gpiochip_get_data(chip);

	dev_dbg(npct->dev, "enable pin %u as GPIO\n", offset);

	mask = 1 << (offset - chip->base);

	dev_dbg(npct->dev, "enable pin %u as PIO%c%d 0x%x\n",
		offset, 'A' + range->id, offset - chip->base, mask);

	ग_लिखोl_relaxed(mask, at91_chip->regbase + PIO_PER);

	वापस 0;
पूर्ण

अटल व्योम at91_gpio_disable_मुक्त(काष्ठा pinctrl_dev *pctldev,
				   काष्ठा pinctrl_gpio_range *range,
				   अचिन्हित offset)
अणु
	काष्ठा at91_pinctrl *npct = pinctrl_dev_get_drvdata(pctldev);

	dev_dbg(npct->dev, "disable pin %u as GPIO\n", offset);
	/* Set the pin to some शेष state, GPIO is usually शेष */
पूर्ण

अटल स्थिर काष्ठा pinmux_ops at91_pmx_ops = अणु
	.get_functions_count	= at91_pmx_get_funcs_count,
	.get_function_name	= at91_pmx_get_func_name,
	.get_function_groups	= at91_pmx_get_groups,
	.set_mux		= at91_pmx_set,
	.gpio_request_enable	= at91_gpio_request_enable,
	.gpio_disable_मुक्त	= at91_gpio_disable_मुक्त,
पूर्ण;

अटल पूर्णांक at91_pinconf_get(काष्ठा pinctrl_dev *pctldev,
			     अचिन्हित pin_id, अचिन्हित दीर्घ *config)
अणु
	काष्ठा at91_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);
	व्योम __iomem *pio;
	अचिन्हित pin;
	पूर्णांक भाग;
	bool out;

	*config = 0;
	dev_dbg(info->dev, "%s:%d, pin_id=%d", __func__, __LINE__, pin_id);
	pio = pin_to_controller(info, pin_to_bank(pin_id));

	अगर (!pio)
		वापस -EINVAL;

	pin = pin_id % MAX_NB_GPIO_PER_BANK;

	अगर (at91_mux_get_multidrive(pio, pin))
		*config |= MULTI_DRIVE;

	अगर (at91_mux_get_pullup(pio, pin))
		*config |= PULL_UP;

	अगर (info->ops->get_deglitch && info->ops->get_deglitch(pio, pin))
		*config |= DEGLITCH;
	अगर (info->ops->get_debounce && info->ops->get_debounce(pio, pin, &भाग))
		*config |= DEBOUNCE | (भाग << DEBOUNCE_VAL_SHIFT);
	अगर (info->ops->get_pullकरोwn && info->ops->get_pullकरोwn(pio, pin))
		*config |= PULL_DOWN;
	अगर (info->ops->get_schmitt_trig && info->ops->get_schmitt_trig(pio, pin))
		*config |= DIS_SCHMIT;
	अगर (info->ops->get_drivestrength)
		*config |= (info->ops->get_drivestrength(pio, pin)
				<< DRIVE_STRENGTH_SHIFT);
	अगर (info->ops->get_slewrate)
		*config |= (info->ops->get_slewrate(pio, pin) << SLEWRATE_SHIFT);
	अगर (at91_mux_get_output(pio, pin, &out))
		*config |= OUTPUT | (out << OUTPUT_VAL_SHIFT);

	वापस 0;
पूर्ण

अटल पूर्णांक at91_pinconf_set(काष्ठा pinctrl_dev *pctldev,
			     अचिन्हित pin_id, अचिन्हित दीर्घ *configs,
			     अचिन्हित num_configs)
अणु
	काष्ठा at91_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित mask;
	व्योम __iomem *pio;
	पूर्णांक i;
	अचिन्हित दीर्घ config;
	अचिन्हित pin;

	क्रम (i = 0; i < num_configs; i++) अणु
		config = configs[i];

		dev_dbg(info->dev,
			"%s:%d, pin_id=%d, config=0x%lx",
			__func__, __LINE__, pin_id, config);
		pio = pin_to_controller(info, pin_to_bank(pin_id));

		अगर (!pio)
			वापस -EINVAL;

		pin = pin_id % MAX_NB_GPIO_PER_BANK;
		mask = pin_to_mask(pin);

		अगर (config & PULL_UP && config & PULL_DOWN)
			वापस -EINVAL;

		at91_mux_set_output(pio, mask, config & OUTPUT,
				    (config & OUTPUT_VAL) >> OUTPUT_VAL_SHIFT);
		at91_mux_set_pullup(pio, mask, config & PULL_UP);
		at91_mux_set_multidrive(pio, mask, config & MULTI_DRIVE);
		अगर (info->ops->set_deglitch)
			info->ops->set_deglitch(pio, mask, config & DEGLITCH);
		अगर (info->ops->set_debounce)
			info->ops->set_debounce(pio, mask, config & DEBOUNCE,
				(config & DEBOUNCE_VAL) >> DEBOUNCE_VAL_SHIFT);
		अगर (info->ops->set_pullकरोwn)
			info->ops->set_pullकरोwn(pio, mask, config & PULL_DOWN);
		अगर (info->ops->disable_schmitt_trig && config & DIS_SCHMIT)
			info->ops->disable_schmitt_trig(pio, mask);
		अगर (info->ops->set_drivestrength)
			info->ops->set_drivestrength(pio, pin,
				(config & DRIVE_STRENGTH)
					>> DRIVE_STRENGTH_SHIFT);
		अगर (info->ops->set_slewrate)
			info->ops->set_slewrate(pio, pin,
				(config & SLEWRATE) >> SLEWRATE_SHIFT);

	पूर्ण /* क्रम each config */

	वापस 0;
पूर्ण

#घोषणा DBG_SHOW_FLAG(flag) करो अणु		\
	अगर (config & flag) अणु			\
		अगर (num_conf)			\
			seq_माला_दो(s, "|");	\
		seq_माला_दो(s, #flag);		\
		num_conf++;			\
	पूर्ण					\
पूर्ण जबतक (0)

#घोषणा DBG_SHOW_FLAG_MASKED(mask, flag, name) करो अणु \
	अगर ((config & mask) == flag) अणु		\
		अगर (num_conf)			\
			seq_माला_दो(s, "|");	\
		seq_माला_दो(s, #name);		\
		num_conf++;			\
	पूर्ण					\
पूर्ण जबतक (0)

अटल व्योम at91_pinconf_dbg_show(काष्ठा pinctrl_dev *pctldev,
				   काष्ठा seq_file *s, अचिन्हित pin_id)
अणु
	अचिन्हित दीर्घ config;
	पूर्णांक val, num_conf = 0;

	at91_pinconf_get(pctldev, pin_id, &config);

	DBG_SHOW_FLAG(MULTI_DRIVE);
	DBG_SHOW_FLAG(PULL_UP);
	DBG_SHOW_FLAG(PULL_DOWN);
	DBG_SHOW_FLAG(DIS_SCHMIT);
	DBG_SHOW_FLAG(DEGLITCH);
	DBG_SHOW_FLAG_MASKED(DRIVE_STRENGTH, DRIVE_STRENGTH_BIT_MSK(LOW),
			     DRIVE_STRENGTH_LOW);
	DBG_SHOW_FLAG_MASKED(DRIVE_STRENGTH, DRIVE_STRENGTH_BIT_MSK(MED),
			     DRIVE_STRENGTH_MED);
	DBG_SHOW_FLAG_MASKED(DRIVE_STRENGTH, DRIVE_STRENGTH_BIT_MSK(HI),
			     DRIVE_STRENGTH_HI);
	DBG_SHOW_FLAG(SLEWRATE);
	DBG_SHOW_FLAG(DEBOUNCE);
	अगर (config & DEBOUNCE) अणु
		val = config >> DEBOUNCE_VAL_SHIFT;
		seq_म_लिखो(s, "(%d)", val);
	पूर्ण

	वापस;
पूर्ण

अटल व्योम at91_pinconf_group_dbg_show(काष्ठा pinctrl_dev *pctldev,
					 काष्ठा seq_file *s, अचिन्हित group)
अणु
पूर्ण

अटल स्थिर काष्ठा pinconf_ops at91_pinconf_ops = अणु
	.pin_config_get			= at91_pinconf_get,
	.pin_config_set			= at91_pinconf_set,
	.pin_config_dbg_show		= at91_pinconf_dbg_show,
	.pin_config_group_dbg_show	= at91_pinconf_group_dbg_show,
पूर्ण;

अटल काष्ठा pinctrl_desc at91_pinctrl_desc = अणु
	.pctlops	= &at91_pctrl_ops,
	.pmxops		= &at91_pmx_ops,
	.confops	= &at91_pinconf_ops,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर अक्षर *gpio_compat = "atmel,at91rm9200-gpio";

अटल व्योम at91_pinctrl_child_count(काष्ठा at91_pinctrl *info,
				     काष्ठा device_node *np)
अणु
	काष्ठा device_node *child;

	क्रम_each_child_of_node(np, child) अणु
		अगर (of_device_is_compatible(child, gpio_compat)) अणु
			अगर (of_device_is_available(child))
				info->nactive_banks++;
		पूर्ण अन्यथा अणु
			info->nfunctions++;
			info->ngroups += of_get_child_count(child);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक at91_pinctrl_mux_mask(काष्ठा at91_pinctrl *info,
				 काष्ठा device_node *np)
अणु
	पूर्णांक ret = 0;
	पूर्णांक size;
	स्थिर __be32 *list;

	list = of_get_property(np, "atmel,mux-mask", &size);
	अगर (!list) अणु
		dev_err(info->dev, "can not read the mux-mask of %d\n", size);
		वापस -EINVAL;
	पूर्ण

	size /= माप(*list);
	अगर (!size || size % gpio_banks) अणु
		dev_err(info->dev, "wrong mux mask array should be by %d\n", gpio_banks);
		वापस -EINVAL;
	पूर्ण
	info->nmux = size / gpio_banks;

	info->mux_mask = devm_kसुस्मृति(info->dev, size, माप(u32),
				      GFP_KERNEL);
	अगर (!info->mux_mask)
		वापस -ENOMEM;

	ret = of_property_पढ़ो_u32_array(np, "atmel,mux-mask",
					  info->mux_mask, size);
	अगर (ret)
		dev_err(info->dev, "can not read the mux-mask of %d\n", size);
	वापस ret;
पूर्ण

अटल पूर्णांक at91_pinctrl_parse_groups(काष्ठा device_node *np,
				     काष्ठा at91_pin_group *grp,
				     काष्ठा at91_pinctrl *info, u32 index)
अणु
	काष्ठा at91_pmx_pin *pin;
	पूर्णांक size;
	स्थिर __be32 *list;
	पूर्णांक i, j;

	dev_dbg(info->dev, "group(%d): %pOFn\n", index, np);

	/* Initialise group */
	grp->name = np->name;

	/*
	 * the binding क्रमmat is aपंचांगel,pins = <bank pin mux CONFIG ...>,
	 * करो sanity check and calculate pins number
	 */
	list = of_get_property(np, "atmel,pins", &size);
	/* we करो not check वापस since it's safe node passed करोwn */
	size /= माप(*list);
	अगर (!size || size % 4) अणु
		dev_err(info->dev, "wrong pins number or pins and configs should be by 4\n");
		वापस -EINVAL;
	पूर्ण

	grp->npins = size / 4;
	pin = grp->pins_conf = devm_kसुस्मृति(info->dev,
					    grp->npins,
					    माप(काष्ठा at91_pmx_pin),
					    GFP_KERNEL);
	grp->pins = devm_kसुस्मृति(info->dev, grp->npins, माप(अचिन्हित पूर्णांक),
				 GFP_KERNEL);
	अगर (!grp->pins_conf || !grp->pins)
		वापस -ENOMEM;

	क्रम (i = 0, j = 0; i < size; i += 4, j++) अणु
		pin->bank = be32_to_cpu(*list++);
		pin->pin = be32_to_cpu(*list++);
		grp->pins[j] = pin->bank * MAX_NB_GPIO_PER_BANK + pin->pin;
		pin->mux = be32_to_cpu(*list++);
		pin->conf = be32_to_cpu(*list++);

		at91_pin_dbg(info->dev, pin);
		pin++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक at91_pinctrl_parse_functions(काष्ठा device_node *np,
					काष्ठा at91_pinctrl *info, u32 index)
अणु
	काष्ठा device_node *child;
	काष्ठा at91_pmx_func *func;
	काष्ठा at91_pin_group *grp;
	पूर्णांक ret;
	अटल u32 grp_index;
	u32 i = 0;

	dev_dbg(info->dev, "parse function(%d): %pOFn\n", index, np);

	func = &info->functions[index];

	/* Initialise function */
	func->name = np->name;
	func->ngroups = of_get_child_count(np);
	अगर (func->ngroups == 0) अणु
		dev_err(info->dev, "no groups defined\n");
		वापस -EINVAL;
	पूर्ण
	func->groups = devm_kसुस्मृति(info->dev,
			func->ngroups, माप(अक्षर *), GFP_KERNEL);
	अगर (!func->groups)
		वापस -ENOMEM;

	क्रम_each_child_of_node(np, child) अणु
		func->groups[i] = child->name;
		grp = &info->groups[grp_index++];
		ret = at91_pinctrl_parse_groups(child, grp, info, i++);
		अगर (ret) अणु
			of_node_put(child);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id at91_pinctrl_of_match[] = अणु
	अणु .compatible = "atmel,sama5d3-pinctrl", .data = &sama5d3_ops पूर्ण,
	अणु .compatible = "atmel,at91sam9x5-pinctrl", .data = &at91sam9x5_ops पूर्ण,
	अणु .compatible = "atmel,at91rm9200-pinctrl", .data = &at91rm9200_ops पूर्ण,
	अणु .compatible = "microchip,sam9x60-pinctrl", .data = &sam9x60_ops पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक at91_pinctrl_probe_dt(काष्ठा platक्रमm_device *pdev,
				 काष्ठा at91_pinctrl *info)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i, j;
	uपूर्णांक32_t *पंचांगp;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *child;

	अगर (!np)
		वापस -ENODEV;

	info->dev = &pdev->dev;
	info->ops = (काष्ठा at91_pinctrl_mux_ops *)
		of_match_device(at91_pinctrl_of_match, &pdev->dev)->data;
	at91_pinctrl_child_count(info, np);

	अगर (gpio_banks < 1) अणु
		dev_err(&pdev->dev, "you need to specify at least one gpio-controller\n");
		वापस -EINVAL;
	पूर्ण

	ret = at91_pinctrl_mux_mask(info, np);
	अगर (ret)
		वापस ret;

	dev_dbg(&pdev->dev, "nmux = %d\n", info->nmux);

	dev_dbg(&pdev->dev, "mux-mask\n");
	पंचांगp = info->mux_mask;
	क्रम (i = 0; i < gpio_banks; i++) अणु
		क्रम (j = 0; j < info->nmux; j++, पंचांगp++) अणु
			dev_dbg(&pdev->dev, "%d:%d\t0x%x\n", i, j, पंचांगp[0]);
		पूर्ण
	पूर्ण

	dev_dbg(&pdev->dev, "nfunctions = %d\n", info->nfunctions);
	dev_dbg(&pdev->dev, "ngroups = %d\n", info->ngroups);
	info->functions = devm_kसुस्मृति(&pdev->dev,
					info->nfunctions,
					माप(काष्ठा at91_pmx_func),
					GFP_KERNEL);
	अगर (!info->functions)
		वापस -ENOMEM;

	info->groups = devm_kसुस्मृति(&pdev->dev,
					info->ngroups,
					माप(काष्ठा at91_pin_group),
					GFP_KERNEL);
	अगर (!info->groups)
		वापस -ENOMEM;

	dev_dbg(&pdev->dev, "nbanks = %d\n", gpio_banks);
	dev_dbg(&pdev->dev, "nfunctions = %d\n", info->nfunctions);
	dev_dbg(&pdev->dev, "ngroups = %d\n", info->ngroups);

	i = 0;

	क्रम_each_child_of_node(np, child) अणु
		अगर (of_device_is_compatible(child, gpio_compat))
			जारी;
		ret = at91_pinctrl_parse_functions(child, info, i++);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to parse function\n");
			of_node_put(child);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक at91_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा at91_pinctrl *info;
	काष्ठा pinctrl_pin_desc *pdesc;
	पूर्णांक ret, i, j, k, ngpio_chips_enabled = 0;

	info = devm_kzalloc(&pdev->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	ret = at91_pinctrl_probe_dt(pdev, info);
	अगर (ret)
		वापस ret;

	/*
	 * We need all the GPIO drivers to probe FIRST, or we will not be able
	 * to obtain references to the काष्ठा gpio_chip * क्रम them, and we
	 * need this to proceed.
	 */
	क्रम (i = 0; i < gpio_banks; i++)
		अगर (gpio_chips[i])
			ngpio_chips_enabled++;

	अगर (ngpio_chips_enabled < info->nactive_banks) अणु
		dev_warn(&pdev->dev,
			 "All GPIO chips are not registered yet (%d/%d)\n",
			 ngpio_chips_enabled, info->nactive_banks);
		devm_kमुक्त(&pdev->dev, info);
		वापस -EPROBE_DEFER;
	पूर्ण

	at91_pinctrl_desc.name = dev_name(&pdev->dev);
	at91_pinctrl_desc.npins = gpio_banks * MAX_NB_GPIO_PER_BANK;
	at91_pinctrl_desc.pins = pdesc =
		devm_kसुस्मृति(&pdev->dev,
			     at91_pinctrl_desc.npins, माप(*pdesc),
			     GFP_KERNEL);

	अगर (!at91_pinctrl_desc.pins)
		वापस -ENOMEM;

	क्रम (i = 0, k = 0; i < gpio_banks; i++) अणु
		क्रम (j = 0; j < MAX_NB_GPIO_PER_BANK; j++, k++) अणु
			pdesc->number = k;
			pdesc->name = kaप्र_लिखो(GFP_KERNEL, "pio%c%d", i + 'A', j);
			pdesc++;
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, info);
	info->pctl = devm_pinctrl_रेजिस्टर(&pdev->dev, &at91_pinctrl_desc,
					   info);

	अगर (IS_ERR(info->pctl)) अणु
		dev_err(&pdev->dev, "could not register AT91 pinctrl driver\n");
		वापस PTR_ERR(info->pctl);
	पूर्ण

	/* We will handle a range of GPIO pins */
	क्रम (i = 0; i < gpio_banks; i++)
		अगर (gpio_chips[i])
			pinctrl_add_gpio_range(info->pctl, &gpio_chips[i]->range);

	dev_info(&pdev->dev, "initialized AT91 pinctrl driver\n");

	वापस 0;
पूर्ण

अटल पूर्णांक at91_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा at91_gpio_chip *at91_gpio = gpiochip_get_data(chip);
	व्योम __iomem *pio = at91_gpio->regbase;
	अचिन्हित mask = 1 << offset;
	u32 osr;

	osr = पढ़ोl_relaxed(pio + PIO_OSR);
	अगर (osr & mask)
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक at91_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा at91_gpio_chip *at91_gpio = gpiochip_get_data(chip);
	व्योम __iomem *pio = at91_gpio->regbase;
	अचिन्हित mask = 1 << offset;

	ग_लिखोl_relaxed(mask, pio + PIO_ODR);
	वापस 0;
पूर्ण

अटल पूर्णांक at91_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा at91_gpio_chip *at91_gpio = gpiochip_get_data(chip);
	व्योम __iomem *pio = at91_gpio->regbase;
	अचिन्हित mask = 1 << offset;
	u32 pdsr;

	pdsr = पढ़ोl_relaxed(pio + PIO_PDSR);
	वापस (pdsr & mask) != 0;
पूर्ण

अटल व्योम at91_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset,
				पूर्णांक val)
अणु
	काष्ठा at91_gpio_chip *at91_gpio = gpiochip_get_data(chip);
	व्योम __iomem *pio = at91_gpio->regbase;
	अचिन्हित mask = 1 << offset;

	ग_लिखोl_relaxed(mask, pio + (val ? PIO_SODR : PIO_CODR));
पूर्ण

अटल व्योम at91_gpio_set_multiple(काष्ठा gpio_chip *chip,
				      अचिन्हित दीर्घ *mask, अचिन्हित दीर्घ *bits)
अणु
	काष्ठा at91_gpio_chip *at91_gpio = gpiochip_get_data(chip);
	व्योम __iomem *pio = at91_gpio->regbase;

#घोषणा BITS_MASK(bits) (((bits) == 32) ? ~0U : (BIT(bits) - 1))
	/* Mask additionally to ngpio as not all GPIO controllers have 32 pins */
	uपूर्णांक32_t set_mask = (*mask & *bits) & BITS_MASK(chip->ngpio);
	uपूर्णांक32_t clear_mask = (*mask & ~(*bits)) & BITS_MASK(chip->ngpio);

	ग_लिखोl_relaxed(set_mask, pio + PIO_SODR);
	ग_लिखोl_relaxed(clear_mask, pio + PIO_CODR);
पूर्ण

अटल पूर्णांक at91_gpio_direction_output(काष्ठा gpio_chip *chip, अचिन्हित offset,
				पूर्णांक val)
अणु
	काष्ठा at91_gpio_chip *at91_gpio = gpiochip_get_data(chip);
	व्योम __iomem *pio = at91_gpio->regbase;
	अचिन्हित mask = 1 << offset;

	ग_लिखोl_relaxed(mask, pio + (val ? PIO_SODR : PIO_CODR));
	ग_लिखोl_relaxed(mask, pio + PIO_OER);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल व्योम at91_gpio_dbg_show(काष्ठा seq_file *s, काष्ठा gpio_chip *chip)
अणु
	क्रमागत at91_mux mode;
	पूर्णांक i;
	काष्ठा at91_gpio_chip *at91_gpio = gpiochip_get_data(chip);
	व्योम __iomem *pio = at91_gpio->regbase;
	स्थिर अक्षर *gpio_label;

	क्रम_each_requested_gpio(chip, i, gpio_label) अणु
		अचिन्हित mask = pin_to_mask(i);

		mode = at91_gpio->ops->get_periph(pio, mask);
		seq_म_लिखो(s, "[%s] GPIO%s%d: ",
			   gpio_label, chip->label, i);
		अगर (mode == AT91_MUX_GPIO) अणु
			seq_म_लिखो(s, "[gpio] ");
			seq_म_लिखो(s, "%s ",
				      पढ़ोl_relaxed(pio + PIO_OSR) & mask ?
				      "output" : "input");
			seq_म_लिखो(s, "%s\n",
				      पढ़ोl_relaxed(pio + PIO_PDSR) & mask ?
				      "set" : "clear");
		पूर्ण अन्यथा अणु
			seq_म_लिखो(s, "[periph %c]\n",
				   mode + 'A' - 1);
		पूर्ण
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा at91_gpio_dbg_show	शून्य
#पूर्ण_अगर

/* Several AIC controller irqs are dispatched through this GPIO handler.
 * To use any AT91_PIN_* as an बाह्यally triggered IRQ, first call
 * at91_set_gpio_input() then maybe enable its glitch filter.
 * Then just request_irq() with the pin ID; it works like any ARM IRQ
 * handler.
 * First implementation always triggers on rising and falling edges
 * whereas the newer PIO3 can be additionally configured to trigger on
 * level, edge with any polarity.
 *
 * Alternatively, certain pins may be used directly as IRQ0..IRQ6 after
 * configuring them with at91_set_a_periph() or at91_set_b_periph().
 * IRQ0..IRQ6 should be configurable, e.g. level vs edge triggering.
 */

अटल व्योम gpio_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा at91_gpio_chip *at91_gpio = irq_data_get_irq_chip_data(d);
	व्योम __iomem	*pio = at91_gpio->regbase;
	अचिन्हित	mask = 1 << d->hwirq;

	अगर (pio)
		ग_लिखोl_relaxed(mask, pio + PIO_IDR);
पूर्ण

अटल व्योम gpio_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा at91_gpio_chip *at91_gpio = irq_data_get_irq_chip_data(d);
	व्योम __iomem	*pio = at91_gpio->regbase;
	अचिन्हित	mask = 1 << d->hwirq;

	अगर (pio)
		ग_लिखोl_relaxed(mask, pio + PIO_IER);
पूर्ण

अटल पूर्णांक gpio_irq_type(काष्ठा irq_data *d, अचिन्हित type)
अणु
	चयन (type) अणु
	हाल IRQ_TYPE_NONE:
	हाल IRQ_TYPE_EDGE_BOTH:
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/* Alternate irq type क्रम PIO3 support */
अटल पूर्णांक alt_gpio_irq_type(काष्ठा irq_data *d, अचिन्हित type)
अणु
	काष्ठा at91_gpio_chip *at91_gpio = irq_data_get_irq_chip_data(d);
	व्योम __iomem	*pio = at91_gpio->regbase;
	अचिन्हित	mask = 1 << d->hwirq;

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		irq_set_handler_locked(d, handle_simple_irq);
		ग_लिखोl_relaxed(mask, pio + PIO_ESR);
		ग_लिखोl_relaxed(mask, pio + PIO_REHLSR);
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		irq_set_handler_locked(d, handle_simple_irq);
		ग_लिखोl_relaxed(mask, pio + PIO_ESR);
		ग_लिखोl_relaxed(mask, pio + PIO_FELLSR);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		irq_set_handler_locked(d, handle_level_irq);
		ग_लिखोl_relaxed(mask, pio + PIO_LSR);
		ग_लिखोl_relaxed(mask, pio + PIO_FELLSR);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		irq_set_handler_locked(d, handle_level_irq);
		ग_लिखोl_relaxed(mask, pio + PIO_LSR);
		ग_लिखोl_relaxed(mask, pio + PIO_REHLSR);
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		/*
		 * disable additional पूर्णांकerrupt modes:
		 * fall back to शेष behavior
		 */
		irq_set_handler_locked(d, handle_simple_irq);
		ग_लिखोl_relaxed(mask, pio + PIO_AIMDR);
		वापस 0;
	हाल IRQ_TYPE_NONE:
	शेष:
		pr_warn("AT91: No type for GPIO irq offset %d\n", d->irq);
		वापस -EINVAL;
	पूर्ण

	/* enable additional पूर्णांकerrupt modes */
	ग_लिखोl_relaxed(mask, pio + PIO_AIMER);

	वापस 0;
पूर्ण

अटल व्योम gpio_irq_ack(काष्ठा irq_data *d)
अणु
	/* the पूर्णांकerrupt is alपढ़ोy cleared beक्रमe by पढ़ोing ISR */
पूर्ण

#अगर_घोषित CONFIG_PM

अटल u32 wakeups[MAX_GPIO_BANKS];
अटल u32 backups[MAX_GPIO_BANKS];

अटल पूर्णांक gpio_irq_set_wake(काष्ठा irq_data *d, अचिन्हित state)
अणु
	काष्ठा at91_gpio_chip *at91_gpio = irq_data_get_irq_chip_data(d);
	अचिन्हित	bank = at91_gpio->pioc_idx;
	अचिन्हित mask = 1 << d->hwirq;

	अगर (unlikely(bank >= MAX_GPIO_BANKS))
		वापस -EINVAL;

	अगर (state)
		wakeups[bank] |= mask;
	अन्यथा
		wakeups[bank] &= ~mask;

	irq_set_irq_wake(at91_gpio->pioc_virq, state);

	वापस 0;
पूर्ण

व्योम at91_pinctrl_gpio_suspend(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < gpio_banks; i++) अणु
		व्योम __iomem  *pio;

		अगर (!gpio_chips[i])
			जारी;

		pio = gpio_chips[i]->regbase;

		backups[i] = पढ़ोl_relaxed(pio + PIO_IMR);
		ग_लिखोl_relaxed(backups[i], pio + PIO_IDR);
		ग_लिखोl_relaxed(wakeups[i], pio + PIO_IER);

		अगर (!wakeups[i])
			clk_disable_unprepare(gpio_chips[i]->घड़ी);
		अन्यथा
			prपूर्णांकk(KERN_DEBUG "GPIO-%c may wake for %08x\n",
			       'A'+i, wakeups[i]);
	पूर्ण
पूर्ण

व्योम at91_pinctrl_gpio_resume(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < gpio_banks; i++) अणु
		व्योम __iomem  *pio;

		अगर (!gpio_chips[i])
			जारी;

		pio = gpio_chips[i]->regbase;

		अगर (!wakeups[i])
			clk_prepare_enable(gpio_chips[i]->घड़ी);

		ग_लिखोl_relaxed(wakeups[i], pio + PIO_IDR);
		ग_लिखोl_relaxed(backups[i], pio + PIO_IER);
	पूर्ण
पूर्ण

#अन्यथा
#घोषणा gpio_irq_set_wake	शून्य
#पूर्ण_अगर /* CONFIG_PM */

अटल व्योम gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा gpio_chip *gpio_chip = irq_desc_get_handler_data(desc);
	काष्ठा at91_gpio_chip *at91_gpio = gpiochip_get_data(gpio_chip);
	व्योम __iomem	*pio = at91_gpio->regbase;
	अचिन्हित दीर्घ	isr;
	पूर्णांक		n;

	chained_irq_enter(chip, desc);
	क्रम (;;) अणु
		/* Reading ISR acks pending (edge triggered) GPIO पूर्णांकerrupts.
		 * When there are none pending, we're finished unless we need
		 * to process multiple banks (like ID_PIOCDE on sam9263).
		 */
		isr = पढ़ोl_relaxed(pio + PIO_ISR) & पढ़ोl_relaxed(pio + PIO_IMR);
		अगर (!isr) अणु
			अगर (!at91_gpio->next)
				अवरोध;
			at91_gpio = at91_gpio->next;
			pio = at91_gpio->regbase;
			gpio_chip = &at91_gpio->chip;
			जारी;
		पूर्ण

		क्रम_each_set_bit(n, &isr, BITS_PER_LONG) अणु
			generic_handle_irq(irq_find_mapping(
					   gpio_chip->irq.करोमुख्य, n));
		पूर्ण
	पूर्ण
	chained_irq_निकास(chip, desc);
	/* now it may re-trigger */
पूर्ण

अटल पूर्णांक at91_gpio_of_irq_setup(काष्ठा platक्रमm_device *pdev,
				  काष्ठा at91_gpio_chip *at91_gpio)
अणु
	काष्ठा gpio_chip	*gpiochip_prev = शून्य;
	काष्ठा at91_gpio_chip   *prev = शून्य;
	काष्ठा irq_data		*d = irq_get_irq_data(at91_gpio->pioc_virq);
	काष्ठा irq_chip		*gpio_irqchip;
	काष्ठा gpio_irq_chip	*girq;
	पूर्णांक i;

	gpio_irqchip = devm_kzalloc(&pdev->dev, माप(*gpio_irqchip),
				    GFP_KERNEL);
	अगर (!gpio_irqchip)
		वापस -ENOMEM;

	at91_gpio->pioc_hwirq = irqd_to_hwirq(d);

	gpio_irqchip->name = "GPIO";
	gpio_irqchip->irq_ack = gpio_irq_ack;
	gpio_irqchip->irq_disable = gpio_irq_mask;
	gpio_irqchip->irq_mask = gpio_irq_mask;
	gpio_irqchip->irq_unmask = gpio_irq_unmask;
	gpio_irqchip->irq_set_wake = gpio_irq_set_wake;
	gpio_irqchip->irq_set_type = at91_gpio->ops->irq_type;

	/* Disable irqs of this PIO controller */
	ग_लिखोl_relaxed(~0, at91_gpio->regbase + PIO_IDR);

	/*
	 * Let the generic code handle this edge IRQ, the the chained
	 * handler will perक्रमm the actual work of handling the parent
	 * पूर्णांकerrupt.
	 */
	girq = &at91_gpio->chip.irq;
	girq->chip = gpio_irqchip;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_edge_irq;

	/*
	 * The top level handler handles one bank of GPIOs, except
	 * on some SoC it can handle up to three...
	 * We only set up the handler क्रम the first of the list.
	 */
	gpiochip_prev = irq_get_handler_data(at91_gpio->pioc_virq);
	अगर (!gpiochip_prev) अणु
		girq->parent_handler = gpio_irq_handler;
		girq->num_parents = 1;
		girq->parents = devm_kसुस्मृति(&pdev->dev, 1,
					     माप(*girq->parents),
					     GFP_KERNEL);
		अगर (!girq->parents)
			वापस -ENOMEM;
		girq->parents[0] = at91_gpio->pioc_virq;
		वापस 0;
	पूर्ण

	prev = gpiochip_get_data(gpiochip_prev);
	/* we can only have 2 banks beक्रमe */
	क्रम (i = 0; i < 2; i++) अणु
		अगर (prev->next) अणु
			prev = prev->next;
		पूर्ण अन्यथा अणु
			prev->next = at91_gpio;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

/* This काष्ठाure is replicated क्रम each GPIO block allocated at probe समय */
अटल स्थिर काष्ठा gpio_chip at91_gpio_ढाँचा = अणु
	.request		= gpiochip_generic_request,
	.मुक्त			= gpiochip_generic_मुक्त,
	.get_direction		= at91_gpio_get_direction,
	.direction_input	= at91_gpio_direction_input,
	.get			= at91_gpio_get,
	.direction_output	= at91_gpio_direction_output,
	.set			= at91_gpio_set,
	.set_multiple		= at91_gpio_set_multiple,
	.dbg_show		= at91_gpio_dbg_show,
	.can_sleep		= false,
	.ngpio			= MAX_NB_GPIO_PER_BANK,
पूर्ण;

अटल स्थिर काष्ठा of_device_id at91_gpio_of_match[] = अणु
	अणु .compatible = "atmel,at91sam9x5-gpio", .data = &at91sam9x5_ops, पूर्ण,
	अणु .compatible = "atmel,at91rm9200-gpio", .data = &at91rm9200_ops पूर्ण,
	अणु .compatible = "microchip,sam9x60-gpio", .data = &sam9x60_ops पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक at91_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा at91_gpio_chip *at91_chip = शून्य;
	काष्ठा gpio_chip *chip;
	काष्ठा pinctrl_gpio_range *range;
	पूर्णांक ret = 0;
	पूर्णांक irq, i;
	पूर्णांक alias_idx = of_alias_get_id(np, "gpio");
	uपूर्णांक32_t ngpio;
	अक्षर **names;

	BUG_ON(alias_idx >= ARRAY_SIZE(gpio_chips));
	अगर (gpio_chips[alias_idx]) अणु
		ret = -EBUSY;
		जाओ err;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = irq;
		जाओ err;
	पूर्ण

	at91_chip = devm_kzalloc(&pdev->dev, माप(*at91_chip), GFP_KERNEL);
	अगर (!at91_chip) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	at91_chip->regbase = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(at91_chip->regbase)) अणु
		ret = PTR_ERR(at91_chip->regbase);
		जाओ err;
	पूर्ण

	at91_chip->ops = (काष्ठा at91_pinctrl_mux_ops *)
		of_match_device(at91_gpio_of_match, &pdev->dev)->data;
	at91_chip->pioc_virq = irq;
	at91_chip->pioc_idx = alias_idx;

	at91_chip->घड़ी = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(at91_chip->घड़ी)) अणु
		dev_err(&pdev->dev, "failed to get clock, ignoring.\n");
		ret = PTR_ERR(at91_chip->घड़ी);
		जाओ err;
	पूर्ण

	ret = clk_prepare_enable(at91_chip->घड़ी);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to prepare and enable clock, ignoring.\n");
		जाओ clk_enable_err;
	पूर्ण

	at91_chip->chip = at91_gpio_ढाँचा;

	chip = &at91_chip->chip;
	chip->of_node = np;
	chip->label = dev_name(&pdev->dev);
	chip->parent = &pdev->dev;
	chip->owner = THIS_MODULE;
	chip->base = alias_idx * MAX_NB_GPIO_PER_BANK;

	अगर (!of_property_पढ़ो_u32(np, "#gpio-lines", &ngpio)) अणु
		अगर (ngpio >= MAX_NB_GPIO_PER_BANK)
			pr_err("at91_gpio.%d, gpio-nb >= %d failback to %d\n",
			       alias_idx, MAX_NB_GPIO_PER_BANK, MAX_NB_GPIO_PER_BANK);
		अन्यथा
			chip->ngpio = ngpio;
	पूर्ण

	names = devm_kसुस्मृति(&pdev->dev, chip->ngpio, माप(अक्षर *),
			     GFP_KERNEL);

	अगर (!names) अणु
		ret = -ENOMEM;
		जाओ clk_enable_err;
	पूर्ण

	क्रम (i = 0; i < chip->ngpio; i++)
		names[i] = kaप्र_लिखो(GFP_KERNEL, "pio%c%d", alias_idx + 'A', i);

	chip->names = (स्थिर अक्षर *स्थिर *)names;

	range = &at91_chip->range;
	range->name = chip->label;
	range->id = alias_idx;
	range->pin_base = range->base = range->id * MAX_NB_GPIO_PER_BANK;

	range->npins = chip->ngpio;
	range->gc = chip;

	ret = at91_gpio_of_irq_setup(pdev, at91_chip);
	अगर (ret)
		जाओ gpiochip_add_err;

	ret = gpiochip_add_data(chip, at91_chip);
	अगर (ret)
		जाओ gpiochip_add_err;

	gpio_chips[alias_idx] = at91_chip;
	gpio_banks = max(gpio_banks, alias_idx + 1);

	dev_info(&pdev->dev, "at address %p\n", at91_chip->regbase);

	वापस 0;

gpiochip_add_err:
clk_enable_err:
	clk_disable_unprepare(at91_chip->घड़ी);
err:
	dev_err(&pdev->dev, "Failure %i for GPIO %i\n", ret, alias_idx);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver at91_gpio_driver = अणु
	.driver = अणु
		.name = "gpio-at91",
		.of_match_table = at91_gpio_of_match,
	पूर्ण,
	.probe = at91_gpio_probe,
पूर्ण;

अटल काष्ठा platक्रमm_driver at91_pinctrl_driver = अणु
	.driver = अणु
		.name = "pinctrl-at91",
		.of_match_table = at91_pinctrl_of_match,
	पूर्ण,
	.probe = at91_pinctrl_probe,
पूर्ण;

अटल काष्ठा platक्रमm_driver * स्थिर drivers[] = अणु
	&at91_gpio_driver,
	&at91_pinctrl_driver,
पूर्ण;

अटल पूर्णांक __init at91_pinctrl_init(व्योम)
अणु
	वापस platक्रमm_रेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण
arch_initcall(at91_pinctrl_init);
