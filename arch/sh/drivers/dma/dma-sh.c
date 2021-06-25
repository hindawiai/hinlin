<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/drivers/dma/dma-sh.c
 *
 * SuperH On-chip DMAC Support
 *
 * Copyright (C) 2000 Takashi YOSHII
 * Copyright (C) 2003, 2004 Paul Mundt
 * Copyright (C) 2005 Andriy Skulysh
 */
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <mach-dreamcast/mach/dma.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/dma-रेजिस्टर.h>
#समावेश <cpu/dma-रेजिस्टर.h>
#समावेश <cpu/dma.h>

/*
 * Define the शेष configuration क्रम dual address memory-memory transfer.
 * The 0x400 value represents स्वतः-request, बाह्यal->बाह्यal.
 */
#घोषणा RS_DUAL	(DM_INC | SM_INC | RS_AUTO | TS_INDEX2VAL(XMIT_SZ_32BIT))

अटल अचिन्हित दीर्घ dma_find_base(अचिन्हित पूर्णांक chan)
अणु
	अचिन्हित दीर्घ base = SH_DMAC_BASE0;

#अगर_घोषित SH_DMAC_BASE1
	अगर (chan >= 6)
		base = SH_DMAC_BASE1;
#पूर्ण_अगर

	वापस base;
पूर्ण

अटल अचिन्हित दीर्घ dma_base_addr(अचिन्हित पूर्णांक chan)
अणु
	अचिन्हित दीर्घ base = dma_find_base(chan);

	/* Normalize offset calculation */
	अगर (chan >= 9)
		chan -= 6;
	अगर (chan >= 4)
		base += 0x10;

	वापस base + (chan * 0x10);
पूर्ण

#अगर_घोषित CONFIG_SH_DMA_IRQ_MULTI
अटल अंतरभूत अचिन्हित पूर्णांक get_dmte_irq(अचिन्हित पूर्णांक chan)
अणु
	वापस chan >= 6 ? DMTE6_IRQ : DMTE0_IRQ;
पूर्ण
#अन्यथा

अटल अचिन्हित पूर्णांक dmte_irq_map[] = अणु
	DMTE0_IRQ, DMTE0_IRQ + 1, DMTE0_IRQ + 2, DMTE0_IRQ + 3,

#अगर_घोषित DMTE4_IRQ
	DMTE4_IRQ, DMTE4_IRQ + 1,
#पूर्ण_अगर

#अगर_घोषित DMTE6_IRQ
	DMTE6_IRQ, DMTE6_IRQ + 1,
#पूर्ण_अगर

#अगर_घोषित DMTE8_IRQ
	DMTE8_IRQ, DMTE9_IRQ, DMTE10_IRQ, DMTE11_IRQ,
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक get_dmte_irq(अचिन्हित पूर्णांक chan)
अणु
	वापस dmte_irq_map[chan];
पूर्ण
#पूर्ण_अगर

/*
 * We determine the correct shअगरt size based off of the CHCR transmit size
 * क्रम the given channel. Since we know that it will take:
 *
 *	info->count >> ts_shअगरt[transmit_size]
 *
 * iterations to complete the transfer.
 */
अटल अचिन्हित पूर्णांक ts_shअगरt[] = TS_SHIFT;

अटल अंतरभूत अचिन्हित पूर्णांक calc_xmit_shअगरt(काष्ठा dma_channel *chan)
अणु
	u32 chcr = __raw_पढ़ोl(dma_base_addr(chan->chan) + CHCR);
	पूर्णांक cnt = ((chcr & CHCR_TS_LOW_MASK) >> CHCR_TS_LOW_SHIFT) |
		((chcr & CHCR_TS_HIGH_MASK) >> CHCR_TS_HIGH_SHIFT);

	वापस ts_shअगरt[cnt];
पूर्ण

/*
 * The transfer end पूर्णांकerrupt must पढ़ो the chcr रेजिस्टर to end the
 * hardware पूर्णांकerrupt active condition.
 * Besides that it needs to waken any रुकोing process, which should handle
 * setting up the next transfer.
 */
अटल irqवापस_t dma_tei(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा dma_channel *chan = dev_id;
	u32 chcr;

	chcr = __raw_पढ़ोl(dma_base_addr(chan->chan) + CHCR);

	अगर (!(chcr & CHCR_TE))
		वापस IRQ_NONE;

	chcr &= ~(CHCR_IE | CHCR_DE);
	__raw_ग_लिखोl(chcr, (dma_base_addr(chan->chan) + CHCR));

	wake_up(&chan->रुको_queue);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sh_dmac_request_dma(काष्ठा dma_channel *chan)
अणु
	अगर (unlikely(!(chan->flags & DMA_TEI_CAPABLE)))
		वापस 0;

	वापस request_irq(get_dmte_irq(chan->chan), dma_tei, IRQF_SHARED,
			   chan->dev_id, chan);
पूर्ण

अटल व्योम sh_dmac_मुक्त_dma(काष्ठा dma_channel *chan)
अणु
	मुक्त_irq(get_dmte_irq(chan->chan), chan);
पूर्ण

अटल पूर्णांक
sh_dmac_configure_channel(काष्ठा dma_channel *chan, अचिन्हित दीर्घ chcr)
अणु
	अगर (!chcr)
		chcr = RS_DUAL | CHCR_IE;

	अगर (chcr & CHCR_IE) अणु
		chcr &= ~CHCR_IE;
		chan->flags |= DMA_TEI_CAPABLE;
	पूर्ण अन्यथा अणु
		chan->flags &= ~DMA_TEI_CAPABLE;
	पूर्ण

	__raw_ग_लिखोl(chcr, (dma_base_addr(chan->chan) + CHCR));

	chan->flags |= DMA_CONFIGURED;
	वापस 0;
पूर्ण

अटल व्योम sh_dmac_enable_dma(काष्ठा dma_channel *chan)
अणु
	पूर्णांक irq;
	u32 chcr;

	chcr = __raw_पढ़ोl(dma_base_addr(chan->chan) + CHCR);
	chcr |= CHCR_DE;

	अगर (chan->flags & DMA_TEI_CAPABLE)
		chcr |= CHCR_IE;

	__raw_ग_लिखोl(chcr, (dma_base_addr(chan->chan) + CHCR));

	अगर (chan->flags & DMA_TEI_CAPABLE) अणु
		irq = get_dmte_irq(chan->chan);
		enable_irq(irq);
	पूर्ण
पूर्ण

अटल व्योम sh_dmac_disable_dma(काष्ठा dma_channel *chan)
अणु
	पूर्णांक irq;
	u32 chcr;

	अगर (chan->flags & DMA_TEI_CAPABLE) अणु
		irq = get_dmte_irq(chan->chan);
		disable_irq(irq);
	पूर्ण

	chcr = __raw_पढ़ोl(dma_base_addr(chan->chan) + CHCR);
	chcr &= ~(CHCR_DE | CHCR_TE | CHCR_IE);
	__raw_ग_लिखोl(chcr, (dma_base_addr(chan->chan) + CHCR));
पूर्ण

अटल पूर्णांक sh_dmac_xfer_dma(काष्ठा dma_channel *chan)
अणु
	/*
	 * If we haven't pre-configured the channel with special flags, use
	 * the शेषs.
	 */
	अगर (unlikely(!(chan->flags & DMA_CONFIGURED)))
		sh_dmac_configure_channel(chan, 0);

	sh_dmac_disable_dma(chan);

	/*
	 * Single-address mode usage note!
	 *
	 * It's important that we don't accidentally ग_लिखो any value to SAR/DAR
	 * (this includes 0) that hasn't been directly specअगरied by the user अगर
	 * we're in single-address mode.
	 *
	 * In this हाल, only one address can be defined, anything अन्यथा will
	 * result in a DMA address error पूर्णांकerrupt (at least on the SH-4),
	 * which will subsequently halt the transfer.
	 *
	 * Channel 2 on the Dreamcast is a special हाल, as this is used क्रम
	 * cascading to the PVR2 DMAC. In this हाल, we still need to ग_लिखो
	 * SAR and DAR, regardless of value, in order क्रम cascading to work.
	 */
	अगर (chan->sar || (mach_is_dreamcast() &&
			  chan->chan == PVR2_CASCADE_CHAN))
		__raw_ग_लिखोl(chan->sar, (dma_base_addr(chan->chan) + SAR));
	अगर (chan->dar || (mach_is_dreamcast() &&
			  chan->chan == PVR2_CASCADE_CHAN))
		__raw_ग_लिखोl(chan->dar, (dma_base_addr(chan->chan) + DAR));

	__raw_ग_लिखोl(chan->count >> calc_xmit_shअगरt(chan),
		(dma_base_addr(chan->chan) + TCR));

	sh_dmac_enable_dma(chan);

	वापस 0;
पूर्ण

अटल पूर्णांक sh_dmac_get_dma_residue(काष्ठा dma_channel *chan)
अणु
	अगर (!(__raw_पढ़ोl(dma_base_addr(chan->chan) + CHCR) & CHCR_DE))
		वापस 0;

	वापस __raw_पढ़ोl(dma_base_addr(chan->chan) + TCR)
		 << calc_xmit_shअगरt(chan);
पूर्ण

/*
 * DMAOR handling
 */
#अगर defined(CONFIG_CPU_SUBTYPE_SH7723)	|| \
    defined(CONFIG_CPU_SUBTYPE_SH7724)	|| \
    defined(CONFIG_CPU_SUBTYPE_SH7780)	|| \
    defined(CONFIG_CPU_SUBTYPE_SH7785)
#घोषणा NR_DMAOR	2
#अन्यथा
#घोषणा NR_DMAOR	1
#पूर्ण_अगर

/*
 * DMAOR bases are broken out amongst channel groups. DMAOR0 manages
 * channels 0 - 5, DMAOR1 6 - 11 (optional).
 */
#घोषणा dmaor_पढ़ो_reg(n)		__raw_पढ़ोw(dma_find_base((n)*6))
#घोषणा dmaor_ग_लिखो_reg(n, data)	__raw_ग_लिखोw(data, dma_find_base(n)*6)

अटल अंतरभूत पूर्णांक dmaor_reset(पूर्णांक no)
अणु
	अचिन्हित दीर्घ dmaor = dmaor_पढ़ो_reg(no);

	/* Try to clear the error flags first, inहाल they are set */
	dmaor &= ~(DMAOR_NMIF | DMAOR_AE);
	dmaor_ग_लिखो_reg(no, dmaor);

	dmaor |= DMAOR_INIT;
	dmaor_ग_लिखो_reg(no, dmaor);

	/* See अगर we got an error again */
	अगर ((dmaor_पढ़ो_reg(no) & (DMAOR_AE | DMAOR_NMIF))) अणु
		prपूर्णांकk(KERN_ERR "dma-sh: Can't initialize DMAOR.\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * DMAE handling
 */
#अगर_घोषित CONFIG_CPU_SH4

#अगर defined(DMAE1_IRQ)
#घोषणा NR_DMAE		2
#अन्यथा
#घोषणा NR_DMAE		1
#पूर्ण_अगर

अटल स्थिर अक्षर *dmae_name[] = अणु
	"DMAC Address Error0",
	"DMAC Address Error1"
पूर्ण;

#अगर_घोषित CONFIG_SH_DMA_IRQ_MULTI
अटल अंतरभूत अचिन्हित पूर्णांक get_dma_error_irq(पूर्णांक n)
अणु
	वापस get_dmte_irq(n * 6);
पूर्ण
#अन्यथा

अटल अचिन्हित पूर्णांक dmae_irq_map[] = अणु
	DMAE0_IRQ,

#अगर_घोषित DMAE1_IRQ
	DMAE1_IRQ,
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक get_dma_error_irq(पूर्णांक n)
अणु
	वापस dmae_irq_map[n];
पूर्ण
#पूर्ण_अगर

अटल irqवापस_t dma_err(पूर्णांक irq, व्योम *dummy)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NR_DMAOR; i++)
		dmaor_reset(i);

	disable_irq(irq);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dmae_irq_init(व्योम)
अणु
	पूर्णांक n;

	क्रम (n = 0; n < NR_DMAE; n++) अणु
		पूर्णांक i = request_irq(get_dma_error_irq(n), dma_err,
				    IRQF_SHARED, dmae_name[n], (व्योम *)dmae_name[n]);
		अगर (unlikely(i < 0)) अणु
			prपूर्णांकk(KERN_ERR "%s request_irq fail\n", dmae_name[n]);
			वापस i;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dmae_irq_मुक्त(व्योम)
अणु
	पूर्णांक n;

	क्रम (n = 0; n < NR_DMAE; n++)
		मुक्त_irq(get_dma_error_irq(n), शून्य);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक dmae_irq_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम dmae_irq_मुक्त(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल काष्ठा dma_ops sh_dmac_ops = अणु
	.request	= sh_dmac_request_dma,
	.मुक्त		= sh_dmac_मुक्त_dma,
	.get_residue	= sh_dmac_get_dma_residue,
	.xfer		= sh_dmac_xfer_dma,
	.configure	= sh_dmac_configure_channel,
पूर्ण;

अटल काष्ठा dma_info sh_dmac_info = अणु
	.name		= "sh_dmac",
	.nr_channels	= CONFIG_NR_ONCHIP_DMA_CHANNELS,
	.ops		= &sh_dmac_ops,
	.flags		= DMAC_CHANNELS_TEI_CAPABLE,
पूर्ण;

अटल पूर्णांक __init sh_dmac_init(व्योम)
अणु
	काष्ठा dma_info *info = &sh_dmac_info;
	पूर्णांक i, rc;

	/*
	 * Initialize DMAE, क्रम parts that support it.
	 */
	rc = dmae_irq_init();
	अगर (unlikely(rc != 0))
		वापस rc;

	/*
	 * Initialize DMAOR, and clean up any error flags that may have
	 * been set.
	 */
	क्रम (i = 0; i < NR_DMAOR; i++) अणु
		rc = dmaor_reset(i);
		अगर (unlikely(rc != 0))
			वापस rc;
	पूर्ण

	वापस रेजिस्टर_dmac(info);
पूर्ण

अटल व्योम __निकास sh_dmac_निकास(व्योम)
अणु
	dmae_irq_मुक्त();
	unरेजिस्टर_dmac(&sh_dmac_info);
पूर्ण

subsys_initcall(sh_dmac_init);
module_निकास(sh_dmac_निकास);

MODULE_AUTHOR("Takashi YOSHII, Paul Mundt, Andriy Skulysh");
MODULE_DESCRIPTION("SuperH On-Chip DMAC Support");
MODULE_LICENSE("GPL v2");
