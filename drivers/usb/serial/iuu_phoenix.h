<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Infinity Unlimited USB Phoenix driver
 *
 * Copyright (C) 2007 Alain Degreffe (eczema@ecze.com)
 *
 *
 * Original code taken from iuutool ( Copyright (C) 2006 Juan Carlos Borrथँs )
 *
 *  And tested with help of WB Electronics
 */

#घोषणा   IUU_USB_VENDOR_ID  0x104f
#घोषणा   IUU_USB_PRODUCT_ID  0x0004
#घोषणा   IUU_USB_OP_TIMEOUT  0x0200

/* Programmer commands */

#घोषणा IUU_NO_OPERATION   0x00
#घोषणा IUU_GET_FIRMWARE_VERSION   0x01
#घोषणा IUU_GET_PRODUCT_NAME   0x02
#घोषणा IUU_GET_STATE_REGISTER   0x03
#घोषणा IUU_SET_LED   0x04
#घोषणा IUU_WAIT_MUS   0x05
#घोषणा IUU_WAIT_MS   0x06
#घोषणा IUU_GET_LOADER_VERSION   0x50
#घोषणा IUU_RST_SET   0x52
#घोषणा IUU_RST_CLEAR   0x53
#घोषणा IUU_SET_VCC   0x59
#घोषणा IUU_UART_ENABLE   0x49
#घोषणा IUU_UART_DISABLE   0x4A
#घोषणा IUU_UART_WRITE_I2C   0x4C
#घोषणा IUU_UART_ESC   0x5E
#घोषणा IUU_UART_TRAP   0x54
#घोषणा IUU_UART_TRAP_BREAK   0x5B
#घोषणा IUU_UART_RX   0x56
#घोषणा IUU_AVR_ON   0x21
#घोषणा IUU_AVR_OFF   0x22
#घोषणा IUU_AVR_1CLK   0x23
#घोषणा IUU_AVR_RESET   0x24
#घोषणा IUU_AVR_RESET_PC   0x25
#घोषणा IUU_AVR_INC_PC   0x26
#घोषणा IUU_AVR_INCN_PC   0x27
#घोषणा IUU_AVR_PREAD   0x29
#घोषणा IUU_AVR_PREADN   0x2A
#घोषणा IUU_AVR_PWRITE   0x28
#घोषणा IUU_AVR_DREAD   0x2C
#घोषणा IUU_AVR_DREADN   0x2D
#घोषणा IUU_AVR_DWRITE   0x2B
#घोषणा IUU_AVR_PWRITEN   0x2E
#घोषणा IUU_EEPROM_ON   0x37
#घोषणा IUU_EEPROM_OFF   0x38
#घोषणा IUU_EEPROM_WRITE   0x39
#घोषणा IUU_EEPROM_WRITEX   0x3A
#घोषणा IUU_EEPROM_WRITE8   0x3B
#घोषणा IUU_EEPROM_WRITE16   0x3C
#घोषणा IUU_EEPROM_WRITEX32   0x3D
#घोषणा IUU_EEPROM_WRITEX64   0x3E
#घोषणा IUU_EEPROM_READ   0x3F
#घोषणा IUU_EEPROM_READX   0x40
#घोषणा IUU_EEPROM_BREAD   0x41
#घोषणा IUU_EEPROM_BREADX   0x42
#घोषणा IUU_PIC_CMD   0x0A
#घोषणा IUU_PIC_CMD_LOAD   0x0B
#घोषणा IUU_PIC_CMD_READ   0x0C
#घोषणा IUU_PIC_ON   0x0D
#घोषणा IUU_PIC_OFF   0x0E
#घोषणा IUU_PIC_RESET   0x16
#घोषणा IUU_PIC_INC_PC   0x0F
#घोषणा IUU_PIC_INCN_PC   0x10
#घोषणा IUU_PIC_PWRITE   0x11
#घोषणा IUU_PIC_PREAD   0x12
#घोषणा IUU_PIC_PREADN   0x13
#घोषणा IUU_PIC_DWRITE   0x14
#घोषणा IUU_PIC_DREAD   0x15
#घोषणा IUU_UART_NOP   0x00
#घोषणा IUU_UART_CHANGE   0x02
#घोषणा IUU_UART_TX   0x04
#घोषणा IUU_DELAY_MS   0x06

#घोषणा IUU_OPERATION_OK   0x00
#घोषणा IUU_DEVICE_NOT_FOUND   0x01
#घोषणा IUU_INVALID_HANDLE   0x02
#घोषणा IUU_INVALID_PARAMETER   0x03
#घोषणा IUU_INVALID_व्योमERFACE   0x04
#घोषणा IUU_INVALID_REQUEST_LENGTH   0x05
#घोषणा IUU_UART_NOT_ENABLED   0x06
#घोषणा IUU_WRITE_ERROR   0x07
#घोषणा IUU_READ_ERROR   0x08
#घोषणा IUU_TX_ERROR   0x09
#घोषणा IUU_RX_ERROR   0x0A

#घोषणा IUU_PARITY_NONE   0x00
#घोषणा IUU_PARITY_EVEN   0x01
#घोषणा IUU_PARITY_ODD   0x02
#घोषणा IUU_PARITY_MARK   0x03
#घोषणा IUU_PARITY_SPACE   0x04
#घोषणा IUU_SC_INSERTED   0x01
#घोषणा IUU_VERIFY_ERROR   0x02
#घोषणा IUU_SIM_INSERTED   0x04
#घोषणा IUU_TWO_STOP_BITS   0x00
#घोषणा IUU_ONE_STOP_BIT   0x20
#घोषणा IUU_BAUD_2400   0x0398
#घोषणा IUU_BAUD_9600   0x0298
#घोषणा IUU_BAUD_19200   0x0164
#घोषणा IUU_BAUD_28800   0x0198
#घोषणा IUU_BAUD_38400   0x01B2
#घोषणा IUU_BAUD_57600   0x0030
#घोषणा IUU_BAUD_115200   0x0098
#घोषणा IUU_CLK_3579000   3579000
#घोषणा IUU_CLK_3680000   3680000
#घोषणा IUU_CLK_6000000   6000000
#घोषणा IUU_FULLCARD_IN   0x01
#घोषणा IUU_DEV_ERROR   0x02
#घोषणा IUU_MINICARD_IN   0x04
#घोषणा IUU_VCC_5V   0x00
#घोषणा IUU_VCC_3V   0x01
