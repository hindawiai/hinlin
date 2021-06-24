<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  blacklist.c
 *
 *  Check to see अगर the given machine has a known bad ACPI BIOS
 *  or अगर the BIOS is too old.
 *  Check given machine against acpi_rev_dmi_table[].
 *
 *  Copyright (C) 2004 Len Brown <len.brown@पूर्णांकel.com>
 *  Copyright (C) 2002 Andy Grover <andrew.grover@पूर्णांकel.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>

#समावेश "internal.h"

#अगर_घोषित CONFIG_DMI
अटल स्थिर काष्ठा dmi_प्रणाली_id acpi_rev_dmi_table[] __initस्थिर;
#पूर्ण_अगर

/*
 * POLICY: If *anything* करोesn't work, put it on the blacklist.
 *	   If they are critical errors, mark it critical, and पात driver load.
 */
अटल काष्ठा acpi_platक्रमm_list acpi_blacklist[] __initdata = अणु
	/* Compaq Presario 1700 */
	अणु"PTLTD ", "  DSDT  ", 0x06040000, ACPI_SIG_DSDT, less_than_or_equal,
	 "Multiple problems", 1पूर्ण,
	/* Sony FX120, FX140, FX150? */
	अणु"SONY  ", "U0      ", 0x20010313, ACPI_SIG_DSDT, less_than_or_equal,
	 "ACPI driver problem", 1पूर्ण,
	/* Compaq Presario 800, Insyde BIOS */
	अणु"INT440", "SYSFexxx", 0x00001001, ACPI_SIG_DSDT, less_than_or_equal,
	 "Does not use _REG to protect EC OpRegions", 1पूर्ण,
	/* IBM 600E - _ADR should वापस 7, but it वापसs 1 */
	अणु"IBM   ", "TP600E  ", 0x00000105, ACPI_SIG_DSDT, less_than_or_equal,
	 "Incorrect _ADR", 1पूर्ण,

	अणु पूर्ण
पूर्ण;

पूर्णांक __init acpi_blacklisted(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक blacklisted = 0;

	i = acpi_match_platक्रमm_list(acpi_blacklist);
	अगर (i >= 0) अणु
		pr_err(PREFIX "Vendor \"%6.6s\" System \"%8.8s\" Revision 0x%x has a known ACPI BIOS problem.\n",
		       acpi_blacklist[i].oem_id,
		       acpi_blacklist[i].oem_table_id,
		       acpi_blacklist[i].oem_revision);

		pr_err(PREFIX "Reason: %s. This is a %s error\n",
		       acpi_blacklist[i].reason,
		       (acpi_blacklist[i].data ?
			"non-recoverable" : "recoverable"));

		blacklisted = acpi_blacklist[i].data;
	पूर्ण

	(व्योम)early_acpi_osi_init();
#अगर_घोषित CONFIG_DMI
	dmi_check_प्रणाली(acpi_rev_dmi_table);
#पूर्ण_अगर

	वापस blacklisted;
पूर्ण
#अगर_घोषित CONFIG_DMI
#अगर_घोषित CONFIG_ACPI_REV_OVERRIDE_POSSIBLE
अटल पूर्णांक __init dmi_enable_rev_override(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	prपूर्णांकk(KERN_NOTICE PREFIX "DMI detected: %s (force ACPI _REV to 5)\n",
	       d->ident);
	acpi_rev_override_setup(शून्य);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dmi_प्रणाली_id acpi_rev_dmi_table[] __initस्थिर = अणु
#अगर_घोषित CONFIG_ACPI_REV_OVERRIDE_POSSIBLE
	/*
	 * DELL XPS 13 (2015) चयनes sound between HDA and I2S
	 * depending on the ACPI _REV callback. If userspace supports
	 * I2S sufficiently (or अगर you करो not care about sound), you
	 * can safely disable this quirk.
	 */
	अणु
	 .callback = dmi_enable_rev_override,
	 .ident = "DELL XPS 13 (2015)",
	 .matches = अणु
		      DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
		      DMI_MATCH(DMI_PRODUCT_NAME, "XPS 13 9343"),
		पूर्ण,
	पूर्ण,
	अणु
	 .callback = dmi_enable_rev_override,
	 .ident = "DELL Precision 5520",
	 .matches = अणु
		      DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
		      DMI_MATCH(DMI_PRODUCT_NAME, "Precision 5520"),
		पूर्ण,
	पूर्ण,
	अणु
	 .callback = dmi_enable_rev_override,
	 .ident = "DELL Precision 3520",
	 .matches = अणु
		      DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
		      DMI_MATCH(DMI_PRODUCT_NAME, "Precision 3520"),
		पूर्ण,
	पूर्ण,
	/*
	 * Resolves a quirk with the Dell Latitude 3350 that
	 * causes the ethernet adapter to not function.
	 */
	अणु
	 .callback = dmi_enable_rev_override,
	 .ident = "DELL Latitude 3350",
	 .matches = अणु
		      DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
		      DMI_MATCH(DMI_PRODUCT_NAME, "Latitude 3350"),
		पूर्ण,
	पूर्ण,
	अणु
	 .callback = dmi_enable_rev_override,
	 .ident = "DELL Inspiron 7537",
	 .matches = अणु
		      DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
		      DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 7537"),
		पूर्ण,
	पूर्ण,
#पूर्ण_अगर
	अणुपूर्ण
पूर्ण;

#पूर्ण_अगर /* CONFIG_DMI */
