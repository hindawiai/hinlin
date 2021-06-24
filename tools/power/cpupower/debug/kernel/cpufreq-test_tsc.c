<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * test module to check whether the TSC-based delay routine जारीs
 * to work properly after cpufreq transitions. Needs ACPI to work
 * properly.
 *
 * Based partly on the Power Management Timer (PMTMR) code to be found
 * in arch/i386/kernel/समयrs/समयr_pm.c on recent 2.6. kernels, especially
 * code written by John Stultz. The पढ़ो_pmपंचांगr function was copied verbatim
 * from that file.
 *
 * (C) 2004 Dominik Broकरोwski
 *
 * To use:
 * 1.) pass घड़ी=tsc to the kernel on your bootloader
 * 2.) modprobe this module (it'll fail)
 * 3.) change CPU frequency
 * 4.) modprobe this module again
 * 5.) अगर the third value, "diff_pmtmr", changes between 2. and 4., the
 *     TSC-based delay routine on the Linux kernel करोes not correctly
 *     handle the cpufreq transition. Please report this to
 *     linux-pm@vger.kernel.org
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/acpi.h>
#समावेश <यंत्र/पन.स>

अटल पूर्णांक pm_पंचांगr_ioport = 0;

/*helper function to safely पढ़ो acpi pm बारource*/
अटल u32 पढ़ो_pmपंचांगr(व्योम)
अणु
	u32 v1=0,v2=0,v3=0;
	/* It has been reported that because of various broken
	 * chipsets (ICH4, PIIX4 and PIIX4E) where the ACPI PM समय
	 * source is not latched, so you must पढ़ो it multiple
	 * बार to insure a safe value is पढ़ो.
	 */
	करो अणु
		v1 = inl(pm_पंचांगr_ioport);
		v2 = inl(pm_पंचांगr_ioport);
		v3 = inl(pm_पंचांगr_ioport);
	पूर्ण जबतक ((v1 > v2 && v1 < v3) || (v2 > v3 && v2 < v1)
		 || (v3 > v1 && v3 < v2));

	/* mask the output to 24 bits */
	वापस (v2 & 0xFFFFFF);
पूर्ण

अटल पूर्णांक __init cpufreq_test_tsc(व्योम)
अणु
	u32 now, then, dअगरf;
	u64 now_tsc, then_tsc, dअगरf_tsc;
	पूर्णांक i;

	/* the following code snipped is copied from arch/x86/kernel/acpi/boot.c
	   of Linux v2.6.25. */

	/* detect the location of the ACPI PM Timer */
	अगर (acpi_gbl_FADT.header.revision >= FADT2_REVISION_ID) अणु
		/* FADT rev. 2 */
		अगर (acpi_gbl_FADT.xpm_समयr_block.space_id !=
		    ACPI_ADR_SPACE_SYSTEM_IO)
			वापस 0;

		pm_पंचांगr_ioport = acpi_gbl_FADT.xpm_समयr_block.address;
		/*
		 * "X" fields are optional extensions to the original V1.0
		 * fields, so we must selectively expand V1.0 fields अगर the
		 * corresponding X field is zero.
	 	 */
		अगर (!pm_पंचांगr_ioport)
			pm_पंचांगr_ioport = acpi_gbl_FADT.pm_समयr_block;
	पूर्ण अन्यथा अणु
		/* FADT rev. 1 */
		pm_पंचांगr_ioport = acpi_gbl_FADT.pm_समयr_block;
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "start--> \n");
	then = पढ़ो_pmपंचांगr();
	then_tsc = rdtsc();
	क्रम (i=0;i<20;i++) अणु
		mdelay(100);
		now = पढ़ो_pmपंचांगr();
		now_tsc = rdtsc();
		dअगरf = (now - then) & 0xFFFFFF;
		dअगरf_tsc = now_tsc - then_tsc;
		prपूर्णांकk(KERN_DEBUG "t1: %08u t2: %08u diff_pmtmr: %08u diff_tsc: %016llu\n", then, now, dअगरf, dअगरf_tsc);
		then = now;
		then_tsc = now_tsc;
	पूर्ण
	prपूर्णांकk(KERN_DEBUG "<-- end \n");
	वापस -ENODEV;
पूर्ण

अटल व्योम __निकास cpufreq_none(व्योम)
अणु
	वापस;
पूर्ण

module_init(cpufreq_test_tsc)
module_निकास(cpufreq_none)


MODULE_AUTHOR("Dominik Brodowski");
MODULE_DESCRIPTION("Verify the TSC cpufreq notifier working correctly -- needs ACPI-enabled system");
MODULE_LICENSE ("GPL");
