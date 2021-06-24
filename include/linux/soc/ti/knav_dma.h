<शैली गुरु>
/*
 * Copyright (C) 2014 Texas Instruments Incorporated
 * Authors:	Sandeep Nair <sandeep_n@ti.com
 *		Cyril Chemparathy <cyril@ti.com
		Santosh Shilimkar <santosh.shilimkar@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित __SOC_TI_KEYSTONE_NAVIGATOR_DMA_H__
#घोषणा __SOC_TI_KEYSTONE_NAVIGATOR_DMA_H__

#समावेश <linux/dmaengine.h>

/*
 * PKTDMA descriptor manipulation macros क्रम host packet descriptor
 */
#घोषणा MASK(x)					(BIT(x) - 1)
#घोषणा KNAV_DMA_DESC_PKT_LEN_MASK		MASK(22)
#घोषणा KNAV_DMA_DESC_PKT_LEN_SHIFT		0
#घोषणा KNAV_DMA_DESC_PS_INFO_IN_SOP		BIT(22)
#घोषणा KNAV_DMA_DESC_PS_INFO_IN_DESC		0
#घोषणा KNAV_DMA_DESC_TAG_MASK			MASK(8)
#घोषणा KNAV_DMA_DESC_SAG_HI_SHIFT		24
#घोषणा KNAV_DMA_DESC_STAG_LO_SHIFT		16
#घोषणा KNAV_DMA_DESC_DTAG_HI_SHIFT		8
#घोषणा KNAV_DMA_DESC_DTAG_LO_SHIFT		0
#घोषणा KNAV_DMA_DESC_HAS_EPIB			BIT(31)
#घोषणा KNAV_DMA_DESC_NO_EPIB			0
#घोषणा KNAV_DMA_DESC_PSLEN_SHIFT		24
#घोषणा KNAV_DMA_DESC_PSLEN_MASK		MASK(6)
#घोषणा KNAV_DMA_DESC_ERR_FLAG_SHIFT		20
#घोषणा KNAV_DMA_DESC_ERR_FLAG_MASK		MASK(4)
#घोषणा KNAV_DMA_DESC_PSFLAG_SHIFT		16
#घोषणा KNAV_DMA_DESC_PSFLAG_MASK		MASK(4)
#घोषणा KNAV_DMA_DESC_RETQ_SHIFT		0
#घोषणा KNAV_DMA_DESC_RETQ_MASK			MASK(14)
#घोषणा KNAV_DMA_DESC_BUF_LEN_MASK		MASK(22)
#घोषणा KNAV_DMA_DESC_EFLAGS_MASK		MASK(4)
#घोषणा KNAV_DMA_DESC_EFLAGS_SHIFT		20

#घोषणा KNAV_DMA_NUM_EPIB_WORDS			4
#घोषणा KNAV_DMA_NUM_PS_WORDS			16
#घोषणा KNAV_DMA_NUM_SW_DATA_WORDS		4
#घोषणा KNAV_DMA_FDQ_PER_CHAN			4

/* Tx channel scheduling priority */
क्रमागत knav_dma_tx_priority अणु
	DMA_PRIO_HIGH	= 0,
	DMA_PRIO_MED_H,
	DMA_PRIO_MED_L,
	DMA_PRIO_LOW
पूर्ण;

/* Rx channel error handling mode during buffer starvation */
क्रमागत knav_dma_rx_err_mode अणु
	DMA_DROP = 0,
	DMA_RETRY
पूर्ण;

/* Rx flow size threshold configuration */
क्रमागत knav_dma_rx_thresholds अणु
	DMA_THRESH_NONE		= 0,
	DMA_THRESH_0		= 1,
	DMA_THRESH_0_1		= 3,
	DMA_THRESH_0_1_2	= 7
पूर्ण;

/* Descriptor type */
क्रमागत knav_dma_desc_type अणु
	DMA_DESC_HOST = 0,
	DMA_DESC_MONOLITHIC = 2
पूर्ण;

/**
 * काष्ठा knav_dma_tx_cfg:	Tx channel configuration
 * @filt_einfo:			Filter extended packet info
 * @filt_pswords:		Filter PS words present
 * @knav_dma_tx_priority:	Tx channel scheduling priority
 */
काष्ठा knav_dma_tx_cfg अणु
	bool				filt_einfo;
	bool				filt_pswords;
	क्रमागत knav_dma_tx_priority	priority;
पूर्ण;

/**
 * काष्ठा knav_dma_rx_cfg:	Rx flow configuration
 * @einfo_present:		Extended packet info present
 * @psinfo_present:		PS words present
 * @knav_dma_rx_err_mode:	Error during buffer starvation
 * @knav_dma_desc_type:	Host or Monolithic desc
 * @psinfo_at_sop:		PS word located at start of packet
 * @sop_offset:			Start of packet offset
 * @dst_q:			Destination queue क्रम a given flow
 * @thresh:			Rx flow size threshold
 * @fdq[]:			Free desc Queue array
 * @sz_thresh0:			RX packet size threshold 0
 * @sz_thresh1:			RX packet size threshold 1
 * @sz_thresh2:			RX packet size threshold 2
 */
काष्ठा knav_dma_rx_cfg अणु
	bool				einfo_present;
	bool				psinfo_present;
	क्रमागत knav_dma_rx_err_mode	err_mode;
	क्रमागत knav_dma_desc_type		desc_type;
	bool				psinfo_at_sop;
	अचिन्हित पूर्णांक			sop_offset;
	अचिन्हित पूर्णांक			dst_q;
	क्रमागत knav_dma_rx_thresholds	thresh;
	अचिन्हित पूर्णांक			fdq[KNAV_DMA_FDQ_PER_CHAN];
	अचिन्हित पूर्णांक			sz_thresh0;
	अचिन्हित पूर्णांक			sz_thresh1;
	अचिन्हित पूर्णांक			sz_thresh2;
पूर्ण;

/**
 * काष्ठा knav_dma_cfg:	Pktdma channel configuration
 * @sl_cfg:			Slave configuration
 * @tx:				Tx channel configuration
 * @rx:				Rx flow configuration
 */
काष्ठा knav_dma_cfg अणु
	क्रमागत dma_transfer_direction direction;
	जोड़ अणु
		काष्ठा knav_dma_tx_cfg	tx;
		काष्ठा knav_dma_rx_cfg	rx;
	पूर्ण u;
पूर्ण;

/**
 * काष्ठा knav_dma_desc:	Host packet descriptor layout
 * @desc_info:			Descriptor inक्रमmation like id, type, length
 * @tag_info:			Flow tag info written in during RX
 * @packet_info:		Queue Manager, policy, flags etc
 * @buff_len:			Buffer length in bytes
 * @buff:			Buffer poपूर्णांकer
 * @next_desc:			For chaining the descriptors
 * @orig_len:			length since 'buff_len' can be overwritten
 * @orig_buff:			buff poपूर्णांकer since 'buff' can be overwritten
 * @epib:			Extended packet info block
 * @psdata:			Protocol specअगरic
 * @sw_data:			Software निजी data not touched by h/w
 */
काष्ठा knav_dma_desc अणु
	__le32	desc_info;
	__le32	tag_info;
	__le32	packet_info;
	__le32	buff_len;
	__le32	buff;
	__le32	next_desc;
	__le32	orig_len;
	__le32	orig_buff;
	__le32	epib[KNAV_DMA_NUM_EPIB_WORDS];
	__le32	psdata[KNAV_DMA_NUM_PS_WORDS];
	u32	sw_data[KNAV_DMA_NUM_SW_DATA_WORDS];
पूर्ण ____cacheline_aligned;

#अगर IS_ENABLED(CONFIG_KEYSTONE_NAVIGATOR_DMA)
व्योम *knav_dma_खोलो_channel(काष्ठा device *dev, स्थिर अक्षर *name,
				काष्ठा knav_dma_cfg *config);
व्योम knav_dma_बंद_channel(व्योम *channel);
पूर्णांक knav_dma_get_flow(व्योम *channel);
bool knav_dma_device_पढ़ोy(व्योम);
#अन्यथा
अटल अंतरभूत व्योम *knav_dma_खोलो_channel(काष्ठा device *dev, स्थिर अक्षर *name,
				काष्ठा knav_dma_cfg *config)
अणु
	वापस (व्योम *) शून्य;
पूर्ण
अटल अंतरभूत व्योम knav_dma_बंद_channel(व्योम *channel)
अणुपूर्ण

अटल अंतरभूत पूर्णांक knav_dma_get_flow(व्योम *channel)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत bool knav_dma_device_पढ़ोy(व्योम)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* __SOC_TI_KEYSTONE_NAVIGATOR_DMA_H__ */
