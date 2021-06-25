<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PTP 1588 घड़ी क्रम Freescale QorIQ 1588 समयr
 *
 * Copyright (C) 2010 OMICRON electronics GmbH
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/device.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/समयx.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>

#समावेश <linux/fsl/ptp_qoriq.h>

/*
 * Register access functions
 */

/* Caller must hold ptp_qoriq->lock. */
अटल u64 पंचांगr_cnt_पढ़ो(काष्ठा ptp_qoriq *ptp_qoriq)
अणु
	काष्ठा ptp_qoriq_रेजिस्टरs *regs = &ptp_qoriq->regs;
	u64 ns;
	u32 lo, hi;

	lo = ptp_qoriq->पढ़ो(&regs->ctrl_regs->पंचांगr_cnt_l);
	hi = ptp_qoriq->पढ़ो(&regs->ctrl_regs->पंचांगr_cnt_h);
	ns = ((u64) hi) << 32;
	ns |= lo;
	वापस ns;
पूर्ण

/* Caller must hold ptp_qoriq->lock. */
अटल व्योम पंचांगr_cnt_ग_लिखो(काष्ठा ptp_qoriq *ptp_qoriq, u64 ns)
अणु
	काष्ठा ptp_qoriq_रेजिस्टरs *regs = &ptp_qoriq->regs;
	u32 hi = ns >> 32;
	u32 lo = ns & 0xffffffff;

	ptp_qoriq->ग_लिखो(&regs->ctrl_regs->पंचांगr_cnt_l, lo);
	ptp_qoriq->ग_लिखो(&regs->ctrl_regs->पंचांगr_cnt_h, hi);
पूर्ण

/* Caller must hold ptp_qoriq->lock. */
अटल व्योम set_alarm(काष्ठा ptp_qoriq *ptp_qoriq)
अणु
	काष्ठा ptp_qoriq_रेजिस्टरs *regs = &ptp_qoriq->regs;
	u64 ns;
	u32 lo, hi;

	ns = पंचांगr_cnt_पढ़ो(ptp_qoriq) + 1500000000ULL;
	ns = भाग_u64(ns, 1000000000UL) * 1000000000ULL;
	ns -= ptp_qoriq->tclk_period;
	hi = ns >> 32;
	lo = ns & 0xffffffff;
	ptp_qoriq->ग_लिखो(&regs->alarm_regs->पंचांगr_alarm1_l, lo);
	ptp_qoriq->ग_लिखो(&regs->alarm_regs->पंचांगr_alarm1_h, hi);
पूर्ण

/* Caller must hold ptp_qoriq->lock. */
अटल व्योम set_fipers(काष्ठा ptp_qoriq *ptp_qoriq)
अणु
	काष्ठा ptp_qoriq_रेजिस्टरs *regs = &ptp_qoriq->regs;

	set_alarm(ptp_qoriq);
	ptp_qoriq->ग_लिखो(&regs->fiper_regs->पंचांगr_fiper1, ptp_qoriq->पंचांगr_fiper1);
	ptp_qoriq->ग_लिखो(&regs->fiper_regs->पंचांगr_fiper2, ptp_qoriq->पंचांगr_fiper2);

	अगर (ptp_qoriq->fiper3_support)
		ptp_qoriq->ग_लिखो(&regs->fiper_regs->पंचांगr_fiper3,
				 ptp_qoriq->पंचांगr_fiper3);
पूर्ण

पूर्णांक extts_clean_up(काष्ठा ptp_qoriq *ptp_qoriq, पूर्णांक index, bool update_event)
अणु
	काष्ठा ptp_qoriq_रेजिस्टरs *regs = &ptp_qoriq->regs;
	काष्ठा ptp_घड़ी_event event;
	व्योम __iomem *reg_etts_l;
	व्योम __iomem *reg_etts_h;
	u32 valid, lo, hi;

	चयन (index) अणु
	हाल 0:
		valid = ETS1_VLD;
		reg_etts_l = &regs->etts_regs->पंचांगr_etts1_l;
		reg_etts_h = &regs->etts_regs->पंचांगr_etts1_h;
		अवरोध;
	हाल 1:
		valid = ETS2_VLD;
		reg_etts_l = &regs->etts_regs->पंचांगr_etts2_l;
		reg_etts_h = &regs->etts_regs->पंचांगr_etts2_h;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	event.type = PTP_CLOCK_EXTTS;
	event.index = index;

	अगर (ptp_qoriq->extts_fअगरo_support)
		अगर (!(ptp_qoriq->पढ़ो(&regs->ctrl_regs->पंचांगr_stat) & valid))
			वापस 0;

	करो अणु
		lo = ptp_qoriq->पढ़ो(reg_etts_l);
		hi = ptp_qoriq->पढ़ो(reg_etts_h);

		अगर (update_event) अणु
			event.बारtamp = ((u64) hi) << 32;
			event.बारtamp |= lo;
			ptp_घड़ी_event(ptp_qoriq->घड़ी, &event);
		पूर्ण

		अगर (!ptp_qoriq->extts_fअगरo_support)
			अवरोध;
	पूर्ण जबतक (ptp_qoriq->पढ़ो(&regs->ctrl_regs->पंचांगr_stat) & valid);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(extts_clean_up);

/*
 * Interrupt service routine
 */

irqवापस_t ptp_qoriq_isr(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा ptp_qoriq *ptp_qoriq = priv;
	काष्ठा ptp_qoriq_रेजिस्टरs *regs = &ptp_qoriq->regs;
	काष्ठा ptp_घड़ी_event event;
	u32 ack = 0, mask, val, irqs;

	spin_lock(&ptp_qoriq->lock);

	val = ptp_qoriq->पढ़ो(&regs->ctrl_regs->पंचांगr_tevent);
	mask = ptp_qoriq->पढ़ो(&regs->ctrl_regs->पंचांगr_temask);

	spin_unlock(&ptp_qoriq->lock);

	irqs = val & mask;

	अगर (irqs & ETS1) अणु
		ack |= ETS1;
		extts_clean_up(ptp_qoriq, 0, true);
	पूर्ण

	अगर (irqs & ETS2) अणु
		ack |= ETS2;
		extts_clean_up(ptp_qoriq, 1, true);
	पूर्ण

	अगर (irqs & PP1) अणु
		ack |= PP1;
		event.type = PTP_CLOCK_PPS;
		ptp_घड़ी_event(ptp_qoriq->घड़ी, &event);
	पूर्ण

	अगर (ack) अणु
		ptp_qoriq->ग_लिखो(&regs->ctrl_regs->पंचांगr_tevent, ack);
		वापस IRQ_HANDLED;
	पूर्ण अन्यथा
		वापस IRQ_NONE;
पूर्ण
EXPORT_SYMBOL_GPL(ptp_qoriq_isr);

/*
 * PTP घड़ी operations
 */

पूर्णांक ptp_qoriq_adjfine(काष्ठा ptp_घड़ी_info *ptp, दीर्घ scaled_ppm)
अणु
	u64 adj, dअगरf;
	u32 पंचांगr_add;
	पूर्णांक neg_adj = 0;
	काष्ठा ptp_qoriq *ptp_qoriq = container_of(ptp, काष्ठा ptp_qoriq, caps);
	काष्ठा ptp_qoriq_रेजिस्टरs *regs = &ptp_qoriq->regs;

	अगर (scaled_ppm < 0) अणु
		neg_adj = 1;
		scaled_ppm = -scaled_ppm;
	पूर्ण
	पंचांगr_add = ptp_qoriq->पंचांगr_add;
	adj = पंचांगr_add;

	/*
	 * Calculate dअगरf and round() to the nearest पूर्णांकeger
	 *
	 * dअगरf = adj * (ppb / 1000000000)
	 *      = adj * scaled_ppm / 65536000000
	 */
	dअगरf = mul_u64_u64_भाग_u64(adj, scaled_ppm, 32768000000);
	dअगरf = DIV64_U64_ROUND_UP(dअगरf, 2);

	पंचांगr_add = neg_adj ? पंचांगr_add - dअगरf : पंचांगr_add + dअगरf;
	ptp_qoriq->ग_लिखो(&regs->ctrl_regs->पंचांगr_add, पंचांगr_add);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ptp_qoriq_adjfine);

पूर्णांक ptp_qoriq_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	s64 now;
	अचिन्हित दीर्घ flags;
	काष्ठा ptp_qoriq *ptp_qoriq = container_of(ptp, काष्ठा ptp_qoriq, caps);

	spin_lock_irqsave(&ptp_qoriq->lock, flags);

	now = पंचांगr_cnt_पढ़ो(ptp_qoriq);
	now += delta;
	पंचांगr_cnt_ग_लिखो(ptp_qoriq, now);
	set_fipers(ptp_qoriq);

	spin_unlock_irqrestore(&ptp_qoriq->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ptp_qoriq_adjसमय);

पूर्णांक ptp_qoriq_समय_लो(काष्ठा ptp_घड़ी_info *ptp, काष्ठा बारpec64 *ts)
अणु
	u64 ns;
	अचिन्हित दीर्घ flags;
	काष्ठा ptp_qoriq *ptp_qoriq = container_of(ptp, काष्ठा ptp_qoriq, caps);

	spin_lock_irqsave(&ptp_qoriq->lock, flags);

	ns = पंचांगr_cnt_पढ़ो(ptp_qoriq);

	spin_unlock_irqrestore(&ptp_qoriq->lock, flags);

	*ts = ns_to_बारpec64(ns);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ptp_qoriq_समय_लो);

पूर्णांक ptp_qoriq_समय_रखो(काष्ठा ptp_घड़ी_info *ptp,
		      स्थिर काष्ठा बारpec64 *ts)
अणु
	u64 ns;
	अचिन्हित दीर्घ flags;
	काष्ठा ptp_qoriq *ptp_qoriq = container_of(ptp, काष्ठा ptp_qoriq, caps);

	ns = बारpec64_to_ns(ts);

	spin_lock_irqsave(&ptp_qoriq->lock, flags);

	पंचांगr_cnt_ग_लिखो(ptp_qoriq, ns);
	set_fipers(ptp_qoriq);

	spin_unlock_irqrestore(&ptp_qoriq->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ptp_qoriq_समय_रखो);

पूर्णांक ptp_qoriq_enable(काष्ठा ptp_घड़ी_info *ptp,
		     काष्ठा ptp_घड़ी_request *rq, पूर्णांक on)
अणु
	काष्ठा ptp_qoriq *ptp_qoriq = container_of(ptp, काष्ठा ptp_qoriq, caps);
	काष्ठा ptp_qoriq_रेजिस्टरs *regs = &ptp_qoriq->regs;
	अचिन्हित दीर्घ flags;
	u32 bit, mask = 0;

	चयन (rq->type) अणु
	हाल PTP_CLK_REQ_EXTTS:
		चयन (rq->extts.index) अणु
		हाल 0:
			bit = ETS1EN;
			अवरोध;
		हाल 1:
			bit = ETS2EN;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		अगर (on)
			extts_clean_up(ptp_qoriq, rq->extts.index, false);

		अवरोध;
	हाल PTP_CLK_REQ_PPS:
		bit = PP1EN;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	spin_lock_irqsave(&ptp_qoriq->lock, flags);

	mask = ptp_qoriq->पढ़ो(&regs->ctrl_regs->पंचांगr_temask);
	अगर (on) अणु
		mask |= bit;
		ptp_qoriq->ग_लिखो(&regs->ctrl_regs->पंचांगr_tevent, bit);
	पूर्ण अन्यथा अणु
		mask &= ~bit;
	पूर्ण

	ptp_qoriq->ग_लिखो(&regs->ctrl_regs->पंचांगr_temask, mask);

	spin_unlock_irqrestore(&ptp_qoriq->lock, flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ptp_qoriq_enable);

अटल स्थिर काष्ठा ptp_घड़ी_info ptp_qoriq_caps = अणु
	.owner		= THIS_MODULE,
	.name		= "qoriq ptp clock",
	.max_adj	= 512000,
	.n_alarm	= 0,
	.n_ext_ts	= N_EXT_TS,
	.n_per_out	= 0,
	.n_pins		= 0,
	.pps		= 1,
	.adjfine	= ptp_qoriq_adjfine,
	.adjसमय	= ptp_qoriq_adjसमय,
	.समय_लो64	= ptp_qoriq_समय_लो,
	.समय_रखो64	= ptp_qoriq_समय_रखो,
	.enable		= ptp_qoriq_enable,
पूर्ण;

/**
 * ptp_qoriq_nominal_freq - calculate nominal frequency according to
 *			    reference घड़ी frequency
 *
 * @clk_src: reference घड़ी frequency
 *
 * The nominal frequency is the desired घड़ी frequency.
 * It should be less than the reference घड़ी frequency.
 * It should be a factor of 1000MHz.
 *
 * Return the nominal frequency
 */
अटल u32 ptp_qoriq_nominal_freq(u32 clk_src)
अणु
	u32 reमुख्यder = 0;

	clk_src /= 1000000;
	reमुख्यder = clk_src % 100;
	अगर (reमुख्यder) अणु
		clk_src -= reमुख्यder;
		clk_src += 100;
	पूर्ण

	करो अणु
		clk_src -= 100;

	पूर्ण जबतक (1000 % clk_src);

	वापस clk_src * 1000000;
पूर्ण

/**
 * ptp_qoriq_स्वतः_config - calculate a set of शेष configurations
 *
 * @ptp_qoriq: poपूर्णांकer to ptp_qoriq
 * @node: poपूर्णांकer to device_node
 *
 * If below dts properties are not provided, this function will be
 * called to calculate a set of शेष configurations क्रम them.
 *   "fsl,tclk-period"
 *   "fsl,tmr-prsc"
 *   "fsl,tmr-add"
 *   "fsl,tmr-fiper1"
 *   "fsl,tmr-fiper2"
 *   "fsl,tmr-fiper3" (required only क्रम DPAA2 and ENETC hardware)
 *   "fsl,max-adj"
 *
 * Return 0 अगर success
 */
अटल पूर्णांक ptp_qoriq_स्वतः_config(काष्ठा ptp_qoriq *ptp_qoriq,
				 काष्ठा device_node *node)
अणु
	काष्ठा clk *clk;
	u64 freq_comp;
	u64 max_adj;
	u32 nominal_freq;
	u32 reमुख्यder = 0;
	u32 clk_src = 0;

	ptp_qoriq->cksel = DEFAULT_CKSEL;

	clk = of_clk_get(node, 0);
	अगर (!IS_ERR(clk)) अणु
		clk_src = clk_get_rate(clk);
		clk_put(clk);
	पूर्ण

	अगर (clk_src <= 100000000UL) अणु
		pr_err("error reference clock value, or lower than 100MHz\n");
		वापस -EINVAL;
	पूर्ण

	nominal_freq = ptp_qoriq_nominal_freq(clk_src);
	अगर (!nominal_freq)
		वापस -EINVAL;

	ptp_qoriq->tclk_period = 1000000000UL / nominal_freq;
	ptp_qoriq->पंचांगr_prsc = DEFAULT_TMR_PRSC;

	/* Calculate initial frequency compensation value क्रम TMR_ADD रेजिस्टर.
	 * freq_comp = उच्चमान(2^32 / freq_ratio)
	 * freq_ratio = reference_घड़ी_freq / nominal_freq
	 */
	freq_comp = ((u64)1 << 32) * nominal_freq;
	freq_comp = भाग_u64_rem(freq_comp, clk_src, &reमुख्यder);
	अगर (reमुख्यder)
		freq_comp++;

	ptp_qoriq->पंचांगr_add = freq_comp;
	ptp_qoriq->पंचांगr_fiper1 = DEFAULT_FIPER1_PERIOD - ptp_qoriq->tclk_period;
	ptp_qoriq->पंचांगr_fiper2 = DEFAULT_FIPER2_PERIOD - ptp_qoriq->tclk_period;
	ptp_qoriq->पंचांगr_fiper3 = DEFAULT_FIPER3_PERIOD - ptp_qoriq->tclk_period;

	/* max_adj = 1000000000 * (freq_ratio - 1.0) - 1
	 * freq_ratio = reference_घड़ी_freq / nominal_freq
	 */
	max_adj = 1000000000ULL * (clk_src - nominal_freq);
	max_adj = भाग_u64(max_adj, nominal_freq) - 1;
	ptp_qoriq->caps.max_adj = max_adj;

	वापस 0;
पूर्ण

पूर्णांक ptp_qoriq_init(काष्ठा ptp_qoriq *ptp_qoriq, व्योम __iomem *base,
		   स्थिर काष्ठा ptp_घड़ी_info *caps)
अणु
	काष्ठा device_node *node = ptp_qoriq->dev->of_node;
	काष्ठा ptp_qoriq_रेजिस्टरs *regs;
	काष्ठा बारpec64 now;
	अचिन्हित दीर्घ flags;
	u32 पंचांगr_ctrl;

	अगर (!node)
		वापस -ENODEV;

	ptp_qoriq->base = base;
	ptp_qoriq->caps = *caps;

	अगर (of_property_पढ़ो_u32(node, "fsl,cksel", &ptp_qoriq->cksel))
		ptp_qoriq->cksel = DEFAULT_CKSEL;

	अगर (of_property_पढ़ो_bool(node, "fsl,extts-fifo"))
		ptp_qoriq->extts_fअगरo_support = true;
	अन्यथा
		ptp_qoriq->extts_fअगरo_support = false;

	अगर (of_device_is_compatible(node, "fsl,dpaa2-ptp") ||
	    of_device_is_compatible(node, "fsl,enetc-ptp"))
		ptp_qoriq->fiper3_support = true;

	अगर (of_property_पढ़ो_u32(node,
				 "fsl,tclk-period", &ptp_qoriq->tclk_period) ||
	    of_property_पढ़ो_u32(node,
				 "fsl,tmr-prsc", &ptp_qoriq->पंचांगr_prsc) ||
	    of_property_पढ़ो_u32(node,
				 "fsl,tmr-add", &ptp_qoriq->पंचांगr_add) ||
	    of_property_पढ़ो_u32(node,
				 "fsl,tmr-fiper1", &ptp_qoriq->पंचांगr_fiper1) ||
	    of_property_पढ़ो_u32(node,
				 "fsl,tmr-fiper2", &ptp_qoriq->पंचांगr_fiper2) ||
	    of_property_पढ़ो_u32(node,
				 "fsl,max-adj", &ptp_qoriq->caps.max_adj) ||
	    (ptp_qoriq->fiper3_support &&
	     of_property_पढ़ो_u32(node, "fsl,tmr-fiper3",
				  &ptp_qoriq->पंचांगr_fiper3))) अणु
		pr_warn("device tree node missing required elements, try automatic configuration\n");

		अगर (ptp_qoriq_स्वतः_config(ptp_qoriq, node))
			वापस -ENODEV;
	पूर्ण

	अगर (of_property_पढ़ो_bool(node, "little-endian")) अणु
		ptp_qoriq->पढ़ो = qoriq_पढ़ो_le;
		ptp_qoriq->ग_लिखो = qoriq_ग_लिखो_le;
	पूर्ण अन्यथा अणु
		ptp_qoriq->पढ़ो = qoriq_पढ़ो_be;
		ptp_qoriq->ग_लिखो = qoriq_ग_लिखो_be;
	पूर्ण

	/* The eTSEC uses dअगरfernt memory map with DPAA/ENETC */
	अगर (of_device_is_compatible(node, "fsl,etsec-ptp")) अणु
		ptp_qoriq->regs.ctrl_regs = base + ETSEC_CTRL_REGS_OFFSET;
		ptp_qoriq->regs.alarm_regs = base + ETSEC_ALARM_REGS_OFFSET;
		ptp_qoriq->regs.fiper_regs = base + ETSEC_FIPER_REGS_OFFSET;
		ptp_qoriq->regs.etts_regs = base + ETSEC_ETTS_REGS_OFFSET;
	पूर्ण अन्यथा अणु
		ptp_qoriq->regs.ctrl_regs = base + CTRL_REGS_OFFSET;
		ptp_qoriq->regs.alarm_regs = base + ALARM_REGS_OFFSET;
		ptp_qoriq->regs.fiper_regs = base + FIPER_REGS_OFFSET;
		ptp_qoriq->regs.etts_regs = base + ETTS_REGS_OFFSET;
	पूर्ण

	spin_lock_init(&ptp_qoriq->lock);

	kसमय_get_real_ts64(&now);
	ptp_qoriq_समय_रखो(&ptp_qoriq->caps, &now);

	पंचांगr_ctrl =
	  (ptp_qoriq->tclk_period & TCLK_PERIOD_MASK) << TCLK_PERIOD_SHIFT |
	  (ptp_qoriq->cksel & CKSEL_MASK) << CKSEL_SHIFT;

	spin_lock_irqsave(&ptp_qoriq->lock, flags);

	regs = &ptp_qoriq->regs;
	ptp_qoriq->ग_लिखो(&regs->ctrl_regs->पंचांगr_ctrl, पंचांगr_ctrl);
	ptp_qoriq->ग_लिखो(&regs->ctrl_regs->पंचांगr_add, ptp_qoriq->पंचांगr_add);
	ptp_qoriq->ग_लिखो(&regs->ctrl_regs->पंचांगr_prsc, ptp_qoriq->पंचांगr_prsc);
	ptp_qoriq->ग_लिखो(&regs->fiper_regs->पंचांगr_fiper1, ptp_qoriq->पंचांगr_fiper1);
	ptp_qoriq->ग_लिखो(&regs->fiper_regs->पंचांगr_fiper2, ptp_qoriq->पंचांगr_fiper2);

	अगर (ptp_qoriq->fiper3_support)
		ptp_qoriq->ग_लिखो(&regs->fiper_regs->पंचांगr_fiper3,
				 ptp_qoriq->पंचांगr_fiper3);

	set_alarm(ptp_qoriq);
	ptp_qoriq->ग_लिखो(&regs->ctrl_regs->पंचांगr_ctrl,
			 पंचांगr_ctrl|FIPERST|RTPE|TE|FRD);

	spin_unlock_irqrestore(&ptp_qoriq->lock, flags);

	ptp_qoriq->घड़ी = ptp_घड़ी_रेजिस्टर(&ptp_qoriq->caps, ptp_qoriq->dev);
	अगर (IS_ERR(ptp_qoriq->घड़ी))
		वापस PTR_ERR(ptp_qoriq->घड़ी);

	ptp_qoriq->phc_index = ptp_घड़ी_index(ptp_qoriq->घड़ी);
	ptp_qoriq_create_debugfs(ptp_qoriq);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ptp_qoriq_init);

व्योम ptp_qoriq_मुक्त(काष्ठा ptp_qoriq *ptp_qoriq)
अणु
	काष्ठा ptp_qoriq_रेजिस्टरs *regs = &ptp_qoriq->regs;

	ptp_qoriq->ग_लिखो(&regs->ctrl_regs->पंचांगr_temask, 0);
	ptp_qoriq->ग_लिखो(&regs->ctrl_regs->पंचांगr_ctrl,   0);

	ptp_qoriq_हटाओ_debugfs(ptp_qoriq);
	ptp_घड़ी_unरेजिस्टर(ptp_qoriq->घड़ी);
	iounmap(ptp_qoriq->base);
	मुक्त_irq(ptp_qoriq->irq, ptp_qoriq);
पूर्ण
EXPORT_SYMBOL_GPL(ptp_qoriq_मुक्त);

अटल पूर्णांक ptp_qoriq_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा ptp_qoriq *ptp_qoriq;
	पूर्णांक err = -ENOMEM;
	व्योम __iomem *base;

	ptp_qoriq = kzalloc(माप(*ptp_qoriq), GFP_KERNEL);
	अगर (!ptp_qoriq)
		जाओ no_memory;

	ptp_qoriq->dev = &dev->dev;

	err = -ENODEV;

	ptp_qoriq->irq = platक्रमm_get_irq(dev, 0);
	अगर (ptp_qoriq->irq < 0) अणु
		pr_err("irq not in device tree\n");
		जाओ no_node;
	पूर्ण
	अगर (request_irq(ptp_qoriq->irq, ptp_qoriq_isr, IRQF_SHARED,
			DRIVER, ptp_qoriq)) अणु
		pr_err("request_irq failed\n");
		जाओ no_node;
	पूर्ण

	ptp_qoriq->rsrc = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	अगर (!ptp_qoriq->rsrc) अणु
		pr_err("no resource\n");
		जाओ no_resource;
	पूर्ण
	अगर (request_resource(&iomem_resource, ptp_qoriq->rsrc)) अणु
		pr_err("resource busy\n");
		जाओ no_resource;
	पूर्ण

	base = ioremap(ptp_qoriq->rsrc->start,
		       resource_size(ptp_qoriq->rsrc));
	अगर (!base) अणु
		pr_err("ioremap ptp registers failed\n");
		जाओ no_ioremap;
	पूर्ण

	err = ptp_qoriq_init(ptp_qoriq, base, &ptp_qoriq_caps);
	अगर (err)
		जाओ no_घड़ी;

	platक्रमm_set_drvdata(dev, ptp_qoriq);
	वापस 0;

no_घड़ी:
	iounmap(ptp_qoriq->base);
no_ioremap:
	release_resource(ptp_qoriq->rsrc);
no_resource:
	मुक्त_irq(ptp_qoriq->irq, ptp_qoriq);
no_node:
	kमुक्त(ptp_qoriq);
no_memory:
	वापस err;
पूर्ण

अटल पूर्णांक ptp_qoriq_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा ptp_qoriq *ptp_qoriq = platक्रमm_get_drvdata(dev);

	ptp_qoriq_मुक्त(ptp_qoriq);
	release_resource(ptp_qoriq->rsrc);
	kमुक्त(ptp_qoriq);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id match_table[] = अणु
	अणु .compatible = "fsl,etsec-ptp" पूर्ण,
	अणु .compatible = "fsl,fman-ptp-timer" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, match_table);

अटल काष्ठा platक्रमm_driver ptp_qoriq_driver = अणु
	.driver = अणु
		.name		= "ptp_qoriq",
		.of_match_table	= match_table,
	पूर्ण,
	.probe       = ptp_qoriq_probe,
	.हटाओ      = ptp_qoriq_हटाओ,
पूर्ण;

module_platक्रमm_driver(ptp_qoriq_driver);

MODULE_AUTHOR("Richard Cochran <richardcochran@gmail.com>");
MODULE_DESCRIPTION("PTP clock for Freescale QorIQ 1588 timer");
MODULE_LICENSE("GPL");
