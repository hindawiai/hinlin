<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/* Copyright (c) 2012-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2019-2021 Linaro Ltd.
 */

#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/अगर_rmnet.h>
#समावेश <linux/dma-direction.h>

#समावेश "gsi.h"
#समावेश "gsi_trans.h"
#समावेश "ipa.h"
#समावेश "ipa_data.h"
#समावेश "ipa_endpoint.h"
#समावेश "ipa_cmd.h"
#समावेश "ipa_mem.h"
#समावेश "ipa_modem.h"
#समावेश "ipa_table.h"
#समावेश "ipa_gsi.h"
#समावेश "ipa_clock.h"

#घोषणा atomic_dec_not_zero(v)	atomic_add_unless((v), -1, 0)

#घोषणा IPA_REPLENISH_BATCH	16

/* RX buffer is 1 page (or a घातer-of-2 contiguous pages) */
#घोषणा IPA_RX_BUFFER_SIZE	8192	/* PAGE_SIZE > 4096 wastes a LOT */

/* The amount of RX buffer space consumed by standard skb overhead */
#घोषणा IPA_RX_BUFFER_OVERHEAD	(PAGE_SIZE - SKB_MAX_ORDER(NET_SKB_PAD, 0))

/* Where to find the QMAP mux_id क्रम a packet within modem-supplied metadata */
#घोषणा IPA_ENDPOINT_QMAP_METADATA_MASK		0x000000ff /* host byte order */

#घोषणा IPA_ENDPOINT_RESET_AGGR_RETRY_MAX	3
#घोषणा IPA_AGGR_TIME_LIMIT			500	/* microseconds */

/** क्रमागत ipa_status_opcode - status element opcode hardware values */
क्रमागत ipa_status_opcode अणु
	IPA_STATUS_OPCODE_PACKET		= 0x01,
	IPA_STATUS_OPCODE_DROPPED_PACKET	= 0x04,
	IPA_STATUS_OPCODE_SUSPENDED_PACKET	= 0x08,
	IPA_STATUS_OPCODE_PACKET_2ND_PASS	= 0x40,
पूर्ण;

/** क्रमागत ipa_status_exception - status element exception type */
क्रमागत ipa_status_exception अणु
	/* 0 means no exception */
	IPA_STATUS_EXCEPTION_DEAGGR		= 0x01,
पूर्ण;

/* Status element provided by hardware */
काष्ठा ipa_status अणु
	u8 opcode;		/* क्रमागत ipa_status_opcode */
	u8 exception;		/* क्रमागत ipa_status_exception */
	__le16 mask;
	__le16 pkt_len;
	u8 endp_src_idx;
	u8 endp_dst_idx;
	__le32 metadata;
	__le32 flags1;
	__le64 flags2;
	__le32 flags3;
	__le32 flags4;
पूर्ण;

/* Field masks क्रम काष्ठा ipa_status काष्ठाure fields */
#घोषणा IPA_STATUS_MASK_TAG_VALID_FMASK		GENMASK(4, 4)
#घोषणा IPA_STATUS_SRC_IDX_FMASK		GENMASK(4, 0)
#घोषणा IPA_STATUS_DST_IDX_FMASK		GENMASK(4, 0)
#घोषणा IPA_STATUS_FLAGS1_RT_RULE_ID_FMASK	GENMASK(31, 22)
#घोषणा IPA_STATUS_FLAGS2_TAG_FMASK		GENMASK_ULL(63, 16)

#अगर_घोषित IPA_VALIDATE

अटल bool ipa_endpoपूर्णांक_data_valid_one(काष्ठा ipa *ipa, u32 count,
			    स्थिर काष्ठा ipa_gsi_endpoपूर्णांक_data *all_data,
			    स्थिर काष्ठा ipa_gsi_endpoपूर्णांक_data *data)
अणु
	स्थिर काष्ठा ipa_gsi_endpoपूर्णांक_data *other_data;
	काष्ठा device *dev = &ipa->pdev->dev;
	क्रमागत ipa_endpoपूर्णांक_name other_name;

	अगर (ipa_gsi_endpoपूर्णांक_data_empty(data))
		वापस true;

	/* IPA v4.5+ uses checksum offload, not yet supported by RMNet */
	अगर (ipa->version >= IPA_VERSION_4_5)
		अगर (data->endpoपूर्णांक.config.checksum)
			वापस false;

	अगर (!data->toward_ipa) अणु
		अगर (data->endpoपूर्णांक.filter_support) अणु
			dev_err(dev, "filtering not supported for "
					"RX endpoint %u\n",
				data->endpoपूर्णांक_id);
			वापस false;
		पूर्ण

		वापस true;	/* Nothing more to check क्रम RX */
	पूर्ण

	अगर (data->endpoपूर्णांक.config.status_enable) अणु
		other_name = data->endpoपूर्णांक.config.tx.status_endpoपूर्णांक;
		अगर (other_name >= count) अणु
			dev_err(dev, "status endpoint name %u out of range "
					"for endpoint %u\n",
				other_name, data->endpoपूर्णांक_id);
			वापस false;
		पूर्ण

		/* Status endpoपूर्णांक must be defined... */
		other_data = &all_data[other_name];
		अगर (ipa_gsi_endpoपूर्णांक_data_empty(other_data)) अणु
			dev_err(dev, "DMA endpoint name %u undefined "
					"for endpoint %u\n",
				other_name, data->endpoपूर्णांक_id);
			वापस false;
		पूर्ण

		/* ...and has to be an RX endpoपूर्णांक... */
		अगर (other_data->toward_ipa) अणु
			dev_err(dev,
				"status endpoint for endpoint %u not RX\n",
				data->endpoपूर्णांक_id);
			वापस false;
		पूर्ण

		/* ...and अगर it's to be an AP endpoपूर्णांक... */
		अगर (other_data->ee_id == GSI_EE_AP) अणु
			/* ...make sure it has status enabled. */
			अगर (!other_data->endpoपूर्णांक.config.status_enable) अणु
				dev_err(dev,
					"status not enabled for endpoint %u\n",
					other_data->endpoपूर्णांक_id);
				वापस false;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (data->endpoपूर्णांक.config.dma_mode) अणु
		other_name = data->endpoपूर्णांक.config.dma_endpoपूर्णांक;
		अगर (other_name >= count) अणु
			dev_err(dev, "DMA endpoint name %u out of range "
					"for endpoint %u\n",
				other_name, data->endpoपूर्णांक_id);
			वापस false;
		पूर्ण

		other_data = &all_data[other_name];
		अगर (ipa_gsi_endpoपूर्णांक_data_empty(other_data)) अणु
			dev_err(dev, "DMA endpoint name %u undefined "
					"for endpoint %u\n",
				other_name, data->endpoपूर्णांक_id);
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल u32 aggr_byte_limit_max(क्रमागत ipa_version version)
अणु
	अगर (version < IPA_VERSION_4_5)
		वापस field_max(aggr_byte_limit_fmask(true));

	वापस field_max(aggr_byte_limit_fmask(false));
पूर्ण

अटल bool ipa_endpoपूर्णांक_data_valid(काष्ठा ipa *ipa, u32 count,
				    स्थिर काष्ठा ipa_gsi_endpoपूर्णांक_data *data)
अणु
	स्थिर काष्ठा ipa_gsi_endpoपूर्णांक_data *dp = data;
	काष्ठा device *dev = &ipa->pdev->dev;
	क्रमागत ipa_endpoपूर्णांक_name name;
	u32 limit;

	अगर (count > IPA_ENDPOINT_COUNT) अणु
		dev_err(dev, "too many endpoints specified (%u > %u)\n",
			count, IPA_ENDPOINT_COUNT);
		वापस false;
	पूर्ण

	/* The aggregation byte limit defines the poपूर्णांक at which an
	 * aggregation winकरोw will बंद.  It is programmed पूर्णांकo the
	 * IPA hardware as a number of KB.  We करोn't use "hard byte
	 * limit" aggregation, which means that we need to supply
	 * enough space in a receive buffer to hold a complete MTU
	 * plus normal skb overhead *after* that aggregation byte
	 * limit has been crossed.
	 *
	 * This check ensures we करोn't define a receive buffer size
	 * that would exceed what we can represent in the field that
	 * is used to program its size.
	 */
	limit = aggr_byte_limit_max(ipa->version) * SZ_1K;
	limit += IPA_MTU + IPA_RX_BUFFER_OVERHEAD;
	अगर (limit < IPA_RX_BUFFER_SIZE) अणु
		dev_err(dev, "buffer size too big for aggregation (%u > %u)\n",
			IPA_RX_BUFFER_SIZE, limit);
		वापस false;
	पूर्ण

	/* Make sure needed endpoपूर्णांकs have defined data */
	अगर (ipa_gsi_endpoपूर्णांक_data_empty(&data[IPA_ENDPOINT_AP_COMMAND_TX])) अणु
		dev_err(dev, "command TX endpoint not defined\n");
		वापस false;
	पूर्ण
	अगर (ipa_gsi_endpoपूर्णांक_data_empty(&data[IPA_ENDPOINT_AP_LAN_RX])) अणु
		dev_err(dev, "LAN RX endpoint not defined\n");
		वापस false;
	पूर्ण
	अगर (ipa_gsi_endpoपूर्णांक_data_empty(&data[IPA_ENDPOINT_AP_MODEM_TX])) अणु
		dev_err(dev, "AP->modem TX endpoint not defined\n");
		वापस false;
	पूर्ण
	अगर (ipa_gsi_endpoपूर्णांक_data_empty(&data[IPA_ENDPOINT_AP_MODEM_RX])) अणु
		dev_err(dev, "AP<-modem RX endpoint not defined\n");
		वापस false;
	पूर्ण

	क्रम (name = 0; name < count; name++, dp++)
		अगर (!ipa_endpoपूर्णांक_data_valid_one(ipa, count, data, dp))
			वापस false;

	वापस true;
पूर्ण

#अन्यथा /* !IPA_VALIDATE */

अटल bool ipa_endpoपूर्णांक_data_valid(काष्ठा ipa *ipa, u32 count,
				    स्थिर काष्ठा ipa_gsi_endpoपूर्णांक_data *data)
अणु
	स्थिर काष्ठा ipa_gsi_endpoपूर्णांक_data *dp = data;
	क्रमागत ipa_endpoपूर्णांक_name name;

	अगर (ipa->version < IPA_VERSION_4_5)
		वापस true;

	/* IPA v4.5+ uses checksum offload, not yet supported by RMNet */
	क्रम (name = 0; name < count; name++, dp++)
		अगर (data->endpoपूर्णांक.config.checksum)
			वापस false;

	वापस true;
पूर्ण

#पूर्ण_अगर /* !IPA_VALIDATE */

/* Allocate a transaction to use on a non-command endpoपूर्णांक */
अटल काष्ठा gsi_trans *ipa_endpoपूर्णांक_trans_alloc(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक,
						  u32 tre_count)
अणु
	काष्ठा gsi *gsi = &endpoपूर्णांक->ipa->gsi;
	u32 channel_id = endpoपूर्णांक->channel_id;
	क्रमागत dma_data_direction direction;

	direction = endpoपूर्णांक->toward_ipa ? DMA_TO_DEVICE : DMA_FROM_DEVICE;

	वापस gsi_channel_trans_alloc(gsi, channel_id, tre_count, direction);
पूर्ण

/* suspend_delay represents suspend क्रम RX, delay क्रम TX endpoपूर्णांकs.
 * Note that suspend is not supported starting with IPA v4.0.
 */
अटल bool
ipa_endpoपूर्णांक_init_ctrl(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक, bool suspend_delay)
अणु
	u32 offset = IPA_REG_ENDP_INIT_CTRL_N_OFFSET(endpoपूर्णांक->endpoपूर्णांक_id);
	काष्ठा ipa *ipa = endpoपूर्णांक->ipa;
	bool state;
	u32 mask;
	u32 val;

	/* Suspend is not supported क्रम IPA v4.0+.  Delay करोesn't work
	 * correctly on IPA v4.2.
	 *
	 * अगर (endpoपूर्णांक->toward_ipa)
	 * 	निश्चित(ipa->version != IPA_VERSION_4.2);
	 * अन्यथा
	 *	निश्चित(ipa->version < IPA_VERSION_4_0);
	 */
	mask = endpoपूर्णांक->toward_ipa ? ENDP_DELAY_FMASK : ENDP_SUSPEND_FMASK;

	val = ioपढ़ो32(ipa->reg_virt + offset);
	/* Don't bother if it's alपढ़ोy in the requested state */
	state = !!(val & mask);
	अगर (suspend_delay != state) अणु
		val ^= mask;
		ioग_लिखो32(val, ipa->reg_virt + offset);
	पूर्ण

	वापस state;
पूर्ण

/* We currently करोn't care what the previous state was क्रम delay mode */
अटल व्योम
ipa_endpoपूर्णांक_program_delay(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक, bool enable)
अणु
	/* निश्चित(endpoपूर्णांक->toward_ipa); */

	/* Delay mode करोesn't work properly क्रम IPA v4.2 */
	अगर (endpoपूर्णांक->ipa->version != IPA_VERSION_4_2)
		(व्योम)ipa_endpoपूर्णांक_init_ctrl(endpoपूर्णांक, enable);
पूर्ण

अटल bool ipa_endpoपूर्णांक_aggr_active(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक)
अणु
	u32 mask = BIT(endpoपूर्णांक->endpoपूर्णांक_id);
	काष्ठा ipa *ipa = endpoपूर्णांक->ipa;
	u32 offset;
	u32 val;

	/* निश्चित(mask & ipa->available); */
	offset = ipa_reg_state_aggr_active_offset(ipa->version);
	val = ioपढ़ो32(ipa->reg_virt + offset);

	वापस !!(val & mask);
पूर्ण

अटल व्योम ipa_endpoपूर्णांक_क्रमce_बंद(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक)
अणु
	u32 mask = BIT(endpoपूर्णांक->endpoपूर्णांक_id);
	काष्ठा ipa *ipa = endpoपूर्णांक->ipa;

	/* निश्चित(mask & ipa->available); */
	ioग_लिखो32(mask, ipa->reg_virt + IPA_REG_AGGR_FORCE_CLOSE_OFFSET);
पूर्ण

/**
 * ipa_endpoपूर्णांक_suspend_aggr() - Emulate suspend पूर्णांकerrupt
 * @endpoपूर्णांक:	Endpoपूर्णांक on which to emulate a suspend
 *
 *  Emulate suspend IPA पूर्णांकerrupt to unsuspend an endpoपूर्णांक suspended
 *  with an खोलो aggregation frame.  This is to work around a hardware
 *  issue in IPA version 3.5.1 where the suspend पूर्णांकerrupt will not be
 *  generated when it should be.
 */
अटल व्योम ipa_endpoपूर्णांक_suspend_aggr(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक)
अणु
	काष्ठा ipa *ipa = endpoपूर्णांक->ipa;

	अगर (!endpoपूर्णांक->data->aggregation)
		वापस;

	/* Nothing to करो अगर the endpoपूर्णांक करोesn't have aggregation खोलो */
	अगर (!ipa_endpoपूर्णांक_aggr_active(endpoपूर्णांक))
		वापस;

	/* Force बंद aggregation */
	ipa_endpoपूर्णांक_क्रमce_बंद(endpoपूर्णांक);

	ipa_पूर्णांकerrupt_simulate_suspend(ipa->पूर्णांकerrupt);
पूर्ण

/* Returns previous suspend state (true means suspend was enabled) */
अटल bool
ipa_endpoपूर्णांक_program_suspend(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक, bool enable)
अणु
	bool suspended;

	अगर (endpoपूर्णांक->ipa->version >= IPA_VERSION_4_0)
		वापस enable;	/* For IPA v4.0+, no change made */

	/* निश्चित(!endpoपूर्णांक->toward_ipa); */

	suspended = ipa_endpoपूर्णांक_init_ctrl(endpoपूर्णांक, enable);

	/* A client suspended with an खोलो aggregation frame will not
	 * generate a SUSPEND IPA पूर्णांकerrupt.  If enabling suspend, have
	 * ipa_endpoपूर्णांक_suspend_aggr() handle this.
	 */
	अगर (enable && !suspended)
		ipa_endpoपूर्णांक_suspend_aggr(endpoपूर्णांक);

	वापस suspended;
पूर्ण

/* Enable or disable delay or suspend mode on all modem endpoपूर्णांकs */
व्योम ipa_endpoपूर्णांक_modem_छोड़ो_all(काष्ठा ipa *ipa, bool enable)
अणु
	u32 endpoपूर्णांक_id;

	/* DELAY mode करोesn't work correctly on IPA v4.2 */
	अगर (ipa->version == IPA_VERSION_4_2)
		वापस;

	क्रम (endpoपूर्णांक_id = 0; endpoपूर्णांक_id < IPA_ENDPOपूर्णांक_उच्च; endpoपूर्णांक_id++) अणु
		काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक = &ipa->endpoपूर्णांक[endpoपूर्णांक_id];

		अगर (endpoपूर्णांक->ee_id != GSI_EE_MODEM)
			जारी;

		/* Set TX delay mode or RX suspend mode */
		अगर (endpoपूर्णांक->toward_ipa)
			ipa_endpoपूर्णांक_program_delay(endpoपूर्णांक, enable);
		अन्यथा
			(व्योम)ipa_endpoपूर्णांक_program_suspend(endpoपूर्णांक, enable);
	पूर्ण
पूर्ण

/* Reset all modem endpoपूर्णांकs to use the शेष exception endpoपूर्णांक */
पूर्णांक ipa_endpoपूर्णांक_modem_exception_reset_all(काष्ठा ipa *ipa)
अणु
	u32 initialized = ipa->initialized;
	काष्ठा gsi_trans *trans;
	u32 count;

	/* We need one command per modem TX endpoपूर्णांक.  We can get an upper
	 * bound on that by assuming all initialized endpoपूर्णांकs are modem->IPA.
	 * That won't happen, and we could be more precise, but this is fine
	 * क्रम now.  End the transaction with commands to clear the pipeline.
	 */
	count = hweight32(initialized) + ipa_cmd_pipeline_clear_count();
	trans = ipa_cmd_trans_alloc(ipa, count);
	अगर (!trans) अणु
		dev_err(&ipa->pdev->dev,
			"no transaction to reset modem exception endpoints\n");
		वापस -EBUSY;
	पूर्ण

	जबतक (initialized) अणु
		u32 endpoपूर्णांक_id = __ffs(initialized);
		काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक;
		u32 offset;

		initialized ^= BIT(endpoपूर्णांक_id);

		/* We only reset modem TX endpoपूर्णांकs */
		endpoपूर्णांक = &ipa->endpoपूर्णांक[endpoपूर्णांक_id];
		अगर (!(endpoपूर्णांक->ee_id == GSI_EE_MODEM && endpoपूर्णांक->toward_ipa))
			जारी;

		offset = IPA_REG_ENDP_STATUS_N_OFFSET(endpoपूर्णांक_id);

		/* Value written is 0, and all bits are updated.  That
		 * means status is disabled on the endpoपूर्णांक, and as a
		 * result all other fields in the रेजिस्टर are ignored.
		 */
		ipa_cmd_रेजिस्टर_ग_लिखो_add(trans, offset, 0, ~0, false);
	पूर्ण

	ipa_cmd_pipeline_clear_add(trans);

	/* XXX This should have a 1 second समयout */
	gsi_trans_commit_रुको(trans);

	ipa_cmd_pipeline_clear_रुको(ipa);

	वापस 0;
पूर्ण

अटल व्योम ipa_endpoपूर्णांक_init_cfg(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक)
अणु
	u32 offset = IPA_REG_ENDP_INIT_CFG_N_OFFSET(endpoपूर्णांक->endpoपूर्णांक_id);
	u32 val = 0;

	/* FRAG_OFFLOAD_EN is 0 */
	अगर (endpoपूर्णांक->data->checksum) अणु
		अगर (endpoपूर्णांक->toward_ipa) अणु
			u32 checksum_offset;

			val |= u32_encode_bits(IPA_CS_OFFLOAD_UL,
					       CS_OFFLOAD_EN_FMASK);
			/* Checksum header offset is in 4-byte units */
			checksum_offset = माप(काष्ठा rmnet_map_header);
			checksum_offset /= माप(u32);
			val |= u32_encode_bits(checksum_offset,
					       CS_METADATA_HDR_OFFSET_FMASK);
		पूर्ण अन्यथा अणु
			val |= u32_encode_bits(IPA_CS_OFFLOAD_DL,
					       CS_OFFLOAD_EN_FMASK);
		पूर्ण
	पूर्ण अन्यथा अणु
		val |= u32_encode_bits(IPA_CS_OFFLOAD_NONE,
				       CS_OFFLOAD_EN_FMASK);
	पूर्ण
	/* CS_GEN_QMB_MASTER_SEL is 0 */

	ioग_लिखो32(val, endpoपूर्णांक->ipa->reg_virt + offset);
पूर्ण

अटल व्योम ipa_endpoपूर्णांक_init_nat(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक)
अणु
	u32 offset;
	u32 val;

	अगर (!endpoपूर्णांक->toward_ipa)
		वापस;

	offset = IPA_REG_ENDP_INIT_NAT_N_OFFSET(endpoपूर्णांक->endpoपूर्णांक_id);
	val = u32_encode_bits(IPA_NAT_BYPASS, NAT_EN_FMASK);

	ioग_लिखो32(val, endpoपूर्णांक->ipa->reg_virt + offset);
पूर्ण

/**
 * ipa_endpoपूर्णांक_init_hdr() - Initialize HDR endpoपूर्णांक configuration रेजिस्टर
 * @endpoपूर्णांक:	Endpoपूर्णांक poपूर्णांकer
 *
 * We program QMAP endpoपूर्णांकs so each packet received is preceded by a QMAP
 * header काष्ठाure.  The QMAP header contains a 1-byte mux_id and 2-byte
 * packet size field, and we have the IPA hardware populate both क्रम each
 * received packet.  The header is configured (in the HDR_EXT रेजिस्टर)
 * to use big endian क्रमmat.
 *
 * The packet size is written पूर्णांकo the QMAP header's pkt_len field.  That
 * location is defined here using the HDR_OFST_PKT_SIZE field.
 *
 * The mux_id comes from a 4-byte metadata value supplied with each packet
 * by the modem.  It is *not* a QMAP header, but it करोes contain the mux_id
 * value that we want, in its low-order byte.  A biपंचांगask defined in the
 * endpoपूर्णांक's METADATA_MASK रेजिस्टर defines which byte within the modem
 * metadata contains the mux_id.  And the OFST_METADATA field programmed
 * here indicates where the extracted byte should be placed within the QMAP
 * header.
 */
अटल व्योम ipa_endpoपूर्णांक_init_hdr(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक)
अणु
	u32 offset = IPA_REG_ENDP_INIT_HDR_N_OFFSET(endpoपूर्णांक->endpoपूर्णांक_id);
	काष्ठा ipa *ipa = endpoपूर्णांक->ipa;
	u32 val = 0;

	अगर (endpoपूर्णांक->data->qmap) अणु
		माप_प्रकार header_size = माप(काष्ठा rmnet_map_header);
		क्रमागत ipa_version version = ipa->version;

		/* We might supply a checksum header after the QMAP header */
		अगर (endpoपूर्णांक->toward_ipa && endpoपूर्णांक->data->checksum)
			header_size += माप(काष्ठा rmnet_map_ul_csum_header);
		val |= ipa_header_size_encoded(version, header_size);

		/* Define how to fill fields in a received QMAP header */
		अगर (!endpoपूर्णांक->toward_ipa) अणु
			u32 offset;	/* Field offset within header */

			/* Where IPA will ग_लिखो the metadata value */
			offset = दुरत्व(काष्ठा rmnet_map_header, mux_id);
			val |= ipa_metadata_offset_encoded(version, offset);

			/* Where IPA will ग_लिखो the length */
			offset = दुरत्व(काष्ठा rmnet_map_header, pkt_len);
			/* Upper bits are stored in HDR_EXT with IPA v4.5 */
			अगर (version >= IPA_VERSION_4_5)
				offset &= field_mask(HDR_OFST_PKT_SIZE_FMASK);

			val |= HDR_OFST_PKT_SIZE_VALID_FMASK;
			val |= u32_encode_bits(offset, HDR_OFST_PKT_SIZE_FMASK);
		पूर्ण
		/* For QMAP TX, metadata offset is 0 (modem assumes this) */
		val |= HDR_OFST_METADATA_VALID_FMASK;

		/* HDR_ADDITIONAL_CONST_LEN is 0; (RX only) */
		/* HDR_A5_MUX is 0 */
		/* HDR_LEN_INC_DEAGG_HDR is 0 */
		/* HDR_METADATA_REG_VALID is 0 (TX only, version < v4.5) */
	पूर्ण

	ioग_लिखो32(val, ipa->reg_virt + offset);
पूर्ण

अटल व्योम ipa_endpoपूर्णांक_init_hdr_ext(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक)
अणु
	u32 offset = IPA_REG_ENDP_INIT_HDR_EXT_N_OFFSET(endpoपूर्णांक->endpoपूर्णांक_id);
	u32 pad_align = endpoपूर्णांक->data->rx.pad_align;
	काष्ठा ipa *ipa = endpoपूर्णांक->ipa;
	u32 val = 0;

	val |= HDR_ENDIANNESS_FMASK;		/* big endian */

	/* A QMAP header contains a 6 bit pad field at offset 0.  The RMNet
	 * driver assumes this field is meaningful in packets it receives,
	 * and assumes the header's payload length includes that padding.
	 * The RMNet driver करोes *not* pad packets it sends, however, so
	 * the pad field (although 0) should be ignored.
	 */
	अगर (endpoपूर्णांक->data->qmap && !endpoपूर्णांक->toward_ipa) अणु
		val |= HDR_TOTAL_LEN_OR_PAD_VALID_FMASK;
		/* HDR_TOTAL_LEN_OR_PAD is 0 (pad, not total_len) */
		val |= HDR_PAYLOAD_LEN_INC_PADDING_FMASK;
		/* HDR_TOTAL_LEN_OR_PAD_OFFSET is 0 */
	पूर्ण

	/* HDR_PAYLOAD_LEN_INC_PADDING is 0 */
	अगर (!endpoपूर्णांक->toward_ipa)
		val |= u32_encode_bits(pad_align, HDR_PAD_TO_ALIGNMENT_FMASK);

	/* IPA v4.5 adds some most-signअगरicant bits to a few fields,
	 * two of which are defined in the HDR (not HDR_EXT) रेजिस्टर.
	 */
	अगर (ipa->version >= IPA_VERSION_4_5) अणु
		/* HDR_TOTAL_LEN_OR_PAD_OFFSET is 0, so MSB is 0 */
		अगर (endpoपूर्णांक->data->qmap && !endpoपूर्णांक->toward_ipa) अणु
			u32 offset;

			offset = दुरत्व(काष्ठा rmnet_map_header, pkt_len);
			offset >>= hweight32(HDR_OFST_PKT_SIZE_FMASK);
			val |= u32_encode_bits(offset,
					       HDR_OFST_PKT_SIZE_MSB_FMASK);
			/* HDR_ADDITIONAL_CONST_LEN is 0 so MSB is 0 */
		पूर्ण
	पूर्ण
	ioग_लिखो32(val, ipa->reg_virt + offset);
पूर्ण

अटल व्योम ipa_endpoपूर्णांक_init_hdr_metadata_mask(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक)
अणु
	u32 endpoपूर्णांक_id = endpoपूर्णांक->endpoपूर्णांक_id;
	u32 val = 0;
	u32 offset;

	अगर (endpoपूर्णांक->toward_ipa)
		वापस;		/* Register not valid क्रम TX endpoपूर्णांकs */

	offset = IPA_REG_ENDP_INIT_HDR_METADATA_MASK_N_OFFSET(endpoपूर्णांक_id);

	/* Note that HDR_ENDIANNESS indicates big endian header fields */
	अगर (endpoपूर्णांक->data->qmap)
		val = (__क्रमce u32)cpu_to_be32(IPA_ENDPOINT_QMAP_METADATA_MASK);

	ioग_लिखो32(val, endpoपूर्णांक->ipa->reg_virt + offset);
पूर्ण

अटल व्योम ipa_endpoपूर्णांक_init_mode(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक)
अणु
	u32 offset = IPA_REG_ENDP_INIT_MODE_N_OFFSET(endpoपूर्णांक->endpoपूर्णांक_id);
	u32 val;

	अगर (!endpoपूर्णांक->toward_ipa)
		वापस;		/* Register not valid क्रम RX endpoपूर्णांकs */

	अगर (endpoपूर्णांक->data->dma_mode) अणु
		क्रमागत ipa_endpoपूर्णांक_name name = endpoपूर्णांक->data->dma_endpoपूर्णांक;
		u32 dma_endpoपूर्णांक_id;

		dma_endpoपूर्णांक_id = endpoपूर्णांक->ipa->name_map[name]->endpoपूर्णांक_id;

		val = u32_encode_bits(IPA_DMA, MODE_FMASK);
		val |= u32_encode_bits(dma_endpoपूर्णांक_id, DEST_PIPE_INDEX_FMASK);
	पूर्ण अन्यथा अणु
		val = u32_encode_bits(IPA_BASIC, MODE_FMASK);
	पूर्ण
	/* All other bits unspecअगरied (and 0) */

	ioग_लिखो32(val, endpoपूर्णांक->ipa->reg_virt + offset);
पूर्ण

/* Compute the aggregation size value to use क्रम a given buffer size */
अटल u32 ipa_aggr_size_kb(u32 rx_buffer_size)
अणु
	/* We करोn't use "hard byte limit" aggregation, so we define the
	 * aggregation limit such that our buffer has enough space *after*
	 * that limit to receive a full MTU of data, plus overhead.
	 */
	rx_buffer_size -= IPA_MTU + IPA_RX_BUFFER_OVERHEAD;

	वापस rx_buffer_size / SZ_1K;
पूर्ण

/* Encoded values क्रम AGGR endpoपूर्णांक रेजिस्टर fields */
अटल u32 aggr_byte_limit_encoded(क्रमागत ipa_version version, u32 limit)
अणु
	अगर (version < IPA_VERSION_4_5)
		वापस u32_encode_bits(limit, aggr_byte_limit_fmask(true));

	वापस u32_encode_bits(limit, aggr_byte_limit_fmask(false));
पूर्ण

/* Encode the aggregation समयr limit (microseconds) based on IPA version */
अटल u32 aggr_समय_limit_encoded(क्रमागत ipa_version version, u32 limit)
अणु
	u32 gran_sel;
	u32 fmask;
	u32 val;

	अगर (version < IPA_VERSION_4_5) अणु
		/* We set aggregation granularity in ipa_hardware_config() */
		limit = DIV_ROUND_CLOSEST(limit, IPA_AGGR_GRANULARITY);

		वापस u32_encode_bits(limit, aggr_समय_limit_fmask(true));
	पूर्ण

	/* IPA v4.5 expresses the समय limit using Qसमय.  The AP has
	 * pulse generators 0 and 1 available, which were configured
	 * in ipa_qसमय_config() to have granularity 100 usec and
	 * 1 msec, respectively.  Use pulse generator 0 अगर possible,
	 * otherwise fall back to pulse generator 1.
	 */
	fmask = aggr_समय_limit_fmask(false);
	val = DIV_ROUND_CLOSEST(limit, 100);
	अगर (val > field_max(fmask)) अणु
		/* Have to use pulse generator 1 (millisecond granularity) */
		gran_sel = AGGR_GRAN_SEL_FMASK;
		val = DIV_ROUND_CLOSEST(limit, 1000);
	पूर्ण अन्यथा अणु
		/* We can use pulse generator 0 (100 usec granularity) */
		gran_sel = 0;
	पूर्ण

	वापस gran_sel | u32_encode_bits(val, fmask);
पूर्ण

अटल u32 aggr_sw_eof_active_encoded(क्रमागत ipa_version version, bool enabled)
अणु
	u32 val = enabled ? 1 : 0;

	अगर (version < IPA_VERSION_4_5)
		वापस u32_encode_bits(val, aggr_sw_eof_active_fmask(true));

	वापस u32_encode_bits(val, aggr_sw_eof_active_fmask(false));
पूर्ण

अटल व्योम ipa_endpoपूर्णांक_init_aggr(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक)
अणु
	u32 offset = IPA_REG_ENDP_INIT_AGGR_N_OFFSET(endpoपूर्णांक->endpoपूर्णांक_id);
	क्रमागत ipa_version version = endpoपूर्णांक->ipa->version;
	u32 val = 0;

	अगर (endpoपूर्णांक->data->aggregation) अणु
		अगर (!endpoपूर्णांक->toward_ipa) अणु
			bool बंद_eof;
			u32 limit;

			val |= u32_encode_bits(IPA_ENABLE_AGGR, AGGR_EN_FMASK);
			val |= u32_encode_bits(IPA_GENERIC, AGGR_TYPE_FMASK);

			limit = ipa_aggr_size_kb(IPA_RX_BUFFER_SIZE);
			val |= aggr_byte_limit_encoded(version, limit);

			limit = IPA_AGGR_TIME_LIMIT;
			val |= aggr_समय_limit_encoded(version, limit);

			/* AGGR_PKT_LIMIT is 0 (unlimited) */

			बंद_eof = endpoपूर्णांक->data->rx.aggr_बंद_eof;
			val |= aggr_sw_eof_active_encoded(version, बंद_eof);

			/* AGGR_HARD_BYTE_LIMIT_ENABLE is 0 */
		पूर्ण अन्यथा अणु
			val |= u32_encode_bits(IPA_ENABLE_DEAGGR,
					       AGGR_EN_FMASK);
			val |= u32_encode_bits(IPA_QCMAP, AGGR_TYPE_FMASK);
			/* other fields ignored */
		पूर्ण
		/* AGGR_FORCE_CLOSE is 0 */
		/* AGGR_GRAN_SEL is 0 क्रम IPA v4.5 */
	पूर्ण अन्यथा अणु
		val |= u32_encode_bits(IPA_BYPASS_AGGR, AGGR_EN_FMASK);
		/* other fields ignored */
	पूर्ण

	ioग_लिखो32(val, endpoपूर्णांक->ipa->reg_virt + offset);
पूर्ण

/* Return the Qसमय-based head-of-line blocking समयr value that
 * represents the given number of microseconds.  The result
 * includes both the समयr value and the selected समयr granularity.
 */
अटल u32 hol_block_समयr_qसमय_val(काष्ठा ipa *ipa, u32 microseconds)
अणु
	u32 gran_sel;
	u32 val;

	/* IPA v4.5 expresses समय limits using Qसमय.  The AP has
	 * pulse generators 0 and 1 available, which were configured
	 * in ipa_qसमय_config() to have granularity 100 usec and
	 * 1 msec, respectively.  Use pulse generator 0 अगर possible,
	 * otherwise fall back to pulse generator 1.
	 */
	val = DIV_ROUND_CLOSEST(microseconds, 100);
	अगर (val > field_max(TIME_LIMIT_FMASK)) अणु
		/* Have to use pulse generator 1 (millisecond granularity) */
		gran_sel = GRAN_SEL_FMASK;
		val = DIV_ROUND_CLOSEST(microseconds, 1000);
	पूर्ण अन्यथा अणु
		/* We can use pulse generator 0 (100 usec granularity) */
		gran_sel = 0;
	पूर्ण

	वापस gran_sel | u32_encode_bits(val, TIME_LIMIT_FMASK);
पूर्ण

/* The head-of-line blocking समयr is defined as a tick count.  For
 * IPA version 4.5 the tick count is based on the Qसमयr, which is
 * derived from the 19.2 MHz SoC XO घड़ी.  For older IPA versions
 * each tick represents 128 cycles of the IPA core घड़ी.
 *
 * Return the encoded value that should be written to that रेजिस्टर
 * that represents the समयout period provided.  For IPA v4.2 this
 * encodes a base and scale value, जबतक क्रम earlier versions the
 * value is a simple tick count.
 */
अटल u32 hol_block_समयr_val(काष्ठा ipa *ipa, u32 microseconds)
अणु
	u32 width;
	u32 scale;
	u64 ticks;
	u64 rate;
	u32 high;
	u32 val;

	अगर (!microseconds)
		वापस 0;	/* Nothing to compute अगर समयr period is 0 */

	अगर (ipa->version >= IPA_VERSION_4_5)
		वापस hol_block_समयr_qसमय_val(ipa, microseconds);

	/* Use 64 bit arithmetic to aव्योम overflow... */
	rate = ipa_घड़ी_rate(ipa);
	ticks = DIV_ROUND_CLOSEST(microseconds * rate, 128 * USEC_PER_SEC);
	/* ...but we still need to fit पूर्णांकo a 32-bit रेजिस्टर */
	WARN_ON(ticks > U32_MAX);

	/* IPA v3.5.1 through v4.1 just record the tick count */
	अगर (ipa->version < IPA_VERSION_4_2)
		वापस (u32)ticks;

	/* For IPA v4.2, the tick count is represented by base and
	 * scale fields within the 32-bit समयr रेजिस्टर, where:
	 *     ticks = base << scale;
	 * The best precision is achieved when the base value is as
	 * large as possible.  Find the highest set bit in the tick
	 * count, and extract the number of bits in the base field
	 * such that high bit is included.
	 */
	high = fls(ticks);		/* 1..32 */
	width = HWEIGHT32(BASE_VALUE_FMASK);
	scale = high > width ? high - width : 0;
	अगर (scale) अणु
		/* If we're scaling, round up to get a बंदr result */
		ticks += 1 << (scale - 1);
		/* High bit was set, so rounding might have affected it */
		अगर (fls(ticks) != high)
			scale++;
	पूर्ण

	val = u32_encode_bits(scale, SCALE_FMASK);
	val |= u32_encode_bits(ticks >> scale, BASE_VALUE_FMASK);

	वापस val;
पूर्ण

/* If microseconds is 0, समयout is immediate */
अटल व्योम ipa_endpoपूर्णांक_init_hol_block_समयr(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक,
					      u32 microseconds)
अणु
	u32 endpoपूर्णांक_id = endpoपूर्णांक->endpoपूर्णांक_id;
	काष्ठा ipa *ipa = endpoपूर्णांक->ipa;
	u32 offset;
	u32 val;

	offset = IPA_REG_ENDP_INIT_HOL_BLOCK_TIMER_N_OFFSET(endpoपूर्णांक_id);
	val = hol_block_समयr_val(ipa, microseconds);
	ioग_लिखो32(val, ipa->reg_virt + offset);
पूर्ण

अटल व्योम
ipa_endpoपूर्णांक_init_hol_block_enable(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक, bool enable)
अणु
	u32 endpoपूर्णांक_id = endpoपूर्णांक->endpoपूर्णांक_id;
	u32 offset;
	u32 val;

	val = enable ? HOL_BLOCK_EN_FMASK : 0;
	offset = IPA_REG_ENDP_INIT_HOL_BLOCK_EN_N_OFFSET(endpoपूर्णांक_id);
	ioग_लिखो32(val, endpoपूर्णांक->ipa->reg_virt + offset);
पूर्ण

व्योम ipa_endpoपूर्णांक_modem_hol_block_clear_all(काष्ठा ipa *ipa)
अणु
	u32 i;

	क्रम (i = 0; i < IPA_ENDPOपूर्णांक_उच्च; i++) अणु
		काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक = &ipa->endpoपूर्णांक[i];

		अगर (endpoपूर्णांक->toward_ipa || endpoपूर्णांक->ee_id != GSI_EE_MODEM)
			जारी;

		ipa_endpoपूर्णांक_init_hol_block_समयr(endpoपूर्णांक, 0);
		ipa_endpoपूर्णांक_init_hol_block_enable(endpoपूर्णांक, true);
	पूर्ण
पूर्ण

अटल व्योम ipa_endpoपूर्णांक_init_deaggr(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक)
अणु
	u32 offset = IPA_REG_ENDP_INIT_DEAGGR_N_OFFSET(endpoपूर्णांक->endpoपूर्णांक_id);
	u32 val = 0;

	अगर (!endpoपूर्णांक->toward_ipa)
		वापस;		/* Register not valid क्रम RX endpoपूर्णांकs */

	/* DEAGGR_HDR_LEN is 0 */
	/* PACKET_OFFSET_VALID is 0 */
	/* PACKET_OFFSET_LOCATION is ignored (not valid) */
	/* MAX_PACKET_LEN is 0 (not enक्रमced) */

	ioग_लिखो32(val, endpoपूर्णांक->ipa->reg_virt + offset);
पूर्ण

अटल व्योम ipa_endpoपूर्णांक_init_rsrc_grp(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक)
अणु
	u32 offset = IPA_REG_ENDP_INIT_RSRC_GRP_N_OFFSET(endpoपूर्णांक->endpoपूर्णांक_id);
	काष्ठा ipa *ipa = endpoपूर्णांक->ipa;
	u32 val;

	val = rsrc_grp_encoded(ipa->version, endpoपूर्णांक->data->resource_group);
	ioग_लिखो32(val, ipa->reg_virt + offset);
पूर्ण

अटल व्योम ipa_endpoपूर्णांक_init_seq(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक)
अणु
	u32 offset = IPA_REG_ENDP_INIT_SEQ_N_OFFSET(endpoपूर्णांक->endpoपूर्णांक_id);
	u32 val = 0;

	अगर (!endpoपूर्णांक->toward_ipa)
		वापस;		/* Register not valid क्रम RX endpoपूर्णांकs */

	/* Low-order byte configures primary packet processing */
	val |= u32_encode_bits(endpoपूर्णांक->data->tx.seq_type, SEQ_TYPE_FMASK);

	/* Second byte configures replicated packet processing */
	val |= u32_encode_bits(endpoपूर्णांक->data->tx.seq_rep_type,
			       SEQ_REP_TYPE_FMASK);

	ioग_लिखो32(val, endpoपूर्णांक->ipa->reg_virt + offset);
पूर्ण

/**
 * ipa_endpoपूर्णांक_skb_tx() - Transmit a socket buffer
 * @endpoपूर्णांक:	Endpoपूर्णांक poपूर्णांकer
 * @skb:	Socket buffer to send
 *
 * Returns:	0 अगर successful, or a negative error code
 */
पूर्णांक ipa_endpoपूर्णांक_skb_tx(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक, काष्ठा sk_buff *skb)
अणु
	काष्ठा gsi_trans *trans;
	u32 nr_frags;
	पूर्णांक ret;

	/* Make sure source endpoपूर्णांक's TLV FIFO has enough entries to
	 * hold the linear portion of the skb and all its fragments.
	 * If not, see अगर we can linearize it beक्रमe giving up.
	 */
	nr_frags = skb_shinfo(skb)->nr_frags;
	अगर (1 + nr_frags > endpoपूर्णांक->trans_tre_max) अणु
		अगर (skb_linearize(skb))
			वापस -E2BIG;
		nr_frags = 0;
	पूर्ण

	trans = ipa_endpoपूर्णांक_trans_alloc(endpoपूर्णांक, 1 + nr_frags);
	अगर (!trans)
		वापस -EBUSY;

	ret = gsi_trans_skb_add(trans, skb);
	अगर (ret)
		जाओ err_trans_मुक्त;
	trans->data = skb;	/* transaction owns skb now */

	gsi_trans_commit(trans, !netdev_xmit_more());

	वापस 0;

err_trans_मुक्त:
	gsi_trans_मुक्त(trans);

	वापस -ENOMEM;
पूर्ण

अटल व्योम ipa_endpoपूर्णांक_status(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक)
अणु
	u32 endpoपूर्णांक_id = endpoपूर्णांक->endpoपूर्णांक_id;
	काष्ठा ipa *ipa = endpoपूर्णांक->ipa;
	u32 val = 0;
	u32 offset;

	offset = IPA_REG_ENDP_STATUS_N_OFFSET(endpoपूर्णांक_id);

	अगर (endpoपूर्णांक->data->status_enable) अणु
		val |= STATUS_EN_FMASK;
		अगर (endpoपूर्णांक->toward_ipa) अणु
			क्रमागत ipa_endpoपूर्णांक_name name;
			u32 status_endpoपूर्णांक_id;

			name = endpoपूर्णांक->data->tx.status_endpoपूर्णांक;
			status_endpoपूर्णांक_id = ipa->name_map[name]->endpoपूर्णांक_id;

			val |= u32_encode_bits(status_endpoपूर्णांक_id,
					       STATUS_ENDP_FMASK);
		पूर्ण
		/* STATUS_LOCATION is 0, meaning status element precedes
		 * packet (not present क्रम IPA v4.5)
		 */
		/* STATUS_PKT_SUPPRESS_FMASK is 0 (not present क्रम v3.5.1) */
	पूर्ण

	ioग_लिखो32(val, ipa->reg_virt + offset);
पूर्ण

अटल पूर्णांक ipa_endpoपूर्णांक_replenish_one(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक)
अणु
	काष्ठा gsi_trans *trans;
	bool करोorbell = false;
	काष्ठा page *page;
	u32 offset;
	u32 len;
	पूर्णांक ret;

	page = dev_alloc_pages(get_order(IPA_RX_BUFFER_SIZE));
	अगर (!page)
		वापस -ENOMEM;

	trans = ipa_endpoपूर्णांक_trans_alloc(endpoपूर्णांक, 1);
	अगर (!trans)
		जाओ err_मुक्त_pages;

	/* Offset the buffer to make space क्रम skb headroom */
	offset = NET_SKB_PAD;
	len = IPA_RX_BUFFER_SIZE - offset;

	ret = gsi_trans_page_add(trans, page, len, offset);
	अगर (ret)
		जाओ err_trans_मुक्त;
	trans->data = page;	/* transaction owns page now */

	अगर (++endpoपूर्णांक->replenish_पढ़ोy == IPA_REPLENISH_BATCH) अणु
		करोorbell = true;
		endpoपूर्णांक->replenish_पढ़ोy = 0;
	पूर्ण

	gsi_trans_commit(trans, करोorbell);

	वापस 0;

err_trans_मुक्त:
	gsi_trans_मुक्त(trans);
err_मुक्त_pages:
	__मुक्त_pages(page, get_order(IPA_RX_BUFFER_SIZE));

	वापस -ENOMEM;
पूर्ण

/**
 * ipa_endpoपूर्णांक_replenish() - Replenish endpoपूर्णांक receive buffers
 * @endpoपूर्णांक:	Endpoपूर्णांक to be replenished
 * @add_one:	Whether this is replacing a just-consumed buffer
 *
 * The IPA hardware can hold a fixed number of receive buffers क्रम an RX
 * endpoपूर्णांक, based on the number of entries in the underlying channel ring
 * buffer.  If an endpoपूर्णांक's "backlog" is non-zero, it indicates how many
 * more receive buffers can be supplied to the hardware.  Replenishing क्रम
 * an endpoपूर्णांक can be disabled, in which हाल requests to replenish a
 * buffer are "saved", and transferred to the backlog once it is re-enabled
 * again.
 */
अटल व्योम ipa_endpoपूर्णांक_replenish(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक, bool add_one)
अणु
	काष्ठा gsi *gsi;
	u32 backlog;

	अगर (!endpoपूर्णांक->replenish_enabled) अणु
		अगर (add_one)
			atomic_inc(&endpoपूर्णांक->replenish_saved);
		वापस;
	पूर्ण

	जबतक (atomic_dec_not_zero(&endpoपूर्णांक->replenish_backlog))
		अगर (ipa_endpoपूर्णांक_replenish_one(endpoपूर्णांक))
			जाओ try_again_later;
	अगर (add_one)
		atomic_inc(&endpoपूर्णांक->replenish_backlog);

	वापस;

try_again_later:
	/* The last one didn't succeed, so fix the backlog */
	backlog = atomic_inc_वापस(&endpoपूर्णांक->replenish_backlog);

	अगर (add_one)
		atomic_inc(&endpoपूर्णांक->replenish_backlog);

	/* Whenever a receive buffer transaction completes we'll try to
	 * replenish again.  It's unlikely, but अगर we fail to supply even
	 * one buffer, nothing will trigger another replenish attempt.
	 * Receive buffer transactions use one TRE, so schedule work to
	 * try replenishing again अगर our backlog is *all* available TREs.
	 */
	gsi = &endpoपूर्णांक->ipa->gsi;
	अगर (backlog == gsi_channel_tre_max(gsi, endpoपूर्णांक->channel_id))
		schedule_delayed_work(&endpoपूर्णांक->replenish_work,
				      msecs_to_jअगरfies(1));
पूर्ण

अटल व्योम ipa_endpoपूर्णांक_replenish_enable(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक)
अणु
	काष्ठा gsi *gsi = &endpoपूर्णांक->ipa->gsi;
	u32 max_backlog;
	u32 saved;

	endpoपूर्णांक->replenish_enabled = true;
	जबतक ((saved = atomic_xchg(&endpoपूर्णांक->replenish_saved, 0)))
		atomic_add(saved, &endpoपूर्णांक->replenish_backlog);

	/* Start replenishing अगर hardware currently has no buffers */
	max_backlog = gsi_channel_tre_max(gsi, endpoपूर्णांक->channel_id);
	अगर (atomic_पढ़ो(&endpoपूर्णांक->replenish_backlog) == max_backlog)
		ipa_endpoपूर्णांक_replenish(endpoपूर्णांक, false);
पूर्ण

अटल व्योम ipa_endpoपूर्णांक_replenish_disable(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक)
अणु
	u32 backlog;

	endpoपूर्णांक->replenish_enabled = false;
	जबतक ((backlog = atomic_xchg(&endpoपूर्णांक->replenish_backlog, 0)))
		atomic_add(backlog, &endpoपूर्णांक->replenish_saved);
पूर्ण

अटल व्योम ipa_endpoपूर्णांक_replenish_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक;

	endpoपूर्णांक = container_of(dwork, काष्ठा ipa_endpoपूर्णांक, replenish_work);

	ipa_endpoपूर्णांक_replenish(endpoपूर्णांक, false);
पूर्ण

अटल व्योम ipa_endpoपूर्णांक_skb_copy(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक,
				  व्योम *data, u32 len, u32 extra)
अणु
	काष्ठा sk_buff *skb;

	skb = __dev_alloc_skb(len, GFP_ATOMIC);
	अगर (skb) अणु
		skb_put(skb, len);
		स_नकल(skb->data, data, len);
		skb->truesize += extra;
	पूर्ण

	/* Now receive it, or drop it अगर there's no netdev */
	अगर (endpoपूर्णांक->netdev)
		ipa_modem_skb_rx(endpoपूर्णांक->netdev, skb);
	अन्यथा अगर (skb)
		dev_kमुक्त_skb_any(skb);
पूर्ण

अटल bool ipa_endpoपूर्णांक_skb_build(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक,
				   काष्ठा page *page, u32 len)
अणु
	काष्ठा sk_buff *skb;

	/* Nothing to करो अगर there's no netdev */
	अगर (!endpoपूर्णांक->netdev)
		वापस false;

	/* निश्चित(len <= SKB_WITH_OVERHEAD(IPA_RX_BUFFER_SIZE-NET_SKB_PAD)); */
	skb = build_skb(page_address(page), IPA_RX_BUFFER_SIZE);
	अगर (skb) अणु
		/* Reserve the headroom and account क्रम the data */
		skb_reserve(skb, NET_SKB_PAD);
		skb_put(skb, len);
	पूर्ण

	/* Receive the buffer (or record drop अगर unable to build it) */
	ipa_modem_skb_rx(endpoपूर्णांक->netdev, skb);

	वापस skb != शून्य;
पूर्ण

/* The क्रमmat of a packet status element is the same क्रम several status
 * types (opcodes).  Other types aren't currently supported.
 */
अटल bool ipa_status_क्रमmat_packet(क्रमागत ipa_status_opcode opcode)
अणु
	चयन (opcode) अणु
	हाल IPA_STATUS_OPCODE_PACKET:
	हाल IPA_STATUS_OPCODE_DROPPED_PACKET:
	हाल IPA_STATUS_OPCODE_SUSPENDED_PACKET:
	हाल IPA_STATUS_OPCODE_PACKET_2ND_PASS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool ipa_endpoपूर्णांक_status_skip(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक,
				     स्थिर काष्ठा ipa_status *status)
अणु
	u32 endpoपूर्णांक_id;

	अगर (!ipa_status_क्रमmat_packet(status->opcode))
		वापस true;
	अगर (!status->pkt_len)
		वापस true;
	endpoपूर्णांक_id = u8_get_bits(status->endp_dst_idx,
				  IPA_STATUS_DST_IDX_FMASK);
	अगर (endpoपूर्णांक_id != endpoपूर्णांक->endpoपूर्णांक_id)
		वापस true;

	वापस false;	/* Don't skip this packet, process it */
पूर्ण

अटल bool ipa_endpoपूर्णांक_status_tag(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक,
				    स्थिर काष्ठा ipa_status *status)
अणु
	काष्ठा ipa_endpoपूर्णांक *command_endpoपूर्णांक;
	काष्ठा ipa *ipa = endpoपूर्णांक->ipa;
	u32 endpoपूर्णांक_id;

	अगर (!le16_get_bits(status->mask, IPA_STATUS_MASK_TAG_VALID_FMASK))
		वापस false;	/* No valid tag */

	/* The status contains a valid tag.  We know the packet was sent to
	 * this endpoपूर्णांक (alपढ़ोy verअगरied by ipa_endpoपूर्णांक_status_skip()).
	 * If the packet came from the AP->command TX endpoपूर्णांक we know
	 * this packet was sent as part of the pipeline clear process.
	 */
	endpoपूर्णांक_id = u8_get_bits(status->endp_src_idx,
				  IPA_STATUS_SRC_IDX_FMASK);
	command_endpoपूर्णांक = ipa->name_map[IPA_ENDPOINT_AP_COMMAND_TX];
	अगर (endpoपूर्णांक_id == command_endpoपूर्णांक->endpoपूर्णांक_id) अणु
		complete(&ipa->completion);
	पूर्ण अन्यथा अणु
		dev_err(&ipa->pdev->dev,
			"unexpected tagged packet from endpoint %u\n",
			endpoपूर्णांक_id);
	पूर्ण

	वापस true;
पूर्ण

/* Return whether the status indicates the packet should be dropped */
अटल bool ipa_endpoपूर्णांक_status_drop(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक,
				     स्थिर काष्ठा ipa_status *status)
अणु
	u32 val;

	/* If the status indicates a tagged transfer, we'll drop the packet */
	अगर (ipa_endpoपूर्णांक_status_tag(endpoपूर्णांक, status))
		वापस true;

	/* Deaggregation exceptions we drop; all other types we consume */
	अगर (status->exception)
		वापस status->exception == IPA_STATUS_EXCEPTION_DEAGGR;

	/* Drop the packet अगर it fails to match a routing rule; otherwise no */
	val = le32_get_bits(status->flags1, IPA_STATUS_FLAGS1_RT_RULE_ID_FMASK);

	वापस val == field_max(IPA_STATUS_FLAGS1_RT_RULE_ID_FMASK);
पूर्ण

अटल व्योम ipa_endpoपूर्णांक_status_parse(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक,
				      काष्ठा page *page, u32 total_len)
अणु
	व्योम *data = page_address(page) + NET_SKB_PAD;
	u32 unused = IPA_RX_BUFFER_SIZE - total_len;
	u32 resid = total_len;

	जबतक (resid) अणु
		स्थिर काष्ठा ipa_status *status = data;
		u32 align;
		u32 len;

		अगर (resid < माप(*status)) अणु
			dev_err(&endpoपूर्णांक->ipa->pdev->dev,
				"short message (%u bytes < %zu byte status)\n",
				resid, माप(*status));
			अवरोध;
		पूर्ण

		/* Skip over status packets that lack packet data */
		अगर (ipa_endpoपूर्णांक_status_skip(endpoपूर्णांक, status)) अणु
			data += माप(*status);
			resid -= माप(*status);
			जारी;
		पूर्ण

		/* Compute the amount of buffer space consumed by the packet,
		 * including the status element.  If the hardware is configured
		 * to pad packet data to an aligned boundary, account क्रम that.
		 * And अगर checksum offload is enabled a trailer containing
		 * computed checksum inक्रमmation will be appended.
		 */
		align = endpoपूर्णांक->data->rx.pad_align ? : 1;
		len = le16_to_cpu(status->pkt_len);
		len = माप(*status) + ALIGN(len, align);
		अगर (endpoपूर्णांक->data->checksum)
			len += माप(काष्ठा rmnet_map_dl_csum_trailer);

		अगर (!ipa_endpoपूर्णांक_status_drop(endpoपूर्णांक, status)) अणु
			व्योम *data2;
			u32 extra;
			u32 len2;

			/* Client receives only packet data (no status) */
			data2 = data + माप(*status);
			len2 = le16_to_cpu(status->pkt_len);

			/* Have the true size reflect the extra unused space in
			 * the original receive buffer.  Distribute the "cost"
			 * proportionately across all aggregated packets in the
			 * buffer.
			 */
			extra = DIV_ROUND_CLOSEST(unused * len, total_len);
			ipa_endpoपूर्णांक_skb_copy(endpoपूर्णांक, data2, len2, extra);
		पूर्ण

		/* Consume status and the full packet it describes */
		data += len;
		resid -= len;
	पूर्ण
पूर्ण

/* Complete a TX transaction, command or from ipa_endpoपूर्णांक_skb_tx() */
अटल व्योम ipa_endpoपूर्णांक_tx_complete(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक,
				     काष्ठा gsi_trans *trans)
अणु
पूर्ण

/* Complete transaction initiated in ipa_endpoपूर्णांक_replenish_one() */
अटल व्योम ipa_endpoपूर्णांक_rx_complete(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक,
				     काष्ठा gsi_trans *trans)
अणु
	काष्ठा page *page;

	ipa_endpoपूर्णांक_replenish(endpoपूर्णांक, true);

	अगर (trans->cancelled)
		वापस;

	/* Parse or build a socket buffer using the actual received length */
	page = trans->data;
	अगर (endpoपूर्णांक->data->status_enable)
		ipa_endpoपूर्णांक_status_parse(endpoपूर्णांक, page, trans->len);
	अन्यथा अगर (ipa_endpoपूर्णांक_skb_build(endpoपूर्णांक, page, trans->len))
		trans->data = शून्य;	/* Pages have been consumed */
पूर्ण

व्योम ipa_endpoपूर्णांक_trans_complete(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक,
				 काष्ठा gsi_trans *trans)
अणु
	अगर (endpoपूर्णांक->toward_ipa)
		ipa_endpoपूर्णांक_tx_complete(endpoपूर्णांक, trans);
	अन्यथा
		ipa_endpoपूर्णांक_rx_complete(endpoपूर्णांक, trans);
पूर्ण

व्योम ipa_endpoपूर्णांक_trans_release(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक,
				काष्ठा gsi_trans *trans)
अणु
	अगर (endpoपूर्णांक->toward_ipa) अणु
		काष्ठा ipa *ipa = endpoपूर्णांक->ipa;

		/* Nothing to करो क्रम command transactions */
		अगर (endpoपूर्णांक != ipa->name_map[IPA_ENDPOINT_AP_COMMAND_TX]) अणु
			काष्ठा sk_buff *skb = trans->data;

			अगर (skb)
				dev_kमुक्त_skb_any(skb);
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा page *page = trans->data;

		अगर (page)
			__मुक्त_pages(page, get_order(IPA_RX_BUFFER_SIZE));
	पूर्ण
पूर्ण

व्योम ipa_endpoपूर्णांक_शेष_route_set(काष्ठा ipa *ipa, u32 endpoपूर्णांक_id)
अणु
	u32 val;

	/* ROUTE_DIS is 0 */
	val = u32_encode_bits(endpoपूर्णांक_id, ROUTE_DEF_PIPE_FMASK);
	val |= ROUTE_DEF_HDR_TABLE_FMASK;
	val |= u32_encode_bits(0, ROUTE_DEF_HDR_OFST_FMASK);
	val |= u32_encode_bits(endpoपूर्णांक_id, ROUTE_FRAG_DEF_PIPE_FMASK);
	val |= ROUTE_DEF_RETAIN_HDR_FMASK;

	ioग_लिखो32(val, ipa->reg_virt + IPA_REG_ROUTE_OFFSET);
पूर्ण

व्योम ipa_endpoपूर्णांक_शेष_route_clear(काष्ठा ipa *ipa)
अणु
	ipa_endpoपूर्णांक_शेष_route_set(ipa, 0);
पूर्ण

/**
 * ipa_endpoपूर्णांक_reset_rx_aggr() - Reset RX endpoपूर्णांक with aggregation active
 * @endpoपूर्णांक:	Endpoपूर्णांक to be reset
 *
 * If aggregation is active on an RX endpoपूर्णांक when a reset is perक्रमmed
 * on its underlying GSI channel, a special sequence of actions must be
 * taken to ensure the IPA pipeline is properly cleared.
 *
 * Return:	0 अगर successful, or a negative error code
 */
अटल पूर्णांक ipa_endpoपूर्णांक_reset_rx_aggr(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक)
अणु
	काष्ठा device *dev = &endpoपूर्णांक->ipa->pdev->dev;
	काष्ठा ipa *ipa = endpoपूर्णांक->ipa;
	काष्ठा gsi *gsi = &ipa->gsi;
	bool suspended = false;
	dma_addr_t addr;
	u32 retries;
	u32 len = 1;
	व्योम *virt;
	पूर्णांक ret;

	virt = kzalloc(len, GFP_KERNEL);
	अगर (!virt)
		वापस -ENOMEM;

	addr = dma_map_single(dev, virt, len, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(dev, addr)) अणु
		ret = -ENOMEM;
		जाओ out_kमुक्त;
	पूर्ण

	/* Force बंद aggregation beक्रमe issuing the reset */
	ipa_endpoपूर्णांक_क्रमce_बंद(endpoपूर्णांक);

	/* Reset and reconfigure the channel with the करोorbell engine
	 * disabled.  Then poll until we know aggregation is no दीर्घer
	 * active.  We'll re-enable the करोorbell (अगर appropriate) when
	 * we reset again below.
	 */
	gsi_channel_reset(gsi, endpoपूर्णांक->channel_id, false);

	/* Make sure the channel isn't suspended */
	suspended = ipa_endpoपूर्णांक_program_suspend(endpoपूर्णांक, false);

	/* Start channel and करो a 1 byte पढ़ो */
	ret = gsi_channel_start(gsi, endpoपूर्णांक->channel_id);
	अगर (ret)
		जाओ out_suspend_again;

	ret = gsi_trans_पढ़ो_byte(gsi, endpoपूर्णांक->channel_id, addr);
	अगर (ret)
		जाओ err_endpoपूर्णांक_stop;

	/* Wait क्रम aggregation to be बंदd on the channel */
	retries = IPA_ENDPOINT_RESET_AGGR_RETRY_MAX;
	करो अणु
		अगर (!ipa_endpoपूर्णांक_aggr_active(endpoपूर्णांक))
			अवरोध;
		usleep_range(USEC_PER_MSEC, 2 * USEC_PER_MSEC);
	पूर्ण जबतक (retries--);

	/* Check one last समय */
	अगर (ipa_endpoपूर्णांक_aggr_active(endpoपूर्णांक))
		dev_err(dev, "endpoint %u still active during reset\n",
			endpoपूर्णांक->endpoपूर्णांक_id);

	gsi_trans_पढ़ो_byte_करोne(gsi, endpoपूर्णांक->channel_id);

	ret = gsi_channel_stop(gsi, endpoपूर्णांक->channel_id);
	अगर (ret)
		जाओ out_suspend_again;

	/* Finally, reset and reconfigure the channel again (re-enabling
	 * the करोorbell engine अगर appropriate).  Sleep क्रम 1 millisecond to
	 * complete the channel reset sequence.  Finish by suspending the
	 * channel again (अगर necessary).
	 */
	gsi_channel_reset(gsi, endpoपूर्णांक->channel_id, true);

	usleep_range(USEC_PER_MSEC, 2 * USEC_PER_MSEC);

	जाओ out_suspend_again;

err_endpoपूर्णांक_stop:
	(व्योम)gsi_channel_stop(gsi, endpoपूर्णांक->channel_id);
out_suspend_again:
	अगर (suspended)
		(व्योम)ipa_endpoपूर्णांक_program_suspend(endpoपूर्णांक, true);
	dma_unmap_single(dev, addr, len, DMA_FROM_DEVICE);
out_kमुक्त:
	kमुक्त(virt);

	वापस ret;
पूर्ण

अटल व्योम ipa_endpoपूर्णांक_reset(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक)
अणु
	u32 channel_id = endpoपूर्णांक->channel_id;
	काष्ठा ipa *ipa = endpoपूर्णांक->ipa;
	bool special;
	पूर्णांक ret = 0;

	/* On IPA v3.5.1, अगर an RX endpoपूर्णांक is reset जबतक aggregation
	 * is active, we need to handle things specially to recover.
	 * All other हालs just need to reset the underlying GSI channel.
	 */
	special = ipa->version < IPA_VERSION_4_0 && !endpoपूर्णांक->toward_ipa &&
			endpoपूर्णांक->data->aggregation;
	अगर (special && ipa_endpoपूर्णांक_aggr_active(endpoपूर्णांक))
		ret = ipa_endpoपूर्णांक_reset_rx_aggr(endpoपूर्णांक);
	अन्यथा
		gsi_channel_reset(&ipa->gsi, channel_id, true);

	अगर (ret)
		dev_err(&ipa->pdev->dev,
			"error %d resetting channel %u for endpoint %u\n",
			ret, endpoपूर्णांक->channel_id, endpoपूर्णांक->endpoपूर्णांक_id);
पूर्ण

अटल व्योम ipa_endpoपूर्णांक_program(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक)
अणु
	अगर (endpoपूर्णांक->toward_ipa)
		ipa_endpoपूर्णांक_program_delay(endpoपूर्णांक, false);
	अन्यथा
		(व्योम)ipa_endpoपूर्णांक_program_suspend(endpoपूर्णांक, false);
	ipa_endpoपूर्णांक_init_cfg(endpoपूर्णांक);
	ipa_endpoपूर्णांक_init_nat(endpoपूर्णांक);
	ipa_endpoपूर्णांक_init_hdr(endpoपूर्णांक);
	ipa_endpoपूर्णांक_init_hdr_ext(endpoपूर्णांक);
	ipa_endpoपूर्णांक_init_hdr_metadata_mask(endpoपूर्णांक);
	ipa_endpoपूर्णांक_init_mode(endpoपूर्णांक);
	ipa_endpoपूर्णांक_init_aggr(endpoपूर्णांक);
	ipa_endpoपूर्णांक_init_deaggr(endpoपूर्णांक);
	ipa_endpoपूर्णांक_init_rsrc_grp(endpoपूर्णांक);
	ipa_endpoपूर्णांक_init_seq(endpoपूर्णांक);
	ipa_endpoपूर्णांक_status(endpoपूर्णांक);
पूर्ण

पूर्णांक ipa_endpoपूर्णांक_enable_one(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक)
अणु
	काष्ठा ipa *ipa = endpoपूर्णांक->ipa;
	काष्ठा gsi *gsi = &ipa->gsi;
	पूर्णांक ret;

	ret = gsi_channel_start(gsi, endpoपूर्णांक->channel_id);
	अगर (ret) अणु
		dev_err(&ipa->pdev->dev,
			"error %d starting %cX channel %u for endpoint %u\n",
			ret, endpoपूर्णांक->toward_ipa ? 'T' : 'R',
			endpoपूर्णांक->channel_id, endpoपूर्णांक->endpoपूर्णांक_id);
		वापस ret;
	पूर्ण

	अगर (!endpoपूर्णांक->toward_ipa) अणु
		ipa_पूर्णांकerrupt_suspend_enable(ipa->पूर्णांकerrupt,
					     endpoपूर्णांक->endpoपूर्णांक_id);
		ipa_endpoपूर्णांक_replenish_enable(endpoपूर्णांक);
	पूर्ण

	ipa->enabled |= BIT(endpoपूर्णांक->endpoपूर्णांक_id);

	वापस 0;
पूर्ण

व्योम ipa_endpoपूर्णांक_disable_one(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक)
अणु
	u32 mask = BIT(endpoपूर्णांक->endpoपूर्णांक_id);
	काष्ठा ipa *ipa = endpoपूर्णांक->ipa;
	काष्ठा gsi *gsi = &ipa->gsi;
	पूर्णांक ret;

	अगर (!(ipa->enabled & mask))
		वापस;

	ipa->enabled ^= mask;

	अगर (!endpoपूर्णांक->toward_ipa) अणु
		ipa_endpoपूर्णांक_replenish_disable(endpoपूर्णांक);
		ipa_पूर्णांकerrupt_suspend_disable(ipa->पूर्णांकerrupt,
					      endpoपूर्णांक->endpoपूर्णांक_id);
	पूर्ण

	/* Note that अगर stop fails, the channel's state is not well-defined */
	ret = gsi_channel_stop(gsi, endpoपूर्णांक->channel_id);
	अगर (ret)
		dev_err(&ipa->pdev->dev,
			"error %d attempting to stop endpoint %u\n", ret,
			endpoपूर्णांक->endpoपूर्णांक_id);
पूर्ण

व्योम ipa_endpoपूर्णांक_suspend_one(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक)
अणु
	काष्ठा device *dev = &endpoपूर्णांक->ipa->pdev->dev;
	काष्ठा gsi *gsi = &endpoपूर्णांक->ipa->gsi;
	bool stop_channel;
	पूर्णांक ret;

	अगर (!(endpoपूर्णांक->ipa->enabled & BIT(endpoपूर्णांक->endpoपूर्णांक_id)))
		वापस;

	अगर (!endpoपूर्णांक->toward_ipa) अणु
		ipa_endpoपूर्णांक_replenish_disable(endpoपूर्णांक);
		(व्योम)ipa_endpoपूर्णांक_program_suspend(endpoपूर्णांक, true);
	पूर्ण

	/* Starting with IPA v4.0, endpoपूर्णांकs are suspended by stopping the
	 * underlying GSI channel rather than using endpoपूर्णांक suspend mode.
	 */
	stop_channel = endpoपूर्णांक->ipa->version >= IPA_VERSION_4_0;
	ret = gsi_channel_suspend(gsi, endpoपूर्णांक->channel_id, stop_channel);
	अगर (ret)
		dev_err(dev, "error %d suspending channel %u\n", ret,
			endpoपूर्णांक->channel_id);
पूर्ण

व्योम ipa_endpoपूर्णांक_resume_one(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक)
अणु
	काष्ठा device *dev = &endpoपूर्णांक->ipa->pdev->dev;
	काष्ठा gsi *gsi = &endpoपूर्णांक->ipa->gsi;
	bool start_channel;
	पूर्णांक ret;

	अगर (!(endpoपूर्णांक->ipa->enabled & BIT(endpoपूर्णांक->endpoपूर्णांक_id)))
		वापस;

	अगर (!endpoपूर्णांक->toward_ipa)
		(व्योम)ipa_endpoपूर्णांक_program_suspend(endpoपूर्णांक, false);

	/* Starting with IPA v4.0, the underlying GSI channel must be
	 * restarted क्रम resume.
	 */
	start_channel = endpoपूर्णांक->ipa->version >= IPA_VERSION_4_0;
	ret = gsi_channel_resume(gsi, endpoपूर्णांक->channel_id, start_channel);
	अगर (ret)
		dev_err(dev, "error %d resuming channel %u\n", ret,
			endpoपूर्णांक->channel_id);
	अन्यथा अगर (!endpoपूर्णांक->toward_ipa)
		ipa_endpoपूर्णांक_replenish_enable(endpoपूर्णांक);
पूर्ण

व्योम ipa_endpoपूर्णांक_suspend(काष्ठा ipa *ipa)
अणु
	अगर (!ipa->setup_complete)
		वापस;

	अगर (ipa->modem_netdev)
		ipa_modem_suspend(ipa->modem_netdev);

	ipa_cmd_pipeline_clear(ipa);

	ipa_endpoपूर्णांक_suspend_one(ipa->name_map[IPA_ENDPOINT_AP_LAN_RX]);
	ipa_endpoपूर्णांक_suspend_one(ipa->name_map[IPA_ENDPOINT_AP_COMMAND_TX]);
पूर्ण

व्योम ipa_endpoपूर्णांक_resume(काष्ठा ipa *ipa)
अणु
	अगर (!ipa->setup_complete)
		वापस;

	ipa_endpoपूर्णांक_resume_one(ipa->name_map[IPA_ENDPOINT_AP_COMMAND_TX]);
	ipa_endpoपूर्णांक_resume_one(ipa->name_map[IPA_ENDPOINT_AP_LAN_RX]);

	अगर (ipa->modem_netdev)
		ipa_modem_resume(ipa->modem_netdev);
पूर्ण

अटल व्योम ipa_endpoपूर्णांक_setup_one(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक)
अणु
	काष्ठा gsi *gsi = &endpoपूर्णांक->ipa->gsi;
	u32 channel_id = endpoपूर्णांक->channel_id;

	/* Only AP endpoपूर्णांकs get set up */
	अगर (endpoपूर्णांक->ee_id != GSI_EE_AP)
		वापस;

	endpoपूर्णांक->trans_tre_max = gsi_channel_trans_tre_max(gsi, channel_id);
	अगर (!endpoपूर्णांक->toward_ipa) अणु
		/* RX transactions require a single TRE, so the maximum
		 * backlog is the same as the maximum outstanding TREs.
		 */
		endpoपूर्णांक->replenish_enabled = false;
		atomic_set(&endpoपूर्णांक->replenish_saved,
			   gsi_channel_tre_max(gsi, endpoपूर्णांक->channel_id));
		atomic_set(&endpoपूर्णांक->replenish_backlog, 0);
		INIT_DELAYED_WORK(&endpoपूर्णांक->replenish_work,
				  ipa_endpoपूर्णांक_replenish_work);
	पूर्ण

	ipa_endpoपूर्णांक_program(endpoपूर्णांक);

	endpoपूर्णांक->ipa->set_up |= BIT(endpoपूर्णांक->endpoपूर्णांक_id);
पूर्ण

अटल व्योम ipa_endpoपूर्णांक_tearकरोwn_one(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक)
अणु
	endpoपूर्णांक->ipa->set_up &= ~BIT(endpoपूर्णांक->endpoपूर्णांक_id);

	अगर (!endpoपूर्णांक->toward_ipa)
		cancel_delayed_work_sync(&endpoपूर्णांक->replenish_work);

	ipa_endpoपूर्णांक_reset(endpoपूर्णांक);
पूर्ण

व्योम ipa_endpoपूर्णांक_setup(काष्ठा ipa *ipa)
अणु
	u32 initialized = ipa->initialized;

	ipa->set_up = 0;
	जबतक (initialized) अणु
		u32 endpoपूर्णांक_id = __ffs(initialized);

		initialized ^= BIT(endpoपूर्णांक_id);

		ipa_endpoपूर्णांक_setup_one(&ipa->endpoपूर्णांक[endpoपूर्णांक_id]);
	पूर्ण
पूर्ण

व्योम ipa_endpoपूर्णांक_tearकरोwn(काष्ठा ipa *ipa)
अणु
	u32 set_up = ipa->set_up;

	जबतक (set_up) अणु
		u32 endpoपूर्णांक_id = __fls(set_up);

		set_up ^= BIT(endpoपूर्णांक_id);

		ipa_endpoपूर्णांक_tearकरोwn_one(&ipa->endpoपूर्णांक[endpoपूर्णांक_id]);
	पूर्ण
	ipa->set_up = 0;
पूर्ण

पूर्णांक ipa_endpoपूर्णांक_config(काष्ठा ipa *ipa)
अणु
	काष्ठा device *dev = &ipa->pdev->dev;
	u32 initialized;
	u32 rx_base;
	u32 rx_mask;
	u32 tx_mask;
	पूर्णांक ret = 0;
	u32 max;
	u32 val;

	/* Find out about the endpoपूर्णांकs supplied by the hardware, and ensure
	 * the highest one करोesn't exceed the number we support.
	 */
	val = ioपढ़ो32(ipa->reg_virt + IPA_REG_FLAVOR_0_OFFSET);

	/* Our RX is an IPA producer */
	rx_base = u32_get_bits(val, IPA_PROD_LOWEST_FMASK);
	max = rx_base + u32_get_bits(val, IPA_MAX_PROD_PIPES_FMASK);
	अगर (max > IPA_ENDPOपूर्णांक_उच्च) अणु
		dev_err(dev, "too many endpoints (%u > %u)\n",
			max, IPA_ENDPOपूर्णांक_उच्च);
		वापस -EINVAL;
	पूर्ण
	rx_mask = GENMASK(max - 1, rx_base);

	/* Our TX is an IPA consumer */
	max = u32_get_bits(val, IPA_MAX_CONS_PIPES_FMASK);
	tx_mask = GENMASK(max - 1, 0);

	ipa->available = rx_mask | tx_mask;

	/* Check क्रम initialized endpoपूर्णांकs not supported by the hardware */
	अगर (ipa->initialized & ~ipa->available) अणु
		dev_err(dev, "unavailable endpoint id(s) 0x%08x\n",
			ipa->initialized & ~ipa->available);
		ret = -EINVAL;		/* Report other errors too */
	पूर्ण

	initialized = ipa->initialized;
	जबतक (initialized) अणु
		u32 endpoपूर्णांक_id = __ffs(initialized);
		काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक;

		initialized ^= BIT(endpoपूर्णांक_id);

		/* Make sure it's poपूर्णांकing in the right direction */
		endpoपूर्णांक = &ipa->endpoपूर्णांक[endpoपूर्णांक_id];
		अगर ((endpoपूर्णांक_id < rx_base) != endpoपूर्णांक->toward_ipa) अणु
			dev_err(dev, "endpoint id %u wrong direction\n",
				endpoपूर्णांक_id);
			ret = -EINVAL;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

व्योम ipa_endpoपूर्णांक_deconfig(काष्ठा ipa *ipa)
अणु
	ipa->available = 0;	/* Nothing more to करो */
पूर्ण

अटल व्योम ipa_endpoपूर्णांक_init_one(काष्ठा ipa *ipa, क्रमागत ipa_endpoपूर्णांक_name name,
				  स्थिर काष्ठा ipa_gsi_endpoपूर्णांक_data *data)
अणु
	काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक;

	endpoपूर्णांक = &ipa->endpoपूर्णांक[data->endpoपूर्णांक_id];

	अगर (data->ee_id == GSI_EE_AP)
		ipa->channel_map[data->channel_id] = endpoपूर्णांक;
	ipa->name_map[name] = endpoपूर्णांक;

	endpoपूर्णांक->ipa = ipa;
	endpoपूर्णांक->ee_id = data->ee_id;
	endpoपूर्णांक->channel_id = data->channel_id;
	endpoपूर्णांक->endpoपूर्णांक_id = data->endpoपूर्णांक_id;
	endpoपूर्णांक->toward_ipa = data->toward_ipa;
	endpoपूर्णांक->data = &data->endpoपूर्णांक.config;

	ipa->initialized |= BIT(endpoपूर्णांक->endpoपूर्णांक_id);
पूर्ण

अटल व्योम ipa_endpoपूर्णांक_निकास_one(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक)
अणु
	endpoपूर्णांक->ipa->initialized &= ~BIT(endpoपूर्णांक->endpoपूर्णांक_id);

	स_रखो(endpoपूर्णांक, 0, माप(*endpoपूर्णांक));
पूर्ण

व्योम ipa_endpoपूर्णांक_निकास(काष्ठा ipa *ipa)
अणु
	u32 initialized = ipa->initialized;

	जबतक (initialized) अणु
		u32 endpoपूर्णांक_id = __fls(initialized);

		initialized ^= BIT(endpoपूर्णांक_id);

		ipa_endpoपूर्णांक_निकास_one(&ipa->endpoपूर्णांक[endpoपूर्णांक_id]);
	पूर्ण
	स_रखो(ipa->name_map, 0, माप(ipa->name_map));
	स_रखो(ipa->channel_map, 0, माप(ipa->channel_map));
पूर्ण

/* Returns a biपंचांगask of endpoपूर्णांकs that support filtering, or 0 on error */
u32 ipa_endpoपूर्णांक_init(काष्ठा ipa *ipa, u32 count,
		      स्थिर काष्ठा ipa_gsi_endpoपूर्णांक_data *data)
अणु
	क्रमागत ipa_endpoपूर्णांक_name name;
	u32 filter_map;

	अगर (!ipa_endpoपूर्णांक_data_valid(ipa, count, data))
		वापस 0;	/* Error */

	ipa->initialized = 0;

	filter_map = 0;
	क्रम (name = 0; name < count; name++, data++) अणु
		अगर (ipa_gsi_endpoपूर्णांक_data_empty(data))
			जारी;	/* Skip over empty slots */

		ipa_endpoपूर्णांक_init_one(ipa, name, data);

		अगर (data->endpoपूर्णांक.filter_support)
			filter_map |= BIT(data->endpoपूर्णांक_id);
	पूर्ण

	अगर (!ipa_filter_map_valid(ipa, filter_map))
		जाओ err_endpoपूर्णांक_निकास;

	वापस filter_map;	/* Non-zero biपंचांगask */

err_endpoपूर्णांक_निकास:
	ipa_endpoपूर्णांक_निकास(ipa);

	वापस 0;	/* Error */
पूर्ण
