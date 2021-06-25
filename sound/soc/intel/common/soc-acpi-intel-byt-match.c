<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * soc-acpi-पूर्णांकel-byt-match.c - tables and support क्रम BYT ACPI क्रमागतeration.
 *
 * Copyright (c) 2017, Intel Corporation.
 */

#समावेश <linux/dmi.h>
#समावेश <sound/soc-acpi.h>
#समावेश <sound/soc-acpi-पूर्णांकel-match.h>

अटल अचिन्हित दीर्घ byt_machine_id;

#घोषणा BYT_RT5672       1
#घोषणा BYT_POV_P1006W   2

अटल पूर्णांक byt_rt5672_quirk_cb(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	byt_machine_id = BYT_RT5672;
	वापस 1;
पूर्ण

अटल पूर्णांक byt_pov_p1006w_quirk_cb(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	byt_machine_id = BYT_POV_P1006W;
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id byt_table[] = अणु
	अणु
		.callback = byt_rt5672_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad 8"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = byt_rt5672_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad 10"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = byt_rt5672_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad Tablet B"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = byt_rt5672_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "Lenovo Miix 2 10"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Poपूर्णांक of View mobii wपूर्णांकab p1006w (v1.0) */
		.callback = byt_pov_p1006w_quirk_cb,
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Insyde"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "BayTrail"),
			/* Note 105b is Foxcon's USB/PCI venकरोr id */
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "105B"),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "0E57"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Aegex 10 tablet (RU2) */
		.callback = byt_rt5672_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "AEGEX"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "RU2"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Dell Venue 10 Pro 5055 */
		.callback = byt_rt5672_quirk_cb,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Venue 10 Pro 5055"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

/* Various devices use an ACPI id of 10EC5640 जबतक using a rt5672 codec */
अटल काष्ठा snd_soc_acpi_mach byt_rt5672 = अणु
	.id = "10EC5640",
	.drv_name = "cht-bsw-rt5672",
	.fw_filename = "intel/fw_sst_0f28.bin",
	.board = "cht-bsw",
	.sof_fw_filename = "sof-byt.ri",
	.sof_tplg_filename = "sof-byt-rt5670.tplg",
पूर्ण;

अटल काष्ठा snd_soc_acpi_mach byt_pov_p1006w = अणु
	.id = "10EC5640",
	.drv_name = "bytcr_rt5651",
	.fw_filename = "intel/fw_sst_0f28.bin",
	.board = "bytcr_rt5651",
	.sof_fw_filename = "sof-byt.ri",
	.sof_tplg_filename = "sof-byt-rt5651.tplg",
पूर्ण;

अटल काष्ठा snd_soc_acpi_mach *byt_quirk(व्योम *arg)
अणु
	काष्ठा snd_soc_acpi_mach *mach = arg;

	dmi_check_प्रणाली(byt_table);

	चयन (byt_machine_id) अणु
	हाल BYT_RT5672:
		वापस &byt_rt5672;
	हाल BYT_POV_P1006W:
		वापस &byt_pov_p1006w;
	शेष:
		वापस mach;
	पूर्ण
पूर्ण

काष्ठा snd_soc_acpi_mach  snd_soc_acpi_पूर्णांकel_baytrail_machines[] = अणु
	अणु
		.id = "10EC5640",
		.drv_name = "bytcr_rt5640",
		.fw_filename = "intel/fw_sst_0f28.bin",
		.board = "bytcr_rt5640",
		.machine_quirk = byt_quirk,
		.sof_fw_filename = "sof-byt.ri",
		.sof_tplg_filename = "sof-byt-rt5640.tplg",
	पूर्ण,
	अणु
		.id = "10EC5642",
		.drv_name = "bytcr_rt5640",
		.fw_filename = "intel/fw_sst_0f28.bin",
		.board = "bytcr_rt5640",
		.sof_fw_filename = "sof-byt.ri",
		.sof_tplg_filename = "sof-byt-rt5640.tplg",
	पूर्ण,
	अणु
		.id = "INTCCFFD",
		.drv_name = "bytcr_rt5640",
		.fw_filename = "intel/fw_sst_0f28.bin",
		.board = "bytcr_rt5640",
		.sof_fw_filename = "sof-byt.ri",
		.sof_tplg_filename = "sof-byt-rt5640.tplg",
	पूर्ण,
	अणु
		.id = "10EC5651",
		.drv_name = "bytcr_rt5651",
		.fw_filename = "intel/fw_sst_0f28.bin",
		.board = "bytcr_rt5651",
		.sof_fw_filename = "sof-byt.ri",
		.sof_tplg_filename = "sof-byt-rt5651.tplg",
	पूर्ण,
	अणु
		.id = "WM510204",
		.drv_name = "bytcr_wm5102",
		.fw_filename = "intel/fw_sst_0f28.bin",
		.board = "bytcr_wm5102",
		.sof_fw_filename = "sof-byt.ri",
		.sof_tplg_filename = "sof-byt-wm5102.tplg",
	पूर्ण,
	अणु
		.id = "WM510205",
		.drv_name = "bytcr_wm5102",
		.fw_filename = "intel/fw_sst_0f28.bin",
		.board = "bytcr_wm5102",
		.sof_fw_filename = "sof-byt.ri",
		.sof_tplg_filename = "sof-byt-wm5102.tplg",
	पूर्ण,
	अणु
		.id = "DLGS7212",
		.drv_name = "bytcht_da7213",
		.fw_filename = "intel/fw_sst_0f28.bin",
		.board = "bytcht_da7213",
		.sof_fw_filename = "sof-byt.ri",
		.sof_tplg_filename = "sof-byt-da7213.tplg",
	पूर्ण,
	अणु
		.id = "DLGS7213",
		.drv_name = "bytcht_da7213",
		.fw_filename = "intel/fw_sst_0f28.bin",
		.board = "bytcht_da7213",
		.sof_fw_filename = "sof-byt.ri",
		.sof_tplg_filename = "sof-byt-da7213.tplg",
	पूर्ण,
	अणु
		.id = "ESSX8316",
		.drv_name = "bytcht_es8316",
		.fw_filename = "intel/fw_sst_0f28.bin",
		.board = "bytcht_es8316",
		.sof_fw_filename = "sof-byt.ri",
		.sof_tplg_filename = "sof-byt-es8316.tplg",
	पूर्ण,
	अणु
		.id = "10EC5682",
		.drv_name = "sof_rt5682",
		.sof_fw_filename = "sof-byt.ri",
		.sof_tplg_filename = "sof-byt-rt5682.tplg",
	पूर्ण,
	/* some Baytrail platक्रमms rely on RT5645, use CHT machine driver */
	अणु
		.id = "10EC5645",
		.drv_name = "cht-bsw-rt5645",
		.fw_filename = "intel/fw_sst_0f28.bin",
		.board = "cht-bsw",
		.sof_fw_filename = "sof-byt.ri",
		.sof_tplg_filename = "sof-byt-rt5645.tplg",
	पूर्ण,
	अणु
		.id = "10EC5648",
		.drv_name = "cht-bsw-rt5645",
		.fw_filename = "intel/fw_sst_0f28.bin",
		.board = "cht-bsw",
		.sof_fw_filename = "sof-byt.ri",
		.sof_tplg_filename = "sof-byt-rt5645.tplg",
	पूर्ण,
	/* use CHT driver to Baytrail Chromebooks */
	अणु
		.id = "193C9890",
		.drv_name = "cht-bsw-max98090",
		.fw_filename = "intel/fw_sst_0f28.bin",
		.board = "cht-bsw",
		.sof_fw_filename = "sof-byt.ri",
		.sof_tplg_filename = "sof-byt-max98090.tplg",
	पूर्ण,
	अणु
		.id = "14F10720",
		.drv_name = "bytcht_cx2072x",
		.fw_filename = "intel/fw_sst_0f28.bin",
		.board = "bytcht_cx2072x",
		.sof_fw_filename = "sof-byt.ri",
		.sof_tplg_filename = "sof-byt-cx2072x.tplg",
	पूर्ण,
#अगर IS_ENABLED(CONFIG_SND_SOC_INTEL_BYT_CHT_NOCODEC_MACH)
	/*
	 * This is always last in the table so that it is selected only when
	 * enabled explicitly and there is no codec-related inक्रमmation in SSDT
	 */
	अणु
		.id = "80860F28",
		.drv_name = "bytcht_nocodec",
		.fw_filename = "intel/fw_sst_0f28.bin",
		.board = "bytcht_nocodec",
	पूर्ण,
#पूर्ण_अगर
	अणुपूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(snd_soc_acpi_पूर्णांकel_baytrail_machines);
