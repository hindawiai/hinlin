<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Hi6220 stub घड़ी driver
 *
 * Copyright (c) 2015 Hisilicon Limited.
 * Copyright (c) 2015 Linaro Limited.
 *
 * Author: Leo Yan <leo.yan@linaro.org>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mailbox_client.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>

/* Stub घड़ीs id */
#घोषणा HI6220_STUB_ACPU0		0
#घोषणा HI6220_STUB_ACPU1		1
#घोषणा HI6220_STUB_GPU			2
#घोषणा HI6220_STUB_DDR			5

/* Mailbox message */
#घोषणा HI6220_MBOX_MSG_LEN		8

#घोषणा HI6220_MBOX_FREQ		0xA
#घोषणा HI6220_MBOX_CMD_SET		0x3
#घोषणा HI6220_MBOX_OBJ_AP		0x0

/* CPU dynamic frequency scaling */
#घोषणा ACPU_DFS_FREQ_MAX		0x1724
#घोषणा ACPU_DFS_CUR_FREQ		0x17CC
#घोषणा ACPU_DFS_FLAG			0x1B30
#घोषणा ACPU_DFS_FREQ_REQ		0x1B34
#घोषणा ACPU_DFS_FREQ_LMT		0x1B38
#घोषणा ACPU_DFS_LOCK_FLAG		0xAEAEAEAE

#घोषणा to_stub_clk(hw) container_of(hw, काष्ठा hi6220_stub_clk, hw)

काष्ठा hi6220_stub_clk अणु
	u32 id;

	काष्ठा device *dev;
	काष्ठा clk_hw hw;

	काष्ठा regmap *dfs_map;
	काष्ठा mbox_client cl;
	काष्ठा mbox_chan *mbox;
पूर्ण;

काष्ठा hi6220_mbox_msg अणु
	अचिन्हित अक्षर type;
	अचिन्हित अक्षर cmd;
	अचिन्हित अक्षर obj;
	अचिन्हित अक्षर src;
	अचिन्हित अक्षर para[4];
पूर्ण;

जोड़ hi6220_mbox_data अणु
	अचिन्हित पूर्णांक data[HI6220_MBOX_MSG_LEN];
	काष्ठा hi6220_mbox_msg msg;
पूर्ण;

अटल अचिन्हित पूर्णांक hi6220_acpu_get_freq(काष्ठा hi6220_stub_clk *stub_clk)
अणु
	अचिन्हित पूर्णांक freq;

	regmap_पढ़ो(stub_clk->dfs_map, ACPU_DFS_CUR_FREQ, &freq);
	वापस freq;
पूर्ण

अटल पूर्णांक hi6220_acpu_set_freq(काष्ठा hi6220_stub_clk *stub_clk,
				अचिन्हित पूर्णांक freq)
अणु
	जोड़ hi6220_mbox_data data;

	/* set the frequency in sram */
	regmap_ग_लिखो(stub_clk->dfs_map, ACPU_DFS_FREQ_REQ, freq);

	/* compound mailbox message */
	data.msg.type = HI6220_MBOX_FREQ;
	data.msg.cmd  = HI6220_MBOX_CMD_SET;
	data.msg.obj  = HI6220_MBOX_OBJ_AP;
	data.msg.src  = HI6220_MBOX_OBJ_AP;

	mbox_send_message(stub_clk->mbox, &data);
	वापस 0;
पूर्ण

अटल पूर्णांक hi6220_acpu_round_freq(काष्ठा hi6220_stub_clk *stub_clk,
				  अचिन्हित पूर्णांक freq)
अणु
	अचिन्हित पूर्णांक limit_flag, limit_freq = अच_पूर्णांक_उच्च;
	अचिन्हित पूर्णांक max_freq;

	/* check the स्थिरrained frequency */
	regmap_पढ़ो(stub_clk->dfs_map, ACPU_DFS_FLAG, &limit_flag);
	अगर (limit_flag == ACPU_DFS_LOCK_FLAG)
		regmap_पढ़ो(stub_clk->dfs_map, ACPU_DFS_FREQ_LMT, &limit_freq);

	/* check the supported maximum frequency */
	regmap_पढ़ो(stub_clk->dfs_map, ACPU_DFS_FREQ_MAX, &max_freq);

	/* calculate the real maximum frequency */
	max_freq = min(max_freq, limit_freq);

	अगर (WARN_ON(freq > max_freq))
		freq = max_freq;

	वापस freq;
पूर्ण

अटल अचिन्हित दीर्घ hi6220_stub_clk_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	u32 rate = 0;
	काष्ठा hi6220_stub_clk *stub_clk = to_stub_clk(hw);

	चयन (stub_clk->id) अणु
	हाल HI6220_STUB_ACPU0:
		rate = hi6220_acpu_get_freq(stub_clk);

		/* convert from kHz to Hz */
		rate *= 1000;
		अवरोध;

	शेष:
		dev_err(stub_clk->dev, "%s: un-supported clock id %d\n",
			__func__, stub_clk->id);
		अवरोध;
	पूर्ण

	वापस rate;
पूर्ण

अटल पूर्णांक hi6220_stub_clk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा hi6220_stub_clk *stub_clk = to_stub_clk(hw);
	अचिन्हित दीर्घ new_rate = rate / 1000;  /* kHz */
	पूर्णांक ret = 0;

	चयन (stub_clk->id) अणु
	हाल HI6220_STUB_ACPU0:
		ret = hi6220_acpu_set_freq(stub_clk, new_rate);
		अगर (ret < 0)
			वापस ret;

		अवरोध;

	शेष:
		dev_err(stub_clk->dev, "%s: un-supported clock id %d\n",
			__func__, stub_clk->id);
		अवरोध;
	पूर्ण

	pr_debug("%s: set rate=%ldkHz\n", __func__, new_rate);
	वापस ret;
पूर्ण

अटल दीर्घ hi6220_stub_clk_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा hi6220_stub_clk *stub_clk = to_stub_clk(hw);
	अचिन्हित दीर्घ new_rate = rate / 1000;  /* kHz */

	चयन (stub_clk->id) अणु
	हाल HI6220_STUB_ACPU0:
		new_rate = hi6220_acpu_round_freq(stub_clk, new_rate);

		/* convert from kHz to Hz */
		new_rate *= 1000;
		अवरोध;

	शेष:
		dev_err(stub_clk->dev, "%s: un-supported clock id %d\n",
			__func__, stub_clk->id);
		अवरोध;
	पूर्ण

	वापस new_rate;
पूर्ण

अटल स्थिर काष्ठा clk_ops hi6220_stub_clk_ops = अणु
	.recalc_rate	= hi6220_stub_clk_recalc_rate,
	.round_rate	= hi6220_stub_clk_round_rate,
	.set_rate	= hi6220_stub_clk_set_rate,
पूर्ण;

अटल पूर्णांक hi6220_stub_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा clk_init_data init;
	काष्ठा hi6220_stub_clk *stub_clk;
	काष्ठा clk *clk;
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक ret;

	stub_clk = devm_kzalloc(dev, माप(*stub_clk), GFP_KERNEL);
	अगर (!stub_clk)
		वापस -ENOMEM;

	stub_clk->dfs_map = syscon_regmap_lookup_by_phandle(np,
				"hisilicon,hi6220-clk-sram");
	अगर (IS_ERR(stub_clk->dfs_map)) अणु
		dev_err(dev, "failed to get sram regmap\n");
		वापस PTR_ERR(stub_clk->dfs_map);
	पूर्ण

	stub_clk->hw.init = &init;
	stub_clk->dev = dev;
	stub_clk->id = HI6220_STUB_ACPU0;

	/* Use mailbox client with blocking mode */
	stub_clk->cl.dev = dev;
	stub_clk->cl.tx_करोne = शून्य;
	stub_clk->cl.tx_block = true;
	stub_clk->cl.tx_tout = 500;
	stub_clk->cl.knows_txकरोne = false;

	/* Allocate mailbox channel */
	stub_clk->mbox = mbox_request_channel(&stub_clk->cl, 0);
	अगर (IS_ERR(stub_clk->mbox)) अणु
		dev_err(dev, "failed get mailbox channel\n");
		वापस PTR_ERR(stub_clk->mbox);
	पूर्ण

	init.name = "acpu0";
	init.ops = &hi6220_stub_clk_ops;
	init.num_parents = 0;
	init.flags = 0;

	clk = devm_clk_रेजिस्टर(dev, &stub_clk->hw);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	ret = of_clk_add_provider(np, of_clk_src_simple_get, clk);
	अगर (ret) अणु
		dev_err(dev, "failed to register OF clock provider\n");
		वापस ret;
	पूर्ण

	/* initialize buffer to zero */
	regmap_ग_लिखो(stub_clk->dfs_map, ACPU_DFS_FLAG, 0x0);
	regmap_ग_लिखो(stub_clk->dfs_map, ACPU_DFS_FREQ_REQ, 0x0);
	regmap_ग_लिखो(stub_clk->dfs_map, ACPU_DFS_FREQ_LMT, 0x0);

	dev_dbg(dev, "Registered clock '%s'\n", init.name);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id hi6220_stub_clk_of_match[] = अणु
	अणु .compatible = "hisilicon,hi6220-stub-clk", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver hi6220_stub_clk_driver = अणु
	.driver	= अणु
		.name = "hi6220-stub-clk",
		.of_match_table = hi6220_stub_clk_of_match,
	पूर्ण,
	.probe = hi6220_stub_clk_probe,
पूर्ण;

अटल पूर्णांक __init hi6220_stub_clk_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&hi6220_stub_clk_driver);
पूर्ण
subsys_initcall(hi6220_stub_clk_init);
