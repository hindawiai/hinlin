<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * include/linux/input/ad714x.h
 *
 * AD714x is very flexible, it can be used as buttons, scrollwheel,
 * slider, touchpad at the same समय. That depends on the boards.
 * The platक्रमm_data क्रम the device's "struct device" holds this
 * inक्रमmation.
 *
 * Copyright 2009-2011 Analog Devices Inc.
 */

#अगर_अघोषित __LINUX_INPUT_AD714X_H__
#घोषणा __LINUX_INPUT_AD714X_H__

#घोषणा STAGE_NUM              12
#घोषणा STAGE_CFGREG_NUM       8
#घोषणा SYS_CFGREG_NUM         8

/* board inक्रमmation which need be initialized in arch/mach... */
काष्ठा ad714x_slider_plat अणु
	पूर्णांक start_stage;
	पूर्णांक end_stage;
	पूर्णांक max_coord;
पूर्ण;

काष्ठा ad714x_wheel_plat अणु
	पूर्णांक start_stage;
	पूर्णांक end_stage;
	पूर्णांक max_coord;
पूर्ण;

काष्ठा ad714x_touchpad_plat अणु
	पूर्णांक x_start_stage;
	पूर्णांक x_end_stage;
	पूर्णांक x_max_coord;

	पूर्णांक y_start_stage;
	पूर्णांक y_end_stage;
	पूर्णांक y_max_coord;
पूर्ण;

काष्ठा ad714x_button_plat अणु
	पूर्णांक keycode;
	अचिन्हित लघु l_mask;
	अचिन्हित लघु h_mask;
पूर्ण;

काष्ठा ad714x_platक्रमm_data अणु
	पूर्णांक slider_num;
	पूर्णांक wheel_num;
	पूर्णांक touchpad_num;
	पूर्णांक button_num;
	काष्ठा ad714x_slider_plat *slider;
	काष्ठा ad714x_wheel_plat *wheel;
	काष्ठा ad714x_touchpad_plat *touchpad;
	काष्ठा ad714x_button_plat *button;
	अचिन्हित लघु stage_cfg_reg[STAGE_NUM][STAGE_CFGREG_NUM];
	अचिन्हित लघु sys_cfg_reg[SYS_CFGREG_NUM];
	अचिन्हित दीर्घ irqflags;
पूर्ण;

#पूर्ण_अगर
