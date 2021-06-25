<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2018 Intel Corporation
 */

#समावेश <linux/dmi.h>

#समावेश "intel_display_types.h"
#समावेश "intel_quirks.h"

/*
 * Some machines (Lenovo U160) करो not work with SSC on LVDS क्रम some reason
 */
अटल व्योम quirk_ssc_क्रमce_disable(काष्ठा drm_i915_निजी *i915)
अणु
	i915->quirks |= QUIRK_LVDS_SSC_DISABLE;
	drm_info(&i915->drm, "applying lvds SSC disable quirk\n");
पूर्ण

/*
 * A machine (e.g. Acer Aspire 5734Z) may need to invert the panel backlight
 * brightness value
 */
अटल व्योम quirk_invert_brightness(काष्ठा drm_i915_निजी *i915)
अणु
	i915->quirks |= QUIRK_INVERT_BRIGHTNESS;
	drm_info(&i915->drm, "applying inverted panel brightness quirk\n");
पूर्ण

/* Some VBT's incorrectly indicate no backlight is present */
अटल व्योम quirk_backlight_present(काष्ठा drm_i915_निजी *i915)
अणु
	i915->quirks |= QUIRK_BACKLIGHT_PRESENT;
	drm_info(&i915->drm, "applying backlight present quirk\n");
पूर्ण

/* Toshiba Satellite P50-C-18C requires T12 delay to be min 800ms
 * which is 300 ms greater than eDP spec T12 min.
 */
अटल व्योम quirk_increase_t12_delay(काष्ठा drm_i915_निजी *i915)
अणु
	i915->quirks |= QUIRK_INCREASE_T12_DELAY;
	drm_info(&i915->drm, "Applying T12 delay quirk\n");
पूर्ण

/*
 * GeminiLake NUC HDMI outमाला_दो require additional off समय
 * this allows the onboard reसमयr to correctly sync to संकेत
 */
अटल व्योम quirk_increase_ddi_disabled_समय(काष्ठा drm_i915_निजी *i915)
अणु
	i915->quirks |= QUIRK_INCREASE_DDI_DISABLED_TIME;
	drm_info(&i915->drm, "Applying Increase DDI Disabled quirk\n");
पूर्ण

काष्ठा पूर्णांकel_quirk अणु
	पूर्णांक device;
	पूर्णांक subप्रणाली_venकरोr;
	पूर्णांक subप्रणाली_device;
	व्योम (*hook)(काष्ठा drm_i915_निजी *i915);
पूर्ण;

/* For प्रणालीs that करोn't have a meaningful PCI subdevice/subvenकरोr ID */
काष्ठा पूर्णांकel_dmi_quirk अणु
	व्योम (*hook)(काष्ठा drm_i915_निजी *i915);
	स्थिर काष्ठा dmi_प्रणाली_id (*dmi_id_list)[];
पूर्ण;

अटल पूर्णांक पूर्णांकel_dmi_reverse_brightness(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	DRM_INFO("Backlight polarity reversed on %s\n", id->ident);
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_dmi_quirk पूर्णांकel_dmi_quirks[] = अणु
	अणु
		.dmi_id_list = &(स्थिर काष्ठा dmi_प्रणाली_id[]) अणु
			अणु
				.callback = पूर्णांकel_dmi_reverse_brightness,
				.ident = "NCR Corporation",
				.matches = अणुDMI_MATCH(DMI_SYS_VENDOR, "NCR Corporation"),
					    DMI_MATCH(DMI_PRODUCT_NAME, ""),
				पूर्ण,
			पूर्ण,
			अणु
				.callback = पूर्णांकel_dmi_reverse_brightness,
				.ident = "Thundersoft TST178 tablet",
				/* DMI strings are too generic, also match on BIOS date */
				.matches = अणुDMI_EXACT_MATCH(DMI_BOARD_VENDOR, "AMI Corporation"),
					    DMI_EXACT_MATCH(DMI_BOARD_NAME, "Aptio CRB"),
					    DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "To be filled by O.E.M."),
					    DMI_EXACT_MATCH(DMI_BIOS_DATE, "04/15/2014"),
				पूर्ण,
			पूर्ण,
			अणु पूर्ण  /* terminating entry */
		पूर्ण,
		.hook = quirk_invert_brightness,
	पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकel_quirk पूर्णांकel_quirks[] = अणु
	/* Lenovo U160 cannot use SSC on LVDS */
	अणु 0x0046, 0x17aa, 0x3920, quirk_ssc_क्रमce_disable पूर्ण,

	/* Sony Vaio Y cannot use SSC on LVDS */
	अणु 0x0046, 0x104d, 0x9076, quirk_ssc_क्रमce_disable पूर्ण,

	/* Acer Aspire 5734Z must invert backlight brightness */
	अणु 0x2a42, 0x1025, 0x0459, quirk_invert_brightness पूर्ण,

	/* Acer/eMachines G725 */
	अणु 0x2a42, 0x1025, 0x0210, quirk_invert_brightness पूर्ण,

	/* Acer/eMachines e725 */
	अणु 0x2a42, 0x1025, 0x0212, quirk_invert_brightness पूर्ण,

	/* Acer/Packard Bell NCL20 */
	अणु 0x2a42, 0x1025, 0x034b, quirk_invert_brightness पूर्ण,

	/* Acer Aspire 4736Z */
	अणु 0x2a42, 0x1025, 0x0260, quirk_invert_brightness पूर्ण,

	/* Acer Aspire 5336 */
	अणु 0x2a42, 0x1025, 0x048a, quirk_invert_brightness पूर्ण,

	/* Acer C720 and C720P Chromebooks (Celeron 2955U) have backlights */
	अणु 0x0a06, 0x1025, 0x0a11, quirk_backlight_present पूर्ण,

	/* Acer C720 Chromebook (Core i3 4005U) */
	अणु 0x0a16, 0x1025, 0x0a11, quirk_backlight_present पूर्ण,

	/* Apple Macbook 2,1 (Core 2 T7400) */
	अणु 0x27a2, 0x8086, 0x7270, quirk_backlight_present पूर्ण,

	/* Apple Macbook 4,1 */
	अणु 0x2a02, 0x106b, 0x00a1, quirk_backlight_present पूर्ण,

	/* Toshiba CB35 Chromebook (Celeron 2955U) */
	अणु 0x0a06, 0x1179, 0x0a88, quirk_backlight_present पूर्ण,

	/* HP Chromebook 14 (Celeron 2955U) */
	अणु 0x0a06, 0x103c, 0x21ed, quirk_backlight_present पूर्ण,

	/* Dell Chromebook 11 */
	अणु 0x0a06, 0x1028, 0x0a35, quirk_backlight_present पूर्ण,

	/* Dell Chromebook 11 (2015 version) */
	अणु 0x0a16, 0x1028, 0x0a35, quirk_backlight_present पूर्ण,

	/* Toshiba Satellite P50-C-18C */
	अणु 0x191B, 0x1179, 0xF840, quirk_increase_t12_delay पूर्ण,

	/* GeminiLake NUC */
	अणु 0x3185, 0x8086, 0x2072, quirk_increase_ddi_disabled_समय पूर्ण,
	अणु 0x3184, 0x8086, 0x2072, quirk_increase_ddi_disabled_समय पूर्ण,
	/* ASRock ITX*/
	अणु 0x3185, 0x1849, 0x2212, quirk_increase_ddi_disabled_समय पूर्ण,
	अणु 0x3184, 0x1849, 0x2212, quirk_increase_ddi_disabled_समय पूर्ण,
पूर्ण;

व्योम पूर्णांकel_init_quirks(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा pci_dev *d = to_pci_dev(i915->drm.dev);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(पूर्णांकel_quirks); i++) अणु
		काष्ठा पूर्णांकel_quirk *q = &पूर्णांकel_quirks[i];

		अगर (d->device == q->device &&
		    (d->subप्रणाली_venकरोr == q->subप्रणाली_venकरोr ||
		     q->subप्रणाली_venकरोr == PCI_ANY_ID) &&
		    (d->subप्रणाली_device == q->subप्रणाली_device ||
		     q->subप्रणाली_device == PCI_ANY_ID))
			q->hook(i915);
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(पूर्णांकel_dmi_quirks); i++) अणु
		अगर (dmi_check_प्रणाली(*पूर्णांकel_dmi_quirks[i].dmi_id_list) != 0)
			पूर्णांकel_dmi_quirks[i].hook(i915);
	पूर्ण
पूर्ण
