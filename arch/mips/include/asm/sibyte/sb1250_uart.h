<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*  *********************************************************************
    *  SB1250 Board Support Package
    *
    *  UART Constants				File: sb1250_uart.h
    *
    *  This module contains स्थिरants and macros useful क्रम
    *  manipulating the SB1250's UARTs
    *
    *  SB1250 specअगरication level:  User's manual 1/02/02
    *
    *********************************************************************
    *
    *  Copyright 2000,2001,2002,2003
    *  Broadcom Corporation. All rights reserved.
    *
    ********************************************************************* */


#अगर_अघोषित _SB1250_UART_H
#घोषणा _SB1250_UART_H

#समावेश <यंत्र/sibyte/sb1250_defs.h>

/* **********************************************************************
   * DUART Registers
   ********************************************************************** */

/*
 * DUART Mode Register #1 (Table 10-3)
 * Register: DUART_MODE_REG_1_A
 * Register: DUART_MODE_REG_1_B
 */

#घोषणा S_DUART_BITS_PER_CHAR	    0
#घोषणा M_DUART_BITS_PER_CHAR	    _SB_MAKEMASK(2, S_DUART_BITS_PER_CHAR)
#घोषणा V_DUART_BITS_PER_CHAR(x)    _SB_MAKEVALUE(x, S_DUART_BITS_PER_CHAR)

#घोषणा K_DUART_BITS_PER_CHAR_RSV0  0
#घोषणा K_DUART_BITS_PER_CHAR_RSV1  1
#घोषणा K_DUART_BITS_PER_CHAR_7	    2
#घोषणा K_DUART_BITS_PER_CHAR_8	    3

#घोषणा V_DUART_BITS_PER_CHAR_RSV0  V_DUART_BITS_PER_CHAR(K_DUART_BITS_PER_CHAR_RSV0)
#घोषणा V_DUART_BITS_PER_CHAR_RSV1  V_DUART_BITS_PER_CHAR(K_DUART_BITS_PER_CHAR_RSV1)
#घोषणा V_DUART_BITS_PER_CHAR_7	    V_DUART_BITS_PER_CHAR(K_DUART_BITS_PER_CHAR_7)
#घोषणा V_DUART_BITS_PER_CHAR_8	    V_DUART_BITS_PER_CHAR(K_DUART_BITS_PER_CHAR_8)


#घोषणा M_DUART_PARITY_TYPE_EVEN    0x00
#घोषणा M_DUART_PARITY_TYPE_ODD	    _SB_MAKEMASK1(2)

#घोषणा S_DUART_PARITY_MODE	     3
#घोषणा M_DUART_PARITY_MODE	    _SB_MAKEMASK(2, S_DUART_PARITY_MODE)
#घोषणा V_DUART_PARITY_MODE(x)	    _SB_MAKEVALUE(x, S_DUART_PARITY_MODE)

#घोषणा K_DUART_PARITY_MODE_ADD	      0
#घोषणा K_DUART_PARITY_MODE_ADD_FIXED 1
#घोषणा K_DUART_PARITY_MODE_NONE      2

#घोषणा V_DUART_PARITY_MODE_ADD	      V_DUART_PARITY_MODE(K_DUART_PARITY_MODE_ADD)
#घोषणा V_DUART_PARITY_MODE_ADD_FIXED V_DUART_PARITY_MODE(K_DUART_PARITY_MODE_ADD_FIXED)
#घोषणा V_DUART_PARITY_MODE_NONE      V_DUART_PARITY_MODE(K_DUART_PARITY_MODE_NONE)

#घोषणा M_DUART_TX_IRQ_SEL_TXRDY    0
#घोषणा M_DUART_TX_IRQ_SEL_TXEMPT   _SB_MAKEMASK1(5)

#घोषणा M_DUART_RX_IRQ_SEL_RXRDY    0
#घोषणा M_DUART_RX_IRQ_SEL_RXFULL   _SB_MAKEMASK1(6)

#घोषणा M_DUART_RX_RTS_ENA	    _SB_MAKEMASK1(7)

/*
 * DUART Mode Register #2 (Table 10-4)
 * Register: DUART_MODE_REG_2_A
 * Register: DUART_MODE_REG_2_B
 */

#घोषणा M_DUART_MODE_RESERVED1	    _SB_MAKEMASK(3, 0)	 /* ignored */

#घोषणा M_DUART_STOP_BIT_LEN_2	    _SB_MAKEMASK1(3)
#घोषणा M_DUART_STOP_BIT_LEN_1	    0

#घोषणा M_DUART_TX_CTS_ENA	    _SB_MAKEMASK1(4)


#घोषणा M_DUART_MODE_RESERVED2	    _SB_MAKEMASK1(5)	/* must be zero */

#घोषणा S_DUART_CHAN_MODE	    6
#घोषणा M_DUART_CHAN_MODE	    _SB_MAKEMASK(2, S_DUART_CHAN_MODE)
#घोषणा V_DUART_CHAN_MODE(x)	    _SB_MAKEVALUE(x, S_DUART_CHAN_MODE)

#घोषणा K_DUART_CHAN_MODE_NORMAL    0
#घोषणा K_DUART_CHAN_MODE_LCL_LOOP  2
#घोषणा K_DUART_CHAN_MODE_REM_LOOP  3

#घोषणा V_DUART_CHAN_MODE_NORMAL    V_DUART_CHAN_MODE(K_DUART_CHAN_MODE_NORMAL)
#घोषणा V_DUART_CHAN_MODE_LCL_LOOP  V_DUART_CHAN_MODE(K_DUART_CHAN_MODE_LCL_LOOP)
#घोषणा V_DUART_CHAN_MODE_REM_LOOP  V_DUART_CHAN_MODE(K_DUART_CHAN_MODE_REM_LOOP)

/*
 * DUART Command Register (Table 10-5)
 * Register: DUART_CMD_A
 * Register: DUART_CMD_B
 */

#घोषणा M_DUART_RX_EN		    _SB_MAKEMASK1(0)
#घोषणा M_DUART_RX_DIS		    _SB_MAKEMASK1(1)
#घोषणा M_DUART_TX_EN		    _SB_MAKEMASK1(2)
#घोषणा M_DUART_TX_DIS		    _SB_MAKEMASK1(3)

#घोषणा S_DUART_MISC_CMD	    4
#घोषणा M_DUART_MISC_CMD	    _SB_MAKEMASK(3, S_DUART_MISC_CMD)
#घोषणा V_DUART_MISC_CMD(x)	    _SB_MAKEVALUE(x, S_DUART_MISC_CMD)

#घोषणा K_DUART_MISC_CMD_NOACTION0	 0
#घोषणा K_DUART_MISC_CMD_NOACTION1	 1
#घोषणा K_DUART_MISC_CMD_RESET_RX	 2
#घोषणा K_DUART_MISC_CMD_RESET_TX	 3
#घोषणा K_DUART_MISC_CMD_NOACTION4	 4
#घोषणा K_DUART_MISC_CMD_RESET_BREAK_INT 5
#घोषणा K_DUART_MISC_CMD_START_BREAK	 6
#घोषणा K_DUART_MISC_CMD_STOP_BREAK	 7

#घोषणा V_DUART_MISC_CMD_NOACTION0	 V_DUART_MISC_CMD(K_DUART_MISC_CMD_NOACTION0)
#घोषणा V_DUART_MISC_CMD_NOACTION1	 V_DUART_MISC_CMD(K_DUART_MISC_CMD_NOACTION1)
#घोषणा V_DUART_MISC_CMD_RESET_RX	 V_DUART_MISC_CMD(K_DUART_MISC_CMD_RESET_RX)
#घोषणा V_DUART_MISC_CMD_RESET_TX	 V_DUART_MISC_CMD(K_DUART_MISC_CMD_RESET_TX)
#घोषणा V_DUART_MISC_CMD_NOACTION4	 V_DUART_MISC_CMD(K_DUART_MISC_CMD_NOACTION4)
#घोषणा V_DUART_MISC_CMD_RESET_BREAK_INT V_DUART_MISC_CMD(K_DUART_MISC_CMD_RESET_BREAK_INT)
#घोषणा V_DUART_MISC_CMD_START_BREAK	 V_DUART_MISC_CMD(K_DUART_MISC_CMD_START_BREAK)
#घोषणा V_DUART_MISC_CMD_STOP_BREAK	 V_DUART_MISC_CMD(K_DUART_MISC_CMD_STOP_BREAK)

#घोषणा M_DUART_CMD_RESERVED		 _SB_MAKEMASK1(7)

/*
 * DUART Status Register (Table 10-6)
 * Register: DUART_STATUS_A
 * Register: DUART_STATUS_B
 * READ-ONLY
 */

#घोषणा M_DUART_RX_RDY		    _SB_MAKEMASK1(0)
#घोषणा M_DUART_RX_FFUL		    _SB_MAKEMASK1(1)
#घोषणा M_DUART_TX_RDY		    _SB_MAKEMASK1(2)
#घोषणा M_DUART_TX_EMT		    _SB_MAKEMASK1(3)
#घोषणा M_DUART_OVRUN_ERR	    _SB_MAKEMASK1(4)
#घोषणा M_DUART_PARITY_ERR	    _SB_MAKEMASK1(5)
#घोषणा M_DUART_FRM_ERR		    _SB_MAKEMASK1(6)
#घोषणा M_DUART_RCVD_BRK	    _SB_MAKEMASK1(7)

/*
 * DUART Baud Rate Register (Table 10-7)
 * Register: DUART_CLK_SEL_A
 * Register: DUART_CLK_SEL_B
 */

#घोषणा M_DUART_CLK_COUNTER	    _SB_MAKEMASK(12, 0)
#घोषणा V_DUART_BAUD_RATE(x)	    (100000000/((x)*20)-1)

/*
 * DUART Data Registers (Table 10-8 and 10-9)
 * Register: DUART_RX_HOLD_A
 * Register: DUART_RX_HOLD_B
 * Register: DUART_TX_HOLD_A
 * Register: DUART_TX_HOLD_B
 */

#घोषणा M_DUART_RX_DATA		    _SB_MAKEMASK(8, 0)
#घोषणा M_DUART_TX_DATA		    _SB_MAKEMASK(8, 0)

/*
 * DUART Input Port Register (Table 10-10)
 * Register: DUART_IN_PORT
 */

#घोषणा M_DUART_IN_PIN0_VAL	    _SB_MAKEMASK1(0)
#घोषणा M_DUART_IN_PIN1_VAL	    _SB_MAKEMASK1(1)
#घोषणा M_DUART_IN_PIN2_VAL	    _SB_MAKEMASK1(2)
#घोषणा M_DUART_IN_PIN3_VAL	    _SB_MAKEMASK1(3)
#घोषणा M_DUART_IN_PIN4_VAL	    _SB_MAKEMASK1(4)
#घोषणा M_DUART_IN_PIN5_VAL	    _SB_MAKEMASK1(5)
#घोषणा M_DUART_RIN0_PIN	    _SB_MAKEMASK1(6)
#घोषणा M_DUART_RIN1_PIN	    _SB_MAKEMASK1(7)

/*
 * DUART Input Port Change Status Register (Tables 10-11, 10-12, and 10-13)
 * Register: DUART_INPORT_CHNG
 */

#घोषणा S_DUART_IN_PIN_VAL	    0
#घोषणा M_DUART_IN_PIN_VAL	    _SB_MAKEMASK(4, S_DUART_IN_PIN_VAL)

#घोषणा S_DUART_IN_PIN_CHNG	    4
#घोषणा M_DUART_IN_PIN_CHNG	    _SB_MAKEMASK(4, S_DUART_IN_PIN_CHNG)


/*
 * DUART Output port control रेजिस्टर (Table 10-14)
 * Register: DUART_OPCR
 */

#घोषणा M_DUART_OPCR_RESERVED0	    _SB_MAKEMASK1(0)   /* must be zero */
#घोषणा M_DUART_OPC2_SEL	    _SB_MAKEMASK1(1)
#घोषणा M_DUART_OPCR_RESERVED1	    _SB_MAKEMASK1(2)   /* must be zero */
#घोषणा M_DUART_OPC3_SEL	    _SB_MAKEMASK1(3)
#घोषणा M_DUART_OPCR_RESERVED2	    _SB_MAKEMASK(4, 4)	/* must be zero */

/*
 * DUART Aux Control Register (Table 10-15)
 * Register: DUART_AUX_CTRL
 */

#घोषणा M_DUART_IP0_CHNG_ENA	    _SB_MAKEMASK1(0)
#घोषणा M_DUART_IP1_CHNG_ENA	    _SB_MAKEMASK1(1)
#घोषणा M_DUART_IP2_CHNG_ENA	    _SB_MAKEMASK1(2)
#घोषणा M_DUART_IP3_CHNG_ENA	    _SB_MAKEMASK1(3)
#घोषणा M_DUART_ACR_RESERVED	    _SB_MAKEMASK(4, 4)

#घोषणा M_DUART_CTS_CHNG_ENA	    _SB_MAKEMASK1(0)
#घोषणा M_DUART_CIN_CHNG_ENA	    _SB_MAKEMASK1(2)

/*
 * DUART Interrupt Status Register (Table 10-16)
 * Register: DUART_ISR
 */

#घोषणा M_DUART_ISR_TX_A	    _SB_MAKEMASK1(0)

#घोषणा S_DUART_ISR_RX_A	    1
#घोषणा M_DUART_ISR_RX_A	    _SB_MAKEMASK1(S_DUART_ISR_RX_A)
#घोषणा V_DUART_ISR_RX_A(x)	    _SB_MAKEVALUE(x, S_DUART_ISR_RX_A)
#घोषणा G_DUART_ISR_RX_A(x)	    _SB_GETVALUE(x, S_DUART_ISR_RX_A, M_DUART_ISR_RX_A)

#घोषणा M_DUART_ISR_BRK_A	    _SB_MAKEMASK1(2)
#घोषणा M_DUART_ISR_IN_A	    _SB_MAKEMASK1(3)
#घोषणा M_DUART_ISR_ALL_A	    _SB_MAKEMASK(4, 0)

#घोषणा M_DUART_ISR_TX_B	    _SB_MAKEMASK1(4)
#घोषणा M_DUART_ISR_RX_B	    _SB_MAKEMASK1(5)
#घोषणा M_DUART_ISR_BRK_B	    _SB_MAKEMASK1(6)
#घोषणा M_DUART_ISR_IN_B	    _SB_MAKEMASK1(7)
#घोषणा M_DUART_ISR_ALL_B	    _SB_MAKEMASK(4, 4)

/*
 * DUART Channel A Interrupt Status Register (Table 10-17)
 * DUART Channel B Interrupt Status Register (Table 10-18)
 * Register: DUART_ISR_A
 * Register: DUART_ISR_B
 */

#घोषणा M_DUART_ISR_TX		    _SB_MAKEMASK1(0)
#घोषणा M_DUART_ISR_RX		    _SB_MAKEMASK1(1)
#घोषणा M_DUART_ISR_BRK		    _SB_MAKEMASK1(2)
#घोषणा M_DUART_ISR_IN		    _SB_MAKEMASK1(3)
#घोषणा M_DUART_ISR_ALL		    _SB_MAKEMASK(4, 0)
#घोषणा M_DUART_ISR_RESERVED	    _SB_MAKEMASK(4, 4)

/*
 * DUART Interrupt Mask Register (Table 10-19)
 * Register: DUART_IMR
 */

#घोषणा M_DUART_IMR_TX_A	    _SB_MAKEMASK1(0)
#घोषणा M_DUART_IMR_RX_A	    _SB_MAKEMASK1(1)
#घोषणा M_DUART_IMR_BRK_A	    _SB_MAKEMASK1(2)
#घोषणा M_DUART_IMR_IN_A	    _SB_MAKEMASK1(3)
#घोषणा M_DUART_IMR_ALL_A	    _SB_MAKEMASK(4, 0)

#घोषणा M_DUART_IMR_TX_B	    _SB_MAKEMASK1(4)
#घोषणा M_DUART_IMR_RX_B	    _SB_MAKEMASK1(5)
#घोषणा M_DUART_IMR_BRK_B	    _SB_MAKEMASK1(6)
#घोषणा M_DUART_IMR_IN_B	    _SB_MAKEMASK1(7)
#घोषणा M_DUART_IMR_ALL_B	    _SB_MAKEMASK(4, 4)

/*
 * DUART Channel A Interrupt Mask Register (Table 10-20)
 * DUART Channel B Interrupt Mask Register (Table 10-21)
 * Register: DUART_IMR_A
 * Register: DUART_IMR_B
 */

#घोषणा M_DUART_IMR_TX		    _SB_MAKEMASK1(0)
#घोषणा M_DUART_IMR_RX		    _SB_MAKEMASK1(1)
#घोषणा M_DUART_IMR_BRK		    _SB_MAKEMASK1(2)
#घोषणा M_DUART_IMR_IN		    _SB_MAKEMASK1(3)
#घोषणा M_DUART_IMR_ALL		    _SB_MAKEMASK(4, 0)
#घोषणा M_DUART_IMR_RESERVED	    _SB_MAKEMASK(4, 4)


/*
 * DUART Output Port Set Register (Table 10-22)
 * Register: DUART_SET_OPR
 */

#घोषणा M_DUART_SET_OPR0	    _SB_MAKEMASK1(0)
#घोषणा M_DUART_SET_OPR1	    _SB_MAKEMASK1(1)
#घोषणा M_DUART_SET_OPR2	    _SB_MAKEMASK1(2)
#घोषणा M_DUART_SET_OPR3	    _SB_MAKEMASK1(3)
#घोषणा M_DUART_OPSR_RESERVED	    _SB_MAKEMASK(4, 4)

/*
 * DUART Output Port Clear Register (Table 10-23)
 * Register: DUART_CLEAR_OPR
 */

#घोषणा M_DUART_CLR_OPR0	    _SB_MAKEMASK1(0)
#घोषणा M_DUART_CLR_OPR1	    _SB_MAKEMASK1(1)
#घोषणा M_DUART_CLR_OPR2	    _SB_MAKEMASK1(2)
#घोषणा M_DUART_CLR_OPR3	    _SB_MAKEMASK1(3)
#घोषणा M_DUART_OPCR_RESERVED	    _SB_MAKEMASK(4, 4)

/*
 * DUART Output Port RTS Register (Table 10-24)
 * Register: DUART_OUT_PORT
 */

#घोषणा M_DUART_OUT_PIN_SET0	    _SB_MAKEMASK1(0)
#घोषणा M_DUART_OUT_PIN_SET1	    _SB_MAKEMASK1(1)
#घोषणा M_DUART_OUT_PIN_CLR0	    _SB_MAKEMASK1(2)
#घोषणा M_DUART_OUT_PIN_CLR1	    _SB_MAKEMASK1(3)
#घोषणा M_DUART_OPRR_RESERVED	    _SB_MAKEMASK(4, 4)

#घोषणा M_DUART_OUT_PIN_SET(chan) \
    (chan == 0 ? M_DUART_OUT_PIN_SET0 : M_DUART_OUT_PIN_SET1)
#घोषणा M_DUART_OUT_PIN_CLR(chan) \
    (chan == 0 ? M_DUART_OUT_PIN_CLR0 : M_DUART_OUT_PIN_CLR1)

#अगर SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1) || SIBYTE_HDR_FEATURE_CHIP(1480)
/*
 * Full Interrupt Control Register
 */

#घोषणा S_DUART_SIG_FULL	   _SB_MAKE64(0)
#घोषणा M_DUART_SIG_FULL	   _SB_MAKEMASK(4, S_DUART_SIG_FULL)
#घोषणा V_DUART_SIG_FULL(x)	   _SB_MAKEVALUE(x, S_DUART_SIG_FULL)
#घोषणा G_DUART_SIG_FULL(x)	   _SB_GETVALUE(x, S_DUART_SIG_FULL, M_DUART_SIG_FULL)

#घोषणा S_DUART_INT_TIME	   _SB_MAKE64(4)
#घोषणा M_DUART_INT_TIME	   _SB_MAKEMASK(4, S_DUART_INT_TIME)
#घोषणा V_DUART_INT_TIME(x)	   _SB_MAKEVALUE(x, S_DUART_INT_TIME)
#घोषणा G_DUART_INT_TIME(x)	   _SB_GETVALUE(x, S_DUART_INT_TIME, M_DUART_INT_TIME)
#पूर्ण_अगर /* 1250 PASS2 || 112x PASS1 || 1480 */


/* ********************************************************************** */


#पूर्ण_अगर
