<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  osi.c - _OSI implementation
 *
 *  Copyright (C) 2016 Intel Corporation
 *    Author: Lv Zheng <lv.zheng@पूर्णांकel.com>
 */

/* Uncomment next line to get verbose prपूर्णांकout */
/* #घोषणा DEBUG */
#घोषणा pr_fmt(fmt) "ACPI: " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/platक्रमm_data/x86/apple.h>

#समावेश "internal.h"


#घोषणा OSI_STRING_LENGTH_MAX	64
#घोषणा OSI_STRING_ENTRIES_MAX	16

काष्ठा acpi_osi_entry अणु
	अक्षर string[OSI_STRING_LENGTH_MAX];
	bool enable;
पूर्ण;

अटल काष्ठा acpi_osi_config अणु
	u8		शेष_disabling;
	अचिन्हित पूर्णांक	linux_enable:1;
	अचिन्हित पूर्णांक	linux_dmi:1;
	अचिन्हित पूर्णांक	linux_cmdline:1;
	अचिन्हित पूर्णांक	darwin_enable:1;
	अचिन्हित पूर्णांक	darwin_dmi:1;
	अचिन्हित पूर्णांक	darwin_cmdline:1;
पूर्ण osi_config;

अटल काष्ठा acpi_osi_config osi_config;
अटल काष्ठा acpi_osi_entry
osi_setup_entries[OSI_STRING_ENTRIES_MAX] __initdata = अणु
	अणु"Module Device", trueपूर्ण,
	अणु"Processor Device", trueपूर्ण,
	अणु"3.0 _SCP Extensions", trueपूर्ण,
	अणु"Processor Aggregator Device", trueपूर्ण,
	/*
	 * Linux-Dell-Video is used by BIOS to disable RTD3 क्रम NVidia graphics
	 * cards as RTD3 is not supported by drivers now.  Systems with NVidia
	 * cards will hang without RTD3 disabled.
	 *
	 * Once NVidia drivers officially support RTD3, this _OSI strings can
	 * be हटाओd अगर both new and old graphics cards are supported.
	 */
	अणु"Linux-Dell-Video", trueपूर्ण,
	/*
	 * Linux-Lenovo-NV-HDMI-Audio is used by BIOS to घातer on NVidia's HDMI
	 * audio device which is turned off क्रम घातer-saving in Winकरोws OS.
	 * This घातer management feature observed on some Lenovo Thinkpad
	 * प्रणालीs which will not be able to output audio via HDMI without
	 * a BIOS workaround.
	 */
	अणु"Linux-Lenovo-NV-HDMI-Audio", trueपूर्ण,
	/*
	 * Linux-HPI-Hybrid-Graphics is used by BIOS to enable dGPU to
	 * output video directly to बाह्यal monitors on HP Inc. mobile
	 * workstations as Nvidia and AMD VGA drivers provide limited
	 * hybrid graphics supports.
	 */
	अणु"Linux-HPI-Hybrid-Graphics", trueपूर्ण,
पूर्ण;

अटल u32 acpi_osi_handler(acpi_string पूर्णांकerface, u32 supported)
अणु
	अगर (!म_भेद("Linux", पूर्णांकerface)) अणु
		pr_notice_once(FW_BUG
			"BIOS _OSI(Linux) query %s%s\n",
			osi_config.linux_enable ? "honored" : "ignored",
			osi_config.linux_cmdline ? " via cmdline" :
			osi_config.linux_dmi ? " via DMI" : "");
	पूर्ण
	अगर (!म_भेद("Darwin", पूर्णांकerface)) अणु
		pr_notice_once(
			"BIOS _OSI(Darwin) query %s%s\n",
			osi_config.darwin_enable ? "honored" : "ignored",
			osi_config.darwin_cmdline ? " via cmdline" :
			osi_config.darwin_dmi ? " via DMI" : "");
	पूर्ण

	वापस supported;
पूर्ण

व्योम __init acpi_osi_setup(अक्षर *str)
अणु
	काष्ठा acpi_osi_entry *osi;
	bool enable = true;
	पूर्णांक i;

	अगर (!acpi_gbl_create_osi_method)
		वापस;

	अगर (str == शून्य || *str == '\0') अणु
		pr_info("_OSI method disabled\n");
		acpi_gbl_create_osi_method = FALSE;
		वापस;
	पूर्ण

	अगर (*str == '!') अणु
		str++;
		अगर (*str == '\0') अणु
			/* Do not override acpi_osi=!* */
			अगर (!osi_config.शेष_disabling)
				osi_config.शेष_disabling =
					ACPI_DISABLE_ALL_VENDOR_STRINGS;
			वापस;
		पूर्ण अन्यथा अगर (*str == '*') अणु
			osi_config.शेष_disabling = ACPI_DISABLE_ALL_STRINGS;
			क्रम (i = 0; i < OSI_STRING_ENTRIES_MAX; i++) अणु
				osi = &osi_setup_entries[i];
				osi->enable = false;
			पूर्ण
			वापस;
		पूर्ण अन्यथा अगर (*str == '!') अणु
			osi_config.शेष_disabling = 0;
			वापस;
		पूर्ण
		enable = false;
	पूर्ण

	क्रम (i = 0; i < OSI_STRING_ENTRIES_MAX; i++) अणु
		osi = &osi_setup_entries[i];
		अगर (!म_भेद(osi->string, str)) अणु
			osi->enable = enable;
			अवरोध;
		पूर्ण अन्यथा अगर (osi->string[0] == '\0') अणु
			osi->enable = enable;
			म_नकलन(osi->string, str, OSI_STRING_LENGTH_MAX);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __init __acpi_osi_setup_darwin(bool enable)
अणु
	osi_config.darwin_enable = !!enable;
	अगर (enable) अणु
		acpi_osi_setup("!");
		acpi_osi_setup("Darwin");
	पूर्ण अन्यथा अणु
		acpi_osi_setup("!!");
		acpi_osi_setup("!Darwin");
	पूर्ण
पूर्ण

अटल व्योम __init acpi_osi_setup_darwin(bool enable)
अणु
	/* Override acpi_osi_dmi_blacklisted() */
	osi_config.darwin_dmi = 0;
	osi_config.darwin_cmdline = 1;
	__acpi_osi_setup_darwin(enable);
पूर्ण

/*
 * The story of _OSI(Linux)
 *
 * From pre-history through Linux-2.6.22, Linux responded TRUE upon a BIOS
 * OSI(Linux) query.
 *
 * Unक्रमtunately, reference BIOS ग_लिखोrs got wind of this and put
 * OSI(Linux) in their example code, quickly exposing this string as
 * ill-conceived and खोलोing the करोor to an un-bounded number of BIOS
 * incompatibilities.
 *
 * For example, OSI(Linux) was used on resume to re-POST a video card on
 * one प्रणाली, because Linux at that समय could not करो a speedy restore in
 * its native driver. But then upon gaining quick native restore
 * capability, Linux has no way to tell the BIOS to skip the समय-consuming
 * POST -- putting Linux at a permanent perक्रमmance disadvantage. On
 * another प्रणाली, the BIOS ग_लिखोr used OSI(Linux) to infer native OS
 * support क्रम IPMI!  On other प्रणालीs, OSI(Linux) simply got in the way of
 * Linux claiming to be compatible with other operating प्रणालीs, exposing
 * BIOS issues such as skipped device initialization.
 *
 * So "Linux" turned out to be a really poor chose of OSI string, and from
 * Linux-2.6.23 onward we respond FALSE.
 *
 * BIOS ग_लिखोrs should NOT query _OSI(Linux) on future प्रणालीs. Linux will
 * complain on the console when it sees it, and वापस FALSE. To get Linux
 * to वापस TRUE क्रम your प्रणाली  will require a kernel source update to
 * add a DMI entry, or boot with "acpi_osi=Linux"
 */
अटल व्योम __init __acpi_osi_setup_linux(bool enable)
अणु
	osi_config.linux_enable = !!enable;
	अगर (enable)
		acpi_osi_setup("Linux");
	अन्यथा
		acpi_osi_setup("!Linux");
पूर्ण

अटल व्योम __init acpi_osi_setup_linux(bool enable)
अणु
	/* Override acpi_osi_dmi_blacklisted() */
	osi_config.linux_dmi = 0;
	osi_config.linux_cmdline = 1;
	__acpi_osi_setup_linux(enable);
पूर्ण

/*
 * Modअगरy the list of "OS Interfaces" reported to BIOS via _OSI
 *
 * empty string disables _OSI
 * string starting with '!' disables that string
 * otherwise string is added to list, augmenting built-in strings
 */
अटल व्योम __init acpi_osi_setup_late(व्योम)
अणु
	काष्ठा acpi_osi_entry *osi;
	अक्षर *str;
	पूर्णांक i;
	acpi_status status;

	अगर (osi_config.शेष_disabling) अणु
		status = acpi_update_पूर्णांकerfaces(osi_config.शेष_disabling);
		अगर (ACPI_SUCCESS(status))
			pr_info("Disabled all _OSI OS vendors%s\n",
				osi_config.शेष_disabling ==
				ACPI_DISABLE_ALL_STRINGS ?
				" and feature groups" : "");
	पूर्ण

	क्रम (i = 0; i < OSI_STRING_ENTRIES_MAX; i++) अणु
		osi = &osi_setup_entries[i];
		str = osi->string;
		अगर (*str == '\0')
			अवरोध;
		अगर (osi->enable) अणु
			status = acpi_install_पूर्णांकerface(str);
			अगर (ACPI_SUCCESS(status))
				pr_info("Added _OSI(%s)\n", str);
		पूर्ण अन्यथा अणु
			status = acpi_हटाओ_पूर्णांकerface(str);
			अगर (ACPI_SUCCESS(status))
				pr_info("Deleted _OSI(%s)\n", str);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __init osi_setup(अक्षर *str)
अणु
	अगर (str && !म_भेद("Linux", str))
		acpi_osi_setup_linux(true);
	अन्यथा अगर (str && !म_भेद("!Linux", str))
		acpi_osi_setup_linux(false);
	अन्यथा अगर (str && !म_भेद("Darwin", str))
		acpi_osi_setup_darwin(true);
	अन्यथा अगर (str && !म_भेद("!Darwin", str))
		acpi_osi_setup_darwin(false);
	अन्यथा
		acpi_osi_setup(str);

	वापस 1;
पूर्ण
__setup("acpi_osi=", osi_setup);

bool acpi_osi_is_win8(व्योम)
अणु
	वापस acpi_gbl_osi_data >= ACPI_OSI_WIN_8;
पूर्ण
EXPORT_SYMBOL(acpi_osi_is_win8);

अटल व्योम __init acpi_osi_dmi_darwin(व्योम)
अणु
	pr_notice("DMI detected to setup _OSI(\"Darwin\"): Apple hardware\n");
	osi_config.darwin_dmi = 1;
	__acpi_osi_setup_darwin(true);
पूर्ण

अटल व्योम __init acpi_osi_dmi_linux(bool enable,
				      स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	pr_notice("DMI detected to setup _OSI(\"Linux\"): %s\n", d->ident);
	osi_config.linux_dmi = 1;
	__acpi_osi_setup_linux(enable);
पूर्ण

अटल पूर्णांक __init dmi_enable_osi_linux(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	acpi_osi_dmi_linux(true, d);

	वापस 0;
पूर्ण

अटल पूर्णांक __init dmi_disable_osi_vista(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	pr_notice("DMI detected: %s\n", d->ident);
	acpi_osi_setup("!Windows 2006");
	acpi_osi_setup("!Windows 2006 SP1");
	acpi_osi_setup("!Windows 2006 SP2");

	वापस 0;
पूर्ण

अटल पूर्णांक __init dmi_disable_osi_win7(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	pr_notice("DMI detected: %s\n", d->ident);
	acpi_osi_setup("!Windows 2009");

	वापस 0;
पूर्ण

अटल पूर्णांक __init dmi_disable_osi_win8(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	pr_notice("DMI detected: %s\n", d->ident);
	acpi_osi_setup("!Windows 2012");

	वापस 0;
पूर्ण

/*
 * Linux शेष _OSI response behavior is determined by this DMI table.
 *
 * Note that _OSI("Linux")/_OSI("Darwin") determined here can be overridden
 * by acpi_osi=!Linux/acpi_osi=!Darwin command line options.
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id acpi_osi_dmi_table[] __initस्थिर = अणु
	अणु
	.callback = dmi_disable_osi_vista,
	.ident = "Fujitsu Siemens",
	.matches = अणु
		     DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"),
		     DMI_MATCH(DMI_PRODUCT_NAME, "ESPRIMO Mobile V5505"),
		पूर्ण,
	पूर्ण,
	अणु
	/*
	 * There have a NVIF method in MSI GX723 DSDT need call by Nvidia
	 * driver (e.g. nouveau) when user press brightness hotkey.
	 * Currently, nouveau driver didn't करो the job and it causes there
	 * have a infinite जबतक loop in DSDT when user press hotkey.
	 * We add MSI GX723's dmi inक्रमmation to this table क्रम workaround
	 * this issue.
	 * Will हटाओ MSI GX723 from the table after nouveau grows support.
	 */
	.callback = dmi_disable_osi_vista,
	.ident = "MSI GX723",
	.matches = अणु
		     DMI_MATCH(DMI_SYS_VENDOR, "Micro-Star International"),
		     DMI_MATCH(DMI_PRODUCT_NAME, "GX723"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = dmi_disable_osi_vista,
	.ident = "Sony VGN-NS10J_S",
	.matches = अणु
		     DMI_MATCH(DMI_SYS_VENDOR, "Sony Corporation"),
		     DMI_MATCH(DMI_PRODUCT_NAME, "VGN-NS10J_S"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = dmi_disable_osi_vista,
	.ident = "Sony VGN-SR290J",
	.matches = अणु
		     DMI_MATCH(DMI_SYS_VENDOR, "Sony Corporation"),
		     DMI_MATCH(DMI_PRODUCT_NAME, "VGN-SR290J"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = dmi_disable_osi_vista,
	.ident = "VGN-NS50B_L",
	.matches = अणु
		     DMI_MATCH(DMI_SYS_VENDOR, "Sony Corporation"),
		     DMI_MATCH(DMI_PRODUCT_NAME, "VGN-NS50B_L"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = dmi_disable_osi_vista,
	.ident = "VGN-SR19XN",
	.matches = अणु
		     DMI_MATCH(DMI_SYS_VENDOR, "Sony Corporation"),
		     DMI_MATCH(DMI_PRODUCT_NAME, "VGN-SR19XN"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = dmi_disable_osi_vista,
	.ident = "Toshiba Satellite L355",
	.matches = अणु
		     DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
		     DMI_MATCH(DMI_PRODUCT_VERSION, "Satellite L355"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = dmi_disable_osi_win7,
	.ident = "ASUS K50IJ",
	.matches = अणु
		     DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK Computer Inc."),
		     DMI_MATCH(DMI_PRODUCT_NAME, "K50IJ"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = dmi_disable_osi_vista,
	.ident = "Toshiba P305D",
	.matches = अणु
		     DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
		     DMI_MATCH(DMI_PRODUCT_NAME, "Satellite P305D"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = dmi_disable_osi_vista,
	.ident = "Toshiba NB100",
	.matches = अणु
		     DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
		     DMI_MATCH(DMI_PRODUCT_NAME, "NB100"),
		पूर्ण,
	पूर्ण,

	/*
	 * The wireless hotkey करोes not work on those machines when
	 * वापसing true क्रम _OSI("Windows 2012")
	 */
	अणु
	.callback = dmi_disable_osi_win8,
	.ident = "Dell Inspiron 7737",
	.matches = अणु
		    DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
		    DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 7737"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = dmi_disable_osi_win8,
	.ident = "Dell Inspiron 7537",
	.matches = अणु
		    DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
		    DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 7537"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = dmi_disable_osi_win8,
	.ident = "Dell Inspiron 5437",
	.matches = अणु
		    DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
		    DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 5437"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = dmi_disable_osi_win8,
	.ident = "Dell Inspiron 3437",
	.matches = अणु
		    DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
		    DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 3437"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = dmi_disable_osi_win8,
	.ident = "Dell Vostro 3446",
	.matches = अणु
		    DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
		    DMI_MATCH(DMI_PRODUCT_NAME, "Vostro 3446"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = dmi_disable_osi_win8,
	.ident = "Dell Vostro 3546",
	.matches = अणु
		    DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
		    DMI_MATCH(DMI_PRODUCT_NAME, "Vostro 3546"),
		पूर्ण,
	पूर्ण,

	/*
	 * BIOS invocation of _OSI(Linux) is almost always a BIOS bug.
	 * Linux ignores it, except क्रम the machines क्रमागतerated below.
	 */

	/*
	 * Without this EEEpc exports a non working WMI पूर्णांकerface, with
	 * this it exports a working "good old" eeepc_laptop पूर्णांकerface,
	 * fixing both brightness control, and rfसमाप्त not working.
	 */
	अणु
	.callback = dmi_enable_osi_linux,
	.ident = "Asus EEE PC 1015PX",
	.matches = अणु
		     DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK Computer INC."),
		     DMI_MATCH(DMI_PRODUCT_NAME, "1015PX"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल __init व्योम acpi_osi_dmi_blacklisted(व्योम)
अणु
	dmi_check_प्रणाली(acpi_osi_dmi_table);

	/* Enable _OSI("Darwin") क्रम Apple platक्रमms. */
	अगर (x86_apple_machine)
		acpi_osi_dmi_darwin();
पूर्ण

पूर्णांक __init early_acpi_osi_init(व्योम)
अणु
	acpi_osi_dmi_blacklisted();

	वापस 0;
पूर्ण

पूर्णांक __init acpi_osi_init(व्योम)
अणु
	acpi_install_पूर्णांकerface_handler(acpi_osi_handler);
	acpi_osi_setup_late();

	वापस 0;
पूर्ण
