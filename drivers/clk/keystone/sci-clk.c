<शैली गुरु>
/*
 * SCI Clock driver क्रम keystone based devices
 *
 * Copyright (C) 2015-2016 Texas Instruments Incorporated - https://www.ti.com/
 *	Tero Kristo <t-kristo@ti.com>
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
#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/soc/ti/ti_sci_protocol.h>
#समावेश <linux/द्वा_खोज.h>
#समावेश <linux/list_sort.h>

#घोषणा SCI_CLK_SSC_ENABLE		BIT(0)
#घोषणा SCI_CLK_ALLOW_FREQ_CHANGE	BIT(1)
#घोषणा SCI_CLK_INPUT_TERMINATION	BIT(2)

/**
 * काष्ठा sci_clk_provider - TI SCI घड़ी provider representation
 * @sci: Handle to the System Control Interface protocol handler
 * @ops: Poपूर्णांकer to the SCI ops to be used by the घड़ीs
 * @dev: Device poपूर्णांकer क्रम the घड़ी provider
 * @घड़ीs: Clocks array क्रम this device
 * @num_घड़ीs: Total number of घड़ीs क्रम this provider
 */
काष्ठा sci_clk_provider अणु
	स्थिर काष्ठा ti_sci_handle *sci;
	स्थिर काष्ठा ti_sci_clk_ops *ops;
	काष्ठा device *dev;
	काष्ठा sci_clk **घड़ीs;
	पूर्णांक num_घड़ीs;
पूर्ण;

/**
 * काष्ठा sci_clk - TI SCI घड़ी representation
 * @hw:		 Hardware घड़ी cookie क्रम common घड़ी framework
 * @dev_id:	 Device index
 * @clk_id:	 Clock index
 * @num_parents: Number of parents क्रम this घड़ी
 * @provider:	 Master घड़ी provider
 * @flags:	 Flags क्रम the घड़ी
 * @node:	 Link क्रम handling घड़ीs probed via DT
 * @cached_req:	 Cached requested freq क्रम determine rate calls
 * @cached_res:	 Cached result freq क्रम determine rate calls
 */
काष्ठा sci_clk अणु
	काष्ठा clk_hw hw;
	u16 dev_id;
	u32 clk_id;
	u32 num_parents;
	काष्ठा sci_clk_provider *provider;
	u8 flags;
	काष्ठा list_head node;
	अचिन्हित दीर्घ cached_req;
	अचिन्हित दीर्घ cached_res;
पूर्ण;

#घोषणा to_sci_clk(_hw) container_of(_hw, काष्ठा sci_clk, hw)

/**
 * sci_clk_prepare - Prepare (enable) a TI SCI घड़ी
 * @hw: घड़ी to prepare
 *
 * Prepares a घड़ी to be actively used. Returns the SCI protocol status.
 */
अटल पूर्णांक sci_clk_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा sci_clk *clk = to_sci_clk(hw);
	bool enable_ssc = clk->flags & SCI_CLK_SSC_ENABLE;
	bool allow_freq_change = clk->flags & SCI_CLK_ALLOW_FREQ_CHANGE;
	bool input_termination = clk->flags & SCI_CLK_INPUT_TERMINATION;

	वापस clk->provider->ops->get_घड़ी(clk->provider->sci, clk->dev_id,
					     clk->clk_id, enable_ssc,
					     allow_freq_change,
					     input_termination);
पूर्ण

/**
 * sci_clk_unprepare - Un-prepares (disables) a TI SCI घड़ी
 * @hw: घड़ी to unprepare
 *
 * Un-prepares a घड़ी from active state.
 */
अटल व्योम sci_clk_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा sci_clk *clk = to_sci_clk(hw);
	पूर्णांक ret;

	ret = clk->provider->ops->put_घड़ी(clk->provider->sci, clk->dev_id,
					    clk->clk_id);
	अगर (ret)
		dev_err(clk->provider->dev,
			"unprepare failed for dev=%d, clk=%d, ret=%d\n",
			clk->dev_id, clk->clk_id, ret);
पूर्ण

/**
 * sci_clk_is_prepared - Check अगर a TI SCI घड़ी is prepared or not
 * @hw: घड़ी to check status क्रम
 *
 * Checks अगर a घड़ी is prepared (enabled) in hardware. Returns non-zero
 * value अगर घड़ी is enabled, zero otherwise.
 */
अटल पूर्णांक sci_clk_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा sci_clk *clk = to_sci_clk(hw);
	bool req_state, current_state;
	पूर्णांक ret;

	ret = clk->provider->ops->is_on(clk->provider->sci, clk->dev_id,
					clk->clk_id, &req_state,
					&current_state);
	अगर (ret) अणु
		dev_err(clk->provider->dev,
			"is_prepared failed for dev=%d, clk=%d, ret=%d\n",
			clk->dev_id, clk->clk_id, ret);
		वापस 0;
	पूर्ण

	वापस req_state;
पूर्ण

/**
 * sci_clk_recalc_rate - Get घड़ी rate क्रम a TI SCI घड़ी
 * @hw: घड़ी to get rate क्रम
 * @parent_rate: parent rate provided by common घड़ी framework, not used
 *
 * Gets the current घड़ी rate of a TI SCI घड़ी. Returns the current
 * घड़ी rate, or zero in failure.
 */
अटल अचिन्हित दीर्घ sci_clk_recalc_rate(काष्ठा clk_hw *hw,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sci_clk *clk = to_sci_clk(hw);
	u64 freq;
	पूर्णांक ret;

	ret = clk->provider->ops->get_freq(clk->provider->sci, clk->dev_id,
					   clk->clk_id, &freq);
	अगर (ret) अणु
		dev_err(clk->provider->dev,
			"recalc-rate failed for dev=%d, clk=%d, ret=%d\n",
			clk->dev_id, clk->clk_id, ret);
		वापस 0;
	पूर्ण

	वापस freq;
पूर्ण

/**
 * sci_clk_determine_rate - Determines a घड़ी rate a घड़ी can be set to
 * @hw: घड़ी to change rate क्रम
 * @req: requested rate configuration क्रम the घड़ी
 *
 * Determines a suitable घड़ी rate and parent क्रम a TI SCI घड़ी.
 * The parent handling is un-used, as generally the parent घड़ी rates
 * are not known by the kernel; instead these are पूर्णांकernally handled
 * by the firmware. Returns 0 on success, negative error value on failure.
 */
अटल पूर्णांक sci_clk_determine_rate(काष्ठा clk_hw *hw,
				  काष्ठा clk_rate_request *req)
अणु
	काष्ठा sci_clk *clk = to_sci_clk(hw);
	पूर्णांक ret;
	u64 new_rate;

	अगर (clk->cached_req && clk->cached_req == req->rate) अणु
		req->rate = clk->cached_res;
		वापस 0;
	पूर्ण

	ret = clk->provider->ops->get_best_match_freq(clk->provider->sci,
						      clk->dev_id,
						      clk->clk_id,
						      req->min_rate,
						      req->rate,
						      req->max_rate,
						      &new_rate);
	अगर (ret) अणु
		dev_err(clk->provider->dev,
			"determine-rate failed for dev=%d, clk=%d, ret=%d\n",
			clk->dev_id, clk->clk_id, ret);
		वापस ret;
	पूर्ण

	clk->cached_req = req->rate;
	clk->cached_res = new_rate;

	req->rate = new_rate;

	वापस 0;
पूर्ण

/**
 * sci_clk_set_rate - Set rate क्रम a TI SCI घड़ी
 * @hw: घड़ी to change rate क्रम
 * @rate: target rate क्रम the घड़ी
 * @parent_rate: rate of the घड़ी parent, not used क्रम TI SCI घड़ीs
 *
 * Sets a घड़ी frequency क्रम a TI SCI घड़ी. Returns the TI SCI
 * protocol status.
 */
अटल पूर्णांक sci_clk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sci_clk *clk = to_sci_clk(hw);

	वापस clk->provider->ops->set_freq(clk->provider->sci, clk->dev_id,
					    clk->clk_id, rate / 10 * 9, rate,
					    rate / 10 * 11);
पूर्ण

/**
 * sci_clk_get_parent - Get the current parent of a TI SCI घड़ी
 * @hw: घड़ी to get parent क्रम
 *
 * Returns the index of the currently selected parent क्रम a TI SCI घड़ी.
 */
अटल u8 sci_clk_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा sci_clk *clk = to_sci_clk(hw);
	u32 parent_id = 0;
	पूर्णांक ret;

	ret = clk->provider->ops->get_parent(clk->provider->sci, clk->dev_id,
					     clk->clk_id, (व्योम *)&parent_id);
	अगर (ret) अणु
		dev_err(clk->provider->dev,
			"get-parent failed for dev=%d, clk=%d, ret=%d\n",
			clk->dev_id, clk->clk_id, ret);
		वापस 0;
	पूर्ण

	parent_id = parent_id - clk->clk_id - 1;

	वापस (u8)parent_id;
पूर्ण

/**
 * sci_clk_set_parent - Set the parent of a TI SCI घड़ी
 * @hw: घड़ी to set parent क्रम
 * @index: new parent index क्रम the घड़ी
 *
 * Sets the parent of a TI SCI घड़ी. Return TI SCI protocol status.
 */
अटल पूर्णांक sci_clk_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा sci_clk *clk = to_sci_clk(hw);

	clk->cached_req = 0;

	वापस clk->provider->ops->set_parent(clk->provider->sci, clk->dev_id,
					      clk->clk_id,
					      index + 1 + clk->clk_id);
पूर्ण

अटल स्थिर काष्ठा clk_ops sci_clk_ops = अणु
	.prepare = sci_clk_prepare,
	.unprepare = sci_clk_unprepare,
	.is_prepared = sci_clk_is_prepared,
	.recalc_rate = sci_clk_recalc_rate,
	.determine_rate = sci_clk_determine_rate,
	.set_rate = sci_clk_set_rate,
	.get_parent = sci_clk_get_parent,
	.set_parent = sci_clk_set_parent,
पूर्ण;

/**
 * _sci_clk_get - Gets a handle क्रम an SCI घड़ी
 * @provider: Handle to SCI घड़ी provider
 * @sci_clk: Handle to the SCI घड़ी to populate
 *
 * Gets a handle to an existing TI SCI hw घड़ी, or builds a new घड़ी
 * entry and रेजिस्टरs it with the common घड़ी framework. Called from
 * the common घड़ी framework, when a corresponding of_clk_get call is
 * executed, or recursively from itself when parsing parent घड़ीs.
 * Returns 0 on success, negative error code on failure.
 */
अटल पूर्णांक _sci_clk_build(काष्ठा sci_clk_provider *provider,
			  काष्ठा sci_clk *sci_clk)
अणु
	काष्ठा clk_init_data init = अणु शून्य पूर्ण;
	अक्षर *name = शून्य;
	अक्षर **parent_names = शून्य;
	पूर्णांक i;
	पूर्णांक ret = 0;

	name = kaप्र_लिखो(GFP_KERNEL, "clk:%d:%d", sci_clk->dev_id,
			 sci_clk->clk_id);

	init.name = name;

	/*
	 * From kernel poपूर्णांक of view, we only care about a घड़ीs parents,
	 * अगर it has more than 1 possible parent. In this हाल, it is going
	 * to have mux functionality. Otherwise it is going to act as a root
	 * घड़ी.
	 */
	अगर (sci_clk->num_parents < 2)
		sci_clk->num_parents = 0;

	अगर (sci_clk->num_parents) अणु
		parent_names = kसुस्मृति(sci_clk->num_parents, माप(अक्षर *),
				       GFP_KERNEL);

		अगर (!parent_names) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		क्रम (i = 0; i < sci_clk->num_parents; i++) अणु
			अक्षर *parent_name;

			parent_name = kaप्र_लिखो(GFP_KERNEL, "clk:%d:%d",
						sci_clk->dev_id,
						sci_clk->clk_id + 1 + i);
			अगर (!parent_name) अणु
				ret = -ENOMEM;
				जाओ err;
			पूर्ण
			parent_names[i] = parent_name;
		पूर्ण
		init.parent_names = (व्योम *)parent_names;
	पूर्ण

	init.ops = &sci_clk_ops;
	init.num_parents = sci_clk->num_parents;
	sci_clk->hw.init = &init;

	ret = devm_clk_hw_रेजिस्टर(provider->dev, &sci_clk->hw);
	अगर (ret)
		dev_err(provider->dev, "failed clk register with %d\n", ret);

err:
	अगर (parent_names) अणु
		क्रम (i = 0; i < sci_clk->num_parents; i++)
			kमुक्त(parent_names[i]);

		kमुक्त(parent_names);
	पूर्ण

	kमुक्त(name);

	वापस ret;
पूर्ण

अटल पूर्णांक _cmp_sci_clk(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा sci_clk *ca = a;
	स्थिर काष्ठा sci_clk *cb = *(काष्ठा sci_clk **)b;

	अगर (ca->dev_id == cb->dev_id && ca->clk_id == cb->clk_id)
		वापस 0;
	अगर (ca->dev_id > cb->dev_id ||
	    (ca->dev_id == cb->dev_id && ca->clk_id > cb->clk_id))
		वापस 1;
	वापस -1;
पूर्ण

/**
 * sci_clk_get - Xlate function क्रम getting घड़ी handles
 * @clkspec: device tree घड़ी specअगरier
 * @data: poपूर्णांकer to the घड़ी provider
 *
 * Xlate function क्रम retrieving घड़ी TI SCI hw घड़ी handles based on
 * device tree घड़ी specअगरier. Called from the common घड़ी framework,
 * when a corresponding of_clk_get call is executed. Returns a poपूर्णांकer
 * to the TI SCI hw घड़ी काष्ठा, or ERR_PTR value in failure.
 */
अटल काष्ठा clk_hw *sci_clk_get(काष्ठा of_phandle_args *clkspec, व्योम *data)
अणु
	काष्ठा sci_clk_provider *provider = data;
	काष्ठा sci_clk **clk;
	काष्ठा sci_clk key;

	अगर (clkspec->args_count != 2)
		वापस ERR_PTR(-EINVAL);

	key.dev_id = clkspec->args[0];
	key.clk_id = clkspec->args[1];

	clk = द्वा_खोज(&key, provider->घड़ीs, provider->num_घड़ीs,
		      माप(clk), _cmp_sci_clk);

	अगर (!clk)
		वापस ERR_PTR(-ENODEV);

	वापस &(*clk)->hw;
पूर्ण

अटल पूर्णांक ti_sci_init_घड़ीs(काष्ठा sci_clk_provider *p)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < p->num_घड़ीs; i++) अणु
		ret = _sci_clk_build(p, p->घड़ीs[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ti_sci_clk_of_match[] = अणु
	अणु .compatible = "ti,k2g-sci-clk" पूर्ण,
	अणु /* Sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ti_sci_clk_of_match);

#अगर_घोषित CONFIG_TI_SCI_CLK_PROBE_FROM_FW
अटल पूर्णांक ti_sci_scan_घड़ीs_from_fw(काष्ठा sci_clk_provider *provider)
अणु
	पूर्णांक ret;
	पूर्णांक num_clks = 0;
	काष्ठा sci_clk **clks = शून्य;
	काष्ठा sci_clk **पंचांगp_clks;
	काष्ठा sci_clk *sci_clk;
	पूर्णांक max_clks = 0;
	पूर्णांक clk_id = 0;
	पूर्णांक dev_id = 0;
	u32 num_parents = 0;
	पूर्णांक gap_size = 0;
	काष्ठा device *dev = provider->dev;

	जबतक (1) अणु
		ret = provider->ops->get_num_parents(provider->sci, dev_id,
						     clk_id,
						     (व्योम *)&num_parents);
		अगर (ret) अणु
			gap_size++;
			अगर (!clk_id) अणु
				अगर (gap_size >= 5)
					अवरोध;
				dev_id++;
			पूर्ण अन्यथा अणु
				अगर (gap_size >= 2) अणु
					dev_id++;
					clk_id = 0;
					gap_size = 0;
				पूर्ण अन्यथा अणु
					clk_id++;
				पूर्ण
			पूर्ण
			जारी;
		पूर्ण

		gap_size = 0;

		अगर (num_clks == max_clks) अणु
			पंचांगp_clks = devm_kदो_स्मृति_array(dev, max_clks + 64,
						      माप(sci_clk),
						      GFP_KERNEL);
			स_नकल(पंचांगp_clks, clks, max_clks * माप(sci_clk));
			अगर (max_clks)
				devm_kमुक्त(dev, clks);
			max_clks += 64;
			clks = पंचांगp_clks;
		पूर्ण

		sci_clk = devm_kzalloc(dev, माप(*sci_clk), GFP_KERNEL);
		अगर (!sci_clk)
			वापस -ENOMEM;
		sci_clk->dev_id = dev_id;
		sci_clk->clk_id = clk_id;
		sci_clk->provider = provider;
		sci_clk->num_parents = num_parents;

		clks[num_clks] = sci_clk;

		clk_id++;
		num_clks++;
	पूर्ण

	provider->घड़ीs = devm_kदो_स्मृति_array(dev, num_clks, माप(sci_clk),
					      GFP_KERNEL);
	अगर (!provider->घड़ीs)
		वापस -ENOMEM;

	स_नकल(provider->घड़ीs, clks, num_clks * माप(sci_clk));

	provider->num_घड़ीs = num_clks;

	devm_kमुक्त(dev, clks);

	वापस 0;
पूर्ण

#अन्यथा

अटल पूर्णांक _cmp_sci_clk_list(व्योम *priv, स्थिर काष्ठा list_head *a,
			     स्थिर काष्ठा list_head *b)
अणु
	काष्ठा sci_clk *ca = container_of(a, काष्ठा sci_clk, node);
	काष्ठा sci_clk *cb = container_of(b, काष्ठा sci_clk, node);

	वापस _cmp_sci_clk(ca, &cb);
पूर्ण

अटल पूर्णांक ti_sci_scan_घड़ीs_from_dt(काष्ठा sci_clk_provider *provider)
अणु
	काष्ठा device *dev = provider->dev;
	काष्ठा device_node *np = शून्य;
	पूर्णांक ret;
	पूर्णांक index;
	काष्ठा of_phandle_args args;
	काष्ठा list_head clks;
	काष्ठा sci_clk *sci_clk, *prev;
	पूर्णांक num_clks = 0;
	पूर्णांक num_parents;
	पूर्णांक clk_id;
	स्थिर अक्षर * स्थिर clk_names[] = अणु
		"clocks", "assigned-clocks", "assigned-clock-parents", शून्य
	पूर्ण;
	स्थिर अक्षर * स्थिर *clk_name;

	INIT_LIST_HEAD(&clks);

	clk_name = clk_names;

	जबतक (*clk_name) अणु
		np = of_find_node_with_property(np, *clk_name);
		अगर (!np) अणु
			clk_name++;
			जारी;
		पूर्ण

		अगर (!of_device_is_available(np))
			जारी;

		index = 0;

		करो अणु
			ret = of_parse_phandle_with_args(np, *clk_name,
							 "#clock-cells", index,
							 &args);
			अगर (ret)
				अवरोध;

			अगर (args.args_count == 2 && args.np == dev->of_node) अणु
				sci_clk = devm_kzalloc(dev, माप(*sci_clk),
						       GFP_KERNEL);
				अगर (!sci_clk)
					वापस -ENOMEM;

				sci_clk->dev_id = args.args[0];
				sci_clk->clk_id = args.args[1];
				sci_clk->provider = provider;
				provider->ops->get_num_parents(provider->sci,
							       sci_clk->dev_id,
							       sci_clk->clk_id,
							       (व्योम *)&sci_clk->num_parents);
				list_add_tail(&sci_clk->node, &clks);

				num_clks++;

				num_parents = sci_clk->num_parents;
				अगर (num_parents == 1)
					num_parents = 0;

				/*
				 * Linux kernel has inherent limitation
				 * of 255 घड़ी parents at the moment.
				 * Right now, it is not expected that
				 * any mux घड़ी from sci-clk driver
				 * would exceed that limit either, but
				 * the ABI basically provides that
				 * possibility. Prपूर्णांक out a warning अगर
				 * this happens क्रम any घड़ी.
				 */
				अगर (num_parents >= 255) अणु
					dev_warn(dev, "too many parents for dev=%d, clk=%d (%d), cropping to 255.\n",
						 sci_clk->dev_id,
						 sci_clk->clk_id, num_parents);
					num_parents = 255;
				पूर्ण

				clk_id = args.args[1] + 1;

				जबतक (num_parents--) अणु
					sci_clk = devm_kzalloc(dev,
							       माप(*sci_clk),
							       GFP_KERNEL);
					अगर (!sci_clk)
						वापस -ENOMEM;
					sci_clk->dev_id = args.args[0];
					sci_clk->clk_id = clk_id++;
					sci_clk->provider = provider;
					list_add_tail(&sci_clk->node, &clks);

					num_clks++;
				पूर्ण
			पूर्ण

			index++;
		पूर्ण जबतक (args.np);
	पूर्ण

	list_sort(शून्य, &clks, _cmp_sci_clk_list);

	provider->घड़ीs = devm_kदो_स्मृति_array(dev, num_clks, माप(sci_clk),
					      GFP_KERNEL);
	अगर (!provider->घड़ीs)
		वापस -ENOMEM;

	num_clks = 0;
	prev = शून्य;

	list_क्रम_each_entry(sci_clk, &clks, node) अणु
		अगर (prev && prev->dev_id == sci_clk->dev_id &&
		    prev->clk_id == sci_clk->clk_id)
			जारी;

		provider->घड़ीs[num_clks++] = sci_clk;
		prev = sci_clk;
	पूर्ण

	provider->num_घड़ीs = num_clks;

	वापस 0;
पूर्ण
#पूर्ण_अगर

/**
 * ti_sci_clk_probe - Probe function क्रम the TI SCI घड़ी driver
 * @pdev: platक्रमm device poपूर्णांकer to be probed
 *
 * Probes the TI SCI घड़ी device. Allocates a new घड़ी provider
 * and रेजिस्टरs this to the common घड़ी framework. Also applies
 * any required flags to the identअगरied घड़ीs via घड़ी lists
 * supplied from DT. Returns 0 क्रम success, negative error value
 * क्रम failure.
 */
अटल पूर्णांक ti_sci_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा sci_clk_provider *provider;
	स्थिर काष्ठा ti_sci_handle *handle;
	पूर्णांक ret;

	handle = devm_ti_sci_get_handle(dev);
	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);

	provider = devm_kzalloc(dev, माप(*provider), GFP_KERNEL);
	अगर (!provider)
		वापस -ENOMEM;

	provider->sci = handle;
	provider->ops = &handle->ops.clk_ops;
	provider->dev = dev;

#अगर_घोषित CONFIG_TI_SCI_CLK_PROBE_FROM_FW
	ret = ti_sci_scan_घड़ीs_from_fw(provider);
	अगर (ret) अणु
		dev_err(dev, "scan clocks from FW failed: %d\n", ret);
		वापस ret;
	पूर्ण
#अन्यथा
	ret = ti_sci_scan_घड़ीs_from_dt(provider);
	अगर (ret) अणु
		dev_err(dev, "scan clocks from DT failed: %d\n", ret);
		वापस ret;
	पूर्ण
#पूर्ण_अगर

	ret = ti_sci_init_घड़ीs(provider);
	अगर (ret) अणु
		pr_err("ti-sci-init-clocks failed.\n");
		वापस ret;
	पूर्ण

	वापस of_clk_add_hw_provider(np, sci_clk_get, provider);
पूर्ण

/**
 * ti_sci_clk_हटाओ - Remove TI SCI घड़ी device
 * @pdev: platक्रमm device poपूर्णांकer क्रम the device to be हटाओd
 *
 * Removes the TI SCI device. Unरेजिस्टरs the घड़ी provider रेजिस्टरed
 * via common घड़ी framework. Any memory allocated क्रम the device will
 * be मुक्त'd silently via the devm framework. Returns 0 always.
 */
अटल पूर्णांक ti_sci_clk_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	of_clk_del_provider(pdev->dev.of_node);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ti_sci_clk_driver = अणु
	.probe = ti_sci_clk_probe,
	.हटाओ = ti_sci_clk_हटाओ,
	.driver = अणु
		.name = "ti-sci-clk",
		.of_match_table = of_match_ptr(ti_sci_clk_of_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ti_sci_clk_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("TI System Control Interface(SCI) Clock driver");
MODULE_AUTHOR("Tero Kristo");
MODULE_ALIAS("platform:ti-sci-clk");
