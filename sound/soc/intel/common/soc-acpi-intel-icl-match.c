<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * soc-acpi-पूर्णांकel-icl-match.c - tables and support क्रम ICL ACPI क्रमागतeration.
 *
 * Copyright (c) 2018, Intel Corporation.
 *
 */

#समावेश <sound/soc-acpi.h>
#समावेश <sound/soc-acpi-पूर्णांकel-match.h>
#समावेश "../skylake/skl.h"

अटल काष्ठा skl_machine_pdata icl_pdata = अणु
	.use_tplg_pcm = true,
पूर्ण;

काष्ठा snd_soc_acpi_mach snd_soc_acpi_पूर्णांकel_icl_machines[] = अणु
	अणु
		.id = "INT34C2",
		.drv_name = "icl_rt274",
		.fw_filename = "intel/dsp_fw_icl.bin",
		.pdata = &icl_pdata,
		.sof_fw_filename = "sof-icl.ri",
		.sof_tplg_filename = "sof-icl-rt274.tplg",
	पूर्ण,
	अणु
		.id = "10EC5682",
		.drv_name = "sof_rt5682",
		.sof_fw_filename = "sof-icl.ri",
		.sof_tplg_filename = "sof-icl-rt5682.tplg",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(snd_soc_acpi_पूर्णांकel_icl_machines);

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

अटल स्थिर काष्ठा snd_soc_acpi_adr_device rt700_0_adr[] = अणु
	अणु
		.adr = 0x000010025D070000,
		.num_endpoपूर्णांकs = 1,
		.endpoपूर्णांकs = &single_endpoपूर्णांक,
		.name_prefix = "rt700"
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_link_adr icl_rvp[] = अणु
	अणु
		.mask = BIT(0),
		.num_adr = ARRAY_SIZE(rt700_0_adr),
		.adr_d = rt700_0_adr,
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

अटल स्थिर काष्ठा snd_soc_acpi_adr_device rt1308_1_adr[] = अणु
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

अटल स्थिर काष्ठा snd_soc_acpi_link_adr icl_3_in_1_शेष[] = अणु
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

अटल स्थिर काष्ठा snd_soc_acpi_link_adr icl_3_in_1_mono_amp[] = अणु
	अणु
		.mask = BIT(0),
		.num_adr = ARRAY_SIZE(rt711_0_adr),
		.adr_d = rt711_0_adr,
	पूर्ण,
	अणु
		.mask = BIT(1),
		.num_adr = ARRAY_SIZE(rt1308_1_adr),
		.adr_d = rt1308_1_adr,
	पूर्ण,
	अणु
		.mask = BIT(3),
		.num_adr = ARRAY_SIZE(rt715_3_adr),
		.adr_d = rt715_3_adr,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा snd_soc_acpi_mach snd_soc_acpi_पूर्णांकel_icl_sdw_machines[] = अणु
	अणु
		.link_mask = 0xF, /* 4 active links required */
		.links = icl_3_in_1_शेष,
		.drv_name = "sof_sdw",
		.sof_fw_filename = "sof-icl.ri",
		.sof_tplg_filename = "sof-icl-rt711-rt1308-rt715.tplg",
	पूर्ण,
	अणु
		.link_mask = 0xB, /* 3 active links required */
		.links = icl_3_in_1_mono_amp,
		.drv_name = "sof_sdw",
		.sof_fw_filename = "sof-icl.ri",
		.sof_tplg_filename = "sof-icl-rt711-rt1308-rt715-mono.tplg",
	पूर्ण,
	अणु
		.link_mask = 0x1, /* rt700 connected on link0 */
		.links = icl_rvp,
		.drv_name = "sof_sdw",
		.sof_fw_filename = "sof-icl.ri",
		.sof_tplg_filename = "sof-icl-rt700.tplg",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(snd_soc_acpi_पूर्णांकel_icl_sdw_machines);
