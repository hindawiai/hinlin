<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */

/*
 * Quirks क्रम AMD IOMMU
 *
 * Copyright (C) 2019 Kai-Heng Feng <kai.heng.feng@canonical.com>
 */

#अगर_घोषित CONFIG_DMI
#समावेश <linux/dmi.h>

#समावेश "amd_iommu.h"

#घोषणा IVHD_SPECIAL_IOAPIC		1

काष्ठा ivrs_quirk_entry अणु
	u8 id;
	u16 devid;
पूर्ण;

क्रमागत अणु
	DELL_INSPIRON_7375 = 0,
	DELL_LATITUDE_5495,
	LENOVO_IDEAPAD_330S_15ARR,
पूर्ण;

अटल स्थिर काष्ठा ivrs_quirk_entry ivrs_ioapic_quirks[][3] __initस्थिर = अणु
	/* ivrs_ioapic[4]=00:14.0 ivrs_ioapic[5]=00:00.2 */
	[DELL_INSPIRON_7375] = अणु
		अणु .id = 4, .devid = 0xa0 पूर्ण,
		अणु .id = 5, .devid = 0x2 पूर्ण,
		अणुपूर्ण
	पूर्ण,
	/* ivrs_ioapic[4]=00:14.0 */
	[DELL_LATITUDE_5495] = अणु
		अणु .id = 4, .devid = 0xa0 पूर्ण,
		अणुपूर्ण
	पूर्ण,
	/* ivrs_ioapic[32]=00:14.0 */
	[LENOVO_IDEAPAD_330S_15ARR] = अणु
		अणु .id = 32, .devid = 0xa0 पूर्ण,
		अणुपूर्ण
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक __init ivrs_ioapic_quirk_cb(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	स्थिर काष्ठा ivrs_quirk_entry *i;

	क्रम (i = d->driver_data; i->id != 0 && i->devid != 0; i++)
		add_special_device(IVHD_SPECIAL_IOAPIC, i->id, (u16 *)&i->devid, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id ivrs_quirks[] __initस्थिर = अणु
	अणु
		.callback = ivrs_ioapic_quirk_cb,
		.ident = "Dell Inspiron 7375",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 7375"),
		पूर्ण,
		.driver_data = (व्योम *)&ivrs_ioapic_quirks[DELL_INSPIRON_7375],
	पूर्ण,
	अणु
		.callback = ivrs_ioapic_quirk_cb,
		.ident = "Dell Latitude 5495",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Latitude 5495"),
		पूर्ण,
		.driver_data = (व्योम *)&ivrs_ioapic_quirks[DELL_LATITUDE_5495],
	पूर्ण,
	अणु
		/*
		 * Acer Aspire A315-41 requires the very same workaround as
		 * Dell Latitude 5495
		 */
		.callback = ivrs_ioapic_quirk_cb,
		.ident = "Acer Aspire A315-41",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire A315-41"),
		पूर्ण,
		.driver_data = (व्योम *)&ivrs_ioapic_quirks[DELL_LATITUDE_5495],
	पूर्ण,
	अणु
		.callback = ivrs_ioapic_quirk_cb,
		.ident = "Lenovo ideapad 330S-15ARR",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_NAME, "81FB"),
		पूर्ण,
		.driver_data = (व्योम *)&ivrs_ioapic_quirks[LENOVO_IDEAPAD_330S_15ARR],
	पूर्ण,
	अणुपूर्ण
पूर्ण;

व्योम __init amd_iommu_apply_ivrs_quirks(व्योम)
अणु
	dmi_check_प्रणाली(ivrs_quirks);
पूर्ण
#पूर्ण_अगर
