<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* pcr.c: Generic sparc64 perक्रमmance counter infraकाष्ठाure.
 *
 * Copyright (C) 2009 David S. Miller (davem@davemloft.net)
 */
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>

#समावेश <linux/irq_work.h>
#समावेश <linux/ftrace.h>

#समावेश <यंत्र/pil.h>
#समावेश <यंत्र/pcr.h>
#समावेश <यंत्र/nmi.h>
#समावेश <यंत्र/asi.h>
#समावेश <यंत्र/spitfire.h>

/* This code is shared between various users of the perक्रमmance
 * counters.  Users will be oprofile, pseuकरो-NMI watchकरोg, and the
 * perf_event support layer.
 */

/* Perक्रमmance counter पूर्णांकerrupts run unmasked at PIL level 15.
 * Thereक्रमe we can't करो things like wakeups and other work
 * that expects IRQ disabling to be adhered to in locking etc.
 *
 * Thereक्रमe in such situations we defer the work by संकेतling
 * a lower level cpu IRQ.
 */
व्योम __irq_entry deferred_pcr_work_irq(पूर्णांक irq, काष्ठा pt_regs *regs)
अणु
	काष्ठा pt_regs *old_regs;

	clear_softपूर्णांक(1 << PIL_DEFERRED_PCR_WORK);

	old_regs = set_irq_regs(regs);
	irq_enter();
#अगर_घोषित CONFIG_IRQ_WORK
	irq_work_run();
#पूर्ण_अगर
	irq_निकास();
	set_irq_regs(old_regs);
पूर्ण

व्योम arch_irq_work_उठाओ(व्योम)
अणु
	set_softपूर्णांक(1 << PIL_DEFERRED_PCR_WORK);
पूर्ण

स्थिर काष्ठा pcr_ops *pcr_ops;
EXPORT_SYMBOL_GPL(pcr_ops);

अटल u64 direct_pcr_पढ़ो(अचिन्हित दीर्घ reg_num)
अणु
	u64 val;

	WARN_ON_ONCE(reg_num != 0);
	__यंत्र__ __अस्थिर__("rd %%pcr, %0" : "=r" (val));
	वापस val;
पूर्ण

अटल व्योम direct_pcr_ग_लिखो(अचिन्हित दीर्घ reg_num, u64 val)
अणु
	WARN_ON_ONCE(reg_num != 0);
	__यंत्र__ __अस्थिर__("wr %0, 0x0, %%pcr" : : "r" (val));
पूर्ण

अटल u64 direct_pic_पढ़ो(अचिन्हित दीर्घ reg_num)
अणु
	u64 val;

	WARN_ON_ONCE(reg_num != 0);
	__यंत्र__ __अस्थिर__("rd %%pic, %0" : "=r" (val));
	वापस val;
पूर्ण

अटल व्योम direct_pic_ग_लिखो(अचिन्हित दीर्घ reg_num, u64 val)
अणु
	WARN_ON_ONCE(reg_num != 0);

	/* Blackbird errata workaround.  See commentary in
	 * arch/sparc64/kernel/smp.c:smp_percpu_समयr_पूर्णांकerrupt()
	 * क्रम more inक्रमmation.
	 */
	__यंत्र__ __अस्थिर__("ba,pt	%%xcc, 99f\n\t"
			     " nop\n\t"
			     ".align	64\n"
			  "99:wr	%0, 0x0, %%pic\n\t"
			     "rd	%%pic, %%g0" : : "r" (val));
पूर्ण

अटल u64 direct_picl_value(अचिन्हित पूर्णांक nmi_hz)
अणु
	u32 delta = local_cpu_data().घड़ी_प्रकारick / nmi_hz;

	वापस ((u64)((0 - delta) & 0xffffffff)) << 32;
पूर्ण

अटल स्थिर काष्ठा pcr_ops direct_pcr_ops = अणु
	.पढ़ो_pcr		= direct_pcr_पढ़ो,
	.ग_लिखो_pcr		= direct_pcr_ग_लिखो,
	.पढ़ो_pic		= direct_pic_पढ़ो,
	.ग_लिखो_pic		= direct_pic_ग_लिखो,
	.nmi_picl_value		= direct_picl_value,
	.pcr_nmi_enable		= (PCR_PIC_PRIV | PCR_STRACE | PCR_UTRACE),
	.pcr_nmi_disable	= PCR_PIC_PRIV,
पूर्ण;

अटल व्योम n2_pcr_ग_लिखो(अचिन्हित दीर्घ reg_num, u64 val)
अणु
	अचिन्हित दीर्घ ret;

	WARN_ON_ONCE(reg_num != 0);
	अगर (val & PCR_N2_HTRACE) अणु
		ret = sun4v_niagara2_setperf(HV_N2_PERF_SPARC_CTL, val);
		अगर (ret != HV_EOK)
			direct_pcr_ग_लिखो(reg_num, val);
	पूर्ण अन्यथा
		direct_pcr_ग_लिखो(reg_num, val);
पूर्ण

अटल u64 n2_picl_value(अचिन्हित पूर्णांक nmi_hz)
अणु
	u32 delta = local_cpu_data().घड़ी_प्रकारick / (nmi_hz << 2);

	वापस ((u64)((0 - delta) & 0xffffffff)) << 32;
पूर्ण

अटल स्थिर काष्ठा pcr_ops n2_pcr_ops = अणु
	.पढ़ो_pcr		= direct_pcr_पढ़ो,
	.ग_लिखो_pcr		= n2_pcr_ग_लिखो,
	.पढ़ो_pic		= direct_pic_पढ़ो,
	.ग_लिखो_pic		= direct_pic_ग_लिखो,
	.nmi_picl_value		= n2_picl_value,
	.pcr_nmi_enable		= (PCR_PIC_PRIV | PCR_STRACE | PCR_UTRACE |
				   PCR_N2_TOE_OV1 |
				   (2 << PCR_N2_SL1_SHIFT) |
				   (0xff << PCR_N2_MASK1_SHIFT)),
	.pcr_nmi_disable	= PCR_PIC_PRIV,
पूर्ण;

अटल u64 n4_pcr_पढ़ो(अचिन्हित दीर्घ reg_num)
अणु
	अचिन्हित दीर्घ val;

	(व्योम) sun4v_vt_get_perfreg(reg_num, &val);

	वापस val;
पूर्ण

अटल व्योम n4_pcr_ग_लिखो(अचिन्हित दीर्घ reg_num, u64 val)
अणु
	(व्योम) sun4v_vt_set_perfreg(reg_num, val);
पूर्ण

अटल u64 n4_pic_पढ़ो(अचिन्हित दीर्घ reg_num)
अणु
	अचिन्हित दीर्घ val;

	__यंत्र__ __अस्थिर__("ldxa [%1] %2, %0"
			     : "=r" (val)
			     : "r" (reg_num * 0x8UL), "i" (ASI_PIC));

	वापस val;
पूर्ण

अटल व्योम n4_pic_ग_लिखो(अचिन्हित दीर्घ reg_num, u64 val)
अणु
	__यंत्र__ __अस्थिर__("stxa %0, [%1] %2"
			     : /* no outमाला_दो */
			     : "r" (val), "r" (reg_num * 0x8UL), "i" (ASI_PIC));
पूर्ण

अटल u64 n4_picl_value(अचिन्हित पूर्णांक nmi_hz)
अणु
	u32 delta = local_cpu_data().घड़ी_प्रकारick / (nmi_hz << 2);

	वापस ((u64)((0 - delta) & 0xffffffff));
पूर्ण

अटल स्थिर काष्ठा pcr_ops n4_pcr_ops = अणु
	.पढ़ो_pcr		= n4_pcr_पढ़ो,
	.ग_लिखो_pcr		= n4_pcr_ग_लिखो,
	.पढ़ो_pic		= n4_pic_पढ़ो,
	.ग_लिखो_pic		= n4_pic_ग_लिखो,
	.nmi_picl_value		= n4_picl_value,
	.pcr_nmi_enable		= (PCR_N4_PICNPT | PCR_N4_STRACE |
				   PCR_N4_UTRACE | PCR_N4_TOE |
				   (26 << PCR_N4_SL_SHIFT)),
	.pcr_nmi_disable	= PCR_N4_PICNPT,
पूर्ण;

अटल u64 n5_pcr_पढ़ो(अचिन्हित दीर्घ reg_num)
अणु
	अचिन्हित दीर्घ val;

	(व्योम) sun4v_t5_get_perfreg(reg_num, &val);

	वापस val;
पूर्ण

अटल व्योम n5_pcr_ग_लिखो(अचिन्हित दीर्घ reg_num, u64 val)
अणु
	(व्योम) sun4v_t5_set_perfreg(reg_num, val);
पूर्ण

अटल स्थिर काष्ठा pcr_ops n5_pcr_ops = अणु
	.पढ़ो_pcr		= n5_pcr_पढ़ो,
	.ग_लिखो_pcr		= n5_pcr_ग_लिखो,
	.पढ़ो_pic		= n4_pic_पढ़ो,
	.ग_लिखो_pic		= n4_pic_ग_लिखो,
	.nmi_picl_value		= n4_picl_value,
	.pcr_nmi_enable		= (PCR_N4_PICNPT | PCR_N4_STRACE |
				   PCR_N4_UTRACE | PCR_N4_TOE |
				   (26 << PCR_N4_SL_SHIFT)),
	.pcr_nmi_disable	= PCR_N4_PICNPT,
पूर्ण;

अटल u64 m7_pcr_पढ़ो(अचिन्हित दीर्घ reg_num)
अणु
	अचिन्हित दीर्घ val;

	(व्योम) sun4v_m7_get_perfreg(reg_num, &val);

	वापस val;
पूर्ण

अटल व्योम m7_pcr_ग_लिखो(अचिन्हित दीर्घ reg_num, u64 val)
अणु
	(व्योम) sun4v_m7_set_perfreg(reg_num, val);
पूर्ण

अटल स्थिर काष्ठा pcr_ops m7_pcr_ops = अणु
	.पढ़ो_pcr		= m7_pcr_पढ़ो,
	.ग_लिखो_pcr		= m7_pcr_ग_लिखो,
	.पढ़ो_pic		= n4_pic_पढ़ो,
	.ग_लिखो_pic		= n4_pic_ग_लिखो,
	.nmi_picl_value		= n4_picl_value,
	.pcr_nmi_enable		= (PCR_N4_PICNPT | PCR_N4_STRACE |
				   PCR_N4_UTRACE | PCR_N4_TOE |
				   (26 << PCR_N4_SL_SHIFT)),
	.pcr_nmi_disable	= PCR_N4_PICNPT,
पूर्ण;

अटल अचिन्हित दीर्घ perf_hsvc_group;
अटल अचिन्हित दीर्घ perf_hsvc_major;
अटल अचिन्हित दीर्घ perf_hsvc_minor;

अटल पूर्णांक __init रेजिस्टर_perf_hsvc(व्योम)
अणु
	अचिन्हित दीर्घ hverror;

	अगर (tlb_type == hypervisor) अणु
		चयन (sun4v_chip_type) अणु
		हाल SUN4V_CHIP_NIAGARA1:
			perf_hsvc_group = HV_GRP_NIAG_PERF;
			अवरोध;

		हाल SUN4V_CHIP_NIAGARA2:
			perf_hsvc_group = HV_GRP_N2_CPU;
			अवरोध;

		हाल SUN4V_CHIP_NIAGARA3:
			perf_hsvc_group = HV_GRP_KT_CPU;
			अवरोध;

		हाल SUN4V_CHIP_NIAGARA4:
			perf_hsvc_group = HV_GRP_VT_CPU;
			अवरोध;

		हाल SUN4V_CHIP_NIAGARA5:
			perf_hsvc_group = HV_GRP_T5_CPU;
			अवरोध;

		हाल SUN4V_CHIP_SPARC_M7:
			perf_hsvc_group = HV_GRP_M7_PERF;
			अवरोध;

		शेष:
			वापस -ENODEV;
		पूर्ण


		perf_hsvc_major = 1;
		perf_hsvc_minor = 0;
		hverror = sun4v_hvapi_रेजिस्टर(perf_hsvc_group,
					       perf_hsvc_major,
					       &perf_hsvc_minor);
		अगर (hverror) अणु
			pr_err("perfmon: Could not register hvapi(0x%lx).\n",
			       hverror);
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __init unरेजिस्टर_perf_hsvc(व्योम)
अणु
	अगर (tlb_type != hypervisor)
		वापस;
	sun4v_hvapi_unरेजिस्टर(perf_hsvc_group);
पूर्ण

अटल पूर्णांक __init setup_sun4v_pcr_ops(व्योम)
अणु
	पूर्णांक ret = 0;

	चयन (sun4v_chip_type) अणु
	हाल SUN4V_CHIP_NIAGARA1:
	हाल SUN4V_CHIP_NIAGARA2:
	हाल SUN4V_CHIP_NIAGARA3:
		pcr_ops = &n2_pcr_ops;
		अवरोध;

	हाल SUN4V_CHIP_NIAGARA4:
		pcr_ops = &n4_pcr_ops;
		अवरोध;

	हाल SUN4V_CHIP_NIAGARA5:
		pcr_ops = &n5_pcr_ops;
		अवरोध;

	हाल SUN4V_CHIP_SPARC_M7:
		pcr_ops = &m7_pcr_ops;
		अवरोध;

	शेष:
		ret = -ENODEV;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक __init pcr_arch_init(व्योम)
अणु
	पूर्णांक err = रेजिस्टर_perf_hsvc();

	अगर (err)
		वापस err;

	चयन (tlb_type) अणु
	हाल hypervisor:
		err = setup_sun4v_pcr_ops();
		अगर (err)
			जाओ out_unरेजिस्टर;
		अवरोध;

	हाल cheetah:
	हाल cheetah_plus:
		pcr_ops = &direct_pcr_ops;
		अवरोध;

	हाल spitfire:
		/* UltraSPARC-I/II and derivatives lack a profile
		 * counter overflow पूर्णांकerrupt so we can't make use of
		 * their hardware currently.
		 */
		fallthrough;
	शेष:
		err = -ENODEV;
		जाओ out_unरेजिस्टर;
	पूर्ण

	वापस nmi_init();

out_unरेजिस्टर:
	unरेजिस्टर_perf_hsvc();
	वापस err;
पूर्ण
