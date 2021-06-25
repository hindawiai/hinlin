<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
//
// This file is provided under a dual BSD/GPLv2 license.  When using or
// redistributing this file, you may करो so under either license.
//
// Copyright(c) 2018 Intel Corporation. All rights reserved.
//
// Authors: Liam Girdwood <liam.r.girdwood@linux.पूर्णांकel.com>
//	    Ranjani Sridharan <ranjani.sridharan@linux.पूर्णांकel.com>
//	    Rander Wang <अक्रमer.wang@पूर्णांकel.com>
//          Keyon Jie <yang.jie@linux.पूर्णांकel.com>
//

/*
 * Hardware पूर्णांकerface क्रम audio DSP on Cannonlake.
 */

#समावेश "../ops.h"
#समावेश "hda.h"
#समावेश "hda-ipc.h"
#समावेश "../sof-audio.h"

अटल स्थिर काष्ठा snd_sof_debugfs_map cnl_dsp_debugfs[] = अणु
	अणु"hda", HDA_DSP_HDA_BAR, 0, 0x4000, SOF_DEBUGFS_ACCESS_ALWAYSपूर्ण,
	अणु"pp", HDA_DSP_PP_BAR,  0, 0x1000, SOF_DEBUGFS_ACCESS_ALWAYSपूर्ण,
	अणु"dsp", HDA_DSP_BAR,  0, 0x10000, SOF_DEBUGFS_ACCESS_ALWAYSपूर्ण,
पूर्ण;

अटल व्योम cnl_ipc_host_करोne(काष्ठा snd_sof_dev *sdev);
अटल व्योम cnl_ipc_dsp_करोne(काष्ठा snd_sof_dev *sdev);

irqवापस_t cnl_ipc_irq_thपढ़ो(पूर्णांक irq, व्योम *context)
अणु
	काष्ठा snd_sof_dev *sdev = context;
	u32 hipci;
	u32 hipcida;
	u32 hipctdr;
	u32 hipctdd;
	u32 msg;
	u32 msg_ext;
	bool ipc_irq = false;

	hipcida = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_BAR, CNL_DSP_REG_HIPCIDA);
	hipctdr = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_BAR, CNL_DSP_REG_HIPCTDR);
	hipctdd = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_BAR, CNL_DSP_REG_HIPCTDD);
	hipci = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_BAR, CNL_DSP_REG_HIPCIDR);

	/* reply message from DSP */
	अगर (hipcida & CNL_DSP_REG_HIPCIDA_DONE) अणु
		msg_ext = hipci & CNL_DSP_REG_HIPCIDR_MSG_MASK;
		msg = hipcida & CNL_DSP_REG_HIPCIDA_MSG_MASK;

		dev_vdbg(sdev->dev,
			 "ipc: firmware response, msg:0x%x, msg_ext:0x%x\n",
			 msg, msg_ext);

		/* mask Done पूर्णांकerrupt */
		snd_sof_dsp_update_bits(sdev, HDA_DSP_BAR,
					CNL_DSP_REG_HIPCCTL,
					CNL_DSP_REG_HIPCCTL_DONE, 0);

		spin_lock_irq(&sdev->ipc_lock);

		/* handle immediate reply from DSP core */
		hda_dsp_ipc_get_reply(sdev);
		snd_sof_ipc_reply(sdev, msg);

		cnl_ipc_dsp_करोne(sdev);

		spin_unlock_irq(&sdev->ipc_lock);

		ipc_irq = true;
	पूर्ण

	/* new message from DSP */
	अगर (hipctdr & CNL_DSP_REG_HIPCTDR_BUSY) अणु
		msg = hipctdr & CNL_DSP_REG_HIPCTDR_MSG_MASK;
		msg_ext = hipctdd & CNL_DSP_REG_HIPCTDD_MSG_MASK;

		dev_vdbg(sdev->dev,
			 "ipc: firmware initiated, msg:0x%x, msg_ext:0x%x\n",
			 msg, msg_ext);

		/* handle messages from DSP */
		अगर ((hipctdr & SOF_IPC_PANIC_MAGIC_MASK) ==
		   SOF_IPC_PANIC_MAGIC) अणु
			snd_sof_dsp_panic(sdev, HDA_DSP_PANIC_OFFSET(msg_ext));
		पूर्ण अन्यथा अणु
			snd_sof_ipc_msgs_rx(sdev);
		पूर्ण

		cnl_ipc_host_करोne(sdev);

		ipc_irq = true;
	पूर्ण

	अगर (!ipc_irq) अणु
		/*
		 * This पूर्णांकerrupt is not shared so no need to वापस IRQ_NONE.
		 */
		dev_dbg_ratelimited(sdev->dev,
				    "nothing to do in IPC IRQ thread\n");
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम cnl_ipc_host_करोne(काष्ठा snd_sof_dev *sdev)
अणु
	/*
	 * clear busy पूर्णांकerrupt to tell dsp controller this
	 * पूर्णांकerrupt has been accepted, not trigger it again
	 */
	snd_sof_dsp_update_bits_क्रमced(sdev, HDA_DSP_BAR,
				       CNL_DSP_REG_HIPCTDR,
				       CNL_DSP_REG_HIPCTDR_BUSY,
				       CNL_DSP_REG_HIPCTDR_BUSY);
	/*
	 * set करोne bit to ack dsp the msg has been
	 * processed and send reply msg to dsp
	 */
	snd_sof_dsp_update_bits_क्रमced(sdev, HDA_DSP_BAR,
				       CNL_DSP_REG_HIPCTDA,
				       CNL_DSP_REG_HIPCTDA_DONE,
				       CNL_DSP_REG_HIPCTDA_DONE);
पूर्ण

अटल व्योम cnl_ipc_dsp_करोne(काष्ठा snd_sof_dev *sdev)
अणु
	/*
	 * set DONE bit - tell DSP we have received the reply msg
	 * from DSP, and processed it, करोn't send more reply to host
	 */
	snd_sof_dsp_update_bits_क्रमced(sdev, HDA_DSP_BAR,
				       CNL_DSP_REG_HIPCIDA,
				       CNL_DSP_REG_HIPCIDA_DONE,
				       CNL_DSP_REG_HIPCIDA_DONE);

	/* unmask Done पूर्णांकerrupt */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAR,
				CNL_DSP_REG_HIPCCTL,
				CNL_DSP_REG_HIPCCTL_DONE,
				CNL_DSP_REG_HIPCCTL_DONE);
पूर्ण

अटल bool cnl_compact_ipc_compress(काष्ठा snd_sof_ipc_msg *msg,
				     u32 *dr, u32 *dd)
अणु
	काष्ठा sof_ipc_pm_gate *pm_gate;

	अगर (msg->header == (SOF_IPC_GLB_PM_MSG | SOF_IPC_PM_GATE)) अणु
		pm_gate = msg->msg_data;

		/* send the compact message via the primary रेजिस्टर */
		*dr = HDA_IPC_MSG_COMPACT | HDA_IPC_PM_GATE;

		/* send payload via the extended data रेजिस्टर */
		*dd = pm_gate->flags;

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

पूर्णांक cnl_ipc_send_msg(काष्ठा snd_sof_dev *sdev, काष्ठा snd_sof_ipc_msg *msg)
अणु
	काष्ठा sof_पूर्णांकel_hda_dev *hdev = sdev->pdata->hw_pdata;
	काष्ठा sof_ipc_cmd_hdr *hdr;
	u32 dr = 0;
	u32 dd = 0;

	/*
	 * Currently the only compact IPC supported is the PM_GATE
	 * IPC which is used क्रम transitioning the DSP between the
	 * D0I0 and D0I3 states. And these are sent only during the
	 * set_घातer_state() op. Thereक्रमe, there will never be a हाल
	 * that a compact IPC results in the DSP निकासing D0I3 without
	 * the host and FW being in sync.
	 */
	अगर (cnl_compact_ipc_compress(msg, &dr, &dd)) अणु
		/* send the message via IPC रेजिस्टरs */
		snd_sof_dsp_ग_लिखो(sdev, HDA_DSP_BAR, CNL_DSP_REG_HIPCIDD,
				  dd);
		snd_sof_dsp_ग_लिखो(sdev, HDA_DSP_BAR, CNL_DSP_REG_HIPCIDR,
				  CNL_DSP_REG_HIPCIDR_BUSY | dr);
		वापस 0;
	पूर्ण

	/* send the message via mailbox */
	sof_mailbox_ग_लिखो(sdev, sdev->host_box.offset, msg->msg_data,
			  msg->msg_size);
	snd_sof_dsp_ग_लिखो(sdev, HDA_DSP_BAR, CNL_DSP_REG_HIPCIDR,
			  CNL_DSP_REG_HIPCIDR_BUSY);

	hdr = msg->msg_data;

	/*
	 * Use mod_delayed_work() to schedule the delayed work
	 * to aव्योम scheduling multiple workqueue items when
	 * IPCs are sent at a high-rate. mod_delayed_work()
	 * modअगरies the समयr अगर the work is pending.
	 * Also, a new delayed work should not be queued after the
	 * CTX_SAVE IPC, which is sent beक्रमe the DSP enters D3.
	 */
	अगर (hdr->cmd != (SOF_IPC_GLB_PM_MSG | SOF_IPC_PM_CTX_SAVE))
		mod_delayed_work(प्रणाली_wq, &hdev->d0i3_work,
				 msecs_to_jअगरfies(SOF_HDA_D0I3_WORK_DELAY_MS));

	वापस 0;
पूर्ण

व्योम cnl_ipc_dump(काष्ठा snd_sof_dev *sdev)
अणु
	u32 hipcctl;
	u32 hipcida;
	u32 hipctdr;

	hda_ipc_irq_dump(sdev);

	/* पढ़ो IPC status */
	hipcida = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_BAR, CNL_DSP_REG_HIPCIDA);
	hipcctl = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_BAR, CNL_DSP_REG_HIPCCTL);
	hipctdr = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_BAR, CNL_DSP_REG_HIPCTDR);

	/* dump the IPC regs */
	/* TODO: parse the raw msg */
	dev_err(sdev->dev,
		"error: host status 0x%8.8x dsp status 0x%8.8x mask 0x%8.8x\n",
		hipcida, hipctdr, hipcctl);
पूर्ण

/* cannonlake ops */
स्थिर काष्ठा snd_sof_dsp_ops sof_cnl_ops = अणु
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
	.debug_map	= cnl_dsp_debugfs,
	.debug_map_count	= ARRAY_SIZE(cnl_dsp_debugfs),
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
	.run = hda_dsp_cl_boot_firmware,

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
EXPORT_SYMBOL_NS(sof_cnl_ops, SND_SOC_SOF_INTEL_HDA_COMMON);

स्थिर काष्ठा sof_पूर्णांकel_dsp_desc cnl_chip_info = अणु
	/* Cannonlake */
	.cores_num = 4,
	.init_core_mask = 1,
	.host_managed_cores_mask = GENMASK(3, 0),
	.ipc_req = CNL_DSP_REG_HIPCIDR,
	.ipc_req_mask = CNL_DSP_REG_HIPCIDR_BUSY,
	.ipc_ack = CNL_DSP_REG_HIPCIDA,
	.ipc_ack_mask = CNL_DSP_REG_HIPCIDA_DONE,
	.ipc_ctl = CNL_DSP_REG_HIPCCTL,
	.rom_init_समयout	= 300,
	.ssp_count = CNL_SSP_COUNT,
	.ssp_base_offset = CNL_SSP_BASE_OFFSET,
पूर्ण;
EXPORT_SYMBOL_NS(cnl_chip_info, SND_SOC_SOF_INTEL_HDA_COMMON);

स्थिर काष्ठा sof_पूर्णांकel_dsp_desc jsl_chip_info = अणु
	/* Jasperlake */
	.cores_num = 2,
	.init_core_mask = 1,
	.host_managed_cores_mask = GENMASK(1, 0),
	.ipc_req = CNL_DSP_REG_HIPCIDR,
	.ipc_req_mask = CNL_DSP_REG_HIPCIDR_BUSY,
	.ipc_ack = CNL_DSP_REG_HIPCIDA,
	.ipc_ack_mask = CNL_DSP_REG_HIPCIDA_DONE,
	.ipc_ctl = CNL_DSP_REG_HIPCCTL,
	.rom_init_समयout	= 300,
	.ssp_count = ICL_SSP_COUNT,
	.ssp_base_offset = CNL_SSP_BASE_OFFSET,
पूर्ण;
EXPORT_SYMBOL_NS(jsl_chip_info, SND_SOC_SOF_INTEL_HDA_COMMON);
