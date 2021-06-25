<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * soc-acpi-पूर्णांकel-hsw-bdw-match.c - tables and support क्रम ACPI क्रमागतeration.
 *
 * Copyright (c) 2017, Intel Corporation.
 */

#समावेश <linux/dmi.h>
#समावेश <sound/soc-acpi.h>
#समावेश <sound/soc-acpi-पूर्णांकel-match.h>

काष्ठा snd_soc_acpi_mach snd_soc_acpi_पूर्णांकel_haswell_machines[] = अणु
	अणु
		.id = "INT33CA",
		.drv_name = "haswell-audio",
		.fw_filename = "intel/IntcSST1.bin",
		.sof_fw_filename = "sof-hsw.ri",
		.sof_tplg_filename = "sof-hsw.tplg",
	पूर्ण,
	अणुपूर्ण
पूर्ण;
EXPORT_SYMBOL_GPL(snd_soc_acpi_पूर्णांकel_haswell_machines);

काष्ठा snd_soc_acpi_mach snd_soc_acpi_पूर्णांकel_broadwell_machines[] = अणु
	अणु
		.id = "INT343A",
		.drv_name = "broadwell-audio",
		.fw_filename =  "intel/IntcSST2.bin",
		.sof_fw_filename = "sof-bdw.ri",
		.sof_tplg_filename = "sof-bdw-rt286.tplg",
	पूर्ण,
	अणु
		.id = "10EC5650",
		.drv_name = "bdw-rt5650",
		.fw_filename = "intel/IntcSST2.bin",
		.sof_fw_filename = "sof-bdw.ri",
		.sof_tplg_filename = "sof-bdw-rt5650.tplg",
	पूर्ण,
	अणु
		.id = "RT5677CE",
		.drv_name = "bdw-rt5677",
		.fw_filename =  "intel/IntcSST2.bin",
		.sof_fw_filename = "sof-bdw.ri",
		.sof_tplg_filename = "sof-bdw-rt5677.tplg",
	पूर्ण,
	अणु
		.id = "INT33CA",
		.drv_name = "haswell-audio",
		.fw_filename = "intel/IntcSST2.bin",
		.sof_fw_filename = "sof-bdw.ri",
		.sof_tplg_filename = "sof-bdw-rt5640.tplg",
	पूर्ण,
	अणुपूर्ण
पूर्ण;
EXPORT_SYMBOL_GPL(snd_soc_acpi_पूर्णांकel_broadwell_machines);
