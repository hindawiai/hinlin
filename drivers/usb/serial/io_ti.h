<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*****************************************************************************
 *
 *	Copyright (C) 1997-2002 Inside Out Networks, Inc.
 *
 *	Feb-16-2001	DMI	Added I2C काष्ठाure definitions
 *	May-29-2002	gkh	Ported to Linux
 *
 *
 ******************************************************************************/

#अगर_अघोषित _IO_TI_H_
#घोषणा _IO_TI_H_

/* Address Space */
#घोषणा DTK_ADDR_SPACE_XDATA		0x03	/* Addr is placed in XDATA space */
#घोषणा DTK_ADDR_SPACE_I2C_TYPE_II	0x82	/* Addr is placed in I2C area */
#घोषणा DTK_ADDR_SPACE_I2C_TYPE_III	0x83	/* Addr is placed in I2C area */

/* UART Defines */
#घोषणा UMPMEM_BASE_UART1		0xFFA0	/* UMP UART1 base address */
#घोषणा UMPMEM_BASE_UART2		0xFFB0	/* UMP UART2 base address */
#घोषणा UMPMEM_OFFS_UART_LSR		0x05	/* UMP UART LSR रेजिस्टर offset */

/* Bits per अक्षरacter */
#घोषणा UMP_UART_CHAR5BITS		0x00
#घोषणा UMP_UART_CHAR6BITS		0x01
#घोषणा UMP_UART_CHAR7BITS		0x02
#घोषणा UMP_UART_CHAR8BITS		0x03

/* Parity */
#घोषणा UMP_UART_NOPARITY		0x00
#घोषणा UMP_UART_ODDPARITY		0x01
#घोषणा UMP_UART_EVENPARITY		0x02
#घोषणा UMP_UART_MARKPARITY		0x03
#घोषणा UMP_UART_SPACEPARITY		0x04

/* Stop bits */
#घोषणा UMP_UART_STOPBIT1		0x00
#घोषणा UMP_UART_STOPBIT15		0x01
#घोषणा UMP_UART_STOPBIT2		0x02

/* Line status रेजिस्टर masks */
#घोषणा UMP_UART_LSR_OV_MASK		0x01
#घोषणा UMP_UART_LSR_PE_MASK		0x02
#घोषणा UMP_UART_LSR_FE_MASK		0x04
#घोषणा UMP_UART_LSR_BR_MASK		0x08
#घोषणा UMP_UART_LSR_ER_MASK		0x0F
#घोषणा UMP_UART_LSR_RX_MASK		0x10
#घोषणा UMP_UART_LSR_TX_MASK		0x20

#घोषणा UMP_UART_LSR_DATA_MASK		(LSR_PAR_ERR | LSR_FRM_ERR | LSR_BREAK)

/* Port Settings Constants) */
#घोषणा UMP_MASK_UART_FLAGS_RTS_FLOW		0x0001
#घोषणा UMP_MASK_UART_FLAGS_RTS_DISABLE		0x0002
#घोषणा UMP_MASK_UART_FLAGS_PARITY		0x0008
#घोषणा UMP_MASK_UART_FLAGS_OUT_X_DSR_FLOW	0x0010
#घोषणा UMP_MASK_UART_FLAGS_OUT_X_CTS_FLOW	0x0020
#घोषणा UMP_MASK_UART_FLAGS_OUT_X		0x0040
#घोषणा UMP_MASK_UART_FLAGS_OUT_XA		0x0080
#घोषणा UMP_MASK_UART_FLAGS_IN_X		0x0100
#घोषणा UMP_MASK_UART_FLAGS_DTR_FLOW		0x0800
#घोषणा UMP_MASK_UART_FLAGS_DTR_DISABLE		0x1000
#घोषणा UMP_MASK_UART_FLAGS_RECEIVE_MS_INT	0x2000
#घोषणा UMP_MASK_UART_FLAGS_AUTO_START_ON_ERR	0x4000

#घोषणा UMP_DMA_MODE_CONTINOUS			0x01
#घोषणा UMP_PIPE_TRANS_TIMEOUT_ENA		0x80
#घोषणा UMP_PIPE_TRANSFER_MODE_MASK		0x03
#घोषणा UMP_PIPE_TRANS_TIMEOUT_MASK		0x7C

/* Purge port Direction Mask Bits */
#घोषणा UMP_PORT_सूची_OUT			0x01
#घोषणा UMP_PORT_सूची_IN				0x02

/* Address of Port 0 */
#घोषणा UMPM_UART1_PORT				0x03

/* Commands */
#घोषणा	UMPC_SET_CONFIG			0x05
#घोषणा	UMPC_OPEN_PORT			0x06
#घोषणा	UMPC_CLOSE_PORT			0x07
#घोषणा	UMPC_START_PORT			0x08
#घोषणा	UMPC_STOP_PORT			0x09
#घोषणा	UMPC_TEST_PORT			0x0A
#घोषणा	UMPC_PURGE_PORT			0x0B

/* Force the Firmware to complete the current Read */
#घोषणा	UMPC_COMPLETE_READ		0x80
/* Force UMP back पूर्णांकo BOOT Mode */
#घोषणा	UMPC_HARDWARE_RESET		0x81
/*
 * Copy current करोwnload image to type 0xf2 record in 16k I2C
 * firmware will change 0xff record to type 2 record when complete
 */
#घोषणा	UMPC_COPY_DNLD_TO_I2C		0x82

/*
 * Special function रेजिस्टर commands
 * wIndex is रेजिस्टर address
 * wValue is MSB/LSB mask/data
 */
#घोषणा	UMPC_WRITE_SFR			0x83	/* Write SFR Register */

/* wIndex is रेजिस्टर address */
#घोषणा	UMPC_READ_SFR			0x84	/* Read SRF Register */

/* Set or Clear DTR (wValue bit 0 Set/Clear)	wIndex ModuleID (port) */
#घोषणा	UMPC_SET_CLR_DTR		0x85

/* Set or Clear RTS (wValue bit 0 Set/Clear)	wIndex ModuleID (port) */
#घोषणा	UMPC_SET_CLR_RTS		0x86

/* Set or Clear LOOPBACK (wValue bit 0 Set/Clear) wIndex ModuleID (port) */
#घोषणा	UMPC_SET_CLR_LOOPBACK		0x87

/* Set or Clear BREAK (wValue bit 0 Set/Clear)	wIndex ModuleID (port) */
#घोषणा	UMPC_SET_CLR_BREAK		0x88

/* Read MSR wIndex ModuleID (port) */
#घोषणा	UMPC_READ_MSR			0x89

/* Toolkit commands */
/* Read-ग_लिखो group */
#घोषणा	UMPC_MEMORY_READ		0x92
#घोषणा	UMPC_MEMORY_WRITE		0x93

/*
 *	UMP DMA Definitions
 */
#घोषणा UMPD_OEDB1_ADDRESS		0xFF08
#घोषणा UMPD_OEDB2_ADDRESS		0xFF10

काष्ठा out_endpoपूर्णांक_desc_block अणु
	u8 Configuration;
	u8 XBufAddr;
	u8 XByteCount;
	u8 Unused1;
	u8 Unused2;
	u8 YBufAddr;
	u8 YByteCount;
	u8 BufferSize;
पूर्ण;


/*
 * TYPE DEFINITIONS
 * Structures क्रम Firmware commands
 */
/* UART settings */
काष्ठा ump_uart_config अणु
	u16 wBaudRate;		/* Baud rate                        */
	u16 wFlags;		/* Biपंचांगap mask of flags             */
	u8 bDataBits;		/* 5..8 - data bits per अक्षरacter   */
	u8 bParity;		/* Parity settings                  */
	u8 bStopBits;		/* Stop bits settings               */
	अक्षर cXon;		/* XON अक्षरacter                    */
	अक्षर cXoff;		/* XOFF अक्षरacter                   */
	u8 bUartMode;		/* Will be updated when a user      */
				/* पूर्णांकerface is defined             */
पूर्ण;


/*
 * TYPE DEFINITIONS
 * Structures क्रम USB पूर्णांकerrupts
 */
/* Interrupt packet काष्ठाure */
काष्ठा ump_पूर्णांकerrupt अणु
	u8 bICode;			/* Interrupt code (पूर्णांकerrupt num)   */
	u8 bIInfo;			/* Interrupt inक्रमmation            */
पूर्ण;


#घोषणा TIUMP_GET_PORT_FROM_CODE(c)	(((c) >> 6) & 0x01)
#घोषणा TIUMP_GET_FUNC_FROM_CODE(c)	((c) & 0x0f)
#घोषणा TIUMP_INTERRUPT_CODE_LSR	0x03
#घोषणा TIUMP_INTERRUPT_CODE_MSR	0x04

#पूर्ण_अगर
