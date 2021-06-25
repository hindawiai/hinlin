<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Touchscreen driver DMI based configuration code
 *
 * Copyright (c) 2017 Red Hat Inc.
 *
 * Red Hat authors:
 * Hans de Goede <hdegoede@redhat.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/device.h>
#समावेश <linux/dmi.h>
#समावेश <linux/efi_embedded_fw.h>
#समावेश <linux/i2c.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/property.h>
#समावेश <linux/माला.स>

काष्ठा ts_dmi_data अणु
	/* The EFI embedded-fw code expects this to be the first member! */
	काष्ठा efi_embedded_fw_desc embedded_fw;
	स्थिर अक्षर *acpi_name;
	स्थिर काष्ठा property_entry *properties;
पूर्ण;

/* NOTE: Please keep all entries sorted alphabetically */

अटल स्थिर काष्ठा property_entry chuwi_hi8_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1665),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1140),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl1680-chuwi-hi8.fw"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data chuwi_hi8_data = अणु
	.acpi_name      = "MSSL0001:00",
	.properties     = chuwi_hi8_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry chuwi_hi8_air_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1728),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1148),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl3676-chuwi-hi8-air.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data chuwi_hi8_air_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= chuwi_hi8_air_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry chuwi_hi8_pro_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-min-x", 6),
	PROPERTY_ENTRY_U32("touchscreen-min-y", 3),
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1728),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1148),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl3680-chuwi-hi8-pro.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data chuwi_hi8_pro_data = अणु
	.embedded_fw = अणु
		.name	= "silead/gsl3680-chuwi-hi8-pro.fw",
		.prefix = अणु 0xf0, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00 पूर्ण,
		.length	= 39864,
		.sha256	= अणु 0xc0, 0x88, 0xc5, 0xef, 0xd1, 0x70, 0x77, 0x59,
			    0x4e, 0xe9, 0xc4, 0xd8, 0x2e, 0xcd, 0xbf, 0x95,
			    0x32, 0xd9, 0x03, 0x28, 0x0d, 0x48, 0x9f, 0x92,
			    0x35, 0x37, 0xf6, 0x8b, 0x2a, 0xe4, 0x73, 0xff पूर्ण,
	पूर्ण,
	.acpi_name	= "MSSL1680:00",
	.properties	= chuwi_hi8_pro_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry chuwi_hi10_air_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1981),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1271),
	PROPERTY_ENTRY_U32("touchscreen-min-x", 99),
	PROPERTY_ENTRY_U32("touchscreen-min-y", 9),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_U32("touchscreen-fuzz-x", 5),
	PROPERTY_ENTRY_U32("touchscreen-fuzz-y", 4),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl1680-chuwi-hi10-air.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data chuwi_hi10_air_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= chuwi_hi10_air_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry chuwi_hi10_plus_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-min-x", 0),
	PROPERTY_ENTRY_U32("touchscreen-min-y", 5),
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1914),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1283),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl1680-chuwi-hi10plus.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data chuwi_hi10_plus_data = अणु
	.acpi_name      = "MSSL0017:00",
	.properties     = chuwi_hi10_plus_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry chuwi_hi10_pro_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-min-x", 8),
	PROPERTY_ENTRY_U32("touchscreen-min-y", 8),
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1912),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1272),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl1680-chuwi-hi10-pro.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data chuwi_hi10_pro_data = अणु
	.embedded_fw = अणु
		.name	= "silead/gsl1680-chuwi-hi10-pro.fw",
		.prefix = अणु 0xf0, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00 पूर्ण,
		.length	= 42504,
		.sha256	= अणु 0xdb, 0x92, 0x68, 0xa8, 0xdb, 0x81, 0x31, 0x00,
			    0x1f, 0x58, 0x89, 0xdb, 0x19, 0x1b, 0x15, 0x8c,
			    0x05, 0x14, 0xf4, 0x95, 0xba, 0x15, 0x45, 0x98,
			    0x42, 0xa3, 0xbb, 0x65, 0xe3, 0x30, 0xa5, 0x93 पूर्ण,
	पूर्ण,
	.acpi_name      = "MSSL1680:00",
	.properties     = chuwi_hi10_pro_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry chuwi_vi8_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-min-x", 4),
	PROPERTY_ENTRY_U32("touchscreen-min-y", 6),
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1724),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1140),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl3676-chuwi-vi8.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data chuwi_vi8_data = अणु
	.acpi_name      = "MSSL1680:00",
	.properties     = chuwi_vi8_props,
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data chuwi_vi8_plus_data = अणु
	.embedded_fw = अणु
		.name	= "chipone/icn8505-HAMP0002.fw",
		.prefix = अणु 0xb0, 0x07, 0x00, 0x00, 0xe4, 0x07, 0x00, 0x00 पूर्ण,
		.length	= 35012,
		.sha256	= अणु 0x93, 0xe5, 0x49, 0xe0, 0xb6, 0xa2, 0xb4, 0xb3,
			    0x88, 0x96, 0x34, 0x97, 0x5e, 0xa8, 0x13, 0x78,
			    0x72, 0x98, 0xb8, 0x29, 0xeb, 0x5c, 0xa7, 0xf1,
			    0x25, 0x13, 0x43, 0xf4, 0x30, 0x7c, 0xfc, 0x7c पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा property_entry chuwi_vi10_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-min-x", 0),
	PROPERTY_ENTRY_U32("touchscreen-min-y", 4),
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1858),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1280),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl3680-chuwi-vi10.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data chuwi_vi10_data = अणु
	.acpi_name      = "MSSL0002:00",
	.properties     = chuwi_vi10_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry chuwi_surbook_mini_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-min-x", 88),
	PROPERTY_ENTRY_U32("touchscreen-min-y", 13),
	PROPERTY_ENTRY_U32("touchscreen-size-x", 2040),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1524),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl1680-chuwi-surbook-mini.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-y"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data chuwi_surbook_mini_data = अणु
	.acpi_name      = "MSSL1680:00",
	.properties     = chuwi_surbook_mini_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry connect_tablet9_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-min-x", 9),
	PROPERTY_ENTRY_U32("touchscreen-min-y", 10),
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1664),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 880),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-y"),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl1680-connect-tablet9.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data connect_tablet9_data = अणु
	.acpi_name      = "MSSL1680:00",
	.properties     = connect_tablet9_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry cube_iwork8_air_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-min-x", 1),
	PROPERTY_ENTRY_U32("touchscreen-min-y", 3),
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1664),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 896),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl3670-cube-iwork8-air.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data cube_iwork8_air_data = अणु
	.embedded_fw = अणु
		.name	= "silead/gsl3670-cube-iwork8-air.fw",
		.prefix = अणु 0xf0, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00 पूर्ण,
		.length	= 38808,
		.sha256	= अणु 0xff, 0x62, 0x2d, 0xd1, 0x8a, 0x78, 0x04, 0x7b,
			    0x33, 0x06, 0xb0, 0x4f, 0x7f, 0x02, 0x08, 0x9c,
			    0x96, 0xd4, 0x9f, 0x04, 0xe1, 0x47, 0x25, 0x25,
			    0x60, 0x77, 0x41, 0x33, 0xeb, 0x12, 0x82, 0xfc पूर्ण,
	पूर्ण,
	.acpi_name	= "MSSL1680:00",
	.properties	= cube_iwork8_air_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry cube_knote_i1101_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-min-x", 20),
	PROPERTY_ENTRY_U32("touchscreen-min-y",  22),
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1961),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1513),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl3692-cube-knote-i1101.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data cube_knote_i1101_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= cube_knote_i1101_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry dexp_ursus_7w_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-size-x", 890),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 630),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl1686-dexp-ursus-7w.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data dexp_ursus_7w_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= dexp_ursus_7w_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry digma_citi_e200_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1980),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1500),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl1686-digma_citi_e200.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data digma_citi_e200_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= digma_citi_e200_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry estar_beauty_hd_props[] = अणु
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data estar_beauty_hd_data = अणु
	.acpi_name	= "GDIX1001:00",
	.properties	= estar_beauty_hd_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry gp_electronic_t701_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-size-x", 960),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 640),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-x"),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl1680-gp-electronic-t701.fw"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data gp_electronic_t701_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= gp_electronic_t701_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry irbis_tw90_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1720),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1138),
	PROPERTY_ENTRY_U32("touchscreen-min-x", 8),
	PROPERTY_ENTRY_U32("touchscreen-min-y", 14),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-y"),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl3680-irbis_tw90.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data irbis_tw90_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= irbis_tw90_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry irbis_tw118_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-min-x", 20),
	PROPERTY_ENTRY_U32("touchscreen-min-y", 30),
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1960),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1510),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl1680-irbis-tw118.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data irbis_tw118_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= irbis_tw118_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry itworks_tw891_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-min-x", 1),
	PROPERTY_ENTRY_U32("touchscreen-min-y", 5),
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1600),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 896),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-y"),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl3670-itworks-tw891.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data itworks_tw891_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= itworks_tw891_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry jumper_ezpad_6_pro_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1980),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1500),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl3692-jumper-ezpad-6-pro.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data jumper_ezpad_6_pro_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= jumper_ezpad_6_pro_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry jumper_ezpad_6_pro_b_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1980),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1500),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl3692-jumper-ezpad-6-pro-b.fw"),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-y"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data jumper_ezpad_6_pro_b_data = अणु
	.acpi_name      = "MSSL1680:00",
	.properties     = jumper_ezpad_6_pro_b_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry jumper_ezpad_6_m4_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-min-x", 35),
	PROPERTY_ENTRY_U32("touchscreen-min-y", 15),
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1950),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1525),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl3692-jumper-ezpad-6-m4.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data jumper_ezpad_6_m4_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= jumper_ezpad_6_m4_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry jumper_ezpad_7_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-min-x", 4),
	PROPERTY_ENTRY_U32("touchscreen-min-y", 10),
	PROPERTY_ENTRY_U32("touchscreen-size-x", 2044),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1526),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl3680-jumper-ezpad-7.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,stuck-controller-bug"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data jumper_ezpad_7_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= jumper_ezpad_7_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry jumper_ezpad_mini3_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-min-x", 23),
	PROPERTY_ENTRY_U32("touchscreen-min-y", 16),
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1700),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1138),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl3676-jumper-ezpad-mini3.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data jumper_ezpad_mini3_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= jumper_ezpad_mini3_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry mpman_converter9_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-min-x", 8),
	PROPERTY_ENTRY_U32("touchscreen-min-y", 8),
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1664),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 880),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-y"),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl1680-mpman-converter9.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data mpman_converter9_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= mpman_converter9_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry mpman_mpwin895cl_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-min-x", 3),
	PROPERTY_ENTRY_U32("touchscreen-min-y", 9),
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1728),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1150),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl3680-mpman-mpwin895cl.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data mpman_mpwin895cl_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= mpman_mpwin895cl_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry myria_my8307_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1720),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1140),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-x"),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-y"),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl1680-myria-my8307.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data myria_my8307_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= myria_my8307_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry onda_obook_20_plus_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1728),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1148),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-x"),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-y"),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl3676-onda-obook-20-plus.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data onda_obook_20_plus_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= onda_obook_20_plus_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry onda_v80_plus_v3_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-min-x", 22),
	PROPERTY_ENTRY_U32("touchscreen-min-y", 15),
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1698),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1140),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl3676-onda-v80-plus-v3.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data onda_v80_plus_v3_data = अणु
	.embedded_fw = अणु
		.name	= "silead/gsl3676-onda-v80-plus-v3.fw",
		.prefix = अणु 0xf0, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00 पूर्ण,
		.length	= 37224,
		.sha256	= अणु 0x8f, 0xbd, 0x8f, 0x0c, 0x6b, 0xba, 0x5b, 0xf5,
			    0xa3, 0xc7, 0xa3, 0xc0, 0x4f, 0xcd, 0xdf, 0x32,
			    0xcc, 0xe4, 0x70, 0xd6, 0x46, 0x9c, 0xd7, 0xa7,
			    0x4b, 0x82, 0x3f, 0xab, 0xc7, 0x90, 0xea, 0x23 पूर्ण,
	पूर्ण,
	.acpi_name	= "MSSL1680:00",
	.properties	= onda_v80_plus_v3_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry onda_v820w_32g_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1665),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1140),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl1680-onda-v820w-32g.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data onda_v820w_32g_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= onda_v820w_32g_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry onda_v891_v5_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1715),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1140),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-x"),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-y"),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_STRING("firmware-name",
			      "gsl3676-onda-v891-v5.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data onda_v891_v5_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= onda_v891_v5_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry onda_v891w_v1_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-min-x", 46),
	PROPERTY_ENTRY_U32("touchscreen-min-y",  8),
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1676),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1130),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl3680-onda-v891w-v1.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data onda_v891w_v1_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= onda_v891w_v1_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry onda_v891w_v3_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-min-x", 35),
	PROPERTY_ENTRY_U32("touchscreen-min-y", 15),
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1625),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1135),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl3676-onda-v891w-v3.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data onda_v891w_v3_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= onda_v891w_v3_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry pipo_w2s_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1660),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 880),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-x"),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl1680-pipo-w2s.fw"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data pipo_w2s_data = अणु
	.embedded_fw = अणु
		.name	= "silead/gsl1680-pipo-w2s.fw",
		.prefix = अणु 0xf0, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00 पूर्ण,
		.length	= 39072,
		.sha256	= अणु 0xd0, 0x58, 0xc4, 0x7d, 0x55, 0x2d, 0x62, 0x18,
			    0xd1, 0x6a, 0x71, 0x73, 0x0b, 0x3f, 0xbe, 0x60,
			    0xbb, 0x45, 0x8c, 0x52, 0x27, 0xb7, 0x18, 0xf4,
			    0x31, 0x00, 0x6a, 0x49, 0x76, 0xd8, 0x7c, 0xd3 पूर्ण,
	पूर्ण,
	.acpi_name	= "MSSL1680:00",
	.properties	= pipo_w2s_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry pipo_w11_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-min-x", 1),
	PROPERTY_ENTRY_U32("touchscreen-min-y", 15),
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1984),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1532),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl1680-pipo-w11.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data pipo_w11_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= pipo_w11_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry pov_mobii_wपूर्णांकab_p800w_v20_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-min-x", 32),
	PROPERTY_ENTRY_U32("touchscreen-min-y", 16),
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1692),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1146),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl3680-pov-mobii-wintab-p800w-v20.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data pov_mobii_wपूर्णांकab_p800w_v20_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= pov_mobii_wपूर्णांकab_p800w_v20_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry pov_mobii_wपूर्णांकab_p800w_v21_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-min-x", 1),
	PROPERTY_ENTRY_U32("touchscreen-min-y", 8),
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1794),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1148),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl3692-pov-mobii-wintab-p800w.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data pov_mobii_wपूर्णांकab_p800w_v21_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= pov_mobii_wपूर्णांकab_p800w_v21_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry pov_mobii_wपूर्णांकab_p1006w_v10_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-min-x", 1),
	PROPERTY_ENTRY_U32("touchscreen-min-y", 3),
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1984),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1520),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl3692-pov-mobii-wintab-p1006w-v10.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data pov_mobii_wपूर्णांकab_p1006w_v10_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= pov_mobii_wपूर्णांकab_p1006w_v10_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry predia_basic_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-min-x", 3),
	PROPERTY_ENTRY_U32("touchscreen-min-y", 10),
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1728),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1144),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl3680-predia-basic.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data predia_basic_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= predia_basic_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry schneider_sct101cपंचांग_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1715),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1140),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-x"),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-y"),
	PROPERTY_ENTRY_BOOL("touchscreen-swapped-x-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl1680-schneider-sct101ctm.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data schneider_sct101cपंचांग_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= schneider_sct101cपंचांग_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry techbite_arc_11_6_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-min-x", 5),
	PROPERTY_ENTRY_U32("touchscreen-min-y", 7),
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1981),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1270),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl1680-techbite-arc-11-6.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data techbite_arc_11_6_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= techbite_arc_11_6_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry teclast_tbook11_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-min-x", 8),
	PROPERTY_ENTRY_U32("touchscreen-min-y", 14),
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1916),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1264),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl3692-teclast-tbook11.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data teclast_tbook11_data = अणु
	.embedded_fw = अणु
		.name	= "silead/gsl3692-teclast-tbook11.fw",
		.prefix = अणु 0xf0, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00 पूर्ण,
		.length	= 43560,
		.sha256	= अणु 0x9d, 0xb0, 0x3d, 0xf1, 0x00, 0x3c, 0xb5, 0x25,
			    0x62, 0x8a, 0xa0, 0x93, 0x4b, 0xe0, 0x4e, 0x75,
			    0xd1, 0x27, 0xb1, 0x65, 0x3c, 0xba, 0xa5, 0x0f,
			    0xcd, 0xb4, 0xbe, 0x00, 0xbb, 0xf6, 0x43, 0x29 पूर्ण,
	पूर्ण,
	.acpi_name	= "MSSL1680:00",
	.properties	= teclast_tbook11_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry teclast_x3_plus_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1980),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1500),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl1680-teclast-x3-plus.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data teclast_x3_plus_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= teclast_x3_plus_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry teclast_x98plus2_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-size-x", 2048),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1280),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-x"),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl1686-teclast_x98plus2.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data teclast_x98plus2_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= teclast_x98plus2_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry trekstor_primebook_c11_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1970),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1530),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-y"),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl1680-trekstor-primebook-c11.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data trekstor_primebook_c11_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= trekstor_primebook_c11_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry trekstor_primebook_c13_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-size-x", 2624),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1920),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl1680-trekstor-primebook-c13.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data trekstor_primebook_c13_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= trekstor_primebook_c13_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry trekstor_primetab_t13b_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-size-x", 2500),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1900),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl1680-trekstor-primetab-t13b.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	PROPERTY_ENTRY_BOOL("touchscreen-inverted-y"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data trekstor_primetab_t13b_data = अणु
	.acpi_name  = "MSSL1680:00",
	.properties = trekstor_primetab_t13b_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry trekstor_surftab_twin_10_1_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-min-x", 20),
	PROPERTY_ENTRY_U32("touchscreen-min-y", 0),
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1890),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1280),
	PROPERTY_ENTRY_U32("touchscreen-inverted-y", 1),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl3670-surftab-twin-10-1-st10432-8.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data trekstor_surftab_twin_10_1_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= trekstor_surftab_twin_10_1_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry trekstor_surftab_wपूर्णांकron70_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-min-x", 12),
	PROPERTY_ENTRY_U32("touchscreen-min-y", 8),
	PROPERTY_ENTRY_U32("touchscreen-size-x", 884),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 632),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl1686-surftab-wintron70-st70416-6.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data trekstor_surftab_wपूर्णांकron70_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= trekstor_surftab_wपूर्णांकron70_props,
पूर्ण;

अटल स्थिर काष्ठा property_entry vinga_twizzle_j116_props[] = अणु
	PROPERTY_ENTRY_U32("touchscreen-size-x", 1920),
	PROPERTY_ENTRY_U32("touchscreen-size-y", 1280),
	PROPERTY_ENTRY_STRING("firmware-name", "gsl1680-vinga-twizzle_j116.fw"),
	PROPERTY_ENTRY_U32("silead,max-fingers", 10),
	PROPERTY_ENTRY_BOOL("silead,home-button"),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data vinga_twizzle_j116_data = अणु
	.acpi_name	= "MSSL1680:00",
	.properties	= vinga_twizzle_j116_props,
पूर्ण;

/* NOTE: Please keep this table sorted alphabetically */
स्थिर काष्ठा dmi_प्रणाली_id touchscreen_dmi_table[] = अणु
	अणु
		/* Chuwi Hi8 */
		.driver_data = (व्योम *)&chuwi_hi8_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ilife"),
			DMI_MATCH(DMI_PRODUCT_NAME, "S806"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Chuwi Hi8 (H1D_S806_206) */
		.driver_data = (व्योम *)&chuwi_hi8_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Insyde"),
			DMI_MATCH(DMI_PRODUCT_NAME, "BayTrail"),
			DMI_MATCH(DMI_BIOS_VERSION, "H1D_S806_206"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Chuwi Hi8 Air (CWI543) */
		.driver_data = (व्योम *)&chuwi_hi8_air_data,
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Default string"),
			DMI_MATCH(DMI_BOARD_NAME, "Cherry Trail CR"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Hi8 Air"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Chuwi Hi8 Pro (CWI513) */
		.driver_data = (व्योम *)&chuwi_hi8_pro_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Hampoo"),
			DMI_MATCH(DMI_PRODUCT_NAME, "X1D3_C806N"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Chuwi Hi10 Air */
		.driver_data = (व्योम *)&chuwi_hi10_air_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "CHUWI INNOVATION AND TECHNOLOGY(SHENZHEN)CO.LTD"),
			DMI_MATCH(DMI_BOARD_NAME, "Cherry Trail CR"),
			DMI_MATCH(DMI_PRODUCT_SKU, "P1W6_C109D_B"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Chuwi Hi10 Plus (CWI527) */
		.driver_data = (व्योम *)&chuwi_hi10_plus_data,
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Hampoo"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Hi10 plus tablet"),
			DMI_MATCH(DMI_BOARD_NAME, "Cherry Trail CR"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Chuwi Hi10 Prus (CWI597) */
		.driver_data = (व्योम *)&chuwi_hi10_pro_data,
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Hampoo"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Hi10 pro tablet"),
			DMI_MATCH(DMI_BOARD_NAME, "Cherry Trail CR"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Chuwi Vi8 (CWI506) */
		.driver_data = (व्योम *)&chuwi_vi8_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Insyde"),
			DMI_MATCH(DMI_PRODUCT_NAME, "i86"),
			DMI_MATCH(DMI_BIOS_VERSION, "CHUWI.D86JLBNR"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Chuwi Vi8 Plus (CWI519) */
		.driver_data = (व्योम *)&chuwi_vi8_plus_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Hampoo"),
			DMI_MATCH(DMI_PRODUCT_NAME, "D2D3_Vi8A1"),
			DMI_MATCH(DMI_BOARD_NAME, "Cherry Trail CR"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Chuwi Vi10 (CWI505) */
		.driver_data = (व्योम *)&chuwi_vi10_data,
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Hampoo"),
			DMI_MATCH(DMI_BOARD_NAME, "BYT-PF02"),
			DMI_MATCH(DMI_SYS_VENDOR, "ilife"),
			DMI_MATCH(DMI_PRODUCT_NAME, "S165"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Chuwi Surbook Mini (CWI540) */
		.driver_data = (व्योम *)&chuwi_surbook_mini_data,
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Hampoo"),
			DMI_MATCH(DMI_PRODUCT_NAME, "C3W6_AP108_4G"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Connect Tablet 9 */
		.driver_data = (व्योम *)&connect_tablet9_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Connect"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Tablet 9"),
		पूर्ण,
	पूर्ण,
	अणु
		/* CUBE iwork8 Air */
		.driver_data = (व्योम *)&cube_iwork8_air_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "cube"),
			DMI_MATCH(DMI_PRODUCT_NAME, "i1-TF"),
			DMI_MATCH(DMI_BOARD_NAME, "Cherry Trail CR"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Cube KNote i1101 */
		.driver_data = (व्योम *)&cube_knote_i1101_data,
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Hampoo"),
			DMI_MATCH(DMI_BOARD_NAME, "L1W6_I1101"),
			DMI_MATCH(DMI_SYS_VENDOR, "ALLDOCUBE"),
			DMI_MATCH(DMI_PRODUCT_NAME, "i1101"),
		पूर्ण,
	पूर्ण,
	अणु
		/* DEXP Ursus 7W */
		.driver_data = (व्योम *)&dexp_ursus_7w_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Insyde"),
			DMI_MATCH(DMI_PRODUCT_NAME, "7W"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Digma Citi E200 */
		.driver_data = (व्योम *)&digma_citi_e200_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Digma"),
			DMI_MATCH(DMI_PRODUCT_NAME, "CITI E200"),
			DMI_MATCH(DMI_BOARD_NAME, "Cherry Trail CR"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Estar Beauty HD (MID 7316R) */
		.driver_data = (व्योम *)&estar_beauty_hd_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Estar"),
			DMI_MATCH(DMI_PRODUCT_NAME, "eSTAR BEAUTY HD Intel Quad core"),
		पूर्ण,
	पूर्ण,
	अणु
		/* GP-electronic T701 */
		.driver_data = (व्योम *)&gp_electronic_t701_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Insyde"),
			DMI_MATCH(DMI_PRODUCT_NAME, "T701"),
			DMI_MATCH(DMI_BIOS_VERSION, "BYT70A.YNCHENG.WIN.007"),
		पूर्ण,
	पूर्ण,
	अणु
		/* I.T.Works TW701 (same hardware as the Trekstor ST70416-6) */
		.driver_data = (व्योम *)&trekstor_surftab_wपूर्णांकron70_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Insyde"),
			DMI_MATCH(DMI_PRODUCT_NAME, "i71c"),
			DMI_MATCH(DMI_BIOS_VERSION, "itWORKS.G.WI71C.JGBMRB"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Irbis TW90 */
		.driver_data = (व्योम *)&irbis_tw90_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "IRBIS"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TW90"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Irbis TW118 */
		.driver_data = (व्योम *)&irbis_tw118_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "IRBIS"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TW118"),
		पूर्ण,
	पूर्ण,
	अणु
		/* I.T.Works TW891 */
		.driver_data = (व्योम *)&itworks_tw891_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "To be filled by O.E.M."),
			DMI_MATCH(DMI_PRODUCT_NAME, "TW891"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Jumper EZpad 6 Pro */
		.driver_data = (व्योम *)&jumper_ezpad_6_pro_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Jumper"),
			DMI_MATCH(DMI_PRODUCT_NAME, "EZpad"),
			DMI_MATCH(DMI_BIOS_VERSION, "5.12"),
			/* Above matches are too generic, add bios-date match */
			DMI_MATCH(DMI_BIOS_DATE, "08/18/2017"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Jumper EZpad 6 Pro B */
		.driver_data = (व्योम *)&jumper_ezpad_6_pro_b_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Jumper"),
			DMI_MATCH(DMI_PRODUCT_NAME, "EZpad"),
			DMI_MATCH(DMI_BIOS_VERSION, "5.12"),
			/* Above matches are too generic, add bios-date match */
			DMI_MATCH(DMI_BIOS_DATE, "04/24/2018"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Jumper EZpad 6 m4 */
		.driver_data = (व्योम *)&jumper_ezpad_6_m4_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "jumper"),
			DMI_MATCH(DMI_PRODUCT_NAME, "EZpad"),
			/* Jumper8.S106x.A00C.1066 with the version dropped */
			DMI_MATCH(DMI_BIOS_VERSION, "Jumper8.S106x"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Jumper EZpad 7 */
		.driver_data = (व्योम *)&jumper_ezpad_7_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Jumper"),
			DMI_MATCH(DMI_PRODUCT_NAME, "EZpad"),
			/* Jumper12x.WJ2012.bsBKRCP05 with the version dropped */
			DMI_MATCH(DMI_BIOS_VERSION, "Jumper12x.WJ2012.bsBKRCP"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Jumper EZpad mini3 */
		.driver_data = (व्योम *)&jumper_ezpad_mini3_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Insyde"),
			/* jumperx.T87.KFBNEEA02 with the version-nr dropped */
			DMI_MATCH(DMI_BIOS_VERSION, "jumperx.T87.KFBNEEA"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Mediacom WinPad 7.0 W700 (same hw as Wपूर्णांकron surftab 7") */
		.driver_data = (व्योम *)&trekstor_surftab_wपूर्णांकron70_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "MEDIACOM"),
			DMI_MATCH(DMI_PRODUCT_NAME, "WinPad 7 W10 - WPW700"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Mediacom Flexbook Edge 11 (same hw as TS Primebook C11) */
		.driver_data = (व्योम *)&trekstor_primebook_c11_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "MEDIACOM"),
			DMI_MATCH(DMI_PRODUCT_NAME, "FlexBook edge11 - M-FBE11"),
		पूर्ण,
	पूर्ण,
	अणु
		/* MP Man Converter 9 */
		.driver_data = (व्योम *)&mpman_converter9_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "MPMAN"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Converter9"),
		पूर्ण,
	पूर्ण,
	अणु
		/* MP Man MPWIN895CL */
		.driver_data = (व्योम *)&mpman_mpwin895cl_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "MPMAN"),
			DMI_MATCH(DMI_PRODUCT_NAME, "MPWIN8900CL"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Myria MY8307 */
		.driver_data = (व्योम *)&myria_my8307_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Complet Electro Serv"),
			DMI_MATCH(DMI_PRODUCT_NAME, "MY8307"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Onda oBook 20 Plus */
		.driver_data = (व्योम *)&onda_obook_20_plus_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ONDA"),
			DMI_MATCH(DMI_PRODUCT_NAME, "OBOOK 20 PLUS"),
		पूर्ण,
	पूर्ण,
	अणु
		/* ONDA V80 plus v3 (P80PSBG9V3A01501) */
		.driver_data = (व्योम *)&onda_v80_plus_v3_data,
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "ONDA"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "V80 PLUS")
		पूर्ण,
	पूर्ण,
	अणु
		/* ONDA V820w DualOS */
		.driver_data = (व्योम *)&onda_v820w_32g_data,
		.matches = अणु
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "ONDA"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "V820w DualOS")
		पूर्ण,
	पूर्ण,
	अणु
		/* ONDA V891 v5 */
		.driver_data = (व्योम *)&onda_v891_v5_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ONDA"),
			DMI_MATCH(DMI_PRODUCT_NAME, "ONDA Tablet"),
			DMI_MATCH(DMI_BIOS_VERSION, "ONDA.D869CJABNRBA06"),
		पूर्ण,
	पूर्ण,
	अणु
		/* ONDA V891w revision P891WBEBV1B00 aka v1 */
		.driver_data = (व्योम *)&onda_v891w_v1_data,
		.matches = अणु
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "ONDA"),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "ONDA Tablet"),
			DMI_EXACT_MATCH(DMI_BOARD_VERSION, "V001"),
			/* Exact match, dअगरferent versions need dअगरferent fw */
			DMI_EXACT_MATCH(DMI_BIOS_VERSION, "ONDA.W89EBBN08"),
		पूर्ण,
	पूर्ण,
	अणु
		/* ONDA V891w Dual OS P891DCF2V1A01274 64GB */
		.driver_data = (व्योम *)&onda_v891w_v3_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Insyde"),
			DMI_MATCH(DMI_PRODUCT_NAME, "ONDA Tablet"),
			DMI_MATCH(DMI_BIOS_VERSION, "ONDA.D890HBBNR0A"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Pipo W2S */
		.driver_data = (व्योम *)&pipo_w2s_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "PIPO"),
			DMI_MATCH(DMI_PRODUCT_NAME, "W2S"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Pipo W11 */
		.driver_data = (व्योम *)&pipo_w11_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "PIPO"),
			DMI_MATCH(DMI_PRODUCT_NAME, "To be filled by O.E.M."),
			/* Above matches are too generic, add bios-ver match */
			DMI_MATCH(DMI_BIOS_VERSION, "JS-BI-10.6-SF133GR300-GA55B-024-F"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Ployer Momo7w (same hardware as the Trekstor ST70416-6) */
		.driver_data = (व्योम *)&trekstor_surftab_wपूर्णांकron70_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Shenzhen PLOYER"),
			DMI_MATCH(DMI_PRODUCT_NAME, "MOMO7W"),
			/* Exact match, dअगरferent versions need dअगरferent fw */
			DMI_MATCH(DMI_BIOS_VERSION, "MOMO.G.WI71C.MABMRBA02"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Poपूर्णांक of View mobii wपूर्णांकab p800w (v2.0) */
		.driver_data = (व्योम *)&pov_mobii_wपूर्णांकab_p800w_v20_data,
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "AMI Corporation"),
			DMI_MATCH(DMI_BOARD_NAME, "Aptio CRB"),
			DMI_MATCH(DMI_BIOS_VERSION, "3BAIR1014"),
			/* Above matches are too generic, add bios-date match */
			DMI_MATCH(DMI_BIOS_DATE, "10/24/2014"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Predia Basic tablet) */
		.driver_data = (व्योम *)&predia_basic_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Insyde"),
			DMI_MATCH(DMI_PRODUCT_NAME, "CherryTrail"),
			/* Above matches are too generic, add bios-version match */
			DMI_MATCH(DMI_BIOS_VERSION, "Mx.WT107.KUBNGEA"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Poपूर्णांक of View mobii wपूर्णांकab p800w (v2.1) */
		.driver_data = (व्योम *)&pov_mobii_wपूर्णांकab_p800w_v21_data,
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "AMI Corporation"),
			DMI_MATCH(DMI_BOARD_NAME, "Aptio CRB"),
			DMI_MATCH(DMI_BIOS_VERSION, "3BAIR1013"),
			/* Above matches are too generic, add bios-date match */
			DMI_MATCH(DMI_BIOS_DATE, "08/22/2014"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Poपूर्णांक of View mobii wपूर्णांकab p1006w (v1.0) */
		.driver_data = (व्योम *)&pov_mobii_wपूर्णांकab_p1006w_v10_data,
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Insyde"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "BayTrail"),
			/* Note 105b is Foxcon's USB/PCI venकरोr id */
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "105B"),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "0E57"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Schneider SCT101CTM */
		.driver_data = (व्योम *)&schneider_sct101cपंचांग_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Default string"),
			DMI_MATCH(DMI_PRODUCT_NAME, "SCT101CTM"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Techbite Arc 11.6 */
		.driver_data = (व्योम *)&techbite_arc_11_6_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "mPTech"),
			DMI_MATCH(DMI_PRODUCT_NAME, "techBite Arc 11.6"),
			DMI_MATCH(DMI_BOARD_NAME, "G8316_272B"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Teclast Tbook 11 */
		.driver_data = (व्योम *)&teclast_tbook11_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "TECLAST"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TbooK 11"),
			DMI_MATCH(DMI_PRODUCT_SKU, "E5A6_A1"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Teclast X3 Plus */
		.driver_data = (व्योम *)&teclast_x3_plus_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "TECLAST"),
			DMI_MATCH(DMI_PRODUCT_NAME, "X3 Plus"),
			DMI_MATCH(DMI_BOARD_NAME, "X3 Plus"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Teclast X98 Plus II */
		.driver_data = (व्योम *)&teclast_x98plus2_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "TECLAST"),
			DMI_MATCH(DMI_PRODUCT_NAME, "X98 Plus II"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Trekstor Primebook C11 */
		.driver_data = (व्योम *)&trekstor_primebook_c11_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "TREKSTOR"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Primebook C11"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Trekstor Primebook C11B (same touchscreen as the C11) */
		.driver_data = (व्योम *)&trekstor_primebook_c11_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "TREKSTOR"),
			DMI_MATCH(DMI_PRODUCT_NAME, "PRIMEBOOK C11B"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Trekstor Primebook C13 */
		.driver_data = (व्योम *)&trekstor_primebook_c13_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "TREKSTOR"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Primebook C13"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Trekstor Primetab T13B */
		.driver_data = (व्योम *)&trekstor_primetab_t13b_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "TREKSTOR"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Primetab T13B"),
		पूर्ण,
	पूर्ण,
	अणु
		/* TrekStor SurfTab twin 10.1 ST10432-8 */
		.driver_data = (व्योम *)&trekstor_surftab_twin_10_1_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "TrekStor"),
			DMI_MATCH(DMI_PRODUCT_NAME, "SurfTab twin 10.1"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Trekstor Surftab Wपूर्णांकron 7.0 ST70416-6 */
		.driver_data = (व्योम *)&trekstor_surftab_wपूर्णांकron70_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Insyde"),
			DMI_MATCH(DMI_PRODUCT_NAME, "ST70416-6"),
			/* Exact match, dअगरferent versions need dअगरferent fw */
			DMI_MATCH(DMI_BIOS_VERSION, "TREK.G.WI71C.JGBMRBA04"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Trekstor Surftab Wपूर्णांकron 7.0 ST70416-6, newer BIOS */
		.driver_data = (व्योम *)&trekstor_surftab_wपूर्णांकron70_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "TrekStor"),
			DMI_MATCH(DMI_PRODUCT_NAME, "SurfTab wintron 7.0 ST70416-6"),
			/* Exact match, dअगरferent versions need dअगरferent fw */
			DMI_MATCH(DMI_BIOS_VERSION, "TREK.G.WI71C.JGBMRBA05"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Trekstor Yourbook C11B (same touchscreen as the Primebook C11) */
		.driver_data = (व्योम *)&trekstor_primebook_c11_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "TREKSTOR"),
			DMI_MATCH(DMI_PRODUCT_NAME, "YOURBOOK C11B"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Vinga Twizzle J116 */
		.driver_data = (व्योम *)&vinga_twizzle_j116_data,
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "VINGA Twizzle J116"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Yours Y8W81, same हाल and touchscreen as Chuwi Vi8 */
		.driver_data = (व्योम *)&chuwi_vi8_data,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "YOURS"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Y8W81"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ts_dmi_data *ts_data;

अटल व्योम ts_dmi_add_props(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	पूर्णांक error;

	अगर (has_acpi_companion(dev) &&
	    !म_भेदन(ts_data->acpi_name, client->name, I2C_NAME_SIZE)) अणु
		error = device_create_managed_software_node(dev, ts_data->properties, शून्य);
		अगर (error)
			dev_err(dev, "failed to add properties: %d\n", error);
	पूर्ण
पूर्ण

अटल पूर्णांक ts_dmi_notअगरier_call(काष्ठा notअगरier_block *nb,
				अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा device *dev = data;
	काष्ठा i2c_client *client;

	चयन (action) अणु
	हाल BUS_NOTIFY_ADD_DEVICE:
		client = i2c_verअगरy_client(dev);
		अगर (client)
			ts_dmi_add_props(client);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block ts_dmi_notअगरier = अणु
	.notअगरier_call = ts_dmi_notअगरier_call,
पूर्ण;

अटल पूर्णांक __init ts_dmi_init(व्योम)
अणु
	स्थिर काष्ठा dmi_प्रणाली_id *dmi_id;
	पूर्णांक error;

	dmi_id = dmi_first_match(touchscreen_dmi_table);
	अगर (!dmi_id)
		वापस 0; /* Not an error */

	ts_data = dmi_id->driver_data;
	/* Some dmi table entries only provide an efi_embedded_fw_desc */
	अगर (!ts_data->properties)
		वापस 0;

	error = bus_रेजिस्टर_notअगरier(&i2c_bus_type, &ts_dmi_notअगरier);
	अगर (error)
		pr_err("%s: failed to register i2c bus notifier: %d\n",
			__func__, error);

	वापस error;
पूर्ण

/*
 * We are रेजिस्टरing out notअगरier after i2c core is initialized and i2c bus
 * itself is पढ़ोy (which happens at postcore initcall level), but beक्रमe
 * ACPI starts क्रमागतerating devices (at subsys initcall level).
 */
arch_initcall(ts_dmi_init);
