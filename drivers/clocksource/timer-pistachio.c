<शैली गुरु>
/*
 * Pistachio घड़ीsource based on general-purpose समयrs
 *
 * Copyright (C) 2015 Imagination Technologies
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#घोषणा pr_fmt(fmt) "%s: " fmt, __func__

#समावेश <linux/clk.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/समय.स>

/* Top level reg */
#घोषणा CR_TIMER_CTRL_CFG		0x00
#घोषणा TIMER_ME_GLOBAL			BIT(0)
#घोषणा CR_TIMER_REV			0x10

/* Timer specअगरic रेजिस्टरs */
#घोषणा TIMER_CFG			0x20
#घोषणा TIMER_ME_LOCAL			BIT(0)
#घोषणा TIMER_RELOAD_VALUE		0x24
#घोषणा TIMER_CURRENT_VALUE		0x28
#घोषणा TIMER_CURRENT_OVERFLOW_VALUE	0x2C
#घोषणा TIMER_IRQ_STATUS		0x30
#घोषणा TIMER_IRQ_CLEAR			0x34
#घोषणा TIMER_IRQ_MASK			0x38

#घोषणा PERIP_TIMER_CONTROL		0x90

/* Timer specअगरic configuration Values */
#घोषणा RELOAD_VALUE			0xffffffff

काष्ठा pistachio_घड़ीsource अणु
	व्योम __iomem *base;
	raw_spinlock_t lock;
	काष्ठा घड़ीsource cs;
पूर्ण;

अटल काष्ठा pistachio_घड़ीsource pcs_gpt;

#घोषणा to_pistachio_घड़ीsource(cs)	\
	container_of(cs, काष्ठा pistachio_घड़ीsource, cs)

अटल अंतरभूत u32 gpt_पढ़ोl(व्योम __iomem *base, u32 offset, u32 gpt_id)
अणु
	वापस पढ़ोl(base + 0x20 * gpt_id + offset);
पूर्ण

अटल अंतरभूत व्योम gpt_ग_लिखोl(व्योम __iomem *base, u32 value, u32 offset,
		u32 gpt_id)
अणु
	ग_लिखोl(value, base + 0x20 * gpt_id + offset);
पूर्ण

अटल u64 notrace
pistachio_घड़ीsource_पढ़ो_cycles(काष्ठा घड़ीsource *cs)
अणु
	काष्ठा pistachio_घड़ीsource *pcs = to_pistachio_घड़ीsource(cs);
	u32 counter, overflow;
	अचिन्हित दीर्घ flags;

	/*
	 * The counter value is only refreshed after the overflow value is पढ़ो.
	 * And they must be पढ़ो in strict order, hence raw spin lock added.
	 */

	raw_spin_lock_irqsave(&pcs->lock, flags);
	overflow = gpt_पढ़ोl(pcs->base, TIMER_CURRENT_OVERFLOW_VALUE, 0);
	counter = gpt_पढ़ोl(pcs->base, TIMER_CURRENT_VALUE, 0);
	raw_spin_unlock_irqrestore(&pcs->lock, flags);

	वापस (u64)~counter;
पूर्ण

अटल u64 notrace pistachio_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस pistachio_घड़ीsource_पढ़ो_cycles(&pcs_gpt.cs);
पूर्ण

अटल व्योम pistachio_clksrc_set_mode(काष्ठा घड़ीsource *cs, पूर्णांक समयridx,
			पूर्णांक enable)
अणु
	काष्ठा pistachio_घड़ीsource *pcs = to_pistachio_घड़ीsource(cs);
	u32 val;

	val = gpt_पढ़ोl(pcs->base, TIMER_CFG, समयridx);
	अगर (enable)
		val |= TIMER_ME_LOCAL;
	अन्यथा
		val &= ~TIMER_ME_LOCAL;

	gpt_ग_लिखोl(pcs->base, val, TIMER_CFG, समयridx);
पूर्ण

अटल व्योम pistachio_clksrc_enable(काष्ठा घड़ीsource *cs, पूर्णांक समयridx)
अणु
	काष्ठा pistachio_घड़ीsource *pcs = to_pistachio_घड़ीsource(cs);

	/* Disable GPT local beक्रमe loading reload value */
	pistachio_clksrc_set_mode(cs, समयridx, false);
	gpt_ग_लिखोl(pcs->base, RELOAD_VALUE, TIMER_RELOAD_VALUE, समयridx);
	pistachio_clksrc_set_mode(cs, समयridx, true);
पूर्ण

अटल व्योम pistachio_clksrc_disable(काष्ठा घड़ीsource *cs, पूर्णांक समयridx)
अणु
	/* Disable GPT local */
	pistachio_clksrc_set_mode(cs, समयridx, false);
पूर्ण

अटल पूर्णांक pistachio_घड़ीsource_enable(काष्ठा घड़ीsource *cs)
अणु
	pistachio_clksrc_enable(cs, 0);
	वापस 0;
पूर्ण

अटल व्योम pistachio_घड़ीsource_disable(काष्ठा घड़ीsource *cs)
अणु
	pistachio_clksrc_disable(cs, 0);
पूर्ण

/* Desirable घड़ी source क्रम pistachio platक्रमm */
अटल काष्ठा pistachio_घड़ीsource pcs_gpt = अणु
	.cs =	अणु
		.name		= "gptimer",
		.rating		= 300,
		.enable		= pistachio_घड़ीsource_enable,
		.disable	= pistachio_घड़ीsource_disable,
		.पढ़ो		= pistachio_घड़ीsource_पढ़ो_cycles,
		.mask		= CLOCKSOURCE_MASK(32),
		.flags		= CLOCK_SOURCE_IS_CONTINUOUS |
				  CLOCK_SOURCE_SUSPEND_NONSTOP,
		पूर्ण,
पूर्ण;

अटल पूर्णांक __init pistachio_clksrc_of_init(काष्ठा device_node *node)
अणु
	काष्ठा clk *sys_clk, *fast_clk;
	काष्ठा regmap *periph_regs;
	अचिन्हित दीर्घ rate;
	पूर्णांक ret;

	pcs_gpt.base = of_iomap(node, 0);
	अगर (!pcs_gpt.base) अणु
		pr_err("cannot iomap\n");
		वापस -ENXIO;
	पूर्ण

	periph_regs = syscon_regmap_lookup_by_phandle(node, "img,cr-periph");
	अगर (IS_ERR(periph_regs)) अणु
		pr_err("cannot get peripheral regmap (%ld)\n",
		       PTR_ERR(periph_regs));
		वापस PTR_ERR(periph_regs);
	पूर्ण

	/* Switch to using the fast counter घड़ी */
	ret = regmap_update_bits(periph_regs, PERIP_TIMER_CONTROL,
				 0xf, 0x0);
	अगर (ret)
		वापस ret;

	sys_clk = of_clk_get_by_name(node, "sys");
	अगर (IS_ERR(sys_clk)) अणु
		pr_err("clock get failed (%ld)\n", PTR_ERR(sys_clk));
		वापस PTR_ERR(sys_clk);
	पूर्ण

	fast_clk = of_clk_get_by_name(node, "fast");
	अगर (IS_ERR(fast_clk)) अणु
		pr_err("clock get failed (%lu)\n", PTR_ERR(fast_clk));
		वापस PTR_ERR(fast_clk);
	पूर्ण

	ret = clk_prepare_enable(sys_clk);
	अगर (ret < 0) अणु
		pr_err("failed to enable clock (%d)\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(fast_clk);
	अगर (ret < 0) अणु
		pr_err("failed to enable clock (%d)\n", ret);
		clk_disable_unprepare(sys_clk);
		वापस ret;
	पूर्ण

	rate = clk_get_rate(fast_clk);

	/* Disable irq's क्रम घड़ीsource usage */
	gpt_ग_लिखोl(pcs_gpt.base, 0, TIMER_IRQ_MASK, 0);
	gpt_ग_लिखोl(pcs_gpt.base, 0, TIMER_IRQ_MASK, 1);
	gpt_ग_लिखोl(pcs_gpt.base, 0, TIMER_IRQ_MASK, 2);
	gpt_ग_लिखोl(pcs_gpt.base, 0, TIMER_IRQ_MASK, 3);

	/* Enable समयr block */
	ग_लिखोl(TIMER_ME_GLOBAL, pcs_gpt.base);

	raw_spin_lock_init(&pcs_gpt.lock);
	sched_घड़ी_रेजिस्टर(pistachio_पढ़ो_sched_घड़ी, 32, rate);
	वापस घड़ीsource_रेजिस्टर_hz(&pcs_gpt.cs, rate);
पूर्ण
TIMER_OF_DECLARE(pistachio_gpसमयr, "img,pistachio-gptimer",
		       pistachio_clksrc_of_init);
