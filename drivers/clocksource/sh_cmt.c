<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SuperH Timer Support - CMT
 *
 *  Copyright (C) 2008 Magnus Damm
 */

#समावेश <linux/clk.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/sh_समयr.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#अगर_घोषित CONFIG_SUPERH
#समावेश <यंत्र/platक्रमm_early.h>
#पूर्ण_अगर

काष्ठा sh_cmt_device;

/*
 * The CMT comes in 5 dअगरferent identअगरied flavours, depending not only on the
 * SoC but also on the particular instance. The following table lists the मुख्य
 * अक्षरacteristics of those flavours.
 *
 *			16B	32B	32B-F	48B	R-Car Gen2
 * -----------------------------------------------------------------------------
 * Channels		2	1/4	1	6	2/8
 * Control Width	16	16	16	16	32
 * Counter Width	16	32	32	32/48	32/48
 * Shared Start/Stop	Y	Y	Y	Y	N
 *
 * The r8a73a4 / R-Car Gen2 version has a per-channel start/stop रेजिस्टर
 * located in the channel रेजिस्टरs block. All other versions have a shared
 * start/stop रेजिस्टर located in the global space.
 *
 * Channels are indexed from 0 to N-1 in the करोcumentation. The channel index
 * infers the start/stop bit position in the control रेजिस्टर and the channel
 * रेजिस्टरs block address. Some CMT instances have a subset of channels
 * available, in which हाल the index in the करोcumentation करोesn't match the
 * "real" index as implemented in hardware. This is क्रम instance the हाल with
 * CMT0 on r8a7740, which is a 32-bit variant with a single channel numbered 0
 * in the करोcumentation but using start/stop bit 5 and having its रेजिस्टरs
 * block at 0x60.
 *
 * Similarly CMT0 on r8a73a4, r8a7790 and r8a7791, जबतक implementing 32-bit
 * channels only, is a 48-bit gen2 CMT with the 48-bit channels unavailable.
 */

क्रमागत sh_cmt_model अणु
	SH_CMT_16BIT,
	SH_CMT_32BIT,
	SH_CMT_48BIT,
	SH_CMT0_RCAR_GEN2,
	SH_CMT1_RCAR_GEN2,
पूर्ण;

काष्ठा sh_cmt_info अणु
	क्रमागत sh_cmt_model model;

	अचिन्हित पूर्णांक channels_mask;

	अचिन्हित दीर्घ width; /* 16 or 32 bit version of hardware block */
	u32 overflow_bit;
	u32 clear_bits;

	/* callbacks क्रम CMSTR and CMCSR access */
	u32 (*पढ़ो_control)(व्योम __iomem *base, अचिन्हित दीर्घ offs);
	व्योम (*ग_लिखो_control)(व्योम __iomem *base, अचिन्हित दीर्घ offs,
			      u32 value);

	/* callbacks क्रम CMCNT and CMCOR access */
	u32 (*पढ़ो_count)(व्योम __iomem *base, अचिन्हित दीर्घ offs);
	व्योम (*ग_लिखो_count)(व्योम __iomem *base, अचिन्हित दीर्घ offs, u32 value);
पूर्ण;

काष्ठा sh_cmt_channel अणु
	काष्ठा sh_cmt_device *cmt;

	अचिन्हित पूर्णांक index;	/* Index in the करोcumentation */
	अचिन्हित पूर्णांक hwidx;	/* Real hardware index */

	व्योम __iomem *iostart;
	व्योम __iomem *ioctrl;

	अचिन्हित पूर्णांक समयr_bit;
	अचिन्हित दीर्घ flags;
	u32 match_value;
	u32 next_match_value;
	u32 max_match_value;
	raw_spinlock_t lock;
	काष्ठा घड़ी_event_device ced;
	काष्ठा घड़ीsource cs;
	u64 total_cycles;
	bool cs_enabled;
पूर्ण;

काष्ठा sh_cmt_device अणु
	काष्ठा platक्रमm_device *pdev;

	स्थिर काष्ठा sh_cmt_info *info;

	व्योम __iomem *mapbase;
	काष्ठा clk *clk;
	अचिन्हित दीर्घ rate;

	raw_spinlock_t lock; /* Protect the shared start/stop रेजिस्टर */

	काष्ठा sh_cmt_channel *channels;
	अचिन्हित पूर्णांक num_channels;
	अचिन्हित पूर्णांक hw_channels;

	bool has_घड़ीevent;
	bool has_घड़ीsource;
पूर्ण;

#घोषणा SH_CMT16_CMCSR_CMF		(1 << 7)
#घोषणा SH_CMT16_CMCSR_CMIE		(1 << 6)
#घोषणा SH_CMT16_CMCSR_CKS8		(0 << 0)
#घोषणा SH_CMT16_CMCSR_CKS32		(1 << 0)
#घोषणा SH_CMT16_CMCSR_CKS128		(2 << 0)
#घोषणा SH_CMT16_CMCSR_CKS512		(3 << 0)
#घोषणा SH_CMT16_CMCSR_CKS_MASK		(3 << 0)

#घोषणा SH_CMT32_CMCSR_CMF		(1 << 15)
#घोषणा SH_CMT32_CMCSR_OVF		(1 << 14)
#घोषणा SH_CMT32_CMCSR_WRFLG		(1 << 13)
#घोषणा SH_CMT32_CMCSR_STTF		(1 << 12)
#घोषणा SH_CMT32_CMCSR_STPF		(1 << 11)
#घोषणा SH_CMT32_CMCSR_SSIE		(1 << 10)
#घोषणा SH_CMT32_CMCSR_CMS		(1 << 9)
#घोषणा SH_CMT32_CMCSR_CMM		(1 << 8)
#घोषणा SH_CMT32_CMCSR_CMTOUT_IE	(1 << 7)
#घोषणा SH_CMT32_CMCSR_CMR_NONE		(0 << 4)
#घोषणा SH_CMT32_CMCSR_CMR_DMA		(1 << 4)
#घोषणा SH_CMT32_CMCSR_CMR_IRQ		(2 << 4)
#घोषणा SH_CMT32_CMCSR_CMR_MASK		(3 << 4)
#घोषणा SH_CMT32_CMCSR_DBGIVD		(1 << 3)
#घोषणा SH_CMT32_CMCSR_CKS_RCLK8	(4 << 0)
#घोषणा SH_CMT32_CMCSR_CKS_RCLK32	(5 << 0)
#घोषणा SH_CMT32_CMCSR_CKS_RCLK128	(6 << 0)
#घोषणा SH_CMT32_CMCSR_CKS_RCLK1	(7 << 0)
#घोषणा SH_CMT32_CMCSR_CKS_MASK		(7 << 0)

अटल u32 sh_cmt_पढ़ो16(व्योम __iomem *base, अचिन्हित दीर्घ offs)
अणु
	वापस ioपढ़ो16(base + (offs << 1));
पूर्ण

अटल u32 sh_cmt_पढ़ो32(व्योम __iomem *base, अचिन्हित दीर्घ offs)
अणु
	वापस ioपढ़ो32(base + (offs << 2));
पूर्ण

अटल व्योम sh_cmt_ग_लिखो16(व्योम __iomem *base, अचिन्हित दीर्घ offs, u32 value)
अणु
	ioग_लिखो16(value, base + (offs << 1));
पूर्ण

अटल व्योम sh_cmt_ग_लिखो32(व्योम __iomem *base, अचिन्हित दीर्घ offs, u32 value)
अणु
	ioग_लिखो32(value, base + (offs << 2));
पूर्ण

अटल स्थिर काष्ठा sh_cmt_info sh_cmt_info[] = अणु
	[SH_CMT_16BIT] = अणु
		.model = SH_CMT_16BIT,
		.width = 16,
		.overflow_bit = SH_CMT16_CMCSR_CMF,
		.clear_bits = ~SH_CMT16_CMCSR_CMF,
		.पढ़ो_control = sh_cmt_पढ़ो16,
		.ग_लिखो_control = sh_cmt_ग_लिखो16,
		.पढ़ो_count = sh_cmt_पढ़ो16,
		.ग_लिखो_count = sh_cmt_ग_लिखो16,
	पूर्ण,
	[SH_CMT_32BIT] = अणु
		.model = SH_CMT_32BIT,
		.width = 32,
		.overflow_bit = SH_CMT32_CMCSR_CMF,
		.clear_bits = ~(SH_CMT32_CMCSR_CMF | SH_CMT32_CMCSR_OVF),
		.पढ़ो_control = sh_cmt_पढ़ो16,
		.ग_लिखो_control = sh_cmt_ग_लिखो16,
		.पढ़ो_count = sh_cmt_पढ़ो32,
		.ग_लिखो_count = sh_cmt_ग_लिखो32,
	पूर्ण,
	[SH_CMT_48BIT] = अणु
		.model = SH_CMT_48BIT,
		.channels_mask = 0x3f,
		.width = 32,
		.overflow_bit = SH_CMT32_CMCSR_CMF,
		.clear_bits = ~(SH_CMT32_CMCSR_CMF | SH_CMT32_CMCSR_OVF),
		.पढ़ो_control = sh_cmt_पढ़ो32,
		.ग_लिखो_control = sh_cmt_ग_लिखो32,
		.पढ़ो_count = sh_cmt_पढ़ो32,
		.ग_लिखो_count = sh_cmt_ग_लिखो32,
	पूर्ण,
	[SH_CMT0_RCAR_GEN2] = अणु
		.model = SH_CMT0_RCAR_GEN2,
		.channels_mask = 0x60,
		.width = 32,
		.overflow_bit = SH_CMT32_CMCSR_CMF,
		.clear_bits = ~(SH_CMT32_CMCSR_CMF | SH_CMT32_CMCSR_OVF),
		.पढ़ो_control = sh_cmt_पढ़ो32,
		.ग_लिखो_control = sh_cmt_ग_लिखो32,
		.पढ़ो_count = sh_cmt_पढ़ो32,
		.ग_लिखो_count = sh_cmt_ग_लिखो32,
	पूर्ण,
	[SH_CMT1_RCAR_GEN2] = अणु
		.model = SH_CMT1_RCAR_GEN2,
		.channels_mask = 0xff,
		.width = 32,
		.overflow_bit = SH_CMT32_CMCSR_CMF,
		.clear_bits = ~(SH_CMT32_CMCSR_CMF | SH_CMT32_CMCSR_OVF),
		.पढ़ो_control = sh_cmt_पढ़ो32,
		.ग_लिखो_control = sh_cmt_ग_लिखो32,
		.पढ़ो_count = sh_cmt_पढ़ो32,
		.ग_लिखो_count = sh_cmt_ग_लिखो32,
	पूर्ण,
पूर्ण;

#घोषणा CMCSR 0 /* channel रेजिस्टर */
#घोषणा CMCNT 1 /* channel रेजिस्टर */
#घोषणा CMCOR 2 /* channel रेजिस्टर */

#घोषणा CMCLKE	0x1000	/* CLK Enable Register (R-Car Gen2) */

अटल अंतरभूत u32 sh_cmt_पढ़ो_cmstr(काष्ठा sh_cmt_channel *ch)
अणु
	अगर (ch->iostart)
		वापस ch->cmt->info->पढ़ो_control(ch->iostart, 0);
	अन्यथा
		वापस ch->cmt->info->पढ़ो_control(ch->cmt->mapbase, 0);
पूर्ण

अटल अंतरभूत व्योम sh_cmt_ग_लिखो_cmstr(काष्ठा sh_cmt_channel *ch, u32 value)
अणु
	अगर (ch->iostart)
		ch->cmt->info->ग_लिखो_control(ch->iostart, 0, value);
	अन्यथा
		ch->cmt->info->ग_लिखो_control(ch->cmt->mapbase, 0, value);
पूर्ण

अटल अंतरभूत u32 sh_cmt_पढ़ो_cmcsr(काष्ठा sh_cmt_channel *ch)
अणु
	वापस ch->cmt->info->पढ़ो_control(ch->ioctrl, CMCSR);
पूर्ण

अटल अंतरभूत व्योम sh_cmt_ग_लिखो_cmcsr(काष्ठा sh_cmt_channel *ch, u32 value)
अणु
	ch->cmt->info->ग_लिखो_control(ch->ioctrl, CMCSR, value);
पूर्ण

अटल अंतरभूत u32 sh_cmt_पढ़ो_cmcnt(काष्ठा sh_cmt_channel *ch)
अणु
	वापस ch->cmt->info->पढ़ो_count(ch->ioctrl, CMCNT);
पूर्ण

अटल अंतरभूत व्योम sh_cmt_ग_लिखो_cmcnt(काष्ठा sh_cmt_channel *ch, u32 value)
अणु
	ch->cmt->info->ग_लिखो_count(ch->ioctrl, CMCNT, value);
पूर्ण

अटल अंतरभूत व्योम sh_cmt_ग_लिखो_cmcor(काष्ठा sh_cmt_channel *ch, u32 value)
अणु
	ch->cmt->info->ग_लिखो_count(ch->ioctrl, CMCOR, value);
पूर्ण

अटल u32 sh_cmt_get_counter(काष्ठा sh_cmt_channel *ch, u32 *has_wrapped)
अणु
	u32 v1, v2, v3;
	u32 o1, o2;

	o1 = sh_cmt_पढ़ो_cmcsr(ch) & ch->cmt->info->overflow_bit;

	/* Make sure the समयr value is stable. Stolen from acpi_pm.c */
	करो अणु
		o2 = o1;
		v1 = sh_cmt_पढ़ो_cmcnt(ch);
		v2 = sh_cmt_पढ़ो_cmcnt(ch);
		v3 = sh_cmt_पढ़ो_cmcnt(ch);
		o1 = sh_cmt_पढ़ो_cmcsr(ch) & ch->cmt->info->overflow_bit;
	पूर्ण जबतक (unlikely((o1 != o2) || (v1 > v2 && v1 < v3)
			  || (v2 > v3 && v2 < v1) || (v3 > v1 && v3 < v2)));

	*has_wrapped = o1;
	वापस v2;
पूर्ण

अटल व्योम sh_cmt_start_stop_ch(काष्ठा sh_cmt_channel *ch, पूर्णांक start)
अणु
	अचिन्हित दीर्घ flags;
	u32 value;

	/* start stop रेजिस्टर shared by multiple समयr channels */
	raw_spin_lock_irqsave(&ch->cmt->lock, flags);
	value = sh_cmt_पढ़ो_cmstr(ch);

	अगर (start)
		value |= 1 << ch->समयr_bit;
	अन्यथा
		value &= ~(1 << ch->समयr_bit);

	sh_cmt_ग_लिखो_cmstr(ch, value);
	raw_spin_unlock_irqrestore(&ch->cmt->lock, flags);
पूर्ण

अटल पूर्णांक sh_cmt_enable(काष्ठा sh_cmt_channel *ch)
अणु
	पूर्णांक k, ret;

	dev_pm_syscore_device(&ch->cmt->pdev->dev, true);

	/* enable घड़ी */
	ret = clk_enable(ch->cmt->clk);
	अगर (ret) अणु
		dev_err(&ch->cmt->pdev->dev, "ch%u: cannot enable clock\n",
			ch->index);
		जाओ err0;
	पूर्ण

	/* make sure channel is disabled */
	sh_cmt_start_stop_ch(ch, 0);

	/* configure channel, periodic mode and maximum समयout */
	अगर (ch->cmt->info->width == 16) अणु
		sh_cmt_ग_लिखो_cmcsr(ch, SH_CMT16_CMCSR_CMIE |
				   SH_CMT16_CMCSR_CKS512);
	पूर्ण अन्यथा अणु
		u32 cmtout = ch->cmt->info->model <= SH_CMT_48BIT ?
			      SH_CMT32_CMCSR_CMTOUT_IE : 0;
		sh_cmt_ग_लिखो_cmcsr(ch, cmtout | SH_CMT32_CMCSR_CMM |
				   SH_CMT32_CMCSR_CMR_IRQ |
				   SH_CMT32_CMCSR_CKS_RCLK8);
	पूर्ण

	sh_cmt_ग_लिखो_cmcor(ch, 0xffffffff);
	sh_cmt_ग_लिखो_cmcnt(ch, 0);

	/*
	 * According to the sh73a0 user's manual, as CMCNT can be operated
	 * only by the RCLK (Pseuकरो 32 kHz), there's one restriction on
	 * modअगरying CMCNT रेजिस्टर; two RCLK cycles are necessary beक्रमe
	 * this रेजिस्टर is either पढ़ो or any modअगरication of the value
	 * it holds is reflected in the LSI's actual operation.
	 *
	 * While at it, we're supposed to clear out the CMCNT as of this
	 * moment, so make sure it's processed properly here.  This will
	 * take RCLKx2 at maximum.
	 */
	क्रम (k = 0; k < 100; k++) अणु
		अगर (!sh_cmt_पढ़ो_cmcnt(ch))
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (sh_cmt_पढ़ो_cmcnt(ch)) अणु
		dev_err(&ch->cmt->pdev->dev, "ch%u: cannot clear CMCNT\n",
			ch->index);
		ret = -ETIMEDOUT;
		जाओ err1;
	पूर्ण

	/* enable channel */
	sh_cmt_start_stop_ch(ch, 1);
	वापस 0;
 err1:
	/* stop घड़ी */
	clk_disable(ch->cmt->clk);

 err0:
	वापस ret;
पूर्ण

अटल व्योम sh_cmt_disable(काष्ठा sh_cmt_channel *ch)
अणु
	/* disable channel */
	sh_cmt_start_stop_ch(ch, 0);

	/* disable पूर्णांकerrupts in CMT block */
	sh_cmt_ग_लिखो_cmcsr(ch, 0);

	/* stop घड़ी */
	clk_disable(ch->cmt->clk);

	dev_pm_syscore_device(&ch->cmt->pdev->dev, false);
पूर्ण

/* निजी flags */
#घोषणा FLAG_CLOCKEVENT (1 << 0)
#घोषणा FLAG_CLOCKSOURCE (1 << 1)
#घोषणा FLAG_REPROGRAM (1 << 2)
#घोषणा FLAG_SKIPEVENT (1 << 3)
#घोषणा FLAG_IRQCONTEXT (1 << 4)

अटल व्योम sh_cmt_घड़ी_event_program_verअगरy(काष्ठा sh_cmt_channel *ch,
					      पूर्णांक असलolute)
अणु
	u32 value = ch->next_match_value;
	u32 new_match;
	u32 delay = 0;
	u32 now = 0;
	u32 has_wrapped;

	now = sh_cmt_get_counter(ch, &has_wrapped);
	ch->flags |= FLAG_REPROGRAM; /* क्रमce reprogram */

	अगर (has_wrapped) अणु
		/* we're competing with the पूर्णांकerrupt handler.
		 *  -> let the पूर्णांकerrupt handler reprogram the समयr.
		 *  -> पूर्णांकerrupt number two handles the event.
		 */
		ch->flags |= FLAG_SKIPEVENT;
		वापस;
	पूर्ण

	अगर (असलolute)
		now = 0;

	करो अणु
		/* reprogram the समयr hardware,
		 * but करोn't save the new match value yet.
		 */
		new_match = now + value + delay;
		अगर (new_match > ch->max_match_value)
			new_match = ch->max_match_value;

		sh_cmt_ग_लिखो_cmcor(ch, new_match);

		now = sh_cmt_get_counter(ch, &has_wrapped);
		अगर (has_wrapped && (new_match > ch->match_value)) अणु
			/* we are changing to a greater match value,
			 * so this wrap must be caused by the counter
			 * matching the old value.
			 * -> first पूर्णांकerrupt reprograms the समयr.
			 * -> पूर्णांकerrupt number two handles the event.
			 */
			ch->flags |= FLAG_SKIPEVENT;
			अवरोध;
		पूर्ण

		अगर (has_wrapped) अणु
			/* we are changing to a smaller match value,
			 * so the wrap must be caused by the counter
			 * matching the new value.
			 * -> save programmed match value.
			 * -> let isr handle the event.
			 */
			ch->match_value = new_match;
			अवरोध;
		पूर्ण

		/* be safe: verअगरy hardware settings */
		अगर (now < new_match) अणु
			/* समयr value is below match value, all good.
			 * this makes sure we won't miss any match events.
			 * -> save programmed match value.
			 * -> let isr handle the event.
			 */
			ch->match_value = new_match;
			अवरोध;
		पूर्ण

		/* the counter has reached a value greater
		 * than our new match value. and since the
		 * has_wrapped flag isn't set we must have
		 * programmed a too बंद event.
		 * -> increase delay and retry.
		 */
		अगर (delay)
			delay <<= 1;
		अन्यथा
			delay = 1;

		अगर (!delay)
			dev_warn(&ch->cmt->pdev->dev, "ch%u: too long delay\n",
				 ch->index);

	पूर्ण जबतक (delay);
पूर्ण

अटल व्योम __sh_cmt_set_next(काष्ठा sh_cmt_channel *ch, अचिन्हित दीर्घ delta)
अणु
	अगर (delta > ch->max_match_value)
		dev_warn(&ch->cmt->pdev->dev, "ch%u: delta out of range\n",
			 ch->index);

	ch->next_match_value = delta;
	sh_cmt_घड़ी_event_program_verअगरy(ch, 0);
पूर्ण

अटल व्योम sh_cmt_set_next(काष्ठा sh_cmt_channel *ch, अचिन्हित दीर्घ delta)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&ch->lock, flags);
	__sh_cmt_set_next(ch, delta);
	raw_spin_unlock_irqrestore(&ch->lock, flags);
पूर्ण

अटल irqवापस_t sh_cmt_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sh_cmt_channel *ch = dev_id;

	/* clear flags */
	sh_cmt_ग_लिखो_cmcsr(ch, sh_cmt_पढ़ो_cmcsr(ch) &
			   ch->cmt->info->clear_bits);

	/* update घड़ी source counter to begin with अगर enabled
	 * the wrap flag should be cleared by the समयr specअगरic
	 * isr beक्रमe we end up here.
	 */
	अगर (ch->flags & FLAG_CLOCKSOURCE)
		ch->total_cycles += ch->match_value + 1;

	अगर (!(ch->flags & FLAG_REPROGRAM))
		ch->next_match_value = ch->max_match_value;

	ch->flags |= FLAG_IRQCONTEXT;

	अगर (ch->flags & FLAG_CLOCKEVENT) अणु
		अगर (!(ch->flags & FLAG_SKIPEVENT)) अणु
			अगर (घड़ीevent_state_oneshot(&ch->ced)) अणु
				ch->next_match_value = ch->max_match_value;
				ch->flags |= FLAG_REPROGRAM;
			पूर्ण

			ch->ced.event_handler(&ch->ced);
		पूर्ण
	पूर्ण

	ch->flags &= ~FLAG_SKIPEVENT;

	अगर (ch->flags & FLAG_REPROGRAM) अणु
		ch->flags &= ~FLAG_REPROGRAM;
		sh_cmt_घड़ी_event_program_verअगरy(ch, 1);

		अगर (ch->flags & FLAG_CLOCKEVENT)
			अगर ((घड़ीevent_state_shutकरोwn(&ch->ced))
			    || (ch->match_value == ch->next_match_value))
				ch->flags &= ~FLAG_REPROGRAM;
	पूर्ण

	ch->flags &= ~FLAG_IRQCONTEXT;

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sh_cmt_start(काष्ठा sh_cmt_channel *ch, अचिन्हित दीर्घ flag)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	अगर (flag & FLAG_CLOCKSOURCE)
		pm_runसमय_get_sync(&ch->cmt->pdev->dev);

	raw_spin_lock_irqsave(&ch->lock, flags);

	अगर (!(ch->flags & (FLAG_CLOCKEVENT | FLAG_CLOCKSOURCE))) अणु
		अगर (flag & FLAG_CLOCKEVENT)
			pm_runसमय_get_sync(&ch->cmt->pdev->dev);
		ret = sh_cmt_enable(ch);
	पूर्ण

	अगर (ret)
		जाओ out;
	ch->flags |= flag;

	/* setup समयout अगर no घड़ीevent */
	अगर ((flag == FLAG_CLOCKSOURCE) && (!(ch->flags & FLAG_CLOCKEVENT)))
		__sh_cmt_set_next(ch, ch->max_match_value);
 out:
	raw_spin_unlock_irqrestore(&ch->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम sh_cmt_stop(काष्ठा sh_cmt_channel *ch, अचिन्हित दीर्घ flag)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ f;

	raw_spin_lock_irqsave(&ch->lock, flags);

	f = ch->flags & (FLAG_CLOCKEVENT | FLAG_CLOCKSOURCE);
	ch->flags &= ~flag;

	अगर (f && !(ch->flags & (FLAG_CLOCKEVENT | FLAG_CLOCKSOURCE))) अणु
		sh_cmt_disable(ch);
		अगर (flag & FLAG_CLOCKEVENT)
			pm_runसमय_put(&ch->cmt->pdev->dev);
	पूर्ण

	/* adjust the समयout to maximum अगर only घड़ीsource left */
	अगर ((flag == FLAG_CLOCKEVENT) && (ch->flags & FLAG_CLOCKSOURCE))
		__sh_cmt_set_next(ch, ch->max_match_value);

	raw_spin_unlock_irqrestore(&ch->lock, flags);

	अगर (flag & FLAG_CLOCKSOURCE)
		pm_runसमय_put(&ch->cmt->pdev->dev);
पूर्ण

अटल काष्ठा sh_cmt_channel *cs_to_sh_cmt(काष्ठा घड़ीsource *cs)
अणु
	वापस container_of(cs, काष्ठा sh_cmt_channel, cs);
पूर्ण

अटल u64 sh_cmt_घड़ीsource_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	काष्ठा sh_cmt_channel *ch = cs_to_sh_cmt(cs);
	अचिन्हित दीर्घ flags;
	u32 has_wrapped;
	u64 value;
	u32 raw;

	raw_spin_lock_irqsave(&ch->lock, flags);
	value = ch->total_cycles;
	raw = sh_cmt_get_counter(ch, &has_wrapped);

	अगर (unlikely(has_wrapped))
		raw += ch->match_value + 1;
	raw_spin_unlock_irqrestore(&ch->lock, flags);

	वापस value + raw;
पूर्ण

अटल पूर्णांक sh_cmt_घड़ीsource_enable(काष्ठा घड़ीsource *cs)
अणु
	पूर्णांक ret;
	काष्ठा sh_cmt_channel *ch = cs_to_sh_cmt(cs);

	WARN_ON(ch->cs_enabled);

	ch->total_cycles = 0;

	ret = sh_cmt_start(ch, FLAG_CLOCKSOURCE);
	अगर (!ret)
		ch->cs_enabled = true;

	वापस ret;
पूर्ण

अटल व्योम sh_cmt_घड़ीsource_disable(काष्ठा घड़ीsource *cs)
अणु
	काष्ठा sh_cmt_channel *ch = cs_to_sh_cmt(cs);

	WARN_ON(!ch->cs_enabled);

	sh_cmt_stop(ch, FLAG_CLOCKSOURCE);
	ch->cs_enabled = false;
पूर्ण

अटल व्योम sh_cmt_घड़ीsource_suspend(काष्ठा घड़ीsource *cs)
अणु
	काष्ठा sh_cmt_channel *ch = cs_to_sh_cmt(cs);

	अगर (!ch->cs_enabled)
		वापस;

	sh_cmt_stop(ch, FLAG_CLOCKSOURCE);
	dev_pm_genpd_suspend(&ch->cmt->pdev->dev);
पूर्ण

अटल व्योम sh_cmt_घड़ीsource_resume(काष्ठा घड़ीsource *cs)
अणु
	काष्ठा sh_cmt_channel *ch = cs_to_sh_cmt(cs);

	अगर (!ch->cs_enabled)
		वापस;

	dev_pm_genpd_resume(&ch->cmt->pdev->dev);
	sh_cmt_start(ch, FLAG_CLOCKSOURCE);
पूर्ण

अटल पूर्णांक sh_cmt_रेजिस्टर_घड़ीsource(काष्ठा sh_cmt_channel *ch,
				       स्थिर अक्षर *name)
अणु
	काष्ठा घड़ीsource *cs = &ch->cs;

	cs->name = name;
	cs->rating = 125;
	cs->पढ़ो = sh_cmt_घड़ीsource_पढ़ो;
	cs->enable = sh_cmt_घड़ीsource_enable;
	cs->disable = sh_cmt_घड़ीsource_disable;
	cs->suspend = sh_cmt_घड़ीsource_suspend;
	cs->resume = sh_cmt_घड़ीsource_resume;
	cs->mask = CLOCKSOURCE_MASK(माप(u64) * 8);
	cs->flags = CLOCK_SOURCE_IS_CONTINUOUS;

	dev_info(&ch->cmt->pdev->dev, "ch%u: used as clock source\n",
		 ch->index);

	घड़ीsource_रेजिस्टर_hz(cs, ch->cmt->rate);
	वापस 0;
पूर्ण

अटल काष्ठा sh_cmt_channel *ced_to_sh_cmt(काष्ठा घड़ी_event_device *ced)
अणु
	वापस container_of(ced, काष्ठा sh_cmt_channel, ced);
पूर्ण

अटल व्योम sh_cmt_घड़ी_event_start(काष्ठा sh_cmt_channel *ch, पूर्णांक periodic)
अणु
	sh_cmt_start(ch, FLAG_CLOCKEVENT);

	अगर (periodic)
		sh_cmt_set_next(ch, ((ch->cmt->rate + HZ/2) / HZ) - 1);
	अन्यथा
		sh_cmt_set_next(ch, ch->max_match_value);
पूर्ण

अटल पूर्णांक sh_cmt_घड़ी_event_shutकरोwn(काष्ठा घड़ी_event_device *ced)
अणु
	काष्ठा sh_cmt_channel *ch = ced_to_sh_cmt(ced);

	sh_cmt_stop(ch, FLAG_CLOCKEVENT);
	वापस 0;
पूर्ण

अटल पूर्णांक sh_cmt_घड़ी_event_set_state(काष्ठा घड़ी_event_device *ced,
					पूर्णांक periodic)
अणु
	काष्ठा sh_cmt_channel *ch = ced_to_sh_cmt(ced);

	/* deal with old setting first */
	अगर (घड़ीevent_state_oneshot(ced) || घड़ीevent_state_periodic(ced))
		sh_cmt_stop(ch, FLAG_CLOCKEVENT);

	dev_info(&ch->cmt->pdev->dev, "ch%u: used for %s clock events\n",
		 ch->index, periodic ? "periodic" : "oneshot");
	sh_cmt_घड़ी_event_start(ch, periodic);
	वापस 0;
पूर्ण

अटल पूर्णांक sh_cmt_घड़ी_event_set_oneshot(काष्ठा घड़ी_event_device *ced)
अणु
	वापस sh_cmt_घड़ी_event_set_state(ced, 0);
पूर्ण

अटल पूर्णांक sh_cmt_घड़ी_event_set_periodic(काष्ठा घड़ी_event_device *ced)
अणु
	वापस sh_cmt_घड़ी_event_set_state(ced, 1);
पूर्ण

अटल पूर्णांक sh_cmt_घड़ी_event_next(अचिन्हित दीर्घ delta,
				   काष्ठा घड़ी_event_device *ced)
अणु
	काष्ठा sh_cmt_channel *ch = ced_to_sh_cmt(ced);

	BUG_ON(!घड़ीevent_state_oneshot(ced));
	अगर (likely(ch->flags & FLAG_IRQCONTEXT))
		ch->next_match_value = delta - 1;
	अन्यथा
		sh_cmt_set_next(ch, delta - 1);

	वापस 0;
पूर्ण

अटल व्योम sh_cmt_घड़ी_event_suspend(काष्ठा घड़ी_event_device *ced)
अणु
	काष्ठा sh_cmt_channel *ch = ced_to_sh_cmt(ced);

	dev_pm_genpd_suspend(&ch->cmt->pdev->dev);
	clk_unprepare(ch->cmt->clk);
पूर्ण

अटल व्योम sh_cmt_घड़ी_event_resume(काष्ठा घड़ी_event_device *ced)
अणु
	काष्ठा sh_cmt_channel *ch = ced_to_sh_cmt(ced);

	clk_prepare(ch->cmt->clk);
	dev_pm_genpd_resume(&ch->cmt->pdev->dev);
पूर्ण

अटल पूर्णांक sh_cmt_रेजिस्टर_घड़ीevent(काष्ठा sh_cmt_channel *ch,
				      स्थिर अक्षर *name)
अणु
	काष्ठा घड़ी_event_device *ced = &ch->ced;
	पूर्णांक irq;
	पूर्णांक ret;

	irq = platक्रमm_get_irq(ch->cmt->pdev, ch->index);
	अगर (irq < 0)
		वापस irq;

	ret = request_irq(irq, sh_cmt_पूर्णांकerrupt,
			  IRQF_TIMER | IRQF_IRQPOLL | IRQF_NOBALANCING,
			  dev_name(&ch->cmt->pdev->dev), ch);
	अगर (ret) अणु
		dev_err(&ch->cmt->pdev->dev, "ch%u: failed to request irq %d\n",
			ch->index, irq);
		वापस ret;
	पूर्ण

	ced->name = name;
	ced->features = CLOCK_EVT_FEAT_PERIODIC;
	ced->features |= CLOCK_EVT_FEAT_ONESHOT;
	ced->rating = 125;
	ced->cpumask = cpu_possible_mask;
	ced->set_next_event = sh_cmt_घड़ी_event_next;
	ced->set_state_shutकरोwn = sh_cmt_घड़ी_event_shutकरोwn;
	ced->set_state_periodic = sh_cmt_घड़ी_event_set_periodic;
	ced->set_state_oneshot = sh_cmt_घड़ी_event_set_oneshot;
	ced->suspend = sh_cmt_घड़ी_event_suspend;
	ced->resume = sh_cmt_घड़ी_event_resume;

	/* TODO: calculate good shअगरt from rate and counter bit width */
	ced->shअगरt = 32;
	ced->mult = भाग_sc(ch->cmt->rate, NSEC_PER_SEC, ced->shअगरt);
	ced->max_delta_ns = घड़ीevent_delta2ns(ch->max_match_value, ced);
	ced->max_delta_ticks = ch->max_match_value;
	ced->min_delta_ns = घड़ीevent_delta2ns(0x1f, ced);
	ced->min_delta_ticks = 0x1f;

	dev_info(&ch->cmt->pdev->dev, "ch%u: used for clock events\n",
		 ch->index);
	घड़ीevents_रेजिस्टर_device(ced);

	वापस 0;
पूर्ण

अटल पूर्णांक sh_cmt_रेजिस्टर(काष्ठा sh_cmt_channel *ch, स्थिर अक्षर *name,
			   bool घड़ीevent, bool घड़ीsource)
अणु
	पूर्णांक ret;

	अगर (घड़ीevent) अणु
		ch->cmt->has_घड़ीevent = true;
		ret = sh_cmt_रेजिस्टर_घड़ीevent(ch, name);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (घड़ीsource) अणु
		ch->cmt->has_घड़ीsource = true;
		sh_cmt_रेजिस्टर_घड़ीsource(ch, name);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sh_cmt_setup_channel(काष्ठा sh_cmt_channel *ch, अचिन्हित पूर्णांक index,
				अचिन्हित पूर्णांक hwidx, bool घड़ीevent,
				bool घड़ीsource, काष्ठा sh_cmt_device *cmt)
अणु
	u32 value;
	पूर्णांक ret;

	/* Skip unused channels. */
	अगर (!घड़ीevent && !घड़ीsource)
		वापस 0;

	ch->cmt = cmt;
	ch->index = index;
	ch->hwidx = hwidx;
	ch->समयr_bit = hwidx;

	/*
	 * Compute the address of the channel control रेजिस्टर block. For the
	 * समयrs with a per-channel start/stop रेजिस्टर, compute its address
	 * as well.
	 */
	चयन (cmt->info->model) अणु
	हाल SH_CMT_16BIT:
		ch->ioctrl = cmt->mapbase + 2 + ch->hwidx * 6;
		अवरोध;
	हाल SH_CMT_32BIT:
	हाल SH_CMT_48BIT:
		ch->ioctrl = cmt->mapbase + 0x10 + ch->hwidx * 0x10;
		अवरोध;
	हाल SH_CMT0_RCAR_GEN2:
	हाल SH_CMT1_RCAR_GEN2:
		ch->iostart = cmt->mapbase + ch->hwidx * 0x100;
		ch->ioctrl = ch->iostart + 0x10;
		ch->समयr_bit = 0;

		/* Enable the घड़ी supply to the channel */
		value = ioपढ़ो32(cmt->mapbase + CMCLKE);
		value |= BIT(hwidx);
		ioग_लिखो32(value, cmt->mapbase + CMCLKE);
		अवरोध;
	पूर्ण

	अगर (cmt->info->width == (माप(ch->max_match_value) * 8))
		ch->max_match_value = ~0;
	अन्यथा
		ch->max_match_value = (1 << cmt->info->width) - 1;

	ch->match_value = ch->max_match_value;
	raw_spin_lock_init(&ch->lock);

	ret = sh_cmt_रेजिस्टर(ch, dev_name(&cmt->pdev->dev),
			      घड़ीevent, घड़ीsource);
	अगर (ret) अणु
		dev_err(&cmt->pdev->dev, "ch%u: registration failed\n",
			ch->index);
		वापस ret;
	पूर्ण
	ch->cs_enabled = false;

	वापस 0;
पूर्ण

अटल पूर्णांक sh_cmt_map_memory(काष्ठा sh_cmt_device *cmt)
अणु
	काष्ठा resource *mem;

	mem = platक्रमm_get_resource(cmt->pdev, IORESOURCE_MEM, 0);
	अगर (!mem) अणु
		dev_err(&cmt->pdev->dev, "failed to get I/O memory\n");
		वापस -ENXIO;
	पूर्ण

	cmt->mapbase = ioremap(mem->start, resource_size(mem));
	अगर (cmt->mapbase == शून्य) अणु
		dev_err(&cmt->pdev->dev, "failed to remap I/O memory\n");
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id sh_cmt_id_table[] = अणु
	अणु "sh-cmt-16", (kernel_uदीर्घ_t)&sh_cmt_info[SH_CMT_16BIT] पूर्ण,
	अणु "sh-cmt-32", (kernel_uदीर्घ_t)&sh_cmt_info[SH_CMT_32BIT] पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, sh_cmt_id_table);

अटल स्थिर काष्ठा of_device_id sh_cmt_of_table[] __maybe_unused = अणु
	अणु
		/* deprecated, preserved क्रम backward compatibility */
		.compatible = "renesas,cmt-48",
		.data = &sh_cmt_info[SH_CMT_48BIT]
	पूर्ण,
	अणु
		/* deprecated, preserved क्रम backward compatibility */
		.compatible = "renesas,cmt-48-gen2",
		.data = &sh_cmt_info[SH_CMT0_RCAR_GEN2]
	पूर्ण,
	अणु
		.compatible = "renesas,r8a7740-cmt1",
		.data = &sh_cmt_info[SH_CMT_48BIT]
	पूर्ण,
	अणु
		.compatible = "renesas,sh73a0-cmt1",
		.data = &sh_cmt_info[SH_CMT_48BIT]
	पूर्ण,
	अणु
		.compatible = "renesas,rcar-gen2-cmt0",
		.data = &sh_cmt_info[SH_CMT0_RCAR_GEN2]
	पूर्ण,
	अणु
		.compatible = "renesas,rcar-gen2-cmt1",
		.data = &sh_cmt_info[SH_CMT1_RCAR_GEN2]
	पूर्ण,
	अणु
		.compatible = "renesas,rcar-gen3-cmt0",
		.data = &sh_cmt_info[SH_CMT0_RCAR_GEN2]
	पूर्ण,
	अणु
		.compatible = "renesas,rcar-gen3-cmt1",
		.data = &sh_cmt_info[SH_CMT1_RCAR_GEN2]
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sh_cmt_of_table);

अटल पूर्णांक sh_cmt_setup(काष्ठा sh_cmt_device *cmt, काष्ठा platक्रमm_device *pdev)
अणु
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	cmt->pdev = pdev;
	raw_spin_lock_init(&cmt->lock);

	अगर (IS_ENABLED(CONFIG_OF) && pdev->dev.of_node) अणु
		cmt->info = of_device_get_match_data(&pdev->dev);
		cmt->hw_channels = cmt->info->channels_mask;
	पूर्ण अन्यथा अगर (pdev->dev.platक्रमm_data) अणु
		काष्ठा sh_समयr_config *cfg = pdev->dev.platक्रमm_data;
		स्थिर काष्ठा platक्रमm_device_id *id = pdev->id_entry;

		cmt->info = (स्थिर काष्ठा sh_cmt_info *)id->driver_data;
		cmt->hw_channels = cfg->channels_mask;
	पूर्ण अन्यथा अणु
		dev_err(&cmt->pdev->dev, "missing platform data\n");
		वापस -ENXIO;
	पूर्ण

	/* Get hold of घड़ी. */
	cmt->clk = clk_get(&cmt->pdev->dev, "fck");
	अगर (IS_ERR(cmt->clk)) अणु
		dev_err(&cmt->pdev->dev, "cannot get clock\n");
		वापस PTR_ERR(cmt->clk);
	पूर्ण

	ret = clk_prepare(cmt->clk);
	अगर (ret < 0)
		जाओ err_clk_put;

	/* Determine घड़ी rate. */
	ret = clk_enable(cmt->clk);
	अगर (ret < 0)
		जाओ err_clk_unprepare;

	अगर (cmt->info->width == 16)
		cmt->rate = clk_get_rate(cmt->clk) / 512;
	अन्यथा
		cmt->rate = clk_get_rate(cmt->clk) / 8;

	/* Map the memory resource(s). */
	ret = sh_cmt_map_memory(cmt);
	अगर (ret < 0)
		जाओ err_clk_disable;

	/* Allocate and setup the channels. */
	cmt->num_channels = hweight8(cmt->hw_channels);
	cmt->channels = kसुस्मृति(cmt->num_channels, माप(*cmt->channels),
				GFP_KERNEL);
	अगर (cmt->channels == शून्य) अणु
		ret = -ENOMEM;
		जाओ err_unmap;
	पूर्ण

	/*
	 * Use the first channel as a घड़ी event device and the second channel
	 * as a घड़ी source. If only one channel is available use it क्रम both.
	 */
	क्रम (i = 0, mask = cmt->hw_channels; i < cmt->num_channels; ++i) अणु
		अचिन्हित पूर्णांक hwidx = ffs(mask) - 1;
		bool घड़ीsource = i == 1 || cmt->num_channels == 1;
		bool घड़ीevent = i == 0;

		ret = sh_cmt_setup_channel(&cmt->channels[i], i, hwidx,
					   घड़ीevent, घड़ीsource, cmt);
		अगर (ret < 0)
			जाओ err_unmap;

		mask &= ~(1 << hwidx);
	पूर्ण

	clk_disable(cmt->clk);

	platक्रमm_set_drvdata(pdev, cmt);

	वापस 0;

err_unmap:
	kमुक्त(cmt->channels);
	iounmap(cmt->mapbase);
err_clk_disable:
	clk_disable(cmt->clk);
err_clk_unprepare:
	clk_unprepare(cmt->clk);
err_clk_put:
	clk_put(cmt->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक sh_cmt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sh_cmt_device *cmt = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	अगर (!is_sh_early_platक्रमm_device(pdev)) अणु
		pm_runसमय_set_active(&pdev->dev);
		pm_runसमय_enable(&pdev->dev);
	पूर्ण

	अगर (cmt) अणु
		dev_info(&pdev->dev, "kept as earlytimer\n");
		जाओ out;
	पूर्ण

	cmt = kzalloc(माप(*cmt), GFP_KERNEL);
	अगर (cmt == शून्य)
		वापस -ENOMEM;

	ret = sh_cmt_setup(cmt, pdev);
	अगर (ret) अणु
		kमुक्त(cmt);
		pm_runसमय_idle(&pdev->dev);
		वापस ret;
	पूर्ण
	अगर (is_sh_early_platक्रमm_device(pdev))
		वापस 0;

 out:
	अगर (cmt->has_घड़ीevent || cmt->has_घड़ीsource)
		pm_runसमय_irq_safe(&pdev->dev);
	अन्यथा
		pm_runसमय_idle(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sh_cmt_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस -EBUSY; /* cannot unरेजिस्टर घड़ीevent and घड़ीsource */
पूर्ण

अटल काष्ठा platक्रमm_driver sh_cmt_device_driver = अणु
	.probe		= sh_cmt_probe,
	.हटाओ		= sh_cmt_हटाओ,
	.driver		= अणु
		.name	= "sh_cmt",
		.of_match_table = of_match_ptr(sh_cmt_of_table),
	पूर्ण,
	.id_table	= sh_cmt_id_table,
पूर्ण;

अटल पूर्णांक __init sh_cmt_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&sh_cmt_device_driver);
पूर्ण

अटल व्योम __निकास sh_cmt_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&sh_cmt_device_driver);
पूर्ण

#अगर_घोषित CONFIG_SUPERH
sh_early_platक्रमm_init("earlytimer", &sh_cmt_device_driver);
#पूर्ण_अगर

subsys_initcall(sh_cmt_init);
module_निकास(sh_cmt_निकास);

MODULE_AUTHOR("Magnus Damm");
MODULE_DESCRIPTION("SuperH CMT Timer Driver");
MODULE_LICENSE("GPL v2");
