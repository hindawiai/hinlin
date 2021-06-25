<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2010 Broadcom Corporation
 */
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/err.h>
#समावेश <linux/jअगरfies.h>
#समावेश <net/cfg80211.h>

#समावेश <brcmu_utils.h>
#समावेश <brcmu_wअगरi.h>
#समावेश "core.h"
#समावेश "debug.h"
#समावेश "bus.h"
#समावेश "fwil.h"
#समावेश "fwil_types.h"
#समावेश "fweh.h"
#समावेश "fwsignal.h"
#समावेश "p2p.h"
#समावेश "cfg80211.h"
#समावेश "proto.h"
#समावेश "bcdc.h"
#समावेश "common.h"

/**
 * DOC: Firmware Signalling
 *
 * Firmware can send संकेतs to host and vice versa, which are passed in the
 * data packets using TLV based header. This संकेतling layer is on top of the
 * BDC bus protocol layer.
 */

/*
 * single definition क्रम firmware-driver flow control tlv's.
 *
 * each tlv is specअगरied by BRCMF_FWS_TLV_DEF(name, ID, length).
 * A length value 0 indicates variable length tlv.
 */
#घोषणा BRCMF_FWS_TLV_DEFLIST \
	BRCMF_FWS_TLV_DEF(MAC_OPEN, 1, 1) \
	BRCMF_FWS_TLV_DEF(MAC_CLOSE, 2, 1) \
	BRCMF_FWS_TLV_DEF(MAC_REQUEST_CREDIT, 3, 2) \
	BRCMF_FWS_TLV_DEF(TXSTATUS, 4, 4) \
	BRCMF_FWS_TLV_DEF(PKTTAG, 5, 4) \
	BRCMF_FWS_TLV_DEF(MACDESC_ADD,	6, 8) \
	BRCMF_FWS_TLV_DEF(MACDESC_DEL, 7, 8) \
	BRCMF_FWS_TLV_DEF(RSSI, 8, 1) \
	BRCMF_FWS_TLV_DEF(INTERFACE_OPEN, 9, 1) \
	BRCMF_FWS_TLV_DEF(INTERFACE_CLOSE, 10, 1) \
	BRCMF_FWS_TLV_DEF(FIFO_CREDITBACK, 11, 6) \
	BRCMF_FWS_TLV_DEF(PENDING_TRAFFIC_BMP, 12, 2) \
	BRCMF_FWS_TLV_DEF(MAC_REQUEST_PACKET, 13, 3) \
	BRCMF_FWS_TLV_DEF(HOST_REORDER_RXPKTS, 14, 10) \
	BRCMF_FWS_TLV_DEF(TRANS_ID, 18, 6) \
	BRCMF_FWS_TLV_DEF(COMP_TXSTATUS, 19, 1) \
	BRCMF_FWS_TLV_DEF(FILLER, 255, 0)

/*
 * क्रमागत brcmf_fws_tlv_type - definition of tlv identअगरiers.
 */
#घोषणा BRCMF_FWS_TLV_DEF(name, id, len) \
	BRCMF_FWS_TYPE_ ## name =  id,
क्रमागत brcmf_fws_tlv_type अणु
	BRCMF_FWS_TLV_DEFLIST
	BRCMF_FWS_TYPE_INVALID
पूर्ण;
#अघोषित BRCMF_FWS_TLV_DEF

/*
 * क्रमागत brcmf_fws_tlv_len - definition of tlv lengths.
 */
#घोषणा BRCMF_FWS_TLV_DEF(name, id, len) \
	BRCMF_FWS_TYPE_ ## name ## _LEN = (len),
क्रमागत brcmf_fws_tlv_len अणु
	BRCMF_FWS_TLV_DEFLIST
पूर्ण;
#अघोषित BRCMF_FWS_TLV_DEF

/* AMPDU rx reordering definitions */
#घोषणा BRCMF_RXREORDER_FLOWID_OFFSET		0
#घोषणा BRCMF_RXREORDER_MAXIDX_OFFSET		2
#घोषणा BRCMF_RXREORDER_FLAGS_OFFSET		4
#घोषणा BRCMF_RXREORDER_CURIDX_OFFSET		6
#घोषणा BRCMF_RXREORDER_EXPIDX_OFFSET		8

#घोषणा BRCMF_RXREORDER_DEL_FLOW		0x01
#घोषणा BRCMF_RXREORDER_FLUSH_ALL		0x02
#घोषणा BRCMF_RXREORDER_CURIDX_VALID		0x04
#घोषणा BRCMF_RXREORDER_EXPIDX_VALID		0x08
#घोषणा BRCMF_RXREORDER_NEW_HOLE		0x10

#अगर_घोषित DEBUG
/*
 * brcmf_fws_tlv_names - array of tlv names.
 */
#घोषणा BRCMF_FWS_TLV_DEF(name, id, len) \
	अणु id, #name पूर्ण,
अटल काष्ठा अणु
	क्रमागत brcmf_fws_tlv_type id;
	स्थिर अक्षर *name;
पूर्ण brcmf_fws_tlv_names[] = अणु
	BRCMF_FWS_TLV_DEFLIST
पूर्ण;
#अघोषित BRCMF_FWS_TLV_DEF


अटल स्थिर अक्षर *brcmf_fws_get_tlv_name(क्रमागत brcmf_fws_tlv_type id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(brcmf_fws_tlv_names); i++)
		अगर (brcmf_fws_tlv_names[i].id == id)
			वापस brcmf_fws_tlv_names[i].name;

	वापस "INVALID";
पूर्ण
#अन्यथा
अटल स्थिर अक्षर *brcmf_fws_get_tlv_name(क्रमागत brcmf_fws_tlv_type id)
अणु
	वापस "NODEBUG";
पूर्ण
#पूर्ण_अगर /* DEBUG */

/*
 * The PKTTAG tlv has additional bytes when firmware-संकेतling
 * mode has REUSESEQ flag set.
 */
#घोषणा BRCMF_FWS_TYPE_SEQ_LEN				2

/*
 * flags used to enable tlv संकेतling from firmware.
 */
#घोषणा BRCMF_FWS_FLAGS_RSSI_SIGNALS			0x0001
#घोषणा BRCMF_FWS_FLAGS_XONXOFF_SIGNALS			0x0002
#घोषणा BRCMF_FWS_FLAGS_CREDIT_STATUS_SIGNALS		0x0004
#घोषणा BRCMF_FWS_FLAGS_HOST_PROPTXSTATUS_ACTIVE	0x0008
#घोषणा BRCMF_FWS_FLAGS_PSQ_GENERATIONFSM_ENABLE	0x0010
#घोषणा BRCMF_FWS_FLAGS_PSQ_ZERO_BUFFER_ENABLE		0x0020
#घोषणा BRCMF_FWS_FLAGS_HOST_RXREORDER_ACTIVE		0x0040

#घोषणा BRCMF_FWS_MAC_DESC_TABLE_SIZE			32
#घोषणा BRCMF_FWS_MAC_DESC_ID_INVALID			0xff

#घोषणा BRCMF_FWS_HOSTIF_FLOWSTATE_OFF			0
#घोषणा BRCMF_FWS_HOSTIF_FLOWSTATE_ON			1
#घोषणा BRCMF_FWS_FLOWCONTROL_HIWATER			128
#घोषणा BRCMF_FWS_FLOWCONTROL_LOWATER			64

#घोषणा BRCMF_FWS_PSQ_PREC_COUNT		((BRCMF_FWS_FIFO_COUNT + 1) * 2)
#घोषणा BRCMF_FWS_PSQ_LEN				256

#घोषणा BRCMF_FWS_HTOD_FLAG_PKTFROMHOST			0x01
#घोषणा BRCMF_FWS_HTOD_FLAG_PKT_REQUESTED		0x02

#घोषणा BRCMF_FWS_RET_OK_NOSCHEDULE			0
#घोषणा BRCMF_FWS_RET_OK_SCHEDULE			1

#घोषणा BRCMF_FWS_MODE_REUSESEQ_SHIFT			3	/* seq reuse */
#घोषणा BRCMF_FWS_MODE_SET_REUSESEQ(x, val)	((x) = \
		((x) & ~(1 << BRCMF_FWS_MODE_REUSESEQ_SHIFT)) | \
		(((val) & 1) << BRCMF_FWS_MODE_REUSESEQ_SHIFT))
#घोषणा BRCMF_FWS_MODE_GET_REUSESEQ(x)	\
		(((x) >> BRCMF_FWS_MODE_REUSESEQ_SHIFT) & 1)

/**
 * क्रमागत brcmf_fws_skb_state - indicates processing state of skb.
 *
 * @BRCMF_FWS_SKBSTATE_NEW: sk_buff is newly arrived in the driver.
 * @BRCMF_FWS_SKBSTATE_DELAYED: sk_buff had to रुको on queue.
 * @BRCMF_FWS_SKBSTATE_SUPPRESSED: sk_buff has been suppressed by firmware.
 * @BRCMF_FWS_SKBSTATE_TIM: allocated क्रम TIM update info.
 */
क्रमागत brcmf_fws_skb_state अणु
	BRCMF_FWS_SKBSTATE_NEW,
	BRCMF_FWS_SKBSTATE_DELAYED,
	BRCMF_FWS_SKBSTATE_SUPPRESSED,
	BRCMF_FWS_SKBSTATE_TIM
पूर्ण;

/**
 * काष्ठा brcmf_skbuff_cb - control buffer associated with skbuff.
 *
 * @bus_flags: 2 bytes reserved क्रम bus specअगरic parameters
 * @अगर_flags: holds पूर्णांकerface index and packet related flags.
 * @htod: host to device packet identअगरier (used in PKTTAG tlv).
 * @htod_seq: this 16-bit is original seq number क्रम every suppress packet.
 * @state: transmit state of the packet.
 * @mac: descriptor related to destination क्रम this packet.
 *
 * This inक्रमmation is stored in control buffer काष्ठा sk_buff::cb, which
 * provides 48 bytes of storage so this काष्ठाure should not exceed that.
 */
काष्ठा brcmf_skbuff_cb अणु
	u16 bus_flags;
	u16 अगर_flags;
	u32 htod;
	u16 htod_seq;
	क्रमागत brcmf_fws_skb_state state;
	काष्ठा brcmf_fws_mac_descriptor *mac;
पूर्ण;

/*
 * macro casting skbuff control buffer to काष्ठा brcmf_skbuff_cb.
 */
#घोषणा brcmf_skbcb(skb)	((काष्ठा brcmf_skbuff_cb *)((skb)->cb))

/*
 * sk_buff control अगर flags
 *
 *	b[11]  - packet sent upon firmware request.
 *	b[10]  - packet only contains संकेतling data.
 *	b[9]   - packet is a tx packet.
 *	b[8]   - packet used requested credit
 *	b[7]   - पूर्णांकerface in AP mode.
 *	b[3:0] - पूर्णांकerface index.
 */
#घोषणा BRCMF_SKB_IF_FLAGS_REQUESTED_MASK	0x0800
#घोषणा BRCMF_SKB_IF_FLAGS_REQUESTED_SHIFT	11
#घोषणा BRCMF_SKB_IF_FLAGS_SIGNAL_ONLY_MASK	0x0400
#घोषणा BRCMF_SKB_IF_FLAGS_SIGNAL_ONLY_SHIFT	10
#घोषणा BRCMF_SKB_IF_FLAGS_TRANSMIT_MASK        0x0200
#घोषणा BRCMF_SKB_IF_FLAGS_TRANSMIT_SHIFT	9
#घोषणा BRCMF_SKB_IF_FLAGS_REQ_CREDIT_MASK	0x0100
#घोषणा BRCMF_SKB_IF_FLAGS_REQ_CREDIT_SHIFT	8
#घोषणा BRCMF_SKB_IF_FLAGS_IF_AP_MASK		0x0080
#घोषणा BRCMF_SKB_IF_FLAGS_IF_AP_SHIFT		7
#घोषणा BRCMF_SKB_IF_FLAGS_INDEX_MASK		0x000f
#घोषणा BRCMF_SKB_IF_FLAGS_INDEX_SHIFT		0

#घोषणा brcmf_skb_अगर_flags_set_field(skb, field, value) \
	brcmu_maskset16(&(brcmf_skbcb(skb)->अगर_flags), \
			BRCMF_SKB_IF_FLAGS_ ## field ## _MASK, \
			BRCMF_SKB_IF_FLAGS_ ## field ## _SHIFT, (value))
#घोषणा brcmf_skb_अगर_flags_get_field(skb, field) \
	brcmu_maskget16(brcmf_skbcb(skb)->अगर_flags, \
			BRCMF_SKB_IF_FLAGS_ ## field ## _MASK, \
			BRCMF_SKB_IF_FLAGS_ ## field ## _SHIFT)

/*
 * sk_buff control packet identअगरier
 *
 * 32-bit packet identअगरier used in PKTTAG tlv from host to करोngle.
 *
 * - Generated at the host (e.g. dhd)
 * - Seen as a generic sequence number by firmware except क्रम the flags field.
 *
 * Generation	: b[31]	=> generation number क्रम this packet [host->fw]
 *			   OR, current generation number [fw->host]
 * Flags	: b[30:27] => command, status flags
 * FIFO-AC	: b[26:24] => AC-FIFO id
 * h-slot	: b[23:8] => hanger-slot
 * मुक्तrun	: b[7:0] => A मुक्त running counter
 */
#घोषणा BRCMF_SKB_HTOD_TAG_GENERATION_MASK		0x80000000
#घोषणा BRCMF_SKB_HTOD_TAG_GENERATION_SHIFT		31
#घोषणा BRCMF_SKB_HTOD_TAG_FLAGS_MASK			0x78000000
#घोषणा BRCMF_SKB_HTOD_TAG_FLAGS_SHIFT			27
#घोषणा BRCMF_SKB_HTOD_TAG_FIFO_MASK			0x07000000
#घोषणा BRCMF_SKB_HTOD_TAG_FIFO_SHIFT			24
#घोषणा BRCMF_SKB_HTOD_TAG_HSLOT_MASK			0x00ffff00
#घोषणा BRCMF_SKB_HTOD_TAG_HSLOT_SHIFT			8
#घोषणा BRCMF_SKB_HTOD_TAG_FREERUN_MASK			0x000000ff
#घोषणा BRCMF_SKB_HTOD_TAG_FREERUN_SHIFT		0

#घोषणा brcmf_skb_htod_tag_set_field(skb, field, value) \
	brcmu_maskset32(&(brcmf_skbcb(skb)->htod), \
			BRCMF_SKB_HTOD_TAG_ ## field ## _MASK, \
			BRCMF_SKB_HTOD_TAG_ ## field ## _SHIFT, (value))
#घोषणा brcmf_skb_htod_tag_get_field(skb, field) \
	brcmu_maskget32(brcmf_skbcb(skb)->htod, \
			BRCMF_SKB_HTOD_TAG_ ## field ## _MASK, \
			BRCMF_SKB_HTOD_TAG_ ## field ## _SHIFT)

#घोषणा BRCMF_SKB_HTOD_SEQ_FROMFW_MASK			0x2000
#घोषणा BRCMF_SKB_HTOD_SEQ_FROMFW_SHIFT			13
#घोषणा BRCMF_SKB_HTOD_SEQ_FROMDRV_MASK			0x1000
#घोषणा BRCMF_SKB_HTOD_SEQ_FROMDRV_SHIFT		12
#घोषणा BRCMF_SKB_HTOD_SEQ_NR_MASK			0x0fff
#घोषणा BRCMF_SKB_HTOD_SEQ_NR_SHIFT			0

#घोषणा brcmf_skb_htod_seq_set_field(skb, field, value) \
	brcmu_maskset16(&(brcmf_skbcb(skb)->htod_seq), \
			BRCMF_SKB_HTOD_SEQ_ ## field ## _MASK, \
			BRCMF_SKB_HTOD_SEQ_ ## field ## _SHIFT, (value))
#घोषणा brcmf_skb_htod_seq_get_field(skb, field) \
	brcmu_maskget16(brcmf_skbcb(skb)->htod_seq, \
			BRCMF_SKB_HTOD_SEQ_ ## field ## _MASK, \
			BRCMF_SKB_HTOD_SEQ_ ## field ## _SHIFT)

#घोषणा BRCMF_FWS_TXSTAT_GENERATION_MASK	0x80000000
#घोषणा BRCMF_FWS_TXSTAT_GENERATION_SHIFT	31
#घोषणा BRCMF_FWS_TXSTAT_FLAGS_MASK		0x78000000
#घोषणा BRCMF_FWS_TXSTAT_FLAGS_SHIFT		27
#घोषणा BRCMF_FWS_TXSTAT_FIFO_MASK		0x07000000
#घोषणा BRCMF_FWS_TXSTAT_FIFO_SHIFT		24
#घोषणा BRCMF_FWS_TXSTAT_HSLOT_MASK		0x00FFFF00
#घोषणा BRCMF_FWS_TXSTAT_HSLOT_SHIFT		8
#घोषणा BRCMF_FWS_TXSTAT_FREERUN_MASK		0x000000FF
#घोषणा BRCMF_FWS_TXSTAT_FREERUN_SHIFT		0

#घोषणा brcmf_txstatus_get_field(txs, field) \
	brcmu_maskget32(txs, BRCMF_FWS_TXSTAT_ ## field ## _MASK, \
			BRCMF_FWS_TXSTAT_ ## field ## _SHIFT)

/* How दीर्घ to defer borrowing in jअगरfies */
#घोषणा BRCMF_FWS_BORROW_DEFER_PERIOD		(HZ / 10)


/**
 * क्रमागत brcmf_fws_txstatus - txstatus flag values.
 *
 * @BRCMF_FWS_TXSTATUS_DISCARD:
 *	host is मुक्त to discard the packet.
 * @BRCMF_FWS_TXSTATUS_CORE_SUPPRESS:
 *	802.11 core suppressed the packet.
 * @BRCMF_FWS_TXSTATUS_FW_PS_SUPPRESS:
 *	firmware suppress the packet as device is alपढ़ोy in PS mode.
 * @BRCMF_FWS_TXSTATUS_FW_TOSSED:
 *	firmware tossed the packet.
 * @BRCMF_FWS_TXSTATUS_FW_DISCARD_NOACK:
 *	firmware tossed the packet after retries.
 * @BRCMF_FWS_TXSTATUS_FW_SUPPRESS_ACKED:
 *	firmware wrongly reported suppressed previously, now fixing to acked.
 * @BRCMF_FWS_TXSTATUS_HOST_TOSSED:
 *	host tossed the packet.
 */
क्रमागत brcmf_fws_txstatus अणु
	BRCMF_FWS_TXSTATUS_DISCARD,
	BRCMF_FWS_TXSTATUS_CORE_SUPPRESS,
	BRCMF_FWS_TXSTATUS_FW_PS_SUPPRESS,
	BRCMF_FWS_TXSTATUS_FW_TOSSED,
	BRCMF_FWS_TXSTATUS_FW_DISCARD_NOACK,
	BRCMF_FWS_TXSTATUS_FW_SUPPRESS_ACKED,
	BRCMF_FWS_TXSTATUS_HOST_TOSSED
पूर्ण;

क्रमागत brcmf_fws_fcmode अणु
	BRCMF_FWS_FCMODE_NONE,
	BRCMF_FWS_FCMODE_IMPLIED_CREDIT,
	BRCMF_FWS_FCMODE_EXPLICIT_CREDIT
पूर्ण;

क्रमागत brcmf_fws_mac_desc_state अणु
	BRCMF_FWS_STATE_OPEN = 1,
	BRCMF_FWS_STATE_CLOSE
पूर्ण;

/**
 * काष्ठा brcmf_fws_mac_descriptor - firmware संकेतling data per node/पूर्णांकerface
 *
 * @name: name of the descriptor.
 * @occupied: slot is in use.
 * @mac_handle: handle क्रम mac entry determined by firmware.
 * @पूर्णांकerface_id: पूर्णांकerface index.
 * @state: current state.
 * @suppressed: mac entry is suppressed.
 * @generation: generation bit.
 * @ac_biपंचांगap: ac queue biपंचांगap.
 * @requested_credit: credits requested by firmware.
 * @requested_packet: packet requested by firmware.
 * @ea: ethernet address.
 * @seq: per-node मुक्त-running sequence.
 * @psq: घातer-save queue.
 * @transit_count: packet in transit to firmware.
 * @suppr_transit_count: suppressed packet in transit to firmware.
 * @send_tim_संकेत: अगर set tim संकेत will be sent.
 * @traffic_pending_bmp: traffic pending biपंचांगap.
 * @traffic_lastreported_bmp: traffic last reported biपंचांगap.
 */
काष्ठा brcmf_fws_mac_descriptor अणु
	अक्षर name[16];
	u8 occupied;
	u8 mac_handle;
	u8 पूर्णांकerface_id;
	u8 state;
	bool suppressed;
	u8 generation;
	u8 ac_biपंचांगap;
	u8 requested_credit;
	u8 requested_packet;
	u8 ea[ETH_ALEN];
	u8 seq[BRCMF_FWS_FIFO_COUNT];
	काष्ठा pktq psq;
	पूर्णांक transit_count;
	पूर्णांक suppr_transit_count;
	bool send_tim_संकेत;
	u8 traffic_pending_bmp;
	u8 traffic_lastreported_bmp;
पूर्ण;

#घोषणा BRCMF_FWS_HANGER_MAXITEMS	3072
#घोषणा BRCMF_BORROW_RATIO			3

/**
 * क्रमागत brcmf_fws_hanger_item_state - state of hanger item.
 *
 * @BRCMF_FWS_HANGER_ITEM_STATE_FREE: item is मुक्त क्रम use.
 * @BRCMF_FWS_HANGER_ITEM_STATE_INUSE: item is in use.
 * @BRCMF_FWS_HANGER_ITEM_STATE_INUSE_SUPPRESSED: item was suppressed.
 */
क्रमागत brcmf_fws_hanger_item_state अणु
	BRCMF_FWS_HANGER_ITEM_STATE_FREE = 1,
	BRCMF_FWS_HANGER_ITEM_STATE_INUSE,
	BRCMF_FWS_HANGER_ITEM_STATE_INUSE_SUPPRESSED
पूर्ण;


/**
 * काष्ठा brcmf_fws_hanger_item - single entry क्रम tx pending packet.
 *
 * @state: entry is either मुक्त or occupied.
 * @pkt: packet itself.
 */
काष्ठा brcmf_fws_hanger_item अणु
	क्रमागत brcmf_fws_hanger_item_state state;
	काष्ठा sk_buff *pkt;
पूर्ण;

/**
 * काष्ठा brcmf_fws_hanger - holds packets aरुकोing firmware txstatus.
 *
 * @pushed: packets pushed to aरुको txstatus.
 * @popped: packets popped upon handling txstatus.
 * @failed_to_push: packets that could not be pushed.
 * @failed_to_pop: packets that could not be popped.
 * @failed_slotfind: packets क्रम which failed to find an entry.
 * @slot_pos: last वापसed item index क्रम a मुक्त entry.
 * @items: array of hanger items.
 */
काष्ठा brcmf_fws_hanger अणु
	u32 pushed;
	u32 popped;
	u32 failed_to_push;
	u32 failed_to_pop;
	u32 failed_slotfind;
	u32 slot_pos;
	काष्ठा brcmf_fws_hanger_item items[BRCMF_FWS_HANGER_MAXITEMS];
पूर्ण;

काष्ठा brcmf_fws_macdesc_table अणु
	काष्ठा brcmf_fws_mac_descriptor nodes[BRCMF_FWS_MAC_DESC_TABLE_SIZE];
	काष्ठा brcmf_fws_mac_descriptor अगरace[BRCMF_MAX_IFS];
	काष्ठा brcmf_fws_mac_descriptor other;
पूर्ण;

काष्ठा brcmf_fws_stats अणु
	u32 tlv_parse_failed;
	u32 tlv_invalid_type;
	u32 header_only_pkt;
	u32 header_pulls;
	u32 pkt2bus;
	u32 send_pkts[5];
	u32 requested_sent[5];
	u32 generic_error;
	u32 mac_update_failed;
	u32 mac_ps_update_failed;
	u32 अगर_update_failed;
	u32 packet_request_failed;
	u32 credit_request_failed;
	u32 rollback_success;
	u32 rollback_failed;
	u32 delayq_full_error;
	u32 supprq_full_error;
	u32 txs_indicate;
	u32 txs_discard;
	u32 txs_supp_core;
	u32 txs_supp_ps;
	u32 txs_tossed;
	u32 txs_host_tossed;
	u32 bus_flow_block;
	u32 fws_flow_block;
पूर्ण;

काष्ठा brcmf_fws_info अणु
	काष्ठा brcmf_pub *drvr;
	spinlock_t spinlock;
	uदीर्घ flags;
	काष्ठा brcmf_fws_stats stats;
	काष्ठा brcmf_fws_hanger hanger;
	क्रमागत brcmf_fws_fcmode fcmode;
	bool fw_संकेतs;
	bool bcmc_credit_check;
	काष्ठा brcmf_fws_macdesc_table desc;
	काष्ठा workqueue_काष्ठा *fws_wq;
	काष्ठा work_काष्ठा fws_dequeue_work;
	u32 fअगरo_enqpkt[BRCMF_FWS_FIFO_COUNT];
	पूर्णांक fअगरo_credit[BRCMF_FWS_FIFO_COUNT];
	पूर्णांक init_fअगरo_credit[BRCMF_FWS_FIFO_COUNT];
	पूर्णांक credits_borrowed[BRCMF_FWS_FIFO_AC_VO + 1]
		[BRCMF_FWS_FIFO_AC_VO + 1];
	पूर्णांक deq_node_pos[BRCMF_FWS_FIFO_COUNT];
	u32 fअगरo_credit_map;
	u32 fअगरo_delay_map;
	अचिन्हित दीर्घ borrow_defer_बारtamp;
	bool bus_flow_blocked;
	bool crediपंचांगap_received;
	u8 mode;
	bool aव्योम_queueing;
पूर्ण;

#घोषणा BRCMF_FWS_TLV_DEF(name, id, len) \
	हाल BRCMF_FWS_TYPE_ ## name: \
		वापस len;

/**
 * brcmf_fws_get_tlv_len() - वापसs defined length क्रम given tlv id.
 *
 * @fws: firmware-संकेतling inक्रमmation.
 * @id: identअगरier of the TLV.
 *
 * Return: the specअगरied length क्रम the given TLV; Otherwise -EINVAL.
 */
अटल पूर्णांक brcmf_fws_get_tlv_len(काष्ठा brcmf_fws_info *fws,
				 क्रमागत brcmf_fws_tlv_type id)
अणु
	चयन (id) अणु
	BRCMF_FWS_TLV_DEFLIST
	शेष:
		fws->stats.tlv_invalid_type++;
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण
#अघोषित BRCMF_FWS_TLV_DEF

अटल व्योम brcmf_fws_lock(काष्ठा brcmf_fws_info *fws)
		__acquires(&fws->spinlock)
अणु
	spin_lock_irqsave(&fws->spinlock, fws->flags);
पूर्ण

अटल व्योम brcmf_fws_unlock(काष्ठा brcmf_fws_info *fws)
		__releases(&fws->spinlock)
अणु
	spin_unlock_irqrestore(&fws->spinlock, fws->flags);
पूर्ण

अटल bool brcmf_fws_अगरidx_match(काष्ठा sk_buff *skb, व्योम *arg)
अणु
	u32 अगरidx = brcmf_skb_अगर_flags_get_field(skb, INDEX);
	वापस अगरidx == *(पूर्णांक *)arg;
पूर्ण

अटल व्योम brcmf_fws_hanger_init(काष्ठा brcmf_fws_hanger *hanger)
अणु
	पूर्णांक i;

	स_रखो(hanger, 0, माप(*hanger));
	क्रम (i = 0; i < ARRAY_SIZE(hanger->items); i++)
		hanger->items[i].state = BRCMF_FWS_HANGER_ITEM_STATE_FREE;
पूर्ण

अटल u32 brcmf_fws_hanger_get_मुक्त_slot(काष्ठा brcmf_fws_hanger *h)
अणु
	u32 i;

	i = (h->slot_pos + 1) % BRCMF_FWS_HANGER_MAXITEMS;

	जबतक (i != h->slot_pos) अणु
		अगर (h->items[i].state == BRCMF_FWS_HANGER_ITEM_STATE_FREE) अणु
			h->slot_pos = i;
			जाओ करोne;
		पूर्ण
		i++;
		अगर (i == BRCMF_FWS_HANGER_MAXITEMS)
			i = 0;
	पूर्ण
	brcmf_err("all slots occupied\n");
	h->failed_slotfind++;
	i = BRCMF_FWS_HANGER_MAXITEMS;
करोne:
	वापस i;
पूर्ण

अटल पूर्णांक brcmf_fws_hanger_pushpkt(काष्ठा brcmf_fws_hanger *h,
				    काष्ठा sk_buff *pkt, u32 slot_id)
अणु
	अगर (slot_id >= BRCMF_FWS_HANGER_MAXITEMS)
		वापस -ENOENT;

	अगर (h->items[slot_id].state != BRCMF_FWS_HANGER_ITEM_STATE_FREE) अणु
		brcmf_err("slot is not free\n");
		h->failed_to_push++;
		वापस -EINVAL;
	पूर्ण

	h->items[slot_id].state = BRCMF_FWS_HANGER_ITEM_STATE_INUSE;
	h->items[slot_id].pkt = pkt;
	h->pushed++;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक brcmf_fws_hanger_poppkt(काष्ठा brcmf_fws_hanger *h,
					  u32 slot_id, काष्ठा sk_buff **pktout,
					  bool हटाओ_item)
अणु
	अगर (slot_id >= BRCMF_FWS_HANGER_MAXITEMS)
		वापस -ENOENT;

	अगर (h->items[slot_id].state == BRCMF_FWS_HANGER_ITEM_STATE_FREE) अणु
		brcmf_err("entry not in use\n");
		h->failed_to_pop++;
		वापस -EINVAL;
	पूर्ण

	*pktout = h->items[slot_id].pkt;
	अगर (हटाओ_item) अणु
		h->items[slot_id].state = BRCMF_FWS_HANGER_ITEM_STATE_FREE;
		h->items[slot_id].pkt = शून्य;
		h->popped++;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम brcmf_fws_psq_flush(काष्ठा brcmf_fws_info *fws, काष्ठा pktq *q,
				पूर्णांक अगरidx)
अणु
	काष्ठा brcmf_fws_hanger_item *hi;
	bool (*matchfn)(काष्ठा sk_buff *, व्योम *) = शून्य;
	काष्ठा sk_buff *skb;
	पूर्णांक prec;
	u32 hslot;

	अगर (अगरidx != -1)
		matchfn = brcmf_fws_अगरidx_match;
	क्रम (prec = 0; prec < q->num_prec; prec++) अणु
		skb = brcmu_pktq_pdeq_match(q, prec, matchfn, &अगरidx);
		जबतक (skb) अणु
			hslot = brcmf_skb_htod_tag_get_field(skb, HSLOT);
			hi = &fws->hanger.items[hslot];
			WARN_ON(skb != hi->pkt);
			hi->state = BRCMF_FWS_HANGER_ITEM_STATE_FREE;
			brcmf_fws_hanger_poppkt(&fws->hanger, hslot, &skb,
						true);
			brcmu_pkt_buf_मुक्त_skb(skb);
			skb = brcmu_pktq_pdeq_match(q, prec, matchfn, &अगरidx);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक brcmf_fws_hanger_mark_suppressed(काष्ठा brcmf_fws_hanger *h,
					    u32 slot_id)
अणु
	अगर (slot_id >= BRCMF_FWS_HANGER_MAXITEMS)
		वापस -ENOENT;

	अगर (h->items[slot_id].state == BRCMF_FWS_HANGER_ITEM_STATE_FREE) अणु
		brcmf_err("entry not in use\n");
		वापस -EINVAL;
	पूर्ण

	h->items[slot_id].state = BRCMF_FWS_HANGER_ITEM_STATE_INUSE_SUPPRESSED;
	वापस 0;
पूर्ण

अटल व्योम brcmf_fws_hanger_cleanup(काष्ठा brcmf_fws_info *fws,
				     bool (*fn)(काष्ठा sk_buff *, व्योम *),
				     पूर्णांक अगरidx)
अणु
	काष्ठा brcmf_fws_hanger *h = &fws->hanger;
	काष्ठा sk_buff *skb;
	पूर्णांक i;
	क्रमागत brcmf_fws_hanger_item_state s;

	क्रम (i = 0; i < ARRAY_SIZE(h->items); i++) अणु
		s = h->items[i].state;
		अगर (s == BRCMF_FWS_HANGER_ITEM_STATE_INUSE ||
		    s == BRCMF_FWS_HANGER_ITEM_STATE_INUSE_SUPPRESSED) अणु
			skb = h->items[i].pkt;
			अगर (fn == शून्य || fn(skb, &अगरidx)) अणु
				/* suppress packets मुक्तd from psq */
				अगर (s == BRCMF_FWS_HANGER_ITEM_STATE_INUSE)
					brcmu_pkt_buf_मुक्त_skb(skb);
				h->items[i].state =
					BRCMF_FWS_HANGER_ITEM_STATE_FREE;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम brcmf_fws_macdesc_set_name(काष्ठा brcmf_fws_info *fws,
				       काष्ठा brcmf_fws_mac_descriptor *desc)
अणु
	अगर (desc == &fws->desc.other)
		strlcpy(desc->name, "MAC-OTHER", माप(desc->name));
	अन्यथा अगर (desc->mac_handle)
		scnम_लिखो(desc->name, माप(desc->name), "MAC-%d:%d",
			  desc->mac_handle, desc->पूर्णांकerface_id);
	अन्यथा
		scnम_लिखो(desc->name, माप(desc->name), "MACIF:%d",
			  desc->पूर्णांकerface_id);
पूर्ण

अटल व्योम brcmf_fws_macdesc_init(काष्ठा brcmf_fws_mac_descriptor *desc,
				   u8 *addr, u8 अगरidx)
अणु
	brcmf_dbg(TRACE,
		  "enter: desc %p ea=%pM, ifidx=%u\n", desc, addr, अगरidx);
	desc->occupied = 1;
	desc->state = BRCMF_FWS_STATE_OPEN;
	desc->requested_credit = 0;
	desc->requested_packet = 0;
	/* depending on use may need अगरp->bsscfgidx instead */
	desc->पूर्णांकerface_id = अगरidx;
	desc->ac_biपंचांगap = 0xff; /* update this when handling APSD */
	अगर (addr)
		स_नकल(&desc->ea[0], addr, ETH_ALEN);
पूर्ण

अटल
व्योम brcmf_fws_macdesc_deinit(काष्ठा brcmf_fws_mac_descriptor *desc)
अणु
	brcmf_dbg(TRACE,
		  "enter: ea=%pM, ifidx=%u\n", desc->ea, desc->पूर्णांकerface_id);
	desc->occupied = 0;
	desc->state = BRCMF_FWS_STATE_CLOSE;
	desc->requested_credit = 0;
	desc->requested_packet = 0;
पूर्ण

अटल काष्ठा brcmf_fws_mac_descriptor *
brcmf_fws_macdesc_lookup(काष्ठा brcmf_fws_info *fws, u8 *ea)
अणु
	काष्ठा brcmf_fws_mac_descriptor *entry;
	पूर्णांक i;

	अगर (ea == शून्य)
		वापस ERR_PTR(-EINVAL);

	entry = &fws->desc.nodes[0];
	क्रम (i = 0; i < ARRAY_SIZE(fws->desc.nodes); i++) अणु
		अगर (entry->occupied && !स_भेद(entry->ea, ea, ETH_ALEN))
			वापस entry;
		entry++;
	पूर्ण

	वापस ERR_PTR(-ENOENT);
पूर्ण

अटल काष्ठा brcmf_fws_mac_descriptor*
brcmf_fws_macdesc_find(काष्ठा brcmf_fws_info *fws, काष्ठा brcmf_अगर *अगरp, u8 *da)
अणु
	काष्ठा brcmf_fws_mac_descriptor *entry;
	bool multicast;

	multicast = is_multicast_ether_addr(da);

	/* Multicast destination, STA and P2P clients get the पूर्णांकerface entry.
	 * STA/GC माला_लो the Mac Entry क्रम TDLS destinations, TDLS destinations
	 * have their own entry.
	 */
	अगर (multicast && अगरp->fws_desc) अणु
		entry = अगरp->fws_desc;
		जाओ करोne;
	पूर्ण

	entry = brcmf_fws_macdesc_lookup(fws, da);
	अगर (IS_ERR(entry))
		entry = अगरp->fws_desc;

करोne:
	वापस entry;
पूर्ण

अटल bool brcmf_fws_macdesc_बंदd(काष्ठा brcmf_fws_info *fws,
				     काष्ठा brcmf_fws_mac_descriptor *entry,
				     पूर्णांक fअगरo)
अणु
	काष्ठा brcmf_fws_mac_descriptor *अगर_entry;
	bool बंदd;

	/* क्रम unique destination entries the related पूर्णांकerface
	 * may be बंदd.
	 */
	अगर (entry->mac_handle) अणु
		अगर_entry = &fws->desc.अगरace[entry->पूर्णांकerface_id];
		अगर (अगर_entry->state == BRCMF_FWS_STATE_CLOSE)
			वापस true;
	पूर्ण
	/* an entry is बंदd when the state is बंदd and
	 * the firmware did not request anything.
	 */
	बंदd = entry->state == BRCMF_FWS_STATE_CLOSE &&
		 !entry->requested_credit && !entry->requested_packet;

	/* Or firmware करोes not allow traffic क्रम given fअगरo */
	वापस बंदd || !(entry->ac_biपंचांगap & BIT(fअगरo));
पूर्ण

अटल व्योम brcmf_fws_macdesc_cleanup(काष्ठा brcmf_fws_info *fws,
				      काष्ठा brcmf_fws_mac_descriptor *entry,
				      पूर्णांक अगरidx)
अणु
	अगर (entry->occupied && (अगरidx == -1 || अगरidx == entry->पूर्णांकerface_id)) अणु
		brcmf_fws_psq_flush(fws, &entry->psq, अगरidx);
		entry->occupied = !!(entry->psq.len);
	पूर्ण
पूर्ण

अटल व्योम brcmf_fws_bus_txq_cleanup(काष्ठा brcmf_fws_info *fws,
				      bool (*fn)(काष्ठा sk_buff *, व्योम *),
				      पूर्णांक अगरidx)
अणु
	काष्ठा brcmf_fws_hanger_item *hi;
	काष्ठा pktq *txq;
	काष्ठा sk_buff *skb;
	पूर्णांक prec;
	u32 hslot;

	txq = brcmf_bus_gettxq(fws->drvr->bus_अगर);
	अगर (IS_ERR(txq)) अणु
		brcmf_dbg(TRACE, "no txq to clean up\n");
		वापस;
	पूर्ण

	क्रम (prec = 0; prec < txq->num_prec; prec++) अणु
		skb = brcmu_pktq_pdeq_match(txq, prec, fn, &अगरidx);
		जबतक (skb) अणु
			hslot = brcmf_skb_htod_tag_get_field(skb, HSLOT);
			hi = &fws->hanger.items[hslot];
			WARN_ON(skb != hi->pkt);
			hi->state = BRCMF_FWS_HANGER_ITEM_STATE_FREE;
			brcmu_pkt_buf_मुक्त_skb(skb);
			skb = brcmu_pktq_pdeq_match(txq, prec, fn, &अगरidx);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम brcmf_fws_cleanup(काष्ठा brcmf_fws_info *fws, पूर्णांक अगरidx)
अणु
	पूर्णांक i;
	काष्ठा brcmf_fws_mac_descriptor *table;
	bool (*matchfn)(काष्ठा sk_buff *, व्योम *) = शून्य;

	अगर (fws == शून्य)
		वापस;

	अगर (अगरidx != -1)
		matchfn = brcmf_fws_अगरidx_match;

	/* cleanup inभागidual nodes */
	table = &fws->desc.nodes[0];
	क्रम (i = 0; i < ARRAY_SIZE(fws->desc.nodes); i++)
		brcmf_fws_macdesc_cleanup(fws, &table[i], अगरidx);

	brcmf_fws_macdesc_cleanup(fws, &fws->desc.other, अगरidx);
	brcmf_fws_bus_txq_cleanup(fws, matchfn, अगरidx);
	brcmf_fws_hanger_cleanup(fws, matchfn, अगरidx);
पूर्ण

अटल u8 brcmf_fws_hdrpush(काष्ठा brcmf_fws_info *fws, काष्ठा sk_buff *skb)
अणु
	काष्ठा brcmf_fws_mac_descriptor *entry = brcmf_skbcb(skb)->mac;
	u8 *wlh;
	u16 data_offset = 0;
	u8 fillers;
	__le32 pkttag = cpu_to_le32(brcmf_skbcb(skb)->htod);
	__le16 pktseq = cpu_to_le16(brcmf_skbcb(skb)->htod_seq);

	brcmf_dbg(TRACE, "enter: %s, idx=%d hslot=%d htod %X seq %X\n",
		  entry->name, brcmf_skb_अगर_flags_get_field(skb, INDEX),
		  (le32_to_cpu(pkttag) >> 8) & 0xffff,
		  brcmf_skbcb(skb)->htod, brcmf_skbcb(skb)->htod_seq);
	अगर (entry->send_tim_संकेत)
		data_offset += 2 + BRCMF_FWS_TYPE_PENDING_TRAFFIC_BMP_LEN;
	अगर (BRCMF_FWS_MODE_GET_REUSESEQ(fws->mode))
		data_offset += BRCMF_FWS_TYPE_SEQ_LEN;
	/* +2 is क्रम Type[1] and Len[1] in TLV, plus TIM संकेत */
	data_offset += 2 + BRCMF_FWS_TYPE_PKTTAG_LEN;
	fillers = round_up(data_offset, 4) - data_offset;
	data_offset += fillers;

	skb_push(skb, data_offset);
	wlh = skb->data;

	wlh[0] = BRCMF_FWS_TYPE_PKTTAG;
	wlh[1] = BRCMF_FWS_TYPE_PKTTAG_LEN;
	स_नकल(&wlh[2], &pkttag, माप(pkttag));
	अगर (BRCMF_FWS_MODE_GET_REUSESEQ(fws->mode)) अणु
		wlh[1] += BRCMF_FWS_TYPE_SEQ_LEN;
		स_नकल(&wlh[2 + BRCMF_FWS_TYPE_PKTTAG_LEN], &pktseq,
		       माप(pktseq));
	पूर्ण
	wlh += wlh[1] + 2;

	अगर (entry->send_tim_संकेत) अणु
		entry->send_tim_संकेत = false;
		wlh[0] = BRCMF_FWS_TYPE_PENDING_TRAFFIC_BMP;
		wlh[1] = BRCMF_FWS_TYPE_PENDING_TRAFFIC_BMP_LEN;
		wlh[2] = entry->mac_handle;
		wlh[3] = entry->traffic_pending_bmp;
		brcmf_dbg(TRACE, "adding TIM info: handle %d bmp 0x%X\n",
			  entry->mac_handle, entry->traffic_pending_bmp);
		wlh += BRCMF_FWS_TYPE_PENDING_TRAFFIC_BMP_LEN + 2;
		entry->traffic_lastreported_bmp = entry->traffic_pending_bmp;
	पूर्ण
	अगर (fillers)
		स_रखो(wlh, BRCMF_FWS_TYPE_FILLER, fillers);

	वापस (u8)(data_offset >> 2);
पूर्ण

अटल bool brcmf_fws_tim_update(काष्ठा brcmf_fws_info *fws,
				 काष्ठा brcmf_fws_mac_descriptor *entry,
				 पूर्णांक fअगरo, bool send_immediately)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा brcmf_skbuff_cb *skcb;
	s32 err;
	u32 len;
	u8 data_offset;
	पूर्णांक अगरidx;

	/* check delayedQ and suppressQ in one call using biपंचांगap */
	अगर (brcmu_pktq_mlen(&entry->psq, 3 << (fअगरo * 2)) == 0)
		entry->traffic_pending_bmp &= ~NBITVAL(fअगरo);
	अन्यथा
		entry->traffic_pending_bmp |= NBITVAL(fअगरo);

	entry->send_tim_संकेत = false;
	अगर (entry->traffic_lastreported_bmp != entry->traffic_pending_bmp)
		entry->send_tim_संकेत = true;
	अगर (send_immediately && entry->send_tim_संकेत &&
	    entry->state == BRCMF_FWS_STATE_CLOSE) अणु
		/* create a dummy packet and sent that. The traffic          */
		/* biपंचांगap info will स्वतःmatically be attached to that packet */
		len = BRCMF_FWS_TYPE_PKTTAG_LEN + 2 +
		      BRCMF_FWS_TYPE_SEQ_LEN +
		      BRCMF_FWS_TYPE_PENDING_TRAFFIC_BMP_LEN + 2 +
		      4 + fws->drvr->hdrlen;
		skb = brcmu_pkt_buf_get_skb(len);
		अगर (skb == शून्य)
			वापस false;
		skb_pull(skb, len);
		skcb = brcmf_skbcb(skb);
		skcb->mac = entry;
		skcb->state = BRCMF_FWS_SKBSTATE_TIM;
		skcb->htod = 0;
		skcb->htod_seq = 0;
		data_offset = brcmf_fws_hdrpush(fws, skb);
		अगरidx = brcmf_skb_अगर_flags_get_field(skb, INDEX);
		brcmf_fws_unlock(fws);
		err = brcmf_proto_txdata(fws->drvr, अगरidx, data_offset, skb);
		brcmf_fws_lock(fws);
		अगर (err)
			brcmu_pkt_buf_मुक्त_skb(skb);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम
brcmf_fws_flow_control_check(काष्ठा brcmf_fws_info *fws, काष्ठा pktq *pq,
			     u8 अगर_id)
अणु
	काष्ठा brcmf_अगर *अगरp = brcmf_get_अगरp(fws->drvr, अगर_id);

	अगर (WARN_ON(!अगरp))
		वापस;

	अगर ((अगरp->netअगर_stop & BRCMF_NETIF_STOP_REASON_FWS_FC) &&
	    pq->len <= BRCMF_FWS_FLOWCONTROL_LOWATER)
		brcmf_txflowblock_अगर(अगरp,
				     BRCMF_NETIF_STOP_REASON_FWS_FC, false);
	अगर (!(अगरp->netअगर_stop & BRCMF_NETIF_STOP_REASON_FWS_FC) &&
	    pq->len >= BRCMF_FWS_FLOWCONTROL_HIWATER) अणु
		fws->stats.fws_flow_block++;
		brcmf_txflowblock_अगर(अगरp, BRCMF_NETIF_STOP_REASON_FWS_FC, true);
	पूर्ण
	वापस;
पूर्ण

अटल पूर्णांक brcmf_fws_rssi_indicate(काष्ठा brcmf_fws_info *fws, s8 rssi)
अणु
	brcmf_dbg(CTL, "rssi %d\n", rssi);
	वापस 0;
पूर्ण

अटल
पूर्णांक brcmf_fws_macdesc_indicate(काष्ठा brcmf_fws_info *fws, u8 type, u8 *data)
अणु
	काष्ठा brcmf_fws_mac_descriptor *entry, *existing;
	u8 mac_handle;
	u8 अगरidx;
	u8 *addr;

	mac_handle = *data++;
	अगरidx = *data++;
	addr = data;

	entry = &fws->desc.nodes[mac_handle & 0x1F];
	अगर (type == BRCMF_FWS_TYPE_MACDESC_DEL) अणु
		अगर (entry->occupied) अणु
			brcmf_dbg(TRACE, "deleting %s mac %pM\n",
				  entry->name, addr);
			brcmf_fws_lock(fws);
			brcmf_fws_macdesc_cleanup(fws, entry, -1);
			brcmf_fws_macdesc_deinit(entry);
			brcmf_fws_unlock(fws);
		पूर्ण अन्यथा
			fws->stats.mac_update_failed++;
		वापस 0;
	पूर्ण

	existing = brcmf_fws_macdesc_lookup(fws, addr);
	अगर (IS_ERR(existing)) अणु
		अगर (!entry->occupied) अणु
			brcmf_fws_lock(fws);
			entry->mac_handle = mac_handle;
			brcmf_fws_macdesc_init(entry, addr, अगरidx);
			brcmf_fws_macdesc_set_name(fws, entry);
			brcmu_pktq_init(&entry->psq, BRCMF_FWS_PSQ_PREC_COUNT,
					BRCMF_FWS_PSQ_LEN);
			brcmf_fws_unlock(fws);
			brcmf_dbg(TRACE, "add %s mac %pM\n", entry->name, addr);
		पूर्ण अन्यथा अणु
			fws->stats.mac_update_failed++;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (entry != existing) अणु
			brcmf_dbg(TRACE, "copy mac %s\n", existing->name);
			brcmf_fws_lock(fws);
			स_नकल(entry, existing,
			       दुरत्व(काष्ठा brcmf_fws_mac_descriptor, psq));
			entry->mac_handle = mac_handle;
			brcmf_fws_macdesc_deinit(existing);
			brcmf_fws_macdesc_set_name(fws, entry);
			brcmf_fws_unlock(fws);
			brcmf_dbg(TRACE, "relocate %s mac %pM\n", entry->name,
				  addr);
		पूर्ण अन्यथा अणु
			brcmf_dbg(TRACE, "use existing\n");
			WARN_ON(entry->mac_handle != mac_handle);
			/* TODO: what should we करो here: जारी, reinit, .. */
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक brcmf_fws_macdesc_state_indicate(काष्ठा brcmf_fws_info *fws,
					    u8 type, u8 *data)
अणु
	काष्ठा brcmf_fws_mac_descriptor *entry;
	u8 mac_handle;
	पूर्णांक ret;

	mac_handle = data[0];
	entry = &fws->desc.nodes[mac_handle & 0x1F];
	अगर (!entry->occupied) अणु
		fws->stats.mac_ps_update_failed++;
		वापस -ESRCH;
	पूर्ण
	brcmf_fws_lock(fws);
	/* a state update should wipe old credits */
	entry->requested_credit = 0;
	entry->requested_packet = 0;
	अगर (type == BRCMF_FWS_TYPE_MAC_OPEN) अणु
		entry->state = BRCMF_FWS_STATE_OPEN;
		ret = BRCMF_FWS_RET_OK_SCHEDULE;
	पूर्ण अन्यथा अणु
		entry->state = BRCMF_FWS_STATE_CLOSE;
		brcmf_fws_tim_update(fws, entry, BRCMF_FWS_FIFO_AC_BK, false);
		brcmf_fws_tim_update(fws, entry, BRCMF_FWS_FIFO_AC_BE, false);
		brcmf_fws_tim_update(fws, entry, BRCMF_FWS_FIFO_AC_VI, false);
		brcmf_fws_tim_update(fws, entry, BRCMF_FWS_FIFO_AC_VO, true);
		ret = BRCMF_FWS_RET_OK_NOSCHEDULE;
	पूर्ण
	brcmf_fws_unlock(fws);
	वापस ret;
पूर्ण

अटल पूर्णांक brcmf_fws_पूर्णांकerface_state_indicate(काष्ठा brcmf_fws_info *fws,
					      u8 type, u8 *data)
अणु
	काष्ठा brcmf_fws_mac_descriptor *entry;
	u8 अगरidx;
	पूर्णांक ret;

	अगरidx = data[0];

	अगर (अगरidx >= BRCMF_MAX_IFS) अणु
		ret = -दुस्फल;
		जाओ fail;
	पूर्ण

	entry = &fws->desc.अगरace[अगरidx];
	अगर (!entry->occupied) अणु
		ret = -ESRCH;
		जाओ fail;
	पूर्ण

	brcmf_dbg(TRACE, "%s (%d): %s\n", brcmf_fws_get_tlv_name(type), type,
		  entry->name);
	brcmf_fws_lock(fws);
	चयन (type) अणु
	हाल BRCMF_FWS_TYPE_INTERFACE_OPEN:
		entry->state = BRCMF_FWS_STATE_OPEN;
		ret = BRCMF_FWS_RET_OK_SCHEDULE;
		अवरोध;
	हाल BRCMF_FWS_TYPE_INTERFACE_CLOSE:
		entry->state = BRCMF_FWS_STATE_CLOSE;
		ret = BRCMF_FWS_RET_OK_NOSCHEDULE;
		अवरोध;
	शेष:
		ret = -EINVAL;
		brcmf_fws_unlock(fws);
		जाओ fail;
	पूर्ण
	brcmf_fws_unlock(fws);
	वापस ret;

fail:
	fws->stats.अगर_update_failed++;
	वापस ret;
पूर्ण

अटल पूर्णांक brcmf_fws_request_indicate(काष्ठा brcmf_fws_info *fws, u8 type,
				      u8 *data)
अणु
	काष्ठा brcmf_fws_mac_descriptor *entry;

	entry = &fws->desc.nodes[data[1] & 0x1F];
	अगर (!entry->occupied) अणु
		अगर (type == BRCMF_FWS_TYPE_MAC_REQUEST_CREDIT)
			fws->stats.credit_request_failed++;
		अन्यथा
			fws->stats.packet_request_failed++;
		वापस -ESRCH;
	पूर्ण

	brcmf_dbg(TRACE, "%s (%d): %s cnt %d bmp %d\n",
		  brcmf_fws_get_tlv_name(type), type, entry->name,
		  data[0], data[2]);
	brcmf_fws_lock(fws);
	अगर (type == BRCMF_FWS_TYPE_MAC_REQUEST_CREDIT)
		entry->requested_credit = data[0];
	अन्यथा
		entry->requested_packet = data[0];

	entry->ac_biपंचांगap = data[2];
	brcmf_fws_unlock(fws);
	वापस BRCMF_FWS_RET_OK_SCHEDULE;
पूर्ण

अटल व्योम
brcmf_fws_macdesc_use_req_credit(काष्ठा brcmf_fws_mac_descriptor *entry,
				 काष्ठा sk_buff *skb)
अणु
	अगर (entry->requested_credit > 0) अणु
		entry->requested_credit--;
		brcmf_skb_अगर_flags_set_field(skb, REQUESTED, 1);
		brcmf_skb_अगर_flags_set_field(skb, REQ_CREDIT, 1);
		अगर (entry->state != BRCMF_FWS_STATE_CLOSE)
			brcmf_err("requested credit set while mac not closed!\n");
	पूर्ण अन्यथा अगर (entry->requested_packet > 0) अणु
		entry->requested_packet--;
		brcmf_skb_अगर_flags_set_field(skb, REQUESTED, 1);
		brcmf_skb_अगर_flags_set_field(skb, REQ_CREDIT, 0);
		अगर (entry->state != BRCMF_FWS_STATE_CLOSE)
			brcmf_err("requested packet set while mac not closed!\n");
	पूर्ण अन्यथा अणु
		brcmf_skb_अगर_flags_set_field(skb, REQUESTED, 0);
		brcmf_skb_अगर_flags_set_field(skb, REQ_CREDIT, 0);
	पूर्ण
पूर्ण

अटल व्योम brcmf_fws_macdesc_वापस_req_credit(काष्ठा sk_buff *skb)
अणु
	काष्ठा brcmf_fws_mac_descriptor *entry = brcmf_skbcb(skb)->mac;

	अगर ((brcmf_skb_अगर_flags_get_field(skb, REQ_CREDIT)) &&
	    (entry->state == BRCMF_FWS_STATE_CLOSE))
		entry->requested_credit++;
पूर्ण

अटल व्योम brcmf_fws_वापस_credits(काष्ठा brcmf_fws_info *fws,
				     u8 fअगरo, u8 credits)
अणु
	पूर्णांक lender_ac;
	पूर्णांक *borrowed;
	पूर्णांक *fअगरo_credit;

	अगर (!credits)
		वापस;

	fws->fअगरo_credit_map |= 1 << fअगरo;

	अगर (fअगरo > BRCMF_FWS_FIFO_AC_BK &&
	    fअगरo <= BRCMF_FWS_FIFO_AC_VO) अणु
		क्रम (lender_ac = BRCMF_FWS_FIFO_AC_VO; lender_ac >= 0;
		     lender_ac--) अणु
			borrowed = &fws->credits_borrowed[fअगरo][lender_ac];
			अगर (*borrowed) अणु
				fws->fअगरo_credit_map |= (1 << lender_ac);
				fअगरo_credit = &fws->fअगरo_credit[lender_ac];
				अगर (*borrowed >= credits) अणु
					*borrowed -= credits;
					*fअगरo_credit += credits;
					वापस;
				पूर्ण अन्यथा अणु
					credits -= *borrowed;
					*fअगरo_credit += *borrowed;
					*borrowed = 0;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (credits) अणु
		fws->fअगरo_credit[fअगरo] += credits;
	पूर्ण

	अगर (fws->fअगरo_credit[fअगरo] > fws->init_fअगरo_credit[fअगरo])
		fws->fअगरo_credit[fअगरo] = fws->init_fअगरo_credit[fअगरo];

पूर्ण

अटल व्योम brcmf_fws_schedule_deq(काष्ठा brcmf_fws_info *fws)
अणु
	/* only schedule dequeue when there are credits क्रम delayed traffic */
	अगर ((fws->fअगरo_credit_map & fws->fअगरo_delay_map) ||
	    (!brcmf_fws_fc_active(fws) && fws->fअगरo_delay_map))
		queue_work(fws->fws_wq, &fws->fws_dequeue_work);
पूर्ण

अटल पूर्णांक brcmf_fws_enq(काष्ठा brcmf_fws_info *fws,
			 क्रमागत brcmf_fws_skb_state state, पूर्णांक fअगरo,
			 काष्ठा sk_buff *p)
अणु
	काष्ठा brcmf_pub *drvr = fws->drvr;
	पूर्णांक prec = 2 * fअगरo;
	u32 *qfull_stat = &fws->stats.delayq_full_error;
	काष्ठा brcmf_fws_mac_descriptor *entry;
	काष्ठा pktq *pq;
	काष्ठा sk_buff_head *queue;
	काष्ठा sk_buff *p_head;
	काष्ठा sk_buff *p_tail;
	u32 fr_new;
	u32 fr_compare;

	entry = brcmf_skbcb(p)->mac;
	अगर (entry == शून्य) अणु
		bphy_err(drvr, "no mac descriptor found for skb %p\n", p);
		वापस -ENOENT;
	पूर्ण

	brcmf_dbg(DATA, "enter: fifo %d skb %p\n", fअगरo, p);
	अगर (state == BRCMF_FWS_SKBSTATE_SUPPRESSED) अणु
		prec += 1;
		qfull_stat = &fws->stats.supprq_full_error;

		/* Fix out of order delivery of frames. Dont assume frame    */
		/* can be inserted at the end, but look क्रम correct position */
		pq = &entry->psq;
		अगर (pktq_full(pq) || pktq_pfull(pq, prec)) अणु
			*qfull_stat += 1;
			वापस -ENखाता;
		पूर्ण
		queue = &pq->q[prec].skblist;

		p_head = skb_peek(queue);
		p_tail = skb_peek_tail(queue);
		fr_new = brcmf_skb_htod_tag_get_field(p, FREERUN);

		जबतक (p_head != p_tail) अणु
			fr_compare = brcmf_skb_htod_tag_get_field(p_tail,
								  FREERUN);
			/* be sure to handle wrap of 256 */
			अगर (((fr_new > fr_compare) &&
			     ((fr_new - fr_compare) < 128)) ||
			    ((fr_new < fr_compare) &&
			     ((fr_compare - fr_new) > 128)))
				अवरोध;
			p_tail = skb_queue_prev(queue, p_tail);
		पूर्ण
		/* Position found. Determine what to करो */
		अगर (p_tail == शून्य) अणु
			/* empty list */
			__skb_queue_tail(queue, p);
		पूर्ण अन्यथा अणु
			fr_compare = brcmf_skb_htod_tag_get_field(p_tail,
								  FREERUN);
			अगर (((fr_new > fr_compare) &&
			     ((fr_new - fr_compare) < 128)) ||
			    ((fr_new < fr_compare) &&
			     ((fr_compare - fr_new) > 128))) अणु
				/* After tail */
				__skb_queue_after(queue, p_tail, p);
			पूर्ण अन्यथा अणु
				/* Beक्रमe tail */
				__skb_insert(p, p_tail->prev, p_tail, queue);
			पूर्ण
		पूर्ण

		/* Complete the counters and statistics */
		pq->len++;
		अगर (pq->hi_prec < prec)
			pq->hi_prec = (u8) prec;
	पूर्ण अन्यथा अगर (brcmu_pktq_penq(&entry->psq, prec, p) == शून्य) अणु
		*qfull_stat += 1;
		वापस -ENखाता;
	पूर्ण

	/* increment total enqueued packet count */
	fws->fअगरo_delay_map |= 1 << fअगरo;
	fws->fअगरo_enqpkt[fअगरo]++;

	/* update the sk_buff state */
	brcmf_skbcb(p)->state = state;

	/*
	 * A packet has been pushed so update traffic
	 * availability biपंचांगap, अगर applicable
	 */
	brcmf_fws_tim_update(fws, entry, fअगरo, true);
	brcmf_fws_flow_control_check(fws, &entry->psq,
				     brcmf_skb_अगर_flags_get_field(p, INDEX));
	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *brcmf_fws_deq(काष्ठा brcmf_fws_info *fws, पूर्णांक fअगरo)
अणु
	काष्ठा brcmf_fws_mac_descriptor *table;
	काष्ठा brcmf_fws_mac_descriptor *entry;
	काष्ठा sk_buff *p;
	पूर्णांक num_nodes;
	पूर्णांक node_pos;
	पूर्णांक prec_out;
	पूर्णांक pmsk;
	पूर्णांक i;

	table = (काष्ठा brcmf_fws_mac_descriptor *)&fws->desc;
	num_nodes = माप(fws->desc) / माप(काष्ठा brcmf_fws_mac_descriptor);
	node_pos = fws->deq_node_pos[fअगरo];

	क्रम (i = 0; i < num_nodes; i++) अणु
		entry = &table[(node_pos + i) % num_nodes];
		अगर (!entry->occupied ||
		    brcmf_fws_macdesc_बंदd(fws, entry, fअगरo))
			जारी;

		अगर (entry->suppressed)
			pmsk = 2;
		अन्यथा
			pmsk = 3;
		p = brcmu_pktq_mdeq(&entry->psq, pmsk << (fअगरo * 2), &prec_out);
		अगर (p == शून्य) अणु
			अगर (entry->suppressed) अणु
				अगर (entry->suppr_transit_count)
					जारी;
				entry->suppressed = false;
				p = brcmu_pktq_mdeq(&entry->psq,
						    1 << (fअगरo * 2), &prec_out);
			पूर्ण
		पूर्ण
		अगर  (p == शून्य)
			जारी;

		brcmf_fws_macdesc_use_req_credit(entry, p);

		/* move dequeue position to ensure fair round-robin */
		fws->deq_node_pos[fअगरo] = (node_pos + i + 1) % num_nodes;
		brcmf_fws_flow_control_check(fws, &entry->psq,
					     brcmf_skb_अगर_flags_get_field(p,
									  INDEX)
					     );
		/*
		 * A packet has been picked up, update traffic
		 * availability biपंचांगap, अगर applicable
		 */
		brcmf_fws_tim_update(fws, entry, fअगरo, false);

		/*
		 * decrement total enqueued fअगरo packets and
		 * clear delay biपंचांगap अगर करोne.
		 */
		fws->fअगरo_enqpkt[fअगरo]--;
		अगर (fws->fअगरo_enqpkt[fअगरo] == 0)
			fws->fअगरo_delay_map &= ~(1 << fअगरo);
		जाओ करोne;
	पूर्ण
	p = शून्य;
करोne:
	brcmf_dbg(DATA, "exit: fifo %d skb %p\n", fअगरo, p);
	वापस p;
पूर्ण

अटल पूर्णांक brcmf_fws_txstatus_suppressed(काष्ठा brcmf_fws_info *fws, पूर्णांक fअगरo,
					 काष्ठा sk_buff *skb,
					 u32 genbit, u16 seq)
अणु
	काष्ठा brcmf_fws_mac_descriptor *entry = brcmf_skbcb(skb)->mac;
	u32 hslot;
	पूर्णांक ret;

	hslot = brcmf_skb_htod_tag_get_field(skb, HSLOT);

	/* this packet was suppressed */
	अगर (!entry->suppressed) अणु
		entry->suppressed = true;
		entry->suppr_transit_count = entry->transit_count;
		brcmf_dbg(DATA, "suppress %s: transit %d\n",
			  entry->name, entry->transit_count);
	पूर्ण

	entry->generation = genbit;

	brcmf_skb_htod_tag_set_field(skb, GENERATION, genbit);
	brcmf_skbcb(skb)->htod_seq = seq;
	अगर (brcmf_skb_htod_seq_get_field(skb, FROMFW)) अणु
		brcmf_skb_htod_seq_set_field(skb, FROMDRV, 1);
		brcmf_skb_htod_seq_set_field(skb, FROMFW, 0);
	पूर्ण अन्यथा अणु
		brcmf_skb_htod_seq_set_field(skb, FROMDRV, 0);
	पूर्ण
	ret = brcmf_fws_enq(fws, BRCMF_FWS_SKBSTATE_SUPPRESSED, fअगरo, skb);

	अगर (ret != 0) अणु
		/* suppress q is full drop this packet */
		brcmf_fws_hanger_poppkt(&fws->hanger, hslot, &skb, true);
	पूर्ण अन्यथा अणु
		/* Mark suppressed to aव्योम a द्विगुन मुक्त during wlfc cleanup */
		brcmf_fws_hanger_mark_suppressed(&fws->hanger, hslot);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
brcmf_fws_txs_process(काष्ठा brcmf_fws_info *fws, u8 flags, u32 hslot,
		      u32 genbit, u16 seq, u8 compcnt)
अणु
	काष्ठा brcmf_pub *drvr = fws->drvr;
	u32 fअगरo;
	u8 cnt = 0;
	पूर्णांक ret;
	bool हटाओ_from_hanger = true;
	काष्ठा sk_buff *skb;
	काष्ठा brcmf_skbuff_cb *skcb;
	काष्ठा brcmf_fws_mac_descriptor *entry = शून्य;
	काष्ठा brcmf_अगर *अगरp;

	brcmf_dbg(DATA, "flags %d\n", flags);

	अगर (flags == BRCMF_FWS_TXSTATUS_DISCARD)
		fws->stats.txs_discard += compcnt;
	अन्यथा अगर (flags == BRCMF_FWS_TXSTATUS_CORE_SUPPRESS) अणु
		fws->stats.txs_supp_core += compcnt;
		हटाओ_from_hanger = false;
	पूर्ण अन्यथा अगर (flags == BRCMF_FWS_TXSTATUS_FW_PS_SUPPRESS) अणु
		fws->stats.txs_supp_ps += compcnt;
		हटाओ_from_hanger = false;
	पूर्ण अन्यथा अगर (flags == BRCMF_FWS_TXSTATUS_FW_TOSSED)
		fws->stats.txs_tossed += compcnt;
	अन्यथा अगर (flags == BRCMF_FWS_TXSTATUS_FW_DISCARD_NOACK)
		fws->stats.txs_discard += compcnt;
	अन्यथा अगर (flags == BRCMF_FWS_TXSTATUS_FW_SUPPRESS_ACKED)
		fws->stats.txs_discard += compcnt;
	अन्यथा अगर (flags == BRCMF_FWS_TXSTATUS_HOST_TOSSED)
		fws->stats.txs_host_tossed += compcnt;
	अन्यथा
		bphy_err(drvr, "unexpected txstatus\n");

	जबतक (cnt < compcnt) अणु
		ret = brcmf_fws_hanger_poppkt(&fws->hanger, hslot, &skb,
					      हटाओ_from_hanger);
		अगर (ret != 0) अणु
			bphy_err(drvr, "no packet in hanger slot: hslot=%d\n",
				 hslot);
			जाओ cont;
		पूर्ण

		skcb = brcmf_skbcb(skb);
		entry = skcb->mac;
		अगर (WARN_ON(!entry)) अणु
			brcmu_pkt_buf_मुक्त_skb(skb);
			जाओ cont;
		पूर्ण
		entry->transit_count--;
		अगर (entry->suppressed && entry->suppr_transit_count)
			entry->suppr_transit_count--;

		brcmf_dbg(DATA, "%s flags %d htod %X seq %X\n", entry->name,
			  flags, skcb->htod, seq);

		/* pick up the implicit credit from this packet */
		fअगरo = brcmf_skb_htod_tag_get_field(skb, FIFO);
		अगर (fws->fcmode == BRCMF_FWS_FCMODE_IMPLIED_CREDIT ||
		    (brcmf_skb_अगर_flags_get_field(skb, REQ_CREDIT)) ||
		    flags == BRCMF_FWS_TXSTATUS_HOST_TOSSED) अणु
			brcmf_fws_वापस_credits(fws, fअगरo, 1);
			brcmf_fws_schedule_deq(fws);
		पूर्ण
		brcmf_fws_macdesc_वापस_req_credit(skb);

		ret = brcmf_proto_hdrpull(fws->drvr, false, skb, &अगरp);
		अगर (ret) अणु
			brcmu_pkt_buf_मुक्त_skb(skb);
			जाओ cont;
		पूर्ण
		अगर (!हटाओ_from_hanger)
			ret = brcmf_fws_txstatus_suppressed(fws, fअगरo, skb,
							    genbit, seq);
		अगर (हटाओ_from_hanger || ret)
			brcmf_txfinalize(अगरp, skb, true);

cont:
		hslot = (hslot + 1) & (BRCMF_FWS_TXSTAT_HSLOT_MASK >>
				       BRCMF_FWS_TXSTAT_HSLOT_SHIFT);
		अगर (BRCMF_FWS_MODE_GET_REUSESEQ(fws->mode))
			seq = (seq + 1) & BRCMF_SKB_HTOD_SEQ_NR_MASK;

		cnt++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक brcmf_fws_fअगरocreditback_indicate(काष्ठा brcmf_fws_info *fws,
					     u8 *data)
अणु
	पूर्णांक i;

	अगर (fws->fcmode != BRCMF_FWS_FCMODE_EXPLICIT_CREDIT) अणु
		brcmf_dbg(INFO, "ignored\n");
		वापस BRCMF_FWS_RET_OK_NOSCHEDULE;
	पूर्ण

	brcmf_dbg(DATA, "enter: data %pM\n", data);
	brcmf_fws_lock(fws);
	क्रम (i = 0; i < BRCMF_FWS_FIFO_COUNT; i++)
		brcmf_fws_वापस_credits(fws, i, data[i]);

	brcmf_dbg(DATA, "map: credit %x delay %x\n", fws->fअगरo_credit_map,
		  fws->fअगरo_delay_map);
	brcmf_fws_unlock(fws);
	वापस BRCMF_FWS_RET_OK_SCHEDULE;
पूर्ण

अटल पूर्णांक brcmf_fws_txstatus_indicate(काष्ठा brcmf_fws_info *fws, u8 type,
				       u8 *data)
अणु
	__le32 status_le;
	__le16 seq_le;
	u32 status;
	u32 hslot;
	u32 genbit;
	u8 flags;
	u16 seq;
	u8 compcnt;
	u8 compcnt_offset = BRCMF_FWS_TYPE_TXSTATUS_LEN;

	स_नकल(&status_le, data, माप(status_le));
	status = le32_to_cpu(status_le);
	flags = brcmf_txstatus_get_field(status, FLAGS);
	hslot = brcmf_txstatus_get_field(status, HSLOT);
	genbit = brcmf_txstatus_get_field(status, GENERATION);
	अगर (BRCMF_FWS_MODE_GET_REUSESEQ(fws->mode)) अणु
		स_नकल(&seq_le, &data[BRCMF_FWS_TYPE_TXSTATUS_LEN],
		       माप(seq_le));
		seq = le16_to_cpu(seq_le);
		compcnt_offset += BRCMF_FWS_TYPE_SEQ_LEN;
	पूर्ण अन्यथा अणु
		seq = 0;
	पूर्ण

	अगर (type == BRCMF_FWS_TYPE_COMP_TXSTATUS)
		compcnt = data[compcnt_offset];
	अन्यथा
		compcnt = 1;
	fws->stats.txs_indicate += compcnt;

	brcmf_fws_lock(fws);
	brcmf_fws_txs_process(fws, flags, hslot, genbit, seq, compcnt);
	brcmf_fws_unlock(fws);
	वापस BRCMF_FWS_RET_OK_NOSCHEDULE;
पूर्ण

अटल पूर्णांक brcmf_fws_dbg_seqnum_check(काष्ठा brcmf_fws_info *fws, u8 *data)
अणु
	__le32 बारtamp;

	स_नकल(&बारtamp, &data[2], माप(बारtamp));
	brcmf_dbg(CTL, "received: seq %d, timestamp %d\n", data[1],
		  le32_to_cpu(बारtamp));
	वापस 0;
पूर्ण

अटल पूर्णांक brcmf_fws_notअगरy_credit_map(काष्ठा brcmf_अगर *अगरp,
				       स्थिर काष्ठा brcmf_event_msg *e,
				       व्योम *data)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	काष्ठा brcmf_fws_info *fws = drvr_to_fws(drvr);
	पूर्णांक i;
	u8 *credits = data;

	अगर (e->datalen < BRCMF_FWS_FIFO_COUNT) अणु
		bphy_err(drvr, "event payload too small (%d)\n", e->datalen);
		वापस -EINVAL;
	पूर्ण

	fws->crediपंचांगap_received = true;

	brcmf_dbg(TRACE, "enter: credits %pM\n", credits);
	brcmf_fws_lock(fws);
	क्रम (i = 0; i < ARRAY_SIZE(fws->fअगरo_credit); i++) अणु
		fws->fअगरo_credit[i] += credits[i] - fws->init_fअगरo_credit[i];
		fws->init_fअगरo_credit[i] = credits[i];
		अगर (fws->fअगरo_credit[i] > 0)
			fws->fअगरo_credit_map |= 1 << i;
		अन्यथा
			fws->fअगरo_credit_map &= ~(1 << i);
		WARN_ONCE(fws->fअगरo_credit[i] < 0,
			  "fifo_credit[%d] is negative(%d)\n", i,
			  fws->fअगरo_credit[i]);
	पूर्ण
	brcmf_fws_schedule_deq(fws);
	brcmf_fws_unlock(fws);
	वापस 0;
पूर्ण

अटल पूर्णांक brcmf_fws_notअगरy_bcmc_credit_support(काष्ठा brcmf_अगर *अगरp,
						स्थिर काष्ठा brcmf_event_msg *e,
						व्योम *data)
अणु
	काष्ठा brcmf_fws_info *fws = drvr_to_fws(अगरp->drvr);

	अगर (fws) अणु
		brcmf_fws_lock(fws);
		fws->bcmc_credit_check = true;
		brcmf_fws_unlock(fws);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम brcmf_rxreorder_get_skb_list(काष्ठा brcmf_ampdu_rx_reorder *rfi,
					 u8 start, u8 end,
					 काष्ठा sk_buff_head *skb_list)
अणु
	/* initialize वापस list */
	__skb_queue_head_init(skb_list);

	अगर (rfi->pend_pkts == 0) अणु
		brcmf_dbg(INFO, "no packets in reorder queue\n");
		वापस;
	पूर्ण

	करो अणु
		अगर (rfi->pktslots[start]) अणु
			__skb_queue_tail(skb_list, rfi->pktslots[start]);
			rfi->pktslots[start] = शून्य;
		पूर्ण
		start++;
		अगर (start > rfi->max_idx)
			start = 0;
	पूर्ण जबतक (start != end);
	rfi->pend_pkts -= skb_queue_len(skb_list);
पूर्ण

व्योम brcmf_fws_rxreorder(काष्ठा brcmf_अगर *अगरp, काष्ठा sk_buff *pkt, bool inirq)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	u8 *reorder_data;
	u8 flow_id, max_idx, cur_idx, exp_idx, end_idx;
	काष्ठा brcmf_ampdu_rx_reorder *rfi;
	काष्ठा sk_buff_head reorder_list;
	काष्ठा sk_buff *pnext;
	u8 flags;
	u32 buf_size;

	reorder_data = ((काष्ठा brcmf_skb_reorder_data *)pkt->cb)->reorder;
	flow_id = reorder_data[BRCMF_RXREORDER_FLOWID_OFFSET];
	flags = reorder_data[BRCMF_RXREORDER_FLAGS_OFFSET];

	/* validate flags and flow id */
	अगर (flags == 0xFF) अणु
		bphy_err(drvr, "invalid flags...so ignore this packet\n");
		brcmf_netअगर_rx(अगरp, pkt, inirq);
		वापस;
	पूर्ण

	rfi = अगरp->drvr->reorder_flows[flow_id];
	अगर (flags & BRCMF_RXREORDER_DEL_FLOW) अणु
		brcmf_dbg(INFO, "flow-%d: delete\n",
			  flow_id);

		अगर (rfi == शून्य) अणु
			brcmf_dbg(INFO, "received flags to cleanup, but no flow (%d) yet\n",
				  flow_id);
			brcmf_netअगर_rx(अगरp, pkt, inirq);
			वापस;
		पूर्ण

		brcmf_rxreorder_get_skb_list(rfi, rfi->exp_idx, rfi->exp_idx,
					     &reorder_list);
		/* add the last packet */
		__skb_queue_tail(&reorder_list, pkt);
		kमुक्त(rfi);
		अगरp->drvr->reorder_flows[flow_id] = शून्य;
		जाओ netअगर_rx;
	पूर्ण
	/* from here on we need a flow reorder instance */
	अगर (rfi == शून्य) अणु
		buf_size = माप(*rfi);
		max_idx = reorder_data[BRCMF_RXREORDER_MAXIDX_OFFSET];

		buf_size += (max_idx + 1) * माप(pkt);

		/* allocate space क्रम flow reorder info */
		brcmf_dbg(INFO, "flow-%d: start, maxidx %d\n",
			  flow_id, max_idx);
		rfi = kzalloc(buf_size, GFP_ATOMIC);
		अगर (rfi == शून्य) अणु
			bphy_err(drvr, "failed to alloc buffer\n");
			brcmf_netअगर_rx(अगरp, pkt, inirq);
			वापस;
		पूर्ण

		अगरp->drvr->reorder_flows[flow_id] = rfi;
		rfi->pktslots = (काष्ठा sk_buff **)(rfi + 1);
		rfi->max_idx = max_idx;
	पूर्ण
	अगर (flags & BRCMF_RXREORDER_NEW_HOLE)  अणु
		अगर (rfi->pend_pkts) अणु
			brcmf_rxreorder_get_skb_list(rfi, rfi->exp_idx,
						     rfi->exp_idx,
						     &reorder_list);
			WARN_ON(rfi->pend_pkts);
		पूर्ण अन्यथा अणु
			__skb_queue_head_init(&reorder_list);
		पूर्ण
		rfi->cur_idx = reorder_data[BRCMF_RXREORDER_CURIDX_OFFSET];
		rfi->exp_idx = reorder_data[BRCMF_RXREORDER_EXPIDX_OFFSET];
		rfi->max_idx = reorder_data[BRCMF_RXREORDER_MAXIDX_OFFSET];
		rfi->pktslots[rfi->cur_idx] = pkt;
		rfi->pend_pkts++;
		brcmf_dbg(DATA, "flow-%d: new hole %d (%d), pending %d\n",
			  flow_id, rfi->cur_idx, rfi->exp_idx, rfi->pend_pkts);
	पूर्ण अन्यथा अगर (flags & BRCMF_RXREORDER_CURIDX_VALID) अणु
		cur_idx = reorder_data[BRCMF_RXREORDER_CURIDX_OFFSET];
		exp_idx = reorder_data[BRCMF_RXREORDER_EXPIDX_OFFSET];

		अगर ((exp_idx == rfi->exp_idx) && (cur_idx != rfi->exp_idx)) अणु
			/* still in the current hole */
			/* enqueue the current on the buffer chain */
			अगर (rfi->pktslots[cur_idx] != शून्य) अणु
				brcmf_dbg(INFO, "HOLE: ERROR buffer pending..free it\n");
				brcmu_pkt_buf_मुक्त_skb(rfi->pktslots[cur_idx]);
				rfi->pktslots[cur_idx] = शून्य;
			पूर्ण
			rfi->pktslots[cur_idx] = pkt;
			rfi->pend_pkts++;
			rfi->cur_idx = cur_idx;
			brcmf_dbg(DATA, "flow-%d: store pkt %d (%d), pending %d\n",
				  flow_id, cur_idx, exp_idx, rfi->pend_pkts);

			/* can वापस now as there is no reorder
			 * list to process.
			 */
			वापस;
		पूर्ण
		अगर (rfi->exp_idx == cur_idx) अणु
			अगर (rfi->pktslots[cur_idx] != शून्य) अणु
				brcmf_dbg(INFO, "error buffer pending..free it\n");
				brcmu_pkt_buf_मुक्त_skb(rfi->pktslots[cur_idx]);
				rfi->pktslots[cur_idx] = शून्य;
			पूर्ण
			rfi->pktslots[cur_idx] = pkt;
			rfi->pend_pkts++;

			/* got the expected one. flush from current to expected
			 * and update expected
			 */
			brcmf_dbg(DATA, "flow-%d: expected %d (%d), pending %d\n",
				  flow_id, cur_idx, exp_idx, rfi->pend_pkts);

			rfi->cur_idx = cur_idx;
			rfi->exp_idx = exp_idx;

			brcmf_rxreorder_get_skb_list(rfi, cur_idx, exp_idx,
						     &reorder_list);
			brcmf_dbg(DATA, "flow-%d: freeing buffers %d, pending %d\n",
				  flow_id, skb_queue_len(&reorder_list),
				  rfi->pend_pkts);
		पूर्ण अन्यथा अणु
			u8 end_idx;

			brcmf_dbg(DATA, "flow-%d (0x%x): both moved, old %d/%d, new %d/%d\n",
				  flow_id, flags, rfi->cur_idx, rfi->exp_idx,
				  cur_idx, exp_idx);
			अगर (flags & BRCMF_RXREORDER_FLUSH_ALL)
				end_idx = rfi->exp_idx;
			अन्यथा
				end_idx = exp_idx;

			/* flush pkts first */
			brcmf_rxreorder_get_skb_list(rfi, rfi->exp_idx, end_idx,
						     &reorder_list);

			अगर (exp_idx == ((cur_idx + 1) % (rfi->max_idx + 1))) अणु
				__skb_queue_tail(&reorder_list, pkt);
			पूर्ण अन्यथा अणु
				rfi->pktslots[cur_idx] = pkt;
				rfi->pend_pkts++;
			पूर्ण
			rfi->exp_idx = exp_idx;
			rfi->cur_idx = cur_idx;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* explicity winकरोw move updating the expected index */
		exp_idx = reorder_data[BRCMF_RXREORDER_EXPIDX_OFFSET];

		brcmf_dbg(DATA, "flow-%d (0x%x): change expected: %d -> %d\n",
			  flow_id, flags, rfi->exp_idx, exp_idx);
		अगर (flags & BRCMF_RXREORDER_FLUSH_ALL)
			end_idx =  rfi->exp_idx;
		अन्यथा
			end_idx =  exp_idx;

		brcmf_rxreorder_get_skb_list(rfi, rfi->exp_idx, end_idx,
					     &reorder_list);
		__skb_queue_tail(&reorder_list, pkt);
		/* set the new expected idx */
		rfi->exp_idx = exp_idx;
	पूर्ण
netअगर_rx:
	skb_queue_walk_safe(&reorder_list, pkt, pnext) अणु
		__skb_unlink(pkt, &reorder_list);
		brcmf_netअगर_rx(अगरp, pkt, inirq);
	पूर्ण
पूर्ण

व्योम brcmf_fws_hdrpull(काष्ठा brcmf_अगर *अगरp, s16 siglen, काष्ठा sk_buff *skb)
अणु
	काष्ठा brcmf_skb_reorder_data *rd;
	काष्ठा brcmf_fws_info *fws = drvr_to_fws(अगरp->drvr);
	u8 *संकेत_data;
	s16 data_len;
	u8 type;
	u8 len;
	u8 *data;
	s32 status;
	s32 err;

	brcmf_dbg(HDRS, "enter: ifidx %d, skblen %u, sig %d\n",
		  अगरp->अगरidx, skb->len, siglen);

	WARN_ON(siglen > skb->len);

	अगर (siglen > skb->len)
		siglen = skb->len;

	अगर (!siglen)
		वापस;
	/* अगर flow control disabled, skip to packet data and leave */
	अगर ((!fws) || (!fws->fw_संकेतs)) अणु
		skb_pull(skb, siglen);
		वापस;
	पूर्ण

	fws->stats.header_pulls++;
	data_len = siglen;
	संकेत_data = skb->data;

	status = BRCMF_FWS_RET_OK_NOSCHEDULE;
	जबतक (data_len > 0) अणु
		/* extract tlv info */
		type = संकेत_data[0];

		/* FILLER type is actually not a TLV, but
		 * a single byte that can be skipped.
		 */
		अगर (type == BRCMF_FWS_TYPE_FILLER) अणु
			संकेत_data += 1;
			data_len -= 1;
			जारी;
		पूर्ण
		len = संकेत_data[1];
		data = संकेत_data + 2;

		brcmf_dbg(HDRS, "tlv type=%s (%d), len=%d (%d)\n",
			  brcmf_fws_get_tlv_name(type), type, len,
			  brcmf_fws_get_tlv_len(fws, type));

		/* पात parsing when length invalid */
		अगर (data_len < len + 2)
			अवरोध;

		अगर (len < brcmf_fws_get_tlv_len(fws, type))
			अवरोध;

		err = BRCMF_FWS_RET_OK_NOSCHEDULE;
		चयन (type) अणु
		हाल BRCMF_FWS_TYPE_HOST_REORDER_RXPKTS:
			rd = (काष्ठा brcmf_skb_reorder_data *)skb->cb;
			rd->reorder = data;
			अवरोध;
		हाल BRCMF_FWS_TYPE_MACDESC_ADD:
		हाल BRCMF_FWS_TYPE_MACDESC_DEL:
			brcmf_fws_macdesc_indicate(fws, type, data);
			अवरोध;
		हाल BRCMF_FWS_TYPE_MAC_OPEN:
		हाल BRCMF_FWS_TYPE_MAC_CLOSE:
			err = brcmf_fws_macdesc_state_indicate(fws, type, data);
			अवरोध;
		हाल BRCMF_FWS_TYPE_INTERFACE_OPEN:
		हाल BRCMF_FWS_TYPE_INTERFACE_CLOSE:
			err = brcmf_fws_पूर्णांकerface_state_indicate(fws, type,
								 data);
			अवरोध;
		हाल BRCMF_FWS_TYPE_MAC_REQUEST_CREDIT:
		हाल BRCMF_FWS_TYPE_MAC_REQUEST_PACKET:
			err = brcmf_fws_request_indicate(fws, type, data);
			अवरोध;
		हाल BRCMF_FWS_TYPE_TXSTATUS:
		हाल BRCMF_FWS_TYPE_COMP_TXSTATUS:
			brcmf_fws_txstatus_indicate(fws, type, data);
			अवरोध;
		हाल BRCMF_FWS_TYPE_FIFO_CREDITBACK:
			err = brcmf_fws_fअगरocreditback_indicate(fws, data);
			अवरोध;
		हाल BRCMF_FWS_TYPE_RSSI:
			brcmf_fws_rssi_indicate(fws, *data);
			अवरोध;
		हाल BRCMF_FWS_TYPE_TRANS_ID:
			brcmf_fws_dbg_seqnum_check(fws, data);
			अवरोध;
		हाल BRCMF_FWS_TYPE_PKTTAG:
		हाल BRCMF_FWS_TYPE_PENDING_TRAFFIC_BMP:
		शेष:
			fws->stats.tlv_invalid_type++;
			अवरोध;
		पूर्ण
		अगर (err == BRCMF_FWS_RET_OK_SCHEDULE)
			status = BRCMF_FWS_RET_OK_SCHEDULE;
		संकेत_data += len + 2;
		data_len -= len + 2;
	पूर्ण

	अगर (data_len != 0)
		fws->stats.tlv_parse_failed++;

	अगर (status == BRCMF_FWS_RET_OK_SCHEDULE)
		brcmf_fws_schedule_deq(fws);

	/* संकेतling processing result करोes
	 * not affect the actual ethernet packet.
	 */
	skb_pull(skb, siglen);

	/* this may be a संकेत-only packet
	 */
	अगर (skb->len == 0)
		fws->stats.header_only_pkt++;
पूर्ण

अटल u8 brcmf_fws_precommit_skb(काष्ठा brcmf_fws_info *fws, पूर्णांक fअगरo,
				   काष्ठा sk_buff *p)
अणु
	काष्ठा brcmf_skbuff_cb *skcb = brcmf_skbcb(p);
	काष्ठा brcmf_fws_mac_descriptor *entry = skcb->mac;
	u8 flags;

	अगर (skcb->state != BRCMF_FWS_SKBSTATE_SUPPRESSED)
		brcmf_skb_htod_tag_set_field(p, GENERATION, entry->generation);
	flags = BRCMF_FWS_HTOD_FLAG_PKTFROMHOST;
	अगर (brcmf_skb_अगर_flags_get_field(p, REQUESTED)) अणु
		/*
		 * Indicate that this packet is being sent in response to an
		 * explicit request from the firmware side.
		 */
		flags |= BRCMF_FWS_HTOD_FLAG_PKT_REQUESTED;
	पूर्ण
	brcmf_skb_htod_tag_set_field(p, FLAGS, flags);
	वापस brcmf_fws_hdrpush(fws, p);
पूर्ण

अटल व्योम brcmf_fws_rollback_toq(काष्ठा brcmf_fws_info *fws,
				   काष्ठा sk_buff *skb, पूर्णांक fअगरo)
अणु
	काष्ठा brcmf_pub *drvr = fws->drvr;
	काष्ठा brcmf_fws_mac_descriptor *entry;
	काष्ठा sk_buff *pktout;
	पूर्णांक qidx, hslot;
	पूर्णांक rc = 0;

	entry = brcmf_skbcb(skb)->mac;
	अगर (entry->occupied) अणु
		qidx = 2 * fअगरo;
		अगर (brcmf_skbcb(skb)->state == BRCMF_FWS_SKBSTATE_SUPPRESSED)
			qidx++;

		pktout = brcmu_pktq_penq_head(&entry->psq, qidx, skb);
		अगर (pktout == शून्य) अणु
			bphy_err(drvr, "%s queue %d full\n", entry->name, qidx);
			rc = -ENOSPC;
		पूर्ण
	पूर्ण अन्यथा अणु
		bphy_err(drvr, "%s entry removed\n", entry->name);
		rc = -ENOENT;
	पूर्ण

	अगर (rc) अणु
		fws->stats.rollback_failed++;
		hslot = brcmf_skb_htod_tag_get_field(skb, HSLOT);
		brcmf_fws_txs_process(fws, BRCMF_FWS_TXSTATUS_HOST_TOSSED,
				      hslot, 0, 0, 1);
	पूर्ण अन्यथा अणु
		fws->stats.rollback_success++;
		brcmf_fws_वापस_credits(fws, fअगरo, 1);
		brcmf_fws_macdesc_वापस_req_credit(skb);
	पूर्ण
पूर्ण

अटल पूर्णांक brcmf_fws_borrow_credit(काष्ठा brcmf_fws_info *fws,
				   पूर्णांक highest_lender_ac, पूर्णांक borrower_ac,
				   bool borrow_all)
अणु
	पूर्णांक lender_ac, borrow_limit = 0;

	क्रम (lender_ac = 0; lender_ac <= highest_lender_ac; lender_ac++) अणु

		अगर (!borrow_all)
			borrow_limit =
			  fws->init_fअगरo_credit[lender_ac] / BRCMF_BORROW_RATIO;
		अन्यथा
			borrow_limit = 0;

		अगर (fws->fअगरo_credit[lender_ac] > borrow_limit) अणु
			fws->credits_borrowed[borrower_ac][lender_ac]++;
			fws->fअगरo_credit[lender_ac]--;
			अगर (fws->fअगरo_credit[lender_ac] == 0)
				fws->fअगरo_credit_map &= ~(1 << lender_ac);
			fws->fअगरo_credit_map |= (1 << borrower_ac);
			brcmf_dbg(DATA, "borrow credit from: %d\n", lender_ac);
			वापस 0;
		पूर्ण
	पूर्ण
	fws->fअगरo_credit_map &= ~(1 << borrower_ac);
	वापस -ENAVAIL;
पूर्ण

अटल पूर्णांक brcmf_fws_commit_skb(काष्ठा brcmf_fws_info *fws, पूर्णांक fअगरo,
				काष्ठा sk_buff *skb)
अणु
	काष्ठा brcmf_skbuff_cb *skcb = brcmf_skbcb(skb);
	काष्ठा brcmf_fws_mac_descriptor *entry;
	पूर्णांक rc;
	u8 अगरidx;
	u8 data_offset;

	entry = skcb->mac;
	अगर (IS_ERR(entry))
		वापस PTR_ERR(entry);

	data_offset = brcmf_fws_precommit_skb(fws, fअगरo, skb);
	entry->transit_count++;
	अगर (entry->suppressed)
		entry->suppr_transit_count++;
	अगरidx = brcmf_skb_अगर_flags_get_field(skb, INDEX);
	brcmf_fws_unlock(fws);
	rc = brcmf_proto_txdata(fws->drvr, अगरidx, data_offset, skb);
	brcmf_fws_lock(fws);
	brcmf_dbg(DATA, "%s flags %X htod %X bus_tx %d\n", entry->name,
		  skcb->अगर_flags, skcb->htod, rc);
	अगर (rc < 0) अणु
		entry->transit_count--;
		अगर (entry->suppressed)
			entry->suppr_transit_count--;
		(व्योम)brcmf_proto_hdrpull(fws->drvr, false, skb, शून्य);
		जाओ rollback;
	पूर्ण

	fws->stats.pkt2bus++;
	fws->stats.send_pkts[fअगरo]++;
	अगर (brcmf_skb_अगर_flags_get_field(skb, REQUESTED))
		fws->stats.requested_sent[fअगरo]++;

	वापस rc;

rollback:
	brcmf_fws_rollback_toq(fws, skb, fअगरo);
	वापस rc;
पूर्ण

अटल पूर्णांक brcmf_fws_assign_htod(काष्ठा brcmf_fws_info *fws, काष्ठा sk_buff *p,
				  पूर्णांक fअगरo)
अणु
	काष्ठा brcmf_skbuff_cb *skcb = brcmf_skbcb(p);
	पूर्णांक rc, hslot;

	skcb->htod = 0;
	skcb->htod_seq = 0;
	hslot = brcmf_fws_hanger_get_मुक्त_slot(&fws->hanger);
	brcmf_skb_htod_tag_set_field(p, HSLOT, hslot);
	brcmf_skb_htod_tag_set_field(p, FREERUN, skcb->mac->seq[fअगरo]);
	brcmf_skb_htod_tag_set_field(p, FIFO, fअगरo);
	rc = brcmf_fws_hanger_pushpkt(&fws->hanger, p, hslot);
	अगर (!rc)
		skcb->mac->seq[fअगरo]++;
	अन्यथा
		fws->stats.generic_error++;
	वापस rc;
पूर्ण

पूर्णांक brcmf_fws_process_skb(काष्ठा brcmf_अगर *अगरp, काष्ठा sk_buff *skb)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	काष्ठा brcmf_fws_info *fws = drvr_to_fws(drvr);
	काष्ठा brcmf_skbuff_cb *skcb = brcmf_skbcb(skb);
	काष्ठा ethhdr *eh = (काष्ठा ethhdr *)(skb->data);
	पूर्णांक fअगरo = BRCMF_FWS_FIFO_BCMC;
	bool multicast = is_multicast_ether_addr(eh->h_dest);
	पूर्णांक rc = 0;

	brcmf_dbg(DATA, "tx proto=0x%X\n", ntohs(eh->h_proto));

	/* set control buffer inक्रमmation */
	skcb->अगर_flags = 0;
	skcb->state = BRCMF_FWS_SKBSTATE_NEW;
	brcmf_skb_अगर_flags_set_field(skb, INDEX, अगरp->अगरidx);

	/* mapping from 802.1d priority to firmware fअगरo index */
	अगर (!multicast)
		fअगरo = brcmf_map_prio_to_aci(drvr->config, skb->priority);

	brcmf_fws_lock(fws);
	अगर (fअगरo != BRCMF_FWS_FIFO_AC_BE && fअगरo < BRCMF_FWS_FIFO_BCMC)
		fws->borrow_defer_बारtamp = jअगरfies +
					      BRCMF_FWS_BORROW_DEFER_PERIOD;

	skcb->mac = brcmf_fws_macdesc_find(fws, अगरp, eh->h_dest);
	brcmf_dbg(DATA, "%s mac %pM multi %d fifo %d\n", skcb->mac->name,
		  eh->h_dest, multicast, fअगरo);
	अगर (!brcmf_fws_assign_htod(fws, skb, fअगरo)) अणु
		brcmf_fws_enq(fws, BRCMF_FWS_SKBSTATE_DELAYED, fअगरo, skb);
		brcmf_fws_schedule_deq(fws);
	पूर्ण अन्यथा अणु
		bphy_err(drvr, "no hanger slot available\n");
		rc = -ENOMEM;
	पूर्ण
	brcmf_fws_unlock(fws);

	वापस rc;
पूर्ण

व्योम brcmf_fws_reset_पूर्णांकerface(काष्ठा brcmf_अगर *अगरp)
अणु
	काष्ठा brcmf_fws_mac_descriptor *entry = अगरp->fws_desc;

	brcmf_dbg(TRACE, "enter: bsscfgidx=%d\n", अगरp->bsscfgidx);
	अगर (!entry)
		वापस;

	brcmf_fws_macdesc_init(entry, अगरp->mac_addr, अगरp->अगरidx);
पूर्ण

व्योम brcmf_fws_add_पूर्णांकerface(काष्ठा brcmf_अगर *अगरp)
अणु
	काष्ठा brcmf_fws_info *fws = drvr_to_fws(अगरp->drvr);
	काष्ठा brcmf_fws_mac_descriptor *entry;

	अगर (!अगरp->ndev || !brcmf_fws_queue_skbs(fws))
		वापस;

	entry = &fws->desc.अगरace[अगरp->अगरidx];
	अगरp->fws_desc = entry;
	brcmf_fws_macdesc_init(entry, अगरp->mac_addr, अगरp->अगरidx);
	brcmf_fws_macdesc_set_name(fws, entry);
	brcmu_pktq_init(&entry->psq, BRCMF_FWS_PSQ_PREC_COUNT,
			BRCMF_FWS_PSQ_LEN);
	brcmf_dbg(TRACE, "added %s\n", entry->name);
पूर्ण

व्योम brcmf_fws_del_पूर्णांकerface(काष्ठा brcmf_अगर *अगरp)
अणु
	काष्ठा brcmf_fws_mac_descriptor *entry = अगरp->fws_desc;
	काष्ठा brcmf_fws_info *fws = drvr_to_fws(अगरp->drvr);

	अगर (!entry)
		वापस;

	brcmf_fws_lock(fws);
	अगरp->fws_desc = शून्य;
	brcmf_dbg(TRACE, "deleting %s\n", entry->name);
	brcmf_fws_macdesc_cleanup(fws, &fws->desc.अगरace[अगरp->अगरidx],
				  अगरp->अगरidx);
	brcmf_fws_macdesc_deinit(entry);
	brcmf_fws_cleanup(fws, अगरp->अगरidx);
	brcmf_fws_unlock(fws);
पूर्ण

अटल व्योम brcmf_fws_dequeue_worker(काष्ठा work_काष्ठा *worker)
अणु
	काष्ठा brcmf_fws_info *fws;
	काष्ठा brcmf_pub *drvr;
	काष्ठा sk_buff *skb;
	पूर्णांक fअगरo;
	u32 hslot;
	u32 अगरidx;
	पूर्णांक ret;

	fws = container_of(worker, काष्ठा brcmf_fws_info, fws_dequeue_work);
	drvr = fws->drvr;

	brcmf_fws_lock(fws);
	क्रम (fअगरo = BRCMF_FWS_FIFO_BCMC; fअगरo >= 0 && !fws->bus_flow_blocked;
	     fअगरo--) अणु
		अगर (!brcmf_fws_fc_active(fws)) अणु
			जबतक ((skb = brcmf_fws_deq(fws, fअगरo)) != शून्य) अणु
				hslot = brcmf_skb_htod_tag_get_field(skb,
								     HSLOT);
				brcmf_fws_hanger_poppkt(&fws->hanger, hslot,
							&skb, true);
				अगरidx = brcmf_skb_अगर_flags_get_field(skb,
								     INDEX);
				/* Use proto layer to send data frame */
				brcmf_fws_unlock(fws);
				ret = brcmf_proto_txdata(drvr, अगरidx, 0, skb);
				brcmf_fws_lock(fws);
				अगर (ret < 0)
					brcmf_txfinalize(brcmf_get_अगरp(drvr,
								       अगरidx),
							 skb, false);
				अगर (fws->bus_flow_blocked)
					अवरोध;
			पूर्ण
			जारी;
		पूर्ण

		जबतक ((fws->fअगरo_credit[fअगरo]) ||
		       ((!fws->bcmc_credit_check) &&
				(fअगरo == BRCMF_FWS_FIFO_BCMC))) अणु
			skb = brcmf_fws_deq(fws, fअगरo);
			अगर (!skb)
				अवरोध;
			fws->fअगरo_credit[fअगरo]--;
			अगर (brcmf_fws_commit_skb(fws, fअगरo, skb))
				अवरोध;
			अगर (fws->bus_flow_blocked)
				अवरोध;
		पूर्ण

		अगर (fअगरo >= BRCMF_FWS_FIFO_AC_BE &&
		    fअगरo <= BRCMF_FWS_FIFO_AC_VO &&
		    fws->fअगरo_credit[fअगरo] == 0 &&
		    !fws->bus_flow_blocked) अणु
			जबतक (brcmf_fws_borrow_credit(fws,
						       fअगरo - 1, fअगरo,
						       true) == 0) अणु
				skb = brcmf_fws_deq(fws, fअगरo);
				अगर (!skb) अणु
					brcmf_fws_वापस_credits(fws, fअगरo, 1);
					अवरोध;
				पूर्ण
				अगर (brcmf_fws_commit_skb(fws, fअगरo, skb))
					अवरोध;
				अगर (fws->bus_flow_blocked)
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	brcmf_fws_unlock(fws);
पूर्ण

#अगर_घोषित DEBUG
अटल पूर्णांक brcmf_debugfs_fws_stats_पढ़ो(काष्ठा seq_file *seq, व्योम *data)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(seq->निजी);
	काष्ठा brcmf_fws_stats *fwstats = &(drvr_to_fws(bus_अगर->drvr)->stats);

	seq_म_लिखो(seq,
		   "header_pulls:      %u\n"
		   "header_only_pkt:   %u\n"
		   "tlv_parse_failed:  %u\n"
		   "tlv_invalid_type:  %u\n"
		   "mac_update_fails:  %u\n"
		   "ps_update_fails:   %u\n"
		   "if_update_fails:   %u\n"
		   "pkt2bus:           %u\n"
		   "generic_error:     %u\n"
		   "rollback_success:  %u\n"
		   "rollback_failed:   %u\n"
		   "delayq_full:       %u\n"
		   "supprq_full:       %u\n"
		   "txs_indicate:      %u\n"
		   "txs_discard:       %u\n"
		   "txs_suppr_core:    %u\n"
		   "txs_suppr_ps:      %u\n"
		   "txs_tossed:        %u\n"
		   "txs_host_tossed:   %u\n"
		   "bus_flow_block:    %u\n"
		   "fws_flow_block:    %u\n"
		   "send_pkts:         BK:%u BE:%u VO:%u VI:%u BCMC:%u\n"
		   "requested_sent:    BK:%u BE:%u VO:%u VI:%u BCMC:%u\n",
		   fwstats->header_pulls,
		   fwstats->header_only_pkt,
		   fwstats->tlv_parse_failed,
		   fwstats->tlv_invalid_type,
		   fwstats->mac_update_failed,
		   fwstats->mac_ps_update_failed,
		   fwstats->अगर_update_failed,
		   fwstats->pkt2bus,
		   fwstats->generic_error,
		   fwstats->rollback_success,
		   fwstats->rollback_failed,
		   fwstats->delayq_full_error,
		   fwstats->supprq_full_error,
		   fwstats->txs_indicate,
		   fwstats->txs_discard,
		   fwstats->txs_supp_core,
		   fwstats->txs_supp_ps,
		   fwstats->txs_tossed,
		   fwstats->txs_host_tossed,
		   fwstats->bus_flow_block,
		   fwstats->fws_flow_block,
		   fwstats->send_pkts[0], fwstats->send_pkts[1],
		   fwstats->send_pkts[2], fwstats->send_pkts[3],
		   fwstats->send_pkts[4],
		   fwstats->requested_sent[0],
		   fwstats->requested_sent[1],
		   fwstats->requested_sent[2],
		   fwstats->requested_sent[3],
		   fwstats->requested_sent[4]);

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक brcmf_debugfs_fws_stats_पढ़ो(काष्ठा seq_file *seq, व्योम *data)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

काष्ठा brcmf_fws_info *brcmf_fws_attach(काष्ठा brcmf_pub *drvr)
अणु
	काष्ठा brcmf_fws_info *fws;
	काष्ठा brcmf_अगर *अगरp;
	u32 tlv = BRCMF_FWS_FLAGS_RSSI_SIGNALS;
	पूर्णांक rc;
	u32 mode;

	fws = kzalloc(माप(*fws), GFP_KERNEL);
	अगर (!fws) अणु
		rc = -ENOMEM;
		जाओ fail;
	पूर्ण

	spin_lock_init(&fws->spinlock);

	/* store drvr reference */
	fws->drvr = drvr;
	fws->fcmode = drvr->settings->fcmode;

	अगर (!drvr->bus_अगर->always_use_fws_queue &&
	    (fws->fcmode == BRCMF_FWS_FCMODE_NONE)) अणु
		fws->aव्योम_queueing = true;
		brcmf_dbg(INFO, "FWS queueing will be avoided\n");
		वापस fws;
	पूर्ण

	fws->fws_wq = create_singlethपढ़ो_workqueue("brcmf_fws_wq");
	अगर (fws->fws_wq == शून्य) अणु
		bphy_err(drvr, "workqueue creation failed\n");
		rc = -EBADF;
		जाओ fail;
	पूर्ण
	INIT_WORK(&fws->fws_dequeue_work, brcmf_fws_dequeue_worker);

	/* enable firmware संकेतling अगर fcmode active */
	अगर (fws->fcmode != BRCMF_FWS_FCMODE_NONE)
		tlv |= BRCMF_FWS_FLAGS_XONXOFF_SIGNALS |
		       BRCMF_FWS_FLAGS_CREDIT_STATUS_SIGNALS |
		       BRCMF_FWS_FLAGS_HOST_PROPTXSTATUS_ACTIVE |
		       BRCMF_FWS_FLAGS_HOST_RXREORDER_ACTIVE;

	rc = brcmf_fweh_रेजिस्टर(drvr, BRCMF_E_FIFO_CREDIT_MAP,
				 brcmf_fws_notअगरy_credit_map);
	अगर (rc < 0) अणु
		bphy_err(drvr, "register credit map handler failed\n");
		जाओ fail;
	पूर्ण
	rc = brcmf_fweh_रेजिस्टर(drvr, BRCMF_E_BCMC_CREDIT_SUPPORT,
				 brcmf_fws_notअगरy_bcmc_credit_support);
	अगर (rc < 0) अणु
		bphy_err(drvr, "register bcmc credit handler failed\n");
		brcmf_fweh_unरेजिस्टर(drvr, BRCMF_E_FIFO_CREDIT_MAP);
		जाओ fail;
	पूर्ण

	/* Setting the iovar may fail अगर feature is unsupported
	 * so leave the rc as is so driver initialization can
	 * जारी. Set mode back to none indicating not enabled.
	 */
	fws->fw_संकेतs = true;
	अगरp = brcmf_get_अगरp(drvr, 0);
	अगर (brcmf_fil_iovar_पूर्णांक_set(अगरp, "tlv", tlv)) अणु
		bphy_err(drvr, "failed to set bdcv2 tlv signaling\n");
		fws->fcmode = BRCMF_FWS_FCMODE_NONE;
		fws->fw_संकेतs = false;
	पूर्ण

	अगर (brcmf_fil_iovar_पूर्णांक_set(अगरp, "ampdu_hostreorder", 1))
		brcmf_dbg(INFO, "enabling AMPDU host-reorder failed\n");

	/* Enable seq number reuse, अगर supported */
	अगर (brcmf_fil_iovar_पूर्णांक_get(अगरp, "wlfc_mode", &mode) == 0) अणु
		अगर (BRCMF_FWS_MODE_GET_REUSESEQ(mode)) अणु
			mode = 0;
			BRCMF_FWS_MODE_SET_REUSESEQ(mode, 1);
			अगर (brcmf_fil_iovar_पूर्णांक_set(अगरp,
						    "wlfc_mode", mode) == 0) अणु
				BRCMF_FWS_MODE_SET_REUSESEQ(fws->mode, 1);
			पूर्ण
		पूर्ण
	पूर्ण

	brcmf_fws_hanger_init(&fws->hanger);
	brcmf_fws_macdesc_init(&fws->desc.other, शून्य, 0);
	brcmf_fws_macdesc_set_name(fws, &fws->desc.other);
	brcmf_dbg(INFO, "added %s\n", fws->desc.other.name);
	brcmu_pktq_init(&fws->desc.other.psq, BRCMF_FWS_PSQ_PREC_COUNT,
			BRCMF_FWS_PSQ_LEN);

	brcmf_dbg(INFO, "%s bdcv2 tlv signaling [%x]\n",
		  fws->fw_संकेतs ? "enabled" : "disabled", tlv);
	वापस fws;

fail:
	brcmf_fws_detach(fws);
	वापस ERR_PTR(rc);
पूर्ण

व्योम brcmf_fws_detach(काष्ठा brcmf_fws_info *fws)
अणु
	अगर (!fws)
		वापस;

	अगर (fws->fws_wq)
		destroy_workqueue(fws->fws_wq);

	/* cleanup */
	brcmf_fws_lock(fws);
	brcmf_fws_cleanup(fws, -1);
	brcmf_fws_unlock(fws);

	/* मुक्त top काष्ठाure */
	kमुक्त(fws);
पूर्ण

व्योम brcmf_fws_debugfs_create(काष्ठा brcmf_pub *drvr)
अणु
	/* create debugfs file क्रम statistics */
	brcmf_debugfs_add_entry(drvr, "fws_stats",
				brcmf_debugfs_fws_stats_पढ़ो);
पूर्ण

bool brcmf_fws_queue_skbs(काष्ठा brcmf_fws_info *fws)
अणु
	वापस !fws->aव्योम_queueing;
पूर्ण

bool brcmf_fws_fc_active(काष्ठा brcmf_fws_info *fws)
अणु
	अगर (!fws->crediपंचांगap_received)
		वापस false;

	वापस fws->fcmode != BRCMF_FWS_FCMODE_NONE;
पूर्ण

व्योम brcmf_fws_bustxfail(काष्ठा brcmf_fws_info *fws, काष्ठा sk_buff *skb)
अणु
	u32 hslot;

	अगर (brcmf_skbcb(skb)->state == BRCMF_FWS_SKBSTATE_TIM) अणु
		brcmu_pkt_buf_मुक्त_skb(skb);
		वापस;
	पूर्ण
	brcmf_fws_lock(fws);
	hslot = brcmf_skb_htod_tag_get_field(skb, HSLOT);
	brcmf_fws_txs_process(fws, BRCMF_FWS_TXSTATUS_HOST_TOSSED, hslot, 0, 0,
			      1);
	brcmf_fws_unlock(fws);
पूर्ण

व्योम brcmf_fws_bus_blocked(काष्ठा brcmf_pub *drvr, bool flow_blocked)
अणु
	काष्ठा brcmf_fws_info *fws = drvr_to_fws(drvr);
	काष्ठा brcmf_अगर *अगरp;
	पूर्णांक i;

	अगर (fws->aव्योम_queueing) अणु
		क्रम (i = 0; i < BRCMF_MAX_IFS; i++) अणु
			अगरp = drvr->अगरlist[i];
			अगर (!अगरp || !अगरp->ndev)
				जारी;
			brcmf_txflowblock_अगर(अगरp, BRCMF_NETIF_STOP_REASON_FLOW,
					     flow_blocked);
		पूर्ण
	पूर्ण अन्यथा अणु
		fws->bus_flow_blocked = flow_blocked;
		अगर (!flow_blocked)
			brcmf_fws_schedule_deq(fws);
		अन्यथा
			fws->stats.bus_flow_block++;
	पूर्ण
पूर्ण
