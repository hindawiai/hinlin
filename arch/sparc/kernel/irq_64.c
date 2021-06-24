<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* irq.c: UltraSparc IRQ handling/init/registry.
 *
 * Copyright (C) 1997, 2007, 2008 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1998  Eddie C. Dost    (ecd@skynet.be)
 * Copyright (C) 1998  Jakub Jelinek    (jj@ultra.linux.cz)
 */

#समावेश <linux/sched.h>
#समावेश <linux/linkage.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/processor.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/upa.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/समयr.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/starfire.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/cpudata.h>
#समावेश <यंत्र/auxपन.स>
#समावेश <यंत्र/head.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/softirq_stack.h>

#समावेश "entry.h"
#समावेश "cpumap.h"
#समावेश "kstack.h"

काष्ठा ino_bucket *ivector_table;
अचिन्हित दीर्घ ivector_table_pa;

/* On several sun4u processors, it is illegal to mix bypass and
 * non-bypass accesses.  Thereक्रमe we access all INO buckets
 * using bypass accesses only.
 */
अटल अचिन्हित दीर्घ bucket_get_chain_pa(अचिन्हित दीर्घ bucket_pa)
अणु
	अचिन्हित दीर्घ ret;

	__यंत्र__ __अस्थिर__("ldxa	[%1] %2, %0"
			     : "=&r" (ret)
			     : "r" (bucket_pa +
				    दुरत्व(काष्ठा ino_bucket,
					     __irq_chain_pa)),
			       "i" (ASI_PHYS_USE_EC));

	वापस ret;
पूर्ण

अटल व्योम bucket_clear_chain_pa(अचिन्हित दीर्घ bucket_pa)
अणु
	__यंत्र__ __अस्थिर__("stxa	%%g0, [%0] %1"
			     : /* no outमाला_दो */
			     : "r" (bucket_pa +
				    दुरत्व(काष्ठा ino_bucket,
					     __irq_chain_pa)),
			       "i" (ASI_PHYS_USE_EC));
पूर्ण

अटल अचिन्हित पूर्णांक bucket_get_irq(अचिन्हित दीर्घ bucket_pa)
अणु
	अचिन्हित पूर्णांक ret;

	__यंत्र__ __अस्थिर__("lduwa	[%1] %2, %0"
			     : "=&r" (ret)
			     : "r" (bucket_pa +
				    दुरत्व(काष्ठा ino_bucket,
					     __irq)),
			       "i" (ASI_PHYS_USE_EC));

	वापस ret;
पूर्ण

अटल व्योम bucket_set_irq(अचिन्हित दीर्घ bucket_pa, अचिन्हित पूर्णांक irq)
अणु
	__यंत्र__ __अस्थिर__("stwa	%0, [%1] %2"
			     : /* no outमाला_दो */
			     : "r" (irq),
			       "r" (bucket_pa +
				    दुरत्व(काष्ठा ino_bucket,
					     __irq)),
			       "i" (ASI_PHYS_USE_EC));
पूर्ण

#घोषणा irq_work_pa(__cpu)	&(trap_block[(__cpu)].irq_worklist_pa)

अटल अचिन्हित दीर्घ hvirq_major __initdata;
अटल पूर्णांक __init early_hvirq_major(अक्षर *p)
अणु
	पूर्णांक rc = kम_से_अदीर्घ(p, 10, &hvirq_major);

	वापस rc;
पूर्ण
early_param("hvirq", early_hvirq_major);

अटल पूर्णांक hv_irq_version;

/* Major version 2.0 of HV_GRP_INTR added support क्रम the VIRQ cookie
 * based पूर्णांकerfaces, but:
 *
 * 1) Several OSs, Solaris and Linux included, use them even when only
 *    negotiating version 1.0 (or failing to negotiate at all).  So the
 *    hypervisor has a workaround that provides the VIRQ पूर्णांकerfaces even
 *    when only verion 1.0 of the API is in use.
 *
 * 2) Second, and more importantly, with major version 2.0 these VIRQ
 *    पूर्णांकerfaces only were actually hooked up क्रम LDC पूर्णांकerrupts, even
 *    though the Hypervisor specअगरication clearly stated:
 *
 *	The new पूर्णांकerrupt API functions will be available to a guest
 *	when it negotiates version 2.0 in the पूर्णांकerrupt API group 0x2. When
 *	a guest negotiates version 2.0, all पूर्णांकerrupt sources will only
 *	support using the cookie पूर्णांकerface, and any attempt to use the
 *	version 1.0 पूर्णांकerrupt APIs numbered 0xa0 to 0xa6 will result in the
 *	ENOTSUPPORTED error being वापसed.
 *
 *   with an emphasis on "all interrupt sources".
 *
 * To correct this, major version 3.0 was created which करोes actually
 * support VIRQs क्रम all पूर्णांकerrupt sources (not just LDC devices).  So
 * अगर we want to move completely over the cookie based VIRQs we must
 * negotiate major version 3.0 or later of HV_GRP_INTR.
 */
अटल bool sun4v_cookie_only_virqs(व्योम)
अणु
	अगर (hv_irq_version >= 3)
		वापस true;
	वापस false;
पूर्ण

अटल व्योम __init irq_init_hv(व्योम)
अणु
	अचिन्हित दीर्घ hv_error, major, minor = 0;

	अगर (tlb_type != hypervisor)
		वापस;

	अगर (hvirq_major)
		major = hvirq_major;
	अन्यथा
		major = 3;

	hv_error = sun4v_hvapi_रेजिस्टर(HV_GRP_INTR, major, &minor);
	अगर (!hv_error)
		hv_irq_version = major;
	अन्यथा
		hv_irq_version = 1;

	pr_info("SUN4V: Using IRQ API major %d, cookie only virqs %s\n",
		hv_irq_version,
		sun4v_cookie_only_virqs() ? "enabled" : "disabled");
पूर्ण

/* This function is क्रम the समयr पूर्णांकerrupt.*/
पूर्णांक __init arch_probe_nr_irqs(व्योम)
अणु
	वापस 1;
पूर्ण

#घोषणा DEFAULT_NUM_IVECS	(0xfffU)
अटल अचिन्हित पूर्णांक nr_ivec = DEFAULT_NUM_IVECS;
#घोषणा NUM_IVECS (nr_ivec)

अटल अचिन्हित पूर्णांक __init size_nr_ivec(व्योम)
अणु
	अगर (tlb_type == hypervisor) अणु
		चयन (sun4v_chip_type) अणु
		/* Athena's devhandle|devino is large.*/
		हाल SUN4V_CHIP_SPARC64X:
			nr_ivec = 0xffff;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस nr_ivec;
पूर्ण

काष्ठा irq_handler_data अणु
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक dev_handle;
			अचिन्हित पूर्णांक dev_ino;
		पूर्ण;
		अचिन्हित दीर्घ sysino;
	पूर्ण;
	काष्ठा ino_bucket bucket;
	अचिन्हित दीर्घ	iclr;
	अचिन्हित दीर्घ	imap;
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक irq_data_to_handle(काष्ठा irq_data *data)
अणु
	काष्ठा irq_handler_data *ihd = irq_data_get_irq_handler_data(data);

	वापस ihd->dev_handle;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक irq_data_to_ino(काष्ठा irq_data *data)
अणु
	काष्ठा irq_handler_data *ihd = irq_data_get_irq_handler_data(data);

	वापस ihd->dev_ino;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ irq_data_to_sysino(काष्ठा irq_data *data)
अणु
	काष्ठा irq_handler_data *ihd = irq_data_get_irq_handler_data(data);

	वापस ihd->sysino;
पूर्ण

व्योम irq_मुक्त(अचिन्हित पूर्णांक irq)
अणु
	व्योम *data = irq_get_handler_data(irq);

	kमुक्त(data);
	irq_set_handler_data(irq, शून्य);
	irq_मुक्त_descs(irq, 1);
पूर्ण

अचिन्हित पूर्णांक irq_alloc(अचिन्हित पूर्णांक dev_handle, अचिन्हित पूर्णांक dev_ino)
अणु
	पूर्णांक irq;

	irq = __irq_alloc_descs(-1, 1, 1, numa_node_id(), शून्य, शून्य);
	अगर (irq <= 0)
		जाओ out;

	वापस irq;
out:
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक cookie_exists(u32 devhandle, अचिन्हित पूर्णांक devino)
अणु
	अचिन्हित दीर्घ hv_err, cookie;
	काष्ठा ino_bucket *bucket;
	अचिन्हित पूर्णांक irq = 0U;

	hv_err = sun4v_vपूर्णांकr_get_cookie(devhandle, devino, &cookie);
	अगर (hv_err) अणु
		pr_err("HV get cookie failed hv_err = %ld\n", hv_err);
		जाओ out;
	पूर्ण

	अगर (cookie & ((1UL << 63UL))) अणु
		cookie = ~cookie;
		bucket = (काष्ठा ino_bucket *) __va(cookie);
		irq = bucket->__irq;
	पूर्ण
out:
	वापस irq;
पूर्ण

अटल अचिन्हित पूर्णांक sysino_exists(u32 devhandle, अचिन्हित पूर्णांक devino)
अणु
	अचिन्हित दीर्घ sysino = sun4v_devino_to_sysino(devhandle, devino);
	काष्ठा ino_bucket *bucket;
	अचिन्हित पूर्णांक irq;

	bucket = &ivector_table[sysino];
	irq = bucket_get_irq(__pa(bucket));

	वापस irq;
पूर्ण

व्योम ack_bad_irq(अचिन्हित पूर्णांक irq)
अणु
	pr_crit("BAD IRQ ack %d\n", irq);
पूर्ण

व्योम irq_install_pre_handler(पूर्णांक irq,
			     व्योम (*func)(अचिन्हित पूर्णांक, व्योम *, व्योम *),
			     व्योम *arg1, व्योम *arg2)
अणु
	pr_warn("IRQ pre handler NOT supported.\n");
पूर्ण

/*
 * /proc/पूर्णांकerrupts prपूर्णांकing:
 */
पूर्णांक arch_show_पूर्णांकerrupts(काष्ठा seq_file *p, पूर्णांक prec)
अणु
	पूर्णांक j;

	seq_म_लिखो(p, "NMI: ");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", cpu_data(j).__nmi_count);
	seq_म_लिखो(p, "     Non-maskable interrupts\n");
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक sun4u_compute_tid(अचिन्हित दीर्घ imap, अचिन्हित दीर्घ cpuid)
अणु
	अचिन्हित पूर्णांक tid;

	अगर (this_is_starfire) अणु
		tid = starfire_translate(imap, cpuid);
		tid <<= IMAP_TID_SHIFT;
		tid &= IMAP_TID_UPA;
	पूर्ण अन्यथा अणु
		अगर (tlb_type == cheetah || tlb_type == cheetah_plus) अणु
			अचिन्हित दीर्घ ver;

			__यंत्र__ ("rdpr %%ver, %0" : "=r" (ver));
			अगर ((ver >> 32UL) == __JALAPENO_ID ||
			    (ver >> 32UL) == __SERRANO_ID) अणु
				tid = cpuid << IMAP_TID_SHIFT;
				tid &= IMAP_TID_JBUS;
			पूर्ण अन्यथा अणु
				अचिन्हित पूर्णांक a = cpuid & 0x1f;
				अचिन्हित पूर्णांक n = (cpuid >> 5) & 0x1f;

				tid = ((a << IMAP_AID_SHIFT) |
				       (n << IMAP_NID_SHIFT));
				tid &= (IMAP_AID_SAFARI |
					IMAP_NID_SAFARI);
			पूर्ण
		पूर्ण अन्यथा अणु
			tid = cpuid << IMAP_TID_SHIFT;
			tid &= IMAP_TID_UPA;
		पूर्ण
	पूर्ण

	वापस tid;
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल पूर्णांक irq_choose_cpu(अचिन्हित पूर्णांक irq, स्थिर काष्ठा cpumask *affinity)
अणु
	cpumask_t mask;
	पूर्णांक cpuid;

	cpumask_copy(&mask, affinity);
	अगर (cpumask_equal(&mask, cpu_online_mask)) अणु
		cpuid = map_to_cpu(irq);
	पूर्ण अन्यथा अणु
		cpumask_t पंचांगp;

		cpumask_and(&पंचांगp, cpu_online_mask, &mask);
		cpuid = cpumask_empty(&पंचांगp) ? map_to_cpu(irq) : cpumask_first(&पंचांगp);
	पूर्ण

	वापस cpuid;
पूर्ण
#अन्यथा
#घोषणा irq_choose_cpu(irq, affinity)	\
	real_hard_smp_processor_id()
#पूर्ण_अगर

अटल व्योम sun4u_irq_enable(काष्ठा irq_data *data)
अणु
	काष्ठा irq_handler_data *handler_data;

	handler_data = irq_data_get_irq_handler_data(data);
	अगर (likely(handler_data)) अणु
		अचिन्हित दीर्घ cpuid, imap, val;
		अचिन्हित पूर्णांक tid;

		cpuid = irq_choose_cpu(data->irq,
				       irq_data_get_affinity_mask(data));
		imap = handler_data->imap;

		tid = sun4u_compute_tid(imap, cpuid);

		val = upa_पढ़ोq(imap);
		val &= ~(IMAP_TID_UPA | IMAP_TID_JBUS |
			 IMAP_AID_SAFARI | IMAP_NID_SAFARI);
		val |= tid | IMAP_VALID;
		upa_ग_लिखोq(val, imap);
		upa_ग_लिखोq(ICLR_IDLE, handler_data->iclr);
	पूर्ण
पूर्ण

अटल पूर्णांक sun4u_set_affinity(काष्ठा irq_data *data,
			       स्थिर काष्ठा cpumask *mask, bool क्रमce)
अणु
	काष्ठा irq_handler_data *handler_data;

	handler_data = irq_data_get_irq_handler_data(data);
	अगर (likely(handler_data)) अणु
		अचिन्हित दीर्घ cpuid, imap, val;
		अचिन्हित पूर्णांक tid;

		cpuid = irq_choose_cpu(data->irq, mask);
		imap = handler_data->imap;

		tid = sun4u_compute_tid(imap, cpuid);

		val = upa_पढ़ोq(imap);
		val &= ~(IMAP_TID_UPA | IMAP_TID_JBUS |
			 IMAP_AID_SAFARI | IMAP_NID_SAFARI);
		val |= tid | IMAP_VALID;
		upa_ग_लिखोq(val, imap);
		upa_ग_लिखोq(ICLR_IDLE, handler_data->iclr);
	पूर्ण

	वापस 0;
पूर्ण

/* Don't करो anything.  The desc->status check क्रम IRQ_DISABLED in
 * handler_irq() will skip the handler call and that will leave the
 * पूर्णांकerrupt in the sent state.  The next ->enable() call will hit the
 * ICLR रेजिस्टर to reset the state machine.
 *
 * This scheme is necessary, instead of clearing the Valid bit in the
 * IMAP रेजिस्टर, to handle the हाल of IMAP रेजिस्टरs being shared by
 * multiple INOs (and thus ICLR रेजिस्टरs).  Since we use a dअगरferent
 * भव IRQ क्रम each shared IMAP instance, the generic code thinks
 * there is only one user so it prematurely calls ->disable() on
 * मुक्त_irq().
 *
 * We have to provide an explicit ->disable() method instead of using
 * शून्य to get the शेष.  The reason is that अगर the generic code
 * sees that, it also hooks up a शेष ->shutकरोwn method which
 * invokes ->mask() which we करो not want.  See irq_chip_set_शेषs().
 */
अटल व्योम sun4u_irq_disable(काष्ठा irq_data *data)
अणु
पूर्ण

अटल व्योम sun4u_irq_eoi(काष्ठा irq_data *data)
अणु
	काष्ठा irq_handler_data *handler_data;

	handler_data = irq_data_get_irq_handler_data(data);
	अगर (likely(handler_data))
		upa_ग_लिखोq(ICLR_IDLE, handler_data->iclr);
पूर्ण

अटल व्योम sun4v_irq_enable(काष्ठा irq_data *data)
अणु
	अचिन्हित दीर्घ cpuid = irq_choose_cpu(data->irq,
					     irq_data_get_affinity_mask(data));
	अचिन्हित पूर्णांक ino = irq_data_to_sysino(data);
	पूर्णांक err;

	err = sun4v_पूर्णांकr_settarget(ino, cpuid);
	अगर (err != HV_EOK)
		prपूर्णांकk(KERN_ERR "sun4v_intr_settarget(%x,%lu): "
		       "err(%d)\n", ino, cpuid, err);
	err = sun4v_पूर्णांकr_setstate(ino, HV_INTR_STATE_IDLE);
	अगर (err != HV_EOK)
		prपूर्णांकk(KERN_ERR "sun4v_intr_setstate(%x): "
		       "err(%d)\n", ino, err);
	err = sun4v_पूर्णांकr_setenabled(ino, HV_INTR_ENABLED);
	अगर (err != HV_EOK)
		prपूर्णांकk(KERN_ERR "sun4v_intr_setenabled(%x): err(%d)\n",
		       ino, err);
पूर्ण

अटल पूर्णांक sun4v_set_affinity(काष्ठा irq_data *data,
			       स्थिर काष्ठा cpumask *mask, bool क्रमce)
अणु
	अचिन्हित दीर्घ cpuid = irq_choose_cpu(data->irq, mask);
	अचिन्हित पूर्णांक ino = irq_data_to_sysino(data);
	पूर्णांक err;

	err = sun4v_पूर्णांकr_settarget(ino, cpuid);
	अगर (err != HV_EOK)
		prपूर्णांकk(KERN_ERR "sun4v_intr_settarget(%x,%lu): "
		       "err(%d)\n", ino, cpuid, err);

	वापस 0;
पूर्ण

अटल व्योम sun4v_irq_disable(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक ino = irq_data_to_sysino(data);
	पूर्णांक err;

	err = sun4v_पूर्णांकr_setenabled(ino, HV_INTR_DISABLED);
	अगर (err != HV_EOK)
		prपूर्णांकk(KERN_ERR "sun4v_intr_setenabled(%x): "
		       "err(%d)\n", ino, err);
पूर्ण

अटल व्योम sun4v_irq_eoi(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक ino = irq_data_to_sysino(data);
	पूर्णांक err;

	err = sun4v_पूर्णांकr_setstate(ino, HV_INTR_STATE_IDLE);
	अगर (err != HV_EOK)
		prपूर्णांकk(KERN_ERR "sun4v_intr_setstate(%x): "
		       "err(%d)\n", ino, err);
पूर्ण

अटल व्योम sun4v_virq_enable(काष्ठा irq_data *data)
अणु
	अचिन्हित दीर्घ dev_handle = irq_data_to_handle(data);
	अचिन्हित दीर्घ dev_ino = irq_data_to_ino(data);
	अचिन्हित दीर्घ cpuid;
	पूर्णांक err;

	cpuid = irq_choose_cpu(data->irq, irq_data_get_affinity_mask(data));

	err = sun4v_vपूर्णांकr_set_target(dev_handle, dev_ino, cpuid);
	अगर (err != HV_EOK)
		prपूर्णांकk(KERN_ERR "sun4v_vintr_set_target(%lx,%lx,%lu): "
		       "err(%d)\n",
		       dev_handle, dev_ino, cpuid, err);
	err = sun4v_vपूर्णांकr_set_state(dev_handle, dev_ino,
				    HV_INTR_STATE_IDLE);
	अगर (err != HV_EOK)
		prपूर्णांकk(KERN_ERR "sun4v_vintr_set_state(%lx,%lx,"
		       "HV_INTR_STATE_IDLE): err(%d)\n",
		       dev_handle, dev_ino, err);
	err = sun4v_vपूर्णांकr_set_valid(dev_handle, dev_ino,
				    HV_INTR_ENABLED);
	अगर (err != HV_EOK)
		prपूर्णांकk(KERN_ERR "sun4v_vintr_set_state(%lx,%lx,"
		       "HV_INTR_ENABLED): err(%d)\n",
		       dev_handle, dev_ino, err);
पूर्ण

अटल पूर्णांक sun4v_virt_set_affinity(काष्ठा irq_data *data,
				    स्थिर काष्ठा cpumask *mask, bool क्रमce)
अणु
	अचिन्हित दीर्घ dev_handle = irq_data_to_handle(data);
	अचिन्हित दीर्घ dev_ino = irq_data_to_ino(data);
	अचिन्हित दीर्घ cpuid;
	पूर्णांक err;

	cpuid = irq_choose_cpu(data->irq, mask);

	err = sun4v_vपूर्णांकr_set_target(dev_handle, dev_ino, cpuid);
	अगर (err != HV_EOK)
		prपूर्णांकk(KERN_ERR "sun4v_vintr_set_target(%lx,%lx,%lu): "
		       "err(%d)\n",
		       dev_handle, dev_ino, cpuid, err);

	वापस 0;
पूर्ण

अटल व्योम sun4v_virq_disable(काष्ठा irq_data *data)
अणु
	अचिन्हित दीर्घ dev_handle = irq_data_to_handle(data);
	अचिन्हित दीर्घ dev_ino = irq_data_to_ino(data);
	पूर्णांक err;


	err = sun4v_vपूर्णांकr_set_valid(dev_handle, dev_ino,
				    HV_INTR_DISABLED);
	अगर (err != HV_EOK)
		prपूर्णांकk(KERN_ERR "sun4v_vintr_set_state(%lx,%lx,"
		       "HV_INTR_DISABLED): err(%d)\n",
		       dev_handle, dev_ino, err);
पूर्ण

अटल व्योम sun4v_virq_eoi(काष्ठा irq_data *data)
अणु
	अचिन्हित दीर्घ dev_handle = irq_data_to_handle(data);
	अचिन्हित दीर्घ dev_ino = irq_data_to_ino(data);
	पूर्णांक err;

	err = sun4v_vपूर्णांकr_set_state(dev_handle, dev_ino,
				    HV_INTR_STATE_IDLE);
	अगर (err != HV_EOK)
		prपूर्णांकk(KERN_ERR "sun4v_vintr_set_state(%lx,%lx,"
		       "HV_INTR_STATE_IDLE): err(%d)\n",
		       dev_handle, dev_ino, err);
पूर्ण

अटल काष्ठा irq_chip sun4u_irq = अणु
	.name			= "sun4u",
	.irq_enable		= sun4u_irq_enable,
	.irq_disable		= sun4u_irq_disable,
	.irq_eoi		= sun4u_irq_eoi,
	.irq_set_affinity	= sun4u_set_affinity,
	.flags			= IRQCHIP_EOI_IF_HANDLED,
पूर्ण;

अटल काष्ठा irq_chip sun4v_irq = अणु
	.name			= "sun4v",
	.irq_enable		= sun4v_irq_enable,
	.irq_disable		= sun4v_irq_disable,
	.irq_eoi		= sun4v_irq_eoi,
	.irq_set_affinity	= sun4v_set_affinity,
	.flags			= IRQCHIP_EOI_IF_HANDLED,
पूर्ण;

अटल काष्ठा irq_chip sun4v_virq = अणु
	.name			= "vsun4v",
	.irq_enable		= sun4v_virq_enable,
	.irq_disable		= sun4v_virq_disable,
	.irq_eoi		= sun4v_virq_eoi,
	.irq_set_affinity	= sun4v_virt_set_affinity,
	.flags			= IRQCHIP_EOI_IF_HANDLED,
पूर्ण;

अचिन्हित पूर्णांक build_irq(पूर्णांक inofixup, अचिन्हित दीर्घ iclr, अचिन्हित दीर्घ imap)
अणु
	काष्ठा irq_handler_data *handler_data;
	काष्ठा ino_bucket *bucket;
	अचिन्हित पूर्णांक irq;
	पूर्णांक ino;

	BUG_ON(tlb_type == hypervisor);

	ino = (upa_पढ़ोq(imap) & (IMAP_IGN | IMAP_INO)) + inofixup;
	bucket = &ivector_table[ino];
	irq = bucket_get_irq(__pa(bucket));
	अगर (!irq) अणु
		irq = irq_alloc(0, ino);
		bucket_set_irq(__pa(bucket), irq);
		irq_set_chip_and_handler_name(irq, &sun4u_irq,
					      handle_fasteoi_irq, "IVEC");
	पूर्ण

	handler_data = irq_get_handler_data(irq);
	अगर (unlikely(handler_data))
		जाओ out;

	handler_data = kzalloc(माप(काष्ठा irq_handler_data), GFP_ATOMIC);
	अगर (unlikely(!handler_data)) अणु
		prom_म_लिखो("IRQ: kzalloc(irq_handler_data) failed.\n");
		prom_halt();
	पूर्ण
	irq_set_handler_data(irq, handler_data);

	handler_data->imap  = imap;
	handler_data->iclr  = iclr;

out:
	वापस irq;
पूर्ण

अटल अचिन्हित पूर्णांक sun4v_build_common(u32 devhandle, अचिन्हित पूर्णांक devino,
		व्योम (*handler_data_init)(काष्ठा irq_handler_data *data,
		u32 devhandle, अचिन्हित पूर्णांक devino),
		काष्ठा irq_chip *chip)
अणु
	काष्ठा irq_handler_data *data;
	अचिन्हित पूर्णांक irq;

	irq = irq_alloc(devhandle, devino);
	अगर (!irq)
		जाओ out;

	data = kzalloc(माप(काष्ठा irq_handler_data), GFP_ATOMIC);
	अगर (unlikely(!data)) अणु
		pr_err("IRQ handler data allocation failed.\n");
		irq_मुक्त(irq);
		irq = 0;
		जाओ out;
	पूर्ण

	irq_set_handler_data(irq, data);
	handler_data_init(data, devhandle, devino);
	irq_set_chip_and_handler_name(irq, chip, handle_fasteoi_irq, "IVEC");
	data->imap = ~0UL;
	data->iclr = ~0UL;
out:
	वापस irq;
पूर्ण

अटल अचिन्हित दीर्घ cookie_assign(अचिन्हित पूर्णांक irq, u32 devhandle,
		अचिन्हित पूर्णांक devino)
अणु
	काष्ठा irq_handler_data *ihd = irq_get_handler_data(irq);
	अचिन्हित दीर्घ hv_error, cookie;

	/* handler_irq needs to find the irq. cookie is seen चिन्हित in
	 * sun4v_dev_monकरो and treated as a non ivector_table delivery.
	 */
	ihd->bucket.__irq = irq;
	cookie = ~__pa(&ihd->bucket);

	hv_error = sun4v_vपूर्णांकr_set_cookie(devhandle, devino, cookie);
	अगर (hv_error)
		pr_err("HV vintr set cookie failed = %ld\n", hv_error);

	वापस hv_error;
पूर्ण

अटल व्योम cookie_handler_data(काष्ठा irq_handler_data *data,
				u32 devhandle, अचिन्हित पूर्णांक devino)
अणु
	data->dev_handle = devhandle;
	data->dev_ino = devino;
पूर्ण

अटल अचिन्हित पूर्णांक cookie_build_irq(u32 devhandle, अचिन्हित पूर्णांक devino,
				     काष्ठा irq_chip *chip)
अणु
	अचिन्हित दीर्घ hv_error;
	अचिन्हित पूर्णांक irq;

	irq = sun4v_build_common(devhandle, devino, cookie_handler_data, chip);

	hv_error = cookie_assign(irq, devhandle, devino);
	अगर (hv_error) अणु
		irq_मुक्त(irq);
		irq = 0;
	पूर्ण

	वापस irq;
पूर्ण

अटल अचिन्हित पूर्णांक sun4v_build_cookie(u32 devhandle, अचिन्हित पूर्णांक devino)
अणु
	अचिन्हित पूर्णांक irq;

	irq = cookie_exists(devhandle, devino);
	अगर (irq)
		जाओ out;

	irq = cookie_build_irq(devhandle, devino, &sun4v_virq);

out:
	वापस irq;
पूर्ण

अटल व्योम sysino_set_bucket(अचिन्हित पूर्णांक irq)
अणु
	काष्ठा irq_handler_data *ihd = irq_get_handler_data(irq);
	काष्ठा ino_bucket *bucket;
	अचिन्हित दीर्घ sysino;

	sysino = sun4v_devino_to_sysino(ihd->dev_handle, ihd->dev_ino);
	BUG_ON(sysino >= nr_ivec);
	bucket = &ivector_table[sysino];
	bucket_set_irq(__pa(bucket), irq);
पूर्ण

अटल व्योम sysino_handler_data(काष्ठा irq_handler_data *data,
				u32 devhandle, अचिन्हित पूर्णांक devino)
अणु
	अचिन्हित दीर्घ sysino;

	sysino = sun4v_devino_to_sysino(devhandle, devino);
	data->sysino = sysino;
पूर्ण

अटल अचिन्हित पूर्णांक sysino_build_irq(u32 devhandle, अचिन्हित पूर्णांक devino,
				     काष्ठा irq_chip *chip)
अणु
	अचिन्हित पूर्णांक irq;

	irq = sun4v_build_common(devhandle, devino, sysino_handler_data, chip);
	अगर (!irq)
		जाओ out;

	sysino_set_bucket(irq);
out:
	वापस irq;
पूर्ण

अटल पूर्णांक sun4v_build_sysino(u32 devhandle, अचिन्हित पूर्णांक devino)
अणु
	पूर्णांक irq;

	irq = sysino_exists(devhandle, devino);
	अगर (irq)
		जाओ out;

	irq = sysino_build_irq(devhandle, devino, &sun4v_irq);
out:
	वापस irq;
पूर्ण

अचिन्हित पूर्णांक sun4v_build_irq(u32 devhandle, अचिन्हित पूर्णांक devino)
अणु
	अचिन्हित पूर्णांक irq;

	अगर (sun4v_cookie_only_virqs())
		irq = sun4v_build_cookie(devhandle, devino);
	अन्यथा
		irq = sun4v_build_sysino(devhandle, devino);

	वापस irq;
पूर्ण

अचिन्हित पूर्णांक sun4v_build_virq(u32 devhandle, अचिन्हित पूर्णांक devino)
अणु
	पूर्णांक irq;

	irq = cookie_build_irq(devhandle, devino, &sun4v_virq);
	अगर (!irq)
		जाओ out;

	/* This is borrowed from the original function.
	 */
	irq_set_status_flags(irq, IRQ_NOAUTOEN);

out:
	वापस irq;
पूर्ण

व्योम *hardirq_stack[NR_CPUS];
व्योम *softirq_stack[NR_CPUS];

व्योम __irq_entry handler_irq(पूर्णांक pil, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ pstate, bucket_pa;
	काष्ठा pt_regs *old_regs;
	व्योम *orig_sp;

	clear_softपूर्णांक(1 << pil);

	old_regs = set_irq_regs(regs);
	irq_enter();

	/* Grab an atomic snapshot of the pending IVECs.  */
	__यंत्र__ __अस्थिर__("rdpr	%%pstate, %0\n\t"
			     "wrpr	%0, %3, %%pstate\n\t"
			     "ldx	[%2], %1\n\t"
			     "stx	%%g0, [%2]\n\t"
			     "wrpr	%0, 0x0, %%pstate\n\t"
			     : "=&r" (pstate), "=&r" (bucket_pa)
			     : "r" (irq_work_pa(smp_processor_id())),
			       "i" (PSTATE_IE)
			     : "memory");

	orig_sp = set_hardirq_stack();

	जबतक (bucket_pa) अणु
		अचिन्हित दीर्घ next_pa;
		अचिन्हित पूर्णांक irq;

		next_pa = bucket_get_chain_pa(bucket_pa);
		irq = bucket_get_irq(bucket_pa);
		bucket_clear_chain_pa(bucket_pa);

		generic_handle_irq(irq);

		bucket_pa = next_pa;
	पूर्ण

	restore_hardirq_stack(orig_sp);

	irq_निकास();
	set_irq_regs(old_regs);
पूर्ण

व्योम करो_softirq_own_stack(व्योम)
अणु
	व्योम *orig_sp, *sp = softirq_stack[smp_processor_id()];

	sp += THREAD_SIZE - 192 - STACK_BIAS;

	__यंत्र__ __अस्थिर__("mov %%sp, %0\n\t"
			     "mov %1, %%sp"
			     : "=&r" (orig_sp)
			     : "r" (sp));
	__करो_softirq();
	__यंत्र__ __अस्थिर__("mov %0, %%sp"
			     : : "r" (orig_sp));
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
व्योम fixup_irqs(व्योम)
अणु
	अचिन्हित पूर्णांक irq;

	क्रम (irq = 0; irq < NR_IRQS; irq++) अणु
		काष्ठा irq_desc *desc = irq_to_desc(irq);
		काष्ठा irq_data *data;
		अचिन्हित दीर्घ flags;

		अगर (!desc)
			जारी;
		data = irq_desc_get_irq_data(desc);
		raw_spin_lock_irqsave(&desc->lock, flags);
		अगर (desc->action && !irqd_is_per_cpu(data)) अणु
			अगर (data->chip->irq_set_affinity)
				data->chip->irq_set_affinity(data,
					irq_data_get_affinity_mask(data),
					false);
		पूर्ण
		raw_spin_unlock_irqrestore(&desc->lock, flags);
	पूर्ण

	tick_ops->disable_irq();
पूर्ण
#पूर्ण_अगर

काष्ठा sun5_समयr अणु
	u64	count0;
	u64	limit0;
	u64	count1;
	u64	limit1;
पूर्ण;

अटल काष्ठा sun5_समयr *prom_समयrs;
अटल u64 prom_limit0, prom_limit1;

अटल व्योम map_prom_समयrs(व्योम)
अणु
	काष्ठा device_node *dp;
	स्थिर अचिन्हित पूर्णांक *addr;

	/* PROM समयr node hangs out in the top level of device siblings... */
	dp = of_find_node_by_path("/");
	dp = dp->child;
	जबतक (dp) अणु
		अगर (of_node_name_eq(dp, "counter-timer"))
			अवरोध;
		dp = dp->sibling;
	पूर्ण

	/* Assume अगर node is not present, PROM uses dअगरferent tick mechanism
	 * which we should not care about.
	 */
	अगर (!dp) अणु
		prom_समयrs = (काष्ठा sun5_समयr *) 0;
		वापस;
	पूर्ण

	/* If PROM is really using this, it must be mapped by him. */
	addr = of_get_property(dp, "address", शून्य);
	अगर (!addr) अणु
		prom_म_लिखो("PROM does not have timer mapped, trying to continue.\n");
		prom_समयrs = (काष्ठा sun5_समयr *) 0;
		वापस;
	पूर्ण
	prom_समयrs = (काष्ठा sun5_समयr *) ((अचिन्हित दीर्घ)addr[0]);
पूर्ण

अटल व्योम समाप्त_prom_समयr(व्योम)
अणु
	अगर (!prom_समयrs)
		वापस;

	/* Save them away क्रम later. */
	prom_limit0 = prom_समयrs->limit0;
	prom_limit1 = prom_समयrs->limit1;

	/* Just as in sun4c PROM uses समयr which ticks at IRQ 14.
	 * We turn both off here just to be paranoid.
	 */
	prom_समयrs->limit0 = 0;
	prom_समयrs->limit1 = 0;

	/* Wheee, eat the पूर्णांकerrupt packet too... */
	__यंत्र__ __अस्थिर__(
"	mov	0x40, %%g2\n"
"	ldxa	[%%g0] %0, %%g1\n"
"	ldxa	[%%g2] %1, %%g1\n"
"	stxa	%%g0, [%%g0] %0\n"
"	membar	#Sync\n"
	: /* no outमाला_दो */
	: "i" (ASI_INTR_RECEIVE), "i" (ASI_INTR_R)
	: "g1", "g2");
पूर्ण

व्योम notrace init_irqwork_curcpu(व्योम)
अणु
	पूर्णांक cpu = hard_smp_processor_id();

	trap_block[cpu].irq_worklist_pa = 0UL;
पूर्ण

/* Please be very careful with रेजिस्टर_one_monकरो() and
 * sun4v_रेजिस्टर_monकरो_queues().
 *
 * On SMP this माला_लो invoked from the CPU trampoline beक्रमe
 * the cpu has fully taken over the trap table from OBP,
 * and it's kernel stack + %g6 thपढ़ो रेजिस्टर state is
 * not fully cooked yet.
 *
 * Thereक्रमe you cannot make any OBP calls, not even prom_म_लिखो,
 * from these two routines.
 */
अटल व्योम notrace रेजिस्टर_one_monकरो(अचिन्हित दीर्घ paddr, अचिन्हित दीर्घ type,
				       अचिन्हित दीर्घ qmask)
अणु
	अचिन्हित दीर्घ num_entries = (qmask + 1) / 64;
	अचिन्हित दीर्घ status;

	status = sun4v_cpu_qconf(type, paddr, num_entries);
	अगर (status != HV_EOK) अणु
		prom_म_लिखो("SUN4V: sun4v_cpu_qconf(%lu:%lx:%lu) failed, "
			    "err %lu\n", type, paddr, num_entries, status);
		prom_halt();
	पूर्ण
पूर्ण

व्योम notrace sun4v_रेजिस्टर_monकरो_queues(पूर्णांक this_cpu)
अणु
	काष्ठा trap_per_cpu *tb = &trap_block[this_cpu];

	रेजिस्टर_one_monकरो(tb->cpu_monकरो_pa, HV_CPU_QUEUE_CPU_MONDO,
			   tb->cpu_monकरो_qmask);
	रेजिस्टर_one_monकरो(tb->dev_monकरो_pa, HV_CPU_QUEUE_DEVICE_MONDO,
			   tb->dev_monकरो_qmask);
	रेजिस्टर_one_monकरो(tb->resum_monकरो_pa, HV_CPU_QUEUE_RES_ERROR,
			   tb->resum_qmask);
	रेजिस्टर_one_monकरो(tb->nonresum_monकरो_pa, HV_CPU_QUEUE_NONRES_ERROR,
			   tb->nonresum_qmask);
पूर्ण

/* Each queue region must be a घातer of 2 multiple of 64 bytes in
 * size.  The base real address must be aligned to the size of the
 * region.  Thus, an 8KB queue must be 8KB aligned, क्रम example.
 */
अटल व्योम __init alloc_one_queue(अचिन्हित दीर्घ *pa_ptr, अचिन्हित दीर्घ qmask)
अणु
	अचिन्हित दीर्घ size = PAGE_ALIGN(qmask + 1);
	अचिन्हित दीर्घ order = get_order(size);
	अचिन्हित दीर्घ p;

	p = __get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO, order);
	अगर (!p) अणु
		prom_म_लिखो("SUN4V: Error, cannot allocate queue.\n");
		prom_halt();
	पूर्ण

	*pa_ptr = __pa(p);
पूर्ण

अटल व्योम __init init_cpu_send_monकरो_info(काष्ठा trap_per_cpu *tb)
अणु
#अगर_घोषित CONFIG_SMP
	अचिन्हित दीर्घ page;
	व्योम *monकरो, *p;

	BUILD_BUG_ON((NR_CPUS * माप(u16)) > PAGE_SIZE);

	/* Make sure monकरो block is 64byte aligned */
	p = kzalloc(127, GFP_KERNEL);
	अगर (!p) अणु
		prom_म_लिखो("SUN4V: Error, cannot allocate mondo block.\n");
		prom_halt();
	पूर्ण
	monकरो = (व्योम *)(((अचिन्हित दीर्घ)p + 63) & ~0x3f);
	tb->cpu_monकरो_block_pa = __pa(monकरो);

	page = get_zeroed_page(GFP_KERNEL);
	अगर (!page) अणु
		prom_म_लिखो("SUN4V: Error, cannot allocate cpu list page.\n");
		prom_halt();
	पूर्ण

	tb->cpu_list_pa = __pa(page);
#पूर्ण_अगर
पूर्ण

/* Allocate monकरो and error queues क्रम all possible cpus.  */
अटल व्योम __init sun4v_init_monकरो_queues(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा trap_per_cpu *tb = &trap_block[cpu];

		alloc_one_queue(&tb->cpu_monकरो_pa, tb->cpu_monकरो_qmask);
		alloc_one_queue(&tb->dev_monकरो_pa, tb->dev_monकरो_qmask);
		alloc_one_queue(&tb->resum_monकरो_pa, tb->resum_qmask);
		alloc_one_queue(&tb->resum_kernel_buf_pa, tb->resum_qmask);
		alloc_one_queue(&tb->nonresum_monकरो_pa, tb->nonresum_qmask);
		alloc_one_queue(&tb->nonresum_kernel_buf_pa,
				tb->nonresum_qmask);
	पूर्ण
पूर्ण

अटल व्योम __init init_send_monकरो_info(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा trap_per_cpu *tb = &trap_block[cpu];

		init_cpu_send_monकरो_info(tb);
	पूर्ण
पूर्ण

अटल काष्ठा irqaction समयr_irq_action = अणु
	.name = "timer",
पूर्ण;

अटल व्योम __init irq_ivector_init(व्योम)
अणु
	अचिन्हित दीर्घ size, order;
	अचिन्हित पूर्णांक ivecs;

	/* If we are करोing cookie only VIRQs then we करो not need the ivector
	 * table to process पूर्णांकerrupts.
	 */
	अगर (sun4v_cookie_only_virqs())
		वापस;

	ivecs = size_nr_ivec();
	size = माप(काष्ठा ino_bucket) * ivecs;
	order = get_order(size);
	ivector_table = (काष्ठा ino_bucket *)
		__get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO, order);
	अगर (!ivector_table) अणु
		prom_म_लिखो("Fatal error, cannot allocate ivector_table\n");
		prom_halt();
	पूर्ण
	__flush_dcache_range((अचिन्हित दीर्घ) ivector_table,
			     ((अचिन्हित दीर्घ) ivector_table) + size);

	ivector_table_pa = __pa(ivector_table);
पूर्ण

/* Only invoked on boot processor.*/
व्योम __init init_IRQ(व्योम)
अणु
	irq_init_hv();
	irq_ivector_init();
	map_prom_समयrs();
	समाप्त_prom_समयr();

	अगर (tlb_type == hypervisor)
		sun4v_init_monकरो_queues();

	init_send_monकरो_info();

	अगर (tlb_type == hypervisor) अणु
		/* Load up the boot cpu's entries.  */
		sun4v_रेजिस्टर_monकरो_queues(hard_smp_processor_id());
	पूर्ण

	/* We need to clear any IRQ's pending in the soft पूर्णांकerrupt
	 * रेजिस्टरs, a spurious one could be left around from the
	 * PROM समयr which we just disabled.
	 */
	clear_softपूर्णांक(get_softपूर्णांक());

	/* Now that ivector table is initialized, it is safe
	 * to receive IRQ vector traps.  We will normally take
	 * one or two right now, in हाल some device PROM used
	 * to boot us wants to speak to us.  We just ignore them.
	 */
	__यंत्र__ __अस्थिर__("rdpr	%%pstate, %%g1\n\t"
			     "or	%%g1, %0, %%g1\n\t"
			     "wrpr	%%g1, 0x0, %%pstate"
			     : /* No outमाला_दो */
			     : "i" (PSTATE_IE)
			     : "g1");

	irq_to_desc(0)->action = &समयr_irq_action;
पूर्ण
