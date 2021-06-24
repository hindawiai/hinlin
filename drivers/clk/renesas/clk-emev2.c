<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * EMMA Mobile EV2 common घड़ी framework support
 *
 * Copyright (C) 2013 Takashi Yoshii <takashi.yoshii.ze@renesas.com>
 * Copyright (C) 2012 Magnus Damm
 */
#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

/* EMEV2 SMU रेजिस्टरs */
#घोषणा USIAU0_RSTCTRL 0x094
#घोषणा USIBU1_RSTCTRL 0x0ac
#घोषणा USIBU2_RSTCTRL 0x0b0
#घोषणा USIBU3_RSTCTRL 0x0b4
#घोषणा IIC0_RSTCTRL 0x0dc
#घोषणा IIC1_RSTCTRL 0x0e0
#घोषणा STI_RSTCTRL 0x124
#घोषणा STI_CLKSEL 0x688

अटल DEFINE_SPINLOCK(lock);

/* not pretty, but hey */
अटल व्योम __iomem *smu_base;

अटल व्योम __init emev2_smu_ग_लिखो(अचिन्हित दीर्घ value, पूर्णांक offs)
अणु
	BUG_ON(!smu_base || (offs >= PAGE_SIZE));
	ग_लिखोl_relaxed(value, smu_base + offs);
पूर्ण

अटल स्थिर काष्ठा of_device_id smu_id[] __initस्थिर = अणु
	अणु .compatible = "renesas,emev2-smu", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल व्योम __init emev2_smu_init(व्योम)
अणु
	काष्ठा device_node *np;

	np = of_find_matching_node(शून्य, smu_id);
	BUG_ON(!np);
	smu_base = of_iomap(np, 0);
	BUG_ON(!smu_base);
	of_node_put(np);

	/* setup STI समयr to run on 32.768 kHz and deनिश्चित reset */
	emev2_smu_ग_लिखो(0, STI_CLKSEL);
	emev2_smu_ग_लिखो(1, STI_RSTCTRL);

	/* deनिश्चित reset क्रम UART0->UART3 */
	emev2_smu_ग_लिखो(2, USIAU0_RSTCTRL);
	emev2_smu_ग_लिखो(2, USIBU1_RSTCTRL);
	emev2_smu_ग_लिखो(2, USIBU2_RSTCTRL);
	emev2_smu_ग_लिखो(2, USIBU3_RSTCTRL);

	/* deनिश्चित reset क्रम IIC0->IIC1 */
	emev2_smu_ग_लिखो(1, IIC0_RSTCTRL);
	emev2_smu_ग_लिखो(1, IIC1_RSTCTRL);
पूर्ण

अटल व्योम __init emev2_smu_clkभाग_init(काष्ठा device_node *np)
अणु
	u32 reg[2];
	काष्ठा clk *clk;
	स्थिर अक्षर *parent_name = of_clk_get_parent_name(np, 0);
	अगर (WARN_ON(of_property_पढ़ो_u32_array(np, "reg", reg, 2)))
		वापस;
	अगर (!smu_base)
		emev2_smu_init();
	clk = clk_रेजिस्टर_भागider(शून्य, np->name, parent_name, 0,
				   smu_base + reg[0], reg[1], 8, 0, &lock);
	of_clk_add_provider(np, of_clk_src_simple_get, clk);
	clk_रेजिस्टर_clkdev(clk, np->full_name, शून्य);
	pr_debug("## %s %pOFn %p\n", __func__, np, clk);
पूर्ण
CLK_OF_DECLARE(emev2_smu_clkभाग, "renesas,emev2-smu-clkdiv",
		emev2_smu_clkभाग_init);

अटल व्योम __init emev2_smu_gclk_init(काष्ठा device_node *np)
अणु
	u32 reg[2];
	काष्ठा clk *clk;
	स्थिर अक्षर *parent_name = of_clk_get_parent_name(np, 0);
	अगर (WARN_ON(of_property_पढ़ो_u32_array(np, "reg", reg, 2)))
		वापस;
	अगर (!smu_base)
		emev2_smu_init();
	clk = clk_रेजिस्टर_gate(शून्य, np->name, parent_name, 0,
				smu_base + reg[0], reg[1], 0, &lock);
	of_clk_add_provider(np, of_clk_src_simple_get, clk);
	clk_रेजिस्टर_clkdev(clk, np->full_name, शून्य);
	pr_debug("## %s %pOFn %p\n", __func__, np, clk);
पूर्ण
CLK_OF_DECLARE(emev2_smu_gclk, "renesas,emev2-smu-gclk", emev2_smu_gclk_init);
