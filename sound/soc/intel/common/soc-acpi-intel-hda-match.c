<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright (c) 2018, Intel Corporation.

/*
 * soc-acpi-पूर्णांकel-hda-match.c - tables and support क्रम HDA+ACPI क्रमागतeration.
 *
 */

#समावेश <sound/soc-acpi.h>
#समावेश <sound/soc-acpi-पूर्णांकel-match.h>
#समावेश "../skylake/skl.h"

अटल काष्ठा skl_machine_pdata hda_pdata = अणु
	.use_tplg_pcm = true,
पूर्ण;

काष्ठा snd_soc_acpi_mach snd_soc_acpi_पूर्णांकel_hda_machines[] = अणु
	अणु
		/* .id is not used in this file */
		.drv_name = "skl_hda_dsp_generic",

		/* .fw_filename is dynamically set in skylake driver */

		/* .sof_fw_filename is dynamically set in sof/पूर्णांकel driver */

		.sof_tplg_filename = "sof-hda-generic.tplg",

		/*
		 * .machine_quirk and .quirk_data are not used here but
		 * can be used अगर we need a more complicated machine driver
		 * combining HDA+other device (e.g. DMIC).
		 */
		.pdata = &hda_pdata,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(snd_soc_acpi_पूर्णांकel_hda_machines);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Intel Common ACPI Match module");
