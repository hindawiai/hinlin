<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2015 Jakub Kicinski <kubakici@wp.pl>
 */

#अगर_अघोषित __MT7601U_MCU_H
#घोषणा __MT7601U_MCU_H

काष्ठा mt7601u_dev;

/* Register definitions */
#घोषणा MT_MCU_RESET_CTL		0x070C
#घोषणा MT_MCU_INT_LEVEL		0x0718
#घोषणा MT_MCU_COM_REG0			0x0730
#घोषणा MT_MCU_COM_REG1			0x0734
#घोषणा MT_MCU_COM_REG2			0x0738
#घोषणा MT_MCU_COM_REG3			0x073C

#घोषणा MT_MCU_IVB_SIZE			0x40
#घोषणा MT_MCU_DLM_OFFSET		0x80000

#घोषणा MT_MCU_MEMMAP_WLAN		0x00410000
#घोषणा MT_MCU_MEMMAP_BBP		0x40000000
#घोषणा MT_MCU_MEMMAP_RF		0x80000000

#घोषणा INBAND_PACKET_MAX_LEN		192

क्रमागत mcu_cmd अणु
	CMD_FUN_SET_OP = 1,
	CMD_LOAD_CR = 2,
	CMD_INIT_GAIN_OP = 3,
	CMD_DYNC_VGA_OP = 6,
	CMD_TDLS_CH_SW = 7,
	CMD_BURST_WRITE = 8,
	CMD_READ_MODIFY_WRITE = 9,
	CMD_RANDOM_READ = 10,
	CMD_BURST_READ = 11,
	CMD_RANDOM_WRITE = 12,
	CMD_LED_MODE_OP = 16,
	CMD_POWER_SAVING_OP = 20,
	CMD_WOW_CONFIG = 21,
	CMD_WOW_QUERY = 22,
	CMD_WOW_FEATURE = 24,
	CMD_CARRIER_DETECT_OP = 28,
	CMD_RADOR_DETECT_OP = 29,
	CMD_SWITCH_CHANNEL_OP = 30,
	CMD_CALIBRATION_OP = 31,
	CMD_BEACON_OP = 32,
	CMD_ANTENNA_OP = 33,
पूर्ण;

क्रमागत mcu_function अणु
	Q_SELECT = 1,
	ATOMIC_TSSI_SETTING = 5,
पूर्ण;

क्रमागत mcu_घातer_mode अणु
	RADIO_OFF = 0x30,
	RADIO_ON = 0x31,
	RADIO_OFF_AUTO_WAKEUP = 0x32,
	RADIO_OFF_ADVANCE = 0x33,
	RADIO_ON_ADVANCE = 0x34,
पूर्ण;

क्रमागत mcu_calibrate अणु
	MCU_CAL_R = 1,
	MCU_CAL_DCOC,
	MCU_CAL_LC,
	MCU_CAL_LOFT,
	MCU_CAL_TXIQ,
	MCU_CAL_BW,
	MCU_CAL_DPD,
	MCU_CAL_RXIQ,
	MCU_CAL_TXDCOC,
पूर्ण;

पूर्णांक mt7601u_mcu_init(काष्ठा mt7601u_dev *dev);
पूर्णांक mt7601u_mcu_cmd_init(काष्ठा mt7601u_dev *dev);
व्योम mt7601u_mcu_cmd_deinit(काष्ठा mt7601u_dev *dev);

पूर्णांक
mt7601u_mcu_calibrate(काष्ठा mt7601u_dev *dev, क्रमागत mcu_calibrate cal, u32 val);
पूर्णांक mt7601u_mcu_tssi_पढ़ो_kick(काष्ठा mt7601u_dev *dev, पूर्णांक use_hvga);

#पूर्ण_अगर
