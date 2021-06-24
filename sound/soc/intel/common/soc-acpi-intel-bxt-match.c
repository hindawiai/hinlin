<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * soc-acpi-पूर्णांकel-bxt-match.c - tables and support क्रम BXT ACPI क्रमागतeration.
 *
 * Copyright (c) 2018, Intel Corporation.
 *
 */

#समावेश <linux/dmi.h>
#समावेश <sound/soc-acpi.h>
#समावेश <sound/soc-acpi-पूर्णांकel-match.h>

क्रमागत अणु
	APL_RVP,
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id apl_table[] = अणु
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Intel Corp."),
			DMI_MATCH(DMI_BOARD_NAME, "Apollolake RVP1A"),
		पूर्ण,
		.driver_data = (व्योम *)(APL_RVP),
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा snd_soc_acpi_mach *apl_quirk(व्योम *arg)
अणु
	काष्ठा snd_soc_acpi_mach *mach = arg;
	स्थिर काष्ठा dmi_प्रणाली_id *dmi_id;
	अचिन्हित दीर्घ apl_machine_id;

	dmi_id = dmi_first_match(apl_table);
	अगर (dmi_id) अणु
		apl_machine_id = (अचिन्हित दीर्घ)dmi_id->driver_data;
		अगर (apl_machine_id == APL_RVP)
			वापस शून्य;
	पूर्ण

	वापस mach;
पूर्ण

अटल काष्ठा snd_soc_acpi_codecs bxt_codecs = अणु
	.num_codecs = 1,
	.codecs = अणु"MX98357A"पूर्ण
पूर्ण;

काष्ठा snd_soc_acpi_mach snd_soc_acpi_पूर्णांकel_bxt_machines[] = अणु
	अणु
		.id = "INT343A",
		.drv_name = "bxt_alc298s_i2s",
		.fw_filename = "intel/dsp_fw_bxtn.bin",
		.sof_fw_filename = "sof-apl.ri",
		.sof_tplg_filename = "sof-apl-rt298.tplg",
	पूर्ण,
	अणु
		.id = "DLGS7219",
		.drv_name = "bxt_da7219_max98357a",
		.fw_filename = "intel/dsp_fw_bxtn.bin",
		.machine_quirk = snd_soc_acpi_codec_list,
		.quirk_data = &bxt_codecs,
		.sof_fw_filename = "sof-apl.ri",
		.sof_tplg_filename = "sof-apl-da7219.tplg",
	पूर्ण,
	अणु
		.id = "104C5122",
		.drv_name = "sof_pcm512x",
		.sof_fw_filename = "sof-apl.ri",
		.sof_tplg_filename = "sof-apl-pcm512x.tplg",
	पूर्ण,
	अणु
		.id = "1AEC8804",
		.drv_name = "sof-wm8804",
		.sof_fw_filename = "sof-apl.ri",
		.sof_tplg_filename = "sof-apl-wm8804.tplg",
	पूर्ण,
	अणु
		.id = "INT34C3",
		.drv_name = "bxt_tdf8532",
		.machine_quirk = apl_quirk,
		.sof_fw_filename = "sof-apl.ri",
		.sof_tplg_filename = "sof-apl-tdf8532.tplg",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(snd_soc_acpi_पूर्णांकel_bxt_machines);
