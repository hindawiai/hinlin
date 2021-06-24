<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * soc-apci-पूर्णांकel-adl-match.c - tables and support क्रम ADL ACPI क्रमागतeration.
 *
 * Copyright (c) 2020, Intel Corporation.
 */

#समावेश <sound/soc-acpi.h>
#समावेश <sound/soc-acpi-पूर्णांकel-match.h>

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

अटल स्थिर काष्ठा snd_soc_acpi_adr_device rt1316_3_group1_adr[] = अणु
	अणु
		.adr = 0x000330025D131601,
		.num_endpoपूर्णांकs = 1,
		.endpoपूर्णांकs = &spk_r_endpoपूर्णांक,
		.name_prefix = "rt1316-2"
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_adr_device rt1316_2_single_adr[] = अणु
	अणु
		.adr = 0x000230025D131601,
		.num_endpoपूर्णांकs = 1,
		.endpoपूर्णांकs = &single_endpoपूर्णांक,
		.name_prefix = "rt1316-1"
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_adr_device rt714_0_adr[] = अणु
	अणु
		.adr = 0x000030025D071401,
		.num_endpoपूर्णांकs = 1,
		.endpoपूर्णांकs = &single_endpoपूर्णांक,
		.name_prefix = "rt714"
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_adr_device rt714_2_adr[] = अणु
	अणु
		.adr = 0x000230025D071401,
		.num_endpoपूर्णांकs = 1,
		.endpoपूर्णांकs = &single_endpoपूर्णांक,
		.name_prefix = "rt714"
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

अटल स्थिर काष्ठा snd_soc_acpi_link_adr adl_शेष[] = अणु
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

अटल स्थिर काष्ठा snd_soc_acpi_link_adr adl_sdca_शेष[] = अणु
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

अटल स्थिर काष्ठा snd_soc_acpi_link_adr adl_sdca_3_in_1[] = अणु
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
		.num_adr = ARRAY_SIZE(rt714_2_adr),
		.adr_d = rt714_2_adr,
	पूर्ण,
	अणु
		.mask = BIT(3),
		.num_adr = ARRAY_SIZE(rt1316_3_group1_adr),
		.adr_d = rt1316_3_group1_adr,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_link_adr adl_sdw_rt1316_link2_rt714_link0[] = अणु
	अणु
		.mask = BIT(2),
		.num_adr = ARRAY_SIZE(rt1316_2_single_adr),
		.adr_d = rt1316_2_single_adr,
	पूर्ण,
	अणु
		.mask = BIT(0),
		.num_adr = ARRAY_SIZE(rt714_0_adr),
		.adr_d = rt714_0_adr,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_link_adr adl_rvp[] = अणु
	अणु
		.mask = BIT(0),
		.num_adr = ARRAY_SIZE(rt711_0_adr),
		.adr_d = rt711_0_adr,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा snd_soc_acpi_mach snd_soc_acpi_पूर्णांकel_adl_machines[] = अणु
	अणुपूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(snd_soc_acpi_पूर्णांकel_adl_machines);

/* this table is used when there is no I2S codec present */
काष्ठा snd_soc_acpi_mach snd_soc_acpi_पूर्णांकel_adl_sdw_machines[] = अणु
	अणु
		.link_mask = 0xF, /* 4 active links required */
		.links = adl_शेष,
		.drv_name = "sof_sdw",
		.sof_tplg_filename = "sof-adl-rt711-l0-rt1308-l12-rt715-l3.tplg",
	पूर्ण,
	अणु
		.link_mask = 0xF, /* 4 active links required */
		.links = adl_sdca_शेष,
		.drv_name = "sof_sdw",
		.sof_tplg_filename = "sof-adl-rt711-l0-rt1316-l12-rt714-l3.tplg",
	पूर्ण,
	अणु
		.link_mask = 0xF, /* 4 active links required */
		.links = adl_sdca_3_in_1,
		.drv_name = "sof_sdw",
		.sof_tplg_filename = "sof-adl-rt711-l0-rt1316-l13-rt714-l2.tplg",
	पूर्ण,
	अणु
		.link_mask = 0x5, /* 2 active links required */
		.links = adl_sdw_rt1316_link2_rt714_link0,
		.drv_name = "sof_sdw",
		.sof_tplg_filename = "sof-adl-rt1316-l2-mono-rt714-l0.tplg",
	पूर्ण,
	अणु
		.link_mask = 0x1, /* link0 required */
		.links = adl_rvp,
		.drv_name = "sof_sdw",
		.sof_tplg_filename = "sof-adl-rt711.tplg",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(snd_soc_acpi_पूर्णांकel_adl_sdw_machines);
