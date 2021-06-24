<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018, The Linux Foundation. All rights reserved.

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>

#समावेश "clk-krait.h"

अटल अचिन्हित पूर्णांक sec_mux_map[] = अणु
	2,
	0,
पूर्ण;

अटल अचिन्हित पूर्णांक pri_mux_map[] = अणु
	1,
	2,
	0,
पूर्ण;

/*
 * Notअगरier function क्रम चयनing the muxes to safe parent
 * जबतक the hfpll is getting reprogrammed.
 */
अटल पूर्णांक krait_notअगरier_cb(काष्ठा notअगरier_block *nb,
			     अचिन्हित दीर्घ event,
			     व्योम *data)
अणु
	पूर्णांक ret = 0;
	काष्ठा krait_mux_clk *mux = container_of(nb, काष्ठा krait_mux_clk,
						 clk_nb);
	/* Switch to safe parent */
	अगर (event == PRE_RATE_CHANGE) अणु
		mux->old_index = krait_mux_clk_ops.get_parent(&mux->hw);
		ret = krait_mux_clk_ops.set_parent(&mux->hw, mux->safe_sel);
		mux->reparent = false;
	/*
	 * By the समय POST_RATE_CHANGE notअगरier is called,
	 * clk framework itself would have changed the parent क्रम the new rate.
	 * Only otherwise, put back to the old parent.
	 */
	पूर्ण अन्यथा अगर (event == POST_RATE_CHANGE) अणु
		अगर (!mux->reparent)
			ret = krait_mux_clk_ops.set_parent(&mux->hw,
							   mux->old_index);
	पूर्ण

	वापस notअगरier_from_त्रुटि_सं(ret);
पूर्ण

अटल पूर्णांक krait_notअगरier_रेजिस्टर(काष्ठा device *dev, काष्ठा clk *clk,
				   काष्ठा krait_mux_clk *mux)
अणु
	पूर्णांक ret = 0;

	mux->clk_nb.notअगरier_call = krait_notअगरier_cb;
	ret = clk_notअगरier_रेजिस्टर(clk, &mux->clk_nb);
	अगर (ret)
		dev_err(dev, "failed to register clock notifier: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक
krait_add_भाग(काष्ठा device *dev, पूर्णांक id, स्थिर अक्षर *s, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा krait_भाग2_clk *भाग;
	काष्ठा clk_init_data init = अणु
		.num_parents = 1,
		.ops = &krait_भाग2_clk_ops,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण;
	स्थिर अक्षर *p_names[1];
	काष्ठा clk *clk;

	भाग = devm_kzalloc(dev, माप(*भाग), GFP_KERNEL);
	अगर (!भाग)
		वापस -ENOMEM;

	भाग->width = 2;
	भाग->shअगरt = 6;
	भाग->lpl = id >= 0;
	भाग->offset = offset;
	भाग->hw.init = &init;

	init.name = kaप्र_लिखो(GFP_KERNEL, "hfpll%s_div", s);
	अगर (!init.name)
		वापस -ENOMEM;

	init.parent_names = p_names;
	p_names[0] = kaप्र_लिखो(GFP_KERNEL, "hfpll%s", s);
	अगर (!p_names[0]) अणु
		kमुक्त(init.name);
		वापस -ENOMEM;
	पूर्ण

	clk = devm_clk_रेजिस्टर(dev, &भाग->hw);
	kमुक्त(p_names[0]);
	kमुक्त(init.name);

	वापस PTR_ERR_OR_ZERO(clk);
पूर्ण

अटल पूर्णांक
krait_add_sec_mux(काष्ठा device *dev, पूर्णांक id, स्थिर अक्षर *s,
		  अचिन्हित पूर्णांक offset, bool unique_aux)
अणु
	पूर्णांक ret;
	काष्ठा krait_mux_clk *mux;
	अटल स्थिर अक्षर *sec_mux_list[] = अणु
		"acpu_aux",
		"qsb",
	पूर्ण;
	काष्ठा clk_init_data init = अणु
		.parent_names = sec_mux_list,
		.num_parents = ARRAY_SIZE(sec_mux_list),
		.ops = &krait_mux_clk_ops,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण;
	काष्ठा clk *clk;

	mux = devm_kzalloc(dev, माप(*mux), GFP_KERNEL);
	अगर (!mux)
		वापस -ENOMEM;

	mux->offset = offset;
	mux->lpl = id >= 0;
	mux->mask = 0x3;
	mux->shअगरt = 2;
	mux->parent_map = sec_mux_map;
	mux->hw.init = &init;
	mux->safe_sel = 0;

	init.name = kaप्र_लिखो(GFP_KERNEL, "krait%s_sec_mux", s);
	अगर (!init.name)
		वापस -ENOMEM;

	अगर (unique_aux) अणु
		sec_mux_list[0] = kaप्र_लिखो(GFP_KERNEL, "acpu%s_aux", s);
		अगर (!sec_mux_list[0]) अणु
			clk = ERR_PTR(-ENOMEM);
			जाओ err_aux;
		पूर्ण
	पूर्ण

	clk = devm_clk_रेजिस्टर(dev, &mux->hw);

	ret = krait_notअगरier_रेजिस्टर(dev, clk, mux);
	अगर (ret)
		जाओ unique_aux;

unique_aux:
	अगर (unique_aux)
		kमुक्त(sec_mux_list[0]);
err_aux:
	kमुक्त(init.name);
	वापस PTR_ERR_OR_ZERO(clk);
पूर्ण

अटल काष्ठा clk *
krait_add_pri_mux(काष्ठा device *dev, पूर्णांक id, स्थिर अक्षर *s,
		  अचिन्हित पूर्णांक offset)
अणु
	पूर्णांक ret;
	काष्ठा krait_mux_clk *mux;
	स्थिर अक्षर *p_names[3];
	काष्ठा clk_init_data init = अणु
		.parent_names = p_names,
		.num_parents = ARRAY_SIZE(p_names),
		.ops = &krait_mux_clk_ops,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण;
	काष्ठा clk *clk;

	mux = devm_kzalloc(dev, माप(*mux), GFP_KERNEL);
	अगर (!mux)
		वापस ERR_PTR(-ENOMEM);

	mux->mask = 0x3;
	mux->shअगरt = 0;
	mux->offset = offset;
	mux->lpl = id >= 0;
	mux->parent_map = pri_mux_map;
	mux->hw.init = &init;
	mux->safe_sel = 2;

	init.name = kaप्र_लिखो(GFP_KERNEL, "krait%s_pri_mux", s);
	अगर (!init.name)
		वापस ERR_PTR(-ENOMEM);

	p_names[0] = kaप्र_लिखो(GFP_KERNEL, "hfpll%s", s);
	अगर (!p_names[0]) अणु
		clk = ERR_PTR(-ENOMEM);
		जाओ err_p0;
	पूर्ण

	p_names[1] = kaप्र_लिखो(GFP_KERNEL, "hfpll%s_div", s);
	अगर (!p_names[1]) अणु
		clk = ERR_PTR(-ENOMEM);
		जाओ err_p1;
	पूर्ण

	p_names[2] = kaप्र_लिखो(GFP_KERNEL, "krait%s_sec_mux", s);
	अगर (!p_names[2]) अणु
		clk = ERR_PTR(-ENOMEM);
		जाओ err_p2;
	पूर्ण

	clk = devm_clk_रेजिस्टर(dev, &mux->hw);

	ret = krait_notअगरier_रेजिस्टर(dev, clk, mux);
	अगर (ret)
		जाओ err_p3;
err_p3:
	kमुक्त(p_names[2]);
err_p2:
	kमुक्त(p_names[1]);
err_p1:
	kमुक्त(p_names[0]);
err_p0:
	kमुक्त(init.name);
	वापस clk;
पूर्ण

/* id < 0 क्रम L2, otherwise id == physical CPU number */
अटल काष्ठा clk *krait_add_clks(काष्ठा device *dev, पूर्णांक id, bool unique_aux)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक offset;
	व्योम *p = शून्य;
	स्थिर अक्षर *s;
	काष्ठा clk *clk;

	अगर (id >= 0) अणु
		offset = 0x4501 + (0x1000 * id);
		s = p = kaप्र_लिखो(GFP_KERNEL, "%d", id);
		अगर (!s)
			वापस ERR_PTR(-ENOMEM);
	पूर्ण अन्यथा अणु
		offset = 0x500;
		s = "_l2";
	पूर्ण

	ret = krait_add_भाग(dev, id, s, offset);
	अगर (ret) अणु
		clk = ERR_PTR(ret);
		जाओ err;
	पूर्ण

	ret = krait_add_sec_mux(dev, id, s, offset, unique_aux);
	अगर (ret) अणु
		clk = ERR_PTR(ret);
		जाओ err;
	पूर्ण

	clk = krait_add_pri_mux(dev, id, s, offset);
err:
	kमुक्त(p);
	वापस clk;
पूर्ण

अटल काष्ठा clk *krait_of_get(काष्ठा of_phandle_args *clkspec, व्योम *data)
अणु
	अचिन्हित पूर्णांक idx = clkspec->args[0];
	काष्ठा clk **clks = data;

	अगर (idx >= 5) अणु
		pr_err("%s: invalid clock index %d\n", __func__, idx);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस clks[idx] ? : ERR_PTR(-ENODEV);
पूर्ण

अटल स्थिर काष्ठा of_device_id krait_cc_match_table[] = अणु
	अणु .compatible = "qcom,krait-cc-v1", (व्योम *)1UL पूर्ण,
	अणु .compatible = "qcom,krait-cc-v2" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, krait_cc_match_table);

अटल पूर्णांक krait_cc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा of_device_id *id;
	अचिन्हित दीर्घ cur_rate, aux_rate;
	पूर्णांक cpu;
	काष्ठा clk *clk;
	काष्ठा clk **clks;
	काष्ठा clk *l2_pri_mux_clk;

	id = of_match_device(krait_cc_match_table, dev);
	अगर (!id)
		वापस -ENODEV;

	/* Rate is 1 because 0 causes problems क्रम __clk_mux_determine_rate */
	clk = clk_रेजिस्टर_fixed_rate(dev, "qsb", शून्य, 0, 1);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	अगर (!id->data) अणु
		clk = clk_रेजिस्टर_fixed_factor(dev, "acpu_aux",
						"gpll0_vote", 0, 1, 2);
		अगर (IS_ERR(clk))
			वापस PTR_ERR(clk);
	पूर्ण

	/* Krait configurations have at most 4 CPUs and one L2 */
	clks = devm_kसुस्मृति(dev, 5, माप(*clks), GFP_KERNEL);
	अगर (!clks)
		वापस -ENOMEM;

	क्रम_each_possible_cpu(cpu) अणु
		clk = krait_add_clks(dev, cpu, id->data);
		अगर (IS_ERR(clk))
			वापस PTR_ERR(clk);
		clks[cpu] = clk;
	पूर्ण

	l2_pri_mux_clk = krait_add_clks(dev, -1, id->data);
	अगर (IS_ERR(l2_pri_mux_clk))
		वापस PTR_ERR(l2_pri_mux_clk);
	clks[4] = l2_pri_mux_clk;

	/*
	 * We करोn't want the CPU or L2 घड़ीs to be turned off at late init
	 * अगर CPUFREQ or HOTPLUG configs are disabled. So, bump up the
	 * refcount of these घड़ीs. Any cpufreq/hotplug manager can assume
	 * that the घड़ीs have alपढ़ोy been prepared and enabled by the समय
	 * they take over.
	 */
	क्रम_each_online_cpu(cpu) अणु
		clk_prepare_enable(l2_pri_mux_clk);
		WARN(clk_prepare_enable(clks[cpu]),
		     "Unable to turn on CPU%d clock", cpu);
	पूर्ण

	/*
	 * Force reinit of HFPLLs and muxes to overग_लिखो any potential
	 * incorrect configuration of HFPLLs and muxes by the bootloader.
	 * While at it, also make sure the cores are running at known rates
	 * and prपूर्णांक the current rate.
	 *
	 * The घड़ीs are set to aux घड़ी rate first to make sure the
	 * secondary mux is not sourcing off of QSB. The rate is then set to
	 * two dअगरferent rates to क्रमce a HFPLL reinit under all
	 * circumstances.
	 */
	cur_rate = clk_get_rate(l2_pri_mux_clk);
	aux_rate = 384000000;
	अगर (cur_rate == 1) अणु
		pr_info("L2 @ QSB rate. Forcing new rate.\n");
		cur_rate = aux_rate;
	पूर्ण
	clk_set_rate(l2_pri_mux_clk, aux_rate);
	clk_set_rate(l2_pri_mux_clk, 2);
	clk_set_rate(l2_pri_mux_clk, cur_rate);
	pr_info("L2 @ %lu KHz\n", clk_get_rate(l2_pri_mux_clk) / 1000);
	क्रम_each_possible_cpu(cpu) अणु
		clk = clks[cpu];
		cur_rate = clk_get_rate(clk);
		अगर (cur_rate == 1) अणु
			pr_info("CPU%d @ QSB rate. Forcing new rate.\n", cpu);
			cur_rate = aux_rate;
		पूर्ण

		clk_set_rate(clk, aux_rate);
		clk_set_rate(clk, 2);
		clk_set_rate(clk, cur_rate);
		pr_info("CPU%d @ %lu KHz\n", cpu, clk_get_rate(clk) / 1000);
	पूर्ण

	of_clk_add_provider(dev->of_node, krait_of_get, clks);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver krait_cc_driver = अणु
	.probe = krait_cc_probe,
	.driver = अणु
		.name = "krait-cc",
		.of_match_table = krait_cc_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(krait_cc_driver);

MODULE_DESCRIPTION("Krait CPU Clock Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:krait-cc");
