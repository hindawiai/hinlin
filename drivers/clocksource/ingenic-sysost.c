<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Ingenic XBurst SoCs SYSOST घड़ीs driver
 * Copyright (c) 2020 ोउॉओौओ (Zhou Yanjie) <zhouyanjie@wanyeetech.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/slab.h>
#समावेश <linux/syscore_ops.h>

#समावेश <dt-bindings/घड़ी/ingenic,sysost.h>

/* OST रेजिस्टर offsets */
#घोषणा OST_REG_OSTCCR			0x00
#घोषणा OST_REG_OSTCR			0x08
#घोषणा OST_REG_OSTFR			0x0c
#घोषणा OST_REG_OSTMR			0x10
#घोषणा OST_REG_OST1DFR			0x14
#घोषणा OST_REG_OST1CNT			0x18
#घोषणा OST_REG_OST2CNTL		0x20
#घोषणा OST_REG_OSTCNT2HBUF		0x24
#घोषणा OST_REG_OSTESR			0x34
#घोषणा OST_REG_OSTECR			0x38

/* bits within the OSTCCR रेजिस्टर */
#घोषणा OSTCCR_PRESCALE1_MASK	0x3
#घोषणा OSTCCR_PRESCALE2_MASK	0xc
#घोषणा OSTCCR_PRESCALE1_LSB	0
#घोषणा OSTCCR_PRESCALE2_LSB	2

/* bits within the OSTCR रेजिस्टर */
#घोषणा OSTCR_OST1CLR			BIT(0)
#घोषणा OSTCR_OST2CLR			BIT(1)

/* bits within the OSTFR रेजिस्टर */
#घोषणा OSTFR_FFLAG				BIT(0)

/* bits within the OSTMR रेजिस्टर */
#घोषणा OSTMR_FMASK				BIT(0)

/* bits within the OSTESR रेजिस्टर */
#घोषणा OSTESR_OST1ENS			BIT(0)
#घोषणा OSTESR_OST2ENS			BIT(1)

/* bits within the OSTECR रेजिस्टर */
#घोषणा OSTECR_OST1ENC			BIT(0)
#घोषणा OSTECR_OST2ENC			BIT(1)

काष्ठा ingenic_soc_info अणु
	अचिन्हित पूर्णांक num_channels;
पूर्ण;

काष्ठा ingenic_ost_clk_info अणु
	काष्ठा clk_init_data init_data;
	u8 ostccr_reg;
पूर्ण;

काष्ठा ingenic_ost_clk अणु
	काष्ठा clk_hw hw;
	अचिन्हित पूर्णांक idx;
	काष्ठा ingenic_ost *ost;
	स्थिर काष्ठा ingenic_ost_clk_info *info;
पूर्ण;

काष्ठा ingenic_ost अणु
	व्योम __iomem *base;
	स्थिर काष्ठा ingenic_soc_info *soc_info;
	काष्ठा clk *clk, *percpu_समयr_clk, *global_समयr_clk;
	काष्ठा घड़ी_event_device cevt;
	काष्ठा घड़ीsource cs;
	अक्षर name[20];

	काष्ठा clk_hw_onecell_data *घड़ीs;
पूर्ण;

अटल काष्ठा ingenic_ost *ingenic_ost;

अटल अंतरभूत काष्ठा ingenic_ost_clk *to_ost_clk(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा ingenic_ost_clk, hw);
पूर्ण

अटल अचिन्हित दीर्घ ingenic_ost_percpu_समयr_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ingenic_ost_clk *ost_clk = to_ost_clk(hw);
	स्थिर काष्ठा ingenic_ost_clk_info *info = ost_clk->info;
	अचिन्हित पूर्णांक prescale;

	prescale = पढ़ोl(ost_clk->ost->base + info->ostccr_reg);

	prescale = (prescale & OSTCCR_PRESCALE1_MASK) >> OSTCCR_PRESCALE1_LSB;

	वापस parent_rate >> (prescale * 2);
पूर्ण

अटल अचिन्हित दीर्घ ingenic_ost_global_समयr_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ingenic_ost_clk *ost_clk = to_ost_clk(hw);
	स्थिर काष्ठा ingenic_ost_clk_info *info = ost_clk->info;
	अचिन्हित पूर्णांक prescale;

	prescale = पढ़ोl(ost_clk->ost->base + info->ostccr_reg);

	prescale = (prescale & OSTCCR_PRESCALE2_MASK) >> OSTCCR_PRESCALE2_LSB;

	वापस parent_rate >> (prescale * 2);
पूर्ण

अटल u8 ingenic_ost_get_prescale(अचिन्हित दीर्घ rate, अचिन्हित दीर्घ req_rate)
अणु
	u8 prescale;

	क्रम (prescale = 0; prescale < 2; prescale++)
		अगर ((rate >> (prescale * 2)) <= req_rate)
			वापस prescale;

	वापस 2; /* /16 भागider */
पूर्ण

अटल दीर्घ ingenic_ost_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ req_rate,
		अचिन्हित दीर्घ *parent_rate)
अणु
	अचिन्हित दीर्घ rate = *parent_rate;
	u8 prescale;

	अगर (req_rate > rate)
		वापस rate;

	prescale = ingenic_ost_get_prescale(rate, req_rate);

	वापस rate >> (prescale * 2);
पूर्ण

अटल पूर्णांक ingenic_ost_percpu_समयr_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ req_rate,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ingenic_ost_clk *ost_clk = to_ost_clk(hw);
	स्थिर काष्ठा ingenic_ost_clk_info *info = ost_clk->info;
	u8 prescale = ingenic_ost_get_prescale(parent_rate, req_rate);
	पूर्णांक val;

	val = पढ़ोl(ost_clk->ost->base + info->ostccr_reg);
	val = (val & ~OSTCCR_PRESCALE1_MASK) | (prescale << OSTCCR_PRESCALE1_LSB);
	ग_लिखोl(val, ost_clk->ost->base + info->ostccr_reg);

	वापस 0;
पूर्ण

अटल पूर्णांक ingenic_ost_global_समयr_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ req_rate,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ingenic_ost_clk *ost_clk = to_ost_clk(hw);
	स्थिर काष्ठा ingenic_ost_clk_info *info = ost_clk->info;
	u8 prescale = ingenic_ost_get_prescale(parent_rate, req_rate);
	पूर्णांक val;

	val = पढ़ोl(ost_clk->ost->base + info->ostccr_reg);
	val = (val & ~OSTCCR_PRESCALE2_MASK) | (prescale << OSTCCR_PRESCALE2_LSB);
	ग_लिखोl(val, ost_clk->ost->base + info->ostccr_reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops ingenic_ost_percpu_समयr_ops = अणु
	.recalc_rate	= ingenic_ost_percpu_समयr_recalc_rate,
	.round_rate		= ingenic_ost_round_rate,
	.set_rate		= ingenic_ost_percpu_समयr_set_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops ingenic_ost_global_समयr_ops = अणु
	.recalc_rate	= ingenic_ost_global_समयr_recalc_rate,
	.round_rate		= ingenic_ost_round_rate,
	.set_rate		= ingenic_ost_global_समयr_set_rate,
पूर्ण;

अटल स्थिर अक्षर * स्थिर ingenic_ost_clk_parents[] = अणु "ext" पूर्ण;

अटल स्थिर काष्ठा ingenic_ost_clk_info ingenic_ost_clk_info[] = अणु
	[OST_CLK_PERCPU_TIMER] = अणु
		.init_data = अणु
			.name = "percpu timer",
			.parent_names = ingenic_ost_clk_parents,
			.num_parents = ARRAY_SIZE(ingenic_ost_clk_parents),
			.ops = &ingenic_ost_percpu_समयr_ops,
			.flags = CLK_SET_RATE_UNGATE,
		पूर्ण,
		.ostccr_reg = OST_REG_OSTCCR,
	पूर्ण,

	[OST_CLK_GLOBAL_TIMER] = अणु
		.init_data = अणु
			.name = "global timer",
			.parent_names = ingenic_ost_clk_parents,
			.num_parents = ARRAY_SIZE(ingenic_ost_clk_parents),
			.ops = &ingenic_ost_global_समयr_ops,
			.flags = CLK_SET_RATE_UNGATE,
		पूर्ण,
		.ostccr_reg = OST_REG_OSTCCR,
	पूर्ण,
पूर्ण;

अटल u64 notrace ingenic_ost_global_समयr_पढ़ो_cntl(व्योम)
अणु
	काष्ठा ingenic_ost *ost = ingenic_ost;
	अचिन्हित पूर्णांक count;

	count = पढ़ोl(ost->base + OST_REG_OST2CNTL);

	वापस count;
पूर्ण

अटल u64 notrace ingenic_ost_घड़ीsource_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	वापस ingenic_ost_global_समयr_पढ़ो_cntl();
पूर्ण

अटल अंतरभूत काष्ठा ingenic_ost *to_ingenic_ost(काष्ठा घड़ी_event_device *evt)
अणु
	वापस container_of(evt, काष्ठा ingenic_ost, cevt);
पूर्ण

अटल पूर्णांक ingenic_ost_cevt_set_state_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा ingenic_ost *ost = to_ingenic_ost(evt);

	ग_लिखोl(OSTECR_OST1ENC, ost->base + OST_REG_OSTECR);

	वापस 0;
पूर्ण

अटल पूर्णांक ingenic_ost_cevt_set_next(अचिन्हित दीर्घ next,
				     काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा ingenic_ost *ost = to_ingenic_ost(evt);

	ग_लिखोl((u32)~OSTFR_FFLAG, ost->base + OST_REG_OSTFR);
	ग_लिखोl(next, ost->base + OST_REG_OST1DFR);
	ग_लिखोl(OSTCR_OST1CLR, ost->base + OST_REG_OSTCR);
	ग_लिखोl(OSTESR_OST1ENS, ost->base + OST_REG_OSTESR);
	ग_लिखोl((u32)~OSTMR_FMASK, ost->base + OST_REG_OSTMR);

	वापस 0;
पूर्ण

अटल irqवापस_t ingenic_ost_cevt_cb(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = dev_id;
	काष्ठा ingenic_ost *ost = to_ingenic_ost(evt);

	ग_लिखोl(OSTECR_OST1ENC, ost->base + OST_REG_OSTECR);

	अगर (evt->event_handler)
		evt->event_handler(evt);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init ingenic_ost_रेजिस्टर_घड़ी(काष्ठा ingenic_ost *ost,
			अचिन्हित पूर्णांक idx, स्थिर काष्ठा ingenic_ost_clk_info *info,
			काष्ठा clk_hw_onecell_data *घड़ीs)
अणु
	काष्ठा ingenic_ost_clk *ost_clk;
	पूर्णांक val, err;

	ost_clk = kzalloc(माप(*ost_clk), GFP_KERNEL);
	अगर (!ost_clk)
		वापस -ENOMEM;

	ost_clk->hw.init = &info->init_data;
	ost_clk->idx = idx;
	ost_clk->info = info;
	ost_clk->ost = ost;

	/* Reset घड़ी भागider */
	val = पढ़ोl(ost->base + info->ostccr_reg);
	val &= ~(OSTCCR_PRESCALE1_MASK | OSTCCR_PRESCALE2_MASK);
	ग_लिखोl(val, ost->base + info->ostccr_reg);

	err = clk_hw_रेजिस्टर(शून्य, &ost_clk->hw);
	अगर (err) अणु
		kमुक्त(ost_clk);
		वापस err;
	पूर्ण

	घड़ीs->hws[idx] = &ost_clk->hw;

	वापस 0;
पूर्ण

अटल काष्ठा clk * __init ingenic_ost_get_घड़ी(काष्ठा device_node *np, पूर्णांक id)
अणु
	काष्ठा of_phandle_args args;

	args.np = np;
	args.args_count = 1;
	args.args[0] = id;

	वापस of_clk_get_from_provider(&args);
पूर्ण

अटल पूर्णांक __init ingenic_ost_percpu_समयr_init(काष्ठा device_node *np,
					 काष्ठा ingenic_ost *ost)
अणु
	अचिन्हित पूर्णांक समयr_virq, channel = OST_CLK_PERCPU_TIMER;
	अचिन्हित दीर्घ rate;
	पूर्णांक err;

	ost->percpu_समयr_clk = ingenic_ost_get_घड़ी(np, channel);
	अगर (IS_ERR(ost->percpu_समयr_clk))
		वापस PTR_ERR(ost->percpu_समयr_clk);

	err = clk_prepare_enable(ost->percpu_समयr_clk);
	अगर (err)
		जाओ err_clk_put;

	rate = clk_get_rate(ost->percpu_समयr_clk);
	अगर (!rate) अणु
		err = -EINVAL;
		जाओ err_clk_disable;
	पूर्ण

	समयr_virq = of_irq_get(np, 0);
	अगर (!समयr_virq) अणु
		err = -EINVAL;
		जाओ err_clk_disable;
	पूर्ण

	snम_लिखो(ost->name, माप(ost->name), "OST percpu timer");

	err = request_irq(समयr_virq, ingenic_ost_cevt_cb, IRQF_TIMER,
			  ost->name, &ost->cevt);
	अगर (err)
		जाओ err_irq_dispose_mapping;

	ost->cevt.cpumask = cpumask_of(smp_processor_id());
	ost->cevt.features = CLOCK_EVT_FEAT_ONESHOT;
	ost->cevt.name = ost->name;
	ost->cevt.rating = 400;
	ost->cevt.set_state_shutकरोwn = ingenic_ost_cevt_set_state_shutकरोwn;
	ost->cevt.set_next_event = ingenic_ost_cevt_set_next;

	घड़ीevents_config_and_रेजिस्टर(&ost->cevt, rate, 4, 0xffffffff);

	वापस 0;

err_irq_dispose_mapping:
	irq_dispose_mapping(समयr_virq);
err_clk_disable:
	clk_disable_unprepare(ost->percpu_समयr_clk);
err_clk_put:
	clk_put(ost->percpu_समयr_clk);
	वापस err;
पूर्ण

अटल पूर्णांक __init ingenic_ost_global_समयr_init(काष्ठा device_node *np,
					       काष्ठा ingenic_ost *ost)
अणु
	अचिन्हित पूर्णांक channel = OST_CLK_GLOBAL_TIMER;
	काष्ठा घड़ीsource *cs = &ost->cs;
	अचिन्हित दीर्घ rate;
	पूर्णांक err;

	ost->global_समयr_clk = ingenic_ost_get_घड़ी(np, channel);
	अगर (IS_ERR(ost->global_समयr_clk))
		वापस PTR_ERR(ost->global_समयr_clk);

	err = clk_prepare_enable(ost->global_समयr_clk);
	अगर (err)
		जाओ err_clk_put;

	rate = clk_get_rate(ost->global_समयr_clk);
	अगर (!rate) अणु
		err = -EINVAL;
		जाओ err_clk_disable;
	पूर्ण

	/* Clear counter CNT रेजिस्टरs */
	ग_लिखोl(OSTCR_OST2CLR, ost->base + OST_REG_OSTCR);

	/* Enable OST channel */
	ग_लिखोl(OSTESR_OST2ENS, ost->base + OST_REG_OSTESR);

	cs->name = "ingenic-ost";
	cs->rating = 400;
	cs->flags = CLOCK_SOURCE_IS_CONTINUOUS;
	cs->mask = CLOCKSOURCE_MASK(32);
	cs->पढ़ो = ingenic_ost_घड़ीsource_पढ़ो;

	err = घड़ीsource_रेजिस्टर_hz(cs, rate);
	अगर (err)
		जाओ err_clk_disable;

	वापस 0;

err_clk_disable:
	clk_disable_unprepare(ost->global_समयr_clk);
err_clk_put:
	clk_put(ost->global_समयr_clk);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा ingenic_soc_info x1000_soc_info = अणु
	.num_channels = 2,
पूर्ण;

अटल स्थिर काष्ठा of_device_id __maybe_unused ingenic_ost_of_match[] __initस्थिर = अणु
	अणु .compatible = "ingenic,x1000-ost", .data = &x1000_soc_info, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक __init ingenic_ost_probe(काष्ठा device_node *np)
अणु
	स्थिर काष्ठा of_device_id *id = of_match_node(ingenic_ost_of_match, np);
	काष्ठा ingenic_ost *ost;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ost = kzalloc(माप(*ost), GFP_KERNEL);
	अगर (!ost)
		वापस -ENOMEM;

	ost->base = of_io_request_and_map(np, 0, of_node_full_name(np));
	अगर (IS_ERR(ost->base)) अणु
		pr_err("%s: Failed to map OST registers\n", __func__);
		ret = PTR_ERR(ost->base);
		जाओ err_मुक्त_ost;
	पूर्ण

	ost->clk = of_clk_get_by_name(np, "ost");
	अगर (IS_ERR(ost->clk)) अणु
		ret = PTR_ERR(ost->clk);
		pr_crit("%s: Cannot get OST clock\n", __func__);
		जाओ err_मुक्त_ost;
	पूर्ण

	ret = clk_prepare_enable(ost->clk);
	अगर (ret) अणु
		pr_crit("%s: Unable to enable OST clock\n", __func__);
		जाओ err_put_clk;
	पूर्ण

	ost->soc_info = id->data;

	ost->घड़ीs = kzalloc(काष्ठा_size(ost->घड़ीs, hws, ost->soc_info->num_channels),
			      GFP_KERNEL);
	अगर (!ost->घड़ीs) अणु
		ret = -ENOMEM;
		जाओ err_clk_disable;
	पूर्ण

	ost->घड़ीs->num = ost->soc_info->num_channels;

	क्रम (i = 0; i < ost->घड़ीs->num; i++) अणु
		ret = ingenic_ost_रेजिस्टर_घड़ी(ost, i, &ingenic_ost_clk_info[i], ost->घड़ीs);
		अगर (ret) अणु
			pr_crit("%s: Cannot register clock %d\n", __func__, i);
			जाओ err_unरेजिस्टर_ost_घड़ीs;
		पूर्ण
	पूर्ण

	ret = of_clk_add_hw_provider(np, of_clk_hw_onecell_get, ost->घड़ीs);
	अगर (ret) अणु
		pr_crit("%s: Cannot add OF clock provider\n", __func__);
		जाओ err_unरेजिस्टर_ost_घड़ीs;
	पूर्ण

	ingenic_ost = ost;

	वापस 0;

err_unरेजिस्टर_ost_घड़ीs:
	क्रम (i = 0; i < ost->घड़ीs->num; i++)
		अगर (ost->घड़ीs->hws[i])
			clk_hw_unरेजिस्टर(ost->घड़ीs->hws[i]);
	kमुक्त(ost->घड़ीs);
err_clk_disable:
	clk_disable_unprepare(ost->clk);
err_put_clk:
	clk_put(ost->clk);
err_मुक्त_ost:
	kमुक्त(ost);
	वापस ret;
पूर्ण

अटल पूर्णांक __init ingenic_ost_init(काष्ठा device_node *np)
अणु
	काष्ठा ingenic_ost *ost;
	अचिन्हित दीर्घ rate;
	पूर्णांक ret;

	ret = ingenic_ost_probe(np);
	अगर (ret) अणु
		pr_crit("%s: Failed to initialize OST clocks: %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	of_node_clear_flag(np, OF_POPULATED);

	ost = ingenic_ost;
	अगर (IS_ERR(ost))
		वापस PTR_ERR(ost);

	ret = ingenic_ost_global_समयr_init(np, ost);
	अगर (ret) अणु
		pr_crit("%s: Unable to init global timer: %x\n", __func__, ret);
		जाओ err_मुक्त_ingenic_ost;
	पूर्ण

	ret = ingenic_ost_percpu_समयr_init(np, ost);
	अगर (ret)
		जाओ err_ost_global_समयr_cleanup;

	/* Register the sched_घड़ी at the end as there's no way to unकरो it */
	rate = clk_get_rate(ost->global_समयr_clk);
	sched_घड़ी_रेजिस्टर(ingenic_ost_global_समयr_पढ़ो_cntl, 32, rate);

	वापस 0;

err_ost_global_समयr_cleanup:
	घड़ीsource_unरेजिस्टर(&ost->cs);
	clk_disable_unprepare(ost->global_समयr_clk);
	clk_put(ost->global_समयr_clk);
err_मुक्त_ingenic_ost:
	kमुक्त(ost);
	वापस ret;
पूर्ण

TIMER_OF_DECLARE(x1000_ost,  "ingenic,x1000-ost",  ingenic_ost_init);
