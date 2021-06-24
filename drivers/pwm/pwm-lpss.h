<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Intel Low Power Subप्रणाली PWM controller driver
 *
 * Copyright (C) 2014, Intel Corporation
 *
 * Derived from the original pwm-lpss.c
 */

#अगर_अघोषित __PWM_LPSS_H
#घोषणा __PWM_LPSS_H

#समावेश <linux/device.h>
#समावेश <linux/pwm.h>

#घोषणा MAX_PWMS			4

काष्ठा pwm_lpss_chip अणु
	काष्ठा pwm_chip chip;
	व्योम __iomem *regs;
	स्थिर काष्ठा pwm_lpss_boardinfo *info;
पूर्ण;

काष्ठा pwm_lpss_boardinfo अणु
	अचिन्हित दीर्घ clk_rate;
	अचिन्हित पूर्णांक npwm;
	अचिन्हित दीर्घ base_unit_bits;
	bool bypass;
	/*
	 * On some devices the _PS0/_PS3 AML code of the GPU (GFX0) device
	 * messes with the PWM0 controllers state,
	 */
	bool other_devices_aml_touches_pwm_regs;
पूर्ण;

काष्ठा pwm_lpss_chip *pwm_lpss_probe(काष्ठा device *dev, काष्ठा resource *r,
				     स्थिर काष्ठा pwm_lpss_boardinfo *info);
पूर्णांक pwm_lpss_हटाओ(काष्ठा pwm_lpss_chip *lpwm);

#पूर्ण_अगर	/* __PWM_LPSS_H */
