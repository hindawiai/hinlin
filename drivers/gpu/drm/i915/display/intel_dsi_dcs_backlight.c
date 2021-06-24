<शैली गुरु>
/*
 * Copyright तऊ 2016 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Author: Deepak M <m.deepak at पूर्णांकel.com>
 */

#समावेश <drm/drm_mipi_dsi.h>
#समावेश <video/mipi_display.h>

#समावेश "i915_drv.h"
#समावेश "intel_display_types.h"
#समावेश "intel_dsi.h"
#समावेश "intel_dsi_dcs_backlight.h"

#घोषणा CONTROL_DISPLAY_BCTRL		(1 << 5)
#घोषणा CONTROL_DISPLAY_DD		(1 << 3)
#घोषणा CONTROL_DISPLAY_BL		(1 << 2)

#घोषणा POWER_SAVE_OFF			(0 << 0)
#घोषणा POWER_SAVE_LOW			(1 << 0)
#घोषणा POWER_SAVE_MEDIUM		(2 << 0)
#घोषणा POWER_SAVE_HIGH			(3 << 0)
#घोषणा POWER_SAVE_OUTDOOR_MODE		(4 << 0)

#घोषणा PANEL_PWM_MAX_VALUE		0xFF

अटल u32 dcs_get_backlight(काष्ठा पूर्णांकel_connector *connector, क्रमागत pipe unused)
अणु
	काष्ठा पूर्णांकel_encoder *encoder = पूर्णांकel_attached_encoder(connector);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	काष्ठा mipi_dsi_device *dsi_device;
	u8 data = 0;
	क्रमागत port port;

	/* FIXME: Need to take care of 16 bit brightness level */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->dcs_backlight_ports) अणु
		dsi_device = पूर्णांकel_dsi->dsi_hosts[port]->device;
		mipi_dsi_dcs_पढ़ो(dsi_device, MIPI_DCS_GET_DISPLAY_BRIGHTNESS,
				  &data, माप(data));
		अवरोध;
	पूर्ण

	वापस data;
पूर्ण

अटल व्योम dcs_set_backlight(स्थिर काष्ठा drm_connector_state *conn_state, u32 level)
अणु
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(to_पूर्णांकel_encoder(conn_state->best_encoder));
	काष्ठा mipi_dsi_device *dsi_device;
	u8 data = level;
	क्रमागत port port;

	/* FIXME: Need to take care of 16 bit brightness level */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->dcs_backlight_ports) अणु
		dsi_device = पूर्णांकel_dsi->dsi_hosts[port]->device;
		mipi_dsi_dcs_ग_लिखो(dsi_device, MIPI_DCS_SET_DISPLAY_BRIGHTNESS,
				   &data, माप(data));
	पूर्ण
पूर्ण

अटल व्योम dcs_disable_backlight(स्थिर काष्ठा drm_connector_state *conn_state, u32 level)
अणु
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(to_पूर्णांकel_encoder(conn_state->best_encoder));
	काष्ठा mipi_dsi_device *dsi_device;
	क्रमागत port port;

	dcs_set_backlight(conn_state, 0);

	क्रम_each_dsi_port(port, पूर्णांकel_dsi->dcs_cabc_ports) अणु
		u8 cabc = POWER_SAVE_OFF;

		dsi_device = पूर्णांकel_dsi->dsi_hosts[port]->device;
		mipi_dsi_dcs_ग_लिखो(dsi_device, MIPI_DCS_WRITE_POWER_SAVE,
				   &cabc, माप(cabc));
	पूर्ण

	क्रम_each_dsi_port(port, पूर्णांकel_dsi->dcs_backlight_ports) अणु
		u8 ctrl = 0;

		dsi_device = पूर्णांकel_dsi->dsi_hosts[port]->device;

		mipi_dsi_dcs_पढ़ो(dsi_device, MIPI_DCS_GET_CONTROL_DISPLAY,
				  &ctrl, माप(ctrl));

		ctrl &= ~CONTROL_DISPLAY_BL;
		ctrl &= ~CONTROL_DISPLAY_DD;
		ctrl &= ~CONTROL_DISPLAY_BCTRL;

		mipi_dsi_dcs_ग_लिखो(dsi_device, MIPI_DCS_WRITE_CONTROL_DISPLAY,
				   &ctrl, माप(ctrl));
	पूर्ण
पूर्ण

अटल व्योम dcs_enable_backlight(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				 स्थिर काष्ठा drm_connector_state *conn_state, u32 level)
अणु
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(to_पूर्णांकel_encoder(conn_state->best_encoder));
	काष्ठा mipi_dsi_device *dsi_device;
	क्रमागत port port;

	क्रम_each_dsi_port(port, पूर्णांकel_dsi->dcs_backlight_ports) अणु
		u8 ctrl = 0;

		dsi_device = पूर्णांकel_dsi->dsi_hosts[port]->device;

		mipi_dsi_dcs_पढ़ो(dsi_device, MIPI_DCS_GET_CONTROL_DISPLAY,
				  &ctrl, माप(ctrl));

		ctrl |= CONTROL_DISPLAY_BL;
		ctrl |= CONTROL_DISPLAY_DD;
		ctrl |= CONTROL_DISPLAY_BCTRL;

		mipi_dsi_dcs_ग_लिखो(dsi_device, MIPI_DCS_WRITE_CONTROL_DISPLAY,
				   &ctrl, माप(ctrl));
	पूर्ण

	क्रम_each_dsi_port(port, पूर्णांकel_dsi->dcs_cabc_ports) अणु
		u8 cabc = POWER_SAVE_MEDIUM;

		dsi_device = पूर्णांकel_dsi->dsi_hosts[port]->device;
		mipi_dsi_dcs_ग_लिखो(dsi_device, MIPI_DCS_WRITE_POWER_SAVE,
				   &cabc, माप(cabc));
	पूर्ण

	dcs_set_backlight(conn_state, level);
पूर्ण

अटल पूर्णांक dcs_setup_backlight(काष्ठा पूर्णांकel_connector *connector,
			       क्रमागत pipe unused)
अणु
	काष्ठा पूर्णांकel_panel *panel = &connector->panel;

	panel->backlight.max = PANEL_PWM_MAX_VALUE;
	panel->backlight.level = PANEL_PWM_MAX_VALUE;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_panel_bl_funcs dcs_bl_funcs = अणु
	.setup = dcs_setup_backlight,
	.enable = dcs_enable_backlight,
	.disable = dcs_disable_backlight,
	.set = dcs_set_backlight,
	.get = dcs_get_backlight,
पूर्ण;

पूर्णांक पूर्णांकel_dsi_dcs_init_backlight_funcs(काष्ठा पूर्णांकel_connector *पूर्णांकel_connector)
अणु
	काष्ठा drm_device *dev = पूर्णांकel_connector->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_encoder *encoder = पूर्णांकel_attached_encoder(पूर्णांकel_connector);
	काष्ठा पूर्णांकel_panel *panel = &पूर्णांकel_connector->panel;

	अगर (dev_priv->vbt.backlight.type != INTEL_BACKLIGHT_DSI_DCS)
		वापस -ENODEV;

	अगर (drm_WARN_ON(dev, encoder->type != INTEL_OUTPUT_DSI))
		वापस -EINVAL;

	panel->backlight.funcs = &dcs_bl_funcs;

	वापस 0;
पूर्ण
