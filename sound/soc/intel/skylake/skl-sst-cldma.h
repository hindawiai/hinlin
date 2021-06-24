<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Intel Code Loader DMA support
 *
 * Copyright (C) 2015, Intel Corporation.
 */

#अगर_अघोषित SKL_SST_CLDMA_H_
#घोषणा SKL_SST_CLDMA_H_

#घोषणा FW_CL_STREAM_NUMBER		0x1

#घोषणा DMA_ADDRESS_128_BITS_ALIGNMENT	7
#घोषणा BDL_ALIGN(x)			(x >> DMA_ADDRESS_128_BITS_ALIGNMENT)

#घोषणा SKL_ADSPIC_CL_DMA			0x2
#घोषणा SKL_ADSPIS_CL_DMA			0x2
#घोषणा SKL_CL_DMA_SD_INT_DESC_ERR		0x10 /* Descriptor error पूर्णांकerrupt */
#घोषणा SKL_CL_DMA_SD_INT_FIFO_ERR		0x08 /* FIFO error पूर्णांकerrupt */
#घोषणा SKL_CL_DMA_SD_INT_COMPLETE		0x04 /* Buffer completion पूर्णांकerrupt */

/* Intel HD Audio Code Loader DMA Registers */

#घोषणा HDA_ADSP_LOADER_BASE		0x80

/* Stream Registers */
#घोषणा SKL_ADSP_REG_CL_SD_CTL			(HDA_ADSP_LOADER_BASE + 0x00)
#घोषणा SKL_ADSP_REG_CL_SD_STS			(HDA_ADSP_LOADER_BASE + 0x03)
#घोषणा SKL_ADSP_REG_CL_SD_LPIB			(HDA_ADSP_LOADER_BASE + 0x04)
#घोषणा SKL_ADSP_REG_CL_SD_CBL			(HDA_ADSP_LOADER_BASE + 0x08)
#घोषणा SKL_ADSP_REG_CL_SD_LVI			(HDA_ADSP_LOADER_BASE + 0x0c)
#घोषणा SKL_ADSP_REG_CL_SD_FIFOW		(HDA_ADSP_LOADER_BASE + 0x0e)
#घोषणा SKL_ADSP_REG_CL_SD_FIFOSIZE		(HDA_ADSP_LOADER_BASE + 0x10)
#घोषणा SKL_ADSP_REG_CL_SD_FORMAT		(HDA_ADSP_LOADER_BASE + 0x12)
#घोषणा SKL_ADSP_REG_CL_SD_FIFOL		(HDA_ADSP_LOADER_BASE + 0x14)
#घोषणा SKL_ADSP_REG_CL_SD_BDLPL		(HDA_ADSP_LOADER_BASE + 0x18)
#घोषणा SKL_ADSP_REG_CL_SD_BDLPU		(HDA_ADSP_LOADER_BASE + 0x1c)

/* CL: Software Position Based FIFO Capability Registers */
#घोषणा SKL_ADSP_REG_CL_SPBFIFO			(HDA_ADSP_LOADER_BASE + 0x20)
#घोषणा SKL_ADSP_REG_CL_SPBFIFO_SPBFCH		(SKL_ADSP_REG_CL_SPBFIFO + 0x0)
#घोषणा SKL_ADSP_REG_CL_SPBFIFO_SPBFCCTL	(SKL_ADSP_REG_CL_SPBFIFO + 0x4)
#घोषणा SKL_ADSP_REG_CL_SPBFIFO_SPIB		(SKL_ADSP_REG_CL_SPBFIFO + 0x8)
#घोषणा SKL_ADSP_REG_CL_SPBFIFO_MAXFIFOS	(SKL_ADSP_REG_CL_SPBFIFO + 0xc)

/* CL: Stream Descriptor x Control */

/* Stream Reset */
#घोषणा CL_SD_CTL_SRST_SHIFT		0
#घोषणा CL_SD_CTL_SRST_MASK		(1 << CL_SD_CTL_SRST_SHIFT)
#घोषणा CL_SD_CTL_SRST(x)		\
			((x << CL_SD_CTL_SRST_SHIFT) & CL_SD_CTL_SRST_MASK)

/* Stream Run */
#घोषणा CL_SD_CTL_RUN_SHIFT		1
#घोषणा CL_SD_CTL_RUN_MASK		(1 << CL_SD_CTL_RUN_SHIFT)
#घोषणा CL_SD_CTL_RUN(x)		\
			((x << CL_SD_CTL_RUN_SHIFT) & CL_SD_CTL_RUN_MASK)

/* Interrupt On Completion Enable */
#घोषणा CL_SD_CTL_IOCE_SHIFT		2
#घोषणा CL_SD_CTL_IOCE_MASK		(1 << CL_SD_CTL_IOCE_SHIFT)
#घोषणा CL_SD_CTL_IOCE(x)		\
			((x << CL_SD_CTL_IOCE_SHIFT) & CL_SD_CTL_IOCE_MASK)

/* FIFO Error Interrupt Enable */
#घोषणा CL_SD_CTL_FEIE_SHIFT		3
#घोषणा CL_SD_CTL_FEIE_MASK		(1 << CL_SD_CTL_FEIE_SHIFT)
#घोषणा CL_SD_CTL_FEIE(x)		\
			((x << CL_SD_CTL_FEIE_SHIFT) & CL_SD_CTL_FEIE_MASK)

/* Descriptor Error Interrupt Enable */
#घोषणा CL_SD_CTL_DEIE_SHIFT		4
#घोषणा CL_SD_CTL_DEIE_MASK		(1 << CL_SD_CTL_DEIE_SHIFT)
#घोषणा CL_SD_CTL_DEIE(x)		\
			((x << CL_SD_CTL_DEIE_SHIFT) & CL_SD_CTL_DEIE_MASK)

/* FIFO Limit Change */
#घोषणा CL_SD_CTL_FIFOLC_SHIFT		5
#घोषणा CL_SD_CTL_FIFOLC_MASK		(1 << CL_SD_CTL_FIFOLC_SHIFT)
#घोषणा CL_SD_CTL_FIFOLC(x)		\
			((x << CL_SD_CTL_FIFOLC_SHIFT) & CL_SD_CTL_FIFOLC_MASK)

/* Stripe Control */
#घोषणा CL_SD_CTL_STRIPE_SHIFT		16
#घोषणा CL_SD_CTL_STRIPE_MASK		(0x3 << CL_SD_CTL_STRIPE_SHIFT)
#घोषणा CL_SD_CTL_STRIPE(x)		\
			((x << CL_SD_CTL_STRIPE_SHIFT) & CL_SD_CTL_STRIPE_MASK)

/* Traffic Priority */
#घोषणा CL_SD_CTL_TP_SHIFT		18
#घोषणा CL_SD_CTL_TP_MASK		(1 << CL_SD_CTL_TP_SHIFT)
#घोषणा CL_SD_CTL_TP(x)			\
			((x << CL_SD_CTL_TP_SHIFT) & CL_SD_CTL_TP_MASK)

/* Bidirectional Direction Control */
#घोषणा CL_SD_CTL_सूची_SHIFT		19
#घोषणा CL_SD_CTL_सूची_MASK		(1 << CL_SD_CTL_सूची_SHIFT)
#घोषणा CL_SD_CTL_सूची(x)		\
			((x << CL_SD_CTL_सूची_SHIFT) & CL_SD_CTL_सूची_MASK)

/* Stream Number */
#घोषणा CL_SD_CTL_STRM_SHIFT		20
#घोषणा CL_SD_CTL_STRM_MASK		(0xf << CL_SD_CTL_STRM_SHIFT)
#घोषणा CL_SD_CTL_STRM(x)		\
			((x << CL_SD_CTL_STRM_SHIFT) & CL_SD_CTL_STRM_MASK)

/* CL: Stream Descriptor x Status */

/* Buffer Completion Interrupt Status */
#घोषणा CL_SD_STS_BCIS(x)		CL_SD_CTL_IOCE(x)

/* FIFO Error */
#घोषणा CL_SD_STS_FIFOE(x)		CL_SD_CTL_FEIE(x)

/* Descriptor Error */
#घोषणा CL_SD_STS_DESE(x)		CL_SD_CTL_DEIE(x)

/* FIFO Ready */
#घोषणा CL_SD_STS_FIFORDY(x)	CL_SD_CTL_FIFOLC(x)


/* CL: Stream Descriptor x Last Valid Index */
#घोषणा CL_SD_LVI_SHIFT			0
#घोषणा CL_SD_LVI_MASK			(0xff << CL_SD_LVI_SHIFT)
#घोषणा CL_SD_LVI(x)			((x << CL_SD_LVI_SHIFT) & CL_SD_LVI_MASK)

/* CL: Stream Descriptor x FIFO Eviction Watermark */
#घोषणा CL_SD_FIFOW_SHIFT		0
#घोषणा CL_SD_FIFOW_MASK		(0x7 << CL_SD_FIFOW_SHIFT)
#घोषणा CL_SD_FIFOW(x)			\
			((x << CL_SD_FIFOW_SHIFT) & CL_SD_FIFOW_MASK)

/* CL: Stream Descriptor x Buffer Descriptor List Poपूर्णांकer Lower Base Address */

/* Protect Bits */
#घोषणा CL_SD_BDLPLBA_PROT_SHIFT	0
#घोषणा CL_SD_BDLPLBA_PROT_MASK		(1 << CL_SD_BDLPLBA_PROT_SHIFT)
#घोषणा CL_SD_BDLPLBA_PROT(x)		\
		((x << CL_SD_BDLPLBA_PROT_SHIFT) & CL_SD_BDLPLBA_PROT_MASK)

/* Buffer Descriptor List Lower Base Address */
#घोषणा CL_SD_BDLPLBA_SHIFT		7
#घोषणा CL_SD_BDLPLBA_MASK		(0x1ffffff << CL_SD_BDLPLBA_SHIFT)
#घोषणा CL_SD_BDLPLBA(x)		\
	((BDL_ALIGN(lower_32_bits(x)) << CL_SD_BDLPLBA_SHIFT) & CL_SD_BDLPLBA_MASK)

/* Buffer Descriptor List Upper Base Address */
#घोषणा CL_SD_BDLPUBA_SHIFT		0
#घोषणा CL_SD_BDLPUBA_MASK		(0xffffffff << CL_SD_BDLPUBA_SHIFT)
#घोषणा CL_SD_BDLPUBA(x)		\
		((upper_32_bits(x) << CL_SD_BDLPUBA_SHIFT) & CL_SD_BDLPUBA_MASK)

/*
 * Code Loader - Software Position Based FIFO
 * Capability Registers x Software Position Based FIFO Header
 */

/* Next Capability Poपूर्णांकer */
#घोषणा CL_SPBFIFO_SPBFCH_PTR_SHIFT	0
#घोषणा CL_SPBFIFO_SPBFCH_PTR_MASK	(0xff << CL_SPBFIFO_SPBFCH_PTR_SHIFT)
#घोषणा CL_SPBFIFO_SPBFCH_PTR(x)	\
		((x << CL_SPBFIFO_SPBFCH_PTR_SHIFT) & CL_SPBFIFO_SPBFCH_PTR_MASK)

/* Capability Identअगरier */
#घोषणा CL_SPBFIFO_SPBFCH_ID_SHIFT	16
#घोषणा CL_SPBFIFO_SPBFCH_ID_MASK	(0xfff << CL_SPBFIFO_SPBFCH_ID_SHIFT)
#घोषणा CL_SPBFIFO_SPBFCH_ID(x)		\
		((x << CL_SPBFIFO_SPBFCH_ID_SHIFT) & CL_SPBFIFO_SPBFCH_ID_MASK)

/* Capability Version */
#घोषणा CL_SPBFIFO_SPBFCH_VER_SHIFT	28
#घोषणा CL_SPBFIFO_SPBFCH_VER_MASK	(0xf << CL_SPBFIFO_SPBFCH_VER_SHIFT)
#घोषणा CL_SPBFIFO_SPBFCH_VER(x)	\
	((x << CL_SPBFIFO_SPBFCH_VER_SHIFT) & CL_SPBFIFO_SPBFCH_VER_MASK)

/* Software Position in Buffer Enable */
#घोषणा CL_SPBFIFO_SPBFCCTL_SPIBE_SHIFT	0
#घोषणा CL_SPBFIFO_SPBFCCTL_SPIBE_MASK	(1 << CL_SPBFIFO_SPBFCCTL_SPIBE_SHIFT)
#घोषणा CL_SPBFIFO_SPBFCCTL_SPIBE(x)	\
	((x << CL_SPBFIFO_SPBFCCTL_SPIBE_SHIFT) & CL_SPBFIFO_SPBFCCTL_SPIBE_MASK)

/* SST IPC SKL defines */
#घोषणा SKL_WAIT_TIMEOUT		500	/* 500 msec */
#घोषणा SKL_MAX_BUFFER_SIZE		(32 * PAGE_SIZE)

क्रमागत skl_cl_dma_wake_states अणु
	SKL_CL_DMA_STATUS_NONE = 0,
	SKL_CL_DMA_BUF_COMPLETE,
	SKL_CL_DMA_ERR,	/* TODO: Expand the error states */
पूर्ण;

काष्ठा sst_dsp;

काष्ठा skl_cl_dev_ops अणु
	व्योम (*cl_setup_bdle)(काष्ठा sst_dsp *ctx,
			काष्ठा snd_dma_buffer *dmab_data,
			__le32 **bdlp, पूर्णांक size, पूर्णांक with_ioc);
	व्योम (*cl_setup_controller)(काष्ठा sst_dsp *ctx,
			काष्ठा snd_dma_buffer *dmab_bdl,
			अचिन्हित पूर्णांक max_size, u32 page_count);
	व्योम (*cl_setup_spb)(काष्ठा sst_dsp  *ctx,
			अचिन्हित पूर्णांक size, bool enable);
	व्योम (*cl_cleanup_spb)(काष्ठा sst_dsp  *ctx);
	व्योम (*cl_trigger)(काष्ठा sst_dsp  *ctx, bool enable);
	व्योम (*cl_cleanup_controller)(काष्ठा sst_dsp  *ctx);
	पूर्णांक (*cl_copy_to_dmabuf)(काष्ठा sst_dsp *ctx,
			स्थिर व्योम *bin, u32 size, bool रुको);
	व्योम (*cl_stop_dma)(काष्ठा sst_dsp *ctx);
पूर्ण;

/**
 * skl_cl_dev - holds inक्रमmation क्रम code loader dma transfer
 *
 * @dmab_data: buffer poपूर्णांकer
 * @dmab_bdl: buffer descriptor list
 * @bufsize: ring buffer size
 * @frags: Last valid buffer descriptor index in the BDL
 * @curr_spib_pos: Current position in ring buffer
 * @dma_buffer_offset: dma buffer offset
 * @ops: operations supported on CL dma
 * @रुको_queue: रुको queue to wake क्रम wake event
 * @wake_status: DMA wake status
 * @रुको_condition: condition to रुको on रुको queue
 * @cl_dma_lock: क्रम synchronized access to cldma
 */
काष्ठा skl_cl_dev अणु
	काष्ठा snd_dma_buffer dmab_data;
	काष्ठा snd_dma_buffer dmab_bdl;

	अचिन्हित पूर्णांक bufsize;
	अचिन्हित पूर्णांक frags;

	अचिन्हित पूर्णांक curr_spib_pos;
	अचिन्हित पूर्णांक dma_buffer_offset;
	काष्ठा skl_cl_dev_ops ops;

	रुको_queue_head_t रुको_queue;
	पूर्णांक wake_status;
	bool रुको_condition;
पूर्ण;

#पूर्ण_अगर /* SKL_SST_CLDMA_H_ */
