<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2014 MediaTek Inc.
 * Author: Flora Fu, MediaTek
 */

#अगर_अघोषित __MFD_MT6397_CORE_H__
#घोषणा __MFD_MT6397_CORE_H__

#समावेश <linux/mutex.h>
#समावेश <linux/notअगरier.h>

क्रमागत chip_id अणु
	MT6323_CHIP_ID = 0x23,
	MT6358_CHIP_ID = 0x58,
	MT6391_CHIP_ID = 0x91,
	MT6397_CHIP_ID = 0x97,
पूर्ण;

क्रमागत mt6397_irq_numbers अणु
	MT6397_IRQ_SPKL_AB = 0,
	MT6397_IRQ_SPKR_AB,
	MT6397_IRQ_SPKL,
	MT6397_IRQ_SPKR,
	MT6397_IRQ_BAT_L,
	MT6397_IRQ_BAT_H,
	MT6397_IRQ_FG_BAT_L,
	MT6397_IRQ_FG_BAT_H,
	MT6397_IRQ_WATCHDOG,
	MT6397_IRQ_PWRKEY,
	MT6397_IRQ_THR_L,
	MT6397_IRQ_THR_H,
	MT6397_IRQ_VBATON_UNDET,
	MT6397_IRQ_BVALID_DET,
	MT6397_IRQ_CHRDET,
	MT6397_IRQ_OV,
	MT6397_IRQ_LDO,
	MT6397_IRQ_HOMEKEY,
	MT6397_IRQ_ACCDET,
	MT6397_IRQ_AUDIO,
	MT6397_IRQ_RTC,
	MT6397_IRQ_PWRKEY_RSTB,
	MT6397_IRQ_HDMI_SIFM,
	MT6397_IRQ_HDMI_CEC,
	MT6397_IRQ_VCA15,
	MT6397_IRQ_VSRMCA15,
	MT6397_IRQ_VCORE,
	MT6397_IRQ_VGPU,
	MT6397_IRQ_VIO18,
	MT6397_IRQ_VPCA7,
	MT6397_IRQ_VSRMCA7,
	MT6397_IRQ_VDRM,
	MT6397_IRQ_NR,
पूर्ण;

काष्ठा mt6397_chip अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा notअगरier_block pm_nb;
	पूर्णांक irq;
	काष्ठा irq_करोमुख्य *irq_करोमुख्य;
	काष्ठा mutex irqlock;
	u16 wake_mask[2];
	u16 irq_masks_cur[2];
	u16 irq_masks_cache[2];
	u16 पूर्णांक_con[2];
	u16 पूर्णांक_status[2];
	u16 chip_id;
	व्योम *irq_data;
पूर्ण;

पूर्णांक mt6358_irq_init(काष्ठा mt6397_chip *chip);
पूर्णांक mt6397_irq_init(काष्ठा mt6397_chip *chip);

#पूर्ण_अगर /* __MFD_MT6397_CORE_H__ */
