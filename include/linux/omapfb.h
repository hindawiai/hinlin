<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * File: include/linux/omapfb.h
 *
 * Framebuffer driver क्रम TI OMAP boards
 *
 * Copyright (C) 2004 Nokia Corporation
 * Author: Imre Deak <imre.deak@nokia.com>
 */
#अगर_अघोषित __LINUX_OMAPFB_H__
#घोषणा __LINUX_OMAPFB_H__

#समावेश <uapi/linux/omapfb.h>


काष्ठा omap_lcd_config अणु
	अक्षर panel_name[16];
	अक्षर ctrl_name[16];
	s16  nreset_gpio;
	u8   data_lines;
पूर्ण;

काष्ठा omapfb_platक्रमm_data अणु
	काष्ठा omap_lcd_config		lcd;
पूर्ण;

व्योम __init omapfb_set_lcd_config(स्थिर काष्ठा omap_lcd_config *config);

#पूर्ण_अगर /* __OMAPFB_H */
