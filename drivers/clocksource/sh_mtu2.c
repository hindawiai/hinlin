<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SuperH Timer Support - MTU2
 *
 *  Copyright (C) 2009 Magnus Damm
 */

#समावेश <linux/clk.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/sh_समयr.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#अगर_घोषित CONFIG_SUPERH
#समावेश <यंत्र/platक्रमm_early.h>
#पूर्ण_अगर

काष्ठा sh_mtu2_device;

काष्ठा sh_mtu2_channel अणु
	काष्ठा sh_mtu2_device *mtu;
	अचिन्हित पूर्णांक index;

	व्योम __iomem *base;

	काष्ठा घड़ी_event_device ced;
पूर्ण;

काष्ठा sh_mtu2_device अणु
	काष्ठा platक्रमm_device *pdev;

	व्योम __iomem *mapbase;
	काष्ठा clk *clk;

	raw_spinlock_t lock; /* Protect the shared रेजिस्टरs */

	काष्ठा sh_mtu2_channel *channels;
	अचिन्हित पूर्णांक num_channels;

	bool has_घड़ीevent;
पूर्ण;

#घोषणा TSTR -1 /* shared रेजिस्टर */
#घोषणा TCR  0 /* channel रेजिस्टर */
#घोषणा TMDR 1 /* channel रेजिस्टर */
#घोषणा TIOR 2 /* channel रेजिस्टर */
#घोषणा TIER 3 /* channel रेजिस्टर */
#घोषणा TSR  4 /* channel रेजिस्टर */
#घोषणा TCNT 5 /* channel रेजिस्टर */
#घोषणा TGR  6 /* channel रेजिस्टर */

#घोषणा TCR_CCLR_NONE		(0 << 5)
#घोषणा TCR_CCLR_TGRA		(1 << 5)
#घोषणा TCR_CCLR_TGRB		(2 << 5)
#घोषणा TCR_CCLR_SYNC		(3 << 5)
#घोषणा TCR_CCLR_TGRC		(5 << 5)
#घोषणा TCR_CCLR_TGRD		(6 << 5)
#घोषणा TCR_CCLR_MASK		(7 << 5)
#घोषणा TCR_CKEG_RISING		(0 << 3)
#घोषणा TCR_CKEG_FALLING	(1 << 3)
#घोषणा TCR_CKEG_BOTH		(2 << 3)
#घोषणा TCR_CKEG_MASK		(3 << 3)
/* Values 4 to 7 are channel-dependent */
#घोषणा TCR_TPSC_P1		(0 << 0)
#घोषणा TCR_TPSC_P4		(1 << 0)
#घोषणा TCR_TPSC_P16		(2 << 0)
#घोषणा TCR_TPSC_P64		(3 << 0)
#घोषणा TCR_TPSC_CH0_TCLKA	(4 << 0)
#घोषणा TCR_TPSC_CH0_TCLKB	(5 << 0)
#घोषणा TCR_TPSC_CH0_TCLKC	(6 << 0)
#घोषणा TCR_TPSC_CH0_TCLKD	(7 << 0)
#घोषणा TCR_TPSC_CH1_TCLKA	(4 << 0)
#घोषणा TCR_TPSC_CH1_TCLKB	(5 << 0)
#घोषणा TCR_TPSC_CH1_P256	(6 << 0)
#घोषणा TCR_TPSC_CH1_TCNT2	(7 << 0)
#घोषणा TCR_TPSC_CH2_TCLKA	(4 << 0)
#घोषणा TCR_TPSC_CH2_TCLKB	(5 << 0)
#घोषणा TCR_TPSC_CH2_TCLKC	(6 << 0)
#घोषणा TCR_TPSC_CH2_P1024	(7 << 0)
#घोषणा TCR_TPSC_CH34_P256	(4 << 0)
#घोषणा TCR_TPSC_CH34_P1024	(5 << 0)
#घोषणा TCR_TPSC_CH34_TCLKA	(6 << 0)
#घोषणा TCR_TPSC_CH34_TCLKB	(7 << 0)
#घोषणा TCR_TPSC_MASK		(7 << 0)

#घोषणा TMDR_BFE		(1 << 6)
#घोषणा TMDR_BFB		(1 << 5)
#घोषणा TMDR_BFA		(1 << 4)
#घोषणा TMDR_MD_NORMAL		(0 << 0)
#घोषणा TMDR_MD_PWM_1		(2 << 0)
#घोषणा TMDR_MD_PWM_2		(3 << 0)
#घोषणा TMDR_MD_PHASE_1		(4 << 0)
#घोषणा TMDR_MD_PHASE_2		(5 << 0)
#घोषणा TMDR_MD_PHASE_3		(6 << 0)
#घोषणा TMDR_MD_PHASE_4		(7 << 0)
#घोषणा TMDR_MD_PWM_SYNC	(8 << 0)
#घोषणा TMDR_MD_PWM_COMP_CREST	(13 << 0)
#घोषणा TMDR_MD_PWM_COMP_TROUGH	(14 << 0)
#घोषणा TMDR_MD_PWM_COMP_BOTH	(15 << 0)
#घोषणा TMDR_MD_MASK		(15 << 0)

#घोषणा TIOC_IOCH(n)		((n) << 4)
#घोषणा TIOC_IOCL(n)		((n) << 0)
#घोषणा TIOR_OC_RETAIN		(0 << 0)
#घोषणा TIOR_OC_0_CLEAR		(1 << 0)
#घोषणा TIOR_OC_0_SET		(2 << 0)
#घोषणा TIOR_OC_0_TOGGLE	(3 << 0)
#घोषणा TIOR_OC_1_CLEAR		(5 << 0)
#घोषणा TIOR_OC_1_SET		(6 << 0)
#घोषणा TIOR_OC_1_TOGGLE	(7 << 0)
#घोषणा TIOR_IC_RISING		(8 << 0)
#घोषणा TIOR_IC_FALLING		(9 << 0)
#घोषणा TIOR_IC_BOTH		(10 << 0)
#घोषणा TIOR_IC_TCNT		(12 << 0)
#घोषणा TIOR_MASK		(15 << 0)

#घोषणा TIER_TTGE		(1 << 7)
#घोषणा TIER_TTGE2		(1 << 6)
#घोषणा TIER_TCIEU		(1 << 5)
#घोषणा TIER_TCIEV		(1 << 4)
#घोषणा TIER_TGIED		(1 << 3)
#घोषणा TIER_TGIEC		(1 << 2)
#घोषणा TIER_TGIEB		(1 << 1)
#घोषणा TIER_TGIEA		(1 << 0)

#घोषणा TSR_TCFD		(1 << 7)
#घोषणा TSR_TCFU		(1 << 5)
#घोषणा TSR_TCFV		(1 << 4)
#घोषणा TSR_TGFD		(1 << 3)
#घोषणा TSR_TGFC		(1 << 2)
#घोषणा TSR_TGFB		(1 << 1)
#घोषणा TSR_TGFA		(1 << 0)

अटल अचिन्हित दीर्घ mtu2_reg_offs[] = अणु
	[TCR] = 0,
	[TMDR] = 1,
	[TIOR] = 2,
	[TIER] = 4,
	[TSR] = 5,
	[TCNT] = 6,
	[TGR] = 8,
पूर्ण;

अटल अंतरभूत अचिन्हित दीर्घ sh_mtu2_पढ़ो(काष्ठा sh_mtu2_channel *ch, पूर्णांक reg_nr)
अणु
	अचिन्हित दीर्घ offs;

	अगर (reg_nr == TSTR)
		वापस ioपढ़ो8(ch->mtu->mapbase + 0x280);

	offs = mtu2_reg_offs[reg_nr];

	अगर ((reg_nr == TCNT) || (reg_nr == TGR))
		वापस ioपढ़ो16(ch->base + offs);
	अन्यथा
		वापस ioपढ़ो8(ch->base + offs);
पूर्ण

अटल अंतरभूत व्योम sh_mtu2_ग_लिखो(काष्ठा sh_mtu2_channel *ch, पूर्णांक reg_nr,
				अचिन्हित दीर्घ value)
अणु
	अचिन्हित दीर्घ offs;

	अगर (reg_nr == TSTR)
		वापस ioग_लिखो8(value, ch->mtu->mapbase + 0x280);

	offs = mtu2_reg_offs[reg_nr];

	अगर ((reg_nr == TCNT) || (reg_nr == TGR))
		ioग_लिखो16(value, ch->base + offs);
	अन्यथा
		ioग_लिखो8(value, ch->base + offs);
पूर्ण

अटल व्योम sh_mtu2_start_stop_ch(काष्ठा sh_mtu2_channel *ch, पूर्णांक start)
अणु
	अचिन्हित दीर्घ flags, value;

	/* start stop रेजिस्टर shared by multiple समयr channels */
	raw_spin_lock_irqsave(&ch->mtu->lock, flags);
	value = sh_mtu2_पढ़ो(ch, TSTR);

	अगर (start)
		value |= 1 << ch->index;
	अन्यथा
		value &= ~(1 << ch->index);

	sh_mtu2_ग_लिखो(ch, TSTR, value);
	raw_spin_unlock_irqrestore(&ch->mtu->lock, flags);
पूर्ण

अटल पूर्णांक sh_mtu2_enable(काष्ठा sh_mtu2_channel *ch)
अणु
	अचिन्हित दीर्घ periodic;
	अचिन्हित दीर्घ rate;
	पूर्णांक ret;

	pm_runसमय_get_sync(&ch->mtu->pdev->dev);
	dev_pm_syscore_device(&ch->mtu->pdev->dev, true);

	/* enable घड़ी */
	ret = clk_enable(ch->mtu->clk);
	अगर (ret) अणु
		dev_err(&ch->mtu->pdev->dev, "ch%u: cannot enable clock\n",
			ch->index);
		वापस ret;
	पूर्ण

	/* make sure channel is disabled */
	sh_mtu2_start_stop_ch(ch, 0);

	rate = clk_get_rate(ch->mtu->clk) / 64;
	periodic = (rate + HZ/2) / HZ;

	/*
	 * "Periodic Counter Operation"
	 * Clear on TGRA compare match, भागide घड़ी by 64.
	 */
	sh_mtu2_ग_लिखो(ch, TCR, TCR_CCLR_TGRA | TCR_TPSC_P64);
	sh_mtu2_ग_लिखो(ch, TIOR, TIOC_IOCH(TIOR_OC_0_CLEAR) |
		      TIOC_IOCL(TIOR_OC_0_CLEAR));
	sh_mtu2_ग_लिखो(ch, TGR, periodic);
	sh_mtu2_ग_लिखो(ch, TCNT, 0);
	sh_mtu2_ग_लिखो(ch, TMDR, TMDR_MD_NORMAL);
	sh_mtu2_ग_लिखो(ch, TIER, TIER_TGIEA);

	/* enable channel */
	sh_mtu2_start_stop_ch(ch, 1);

	वापस 0;
पूर्ण

अटल व्योम sh_mtu2_disable(काष्ठा sh_mtu2_channel *ch)
अणु
	/* disable channel */
	sh_mtu2_start_stop_ch(ch, 0);

	/* stop घड़ी */
	clk_disable(ch->mtu->clk);

	dev_pm_syscore_device(&ch->mtu->pdev->dev, false);
	pm_runसमय_put(&ch->mtu->pdev->dev);
पूर्ण

अटल irqवापस_t sh_mtu2_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sh_mtu2_channel *ch = dev_id;

	/* acknowledge पूर्णांकerrupt */
	sh_mtu2_पढ़ो(ch, TSR);
	sh_mtu2_ग_लिखो(ch, TSR, ~TSR_TGFA);

	/* notअगरy घड़ीevent layer */
	ch->ced.event_handler(&ch->ced);
	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा sh_mtu2_channel *ced_to_sh_mtu2(काष्ठा घड़ी_event_device *ced)
अणु
	वापस container_of(ced, काष्ठा sh_mtu2_channel, ced);
पूर्ण

अटल पूर्णांक sh_mtu2_घड़ी_event_shutकरोwn(काष्ठा घड़ी_event_device *ced)
अणु
	काष्ठा sh_mtu2_channel *ch = ced_to_sh_mtu2(ced);

	अगर (घड़ीevent_state_periodic(ced))
		sh_mtu2_disable(ch);

	वापस 0;
पूर्ण

अटल पूर्णांक sh_mtu2_घड़ी_event_set_periodic(काष्ठा घड़ी_event_device *ced)
अणु
	काष्ठा sh_mtu2_channel *ch = ced_to_sh_mtu2(ced);

	अगर (घड़ीevent_state_periodic(ced))
		sh_mtu2_disable(ch);

	dev_info(&ch->mtu->pdev->dev, "ch%u: used for periodic clock events\n",
		 ch->index);
	sh_mtu2_enable(ch);
	वापस 0;
पूर्ण

अटल व्योम sh_mtu2_घड़ी_event_suspend(काष्ठा घड़ी_event_device *ced)
अणु
	dev_pm_genpd_suspend(&ced_to_sh_mtu2(ced)->mtu->pdev->dev);
पूर्ण

अटल व्योम sh_mtu2_घड़ी_event_resume(काष्ठा घड़ी_event_device *ced)
अणु
	dev_pm_genpd_resume(&ced_to_sh_mtu2(ced)->mtu->pdev->dev);
पूर्ण

अटल व्योम sh_mtu2_रेजिस्टर_घड़ीevent(काष्ठा sh_mtu2_channel *ch,
					स्थिर अक्षर *name)
अणु
	काष्ठा घड़ी_event_device *ced = &ch->ced;

	ced->name = name;
	ced->features = CLOCK_EVT_FEAT_PERIODIC;
	ced->rating = 200;
	ced->cpumask = cpu_possible_mask;
	ced->set_state_shutकरोwn = sh_mtu2_घड़ी_event_shutकरोwn;
	ced->set_state_periodic = sh_mtu2_घड़ी_event_set_periodic;
	ced->suspend = sh_mtu2_घड़ी_event_suspend;
	ced->resume = sh_mtu2_घड़ी_event_resume;

	dev_info(&ch->mtu->pdev->dev, "ch%u: used for clock events\n",
		 ch->index);
	घड़ीevents_रेजिस्टर_device(ced);
पूर्ण

अटल पूर्णांक sh_mtu2_रेजिस्टर(काष्ठा sh_mtu2_channel *ch, स्थिर अक्षर *name)
अणु
	ch->mtu->has_घड़ीevent = true;
	sh_mtu2_रेजिस्टर_घड़ीevent(ch, name);

	वापस 0;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक sh_mtu2_channel_offsets[] = अणु
	0x300, 0x380, 0x000,
पूर्ण;

अटल पूर्णांक sh_mtu2_setup_channel(काष्ठा sh_mtu2_channel *ch, अचिन्हित पूर्णांक index,
				 काष्ठा sh_mtu2_device *mtu)
अणु
	अक्षर name[6];
	पूर्णांक irq;
	पूर्णांक ret;

	ch->mtu = mtu;

	प्र_लिखो(name, "tgi%ua", index);
	irq = platक्रमm_get_irq_byname(mtu->pdev, name);
	अगर (irq < 0) अणु
		/* Skip channels with no declared पूर्णांकerrupt. */
		वापस 0;
	पूर्ण

	ret = request_irq(irq, sh_mtu2_पूर्णांकerrupt,
			  IRQF_TIMER | IRQF_IRQPOLL | IRQF_NOBALANCING,
			  dev_name(&ch->mtu->pdev->dev), ch);
	अगर (ret) अणु
		dev_err(&ch->mtu->pdev->dev, "ch%u: failed to request irq %d\n",
			index, irq);
		वापस ret;
	पूर्ण

	ch->base = mtu->mapbase + sh_mtu2_channel_offsets[index];
	ch->index = index;

	वापस sh_mtu2_रेजिस्टर(ch, dev_name(&mtu->pdev->dev));
पूर्ण

अटल पूर्णांक sh_mtu2_map_memory(काष्ठा sh_mtu2_device *mtu)
अणु
	काष्ठा resource *res;

	res = platक्रमm_get_resource(mtu->pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&mtu->pdev->dev, "failed to get I/O memory\n");
		वापस -ENXIO;
	पूर्ण

	mtu->mapbase = ioremap(res->start, resource_size(res));
	अगर (mtu->mapbase == शून्य)
		वापस -ENXIO;

	वापस 0;
पूर्ण

अटल पूर्णांक sh_mtu2_setup(काष्ठा sh_mtu2_device *mtu,
			 काष्ठा platक्रमm_device *pdev)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	mtu->pdev = pdev;

	raw_spin_lock_init(&mtu->lock);

	/* Get hold of घड़ी. */
	mtu->clk = clk_get(&mtu->pdev->dev, "fck");
	अगर (IS_ERR(mtu->clk)) अणु
		dev_err(&mtu->pdev->dev, "cannot get clock\n");
		वापस PTR_ERR(mtu->clk);
	पूर्ण

	ret = clk_prepare(mtu->clk);
	अगर (ret < 0)
		जाओ err_clk_put;

	/* Map the memory resource. */
	ret = sh_mtu2_map_memory(mtu);
	अगर (ret < 0) अणु
		dev_err(&mtu->pdev->dev, "failed to remap I/O memory\n");
		जाओ err_clk_unprepare;
	पूर्ण

	/* Allocate and setup the channels. */
	ret = platक्रमm_irq_count(pdev);
	अगर (ret < 0)
		जाओ err_unmap;

	mtu->num_channels = min_t(अचिन्हित पूर्णांक, ret,
				  ARRAY_SIZE(sh_mtu2_channel_offsets));

	mtu->channels = kसुस्मृति(mtu->num_channels, माप(*mtu->channels),
				GFP_KERNEL);
	अगर (mtu->channels == शून्य) अणु
		ret = -ENOMEM;
		जाओ err_unmap;
	पूर्ण

	क्रम (i = 0; i < mtu->num_channels; ++i) अणु
		ret = sh_mtu2_setup_channel(&mtu->channels[i], i, mtu);
		अगर (ret < 0)
			जाओ err_unmap;
	पूर्ण

	platक्रमm_set_drvdata(pdev, mtu);

	वापस 0;

err_unmap:
	kमुक्त(mtu->channels);
	iounmap(mtu->mapbase);
err_clk_unprepare:
	clk_unprepare(mtu->clk);
err_clk_put:
	clk_put(mtu->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक sh_mtu2_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sh_mtu2_device *mtu = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	अगर (!is_sh_early_platक्रमm_device(pdev)) अणु
		pm_runसमय_set_active(&pdev->dev);
		pm_runसमय_enable(&pdev->dev);
	पूर्ण

	अगर (mtu) अणु
		dev_info(&pdev->dev, "kept as earlytimer\n");
		जाओ out;
	पूर्ण

	mtu = kzalloc(माप(*mtu), GFP_KERNEL);
	अगर (mtu == शून्य)
		वापस -ENOMEM;

	ret = sh_mtu2_setup(mtu, pdev);
	अगर (ret) अणु
		kमुक्त(mtu);
		pm_runसमय_idle(&pdev->dev);
		वापस ret;
	पूर्ण
	अगर (is_sh_early_platक्रमm_device(pdev))
		वापस 0;

 out:
	अगर (mtu->has_घड़ीevent)
		pm_runसमय_irq_safe(&pdev->dev);
	अन्यथा
		pm_runसमय_idle(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sh_mtu2_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस -EBUSY; /* cannot unरेजिस्टर घड़ीevent */
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id sh_mtu2_id_table[] = अणु
	अणु "sh-mtu2", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, sh_mtu2_id_table);

अटल स्थिर काष्ठा of_device_id sh_mtu2_of_table[] __maybe_unused = अणु
	अणु .compatible = "renesas,mtu2" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sh_mtu2_of_table);

अटल काष्ठा platक्रमm_driver sh_mtu2_device_driver = अणु
	.probe		= sh_mtu2_probe,
	.हटाओ		= sh_mtu2_हटाओ,
	.driver		= अणु
		.name	= "sh_mtu2",
		.of_match_table = of_match_ptr(sh_mtu2_of_table),
	पूर्ण,
	.id_table	= sh_mtu2_id_table,
पूर्ण;

अटल पूर्णांक __init sh_mtu2_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&sh_mtu2_device_driver);
पूर्ण

अटल व्योम __निकास sh_mtu2_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&sh_mtu2_device_driver);
पूर्ण

#अगर_घोषित CONFIG_SUPERH
sh_early_platक्रमm_init("earlytimer", &sh_mtu2_device_driver);
#पूर्ण_अगर

subsys_initcall(sh_mtu2_init);
module_निकास(sh_mtu2_निकास);

MODULE_AUTHOR("Magnus Damm");
MODULE_DESCRIPTION("SuperH MTU2 Timer Driver");
MODULE_LICENSE("GPL v2");
