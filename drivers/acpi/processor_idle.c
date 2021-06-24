<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * processor_idle - idle state submodule to the ACPI processor driver
 *
 *  Copyright (C) 2001, 2002 Andy Grover <andrew.grover@पूर्णांकel.com>
 *  Copyright (C) 2001, 2002 Paul Diefenbaugh <paul.s.diefenbaugh@पूर्णांकel.com>
 *  Copyright (C) 2004, 2005 Dominik Broकरोwski <linux@broकरो.de>
 *  Copyright (C) 2004  Anil S Keshavamurthy <anil.s.keshavamurthy@पूर्णांकel.com>
 *  			- Added processor hotplug support
 *  Copyright (C) 2005  Venkatesh Pallipadi <venkatesh.pallipadi@पूर्णांकel.com>
 *  			- Added support क्रम C3 on SMP
 */
#घोषणा pr_fmt(fmt) "ACPI: " fmt

#समावेश <linux/module.h>
#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/sched.h>       /* need_resched() */
#समावेश <linux/tick.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/cpu.h>
#समावेश <acpi/processor.h>

/*
 * Include the apic definitions क्रम x86 to have the APIC समयr related defines
 * available also क्रम UP (on SMP it माला_लो magically included via linux/smp.h).
 * यंत्र/acpi.h is not an option, as it would require more include magic. Also
 * creating an empty यंत्र-ia64/apic.h would just trade pest vs. cholera.
 */
#अगर_घोषित CONFIG_X86
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/cpu.h>
#पूर्ण_अगर

#घोषणा ACPI_IDLE_STATE_START	(IS_ENABLED(CONFIG_ARCH_HAS_CPU_RELAX) ? 1 : 0)

अटल अचिन्हित पूर्णांक max_cstate __पढ़ो_mostly = ACPI_PROCESSOR_MAX_POWER;
module_param(max_cstate, uपूर्णांक, 0000);
अटल अचिन्हित पूर्णांक nocst __पढ़ो_mostly;
module_param(nocst, uपूर्णांक, 0000);
अटल पूर्णांक bm_check_disable __पढ़ो_mostly;
module_param(bm_check_disable, uपूर्णांक, 0000);

अटल अचिन्हित पूर्णांक latency_factor __पढ़ो_mostly = 2;
module_param(latency_factor, uपूर्णांक, 0644);

अटल DEFINE_PER_CPU(काष्ठा cpuidle_device *, acpi_cpuidle_device);

काष्ठा cpuidle_driver acpi_idle_driver = अणु
	.name =		"acpi_idle",
	.owner =	THIS_MODULE,
पूर्ण;

#अगर_घोषित CONFIG_ACPI_PROCESSOR_CSTATE
अटल
DEFINE_PER_CPU(काष्ठा acpi_processor_cx * [CPUIDLE_STATE_MAX], acpi_cstate);

अटल पूर्णांक disabled_by_idle_boot_param(व्योम)
अणु
	वापस boot_option_idle_override == IDLE_POLL ||
		boot_option_idle_override == IDLE_HALT;
पूर्ण

/*
 * IBM ThinkPad R40e crashes mysteriously when going पूर्णांकo C2 or C3.
 * For now disable this. Probably a bug somewhere अन्यथा.
 *
 * To skip this limit, boot/load with a large max_cstate limit.
 */
अटल पूर्णांक set_max_cstate(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	अगर (max_cstate > ACPI_PROCESSOR_MAX_POWER)
		वापस 0;

	pr_notice("%s detected - limiting to C%ld max_cstate."
		  " Override with \"processor.max_cstate=%d\"\n", id->ident,
		  (दीर्घ)id->driver_data, ACPI_PROCESSOR_MAX_POWER + 1);

	max_cstate = (दीर्घ)id->driver_data;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id processor_घातer_dmi_table[] = अणु
	अणु set_max_cstate, "Clevo 5600D", अणु
	  DMI_MATCH(DMI_BIOS_VENDOR,"Phoenix Technologies LTD"),
	  DMI_MATCH(DMI_BIOS_VERSION,"SHE845M0.86C.0013.D.0302131307")पूर्ण,
	 (व्योम *)2पूर्ण,
	अणु set_max_cstate, "Pavilion zv5000", अणु
	  DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
	  DMI_MATCH(DMI_PRODUCT_NAME,"Pavilion zv5000 (DS502A#ABA)")पूर्ण,
	 (व्योम *)1पूर्ण,
	अणु set_max_cstate, "Asus L8400B", अणु
	  DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK Computer Inc."),
	  DMI_MATCH(DMI_PRODUCT_NAME,"L8400B series Notebook PC")पूर्ण,
	 (व्योम *)1पूर्ण,
	अणुपूर्ण,
पूर्ण;


/*
 * Callers should disable पूर्णांकerrupts beक्रमe the call and enable
 * पूर्णांकerrupts after वापस.
 */
अटल व्योम __cpuidle acpi_safe_halt(व्योम)
अणु
	अगर (!tअगर_need_resched()) अणु
		safe_halt();
		local_irq_disable();
	पूर्ण
पूर्ण

#अगर_घोषित ARCH_APICTIMER_STOPS_ON_C3

/*
 * Some BIOS implementations चयन to C3 in the published C2 state.
 * This seems to be a common problem on AMD boxen, but other venकरोrs
 * are affected too. We pick the most conservative approach: we assume
 * that the local APIC stops in both C2 and C3.
 */
अटल व्योम lapic_समयr_check_state(पूर्णांक state, काष्ठा acpi_processor *pr,
				   काष्ठा acpi_processor_cx *cx)
अणु
	काष्ठा acpi_processor_घातer *pwr = &pr->घातer;
	u8 type = local_apic_समयr_c2_ok ? ACPI_STATE_C3 : ACPI_STATE_C2;

	अगर (cpu_has(&cpu_data(pr->id), X86_FEATURE_ARAT))
		वापस;

	अगर (boot_cpu_has_bug(X86_BUG_AMD_APIC_C1E))
		type = ACPI_STATE_C1;

	/*
	 * Check, अगर one of the previous states alपढ़ोy marked the lapic
	 * unstable
	 */
	अगर (pwr->समयr_broadcast_on_state < state)
		वापस;

	अगर (cx->type >= type)
		pr->घातer.समयr_broadcast_on_state = state;
पूर्ण

अटल व्योम __lapic_समयr_propagate_broadcast(व्योम *arg)
अणु
	काष्ठा acpi_processor *pr = (काष्ठा acpi_processor *) arg;

	अगर (pr->घातer.समयr_broadcast_on_state < पूर्णांक_उच्च)
		tick_broadcast_enable();
	अन्यथा
		tick_broadcast_disable();
पूर्ण

अटल व्योम lapic_समयr_propagate_broadcast(काष्ठा acpi_processor *pr)
अणु
	smp_call_function_single(pr->id, __lapic_समयr_propagate_broadcast,
				 (व्योम *)pr, 1);
पूर्ण

/* Power(C) State समयr broadcast control */
अटल bool lapic_समयr_needs_broadcast(काष्ठा acpi_processor *pr,
					काष्ठा acpi_processor_cx *cx)
अणु
	वापस cx - pr->घातer.states >= pr->घातer.समयr_broadcast_on_state;
पूर्ण

#अन्यथा

अटल व्योम lapic_समयr_check_state(पूर्णांक state, काष्ठा acpi_processor *pr,
				   काष्ठा acpi_processor_cx *cstate) अणु पूर्ण
अटल व्योम lapic_समयr_propagate_broadcast(काष्ठा acpi_processor *pr) अणु पूर्ण

अटल bool lapic_समयr_needs_broadcast(काष्ठा acpi_processor *pr,
					काष्ठा acpi_processor_cx *cx)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर

#अगर defined(CONFIG_X86)
अटल व्योम tsc_check_state(पूर्णांक state)
अणु
	चयन (boot_cpu_data.x86_venकरोr) अणु
	हाल X86_VENDOR_HYGON:
	हाल X86_VENDOR_AMD:
	हाल X86_VENDOR_INTEL:
	हाल X86_VENDOR_CENTAUR:
	हाल X86_VENDOR_ZHAOXIN:
		/*
		 * AMD Fam10h TSC will tick in all
		 * C/P/S0/S1 states when this bit is set.
		 */
		अगर (boot_cpu_has(X86_FEATURE_NONSTOP_TSC))
			वापस;
		fallthrough;
	शेष:
		/* TSC could halt in idle, so notअगरy users */
		अगर (state > ACPI_STATE_C1)
			mark_tsc_unstable("TSC halts in idle");
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम tsc_check_state(पूर्णांक state) अणु वापस; पूर्ण
#पूर्ण_अगर

अटल पूर्णांक acpi_processor_get_घातer_info_fadt(काष्ठा acpi_processor *pr)
अणु

	अगर (!pr->pblk)
		वापस -ENODEV;

	/* अगर info is obtained from pblk/fadt, type equals state */
	pr->घातer.states[ACPI_STATE_C2].type = ACPI_STATE_C2;
	pr->घातer.states[ACPI_STATE_C3].type = ACPI_STATE_C3;

#अगर_अघोषित CONFIG_HOTPLUG_CPU
	/*
	 * Check क्रम P_LVL2_UP flag beक्रमe entering C2 and above on
	 * an SMP प्रणाली.
	 */
	अगर ((num_online_cpus() > 1) &&
	    !(acpi_gbl_FADT.flags & ACPI_FADT_C2_MP_SUPPORTED))
		वापस -ENODEV;
#पूर्ण_अगर

	/* determine C2 and C3 address from pblk */
	pr->घातer.states[ACPI_STATE_C2].address = pr->pblk + 4;
	pr->घातer.states[ACPI_STATE_C3].address = pr->pblk + 5;

	/* determine latencies from FADT */
	pr->घातer.states[ACPI_STATE_C2].latency = acpi_gbl_FADT.c2_latency;
	pr->घातer.states[ACPI_STATE_C3].latency = acpi_gbl_FADT.c3_latency;

	/*
	 * FADT specअगरied C2 latency must be less than or equal to
	 * 100 microseconds.
	 */
	अगर (acpi_gbl_FADT.c2_latency > ACPI_PROCESSOR_MAX_C2_LATENCY) अणु
		acpi_handle_debug(pr->handle, "C2 latency too large [%d]\n",
				  acpi_gbl_FADT.c2_latency);
		/* invalidate C2 */
		pr->घातer.states[ACPI_STATE_C2].address = 0;
	पूर्ण

	/*
	 * FADT supplied C3 latency must be less than or equal to
	 * 1000 microseconds.
	 */
	अगर (acpi_gbl_FADT.c3_latency > ACPI_PROCESSOR_MAX_C3_LATENCY) अणु
		acpi_handle_debug(pr->handle, "C3 latency too large [%d]\n",
				  acpi_gbl_FADT.c3_latency);
		/* invalidate C3 */
		pr->घातer.states[ACPI_STATE_C3].address = 0;
	पूर्ण

	acpi_handle_debug(pr->handle, "lvl2[0x%08x] lvl3[0x%08x]\n",
			  pr->घातer.states[ACPI_STATE_C2].address,
			  pr->घातer.states[ACPI_STATE_C3].address);

	snम_लिखो(pr->घातer.states[ACPI_STATE_C2].desc,
			 ACPI_CX_DESC_LEN, "ACPI P_LVL2 IOPORT 0x%x",
			 pr->घातer.states[ACPI_STATE_C2].address);
	snम_लिखो(pr->घातer.states[ACPI_STATE_C3].desc,
			 ACPI_CX_DESC_LEN, "ACPI P_LVL3 IOPORT 0x%x",
			 pr->घातer.states[ACPI_STATE_C3].address);

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_processor_get_घातer_info_शेष(काष्ठा acpi_processor *pr)
अणु
	अगर (!pr->घातer.states[ACPI_STATE_C1].valid) अणु
		/* set the first C-State to C1 */
		/* all processors need to support C1 */
		pr->घातer.states[ACPI_STATE_C1].type = ACPI_STATE_C1;
		pr->घातer.states[ACPI_STATE_C1].valid = 1;
		pr->घातer.states[ACPI_STATE_C1].entry_method = ACPI_CSTATE_HALT;

		snम_लिखो(pr->घातer.states[ACPI_STATE_C1].desc,
			 ACPI_CX_DESC_LEN, "ACPI HLT");
	पूर्ण
	/* the C0 state only exists as a filler in our array */
	pr->घातer.states[ACPI_STATE_C0].valid = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_processor_get_घातer_info_cst(काष्ठा acpi_processor *pr)
अणु
	पूर्णांक ret;

	अगर (nocst)
		वापस -ENODEV;

	ret = acpi_processor_evaluate_cst(pr->handle, pr->id, &pr->घातer);
	अगर (ret)
		वापस ret;

	अगर (!pr->घातer.count)
		वापस -EFAULT;

	pr->flags.has_cst = 1;
	वापस 0;
पूर्ण

अटल व्योम acpi_processor_घातer_verअगरy_c3(काष्ठा acpi_processor *pr,
					   काष्ठा acpi_processor_cx *cx)
अणु
	अटल पूर्णांक bm_check_flag = -1;
	अटल पूर्णांक bm_control_flag = -1;


	अगर (!cx->address)
		वापस;

	/*
	 * PIIX4 Erratum #18: We करोn't support C3 when Type-F (fast)
	 * DMA transfers are used by any ISA device to aव्योम livelock.
	 * Note that we could disable Type-F DMA (as recommended by
	 * the erratum), but this is known to disrupt certain ISA
	 * devices thus we take the conservative approach.
	 */
	अन्यथा अगर (errata.piix4.fdma) अणु
		acpi_handle_debug(pr->handle,
				  "C3 not supported on PIIX4 with Type-F DMA\n");
		वापस;
	पूर्ण

	/* All the logic here assumes flags.bm_check is same across all CPUs */
	अगर (bm_check_flag == -1) अणु
		/* Determine whether bm_check is needed based on CPU  */
		acpi_processor_घातer_init_bm_check(&(pr->flags), pr->id);
		bm_check_flag = pr->flags.bm_check;
		bm_control_flag = pr->flags.bm_control;
	पूर्ण अन्यथा अणु
		pr->flags.bm_check = bm_check_flag;
		pr->flags.bm_control = bm_control_flag;
	पूर्ण

	अगर (pr->flags.bm_check) अणु
		अगर (!pr->flags.bm_control) अणु
			अगर (pr->flags.has_cst != 1) अणु
				/* bus mastering control is necessary */
				acpi_handle_debug(pr->handle,
						  "C3 support requires BM control\n");
				वापस;
			पूर्ण अन्यथा अणु
				/* Here we enter C3 without bus mastering */
				acpi_handle_debug(pr->handle,
						  "C3 support without BM control\n");
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * WBINVD should be set in fadt, क्रम C3 state to be
		 * supported on when bm_check is not required.
		 */
		अगर (!(acpi_gbl_FADT.flags & ACPI_FADT_WBINVD)) अणु
			acpi_handle_debug(pr->handle,
					  "Cache invalidation should work properly"
					  " for C3 to be enabled on SMP systems\n");
			वापस;
		पूर्ण
	पूर्ण

	/*
	 * Otherwise we've met all of our C3 requirements.
	 * Normalize the C3 latency to expidite policy.  Enable
	 * checking of bus mastering status (bm_check) so we can
	 * use this in our C3 policy
	 */
	cx->valid = 1;

	/*
	 * On older chipsets, BM_RLD needs to be set
	 * in order क्रम Bus Master activity to wake the
	 * प्रणाली from C3.  Newer chipsets handle DMA
	 * during C3 स्वतःmatically and BM_RLD is a NOP.
	 * In either हाल, the proper way to
	 * handle BM_RLD is to set it and leave it set.
	 */
	acpi_ग_लिखो_bit_रेजिस्टर(ACPI_BITREG_BUS_MASTER_RLD, 1);

	वापस;
पूर्ण

अटल पूर्णांक acpi_processor_घातer_verअगरy(काष्ठा acpi_processor *pr)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक working = 0;

	pr->घातer.समयr_broadcast_on_state = पूर्णांक_उच्च;

	क्रम (i = 1; i < ACPI_PROCESSOR_MAX_POWER && i <= max_cstate; i++) अणु
		काष्ठा acpi_processor_cx *cx = &pr->घातer.states[i];

		चयन (cx->type) अणु
		हाल ACPI_STATE_C1:
			cx->valid = 1;
			अवरोध;

		हाल ACPI_STATE_C2:
			अगर (!cx->address)
				अवरोध;
			cx->valid = 1;
			अवरोध;

		हाल ACPI_STATE_C3:
			acpi_processor_घातer_verअगरy_c3(pr, cx);
			अवरोध;
		पूर्ण
		अगर (!cx->valid)
			जारी;

		lapic_समयr_check_state(i, pr, cx);
		tsc_check_state(cx->type);
		working++;
	पूर्ण

	lapic_समयr_propagate_broadcast(pr);

	वापस (working);
पूर्ण

अटल पूर्णांक acpi_processor_get_cstate_info(काष्ठा acpi_processor *pr)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक result;


	/* NOTE: the idle thपढ़ो may not be running जबतक calling
	 * this function */

	/* Zero initialize all the C-states info. */
	स_रखो(pr->घातer.states, 0, माप(pr->घातer.states));

	result = acpi_processor_get_घातer_info_cst(pr);
	अगर (result == -ENODEV)
		result = acpi_processor_get_घातer_info_fadt(pr);

	अगर (result)
		वापस result;

	acpi_processor_get_घातer_info_शेष(pr);

	pr->घातer.count = acpi_processor_घातer_verअगरy(pr);

	/*
	 * अगर one state of type C2 or C3 is available, mark this
	 * CPU as being "idle manageable"
	 */
	क्रम (i = 1; i < ACPI_PROCESSOR_MAX_POWER; i++) अणु
		अगर (pr->घातer.states[i].valid) अणु
			pr->घातer.count = i;
			pr->flags.घातer = 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * acpi_idle_bm_check - checks अगर bus master activity was detected
 */
अटल पूर्णांक acpi_idle_bm_check(व्योम)
अणु
	u32 bm_status = 0;

	अगर (bm_check_disable)
		वापस 0;

	acpi_पढ़ो_bit_रेजिस्टर(ACPI_BITREG_BUS_MASTER_STATUS, &bm_status);
	अगर (bm_status)
		acpi_ग_लिखो_bit_रेजिस्टर(ACPI_BITREG_BUS_MASTER_STATUS, 1);
	/*
	 * PIIX4 Erratum #18: Note that BM_STS करोesn't always reflect
	 * the true state of bus mastering activity; क्रमcing us to
	 * manually check the BMIDEA bit of each IDE channel.
	 */
	अन्यथा अगर (errata.piix4.bmisx) अणु
		अगर ((inb_p(errata.piix4.bmisx + 0x02) & 0x01)
		    || (inb_p(errata.piix4.bmisx + 0x0A) & 0x01))
			bm_status = 1;
	पूर्ण
	वापस bm_status;
पूर्ण

अटल व्योम रुको_क्रम_मुक्तze(व्योम)
अणु
#अगर_घोषित	CONFIG_X86
	/* No delay is needed अगर we are in guest */
	अगर (boot_cpu_has(X86_FEATURE_HYPERVISOR))
		वापस;
#पूर्ण_अगर
	/* Dummy रुको op - must करो something useless after P_LVL2 पढ़ो
	   because chipsets cannot guarantee that STPCLK# संकेत
	   माला_लो निश्चितed in समय to मुक्तze execution properly. */
	inl(acpi_gbl_FADT.xpm_समयr_block.address);
पूर्ण

/**
 * acpi_idle_करो_entry - enter idle state using the appropriate method
 * @cx: cstate data
 *
 * Caller disables पूर्णांकerrupt beक्रमe call and enables पूर्णांकerrupt after वापस.
 */
अटल व्योम __cpuidle acpi_idle_करो_entry(काष्ठा acpi_processor_cx *cx)
अणु
	अगर (cx->entry_method == ACPI_CSTATE_FFH) अणु
		/* Call पूर्णांकo architectural FFH based C-state */
		acpi_processor_ffh_cstate_enter(cx);
	पूर्ण अन्यथा अगर (cx->entry_method == ACPI_CSTATE_HALT) अणु
		acpi_safe_halt();
	पूर्ण अन्यथा अणु
		/* IO port based C-state */
		inb(cx->address);
		रुको_क्रम_मुक्तze();
	पूर्ण
पूर्ण

/**
 * acpi_idle_play_dead - enters an ACPI state क्रम दीर्घ-term idle (i.e. off-lining)
 * @dev: the target CPU
 * @index: the index of suggested state
 */
अटल पूर्णांक acpi_idle_play_dead(काष्ठा cpuidle_device *dev, पूर्णांक index)
अणु
	काष्ठा acpi_processor_cx *cx = per_cpu(acpi_cstate[index], dev->cpu);

	ACPI_FLUSH_CPU_CACHE();

	जबतक (1) अणु

		अगर (cx->entry_method == ACPI_CSTATE_HALT)
			safe_halt();
		अन्यथा अगर (cx->entry_method == ACPI_CSTATE_SYSTEMIO) अणु
			inb(cx->address);
			रुको_क्रम_मुक्तze();
		पूर्ण अन्यथा
			वापस -ENODEV;

#अगर defined(CONFIG_X86) && defined(CONFIG_HOTPLUG_CPU)
		cond_wakeup_cpu0();
#पूर्ण_अगर
	पूर्ण

	/* Never reached */
	वापस 0;
पूर्ण

अटल bool acpi_idle_fallback_to_c1(काष्ठा acpi_processor *pr)
अणु
	वापस IS_ENABLED(CONFIG_HOTPLUG_CPU) && !pr->flags.has_cst &&
		!(acpi_gbl_FADT.flags & ACPI_FADT_C2_MP_SUPPORTED);
पूर्ण

अटल पूर्णांक c3_cpu_count;
अटल DEFINE_RAW_SPINLOCK(c3_lock);

/**
 * acpi_idle_enter_bm - enters C3 with proper BM handling
 * @drv: cpuidle driver
 * @pr: Target processor
 * @cx: Target state context
 * @index: index of target state
 */
अटल पूर्णांक acpi_idle_enter_bm(काष्ठा cpuidle_driver *drv,
			       काष्ठा acpi_processor *pr,
			       काष्ठा acpi_processor_cx *cx,
			       पूर्णांक index)
अणु
	अटल काष्ठा acpi_processor_cx safe_cx = अणु
		.entry_method = ACPI_CSTATE_HALT,
	पूर्ण;

	/*
	 * disable bus master
	 * bm_check implies we need ARB_DIS
	 * bm_control implies whether we can करो ARB_DIS
	 *
	 * That leaves a हाल where bm_check is set and bm_control is not set.
	 * In that हाल we cannot करो much, we enter C3 without करोing anything.
	 */
	bool dis_bm = pr->flags.bm_control;

	/* If we can skip BM, demote to a safe state. */
	अगर (!cx->bm_sts_skip && acpi_idle_bm_check()) अणु
		dis_bm = false;
		index = drv->safe_state_index;
		अगर (index >= 0) अणु
			cx = this_cpu_पढ़ो(acpi_cstate[index]);
		पूर्ण अन्यथा अणु
			cx = &safe_cx;
			index = -EBUSY;
		पूर्ण
	पूर्ण

	अगर (dis_bm) अणु
		raw_spin_lock(&c3_lock);
		c3_cpu_count++;
		/* Disable bus master arbitration when all CPUs are in C3 */
		अगर (c3_cpu_count == num_online_cpus())
			acpi_ग_लिखो_bit_रेजिस्टर(ACPI_BITREG_ARB_DISABLE, 1);
		raw_spin_unlock(&c3_lock);
	पूर्ण

	rcu_idle_enter();

	acpi_idle_करो_entry(cx);

	rcu_idle_निकास();

	/* Re-enable bus master arbitration */
	अगर (dis_bm) अणु
		raw_spin_lock(&c3_lock);
		acpi_ग_लिखो_bit_रेजिस्टर(ACPI_BITREG_ARB_DISABLE, 0);
		c3_cpu_count--;
		raw_spin_unlock(&c3_lock);
	पूर्ण

	वापस index;
पूर्ण

अटल पूर्णांक acpi_idle_enter(काष्ठा cpuidle_device *dev,
			   काष्ठा cpuidle_driver *drv, पूर्णांक index)
अणु
	काष्ठा acpi_processor_cx *cx = per_cpu(acpi_cstate[index], dev->cpu);
	काष्ठा acpi_processor *pr;

	pr = __this_cpu_पढ़ो(processors);
	अगर (unlikely(!pr))
		वापस -EINVAL;

	अगर (cx->type != ACPI_STATE_C1) अणु
		अगर (cx->type == ACPI_STATE_C3 && pr->flags.bm_check)
			वापस acpi_idle_enter_bm(drv, pr, cx, index);

		/* C2 to C1 demotion. */
		अगर (acpi_idle_fallback_to_c1(pr) && num_online_cpus() > 1) अणु
			index = ACPI_IDLE_STATE_START;
			cx = per_cpu(acpi_cstate[index], dev->cpu);
		पूर्ण
	पूर्ण

	अगर (cx->type == ACPI_STATE_C3)
		ACPI_FLUSH_CPU_CACHE();

	acpi_idle_करो_entry(cx);

	वापस index;
पूर्ण

अटल पूर्णांक acpi_idle_enter_s2idle(काष्ठा cpuidle_device *dev,
				  काष्ठा cpuidle_driver *drv, पूर्णांक index)
अणु
	काष्ठा acpi_processor_cx *cx = per_cpu(acpi_cstate[index], dev->cpu);

	अगर (cx->type == ACPI_STATE_C3) अणु
		काष्ठा acpi_processor *pr = __this_cpu_पढ़ो(processors);

		अगर (unlikely(!pr))
			वापस 0;

		अगर (pr->flags.bm_check) अणु
			u8 bm_sts_skip = cx->bm_sts_skip;

			/* Don't check BM_STS, करो an unconditional ARB_DIS क्रम S2IDLE */
			cx->bm_sts_skip = 1;
			acpi_idle_enter_bm(drv, pr, cx, index);
			cx->bm_sts_skip = bm_sts_skip;

			वापस 0;
		पूर्ण अन्यथा अणु
			ACPI_FLUSH_CPU_CACHE();
		पूर्ण
	पूर्ण
	acpi_idle_करो_entry(cx);

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_processor_setup_cpuidle_cx(काष्ठा acpi_processor *pr,
					   काष्ठा cpuidle_device *dev)
अणु
	पूर्णांक i, count = ACPI_IDLE_STATE_START;
	काष्ठा acpi_processor_cx *cx;
	काष्ठा cpuidle_state *state;

	अगर (max_cstate == 0)
		max_cstate = 1;

	क्रम (i = 1; i < ACPI_PROCESSOR_MAX_POWER && i <= max_cstate; i++) अणु
		state = &acpi_idle_driver.states[count];
		cx = &pr->घातer.states[i];

		अगर (!cx->valid)
			जारी;

		per_cpu(acpi_cstate[count], dev->cpu) = cx;

		अगर (lapic_समयr_needs_broadcast(pr, cx))
			state->flags |= CPUIDLE_FLAG_TIMER_STOP;

		अगर (cx->type == ACPI_STATE_C3) अणु
			state->flags |= CPUIDLE_FLAG_TLB_FLUSHED;
			अगर (pr->flags.bm_check)
				state->flags |= CPUIDLE_FLAG_RCU_IDLE;
		पूर्ण

		count++;
		अगर (count == CPUIDLE_STATE_MAX)
			अवरोध;
	पूर्ण

	अगर (!count)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_processor_setup_cstates(काष्ठा acpi_processor *pr)
अणु
	पूर्णांक i, count;
	काष्ठा acpi_processor_cx *cx;
	काष्ठा cpuidle_state *state;
	काष्ठा cpuidle_driver *drv = &acpi_idle_driver;

	अगर (max_cstate == 0)
		max_cstate = 1;

	अगर (IS_ENABLED(CONFIG_ARCH_HAS_CPU_RELAX)) अणु
		cpuidle_poll_state_init(drv);
		count = 1;
	पूर्ण अन्यथा अणु
		count = 0;
	पूर्ण

	क्रम (i = 1; i < ACPI_PROCESSOR_MAX_POWER && i <= max_cstate; i++) अणु
		cx = &pr->घातer.states[i];

		अगर (!cx->valid)
			जारी;

		state = &drv->states[count];
		snम_लिखो(state->name, CPUIDLE_NAME_LEN, "C%d", i);
		strlcpy(state->desc, cx->desc, CPUIDLE_DESC_LEN);
		state->निकास_latency = cx->latency;
		state->target_residency = cx->latency * latency_factor;
		state->enter = acpi_idle_enter;

		state->flags = 0;
		अगर (cx->type == ACPI_STATE_C1 || cx->type == ACPI_STATE_C2) अणु
			state->enter_dead = acpi_idle_play_dead;
			drv->safe_state_index = count;
		पूर्ण
		/*
		 * Halt-induced C1 is not good क्रम ->enter_s2idle, because it
		 * re-enables पूर्णांकerrupts on निकास.  Moreover, C1 is generally not
		 * particularly पूर्णांकeresting from the suspend-to-idle angle, so
		 * aव्योम C1 and the situations in which we may need to fall back
		 * to it altogether.
		 */
		अगर (cx->type != ACPI_STATE_C1 && !acpi_idle_fallback_to_c1(pr))
			state->enter_s2idle = acpi_idle_enter_s2idle;

		count++;
		अगर (count == CPUIDLE_STATE_MAX)
			अवरोध;
	पूर्ण

	drv->state_count = count;

	अगर (!count)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम acpi_processor_cstate_first_run_checks(व्योम)
अणु
	अटल पूर्णांक first_run;

	अगर (first_run)
		वापस;
	dmi_check_प्रणाली(processor_घातer_dmi_table);
	max_cstate = acpi_processor_cstate_check(max_cstate);
	अगर (max_cstate < ACPI_C_STATES_MAX)
		pr_notice("processor limited to max C-state %d\n", max_cstate);

	first_run++;

	अगर (nocst)
		वापस;

	acpi_processor_claim_cst_control();
पूर्ण
#अन्यथा

अटल अंतरभूत पूर्णांक disabled_by_idle_boot_param(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम acpi_processor_cstate_first_run_checks(व्योम) अणु पूर्ण
अटल पूर्णांक acpi_processor_get_cstate_info(काष्ठा acpi_processor *pr)
अणु
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक acpi_processor_setup_cpuidle_cx(काष्ठा acpi_processor *pr,
					   काष्ठा cpuidle_device *dev)
अणु
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक acpi_processor_setup_cstates(काष्ठा acpi_processor *pr)
अणु
	वापस -EINVAL;
पूर्ण

#पूर्ण_अगर /* CONFIG_ACPI_PROCESSOR_CSTATE */

काष्ठा acpi_lpi_states_array अणु
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक composite_states_size;
	काष्ठा acpi_lpi_state *entries;
	काष्ठा acpi_lpi_state *composite_states[ACPI_PROCESSOR_MAX_POWER];
पूर्ण;

अटल पूर्णांक obj_get_पूर्णांकeger(जोड़ acpi_object *obj, u32 *value)
अणु
	अगर (obj->type != ACPI_TYPE_INTEGER)
		वापस -EINVAL;

	*value = obj->पूर्णांकeger.value;
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_processor_evaluate_lpi(acpi_handle handle,
				       काष्ठा acpi_lpi_states_array *info)
अणु
	acpi_status status;
	पूर्णांक ret = 0;
	पूर्णांक pkg_count, state_idx = 1, loop;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *lpi_data;
	काष्ठा acpi_lpi_state *lpi_state;

	status = acpi_evaluate_object(handle, "_LPI", शून्य, &buffer);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_handle_debug(handle, "No _LPI, giving up\n");
		वापस -ENODEV;
	पूर्ण

	lpi_data = buffer.poपूर्णांकer;

	/* There must be at least 4 elements = 3 elements + 1 package */
	अगर (!lpi_data || lpi_data->type != ACPI_TYPE_PACKAGE ||
	    lpi_data->package.count < 4) अणु
		pr_debug("not enough elements in _LPI\n");
		ret = -ENODATA;
		जाओ end;
	पूर्ण

	pkg_count = lpi_data->package.elements[2].पूर्णांकeger.value;

	/* Validate number of घातer states. */
	अगर (pkg_count < 1 || pkg_count != lpi_data->package.count - 3) अणु
		pr_debug("count given by _LPI is not valid\n");
		ret = -ENODATA;
		जाओ end;
	पूर्ण

	lpi_state = kसुस्मृति(pkg_count, माप(*lpi_state), GFP_KERNEL);
	अगर (!lpi_state) अणु
		ret = -ENOMEM;
		जाओ end;
	पूर्ण

	info->size = pkg_count;
	info->entries = lpi_state;

	/* LPI States start at index 3 */
	क्रम (loop = 3; state_idx <= pkg_count; loop++, state_idx++, lpi_state++) अणु
		जोड़ acpi_object *element, *pkg_elem, *obj;

		element = &lpi_data->package.elements[loop];
		अगर (element->type != ACPI_TYPE_PACKAGE || element->package.count < 7)
			जारी;

		pkg_elem = element->package.elements;

		obj = pkg_elem + 6;
		अगर (obj->type == ACPI_TYPE_BUFFER) अणु
			काष्ठा acpi_घातer_रेजिस्टर *reg;

			reg = (काष्ठा acpi_घातer_रेजिस्टर *)obj->buffer.poपूर्णांकer;
			अगर (reg->space_id != ACPI_ADR_SPACE_SYSTEM_IO &&
			    reg->space_id != ACPI_ADR_SPACE_FIXED_HARDWARE)
				जारी;

			lpi_state->address = reg->address;
			lpi_state->entry_method =
				reg->space_id == ACPI_ADR_SPACE_FIXED_HARDWARE ?
				ACPI_CSTATE_FFH : ACPI_CSTATE_SYSTEMIO;
		पूर्ण अन्यथा अगर (obj->type == ACPI_TYPE_INTEGER) अणु
			lpi_state->entry_method = ACPI_CSTATE_INTEGER;
			lpi_state->address = obj->पूर्णांकeger.value;
		पूर्ण अन्यथा अणु
			जारी;
		पूर्ण

		/* elements[7,8] skipped क्रम now i.e. Residency/Usage counter*/

		obj = pkg_elem + 9;
		अगर (obj->type == ACPI_TYPE_STRING)
			strlcpy(lpi_state->desc, obj->string.poपूर्णांकer,
				ACPI_CX_DESC_LEN);

		lpi_state->index = state_idx;
		अगर (obj_get_पूर्णांकeger(pkg_elem + 0, &lpi_state->min_residency)) अणु
			pr_debug("No min. residency found, assuming 10 us\n");
			lpi_state->min_residency = 10;
		पूर्ण

		अगर (obj_get_पूर्णांकeger(pkg_elem + 1, &lpi_state->wake_latency)) अणु
			pr_debug("No wakeup residency found, assuming 10 us\n");
			lpi_state->wake_latency = 10;
		पूर्ण

		अगर (obj_get_पूर्णांकeger(pkg_elem + 2, &lpi_state->flags))
			lpi_state->flags = 0;

		अगर (obj_get_पूर्णांकeger(pkg_elem + 3, &lpi_state->arch_flags))
			lpi_state->arch_flags = 0;

		अगर (obj_get_पूर्णांकeger(pkg_elem + 4, &lpi_state->res_cnt_freq))
			lpi_state->res_cnt_freq = 1;

		अगर (obj_get_पूर्णांकeger(pkg_elem + 5, &lpi_state->enable_parent_state))
			lpi_state->enable_parent_state = 0;
	पूर्ण

	acpi_handle_debug(handle, "Found %d power states\n", state_idx);
end:
	kमुक्त(buffer.poपूर्णांकer);
	वापस ret;
पूर्ण

/*
 * flat_state_cnt - the number of composite LPI states after the process of flattening
 */
अटल पूर्णांक flat_state_cnt;

/**
 * combine_lpi_states - combine local and parent LPI states to क्रमm a composite LPI state
 *
 * @local: local LPI state
 * @parent: parent LPI state
 * @result: composite LPI state
 */
अटल bool combine_lpi_states(काष्ठा acpi_lpi_state *local,
			       काष्ठा acpi_lpi_state *parent,
			       काष्ठा acpi_lpi_state *result)
अणु
	अगर (parent->entry_method == ACPI_CSTATE_INTEGER) अणु
		अगर (!parent->address) /* 0 means स्वतःpromotable */
			वापस false;
		result->address = local->address + parent->address;
	पूर्ण अन्यथा अणु
		result->address = parent->address;
	पूर्ण

	result->min_residency = max(local->min_residency, parent->min_residency);
	result->wake_latency = local->wake_latency + parent->wake_latency;
	result->enable_parent_state = parent->enable_parent_state;
	result->entry_method = local->entry_method;

	result->flags = parent->flags;
	result->arch_flags = parent->arch_flags;
	result->index = parent->index;

	strlcpy(result->desc, local->desc, ACPI_CX_DESC_LEN);
	strlcat(result->desc, "+", ACPI_CX_DESC_LEN);
	strlcat(result->desc, parent->desc, ACPI_CX_DESC_LEN);
	वापस true;
पूर्ण

#घोषणा ACPI_LPI_STATE_FLAGS_ENABLED			BIT(0)

अटल व्योम stash_composite_state(काष्ठा acpi_lpi_states_array *curr_level,
				  काष्ठा acpi_lpi_state *t)
अणु
	curr_level->composite_states[curr_level->composite_states_size++] = t;
पूर्ण

अटल पूर्णांक flatten_lpi_states(काष्ठा acpi_processor *pr,
			      काष्ठा acpi_lpi_states_array *curr_level,
			      काष्ठा acpi_lpi_states_array *prev_level)
अणु
	पूर्णांक i, j, state_count = curr_level->size;
	काष्ठा acpi_lpi_state *p, *t = curr_level->entries;

	curr_level->composite_states_size = 0;
	क्रम (j = 0; j < state_count; j++, t++) अणु
		काष्ठा acpi_lpi_state *flpi;

		अगर (!(t->flags & ACPI_LPI_STATE_FLAGS_ENABLED))
			जारी;

		अगर (flat_state_cnt >= ACPI_PROCESSOR_MAX_POWER) अणु
			pr_warn("Limiting number of LPI states to max (%d)\n",
				ACPI_PROCESSOR_MAX_POWER);
			pr_warn("Please increase ACPI_PROCESSOR_MAX_POWER if needed.\n");
			अवरोध;
		पूर्ण

		flpi = &pr->घातer.lpi_states[flat_state_cnt];

		अगर (!prev_level) अणु /* leaf/processor node */
			स_नकल(flpi, t, माप(*t));
			stash_composite_state(curr_level, flpi);
			flat_state_cnt++;
			जारी;
		पूर्ण

		क्रम (i = 0; i < prev_level->composite_states_size; i++) अणु
			p = prev_level->composite_states[i];
			अगर (t->index <= p->enable_parent_state &&
			    combine_lpi_states(p, t, flpi)) अणु
				stash_composite_state(curr_level, flpi);
				flat_state_cnt++;
				flpi++;
			पूर्ण
		पूर्ण
	पूर्ण

	kमुक्त(curr_level->entries);
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_processor_get_lpi_info(काष्ठा acpi_processor *pr)
अणु
	पूर्णांक ret, i;
	acpi_status status;
	acpi_handle handle = pr->handle, pr_ahandle;
	काष्ठा acpi_device *d = शून्य;
	काष्ठा acpi_lpi_states_array info[2], *पंचांगp, *prev, *curr;

	अगर (!osc_pc_lpi_support_confirmed)
		वापस -EOPNOTSUPP;

	अगर (!acpi_has_method(handle, "_LPI"))
		वापस -EINVAL;

	flat_state_cnt = 0;
	prev = &info[0];
	curr = &info[1];
	handle = pr->handle;
	ret = acpi_processor_evaluate_lpi(handle, prev);
	अगर (ret)
		वापस ret;
	flatten_lpi_states(pr, prev, शून्य);

	status = acpi_get_parent(handle, &pr_ahandle);
	जबतक (ACPI_SUCCESS(status)) अणु
		acpi_bus_get_device(pr_ahandle, &d);
		handle = pr_ahandle;

		अगर (म_भेद(acpi_device_hid(d), ACPI_PROCESSOR_CONTAINER_HID))
			अवरोध;

		/* can be optional ? */
		अगर (!acpi_has_method(handle, "_LPI"))
			अवरोध;

		ret = acpi_processor_evaluate_lpi(handle, curr);
		अगर (ret)
			अवरोध;

		/* flatten all the LPI states in this level of hierarchy */
		flatten_lpi_states(pr, curr, prev);

		पंचांगp = prev, prev = curr, curr = पंचांगp;

		status = acpi_get_parent(handle, &pr_ahandle);
	पूर्ण

	pr->घातer.count = flat_state_cnt;
	/* reset the index after flattening */
	क्रम (i = 0; i < pr->घातer.count; i++)
		pr->घातer.lpi_states[i].index = i;

	/* Tell driver that _LPI is supported. */
	pr->flags.has_lpi = 1;
	pr->flags.घातer = 1;

	वापस 0;
पूर्ण

पूर्णांक __weak acpi_processor_ffh_lpi_probe(अचिन्हित पूर्णांक cpu)
अणु
	वापस -ENODEV;
पूर्ण

पूर्णांक __weak acpi_processor_ffh_lpi_enter(काष्ठा acpi_lpi_state *lpi)
अणु
	वापस -ENODEV;
पूर्ण

/**
 * acpi_idle_lpi_enter - enters an ACPI any LPI state
 * @dev: the target CPU
 * @drv: cpuidle driver containing cpuidle state info
 * @index: index of target state
 *
 * Return: 0 क्रम success or negative value क्रम error
 */
अटल पूर्णांक acpi_idle_lpi_enter(काष्ठा cpuidle_device *dev,
			       काष्ठा cpuidle_driver *drv, पूर्णांक index)
अणु
	काष्ठा acpi_processor *pr;
	काष्ठा acpi_lpi_state *lpi;

	pr = __this_cpu_पढ़ो(processors);

	अगर (unlikely(!pr))
		वापस -EINVAL;

	lpi = &pr->घातer.lpi_states[index];
	अगर (lpi->entry_method == ACPI_CSTATE_FFH)
		वापस acpi_processor_ffh_lpi_enter(lpi);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक acpi_processor_setup_lpi_states(काष्ठा acpi_processor *pr)
अणु
	पूर्णांक i;
	काष्ठा acpi_lpi_state *lpi;
	काष्ठा cpuidle_state *state;
	काष्ठा cpuidle_driver *drv = &acpi_idle_driver;

	अगर (!pr->flags.has_lpi)
		वापस -EOPNOTSUPP;

	क्रम (i = 0; i < pr->घातer.count && i < CPUIDLE_STATE_MAX; i++) अणु
		lpi = &pr->घातer.lpi_states[i];

		state = &drv->states[i];
		snम_लिखो(state->name, CPUIDLE_NAME_LEN, "LPI-%d", i);
		strlcpy(state->desc, lpi->desc, CPUIDLE_DESC_LEN);
		state->निकास_latency = lpi->wake_latency;
		state->target_residency = lpi->min_residency;
		अगर (lpi->arch_flags)
			state->flags |= CPUIDLE_FLAG_TIMER_STOP;
		state->enter = acpi_idle_lpi_enter;
		drv->safe_state_index = i;
	पूर्ण

	drv->state_count = i;

	वापस 0;
पूर्ण

/**
 * acpi_processor_setup_cpuidle_states- prepares and configures cpuidle
 * global state data i.e. idle routines
 *
 * @pr: the ACPI processor
 */
अटल पूर्णांक acpi_processor_setup_cpuidle_states(काष्ठा acpi_processor *pr)
अणु
	पूर्णांक i;
	काष्ठा cpuidle_driver *drv = &acpi_idle_driver;

	अगर (!pr->flags.घातer_setup_करोne || !pr->flags.घातer)
		वापस -EINVAL;

	drv->safe_state_index = -1;
	क्रम (i = ACPI_IDLE_STATE_START; i < CPUIDLE_STATE_MAX; i++) अणु
		drv->states[i].name[0] = '\0';
		drv->states[i].desc[0] = '\0';
	पूर्ण

	अगर (pr->flags.has_lpi)
		वापस acpi_processor_setup_lpi_states(pr);

	वापस acpi_processor_setup_cstates(pr);
पूर्ण

/**
 * acpi_processor_setup_cpuidle_dev - prepares and configures CPUIDLE
 * device i.e. per-cpu data
 *
 * @pr: the ACPI processor
 * @dev : the cpuidle device
 */
अटल पूर्णांक acpi_processor_setup_cpuidle_dev(काष्ठा acpi_processor *pr,
					    काष्ठा cpuidle_device *dev)
अणु
	अगर (!pr->flags.घातer_setup_करोne || !pr->flags.घातer || !dev)
		वापस -EINVAL;

	dev->cpu = pr->id;
	अगर (pr->flags.has_lpi)
		वापस acpi_processor_ffh_lpi_probe(pr->id);

	वापस acpi_processor_setup_cpuidle_cx(pr, dev);
पूर्ण

अटल पूर्णांक acpi_processor_get_घातer_info(काष्ठा acpi_processor *pr)
अणु
	पूर्णांक ret;

	ret = acpi_processor_get_lpi_info(pr);
	अगर (ret)
		ret = acpi_processor_get_cstate_info(pr);

	वापस ret;
पूर्ण

पूर्णांक acpi_processor_hotplug(काष्ठा acpi_processor *pr)
अणु
	पूर्णांक ret = 0;
	काष्ठा cpuidle_device *dev;

	अगर (disabled_by_idle_boot_param())
		वापस 0;

	अगर (!pr->flags.घातer_setup_करोne)
		वापस -ENODEV;

	dev = per_cpu(acpi_cpuidle_device, pr->id);
	cpuidle_छोड़ो_and_lock();
	cpuidle_disable_device(dev);
	ret = acpi_processor_get_घातer_info(pr);
	अगर (!ret && pr->flags.घातer) अणु
		acpi_processor_setup_cpuidle_dev(pr, dev);
		ret = cpuidle_enable_device(dev);
	पूर्ण
	cpuidle_resume_and_unlock();

	वापस ret;
पूर्ण

पूर्णांक acpi_processor_घातer_state_has_changed(काष्ठा acpi_processor *pr)
अणु
	पूर्णांक cpu;
	काष्ठा acpi_processor *_pr;
	काष्ठा cpuidle_device *dev;

	अगर (disabled_by_idle_boot_param())
		वापस 0;

	अगर (!pr->flags.घातer_setup_करोne)
		वापस -ENODEV;

	/*
	 * FIXME:  Design the ACPI notअगरication to make it once per
	 * प्रणाली instead of once per-cpu.  This condition is a hack
	 * to make the code that updates C-States be called once.
	 */

	अगर (pr->id == 0 && cpuidle_get_driver() == &acpi_idle_driver) अणु

		/* Protect against cpu-hotplug */
		get_online_cpus();
		cpuidle_छोड़ो_and_lock();

		/* Disable all cpuidle devices */
		क्रम_each_online_cpu(cpu) अणु
			_pr = per_cpu(processors, cpu);
			अगर (!_pr || !_pr->flags.घातer_setup_करोne)
				जारी;
			dev = per_cpu(acpi_cpuidle_device, cpu);
			cpuidle_disable_device(dev);
		पूर्ण

		/* Populate Updated C-state inक्रमmation */
		acpi_processor_get_घातer_info(pr);
		acpi_processor_setup_cpuidle_states(pr);

		/* Enable all cpuidle devices */
		क्रम_each_online_cpu(cpu) अणु
			_pr = per_cpu(processors, cpu);
			अगर (!_pr || !_pr->flags.घातer_setup_करोne)
				जारी;
			acpi_processor_get_घातer_info(_pr);
			अगर (_pr->flags.घातer) अणु
				dev = per_cpu(acpi_cpuidle_device, cpu);
				acpi_processor_setup_cpuidle_dev(_pr, dev);
				cpuidle_enable_device(dev);
			पूर्ण
		पूर्ण
		cpuidle_resume_and_unlock();
		put_online_cpus();
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_processor_रेजिस्टरed;

पूर्णांक acpi_processor_घातer_init(काष्ठा acpi_processor *pr)
अणु
	पूर्णांक retval;
	काष्ठा cpuidle_device *dev;

	अगर (disabled_by_idle_boot_param())
		वापस 0;

	acpi_processor_cstate_first_run_checks();

	अगर (!acpi_processor_get_घातer_info(pr))
		pr->flags.घातer_setup_करोne = 1;

	/*
	 * Install the idle handler अगर processor घातer management is supported.
	 * Note that we use previously set idle handler will be used on
	 * platक्रमms that only support C1.
	 */
	अगर (pr->flags.घातer) अणु
		/* Register acpi_idle_driver अगर not alपढ़ोy रेजिस्टरed */
		अगर (!acpi_processor_रेजिस्टरed) अणु
			acpi_processor_setup_cpuidle_states(pr);
			retval = cpuidle_रेजिस्टर_driver(&acpi_idle_driver);
			अगर (retval)
				वापस retval;
			pr_debug("%s registered with cpuidle\n",
				 acpi_idle_driver.name);
		पूर्ण

		dev = kzalloc(माप(*dev), GFP_KERNEL);
		अगर (!dev)
			वापस -ENOMEM;
		per_cpu(acpi_cpuidle_device, pr->id) = dev;

		acpi_processor_setup_cpuidle_dev(pr, dev);

		/* Register per-cpu cpuidle_device. Cpuidle driver
		 * must alपढ़ोy be रेजिस्टरed beक्रमe रेजिस्टरing device
		 */
		retval = cpuidle_रेजिस्टर_device(dev);
		अगर (retval) अणु
			अगर (acpi_processor_रेजिस्टरed == 0)
				cpuidle_unरेजिस्टर_driver(&acpi_idle_driver);
			वापस retval;
		पूर्ण
		acpi_processor_रेजिस्टरed++;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक acpi_processor_घातer_निकास(काष्ठा acpi_processor *pr)
अणु
	काष्ठा cpuidle_device *dev = per_cpu(acpi_cpuidle_device, pr->id);

	अगर (disabled_by_idle_boot_param())
		वापस 0;

	अगर (pr->flags.घातer) अणु
		cpuidle_unरेजिस्टर_device(dev);
		acpi_processor_रेजिस्टरed--;
		अगर (acpi_processor_रेजिस्टरed == 0)
			cpuidle_unरेजिस्टर_driver(&acpi_idle_driver);
	पूर्ण

	pr->flags.घातer_setup_करोne = 0;
	वापस 0;
पूर्ण
