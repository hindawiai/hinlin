<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* drivers/aपंचांग/idt77105.h - IDT77105 (PHY) declarations */
 
/* Written 1999 by Greg Banks, NEC Australia <gnb@linuxfan.com>. Based on suni.h */
 

#अगर_अघोषित DRIVER_ATM_IDT77105_H
#घोषणा DRIVER_ATM_IDT77105_H

#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/aपंचांगioc.h>


/* IDT77105 रेजिस्टरs */

#घोषणा IDT77105_MCR		0x0	/* Master Control Register */
#घोषणा IDT77105_ISTAT	        0x1	/* Interrupt Status */
#घोषणा IDT77105_DIAG   	0x2	/* Diagnostic Control */
#घोषणा IDT77105_LEDHEC		0x3	/* LED Driver & HEC Status/Control */
#घोषणा IDT77105_CTRLO		0x4	/* Low Byte Counter Register */
#घोषणा IDT77105_CTRHI		0x5	/* High Byte Counter Register */
#घोषणा IDT77105_CTRSEL		0x6	/* Counter Register Read Select */

/* IDT77105 रेजिस्टर values */

/* MCR */
#घोषणा IDT77105_MCR_UPLO	0x80	/* R/W, User Prog'le Output Latch */
#घोषणा IDT77105_MCR_DREC	0x40	/* R/W, Discard Receive Error Cells */
#घोषणा IDT77105_MCR_ECEIO	0x20	/* R/W, Enable Cell Error Interrupts
                                         * Only */
#घोषणा IDT77105_MCR_TDPC	0x10	/* R/W, Transmit Data Parity Check */
#घोषणा IDT77105_MCR_DRIC	0x08	/* R/W, Discard Received Idle Cells */
#घोषणा IDT77105_MCR_HALTTX	0x04	/* R/W, Halt Tx */
#घोषणा IDT77105_MCR_UMODE	0x02	/* R/W, Utopia (cell/byte) Mode */
#घोषणा IDT77105_MCR_EIP	0x01	/* R/W, Enable Interrupt Pin */

/* ISTAT */
#घोषणा IDT77105_ISTAT_GOODSIG	0x40	/* R, Good Signal Bit */
#घोषणा IDT77105_ISTAT_HECERR	0x20	/* sticky, HEC Error*/
#घोषणा IDT77105_ISTAT_SCR	0x10	/* sticky, Short Cell Received */
#घोषणा IDT77105_ISTAT_TPE	0x08	/* sticky, Transmit Parity Error */
#घोषणा IDT77105_ISTAT_RSCC	0x04	/* sticky, Rx Signal Condition Change */
#घोषणा IDT77105_ISTAT_RSE	0x02	/* sticky, Rx Symbol Error */
#घोषणा IDT77105_ISTAT_RFO	0x01	/* sticky, Rx FIFO Overrun */

/* DIAG */
#घोषणा IDT77105_DIAG_FTD	0x80	/* R/W, Force TxClav deनिश्चित */
#घोषणा IDT77105_DIAG_ROS	0x40	/* R/W, RxClav operation select */
#घोषणा IDT77105_DIAG_MPCS	0x20	/* R/W, Multi-PHY config'n select */
#घोषणा IDT77105_DIAG_RFLUSH	0x10	/* R/W, clear receive FIFO */
#घोषणा IDT77105_DIAG_ITPE	0x08	/* R/W, Insert Tx payload error */
#घोषणा IDT77105_DIAG_ITHE	0x04	/* R/W, Insert Tx HEC error */
#घोषणा IDT77105_DIAG_UMODE	0x02	/* R/W, Utopia (cell/byte) Mode */
#घोषणा IDT77105_DIAG_LCMASK	0x03	/* R/W, Loopback Control */

#घोषणा IDT77105_DIAG_LC_NORMAL         0x00	/* Receive from network */
#घोषणा IDT77105_DIAG_LC_PHY_LOOPBACK	0x02
#घोषणा IDT77105_DIAG_LC_LINE_LOOPBACK	0x03

/* LEDHEC */
#घोषणा IDT77105_LEDHEC_DRHC	0x40	/* R/W, Disable Rx HEC check */
#घोषणा IDT77105_LEDHEC_DTHC	0x20	/* R/W, Disable Tx HEC calculation */
#घोषणा IDT77105_LEDHEC_RPWMASK	0x18	/* R/W, RxRef pulse width select */
#घोषणा IDT77105_LEDHEC_TFS	0x04	/* R, Tx FIFO Status (1=empty) */
#घोषणा IDT77105_LEDHEC_TLS	0x02	/* R, Tx LED Status (1=lit) */
#घोषणा IDT77105_LEDHEC_RLS	0x01	/* R, Rx LED Status (1=lit) */

#घोषणा IDT77105_LEDHEC_RPW_1	0x00	/* RxRef active क्रम 1 RxClk cycle */
#घोषणा IDT77105_LEDHEC_RPW_2	0x08	/* RxRef active क्रम 2 RxClk cycle */
#घोषणा IDT77105_LEDHEC_RPW_4	0x10	/* RxRef active क्रम 4 RxClk cycle */
#घोषणा IDT77105_LEDHEC_RPW_8	0x18	/* RxRef active क्रम 8 RxClk cycle */

/* CTRSEL */
#घोषणा IDT77105_CTRSEL_SEC	0x08	/* W, Symbol Error Counter */
#घोषणा IDT77105_CTRSEL_TCC	0x04	/* W, Tx Cell Counter */
#घोषणा IDT77105_CTRSEL_RCC	0x02	/* W, Rx Cell Counter */
#घोषणा IDT77105_CTRSEL_RHEC	0x01	/* W, Rx HEC Error Counter */

#अगर_घोषित __KERNEL__
पूर्णांक idt77105_init(काष्ठा aपंचांग_dev *dev);
#पूर्ण_अगर

/*
 * Tunable parameters
 */
 
/* Time between samples of the hardware cell counters. Should be <= 1 sec */
#घोषणा IDT77105_STATS_TIMER_PERIOD     (HZ) 
/* Time between checks to see अगर the संकेत has been found again */
#घोषणा IDT77105_RESTART_TIMER_PERIOD   (5 * HZ)

#पूर्ण_अगर
