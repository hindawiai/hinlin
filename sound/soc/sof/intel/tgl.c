<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
//
// Copyright(c) 2020 Intel Corporation. All rights reserved.
//
// Authors: Ranjani Sridharan <ranjani.sridharan@linux.पूर्णांकel.com>
//

/*
 * Hardware पूर्णांकerface क्रम audio DSP on Tigerlake.
 */

#समावेश "../ops.h"
#समावेश "hda.h"
#समावेश "hda-ipc.h"
#समावेश "../sof-audio.h"

अटल स्थिर काष्ठा snd_sof_debugfs_map tgl_dsp_debugfs[] = अणु
	अणु"hda", HDA_DSP_HDA_BAR, 0, 0x4000, SOF_DEBUGFS_ACCESS_ALWAYSपूर्ण,
	अणु"pp", HDA_DSP_PP_BAR,  0, 0x1000, SOF_DEBUGFS_ACCESS_ALWAYSपूर्ण,
	अणु"dsp", HDA_DSP_BAR,  0, 0x10000, SOF_DEBUGFS_ACCESS_ALWAYSपूर्ण,
पूर्ण;

/* Tigerlake ops */
स्थिर काष्ठा snd_sof_dsp_ops sof_tgl_ops = अणु
	/* probe/हटाओ/shutकरोwn */
	.probe		= hda_dsp_probe,
	.हटाओ		= hda_dsp_हटाओ,
	.shutकरोwn	= hda_dsp_shutकरोwn,

	/* Register IO */
	.ग_लिखो		= sof_io_ग_लिखो,
	.पढ़ो		= sof_io_पढ़ो,
	.ग_लिखो64	= sof_io_ग_लिखो64,
	.पढ़ो64		= sof_io_पढ़ो64,

	/* Block IO */
	.block_पढ़ो	= sof_block_पढ़ो,
	.block_ग_लिखो	= sof_block_ग_लिखो,

	/* करोorbell */
	.irq_thपढ़ो	= cnl_ipc_irq_thपढ़ो,

	/* ipc */
	.send_msg	= cnl_ipc_send_msg,
	.fw_पढ़ोy	= sof_fw_पढ़ोy,
	.get_mailbox_offset = hda_dsp_ipc_get_mailbox_offset,
	.get_winकरोw_offset = hda_dsp_ipc_get_winकरोw_offset,

	.ipc_msg_data	= hda_ipc_msg_data,
	.ipc_pcm_params	= hda_ipc_pcm_params,

	/* machine driver */
	.machine_select = hda_machine_select,
	.machine_रेजिस्टर = sof_machine_रेजिस्टर,
	.machine_unरेजिस्टर = sof_machine_unरेजिस्टर,
	.set_mach_params = hda_set_mach_params,

	/* debug */
	.debug_map	= tgl_dsp_debugfs,
	.debug_map_count	= ARRAY_SIZE(tgl_dsp_debugfs),
	.dbg_dump	= hda_dsp_dump,
	.ipc_dump	= cnl_ipc_dump,

	/* stream callbacks */
	.pcm_खोलो	= hda_dsp_pcm_खोलो,
	.pcm_बंद	= hda_dsp_pcm_बंद,
	.pcm_hw_params	= hda_dsp_pcm_hw_params,
	.pcm_hw_मुक्त	= hda_dsp_stream_hw_मुक्त,
	.pcm_trigger	= hda_dsp_pcm_trigger,
	.pcm_poपूर्णांकer	= hda_dsp_pcm_poपूर्णांकer,

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA_PROBES)
	/* probe callbacks */
	.probe_assign	= hda_probe_compr_assign,
	.probe_मुक्त	= hda_probe_compr_मुक्त,
	.probe_set_params	= hda_probe_compr_set_params,
	.probe_trigger	= hda_probe_compr_trigger,
	.probe_poपूर्णांकer	= hda_probe_compr_poपूर्णांकer,
#पूर्ण_अगर

	/* firmware loading */
	.load_firmware = snd_sof_load_firmware_raw,

	/* pre/post fw run */
	.pre_fw_run = hda_dsp_pre_fw_run,
	.post_fw_run = hda_dsp_post_fw_run,

	/* parse platक्रमm specअगरic extended manअगरest */
	.parse_platक्रमm_ext_manअगरest = hda_dsp_ext_man_get_cavs_config_data,

	/* dsp core घातer up/करोwn */
	.core_घातer_up = hda_dsp_enable_core,
	.core_घातer_करोwn = hda_dsp_core_reset_घातer_करोwn,

	/* firmware run */
	.run = hda_dsp_cl_boot_firmware_iccmax,

	/* trace callback */
	.trace_init = hda_dsp_trace_init,
	.trace_release = hda_dsp_trace_release,
	.trace_trigger = hda_dsp_trace_trigger,

	/* DAI drivers */
	.drv		= skl_dai,
	.num_drv	= SOF_SKL_NUM_DAIS,

	/* PM */
	.suspend		= hda_dsp_suspend,
	.resume			= hda_dsp_resume,
	.runसमय_suspend	= hda_dsp_runसमय_suspend,
	.runसमय_resume		= hda_dsp_runसमय_resume,
	.runसमय_idle		= hda_dsp_runसमय_idle,
	.set_hw_params_upon_resume = hda_dsp_set_hw_params_upon_resume,
	.set_घातer_state	= hda_dsp_set_घातer_state,

	/* ALSA HW info flags */
	.hw_info =	SNDRV_PCM_INFO_MMAP |
			SNDRV_PCM_INFO_MMAP_VALID |
			SNDRV_PCM_INFO_INTERLEAVED |
			SNDRV_PCM_INFO_PAUSE |
			SNDRV_PCM_INFO_NO_PERIOD_WAKEUP,

	.arch_ops = &sof_xtensa_arch_ops,
पूर्ण;
EXPORT_SYMBOL_NS(sof_tgl_ops, SND_SOC_SOF_INTEL_HDA_COMMON);

स्थिर काष्ठा sof_पूर्णांकel_dsp_desc tgl_chip_info = अणु
	/* Tigerlake , Alderlake */
	.cores_num = 4,
	.init_core_mask = 1,
	.host_managed_cores_mask = BIT(0),
	.ipc_req = CNL_DSP_REG_HIPCIDR,
	.ipc_req_mask = CNL_DSP_REG_HIPCIDR_BUSY,
	.ipc_ack = CNL_DSP_REG_HIPCIDA,
	.ipc_ack_mask = CNL_DSP_REG_HIPCIDA_DONE,
	.ipc_ctl = CNL_DSP_REG_HIPCCTL,
	.rom_init_समयout	= 300,
	.ssp_count = ICL_SSP_COUNT,
	.ssp_base_offset = CNL_SSP_BASE_OFFSET,
पूर्ण;
EXPORT_SYMBOL_NS(tgl_chip_info, SND_SOC_SOF_INTEL_HDA_COMMON);

स्थिर काष्ठा sof_पूर्णांकel_dsp_desc tglh_chip_info = अणु
	/* Tigerlake-H */
	.cores_num = 2,
	.init_core_mask = 1,
	.host_managed_cores_mask = BIT(0),
	.ipc_req = CNL_DSP_REG_HIPCIDR,
	.ipc_req_mask = CNL_DSP_REG_HIPCIDR_BUSY,
	.ipc_ack = CNL_DSP_REG_HIPCIDA,
	.ipc_ack_mask = CNL_DSP_REG_HIPCIDA_DONE,
	.ipc_ctl = CNL_DSP_REG_HIPCCTL,
	.rom_init_समयout	= 300,
	.ssp_count = ICL_SSP_COUNT,
	.ssp_base_offset = CNL_SSP_BASE_OFFSET,
पूर्ण;
EXPORT_SYMBOL_NS(tglh_chip_info, SND_SOC_SOF_INTEL_HDA_COMMON);

स्थिर काष्ठा sof_पूर्णांकel_dsp_desc ehl_chip_info = अणु
	/* Elkhartlake */
	.cores_num = 4,
	.init_core_mask = 1,
	.host_managed_cores_mask = BIT(0),
	.ipc_req = CNL_DSP_REG_HIPCIDR,
	.ipc_req_mask = CNL_DSP_REG_HIPCIDR_BUSY,
	.ipc_ack = CNL_DSP_REG_HIPCIDA,
	.ipc_ack_mask = CNL_DSP_REG_HIPCIDA_DONE,
	.ipc_ctl = CNL_DSP_REG_HIPCCTL,
	.rom_init_समयout	= 300,
	.ssp_count = ICL_SSP_COUNT,
	.ssp_base_offset = CNL_SSP_BASE_OFFSET,
पूर्ण;
EXPORT_SYMBOL_NS(ehl_chip_info, SND_SOC_SOF_INTEL_HDA_COMMON);

स्थिर काष्ठा sof_पूर्णांकel_dsp_desc adls_chip_info = अणु
	/* Alderlake-S */
	.cores_num = 2,
	.init_core_mask = BIT(0),
	.host_managed_cores_mask = BIT(0),
	.ipc_req = CNL_DSP_REG_HIPCIDR,
	.ipc_req_mask = CNL_DSP_REG_HIPCIDR_BUSY,
	.ipc_ack = CNL_DSP_REG_HIPCIDA,
	.ipc_ack_mask = CNL_DSP_REG_HIPCIDA_DONE,
	.ipc_ctl = CNL_DSP_REG_HIPCCTL,
	.rom_init_समयout	= 300,
	.ssp_count = ICL_SSP_COUNT,
	.ssp_base_offset = CNL_SSP_BASE_OFFSET,
पूर्ण;
EXPORT_SYMBOL_NS(adls_chip_info, SND_SOC_SOF_INTEL_HDA_COMMON);
