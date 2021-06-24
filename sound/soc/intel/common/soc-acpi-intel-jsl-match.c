<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * soc-apci-पूर्णांकel-jsl-match.c - tables and support क्रम JSL ACPI क्रमागतeration.
 *
 * Copyright (c) 2019-2020, Intel Corporation.
 *
 */

#समावेश <sound/soc-acpi.h>
#समावेश <sound/soc-acpi-पूर्णांकel-match.h>

अटल काष्ठा snd_soc_acpi_codecs jsl_7219_98373_codecs = अणु
	.num_codecs = 1,
	.codecs = अणु"MX98373"पूर्ण
पूर्ण;

अटल काष्ठा snd_soc_acpi_codecs rt1015_spk = अणु
	.num_codecs = 1,
	.codecs = अणु"10EC1015"पूर्ण
पूर्ण;

अटल काष्ठा snd_soc_acpi_codecs rt1015p_spk = अणु
	.num_codecs = 1,
	.codecs = अणु"RTL1015"पूर्ण
पूर्ण;

अटल काष्ठा snd_soc_acpi_codecs mx98360a_spk = अणु
	.num_codecs = 1,
	.codecs = अणु"MX98360A"पूर्ण
पूर्ण;

/*
 * When adding new entry to the snd_soc_acpi_पूर्णांकel_jsl_machines array,
 * use .quirk_data member to distinguish dअगरferent machine driver,
 * and keep ACPI .id field unchanged क्रम the common codec.
 */
काष्ठा snd_soc_acpi_mach snd_soc_acpi_पूर्णांकel_jsl_machines[] = अणु
	अणु
		.id = "DLGS7219",
		.drv_name = "sof_da7219_max98373",
		.sof_fw_filename = "sof-jsl.ri",
		.sof_tplg_filename = "sof-jsl-da7219.tplg",
		.machine_quirk = snd_soc_acpi_codec_list,
		.quirk_data = &jsl_7219_98373_codecs,
	पूर्ण,
	अणु
		.id = "DLGS7219",
		.drv_name = "sof_da7219_max98360a",
		.sof_fw_filename = "sof-jsl.ri",
		.sof_tplg_filename = "sof-jsl-da7219-mx98360a.tplg",
	पूर्ण,
	अणु
		.id = "10EC5682",
		.drv_name = "jsl_rt5682_rt1015",
		.sof_fw_filename = "sof-jsl.ri",
		.machine_quirk = snd_soc_acpi_codec_list,
		.quirk_data = &rt1015_spk,
		.sof_tplg_filename = "sof-jsl-rt5682-rt1015.tplg",
	पूर्ण,
	अणु
		.id = "10EC5682",
		.drv_name = "jsl_rt5682_rt1015p",
		.sof_fw_filename = "sof-jsl.ri",
		.machine_quirk = snd_soc_acpi_codec_list,
		.quirk_data = &rt1015p_spk,
		.sof_tplg_filename = "sof-jsl-rt5682-rt1015.tplg",
	पूर्ण,
	अणु
		.id = "10EC5682",
		.drv_name = "jsl_rt5682_max98360a",
		.sof_fw_filename = "sof-jsl.ri",
		.machine_quirk = snd_soc_acpi_codec_list,
		.quirk_data = &mx98360a_spk,
		.sof_tplg_filename = "sof-jsl-rt5682-mx98360a.tplg",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(snd_soc_acpi_पूर्णांकel_jsl_machines);
