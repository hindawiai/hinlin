<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * soc-acpi-पूर्णांकel-glk-match.c - tables and support क्रम GLK ACPI क्रमागतeration.
 *
 * Copyright (c) 2018, Intel Corporation.
 *
 */

#समावेश <sound/soc-acpi.h>
#समावेश <sound/soc-acpi-पूर्णांकel-match.h>

अटल काष्ठा snd_soc_acpi_codecs glk_codecs = अणु
	.num_codecs = 1,
	.codecs = अणु"MX98357A"पूर्ण
पूर्ण;

काष्ठा snd_soc_acpi_mach snd_soc_acpi_पूर्णांकel_glk_machines[] = अणु
	अणु
		.id = "INT343A",
		.drv_name = "glk_alc298s_i2s",
		.fw_filename = "intel/dsp_fw_glk.bin",
		.sof_fw_filename = "sof-glk.ri",
		.sof_tplg_filename = "sof-glk-alc298.tplg",
	पूर्ण,
	अणु
		.id = "DLGS7219",
		.drv_name = "glk_da7219_max98357a",
		.fw_filename = "intel/dsp_fw_glk.bin",
		.machine_quirk = snd_soc_acpi_codec_list,
		.quirk_data = &glk_codecs,
		.sof_fw_filename = "sof-glk.ri",
		.sof_tplg_filename = "sof-glk-da7219.tplg",
	पूर्ण,
	अणु
		.id = "10EC5682",
		.drv_name = "glk_rt5682_max98357a",
		.fw_filename = "intel/dsp_fw_glk.bin",
		.machine_quirk = snd_soc_acpi_codec_list,
		.quirk_data = &glk_codecs,
		.sof_fw_filename = "sof-glk.ri",
		.sof_tplg_filename = "sof-glk-rt5682.tplg",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(snd_soc_acpi_पूर्णांकel_glk_machines);
