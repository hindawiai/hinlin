<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	खाता    	SA-1100.h
 *
 *	Version 	1.2
 *	Author  	Copyright (c) Marc A. Viredaz, 1998
 *	        	DEC Western Research Laboratory, Palo Alto, CA
 *	Date    	January 1998 (April 1997)
 *	System  	StrongARM SA-1100
 *	Language	C or ARM Assembly
 *	Purpose 	Definition of स्थिरants related to the StrongARM
 *	        	SA-1100 microprocessor (Advanced RISC Machine (ARM)
 *	        	architecture version 4). This file is based on the
 *	        	StrongARM SA-1100 data sheet version 2.2.
 *
 */


/* Be sure that भव mapping is defined right */
#अगर_अघोषित __ASM_ARCH_HARDWARE_H
#त्रुटि You must include hardware.h not SA-1100.h
#पूर्ण_अगर

#समावेश "bitfield.h"

/*
 * SA1100 CS line to physical address
 */

#घोषणा SA1100_CS0_PHYS	0x00000000
#घोषणा SA1100_CS1_PHYS	0x08000000
#घोषणा SA1100_CS2_PHYS	0x10000000
#घोषणा SA1100_CS3_PHYS	0x18000000
#घोषणा SA1100_CS4_PHYS	0x40000000
#घोषणा SA1100_CS5_PHYS	0x48000000

/*
 * Personal Computer Memory Card International Association (PCMCIA) sockets
 */

#घोषणा PCMCIAPrtSp	0x04000000	/* PCMCIA Partition Space [byte]   */
#घोषणा PCMCIASp	(4*PCMCIAPrtSp)	/* PCMCIA Space [byte]             */
#घोषणा PCMCIAIOSp	PCMCIAPrtSp	/* PCMCIA I/O Space [byte]         */
#घोषणा PCMCIAAttrSp	PCMCIAPrtSp	/* PCMCIA Attribute Space [byte]   */
#घोषणा PCMCIAMemSp	PCMCIAPrtSp	/* PCMCIA Memory Space [byte]      */

#घोषणा PCMCIA0Sp	PCMCIASp	/* PCMCIA 0 Space [byte]           */
#घोषणा PCMCIA0IOSp	PCMCIAIOSp	/* PCMCIA 0 I/O Space [byte]       */
#घोषणा PCMCIA0AttrSp	PCMCIAAttrSp	/* PCMCIA 0 Attribute Space [byte] */
#घोषणा PCMCIA0MemSp	PCMCIAMemSp	/* PCMCIA 0 Memory Space [byte]    */

#घोषणा PCMCIA1Sp	PCMCIASp	/* PCMCIA 1 Space [byte]           */
#घोषणा PCMCIA1IOSp	PCMCIAIOSp	/* PCMCIA 1 I/O Space [byte]       */
#घोषणा PCMCIA1AttrSp	PCMCIAAttrSp	/* PCMCIA 1 Attribute Space [byte] */
#घोषणा PCMCIA1MemSp	PCMCIAMemSp	/* PCMCIA 1 Memory Space [byte]    */

#घोषणा _PCMCIA(Nb)	        	/* PCMCIA [0..1]                   */ \
                	(0x20000000 + (Nb)*PCMCIASp)
#घोषणा _PCMCIAIO(Nb)	_PCMCIA (Nb)	/* PCMCIA I/O [0..1]               */
#घोषणा _PCMCIAAttr(Nb)	        	/* PCMCIA Attribute [0..1]         */ \
                	(_PCMCIA (Nb) + 2*PCMCIAPrtSp)
#घोषणा _PCMCIAMem(Nb)	        	/* PCMCIA Memory [0..1]            */ \
                	(_PCMCIA (Nb) + 3*PCMCIAPrtSp)

#घोषणा _PCMCIA0	_PCMCIA (0)	/* PCMCIA 0                        */
#घोषणा _PCMCIA0IO	_PCMCIAIO (0)	/* PCMCIA 0 I/O                    */
#घोषणा _PCMCIA0Attr	_PCMCIAAttr (0)	/* PCMCIA 0 Attribute              */
#घोषणा _PCMCIA0Mem	_PCMCIAMem (0)	/* PCMCIA 0 Memory                 */

#घोषणा _PCMCIA1	_PCMCIA (1)	/* PCMCIA 1                        */
#घोषणा _PCMCIA1IO	_PCMCIAIO (1)	/* PCMCIA 1 I/O                    */
#घोषणा _PCMCIA1Attr	_PCMCIAAttr (1)	/* PCMCIA 1 Attribute              */
#घोषणा _PCMCIA1Mem	_PCMCIAMem (1)	/* PCMCIA 1 Memory                 */


/*
 * Universal Serial Bus (USB) Device Controller (UDC) control रेजिस्टरs
 *
 * Registers
 *    Ser0UDCCR 	Serial port 0 Universal Serial Bus (USB) Device
 *              	Controller (UDC) Control Register (पढ़ो/ग_लिखो).
 *    Ser0UDCAR 	Serial port 0 Universal Serial Bus (USB) Device
 *              	Controller (UDC) Address Register (पढ़ो/ग_लिखो).
 *    Ser0UDCOMP	Serial port 0 Universal Serial Bus (USB) Device
 *              	Controller (UDC) Output Maximum Packet size रेजिस्टर
 *              	(पढ़ो/ग_लिखो).
 *    Ser0UDCIMP	Serial port 0 Universal Serial Bus (USB) Device
 *              	Controller (UDC) Input Maximum Packet size रेजिस्टर
 *              	(पढ़ो/ग_लिखो).
 *    Ser0UDCCS0	Serial port 0 Universal Serial Bus (USB) Device
 *              	Controller (UDC) Control/Status रेजिस्टर end-poपूर्णांक 0
 *              	(पढ़ो/ग_लिखो).
 *    Ser0UDCCS1	Serial port 0 Universal Serial Bus (USB) Device
 *              	Controller (UDC) Control/Status रेजिस्टर end-poपूर्णांक 1
 *              	(output, पढ़ो/ग_लिखो).
 *    Ser0UDCCS2	Serial port 0 Universal Serial Bus (USB) Device
 *              	Controller (UDC) Control/Status रेजिस्टर end-poपूर्णांक 2
 *              	(input, पढ़ो/ग_लिखो).
 *    Ser0UDCD0 	Serial port 0 Universal Serial Bus (USB) Device
 *              	Controller (UDC) Data रेजिस्टर end-poपूर्णांक 0
 *              	(पढ़ो/ग_लिखो).
 *    Ser0UDCWC 	Serial port 0 Universal Serial Bus (USB) Device
 *              	Controller (UDC) Write Count रेजिस्टर end-poपूर्णांक 0
 *              	(पढ़ो).
 *    Ser0UDCDR 	Serial port 0 Universal Serial Bus (USB) Device
 *              	Controller (UDC) Data Register (पढ़ो/ग_लिखो).
 *    Ser0UDCSR 	Serial port 0 Universal Serial Bus (USB) Device
 *              	Controller (UDC) Status Register (पढ़ो/ग_लिखो).
 */

#घोषणा Ser0UDCCR	__REG(0x80000000)  /* Ser. port 0 UDC Control Reg. */
#घोषणा Ser0UDCAR	__REG(0x80000004)  /* Ser. port 0 UDC Address Reg. */
#घोषणा Ser0UDCOMP	__REG(0x80000008)  /* Ser. port 0 UDC Output Maximum Packet size reg. */
#घोषणा Ser0UDCIMP	__REG(0x8000000C)  /* Ser. port 0 UDC Input Maximum Packet size reg. */
#घोषणा Ser0UDCCS0	__REG(0x80000010)  /* Ser. port 0 UDC Control/Status reg. end-poपूर्णांक 0 */
#घोषणा Ser0UDCCS1	__REG(0x80000014)  /* Ser. port 0 UDC Control/Status reg. end-poपूर्णांक 1 (output) */
#घोषणा Ser0UDCCS2	__REG(0x80000018)  /* Ser. port 0 UDC Control/Status reg. end-poपूर्णांक 2 (input) */
#घोषणा Ser0UDCD0	__REG(0x8000001C)  /* Ser. port 0 UDC Data reg. end-poपूर्णांक 0 */
#घोषणा Ser0UDCWC	__REG(0x80000020)  /* Ser. port 0 UDC Write Count reg. end-poपूर्णांक 0 */
#घोषणा Ser0UDCDR	__REG(0x80000028)  /* Ser. port 0 UDC Data Reg. */
#घोषणा Ser0UDCSR	__REG(0x80000030)  /* Ser. port 0 UDC Status Reg. */

#घोषणा UDCCR_UDD	0x00000001	/* UDC Disable                     */
#घोषणा UDCCR_UDA	0x00000002	/* UDC Active (पढ़ो)               */
#घोषणा UDCCR_RESIM	0x00000004	/* Resume Interrupt Mask, per errata */
#घोषणा UDCCR_EIM	0x00000008	/* End-poपूर्णांक 0 Interrupt Mask      */
                	        	/* (disable)                       */
#घोषणा UDCCR_RIM	0x00000010	/* Receive Interrupt Mask          */
                	        	/* (disable)                       */
#घोषणा UDCCR_TIM	0x00000020	/* Transmit Interrupt Mask         */
                	        	/* (disable)                       */
#घोषणा UDCCR_SRM	0x00000040	/* Suspend/Resume पूर्णांकerrupt Mask   */
                	        	/* (disable)                       */
#घोषणा UDCCR_SUSIM	UDCCR_SRM	/* Per errata, SRM just masks suspend */
#घोषणा UDCCR_REM	0x00000080	/* REset पूर्णांकerrupt Mask (disable)  */

#घोषणा UDCAR_ADD	Fld (7, 0)	/* function ADDress                */

#घोषणा UDCOMP_OUTMAXP	Fld (8, 0)	/* OUTput MAXimum Packet size - 1  */
                	        	/* [byte]                          */
#घोषणा UDCOMP_OutMaxPkt(Size)  	/* Output Maximum Packet size      */ \
                	        	/* [1..256 byte]                   */ \
                	(((Size) - 1) << FShft (UDCOMP_OUTMAXP))

#घोषणा UDCIMP_INMAXP	Fld (8, 0)	/* INput MAXimum Packet size - 1   */
                	        	/* [byte]                          */
#घोषणा UDCIMP_InMaxPkt(Size)   	/* Input Maximum Packet size       */ \
                	        	/* [1..256 byte]                   */ \
                	(((Size) - 1) << FShft (UDCIMP_INMAXP))

#घोषणा UDCCS0_OPR	0x00000001	/* Output Packet Ready (पढ़ो)      */
#घोषणा UDCCS0_IPR	0x00000002	/* Input Packet Ready              */
#घोषणा UDCCS0_SST	0x00000004	/* Sent STall                      */
#घोषणा UDCCS0_FST	0x00000008	/* Force STall                     */
#घोषणा UDCCS0_DE	0x00000010	/* Data End                        */
#घोषणा UDCCS0_SE	0x00000020	/* Setup End (पढ़ो)                */
#घोषणा UDCCS0_SO	0x00000040	/* Serviced Output packet पढ़ोy    */
                	        	/* (ग_लिखो)                         */
#घोषणा UDCCS0_SSE	0x00000080	/* Serviced Setup End (ग_लिखो)      */

#घोषणा UDCCS1_RFS	0x00000001	/* Receive FIFO 12-bytes or more   */
                	        	/* Service request (पढ़ो)          */
#घोषणा UDCCS1_RPC	0x00000002	/* Receive Packet Complete         */
#घोषणा UDCCS1_RPE	0x00000004	/* Receive Packet Error (पढ़ो)     */
#घोषणा UDCCS1_SST	0x00000008	/* Sent STall                      */
#घोषणा UDCCS1_FST	0x00000010	/* Force STall                     */
#घोषणा UDCCS1_RNE	0x00000020	/* Receive FIFO Not Empty (पढ़ो)   */

#घोषणा UDCCS2_TFS	0x00000001	/* Transmit FIFO 8-bytes or less   */
                	        	/* Service request (पढ़ो)          */
#घोषणा UDCCS2_TPC	0x00000002	/* Transmit Packet Complete        */
#घोषणा UDCCS2_TPE	0x00000004	/* Transmit Packet Error (पढ़ो)    */
#घोषणा UDCCS2_TUR	0x00000008	/* Transmit FIFO Under-Run         */
#घोषणा UDCCS2_SST	0x00000010	/* Sent STall                      */
#घोषणा UDCCS2_FST	0x00000020	/* Force STall                     */

#घोषणा UDCD0_DATA	Fld (8, 0)	/* receive/transmit DATA FIFOs     */

#घोषणा UDCWC_WC	Fld (4, 0)	/* Write Count                     */

#घोषणा UDCDR_DATA	Fld (8, 0)	/* receive/transmit DATA FIFOs     */

#घोषणा UDCSR_EIR	0x00000001	/* End-poपूर्णांक 0 Interrupt Request   */
#घोषणा UDCSR_RIR	0x00000002	/* Receive Interrupt Request       */
#घोषणा UDCSR_TIR	0x00000004	/* Transmit Interrupt Request      */
#घोषणा UDCSR_SUSIR	0x00000008	/* SUSpend Interrupt Request       */
#घोषणा UDCSR_RESIR	0x00000010	/* RESume Interrupt Request        */
#घोषणा UDCSR_RSTIR	0x00000020	/* ReSeT Interrupt Request         */


/*
 * Universal Asynchronous Receiver/Transmitter (UART) control रेजिस्टरs
 *
 * Registers
 *    Ser1UTCR0 	Serial port 1 Universal Asynchronous
 *              	Receiver/Transmitter (UART) Control Register 0
 *              	(पढ़ो/ग_लिखो).
 *    Ser1UTCR1 	Serial port 1 Universal Asynchronous
 *              	Receiver/Transmitter (UART) Control Register 1
 *              	(पढ़ो/ग_लिखो).
 *    Ser1UTCR2 	Serial port 1 Universal Asynchronous
 *              	Receiver/Transmitter (UART) Control Register 2
 *              	(पढ़ो/ग_लिखो).
 *    Ser1UTCR3 	Serial port 1 Universal Asynchronous
 *              	Receiver/Transmitter (UART) Control Register 3
 *              	(पढ़ो/ग_लिखो).
 *    Ser1UTDR  	Serial port 1 Universal Asynchronous
 *              	Receiver/Transmitter (UART) Data Register
 *              	(पढ़ो/ग_लिखो).
 *    Ser1UTSR0 	Serial port 1 Universal Asynchronous
 *              	Receiver/Transmitter (UART) Status Register 0
 *              	(पढ़ो/ग_लिखो).
 *    Ser1UTSR1 	Serial port 1 Universal Asynchronous
 *              	Receiver/Transmitter (UART) Status Register 1 (पढ़ो).
 *
 *    Ser2UTCR0 	Serial port 2 Universal Asynchronous
 *              	Receiver/Transmitter (UART) Control Register 0
 *              	(पढ़ो/ग_लिखो).
 *    Ser2UTCR1 	Serial port 2 Universal Asynchronous
 *              	Receiver/Transmitter (UART) Control Register 1
 *              	(पढ़ो/ग_लिखो).
 *    Ser2UTCR2 	Serial port 2 Universal Asynchronous
 *              	Receiver/Transmitter (UART) Control Register 2
 *              	(पढ़ो/ग_लिखो).
 *    Ser2UTCR3 	Serial port 2 Universal Asynchronous
 *              	Receiver/Transmitter (UART) Control Register 3
 *              	(पढ़ो/ग_लिखो).
 *    Ser2UTCR4 	Serial port 2 Universal Asynchronous
 *              	Receiver/Transmitter (UART) Control Register 4
 *              	(पढ़ो/ग_लिखो).
 *    Ser2UTDR  	Serial port 2 Universal Asynchronous
 *              	Receiver/Transmitter (UART) Data Register
 *              	(पढ़ो/ग_लिखो).
 *    Ser2UTSR0 	Serial port 2 Universal Asynchronous
 *              	Receiver/Transmitter (UART) Status Register 0
 *              	(पढ़ो/ग_लिखो).
 *    Ser2UTSR1 	Serial port 2 Universal Asynchronous
 *              	Receiver/Transmitter (UART) Status Register 1 (पढ़ो).
 *
 *    Ser3UTCR0 	Serial port 3 Universal Asynchronous
 *              	Receiver/Transmitter (UART) Control Register 0
 *              	(पढ़ो/ग_लिखो).
 *    Ser3UTCR1 	Serial port 3 Universal Asynchronous
 *              	Receiver/Transmitter (UART) Control Register 1
 *              	(पढ़ो/ग_लिखो).
 *    Ser3UTCR2 	Serial port 3 Universal Asynchronous
 *              	Receiver/Transmitter (UART) Control Register 2
 *              	(पढ़ो/ग_लिखो).
 *    Ser3UTCR3 	Serial port 3 Universal Asynchronous
 *              	Receiver/Transmitter (UART) Control Register 3
 *              	(पढ़ो/ग_लिखो).
 *    Ser3UTDR  	Serial port 3 Universal Asynchronous
 *              	Receiver/Transmitter (UART) Data Register
 *              	(पढ़ो/ग_लिखो).
 *    Ser3UTSR0 	Serial port 3 Universal Asynchronous
 *              	Receiver/Transmitter (UART) Status Register 0
 *              	(पढ़ो/ग_लिखो).
 *    Ser3UTSR1 	Serial port 3 Universal Asynchronous
 *              	Receiver/Transmitter (UART) Status Register 1 (पढ़ो).
 *
 * Clocks
 *    fxtl, Txtl	Frequency, period of the प्रणाली crystal (3.6864 MHz
 *              	or 3.5795 MHz).
 *    fua, Tua  	Frequency, period of the UART communication.
 */

#घोषणा _UTCR0(Nb)	__REG(0x80010000 + ((Nb) - 1)*0x00020000)  /* UART Control Reg. 0 [1..3] */
#घोषणा _UTCR1(Nb)	__REG(0x80010004 + ((Nb) - 1)*0x00020000)  /* UART Control Reg. 1 [1..3] */
#घोषणा _UTCR2(Nb)	__REG(0x80010008 + ((Nb) - 1)*0x00020000)  /* UART Control Reg. 2 [1..3] */
#घोषणा _UTCR3(Nb)	__REG(0x8001000C + ((Nb) - 1)*0x00020000)  /* UART Control Reg. 3 [1..3] */
#घोषणा _UTCR4(Nb)	__REG(0x80010010 + ((Nb) - 1)*0x00020000)  /* UART Control Reg. 4 [2] */
#घोषणा _UTDR(Nb)	__REG(0x80010014 + ((Nb) - 1)*0x00020000)  /* UART Data Reg. [1..3] */
#घोषणा _UTSR0(Nb)	__REG(0x8001001C + ((Nb) - 1)*0x00020000)  /* UART Status Reg. 0 [1..3] */
#घोषणा _UTSR1(Nb)	__REG(0x80010020 + ((Nb) - 1)*0x00020000)  /* UART Status Reg. 1 [1..3] */

#घोषणा Ser1UTCR0	_UTCR0 (1)	/* Ser. port 1 UART Control Reg. 0 */
#घोषणा Ser1UTCR1	_UTCR1 (1)	/* Ser. port 1 UART Control Reg. 1 */
#घोषणा Ser1UTCR2	_UTCR2 (1)	/* Ser. port 1 UART Control Reg. 2 */
#घोषणा Ser1UTCR3	_UTCR3 (1)	/* Ser. port 1 UART Control Reg. 3 */
#घोषणा Ser1UTDR	_UTDR (1)	/* Ser. port 1 UART Data Reg.      */
#घोषणा Ser1UTSR0	_UTSR0 (1)	/* Ser. port 1 UART Status Reg. 0  */
#घोषणा Ser1UTSR1	_UTSR1 (1)	/* Ser. port 1 UART Status Reg. 1  */

#घोषणा Ser2UTCR0	_UTCR0 (2)	/* Ser. port 2 UART Control Reg. 0 */
#घोषणा Ser2UTCR1	_UTCR1 (2)	/* Ser. port 2 UART Control Reg. 1 */
#घोषणा Ser2UTCR2	_UTCR2 (2)	/* Ser. port 2 UART Control Reg. 2 */
#घोषणा Ser2UTCR3	_UTCR3 (2)	/* Ser. port 2 UART Control Reg. 3 */
#घोषणा Ser2UTCR4	_UTCR4 (2)	/* Ser. port 2 UART Control Reg. 4 */
#घोषणा Ser2UTDR	_UTDR (2)	/* Ser. port 2 UART Data Reg.      */
#घोषणा Ser2UTSR0	_UTSR0 (2)	/* Ser. port 2 UART Status Reg. 0  */
#घोषणा Ser2UTSR1	_UTSR1 (2)	/* Ser. port 2 UART Status Reg. 1  */

#घोषणा Ser3UTCR0	_UTCR0 (3)	/* Ser. port 3 UART Control Reg. 0 */
#घोषणा Ser3UTCR1	_UTCR1 (3)	/* Ser. port 3 UART Control Reg. 1 */
#घोषणा Ser3UTCR2	_UTCR2 (3)	/* Ser. port 3 UART Control Reg. 2 */
#घोषणा Ser3UTCR3	_UTCR3 (3)	/* Ser. port 3 UART Control Reg. 3 */
#घोषणा Ser3UTDR	_UTDR (3)	/* Ser. port 3 UART Data Reg.      */
#घोषणा Ser3UTSR0	_UTSR0 (3)	/* Ser. port 3 UART Status Reg. 0  */
#घोषणा Ser3UTSR1	_UTSR1 (3)	/* Ser. port 3 UART Status Reg. 1  */

/* Those are still used in some places */
#घोषणा _Ser1UTCR0	__PREG(Ser1UTCR0)
#घोषणा _Ser2UTCR0	__PREG(Ser2UTCR0)
#घोषणा _Ser3UTCR0	__PREG(Ser3UTCR0)

/* Register offsets */
#घोषणा UTCR0		0x00
#घोषणा UTCR1		0x04
#घोषणा UTCR2		0x08
#घोषणा UTCR3		0x0c
#घोषणा UTDR		0x14
#घोषणा UTSR0		0x1c
#घोषणा UTSR1		0x20

#घोषणा UTCR0_PE	0x00000001	/* Parity Enable                   */
#घोषणा UTCR0_OES	0x00000002	/* Odd/Even parity Select          */
#घोषणा UTCR0_OddPar	(UTCR0_OES*0)	/*  Odd Parity                     */
#घोषणा UTCR0_EvenPar	(UTCR0_OES*1)	/*  Even Parity                    */
#घोषणा UTCR0_SBS	0x00000004	/* Stop Bit Select                 */
#घोषणा UTCR0_1StpBit	(UTCR0_SBS*0)	/*  1 Stop Bit per frame           */
#घोषणा UTCR0_2StpBit	(UTCR0_SBS*1)	/*  2 Stop Bits per frame          */
#घोषणा UTCR0_DSS	0x00000008	/* Data Size Select                */
#घोषणा UTCR0_7BitData	(UTCR0_DSS*0)	/*  7-Bit Data                     */
#घोषणा UTCR0_8BitData	(UTCR0_DSS*1)	/*  8-Bit Data                     */
#घोषणा UTCR0_SCE	0x00000010	/* Sample Clock Enable             */
                	        	/* (ser. port 1: GPIO [18],        */
                	        	/* ser. port 3: GPIO [20])         */
#घोषणा UTCR0_RCE	0x00000020	/* Receive Clock Edge select       */
#घोषणा UTCR0_RcRsEdg	(UTCR0_RCE*0)	/*  Receive घड़ी Rising-Edge      */
#घोषणा UTCR0_RcFlEdg	(UTCR0_RCE*1)	/*  Receive घड़ी Falling-Edge     */
#घोषणा UTCR0_TCE	0x00000040	/* Transmit Clock Edge select      */
#घोषणा UTCR0_TrRsEdg	(UTCR0_TCE*0)	/*  Transmit घड़ी Rising-Edge     */
#घोषणा UTCR0_TrFlEdg	(UTCR0_TCE*1)	/*  Transmit घड़ी Falling-Edge    */
#घोषणा UTCR0_Ser2IrDA	        	/* Ser. port 2 IrDA settings       */ \
                	(UTCR0_1StpBit + UTCR0_8BitData)

#घोषणा UTCR1_BRD	Fld (4, 0)	/* Baud Rate Divisor/16 - 1 [11:8] */
#घोषणा UTCR2_BRD	Fld (8, 0)	/* Baud Rate Divisor/16 - 1  [7:0] */
                	        	/* fua = fxtl/(16*(BRD[11:0] + 1)) */
                	        	/* Tua = 16*(BRD [11:0] + 1)*Txtl  */
#घोषणा UTCR1_BdRtDiv(Div)      	/*  Baud Rate Divisor [16..65536]  */ \
                	(((Div) - 16)/16 >> FSize (UTCR2_BRD) << \
                	 FShft (UTCR1_BRD))
#घोषणा UTCR2_BdRtDiv(Div)      	/*  Baud Rate Divisor [16..65536]  */ \
                	(((Div) - 16)/16 & FAlnMsk (UTCR2_BRD) << \
                	 FShft (UTCR2_BRD))
                	        	/*  fua = fxtl/(16*Floor (Div/16)) */
                	        	/*  Tua = 16*Floor (Div/16)*Txtl   */
#घोषणा UTCR1_CeilBdRtDiv(Div)  	/*  Ceil. of BdRtDiv [16..65536]   */ \
                	(((Div) - 1)/16 >> FSize (UTCR2_BRD) << \
                	 FShft (UTCR1_BRD))
#घोषणा UTCR2_CeilBdRtDiv(Div)  	/*  Ceil. of BdRtDiv [16..65536]   */ \
                	(((Div) - 1)/16 & FAlnMsk (UTCR2_BRD) << \
                	 FShft (UTCR2_BRD))
                	        	/*  fua = fxtl/(16*Ceil (Div/16))  */
                	        	/*  Tua = 16*Ceil (Div/16)*Txtl    */

#घोषणा UTCR3_RXE	0x00000001	/* Receive Enable                  */
#घोषणा UTCR3_TXE	0x00000002	/* Transmit Enable                 */
#घोषणा UTCR3_BRK	0x00000004	/* BReaK mode                      */
#घोषणा UTCR3_RIE	0x00000008	/* Receive FIFO 1/3-to-2/3-full or */
                	        	/* more Interrupt Enable           */
#घोषणा UTCR3_TIE	0x00000010	/* Transmit FIFO 1/2-full or less  */
                	        	/* Interrupt Enable                */
#घोषणा UTCR3_LBM	0x00000020	/* Look-Back Mode                  */
#घोषणा UTCR3_Ser2IrDA	        	/* Ser. port 2 IrDA settings (RIE, */ \
                	        	/* TIE, LBM can be set or cleared) */ \
                	(UTCR3_RXE + UTCR3_TXE)

#घोषणा UTCR4_HSE	0x00000001	/* Hewlett-Packard Serial InfraRed */
                	        	/* (HP-SIR) modulation Enable      */
#घोषणा UTCR4_NRZ	(UTCR4_HSE*0)	/*  Non-Return to Zero modulation  */
#घोषणा UTCR4_HPSIR	(UTCR4_HSE*1)	/*  HP-SIR modulation              */
#घोषणा UTCR4_LPM	0x00000002	/* Low-Power Mode                  */
#घोषणा UTCR4_Z3_16Bit	(UTCR4_LPM*0)	/*  Zero pulse = 3/16 Bit समय     */
#घोषणा UTCR4_Z1_6us	(UTCR4_LPM*1)	/*  Zero pulse = 1.6 us            */

#घोषणा UTDR_DATA	Fld (8, 0)	/* receive/transmit DATA FIFOs     */
#अगर 0           	        	/* Hidden receive FIFO bits        */
#घोषणा UTDR_PRE	0x00000100	/*  receive PaRity Error (पढ़ो)    */
#घोषणा UTDR_FRE	0x00000200	/*  receive FRaming Error (पढ़ो)   */
#घोषणा UTDR_ROR	0x00000400	/*  Receive FIFO Over-Run (पढ़ो)   */
#पूर्ण_अगर /* 0 */

#घोषणा UTSR0_TFS	0x00000001	/* Transmit FIFO 1/2-full or less  */
                	        	/* Service request (पढ़ो)          */
#घोषणा UTSR0_RFS	0x00000002	/* Receive FIFO 1/3-to-2/3-full or */
                	        	/* more Service request (पढ़ो)     */
#घोषणा UTSR0_RID	0x00000004	/* Receiver IDle                   */
#घोषणा UTSR0_RBB	0x00000008	/* Receive Beginning of Break      */
#घोषणा UTSR0_REB	0x00000010	/* Receive End of Break            */
#घोषणा UTSR0_EIF	0x00000020	/* Error In FIFO (पढ़ो)            */

#घोषणा UTSR1_TBY	0x00000001	/* Transmitter BusY (पढ़ो)         */
#घोषणा UTSR1_RNE	0x00000002	/* Receive FIFO Not Empty (पढ़ो)   */
#घोषणा UTSR1_TNF	0x00000004	/* Transmit FIFO Not Full (पढ़ो)   */
#घोषणा UTSR1_PRE	0x00000008	/* receive PaRity Error (पढ़ो)     */
#घोषणा UTSR1_FRE	0x00000010	/* receive FRaming Error (पढ़ो)    */
#घोषणा UTSR1_ROR	0x00000020	/* Receive FIFO Over-Run (पढ़ो)    */


/*
 * Synchronous Data Link Controller (SDLC) control रेजिस्टरs
 *
 * Registers
 *    Ser1SDCR0 	Serial port 1 Synchronous Data Link Controller (SDLC)
 *              	Control Register 0 (पढ़ो/ग_लिखो).
 *    Ser1SDCR1 	Serial port 1 Synchronous Data Link Controller (SDLC)
 *              	Control Register 1 (पढ़ो/ग_लिखो).
 *    Ser1SDCR2 	Serial port 1 Synchronous Data Link Controller (SDLC)
 *              	Control Register 2 (पढ़ो/ग_लिखो).
 *    Ser1SDCR3 	Serial port 1 Synchronous Data Link Controller (SDLC)
 *              	Control Register 3 (पढ़ो/ग_लिखो).
 *    Ser1SDCR4 	Serial port 1 Synchronous Data Link Controller (SDLC)
 *              	Control Register 4 (पढ़ो/ग_लिखो).
 *    Ser1SDDR  	Serial port 1 Synchronous Data Link Controller (SDLC)
 *              	Data Register (पढ़ो/ग_लिखो).
 *    Ser1SDSR0 	Serial port 1 Synchronous Data Link Controller (SDLC)
 *              	Status Register 0 (पढ़ो/ग_लिखो).
 *    Ser1SDSR1 	Serial port 1 Synchronous Data Link Controller (SDLC)
 *              	Status Register 1 (पढ़ो/ग_लिखो).
 *
 * Clocks
 *    fxtl, Txtl	Frequency, period of the प्रणाली crystal (3.6864 MHz
 *              	or 3.5795 MHz).
 *    fsd, Tsd  	Frequency, period of the SDLC communication.
 */

#घोषणा Ser1SDCR0	__REG(0x80020060)  /* Ser. port 1 SDLC Control Reg. 0 */
#घोषणा Ser1SDCR1	__REG(0x80020064)  /* Ser. port 1 SDLC Control Reg. 1 */
#घोषणा Ser1SDCR2	__REG(0x80020068)  /* Ser. port 1 SDLC Control Reg. 2 */
#घोषणा Ser1SDCR3	__REG(0x8002006C)  /* Ser. port 1 SDLC Control Reg. 3 */
#घोषणा Ser1SDCR4	__REG(0x80020070)  /* Ser. port 1 SDLC Control Reg. 4 */
#घोषणा Ser1SDDR	__REG(0x80020078)  /* Ser. port 1 SDLC Data Reg.      */
#घोषणा Ser1SDSR0	__REG(0x80020080)  /* Ser. port 1 SDLC Status Reg. 0  */
#घोषणा Ser1SDSR1	__REG(0x80020084)  /* Ser. port 1 SDLC Status Reg. 1  */

#घोषणा SDCR0_SUS	0x00000001	/* SDLC/UART Select                */
#घोषणा SDCR0_SDLC	(SDCR0_SUS*0)	/*  SDLC mode (TXD1 & RXD1)        */
#घोषणा SDCR0_UART	(SDCR0_SUS*1)	/*  UART mode (TXD1 & RXD1)        */
#घोषणा SDCR0_SDF	0x00000002	/* Single/Double start Flag select */
#घोषणा SDCR0_SglFlg	(SDCR0_SDF*0)	/*  Single start Flag              */
#घोषणा SDCR0_DblFlg	(SDCR0_SDF*1)	/*  Double start Flag              */
#घोषणा SDCR0_LBM	0x00000004	/* Look-Back Mode                  */
#घोषणा SDCR0_BMS	0x00000008	/* Bit Modulation Select           */
#घोषणा SDCR0_FM0	(SDCR0_BMS*0)	/*  Freq. Modulation zero (0)      */
#घोषणा SDCR0_NRZ	(SDCR0_BMS*1)	/*  Non-Return to Zero modulation  */
#घोषणा SDCR0_SCE	0x00000010	/* Sample Clock Enable (GPIO [16]) */
#घोषणा SDCR0_SCD	0x00000020	/* Sample Clock Direction select   */
                	        	/* (GPIO [16])                     */
#घोषणा SDCR0_SClkIn	(SDCR0_SCD*0)	/*  Sample Clock Input             */
#घोषणा SDCR0_SClkOut	(SDCR0_SCD*1)	/*  Sample Clock Output            */
#घोषणा SDCR0_RCE	0x00000040	/* Receive Clock Edge select       */
#घोषणा SDCR0_RcRsEdg	(SDCR0_RCE*0)	/*  Receive घड़ी Rising-Edge      */
#घोषणा SDCR0_RcFlEdg	(SDCR0_RCE*1)	/*  Receive घड़ी Falling-Edge     */
#घोषणा SDCR0_TCE	0x00000080	/* Transmit Clock Edge select      */
#घोषणा SDCR0_TrRsEdg	(SDCR0_TCE*0)	/*  Transmit घड़ी Rising-Edge     */
#घोषणा SDCR0_TrFlEdg	(SDCR0_TCE*1)	/*  Transmit घड़ी Falling-Edge    */

#घोषणा SDCR1_AAF	0x00000001	/* Abort After Frame enable        */
                	        	/* (GPIO [17])                     */
#घोषणा SDCR1_TXE	0x00000002	/* Transmit Enable                 */
#घोषणा SDCR1_RXE	0x00000004	/* Receive Enable                  */
#घोषणा SDCR1_RIE	0x00000008	/* Receive FIFO 1/3-to-2/3-full or */
                	        	/* more Interrupt Enable           */
#घोषणा SDCR1_TIE	0x00000010	/* Transmit FIFO 1/2-full or less  */
                	        	/* Interrupt Enable                */
#घोषणा SDCR1_AME	0x00000020	/* Address Match Enable            */
#घोषणा SDCR1_TUS	0x00000040	/* Transmit FIFO Under-run Select  */
#घोषणा SDCR1_EFrmURn	(SDCR1_TUS*0)	/*  End Frame on Under-Run         */
#घोषणा SDCR1_AbortURn	(SDCR1_TUS*1)	/*  Abort on Under-Run             */
#घोषणा SDCR1_RAE	0x00000080	/* Receive Abort पूर्णांकerrupt Enable  */

#घोषणा SDCR2_AMV	Fld (8, 0)	/* Address Match Value             */

#घोषणा SDCR3_BRD	Fld (4, 0)	/* Baud Rate Divisor/16 - 1 [11:8] */
#घोषणा SDCR4_BRD	Fld (8, 0)	/* Baud Rate Divisor/16 - 1  [7:0] */
                	        	/* fsd = fxtl/(16*(BRD[11:0] + 1)) */
                	        	/* Tsd = 16*(BRD[11:0] + 1)*Txtl   */
#घोषणा SDCR3_BdRtDiv(Div)      	/*  Baud Rate Divisor [16..65536]  */ \
                	(((Div) - 16)/16 >> FSize (SDCR4_BRD) << \
                	 FShft (SDCR3_BRD))
#घोषणा SDCR4_BdRtDiv(Div)      	/*  Baud Rate Divisor [16..65536]  */ \
                	(((Div) - 16)/16 & FAlnMsk (SDCR4_BRD) << \
                	 FShft (SDCR4_BRD))
                	        	/*  fsd = fxtl/(16*Floor (Div/16)) */
                	        	/*  Tsd = 16*Floor (Div/16)*Txtl   */
#घोषणा SDCR3_CeilBdRtDiv(Div)  	/*  Ceil. of BdRtDiv [16..65536]   */ \
                	(((Div) - 1)/16 >> FSize (SDCR4_BRD) << \
                	 FShft (SDCR3_BRD))
#घोषणा SDCR4_CeilBdRtDiv(Div)  	/*  Ceil. of BdRtDiv [16..65536]   */ \
                	(((Div) - 1)/16 & FAlnMsk (SDCR4_BRD) << \
                	 FShft (SDCR4_BRD))
                	        	/*  fsd = fxtl/(16*Ceil (Div/16))  */
                	        	/*  Tsd = 16*Ceil (Div/16)*Txtl    */

#घोषणा SDDR_DATA	Fld (8, 0)	/* receive/transmit DATA FIFOs     */
#अगर 0           	        	/* Hidden receive FIFO bits        */
#घोषणा SDDR_खातापूर्ण	0x00000100	/*  receive End-Of-Frame (पढ़ो)    */
#घोषणा SDDR_CRE	0x00000200	/*  receive CRC Error (पढ़ो)       */
#घोषणा SDDR_ROR	0x00000400	/*  Receive FIFO Over-Run (पढ़ो)   */
#पूर्ण_अगर /* 0 */

#घोषणा SDSR0_EIF	0x00000001	/* Error In FIFO (पढ़ो)            */
#घोषणा SDSR0_TUR	0x00000002	/* Transmit FIFO Under-Run         */
#घोषणा SDSR0_RAB	0x00000004	/* Receive ABort                   */
#घोषणा SDSR0_TFS	0x00000008	/* Transmit FIFO 1/2-full or less  */
                	        	/* Service request (पढ़ो)          */
#घोषणा SDSR0_RFS	0x00000010	/* Receive FIFO 1/3-to-2/3-full or */
                	        	/* more Service request (पढ़ो)     */

#घोषणा SDSR1_RSY	0x00000001	/* Receiver SYnchronized (पढ़ो)    */
#घोषणा SDSR1_TBY	0x00000002	/* Transmitter BusY (पढ़ो)         */
#घोषणा SDSR1_RNE	0x00000004	/* Receive FIFO Not Empty (पढ़ो)   */
#घोषणा SDSR1_TNF	0x00000008	/* Transmit FIFO Not Full (पढ़ो)   */
#घोषणा SDSR1_RTD	0x00000010	/* Receive Transition Detected     */
#घोषणा SDSR1_खातापूर्ण	0x00000020	/* receive End-Of-Frame (पढ़ो)     */
#घोषणा SDSR1_CRE	0x00000040	/* receive CRC Error (पढ़ो)        */
#घोषणा SDSR1_ROR	0x00000080	/* Receive FIFO Over-Run (पढ़ो)    */


/*
 * High-Speed Serial to Parallel controller (HSSP) control रेजिस्टरs
 *
 * Registers
 *    Ser2HSCR0 	Serial port 2 High-Speed Serial to Parallel
 *              	controller (HSSP) Control Register 0 (पढ़ो/ग_लिखो).
 *    Ser2HSCR1 	Serial port 2 High-Speed Serial to Parallel
 *              	controller (HSSP) Control Register 1 (पढ़ो/ग_लिखो).
 *    Ser2HSDR  	Serial port 2 High-Speed Serial to Parallel
 *              	controller (HSSP) Data Register (पढ़ो/ग_लिखो).
 *    Ser2HSSR0 	Serial port 2 High-Speed Serial to Parallel
 *              	controller (HSSP) Status Register 0 (पढ़ो/ग_लिखो).
 *    Ser2HSSR1 	Serial port 2 High-Speed Serial to Parallel
 *              	controller (HSSP) Status Register 1 (पढ़ो).
 *    Ser2HSCR2 	Serial port 2 High-Speed Serial to Parallel
 *              	controller (HSSP) Control Register 2 (पढ़ो/ग_लिखो).
 *              	[The HSCR2 रेजिस्टर is only implemented in
 *              	versions 2.0 (rev. = 8) and higher of the StrongARM
 *              	SA-1100.]
 */

#घोषणा Ser2HSCR0	__REG(0x80040060)  /* Ser. port 2 HSSP Control Reg. 0 */
#घोषणा Ser2HSCR1	__REG(0x80040064)  /* Ser. port 2 HSSP Control Reg. 1 */
#घोषणा Ser2HSDR	__REG(0x8004006C)  /* Ser. port 2 HSSP Data Reg.      */
#घोषणा Ser2HSSR0	__REG(0x80040074)  /* Ser. port 2 HSSP Status Reg. 0  */
#घोषणा Ser2HSSR1	__REG(0x80040078)  /* Ser. port 2 HSSP Status Reg. 1  */
#घोषणा Ser2HSCR2	__REG(0x90060028)  /* Ser. port 2 HSSP Control Reg. 2 */

#घोषणा HSCR0_ITR	0x00000001	/* IrDA Transmission Rate          */
#घोषणा HSCR0_UART	(HSCR0_ITR*0)	/*  UART mode (115.2 kb/s अगर IrDA) */
#घोषणा HSCR0_HSSP	(HSCR0_ITR*1)	/*  HSSP mode (4 Mb/s)             */
#घोषणा HSCR0_LBM	0x00000002	/* Look-Back Mode                  */
#घोषणा HSCR0_TUS	0x00000004	/* Transmit FIFO Under-run Select  */
#घोषणा HSCR0_EFrmURn	(HSCR0_TUS*0)	/*  End Frame on Under-Run         */
#घोषणा HSCR0_AbortURn	(HSCR0_TUS*1)	/*  Abort on Under-Run             */
#घोषणा HSCR0_TXE	0x00000008	/* Transmit Enable                 */
#घोषणा HSCR0_RXE	0x00000010	/* Receive Enable                  */
#घोषणा HSCR0_RIE	0x00000020	/* Receive FIFO 2/5-to-3/5-full or */
                	        	/* more Interrupt Enable           */
#घोषणा HSCR0_TIE	0x00000040	/* Transmit FIFO 1/2-full or less  */
                	        	/* Interrupt Enable                */
#घोषणा HSCR0_AME	0x00000080	/* Address Match Enable            */

#घोषणा HSCR1_AMV	Fld (8, 0)	/* Address Match Value             */

#घोषणा HSDR_DATA	Fld (8, 0)	/* receive/transmit DATA FIFOs     */
#अगर 0           	        	/* Hidden receive FIFO bits        */
#घोषणा HSDR_खातापूर्ण	0x00000100	/*  receive End-Of-Frame (पढ़ो)    */
#घोषणा HSDR_CRE	0x00000200	/*  receive CRC Error (पढ़ो)       */
#घोषणा HSDR_ROR	0x00000400	/*  Receive FIFO Over-Run (पढ़ो)   */
#पूर्ण_अगर /* 0 */

#घोषणा HSSR0_EIF	0x00000001	/* Error In FIFO (पढ़ो)            */
#घोषणा HSSR0_TUR	0x00000002	/* Transmit FIFO Under-Run         */
#घोषणा HSSR0_RAB	0x00000004	/* Receive ABort                   */
#घोषणा HSSR0_TFS	0x00000008	/* Transmit FIFO 1/2-full or less  */
                	        	/* Service request (पढ़ो)          */
#घोषणा HSSR0_RFS	0x00000010	/* Receive FIFO 2/5-to-3/5-full or */
                	        	/* more Service request (पढ़ो)     */
#घोषणा HSSR0_FRE	0x00000020	/* receive FRaming Error           */

#घोषणा HSSR1_RSY	0x00000001	/* Receiver SYnchronized (पढ़ो)    */
#घोषणा HSSR1_TBY	0x00000002	/* Transmitter BusY (पढ़ो)         */
#घोषणा HSSR1_RNE	0x00000004	/* Receive FIFO Not Empty (पढ़ो)   */
#घोषणा HSSR1_TNF	0x00000008	/* Transmit FIFO Not Full (पढ़ो)   */
#घोषणा HSSR1_खातापूर्ण	0x00000010	/* receive End-Of-Frame (पढ़ो)     */
#घोषणा HSSR1_CRE	0x00000020	/* receive CRC Error (पढ़ो)        */
#घोषणा HSSR1_ROR	0x00000040	/* Receive FIFO Over-Run (पढ़ो)    */

#घोषणा HSCR2_TXP	0x00040000	/* Transmit data Polarity (TXD_2)  */
#घोषणा HSCR2_TrDataL	(HSCR2_TXP*0)	/*  Transmit Data active Low       */
                	        	/*  (inverted)                     */
#घोषणा HSCR2_TrDataH	(HSCR2_TXP*1)	/*  Transmit Data active High      */
                	        	/*  (non-inverted)                 */
#घोषणा HSCR2_RXP	0x00080000	/* Receive data Polarity (RXD_2)   */
#घोषणा HSCR2_RcDataL	(HSCR2_RXP*0)	/*  Receive Data active Low        */
                	        	/*  (inverted)                     */
#घोषणा HSCR2_RcDataH	(HSCR2_RXP*1)	/*  Receive Data active High       */
                	        	/*  (non-inverted)                 */


/*
 * Multi-media Communications Port (MCP) control रेजिस्टरs
 *
 * Registers
 *    Ser4MCCR0 	Serial port 4 Multi-media Communications Port (MCP)
 *              	Control Register 0 (पढ़ो/ग_लिखो).
 *    Ser4MCDR0 	Serial port 4 Multi-media Communications Port (MCP)
 *              	Data Register 0 (audio, पढ़ो/ग_लिखो).
 *    Ser4MCDR1 	Serial port 4 Multi-media Communications Port (MCP)
 *              	Data Register 1 (telecom, पढ़ो/ग_लिखो).
 *    Ser4MCDR2 	Serial port 4 Multi-media Communications Port (MCP)
 *              	Data Register 2 (CODEC रेजिस्टरs, पढ़ो/ग_लिखो).
 *    Ser4MCSR  	Serial port 4 Multi-media Communications Port (MCP)
 *              	Status Register (पढ़ो/ग_लिखो).
 *    Ser4MCCR1 	Serial port 4 Multi-media Communications Port (MCP)
 *              	Control Register 1 (पढ़ो/ग_लिखो).
 *              	[The MCCR1 रेजिस्टर is only implemented in
 *              	versions 2.0 (rev. = 8) and higher of the StrongARM
 *              	SA-1100.]
 *
 * Clocks
 *    fmc, Tmc  	Frequency, period of the MCP communication (10 MHz,
 *              	12 MHz, or GPIO [21]).
 *    faud, Taud	Frequency, period of the audio sampling.
 *    ftcm, Ttcm	Frequency, period of the telecom sampling.
 */

#घोषणा Ser4MCCR0	__REG(0x80060000)  /* Ser. port 4 MCP Control Reg. 0 */
#घोषणा Ser4MCDR0	__REG(0x80060008)  /* Ser. port 4 MCP Data Reg. 0 (audio) */
#घोषणा Ser4MCDR1	__REG(0x8006000C)  /* Ser. port 4 MCP Data Reg. 1 (telecom) */
#घोषणा Ser4MCDR2	__REG(0x80060010)  /* Ser. port 4 MCP Data Reg. 2 (CODEC reg.) */
#घोषणा Ser4MCSR	__REG(0x80060018)  /* Ser. port 4 MCP Status Reg. */
#घोषणा Ser4MCCR1	__REG(0x90060030)  /* Ser. port 4 MCP Control Reg. 1 */

#घोषणा MCCR0_ASD	Fld (7, 0)	/* Audio Sampling rate Divisor/32  */
                	        	/* [6..127]                        */
                	        	/* faud = fmc/(32*ASD)             */
                	        	/* Taud = 32*ASD*Tmc               */
#घोषणा MCCR0_AudSmpDiv(Div)    	/*  Audio Sampling rate Divisor    */ \
                	        	/*  [192..4064]                    */ \
                	((Div)/32 << FShft (MCCR0_ASD))
                	        	/*  faud = fmc/(32*Floor (Div/32)) */
                	        	/*  Taud = 32*Floor (Div/32)*Tmc   */
#घोषणा MCCR0_CeilAudSmpDiv(Div)	/*  Ceil. of AudSmpDiv [192..4064] */ \
                	(((Div) + 31)/32 << FShft (MCCR0_ASD))
                	        	/*  faud = fmc/(32*Ceil (Div/32))  */
                	        	/*  Taud = 32*Ceil (Div/32)*Tmc    */
#घोषणा MCCR0_TSD	Fld (7, 8)	/* Telecom Sampling rate           */
                	        	/* Divisor/32 [16..127]            */
                	        	/* ftcm = fmc/(32*TSD)             */
                	        	/* Ttcm = 32*TSD*Tmc               */
#घोषणा MCCR0_TcmSmpDiv(Div)    	/*  Telecom Sampling rate Divisor  */ \
                	        	/*  [512..4064]                    */ \
                	((Div)/32 << FShft (MCCR0_TSD))
                	        	/*  ftcm = fmc/(32*Floor (Div/32)) */
                	        	/*  Ttcm = 32*Floor (Div/32)*Tmc   */
#घोषणा MCCR0_CeilTcmSmpDiv(Div)	/*  Ceil. of TcmSmpDiv [512..4064] */ \
                	(((Div) + 31)/32 << FShft (MCCR0_TSD))
                	        	/*  ftcm = fmc/(32*Ceil (Div/32))  */
                	        	/*  Ttcm = 32*Ceil (Div/32)*Tmc    */
#घोषणा MCCR0_MCE	0x00010000	/* MCP Enable                      */
#घोषणा MCCR0_ECS	0x00020000	/* External Clock Select           */
#घोषणा MCCR0_IntClk	(MCCR0_ECS*0)	/*  Internal Clock (10 or 12 MHz)  */
#घोषणा MCCR0_ExtClk	(MCCR0_ECS*1)	/*  External Clock (GPIO [21])     */
#घोषणा MCCR0_ADM	0x00040000	/* A/D (audio/telecom) data        */
                	        	/* sampling/storing Mode           */
#घोषणा MCCR0_VldBit	(MCCR0_ADM*0)	/*  Valid Bit storing mode         */
#घोषणा MCCR0_SmpCnt	(MCCR0_ADM*1)	/*  Sampling Counter storing mode  */
#घोषणा MCCR0_TTE	0x00080000	/* Telecom Transmit FIFO 1/2-full  */
                	        	/* or less पूर्णांकerrupt Enable        */
#घोषणा MCCR0_TRE	0x00100000	/* Telecom Receive FIFO 1/2-full   */
                	        	/* or more पूर्णांकerrupt Enable        */
#घोषणा MCCR0_ATE	0x00200000	/* Audio Transmit FIFO 1/2-full    */
                	        	/* or less पूर्णांकerrupt Enable        */
#घोषणा MCCR0_ARE	0x00400000	/* Audio Receive FIFO 1/2-full or  */
                	        	/* more पूर्णांकerrupt Enable           */
#घोषणा MCCR0_LBM	0x00800000	/* Look-Back Mode                  */
#घोषणा MCCR0_ECP	Fld (2, 24)	/* External Clock Prescaler - 1    */
#घोषणा MCCR0_ExtClkDiv(Div)    	/*  External Clock Divisor [1..4]  */ \
                	(((Div) - 1) << FShft (MCCR0_ECP))

#घोषणा MCDR0_DATA	Fld (12, 4)	/* receive/transmit audio DATA     */
                	        	/* FIFOs                           */

#घोषणा MCDR1_DATA	Fld (14, 2)	/* receive/transmit telecom DATA   */
                	        	/* FIFOs                           */

                	        	/* receive/transmit CODEC reg.     */
                	        	/* FIFOs:                          */
#घोषणा MCDR2_DATA	Fld (16, 0)	/*  reg. DATA                      */
#घोषणा MCDR2_RW	0x00010000	/*  reg. Read/Write (transmit)     */
#घोषणा MCDR2_Rd	(MCDR2_RW*0)	/*   reg. Read                     */
#घोषणा MCDR2_Wr	(MCDR2_RW*1)	/*   reg. Write                    */
#घोषणा MCDR2_ADD	Fld (4, 17)	/*  reg. ADDress                   */

#घोषणा MCSR_ATS	0x00000001	/* Audio Transmit FIFO 1/2-full    */
                	        	/* or less Service request (पढ़ो)  */
#घोषणा MCSR_ARS	0x00000002	/* Audio Receive FIFO 1/2-full or  */
                	        	/* more Service request (पढ़ो)     */
#घोषणा MCSR_TTS	0x00000004	/* Telecom Transmit FIFO 1/2-full  */
                	        	/* or less Service request (पढ़ो)  */
#घोषणा MCSR_TRS	0x00000008	/* Telecom Receive FIFO 1/2-full   */
                	        	/* or more Service request (पढ़ो)  */
#घोषणा MCSR_ATU	0x00000010	/* Audio Transmit FIFO Under-run   */
#घोषणा MCSR_ARO	0x00000020	/* Audio Receive FIFO Over-run     */
#घोषणा MCSR_TTU	0x00000040	/* Telecom Transmit FIFO Under-run */
#घोषणा MCSR_TRO	0x00000080	/* Telecom Receive FIFO Over-run   */
#घोषणा MCSR_ANF	0x00000100	/* Audio transmit FIFO Not Full    */
                	        	/* (पढ़ो)                          */
#घोषणा MCSR_ANE	0x00000200	/* Audio receive FIFO Not Empty    */
                	        	/* (पढ़ो)                          */
#घोषणा MCSR_TNF	0x00000400	/* Telecom transmit FIFO Not Full  */
                	        	/* (पढ़ो)                          */
#घोषणा MCSR_TNE	0x00000800	/* Telecom receive FIFO Not Empty  */
                	        	/* (पढ़ो)                          */
#घोषणा MCSR_CWC	0x00001000	/* CODEC रेजिस्टर Write Completed  */
                	        	/* (पढ़ो)                          */
#घोषणा MCSR_CRC	0x00002000	/* CODEC रेजिस्टर Read Completed   */
                	        	/* (पढ़ो)                          */
#घोषणा MCSR_ACE	0x00004000	/* Audio CODEC Enabled (पढ़ो)      */
#घोषणा MCSR_TCE	0x00008000	/* Telecom CODEC Enabled (पढ़ो)    */

#घोषणा MCCR1_CFS	0x00100000	/* Clock Freq. Select              */
#घोषणा MCCR1_F12MHz	(MCCR1_CFS*0)	/*  Freq. (fmc) = ~ 12 MHz         */
                	        	/*  (11.981 MHz)                   */
#घोषणा MCCR1_F10MHz	(MCCR1_CFS*1)	/*  Freq. (fmc) = ~ 10 MHz         */
                	        	/*  (9.585 MHz)                    */


/*
 * Synchronous Serial Port (SSP) control रेजिस्टरs
 *
 * Registers
 *    Ser4SSCR0 	Serial port 4 Synchronous Serial Port (SSP) Control
 *              	Register 0 (पढ़ो/ग_लिखो).
 *    Ser4SSCR1 	Serial port 4 Synchronous Serial Port (SSP) Control
 *              	Register 1 (पढ़ो/ग_लिखो).
 *              	[Bits SPO and SP are only implemented in versions 2.0
 *              	(rev. = 8) and higher of the StrongARM SA-1100.]
 *    Ser4SSDR  	Serial port 4 Synchronous Serial Port (SSP) Data
 *              	Register (पढ़ो/ग_लिखो).
 *    Ser4SSSR  	Serial port 4 Synchronous Serial Port (SSP) Status
 *              	Register (पढ़ो/ग_लिखो).
 *
 * Clocks
 *    fxtl, Txtl	Frequency, period of the प्रणाली crystal (3.6864 MHz
 *              	or 3.5795 MHz).
 *    fss, Tss  	Frequency, period of the SSP communication.
 */

#घोषणा Ser4SSCR0	__REG(0x80070060)  /* Ser. port 4 SSP Control Reg. 0 */
#घोषणा Ser4SSCR1	__REG(0x80070064)  /* Ser. port 4 SSP Control Reg. 1 */
#घोषणा Ser4SSDR	__REG(0x8007006C)  /* Ser. port 4 SSP Data Reg. */
#घोषणा Ser4SSSR	__REG(0x80070074)  /* Ser. port 4 SSP Status Reg. */

#घोषणा SSCR0_DSS	Fld (4, 0)	/* Data Size - 1 Select [3..15]    */
#घोषणा SSCR0_DataSize(Size)    	/*  Data Size Select [4..16]       */ \
                	(((Size) - 1) << FShft (SSCR0_DSS))
#घोषणा SSCR0_FRF	Fld (2, 4)	/* FRame Format                    */
#घोषणा SSCR0_Motorola	        	/*  Motorola Serial Peripheral     */ \
                	        	/*  Interface (SPI) क्रमmat         */ \
                	(0 << FShft (SSCR0_FRF))
#घोषणा SSCR0_TI	        	/*  Texas Instruments Synchronous  */ \
                	        	/*  Serial क्रमmat                  */ \
                	(1 << FShft (SSCR0_FRF))
#घोषणा SSCR0_National	        	/*  National Microwire क्रमmat      */ \
                	(2 << FShft (SSCR0_FRF))
#घोषणा SSCR0_SSE	0x00000080	/* SSP Enable                      */
#घोषणा SSCR0_SCR	Fld (8, 8)	/* Serial Clock Rate भागisor/2 - 1 */
                	        	/* fss = fxtl/(2*(SCR + 1))        */
                	        	/* Tss = 2*(SCR + 1)*Txtl          */
#घोषणा SSCR0_SerClkDiv(Div)    	/*  Serial Clock Divisor [2..512]  */ \
                	(((Div) - 2)/2 << FShft (SSCR0_SCR))
                	        	/*  fss = fxtl/(2*Floor (Div/2))   */
                	        	/*  Tss = 2*Floor (Div/2)*Txtl     */
#घोषणा SSCR0_CeilSerClkDiv(Div)	/*  Ceil. of SerClkDiv [2..512]    */ \
                	(((Div) - 1)/2 << FShft (SSCR0_SCR))
                	        	/*  fss = fxtl/(2*Ceil (Div/2))    */
                	        	/*  Tss = 2*Ceil (Div/2)*Txtl      */

#घोषणा SSCR1_RIE	0x00000001	/* Receive FIFO 1/2-full or more   */
                	        	/* Interrupt Enable                */
#घोषणा SSCR1_TIE	0x00000002	/* Transmit FIFO 1/2-full or less  */
                	        	/* Interrupt Enable                */
#घोषणा SSCR1_LBM	0x00000004	/* Look-Back Mode                  */
#घोषणा SSCR1_SPO	0x00000008	/* Sample घड़ी (SCLK) POlarity    */
#घोषणा SSCR1_SClkIactL	(SSCR1_SPO*0)	/*  Sample Clock Inactive Low      */
#घोषणा SSCR1_SClkIactH	(SSCR1_SPO*1)	/*  Sample Clock Inactive High     */
#घोषणा SSCR1_SP	0x00000010	/* Sample घड़ी (SCLK) Phase       */
#घोषणा SSCR1_SClk1P	(SSCR1_SP*0)	/*  Sample Clock active 1 Period   */
                	        	/*  after frame (SFRM, 1st edge)   */
#घोषणा SSCR1_SClk1_2P	(SSCR1_SP*1)	/*  Sample Clock active 1/2 Period */
                	        	/*  after frame (SFRM, 1st edge)   */
#घोषणा SSCR1_ECS	0x00000020	/* External Clock Select           */
#घोषणा SSCR1_IntClk	(SSCR1_ECS*0)	/*  Internal Clock                 */
#घोषणा SSCR1_ExtClk	(SSCR1_ECS*1)	/*  External Clock (GPIO [19])     */

#घोषणा SSDR_DATA	Fld (16, 0)	/* receive/transmit DATA FIFOs     */

#घोषणा SSSR_TNF	0x00000002	/* Transmit FIFO Not Full (पढ़ो)   */
#घोषणा SSSR_RNE	0x00000004	/* Receive FIFO Not Empty (पढ़ो)   */
#घोषणा SSSR_BSY	0x00000008	/* SSP BuSY (पढ़ो)                 */
#घोषणा SSSR_TFS	0x00000010	/* Transmit FIFO 1/2-full or less  */
                	        	/* Service request (पढ़ो)          */
#घोषणा SSSR_RFS	0x00000020	/* Receive FIFO 1/2-full or more   */
                	        	/* Service request (पढ़ो)          */
#घोषणा SSSR_ROR	0x00000040	/* Receive FIFO Over-Run           */


/*
 * Operating System (OS) समयr control रेजिस्टरs
 *
 * Registers
 *    OSMR0     	Operating System (OS) समयr Match Register 0
 *              	(पढ़ो/ग_लिखो).
 *    OSMR1     	Operating System (OS) समयr Match Register 1
 *              	(पढ़ो/ग_लिखो).
 *    OSMR2     	Operating System (OS) समयr Match Register 2
 *              	(पढ़ो/ग_लिखो).
 *    OSMR3     	Operating System (OS) समयr Match Register 3
 *              	(पढ़ो/ग_लिखो).
 *    OSCR      	Operating System (OS) समयr Counter Register
 *              	(पढ़ो/ग_लिखो).
 *    OSSR      	Operating System (OS) समयr Status Register
 *              	(पढ़ो/ग_लिखो).
 *    OWER      	Operating System (OS) समयr Watch-करोg Enable Register
 *              	(पढ़ो/ग_लिखो).
 *    OIER      	Operating System (OS) समयr Interrupt Enable Register
 *              	(पढ़ो/ग_लिखो).
 */

#घोषणा OSMR0  		io_p2v(0x90000000)  /* OS समयr Match Reg. 0 */
#घोषणा OSMR1  		io_p2v(0x90000004)  /* OS समयr Match Reg. 1 */
#घोषणा OSMR2  		io_p2v(0x90000008)  /* OS समयr Match Reg. 2 */
#घोषणा OSMR3  		io_p2v(0x9000000c)  /* OS समयr Match Reg. 3 */
#घोषणा OSCR   		io_p2v(0x90000010)  /* OS समयr Counter Reg. */
#घोषणा OSSR   		io_p2v(0x90000014)  /* OS समयr Status Reg. */
#घोषणा OWER   		io_p2v(0x90000018)  /* OS समयr Watch-करोg Enable Reg. */
#घोषणा OIER  	 	io_p2v(0x9000001C)  /* OS समयr Interrupt Enable Reg. */

#घोषणा OSSR_M(Nb)	        	/* Match detected [0..3]           */ \
                	(0x00000001 << (Nb))
#घोषणा OSSR_M0 	OSSR_M (0)	/* Match detected 0                */
#घोषणा OSSR_M1 	OSSR_M (1)	/* Match detected 1                */
#घोषणा OSSR_M2 	OSSR_M (2)	/* Match detected 2                */
#घोषणा OSSR_M3 	OSSR_M (3)	/* Match detected 3                */

#घोषणा OWER_WME	0x00000001	/* Watch-करोg Match Enable          */
                	        	/* (set only)                      */

#घोषणा OIER_E(Nb)	        	/* match पूर्णांकerrupt Enable [0..3]   */ \
                	(0x00000001 << (Nb))
#घोषणा OIER_E0 	OIER_E (0)	/* match पूर्णांकerrupt Enable 0        */
#घोषणा OIER_E1 	OIER_E (1)	/* match पूर्णांकerrupt Enable 1        */
#घोषणा OIER_E2 	OIER_E (2)	/* match पूर्णांकerrupt Enable 2        */
#घोषणा OIER_E3 	OIER_E (3)	/* match पूर्णांकerrupt Enable 3        */


/*
 * Power Manager (PM) control रेजिस्टरs
 *
 * Registers
 *    PMCR      	Power Manager (PM) Control Register (पढ़ो/ग_लिखो).
 *    PSSR      	Power Manager (PM) Sleep Status Register (पढ़ो/ग_लिखो).
 *    PSPR      	Power Manager (PM) Scratch-Pad Register (पढ़ो/ग_लिखो).
 *    PWER      	Power Manager (PM) Wake-up Enable Register
 *              	(पढ़ो/ग_लिखो).
 *    PCFR      	Power Manager (PM) general ConFiguration Register
 *              	(पढ़ो/ग_लिखो).
 *    PPCR      	Power Manager (PM) Phase-Locked Loop (PLL)
 *              	Configuration Register (पढ़ो/ग_लिखो).
 *    PGSR      	Power Manager (PM) General-Purpose Input/Output (GPIO)
 *              	Sleep state Register (पढ़ो/ग_लिखो, see GPIO pins).
 *    POSR      	Power Manager (PM) Oscillator Status Register (पढ़ो).
 *
 * Clocks
 *    fxtl, Txtl	Frequency, period of the प्रणाली crystal (3.6864 MHz
 *              	or 3.5795 MHz).
 *    fcpu, Tcpu	Frequency, period of the CPU core घड़ी (CCLK).
 */

#घोषणा PMCR		__REG(0x90020000)  /* PM Control Reg. */
#घोषणा PSSR		__REG(0x90020004)  /* PM Sleep Status Reg. */
#घोषणा PSPR		__REG(0x90020008)  /* PM Scratch-Pad Reg. */
#घोषणा PWER		__REG(0x9002000C)  /* PM Wake-up Enable Reg. */
#घोषणा PCFR		__REG(0x90020010)  /* PM general ConFiguration Reg. */
#घोषणा PPCR		__REG(0x90020014)  /* PM PLL Configuration Reg. */
#घोषणा PGSR		__REG(0x90020018)  /* PM GPIO Sleep state Reg. */
#घोषणा POSR		__REG(0x9002001C)  /* PM Oscillator Status Reg. */

#घोषणा PMCR_SF 	0x00000001	/* Sleep Force (set only)          */

#घोषणा PSSR_SS 	0x00000001	/* Software Sleep                  */
#घोषणा PSSR_BFS	0x00000002	/* Battery Fault Status            */
                	        	/* (BATT_FAULT)                    */
#घोषणा PSSR_VFS	0x00000004	/* Vdd Fault Status (VDD_FAULT)    */
#घोषणा PSSR_DH 	0x00000008	/* DRAM control Hold               */
#घोषणा PSSR_PH 	0x00000010	/* Peripheral control Hold         */

#घोषणा PWER_GPIO(Nb)	GPIO_GPIO (Nb)	/* GPIO [0..27] wake-up enable     */
#घोषणा PWER_GPIO0	PWER_GPIO (0)	/* GPIO  [0] wake-up enable        */
#घोषणा PWER_GPIO1	PWER_GPIO (1)	/* GPIO  [1] wake-up enable        */
#घोषणा PWER_GPIO2	PWER_GPIO (2)	/* GPIO  [2] wake-up enable        */
#घोषणा PWER_GPIO3	PWER_GPIO (3)	/* GPIO  [3] wake-up enable        */
#घोषणा PWER_GPIO4	PWER_GPIO (4)	/* GPIO  [4] wake-up enable        */
#घोषणा PWER_GPIO5	PWER_GPIO (5)	/* GPIO  [5] wake-up enable        */
#घोषणा PWER_GPIO6	PWER_GPIO (6)	/* GPIO  [6] wake-up enable        */
#घोषणा PWER_GPIO7	PWER_GPIO (7)	/* GPIO  [7] wake-up enable        */
#घोषणा PWER_GPIO8	PWER_GPIO (8)	/* GPIO  [8] wake-up enable        */
#घोषणा PWER_GPIO9	PWER_GPIO (9)	/* GPIO  [9] wake-up enable        */
#घोषणा PWER_GPIO10	PWER_GPIO (10)	/* GPIO [10] wake-up enable        */
#घोषणा PWER_GPIO11	PWER_GPIO (11)	/* GPIO [11] wake-up enable        */
#घोषणा PWER_GPIO12	PWER_GPIO (12)	/* GPIO [12] wake-up enable        */
#घोषणा PWER_GPIO13	PWER_GPIO (13)	/* GPIO [13] wake-up enable        */
#घोषणा PWER_GPIO14	PWER_GPIO (14)	/* GPIO [14] wake-up enable        */
#घोषणा PWER_GPIO15	PWER_GPIO (15)	/* GPIO [15] wake-up enable        */
#घोषणा PWER_GPIO16	PWER_GPIO (16)	/* GPIO [16] wake-up enable        */
#घोषणा PWER_GPIO17	PWER_GPIO (17)	/* GPIO [17] wake-up enable        */
#घोषणा PWER_GPIO18	PWER_GPIO (18)	/* GPIO [18] wake-up enable        */
#घोषणा PWER_GPIO19	PWER_GPIO (19)	/* GPIO [19] wake-up enable        */
#घोषणा PWER_GPIO20	PWER_GPIO (20)	/* GPIO [20] wake-up enable        */
#घोषणा PWER_GPIO21	PWER_GPIO (21)	/* GPIO [21] wake-up enable        */
#घोषणा PWER_GPIO22	PWER_GPIO (22)	/* GPIO [22] wake-up enable        */
#घोषणा PWER_GPIO23	PWER_GPIO (23)	/* GPIO [23] wake-up enable        */
#घोषणा PWER_GPIO24	PWER_GPIO (24)	/* GPIO [24] wake-up enable        */
#घोषणा PWER_GPIO25	PWER_GPIO (25)	/* GPIO [25] wake-up enable        */
#घोषणा PWER_GPIO26	PWER_GPIO (26)	/* GPIO [26] wake-up enable        */
#घोषणा PWER_GPIO27	PWER_GPIO (27)	/* GPIO [27] wake-up enable        */
#घोषणा PWER_RTC	0x80000000	/* RTC alarm wake-up enable        */

#घोषणा PCFR_OPDE	0x00000001	/* Oscillator Power-Down Enable    */
#घोषणा PCFR_ClkRun	(PCFR_OPDE*0)	/*  Clock Running in sleep mode    */
#घोषणा PCFR_ClkStp	(PCFR_OPDE*1)	/*  Clock Stopped in sleep mode    */
#घोषणा PCFR_FP 	0x00000002	/* Float PCMCIA pins               */
#घोषणा PCFR_PCMCIANeg	(PCFR_FP*0)	/*  PCMCIA pins Negated (1)        */
#घोषणा PCFR_PCMCIAFlt	(PCFR_FP*1)	/*  PCMCIA pins Floating           */
#घोषणा PCFR_FS 	0x00000004	/* Float Static memory pins        */
#घोषणा PCFR_StMemNeg	(PCFR_FS*0)	/*  Static Memory pins Negated (1) */
#घोषणा PCFR_StMemFlt	(PCFR_FS*1)	/*  Static Memory pins Floating    */
#घोषणा PCFR_FO 	0x00000008	/* Force RTC oscillator            */
                	        	/* (32.768 kHz) enable On          */

#घोषणा PPCR_CCF	Fld (5, 0)	/* CPU core Clock (CCLK) Freq.     */
#घोषणा PPCR_Fx16	        	/*  Freq. x 16 (fcpu = 16*fxtl)    */ \
                	(0x00 << FShft (PPCR_CCF))
#घोषणा PPCR_Fx20	        	/*  Freq. x 20 (fcpu = 20*fxtl)    */ \
                	(0x01 << FShft (PPCR_CCF))
#घोषणा PPCR_Fx24	        	/*  Freq. x 24 (fcpu = 24*fxtl)    */ \
                	(0x02 << FShft (PPCR_CCF))
#घोषणा PPCR_Fx28	        	/*  Freq. x 28 (fcpu = 28*fxtl)    */ \
                	(0x03 << FShft (PPCR_CCF))
#घोषणा PPCR_Fx32	        	/*  Freq. x 32 (fcpu = 32*fxtl)    */ \
                	(0x04 << FShft (PPCR_CCF))
#घोषणा PPCR_Fx36	        	/*  Freq. x 36 (fcpu = 36*fxtl)    */ \
                	(0x05 << FShft (PPCR_CCF))
#घोषणा PPCR_Fx40	        	/*  Freq. x 40 (fcpu = 40*fxtl)    */ \
                	(0x06 << FShft (PPCR_CCF))
#घोषणा PPCR_Fx44	        	/*  Freq. x 44 (fcpu = 44*fxtl)    */ \
                	(0x07 << FShft (PPCR_CCF))
#घोषणा PPCR_Fx48	        	/*  Freq. x 48 (fcpu = 48*fxtl)    */ \
                	(0x08 << FShft (PPCR_CCF))
#घोषणा PPCR_Fx52	        	/*  Freq. x 52 (fcpu = 52*fxtl)    */ \
                	(0x09 << FShft (PPCR_CCF))
#घोषणा PPCR_Fx56	        	/*  Freq. x 56 (fcpu = 56*fxtl)    */ \
                	(0x0A << FShft (PPCR_CCF))
#घोषणा PPCR_Fx60	        	/*  Freq. x 60 (fcpu = 60*fxtl)    */ \
                	(0x0B << FShft (PPCR_CCF))
#घोषणा PPCR_Fx64	        	/*  Freq. x 64 (fcpu = 64*fxtl)    */ \
                	(0x0C << FShft (PPCR_CCF))
#घोषणा PPCR_Fx68	        	/*  Freq. x 68 (fcpu = 68*fxtl)    */ \
                	(0x0D << FShft (PPCR_CCF))
#घोषणा PPCR_Fx72	        	/*  Freq. x 72 (fcpu = 72*fxtl)    */ \
                	(0x0E << FShft (PPCR_CCF))
#घोषणा PPCR_Fx76	        	/*  Freq. x 76 (fcpu = 76*fxtl)    */ \
                	(0x0F << FShft (PPCR_CCF))
                	        	/*  3.6864 MHz crystal (fxtl):     */
#घोषणा PPCR_F59_0MHz	PPCR_Fx16	/*   Freq. (fcpu) =  59.0 MHz      */
#घोषणा PPCR_F73_7MHz	PPCR_Fx20	/*   Freq. (fcpu) =  73.7 MHz      */
#घोषणा PPCR_F88_5MHz	PPCR_Fx24	/*   Freq. (fcpu) =  88.5 MHz      */
#घोषणा PPCR_F103_2MHz	PPCR_Fx28	/*   Freq. (fcpu) = 103.2 MHz      */
#घोषणा PPCR_F118_0MHz	PPCR_Fx32	/*   Freq. (fcpu) = 118.0 MHz      */
#घोषणा PPCR_F132_7MHz	PPCR_Fx36	/*   Freq. (fcpu) = 132.7 MHz      */
#घोषणा PPCR_F147_5MHz	PPCR_Fx40	/*   Freq. (fcpu) = 147.5 MHz      */
#घोषणा PPCR_F162_2MHz	PPCR_Fx44	/*   Freq. (fcpu) = 162.2 MHz      */
#घोषणा PPCR_F176_9MHz	PPCR_Fx48	/*   Freq. (fcpu) = 176.9 MHz      */
#घोषणा PPCR_F191_7MHz	PPCR_Fx52	/*   Freq. (fcpu) = 191.7 MHz      */
#घोषणा PPCR_F206_4MHz	PPCR_Fx56	/*   Freq. (fcpu) = 206.4 MHz      */
#घोषणा PPCR_F221_2MHz	PPCR_Fx60	/*   Freq. (fcpu) = 221.2 MHz      */
#घोषणा PPCR_F239_6MHz	PPCR_Fx64	/*   Freq. (fcpu) = 239.6 MHz      */
#घोषणा PPCR_F250_7MHz	PPCR_Fx68	/*   Freq. (fcpu) = 250.7 MHz      */
#घोषणा PPCR_F265_4MHz	PPCR_Fx72	/*   Freq. (fcpu) = 265.4 MHz      */
#घोषणा PPCR_F280_2MHz	PPCR_Fx76	/*   Freq. (fcpu) = 280.2 MHz      */
                	        	/*  3.5795 MHz crystal (fxtl):     */
#घोषणा PPCR_F57_3MHz	PPCR_Fx16	/*   Freq. (fcpu) =  57.3 MHz      */
#घोषणा PPCR_F71_6MHz	PPCR_Fx20	/*   Freq. (fcpu) =  71.6 MHz      */
#घोषणा PPCR_F85_9MHz	PPCR_Fx24	/*   Freq. (fcpu) =  85.9 MHz      */
#घोषणा PPCR_F100_2MHz	PPCR_Fx28	/*   Freq. (fcpu) = 100.2 MHz      */
#घोषणा PPCR_F114_5MHz	PPCR_Fx32	/*   Freq. (fcpu) = 114.5 MHz      */
#घोषणा PPCR_F128_9MHz	PPCR_Fx36	/*   Freq. (fcpu) = 128.9 MHz      */
#घोषणा PPCR_F143_2MHz	PPCR_Fx40	/*   Freq. (fcpu) = 143.2 MHz      */
#घोषणा PPCR_F157_5MHz	PPCR_Fx44	/*   Freq. (fcpu) = 157.5 MHz      */
#घोषणा PPCR_F171_8MHz	PPCR_Fx48	/*   Freq. (fcpu) = 171.8 MHz      */
#घोषणा PPCR_F186_1MHz	PPCR_Fx52	/*   Freq. (fcpu) = 186.1 MHz      */
#घोषणा PPCR_F200_5MHz	PPCR_Fx56	/*   Freq. (fcpu) = 200.5 MHz      */
#घोषणा PPCR_F214_8MHz	PPCR_Fx60	/*   Freq. (fcpu) = 214.8 MHz      */
#घोषणा PPCR_F229_1MHz	PPCR_Fx64	/*   Freq. (fcpu) = 229.1 MHz      */
#घोषणा PPCR_F243_4MHz	PPCR_Fx68	/*   Freq. (fcpu) = 243.4 MHz      */
#घोषणा PPCR_F257_7MHz	PPCR_Fx72	/*   Freq. (fcpu) = 257.7 MHz      */
#घोषणा PPCR_F272_0MHz	PPCR_Fx76	/*   Freq. (fcpu) = 272.0 MHz      */

#घोषणा POSR_OOK	0x00000001	/* RTC Oscillator (32.768 kHz) OK  */


/*
 * Reset Controller (RC) control रेजिस्टरs
 *
 * Registers
 *    RSRR      	Reset Controller (RC) Software Reset Register
 *              	(पढ़ो/ग_लिखो).
 *    RCSR      	Reset Controller (RC) Status Register (पढ़ो/ग_लिखो).
 */

#घोषणा RSRR		__REG(0x90030000)  /* RC Software Reset Reg. */
#घोषणा RCSR		__REG(0x90030004)  /* RC Status Reg. */

#घोषणा RSRR_SWR	0x00000001	/* SoftWare Reset (set only)       */

#घोषणा RCSR_HWR	0x00000001	/* HardWare Reset                  */
#घोषणा RCSR_SWR	0x00000002	/* SoftWare Reset                  */
#घोषणा RCSR_WDR	0x00000004	/* Watch-Dog Reset                 */
#घोषणा RCSR_SMR	0x00000008	/* Sleep-Mode Reset                */


/*
 * Test unit control रेजिस्टरs
 *
 * Registers
 *    TUCR      	Test Unit Control Register (पढ़ो/ग_लिखो).
 */

#घोषणा TUCR		__REG(0x90030008)  /* Test Unit Control Reg. */

#घोषणा TUCR_TIC	0x00000040	/* TIC mode                        */
#घोषणा TUCR_TTST	0x00000080	/* Trim TeST mode                  */
#घोषणा TUCR_RCRC	0x00000100	/* Riअक्षरd's Cyclic Redundancy     */
                	        	/* Check                           */
#घोषणा TUCR_PMD	0x00000200	/* Power Management Disable        */
#घोषणा TUCR_MR 	0x00000400	/* Memory Request mode             */
#घोषणा TUCR_NoMB	(TUCR_MR*0)	/*  No Memory Bus request & grant  */
#घोषणा TUCR_MBGPIO	(TUCR_MR*1)	/*  Memory Bus request (MBREQ) &   */
                	        	/*  grant (MBGNT) on GPIO [22:21]  */
#घोषणा TUCR_CTB	Fld (3, 20)	/* Clock Test Bits                 */
#घोषणा TUCR_FDC	0x00800000	/* RTC Force Delete Count          */
#घोषणा TUCR_FMC	0x01000000	/* Force Michelle's Control mode   */
#घोषणा TUCR_TMC	0x02000000	/* RTC Trimmer Multiplexer Control */
#घोषणा TUCR_DPS	0x04000000	/* Disallow Pad Sleep              */
#घोषणा TUCR_TSEL	Fld (3, 29)	/* घड़ी Test SELect on GPIO [27]  */
#घोषणा TUCR_32_768kHz	        	/*  32.768 kHz osc. on GPIO [27]   */ \
                	(0 << FShft (TUCR_TSEL))
#घोषणा TUCR_3_6864MHz	        	/*  3.6864 MHz osc. on GPIO [27]   */ \
                	(1 << FShft (TUCR_TSEL))
#घोषणा TUCR_VDD	        	/*  VDD ring osc./16 on GPIO [27]  */ \
                	(2 << FShft (TUCR_TSEL))
#घोषणा TUCR_96MHzPLL	        	/*  96 MHz PLL/4 on GPIO [27]      */ \
                	(3 << FShft (TUCR_TSEL))
#घोषणा TUCR_Clock	        	/*  पूर्णांकernal (fcpu/2) & 32.768 kHz */ \
                	        	/*  Clocks on GPIO [26:27]         */ \
                	(4 << FShft (TUCR_TSEL))
#घोषणा TUCR_3_6864MHzA	        	/*  3.6864 MHz osc. on GPIO [27]   */ \
                	        	/*  (Alternative)                  */ \
                	(5 << FShft (TUCR_TSEL))
#घोषणा TUCR_MainPLL	        	/*  Main PLL/16 on GPIO [27]       */ \
                	(6 << FShft (TUCR_TSEL))
#घोषणा TUCR_VDDL	        	/*  VDDL ring osc./4 on GPIO [27]  */ \
                	(7 << FShft (TUCR_TSEL))


/*
 * General-Purpose Input/Output (GPIO) control रेजिस्टरs
 *
 * Registers
 *    GPLR      	General-Purpose Input/Output (GPIO) Pin Level
 *              	Register (पढ़ो).
 *    GPDR      	General-Purpose Input/Output (GPIO) Pin Direction
 *              	Register (पढ़ो/ग_लिखो).
 *    GPSR      	General-Purpose Input/Output (GPIO) Pin output Set
 *              	Register (ग_लिखो).
 *    GPCR      	General-Purpose Input/Output (GPIO) Pin output Clear
 *              	Register (ग_लिखो).
 *    GRER      	General-Purpose Input/Output (GPIO) Rising-Edge
 *              	detect Register (पढ़ो/ग_लिखो).
 *    GFER      	General-Purpose Input/Output (GPIO) Falling-Edge
 *              	detect Register (पढ़ो/ग_लिखो).
 *    GEDR      	General-Purpose Input/Output (GPIO) Edge Detect
 *              	status Register (पढ़ो/ग_लिखो).
 *    GAFR      	General-Purpose Input/Output (GPIO) Alternate
 *              	Function Register (पढ़ो/ग_लिखो).
 *
 * Clock
 *    fcpu, Tcpu	Frequency, period of the CPU core घड़ी (CCLK).
 */

#घोषणा GPLR		__REG(0x90040000)  /* GPIO Pin Level Reg.             */
#घोषणा GPDR		__REG(0x90040004)  /* GPIO Pin Direction Reg.         */
#घोषणा GPSR		__REG(0x90040008)  /* GPIO Pin output Set Reg.        */
#घोषणा GPCR		__REG(0x9004000C)  /* GPIO Pin output Clear Reg.      */
#घोषणा GRER		__REG(0x90040010)  /* GPIO Rising-Edge detect Reg.    */
#घोषणा GFER		__REG(0x90040014)  /* GPIO Falling-Edge detect Reg.   */
#घोषणा GEDR		__REG(0x90040018)  /* GPIO Edge Detect status Reg.    */
#घोषणा GAFR		__REG(0x9004001C)  /* GPIO Alternate Function Reg.    */

#घोषणा GPIO_MIN	(0)
#घोषणा GPIO_MAX	(27)

#घोषणा GPIO_GPIO(Nb)	        	/* GPIO [0..27]                    */ \
                	(0x00000001 << (Nb))
#घोषणा GPIO_GPIO0	GPIO_GPIO (0)	/* GPIO  [0]                       */
#घोषणा GPIO_GPIO1	GPIO_GPIO (1)	/* GPIO  [1]                       */
#घोषणा GPIO_GPIO2	GPIO_GPIO (2)	/* GPIO  [2]                       */
#घोषणा GPIO_GPIO3	GPIO_GPIO (3)	/* GPIO  [3]                       */
#घोषणा GPIO_GPIO4	GPIO_GPIO (4)	/* GPIO  [4]                       */
#घोषणा GPIO_GPIO5	GPIO_GPIO (5)	/* GPIO  [5]                       */
#घोषणा GPIO_GPIO6	GPIO_GPIO (6)	/* GPIO  [6]                       */
#घोषणा GPIO_GPIO7	GPIO_GPIO (7)	/* GPIO  [7]                       */
#घोषणा GPIO_GPIO8	GPIO_GPIO (8)	/* GPIO  [8]                       */
#घोषणा GPIO_GPIO9	GPIO_GPIO (9)	/* GPIO  [9]                       */
#घोषणा GPIO_GPIO10	GPIO_GPIO (10)	/* GPIO [10]                       */
#घोषणा GPIO_GPIO11	GPIO_GPIO (11)	/* GPIO [11]                       */
#घोषणा GPIO_GPIO12	GPIO_GPIO (12)	/* GPIO [12]                       */
#घोषणा GPIO_GPIO13	GPIO_GPIO (13)	/* GPIO [13]                       */
#घोषणा GPIO_GPIO14	GPIO_GPIO (14)	/* GPIO [14]                       */
#घोषणा GPIO_GPIO15	GPIO_GPIO (15)	/* GPIO [15]                       */
#घोषणा GPIO_GPIO16	GPIO_GPIO (16)	/* GPIO [16]                       */
#घोषणा GPIO_GPIO17	GPIO_GPIO (17)	/* GPIO [17]                       */
#घोषणा GPIO_GPIO18	GPIO_GPIO (18)	/* GPIO [18]                       */
#घोषणा GPIO_GPIO19	GPIO_GPIO (19)	/* GPIO [19]                       */
#घोषणा GPIO_GPIO20	GPIO_GPIO (20)	/* GPIO [20]                       */
#घोषणा GPIO_GPIO21	GPIO_GPIO (21)	/* GPIO [21]                       */
#घोषणा GPIO_GPIO22	GPIO_GPIO (22)	/* GPIO [22]                       */
#घोषणा GPIO_GPIO23	GPIO_GPIO (23)	/* GPIO [23]                       */
#घोषणा GPIO_GPIO24	GPIO_GPIO (24)	/* GPIO [24]                       */
#घोषणा GPIO_GPIO25	GPIO_GPIO (25)	/* GPIO [25]                       */
#घोषणा GPIO_GPIO26	GPIO_GPIO (26)	/* GPIO [26]                       */
#घोषणा GPIO_GPIO27	GPIO_GPIO (27)	/* GPIO [27]                       */

#घोषणा GPIO_LDD(Nb)	        	/* LCD Data [8..15] (O)            */ \
                	GPIO_GPIO ((Nb) - 6)
#घोषणा GPIO_LDD8	GPIO_LDD (8)	/* LCD Data  [8] (O)               */
#घोषणा GPIO_LDD9	GPIO_LDD (9)	/* LCD Data  [9] (O)               */
#घोषणा GPIO_LDD10	GPIO_LDD (10)	/* LCD Data [10] (O)               */
#घोषणा GPIO_LDD11	GPIO_LDD (11)	/* LCD Data [11] (O)               */
#घोषणा GPIO_LDD12	GPIO_LDD (12)	/* LCD Data [12] (O)               */
#घोषणा GPIO_LDD13	GPIO_LDD (13)	/* LCD Data [13] (O)               */
#घोषणा GPIO_LDD14	GPIO_LDD (14)	/* LCD Data [14] (O)               */
#घोषणा GPIO_LDD15	GPIO_LDD (15)	/* LCD Data [15] (O)               */
                	        	/* ser. port 4:                    */
#घोषणा GPIO_SSP_TXD	GPIO_GPIO (10)	/*  SSP Transmit Data (O)          */
#घोषणा GPIO_SSP_RXD	GPIO_GPIO (11)	/*  SSP Receive Data (I)           */
#घोषणा GPIO_SSP_SCLK	GPIO_GPIO (12)	/*  SSP Sample CLocK (O)           */
#घोषणा GPIO_SSP_SFRM	GPIO_GPIO (13)	/*  SSP Sample FRaMe (O)           */
                	        	/* ser. port 1:                    */
#घोषणा GPIO_UART_TXD	GPIO_GPIO (14)	/*  UART Transmit Data (O)         */
#घोषणा GPIO_UART_RXD	GPIO_GPIO (15)	/*  UART Receive Data (I)          */
#घोषणा GPIO_SDLC_SCLK	GPIO_GPIO (16)	/*  SDLC Sample CLocK (I/O)        */
#घोषणा GPIO_SDLC_AAF	GPIO_GPIO (17)	/*  SDLC Abort After Frame (O)     */
#घोषणा GPIO_UART_SCLK1	GPIO_GPIO (18)	/*  UART Sample CLocK 1 (I)        */
                	        	/* ser. port 4:                    */
#घोषणा GPIO_SSP_CLK	GPIO_GPIO (19)	/*  SSP बाह्यal CLocK (I)         */
                	        	/* ser. port 3:                    */
#घोषणा GPIO_UART_SCLK3	GPIO_GPIO (20)	/*  UART Sample CLocK 3 (I)        */
                	        	/* ser. port 4:                    */
#घोषणा GPIO_MCP_CLK	GPIO_GPIO (21)	/*  MCP CLocK (I)                  */
                	        	/* test controller:                */
#घोषणा GPIO_TIC_ACK	GPIO_GPIO (21)	/*  TIC ACKnowledge (O)            */
#घोषणा GPIO_MBGNT	GPIO_GPIO (21)	/*  Memory Bus GraNT (O)           */
#घोषणा GPIO_TREQA	GPIO_GPIO (22)	/*  TIC REQuest A (I)              */
#घोषणा GPIO_MBREQ	GPIO_GPIO (22)	/*  Memory Bus REQuest (I)         */
#घोषणा GPIO_TREQB	GPIO_GPIO (23)	/*  TIC REQuest B (I)              */
#घोषणा GPIO_1Hz	GPIO_GPIO (25)	/* 1 Hz घड़ी (O)                  */
#घोषणा GPIO_RCLK	GPIO_GPIO (26)	/* पूर्णांकernal (R) CLocK (O, fcpu/2)  */
#घोषणा GPIO_32_768kHz	GPIO_GPIO (27)	/* 32.768 kHz घड़ी (O, RTC)       */

#घोषणा GPDR_In 	0       	/* Input                           */
#घोषणा GPDR_Out	1       	/* Output                          */


/*
 * Interrupt Controller (IC) control रेजिस्टरs
 *
 * Registers
 *    ICIP      	Interrupt Controller (IC) Interrupt ReQuest (IRQ)
 *              	Pending रेजिस्टर (पढ़ो).
 *    ICMR      	Interrupt Controller (IC) Mask Register (पढ़ो/ग_लिखो).
 *    ICLR      	Interrupt Controller (IC) Level Register (पढ़ो/ग_लिखो).
 *    ICCR      	Interrupt Controller (IC) Control Register
 *              	(पढ़ो/ग_लिखो).
 *              	[The ICCR रेजिस्टर is only implemented in versions 2.0
 *              	(rev. = 8) and higher of the StrongARM SA-1100.]
 *    ICFP      	Interrupt Controller (IC) Fast Interrupt reQuest
 *              	(FIQ) Pending रेजिस्टर (पढ़ो).
 *    ICPR      	Interrupt Controller (IC) Pending Register (पढ़ो).
 *              	[The ICPR रेजिस्टर is active low (inverted) in
 *              	versions 1.0 (rev. = 1) and 1.1 (rev. = 2) of the
 *              	StrongARM SA-1100, it is active high (non-inverted) in
 *              	versions 2.0 (rev. = 8) and higher.]
 */

#घोषणा ICIP		__REG(0x90050000)  /* IC IRQ Pending reg.             */
#घोषणा ICMR		__REG(0x90050004)  /* IC Mask Reg.                    */
#घोषणा ICLR		__REG(0x90050008)  /* IC Level Reg.                   */
#घोषणा ICCR		__REG(0x9005000C)  /* IC Control Reg.                 */
#घोषणा ICFP		__REG(0x90050010)  /* IC FIQ Pending reg.             */
#घोषणा ICPR		__REG(0x90050020)  /* IC Pending Reg.                 */

#घोषणा IC_GPIO(Nb)	        	/* GPIO [0..10]                    */ \
                	(0x00000001 << (Nb))
#घोषणा IC_GPIO0	IC_GPIO (0)	/* GPIO  [0]                       */
#घोषणा IC_GPIO1	IC_GPIO (1)	/* GPIO  [1]                       */
#घोषणा IC_GPIO2	IC_GPIO (2)	/* GPIO  [2]                       */
#घोषणा IC_GPIO3	IC_GPIO (3)	/* GPIO  [3]                       */
#घोषणा IC_GPIO4	IC_GPIO (4)	/* GPIO  [4]                       */
#घोषणा IC_GPIO5	IC_GPIO (5)	/* GPIO  [5]                       */
#घोषणा IC_GPIO6	IC_GPIO (6)	/* GPIO  [6]                       */
#घोषणा IC_GPIO7	IC_GPIO (7)	/* GPIO  [7]                       */
#घोषणा IC_GPIO8	IC_GPIO (8)	/* GPIO  [8]                       */
#घोषणा IC_GPIO9	IC_GPIO (9)	/* GPIO  [9]                       */
#घोषणा IC_GPIO10	IC_GPIO (10)	/* GPIO [10]                       */
#घोषणा IC_GPIO11_27	0x00000800	/* GPIO [11:27] (ORed)             */
#घोषणा IC_LCD  	0x00001000	/* LCD controller                  */
#घोषणा IC_Ser0UDC	0x00002000	/* Ser. port 0 UDC                 */
#घोषणा IC_Ser1SDLC	0x00004000	/* Ser. port 1 SDLC                */
#घोषणा IC_Ser1UART	0x00008000	/* Ser. port 1 UART                */
#घोषणा IC_Ser2ICP	0x00010000	/* Ser. port 2 ICP                 */
#घोषणा IC_Ser3UART	0x00020000	/* Ser. port 3 UART                */
#घोषणा IC_Ser4MCP	0x00040000	/* Ser. port 4 MCP                 */
#घोषणा IC_Ser4SSP	0x00080000	/* Ser. port 4 SSP                 */
#घोषणा IC_DMA(Nb)	        	/* DMA controller channel [0..5]   */ \
                	(0x00100000 << (Nb))
#घोषणा IC_DMA0 	IC_DMA (0)	/* DMA controller channel 0        */
#घोषणा IC_DMA1 	IC_DMA (1)	/* DMA controller channel 1        */
#घोषणा IC_DMA2 	IC_DMA (2)	/* DMA controller channel 2        */
#घोषणा IC_DMA3 	IC_DMA (3)	/* DMA controller channel 3        */
#घोषणा IC_DMA4 	IC_DMA (4)	/* DMA controller channel 4        */
#घोषणा IC_DMA5 	IC_DMA (5)	/* DMA controller channel 5        */
#घोषणा IC_OST(Nb)	        	/* OS Timer match [0..3]           */ \
                	(0x04000000 << (Nb))
#घोषणा IC_OST0 	IC_OST (0)	/* OS Timer match 0                */
#घोषणा IC_OST1 	IC_OST (1)	/* OS Timer match 1                */
#घोषणा IC_OST2 	IC_OST (2)	/* OS Timer match 2                */
#घोषणा IC_OST3 	IC_OST (3)	/* OS Timer match 3                */
#घोषणा IC_RTC1Hz	0x40000000	/* RTC 1 Hz घड़ी                  */
#घोषणा IC_RTCAlrm	0x80000000	/* RTC Alarm                       */

#घोषणा ICLR_IRQ	0       	/* Interrupt ReQuest               */
#घोषणा ICLR_FIQ	1       	/* Fast Interrupt reQuest          */

#घोषणा ICCR_DIM	0x00000001	/* Disable Idle-mode पूर्णांकerrupt     */
                	        	/* Mask                            */
#घोषणा ICCR_IdleAllInt	(ICCR_DIM*0)	/*  Idle-mode All Interrupt enable */
                	        	/*  (ICMR ignored)                 */
#घोषणा ICCR_IdleMskInt	(ICCR_DIM*1)	/*  Idle-mode non-Masked Interrupt */
                	        	/*  enable (ICMR used)             */


/*
 * Peripheral Pin Controller (PPC) control रेजिस्टरs
 *
 * Registers
 *    PPDR      	Peripheral Pin Controller (PPC) Pin Direction
 *              	Register (पढ़ो/ग_लिखो).
 *    PPSR      	Peripheral Pin Controller (PPC) Pin State Register
 *              	(पढ़ो/ग_लिखो).
 *    PPAR      	Peripheral Pin Controller (PPC) Pin Assignment
 *              	Register (पढ़ो/ग_लिखो).
 *    PSDR      	Peripheral Pin Controller (PPC) Sleep-mode pin
 *              	Direction Register (पढ़ो/ग_लिखो).
 *    PPFR      	Peripheral Pin Controller (PPC) Pin Flag Register
 *              	(पढ़ो).
 */

#घोषणा PPDR		__REG(0x90060000)  /* PPC Pin Direction Reg.          */
#घोषणा PPSR		__REG(0x90060004)  /* PPC Pin State Reg.              */
#घोषणा PPAR		__REG(0x90060008)  /* PPC Pin Assignment Reg.         */
#घोषणा PSDR		__REG(0x9006000C)  /* PPC Sleep-mode pin Direction Reg. */
#घोषणा PPFR		__REG(0x90060010)  /* PPC Pin Flag Reg.               */

#घोषणा PPC_LDD(Nb)	        	/* LCD Data [0..7]                 */ \
                	(0x00000001 << (Nb))
#घोषणा PPC_LDD0	PPC_LDD (0)	/* LCD Data [0]                    */
#घोषणा PPC_LDD1	PPC_LDD (1)	/* LCD Data [1]                    */
#घोषणा PPC_LDD2	PPC_LDD (2)	/* LCD Data [2]                    */
#घोषणा PPC_LDD3	PPC_LDD (3)	/* LCD Data [3]                    */
#घोषणा PPC_LDD4	PPC_LDD (4)	/* LCD Data [4]                    */
#घोषणा PPC_LDD5	PPC_LDD (5)	/* LCD Data [5]                    */
#घोषणा PPC_LDD6	PPC_LDD (6)	/* LCD Data [6]                    */
#घोषणा PPC_LDD7	PPC_LDD (7)	/* LCD Data [7]                    */
#घोषणा PPC_L_PCLK	0x00000100	/* LCD Pixel CLocK                 */
#घोषणा PPC_L_LCLK	0x00000200	/* LCD Line CLocK                  */
#घोषणा PPC_L_FCLK	0x00000400	/* LCD Frame CLocK                 */
#घोषणा PPC_L_BIAS	0x00000800	/* LCD AC BIAS                     */
                	        	/* ser. port 1:                    */
#घोषणा PPC_TXD1	0x00001000	/*  SDLC/UART Transmit Data 1      */
#घोषणा PPC_RXD1	0x00002000	/*  SDLC/UART Receive Data 1       */
                	        	/* ser. port 2:                    */
#घोषणा PPC_TXD2	0x00004000	/*  IPC Transmit Data 2            */
#घोषणा PPC_RXD2	0x00008000	/*  IPC Receive Data 2             */
                	        	/* ser. port 3:                    */
#घोषणा PPC_TXD3	0x00010000	/*  UART Transmit Data 3           */
#घोषणा PPC_RXD3	0x00020000	/*  UART Receive Data 3            */
                	        	/* ser. port 4:                    */
#घोषणा PPC_TXD4	0x00040000	/*  MCP/SSP Transmit Data 4        */
#घोषणा PPC_RXD4	0x00080000	/*  MCP/SSP Receive Data 4         */
#घोषणा PPC_SCLK	0x00100000	/*  MCP/SSP Sample CLocK           */
#घोषणा PPC_SFRM	0x00200000	/*  MCP/SSP Sample FRaMe           */

#घोषणा PPDR_In 	0       	/* Input                           */
#घोषणा PPDR_Out	1       	/* Output                          */

                	        	/* ser. port 1:                    */
#घोषणा PPAR_UPR	0x00001000	/*  UART Pin Reassignment          */
#घोषणा PPAR_UARTTR	(PPAR_UPR*0)	/*   UART on TXD_1 & RXD_1         */
#घोषणा PPAR_UARTGPIO	(PPAR_UPR*1)	/*   UART on GPIO [14:15]          */
                	        	/* ser. port 4:                    */
#घोषणा PPAR_SPR	0x00040000	/*  SSP Pin Reassignment           */
#घोषणा PPAR_SSPTRSS	(PPAR_SPR*0)	/*   SSP on TXD_C, RXD_C, SCLK_C,  */
                	        	/*   & SFRM_C                      */
#घोषणा PPAR_SSPGPIO	(PPAR_SPR*1)	/*   SSP on GPIO [10:13]           */

#घोषणा PSDR_OutL	0       	/* Output Low in sleep mode        */
#घोषणा PSDR_Flt	1       	/* Floating (input) in sleep mode  */

#घोषणा PPFR_LCD	0x00000001	/* LCD controller                  */
#घोषणा PPFR_SP1TX	0x00001000	/* Ser. Port 1 SDLC/UART Transmit  */
#घोषणा PPFR_SP1RX	0x00002000	/* Ser. Port 1 SDLC/UART Receive   */
#घोषणा PPFR_SP2TX	0x00004000	/* Ser. Port 2 ICP Transmit        */
#घोषणा PPFR_SP2RX	0x00008000	/* Ser. Port 2 ICP Receive         */
#घोषणा PPFR_SP3TX	0x00010000	/* Ser. Port 3 UART Transmit       */
#घोषणा PPFR_SP3RX	0x00020000	/* Ser. Port 3 UART Receive        */
#घोषणा PPFR_SP4	0x00040000	/* Ser. Port 4 MCP/SSP             */
#घोषणा PPFR_PerEn	0       	/* Peripheral Enabled              */
#घोषणा PPFR_PPCEn	1       	/* PPC Enabled                     */


/*
 * Dynamic Ranकरोm-Access Memory (DRAM) control रेजिस्टरs
 *
 * Registers
 *    MDCNFG    	Memory प्रणाली: Dynamic Ranकरोm-Access Memory (DRAM)
 *              	CoNFiGuration रेजिस्टर (पढ़ो/ग_लिखो).
 *    MDCAS0    	Memory प्रणाली: Dynamic Ranकरोm-Access Memory (DRAM)
 *              	Column Address Strobe (CAS) shअगरt रेजिस्टर 0
 *              	(पढ़ो/ग_लिखो).
 *    MDCAS1    	Memory प्रणाली: Dynamic Ranकरोm-Access Memory (DRAM)
 *              	Column Address Strobe (CAS) shअगरt रेजिस्टर 1
 *              	(पढ़ो/ग_लिखो).
 *    MDCAS2    	Memory प्रणाली: Dynamic Ranकरोm-Access Memory (DRAM)
 *              	Column Address Strobe (CAS) shअगरt रेजिस्टर 2
 *              	(पढ़ो/ग_लिखो).
 *
 * Clocks
 *    fcpu, Tcpu	Frequency, period of the CPU core घड़ी (CCLK).
 *    fmem, Tmem	Frequency, period of the memory घड़ी (fmem = fcpu/2).
 *    fcas, Tcas	Frequency, period of the DRAM CAS shअगरt रेजिस्टरs.
 */

#घोषणा MDCNFG		__REG(0xA0000000)  /*  DRAM CoNFiGuration reg. */
#घोषणा MDCAS0		__REG(0xA0000004)  /* DRAM CAS shअगरt reg. 0 */
#घोषणा MDCAS1		__REG(0xA0000008)  /* DRAM CAS shअगरt reg. 1 */
#घोषणा MDCAS2		__REG(0xA000000c)  /* DRAM CAS shअगरt reg. 2 */

/* SA1100 MDCNFG values */
#घोषणा MDCNFG_DE(Nb)	        	/* DRAM Enable bank [0..3]         */ \
                	(0x00000001 << (Nb))
#घोषणा MDCNFG_DE0	MDCNFG_DE (0)	/* DRAM Enable bank 0              */
#घोषणा MDCNFG_DE1	MDCNFG_DE (1)	/* DRAM Enable bank 1              */
#घोषणा MDCNFG_DE2	MDCNFG_DE (2)	/* DRAM Enable bank 2              */
#घोषणा MDCNFG_DE3	MDCNFG_DE (3)	/* DRAM Enable bank 3              */
#घोषणा MDCNFG_DRAC	Fld (2, 4)	/* DRAM Row Address Count - 9      */
#घोषणा MDCNFG_RowAdd(Add)      	/*  Row Address count [9..12]      */ \
                	(((Add) - 9) << FShft (MDCNFG_DRAC))
#घोषणा MDCNFG_CDB2	0x00000040	/* shअगरt reg. Clock Divide By 2    */
                	        	/* (fcas = fcpu/2)                 */
#घोषणा MDCNFG_TRP	Fld (4, 7)	/* Time RAS Pre-अक्षरge - 1 [Tmem]  */
#घोषणा MDCNFG_PrChrg(Tcpu)     	/*  Pre-Charge समय [2..32 Tcpu]   */ \
                	(((Tcpu) - 2)/2 << FShft (MDCNFG_TRP))
#घोषणा MDCNFG_CeilPrChrg(Tcpu) 	/*  Ceil. of PrChrg [2..32 Tcpu]   */ \
                	(((Tcpu) - 1)/2 << FShft (MDCNFG_TRP))
#घोषणा MDCNFG_TRASR	Fld (4, 11)	/* Time RAS Refresh - 1 [Tmem]     */
#घोषणा MDCNFG_Ref(Tcpu)        	/*  Refresh समय [2..32 Tcpu]      */ \
                	(((Tcpu) - 2)/2 << FShft (MDCNFG_TRASR))
#घोषणा MDCNFG_CeilRef(Tcpu)    	/*  Ceil. of Ref [2..32 Tcpu]      */ \
                	(((Tcpu) - 1)/2 << FShft (MDCNFG_TRASR))
#घोषणा MDCNFG_TDL	Fld (2, 15)	/* Time Data Latch [Tcpu]          */
#घोषणा MDCNFG_DataLtch(Tcpu)   	/*  Data Latch delay [0..3 Tcpu]   */ \
                	((Tcpu) << FShft (MDCNFG_TDL))
#घोषणा MDCNFG_DRI	Fld (15, 17)	/* min. DRAM Refresh Interval/4    */
                	        	/* [Tmem]                          */
#घोषणा MDCNFG_RefInt(Tcpu)     	/*  min. Refresh Interval          */ \
                	        	/*  [0..262136 Tcpu]               */ \
                	((Tcpu)/8 << FShft (MDCNFG_DRI))

/* SA1110 MDCNFG values */
#घोषणा MDCNFG_SA1110_DE0	0x00000001	/* DRAM Enable bank 0        */
#घोषणा MDCNFG_SA1110_DE1	0x00000002 	/* DRAM Enable bank 1        */
#घोषणा MDCNFG_SA1110_DTIM0	0x00000004	/* DRAM timing type 0/1      */
#घोषणा MDCNFG_SA1110_DWID0	0x00000008	/* DRAM bus width 0/1        */
#घोषणा MDCNFG_SA1110_DRAC0	Fld(3, 4)	/* DRAM row addr bit count   */
                	        		/* bank 0/1                  */
#घोषणा MDCNFG_SA1110_CDB20	0x00000080	/* Mem Clock भागide by 2 0/1 */
#घोषणा MDCNFG_SA1110_TRP0	Fld(3, 8)	/* RAS preअक्षरge 0/1         */
#घोषणा MDCNFG_SA1110_TDL0	Fld(2, 12)	/* Data input latch after CAS*/
                	        		/* deनिश्चितion 0/1           */
#घोषणा MDCNFG_SA1110_TWR0	Fld(2, 14)	/* SDRAM ग_लिखो recovery 0/1  */
#घोषणा MDCNFG_SA1110_DE2	0x00010000	/* DRAM Enable bank 0        */
#घोषणा MDCNFG_SA1110_DE3	0x00020000 	/* DRAM Enable bank 1        */
#घोषणा MDCNFG_SA1110_DTIM2	0x00040000	/* DRAM timing type 0/1      */
#घोषणा MDCNFG_SA1110_DWID2	0x00080000	/* DRAM bus width 0/1        */
#घोषणा MDCNFG_SA1110_DRAC2	Fld(3, 20)	/* DRAM row addr bit count   */
                	        		/* bank 0/1                  */
#घोषणा MDCNFG_SA1110_CDB22	0x00800000	/* Mem Clock भागide by 2 0/1 */
#घोषणा MDCNFG_SA1110_TRP2	Fld(3, 24)	/* RAS preअक्षरge 0/1         */
#घोषणा MDCNFG_SA1110_TDL2	Fld(2, 28)	/* Data input latch after CAS*/
                	        		/* deनिश्चितion 0/1           */
#घोषणा MDCNFG_SA1110_TWR2	Fld(2, 30)	/* SDRAM ग_लिखो recovery 0/1  */


/*
 * Static memory control रेजिस्टरs
 *
 * Registers
 *    MSC0      	Memory प्रणाली: Static memory Control रेजिस्टर 0
 *              	(पढ़ो/ग_लिखो).
 *    MSC1      	Memory प्रणाली: Static memory Control रेजिस्टर 1
 *              	(पढ़ो/ग_लिखो).
 *
 * Clocks
 *    fcpu, Tcpu	Frequency, period of the CPU core घड़ी (CCLK).
 *    fmem, Tmem	Frequency, period of the memory घड़ी (fmem = fcpu/2).
 */

#घोषणा MSC0		__REG(0xa0000010)  /* Static memory Control reg. 0 */
#घोषणा MSC1		__REG(0xa0000014)  /* Static memory Control reg. 1 */
#घोषणा MSC2		__REG(0xa000002c)  /* Static memory Control reg. 2, not contiguous   */

#घोषणा MSC_Bnk(Nb)	        	/* अटल memory Bank [0..3]       */ \
                	Fld (16, ((Nb) Modulo 2)*16)
#घोषणा MSC0_Bnk0	MSC_Bnk (0)	/* अटल memory Bank 0            */
#घोषणा MSC0_Bnk1	MSC_Bnk (1)	/* अटल memory Bank 1            */
#घोषणा MSC1_Bnk2	MSC_Bnk (2)	/* अटल memory Bank 2            */
#घोषणा MSC1_Bnk3	MSC_Bnk (3)	/* अटल memory Bank 3            */

#घोषणा MSC_RT  	Fld (2, 0)	/* ROM/अटल memory Type          */
#घोषणा MSC_NonBrst	        	/*  Non-Burst अटल memory        */ \
                	(0 << FShft (MSC_RT))
#घोषणा MSC_SRAM	        	/*  32-bit byte-writable SRAM      */ \
                	(1 << FShft (MSC_RT))
#घोषणा MSC_Brst4	        	/*  Burst-of-4 अटल memory       */ \
                	(2 << FShft (MSC_RT))
#घोषणा MSC_Brst8	        	/*  Burst-of-8 अटल memory       */ \
                	(3 << FShft (MSC_RT))
#घोषणा MSC_RBW 	0x0004  	/* ROM/अटल memory Bus Width     */
#घोषणा MSC_32BitStMem	(MSC_RBW*0)	/*  32-Bit Static Memory           */
#घोषणा MSC_16BitStMem	(MSC_RBW*1)	/*  16-Bit Static Memory           */
#घोषणा MSC_RDF 	Fld (5, 3)	/* ROM/अटल memory पढ़ो Delay    */
                	        	/* First access - 1(.5) [Tmem]     */
#घोषणा MSC_1stRdAcc(Tcpu)      	/*  1st Read Access समय (burst    */ \
                	        	/*  अटल memory) [3..65 Tcpu]    */ \
                	((((Tcpu) - 3)/2) << FShft (MSC_RDF))
#घोषणा MSC_Ceil1stRdAcc(Tcpu)  	/*  Ceil. of 1stRdAcc [3..65 Tcpu] */ \
                	((((Tcpu) - 2)/2) << FShft (MSC_RDF))
#घोषणा MSC_RdAcc(Tcpu)	        	/*  Read Access समय (non-burst    */ \
                	        	/*  अटल memory) [2..64 Tcpu]    */ \
                	((((Tcpu) - 2)/2) << FShft (MSC_RDF))
#घोषणा MSC_CeilRdAcc(Tcpu)     	/*  Ceil. of RdAcc [2..64 Tcpu]    */ \
                	((((Tcpu) - 1)/2) << FShft (MSC_RDF))
#घोषणा MSC_RDN 	Fld (5, 8)	/* ROM/अटल memory पढ़ो Delay    */
                	        	/* Next access - 1 [Tmem]          */
#घोषणा MSC_NxtRdAcc(Tcpu)      	/*  Next Read Access समय (burst   */ \
                	        	/*  अटल memory) [2..64 Tcpu]    */ \
                	((((Tcpu) - 2)/2) << FShft (MSC_RDN))
#घोषणा MSC_CeilNxtRdAcc(Tcpu)  	/*  Ceil. of NxtRdAcc [2..64 Tcpu] */ \
                	((((Tcpu) - 1)/2) << FShft (MSC_RDN))
#घोषणा MSC_WrAcc(Tcpu)	        	/*  Write Access समय (non-burst   */ \
                	        	/*  अटल memory) [2..64 Tcpu]    */ \
                	((((Tcpu) - 2)/2) << FShft (MSC_RDN))
#घोषणा MSC_CeilWrAcc(Tcpu)     	/*  Ceil. of WrAcc [2..64 Tcpu]    */ \
                	((((Tcpu) - 1)/2) << FShft (MSC_RDN))
#घोषणा MSC_RRR 	Fld (3, 13)	/* ROM/अटल memory RecoveRy      */
                	        	/* समय/2 [Tmem]                   */
#घोषणा MSC_Rec(Tcpu)	        	/*  Recovery समय [0..28 Tcpu]     */ \
                	(((Tcpu)/4) << FShft (MSC_RRR))
#घोषणा MSC_CeilRec(Tcpu)       	/*  Ceil. of Rec [0..28 Tcpu]      */ \
                	((((Tcpu) + 3)/4) << FShft (MSC_RRR))


/*
 * Personal Computer Memory Card International Association (PCMCIA) control
 * रेजिस्टर
 *
 * Register
 *    MECR      	Memory प्रणाली: Expansion memory bus (PCMCIA)
 *              	Configuration Register (पढ़ो/ग_लिखो).
 *
 * Clocks
 *    fcpu, Tcpu	Frequency, period of the CPU core घड़ी (CCLK).
 *    fmem, Tmem	Frequency, period of the memory घड़ी (fmem = fcpu/2).
 *    fbclk, Tbclk	Frequency, period of the PCMCIA घड़ी (BCLK).
 */

                	        	/* Memory प्रणाली:                  */
#घोषणा MECR		__REG(0xA0000018)  /*  Expansion memory bus (PCMCIA) Configuration Reg.             */

#घोषणा MECR_PCMCIA(Nb)	        	/* PCMCIA [0..1]                   */ \
                	Fld (15, (Nb)*16)
#घोषणा MECR_PCMCIA0	MECR_PCMCIA (0)	/* PCMCIA 0                        */
#घोषणा MECR_PCMCIA1	MECR_PCMCIA (1)	/* PCMCIA 1                        */

#घोषणा MECR_BSIO	Fld (5, 0)	/* BCLK Select I/O - 1 [Tmem]      */
#घोषणा MECR_IOClk(Tcpu)        	/*  I/O Clock [2..64 Tcpu]         */ \
                	((((Tcpu) - 2)/2) << FShft (MECR_BSIO))
#घोषणा MECR_CeilIOClk(Tcpu)    	/*  Ceil. of IOClk [2..64 Tcpu]    */ \
                	((((Tcpu) - 1)/2) << FShft (MECR_BSIO))
#घोषणा MECR_BSA	Fld (5, 5)	/* BCLK Select Attribute - 1       */
                	        	/* [Tmem]                          */
#घोषणा MECR_AttrClk(Tcpu)      	/*  Attribute Clock [2..64 Tcpu]   */ \
                	((((Tcpu) - 2)/2) << FShft (MECR_BSA))
#घोषणा MECR_CeilAttrClk(Tcpu)  	/*  Ceil. of AttrClk [2..64 Tcpu]  */ \
                	((((Tcpu) - 1)/2) << FShft (MECR_BSA))
#घोषणा MECR_BSM	Fld (5, 10)	/* BCLK Select Memory - 1 [Tmem]   */
#घोषणा MECR_MemClk(Tcpu)       	/*  Memory Clock [2..64 Tcpu]      */ \
                	((((Tcpu) - 2)/2) << FShft (MECR_BSM))
#घोषणा MECR_CeilMemClk(Tcpu)   	/*  Ceil. of MemClk [2..64 Tcpu]   */ \
                	((((Tcpu) - 1)/2) << FShft (MECR_BSM))

/*
 * On SA1110 only
 */

#घोषणा MDREFR		__REG(0xA000001C)

#घोषणा MDREFR_TRASR		Fld (4, 0)
#घोषणा MDREFR_DRI		Fld (12, 4)
#घोषणा MDREFR_E0PIN		(1 << 16)
#घोषणा MDREFR_K0RUN		(1 << 17)
#घोषणा MDREFR_K0DB2		(1 << 18)
#घोषणा MDREFR_E1PIN		(1 << 20)
#घोषणा MDREFR_K1RUN		(1 << 21)
#घोषणा MDREFR_K1DB2		(1 << 22)
#घोषणा MDREFR_K2RUN		(1 << 25)
#घोषणा MDREFR_K2DB2		(1 << 26)
#घोषणा MDREFR_EAPD		(1 << 28)
#घोषणा MDREFR_KAPD		(1 << 29)
#घोषणा MDREFR_SLFRSH		(1 << 31)


/*
 * Direct Memory Access (DMA) control रेजिस्टरs
 */
#घोषणा DMA_SIZE	(6 * 0x20)
#घोषणा DMA_PHYS	0xb0000000


/*
 * Liquid Crystal Display (LCD) control रेजिस्टरs
 *
 * Registers
 *    LCCR0     	Liquid Crystal Display (LCD) Control Register 0
 *              	(पढ़ो/ग_लिखो).
 *              	[Bits LDM, BAM, and ERM are only implemented in
 *              	versions 2.0 (rev. = 8) and higher of the StrongARM
 *              	SA-1100.]
 *    LCSR      	Liquid Crystal Display (LCD) Status Register
 *              	(पढ़ो/ग_लिखो).
 *              	[Bit LDD can be only पढ़ो in versions 1.0 (rev. = 1)
 *              	and 1.1 (rev. = 2) of the StrongARM SA-1100, it can be
 *              	पढ़ो and written (cleared) in versions 2.0 (rev. = 8)
 *              	and higher.]
 *    DBAR1     	Liquid Crystal Display (LCD) Direct Memory Access
 *              	(DMA) Base Address Register channel 1 (पढ़ो/ग_लिखो).
 *    DCAR1     	Liquid Crystal Display (LCD) Direct Memory Access
 *              	(DMA) Current Address Register channel 1 (पढ़ो).
 *    DBAR2     	Liquid Crystal Display (LCD) Direct Memory Access
 *              	(DMA) Base Address Register channel 2 (पढ़ो/ग_लिखो).
 *    DCAR2     	Liquid Crystal Display (LCD) Direct Memory Access
 *              	(DMA) Current Address Register channel 2 (पढ़ो).
 *    LCCR1     	Liquid Crystal Display (LCD) Control Register 1
 *              	(पढ़ो/ग_लिखो).
 *              	[The LCCR1 रेजिस्टर can be only written in
 *              	versions 1.0 (rev. = 1) and 1.1 (rev. = 2) of the
 *              	StrongARM SA-1100, it can be written and पढ़ो in
 *              	versions 2.0 (rev. = 8) and higher.]
 *    LCCR2     	Liquid Crystal Display (LCD) Control Register 2
 *              	(पढ़ो/ग_लिखो).
 *              	[The LCCR1 रेजिस्टर can be only written in
 *              	versions 1.0 (rev. = 1) and 1.1 (rev. = 2) of the
 *              	StrongARM SA-1100, it can be written and पढ़ो in
 *              	versions 2.0 (rev. = 8) and higher.]
 *    LCCR3     	Liquid Crystal Display (LCD) Control Register 3
 *              	(पढ़ो/ग_लिखो).
 *              	[The LCCR1 रेजिस्टर can be only written in
 *              	versions 1.0 (rev. = 1) and 1.1 (rev. = 2) of the
 *              	StrongARM SA-1100, it can be written and पढ़ो in
 *              	versions 2.0 (rev. = 8) and higher. Bit PCP is only
 *              	implemented in versions 2.0 (rev. = 8) and higher of
 *              	the StrongARM SA-1100.]
 *
 * Clocks
 *    fcpu, Tcpu	Frequency, period of the CPU core घड़ी (CCLK).
 *    fmem, Tmem	Frequency, period of the memory घड़ी (fmem = fcpu/2).
 *    fpix, Tpix	Frequency, period of the pixel घड़ी.
 *    fln, Tln  	Frequency, period of the line घड़ी.
 *    fac, Tac  	Frequency, period of the AC bias घड़ी.
 */

#घोषणा LCD_PEntrySp	2       	/* LCD Palette Entry Space [byte]  */
#घोषणा LCD_4BitPSp	        	/* LCD 4-Bit pixel Palette Space   */ \
                	        	/* [byte]                          */ \
                	(16*LCD_PEntrySp)
#घोषणा LCD_8BitPSp	        	/* LCD 8-Bit pixel Palette Space   */ \
                	        	/* [byte]                          */ \
                	(256*LCD_PEntrySp)
#घोषणा LCD_12_16BitPSp	        	/* LCD 12/16-Bit pixel             */ \
                	        	/* dummy-Palette Space [byte]      */ \
                	(16*LCD_PEntrySp)

#घोषणा LCD_PGrey	Fld (4, 0)	/* LCD Palette entry Grey value    */
#घोषणा LCD_PBlue	Fld (4, 0)	/* LCD Palette entry Blue value    */
#घोषणा LCD_PGreen	Fld (4, 4)	/* LCD Palette entry Green value   */
#घोषणा LCD_PRed	Fld (4, 8)	/* LCD Palette entry Red value     */
#घोषणा LCD_PBS 	Fld (2, 12)	/* LCD Pixel Bit Size              */
#घोषणा LCD_4Bit	        	/*  LCD 4-Bit pixel mode           */ \
                	(0 << FShft (LCD_PBS))
#घोषणा LCD_8Bit	        	/*  LCD 8-Bit pixel mode           */ \
                	(1 << FShft (LCD_PBS))
#घोषणा LCD_12_16Bit	        	/*  LCD 12/16-Bit pixel mode       */ \
                	(2 << FShft (LCD_PBS))

#घोषणा LCD_Int0_0	0x0     	/* LCD Intensity =   0.0% =  0     */
#घोषणा LCD_Int11_1	0x1     	/* LCD Intensity =  11.1% =  1/9   */
#घोषणा LCD_Int20_0	0x2     	/* LCD Intensity =  20.0% =  1/5   */
#घोषणा LCD_Int26_7	0x3     	/* LCD Intensity =  26.7% =  4/15  */
#घोषणा LCD_Int33_3	0x4     	/* LCD Intensity =  33.3% =  3/9   */
#घोषणा LCD_Int40_0	0x5     	/* LCD Intensity =  40.0% =  2/5   */
#घोषणा LCD_Int44_4	0x6     	/* LCD Intensity =  44.4% =  4/9   */
#घोषणा LCD_Int50_0	0x7     	/* LCD Intensity =  50.0% =  1/2   */
#घोषणा LCD_Int55_6	0x8     	/* LCD Intensity =  55.6% =  5/9   */
#घोषणा LCD_Int60_0	0x9     	/* LCD Intensity =  60.0% =  3/5   */
#घोषणा LCD_Int66_7	0xA     	/* LCD Intensity =  66.7% =  6/9   */
#घोषणा LCD_Int73_3	0xB     	/* LCD Intensity =  73.3% = 11/15  */
#घोषणा LCD_Int80_0	0xC     	/* LCD Intensity =  80.0% =  4/5   */
#घोषणा LCD_Int88_9	0xD     	/* LCD Intensity =  88.9% =  8/9   */
#घोषणा LCD_Int100_0	0xE     	/* LCD Intensity = 100.0% =  1     */
#घोषणा LCD_Int100_0A	0xF     	/* LCD Intensity = 100.0% =  1     */
                	        	/* (Alternative)                   */

#घोषणा LCCR0_LEN	0x00000001	/* LCD ENable                      */
#घोषणा LCCR0_CMS	0x00000002	/* Color/Monochrome display Select */
#घोषणा LCCR0_Color	(LCCR0_CMS*0)	/*  Color display                  */
#घोषणा LCCR0_Mono	(LCCR0_CMS*1)	/*  Monochrome display             */
#घोषणा LCCR0_SDS	0x00000004	/* Single/Dual panel display       */
                	        	/* Select                          */
#घोषणा LCCR0_Sngl	(LCCR0_SDS*0)	/*  Single panel display           */
#घोषणा LCCR0_Dual	(LCCR0_SDS*1)	/*  Dual panel display             */
#घोषणा LCCR0_LDM	0x00000008	/* LCD Disable करोne (LDD)          */
                	        	/* पूर्णांकerrupt Mask (disable)        */
#घोषणा LCCR0_BAM	0x00000010	/* Base Address update (BAU)       */
                	        	/* पूर्णांकerrupt Mask (disable)        */
#घोषणा LCCR0_ERM	0x00000020	/* LCD ERror (BER, IOL, IUL, IOU,  */
                	        	/* IUU, OOL, OUL, OOU, and OUU)    */
                	        	/* पूर्णांकerrupt Mask (disable)        */
#घोषणा LCCR0_PAS	0x00000080	/* Passive/Active display Select   */
#घोषणा LCCR0_Pas	(LCCR0_PAS*0)	/*  Passive display (STN)          */
#घोषणा LCCR0_Act	(LCCR0_PAS*1)	/*  Active display (TFT)           */
#घोषणा LCCR0_BLE	0x00000100	/* Big/Little Endian select        */
#घोषणा LCCR0_LtlEnd	(LCCR0_BLE*0)	/*  Little Endian frame buffer     */
#घोषणा LCCR0_BigEnd	(LCCR0_BLE*1)	/*  Big Endian frame buffer        */
#घोषणा LCCR0_DPD	0x00000200	/* Double Pixel Data (monochrome   */
                	        	/* display mode)                   */
#घोषणा LCCR0_4PixMono	(LCCR0_DPD*0)	/*  4-Pixel/घड़ी Monochrome       */
                	        	/*  display                        */
#घोषणा LCCR0_8PixMono	(LCCR0_DPD*1)	/*  8-Pixel/घड़ी Monochrome       */
                	        	/*  display                        */
#घोषणा LCCR0_PDD	Fld (8, 12)	/* Palette DMA request Delay       */
                	        	/* [Tmem]                          */
#घोषणा LCCR0_DMADel(Tcpu)      	/*  palette DMA request Delay      */ \
                	        	/*  [0..510 Tcpu]                  */ \
                	((Tcpu)/2 << FShft (LCCR0_PDD))

#घोषणा LCSR_LDD	0x00000001	/* LCD Disable Done                */
#घोषणा LCSR_BAU	0x00000002	/* Base Address Update (पढ़ो)      */
#घोषणा LCSR_BER	0x00000004	/* Bus ERror                       */
#घोषणा LCSR_ABC	0x00000008	/* AC Bias घड़ी Count             */
#घोषणा LCSR_IOL	0x00000010	/* Input FIFO Over-run Lower       */
                	        	/* panel                           */
#घोषणा LCSR_IUL	0x00000020	/* Input FIFO Under-run Lower      */
                	        	/* panel                           */
#घोषणा LCSR_IOU	0x00000040	/* Input FIFO Over-run Upper       */
                	        	/* panel                           */
#घोषणा LCSR_IUU	0x00000080	/* Input FIFO Under-run Upper      */
                	        	/* panel                           */
#घोषणा LCSR_OOL	0x00000100	/* Output FIFO Over-run Lower      */
                	        	/* panel                           */
#घोषणा LCSR_OUL	0x00000200	/* Output FIFO Under-run Lower     */
                	        	/* panel                           */
#घोषणा LCSR_OOU	0x00000400	/* Output FIFO Over-run Upper      */
                	        	/* panel                           */
#घोषणा LCSR_OUU	0x00000800	/* Output FIFO Under-run Upper     */
                	        	/* panel                           */

#घोषणा LCCR1_PPL	Fld (6, 4)	/* Pixels Per Line/16 - 1          */
#घोषणा LCCR1_DisWdth(Pixel)    	/*  Display Width [16..1024 pix.]  */ \
                	(((Pixel) - 16)/16 << FShft (LCCR1_PPL))
#घोषणा LCCR1_HSW	Fld (6, 10)	/* Horizontal Synchronization      */
                	        	/* pulse Width - 1 [Tpix] (L_LCLK) */
#घोषणा LCCR1_HorSnchWdth(Tpix) 	/*  Horizontal Synchronization     */ \
                	        	/*  pulse Width [1..64 Tpix]       */ \
                	(((Tpix) - 1) << FShft (LCCR1_HSW))
#घोषणा LCCR1_ELW	Fld (8, 16)	/* End-of-Line pixel घड़ी Wait    */
                	        	/* count - 1 [Tpix]                */
#घोषणा LCCR1_EndLnDel(Tpix)    	/*  End-of-Line Delay              */ \
                	        	/*  [1..256 Tpix]                  */ \
                	(((Tpix) - 1) << FShft (LCCR1_ELW))
#घोषणा LCCR1_BLW	Fld (8, 24)	/* Beginning-of-Line pixel घड़ी   */
                	        	/* Wait count - 1 [Tpix]           */
#घोषणा LCCR1_BegLnDel(Tpix)    	/*  Beginning-of-Line Delay        */ \
                	        	/*  [1..256 Tpix]                  */ \
                	(((Tpix) - 1) << FShft (LCCR1_BLW))

#घोषणा LCCR2_LPP	Fld (10, 0)	/* Line Per Panel - 1              */
#घोषणा LCCR2_DisHght(Line)     	/*  Display Height [1..1024 lines] */ \
                	(((Line) - 1) << FShft (LCCR2_LPP))
#घोषणा LCCR2_VSW	Fld (6, 10)	/* Vertical Synchronization pulse  */
                	        	/* Width - 1 [Tln] (L_FCLK)        */
#घोषणा LCCR2_VrtSnchWdth(Tln)  	/*  Vertical Synchronization pulse */ \
                	        	/*  Width [1..64 Tln]              */ \
                	(((Tln) - 1) << FShft (LCCR2_VSW))
#घोषणा LCCR2_EFW	Fld (8, 16)	/* End-of-Frame line घड़ी Wait    */
                	        	/* count [Tln]                     */
#घोषणा LCCR2_EndFrmDel(Tln)    	/*  End-of-Frame Delay             */ \
                	        	/*  [0..255 Tln]                   */ \
                	((Tln) << FShft (LCCR2_EFW))
#घोषणा LCCR2_BFW	Fld (8, 24)	/* Beginning-of-Frame line घड़ी   */
                	        	/* Wait count [Tln]                */
#घोषणा LCCR2_BegFrmDel(Tln)    	/*  Beginning-of-Frame Delay       */ \
                	        	/*  [0..255 Tln]                   */ \
                	((Tln) << FShft (LCCR2_BFW))

#घोषणा LCCR3_PCD	Fld (8, 0)	/* Pixel Clock Divisor/2 - 2       */
                	        	/* [1..255] (L_PCLK)               */
                	        	/* fpix = fcpu/(2*(PCD + 2))       */
                	        	/* Tpix = 2*(PCD + 2)*Tcpu         */
#घोषणा LCCR3_PixClkDiv(Div)    	/*  Pixel Clock Divisor [6..514]   */ \
                	(((Div) - 4)/2 << FShft (LCCR3_PCD))
                	        	/*  fpix = fcpu/(2*Floor (Div/2))  */
                	        	/*  Tpix = 2*Floor (Div/2)*Tcpu    */
#घोषणा LCCR3_CeilPixClkDiv(Div)	/*  Ceil. of PixClkDiv [6..514]    */ \
                	(((Div) - 3)/2 << FShft (LCCR3_PCD))
                	        	/*  fpix = fcpu/(2*Ceil (Div/2))   */
                	        	/*  Tpix = 2*Ceil (Div/2)*Tcpu     */
#घोषणा LCCR3_ACB	Fld (8, 8)	/* AC Bias घड़ी half period - 1   */
                	        	/* [Tln] (L_BIAS)                  */
#घोषणा LCCR3_ACBsDiv(Div)      	/*  AC Bias घड़ी Divisor [2..512] */ \
                	(((Div) - 2)/2 << FShft (LCCR3_ACB))
                	        	/*  fac = fln/(2*Floor (Div/2))    */
                	        	/*  Tac = 2*Floor (Div/2)*Tln      */
#घोषणा LCCR3_CeilACBsDiv(Div)  	/*  Ceil. of ACBsDiv [2..512]      */ \
                	(((Div) - 1)/2 << FShft (LCCR3_ACB))
                	        	/*  fac = fln/(2*Ceil (Div/2))     */
                	        	/*  Tac = 2*Ceil (Div/2)*Tln       */
#घोषणा LCCR3_API	Fld (4, 16)	/* AC bias Pin transitions per     */
                	        	/* Interrupt                       */
#घोषणा LCCR3_ACBsCntOff        	/*  AC Bias घड़ी transition Count */ \
                	        	/*  Off                            */ \
                	(0 << FShft (LCCR3_API))
#घोषणा LCCR3_ACBsCnt(Trans)    	/*  AC Bias घड़ी transition Count */ \
                	        	/*  [1..15]                        */ \
                	((Trans) << FShft (LCCR3_API))
#घोषणा LCCR3_VSP	0x00100000	/* Vertical Synchronization pulse  */
                	        	/* Polarity (L_FCLK)               */
#घोषणा LCCR3_VrtSnchH	(LCCR3_VSP*0)	/*  Vertical Synchronization pulse */
                	        	/*  active High                    */
#घोषणा LCCR3_VrtSnchL	(LCCR3_VSP*1)	/*  Vertical Synchronization pulse */
                	        	/*  active Low                     */
#घोषणा LCCR3_HSP	0x00200000	/* Horizontal Synchronization      */
                	        	/* pulse Polarity (L_LCLK)         */
#घोषणा LCCR3_HorSnchH	(LCCR3_HSP*0)	/*  Horizontal Synchronization     */
                	        	/*  pulse active High              */
#घोषणा LCCR3_HorSnchL	(LCCR3_HSP*1)	/*  Horizontal Synchronization     */
                	        	/*  pulse active Low               */
#घोषणा LCCR3_PCP	0x00400000	/* Pixel Clock Polarity (L_PCLK)   */
#घोषणा LCCR3_PixRsEdg	(LCCR3_PCP*0)	/*  Pixel घड़ी Rising-Edge        */
#घोषणा LCCR3_PixFlEdg	(LCCR3_PCP*1)	/*  Pixel घड़ी Falling-Edge       */
#घोषणा LCCR3_OEP	0x00800000	/* Output Enable Polarity (L_BIAS, */
                	        	/* active display mode)            */
#घोषणा LCCR3_OutEnH	(LCCR3_OEP*0)	/*  Output Enable active High      */
#घोषणा LCCR3_OutEnL	(LCCR3_OEP*1)	/*  Output Enable active Low       */
