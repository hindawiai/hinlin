<शैली गुरु>
/*
 * TI घड़ी support
 *
 * Copyright (C) 2013 Texas Instruments, Inc.
 *
 * Tero Kristo <t-kristo@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk/ti.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/list.h>
#समावेश <linux/regmap.h>
#समावेश <linux/memblock.h>
#समावेश <linux/device.h>

#समावेश "clock.h"

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) "%s: " fmt, __func__

अटल LIST_HEAD(clk_hw_omap_घड़ीs);
काष्ठा ti_clk_ll_ops *ti_clk_ll_ops;
अटल काष्ठा device_node *घड़ीs_node_ptr[CLK_MAX_MEMMAPS];

काष्ठा ti_clk_features ti_clk_features;

काष्ठा clk_iomap अणु
	काष्ठा regmap *regmap;
	व्योम __iomem *mem;
पूर्ण;

अटल काष्ठा clk_iomap *clk_memmaps[CLK_MAX_MEMMAPS];

अटल व्योम clk_memmap_ग_लिखोl(u32 val, स्थिर काष्ठा clk_omap_reg *reg)
अणु
	काष्ठा clk_iomap *io = clk_memmaps[reg->index];

	अगर (reg->ptr)
		ग_लिखोl_relaxed(val, reg->ptr);
	अन्यथा अगर (io->regmap)
		regmap_ग_लिखो(io->regmap, reg->offset, val);
	अन्यथा
		ग_लिखोl_relaxed(val, io->mem + reg->offset);
पूर्ण

अटल व्योम _clk_rmw(u32 val, u32 mask, व्योम __iomem *ptr)
अणु
	u32 v;

	v = पढ़ोl_relaxed(ptr);
	v &= ~mask;
	v |= val;
	ग_लिखोl_relaxed(v, ptr);
पूर्ण

अटल व्योम clk_memmap_rmw(u32 val, u32 mask, स्थिर काष्ठा clk_omap_reg *reg)
अणु
	काष्ठा clk_iomap *io = clk_memmaps[reg->index];

	अगर (reg->ptr) अणु
		_clk_rmw(val, mask, reg->ptr);
	पूर्ण अन्यथा अगर (io->regmap) अणु
		regmap_update_bits(io->regmap, reg->offset, mask, val);
	पूर्ण अन्यथा अणु
		_clk_rmw(val, mask, io->mem + reg->offset);
	पूर्ण
पूर्ण

अटल u32 clk_memmap_पढ़ोl(स्थिर काष्ठा clk_omap_reg *reg)
अणु
	u32 val;
	काष्ठा clk_iomap *io = clk_memmaps[reg->index];

	अगर (reg->ptr)
		val = पढ़ोl_relaxed(reg->ptr);
	अन्यथा अगर (io->regmap)
		regmap_पढ़ो(io->regmap, reg->offset, &val);
	अन्यथा
		val = पढ़ोl_relaxed(io->mem + reg->offset);

	वापस val;
पूर्ण

/**
 * ti_clk_setup_ll_ops - setup low level घड़ी operations
 * @ops: low level घड़ी ops descriptor
 *
 * Sets up low level घड़ी operations क्रम TI घड़ी driver. This is used
 * to provide various callbacks क्रम the घड़ी driver towards platक्रमm
 * specअगरic code. Returns 0 on success, -EBUSY अगर ll_ops have been
 * रेजिस्टरed alपढ़ोy.
 */
पूर्णांक ti_clk_setup_ll_ops(काष्ठा ti_clk_ll_ops *ops)
अणु
	अगर (ti_clk_ll_ops) अणु
		pr_err("Attempt to register ll_ops multiple times.\n");
		वापस -EBUSY;
	पूर्ण

	ti_clk_ll_ops = ops;
	ops->clk_पढ़ोl = clk_memmap_पढ़ोl;
	ops->clk_ग_लिखोl = clk_memmap_ग_लिखोl;
	ops->clk_rmw = clk_memmap_rmw;

	वापस 0;
पूर्ण

/**
 * ti_dt_घड़ीs_रेजिस्टर - रेजिस्टर DT alias घड़ीs during boot
 * @oclks: list of घड़ीs to रेजिस्टर
 *
 * Register alias or non-standard DT घड़ी entries during boot. By
 * शेष, DT घड़ीs are found based on their node name. If any
 * additional con-id / dev-id -> घड़ी mapping is required, use this
 * function to list these.
 */
व्योम __init ti_dt_घड़ीs_रेजिस्टर(काष्ठा ti_dt_clk oclks[])
अणु
	काष्ठा ti_dt_clk *c;
	काष्ठा device_node *node, *parent;
	काष्ठा clk *clk;
	काष्ठा of_phandle_args clkspec;
	अक्षर buf[64];
	अक्षर *ptr;
	अक्षर *tags[2];
	पूर्णांक i;
	पूर्णांक num_args;
	पूर्णांक ret;
	अटल bool clkctrl_nodes_missing;
	अटल bool has_clkctrl_data;
	अटल bool compat_mode;

	compat_mode = ti_clk_get_features()->flags & TI_CLK_CLKCTRL_COMPAT;

	क्रम (c = oclks; c->node_name != शून्य; c++) अणु
		म_नकल(buf, c->node_name);
		ptr = buf;
		क्रम (i = 0; i < 2; i++)
			tags[i] = शून्य;
		num_args = 0;
		जबतक (*ptr) अणु
			अगर (*ptr == ':') अणु
				अगर (num_args >= 2) अणु
					pr_warn("Bad number of tags on %s\n",
						c->node_name);
					वापस;
				पूर्ण
				tags[num_args++] = ptr + 1;
				*ptr = 0;
			पूर्ण
			ptr++;
		पूर्ण

		अगर (num_args && clkctrl_nodes_missing)
			जारी;

		node = of_find_node_by_name(शून्य, buf);
		अगर (num_args && compat_mode) अणु
			parent = node;
			node = of_get_child_by_name(parent, "clock");
			अगर (!node)
				node = of_get_child_by_name(parent, "clk");
			of_node_put(parent);
		पूर्ण

		clkspec.np = node;
		clkspec.args_count = num_args;
		क्रम (i = 0; i < num_args; i++) अणु
			ret = kstrtoपूर्णांक(tags[i], i ? 10 : 16, clkspec.args + i);
			अगर (ret) अणु
				pr_warn("Bad tag in %s at %d: %s\n",
					c->node_name, i, tags[i]);
				of_node_put(node);
				वापस;
			पूर्ण
		पूर्ण
		clk = of_clk_get_from_provider(&clkspec);
		of_node_put(node);
		अगर (!IS_ERR(clk)) अणु
			c->lk.clk = clk;
			clkdev_add(&c->lk);
		पूर्ण अन्यथा अणु
			अगर (num_args && !has_clkctrl_data) अणु
				काष्ठा device_node *np;

				np = of_find_compatible_node(शून्य, शून्य,
							     "ti,clkctrl");
				अगर (np) अणु
					has_clkctrl_data = true;
					of_node_put(np);
				पूर्ण अन्यथा अणु
					clkctrl_nodes_missing = true;

					pr_warn("missing clkctrl nodes, please update your dts.\n");
					जारी;
				पूर्ण
			पूर्ण

			pr_warn("failed to lookup clock node %s, ret=%ld\n",
				c->node_name, PTR_ERR(clk));
		पूर्ण
	पूर्ण
पूर्ण

काष्ठा clk_init_item अणु
	काष्ठा device_node *node;
	व्योम *user;
	ti_of_clk_init_cb_t func;
	काष्ठा list_head link;
पूर्ण;

अटल LIST_HEAD(retry_list);

/**
 * ti_clk_retry_init - retries a failed घड़ी init at later phase
 * @node: device not क्रम the घड़ी
 * @user: user data poपूर्णांकer
 * @func: init function to be called क्रम the घड़ी
 *
 * Adds a failed घड़ी init to the retry list. The retry list is parsed
 * once all the other घड़ीs have been initialized.
 */
पूर्णांक __init ti_clk_retry_init(काष्ठा device_node *node, व्योम *user,
			     ti_of_clk_init_cb_t func)
अणु
	काष्ठा clk_init_item *retry;

	pr_debug("%pOFn: adding to retry list...\n", node);
	retry = kzalloc(माप(*retry), GFP_KERNEL);
	अगर (!retry)
		वापस -ENOMEM;

	retry->node = node;
	retry->func = func;
	retry->user = user;
	list_add(&retry->link, &retry_list);

	वापस 0;
पूर्ण

/**
 * ti_clk_get_reg_addr - get रेजिस्टर address क्रम a घड़ी रेजिस्टर
 * @node: device node क्रम the घड़ी
 * @index: रेजिस्टर index from the घड़ी node
 * @reg: poपूर्णांकer to target रेजिस्टर काष्ठा
 *
 * Builds घड़ी रेजिस्टर address from device tree inक्रमmation, and वापसs
 * the data via the provided output poपूर्णांकer @reg. Returns 0 on success,
 * negative error value on failure.
 */
पूर्णांक ti_clk_get_reg_addr(काष्ठा device_node *node, पूर्णांक index,
			काष्ठा clk_omap_reg *reg)
अणु
	u32 val;
	पूर्णांक i;

	क्रम (i = 0; i < CLK_MAX_MEMMAPS; i++) अणु
		अगर (घड़ीs_node_ptr[i] == node->parent)
			अवरोध;
	पूर्ण

	अगर (i == CLK_MAX_MEMMAPS) अणु
		pr_err("clk-provider not found for %pOFn!\n", node);
		वापस -ENOENT;
	पूर्ण

	reg->index = i;

	अगर (of_property_पढ़ो_u32_index(node, "reg", index, &val)) अणु
		pr_err("%pOFn must have reg[%d]!\n", node, index);
		वापस -EINVAL;
	पूर्ण

	reg->offset = val;
	reg->ptr = शून्य;

	वापस 0;
पूर्ण

व्योम ti_clk_latch(काष्ठा clk_omap_reg *reg, s8 shअगरt)
अणु
	u32 latch;

	अगर (shअगरt < 0)
		वापस;

	latch = 1 << shअगरt;

	ti_clk_ll_ops->clk_rmw(latch, latch, reg);
	ti_clk_ll_ops->clk_rmw(0, latch, reg);
	ti_clk_ll_ops->clk_पढ़ोl(reg); /* OCP barrier */
पूर्ण

/**
 * omap2_clk_provider_init - init master घड़ी provider
 * @parent: master node
 * @index: पूर्णांकernal index क्रम clk_reg_ops
 * @syscon: syscon regmap poपूर्णांकer क्रम accessing घड़ी रेजिस्टरs
 * @mem: iomem poपूर्णांकer क्रम the घड़ी provider memory area, only used अगर
 *       syscon is not provided
 *
 * Initializes a master घड़ी IP block. This basically sets up the
 * mapping from घड़ीs node to the memory map index. All the घड़ीs
 * are then initialized through the common of_clk_init call, and the
 * घड़ीs will access their memory maps based on the node layout.
 * Returns 0 in success.
 */
पूर्णांक __init omap2_clk_provider_init(काष्ठा device_node *parent, पूर्णांक index,
				   काष्ठा regmap *syscon, व्योम __iomem *mem)
अणु
	काष्ठा device_node *घड़ीs;
	काष्ठा clk_iomap *io;

	/* get घड़ीs क्रम this parent */
	घड़ीs = of_get_child_by_name(parent, "clocks");
	अगर (!घड़ीs) अणु
		pr_err("%pOFn missing 'clocks' child node.\n", parent);
		वापस -EINVAL;
	पूर्ण

	/* add घड़ीs node info */
	घड़ीs_node_ptr[index] = घड़ीs;

	io = kzalloc(माप(*io), GFP_KERNEL);
	अगर (!io)
		वापस -ENOMEM;

	io->regmap = syscon;
	io->mem = mem;

	clk_memmaps[index] = io;

	वापस 0;
पूर्ण

/**
 * omap2_clk_legacy_provider_init - initialize a legacy घड़ी provider
 * @index: index क्रम the घड़ी provider
 * @mem: iomem poपूर्णांकer क्रम the घड़ी provider memory area
 *
 * Initializes a legacy घड़ी provider memory mapping.
 */
व्योम __init omap2_clk_legacy_provider_init(पूर्णांक index, व्योम __iomem *mem)
अणु
	काष्ठा clk_iomap *io;

	io = memblock_alloc(माप(*io), SMP_CACHE_BYTES);
	अगर (!io)
		panic("%s: Failed to allocate %zu bytes\n", __func__,
		      माप(*io));

	io->mem = mem;

	clk_memmaps[index] = io;
पूर्ण

/**
 * ti_dt_clk_init_retry_clks - init घड़ीs from the retry list
 *
 * Initializes any घड़ीs that have failed to initialize beक्रमe,
 * reasons being missing parent node(s) during earlier init. This
 * typically happens only क्रम DPLLs which need to have both of their
 * parent घड़ीs पढ़ोy during init.
 */
व्योम ti_dt_clk_init_retry_clks(व्योम)
अणु
	काष्ठा clk_init_item *retry;
	काष्ठा clk_init_item *पंचांगp;
	पूर्णांक retries = 5;

	जबतक (!list_empty(&retry_list) && retries) अणु
		list_क्रम_each_entry_safe(retry, पंचांगp, &retry_list, link) अणु
			pr_debug("retry-init: %pOFn\n", retry->node);
			retry->func(retry->user, retry->node);
			list_del(&retry->link);
			kमुक्त(retry);
		पूर्ण
		retries--;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा of_device_id simple_clk_match_table[] __initस्थिर = अणु
	अणु .compatible = "fixed-clock" पूर्ण,
	अणु .compatible = "fixed-factor-clock" पूर्ण,
	अणु पूर्ण
पूर्ण;

/**
 * ti_clk_add_aliases - setup घड़ी aliases
 *
 * Sets up any missing घड़ी aliases. No वापस value.
 */
व्योम __init ti_clk_add_aliases(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा clk *clk;

	क्रम_each_matching_node(np, simple_clk_match_table) अणु
		काष्ठा of_phandle_args clkspec;

		clkspec.np = np;
		clk = of_clk_get_from_provider(&clkspec);

		ti_clk_add_alias(शून्य, clk, np->name);
	पूर्ण
पूर्ण

/**
 * ti_clk_setup_features - setup घड़ी features flags
 * @features: features definition to use
 *
 * Initializes the घड़ी driver features flags based on platक्रमm
 * provided data. No वापस value.
 */
व्योम __init ti_clk_setup_features(काष्ठा ti_clk_features *features)
अणु
	स_नकल(&ti_clk_features, features, माप(*features));
पूर्ण

/**
 * ti_clk_get_features - get घड़ी driver features flags
 *
 * Get TI घड़ी driver features description. Returns a poपूर्णांकer
 * to the current feature setup.
 */
स्थिर काष्ठा ti_clk_features *ti_clk_get_features(व्योम)
अणु
	वापस &ti_clk_features;
पूर्ण

/**
 * omap2_clk_enable_init_घड़ीs - prepare & enable a list of घड़ीs
 * @clk_names: ptr to an array of strings of घड़ी names to enable
 * @num_घड़ीs: number of घड़ी names in @clk_names
 *
 * Prepare and enable a list of घड़ीs, named by @clk_names.  No
 * वापस value. XXX Deprecated; only needed until these घड़ीs are
 * properly claimed and enabled by the drivers or core code that uses
 * them.  XXX What code disables & calls clk_put on these घड़ीs?
 */
व्योम omap2_clk_enable_init_घड़ीs(स्थिर अक्षर **clk_names, u8 num_घड़ीs)
अणु
	काष्ठा clk *init_clk;
	पूर्णांक i;

	क्रम (i = 0; i < num_घड़ीs; i++) अणु
		init_clk = clk_get(शून्य, clk_names[i]);
		अगर (WARN(IS_ERR(init_clk), "could not find init clock %s\n",
			 clk_names[i]))
			जारी;
		clk_prepare_enable(init_clk);
	पूर्ण
पूर्ण

/**
 * ti_clk_add_alias - add a घड़ी alias क्रम a TI घड़ी
 * @dev: device alias क्रम this घड़ी
 * @clk: घड़ी handle to create alias क्रम
 * @con: connection ID क्रम this घड़ी
 *
 * Creates a घड़ी alias क्रम a TI घड़ी. Allocates the घड़ी lookup entry
 * and assigns the data to it. Returns 0 अगर successful, negative error
 * value otherwise.
 */
पूर्णांक ti_clk_add_alias(काष्ठा device *dev, काष्ठा clk *clk, स्थिर अक्षर *con)
अणु
	काष्ठा clk_lookup *cl;

	अगर (!clk)
		वापस 0;

	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	cl = kzalloc(माप(*cl), GFP_KERNEL);
	अगर (!cl)
		वापस -ENOMEM;

	अगर (dev)
		cl->dev_id = dev_name(dev);
	cl->con_id = con;
	cl->clk = clk;

	clkdev_add(cl);

	वापस 0;
पूर्ण

/**
 * ti_clk_रेजिस्टर - रेजिस्टर a TI घड़ी to the common घड़ी framework
 * @dev: device क्रम this घड़ी
 * @hw: hardware घड़ी handle
 * @con: connection ID क्रम this घड़ी
 *
 * Registers a TI घड़ी to the common घड़ी framework, and adds a घड़ी
 * alias क्रम it. Returns a handle to the रेजिस्टरed घड़ी अगर successful,
 * ERR_PTR value in failure.
 */
काष्ठा clk *ti_clk_रेजिस्टर(काष्ठा device *dev, काष्ठा clk_hw *hw,
			    स्थिर अक्षर *con)
अणु
	काष्ठा clk *clk;
	पूर्णांक ret;

	clk = clk_रेजिस्टर(dev, hw);
	अगर (IS_ERR(clk))
		वापस clk;

	ret = ti_clk_add_alias(dev, clk, con);
	अगर (ret) अणु
		clk_unरेजिस्टर(clk);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस clk;
पूर्ण

/**
 * ti_clk_रेजिस्टर_omap_hw - रेजिस्टर a clk_hw_omap to the घड़ी framework
 * @dev: device क्रम this घड़ी
 * @hw: hardware घड़ी handle
 * @con: connection ID क्रम this घड़ी
 *
 * Registers a clk_hw_omap घड़ी to the घड़ी framewor, adds a घड़ी alias
 * क्रम it, and adds the list to the available clk_hw_omap type घड़ीs.
 * Returns a handle to the रेजिस्टरed घड़ी अगर successful, ERR_PTR value
 * in failure.
 */
काष्ठा clk *ti_clk_रेजिस्टर_omap_hw(काष्ठा device *dev, काष्ठा clk_hw *hw,
				    स्थिर अक्षर *con)
अणु
	काष्ठा clk *clk;
	काष्ठा clk_hw_omap *oclk;

	clk = ti_clk_रेजिस्टर(dev, hw, con);
	अगर (IS_ERR(clk))
		वापस clk;

	oclk = to_clk_hw_omap(hw);

	list_add(&oclk->node, &clk_hw_omap_घड़ीs);

	वापस clk;
पूर्ण

/**
 * omap2_clk_क्रम_each - call function क्रम each रेजिस्टरed clk_hw_omap
 * @fn: poपूर्णांकer to a callback function
 *
 * Call @fn क्रम each रेजिस्टरed clk_hw_omap, passing @hw to each
 * function.  @fn must वापस 0 क्रम success or any other value क्रम
 * failure.  If @fn वापसs non-zero, the iteration across घड़ीs
 * will stop and the non-zero वापस value will be passed to the
 * caller of omap2_clk_क्रम_each().
 */
पूर्णांक omap2_clk_क्रम_each(पूर्णांक (*fn)(काष्ठा clk_hw_omap *hw))
अणु
	पूर्णांक ret;
	काष्ठा clk_hw_omap *hw;

	list_क्रम_each_entry(hw, &clk_hw_omap_घड़ीs, node) अणु
		ret = (*fn)(hw);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * omap2_clk_is_hw_omap - check अगर the provided clk_hw is OMAP घड़ी
 * @hw: clk_hw to check अगर it is an omap घड़ी or not
 *
 * Checks अगर the provided clk_hw is OMAP घड़ी or not. Returns true अगर
 * it is, false otherwise.
 */
bool omap2_clk_is_hw_omap(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw_omap *oclk;

	list_क्रम_each_entry(oclk, &clk_hw_omap_घड़ीs, node) अणु
		अगर (&oclk->hw == hw)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण
