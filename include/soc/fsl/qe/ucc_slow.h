<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2006 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Authors: 	Shlomi Gridish <gridish@मुक्तscale.com>
 * 		Li Yang <leoli@मुक्तscale.com>
 *
 * Description:
 * Internal header file क्रम UCC SLOW unit routines.
 */
#अगर_अघोषित __UCC_SLOW_H__
#घोषणा __UCC_SLOW_H__

#समावेश <linux/kernel.h>

#समावेश <soc/fsl/qe/immap_qe.h>
#समावेश <soc/fsl/qe/qe.h>

#समावेश <soc/fsl/qe/ucc.h>

/* transmit BD's status */
#घोषणा T_R	0x80000000	/* पढ़ोy bit */
#घोषणा T_PAD	0x40000000	/* add pads to लघु frames */
#घोषणा T_W	0x20000000	/* wrap bit */
#घोषणा T_I	0x10000000	/* पूर्णांकerrupt on completion */
#घोषणा T_L	0x08000000	/* last */

#घोषणा T_A	0x04000000	/* Address - the data transmitted as address
				   अक्षरs */
#घोषणा T_TC	0x04000000	/* transmit CRC */
#घोषणा T_CM	0x02000000	/* continuous mode */
#घोषणा T_DEF	0x02000000	/* collision on previous attempt to transmit */
#घोषणा T_P	0x01000000	/* Preamble - send Preamble sequence beक्रमe
				   data */
#घोषणा T_HB	0x01000000	/* heartbeat */
#घोषणा T_NS	0x00800000	/* No Stop */
#घोषणा T_LC	0x00800000	/* late collision */
#घोषणा T_RL	0x00400000	/* retransmission limit */
#घोषणा T_UN	0x00020000	/* underrun */
#घोषणा T_CT	0x00010000	/* CTS lost */
#घोषणा T_CSL	0x00010000	/* carrier sense lost */
#घोषणा T_RC	0x003c0000	/* retry count */

/* Receive BD's status */
#घोषणा R_E	0x80000000	/* buffer empty */
#घोषणा R_W	0x20000000	/* wrap bit */
#घोषणा R_I	0x10000000	/* पूर्णांकerrupt on reception */
#घोषणा R_L	0x08000000	/* last */
#घोषणा R_C	0x08000000	/* the last byte in this buffer is a cntl
				   अक्षर */
#घोषणा R_F	0x04000000	/* first */
#घोषणा R_A	0x04000000	/* the first byte in this buffer is address
				   byte */
#घोषणा R_CM	0x02000000	/* continuous mode */
#घोषणा R_ID	0x01000000	/* buffer बंद on reception of idles */
#घोषणा R_M	0x01000000	/* Frame received because of promiscuous
				   mode */
#घोषणा R_AM	0x00800000	/* Address match */
#घोषणा R_DE	0x00800000	/* Address match */
#घोषणा R_LG	0x00200000	/* Break received */
#घोषणा R_BR	0x00200000	/* Frame length violation */
#घोषणा R_NO	0x00100000	/* Rx Non Octet Aligned Packet */
#घोषणा R_FR	0x00100000	/* Framing Error (no stop bit) अक्षरacter
				   received */
#घोषणा R_PR	0x00080000	/* Parity Error अक्षरacter received */
#घोषणा R_AB	0x00080000	/* Frame Aborted */
#घोषणा R_SH	0x00080000	/* frame is too लघु */
#घोषणा R_CR	0x00040000	/* CRC Error */
#घोषणा R_OV	0x00020000	/* Overrun */
#घोषणा R_CD	0x00010000	/* CD lost */
#घोषणा R_CL	0x00010000	/* this frame is बंदd because of a
				   collision */

/* Rx Data buffer must be 4 bytes aligned in most हालs.*/
#घोषणा UCC_SLOW_RX_ALIGN		4
#घोषणा UCC_SLOW_MRBLR_ALIGNMENT	4
#घोषणा UCC_SLOW_PRAM_SIZE		0x100
#घोषणा ALIGNMENT_OF_UCC_SLOW_PRAM	64

/* UCC Slow Channel Protocol Mode */
क्रमागत ucc_slow_channel_protocol_mode अणु
	UCC_SLOW_CHANNEL_PROTOCOL_MODE_QMC = 0x00000002,
	UCC_SLOW_CHANNEL_PROTOCOL_MODE_UART = 0x00000004,
	UCC_SLOW_CHANNEL_PROTOCOL_MODE_BISYNC = 0x00000008,
पूर्ण;

/* UCC Slow Transparent Transmit CRC (TCRC) */
क्रमागत ucc_slow_transparent_tcrc अणु
	/* 16-bit CCITT CRC (HDLC).  (X16 + X12 + X5 + 1) */
	UCC_SLOW_TRANSPARENT_TCRC_CCITT_CRC16 = 0x00000000,
	/* CRC16 (BISYNC).  (X16 + X15 + X2 + 1) */
	UCC_SLOW_TRANSPARENT_TCRC_CRC16 = 0x00004000,
	/* 32-bit CCITT CRC (Ethernet and HDLC) */
	UCC_SLOW_TRANSPARENT_TCRC_CCITT_CRC32 = 0x00008000,
पूर्ण;

/* UCC Slow oversampling rate क्रम transmitter (TDCR) */
क्रमागत ucc_slow_tx_oversampling_rate अणु
	/* 1x घड़ी mode */
	UCC_SLOW_OVERSAMPLING_RATE_TX_TDCR_1 = 0x00000000,
	/* 8x घड़ी mode */
	UCC_SLOW_OVERSAMPLING_RATE_TX_TDCR_8 = 0x00010000,
	/* 16x घड़ी mode */
	UCC_SLOW_OVERSAMPLING_RATE_TX_TDCR_16 = 0x00020000,
	/* 32x घड़ी mode */
	UCC_SLOW_OVERSAMPLING_RATE_TX_TDCR_32 = 0x00030000,
पूर्ण;

/* UCC Slow Oversampling rate क्रम receiver (RDCR)
*/
क्रमागत ucc_slow_rx_oversampling_rate अणु
	/* 1x घड़ी mode */
	UCC_SLOW_OVERSAMPLING_RATE_RX_RDCR_1 = 0x00000000,
	/* 8x घड़ी mode */
	UCC_SLOW_OVERSAMPLING_RATE_RX_RDCR_8 = 0x00004000,
	/* 16x घड़ी mode */
	UCC_SLOW_OVERSAMPLING_RATE_RX_RDCR_16 = 0x00008000,
	/* 32x घड़ी mode */
	UCC_SLOW_OVERSAMPLING_RATE_RX_RDCR_32 = 0x0000c000,
पूर्ण;

/* UCC Slow Transmitter encoding method (TENC)
*/
क्रमागत ucc_slow_tx_encoding_method अणु
	UCC_SLOW_TRANSMITTER_ENCODING_METHOD_TENC_NRZ = 0x00000000,
	UCC_SLOW_TRANSMITTER_ENCODING_METHOD_TENC_NRZI = 0x00000100
पूर्ण;

/* UCC Slow Receiver decoding method (RENC)
*/
क्रमागत ucc_slow_rx_decoding_method अणु
	UCC_SLOW_RECEIVER_DECODING_METHOD_RENC_NRZ = 0x00000000,
	UCC_SLOW_RECEIVER_DECODING_METHOD_RENC_NRZI = 0x00000800
पूर्ण;

/* UCC Slow Diagnostic mode (DIAG)
*/
क्रमागत ucc_slow_diag_mode अणु
	UCC_SLOW_DIAG_MODE_NORMAL = 0x00000000,
	UCC_SLOW_DIAG_MODE_LOOPBACK = 0x00000040,
	UCC_SLOW_DIAG_MODE_ECHO = 0x00000080,
	UCC_SLOW_DIAG_MODE_LOOPBACK_ECHO = 0x000000c0
पूर्ण;

काष्ठा ucc_slow_info अणु
	पूर्णांक ucc_num;
	पूर्णांक protocol;			/* QE_CR_PROTOCOL_xxx */
	क्रमागत qe_घड़ी rx_घड़ी;
	क्रमागत qe_घड़ी tx_घड़ी;
	phys_addr_t regs;
	पूर्णांक irq;
	u16 uccm_mask;
	पूर्णांक data_mem_part;
	पूर्णांक init_tx;
	पूर्णांक init_rx;
	u32 tx_bd_ring_len;
	u32 rx_bd_ring_len;
	पूर्णांक rx_पूर्णांकerrupts;
	पूर्णांक brkpt_support;
	पूर्णांक grant_support;
	पूर्णांक tsa;
	पूर्णांक cdp;
	पूर्णांक cds;
	पूर्णांक ctsp;
	पूर्णांक ctss;
	पूर्णांक rinv;
	पूर्णांक tinv;
	पूर्णांक rtsm;
	पूर्णांक rfw;
	पूर्णांक tci;
	पूर्णांक tend;
	पूर्णांक tfl;
	पूर्णांक txsy;
	u16 max_rx_buf_length;
	क्रमागत ucc_slow_transparent_tcrc tcrc;
	क्रमागत ucc_slow_channel_protocol_mode mode;
	क्रमागत ucc_slow_diag_mode diag;
	क्रमागत ucc_slow_tx_oversampling_rate tdcr;
	क्रमागत ucc_slow_rx_oversampling_rate rdcr;
	क्रमागत ucc_slow_tx_encoding_method tenc;
	क्रमागत ucc_slow_rx_decoding_method renc;
पूर्ण;

काष्ठा ucc_slow_निजी अणु
	काष्ठा ucc_slow_info *us_info;
	काष्ठा ucc_slow __iomem *us_regs; /* Ptr to memory map of UCC regs */
	काष्ठा ucc_slow_pram __iomem *us_pram;	/* a poपूर्णांकer to the parameter RAM */
	s32 us_pram_offset;
	पूर्णांक enabled_tx;		/* Whether channel is enabled क्रम Tx (ENT) */
	पूर्णांक enabled_rx;		/* Whether channel is enabled क्रम Rx (ENR) */
	पूर्णांक stopped_tx;		/* Whether channel has been stopped क्रम Tx
				   (STOP_TX, etc.) */
	पूर्णांक stopped_rx;		/* Whether channel has been stopped क्रम Rx */
	काष्ठा list_head confQ;	/* frames passed to chip रुकोing क्रम tx */
	u32 first_tx_bd_mask;	/* mask is used in Tx routine to save status
				   and length क्रम first BD in a frame */
	s32 tx_base_offset;	/* first BD in Tx BD table offset (In MURAM) */
	s32 rx_base_offset;	/* first BD in Rx BD table offset (In MURAM) */
	काष्ठा qe_bd __iomem *confBd;	/* next BD क्रम confirm after Tx */
	काष्ठा qe_bd __iomem *tx_bd;	/* next BD क्रम new Tx request */
	काष्ठा qe_bd __iomem *rx_bd;	/* next BD to collect after Rx */
	व्योम *p_rx_frame;	/* accumulating receive frame */
	__be16 __iomem *p_ucce;	/* a poपूर्णांकer to the event रेजिस्टर in memory */
	__be16 __iomem *p_uccm;	/* a poपूर्णांकer to the mask रेजिस्टर in memory */
	u16 saved_uccm;		/* a saved mask क्रम the RX Interrupt bits */
#अगर_घोषित STATISTICS
	u32 tx_frames;		/* Transmitted frames counters */
	u32 rx_frames;		/* Received frames counters (only frames
				   passed to application) */
	u32 rx_discarded;	/* Discarded frames counters (frames that
				   were discarded by the driver due to
				   errors) */
#पूर्ण_अगर				/* STATISTICS */
पूर्ण;

/* ucc_slow_init
 * Initializes Slow UCC according to provided parameters.
 *
 * us_info  - (In) poपूर्णांकer to the slow UCC info काष्ठाure.
 * uccs_ret - (Out) poपूर्णांकer to the slow UCC काष्ठाure.
 */
पूर्णांक ucc_slow_init(काष्ठा ucc_slow_info * us_info, काष्ठा ucc_slow_निजी ** uccs_ret);

/* ucc_slow_मुक्त
 * Frees all resources क्रम slow UCC.
 *
 * uccs - (In) poपूर्णांकer to the slow UCC काष्ठाure.
 */
व्योम ucc_slow_मुक्त(काष्ठा ucc_slow_निजी * uccs);

/* ucc_slow_enable
 * Enables a fast UCC port.
 * This routine enables Tx and/or Rx through the General UCC Mode Register.
 *
 * uccs - (In) poपूर्णांकer to the slow UCC काष्ठाure.
 * mode - (In) TX, RX, or both.
 */
व्योम ucc_slow_enable(काष्ठा ucc_slow_निजी * uccs, क्रमागत comm_dir mode);

/* ucc_slow_disable
 * Disables a fast UCC port.
 * This routine disables Tx and/or Rx through the General UCC Mode Register.
 *
 * uccs - (In) poपूर्णांकer to the slow UCC काष्ठाure.
 * mode - (In) TX, RX, or both.
 */
व्योम ucc_slow_disable(काष्ठा ucc_slow_निजी * uccs, क्रमागत comm_dir mode);

/* ucc_slow_graceful_stop_tx
 * Smoothly stops transmission on a specअगरied slow UCC.
 *
 * uccs - (In) poपूर्णांकer to the slow UCC काष्ठाure.
 */
व्योम ucc_slow_graceful_stop_tx(काष्ठा ucc_slow_निजी * uccs);

/* ucc_slow_stop_tx
 * Stops transmission on a specअगरied slow UCC.
 *
 * uccs - (In) poपूर्णांकer to the slow UCC काष्ठाure.
 */
व्योम ucc_slow_stop_tx(काष्ठा ucc_slow_निजी * uccs);

/* ucc_slow_restart_tx
 * Restarts transmitting on a specअगरied slow UCC.
 *
 * uccs - (In) poपूर्णांकer to the slow UCC काष्ठाure.
 */
व्योम ucc_slow_restart_tx(काष्ठा ucc_slow_निजी *uccs);

u32 ucc_slow_get_qe_cr_subblock(पूर्णांक uccs_num);

#पूर्ण_अगर				/* __UCC_SLOW_H__ */
