<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2015 Jakub Kicinski <kubakici@wp.pl>
 */

#अगर_अघोषित __MT76X0U_MCU_H
#घोषणा __MT76X0U_MCU_H

#समावेश "../mt76x02_mcu.h"

काष्ठा mt76x02_dev;

#घोषणा MT_MCU_IVB_SIZE			0x40
#घोषणा MT_MCU_DLM_OFFSET		0x80000

/* We use same space क्रम BBP as क्रम MAC regs
 * #घोषणा MT_MCU_MEMMAP_BBP		0x40000000
 */
#घोषणा MT_MCU_MEMMAP_RF		0x80000000

क्रमागत mcu_calibrate अणु
	MCU_CAL_R = 1,
	MCU_CAL_RXDCOC,
	MCU_CAL_LC,
	MCU_CAL_LOFT,
	MCU_CAL_TXIQ,
	MCU_CAL_BW,
	MCU_CAL_DPD,
	MCU_CAL_RXIQ,
	MCU_CAL_TXDCOC,
	MCU_CAL_RX_GROUP_DELAY,
	MCU_CAL_TX_GROUP_DELAY,
	MCU_CAL_VCO,
	MCU_CAL_NO_SIGNAL = 0xfe,
	MCU_CAL_FULL = 0xff,
पूर्ण;

पूर्णांक mt76x0e_mcu_init(काष्ठा mt76x02_dev *dev);
पूर्णांक mt76x0u_mcu_init(काष्ठा mt76x02_dev *dev);
अटल अंतरभूत पूर्णांक mt76x0_firmware_running(काष्ठा mt76x02_dev *dev)
अणु
	वापस mt76_rr(dev, MT_MCU_COM_REG0) == 1;
पूर्ण

#पूर्ण_अगर
