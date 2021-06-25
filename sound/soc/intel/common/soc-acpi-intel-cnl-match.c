<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * soc-acpi-पूर्णांकel-cnl-match.c - tables and support क्रम CNL ACPI क्रमागतeration.
 *
 * Copyright (c) 2018, Intel Corporation.
 *
 */

#समावेश <sound/soc-acpi.h>
#समावेश <sound/soc-acpi-पूर्णांकel-match.h>
#समावेश "../skylake/skl.h"

अटल काष्ठा skl_machine_pdata cnl_pdata = अणु
	.use_tplg_pcm = true,
पूर्ण;

काष्ठा snd_soc_acpi_mach snd_soc_acpi_पूर्णांकel_cnl_machines[] = अणु
	अणु
		.id = "INT34C2",
		.drv_name = "cnl_rt274",
		.fw_filename = "intel/dsp_fw_cnl.bin",
		.pdata = &cnl_pdata,
		.sof_fw_filename = "sof-cnl.ri",
		.sof_tplg_filename = "sof-cnl-rt274.tplg",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(snd_soc_acpi_पूर्णांकel_cnl_machines);

अटल स्थिर काष्ठा snd_soc_acpi_endpoपूर्णांक single_endpoपूर्णांक = अणु
	.num = 0,
	.aggregated = 0,
	.group_position = 0,
	.group_id = 0,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_adr_device rt5682_2_adr[] = अणु
	अणु
		.adr = 0x000220025D568200,
		.num_endpoपूर्णांकs = 1,
		.endpoपूर्णांकs = &single_endpoपूर्णांक,
		.name_prefix = "rt5682"
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_acpi_link_adr up_extreme_rt5682_2[] = अणु
	अणु
		.mask = BIT(2),
		.num_adr = ARRAY_SIZE(rt5682_2_adr),
		.adr_d = rt5682_2_adr,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा snd_soc_acpi_mach snd_soc_acpi_पूर्णांकel_cnl_sdw_machines[] = अणु
	अणु
		.link_mask = BIT(2),
		.links = up_extreme_rt5682_2,
		.drv_name = "sof_sdw",
		.sof_fw_filename = "sof-cnl.ri",
		.sof_tplg_filename = "sof-cnl-rt5682-sdw2.tplg"
	पूर्ण,
	अणुपूर्ण
पूर्ण;
EXPORT_SYMBOL_GPL(snd_soc_acpi_पूर्णांकel_cnl_sdw_machines);
