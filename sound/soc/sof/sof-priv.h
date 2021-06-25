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

#अगर_अघोषित __SOUND_SOC_SOF_PRIV_H
#घोषणा __SOUND_SOC_SOF_PRIV_H

#समावेश <linux/device.h>
#समावेश <sound/hdaudपन.स>
#समावेश <sound/sof.h>
#समावेश <sound/sof/info.h>
#समावेश <sound/sof/pm.h>
#समावेश <sound/sof/trace.h>
#समावेश <uapi/sound/sof/fw.h>
#समावेश <sound/sof/ext_manअगरest.h>

/* debug flags */
#घोषणा SOF_DBG_ENABLE_TRACE	BIT(0)
#घोषणा SOF_DBG_RETAIN_CTX	BIT(1)	/* prevent DSP D3 on FW exception */

#घोषणा SOF_DBG_DUMP_REGS		BIT(0)
#घोषणा SOF_DBG_DUMP_MBOX		BIT(1)
#घोषणा SOF_DBG_DUMP_TEXT		BIT(2)
#घोषणा SOF_DBG_DUMP_PCI		BIT(3)
#घोषणा SOF_DBG_DUMP_FORCE_ERR_LEVEL	BIT(4) /* used to dump dsp status with error log level */


/* global debug state set by SOF_DBG_ flags */
बाह्य पूर्णांक sof_core_debug;

/* max BARs mmaped devices can use */
#घोषणा SND_SOF_BARS	8

/* समय in ms क्रम runसमय suspend delay */
#घोषणा SND_SOF_SUSPEND_DELAY_MS	2000

/* DMA buffer size क्रम trace */
#घोषणा DMA_BUF_SIZE_FOR_TRACE (PAGE_SIZE * 16)

#घोषणा SOF_IPC_DSP_REPLY		0
#घोषणा SOF_IPC_HOST_REPLY		1

/* convenience स्थिरructor क्रम DAI driver streams */
#घोषणा SOF_DAI_STREAM(sname, scmin, scmax, srates, sfmt) \
	अणु.stream_name = sname, .channels_min = scmin, .channels_max = scmax, \
	 .rates = srates, .क्रमmats = sfmtपूर्ण

#घोषणा SOF_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE | \
	SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_FLOAT)

#घोषणा ENABLE_DEBUGFS_CACHEBUF \
	(IS_ENABLED(CONFIG_SND_SOC_SOF_DEBUG_ENABLE_DEBUGFS_CACHE) || \
	 IS_ENABLED(CONFIG_SND_SOC_SOF_DEBUG_IPC_FLOOD_TEST))

/* So far the primary core on all DSPs has ID 0 */
#घोषणा SOF_DSP_PRIMARY_CORE 0

/* DSP घातer state */
क्रमागत sof_dsp_घातer_states अणु
	SOF_DSP_PM_D0,
	SOF_DSP_PM_D1,
	SOF_DSP_PM_D2,
	SOF_DSP_PM_D3_HOT,
	SOF_DSP_PM_D3,
	SOF_DSP_PM_D3_COLD,
पूर्ण;

काष्ठा sof_dsp_घातer_state अणु
	u32 state;
	u32 substate; /* platक्रमm-specअगरic */
पूर्ण;

/* System suspend target state */
क्रमागत sof_प्रणाली_suspend_state अणु
	SOF_SUSPEND_NONE = 0,
	SOF_SUSPEND_S0IX,
	SOF_SUSPEND_S3,
पूर्ण;

काष्ठा snd_sof_dev;
काष्ठा snd_sof_ipc_msg;
काष्ठा snd_sof_ipc;
काष्ठा snd_sof_debugfs_map;
काष्ठा snd_soc_tplg_ops;
काष्ठा snd_soc_component;
काष्ठा snd_sof_pdata;

/*
 * SOF DSP HW असलtraction operations.
 * Used to असलtract DSP HW architecture and any IO busses between host CPU
 * and DSP device(s).
 */
काष्ठा snd_sof_dsp_ops अणु

	/* probe/हटाओ/shutकरोwn */
	पूर्णांक (*probe)(काष्ठा snd_sof_dev *sof_dev); /* mandatory */
	पूर्णांक (*हटाओ)(काष्ठा snd_sof_dev *sof_dev); /* optional */
	पूर्णांक (*shutकरोwn)(काष्ठा snd_sof_dev *sof_dev); /* optional */

	/* DSP core boot / reset */
	पूर्णांक (*run)(काष्ठा snd_sof_dev *sof_dev); /* mandatory */
	पूर्णांक (*stall)(काष्ठा snd_sof_dev *sof_dev, अचिन्हित पूर्णांक core_mask); /* optional */
	पूर्णांक (*reset)(काष्ठा snd_sof_dev *sof_dev); /* optional */
	पूर्णांक (*core_घातer_up)(काष्ठा snd_sof_dev *sof_dev,
			     अचिन्हित पूर्णांक core_mask); /* optional */
	पूर्णांक (*core_घातer_करोwn)(काष्ठा snd_sof_dev *sof_dev,
			       अचिन्हित पूर्णांक core_mask); /* optional */

	/*
	 * Register IO: only used by respective drivers themselves,
	 * TODO: consider removing these operations and calling respective
	 * implementations directly
	 */
	व्योम (*ग_लिखो)(काष्ठा snd_sof_dev *sof_dev, व्योम __iomem *addr,
		      u32 value); /* optional */
	u32 (*पढ़ो)(काष्ठा snd_sof_dev *sof_dev,
		    व्योम __iomem *addr); /* optional */
	व्योम (*ग_लिखो64)(काष्ठा snd_sof_dev *sof_dev, व्योम __iomem *addr,
			u64 value); /* optional */
	u64 (*पढ़ो64)(काष्ठा snd_sof_dev *sof_dev,
		      व्योम __iomem *addr); /* optional */

	/* स_नकल IO */
	व्योम (*block_पढ़ो)(काष्ठा snd_sof_dev *sof_dev, u32 bar,
			   u32 offset, व्योम *dest,
			   माप_प्रकार size); /* mandatory */
	व्योम (*block_ग_लिखो)(काष्ठा snd_sof_dev *sof_dev, u32 bar,
			    u32 offset, व्योम *src,
			    माप_प्रकार size); /* mandatory */

	/* करोorbell */
	irqवापस_t (*irq_handler)(पूर्णांक irq, व्योम *context); /* optional */
	irqवापस_t (*irq_thपढ़ो)(पूर्णांक irq, व्योम *context); /* optional */

	/* ipc */
	पूर्णांक (*send_msg)(काष्ठा snd_sof_dev *sof_dev,
			काष्ठा snd_sof_ipc_msg *msg); /* mandatory */

	/* FW loading */
	पूर्णांक (*load_firmware)(काष्ठा snd_sof_dev *sof_dev); /* mandatory */
	पूर्णांक (*load_module)(काष्ठा snd_sof_dev *sof_dev,
			   काष्ठा snd_sof_mod_hdr *hdr); /* optional */
	/*
	 * FW पढ़ोy checks क्रम ABI compatibility and creates
	 * memory winकरोws at first boot
	 */
	पूर्णांक (*fw_पढ़ोy)(काष्ठा snd_sof_dev *sdev, u32 msg_id); /* mandatory */

	/* connect pcm substream to a host stream */
	पूर्णांक (*pcm_खोलो)(काष्ठा snd_sof_dev *sdev,
			काष्ठा snd_pcm_substream *substream); /* optional */
	/* disconnect pcm substream to a host stream */
	पूर्णांक (*pcm_बंद)(काष्ठा snd_sof_dev *sdev,
			 काष्ठा snd_pcm_substream *substream); /* optional */

	/* host stream hw params */
	पूर्णांक (*pcm_hw_params)(काष्ठा snd_sof_dev *sdev,
			     काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा sof_ipc_stream_params *ipc_params); /* optional */

	/* host stream hw_मुक्त */
	पूर्णांक (*pcm_hw_मुक्त)(काष्ठा snd_sof_dev *sdev,
			   काष्ठा snd_pcm_substream *substream); /* optional */

	/* host stream trigger */
	पूर्णांक (*pcm_trigger)(काष्ठा snd_sof_dev *sdev,
			   काष्ठा snd_pcm_substream *substream,
			   पूर्णांक cmd); /* optional */

	/* host stream poपूर्णांकer */
	snd_pcm_uframes_t (*pcm_poपूर्णांकer)(काष्ठा snd_sof_dev *sdev,
					 काष्ठा snd_pcm_substream *substream); /* optional */

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_DEBUG_PROBES)
	/* Except क्रम probe_poपूर्णांकer, all probe ops are mandatory */
	पूर्णांक (*probe_assign)(काष्ठा snd_sof_dev *sdev,
			काष्ठा snd_compr_stream *cstream,
			काष्ठा snd_soc_dai *dai); /* mandatory */
	पूर्णांक (*probe_मुक्त)(काष्ठा snd_sof_dev *sdev,
			काष्ठा snd_compr_stream *cstream,
			काष्ठा snd_soc_dai *dai); /* mandatory */
	पूर्णांक (*probe_set_params)(काष्ठा snd_sof_dev *sdev,
			काष्ठा snd_compr_stream *cstream,
			काष्ठा snd_compr_params *params,
			काष्ठा snd_soc_dai *dai); /* mandatory */
	पूर्णांक (*probe_trigger)(काष्ठा snd_sof_dev *sdev,
			काष्ठा snd_compr_stream *cstream, पूर्णांक cmd,
			काष्ठा snd_soc_dai *dai); /* mandatory */
	पूर्णांक (*probe_poपूर्णांकer)(काष्ठा snd_sof_dev *sdev,
			काष्ठा snd_compr_stream *cstream,
			काष्ठा snd_compr_tstamp *tstamp,
			काष्ठा snd_soc_dai *dai); /* optional */
#पूर्ण_अगर

	/* host पढ़ो DSP stream data */
	व्योम (*ipc_msg_data)(काष्ठा snd_sof_dev *sdev,
			     काष्ठा snd_pcm_substream *substream,
			     व्योम *p, माप_प्रकार sz); /* mandatory */

	/* host configure DSP HW parameters */
	पूर्णांक (*ipc_pcm_params)(काष्ठा snd_sof_dev *sdev,
			      काष्ठा snd_pcm_substream *substream,
			      स्थिर काष्ठा sof_ipc_pcm_params_reply *reply); /* mandatory */

	/* pre/post firmware run */
	पूर्णांक (*pre_fw_run)(काष्ठा snd_sof_dev *sof_dev); /* optional */
	पूर्णांक (*post_fw_run)(काष्ठा snd_sof_dev *sof_dev); /* optional */

	/* parse platक्रमm specअगरic extended manअगरest, optional */
	पूर्णांक (*parse_platक्रमm_ext_manअगरest)(काष्ठा snd_sof_dev *sof_dev,
					   स्थिर काष्ठा sof_ext_man_elem_header *hdr);

	/* DSP PM */
	पूर्णांक (*suspend)(काष्ठा snd_sof_dev *sof_dev,
		       u32 target_state); /* optional */
	पूर्णांक (*resume)(काष्ठा snd_sof_dev *sof_dev); /* optional */
	पूर्णांक (*runसमय_suspend)(काष्ठा snd_sof_dev *sof_dev); /* optional */
	पूर्णांक (*runसमय_resume)(काष्ठा snd_sof_dev *sof_dev); /* optional */
	पूर्णांक (*runसमय_idle)(काष्ठा snd_sof_dev *sof_dev); /* optional */
	पूर्णांक (*set_hw_params_upon_resume)(काष्ठा snd_sof_dev *sdev); /* optional */
	पूर्णांक (*set_घातer_state)(काष्ठा snd_sof_dev *sdev,
			       स्थिर काष्ठा sof_dsp_घातer_state *target_state); /* optional */

	/* DSP घड़ीing */
	पूर्णांक (*set_clk)(काष्ठा snd_sof_dev *sof_dev, u32 freq); /* optional */

	/* debug */
	स्थिर काष्ठा snd_sof_debugfs_map *debug_map; /* optional */
	पूर्णांक debug_map_count; /* optional */
	व्योम (*dbg_dump)(काष्ठा snd_sof_dev *sof_dev,
			 u32 flags); /* optional */
	व्योम (*ipc_dump)(काष्ठा snd_sof_dev *sof_dev); /* optional */

	/* host DMA trace initialization */
	पूर्णांक (*trace_init)(काष्ठा snd_sof_dev *sdev,
			  u32 *stream_tag); /* optional */
	पूर्णांक (*trace_release)(काष्ठा snd_sof_dev *sdev); /* optional */
	पूर्णांक (*trace_trigger)(काष्ठा snd_sof_dev *sdev,
			     पूर्णांक cmd); /* optional */

	/* misc */
	पूर्णांक (*get_bar_index)(काष्ठा snd_sof_dev *sdev,
			     u32 type); /* optional */
	पूर्णांक (*get_mailbox_offset)(काष्ठा snd_sof_dev *sdev);/* mandatory क्रम common loader code */
	पूर्णांक (*get_winकरोw_offset)(काष्ठा snd_sof_dev *sdev,
				 u32 id);/* mandatory क्रम common loader code */

	/* machine driver ops */
	पूर्णांक (*machine_रेजिस्टर)(काष्ठा snd_sof_dev *sdev,
				व्योम *pdata); /* optional */
	व्योम (*machine_unरेजिस्टर)(काष्ठा snd_sof_dev *sdev,
				   व्योम *pdata); /* optional */
	व्योम (*machine_select)(काष्ठा snd_sof_dev *sdev); /* optional */
	व्योम (*set_mach_params)(स्थिर काष्ठा snd_soc_acpi_mach *mach,
				काष्ठा snd_sof_dev *sdev); /* optional */

	/* DAI ops */
	काष्ठा snd_soc_dai_driver *drv;
	पूर्णांक num_drv;

	/* ALSA HW info flags, will be stored in snd_pcm_runसमय.सw.info */
	u32 hw_info;

	स्थिर काष्ठा sof_arch_ops *arch_ops;
पूर्ण;

/* DSP architecture specअगरic callbacks क्रम oops and stack dumps */
काष्ठा sof_arch_ops अणु
	व्योम (*dsp_oops)(काष्ठा snd_sof_dev *sdev, व्योम *oops);
	व्योम (*dsp_stack)(काष्ठा snd_sof_dev *sdev, व्योम *oops,
			  u32 *stack, u32 stack_words);
पूर्ण;

#घोषणा sof_arch_ops(sdev) ((sdev)->pdata->desc->ops->arch_ops)

/* DSP device HW descriptor mapping between bus ID and ops */
काष्ठा sof_ops_table अणु
	स्थिर काष्ठा sof_dev_desc *desc;
	स्थिर काष्ठा snd_sof_dsp_ops *ops;
पूर्ण;

क्रमागत sof_dfsentry_type अणु
	SOF_DFSENTRY_TYPE_IOMEM = 0,
	SOF_DFSENTRY_TYPE_BUF,
पूर्ण;

क्रमागत sof_debugfs_access_type अणु
	SOF_DEBUGFS_ACCESS_ALWAYS = 0,
	SOF_DEBUGFS_ACCESS_D0_ONLY,
पूर्ण;

/* FS entry क्रम debug files that can expose DSP memories, रेजिस्टरs */
काष्ठा snd_sof_dfsentry अणु
	माप_प्रकार size;
	माप_प्रकार buf_data_size;  /* length of buffered data क्रम file पढ़ो operation */
	क्रमागत sof_dfsentry_type type;
	/*
	 * access_type specअगरies अगर the
	 * memory -> DSP resource (memory, रेजिस्टर etc) is always accessible
	 * or अगर it is accessible only when the DSP is in D0.
	 */
	क्रमागत sof_debugfs_access_type access_type;
#अगर ENABLE_DEBUGFS_CACHEBUF
	अक्षर *cache_buf; /* buffer to cache the contents of debugfs memory */
#पूर्ण_अगर
	काष्ठा snd_sof_dev *sdev;
	काष्ठा list_head list;  /* list in sdev dfsentry list */
	जोड़ अणु
		व्योम __iomem *io_mem;
		व्योम *buf;
	पूर्ण;
पूर्ण;

/* Debug mapping क्रम any DSP memory or रेजिस्टरs that can used क्रम debug */
काष्ठा snd_sof_debugfs_map अणु
	स्थिर अक्षर *name;
	u32 bar;
	u32 offset;
	u32 size;
	/*
	 * access_type specअगरies अगर the memory is always accessible
	 * or अगर it is accessible only when the DSP is in D0.
	 */
	क्रमागत sof_debugfs_access_type access_type;
पूर्ण;

/* mailbox descriptor, used क्रम host <-> DSP IPC */
काष्ठा snd_sof_mailbox अणु
	u32 offset;
	माप_प्रकार size;
पूर्ण;

/* IPC message descriptor क्रम host <-> DSP IO */
काष्ठा snd_sof_ipc_msg अणु
	/* message data */
	u32 header;
	व्योम *msg_data;
	व्योम *reply_data;
	माप_प्रकार msg_size;
	माप_प्रकार reply_size;
	पूर्णांक reply_error;

	रुको_queue_head_t रुकोq;
	bool ipc_complete;
पूर्ण;

क्रमागत snd_sof_fw_state अणु
	SOF_FW_BOOT_NOT_STARTED = 0,
	SOF_FW_BOOT_PREPARE,
	SOF_FW_BOOT_IN_PROGRESS,
	SOF_FW_BOOT_FAILED,
	SOF_FW_BOOT_READY_FAILED, /* firmware booted but fw_पढ़ोy op failed */
	SOF_FW_BOOT_COMPLETE,
पूर्ण;

/*
 * SOF Device Level.
 */
काष्ठा snd_sof_dev अणु
	काष्ठा device *dev;
	spinlock_t ipc_lock;	/* lock क्रम IPC users */
	spinlock_t hw_lock;	/* lock क्रम HW IO access */

	/*
	 * ASoC components. plat_drv fields are set dynamically so
	 * can't use स्थिर
	 */
	काष्ठा snd_soc_component_driver plat_drv;

	/* current DSP घातer state */
	काष्ठा sof_dsp_घातer_state dsp_घातer_state;
	/* mutex to protect the dsp_घातer_state access */
	काष्ठा mutex घातer_state_access;

	/* Intended घातer target of प्रणाली suspend */
	क्रमागत sof_प्रणाली_suspend_state प्रणाली_suspend_target;

	/* DSP firmware boot */
	रुको_queue_head_t boot_रुको;
	क्रमागत snd_sof_fw_state fw_state;
	bool first_boot;

	/* work queue in हाल the probe is implemented in two steps */
	काष्ठा work_काष्ठा probe_work;
	bool probe_completed;

	/* DSP HW dअगरferentiation */
	काष्ठा snd_sof_pdata *pdata;

	/* IPC */
	काष्ठा snd_sof_ipc *ipc;
	काष्ठा snd_sof_mailbox dsp_box;		/* DSP initiated IPC */
	काष्ठा snd_sof_mailbox host_box;	/* Host initiated IPC */
	काष्ठा snd_sof_mailbox stream_box;	/* Stream position update */
	काष्ठा snd_sof_mailbox debug_box;	/* Debug info updates */
	काष्ठा snd_sof_ipc_msg *msg;
	पूर्णांक ipc_irq;
	u32 next_comp_id; /* monotonic - reset during S3 */

	/* memory bases क्रम mmaped DSPs - set by dsp_init() */
	व्योम __iomem *bar[SND_SOF_BARS];	/* DSP base address */
	पूर्णांक mmio_bar;
	पूर्णांक mailbox_bar;
	माप_प्रकार dsp_oops_offset;

	/* debug */
	काष्ठा dentry *debugfs_root;
	काष्ठा list_head dfsentry_list;

	/* firmware loader */
	काष्ठा snd_dma_buffer dmab;
	काष्ठा snd_dma_buffer dmab_bdl;
	काष्ठा sof_ipc_fw_पढ़ोy fw_पढ़ोy;
	काष्ठा sof_ipc_fw_version fw_version;
	काष्ठा sof_ipc_cc_version *cc_version;

	/* topology */
	काष्ठा snd_soc_tplg_ops *tplg_ops;
	काष्ठा list_head pcm_list;
	काष्ठा list_head kcontrol_list;
	काष्ठा list_head widget_list;
	काष्ठा list_head dai_list;
	काष्ठा list_head route_list;
	काष्ठा snd_soc_component *component;
	u32 enabled_cores_mask; /* keep track of enabled cores */

	/* FW configuration */
	काष्ठा sof_ipc_winकरोw *info_winकरोw;

	/* IPC समयouts in ms */
	पूर्णांक ipc_समयout;
	पूर्णांक boot_समयout;

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_DEBUG_PROBES)
	अचिन्हित पूर्णांक extractor_stream_tag;
#पूर्ण_अगर

	/* DMA क्रम Trace */
	काष्ठा snd_dma_buffer dmatb;
	काष्ठा snd_dma_buffer dmatp;
	पूर्णांक dma_trace_pages;
	रुको_queue_head_t trace_sleep;
	u32 host_offset;
	bool dtrace_is_supported; /* set with Kconfig or module parameter */
	bool dtrace_is_enabled;
	bool dtrace_error;
	bool dtrace_draining;

	bool msi_enabled;

	व्योम *निजी;			/* core करोes not touch this */
पूर्ण;

/*
 * Device Level.
 */

पूर्णांक snd_sof_device_probe(काष्ठा device *dev, काष्ठा snd_sof_pdata *plat_data);
पूर्णांक snd_sof_device_हटाओ(काष्ठा device *dev);
पूर्णांक snd_sof_device_shutकरोwn(काष्ठा device *dev);
bool snd_sof_device_probe_completed(काष्ठा device *dev);

पूर्णांक snd_sof_runसमय_suspend(काष्ठा device *dev);
पूर्णांक snd_sof_runसमय_resume(काष्ठा device *dev);
पूर्णांक snd_sof_runसमय_idle(काष्ठा device *dev);
पूर्णांक snd_sof_resume(काष्ठा device *dev);
पूर्णांक snd_sof_suspend(काष्ठा device *dev);
पूर्णांक snd_sof_dsp_घातer_करोwn_notअगरy(काष्ठा snd_sof_dev *sdev);
पूर्णांक snd_sof_prepare(काष्ठा device *dev);
व्योम snd_sof_complete(काष्ठा device *dev);

व्योम snd_sof_new_platक्रमm_drv(काष्ठा snd_sof_dev *sdev);

पूर्णांक snd_sof_create_page_table(काष्ठा device *dev,
			      काष्ठा snd_dma_buffer *dmab,
			      अचिन्हित अक्षर *page_table, माप_प्रकार size);

/*
 * Firmware loading.
 */
पूर्णांक snd_sof_load_firmware(काष्ठा snd_sof_dev *sdev);
पूर्णांक snd_sof_load_firmware_raw(काष्ठा snd_sof_dev *sdev);
पूर्णांक snd_sof_load_firmware_स_नकल(काष्ठा snd_sof_dev *sdev);
पूर्णांक snd_sof_run_firmware(काष्ठा snd_sof_dev *sdev);
पूर्णांक snd_sof_parse_module_स_नकल(काष्ठा snd_sof_dev *sdev,
				काष्ठा snd_sof_mod_hdr *module);
व्योम snd_sof_fw_unload(काष्ठा snd_sof_dev *sdev);
पूर्णांक snd_sof_fw_parse_ext_data(काष्ठा snd_sof_dev *sdev, u32 bar, u32 offset);

/*
 * IPC low level APIs.
 */
काष्ठा snd_sof_ipc *snd_sof_ipc_init(काष्ठा snd_sof_dev *sdev);
व्योम snd_sof_ipc_मुक्त(काष्ठा snd_sof_dev *sdev);
व्योम snd_sof_ipc_reply(काष्ठा snd_sof_dev *sdev, u32 msg_id);
व्योम snd_sof_ipc_msgs_rx(काष्ठा snd_sof_dev *sdev);
पूर्णांक snd_sof_ipc_stream_pcm_params(काष्ठा snd_sof_dev *sdev,
				  काष्ठा sof_ipc_pcm_params *params);
पूर्णांक snd_sof_dsp_mailbox_init(काष्ठा snd_sof_dev *sdev, u32 dspbox,
			     माप_प्रकार dspbox_size, u32 hostbox,
			     माप_प्रकार hostbox_size);
पूर्णांक snd_sof_ipc_valid(काष्ठा snd_sof_dev *sdev);
पूर्णांक sof_ipc_tx_message(काष्ठा snd_sof_ipc *ipc, u32 header,
		       व्योम *msg_data, माप_प्रकार msg_bytes, व्योम *reply_data,
		       माप_प्रकार reply_bytes);
पूर्णांक sof_ipc_tx_message_no_pm(काष्ठा snd_sof_ipc *ipc, u32 header,
			     व्योम *msg_data, माप_प्रकार msg_bytes,
			     व्योम *reply_data, माप_प्रकार reply_bytes);

/*
 * Trace/debug
 */
पूर्णांक snd_sof_init_trace(काष्ठा snd_sof_dev *sdev);
व्योम snd_sof_release_trace(काष्ठा snd_sof_dev *sdev);
व्योम snd_sof_मुक्त_trace(काष्ठा snd_sof_dev *sdev);
पूर्णांक snd_sof_dbg_init(काष्ठा snd_sof_dev *sdev);
व्योम snd_sof_मुक्त_debug(काष्ठा snd_sof_dev *sdev);
पूर्णांक snd_sof_debugfs_io_item(काष्ठा snd_sof_dev *sdev,
			    व्योम __iomem *base, माप_प्रकार size,
			    स्थिर अक्षर *name,
			    क्रमागत sof_debugfs_access_type access_type);
पूर्णांक snd_sof_debugfs_buf_item(काष्ठा snd_sof_dev *sdev,
			     व्योम *base, माप_प्रकार size,
			     स्थिर अक्षर *name, mode_t mode);
पूर्णांक snd_sof_trace_update_pos(काष्ठा snd_sof_dev *sdev,
			     काष्ठा sof_ipc_dma_trace_posn *posn);
व्योम snd_sof_trace_notअगरy_क्रम_error(काष्ठा snd_sof_dev *sdev);
व्योम snd_sof_get_status(काष्ठा snd_sof_dev *sdev, u32 panic_code,
			u32 tracep_code, व्योम *oops,
			काष्ठा sof_ipc_panic_info *panic_info,
			व्योम *stack, माप_प्रकार stack_words);
पूर्णांक snd_sof_init_trace_ipc(काष्ठा snd_sof_dev *sdev);
व्योम snd_sof_handle_fw_exception(काष्ठा snd_sof_dev *sdev);
पूर्णांक snd_sof_dbg_memory_info_init(काष्ठा snd_sof_dev *sdev);

/*
 * Platक्रमm specअगरic ops.
 */
बाह्य काष्ठा snd_compress_ops sof_compressed_ops;

/*
 * DSP Architectures.
 */
अटल अंतरभूत व्योम sof_stack(काष्ठा snd_sof_dev *sdev, व्योम *oops, u32 *stack,
			     u32 stack_words)
अणु
		sof_arch_ops(sdev)->dsp_stack(sdev, oops, stack, stack_words);
पूर्ण

अटल अंतरभूत व्योम sof_oops(काष्ठा snd_sof_dev *sdev, व्योम *oops)
अणु
	अगर (sof_arch_ops(sdev)->dsp_oops)
		sof_arch_ops(sdev)->dsp_oops(sdev, oops);
पूर्ण

बाह्य स्थिर काष्ठा sof_arch_ops sof_xtensa_arch_ops;

/*
 * Utilities
 */
व्योम sof_io_ग_लिखो(काष्ठा snd_sof_dev *sdev, व्योम __iomem *addr, u32 value);
व्योम sof_io_ग_लिखो64(काष्ठा snd_sof_dev *sdev, व्योम __iomem *addr, u64 value);
u32 sof_io_पढ़ो(काष्ठा snd_sof_dev *sdev, व्योम __iomem *addr);
u64 sof_io_पढ़ो64(काष्ठा snd_sof_dev *sdev, व्योम __iomem *addr);
व्योम sof_mailbox_ग_लिखो(काष्ठा snd_sof_dev *sdev, u32 offset,
		       व्योम *message, माप_प्रकार bytes);
व्योम sof_mailbox_पढ़ो(काष्ठा snd_sof_dev *sdev, u32 offset,
		      व्योम *message, माप_प्रकार bytes);
व्योम sof_block_ग_लिखो(काष्ठा snd_sof_dev *sdev, u32 bar, u32 offset, व्योम *src,
		     माप_प्रकार size);
व्योम sof_block_पढ़ो(काष्ठा snd_sof_dev *sdev, u32 bar, u32 offset, व्योम *dest,
		    माप_प्रकार size);

पूर्णांक sof_fw_पढ़ोy(काष्ठा snd_sof_dev *sdev, u32 msg_id);

व्योम पूर्णांकel_ipc_msg_data(काष्ठा snd_sof_dev *sdev,
			काष्ठा snd_pcm_substream *substream,
			व्योम *p, माप_प्रकार sz);
पूर्णांक पूर्णांकel_ipc_pcm_params(काष्ठा snd_sof_dev *sdev,
			 काष्ठा snd_pcm_substream *substream,
			 स्थिर काष्ठा sof_ipc_pcm_params_reply *reply);

पूर्णांक पूर्णांकel_pcm_खोलो(काष्ठा snd_sof_dev *sdev,
		   काष्ठा snd_pcm_substream *substream);
पूर्णांक पूर्णांकel_pcm_बंद(काष्ठा snd_sof_dev *sdev,
		    काष्ठा snd_pcm_substream *substream);

पूर्णांक sof_machine_check(काष्ठा snd_sof_dev *sdev);

#घोषणा sof_dev_dbg_or_err(dev, is_err, fmt, ...)			\
	करो अणु								\
		अगर (is_err)						\
			dev_err(dev, "error: " fmt, __VA_ARGS__);	\
		अन्यथा							\
			dev_dbg(dev, fmt, __VA_ARGS__);			\
	पूर्ण जबतक (0)

#पूर्ण_अगर
