<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Copyright (C) 2019 Texas Instruments Incorporated - https://www.ti.com
 */

#अगर_अघोषित K3_PSIL_H_
#घोषणा K3_PSIL_H_

#समावेश <linux/types.h>

#घोषणा K3_PSIL_DST_THREAD_ID_OFFSET 0x8000

काष्ठा device;

/**
 * क्रमागत udma_tp_level - Channel Throughput Levels
 * @UDMA_TP_NORMAL:	Normal channel
 * @UDMA_TP_HIGH:	High Throughput channel
 * @UDMA_TP_ULTRAHIGH:	Ultra High Throughput channel
 */
क्रमागत udma_tp_level अणु
	UDMA_TP_NORMAL = 0,
	UDMA_TP_HIGH,
	UDMA_TP_ULTRAHIGH,
	UDMA_TP_LAST,
पूर्ण;

/**
 * क्रमागत psil_endpoपूर्णांक_type - PSI-L Endpoपूर्णांक type
 * @PSIL_EP_NATIVE:	Normal channel
 * @PSIL_EP_PDMA_XY:	XY mode PDMA
 * @PSIL_EP_PDMA_MCAN:	MCAN mode PDMA
 * @PSIL_EP_PDMA_AASRC: AASRC mode PDMA
 */
क्रमागत psil_endpoपूर्णांक_type अणु
	PSIL_EP_NATIVE = 0,
	PSIL_EP_PDMA_XY,
	PSIL_EP_PDMA_MCAN,
	PSIL_EP_PDMA_AASRC,
पूर्ण;

/**
 * काष्ठा psil_endpoपूर्णांक_config - PSI-L Endpoपूर्णांक configuration
 * @ep_type:		PSI-L endpoपूर्णांक type
 * @channel_tpl:	Desired throughput level क्रम the channel
 * @pkt_mode:		If set, the channel must be in Packet mode, otherwise in
 *			TR mode
 * @notdpkt:		TDCM must be suppressed on the TX channel
 * @needs_epib:		Endpoपूर्णांक needs EPIB
 * @pdma_acc32:		ACC32 must be enabled on the PDMA side
 * @pdma_burst:		BURST must be enabled on the PDMA side
 * @psd_size:		If set, PSdata is used by the endpoपूर्णांक
 * @mapped_channel_id:	PKTDMA thपढ़ो to channel mapping क्रम mapped channels.
 *			The thपढ़ो must be serviced by the specअगरied channel अगर
 *			mapped_channel_id is >= 0 in हाल of PKTDMA
 * @flow_start:		PKDMA flow range start of mapped channel. Unmapped
 *			channels use flow_id == chan_id
 * @flow_num:		PKDMA flow count of mapped channel. Unmapped channels
 *			use flow_id == chan_id
 * @शेष_flow_id:	PKDMA शेष (r)flow index of mapped channel.
 *			Must be within the flow range of the mapped channel.
 */
काष्ठा psil_endpoपूर्णांक_config अणु
	क्रमागत psil_endpoपूर्णांक_type ep_type;
	क्रमागत udma_tp_level channel_tpl;

	अचिन्हित pkt_mode:1;
	अचिन्हित notdpkt:1;
	अचिन्हित needs_epib:1;
	/* PDMA properties, valid क्रम PSIL_EP_PDMA_* */
	अचिन्हित pdma_acc32:1;
	अचिन्हित pdma_burst:1;

	u32 psd_size;
	/* PKDMA mapped channel */
	s16 mapped_channel_id;
	/* PKTDMA tflow and rflow ranges क्रम mapped channel */
	u16 flow_start;
	u16 flow_num;
	s16 शेष_flow_id;
पूर्ण;

पूर्णांक psil_set_new_ep_config(काष्ठा device *dev, स्थिर अक्षर *name,
			   काष्ठा psil_endpoपूर्णांक_config *ep_config);

#पूर्ण_अगर /* K3_PSIL_H_ */
