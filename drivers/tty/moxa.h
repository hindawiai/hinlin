<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित MOXA_H_खाता
#घोषणा MOXA_H_खाता

#घोषणा	MOXA		0x400
#घोषणा MOXA_GET_IQUEUE 	(MOXA + 1)	/* get input buffered count */
#घोषणा MOXA_GET_OQUEUE 	(MOXA + 2)	/* get output buffered count */
#घोषणा MOXA_GETDATACOUNT       (MOXA + 23)
#घोषणा MOXA_GET_IOQUEUE	(MOXA + 27)
#घोषणा MOXA_FLUSH_QUEUE	(MOXA + 28)
#घोषणा MOXA_GETMSTATUS         (MOXA + 65)

/*
 *    System Configuration
 */

#घोषणा Magic_code	0x404

/*
 *    क्रम C218 BIOS initialization
 */
#घोषणा C218_ConfBase	0x800
#घोषणा C218_status	(C218_ConfBase + 0)	/* BIOS running status    */
#घोषणा C218_diag	(C218_ConfBase + 2)	/* diagnostic status      */
#घोषणा C218_key	(C218_ConfBase + 4)	/* WORD (0x218 क्रम C218) */
#घोषणा C218DLoad_len	(C218_ConfBase + 6)	/* WORD           */
#घोषणा C218check_sum	(C218_ConfBase + 8)	/* BYTE           */
#घोषणा C218chksum_ok	(C218_ConfBase + 0x0a)	/* BYTE (1:ok)            */
#घोषणा C218_TestRx	(C218_ConfBase + 0x10)	/* 8 bytes क्रम 8 ports    */
#घोषणा C218_TestTx	(C218_ConfBase + 0x18)	/* 8 bytes क्रम 8 ports    */
#घोषणा C218_RXerr	(C218_ConfBase + 0x20)	/* 8 bytes क्रम 8 ports    */
#घोषणा C218_ErrFlag	(C218_ConfBase + 0x28)	/* 8 bytes क्रम 8 ports    */

#घोषणा C218_LoadBuf	0x0F00
#घोषणा C218_KeyCode	0x218
#घोषणा CP204J_KeyCode	0x204

/*
 *    क्रम C320 BIOS initialization
 */
#घोषणा C320_ConfBase	0x800
#घोषणा C320_LoadBuf	0x0f00
#घोषणा STS_init	0x05	/* क्रम C320_status        */

#घोषणा C320_status	C320_ConfBase + 0	/* BIOS running status    */
#घोषणा C320_diag	C320_ConfBase + 2	/* diagnostic status      */
#घोषणा C320_key	C320_ConfBase + 4	/* WORD (0320H क्रम C320) */
#घोषणा C320DLoad_len	C320_ConfBase + 6	/* WORD           */
#घोषणा C320check_sum	C320_ConfBase + 8	/* WORD           */
#घोषणा C320chksum_ok	C320_ConfBase + 0x0a	/* WORD (1:ok)            */
#घोषणा C320bapi_len	C320_ConfBase + 0x0c	/* WORD           */
#घोषणा C320UART_no	C320_ConfBase + 0x0e	/* WORD           */

#घोषणा C320_KeyCode	0x320

#घोषणा FixPage_addr	0x0000	/* starting addr of अटल page  */
#घोषणा DynPage_addr	0x2000	/* starting addr of dynamic page */
#घोषणा C218_start	0x3000	/* starting addr of C218 BIOS prg */
#घोषणा Control_reg	0x1ff0	/* select page and reset control */
#घोषणा HW_reset	0x80

/*
 *    Function Codes
 */
#घोषणा FC_CardReset	0x80
#घोषणा FC_ChannelReset 1	/* C320 firmware not supported */
#घोषणा FC_EnableCH	2
#घोषणा FC_DisableCH	3
#घोषणा FC_SetParam	4
#घोषणा FC_SetMode	5
#घोषणा FC_SetRate	6
#घोषणा FC_LineControl	7
#घोषणा FC_LineStatus	8
#घोषणा FC_XmitControl	9
#घोषणा FC_FlushQueue	10
#घोषणा FC_SendBreak	11
#घोषणा FC_StopBreak	12
#घोषणा FC_LoopbackON	13
#घोषणा FC_LoopbackOFF	14
#घोषणा FC_ClrIrqTable	15
#घोषणा FC_SendXon	16
#घोषणा FC_SetTermIrq	17	/* C320 firmware not supported */
#घोषणा FC_SetCntIrq	18	/* C320 firmware not supported */
#घोषणा FC_SetBreakIrq	19
#घोषणा FC_SetLineIrq	20
#घोषणा FC_SetFlowCtl	21
#घोषणा FC_GenIrq	22
#घोषणा FC_InCD180	23
#घोषणा FC_OutCD180	24
#घोषणा FC_InUARTreg	23
#घोषणा FC_OutUARTreg	24
#घोषणा FC_SetXonXoff	25
#घोषणा FC_OutCD180CCR	26
#घोषणा FC_ExtIQueue	27
#घोषणा FC_ExtOQueue	28
#घोषणा FC_ClrLineIrq	29
#घोषणा FC_HWFlowCtl	30
#घोषणा FC_GetClockRate 35
#घोषणा FC_SetBaud	36
#घोषणा FC_SetDataMode  41
#घोषणा FC_GetCCSR      43
#घोषणा FC_GetDataError 45
#घोषणा FC_RxControl	50
#घोषणा FC_ImmSend	51
#घोषणा FC_SetXonState	52
#घोषणा FC_SetXoffState	53
#घोषणा FC_SetRxFIFOTrig 54
#घोषणा FC_SetTxFIFOCnt 55
#घोषणा FC_UnixRate	56
#घोषणा FC_UnixResetTimer 57

#घोषणा	RxFIFOTrig1	0
#घोषणा	RxFIFOTrig4	1
#घोषणा	RxFIFOTrig8	2
#घोषणा	RxFIFOTrig14	3

/*
 *    Dual-Ported RAM
 */
#घोषणा DRAM_global	0
#घोषणा INT_data	(DRAM_global + 0)
#घोषणा Config_base	(DRAM_global + 0x108)

#घोषणा IRQindex	(INT_data + 0)
#घोषणा IRQpending	(INT_data + 4)
#घोषणा IRQtable	(INT_data + 8)

/*
 *    Interrupt Status
 */
#घोषणा IntrRx		0x01	/* receiver data O.K.             */
#घोषणा IntrTx		0x02	/* transmit buffer empty  */
#घोषणा IntrFunc	0x04	/* function complete              */
#घोषणा IntrBreak	0x08	/* received अवरोध         */
#घोषणा IntrLine	0x10	/* line status change
				   क्रम transmitter                */
#घोषणा IntrIntr	0x20	/* received INTR code             */
#घोषणा IntrQuit	0x40	/* received QUIT code             */
#घोषणा Intrखातापूर्ण 	0x80	/* received खातापूर्ण code              */

#घोषणा IntrRxTrigger 	0x100	/* rx data count reach trigger value */
#घोषणा IntrTxTrigger 	0x200	/* tx data count below trigger value */

#घोषणा Magic_no	(Config_base + 0)
#घोषणा Card_model_no	(Config_base + 2)
#घोषणा Total_ports	(Config_base + 4)
#घोषणा Module_cnt	(Config_base + 8)
#घोषणा Module_no	(Config_base + 10)
#घोषणा Timer_10ms	(Config_base + 14)
#घोषणा Disable_IRQ	(Config_base + 20)
#घोषणा TMS320_PORT1	(Config_base + 22)
#घोषणा TMS320_PORT2	(Config_base + 24)
#घोषणा TMS320_CLOCK	(Config_base + 26)

/*
 *    DATA BUFFER in DRAM
 */
#घोषणा Extern_table	0x400	/* Base address of the बाह्यal table
				   (24 words *    64) total 3K bytes
				   (24 words * 128) total 6K bytes */
#घोषणा Extern_size	0x60	/* 96 bytes                       */
#घोषणा RXrptr		0x00	/* पढ़ो poपूर्णांकer क्रम RX buffer     */
#घोषणा RXwptr		0x02	/* ग_लिखो poपूर्णांकer क्रम RX buffer    */
#घोषणा TXrptr		0x04	/* पढ़ो poपूर्णांकer क्रम TX buffer     */
#घोषणा TXwptr		0x06	/* ग_लिखो poपूर्णांकer क्रम TX buffer    */
#घोषणा HostStat	0x08	/* IRQ flag and general flag      */
#घोषणा FlagStat	0x0A
#घोषणा FlowControl	0x0C	/* B7 B6 B5 B4 B3 B2 B1 B0              */
				/*  x  x  x  x  |  |  |  |            */
				/*              |  |  |  + CTS flow   */
				/*              |  |  +--- RTS flow   */
				/*              |  +------ TX Xon/Xoff */
				/*              +--------- RX Xon/Xoff */
#घोषणा Break_cnt	0x0E	/* received अवरोध count   */
#घोषणा CD180TXirq	0x10	/* अगर non-0: enable TX irq        */
#घोषणा RX_mask 	0x12
#घोषणा TX_mask 	0x14
#घोषणा Ofs_rxb 	0x16
#घोषणा Ofs_txb 	0x18
#घोषणा Page_rxb	0x1A
#घोषणा Page_txb	0x1C
#घोषणा EndPage_rxb	0x1E
#घोषणा EndPage_txb	0x20
#घोषणा Data_error	0x22
#घोषणा RxTrigger	0x28
#घोषणा TxTrigger	0x2a

#घोषणा rRXwptr 	0x34
#घोषणा Low_water	0x36

#घोषणा FuncCode	0x40
#घोषणा FuncArg 	0x42
#घोषणा FuncArg1	0x44

#घोषणा C218rx_size	0x2000	/* 8K bytes */
#घोषणा C218tx_size	0x8000	/* 32K bytes */

#घोषणा C218rx_mask	(C218rx_size - 1)
#घोषणा C218tx_mask	(C218tx_size - 1)

#घोषणा C320p8rx_size	0x2000
#घोषणा C320p8tx_size	0x8000
#घोषणा C320p8rx_mask	(C320p8rx_size - 1)
#घोषणा C320p8tx_mask	(C320p8tx_size - 1)

#घोषणा C320p16rx_size	0x2000
#घोषणा C320p16tx_size	0x4000
#घोषणा C320p16rx_mask	(C320p16rx_size - 1)
#घोषणा C320p16tx_mask	(C320p16tx_size - 1)

#घोषणा C320p24rx_size	0x2000
#घोषणा C320p24tx_size	0x2000
#घोषणा C320p24rx_mask	(C320p24rx_size - 1)
#घोषणा C320p24tx_mask	(C320p24tx_size - 1)

#घोषणा C320p32rx_size	0x1000
#घोषणा C320p32tx_size	0x1000
#घोषणा C320p32rx_mask	(C320p32rx_size - 1)
#घोषणा C320p32tx_mask	(C320p32tx_size - 1)

#घोषणा Page_size	0x2000U
#घोषणा Page_mask	(Page_size - 1)
#घोषणा C218rx_spage	3
#घोषणा C218tx_spage	4
#घोषणा C218rx_pageno	1
#घोषणा C218tx_pageno	4
#घोषणा C218buf_pageno	5

#घोषणा C320p8rx_spage	3
#घोषणा C320p8tx_spage	4
#घोषणा C320p8rx_pgno	1
#घोषणा C320p8tx_pgno	4
#घोषणा C320p8buf_pgno	5

#घोषणा C320p16rx_spage 3
#घोषणा C320p16tx_spage 4
#घोषणा C320p16rx_pgno	1
#घोषणा C320p16tx_pgno	2
#घोषणा C320p16buf_pgno 3

#घोषणा C320p24rx_spage 3
#घोषणा C320p24tx_spage 4
#घोषणा C320p24rx_pgno	1
#घोषणा C320p24tx_pgno	1
#घोषणा C320p24buf_pgno 2

#घोषणा C320p32rx_spage 3
#घोषणा C320p32tx_ofs	C320p32rx_size
#घोषणा C320p32tx_spage 3
#घोषणा C320p32buf_pgno 1

/*
 *    Host Status
 */
#घोषणा WakeupRx	0x01
#घोषणा WakeupTx	0x02
#घोषणा WakeupBreak	0x08
#घोषणा WakeupLine	0x10
#घोषणा WakeupIntr	0x20
#घोषणा WakeupQuit	0x40
#घोषणा Wakeupखातापूर्ण	0x80	/* used in VTIME control */
#घोषणा WakeupRxTrigger	0x100
#घोषणा WakeupTxTrigger	0x200
/*
 *    Flag status
 */
#घोषणा Rx_over		0x01
#घोषणा Xoff_state	0x02
#घोषणा Tx_flowOff	0x04
#घोषणा Tx_enable	0x08
#घोषणा CTS_state	0x10
#घोषणा DSR_state	0x20
#घोषणा DCD_state	0x80
/*
 *    FlowControl
 */
#घोषणा CTS_FlowCtl	1
#घोषणा RTS_FlowCtl	2
#घोषणा Tx_FlowCtl	4
#घोषणा Rx_FlowCtl	8
#घोषणा IXM_IXANY	0x10

#घोषणा LowWater	128

#घोषणा DTR_ON		1
#घोषणा RTS_ON		2
#घोषणा CTS_ON		1
#घोषणा DSR_ON		2
#घोषणा DCD_ON		8

/* mode definition */
#घोषणा	MX_CS8		0x03
#घोषणा	MX_CS7		0x02
#घोषणा	MX_CS6		0x01
#घोषणा	MX_CS5		0x00

#घोषणा	MX_STOP1	0x00
#घोषणा	MX_STOP15	0x04
#घोषणा	MX_STOP2	0x08

#घोषणा	MX_PARNONE	0x00
#घोषणा	MX_PAREVEN	0x40
#घोषणा	MX_PARODD	0xC0
#घोषणा	MX_PARMARK	0xA0
#घोषणा	MX_PARSPACE	0x20

#पूर्ण_अगर
