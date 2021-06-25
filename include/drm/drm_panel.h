<शैली गुरु>
/*
 * Copyright (C) 2013, NVIDIA Corporation.  All rights reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sub license,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#अगर_अघोषित __DRM_PANEL_H__
#घोषणा __DRM_PANEL_H__

#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/list.h>

काष्ठा backlight_device;
काष्ठा device_node;
काष्ठा drm_connector;
काष्ठा drm_device;
काष्ठा drm_panel;
काष्ठा display_timing;

क्रमागत drm_panel_orientation;

/**
 * काष्ठा drm_panel_funcs - perक्रमm operations on a given panel
 *
 * The .prepare() function is typically called beक्रमe the display controller
 * starts to transmit video data. Panel drivers can use this to turn the panel
 * on and रुको क्रम it to become पढ़ोy. If additional configuration is required
 * (via a control bus such as I2C, SPI or DSI क्रम example) this is a good समय
 * to करो that.
 *
 * After the display controller has started transmitting video data, it's safe
 * to call the .enable() function. This will typically enable the backlight to
 * make the image on screen visible. Some panels require a certain amount of
 * समय or frames beक्रमe the image is displayed. This function is responsible
 * क्रम taking this पूर्णांकo account beक्रमe enabling the backlight to aव्योम visual
 * glitches.
 *
 * Beक्रमe stopping video transmission from the display controller it can be
 * necessary to turn off the panel to aव्योम visual glitches. This is करोne in
 * the .disable() function. Analogously to .enable() this typically involves
 * turning off the backlight and रुकोing क्रम some समय to make sure no image
 * is visible on the panel. It is then safe क्रम the display controller to
 * cease transmission of video data.
 *
 * To save घातer when no video data is transmitted, a driver can घातer करोwn
 * the panel. This is the job of the .unprepare() function.
 *
 * Backlight can be handled स्वतःmatically अगर configured using
 * drm_panel_of_backlight(). Then the driver करोes not need to implement the
 * functionality to enable/disable backlight.
 */
काष्ठा drm_panel_funcs अणु
	/**
	 * @prepare:
	 *
	 * Turn on panel and perक्रमm set up.
	 *
	 * This function is optional.
	 */
	पूर्णांक (*prepare)(काष्ठा drm_panel *panel);

	/**
	 * @enable:
	 *
	 * Enable panel (turn on back light, etc.).
	 *
	 * This function is optional.
	 */
	पूर्णांक (*enable)(काष्ठा drm_panel *panel);

	/**
	 * @disable:
	 *
	 * Disable panel (turn off back light, etc.).
	 *
	 * This function is optional.
	 */
	पूर्णांक (*disable)(काष्ठा drm_panel *panel);

	/**
	 * @unprepare:
	 *
	 * Turn off panel.
	 *
	 * This function is optional.
	 */
	पूर्णांक (*unprepare)(काष्ठा drm_panel *panel);

	/**
	 * @get_modes:
	 *
	 * Add modes to the connector that the panel is attached to
	 * and वापसs the number of modes added.
	 *
	 * This function is mandatory.
	 */
	पूर्णांक (*get_modes)(काष्ठा drm_panel *panel,
			 काष्ठा drm_connector *connector);

	/**
	 * @get_timings:
	 *
	 * Copy display timings पूर्णांकo the provided array and वापस
	 * the number of display timings available.
	 *
	 * This function is optional.
	 */
	पूर्णांक (*get_timings)(काष्ठा drm_panel *panel, अचिन्हित पूर्णांक num_timings,
			   काष्ठा display_timing *timings);
पूर्ण;

/**
 * काष्ठा drm_panel - DRM panel object
 */
काष्ठा drm_panel अणु
	/**
	 * @dev:
	 *
	 * Parent device of the panel.
	 */
	काष्ठा device *dev;

	/**
	 * @backlight:
	 *
	 * Backlight device, used to turn on backlight after the call
	 * to enable(), and to turn off backlight beक्रमe the call to
	 * disable().
	 * backlight is set by drm_panel_of_backlight() and drivers
	 * shall not assign it.
	 */
	काष्ठा backlight_device *backlight;

	/**
	 * @funcs:
	 *
	 * Operations that can be perक्रमmed on the panel.
	 */
	स्थिर काष्ठा drm_panel_funcs *funcs;

	/**
	 * @connector_type:
	 *
	 * Type of the panel as a DRM_MODE_CONNECTOR_* value. This is used to
	 * initialise the drm_connector corresponding to the panel with the
	 * correct connector type.
	 */
	पूर्णांक connector_type;

	/**
	 * @list:
	 *
	 * Panel entry in registry.
	 */
	काष्ठा list_head list;
पूर्ण;

व्योम drm_panel_init(काष्ठा drm_panel *panel, काष्ठा device *dev,
		    स्थिर काष्ठा drm_panel_funcs *funcs,
		    पूर्णांक connector_type);

व्योम drm_panel_add(काष्ठा drm_panel *panel);
व्योम drm_panel_हटाओ(काष्ठा drm_panel *panel);

पूर्णांक drm_panel_prepare(काष्ठा drm_panel *panel);
पूर्णांक drm_panel_unprepare(काष्ठा drm_panel *panel);

पूर्णांक drm_panel_enable(काष्ठा drm_panel *panel);
पूर्णांक drm_panel_disable(काष्ठा drm_panel *panel);

पूर्णांक drm_panel_get_modes(काष्ठा drm_panel *panel, काष्ठा drm_connector *connector);

#अगर defined(CONFIG_OF) && defined(CONFIG_DRM_PANEL)
काष्ठा drm_panel *of_drm_find_panel(स्थिर काष्ठा device_node *np);
पूर्णांक of_drm_get_panel_orientation(स्थिर काष्ठा device_node *np,
				 क्रमागत drm_panel_orientation *orientation);
#अन्यथा
अटल अंतरभूत काष्ठा drm_panel *of_drm_find_panel(स्थिर काष्ठा device_node *np)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत पूर्णांक of_drm_get_panel_orientation(स्थिर काष्ठा device_node *np,
					       क्रमागत drm_panel_orientation *orientation)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_DRM_PANEL) && (IS_BUILTIN(CONFIG_BACKLIGHT_CLASS_DEVICE) || \
	(IS_MODULE(CONFIG_DRM) && IS_MODULE(CONFIG_BACKLIGHT_CLASS_DEVICE)))
पूर्णांक drm_panel_of_backlight(काष्ठा drm_panel *panel);
#अन्यथा
अटल अंतरभूत पूर्णांक drm_panel_of_backlight(काष्ठा drm_panel *panel)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
