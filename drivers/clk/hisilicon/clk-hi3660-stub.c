<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hisilicon घड़ी driver
 *
 * Copyright (c) 2013-2017 Hisilicon Limited.
 * Copyright (c) 2017 Linaro Limited.
 *
 * Author: Kai Zhao <zhaokai1@hisilicon.com>
 *	    Tao Wang <kevin.wangtao@hisilicon.com>
 *	    Leo Yan <leo.yan@linaro.org>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/mailbox_client.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <dt-bindings/घड़ी/hi3660-घड़ी.h>

#घोषणा HI3660_STUB_CLOCK_DATA		(0x70)
#घोषणा MHZ				(1000 * 1000)

#घोषणा DEFINE_CLK_STUB(_id, _cmd, _name)			\
	अणु							\
		.id = (_id),					\
		.cmd = (_cmd),					\
		.hw.init = &(काष्ठा clk_init_data) अणु		\
			.name = #_name,				\
			.ops = &hi3660_stub_clk_ops,		\
			.num_parents = 0,			\
			.flags = CLK_GET_RATE_NOCACHE,		\
		पूर्ण,						\
	पूर्ण,

#घोषणा to_stub_clk(_hw) container_of(_hw, काष्ठा hi3660_stub_clk, hw)

काष्ठा hi3660_stub_clk_chan अणु
	काष्ठा mbox_client cl;
	काष्ठा mbox_chan *mbox;
पूर्ण;

काष्ठा hi3660_stub_clk अणु
	अचिन्हित पूर्णांक id;
	काष्ठा clk_hw hw;
	अचिन्हित पूर्णांक cmd;
	अचिन्हित पूर्णांक msg[8];
	अचिन्हित पूर्णांक rate;
पूर्ण;

अटल व्योम __iomem *freq_reg;
अटल काष्ठा hi3660_stub_clk_chan stub_clk_chan;

अटल अचिन्हित दीर्घ hi3660_stub_clk_recalc_rate(काष्ठा clk_hw *hw,
						 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा hi3660_stub_clk *stub_clk = to_stub_clk(hw);

	/*
	 * LPM3 ग_लिखोs back the CPU frequency in shared SRAM so पढ़ो
	 * back the frequency.
	 */
	stub_clk->rate = पढ़ोl(freq_reg + (stub_clk->id << 2)) * MHZ;
	वापस stub_clk->rate;
पूर्ण

अटल दीर्घ hi3660_stub_clk_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				       अचिन्हित दीर्घ *prate)
अणु
	/*
	 * LPM3 handles rate rounding so just वापस whatever
	 * rate is requested.
	 */
	वापस rate;
पूर्ण

अटल पूर्णांक hi3660_stub_clk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा hi3660_stub_clk *stub_clk = to_stub_clk(hw);

	stub_clk->msg[0] = stub_clk->cmd;
	stub_clk->msg[1] = rate / MHZ;

	dev_dbg(stub_clk_chan.cl.dev, "set rate msg[0]=0x%x msg[1]=0x%x\n",
		stub_clk->msg[0], stub_clk->msg[1]);

	mbox_send_message(stub_clk_chan.mbox, stub_clk->msg);
	mbox_client_txकरोne(stub_clk_chan.mbox, 0);

	stub_clk->rate = rate;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops hi3660_stub_clk_ops = अणु
	.recalc_rate    = hi3660_stub_clk_recalc_rate,
	.round_rate     = hi3660_stub_clk_round_rate,
	.set_rate       = hi3660_stub_clk_set_rate,
पूर्ण;

अटल काष्ठा hi3660_stub_clk hi3660_stub_clks[HI3660_CLK_STUB_NUM] = अणु
	DEFINE_CLK_STUB(HI3660_CLK_STUB_CLUSTER0, 0x0001030A, "cpu-cluster.0")
	DEFINE_CLK_STUB(HI3660_CLK_STUB_CLUSTER1, 0x0002030A, "cpu-cluster.1")
	DEFINE_CLK_STUB(HI3660_CLK_STUB_GPU, 0x0003030A, "clk-g3d")
	DEFINE_CLK_STUB(HI3660_CLK_STUB_DDR, 0x00040309, "clk-ddrc")
पूर्ण;

अटल काष्ठा clk_hw *hi3660_stub_clk_hw_get(काष्ठा of_phandle_args *clkspec,
					     व्योम *data)
अणु
	अचिन्हित पूर्णांक idx = clkspec->args[0];

	अगर (idx >= HI3660_CLK_STUB_NUM) अणु
		pr_err("%s: invalid index %u\n", __func__, idx);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस &hi3660_stub_clks[idx].hw;
पूर्ण

अटल पूर्णांक hi3660_stub_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/* Use mailbox client without blocking */
	stub_clk_chan.cl.dev = dev;
	stub_clk_chan.cl.tx_करोne = शून्य;
	stub_clk_chan.cl.tx_block = false;
	stub_clk_chan.cl.knows_txकरोne = false;

	/* Allocate mailbox channel */
	stub_clk_chan.mbox = mbox_request_channel(&stub_clk_chan.cl, 0);
	अगर (IS_ERR(stub_clk_chan.mbox))
		वापस PTR_ERR(stub_clk_chan.mbox);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -EINVAL;
	freq_reg = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!freq_reg)
		वापस -ENOMEM;

	freq_reg += HI3660_STUB_CLOCK_DATA;

	क्रम (i = 0; i < HI3660_CLK_STUB_NUM; i++) अणु
		ret = devm_clk_hw_रेजिस्टर(&pdev->dev, &hi3660_stub_clks[i].hw);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस devm_of_clk_add_hw_provider(&pdev->dev, hi3660_stub_clk_hw_get,
					   hi3660_stub_clks);
पूर्ण

अटल स्थिर काष्ठा of_device_id hi3660_stub_clk_of_match[] = अणु
	अणु .compatible = "hisilicon,hi3660-stub-clk", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver hi3660_stub_clk_driver = अणु
	.probe	= hi3660_stub_clk_probe,
	.driver = अणु
		.name = "hi3660-stub-clk",
		.of_match_table = hi3660_stub_clk_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init hi3660_stub_clk_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&hi3660_stub_clk_driver);
पूर्ण
subsys_initcall(hi3660_stub_clk_init);
