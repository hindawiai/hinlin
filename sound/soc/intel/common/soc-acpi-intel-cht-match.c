<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * soc-acpi-पूर्णांकel-cht-match.c - tables and support क्रम CHT ACPI क्रमागतeration.
 *
 * Copyright (c) 2017, Intel Corporation.
 */

#समावेश <linux/dmi.h>
#समावेश <sound/soc-acpi.h>
#समावेश <sound/soc-acpi-पूर्णांकel-match.h>

अटल अचिन्हित दीर्घ cht_machine_id;

#घोषणा CHT_SURFACE_MACH 1

अटल पूर्णांक cht_surface_quirk_cb(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	cht_machine_id = CHT_SURFACE_MACH;
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id cht_table[] = अणु
	अणु
		.callback = cht_surface_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Microsoft Corporation"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Surface 3"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा snd_soc_acpi_mach cht_surface_mach = अणु
	.id = "10EC5640",
	.drv_name = "cht-bsw-rt5645",
	.fw_filename = "intel/fw_sst_22a8.bin",
	.board = "cht-bsw",
	.sof_fw_filename = "sof-cht.ri",
	.sof_tplg_filename = "sof-cht-rt5645.tplg",
पूर्ण;

अटल काष्ठा snd_soc_acpi_mach *cht_quirk(व्योम *arg)
अणु
	काष्ठा snd_soc_acpi_mach *mach = arg;

	dmi_check_प्रणाली(cht_table);

	अगर (cht_machine_id == CHT_SURFACE_MACH)
		वापस &cht_surface_mach;
	अन्यथा
		वापस mach;
पूर्ण

/* Cherryview-based platक्रमms: CherryTrail and Braswell */
काष्ठा snd_soc_acpi_mach  snd_soc_acpi_पूर्णांकel_cherrytrail_machines[] = अणु
	अणु
		.id = "10EC5670",
		.drv_name = "cht-bsw-rt5672",
		.fw_filename = "intel/fw_sst_22a8.bin",
		.board = "cht-bsw",
		.sof_fw_filename = "sof-cht.ri",
		.sof_tplg_filename = "sof-cht-rt5670.tplg",
	पूर्ण,
	अणु
		.id = "10EC5672",
		.drv_name = "cht-bsw-rt5672",
		.fw_filename = "intel/fw_sst_22a8.bin",
		.board = "cht-bsw",
		.sof_fw_filename = "sof-cht.ri",
		.sof_tplg_filename = "sof-cht-rt5670.tplg",
	पूर्ण,
	अणु
		.id = "10EC5645",
		.drv_name = "cht-bsw-rt5645",
		.fw_filename = "intel/fw_sst_22a8.bin",
		.board = "cht-bsw",
		.sof_fw_filename = "sof-cht.ri",
		.sof_tplg_filename = "sof-cht-rt5645.tplg",
	पूर्ण,
	अणु
		.id = "10EC5650",
		.drv_name = "cht-bsw-rt5645",
		.fw_filename = "intel/fw_sst_22a8.bin",
		.board = "cht-bsw",
		.sof_fw_filename = "sof-cht.ri",
		.sof_tplg_filename = "sof-cht-rt5645.tplg",
	पूर्ण,
	अणु
		.id = "10EC3270",
		.drv_name = "cht-bsw-rt5645",
		.fw_filename = "intel/fw_sst_22a8.bin",
		.board = "cht-bsw",
		.sof_fw_filename = "sof-cht.ri",
		.sof_tplg_filename = "sof-cht-rt5645.tplg",
	पूर्ण,
	अणु
		.id = "193C9890",
		.drv_name = "cht-bsw-max98090",
		.fw_filename = "intel/fw_sst_22a8.bin",
		.board = "cht-bsw",
		.sof_fw_filename = "sof-cht.ri",
		.sof_tplg_filename = "sof-cht-max98090.tplg",
	पूर्ण,
	अणु
		.id = "10508824",
		.drv_name = "cht-bsw-nau8824",
		.fw_filename = "intel/fw_sst_22a8.bin",
		.board = "cht-bsw",
		.sof_fw_filename = "sof-cht.ri",
		.sof_tplg_filename = "sof-cht-nau8824.tplg",
	पूर्ण,
	अणु
		.id = "DLGS7212",
		.drv_name = "bytcht_da7213",
		.fw_filename = "intel/fw_sst_22a8.bin",
		.board = "bytcht_da7213",
		.sof_fw_filename = "sof-cht.ri",
		.sof_tplg_filename = "sof-cht-da7213.tplg",
	पूर्ण,
	अणु
		.id = "DLGS7213",
		.drv_name = "bytcht_da7213",
		.fw_filename = "intel/fw_sst_22a8.bin",
		.board = "bytcht_da7213",
		.sof_fw_filename = "sof-cht.ri",
		.sof_tplg_filename = "sof-cht-da7213.tplg",
	पूर्ण,
	अणु
		.id = "ESSX8316",
		.drv_name = "bytcht_es8316",
		.fw_filename = "intel/fw_sst_22a8.bin",
		.board = "bytcht_es8316",
		.sof_fw_filename = "sof-cht.ri",
		.sof_tplg_filename = "sof-cht-es8316.tplg",
	पूर्ण,
	/* some CHT-T platक्रमms rely on RT5640, use Baytrail machine driver */
	अणु
		.id = "10EC5640",
		.drv_name = "bytcr_rt5640",
		.fw_filename = "intel/fw_sst_22a8.bin",
		.board = "bytcr_rt5640",
		.machine_quirk = cht_quirk,
		.sof_fw_filename = "sof-cht.ri",
		.sof_tplg_filename = "sof-cht-rt5640.tplg",
	पूर्ण,
	अणु
		.id = "10EC3276",
		.drv_name = "bytcr_rt5640",
		.fw_filename = "intel/fw_sst_22a8.bin",
		.board = "bytcr_rt5640",
		.sof_fw_filename = "sof-cht.ri",
		.sof_tplg_filename = "sof-cht-rt5640.tplg",
	पूर्ण,
	अणु
		.id = "10EC5682",
		.drv_name = "sof_rt5682",
		.sof_fw_filename = "sof-cht.ri",
		.sof_tplg_filename = "sof-cht-rt5682.tplg",
	पूर्ण,
	/* some CHT-T platक्रमms rely on RT5651, use Baytrail machine driver */
	अणु
		.id = "10EC5651",
		.drv_name = "bytcr_rt5651",
		.fw_filename = "intel/fw_sst_22a8.bin",
		.board = "bytcr_rt5651",
		.sof_fw_filename = "sof-cht.ri",
		.sof_tplg_filename = "sof-cht-rt5651.tplg",
	पूर्ण,
	अणु
		.id = "14F10720",
		.drv_name = "bytcht_cx2072x",
		.fw_filename = "intel/fw_sst_22a8.bin",
		.board = "bytcht_cx2072x",
		.sof_fw_filename = "sof-cht.ri",
		.sof_tplg_filename = "sof-cht-cx2072x.tplg",
	पूर्ण,
	अणु
		.id = "104C5122",
		.drv_name = "sof_pcm512x",
		.sof_fw_filename = "sof-cht.ri",
		.sof_tplg_filename = "sof-cht-src-50khz-pcm512x.tplg",
	पूर्ण,

#अगर IS_ENABLED(CONFIG_SND_SOC_INTEL_BYT_CHT_NOCODEC_MACH)
	/*
	 * This is always last in the table so that it is selected only when
	 * enabled explicitly and there is no codec-related inक्रमmation in SSDT
	 */
	अणु
		.id = "808622A8",
		.drv_name = "bytcht_nocodec",
		.fw_filename = "intel/fw_sst_22a8.bin",
		.board = "bytcht_nocodec",
	पूर्ण,
#पूर्ण_अगर
	अणुपूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(snd_soc_acpi_पूर्णांकel_cherrytrail_machines);
