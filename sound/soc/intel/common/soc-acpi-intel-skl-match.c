<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * soc-acpi-पूर्णांकel-skl-match.c - tables and support क्रम SKL ACPI क्रमागतeration.
 *
 * Copyright (c) 2018, Intel Corporation.
 *
 */

#समावेश <sound/soc-acpi.h>
#समावेश <sound/soc-acpi-पूर्णांकel-match.h>
#समावेश "../skylake/skl.h"

अटल काष्ठा skl_machine_pdata skl_dmic_data;

अटल काष्ठा snd_soc_acpi_codecs skl_codecs = अणु
	.num_codecs = 1,
	.codecs = अणु"10508825"पूर्ण
पूर्ण;

काष्ठा snd_soc_acpi_mach snd_soc_acpi_पूर्णांकel_skl_machines[] = अणु
	अणु
		.id = "INT343A",
		.drv_name = "skl_alc286s_i2s",
		.fw_filename = "intel/dsp_fw_release.bin",
	पूर्ण,
	अणु
		.id = "INT343B",
		.drv_name = "skl_n88l25_s4567",
		.fw_filename = "intel/dsp_fw_release.bin",
		.machine_quirk = snd_soc_acpi_codec_list,
		.quirk_data = &skl_codecs,
		.pdata = &skl_dmic_data,
	पूर्ण,
	अणु
		.id = "MX98357A",
		.drv_name = "skl_n88l25_m98357a",
		.fw_filename = "intel/dsp_fw_release.bin",
		.machine_quirk = snd_soc_acpi_codec_list,
		.quirk_data = &skl_codecs,
		.pdata = &skl_dmic_data,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(snd_soc_acpi_पूर्णांकel_skl_machines);
