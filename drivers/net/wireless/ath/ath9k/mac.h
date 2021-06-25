<शैली गुरु>
/*
 * Copyright (c) 2008-2011 Atheros Communications Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित MAC_H
#घोषणा MAC_H
#समावेश <net/cfg80211.h>

#घोषणा set11nTries(_series, _index) \
	(SM((_series)[_index].Tries, AR_XmitDataTries##_index))

#घोषणा set11nRate(_series, _index) \
	(SM((_series)[_index].Rate, AR_XmitRate##_index))

#घोषणा set11nPktDurRTSCTS(_series, _index)				\
	(SM((_series)[_index].PktDuration, AR_PacketDur##_index) |	\
	 ((_series)[_index].RateFlags & ATH9K_RATESERIES_RTS_CTS   ?	\
	  AR_RTSCTSQual##_index : 0))

#घोषणा set11nRateFlags(_series, _index)				\
	(((_series)[_index].RateFlags & ATH9K_RATESERIES_2040 ?		\
	  AR_2040_##_index : 0)						\
	 |((_series)[_index].RateFlags & ATH9K_RATESERIES_HALFGI ?	\
	   AR_GI##_index : 0)						\
	 |((_series)[_index].RateFlags & ATH9K_RATESERIES_STBC ?	\
	   AR_STBC##_index : 0)						\
	 |SM((_series)[_index].ChSel, AR_ChainSel##_index))

#घोषणा CCK_SIFS_TIME        10
#घोषणा CCK_PREAMBLE_BITS   144
#घोषणा CCK_PLCP_BITS        48

#घोषणा OFDM_SIFS_TIME        16
#घोषणा OFDM_PREAMBLE_TIME    20
#घोषणा OFDM_PLCP_BITS        22
#घोषणा OFDM_SYMBOL_TIME      4

#घोषणा OFDM_SIFS_TIME_HALF     32
#घोषणा OFDM_PREAMBLE_TIME_HALF 40
#घोषणा OFDM_PLCP_BITS_HALF     22
#घोषणा OFDM_SYMBOL_TIME_HALF   8

#घोषणा OFDM_SIFS_TIME_QUARTER      64
#घोषणा OFDM_PREAMBLE_TIME_QUARTER  80
#घोषणा OFDM_PLCP_BITS_QUARTER      22
#घोषणा OFDM_SYMBOL_TIME_QUARTER    16

#घोषणा INIT_AIFS       2
#घोषणा INIT_CWMIN      15
#घोषणा INIT_CWMIN_11B  31
#घोषणा INIT_CWMAX      1023
#घोषणा INIT_SH_RETRY   10
#घोषणा INIT_LG_RETRY   10
#घोषणा INIT_SSH_RETRY  32
#घोषणा INIT_SLG_RETRY  32

#घोषणा ATH9K_TXERR_XRETRY         0x01
#घोषणा ATH9K_TXERR_FILT           0x02
#घोषणा ATH9K_TXERR_FIFO           0x04
#घोषणा ATH9K_TXERR_XTXOP          0x08
#घोषणा ATH9K_TXERR_TIMER_EXPIRED  0x10
#घोषणा ATH9K_TX_ACKED		   0x20
#घोषणा ATH9K_TX_FLUSH		   0x40
#घोषणा ATH9K_TXERR_MASK						\
	(ATH9K_TXERR_XRETRY | ATH9K_TXERR_FILT | ATH9K_TXERR_FIFO |	\
	 ATH9K_TXERR_XTXOP | ATH9K_TXERR_TIMER_EXPIRED | ATH9K_TX_FLUSH)

#घोषणा ATH9K_TX_BA                0x01
#घोषणा ATH9K_TX_PWRMGMT           0x02
#घोषणा ATH9K_TX_DESC_CFG_ERR      0x04
#घोषणा ATH9K_TX_DATA_UNDERRUN     0x08
#घोषणा ATH9K_TX_DELIM_UNDERRUN    0x10
#घोषणा ATH9K_TX_SW_FILTERED       0x80

/* 64 bytes */
#घोषणा MIN_TX_FIFO_THRESHOLD   0x1

/*
 * Single stream device AR9285 and AR9271 require 2 KB
 * to work around a hardware issue, all other devices
 * have can use the max 4 KB limit.
 */
#घोषणा MAX_TX_FIFO_THRESHOLD   ((4096 / 64) - 1)

काष्ठा ath_tx_status अणु
	u32 ts_tstamp;
	u16 ts_seqnum;
	u8 ts_status;
	u8 ts_rateindex;
	पूर्णांक8_t ts_rssi;
	u8 ts_लघुretry;
	u8 ts_दीर्घretry;
	u8 ts_virtcol;
	u8 ts_flags;
	पूर्णांक8_t ts_rssi_ctl0;
	पूर्णांक8_t ts_rssi_ctl1;
	पूर्णांक8_t ts_rssi_ctl2;
	पूर्णांक8_t ts_rssi_ext0;
	पूर्णांक8_t ts_rssi_ext1;
	पूर्णांक8_t ts_rssi_ext2;
	u8 qid;
	u16 desc_id;
	u8 tid;
	u32 ba_low;
	u32 ba_high;
	u32 evm0;
	u32 evm1;
	u32 evm2;
	u32 duration;
पूर्ण;

काष्ठा ath_rx_status अणु
	u32 rs_tstamp;
	u16 rs_datalen;
	u8 rs_status;
	u8 rs_phyerr;
	पूर्णांक8_t rs_rssi;
	u8 rs_keyix;
	u8 rs_rate;
	u8 rs_antenna;
	u8 rs_more;
	पूर्णांक8_t rs_rssi_ctl[3];
	पूर्णांक8_t rs_rssi_ext[3];
	u8 rs_isaggr;
	u8 rs_firstaggr;
	u8 rs_moreaggr;
	u8 rs_num_delims;
	u8 rs_flags;
	bool is_mybeacon;
	u32 evm0;
	u32 evm1;
	u32 evm2;
	u32 evm3;
	u32 evm4;
	u16 enc_flags;
	क्रमागत rate_info_bw bw;
पूर्ण;

काष्ठा ath_htc_rx_status अणु
	__be64 rs_tstamp;
	__be16 rs_datalen;
	u8 rs_status;
	u8 rs_phyerr;
	पूर्णांक8_t rs_rssi;
	पूर्णांक8_t rs_rssi_ctl[3];
	पूर्णांक8_t rs_rssi_ext[3];
	u8 rs_keyix;
	u8 rs_rate;
	u8 rs_antenna;
	u8 rs_more;
	u8 rs_isaggr;
	u8 rs_moreaggr;
	u8 rs_num_delims;
	u8 rs_flags;
	u8 rs_dummy;
	/* FIXME: evm* never used? */
	__be32 evm0;
	__be32 evm1;
	__be32 evm2;
पूर्ण;

#घोषणा ATH9K_RXERR_CRC           0x01
#घोषणा ATH9K_RXERR_PHY           0x02
#घोषणा ATH9K_RXERR_FIFO          0x04
#घोषणा ATH9K_RXERR_DECRYPT       0x08
#घोषणा ATH9K_RXERR_MIC           0x10
#घोषणा ATH9K_RXERR_KEYMISS       0x20
#घोषणा ATH9K_RXERR_CORRUPT_DESC  0x40

#घोषणा ATH9K_RX_MORE             0x01
#घोषणा ATH9K_RX_MORE_AGGR        0x02
#घोषणा ATH9K_RX_GI               0x04
#घोषणा ATH9K_RX_2040             0x08
#घोषणा ATH9K_RX_DELIM_CRC_PRE    0x10
#घोषणा ATH9K_RX_DELIM_CRC_POST   0x20
#घोषणा ATH9K_RX_DECRYPT_BUSY     0x40

#घोषणा ATH9K_RXKEYIX_INVALID	((u8)-1)
#घोषणा ATH9K_TXKEYIX_INVALID	((u8)-1)

क्रमागत ath9k_phyerr अणु
	ATH9K_PHYERR_UNDERRUN             = 0,  /* Transmit underrun */
	ATH9K_PHYERR_TIMING               = 1,  /* Timing error */
	ATH9K_PHYERR_PARITY               = 2,  /* Illegal parity */
	ATH9K_PHYERR_RATE                 = 3,  /* Illegal rate */
	ATH9K_PHYERR_LENGTH               = 4,  /* Illegal length */
	ATH9K_PHYERR_RADAR                = 5,  /* Radar detect */
	ATH9K_PHYERR_SERVICE              = 6,  /* Illegal service */
	ATH9K_PHYERR_TOR                  = 7,  /* Transmit override receive */

	ATH9K_PHYERR_OFDM_TIMING          = 17,
	ATH9K_PHYERR_OFDM_SIGNAL_PARITY   = 18,
	ATH9K_PHYERR_OFDM_RATE_ILLEGAL    = 19,
	ATH9K_PHYERR_OFDM_LENGTH_ILLEGAL  = 20,
	ATH9K_PHYERR_OFDM_POWER_DROP      = 21,
	ATH9K_PHYERR_OFDM_SERVICE         = 22,
	ATH9K_PHYERR_OFDM_RESTART         = 23,

	ATH9K_PHYERR_CCK_BLOCKER          = 24,
	ATH9K_PHYERR_CCK_TIMING           = 25,
	ATH9K_PHYERR_CCK_HEADER_CRC       = 26,
	ATH9K_PHYERR_CCK_RATE_ILLEGAL     = 27,
	ATH9K_PHYERR_CCK_LENGTH_ILLEGAL   = 28,
	ATH9K_PHYERR_CCK_POWER_DROP       = 29,
	ATH9K_PHYERR_CCK_SERVICE          = 30,
	ATH9K_PHYERR_CCK_RESTART          = 31,

	ATH9K_PHYERR_HT_CRC_ERROR         = 32,
	ATH9K_PHYERR_HT_LENGTH_ILLEGAL    = 33,
	ATH9K_PHYERR_HT_RATE_ILLEGAL      = 34,
	ATH9K_PHYERR_HT_ZLF               = 35,

	ATH9K_PHYERR_FALSE_RADAR_EXT      = 36,
	ATH9K_PHYERR_GREEN_FIELD          = 37,
	ATH9K_PHYERR_SPECTRAL             = 38,

	ATH9K_PHYERR_MAX                  = 39,
पूर्ण;

काष्ठा ath_desc अणु
	u32 ds_link;
	u32 ds_data;
	u32 ds_ctl0;
	u32 ds_ctl1;
	u32 ds_hw[20];
	व्योम *ds_vdata;
पूर्ण __packed __aligned(4);

#घोषणा ATH9K_TXDESC_NOACK		0x0002
#घोषणा ATH9K_TXDESC_RTSENA		0x0004
#घोषणा ATH9K_TXDESC_CTSENA		0x0008
/* ATH9K_TXDESC_INTREQ क्रमces a tx पूर्णांकerrupt to be generated क्रम
 * the descriptor its marked on.  We take a tx पूर्णांकerrupt to reap
 * descriptors when the h/w hits an EOL condition or
 * when the descriptor is specअगरically marked to generate
 * an पूर्णांकerrupt with this flag. Descriptors should be
 * marked periodically to insure समयly replenishing of the
 * supply needed क्रम sending frames. Defering पूर्णांकerrupts
 * reduces प्रणाली load and potentially allows more concurrent
 * work to be करोne but अगर करोne to aggressively can cause
 * senders to backup. When the hardware queue is left too
 * large rate control inक्रमmation may also be too out of
 * date. An Alternative क्रम this is TX पूर्णांकerrupt mitigation
 * but this needs more testing. */
#घोषणा ATH9K_TXDESC_INTREQ		0x0010
#घोषणा ATH9K_TXDESC_VEOL		0x0020
#घोषणा ATH9K_TXDESC_EXT_ONLY		0x0040
#घोषणा ATH9K_TXDESC_EXT_AND_CTL	0x0080
#घोषणा ATH9K_TXDESC_VMF		0x0100
#घोषणा ATH9K_TXDESC_FRAG_IS_ON 	0x0200
#घोषणा ATH9K_TXDESC_LOWRXCHAIN		0x0400
#घोषणा ATH9K_TXDESC_LDPC		0x0800
#घोषणा ATH9K_TXDESC_CLRDMASK		0x1000

#घोषणा ATH9K_TXDESC_PAPRD		0x70000
#घोषणा ATH9K_TXDESC_PAPRD_S		16

#घोषणा ATH9K_RXDESC_INTREQ		0x0020

काष्ठा ar5416_desc अणु
	u32 ds_link;
	u32 ds_data;
	u32 ds_ctl0;
	u32 ds_ctl1;
	जोड़ अणु
		काष्ठा अणु
			u32 ctl2;
			u32 ctl3;
			u32 ctl4;
			u32 ctl5;
			u32 ctl6;
			u32 ctl7;
			u32 ctl8;
			u32 ctl9;
			u32 ctl10;
			u32 ctl11;
			u32 status0;
			u32 status1;
			u32 status2;
			u32 status3;
			u32 status4;
			u32 status5;
			u32 status6;
			u32 status7;
			u32 status8;
			u32 status9;
		पूर्ण tx;
		काष्ठा अणु
			u32 status0;
			u32 status1;
			u32 status2;
			u32 status3;
			u32 status4;
			u32 status5;
			u32 status6;
			u32 status7;
			u32 status8;
		पूर्ण rx;
	पूर्ण u;
पूर्ण __packed __aligned(4);

#घोषणा AR5416DESC(_ds)         ((काष्ठा ar5416_desc *)(_ds))
#घोषणा AR5416DESC_CONST(_ds)   ((स्थिर काष्ठा ar5416_desc *)(_ds))

#घोषणा ds_ctl2     u.tx.ctl2
#घोषणा ds_ctl3     u.tx.ctl3
#घोषणा ds_ctl4     u.tx.ctl4
#घोषणा ds_ctl5     u.tx.ctl5
#घोषणा ds_ctl6     u.tx.ctl6
#घोषणा ds_ctl7     u.tx.ctl7
#घोषणा ds_ctl8     u.tx.ctl8
#घोषणा ds_ctl9     u.tx.ctl9
#घोषणा ds_ctl10    u.tx.ctl10
#घोषणा ds_ctl11    u.tx.ctl11

#घोषणा ds_txstatus0    u.tx.status0
#घोषणा ds_txstatus1    u.tx.status1
#घोषणा ds_txstatus2    u.tx.status2
#घोषणा ds_txstatus3    u.tx.status3
#घोषणा ds_txstatus4    u.tx.status4
#घोषणा ds_txstatus5    u.tx.status5
#घोषणा ds_txstatus6    u.tx.status6
#घोषणा ds_txstatus7    u.tx.status7
#घोषणा ds_txstatus8    u.tx.status8
#घोषणा ds_txstatus9    u.tx.status9

#घोषणा ds_rxstatus0    u.rx.status0
#घोषणा ds_rxstatus1    u.rx.status1
#घोषणा ds_rxstatus2    u.rx.status2
#घोषणा ds_rxstatus3    u.rx.status3
#घोषणा ds_rxstatus4    u.rx.status4
#घोषणा ds_rxstatus5    u.rx.status5
#घोषणा ds_rxstatus6    u.rx.status6
#घोषणा ds_rxstatus7    u.rx.status7
#घोषणा ds_rxstatus8    u.rx.status8

#घोषणा AR_FrameLen         0x00000fff
#घोषणा AR_VirtMoreFrag     0x00001000
#घोषणा AR_TxCtlRsvd00      0x0000e000
#घोषणा AR_XmitPower0       0x003f0000
#घोषणा AR_XmitPower0_S     16
#घोषणा AR_XmitPower1	    0x3f000000
#घोषणा AR_XmitPower1_S     24
#घोषणा AR_XmitPower2	    0x3f000000
#घोषणा AR_XmitPower2_S     24
#घोषणा AR_XmitPower3	    0x3f000000
#घोषणा AR_XmitPower3_S     24
#घोषणा AR_RTSEnable        0x00400000
#घोषणा AR_VEOL             0x00800000
#घोषणा AR_ClrDestMask      0x01000000
#घोषणा AR_TxCtlRsvd01      0x1e000000
#घोषणा AR_TxIntrReq        0x20000000
#घोषणा AR_DestIdxValid     0x40000000
#घोषणा AR_CTSEnable        0x80000000

#घोषणा AR_TxMore           0x00001000
#घोषणा AR_DestIdx          0x000fe000
#घोषणा AR_DestIdx_S        13
#घोषणा AR_FrameType        0x00f00000
#घोषणा AR_FrameType_S      20
#घोषणा AR_NoAck            0x01000000
#घोषणा AR_InsertTS         0x02000000
#घोषणा AR_CorruptFCS       0x04000000
#घोषणा AR_ExtOnly          0x08000000
#घोषणा AR_ExtAndCtl        0x10000000
#घोषणा AR_MoreAggr         0x20000000
#घोषणा AR_IsAggr           0x40000000

#घोषणा AR_BurstDur         0x00007fff
#घोषणा AR_BurstDur_S       0
#घोषणा AR_DurUpdateEna     0x00008000
#घोषणा AR_XmitDataTries0   0x000f0000
#घोषणा AR_XmitDataTries0_S 16
#घोषणा AR_XmitDataTries1   0x00f00000
#घोषणा AR_XmitDataTries1_S 20
#घोषणा AR_XmitDataTries2   0x0f000000
#घोषणा AR_XmitDataTries2_S 24
#घोषणा AR_XmitDataTries3   0xf0000000
#घोषणा AR_XmitDataTries3_S 28

#घोषणा AR_XmitRate0        0x000000ff
#घोषणा AR_XmitRate0_S      0
#घोषणा AR_XmitRate1        0x0000ff00
#घोषणा AR_XmitRate1_S      8
#घोषणा AR_XmitRate2        0x00ff0000
#घोषणा AR_XmitRate2_S      16
#घोषणा AR_XmitRate3        0xff000000
#घोषणा AR_XmitRate3_S      24

#घोषणा AR_PacketDur0       0x00007fff
#घोषणा AR_PacketDur0_S     0
#घोषणा AR_RTSCTSQual0      0x00008000
#घोषणा AR_PacketDur1       0x7fff0000
#घोषणा AR_PacketDur1_S     16
#घोषणा AR_RTSCTSQual1      0x80000000

#घोषणा AR_PacketDur2       0x00007fff
#घोषणा AR_PacketDur2_S     0
#घोषणा AR_RTSCTSQual2      0x00008000
#घोषणा AR_PacketDur3       0x7fff0000
#घोषणा AR_PacketDur3_S     16
#घोषणा AR_RTSCTSQual3      0x80000000

#घोषणा AR_AggrLen          0x0000ffff
#घोषणा AR_AggrLen_S        0
#घोषणा AR_TxCtlRsvd60      0x00030000
#घोषणा AR_PadDelim         0x03fc0000
#घोषणा AR_PadDelim_S       18
#घोषणा AR_EncrType         0x0c000000
#घोषणा AR_EncrType_S       26
#घोषणा AR_TxCtlRsvd61      0xf0000000
#घोषणा AR_LDPC             0x80000000

#घोषणा AR_2040_0           0x00000001
#घोषणा AR_GI0              0x00000002
#घोषणा AR_ChainSel0        0x0000001c
#घोषणा AR_ChainSel0_S      2
#घोषणा AR_2040_1           0x00000020
#घोषणा AR_GI1              0x00000040
#घोषणा AR_ChainSel1        0x00000380
#घोषणा AR_ChainSel1_S      7
#घोषणा AR_2040_2           0x00000400
#घोषणा AR_GI2              0x00000800
#घोषणा AR_ChainSel2        0x00007000
#घोषणा AR_ChainSel2_S      12
#घोषणा AR_2040_3           0x00008000
#घोषणा AR_GI3              0x00010000
#घोषणा AR_ChainSel3        0x000e0000
#घोषणा AR_ChainSel3_S      17
#घोषणा AR_RTSCTSRate       0x0ff00000
#घोषणा AR_RTSCTSRate_S     20
#घोषणा AR_STBC0            0x10000000
#घोषणा AR_STBC1            0x20000000
#घोषणा AR_STBC2            0x40000000
#घोषणा AR_STBC3            0x80000000

#घोषणा AR_TxRSSIAnt00      0x000000ff
#घोषणा AR_TxRSSIAnt00_S    0
#घोषणा AR_TxRSSIAnt01      0x0000ff00
#घोषणा AR_TxRSSIAnt01_S    8
#घोषणा AR_TxRSSIAnt02      0x00ff0000
#घोषणा AR_TxRSSIAnt02_S    16
#घोषणा AR_TxStatusRsvd00   0x3f000000
#घोषणा AR_TxBaStatus       0x40000000
#घोषणा AR_TxStatusRsvd01   0x80000000

/*
 * AR_FrmXmitOK - Frame transmission success flag. If set, the frame was
 * transmitted successfully. If clear, no ACK or BA was received to indicate
 * successful transmission when we were expecting an ACK or BA.
 */
#घोषणा AR_FrmXmitOK            0x00000001
#घोषणा AR_ExcessiveRetries     0x00000002
#घोषणा AR_FIFOUnderrun         0x00000004
#घोषणा AR_Filtered             0x00000008
#घोषणा AR_RTSFailCnt           0x000000f0
#घोषणा AR_RTSFailCnt_S         4
#घोषणा AR_DataFailCnt          0x00000f00
#घोषणा AR_DataFailCnt_S        8
#घोषणा AR_VirtRetryCnt         0x0000f000
#घोषणा AR_VirtRetryCnt_S       12
#घोषणा AR_TxDelimUnderrun      0x00010000
#घोषणा AR_TxDataUnderrun       0x00020000
#घोषणा AR_DescCfgErr           0x00040000
#घोषणा AR_TxTimerExpired       0x00080000
#घोषणा AR_TxStatusRsvd10       0xfff00000

#घोषणा AR_SendTimestamp    ds_txstatus2
#घोषणा AR_BaBiपंचांगapLow      ds_txstatus3
#घोषणा AR_BaBiपंचांगapHigh     ds_txstatus4

#घोषणा AR_TxRSSIAnt10      0x000000ff
#घोषणा AR_TxRSSIAnt10_S    0
#घोषणा AR_TxRSSIAnt11      0x0000ff00
#घोषणा AR_TxRSSIAnt11_S    8
#घोषणा AR_TxRSSIAnt12      0x00ff0000
#घोषणा AR_TxRSSIAnt12_S    16
#घोषणा AR_TxRSSICombined   0xff000000
#घोषणा AR_TxRSSICombined_S 24

#घोषणा AR_TxTid	0xf0000000
#घोषणा AR_TxTid_S	28

#घोषणा AR_TxEVM0           ds_txstatus5
#घोषणा AR_TxEVM1           ds_txstatus6
#घोषणा AR_TxEVM2           ds_txstatus7

#घोषणा AR_TxDone           0x00000001
#घोषणा AR_SeqNum           0x00001ffe
#घोषणा AR_SeqNum_S         1
#घोषणा AR_TxStatusRsvd80   0x0001e000
#घोषणा AR_TxOpExceeded     0x00020000
#घोषणा AR_TxStatusRsvd81   0x001c0000
#घोषणा AR_FinalTxIdx       0x00600000
#घोषणा AR_FinalTxIdx_S     21
#घोषणा AR_TxStatusRsvd82   0x01800000
#घोषणा AR_PowerMgmt        0x02000000
#घोषणा AR_TxStatusRsvd83   0xfc000000

#घोषणा AR_RxCTLRsvd00  0xffffffff

#घोषणा AR_RxCtlRsvd00  0x00001000
#घोषणा AR_RxIntrReq    0x00002000
#घोषणा AR_RxCtlRsvd01  0xffffc000

#घोषणा AR_RxRSSIAnt00      0x000000ff
#घोषणा AR_RxRSSIAnt00_S    0
#घोषणा AR_RxRSSIAnt01      0x0000ff00
#घोषणा AR_RxRSSIAnt01_S    8
#घोषणा AR_RxRSSIAnt02      0x00ff0000
#घोषणा AR_RxRSSIAnt02_S    16
#घोषणा AR_RxRate           0xff000000
#घोषणा AR_RxRate_S         24
#घोषणा AR_RxStatusRsvd00   0xff000000

#घोषणा AR_DataLen          0x00000fff
#घोषणा AR_RxMore           0x00001000
#घोषणा AR_NumDelim         0x003fc000
#घोषणा AR_NumDelim_S       14
#घोषणा AR_RxStatusRsvd10   0xff800000

#घोषणा AR_RcvTimestamp     ds_rxstatus2

#घोषणा AR_GI               0x00000001
#घोषणा AR_2040             0x00000002
#घोषणा AR_Parallel40       0x00000004
#घोषणा AR_Parallel40_S     2
#घोषणा AR_STBC             0x00000008 /* on ar9280 and later */
#घोषणा AR_RxStatusRsvd30   0x000000f0
#घोषणा AR_RxAntenna	    0xffffff00
#घोषणा AR_RxAntenna_S	    8

#घोषणा AR_RxRSSIAnt10            0x000000ff
#घोषणा AR_RxRSSIAnt10_S          0
#घोषणा AR_RxRSSIAnt11            0x0000ff00
#घोषणा AR_RxRSSIAnt11_S          8
#घोषणा AR_RxRSSIAnt12            0x00ff0000
#घोषणा AR_RxRSSIAnt12_S          16
#घोषणा AR_RxRSSICombined         0xff000000
#घोषणा AR_RxRSSICombined_S       24

#घोषणा AR_RxEVM0           ds_rxstatus4
#घोषणा AR_RxEVM1           ds_rxstatus5
#घोषणा AR_RxEVM2           ds_rxstatus6

#घोषणा AR_RxDone           0x00000001
#घोषणा AR_RxFrameOK        0x00000002
#घोषणा AR_CRCErr           0x00000004
#घोषणा AR_DecryptCRCErr    0x00000008
#घोषणा AR_PHYErr           0x00000010
#घोषणा AR_MichaelErr       0x00000020
#घोषणा AR_PreDelimCRCErr   0x00000040
#घोषणा AR_RxStatusRsvd70   0x00000080
#घोषणा AR_RxKeyIdxValid    0x00000100
#घोषणा AR_KeyIdx           0x0000fe00
#घोषणा AR_KeyIdx_S         9
#घोषणा AR_PHYErrCode       0x0000ff00
#घोषणा AR_PHYErrCode_S     8
#घोषणा AR_RxMoreAggr       0x00010000
#घोषणा AR_RxAggr           0x00020000
#घोषणा AR_PostDelimCRCErr  0x00040000
#घोषणा AR_RxStatusRsvd71   0x3ff80000
#घोषणा AR_RxFirstAggr      0x20000000
#घोषणा AR_DecryptBusyErr   0x40000000
#घोषणा AR_KeyMiss          0x80000000

क्रमागत ath9k_tx_queue अणु
	ATH9K_TX_QUEUE_INACTIVE = 0,
	ATH9K_TX_QUEUE_DATA,
	ATH9K_TX_QUEUE_BEACON,
	ATH9K_TX_QUEUE_CAB,
	ATH9K_TX_QUEUE_UAPSD,
	ATH9K_TX_QUEUE_PSPOLL
पूर्ण;

#घोषणा	ATH9K_NUM_TX_QUEUES 10

/* Used as a queue subtype instead of a WMM AC */
#घोषणा ATH9K_WME_UPSD	4

क्रमागत ath9k_tx_queue_flags अणु
	TXQ_FLAG_TXINT_ENABLE = 0x0001,
	TXQ_FLAG_TXDESCINT_ENABLE = 0x0002,
	TXQ_FLAG_TXEOLINT_ENABLE = 0x0004,
	TXQ_FLAG_TXURNINT_ENABLE = 0x0008,
	TXQ_FLAG_BACKOFF_DISABLE = 0x0010,
	TXQ_FLAG_COMPRESSION_ENABLE = 0x0020,
	TXQ_FLAG_RDYTIME_EXP_POLICY_ENABLE = 0x0040,
	TXQ_FLAG_FRAG_BURST_BACKOFF_ENABLE = 0x0080,
पूर्ण;

#घोषणा ATH9K_TXQ_USEDEFAULT ((u32) -1)
#घोषणा ATH9K_TXQ_USE_LOCKOUT_BKOFF_DIS 0x00000001

#घोषणा ATH9K_DECOMP_MASK_SIZE     128

क्रमागत ath9k_pkt_type अणु
	ATH9K_PKT_TYPE_NORMAL = 0,
	ATH9K_PKT_TYPE_ATIM,
	ATH9K_PKT_TYPE_PSPOLL,
	ATH9K_PKT_TYPE_BEACON,
	ATH9K_PKT_TYPE_PROBE_RESP,
	ATH9K_PKT_TYPE_CHIRP,
	ATH9K_PKT_TYPE_GRP_POLL,
पूर्ण;

काष्ठा ath9k_tx_queue_info अणु
	u32 tqi_ver;
	क्रमागत ath9k_tx_queue tqi_type;
	पूर्णांक tqi_subtype;
	क्रमागत ath9k_tx_queue_flags tqi_qflags;
	u32 tqi_priority;
	u32 tqi_aअगरs;
	u32 tqi_cwmin;
	u32 tqi_cwmax;
	u16 tqi_shretry;
	u16 tqi_lgretry;
	u32 tqi_cbrPeriod;
	u32 tqi_cbrOverflowLimit;
	u32 tqi_burstTime;
	u32 tqi_पढ़ोyTime;
	u32 tqi_physCompBuf;
	u32 tqi_पूर्णांकFlags;
पूर्ण;

क्रमागत ath9k_rx_filter अणु
	ATH9K_RX_FILTER_UCAST = 0x00000001,
	ATH9K_RX_FILTER_MCAST = 0x00000002,
	ATH9K_RX_FILTER_BCAST = 0x00000004,
	ATH9K_RX_FILTER_CONTROL = 0x00000008,
	ATH9K_RX_FILTER_BEACON = 0x00000010,
	ATH9K_RX_FILTER_PROM = 0x00000020,
	ATH9K_RX_FILTER_PROBEREQ = 0x00000080,
	ATH9K_RX_FILTER_PHYERR = 0x00000100,
	ATH9K_RX_FILTER_MYBEACON = 0x00000200,
	ATH9K_RX_FILTER_COMP_BAR = 0x00000400,
	ATH9K_RX_FILTER_COMP_BA = 0x00000800,
	ATH9K_RX_FILTER_UNCOMP_BA_BAR = 0x00001000,
	ATH9K_RX_FILTER_PSPOLL = 0x00004000,
	ATH9K_RX_FILTER_PHYRADAR = 0x00002000,
	ATH9K_RX_FILTER_MCAST_BCAST_ALL = 0x00008000,
	ATH9K_RX_FILTER_CONTROL_WRAPPER = 0x00080000,
	ATH9K_RX_FILTER_4ADDRESS = 0x00100000,
पूर्ण;

#घोषणा ATH9K_RATESERIES_RTS_CTS  0x0001
#घोषणा ATH9K_RATESERIES_2040     0x0002
#घोषणा ATH9K_RATESERIES_HALFGI   0x0004
#घोषणा ATH9K_RATESERIES_STBC     0x0008

काष्ठा ath9k_11n_rate_series अणु
	u32 Tries;
	u32 Rate;
	u32 PktDuration;
	u32 ChSel;
	u32 RateFlags;
पूर्ण;

क्रमागत aggr_type अणु
	AGGR_BUF_NONE,
	AGGR_BUF_FIRST,
	AGGR_BUF_MIDDLE,
	AGGR_BUF_LAST,
पूर्ण;

क्रमागत ath9k_key_type अणु
	ATH9K_KEY_TYPE_CLEAR,
	ATH9K_KEY_TYPE_WEP,
	ATH9K_KEY_TYPE_AES,
	ATH9K_KEY_TYPE_TKIP,
पूर्ण;

काष्ठा ath_tx_info अणु
	u8 qcu;

	bool is_first;
	bool is_last;

	क्रमागत aggr_type aggr;
	u8 ndelim;
	u16 aggr_len;

	dma_addr_t link;
	पूर्णांक pkt_len;
	u32 flags;

	dma_addr_t buf_addr[4];
	पूर्णांक buf_len[4];

	काष्ठा ath9k_11n_rate_series rates[4];
	u8 rtscts_rate;
	bool dur_update;

	क्रमागत ath9k_pkt_type type;
	क्रमागत ath9k_key_type keytype;
	u8 keyix;
	u8 txघातer[4];
पूर्ण;

काष्ठा ath_hw;
काष्ठा ath9k_channel;
क्रमागत ath9k_पूर्णांक;

u32 ath9k_hw_gettxbuf(काष्ठा ath_hw *ah, u32 q);
व्योम ath9k_hw_puttxbuf(काष्ठा ath_hw *ah, u32 q, u32 txdp);
व्योम ath9k_hw_txstart(काष्ठा ath_hw *ah, u32 q);
u32 ath9k_hw_numtxpending(काष्ठा ath_hw *ah, u32 q);
bool ath9k_hw_updatetxtriglevel(काष्ठा ath_hw *ah, bool bIncTrigLevel);
bool ath9k_hw_stop_dma_queue(काष्ठा ath_hw *ah, u32 q);
व्योम ath9k_hw_पात_tx_dma(काष्ठा ath_hw *ah);
bool ath9k_hw_set_txq_props(काष्ठा ath_hw *ah, पूर्णांक q,
			    स्थिर काष्ठा ath9k_tx_queue_info *qinfo);
bool ath9k_hw_get_txq_props(काष्ठा ath_hw *ah, पूर्णांक q,
			    काष्ठा ath9k_tx_queue_info *qinfo);
पूर्णांक ath9k_hw_setuptxqueue(काष्ठा ath_hw *ah, क्रमागत ath9k_tx_queue type,
			  स्थिर काष्ठा ath9k_tx_queue_info *qinfo);
bool ath9k_hw_releasetxqueue(काष्ठा ath_hw *ah, u32 q);
bool ath9k_hw_resettxqueue(काष्ठा ath_hw *ah, u32 q);
पूर्णांक ath9k_hw_rxprocdesc(काष्ठा ath_hw *ah, काष्ठा ath_desc *ds,
			काष्ठा ath_rx_status *rs);
व्योम ath9k_hw_setuprxdesc(काष्ठा ath_hw *ah, काष्ठा ath_desc *ds,
			  u32 size, u32 flags);
bool ath9k_hw_setrxपात(काष्ठा ath_hw *ah, bool set);
व्योम ath9k_hw_putrxbuf(काष्ठा ath_hw *ah, u32 rxdp);
व्योम ath9k_hw_startpcureceive(काष्ठा ath_hw *ah, bool is_scanning);
व्योम ath9k_hw_पातpcurecv(काष्ठा ath_hw *ah);
bool ath9k_hw_stopdmarecv(काष्ठा ath_hw *ah, bool *reset);
पूर्णांक ath9k_hw_beaconq_setup(काष्ठा ath_hw *ah);
व्योम ath9k_hw_set_tx_filter(काष्ठा ath_hw *ah, u8 destidx, bool set);

/* Interrupt Handling */
bool ath9k_hw_पूर्णांकrpend(काष्ठा ath_hw *ah);
व्योम ath9k_hw_set_पूर्णांकerrupts(काष्ठा ath_hw *ah);
व्योम ath9k_hw_enable_पूर्णांकerrupts(काष्ठा ath_hw *ah);
व्योम ath9k_hw_disable_पूर्णांकerrupts(काष्ठा ath_hw *ah);
व्योम ath9k_hw_समाप्त_पूर्णांकerrupts(काष्ठा ath_hw *ah);
व्योम ath9k_hw_resume_पूर्णांकerrupts(काष्ठा ath_hw *ah);

व्योम ar9002_hw_attach_mac_ops(काष्ठा ath_hw *ah);

#पूर्ण_अगर /* MAC_H */
