<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
// Copyright(c) 2021 Intel Corporation.

/*
 * Soundwire DMI quirks
 */

#समावेश <linux/device.h>
#समावेश <linux/dmi.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश "bus.h"

काष्ठा adr_remap अणु
	u64 adr;
	u64 remapped_adr;
पूर्ण;

/*
 * HP Spectre 360 Convertible devices करो not expose the correct _ADR
 * in the DSDT.
 * Remap the bad _ADR values to the ones reported by hardware
 */
अटल स्थिर काष्ठा adr_remap hp_spectre_360[] = अणु
	अणु
		0x000010025D070100,
		0x000020025D071100
	पूर्ण,
	अणु
		0x000110025d070100,
		0x000120025D130800
	पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
 * The initial version of the Dell SKU 0A3E did not expose the devices
 * on the correct links.
 */
अटल स्थिर काष्ठा adr_remap dell_sku_0A3E[] = अणु
	/* rt715 on link0 */
	अणु
		0x00020025d071100,
		0x00021025d071500
	पूर्ण,
	/* rt711 on link1 */
	अणु
		0x000120025d130800,
		0x000120025d071100,
	पूर्ण,
	/* rt1308 on link2 */
	अणु
		0x000220025d071500,
		0x000220025d130800
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id adr_remap_quirk_table[] = अणु
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "HP"),
			DMI_MATCH(DMI_PRODUCT_NAME, "HP Spectre x360 Convertible"),
		पूर्ण,
		.driver_data = (व्योम *)hp_spectre_360,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc"),
			DMI_EXACT_MATCH(DMI_PRODUCT_SKU, "0A3E")
		पूर्ण,
		.driver_data = (व्योम *)dell_sku_0A3E,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

u64 sdw_dmi_override_adr(काष्ठा sdw_bus *bus, u64 addr)
अणु
	स्थिर काष्ठा dmi_प्रणाली_id *dmi_id;

	/* check अगर any address remap quirk applies */
	dmi_id = dmi_first_match(adr_remap_quirk_table);
	अगर (dmi_id) अणु
		काष्ठा adr_remap *map = dmi_id->driver_data;

		क्रम (map = dmi_id->driver_data; map->adr; map++) अणु
			अगर (map->adr == addr) अणु
				dev_dbg(bus->dev, "remapped _ADR 0x%llx as 0x%llx\n",
					addr, map->remapped_adr);
				addr = map->remapped_adr;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस addr;
पूर्ण
