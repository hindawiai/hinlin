<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * CPU-Measurement Counter Facility Support - Common Layer
 *
 *  Copyright IBM Corp. 2019
 *  Author(s): Hendrik Brueckner <brueckner@linux.ibm.com>
 */
#घोषणा KMSG_COMPONENT	"cpum_cf_common"
#घोषणा pr_fmt(fmt)	KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/percpu.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/ctl_reg.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/cpu_mcf.h>

/* Per-CPU event काष्ठाure क्रम the counter facility */
DEFINE_PER_CPU(काष्ठा cpu_cf_events, cpu_cf_events) = अणु
	.ctr_set = अणु
		[CPUMF_CTR_SET_BASIC]	= ATOMIC_INIT(0),
		[CPUMF_CTR_SET_USER]	= ATOMIC_INIT(0),
		[CPUMF_CTR_SET_CRYPTO]	= ATOMIC_INIT(0),
		[CPUMF_CTR_SET_EXT]	= ATOMIC_INIT(0),
		[CPUMF_CTR_SET_MT_DIAG] = ATOMIC_INIT(0),
	पूर्ण,
	.alert = ATOMIC64_INIT(0),
	.state = 0,
	.flags = 0,
	.txn_flags = 0,
पूर्ण;
/* Indicator whether the CPU-Measurement Counter Facility Support is पढ़ोy */
अटल bool cpum_cf_initalized;

/* CPU-measurement alerts क्रम the counter facility */
अटल व्योम cpumf_measurement_alert(काष्ठा ext_code ext_code,
				    अचिन्हित पूर्णांक alert, अचिन्हित दीर्घ unused)
अणु
	काष्ठा cpu_cf_events *cpuhw;

	अगर (!(alert & CPU_MF_INT_CF_MASK))
		वापस;

	inc_irq_stat(IRQEXT_CMC);
	cpuhw = this_cpu_ptr(&cpu_cf_events);

	/* Measurement alerts are shared and might happen when the PMU
	 * is not reserved.  Ignore these alerts in this हाल. */
	अगर (!(cpuhw->flags & PMU_F_RESERVED))
		वापस;

	/* counter authorization change alert */
	अगर (alert & CPU_MF_INT_CF_CACA)
		qctri(&cpuhw->info);

	/* loss of counter data alert */
	अगर (alert & CPU_MF_INT_CF_LCDA)
		pr_err("CPU[%i] Counter data was lost\n", smp_processor_id());

	/* loss of MT counter data alert */
	अगर (alert & CPU_MF_INT_CF_MTDA)
		pr_warn("CPU[%i] MT counter data was lost\n",
			smp_processor_id());

	/* store alert क्रम special handling by in-kernel users */
	atomic64_or(alert, &cpuhw->alert);
पूर्ण

#घोषणा PMC_INIT      0
#घोषणा PMC_RELEASE   1
अटल व्योम cpum_cf_setup_cpu(व्योम *flags)
अणु
	काष्ठा cpu_cf_events *cpuhw = this_cpu_ptr(&cpu_cf_events);

	चयन (*((पूर्णांक *) flags)) अणु
	हाल PMC_INIT:
		स_रखो(&cpuhw->info, 0, माप(cpuhw->info));
		qctri(&cpuhw->info);
		cpuhw->flags |= PMU_F_RESERVED;
		अवरोध;

	हाल PMC_RELEASE:
		cpuhw->flags &= ~PMU_F_RESERVED;
		अवरोध;
	पूर्ण

	/* Disable CPU counter sets */
	lcctl(0);
पूर्ण

bool kernel_cpumcf_avail(व्योम)
अणु
	वापस cpum_cf_initalized;
पूर्ण
EXPORT_SYMBOL(kernel_cpumcf_avail);


/* Reserve/release functions क्रम sharing perf hardware */
अटल DEFINE_SPINLOCK(cpumcf_owner_lock);
अटल व्योम *cpumcf_owner;

/* Initialize the CPU-measurement counter facility */
पूर्णांक __kernel_cpumcf_begin(व्योम)
अणु
	पूर्णांक flags = PMC_INIT;
	पूर्णांक err = 0;

	spin_lock(&cpumcf_owner_lock);
	अगर (cpumcf_owner)
		err = -EBUSY;
	अन्यथा
		cpumcf_owner = __builtin_वापस_address(0);
	spin_unlock(&cpumcf_owner_lock);
	अगर (err)
		वापस err;

	on_each_cpu(cpum_cf_setup_cpu, &flags, 1);
	irq_subclass_रेजिस्टर(IRQ_SUBCLASS_MEASUREMENT_ALERT);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(__kernel_cpumcf_begin);

/* Obtain the CPU-measurement alerts क्रम the counter facility */
अचिन्हित दीर्घ kernel_cpumcf_alert(पूर्णांक clear)
अणु
	काष्ठा cpu_cf_events *cpuhw = this_cpu_ptr(&cpu_cf_events);
	अचिन्हित दीर्घ alert;

	alert = atomic64_पढ़ो(&cpuhw->alert);
	अगर (clear)
		atomic64_set(&cpuhw->alert, 0);

	वापस alert;
पूर्ण
EXPORT_SYMBOL(kernel_cpumcf_alert);

/* Release the CPU-measurement counter facility */
व्योम __kernel_cpumcf_end(व्योम)
अणु
	पूर्णांक flags = PMC_RELEASE;

	on_each_cpu(cpum_cf_setup_cpu, &flags, 1);
	irq_subclass_unरेजिस्टर(IRQ_SUBCLASS_MEASUREMENT_ALERT);

	spin_lock(&cpumcf_owner_lock);
	cpumcf_owner = शून्य;
	spin_unlock(&cpumcf_owner_lock);
पूर्ण
EXPORT_SYMBOL(__kernel_cpumcf_end);

अटल पूर्णांक cpum_cf_setup(अचिन्हित पूर्णांक cpu, पूर्णांक flags)
अणु
	local_irq_disable();
	cpum_cf_setup_cpu(&flags);
	local_irq_enable();
	वापस 0;
पूर्ण

अटल पूर्णांक cpum_cf_online_cpu(अचिन्हित पूर्णांक cpu)
अणु
	वापस cpum_cf_setup(cpu, PMC_INIT);
पूर्ण

अटल पूर्णांक cpum_cf_offline_cpu(अचिन्हित पूर्णांक cpu)
अणु
	वापस cpum_cf_setup(cpu, PMC_RELEASE);
पूर्ण

/* Return the maximum possible counter set size (in number of 8 byte counters)
 * depending on type and model number.
 */
माप_प्रकार cpum_cf_ctrset_size(क्रमागत cpumf_ctr_set ctrset,
			   काष्ठा cpumf_ctr_info *info)
अणु
	माप_प्रकार ctrset_size = 0;

	चयन (ctrset) अणु
	हाल CPUMF_CTR_SET_BASIC:
		अगर (info->cfvn >= 1)
			ctrset_size = 6;
		अवरोध;
	हाल CPUMF_CTR_SET_USER:
		अगर (info->cfvn == 1)
			ctrset_size = 6;
		अन्यथा अगर (info->cfvn >= 3)
			ctrset_size = 2;
		अवरोध;
	हाल CPUMF_CTR_SET_CRYPTO:
		अगर (info->csvn >= 1 && info->csvn <= 5)
			ctrset_size = 16;
		अन्यथा अगर (info->csvn == 6)
			ctrset_size = 20;
		अवरोध;
	हाल CPUMF_CTR_SET_EXT:
		अगर (info->csvn == 1)
			ctrset_size = 32;
		अन्यथा अगर (info->csvn == 2)
			ctrset_size = 48;
		अन्यथा अगर (info->csvn >= 3 && info->csvn <= 5)
			ctrset_size = 128;
		अन्यथा अगर (info->csvn == 6)
			ctrset_size = 160;
		अवरोध;
	हाल CPUMF_CTR_SET_MT_DIAG:
		अगर (info->csvn > 3)
			ctrset_size = 48;
		अवरोध;
	हाल CPUMF_CTR_SET_MAX:
		अवरोध;
	पूर्ण

	वापस ctrset_size;
पूर्ण

अटल पूर्णांक __init cpum_cf_init(व्योम)
अणु
	पूर्णांक rc;

	अगर (!cpum_cf_avail())
		वापस -ENODEV;

	/* clear bit 15 of cr0 to unauthorize problem-state to
	 * extract measurement counters */
	ctl_clear_bit(0, 48);

	/* रेजिस्टर handler क्रम measurement-alert पूर्णांकerruptions */
	rc = रेजिस्टर_बाह्यal_irq(EXT_IRQ_MEASURE_ALERT,
				   cpumf_measurement_alert);
	अगर (rc) अणु
		pr_err("Registering for CPU-measurement alerts "
		       "failed with rc=%i\n", rc);
		वापस rc;
	पूर्ण

	rc = cpuhp_setup_state(CPUHP_AP_PERF_S390_CF_ONLINE,
				"perf/s390/cf:online",
				cpum_cf_online_cpu, cpum_cf_offline_cpu);
	अगर (!rc)
		cpum_cf_initalized = true;

	वापस rc;
पूर्ण
early_initcall(cpum_cf_init);
