<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 */

#अगर_अघोषित __MT76x2_MCU_H
#घोषणा __MT76x2_MCU_H

#समावेश "../mt76x02_mcu.h"

/* Register definitions */
#घोषणा MT_MCU_CPU_CTL			0x0704
#घोषणा MT_MCU_CLOCK_CTL		0x0708
#घोषणा MT_MCU_PCIE_REMAP_BASE1		0x0740
#घोषणा MT_MCU_PCIE_REMAP_BASE2		0x0744
#घोषणा MT_MCU_PCIE_REMAP_BASE3		0x0748

#घोषणा MT_MCU_ROM_PATCH_OFFSET		0x80000
#घोषणा MT_MCU_ROM_PATCH_ADDR		0x90000

#घोषणा MT_MCU_ILM_OFFSET		0x80000

#घोषणा MT_MCU_DLM_OFFSET		0x100000
#घोषणा MT_MCU_DLM_ADDR			0x90000
#घोषणा MT_MCU_DLM_ADDR_E3		0x90800

क्रमागत mcu_calibration अणु
	MCU_CAL_R = 1,
	MCU_CAL_TEMP_SENSOR,
	MCU_CAL_RXDCOC,
	MCU_CAL_RC,
	MCU_CAL_SX_LOGEN,
	MCU_CAL_LC,
	MCU_CAL_TX_LOFT,
	MCU_CAL_TXIQ,
	MCU_CAL_TSSI,
	MCU_CAL_TSSI_COMP,
	MCU_CAL_DPD,
	MCU_CAL_RXIQC_FI,
	MCU_CAL_RXIQC_FD,
	MCU_CAL_PWRON,
	MCU_CAL_TX_SHAPING,
पूर्ण;

क्रमागत mt76x2_mcu_cr_mode अणु
	MT_RF_CR,
	MT_BBP_CR,
	MT_RF_BBP_CR,
	MT_HL_TEMP_CR_UPDATE,
पूर्ण;

काष्ठा mt76x2_tssi_comp अणु
	u8 pa_mode;
	u8 cal_mode;
	u16 pad;

	u8 slope0;
	u8 slope1;
	u8 offset0;
	u8 offset1;
पूर्ण __packed __aligned(4);

पूर्णांक mt76x2_mcu_tssi_comp(काष्ठा mt76x02_dev *dev,
			 काष्ठा mt76x2_tssi_comp *tssi_data);
पूर्णांक mt76x2_mcu_init_gain(काष्ठा mt76x02_dev *dev, u8 channel, u32 gain,
			 bool क्रमce);

#पूर्ण_अगर
