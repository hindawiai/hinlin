<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * platक्रमm_sst_audपन.स:  sst audio platक्रमm data header file
 *
 * Copyright (C) 2012-14 Intel Corporation
 * Author: Jeeja KP <jeeja.kp@पूर्णांकel.com>
 * 	Omair Mohammed Abdullah <omair.m.abdullah@पूर्णांकel.com>
 *	Vinod Koul ,vinod.koul@पूर्णांकel.com>
 */
#अगर_अघोषित _PLATFORM_SST_AUDIO_H_
#घोषणा _PLATFORM_SST_AUDIO_H_

#घोषणा MAX_NUM_STREAMS_MRFLD	25
#घोषणा MAX_NUM_STREAMS	MAX_NUM_STREAMS_MRFLD

क्रमागत sst_audio_task_id_mrfld अणु
	SST_TASK_ID_NONE = 0,
	SST_TASK_ID_SBA = 1,
	SST_TASK_ID_MEDIA = 3,
	SST_TASK_ID_MAX = SST_TASK_ID_MEDIA,
पूर्ण;

/* Device IDs क्रम Merrअगरield are Pipe IDs,
 * ref: DSP spec v0.75 */
क्रमागत sst_audio_device_id_mrfld अणु
	/* Output pipeline IDs */
	PIPE_ID_OUT_START = 0x0,
	PIPE_CODEC_OUT0 = 0x2,
	PIPE_CODEC_OUT1 = 0x3,
	PIPE_SPROT_LOOP_OUT = 0x4,
	PIPE_MEDIA_LOOP1_OUT = 0x5,
	PIPE_MEDIA_LOOP2_OUT = 0x6,
	PIPE_VOIP_OUT = 0xC,
	PIPE_PCM0_OUT = 0xD,
	PIPE_PCM1_OUT = 0xE,
	PIPE_PCM2_OUT = 0xF,
	PIPE_MEDIA0_OUT = 0x12,
	PIPE_MEDIA1_OUT = 0x13,
/* Input Pipeline IDs */
	PIPE_ID_IN_START = 0x80,
	PIPE_CODEC_IN0 = 0x82,
	PIPE_CODEC_IN1 = 0x83,
	PIPE_SPROT_LOOP_IN = 0x84,
	PIPE_MEDIA_LOOP1_IN = 0x85,
	PIPE_MEDIA_LOOP2_IN = 0x86,
	PIPE_VOIP_IN = 0x8C,
	PIPE_PCM0_IN = 0x8D,
	PIPE_PCM1_IN = 0x8E,
	PIPE_MEDIA0_IN = 0x8F,
	PIPE_MEDIA1_IN = 0x90,
	PIPE_MEDIA2_IN = 0x91,
	PIPE_MEDIA3_IN = 0x9C,
	PIPE_RSVD = 0xFF,
पूर्ण;

/* The stream map क्रम each platक्रमm consists of an array of the below
 * stream map काष्ठाure.
 */
काष्ठा sst_dev_stream_map अणु
	u8 dev_num;		/* device id */
	u8 subdev_num;		/* substream */
	u8 direction;
	u8 device_id;		/* fw id */
	u8 task_id;		/* fw task */
	u8 status;
पूर्ण;

काष्ठा sst_platक्रमm_data अणु
	/* Intel software platक्रमm id*/
	काष्ठा sst_dev_stream_map *pdev_strm_map;
	अचिन्हित पूर्णांक strm_map_size;
पूर्ण;

काष्ठा sst_info अणु
	u32 iram_start;
	u32 iram_end;
	bool iram_use;
	u32 dram_start;
	u32 dram_end;
	bool dram_use;
	u32 imr_start;
	u32 imr_end;
	bool imr_use;
	u32 mailbox_start;
	bool use_elf;
	bool lpe_viewpt_rqd;
	अचिन्हित पूर्णांक max_streams;
	u32 dma_max_len;
	u8 num_probes;
पूर्ण;

काष्ठा sst_lib_dnld_info अणु
	अचिन्हित पूर्णांक mod_base;
	अचिन्हित पूर्णांक mod_end;
	अचिन्हित पूर्णांक mod_table_offset;
	अचिन्हित पूर्णांक mod_table_size;
	bool mod_ddr_dnld;
पूर्ण;

काष्ठा sst_res_info अणु
	अचिन्हित पूर्णांक shim_offset;
	अचिन्हित पूर्णांक shim_size;
	अचिन्हित पूर्णांक shim_phy_addr;
	अचिन्हित पूर्णांक ssp0_offset;
	अचिन्हित पूर्णांक ssp0_size;
	अचिन्हित पूर्णांक dma0_offset;
	अचिन्हित पूर्णांक dma0_size;
	अचिन्हित पूर्णांक dma1_offset;
	अचिन्हित पूर्णांक dma1_size;
	अचिन्हित पूर्णांक iram_offset;
	अचिन्हित पूर्णांक iram_size;
	अचिन्हित पूर्णांक dram_offset;
	अचिन्हित पूर्णांक dram_size;
	अचिन्हित पूर्णांक mbox_offset;
	अचिन्हित पूर्णांक mbox_size;
	अचिन्हित पूर्णांक acpi_lpe_res_index;
	अचिन्हित पूर्णांक acpi_ddr_index;
	अचिन्हित पूर्णांक acpi_ipc_irq_index;
पूर्ण;

काष्ठा sst_ipc_info अणु
	पूर्णांक ipc_offset;
	अचिन्हित पूर्णांक mbox_recv_off;
पूर्ण;

काष्ठा sst_platक्रमm_info अणु
	स्थिर काष्ठा sst_info *probe_data;
	स्थिर काष्ठा sst_ipc_info *ipc_info;
	स्थिर काष्ठा sst_res_info *res_info;
	स्थिर काष्ठा sst_lib_dnld_info *lib_info;
	स्थिर अक्षर *platक्रमm;
	bool streams_lost_on_suspend;
पूर्ण;
पूर्णांक add_sst_platक्रमm_device(व्योम);
#पूर्ण_अगर

