<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2012-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fw_api_tx_h__
#घोषणा __iwl_fw_api_tx_h__
#समावेश <linux/ieee80211.h>

/**
 * क्रमागत iwl_tx_flags - biपंचांगasks क्रम tx_flags in TX command
 * @TX_CMD_FLG_PROT_REQUIRE: use RTS or CTS-to-self to protect the frame
 * @TX_CMD_FLG_WRITE_TX_POWER: update current tx घातer value in the mgmt frame
 * @TX_CMD_FLG_ACK: expect ACK from receiving station
 * @TX_CMD_FLG_STA_RATE: use RS table with initial index from the TX command.
 *	Otherwise, use rate_n_flags from the TX command
 * @TX_CMD_FLG_BAR: this frame is a BA request, immediate BAR is expected
 *	Must set TX_CMD_FLG_ACK with this flag.
 * @TX_CMD_FLG_TXOP_PROT: TXOP protection requested
 * @TX_CMD_FLG_VHT_NDPA: mark frame is NDPA क्रम VHT beamक्रमmer sequence
 * @TX_CMD_FLG_HT_NDPA: mark frame is NDPA क्रम HT beamक्रमmer sequence
 * @TX_CMD_FLG_CSI_FDBK2HOST: mark to send feedback to host (only अगर good CRC)
 * @TX_CMD_FLG_BT_PRIO_MASK: BT priority value
 * @TX_CMD_FLG_BT_PRIO_POS: the position of the BT priority (bit 11 is ignored
 *	on old firmwares).
 * @TX_CMD_FLG_BT_DIS: disable BT priority क्रम this frame
 * @TX_CMD_FLG_SEQ_CTL: set अगर FW should override the sequence control.
 *	Should be set क्रम mgmt, non-QOS data, mcast, bcast and in scan command
 * @TX_CMD_FLG_MORE_FRAG: this frame is non-last MPDU
 * @TX_CMD_FLG_TSF: FW should calculate and insert TSF in the frame
 *	Should be set क्रम beacons and probe responses
 * @TX_CMD_FLG_CALIB: activate PA TX घातer calibrations
 * @TX_CMD_FLG_KEEP_SEQ_CTL: अगर seq_ctl is set, करोn't increase inner seq count
 * @TX_CMD_FLG_MH_PAD: driver inserted 2 byte padding after MAC header.
 *	Should be set क्रम 26/30 length MAC headers
 * @TX_CMD_FLG_RESP_TO_DRV: zero this अगर the response should go only to FW
 * @TX_CMD_FLG_TKIP_MIC_DONE: FW alपढ़ोy perक्रमmed TKIP MIC calculation
 * @TX_CMD_FLG_DUR: disable duration overwriting used in PS-Poll Assoc-id
 * @TX_CMD_FLG_FW_DROP: FW should mark frame to be dropped
 * @TX_CMD_FLG_EXEC_PAPD: execute PAPD
 * @TX_CMD_FLG_PAPD_TYPE: 0 क्रम reference घातer, 1 क्रम nominal घातer
 * @TX_CMD_FLG_HCCA_CHUNK: mark start of TSPEC chunk
 */
क्रमागत iwl_tx_flags अणु
	TX_CMD_FLG_PROT_REQUIRE		= BIT(0),
	TX_CMD_FLG_WRITE_TX_POWER	= BIT(1),
	TX_CMD_FLG_ACK			= BIT(3),
	TX_CMD_FLG_STA_RATE		= BIT(4),
	TX_CMD_FLG_BAR			= BIT(6),
	TX_CMD_FLG_TXOP_PROT		= BIT(7),
	TX_CMD_FLG_VHT_NDPA		= BIT(8),
	TX_CMD_FLG_HT_NDPA		= BIT(9),
	TX_CMD_FLG_CSI_FDBK2HOST	= BIT(10),
	TX_CMD_FLG_BT_PRIO_POS		= 11,
	TX_CMD_FLG_BT_PRIO_MASK		= BIT(11) | BIT(12),
	TX_CMD_FLG_BT_DIS		= BIT(12),
	TX_CMD_FLG_SEQ_CTL		= BIT(13),
	TX_CMD_FLG_MORE_FRAG		= BIT(14),
	TX_CMD_FLG_TSF			= BIT(16),
	TX_CMD_FLG_CALIB		= BIT(17),
	TX_CMD_FLG_KEEP_SEQ_CTL		= BIT(18),
	TX_CMD_FLG_MH_PAD		= BIT(20),
	TX_CMD_FLG_RESP_TO_DRV		= BIT(21),
	TX_CMD_FLG_TKIP_MIC_DONE	= BIT(23),
	TX_CMD_FLG_DUR			= BIT(25),
	TX_CMD_FLG_FW_DROP		= BIT(26),
	TX_CMD_FLG_EXEC_PAPD		= BIT(27),
	TX_CMD_FLG_PAPD_TYPE		= BIT(28),
	TX_CMD_FLG_HCCA_CHUNK		= BIT(31)
पूर्ण; /* TX_FLAGS_BITS_API_S_VER_1 */

/**
 * क्रमागत iwl_tx_cmd_flags - biपंचांगasks क्रम tx_flags in TX command क्रम 22000
 * @IWL_TX_FLAGS_CMD_RATE: use rate from the TX command
 * @IWL_TX_FLAGS_ENCRYPT_DIS: frame should not be encrypted, even अगर it beदीर्घs
 *	to a secured STA
 * @IWL_TX_FLAGS_HIGH_PRI: high priority frame (like EAPOL) - can affect rate
 *	selection, retry limits and BT समाप्त
 */
क्रमागत iwl_tx_cmd_flags अणु
	IWL_TX_FLAGS_CMD_RATE		= BIT(0),
	IWL_TX_FLAGS_ENCRYPT_DIS	= BIT(1),
	IWL_TX_FLAGS_HIGH_PRI		= BIT(2),
पूर्ण; /* TX_FLAGS_BITS_API_S_VER_3 */

/**
 * क्रमागत iwl_tx_pm_समयouts - pm समयout values in TX command
 * @PM_FRAME_NONE: no need to suspend sleep mode
 * @PM_FRAME_MGMT: fw suspend sleep mode क्रम 100TU
 * @PM_FRAME_ASSOC: fw suspend sleep mode क्रम 10sec
 */
क्रमागत iwl_tx_pm_समयouts अणु
	PM_FRAME_NONE		= 0,
	PM_FRAME_MGMT		= 2,
	PM_FRAME_ASSOC		= 3,
पूर्ण;

#घोषणा TX_CMD_SEC_MSK			0x07
#घोषणा TX_CMD_SEC_WEP_KEY_IDX_POS	6
#घोषणा TX_CMD_SEC_WEP_KEY_IDX_MSK	0xc0

/**
 * क्रमागत iwl_tx_cmd_sec_ctrl - biपंचांगasks क्रम security control in TX command
 * @TX_CMD_SEC_WEP: WEP encryption algorithm.
 * @TX_CMD_SEC_CCM: CCM encryption algorithm.
 * @TX_CMD_SEC_TKIP: TKIP encryption algorithm.
 * @TX_CMD_SEC_EXT: extended cipher algorithm.
 * @TX_CMD_SEC_GCMP: GCMP encryption algorithm.
 * @TX_CMD_SEC_KEY128: set क्रम 104 bits WEP key.
 * @TX_CMD_SEC_KEY_FROM_TABLE: क्रम a non-WEP key, set अगर the key should be taken
 *	from the table instead of from the TX command.
 *	If the key is taken from the key table its index should be given by the
 *	first byte of the TX command key field.
 */
क्रमागत iwl_tx_cmd_sec_ctrl अणु
	TX_CMD_SEC_WEP			= 0x01,
	TX_CMD_SEC_CCM			= 0x02,
	TX_CMD_SEC_TKIP			= 0x03,
	TX_CMD_SEC_EXT			= 0x04,
	TX_CMD_SEC_GCMP			= 0x05,
	TX_CMD_SEC_KEY128		= 0x08,
	TX_CMD_SEC_KEY_FROM_TABLE	= 0x10,
पूर्ण;

/*
 * TX command Frame lअगरe समय in us - to be written in pm_frame_समयout
 */
#घोषणा TX_CMD_LIFE_TIME_INFINITE	0xFFFFFFFF
#घोषणा TX_CMD_LIFE_TIME_DEFAULT	2000000 /* 2000 ms*/
#घोषणा TX_CMD_LIFE_TIME_PROBE_RESP	40000 /* 40 ms */
#घोषणा TX_CMD_LIFE_TIME_EXPIRED_FRAME	0

/*
 * TID क्रम non QoS frames - to be written in tid_tspec
 */
#घोषणा IWL_TID_NON_QOS	0

/*
 * Limits on the retransmissions - to be written in अणुdata,rtsपूर्ण_retry_limit
 */
#घोषणा IWL_DEFAULT_TX_RETRY			15
#घोषणा IWL_MGMT_DFAULT_RETRY_LIMIT		3
#घोषणा IWL_RTS_DFAULT_RETRY_LIMIT		60
#घोषणा IWL_BAR_DFAULT_RETRY_LIMIT		60
#घोषणा IWL_LOW_RETRY_LIMIT			7

/**
 * क्रमागत iwl_tx_offload_assist_flags_pos -  set %iwl_tx_cmd offload_assist values
 * @TX_CMD_OFFLD_IP_HDR: offset to start of IP header (in words)
 *	from mac header end. For normal हाल it is 4 words क्रम SNAP.
 *	note: tx_cmd, mac header and pad are not counted in the offset.
 *	This is used to help the offload in हाल there is tunneling such as
 *	IPv6 in IPv4, in such हाल the ip header offset should poपूर्णांक to the
 *	inner ip header and IPv4 checksum of the बाह्यal header should be
 *	calculated by driver.
 * @TX_CMD_OFFLD_L4_EN: enable TCP/UDP checksum
 * @TX_CMD_OFFLD_L3_EN: enable IP header checksum
 * @TX_CMD_OFFLD_MH_SIZE: size of the mac header in words. Includes the IV
 *	field. Doesn't include the pad.
 * @TX_CMD_OFFLD_PAD: mark 2-byte pad was inserted after the mac header क्रम
 *	alignment
 * @TX_CMD_OFFLD_AMSDU: mark TX command is A-MSDU
 */
क्रमागत iwl_tx_offload_assist_flags_pos अणु
	TX_CMD_OFFLD_IP_HDR =		0,
	TX_CMD_OFFLD_L4_EN =		6,
	TX_CMD_OFFLD_L3_EN =		7,
	TX_CMD_OFFLD_MH_SIZE =		8,
	TX_CMD_OFFLD_PAD =		13,
	TX_CMD_OFFLD_AMSDU =		14,
पूर्ण;

#घोषणा IWL_TX_CMD_OFFLD_MH_MASK	0x1f
#घोषणा IWL_TX_CMD_OFFLD_IP_HDR_MASK	0x3f

/* TODO: complete करोcumentation क्रम try_cnt and btसमाप्त_cnt */
/**
 * काष्ठा iwl_tx_cmd - TX command काष्ठा to FW
 * ( TX_CMD = 0x1c )
 * @len: in bytes of the payload, see below क्रम details
 * @offload_assist: TX offload configuration
 * @tx_flags: combination of TX_CMD_FLG_*, see &क्रमागत iwl_tx_flags
 * @scratch: scratch buffer used by the device
 * @rate_n_flags: rate क्रम *all* Tx attempts, अगर TX_CMD_FLG_STA_RATE_MSK is
 *	cleared. Combination of RATE_MCS_*
 * @sta_id: index of destination station in FW station table
 * @sec_ctl: security control, TX_CMD_SEC_*
 * @initial_rate_index: index पूर्णांकo the the rate table क्रम initial TX attempt.
 *	Applied अगर TX_CMD_FLG_STA_RATE_MSK is set, normally 0 क्रम data frames.
 * @reserved2: reserved
 * @key: security key
 * @reserved3: reserved
 * @lअगरe_समय: frame lअगरe समय (usecs??)
 * @dram_lsb_ptr: Physical address of scratch area in the command (try_cnt +
 *	btसमाप्त_cnd + reserved), first 32 bits. "0" disables usage.
 * @dram_msb_ptr: upper bits of the scratch physical address
 * @rts_retry_limit: max attempts क्रम RTS
 * @data_retry_limit: max attempts to send the data packet
 * @tid_tspec: TID/tspec
 * @pm_frame_समयout: PM TX frame समयout
 * @reserved4: reserved
 * @payload: payload (same as @hdr)
 * @hdr: 802.11 header (same as @payload)
 *
 * The byte count (both len and next_frame_len) includes MAC header
 * (24/26/30/32 bytes)
 * + 2 bytes pad अगर 26/30 header size
 * + 8 byte IV क्रम CCM or TKIP (not used क्रम WEP)
 * + Data payload
 * + 8-byte MIC (not used क्रम CCM/WEP)
 * It करोes not include post-MAC padding, i.e.,
 * MIC (CCM) 8 bytes, ICV (WEP/TKIP/CKIP) 4 bytes, CRC 4 bytes.
 * Range of len: 14-2342 bytes.
 *
 * After the काष्ठा fields the MAC header is placed, plus any padding,
 * and then the actial payload.
 */
काष्ठा iwl_tx_cmd अणु
	__le16 len;
	__le16 offload_assist;
	__le32 tx_flags;
	काष्ठा अणु
		u8 try_cnt;
		u8 btसमाप्त_cnt;
		__le16 reserved;
	पूर्ण scratch; /* DRAM_SCRATCH_API_U_VER_1 */
	__le32 rate_n_flags;
	u8 sta_id;
	u8 sec_ctl;
	u8 initial_rate_index;
	u8 reserved2;
	u8 key[16];
	__le32 reserved3;
	__le32 lअगरe_समय;
	__le32 dram_lsb_ptr;
	u8 dram_msb_ptr;
	u8 rts_retry_limit;
	u8 data_retry_limit;
	u8 tid_tspec;
	__le16 pm_frame_समयout;
	__le16 reserved4;
	u8 payload[0];
	काष्ठा ieee80211_hdr hdr[0];
पूर्ण __packed; /* TX_CMD_API_S_VER_6 */

काष्ठा iwl_dram_sec_info अणु
	__le32 pn_low;
	__le16 pn_high;
	__le16 aux_info;
पूर्ण __packed; /* DRAM_SEC_INFO_API_S_VER_1 */

/**
 * काष्ठा iwl_tx_cmd_gen2 - TX command काष्ठा to FW क्रम 22000 devices
 * ( TX_CMD = 0x1c )
 * @len: in bytes of the payload, see below क्रम details
 * @offload_assist: TX offload configuration
 * @flags: combination of &क्रमागत iwl_tx_cmd_flags
 * @dram_info: FW पूर्णांकernal DRAM storage
 * @rate_n_flags: rate क्रम *all* Tx attempts, अगर TX_CMD_FLG_STA_RATE_MSK is
 *	cleared. Combination of RATE_MCS_*
 * @hdr: 802.11 header
 */
काष्ठा iwl_tx_cmd_gen2 अणु
	__le16 len;
	__le16 offload_assist;
	__le32 flags;
	काष्ठा iwl_dram_sec_info dram_info;
	__le32 rate_n_flags;
	काष्ठा ieee80211_hdr hdr[];
पूर्ण __packed; /* TX_CMD_API_S_VER_7 */

/**
 * काष्ठा iwl_tx_cmd_gen3 - TX command काष्ठा to FW क्रम AX210+ devices
 * ( TX_CMD = 0x1c )
 * @len: in bytes of the payload, see below क्रम details
 * @flags: combination of &क्रमागत iwl_tx_cmd_flags
 * @offload_assist: TX offload configuration
 * @dram_info: FW पूर्णांकernal DRAM storage
 * @rate_n_flags: rate क्रम *all* Tx attempts, अगर TX_CMD_FLG_STA_RATE_MSK is
 *	cleared. Combination of RATE_MCS_*
 * @ttl: समय to live - packet lअगरeसमय limit. The FW should drop अगर
 *	passed.
 * @hdr: 802.11 header
 */
काष्ठा iwl_tx_cmd_gen3 अणु
	__le16 len;
	__le16 flags;
	__le32 offload_assist;
	काष्ठा iwl_dram_sec_info dram_info;
	__le32 rate_n_flags;
	__le64 ttl;
	काष्ठा ieee80211_hdr hdr[];
पूर्ण __packed; /* TX_CMD_API_S_VER_8 */

/*
 * TX response related data
 */

/*
 * क्रमागत iwl_tx_status - status that is वापसed by the fw after attempts to Tx
 * @TX_STATUS_SUCCESS:
 * @TX_STATUS_सूचीECT_DONE:
 * @TX_STATUS_POSTPONE_DELAY:
 * @TX_STATUS_POSTPONE_FEW_BYTES:
 * @TX_STATUS_POSTPONE_BT_PRIO:
 * @TX_STATUS_POSTPONE_QUIET_PERIOD:
 * @TX_STATUS_POSTPONE_CALC_TTAK:
 * @TX_STATUS_FAIL_INTERNAL_CROSSED_RETRY:
 * @TX_STATUS_FAIL_SHORT_LIMIT:
 * @TX_STATUS_FAIL_LONG_LIMIT:
 * @TX_STATUS_FAIL_UNDERRUN:
 * @TX_STATUS_FAIL_DRAIN_FLOW:
 * @TX_STATUS_FAIL_RFKILL_FLUSH:
 * @TX_STATUS_FAIL_LIFE_EXPIRE:
 * @TX_STATUS_FAIL_DEST_PS:
 * @TX_STATUS_FAIL_HOST_ABORTED:
 * @TX_STATUS_FAIL_BT_RETRY:
 * @TX_STATUS_FAIL_STA_INVALID:
 * @TX_TATUS_FAIL_FRAG_DROPPED:
 * @TX_STATUS_FAIL_TID_DISABLE:
 * @TX_STATUS_FAIL_FIFO_FLUSHED:
 * @TX_STATUS_FAIL_SMALL_CF_POLL:
 * @TX_STATUS_FAIL_FW_DROP:
 * @TX_STATUS_FAIL_STA_COLOR_MISMATCH: mismatch between color of Tx cmd and
 *	STA table
 * @TX_FRAME_STATUS_INTERNAL_ABORT:
 * @TX_MODE_MSK:
 * @TX_MODE_NO_BURST:
 * @TX_MODE_IN_BURST_SEQ:
 * @TX_MODE_FIRST_IN_BURST:
 * @TX_QUEUE_NUM_MSK:
 *
 * Valid only अगर frame_count =1
 * TODO: complete करोcumentation
 */
क्रमागत iwl_tx_status अणु
	TX_STATUS_MSK = 0x000000ff,
	TX_STATUS_SUCCESS = 0x01,
	TX_STATUS_सूचीECT_DONE = 0x02,
	/* postpone TX */
	TX_STATUS_POSTPONE_DELAY = 0x40,
	TX_STATUS_POSTPONE_FEW_BYTES = 0x41,
	TX_STATUS_POSTPONE_BT_PRIO = 0x42,
	TX_STATUS_POSTPONE_QUIET_PERIOD = 0x43,
	TX_STATUS_POSTPONE_CALC_TTAK = 0x44,
	/* पात TX */
	TX_STATUS_FAIL_INTERNAL_CROSSED_RETRY = 0x81,
	TX_STATUS_FAIL_SHORT_LIMIT = 0x82,
	TX_STATUS_FAIL_LONG_LIMIT = 0x83,
	TX_STATUS_FAIL_UNDERRUN = 0x84,
	TX_STATUS_FAIL_DRAIN_FLOW = 0x85,
	TX_STATUS_FAIL_RFKILL_FLUSH = 0x86,
	TX_STATUS_FAIL_LIFE_EXPIRE = 0x87,
	TX_STATUS_FAIL_DEST_PS = 0x88,
	TX_STATUS_FAIL_HOST_ABORTED = 0x89,
	TX_STATUS_FAIL_BT_RETRY = 0x8a,
	TX_STATUS_FAIL_STA_INVALID = 0x8b,
	TX_STATUS_FAIL_FRAG_DROPPED = 0x8c,
	TX_STATUS_FAIL_TID_DISABLE = 0x8d,
	TX_STATUS_FAIL_FIFO_FLUSHED = 0x8e,
	TX_STATUS_FAIL_SMALL_CF_POLL = 0x8f,
	TX_STATUS_FAIL_FW_DROP = 0x90,
	TX_STATUS_FAIL_STA_COLOR_MISMATCH = 0x91,
	TX_STATUS_INTERNAL_ABORT = 0x92,
	TX_MODE_MSK = 0x00000f00,
	TX_MODE_NO_BURST = 0x00000000,
	TX_MODE_IN_BURST_SEQ = 0x00000100,
	TX_MODE_FIRST_IN_BURST = 0x00000200,
	TX_QUEUE_NUM_MSK = 0x0001f000,
	TX_NARROW_BW_MSK = 0x00060000,
	TX_NARROW_BW_1DIV2 = 0x00020000,
	TX_NARROW_BW_1DIV4 = 0x00040000,
	TX_NARROW_BW_1DIV8 = 0x00060000,
पूर्ण;

/*
 * क्रमागत iwl_tx_agg_status - TX aggregation status
 * @AGG_TX_STATE_STATUS_MSK:
 * @AGG_TX_STATE_TRANSMITTED:
 * @AGG_TX_STATE_UNDERRUN:
 * @AGG_TX_STATE_BT_PRIO:
 * @AGG_TX_STATE_FEW_BYTES:
 * @AGG_TX_STATE_ABORT:
 * @AGG_TX_STATE_TX_ON_AIR_DROP: TX_ON_AIR संकेत drop without underrun or
 *	BT detection
 * @AGG_TX_STATE_LAST_SENT_TRY_CNT:
 * @AGG_TX_STATE_LAST_SENT_BT_KILL:
 * @AGG_TX_STATE_SCD_QUERY:
 * @AGG_TX_STATE_TEST_BAD_CRC32:
 * @AGG_TX_STATE_RESPONSE:
 * @AGG_TX_STATE_DUMP_TX:
 * @AGG_TX_STATE_DELAY_TX:
 * @AGG_TX_STATE_TRY_CNT_MSK: Retry count क्रम 1st frame in aggregation (retries
 *	occur अगर tx failed क्रम this frame when it was a member of a previous
 *	aggregation block). If rate scaling is used, retry count indicates the
 *	rate table entry used क्रम all frames in the new agg.
 * @AGG_TX_STATE_SEQ_NUM_MSK: Command ID and sequence number of Tx command क्रम
 *	this frame
 *
 * TODO: complete करोcumentation
 */
क्रमागत iwl_tx_agg_status अणु
	AGG_TX_STATE_STATUS_MSK = 0x00fff,
	AGG_TX_STATE_TRANSMITTED = 0x000,
	AGG_TX_STATE_UNDERRUN = 0x001,
	AGG_TX_STATE_BT_PRIO = 0x002,
	AGG_TX_STATE_FEW_BYTES = 0x004,
	AGG_TX_STATE_ABORT = 0x008,
	AGG_TX_STATE_TX_ON_AIR_DROP = 0x010,
	AGG_TX_STATE_LAST_SENT_TRY_CNT = 0x020,
	AGG_TX_STATE_LAST_SENT_BT_KILL = 0x040,
	AGG_TX_STATE_SCD_QUERY = 0x080,
	AGG_TX_STATE_TEST_BAD_CRC32 = 0x0100,
	AGG_TX_STATE_RESPONSE = 0x1ff,
	AGG_TX_STATE_DUMP_TX = 0x200,
	AGG_TX_STATE_DELAY_TX = 0x400,
	AGG_TX_STATE_TRY_CNT_POS = 12,
	AGG_TX_STATE_TRY_CNT_MSK = 0xf << AGG_TX_STATE_TRY_CNT_POS,
पूर्ण;

/*
 * The mask below describes a status where we are असलolutely sure that the MPDU
 * wasn't sent. For BA/Underrun we cannot be that sure. All we know that we've
 * written the bytes to the TXE, but we know nothing about what the DSP did.
 */
#घोषणा AGG_TX_STAT_FRAME_NOT_SENT (AGG_TX_STATE_FEW_BYTES | \
				    AGG_TX_STATE_ABORT | \
				    AGG_TX_STATE_SCD_QUERY)

/*
 * REPLY_TX = 0x1c (response)
 *
 * This response may be in one of two slightly dअगरferent क्रमmats, indicated
 * by the frame_count field:
 *
 * 1)	No aggregation (frame_count == 1).  This reports Tx results क्रम a single
 *	frame. Multiple attempts, at various bit rates, may have been made क्रम
 *	this frame.
 *
 * 2)	Aggregation (frame_count > 1).  This reports Tx results क्रम two or more
 *	frames that used block-acknowledge.  All frames were transmitted at
 *	same rate. Rate scaling may have been used अगर first frame in this new
 *	agg block failed in previous agg block(s).
 *
 *	Note that, क्रम aggregation, ACK (block-ack) status is not delivered
 *	here; block-ack has not been received by the समय the device records
 *	this status.
 *	This status relates to reasons the tx might have been blocked or पातed
 *	within the device, rather than whether it was received successfully by
 *	the destination station.
 */

/**
 * काष्ठा agg_tx_status - per packet TX aggregation status
 * @status: See &क्रमागत iwl_tx_agg_status
 * @sequence: Sequence # क्रम this frame's Tx cmd (not SSN!)
 */
काष्ठा agg_tx_status अणु
	__le16 status;
	__le16 sequence;
पूर्ण __packed;

/*
 * definitions क्रम initial rate index field
 * bits [3:0] initial rate index
 * bits [6:4] rate table color, used क्रम the initial rate
 * bit-7 invalid rate indication
 */
#घोषणा TX_RES_INIT_RATE_INDEX_MSK 0x0f
#घोषणा TX_RES_RATE_TABLE_COLOR_POS 4
#घोषणा TX_RES_RATE_TABLE_COLOR_MSK 0x70
#घोषणा TX_RES_INV_RATE_INDEX_MSK 0x80
#घोषणा TX_RES_RATE_TABLE_COL_GET(_f) (((_f) & TX_RES_RATE_TABLE_COLOR_MSK) >>\
				       TX_RES_RATE_TABLE_COLOR_POS)

#घोषणा IWL_MVM_TX_RES_GET_TID(_ra_tid) ((_ra_tid) & 0x0f)
#घोषणा IWL_MVM_TX_RES_GET_RA(_ra_tid) ((_ra_tid) >> 4)

/**
 * काष्ठा iwl_mvm_tx_resp_v3 - notअगरies that fw is TXing a packet
 * ( REPLY_TX = 0x1c )
 * @frame_count: 1 no aggregation, >1 aggregation
 * @bt_समाप्त_count: num of बार blocked by bluetooth (unused क्रम agg)
 * @failure_rts: num of failures due to unsuccessful RTS
 * @failure_frame: num failures due to no ACK (unused क्रम agg)
 * @initial_rate: क्रम non-agg: rate of the successful Tx. For agg: rate of the
 *	Tx of all the batch. RATE_MCS_*
 * @wireless_media_समय: क्रम non-agg: RTS + CTS + frame tx attempts समय + ACK.
 *	क्रम agg: RTS + CTS + aggregation tx समय + block-ack समय.
 *	in usec.
 * @pa_status: tx घातer info
 * @pa_पूर्णांकeg_res_a: tx घातer info
 * @pa_पूर्णांकeg_res_b: tx घातer info
 * @pa_पूर्णांकeg_res_c: tx घातer info
 * @measurement_req_id: tx घातer info
 * @reduced_tpc: transmit घातer reduction used
 * @reserved: reserved
 * @tfd_info: TFD inक्रमmation set by the FH
 * @seq_ctl: sequence control from the Tx cmd
 * @byte_cnt: byte count from the Tx cmd
 * @tlc_info: TLC rate info
 * @ra_tid: bits [3:0] = ra, bits [7:4] = tid
 * @frame_ctrl: frame control
 * @status: क्रम non-agg:  frame status TX_STATUS_*
 *	क्रम agg: status of 1st frame, AGG_TX_STATE_*; other frame status fields
 *	follow this one, up to frame_count. Length in @frame_count.
 *
 * After the array of statuses comes the SSN of the SCD. Look at
 * %iwl_mvm_get_scd_ssn क्रम more details.
 */
काष्ठा iwl_mvm_tx_resp_v3 अणु
	u8 frame_count;
	u8 bt_समाप्त_count;
	u8 failure_rts;
	u8 failure_frame;
	__le32 initial_rate;
	__le16 wireless_media_समय;

	u8 pa_status;
	u8 pa_पूर्णांकeg_res_a[3];
	u8 pa_पूर्णांकeg_res_b[3];
	u8 pa_पूर्णांकeg_res_c[3];
	__le16 measurement_req_id;
	u8 reduced_tpc;
	u8 reserved;

	__le32 tfd_info;
	__le16 seq_ctl;
	__le16 byte_cnt;
	u8 tlc_info;
	u8 ra_tid;
	__le16 frame_ctrl;
	काष्ठा agg_tx_status status[];
पूर्ण __packed; /* TX_RSP_API_S_VER_3 */

/**
 * काष्ठा iwl_mvm_tx_resp - notअगरies that fw is TXing a packet
 * ( REPLY_TX = 0x1c )
 * @frame_count: 1 no aggregation, >1 aggregation
 * @bt_समाप्त_count: num of बार blocked by bluetooth (unused क्रम agg)
 * @failure_rts: num of failures due to unsuccessful RTS
 * @failure_frame: num failures due to no ACK (unused क्रम agg)
 * @initial_rate: क्रम non-agg: rate of the successful Tx. For agg: rate of the
 *	Tx of all the batch. RATE_MCS_*
 * @wireless_media_समय: क्रम non-agg: RTS + CTS + frame tx attempts समय + ACK.
 *	क्रम agg: RTS + CTS + aggregation tx समय + block-ack समय.
 *	in usec.
 * @pa_status: tx घातer info
 * @pa_पूर्णांकeg_res_a: tx घातer info
 * @pa_पूर्णांकeg_res_b: tx घातer info
 * @pa_पूर्णांकeg_res_c: tx घातer info
 * @measurement_req_id: tx घातer info
 * @reduced_tpc: transmit घातer reduction used
 * @reserved: reserved
 * @tfd_info: TFD inक्रमmation set by the FH
 * @seq_ctl: sequence control from the Tx cmd
 * @byte_cnt: byte count from the Tx cmd
 * @tlc_info: TLC rate info
 * @ra_tid: bits [3:0] = ra, bits [7:4] = tid
 * @frame_ctrl: frame control
 * @tx_queue: TX queue क्रम this response
 * @reserved2: reserved क्रम padding/alignment
 * @status: क्रम non-agg:  frame status TX_STATUS_*
 *	For version 6 TX response isn't received क्रम aggregation at all.
 *
 * After the array of statuses comes the SSN of the SCD. Look at
 * %iwl_mvm_get_scd_ssn क्रम more details.
 */
काष्ठा iwl_mvm_tx_resp अणु
	u8 frame_count;
	u8 bt_समाप्त_count;
	u8 failure_rts;
	u8 failure_frame;
	__le32 initial_rate;
	__le16 wireless_media_समय;

	u8 pa_status;
	u8 pa_पूर्णांकeg_res_a[3];
	u8 pa_पूर्णांकeg_res_b[3];
	u8 pa_पूर्णांकeg_res_c[3];
	__le16 measurement_req_id;
	u8 reduced_tpc;
	u8 reserved;

	__le32 tfd_info;
	__le16 seq_ctl;
	__le16 byte_cnt;
	u8 tlc_info;
	u8 ra_tid;
	__le16 frame_ctrl;
	__le16 tx_queue;
	__le16 reserved2;
	काष्ठा agg_tx_status status;
पूर्ण __packed; /* TX_RSP_API_S_VER_6 */

/**
 * काष्ठा iwl_mvm_ba_notअगर - notअगरies about reception of BA
 * ( BA_NOTIF = 0xc5 )
 * @sta_addr: MAC address
 * @reserved: reserved
 * @sta_id: Index of recipient (BA-sending) station in fw's station table
 * @tid: tid of the session
 * @seq_ctl: sequence control field
 * @biपंचांगap: the biपंचांगap of the BA notअगरication as seen in the air
 * @scd_flow: the tx queue this BA relates to
 * @scd_ssn: the index of the last contiguously sent packet
 * @txed: number of Txed frames in this batch
 * @txed_2_करोne: number of Acked frames in this batch
 * @reduced_txp: घातer reduced according to TPC. This is the actual value and
 *	not a copy from the LQ command. Thus, अगर not the first rate was used
 *	क्रम Tx-ing then this value will be set to 0 by FW.
 * @reserved1: reserved
 */
काष्ठा iwl_mvm_ba_notअगर अणु
	u8 sta_addr[ETH_ALEN];
	__le16 reserved;

	u8 sta_id;
	u8 tid;
	__le16 seq_ctl;
	__le64 biपंचांगap;
	__le16 scd_flow;
	__le16 scd_ssn;
	u8 txed;
	u8 txed_2_करोne;
	u8 reduced_txp;
	u8 reserved1;
पूर्ण __packed;

/**
 * काष्ठा iwl_mvm_compressed_ba_tfd - progress of a TFD queue
 * @q_num: TFD queue number
 * @tfd_index: Index of first un-acked frame in the  TFD queue
 * @scd_queue: For debug only - the physical queue the TFD queue is bound to
 * @tid: TID of the queue (0-7)
 * @reserved: reserved क्रम alignment
 */
काष्ठा iwl_mvm_compressed_ba_tfd अणु
	__le16 q_num;
	__le16 tfd_index;
	u8 scd_queue;
	u8 tid;
	u8 reserved[2];
पूर्ण __packed; /* COMPRESSED_BA_TFD_API_S_VER_1 */

/**
 * काष्ठा iwl_mvm_compressed_ba_ratid - progress of a RA TID queue
 * @q_num: RA TID queue number
 * @tid: TID of the queue
 * @ssn: BA winकरोw current SSN
 */
काष्ठा iwl_mvm_compressed_ba_ratid अणु
	u8 q_num;
	u8 tid;
	__le16 ssn;
पूर्ण __packed; /* COMPRESSED_BA_RATID_API_S_VER_1 */

/*
 * क्रमागत iwl_mvm_ba_resp_flags - TX aggregation status
 * @IWL_MVM_BA_RESP_TX_AGG: generated due to BA
 * @IWL_MVM_BA_RESP_TX_BAR: generated due to BA after BAR
 * @IWL_MVM_BA_RESP_TX_AGG_FAIL: aggregation didn't receive BA
 * @IWL_MVM_BA_RESP_TX_UNDERRUN: aggregation got underrun
 * @IWL_MVM_BA_RESP_TX_BT_KILL: aggregation got BT-समाप्त
 * @IWL_MVM_BA_RESP_TX_DSP_TIMEOUT: aggregation didn't finish within the
 *	expected समय
 */
क्रमागत iwl_mvm_ba_resp_flags अणु
	IWL_MVM_BA_RESP_TX_AGG,
	IWL_MVM_BA_RESP_TX_BAR,
	IWL_MVM_BA_RESP_TX_AGG_FAIL,
	IWL_MVM_BA_RESP_TX_UNDERRUN,
	IWL_MVM_BA_RESP_TX_BT_KILL,
	IWL_MVM_BA_RESP_TX_DSP_TIMEOUT
पूर्ण;

/**
 * काष्ठा iwl_mvm_compressed_ba_notअगर - notअगरies about reception of BA
 * ( BA_NOTIF = 0xc5 )
 * @flags: status flag, see the &iwl_mvm_ba_resp_flags
 * @sta_id: Index of recipient (BA-sending) station in fw's station table
 * @reduced_txp: घातer reduced according to TPC. This is the actual value and
 *	not a copy from the LQ command. Thus, अगर not the first rate was used
 *	क्रम Tx-ing then this value will be set to 0 by FW.
 * @tlc_rate_info: TLC rate info, initial rate index, TLC table color
 * @retry_cnt: retry count
 * @query_byte_cnt: SCD query byte count
 * @query_frame_cnt: SCD query frame count
 * @txed: number of frames sent in the aggregation (all-TIDs)
 * @करोne: number of frames that were Acked by the BA (all-TIDs)
 * @reserved: reserved (क्रम alignment)
 * @wireless_समय: Wireless-media समय
 * @tx_rate: the rate the aggregation was sent at
 * @tfd_cnt: number of TFD-Q elements
 * @ra_tid_cnt: number of RATID-Q elements
 * @tfd: array of TFD queue status updates. See &iwl_mvm_compressed_ba_tfd
 *	क्रम details. Length in @tfd_cnt.
 * @ra_tid: array of RA-TID queue status updates. For debug purposes only. See
 *	&iwl_mvm_compressed_ba_ratid क्रम more details. Length in @ra_tid_cnt.
 */
काष्ठा iwl_mvm_compressed_ba_notअगर अणु
	__le32 flags;
	u8 sta_id;
	u8 reduced_txp;
	u8 tlc_rate_info;
	u8 retry_cnt;
	__le32 query_byte_cnt;
	__le16 query_frame_cnt;
	__le16 txed;
	__le16 करोne;
	__le16 reserved;
	__le32 wireless_समय;
	__le32 tx_rate;
	__le16 tfd_cnt;
	__le16 ra_tid_cnt;
	काष्ठा iwl_mvm_compressed_ba_ratid ra_tid[0];
	काष्ठा iwl_mvm_compressed_ba_tfd tfd[];
पूर्ण __packed; /* COMPRESSED_BA_RES_API_S_VER_4 */

/**
 * काष्ठा iwl_mac_beacon_cmd_v6 - beacon ढाँचा command
 * @tx: the tx commands associated with the beacon frame
 * @ढाँचा_id: currently equal to the mac context id of the coresponding
 *  mac.
 * @tim_idx: the offset of the tim IE in the beacon
 * @tim_size: the length of the tim IE
 * @frame: the ढाँचा of the beacon frame
 */
काष्ठा iwl_mac_beacon_cmd_v6 अणु
	काष्ठा iwl_tx_cmd tx;
	__le32 ढाँचा_id;
	__le32 tim_idx;
	__le32 tim_size;
	काष्ठा ieee80211_hdr frame[];
पूर्ण __packed; /* BEACON_TEMPLATE_CMD_API_S_VER_6 */

/**
 * काष्ठा iwl_mac_beacon_cmd_v7 - beacon ढाँचा command with offloaded CSA
 * @tx: the tx commands associated with the beacon frame
 * @ढाँचा_id: currently equal to the mac context id of the coresponding
 *  mac.
 * @tim_idx: the offset of the tim IE in the beacon
 * @tim_size: the length of the tim IE
 * @ecsa_offset: offset to the ECSA IE अगर present
 * @csa_offset: offset to the CSA IE अगर present
 * @frame: the ढाँचा of the beacon frame
 */
काष्ठा iwl_mac_beacon_cmd_v7 अणु
	काष्ठा iwl_tx_cmd tx;
	__le32 ढाँचा_id;
	__le32 tim_idx;
	__le32 tim_size;
	__le32 ecsa_offset;
	__le32 csa_offset;
	काष्ठा ieee80211_hdr frame[];
पूर्ण __packed; /* BEACON_TEMPLATE_CMD_API_S_VER_7 */

क्रमागत iwl_mac_beacon_flags अणु
	IWL_MAC_BEACON_CCK	= BIT(8),
	IWL_MAC_BEACON_ANT_A	= BIT(9),
	IWL_MAC_BEACON_ANT_B	= BIT(10),
	IWL_MAC_BEACON_ANT_C	= BIT(11),
	IWL_MAC_BEACON_FILS	= BIT(12),
पूर्ण;

/**
 * काष्ठा iwl_mac_beacon_cmd - beacon ढाँचा command with offloaded CSA
 * @byte_cnt: byte count of the beacon frame.
 * @flags: least signअगरicant byte क्रम rate code. The most signअगरicant byte
 *	is &क्रमागत iwl_mac_beacon_flags.
 * @लघु_ssid: Short SSID
 * @reserved: reserved
 * @ढाँचा_id: currently equal to the mac context id of the coresponding mac.
 * @tim_idx: the offset of the tim IE in the beacon
 * @tim_size: the length of the tim IE
 * @ecsa_offset: offset to the ECSA IE अगर present
 * @csa_offset: offset to the CSA IE अगर present
 * @frame: the ढाँचा of the beacon frame
 */
काष्ठा iwl_mac_beacon_cmd अणु
	__le16 byte_cnt;
	__le16 flags;
	__le32 लघु_ssid;
	__le32 reserved;
	__le32 ढाँचा_id;
	__le32 tim_idx;
	__le32 tim_size;
	__le32 ecsa_offset;
	__le32 csa_offset;
	काष्ठा ieee80211_hdr frame[];
पूर्ण __packed; /* BEACON_TEMPLATE_CMD_API_S_VER_10 */

काष्ठा iwl_beacon_notअगर अणु
	काष्ठा iwl_mvm_tx_resp beacon_notअगरy_hdr;
	__le64 tsf;
	__le32 ibss_mgr_status;
पूर्ण __packed;

/**
 * काष्ठा iwl_extended_beacon_notअगर_v5 - notअगरies about beacon transmission
 * @beacon_notअगरy_hdr: tx response command associated with the beacon
 * @tsf: last beacon tsf
 * @ibss_mgr_status: whether IBSS is manager
 * @gp2: last beacon समय in gp2
 */
काष्ठा iwl_extended_beacon_notअगर_v5 अणु
	काष्ठा iwl_mvm_tx_resp beacon_notअगरy_hdr;
	__le64 tsf;
	__le32 ibss_mgr_status;
	__le32 gp2;
पूर्ण __packed; /* BEACON_NTFY_API_S_VER_5 */

/**
 * काष्ठा iwl_extended_beacon_notअगर - notअगरies about beacon transmission
 * @status: the status of the Tx response of the beacon
 * @tsf: last beacon tsf
 * @ibss_mgr_status: whether IBSS is manager
 * @gp2: last beacon समय in gp2
 */
काष्ठा iwl_extended_beacon_notअगर अणु
	__le32 status;
	__le64 tsf;
	__le32 ibss_mgr_status;
	__le32 gp2;
पूर्ण __packed; /* BEACON_NTFY_API_S_VER_6_ */

/**
 * क्रमागत iwl_dump_control - dump (flush) control flags
 * @DUMP_TX_FIFO_FLUSH: Dump MSDUs until the the FIFO is empty
 *	and the TFD queues are empty.
 */
क्रमागत iwl_dump_control अणु
	DUMP_TX_FIFO_FLUSH	= BIT(1),
पूर्ण;

/**
 * काष्ठा iwl_tx_path_flush_cmd -- queue/FIFO flush command
 * @queues_ctl: biपंचांगap of queues to flush
 * @flush_ctl: control flags
 * @reserved: reserved
 */
काष्ठा iwl_tx_path_flush_cmd_v1 अणु
	__le32 queues_ctl;
	__le16 flush_ctl;
	__le16 reserved;
पूर्ण __packed; /* TX_PATH_FLUSH_CMD_API_S_VER_1 */

/**
 * काष्ठा iwl_tx_path_flush_cmd -- queue/FIFO flush command
 * @sta_id: station ID to flush
 * @tid_mask: TID mask to flush
 * @reserved: reserved
 */
काष्ठा iwl_tx_path_flush_cmd अणु
	__le32 sta_id;
	__le16 tid_mask;
	__le16 reserved;
पूर्ण __packed; /* TX_PATH_FLUSH_CMD_API_S_VER_2 */

#घोषणा IWL_TX_FLUSH_QUEUE_RSP 16

/**
 * काष्ठा iwl_flush_queue_info - भव flush queue info
 * @queue_num: भव queue id
 * @पढ़ो_beक्रमe_flush: पढ़ो poपूर्णांकer beक्रमe flush
 * @पढ़ो_after_flush: पढ़ो poपूर्णांकer after flush
 */
काष्ठा iwl_flush_queue_info अणु
	__le16 tid;
	__le16 queue_num;
	__le16 पढ़ो_beक्रमe_flush;
	__le16 पढ़ो_after_flush;
पूर्ण __packed; /* TFDQ_FLUSH_INFO_API_S_VER_1 */

/**
 * काष्ठा iwl_tx_path_flush_cmd_rsp -- queue/FIFO flush command response
 * @num_flushed_queues: number of queues in queues array
 * @queues: all flushed queues
 */
काष्ठा iwl_tx_path_flush_cmd_rsp अणु
	__le16 sta_id;
	__le16 num_flushed_queues;
	काष्ठा iwl_flush_queue_info queues[IWL_TX_FLUSH_QUEUE_RSP];
पूर्ण __packed; /* TX_PATH_FLUSH_CMD_RSP_API_S_VER_1 */

/* Available options क्रम the SCD_QUEUE_CFG HCMD */
क्रमागत iwl_scd_cfg_actions अणु
	SCD_CFG_DISABLE_QUEUE		= 0x0,
	SCD_CFG_ENABLE_QUEUE		= 0x1,
	SCD_CFG_UPDATE_QUEUE_TID	= 0x2,
पूर्ण;

/**
 * काष्ठा iwl_scd_txq_cfg_cmd - New txq hw scheduler config command
 * @token: unused
 * @sta_id: station id
 * @tid: TID
 * @scd_queue: scheduler queue to confiug
 * @action: 1 queue enable, 0 queue disable, 2 change txq's tid owner
 *	Value is one of &क्रमागत iwl_scd_cfg_actions options
 * @aggregate: 1 aggregated queue, 0 otherwise
 * @tx_fअगरo: &क्रमागत iwl_mvm_tx_fअगरo
 * @winकरोw: BA winकरोw size
 * @ssn: SSN क्रम the BA agreement
 * @reserved: reserved
 */
काष्ठा iwl_scd_txq_cfg_cmd अणु
	u8 token;
	u8 sta_id;
	u8 tid;
	u8 scd_queue;
	u8 action;
	u8 aggregate;
	u8 tx_fअगरo;
	u8 winकरोw;
	__le16 ssn;
	__le16 reserved;
पूर्ण __packed; /* SCD_QUEUE_CFG_CMD_API_S_VER_1 */

/**
 * काष्ठा iwl_scd_txq_cfg_rsp
 * @token: taken from the command
 * @sta_id: station id from the command
 * @tid: tid from the command
 * @scd_queue: scd_queue from the command
 */
काष्ठा iwl_scd_txq_cfg_rsp अणु
	u8 token;
	u8 sta_id;
	u8 tid;
	u8 scd_queue;
पूर्ण __packed; /* SCD_QUEUE_CFG_RSP_API_S_VER_1 */

#पूर्ण_अगर /* __iwl_fw_api_tx_h__ */
