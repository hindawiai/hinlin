<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/
#अगर_अघोषित _RTL8712_RECV_H_
#घोषणा _RTL8712_RECV_H_

#समावेश "osdep_service.h"
#समावेश "drv_types.h"

/* Realtek's v2.6.6 reduced this to 4. However, under heavy network and CPU
 * loads, even 8 receive buffers might not be enough; cutting it to 4 seemed
 * unwise.
 */
#घोषणा NR_RECVBUFF (8)

#घोषणा NR_PREALLOC_RECV_SKB (8)
#घोषणा RXDESC_SIZE	24
#घोषणा RXDESC_OFFSET RXDESC_SIZE
#घोषणा RECV_BLK_SZ 512
#घोषणा RECV_BLK_CNT 16
#घोषणा RECV_BLK_TH RECV_BLK_CNT
#घोषणा MAX_RECVBUF_SZ 9100
#घोषणा RECVBUFF_ALIGN_SZ 512
#घोषणा RSVD_ROOM_SZ (0)
/*These definition is used क्रम Rx packet reordering.*/
#घोषणा SN_LESS(a, b)		(((a-b) & 0x800) != 0)
#घोषणा SN_EQUAL(a, b)	(a == b)
#घोषणा REORDER_WAIT_TIME	30 /* (ms)*/

काष्ठा recv_stat अणु
	__le32 rxdw0;
	__le32 rxdw1;
	__le32 rxdw2;
	__le32 rxdw3;
	__le32 rxdw4;
	__le32 rxdw5;
पूर्ण;

काष्ठा phy_cck_rx_status अणु
	/* For CCK rate descriptor. This is a अचिन्हित 8:1 variable.
	 * LSB bit present 0.5. And MSB 7 bts present a चिन्हित value.
	 * Range from -64~+63.5.
	 */
	u8	adc_pwdb_X[4];
	u8	sq_rpt;
	u8	cck_agc_rpt;
पूर्ण;

काष्ठा phy_stat अणु
	__le32 phydw0;
	__le32 phydw1;
	__le32 phydw2;
	__le32 phydw3;
	__le32 phydw4;
	__le32 phydw5;
	__le32 phydw6;
	__le32 phydw7;
पूर्ण;

#घोषणा PHY_STAT_GAIN_TRSW_SHT 0
#घोषणा PHY_STAT_PWDB_ALL_SHT 4
#घोषणा PHY_STAT_CFOSHO_SHT 5
#घोषणा PHY_STAT_CCK_AGC_RPT_SHT 5
#घोषणा PHY_STAT_CFOTAIL_SHT 9
#घोषणा PHY_STAT_RXEVM_SHT 13
#घोषणा PHY_STAT_RXSNR_SHT 15
#घोषणा PHY_STAT_PDSNR_SHT 19
#घोषणा PHY_STAT_CSI_CURRENT_SHT 21
#घोषणा PHY_STAT_CSI_TARGET_SHT 23
#घोषणा PHY_STAT_SIGEVM_SHT 25
#घोषणा PHY_STAT_MAX_EX_PWR_SHT 26

जोड़ recvstat अणु
	काष्ठा recv_stat recv_stat;
	अचिन्हित पूर्णांक value[RXDESC_SIZE>>2];
पूर्ण;

काष्ठा recv_buf अणु
	काष्ठा list_head list;
	spinlock_t recvbuf_lock;
	u32	ref_cnt;
	काष्ठा _adapter  *adapter;
	काष्ठा urb *purb;
	_pkt *pskb;
	u8  irp_pending;
	u32  transfer_len;
	uपूर्णांक  len;
	u8 *phead;
	u8 *pdata;
	u8 *ptail;
	u8 *pend;
	u8 *pbuf;
	u8 *pallocated_buf;
पूर्ण;

/*
 *	head  ----->
 *		data  ----->
 *			payload
 *		tail  ----->
 *	end   ----->
 *	len = (अचिन्हित पूर्णांक )(tail - data);
 */
काष्ठा recv_frame_hdr अणु
	काष्ठा list_head list;
	_pkt	*pkt;
	_pkt *pkt_newalloc;
	काष्ठा _adapter  *adapter;
	u8 fragcnt;
	काष्ठा rx_pkt_attrib attrib;
	uपूर्णांक  len;
	u8 *rx_head;
	u8 *rx_data;
	u8 *rx_tail;
	u8 *rx_end;
	व्योम *precvbuf;
	काष्ठा sta_info *psta;
	/*क्रम A-MPDU Rx reordering buffer control*/
	काष्ठा recv_reorder_ctrl *preorder_ctrl;
पूर्ण;

जोड़ recv_frame अणु
	जोड़ अणु
		काष्ठा list_head list;
		काष्ठा recv_frame_hdr hdr;
	पूर्ण u;
पूर्ण;

व्योम r8712_init_recvbuf(काष्ठा _adapter *padapter, काष्ठा recv_buf *precvbuf);
व्योम r8712_rxcmd_event_hdl(काष्ठा _adapter *padapter, व्योम *prxcmdbuf);
s32 r8712_संकेत_scale_mapping(s32 cur_sig);
व्योम r8712_reordering_ctrl_समयout_handler(व्योम *pcontext);

#पूर्ण_अगर

