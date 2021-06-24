<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic MMIO घड़ीsource support
 */
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>

काष्ठा घड़ीsource_mmio अणु
	व्योम __iomem *reg;
	काष्ठा घड़ीsource clksrc;
पूर्ण;

अटल अंतरभूत काष्ठा घड़ीsource_mmio *to_mmio_clksrc(काष्ठा घड़ीsource *c)
अणु
	वापस container_of(c, काष्ठा घड़ीsource_mmio, clksrc);
पूर्ण

u64 घड़ीsource_mmio_पढ़ोl_up(काष्ठा घड़ीsource *c)
अणु
	वापस (u64)पढ़ोl_relaxed(to_mmio_clksrc(c)->reg);
पूर्ण

u64 घड़ीsource_mmio_पढ़ोl_करोwn(काष्ठा घड़ीsource *c)
अणु
	वापस ~(u64)पढ़ोl_relaxed(to_mmio_clksrc(c)->reg) & c->mask;
पूर्ण

u64 घड़ीsource_mmio_पढ़ोw_up(काष्ठा घड़ीsource *c)
अणु
	वापस (u64)पढ़ोw_relaxed(to_mmio_clksrc(c)->reg);
पूर्ण

u64 घड़ीsource_mmio_पढ़ोw_करोwn(काष्ठा घड़ीsource *c)
अणु
	वापस ~(u64)पढ़ोw_relaxed(to_mmio_clksrc(c)->reg) & c->mask;
पूर्ण

/**
 * घड़ीsource_mmio_init - Initialize a simple mmio based घड़ीsource
 * @base:	Virtual address of the घड़ी पढ़ोout रेजिस्टर
 * @name:	Name of the घड़ीsource
 * @hz:		Frequency of the घड़ीsource in Hz
 * @rating:	Rating of the घड़ीsource
 * @bits:	Number of valid bits
 * @पढ़ो:	One of घड़ीsource_mmio_पढ़ो*() above
 */
पूर्णांक __init घड़ीsource_mmio_init(व्योम __iomem *base, स्थिर अक्षर *name,
	अचिन्हित दीर्घ hz, पूर्णांक rating, अचिन्हित bits,
	u64 (*पढ़ो)(काष्ठा घड़ीsource *))
अणु
	काष्ठा घड़ीsource_mmio *cs;

	अगर (bits > 64 || bits < 16)
		वापस -EINVAL;

	cs = kzalloc(माप(काष्ठा घड़ीsource_mmio), GFP_KERNEL);
	अगर (!cs)
		वापस -ENOMEM;

	cs->reg = base;
	cs->clksrc.name = name;
	cs->clksrc.rating = rating;
	cs->clksrc.पढ़ो = पढ़ो;
	cs->clksrc.mask = CLOCKSOURCE_MASK(bits);
	cs->clksrc.flags = CLOCK_SOURCE_IS_CONTINUOUS;

	वापस घड़ीsource_रेजिस्टर_hz(&cs->clksrc, hz);
पूर्ण
