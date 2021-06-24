<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */

/*
 * Core definitions क्रम RAVE SP MFD driver.
 *
 * Copyright (C) 2017 Zodiac Inflight Innovations
 */

#अगर_अघोषित _LINUX_RAVE_SP_H_
#घोषणा _LINUX_RAVE_SP_H_

#समावेश <linux/notअगरier.h>

क्रमागत rave_sp_command अणु
	RAVE_SP_CMD_GET_FIRMWARE_VERSION	= 0x20,
	RAVE_SP_CMD_GET_BOOTLOADER_VERSION	= 0x21,
	RAVE_SP_CMD_BOOT_SOURCE			= 0x26,
	RAVE_SP_CMD_GET_BOARD_COPPER_REV	= 0x2B,
	RAVE_SP_CMD_GET_GPIO_STATE		= 0x2F,

	RAVE_SP_CMD_STATUS			= 0xA0,
	RAVE_SP_CMD_SW_WDT			= 0xA1,
	RAVE_SP_CMD_PET_WDT			= 0xA2,
	RAVE_SP_CMD_RMB_EEPROM			= 0xA4,
	RAVE_SP_CMD_SET_BACKLIGHT		= 0xA6,
	RAVE_SP_CMD_RESET			= 0xA7,
	RAVE_SP_CMD_RESET_REASON		= 0xA8,

	RAVE_SP_CMD_REQ_COPPER_REV		= 0xB6,
	RAVE_SP_CMD_GET_I2C_DEVICE_STATUS	= 0xBA,
	RAVE_SP_CMD_GET_SP_SILICON_REV		= 0xB9,
	RAVE_SP_CMD_CONTROL_EVENTS		= 0xBB,

	RAVE_SP_EVNT_BASE			= 0xE0,
पूर्ण;

काष्ठा rave_sp;

अटल अंतरभूत अचिन्हित दीर्घ rave_sp_action_pack(u8 event, u8 value)
अणु
	वापस ((अचिन्हित दीर्घ)value << 8) | event;
पूर्ण

अटल अंतरभूत u8 rave_sp_action_unpack_event(अचिन्हित दीर्घ action)
अणु
	वापस action;
पूर्ण

अटल अंतरभूत u8 rave_sp_action_unpack_value(अचिन्हित दीर्घ action)
अणु
	वापस action >> 8;
पूर्ण

पूर्णांक rave_sp_exec(काष्ठा rave_sp *sp,
		 व्योम *__data,  माप_प्रकार data_size,
		 व्योम *reply_data, माप_प्रकार reply_data_size);

काष्ठा device;
पूर्णांक devm_rave_sp_रेजिस्टर_event_notअगरier(काष्ठा device *dev,
					 काष्ठा notअगरier_block *nb);

#पूर्ण_अगर /* _LINUX_RAVE_SP_H_ */
