<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * soc-acpi-पूर्णांकel-cml-match.c - tables and support क्रम CML ACPI क्रमागतeration.
 *
 * Copyright (c) 2019, Intel Corporation.
 *
 */

#समावेश <sound/soc-acpi.h>
#समावेश <sound/soc-acpi-पूर्णांकel-match.h>

अटल काष्ठा snd_soc_acpi_codecs rt1011_spk_codecs = अणु
	.num_codecs = 1,
	.codecs = अणु"10EC1011"पूर्ण
पूर्ण;

अटल काष्ठा snd_soc_acpi_codecs rt1015_spk_codecs = अणु
	.num_codecs = 1,
	.codecs = अणु"10EC1015"पूर्ण
पूर्ण;

अटल काष्ठा snd_soc_acpi_codecs max98357a_spk_codecs = अणु
	.num_codecs = 1,
	.codecs = अणु"MX98357A"पूर्ण
पूर्ण;

अटल काष्ठा snd_soc_acpi_codecs max98390_spk_codecs = अणु
	.num_codecs = 1,
	.codecs = अणु"MX98390"पूर्ण
पूर्ण;

/*
 * The order of the three entries with .id = "10EC5682" matters
 * here, because DSDT tables expose an ACPI HID क्रम the MAX98357A
 * speaker amplअगरier which is not populated on the board.
 */
काष्ठा snd_soc_acpi_mach snd_soc_acpi_पूर्णांकel_cml_machines[] = अणु
	अणु
		.id = "10EC5682",
		.drv_name = "cml_rt1011_rt5682",
		.machine_quirk = snd_soc_acpi_codec_list,
		.quirk_data = &rt1011_spk_codecs,
		.sof_fw_filename = "sof-cml.ri",
		.sof_tplg_filename = "sof-cml-rt1011-rt5682.tplg",
	पूर्ण,
	अणु
		.id = "10EC5682",
		.drv_name = "cml_rt1015_rt5682",
		.machine_quirk = snd_soc_acpi_codec_list,
		.quirk_data = &rt1015_spk_codecs,
		.sof_fw_filename = "sof-cml.ri",
		.sof_tplg_filename = "sof-cml-rt1011-rt5682.tplg",
	पूर्ण,
	अणु
		.id = "10EC5682",
		.drv_name = "sof_rt5682",
		.machine_quirk = snd_soc_acpi_codec_list,
		.quirk_data = &max98357a_spk_codecs,
		.sof_fw_filename = "sof-cml.ri",
		.sof_tplg_filename = "sof-cml-rt5682-max98357a.tplg",
	पूर्ण,
	अणु
		.id = "10EC5682",
		.drv_name = "sof_rt5682",
		.sof_fw_filename = "sof-cml.ri",
		.sof_tplg_filename = "sof-cml-rt5682.tplg",
	पूर्ण,
	अणु
		.id = "DLGS7219",
		.drv_name = "cml_da7219_max98357a",
		.machine_quirk = snd_soc_acpi_codec_list,
		.quirk_data = &max98357a_spk_codecs,
		.sof_fw_filename = "sof-cml.ri",
		.sof_tplg_filename = "sof-cml-da7219-max98357a.tplg",
	पूर्ण,
	अणु
		.id = "DLGS7219",
		.drv_name = "cml_da7219_max98357a",
		.machine_quirk = snd_soc_acpi_codec_list,
		.quirk_data = &max98390_spk_codecs,
		.sof_fw_filename = "sof-cml.ri",
		.sof_tplg_filename = "sof-cml-da7219-max98390.tplg",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(snd_soc_acpi_पूर्णांकel_cml_machines);

अटल स्थिर काष्ठा snd_soc_acpi_endpoपूर्णांक single_endpoपूर्णांक = अणु
	.num = 0,
	.aggregated = 0,
	.group_position = 0,
	.group_id = 0,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_endpoपूर्णांक spk_l_endpoपूर्णांक = अणु
	.num = 0,
	.aggregated = 1,
	.group_position = 0,
	.group_id = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_endpoपूर्णांक spk_r_endpoपूर्णांक = अणु
	.num = 0,
	.aggregated = 1,
	.group_position = 1,
	.group_id = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_adr_device rt700_1_adr[] = अणु
	अणु
		.adr = 0x000110025D070000,
		.num_endpoपूर्णांकs = 1,
		.endpoपूर्णांकs = &single_endpoपूर्णांक,
		.name_prefix = "rt700"
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_link_adr cml_rvp[] = अणु
	अणु
		.mask = BIT(1),
		.num_adr = ARRAY_SIZE(rt700_1_adr),
		.adr_d = rt700_1_adr,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_adr_device rt711_0_adr[] = अणु
	अणु
		.adr = 0x000020025D071100,
		.num_endpoपूर्णांकs = 1,
		.endpoपूर्णांकs = &single_endpoपूर्णांक,
		.name_prefix = "rt711"
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_adr_device rt1308_1_single_adr[] = अणु
	अणु
		.adr = 0x000120025D130800,
		.num_endpoपूर्णांकs = 1,
		.endpoपूर्णांकs = &single_endpoपूर्णांक,
		.name_prefix = "rt1308-1"
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_adr_device rt1308_1_group1_adr[] = अणु
	अणु
		.adr = 0x000120025D130800,
		.num_endpoपूर्णांकs = 1,
		.endpoपूर्णांकs = &spk_l_endpoपूर्णांक,
		.name_prefix = "rt1308-1"
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_adr_device rt1308_2_group1_adr[] = अणु
	अणु
		.adr = 0x000220025D130800,
		.num_endpoपूर्णांकs = 1,
		.endpoपूर्णांकs = &spk_r_endpoपूर्णांक,
		.name_prefix = "rt1308-2"
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_adr_device rt715_3_adr[] = अणु
	अणु
		.adr = 0x000320025D071500,
		.num_endpoपूर्णांकs = 1,
		.endpoपूर्णांकs = &single_endpoपूर्णांक,
		.name_prefix = "rt715"
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_adr_device rt711_sdca_0_adr[] = अणु
	अणु
		.adr = 0x000030025D071101,
		.num_endpoपूर्णांकs = 1,
		.endpoपूर्णांकs = &single_endpoपूर्णांक,
		.name_prefix = "rt711"
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_adr_device rt1316_1_group1_adr[] = अणु
	अणु
		.adr = 0x000131025D131601, /* unique ID is set क्रम some reason */
		.num_endpoपूर्णांकs = 1,
		.endpoपूर्णांकs = &spk_l_endpoपूर्णांक,
		.name_prefix = "rt1316-1"
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_adr_device rt1316_2_group1_adr[] = अणु
	अणु
		.adr = 0x000230025D131601,
		.num_endpoपूर्णांकs = 1,
		.endpoपूर्णांकs = &spk_r_endpoपूर्णांक,
		.name_prefix = "rt1316-2"
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_adr_device rt714_3_adr[] = अणु
	अणु
		.adr = 0x000330025D071401,
		.num_endpoपूर्णांकs = 1,
		.endpoपूर्णांकs = &single_endpoपूर्णांक,
		.name_prefix = "rt714"
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_link_adr cml_3_in_1_शेष[] = अणु
	अणु
		.mask = BIT(0),
		.num_adr = ARRAY_SIZE(rt711_0_adr),
		.adr_d = rt711_0_adr,
	पूर्ण,
	अणु
		.mask = BIT(1),
		.num_adr = ARRAY_SIZE(rt1308_1_group1_adr),
		.adr_d = rt1308_1_group1_adr,
	पूर्ण,
	अणु
		.mask = BIT(2),
		.num_adr = ARRAY_SIZE(rt1308_2_group1_adr),
		.adr_d = rt1308_2_group1_adr,
	पूर्ण,
	अणु
		.mask = BIT(3),
		.num_adr = ARRAY_SIZE(rt715_3_adr),
		.adr_d = rt715_3_adr,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_link_adr cml_3_in_1_mono_amp[] = अणु
	अणु
		.mask = BIT(0),
		.num_adr = ARRAY_SIZE(rt711_0_adr),
		.adr_d = rt711_0_adr,
	पूर्ण,
	अणु
		.mask = BIT(1),
		.num_adr = ARRAY_SIZE(rt1308_1_single_adr),
		.adr_d = rt1308_1_single_adr,
	पूर्ण,
	अणु
		.mask = BIT(3),
		.num_adr = ARRAY_SIZE(rt715_3_adr),
		.adr_d = rt715_3_adr,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_link_adr cml_3_in_1_sdca[] = अणु
	अणु
		.mask = BIT(0),
		.num_adr = ARRAY_SIZE(rt711_sdca_0_adr),
		.adr_d = rt711_sdca_0_adr,
	पूर्ण,
	अणु
		.mask = BIT(1),
		.num_adr = ARRAY_SIZE(rt1316_1_group1_adr),
		.adr_d = rt1316_1_group1_adr,
	पूर्ण,
	अणु
		.mask = BIT(2),
		.num_adr = ARRAY_SIZE(rt1316_2_group1_adr),
		.adr_d = rt1316_2_group1_adr,
	पूर्ण,
	अणु
		.mask = BIT(3),
		.num_adr = ARRAY_SIZE(rt714_3_adr),
		.adr_d = rt714_3_adr,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा snd_soc_acpi_mach snd_soc_acpi_पूर्णांकel_cml_sdw_machines[] = अणु
	अणु
		.link_mask = 0xF, /* 4 active links required */
		.links = cml_3_in_1_शेष,
		.drv_name = "sof_sdw",
		.sof_fw_filename = "sof-cml.ri",
		.sof_tplg_filename = "sof-cml-rt711-rt1308-rt715.tplg",
	पूर्ण,
	अणु
		.link_mask = 0xF, /* 4 active links required */
		.links = cml_3_in_1_sdca,
		.drv_name = "sof_sdw",
		.sof_fw_filename = "sof-cml.ri",
		.sof_tplg_filename = "sof-cml-rt711-rt1316-rt714.tplg",
	पूर्ण,
	अणु
		/*
		 * link_mask should be 0xB, but all links are enabled by BIOS.
		 * This entry will be selected अगर there is no rt1308 exposed
		 * on link2 since it will fail to match the above entry.
		 */
		.link_mask = 0xF,
		.links = cml_3_in_1_mono_amp,
		.drv_name = "sof_sdw",
		.sof_fw_filename = "sof-cml.ri",
		.sof_tplg_filename = "sof-cml-rt711-rt1308-mono-rt715.tplg",
	पूर्ण,
	अणु
		.link_mask = 0x2, /* RT700 connected on Link1 */
		.links = cml_rvp,
		.drv_name = "sof_sdw",
		.sof_fw_filename = "sof-cml.ri",
		.sof_tplg_filename = "sof-cml-rt700.tplg",
	पूर्ण,
	अणुपूर्ण
पूर्ण;
EXPORT_SYMBOL_GPL(snd_soc_acpi_पूर्णांकel_cml_sdw_machines);
