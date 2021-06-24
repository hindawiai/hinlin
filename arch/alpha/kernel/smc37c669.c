<शैली गुरु>
/*
 * SMC 37C669 initialization code
 */
#समावेश <linux/kernel.h>

#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/spinlock.h>

#समावेश <यंत्र/hwrpb.h>
#समावेश <यंत्र/पन.स>

#अगर 0
# define DBG_DEVS(args)         prपूर्णांकk args
#अन्यथा
# define DBG_DEVS(args)
#पूर्ण_अगर

#घोषणा KB              1024
#घोषणा MB              (1024*KB)
#घोषणा GB              (1024*MB)

#घोषणा SMC_DEBUG   0

/* File:	smcc669_def.h
 *
 * Copyright (C) 1997 by
 * Digital Equipment Corporation, Maynard, Massachusetts.
 * All rights reserved.
 *
 * This software is furnished under a license and may be used and copied
 * only  in  accordance  of  the  terms  of  such  license  and with the
 * inclusion of the above copyright notice. This software or  any  other
 * copies thereof may not be provided or otherwise made available to any
 * other person.  No title to and  ownership of the  software is  hereby
 * transferred.
 *
 * The inक्रमmation in this software is  subject to change without notice
 * and  should  not  be  स्थिरrued  as a commiपंचांगent by Digital Equipment
 * Corporation.
 *
 * Digital assumes no responsibility क्रम the use  or  reliability of its
 * software on equipment which is not supplied by Digital.
 *
 *
 * Abstract:	
 *
 *	This file contains header definitions क्रम the SMC37c669 
 *	Super I/O controller. 
 *
 * Author:	
 *
 *	Eric Rयंत्रussen
 *
 * Modअगरication History:
 *
 *	er	28-Jan-1997	Initial Entry
 */

#अगर_अघोषित __SMC37c669_H
#घोषणा __SMC37c669_H

/*
** Macros क्रम handling device IRQs
**
** The mask acts as a flag used in mapping actual ISA IRQs (0 - 15) 
** to device IRQs (A - H).
*/
#घोषणा SMC37c669_DEVICE_IRQ_MASK	0x80000000
#घोषणा SMC37c669_DEVICE_IRQ( __i )	\
	((SMC37c669_DEVICE_IRQ_MASK) | (__i))
#घोषणा SMC37c669_IS_DEVICE_IRQ(__i)	\
	(((__i) & (SMC37c669_DEVICE_IRQ_MASK)) == (SMC37c669_DEVICE_IRQ_MASK))
#घोषणा SMC37c669_RAW_DEVICE_IRQ(__i)	\
	((__i) & ~(SMC37c669_DEVICE_IRQ_MASK))

/*
** Macros क्रम handling device DRQs
**
** The mask acts as a flag used in mapping actual ISA DMA
** channels to device DMA channels (A - C).
*/
#घोषणा SMC37c669_DEVICE_DRQ_MASK	0x80000000
#घोषणा SMC37c669_DEVICE_DRQ(__d)	\
	((SMC37c669_DEVICE_DRQ_MASK) | (__d))
#घोषणा SMC37c669_IS_DEVICE_DRQ(__d)	\
	(((__d) & (SMC37c669_DEVICE_DRQ_MASK)) == (SMC37c669_DEVICE_DRQ_MASK))
#घोषणा SMC37c669_RAW_DEVICE_DRQ(__d)	\
	((__d) & ~(SMC37c669_DEVICE_DRQ_MASK))

#घोषणा SMC37c669_DEVICE_ID	0x3

/*
** SMC37c669 Device Function Definitions
*/
#घोषणा SERIAL_0	0
#घोषणा SERIAL_1	1
#घोषणा PARALLEL_0	2
#घोषणा FLOPPY_0	3
#घोषणा IDE_0		4
#घोषणा NUM_FUNCS	5

/*
** Default Device Function Mappings
*/
#घोषणा COM1_BASE	0x3F8
#घोषणा COM1_IRQ	4
#घोषणा COM2_BASE	0x2F8
#घोषणा COM2_IRQ	3
#घोषणा PARP_BASE	0x3BC
#घोषणा PARP_IRQ	7
#घोषणा PARP_DRQ	3
#घोषणा FDC_BASE	0x3F0
#घोषणा FDC_IRQ		6
#घोषणा FDC_DRQ		2

/*
** Configuration On/Off Key Definitions
*/
#घोषणा SMC37c669_CONFIG_ON_KEY		0x55
#घोषणा SMC37c669_CONFIG_OFF_KEY	0xAA

/*
** SMC 37c669 Device IRQs
*/
#घोषणा SMC37c669_DEVICE_IRQ_A	    ( SMC37c669_DEVICE_IRQ( 0x01 ) )
#घोषणा SMC37c669_DEVICE_IRQ_B	    ( SMC37c669_DEVICE_IRQ( 0x02 ) )
#घोषणा SMC37c669_DEVICE_IRQ_C	    ( SMC37c669_DEVICE_IRQ( 0x03 ) )
#घोषणा SMC37c669_DEVICE_IRQ_D	    ( SMC37c669_DEVICE_IRQ( 0x04 ) )
#घोषणा SMC37c669_DEVICE_IRQ_E	    ( SMC37c669_DEVICE_IRQ( 0x05 ) )
#घोषणा SMC37c669_DEVICE_IRQ_F	    ( SMC37c669_DEVICE_IRQ( 0x06 ) )
/*      SMC37c669_DEVICE_IRQ_G	    *** RESERVED ***/
#घोषणा SMC37c669_DEVICE_IRQ_H	    ( SMC37c669_DEVICE_IRQ( 0x08 ) )

/*
** SMC 37c669 Device DMA Channel Definitions
*/
#घोषणा SMC37c669_DEVICE_DRQ_A		    ( SMC37c669_DEVICE_DRQ( 0x01 ) )
#घोषणा SMC37c669_DEVICE_DRQ_B		    ( SMC37c669_DEVICE_DRQ( 0x02 ) )
#घोषणा SMC37c669_DEVICE_DRQ_C		    ( SMC37c669_DEVICE_DRQ( 0x03 ) )

/*
** Configuration Register Index Definitions
*/
#घोषणा SMC37c669_CR00_INDEX	    0x00
#घोषणा SMC37c669_CR01_INDEX	    0x01
#घोषणा SMC37c669_CR02_INDEX	    0x02
#घोषणा SMC37c669_CR03_INDEX	    0x03
#घोषणा SMC37c669_CR04_INDEX	    0x04
#घोषणा SMC37c669_CR05_INDEX	    0x05
#घोषणा SMC37c669_CR06_INDEX	    0x06
#घोषणा SMC37c669_CR07_INDEX	    0x07
#घोषणा SMC37c669_CR08_INDEX	    0x08
#घोषणा SMC37c669_CR09_INDEX	    0x09
#घोषणा SMC37c669_CR0A_INDEX	    0x0A
#घोषणा SMC37c669_CR0B_INDEX	    0x0B
#घोषणा SMC37c669_CR0C_INDEX	    0x0C
#घोषणा SMC37c669_CR0D_INDEX	    0x0D
#घोषणा SMC37c669_CR0E_INDEX	    0x0E
#घोषणा SMC37c669_CR0F_INDEX	    0x0F
#घोषणा SMC37c669_CR10_INDEX	    0x10
#घोषणा SMC37c669_CR11_INDEX	    0x11
#घोषणा SMC37c669_CR12_INDEX	    0x12
#घोषणा SMC37c669_CR13_INDEX	    0x13
#घोषणा SMC37c669_CR14_INDEX	    0x14
#घोषणा SMC37c669_CR15_INDEX	    0x15
#घोषणा SMC37c669_CR16_INDEX	    0x16
#घोषणा SMC37c669_CR17_INDEX	    0x17
#घोषणा SMC37c669_CR18_INDEX	    0x18
#घोषणा SMC37c669_CR19_INDEX	    0x19
#घोषणा SMC37c669_CR1A_INDEX	    0x1A
#घोषणा SMC37c669_CR1B_INDEX	    0x1B
#घोषणा SMC37c669_CR1C_INDEX	    0x1C
#घोषणा SMC37c669_CR1D_INDEX	    0x1D
#घोषणा SMC37c669_CR1E_INDEX	    0x1E
#घोषणा SMC37c669_CR1F_INDEX	    0x1F
#घोषणा SMC37c669_CR20_INDEX	    0x20
#घोषणा SMC37c669_CR21_INDEX	    0x21
#घोषणा SMC37c669_CR22_INDEX	    0x22
#घोषणा SMC37c669_CR23_INDEX	    0x23
#घोषणा SMC37c669_CR24_INDEX	    0x24
#घोषणा SMC37c669_CR25_INDEX	    0x25
#घोषणा SMC37c669_CR26_INDEX	    0x26
#घोषणा SMC37c669_CR27_INDEX	    0x27
#घोषणा SMC37c669_CR28_INDEX	    0x28
#घोषणा SMC37c669_CR29_INDEX	    0x29

/*
** Configuration Register Alias Definitions
*/
#घोषणा SMC37c669_DEVICE_ID_INDEX		    SMC37c669_CR0D_INDEX
#घोषणा SMC37c669_DEVICE_REVISION_INDEX		    SMC37c669_CR0E_INDEX
#घोषणा SMC37c669_FDC_BASE_ADDRESS_INDEX	    SMC37c669_CR20_INDEX
#घोषणा SMC37c669_IDE_BASE_ADDRESS_INDEX	    SMC37c669_CR21_INDEX
#घोषणा SMC37c669_IDE_ALTERNATE_ADDRESS_INDEX	    SMC37c669_CR22_INDEX
#घोषणा SMC37c669_PARALLEL0_BASE_ADDRESS_INDEX	    SMC37c669_CR23_INDEX
#घोषणा SMC37c669_SERIAL0_BASE_ADDRESS_INDEX	    SMC37c669_CR24_INDEX
#घोषणा SMC37c669_SERIAL1_BASE_ADDRESS_INDEX	    SMC37c669_CR25_INDEX
#घोषणा SMC37c669_PARALLEL_FDC_DRQ_INDEX	    SMC37c669_CR26_INDEX
#घोषणा SMC37c669_PARALLEL_FDC_IRQ_INDEX	    SMC37c669_CR27_INDEX
#घोषणा SMC37c669_SERIAL_IRQ_INDEX		    SMC37c669_CR28_INDEX

/*
** Configuration Register Definitions
**
** The INDEX (ग_लिखो only) and DATA (पढ़ो/ग_लिखो) ports are effective 
** only when the chip is in the Configuration State.
*/
प्रकार काष्ठा _SMC37c669_CONFIG_REGS अणु
    अचिन्हित अक्षर index_port;
    अचिन्हित अक्षर data_port;
पूर्ण SMC37c669_CONFIG_REGS;

/*
** CR00 - शेष value 0x28
**
**  IDE_EN (CR00<1:0>):
**	0x - 30ua pull-ups on nIDEEN, nHDCS0, NHDCS1
**	11 - IRQ_H available as IRQ output,
**	     IRRX2, IRTX2 available as alternate IR pins
**	10 - nIDEEN, nHDCS0, nHDCS1 used to control IDE
**
**  VALID (CR00<7>):
**	A high level on this software controlled bit can
**	be used to indicate that a valid configuration
**	cycle has occurred.  The control software must
**	take care to set this bit at the appropriate बार.
**	Set to zero after घातer up.  This bit has no
**	effect on any other hardware in the chip.
**
*/
प्रकार जोड़ _SMC37c669_CR00 अणु
    अचिन्हित अक्षर as_uअक्षर;
    काष्ठा अणु
    	अचिन्हित ide_en : 2;	    /* See note above		*/
	अचिन्हित reserved1 : 1;	    /* RAZ			*/
	अचिन्हित fdc_pwr : 1;	    /* 1 = supply घातer to FDC  */
	अचिन्हित reserved2 : 3;	    /* Read as 010b		*/
	अचिन्हित valid : 1;	    /* See note above		*/
    पूर्ण	by_field;
पूर्ण SMC37c669_CR00;

/*
** CR01 - शेष value 0x9C
*/
प्रकार जोड़ _SMC37c669_CR01 अणु
    अचिन्हित अक्षर as_uअक्षर;
    काष्ठा अणु
    	अचिन्हित reserved1 : 2;	    /* RAZ			    */
	अचिन्हित ppt_pwr : 1;	    /* 1 = supply घातer to PPT	    */
	अचिन्हित ppt_mode : 1;	    /* 1 = Prपूर्णांकer mode, 0 = EPP    */
	अचिन्हित reserved2 : 1;	    /* Read as 1		    */
	अचिन्हित reserved3 : 2;	    /* RAZ			    */
	अचिन्हित lock_crx: 1;	    /* Lock CR00 - CR18		    */
    पूर्ण	by_field;
पूर्ण SMC37c669_CR01;

/*
** CR02 - शेष value 0x88
*/
प्रकार जोड़ _SMC37c669_CR02 अणु
    अचिन्हित अक्षर as_uअक्षर;
    काष्ठा अणु
    	अचिन्हित reserved1 : 3;	    /* RAZ			    */
	अचिन्हित uart1_pwr : 1;	    /* 1 = supply घातer to UART1    */
	अचिन्हित reserved2 : 3;	    /* RAZ			    */
	अचिन्हित uart2_pwr : 1;	    /* 1 = supply घातer to UART2    */
    पूर्ण	by_field;
पूर्ण SMC37c669_CR02;

/*
** CR03 - शेष value 0x78
**
**  CR03<7>	CR03<2>	    Pin 94
**  -------	-------	    ------
**     0	   X	    DRV2 (input)
**     1	   0	    ADRX
**     1	   1	    IRQ_B
**
**  CR03<6>	CR03<5>	    Op Mode
**  -------	-------	    -------
**     0	   0	    Model 30
**     0	   1	    PS/2
**     1	   0	    Reserved
**     1	   1	    AT Mode
*/
प्रकार जोड़ _SMC37c669_CR03 अणु
    अचिन्हित अक्षर as_uअक्षर;
    काष्ठा अणु
    	अचिन्हित pwrgd_gamecs : 1;  /* 1 = PWRGD, 0 = GAMECS	    */
	अचिन्हित fdc_mode2 : 1;	    /* 1 = Enhanced Mode 2	    */
	अचिन्हित pin94_0 : 1;	    /* See note above		    */
	अचिन्हित reserved1 : 1;	    /* RAZ			    */
	अचिन्हित drvden : 1;	    /* 1 = high, 0 - output	    */
	अचिन्हित op_mode : 2;	    /* See note above		    */
	अचिन्हित pin94_1 : 1;	    /* See note above		    */
    पूर्ण	by_field;
पूर्ण SMC37c669_CR03;

/*
** CR04 - शेष value 0x00
**
**  PP_EXT_MODE:
**	If CR01<PP_MODE> = 0 and PP_EXT_MODE =
**	    00 - Standard and Bidirectional
**	    01 - EPP mode and SPP
**	    10 - ECP mode
**		 In this mode, 2 drives can be supported
**		 directly, 3 or 4 drives must use बाह्यal
**		 4 drive support.  SPP can be selected
**		 through the ECR रेजिस्टर of ECP as mode 000.
**	    11 - ECP mode and EPP mode
**		 In this mode, 2 drives can be supported
**		 directly, 3 or 4 drives must use बाह्यal
**		 4 drive support.  SPP can be selected
**		 through the ECR रेजिस्टर of ECP as mode 000.
**		 In this mode, EPP can be selected through
**		 the ECR रेजिस्टर of ECP as mode 100.
**
**  PP_FDC:
**	00 - Normal
**	01 - PPFD1
**	10 - PPFD2
**	11 - Reserved
**
**  MIDI1:
**	Serial Clock Select: 
**	    A low level on this bit disables MIDI support,
**	    घड़ी = भागide by 13.  A high level on this 
**	    bit enables MIDI support, घड़ी = भागide by 12.
**
**	MIDI operates at 31.25 Kbps which can be derived 
**	from 125 KHz (24 MHz / 12 = 2 MHz, 2 MHz / 16 = 125 KHz)
**
**  ALT_IO:
**	0 - Use pins IRRX, IRTX
**	1 - Use pins IRRX2, IRTX2
**
**	If this bit is set, the IR receive and transmit
**	functions will not be available on pins 25 and 26
**	unless CR00<IDE_EN> = 11.
*/
प्रकार जोड़ _SMC37c669_CR04 अणु
    अचिन्हित अक्षर as_uअक्षर;
    काष्ठा अणु
    	अचिन्हित ppt_ext_mode : 2;  /* See note above		    */
	अचिन्हित ppt_fdc : 2;	    /* See note above		    */
	अचिन्हित midi1 : 1;	    /* See note above		    */
	अचिन्हित midi2 : 1;	    /* See note above		    */
	अचिन्हित epp_type : 1;	    /* 0 = EPP 1.9, 1 = EPP 1.7	    */
	अचिन्हित alt_io : 1;	    /* See note above		    */
    पूर्ण	by_field;
पूर्ण SMC37c669_CR04;

/*
** CR05 - शेष value 0x00
**
**  DEN_SEL:
**	00 - Densel output normal
**	01 - Reserved
**	10 - Densel output 1
**	11 - Densel output 0
**
*/
प्रकार जोड़ _SMC37c669_CR05 अणु
    अचिन्हित अक्षर as_uअक्षर;
    काष्ठा अणु
    	अचिन्हित reserved1 : 2;	    /* RAZ					*/
	अचिन्हित fdc_dma_mode : 1;  /* 0 = burst, 1 = non-burst			*/
	अचिन्हित den_sel : 2;	    /* See note above				*/
	अचिन्हित swap_drv : 1;	    /* Swap the FDC motor selects		*/
	अचिन्हित extx4 : 1;	    /* 0 = 2 drive, 1 = बाह्यal 4 drive decode	*/
	अचिन्हित reserved2 : 1;	    /* RAZ					*/
    पूर्ण	by_field;
पूर्ण SMC37c669_CR05;

/*
** CR06 - शेष value 0xFF
*/
प्रकार जोड़ _SMC37c669_CR06 अणु
    अचिन्हित अक्षर as_uअक्षर;
    काष्ठा अणु
    	अचिन्हित floppy_a : 2;	    /* Type of floppy drive A	    */
	अचिन्हित floppy_b : 2;	    /* Type of floppy drive B	    */
	अचिन्हित floppy_c : 2;	    /* Type of floppy drive C	    */
	अचिन्हित floppy_d : 2;	    /* Type of floppy drive D	    */
    पूर्ण	by_field;
पूर्ण SMC37c669_CR06;

/*
** CR07 - शेष value 0x00
**
**  Auto Power Management CR07<7:4>:
**	0 - Auto Powerकरोwn disabled (शेष)
**	1 - Auto Powerकरोwn enabled
**
**	This bit is reset to the शेष state by POR or
**	a hardware reset.
**
*/
प्रकार जोड़ _SMC37c669_CR07 अणु
    अचिन्हित अक्षर as_uअक्षर;
    काष्ठा अणु
    	अचिन्हित floppy_boot : 2;   /* 0 = A:, 1 = B:		    */
	अचिन्हित reserved1 : 2;	    /* RAZ			    */
	अचिन्हित ppt_en : 1;	    /* See note above		    */
	अचिन्हित uart1_en : 1;	    /* See note above		    */
	अचिन्हित uart2_en : 1;	    /* See note above		    */
	अचिन्हित fdc_en : 1;	    /* See note above		    */
    पूर्ण	by_field;
पूर्ण SMC37c669_CR07;

/*
** CR08 - शेष value 0x00
*/
प्रकार जोड़ _SMC37c669_CR08 अणु
    अचिन्हित अक्षर as_uअक्षर;
    काष्ठा अणु
    	अचिन्हित zero : 4;	    /* 0			    */
	अचिन्हित addrx7_4 : 4;	    /* ADR<7:3> क्रम ADRx decode	    */
    पूर्ण	by_field;
पूर्ण SMC37c669_CR08;

/*
** CR09 - शेष value 0x00
**
**  ADRx_CONFIG:
**	00 - ADRx disabled
**	01 - 1 byte decode A<3:0> = 0000b
**	10 - 8 byte block decode A<3:0> = 0XXXb
**	11 - 16 byte block decode A<3:0> = XXXXb
**
*/
प्रकार जोड़ _SMC37c669_CR09 अणु
    अचिन्हित अक्षर as_uअक्षर;
    काष्ठा अणु
    	अचिन्हित adra8 : 3;	    /* ADR<10:8> क्रम ADRx decode    */
	अचिन्हित reserved1 : 3;
	अचिन्हित adrx_config : 2;   /* See note above		    */
    पूर्ण	by_field;
पूर्ण SMC37c669_CR09;

/*
** CR0A - शेष value 0x00
*/
प्रकार जोड़ _SMC37c669_CR0A अणु
    अचिन्हित अक्षर as_uअक्षर;
    काष्ठा अणु
    	अचिन्हित ecp_fअगरo_threshold : 4;
	अचिन्हित reserved1 : 4;
    पूर्ण	by_field;
पूर्ण SMC37c669_CR0A;

/*
** CR0B - शेष value 0x00
*/
प्रकार जोड़ _SMC37c669_CR0B अणु
    अचिन्हित अक्षर as_uअक्षर;
    काष्ठा अणु
    	अचिन्हित fdd0_drtx : 2;	    /* FDD0 Data Rate Table	    */
	अचिन्हित fdd1_drtx : 2;	    /* FDD1 Data Rate Table	    */
	अचिन्हित fdd2_drtx : 2;	    /* FDD2 Data Rate Table	    */
	अचिन्हित fdd3_drtx : 2;	    /* FDD3 Data Rate Table	    */
    पूर्ण	by_field;
पूर्ण SMC37c669_CR0B;

/*
** CR0C - शेष value 0x00
**
**  UART2_MODE:
**	000 - Standard (शेष)
**	001 - IrDA (HPSIR)
**	010 - Amplitude Shअगरt Keyed IR @500 KHz
**	011 - Reserved
**	1xx - Reserved
**
*/
प्रकार जोड़ _SMC37c669_CR0C अणु
    अचिन्हित अक्षर as_uअक्षर;
    काष्ठा अणु
    	अचिन्हित uart2_rcv_polarity : 1;    /* 1 = invert RX		*/
	अचिन्हित uart2_xmit_polarity : 1;   /* 1 = invert TX		*/
	अचिन्हित uart2_duplex : 1;	    /* 1 = full, 0 = half	*/
	अचिन्हित uart2_mode : 3;	    /* See note above		*/
	अचिन्हित uart1_speed : 1;	    /* 1 = high speed enabled	*/
	अचिन्हित uart2_speed : 1;	    /* 1 = high speed enabled	*/
    पूर्ण	by_field;
पूर्ण SMC37c669_CR0C;

/*
** CR0D - शेष value 0x03
**
**  Device ID Register - पढ़ो only
*/
प्रकार जोड़ _SMC37c669_CR0D अणु
    अचिन्हित अक्षर as_uअक्षर;
    काष्ठा अणु
    	अचिन्हित device_id : 8;	    /* Returns 0x3 in this field    */
    पूर्ण	by_field;
पूर्ण SMC37c669_CR0D;

/*
** CR0E - शेष value 0x02
**
**  Device Revision Register - पढ़ो only
*/
प्रकार जोड़ _SMC37c669_CR0E अणु
    अचिन्हित अक्षर as_uअक्षर;
    काष्ठा अणु
    	अचिन्हित device_rev : 8;    /* Returns 0x2 in this field    */
    पूर्ण	by_field;
पूर्ण SMC37c669_CR0E;

/*
** CR0F - शेष value 0x00
*/
प्रकार जोड़ _SMC37c669_CR0F अणु
    अचिन्हित अक्षर as_uअक्षर;
    काष्ठा अणु
    	अचिन्हित test0 : 1;	    /* Reserved - set to 0	    */
	अचिन्हित test1 : 1;	    /* Reserved - set to 0	    */
	अचिन्हित test2 : 1;	    /* Reserved - set to 0	    */
	अचिन्हित test3 : 1;	    /* Reserved - set t0 0	    */
	अचिन्हित test4 : 1;	    /* Reserved - set to 0	    */
	अचिन्हित test5 : 1;	    /* Reserved - set t0 0	    */
	अचिन्हित test6 : 1;	    /* Reserved - set t0 0	    */
	अचिन्हित test7 : 1;	    /* Reserved - set to 0	    */
    पूर्ण	by_field;
पूर्ण SMC37c669_CR0F;

/*
** CR10 - शेष value 0x00
*/
प्रकार जोड़ _SMC37c669_CR10 अणु
    अचिन्हित अक्षर as_uअक्षर;
    काष्ठा अणु
    	अचिन्हित reserved1 : 3;	     /* RAZ			    */
	अचिन्हित pll_gain : 1;	     /* 1 = 3V, 2 = 5V operation    */
	अचिन्हित pll_stop : 1;	     /* 1 = stop PLLs		    */
	अचिन्हित ace_stop : 1;	     /* 1 = stop UART घड़ीs	    */
	अचिन्हित pll_घड़ी_ctrl : 1; /* 0 = 14.318 MHz, 1 = 24 MHz  */
	अचिन्हित ir_test : 1;	     /* Enable IR test mode	    */
    पूर्ण	by_field;
पूर्ण SMC37c669_CR10;

/*
** CR11 - शेष value 0x00
*/
प्रकार जोड़ _SMC37c669_CR11 अणु
    अचिन्हित अक्षर as_uअक्षर;
    काष्ठा अणु
    	अचिन्हित ir_loopback : 1;   /* Internal IR loop back		    */
	अचिन्हित test_10ms : 1;	    /* Test 10ms स्वतःघातerकरोwn FDC समयout  */
	अचिन्हित reserved1 : 6;	    /* RAZ				    */
    पूर्ण	by_field;
पूर्ण SMC37c669_CR11;

/*
** CR12 - CR1D are reserved रेजिस्टरs
*/

/*
** CR1E - शेष value 0x80
**
**  GAMECS:
**	00 - GAMECS disabled
**	01 - 1 byte decode ADR<3:0> = 0001b
**	10 - 8 byte block decode ADR<3:0> = 0XXXb
**	11 - 16 byte block decode ADR<3:0> = XXXXb
**
*/
प्रकार जोड़ _SMC37c66_CR1E अणु
    अचिन्हित अक्षर as_uअक्षर;
    काष्ठा अणु
    	अचिन्हित gamecs_config: 2;   /* See note above		    */
	अचिन्हित gamecs_addr9_4 : 6; /* GAMECS Addr<9:4>	    */
    पूर्ण	by_field;
पूर्ण SMC37c669_CR1E;

/*
** CR1F - शेष value 0x00
**
**  DT0 DT1 DRVDEN0 DRVDEN1 Drive Type
**  --- --- ------- ------- ----------
**   0   0  DENSEL  DRATE0  4/2/1 MB 3.5"
**                          2/1 MB 5.25"
**                          2/1.6/1 MB 3.5" (3-mode)
**   0   1  DRATE1  DRATE0
**   1   0  nDENSEL DRATE0  PS/2
**   1   1  DRATE0  DRATE1
**
**  Note: DENSEL, DRATE1, and DRATE0 map onto two output
**	  pins - DRVDEN0 and DRVDEN1.
**
*/
प्रकार जोड़ _SMC37c669_CR1F अणु
    अचिन्हित अक्षर as_uअक्षर;
    काष्ठा अणु
    	अचिन्हित fdd0_drive_type : 2;	/* FDD0 drive type	    */
	अचिन्हित fdd1_drive_type : 2;	/* FDD1 drive type	    */
	अचिन्हित fdd2_drive_type : 2;	/* FDD2 drive type	    */
	अचिन्हित fdd3_drive_type : 2;	/* FDD3 drive type	    */
    पूर्ण	by_field;
पूर्ण SMC37c669_CR1F;

/*
** CR20 - शेष value 0x3C
**
**  FDC Base Address Register
**	- To disable this decode set Addr<9:8> = 0
**	- A<10> = 0, A<3:0> = 0XXXb to access.
**
*/
प्रकार जोड़ _SMC37c669_CR20 अणु
    अचिन्हित अक्षर as_uअक्षर;
    काष्ठा अणु
    	अचिन्हित zero : 2;	    /* 0			    */
	अचिन्हित addr9_4 : 6;	    /* FDC Addr<9:4>		    */
    पूर्ण	by_field;
पूर्ण SMC37c669_CR20;

/*
** CR21 - शेष value 0x3C
**
**  IDE Base Address Register
**	- To disable this decode set Addr<9:8> = 0
**	- A<10> = 0, A<3:0> = 0XXXb to access.
**
*/
प्रकार जोड़ _SMC37c669_CR21 अणु
    अचिन्हित अक्षर as_uअक्षर;
    काष्ठा अणु
    	अचिन्हित zero : 2;	    /* 0			    */
	अचिन्हित addr9_4 : 6;	    /* IDE Addr<9:4>		    */
    पूर्ण	by_field;
पूर्ण SMC37c669_CR21;

/*
** CR22 - शेष value 0x3D
**
**  IDE Alternate Status Base Address Register
**	- To disable this decode set Addr<9:8> = 0
**	- A<10> = 0, A<3:0> = 0110b to access.
**
*/
प्रकार जोड़ _SMC37c669_CR22 अणु
    अचिन्हित अक्षर as_uअक्षर;
    काष्ठा अणु
    	अचिन्हित zero : 2;	    /* 0			    */
	अचिन्हित addr9_4 : 6;	    /* IDE Alt Status Addr<9:4>	    */
    पूर्ण	by_field;
पूर्ण SMC37c669_CR22;

/*
** CR23 - शेष value 0x00
**
**  Parallel Port Base Address Register
**	- To disable this decode set Addr<9:8> = 0
**	- A<10> = 0 to access.
**	- If EPP is enabled, A<2:0> = XXXb to access.
**	  If EPP is NOT enabled, A<1:0> = XXb to access
**
*/
प्रकार जोड़ _SMC37c669_CR23 अणु
    अचिन्हित अक्षर as_uअक्षर;
    काष्ठा अणु
	अचिन्हित addr9_2 : 8;	    /* Parallel Port Addr<9:2>	    */
    पूर्ण	by_field;
पूर्ण SMC37c669_CR23;

/*
** CR24 - शेष value 0x00
**
**  UART1 Base Address Register
**	- To disable this decode set Addr<9:8> = 0
**	- A<10> = 0, A<2:0> = XXXb to access.
**
*/
प्रकार जोड़ _SMC37c669_CR24 अणु
    अचिन्हित अक्षर as_uअक्षर;
    काष्ठा अणु
    	अचिन्हित zero : 1;	    /* 0			    */
	अचिन्हित addr9_3 : 7;	    /* UART1 Addr<9:3>		    */
    पूर्ण	by_field;
पूर्ण SMC37c669_CR24;

/*
** CR25 - शेष value 0x00
**
**  UART2 Base Address Register
**	- To disable this decode set Addr<9:8> = 0
**	- A<10> = 0, A<2:0> = XXXb to access.
**
*/
प्रकार जोड़ _SMC37c669_CR25 अणु
    अचिन्हित अक्षर as_uअक्षर;
    काष्ठा अणु
    	अचिन्हित zero : 1;	    /* 0			    */
	अचिन्हित addr9_3 : 7;	    /* UART2 Addr<9:3>		    */
    पूर्ण	by_field;
पूर्ण SMC37c669_CR25;

/*
** CR26 - शेष value 0x00
**
**  Parallel Port / FDC DMA Select Register
**
**  D3 - D0	  DMA
**  D7 - D4	Selected
**  -------	--------
**   0000	 None
**   0001	 DMA_A
**   0010	 DMA_B
**   0011	 DMA_C
**
*/
प्रकार जोड़ _SMC37c669_CR26 अणु
    अचिन्हित अक्षर as_uअक्षर;
    काष्ठा अणु
    	अचिन्हित ppt_drq : 4;	    /* See note above		    */
	अचिन्हित fdc_drq : 4;	    /* See note above		    */
    पूर्ण	by_field;
पूर्ण SMC37c669_CR26;

/*
** CR27 - शेष value 0x00
**
**  Parallel Port / FDC IRQ Select Register
**
**  D3 - D0	  IRQ
**  D7 - D4	Selected
**  -------	--------
**   0000	 None
**   0001	 IRQ_A
**   0010	 IRQ_B
**   0011	 IRQ_C
**   0100	 IRQ_D
**   0101	 IRQ_E
**   0110	 IRQ_F
**   0111	 Reserved
**   1000	 IRQ_H
**
**  Any unselected IRQ REQ is in tristate
**
*/
प्रकार जोड़ _SMC37c669_CR27 अणु
    अचिन्हित अक्षर as_uअक्षर;
    काष्ठा अणु
    	अचिन्हित ppt_irq : 4;	    /* See note above		    */
	अचिन्हित fdc_irq : 4;	    /* See note above		    */
    पूर्ण	by_field;
पूर्ण SMC37c669_CR27;

/*
** CR28 - शेष value 0x00
**
**  UART IRQ Select Register
**
**  D3 - D0	  IRQ
**  D7 - D4	Selected
**  -------	--------
**   0000	 None
**   0001	 IRQ_A
**   0010	 IRQ_B
**   0011	 IRQ_C
**   0100	 IRQ_D
**   0101	 IRQ_E
**   0110	 IRQ_F
**   0111	 Reserved
**   1000	 IRQ_H
**   1111	 share with UART1 (only क्रम UART2)
**
**  Any unselected IRQ REQ is in tristate
**
**  To share an IRQ between UART1 and UART2, set
**  UART1 to use the desired IRQ and set UART2 to
**  0xF to enable sharing mechanism.
**
*/
प्रकार जोड़ _SMC37c669_CR28 अणु
    अचिन्हित अक्षर as_uअक्षर;
    काष्ठा अणु
    	अचिन्हित uart2_irq : 4;	    /* See note above		    */
	अचिन्हित uart1_irq : 4;	    /* See note above		    */
    पूर्ण	by_field;
पूर्ण SMC37c669_CR28;

/*
** CR29 - शेष value 0x00
**
**  IRQIN IRQ Select Register
**
**  D3 - D0	  IRQ
**  D7 - D4	Selected
**  -------	--------
**   0000	 None
**   0001	 IRQ_A
**   0010	 IRQ_B
**   0011	 IRQ_C
**   0100	 IRQ_D
**   0101	 IRQ_E
**   0110	 IRQ_F
**   0111	 Reserved
**   1000	 IRQ_H
**
**  Any unselected IRQ REQ is in tristate
**
*/
प्रकार जोड़ _SMC37c669_CR29 अणु
    अचिन्हित अक्षर as_uअक्षर;
    काष्ठा अणु
    	अचिन्हित irqin_irq : 4;	    /* See note above		    */
	अचिन्हित reserved1 : 4;	    /* RAZ			    */
    पूर्ण	by_field;
पूर्ण SMC37c669_CR29;

/*
** Aliases of Configuration Register क्रमmats (should match
** the set of index aliases).
**
** Note that CR24 and CR25 have the same क्रमmat and are the
** base address रेजिस्टरs क्रम UART1 and UART2.  Because of
** this we only define 1 alias here - क्रम CR24 - as the serial
** base address रेजिस्टर.
**
** Note that CR21 and CR22 have the same क्रमmat and are the
** base address and alternate status address रेजिस्टरs क्रम
** the IDE controller.  Because of this we only define 1 alias
** here - क्रम CR21 - as the IDE address रेजिस्टर.
**
*/
प्रकार SMC37c669_CR0D SMC37c669_DEVICE_ID_REGISTER;
प्रकार SMC37c669_CR0E SMC37c669_DEVICE_REVISION_REGISTER;
प्रकार SMC37c669_CR20 SMC37c669_FDC_BASE_ADDRESS_REGISTER;
प्रकार SMC37c669_CR21 SMC37c669_IDE_ADDRESS_REGISTER;
प्रकार SMC37c669_CR23 SMC37c669_PARALLEL_BASE_ADDRESS_REGISTER;
प्रकार SMC37c669_CR24 SMC37c669_SERIAL_BASE_ADDRESS_REGISTER;
प्रकार SMC37c669_CR26 SMC37c669_PARALLEL_FDC_DRQ_REGISTER;
प्रकार SMC37c669_CR27 SMC37c669_PARALLEL_FDC_IRQ_REGISTER;
प्रकार SMC37c669_CR28 SMC37c669_SERIAL_IRQ_REGISTER;

/*
** ISA/Device IRQ Translation Table Entry Definition
*/
प्रकार काष्ठा _SMC37c669_IRQ_TRANSLATION_ENTRY अणु
    पूर्णांक device_irq;
    पूर्णांक isa_irq;
पूर्ण SMC37c669_IRQ_TRANSLATION_ENTRY;

/*
** ISA/Device DMA Translation Table Entry Definition
*/
प्रकार काष्ठा _SMC37c669_DRQ_TRANSLATION_ENTRY अणु
    पूर्णांक device_drq;
    पूर्णांक isa_drq;
पूर्ण SMC37c669_DRQ_TRANSLATION_ENTRY;

/*
** External Interface Function Prototype Declarations
*/

SMC37c669_CONFIG_REGS *SMC37c669_detect( 
    पूर्णांक
);

अचिन्हित पूर्णांक SMC37c669_enable_device( 
    अचिन्हित पूर्णांक func 
);

अचिन्हित पूर्णांक SMC37c669_disable_device( 
    अचिन्हित पूर्णांक func 
);

अचिन्हित पूर्णांक SMC37c669_configure_device( 
    अचिन्हित पूर्णांक func, 
    पूर्णांक port, 
    पूर्णांक irq, 
    पूर्णांक drq 
);

व्योम SMC37c669_display_device_info( 
    व्योम 
);

#पूर्ण_अगर	/* __SMC37c669_H */

/* file:	smcc669.c
 *
 * Copyright (C) 1997 by
 * Digital Equipment Corporation, Maynard, Massachusetts.
 * All rights reserved.
 *
 * This software is furnished under a license and may be used and copied
 * only  in  accordance  of  the  terms  of  such  license  and with the
 * inclusion of the above copyright notice. This software or  any  other
 * copies thereof may not be provided or otherwise made available to any
 * other person.  No title to and  ownership of the  software is  hereby
 * transferred.
 *
 * The inक्रमmation in this software is  subject to change without notice
 * and  should  not  be  स्थिरrued  as a commiपंचांगent by digital equipment
 * corporation.
 *
 * Digital assumes no responsibility क्रम the use  or  reliability of its
 * software on equipment which is not supplied by digital.
 */

/*
 *++
 *  FACILITY:
 *
 *      Alpha SRM Console Firmware
 *
 *  MODULE DESCRIPTION:
 *
 *	SMC37c669 Super I/O controller configuration routines.
 *
 *  AUTHORS:
 *
 *	Eric Rयंत्रussen
 *
 *  CREATION DATE:
 *  
 *	28-Jan-1997
 *
 *  MODIFICATION HISTORY:
 *	
 *	er	01-May-1997	Fixed poपूर्णांकer conversion errors in 
 *				SMC37c669_get_device_config().
 *      er	28-Jan-1997	Initial version.
 *
 *--
 */

#अगर_अघोषित TRUE
#घोषणा TRUE 1
#पूर्ण_अगर
#अगर_अघोषित FALSE
#घोषणा FALSE 0
#पूर्ण_अगर

#घोषणा wb( _x_, _y_ )	outb( _y_, (अचिन्हित पूर्णांक)((अचिन्हित दीर्घ)_x_) )
#घोषणा rb( _x_ )	inb( (अचिन्हित पूर्णांक)((अचिन्हित दीर्घ)_x_) )

/*
** Local storage क्रम device configuration inक्रमmation.
**
** Since the SMC37c669 करोes not provide an explicit
** mechanism क्रम enabling/disabling inभागidual device 
** functions, other than unmapping the device, local 
** storage क्रम device configuration inक्रमmation is 
** allocated here क्रम use in implementing our own 
** function enable/disable scheme.
*/
अटल काष्ठा DEVICE_CONFIG अणु
    अचिन्हित पूर्णांक port1;
    अचिन्हित पूर्णांक port2;
    पूर्णांक irq;
    पूर्णांक drq;
पूर्ण local_config [NUM_FUNCS];

/*
** List of all possible addresses क्रम the Super I/O chip
*/
अटल अचिन्हित दीर्घ SMC37c669_Addresses[] __initdata =
    अणु
	0x3F0UL,	    /* Primary address	    */
	0x370UL,	    /* Secondary address    */
	0UL		    /* End of list	    */
    पूर्ण;

/*
** Global Poपूर्णांकer to the Super I/O device
*/
अटल SMC37c669_CONFIG_REGS *SMC37c669 __initdata = शून्य;

/*
** IRQ Translation Table
**
** The IRQ translation table is a list of SMC37c669 device 
** and standard ISA IRQs.
**
*/
अटल SMC37c669_IRQ_TRANSLATION_ENTRY *SMC37c669_irq_table __initdata; 

/*
** The following definition is क्रम the शेष IRQ 
** translation table.
*/
अटल SMC37c669_IRQ_TRANSLATION_ENTRY SMC37c669_शेष_irq_table[]
__initdata = 
    अणु 
	अणु SMC37c669_DEVICE_IRQ_A, -1 पूर्ण, 
	अणु SMC37c669_DEVICE_IRQ_B, -1 पूर्ण, 
	अणु SMC37c669_DEVICE_IRQ_C, 7 पूर्ण, 
	अणु SMC37c669_DEVICE_IRQ_D, 6 पूर्ण, 
	अणु SMC37c669_DEVICE_IRQ_E, 4 पूर्ण, 
	अणु SMC37c669_DEVICE_IRQ_F, 3 पूर्ण, 
	अणु SMC37c669_DEVICE_IRQ_H, -1 पूर्ण, 
	अणु -1, -1 पूर्ण /* End of table */
    पूर्ण;

/*
** The following definition is क्रम the MONET (XP1000) IRQ 
** translation table.
*/
अटल SMC37c669_IRQ_TRANSLATION_ENTRY SMC37c669_monet_irq_table[]
__initdata = 
    अणु 
	अणु SMC37c669_DEVICE_IRQ_A, -1 पूर्ण, 
	अणु SMC37c669_DEVICE_IRQ_B, -1 पूर्ण, 
	अणु SMC37c669_DEVICE_IRQ_C, 6 पूर्ण, 
	अणु SMC37c669_DEVICE_IRQ_D, 7 पूर्ण, 
	अणु SMC37c669_DEVICE_IRQ_E, 4 पूर्ण, 
	अणु SMC37c669_DEVICE_IRQ_F, 3 पूर्ण, 
	अणु SMC37c669_DEVICE_IRQ_H, -1 पूर्ण, 
	अणु -1, -1 पूर्ण /* End of table */
    पूर्ण;

अटल SMC37c669_IRQ_TRANSLATION_ENTRY *SMC37c669_irq_tables[] __initdata =
    अणु
	SMC37c669_शेष_irq_table,
	SMC37c669_monet_irq_table
    पूर्ण; 

/*
** DRQ Translation Table
**
** The DRQ translation table is a list of SMC37c669 device and
** ISA DMA channels.
**
*/
अटल SMC37c669_DRQ_TRANSLATION_ENTRY *SMC37c669_drq_table __initdata;

/*
** The following definition is the शेष DRQ
** translation table.
*/
अटल SMC37c669_DRQ_TRANSLATION_ENTRY SMC37c669_शेष_drq_table[]
__initdata = 
    अणु 
	अणु SMC37c669_DEVICE_DRQ_A, 2 पूर्ण, 
	अणु SMC37c669_DEVICE_DRQ_B, 3 पूर्ण, 
	अणु SMC37c669_DEVICE_DRQ_C, -1 पूर्ण, 
	अणु -1, -1 पूर्ण /* End of table */
    पूर्ण;

/*
** Local Function Prototype Declarations
*/

अटल अचिन्हित पूर्णांक SMC37c669_is_device_enabled( 
    अचिन्हित पूर्णांक func 
);

#अगर 0
अटल अचिन्हित पूर्णांक SMC37c669_get_device_config( 
    अचिन्हित पूर्णांक func, 
    पूर्णांक *port, 
    पूर्णांक *irq, 
    पूर्णांक *drq 
);
#पूर्ण_अगर

अटल व्योम SMC37c669_config_mode( 
    अचिन्हित पूर्णांक enable 
);

अटल अचिन्हित अक्षर SMC37c669_पढ़ो_config( 
    अचिन्हित अक्षर index 
);

अटल व्योम SMC37c669_ग_लिखो_config( 
    अचिन्हित अक्षर index, 
    अचिन्हित अक्षर data 
);

अटल व्योम SMC37c669_init_local_config( व्योम );

अटल काष्ठा DEVICE_CONFIG *SMC37c669_get_config(
    अचिन्हित पूर्णांक func
);

अटल पूर्णांक SMC37c669_xlate_irq(
    पूर्णांक irq 
);

अटल पूर्णांक SMC37c669_xlate_drq(
    पूर्णांक drq 
);

अटल  __cacheline_aligned DEFINE_SPINLOCK(smc_lock);

/*
**++
**  FUNCTIONAL DESCRIPTION:
**
**      This function detects the presence of an SMC37c669 Super I/O
**	controller.
**
**  FORMAL PARAMETERS:
**
**	None
**
**  RETURN VALUE:
**
**      Returns a poपूर्णांकer to the device अगर found, otherwise,
**	the शून्य poपूर्णांकer is वापसed.
**
**  SIDE EFFECTS:
**
**      None
**
**--
*/
SMC37c669_CONFIG_REGS * __init SMC37c669_detect( पूर्णांक index )
अणु
    पूर्णांक i;
    SMC37c669_DEVICE_ID_REGISTER id;

    क्रम ( i = 0;  SMC37c669_Addresses[i] != 0;  i++ ) अणु
/*
** Initialize the device poपूर्णांकer even though we करोn't yet know अगर
** the controller is at this address.  The support functions access
** the controller through this device poपूर्णांकer so we need to set it
** even when we are looking ...
*/
    	SMC37c669 = ( SMC37c669_CONFIG_REGS * )SMC37c669_Addresses[i];
/*
** Enter configuration mode
*/
	SMC37c669_config_mode( TRUE );
/*
** Read the device id
*/
	id.as_uअक्षर = SMC37c669_पढ़ो_config( SMC37c669_DEVICE_ID_INDEX );
/*
** Exit configuration mode
*/
	SMC37c669_config_mode( FALSE );
/*
** Does the device id match?  If so, assume we have found an
** SMC37c669 controller at this address.
*/
	अगर ( id.by_field.device_id == SMC37c669_DEVICE_ID ) अणु
/*
** Initialize the IRQ and DRQ translation tables.
*/
    	    SMC37c669_irq_table = SMC37c669_irq_tables[ index ];
	    SMC37c669_drq_table = SMC37c669_शेष_drq_table;
/*
** erfix
**
** If the platक्रमm can't use the IRQ and DRQ शेषs set up in this 
** file, it should call a platक्रमm-specअगरic बाह्यal routine at this 
** poपूर्णांक to reset the IRQ and DRQ translation table poपूर्णांकers to poपूर्णांक 
** at the appropriate tables क्रम the platक्रमm.  If the शेषs are 
** acceptable, then the बाह्यal routine should करो nothing.
*/

/*
** Put the chip back पूर्णांकo configuration mode
*/
	    SMC37c669_config_mode( TRUE );
/*
** Initialize local storage क्रम configuration inक्रमmation
*/
	    SMC37c669_init_local_config( );
/*
** Exit configuration mode
*/
	    SMC37c669_config_mode( FALSE );
/*
** SMC37c669 controller found, अवरोध out of search loop
*/
	    अवरोध;
	पूर्ण
	अन्यथा अणु
/*
** Otherwise, we did not find an SMC37c669 controller at this
** address so set the device poपूर्णांकer to शून्य.
*/
	    SMC37c669 = शून्य;
	पूर्ण
    पूर्ण
    वापस SMC37c669;
पूर्ण


/*
**++
**  FUNCTIONAL DESCRIPTION:
**
**      This function enables an SMC37c669 device function.
**
**  FORMAL PARAMETERS:
**
**      func:
**          Which device function to enable
**
**  RETURN VALUE:
**
**      Returns TRUE is the device function was enabled, otherwise, FALSE
**
**  SIDE EFFECTS:
**
**      अणु@description or none@पूर्ण
**
**  DESIGN:
**
**      Enabling a device function in the SMC37c669 controller involves
**	setting all of its mappings (port, irq, drq ...).  A local 
**	"shadow" copy of the device configuration is kept so we can
**	just set each mapping to what the local copy says.
**
**	This function ALWAYS updates the local shaकरोw configuration of
**	the device function being enabled, even अगर the device is always
**	enabled.  To aव्योम replication of code, functions such as
**	configure_device set up the local copy and then call this 
**	function to the update the real device.
**
**--
*/
अचिन्हित पूर्णांक __init SMC37c669_enable_device ( अचिन्हित पूर्णांक func )
अणु
    अचिन्हित पूर्णांक ret_val = FALSE;
/*
** Put the device पूर्णांकo configuration mode
*/
    SMC37c669_config_mode( TRUE );
    चयन ( func ) अणु
    	हाल SERIAL_0:
	    अणु
	    	SMC37c669_SERIAL_BASE_ADDRESS_REGISTER base_addr;
		SMC37c669_SERIAL_IRQ_REGISTER irq;
/*
** Enable the serial 1 IRQ mapping
*/
	    	irq.as_uअक्षर = 
		    SMC37c669_पढ़ो_config( SMC37c669_SERIAL_IRQ_INDEX );

		irq.by_field.uart1_irq =
		    SMC37c669_RAW_DEVICE_IRQ(
			SMC37c669_xlate_irq( local_config[ func ].irq )
		    );

		SMC37c669_ग_लिखो_config( SMC37c669_SERIAL_IRQ_INDEX, irq.as_uअक्षर );
/*
** Enable the serial 1 port base address mapping
*/
		base_addr.as_uअक्षर = 0;
		base_addr.by_field.addr9_3 = local_config[ func ].port1 >> 3;

		SMC37c669_ग_लिखो_config( 
		    SMC37c669_SERIAL0_BASE_ADDRESS_INDEX,
		    base_addr.as_uअक्षर
		);
		ret_val = TRUE;
		अवरोध;
	    पूर्ण
	हाल SERIAL_1:
	    अणु
	    	SMC37c669_SERIAL_BASE_ADDRESS_REGISTER base_addr;
		SMC37c669_SERIAL_IRQ_REGISTER irq;
/*
** Enable the serial 2 IRQ mapping
*/
	    	irq.as_uअक्षर = 
		    SMC37c669_पढ़ो_config( SMC37c669_SERIAL_IRQ_INDEX );

		irq.by_field.uart2_irq =
		    SMC37c669_RAW_DEVICE_IRQ(
			SMC37c669_xlate_irq( local_config[ func ].irq )
		    );

		SMC37c669_ग_लिखो_config( SMC37c669_SERIAL_IRQ_INDEX, irq.as_uअक्षर );
/*
** Enable the serial 2 port base address mapping
*/
		base_addr.as_uअक्षर = 0;
		base_addr.by_field.addr9_3 = local_config[ func ].port1 >> 3;

		SMC37c669_ग_लिखो_config( 
		    SMC37c669_SERIAL1_BASE_ADDRESS_INDEX,
		    base_addr.as_uअक्षर
		);
		ret_val = TRUE;
		अवरोध;
	    पूर्ण
	हाल PARALLEL_0:
	    अणु
	    	SMC37c669_PARALLEL_BASE_ADDRESS_REGISTER base_addr;
		SMC37c669_PARALLEL_FDC_IRQ_REGISTER irq;
		SMC37c669_PARALLEL_FDC_DRQ_REGISTER drq;
/*
** Enable the parallel port DMA channel mapping
*/
	    	drq.as_uअक्षर =
		    SMC37c669_पढ़ो_config( SMC37c669_PARALLEL_FDC_DRQ_INDEX );

		drq.by_field.ppt_drq = 
		    SMC37c669_RAW_DEVICE_DRQ(
			SMC37c669_xlate_drq( local_config[ func ].drq )
		    );

		SMC37c669_ग_लिखो_config(
		    SMC37c669_PARALLEL_FDC_DRQ_INDEX,
		    drq.as_uअक्षर
		);
/*
** Enable the parallel port IRQ mapping
*/
		irq.as_uअक्षर = 
		    SMC37c669_पढ़ो_config( SMC37c669_PARALLEL_FDC_IRQ_INDEX );

		irq.by_field.ppt_irq =
		    SMC37c669_RAW_DEVICE_IRQ(
			SMC37c669_xlate_irq( local_config[ func ].irq )
		    );

		SMC37c669_ग_लिखो_config( 
		    SMC37c669_PARALLEL_FDC_IRQ_INDEX,
		    irq.as_uअक्षर
		);
/*
** Enable the parallel port base address mapping
*/
		base_addr.as_uअक्षर = 0;
		base_addr.by_field.addr9_2 = local_config[ func ].port1 >> 2;

		SMC37c669_ग_लिखो_config(
		    SMC37c669_PARALLEL0_BASE_ADDRESS_INDEX,
		    base_addr.as_uअक्षर
		);
		ret_val = TRUE;
		अवरोध;
	    पूर्ण
	हाल FLOPPY_0:
	    अणु
	    	SMC37c669_FDC_BASE_ADDRESS_REGISTER base_addr;
		SMC37c669_PARALLEL_FDC_IRQ_REGISTER irq;
		SMC37c669_PARALLEL_FDC_DRQ_REGISTER drq;
/*
** Enable the floppy controller DMA channel mapping
*/
	    	drq.as_uअक्षर =
		    SMC37c669_पढ़ो_config( SMC37c669_PARALLEL_FDC_DRQ_INDEX );
		 
		drq.by_field.fdc_drq =
		    SMC37c669_RAW_DEVICE_DRQ(
			SMC37c669_xlate_drq( local_config[ func ].drq )
		    );
		 
		SMC37c669_ग_लिखो_config( 
		    SMC37c669_PARALLEL_FDC_DRQ_INDEX,
		    drq.as_uअक्षर
		);
/*
** Enable the floppy controller IRQ mapping
*/
		irq.as_uअक्षर =
		    SMC37c669_पढ़ो_config( SMC37c669_PARALLEL_FDC_IRQ_INDEX );
		 
		irq.by_field.fdc_irq =
		    SMC37c669_RAW_DEVICE_IRQ(
			SMC37c669_xlate_irq( local_config[ func ].irq )
		    );
		 
		SMC37c669_ग_लिखो_config(
		    SMC37c669_PARALLEL_FDC_IRQ_INDEX,
		    irq.as_uअक्षर
		);
/*
** Enable the floppy controller base address mapping
*/
		base_addr.as_uअक्षर = 0;
		base_addr.by_field.addr9_4 = local_config[ func ].port1 >> 4;
		 
		SMC37c669_ग_लिखो_config(
		    SMC37c669_FDC_BASE_ADDRESS_INDEX,
		    base_addr.as_uअक्षर
		);
		ret_val = TRUE;
		अवरोध;
	    पूर्ण
	हाल IDE_0:
	    अणु
	    	SMC37c669_IDE_ADDRESS_REGISTER ide_addr;
/*
** Enable the IDE alternate status base address mapping
*/
	    	ide_addr.as_uअक्षर = 0;
		ide_addr.by_field.addr9_4 = local_config[ func ].port2 >> 4;
		 
		SMC37c669_ग_लिखो_config(
		    SMC37c669_IDE_ALTERNATE_ADDRESS_INDEX,
		    ide_addr.as_uअक्षर
		);
/*
** Enable the IDE controller base address mapping
*/
		ide_addr.as_uअक्षर = 0;
		ide_addr.by_field.addr9_4 = local_config[ func ].port1 >> 4;
		 
		SMC37c669_ग_लिखो_config(
		    SMC37c669_IDE_BASE_ADDRESS_INDEX,
		    ide_addr.as_uअक्षर
		);
		ret_val = TRUE;
		अवरोध;
	    पूर्ण
    पूर्ण
/*
** Exit configuration mode and वापस
*/
    SMC37c669_config_mode( FALSE );

    वापस ret_val;
पूर्ण


/*
**++
**  FUNCTIONAL DESCRIPTION:
**
**      This function disables a device function within the
**	SMC37c669 Super I/O controller.
**
**  FORMAL PARAMETERS:
**
**      func:
**          Which function to disable
**
**  RETURN VALUE:
**
**      Return TRUE अगर the device function was disabled, otherwise, FALSE
**
**  SIDE EFFECTS:
**
**      अणु@description or none@पूर्ण
**
**  DESIGN:
**
**      Disabling a function in the SMC37c669 device involves
**	disabling all the function's mappings (port, irq, drq ...).
**	A shaकरोw copy of the device configuration is मुख्यtained
**	in local storage so we won't worry aboving saving the
**	current configuration inक्रमmation.
**
**--
*/
अचिन्हित पूर्णांक __init SMC37c669_disable_device ( अचिन्हित पूर्णांक func )
अणु
    अचिन्हित पूर्णांक ret_val = FALSE;

/*
** Put the device पूर्णांकo configuration mode
*/
    SMC37c669_config_mode( TRUE );
    चयन ( func ) अणु
    	हाल SERIAL_0:
	    अणु
	    	SMC37c669_SERIAL_BASE_ADDRESS_REGISTER base_addr;
		SMC37c669_SERIAL_IRQ_REGISTER irq;
/*
** Disable the serial 1 IRQ mapping
*/
	    	irq.as_uअक्षर = 
		    SMC37c669_पढ़ो_config( SMC37c669_SERIAL_IRQ_INDEX );

		irq.by_field.uart1_irq = 0;

		SMC37c669_ग_लिखो_config( SMC37c669_SERIAL_IRQ_INDEX, irq.as_uअक्षर );
/*
** Disable the serial 1 port base address mapping
*/
		base_addr.as_uअक्षर = 0;
		SMC37c669_ग_लिखो_config( 
		    SMC37c669_SERIAL0_BASE_ADDRESS_INDEX,
		    base_addr.as_uअक्षर
		);
		ret_val = TRUE;
		अवरोध;
	    पूर्ण
	हाल SERIAL_1:
	    अणु
	    	SMC37c669_SERIAL_BASE_ADDRESS_REGISTER base_addr;
		SMC37c669_SERIAL_IRQ_REGISTER irq;
/*
** Disable the serial 2 IRQ mapping
*/
	    	irq.as_uअक्षर = 
		    SMC37c669_पढ़ो_config( SMC37c669_SERIAL_IRQ_INDEX );

		irq.by_field.uart2_irq = 0;

		SMC37c669_ग_लिखो_config( SMC37c669_SERIAL_IRQ_INDEX, irq.as_uअक्षर );
/*
** Disable the serial 2 port base address mapping
*/
		base_addr.as_uअक्षर = 0;

		SMC37c669_ग_लिखो_config( 
		    SMC37c669_SERIAL1_BASE_ADDRESS_INDEX,
		    base_addr.as_uअक्षर
		);
		ret_val = TRUE;
		अवरोध;
	    पूर्ण
	हाल PARALLEL_0:
	    अणु
	    	SMC37c669_PARALLEL_BASE_ADDRESS_REGISTER base_addr;
		SMC37c669_PARALLEL_FDC_IRQ_REGISTER irq;
		SMC37c669_PARALLEL_FDC_DRQ_REGISTER drq;
/*
** Disable the parallel port DMA channel mapping
*/
	    	drq.as_uअक्षर =
		    SMC37c669_पढ़ो_config( SMC37c669_PARALLEL_FDC_DRQ_INDEX );

		drq.by_field.ppt_drq = 0;

		SMC37c669_ग_लिखो_config(
		    SMC37c669_PARALLEL_FDC_DRQ_INDEX,
		    drq.as_uअक्षर
		);
/*
** Disable the parallel port IRQ mapping
*/
		irq.as_uअक्षर = 
		    SMC37c669_पढ़ो_config( SMC37c669_PARALLEL_FDC_IRQ_INDEX );

		irq.by_field.ppt_irq = 0;

		SMC37c669_ग_लिखो_config( 
		    SMC37c669_PARALLEL_FDC_IRQ_INDEX,
		    irq.as_uअक्षर
		);
/*
** Disable the parallel port base address mapping
*/
		base_addr.as_uअक्षर = 0;

		SMC37c669_ग_लिखो_config(
		    SMC37c669_PARALLEL0_BASE_ADDRESS_INDEX,
		    base_addr.as_uअक्षर
		);
		ret_val = TRUE;
		अवरोध;
	    पूर्ण
	हाल FLOPPY_0:
	    अणु
	    	SMC37c669_FDC_BASE_ADDRESS_REGISTER base_addr;
		SMC37c669_PARALLEL_FDC_IRQ_REGISTER irq;
		SMC37c669_PARALLEL_FDC_DRQ_REGISTER drq;
/*
** Disable the floppy controller DMA channel mapping
*/
	    	drq.as_uअक्षर =
		    SMC37c669_पढ़ो_config( SMC37c669_PARALLEL_FDC_DRQ_INDEX );
		 
		drq.by_field.fdc_drq = 0;
		 
		SMC37c669_ग_लिखो_config( 
		    SMC37c669_PARALLEL_FDC_DRQ_INDEX,
		    drq.as_uअक्षर
		);
/*
** Disable the floppy controller IRQ mapping
*/
		irq.as_uअक्षर =
		    SMC37c669_पढ़ो_config( SMC37c669_PARALLEL_FDC_IRQ_INDEX );
		 
		irq.by_field.fdc_irq = 0;
		 
		SMC37c669_ग_लिखो_config(
		    SMC37c669_PARALLEL_FDC_IRQ_INDEX,
		    irq.as_uअक्षर
		);
/*
** Disable the floppy controller base address mapping
*/
		base_addr.as_uअक्षर = 0;
		 
		SMC37c669_ग_लिखो_config(
		    SMC37c669_FDC_BASE_ADDRESS_INDEX,
		    base_addr.as_uअक्षर
		);
		ret_val = TRUE;
		अवरोध;
	    पूर्ण
	हाल IDE_0:
	    अणु
	    	SMC37c669_IDE_ADDRESS_REGISTER ide_addr;
/*
** Disable the IDE alternate status base address mapping
*/
	    	ide_addr.as_uअक्षर = 0;
		 
		SMC37c669_ग_लिखो_config(
		    SMC37c669_IDE_ALTERNATE_ADDRESS_INDEX,
		    ide_addr.as_uअक्षर
		);
/*
** Disable the IDE controller base address mapping
*/
		ide_addr.as_uअक्षर = 0;
		 
		SMC37c669_ग_लिखो_config(
		    SMC37c669_IDE_BASE_ADDRESS_INDEX,
		    ide_addr.as_uअक्षर
		);
		ret_val = TRUE;
		अवरोध;
	    पूर्ण
    पूर्ण
/*
** Exit configuration mode and वापस
*/
    SMC37c669_config_mode( FALSE );

    वापस ret_val;
पूर्ण


/*
**++
**  FUNCTIONAL DESCRIPTION:
**
**      This function configures a device function within the 
**	SMC37c669 Super I/O controller.
**
**  FORMAL PARAMETERS:
**
**      func:
**          Which device function
**       
**      port:
**          I/O port क्रम the function to use
**	 
**      irq:
**          IRQ क्रम the device function to use
**	 
**      drq:
**          DMA channel क्रम the device function to use
**
**  RETURN VALUE:
**
**      Returns TRUE अगर the device function was configured, 
**	otherwise, FALSE.
**
**  SIDE EFFECTS:
**
**      अणु@description or none@पूर्ण
**
**  DESIGN:
**
**	If this function वापसs TRUE, the local shaकरोw copy of
**	the configuration is also updated.  If the device function
**	is currently disabled, only the local shaकरोw copy is 
**	updated and the actual device function will be updated
**	अगर/when it is enabled.
**
**--
*/
अचिन्हित पूर्णांक __init SMC37c669_configure_device (
    अचिन्हित पूर्णांक func,
    पूर्णांक port,
    पूर्णांक irq,
    पूर्णांक drq )
अणु
    काष्ठा DEVICE_CONFIG *cp;

/*
** Check क्रम a valid configuration
*/
    अगर ( ( cp = SMC37c669_get_config ( func ) ) != शून्य ) अणु
/*
** Configuration is valid, update the local shaकरोw copy
*/
    	अगर ( ( drq & ~0xFF ) == 0 ) अणु
	    cp->drq = drq;
	पूर्ण
	अगर ( ( irq & ~0xFF ) == 0 ) अणु
	    cp->irq = irq;
	पूर्ण
	अगर ( ( port & ~0xFFFF ) == 0 ) अणु
	    cp->port1 = port;
	पूर्ण
/*
** If the device function is enabled, update the actual
** device configuration.
*/
	अगर ( SMC37c669_is_device_enabled( func ) ) अणु
	    SMC37c669_enable_device( func );
	पूर्ण
	वापस TRUE;
    पूर्ण
    वापस FALSE;
पूर्ण


/*
**++
**  FUNCTIONAL DESCRIPTION:
**
**      This function determines whether a device function
**	within the SMC37c669 controller is enabled.
**
**  FORMAL PARAMETERS:
**
**      func:
**          Which device function
**
**  RETURN VALUE:
**
**      Returns TRUE अगर the device function is enabled, otherwise, FALSE
**
**  SIDE EFFECTS:
**
**      अणु@description or none@पूर्ण
**
**  DESIGN:
**
**      To check whether a device is enabled we will only look at 
**	the port base address mapping.  According to the SMC37c669
**	specअगरication, all of the port base address mappings are
**	disabled अगर the addr<9:8> (bits <7:6> of the रेजिस्टर) are
**	zero.
**
**--
*/
अटल अचिन्हित पूर्णांक __init SMC37c669_is_device_enabled ( अचिन्हित पूर्णांक func )
अणु
    अचिन्हित अक्षर base_addr = 0;
    अचिन्हित पूर्णांक dev_ok = FALSE;
    अचिन्हित पूर्णांक ret_val = FALSE;
/*
** Enter configuration mode
*/
    SMC37c669_config_mode( TRUE );
     
    चयन ( func ) अणु
    	हाल SERIAL_0:
	    base_addr =
		SMC37c669_पढ़ो_config( SMC37c669_SERIAL0_BASE_ADDRESS_INDEX );
	    dev_ok = TRUE;
	    अवरोध;
	हाल SERIAL_1:
	    base_addr =
		SMC37c669_पढ़ो_config( SMC37c669_SERIAL1_BASE_ADDRESS_INDEX );
	    dev_ok = TRUE;
	    अवरोध;
	हाल PARALLEL_0:
	    base_addr =
		SMC37c669_पढ़ो_config( SMC37c669_PARALLEL0_BASE_ADDRESS_INDEX );
	    dev_ok = TRUE;
	    अवरोध;
	हाल FLOPPY_0:
	    base_addr =
		SMC37c669_पढ़ो_config( SMC37c669_FDC_BASE_ADDRESS_INDEX );
	    dev_ok = TRUE;
	    अवरोध;
	हाल IDE_0:
	    base_addr =
		SMC37c669_पढ़ो_config( SMC37c669_IDE_BASE_ADDRESS_INDEX );
	    dev_ok = TRUE;
	    अवरोध;
    पूर्ण
/*
** If we have a valid device, check base_addr<7:6> to see अगर the
** device is enabled (mapped).
*/
    अगर ( ( dev_ok ) && ( ( base_addr & 0xC0 ) != 0 ) ) अणु
/*
** The mapping is not disabled, so assume that the function is 
** enabled.
*/
    	ret_val = TRUE;
    पूर्ण
/*
** Exit configuration mode 
*/
    SMC37c669_config_mode( FALSE );

    वापस ret_val;
पूर्ण


#अगर 0
/*
**++
**  FUNCTIONAL DESCRIPTION:
**
**      This function retrieves the configuration inक्रमmation of a 
**	device function within the SMC37c699 Super I/O controller.
**
**  FORMAL PARAMETERS:
**
**      func:
**          Which device function
**       
**      port:
**          I/O port वापसed
**	 
**      irq:
**          IRQ वापसed
**	 
**      drq:
**          DMA channel वापसed
**
**  RETURN VALUE:
**
**      Returns TRUE अगर the device configuration was successfully
**	retrieved, otherwise, FALSE.
**
**  SIDE EFFECTS:
**
**      The data poपूर्णांकed to by the port, irq, and drq parameters
**	my be modअगरied even अगर the configuration is not successfully
**	retrieved.
**
**  DESIGN:
**
**      The device configuration is fetched from the local shaकरोw
**	copy.  Any unused parameters will be set to -1.  Any
**	parameter which is not desired can specअगरy the शून्य
**	poपूर्णांकer.
**
**--
*/
अटल अचिन्हित पूर्णांक __init SMC37c669_get_device_config (
    अचिन्हित पूर्णांक func,
    पूर्णांक *port,
    पूर्णांक *irq,
    पूर्णांक *drq )
अणु
    काष्ठा DEVICE_CONFIG *cp;
    अचिन्हित पूर्णांक ret_val = FALSE;
/*
** Check क्रम a valid device configuration
*/
    अगर ( ( cp = SMC37c669_get_config( func ) ) != शून्य ) अणु
    	अगर ( drq != शून्य ) अणु
	    *drq = cp->drq;
	    ret_val = TRUE;
	पूर्ण
	अगर ( irq != शून्य ) अणु
	    *irq = cp->irq;
	    ret_val = TRUE;
	पूर्ण
	अगर ( port != शून्य ) अणु
	    *port = cp->port1;
	    ret_val = TRUE;
	पूर्ण
    पूर्ण
    वापस ret_val;
पूर्ण
#पूर्ण_अगर


/*
**++
**  FUNCTIONAL DESCRIPTION:
**
**      This function displays the current state of the SMC37c699
**	Super I/O controller's device functions.
**
**  FORMAL PARAMETERS:
**
**      None
**
**  RETURN VALUE:
**
**      None
**
**  SIDE EFFECTS:
**
**      None
**
**--
*/
व्योम __init SMC37c669_display_device_info ( व्योम )
अणु
    अगर ( SMC37c669_is_device_enabled( SERIAL_0 ) ) अणु
    	prपूर्णांकk( "  Serial 0:    Enabled [ Port 0x%x, IRQ %d ]\n",
		 local_config[ SERIAL_0 ].port1,
		 local_config[ SERIAL_0 ].irq
	);
    पूर्ण
    अन्यथा अणु
    	prपूर्णांकk( "  Serial 0:    Disabled\n" );
    पूर्ण

    अगर ( SMC37c669_is_device_enabled( SERIAL_1 ) ) अणु
    	prपूर्णांकk( "  Serial 1:    Enabled [ Port 0x%x, IRQ %d ]\n",
		 local_config[ SERIAL_1 ].port1,
		 local_config[ SERIAL_1 ].irq
	);
    पूर्ण
    अन्यथा अणु
    	prपूर्णांकk( "  Serial 1:    Disabled\n" );
    पूर्ण

    अगर ( SMC37c669_is_device_enabled( PARALLEL_0 ) ) अणु
    	prपूर्णांकk( "  Parallel:    Enabled [ Port 0x%x, IRQ %d/%d ]\n",
		 local_config[ PARALLEL_0 ].port1,
		 local_config[ PARALLEL_0 ].irq,
		 local_config[ PARALLEL_0 ].drq
	);
    पूर्ण
    अन्यथा अणु
    	prपूर्णांकk( "  Parallel:    Disabled\n" );
    पूर्ण

    अगर ( SMC37c669_is_device_enabled( FLOPPY_0 ) ) अणु
    	prपूर्णांकk( "  Floppy Ctrl: Enabled [ Port 0x%x, IRQ %d/%d ]\n",
		 local_config[ FLOPPY_0 ].port1,
		 local_config[ FLOPPY_0 ].irq,
		 local_config[ FLOPPY_0 ].drq
	);
    पूर्ण
    अन्यथा अणु
    	prपूर्णांकk( "  Floppy Ctrl: Disabled\n" );
    पूर्ण

    अगर ( SMC37c669_is_device_enabled( IDE_0 ) ) अणु
    	prपूर्णांकk( "  IDE 0:       Enabled [ Port 0x%x, IRQ %d ]\n",
		 local_config[ IDE_0 ].port1,
		 local_config[ IDE_0 ].irq
	);
    पूर्ण
    अन्यथा अणु
    	prपूर्णांकk( "  IDE 0:       Disabled\n" );
    पूर्ण
पूर्ण


/*
**++
**  FUNCTIONAL DESCRIPTION:
**
**      This function माला_दो the SMC37c669 Super I/O controller पूर्णांकo,
**	and takes it out of, configuration mode.
**
**  FORMAL PARAMETERS:
**
**      enable:
**          TRUE to enter configuration mode, FALSE to निकास.
**
**  RETURN VALUE:
**
**      None
**
**  SIDE EFFECTS:
**
**      The SMC37c669 controller may be left in configuration mode.
**
**--
*/
अटल व्योम __init SMC37c669_config_mode( 
    अचिन्हित पूर्णांक enable )
अणु
    अगर ( enable ) अणु
/*
** To enter configuration mode, two ग_लिखोs in succession to the index
** port are required.  If a ग_लिखो to another address or port occurs
** between these two ग_लिखोs, the chip करोes not enter configuration
** mode.  Thereक्रमe, a spinlock is placed around the two ग_लिखोs to 
** guarantee that they complete unपूर्णांकerrupted.
*/
	spin_lock(&smc_lock);
    	wb( &SMC37c669->index_port, SMC37c669_CONFIG_ON_KEY );
    	wb( &SMC37c669->index_port, SMC37c669_CONFIG_ON_KEY );
	spin_unlock(&smc_lock);
    पूर्ण
    अन्यथा अणु
    	wb( &SMC37c669->index_port, SMC37c669_CONFIG_OFF_KEY );
    पूर्ण
पूर्ण

/*
**++
**  FUNCTIONAL DESCRIPTION:
**
**      This function पढ़ोs an SMC37c669 Super I/O controller
**	configuration रेजिस्टर.  This function assumes that the
**	device is alपढ़ोy in configuration mode.
**
**  FORMAL PARAMETERS:
**
**      index:
**          Index value of configuration रेजिस्टर to पढ़ो
**
**  RETURN VALUE:
**
**      Data पढ़ो from configuration रेजिस्टर
**
**  SIDE EFFECTS:
**
**      None
**
**--
*/
अटल अचिन्हित अक्षर __init SMC37c669_पढ़ो_config( 
    अचिन्हित अक्षर index )
अणु
	wb(&SMC37c669->index_port, index);
	वापस rb(&SMC37c669->data_port);
पूर्ण

/*
**++
**  FUNCTIONAL DESCRIPTION:
**
**      This function ग_लिखोs an SMC37c669 Super I/O controller
**	configuration रेजिस्टर.  This function assumes that the
**	device is alपढ़ोy in configuration mode.
**
**  FORMAL PARAMETERS:
**
**      index:
**          Index of configuration रेजिस्टर to ग_लिखो
**       
**      data:
**          Data to be written
**
**  RETURN VALUE:
**
**      None
**
**  SIDE EFFECTS:
**
**      None
**
**--
*/
अटल व्योम __init SMC37c669_ग_लिखो_config( 
    अचिन्हित अक्षर index, 
    अचिन्हित अक्षर data )
अणु
    wb( &SMC37c669->index_port, index );
    wb( &SMC37c669->data_port, data );
पूर्ण


/*
**++
**  FUNCTIONAL DESCRIPTION:
**
**      This function initializes the local device
**	configuration storage.  This function assumes
**	that the device is alपढ़ोy in configuration
**	mode.
**
**  FORMAL PARAMETERS:
**
**      None
**
**  RETURN VALUE:
**
**      None
**
**  SIDE EFFECTS:
**
**      Local storage क्रम device configuration inक्रमmation
**	is initialized.
**
**--
*/
अटल व्योम __init SMC37c669_init_local_config ( व्योम )
अणु
    SMC37c669_SERIAL_BASE_ADDRESS_REGISTER uart_base;
    SMC37c669_SERIAL_IRQ_REGISTER uart_irqs;
    SMC37c669_PARALLEL_BASE_ADDRESS_REGISTER ppt_base;
    SMC37c669_PARALLEL_FDC_IRQ_REGISTER ppt_fdc_irqs;
    SMC37c669_PARALLEL_FDC_DRQ_REGISTER ppt_fdc_drqs;
    SMC37c669_FDC_BASE_ADDRESS_REGISTER fdc_base;
    SMC37c669_IDE_ADDRESS_REGISTER ide_base;
    SMC37c669_IDE_ADDRESS_REGISTER ide_alt;

/*
** Get serial port 1 base address 
*/
    uart_base.as_uअक्षर = 
	SMC37c669_पढ़ो_config( SMC37c669_SERIAL0_BASE_ADDRESS_INDEX );
/*
** Get IRQs क्रम serial ports 1 & 2
*/
    uart_irqs.as_uअक्षर = 
	SMC37c669_पढ़ो_config( SMC37c669_SERIAL_IRQ_INDEX );
/*
** Store local configuration inक्रमmation क्रम serial port 1
*/
    local_config[SERIAL_0].port1 = uart_base.by_field.addr9_3 << 3;
    local_config[SERIAL_0].irq = 
	SMC37c669_xlate_irq( 
	    SMC37c669_DEVICE_IRQ( uart_irqs.by_field.uart1_irq ) 
	);
/*
** Get serial port 2 base address
*/
    uart_base.as_uअक्षर = 
	SMC37c669_पढ़ो_config( SMC37c669_SERIAL1_BASE_ADDRESS_INDEX );
/*
** Store local configuration inक्रमmation क्रम serial port 2
*/
    local_config[SERIAL_1].port1 = uart_base.by_field.addr9_3 << 3;
    local_config[SERIAL_1].irq = 
	SMC37c669_xlate_irq( 
	    SMC37c669_DEVICE_IRQ( uart_irqs.by_field.uart2_irq ) 
	);
/*
** Get parallel port base address
*/
    ppt_base.as_uअक्षर =
	SMC37c669_पढ़ो_config( SMC37c669_PARALLEL0_BASE_ADDRESS_INDEX );
/*
** Get IRQs क्रम parallel port and floppy controller
*/
    ppt_fdc_irqs.as_uअक्षर =
	SMC37c669_पढ़ो_config( SMC37c669_PARALLEL_FDC_IRQ_INDEX );
/*
** Get DRQs क्रम parallel port and floppy controller
*/
    ppt_fdc_drqs.as_uअक्षर =
	SMC37c669_पढ़ो_config( SMC37c669_PARALLEL_FDC_DRQ_INDEX );
/*
** Store local configuration inक्रमmation क्रम parallel port
*/
    local_config[PARALLEL_0].port1 = ppt_base.by_field.addr9_2 << 2;
    local_config[PARALLEL_0].irq =
	SMC37c669_xlate_irq(
	    SMC37c669_DEVICE_IRQ( ppt_fdc_irqs.by_field.ppt_irq )
	);
    local_config[PARALLEL_0].drq =
	SMC37c669_xlate_drq(
	    SMC37c669_DEVICE_DRQ( ppt_fdc_drqs.by_field.ppt_drq )
	);
/*
** Get floppy controller base address
*/
    fdc_base.as_uअक्षर = 
	SMC37c669_पढ़ो_config( SMC37c669_FDC_BASE_ADDRESS_INDEX );
/*
** Store local configuration inक्रमmation क्रम floppy controller
*/
    local_config[FLOPPY_0].port1 = fdc_base.by_field.addr9_4 << 4;
    local_config[FLOPPY_0].irq =
	SMC37c669_xlate_irq(
	    SMC37c669_DEVICE_IRQ( ppt_fdc_irqs.by_field.fdc_irq )
	);
    local_config[FLOPPY_0].drq =
	SMC37c669_xlate_drq(
	    SMC37c669_DEVICE_DRQ( ppt_fdc_drqs.by_field.fdc_drq )
	);
/*
** Get IDE controller base address
*/
    ide_base.as_uअक्षर =
	SMC37c669_पढ़ो_config( SMC37c669_IDE_BASE_ADDRESS_INDEX );
/*
** Get IDE alternate status base address
*/
    ide_alt.as_uअक्षर =
	SMC37c669_पढ़ो_config( SMC37c669_IDE_ALTERNATE_ADDRESS_INDEX );
/*
** Store local configuration inक्रमmation क्रम IDE controller
*/
    local_config[IDE_0].port1 = ide_base.by_field.addr9_4 << 4;
    local_config[IDE_0].port2 = ide_alt.by_field.addr9_4 << 4;
    local_config[IDE_0].irq = 14;
पूर्ण


/*
**++
**  FUNCTIONAL DESCRIPTION:
**
**      This function वापसs a poपूर्णांकer to the local shaकरोw
**	configuration of the requested device function.
**
**  FORMAL PARAMETERS:
**
**      func:
**          Which device function
**
**  RETURN VALUE:
**
**      Returns a poपूर्णांकer to the DEVICE_CONFIG काष्ठाure क्रम the
**	requested function, otherwise, शून्य.
**
**  SIDE EFFECTS:
**
**      अणु@description or none@पूर्ण
**
**--
*/
अटल काष्ठा DEVICE_CONFIG * __init SMC37c669_get_config( अचिन्हित पूर्णांक func )
अणु
    काष्ठा DEVICE_CONFIG *cp = शून्य;

    चयन ( func ) अणु
    	हाल SERIAL_0:
	    cp = &local_config[ SERIAL_0 ];
	    अवरोध;
	हाल SERIAL_1:
	    cp = &local_config[ SERIAL_1 ];
	    अवरोध;
	हाल PARALLEL_0:
	    cp = &local_config[ PARALLEL_0 ];
	    अवरोध;
	हाल FLOPPY_0:
	    cp = &local_config[ FLOPPY_0 ];
	    अवरोध;
	हाल IDE_0:
	    cp = &local_config[ IDE_0 ];
	    अवरोध;
    पूर्ण
    वापस cp;
पूर्ण

/*
**++
**  FUNCTIONAL DESCRIPTION:
**
**      This function translates IRQs back and क्रमth between ISA
**	IRQs and SMC37c669 device IRQs.
**
**  FORMAL PARAMETERS:
**
**      irq:
**          The IRQ to translate
**
**  RETURN VALUE:
**
**      Returns the translated IRQ, otherwise, वापसs -1.
**
**  SIDE EFFECTS:
**
**      अणु@description or none@पूर्ण
**
**--
*/
अटल पूर्णांक __init SMC37c669_xlate_irq ( पूर्णांक irq )
अणु
    पूर्णांक i, translated_irq = -1;

    अगर ( SMC37c669_IS_DEVICE_IRQ( irq ) ) अणु
/*
** We are translating a device IRQ to an ISA IRQ
*/
    	क्रम ( i = 0; ( SMC37c669_irq_table[i].device_irq != -1 ) || ( SMC37c669_irq_table[i].isa_irq != -1 ); i++ ) अणु
	    अगर ( irq == SMC37c669_irq_table[i].device_irq ) अणु
	    	translated_irq = SMC37c669_irq_table[i].isa_irq;
		अवरोध;
	    पूर्ण
	पूर्ण
    पूर्ण
    अन्यथा अणु
/*
** We are translating an ISA IRQ to a device IRQ
*/
    	क्रम ( i = 0; ( SMC37c669_irq_table[i].isa_irq != -1 ) || ( SMC37c669_irq_table[i].device_irq != -1 ); i++ ) अणु
	    अगर ( irq == SMC37c669_irq_table[i].isa_irq ) अणु
	    	translated_irq = SMC37c669_irq_table[i].device_irq;
		अवरोध;
	    पूर्ण
	पूर्ण
    पूर्ण
    वापस translated_irq;
पूर्ण


/*
**++
**  FUNCTIONAL DESCRIPTION:
**
**      This function translates DMA channels back and क्रमth between
**	ISA DMA channels and SMC37c669 device DMA channels.
**
**  FORMAL PARAMETERS:
**
**      drq:
**          The DMA channel to translate
**
**  RETURN VALUE:
**
**      Returns the translated DMA channel, otherwise, वापसs -1
**
**  SIDE EFFECTS:
**
**      अणु@description or none@पूर्ण
**
**--
*/
अटल पूर्णांक __init SMC37c669_xlate_drq ( पूर्णांक drq )
अणु
    पूर्णांक i, translated_drq = -1;

    अगर ( SMC37c669_IS_DEVICE_DRQ( drq ) ) अणु
/*
** We are translating a device DMA channel to an ISA DMA channel
*/
    	क्रम ( i = 0; ( SMC37c669_drq_table[i].device_drq != -1 ) || ( SMC37c669_drq_table[i].isa_drq != -1 ); i++ ) अणु
	    अगर ( drq == SMC37c669_drq_table[i].device_drq ) अणु
	    	translated_drq = SMC37c669_drq_table[i].isa_drq;
		अवरोध;
	    पूर्ण
	पूर्ण
    पूर्ण
    अन्यथा अणु
/*
** We are translating an ISA DMA channel to a device DMA channel
*/
    	क्रम ( i = 0; ( SMC37c669_drq_table[i].isa_drq != -1 ) || ( SMC37c669_drq_table[i].device_drq != -1 ); i++ ) अणु
	    अगर ( drq == SMC37c669_drq_table[i].isa_drq ) अणु
	    	translated_drq = SMC37c669_drq_table[i].device_drq;
		अवरोध;
	    पूर्ण
	पूर्ण
    पूर्ण
    वापस translated_drq;
पूर्ण

#अगर 0
पूर्णांक __init smcc669_init ( व्योम )
अणु
    काष्ठा INODE *ip;

    allocinode( smc_ddb.name, 1, &ip );
    ip->dva = &smc_ddb;
    ip->attr = ATTR$M_WRITE | ATTR$M_READ;
    ip->len[0] = 0x30;
    ip->misc = 0;
    INODE_UNLOCK( ip );

    वापस msg_success;
पूर्ण

पूर्णांक __init smcc669_खोलो( काष्ठा खाता *fp, अक्षर *info, अक्षर *next, अक्षर *mode )
अणु
    काष्ठा INODE *ip;
/*
** Allow multiple पढ़ोers but only one ग_लिखोr.  ip->misc keeps track
** of the number of ग_लिखोrs
*/
    ip = fp->ip;
    INODE_LOCK( ip );
    अगर ( fp->mode & ATTR$M_WRITE ) अणु
	अगर ( ip->misc ) अणु
	    INODE_UNLOCK( ip );
	    वापस msg_failure;	    /* too many ग_लिखोrs */
	पूर्ण
	ip->misc++;
    पूर्ण
/*
** Treat the inक्रमmation field as a byte offset
*/
    *fp->offset = xtoi( info );
    INODE_UNLOCK( ip );

    वापस msg_success;
पूर्ण

पूर्णांक __init smcc669_बंद( काष्ठा खाता *fp )
अणु
    काष्ठा INODE *ip;

    ip = fp->ip;
    अगर ( fp->mode & ATTR$M_WRITE ) अणु
	INODE_LOCK( ip );
	ip->misc--;
	INODE_UNLOCK( ip );
    पूर्ण
    वापस msg_success;
पूर्ण

पूर्णांक __init smcc669_पढ़ो( काष्ठा खाता *fp, पूर्णांक size, पूर्णांक number, अचिन्हित अक्षर *buf )
अणु
    पूर्णांक i;
    पूर्णांक length;
    पूर्णांक nbytes;
    काष्ठा INODE *ip;

/*
** Always access a byte at a समय
*/
    ip = fp->ip;
    length = size * number;
    nbytes = 0;

    SMC37c669_config_mode( TRUE );
    क्रम ( i = 0; i < length; i++ ) अणु
	अगर ( !inrange( *fp->offset, 0, ip->len[0] ) ) 
	    अवरोध;
	*buf++ = SMC37c669_पढ़ो_config( *fp->offset );
	*fp->offset += 1;
	nbytes++;
    पूर्ण
    SMC37c669_config_mode( FALSE );
    वापस nbytes;
पूर्ण

पूर्णांक __init smcc669_ग_लिखो( काष्ठा खाता *fp, पूर्णांक size, पूर्णांक number, अचिन्हित अक्षर *buf )
अणु
    पूर्णांक i;
    पूर्णांक length;
    पूर्णांक nbytes;
    काष्ठा INODE *ip;
/*
** Always access a byte at a समय
*/
    ip = fp->ip;
    length = size * number;
    nbytes = 0;

    SMC37c669_config_mode( TRUE );
    क्रम ( i = 0; i < length; i++ ) अणु
	अगर ( !inrange( *fp->offset, 0, ip->len[0] ) ) 
	    अवरोध;
	SMC37c669_ग_लिखो_config( *fp->offset, *buf );
	*fp->offset += 1;
	buf++;
	nbytes++;
    पूर्ण
    SMC37c669_config_mode( FALSE );
    वापस nbytes;
पूर्ण
#पूर्ण_अगर

व्योम __init
SMC37c669_dump_रेजिस्टरs(व्योम)
अणु
  पूर्णांक i;
  क्रम (i = 0; i <= 0x29; i++)
    prपूर्णांकk("-- CR%02x : %02x\n", i, SMC37c669_पढ़ो_config(i));
पूर्ण
/*+
 * ============================================================================
 * = SMC_init - SMC37c669 Super I/O controller initialization                 =
 * ============================================================================
 *
 * OVERVIEW:
 *
 *      This routine configures and enables device functions on the
 *      SMC37c669 Super I/O controller.
 *
 * FORM OF CALL:
 *
 *      SMC_init( );
 *
 * RETURNS:
 *
 *      Nothing
 *
 * ARGUMENTS:
 *
 *      None
 *
 * SIDE EFFECTS:
 *
 *      None
 *
 */
व्योम __init SMC669_Init ( पूर्णांक index )
अणु
    SMC37c669_CONFIG_REGS *SMC_base;
    अचिन्हित दीर्घ flags;

    local_irq_save(flags);
    अगर ( ( SMC_base = SMC37c669_detect( index ) ) != शून्य ) अणु
#अगर SMC_DEBUG
	SMC37c669_config_mode( TRUE );
	SMC37c669_dump_रेजिस्टरs( );
	SMC37c669_config_mode( FALSE );
        SMC37c669_display_device_info( );
#पूर्ण_अगर
        SMC37c669_disable_device( SERIAL_0 );
        SMC37c669_configure_device(
            SERIAL_0,
            COM1_BASE,
            COM1_IRQ,
            -1
        );
        SMC37c669_enable_device( SERIAL_0 );

        SMC37c669_disable_device( SERIAL_1 );
        SMC37c669_configure_device(
            SERIAL_1,
            COM2_BASE,
            COM2_IRQ,
            -1
        );
        SMC37c669_enable_device( SERIAL_1 );

        SMC37c669_disable_device( PARALLEL_0 );
        SMC37c669_configure_device(
            PARALLEL_0,
            PARP_BASE,
            PARP_IRQ,
            PARP_DRQ
        );
        SMC37c669_enable_device( PARALLEL_0 );

        SMC37c669_disable_device( FLOPPY_0 );
        SMC37c669_configure_device(
            FLOPPY_0,
            FDC_BASE,
            FDC_IRQ,
            FDC_DRQ
        );
        SMC37c669_enable_device( FLOPPY_0 );
          
	/* Wake up someबार क्रमgotten floppy, especially on DP264. */
	outb(0xc, 0x3f2);

        SMC37c669_disable_device( IDE_0 );

#अगर SMC_DEBUG
	SMC37c669_config_mode( TRUE );
	SMC37c669_dump_रेजिस्टरs( );
	SMC37c669_config_mode( FALSE );
        SMC37c669_display_device_info( );
#पूर्ण_अगर
	local_irq_restore(flags);
        prपूर्णांकk( "SMC37c669 Super I/O Controller found @ 0x%p\n",
		SMC_base );
    पूर्ण
    अन्यथा अणु
	local_irq_restore(flags);
#अगर SMC_DEBUG
        prपूर्णांकk( "No SMC37c669 Super I/O Controller found\n" );
#पूर्ण_अगर
    पूर्ण
पूर्ण
