<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * drm_panel_orientation_quirks.c -- Quirks क्रम non-normal panel orientation
 *
 * Copyright (C) 2017 Hans de Goede <hdegoede@redhat.com>
 *
 * Note the quirks in this file are shared with fbdev/efअगरb and as such
 * must not depend on other drm code.
 */

#समावेश <linux/dmi.h>
#समावेश <linux/module.h>
#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_utils.h>

#अगर_घोषित CONFIG_DMI

/*
 * Some x86 clamshell design devices use portrait tablet screens and a display
 * engine which cannot rotate in hardware, so we need to rotate the fbcon to
 * compensate. Unक्रमtunately these (cheap) devices also typically have quite
 * generic DMI data, so we match on a combination of DMI data, screen resolution
 * and a list of known BIOS dates to aव्योम false positives.
 */

काष्ठा drm_dmi_panel_orientation_data अणु
	पूर्णांक width;
	पूर्णांक height;
	स्थिर अक्षर * स्थिर *bios_dates;
	पूर्णांक orientation;
पूर्ण;

अटल स्थिर काष्ठा drm_dmi_panel_orientation_data asus_t100ha = अणु
	.width = 800,
	.height = 1280,
	.orientation = DRM_MODE_PANEL_ORIENTATION_LEFT_UP,
पूर्ण;

अटल स्थिर काष्ठा drm_dmi_panel_orientation_data gpd_micropc = अणु
	.width = 720,
	.height = 1280,
	.bios_dates = (स्थिर अक्षर * स्थिर [])अणु "04/26/2019",
		शून्य पूर्ण,
	.orientation = DRM_MODE_PANEL_ORIENTATION_RIGHT_UP,
पूर्ण;

अटल स्थिर काष्ठा drm_dmi_panel_orientation_data gpd_pocket = अणु
	.width = 1200,
	.height = 1920,
	.bios_dates = (स्थिर अक्षर * स्थिर [])अणु "05/26/2017", "06/28/2017",
		"07/05/2017", "08/07/2017", शून्य पूर्ण,
	.orientation = DRM_MODE_PANEL_ORIENTATION_RIGHT_UP,
पूर्ण;

अटल स्थिर काष्ठा drm_dmi_panel_orientation_data gpd_pocket2 = अणु
	.width = 1200,
	.height = 1920,
	.bios_dates = (स्थिर अक्षर * स्थिर [])अणु "06/28/2018", "08/28/2018",
		"12/07/2018", शून्य पूर्ण,
	.orientation = DRM_MODE_PANEL_ORIENTATION_RIGHT_UP,
पूर्ण;

अटल स्थिर काष्ठा drm_dmi_panel_orientation_data gpd_win = अणु
	.width = 720,
	.height = 1280,
	.bios_dates = (स्थिर अक्षर * स्थिर [])अणु
		"10/25/2016", "11/18/2016", "12/23/2016", "12/26/2016",
		"02/21/2017", "03/20/2017", "05/25/2017", शून्य पूर्ण,
	.orientation = DRM_MODE_PANEL_ORIENTATION_RIGHT_UP,
पूर्ण;

अटल स्थिर काष्ठा drm_dmi_panel_orientation_data gpd_win2 = अणु
	.width = 720,
	.height = 1280,
	.bios_dates = (स्थिर अक्षर * स्थिर [])अणु
		"12/07/2017", "05/24/2018", "06/29/2018", शून्य पूर्ण,
	.orientation = DRM_MODE_PANEL_ORIENTATION_RIGHT_UP,
पूर्ण;

अटल स्थिर काष्ठा drm_dmi_panel_orientation_data itworks_tw891 = अणु
	.width = 800,
	.height = 1280,
	.bios_dates = (स्थिर अक्षर * स्थिर [])अणु "10/16/2015", शून्य पूर्ण,
	.orientation = DRM_MODE_PANEL_ORIENTATION_RIGHT_UP,
पूर्ण;

अटल स्थिर काष्ठा drm_dmi_panel_orientation_data onegx1_pro = अणु
	.width = 1200,
	.height = 1920,
	.bios_dates = (स्थिर अक्षर * स्थिर [])अणु "12/17/2020", शून्य पूर्ण,
	.orientation = DRM_MODE_PANEL_ORIENTATION_RIGHT_UP,
पूर्ण;

अटल स्थिर काष्ठा drm_dmi_panel_orientation_data lcd720x1280_rightside_up = अणु
	.width = 720,
	.height = 1280,
	.orientation = DRM_MODE_PANEL_ORIENTATION_RIGHT_UP,
पूर्ण;

अटल स्थिर काष्ठा drm_dmi_panel_orientation_data lcd800x1280_rightside_up = अणु
	.width = 800,
	.height = 1280,
	.orientation = DRM_MODE_PANEL_ORIENTATION_RIGHT_UP,
पूर्ण;

अटल स्थिर काष्ठा drm_dmi_panel_orientation_data lcd1200x1920_rightside_up = अणु
	.width = 1200,
	.height = 1920,
	.orientation = DRM_MODE_PANEL_ORIENTATION_RIGHT_UP,
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id orientation_data[] = अणु
	अणु	/* Acer One 10 (S1003) */
		.matches = अणु
		  DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Acer"),
		  DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "One S1003"),
		पूर्ण,
		.driver_data = (व्योम *)&lcd800x1280_rightside_up,
	पूर्ण, अणु	/* Asus T100HA */
		.matches = अणु
		  DMI_EXACT_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
		  DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "T100HAN"),
		पूर्ण,
		.driver_data = (व्योम *)&asus_t100ha,
	पूर्ण, अणु	/* Asus T101HA */
		.matches = अणु
		  DMI_EXACT_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
		  DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "T101HA"),
		पूर्ण,
		.driver_data = (व्योम *)&lcd800x1280_rightside_up,
	पूर्ण, अणु	/* Asus T103HAF */
		.matches = अणु
		  DMI_EXACT_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
		  DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "T103HAF"),
		पूर्ण,
		.driver_data = (व्योम *)&lcd800x1280_rightside_up,
	पूर्ण, अणु	/* GPD MicroPC (generic strings, also match on bios date) */
		.matches = अणु
		  DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Default string"),
		  DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Default string"),
		  DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "Default string"),
		  DMI_EXACT_MATCH(DMI_BOARD_NAME, "Default string"),
		पूर्ण,
		.driver_data = (व्योम *)&gpd_micropc,
	पूर्ण, अणु	/* GPD MicroPC (later BIOS versions with proper DMI strings) */
		.matches = अणु
		  DMI_EXACT_MATCH(DMI_SYS_VENDOR, "GPD"),
		  DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "MicroPC"),
		पूर्ण,
		.driver_data = (व्योम *)&lcd720x1280_rightside_up,
	पूर्ण, अणु	/*
		 * GPD Pocket, note that the the DMI data is less generic then
		 * it seems, devices with a board-venकरोr of "AMI Corporation"
		 * are quite rare, as are devices which have both board- *and*
		 * product-id set to "Default String"
		 */
		.matches = अणु
		  DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "AMI Corporation"),
		  DMI_EXACT_MATCH(DMI_BOARD_NAME, "Default string"),
		  DMI_EXACT_MATCH(DMI_BOARD_SERIAL, "Default string"),
		  DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Default string"),
		पूर्ण,
		.driver_data = (व्योम *)&gpd_pocket,
	पूर्ण, अणु	/* GPD Pocket 2 (generic strings, also match on bios date) */
		.matches = अणु
		  DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Default string"),
		  DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Default string"),
		  DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "Default string"),
		  DMI_EXACT_MATCH(DMI_BOARD_NAME, "Default string"),
		पूर्ण,
		.driver_data = (व्योम *)&gpd_pocket2,
	पूर्ण, अणु	/* GPD Win (same note on DMI match as GPD Pocket) */
		.matches = अणु
		  DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "AMI Corporation"),
		  DMI_EXACT_MATCH(DMI_BOARD_NAME, "Default string"),
		  DMI_EXACT_MATCH(DMI_BOARD_SERIAL, "Default string"),
		  DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Default string"),
		पूर्ण,
		.driver_data = (व्योम *)&gpd_win,
	पूर्ण, अणु	/* GPD Win 2 (too generic strings, also match on bios date) */
		.matches = अणु
		  DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Default string"),
		  DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Default string"),
		  DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "Default string"),
		  DMI_EXACT_MATCH(DMI_BOARD_NAME, "Default string"),
		पूर्ण,
		.driver_data = (व्योम *)&gpd_win2,
	पूर्ण, अणु	/* I.T.Works TW891 */
		.matches = अणु
		  DMI_EXACT_MATCH(DMI_SYS_VENDOR, "To be filled by O.E.M."),
		  DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "TW891"),
		  DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "To be filled by O.E.M."),
		  DMI_EXACT_MATCH(DMI_BOARD_NAME, "TW891"),
		पूर्ण,
		.driver_data = (व्योम *)&itworks_tw891,
	पूर्ण, अणु	/*
		 * Lenovo Ideapad Miix 310 laptop, only some production batches
		 * have a portrait screen, the resolution checks makes the quirk
		 * apply only to those batches.
		 */
		.matches = अणु
		  DMI_EXACT_MATCH(DMI_SYS_VENDOR, "LENOVO"),
		  DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "80SG"),
		  DMI_EXACT_MATCH(DMI_PRODUCT_VERSION, "MIIX 310-10ICR"),
		पूर्ण,
		.driver_data = (व्योम *)&lcd800x1280_rightside_up,
	पूर्ण, अणु	/* Lenovo Ideapad Miix 320 */
		.matches = अणु
		  DMI_EXACT_MATCH(DMI_SYS_VENDOR, "LENOVO"),
		  DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "80XF"),
		  DMI_EXACT_MATCH(DMI_PRODUCT_VERSION, "Lenovo MIIX 320-10ICR"),
		पूर्ण,
		.driver_data = (व्योम *)&lcd800x1280_rightside_up,
	पूर्ण, अणु	/* Lenovo Ideapad D330 */
		.matches = अणु
		  DMI_EXACT_MATCH(DMI_SYS_VENDOR, "LENOVO"),
		  DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "81H3"),
		  DMI_EXACT_MATCH(DMI_PRODUCT_VERSION, "Lenovo ideapad D330-10IGM"),
		पूर्ण,
		.driver_data = (व्योम *)&lcd1200x1920_rightside_up,
	पूर्ण, अणु	/* OneGX1 Pro */
		.matches = अणु
		  DMI_EXACT_MATCH(DMI_SYS_VENDOR, "SYSTEM_MANUFACTURER"),
		  DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "SYSTEM_PRODUCT_NAME"),
		  DMI_EXACT_MATCH(DMI_PRODUCT_VERSION, "Default string"),
		पूर्ण,
		.driver_data = (व्योम *)&onegx1_pro,
	पूर्ण, अणु	/* VIOS LTH17 */
		.matches = अणु
		  DMI_EXACT_MATCH(DMI_SYS_VENDOR, "VIOS"),
		  DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "LTH17"),
		पूर्ण,
		.driver_data = (व्योम *)&lcd800x1280_rightside_up,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

/**
 * drm_get_panel_orientation_quirk - Check क्रम panel orientation quirks
 * @width: width in pixels of the panel
 * @height: height in pixels of the panel
 *
 * This function checks क्रम platक्रमm specअगरic (e.g. DMI based) quirks
 * providing info on panel_orientation क्रम प्रणालीs where this cannot be
 * probed from the hard-/firm-ware. To aव्योम false-positive this function
 * takes the panel resolution as argument and checks that against the
 * resolution expected by the quirk-table entry.
 *
 * Note this function is also used outside of the drm-subsys, by क्रम example
 * the efअगरb code. Because of this this function माला_लो compiled पूर्णांकo its own
 * kernel-module when built as a module.
 *
 * Returns:
 * A DRM_MODE_PANEL_ORIENTATION_* value अगर there is a quirk क्रम this प्रणाली,
 * or DRM_MODE_PANEL_ORIENTATION_UNKNOWN अगर there is no quirk.
 */
पूर्णांक drm_get_panel_orientation_quirk(पूर्णांक width, पूर्णांक height)
अणु
	स्थिर काष्ठा dmi_प्रणाली_id *match;
	स्थिर काष्ठा drm_dmi_panel_orientation_data *data;
	स्थिर अक्षर *bios_date;
	पूर्णांक i;

	क्रम (match = dmi_first_match(orientation_data);
	     match;
	     match = dmi_first_match(match + 1)) अणु
		data = match->driver_data;

		अगर (data->width != width ||
		    data->height != height)
			जारी;

		अगर (!data->bios_dates)
			वापस data->orientation;

		bios_date = dmi_get_प्रणाली_info(DMI_BIOS_DATE);
		अगर (!bios_date)
			जारी;

		i = match_string(data->bios_dates, -1, bios_date);
		अगर (i >= 0)
			वापस data->orientation;
	पूर्ण

	वापस DRM_MODE_PANEL_ORIENTATION_UNKNOWN;
पूर्ण
EXPORT_SYMBOL(drm_get_panel_orientation_quirk);

#अन्यथा

/* There are no quirks क्रम non x86 devices yet */
पूर्णांक drm_get_panel_orientation_quirk(पूर्णांक width, पूर्णांक height)
अणु
	वापस DRM_MODE_PANEL_ORIENTATION_UNKNOWN;
पूर्ण
EXPORT_SYMBOL(drm_get_panel_orientation_quirk);

#पूर्ण_अगर

MODULE_LICENSE("Dual MIT/GPL");
