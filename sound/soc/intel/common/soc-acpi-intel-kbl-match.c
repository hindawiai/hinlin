<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * soc-acpi-पूर्णांकel-kbl-match.c - tables and support क्रम KBL ACPI क्रमागतeration.
 *
 * Copyright (c) 2018, Intel Corporation.
 *
 */

#समावेश <sound/soc-acpi.h>
#समावेश <sound/soc-acpi-पूर्णांकel-match.h>
#समावेश "../skylake/skl.h"

अटल काष्ठा skl_machine_pdata skl_dmic_data;

अटल काष्ठा snd_soc_acpi_codecs kbl_codecs = अणु
	.num_codecs = 1,
	.codecs = अणु"10508825"पूर्ण
पूर्ण;

अटल काष्ठा snd_soc_acpi_codecs kbl_poppy_codecs = अणु
	.num_codecs = 1,
	.codecs = अणु"10EC5663"पूर्ण
पूर्ण;

अटल काष्ठा snd_soc_acpi_codecs kbl_5663_5514_codecs = अणु
	.num_codecs = 2,
	.codecs = अणु"10EC5663", "10EC5514"पूर्ण
पूर्ण;

अटल काष्ठा snd_soc_acpi_codecs kbl_7219_98357_codecs = अणु
	.num_codecs = 1,
	.codecs = अणु"MX98357A"पूर्ण
पूर्ण;

अटल काष्ठा snd_soc_acpi_codecs kbl_7219_98927_codecs = अणु
	.num_codecs = 1,
	.codecs = अणु"MX98927"पूर्ण
पूर्ण;

अटल काष्ठा snd_soc_acpi_codecs kbl_7219_98373_codecs = अणु
	.num_codecs = 1,
	.codecs = अणु"MX98373"पूर्ण
पूर्ण;

काष्ठा snd_soc_acpi_mach snd_soc_acpi_पूर्णांकel_kbl_machines[] = अणु
	अणु
		.id = "INT343A",
		.drv_name = "kbl_alc286s_i2s",
		.fw_filename = "intel/dsp_fw_kbl.bin",
	पूर्ण,
	अणु
		.id = "INT343B",
		.drv_name = "kbl_n88l25_s4567",
		.fw_filename = "intel/dsp_fw_kbl.bin",
		.machine_quirk = snd_soc_acpi_codec_list,
		.quirk_data = &kbl_codecs,
		.pdata = &skl_dmic_data,
	पूर्ण,
	अणु
		.id = "MX98357A",
		.drv_name = "kbl_n88l25_m98357a",
		.fw_filename = "intel/dsp_fw_kbl.bin",
		.machine_quirk = snd_soc_acpi_codec_list,
		.quirk_data = &kbl_codecs,
		.pdata = &skl_dmic_data,
	पूर्ण,
	अणु
		.id = "MX98927",
		.drv_name = "kbl_r5514_5663_max",
		.fw_filename = "intel/dsp_fw_kbl.bin",
		.machine_quirk = snd_soc_acpi_codec_list,
		.quirk_data = &kbl_5663_5514_codecs,
		.pdata = &skl_dmic_data,
	पूर्ण,
	अणु
		.id = "MX98927",
		.drv_name = "kbl_rt5663_m98927",
		.fw_filename = "intel/dsp_fw_kbl.bin",
		.machine_quirk = snd_soc_acpi_codec_list,
		.quirk_data = &kbl_poppy_codecs,
		.pdata = &skl_dmic_data,
	पूर्ण,
	अणु
		.id = "10EC5663",
		.drv_name = "kbl_rt5663",
		.fw_filename = "intel/dsp_fw_kbl.bin",
	पूर्ण,
	अणु
		.id = "DLGS7219",
		.drv_name = "kbl_da7219_max98357a",
		.fw_filename = "intel/dsp_fw_kbl.bin",
		.machine_quirk = snd_soc_acpi_codec_list,
		.quirk_data = &kbl_7219_98357_codecs,
		.pdata = &skl_dmic_data,
	पूर्ण,
	अणु
		.id = "DLGS7219",
		.drv_name = "kbl_da7219_max98927",
		.fw_filename = "intel/dsp_fw_kbl.bin",
		.machine_quirk = snd_soc_acpi_codec_list,
		.quirk_data = &kbl_7219_98927_codecs,
		.pdata = &skl_dmic_data
	पूर्ण,
	अणु
		.id = "10EC5660",
		.drv_name = "kbl_rt5660",
		.fw_filename = "intel/dsp_fw_kbl.bin",
	पूर्ण,
	अणु
		.id = "10EC3277",
		.drv_name = "kbl_rt5660",
		.fw_filename = "intel/dsp_fw_kbl.bin",
	पूर्ण,
	अणु
		.id = "DLGS7219",
		.drv_name = "kbl_da7219_max98373",
		.fw_filename = "intel/dsp_fw_kbl.bin",
		.machine_quirk = snd_soc_acpi_codec_list,
		.quirk_data = &kbl_7219_98373_codecs,
		.pdata = &skl_dmic_data
	पूर्ण,
	अणु
		.id = "MX98373",
		.drv_name = "kbl_max98373",
		.fw_filename = "intel/dsp_fw_kbl.bin",
		.pdata = &skl_dmic_data
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(snd_soc_acpi_पूर्णांकel_kbl_machines);
