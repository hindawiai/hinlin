<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Ingenic SoCs TCU IRQ driver
 * Copyright (C) 2019 Paul Cercueil <paul@crapouillou.net>
 * Copyright (C) 2020 ोउॉओौओ (Zhou Yanjie) <zhouyanjie@wanyeetech.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/ingenic-tcu.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/overflow.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/sched_घड़ी.h>

#समावेश <dt-bindings/घड़ी/ingenic,tcu.h>

अटल DEFINE_PER_CPU(call_single_data_t, ingenic_cevt_csd);

काष्ठा ingenic_soc_info अणु
	अचिन्हित पूर्णांक num_channels;
पूर्ण;

काष्ठा ingenic_tcu_समयr अणु
	अचिन्हित पूर्णांक cpu;
	अचिन्हित पूर्णांक channel;
	काष्ठा घड़ी_event_device cevt;
	काष्ठा clk *clk;
	अक्षर name[8];
पूर्ण;

काष्ठा ingenic_tcu अणु
	काष्ठा regmap *map;
	काष्ठा device_node *np;
	काष्ठा clk *cs_clk;
	अचिन्हित पूर्णांक cs_channel;
	काष्ठा घड़ीsource cs;
	अचिन्हित दीर्घ pwm_channels_mask;
	काष्ठा ingenic_tcu_समयr समयrs[];
पूर्ण;

अटल काष्ठा ingenic_tcu *ingenic_tcu;

अटल u64 notrace ingenic_tcu_समयr_पढ़ो(व्योम)
अणु
	काष्ठा ingenic_tcu *tcu = ingenic_tcu;
	अचिन्हित पूर्णांक count;

	regmap_पढ़ो(tcu->map, TCU_REG_TCNTc(tcu->cs_channel), &count);

	वापस count;
पूर्ण

अटल u64 notrace ingenic_tcu_समयr_cs_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	वापस ingenic_tcu_समयr_पढ़ो();
पूर्ण

अटल अंतरभूत काष्ठा ingenic_tcu *
to_ingenic_tcu(काष्ठा ingenic_tcu_समयr *समयr)
अणु
	वापस container_of(समयr, काष्ठा ingenic_tcu, समयrs[समयr->cpu]);
पूर्ण

अटल अंतरभूत काष्ठा ingenic_tcu_समयr *
to_ingenic_tcu_समयr(काष्ठा घड़ी_event_device *evt)
अणु
	वापस container_of(evt, काष्ठा ingenic_tcu_समयr, cevt);
पूर्ण

अटल पूर्णांक ingenic_tcu_cevt_set_state_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा ingenic_tcu_समयr *समयr = to_ingenic_tcu_समयr(evt);
	काष्ठा ingenic_tcu *tcu = to_ingenic_tcu(समयr);

	regmap_ग_लिखो(tcu->map, TCU_REG_TECR, BIT(समयr->channel));

	वापस 0;
पूर्ण

अटल पूर्णांक ingenic_tcu_cevt_set_next(अचिन्हित दीर्घ next,
				     काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा ingenic_tcu_समयr *समयr = to_ingenic_tcu_समयr(evt);
	काष्ठा ingenic_tcu *tcu = to_ingenic_tcu(समयr);

	अगर (next > 0xffff)
		वापस -EINVAL;

	regmap_ग_लिखो(tcu->map, TCU_REG_TDFRc(समयr->channel), next);
	regmap_ग_लिखो(tcu->map, TCU_REG_TCNTc(समयr->channel), 0);
	regmap_ग_लिखो(tcu->map, TCU_REG_TESR, BIT(समयr->channel));

	वापस 0;
पूर्ण

अटल व्योम ingenic_per_cpu_event_handler(व्योम *info)
अणु
	काष्ठा घड़ी_event_device *cevt = (काष्ठा घड़ी_event_device *) info;

	cevt->event_handler(cevt);
पूर्ण

अटल irqवापस_t ingenic_tcu_cevt_cb(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ingenic_tcu_समयr *समयr = dev_id;
	काष्ठा ingenic_tcu *tcu = to_ingenic_tcu(समयr);
	call_single_data_t *csd;

	regmap_ग_लिखो(tcu->map, TCU_REG_TECR, BIT(समयr->channel));

	अगर (समयr->cevt.event_handler) अणु
		csd = &per_cpu(ingenic_cevt_csd, समयr->cpu);
		csd->info = (व्योम *) &समयr->cevt;
		csd->func = ingenic_per_cpu_event_handler;
		smp_call_function_single_async(समयr->cpu, csd);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा clk *ingenic_tcu_get_घड़ी(काष्ठा device_node *np, पूर्णांक id)
अणु
	काष्ठा of_phandle_args args;

	args.np = np;
	args.args_count = 1;
	args.args[0] = id;

	वापस of_clk_get_from_provider(&args);
पूर्ण

अटल पूर्णांक ingenic_tcu_setup_cevt(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा ingenic_tcu *tcu = ingenic_tcu;
	काष्ठा ingenic_tcu_समयr *समयr = &tcu->समयrs[cpu];
	अचिन्हित पूर्णांक समयr_virq;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	अचिन्हित दीर्घ rate;
	पूर्णांक err;

	समयr->clk = ingenic_tcu_get_घड़ी(tcu->np, समयr->channel);
	अगर (IS_ERR(समयr->clk))
		वापस PTR_ERR(समयr->clk);

	err = clk_prepare_enable(समयr->clk);
	अगर (err)
		जाओ err_clk_put;

	rate = clk_get_rate(समयr->clk);
	अगर (!rate) अणु
		err = -EINVAL;
		जाओ err_clk_disable;
	पूर्ण

	करोमुख्य = irq_find_host(tcu->np);
	अगर (!करोमुख्य) अणु
		err = -ENODEV;
		जाओ err_clk_disable;
	पूर्ण

	समयr_virq = irq_create_mapping(करोमुख्य, समयr->channel);
	अगर (!समयr_virq) अणु
		err = -EINVAL;
		जाओ err_clk_disable;
	पूर्ण

	snम_लिखो(समयr->name, माप(समयr->name), "TCU%u", समयr->channel);

	err = request_irq(समयr_virq, ingenic_tcu_cevt_cb, IRQF_TIMER,
			  समयr->name, समयr);
	अगर (err)
		जाओ err_irq_dispose_mapping;

	समयr->cpu = smp_processor_id();
	समयr->cevt.cpumask = cpumask_of(smp_processor_id());
	समयr->cevt.features = CLOCK_EVT_FEAT_ONESHOT;
	समयr->cevt.name = समयr->name;
	समयr->cevt.rating = 200;
	समयr->cevt.set_state_shutकरोwn = ingenic_tcu_cevt_set_state_shutकरोwn;
	समयr->cevt.set_next_event = ingenic_tcu_cevt_set_next;

	घड़ीevents_config_and_रेजिस्टर(&समयr->cevt, rate, 10, 0xffff);

	वापस 0;

err_irq_dispose_mapping:
	irq_dispose_mapping(समयr_virq);
err_clk_disable:
	clk_disable_unprepare(समयr->clk);
err_clk_put:
	clk_put(समयr->clk);
	वापस err;
पूर्ण

अटल पूर्णांक __init ingenic_tcu_घड़ीsource_init(काष्ठा device_node *np,
					       काष्ठा ingenic_tcu *tcu)
अणु
	अचिन्हित पूर्णांक channel = tcu->cs_channel;
	काष्ठा घड़ीsource *cs = &tcu->cs;
	अचिन्हित दीर्घ rate;
	पूर्णांक err;

	tcu->cs_clk = ingenic_tcu_get_घड़ी(np, channel);
	अगर (IS_ERR(tcu->cs_clk))
		वापस PTR_ERR(tcu->cs_clk);

	err = clk_prepare_enable(tcu->cs_clk);
	अगर (err)
		जाओ err_clk_put;

	rate = clk_get_rate(tcu->cs_clk);
	अगर (!rate) अणु
		err = -EINVAL;
		जाओ err_clk_disable;
	पूर्ण

	/* Reset channel */
	regmap_update_bits(tcu->map, TCU_REG_TCSRc(channel),
			   0xffff & ~TCU_TCSR_RESERVED_BITS, 0);

	/* Reset counter */
	regmap_ग_लिखो(tcu->map, TCU_REG_TDFRc(channel), 0xffff);
	regmap_ग_लिखो(tcu->map, TCU_REG_TCNTc(channel), 0);

	/* Enable channel */
	regmap_ग_लिखो(tcu->map, TCU_REG_TESR, BIT(channel));

	cs->name = "ingenic-timer";
	cs->rating = 200;
	cs->flags = CLOCK_SOURCE_IS_CONTINUOUS;
	cs->mask = CLOCKSOURCE_MASK(16);
	cs->पढ़ो = ingenic_tcu_समयr_cs_पढ़ो;

	err = घड़ीsource_रेजिस्टर_hz(cs, rate);
	अगर (err)
		जाओ err_clk_disable;

	वापस 0;

err_clk_disable:
	clk_disable_unprepare(tcu->cs_clk);
err_clk_put:
	clk_put(tcu->cs_clk);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा ingenic_soc_info jz4740_soc_info = अणु
	.num_channels = 8,
पूर्ण;

अटल स्थिर काष्ठा ingenic_soc_info jz4725b_soc_info = अणु
	.num_channels = 6,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ingenic_tcu_of_match[] = अणु
	अणु .compatible = "ingenic,jz4740-tcu", .data = &jz4740_soc_info, पूर्ण,
	अणु .compatible = "ingenic,jz4725b-tcu", .data = &jz4725b_soc_info, पूर्ण,
	अणु .compatible = "ingenic,jz4760-tcu", .data = &jz4740_soc_info, पूर्ण,
	अणु .compatible = "ingenic,jz4770-tcu", .data = &jz4740_soc_info, पूर्ण,
	अणु .compatible = "ingenic,x1000-tcu", .data = &jz4740_soc_info, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक __init ingenic_tcu_init(काष्ठा device_node *np)
अणु
	स्थिर काष्ठा of_device_id *id = of_match_node(ingenic_tcu_of_match, np);
	स्थिर काष्ठा ingenic_soc_info *soc_info = id->data;
	काष्ठा ingenic_tcu_समयr *समयr;
	काष्ठा ingenic_tcu *tcu;
	काष्ठा regmap *map;
	अचिन्हित पूर्णांक cpu;
	पूर्णांक ret, last_bit = -1;
	दीर्घ rate;

	of_node_clear_flag(np, OF_POPULATED);

	map = device_node_to_regmap(np);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);

	tcu = kzalloc(काष्ठा_size(tcu, समयrs, num_possible_cpus()),
		      GFP_KERNEL);
	अगर (!tcu)
		वापस -ENOMEM;

	/*
	 * Enable all TCU channels क्रम PWM use by शेष except channels 0/1,
	 * and channel 2 अगर target CPU is JZ4780/X2000 and SMP is selected.
	 */
	tcu->pwm_channels_mask = GENMASK(soc_info->num_channels - 1,
					 num_possible_cpus() + 1);
	of_property_पढ़ो_u32(np, "ingenic,pwm-channels-mask",
			     (u32 *)&tcu->pwm_channels_mask);

	/* Verअगरy that we have at least num_possible_cpus() + 1 मुक्त channels */
	अगर (hweight8(tcu->pwm_channels_mask) >
			soc_info->num_channels - num_possible_cpus() + 1) अणु
		pr_crit("%s: Invalid PWM channel mask: 0x%02lx\n", __func__,
			tcu->pwm_channels_mask);
		ret = -EINVAL;
		जाओ err_मुक्त_ingenic_tcu;
	पूर्ण

	tcu->map = map;
	tcu->np = np;
	ingenic_tcu = tcu;

	क्रम (cpu = 0; cpu < num_possible_cpus(); cpu++) अणु
		समयr = &tcu->समयrs[cpu];

		समयr->cpu = cpu;
		समयr->channel = find_next_zero_bit(&tcu->pwm_channels_mask,
						  soc_info->num_channels,
						  last_bit + 1);
		last_bit = समयr->channel;
	पूर्ण

	tcu->cs_channel = find_next_zero_bit(&tcu->pwm_channels_mask,
					     soc_info->num_channels,
					     last_bit + 1);

	ret = ingenic_tcu_घड़ीsource_init(np, tcu);
	अगर (ret) अणु
		pr_crit("%s: Unable to init clocksource: %d\n", __func__, ret);
		जाओ err_मुक्त_ingenic_tcu;
	पूर्ण

	/* Setup घड़ी events on each CPU core */
	ret = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "Ingenic XBurst: online",
				ingenic_tcu_setup_cevt, शून्य);
	अगर (ret < 0) अणु
		pr_crit("%s: Unable to start CPU timers: %d\n", __func__, ret);
		जाओ err_tcu_घड़ीsource_cleanup;
	पूर्ण

	/* Register the sched_घड़ी at the end as there's no way to unकरो it */
	rate = clk_get_rate(tcu->cs_clk);
	sched_घड़ी_रेजिस्टर(ingenic_tcu_समयr_पढ़ो, 16, rate);

	वापस 0;

err_tcu_घड़ीsource_cleanup:
	घड़ीsource_unरेजिस्टर(&tcu->cs);
	clk_disable_unprepare(tcu->cs_clk);
	clk_put(tcu->cs_clk);
err_मुक्त_ingenic_tcu:
	kमुक्त(tcu);
	वापस ret;
पूर्ण

TIMER_OF_DECLARE(jz4740_tcu_पूर्णांकc,  "ingenic,jz4740-tcu",  ingenic_tcu_init);
TIMER_OF_DECLARE(jz4725b_tcu_पूर्णांकc, "ingenic,jz4725b-tcu", ingenic_tcu_init);
TIMER_OF_DECLARE(jz4760_tcu_पूर्णांकc,  "ingenic,jz4760-tcu",  ingenic_tcu_init);
TIMER_OF_DECLARE(jz4770_tcu_पूर्णांकc,  "ingenic,jz4770-tcu",  ingenic_tcu_init);
TIMER_OF_DECLARE(x1000_tcu_पूर्णांकc,  "ingenic,x1000-tcu",  ingenic_tcu_init);

अटल पूर्णांक __init ingenic_tcu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	platक्रमm_set_drvdata(pdev, ingenic_tcu);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ingenic_tcu_suspend(काष्ठा device *dev)
अणु
	काष्ठा ingenic_tcu *tcu = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक cpu;

	clk_disable(tcu->cs_clk);

	क्रम (cpu = 0; cpu < num_online_cpus(); cpu++)
		clk_disable(tcu->समयrs[cpu].clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ingenic_tcu_resume(काष्ठा device *dev)
अणु
	काष्ठा ingenic_tcu *tcu = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक cpu;
	पूर्णांक ret;

	क्रम (cpu = 0; cpu < num_online_cpus(); cpu++) अणु
		ret = clk_enable(tcu->समयrs[cpu].clk);
		अगर (ret)
			जाओ err_समयr_clk_disable;
	पूर्ण

	ret = clk_enable(tcu->cs_clk);
	अगर (ret)
		जाओ err_समयr_clk_disable;

	वापस 0;

err_समयr_clk_disable:
	क्रम (; cpu > 0; cpu--)
		clk_disable(tcu->समयrs[cpu - 1].clk);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops __maybe_unused ingenic_tcu_pm_ops = अणु
	/* _noirq: We want the TCU घड़ीs to be gated last / ungated first */
	.suspend_noirq = ingenic_tcu_suspend,
	.resume_noirq  = ingenic_tcu_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver ingenic_tcu_driver = अणु
	.driver = अणु
		.name	= "ingenic-tcu-timer",
#अगर_घोषित CONFIG_PM_SLEEP
		.pm	= &ingenic_tcu_pm_ops,
#पूर्ण_अगर
		.of_match_table = ingenic_tcu_of_match,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver_probe(ingenic_tcu_driver, ingenic_tcu_probe);
