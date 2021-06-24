<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * scc2698.h
 *
 * driver क्रम the IPOCTAL boards
 *
 * Copyright (C) 2009-2012 CERN (www.cern.ch)
 * Author: Nicolas Serafini, EIC2 SA
 * Author: Samuel Iglesias Gonsalvez <siglesias@igalia.com>
 */

#अगर_अघोषित SCC2698_H_
#घोषणा SCC2698_H_

/*
 * जोड़ scc2698_channel - Channel access to scc2698 IO
 *
 * dn value are only spacer.
 *
 */
जोड़ scc2698_channel अणु
	काष्ठा अणु
		u8 d0, mr;  /* Mode रेजिस्टर 1/2*/
		u8 d1, sr;  /* Status रेजिस्टर */
		u8 d2, r1;  /* reserved */
		u8 d3, rhr; /* Receive holding रेजिस्टर (R) */
		u8 junk[8]; /* other crap क्रम block control */
	पूर्ण __packed r; /* Read access */
	काष्ठा अणु
		u8 d0, mr;  /* Mode रेजिस्टर 1/2 */
		u8 d1, csr; /* Clock select रेजिस्टर */
		u8 d2, cr;  /* Command रेजिस्टर */
		u8 d3, thr; /* Transmit holding रेजिस्टर */
		u8 junk[8]; /* other crap क्रम block control */
	पूर्ण __packed w; /* Write access */
पूर्ण;

/*
 * जोड़ scc2698_block - Block access to scc2698 IO
 *
 * The scc2698 contain 4 block.
 * Each block contaपूर्णांक two channel a and b.
 * dn value are only spacer.
 *
 */
जोड़ scc2698_block अणु
	काष्ठा अणु
		u8 d0, mra;  /* Mode रेजिस्टर 1/2 (a) */
		u8 d1, sra;  /* Status रेजिस्टर (a) */
		u8 d2, r1;   /* reserved */
		u8 d3, rhra; /* Receive holding रेजिस्टर (a) */
		u8 d4, ipcr; /* Input port change रेजिस्टर of block */
		u8 d5, isr;  /* Interrupt status रेजिस्टर of block */
		u8 d6, ctur; /* Counter समयr upper रेजिस्टर of block */
		u8 d7, ctlr; /* Counter समयr lower रेजिस्टर of block */
		u8 d8, mrb;  /* Mode रेजिस्टर 1/2 (b) */
		u8 d9, srb;  /* Status रेजिस्टर (b) */
		u8 da, r2;   /* reserved */
		u8 db, rhrb; /* Receive holding रेजिस्टर (b) */
		u8 dc, r3;   /* reserved */
		u8 dd, ip;   /* Input port रेजिस्टर of block */
		u8 de, ctg;  /* Start counter समयr of block */
		u8 df, cts;  /* Stop counter समयr of block */
	पूर्ण __packed r; /* Read access */
	काष्ठा अणु
		u8 d0, mra;  /* Mode रेजिस्टर 1/2 (a) */
		u8 d1, csra; /* Clock select रेजिस्टर (a) */
		u8 d2, cra;  /* Command रेजिस्टर (a) */
		u8 d3, thra; /* Transmit holding रेजिस्टर (a) */
		u8 d4, acr;  /* Auxiliary control रेजिस्टर of block */
		u8 d5, imr;  /* Interrupt mask रेजिस्टर of block  */
		u8 d6, ctu;  /* Counter समयr upper रेजिस्टर of block */
		u8 d7, ctl;  /* Counter समयr lower रेजिस्टर of block */
		u8 d8, mrb;  /* Mode रेजिस्टर 1/2 (b) */
		u8 d9, csrb; /* Clock select रेजिस्टर (a) */
		u8 da, crb;  /* Command रेजिस्टर (b) */
		u8 db, thrb; /* Transmit holding रेजिस्टर (b) */
		u8 dc, r1;   /* reserved */
		u8 dd, opcr; /* Output port configuration रेजिस्टर of block */
		u8 de, r2;   /* reserved */
		u8 df, r3;   /* reserved */
	पूर्ण __packed w; /* Write access */
पूर्ण;

#घोषणा MR1_CHRL_5_BITS             (0x0 << 0)
#घोषणा MR1_CHRL_6_BITS             (0x1 << 0)
#घोषणा MR1_CHRL_7_BITS             (0x2 << 0)
#घोषणा MR1_CHRL_8_BITS             (0x3 << 0)
#घोषणा MR1_PARITY_EVEN             (0x1 << 2)
#घोषणा MR1_PARITY_ODD              (0x0 << 2)
#घोषणा MR1_PARITY_ON               (0x0 << 3)
#घोषणा MR1_PARITY_FORCE            (0x1 << 3)
#घोषणा MR1_PARITY_OFF              (0x2 << 3)
#घोषणा MR1_PARITY_SPECIAL          (0x3 << 3)
#घोषणा MR1_ERROR_CHAR              (0x0 << 5)
#घोषणा MR1_ERROR_BLOCK             (0x1 << 5)
#घोषणा MR1_RxINT_RxRDY             (0x0 << 6)
#घोषणा MR1_RxINT_FFULL             (0x1 << 6)
#घोषणा MR1_RxRTS_CONTROL_ON        (0x1 << 7)
#घोषणा MR1_RxRTS_CONTROL_OFF       (0x0 << 7)

#घोषणा MR2_STOP_BITS_LENGTH_1      (0x7 << 0)
#घोषणा MR2_STOP_BITS_LENGTH_2      (0xF << 0)
#घोषणा MR2_CTS_ENABLE_TX_ON        (0x1 << 4)
#घोषणा MR2_CTS_ENABLE_TX_OFF       (0x0 << 4)
#घोषणा MR2_TxRTS_CONTROL_ON        (0x1 << 5)
#घोषणा MR2_TxRTS_CONTROL_OFF       (0x0 << 5)
#घोषणा MR2_CH_MODE_NORMAL          (0x0 << 6)
#घोषणा MR2_CH_MODE_ECHO            (0x1 << 6)
#घोषणा MR2_CH_MODE_LOCAL           (0x2 << 6)
#घोषणा MR2_CH_MODE_REMOTE          (0x3 << 6)

#घोषणा CR_ENABLE_RX                (0x1 << 0)
#घोषणा CR_DISABLE_RX               (0x1 << 1)
#घोषणा CR_ENABLE_TX                (0x1 << 2)
#घोषणा CR_DISABLE_TX               (0x1 << 3)
#घोषणा CR_CMD_RESET_MR             (0x1 << 4)
#घोषणा CR_CMD_RESET_RX             (0x2 << 4)
#घोषणा CR_CMD_RESET_TX             (0x3 << 4)
#घोषणा CR_CMD_RESET_ERR_STATUS     (0x4 << 4)
#घोषणा CR_CMD_RESET_BREAK_CHANGE   (0x5 << 4)
#घोषणा CR_CMD_START_BREAK          (0x6 << 4)
#घोषणा CR_CMD_STOP_BREAK           (0x7 << 4)
#घोषणा CR_CMD_ASSERT_RTSN          (0x8 << 4)
#घोषणा CR_CMD_NEGATE_RTSN          (0x9 << 4)
#घोषणा CR_CMD_SET_TIMEOUT_MODE     (0xA << 4)
#घोषणा CR_CMD_DISABLE_TIMEOUT_MODE (0xC << 4)

#घोषणा SR_RX_READY                 (0x1 << 0)
#घोषणा SR_FIFO_FULL                (0x1 << 1)
#घोषणा SR_TX_READY                 (0x1 << 2)
#घोषणा SR_TX_EMPTY                 (0x1 << 3)
#घोषणा SR_OVERRUN_ERROR            (0x1 << 4)
#घोषणा SR_PARITY_ERROR             (0x1 << 5)
#घोषणा SR_FRAMING_ERROR            (0x1 << 6)
#घोषणा SR_RECEIVED_BREAK           (0x1 << 7)

#घोषणा SR_ERROR                    (0xF0)

#घोषणा ACR_DELTA_IP0_IRQ_EN        (0x1 << 0)
#घोषणा ACR_DELTA_IP1_IRQ_EN        (0x1 << 1)
#घोषणा ACR_DELTA_IP2_IRQ_EN        (0x1 << 2)
#घोषणा ACR_DELTA_IP3_IRQ_EN        (0x1 << 3)
#घोषणा ACR_CT_Mask                 (0x7 << 4)
#घोषणा ACR_CExt                    (0x0 << 4)
#घोषणा ACR_CTxCA                   (0x1 << 4)
#घोषणा ACR_CTxCB                   (0x2 << 4)
#घोषणा ACR_CClk16                  (0x3 << 4)
#घोषणा ACR_TExt                    (0x4 << 4)
#घोषणा ACR_TExt16                  (0x5 << 4)
#घोषणा ACR_TClk                    (0x6 << 4)
#घोषणा ACR_TClk16                  (0x7 << 4)
#घोषणा ACR_BRG_SET1                (0x0 << 7)
#घोषणा ACR_BRG_SET2                (0x1 << 7)

#घोषणा TX_CLK_75                   (0x0 << 0)
#घोषणा TX_CLK_110                  (0x1 << 0)
#घोषणा TX_CLK_38400                (0x2 << 0)
#घोषणा TX_CLK_150                  (0x3 << 0)
#घोषणा TX_CLK_300                  (0x4 << 0)
#घोषणा TX_CLK_600                  (0x5 << 0)
#घोषणा TX_CLK_1200                 (0x6 << 0)
#घोषणा TX_CLK_2000                 (0x7 << 0)
#घोषणा TX_CLK_2400                 (0x8 << 0)
#घोषणा TX_CLK_4800                 (0x9 << 0)
#घोषणा TX_CLK_1800                 (0xA << 0)
#घोषणा TX_CLK_9600                 (0xB << 0)
#घोषणा TX_CLK_19200                (0xC << 0)
#घोषणा RX_CLK_75                   (0x0 << 4)
#घोषणा RX_CLK_110                  (0x1 << 4)
#घोषणा RX_CLK_38400                (0x2 << 4)
#घोषणा RX_CLK_150                  (0x3 << 4)
#घोषणा RX_CLK_300                  (0x4 << 4)
#घोषणा RX_CLK_600                  (0x5 << 4)
#घोषणा RX_CLK_1200                 (0x6 << 4)
#घोषणा RX_CLK_2000                 (0x7 << 4)
#घोषणा RX_CLK_2400                 (0x8 << 4)
#घोषणा RX_CLK_4800                 (0x9 << 4)
#घोषणा RX_CLK_1800                 (0xA << 4)
#घोषणा RX_CLK_9600                 (0xB << 4)
#घोषणा RX_CLK_19200                (0xC << 4)

#घोषणा OPCR_MPOa_RTSN              (0x0 << 0)
#घोषणा OPCR_MPOa_C_TO              (0x1 << 0)
#घोषणा OPCR_MPOa_TxC1X             (0x2 << 0)
#घोषणा OPCR_MPOa_TxC16X            (0x3 << 0)
#घोषणा OPCR_MPOa_RxC1X             (0x4 << 0)
#घोषणा OPCR_MPOa_RxC16X            (0x5 << 0)
#घोषणा OPCR_MPOa_TxRDY             (0x6 << 0)
#घोषणा OPCR_MPOa_RxRDY_FF          (0x7 << 0)

#घोषणा OPCR_MPOb_RTSN              (0x0 << 4)
#घोषणा OPCR_MPOb_C_TO              (0x1 << 4)
#घोषणा OPCR_MPOb_TxC1X             (0x2 << 4)
#घोषणा OPCR_MPOb_TxC16X            (0x3 << 4)
#घोषणा OPCR_MPOb_RxC1X             (0x4 << 4)
#घोषणा OPCR_MPOb_RxC16X            (0x5 << 4)
#घोषणा OPCR_MPOb_TxRDY             (0x6 << 4)
#घोषणा OPCR_MPOb_RxRDY_FF          (0x7 << 4)

#घोषणा OPCR_MPP_INPUT              (0x0 << 7)
#घोषणा OPCR_MPP_OUTPUT             (0x1 << 7)

#घोषणा IMR_TxRDY_A                 (0x1 << 0)
#घोषणा IMR_RxRDY_FFULL_A           (0x1 << 1)
#घोषणा IMR_DELTA_BREAK_A           (0x1 << 2)
#घोषणा IMR_COUNTER_READY           (0x1 << 3)
#घोषणा IMR_TxRDY_B                 (0x1 << 4)
#घोषणा IMR_RxRDY_FFULL_B           (0x1 << 5)
#घोषणा IMR_DELTA_BREAK_B           (0x1 << 6)
#घोषणा IMR_INPUT_PORT_CHANGE       (0x1 << 7)

#घोषणा ISR_TxRDY_A                 (0x1 << 0)
#घोषणा ISR_RxRDY_FFULL_A           (0x1 << 1)
#घोषणा ISR_DELTA_BREAK_A           (0x1 << 2)
#घोषणा ISR_COUNTER_READY           (0x1 << 3)
#घोषणा ISR_TxRDY_B                 (0x1 << 4)
#घोषणा ISR_RxRDY_FFULL_B           (0x1 << 5)
#घोषणा ISR_DELTA_BREAK_B           (0x1 << 6)
#घोषणा ISR_INPUT_PORT_CHANGE       (0x1 << 7)

#घोषणा ACK_INT_REQ0			0
#घोषणा ACK_INT_REQ1			2

#पूर्ण_अगर /* SCC2698_H_ */
