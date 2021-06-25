<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Au1300 media block घातer gating (VSS)
 *
 * This is a stop-gap solution until I have the घड़ी framework पूर्णांकegration
 * पढ़ोy. This stuff here really must be handled transparently when घड़ीs
 * क्रम various media blocks are enabled/disabled.
 */

#समावेश <linux/export.h>
#समावेश <linux/spinlock.h>
#समावेश <यंत्र/mach-au1x00/au1000.h>

#घोषणा VSS_GATE	0x00	/* gate रुको समयrs */
#घोषणा VSS_CLKRST	0x04	/* घड़ी/block control */
#घोषणा VSS_FTR		0x08	/* footers */

#घोषणा VSS_ADDR(blk)	(KSEG1ADDR(AU1300_VSS_PHYS_ADDR) + (blk * 0x0c))

अटल DEFINE_SPINLOCK(au1300_vss_lock);

/* enable a block as outlined in the databook */
अटल अंतरभूत व्योम __enable_block(पूर्णांक block)
अणु
	व्योम __iomem *base = (व्योम __iomem *)VSS_ADDR(block);

	__raw_ग_लिखोl(3, base + VSS_CLKRST);	/* enable घड़ी, निश्चित reset */
	wmb();

	__raw_ग_लिखोl(0x01fffffe, base + VSS_GATE); /* maximum setup समय */
	wmb();

	/* enable footers in sequence */
	__raw_ग_लिखोl(0x01, base + VSS_FTR);
	wmb();
	__raw_ग_लिखोl(0x03, base + VSS_FTR);
	wmb();
	__raw_ग_लिखोl(0x07, base + VSS_FTR);
	wmb();
	__raw_ग_लिखोl(0x0f, base + VSS_FTR);
	wmb();

	__raw_ग_लिखोl(0x01ffffff, base + VSS_GATE); /* start FSM too */
	wmb();

	__raw_ग_लिखोl(2, base + VSS_CLKRST);	/* deनिश्चित reset */
	wmb();

	__raw_ग_लिखोl(0x1f, base + VSS_FTR);	/* enable isolation cells */
	wmb();
पूर्ण

/* disable a block as outlined in the databook */
अटल अंतरभूत व्योम __disable_block(पूर्णांक block)
अणु
	व्योम __iomem *base = (व्योम __iomem *)VSS_ADDR(block);

	__raw_ग_लिखोl(0x0f, base + VSS_FTR);	/* disable isolation cells */
	wmb();
	__raw_ग_लिखोl(0, base + VSS_GATE);	/* disable FSM */
	wmb();
	__raw_ग_लिखोl(3, base + VSS_CLKRST);	/* निश्चित reset */
	wmb();
	__raw_ग_लिखोl(1, base + VSS_CLKRST);	/* disable घड़ी */
	wmb();
	__raw_ग_लिखोl(0, base + VSS_FTR);	/* disable all footers */
	wmb();
पूर्ण

व्योम au1300_vss_block_control(पूर्णांक block, पूर्णांक enable)
अणु
	अचिन्हित दीर्घ flags;

	अगर (alchemy_get_cputype() != ALCHEMY_CPU_AU1300)
		वापस;

	/* only one block at a समय */
	spin_lock_irqsave(&au1300_vss_lock, flags);
	अगर (enable)
		__enable_block(block);
	अन्यथा
		__disable_block(block);
	spin_unlock_irqrestore(&au1300_vss_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(au1300_vss_block_control);
