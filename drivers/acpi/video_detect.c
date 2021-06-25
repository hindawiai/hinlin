<शैली गुरु>
/*
 *  Copyright (C) 2015       Red Hat Inc.
 *                           Hans de Goede <hdegoede@redhat.com>
 *  Copyright (C) 2008       SuSE Linux Products GmbH
 *                           Thomas Renninger <trenn@suse.de>
 *
 *  May be copied or modअगरied under the terms of the GNU General Public License
 *
 * video_detect.c:
 * After PCI devices are glued with ACPI devices
 * acpi_get_pci_dev() can be called to identअगरy ACPI graphics
 * devices क्रम which a real graphics card is plugged in
 *
 * Depending on whether ACPI graphics extensions (cmp. ACPI spec Appendix B)
 * are available, video.ko should be used to handle the device.
 *
 * Otherwise venकरोr specअगरic drivers like thinkpad_acpi, asus-laptop,
 * sony_acpi,... can take care about backlight brightness.
 *
 * Backlight drivers can use acpi_video_get_backlight_type() to determine
 * which driver should handle the backlight.
 *
 * If CONFIG_ACPI_VIDEO is neither set as "compiled in" (y) nor as a module (m)
 * this file will not be compiled and acpi_video_get_backlight_type() will
 * always वापस acpi_backlight_venकरोr.
 */

#समावेश <linux/export.h>
#समावेश <linux/acpi.h>
#समावेश <linux/backlight.h>
#समावेश <linux/dmi.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>
#समावेश <acpi/video.h>

व्योम acpi_video_unरेजिस्टर_backlight(व्योम);

अटल bool backlight_notअगरier_रेजिस्टरed;
अटल काष्ठा notअगरier_block backlight_nb;
अटल काष्ठा work_काष्ठा backlight_notअगरy_work;

अटल क्रमागत acpi_backlight_type acpi_backlight_cmdline = acpi_backlight_undef;
अटल क्रमागत acpi_backlight_type acpi_backlight_dmi = acpi_backlight_undef;

अटल व्योम acpi_video_parse_cmdline(व्योम)
अणु
	अगर (!म_भेद("vendor", acpi_video_backlight_string))
		acpi_backlight_cmdline = acpi_backlight_venकरोr;
	अगर (!म_भेद("video", acpi_video_backlight_string))
		acpi_backlight_cmdline = acpi_backlight_video;
	अगर (!म_भेद("native", acpi_video_backlight_string))
		acpi_backlight_cmdline = acpi_backlight_native;
	अगर (!म_भेद("none", acpi_video_backlight_string))
		acpi_backlight_cmdline = acpi_backlight_none;
पूर्ण

अटल acpi_status
find_video(acpi_handle handle, u32 lvl, व्योम *context, व्योम **rv)
अणु
	दीर्घ *cap = context;
	काष्ठा pci_dev *dev;
	काष्ठा acpi_device *acpi_dev;

	अटल स्थिर काष्ठा acpi_device_id video_ids[] = अणु
		अणुACPI_VIDEO_HID, 0पूर्ण,
		अणु"", 0पूर्ण,
	पूर्ण;
	अगर (acpi_bus_get_device(handle, &acpi_dev))
		वापस AE_OK;

	अगर (!acpi_match_device_ids(acpi_dev, video_ids)) अणु
		dev = acpi_get_pci_dev(handle);
		अगर (!dev)
			वापस AE_OK;
		pci_dev_put(dev);
		*cap |= acpi_is_video_device(handle);
	पूर्ण
	वापस AE_OK;
पूर्ण

/* Force to use venकरोr driver when the ACPI device is known to be
 * buggy */
अटल पूर्णांक video_detect_क्रमce_venकरोr(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	acpi_backlight_dmi = acpi_backlight_venकरोr;
	वापस 0;
पूर्ण

अटल पूर्णांक video_detect_क्रमce_video(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	acpi_backlight_dmi = acpi_backlight_video;
	वापस 0;
पूर्ण

अटल पूर्णांक video_detect_क्रमce_native(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	acpi_backlight_dmi = acpi_backlight_native;
	वापस 0;
पूर्ण

अटल पूर्णांक video_detect_क्रमce_none(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	acpi_backlight_dmi = acpi_backlight_none;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id video_detect_dmi_table[] = अणु
	/* On Samsung X360, the BIOS will set a flag (VDRV) अगर generic
	 * ACPI backlight device is used. This flag will definitively अवरोध
	 * the backlight पूर्णांकerface (even the venकरोr पूर्णांकerface) until next
	 * reboot. It's why we should prevent video.ko from being used here
	 * and we can't rely on a later call to acpi_video_unरेजिस्टर().
	 */
	अणु
	 .callback = video_detect_क्रमce_venकरोr,
	 .ident = "X360",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "SAMSUNG ELECTRONICS CO., LTD."),
		DMI_MATCH(DMI_PRODUCT_NAME, "X360"),
		DMI_MATCH(DMI_BOARD_NAME, "X360"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = video_detect_क्रमce_venकरोr,
	.ident = "Asus UL30VT",
	.matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK Computer Inc."),
		DMI_MATCH(DMI_PRODUCT_NAME, "UL30VT"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = video_detect_क्रमce_venकरोr,
	.ident = "Asus UL30A",
	.matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK Computer Inc."),
		DMI_MATCH(DMI_PRODUCT_NAME, "UL30A"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = video_detect_क्रमce_venकरोr,
	.ident = "GIGABYTE GB-BXBT-2807",
	.matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "GIGABYTE"),
		DMI_MATCH(DMI_PRODUCT_NAME, "GB-BXBT-2807"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = video_detect_क्रमce_venकरोr,
	.ident = "Sony VPCEH3U1E",
	.matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Sony Corporation"),
		DMI_MATCH(DMI_PRODUCT_NAME, "VPCEH3U1E"),
		पूर्ण,
	पूर्ण,

	/*
	 * These models have a working acpi_video backlight control, and using
	 * native backlight causes a regression where backlight करोes not work
	 * when userspace is not handling brightness key events. Disable
	 * native_backlight on these to fix this:
	 * https://bugzilla.kernel.org/show_bug.cgi?id=81691
	 */
	अणु
	 .callback = video_detect_क्रमce_video,
	 .ident = "ThinkPad T420",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
		DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad T420"),
		पूर्ण,
	पूर्ण,
	अणु
	 .callback = video_detect_क्रमce_video,
	 .ident = "ThinkPad T520",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
		DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad T520"),
		पूर्ण,
	पूर्ण,
	अणु
	 .callback = video_detect_क्रमce_video,
	 .ident = "ThinkPad X201s",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
		DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad X201s"),
		पूर्ण,
	पूर्ण,
	अणु
	 .callback = video_detect_क्रमce_video,
	 .ident = "ThinkPad X201T",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
		DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad X201T"),
		पूर्ण,
	पूर्ण,

	/* The native backlight controls करो not work on some older machines */
	अणु
	 /* https://bugs.मुक्तdesktop.org/show_bug.cgi?id=81515 */
	 .callback = video_detect_क्रमce_video,
	 .ident = "HP ENVY 15 Notebook",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
		DMI_MATCH(DMI_PRODUCT_NAME, "HP ENVY 15 Notebook PC"),
		पूर्ण,
	पूर्ण,
	अणु
	 .callback = video_detect_क्रमce_video,
	 .ident = "SAMSUNG 870Z5E/880Z5E/680Z5E",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "SAMSUNG ELECTRONICS CO., LTD."),
		DMI_MATCH(DMI_PRODUCT_NAME, "870Z5E/880Z5E/680Z5E"),
		पूर्ण,
	पूर्ण,
	अणु
	 .callback = video_detect_क्रमce_video,
	 .ident = "SAMSUNG 370R4E/370R4V/370R5E/3570RE/370R5V",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "SAMSUNG ELECTRONICS CO., LTD."),
		DMI_MATCH(DMI_PRODUCT_NAME,
			  "370R4E/370R4V/370R5E/3570RE/370R5V"),
		पूर्ण,
	पूर्ण,
	अणु
	 /* https://bugzilla.redhat.com/show_bug.cgi?id=1186097 */
	 .callback = video_detect_क्रमce_video,
	 .ident = "SAMSUNG 3570R/370R/470R/450R/510R/4450RV",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "SAMSUNG ELECTRONICS CO., LTD."),
		DMI_MATCH(DMI_PRODUCT_NAME,
			  "3570R/370R/470R/450R/510R/4450RV"),
		पूर्ण,
	पूर्ण,
	अणु
	 /* https://bugzilla.redhat.com/show_bug.cgi?id=1557060 */
	 .callback = video_detect_क्रमce_video,
	 .ident = "SAMSUNG 670Z5E",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "SAMSUNG ELECTRONICS CO., LTD."),
		DMI_MATCH(DMI_PRODUCT_NAME, "670Z5E"),
		पूर्ण,
	पूर्ण,
	अणु
	 /* https://bugzilla.redhat.com/show_bug.cgi?id=1094948 */
	 .callback = video_detect_क्रमce_video,
	 .ident = "SAMSUNG 730U3E/740U3E",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "SAMSUNG ELECTRONICS CO., LTD."),
		DMI_MATCH(DMI_PRODUCT_NAME, "730U3E/740U3E"),
		पूर्ण,
	पूर्ण,
	अणु
	 /* https://bugs.मुक्तdesktop.org/show_bug.cgi?id=87286 */
	 .callback = video_detect_क्रमce_video,
	 .ident = "SAMSUNG 900X3C/900X3D/900X3E/900X4C/900X4D",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "SAMSUNG ELECTRONICS CO., LTD."),
		DMI_MATCH(DMI_PRODUCT_NAME,
			  "900X3C/900X3D/900X3E/900X4C/900X4D"),
		पूर्ण,
	पूर्ण,
	अणु
	 /* https://bugzilla.redhat.com/show_bug.cgi?id=1272633 */
	 .callback = video_detect_क्रमce_video,
	 .ident = "Dell XPS14 L421X",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
		DMI_MATCH(DMI_PRODUCT_NAME, "XPS L421X"),
		पूर्ण,
	पूर्ण,
	अणु
	 /* https://bugzilla.redhat.com/show_bug.cgi?id=1163574 */
	 .callback = video_detect_क्रमce_video,
	 .ident = "Dell XPS15 L521X",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
		DMI_MATCH(DMI_PRODUCT_NAME, "XPS L521X"),
		पूर्ण,
	पूर्ण,
	अणु
	 /* https://bugzilla.kernel.org/show_bug.cgi?id=108971 */
	 .callback = video_detect_क्रमce_video,
	 .ident = "SAMSUNG 530U4E/540U4E",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "SAMSUNG ELECTRONICS CO., LTD."),
		DMI_MATCH(DMI_PRODUCT_NAME, "530U4E/540U4E"),
		पूर्ण,
	पूर्ण,
	/* https://bugs.launchpad.net/bugs/1894667 */
	अणु
	 .callback = video_detect_क्रमce_video,
	 .ident = "HP 635 Notebook",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
		DMI_MATCH(DMI_PRODUCT_NAME, "HP 635 Notebook PC"),
		पूर्ण,
	पूर्ण,

	/* Non win8 machines which need native backlight nevertheless */
	अणु
	 /* https://bugzilla.redhat.com/show_bug.cgi?id=1201530 */
	 .callback = video_detect_क्रमce_native,
	 .ident = "Lenovo Ideapad S405",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
		DMI_MATCH(DMI_BOARD_NAME, "Lenovo IdeaPad S405"),
		पूर्ण,
	पूर्ण,
	अणु
	 /* https://bugzilla.redhat.com/show_bug.cgi?id=1187004 */
	 .callback = video_detect_क्रमce_native,
	 .ident = "Lenovo Ideapad Z570",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
		DMI_MATCH(DMI_PRODUCT_NAME, "102434U"),
		पूर्ण,
	पूर्ण,
	अणु
	 .callback = video_detect_क्रमce_native,
	 .ident = "Lenovo E41-25",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
		DMI_MATCH(DMI_PRODUCT_NAME, "81FS"),
		पूर्ण,
	पूर्ण,
	अणु
	 .callback = video_detect_क्रमce_native,
	 .ident = "Lenovo E41-45",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
		DMI_MATCH(DMI_PRODUCT_NAME, "82BK"),
		पूर्ण,
	पूर्ण,
	अणु
	 /* https://bugzilla.redhat.com/show_bug.cgi?id=1217249 */
	 .callback = video_detect_क्रमce_native,
	 .ident = "Apple MacBook Pro 12,1",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Apple Inc."),
		DMI_MATCH(DMI_PRODUCT_NAME, "MacBookPro12,1"),
		पूर्ण,
	पूर्ण,
	अणु
	 .callback = video_detect_क्रमce_native,
	 .ident = "Dell Vostro V131",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
		DMI_MATCH(DMI_PRODUCT_NAME, "Vostro V131"),
		पूर्ण,
	पूर्ण,
	अणु
	 /* https://bugzilla.redhat.com/show_bug.cgi?id=1123661 */
	 .callback = video_detect_क्रमce_native,
	 .ident = "Dell XPS 17 L702X",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
		DMI_MATCH(DMI_PRODUCT_NAME, "Dell System XPS L702X"),
		पूर्ण,
	पूर्ण,
	अणु
	 .callback = video_detect_क्रमce_native,
	 .ident = "Dell Precision 7510",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
		DMI_MATCH(DMI_PRODUCT_NAME, "Precision 7510"),
		पूर्ण,
	पूर्ण,
	अणु
	 .callback = video_detect_क्रमce_native,
	 .ident = "Acer Aspire 5738z",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
		DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 5738"),
		DMI_MATCH(DMI_BOARD_NAME, "JV50"),
		पूर्ण,
	पूर्ण,
	अणु
	 /* https://bugzilla.kernel.org/show_bug.cgi?id=207835 */
	 .callback = video_detect_क्रमce_native,
	 .ident = "Acer TravelMate 5735Z",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
		DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate 5735Z"),
		DMI_MATCH(DMI_BOARD_NAME, "BA51_MV"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = video_detect_क्रमce_native,
	.ident = "ASUSTeK COMPUTER INC. GA401",
	.matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
		DMI_MATCH(DMI_PRODUCT_NAME, "GA401"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = video_detect_क्रमce_native,
	.ident = "ASUSTeK COMPUTER INC. GA502",
	.matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
		DMI_MATCH(DMI_PRODUCT_NAME, "GA502"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = video_detect_क्रमce_native,
	.ident = "ASUSTeK COMPUTER INC. GA503",
	.matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
		DMI_MATCH(DMI_PRODUCT_NAME, "GA503"),
		पूर्ण,
	पूर्ण,

	/*
	 * Desktops which falsely report a backlight and which our heuristics
	 * क्रम this करो not catch.
	 */
	अणु
	 .callback = video_detect_क्रमce_none,
	 .ident = "Dell OptiPlex 9020M",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
		DMI_MATCH(DMI_PRODUCT_NAME, "OptiPlex 9020M"),
		पूर्ण,
	पूर्ण,
	अणु
	 .callback = video_detect_क्रमce_none,
	 .ident = "MSI MS-7721",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "MSI"),
		DMI_MATCH(DMI_PRODUCT_NAME, "MS-7721"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

/* This uses a workqueue to aव्योम various locking ordering issues */
अटल व्योम acpi_video_backlight_notअगरy_work(काष्ठा work_काष्ठा *work)
अणु
	अगर (acpi_video_get_backlight_type() != acpi_backlight_video)
		acpi_video_unरेजिस्टर_backlight();
पूर्ण

अटल पूर्णांक acpi_video_backlight_notअगरy(काष्ठा notअगरier_block *nb,
				       अचिन्हित दीर्घ val, व्योम *bd)
अणु
	काष्ठा backlight_device *backlight = bd;

	/* A raw bl रेजिस्टरing may change video -> native */
	अगर (backlight->props.type == BACKLIGHT_RAW &&
	    val == BACKLIGHT_REGISTERED)
		schedule_work(&backlight_notअगरy_work);

	वापस NOTIFY_OK;
पूर्ण

/*
 * Determine which type of backlight पूर्णांकerface to use on this प्रणाली,
 * First check cmdline, then dmi quirks, then करो स्वतःdetect.
 *
 * The स्वतःdetect order is:
 * 1) Is the acpi-video backlight पूर्णांकerface supported ->
 *  no, use a venकरोr पूर्णांकerface
 * 2) Is this a win8 "ready" BIOS and करो we have a native पूर्णांकerface ->
 *  yes, use a native पूर्णांकerface
 * 3) Else use the acpi-video पूर्णांकerface
 *
 * Arguably the native on win8 check should be करोne first, but that would
 * be a behavior change, which may causes issues.
 */
क्रमागत acpi_backlight_type acpi_video_get_backlight_type(व्योम)
अणु
	अटल DEFINE_MUTEX(init_mutex);
	अटल bool init_करोne;
	अटल दीर्घ video_caps;

	/* Parse cmdline, dmi and acpi only once */
	mutex_lock(&init_mutex);
	अगर (!init_करोne) अणु
		acpi_video_parse_cmdline();
		dmi_check_प्रणाली(video_detect_dmi_table);
		acpi_walk_namespace(ACPI_TYPE_DEVICE, ACPI_ROOT_OBJECT,
				    ACPI_UINT32_MAX, find_video, शून्य,
				    &video_caps, शून्य);
		INIT_WORK(&backlight_notअगरy_work,
			  acpi_video_backlight_notअगरy_work);
		backlight_nb.notअगरier_call = acpi_video_backlight_notअगरy;
		backlight_nb.priority = 0;
		अगर (backlight_रेजिस्टर_notअगरier(&backlight_nb) == 0)
			backlight_notअगरier_रेजिस्टरed = true;
		init_करोne = true;
	पूर्ण
	mutex_unlock(&init_mutex);

	अगर (acpi_backlight_cmdline != acpi_backlight_undef)
		वापस acpi_backlight_cmdline;

	अगर (acpi_backlight_dmi != acpi_backlight_undef)
		वापस acpi_backlight_dmi;

	अगर (!(video_caps & ACPI_VIDEO_BACKLIGHT))
		वापस acpi_backlight_venकरोr;

	अगर (acpi_osi_is_win8() && backlight_device_get_by_type(BACKLIGHT_RAW))
		वापस acpi_backlight_native;

	वापस acpi_backlight_video;
पूर्ण
EXPORT_SYMBOL(acpi_video_get_backlight_type);

/*
 * Set the preferred backlight पूर्णांकerface type based on DMI info.
 * This function allows DMI blacklists to be implemented by बाह्यal
 * platक्रमm drivers instead of putting a big blacklist in video_detect.c
 */
व्योम acpi_video_set_dmi_backlight_type(क्रमागत acpi_backlight_type type)
अणु
	acpi_backlight_dmi = type;
	/* Remove acpi-video backlight पूर्णांकerface अगर it is no दीर्घer desired */
	अगर (acpi_video_get_backlight_type() != acpi_backlight_video)
		acpi_video_unरेजिस्टर_backlight();
पूर्ण
EXPORT_SYMBOL(acpi_video_set_dmi_backlight_type);

व्योम __निकास acpi_video_detect_निकास(व्योम)
अणु
	अगर (backlight_notअगरier_रेजिस्टरed)
		backlight_unरेजिस्टर_notअगरier(&backlight_nb);
पूर्ण
