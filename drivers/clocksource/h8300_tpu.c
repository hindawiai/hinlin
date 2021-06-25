<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  H8S TPU Driver
 *
 *  Copyright 2015 Yoshinori Sato <ysato@users.sourcefoge.jp>
 *
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#घोषणा TCR	0x0
#घोषणा TSR	0x5
#घोषणा TCNT	0x6

#घोषणा TCFV	0x10

काष्ठा tpu_priv अणु
	काष्ठा घड़ीsource cs;
	व्योम __iomem *mapbase1;
	व्योम __iomem *mapbase2;
	raw_spinlock_t lock;
	अचिन्हित पूर्णांक cs_enabled;
पूर्ण;

अटल अंतरभूत अचिन्हित दीर्घ पढ़ो_tcnt32(काष्ठा tpu_priv *p)
अणु
	अचिन्हित दीर्घ tcnt;

	tcnt = ioपढ़ो16be(p->mapbase1 + TCNT) << 16;
	tcnt |= ioपढ़ो16be(p->mapbase2 + TCNT);
	वापस tcnt;
पूर्ण

अटल पूर्णांक tpu_get_counter(काष्ठा tpu_priv *p, अचिन्हित दीर्घ दीर्घ *val)
अणु
	अचिन्हित दीर्घ v1, v2, v3;
	पूर्णांक o1, o2;

	o1 = ioपढ़ो8(p->mapbase1 + TSR) & TCFV;

	/* Make sure the समयr value is stable. Stolen from acpi_pm.c */
	करो अणु
		o2 = o1;
		v1 = पढ़ो_tcnt32(p);
		v2 = पढ़ो_tcnt32(p);
		v3 = पढ़ो_tcnt32(p);
		o1 = ioपढ़ो8(p->mapbase1 + TSR) & TCFV;
	पूर्ण जबतक (unlikely((o1 != o2) || (v1 > v2 && v1 < v3)
			  || (v2 > v3 && v2 < v1) || (v3 > v1 && v3 < v2)));

	*val = v2;
	वापस o1;
पूर्ण

अटल अंतरभूत काष्ठा tpu_priv *cs_to_priv(काष्ठा घड़ीsource *cs)
अणु
	वापस container_of(cs, काष्ठा tpu_priv, cs);
पूर्ण

अटल u64 tpu_घड़ीsource_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	काष्ठा tpu_priv *p = cs_to_priv(cs);
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ दीर्घ value;

	raw_spin_lock_irqsave(&p->lock, flags);
	अगर (tpu_get_counter(p, &value))
		value += 0x100000000;
	raw_spin_unlock_irqrestore(&p->lock, flags);

	वापस value;
पूर्ण

अटल पूर्णांक tpu_घड़ीsource_enable(काष्ठा घड़ीsource *cs)
अणु
	काष्ठा tpu_priv *p = cs_to_priv(cs);

	WARN_ON(p->cs_enabled);

	ioग_लिखो16be(0, p->mapbase1 + TCNT);
	ioग_लिखो16be(0, p->mapbase2 + TCNT);
	ioग_लिखो8(0x0f, p->mapbase1 + TCR);
	ioग_लिखो8(0x03, p->mapbase2 + TCR);

	p->cs_enabled = true;
	वापस 0;
पूर्ण

अटल व्योम tpu_घड़ीsource_disable(काष्ठा घड़ीsource *cs)
अणु
	काष्ठा tpu_priv *p = cs_to_priv(cs);

	WARN_ON(!p->cs_enabled);

	ioग_लिखो8(0, p->mapbase1 + TCR);
	ioग_लिखो8(0, p->mapbase2 + TCR);
	p->cs_enabled = false;
पूर्ण

अटल काष्ठा tpu_priv tpu_priv = अणु
	.cs = अणु
		.name = "H8S_TPU",
		.rating = 200,
		.पढ़ो = tpu_घड़ीsource_पढ़ो,
		.enable = tpu_घड़ीsource_enable,
		.disable = tpu_घड़ीsource_disable,
		.mask = CLOCKSOURCE_MASK(माप(अचिन्हित दीर्घ) * 8),
		.flags = CLOCK_SOURCE_IS_CONTINUOUS,
	पूर्ण,
पूर्ण;

#घोषणा CH_L 0
#घोषणा CH_H 1

अटल पूर्णांक __init h8300_tpu_init(काष्ठा device_node *node)
अणु
	व्योम __iomem *base[2];
	काष्ठा clk *clk;
	पूर्णांक ret = -ENXIO;

	clk = of_clk_get(node, 0);
	अगर (IS_ERR(clk)) अणु
		pr_err("failed to get clock for clocksource\n");
		वापस PTR_ERR(clk);
	पूर्ण

	base[CH_L] = of_iomap(node, CH_L);
	अगर (!base[CH_L]) अणु
		pr_err("failed to map registers for clocksource\n");
		जाओ मुक्त_clk;
	पूर्ण
	base[CH_H] = of_iomap(node, CH_H);
	अगर (!base[CH_H]) अणु
		pr_err("failed to map registers for clocksource\n");
		जाओ unmap_L;
	पूर्ण

	tpu_priv.mapbase1 = base[CH_L];
	tpu_priv.mapbase2 = base[CH_H];

	वापस घड़ीsource_रेजिस्टर_hz(&tpu_priv.cs, clk_get_rate(clk) / 64);

unmap_L:
	iounmap(base[CH_H]);
मुक्त_clk:
	clk_put(clk);
	वापस ret;
पूर्ण

TIMER_OF_DECLARE(h8300_tpu, "renesas,tpu", h8300_tpu_init);
