<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright 2018 Hans de Goede <hdegoede@redhat.com>
 */

#समावेश <linux/dmi.h>
#समावेश <linux/mod_devicetable.h>
#समावेश "core.h"
#समावेश "common.h"
#समावेश "brcm_hw_ids.h"

/* The DMI data never changes so we can use a अटल buf क्रम this */
अटल अक्षर dmi_board_type[128];

काष्ठा brcmf_dmi_data अणु
	u32 chip;
	u32 chiprev;
	स्थिर अक्षर *board_type;
पूर्ण;

/* NOTE: Please keep all entries sorted alphabetically */

अटल स्थिर काष्ठा brcmf_dmi_data acepc_t8_data = अणु
	BRCM_CC_4345_CHIP_ID, 6, "acepc-t8"
पूर्ण;

अटल स्थिर काष्ठा brcmf_dmi_data gpd_win_pocket_data = अणु
	BRCM_CC_4356_CHIP_ID, 2, "gpd-win-pocket"
पूर्ण;

अटल स्थिर काष्ठा brcmf_dmi_data jumper_ezpad_mini3_data = अणु
	BRCM_CC_43430_CHIP_ID, 0, "jumper-ezpad-mini3"
पूर्ण;

अटल स्थिर काष्ठा brcmf_dmi_data meegopad_t08_data = अणु
	BRCM_CC_43340_CHIP_ID, 2, "meegopad-t08"
पूर्ण;

अटल स्थिर काष्ठा brcmf_dmi_data pov_tab_p1006w_data = अणु
	BRCM_CC_43340_CHIP_ID, 2, "pov-tab-p1006w-data"
पूर्ण;

अटल स्थिर काष्ठा brcmf_dmi_data predia_basic_data = अणु
	BRCM_CC_43341_CHIP_ID, 2, "predia-basic"
पूर्ण;

/* Note the Voyo winpad A15 tablet uses the same Ampak AP6330 module, with the
 * exact same nvram file as the Prowise-PT301 tablet. Since the nvram क्रम the
 * Prowise-PT301 is alपढ़ोy in linux-firmware we just poपूर्णांक to that here.
 */
अटल स्थिर काष्ठा brcmf_dmi_data voyo_winpad_a15_data = अणु
	BRCM_CC_4330_CHIP_ID, 4, "Prowise-PT301"
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id dmi_platक्रमm_data[] = अणु
	अणु
		/* ACEPC T8 Cherry Trail Z8350 mini PC */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "To be filled by O.E.M."),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "Cherry Trail CR"),
			DMI_EXACT_MATCH(DMI_PRODUCT_SKU, "T8"),
			/* also match on somewhat unique bios-version */
			DMI_EXACT_MATCH(DMI_BIOS_VERSION, "1.000"),
		पूर्ण,
		.driver_data = (व्योम *)&acepc_t8_data,
	पूर्ण,
	अणु
		/* ACEPC T11 Cherry Trail Z8350 mini PC, same wअगरi as the T8 */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "To be filled by O.E.M."),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "Cherry Trail CR"),
			DMI_EXACT_MATCH(DMI_PRODUCT_SKU, "T11"),
			/* also match on somewhat unique bios-version */
			DMI_EXACT_MATCH(DMI_BIOS_VERSION, "1.000"),
		पूर्ण,
		.driver_data = (व्योम *)&acepc_t8_data,
	पूर्ण,
	अणु
		/* Match क्रम the GPDwin which unक्रमtunately uses somewhat
		 * generic dmi strings, which is why we test क्रम 4 strings.
		 * Comparing against 23 other byt/cht boards, board_venकरोr
		 * and board_name are unique to the GPDwin, where as only one
		 * other board has the same board_serial and 3 others have
		 * the same शेष product_name. Also the GPDwin is the
		 * only device to have both board_ and product_name not set.
		 */
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "AMI Corporation"),
			DMI_MATCH(DMI_BOARD_NAME, "Default string"),
			DMI_MATCH(DMI_BOARD_SERIAL, "Default string"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Default string"),
		पूर्ण,
		.driver_data = (व्योम *)&gpd_win_pocket_data,
	पूर्ण,
	अणु
		/* Jumper EZpad mini3 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Insyde"),
			DMI_MATCH(DMI_PRODUCT_NAME, "CherryTrail"),
			/* jumperx.T87.KFBNEEA02 with the version-nr dropped */
			DMI_MATCH(DMI_BIOS_VERSION, "jumperx.T87.KFBNEEA"),
		पूर्ण,
		.driver_data = (व्योम *)&jumper_ezpad_mini3_data,
	पूर्ण,
	अणु
		/* Meegopad T08 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Default string"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Default string"),
			DMI_MATCH(DMI_BOARD_NAME, "T3 MRD"),
			DMI_MATCH(DMI_BOARD_VERSION, "V1.1"),
		पूर्ण,
		.driver_data = (व्योम *)&meegopad_t08_data,
	पूर्ण,
	अणु
		/* Poपूर्णांक of View TAB-P1006W-232 */
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Insyde"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "BayTrail"),
			/* Note 105b is Foxcon's USB/PCI venकरोr id */
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "105B"),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "0E57"),
		पूर्ण,
		.driver_data = (व्योम *)&pov_tab_p1006w_data,
	पूर्ण,
	अणु
		/* Predia Basic tablet (+ with keyboard करोck) */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Insyde"),
			DMI_MATCH(DMI_PRODUCT_NAME, "CherryTrail"),
			/* Mx.WT107.KUBNGEA02 with the version-nr dropped */
			DMI_MATCH(DMI_BIOS_VERSION, "Mx.WT107.KUBNGEA"),
		पूर्ण,
		.driver_data = (व्योम *)&predia_basic_data,
	पूर्ण,
	अणु
		/* Voyo winpad A15 tablet */
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "AMI Corporation"),
			DMI_MATCH(DMI_BOARD_NAME, "Aptio CRB"),
			/* Above strings are too generic, also match on BIOS date */
			DMI_MATCH(DMI_BIOS_DATE, "11/20/2014"),
		पूर्ण,
		.driver_data = (व्योम *)&voyo_winpad_a15_data,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

व्योम brcmf_dmi_probe(काष्ठा brcmf_mp_device *settings, u32 chip, u32 chiprev)
अणु
	स्थिर काष्ठा dmi_प्रणाली_id *match;
	स्थिर काष्ठा brcmf_dmi_data *data;
	स्थिर अक्षर *sys_venकरोr;
	स्थिर अक्षर *product_name;

	/* Some models have DMI strings which are too generic, e.g.
	 * "Default string", we use a quirk table क्रम these.
	 */
	क्रम (match = dmi_first_match(dmi_platक्रमm_data);
	     match;
	     match = dmi_first_match(match + 1)) अणु
		data = match->driver_data;

		अगर (data->chip == chip && data->chiprev == chiprev) अणु
			settings->board_type = data->board_type;
			वापस;
		पूर्ण
	पूर्ण

	/* Not found in the quirk-table, use sys_venकरोr-product_name */
	sys_venकरोr = dmi_get_प्रणाली_info(DMI_SYS_VENDOR);
	product_name = dmi_get_प्रणाली_info(DMI_PRODUCT_NAME);
	अगर (sys_venकरोr && product_name) अणु
		snम_लिखो(dmi_board_type, माप(dmi_board_type), "%s-%s",
			 sys_venकरोr, product_name);
		settings->board_type = dmi_board_type;
	पूर्ण
पूर्ण
