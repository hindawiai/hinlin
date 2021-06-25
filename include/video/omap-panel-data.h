<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Header containing platक्रमm_data काष्ठाs क्रम omap panels
 *
 * Copyright (C) 2013 Texas Instruments
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 *	   Archit Taneja <archit@ti.com>
 *
 * Copyright (C) 2011 Texas Instruments
 * Author: Mayuresh Janorkar <mayur@ti.com>
 *
 * Copyright (C) 2010 Canonical Ltd.
 * Author: Bryan Wu <bryan.wu@canonical.com>
 */

#अगर_अघोषित __OMAP_PANEL_DATA_H
#घोषणा __OMAP_PANEL_DATA_H

#समावेश <video/display_timing.h>

/**
 * connector_atv platक्रमm data
 * @name: name क्रम this display entity
 * @source: name of the display entity used as a video source
 * @invert_polarity: invert संकेत polarity
 */
काष्ठा connector_atv_platक्रमm_data अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *source;

	bool invert_polarity;
पूर्ण;

/**
 * panel_dpi platक्रमm data
 * @name: name क्रम this display entity
 * @source: name of the display entity used as a video source
 * @data_lines: number of DPI datalines
 * @display_timing: timings क्रम this panel
 * @backlight_gpio: gpio to enable/disable the backlight (or -1)
 * @enable_gpio: gpio to enable/disable the panel (or -1)
 */
काष्ठा panel_dpi_platक्रमm_data अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *source;

	पूर्णांक data_lines;

	स्थिर काष्ठा display_timing *display_timing;

	पूर्णांक backlight_gpio;
	पूर्णांक enable_gpio;
पूर्ण;

/**
 * panel_acx565akm platक्रमm data
 * @name: name क्रम this display entity
 * @source: name of the display entity used as a video source
 * @reset_gpio: gpio to reset the panel (or -1)
 * @datapairs: number of SDI datapairs
 */
काष्ठा panel_acx565akm_platक्रमm_data अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *source;

	पूर्णांक reset_gpio;

	पूर्णांक datapairs;
पूर्ण;

#पूर्ण_अगर /* __OMAP_PANEL_DATA_H */
