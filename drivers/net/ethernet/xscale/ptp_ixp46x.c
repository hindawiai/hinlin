<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PTP 1588 घड़ी using the IXP46X
 *
 * Copyright (C) 2010 OMICRON electronics GmbH
 */
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश <linux/ptp_घड़ी_kernel.h>

#समावेश "ixp46x_ts.h"

#घोषणा DRIVER		"ptp_ixp46x"
#घोषणा N_EXT_TS	2
#घोषणा MASTER_GPIO	8
#घोषणा MASTER_IRQ	25
#घोषणा SLAVE_GPIO	7
#घोषणा SLAVE_IRQ	24

काष्ठा ixp_घड़ी अणु
	काष्ठा ixp46x_ts_regs *regs;
	काष्ठा ptp_घड़ी *ptp_घड़ी;
	काष्ठा ptp_घड़ी_info caps;
	पूर्णांक exts0_enabled;
	पूर्णांक exts1_enabled;
पूर्ण;

DEFINE_SPINLOCK(रेजिस्टर_lock);

/*
 * Register access functions
 */

अटल u64 ixp_sysसमय_पढ़ो(काष्ठा ixp46x_ts_regs *regs)
अणु
	u64 ns;
	u32 lo, hi;

	lo = __raw_पढ़ोl(&regs->sysसमय_lo);
	hi = __raw_पढ़ोl(&regs->sysसमय_hi);

	ns = ((u64) hi) << 32;
	ns |= lo;
	ns <<= TICKS_NS_SHIFT;

	वापस ns;
पूर्ण

अटल व्योम ixp_sysसमय_ग_लिखो(काष्ठा ixp46x_ts_regs *regs, u64 ns)
अणु
	u32 hi, lo;

	ns >>= TICKS_NS_SHIFT;
	hi = ns >> 32;
	lo = ns & 0xffffffff;

	__raw_ग_लिखोl(lo, &regs->sysसमय_lo);
	__raw_ग_लिखोl(hi, &regs->sysसमय_hi);
पूर्ण

/*
 * Interrupt service routine
 */

अटल irqवापस_t isr(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा ixp_घड़ी *ixp_घड़ी = priv;
	काष्ठा ixp46x_ts_regs *regs = ixp_घड़ी->regs;
	काष्ठा ptp_घड़ी_event event;
	u32 ack = 0, lo, hi, val;

	val = __raw_पढ़ोl(&regs->event);

	अगर (val & TSER_SNS) अणु
		ack |= TSER_SNS;
		अगर (ixp_घड़ी->exts0_enabled) अणु
			hi = __raw_पढ़ोl(&regs->यंत्रs_hi);
			lo = __raw_पढ़ोl(&regs->यंत्रs_lo);
			event.type = PTP_CLOCK_EXTTS;
			event.index = 0;
			event.बारtamp = ((u64) hi) << 32;
			event.बारtamp |= lo;
			event.बारtamp <<= TICKS_NS_SHIFT;
			ptp_घड़ी_event(ixp_घड़ी->ptp_घड़ी, &event);
		पूर्ण
	पूर्ण

	अगर (val & TSER_SNM) अणु
		ack |= TSER_SNM;
		अगर (ixp_घड़ी->exts1_enabled) अणु
			hi = __raw_पढ़ोl(&regs->amms_hi);
			lo = __raw_पढ़ोl(&regs->amms_lo);
			event.type = PTP_CLOCK_EXTTS;
			event.index = 1;
			event.बारtamp = ((u64) hi) << 32;
			event.बारtamp |= lo;
			event.बारtamp <<= TICKS_NS_SHIFT;
			ptp_घड़ी_event(ixp_घड़ी->ptp_घड़ी, &event);
		पूर्ण
	पूर्ण

	अगर (val & TTIPEND)
		ack |= TTIPEND; /* this bit seems to be always set */

	अगर (ack) अणु
		__raw_ग_लिखोl(ack, &regs->event);
		वापस IRQ_HANDLED;
	पूर्ण अन्यथा
		वापस IRQ_NONE;
पूर्ण

/*
 * PTP घड़ी operations
 */

अटल पूर्णांक ptp_ixp_adjfreq(काष्ठा ptp_घड़ी_info *ptp, s32 ppb)
अणु
	u64 adj;
	u32 dअगरf, addend;
	पूर्णांक neg_adj = 0;
	काष्ठा ixp_घड़ी *ixp_घड़ी = container_of(ptp, काष्ठा ixp_घड़ी, caps);
	काष्ठा ixp46x_ts_regs *regs = ixp_घड़ी->regs;

	अगर (ppb < 0) अणु
		neg_adj = 1;
		ppb = -ppb;
	पूर्ण
	addend = DEFAULT_ADDEND;
	adj = addend;
	adj *= ppb;
	dअगरf = भाग_u64(adj, 1000000000ULL);

	addend = neg_adj ? addend - dअगरf : addend + dअगरf;

	__raw_ग_लिखोl(addend, &regs->addend);

	वापस 0;
पूर्ण

अटल पूर्णांक ptp_ixp_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	s64 now;
	अचिन्हित दीर्घ flags;
	काष्ठा ixp_घड़ी *ixp_घड़ी = container_of(ptp, काष्ठा ixp_घड़ी, caps);
	काष्ठा ixp46x_ts_regs *regs = ixp_घड़ी->regs;

	spin_lock_irqsave(&रेजिस्टर_lock, flags);

	now = ixp_sysसमय_पढ़ो(regs);
	now += delta;
	ixp_sysसमय_ग_लिखो(regs, now);

	spin_unlock_irqrestore(&रेजिस्टर_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ptp_ixp_समय_लो(काष्ठा ptp_घड़ी_info *ptp, काष्ठा बारpec64 *ts)
अणु
	u64 ns;
	अचिन्हित दीर्घ flags;
	काष्ठा ixp_घड़ी *ixp_घड़ी = container_of(ptp, काष्ठा ixp_घड़ी, caps);
	काष्ठा ixp46x_ts_regs *regs = ixp_घड़ी->regs;

	spin_lock_irqsave(&रेजिस्टर_lock, flags);

	ns = ixp_sysसमय_पढ़ो(regs);

	spin_unlock_irqrestore(&रेजिस्टर_lock, flags);

	*ts = ns_to_बारpec64(ns);
	वापस 0;
पूर्ण

अटल पूर्णांक ptp_ixp_समय_रखो(काष्ठा ptp_घड़ी_info *ptp,
			   स्थिर काष्ठा बारpec64 *ts)
अणु
	u64 ns;
	अचिन्हित दीर्घ flags;
	काष्ठा ixp_घड़ी *ixp_घड़ी = container_of(ptp, काष्ठा ixp_घड़ी, caps);
	काष्ठा ixp46x_ts_regs *regs = ixp_घड़ी->regs;

	ns = बारpec64_to_ns(ts);

	spin_lock_irqsave(&रेजिस्टर_lock, flags);

	ixp_sysसमय_ग_लिखो(regs, ns);

	spin_unlock_irqrestore(&रेजिस्टर_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ptp_ixp_enable(काष्ठा ptp_घड़ी_info *ptp,
			  काष्ठा ptp_घड़ी_request *rq, पूर्णांक on)
अणु
	काष्ठा ixp_घड़ी *ixp_घड़ी = container_of(ptp, काष्ठा ixp_घड़ी, caps);

	चयन (rq->type) अणु
	हाल PTP_CLK_REQ_EXTTS:
		चयन (rq->extts.index) अणु
		हाल 0:
			ixp_घड़ी->exts0_enabled = on ? 1 : 0;
			अवरोध;
		हाल 1:
			ixp_घड़ी->exts1_enabled = on ? 1 : 0;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर काष्ठा ptp_घड़ी_info ptp_ixp_caps = अणु
	.owner		= THIS_MODULE,
	.name		= "IXP46X timer",
	.max_adj	= 66666655,
	.n_ext_ts	= N_EXT_TS,
	.n_pins		= 0,
	.pps		= 0,
	.adjfreq	= ptp_ixp_adjfreq,
	.adjसमय	= ptp_ixp_adjसमय,
	.समय_लो64	= ptp_ixp_समय_लो,
	.समय_रखो64	= ptp_ixp_समय_रखो,
	.enable		= ptp_ixp_enable,
पूर्ण;

/* module operations */

अटल काष्ठा ixp_घड़ी ixp_घड़ी;

अटल पूर्णांक setup_पूर्णांकerrupt(पूर्णांक gpio)
अणु
	पूर्णांक irq;
	पूर्णांक err;

	err = gpio_request(gpio, "ixp4-ptp");
	अगर (err)
		वापस err;

	err = gpio_direction_input(gpio);
	अगर (err)
		वापस err;

	irq = gpio_to_irq(gpio);
	अगर (irq < 0)
		वापस irq;

	err = irq_set_irq_type(irq, IRQF_TRIGGER_FALLING);
	अगर (err) अणु
		pr_err("cannot set trigger type for irq %d\n", irq);
		वापस err;
	पूर्ण

	err = request_irq(irq, isr, 0, DRIVER, &ixp_घड़ी);
	अगर (err) अणु
		pr_err("request_irq failed for irq %d\n", irq);
		वापस err;
	पूर्ण

	वापस irq;
पूर्ण

अटल व्योम __निकास ptp_ixp_निकास(व्योम)
अणु
	मुक्त_irq(MASTER_IRQ, &ixp_घड़ी);
	मुक्त_irq(SLAVE_IRQ, &ixp_घड़ी);
	ixp46x_phc_index = -1;
	ptp_घड़ी_unरेजिस्टर(ixp_घड़ी.ptp_घड़ी);
पूर्ण

अटल पूर्णांक __init ptp_ixp_init(व्योम)
अणु
	अगर (!cpu_is_ixp46x())
		वापस -ENODEV;

	ixp_घड़ी.regs =
		(काष्ठा ixp46x_ts_regs __iomem *) IXP4XX_TIMESYNC_BASE_VIRT;

	ixp_घड़ी.caps = ptp_ixp_caps;

	ixp_घड़ी.ptp_घड़ी = ptp_घड़ी_रेजिस्टर(&ixp_घड़ी.caps, शून्य);

	अगर (IS_ERR(ixp_घड़ी.ptp_घड़ी))
		वापस PTR_ERR(ixp_घड़ी.ptp_घड़ी);

	ixp46x_phc_index = ptp_घड़ी_index(ixp_घड़ी.ptp_घड़ी);

	__raw_ग_लिखोl(DEFAULT_ADDEND, &ixp_घड़ी.regs->addend);
	__raw_ग_लिखोl(1, &ixp_घड़ी.regs->trgt_lo);
	__raw_ग_लिखोl(0, &ixp_घड़ी.regs->trgt_hi);
	__raw_ग_लिखोl(TTIPEND, &ixp_घड़ी.regs->event);

	अगर (MASTER_IRQ != setup_पूर्णांकerrupt(MASTER_GPIO)) अणु
		pr_err("failed to setup gpio %d as irq\n", MASTER_GPIO);
		जाओ no_master;
	पूर्ण
	अगर (SLAVE_IRQ != setup_पूर्णांकerrupt(SLAVE_GPIO)) अणु
		pr_err("failed to setup gpio %d as irq\n", SLAVE_GPIO);
		जाओ no_slave;
	पूर्ण

	वापस 0;
no_slave:
	मुक्त_irq(MASTER_IRQ, &ixp_घड़ी);
no_master:
	ptp_घड़ी_unरेजिस्टर(ixp_घड़ी.ptp_घड़ी);
	वापस -ENODEV;
पूर्ण

module_init(ptp_ixp_init);
module_निकास(ptp_ixp_निकास);

MODULE_AUTHOR("Richard Cochran <richardcochran@gmail.com>");
MODULE_DESCRIPTION("PTP clock using the IXP46X timer");
MODULE_LICENSE("GPL");
