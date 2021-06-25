<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2016,2017 IBM Corporation.
 */

#घोषणा pr_fmt(fmt) "xive: " fmt

#समावेश <linux/types.h>
#समावेश <linux/irq.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/smp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/mm.h>
#समावेश <linux/kmemleak.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <यंत्र/xive.h>
#समावेश <यंत्र/xive-regs.h>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/kvm_ppc.h>

#समावेश "xive-internal.h"


अटल u32 xive_provision_size;
अटल u32 *xive_provision_chips;
अटल u32 xive_provision_chip_count;
अटल u32 xive_queue_shअगरt;
अटल u32 xive_pool_vps = XIVE_INVALID_VP;
अटल काष्ठा kmem_cache *xive_provision_cache;
अटल bool xive_has_single_esc;

पूर्णांक xive_native_populate_irq_data(u32 hw_irq, काष्ठा xive_irq_data *data)
अणु
	__be64 flags, eoi_page, trig_page;
	__be32 esb_shअगरt, src_chip;
	u64 opal_flags;
	s64 rc;

	स_रखो(data, 0, माप(*data));

	rc = opal_xive_get_irq_info(hw_irq, &flags, &eoi_page, &trig_page,
				    &esb_shअगरt, &src_chip);
	अगर (rc) अणु
		pr_err("opal_xive_get_irq_info(0x%x) returned %lld\n",
		       hw_irq, rc);
		वापस -EINVAL;
	पूर्ण

	opal_flags = be64_to_cpu(flags);
	अगर (opal_flags & OPAL_XIVE_IRQ_STORE_EOI)
		data->flags |= XIVE_IRQ_FLAG_STORE_EOI;
	अगर (opal_flags & OPAL_XIVE_IRQ_LSI)
		data->flags |= XIVE_IRQ_FLAG_LSI;
	data->eoi_page = be64_to_cpu(eoi_page);
	data->trig_page = be64_to_cpu(trig_page);
	data->esb_shअगरt = be32_to_cpu(esb_shअगरt);
	data->src_chip = be32_to_cpu(src_chip);

	data->eoi_mmio = ioremap(data->eoi_page, 1u << data->esb_shअगरt);
	अगर (!data->eoi_mmio) अणु
		pr_err("Failed to map EOI page for irq 0x%x\n", hw_irq);
		वापस -ENOMEM;
	पूर्ण

	data->hw_irq = hw_irq;

	अगर (!data->trig_page)
		वापस 0;
	अगर (data->trig_page == data->eoi_page) अणु
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
EXPORT_SYMBOL_GPL(xive_native_populate_irq_data);

पूर्णांक xive_native_configure_irq(u32 hw_irq, u32 target, u8 prio, u32 sw_irq)
अणु
	s64 rc;

	क्रम (;;) अणु
		rc = opal_xive_set_irq_config(hw_irq, target, prio, sw_irq);
		अगर (rc != OPAL_BUSY)
			अवरोध;
		msleep(OPAL_BUSY_DELAY_MS);
	पूर्ण
	वापस rc == 0 ? 0 : -ENXIO;
पूर्ण
EXPORT_SYMBOL_GPL(xive_native_configure_irq);

अटल पूर्णांक xive_native_get_irq_config(u32 hw_irq, u32 *target, u8 *prio,
				      u32 *sw_irq)
अणु
	s64 rc;
	__be64 vp;
	__be32 lirq;

	rc = opal_xive_get_irq_config(hw_irq, &vp, prio, &lirq);

	*target = be64_to_cpu(vp);
	*sw_irq = be32_to_cpu(lirq);

	वापस rc == 0 ? 0 : -ENXIO;
पूर्ण

#घोषणा vp_err(vp, fmt, ...) pr_err("VP[0x%x]: " fmt, vp, ##__VA_ARGS__)

/* This can be called multiple समय to change a queue configuration */
पूर्णांक xive_native_configure_queue(u32 vp_id, काष्ठा xive_q *q, u8 prio,
				__be32 *qpage, u32 order, bool can_escalate)
अणु
	s64 rc = 0;
	__be64 qeoi_page_be;
	__be32 esc_irq_be;
	u64 flags, qpage_phys;

	/* If there's an actual queue page, clean it */
	अगर (order) अणु
		अगर (WARN_ON(!qpage))
			वापस -EINVAL;
		qpage_phys = __pa(qpage);
	पूर्ण अन्यथा
		qpage_phys = 0;

	/* Initialize the rest of the fields */
	q->msk = order ? ((1u << (order - 2)) - 1) : 0;
	q->idx = 0;
	q->toggle = 0;

	rc = opal_xive_get_queue_info(vp_id, prio, शून्य, शून्य,
				      &qeoi_page_be,
				      &esc_irq_be,
				      शून्य);
	अगर (rc) अणु
		vp_err(vp_id, "Failed to get queue %d info : %lld\n", prio, rc);
		rc = -EIO;
		जाओ fail;
	पूर्ण
	q->eoi_phys = be64_to_cpu(qeoi_page_be);

	/* Default flags */
	flags = OPAL_XIVE_EQ_ALWAYS_NOTIFY | OPAL_XIVE_EQ_ENABLED;

	/* Escalation needed ? */
	अगर (can_escalate) अणु
		q->esc_irq = be32_to_cpu(esc_irq_be);
		flags |= OPAL_XIVE_EQ_ESCALATE;
	पूर्ण

	/* Configure and enable the queue in HW */
	क्रम (;;) अणु
		rc = opal_xive_set_queue_info(vp_id, prio, qpage_phys, order, flags);
		अगर (rc != OPAL_BUSY)
			अवरोध;
		msleep(OPAL_BUSY_DELAY_MS);
	पूर्ण
	अगर (rc) अणु
		vp_err(vp_id, "Failed to set queue %d info: %lld\n", prio, rc);
		rc = -EIO;
	पूर्ण अन्यथा अणु
		/*
		 * KVM code requires all of the above to be visible beक्रमe
		 * q->qpage is set due to how it manages IPI EOIs
		 */
		wmb();
		q->qpage = qpage;
	पूर्ण
fail:
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(xive_native_configure_queue);

अटल व्योम __xive_native_disable_queue(u32 vp_id, काष्ठा xive_q *q, u8 prio)
अणु
	s64 rc;

	/* Disable the queue in HW */
	क्रम (;;) अणु
		rc = opal_xive_set_queue_info(vp_id, prio, 0, 0, 0);
		अगर (rc != OPAL_BUSY)
			अवरोध;
		msleep(OPAL_BUSY_DELAY_MS);
	पूर्ण
	अगर (rc)
		vp_err(vp_id, "Failed to disable queue %d : %lld\n", prio, rc);
पूर्ण

व्योम xive_native_disable_queue(u32 vp_id, काष्ठा xive_q *q, u8 prio)
अणु
	__xive_native_disable_queue(vp_id, q, prio);
पूर्ण
EXPORT_SYMBOL_GPL(xive_native_disable_queue);

अटल पूर्णांक xive_native_setup_queue(अचिन्हित पूर्णांक cpu, काष्ठा xive_cpu *xc, u8 prio)
अणु
	काष्ठा xive_q *q = &xc->queue[prio];
	__be32 *qpage;

	qpage = xive_queue_page_alloc(cpu, xive_queue_shअगरt);
	अगर (IS_ERR(qpage))
		वापस PTR_ERR(qpage);

	वापस xive_native_configure_queue(get_hard_smp_processor_id(cpu),
					   q, prio, qpage, xive_queue_shअगरt, false);
पूर्ण

अटल व्योम xive_native_cleanup_queue(अचिन्हित पूर्णांक cpu, काष्ठा xive_cpu *xc, u8 prio)
अणु
	काष्ठा xive_q *q = &xc->queue[prio];
	अचिन्हित पूर्णांक alloc_order;

	/*
	 * We use the variant with no iounmap as this is called on exec
	 * from an IPI and iounmap isn't safe
	 */
	__xive_native_disable_queue(get_hard_smp_processor_id(cpu), q, prio);
	alloc_order = xive_alloc_order(xive_queue_shअगरt);
	मुक्त_pages((अचिन्हित दीर्घ)q->qpage, alloc_order);
	q->qpage = शून्य;
पूर्ण

अटल bool xive_native_match(काष्ठा device_node *node)
अणु
	वापस of_device_is_compatible(node, "ibm,opal-xive-vc");
पूर्ण

अटल s64 opal_xive_allocate_irq(u32 chip_id)
अणु
	s64 irq = opal_xive_allocate_irq_raw(chip_id);

	/*
	 * Old versions of skiboot can incorrectly वापस 0xffffffff to
	 * indicate no space, fix it up here.
	 */
	वापस irq == 0xffffffff ? OPAL_RESOURCE : irq;
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल पूर्णांक xive_native_get_ipi(अचिन्हित पूर्णांक cpu, काष्ठा xive_cpu *xc)
अणु
	s64 irq;

	/* Allocate an IPI and populate info about it */
	क्रम (;;) अणु
		irq = opal_xive_allocate_irq(xc->chip_id);
		अगर (irq == OPAL_BUSY) अणु
			msleep(OPAL_BUSY_DELAY_MS);
			जारी;
		पूर्ण
		अगर (irq < 0) अणु
			pr_err("Failed to allocate IPI on CPU %d\n", cpu);
			वापस -ENXIO;
		पूर्ण
		xc->hw_ipi = irq;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

u32 xive_native_alloc_irq_on_chip(u32 chip_id)
अणु
	s64 rc;

	क्रम (;;) अणु
		rc = opal_xive_allocate_irq(chip_id);
		अगर (rc != OPAL_BUSY)
			अवरोध;
		msleep(OPAL_BUSY_DELAY_MS);
	पूर्ण
	अगर (rc < 0)
		वापस 0;
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(xive_native_alloc_irq_on_chip);

व्योम xive_native_मुक्त_irq(u32 irq)
अणु
	क्रम (;;) अणु
		s64 rc = opal_xive_मुक्त_irq(irq);
		अगर (rc != OPAL_BUSY)
			अवरोध;
		msleep(OPAL_BUSY_DELAY_MS);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(xive_native_मुक्त_irq);

#अगर_घोषित CONFIG_SMP
अटल व्योम xive_native_put_ipi(अचिन्हित पूर्णांक cpu, काष्ठा xive_cpu *xc)
अणु
	s64 rc;

	/* Free the IPI */
	अगर (xc->hw_ipi == XIVE_BAD_IRQ)
		वापस;
	क्रम (;;) अणु
		rc = opal_xive_मुक्त_irq(xc->hw_ipi);
		अगर (rc == OPAL_BUSY) अणु
			msleep(OPAL_BUSY_DELAY_MS);
			जारी;
		पूर्ण
		xc->hw_ipi = XIVE_BAD_IRQ;
		अवरोध;
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

अटल व्योम xive_native_shutकरोwn(व्योम)
अणु
	/* Switch the XIVE to emulation mode */
	opal_xive_reset(OPAL_XIVE_MODE_EMU);
पूर्ण

/*
 * Perक्रमm an "ack" cycle on the current thपढ़ो, thus
 * grabbing the pending active priorities and updating
 * the CPPR to the most favored one.
 */
अटल व्योम xive_native_update_pending(काष्ठा xive_cpu *xc)
अणु
	u8 he, cppr;
	u16 ack;

	/* Perक्रमm the acknowledge hypervisor to रेजिस्टर cycle */
	ack = be16_to_cpu(__raw_पढ़ोw(xive_tima + TM_SPC_ACK_HV_REG));

	/* Synchronize subsequent queue accesses */
	mb();

	/*
	 * Grab the CPPR and the "HE" field which indicates the source
	 * of the hypervisor पूर्णांकerrupt (अगर any)
	 */
	cppr = ack & 0xff;
	he = (ack >> 8) >> 6;
	चयन(he) अणु
	हाल TM_QW3_NSR_HE_NONE: /* Nothing to see here */
		अवरोध;
	हाल TM_QW3_NSR_HE_PHYS: /* Physical thपढ़ो पूर्णांकerrupt */
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
		अवरोध;
	हाल TM_QW3_NSR_HE_POOL: /* HV Pool पूर्णांकerrupt (unused) */
	हाल TM_QW3_NSR_HE_LSI:  /* Legacy FW LSI (unused) */
		pr_err("CPU %d got unexpected interrupt type HE=%d\n",
		       smp_processor_id(), he);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम xive_native_prepare_cpu(अचिन्हित पूर्णांक cpu, काष्ठा xive_cpu *xc)
अणु
	xc->chip_id = cpu_to_chip_id(cpu);
पूर्ण

अटल व्योम xive_native_setup_cpu(अचिन्हित पूर्णांक cpu, काष्ठा xive_cpu *xc)
अणु
	s64 rc;
	u32 vp;
	__be64 vp_cam_be;
	u64 vp_cam;

	अगर (xive_pool_vps == XIVE_INVALID_VP)
		वापस;

	/* Check अगर pool VP alपढ़ोy active, अगर it is, pull it */
	अगर (in_be32(xive_tima + TM_QW2_HV_POOL + TM_WORD2) & TM_QW2W2_VP)
		in_be64(xive_tima + TM_SPC_PULL_POOL_CTX);

	/* Enable the pool VP */
	vp = xive_pool_vps + cpu;
	क्रम (;;) अणु
		rc = opal_xive_set_vp_info(vp, OPAL_XIVE_VP_ENABLED, 0);
		अगर (rc != OPAL_BUSY)
			अवरोध;
		msleep(OPAL_BUSY_DELAY_MS);
	पूर्ण
	अगर (rc) अणु
		pr_err("Failed to enable pool VP on CPU %d\n", cpu);
		वापस;
	पूर्ण

	/* Grab it's CAM value */
	rc = opal_xive_get_vp_info(vp, शून्य, &vp_cam_be, शून्य, शून्य);
	अगर (rc) अणु
		pr_err("Failed to get pool VP info CPU %d\n", cpu);
		वापस;
	पूर्ण
	vp_cam = be64_to_cpu(vp_cam_be);

	/* Push it on the CPU (set LSMFB to 0xff to skip backlog scan) */
	out_be32(xive_tima + TM_QW2_HV_POOL + TM_WORD0, 0xff);
	out_be32(xive_tima + TM_QW2_HV_POOL + TM_WORD2, TM_QW2W2_VP | vp_cam);
पूर्ण

अटल व्योम xive_native_tearकरोwn_cpu(अचिन्हित पूर्णांक cpu, काष्ठा xive_cpu *xc)
अणु
	s64 rc;
	u32 vp;

	अगर (xive_pool_vps == XIVE_INVALID_VP)
		वापस;

	/* Pull the pool VP from the CPU */
	in_be64(xive_tima + TM_SPC_PULL_POOL_CTX);

	/* Disable it */
	vp = xive_pool_vps + cpu;
	क्रम (;;) अणु
		rc = opal_xive_set_vp_info(vp, 0, 0);
		अगर (rc != OPAL_BUSY)
			अवरोध;
		msleep(OPAL_BUSY_DELAY_MS);
	पूर्ण
पूर्ण

व्योम xive_native_sync_source(u32 hw_irq)
अणु
	opal_xive_sync(XIVE_SYNC_EAS, hw_irq);
पूर्ण
EXPORT_SYMBOL_GPL(xive_native_sync_source);

व्योम xive_native_sync_queue(u32 hw_irq)
अणु
	opal_xive_sync(XIVE_SYNC_QUEUE, hw_irq);
पूर्ण
EXPORT_SYMBOL_GPL(xive_native_sync_queue);

अटल स्थिर काष्ठा xive_ops xive_native_ops = अणु
	.populate_irq_data	= xive_native_populate_irq_data,
	.configure_irq		= xive_native_configure_irq,
	.get_irq_config		= xive_native_get_irq_config,
	.setup_queue		= xive_native_setup_queue,
	.cleanup_queue		= xive_native_cleanup_queue,
	.match			= xive_native_match,
	.shutकरोwn		= xive_native_shutकरोwn,
	.update_pending		= xive_native_update_pending,
	.prepare_cpu		= xive_native_prepare_cpu,
	.setup_cpu		= xive_native_setup_cpu,
	.tearकरोwn_cpu		= xive_native_tearकरोwn_cpu,
	.sync_source		= xive_native_sync_source,
#अगर_घोषित CONFIG_SMP
	.get_ipi		= xive_native_get_ipi,
	.put_ipi		= xive_native_put_ipi,
#पूर्ण_अगर /* CONFIG_SMP */
	.name			= "native",
पूर्ण;

अटल bool xive_parse_provisioning(काष्ठा device_node *np)
अणु
	पूर्णांक rc;

	अगर (of_property_पढ़ो_u32(np, "ibm,xive-provision-page-size",
				 &xive_provision_size) < 0)
		वापस true;
	rc = of_property_count_elems_of_size(np, "ibm,xive-provision-chips", 4);
	अगर (rc < 0) अणु
		pr_err("Error %d getting provision chips array\n", rc);
		वापस false;
	पूर्ण
	xive_provision_chip_count = rc;
	अगर (rc == 0)
		वापस true;

	xive_provision_chips = kसुस्मृति(4, xive_provision_chip_count,
				       GFP_KERNEL);
	अगर (WARN_ON(!xive_provision_chips))
		वापस false;

	rc = of_property_पढ़ो_u32_array(np, "ibm,xive-provision-chips",
					xive_provision_chips,
					xive_provision_chip_count);
	अगर (rc < 0) अणु
		pr_err("Error %d reading provision chips array\n", rc);
		वापस false;
	पूर्ण

	xive_provision_cache = kmem_cache_create("xive-provision",
						 xive_provision_size,
						 xive_provision_size,
						 0, शून्य);
	अगर (!xive_provision_cache) अणु
		pr_err("Failed to allocate provision cache\n");
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम xive_native_setup_pools(व्योम)
अणु
	/* Allocate a pool big enough */
	pr_debug("XIVE: Allocating VP block for pool size %u\n", nr_cpu_ids);

	xive_pool_vps = xive_native_alloc_vp_block(nr_cpu_ids);
	अगर (WARN_ON(xive_pool_vps == XIVE_INVALID_VP))
		pr_err("XIVE: Failed to allocate pool VP, KVM might not function\n");

	pr_debug("XIVE: Pool VPs allocated at 0x%x for %u max CPUs\n",
		 xive_pool_vps, nr_cpu_ids);
पूर्ण

u32 xive_native_शेष_eq_shअगरt(व्योम)
अणु
	वापस xive_queue_shअगरt;
पूर्ण
EXPORT_SYMBOL_GPL(xive_native_शेष_eq_shअगरt);

अचिन्हित दीर्घ xive_tima_os;
EXPORT_SYMBOL_GPL(xive_tima_os);

bool __init xive_native_init(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा resource r;
	व्योम __iomem *tima;
	काष्ठा property *prop;
	u8 max_prio = 7;
	स्थिर __be32 *p;
	u32 val, cpu;
	s64 rc;

	अगर (xive_cmdline_disabled)
		वापस false;

	pr_devel("xive_native_init()\n");
	np = of_find_compatible_node(शून्य, शून्य, "ibm,opal-xive-pe");
	अगर (!np) अणु
		pr_devel("not found !\n");
		वापस false;
	पूर्ण
	pr_devel("Found %pOF\n", np);

	/* Resource 1 is HV winकरोw */
	अगर (of_address_to_resource(np, 1, &r)) अणु
		pr_err("Failed to get thread mgmnt area resource\n");
		वापस false;
	पूर्ण
	tima = ioremap(r.start, resource_size(&r));
	अगर (!tima) अणु
		pr_err("Failed to map thread mgmnt area\n");
		वापस false;
	पूर्ण

	/* Read number of priorities */
	अगर (of_property_पढ़ो_u32(np, "ibm,xive-#priorities", &val) == 0)
		max_prio = val - 1;

	/* Iterate the EQ sizes and pick one */
	of_property_क्रम_each_u32(np, "ibm,xive-eq-sizes", prop, p, val) अणु
		xive_queue_shअगरt = val;
		अगर (val == PAGE_SHIFT)
			अवरोध;
	पूर्ण

	/* Do we support single escalation */
	अगर (of_get_property(np, "single-escalation-support", शून्य) != शून्य)
		xive_has_single_esc = true;

	/* Configure Thपढ़ो Management areas क्रम KVM */
	क्रम_each_possible_cpu(cpu)
		kvmppc_set_xive_tima(cpu, r.start, tima);

	/* Resource 2 is OS winकरोw */
	अगर (of_address_to_resource(np, 2, &r)) अणु
		pr_err("Failed to get thread mgmnt area resource\n");
		वापस false;
	पूर्ण

	xive_tima_os = r.start;

	/* Grab size of provisionning pages */
	xive_parse_provisioning(np);

	/* Switch the XIVE to exploitation mode */
	rc = opal_xive_reset(OPAL_XIVE_MODE_EXPL);
	अगर (rc) अणु
		pr_err("Switch to exploitation mode failed with error %lld\n", rc);
		वापस false;
	पूर्ण

	/* Setup some dummy HV pool VPs */
	xive_native_setup_pools();

	/* Initialize XIVE core with our backend */
	अगर (!xive_core_init(np, &xive_native_ops, tima, TM_QW3_HV_PHYS,
			    max_prio)) अणु
		opal_xive_reset(OPAL_XIVE_MODE_EMU);
		वापस false;
	पूर्ण
	pr_info("Using %dkB queues\n", 1 << (xive_queue_shअगरt - 10));
	वापस true;
पूर्ण

अटल bool xive_native_provision_pages(व्योम)
अणु
	u32 i;
	व्योम *p;

	क्रम (i = 0; i < xive_provision_chip_count; i++) अणु
		u32 chip = xive_provision_chips[i];

		/*
		 * XXX TODO: Try to make the allocation local to the node where
		 * the chip resides.
		 */
		p = kmem_cache_alloc(xive_provision_cache, GFP_KERNEL);
		अगर (!p) अणु
			pr_err("Failed to allocate provisioning page\n");
			वापस false;
		पूर्ण
		kmemleak_ignore(p);
		opal_xive_करोnate_page(chip, __pa(p));
	पूर्ण
	वापस true;
पूर्ण

u32 xive_native_alloc_vp_block(u32 max_vcpus)
अणु
	s64 rc;
	u32 order;

	order = fls(max_vcpus) - 1;
	अगर (max_vcpus > (1 << order))
		order++;

	pr_debug("VP block alloc, for max VCPUs %d use order %d\n",
		 max_vcpus, order);

	क्रम (;;) अणु
		rc = opal_xive_alloc_vp_block(order);
		चयन (rc) अणु
		हाल OPAL_BUSY:
			msleep(OPAL_BUSY_DELAY_MS);
			अवरोध;
		हाल OPAL_XIVE_PROVISIONING:
			अगर (!xive_native_provision_pages())
				वापस XIVE_INVALID_VP;
			अवरोध;
		शेष:
			अगर (rc < 0) अणु
				pr_err("OPAL failed to allocate VCPUs order %d, err %lld\n",
				       order, rc);
				वापस XIVE_INVALID_VP;
			पूर्ण
			वापस rc;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(xive_native_alloc_vp_block);

व्योम xive_native_मुक्त_vp_block(u32 vp_base)
अणु
	s64 rc;

	अगर (vp_base == XIVE_INVALID_VP)
		वापस;

	rc = opal_xive_मुक्त_vp_block(vp_base);
	अगर (rc < 0)
		pr_warn("OPAL error %lld freeing VP block\n", rc);
पूर्ण
EXPORT_SYMBOL_GPL(xive_native_मुक्त_vp_block);

पूर्णांक xive_native_enable_vp(u32 vp_id, bool single_escalation)
अणु
	s64 rc;
	u64 flags = OPAL_XIVE_VP_ENABLED;

	अगर (single_escalation)
		flags |= OPAL_XIVE_VP_SINGLE_ESCALATION;
	क्रम (;;) अणु
		rc = opal_xive_set_vp_info(vp_id, flags, 0);
		अगर (rc != OPAL_BUSY)
			अवरोध;
		msleep(OPAL_BUSY_DELAY_MS);
	पूर्ण
	अगर (rc)
		vp_err(vp_id, "Failed to enable VP : %lld\n", rc);
	वापस rc ? -EIO : 0;
पूर्ण
EXPORT_SYMBOL_GPL(xive_native_enable_vp);

पूर्णांक xive_native_disable_vp(u32 vp_id)
अणु
	s64 rc;

	क्रम (;;) अणु
		rc = opal_xive_set_vp_info(vp_id, 0, 0);
		अगर (rc != OPAL_BUSY)
			अवरोध;
		msleep(OPAL_BUSY_DELAY_MS);
	पूर्ण
	अगर (rc)
		vp_err(vp_id, "Failed to disable VP : %lld\n", rc);
	वापस rc ? -EIO : 0;
पूर्ण
EXPORT_SYMBOL_GPL(xive_native_disable_vp);

पूर्णांक xive_native_get_vp_info(u32 vp_id, u32 *out_cam_id, u32 *out_chip_id)
अणु
	__be64 vp_cam_be;
	__be32 vp_chip_id_be;
	s64 rc;

	rc = opal_xive_get_vp_info(vp_id, शून्य, &vp_cam_be, शून्य, &vp_chip_id_be);
	अगर (rc) अणु
		vp_err(vp_id, "Failed to get VP info : %lld\n", rc);
		वापस -EIO;
	पूर्ण
	*out_cam_id = be64_to_cpu(vp_cam_be) & 0xffffffffu;
	*out_chip_id = be32_to_cpu(vp_chip_id_be);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xive_native_get_vp_info);

bool xive_native_has_single_escalation(व्योम)
अणु
	वापस xive_has_single_esc;
पूर्ण
EXPORT_SYMBOL_GPL(xive_native_has_single_escalation);

पूर्णांक xive_native_get_queue_info(u32 vp_id, u32 prio,
			       u64 *out_qpage,
			       u64 *out_qsize,
			       u64 *out_qeoi_page,
			       u32 *out_escalate_irq,
			       u64 *out_qflags)
अणु
	__be64 qpage;
	__be64 qsize;
	__be64 qeoi_page;
	__be32 escalate_irq;
	__be64 qflags;
	s64 rc;

	rc = opal_xive_get_queue_info(vp_id, prio, &qpage, &qsize,
				      &qeoi_page, &escalate_irq, &qflags);
	अगर (rc) अणु
		vp_err(vp_id, "failed to get queue %d info : %lld\n", prio, rc);
		वापस -EIO;
	पूर्ण

	अगर (out_qpage)
		*out_qpage = be64_to_cpu(qpage);
	अगर (out_qsize)
		*out_qsize = be32_to_cpu(qsize);
	अगर (out_qeoi_page)
		*out_qeoi_page = be64_to_cpu(qeoi_page);
	अगर (out_escalate_irq)
		*out_escalate_irq = be32_to_cpu(escalate_irq);
	अगर (out_qflags)
		*out_qflags = be64_to_cpu(qflags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xive_native_get_queue_info);

पूर्णांक xive_native_get_queue_state(u32 vp_id, u32 prio, u32 *qtoggle, u32 *qindex)
अणु
	__be32 opal_qtoggle;
	__be32 opal_qindex;
	s64 rc;

	rc = opal_xive_get_queue_state(vp_id, prio, &opal_qtoggle,
				       &opal_qindex);
	अगर (rc) अणु
		vp_err(vp_id, "failed to get queue %d state : %lld\n", prio, rc);
		वापस -EIO;
	पूर्ण

	अगर (qtoggle)
		*qtoggle = be32_to_cpu(opal_qtoggle);
	अगर (qindex)
		*qindex = be32_to_cpu(opal_qindex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xive_native_get_queue_state);

पूर्णांक xive_native_set_queue_state(u32 vp_id, u32 prio, u32 qtoggle, u32 qindex)
अणु
	s64 rc;

	rc = opal_xive_set_queue_state(vp_id, prio, qtoggle, qindex);
	अगर (rc) अणु
		vp_err(vp_id, "failed to set queue %d state : %lld\n", prio, rc);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xive_native_set_queue_state);

bool xive_native_has_queue_state_support(व्योम)
अणु
	वापस opal_check_token(OPAL_XIVE_GET_QUEUE_STATE) &&
		opal_check_token(OPAL_XIVE_SET_QUEUE_STATE);
पूर्ण
EXPORT_SYMBOL_GPL(xive_native_has_queue_state_support);

पूर्णांक xive_native_get_vp_state(u32 vp_id, u64 *out_state)
अणु
	__be64 state;
	s64 rc;

	rc = opal_xive_get_vp_state(vp_id, &state);
	अगर (rc) अणु
		vp_err(vp_id, "failed to get vp state : %lld\n", rc);
		वापस -EIO;
	पूर्ण

	अगर (out_state)
		*out_state = be64_to_cpu(state);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xive_native_get_vp_state);

machine_arch_initcall(घातernv, xive_core_debug_init);
