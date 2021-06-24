<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित DDK750_POWER_H__
#घोषणा DDK750_POWER_H__

क्रमागत dpms अणु
	crtDPMS_ON = 0x0,
	crtDPMS_STANDBY = 0x1,
	crtDPMS_SUSPEND = 0x2,
	crtDPMS_OFF = 0x3,
पूर्ण;

#घोषणा set_DAC(off) अणु							\
	poke32(MISC_CTRL,						\
	       (peek32(MISC_CTRL) & ~MISC_CTRL_DAC_POWER_OFF) | (off)); \
पूर्ण

व्योम ddk750_set_dpms(क्रमागत dpms state);
व्योम sm750_set_घातer_mode(अचिन्हित पूर्णांक घातerMode);
व्योम sm750_set_current_gate(अचिन्हित पूर्णांक gate);

/*
 * This function enable/disable the 2D engine.
 */
व्योम sm750_enable_2d_engine(अचिन्हित पूर्णांक enable);

/*
 * This function enable/disable the DMA Engine
 */
व्योम sm750_enable_dma(अचिन्हित पूर्णांक enable);

/*
 * This function enable/disable the GPIO Engine
 */
व्योम sm750_enable_gpio(अचिन्हित पूर्णांक enable);

/*
 * This function enable/disable the I2C Engine
 */
व्योम sm750_enable_i2c(अचिन्हित पूर्णांक enable);

#पूर्ण_अगर
