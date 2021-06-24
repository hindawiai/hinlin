<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
//
// This file is provided under a dual BSD/GPLv2 license.  When using or
// redistributing this file, you may करो so under either license.
//
// Copyright(c) 2018-2021 Intel Corporation. All rights reserved.
//
// Author: Liam Girdwood <liam.r.girdwood@linux.पूर्णांकel.com>
//

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <sound/soc-acpi.h>
#समावेश <sound/soc-acpi-पूर्णांकel-match.h>
#समावेश <sound/sof.h>
#समावेश "../ops.h"
#समावेश "../sof-pci-dev.h"

/* platक्रमm specअगरic devices */
#समावेश "hda.h"

अटल स्थिर काष्ठा sof_dev_desc bxt_desc = अणु
	.machines		= snd_soc_acpi_पूर्णांकel_bxt_machines,
	.use_acpi_target_states	= true,
	.resindex_lpe_base	= 0,
	.resindex_pcicfg_base	= -1,
	.resindex_imr_base	= -1,
	.irqindex_host_ipc	= -1,
	.resindex_dma_base	= -1,
	.chip_info = &apl_chip_info,
	.शेष_fw_path = "intel/sof",
	.शेष_tplg_path = "intel/sof-tplg",
	.शेष_fw_filename = "sof-apl.ri",
	.nocodec_tplg_filename = "sof-apl-nocodec.tplg",
	.ops = &sof_apl_ops,
पूर्ण;

अटल स्थिर काष्ठा sof_dev_desc glk_desc = अणु
	.machines		= snd_soc_acpi_पूर्णांकel_glk_machines,
	.use_acpi_target_states	= true,
	.resindex_lpe_base	= 0,
	.resindex_pcicfg_base	= -1,
	.resindex_imr_base	= -1,
	.irqindex_host_ipc	= -1,
	.resindex_dma_base	= -1,
	.chip_info = &apl_chip_info,
	.शेष_fw_path = "intel/sof",
	.शेष_tplg_path = "intel/sof-tplg",
	.शेष_fw_filename = "sof-glk.ri",
	.nocodec_tplg_filename = "sof-glk-nocodec.tplg",
	.ops = &sof_apl_ops,
पूर्ण;

/* PCI IDs */
अटल स्थिर काष्ठा pci_device_id sof_pci_ids[] = अणु
	अणु PCI_DEVICE(0x8086, 0x5a98), /* BXT-P (ApolloLake) */
		.driver_data = (अचिन्हित दीर्घ)&bxt_descपूर्ण,
	अणु PCI_DEVICE(0x8086, 0x1a98),/* BXT-T */
		.driver_data = (अचिन्हित दीर्घ)&bxt_descपूर्ण,
	अणु PCI_DEVICE(0x8086, 0x3198), /* GeminiLake */
		.driver_data = (अचिन्हित दीर्घ)&glk_descपूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, sof_pci_ids);

/* pci_driver definition */
अटल काष्ठा pci_driver snd_sof_pci_पूर्णांकel_apl_driver = अणु
	.name = "sof-audio-pci-intel-apl",
	.id_table = sof_pci_ids,
	.probe = hda_pci_पूर्णांकel_probe,
	.हटाओ = sof_pci_हटाओ,
	.shutकरोwn = sof_pci_shutकरोwn,
	.driver = अणु
		.pm = &sof_pci_pm,
	पूर्ण,
पूर्ण;
module_pci_driver(snd_sof_pci_पूर्णांकel_apl_driver);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_IMPORT_NS(SND_SOC_SOF_INTEL_HDA_COMMON);
MODULE_IMPORT_NS(SND_SOC_SOF_PCI_DEV);
