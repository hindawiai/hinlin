<शैली गुरु>
/*
   BlueZ - Bluetooth protocol stack क्रम Linux
   Copyright (C) 2000-2001 Qualcomm Incorporated
   Copyright (C) 2009-2010 Gustavo F. Paकरोvan <gustavo@paकरोvan.org>
   Copyright (C) 2010 Google Inc.

   Written 2000,2001 by Maxim Krasnyansky <maxk@qualcomm.com>

   This program is मुक्त software; you can redistribute it and/or modअगरy
   it under the terms of the GNU General Public License version 2 as
   published by the Free Software Foundation;

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY
   CLAIM, OR ANY SPECIAL INसूचीECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES
   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS,
   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS
   SOFTWARE IS DISCLAIMED.
*/

#अगर_अघोषित __L2CAP_H
#घोषणा __L2CAP_H

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/atomic.h>

/* L2CAP शेषs */
#घोषणा L2CAP_DEFAULT_MTU		672
#घोषणा L2CAP_DEFAULT_MIN_MTU		48
#घोषणा L2CAP_DEFAULT_FLUSH_TO		0xFFFF
#घोषणा L2CAP_EFS_DEFAULT_FLUSH_TO	0xFFFFFFFF
#घोषणा L2CAP_DEFAULT_TX_WINDOW		63
#घोषणा L2CAP_DEFAULT_EXT_WINDOW	0x3FFF
#घोषणा L2CAP_DEFAULT_MAX_TX		3
#घोषणा L2CAP_DEFAULT_RETRANS_TO	2000    /* 2 seconds */
#घोषणा L2CAP_DEFAULT_MONITOR_TO	12000   /* 12 seconds */
#घोषणा L2CAP_DEFAULT_MAX_PDU_SIZE	1492    /* Sized क्रम AMP packet */
#घोषणा L2CAP_DEFAULT_ACK_TO		200
#घोषणा L2CAP_DEFAULT_MAX_SDU_SIZE	0xFFFF
#घोषणा L2CAP_DEFAULT_SDU_ITIME		0xFFFFFFFF
#घोषणा L2CAP_DEFAULT_ACC_LAT		0xFFFFFFFF
#घोषणा L2CAP_BREDR_MAX_PAYLOAD		1019    /* 3-DH5 packet */
#घोषणा L2CAP_LE_MIN_MTU		23
#घोषणा L2CAP_ECRED_CONN_SCID_MAX	5

#घोषणा L2CAP_DISC_TIMEOUT		msecs_to_jअगरfies(100)
#घोषणा L2CAP_DISC_REJ_TIMEOUT		msecs_to_jअगरfies(5000)
#घोषणा L2CAP_ENC_TIMEOUT		msecs_to_jअगरfies(5000)
#घोषणा L2CAP_CONN_TIMEOUT		msecs_to_jअगरfies(40000)
#घोषणा L2CAP_INFO_TIMEOUT		msecs_to_jअगरfies(4000)
#घोषणा L2CAP_MOVE_TIMEOUT		msecs_to_jअगरfies(4000)
#घोषणा L2CAP_MOVE_ERTX_TIMEOUT		msecs_to_jअगरfies(60000)
#घोषणा L2CAP_WAIT_ACK_POLL_PERIOD	msecs_to_jअगरfies(200)
#घोषणा L2CAP_WAIT_ACK_TIMEOUT		msecs_to_jअगरfies(10000)

#घोषणा L2CAP_A2MP_DEFAULT_MTU		670

/* L2CAP socket address */
काष्ठा sockaddr_l2 अणु
	sa_family_t	l2_family;
	__le16		l2_psm;
	bdaddr_t	l2_bdaddr;
	__le16		l2_cid;
	__u8		l2_bdaddr_type;
पूर्ण;

/* L2CAP socket options */
#घोषणा L2CAP_OPTIONS	0x01
काष्ठा l2cap_options अणु
	__u16 omtu;
	__u16 imtu;
	__u16 flush_to;
	__u8  mode;
	__u8  fcs;
	__u8  max_tx;
	__u16 txwin_size;
पूर्ण;

#घोषणा L2CAP_CONNINFO	0x02
काष्ठा l2cap_conninfo अणु
	__u16 hci_handle;
	__u8  dev_class[3];
पूर्ण;

#घोषणा L2CAP_LM	0x03
#घोषणा L2CAP_LM_MASTER		0x0001
#घोषणा L2CAP_LM_AUTH		0x0002
#घोषणा L2CAP_LM_ENCRYPT	0x0004
#घोषणा L2CAP_LM_TRUSTED	0x0008
#घोषणा L2CAP_LM_RELIABLE	0x0010
#घोषणा L2CAP_LM_SECURE		0x0020
#घोषणा L2CAP_LM_FIPS		0x0040

/* L2CAP command codes */
#घोषणा L2CAP_COMMAND_REJ	0x01
#घोषणा L2CAP_CONN_REQ		0x02
#घोषणा L2CAP_CONN_RSP		0x03
#घोषणा L2CAP_CONF_REQ		0x04
#घोषणा L2CAP_CONF_RSP		0x05
#घोषणा L2CAP_DISCONN_REQ	0x06
#घोषणा L2CAP_DISCONN_RSP	0x07
#घोषणा L2CAP_ECHO_REQ		0x08
#घोषणा L2CAP_ECHO_RSP		0x09
#घोषणा L2CAP_INFO_REQ		0x0a
#घोषणा L2CAP_INFO_RSP		0x0b
#घोषणा L2CAP_CREATE_CHAN_REQ	0x0c
#घोषणा L2CAP_CREATE_CHAN_RSP	0x0d
#घोषणा L2CAP_MOVE_CHAN_REQ	0x0e
#घोषणा L2CAP_MOVE_CHAN_RSP	0x0f
#घोषणा L2CAP_MOVE_CHAN_CFM	0x10
#घोषणा L2CAP_MOVE_CHAN_CFM_RSP	0x11
#घोषणा L2CAP_CONN_PARAM_UPDATE_REQ	0x12
#घोषणा L2CAP_CONN_PARAM_UPDATE_RSP	0x13
#घोषणा L2CAP_LE_CONN_REQ	0x14
#घोषणा L2CAP_LE_CONN_RSP	0x15
#घोषणा L2CAP_LE_CREDITS	0x16
#घोषणा L2CAP_ECRED_CONN_REQ	0x17
#घोषणा L2CAP_ECRED_CONN_RSP	0x18
#घोषणा L2CAP_ECRED_RECONF_REQ	0x19
#घोषणा L2CAP_ECRED_RECONF_RSP	0x1a

/* L2CAP extended feature mask */
#घोषणा L2CAP_FEAT_FLOWCTL	0x00000001
#घोषणा L2CAP_FEAT_RETRANS	0x00000002
#घोषणा L2CAP_FEAT_BIसूची_QOS	0x00000004
#घोषणा L2CAP_FEAT_ERTM		0x00000008
#घोषणा L2CAP_FEAT_STREAMING	0x00000010
#घोषणा L2CAP_FEAT_FCS		0x00000020
#घोषणा L2CAP_FEAT_EXT_FLOW	0x00000040
#घोषणा L2CAP_FEAT_FIXED_CHAN	0x00000080
#घोषणा L2CAP_FEAT_EXT_WINDOW	0x00000100
#घोषणा L2CAP_FEAT_UCD		0x00000200

/* L2CAP checksum option */
#घोषणा L2CAP_FCS_NONE		0x00
#घोषणा L2CAP_FCS_CRC16		0x01

/* L2CAP fixed channels */
#घोषणा L2CAP_FC_SIG_BREDR	0x02
#घोषणा L2CAP_FC_CONNLESS	0x04
#घोषणा L2CAP_FC_A2MP		0x08
#घोषणा L2CAP_FC_ATT		0x10
#घोषणा L2CAP_FC_SIG_LE		0x20
#घोषणा L2CAP_FC_SMP_LE		0x40
#घोषणा L2CAP_FC_SMP_BREDR	0x80

/* L2CAP Control Field bit masks */
#घोषणा L2CAP_CTRL_SAR			0xC000
#घोषणा L2CAP_CTRL_REQSEQ		0x3F00
#घोषणा L2CAP_CTRL_TXSEQ		0x007E
#घोषणा L2CAP_CTRL_SUPERVISE		0x000C

#घोषणा L2CAP_CTRL_RETRANS		0x0080
#घोषणा L2CAP_CTRL_FINAL		0x0080
#घोषणा L2CAP_CTRL_POLL			0x0010
#घोषणा L2CAP_CTRL_FRAME_TYPE		0x0001 /* I- or S-Frame */

#घोषणा L2CAP_CTRL_TXSEQ_SHIFT		1
#घोषणा L2CAP_CTRL_SUPER_SHIFT		2
#घोषणा L2CAP_CTRL_POLL_SHIFT		4
#घोषणा L2CAP_CTRL_FINAL_SHIFT		7
#घोषणा L2CAP_CTRL_REQSEQ_SHIFT		8
#घोषणा L2CAP_CTRL_SAR_SHIFT		14

/* L2CAP Extended Control Field bit mask */
#घोषणा L2CAP_EXT_CTRL_TXSEQ		0xFFFC0000
#घोषणा L2CAP_EXT_CTRL_SAR		0x00030000
#घोषणा L2CAP_EXT_CTRL_SUPERVISE	0x00030000
#घोषणा L2CAP_EXT_CTRL_REQSEQ		0x0000FFFC

#घोषणा L2CAP_EXT_CTRL_POLL		0x00040000
#घोषणा L2CAP_EXT_CTRL_FINAL		0x00000002
#घोषणा L2CAP_EXT_CTRL_FRAME_TYPE	0x00000001 /* I- or S-Frame */

#घोषणा L2CAP_EXT_CTRL_FINAL_SHIFT	1
#घोषणा L2CAP_EXT_CTRL_REQSEQ_SHIFT	2
#घोषणा L2CAP_EXT_CTRL_SAR_SHIFT	16
#घोषणा L2CAP_EXT_CTRL_SUPER_SHIFT	16
#घोषणा L2CAP_EXT_CTRL_POLL_SHIFT	18
#घोषणा L2CAP_EXT_CTRL_TXSEQ_SHIFT	18

/* L2CAP Supervisory Function */
#घोषणा L2CAP_SUPER_RR		0x00
#घोषणा L2CAP_SUPER_REJ		0x01
#घोषणा L2CAP_SUPER_RNR		0x02
#घोषणा L2CAP_SUPER_SREJ	0x03

/* L2CAP Segmentation and Reassembly */
#घोषणा L2CAP_SAR_UNSEGMENTED	0x00
#घोषणा L2CAP_SAR_START		0x01
#घोषणा L2CAP_SAR_END		0x02
#घोषणा L2CAP_SAR_CONTINUE	0x03

/* L2CAP Command rej. reasons */
#घोषणा L2CAP_REJ_NOT_UNDERSTOOD	0x0000
#घोषणा L2CAP_REJ_MTU_EXCEEDED		0x0001
#घोषणा L2CAP_REJ_INVALID_CID		0x0002

/* L2CAP काष्ठाures */
काष्ठा l2cap_hdr अणु
	__le16     len;
	__le16     cid;
पूर्ण __packed;
#घोषणा L2CAP_LEN_SIZE		2
#घोषणा L2CAP_HDR_SIZE		4
#घोषणा L2CAP_ENH_HDR_SIZE	6
#घोषणा L2CAP_EXT_HDR_SIZE	8

#घोषणा L2CAP_FCS_SIZE		2
#घोषणा L2CAP_SDULEN_SIZE	2
#घोषणा L2CAP_PSMLEN_SIZE	2
#घोषणा L2CAP_ENH_CTRL_SIZE	2
#घोषणा L2CAP_EXT_CTRL_SIZE	4

काष्ठा l2cap_cmd_hdr अणु
	__u8       code;
	__u8       ident;
	__le16     len;
पूर्ण __packed;
#घोषणा L2CAP_CMD_HDR_SIZE	4

काष्ठा l2cap_cmd_rej_unk अणु
	__le16     reason;
पूर्ण __packed;

काष्ठा l2cap_cmd_rej_mtu अणु
	__le16     reason;
	__le16     max_mtu;
पूर्ण __packed;

काष्ठा l2cap_cmd_rej_cid अणु
	__le16     reason;
	__le16     scid;
	__le16     dcid;
पूर्ण __packed;

काष्ठा l2cap_conn_req अणु
	__le16     psm;
	__le16     scid;
पूर्ण __packed;

काष्ठा l2cap_conn_rsp अणु
	__le16     dcid;
	__le16     scid;
	__le16     result;
	__le16     status;
पूर्ण __packed;

/* protocol/service multiplexer (PSM) */
#घोषणा L2CAP_PSM_SDP		0x0001
#घोषणा L2CAP_PSM_RFCOMM	0x0003
#घोषणा L2CAP_PSM_3DSP		0x0021
#घोषणा L2CAP_PSM_IPSP		0x0023 /* 6LoWPAN */

#घोषणा L2CAP_PSM_DYN_START	0x1001
#घोषणा L2CAP_PSM_DYN_END	0xffff
#घोषणा L2CAP_PSM_AUTO_END	0x10ff
#घोषणा L2CAP_PSM_LE_DYN_START  0x0080
#घोषणा L2CAP_PSM_LE_DYN_END	0x00ff

/* channel identअगरier */
#घोषणा L2CAP_CID_SIGNALING	0x0001
#घोषणा L2CAP_CID_CONN_LESS	0x0002
#घोषणा L2CAP_CID_A2MP		0x0003
#घोषणा L2CAP_CID_ATT		0x0004
#घोषणा L2CAP_CID_LE_SIGNALING	0x0005
#घोषणा L2CAP_CID_SMP		0x0006
#घोषणा L2CAP_CID_SMP_BREDR	0x0007
#घोषणा L2CAP_CID_DYN_START	0x0040
#घोषणा L2CAP_CID_DYN_END	0xffff
#घोषणा L2CAP_CID_LE_DYN_END	0x007f

/* connect/create channel results */
#घोषणा L2CAP_CR_SUCCESS	0x0000
#घोषणा L2CAP_CR_PEND		0x0001
#घोषणा L2CAP_CR_BAD_PSM	0x0002
#घोषणा L2CAP_CR_SEC_BLOCK	0x0003
#घोषणा L2CAP_CR_NO_MEM		0x0004
#घोषणा L2CAP_CR_BAD_AMP	0x0005
#घोषणा L2CAP_CR_INVALID_SCID	0x0006
#घोषणा L2CAP_CR_SCID_IN_USE	0x0007

/* credit based connect results */
#घोषणा L2CAP_CR_LE_SUCCESS		0x0000
#घोषणा L2CAP_CR_LE_BAD_PSM		0x0002
#घोषणा L2CAP_CR_LE_NO_MEM		0x0004
#घोषणा L2CAP_CR_LE_AUTHENTICATION	0x0005
#घोषणा L2CAP_CR_LE_AUTHORIZATION	0x0006
#घोषणा L2CAP_CR_LE_BAD_KEY_SIZE	0x0007
#घोषणा L2CAP_CR_LE_ENCRYPTION		0x0008
#घोषणा L2CAP_CR_LE_INVALID_SCID	0x0009
#घोषणा L2CAP_CR_LE_SCID_IN_USE		0X000A
#घोषणा L2CAP_CR_LE_UNACCEPT_PARAMS	0X000B
#घोषणा L2CAP_CR_LE_INVALID_PARAMS	0X000C

/* connect/create channel status */
#घोषणा L2CAP_CS_NO_INFO	0x0000
#घोषणा L2CAP_CS_AUTHEN_PEND	0x0001
#घोषणा L2CAP_CS_AUTHOR_PEND	0x0002

काष्ठा l2cap_conf_req अणु
	__le16     dcid;
	__le16     flags;
	__u8       data[];
पूर्ण __packed;

काष्ठा l2cap_conf_rsp अणु
	__le16     scid;
	__le16     flags;
	__le16     result;
	__u8       data[];
पूर्ण __packed;

#घोषणा L2CAP_CONF_SUCCESS	0x0000
#घोषणा L2CAP_CONF_UNACCEPT	0x0001
#घोषणा L2CAP_CONF_REJECT	0x0002
#घोषणा L2CAP_CONF_UNKNOWN	0x0003
#घोषणा L2CAP_CONF_PENDING	0x0004
#घोषणा L2CAP_CONF_EFS_REJECT	0x0005

/* configuration req/rsp continuation flag */
#घोषणा L2CAP_CONF_FLAG_CONTINUATION	0x0001

काष्ठा l2cap_conf_opt अणु
	__u8       type;
	__u8       len;
	__u8       val[];
पूर्ण __packed;
#घोषणा L2CAP_CONF_OPT_SIZE	2

#घोषणा L2CAP_CONF_HINT		0x80
#घोषणा L2CAP_CONF_MASK		0x7f

#घोषणा L2CAP_CONF_MTU		0x01
#घोषणा L2CAP_CONF_FLUSH_TO	0x02
#घोषणा L2CAP_CONF_QOS		0x03
#घोषणा L2CAP_CONF_RFC		0x04
#घोषणा L2CAP_CONF_FCS		0x05
#घोषणा L2CAP_CONF_EFS		0x06
#घोषणा L2CAP_CONF_EWS		0x07

#घोषणा L2CAP_CONF_MAX_SIZE	22

काष्ठा l2cap_conf_rfc अणु
	__u8       mode;
	__u8       txwin_size;
	__u8       max_transmit;
	__le16     retrans_समयout;
	__le16     monitor_समयout;
	__le16     max_pdu_size;
पूर्ण __packed;

#घोषणा L2CAP_MODE_BASIC	0x00
#घोषणा L2CAP_MODE_RETRANS	0x01
#घोषणा L2CAP_MODE_FLOWCTL	0x02
#घोषणा L2CAP_MODE_ERTM		0x03
#घोषणा L2CAP_MODE_STREAMING	0x04

/* Unlike the above this one करोesn't actually map to anything that would
 * ever be sent over the air. Thereक्रमe, use a value that's unlikely to
 * ever be used in the BR/EDR configuration phase.
 */
#घोषणा L2CAP_MODE_LE_FLOWCTL	0x80
#घोषणा L2CAP_MODE_EXT_FLOWCTL	0x81

काष्ठा l2cap_conf_efs अणु
	__u8	id;
	__u8	stype;
	__le16	msdu;
	__le32	sdu_iसमय;
	__le32	acc_lat;
	__le32	flush_to;
पूर्ण __packed;

#घोषणा L2CAP_SERV_NOTRAFIC	0x00
#घोषणा L2CAP_SERV_BESTEFFORT	0x01
#घोषणा L2CAP_SERV_GUARANTEED	0x02

#घोषणा L2CAP_BESTEFFORT_ID	0x01

काष्ठा l2cap_disconn_req अणु
	__le16     dcid;
	__le16     scid;
पूर्ण __packed;

काष्ठा l2cap_disconn_rsp अणु
	__le16     dcid;
	__le16     scid;
पूर्ण __packed;

काष्ठा l2cap_info_req अणु
	__le16      type;
पूर्ण __packed;

काष्ठा l2cap_info_rsp अणु
	__le16      type;
	__le16      result;
	__u8        data[];
पूर्ण __packed;

काष्ठा l2cap_create_chan_req अणु
	__le16      psm;
	__le16      scid;
	__u8        amp_id;
पूर्ण __packed;

काष्ठा l2cap_create_chan_rsp अणु
	__le16      dcid;
	__le16      scid;
	__le16      result;
	__le16      status;
पूर्ण __packed;

काष्ठा l2cap_move_chan_req अणु
	__le16      icid;
	__u8        dest_amp_id;
पूर्ण __packed;

काष्ठा l2cap_move_chan_rsp अणु
	__le16      icid;
	__le16      result;
पूर्ण __packed;

#घोषणा L2CAP_MR_SUCCESS	0x0000
#घोषणा L2CAP_MR_PEND		0x0001
#घोषणा L2CAP_MR_BAD_ID		0x0002
#घोषणा L2CAP_MR_SAME_ID	0x0003
#घोषणा L2CAP_MR_NOT_SUPP	0x0004
#घोषणा L2CAP_MR_COLLISION	0x0005
#घोषणा L2CAP_MR_NOT_ALLOWED	0x0006

काष्ठा l2cap_move_chan_cfm अणु
	__le16      icid;
	__le16      result;
पूर्ण __packed;

#घोषणा L2CAP_MC_CONFIRMED	0x0000
#घोषणा L2CAP_MC_UNCONFIRMED	0x0001

काष्ठा l2cap_move_chan_cfm_rsp अणु
	__le16      icid;
पूर्ण __packed;

/* info type */
#घोषणा L2CAP_IT_CL_MTU		0x0001
#घोषणा L2CAP_IT_FEAT_MASK	0x0002
#घोषणा L2CAP_IT_FIXED_CHAN	0x0003

/* info result */
#घोषणा L2CAP_IR_SUCCESS	0x0000
#घोषणा L2CAP_IR_NOTSUPP	0x0001

काष्ठा l2cap_conn_param_update_req अणु
	__le16      min;
	__le16      max;
	__le16      latency;
	__le16      to_multiplier;
पूर्ण __packed;

काष्ठा l2cap_conn_param_update_rsp अणु
	__le16      result;
पूर्ण __packed;

/* Connection Parameters result */
#घोषणा L2CAP_CONN_PARAM_ACCEPTED	0x0000
#घोषणा L2CAP_CONN_PARAM_REJECTED	0x0001

काष्ठा l2cap_le_conn_req अणु
	__le16     psm;
	__le16     scid;
	__le16     mtu;
	__le16     mps;
	__le16     credits;
पूर्ण __packed;

काष्ठा l2cap_le_conn_rsp अणु
	__le16     dcid;
	__le16     mtu;
	__le16     mps;
	__le16     credits;
	__le16     result;
पूर्ण __packed;

काष्ठा l2cap_le_credits अणु
	__le16     cid;
	__le16     credits;
पूर्ण __packed;

#घोषणा L2CAP_ECRED_MIN_MTU		64
#घोषणा L2CAP_ECRED_MIN_MPS		64
#घोषणा L2CAP_ECRED_MAX_CID		5

काष्ठा l2cap_ecred_conn_req अणु
	__le16 psm;
	__le16 mtu;
	__le16 mps;
	__le16 credits;
	__le16 scid[];
पूर्ण __packed;

काष्ठा l2cap_ecred_conn_rsp अणु
	__le16 mtu;
	__le16 mps;
	__le16 credits;
	__le16 result;
	__le16 dcid[];
पूर्ण;

काष्ठा l2cap_ecred_reconf_req अणु
	__le16 mtu;
	__le16 mps;
	__le16 scid[];
पूर्ण __packed;

#घोषणा L2CAP_RECONF_SUCCESS		0x0000
#घोषणा L2CAP_RECONF_INVALID_MTU	0x0001
#घोषणा L2CAP_RECONF_INVALID_MPS	0x0002

काष्ठा l2cap_ecred_reconf_rsp अणु
	__le16 result;
पूर्ण __packed;

/* ----- L2CAP channels and connections ----- */
काष्ठा l2cap_seq_list अणु
	__u16	head;
	__u16	tail;
	__u16	mask;
	__u16	*list;
पूर्ण;

#घोषणा L2CAP_SEQ_LIST_CLEAR	0xFFFF
#घोषणा L2CAP_SEQ_LIST_TAIL	0x8000

काष्ठा l2cap_chan अणु
	काष्ठा l2cap_conn	*conn;
	काष्ठा hci_conn		*hs_hcon;
	काष्ठा hci_chan		*hs_hchan;
	काष्ठा kref	kref;
	atomic_t	nesting;

	__u8		state;

	bdaddr_t	dst;
	__u8		dst_type;
	bdaddr_t	src;
	__u8		src_type;
	__le16		psm;
	__le16		sport;
	__u16		dcid;
	__u16		scid;

	__u16		imtu;
	__u16		omtu;
	__u16		flush_to;
	__u8		mode;
	__u8		chan_type;
	__u8		chan_policy;

	__u8		sec_level;

	__u8		ident;

	__u8		conf_req[64];
	__u8		conf_len;
	__u8		num_conf_req;
	__u8		num_conf_rsp;

	__u8		fcs;

	__u16		tx_win;
	__u16		tx_win_max;
	__u16		ack_win;
	__u8		max_tx;
	__u16		retrans_समयout;
	__u16		monitor_समयout;
	__u16		mps;

	__u16		tx_credits;
	__u16		rx_credits;

	__u8		tx_state;
	__u8		rx_state;

	अचिन्हित दीर्घ	conf_state;
	अचिन्हित दीर्घ	conn_state;
	अचिन्हित दीर्घ	flags;

	__u8		remote_amp_id;
	__u8		local_amp_id;
	__u8		move_id;
	__u8		move_state;
	__u8		move_role;

	__u16		next_tx_seq;
	__u16		expected_ack_seq;
	__u16		expected_tx_seq;
	__u16		buffer_seq;
	__u16		srej_save_reqseq;
	__u16		last_acked_seq;
	__u16		frames_sent;
	__u16		unacked_frames;
	__u8		retry_count;
	__u16		sdu_len;
	काष्ठा sk_buff	*sdu;
	काष्ठा sk_buff	*sdu_last_frag;

	__u16		remote_tx_win;
	__u8		remote_max_tx;
	__u16		remote_mps;

	__u8		local_id;
	__u8		local_stype;
	__u16		local_msdu;
	__u32		local_sdu_iसमय;
	__u32		local_acc_lat;
	__u32		local_flush_to;

	__u8		remote_id;
	__u8		remote_stype;
	__u16		remote_msdu;
	__u32		remote_sdu_iसमय;
	__u32		remote_acc_lat;
	__u32		remote_flush_to;

	काष्ठा delayed_work	chan_समयr;
	काष्ठा delayed_work	retrans_समयr;
	काष्ठा delayed_work	monitor_समयr;
	काष्ठा delayed_work	ack_समयr;

	काष्ठा sk_buff		*tx_send_head;
	काष्ठा sk_buff_head	tx_q;
	काष्ठा sk_buff_head	srej_q;
	काष्ठा l2cap_seq_list	srej_list;
	काष्ठा l2cap_seq_list	retrans_list;

	काष्ठा list_head	list;
	काष्ठा list_head	global_l;

	व्योम			*data;
	स्थिर काष्ठा l2cap_ops	*ops;
	काष्ठा mutex		lock;
पूर्ण;

काष्ठा l2cap_ops अणु
	अक्षर			*name;

	काष्ठा l2cap_chan	*(*new_connection) (काष्ठा l2cap_chan *chan);
	पूर्णांक			(*recv) (काष्ठा l2cap_chan * chan,
					 काष्ठा sk_buff *skb);
	व्योम			(*tearकरोwn) (काष्ठा l2cap_chan *chan, पूर्णांक err);
	व्योम			(*बंद) (काष्ठा l2cap_chan *chan);
	व्योम			(*state_change) (काष्ठा l2cap_chan *chan,
						 पूर्णांक state, पूर्णांक err);
	व्योम			(*पढ़ोy) (काष्ठा l2cap_chan *chan);
	व्योम			(*defer) (काष्ठा l2cap_chan *chan);
	व्योम			(*resume) (काष्ठा l2cap_chan *chan);
	व्योम			(*suspend) (काष्ठा l2cap_chan *chan);
	व्योम			(*set_shutकरोwn) (काष्ठा l2cap_chan *chan);
	दीर्घ			(*get_sndसमयo) (काष्ठा l2cap_chan *chan);
	काष्ठा pid		*(*get_peer_pid) (काष्ठा l2cap_chan *chan);
	काष्ठा sk_buff		*(*alloc_skb) (काष्ठा l2cap_chan *chan,
					       अचिन्हित दीर्घ hdr_len,
					       अचिन्हित दीर्घ len, पूर्णांक nb);
	पूर्णांक			(*filter) (काष्ठा l2cap_chan * chan,
					   काष्ठा sk_buff *skb);
पूर्ण;

काष्ठा l2cap_conn अणु
	काष्ठा hci_conn		*hcon;
	काष्ठा hci_chan		*hchan;

	अचिन्हित पूर्णांक		mtu;

	__u32			feat_mask;
	__u8			remote_fixed_chan;
	__u8			local_fixed_chan;

	__u8			info_state;
	__u8			info_ident;

	काष्ठा delayed_work	info_समयr;

	काष्ठा sk_buff		*rx_skb;
	__u32			rx_len;
	__u8			tx_ident;
	काष्ठा mutex		ident_lock;

	काष्ठा sk_buff_head	pending_rx;
	काष्ठा work_काष्ठा	pending_rx_work;

	काष्ठा work_काष्ठा	id_addr_update_work;

	__u8			disc_reason;

	काष्ठा l2cap_chan	*smp;

	काष्ठा list_head	chan_l;
	काष्ठा mutex		chan_lock;
	काष्ठा kref		ref;
	काष्ठा list_head	users;
पूर्ण;

काष्ठा l2cap_user अणु
	काष्ठा list_head list;
	पूर्णांक (*probe) (काष्ठा l2cap_conn *conn, काष्ठा l2cap_user *user);
	व्योम (*हटाओ) (काष्ठा l2cap_conn *conn, काष्ठा l2cap_user *user);
पूर्ण;

#घोषणा L2CAP_INFO_CL_MTU_REQ_SENT	0x01
#घोषणा L2CAP_INFO_FEAT_MASK_REQ_SENT	0x04
#घोषणा L2CAP_INFO_FEAT_MASK_REQ_DONE	0x08

#घोषणा L2CAP_CHAN_RAW			1
#घोषणा L2CAP_CHAN_CONN_LESS		2
#घोषणा L2CAP_CHAN_CONN_ORIENTED	3
#घोषणा L2CAP_CHAN_FIXED		4

/* ----- L2CAP socket info ----- */
#घोषणा l2cap_pi(sk) ((काष्ठा l2cap_pinfo *) sk)

काष्ठा l2cap_pinfo अणु
	काष्ठा bt_sock		bt;
	काष्ठा l2cap_chan	*chan;
	काष्ठा sk_buff		*rx_busy_skb;
पूर्ण;

क्रमागत अणु
	CONF_REQ_SENT,
	CONF_INPUT_DONE,
	CONF_OUTPUT_DONE,
	CONF_MTU_DONE,
	CONF_MODE_DONE,
	CONF_CONNECT_PEND,
	CONF_RECV_NO_FCS,
	CONF_STATE2_DEVICE,
	CONF_EWS_RECV,
	CONF_LOC_CONF_PEND,
	CONF_REM_CONF_PEND,
	CONF_NOT_COMPLETE,
पूर्ण;

#घोषणा L2CAP_CONF_MAX_CONF_REQ 2
#घोषणा L2CAP_CONF_MAX_CONF_RSP 2

क्रमागत अणु
	CONN_SREJ_SENT,
	CONN_WAIT_F,
	CONN_SREJ_ACT,
	CONN_SEND_PBIT,
	CONN_REMOTE_BUSY,
	CONN_LOCAL_BUSY,
	CONN_REJ_ACT,
	CONN_SEND_FBIT,
	CONN_RNR_SENT,
पूर्ण;

/* Definitions क्रम flags in l2cap_chan */
क्रमागत अणु
	FLAG_ROLE_SWITCH,
	FLAG_FORCE_ACTIVE,
	FLAG_FORCE_RELIABLE,
	FLAG_FLUSHABLE,
	FLAG_EXT_CTRL,
	FLAG_EFS_ENABLE,
	FLAG_DEFER_SETUP,
	FLAG_LE_CONN_REQ_SENT,
	FLAG_ECRED_CONN_REQ_SENT,
	FLAG_PENDING_SECURITY,
	FLAG_HOLD_HCI_CONN,
पूर्ण;

/* Lock nesting levels क्रम L2CAP channels. We need these because lockdep
 * otherwise considers all channels equal and will e.g. complain about a
 * connection oriented channel triggering SMP procedures or a listening
 * channel creating and locking a child channel.
 */
क्रमागत अणु
	L2CAP_NESTING_SMP,
	L2CAP_NESTING_NORMAL,
	L2CAP_NESTING_PARENT,
पूर्ण;

क्रमागत अणु
	L2CAP_TX_STATE_XMIT,
	L2CAP_TX_STATE_WAIT_F,
पूर्ण;

क्रमागत अणु
	L2CAP_RX_STATE_RECV,
	L2CAP_RX_STATE_SREJ_SENT,
	L2CAP_RX_STATE_MOVE,
	L2CAP_RX_STATE_WAIT_P,
	L2CAP_RX_STATE_WAIT_F,
पूर्ण;

क्रमागत अणु
	L2CAP_TXSEQ_EXPECTED,
	L2CAP_TXSEQ_EXPECTED_SREJ,
	L2CAP_TXSEQ_UNEXPECTED,
	L2CAP_TXSEQ_UNEXPECTED_SREJ,
	L2CAP_TXSEQ_DUPLICATE,
	L2CAP_TXSEQ_DUPLICATE_SREJ,
	L2CAP_TXSEQ_INVALID,
	L2CAP_TXSEQ_INVALID_IGNORE,
पूर्ण;

क्रमागत अणु
	L2CAP_EV_DATA_REQUEST,
	L2CAP_EV_LOCAL_BUSY_DETECTED,
	L2CAP_EV_LOCAL_BUSY_CLEAR,
	L2CAP_EV_RECV_REQSEQ_AND_FBIT,
	L2CAP_EV_RECV_FBIT,
	L2CAP_EV_RETRANS_TO,
	L2CAP_EV_MONITOR_TO,
	L2CAP_EV_EXPLICIT_POLL,
	L2CAP_EV_RECV_IFRAME,
	L2CAP_EV_RECV_RR,
	L2CAP_EV_RECV_REJ,
	L2CAP_EV_RECV_RNR,
	L2CAP_EV_RECV_SREJ,
	L2CAP_EV_RECV_FRAME,
पूर्ण;

क्रमागत अणु
	L2CAP_MOVE_ROLE_NONE,
	L2CAP_MOVE_ROLE_INITIATOR,
	L2CAP_MOVE_ROLE_RESPONDER,
पूर्ण;

क्रमागत अणु
	L2CAP_MOVE_STABLE,
	L2CAP_MOVE_WAIT_REQ,
	L2CAP_MOVE_WAIT_RSP,
	L2CAP_MOVE_WAIT_RSP_SUCCESS,
	L2CAP_MOVE_WAIT_CONFIRM,
	L2CAP_MOVE_WAIT_CONFIRM_RSP,
	L2CAP_MOVE_WAIT_LOGICAL_COMP,
	L2CAP_MOVE_WAIT_LOGICAL_CFM,
	L2CAP_MOVE_WAIT_LOCAL_BUSY,
	L2CAP_MOVE_WAIT_PREPARE,
पूर्ण;

व्योम l2cap_chan_hold(काष्ठा l2cap_chan *c);
व्योम l2cap_chan_put(काष्ठा l2cap_chan *c);

अटल अंतरभूत व्योम l2cap_chan_lock(काष्ठा l2cap_chan *chan)
अणु
	mutex_lock_nested(&chan->lock, atomic_पढ़ो(&chan->nesting));
पूर्ण

अटल अंतरभूत व्योम l2cap_chan_unlock(काष्ठा l2cap_chan *chan)
अणु
	mutex_unlock(&chan->lock);
पूर्ण

अटल अंतरभूत व्योम l2cap_set_समयr(काष्ठा l2cap_chan *chan,
				   काष्ठा delayed_work *work, दीर्घ समयout)
अणु
	BT_DBG("chan %p state %s timeout %ld", chan,
	       state_to_string(chan->state), समयout);

	/* If delayed work cancelled करो not hold(chan)
	   since it is alपढ़ोy करोne with previous set_समयr */
	अगर (!cancel_delayed_work(work))
		l2cap_chan_hold(chan);

	schedule_delayed_work(work, समयout);
पूर्ण

अटल अंतरभूत bool l2cap_clear_समयr(काष्ठा l2cap_chan *chan,
				     काष्ठा delayed_work *work)
अणु
	bool ret;

	/* put(chan) अगर delayed work cancelled otherwise it
	   is करोne in delayed work function */
	ret = cancel_delayed_work(work);
	अगर (ret)
		l2cap_chan_put(chan);

	वापस ret;
पूर्ण

#घोषणा __set_chan_समयr(c, t) l2cap_set_समयr(c, &c->chan_समयr, (t))
#घोषणा __clear_chan_समयr(c) l2cap_clear_समयr(c, &c->chan_समयr)
#घोषणा __clear_retrans_समयr(c) l2cap_clear_समयr(c, &c->retrans_समयr)
#घोषणा __clear_monitor_समयr(c) l2cap_clear_समयr(c, &c->monitor_समयr)
#घोषणा __set_ack_समयr(c) l2cap_set_समयr(c, &chan->ack_समयr, \
		msecs_to_jअगरfies(L2CAP_DEFAULT_ACK_TO));
#घोषणा __clear_ack_समयr(c) l2cap_clear_समयr(c, &c->ack_समयr)

अटल अंतरभूत पूर्णांक __seq_offset(काष्ठा l2cap_chan *chan, __u16 seq1, __u16 seq2)
अणु
	अगर (seq1 >= seq2)
		वापस seq1 - seq2;
	अन्यथा
		वापस chan->tx_win_max + 1 - seq2 + seq1;
पूर्ण

अटल अंतरभूत __u16 __next_seq(काष्ठा l2cap_chan *chan, __u16 seq)
अणु
	वापस (seq + 1) % (chan->tx_win_max + 1);
पूर्ण

अटल अंतरभूत काष्ठा l2cap_chan *l2cap_chan_no_new_connection(काष्ठा l2cap_chan *chan)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक l2cap_chan_no_recv(काष्ठा l2cap_chan *chan, काष्ठा sk_buff *skb)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *l2cap_chan_no_alloc_skb(काष्ठा l2cap_chan *chan,
						      अचिन्हित दीर्घ hdr_len,
						      अचिन्हित दीर्घ len, पूर्णांक nb)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

अटल अंतरभूत व्योम l2cap_chan_no_tearकरोwn(काष्ठा l2cap_chan *chan, पूर्णांक err)
अणु
पूर्ण

अटल अंतरभूत व्योम l2cap_chan_no_बंद(काष्ठा l2cap_chan *chan)
अणु
पूर्ण

अटल अंतरभूत व्योम l2cap_chan_no_पढ़ोy(काष्ठा l2cap_chan *chan)
अणु
पूर्ण

अटल अंतरभूत व्योम l2cap_chan_no_state_change(काष्ठा l2cap_chan *chan,
					      पूर्णांक state, पूर्णांक err)
अणु
पूर्ण

अटल अंतरभूत व्योम l2cap_chan_no_defer(काष्ठा l2cap_chan *chan)
अणु
पूर्ण

अटल अंतरभूत व्योम l2cap_chan_no_suspend(काष्ठा l2cap_chan *chan)
अणु
पूर्ण

अटल अंतरभूत व्योम l2cap_chan_no_resume(काष्ठा l2cap_chan *chan)
अणु
पूर्ण

अटल अंतरभूत व्योम l2cap_chan_no_set_shutकरोwn(काष्ठा l2cap_chan *chan)
अणु
पूर्ण

अटल अंतरभूत दीर्घ l2cap_chan_no_get_sndसमयo(काष्ठा l2cap_chan *chan)
अणु
	वापस 0;
पूर्ण

बाह्य bool disable_erपंचांग;
बाह्य bool enable_ecred;

पूर्णांक l2cap_init_sockets(व्योम);
व्योम l2cap_cleanup_sockets(व्योम);
bool l2cap_is_socket(काष्ठा socket *sock);

व्योम __l2cap_le_connect_rsp_defer(काष्ठा l2cap_chan *chan);
व्योम __l2cap_ecred_conn_rsp_defer(काष्ठा l2cap_chan *chan);
व्योम __l2cap_connect_rsp_defer(काष्ठा l2cap_chan *chan);

पूर्णांक l2cap_add_psm(काष्ठा l2cap_chan *chan, bdaddr_t *src, __le16 psm);
पूर्णांक l2cap_add_scid(काष्ठा l2cap_chan *chan,  __u16 scid);

काष्ठा l2cap_chan *l2cap_chan_create(व्योम);
व्योम l2cap_chan_बंद(काष्ठा l2cap_chan *chan, पूर्णांक reason);
पूर्णांक l2cap_chan_connect(काष्ठा l2cap_chan *chan, __le16 psm, u16 cid,
		       bdaddr_t *dst, u8 dst_type);
पूर्णांक l2cap_chan_reconfigure(काष्ठा l2cap_chan *chan, __u16 mtu);
पूर्णांक l2cap_chan_send(काष्ठा l2cap_chan *chan, काष्ठा msghdr *msg, माप_प्रकार len);
व्योम l2cap_chan_busy(काष्ठा l2cap_chan *chan, पूर्णांक busy);
पूर्णांक l2cap_chan_check_security(काष्ठा l2cap_chan *chan, bool initiator);
व्योम l2cap_chan_set_शेषs(काष्ठा l2cap_chan *chan);
पूर्णांक l2cap_erपंचांग_init(काष्ठा l2cap_chan *chan);
व्योम l2cap_chan_add(काष्ठा l2cap_conn *conn, काष्ठा l2cap_chan *chan);
व्योम __l2cap_chan_add(काष्ठा l2cap_conn *conn, काष्ठा l2cap_chan *chan);
प्रकार व्योम (*l2cap_chan_func_t)(काष्ठा l2cap_chan *chan, व्योम *data);
व्योम l2cap_chan_list(काष्ठा l2cap_conn *conn, l2cap_chan_func_t func,
		     व्योम *data);
व्योम l2cap_chan_del(काष्ठा l2cap_chan *chan, पूर्णांक err);
व्योम l2cap_send_conn_req(काष्ठा l2cap_chan *chan);
व्योम l2cap_move_start(काष्ठा l2cap_chan *chan);
व्योम l2cap_logical_cfm(काष्ठा l2cap_chan *chan, काष्ठा hci_chan *hchan,
		       u8 status);
व्योम __l2cap_physical_cfm(काष्ठा l2cap_chan *chan, पूर्णांक result);

काष्ठा l2cap_conn *l2cap_conn_get(काष्ठा l2cap_conn *conn);
व्योम l2cap_conn_put(काष्ठा l2cap_conn *conn);

पूर्णांक l2cap_रेजिस्टर_user(काष्ठा l2cap_conn *conn, काष्ठा l2cap_user *user);
व्योम l2cap_unरेजिस्टर_user(काष्ठा l2cap_conn *conn, काष्ठा l2cap_user *user);

#पूर्ण_अगर /* __L2CAP_H */
