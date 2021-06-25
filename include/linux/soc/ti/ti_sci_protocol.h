<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Texas Instruments System Control Interface Protocol
 *
 * Copyright (C) 2015-2016 Texas Instruments Incorporated - https://www.ti.com/
 *	Nishanth Menon
 */

#अगर_अघोषित __TISCI_PROTOCOL_H
#घोषणा __TISCI_PROTOCOL_H

/**
 * काष्ठा ti_sci_version_info - version inक्रमmation काष्ठाure
 * @abi_major:	Major ABI version. Change here implies risk of backward
 *		compatibility अवरोध.
 * @abi_minor:	Minor ABI version. Change here implies new feature addition,
 *		or compatible change in ABI.
 * @firmware_revision:	Firmware revision (not usually used).
 * @firmware_description: Firmware description (not usually used).
 */
काष्ठा ti_sci_version_info अणु
	u8 abi_major;
	u8 abi_minor;
	u16 firmware_revision;
	अक्षर firmware_description[32];
पूर्ण;

काष्ठा ti_sci_handle;

/**
 * काष्ठा ti_sci_core_ops - SoC Core Operations
 * @reboot_device: Reboot the SoC
 *		Returns 0 क्रम successful request(ideally should never वापस),
 *		अन्यथा वापसs corresponding error value.
 */
काष्ठा ti_sci_core_ops अणु
	पूर्णांक (*reboot_device)(स्थिर काष्ठा ti_sci_handle *handle);
पूर्ण;

/**
 * काष्ठा ti_sci_dev_ops - Device control operations
 * @get_device: Command to request क्रम device managed by TISCI
 *		Returns 0 क्रम successful exclusive request, अन्यथा वापसs
 *		corresponding error message.
 * @idle_device: Command to idle a device managed by TISCI
 *		Returns 0 क्रम successful exclusive request, अन्यथा वापसs
 *		corresponding error message.
 * @put_device:	Command to release a device managed by TISCI
 *		Returns 0 क्रम successful release, अन्यथा वापसs corresponding
 *		error message.
 * @is_valid:	Check अगर the device ID is a valid ID.
 *		Returns 0 अगर the ID is valid, अन्यथा वापसs corresponding error.
 * @get_context_loss_count: Command to retrieve context loss counter - this
 *		increments every समय the device looses context. Overflow
 *		is possible.
 *		- count: poपूर्णांकer to u32 which will retrieve counter
 *		Returns 0 क्रम successful inक्रमmation request and count has
 *		proper data, अन्यथा वापसs corresponding error message.
 * @is_idle:	Reports back about device idle state
 *		- req_state: Returns requested idle state
 *		Returns 0 क्रम successful inक्रमmation request and req_state and
 *		current_state has proper data, अन्यथा वापसs corresponding error
 *		message.
 * @is_stop:	Reports back about device stop state
 *		- req_state: Returns requested stop state
 *		- current_state: Returns current stop state
 *		Returns 0 क्रम successful inक्रमmation request and req_state and
 *		current_state has proper data, अन्यथा वापसs corresponding error
 *		message.
 * @is_on:	Reports back about device ON(or active) state
 *		- req_state: Returns requested ON state
 *		- current_state: Returns current ON state
 *		Returns 0 क्रम successful inक्रमmation request and req_state and
 *		current_state has proper data, अन्यथा वापसs corresponding error
 *		message.
 * @is_transitioning: Reports back अगर the device is in the middle of transition
 *		of state.
 *		-current_state: Returns 'true' अगर currently transitioning.
 * @set_device_resets: Command to configure resets क्रम device managed by TISCI.
 *		-reset_state: Device specअगरic reset bit field
 *		Returns 0 क्रम successful request, अन्यथा वापसs
 *		corresponding error message.
 * @get_device_resets: Command to पढ़ो state of resets क्रम device managed
 *		by TISCI.
 *		-reset_state: poपूर्णांकer to u32 which will retrieve resets
 *		Returns 0 क्रम successful request, अन्यथा वापसs
 *		corresponding error message.
 *
 * NOTE: क्रम all these functions, the following parameters are generic in
 * nature:
 * -handle:	Poपूर्णांकer to TISCI handle as retrieved by *ti_sci_get_handle
 * -id:		Device Identअगरier
 *
 * Request क्रम the device - NOTE: the client MUST मुख्यtain पूर्णांकegrity of
 * usage count by balancing get_device with put_device. No refcounting is
 * managed by driver क्रम that purpose.
 */
काष्ठा ti_sci_dev_ops अणु
	पूर्णांक (*get_device)(स्थिर काष्ठा ti_sci_handle *handle, u32 id);
	पूर्णांक (*get_device_exclusive)(स्थिर काष्ठा ti_sci_handle *handle, u32 id);
	पूर्णांक (*idle_device)(स्थिर काष्ठा ti_sci_handle *handle, u32 id);
	पूर्णांक (*idle_device_exclusive)(स्थिर काष्ठा ti_sci_handle *handle,
				     u32 id);
	पूर्णांक (*put_device)(स्थिर काष्ठा ti_sci_handle *handle, u32 id);
	पूर्णांक (*is_valid)(स्थिर काष्ठा ti_sci_handle *handle, u32 id);
	पूर्णांक (*get_context_loss_count)(स्थिर काष्ठा ti_sci_handle *handle,
				      u32 id, u32 *count);
	पूर्णांक (*is_idle)(स्थिर काष्ठा ti_sci_handle *handle, u32 id,
		       bool *requested_state);
	पूर्णांक (*is_stop)(स्थिर काष्ठा ti_sci_handle *handle, u32 id,
		       bool *req_state, bool *current_state);
	पूर्णांक (*is_on)(स्थिर काष्ठा ti_sci_handle *handle, u32 id,
		     bool *req_state, bool *current_state);
	पूर्णांक (*is_transitioning)(स्थिर काष्ठा ti_sci_handle *handle, u32 id,
				bool *current_state);
	पूर्णांक (*set_device_resets)(स्थिर काष्ठा ti_sci_handle *handle, u32 id,
				 u32 reset_state);
	पूर्णांक (*get_device_resets)(स्थिर काष्ठा ti_sci_handle *handle, u32 id,
				 u32 *reset_state);
पूर्ण;

/**
 * काष्ठा ti_sci_clk_ops - Clock control operations
 * @get_घड़ी:	Request क्रम activation of घड़ी and manage by processor
 *		- needs_ssc: 'true' अगर Spपढ़ो Spectrum घड़ी is desired.
 *		- can_change_freq: 'true' अगर frequency change is desired.
 *		- enable_input_term: 'true' अगर input termination is desired.
 * @idle_घड़ी:	Request क्रम Idling a घड़ी managed by processor
 * @put_घड़ी:	Release the घड़ी to be स्वतः managed by TISCI
 * @is_स्वतः:	Is the घड़ी being स्वतः managed
 *		- req_state: state indicating अगर the घड़ी is स्वतः managed
 * @is_on:	Is the घड़ी ON
 *		- req_state: अगर the घड़ी is requested to be क्रमced ON
 *		- current_state: अगर the घड़ी is currently ON
 * @is_off:	Is the घड़ी OFF
 *		- req_state: अगर the घड़ी is requested to be क्रमced OFF
 *		- current_state: अगर the घड़ी is currently Gated
 * @set_parent:	Set the घड़ी source of a specअगरic device घड़ी
 *		- parent_id: Parent घड़ी identअगरier to set.
 * @get_parent:	Get the current घड़ी source of a specअगरic device घड़ी
 *		- parent_id: Parent घड़ी identअगरier which is the parent.
 * @get_num_parents: Get the number of parents of the current घड़ी source
 *		- num_parents: वापसs the number of parent घड़ीs.
 * @get_best_match_freq: Find a best matching frequency क्रम a frequency
 *		range.
 *		- match_freq: Best matching frequency in Hz.
 * @set_freq:	Set the Clock frequency
 * @get_freq:	Get the Clock frequency
 *		- current_freq: Frequency in Hz that the घड़ी is at.
 *
 * NOTE: क्रम all these functions, the following parameters are generic in
 * nature:
 * -handle:	Poपूर्णांकer to TISCI handle as retrieved by *ti_sci_get_handle
 * -did:	Device identअगरier this request is क्रम
 * -cid:	Clock identअगरier क्रम the device क्रम this request.
 *		Each device has it's own set of घड़ी inमाला_दो. This indexes
 *		which घड़ी input to modअगरy.
 * -min_freq:	The minimum allowable frequency in Hz. This is the minimum
 *		allowable programmed frequency and करोes not account क्रम घड़ी
 *		tolerances and jitter.
 * -target_freq: The target घड़ी frequency in Hz. A frequency will be
 *		processed as बंद to this target frequency as possible.
 * -max_freq:	The maximum allowable frequency in Hz. This is the maximum
 *		allowable programmed frequency and करोes not account क्रम घड़ी
 *		tolerances and jitter.
 *
 * Request क्रम the घड़ी - NOTE: the client MUST मुख्यtain पूर्णांकegrity of
 * usage count by balancing get_घड़ी with put_घड़ी. No refcounting is
 * managed by driver क्रम that purpose.
 */
काष्ठा ti_sci_clk_ops अणु
	पूर्णांक (*get_घड़ी)(स्थिर काष्ठा ti_sci_handle *handle, u32 did, u32 cid,
			 bool needs_ssc, bool can_change_freq,
			 bool enable_input_term);
	पूर्णांक (*idle_घड़ी)(स्थिर काष्ठा ti_sci_handle *handle, u32 did, u32 cid);
	पूर्णांक (*put_घड़ी)(स्थिर काष्ठा ti_sci_handle *handle, u32 did, u32 cid);
	पूर्णांक (*is_स्वतः)(स्थिर काष्ठा ti_sci_handle *handle, u32 did, u32 cid,
		       bool *req_state);
	पूर्णांक (*is_on)(स्थिर काष्ठा ti_sci_handle *handle, u32 did, u32 cid,
		     bool *req_state, bool *current_state);
	पूर्णांक (*is_off)(स्थिर काष्ठा ti_sci_handle *handle, u32 did, u32 cid,
		      bool *req_state, bool *current_state);
	पूर्णांक (*set_parent)(स्थिर काष्ठा ti_sci_handle *handle, u32 did, u32 cid,
			  u32 parent_id);
	पूर्णांक (*get_parent)(स्थिर काष्ठा ti_sci_handle *handle, u32 did, u32 cid,
			  u32 *parent_id);
	पूर्णांक (*get_num_parents)(स्थिर काष्ठा ti_sci_handle *handle, u32 did,
			       u32 cid, u32 *num_parents);
	पूर्णांक (*get_best_match_freq)(स्थिर काष्ठा ti_sci_handle *handle, u32 did,
				   u32 cid, u64 min_freq, u64 target_freq,
				   u64 max_freq, u64 *match_freq);
	पूर्णांक (*set_freq)(स्थिर काष्ठा ti_sci_handle *handle, u32 did, u32 cid,
			u64 min_freq, u64 target_freq, u64 max_freq);
	पूर्णांक (*get_freq)(स्थिर काष्ठा ti_sci_handle *handle, u32 did, u32 cid,
			u64 *current_freq);
पूर्ण;

/**
 * काष्ठा ti_sci_resource_desc - Description of TI SCI resource instance range.
 * @start:	Start index of the first resource range.
 * @num:	Number of resources in the first range.
 * @start_sec:	Start index of the second resource range.
 * @num_sec:	Number of resources in the second range.
 * @res_map:	Biपंचांगap to manage the allocation of these resources.
 */
काष्ठा ti_sci_resource_desc अणु
	u16 start;
	u16 num;
	u16 start_sec;
	u16 num_sec;
	अचिन्हित दीर्घ *res_map;
पूर्ण;

/**
 * काष्ठा ti_sci_rm_core_ops - Resource management core operations
 * @get_range:		Get a range of resources beदीर्घing to ti sci host.
 * @get_rage_from_shost:	Get a range of resources beदीर्घing to
 *				specअगरied host id.
 *			- s_host: Host processing entity to which the
 *				  resources are allocated
 *
 * NOTE: क्रम these functions, all the parameters are consolidated and defined
 * as below:
 * - handle:	Poपूर्णांकer to TISCI handle as retrieved by *ti_sci_get_handle
 * - dev_id:	TISCI device ID.
 * - subtype:	Resource assignment subtype that is being requested
 *		from the given device.
 * - desc:	Poपूर्णांकer to ti_sci_resource_desc to be updated with the resource
 *		range start index and number of resources
 */
काष्ठा ti_sci_rm_core_ops अणु
	पूर्णांक (*get_range)(स्थिर काष्ठा ti_sci_handle *handle, u32 dev_id,
			 u8 subtype, काष्ठा ti_sci_resource_desc *desc);
	पूर्णांक (*get_range_from_shost)(स्थिर काष्ठा ti_sci_handle *handle,
				    u32 dev_id, u8 subtype, u8 s_host,
				    काष्ठा ti_sci_resource_desc *desc);
पूर्ण;

#घोषणा TI_SCI_RESASG_SUBTYPE_IR_OUTPUT		0
#घोषणा TI_SCI_RESASG_SUBTYPE_IA_VINT		0xa
#घोषणा TI_SCI_RESASG_SUBTYPE_GLOBAL_EVENT_SEVT	0xd
/**
 * काष्ठा ti_sci_rm_irq_ops: IRQ management operations
 * @set_irq:		Set an IRQ route between the requested source
 *			and destination
 * @set_event_map:	Set an Event based peripheral irq to Interrupt
 *			Aggregator.
 * @मुक्त_irq:		Free an IRQ route between the requested source
 *			and destination.
 * @मुक्त_event_map:	Free an event based peripheral irq to Interrupt
 *			Aggregator.
 */
काष्ठा ti_sci_rm_irq_ops अणु
	पूर्णांक (*set_irq)(स्थिर काष्ठा ti_sci_handle *handle, u16 src_id,
		       u16 src_index, u16 dst_id, u16 dst_host_irq);
	पूर्णांक (*set_event_map)(स्थिर काष्ठा ti_sci_handle *handle, u16 src_id,
			     u16 src_index, u16 ia_id, u16 vपूर्णांक,
			     u16 global_event, u8 vपूर्णांक_status_bit);
	पूर्णांक (*मुक्त_irq)(स्थिर काष्ठा ti_sci_handle *handle, u16 src_id,
			u16 src_index, u16 dst_id, u16 dst_host_irq);
	पूर्णांक (*मुक्त_event_map)(स्थिर काष्ठा ti_sci_handle *handle, u16 src_id,
			      u16 src_index, u16 ia_id, u16 vपूर्णांक,
			      u16 global_event, u8 vपूर्णांक_status_bit);
पूर्ण;

/* RA config.addr_lo parameter is valid क्रम RM ring configure TI_SCI message */
#घोषणा TI_SCI_MSG_VALUE_RM_RING_ADDR_LO_VALID	BIT(0)
/* RA config.addr_hi parameter is valid क्रम RM ring configure TI_SCI message */
#घोषणा TI_SCI_MSG_VALUE_RM_RING_ADDR_HI_VALID	BIT(1)
 /* RA config.count parameter is valid क्रम RM ring configure TI_SCI message */
#घोषणा TI_SCI_MSG_VALUE_RM_RING_COUNT_VALID	BIT(2)
/* RA config.mode parameter is valid क्रम RM ring configure TI_SCI message */
#घोषणा TI_SCI_MSG_VALUE_RM_RING_MODE_VALID	BIT(3)
/* RA config.size parameter is valid क्रम RM ring configure TI_SCI message */
#घोषणा TI_SCI_MSG_VALUE_RM_RING_SIZE_VALID	BIT(4)
/* RA config.order_id parameter is valid क्रम RM ring configure TISCI message */
#घोषणा TI_SCI_MSG_VALUE_RM_RING_ORDER_ID_VALID	BIT(5)
/* RA config.virtid parameter is valid क्रम RM ring configure TISCI message */
#घोषणा TI_SCI_MSG_VALUE_RM_RING_VIRTID_VALID	BIT(6)
/* RA config.asel parameter is valid क्रम RM ring configure TISCI message */
#घोषणा TI_SCI_MSG_VALUE_RM_RING_ASEL_VALID	BIT(7)

#घोषणा TI_SCI_MSG_VALUE_RM_ALL_NO_ORDER \
	(TI_SCI_MSG_VALUE_RM_RING_ADDR_LO_VALID | \
	TI_SCI_MSG_VALUE_RM_RING_ADDR_HI_VALID | \
	TI_SCI_MSG_VALUE_RM_RING_COUNT_VALID | \
	TI_SCI_MSG_VALUE_RM_RING_MODE_VALID | \
	TI_SCI_MSG_VALUE_RM_RING_SIZE_VALID | \
	TI_SCI_MSG_VALUE_RM_RING_ASEL_VALID)

/**
 * काष्ठा ti_sci_msg_rm_ring_cfg - Ring configuration
 *
 * Parameters क्रम Navigator Subप्रणाली ring configuration
 * See @ti_sci_msg_rm_ring_cfg_req
 */
काष्ठा ti_sci_msg_rm_ring_cfg अणु
	u32 valid_params;
	u16 nav_id;
	u16 index;
	u32 addr_lo;
	u32 addr_hi;
	u32 count;
	u8 mode;
	u8 size;
	u8 order_id;
	u16 virtid;
	u8 asel;
पूर्ण;

/**
 * काष्ठा ti_sci_rm_ringacc_ops - Ring Accelerator Management operations
 * @set_cfg: configure the SoC Navigator Subप्रणाली Ring Accelerator ring
 */
काष्ठा ti_sci_rm_ringacc_ops अणु
	पूर्णांक (*set_cfg)(स्थिर काष्ठा ti_sci_handle *handle,
		       स्थिर काष्ठा ti_sci_msg_rm_ring_cfg *params);
पूर्ण;

/**
 * काष्ठा ti_sci_rm_psil_ops - PSI-L thपढ़ो operations
 * @pair: pair PSI-L source thपढ़ो to a destination thपढ़ो.
 *	If the src_thपढ़ो is mapped to UDMA tchan, the corresponding channel's
 *	TCHAN_THRD_ID रेजिस्टर is updated.
 *	If the dst_thपढ़ो is mapped to UDMA rchan, the corresponding channel's
 *	RCHAN_THRD_ID रेजिस्टर is updated.
 * @unpair: unpair PSI-L source thपढ़ो from a destination thपढ़ो.
 *	If the src_thपढ़ो is mapped to UDMA tchan, the corresponding channel's
 *	TCHAN_THRD_ID रेजिस्टर is cleared.
 *	If the dst_thपढ़ो is mapped to UDMA rchan, the corresponding channel's
 *	RCHAN_THRD_ID रेजिस्टर is cleared.
 */
काष्ठा ti_sci_rm_psil_ops अणु
	पूर्णांक (*pair)(स्थिर काष्ठा ti_sci_handle *handle, u32 nav_id,
		    u32 src_thपढ़ो, u32 dst_thपढ़ो);
	पूर्णांक (*unpair)(स्थिर काष्ठा ti_sci_handle *handle, u32 nav_id,
		      u32 src_thपढ़ो, u32 dst_thपढ़ो);
पूर्ण;

/* UDMAP channel types */
#घोषणा TI_SCI_RM_UDMAP_CHAN_TYPE_PKT_PBRR		2
#घोषणा TI_SCI_RM_UDMAP_CHAN_TYPE_PKT_PBRR_SB		3	/* RX only */
#घोषणा TI_SCI_RM_UDMAP_CHAN_TYPE_3RDP_PBRR		10
#घोषणा TI_SCI_RM_UDMAP_CHAN_TYPE_3RDP_PBVR		11
#घोषणा TI_SCI_RM_UDMAP_CHAN_TYPE_3RDP_BCOPY_PBRR	12
#घोषणा TI_SCI_RM_UDMAP_CHAN_TYPE_3RDP_BCOPY_PBVR	13

#घोषणा TI_SCI_RM_UDMAP_RX_FLOW_DESC_HOST		0
#घोषणा TI_SCI_RM_UDMAP_RX_FLOW_DESC_MONO		2

#घोषणा TI_SCI_RM_UDMAP_CHAN_BURST_SIZE_64_BYTES	1
#घोषणा TI_SCI_RM_UDMAP_CHAN_BURST_SIZE_128_BYTES	2
#घोषणा TI_SCI_RM_UDMAP_CHAN_BURST_SIZE_256_BYTES	3

#घोषणा TI_SCI_RM_BCDMA_EXTENDED_CH_TYPE_TCHAN		0
#घोषणा TI_SCI_RM_BCDMA_EXTENDED_CH_TYPE_BCHAN		1

/* UDMAP TX/RX channel valid_params common declarations */
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_CH_PAUSE_ON_ERR_VALID		BIT(0)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_CH_ATYPE_VALID                BIT(1)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_CH_CHAN_TYPE_VALID            BIT(2)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_CH_FETCH_SIZE_VALID           BIT(3)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_CH_CQ_QNUM_VALID              BIT(4)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_CH_PRIORITY_VALID             BIT(5)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_CH_QOS_VALID                  BIT(6)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_CH_ORDER_ID_VALID             BIT(7)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_CH_SCHED_PRIORITY_VALID       BIT(8)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_CH_BURST_SIZE_VALID		BIT(14)

/**
 * Configures a Navigator Subप्रणाली UDMAP transmit channel
 *
 * Configures a Navigator Subप्रणाली UDMAP transmit channel रेजिस्टरs.
 * See @ti_sci_msg_rm_udmap_tx_ch_cfg_req
 */
काष्ठा ti_sci_msg_rm_udmap_tx_ch_cfg अणु
	u32 valid_params;
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_CH_TX_FILT_EINFO_VALID        BIT(9)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_CH_TX_FILT_PSWORDS_VALID      BIT(10)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_CH_TX_SUPR_TDPKT_VALID        BIT(11)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_CH_TX_CREDIT_COUNT_VALID      BIT(12)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_CH_TX_FDEPTH_VALID            BIT(13)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_CH_TX_TDTYPE_VALID            BIT(15)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_CH_EXTENDED_CH_TYPE_VALID	BIT(16)
	u16 nav_id;
	u16 index;
	u8 tx_छोड़ो_on_err;
	u8 tx_filt_einfo;
	u8 tx_filt_pswords;
	u8 tx_atype;
	u8 tx_chan_type;
	u8 tx_supr_tdpkt;
	u16 tx_fetch_size;
	u8 tx_credit_count;
	u16 txcq_qnum;
	u8 tx_priority;
	u8 tx_qos;
	u8 tx_orderid;
	u16 fdepth;
	u8 tx_sched_priority;
	u8 tx_burst_size;
	u8 tx_tdtype;
	u8 extended_ch_type;
पूर्ण;

/**
 * Configures a Navigator Subप्रणाली UDMAP receive channel
 *
 * Configures a Navigator Subप्रणाली UDMAP receive channel रेजिस्टरs.
 * See @ti_sci_msg_rm_udmap_rx_ch_cfg_req
 */
काष्ठा ti_sci_msg_rm_udmap_rx_ch_cfg अणु
	u32 valid_params;
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_CH_RX_FLOWID_START_VALID      BIT(9)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_CH_RX_FLOWID_CNT_VALID        BIT(10)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_CH_RX_IGNORE_SHORT_VALID      BIT(11)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_CH_RX_IGNORE_LONG_VALID       BIT(12)
	u16 nav_id;
	u16 index;
	u16 rx_fetch_size;
	u16 rxcq_qnum;
	u8 rx_priority;
	u8 rx_qos;
	u8 rx_orderid;
	u8 rx_sched_priority;
	u16 flowid_start;
	u16 flowid_cnt;
	u8 rx_छोड़ो_on_err;
	u8 rx_atype;
	u8 rx_chan_type;
	u8 rx_ignore_लघु;
	u8 rx_ignore_दीर्घ;
	u8 rx_burst_size;
पूर्ण;

/**
 * Configures a Navigator Subप्रणाली UDMAP receive flow
 *
 * Configures a Navigator Subप्रणाली UDMAP receive flow's रेजिस्टरs.
 * See @tis_ci_msg_rm_udmap_flow_cfg_req
 */
काष्ठा ti_sci_msg_rm_udmap_flow_cfg अणु
	u32 valid_params;
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_EINFO_PRESENT_VALID	BIT(0)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_PSINFO_PRESENT_VALID     BIT(1)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_ERROR_HANDLING_VALID     BIT(2)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_DESC_TYPE_VALID          BIT(3)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_SOP_OFFSET_VALID         BIT(4)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_DEST_QNUM_VALID          BIT(5)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_SRC_TAG_HI_VALID         BIT(6)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_SRC_TAG_LO_VALID         BIT(7)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_DEST_TAG_HI_VALID        BIT(8)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_DEST_TAG_LO_VALID        BIT(9)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_SRC_TAG_HI_SEL_VALID     BIT(10)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_SRC_TAG_LO_SEL_VALID     BIT(11)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_DEST_TAG_HI_SEL_VALID    BIT(12)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_DEST_TAG_LO_SEL_VALID    BIT(13)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ0_SZ0_QNUM_VALID      BIT(14)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ1_QNUM_VALID          BIT(15)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ2_QNUM_VALID          BIT(16)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ3_QNUM_VALID          BIT(17)
#घोषणा TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_PS_LOCATION_VALID        BIT(18)
	u16 nav_id;
	u16 flow_index;
	u8 rx_einfo_present;
	u8 rx_psinfo_present;
	u8 rx_error_handling;
	u8 rx_desc_type;
	u16 rx_sop_offset;
	u16 rx_dest_qnum;
	u8 rx_src_tag_hi;
	u8 rx_src_tag_lo;
	u8 rx_dest_tag_hi;
	u8 rx_dest_tag_lo;
	u8 rx_src_tag_hi_sel;
	u8 rx_src_tag_lo_sel;
	u8 rx_dest_tag_hi_sel;
	u8 rx_dest_tag_lo_sel;
	u16 rx_fdq0_sz0_qnum;
	u16 rx_fdq1_qnum;
	u16 rx_fdq2_qnum;
	u16 rx_fdq3_qnum;
	u8 rx_ps_location;
पूर्ण;

/**
 * काष्ठा ti_sci_rm_udmap_ops - UDMA Management operations
 * @tx_ch_cfg: configure SoC Navigator Subप्रणाली UDMA transmit channel.
 * @rx_ch_cfg: configure SoC Navigator Subप्रणाली UDMA receive channel.
 * @rx_flow_cfg1: configure SoC Navigator Subप्रणाली UDMA receive flow.
 */
काष्ठा ti_sci_rm_udmap_ops अणु
	पूर्णांक (*tx_ch_cfg)(स्थिर काष्ठा ti_sci_handle *handle,
			 स्थिर काष्ठा ti_sci_msg_rm_udmap_tx_ch_cfg *params);
	पूर्णांक (*rx_ch_cfg)(स्थिर काष्ठा ti_sci_handle *handle,
			 स्थिर काष्ठा ti_sci_msg_rm_udmap_rx_ch_cfg *params);
	पूर्णांक (*rx_flow_cfg)(स्थिर काष्ठा ti_sci_handle *handle,
			   स्थिर काष्ठा ti_sci_msg_rm_udmap_flow_cfg *params);
पूर्ण;

/**
 * काष्ठा ti_sci_proc_ops - Processor Control operations
 * @request:	Request to control a physical processor. The requesting host
 *		should be in the processor access list
 * @release:	Relinquish a physical processor control
 * @hanकरोver:	Hanकरोver a physical processor control to another host
 *		in the permitted list
 * @set_config:	Set base configuration of a processor
 * @set_control: Setup limited control flags in specअगरic हालs
 * @get_status: Get the state of physical processor
 *
 * NOTE: The following paramteres are generic in nature क्रम all these ops,
 * -handle:	Poपूर्णांकer to TI SCI handle as retrieved by *ti_sci_get_handle
 * -pid:	Processor ID
 * -hid:	Host ID
 */
काष्ठा ti_sci_proc_ops अणु
	पूर्णांक (*request)(स्थिर काष्ठा ti_sci_handle *handle, u8 pid);
	पूर्णांक (*release)(स्थिर काष्ठा ti_sci_handle *handle, u8 pid);
	पूर्णांक (*hanकरोver)(स्थिर काष्ठा ti_sci_handle *handle, u8 pid, u8 hid);
	पूर्णांक (*set_config)(स्थिर काष्ठा ti_sci_handle *handle, u8 pid,
			  u64 boot_vector, u32 cfg_set, u32 cfg_clr);
	पूर्णांक (*set_control)(स्थिर काष्ठा ti_sci_handle *handle, u8 pid,
			   u32 ctrl_set, u32 ctrl_clr);
	पूर्णांक (*get_status)(स्थिर काष्ठा ti_sci_handle *handle, u8 pid,
			  u64 *boot_vector, u32 *cfg_flags, u32 *ctrl_flags,
			  u32 *status_flags);
पूर्ण;

/**
 * काष्ठा ti_sci_ops - Function support क्रम TI SCI
 * @dev_ops:	Device specअगरic operations
 * @clk_ops:	Clock specअगरic operations
 * @rm_core_ops:	Resource management core operations.
 * @rm_irq_ops:		IRQ management specअगरic operations
 * @proc_ops:	Processor Control specअगरic operations
 */
काष्ठा ti_sci_ops अणु
	काष्ठा ti_sci_core_ops core_ops;
	काष्ठा ti_sci_dev_ops dev_ops;
	काष्ठा ti_sci_clk_ops clk_ops;
	काष्ठा ti_sci_rm_core_ops rm_core_ops;
	काष्ठा ti_sci_rm_irq_ops rm_irq_ops;
	काष्ठा ti_sci_rm_ringacc_ops rm_ring_ops;
	काष्ठा ti_sci_rm_psil_ops rm_psil_ops;
	काष्ठा ti_sci_rm_udmap_ops rm_udmap_ops;
	काष्ठा ti_sci_proc_ops proc_ops;
पूर्ण;

/**
 * काष्ठा ti_sci_handle - Handle वापसed to TI SCI clients क्रम usage.
 * @version:	काष्ठाure containing version inक्रमmation
 * @ops:	operations that are made available to TI SCI clients
 */
काष्ठा ti_sci_handle अणु
	काष्ठा ti_sci_version_info version;
	काष्ठा ti_sci_ops ops;
पूर्ण;

#घोषणा TI_SCI_RESOURCE_शून्य	0xffff

/**
 * काष्ठा ti_sci_resource - Structure representing a resource asचिन्हित
 *			    to a device.
 * @sets:	Number of sets available from this resource type
 * @lock:	Lock to guard the res map in each set.
 * @desc:	Array of resource descriptors.
 */
काष्ठा ti_sci_resource अणु
	u16 sets;
	raw_spinlock_t lock;
	काष्ठा ti_sci_resource_desc *desc;
पूर्ण;

#अगर IS_ENABLED(CONFIG_TI_SCI_PROTOCOL)
स्थिर काष्ठा ti_sci_handle *ti_sci_get_handle(काष्ठा device *dev);
पूर्णांक ti_sci_put_handle(स्थिर काष्ठा ti_sci_handle *handle);
स्थिर काष्ठा ti_sci_handle *devm_ti_sci_get_handle(काष्ठा device *dev);
स्थिर काष्ठा ti_sci_handle *ti_sci_get_by_phandle(काष्ठा device_node *np,
						  स्थिर अक्षर *property);
स्थिर काष्ठा ti_sci_handle *devm_ti_sci_get_by_phandle(काष्ठा device *dev,
						       स्थिर अक्षर *property);
u16 ti_sci_get_मुक्त_resource(काष्ठा ti_sci_resource *res);
व्योम ti_sci_release_resource(काष्ठा ti_sci_resource *res, u16 id);
u32 ti_sci_get_num_resources(काष्ठा ti_sci_resource *res);
काष्ठा ti_sci_resource *
devm_ti_sci_get_of_resource(स्थिर काष्ठा ti_sci_handle *handle,
			    काष्ठा device *dev, u32 dev_id, अक्षर *of_prop);
काष्ठा ti_sci_resource *
devm_ti_sci_get_resource(स्थिर काष्ठा ti_sci_handle *handle, काष्ठा device *dev,
			 u32 dev_id, u32 sub_type);

#अन्यथा	/* CONFIG_TI_SCI_PROTOCOL */

अटल अंतरभूत स्थिर काष्ठा ti_sci_handle *ti_sci_get_handle(काष्ठा device *dev)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल अंतरभूत पूर्णांक ti_sci_put_handle(स्थिर काष्ठा ti_sci_handle *handle)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत
स्थिर काष्ठा ti_sci_handle *devm_ti_sci_get_handle(काष्ठा device *dev)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल अंतरभूत
स्थिर काष्ठा ti_sci_handle *ti_sci_get_by_phandle(काष्ठा device_node *np,
						  स्थिर अक्षर *property)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल अंतरभूत
स्थिर काष्ठा ti_sci_handle *devm_ti_sci_get_by_phandle(काष्ठा device *dev,
						       स्थिर अक्षर *property)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल अंतरभूत u16 ti_sci_get_मुक्त_resource(काष्ठा ti_sci_resource *res)
अणु
	वापस TI_SCI_RESOURCE_शून्य;
पूर्ण

अटल अंतरभूत व्योम ti_sci_release_resource(काष्ठा ti_sci_resource *res, u16 id)
अणु
पूर्ण

अटल अंतरभूत u32 ti_sci_get_num_resources(काष्ठा ti_sci_resource *res)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा ti_sci_resource *
devm_ti_sci_get_of_resource(स्थिर काष्ठा ti_sci_handle *handle,
			    काष्ठा device *dev, u32 dev_id, अक्षर *of_prop)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल अंतरभूत काष्ठा ti_sci_resource *
devm_ti_sci_get_resource(स्थिर काष्ठा ti_sci_handle *handle, काष्ठा device *dev,
			 u32 dev_id, u32 sub_type);
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण
#पूर्ण_अगर	/* CONFIG_TI_SCI_PROTOCOL */

#पूर्ण_अगर	/* __TISCI_PROTOCOL_H */
