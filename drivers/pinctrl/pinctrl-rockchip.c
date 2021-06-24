<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Pinctrl driver क्रम Rockchip SoCs
 *
 * Copyright (c) 2013 MunकरोReader S.L.
 * Author: Heiko Stuebner <heiko@sntech.de>
 *
 * With some ideas taken from pinctrl-samsung:
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 * Copyright (c) 2012 Linaro Ltd
 *		https://www.linaro.org
 *
 * and pinctrl-at91:
 * Copyright (C) 2011-2012 Jean-Christophe PLAGNIOL-VILLARD <plagnioj@jcrosoft.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/bitops.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pinctrl/machine.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/clk.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <dt-bindings/pinctrl/rockchip.h>

#समावेश "core.h"
#समावेश "pinconf.h"

/* GPIO control रेजिस्टरs */
#घोषणा GPIO_SWPORT_DR		0x00
#घोषणा GPIO_SWPORT_DDR		0x04
#घोषणा GPIO_INTEN		0x30
#घोषणा GPIO_INTMASK		0x34
#घोषणा GPIO_INTTYPE_LEVEL	0x38
#घोषणा GPIO_INT_POLARITY	0x3c
#घोषणा GPIO_INT_STATUS		0x40
#घोषणा GPIO_INT_RAWSTATUS	0x44
#घोषणा GPIO_DEBOUNCE		0x48
#घोषणा GPIO_PORTS_EOI		0x4c
#घोषणा GPIO_EXT_PORT		0x50
#घोषणा GPIO_LS_SYNC		0x60

क्रमागत rockchip_pinctrl_type अणु
	PX30,
	RV1108,
	RK2928,
	RK3066B,
	RK3128,
	RK3188,
	RK3288,
	RK3308,
	RK3368,
	RK3399,
	RK3568,
पूर्ण;


/**
 * Generate a biपंचांगask क्रम setting a value (v) with a ग_लिखो mask bit in hiword
 * रेजिस्टर 31:16 area.
 */
#घोषणा WRITE_MASK_VAL(h, l, v) \
	(GENMASK(((h) + 16), ((l) + 16)) | (((v) << (l)) & GENMASK((h), (l))))

/*
 * Encode variants of iomux रेजिस्टरs पूर्णांकo a type variable
 */
#घोषणा IOMUX_GPIO_ONLY		BIT(0)
#घोषणा IOMUX_WIDTH_4BIT	BIT(1)
#घोषणा IOMUX_SOURCE_PMU	BIT(2)
#घोषणा IOMUX_UNROUTED		BIT(3)
#घोषणा IOMUX_WIDTH_3BIT	BIT(4)
#घोषणा IOMUX_WIDTH_2BIT	BIT(5)

/**
 * काष्ठा rockchip_iomux
 * @type: iomux variant using IOMUX_* स्थिरants
 * @offset: अगर initialized to -1 it will be स्वतःcalculated, by specअगरying
 *	    an initial offset value the relevant source offset can be reset
 *	    to a new value क्रम स्वतःcalculating the following iomux रेजिस्टरs.
 */
काष्ठा rockchip_iomux अणु
	पूर्णांक				type;
	पूर्णांक				offset;
पूर्ण;

/*
 * क्रमागत type index corresponding to rockchip_perpin_drv_list arrays index.
 */
क्रमागत rockchip_pin_drv_type अणु
	DRV_TYPE_IO_DEFAULT = 0,
	DRV_TYPE_IO_1V8_OR_3V0,
	DRV_TYPE_IO_1V8_ONLY,
	DRV_TYPE_IO_1V8_3V0_AUTO,
	DRV_TYPE_IO_3V3_ONLY,
	DRV_TYPE_MAX
पूर्ण;

/*
 * क्रमागत type index corresponding to rockchip_pull_list arrays index.
 */
क्रमागत rockchip_pin_pull_type अणु
	PULL_TYPE_IO_DEFAULT = 0,
	PULL_TYPE_IO_1V8_ONLY,
	PULL_TYPE_MAX
पूर्ण;

/**
 * काष्ठा rockchip_drv
 * @drv_type: drive strength variant using rockchip_perpin_drv_type
 * @offset: अगर initialized to -1 it will be स्वतःcalculated, by specअगरying
 *	    an initial offset value the relevant source offset can be reset
 *	    to a new value क्रम स्वतःcalculating the following drive strength
 *	    रेजिस्टरs. अगर used chips own cal_drv func instead to calculate
 *	    रेजिस्टरs offset, the variant could be ignored.
 */
काष्ठा rockchip_drv अणु
	क्रमागत rockchip_pin_drv_type	drv_type;
	पूर्णांक				offset;
पूर्ण;

/**
 * काष्ठा rockchip_pin_bank
 * @reg_base: रेजिस्टर base of the gpio bank
 * @regmap_pull: optional separate रेजिस्टर क्रम additional pull settings
 * @clk: घड़ी of the gpio bank
 * @irq: पूर्णांकerrupt of the gpio bank
 * @saved_masks: Saved content of GPIO_INTEN at suspend समय.
 * @pin_base: first pin number
 * @nr_pins: number of pins in this bank
 * @name: name of the bank
 * @bank_num: number of the bank, to account क्रम holes
 * @iomux: array describing the 4 iomux sources of the bank
 * @drv: array describing the 4 drive strength sources of the bank
 * @pull_type: array describing the 4 pull type sources of the bank
 * @valid: is all necessary inक्रमmation present
 * @of_node: dt node of this bank
 * @drvdata: common pinctrl basedata
 * @करोमुख्य: irqकरोमुख्य of the gpio bank
 * @gpio_chip: gpiolib chip
 * @grange: gpio range
 * @slock: spinlock क्रम the gpio bank
 * @toggle_edge_mode: bit mask to toggle (falling/rising) edge mode
 * @recalced_mask: bit mask to indicate a need to recalulate the mask
 * @route_mask: bits describing the routing pins of per bank
 */
काष्ठा rockchip_pin_bank अणु
	व्योम __iomem			*reg_base;
	काष्ठा regmap			*regmap_pull;
	काष्ठा clk			*clk;
	पूर्णांक				irq;
	u32				saved_masks;
	u32				pin_base;
	u8				nr_pins;
	अक्षर				*name;
	u8				bank_num;
	काष्ठा rockchip_iomux		iomux[4];
	काष्ठा rockchip_drv		drv[4];
	क्रमागत rockchip_pin_pull_type	pull_type[4];
	bool				valid;
	काष्ठा device_node		*of_node;
	काष्ठा rockchip_pinctrl		*drvdata;
	काष्ठा irq_करोमुख्य		*करोमुख्य;
	काष्ठा gpio_chip		gpio_chip;
	काष्ठा pinctrl_gpio_range	grange;
	raw_spinlock_t			slock;
	u32				toggle_edge_mode;
	u32				recalced_mask;
	u32				route_mask;
पूर्ण;

#घोषणा PIN_BANK(id, pins, label)			\
	अणु						\
		.bank_num	= id,			\
		.nr_pins	= pins,			\
		.name		= label,		\
		.iomux		= अणु			\
			अणु .offset = -1 पूर्ण,		\
			अणु .offset = -1 पूर्ण,		\
			अणु .offset = -1 पूर्ण,		\
			अणु .offset = -1 पूर्ण,		\
		पूर्ण,					\
	पूर्ण

#घोषणा PIN_BANK_IOMUX_FLAGS(id, pins, label, iom0, iom1, iom2, iom3)	\
	अणु								\
		.bank_num	= id,					\
		.nr_pins	= pins,					\
		.name		= label,				\
		.iomux		= अणु					\
			अणु .type = iom0, .offset = -1 पूर्ण,			\
			अणु .type = iom1, .offset = -1 पूर्ण,			\
			अणु .type = iom2, .offset = -1 पूर्ण,			\
			अणु .type = iom3, .offset = -1 पूर्ण,			\
		पूर्ण,							\
	पूर्ण

#घोषणा PIN_BANK_DRV_FLAGS(id, pins, label, type0, type1, type2, type3) \
	अणु								\
		.bank_num	= id,					\
		.nr_pins	= pins,					\
		.name		= label,				\
		.iomux		= अणु					\
			अणु .offset = -1 पूर्ण,				\
			अणु .offset = -1 पूर्ण,				\
			अणु .offset = -1 पूर्ण,				\
			अणु .offset = -1 पूर्ण,				\
		पूर्ण,							\
		.drv		= अणु					\
			अणु .drv_type = type0, .offset = -1 पूर्ण,		\
			अणु .drv_type = type1, .offset = -1 पूर्ण,		\
			अणु .drv_type = type2, .offset = -1 पूर्ण,		\
			अणु .drv_type = type3, .offset = -1 पूर्ण,		\
		पूर्ण,							\
	पूर्ण

#घोषणा PIN_BANK_DRV_FLAGS_PULL_FLAGS(id, pins, label, drv0, drv1,	\
				      drv2, drv3, pull0, pull1,		\
				      pull2, pull3)			\
	अणु								\
		.bank_num	= id,					\
		.nr_pins	= pins,					\
		.name		= label,				\
		.iomux		= अणु					\
			अणु .offset = -1 पूर्ण,				\
			अणु .offset = -1 पूर्ण,				\
			अणु .offset = -1 पूर्ण,				\
			अणु .offset = -1 पूर्ण,				\
		पूर्ण,							\
		.drv		= अणु					\
			अणु .drv_type = drv0, .offset = -1 पूर्ण,		\
			अणु .drv_type = drv1, .offset = -1 पूर्ण,		\
			अणु .drv_type = drv2, .offset = -1 पूर्ण,		\
			अणु .drv_type = drv3, .offset = -1 पूर्ण,		\
		पूर्ण,							\
		.pull_type[0] = pull0,					\
		.pull_type[1] = pull1,					\
		.pull_type[2] = pull2,					\
		.pull_type[3] = pull3,					\
	पूर्ण

#घोषणा PIN_BANK_IOMUX_DRV_FLAGS_OFFSET(id, pins, label, iom0, iom1,	\
					iom2, iom3, drv0, drv1, drv2,	\
					drv3, offset0, offset1,		\
					offset2, offset3)		\
	अणु								\
		.bank_num	= id,					\
		.nr_pins	= pins,					\
		.name		= label,				\
		.iomux		= अणु					\
			अणु .type = iom0, .offset = -1 पूर्ण,			\
			अणु .type = iom1, .offset = -1 पूर्ण,			\
			अणु .type = iom2, .offset = -1 पूर्ण,			\
			अणु .type = iom3, .offset = -1 पूर्ण,			\
		पूर्ण,							\
		.drv		= अणु					\
			अणु .drv_type = drv0, .offset = offset0 पूर्ण,	\
			अणु .drv_type = drv1, .offset = offset1 पूर्ण,	\
			अणु .drv_type = drv2, .offset = offset2 पूर्ण,	\
			अणु .drv_type = drv3, .offset = offset3 पूर्ण,	\
		पूर्ण,							\
	पूर्ण

#घोषणा PIN_BANK_IOMUX_FLAGS_DRV_FLAGS_OFFSET_PULL_FLAGS(id, pins,	\
					      label, iom0, iom1, iom2,  \
					      iom3, drv0, drv1, drv2,   \
					      drv3, offset0, offset1,   \
					      offset2, offset3, pull0,  \
					      pull1, pull2, pull3)	\
	अणु								\
		.bank_num	= id,					\
		.nr_pins	= pins,					\
		.name		= label,				\
		.iomux		= अणु					\
			अणु .type = iom0, .offset = -1 पूर्ण,			\
			अणु .type = iom1, .offset = -1 पूर्ण,			\
			अणु .type = iom2, .offset = -1 पूर्ण,			\
			अणु .type = iom3, .offset = -1 पूर्ण,			\
		पूर्ण,							\
		.drv		= अणु					\
			अणु .drv_type = drv0, .offset = offset0 पूर्ण,	\
			अणु .drv_type = drv1, .offset = offset1 पूर्ण,	\
			अणु .drv_type = drv2, .offset = offset2 पूर्ण,	\
			अणु .drv_type = drv3, .offset = offset3 पूर्ण,	\
		पूर्ण,							\
		.pull_type[0] = pull0,					\
		.pull_type[1] = pull1,					\
		.pull_type[2] = pull2,					\
		.pull_type[3] = pull3,					\
	पूर्ण

#घोषणा PIN_BANK_MUX_ROUTE_FLAGS(ID, PIN, FUNC, REG, VAL, FLAG)		\
	अणु								\
		.bank_num	= ID,					\
		.pin		= PIN,					\
		.func		= FUNC,					\
		.route_offset	= REG,					\
		.route_val	= VAL,					\
		.route_location	= FLAG,					\
	पूर्ण

#घोषणा RK_MUXROUTE_SAME(ID, PIN, FUNC, REG, VAL)	\
	PIN_BANK_MUX_ROUTE_FLAGS(ID, PIN, FUNC, REG, VAL, ROCKCHIP_ROUTE_SAME)

#घोषणा RK_MUXROUTE_GRF(ID, PIN, FUNC, REG, VAL)	\
	PIN_BANK_MUX_ROUTE_FLAGS(ID, PIN, FUNC, REG, VAL, ROCKCHIP_ROUTE_GRF)

#घोषणा RK_MUXROUTE_PMU(ID, PIN, FUNC, REG, VAL)	\
	PIN_BANK_MUX_ROUTE_FLAGS(ID, PIN, FUNC, REG, VAL, ROCKCHIP_ROUTE_PMU)

/**
 * काष्ठा rockchip_mux_recalced_data: represent a pin iomux data.
 * @num: bank number.
 * @pin: pin number.
 * @bit: index at रेजिस्टर.
 * @reg: रेजिस्टर offset.
 * @mask: mask bit
 */
काष्ठा rockchip_mux_recalced_data अणु
	u8 num;
	u8 pin;
	u32 reg;
	u8 bit;
	u8 mask;
पूर्ण;

क्रमागत rockchip_mux_route_location अणु
	ROCKCHIP_ROUTE_SAME = 0,
	ROCKCHIP_ROUTE_PMU,
	ROCKCHIP_ROUTE_GRF,
पूर्ण;

/**
 * काष्ठा rockchip_mux_recalced_data: represent a pin iomux data.
 * @bank_num: bank number.
 * @pin: index at रेजिस्टर or used to calc index.
 * @func: the min pin.
 * @route_location: the mux route location (same, pmu, grf).
 * @route_offset: the max pin.
 * @route_val: the रेजिस्टर offset.
 */
काष्ठा rockchip_mux_route_data अणु
	u8 bank_num;
	u8 pin;
	u8 func;
	क्रमागत rockchip_mux_route_location route_location;
	u32 route_offset;
	u32 route_val;
पूर्ण;

काष्ठा rockchip_pin_ctrl अणु
	काष्ठा rockchip_pin_bank	*pin_banks;
	u32				nr_banks;
	u32				nr_pins;
	अक्षर				*label;
	क्रमागत rockchip_pinctrl_type	type;
	पूर्णांक				grf_mux_offset;
	पूर्णांक				pmu_mux_offset;
	पूर्णांक				grf_drv_offset;
	पूर्णांक				pmu_drv_offset;
	काष्ठा rockchip_mux_recalced_data *iomux_recalced;
	u32				niomux_recalced;
	काष्ठा rockchip_mux_route_data *iomux_routes;
	u32				niomux_routes;

	व्योम	(*pull_calc_reg)(काष्ठा rockchip_pin_bank *bank,
				    पूर्णांक pin_num, काष्ठा regmap **regmap,
				    पूर्णांक *reg, u8 *bit);
	व्योम	(*drv_calc_reg)(काष्ठा rockchip_pin_bank *bank,
				    पूर्णांक pin_num, काष्ठा regmap **regmap,
				    पूर्णांक *reg, u8 *bit);
	पूर्णांक	(*schmitt_calc_reg)(काष्ठा rockchip_pin_bank *bank,
				    पूर्णांक pin_num, काष्ठा regmap **regmap,
				    पूर्णांक *reg, u8 *bit);
पूर्ण;

काष्ठा rockchip_pin_config अणु
	अचिन्हित पूर्णांक		func;
	अचिन्हित दीर्घ		*configs;
	अचिन्हित पूर्णांक		nconfigs;
पूर्ण;

/**
 * काष्ठा rockchip_pin_group: represent group of pins of a pinmux function.
 * @name: name of the pin group, used to lookup the group.
 * @pins: the pins included in this group.
 * @npins: number of pins included in this group.
 * @data: local pin configuration
 */
काष्ठा rockchip_pin_group अणु
	स्थिर अक्षर			*name;
	अचिन्हित पूर्णांक			npins;
	अचिन्हित पूर्णांक			*pins;
	काष्ठा rockchip_pin_config	*data;
पूर्ण;

/**
 * काष्ठा rockchip_pmx_func: represent a pin function.
 * @name: name of the pin function, used to lookup the function.
 * @groups: one or more names of pin groups that provide this function.
 * @ngroups: number of groups included in @groups.
 */
काष्ठा rockchip_pmx_func अणु
	स्थिर अक्षर		*name;
	स्थिर अक्षर		**groups;
	u8			ngroups;
पूर्ण;

काष्ठा rockchip_pinctrl अणु
	काष्ठा regmap			*regmap_base;
	पूर्णांक				reg_size;
	काष्ठा regmap			*regmap_pull;
	काष्ठा regmap			*regmap_pmu;
	काष्ठा device			*dev;
	काष्ठा rockchip_pin_ctrl	*ctrl;
	काष्ठा pinctrl_desc		pctl;
	काष्ठा pinctrl_dev		*pctl_dev;
	काष्ठा rockchip_pin_group	*groups;
	अचिन्हित पूर्णांक			ngroups;
	काष्ठा rockchip_pmx_func	*functions;
	अचिन्हित पूर्णांक			nfunctions;
पूर्ण;

अटल काष्ठा regmap_config rockchip_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
पूर्ण;

अटल अंतरभूत स्थिर काष्ठा rockchip_pin_group *pinctrl_name_to_group(
					स्थिर काष्ठा rockchip_pinctrl *info,
					स्थिर अक्षर *name)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < info->ngroups; i++) अणु
		अगर (!म_भेद(info->groups[i].name, name))
			वापस &info->groups[i];
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * given a pin number that is local to a pin controller, find out the pin bank
 * and the रेजिस्टर base of the pin bank.
 */
अटल काष्ठा rockchip_pin_bank *pin_to_bank(काष्ठा rockchip_pinctrl *info,
								अचिन्हित pin)
अणु
	काष्ठा rockchip_pin_bank *b = info->ctrl->pin_banks;

	जबतक (pin >= (b->pin_base + b->nr_pins))
		b++;

	वापस b;
पूर्ण

अटल काष्ठा rockchip_pin_bank *bank_num_to_bank(
					काष्ठा rockchip_pinctrl *info,
					अचिन्हित num)
अणु
	काष्ठा rockchip_pin_bank *b = info->ctrl->pin_banks;
	पूर्णांक i;

	क्रम (i = 0; i < info->ctrl->nr_banks; i++, b++) अणु
		अगर (b->bank_num == num)
			वापस b;
	पूर्ण

	वापस ERR_PTR(-EINVAL);
पूर्ण

/*
 * Pinctrl_ops handling
 */

अटल पूर्णांक rockchip_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा rockchip_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);

	वापस info->ngroups;
पूर्ण

अटल स्थिर अक्षर *rockchip_get_group_name(काष्ठा pinctrl_dev *pctldev,
							अचिन्हित selector)
अणु
	काष्ठा rockchip_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);

	वापस info->groups[selector].name;
पूर्ण

अटल पूर्णांक rockchip_get_group_pins(काष्ठा pinctrl_dev *pctldev,
				      अचिन्हित selector, स्थिर अचिन्हित **pins,
				      अचिन्हित *npins)
अणु
	काष्ठा rockchip_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);

	अगर (selector >= info->ngroups)
		वापस -EINVAL;

	*pins = info->groups[selector].pins;
	*npins = info->groups[selector].npins;

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
				 काष्ठा device_node *np,
				 काष्ठा pinctrl_map **map, अचिन्हित *num_maps)
अणु
	काष्ठा rockchip_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा rockchip_pin_group *grp;
	काष्ठा pinctrl_map *new_map;
	काष्ठा device_node *parent;
	पूर्णांक map_num = 1;
	पूर्णांक i;

	/*
	 * first find the group of this node and check अगर we need to create
	 * config maps क्रम pins
	 */
	grp = pinctrl_name_to_group(info, np->name);
	अगर (!grp) अणु
		dev_err(info->dev, "unable to find group for node %pOFn\n",
			np);
		वापस -EINVAL;
	पूर्ण

	map_num += grp->npins;

	new_map = kसुस्मृति(map_num, माप(*new_map), GFP_KERNEL);
	अगर (!new_map)
		वापस -ENOMEM;

	*map = new_map;
	*num_maps = map_num;

	/* create mux map */
	parent = of_get_parent(np);
	अगर (!parent) अणु
		kमुक्त(new_map);
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
		new_map[i].data.configs.configs = grp->data[i].configs;
		new_map[i].data.configs.num_configs = grp->data[i].nconfigs;
	पूर्ण

	dev_dbg(pctldev->dev, "maps: function %s group %s num %d\n",
		(*map)->data.mux.function, (*map)->data.mux.group, map_num);

	वापस 0;
पूर्ण

अटल व्योम rockchip_dt_मुक्त_map(काष्ठा pinctrl_dev *pctldev,
				    काष्ठा pinctrl_map *map, अचिन्हित num_maps)
अणु
	kमुक्त(map);
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops rockchip_pctrl_ops = अणु
	.get_groups_count	= rockchip_get_groups_count,
	.get_group_name		= rockchip_get_group_name,
	.get_group_pins		= rockchip_get_group_pins,
	.dt_node_to_map		= rockchip_dt_node_to_map,
	.dt_मुक्त_map		= rockchip_dt_मुक्त_map,
पूर्ण;

/*
 * Hardware access
 */

अटल काष्ठा rockchip_mux_recalced_data rv1108_mux_recalced_data[] = अणु
	अणु
		.num = 1,
		.pin = 0,
		.reg = 0x418,
		.bit = 0,
		.mask = 0x3
	पूर्ण, अणु
		.num = 1,
		.pin = 1,
		.reg = 0x418,
		.bit = 2,
		.mask = 0x3
	पूर्ण, अणु
		.num = 1,
		.pin = 2,
		.reg = 0x418,
		.bit = 4,
		.mask = 0x3
	पूर्ण, अणु
		.num = 1,
		.pin = 3,
		.reg = 0x418,
		.bit = 6,
		.mask = 0x3
	पूर्ण, अणु
		.num = 1,
		.pin = 4,
		.reg = 0x418,
		.bit = 8,
		.mask = 0x3
	पूर्ण, अणु
		.num = 1,
		.pin = 5,
		.reg = 0x418,
		.bit = 10,
		.mask = 0x3
	पूर्ण, अणु
		.num = 1,
		.pin = 6,
		.reg = 0x418,
		.bit = 12,
		.mask = 0x3
	पूर्ण, अणु
		.num = 1,
		.pin = 7,
		.reg = 0x418,
		.bit = 14,
		.mask = 0x3
	पूर्ण, अणु
		.num = 1,
		.pin = 8,
		.reg = 0x41c,
		.bit = 0,
		.mask = 0x3
	पूर्ण, अणु
		.num = 1,
		.pin = 9,
		.reg = 0x41c,
		.bit = 2,
		.mask = 0x3
	पूर्ण,
पूर्ण;

अटल  काष्ठा rockchip_mux_recalced_data rk3128_mux_recalced_data[] = अणु
	अणु
		.num = 2,
		.pin = 20,
		.reg = 0xe8,
		.bit = 0,
		.mask = 0x7
	पूर्ण, अणु
		.num = 2,
		.pin = 21,
		.reg = 0xe8,
		.bit = 4,
		.mask = 0x7
	पूर्ण, अणु
		.num = 2,
		.pin = 22,
		.reg = 0xe8,
		.bit = 8,
		.mask = 0x7
	पूर्ण, अणु
		.num = 2,
		.pin = 23,
		.reg = 0xe8,
		.bit = 12,
		.mask = 0x7
	पूर्ण, अणु
		.num = 2,
		.pin = 24,
		.reg = 0xd4,
		.bit = 12,
		.mask = 0x7
	पूर्ण,
पूर्ण;

अटल काष्ठा rockchip_mux_recalced_data rk3308_mux_recalced_data[] = अणु
	अणु
		.num = 1,
		.pin = 14,
		.reg = 0x28,
		.bit = 12,
		.mask = 0xf
	पूर्ण, अणु
		.num = 1,
		.pin = 15,
		.reg = 0x2c,
		.bit = 0,
		.mask = 0x3
	पूर्ण, अणु
		.num = 1,
		.pin = 18,
		.reg = 0x30,
		.bit = 4,
		.mask = 0xf
	पूर्ण, अणु
		.num = 1,
		.pin = 19,
		.reg = 0x30,
		.bit = 8,
		.mask = 0xf
	पूर्ण, अणु
		.num = 1,
		.pin = 20,
		.reg = 0x30,
		.bit = 12,
		.mask = 0xf
	पूर्ण, अणु
		.num = 1,
		.pin = 21,
		.reg = 0x34,
		.bit = 0,
		.mask = 0xf
	पूर्ण, अणु
		.num = 1,
		.pin = 22,
		.reg = 0x34,
		.bit = 4,
		.mask = 0xf
	पूर्ण, अणु
		.num = 1,
		.pin = 23,
		.reg = 0x34,
		.bit = 8,
		.mask = 0xf
	पूर्ण, अणु
		.num = 3,
		.pin = 12,
		.reg = 0x68,
		.bit = 8,
		.mask = 0xf
	पूर्ण, अणु
		.num = 3,
		.pin = 13,
		.reg = 0x68,
		.bit = 12,
		.mask = 0xf
	पूर्ण, अणु
		.num = 2,
		.pin = 2,
		.reg = 0x608,
		.bit = 0,
		.mask = 0x7
	पूर्ण, अणु
		.num = 2,
		.pin = 3,
		.reg = 0x608,
		.bit = 4,
		.mask = 0x7
	पूर्ण, अणु
		.num = 2,
		.pin = 16,
		.reg = 0x610,
		.bit = 8,
		.mask = 0x7
	पूर्ण, अणु
		.num = 3,
		.pin = 10,
		.reg = 0x610,
		.bit = 0,
		.mask = 0x7
	पूर्ण, अणु
		.num = 3,
		.pin = 11,
		.reg = 0x610,
		.bit = 4,
		.mask = 0x7
	पूर्ण,
पूर्ण;

अटल काष्ठा rockchip_mux_recalced_data rk3328_mux_recalced_data[] = अणु
	अणु
		.num = 2,
		.pin = 12,
		.reg = 0x24,
		.bit = 8,
		.mask = 0x3
	पूर्ण, अणु
		.num = 2,
		.pin = 15,
		.reg = 0x28,
		.bit = 0,
		.mask = 0x7
	पूर्ण, अणु
		.num = 2,
		.pin = 23,
		.reg = 0x30,
		.bit = 14,
		.mask = 0x3
	पूर्ण,
पूर्ण;

अटल व्योम rockchip_get_recalced_mux(काष्ठा rockchip_pin_bank *bank, पूर्णांक pin,
				      पूर्णांक *reg, u8 *bit, पूर्णांक *mask)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;
	काष्ठा rockchip_pin_ctrl *ctrl = info->ctrl;
	काष्ठा rockchip_mux_recalced_data *data;
	पूर्णांक i;

	क्रम (i = 0; i < ctrl->niomux_recalced; i++) अणु
		data = &ctrl->iomux_recalced[i];
		अगर (data->num == bank->bank_num &&
		    data->pin == pin)
			अवरोध;
	पूर्ण

	अगर (i >= ctrl->niomux_recalced)
		वापस;

	*reg = data->reg;
	*mask = data->mask;
	*bit = data->bit;
पूर्ण

अटल काष्ठा rockchip_mux_route_data px30_mux_route_data[] = अणु
	RK_MUXROUTE_SAME(2, RK_PA0, 1, 0x184, BIT(16 + 7)), /* cअगर-d2m0 */
	RK_MUXROUTE_SAME(3, RK_PA3, 3, 0x184, BIT(16 + 7) | BIT(7)), /* cअगर-d2m1 */
	RK_MUXROUTE_SAME(3, RK_PC6, 2, 0x184, BIT(16 + 8)), /* pdm-m0 */
	RK_MUXROUTE_SAME(2, RK_PC6, 1, 0x184, BIT(16 + 8) | BIT(8)), /* pdm-m1 */
	RK_MUXROUTE_SAME(1, RK_PD3, 2, 0x184, BIT(16 + 10)), /* uart2-rxm0 */
	RK_MUXROUTE_SAME(2, RK_PB6, 2, 0x184, BIT(16 + 10) | BIT(10)), /* uart2-rxm1 */
	RK_MUXROUTE_SAME(0, RK_PC1, 2, 0x184, BIT(16 + 9)), /* uart3-rxm0 */
	RK_MUXROUTE_SAME(1, RK_PB7, 2, 0x184, BIT(16 + 9) | BIT(9)), /* uart3-rxm1 */
पूर्ण;

अटल काष्ठा rockchip_mux_route_data rk3128_mux_route_data[] = अणु
	RK_MUXROUTE_SAME(1, RK_PB2, 1, 0x144, BIT(16 + 3) | BIT(16 + 4)), /* spi-0 */
	RK_MUXROUTE_SAME(1, RK_PD3, 3, 0x144, BIT(16 + 3) | BIT(16 + 4) | BIT(3)), /* spi-1 */
	RK_MUXROUTE_SAME(0, RK_PB5, 2, 0x144, BIT(16 + 3) | BIT(16 + 4) | BIT(4)), /* spi-2 */
	RK_MUXROUTE_SAME(1, RK_PA5, 1, 0x144, BIT(16 + 5)), /* i2s-0 */
	RK_MUXROUTE_SAME(0, RK_PB6, 1, 0x144, BIT(16 + 5) | BIT(5)), /* i2s-1 */
	RK_MUXROUTE_SAME(1, RK_PC6, 2, 0x144, BIT(16 + 6)), /* emmc-0 */
	RK_MUXROUTE_SAME(2, RK_PA4, 2, 0x144, BIT(16 + 6) | BIT(6)), /* emmc-1 */
पूर्ण;

अटल काष्ठा rockchip_mux_route_data rk3188_mux_route_data[] = अणु
	RK_MUXROUTE_SAME(0, RK_PD0, 1, 0xa0, BIT(16 + 11)), /* non-iomuxed emmc/flash pins on flash-dqs */
	RK_MUXROUTE_SAME(0, RK_PD0, 2, 0xa0, BIT(16 + 11) | BIT(11)), /* non-iomuxed emmc/flash pins on emmc-clk */
पूर्ण;

अटल काष्ठा rockchip_mux_route_data rk3228_mux_route_data[] = अणु
	RK_MUXROUTE_SAME(0, RK_PD2, 1, 0x50, BIT(16)), /* pwm0-0 */
	RK_MUXROUTE_SAME(3, RK_PC5, 1, 0x50, BIT(16) | BIT(0)), /* pwm0-1 */
	RK_MUXROUTE_SAME(0, RK_PD3, 1, 0x50, BIT(16 + 1)), /* pwm1-0 */
	RK_MUXROUTE_SAME(0, RK_PD6, 2, 0x50, BIT(16 + 1) | BIT(1)), /* pwm1-1 */
	RK_MUXROUTE_SAME(0, RK_PD4, 1, 0x50, BIT(16 + 2)), /* pwm2-0 */
	RK_MUXROUTE_SAME(1, RK_PB4, 2, 0x50, BIT(16 + 2) | BIT(2)), /* pwm2-1 */
	RK_MUXROUTE_SAME(3, RK_PD2, 1, 0x50, BIT(16 + 3)), /* pwm3-0 */
	RK_MUXROUTE_SAME(1, RK_PB3, 2, 0x50, BIT(16 + 3) | BIT(3)), /* pwm3-1 */
	RK_MUXROUTE_SAME(1, RK_PA1, 1, 0x50, BIT(16 + 4)), /* sdio-0_d0 */
	RK_MUXROUTE_SAME(3, RK_PA2, 1, 0x50, BIT(16 + 4) | BIT(4)), /* sdio-1_d0 */
	RK_MUXROUTE_SAME(0, RK_PB5, 2, 0x50, BIT(16 + 5)), /* spi-0_rx */
	RK_MUXROUTE_SAME(2, RK_PA0, 2, 0x50, BIT(16 + 5) | BIT(5)), /* spi-1_rx */
	RK_MUXROUTE_SAME(1, RK_PC6, 2, 0x50, BIT(16 + 7)), /* emmc-0_cmd */
	RK_MUXROUTE_SAME(2, RK_PA4, 2, 0x50, BIT(16 + 7) | BIT(7)), /* emmc-1_cmd */
	RK_MUXROUTE_SAME(1, RK_PC3, 2, 0x50, BIT(16 + 8)), /* uart2-0_rx */
	RK_MUXROUTE_SAME(1, RK_PB2, 2, 0x50, BIT(16 + 8) | BIT(8)), /* uart2-1_rx */
	RK_MUXROUTE_SAME(1, RK_PB2, 1, 0x50, BIT(16 + 11)), /* uart1-0_rx */
	RK_MUXROUTE_SAME(3, RK_PB5, 1, 0x50, BIT(16 + 11) | BIT(11)), /* uart1-1_rx */
पूर्ण;

अटल काष्ठा rockchip_mux_route_data rk3288_mux_route_data[] = अणु
	RK_MUXROUTE_SAME(7, RK_PC0, 2, 0x264, BIT(16 + 12) | BIT(12)), /* edphdmi_cecinoutt1 */
	RK_MUXROUTE_SAME(7, RK_PC7, 4, 0x264, BIT(16 + 12)), /* edphdmi_cecinout */
पूर्ण;

अटल काष्ठा rockchip_mux_route_data rk3308_mux_route_data[] = अणु
	RK_MUXROUTE_SAME(0, RK_PC3, 1, 0x314, BIT(16 + 0) | BIT(0)), /* rtc_clk */
	RK_MUXROUTE_SAME(1, RK_PC6, 2, 0x314, BIT(16 + 2) | BIT(16 + 3)), /* uart2_rxm0 */
	RK_MUXROUTE_SAME(4, RK_PD2, 2, 0x314, BIT(16 + 2) | BIT(16 + 3) | BIT(2)), /* uart2_rxm1 */
	RK_MUXROUTE_SAME(0, RK_PB7, 2, 0x608, BIT(16 + 8) | BIT(16 + 9)), /* i2c3_sdam0 */
	RK_MUXROUTE_SAME(3, RK_PB4, 2, 0x608, BIT(16 + 8) | BIT(16 + 9) | BIT(8)), /* i2c3_sdam1 */
	RK_MUXROUTE_SAME(2, RK_PA0, 3, 0x608, BIT(16 + 8) | BIT(16 + 9) | BIT(9)), /* i2c3_sdam2 */
	RK_MUXROUTE_SAME(1, RK_PA3, 2, 0x308, BIT(16 + 3)), /* i2s-8ch-1-sclktxm0 */
	RK_MUXROUTE_SAME(1, RK_PA4, 2, 0x308, BIT(16 + 3)), /* i2s-8ch-1-sclkrxm0 */
	RK_MUXROUTE_SAME(1, RK_PB5, 2, 0x308, BIT(16 + 3) | BIT(3)), /* i2s-8ch-1-sclktxm1 */
	RK_MUXROUTE_SAME(1, RK_PB6, 2, 0x308, BIT(16 + 3) | BIT(3)), /* i2s-8ch-1-sclkrxm1 */
	RK_MUXROUTE_SAME(1, RK_PA4, 3, 0x308, BIT(16 + 12) | BIT(16 + 13)), /* pdm-clkm0 */
	RK_MUXROUTE_SAME(1, RK_PB6, 4, 0x308, BIT(16 + 12) | BIT(16 + 13) | BIT(12)), /* pdm-clkm1 */
	RK_MUXROUTE_SAME(2, RK_PA6, 2, 0x308, BIT(16 + 12) | BIT(16 + 13) | BIT(13)), /* pdm-clkm2 */
	RK_MUXROUTE_SAME(2, RK_PA4, 3, 0x600, BIT(16 + 2) | BIT(2)), /* pdm-clkm-m2 */
	RK_MUXROUTE_SAME(3, RK_PB2, 3, 0x314, BIT(16 + 9)), /* spi1_miso */
	RK_MUXROUTE_SAME(2, RK_PA4, 2, 0x314, BIT(16 + 9) | BIT(9)), /* spi1_miso_m1 */
	RK_MUXROUTE_SAME(0, RK_PB3, 3, 0x314, BIT(16 + 10) | BIT(16 + 11)), /* owire_m0 */
	RK_MUXROUTE_SAME(1, RK_PC6, 7, 0x314, BIT(16 + 10) | BIT(16 + 11) | BIT(10)), /* owire_m1 */
	RK_MUXROUTE_SAME(2, RK_PA2, 5, 0x314, BIT(16 + 10) | BIT(16 + 11) | BIT(11)), /* owire_m2 */
	RK_MUXROUTE_SAME(0, RK_PB3, 2, 0x314, BIT(16 + 12) | BIT(16 + 13)), /* can_rxd_m0 */
	RK_MUXROUTE_SAME(1, RK_PC6, 5, 0x314, BIT(16 + 12) | BIT(16 + 13) | BIT(12)), /* can_rxd_m1 */
	RK_MUXROUTE_SAME(2, RK_PA2, 4, 0x314, BIT(16 + 12) | BIT(16 + 13) | BIT(13)), /* can_rxd_m2 */
	RK_MUXROUTE_SAME(1, RK_PC4, 3, 0x314, BIT(16 + 14)), /* mac_rxd0_m0 */
	RK_MUXROUTE_SAME(4, RK_PA2, 2, 0x314, BIT(16 + 14) | BIT(14)), /* mac_rxd0_m1 */
	RK_MUXROUTE_SAME(3, RK_PB4, 4, 0x314, BIT(16 + 15)), /* uart3_rx */
	RK_MUXROUTE_SAME(0, RK_PC1, 3, 0x314, BIT(16 + 15) | BIT(15)), /* uart3_rx_m1 */
पूर्ण;

अटल काष्ठा rockchip_mux_route_data rk3328_mux_route_data[] = अणु
	RK_MUXROUTE_SAME(1, RK_PA1, 2, 0x50, BIT(16) | BIT(16 + 1)), /* uart2dbg_rxm0 */
	RK_MUXROUTE_SAME(2, RK_PA1, 1, 0x50, BIT(16) | BIT(16 + 1) | BIT(0)), /* uart2dbg_rxm1 */
	RK_MUXROUTE_SAME(1, RK_PB3, 2, 0x50, BIT(16 + 2) | BIT(2)), /* gmac-m1_rxd0 */
	RK_MUXROUTE_SAME(1, RK_PB6, 2, 0x50, BIT(16 + 10) | BIT(10)), /* gmac-m1-optimized_rxd3 */
	RK_MUXROUTE_SAME(2, RK_PC3, 2, 0x50, BIT(16 + 3)), /* pdm_sdi0m0 */
	RK_MUXROUTE_SAME(1, RK_PC7, 3, 0x50, BIT(16 + 3) | BIT(3)), /* pdm_sdi0m1 */
	RK_MUXROUTE_SAME(3, RK_PA2, 4, 0x50, BIT(16 + 4) | BIT(16 + 5) | BIT(5)), /* spi_rxdm2 */
	RK_MUXROUTE_SAME(1, RK_PD0, 1, 0x50, BIT(16 + 6)), /* i2s2_sdim0 */
	RK_MUXROUTE_SAME(3, RK_PA2, 6, 0x50, BIT(16 + 6) | BIT(6)), /* i2s2_sdim1 */
	RK_MUXROUTE_SAME(2, RK_PC6, 3, 0x50, BIT(16 + 7) | BIT(7)), /* card_iom1 */
	RK_MUXROUTE_SAME(2, RK_PC0, 3, 0x50, BIT(16 + 8) | BIT(8)), /* tsp_d5m1 */
	RK_MUXROUTE_SAME(2, RK_PC0, 4, 0x50, BIT(16 + 9) | BIT(9)), /* cअगर_data5m1 */
पूर्ण;

अटल काष्ठा rockchip_mux_route_data rk3399_mux_route_data[] = अणु
	RK_MUXROUTE_SAME(4, RK_PB0, 2, 0xe21c, BIT(16 + 10) | BIT(16 + 11)), /* uart2dbga_rx */
	RK_MUXROUTE_SAME(4, RK_PC0, 2, 0xe21c, BIT(16 + 10) | BIT(16 + 11) | BIT(10)), /* uart2dbgb_rx */
	RK_MUXROUTE_SAME(4, RK_PC3, 1, 0xe21c, BIT(16 + 10) | BIT(16 + 11) | BIT(11)), /* uart2dbgc_rx */
	RK_MUXROUTE_SAME(2, RK_PD2, 2, 0xe21c, BIT(16 + 14)), /* pcie_clkreqn */
	RK_MUXROUTE_SAME(4, RK_PD0, 1, 0xe21c, BIT(16 + 14) | BIT(14)), /* pcie_clkreqnb */
पूर्ण;

अटल काष्ठा rockchip_mux_route_data rk3568_mux_route_data[] = अणु
	RK_MUXROUTE_PMU(0, RK_PB7, 1, 0x0110, WRITE_MASK_VAL(1, 0, 0)), /* PWM0 IO mux M0 */
	RK_MUXROUTE_PMU(0, RK_PC7, 2, 0x0110, WRITE_MASK_VAL(1, 0, 1)), /* PWM0 IO mux M1 */
	RK_MUXROUTE_PMU(0, RK_PC0, 1, 0x0110, WRITE_MASK_VAL(3, 2, 0)), /* PWM1 IO mux M0 */
	RK_MUXROUTE_PMU(0, RK_PB5, 4, 0x0110, WRITE_MASK_VAL(3, 2, 1)), /* PWM1 IO mux M1 */
	RK_MUXROUTE_PMU(0, RK_PC1, 1, 0x0110, WRITE_MASK_VAL(5, 4, 0)), /* PWM2 IO mux M0 */
	RK_MUXROUTE_PMU(0, RK_PB6, 4, 0x0110, WRITE_MASK_VAL(5, 4, 1)), /* PWM2 IO mux M1 */
	RK_MUXROUTE_PMU(0, RK_PB3, 2, 0x0300, WRITE_MASK_VAL(0, 0, 0)), /* CAN0 IO mux M0 */
	RK_MUXROUTE_GRF(2, RK_PA1, 4, 0x0300, WRITE_MASK_VAL(0, 0, 1)), /* CAN0 IO mux M1 */
	RK_MUXROUTE_GRF(1, RK_PA1, 3, 0x0300, WRITE_MASK_VAL(2, 2, 0)), /* CAN1 IO mux M0 */
	RK_MUXROUTE_GRF(4, RK_PC3, 3, 0x0300, WRITE_MASK_VAL(2, 2, 1)), /* CAN1 IO mux M1 */
	RK_MUXROUTE_GRF(4, RK_PB5, 3, 0x0300, WRITE_MASK_VAL(4, 4, 0)), /* CAN2 IO mux M0 */
	RK_MUXROUTE_GRF(2, RK_PB2, 4, 0x0300, WRITE_MASK_VAL(4, 4, 1)), /* CAN2 IO mux M1 */
	RK_MUXROUTE_GRF(4, RK_PC4, 1, 0x0300, WRITE_MASK_VAL(6, 6, 0)), /* HPDIN IO mux M0 */
	RK_MUXROUTE_PMU(0, RK_PC2, 2, 0x0300, WRITE_MASK_VAL(6, 6, 1)), /* HPDIN IO mux M1 */
	RK_MUXROUTE_GRF(3, RK_PB1, 3, 0x0300, WRITE_MASK_VAL(8, 8, 0)), /* GMAC1 IO mux M0 */
	RK_MUXROUTE_GRF(4, RK_PA7, 3, 0x0300, WRITE_MASK_VAL(8, 8, 1)), /* GMAC1 IO mux M1 */
	RK_MUXROUTE_GRF(4, RK_PD1, 1, 0x0300, WRITE_MASK_VAL(10, 10, 0)), /* HDMITX IO mux M0 */
	RK_MUXROUTE_PMU(0, RK_PC7, 1, 0x0300, WRITE_MASK_VAL(10, 10, 1)), /* HDMITX IO mux M1 */
	RK_MUXROUTE_PMU(0, RK_PB6, 1, 0x0300, WRITE_MASK_VAL(14, 14, 0)), /* I2C2 IO mux M0 */
	RK_MUXROUTE_GRF(4, RK_PB4, 1, 0x0300, WRITE_MASK_VAL(14, 14, 1)), /* I2C2 IO mux M1 */
	RK_MUXROUTE_GRF(1, RK_PA0, 1, 0x0304, WRITE_MASK_VAL(0, 0, 0)), /* I2C3 IO mux M0 */
	RK_MUXROUTE_GRF(3, RK_PB6, 4, 0x0304, WRITE_MASK_VAL(0, 0, 1)), /* I2C3 IO mux M1 */
	RK_MUXROUTE_GRF(4, RK_PB2, 1, 0x0304, WRITE_MASK_VAL(2, 2, 0)), /* I2C4 IO mux M0 */
	RK_MUXROUTE_GRF(2, RK_PB1, 2, 0x0304, WRITE_MASK_VAL(2, 2, 1)), /* I2C4 IO mux M1 */
	RK_MUXROUTE_GRF(3, RK_PB4, 4, 0x0304, WRITE_MASK_VAL(4, 4, 0)), /* I2C5 IO mux M0 */
	RK_MUXROUTE_GRF(4, RK_PD0, 2, 0x0304, WRITE_MASK_VAL(4, 4, 1)), /* I2C5 IO mux M1 */
	RK_MUXROUTE_GRF(3, RK_PB1, 5, 0x0304, WRITE_MASK_VAL(14, 14, 0)), /* PWM8 IO mux M0 */
	RK_MUXROUTE_GRF(1, RK_PD5, 4, 0x0304, WRITE_MASK_VAL(14, 14, 1)), /* PWM8 IO mux M1 */
	RK_MUXROUTE_GRF(3, RK_PB2, 5, 0x0308, WRITE_MASK_VAL(0, 0, 0)), /* PWM9 IO mux M0 */
	RK_MUXROUTE_GRF(1, RK_PD6, 4, 0x0308, WRITE_MASK_VAL(0, 0, 1)), /* PWM9 IO mux M1 */
	RK_MUXROUTE_GRF(3, RK_PB5, 5, 0x0308, WRITE_MASK_VAL(2, 2, 0)), /* PWM10 IO mux M0 */
	RK_MUXROUTE_GRF(2, RK_PA1, 2, 0x0308, WRITE_MASK_VAL(2, 2, 1)), /* PWM10 IO mux M1 */
	RK_MUXROUTE_GRF(3, RK_PB6, 5, 0x0308, WRITE_MASK_VAL(4, 4, 0)), /* PWM11 IO mux M0 */
	RK_MUXROUTE_GRF(4, RK_PC0, 3, 0x0308, WRITE_MASK_VAL(4, 4, 1)), /* PWM11 IO mux M1 */
	RK_MUXROUTE_GRF(3, RK_PB7, 2, 0x0308, WRITE_MASK_VAL(6, 6, 0)), /* PWM12 IO mux M0 */
	RK_MUXROUTE_GRF(4, RK_PC5, 1, 0x0308, WRITE_MASK_VAL(6, 6, 1)), /* PWM12 IO mux M1 */
	RK_MUXROUTE_GRF(3, RK_PC0, 2, 0x0308, WRITE_MASK_VAL(8, 8, 0)), /* PWM13 IO mux M0 */
	RK_MUXROUTE_GRF(4, RK_PC6, 1, 0x0308, WRITE_MASK_VAL(8, 8, 1)), /* PWM13 IO mux M1 */
	RK_MUXROUTE_GRF(3, RK_PC4, 1, 0x0308, WRITE_MASK_VAL(10, 10, 0)), /* PWM14 IO mux M0 */
	RK_MUXROUTE_GRF(4, RK_PC2, 1, 0x0308, WRITE_MASK_VAL(10, 10, 1)), /* PWM14 IO mux M1 */
	RK_MUXROUTE_GRF(3, RK_PC5, 1, 0x0308, WRITE_MASK_VAL(12, 12, 0)), /* PWM15 IO mux M0 */
	RK_MUXROUTE_GRF(4, RK_PC3, 1, 0x0308, WRITE_MASK_VAL(12, 12, 1)), /* PWM15 IO mux M1 */
	RK_MUXROUTE_GRF(3, RK_PD2, 3, 0x0308, WRITE_MASK_VAL(14, 14, 0)), /* SDMMC2 IO mux M0 */
	RK_MUXROUTE_GRF(3, RK_PA5, 5, 0x0308, WRITE_MASK_VAL(14, 14, 1)), /* SDMMC2 IO mux M1 */
	RK_MUXROUTE_PMU(0, RK_PB5, 2, 0x030c, WRITE_MASK_VAL(0, 0, 0)), /* SPI0 IO mux M0 */
	RK_MUXROUTE_GRF(2, RK_PD3, 3, 0x030c, WRITE_MASK_VAL(0, 0, 1)), /* SPI0 IO mux M1 */
	RK_MUXROUTE_GRF(2, RK_PB5, 3, 0x030c, WRITE_MASK_VAL(2, 2, 0)), /* SPI1 IO mux M0 */
	RK_MUXROUTE_GRF(3, RK_PC3, 3, 0x030c, WRITE_MASK_VAL(2, 2, 1)), /* SPI1 IO mux M1 */
	RK_MUXROUTE_GRF(2, RK_PC1, 4, 0x030c, WRITE_MASK_VAL(4, 4, 0)), /* SPI2 IO mux M0 */
	RK_MUXROUTE_GRF(3, RK_PA0, 3, 0x030c, WRITE_MASK_VAL(4, 4, 1)), /* SPI2 IO mux M1 */
	RK_MUXROUTE_GRF(4, RK_PB3, 4, 0x030c, WRITE_MASK_VAL(6, 6, 0)), /* SPI3 IO mux M0 */
	RK_MUXROUTE_GRF(4, RK_PC2, 2, 0x030c, WRITE_MASK_VAL(6, 6, 1)), /* SPI3 IO mux M1 */
	RK_MUXROUTE_GRF(2, RK_PB4, 2, 0x030c, WRITE_MASK_VAL(8, 8, 0)), /* UART1 IO mux M0 */
	RK_MUXROUTE_PMU(0, RK_PD1, 1, 0x030c, WRITE_MASK_VAL(8, 8, 1)), /* UART1 IO mux M1 */
	RK_MUXROUTE_PMU(0, RK_PD1, 1, 0x030c, WRITE_MASK_VAL(10, 10, 0)), /* UART2 IO mux M0 */
	RK_MUXROUTE_GRF(1, RK_PD5, 2, 0x030c, WRITE_MASK_VAL(10, 10, 1)), /* UART2 IO mux M1 */
	RK_MUXROUTE_GRF(1, RK_PA1, 2, 0x030c, WRITE_MASK_VAL(12, 12, 0)), /* UART3 IO mux M0 */
	RK_MUXROUTE_GRF(3, RK_PB7, 4, 0x030c, WRITE_MASK_VAL(12, 12, 1)), /* UART3 IO mux M1 */
	RK_MUXROUTE_GRF(1, RK_PA6, 2, 0x030c, WRITE_MASK_VAL(14, 14, 0)), /* UART4 IO mux M0 */
	RK_MUXROUTE_GRF(3, RK_PB2, 4, 0x030c, WRITE_MASK_VAL(14, 14, 1)), /* UART4 IO mux M1 */
	RK_MUXROUTE_GRF(2, RK_PA2, 3, 0x0310, WRITE_MASK_VAL(0, 0, 0)), /* UART5 IO mux M0 */
	RK_MUXROUTE_GRF(3, RK_PC2, 4, 0x0310, WRITE_MASK_VAL(0, 0, 1)), /* UART5 IO mux M1 */
	RK_MUXROUTE_GRF(2, RK_PA4, 3, 0x0310, WRITE_MASK_VAL(2, 2, 0)), /* UART6 IO mux M0 */
	RK_MUXROUTE_GRF(1, RK_PD5, 3, 0x0310, WRITE_MASK_VAL(2, 2, 1)), /* UART6 IO mux M1 */
	RK_MUXROUTE_GRF(2, RK_PA6, 3, 0x0310, WRITE_MASK_VAL(5, 4, 0)), /* UART7 IO mux M0 */
	RK_MUXROUTE_GRF(3, RK_PC4, 4, 0x0310, WRITE_MASK_VAL(5, 4, 1)), /* UART7 IO mux M1 */
	RK_MUXROUTE_GRF(4, RK_PA2, 4, 0x0310, WRITE_MASK_VAL(5, 4, 2)), /* UART7 IO mux M2 */
	RK_MUXROUTE_GRF(2, RK_PC5, 3, 0x0310, WRITE_MASK_VAL(6, 6, 0)), /* UART8 IO mux M0 */
	RK_MUXROUTE_GRF(2, RK_PD7, 4, 0x0310, WRITE_MASK_VAL(6, 6, 1)), /* UART8 IO mux M1 */
	RK_MUXROUTE_GRF(2, RK_PB0, 3, 0x0310, WRITE_MASK_VAL(9, 8, 0)), /* UART9 IO mux M0 */
	RK_MUXROUTE_GRF(4, RK_PC5, 4, 0x0310, WRITE_MASK_VAL(9, 8, 1)), /* UART9 IO mux M1 */
	RK_MUXROUTE_GRF(4, RK_PA4, 4, 0x0310, WRITE_MASK_VAL(9, 8, 2)), /* UART9 IO mux M2 */
	RK_MUXROUTE_GRF(1, RK_PA2, 1, 0x0310, WRITE_MASK_VAL(11, 10, 0)), /* I2S1 IO mux M0 */
	RK_MUXROUTE_GRF(3, RK_PC6, 4, 0x0310, WRITE_MASK_VAL(11, 10, 1)), /* I2S1 IO mux M1 */
	RK_MUXROUTE_GRF(2, RK_PD0, 5, 0x0310, WRITE_MASK_VAL(11, 10, 2)), /* I2S1 IO mux M2 */
	RK_MUXROUTE_GRF(2, RK_PC1, 1, 0x0310, WRITE_MASK_VAL(12, 12, 0)), /* I2S2 IO mux M0 */
	RK_MUXROUTE_GRF(4, RK_PB6, 5, 0x0310, WRITE_MASK_VAL(12, 12, 1)), /* I2S2 IO mux M1 */
	RK_MUXROUTE_GRF(3, RK_PA2, 4, 0x0310, WRITE_MASK_VAL(14, 14, 0)), /* I2S3 IO mux M0 */
	RK_MUXROUTE_GRF(4, RK_PC2, 5, 0x0310, WRITE_MASK_VAL(14, 14, 1)), /* I2S3 IO mux M1 */
	RK_MUXROUTE_GRF(1, RK_PA4, 3, 0x0314, WRITE_MASK_VAL(1, 0, 0)), /* PDM IO mux M0 */
	RK_MUXROUTE_GRF(1, RK_PA6, 3, 0x0314, WRITE_MASK_VAL(1, 0, 0)), /* PDM IO mux M0 */
	RK_MUXROUTE_GRF(3, RK_PD6, 5, 0x0314, WRITE_MASK_VAL(1, 0, 1)), /* PDM IO mux M1 */
	RK_MUXROUTE_GRF(4, RK_PA0, 4, 0x0314, WRITE_MASK_VAL(1, 0, 1)), /* PDM IO mux M1 */
	RK_MUXROUTE_GRF(3, RK_PC4, 5, 0x0314, WRITE_MASK_VAL(1, 0, 2)), /* PDM IO mux M2 */
	RK_MUXROUTE_PMU(0, RK_PA5, 3, 0x0314, WRITE_MASK_VAL(3, 2, 0)), /* PCIE20 IO mux M0 */
	RK_MUXROUTE_GRF(2, RK_PD0, 4, 0x0314, WRITE_MASK_VAL(3, 2, 1)), /* PCIE20 IO mux M1 */
	RK_MUXROUTE_GRF(1, RK_PB0, 4, 0x0314, WRITE_MASK_VAL(3, 2, 2)), /* PCIE20 IO mux M2 */
	RK_MUXROUTE_PMU(0, RK_PA4, 3, 0x0314, WRITE_MASK_VAL(5, 4, 0)), /* PCIE30X1 IO mux M0 */
	RK_MUXROUTE_GRF(2, RK_PD2, 4, 0x0314, WRITE_MASK_VAL(5, 4, 1)), /* PCIE30X1 IO mux M1 */
	RK_MUXROUTE_GRF(1, RK_PA5, 4, 0x0314, WRITE_MASK_VAL(5, 4, 2)), /* PCIE30X1 IO mux M2 */
	RK_MUXROUTE_PMU(0, RK_PA6, 2, 0x0314, WRITE_MASK_VAL(7, 6, 0)), /* PCIE30X2 IO mux M0 */
	RK_MUXROUTE_GRF(2, RK_PD4, 4, 0x0314, WRITE_MASK_VAL(7, 6, 1)), /* PCIE30X2 IO mux M1 */
	RK_MUXROUTE_GRF(4, RK_PC2, 4, 0x0314, WRITE_MASK_VAL(7, 6, 2)), /* PCIE30X2 IO mux M2 */
पूर्ण;

अटल bool rockchip_get_mux_route(काष्ठा rockchip_pin_bank *bank, पूर्णांक pin,
				   पूर्णांक mux, u32 *loc, u32 *reg, u32 *value)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;
	काष्ठा rockchip_pin_ctrl *ctrl = info->ctrl;
	काष्ठा rockchip_mux_route_data *data;
	पूर्णांक i;

	क्रम (i = 0; i < ctrl->niomux_routes; i++) अणु
		data = &ctrl->iomux_routes[i];
		अगर ((data->bank_num == bank->bank_num) &&
		    (data->pin == pin) && (data->func == mux))
			अवरोध;
	पूर्ण

	अगर (i >= ctrl->niomux_routes)
		वापस false;

	*loc = data->route_location;
	*reg = data->route_offset;
	*value = data->route_val;

	वापस true;
पूर्ण

अटल पूर्णांक rockchip_get_mux(काष्ठा rockchip_pin_bank *bank, पूर्णांक pin)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;
	पूर्णांक iomux_num = (pin / 8);
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक val;
	पूर्णांक reg, ret, mask, mux_type;
	u8 bit;

	अगर (iomux_num > 3)
		वापस -EINVAL;

	अगर (bank->iomux[iomux_num].type & IOMUX_UNROUTED) अणु
		dev_err(info->dev, "pin %d is unrouted\n", pin);
		वापस -EINVAL;
	पूर्ण

	अगर (bank->iomux[iomux_num].type & IOMUX_GPIO_ONLY)
		वापस RK_FUNC_GPIO;

	regmap = (bank->iomux[iomux_num].type & IOMUX_SOURCE_PMU)
				? info->regmap_pmu : info->regmap_base;

	/* get basic quadrupel of mux रेजिस्टरs and the correct reg inside */
	mux_type = bank->iomux[iomux_num].type;
	reg = bank->iomux[iomux_num].offset;
	अगर (mux_type & IOMUX_WIDTH_4BIT) अणु
		अगर ((pin % 8) >= 4)
			reg += 0x4;
		bit = (pin % 4) * 4;
		mask = 0xf;
	पूर्ण अन्यथा अगर (mux_type & IOMUX_WIDTH_3BIT) अणु
		अगर ((pin % 8) >= 5)
			reg += 0x4;
		bit = (pin % 8 % 5) * 3;
		mask = 0x7;
	पूर्ण अन्यथा अणु
		bit = (pin % 8) * 2;
		mask = 0x3;
	पूर्ण

	अगर (bank->recalced_mask & BIT(pin))
		rockchip_get_recalced_mux(bank, pin, &reg, &bit, &mask);

	ret = regmap_पढ़ो(regmap, reg, &val);
	अगर (ret)
		वापस ret;

	वापस ((val >> bit) & mask);
पूर्ण

अटल पूर्णांक rockchip_verअगरy_mux(काष्ठा rockchip_pin_bank *bank,
			       पूर्णांक pin, पूर्णांक mux)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;
	पूर्णांक iomux_num = (pin / 8);

	अगर (iomux_num > 3)
		वापस -EINVAL;

	अगर (bank->iomux[iomux_num].type & IOMUX_UNROUTED) अणु
		dev_err(info->dev, "pin %d is unrouted\n", pin);
		वापस -EINVAL;
	पूर्ण

	अगर (bank->iomux[iomux_num].type & IOMUX_GPIO_ONLY) अणु
		अगर (mux != RK_FUNC_GPIO) अणु
			dev_err(info->dev,
				"pin %d only supports a gpio mux\n", pin);
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Set a new mux function क्रम a pin.
 *
 * The रेजिस्टर is भागided पूर्णांकo the upper and lower 16 bit. When changing
 * a value, the previous रेजिस्टर value is not पढ़ो and changed. Instead
 * it seems the changed bits are marked in the upper 16 bit, जबतक the
 * changed value माला_लो set in the same offset in the lower 16 bit.
 * All pin settings seem to be 2 bit wide in both the upper and lower
 * parts.
 * @bank: pin bank to change
 * @pin: pin to change
 * @mux: new mux function to set
 */
अटल पूर्णांक rockchip_set_mux(काष्ठा rockchip_pin_bank *bank, पूर्णांक pin, पूर्णांक mux)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;
	पूर्णांक iomux_num = (pin / 8);
	काष्ठा regmap *regmap;
	पूर्णांक reg, ret, mask, mux_type;
	u8 bit;
	u32 data, rmask, route_location, route_reg, route_val;

	ret = rockchip_verअगरy_mux(bank, pin, mux);
	अगर (ret < 0)
		वापस ret;

	अगर (bank->iomux[iomux_num].type & IOMUX_GPIO_ONLY)
		वापस 0;

	dev_dbg(info->dev, "setting mux of GPIO%d-%d to %d\n",
						bank->bank_num, pin, mux);

	regmap = (bank->iomux[iomux_num].type & IOMUX_SOURCE_PMU)
				? info->regmap_pmu : info->regmap_base;

	/* get basic quadrupel of mux रेजिस्टरs and the correct reg inside */
	mux_type = bank->iomux[iomux_num].type;
	reg = bank->iomux[iomux_num].offset;
	अगर (mux_type & IOMUX_WIDTH_4BIT) अणु
		अगर ((pin % 8) >= 4)
			reg += 0x4;
		bit = (pin % 4) * 4;
		mask = 0xf;
	पूर्ण अन्यथा अगर (mux_type & IOMUX_WIDTH_3BIT) अणु
		अगर ((pin % 8) >= 5)
			reg += 0x4;
		bit = (pin % 8 % 5) * 3;
		mask = 0x7;
	पूर्ण अन्यथा अणु
		bit = (pin % 8) * 2;
		mask = 0x3;
	पूर्ण

	अगर (bank->recalced_mask & BIT(pin))
		rockchip_get_recalced_mux(bank, pin, &reg, &bit, &mask);

	अगर (bank->route_mask & BIT(pin)) अणु
		अगर (rockchip_get_mux_route(bank, pin, mux, &route_location,
					   &route_reg, &route_val)) अणु
			काष्ठा regmap *route_regmap = regmap;

			/* handle special locations */
			चयन (route_location) अणु
			हाल ROCKCHIP_ROUTE_PMU:
				route_regmap = info->regmap_pmu;
				अवरोध;
			हाल ROCKCHIP_ROUTE_GRF:
				route_regmap = info->regmap_base;
				अवरोध;
			पूर्ण

			ret = regmap_ग_लिखो(route_regmap, route_reg, route_val);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	data = (mask << (bit + 16));
	rmask = data | (data >> 16);
	data |= (mux & mask) << bit;
	ret = regmap_update_bits(regmap, reg, rmask, data);

	वापस ret;
पूर्ण

#घोषणा PX30_PULL_PMU_OFFSET		0x10
#घोषणा PX30_PULL_GRF_OFFSET		0x60
#घोषणा PX30_PULL_BITS_PER_PIN		2
#घोषणा PX30_PULL_PINS_PER_REG		8
#घोषणा PX30_PULL_BANK_STRIDE		16

अटल व्योम px30_calc_pull_reg_and_bit(काष्ठा rockchip_pin_bank *bank,
				       पूर्णांक pin_num, काष्ठा regmap **regmap,
				       पूर्णांक *reg, u8 *bit)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;

	/* The first 32 pins of the first bank are located in PMU */
	अगर (bank->bank_num == 0) अणु
		*regmap = info->regmap_pmu;
		*reg = PX30_PULL_PMU_OFFSET;
	पूर्ण अन्यथा अणु
		*regmap = info->regmap_base;
		*reg = PX30_PULL_GRF_OFFSET;

		/* correct the offset, as we're starting with the 2nd bank */
		*reg -= 0x10;
		*reg += bank->bank_num * PX30_PULL_BANK_STRIDE;
	पूर्ण

	*reg += ((pin_num / PX30_PULL_PINS_PER_REG) * 4);
	*bit = (pin_num % PX30_PULL_PINS_PER_REG);
	*bit *= PX30_PULL_BITS_PER_PIN;
पूर्ण

#घोषणा PX30_DRV_PMU_OFFSET		0x20
#घोषणा PX30_DRV_GRF_OFFSET		0xf0
#घोषणा PX30_DRV_BITS_PER_PIN		2
#घोषणा PX30_DRV_PINS_PER_REG		8
#घोषणा PX30_DRV_BANK_STRIDE		16

अटल व्योम px30_calc_drv_reg_and_bit(काष्ठा rockchip_pin_bank *bank,
				      पूर्णांक pin_num, काष्ठा regmap **regmap,
				      पूर्णांक *reg, u8 *bit)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;

	/* The first 32 pins of the first bank are located in PMU */
	अगर (bank->bank_num == 0) अणु
		*regmap = info->regmap_pmu;
		*reg = PX30_DRV_PMU_OFFSET;
	पूर्ण अन्यथा अणु
		*regmap = info->regmap_base;
		*reg = PX30_DRV_GRF_OFFSET;

		/* correct the offset, as we're starting with the 2nd bank */
		*reg -= 0x10;
		*reg += bank->bank_num * PX30_DRV_BANK_STRIDE;
	पूर्ण

	*reg += ((pin_num / PX30_DRV_PINS_PER_REG) * 4);
	*bit = (pin_num % PX30_DRV_PINS_PER_REG);
	*bit *= PX30_DRV_BITS_PER_PIN;
पूर्ण

#घोषणा PX30_SCHMITT_PMU_OFFSET			0x38
#घोषणा PX30_SCHMITT_GRF_OFFSET			0xc0
#घोषणा PX30_SCHMITT_PINS_PER_PMU_REG		16
#घोषणा PX30_SCHMITT_BANK_STRIDE		16
#घोषणा PX30_SCHMITT_PINS_PER_GRF_REG		8

अटल पूर्णांक px30_calc_schmitt_reg_and_bit(काष्ठा rockchip_pin_bank *bank,
					 पूर्णांक pin_num,
					 काष्ठा regmap **regmap,
					 पूर्णांक *reg, u8 *bit)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;
	पूर्णांक pins_per_reg;

	अगर (bank->bank_num == 0) अणु
		*regmap = info->regmap_pmu;
		*reg = PX30_SCHMITT_PMU_OFFSET;
		pins_per_reg = PX30_SCHMITT_PINS_PER_PMU_REG;
	पूर्ण अन्यथा अणु
		*regmap = info->regmap_base;
		*reg = PX30_SCHMITT_GRF_OFFSET;
		pins_per_reg = PX30_SCHMITT_PINS_PER_GRF_REG;
		*reg += (bank->bank_num  - 1) * PX30_SCHMITT_BANK_STRIDE;
	पूर्ण

	*reg += ((pin_num / pins_per_reg) * 4);
	*bit = pin_num % pins_per_reg;

	वापस 0;
पूर्ण

#घोषणा RV1108_PULL_PMU_OFFSET		0x10
#घोषणा RV1108_PULL_OFFSET		0x110
#घोषणा RV1108_PULL_PINS_PER_REG	8
#घोषणा RV1108_PULL_BITS_PER_PIN	2
#घोषणा RV1108_PULL_BANK_STRIDE		16

अटल व्योम rv1108_calc_pull_reg_and_bit(काष्ठा rockchip_pin_bank *bank,
					 पूर्णांक pin_num, काष्ठा regmap **regmap,
					 पूर्णांक *reg, u8 *bit)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;

	/* The first 24 pins of the first bank are located in PMU */
	अगर (bank->bank_num == 0) अणु
		*regmap = info->regmap_pmu;
		*reg = RV1108_PULL_PMU_OFFSET;
	पूर्ण अन्यथा अणु
		*reg = RV1108_PULL_OFFSET;
		*regmap = info->regmap_base;
		/* correct the offset, as we're starting with the 2nd bank */
		*reg -= 0x10;
		*reg += bank->bank_num * RV1108_PULL_BANK_STRIDE;
	पूर्ण

	*reg += ((pin_num / RV1108_PULL_PINS_PER_REG) * 4);
	*bit = (pin_num % RV1108_PULL_PINS_PER_REG);
	*bit *= RV1108_PULL_BITS_PER_PIN;
पूर्ण

#घोषणा RV1108_DRV_PMU_OFFSET		0x20
#घोषणा RV1108_DRV_GRF_OFFSET		0x210
#घोषणा RV1108_DRV_BITS_PER_PIN		2
#घोषणा RV1108_DRV_PINS_PER_REG		8
#घोषणा RV1108_DRV_BANK_STRIDE		16

अटल व्योम rv1108_calc_drv_reg_and_bit(काष्ठा rockchip_pin_bank *bank,
					पूर्णांक pin_num, काष्ठा regmap **regmap,
					पूर्णांक *reg, u8 *bit)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;

	/* The first 24 pins of the first bank are located in PMU */
	अगर (bank->bank_num == 0) अणु
		*regmap = info->regmap_pmu;
		*reg = RV1108_DRV_PMU_OFFSET;
	पूर्ण अन्यथा अणु
		*regmap = info->regmap_base;
		*reg = RV1108_DRV_GRF_OFFSET;

		/* correct the offset, as we're starting with the 2nd bank */
		*reg -= 0x10;
		*reg += bank->bank_num * RV1108_DRV_BANK_STRIDE;
	पूर्ण

	*reg += ((pin_num / RV1108_DRV_PINS_PER_REG) * 4);
	*bit = pin_num % RV1108_DRV_PINS_PER_REG;
	*bit *= RV1108_DRV_BITS_PER_PIN;
पूर्ण

#घोषणा RV1108_SCHMITT_PMU_OFFSET		0x30
#घोषणा RV1108_SCHMITT_GRF_OFFSET		0x388
#घोषणा RV1108_SCHMITT_BANK_STRIDE		8
#घोषणा RV1108_SCHMITT_PINS_PER_GRF_REG		16
#घोषणा RV1108_SCHMITT_PINS_PER_PMU_REG		8

अटल पूर्णांक rv1108_calc_schmitt_reg_and_bit(काष्ठा rockchip_pin_bank *bank,
					   पूर्णांक pin_num,
					   काष्ठा regmap **regmap,
					   पूर्णांक *reg, u8 *bit)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;
	पूर्णांक pins_per_reg;

	अगर (bank->bank_num == 0) अणु
		*regmap = info->regmap_pmu;
		*reg = RV1108_SCHMITT_PMU_OFFSET;
		pins_per_reg = RV1108_SCHMITT_PINS_PER_PMU_REG;
	पूर्ण अन्यथा अणु
		*regmap = info->regmap_base;
		*reg = RV1108_SCHMITT_GRF_OFFSET;
		pins_per_reg = RV1108_SCHMITT_PINS_PER_GRF_REG;
		*reg += (bank->bank_num  - 1) * RV1108_SCHMITT_BANK_STRIDE;
	पूर्ण
	*reg += ((pin_num / pins_per_reg) * 4);
	*bit = pin_num % pins_per_reg;

	वापस 0;
पूर्ण

#घोषणा RK3308_SCHMITT_PINS_PER_REG		8
#घोषणा RK3308_SCHMITT_BANK_STRIDE		16
#घोषणा RK3308_SCHMITT_GRF_OFFSET		0x1a0

अटल पूर्णांक rk3308_calc_schmitt_reg_and_bit(काष्ठा rockchip_pin_bank *bank,
				    पूर्णांक pin_num, काष्ठा regmap **regmap,
				    पूर्णांक *reg, u8 *bit)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;

	*regmap = info->regmap_base;
	*reg = RK3308_SCHMITT_GRF_OFFSET;

	*reg += bank->bank_num * RK3308_SCHMITT_BANK_STRIDE;
	*reg += ((pin_num / RK3308_SCHMITT_PINS_PER_REG) * 4);
	*bit = pin_num % RK3308_SCHMITT_PINS_PER_REG;

	वापस 0;
पूर्ण

#घोषणा RK2928_PULL_OFFSET		0x118
#घोषणा RK2928_PULL_PINS_PER_REG	16
#घोषणा RK2928_PULL_BANK_STRIDE		8

अटल व्योम rk2928_calc_pull_reg_and_bit(काष्ठा rockchip_pin_bank *bank,
				    पूर्णांक pin_num, काष्ठा regmap **regmap,
				    पूर्णांक *reg, u8 *bit)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;

	*regmap = info->regmap_base;
	*reg = RK2928_PULL_OFFSET;
	*reg += bank->bank_num * RK2928_PULL_BANK_STRIDE;
	*reg += (pin_num / RK2928_PULL_PINS_PER_REG) * 4;

	*bit = pin_num % RK2928_PULL_PINS_PER_REG;
पूर्ण;

#घोषणा RK3128_PULL_OFFSET	0x118

अटल व्योम rk3128_calc_pull_reg_and_bit(काष्ठा rockchip_pin_bank *bank,
					 पूर्णांक pin_num, काष्ठा regmap **regmap,
					 पूर्णांक *reg, u8 *bit)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;

	*regmap = info->regmap_base;
	*reg = RK3128_PULL_OFFSET;
	*reg += bank->bank_num * RK2928_PULL_BANK_STRIDE;
	*reg += ((pin_num / RK2928_PULL_PINS_PER_REG) * 4);

	*bit = pin_num % RK2928_PULL_PINS_PER_REG;
पूर्ण

#घोषणा RK3188_PULL_OFFSET		0x164
#घोषणा RK3188_PULL_BITS_PER_PIN	2
#घोषणा RK3188_PULL_PINS_PER_REG	8
#घोषणा RK3188_PULL_BANK_STRIDE		16
#घोषणा RK3188_PULL_PMU_OFFSET		0x64

अटल व्योम rk3188_calc_pull_reg_and_bit(काष्ठा rockchip_pin_bank *bank,
				    पूर्णांक pin_num, काष्ठा regmap **regmap,
				    पूर्णांक *reg, u8 *bit)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;

	/* The first 12 pins of the first bank are located अन्यथाwhere */
	अगर (bank->bank_num == 0 && pin_num < 12) अणु
		*regmap = info->regmap_pmu ? info->regmap_pmu
					   : bank->regmap_pull;
		*reg = info->regmap_pmu ? RK3188_PULL_PMU_OFFSET : 0;
		*reg += ((pin_num / RK3188_PULL_PINS_PER_REG) * 4);
		*bit = pin_num % RK3188_PULL_PINS_PER_REG;
		*bit *= RK3188_PULL_BITS_PER_PIN;
	पूर्ण अन्यथा अणु
		*regmap = info->regmap_pull ? info->regmap_pull
					    : info->regmap_base;
		*reg = info->regmap_pull ? 0 : RK3188_PULL_OFFSET;

		/* correct the offset, as it is the 2nd pull रेजिस्टर */
		*reg -= 4;
		*reg += bank->bank_num * RK3188_PULL_BANK_STRIDE;
		*reg += ((pin_num / RK3188_PULL_PINS_PER_REG) * 4);

		/*
		 * The bits in these रेजिस्टरs have an inverse ordering
		 * with the lowest pin being in bits 15:14 and the highest
		 * pin in bits 1:0
		 */
		*bit = 7 - (pin_num % RK3188_PULL_PINS_PER_REG);
		*bit *= RK3188_PULL_BITS_PER_PIN;
	पूर्ण
पूर्ण

#घोषणा RK3288_PULL_OFFSET		0x140
अटल व्योम rk3288_calc_pull_reg_and_bit(काष्ठा rockchip_pin_bank *bank,
				    पूर्णांक pin_num, काष्ठा regmap **regmap,
				    पूर्णांक *reg, u8 *bit)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;

	/* The first 24 pins of the first bank are located in PMU */
	अगर (bank->bank_num == 0) अणु
		*regmap = info->regmap_pmu;
		*reg = RK3188_PULL_PMU_OFFSET;

		*reg += ((pin_num / RK3188_PULL_PINS_PER_REG) * 4);
		*bit = pin_num % RK3188_PULL_PINS_PER_REG;
		*bit *= RK3188_PULL_BITS_PER_PIN;
	पूर्ण अन्यथा अणु
		*regmap = info->regmap_base;
		*reg = RK3288_PULL_OFFSET;

		/* correct the offset, as we're starting with the 2nd bank */
		*reg -= 0x10;
		*reg += bank->bank_num * RK3188_PULL_BANK_STRIDE;
		*reg += ((pin_num / RK3188_PULL_PINS_PER_REG) * 4);

		*bit = (pin_num % RK3188_PULL_PINS_PER_REG);
		*bit *= RK3188_PULL_BITS_PER_PIN;
	पूर्ण
पूर्ण

#घोषणा RK3288_DRV_PMU_OFFSET		0x70
#घोषणा RK3288_DRV_GRF_OFFSET		0x1c0
#घोषणा RK3288_DRV_BITS_PER_PIN		2
#घोषणा RK3288_DRV_PINS_PER_REG		8
#घोषणा RK3288_DRV_BANK_STRIDE		16

अटल व्योम rk3288_calc_drv_reg_and_bit(काष्ठा rockchip_pin_bank *bank,
				    पूर्णांक pin_num, काष्ठा regmap **regmap,
				    पूर्णांक *reg, u8 *bit)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;

	/* The first 24 pins of the first bank are located in PMU */
	अगर (bank->bank_num == 0) अणु
		*regmap = info->regmap_pmu;
		*reg = RK3288_DRV_PMU_OFFSET;

		*reg += ((pin_num / RK3288_DRV_PINS_PER_REG) * 4);
		*bit = pin_num % RK3288_DRV_PINS_PER_REG;
		*bit *= RK3288_DRV_BITS_PER_PIN;
	पूर्ण अन्यथा अणु
		*regmap = info->regmap_base;
		*reg = RK3288_DRV_GRF_OFFSET;

		/* correct the offset, as we're starting with the 2nd bank */
		*reg -= 0x10;
		*reg += bank->bank_num * RK3288_DRV_BANK_STRIDE;
		*reg += ((pin_num / RK3288_DRV_PINS_PER_REG) * 4);

		*bit = (pin_num % RK3288_DRV_PINS_PER_REG);
		*bit *= RK3288_DRV_BITS_PER_PIN;
	पूर्ण
पूर्ण

#घोषणा RK3228_PULL_OFFSET		0x100

अटल व्योम rk3228_calc_pull_reg_and_bit(काष्ठा rockchip_pin_bank *bank,
				    पूर्णांक pin_num, काष्ठा regmap **regmap,
				    पूर्णांक *reg, u8 *bit)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;

	*regmap = info->regmap_base;
	*reg = RK3228_PULL_OFFSET;
	*reg += bank->bank_num * RK3188_PULL_BANK_STRIDE;
	*reg += ((pin_num / RK3188_PULL_PINS_PER_REG) * 4);

	*bit = (pin_num % RK3188_PULL_PINS_PER_REG);
	*bit *= RK3188_PULL_BITS_PER_PIN;
पूर्ण

#घोषणा RK3228_DRV_GRF_OFFSET		0x200

अटल व्योम rk3228_calc_drv_reg_and_bit(काष्ठा rockchip_pin_bank *bank,
				    पूर्णांक pin_num, काष्ठा regmap **regmap,
				    पूर्णांक *reg, u8 *bit)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;

	*regmap = info->regmap_base;
	*reg = RK3228_DRV_GRF_OFFSET;
	*reg += bank->bank_num * RK3288_DRV_BANK_STRIDE;
	*reg += ((pin_num / RK3288_DRV_PINS_PER_REG) * 4);

	*bit = (pin_num % RK3288_DRV_PINS_PER_REG);
	*bit *= RK3288_DRV_BITS_PER_PIN;
पूर्ण

#घोषणा RK3308_PULL_OFFSET		0xa0

अटल व्योम rk3308_calc_pull_reg_and_bit(काष्ठा rockchip_pin_bank *bank,
				    पूर्णांक pin_num, काष्ठा regmap **regmap,
				    पूर्णांक *reg, u8 *bit)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;

	*regmap = info->regmap_base;
	*reg = RK3308_PULL_OFFSET;
	*reg += bank->bank_num * RK3188_PULL_BANK_STRIDE;
	*reg += ((pin_num / RK3188_PULL_PINS_PER_REG) * 4);

	*bit = (pin_num % RK3188_PULL_PINS_PER_REG);
	*bit *= RK3188_PULL_BITS_PER_PIN;
पूर्ण

#घोषणा RK3308_DRV_GRF_OFFSET		0x100

अटल व्योम rk3308_calc_drv_reg_and_bit(काष्ठा rockchip_pin_bank *bank,
				    पूर्णांक pin_num, काष्ठा regmap **regmap,
				    पूर्णांक *reg, u8 *bit)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;

	*regmap = info->regmap_base;
	*reg = RK3308_DRV_GRF_OFFSET;
	*reg += bank->bank_num * RK3288_DRV_BANK_STRIDE;
	*reg += ((pin_num / RK3288_DRV_PINS_PER_REG) * 4);

	*bit = (pin_num % RK3288_DRV_PINS_PER_REG);
	*bit *= RK3288_DRV_BITS_PER_PIN;
पूर्ण

#घोषणा RK3368_PULL_GRF_OFFSET		0x100
#घोषणा RK3368_PULL_PMU_OFFSET		0x10

अटल व्योम rk3368_calc_pull_reg_and_bit(काष्ठा rockchip_pin_bank *bank,
				    पूर्णांक pin_num, काष्ठा regmap **regmap,
				    पूर्णांक *reg, u8 *bit)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;

	/* The first 32 pins of the first bank are located in PMU */
	अगर (bank->bank_num == 0) अणु
		*regmap = info->regmap_pmu;
		*reg = RK3368_PULL_PMU_OFFSET;

		*reg += ((pin_num / RK3188_PULL_PINS_PER_REG) * 4);
		*bit = pin_num % RK3188_PULL_PINS_PER_REG;
		*bit *= RK3188_PULL_BITS_PER_PIN;
	पूर्ण अन्यथा अणु
		*regmap = info->regmap_base;
		*reg = RK3368_PULL_GRF_OFFSET;

		/* correct the offset, as we're starting with the 2nd bank */
		*reg -= 0x10;
		*reg += bank->bank_num * RK3188_PULL_BANK_STRIDE;
		*reg += ((pin_num / RK3188_PULL_PINS_PER_REG) * 4);

		*bit = (pin_num % RK3188_PULL_PINS_PER_REG);
		*bit *= RK3188_PULL_BITS_PER_PIN;
	पूर्ण
पूर्ण

#घोषणा RK3368_DRV_PMU_OFFSET		0x20
#घोषणा RK3368_DRV_GRF_OFFSET		0x200

अटल व्योम rk3368_calc_drv_reg_and_bit(काष्ठा rockchip_pin_bank *bank,
				    पूर्णांक pin_num, काष्ठा regmap **regmap,
				    पूर्णांक *reg, u8 *bit)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;

	/* The first 32 pins of the first bank are located in PMU */
	अगर (bank->bank_num == 0) अणु
		*regmap = info->regmap_pmu;
		*reg = RK3368_DRV_PMU_OFFSET;

		*reg += ((pin_num / RK3288_DRV_PINS_PER_REG) * 4);
		*bit = pin_num % RK3288_DRV_PINS_PER_REG;
		*bit *= RK3288_DRV_BITS_PER_PIN;
	पूर्ण अन्यथा अणु
		*regmap = info->regmap_base;
		*reg = RK3368_DRV_GRF_OFFSET;

		/* correct the offset, as we're starting with the 2nd bank */
		*reg -= 0x10;
		*reg += bank->bank_num * RK3288_DRV_BANK_STRIDE;
		*reg += ((pin_num / RK3288_DRV_PINS_PER_REG) * 4);

		*bit = (pin_num % RK3288_DRV_PINS_PER_REG);
		*bit *= RK3288_DRV_BITS_PER_PIN;
	पूर्ण
पूर्ण

#घोषणा RK3399_PULL_GRF_OFFSET		0xe040
#घोषणा RK3399_PULL_PMU_OFFSET		0x40
#घोषणा RK3399_DRV_3BITS_PER_PIN	3

अटल व्योम rk3399_calc_pull_reg_and_bit(काष्ठा rockchip_pin_bank *bank,
					 पूर्णांक pin_num, काष्ठा regmap **regmap,
					 पूर्णांक *reg, u8 *bit)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;

	/* The bank0:16 and bank1:32 pins are located in PMU */
	अगर ((bank->bank_num == 0) || (bank->bank_num == 1)) अणु
		*regmap = info->regmap_pmu;
		*reg = RK3399_PULL_PMU_OFFSET;

		*reg += bank->bank_num * RK3188_PULL_BANK_STRIDE;

		*reg += ((pin_num / RK3188_PULL_PINS_PER_REG) * 4);
		*bit = pin_num % RK3188_PULL_PINS_PER_REG;
		*bit *= RK3188_PULL_BITS_PER_PIN;
	पूर्ण अन्यथा अणु
		*regmap = info->regmap_base;
		*reg = RK3399_PULL_GRF_OFFSET;

		/* correct the offset, as we're starting with the 3rd bank */
		*reg -= 0x20;
		*reg += bank->bank_num * RK3188_PULL_BANK_STRIDE;
		*reg += ((pin_num / RK3188_PULL_PINS_PER_REG) * 4);

		*bit = (pin_num % RK3188_PULL_PINS_PER_REG);
		*bit *= RK3188_PULL_BITS_PER_PIN;
	पूर्ण
पूर्ण

अटल व्योम rk3399_calc_drv_reg_and_bit(काष्ठा rockchip_pin_bank *bank,
					पूर्णांक pin_num, काष्ठा regmap **regmap,
					पूर्णांक *reg, u8 *bit)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;
	पूर्णांक drv_num = (pin_num / 8);

	/*  The bank0:16 and bank1:32 pins are located in PMU */
	अगर ((bank->bank_num == 0) || (bank->bank_num == 1))
		*regmap = info->regmap_pmu;
	अन्यथा
		*regmap = info->regmap_base;

	*reg = bank->drv[drv_num].offset;
	अगर ((bank->drv[drv_num].drv_type == DRV_TYPE_IO_1V8_3V0_AUTO) ||
	    (bank->drv[drv_num].drv_type == DRV_TYPE_IO_3V3_ONLY))
		*bit = (pin_num % 8) * 3;
	अन्यथा
		*bit = (pin_num % 8) * 2;
पूर्ण

#घोषणा RK3568_PULL_PMU_OFFSET		0x20
#घोषणा RK3568_PULL_GRF_OFFSET		0x80
#घोषणा RK3568_PULL_BITS_PER_PIN	2
#घोषणा RK3568_PULL_PINS_PER_REG	8
#घोषणा RK3568_PULL_BANK_STRIDE		0x10

अटल व्योम rk3568_calc_pull_reg_and_bit(काष्ठा rockchip_pin_bank *bank,
					 पूर्णांक pin_num, काष्ठा regmap **regmap,
					 पूर्णांक *reg, u8 *bit)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;

	अगर (bank->bank_num == 0) अणु
		*regmap = info->regmap_pmu;
		*reg = RK3568_PULL_PMU_OFFSET;
		*reg += bank->bank_num * RK3568_PULL_BANK_STRIDE;
		*reg += ((pin_num / RK3568_PULL_PINS_PER_REG) * 4);

		*bit = pin_num % RK3568_PULL_PINS_PER_REG;
		*bit *= RK3568_PULL_BITS_PER_PIN;
	पूर्ण अन्यथा अणु
		*regmap = info->regmap_base;
		*reg = RK3568_PULL_GRF_OFFSET;
		*reg += (bank->bank_num - 1) * RK3568_PULL_BANK_STRIDE;
		*reg += ((pin_num / RK3568_PULL_PINS_PER_REG) * 4);

		*bit = (pin_num % RK3568_PULL_PINS_PER_REG);
		*bit *= RK3568_PULL_BITS_PER_PIN;
	पूर्ण
पूर्ण

#घोषणा RK3568_DRV_PMU_OFFSET		0x70
#घोषणा RK3568_DRV_GRF_OFFSET		0x200
#घोषणा RK3568_DRV_BITS_PER_PIN		8
#घोषणा RK3568_DRV_PINS_PER_REG		2
#घोषणा RK3568_DRV_BANK_STRIDE		0x40

अटल व्योम rk3568_calc_drv_reg_and_bit(काष्ठा rockchip_pin_bank *bank,
					पूर्णांक pin_num, काष्ठा regmap **regmap,
					पूर्णांक *reg, u8 *bit)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;

	/* The first 32 pins of the first bank are located in PMU */
	अगर (bank->bank_num == 0) अणु
		*regmap = info->regmap_pmu;
		*reg = RK3568_DRV_PMU_OFFSET;
		*reg += ((pin_num / RK3568_DRV_PINS_PER_REG) * 4);

		*bit = pin_num % RK3568_DRV_PINS_PER_REG;
		*bit *= RK3568_DRV_BITS_PER_PIN;
	पूर्ण अन्यथा अणु
		*regmap = info->regmap_base;
		*reg = RK3568_DRV_GRF_OFFSET;
		*reg += (bank->bank_num - 1) * RK3568_DRV_BANK_STRIDE;
		*reg += ((pin_num / RK3568_DRV_PINS_PER_REG) * 4);

		*bit = (pin_num % RK3568_DRV_PINS_PER_REG);
		*bit *= RK3568_DRV_BITS_PER_PIN;
	पूर्ण
पूर्ण

अटल पूर्णांक rockchip_perpin_drv_list[DRV_TYPE_MAX][8] = अणु
	अणु 2, 4, 8, 12, -1, -1, -1, -1 पूर्ण,
	अणु 3, 6, 9, 12, -1, -1, -1, -1 पूर्ण,
	अणु 5, 10, 15, 20, -1, -1, -1, -1 पूर्ण,
	अणु 4, 6, 8, 10, 12, 14, 16, 18 पूर्ण,
	अणु 4, 7, 10, 13, 16, 19, 22, 26 पूर्ण
पूर्ण;

अटल पूर्णांक rockchip_get_drive_perpin(काष्ठा rockchip_pin_bank *bank,
				     पूर्णांक pin_num)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;
	काष्ठा rockchip_pin_ctrl *ctrl = info->ctrl;
	काष्ठा regmap *regmap;
	पूर्णांक reg, ret;
	u32 data, temp, rmask_bits;
	u8 bit;
	पूर्णांक drv_type = bank->drv[pin_num / 8].drv_type;

	ctrl->drv_calc_reg(bank, pin_num, &regmap, &reg, &bit);

	चयन (drv_type) अणु
	हाल DRV_TYPE_IO_1V8_3V0_AUTO:
	हाल DRV_TYPE_IO_3V3_ONLY:
		rmask_bits = RK3399_DRV_3BITS_PER_PIN;
		चयन (bit) अणु
		हाल 0 ... 12:
			/* regular हाल, nothing to करो */
			अवरोध;
		हाल 15:
			/*
			 * drive-strength offset is special, as it is
			 * spपढ़ो over 2 रेजिस्टरs
			 */
			ret = regmap_पढ़ो(regmap, reg, &data);
			अगर (ret)
				वापस ret;

			ret = regmap_पढ़ो(regmap, reg + 0x4, &temp);
			अगर (ret)
				वापस ret;

			/*
			 * the bit data[15] contains bit 0 of the value
			 * जबतक temp[1:0] contains bits 2 and 1
			 */
			data >>= 15;
			temp &= 0x3;
			temp <<= 1;
			data |= temp;

			वापस rockchip_perpin_drv_list[drv_type][data];
		हाल 18 ... 21:
			/* setting fully enबंदd in the second रेजिस्टर */
			reg += 4;
			bit -= 16;
			अवरोध;
		शेष:
			dev_err(info->dev, "unsupported bit: %d for pinctrl drive type: %d\n",
				bit, drv_type);
			वापस -EINVAL;
		पूर्ण

		अवरोध;
	हाल DRV_TYPE_IO_DEFAULT:
	हाल DRV_TYPE_IO_1V8_OR_3V0:
	हाल DRV_TYPE_IO_1V8_ONLY:
		rmask_bits = RK3288_DRV_BITS_PER_PIN;
		अवरोध;
	शेष:
		dev_err(info->dev, "unsupported pinctrl drive type: %d\n",
			drv_type);
		वापस -EINVAL;
	पूर्ण

	ret = regmap_पढ़ो(regmap, reg, &data);
	अगर (ret)
		वापस ret;

	data >>= bit;
	data &= (1 << rmask_bits) - 1;

	वापस rockchip_perpin_drv_list[drv_type][data];
पूर्ण

अटल पूर्णांक rockchip_set_drive_perpin(काष्ठा rockchip_pin_bank *bank,
				     पूर्णांक pin_num, पूर्णांक strength)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;
	काष्ठा rockchip_pin_ctrl *ctrl = info->ctrl;
	काष्ठा regmap *regmap;
	पूर्णांक reg, ret, i;
	u32 data, rmask, rmask_bits, temp;
	u8 bit;
	पूर्णांक drv_type = bank->drv[pin_num / 8].drv_type;

	dev_dbg(info->dev, "setting drive of GPIO%d-%d to %d\n",
		bank->bank_num, pin_num, strength);

	ctrl->drv_calc_reg(bank, pin_num, &regmap, &reg, &bit);
	अगर (ctrl->type == RK3568) अणु
		rmask_bits = RK3568_DRV_BITS_PER_PIN;
		ret = (1 << (strength + 1)) - 1;
		जाओ config;
	पूर्ण

	ret = -EINVAL;
	क्रम (i = 0; i < ARRAY_SIZE(rockchip_perpin_drv_list[drv_type]); i++) अणु
		अगर (rockchip_perpin_drv_list[drv_type][i] == strength) अणु
			ret = i;
			अवरोध;
		पूर्ण अन्यथा अगर (rockchip_perpin_drv_list[drv_type][i] < 0) अणु
			ret = rockchip_perpin_drv_list[drv_type][i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret < 0) अणु
		dev_err(info->dev, "unsupported driver strength %d\n",
			strength);
		वापस ret;
	पूर्ण

	चयन (drv_type) अणु
	हाल DRV_TYPE_IO_1V8_3V0_AUTO:
	हाल DRV_TYPE_IO_3V3_ONLY:
		rmask_bits = RK3399_DRV_3BITS_PER_PIN;
		चयन (bit) अणु
		हाल 0 ... 12:
			/* regular हाल, nothing to करो */
			अवरोध;
		हाल 15:
			/*
			 * drive-strength offset is special, as it is spपढ़ो
			 * over 2 रेजिस्टरs, the bit data[15] contains bit 0
			 * of the value जबतक temp[1:0] contains bits 2 and 1
			 */
			data = (ret & 0x1) << 15;
			temp = (ret >> 0x1) & 0x3;

			rmask = BIT(15) | BIT(31);
			data |= BIT(31);
			ret = regmap_update_bits(regmap, reg, rmask, data);
			अगर (ret)
				वापस ret;

			rmask = 0x3 | (0x3 << 16);
			temp |= (0x3 << 16);
			reg += 0x4;
			ret = regmap_update_bits(regmap, reg, rmask, temp);

			वापस ret;
		हाल 18 ... 21:
			/* setting fully enबंदd in the second रेजिस्टर */
			reg += 4;
			bit -= 16;
			अवरोध;
		शेष:
			dev_err(info->dev, "unsupported bit: %d for pinctrl drive type: %d\n",
				bit, drv_type);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल DRV_TYPE_IO_DEFAULT:
	हाल DRV_TYPE_IO_1V8_OR_3V0:
	हाल DRV_TYPE_IO_1V8_ONLY:
		rmask_bits = RK3288_DRV_BITS_PER_PIN;
		अवरोध;
	शेष:
		dev_err(info->dev, "unsupported pinctrl drive type: %d\n",
			drv_type);
		वापस -EINVAL;
	पूर्ण

config:
	/* enable the ग_लिखो to the equivalent lower bits */
	data = ((1 << rmask_bits) - 1) << (bit + 16);
	rmask = data | (data >> 16);
	data |= (ret << bit);

	ret = regmap_update_bits(regmap, reg, rmask, data);

	वापस ret;
पूर्ण

अटल पूर्णांक rockchip_pull_list[PULL_TYPE_MAX][4] = अणु
	अणु
		PIN_CONFIG_BIAS_DISABLE,
		PIN_CONFIG_BIAS_PULL_UP,
		PIN_CONFIG_BIAS_PULL_DOWN,
		PIN_CONFIG_BIAS_BUS_HOLD
	पूर्ण,
	अणु
		PIN_CONFIG_BIAS_DISABLE,
		PIN_CONFIG_BIAS_PULL_DOWN,
		PIN_CONFIG_BIAS_DISABLE,
		PIN_CONFIG_BIAS_PULL_UP
	पूर्ण,
पूर्ण;

अटल पूर्णांक rockchip_get_pull(काष्ठा rockchip_pin_bank *bank, पूर्णांक pin_num)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;
	काष्ठा rockchip_pin_ctrl *ctrl = info->ctrl;
	काष्ठा regmap *regmap;
	पूर्णांक reg, ret, pull_type;
	u8 bit;
	u32 data;

	/* rk3066b करोes support any pulls */
	अगर (ctrl->type == RK3066B)
		वापस PIN_CONFIG_BIAS_DISABLE;

	ctrl->pull_calc_reg(bank, pin_num, &regmap, &reg, &bit);

	ret = regmap_पढ़ो(regmap, reg, &data);
	अगर (ret)
		वापस ret;

	चयन (ctrl->type) अणु
	हाल RK2928:
	हाल RK3128:
		वापस !(data & BIT(bit))
				? PIN_CONFIG_BIAS_PULL_PIN_DEFAULT
				: PIN_CONFIG_BIAS_DISABLE;
	हाल PX30:
	हाल RV1108:
	हाल RK3188:
	हाल RK3288:
	हाल RK3308:
	हाल RK3368:
	हाल RK3399:
		pull_type = bank->pull_type[pin_num / 8];
		data >>= bit;
		data &= (1 << RK3188_PULL_BITS_PER_PIN) - 1;

		वापस rockchip_pull_list[pull_type][data];
	शेष:
		dev_err(info->dev, "unsupported pinctrl type\n");
		वापस -EINVAL;
	पूर्ण;
पूर्ण

अटल पूर्णांक rockchip_set_pull(काष्ठा rockchip_pin_bank *bank,
					पूर्णांक pin_num, पूर्णांक pull)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;
	काष्ठा rockchip_pin_ctrl *ctrl = info->ctrl;
	काष्ठा regmap *regmap;
	पूर्णांक reg, ret, i, pull_type;
	u8 bit;
	u32 data, rmask;

	dev_dbg(info->dev, "setting pull of GPIO%d-%d to %d\n",
		 bank->bank_num, pin_num, pull);

	/* rk3066b करोes support any pulls */
	अगर (ctrl->type == RK3066B)
		वापस pull ? -EINVAL : 0;

	ctrl->pull_calc_reg(bank, pin_num, &regmap, &reg, &bit);

	चयन (ctrl->type) अणु
	हाल RK2928:
	हाल RK3128:
		data = BIT(bit + 16);
		अगर (pull == PIN_CONFIG_BIAS_DISABLE)
			data |= BIT(bit);
		ret = regmap_ग_लिखो(regmap, reg, data);
		अवरोध;
	हाल PX30:
	हाल RV1108:
	हाल RK3188:
	हाल RK3288:
	हाल RK3308:
	हाल RK3368:
	हाल RK3399:
	हाल RK3568:
		pull_type = bank->pull_type[pin_num / 8];
		ret = -EINVAL;
		क्रम (i = 0; i < ARRAY_SIZE(rockchip_pull_list[pull_type]);
			i++) अणु
			अगर (rockchip_pull_list[pull_type][i] == pull) अणु
				ret = i;
				अवरोध;
			पूर्ण
		पूर्ण
		/*
		 * In the TRM, pull-up being 1 क्रम everything except the GPIO0_D0-D6,
		 * where that pull up value becomes 3.
		 */
		अगर (ctrl->type == RK3568 && bank->bank_num == 0 && pin_num >= 27 && pin_num <= 30) अणु
			अगर (ret == 1)
				ret = 3;
		पूर्ण

		अगर (ret < 0) अणु
			dev_err(info->dev, "unsupported pull setting %d\n",
				pull);
			वापस ret;
		पूर्ण

		/* enable the ग_लिखो to the equivalent lower bits */
		data = ((1 << RK3188_PULL_BITS_PER_PIN) - 1) << (bit + 16);
		rmask = data | (data >> 16);
		data |= (ret << bit);

		ret = regmap_update_bits(regmap, reg, rmask, data);
		अवरोध;
	शेष:
		dev_err(info->dev, "unsupported pinctrl type\n");
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

#घोषणा RK3328_SCHMITT_BITS_PER_PIN		1
#घोषणा RK3328_SCHMITT_PINS_PER_REG		16
#घोषणा RK3328_SCHMITT_BANK_STRIDE		8
#घोषणा RK3328_SCHMITT_GRF_OFFSET		0x380

अटल पूर्णांक rk3328_calc_schmitt_reg_and_bit(काष्ठा rockchip_pin_bank *bank,
					   पूर्णांक pin_num,
					   काष्ठा regmap **regmap,
					   पूर्णांक *reg, u8 *bit)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;

	*regmap = info->regmap_base;
	*reg = RK3328_SCHMITT_GRF_OFFSET;

	*reg += bank->bank_num * RK3328_SCHMITT_BANK_STRIDE;
	*reg += ((pin_num / RK3328_SCHMITT_PINS_PER_REG) * 4);
	*bit = pin_num % RK3328_SCHMITT_PINS_PER_REG;

	वापस 0;
पूर्ण

#घोषणा RK3568_SCHMITT_BITS_PER_PIN		2
#घोषणा RK3568_SCHMITT_PINS_PER_REG		8
#घोषणा RK3568_SCHMITT_BANK_STRIDE		0x10
#घोषणा RK3568_SCHMITT_GRF_OFFSET		0xc0
#घोषणा RK3568_SCHMITT_PMUGRF_OFFSET		0x30

अटल पूर्णांक rk3568_calc_schmitt_reg_and_bit(काष्ठा rockchip_pin_bank *bank,
					   पूर्णांक pin_num,
					   काष्ठा regmap **regmap,
					   पूर्णांक *reg, u8 *bit)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;

	अगर (bank->bank_num == 0) अणु
		*regmap = info->regmap_pmu;
		*reg = RK3568_SCHMITT_PMUGRF_OFFSET;
	पूर्ण अन्यथा अणु
		*regmap = info->regmap_base;
		*reg = RK3568_SCHMITT_GRF_OFFSET;
		*reg += (bank->bank_num - 1) * RK3568_SCHMITT_BANK_STRIDE;
	पूर्ण

	*reg += ((pin_num / RK3568_SCHMITT_PINS_PER_REG) * 4);
	*bit = pin_num % RK3568_SCHMITT_PINS_PER_REG;
	*bit *= RK3568_SCHMITT_BITS_PER_PIN;

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_get_schmitt(काष्ठा rockchip_pin_bank *bank, पूर्णांक pin_num)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;
	काष्ठा rockchip_pin_ctrl *ctrl = info->ctrl;
	काष्ठा regmap *regmap;
	पूर्णांक reg, ret;
	u8 bit;
	u32 data;

	ret = ctrl->schmitt_calc_reg(bank, pin_num, &regmap, &reg, &bit);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(regmap, reg, &data);
	अगर (ret)
		वापस ret;

	data >>= bit;
	चयन (ctrl->type) अणु
	हाल RK3568:
		वापस data & ((1 << RK3568_SCHMITT_BITS_PER_PIN) - 1);
	शेष:
		अवरोध;
	पूर्ण

	वापस data & 0x1;
पूर्ण

अटल पूर्णांक rockchip_set_schmitt(काष्ठा rockchip_pin_bank *bank,
				पूर्णांक pin_num, पूर्णांक enable)
अणु
	काष्ठा rockchip_pinctrl *info = bank->drvdata;
	काष्ठा rockchip_pin_ctrl *ctrl = info->ctrl;
	काष्ठा regmap *regmap;
	पूर्णांक reg, ret;
	u8 bit;
	u32 data, rmask;

	dev_dbg(info->dev, "setting input schmitt of GPIO%d-%d to %d\n",
		bank->bank_num, pin_num, enable);

	ret = ctrl->schmitt_calc_reg(bank, pin_num, &regmap, &reg, &bit);
	अगर (ret)
		वापस ret;

	/* enable the ग_लिखो to the equivalent lower bits */
	चयन (ctrl->type) अणु
	हाल RK3568:
		data = ((1 << RK3568_SCHMITT_BITS_PER_PIN) - 1) << (bit + 16);
		rmask = data | (data >> 16);
		data |= ((enable ? 0x2 : 0x1) << bit);
		अवरोध;
	शेष:
		data = BIT(bit + 16) | (enable << bit);
		rmask = BIT(bit + 16) | BIT(bit);
		अवरोध;
	पूर्ण

	वापस regmap_update_bits(regmap, reg, rmask, data);
पूर्ण

/*
 * Pinmux_ops handling
 */

अटल पूर्णांक rockchip_pmx_get_funcs_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा rockchip_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);

	वापस info->nfunctions;
पूर्ण

अटल स्थिर अक्षर *rockchip_pmx_get_func_name(काष्ठा pinctrl_dev *pctldev,
					  अचिन्हित selector)
अणु
	काष्ठा rockchip_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);

	वापस info->functions[selector].name;
पूर्ण

अटल पूर्णांक rockchip_pmx_get_groups(काष्ठा pinctrl_dev *pctldev,
				अचिन्हित selector, स्थिर अक्षर * स्थिर **groups,
				अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा rockchip_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);

	*groups = info->functions[selector].groups;
	*num_groups = info->functions[selector].ngroups;

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_pmx_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित selector,
			    अचिन्हित group)
अणु
	काष्ठा rockchip_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);
	स्थिर अचिन्हित पूर्णांक *pins = info->groups[group].pins;
	स्थिर काष्ठा rockchip_pin_config *data = info->groups[group].data;
	काष्ठा rockchip_pin_bank *bank;
	पूर्णांक cnt, ret = 0;

	dev_dbg(info->dev, "enable function %s group %s\n",
		info->functions[selector].name, info->groups[group].name);

	/*
	 * क्रम each pin in the pin group selected, program the corresponding
	 * pin function number in the config रेजिस्टर.
	 */
	क्रम (cnt = 0; cnt < info->groups[group].npins; cnt++) अणु
		bank = pin_to_bank(info, pins[cnt]);
		ret = rockchip_set_mux(bank, pins[cnt] - bank->pin_base,
				       data[cnt].func);
		अगर (ret)
			अवरोध;
	पूर्ण

	अगर (ret) अणु
		/* revert the alपढ़ोy करोne pin settings */
		क्रम (cnt--; cnt >= 0; cnt--)
			rockchip_set_mux(bank, pins[cnt] - bank->pin_base, 0);

		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा rockchip_pin_bank *bank = gpiochip_get_data(chip);
	u32 data;
	पूर्णांक ret;

	ret = clk_enable(bank->clk);
	अगर (ret < 0) अणु
		dev_err(bank->drvdata->dev,
			"failed to enable clock for bank %s\n", bank->name);
		वापस ret;
	पूर्ण
	data = पढ़ोl_relaxed(bank->reg_base + GPIO_SWPORT_DDR);
	clk_disable(bank->clk);

	अगर (data & BIT(offset))
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

/*
 * The calls to gpio_direction_output() and gpio_direction_input()
 * leads to this function call (via the pinctrl_gpio_direction_अणुinput|outputपूर्ण()
 * function called from the gpiolib पूर्णांकerface).
 */
अटल पूर्णांक _rockchip_pmx_gpio_set_direction(काष्ठा gpio_chip *chip,
					    पूर्णांक pin, bool input)
अणु
	काष्ठा rockchip_pin_bank *bank;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	u32 data;

	bank = gpiochip_get_data(chip);

	ret = rockchip_set_mux(bank, pin, RK_FUNC_GPIO);
	अगर (ret < 0)
		वापस ret;

	clk_enable(bank->clk);
	raw_spin_lock_irqsave(&bank->slock, flags);

	data = पढ़ोl_relaxed(bank->reg_base + GPIO_SWPORT_DDR);
	/* set bit to 1 क्रम output, 0 क्रम input */
	अगर (!input)
		data |= BIT(pin);
	अन्यथा
		data &= ~BIT(pin);
	ग_लिखोl_relaxed(data, bank->reg_base + GPIO_SWPORT_DDR);

	raw_spin_unlock_irqrestore(&bank->slock, flags);
	clk_disable(bank->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_pmx_gpio_set_direction(काष्ठा pinctrl_dev *pctldev,
					      काष्ठा pinctrl_gpio_range *range,
					      अचिन्हित offset, bool input)
अणु
	काष्ठा rockchip_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा gpio_chip *chip;
	पूर्णांक pin;

	chip = range->gc;
	pin = offset - chip->base;
	dev_dbg(info->dev, "gpio_direction for pin %u as %s-%d to %s\n",
		 offset, range->name, pin, input ? "input" : "output");

	वापस _rockchip_pmx_gpio_set_direction(chip, offset - chip->base,
						input);
पूर्ण

अटल स्थिर काष्ठा pinmux_ops rockchip_pmx_ops = अणु
	.get_functions_count	= rockchip_pmx_get_funcs_count,
	.get_function_name	= rockchip_pmx_get_func_name,
	.get_function_groups	= rockchip_pmx_get_groups,
	.set_mux		= rockchip_pmx_set,
	.gpio_set_direction	= rockchip_pmx_gpio_set_direction,
पूर्ण;

/*
 * Pinconf_ops handling
 */

अटल bool rockchip_pinconf_pull_valid(काष्ठा rockchip_pin_ctrl *ctrl,
					क्रमागत pin_config_param pull)
अणु
	चयन (ctrl->type) अणु
	हाल RK2928:
	हाल RK3128:
		वापस (pull == PIN_CONFIG_BIAS_PULL_PIN_DEFAULT ||
					pull == PIN_CONFIG_BIAS_DISABLE);
	हाल RK3066B:
		वापस pull ? false : true;
	हाल PX30:
	हाल RV1108:
	हाल RK3188:
	हाल RK3288:
	हाल RK3308:
	हाल RK3368:
	हाल RK3399:
	हाल RK3568:
		वापस (pull != PIN_CONFIG_BIAS_PULL_PIN_DEFAULT);
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम rockchip_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित offset, पूर्णांक value);
अटल पूर्णांक rockchip_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित offset);

/* set the pin config settings क्रम a specअगरied pin */
अटल पूर्णांक rockchip_pinconf_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
				अचिन्हित दीर्घ *configs, अचिन्हित num_configs)
अणु
	काष्ठा rockchip_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा rockchip_pin_bank *bank = pin_to_bank(info, pin);
	क्रमागत pin_config_param param;
	u32 arg;
	पूर्णांक i;
	पूर्णांक rc;

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_DISABLE:
			rc =  rockchip_set_pull(bank, pin - bank->pin_base,
				param);
			अगर (rc)
				वापस rc;
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_UP:
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
		हाल PIN_CONFIG_BIAS_PULL_PIN_DEFAULT:
		हाल PIN_CONFIG_BIAS_BUS_HOLD:
			अगर (!rockchip_pinconf_pull_valid(info->ctrl, param))
				वापस -ENOTSUPP;

			अगर (!arg)
				वापस -EINVAL;

			rc = rockchip_set_pull(bank, pin - bank->pin_base,
				param);
			अगर (rc)
				वापस rc;
			अवरोध;
		हाल PIN_CONFIG_OUTPUT:
			rockchip_gpio_set(&bank->gpio_chip,
					  pin - bank->pin_base, arg);
			rc = _rockchip_pmx_gpio_set_direction(&bank->gpio_chip,
					  pin - bank->pin_base, false);
			अगर (rc)
				वापस rc;
			अवरोध;
		हाल PIN_CONFIG_DRIVE_STRENGTH:
			/* rk3288 is the first with per-pin drive-strength */
			अगर (!info->ctrl->drv_calc_reg)
				वापस -ENOTSUPP;

			rc = rockchip_set_drive_perpin(bank,
						pin - bank->pin_base, arg);
			अगर (rc < 0)
				वापस rc;
			अवरोध;
		हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
			अगर (!info->ctrl->schmitt_calc_reg)
				वापस -ENOTSUPP;

			rc = rockchip_set_schmitt(bank,
						  pin - bank->pin_base, arg);
			अगर (rc < 0)
				वापस rc;
			अवरोध;
		शेष:
			वापस -ENOTSUPP;
			अवरोध;
		पूर्ण
	पूर्ण /* क्रम each config */

	वापस 0;
पूर्ण

/* get the pin config settings क्रम a specअगरied pin */
अटल पूर्णांक rockchip_pinconf_get(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
							अचिन्हित दीर्घ *config)
अणु
	काष्ठा rockchip_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा rockchip_pin_bank *bank = pin_to_bank(info, pin);
	क्रमागत pin_config_param param = pinconf_to_config_param(*config);
	u16 arg;
	पूर्णांक rc;

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		अगर (rockchip_get_pull(bank, pin - bank->pin_base) != param)
			वापस -EINVAL;

		arg = 0;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_UP:
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
	हाल PIN_CONFIG_BIAS_PULL_PIN_DEFAULT:
	हाल PIN_CONFIG_BIAS_BUS_HOLD:
		अगर (!rockchip_pinconf_pull_valid(info->ctrl, param))
			वापस -ENOTSUPP;

		अगर (rockchip_get_pull(bank, pin - bank->pin_base) != param)
			वापस -EINVAL;

		arg = 1;
		अवरोध;
	हाल PIN_CONFIG_OUTPUT:
		rc = rockchip_get_mux(bank, pin - bank->pin_base);
		अगर (rc != RK_FUNC_GPIO)
			वापस -EINVAL;

		rc = rockchip_gpio_get(&bank->gpio_chip, pin - bank->pin_base);
		अगर (rc < 0)
			वापस rc;

		arg = rc ? 1 : 0;
		अवरोध;
	हाल PIN_CONFIG_DRIVE_STRENGTH:
		/* rk3288 is the first with per-pin drive-strength */
		अगर (!info->ctrl->drv_calc_reg)
			वापस -ENOTSUPP;

		rc = rockchip_get_drive_perpin(bank, pin - bank->pin_base);
		अगर (rc < 0)
			वापस rc;

		arg = rc;
		अवरोध;
	हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		अगर (!info->ctrl->schmitt_calc_reg)
			वापस -ENOTSUPP;

		rc = rockchip_get_schmitt(bank, pin - bank->pin_base);
		अगर (rc < 0)
			वापस rc;

		arg = rc;
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
		अवरोध;
	पूर्ण

	*config = pinconf_to_config_packed(param, arg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops rockchip_pinconf_ops = अणु
	.pin_config_get			= rockchip_pinconf_get,
	.pin_config_set			= rockchip_pinconf_set,
	.is_generic			= true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rockchip_bank_match[] = अणु
	अणु .compatible = "rockchip,gpio-bank" पूर्ण,
	अणु .compatible = "rockchip,rk3188-gpio-bank0" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल व्योम rockchip_pinctrl_child_count(काष्ठा rockchip_pinctrl *info,
						काष्ठा device_node *np)
अणु
	काष्ठा device_node *child;

	क्रम_each_child_of_node(np, child) अणु
		अगर (of_match_node(rockchip_bank_match, child))
			जारी;

		info->nfunctions++;
		info->ngroups += of_get_child_count(child);
	पूर्ण
पूर्ण

अटल पूर्णांक rockchip_pinctrl_parse_groups(काष्ठा device_node *np,
					      काष्ठा rockchip_pin_group *grp,
					      काष्ठा rockchip_pinctrl *info,
					      u32 index)
अणु
	काष्ठा rockchip_pin_bank *bank;
	पूर्णांक size;
	स्थिर __be32 *list;
	पूर्णांक num;
	पूर्णांक i, j;
	पूर्णांक ret;

	dev_dbg(info->dev, "group(%d): %pOFn\n", index, np);

	/* Initialise group */
	grp->name = np->name;

	/*
	 * the binding क्रमmat is rockchip,pins = <bank pin mux CONFIG>,
	 * करो sanity check and calculate pins number
	 */
	list = of_get_property(np, "rockchip,pins", &size);
	/* we करो not check वापस since it's safe node passed करोwn */
	size /= माप(*list);
	अगर (!size || size % 4) अणु
		dev_err(info->dev, "wrong pins number or pins and configs should be by 4\n");
		वापस -EINVAL;
	पूर्ण

	grp->npins = size / 4;

	grp->pins = devm_kसुस्मृति(info->dev, grp->npins, माप(अचिन्हित पूर्णांक),
						GFP_KERNEL);
	grp->data = devm_kसुस्मृति(info->dev,
					grp->npins,
					माप(काष्ठा rockchip_pin_config),
					GFP_KERNEL);
	अगर (!grp->pins || !grp->data)
		वापस -ENOMEM;

	क्रम (i = 0, j = 0; i < size; i += 4, j++) अणु
		स्थिर __be32 *phandle;
		काष्ठा device_node *np_config;

		num = be32_to_cpu(*list++);
		bank = bank_num_to_bank(info, num);
		अगर (IS_ERR(bank))
			वापस PTR_ERR(bank);

		grp->pins[j] = bank->pin_base + be32_to_cpu(*list++);
		grp->data[j].func = be32_to_cpu(*list++);

		phandle = list++;
		अगर (!phandle)
			वापस -EINVAL;

		np_config = of_find_node_by_phandle(be32_to_cpup(phandle));
		ret = pinconf_generic_parse_dt_config(np_config, शून्य,
				&grp->data[j].configs, &grp->data[j].nconfigs);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_pinctrl_parse_functions(काष्ठा device_node *np,
						काष्ठा rockchip_pinctrl *info,
						u32 index)
अणु
	काष्ठा device_node *child;
	काष्ठा rockchip_pmx_func *func;
	काष्ठा rockchip_pin_group *grp;
	पूर्णांक ret;
	अटल u32 grp_index;
	u32 i = 0;

	dev_dbg(info->dev, "parse function(%d): %pOFn\n", index, np);

	func = &info->functions[index];

	/* Initialise function */
	func->name = np->name;
	func->ngroups = of_get_child_count(np);
	अगर (func->ngroups <= 0)
		वापस 0;

	func->groups = devm_kसुस्मृति(info->dev,
			func->ngroups, माप(अक्षर *), GFP_KERNEL);
	अगर (!func->groups)
		वापस -ENOMEM;

	क्रम_each_child_of_node(np, child) अणु
		func->groups[i] = child->name;
		grp = &info->groups[grp_index++];
		ret = rockchip_pinctrl_parse_groups(child, grp, info, i++);
		अगर (ret) अणु
			of_node_put(child);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_pinctrl_parse_dt(काष्ठा platक्रमm_device *pdev,
					      काष्ठा rockchip_pinctrl *info)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *child;
	पूर्णांक ret;
	पूर्णांक i;

	rockchip_pinctrl_child_count(info, np);

	dev_dbg(&pdev->dev, "nfunctions = %d\n", info->nfunctions);
	dev_dbg(&pdev->dev, "ngroups = %d\n", info->ngroups);

	info->functions = devm_kसुस्मृति(dev,
					      info->nfunctions,
					      माप(काष्ठा rockchip_pmx_func),
					      GFP_KERNEL);
	अगर (!info->functions)
		वापस -ENOMEM;

	info->groups = devm_kसुस्मृति(dev,
					    info->ngroups,
					    माप(काष्ठा rockchip_pin_group),
					    GFP_KERNEL);
	अगर (!info->groups)
		वापस -ENOMEM;

	i = 0;

	क्रम_each_child_of_node(np, child) अणु
		अगर (of_match_node(rockchip_bank_match, child))
			जारी;

		ret = rockchip_pinctrl_parse_functions(child, info, i++);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to parse function\n");
			of_node_put(child);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_pinctrl_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
					काष्ठा rockchip_pinctrl *info)
अणु
	काष्ठा pinctrl_desc *ctrldesc = &info->pctl;
	काष्ठा pinctrl_pin_desc *pindesc, *pdesc;
	काष्ठा rockchip_pin_bank *pin_bank;
	पूर्णांक pin, bank, ret;
	पूर्णांक k;

	ctrldesc->name = "rockchip-pinctrl";
	ctrldesc->owner = THIS_MODULE;
	ctrldesc->pctlops = &rockchip_pctrl_ops;
	ctrldesc->pmxops = &rockchip_pmx_ops;
	ctrldesc->confops = &rockchip_pinconf_ops;

	pindesc = devm_kसुस्मृति(&pdev->dev,
			       info->ctrl->nr_pins, माप(*pindesc),
			       GFP_KERNEL);
	अगर (!pindesc)
		वापस -ENOMEM;

	ctrldesc->pins = pindesc;
	ctrldesc->npins = info->ctrl->nr_pins;

	pdesc = pindesc;
	क्रम (bank = 0 , k = 0; bank < info->ctrl->nr_banks; bank++) अणु
		pin_bank = &info->ctrl->pin_banks[bank];
		क्रम (pin = 0; pin < pin_bank->nr_pins; pin++, k++) अणु
			pdesc->number = k;
			pdesc->name = kaप्र_लिखो(GFP_KERNEL, "%s-%d",
						pin_bank->name, pin);
			pdesc++;
		पूर्ण
	पूर्ण

	ret = rockchip_pinctrl_parse_dt(pdev, info);
	अगर (ret)
		वापस ret;

	info->pctl_dev = devm_pinctrl_रेजिस्टर(&pdev->dev, ctrldesc, info);
	अगर (IS_ERR(info->pctl_dev)) अणु
		dev_err(&pdev->dev, "could not register pinctrl driver\n");
		वापस PTR_ERR(info->pctl_dev);
	पूर्ण

	क्रम (bank = 0; bank < info->ctrl->nr_banks; ++bank) अणु
		pin_bank = &info->ctrl->pin_banks[bank];
		pin_bank->grange.name = pin_bank->name;
		pin_bank->grange.id = bank;
		pin_bank->grange.pin_base = pin_bank->pin_base;
		pin_bank->grange.base = pin_bank->gpio_chip.base;
		pin_bank->grange.npins = pin_bank->gpio_chip.ngpio;
		pin_bank->grange.gc = &pin_bank->gpio_chip;
		pinctrl_add_gpio_range(info->pctl_dev, &pin_bank->grange);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * GPIO handling
 */

अटल व्योम rockchip_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा rockchip_pin_bank *bank = gpiochip_get_data(gc);
	व्योम __iomem *reg = bank->reg_base + GPIO_SWPORT_DR;
	अचिन्हित दीर्घ flags;
	u32 data;

	clk_enable(bank->clk);
	raw_spin_lock_irqsave(&bank->slock, flags);

	data = पढ़ोl(reg);
	data &= ~BIT(offset);
	अगर (value)
		data |= BIT(offset);
	ग_लिखोl(data, reg);

	raw_spin_unlock_irqrestore(&bank->slock, flags);
	clk_disable(bank->clk);
पूर्ण

/*
 * Returns the level of the pin क्रम input direction and setting of the DR
 * रेजिस्टर क्रम output gpios.
 */
अटल पूर्णांक rockchip_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा rockchip_pin_bank *bank = gpiochip_get_data(gc);
	u32 data;

	clk_enable(bank->clk);
	data = पढ़ोl(bank->reg_base + GPIO_EXT_PORT);
	clk_disable(bank->clk);
	data >>= offset;
	data &= 1;
	वापस data;
पूर्ण

/*
 * gpiolib gpio_direction_input callback function. The setting of the pin
 * mux function as 'gpio input' will be handled by the pinctrl subप्रणाली
 * पूर्णांकerface.
 */
अटल पूर्णांक rockchip_gpio_direction_input(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	वापस pinctrl_gpio_direction_input(gc->base + offset);
पूर्ण

/*
 * gpiolib gpio_direction_output callback function. The setting of the pin
 * mux function as 'gpio output' will be handled by the pinctrl subप्रणाली
 * पूर्णांकerface.
 */
अटल पूर्णांक rockchip_gpio_direction_output(काष्ठा gpio_chip *gc,
					  अचिन्हित offset, पूर्णांक value)
अणु
	rockchip_gpio_set(gc, offset, value);
	वापस pinctrl_gpio_direction_output(gc->base + offset);
पूर्ण

अटल व्योम rockchip_gpio_set_debounce(काष्ठा gpio_chip *gc,
				       अचिन्हित पूर्णांक offset, bool enable)
अणु
	काष्ठा rockchip_pin_bank *bank = gpiochip_get_data(gc);
	व्योम __iomem *reg = bank->reg_base + GPIO_DEBOUNCE;
	अचिन्हित दीर्घ flags;
	u32 data;

	clk_enable(bank->clk);
	raw_spin_lock_irqsave(&bank->slock, flags);

	data = पढ़ोl(reg);
	अगर (enable)
		data |= BIT(offset);
	अन्यथा
		data &= ~BIT(offset);
	ग_लिखोl(data, reg);

	raw_spin_unlock_irqrestore(&bank->slock, flags);
	clk_disable(bank->clk);
पूर्ण

/*
 * gpiolib set_config callback function. The setting of the pin
 * mux function as 'gpio output' will be handled by the pinctrl subप्रणाली
 * पूर्णांकerface.
 */
अटल पूर्णांक rockchip_gpio_set_config(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset,
				  अचिन्हित दीर्घ config)
अणु
	क्रमागत pin_config_param param = pinconf_to_config_param(config);

	चयन (param) अणु
	हाल PIN_CONFIG_INPUT_DEBOUNCE:
		rockchip_gpio_set_debounce(gc, offset, true);
		/*
		 * Rockchip's gpio could only support up to one period
		 * of the debounce घड़ी(pclk), which is far away from
		 * satisftying the requirement, as pclk is usually near
		 * 100MHz shared by all peripherals. So the fact is it
		 * has crippled debounce capability could only be useful
		 * to prevent any spurious glitches from waking up the प्रणाली
		 * अगर the gpio is conguired as wakeup पूर्णांकerrupt source. Let's
		 * still वापस -ENOTSUPP as beक्रमe, to make sure the caller
		 * of gpiod_set_debounce won't change its behaviour.
		 */
		वापस -ENOTSUPP;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

/*
 * gpiolib gpio_to_irq callback function. Creates a mapping between a GPIO pin
 * and a भव IRQ, अगर not alपढ़ोy present.
 */
अटल पूर्णांक rockchip_gpio_to_irq(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा rockchip_pin_bank *bank = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक virq;

	अगर (!bank->करोमुख्य)
		वापस -ENXIO;

	clk_enable(bank->clk);
	virq = irq_create_mapping(bank->करोमुख्य, offset);
	clk_disable(bank->clk);

	वापस (virq) ? : -ENXIO;
पूर्ण

अटल स्थिर काष्ठा gpio_chip rockchip_gpiolib_chip = अणु
	.request = gpiochip_generic_request,
	.मुक्त = gpiochip_generic_मुक्त,
	.set = rockchip_gpio_set,
	.get = rockchip_gpio_get,
	.get_direction	= rockchip_gpio_get_direction,
	.direction_input = rockchip_gpio_direction_input,
	.direction_output = rockchip_gpio_direction_output,
	.set_config = rockchip_gpio_set_config,
	.to_irq = rockchip_gpio_to_irq,
	.owner = THIS_MODULE,
पूर्ण;

/*
 * Interrupt handling
 */

अटल व्योम rockchip_irq_demux(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा rockchip_pin_bank *bank = irq_desc_get_handler_data(desc);
	u32 pend;

	dev_dbg(bank->drvdata->dev, "got irq for bank %s\n", bank->name);

	chained_irq_enter(chip, desc);

	pend = पढ़ोl_relaxed(bank->reg_base + GPIO_INT_STATUS);

	जबतक (pend) अणु
		अचिन्हित पूर्णांक irq, virq;

		irq = __ffs(pend);
		pend &= ~BIT(irq);
		virq = irq_find_mapping(bank->करोमुख्य, irq);

		अगर (!virq) अणु
			dev_err(bank->drvdata->dev, "unmapped irq %d\n", irq);
			जारी;
		पूर्ण

		dev_dbg(bank->drvdata->dev, "handling irq %d\n", irq);

		/*
		 * Triggering IRQ on both rising and falling edge
		 * needs manual पूर्णांकervention.
		 */
		अगर (bank->toggle_edge_mode & BIT(irq)) अणु
			u32 data, data_old, polarity;
			अचिन्हित दीर्घ flags;

			data = पढ़ोl_relaxed(bank->reg_base + GPIO_EXT_PORT);
			करो अणु
				raw_spin_lock_irqsave(&bank->slock, flags);

				polarity = पढ़ोl_relaxed(bank->reg_base +
							 GPIO_INT_POLARITY);
				अगर (data & BIT(irq))
					polarity &= ~BIT(irq);
				अन्यथा
					polarity |= BIT(irq);
				ग_लिखोl(polarity,
				       bank->reg_base + GPIO_INT_POLARITY);

				raw_spin_unlock_irqrestore(&bank->slock, flags);

				data_old = data;
				data = पढ़ोl_relaxed(bank->reg_base +
						     GPIO_EXT_PORT);
			पूर्ण जबतक ((data & BIT(irq)) != (data_old & BIT(irq)));
		पूर्ण

		generic_handle_irq(virq);
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल पूर्णांक rockchip_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा rockchip_pin_bank *bank = gc->निजी;
	u32 mask = BIT(d->hwirq);
	u32 polarity;
	u32 level;
	u32 data;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* make sure the pin is configured as gpio input */
	ret = rockchip_set_mux(bank, d->hwirq, RK_FUNC_GPIO);
	अगर (ret < 0)
		वापस ret;

	clk_enable(bank->clk);
	raw_spin_lock_irqsave(&bank->slock, flags);

	data = पढ़ोl_relaxed(bank->reg_base + GPIO_SWPORT_DDR);
	data &= ~mask;
	ग_लिखोl_relaxed(data, bank->reg_base + GPIO_SWPORT_DDR);

	raw_spin_unlock_irqrestore(&bank->slock, flags);

	अगर (type & IRQ_TYPE_EDGE_BOTH)
		irq_set_handler_locked(d, handle_edge_irq);
	अन्यथा
		irq_set_handler_locked(d, handle_level_irq);

	raw_spin_lock_irqsave(&bank->slock, flags);
	irq_gc_lock(gc);

	level = पढ़ोl_relaxed(gc->reg_base + GPIO_INTTYPE_LEVEL);
	polarity = पढ़ोl_relaxed(gc->reg_base + GPIO_INT_POLARITY);

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_BOTH:
		bank->toggle_edge_mode |= mask;
		level |= mask;

		/*
		 * Determine gpio state. If 1 next पूर्णांकerrupt should be falling
		 * otherwise rising.
		 */
		data = पढ़ोl(bank->reg_base + GPIO_EXT_PORT);
		अगर (data & mask)
			polarity &= ~mask;
		अन्यथा
			polarity |= mask;
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		bank->toggle_edge_mode &= ~mask;
		level |= mask;
		polarity |= mask;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		bank->toggle_edge_mode &= ~mask;
		level |= mask;
		polarity &= ~mask;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		bank->toggle_edge_mode &= ~mask;
		level &= ~mask;
		polarity |= mask;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		bank->toggle_edge_mode &= ~mask;
		level &= ~mask;
		polarity &= ~mask;
		अवरोध;
	शेष:
		irq_gc_unlock(gc);
		raw_spin_unlock_irqrestore(&bank->slock, flags);
		clk_disable(bank->clk);
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl_relaxed(level, gc->reg_base + GPIO_INTTYPE_LEVEL);
	ग_लिखोl_relaxed(polarity, gc->reg_base + GPIO_INT_POLARITY);

	irq_gc_unlock(gc);
	raw_spin_unlock_irqrestore(&bank->slock, flags);
	clk_disable(bank->clk);

	वापस 0;
पूर्ण

अटल व्योम rockchip_irq_suspend(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा rockchip_pin_bank *bank = gc->निजी;

	clk_enable(bank->clk);
	bank->saved_masks = irq_reg_पढ़ोl(gc, GPIO_INTMASK);
	irq_reg_ग_लिखोl(gc, ~gc->wake_active, GPIO_INTMASK);
	clk_disable(bank->clk);
पूर्ण

अटल व्योम rockchip_irq_resume(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा rockchip_pin_bank *bank = gc->निजी;

	clk_enable(bank->clk);
	irq_reg_ग_लिखोl(gc, bank->saved_masks, GPIO_INTMASK);
	clk_disable(bank->clk);
पूर्ण

अटल व्योम rockchip_irq_enable(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा rockchip_pin_bank *bank = gc->निजी;

	clk_enable(bank->clk);
	irq_gc_mask_clr_bit(d);
पूर्ण

अटल व्योम rockchip_irq_disable(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा rockchip_pin_bank *bank = gc->निजी;

	irq_gc_mask_set_bit(d);
	clk_disable(bank->clk);
पूर्ण

अटल पूर्णांक rockchip_पूर्णांकerrupts_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
						काष्ठा rockchip_pinctrl *info)
अणु
	काष्ठा rockchip_pin_ctrl *ctrl = info->ctrl;
	काष्ठा rockchip_pin_bank *bank = ctrl->pin_banks;
	अचिन्हित पूर्णांक clr = IRQ_NOREQUEST | IRQ_NOPROBE | IRQ_NOAUTOEN;
	काष्ठा irq_chip_generic *gc;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < ctrl->nr_banks; ++i, ++bank) अणु
		अगर (!bank->valid) अणु
			dev_warn(&pdev->dev, "bank %s is not valid\n",
				 bank->name);
			जारी;
		पूर्ण

		ret = clk_enable(bank->clk);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to enable clock for bank %s\n",
				bank->name);
			जारी;
		पूर्ण

		bank->करोमुख्य = irq_करोमुख्य_add_linear(bank->of_node, 32,
						&irq_generic_chip_ops, शून्य);
		अगर (!bank->करोमुख्य) अणु
			dev_warn(&pdev->dev, "could not initialize irq domain for bank %s\n",
				 bank->name);
			clk_disable(bank->clk);
			जारी;
		पूर्ण

		ret = irq_alloc_करोमुख्य_generic_chips(bank->करोमुख्य, 32, 1,
					 "rockchip_gpio_irq", handle_level_irq,
					 clr, 0, 0);
		अगर (ret) अणु
			dev_err(&pdev->dev, "could not alloc generic chips for bank %s\n",
				bank->name);
			irq_करोमुख्य_हटाओ(bank->करोमुख्य);
			clk_disable(bank->clk);
			जारी;
		पूर्ण

		gc = irq_get_करोमुख्य_generic_chip(bank->करोमुख्य, 0);
		gc->reg_base = bank->reg_base;
		gc->निजी = bank;
		gc->chip_types[0].regs.mask = GPIO_INTMASK;
		gc->chip_types[0].regs.ack = GPIO_PORTS_EOI;
		gc->chip_types[0].chip.irq_ack = irq_gc_ack_set_bit;
		gc->chip_types[0].chip.irq_mask = irq_gc_mask_set_bit;
		gc->chip_types[0].chip.irq_unmask = irq_gc_mask_clr_bit;
		gc->chip_types[0].chip.irq_enable = rockchip_irq_enable;
		gc->chip_types[0].chip.irq_disable = rockchip_irq_disable;
		gc->chip_types[0].chip.irq_set_wake = irq_gc_set_wake;
		gc->chip_types[0].chip.irq_suspend = rockchip_irq_suspend;
		gc->chip_types[0].chip.irq_resume = rockchip_irq_resume;
		gc->chip_types[0].chip.irq_set_type = rockchip_irq_set_type;
		gc->wake_enabled = IRQ_MSK(bank->nr_pins);

		/*
		 * Linux assumes that all पूर्णांकerrupts start out disabled/masked.
		 * Our driver only uses the concept of masked and always keeps
		 * things enabled, so क्रम us that's all masked and all enabled.
		 */
		ग_लिखोl_relaxed(0xffffffff, bank->reg_base + GPIO_INTMASK);
		ग_लिखोl_relaxed(0xffffffff, bank->reg_base + GPIO_PORTS_EOI);
		ग_लिखोl_relaxed(0xffffffff, bank->reg_base + GPIO_INTEN);
		gc->mask_cache = 0xffffffff;

		irq_set_chained_handler_and_data(bank->irq,
						 rockchip_irq_demux, bank);
		clk_disable(bank->clk);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_gpiolib_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
						काष्ठा rockchip_pinctrl *info)
अणु
	काष्ठा rockchip_pin_ctrl *ctrl = info->ctrl;
	काष्ठा rockchip_pin_bank *bank = ctrl->pin_banks;
	काष्ठा gpio_chip *gc;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < ctrl->nr_banks; ++i, ++bank) अणु
		अगर (!bank->valid) अणु
			dev_warn(&pdev->dev, "bank %s is not valid\n",
				 bank->name);
			जारी;
		पूर्ण

		bank->gpio_chip = rockchip_gpiolib_chip;

		gc = &bank->gpio_chip;
		gc->base = bank->pin_base;
		gc->ngpio = bank->nr_pins;
		gc->parent = &pdev->dev;
		gc->of_node = bank->of_node;
		gc->label = bank->name;

		ret = gpiochip_add_data(gc, bank);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to register gpio_chip %s, error code: %d\n",
							gc->label, ret);
			जाओ fail;
		पूर्ण
	पूर्ण

	rockchip_पूर्णांकerrupts_रेजिस्टर(pdev, info);

	वापस 0;

fail:
	क्रम (--i, --bank; i >= 0; --i, --bank) अणु
		अगर (!bank->valid)
			जारी;
		gpiochip_हटाओ(&bank->gpio_chip);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक rockchip_gpiolib_unरेजिस्टर(काष्ठा platक्रमm_device *pdev,
						काष्ठा rockchip_pinctrl *info)
अणु
	काष्ठा rockchip_pin_ctrl *ctrl = info->ctrl;
	काष्ठा rockchip_pin_bank *bank = ctrl->pin_banks;
	पूर्णांक i;

	क्रम (i = 0; i < ctrl->nr_banks; ++i, ++bank) अणु
		अगर (!bank->valid)
			जारी;
		gpiochip_हटाओ(&bank->gpio_chip);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_get_bank_data(काष्ठा rockchip_pin_bank *bank,
				  काष्ठा rockchip_pinctrl *info)
अणु
	काष्ठा resource res;
	व्योम __iomem *base;

	अगर (of_address_to_resource(bank->of_node, 0, &res)) अणु
		dev_err(info->dev, "cannot find IO resource for bank\n");
		वापस -ENOENT;
	पूर्ण

	bank->reg_base = devm_ioremap_resource(info->dev, &res);
	अगर (IS_ERR(bank->reg_base))
		वापस PTR_ERR(bank->reg_base);

	/*
	 * special हाल, where parts of the pull setting-रेजिस्टरs are
	 * part of the PMU रेजिस्टर space
	 */
	अगर (of_device_is_compatible(bank->of_node,
				    "rockchip,rk3188-gpio-bank0")) अणु
		काष्ठा device_node *node;

		node = of_parse_phandle(bank->of_node->parent,
					"rockchip,pmu", 0);
		अगर (!node) अणु
			अगर (of_address_to_resource(bank->of_node, 1, &res)) अणु
				dev_err(info->dev, "cannot find IO resource for bank\n");
				वापस -ENOENT;
			पूर्ण

			base = devm_ioremap_resource(info->dev, &res);
			अगर (IS_ERR(base))
				वापस PTR_ERR(base);
			rockchip_regmap_config.max_रेजिस्टर =
						    resource_size(&res) - 4;
			rockchip_regmap_config.name =
					    "rockchip,rk3188-gpio-bank0-pull";
			bank->regmap_pull = devm_regmap_init_mmio(info->dev,
						    base,
						    &rockchip_regmap_config);
		पूर्ण
		of_node_put(node);
	पूर्ण

	bank->irq = irq_of_parse_and_map(bank->of_node, 0);

	bank->clk = of_clk_get(bank->of_node, 0);
	अगर (IS_ERR(bank->clk))
		वापस PTR_ERR(bank->clk);

	वापस clk_prepare(bank->clk);
पूर्ण

अटल स्थिर काष्ठा of_device_id rockchip_pinctrl_dt_match[];

/* retrieve the soc specअगरic data */
अटल काष्ठा rockchip_pin_ctrl *rockchip_pinctrl_get_soc_data(
						काष्ठा rockchip_pinctrl *d,
						काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा device_node *np;
	काष्ठा rockchip_pin_ctrl *ctrl;
	काष्ठा rockchip_pin_bank *bank;
	पूर्णांक grf_offs, pmu_offs, drv_grf_offs, drv_pmu_offs, i, j;

	match = of_match_node(rockchip_pinctrl_dt_match, node);
	ctrl = (काष्ठा rockchip_pin_ctrl *)match->data;

	क्रम_each_child_of_node(node, np) अणु
		अगर (!of_find_property(np, "gpio-controller", शून्य))
			जारी;

		bank = ctrl->pin_banks;
		क्रम (i = 0; i < ctrl->nr_banks; ++i, ++bank) अणु
			अगर (!म_भेद(bank->name, np->name)) अणु
				bank->of_node = np;

				अगर (!rockchip_get_bank_data(bank, d))
					bank->valid = true;

				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	grf_offs = ctrl->grf_mux_offset;
	pmu_offs = ctrl->pmu_mux_offset;
	drv_pmu_offs = ctrl->pmu_drv_offset;
	drv_grf_offs = ctrl->grf_drv_offset;
	bank = ctrl->pin_banks;
	क्रम (i = 0; i < ctrl->nr_banks; ++i, ++bank) अणु
		पूर्णांक bank_pins = 0;

		raw_spin_lock_init(&bank->slock);
		bank->drvdata = d;
		bank->pin_base = ctrl->nr_pins;
		ctrl->nr_pins += bank->nr_pins;

		/* calculate iomux and drv offsets */
		क्रम (j = 0; j < 4; j++) अणु
			काष्ठा rockchip_iomux *iom = &bank->iomux[j];
			काष्ठा rockchip_drv *drv = &bank->drv[j];
			पूर्णांक inc;

			अगर (bank_pins >= bank->nr_pins)
				अवरोध;

			/* preset iomux offset value, set new start value */
			अगर (iom->offset >= 0) अणु
				अगर (iom->type & IOMUX_SOURCE_PMU)
					pmu_offs = iom->offset;
				अन्यथा
					grf_offs = iom->offset;
			पूर्ण अन्यथा अणु /* set current iomux offset */
				iom->offset = (iom->type & IOMUX_SOURCE_PMU) ?
							pmu_offs : grf_offs;
			पूर्ण

			/* preset drv offset value, set new start value */
			अगर (drv->offset >= 0) अणु
				अगर (iom->type & IOMUX_SOURCE_PMU)
					drv_pmu_offs = drv->offset;
				अन्यथा
					drv_grf_offs = drv->offset;
			पूर्ण अन्यथा अणु /* set current drv offset */
				drv->offset = (iom->type & IOMUX_SOURCE_PMU) ?
						drv_pmu_offs : drv_grf_offs;
			पूर्ण

			dev_dbg(d->dev, "bank %d, iomux %d has iom_offset 0x%x drv_offset 0x%x\n",
				i, j, iom->offset, drv->offset);

			/*
			 * Increase offset according to iomux width.
			 * 4bit iomux'es are spपढ़ो over two रेजिस्टरs.
			 */
			inc = (iom->type & (IOMUX_WIDTH_4BIT |
					    IOMUX_WIDTH_3BIT |
					    IOMUX_WIDTH_2BIT)) ? 8 : 4;
			अगर (iom->type & IOMUX_SOURCE_PMU)
				pmu_offs += inc;
			अन्यथा
				grf_offs += inc;

			/*
			 * Increase offset according to drv width.
			 * 3bit drive-strenth'es are spपढ़ो over two रेजिस्टरs.
			 */
			अगर ((drv->drv_type == DRV_TYPE_IO_1V8_3V0_AUTO) ||
			    (drv->drv_type == DRV_TYPE_IO_3V3_ONLY))
				inc = 8;
			अन्यथा
				inc = 4;

			अगर (iom->type & IOMUX_SOURCE_PMU)
				drv_pmu_offs += inc;
			अन्यथा
				drv_grf_offs += inc;

			bank_pins += 8;
		पूर्ण

		/* calculate the per-bank recalced_mask */
		क्रम (j = 0; j < ctrl->niomux_recalced; j++) अणु
			पूर्णांक pin = 0;

			अगर (ctrl->iomux_recalced[j].num == bank->bank_num) अणु
				pin = ctrl->iomux_recalced[j].pin;
				bank->recalced_mask |= BIT(pin);
			पूर्ण
		पूर्ण

		/* calculate the per-bank route_mask */
		क्रम (j = 0; j < ctrl->niomux_routes; j++) अणु
			पूर्णांक pin = 0;

			अगर (ctrl->iomux_routes[j].bank_num == bank->bank_num) अणु
				pin = ctrl->iomux_routes[j].pin;
				bank->route_mask |= BIT(pin);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ctrl;
पूर्ण

#घोषणा RK3288_GRF_GPIO6C_IOMUX		0x64
#घोषणा GPIO6C6_SEL_WRITE_ENABLE	BIT(28)

अटल u32 rk3288_grf_gpio6c_iomux;

अटल पूर्णांक __maybe_unused rockchip_pinctrl_suspend(काष्ठा device *dev)
अणु
	काष्ठा rockchip_pinctrl *info = dev_get_drvdata(dev);
	पूर्णांक ret = pinctrl_क्रमce_sleep(info->pctl_dev);

	अगर (ret)
		वापस ret;

	/*
	 * RK3288 GPIO6_C6 mux would be modअगरied by Maskrom when resume, so save
	 * the setting here, and restore it at resume.
	 */
	अगर (info->ctrl->type == RK3288) अणु
		ret = regmap_पढ़ो(info->regmap_base, RK3288_GRF_GPIO6C_IOMUX,
				  &rk3288_grf_gpio6c_iomux);
		अगर (ret) अणु
			pinctrl_क्रमce_शेष(info->pctl_dev);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rockchip_pinctrl_resume(काष्ठा device *dev)
अणु
	काष्ठा rockchip_pinctrl *info = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (info->ctrl->type == RK3288) अणु
		ret = regmap_ग_लिखो(info->regmap_base, RK3288_GRF_GPIO6C_IOMUX,
				   rk3288_grf_gpio6c_iomux |
				   GPIO6C6_SEL_WRITE_ENABLE);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस pinctrl_क्रमce_शेष(info->pctl_dev);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(rockchip_pinctrl_dev_pm_ops, rockchip_pinctrl_suspend,
			 rockchip_pinctrl_resume);

अटल पूर्णांक rockchip_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rockchip_pinctrl *info;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rockchip_pin_ctrl *ctrl;
	काष्ठा device_node *np = pdev->dev.of_node, *node;
	काष्ठा resource *res;
	व्योम __iomem *base;
	पूर्णांक ret;

	अगर (!dev->of_node) अणु
		dev_err(dev, "device tree node not found\n");
		वापस -ENODEV;
	पूर्ण

	info = devm_kzalloc(dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->dev = dev;

	ctrl = rockchip_pinctrl_get_soc_data(info, pdev);
	अगर (!ctrl) अणु
		dev_err(dev, "driver data not available\n");
		वापस -EINVAL;
	पूर्ण
	info->ctrl = ctrl;

	node = of_parse_phandle(np, "rockchip,grf", 0);
	अगर (node) अणु
		info->regmap_base = syscon_node_to_regmap(node);
		अगर (IS_ERR(info->regmap_base))
			वापस PTR_ERR(info->regmap_base);
	पूर्ण अन्यथा अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
		base = devm_ioremap_resource(&pdev->dev, res);
		अगर (IS_ERR(base))
			वापस PTR_ERR(base);

		rockchip_regmap_config.max_रेजिस्टर = resource_size(res) - 4;
		rockchip_regmap_config.name = "rockchip,pinctrl";
		info->regmap_base = devm_regmap_init_mmio(&pdev->dev, base,
						    &rockchip_regmap_config);

		/* to check क्रम the old dt-bindings */
		info->reg_size = resource_size(res);

		/* Honor the old binding, with pull रेजिस्टरs as 2nd resource */
		अगर (ctrl->type == RK3188 && info->reg_size < 0x200) अणु
			res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
			base = devm_ioremap_resource(&pdev->dev, res);
			अगर (IS_ERR(base))
				वापस PTR_ERR(base);

			rockchip_regmap_config.max_रेजिस्टर =
							resource_size(res) - 4;
			rockchip_regmap_config.name = "rockchip,pinctrl-pull";
			info->regmap_pull = devm_regmap_init_mmio(&pdev->dev,
						    base,
						    &rockchip_regmap_config);
		पूर्ण
	पूर्ण

	/* try to find the optional reference to the pmu syscon */
	node = of_parse_phandle(np, "rockchip,pmu", 0);
	अगर (node) अणु
		info->regmap_pmu = syscon_node_to_regmap(node);
		अगर (IS_ERR(info->regmap_pmu))
			वापस PTR_ERR(info->regmap_pmu);
	पूर्ण

	ret = rockchip_gpiolib_रेजिस्टर(pdev, info);
	अगर (ret)
		वापस ret;

	ret = rockchip_pinctrl_रेजिस्टर(pdev, info);
	अगर (ret) अणु
		rockchip_gpiolib_unरेजिस्टर(pdev, info);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, info);

	वापस 0;
पूर्ण

अटल काष्ठा rockchip_pin_bank px30_pin_banks[] = अणु
	PIN_BANK_IOMUX_FLAGS(0, 32, "gpio0", IOMUX_SOURCE_PMU,
					     IOMUX_SOURCE_PMU,
					     IOMUX_SOURCE_PMU,
					     IOMUX_SOURCE_PMU
			    ),
	PIN_BANK_IOMUX_FLAGS(1, 32, "gpio1", IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT
			    ),
	PIN_BANK_IOMUX_FLAGS(2, 32, "gpio2", IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT
			    ),
	PIN_BANK_IOMUX_FLAGS(3, 32, "gpio3", IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT
			    ),
पूर्ण;

अटल काष्ठा rockchip_pin_ctrl px30_pin_ctrl = अणु
		.pin_banks		= px30_pin_banks,
		.nr_banks		= ARRAY_SIZE(px30_pin_banks),
		.label			= "PX30-GPIO",
		.type			= PX30,
		.grf_mux_offset		= 0x0,
		.pmu_mux_offset		= 0x0,
		.iomux_routes		= px30_mux_route_data,
		.niomux_routes		= ARRAY_SIZE(px30_mux_route_data),
		.pull_calc_reg		= px30_calc_pull_reg_and_bit,
		.drv_calc_reg		= px30_calc_drv_reg_and_bit,
		.schmitt_calc_reg	= px30_calc_schmitt_reg_and_bit,
पूर्ण;

अटल काष्ठा rockchip_pin_bank rv1108_pin_banks[] = अणु
	PIN_BANK_IOMUX_FLAGS(0, 32, "gpio0", IOMUX_SOURCE_PMU,
					     IOMUX_SOURCE_PMU,
					     IOMUX_SOURCE_PMU,
					     IOMUX_SOURCE_PMU),
	PIN_BANK_IOMUX_FLAGS(1, 32, "gpio1", 0, 0, 0, 0),
	PIN_BANK_IOMUX_FLAGS(2, 32, "gpio2", 0, 0, 0, 0),
	PIN_BANK_IOMUX_FLAGS(3, 32, "gpio3", 0, 0, 0, 0),
पूर्ण;

अटल काष्ठा rockchip_pin_ctrl rv1108_pin_ctrl = अणु
	.pin_banks		= rv1108_pin_banks,
	.nr_banks		= ARRAY_SIZE(rv1108_pin_banks),
	.label			= "RV1108-GPIO",
	.type			= RV1108,
	.grf_mux_offset		= 0x10,
	.pmu_mux_offset		= 0x0,
	.iomux_recalced		= rv1108_mux_recalced_data,
	.niomux_recalced	= ARRAY_SIZE(rv1108_mux_recalced_data),
	.pull_calc_reg		= rv1108_calc_pull_reg_and_bit,
	.drv_calc_reg		= rv1108_calc_drv_reg_and_bit,
	.schmitt_calc_reg	= rv1108_calc_schmitt_reg_and_bit,
पूर्ण;

अटल काष्ठा rockchip_pin_bank rk2928_pin_banks[] = अणु
	PIN_BANK(0, 32, "gpio0"),
	PIN_BANK(1, 32, "gpio1"),
	PIN_BANK(2, 32, "gpio2"),
	PIN_BANK(3, 32, "gpio3"),
पूर्ण;

अटल काष्ठा rockchip_pin_ctrl rk2928_pin_ctrl = अणु
		.pin_banks		= rk2928_pin_banks,
		.nr_banks		= ARRAY_SIZE(rk2928_pin_banks),
		.label			= "RK2928-GPIO",
		.type			= RK2928,
		.grf_mux_offset		= 0xa8,
		.pull_calc_reg		= rk2928_calc_pull_reg_and_bit,
पूर्ण;

अटल काष्ठा rockchip_pin_bank rk3036_pin_banks[] = अणु
	PIN_BANK(0, 32, "gpio0"),
	PIN_BANK(1, 32, "gpio1"),
	PIN_BANK(2, 32, "gpio2"),
पूर्ण;

अटल काष्ठा rockchip_pin_ctrl rk3036_pin_ctrl = अणु
		.pin_banks		= rk3036_pin_banks,
		.nr_banks		= ARRAY_SIZE(rk3036_pin_banks),
		.label			= "RK3036-GPIO",
		.type			= RK2928,
		.grf_mux_offset		= 0xa8,
		.pull_calc_reg		= rk2928_calc_pull_reg_and_bit,
पूर्ण;

अटल काष्ठा rockchip_pin_bank rk3066a_pin_banks[] = अणु
	PIN_BANK(0, 32, "gpio0"),
	PIN_BANK(1, 32, "gpio1"),
	PIN_BANK(2, 32, "gpio2"),
	PIN_BANK(3, 32, "gpio3"),
	PIN_BANK(4, 32, "gpio4"),
	PIN_BANK(6, 16, "gpio6"),
पूर्ण;

अटल काष्ठा rockchip_pin_ctrl rk3066a_pin_ctrl = अणु
		.pin_banks		= rk3066a_pin_banks,
		.nr_banks		= ARRAY_SIZE(rk3066a_pin_banks),
		.label			= "RK3066a-GPIO",
		.type			= RK2928,
		.grf_mux_offset		= 0xa8,
		.pull_calc_reg		= rk2928_calc_pull_reg_and_bit,
पूर्ण;

अटल काष्ठा rockchip_pin_bank rk3066b_pin_banks[] = अणु
	PIN_BANK(0, 32, "gpio0"),
	PIN_BANK(1, 32, "gpio1"),
	PIN_BANK(2, 32, "gpio2"),
	PIN_BANK(3, 32, "gpio3"),
पूर्ण;

अटल काष्ठा rockchip_pin_ctrl rk3066b_pin_ctrl = अणु
		.pin_banks	= rk3066b_pin_banks,
		.nr_banks	= ARRAY_SIZE(rk3066b_pin_banks),
		.label		= "RK3066b-GPIO",
		.type		= RK3066B,
		.grf_mux_offset	= 0x60,
पूर्ण;

अटल काष्ठा rockchip_pin_bank rk3128_pin_banks[] = अणु
	PIN_BANK(0, 32, "gpio0"),
	PIN_BANK(1, 32, "gpio1"),
	PIN_BANK(2, 32, "gpio2"),
	PIN_BANK(3, 32, "gpio3"),
पूर्ण;

अटल काष्ठा rockchip_pin_ctrl rk3128_pin_ctrl = अणु
		.pin_banks		= rk3128_pin_banks,
		.nr_banks		= ARRAY_SIZE(rk3128_pin_banks),
		.label			= "RK3128-GPIO",
		.type			= RK3128,
		.grf_mux_offset		= 0xa8,
		.iomux_recalced		= rk3128_mux_recalced_data,
		.niomux_recalced	= ARRAY_SIZE(rk3128_mux_recalced_data),
		.iomux_routes		= rk3128_mux_route_data,
		.niomux_routes		= ARRAY_SIZE(rk3128_mux_route_data),
		.pull_calc_reg		= rk3128_calc_pull_reg_and_bit,
पूर्ण;

अटल काष्ठा rockchip_pin_bank rk3188_pin_banks[] = अणु
	PIN_BANK_IOMUX_FLAGS(0, 32, "gpio0", IOMUX_GPIO_ONLY, 0, 0, 0),
	PIN_BANK(1, 32, "gpio1"),
	PIN_BANK(2, 32, "gpio2"),
	PIN_BANK(3, 32, "gpio3"),
पूर्ण;

अटल काष्ठा rockchip_pin_ctrl rk3188_pin_ctrl = अणु
		.pin_banks		= rk3188_pin_banks,
		.nr_banks		= ARRAY_SIZE(rk3188_pin_banks),
		.label			= "RK3188-GPIO",
		.type			= RK3188,
		.grf_mux_offset		= 0x60,
		.iomux_routes		= rk3188_mux_route_data,
		.niomux_routes		= ARRAY_SIZE(rk3188_mux_route_data),
		.pull_calc_reg		= rk3188_calc_pull_reg_and_bit,
पूर्ण;

अटल काष्ठा rockchip_pin_bank rk3228_pin_banks[] = अणु
	PIN_BANK(0, 32, "gpio0"),
	PIN_BANK(1, 32, "gpio1"),
	PIN_BANK(2, 32, "gpio2"),
	PIN_BANK(3, 32, "gpio3"),
पूर्ण;

अटल काष्ठा rockchip_pin_ctrl rk3228_pin_ctrl = अणु
		.pin_banks		= rk3228_pin_banks,
		.nr_banks		= ARRAY_SIZE(rk3228_pin_banks),
		.label			= "RK3228-GPIO",
		.type			= RK3288,
		.grf_mux_offset		= 0x0,
		.iomux_routes		= rk3228_mux_route_data,
		.niomux_routes		= ARRAY_SIZE(rk3228_mux_route_data),
		.pull_calc_reg		= rk3228_calc_pull_reg_and_bit,
		.drv_calc_reg		= rk3228_calc_drv_reg_and_bit,
पूर्ण;

अटल काष्ठा rockchip_pin_bank rk3288_pin_banks[] = अणु
	PIN_BANK_IOMUX_FLAGS(0, 24, "gpio0", IOMUX_SOURCE_PMU,
					     IOMUX_SOURCE_PMU,
					     IOMUX_SOURCE_PMU,
					     IOMUX_UNROUTED
			    ),
	PIN_BANK_IOMUX_FLAGS(1, 32, "gpio1", IOMUX_UNROUTED,
					     IOMUX_UNROUTED,
					     IOMUX_UNROUTED,
					     0
			    ),
	PIN_BANK_IOMUX_FLAGS(2, 32, "gpio2", 0, 0, 0, IOMUX_UNROUTED),
	PIN_BANK_IOMUX_FLAGS(3, 32, "gpio3", 0, 0, 0, IOMUX_WIDTH_4BIT),
	PIN_BANK_IOMUX_FLAGS(4, 32, "gpio4", IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     0,
					     0
			    ),
	PIN_BANK_IOMUX_FLAGS(5, 32, "gpio5", IOMUX_UNROUTED,
					     0,
					     0,
					     IOMUX_UNROUTED
			    ),
	PIN_BANK_IOMUX_FLAGS(6, 32, "gpio6", 0, 0, 0, IOMUX_UNROUTED),
	PIN_BANK_IOMUX_FLAGS(7, 32, "gpio7", 0,
					     0,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_UNROUTED
			    ),
	PIN_BANK(8, 16, "gpio8"),
पूर्ण;

अटल काष्ठा rockchip_pin_ctrl rk3288_pin_ctrl = अणु
		.pin_banks		= rk3288_pin_banks,
		.nr_banks		= ARRAY_SIZE(rk3288_pin_banks),
		.label			= "RK3288-GPIO",
		.type			= RK3288,
		.grf_mux_offset		= 0x0,
		.pmu_mux_offset		= 0x84,
		.iomux_routes		= rk3288_mux_route_data,
		.niomux_routes		= ARRAY_SIZE(rk3288_mux_route_data),
		.pull_calc_reg		= rk3288_calc_pull_reg_and_bit,
		.drv_calc_reg		= rk3288_calc_drv_reg_and_bit,
पूर्ण;

अटल काष्ठा rockchip_pin_bank rk3308_pin_banks[] = अणु
	PIN_BANK_IOMUX_FLAGS(0, 32, "gpio0", IOMUX_WIDTH_2BIT,
					     IOMUX_WIDTH_2BIT,
					     IOMUX_WIDTH_2BIT,
					     IOMUX_WIDTH_2BIT),
	PIN_BANK_IOMUX_FLAGS(1, 32, "gpio1", IOMUX_WIDTH_2BIT,
					     IOMUX_WIDTH_2BIT,
					     IOMUX_WIDTH_2BIT,
					     IOMUX_WIDTH_2BIT),
	PIN_BANK_IOMUX_FLAGS(2, 32, "gpio2", IOMUX_WIDTH_2BIT,
					     IOMUX_WIDTH_2BIT,
					     IOMUX_WIDTH_2BIT,
					     IOMUX_WIDTH_2BIT),
	PIN_BANK_IOMUX_FLAGS(3, 32, "gpio3", IOMUX_WIDTH_2BIT,
					     IOMUX_WIDTH_2BIT,
					     IOMUX_WIDTH_2BIT,
					     IOMUX_WIDTH_2BIT),
	PIN_BANK_IOMUX_FLAGS(4, 32, "gpio4", IOMUX_WIDTH_2BIT,
					     IOMUX_WIDTH_2BIT,
					     IOMUX_WIDTH_2BIT,
					     IOMUX_WIDTH_2BIT),
पूर्ण;

अटल काष्ठा rockchip_pin_ctrl rk3308_pin_ctrl = अणु
		.pin_banks		= rk3308_pin_banks,
		.nr_banks		= ARRAY_SIZE(rk3308_pin_banks),
		.label			= "RK3308-GPIO",
		.type			= RK3308,
		.grf_mux_offset		= 0x0,
		.iomux_recalced		= rk3308_mux_recalced_data,
		.niomux_recalced	= ARRAY_SIZE(rk3308_mux_recalced_data),
		.iomux_routes		= rk3308_mux_route_data,
		.niomux_routes		= ARRAY_SIZE(rk3308_mux_route_data),
		.pull_calc_reg		= rk3308_calc_pull_reg_and_bit,
		.drv_calc_reg		= rk3308_calc_drv_reg_and_bit,
		.schmitt_calc_reg	= rk3308_calc_schmitt_reg_and_bit,
पूर्ण;

अटल काष्ठा rockchip_pin_bank rk3328_pin_banks[] = अणु
	PIN_BANK_IOMUX_FLAGS(0, 32, "gpio0", 0, 0, 0, 0),
	PIN_BANK_IOMUX_FLAGS(1, 32, "gpio1", 0, 0, 0, 0),
	PIN_BANK_IOMUX_FLAGS(2, 32, "gpio2", 0,
			     IOMUX_WIDTH_3BIT,
			     IOMUX_WIDTH_3BIT,
			     0),
	PIN_BANK_IOMUX_FLAGS(3, 32, "gpio3",
			     IOMUX_WIDTH_3BIT,
			     IOMUX_WIDTH_3BIT,
			     0,
			     0),
पूर्ण;

अटल काष्ठा rockchip_pin_ctrl rk3328_pin_ctrl = अणु
		.pin_banks		= rk3328_pin_banks,
		.nr_banks		= ARRAY_SIZE(rk3328_pin_banks),
		.label			= "RK3328-GPIO",
		.type			= RK3288,
		.grf_mux_offset		= 0x0,
		.iomux_recalced		= rk3328_mux_recalced_data,
		.niomux_recalced	= ARRAY_SIZE(rk3328_mux_recalced_data),
		.iomux_routes		= rk3328_mux_route_data,
		.niomux_routes		= ARRAY_SIZE(rk3328_mux_route_data),
		.pull_calc_reg		= rk3228_calc_pull_reg_and_bit,
		.drv_calc_reg		= rk3228_calc_drv_reg_and_bit,
		.schmitt_calc_reg	= rk3328_calc_schmitt_reg_and_bit,
पूर्ण;

अटल काष्ठा rockchip_pin_bank rk3368_pin_banks[] = अणु
	PIN_BANK_IOMUX_FLAGS(0, 32, "gpio0", IOMUX_SOURCE_PMU,
					     IOMUX_SOURCE_PMU,
					     IOMUX_SOURCE_PMU,
					     IOMUX_SOURCE_PMU
			    ),
	PIN_BANK(1, 32, "gpio1"),
	PIN_BANK(2, 32, "gpio2"),
	PIN_BANK(3, 32, "gpio3"),
पूर्ण;

अटल काष्ठा rockchip_pin_ctrl rk3368_pin_ctrl = अणु
		.pin_banks		= rk3368_pin_banks,
		.nr_banks		= ARRAY_SIZE(rk3368_pin_banks),
		.label			= "RK3368-GPIO",
		.type			= RK3368,
		.grf_mux_offset		= 0x0,
		.pmu_mux_offset		= 0x0,
		.pull_calc_reg		= rk3368_calc_pull_reg_and_bit,
		.drv_calc_reg		= rk3368_calc_drv_reg_and_bit,
पूर्ण;

अटल काष्ठा rockchip_pin_bank rk3399_pin_banks[] = अणु
	PIN_BANK_IOMUX_FLAGS_DRV_FLAGS_OFFSET_PULL_FLAGS(0, 32, "gpio0",
							 IOMUX_SOURCE_PMU,
							 IOMUX_SOURCE_PMU,
							 IOMUX_SOURCE_PMU,
							 IOMUX_SOURCE_PMU,
							 DRV_TYPE_IO_1V8_ONLY,
							 DRV_TYPE_IO_1V8_ONLY,
							 DRV_TYPE_IO_DEFAULT,
							 DRV_TYPE_IO_DEFAULT,
							 0x80,
							 0x88,
							 -1,
							 -1,
							 PULL_TYPE_IO_1V8_ONLY,
							 PULL_TYPE_IO_1V8_ONLY,
							 PULL_TYPE_IO_DEFAULT,
							 PULL_TYPE_IO_DEFAULT
							),
	PIN_BANK_IOMUX_DRV_FLAGS_OFFSET(1, 32, "gpio1", IOMUX_SOURCE_PMU,
					IOMUX_SOURCE_PMU,
					IOMUX_SOURCE_PMU,
					IOMUX_SOURCE_PMU,
					DRV_TYPE_IO_1V8_OR_3V0,
					DRV_TYPE_IO_1V8_OR_3V0,
					DRV_TYPE_IO_1V8_OR_3V0,
					DRV_TYPE_IO_1V8_OR_3V0,
					0xa0,
					0xa8,
					0xb0,
					0xb8
					),
	PIN_BANK_DRV_FLAGS_PULL_FLAGS(2, 32, "gpio2", DRV_TYPE_IO_1V8_OR_3V0,
				      DRV_TYPE_IO_1V8_OR_3V0,
				      DRV_TYPE_IO_1V8_ONLY,
				      DRV_TYPE_IO_1V8_ONLY,
				      PULL_TYPE_IO_DEFAULT,
				      PULL_TYPE_IO_DEFAULT,
				      PULL_TYPE_IO_1V8_ONLY,
				      PULL_TYPE_IO_1V8_ONLY
				      ),
	PIN_BANK_DRV_FLAGS(3, 32, "gpio3", DRV_TYPE_IO_3V3_ONLY,
			   DRV_TYPE_IO_3V3_ONLY,
			   DRV_TYPE_IO_3V3_ONLY,
			   DRV_TYPE_IO_1V8_OR_3V0
			   ),
	PIN_BANK_DRV_FLAGS(4, 32, "gpio4", DRV_TYPE_IO_1V8_OR_3V0,
			   DRV_TYPE_IO_1V8_3V0_AUTO,
			   DRV_TYPE_IO_1V8_OR_3V0,
			   DRV_TYPE_IO_1V8_OR_3V0
			   ),
पूर्ण;

अटल काष्ठा rockchip_pin_ctrl rk3399_pin_ctrl = अणु
		.pin_banks		= rk3399_pin_banks,
		.nr_banks		= ARRAY_SIZE(rk3399_pin_banks),
		.label			= "RK3399-GPIO",
		.type			= RK3399,
		.grf_mux_offset		= 0xe000,
		.pmu_mux_offset		= 0x0,
		.grf_drv_offset		= 0xe100,
		.pmu_drv_offset		= 0x80,
		.iomux_routes		= rk3399_mux_route_data,
		.niomux_routes		= ARRAY_SIZE(rk3399_mux_route_data),
		.pull_calc_reg		= rk3399_calc_pull_reg_and_bit,
		.drv_calc_reg		= rk3399_calc_drv_reg_and_bit,
पूर्ण;

अटल काष्ठा rockchip_pin_bank rk3568_pin_banks[] = अणु
	PIN_BANK_IOMUX_FLAGS(0, 32, "gpio0", IOMUX_SOURCE_PMU | IOMUX_WIDTH_4BIT,
					     IOMUX_SOURCE_PMU | IOMUX_WIDTH_4BIT,
					     IOMUX_SOURCE_PMU | IOMUX_WIDTH_4BIT,
					     IOMUX_SOURCE_PMU | IOMUX_WIDTH_4BIT),
	PIN_BANK_IOMUX_FLAGS(1, 32, "gpio1", IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT),
	PIN_BANK_IOMUX_FLAGS(2, 32, "gpio2", IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT),
	PIN_BANK_IOMUX_FLAGS(3, 32, "gpio3", IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT),
	PIN_BANK_IOMUX_FLAGS(4, 32, "gpio4", IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT),
पूर्ण;

अटल काष्ठा rockchip_pin_ctrl rk3568_pin_ctrl = अणु
	.pin_banks		= rk3568_pin_banks,
	.nr_banks		= ARRAY_SIZE(rk3568_pin_banks),
	.label			= "RK3568-GPIO",
	.type			= RK3568,
	.grf_mux_offset		= 0x0,
	.pmu_mux_offset		= 0x0,
	.grf_drv_offset		= 0x0200,
	.pmu_drv_offset		= 0x0070,
	.iomux_routes		= rk3568_mux_route_data,
	.niomux_routes		= ARRAY_SIZE(rk3568_mux_route_data),
	.pull_calc_reg		= rk3568_calc_pull_reg_and_bit,
	.drv_calc_reg		= rk3568_calc_drv_reg_and_bit,
	.schmitt_calc_reg	= rk3568_calc_schmitt_reg_and_bit,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rockchip_pinctrl_dt_match[] = अणु
	अणु .compatible = "rockchip,px30-pinctrl",
		.data = &px30_pin_ctrl पूर्ण,
	अणु .compatible = "rockchip,rv1108-pinctrl",
		.data = &rv1108_pin_ctrl पूर्ण,
	अणु .compatible = "rockchip,rk2928-pinctrl",
		.data = &rk2928_pin_ctrl पूर्ण,
	अणु .compatible = "rockchip,rk3036-pinctrl",
		.data = &rk3036_pin_ctrl पूर्ण,
	अणु .compatible = "rockchip,rk3066a-pinctrl",
		.data = &rk3066a_pin_ctrl पूर्ण,
	अणु .compatible = "rockchip,rk3066b-pinctrl",
		.data = &rk3066b_pin_ctrl पूर्ण,
	अणु .compatible = "rockchip,rk3128-pinctrl",
		.data = (व्योम *)&rk3128_pin_ctrl पूर्ण,
	अणु .compatible = "rockchip,rk3188-pinctrl",
		.data = &rk3188_pin_ctrl पूर्ण,
	अणु .compatible = "rockchip,rk3228-pinctrl",
		.data = &rk3228_pin_ctrl पूर्ण,
	अणु .compatible = "rockchip,rk3288-pinctrl",
		.data = &rk3288_pin_ctrl पूर्ण,
	अणु .compatible = "rockchip,rk3308-pinctrl",
		.data = &rk3308_pin_ctrl पूर्ण,
	अणु .compatible = "rockchip,rk3328-pinctrl",
		.data = &rk3328_pin_ctrl पूर्ण,
	अणु .compatible = "rockchip,rk3368-pinctrl",
		.data = &rk3368_pin_ctrl पूर्ण,
	अणु .compatible = "rockchip,rk3399-pinctrl",
		.data = &rk3399_pin_ctrl पूर्ण,
	अणु .compatible = "rockchip,rk3568-pinctrl",
		.data = &rk3568_pin_ctrl पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver rockchip_pinctrl_driver = अणु
	.probe		= rockchip_pinctrl_probe,
	.driver = अणु
		.name	= "rockchip-pinctrl",
		.pm = &rockchip_pinctrl_dev_pm_ops,
		.of_match_table = rockchip_pinctrl_dt_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init rockchip_pinctrl_drv_रेजिस्टर(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&rockchip_pinctrl_driver);
पूर्ण
postcore_initcall(rockchip_pinctrl_drv_रेजिस्टर);

अटल व्योम __निकास rockchip_pinctrl_drv_unरेजिस्टर(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&rockchip_pinctrl_driver);
पूर्ण
module_निकास(rockchip_pinctrl_drv_unरेजिस्टर);

MODULE_DESCRIPTION("ROCKCHIP Pin Controller Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pinctrl-rockchip");
MODULE_DEVICE_TABLE(of, rockchip_pinctrl_dt_match);
