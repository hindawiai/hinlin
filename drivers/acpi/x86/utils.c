<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * X86 ACPI Utility Functions
 *
 * Copyright (C) 2017 Hans de Goede <hdegoede@redhat.com>
 *
 * Based on various non upstream patches to support the CHT Whiskey Cove PMIC:
 * Copyright (C) 2013-2015 Intel Corporation. All rights reserved.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश "../internal.h"

/*
 * Some ACPI devices are hidden (status == 0x0) in recent BIOS-es because
 * some recent Winकरोws drivers bind to one device but poke at multiple
 * devices at the same समय, so the others get hidden.
 *
 * Some BIOS-es (temporarily) hide specअगरic APCI devices to work around Winकरोws
 * driver bugs. We use DMI matching to match known हालs of this.
 *
 * We work around this by always reporting ACPI_STA_DEFAULT क्रम these
 * devices. Note this MUST only be करोne क्रम devices where this is safe.
 *
 * This क्रमcing of devices to be present is limited to specअगरic CPU (SoC)
 * models both to aव्योम potentially causing trouble on other models and
 * because some HIDs are re-used on dअगरferent SoCs क्रम completely
 * dअगरferent devices.
 */
काष्ठा always_present_id अणु
	काष्ठा acpi_device_id hid[2];
	काष्ठा x86_cpu_id cpu_ids[2];
	काष्ठा dmi_प्रणाली_id dmi_ids[2]; /* Optional */
	स्थिर अक्षर *uid;
पूर्ण;

#घोषणा X86_MATCH(model)	X86_MATCH_INTEL_FAM6_MODEL(model, शून्य)

#घोषणा ENTRY(hid, uid, cpu_models, dmi...) अणु				\
	अणु अणु hid, पूर्ण, अणुपूर्ण पूर्ण,						\
	अणु cpu_models, अणुपूर्ण पूर्ण,						\
	अणु अणु .matches = dmi पूर्ण, अणुपूर्ण पूर्ण,					\
	uid,								\
पूर्ण

अटल स्थिर काष्ठा always_present_id always_present_ids[] = अणु
	/*
	 * Bay / Cherry Trail PWM directly poked by GPU driver in win10,
	 * but Linux uses a separate PWM driver, harmless अगर not used.
	 */
	ENTRY("80860F09", "1", X86_MATCH(ATOM_SILVERMONT), अणुपूर्ण),
	ENTRY("80862288", "1", X86_MATCH(ATOM_AIRMONT), अणुपूर्ण),

	/* Lenovo Yoga Book uses PWM2 क्रम keyboard backlight control */
	ENTRY("80862289", "2", X86_MATCH(ATOM_AIRMONT), अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Lenovo YB1-X9"),
		पूर्ण),
	/*
	 * The INT0002 device is necessary to clear wakeup पूर्णांकerrupt sources
	 * on Cherry Trail devices, without it we get nobody cared IRQ msgs.
	 */
	ENTRY("INT0002", "1", X86_MATCH(ATOM_AIRMONT), अणुपूर्ण),
	/*
	 * On the Dell Venue 11 Pro 7130 and 7139, the DSDT hides
	 * the touchscreen ACPI device until a certain समय
	 * after _SB.PCI0.GFX0.LCD.LCD1._ON माला_लो called has passed
	 * *and* _STA has been called at least 3 बार since.
	 */
	ENTRY("SYNA7500", "1", X86_MATCH(HASWELL_L), अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
		DMI_MATCH(DMI_PRODUCT_NAME, "Venue 11 Pro 7130"),
	      पूर्ण),
	ENTRY("SYNA7500", "1", X86_MATCH(HASWELL_L), अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
		DMI_MATCH(DMI_PRODUCT_NAME, "Venue 11 Pro 7139"),
	      पूर्ण),

	/*
	 * The GPD win BIOS dated 20170221 has disabled the accelerometer, the
	 * drivers someबार cause crashes under Winकरोws and this is how the
	 * manufacturer has solved this :| Note that the the DMI data is less
	 * generic then it seems, a board_venकरोr of "AMI Corporation" is quite
	 * rare and a board_name of "Default String" also is rare.
	 *
	 * Unक्रमtunately the GPD pocket also uses these strings and its BIOS
	 * was copy-pasted from the GPD win, so it has a disabled KIOX000A
	 * node which we should not enable, thus we also check the BIOS date.
	 */
	ENTRY("KIOX000A", "1", X86_MATCH(ATOM_AIRMONT), अणु
		DMI_MATCH(DMI_BOARD_VENDOR, "AMI Corporation"),
		DMI_MATCH(DMI_BOARD_NAME, "Default string"),
		DMI_MATCH(DMI_PRODUCT_NAME, "Default string"),
		DMI_MATCH(DMI_BIOS_DATE, "02/21/2017")
	      पूर्ण),
	ENTRY("KIOX000A", "1", X86_MATCH(ATOM_AIRMONT), अणु
		DMI_MATCH(DMI_BOARD_VENDOR, "AMI Corporation"),
		DMI_MATCH(DMI_BOARD_NAME, "Default string"),
		DMI_MATCH(DMI_PRODUCT_NAME, "Default string"),
		DMI_MATCH(DMI_BIOS_DATE, "03/20/2017")
	      पूर्ण),
	ENTRY("KIOX000A", "1", X86_MATCH(ATOM_AIRMONT), अणु
		DMI_MATCH(DMI_BOARD_VENDOR, "AMI Corporation"),
		DMI_MATCH(DMI_BOARD_NAME, "Default string"),
		DMI_MATCH(DMI_PRODUCT_NAME, "Default string"),
		DMI_MATCH(DMI_BIOS_DATE, "05/25/2017")
	      पूर्ण),
पूर्ण;

bool acpi_device_always_present(काष्ठा acpi_device *adev)
अणु
	bool ret = false;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(always_present_ids); i++) अणु
		अगर (acpi_match_device_ids(adev, always_present_ids[i].hid))
			जारी;

		अगर (!adev->pnp.unique_id ||
		    म_भेद(adev->pnp.unique_id, always_present_ids[i].uid))
			जारी;

		अगर (!x86_match_cpu(always_present_ids[i].cpu_ids))
			जारी;

		अगर (always_present_ids[i].dmi_ids[0].matches[0].slot &&
		    !dmi_check_प्रणाली(always_present_ids[i].dmi_ids))
			जारी;

		ret = true;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
