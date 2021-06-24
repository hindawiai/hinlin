<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * System Control and Power Interface (SCMI) Protocol based घड़ी driver
 *
 * Copyright (C) 2018-2021 ARM Ltd.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/module.h>
#समावेश <linux/scmi_protocol.h>
#समावेश <यंत्र/भाग64.h>

अटल स्थिर काष्ठा scmi_clk_proto_ops *scmi_proto_clk_ops;

काष्ठा scmi_clk अणु
	u32 id;
	काष्ठा clk_hw hw;
	स्थिर काष्ठा scmi_घड़ी_info *info;
	स्थिर काष्ठा scmi_protocol_handle *ph;
पूर्ण;

#घोषणा to_scmi_clk(clk) container_of(clk, काष्ठा scmi_clk, hw)

अटल अचिन्हित दीर्घ scmi_clk_recalc_rate(काष्ठा clk_hw *hw,
					  अचिन्हित दीर्घ parent_rate)
अणु
	पूर्णांक ret;
	u64 rate;
	काष्ठा scmi_clk *clk = to_scmi_clk(hw);

	ret = scmi_proto_clk_ops->rate_get(clk->ph, clk->id, &rate);
	अगर (ret)
		वापस 0;
	वापस rate;
पूर्ण

अटल दीर्घ scmi_clk_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *parent_rate)
अणु
	u64 fmin, fmax, fपंचांगp;
	काष्ठा scmi_clk *clk = to_scmi_clk(hw);

	/*
	 * We can't figure out what rate it will be, so just वापस the
	 * rate back to the caller. scmi_clk_recalc_rate() will be called
	 * after the rate is set and we'll know what rate the घड़ी is
	 * running at then.
	 */
	अगर (clk->info->rate_discrete)
		वापस rate;

	fmin = clk->info->range.min_rate;
	fmax = clk->info->range.max_rate;
	अगर (rate <= fmin)
		वापस fmin;
	अन्यथा अगर (rate >= fmax)
		वापस fmax;

	fपंचांगp = rate - fmin;
	fपंचांगp += clk->info->range.step_size - 1; /* to round up */
	करो_भाग(fपंचांगp, clk->info->range.step_size);

	वापस fपंचांगp * clk->info->range.step_size + fmin;
पूर्ण

अटल पूर्णांक scmi_clk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा scmi_clk *clk = to_scmi_clk(hw);

	वापस scmi_proto_clk_ops->rate_set(clk->ph, clk->id, rate);
पूर्ण

अटल पूर्णांक scmi_clk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा scmi_clk *clk = to_scmi_clk(hw);

	वापस scmi_proto_clk_ops->enable(clk->ph, clk->id);
पूर्ण

अटल व्योम scmi_clk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा scmi_clk *clk = to_scmi_clk(hw);

	scmi_proto_clk_ops->disable(clk->ph, clk->id);
पूर्ण

अटल स्थिर काष्ठा clk_ops scmi_clk_ops = अणु
	.recalc_rate = scmi_clk_recalc_rate,
	.round_rate = scmi_clk_round_rate,
	.set_rate = scmi_clk_set_rate,
	/*
	 * We can't provide enable/disable callback as we can't perक्रमm the same
	 * in atomic context. Since the घड़ी framework provides standard API
	 * clk_prepare_enable that helps हालs using clk_enable in non-atomic
	 * context, it should be fine providing prepare/unprepare.
	 */
	.prepare = scmi_clk_enable,
	.unprepare = scmi_clk_disable,
पूर्ण;

अटल पूर्णांक scmi_clk_ops_init(काष्ठा device *dev, काष्ठा scmi_clk *sclk)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ min_rate, max_rate;

	काष्ठा clk_init_data init = अणु
		.flags = CLK_GET_RATE_NOCACHE,
		.num_parents = 0,
		.ops = &scmi_clk_ops,
		.name = sclk->info->name,
	पूर्ण;

	sclk->hw.init = &init;
	ret = devm_clk_hw_रेजिस्टर(dev, &sclk->hw);
	अगर (ret)
		वापस ret;

	अगर (sclk->info->rate_discrete) अणु
		पूर्णांक num_rates = sclk->info->list.num_rates;

		अगर (num_rates <= 0)
			वापस -EINVAL;

		min_rate = sclk->info->list.rates[0];
		max_rate = sclk->info->list.rates[num_rates - 1];
	पूर्ण अन्यथा अणु
		min_rate = sclk->info->range.min_rate;
		max_rate = sclk->info->range.max_rate;
	पूर्ण

	clk_hw_set_rate_range(&sclk->hw, min_rate, max_rate);
	वापस ret;
पूर्ण

अटल पूर्णांक scmi_घड़ीs_probe(काष्ठा scmi_device *sdev)
अणु
	पूर्णांक idx, count, err;
	काष्ठा clk_hw **hws;
	काष्ठा clk_hw_onecell_data *clk_data;
	काष्ठा device *dev = &sdev->dev;
	काष्ठा device_node *np = dev->of_node;
	स्थिर काष्ठा scmi_handle *handle = sdev->handle;
	काष्ठा scmi_protocol_handle *ph;

	अगर (!handle)
		वापस -ENODEV;

	scmi_proto_clk_ops =
		handle->devm_protocol_get(sdev, SCMI_PROTOCOL_CLOCK, &ph);
	अगर (IS_ERR(scmi_proto_clk_ops))
		वापस PTR_ERR(scmi_proto_clk_ops);

	count = scmi_proto_clk_ops->count_get(ph);
	अगर (count < 0) अणु
		dev_err(dev, "%pOFn: invalid clock output count\n", np);
		वापस -EINVAL;
	पूर्ण

	clk_data = devm_kzalloc(dev, काष्ठा_size(clk_data, hws, count),
				GFP_KERNEL);
	अगर (!clk_data)
		वापस -ENOMEM;

	clk_data->num = count;
	hws = clk_data->hws;

	क्रम (idx = 0; idx < count; idx++) अणु
		काष्ठा scmi_clk *sclk;

		sclk = devm_kzalloc(dev, माप(*sclk), GFP_KERNEL);
		अगर (!sclk)
			वापस -ENOMEM;

		sclk->info = scmi_proto_clk_ops->info_get(ph, idx);
		अगर (!sclk->info) अणु
			dev_dbg(dev, "invalid clock info for idx %d\n", idx);
			जारी;
		पूर्ण

		sclk->id = idx;
		sclk->ph = ph;

		err = scmi_clk_ops_init(dev, sclk);
		अगर (err) अणु
			dev_err(dev, "failed to register clock %d\n", idx);
			devm_kमुक्त(dev, sclk);
			hws[idx] = शून्य;
		पूर्ण अन्यथा अणु
			dev_dbg(dev, "Registered clock:%s\n", sclk->info->name);
			hws[idx] = &sclk->hw;
		पूर्ण
	पूर्ण

	वापस devm_of_clk_add_hw_provider(dev, of_clk_hw_onecell_get,
					   clk_data);
पूर्ण

अटल स्थिर काष्ठा scmi_device_id scmi_id_table[] = अणु
	अणु SCMI_PROTOCOL_CLOCK, "clocks" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(scmi, scmi_id_table);

अटल काष्ठा scmi_driver scmi_घड़ीs_driver = अणु
	.name = "scmi-clocks",
	.probe = scmi_घड़ीs_probe,
	.id_table = scmi_id_table,
पूर्ण;
module_scmi_driver(scmi_घड़ीs_driver);

MODULE_AUTHOR("Sudeep Holla <sudeep.holla@arm.com>");
MODULE_DESCRIPTION("ARM SCMI clock driver");
MODULE_LICENSE("GPL v2");
