<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * soc-acpi-पूर्णांकel-tgl-match.c - tables and support क्रम TGL ACPI क्रमागतeration.
 *
 * Copyright (c) 2019, Intel Corporation.
 *
 */

#समावेश <sound/soc-acpi.h>
#समावेश <sound/soc-acpi-पूर्णांकel-match.h>

अटल स्थिर काष्ठा snd_soc_acpi_codecs tgl_codecs = अणु
	.num_codecs = 1,
	.codecs = अणु"MX98357A"पूर्ण
पूर्ण;

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

अटल स्थिर काष्ठा snd_soc_acpi_adr_device rt711_0_adr[] = अणु
	अणु
		.adr = 0x000020025D071100,
		.num_endpoपूर्णांकs = 1,
		.endpoपूर्णांकs = &single_endpoपूर्णांक,
		.name_prefix = "rt711"
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_adr_device rt711_1_adr[] = अणु
	अणु
		.adr = 0x000120025D071100,
		.num_endpoपूर्णांकs = 1,
		.endpoपूर्णांकs = &single_endpoपूर्णांक,
		.name_prefix = "rt711"
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_adr_device rt1308_1_dual_adr[] = अणु
	अणु
		.adr = 0x000120025D130800,
		.num_endpoपूर्णांकs = 1,
		.endpoपूर्णांकs = &spk_l_endpoपूर्णांक,
		.name_prefix = "rt1308-1"
	पूर्ण,
	अणु
		.adr = 0x000122025D130800,
		.num_endpoपूर्णांकs = 1,
		.endpoपूर्णांकs = &spk_r_endpoपूर्णांक,
		.name_prefix = "rt1308-2"
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

अटल स्थिर काष्ठा snd_soc_acpi_adr_device rt1308_2_single_adr[] = अणु
	अणु
		.adr = 0x000220025D130800,
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

अटल स्थिर काष्ठा snd_soc_acpi_adr_device rt715_0_adr[] = अणु
	अणु
		.adr = 0x000021025D071500,
		.num_endpoपूर्णांकs = 1,
		.endpoपूर्णांकs = &single_endpoपूर्णांक,
		.name_prefix = "rt715"
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

अटल स्थिर काष्ठा snd_soc_acpi_adr_device mx8373_1_adr[] = अणु
	अणु
		.adr = 0x000123019F837300,
		.num_endpoपूर्णांकs = 1,
		.endpoपूर्णांकs = &spk_l_endpoपूर्णांक,
		.name_prefix = "Right"
	पूर्ण,
	अणु
		.adr = 0x000127019F837300,
		.num_endpoपूर्णांकs = 1,
		.endpoपूर्णांकs = &spk_r_endpoपूर्णांक,
		.name_prefix = "Left"
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_adr_device rt5682_0_adr[] = अणु
	अणु
		.adr = 0x000021025D568200,
		.num_endpoपूर्णांकs = 1,
		.endpoपूर्णांकs = &single_endpoपूर्णांक,
		.name_prefix = "rt5682"
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

अटल स्थिर काष्ठा snd_soc_acpi_link_adr tgl_rvp[] = अणु
	अणु
		.mask = BIT(0),
		.num_adr = ARRAY_SIZE(rt711_0_adr),
		.adr_d = rt711_0_adr,
	पूर्ण,
	अणु
		.mask = BIT(1),
		.num_adr = ARRAY_SIZE(rt1308_1_dual_adr),
		.adr_d = rt1308_1_dual_adr,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_link_adr tgl_hp[] = अणु
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
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_link_adr tgl_chromebook_base[] = अणु
	अणु
		.mask = BIT(0),
		.num_adr = ARRAY_SIZE(rt5682_0_adr),
		.adr_d = rt5682_0_adr,
	पूर्ण,
	अणु
		.mask = BIT(1),
		.num_adr = ARRAY_SIZE(mx8373_1_adr),
		.adr_d = mx8373_1_adr,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_link_adr tgl_3_in_1_शेष[] = अणु
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

अटल स्थिर काष्ठा snd_soc_acpi_link_adr tgl_3_in_1_mono_amp[] = अणु
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

अटल स्थिर काष्ठा snd_soc_acpi_link_adr tgl_sdw_rt711_link1_rt1308_link2_rt715_link0[] = अणु
	अणु
		.mask = BIT(1),
		.num_adr = ARRAY_SIZE(rt711_1_adr),
		.adr_d = rt711_1_adr,
	पूर्ण,
	अणु
		.mask = BIT(2),
		.num_adr = ARRAY_SIZE(rt1308_2_single_adr),
		.adr_d = rt1308_2_single_adr,
	पूर्ण,
	अणु
		.mask = BIT(0),
		.num_adr = ARRAY_SIZE(rt715_0_adr),
		.adr_d = rt715_0_adr,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_link_adr tgl_3_in_1_sdca[] = अणु
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

अटल स्थिर काष्ठा snd_soc_acpi_codecs tgl_max98373_amp = अणु
	.num_codecs = 1,
	.codecs = अणु"MX98373"पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_codecs tgl_rt1011_amp = अणु
	.num_codecs = 1,
	.codecs = अणु"10EC1011"पूर्ण
पूर्ण;

काष्ठा snd_soc_acpi_mach snd_soc_acpi_पूर्णांकel_tgl_machines[] = अणु
	अणु
		.id = "10EC5682",
		.drv_name = "tgl_max98357a_rt5682",
		.machine_quirk = snd_soc_acpi_codec_list,
		.quirk_data = &tgl_codecs,
		.sof_fw_filename = "sof-tgl.ri",
		.sof_tplg_filename = "sof-tgl-max98357a-rt5682.tplg",
	पूर्ण,
	अणु
		.id = "10EC5682",
		.drv_name = "tgl_max98373_rt5682",
		.machine_quirk = snd_soc_acpi_codec_list,
		.quirk_data = &tgl_max98373_amp,
		.sof_fw_filename = "sof-tgl.ri",
		.sof_tplg_filename = "sof-tgl-max98373-rt5682.tplg",
	पूर्ण,
	अणु
		.id = "10EC5682",
		.drv_name = "tgl_rt1011_rt5682",
		.machine_quirk = snd_soc_acpi_codec_list,
		.quirk_data = &tgl_rt1011_amp,
		.sof_fw_filename = "sof-tgl.ri",
		.sof_tplg_filename = "sof-tgl-rt1011-rt5682.tplg",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(snd_soc_acpi_पूर्णांकel_tgl_machines);

/* this table is used when there is no I2S codec present */
काष्ठा snd_soc_acpi_mach snd_soc_acpi_पूर्णांकel_tgl_sdw_machines[] = अणु
	अणु
		.link_mask = 0x7,
		.links = tgl_sdw_rt711_link1_rt1308_link2_rt715_link0,
		.drv_name = "sof_sdw",
		.sof_tplg_filename = "sof-tgl-rt715-rt711-rt1308-mono.tplg",
	पूर्ण,
	अणु
		.link_mask = 0xF, /* 4 active links required */
		.links = tgl_3_in_1_शेष,
		.drv_name = "sof_sdw",
		.sof_tplg_filename = "sof-tgl-rt711-rt1308-rt715.tplg",
	पूर्ण,
	अणु
		/*
		 * link_mask should be 0xB, but all links are enabled by BIOS.
		 * This entry will be selected अगर there is no rt1308 exposed
		 * on link2 since it will fail to match the above entry.
		 */
		.link_mask = 0xF,
		.links = tgl_3_in_1_mono_amp,
		.drv_name = "sof_sdw",
		.sof_tplg_filename = "sof-tgl-rt711-rt1308-mono-rt715.tplg",
	पूर्ण,
	अणु
		.link_mask = 0xF, /* 4 active links required */
		.links = tgl_3_in_1_sdca,
		.drv_name = "sof_sdw",
		.sof_tplg_filename = "sof-tgl-rt711-rt1316-rt714.tplg",
	पूर्ण,
	अणु
		.link_mask = 0x3, /* rt711 on link 0 and 1 rt1308 on link 1 */
		.links = tgl_hp,
		.drv_name = "sof_sdw",
		.sof_tplg_filename = "sof-tgl-rt711-rt1308.tplg",
	पूर्ण,
	अणु
		.link_mask = 0x3, /* rt711 on link 0 and 2 rt1308s on link 1 */
		.links = tgl_rvp,
		.drv_name = "sof_sdw",
		.sof_tplg_filename = "sof-tgl-rt711-rt1308.tplg",
	पूर्ण,
	अणु
		.link_mask = 0x3, /* rt5682 on link0 & 2xmax98373 on link 1 */
		.links = tgl_chromebook_base,
		.drv_name = "sof_sdw",
		.sof_tplg_filename = "sof-tgl-sdw-max98373-rt5682.tplg",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(snd_soc_acpi_पूर्णांकel_tgl_sdw_machines);
