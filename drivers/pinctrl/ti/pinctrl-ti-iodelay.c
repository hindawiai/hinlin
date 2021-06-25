<शैली गुरु>
/*
 * Support क्रम configuration of IO Delay module found on Texas Instruments SoCs
 * such as DRA7
 *
 * Copyright (C) 2015-2017 Texas Instruments Incorporated - https://www.ti.com/
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश "../core.h"
#समावेश "../devicetree.h"

#घोषणा DRIVER_NAME	"ti-iodelay"

/**
 * काष्ठा ti_iodelay_reg_data - Describes the रेजिस्टरs क्रम the iodelay instance
 * @signature_mask: CONFIG_REG mask क्रम the signature bits (see TRM)
 * @signature_value: CONFIG_REG signature value to be written (see TRM)
 * @lock_mask: CONFIG_REG mask क्रम the lock bits (see TRM)
 * @lock_val: CONFIG_REG lock value क्रम the lock bits (see TRM)
 * @unlock_val:CONFIG_REG unlock value क्रम the lock bits (see TRM)
 * @binary_data_coarse_mask: CONFIG_REG coarse mask (see TRM)
 * @binary_data_fine_mask: CONFIG_REG fine mask (see TRM)
 * @reg_refclk_offset: Refclk रेजिस्टर offset
 * @refclk_period_mask: Refclk mask
 * @reg_coarse_offset: Coarse रेजिस्टर configuration offset
 * @coarse_delay_count_mask: Coarse delay count mask
 * @coarse_ref_count_mask: Coarse ref count mask
 * @reg_fine_offset: Fine रेजिस्टर configuration offset
 * @fine_delay_count_mask: Fine delay count mask
 * @fine_ref_count_mask: Fine ref count mask
 * @reg_global_lock_offset: Global iodelay module lock रेजिस्टर offset
 * @global_lock_mask: Lock mask
 * @global_unlock_val: Unlock value
 * @global_lock_val: Lock value
 * @reg_start_offset: Offset to iodelay रेजिस्टरs after the CONFIG_REG_0 to 8
 * @reg_nr_per_pin: Number of iodelay रेजिस्टरs क्रम each pin
 * @regmap_config: Regmap configuration क्रम the IODelay region
 */
काष्ठा ti_iodelay_reg_data अणु
	u32 signature_mask;
	u32 signature_value;
	u32 lock_mask;
	u32 lock_val;
	u32 unlock_val;
	u32 binary_data_coarse_mask;
	u32 binary_data_fine_mask;

	u32 reg_refclk_offset;
	u32 refclk_period_mask;

	u32 reg_coarse_offset;
	u32 coarse_delay_count_mask;
	u32 coarse_ref_count_mask;

	u32 reg_fine_offset;
	u32 fine_delay_count_mask;
	u32 fine_ref_count_mask;

	u32 reg_global_lock_offset;
	u32 global_lock_mask;
	u32 global_unlock_val;
	u32 global_lock_val;

	u32 reg_start_offset;
	u32 reg_nr_per_pin;

	काष्ठा regmap_config *regmap_config;
पूर्ण;

/**
 * काष्ठा ti_iodelay_reg_values - Computed io_reg configuration values (see TRM)
 * @coarse_ref_count: Coarse reference count
 * @coarse_delay_count: Coarse delay count
 * @fine_ref_count: Fine reference count
 * @fine_delay_count: Fine Delay count
 * @ref_clk_period: Reference Clock period
 * @cdpe: Coarse delay parameter
 * @fdpe: Fine delay parameter
 */
काष्ठा ti_iodelay_reg_values अणु
	u16 coarse_ref_count;
	u16 coarse_delay_count;

	u16 fine_ref_count;
	u16 fine_delay_count;

	u16 ref_clk_period;

	u32 cdpe;
	u32 fdpe;
पूर्ण;

/**
 * काष्ठा ti_iodelay_cfg - Description of each configuration parameters
 * @offset: Configuration रेजिस्टर offset
 * @a_delay: Agnostic Delay (in ps)
 * @g_delay: Gnostic Delay (in ps)
 */
काष्ठा ti_iodelay_cfg अणु
	u16 offset;
	u16 a_delay;
	u16 g_delay;
पूर्ण;

/**
 * काष्ठा ti_iodelay_pingroup - Structure that describes one group
 * @cfg: configuration array क्रम the pin (from dt)
 * @ncfg: number of configuration values allocated
 * @config: pinconf "Config" - currently a dummy value
 */
काष्ठा ti_iodelay_pingroup अणु
	काष्ठा ti_iodelay_cfg *cfg;
	पूर्णांक ncfg;
	अचिन्हित दीर्घ config;
पूर्ण;

/**
 * काष्ठा ti_iodelay_device - Represents inक्रमmation क्रम a iodelay instance
 * @dev: Device poपूर्णांकer
 * @phys_base: Physical address base of the iodelay device
 * @reg_base: Virtual address base of the iodelay device
 * @regmap: Regmap क्रम this iodelay instance
 * @pctl: Pinctrl device
 * @desc: pinctrl descriptor क्रम pctl
 * @pa: pinctrl pin wise description
 * @reg_data: Register definition data क्रम the IODelay instance
 * @reg_init_conf_values: Initial configuration values.
 */
काष्ठा ti_iodelay_device अणु
	काष्ठा device *dev;
	अचिन्हित दीर्घ phys_base;
	व्योम __iomem *reg_base;
	काष्ठा regmap *regmap;

	काष्ठा pinctrl_dev *pctl;
	काष्ठा pinctrl_desc desc;
	काष्ठा pinctrl_pin_desc *pa;

	स्थिर काष्ठा ti_iodelay_reg_data *reg_data;
	काष्ठा ti_iodelay_reg_values reg_init_conf_values;
पूर्ण;

/**
 * ti_iodelay_extract() - extract bits क्रम a field
 * @val: Register value
 * @mask: Mask
 *
 * Return: extracted value which is appropriately shअगरted
 */
अटल अंतरभूत u32 ti_iodelay_extract(u32 val, u32 mask)
अणु
	वापस (val & mask) >> __ffs(mask);
पूर्ण

/**
 * ti_iodelay_compute_dpe() - Compute equation क्रम delay parameter
 * @period: Period to use
 * @ref: Reference Count
 * @delay: Delay count
 * @delay_m: Delay multiplier
 *
 * Return: Computed delay parameter
 */
अटल अंतरभूत u32 ti_iodelay_compute_dpe(u16 period, u16 ref, u16 delay,
					 u16 delay_m)
अणु
	u64 m, d;

	/* Handle overflow conditions */
	m = 10 * (u64)period * (u64)ref;
	d = 2 * (u64)delay * (u64)delay_m;

	/* Truncate result back to 32 bits */
	वापस भाग64_u64(m, d);
पूर्ण

/**
 * ti_iodelay_pinconf_set() - Configure the pin configuration
 * @iod: iodelay device
 * @cfg: Configuration
 *
 * Update the configuration रेजिस्टर as per TRM and lockup once करोne.
 * *IMPORTANT NOTE* SoC TRM करोes recommend करोing iodelay programmation only
 * जबतक in Isolation. But, then, isolation also implies that every pin
 * on the SoC (including DDR) will be isolated out. The only benefit being
 * a glitchless configuration, However, the पूर्णांकent of this driver is purely
 * to support a "glitchy" configuration where applicable.
 *
 * Return: 0 in हाल of success, अन्यथा appropriate error value
 */
अटल पूर्णांक ti_iodelay_pinconf_set(काष्ठा ti_iodelay_device *iod,
				  काष्ठा ti_iodelay_cfg *cfg)
अणु
	स्थिर काष्ठा ti_iodelay_reg_data *reg = iod->reg_data;
	काष्ठा ti_iodelay_reg_values *ival = &iod->reg_init_conf_values;
	काष्ठा device *dev = iod->dev;
	u32 g_delay_coarse, g_delay_fine;
	u32 a_delay_coarse, a_delay_fine;
	u32 c_elements, f_elements;
	u32 total_delay;
	u32 reg_mask, reg_val, पंचांगp_val;
	पूर्णांक r;

	/* NOTE: Truncation is expected in all भागision below */
	g_delay_coarse = cfg->g_delay / 920;
	g_delay_fine = ((cfg->g_delay % 920) * 10) / 60;

	a_delay_coarse = cfg->a_delay / ival->cdpe;
	a_delay_fine = ((cfg->a_delay % ival->cdpe) * 10) / ival->fdpe;

	c_elements = g_delay_coarse + a_delay_coarse;
	f_elements = (g_delay_fine + a_delay_fine) / 10;

	अगर (f_elements > 22) अणु
		total_delay = c_elements * ival->cdpe + f_elements * ival->fdpe;
		c_elements = total_delay / ival->cdpe;
		f_elements = (total_delay % ival->cdpe) / ival->fdpe;
	पूर्ण

	reg_mask = reg->signature_mask;
	reg_val = reg->signature_value << __ffs(reg->signature_mask);

	reg_mask |= reg->binary_data_coarse_mask;
	पंचांगp_val = c_elements << __ffs(reg->binary_data_coarse_mask);
	अगर (पंचांगp_val & ~reg->binary_data_coarse_mask) अणु
		dev_err(dev, "Masking overflow of coarse elements %08x\n",
			पंचांगp_val);
		पंचांगp_val &= reg->binary_data_coarse_mask;
	पूर्ण
	reg_val |= पंचांगp_val;

	reg_mask |= reg->binary_data_fine_mask;
	पंचांगp_val = f_elements << __ffs(reg->binary_data_fine_mask);
	अगर (पंचांगp_val & ~reg->binary_data_fine_mask) अणु
		dev_err(dev, "Masking overflow of fine elements %08x\n",
			पंचांगp_val);
		पंचांगp_val &= reg->binary_data_fine_mask;
	पूर्ण
	reg_val |= पंचांगp_val;

	/*
	 * NOTE: we leave the iodelay values unlocked - this is to work around
	 * situations such as those found with mmc mode change.
	 * However, this leaves खोलो any unwarranted changes to padconf रेजिस्टर
	 * impacting iodelay configuration. Use with care!
	 */
	reg_mask |= reg->lock_mask;
	reg_val |= reg->unlock_val << __ffs(reg->lock_mask);
	r = regmap_update_bits(iod->regmap, cfg->offset, reg_mask, reg_val);

	dev_dbg(dev, "Set reg 0x%x Delay(a: %d g: %d), Elements(C=%d F=%d)0x%x\n",
		cfg->offset, cfg->a_delay, cfg->g_delay, c_elements,
		f_elements, reg_val);

	वापस r;
पूर्ण

/**
 * ti_iodelay_pinconf_init_dev() - Initialize IODelay device
 * @iod: iodelay device
 *
 * Unlocks the iodelay region, computes the common parameters
 *
 * Return: 0 in हाल of success, अन्यथा appropriate error value
 */
अटल पूर्णांक ti_iodelay_pinconf_init_dev(काष्ठा ti_iodelay_device *iod)
अणु
	स्थिर काष्ठा ti_iodelay_reg_data *reg = iod->reg_data;
	काष्ठा device *dev = iod->dev;
	काष्ठा ti_iodelay_reg_values *ival = &iod->reg_init_conf_values;
	u32 val;
	पूर्णांक r;

	/* unlock the iodelay region */
	r = regmap_update_bits(iod->regmap, reg->reg_global_lock_offset,
			       reg->global_lock_mask, reg->global_unlock_val);
	अगर (r)
		वापस r;

	/* Read up Recalibration sequence करोne by bootloader */
	r = regmap_पढ़ो(iod->regmap, reg->reg_refclk_offset, &val);
	अगर (r)
		वापस r;
	ival->ref_clk_period = ti_iodelay_extract(val, reg->refclk_period_mask);
	dev_dbg(dev, "refclk_period=0x%04x\n", ival->ref_clk_period);

	r = regmap_पढ़ो(iod->regmap, reg->reg_coarse_offset, &val);
	अगर (r)
		वापस r;
	ival->coarse_ref_count =
	    ti_iodelay_extract(val, reg->coarse_ref_count_mask);
	ival->coarse_delay_count =
	    ti_iodelay_extract(val, reg->coarse_delay_count_mask);
	अगर (!ival->coarse_delay_count) अणु
		dev_err(dev, "Invalid Coarse delay count (0) (reg=0x%08x)\n",
			val);
		वापस -EINVAL;
	पूर्ण
	ival->cdpe = ti_iodelay_compute_dpe(ival->ref_clk_period,
					    ival->coarse_ref_count,
					    ival->coarse_delay_count, 88);
	अगर (!ival->cdpe) अणु
		dev_err(dev, "Invalid cdpe computed params = %d %d %d\n",
			ival->ref_clk_period, ival->coarse_ref_count,
			ival->coarse_delay_count);
		वापस -EINVAL;
	पूर्ण
	dev_dbg(iod->dev, "coarse: ref=0x%04x delay=0x%04x cdpe=0x%08x\n",
		ival->coarse_ref_count, ival->coarse_delay_count, ival->cdpe);

	r = regmap_पढ़ो(iod->regmap, reg->reg_fine_offset, &val);
	अगर (r)
		वापस r;
	ival->fine_ref_count =
	    ti_iodelay_extract(val, reg->fine_ref_count_mask);
	ival->fine_delay_count =
	    ti_iodelay_extract(val, reg->fine_delay_count_mask);
	अगर (!ival->fine_delay_count) अणु
		dev_err(dev, "Invalid Fine delay count (0) (reg=0x%08x)\n",
			val);
		वापस -EINVAL;
	पूर्ण
	ival->fdpe = ti_iodelay_compute_dpe(ival->ref_clk_period,
					    ival->fine_ref_count,
					    ival->fine_delay_count, 264);
	अगर (!ival->fdpe) अणु
		dev_err(dev, "Invalid fdpe(0) computed params = %d %d %d\n",
			ival->ref_clk_period, ival->fine_ref_count,
			ival->fine_delay_count);
		वापस -EINVAL;
	पूर्ण
	dev_dbg(iod->dev, "fine: ref=0x%04x delay=0x%04x fdpe=0x%08x\n",
		ival->fine_ref_count, ival->fine_delay_count, ival->fdpe);

	वापस 0;
पूर्ण

/**
 * ti_iodelay_pinconf_deinit_dev() - deinit the iodelay device
 * @iod:	IODelay device
 *
 * Deinitialize the IODelay device (basically just lock the region back up.
 */
अटल व्योम ti_iodelay_pinconf_deinit_dev(काष्ठा ti_iodelay_device *iod)
अणु
	स्थिर काष्ठा ti_iodelay_reg_data *reg = iod->reg_data;

	/* lock the iodelay region back again */
	regmap_update_bits(iod->regmap, reg->reg_global_lock_offset,
			   reg->global_lock_mask, reg->global_lock_val);
पूर्ण

/**
 * ti_iodelay_get_pingroup() - Find the group mapped by a group selector
 * @iod: iodelay device
 * @selector: Group Selector
 *
 * Return: Corresponding group representing group selector
 */
अटल काष्ठा ti_iodelay_pingroup *
ti_iodelay_get_pingroup(काष्ठा ti_iodelay_device *iod, अचिन्हित पूर्णांक selector)
अणु
	काष्ठा group_desc *g;

	g = pinctrl_generic_get_group(iod->pctl, selector);
	अगर (!g) अणु
		dev_err(iod->dev, "%s could not find pingroup %i\n", __func__,
			selector);

		वापस शून्य;
	पूर्ण

	वापस g->data;
पूर्ण

/**
 * ti_iodelay_offset_to_pin() - get a pin index based on the रेजिस्टर offset
 * @iod: iodelay driver instance
 * @offset: रेजिस्टर offset from the base
 */
अटल पूर्णांक ti_iodelay_offset_to_pin(काष्ठा ti_iodelay_device *iod,
				    अचिन्हित पूर्णांक offset)
अणु
	स्थिर काष्ठा ti_iodelay_reg_data *r = iod->reg_data;
	अचिन्हित पूर्णांक index;

	अगर (offset > r->regmap_config->max_रेजिस्टर) अणु
		dev_err(iod->dev, "mux offset out of range: 0x%x (0x%x)\n",
			offset, r->regmap_config->max_रेजिस्टर);
		वापस -EINVAL;
	पूर्ण

	index = (offset - r->reg_start_offset) / r->regmap_config->reg_stride;
	index /= r->reg_nr_per_pin;

	वापस index;
पूर्ण

/**
 * ti_iodelay_node_iterator() - Iterate iodelay node
 * @pctldev: Pin controller driver
 * @np: Device node
 * @pinctrl_spec: Parsed arguments from device tree
 * @pins: Array of pins in the pin group
 * @pin_index: Pin index in the pin array
 * @data: Pin controller driver specअगरic data
 *
 */
अटल पूर्णांक ti_iodelay_node_iterator(काष्ठा pinctrl_dev *pctldev,
				    काष्ठा device_node *np,
				    स्थिर काष्ठा of_phandle_args *pinctrl_spec,
				    पूर्णांक *pins, पूर्णांक pin_index, व्योम *data)
अणु
	काष्ठा ti_iodelay_device *iod;
	काष्ठा ti_iodelay_cfg *cfg = data;
	स्थिर काष्ठा ti_iodelay_reg_data *r;
	काष्ठा pinctrl_pin_desc *pd;
	पूर्णांक pin;

	iod = pinctrl_dev_get_drvdata(pctldev);
	अगर (!iod)
		वापस -EINVAL;

	r = iod->reg_data;

	अगर (pinctrl_spec->args_count < r->reg_nr_per_pin) अणु
		dev_err(iod->dev, "invalid args_count for spec: %i\n",
			pinctrl_spec->args_count);

		वापस -EINVAL;
	पूर्ण

	/* Index plus two value cells */
	cfg[pin_index].offset = pinctrl_spec->args[0];
	cfg[pin_index].a_delay = pinctrl_spec->args[1] & 0xffff;
	cfg[pin_index].g_delay = pinctrl_spec->args[2] & 0xffff;

	pin = ti_iodelay_offset_to_pin(iod, cfg[pin_index].offset);
	अगर (pin < 0) अणु
		dev_err(iod->dev, "could not add functions for %pOFn %ux\n",
			np, cfg[pin_index].offset);
		वापस -ENODEV;
	पूर्ण
	pins[pin_index] = pin;

	pd = &iod->pa[pin];
	pd->drv_data = &cfg[pin_index];

	dev_dbg(iod->dev, "%pOFn offset=%x a_delay = %d g_delay = %d\n",
		np, cfg[pin_index].offset, cfg[pin_index].a_delay,
		cfg[pin_index].g_delay);

	वापस 0;
पूर्ण

/**
 * ti_iodelay_dt_node_to_map() - Map a device tree node to appropriate group
 * @pctldev: pinctrl device representing IODelay device
 * @np: Node Poपूर्णांकer (device tree)
 * @map: Pinctrl Map वापसed back to pinctrl framework
 * @num_maps: Number of maps (1)
 *
 * Maps the device tree description पूर्णांकo a group of configuration parameters
 * क्रम iodelay block entry.
 *
 * Return: 0 in हाल of success, अन्यथा appropriate error value
 */
अटल पूर्णांक ti_iodelay_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
				     काष्ठा device_node *np,
				     काष्ठा pinctrl_map **map,
				     अचिन्हित पूर्णांक *num_maps)
अणु
	काष्ठा ti_iodelay_device *iod;
	काष्ठा ti_iodelay_cfg *cfg;
	काष्ठा ti_iodelay_pingroup *g;
	स्थिर अक्षर *name = "pinctrl-pin-array";
	पूर्णांक rows, *pins, error = -EINVAL, i;

	iod = pinctrl_dev_get_drvdata(pctldev);
	अगर (!iod)
		वापस -EINVAL;

	rows = pinctrl_count_index_with_args(np, name);
	अगर (rows < 0)
		वापस rows;

	*map = devm_kzalloc(iod->dev, माप(**map), GFP_KERNEL);
	अगर (!*map)
		वापस -ENOMEM;
	*num_maps = 0;

	g = devm_kzalloc(iod->dev, माप(*g), GFP_KERNEL);
	अगर (!g) अणु
		error = -ENOMEM;
		जाओ मुक्त_map;
	पूर्ण

	pins = devm_kसुस्मृति(iod->dev, rows, माप(*pins), GFP_KERNEL);
	अगर (!pins) अणु
		error = -ENOMEM;
		जाओ मुक्त_group;
	पूर्ण

	cfg = devm_kसुस्मृति(iod->dev, rows, माप(*cfg), GFP_KERNEL);
	अगर (!cfg) अणु
		error = -ENOMEM;
		जाओ मुक्त_pins;
	पूर्ण

	क्रम (i = 0; i < rows; i++) अणु
		काष्ठा of_phandle_args pinctrl_spec;

		error = pinctrl_parse_index_with_args(np, name, i,
						      &pinctrl_spec);
		अगर (error)
			जाओ मुक्त_data;

		error = ti_iodelay_node_iterator(pctldev, np, &pinctrl_spec,
						 pins, i, cfg);
		अगर (error)
			जाओ मुक्त_data;
	पूर्ण

	g->cfg = cfg;
	g->ncfg = i;
	g->config = PIN_CONFIG_END;

	error = pinctrl_generic_add_group(iod->pctl, np->name, pins, i, g);
	अगर (error < 0)
		जाओ मुक्त_data;

	(*map)->type = PIN_MAP_TYPE_CONFIGS_GROUP;
	(*map)->data.configs.group_or_pin = np->name;
	(*map)->data.configs.configs = &g->config;
	(*map)->data.configs.num_configs = 1;
	*num_maps = 1;

	वापस 0;

मुक्त_data:
	devm_kमुक्त(iod->dev, cfg);
मुक्त_pins:
	devm_kमुक्त(iod->dev, pins);
मुक्त_group:
	devm_kमुक्त(iod->dev, g);
मुक्त_map:
	devm_kमुक्त(iod->dev, *map);

	वापस error;
पूर्ण

/**
 * ti_iodelay_pinconf_group_get() - Get the group configuration
 * @pctldev: pinctrl device representing IODelay device
 * @selector: Group selector
 * @config: Configuration वापसed
 *
 * Return: The configuration अगर the group is valid, अन्यथा वापसs -EINVAL
 */
अटल पूर्णांक ti_iodelay_pinconf_group_get(काष्ठा pinctrl_dev *pctldev,
					अचिन्हित पूर्णांक selector,
					अचिन्हित दीर्घ *config)
अणु
	काष्ठा ti_iodelay_device *iod;
	काष्ठा ti_iodelay_pingroup *group;

	iod = pinctrl_dev_get_drvdata(pctldev);
	group = ti_iodelay_get_pingroup(iod, selector);

	अगर (!group)
		वापस -EINVAL;

	*config = group->config;
	वापस 0;
पूर्ण

/**
 * ti_iodelay_pinconf_group_set() - Configure the groups of pins
 * @pctldev: pinctrl device representing IODelay device
 * @selector: Group selector
 * @configs: Configurations
 * @num_configs: Number of configurations
 *
 * Return: 0 अगर all went fine, अन्यथा appropriate error value.
 */
अटल पूर्णांक ti_iodelay_pinconf_group_set(काष्ठा pinctrl_dev *pctldev,
					अचिन्हित पूर्णांक selector,
					अचिन्हित दीर्घ *configs,
					अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा ti_iodelay_device *iod;
	काष्ठा device *dev;
	काष्ठा ti_iodelay_pingroup *group;
	पूर्णांक i;

	iod = pinctrl_dev_get_drvdata(pctldev);
	dev = iod->dev;
	group = ti_iodelay_get_pingroup(iod, selector);

	अगर (num_configs != 1) अणु
		dev_err(dev, "Unsupported number of configurations %d\n",
			num_configs);
		वापस -EINVAL;
	पूर्ण

	अगर (*configs != PIN_CONFIG_END) अणु
		dev_err(dev, "Unsupported configuration\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < group->ncfg; i++) अणु
		अगर (ti_iodelay_pinconf_set(iod, &group->cfg[i]))
			वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
/**
 * ti_iodelay_pin_to_offset() - get pin रेजिस्टर offset based on the pin index
 * @iod: iodelay driver instance
 * @selector: Pin index
 */
अटल अचिन्हित पूर्णांक ti_iodelay_pin_to_offset(काष्ठा ti_iodelay_device *iod,
					     अचिन्हित पूर्णांक selector)
अणु
	स्थिर काष्ठा ti_iodelay_reg_data *r = iod->reg_data;
	अचिन्हित पूर्णांक offset;

	offset = selector * r->regmap_config->reg_stride;
	offset *= r->reg_nr_per_pin;
	offset += r->reg_start_offset;

	वापस offset;
पूर्ण

अटल व्योम ti_iodelay_pin_dbg_show(काष्ठा pinctrl_dev *pctldev,
				    काष्ठा seq_file *s,
				    अचिन्हित पूर्णांक pin)
अणु
	काष्ठा ti_iodelay_device *iod;
	काष्ठा pinctrl_pin_desc *pd;
	काष्ठा ti_iodelay_cfg *cfg;
	स्थिर काष्ठा ti_iodelay_reg_data *r;
	अचिन्हित दीर्घ offset;
	u32 in, oen, out;

	iod = pinctrl_dev_get_drvdata(pctldev);
	r = iod->reg_data;

	offset = ti_iodelay_pin_to_offset(iod, pin);
	pd = &iod->pa[pin];
	cfg = pd->drv_data;

	regmap_पढ़ो(iod->regmap, offset, &in);
	regmap_पढ़ो(iod->regmap, offset + r->regmap_config->reg_stride, &oen);
	regmap_पढ़ो(iod->regmap, offset + r->regmap_config->reg_stride * 2,
		    &out);

	seq_म_लिखो(s, "%lx a: %i g: %i (%08x %08x %08x) %s ",
		   iod->phys_base + offset,
		   cfg ? cfg->a_delay : -1,
		   cfg ? cfg->g_delay : -1,
		   in, oen, out, DRIVER_NAME);
पूर्ण

/**
 * ti_iodelay_pinconf_group_dbg_show() - show the group inक्रमmation
 * @pctldev: Show the group inक्रमmation
 * @s: Sequence file
 * @selector: Group selector
 *
 * Provide the configuration inक्रमmation of the selected group
 */
अटल व्योम ti_iodelay_pinconf_group_dbg_show(काष्ठा pinctrl_dev *pctldev,
					      काष्ठा seq_file *s,
					      अचिन्हित पूर्णांक selector)
अणु
	काष्ठा ti_iodelay_device *iod;
	काष्ठा ti_iodelay_pingroup *group;
	पूर्णांक i;

	iod = pinctrl_dev_get_drvdata(pctldev);
	group = ti_iodelay_get_pingroup(iod, selector);
	अगर (!group)
		वापस;

	क्रम (i = 0; i < group->ncfg; i++) अणु
		काष्ठा ti_iodelay_cfg *cfg;
		u32 reg = 0;

		cfg = &group->cfg[i];
		regmap_पढ़ो(iod->regmap, cfg->offset, &reg);
		seq_म_लिखो(s, "\n\t0x%08x = 0x%08x (%3d, %3d)",
			cfg->offset, reg, cfg->a_delay, cfg->g_delay);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा pinctrl_ops ti_iodelay_pinctrl_ops = अणु
	.get_groups_count = pinctrl_generic_get_group_count,
	.get_group_name = pinctrl_generic_get_group_name,
	.get_group_pins = pinctrl_generic_get_group_pins,
#अगर_घोषित CONFIG_DEBUG_FS
	.pin_dbg_show = ti_iodelay_pin_dbg_show,
#पूर्ण_अगर
	.dt_node_to_map = ti_iodelay_dt_node_to_map,
पूर्ण;

अटल स्थिर काष्ठा pinconf_ops ti_iodelay_pinctrl_pinconf_ops = अणु
	.pin_config_group_get = ti_iodelay_pinconf_group_get,
	.pin_config_group_set = ti_iodelay_pinconf_group_set,
#अगर_घोषित CONFIG_DEBUG_FS
	.pin_config_group_dbg_show = ti_iodelay_pinconf_group_dbg_show,
#पूर्ण_अगर
पूर्ण;

/**
 * ti_iodelay_alloc_pins() - Allocate काष्ठाures needed क्रम pins क्रम iodelay
 * @dev: Device poपूर्णांकer
 * @iod: iodelay device
 * @base_phy: Base Physical Address
 *
 * Return: 0 अगर all went fine, अन्यथा appropriate error value.
 */
अटल पूर्णांक ti_iodelay_alloc_pins(काष्ठा device *dev,
				 काष्ठा ti_iodelay_device *iod, u32 base_phy)
अणु
	स्थिर काष्ठा ti_iodelay_reg_data *r = iod->reg_data;
	काष्ठा pinctrl_pin_desc *pin;
	u32 phy_reg;
	पूर्णांक nr_pins, i;

	nr_pins = ti_iodelay_offset_to_pin(iod, r->regmap_config->max_रेजिस्टर);
	dev_dbg(dev, "Allocating %i pins\n", nr_pins);

	iod->pa = devm_kसुस्मृति(dev, nr_pins, माप(*iod->pa), GFP_KERNEL);
	अगर (!iod->pa)
		वापस -ENOMEM;

	iod->desc.pins = iod->pa;
	iod->desc.npins = nr_pins;

	phy_reg = r->reg_start_offset + base_phy;

	क्रम (i = 0; i < nr_pins; i++, phy_reg += 4) अणु
		pin = &iod->pa[i];
		pin->number = i;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा regmap_config dra7_iodelay_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = 0xd1c,
पूर्ण;

अटल काष्ठा ti_iodelay_reg_data dra7_iodelay_data = अणु
	.signature_mask = 0x0003f000,
	.signature_value = 0x29,
	.lock_mask = 0x00000400,
	.lock_val = 1,
	.unlock_val = 0,
	.binary_data_coarse_mask = 0x000003e0,
	.binary_data_fine_mask = 0x0000001f,

	.reg_refclk_offset = 0x14,
	.refclk_period_mask = 0xffff,

	.reg_coarse_offset = 0x18,
	.coarse_delay_count_mask = 0xffff0000,
	.coarse_ref_count_mask = 0x0000ffff,

	.reg_fine_offset = 0x1C,
	.fine_delay_count_mask = 0xffff0000,
	.fine_ref_count_mask = 0x0000ffff,

	.reg_global_lock_offset = 0x2c,
	.global_lock_mask = 0x0000ffff,
	.global_unlock_val = 0x0000aaaa,
	.global_lock_val = 0x0000aaab,

	.reg_start_offset = 0x30,
	.reg_nr_per_pin = 3,
	.regmap_config = &dra7_iodelay_regmap_config,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ti_iodelay_of_match[] = अणु
	अणु.compatible = "ti,dra7-iodelay", .data = &dra7_iodelay_dataपूर्ण,
	अणु /* Hopefully no more.. */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ti_iodelay_of_match);

/**
 * ti_iodelay_probe() - Standard probe
 * @pdev: platक्रमm device
 *
 * Return: 0 अगर all went fine, अन्यथा appropriate error value.
 */
अटल पूर्णांक ti_iodelay_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = of_node_get(dev->of_node);
	स्थिर काष्ठा of_device_id *match;
	काष्ठा resource *res;
	काष्ठा ti_iodelay_device *iod;
	पूर्णांक ret = 0;

	अगर (!np) अणु
		ret = -EINVAL;
		dev_err(dev, "No OF node\n");
		जाओ निकास_out;
	पूर्ण

	match = of_match_device(ti_iodelay_of_match, dev);
	अगर (!match) अणु
		ret = -EINVAL;
		dev_err(dev, "No DATA match\n");
		जाओ निकास_out;
	पूर्ण

	iod = devm_kzalloc(dev, माप(*iod), GFP_KERNEL);
	अगर (!iod) अणु
		ret = -ENOMEM;
		जाओ निकास_out;
	पूर्ण
	iod->dev = dev;
	iod->reg_data = match->data;

	/* So far We can assume there is only 1 bank of रेजिस्टरs */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(dev, "Missing MEM resource\n");
		ret = -ENODEV;
		जाओ निकास_out;
	पूर्ण

	iod->phys_base = res->start;
	iod->reg_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(iod->reg_base)) अणु
		ret = PTR_ERR(iod->reg_base);
		जाओ निकास_out;
	पूर्ण

	iod->regmap = devm_regmap_init_mmio(dev, iod->reg_base,
					    iod->reg_data->regmap_config);
	अगर (IS_ERR(iod->regmap)) अणु
		dev_err(dev, "Regmap MMIO init failed.\n");
		ret = PTR_ERR(iod->regmap);
		जाओ निकास_out;
	पूर्ण

	ret = ti_iodelay_pinconf_init_dev(iod);
	अगर (ret)
		जाओ निकास_out;

	ret = ti_iodelay_alloc_pins(dev, iod, res->start);
	अगर (ret)
		जाओ निकास_out;

	iod->desc.pctlops = &ti_iodelay_pinctrl_ops;
	/* no pinmux ops - we are pinconf */
	iod->desc.confops = &ti_iodelay_pinctrl_pinconf_ops;
	iod->desc.name = dev_name(dev);
	iod->desc.owner = THIS_MODULE;

	ret = pinctrl_रेजिस्टर_and_init(&iod->desc, dev, iod, &iod->pctl);
	अगर (ret) अणु
		dev_err(dev, "Failed to register pinctrl\n");
		जाओ निकास_out;
	पूर्ण

	platक्रमm_set_drvdata(pdev, iod);

	वापस pinctrl_enable(iod->pctl);

निकास_out:
	of_node_put(np);
	वापस ret;
पूर्ण

/**
 * ti_iodelay_हटाओ() - standard हटाओ
 * @pdev: platक्रमm device
 *
 * Return: 0 अगर all went fine, अन्यथा appropriate error value.
 */
अटल पूर्णांक ti_iodelay_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ti_iodelay_device *iod = platक्रमm_get_drvdata(pdev);

	अगर (!iod)
		वापस 0;

	अगर (iod->pctl)
		pinctrl_unरेजिस्टर(iod->pctl);

	ti_iodelay_pinconf_deinit_dev(iod);

	/* Expect other allocations to be मुक्तd by devm */

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ti_iodelay_driver = अणु
	.probe = ti_iodelay_probe,
	.हटाओ = ti_iodelay_हटाओ,
	.driver = अणु
		   .name = DRIVER_NAME,
		   .of_match_table = ti_iodelay_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ti_iodelay_driver);

MODULE_AUTHOR("Texas Instruments, Inc.");
MODULE_DESCRIPTION("Pinconf driver for TI's IO Delay module");
MODULE_LICENSE("GPL v2");
