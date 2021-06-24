<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * linux/sound/wm8996.h -- Platक्रमm data क्रम WM8996
 *
 * Copyright 2011 Wolfson Microelectronics. PLC.
 */

#अगर_अघोषित __LINUX_SND_WM8996_H
#घोषणा __LINUX_SND_WM8996_H

क्रमागत wm8996_inmode अणु
	WM8996_DIFFERRENTIAL_1 = 0,   /* IN1xP - IN1xN */
	WM8996_INVERTING = 1,         /* IN1xN */
	WM8996_NON_INVERTING = 2,     /* IN1xP */
	WM8996_DIFFERENTIAL_2 = 3,    /* IN2xP - IN2xP */
पूर्ण;

/**
 * ReTune Mobile configurations are specअगरied with a label, sample
 * rate and set of values to ग_लिखो (the enable bits will be ignored).
 *
 * Configurations are expected to be generated using the ReTune Mobile
 * control panel in WISCE - see http://www.wolfsonmicro.com/wisce/
 */
काष्ठा wm8996_retune_mobile_config अणु
	स्थिर अक्षर *name;
	पूर्णांक rate;
	u16 regs[20];
पूर्ण;

#घोषणा WM8996_SET_DEFAULT 0x10000

काष्ठा wm8996_pdata अणु
	पूर्णांक irq_flags;  /** Set IRQ trigger flags; शेष active low */

	पूर्णांक lकरो_ena;  /** GPIO क्रम LDO1; -1 क्रम none */

	पूर्णांक micdet_def;  /** Default MICDET_SRC/HP1FB_SRC/MICD_BIAS */

	क्रमागत wm8996_inmode inl_mode;
	क्रमागत wm8996_inmode inr_mode;

	u32 spkmute_seq;  /** Value क्रम रेजिस्टर 0x802 */

	पूर्णांक gpio_base;
	u32 gpio_शेष[5];

	पूर्णांक num_retune_mobile_cfgs;
	काष्ठा wm8996_retune_mobile_config *retune_mobile_cfgs;
पूर्ण;

#पूर्ण_अगर
