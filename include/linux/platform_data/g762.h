<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Platक्रमm data काष्ठाure क्रम g762 fan controller driver
 *
 * Copyright (C) 2013, Arnaud EBALARD <arno@natisbad.org>
 */
#अगर_अघोषित __LINUX_PLATFORM_DATA_G762_H__
#घोषणा __LINUX_PLATFORM_DATA_G762_H__

/*
 * Following काष्ठाure can be used to set g762 driver platक्रमm specअगरic data
 * during board init. Note that passing a sparse काष्ठाure is possible but
 * will result in non-specअगरied attributes to be set to शेष value, hence
 * overloading those installed during boot (e.g. by u-boot).
 */

काष्ठा g762_platक्रमm_data अणु
	u32 fan_startv;
	u32 fan_gear_mode;
	u32 pwm_polarity;
	u32 clk_freq;
पूर्ण;

#पूर्ण_अगर /* __LINUX_PLATFORM_DATA_G762_H__ */
