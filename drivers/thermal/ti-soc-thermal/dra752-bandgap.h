<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * DRA752 bandgap रेजिस्टरs, bitfields and temperature definitions
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * Contact:
 *   Eduarकरो Valentin <eduarकरो.valentin@ti.com>
 *   Tero Kristo <t-kristo@ti.com>
 *
 * This is an स्वतः generated file.
 */
#अगर_अघोषित __DRA752_BANDGAP_H
#घोषणा __DRA752_BANDGAP_H

/**
 * *** DRA752 ***
 *
 * Below, in sequence, are the Register definitions,
 * the bitfields and the temperature definitions क्रम DRA752.
 */

/**
 * DRA752 रेजिस्टर definitions
 *
 * Registers are defined as offsets. The offsets are
 * relative to FUSE_OPP_BGAP_GPU on DRA752.
 * DRA752_BANDGAP_BASE		0x4a0021e0
 *
 * Register below are grouped by करोमुख्य (not necessarily in offset order)
 */


/* DRA752.common रेजिस्टर offsets */
#घोषणा DRA752_BANDGAP_CTRL_1_OFFSET		0x1a0
#घोषणा DRA752_BANDGAP_STATUS_1_OFFSET		0x1c8
#घोषणा DRA752_BANDGAP_CTRL_2_OFFSET		0x39c
#घोषणा DRA752_BANDGAP_STATUS_2_OFFSET		0x3b8

/* DRA752.core रेजिस्टर offsets */
#घोषणा DRA752_STD_FUSE_OPP_BGAP_CORE_OFFSET		0x8
#घोषणा DRA752_TEMP_SENSOR_CORE_OFFSET			0x154
#घोषणा DRA752_BANDGAP_THRESHOLD_CORE_OFFSET		0x1ac
#घोषणा DRA752_DTEMP_CORE_1_OFFSET			0x20c
#घोषणा DRA752_DTEMP_CORE_2_OFFSET			0x210

/* DRA752.iva रेजिस्टर offsets */
#घोषणा DRA752_STD_FUSE_OPP_BGAP_IVA_OFFSET		0x388
#घोषणा DRA752_TEMP_SENSOR_IVA_OFFSET			0x398
#घोषणा DRA752_BANDGAP_THRESHOLD_IVA_OFFSET		0x3a4
#घोषणा DRA752_DTEMP_IVA_1_OFFSET			0x3d4
#घोषणा DRA752_DTEMP_IVA_2_OFFSET			0x3d8

/* DRA752.mpu रेजिस्टर offsets */
#घोषणा DRA752_STD_FUSE_OPP_BGAP_MPU_OFFSET		0x4
#घोषणा DRA752_TEMP_SENSOR_MPU_OFFSET			0x14c
#घोषणा DRA752_BANDGAP_THRESHOLD_MPU_OFFSET		0x1a4
#घोषणा DRA752_DTEMP_MPU_1_OFFSET			0x1e4
#घोषणा DRA752_DTEMP_MPU_2_OFFSET			0x1e8

/* DRA752.dspeve रेजिस्टर offsets */
#घोषणा DRA752_STD_FUSE_OPP_BGAP_DSPEVE_OFFSET			0x384
#घोषणा DRA752_TEMP_SENSOR_DSPEVE_OFFSET			0x394
#घोषणा DRA752_BANDGAP_THRESHOLD_DSPEVE_OFFSET			0x3a0
#घोषणा DRA752_DTEMP_DSPEVE_1_OFFSET				0x3c0
#घोषणा DRA752_DTEMP_DSPEVE_2_OFFSET				0x3c4

/* DRA752.gpu रेजिस्टर offsets */
#घोषणा DRA752_STD_FUSE_OPP_BGAP_GPU_OFFSET		0x0
#घोषणा DRA752_TEMP_SENSOR_GPU_OFFSET			0x150
#घोषणा DRA752_BANDGAP_THRESHOLD_GPU_OFFSET		0x1a8
#घोषणा DRA752_DTEMP_GPU_1_OFFSET			0x1f8
#घोषणा DRA752_DTEMP_GPU_2_OFFSET			0x1fc

/**
 * Register bitfields क्रम DRA752
 *
 * All the macros bellow define the required bits क्रम
 * controlling temperature on DRA752. Bit defines are
 * grouped by रेजिस्टर.
 */

/* DRA752.BANDGAP_STATUS_1 */
#घोषणा DRA752_BANDGAP_STATUS_1_HOT_CORE_MASK		BIT(5)
#घोषणा DRA752_BANDGAP_STATUS_1_COLD_CORE_MASK		BIT(4)
#घोषणा DRA752_BANDGAP_STATUS_1_HOT_GPU_MASK		BIT(3)
#घोषणा DRA752_BANDGAP_STATUS_1_COLD_GPU_MASK		BIT(2)
#घोषणा DRA752_BANDGAP_STATUS_1_HOT_MPU_MASK		BIT(1)
#घोषणा DRA752_BANDGAP_STATUS_1_COLD_MPU_MASK		BIT(0)

/* DRA752.BANDGAP_CTRL_2 */
#घोषणा DRA752_BANDGAP_CTRL_2_FREEZE_IVA_MASK			BIT(22)
#घोषणा DRA752_BANDGAP_CTRL_2_FREEZE_DSPEVE_MASK		BIT(21)
#घोषणा DRA752_BANDGAP_CTRL_2_MASK_HOT_IVA_MASK			BIT(3)
#घोषणा DRA752_BANDGAP_CTRL_2_MASK_COLD_IVA_MASK		BIT(2)
#घोषणा DRA752_BANDGAP_CTRL_2_MASK_HOT_DSPEVE_MASK		BIT(1)
#घोषणा DRA752_BANDGAP_CTRL_2_MASK_COLD_DSPEVE_MASK		BIT(0)

/* DRA752.BANDGAP_STATUS_2 */
#घोषणा DRA752_BANDGAP_STATUS_2_HOT_IVA_MASK			BIT(3)
#घोषणा DRA752_BANDGAP_STATUS_2_COLD_IVA_MASK			BIT(2)
#घोषणा DRA752_BANDGAP_STATUS_2_HOT_DSPEVE_MASK			BIT(1)
#घोषणा DRA752_BANDGAP_STATUS_2_COLD_DSPEVE_MASK		BIT(0)

/* DRA752.BANDGAP_CTRL_1 */
#घोषणा DRA752_BANDGAP_CTRL_1_COUNTER_DELAY_MASK		(0x7 << 27)
#घोषणा DRA752_BANDGAP_CTRL_1_FREEZE_CORE_MASK			BIT(23)
#घोषणा DRA752_BANDGAP_CTRL_1_FREEZE_GPU_MASK			BIT(22)
#घोषणा DRA752_BANDGAP_CTRL_1_FREEZE_MPU_MASK			BIT(21)
#घोषणा DRA752_BANDGAP_CTRL_1_MASK_HOT_CORE_MASK		BIT(5)
#घोषणा DRA752_BANDGAP_CTRL_1_MASK_COLD_CORE_MASK		BIT(4)
#घोषणा DRA752_BANDGAP_CTRL_1_MASK_HOT_GPU_MASK			BIT(3)
#घोषणा DRA752_BANDGAP_CTRL_1_MASK_COLD_GPU_MASK		BIT(2)
#घोषणा DRA752_BANDGAP_CTRL_1_MASK_HOT_MPU_MASK			BIT(1)
#घोषणा DRA752_BANDGAP_CTRL_1_MASK_COLD_MPU_MASK		BIT(0)

/* DRA752.TEMP_SENSOR */
#घोषणा DRA752_TEMP_SENSOR_TMPSOFF_MASK		BIT(11)
#घोषणा DRA752_TEMP_SENSOR_EOCZ_MASK		BIT(10)
#घोषणा DRA752_TEMP_SENSOR_DTEMP_MASK		(0x3ff << 0)

/* DRA752.BANDGAP_THRESHOLD */
#घोषणा DRA752_BANDGAP_THRESHOLD_HOT_MASK		(0x3ff << 16)
#घोषणा DRA752_BANDGAP_THRESHOLD_COLD_MASK		(0x3ff << 0)

/**
 * Temperature limits and thresholds क्रम DRA752
 *
 * All the macros bellow are definitions क्रम handling the
 * ADC conversions and representation of temperature limits
 * and thresholds क्रम DRA752. Definitions are grouped
 * by temperature करोमुख्य.
 */

/* DRA752.common temperature definitions */
/* ADC conversion table limits */
#घोषणा DRA752_ADC_START_VALUE		540
#घोषणा DRA752_ADC_END_VALUE		945

/* DRA752.GPU temperature definitions */
/* bandgap घड़ी limits */
#घोषणा DRA752_GPU_MAX_FREQ				1500000
#घोषणा DRA752_GPU_MIN_FREQ				1000000
/* पूर्णांकerrupts thresholds */
#घोषणा DRA752_GPU_T_HOT				800
#घोषणा DRA752_GPU_T_COLD				795

/* DRA752.MPU temperature definitions */
/* bandgap घड़ी limits */
#घोषणा DRA752_MPU_MAX_FREQ				1500000
#घोषणा DRA752_MPU_MIN_FREQ				1000000
/* पूर्णांकerrupts thresholds */
#घोषणा DRA752_MPU_T_HOT				800
#घोषणा DRA752_MPU_T_COLD				795

/* DRA752.CORE temperature definitions */
/* bandgap घड़ी limits */
#घोषणा DRA752_CORE_MAX_FREQ				1500000
#घोषणा DRA752_CORE_MIN_FREQ				1000000
/* पूर्णांकerrupts thresholds */
#घोषणा DRA752_CORE_T_HOT				800
#घोषणा DRA752_CORE_T_COLD				795

/* DRA752.DSPEVE temperature definitions */
/* bandgap घड़ी limits */
#घोषणा DRA752_DSPEVE_MAX_FREQ				1500000
#घोषणा DRA752_DSPEVE_MIN_FREQ				1000000
/* पूर्णांकerrupts thresholds */
#घोषणा DRA752_DSPEVE_T_HOT				800
#घोषणा DRA752_DSPEVE_T_COLD				795

/* DRA752.IVA temperature definitions */
/* bandgap घड़ी limits */
#घोषणा DRA752_IVA_MAX_FREQ				1500000
#घोषणा DRA752_IVA_MIN_FREQ				1000000
/* पूर्णांकerrupts thresholds */
#घोषणा DRA752_IVA_T_HOT				800
#घोषणा DRA752_IVA_T_COLD				795

#पूर्ण_अगर /* __DRA752_BANDGAP_H */
