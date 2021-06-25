<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sleep.c - x86-specअगरic ACPI sleep support.
 *
 *  Copyright (C) 2001-2003 Patrick Mochel
 *  Copyright (C) 2001-2003 Pavel Machek <pavel@ucw.cz>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/memblock.h>
#समावेश <linux/dmi.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/segment.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/realmode.h>

#समावेश <linux/ftrace.h>
#समावेश "../../realmode/rm/wakeup.h"
#समावेश "sleep.h"

अचिन्हित दीर्घ acpi_realmode_flags;

#अगर defined(CONFIG_SMP) && defined(CONFIG_64BIT)
अटल अक्षर temp_stack[4096];
#पूर्ण_अगर

/**
 * acpi_get_wakeup_address - provide physical address क्रम S3 wakeup
 *
 * Returns the physical address where the kernel should be resumed after the
 * प्रणाली awakes from S3, e.g. क्रम programming पूर्णांकo the firmware waking vector.
 */
अचिन्हित दीर्घ acpi_get_wakeup_address(व्योम)
अणु
	वापस ((अचिन्हित दीर्घ)(real_mode_header->wakeup_start));
पूर्ण

/**
 * x86_acpi_enter_sleep_state - enter sleep state
 * @state: Sleep state to enter.
 *
 * Wrapper around acpi_enter_sleep_state() to be called by assembly.
 */
यंत्रlinkage acpi_status __visible x86_acpi_enter_sleep_state(u8 state)
अणु
	वापस acpi_enter_sleep_state(state);
पूर्ण

/**
 * x86_acpi_suspend_lowlevel - save kernel state
 *
 * Create an identity mapped page table and copy the wakeup routine to
 * low memory.
 */
पूर्णांक x86_acpi_suspend_lowlevel(व्योम)
अणु
	काष्ठा wakeup_header *header =
		(काष्ठा wakeup_header *) __va(real_mode_header->wakeup_header);

	अगर (header->signature != WAKEUP_HEADER_SIGNATURE) अणु
		prपूर्णांकk(KERN_ERR "wakeup header does not match\n");
		वापस -EINVAL;
	पूर्ण

	header->video_mode = saved_video_mode;

	header->pmode_behavior = 0;

#अगर_अघोषित CONFIG_64BIT
	native_store_gdt((काष्ठा desc_ptr *)&header->pmode_gdt);

	/*
	 * We have to check that we can ग_लिखो back the value, and not
	 * just पढ़ो it.  At least on 90 nm Pentium M (Family 6, Model
	 * 13), पढ़ोing an invalid MSR is not guaranteed to trap, see
	 * Erratum X4 in "Intel Pentium M Processor on 90 nm Process
	 * with 2-MB L2 Cache and Intelतऍ Processor A100 and A110 on 90
	 * nm process with 512-KB L2 Cache Specअगरication Update".
	 */
	अगर (!rdmsr_safe(MSR_EFER,
			&header->pmode_efer_low,
			&header->pmode_efer_high) &&
	    !wrmsr_safe(MSR_EFER,
			header->pmode_efer_low,
			header->pmode_efer_high))
		header->pmode_behavior |= (1 << WAKEUP_BEHAVIOR_RESTORE_EFER);
#पूर्ण_अगर /* !CONFIG_64BIT */

	header->pmode_cr0 = पढ़ो_cr0();
	अगर (__this_cpu_पढ़ो(cpu_info.cpuid_level) >= 0) अणु
		header->pmode_cr4 = __पढ़ो_cr4();
		header->pmode_behavior |= (1 << WAKEUP_BEHAVIOR_RESTORE_CR4);
	पूर्ण
	अगर (!rdmsr_safe(MSR_IA32_MISC_ENABLE,
			&header->pmode_misc_en_low,
			&header->pmode_misc_en_high) &&
	    !wrmsr_safe(MSR_IA32_MISC_ENABLE,
			header->pmode_misc_en_low,
			header->pmode_misc_en_high))
		header->pmode_behavior |=
			(1 << WAKEUP_BEHAVIOR_RESTORE_MISC_ENABLE);
	header->realmode_flags = acpi_realmode_flags;
	header->real_magic = 0x12345678;

#अगर_अघोषित CONFIG_64BIT
	header->pmode_entry = (u32)&wakeup_pmode_वापस;
	header->pmode_cr3 = (u32)__pa_symbol(initial_page_table);
	saved_magic = 0x12345678;
#अन्यथा /* CONFIG_64BIT */
#अगर_घोषित CONFIG_SMP
	initial_stack = (अचिन्हित दीर्घ)temp_stack + माप(temp_stack);
	early_gdt_descr.address =
			(अचिन्हित दीर्घ)get_cpu_gdt_rw(smp_processor_id());
	initial_gs = per_cpu_offset(smp_processor_id());
#पूर्ण_अगर
	initial_code = (अचिन्हित दीर्घ)wakeup_दीर्घ64;
       saved_magic = 0x123456789abcdef0L;
#पूर्ण_अगर /* CONFIG_64BIT */

	/*
	 * Pause/unछोड़ो graph tracing around करो_suspend_lowlevel as it has
	 * inconsistent call/वापस info after it jumps to the wakeup vector.
	 */
	छोड़ो_graph_tracing();
	करो_suspend_lowlevel();
	unछोड़ो_graph_tracing();
	वापस 0;
पूर्ण

अटल पूर्णांक __init acpi_sleep_setup(अक्षर *str)
अणु
	जबतक ((str != शून्य) && (*str != '\0')) अणु
		अगर (म_भेदन(str, "s3_bios", 7) == 0)
			acpi_realmode_flags |= 1;
		अगर (म_भेदन(str, "s3_mode", 7) == 0)
			acpi_realmode_flags |= 2;
		अगर (म_भेदन(str, "s3_beep", 7) == 0)
			acpi_realmode_flags |= 4;
#अगर_घोषित CONFIG_HIBERNATION
		अगर (म_भेदन(str, "s4_nohwsig", 10) == 0)
			acpi_no_s4_hw_signature();
#पूर्ण_अगर
		अगर (म_भेदन(str, "nonvs", 5) == 0)
			acpi_nvs_nosave();
		अगर (म_भेदन(str, "nonvs_s3", 8) == 0)
			acpi_nvs_nosave_s3();
		अगर (म_भेदन(str, "old_ordering", 12) == 0)
			acpi_old_suspend_ordering();
		अगर (म_भेदन(str, "nobl", 4) == 0)
			acpi_sleep_no_blacklist();
		str = म_अक्षर(str, ',');
		अगर (str != शून्य)
			str += म_अखोज(str, ", \t");
	पूर्ण
	वापस 1;
पूर्ण

__setup("acpi_sleep=", acpi_sleep_setup);
