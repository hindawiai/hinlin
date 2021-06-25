<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2016,2017 IBM Corporation.
 */

#घोषणा pr_fmt(fmt) "xive: " fmt

#समावेश <linux/types.h>
#समावेश <linux/irq.h>
#समावेश <linux/smp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/libfdt.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <यंत्र/xive.h>
#समावेश <यंत्र/xive-regs.h>
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/svm.h>
#समावेश <यंत्र/ultravisor.h>

#समावेश "xive-internal.h"

अटल u32 xive_queue_shअगरt;

काष्ठा xive_irq_biपंचांगap अणु
	अचिन्हित दीर्घ		*biपंचांगap;
	अचिन्हित पूर्णांक		base;
	अचिन्हित पूर्णांक		count;
	spinlock_t		lock;
	काष्ठा list_head	list;
पूर्ण;

अटल LIST_HEAD(xive_irq_biपंचांगaps);

अटल पूर्णांक xive_irq_biपंचांगap_add(पूर्णांक base, पूर्णांक count)
अणु
	काष्ठा xive_irq_biपंचांगap *xibm;

	xibm = kzalloc(माप(*xibm), GFP_KERNEL);
	अगर (!xibm)
		वापस -ENOMEM;

	spin_lock_init(&xibm->lock);
	xibm->base = base;
	xibm->count = count;
	xibm->biपंचांगap = kzalloc(xibm->count, GFP_KERNEL);
	अगर (!xibm->biपंचांगap) अणु
		kमुक्त(xibm);
		वापस -ENOMEM;
	पूर्ण
	list_add(&xibm->list, &xive_irq_biपंचांगaps);

	pr_info("Using IRQ range [%x-%x]", xibm->base,
		xibm->base + xibm->count - 1);
	वापस 0;
पूर्ण

अटल पूर्णांक __xive_irq_biपंचांगap_alloc(काष्ठा xive_irq_biपंचांगap *xibm)
अणु
	पूर्णांक irq;

	irq = find_first_zero_bit(xibm->biपंचांगap, xibm->count);
	अगर (irq != xibm->count) अणु
		set_bit(irq, xibm->biपंचांगap);
		irq += xibm->base;
	पूर्ण अन्यथा अणु
		irq = -ENOMEM;
	पूर्ण

	वापस irq;
पूर्ण

अटल पूर्णांक xive_irq_biपंचांगap_alloc(व्योम)
अणु
	काष्ठा xive_irq_biपंचांगap *xibm;
	अचिन्हित दीर्घ flags;
	पूर्णांक irq = -ENOENT;

	list_क्रम_each_entry(xibm, &xive_irq_biपंचांगaps, list) अणु
		spin_lock_irqsave(&xibm->lock, flags);
		irq = __xive_irq_biपंचांगap_alloc(xibm);
		spin_unlock_irqrestore(&xibm->lock, flags);
		अगर (irq >= 0)
			अवरोध;
	पूर्ण
	वापस irq;
पूर्ण

अटल व्योम xive_irq_biपंचांगap_मुक्त(पूर्णांक irq)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा xive_irq_biपंचांगap *xibm;

	list_क्रम_each_entry(xibm, &xive_irq_biपंचांगaps, list) अणु
		अगर ((irq >= xibm->base) && (irq < xibm->base + xibm->count)) अणु
			spin_lock_irqsave(&xibm->lock, flags);
			clear_bit(irq - xibm->base, xibm->biपंचांगap);
			spin_unlock_irqrestore(&xibm->lock, flags);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण


/* Based on the similar routines in RTAS */
अटल अचिन्हित पूर्णांक plpar_busy_delay_समय(दीर्घ rc)
अणु
	अचिन्हित पूर्णांक ms = 0;

	अगर (H_IS_LONG_BUSY(rc)) अणु
		ms = get_दीर्घbusy_msecs(rc);
	पूर्ण अन्यथा अगर (rc == H_BUSY) अणु
		ms = 10; /* seems appropriate क्रम XIVE hcalls */
	पूर्ण

	वापस ms;
पूर्ण

अटल अचिन्हित पूर्णांक plpar_busy_delay(पूर्णांक rc)
अणु
	अचिन्हित पूर्णांक ms;

	ms = plpar_busy_delay_समय(rc);
	अगर (ms)
		mdelay(ms);

	वापस ms;
पूर्ण

/*
 * Note: this call has a partition wide scope and can take a जबतक to
 * complete. If it वापसs H_LONG_BUSY_* it should be retried
 * periodically.
 */
अटल दीर्घ plpar_पूर्णांक_reset(अचिन्हित दीर्घ flags)
अणु
	दीर्घ rc;

	करो अणु
		rc = plpar_hcall_norets(H_INT_RESET, flags);
	पूर्ण जबतक (plpar_busy_delay(rc));

	अगर (rc)
		pr_err("H_INT_RESET failed %ld\n", rc);

	वापस rc;
पूर्ण

अटल दीर्घ plpar_पूर्णांक_get_source_info(अचिन्हित दीर्घ flags,
				      अचिन्हित दीर्घ lisn,
				      अचिन्हित दीर्घ *src_flags,
				      अचिन्हित दीर्घ *eoi_page,
				      अचिन्हित दीर्घ *trig_page,
				      अचिन्हित दीर्घ *esb_shअगरt)
अणु
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];
	दीर्घ rc;

	करो अणु
		rc = plpar_hcall(H_INT_GET_SOURCE_INFO, retbuf, flags, lisn);
	पूर्ण जबतक (plpar_busy_delay(rc));

	अगर (rc) अणु
		pr_err("H_INT_GET_SOURCE_INFO lisn=%ld failed %ld\n", lisn, rc);
		वापस rc;
	पूर्ण

	*src_flags = retbuf[0];
	*eoi_page  = retbuf[1];
	*trig_page = retbuf[2];
	*esb_shअगरt = retbuf[3];

	pr_devel("H_INT_GET_SOURCE_INFO flags=%lx eoi=%lx trig=%lx shift=%lx\n",
		retbuf[0], retbuf[1], retbuf[2], retbuf[3]);

	वापस 0;
पूर्ण

#घोषणा XIVE_SRC_SET_EISN (1ull << (63 - 62))
#घोषणा XIVE_SRC_MASK     (1ull << (63 - 63)) /* unused */

अटल दीर्घ plpar_पूर्णांक_set_source_config(अचिन्हित दीर्घ flags,
					अचिन्हित दीर्घ lisn,
					अचिन्हित दीर्घ target,
					अचिन्हित दीर्घ prio,
					अचिन्हित दीर्घ sw_irq)
अणु
	दीर्घ rc;


	pr_devel("H_INT_SET_SOURCE_CONFIG flags=%lx lisn=%lx target=%lx prio=%lx sw_irq=%lx\n",
		flags, lisn, target, prio, sw_irq);


	करो अणु
		rc = plpar_hcall_norets(H_INT_SET_SOURCE_CONFIG, flags, lisn,
					target, prio, sw_irq);
	पूर्ण जबतक (plpar_busy_delay(rc));

	अगर (rc) अणु
		pr_err("H_INT_SET_SOURCE_CONFIG lisn=%ld target=%lx prio=%lx failed %ld\n",
		       lisn, target, prio, rc);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल दीर्घ plpar_पूर्णांक_get_source_config(अचिन्हित दीर्घ flags,
					अचिन्हित दीर्घ lisn,
					अचिन्हित दीर्घ *target,
					अचिन्हित दीर्घ *prio,
					अचिन्हित दीर्घ *sw_irq)
अणु
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];
	दीर्घ rc;

	pr_devel("H_INT_GET_SOURCE_CONFIG flags=%lx lisn=%lx\n", flags, lisn);

	करो अणु
		rc = plpar_hcall(H_INT_GET_SOURCE_CONFIG, retbuf, flags, lisn,
				 target, prio, sw_irq);
	पूर्ण जबतक (plpar_busy_delay(rc));

	अगर (rc) अणु
		pr_err("H_INT_GET_SOURCE_CONFIG lisn=%ld failed %ld\n",
		       lisn, rc);
		वापस rc;
	पूर्ण

	*target = retbuf[0];
	*prio   = retbuf[1];
	*sw_irq = retbuf[2];

	pr_devel("H_INT_GET_SOURCE_CONFIG target=%lx prio=%lx sw_irq=%lx\n",
		retbuf[0], retbuf[1], retbuf[2]);

	वापस 0;
पूर्ण

अटल दीर्घ plpar_पूर्णांक_get_queue_info(अचिन्हित दीर्घ flags,
				     अचिन्हित दीर्घ target,
				     अचिन्हित दीर्घ priority,
				     अचिन्हित दीर्घ *esn_page,
				     अचिन्हित दीर्घ *esn_size)
अणु
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];
	दीर्घ rc;

	करो अणु
		rc = plpar_hcall(H_INT_GET_QUEUE_INFO, retbuf, flags, target,
				 priority);
	पूर्ण जबतक (plpar_busy_delay(rc));

	अगर (rc) अणु
		pr_err("H_INT_GET_QUEUE_INFO cpu=%ld prio=%ld failed %ld\n",
		       target, priority, rc);
		वापस rc;
	पूर्ण

	*esn_page = retbuf[0];
	*esn_size = retbuf[1];

	pr_devel("H_INT_GET_QUEUE_INFO page=%lx size=%lx\n",
		retbuf[0], retbuf[1]);

	वापस 0;
पूर्ण

#घोषणा XIVE_EQ_ALWAYS_NOTIFY (1ull << (63 - 63))

अटल दीर्घ plpar_पूर्णांक_set_queue_config(अचिन्हित दीर्घ flags,
				       अचिन्हित दीर्घ target,
				       अचिन्हित दीर्घ priority,
				       अचिन्हित दीर्घ qpage,
				       अचिन्हित दीर्घ qsize)
अणु
	दीर्घ rc;

	pr_devel("H_INT_SET_QUEUE_CONFIG flags=%lx target=%lx priority=%lx qpage=%lx qsize=%lx\n",
		flags,  target, priority, qpage, qsize);

	करो अणु
		rc = plpar_hcall_norets(H_INT_SET_QUEUE_CONFIG, flags, target,
					priority, qpage, qsize);
	पूर्ण जबतक (plpar_busy_delay(rc));

	अगर (rc) अणु
		pr_err("H_INT_SET_QUEUE_CONFIG cpu=%ld prio=%ld qpage=%lx returned %ld\n",
		       target, priority, qpage, rc);
		वापस  rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल दीर्घ plpar_पूर्णांक_sync(अचिन्हित दीर्घ flags, अचिन्हित दीर्घ lisn)
अणु
	दीर्घ rc;

	करो अणु
		rc = plpar_hcall_norets(H_INT_SYNC, flags, lisn);
	पूर्ण जबतक (plpar_busy_delay(rc));

	अगर (rc) अणु
		pr_err("H_INT_SYNC lisn=%ld returned %ld\n", lisn, rc);
		वापस  rc;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा XIVE_ESB_FLAG_STORE (1ull << (63 - 63))

अटल दीर्घ plpar_पूर्णांक_esb(अचिन्हित दीर्घ flags,
			  अचिन्हित दीर्घ lisn,
			  अचिन्हित दीर्घ offset,
			  अचिन्हित दीर्घ in_data,
			  अचिन्हित दीर्घ *out_data)
अणु
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];
	दीर्घ rc;

	pr_devel("H_INT_ESB flags=%lx lisn=%lx offset=%lx in=%lx\n",
		flags,  lisn, offset, in_data);

	करो अणु
		rc = plpar_hcall(H_INT_ESB, retbuf, flags, lisn, offset,
				 in_data);
	पूर्ण जबतक (plpar_busy_delay(rc));

	अगर (rc) अणु
		pr_err("H_INT_ESB lisn=%ld offset=%ld returned %ld\n",
		       lisn, offset, rc);
		वापस  rc;
	पूर्ण

	*out_data = retbuf[0];

	वापस 0;
पूर्ण

अटल u64 xive_spapr_esb_rw(u32 lisn, u32 offset, u64 data, bool ग_लिखो)
अणु
	अचिन्हित दीर्घ पढ़ो_data;
	दीर्घ rc;

	rc = plpar_पूर्णांक_esb(ग_लिखो ? XIVE_ESB_FLAG_STORE : 0,
			   lisn, offset, data, &पढ़ो_data);
	अगर (rc)
		वापस -1;

	वापस ग_लिखो ? 0 : पढ़ो_data;
पूर्ण

#घोषणा XIVE_SRC_H_INT_ESB     (1ull << (63 - 60))
#घोषणा XIVE_SRC_LSI           (1ull << (63 - 61))
#घोषणा XIVE_SRC_TRIGGER       (1ull << (63 - 62))
#घोषणा XIVE_SRC_STORE_EOI     (1ull << (63 - 63))

अटल पूर्णांक xive_spapr_populate_irq_data(u32 hw_irq, काष्ठा xive_irq_data *data)
अणु
	दीर्घ rc;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ eoi_page;
	अचिन्हित दीर्घ trig_page;
	अचिन्हित दीर्घ esb_shअगरt;

	स_रखो(data, 0, माप(*data));

	rc = plpar_पूर्णांक_get_source_info(0, hw_irq, &flags, &eoi_page, &trig_page,
				       &esb_shअगरt);
	अगर (rc)
		वापस  -EINVAL;

	अगर (flags & XIVE_SRC_H_INT_ESB)
		data->flags  |= XIVE_IRQ_FLAG_H_INT_ESB;
	अगर (flags & XIVE_SRC_STORE_EOI)
		data->flags  |= XIVE_IRQ_FLAG_STORE_EOI;
	अगर (flags & XIVE_SRC_LSI)
		data->flags  |= XIVE_IRQ_FLAG_LSI;
	data->eoi_page  = eoi_page;
	data->esb_shअगरt = esb_shअगरt;
	data->trig_page = trig_page;

	data->hw_irq = hw_irq;

	/*
	 * No chip-id क्रम the sPAPR backend. This has an impact how we
	 * pick a target. See xive_pick_irq_target().
	 */
	data->src_chip = XIVE_INVALID_CHIP_ID;

	/*
	 * When the H_INT_ESB flag is set, the H_INT_ESB hcall should
	 * be used क्रम पूर्णांकerrupt management. Skip the remapping of the
	 * ESB pages which are not available.
	 */
	अगर (data->flags & XIVE_IRQ_FLAG_H_INT_ESB)
		वापस 0;

	data->eoi_mmio = ioremap(data->eoi_page, 1u << data->esb_shअगरt);
	अगर (!data->eoi_mmio) अणु
		pr_err("Failed to map EOI page for irq 0x%x\n", hw_irq);
		वापस -ENOMEM;
	पूर्ण

	/* Full function page supports trigger */
	अगर (flags & XIVE_SRC_TRIGGER) अणु
		data->trig_mmio = data->eoi_mmio;
		वापस 0;
	पूर्ण

	data->trig_mmio = ioremap(data->trig_page, 1u << data->esb_shअगरt);
	अगर (!data->trig_mmio) अणु
		pr_err("Failed to map trigger page for irq 0x%x\n", hw_irq);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक xive_spapr_configure_irq(u32 hw_irq, u32 target, u8 prio, u32 sw_irq)
अणु
	दीर्घ rc;

	rc = plpar_पूर्णांक_set_source_config(XIVE_SRC_SET_EISN, hw_irq, target,
					 prio, sw_irq);

	वापस rc == 0 ? 0 : -ENXIO;
पूर्ण

अटल पूर्णांक xive_spapr_get_irq_config(u32 hw_irq, u32 *target, u8 *prio,
				     u32 *sw_irq)
अणु
	दीर्घ rc;
	अचिन्हित दीर्घ h_target;
	अचिन्हित दीर्घ h_prio;
	अचिन्हित दीर्घ h_sw_irq;

	rc = plpar_पूर्णांक_get_source_config(0, hw_irq, &h_target, &h_prio,
					 &h_sw_irq);

	*target = h_target;
	*prio = h_prio;
	*sw_irq = h_sw_irq;

	वापस rc == 0 ? 0 : -ENXIO;
पूर्ण

/* This can be called multiple समय to change a queue configuration */
अटल पूर्णांक xive_spapr_configure_queue(u32 target, काष्ठा xive_q *q, u8 prio,
				   __be32 *qpage, u32 order)
अणु
	s64 rc = 0;
	अचिन्हित दीर्घ esn_page;
	अचिन्हित दीर्घ esn_size;
	u64 flags, qpage_phys;

	/* If there's an actual queue page, clean it */
	अगर (order) अणु
		अगर (WARN_ON(!qpage))
			वापस -EINVAL;
		qpage_phys = __pa(qpage);
	पूर्ण अन्यथा अणु
		qpage_phys = 0;
	पूर्ण

	/* Initialize the rest of the fields */
	q->msk = order ? ((1u << (order - 2)) - 1) : 0;
	q->idx = 0;
	q->toggle = 0;

	rc = plpar_पूर्णांक_get_queue_info(0, target, prio, &esn_page, &esn_size);
	अगर (rc) अणु
		pr_err("Error %lld getting queue info CPU %d prio %d\n", rc,
		       target, prio);
		rc = -EIO;
		जाओ fail;
	पूर्ण

	/* TODO: add support क्रम the notअगरication page */
	q->eoi_phys = esn_page;

	/* Default is to always notअगरy */
	flags = XIVE_EQ_ALWAYS_NOTIFY;

	/* Configure and enable the queue in HW */
	rc = plpar_पूर्णांक_set_queue_config(flags, target, prio, qpage_phys, order);
	अगर (rc) अणु
		pr_err("Error %lld setting queue for CPU %d prio %d\n", rc,
		       target, prio);
		rc = -EIO;
	पूर्ण अन्यथा अणु
		q->qpage = qpage;
		अगर (is_secure_guest())
			uv_share_page(PHYS_PFN(qpage_phys),
					1 << xive_alloc_order(order));
	पूर्ण
fail:
	वापस rc;
पूर्ण

अटल पूर्णांक xive_spapr_setup_queue(अचिन्हित पूर्णांक cpu, काष्ठा xive_cpu *xc,
				  u8 prio)
अणु
	काष्ठा xive_q *q = &xc->queue[prio];
	__be32 *qpage;

	qpage = xive_queue_page_alloc(cpu, xive_queue_shअगरt);
	अगर (IS_ERR(qpage))
		वापस PTR_ERR(qpage);

	वापस xive_spapr_configure_queue(get_hard_smp_processor_id(cpu),
					  q, prio, qpage, xive_queue_shअगरt);
पूर्ण

अटल व्योम xive_spapr_cleanup_queue(अचिन्हित पूर्णांक cpu, काष्ठा xive_cpu *xc,
				  u8 prio)
अणु
	काष्ठा xive_q *q = &xc->queue[prio];
	अचिन्हित पूर्णांक alloc_order;
	दीर्घ rc;
	पूर्णांक hw_cpu = get_hard_smp_processor_id(cpu);

	rc = plpar_पूर्णांक_set_queue_config(0, hw_cpu, prio, 0, 0);
	अगर (rc)
		pr_err("Error %ld setting queue for CPU %d prio %d\n", rc,
		       hw_cpu, prio);

	alloc_order = xive_alloc_order(xive_queue_shअगरt);
	अगर (is_secure_guest())
		uv_unshare_page(PHYS_PFN(__pa(q->qpage)), 1 << alloc_order);
	मुक्त_pages((अचिन्हित दीर्घ)q->qpage, alloc_order);
	q->qpage = शून्य;
पूर्ण

अटल bool xive_spapr_match(काष्ठा device_node *node)
अणु
	/* Ignore cascaded controllers क्रम the moment */
	वापस true;
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल पूर्णांक xive_spapr_get_ipi(अचिन्हित पूर्णांक cpu, काष्ठा xive_cpu *xc)
अणु
	पूर्णांक irq = xive_irq_biपंचांगap_alloc();

	अगर (irq < 0) अणु
		pr_err("Failed to allocate IPI on CPU %d\n", cpu);
		वापस -ENXIO;
	पूर्ण

	xc->hw_ipi = irq;
	वापस 0;
पूर्ण

अटल व्योम xive_spapr_put_ipi(अचिन्हित पूर्णांक cpu, काष्ठा xive_cpu *xc)
अणु
	अगर (xc->hw_ipi == XIVE_BAD_IRQ)
		वापस;

	xive_irq_biपंचांगap_मुक्त(xc->hw_ipi);
	xc->hw_ipi = XIVE_BAD_IRQ;
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

अटल व्योम xive_spapr_shutकरोwn(व्योम)
अणु
	plpar_पूर्णांक_reset(0);
पूर्ण

/*
 * Perक्रमm an "ack" cycle on the current thपढ़ो. Grab the pending
 * active priorities and update the CPPR to the most favored one.
 */
अटल व्योम xive_spapr_update_pending(काष्ठा xive_cpu *xc)
अणु
	u8 nsr, cppr;
	u16 ack;

	/*
	 * Perक्रमm the "Acknowledge O/S to Register" cycle.
	 *
	 * Let's speedup the access to the TIMA using the raw I/O
	 * accessor as we करोn't need the synchronisation routine of
	 * the higher level ones
	 */
	ack = be16_to_cpu(__raw_पढ़ोw(xive_tima + TM_SPC_ACK_OS_REG));

	/* Synchronize subsequent queue accesses */
	mb();

	/*
	 * Grab the CPPR and the "NSR" field which indicates the source
	 * of the पूर्णांकerrupt (अगर any)
	 */
	cppr = ack & 0xff;
	nsr = ack >> 8;

	अगर (nsr & TM_QW1_NSR_EO) अणु
		अगर (cppr == 0xff)
			वापस;
		/* Mark the priority pending */
		xc->pending_prio |= 1 << cppr;

		/*
		 * A new पूर्णांकerrupt should never have a CPPR less favored
		 * than our current one.
		 */
		अगर (cppr >= xc->cppr)
			pr_err("CPU %d odd ack CPPR, got %d at %d\n",
			       smp_processor_id(), cppr, xc->cppr);

		/* Update our idea of what the CPPR is */
		xc->cppr = cppr;
	पूर्ण
पूर्ण

अटल व्योम xive_spapr_setup_cpu(अचिन्हित पूर्णांक cpu, काष्ठा xive_cpu *xc)
अणु
	/* Only some debug on the TIMA settings */
	pr_debug("(HW value: %08x %08x %08x)\n",
		 in_be32(xive_tima + TM_QW1_OS + TM_WORD0),
		 in_be32(xive_tima + TM_QW1_OS + TM_WORD1),
		 in_be32(xive_tima + TM_QW1_OS + TM_WORD2));
पूर्ण

अटल व्योम xive_spapr_tearकरोwn_cpu(अचिन्हित पूर्णांक cpu, काष्ठा xive_cpu *xc)
अणु
	/* Nothing to करो */;
पूर्ण

अटल व्योम xive_spapr_sync_source(u32 hw_irq)
अणु
	/* Specs are unclear on what this is करोing */
	plpar_पूर्णांक_sync(0, hw_irq);
पूर्ण

अटल पूर्णांक xive_spapr_debug_show(काष्ठा seq_file *m, व्योम *निजी)
अणु
	काष्ठा xive_irq_biपंचांगap *xibm;
	अक्षर *buf = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);

	list_क्रम_each_entry(xibm, &xive_irq_biपंचांगaps, list) अणु
		स_रखो(buf, 0, PAGE_SIZE);
		biपंचांगap_prपूर्णांक_to_pagebuf(true, buf, xibm->biपंचांगap, xibm->count);
		seq_म_लिखो(m, "bitmap #%d: %s", xibm->count, buf);
	पूर्ण
	kमुक्त(buf);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा xive_ops xive_spapr_ops = अणु
	.populate_irq_data	= xive_spapr_populate_irq_data,
	.configure_irq		= xive_spapr_configure_irq,
	.get_irq_config		= xive_spapr_get_irq_config,
	.setup_queue		= xive_spapr_setup_queue,
	.cleanup_queue		= xive_spapr_cleanup_queue,
	.match			= xive_spapr_match,
	.shutकरोwn		= xive_spapr_shutकरोwn,
	.update_pending		= xive_spapr_update_pending,
	.setup_cpu		= xive_spapr_setup_cpu,
	.tearकरोwn_cpu		= xive_spapr_tearकरोwn_cpu,
	.sync_source		= xive_spapr_sync_source,
	.esb_rw			= xive_spapr_esb_rw,
#अगर_घोषित CONFIG_SMP
	.get_ipi		= xive_spapr_get_ipi,
	.put_ipi		= xive_spapr_put_ipi,
	.debug_show		= xive_spapr_debug_show,
#पूर्ण_अगर /* CONFIG_SMP */
	.name			= "spapr",
पूर्ण;

/*
 * get max priority from "/ibm,plat-res-int-priorities"
 */
अटल bool xive_get_max_prio(u8 *max_prio)
अणु
	काष्ठा device_node *rootdn;
	स्थिर __be32 *reg;
	u32 len;
	पूर्णांक prio, found;

	rootdn = of_find_node_by_path("/");
	अगर (!rootdn) अणु
		pr_err("not root node found !\n");
		वापस false;
	पूर्ण

	reg = of_get_property(rootdn, "ibm,plat-res-int-priorities", &len);
	अगर (!reg) अणु
		pr_err("Failed to read 'ibm,plat-res-int-priorities' property\n");
		वापस false;
	पूर्ण

	अगर (len % (2 * माप(u32)) != 0) अणु
		pr_err("invalid 'ibm,plat-res-int-priorities' property\n");
		वापस false;
	पूर्ण

	/* HW supports priorities in the range [0-7] and 0xFF is a
	 * wildcard priority used to mask. We scan the ranges reserved
	 * by the hypervisor to find the lowest priority we can use.
	 */
	found = 0xFF;
	क्रम (prio = 0; prio < 8; prio++) अणु
		पूर्णांक reserved = 0;
		पूर्णांक i;

		क्रम (i = 0; i < len / (2 * माप(u32)); i++) अणु
			पूर्णांक base  = be32_to_cpu(reg[2 * i]);
			पूर्णांक range = be32_to_cpu(reg[2 * i + 1]);

			अगर (prio >= base && prio < base + range)
				reserved++;
		पूर्ण

		अगर (!reserved)
			found = prio;
	पूर्ण

	अगर (found == 0xFF) अणु
		pr_err("no valid priority found in 'ibm,plat-res-int-priorities'\n");
		वापस false;
	पूर्ण

	*max_prio = found;
	वापस true;
पूर्ण

अटल स्थिर u8 *get_vec5_feature(अचिन्हित पूर्णांक index)
अणु
	अचिन्हित दीर्घ root, chosen;
	पूर्णांक size;
	स्थिर u8 *vec5;

	root = of_get_flat_dt_root();
	chosen = of_get_flat_dt_subnode_by_name(root, "chosen");
	अगर (chosen == -FDT_ERR_NOTFOUND)
		वापस शून्य;

	vec5 = of_get_flat_dt_prop(chosen, "ibm,architecture-vec-5", &size);
	अगर (!vec5)
		वापस शून्य;

	अगर (size <= index)
		वापस शून्य;

	वापस vec5 + index;
पूर्ण

अटल bool __init xive_spapr_disabled(व्योम)
अणु
	स्थिर u8 *vec5_xive;

	vec5_xive = get_vec5_feature(OV5_INDX(OV5_XIVE_SUPPORT));
	अगर (vec5_xive) अणु
		u8 val;

		val = *vec5_xive & OV5_FEAT(OV5_XIVE_SUPPORT);
		चयन (val) अणु
		हाल OV5_FEAT(OV5_XIVE_EITHER):
		हाल OV5_FEAT(OV5_XIVE_LEGACY):
			अवरोध;
		हाल OV5_FEAT(OV5_XIVE_EXPLOIT):
			/* Hypervisor only supports XIVE */
			अगर (xive_cmdline_disabled)
				pr_warn("WARNING: Ignoring cmdline option xive=off\n");
			वापस false;
		शेष:
			pr_warn("%s: Unknown xive support option: 0x%x\n",
				__func__, val);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस xive_cmdline_disabled;
पूर्ण

bool __init xive_spapr_init(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा resource r;
	व्योम __iomem *tima;
	काष्ठा property *prop;
	u8 max_prio;
	u32 val;
	u32 len;
	स्थिर __be32 *reg;
	पूर्णांक i;

	अगर (xive_spapr_disabled())
		वापस false;

	pr_devel("%s()\n", __func__);
	np = of_find_compatible_node(शून्य, शून्य, "ibm,power-ivpe");
	अगर (!np) अणु
		pr_devel("not found !\n");
		वापस false;
	पूर्ण
	pr_devel("Found %s\n", np->full_name);

	/* Resource 1 is the OS ring TIMA */
	अगर (of_address_to_resource(np, 1, &r)) अणु
		pr_err("Failed to get thread mgmnt area resource\n");
		वापस false;
	पूर्ण
	tima = ioremap(r.start, resource_size(&r));
	अगर (!tima) अणु
		pr_err("Failed to map thread mgmnt area\n");
		वापस false;
	पूर्ण

	अगर (!xive_get_max_prio(&max_prio))
		वापस false;

	/* Feed the IRQ number allocator with the ranges given in the DT */
	reg = of_get_property(np, "ibm,xive-lisn-ranges", &len);
	अगर (!reg) अणु
		pr_err("Failed to read 'ibm,xive-lisn-ranges' property\n");
		वापस false;
	पूर्ण

	अगर (len % (2 * माप(u32)) != 0) अणु
		pr_err("invalid 'ibm,xive-lisn-ranges' property\n");
		वापस false;
	पूर्ण

	क्रम (i = 0; i < len / (2 * माप(u32)); i++, reg += 2)
		xive_irq_biपंचांगap_add(be32_to_cpu(reg[0]),
				    be32_to_cpu(reg[1]));

	/* Iterate the EQ sizes and pick one */
	of_property_क्रम_each_u32(np, "ibm,xive-eq-sizes", prop, reg, val) अणु
		xive_queue_shअगरt = val;
		अगर (val == PAGE_SHIFT)
			अवरोध;
	पूर्ण

	/* Initialize XIVE core with our backend */
	अगर (!xive_core_init(np, &xive_spapr_ops, tima, TM_QW1_OS, max_prio))
		वापस false;

	pr_info("Using %dkB queues\n", 1 << (xive_queue_shअगरt - 10));
	वापस true;
पूर्ण

machine_arch_initcall(pseries, xive_core_debug_init);
