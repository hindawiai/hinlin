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
#समावेश "shim.h"

अटल काष्ठा snd_soc_acpi_mach sof_tng_machines[] = अणु
	अणु
		.id = "INT343A",
		.drv_name = "edison",
		.sof_fw_filename = "sof-byt.ri",
		.sof_tplg_filename = "sof-byt.tplg",
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा sof_dev_desc tng_desc = अणु
	.machines		= sof_tng_machines,
	.resindex_lpe_base	= 3,	/* IRAM, but subtract IRAM offset */
	.resindex_pcicfg_base	= -1,
	.resindex_imr_base	= 0,
	.irqindex_host_ipc	= -1,
	.resindex_dma_base	= -1,
	.chip_info = &tng_chip_info,
	.शेष_fw_path = "intel/sof",
	.शेष_tplg_path = "intel/sof-tplg",
	.शेष_fw_filename = "sof-byt.ri",
	.nocodec_tplg_filename = "sof-byt.tplg",
	.ops = &sof_tng_ops,
पूर्ण;

/* PCI IDs */
अटल स्थिर काष्ठा pci_device_id sof_pci_ids[] = अणु
	अणु PCI_DEVICE(0x8086, 0x119a),
		.driver_data = (अचिन्हित दीर्घ)&tng_descपूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, sof_pci_ids);

/* pci_driver definition */
अटल काष्ठा pci_driver snd_sof_pci_पूर्णांकel_tng_driver = अणु
	.name = "sof-audio-pci-intel-tng",
	.id_table = sof_pci_ids,
	.probe = sof_pci_probe,
	.हटाओ = sof_pci_हटाओ,
	.shutकरोwn = sof_pci_shutकरोwn,
	.driver = अणु
		.pm = &sof_pci_pm,
	पूर्ण,
पूर्ण;
module_pci_driver(snd_sof_pci_पूर्णांकel_tng_driver);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_IMPORT_NS(SND_SOC_SOF_MERRIFIELD);
MODULE_IMPORT_NS(SND_SOC_SOF_PCI_DEV);
