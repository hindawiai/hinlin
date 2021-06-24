<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * Copyright(c) 2018 Intel Corporation. All rights reserved.
 */

#अगर_अघोषित __INCLUDE_SOUND_SOF_TOPOLOGY_H__
#घोषणा __INCLUDE_SOUND_SOF_TOPOLOGY_H__

#समावेश <sound/sof/header.h>

/*
 * Component
 */

/* types of component */
क्रमागत sof_comp_type अणु
	SOF_COMP_NONE = 0,
	SOF_COMP_HOST,
	SOF_COMP_DAI,
	SOF_COMP_SG_HOST,	/**< scatter gather variant */
	SOF_COMP_SG_DAI,	/**< scatter gather variant */
	SOF_COMP_VOLUME,
	SOF_COMP_MIXER,
	SOF_COMP_MUX,
	SOF_COMP_SRC,
	SOF_COMP_SPLITTER,
	SOF_COMP_TONE,
	SOF_COMP_SWITCH,
	SOF_COMP_BUFFER,
	SOF_COMP_EQ_IIR,
	SOF_COMP_EQ_FIR,
	SOF_COMP_KEYWORD_DETECT,
	SOF_COMP_KPB,			/* A key phrase buffer component */
	SOF_COMP_SELECTOR,		/**< channel selector component */
	SOF_COMP_DEMUX,
	SOF_COMP_ASRC,		/**< Asynchronous sample rate converter */
	SOF_COMP_DCBLOCK,
	SOF_COMP_SMART_AMP,             /**< smart amplअगरier component */
	/* keep खाताREAD/खाताWRITE as the last ones */
	SOF_COMP_खाताREAD = 10000,	/**< host test based file IO */
	SOF_COMP_खाताWRITE = 10001,	/**< host test based file IO */
पूर्ण;

/* XRUN action क्रम component */
#घोषणा SOF_XRUN_STOP		1	/**< stop stream */
#घोषणा SOF_XRUN_UNDER_ZERO	2	/**< send 0s to sink */
#घोषणा SOF_XRUN_OVER_शून्य	4	/**< send data to शून्य */

/* create new generic component - SOF_IPC_TPLG_COMP_NEW */
काष्ठा sof_ipc_comp अणु
	काष्ठा sof_ipc_cmd_hdr hdr;
	uपूर्णांक32_t id;
	क्रमागत sof_comp_type type;
	uपूर्णांक32_t pipeline_id;
	uपूर्णांक32_t core;

	/* extended data length, 0 अगर no extended data */
	uपूर्णांक32_t ext_data_length;
पूर्ण __packed;

/*
 * Component Buffers
 */

/*
 * SOF memory capabilities, add new ones at the end
 */
#घोषणा SOF_MEM_CAPS_RAM			(1 << 0)
#घोषणा SOF_MEM_CAPS_ROM			(1 << 1)
#घोषणा SOF_MEM_CAPS_EXT			(1 << 2) /**< बाह्यal */
#घोषणा SOF_MEM_CAPS_LP			(1 << 3) /**< low घातer */
#घोषणा SOF_MEM_CAPS_HP			(1 << 4) /**< high perक्रमmance */
#घोषणा SOF_MEM_CAPS_DMA			(1 << 5) /**< DMA'able */
#घोषणा SOF_MEM_CAPS_CACHE			(1 << 6) /**< cacheable */
#घोषणा SOF_MEM_CAPS_EXEC			(1 << 7) /**< executable */

/*
 * overrun will cause ring buffer overग_लिखो, instead of XRUN.
 */
#घोषणा SOF_BUF_OVERRUN_PERMITTED	BIT(0)

/*
 * underrun will cause पढ़ोback of 0s, instead of XRUN.
 */
#घोषणा SOF_BUF_UNDERRUN_PERMITTED	BIT(1)

/* the UUID size in bytes, shared between FW and host */
#घोषणा SOF_UUID_SIZE	16

/* create new component buffer - SOF_IPC_TPLG_BUFFER_NEW */
काष्ठा sof_ipc_buffer अणु
	काष्ठा sof_ipc_comp comp;
	uपूर्णांक32_t size;		/**< buffer size in bytes */
	uपूर्णांक32_t caps;		/**< SOF_MEM_CAPS_ */
	uपूर्णांक32_t flags;		/**< SOF_BUF_ flags defined above */
	uपूर्णांक32_t reserved;	/**< reserved क्रम future use */
पूर्ण __packed;

/* generic component config data - must always be after काष्ठा sof_ipc_comp */
काष्ठा sof_ipc_comp_config अणु
	काष्ठा sof_ipc_cmd_hdr hdr;
	uपूर्णांक32_t periods_sink;	/**< 0 means variable */
	uपूर्णांक32_t periods_source;/**< 0 means variable */
	uपूर्णांक32_t reserved1;	/**< reserved */
	uपूर्णांक32_t frame_fmt;	/**< SOF_IPC_FRAME_ */
	uपूर्णांक32_t xrun_action;

	/* reserved क्रम future use */
	uपूर्णांक32_t reserved[2];
पूर्ण __packed;

/* generic host component */
काष्ठा sof_ipc_comp_host अणु
	काष्ठा sof_ipc_comp comp;
	काष्ठा sof_ipc_comp_config config;
	uपूर्णांक32_t direction;	/**< SOF_IPC_STREAM_ */
	uपूर्णांक32_t no_irq;	/**< करोn't send periodic IRQ to host/DSP */
	uपूर्णांक32_t dmac_config; /**< DMA engine specअगरic */
पूर्ण  __packed;

/* generic DAI component */
काष्ठा sof_ipc_comp_dai अणु
	काष्ठा sof_ipc_comp comp;
	काष्ठा sof_ipc_comp_config config;
	uपूर्णांक32_t direction;	/**< SOF_IPC_STREAM_ */
	uपूर्णांक32_t dai_index;	/**< index of this type dai */
	uपूर्णांक32_t type;		/**< DAI type - SOF_DAI_ */
	uपूर्णांक32_t reserved;	/**< reserved */
पूर्ण  __packed;

/* generic mixer component */
काष्ठा sof_ipc_comp_mixer अणु
	काष्ठा sof_ipc_comp comp;
	काष्ठा sof_ipc_comp_config config;
पूर्ण  __packed;

/* volume ramping types */
क्रमागत sof_volume_ramp अणु
	SOF_VOLUME_LINEAR	= 0,
	SOF_VOLUME_LOG,
	SOF_VOLUME_LINEAR_ZC,
	SOF_VOLUME_LOG_ZC,
पूर्ण;

/* generic volume component */
काष्ठा sof_ipc_comp_volume अणु
	काष्ठा sof_ipc_comp comp;
	काष्ठा sof_ipc_comp_config config;
	uपूर्णांक32_t channels;
	uपूर्णांक32_t min_value;
	uपूर्णांक32_t max_value;
	uपूर्णांक32_t ramp;		/**< SOF_VOLUME_ */
	uपूर्णांक32_t initial_ramp;	/**< ramp space in ms */
पूर्ण  __packed;

/* generic SRC component */
काष्ठा sof_ipc_comp_src अणु
	काष्ठा sof_ipc_comp comp;
	काष्ठा sof_ipc_comp_config config;
	/* either source or sink rate must be non zero */
	uपूर्णांक32_t source_rate;	/**< source rate or 0 क्रम variable */
	uपूर्णांक32_t sink_rate;	/**< sink rate or 0 क्रम variable */
	uपूर्णांक32_t rate_mask;	/**< SOF_RATE_ supported rates */
पूर्ण __packed;

/* generic ASRC component */
काष्ठा sof_ipc_comp_asrc अणु
	काष्ठा sof_ipc_comp comp;
	काष्ठा sof_ipc_comp_config config;
	/* either source or sink rate must be non zero */
	uपूर्णांक32_t source_rate;		/**< Define fixed source rate or */
					/**< use 0 to indicate need to get */
					/**< the rate from stream */
	uपूर्णांक32_t sink_rate;		/**< Define fixed sink rate or */
					/**< use 0 to indicate need to get */
					/**< the rate from stream */
	uपूर्णांक32_t asynchronous_mode;	/**< synchronous 0, asynchronous 1 */
					/**< When 1 the ASRC tracks and */
					/**< compensates क्रम drअगरt. */
	uपूर्णांक32_t operation_mode;	/**< push 0, pull 1, In push mode the */
					/**< ASRC consumes a defined number */
					/**< of frames at input, with varying */
					/**< number of frames at output. */
					/**< In pull mode the ASRC outमाला_दो */
					/**< a defined number of frames जबतक */
					/**< number of input frames varies. */

	/* reserved क्रम future use */
	uपूर्णांक32_t reserved[4];
पूर्ण __attribute__((packed));

/* generic MUX component */
काष्ठा sof_ipc_comp_mux अणु
	काष्ठा sof_ipc_comp comp;
	काष्ठा sof_ipc_comp_config config;
पूर्ण __packed;

/* generic tone generator component */
काष्ठा sof_ipc_comp_tone अणु
	काष्ठा sof_ipc_comp comp;
	काष्ठा sof_ipc_comp_config config;
	पूर्णांक32_t sample_rate;
	पूर्णांक32_t frequency;
	पूर्णांक32_t amplitude;
	पूर्णांक32_t freq_mult;
	पूर्णांक32_t ampl_mult;
	पूर्णांक32_t length;
	पूर्णांक32_t period;
	पूर्णांक32_t repeats;
	पूर्णांक32_t ramp_step;
पूर्ण __packed;

/** \मrief Types of processing components */
क्रमागत sof_ipc_process_type अणु
	SOF_PROCESS_NONE = 0,		/**< None */
	SOF_PROCESS_EQFIR,		/**< Intel FIR */
	SOF_PROCESS_EQIIR,		/**< Intel IIR */
	SOF_PROCESS_KEYWORD_DETECT,	/**< Keyword Detection */
	SOF_PROCESS_KPB,		/**< KeyPhrase Buffer Manager */
	SOF_PROCESS_CHAN_SELECTOR,	/**< Channel Selector */
	SOF_PROCESS_MUX,
	SOF_PROCESS_DEMUX,
	SOF_PROCESS_DCBLOCK,
	SOF_PROCESS_SMART_AMP,	/**< Smart Amplअगरier */
पूर्ण;

/* generic "effect", "codec" or proprietary processing component */
काष्ठा sof_ipc_comp_process अणु
	काष्ठा sof_ipc_comp comp;
	काष्ठा sof_ipc_comp_config config;
	uपूर्णांक32_t size;	/**< size of bespoke data section in bytes */
	uपूर्णांक32_t type;	/**< sof_ipc_process_type */

	/* reserved क्रम future use */
	uपूर्णांक32_t reserved[7];

	uपूर्णांक8_t data[0];
पूर्ण __packed;

/* मुक्तs components, buffers and pipelines
 * SOF_IPC_TPLG_COMP_FREE, SOF_IPC_TPLG_PIPE_FREE, SOF_IPC_TPLG_BUFFER_FREE
 */
काष्ठा sof_ipc_मुक्त अणु
	काष्ठा sof_ipc_cmd_hdr hdr;
	uपूर्णांक32_t id;
पूर्ण __packed;

काष्ठा sof_ipc_comp_reply अणु
	काष्ठा sof_ipc_reply rhdr;
	uपूर्णांक32_t id;
	uपूर्णांक32_t offset;
पूर्ण __packed;

/*
 * Pipeline
 */

/** \मrief Types of pipeline scheduling समय करोमुख्यs */
क्रमागत sof_ipc_pipe_sched_समय_करोमुख्य अणु
	SOF_TIME_DOMAIN_DMA = 0,	/**< DMA पूर्णांकerrupt */
	SOF_TIME_DOMAIN_TIMER,		/**< Timer पूर्णांकerrupt */
पूर्ण;

/* new pipeline - SOF_IPC_TPLG_PIPE_NEW */
काष्ठा sof_ipc_pipe_new अणु
	काष्ठा sof_ipc_cmd_hdr hdr;
	uपूर्णांक32_t comp_id;	/**< component id क्रम pipeline */
	uपूर्णांक32_t pipeline_id;	/**< pipeline id */
	uपूर्णांक32_t sched_id;	/**< Scheduling component id */
	uपूर्णांक32_t core;		/**< core we run on */
	uपूर्णांक32_t period;	/**< execution period in us*/
	uपूर्णांक32_t priority;	/**< priority level 0 (low) to 10 (max) */
	uपूर्णांक32_t period_mips;	/**< worst हाल inकाष्ठाion count per period */
	uपूर्णांक32_t frames_per_sched;/**< output frames of pipeline, 0 is variable */
	uपूर्णांक32_t xrun_limit_usecs; /**< report xruns greater than limit */
	uपूर्णांक32_t समय_करोमुख्य;	/**< scheduling समय करोमुख्य */
पूर्ण  __packed;

/* pipeline स्थिरruction complete - SOF_IPC_TPLG_PIPE_COMPLETE */
काष्ठा sof_ipc_pipe_पढ़ोy अणु
	काष्ठा sof_ipc_cmd_hdr hdr;
	uपूर्णांक32_t comp_id;
पूर्ण  __packed;

काष्ठा sof_ipc_pipe_मुक्त अणु
	काष्ठा sof_ipc_cmd_hdr hdr;
	uपूर्णांक32_t comp_id;
पूर्ण  __packed;

/* connect two components in pipeline - SOF_IPC_TPLG_COMP_CONNECT */
काष्ठा sof_ipc_pipe_comp_connect अणु
	काष्ठा sof_ipc_cmd_hdr hdr;
	uपूर्णांक32_t source_id;
	uपूर्णांक32_t sink_id;
पूर्ण  __packed;

/* बाह्यal events */
क्रमागत sof_event_types अणु
	SOF_EVENT_NONE = 0,
	SOF_KEYWORD_DETECT_DAPM_EVENT,
पूर्ण;

/* extended data काष्ठा क्रम UUID components */
काष्ठा sof_ipc_comp_ext अणु
	uपूर्णांक8_t uuid[SOF_UUID_SIZE];
पूर्ण  __packed;

#पूर्ण_अगर
