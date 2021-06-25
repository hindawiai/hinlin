<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  H8/300 16bit Timer driver
 *
 *  Copyright 2015 Yoshinori Sato <ysato@users.sourcefoge.jp>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#घोषणा TSTR	0
#घोषणा TISRC	6

#घोषणा TCR	0
#घोषणा TCNT	2

#घोषणा bset(b, a) ioग_लिखो8(ioपढ़ो8(a) | (1 << (b)), (a))
#घोषणा bclr(b, a) ioग_लिखो8(ioपढ़ो8(a) & ~(1 << (b)), (a))

काष्ठा समयr16_priv अणु
	काष्ठा घड़ीsource cs;
	अचिन्हित दीर्घ total_cycles;
	व्योम __iomem *mapbase;
	व्योम __iomem *mapcommon;
	अचिन्हित लघु cs_enabled;
	अचिन्हित अक्षर enb;
	अचिन्हित अक्षर ovf;
	अचिन्हित अक्षर ovie;
पूर्ण;

अटल अचिन्हित दीर्घ समयr16_get_counter(काष्ठा समयr16_priv *p)
अणु
	अचिन्हित लघु v1, v2, v3;
	अचिन्हित अक्षर  o1, o2;

	o1 = ioपढ़ो8(p->mapcommon + TISRC) & p->ovf;

	/* Make sure the समयr value is stable. Stolen from acpi_pm.c */
	करो अणु
		o2 = o1;
		v1 = ioपढ़ो16be(p->mapbase + TCNT);
		v2 = ioपढ़ो16be(p->mapbase + TCNT);
		v3 = ioपढ़ो16be(p->mapbase + TCNT);
		o1 = ioपढ़ो8(p->mapcommon + TISRC) & p->ovf;
	पूर्ण जबतक (unlikely((o1 != o2) || (v1 > v2 && v1 < v3)
			  || (v2 > v3 && v2 < v1) || (v3 > v1 && v3 < v2)));

	अगर (likely(!o1))
		वापस v2;
	अन्यथा
		वापस v2 + 0x10000;
पूर्ण


अटल irqवापस_t समयr16_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा समयr16_priv *p = (काष्ठा समयr16_priv *)dev_id;

	bclr(p->ovf, p->mapcommon + TISRC);
	p->total_cycles += 0x10000;

	वापस IRQ_HANDLED;
पूर्ण

अटल अंतरभूत काष्ठा समयr16_priv *cs_to_priv(काष्ठा घड़ीsource *cs)
अणु
	वापस container_of(cs, काष्ठा समयr16_priv, cs);
पूर्ण

अटल u64 समयr16_घड़ीsource_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	काष्ठा समयr16_priv *p = cs_to_priv(cs);
	अचिन्हित दीर्घ raw, value;

	value = p->total_cycles;
	raw = समयr16_get_counter(p);

	वापस value + raw;
पूर्ण

अटल पूर्णांक समयr16_enable(काष्ठा घड़ीsource *cs)
अणु
	काष्ठा समयr16_priv *p = cs_to_priv(cs);

	WARN_ON(p->cs_enabled);

	p->total_cycles = 0;
	ioग_लिखो16be(0x0000, p->mapbase + TCNT);
	ioग_लिखो8(0x83, p->mapbase + TCR);
	bset(p->ovie, p->mapcommon + TISRC);
	bset(p->enb, p->mapcommon + TSTR);

	p->cs_enabled = true;
	वापस 0;
पूर्ण

अटल व्योम समयr16_disable(काष्ठा घड़ीsource *cs)
अणु
	काष्ठा समयr16_priv *p = cs_to_priv(cs);

	WARN_ON(!p->cs_enabled);

	bclr(p->ovie, p->mapcommon + TISRC);
	bclr(p->enb, p->mapcommon + TSTR);

	p->cs_enabled = false;
पूर्ण

अटल काष्ठा समयr16_priv समयr16_priv = अणु
	.cs = अणु
		.name = "h8300_16timer",
		.rating = 200,
		.पढ़ो = समयr16_घड़ीsource_पढ़ो,
		.enable = समयr16_enable,
		.disable = समयr16_disable,
		.mask = CLOCKSOURCE_MASK(माप(अचिन्हित दीर्घ) * 8),
		.flags = CLOCK_SOURCE_IS_CONTINUOUS,
	पूर्ण,
पूर्ण;

#घोषणा REG_CH   0
#घोषणा REG_COMM 1

अटल पूर्णांक __init h8300_16समयr_init(काष्ठा device_node *node)
अणु
	व्योम __iomem *base[2];
	पूर्णांक ret, irq;
	अचिन्हित पूर्णांक ch;
	काष्ठा clk *clk;

	clk = of_clk_get(node, 0);
	अगर (IS_ERR(clk)) अणु
		pr_err("failed to get clock for clocksource\n");
		वापस PTR_ERR(clk);
	पूर्ण

	ret = -ENXIO;
	base[REG_CH] = of_iomap(node, 0);
	अगर (!base[REG_CH]) अणु
		pr_err("failed to map registers for clocksource\n");
		जाओ मुक्त_clk;
	पूर्ण

	base[REG_COMM] = of_iomap(node, 1);
	अगर (!base[REG_COMM]) अणु
		pr_err("failed to map registers for clocksource\n");
		जाओ unmap_ch;
	पूर्ण

	ret = -EINVAL;
	irq = irq_of_parse_and_map(node, 0);
	अगर (!irq) अणु
		pr_err("failed to get irq for clockevent\n");
		जाओ unmap_comm;
	पूर्ण

	of_property_पढ़ो_u32(node, "renesas,channel", &ch);

	समयr16_priv.mapbase = base[REG_CH];
	समयr16_priv.mapcommon = base[REG_COMM];
	समयr16_priv.enb = ch;
	समयr16_priv.ovf = ch;
	समयr16_priv.ovie = 4 + ch;

	ret = request_irq(irq, समयr16_पूर्णांकerrupt,
			  IRQF_TIMER, समयr16_priv.cs.name, &समयr16_priv);
	अगर (ret < 0) अणु
		pr_err("failed to request irq %d of clocksource\n", irq);
		जाओ unmap_comm;
	पूर्ण

	घड़ीsource_रेजिस्टर_hz(&समयr16_priv.cs,
				clk_get_rate(clk) / 8);
	वापस 0;

unmap_comm:
	iounmap(base[REG_COMM]);
unmap_ch:
	iounmap(base[REG_CH]);
मुक्त_clk:
	clk_put(clk);
	वापस ret;
पूर्ण

TIMER_OF_DECLARE(h8300_16bit, "renesas,16bit-timer",
			   h8300_16समयr_init);
