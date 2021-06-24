<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Copyright IBM Corp. 2007, 2009
 *    Author(s): Hongjie Yang <hongjie@us.ibm.com>,
 *		 Heiko Carstens <heiko.carstens@de.ibm.com>
 */

#घोषणा KMSG_COMPONENT "setup"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/compiler.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/lockdep.h>
#समावेश <linux/extable.h>
#समावेश <linux/pfn.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/diag.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/ipl.h>
#समावेश <यंत्र/lowcore.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/sysinfo.h>
#समावेश <यंत्र/cpcmd.h>
#समावेश <यंत्र/sclp.h>
#समावेश <यंत्र/facility.h>
#समावेश <यंत्र/boot_data.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश "entry.h"

अटल व्योम __init reset_tod_घड़ी(व्योम)
अणु
	जोड़ tod_घड़ी clk;

	अगर (store_tod_घड़ी_ext_cc(&clk) == 0)
		वापस;
	/* TOD घड़ी not running. Set the घड़ी to Unix Epoch. */
	अगर (set_tod_घड़ी(TOD_UNIX_EPOCH) || store_tod_घड़ी_ext_cc(&clk))
		disabled_रुको();

	स_रखो(&tod_घड़ी_base, 0, माप(tod_घड़ी_base));
	tod_घड़ी_base.tod = TOD_UNIX_EPOCH;
	S390_lowcore.last_update_घड़ी = TOD_UNIX_EPOCH;
पूर्ण

/*
 * Initialize storage key क्रम kernel pages
 */
अटल noअंतरभूत __init व्योम init_kernel_storage_key(व्योम)
अणु
#अगर PAGE_DEFAULT_KEY
	अचिन्हित दीर्घ end_pfn, init_pfn;

	end_pfn = PFN_UP(__pa(_end));

	क्रम (init_pfn = 0 ; init_pfn < end_pfn; init_pfn++)
		page_set_storage_key(init_pfn << PAGE_SHIFT,
				     PAGE_DEFAULT_KEY, 0);
#पूर्ण_अगर
पूर्ण

अटल __initdata अक्षर sysinfo_page[PAGE_SIZE] __aligned(PAGE_SIZE);

अटल noअंतरभूत __init व्योम detect_machine_type(व्योम)
अणु
	काष्ठा sysinfo_3_2_2 *vmms = (काष्ठा sysinfo_3_2_2 *)&sysinfo_page;

	/* Check current-configuration-level */
	अगर (stsi(शून्य, 0, 0, 0) <= 2) अणु
		S390_lowcore.machine_flags |= MACHINE_FLAG_LPAR;
		वापस;
	पूर्ण
	/* Get भव-machine cpu inक्रमmation. */
	अगर (stsi(vmms, 3, 2, 2) || !vmms->count)
		वापस;

	/* Detect known hypervisors */
	अगर (!स_भेद(vmms->vm[0].cpi, "\xd2\xe5\xd4", 3))
		S390_lowcore.machine_flags |= MACHINE_FLAG_KVM;
	अन्यथा अगर (!स_भेद(vmms->vm[0].cpi, "\xa9\x61\xe5\xd4", 4))
		S390_lowcore.machine_flags |= MACHINE_FLAG_VM;
पूर्ण

/* Remove leading, trailing and द्विगुन whitespace. */
अटल अंतरभूत व्योम strim_all(अक्षर *str)
अणु
	अक्षर *s;

	s = strim(str);
	अगर (s != str)
		स_हटाओ(str, s, म_माप(s));
	जबतक (*str) अणु
		अगर (!है_खाली(*str++))
			जारी;
		अगर (है_खाली(*str)) अणु
			s = skip_spaces(str);
			स_हटाओ(str, s, म_माप(s) + 1);
		पूर्ण
	पूर्ण
पूर्ण

अटल noअंतरभूत __init व्योम setup_arch_string(व्योम)
अणु
	काष्ठा sysinfo_1_1_1 *mach = (काष्ठा sysinfo_1_1_1 *)&sysinfo_page;
	काष्ठा sysinfo_3_2_2 *vm = (काष्ठा sysinfo_3_2_2 *)&sysinfo_page;
	अक्षर mstr[80], hvstr[17];

	अगर (stsi(mach, 1, 1, 1))
		वापस;
	EBCASC(mach->manufacturer, माप(mach->manufacturer));
	EBCASC(mach->type, माप(mach->type));
	EBCASC(mach->model, माप(mach->model));
	EBCASC(mach->model_capacity, माप(mach->model_capacity));
	प्र_लिखो(mstr, "%-16.16s %-4.4s %-16.16s %-16.16s",
		mach->manufacturer, mach->type,
		mach->model, mach->model_capacity);
	strim_all(mstr);
	अगर (stsi(vm, 3, 2, 2) == 0 && vm->count) अणु
		EBCASC(vm->vm[0].cpi, माप(vm->vm[0].cpi));
		प्र_लिखो(hvstr, "%-16.16s", vm->vm[0].cpi);
		strim_all(hvstr);
	पूर्ण अन्यथा अणु
		प्र_लिखो(hvstr, "%s",
			MACHINE_IS_LPAR ? "LPAR" :
			MACHINE_IS_VM ? "z/VM" :
			MACHINE_IS_KVM ? "KVM" : "unknown");
	पूर्ण
	dump_stack_set_arch_desc("%s (%s)", mstr, hvstr);
पूर्ण

अटल __init व्योम setup_topology(व्योम)
अणु
	पूर्णांक max_mnest;

	अगर (!test_facility(11))
		वापस;
	S390_lowcore.machine_flags |= MACHINE_FLAG_TOPOLOGY;
	क्रम (max_mnest = 6; max_mnest > 1; max_mnest--) अणु
		अगर (stsi(&sysinfo_page, 15, 1, max_mnest) == 0)
			अवरोध;
	पूर्ण
	topology_max_mnest = max_mnest;
पूर्ण

अटल व्योम early_pgm_check_handler(व्योम)
अणु
	स्थिर काष्ठा exception_table_entry *fixup;
	अचिन्हित दीर्घ cr0, cr0_new;
	अचिन्हित दीर्घ addr;

	addr = S390_lowcore.program_old_psw.addr;
	fixup = s390_search_extables(addr);
	अगर (!fixup)
		disabled_रुको();
	/* Disable low address protection beक्रमe storing पूर्णांकo lowcore. */
	__ctl_store(cr0, 0, 0);
	cr0_new = cr0 & ~(1UL << 28);
	__ctl_load(cr0_new, 0, 0);
	S390_lowcore.program_old_psw.addr = extable_fixup(fixup);
	__ctl_load(cr0, 0, 0);
पूर्ण

अटल noअंतरभूत __init व्योम setup_lowcore_early(व्योम)
अणु
	psw_t psw;

	psw.addr = (अचिन्हित दीर्घ)s390_base_pgm_handler;
	psw.mask = PSW_MASK_BASE | PSW_DEFAULT_KEY | PSW_MASK_EA | PSW_MASK_BA;
	अगर (IS_ENABLED(CONFIG_KASAN))
		psw.mask |= PSW_MASK_DAT;
	S390_lowcore.program_new_psw = psw;
	s390_base_pgm_handler_fn = early_pgm_check_handler;
	S390_lowcore.preempt_count = INIT_PREEMPT_COUNT;
पूर्ण

अटल noअंतरभूत __init व्योम setup_facility_list(व्योम)
अणु
	स_नकल(S390_lowcore.alt_stfle_fac_list,
	       S390_lowcore.stfle_fac_list,
	       माप(S390_lowcore.alt_stfle_fac_list));
	अगर (!IS_ENABLED(CONFIG_KERNEL_NOBP))
		__clear_facility(82, S390_lowcore.alt_stfle_fac_list);
पूर्ण

अटल __init व्योम detect_diag9c(व्योम)
अणु
	अचिन्हित पूर्णांक cpu_address;
	पूर्णांक rc;

	cpu_address = stap();
	diag_stat_inc(DIAG_STAT_X09C);
	यंत्र अस्थिर(
		"	diag	%2,0,0x9c\n"
		"0:	la	%0,0\n"
		"1:\n"
		EX_TABLE(0b,1b)
		: "=d" (rc) : "0" (-EOPNOTSUPP), "d" (cpu_address) : "cc");
	अगर (!rc)
		S390_lowcore.machine_flags |= MACHINE_FLAG_DIAG9C;
पूर्ण

अटल __init व्योम detect_machine_facilities(व्योम)
अणु
	अगर (test_facility(8)) अणु
		S390_lowcore.machine_flags |= MACHINE_FLAG_EDAT1;
		__ctl_set_bit(0, 23);
	पूर्ण
	अगर (test_facility(78))
		S390_lowcore.machine_flags |= MACHINE_FLAG_EDAT2;
	अगर (test_facility(3))
		S390_lowcore.machine_flags |= MACHINE_FLAG_IDTE;
	अगर (test_facility(50) && test_facility(73)) अणु
		S390_lowcore.machine_flags |= MACHINE_FLAG_TE;
		__ctl_set_bit(0, 55);
	पूर्ण
	अगर (test_facility(51))
		S390_lowcore.machine_flags |= MACHINE_FLAG_TLB_LC;
	अगर (test_facility(129)) अणु
		S390_lowcore.machine_flags |= MACHINE_FLAG_VX;
		__ctl_set_bit(0, 17);
	पूर्ण
	अगर (test_facility(130) && !noexec_disabled) अणु
		S390_lowcore.machine_flags |= MACHINE_FLAG_NX;
		__ctl_set_bit(0, 20);
	पूर्ण
	अगर (test_facility(133))
		S390_lowcore.machine_flags |= MACHINE_FLAG_GS;
	अगर (test_facility(139) && (tod_घड़ी_base.tod >> 63)) अणु
		/* Enabled चिन्हित घड़ी comparator comparisons */
		S390_lowcore.machine_flags |= MACHINE_FLAG_SCC;
		घड़ी_comparator_max = -1ULL >> 1;
		__ctl_set_bit(0, 53);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम save_vector_रेजिस्टरs(व्योम)
अणु
#अगर_घोषित CONFIG_CRASH_DUMP
	अगर (test_facility(129))
		save_vx_regs(boot_cpu_vector_save_area);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम setup_control_रेजिस्टरs(व्योम)
अणु
	अचिन्हित दीर्घ reg;

	__ctl_store(reg, 0, 0);
	reg |= CR0_LOW_ADDRESS_PROTECTION;
	reg |= CR0_EMERGENCY_SIGNAL_SUBMASK;
	reg |= CR0_EXTERNAL_CALL_SUBMASK;
	__ctl_load(reg, 0, 0);
पूर्ण

अटल अंतरभूत व्योम setup_access_रेजिस्टरs(व्योम)
अणु
	अचिन्हित पूर्णांक acrs[NUM_ACRS] = अणु 0 पूर्ण;

	restore_access_regs(acrs);
पूर्ण

अटल पूर्णांक __init disable_vector_extension(अक्षर *str)
अणु
	S390_lowcore.machine_flags &= ~MACHINE_FLAG_VX;
	__ctl_clear_bit(0, 17);
	वापस 0;
पूर्ण
early_param("novx", disable_vector_extension);

अक्षर __bootdata(early_command_line)[COMMAND_LINE_SIZE];
अटल व्योम __init setup_boot_command_line(व्योम)
अणु
	/* copy arch command line */
	strlcpy(boot_command_line, early_command_line, ARCH_COMMAND_LINE_SIZE);
पूर्ण

अटल व्योम __init check_image_bootable(व्योम)
अणु
	अगर (!स_भेद(EP_STRING, (व्योम *)EP_OFFSET, म_माप(EP_STRING)))
		वापस;

	sclp_early_prपूर्णांकk("Linux kernel boot failure: An attempt to boot a vmlinux ELF image failed.\n");
	sclp_early_prपूर्णांकk("This image does not contain all parts necessary for starting up. Use\n");
	sclp_early_prपूर्णांकk("bzImage or arch/s390/boot/compressed/vmlinux instead.\n");
	disabled_रुको();
पूर्ण

व्योम __init startup_init(व्योम)
अणु
	reset_tod_घड़ी();
	check_image_bootable();
	समय_early_init();
	init_kernel_storage_key();
	lockdep_off();
	setup_lowcore_early();
	setup_facility_list();
	detect_machine_type();
	setup_arch_string();
	setup_boot_command_line();
	detect_diag9c();
	detect_machine_facilities();
	save_vector_रेजिस्टरs();
	setup_topology();
	sclp_early_detect();
	setup_control_रेजिस्टरs();
	setup_access_रेजिस्टरs();
	lockdep_on();
पूर्ण
