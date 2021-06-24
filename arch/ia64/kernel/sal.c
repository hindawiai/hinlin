<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * System Abstraction Layer (SAL) पूर्णांकerface routines.
 *
 * Copyright (C) 1998, 1999, 2001, 2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 * Copyright (C) 1999 VA Linux Systems
 * Copyright (C) 1999 Walt Drummond <drummond@valinux.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/sal.h>
#समावेश <यंत्र/pal.h>
#समावेश <यंत्र/xtp.h>

 __cacheline_aligned DEFINE_SPINLOCK(sal_lock);
अचिन्हित दीर्घ sal_platक्रमm_features;

अचिन्हित लघु sal_revision;
अचिन्हित लघु sal_version;

#घोषणा SAL_MAJOR(x) ((x) >> 8)
#घोषणा SAL_MINOR(x) ((x) & 0xff)

अटल काष्ठा अणु
	व्योम *addr;	/* function entry poपूर्णांक */
	व्योम *gpval;	/* gp value to use */
पूर्ण pdesc;

अटल दीर्घ
शेष_handler (व्योम)
अणु
	वापस -1;
पूर्ण

ia64_sal_handler ia64_sal = (ia64_sal_handler) शेष_handler;
ia64_sal_desc_ptc_t *ia64_ptc_करोमुख्य_info;

स्थिर अक्षर *
ia64_sal_म_त्रुटि (दीर्घ status)
अणु
	स्थिर अक्षर *str;
	चयन (status) अणु
	      हाल 0: str = "Call completed without error"; अवरोध;
	      हाल 1: str = "Effect a warm boot of the system to complete "
			      "the update"; अवरोध;
	      हाल -1: str = "Not implemented"; अवरोध;
	      हाल -2: str = "Invalid argument"; अवरोध;
	      हाल -3: str = "Call completed with error"; अवरोध;
	      हाल -4: str = "Virtual address not registered"; अवरोध;
	      हाल -5: str = "No information available"; अवरोध;
	      हाल -6: str = "Insufficient space to add the entry"; अवरोध;
	      हाल -7: str = "Invalid entry_addr value"; अवरोध;
	      हाल -8: str = "Invalid interrupt vector"; अवरोध;
	      हाल -9: str = "Requested memory not available"; अवरोध;
	      हाल -10: str = "Unable to write to the NVM device"; अवरोध;
	      हाल -11: str = "Invalid partition type specified"; अवरोध;
	      हाल -12: str = "Invalid NVM_Object id specified"; अवरोध;
	      हाल -13: str = "NVM_Object already has the maximum number "
				"of partitions"; अवरोध;
	      हाल -14: str = "Insufficient space in partition for the "
				"requested write sub-function"; अवरोध;
	      हाल -15: str = "Insufficient data buffer space for the "
				"requested read record sub-function"; अवरोध;
	      हाल -16: str = "Scratch buffer required for the write/delete "
				"sub-function"; अवरोध;
	      हाल -17: str = "Insufficient space in the NVM_Object for the "
				"requested create sub-function"; अवरोध;
	      हाल -18: str = "Invalid value specified in the partition_rec "
				"argument"; अवरोध;
	      हाल -19: str = "Record oriented I/O not supported for this "
				"partition"; अवरोध;
	      हाल -20: str = "Bad format of record to be written or "
				"required keyword variable not "
				"specified"; अवरोध;
	      शेष: str = "Unknown SAL status code"; अवरोध;
	पूर्ण
	वापस str;
पूर्ण

व्योम __init
ia64_sal_handler_init (व्योम *entry_poपूर्णांक, व्योम *gpval)
अणु
	/* fill in the SAL procedure descriptor and poपूर्णांक ia64_sal to it: */
	pdesc.addr = entry_poपूर्णांक;
	pdesc.gpval = gpval;
	ia64_sal = (ia64_sal_handler) &pdesc;
पूर्ण

अटल व्योम __init
check_versions (काष्ठा ia64_sal_systab *systab)
अणु
	sal_revision = (systab->sal_rev_major << 8) | systab->sal_rev_minor;
	sal_version = (systab->sal_b_rev_major << 8) | systab->sal_b_rev_minor;

	/* Check क्रम broken firmware */
	अगर ((sal_revision == SAL_VERSION_CODE(49, 29))
	    && (sal_version == SAL_VERSION_CODE(49, 29)))
	अणु
		/*
		 * Old firmware क्रम zx2000 prototypes have this weird version number,
		 * reset it to something sane.
		 */
		sal_revision = SAL_VERSION_CODE(2, 8);
		sal_version = SAL_VERSION_CODE(0, 0);
	पूर्ण
पूर्ण

अटल व्योम __init
sal_desc_entry_poपूर्णांक (व्योम *p)
अणु
	काष्ठा ia64_sal_desc_entry_poपूर्णांक *ep = p;
	ia64_pal_handler_init(__va(ep->pal_proc));
	ia64_sal_handler_init(__va(ep->sal_proc), __va(ep->gp));
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल व्योम __init
set_smp_redirect (पूर्णांक flag)
अणु
#अगर_अघोषित CONFIG_HOTPLUG_CPU
	अगर (no_पूर्णांक_routing)
		smp_पूर्णांक_redirect &= ~flag;
	अन्यथा
		smp_पूर्णांक_redirect |= flag;
#अन्यथा
	/*
	 * For CPU Hotplug we करोnt want to करो any chipset supported
	 * पूर्णांकerrupt redirection. The reason is this would require that
	 * All पूर्णांकerrupts be stopped and hard bind the irq to a cpu.
	 * Later when the पूर्णांकerrupt is fired we need to set the redir hपूर्णांक
	 * on again in the vector. This is cumbersome क्रम something that the
	 * user mode irq balancer will solve anyways.
	 */
	no_पूर्णांक_routing=1;
	smp_पूर्णांक_redirect &= ~flag;
#पूर्ण_अगर
पूर्ण
#अन्यथा
#घोषणा set_smp_redirect(flag)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

अटल व्योम __init
sal_desc_platक्रमm_feature (व्योम *p)
अणु
	काष्ठा ia64_sal_desc_platक्रमm_feature *pf = p;
	sal_platक्रमm_features = pf->feature_mask;

	prपूर्णांकk(KERN_INFO "SAL Platform features:");
	अगर (!sal_platक्रमm_features) अणु
		prपूर्णांकk(" None\n");
		वापस;
	पूर्ण

	अगर (sal_platक्रमm_features & IA64_SAL_PLATFORM_FEATURE_BUS_LOCK)
		prपूर्णांकk(" BusLock");
	अगर (sal_platक्रमm_features & IA64_SAL_PLATFORM_FEATURE_IRQ_REसूची_HINT) अणु
		prपूर्णांकk(" IRQ_Redirection");
		set_smp_redirect(SMP_IRQ_REसूचीECTION);
	पूर्ण
	अगर (sal_platक्रमm_features & IA64_SAL_PLATFORM_FEATURE_IPI_REसूची_HINT) अणु
		prपूर्णांकk(" IPI_Redirection");
		set_smp_redirect(SMP_IPI_REसूचीECTION);
	पूर्ण
	अगर (sal_platक्रमm_features & IA64_SAL_PLATFORM_FEATURE_ITC_DRIFT)
		prपूर्णांकk(" ITC_Drift");
	prपूर्णांकk("\n");
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल व्योम __init
sal_desc_ap_wakeup (व्योम *p)
अणु
	काष्ठा ia64_sal_desc_ap_wakeup *ap = p;

	चयन (ap->mechanism) अणु
	हाल IA64_SAL_AP_EXTERNAL_INT:
		ap_wakeup_vector = ap->vector;
		prपूर्णांकk(KERN_INFO "SAL: AP wakeup using external interrupt "
				"vector 0x%lx\n", ap_wakeup_vector);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "SAL: AP wakeup mechanism unsupported!\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम __init
chk_noपूर्णांकroute_opt(व्योम)
अणु
	अक्षर *cp;

	क्रम (cp = boot_command_line; *cp; ) अणु
		अगर (स_भेद(cp, "nointroute", 10) == 0) अणु
			no_पूर्णांक_routing = 1;
			prपूर्णांकk ("no_int_routing on\n");
			अवरोध;
		पूर्ण अन्यथा अणु
			जबतक (*cp != ' ' && *cp)
				++cp;
			जबतक (*cp == ' ')
				++cp;
		पूर्ण
	पूर्ण
पूर्ण

#अन्यथा
अटल व्योम __init sal_desc_ap_wakeup(व्योम *p) अणु पूर्ण
#पूर्ण_अगर

/*
 * HP rx5670 firmware polls क्रम पूर्णांकerrupts during SAL_CACHE_FLUSH by पढ़ोing
 * cr.ivr, but it never ग_लिखोs cr.eoi.  This leaves any पूर्णांकerrupt marked as
 * "in-service" and masks other पूर्णांकerrupts of equal or lower priority.
 *
 * HP पूर्णांकernal defect reports: F1859, F2775, F3031.
 */
अटल पूर्णांक sal_cache_flush_drops_पूर्णांकerrupts;

अटल पूर्णांक __init
क्रमce_pal_cache_flush(अक्षर *str)
अणु
	sal_cache_flush_drops_पूर्णांकerrupts = 1;
	वापस 0;
पूर्ण
early_param("force_pal_cache_flush", क्रमce_pal_cache_flush);

व्योम __init
check_sal_cache_flush (व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक cpu;
	u64 vector, cache_type = 3;
	काष्ठा ia64_sal_retval isrv;

	अगर (sal_cache_flush_drops_पूर्णांकerrupts)
		वापस;

	cpu = get_cpu();
	local_irq_save(flags);

	/*
	 * Send ourselves a समयr पूर्णांकerrupt, रुको until it's reported, and see
	 * अगर SAL_CACHE_FLUSH drops it.
	 */
	ia64_send_ipi(cpu, IA64_TIMER_VECTOR, IA64_IPI_DM_INT, 0);

	जबतक (!ia64_get_irr(IA64_TIMER_VECTOR))
		cpu_relax();

	SAL_CALL(isrv, SAL_CACHE_FLUSH, cache_type, 0, 0, 0, 0, 0, 0);

	अगर (isrv.status)
		prपूर्णांकk(KERN_ERR "SAL_CAL_FLUSH failed with %ld\n", isrv.status);

	अगर (ia64_get_irr(IA64_TIMER_VECTOR)) अणु
		vector = ia64_get_ivr();
		ia64_eoi();
		WARN_ON(vector != IA64_TIMER_VECTOR);
	पूर्ण अन्यथा अणु
		sal_cache_flush_drops_पूर्णांकerrupts = 1;
		prपूर्णांकk(KERN_ERR "SAL: SAL_CACHE_FLUSH drops interrupts; "
			"PAL_CACHE_FLUSH will be used instead\n");
		ia64_eoi();
	पूर्ण

	local_irq_restore(flags);
	put_cpu();
पूर्ण

s64
ia64_sal_cache_flush (u64 cache_type)
अणु
	काष्ठा ia64_sal_retval isrv;

	अगर (sal_cache_flush_drops_पूर्णांकerrupts) अणु
		अचिन्हित दीर्घ flags;
		u64 progress;
		s64 rc;

		progress = 0;
		local_irq_save(flags);
		rc = ia64_pal_cache_flush(cache_type,
			PAL_CACHE_FLUSH_INVALIDATE, &progress, शून्य);
		local_irq_restore(flags);
		वापस rc;
	पूर्ण

	SAL_CALL(isrv, SAL_CACHE_FLUSH, cache_type, 0, 0, 0, 0, 0, 0);
	वापस isrv.status;
पूर्ण
EXPORT_SYMBOL_GPL(ia64_sal_cache_flush);

व्योम __init
ia64_sal_init (काष्ठा ia64_sal_systab *systab)
अणु
	अक्षर *p;
	पूर्णांक i;

	अगर (!systab) अणु
		prपूर्णांकk(KERN_WARNING "Hmm, no SAL System Table.\n");
		वापस;
	पूर्ण

	अगर (म_भेदन(systab->signature, "SST_", 4) != 0)
		prपूर्णांकk(KERN_ERR "bad signature in system table!");

	check_versions(systab);
#अगर_घोषित CONFIG_SMP
	chk_noपूर्णांकroute_opt();
#पूर्ण_अगर

	/* revisions are coded in BCD, so %x करोes the job क्रम us */
	prपूर्णांकk(KERN_INFO "SAL %x.%x: %.32s %.32s%sversion %x.%x\n",
			SAL_MAJOR(sal_revision), SAL_MINOR(sal_revision),
			systab->oem_id, systab->product_id,
			systab->product_id[0] ? " " : "",
			SAL_MAJOR(sal_version), SAL_MINOR(sal_version));

	p = (अक्षर *) (systab + 1);
	क्रम (i = 0; i < systab->entry_count; i++) अणु
		/*
		 * The first byte of each entry type contains the type
		 * descriptor.
		 */
		चयन (*p) अणु
		हाल SAL_DESC_ENTRY_POINT:
			sal_desc_entry_poपूर्णांक(p);
			अवरोध;
		हाल SAL_DESC_PLATFORM_FEATURE:
			sal_desc_platक्रमm_feature(p);
			अवरोध;
		हाल SAL_DESC_PTC:
			ia64_ptc_करोमुख्य_info = (ia64_sal_desc_ptc_t *)p;
			अवरोध;
		हाल SAL_DESC_AP_WAKEUP:
			sal_desc_ap_wakeup(p);
			अवरोध;
		पूर्ण
		p += SAL_DESC_SIZE(*p);
	पूर्ण

पूर्ण

पूर्णांक
ia64_sal_oemcall(काष्ठा ia64_sal_retval *isrvp, u64 oemfunc, u64 arg1,
		 u64 arg2, u64 arg3, u64 arg4, u64 arg5, u64 arg6, u64 arg7)
अणु
	अगर (oemfunc < IA64_SAL_OEMFUNC_MIN || oemfunc > IA64_SAL_OEMFUNC_MAX)
		वापस -1;
	SAL_CALL(*isrvp, oemfunc, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ia64_sal_oemcall);

पूर्णांक
ia64_sal_oemcall_nolock(काष्ठा ia64_sal_retval *isrvp, u64 oemfunc, u64 arg1,
			u64 arg2, u64 arg3, u64 arg4, u64 arg5, u64 arg6,
			u64 arg7)
अणु
	अगर (oemfunc < IA64_SAL_OEMFUNC_MIN || oemfunc > IA64_SAL_OEMFUNC_MAX)
		वापस -1;
	SAL_CALL_NOLOCK(*isrvp, oemfunc, arg1, arg2, arg3, arg4, arg5, arg6,
			arg7);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ia64_sal_oemcall_nolock);

पूर्णांक
ia64_sal_oemcall_reentrant(काष्ठा ia64_sal_retval *isrvp, u64 oemfunc,
			   u64 arg1, u64 arg2, u64 arg3, u64 arg4, u64 arg5,
			   u64 arg6, u64 arg7)
अणु
	अगर (oemfunc < IA64_SAL_OEMFUNC_MIN || oemfunc > IA64_SAL_OEMFUNC_MAX)
		वापस -1;
	SAL_CALL_REENTRANT(*isrvp, oemfunc, arg1, arg2, arg3, arg4, arg5, arg6,
			   arg7);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ia64_sal_oemcall_reentrant);

दीर्घ
ia64_sal_freq_base (अचिन्हित दीर्घ which, अचिन्हित दीर्घ *ticks_per_second,
		    अचिन्हित दीर्घ *drअगरt_info)
अणु
	काष्ठा ia64_sal_retval isrv;

	SAL_CALL(isrv, SAL_FREQ_BASE, which, 0, 0, 0, 0, 0, 0);
	*ticks_per_second = isrv.v0;
	*drअगरt_info = isrv.v1;
	वापस isrv.status;
पूर्ण
EXPORT_SYMBOL_GPL(ia64_sal_freq_base);
