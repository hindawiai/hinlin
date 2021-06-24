<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/घड़ीsource/acpi_pm.c
 *
 * This file contains the ACPI PM based घड़ीsource.
 *
 * This code was largely moved from the i386 समयr_pm.c file
 * which was (C) Dominik Broकरोwski <linux@broकरो.de> 2003
 * and contained the following comments:
 *
 * Driver to use the Power Management Timer (PMTMR) available in some
 * southbridges as primary timing source क्रम the Linux kernel.
 *
 * Based on parts of linux/drivers/acpi/hardware/hwसमयr.c, समयr_pit.c,
 * समयr_hpet.c, and on Arjan van de Ven's implementation क्रम 2.4.
 */

#समावेश <linux/acpi_pmपंचांगr.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/समयx.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/पन.स>

/*
 * The I/O port the PMTMR resides at.
 * The location is detected during setup_arch(),
 * in arch/i386/kernel/acpi/boot.c
 */
u32 pmपंचांगr_ioport __पढ़ो_mostly;

अटल अंतरभूत u32 पढ़ो_pmपंचांगr(व्योम)
अणु
	/* mask the output to 24 bits */
	वापस inl(pmपंचांगr_ioport) & ACPI_PM_MASK;
पूर्ण

u32 acpi_pm_पढ़ो_verअगरied(व्योम)
अणु
	u32 v1 = 0, v2 = 0, v3 = 0;

	/*
	 * It has been reported that because of various broken
	 * chipsets (ICH4, PIIX4 and PIIX4E) where the ACPI PM घड़ी
	 * source is not latched, you must पढ़ो it multiple
	 * बार to ensure a safe value is पढ़ो:
	 */
	करो अणु
		v1 = पढ़ो_pmपंचांगr();
		v2 = पढ़ो_pmपंचांगr();
		v3 = पढ़ो_pmपंचांगr();
	पूर्ण जबतक (unlikely((v1 > v2 && v1 < v3) || (v2 > v3 && v2 < v1)
			  || (v3 > v1 && v3 < v2)));

	वापस v2;
पूर्ण

अटल u64 acpi_pm_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	वापस (u64)पढ़ो_pmपंचांगr();
पूर्ण

अटल काष्ठा घड़ीsource घड़ीsource_acpi_pm = अणु
	.name		= "acpi_pm",
	.rating		= 200,
	.पढ़ो		= acpi_pm_पढ़ो,
	.mask		= (u64)ACPI_PM_MASK,
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;


#अगर_घोषित CONFIG_PCI
अटल पूर्णांक acpi_pm_good;
अटल पूर्णांक __init acpi_pm_good_setup(अक्षर *__str)
अणु
	acpi_pm_good = 1;
	वापस 1;
पूर्ण
__setup("acpi_pm_good", acpi_pm_good_setup);

अटल u64 acpi_pm_पढ़ो_slow(काष्ठा घड़ीsource *cs)
अणु
	वापस (u64)acpi_pm_पढ़ो_verअगरied();
पूर्ण

अटल अंतरभूत व्योम acpi_pm_need_workaround(व्योम)
अणु
	घड़ीsource_acpi_pm.पढ़ो = acpi_pm_पढ़ो_slow;
	घड़ीsource_acpi_pm.rating = 120;
पूर्ण

/*
 * PIIX4 Errata:
 *
 * The घातer management समयr may वापस improper results when पढ़ो.
 * Although the समयr value settles properly after incrementing,
 * जबतक incrementing there is a 3 ns winकरोw every 69.8 ns where the
 * समयr value is indeterminate (a 4.2% chance that the data will be
 * incorrect when पढ़ो). As a result, the ACPI मुक्त running count up
 * समयr specअगरication is violated due to erroneous पढ़ोs.
 */
अटल व्योम acpi_pm_check_blacklist(काष्ठा pci_dev *dev)
अणु
	अगर (acpi_pm_good)
		वापस;

	/* the bug has been fixed in PIIX4M */
	अगर (dev->revision < 3) अणु
		pr_warn("* Found PM-Timer Bug on the chipset. Due to workarounds for a bug,\n"
			"* this clock source is slow. Consider trying other clock sources\n");

		acpi_pm_need_workaround();
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82371AB_3,
			acpi_pm_check_blacklist);

अटल व्योम acpi_pm_check_graylist(काष्ठा pci_dev *dev)
अणु
	अगर (acpi_pm_good)
		वापस;

	pr_warn("* The chipset may have PM-Timer Bug. Due to workarounds for a bug,\n"
		"* this clock source is slow. If you are sure your timer does not have\n"
		"* this bug, please use \"acpi_pm_good\" to disable the workaround\n");

	acpi_pm_need_workaround();
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82801DB_0,
			acpi_pm_check_graylist);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_SERVERWORKS, PCI_DEVICE_ID_SERVERWORKS_LE,
			acpi_pm_check_graylist);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_X86_64
#समावेश <यंत्र/mach_समयr.h>
#घोषणा PMTMR_EXPECTED_RATE \
  ((CALIBRATE_LATCH * (PMTMR_TICKS_PER_SEC >> 10)) / (PIT_TICK_RATE>>10))
/*
 * Some boards have the PMTMR running way too fast. We check
 * the PMTMR rate against PIT channel 2 to catch these हालs.
 */
अटल पूर्णांक verअगरy_pmपंचांगr_rate(व्योम)
अणु
	u64 value1, value2;
	अचिन्हित दीर्घ count, delta;

	mach_prepare_counter();
	value1 = घड़ीsource_acpi_pm.पढ़ो(&घड़ीsource_acpi_pm);
	mach_countup(&count);
	value2 = घड़ीsource_acpi_pm.पढ़ो(&घड़ीsource_acpi_pm);
	delta = (value2 - value1) & ACPI_PM_MASK;

	/* Check that the PMTMR delta is within 5% of what we expect */
	अगर (delta < (PMTMR_EXPECTED_RATE * 19) / 20 ||
	    delta > (PMTMR_EXPECTED_RATE * 21) / 20) अणु
		pr_info("PM-Timer running at invalid rate: %lu%% of normal - aborting.\n",
			100UL * delta / PMTMR_EXPECTED_RATE);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा verअगरy_pmपंचांगr_rate() (0)
#पूर्ण_अगर

/* Number of monotonicity checks to perक्रमm during initialization */
#घोषणा ACPI_PM_MONOTONICITY_CHECKS 10
/* Number of पढ़ोs we try to get two dअगरferent values */
#घोषणा ACPI_PM_READ_CHECKS 10000

अटल पूर्णांक __init init_acpi_pm_घड़ीsource(व्योम)
अणु
	u64 value1, value2;
	अचिन्हित पूर्णांक i, j = 0;

	अगर (!pmपंचांगr_ioport)
		वापस -ENODEV;

	/* "verify" this timing source: */
	क्रम (j = 0; j < ACPI_PM_MONOTONICITY_CHECKS; j++) अणु
		udelay(100 * j);
		value1 = घड़ीsource_acpi_pm.पढ़ो(&घड़ीsource_acpi_pm);
		क्रम (i = 0; i < ACPI_PM_READ_CHECKS; i++) अणु
			value2 = घड़ीsource_acpi_pm.पढ़ो(&घड़ीsource_acpi_pm);
			अगर (value2 == value1)
				जारी;
			अगर (value2 > value1)
				अवरोध;
			अगर ((value2 < value1) && ((value2) < 0xFFF))
				अवरोध;
			pr_info("PM-Timer had inconsistent results: %#llx, %#llx - aborting.\n",
				value1, value2);
			pmपंचांगr_ioport = 0;
			वापस -EINVAL;
		पूर्ण
		अगर (i == ACPI_PM_READ_CHECKS) अणु
			pr_info("PM-Timer failed consistency check  (%#llx) - aborting.\n",
				value1);
			pmपंचांगr_ioport = 0;
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	अगर (verअगरy_pmपंचांगr_rate() != 0)अणु
		pmपंचांगr_ioport = 0;
		वापस -ENODEV;
	पूर्ण

	वापस घड़ीsource_रेजिस्टर_hz(&घड़ीsource_acpi_pm,
						PMTMR_TICKS_PER_SEC);
पूर्ण

/* We use fs_initcall because we want the PCI fixups to have run
 * but we still need to load beक्रमe device_initcall
 */
fs_initcall(init_acpi_pm_घड़ीsource);

/*
 * Allow an override of the IOPort. Stupid BIOSes करो not tell us about
 * the PMTimer, but we might know where it is.
 */
अटल पूर्णांक __init parse_pmपंचांगr(अक्षर *arg)
अणु
	अचिन्हित पूर्णांक base;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक(arg, 16, &base);
	अगर (ret)
		वापस ret;

	pr_info("PMTMR IOPort override: 0x%04x -> 0x%04x\n", pmपंचांगr_ioport,
		base);
	pmपंचांगr_ioport = base;

	वापस 1;
पूर्ण
__setup("pmtmr=", parse_pmपंचांगr);
