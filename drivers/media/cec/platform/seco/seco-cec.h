<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * SECO X86 Boards CEC रेजिस्टर defines
 *
 * Author:  Ettore Chimenti <ek5.chimenti@gmail.com>
 * Copyright (C) 2018, SECO Spa.
 * Copyright (C) 2018, Aidilab Srl.
 */

#अगर_अघोषित __SECO_CEC_H__
#घोषणा __SECO_CEC_H__

#घोषणा SECOCEC_MAX_ADDRS		1
#घोषणा SECOCEC_DEV_NAME		"secocec"
#घोषणा SECOCEC_LATEST_FW		0x0f0b

#घोषणा SMBTIMEOUT			0xfff
#घोषणा SMB_POLL_UDELAY			10

#घोषणा SMBUS_WRITE			0
#घोषणा SMBUS_READ			1

#घोषणा CMD_BYTE_DATA			0
#घोषणा CMD_WORD_DATA			1

/*
 * SMBus definitons क्रम Braswell
 */

#घोषणा BRA_DONE_STATUS			BIT(7)
#घोषणा BRA_INUSE_STS			BIT(6)
#घोषणा BRA_FAILED_OP			BIT(4)
#घोषणा BRA_BUS_ERR			BIT(3)
#घोषणा BRA_DEV_ERR			BIT(2)
#घोषणा BRA_INTR			BIT(1)
#घोषणा BRA_HOST_BUSY			BIT(0)
#घोषणा BRA_HSTS_ERR_MASK   (BRA_FAILED_OP | BRA_BUS_ERR | BRA_DEV_ERR)

#घोषणा BRA_PEC_EN			BIT(7)
#घोषणा BRA_START			BIT(6)
#घोषणा BRA_LAST__BYTE			BIT(5)
#घोषणा BRA_INTREN			BIT(0)
#घोषणा BRA_SMB_CMD			(7 << 2)
#घोषणा BRA_SMB_CMD_QUICK		(0 << 2)
#घोषणा BRA_SMB_CMD_BYTE		(1 << 2)
#घोषणा BRA_SMB_CMD_BYTE_DATA		(2 << 2)
#घोषणा BRA_SMB_CMD_WORD_DATA		(3 << 2)
#घोषणा BRA_SMB_CMD_PROCESS_CALL	(4 << 2)
#घोषणा BRA_SMB_CMD_BLOCK		(5 << 2)
#घोषणा BRA_SMB_CMD_I2CREAD		(6 << 2)
#घोषणा BRA_SMB_CMD_BLOCK_PROCESS	(7 << 2)

#घोषणा BRA_SMB_BASE_ADDR  0x2040
#घोषणा HSTS               (BRA_SMB_BASE_ADDR + 0)
#घोषणा HCNT               (BRA_SMB_BASE_ADDR + 2)
#घोषणा HCMD               (BRA_SMB_BASE_ADDR + 3)
#घोषणा XMIT_SLVA          (BRA_SMB_BASE_ADDR + 4)
#घोषणा HDAT0              (BRA_SMB_BASE_ADDR + 5)
#घोषणा HDAT1              (BRA_SMB_BASE_ADDR + 6)

/*
 * Microcontroller Address
 */

#घोषणा SECOCEC_MICRO_ADDRESS		0x40

/*
 * STM32 SMBus Registers
 */

#घोषणा SECOCEC_VERSION			0x00
#घोषणा SECOCEC_ENABLE_REG_1		0x01
#घोषणा SECOCEC_ENABLE_REG_2		0x02
#घोषणा SECOCEC_STATUS_REG_1		0x03
#घोषणा SECOCEC_STATUS_REG_2		0x04

#घोषणा SECOCEC_STATUS			0x28
#घोषणा SECOCEC_DEVICE_LA		0x29
#घोषणा SECOCEC_READ_OPERATION_ID	0x2a
#घोषणा SECOCEC_READ_DATA_LENGTH	0x2b
#घोषणा SECOCEC_READ_DATA_00		0x2c
#घोषणा SECOCEC_READ_DATA_02		0x2d
#घोषणा SECOCEC_READ_DATA_04		0x2e
#घोषणा SECOCEC_READ_DATA_06		0x2f
#घोषणा SECOCEC_READ_DATA_08		0x30
#घोषणा SECOCEC_READ_DATA_10		0x31
#घोषणा SECOCEC_READ_DATA_12		0x32
#घोषणा SECOCEC_READ_BYTE0		0x33
#घोषणा SECOCEC_WRITE_OPERATION_ID	0x34
#घोषणा SECOCEC_WRITE_DATA_LENGTH	0x35
#घोषणा SECOCEC_WRITE_DATA_00		0x36
#घोषणा SECOCEC_WRITE_DATA_02		0x37
#घोषणा SECOCEC_WRITE_DATA_04		0x38
#घोषणा SECOCEC_WRITE_DATA_06		0x39
#घोषणा SECOCEC_WRITE_DATA_08		0x3a
#घोषणा SECOCEC_WRITE_DATA_10		0x3b
#घोषणा SECOCEC_WRITE_DATA_12		0x3c
#घोषणा SECOCEC_WRITE_BYTE0		0x3d

#घोषणा SECOCEC_IR_READ_DATA		0x3e

/*
 * IR
 */

#घोषणा SECOCEC_IR_COMMAND_MASK		0x007F
#घोषणा SECOCEC_IR_COMMAND_SHL		0
#घोषणा SECOCEC_IR_ADDRESS_MASK		0x1F00
#घोषणा SECOCEC_IR_ADDRESS_SHL		8
#घोषणा SECOCEC_IR_TOGGLE_MASK		0x8000
#घोषणा SECOCEC_IR_TOGGLE_SHL		15

/*
 * Enabling रेजिस्टर
 */

#घोषणा SECOCEC_ENABLE_REG_1_CEC		0x1000
#घोषणा SECOCEC_ENABLE_REG_1_IR			0x2000
#घोषणा SECOCEC_ENABLE_REG_1_IR_PASSTHROUGH	0x4000

/*
 * Status रेजिस्टर
 */

#घोषणा SECOCEC_STATUS_REG_1_CEC	SECOCEC_ENABLE_REG_1_CEC
#घोषणा SECOCEC_STATUS_REG_1_IR		SECOCEC_ENABLE_REG_1_IR
#घोषणा SECOCEC_STATUS_REG_1_IR_PASSTHR	SECOCEC_ENABLE_REG_1_IR_PASSTHR

/*
 * Status data
 */

#घोषणा SECOCEC_STATUS_MSG_RECEIVED_MASK	BIT(0)
#घोषणा SECOCEC_STATUS_RX_ERROR_MASK		BIT(1)
#घोषणा SECOCEC_STATUS_MSG_SENT_MASK		BIT(2)
#घोषणा SECOCEC_STATUS_TX_ERROR_MASK		BIT(3)

#घोषणा SECOCEC_STATUS_TX_NACK_ERROR		BIT(4)
#घोषणा SECOCEC_STATUS_RX_OVERFLOW_MASK		BIT(5)

#पूर्ण_अगर /* __SECO_CEC_H__ */
