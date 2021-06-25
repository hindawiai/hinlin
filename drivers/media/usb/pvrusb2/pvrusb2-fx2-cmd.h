<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 *  Copyright (C) 2007 Michael Krufky <mkrufky@linuxtv.org>
 */

#अगर_अघोषित _PVRUSB2_FX2_CMD_H_
#घोषणा _PVRUSB2_FX2_CMD_H_

#घोषणा FX2CMD_MEM_WRITE_DWORD  0x01u
#घोषणा FX2CMD_MEM_READ_DWORD   0x02u

#घोषणा FX2CMD_HCW_ZILOG_RESET  0x10u /* 1=reset 0=release */

#घोषणा FX2CMD_MEM_READ_64BYTES 0x28u

#घोषणा FX2CMD_REG_WRITE        0x04u
#घोषणा FX2CMD_REG_READ         0x05u
#घोषणा FX2CMD_MEMSEL           0x06u

#घोषणा FX2CMD_I2C_WRITE        0x08u
#घोषणा FX2CMD_I2C_READ         0x09u

#घोषणा FX2CMD_GET_USB_SPEED    0x0bu

#घोषणा FX2CMD_STREAMING_ON     0x36u
#घोषणा FX2CMD_STREAMING_OFF    0x37u

#घोषणा FX2CMD_FWPOST1          0x52u

/* These 2 only exist on Model 160xxx */
#घोषणा FX2CMD_HCW_DEMOD_RESET_PIN 0xd4u
#घोषणा FX2CMD_HCW_MAKO_SLEEP_PIN  0xd5u

#घोषणा FX2CMD_POWER_OFF        0xdcu
#घोषणा FX2CMD_POWER_ON         0xdeu

#घोषणा FX2CMD_DEEP_RESET       0xddu

#घोषणा FX2CMD_GET_EEPROM_ADDR  0xebu
#घोषणा FX2CMD_GET_IR_CODE      0xecu

#घोषणा FX2CMD_HCW_DEMOD_RESETIN       0xf0u
#घोषणा FX2CMD_HCW_DTV_STREAMING_ON    0xf1u
#घोषणा FX2CMD_HCW_DTV_STREAMING_OFF   0xf2u

#घोषणा FX2CMD_ONAIR_DTV_STREAMING_ON  0xa0u
#घोषणा FX2CMD_ONAIR_DTV_STREAMING_OFF 0xa1u
#घोषणा FX2CMD_ONAIR_DTV_POWER_ON      0xa2u
#घोषणा FX2CMD_ONAIR_DTV_POWER_OFF     0xa3u

#पूर्ण_अगर /* _PVRUSB2_FX2_CMD_H_ */
