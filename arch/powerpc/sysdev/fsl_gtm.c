<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Freescale General-purpose Timers Module
 *
 * Copyright (c) Freescale Semiconductor, Inc. 2006.
 *               Shlomi Gridish <gridish@मुक्तscale.com>
 *               Jerry Huang <Chang-Ming.Huang@मुक्तscale.com>
 * Copyright (c) MontaVista Software, Inc. 2008.
 *               Anton Vorontsov <avorontsov@ru.mvista.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/list.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/fsl_gपंचांग.h>

#घोषणा GTCFR_STP(x)		((x) & 1 ? 1 << 5 : 1 << 1)
#घोषणा GTCFR_RST(x)		((x) & 1 ? 1 << 4 : 1 << 0)

#घोषणा GTMDR_ICLK_MASK		(3 << 1)
#घोषणा GTMDR_ICLK_ICAS		(0 << 1)
#घोषणा GTMDR_ICLK_ICLK		(1 << 1)
#घोषणा GTMDR_ICLK_SLGO		(2 << 1)
#घोषणा GTMDR_FRR		(1 << 3)
#घोषणा GTMDR_ORI		(1 << 4)
#घोषणा GTMDR_SPS(x)		((x) << 8)

काष्ठा gपंचांग_समयrs_regs अणु
	u8	gtcfr1;		/* Timer 1, Timer 2 global config रेजिस्टर */
	u8	res0[0x3];
	u8	gtcfr2;		/* Timer 3, समयr 4 global config रेजिस्टर */
	u8	res1[0xB];
	__be16	gपंचांगdr1;		/* Timer 1 mode रेजिस्टर */
	__be16	gपंचांगdr2;		/* Timer 2 mode रेजिस्टर */
	__be16	gtrfr1;		/* Timer 1 reference रेजिस्टर */
	__be16	gtrfr2;		/* Timer 2 reference रेजिस्टर */
	__be16	gtcpr1;		/* Timer 1 capture रेजिस्टर */
	__be16	gtcpr2;		/* Timer 2 capture रेजिस्टर */
	__be16	gtcnr1;		/* Timer 1 counter */
	__be16	gtcnr2;		/* Timer 2 counter */
	__be16	gपंचांगdr3;		/* Timer 3 mode रेजिस्टर */
	__be16	gपंचांगdr4;		/* Timer 4 mode रेजिस्टर */
	__be16	gtrfr3;		/* Timer 3 reference रेजिस्टर */
	__be16	gtrfr4;		/* Timer 4 reference रेजिस्टर */
	__be16	gtcpr3;		/* Timer 3 capture रेजिस्टर */
	__be16	gtcpr4;		/* Timer 4 capture रेजिस्टर */
	__be16	gtcnr3;		/* Timer 3 counter */
	__be16	gtcnr4;		/* Timer 4 counter */
	__be16	gtevr1;		/* Timer 1 event रेजिस्टर */
	__be16	gtevr2;		/* Timer 2 event रेजिस्टर */
	__be16	gtevr3;		/* Timer 3 event रेजिस्टर */
	__be16	gtevr4;		/* Timer 4 event रेजिस्टर */
	__be16	gtpsr1;		/* Timer 1 prescale रेजिस्टर */
	__be16	gtpsr2;		/* Timer 2 prescale रेजिस्टर */
	__be16	gtpsr3;		/* Timer 3 prescale रेजिस्टर */
	__be16	gtpsr4;		/* Timer 4 prescale रेजिस्टर */
	u8 res2[0x40];
पूर्ण __attribute__ ((packed));

काष्ठा gपंचांग अणु
	अचिन्हित पूर्णांक घड़ी;
	काष्ठा gपंचांग_समयrs_regs __iomem *regs;
	काष्ठा gपंचांग_समयr समयrs[4];
	spinlock_t lock;
	काष्ठा list_head list_node;
पूर्ण;

अटल LIST_HEAD(gपंचांगs);

/**
 * gपंचांग_get_समयr - request GTM समयr to use it with the rest of GTM API
 * Context:	non-IRQ
 *
 * This function reserves GTM समयr क्रम later use. It वापसs gपंचांग_समयr
 * काष्ठाure to use with the rest of GTM API, you should use समयr->irq
 * to manage समयr पूर्णांकerrupt.
 */
काष्ठा gपंचांग_समयr *gपंचांग_get_समयr16(व्योम)
अणु
	काष्ठा gपंचांग *gपंचांग = शून्य;
	पूर्णांक i;

	list_क्रम_each_entry(gपंचांग, &gपंचांगs, list_node) अणु
		spin_lock_irq(&gपंचांग->lock);

		क्रम (i = 0; i < ARRAY_SIZE(gपंचांग->समयrs); i++) अणु
			अगर (!gपंचांग->समयrs[i].requested) अणु
				gपंचांग->समयrs[i].requested = true;
				spin_unlock_irq(&gपंचांग->lock);
				वापस &gपंचांग->समयrs[i];
			पूर्ण
		पूर्ण

		spin_unlock_irq(&gपंचांग->lock);
	पूर्ण

	अगर (gपंचांग)
		वापस ERR_PTR(-EBUSY);
	वापस ERR_PTR(-ENODEV);
पूर्ण
EXPORT_SYMBOL(gपंचांग_get_समयr16);

/**
 * gपंचांग_get_specअगरic_समयr - request specअगरic GTM समयr
 * @gपंचांग:	specअगरic GTM, pass here GTM's device_node->data
 * @समयr:	specअगरic समयr number, Timer1 is 0.
 * Context:	non-IRQ
 *
 * This function reserves GTM समयr क्रम later use. It वापसs gपंचांग_समयr
 * काष्ठाure to use with the rest of GTM API, you should use समयr->irq
 * to manage समयr पूर्णांकerrupt.
 */
काष्ठा gपंचांग_समयr *gपंचांग_get_specअगरic_समयr16(काष्ठा gपंचांग *gपंचांग,
					   अचिन्हित पूर्णांक समयr)
अणु
	काष्ठा gपंचांग_समयr *ret = ERR_PTR(-EBUSY);

	अगर (समयr > 3)
		वापस ERR_PTR(-EINVAL);

	spin_lock_irq(&gपंचांग->lock);

	अगर (gपंचांग->समयrs[समयr].requested)
		जाओ out;

	ret = &gपंचांग->समयrs[समयr];
	ret->requested = true;

out:
	spin_unlock_irq(&gपंचांग->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(gपंचांग_get_specअगरic_समयr16);

/**
 * gपंचांग_put_समयr16 - release 16 bits GTM समयr
 * @पंचांगr:	poपूर्णांकer to the gपंचांग_समयr काष्ठाure obtained from gपंचांग_get_समयr
 * Context:	any
 *
 * This function releases GTM समयr so others may request it.
 */
व्योम gपंचांग_put_समयr16(काष्ठा gपंचांग_समयr *पंचांगr)
अणु
	gपंचांग_stop_समयr16(पंचांगr);

	spin_lock_irq(&पंचांगr->gपंचांग->lock);
	पंचांगr->requested = false;
	spin_unlock_irq(&पंचांगr->gपंचांग->lock);
पूर्ण
EXPORT_SYMBOL(gपंचांग_put_समयr16);

/*
 * This is back-end क्रम the exported functions, it's used to reset single
 * समयr in reference mode.
 */
अटल पूर्णांक gपंचांग_set_ref_समयr16(काष्ठा gपंचांग_समयr *पंचांगr, पूर्णांक frequency,
			       पूर्णांक reference_value, bool मुक्त_run)
अणु
	काष्ठा gपंचांग *gपंचांग = पंचांगr->gपंचांग;
	पूर्णांक num = पंचांगr - &gपंचांग->समयrs[0];
	अचिन्हित पूर्णांक prescaler;
	u8 iclk = GTMDR_ICLK_ICLK;
	u8 psr;
	u8 sps;
	अचिन्हित दीर्घ flags;
	पूर्णांक max_prescaler = 256 * 256 * 16;

	/* CPM2 करोesn't have primary prescaler */
	अगर (!पंचांगr->gtpsr)
		max_prescaler /= 256;

	prescaler = gपंचांग->घड़ी / frequency;
	/*
	 * We have two 8 bit prescalers -- primary and secondary (psr, sps),
	 * plus "slow go" mode (clk / 16). So, total prescale value is
	 * 16 * (psr + 1) * (sps + 1). Though, क्रम CPM2 GTMs we losing psr.
	 */
	अगर (prescaler > max_prescaler)
		वापस -EINVAL;

	अगर (prescaler > max_prescaler / 16) अणु
		iclk = GTMDR_ICLK_SLGO;
		prescaler /= 16;
	पूर्ण

	अगर (prescaler <= 256) अणु
		psr = 0;
		sps = prescaler - 1;
	पूर्ण अन्यथा अणु
		psr = 256 - 1;
		sps = prescaler / 256 - 1;
	पूर्ण

	spin_lock_irqsave(&gपंचांग->lock, flags);

	/*
	 * Properly reset समयrs: stop, reset, set up prescalers, reference
	 * value and clear event रेजिस्टर.
	 */
	clrsetbits_8(पंचांगr->gtcfr, ~(GTCFR_STP(num) | GTCFR_RST(num)),
				 GTCFR_STP(num) | GTCFR_RST(num));

	setbits8(पंचांगr->gtcfr, GTCFR_STP(num));

	अगर (पंचांगr->gtpsr)
		out_be16(पंचांगr->gtpsr, psr);
	clrsetbits_be16(पंचांगr->gपंचांगdr, 0xFFFF, iclk | GTMDR_SPS(sps) |
			GTMDR_ORI | (मुक्त_run ? GTMDR_FRR : 0));
	out_be16(पंचांगr->gtcnr, 0);
	out_be16(पंचांगr->gtrfr, reference_value);
	out_be16(पंचांगr->gtevr, 0xFFFF);

	/* Let it be. */
	clrbits8(पंचांगr->gtcfr, GTCFR_STP(num));

	spin_unlock_irqrestore(&gपंचांग->lock, flags);

	वापस 0;
पूर्ण

/**
 * gपंचांग_set_समयr16 - (re)set 16 bit समयr with arbitrary precision
 * @पंचांगr:	poपूर्णांकer to the gपंचांग_समयr काष्ठाure obtained from gपंचांग_get_समयr
 * @usec:	समयr पूर्णांकerval in microseconds
 * @reload:	अगर set, the समयr will reset upon expiry rather than
 *         	जारी running मुक्त.
 * Context:	any
 *
 * This function (re)sets the GTM समयr so that it counts up to the requested
 * पूर्णांकerval value, and fires the पूर्णांकerrupt when the value is reached. This
 * function will reduce the precision of the समयr as needed in order क्रम the
 * requested समयout to fit in a 16-bit रेजिस्टर.
 */
पूर्णांक gपंचांग_set_समयr16(काष्ठा gपंचांग_समयr *पंचांगr, अचिन्हित दीर्घ usec, bool reload)
अणु
	/* quite obvious, frequency which is enough क्रम तगSec precision */
	पूर्णांक freq = 1000000;
	अचिन्हित पूर्णांक bit;

	bit = fls_दीर्घ(usec);
	अगर (bit > 15) अणु
		freq >>= bit - 15;
		usec >>= bit - 15;
	पूर्ण

	अगर (!freq)
		वापस -EINVAL;

	वापस gपंचांग_set_ref_समयr16(पंचांगr, freq, usec, reload);
पूर्ण
EXPORT_SYMBOL(gपंचांग_set_समयr16);

/**
 * gपंचांग_set_exact_uसमयr16 - (re)set 16 bits समयr
 * @पंचांगr:	poपूर्णांकer to the gपंचांग_समयr काष्ठाure obtained from gपंचांग_get_समयr
 * @usec:	समयr पूर्णांकerval in microseconds
 * @reload:	अगर set, the समयr will reset upon expiry rather than
 *         	जारी running मुक्त.
 * Context:	any
 *
 * This function (re)sets GTM समयr so that it counts up to the requested
 * पूर्णांकerval value, and fires the पूर्णांकerrupt when the value is reached. If reload
 * flag was set, समयr will also reset itself upon reference value, otherwise
 * it जारीs to increment.
 *
 * The _exact_ bit in the function name states that this function will not
 * crop precision of the "usec" argument, thus usec is limited to 16 bits
 * (single समयr width).
 */
पूर्णांक gपंचांग_set_exact_समयr16(काष्ठा gपंचांग_समयr *पंचांगr, u16 usec, bool reload)
अणु
	/* quite obvious, frequency which is enough क्रम तगSec precision */
	स्थिर पूर्णांक freq = 1000000;

	/*
	 * We can lower the frequency (and probably घातer consumption) by
	 * भागiding both frequency and usec by 2 until there is no reमुख्यder.
	 * But we won't bother with this unless savings are measured, so just
	 * run the समयr as is.
	 */

	वापस gपंचांग_set_ref_समयr16(पंचांगr, freq, usec, reload);
पूर्ण
EXPORT_SYMBOL(gपंचांग_set_exact_समयr16);

/**
 * gपंचांग_stop_समयr16 - stop single समयr
 * @पंचांगr:	poपूर्णांकer to the gपंचांग_समयr काष्ठाure obtained from gपंचांग_get_समयr
 * Context:	any
 *
 * This function simply stops the GTM समयr.
 */
व्योम gपंचांग_stop_समयr16(काष्ठा gपंचांग_समयr *पंचांगr)
अणु
	काष्ठा gपंचांग *gपंचांग = पंचांगr->gपंचांग;
	पूर्णांक num = पंचांगr - &gपंचांग->समयrs[0];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gपंचांग->lock, flags);

	setbits8(पंचांगr->gtcfr, GTCFR_STP(num));
	out_be16(पंचांगr->gtevr, 0xFFFF);

	spin_unlock_irqrestore(&gपंचांग->lock, flags);
पूर्ण
EXPORT_SYMBOL(gपंचांग_stop_समयr16);

/**
 * gपंचांग_ack_समयr16 - acknowledge समयr event (मुक्त-run समयrs only)
 * @पंचांगr:	poपूर्णांकer to the gपंचांग_समयr काष्ठाure obtained from gपंचांग_get_समयr
 * @events:	events mask to ack
 * Context:	any
 *
 * Thus function used to acknowledge समयr पूर्णांकerrupt event, use it inside the
 * पूर्णांकerrupt handler.
 */
व्योम gपंचांग_ack_समयr16(काष्ठा gपंचांग_समयr *पंचांगr, u16 events)
अणु
	out_be16(पंचांगr->gtevr, events);
पूर्ण
EXPORT_SYMBOL(gपंचांग_ack_समयr16);

अटल व्योम __init gपंचांग_set_लघुcuts(काष्ठा device_node *np,
				     काष्ठा gपंचांग_समयr *समयrs,
				     काष्ठा gपंचांग_समयrs_regs __iomem *regs)
अणु
	/*
	 * Yeah, I करोn't like this either, but timers' रेजिस्टरs a bit messed,
	 * so we have to provide लघुcuts to ग_लिखो समयr independent code.
	 * Alternative option is to create gt*() accessors, but that will be
	 * even uglier and cryptic.
	 */
	समयrs[0].gtcfr = &regs->gtcfr1;
	समयrs[0].gपंचांगdr = &regs->gपंचांगdr1;
	समयrs[0].gtcnr = &regs->gtcnr1;
	समयrs[0].gtrfr = &regs->gtrfr1;
	समयrs[0].gtevr = &regs->gtevr1;

	समयrs[1].gtcfr = &regs->gtcfr1;
	समयrs[1].gपंचांगdr = &regs->gपंचांगdr2;
	समयrs[1].gtcnr = &regs->gtcnr2;
	समयrs[1].gtrfr = &regs->gtrfr2;
	समयrs[1].gtevr = &regs->gtevr2;

	समयrs[2].gtcfr = &regs->gtcfr2;
	समयrs[2].gपंचांगdr = &regs->gपंचांगdr3;
	समयrs[2].gtcnr = &regs->gtcnr3;
	समयrs[2].gtrfr = &regs->gtrfr3;
	समयrs[2].gtevr = &regs->gtevr3;

	समयrs[3].gtcfr = &regs->gtcfr2;
	समयrs[3].gपंचांगdr = &regs->gपंचांगdr4;
	समयrs[3].gtcnr = &regs->gtcnr4;
	समयrs[3].gtrfr = &regs->gtrfr4;
	समयrs[3].gtevr = &regs->gtevr4;

	/* CPM2 करोesn't have primary prescaler */
	अगर (!of_device_is_compatible(np, "fsl,cpm2-gtm")) अणु
		समयrs[0].gtpsr = &regs->gtpsr1;
		समयrs[1].gtpsr = &regs->gtpsr2;
		समयrs[2].gtpsr = &regs->gtpsr3;
		समयrs[3].gtpsr = &regs->gtpsr4;
	पूर्ण
पूर्ण

अटल पूर्णांक __init fsl_gपंचांग_init(व्योम)
अणु
	काष्ठा device_node *np;

	क्रम_each_compatible_node(np, शून्य, "fsl,gtm") अणु
		पूर्णांक i;
		काष्ठा gपंचांग *gपंचांग;
		स्थिर u32 *घड़ी;
		पूर्णांक size;

		gपंचांग = kzalloc(माप(*gपंचांग), GFP_KERNEL);
		अगर (!gपंचांग) अणु
			pr_err("%pOF: unable to allocate memory\n",
				np);
			जारी;
		पूर्ण

		spin_lock_init(&gपंचांग->lock);

		घड़ी = of_get_property(np, "clock-frequency", &size);
		अगर (!घड़ी || size != माप(*घड़ी)) अणु
			pr_err("%pOF: no clock-frequency\n", np);
			जाओ err;
		पूर्ण
		gपंचांग->घड़ी = *घड़ी;

		क्रम (i = 0; i < ARRAY_SIZE(gपंचांग->समयrs); i++) अणु
			अचिन्हित पूर्णांक irq;

			irq = irq_of_parse_and_map(np, i);
			अगर (!irq) अणु
				pr_err("%pOF: not enough interrupts specified\n",
				       np);
				जाओ err;
			पूर्ण
			gपंचांग->समयrs[i].irq = irq;
			gपंचांग->समयrs[i].gपंचांग = gपंचांग;
		पूर्ण

		gपंचांग->regs = of_iomap(np, 0);
		अगर (!gपंचांग->regs) अणु
			pr_err("%pOF: unable to iomap registers\n",
			       np);
			जाओ err;
		पूर्ण

		gपंचांग_set_लघुcuts(np, gपंचांग->समयrs, gपंचांग->regs);
		list_add(&gपंचांग->list_node, &gपंचांगs);

		/* We करोn't want to lose the node and its ->data */
		np->data = gपंचांग;
		of_node_get(np);

		जारी;
err:
		kमुक्त(gपंचांग);
	पूर्ण
	वापस 0;
पूर्ण
arch_initcall(fsl_gपंचांग_init);
