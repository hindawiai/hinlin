<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित	_CM4040_H_
#घोषणा	_CM4040_H_

#घोषणा	CM_MAX_DEV		4

#घोषणा	DEVICE_NAME		"cmx"
#घोषणा	MODULE_NAME		"cm4040_cs"

#घोषणा REG_OFFSET_BULK_OUT      0
#घोषणा REG_OFFSET_BULK_IN       0
#घोषणा REG_OFFSET_BUFFER_STATUS 1
#घोषणा REG_OFFSET_SYNC_CONTROL  2

#घोषणा BSR_BULK_IN_FULL  0x02
#घोषणा BSR_BULK_OUT_FULL 0x01

#घोषणा SCR_HOST_TO_READER_START 0x80
#घोषणा SCR_ABORT                0x40
#घोषणा SCR_EN_NOTIFY            0x20
#घोषणा SCR_ACK_NOTIFY           0x10
#घोषणा SCR_READER_TO_HOST_DONE  0x08
#घोषणा SCR_HOST_TO_READER_DONE  0x04
#घोषणा SCR_PULSE_INTERRUPT      0x02
#घोषणा SCR_POWER_DOWN           0x01


#घोषणा  CMD_PC_TO_RDR_ICCPOWERON       0x62
#घोषणा  CMD_PC_TO_RDR_GETSLOTSTATUS    0x65
#घोषणा  CMD_PC_TO_RDR_ICCPOWEROFF      0x63
#घोषणा  CMD_PC_TO_RDR_SECURE           0x69
#घोषणा  CMD_PC_TO_RDR_GETPARAMETERS    0x6C
#घोषणा  CMD_PC_TO_RDR_RESETPARAMETERS  0x6D
#घोषणा  CMD_PC_TO_RDR_SETPARAMETERS    0x61
#घोषणा  CMD_PC_TO_RDR_XFRBLOCK         0x6F
#घोषणा  CMD_PC_TO_RDR_ESCAPE           0x6B
#घोषणा  CMD_PC_TO_RDR_ICCCLOCK         0x6E
#घोषणा  CMD_PC_TO_RDR_TEST_SECURE      0x74
#घोषणा  CMD_PC_TO_RDR_OK_SECURE        0x89


#घोषणा  CMD_RDR_TO_PC_SLOTSTATUS         0x81
#घोषणा  CMD_RDR_TO_PC_DATABLOCK          0x80
#घोषणा  CMD_RDR_TO_PC_PARAMETERS         0x82
#घोषणा  CMD_RDR_TO_PC_ESCAPE             0x83
#घोषणा  CMD_RDR_TO_PC_OK_SECURE          0x89

#पूर्ण_अगर	/* _CM4040_H_ */
