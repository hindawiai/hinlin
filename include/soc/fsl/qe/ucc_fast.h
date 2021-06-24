<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Internal header file क्रम UCC FAST unit routines.
 *
 * Copyright (C) 2006 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Authors: 	Shlomi Gridish <gridish@मुक्तscale.com>
 * 		Li Yang <leoli@मुक्तscale.com>
 */
#अगर_अघोषित __UCC_FAST_H__
#घोषणा __UCC_FAST_H__

#समावेश <linux/kernel.h>

#समावेश <soc/fsl/qe/immap_qe.h>
#समावेश <soc/fsl/qe/qe.h>

#समावेश <soc/fsl/qe/ucc.h>

/* Receive BD's status and length*/
#घोषणा R_E	0x80000000	/* buffer empty */
#घोषणा R_W	0x20000000	/* wrap bit */
#घोषणा R_I	0x10000000	/* पूर्णांकerrupt on reception */
#घोषणा R_L	0x08000000	/* last */
#घोषणा R_F	0x04000000	/* first */

/* transmit BD's status and length*/
#घोषणा T_R	0x80000000	/* पढ़ोy bit */
#घोषणा T_W	0x20000000	/* wrap bit */
#घोषणा T_I	0x10000000	/* पूर्णांकerrupt on completion */
#घोषणा T_L	0x08000000	/* last */

/* Receive BD's status */
#घोषणा R_E_S	0x8000	/* buffer empty */
#घोषणा R_W_S	0x2000	/* wrap bit */
#घोषणा R_I_S	0x1000	/* पूर्णांकerrupt on reception */
#घोषणा R_L_S	0x0800	/* last */
#घोषणा R_F_S	0x0400	/* first */
#घोषणा R_CM_S	0x0200	/* continuous mode */
#घोषणा R_LG_S  0x0020  /* frame length */
#घोषणा R_NO_S  0x0010  /* nonoctet */
#घोषणा R_AB_S  0x0008  /* पात */
#घोषणा R_CR_S	0x0004	/* crc */
#घोषणा R_OV_S	0x0002	/* overrun */
#घोषणा R_CD_S  0x0001  /* carrier detect */

/* transmit BD's status */
#घोषणा T_R_S	0x8000	/* पढ़ोy bit */
#घोषणा T_W_S	0x2000	/* wrap bit */
#घोषणा T_I_S	0x1000	/* पूर्णांकerrupt on completion */
#घोषणा T_L_S	0x0800	/* last */
#घोषणा T_TC_S	0x0400	/* crc */
#घोषणा T_TM_S	0x0200	/* continuous mode */
#घोषणा T_UN_S  0x0002  /* hdlc underrun */
#घोषणा T_CT_S  0x0001  /* hdlc carrier lost */

/* Rx Data buffer must be 4 bytes aligned in most हालs */
#घोषणा UCC_FAST_RX_ALIGN			4
#घोषणा UCC_FAST_MRBLR_ALIGNMENT		4
#घोषणा UCC_FAST_VIRT_FIFO_REGS_ALIGNMENT	8

/* Sizes */
#घोषणा UCC_FAST_URFS_MIN_VAL				0x88
#घोषणा UCC_FAST_RECEIVE_VIRTUAL_FIFO_SIZE_FUDGE_FACTOR	8

/* ucc_fast_channel_protocol_mode - UCC FAST mode */
क्रमागत ucc_fast_channel_protocol_mode अणु
	UCC_FAST_PROTOCOL_MODE_HDLC = 0x00000000,
	UCC_FAST_PROTOCOL_MODE_RESERVED01 = 0x00000001,
	UCC_FAST_PROTOCOL_MODE_RESERVED_QMC = 0x00000002,
	UCC_FAST_PROTOCOL_MODE_RESERVED02 = 0x00000003,
	UCC_FAST_PROTOCOL_MODE_RESERVED_UART = 0x00000004,
	UCC_FAST_PROTOCOL_MODE_RESERVED03 = 0x00000005,
	UCC_FAST_PROTOCOL_MODE_RESERVED_EX_MAC_1 = 0x00000006,
	UCC_FAST_PROTOCOL_MODE_RESERVED_EX_MAC_2 = 0x00000007,
	UCC_FAST_PROTOCOL_MODE_RESERVED_BISYNC = 0x00000008,
	UCC_FAST_PROTOCOL_MODE_RESERVED04 = 0x00000009,
	UCC_FAST_PROTOCOL_MODE_ATM = 0x0000000A,
	UCC_FAST_PROTOCOL_MODE_RESERVED05 = 0x0000000B,
	UCC_FAST_PROTOCOL_MODE_ETHERNET = 0x0000000C,
	UCC_FAST_PROTOCOL_MODE_RESERVED06 = 0x0000000D,
	UCC_FAST_PROTOCOL_MODE_POS = 0x0000000E,
	UCC_FAST_PROTOCOL_MODE_RESERVED07 = 0x0000000F
पूर्ण;

/* ucc_fast_transparent_txrx - UCC Fast Transparent TX & RX */
क्रमागत ucc_fast_transparent_txrx अणु
	UCC_FAST_GUMR_TRANSPARENT_TTX_TRX_NORMAL = 0x00000000,
	UCC_FAST_GUMR_TRANSPARENT_TTX_TRX_TRANSPARENT = 0x18000000
पूर्ण;

/* UCC fast diagnostic mode */
क्रमागत ucc_fast_diag_mode अणु
	UCC_FAST_DIAGNOSTIC_NORMAL = 0x0,
	UCC_FAST_DIAGNOSTIC_LOCAL_LOOP_BACK = 0x40000000,
	UCC_FAST_DIAGNOSTIC_AUTO_ECHO = 0x80000000,
	UCC_FAST_DIAGNOSTIC_LOOP_BACK_AND_ECHO = 0xC0000000
पूर्ण;

/* UCC fast Sync length (transparent mode only) */
क्रमागत ucc_fast_sync_len अणु
	UCC_FAST_SYNC_LEN_NOT_USED = 0x0,
	UCC_FAST_SYNC_LEN_AUTOMATIC = 0x00004000,
	UCC_FAST_SYNC_LEN_8_BIT = 0x00008000,
	UCC_FAST_SYNC_LEN_16_BIT = 0x0000C000
पूर्ण;

/* UCC fast RTS mode */
क्रमागत ucc_fast_पढ़ोy_to_send अणु
	UCC_FAST_SEND_IDLES_BETWEEN_FRAMES = 0x00000000,
	UCC_FAST_SEND_FLAGS_BETWEEN_FRAMES = 0x00002000
पूर्ण;

/* UCC fast receiver decoding mode */
क्रमागत ucc_fast_rx_decoding_method अणु
	UCC_FAST_RX_ENCODING_NRZ = 0x00000000,
	UCC_FAST_RX_ENCODING_NRZI = 0x00000800,
	UCC_FAST_RX_ENCODING_RESERVED0 = 0x00001000,
	UCC_FAST_RX_ENCODING_RESERVED1 = 0x00001800
पूर्ण;

/* UCC fast transmitter encoding mode */
क्रमागत ucc_fast_tx_encoding_method अणु
	UCC_FAST_TX_ENCODING_NRZ = 0x00000000,
	UCC_FAST_TX_ENCODING_NRZI = 0x00000100,
	UCC_FAST_TX_ENCODING_RESERVED0 = 0x00000200,
	UCC_FAST_TX_ENCODING_RESERVED1 = 0x00000300
पूर्ण;

/* UCC fast CRC length */
क्रमागत ucc_fast_transparent_tcrc अणु
	UCC_FAST_16_BIT_CRC = 0x00000000,
	UCC_FAST_CRC_RESERVED0 = 0x00000040,
	UCC_FAST_32_BIT_CRC = 0x00000080,
	UCC_FAST_CRC_RESERVED1 = 0x000000C0
पूर्ण;

/* Fast UCC initialization काष्ठाure */
काष्ठा ucc_fast_info अणु
	पूर्णांक ucc_num;
	पूर्णांक tdm_num;
	क्रमागत qe_घड़ी rx_घड़ी;
	क्रमागत qe_घड़ी tx_घड़ी;
	क्रमागत qe_घड़ी rx_sync;
	क्रमागत qe_घड़ी tx_sync;
	resource_माप_प्रकार regs;
	पूर्णांक irq;
	u32 uccm_mask;
	पूर्णांक brkpt_support;
	पूर्णांक grant_support;
	पूर्णांक tsa;
	पूर्णांक cdp;
	पूर्णांक cds;
	पूर्णांक ctsp;
	पूर्णांक ctss;
	पूर्णांक tci;
	पूर्णांक txsy;
	पूर्णांक rtsm;
	पूर्णांक revd;
	पूर्णांक rsyn;
	u16 max_rx_buf_length;
	u16 urfs;
	u16 urfet;
	u16 urfset;
	u16 utfs;
	u16 utfet;
	u16 utftt;
	u16 ufpt;
	क्रमागत ucc_fast_channel_protocol_mode mode;
	क्रमागत ucc_fast_transparent_txrx ttx_trx;
	क्रमागत ucc_fast_tx_encoding_method tenc;
	क्रमागत ucc_fast_rx_decoding_method renc;
	क्रमागत ucc_fast_transparent_tcrc tcrc;
	क्रमागत ucc_fast_sync_len synl;
पूर्ण;

काष्ठा ucc_fast_निजी अणु
	काष्ठा ucc_fast_info *uf_info;
	काष्ठा ucc_fast __iomem *uf_regs; /* a poपूर्णांकer to the UCC regs. */
	__be32 __iomem *p_ucce;	/* a poपूर्णांकer to the event रेजिस्टर in memory. */
	__be32 __iomem *p_uccm;	/* a poपूर्णांकer to the mask रेजिस्टर in memory. */
#अगर_घोषित CONFIG_UGETH_TX_ON_DEMAND
	__be16 __iomem *p_utodr;/* poपूर्णांकer to the transmit on demand रेजिस्टर */
#पूर्ण_अगर
	पूर्णांक enabled_tx;		/* Whether channel is enabled क्रम Tx (ENT) */
	पूर्णांक enabled_rx;		/* Whether channel is enabled क्रम Rx (ENR) */
	पूर्णांक stopped_tx;		/* Whether channel has been stopped क्रम Tx
				   (STOP_TX, etc.) */
	पूर्णांक stopped_rx;		/* Whether channel has been stopped क्रम Rx */
	s32 ucc_fast_tx_भव_fअगरo_base_offset;/* poपूर्णांकer to base of Tx
						    भव fअगरo */
	s32 ucc_fast_rx_भव_fअगरo_base_offset;/* poपूर्णांकer to base of Rx
						    भव fअगरo */
#अगर_घोषित STATISTICS
	u32 tx_frames;		/* Transmitted frames counter. */
	u32 rx_frames;		/* Received frames counter (only frames
				   passed to application). */
	u32 tx_discarded;	/* Discarded tx frames counter (frames that
				   were discarded by the driver due to errors).
				   */
	u32 rx_discarded;	/* Discarded rx frames counter (frames that
				   were discarded by the driver due to errors).
				   */
#पूर्ण_अगर				/* STATISTICS */
	u16 mrblr;		/* maximum receive buffer length */
पूर्ण;

/* ucc_fast_init
 * Initializes Fast UCC according to user provided parameters.
 *
 * uf_info  - (In) poपूर्णांकer to the fast UCC info काष्ठाure.
 * uccf_ret - (Out) poपूर्णांकer to the fast UCC काष्ठाure.
 */
पूर्णांक ucc_fast_init(काष्ठा ucc_fast_info * uf_info, काष्ठा ucc_fast_निजी ** uccf_ret);

/* ucc_fast_मुक्त
 * Frees all resources क्रम fast UCC.
 *
 * uccf - (In) poपूर्णांकer to the fast UCC काष्ठाure.
 */
व्योम ucc_fast_मुक्त(काष्ठा ucc_fast_निजी * uccf);

/* ucc_fast_enable
 * Enables a fast UCC port.
 * This routine enables Tx and/or Rx through the General UCC Mode Register.
 *
 * uccf - (In) poपूर्णांकer to the fast UCC काष्ठाure.
 * mode - (In) TX, RX, or both.
 */
व्योम ucc_fast_enable(काष्ठा ucc_fast_निजी * uccf, क्रमागत comm_dir mode);

/* ucc_fast_disable
 * Disables a fast UCC port.
 * This routine disables Tx and/or Rx through the General UCC Mode Register.
 *
 * uccf - (In) poपूर्णांकer to the fast UCC काष्ठाure.
 * mode - (In) TX, RX, or both.
 */
व्योम ucc_fast_disable(काष्ठा ucc_fast_निजी * uccf, क्रमागत comm_dir mode);

/* ucc_fast_irq
 * Handles पूर्णांकerrupts on fast UCC.
 * Called from the general पूर्णांकerrupt routine to handle पूर्णांकerrupts on fast UCC.
 *
 * uccf - (In) poपूर्णांकer to the fast UCC काष्ठाure.
 */
व्योम ucc_fast_irq(काष्ठा ucc_fast_निजी * uccf);

/* ucc_fast_transmit_on_demand
 * Immediately क्रमces a poll of the transmitter क्रम data to be sent.
 * Typically, the hardware perक्रमms a periodic poll क्रम data that the
 * transmit routine has set up to be transmitted. In हालs where
 * this polling cycle is not soon enough, this optional routine can
 * be invoked to क्रमce a poll right away, instead. Proper use क्रम
 * each transmission क्रम which this functionality is desired is to
 * call the transmit routine and then this routine right after.
 *
 * uccf - (In) poपूर्णांकer to the fast UCC काष्ठाure.
 */
व्योम ucc_fast_transmit_on_demand(काष्ठा ucc_fast_निजी * uccf);

u32 ucc_fast_get_qe_cr_subblock(पूर्णांक uccf_num);

व्योम ucc_fast_dump_regs(काष्ठा ucc_fast_निजी * uccf);

#पूर्ण_अगर				/* __UCC_FAST_H__ */
