<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Audio support क्रम PS3
 * Copyright (C) 2007 Sony Computer Entertainment Inc.
 * All rights reserved.
 * Copyright 2006, 2007 Sony Corporation
 */

#अगर !defined(_SND_PS3_H_)
#घोषणा _SND_PS3_H_

#समावेश <linux/irqवापस.h>

#घोषणा SND_PS3_DRIVER_NAME "snd_ps3"

क्रमागत snd_ps3_out_channel अणु
	SND_PS3_OUT_SPDIF_0,
	SND_PS3_OUT_SPDIF_1,
	SND_PS3_OUT_SERIAL_0,
	SND_PS3_OUT_DEVS
पूर्ण;

क्रमागत snd_ps3_dma_filltype अणु
	SND_PS3_DMA_FILLTYPE_FIRSTFILL,
	SND_PS3_DMA_FILLTYPE_RUNNING,
	SND_PS3_DMA_FILLTYPE_SILENT_FIRSTFILL,
	SND_PS3_DMA_FILLTYPE_SILENT_RUNNING
पूर्ण;

क्रमागत snd_ps3_ch अणु
	SND_PS3_CH_L = 0,
	SND_PS3_CH_R = 1,
	SND_PS3_CH_MAX = 2
पूर्ण;

काष्ठा snd_ps3_avsetting_info अणु
	uपूर्णांक32_t avs_audio_ch;     /* fixed */
	uपूर्णांक32_t avs_audio_rate;
	uपूर्णांक32_t avs_audio_width;
	uपूर्णांक32_t avs_audio_क्रमmat; /* fixed */
	uपूर्णांक32_t avs_audio_source; /* fixed */
	अचिन्हित अक्षर avs_cs_info[8];
पूर्ण;
/*
 * PS3 audio 'card' instance
 * there should be only ONE hardware.
 */
काष्ठा snd_ps3_card_info अणु
	काष्ठा ps3_प्रणाली_bus_device *ps3_dev;
	काष्ठा snd_card *card;

	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm_substream *substream;

	/* hvc info */
	u64 audio_lpar_addr;
	u64 audio_lpar_size;

	/* रेजिस्टरs */
	व्योम __iomem *mapped_mmio_vaddr;

	/* irq */
	u64 audio_irq_outlet;
	अचिन्हित पूर्णांक irq_no;

	/* remember avsetting */
	काष्ठा snd_ps3_avsetting_info avs;

	/* dma buffer management */
	spinlock_t dma_lock;
		/* dma_lock start */
		व्योम * dma_start_vaddr[2]; /* 0 क्रम L, 1 क्रम R */
		dma_addr_t dma_start_bus_addr[2];
		माप_प्रकार dma_buffer_size;
		व्योम * dma_last_transfer_vaddr[2];
		व्योम * dma_next_transfer_vaddr[2];
		पूर्णांक    silent;
		/* dma_lock end */

	पूर्णांक running;

	/* null buffer */
	व्योम *null_buffer_start_vaddr;
	dma_addr_t null_buffer_start_dma_addr;

	/* start delay */
	अचिन्हित पूर्णांक start_delay;

पूर्ण;


/* PS3 audio DMAC block size in bytes */
#घोषणा PS3_AUDIO_DMAC_BLOCK_SIZE (128)
/* one stage (stereo)  of audio FIFO in bytes */
#घोषणा PS3_AUDIO_FIFO_STAGE_SIZE (256)
/* how many stages the fअगरo have */
#घोषणा PS3_AUDIO_FIFO_STAGE_COUNT (8)
/* fअगरo size 128 bytes * 8 stages * stereo (2ch) */
#घोषणा PS3_AUDIO_FIFO_SIZE \
	(PS3_AUDIO_FIFO_STAGE_SIZE * PS3_AUDIO_FIFO_STAGE_COUNT)

/* PS3 audio DMAC max block count in one dma shot = 128 (0x80) blocks*/
#घोषणा PS3_AUDIO_DMAC_MAX_BLOCKS  (PS3_AUDIO_DMASIZE_BLOCKS_MASK + 1)

#घोषणा PS3_AUDIO_NORMAL_DMA_START_CH (0)
#घोषणा PS3_AUDIO_NORMAL_DMA_COUNT    (8)
#घोषणा PS3_AUDIO_शून्य_DMA_START_CH \
	(PS3_AUDIO_NORMAL_DMA_START_CH + PS3_AUDIO_NORMAL_DMA_COUNT)
#घोषणा PS3_AUDIO_शून्य_DMA_COUNT      (2)

#घोषणा SND_PS3_MAX_VOL (0x0F)
#घोषणा SND_PS3_MIN_VOL (0x00)
#घोषणा SND_PS3_MIN_ATT SND_PS3_MIN_VOL
#घोषणा SND_PS3_MAX_ATT SND_PS3_MAX_VOL

#घोषणा SND_PS3_PCM_PREALLOC_SIZE \
	(PS3_AUDIO_DMAC_BLOCK_SIZE * PS3_AUDIO_DMAC_MAX_BLOCKS * 4)

#घोषणा SND_PS3_DMA_REGION_SIZE \
	(SND_PS3_PCM_PREALLOC_SIZE + PAGE_SIZE)

#घोषणा PS3_AUDIO_IOID       (1UL)

#पूर्ण_अगर /* _SND_PS3_H_ */
