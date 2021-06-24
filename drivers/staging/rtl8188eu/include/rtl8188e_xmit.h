<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __RTL8188E_XMIT_H__
#घोषणा __RTL8188E_XMIT_H__

#घोषणा		MAX_TX_AGG_PACKET_NUMBER	0xFF
/*  */
/*  Queue Select Value in TxDesc */
/*  */
#घोषणा QSLT_BK							0x2/* 0x01 */
#घोषणा QSLT_BE							0x0
#घोषणा QSLT_VI							0x5/* 0x4 */
#घोषणा QSLT_VO							0x7/* 0x6 */
#घोषणा QSLT_BEACON						0x10
#घोषणा QSLT_HIGH						0x11
#घोषणा QSLT_MGNT						0x12
#घोषणा QSLT_CMD						0x13

/* For 88e early mode */
#घोषणा SET_EARLYMODE_PKTNUM(__pAddr, __Value)			\
	SET_BITS_TO_LE_4BYTE(__pAddr, 0, 3, __Value)
#घोषणा SET_EARLYMODE_LEN0(__pAddr, __Value)			\
	SET_BITS_TO_LE_4BYTE(__pAddr, 4, 12, __Value)
#घोषणा SET_EARLYMODE_LEN1(__pAddr, __Value)			\
	SET_BITS_TO_LE_4BYTE(__pAddr, 16, 12, __Value)
#घोषणा SET_EARLYMODE_LEN2_1(__pAddr, __Value)			\
	SET_BITS_TO_LE_4BYTE(__pAddr, 28, 4, __Value)
#घोषणा SET_EARLYMODE_LEN2_2(__pAddr, __Value)			\
	SET_BITS_TO_LE_4BYTE(__pAddr + 4, 0, 8, __Value)
#घोषणा SET_EARLYMODE_LEN3(__pAddr, __Value)			\
	SET_BITS_TO_LE_4BYTE(__pAddr + 4, 8, 12, __Value)
#घोषणा SET_EARLYMODE_LEN4(__pAddr, __Value)			\
	SET_BITS_TO_LE_4BYTE(__pAddr + 4, 20, 12, __Value)

/*  */
/* defined क्रम TX DESC Operation */
/*  */

#घोषणा MAX_TID (15)

/* OFFSET 0 */
#घोषणा OFFSET_SZ	0
#घोषणा OFFSET_SHT	16
#घोषणा BMC		BIT(24)
#घोषणा LSG		BIT(26)
#घोषणा FSG		BIT(27)
#घोषणा OWN		BIT(31)

/* OFFSET 4 */
#घोषणा PKT_OFFSET_SZ		0
#घोषणा QSEL_SHT		8
#घोषणा RATE_ID_SHT		16
#घोषणा NAVUSEHDR		BIT(20)
#घोषणा SEC_TYPE_SHT		22
#घोषणा PKT_OFFSET_SHT		26

/* OFFSET 8 */
#घोषणा AGG_EN			BIT(12)
#घोषणा AGG_BK			BIT(16)
#घोषणा AMPDU_DENSITY_SHT	20
#घोषणा ANTSEL_A		BIT(24)
#घोषणा ANTSEL_B		BIT(25)
#घोषणा TX_ANT_CCK_SHT		26
#घोषणा TX_ANTL_SHT		28
#घोषणा TX_ANT_HT_SHT		30

/* OFFSET 12 */
#घोषणा SEQ_SHT			16
#घोषणा EN_HWSEQ		BIT(31)

/* OFFSET 16 */
#घोषणा QOS			BIT(6)
#घोषणा	HW_SSN			BIT(7)
#घोषणा USERATE			BIT(8)
#घोषणा DISDATAFB		BIT(10)
#घोषणा CTS_2_SELF		BIT(11)
#घोषणा	RTS_EN			BIT(12)
#घोषणा	HW_RTS_EN		BIT(13)
#घोषणा DATA_SHORT		BIT(24)
#घोषणा PWR_STATUS_SHT		15
#घोषणा DATA_SC_SHT		20
#घोषणा DATA_BW			BIT(25)

/* OFFSET 20 */
#घोषणा	RTY_LMT_EN		BIT(17)

क्रमागत TXDESC_SC अणु
	SC_DONT_CARE = 0x00,
	SC_UPPER = 0x01,
	SC_LOWER = 0x02,
	SC_DUPLICATE = 0x03
पूर्ण;

/* OFFSET 20 */
#घोषणा SGI			BIT(6)
#घोषणा USB_TXAGG_NUM_SHT	24

#घोषणा txdesc_set_ccx_sw_88e(txdesc, value) \
	करो अणु \
		((काष्ठा txdesc_88e *)(txdesc))->sw1 = (((value) >> 8) & 0x0f); \
		((काष्ठा txdesc_88e *)(txdesc))->sw0 = ((value) & 0xff); \
	पूर्ण जबतक (0)

काष्ठा txrpt_ccx_88e अणु
	/* offset 0 */
	u8 tag1:1;
	u8 pkt_num:3;
	u8 txdma_underflow:1;
	u8 पूर्णांक_bt:1;
	u8 पूर्णांक_tri:1;
	u8 पूर्णांक_ccx:1;

	/* offset 1 */
	u8 mac_id:6;
	u8 pkt_ok:1;
	u8 bmc:1;

	/* offset 2 */
	u8 retry_cnt:6;
	u8 lअगरeसमय_over:1;
	u8 retry_over:1;

	/* offset 3 */
	u8 ccx_qसमय0;
	u8 ccx_qसमय1;

	/* offset 5 */
	u8 final_data_rate;

	/* offset 6 */
	u8 sw1:4;
	u8 qsel:4;

	/* offset 7 */
	u8 sw0;
पूर्ण;

#घोषणा txrpt_ccx_sw_88e(txrpt_ccx) ((txrpt_ccx)->sw0 + ((txrpt_ccx)->sw1 << 8))
#घोषणा txrpt_ccx_qसमय_88e(txrpt_ccx)			\
	((txrpt_ccx)->ccx_qसमय0 + ((txrpt_ccx)->ccx_qसमय1 << 8))

व्योम rtl8188e_fill_fake_txdesc(काष्ठा adapter *padapter, u8 *pDesc,
			       u32 BufferLen, u8 IsPsPoll, u8 IsBTQosNull);
s32 rtl8188eu_init_xmit_priv(काष्ठा adapter *padapter);
s32 rtl8188eu_xmit_buf_handler(काष्ठा adapter *padapter);
#घोषणा hal_xmit_handler rtl8188eu_xmit_buf_handler
व्योम rtl8188eu_xmit_tasklet(काष्ठा tasklet_काष्ठा *t);
bool rtl8188eu_xmitframe_complete(काष्ठा adapter *padapter,
				  काष्ठा xmit_priv *pxmitpriv);

व्योम handle_txrpt_ccx_88e(काष्ठा adapter *adapter, u8 *buf);

व्योम _dbg_dump_tx_info(काष्ठा adapter *padapter, पूर्णांक frame_tag,
		       काष्ठा tx_desc *ptxdesc);

#पूर्ण_अगर /* __RTL8188E_XMIT_H__ */
