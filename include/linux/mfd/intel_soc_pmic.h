<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Intel SoC PMIC Driver
 *
 * Copyright (C) 2012-2014 Intel Corporation. All rights reserved.
 *
 * Author: Yang, Bin <bin.yang@पूर्णांकel.com>
 * Author: Zhu, Lejun <lejun.zhu@linux.पूर्णांकel.com>
 */

#अगर_अघोषित __INTEL_SOC_PMIC_H__
#घोषणा __INTEL_SOC_PMIC_H__

#समावेश <linux/regmap.h>

/**
 * काष्ठा पूर्णांकel_soc_pmic - Intel SoC PMIC data
 * @irq: Master पूर्णांकerrupt number of the parent PMIC device
 * @regmap: Poपूर्णांकer to the parent PMIC device regmap काष्ठाure
 * @irq_chip_data: IRQ chip data क्रम the PMIC itself
 * @irq_chip_data_pwrbtn: Chained IRQ chip data क्रम the Power Button
 * @irq_chip_data_पंचांगu: Chained IRQ chip data क्रम the Time Management Unit
 * @irq_chip_data_bcu: Chained IRQ chip data क्रम the Burst Control Unit
 * @irq_chip_data_adc: Chained IRQ chip data क्रम the General Purpose ADC
 * @irq_chip_data_chgr: Chained IRQ chip data क्रम the External Charger
 * @irq_chip_data_crit: Chained IRQ chip data क्रम the Critical Event Handler
 * @dev: Poपूर्णांकer to the parent PMIC device
 * @scu: Poपूर्णांकer to the SCU IPC device data काष्ठाure
 */
काष्ठा पूर्णांकel_soc_pmic अणु
	पूर्णांक irq;
	काष्ठा regmap *regmap;
	काष्ठा regmap_irq_chip_data *irq_chip_data;
	काष्ठा regmap_irq_chip_data *irq_chip_data_pwrbtn;
	काष्ठा regmap_irq_chip_data *irq_chip_data_पंचांगu;
	काष्ठा regmap_irq_chip_data *irq_chip_data_bcu;
	काष्ठा regmap_irq_chip_data *irq_chip_data_adc;
	काष्ठा regmap_irq_chip_data *irq_chip_data_chgr;
	काष्ठा regmap_irq_chip_data *irq_chip_data_crit;
	काष्ठा device *dev;
	काष्ठा पूर्णांकel_scu_ipc_dev *scu;
पूर्ण;

पूर्णांक पूर्णांकel_soc_pmic_exec_mipi_pmic_seq_element(u16 i2c_address, u32 reg_address,
					      u32 value, u32 mask);

#पूर्ण_अगर	/* __INTEL_SOC_PMIC_H__ */
