<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * Copyright(c) 2018 Intel Corporation. All rights reserved.
 *
 * Author: Liam Girdwood <liam.r.girdwood@linux.पूर्णांकel.com>
 */

#अगर_अघोषित __INCLUDE_SOUND_SOF_H
#घोषणा __INCLUDE_SOUND_SOF_H

#समावेश <linux/pci.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-acpi.h>

काष्ठा snd_sof_dsp_ops;

/*
 * SOF Platक्रमm data.
 */
काष्ठा snd_sof_pdata अणु
	स्थिर काष्ठा firmware *fw;
	स्थिर अक्षर *name;
	स्थिर अक्षर *platक्रमm;

	काष्ठा device *dev;

	/* indicate how many first bytes shouldn't be loaded पूर्णांकo DSP memory. */
	माप_प्रकार fw_offset;

	/*
	 * notअगरication callback used अगर the hardware initialization
	 * can take समय or is handled in a workqueue. This callback
	 * can be used by the caller to e.g. enable runसमय_pm
	 * or limit functionality until all low-level inits are
	 * complete.
	 */
	व्योम (*sof_probe_complete)(काष्ठा device *dev);

	/* descriptor */
	स्थिर काष्ठा sof_dev_desc *desc;

	/* firmware and topology filenames */
	स्थिर अक्षर *fw_filename_prefix;
	स्थिर अक्षर *fw_filename;
	स्थिर अक्षर *tplg_filename_prefix;
	स्थिर अक्षर *tplg_filename;

	/* machine */
	काष्ठा platक्रमm_device *pdev_mach;
	स्थिर काष्ठा snd_soc_acpi_mach *machine;

	व्योम *hw_pdata;
पूर्ण;

/*
 * Descriptor used क्रम setting up SOF platक्रमm data. This is used when
 * ACPI/PCI data is missing or mapped dअगरferently.
 */
काष्ठा sof_dev_desc अणु
	/* list of machines using this configuration */
	काष्ठा snd_soc_acpi_mach *machines;

	/* alternate list of machines using this configuration */
	काष्ठा snd_soc_acpi_mach *alt_machines;

	bool use_acpi_target_states;

	/* Platक्रमm resource indexes in BAR / ACPI resources. */
	/* Must set to -1 अगर not used - add new items to end */
	पूर्णांक resindex_lpe_base;
	पूर्णांक resindex_pcicfg_base;
	पूर्णांक resindex_imr_base;
	पूर्णांक irqindex_host_ipc;
	पूर्णांक resindex_dma_base;

	/* DMA only valid when resindex_dma_base != -1*/
	पूर्णांक dma_engine;
	पूर्णांक dma_size;

	/* IPC समयouts in ms */
	पूर्णांक ipc_समयout;
	पूर्णांक boot_समयout;

	/* chip inक्रमmation क्रम dsp */
	स्थिर व्योम *chip_info;

	/* शेषs क्रम no codec mode */
	स्थिर अक्षर *nocodec_tplg_filename;

	/* शेषs paths क्रम firmware and topology files */
	स्थिर अक्षर *शेष_fw_path;
	स्थिर अक्षर *शेष_tplg_path;

	/* शेष firmware name */
	स्थिर अक्षर *शेष_fw_filename;

	स्थिर काष्ठा snd_sof_dsp_ops *ops;
पूर्ण;

पूर्णांक sof_dai_get_mclk(काष्ठा snd_soc_pcm_runसमय *rtd);

#पूर्ण_अगर
