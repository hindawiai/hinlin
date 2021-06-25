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

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <video/display_timing.h>
#समावेश <video/of_display_timing.h>
#समावेश <video/videomode.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_panel.h>

/**
 * काष्ठा panel_desc - Describes a simple panel.
 */
काष्ठा panel_desc अणु
	/**
	 * @modes: Poपूर्णांकer to array of fixed modes appropriate क्रम this panel.
	 *
	 * If only one mode then this can just be the address of the mode.
	 * NOTE: cannot be used with "timings" and also अगर this is specअगरied
	 * then you cannot override the mode in the device tree.
	 */
	स्थिर काष्ठा drm_display_mode *modes;

	/** @num_modes: Number of elements in modes array. */
	अचिन्हित पूर्णांक num_modes;

	/**
	 * @timings: Poपूर्णांकer to array of display timings
	 *
	 * NOTE: cannot be used with "modes" and also these will be used to
	 * validate a device tree override अगर one is present.
	 */
	स्थिर काष्ठा display_timing *timings;

	/** @num_timings: Number of elements in timings array. */
	अचिन्हित पूर्णांक num_timings;

	/** @bpc: Bits per color. */
	अचिन्हित पूर्णांक bpc;

	/** @size: Structure containing the physical size of this panel. */
	काष्ठा अणु
		/**
		 * @size.width: Width (in mm) of the active display area.
		 */
		अचिन्हित पूर्णांक width;

		/**
		 * @size.height: Height (in mm) of the active display area.
		 */
		अचिन्हित पूर्णांक height;
	पूर्ण size;

	/** @delay: Structure containing various delay values क्रम this panel. */
	काष्ठा अणु
		/**
		 * @delay.prepare: Time क्रम the panel to become पढ़ोy.
		 *
		 * The समय (in milliseconds) that it takes क्रम the panel to
		 * become पढ़ोy and start receiving video data
		 */
		अचिन्हित पूर्णांक prepare;

		/**
		 * @delay.hpd_असलent_delay: Time to रुको अगर HPD isn't hooked up.
		 *
		 * Add this to the prepare delay अगर we know Hot Plug Detect
		 * isn't used.
		 */
		अचिन्हित पूर्णांक hpd_असलent_delay;

		/**
		 * @delay.prepare_to_enable: Time between prepare and enable.
		 *
		 * The minimum समय, in milliseconds, that needs to have passed
		 * between when prepare finished and enable may begin. If at
		 * enable समय less समय has passed since prepare finished,
		 * the driver रुकोs क्रम the reमुख्यing समय.
		 *
		 * If a fixed enable delay is also specअगरied, we'll start
		 * counting beक्रमe delaying क्रम the fixed delay.
		 *
		 * If a fixed prepare delay is also specअगरied, we won't start
		 * counting until after the fixed delay. We can't overlap this
		 * fixed delay with the min समय because the fixed delay
		 * करोesn't happen at the end of the function अगर a HPD GPIO was
		 * specअगरied.
		 *
		 * In other words:
		 *   prepare()
		 *     ...
		 *     // करो fixed prepare delay
		 *     // रुको क्रम HPD GPIO अगर applicable
		 *     // start counting क्रम prepare_to_enable
		 *
		 *   enable()
		 *     // करो fixed enable delay
		 *     // enक्रमce prepare_to_enable min समय
		 */
		अचिन्हित पूर्णांक prepare_to_enable;

		/**
		 * @delay.enable: Time क्रम the panel to display a valid frame.
		 *
		 * The समय (in milliseconds) that it takes क्रम the panel to
		 * display the first valid frame after starting to receive
		 * video data.
		 */
		अचिन्हित पूर्णांक enable;

		/**
		 * @delay.disable: Time क्रम the panel to turn the display off.
		 *
		 * The समय (in milliseconds) that it takes क्रम the panel to
		 * turn the display off (no content is visible).
		 */
		अचिन्हित पूर्णांक disable;

		/**
		 * @delay.unprepare: Time to घातer करोwn completely.
		 *
		 * The समय (in milliseconds) that it takes क्रम the panel
		 * to घातer itself करोwn completely.
		 *
		 * This समय is used to prevent a future "prepare" from
		 * starting until at least this many milliseconds has passed.
		 * If at prepare समय less समय has passed since unprepare
		 * finished, the driver रुकोs क्रम the reमुख्यing समय.
		 */
		अचिन्हित पूर्णांक unprepare;
	पूर्ण delay;

	/** @bus_क्रमmat: See MEDIA_BUS_FMT_... defines. */
	u32 bus_क्रमmat;

	/** @bus_flags: See DRM_BUS_FLAG_... defines. */
	u32 bus_flags;

	/** @connector_type: LVDS, eDP, DSI, DPI, etc. */
	पूर्णांक connector_type;
पूर्ण;

काष्ठा panel_simple अणु
	काष्ठा drm_panel base;
	bool enabled;
	bool no_hpd;

	kसमय_प्रकार prepared_समय;
	kसमय_प्रकार unprepared_समय;

	स्थिर काष्ठा panel_desc *desc;

	काष्ठा regulator *supply;
	काष्ठा i2c_adapter *ddc;

	काष्ठा gpio_desc *enable_gpio;
	काष्ठा gpio_desc *hpd_gpio;

	काष्ठा drm_display_mode override_mode;

	क्रमागत drm_panel_orientation orientation;
पूर्ण;

अटल अंतरभूत काष्ठा panel_simple *to_panel_simple(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा panel_simple, base);
पूर्ण

अटल अचिन्हित पूर्णांक panel_simple_get_timings_modes(काष्ठा panel_simple *panel,
						   काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_display_mode *mode;
	अचिन्हित पूर्णांक i, num = 0;

	क्रम (i = 0; i < panel->desc->num_timings; i++) अणु
		स्थिर काष्ठा display_timing *dt = &panel->desc->timings[i];
		काष्ठा videomode vm;

		videomode_from_timing(dt, &vm);
		mode = drm_mode_create(connector->dev);
		अगर (!mode) अणु
			dev_err(panel->base.dev, "failed to add mode %ux%u\n",
				dt->hactive.typ, dt->vactive.typ);
			जारी;
		पूर्ण

		drm_display_mode_from_videomode(&vm, mode);

		mode->type |= DRM_MODE_TYPE_DRIVER;

		अगर (panel->desc->num_timings == 1)
			mode->type |= DRM_MODE_TYPE_PREFERRED;

		drm_mode_probed_add(connector, mode);
		num++;
	पूर्ण

	वापस num;
पूर्ण

अटल अचिन्हित पूर्णांक panel_simple_get_display_modes(काष्ठा panel_simple *panel,
						   काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_display_mode *mode;
	अचिन्हित पूर्णांक i, num = 0;

	क्रम (i = 0; i < panel->desc->num_modes; i++) अणु
		स्थिर काष्ठा drm_display_mode *m = &panel->desc->modes[i];

		mode = drm_mode_duplicate(connector->dev, m);
		अगर (!mode) अणु
			dev_err(panel->base.dev, "failed to add mode %ux%u@%u\n",
				m->hdisplay, m->vdisplay,
				drm_mode_vrefresh(m));
			जारी;
		पूर्ण

		mode->type |= DRM_MODE_TYPE_DRIVER;

		अगर (panel->desc->num_modes == 1)
			mode->type |= DRM_MODE_TYPE_PREFERRED;

		drm_mode_set_name(mode);

		drm_mode_probed_add(connector, mode);
		num++;
	पूर्ण

	वापस num;
पूर्ण

अटल पूर्णांक panel_simple_get_non_edid_modes(काष्ठा panel_simple *panel,
					   काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_display_mode *mode;
	bool has_override = panel->override_mode.type;
	अचिन्हित पूर्णांक num = 0;

	अगर (!panel->desc)
		वापस 0;

	अगर (has_override) अणु
		mode = drm_mode_duplicate(connector->dev,
					  &panel->override_mode);
		अगर (mode) अणु
			drm_mode_probed_add(connector, mode);
			num = 1;
		पूर्ण अन्यथा अणु
			dev_err(panel->base.dev, "failed to add override mode\n");
		पूर्ण
	पूर्ण

	/* Only add timings अगर override was not there or failed to validate */
	अगर (num == 0 && panel->desc->num_timings)
		num = panel_simple_get_timings_modes(panel, connector);

	/*
	 * Only add fixed modes अगर timings/override added no mode.
	 *
	 * We should only ever have either the display timings specअगरied
	 * or a fixed mode. Anything अन्यथा is rather bogus.
	 */
	WARN_ON(panel->desc->num_timings && panel->desc->num_modes);
	अगर (num == 0)
		num = panel_simple_get_display_modes(panel, connector);

	connector->display_info.bpc = panel->desc->bpc;
	connector->display_info.width_mm = panel->desc->size.width;
	connector->display_info.height_mm = panel->desc->size.height;
	अगर (panel->desc->bus_क्रमmat)
		drm_display_info_set_bus_क्रमmats(&connector->display_info,
						 &panel->desc->bus_क्रमmat, 1);
	connector->display_info.bus_flags = panel->desc->bus_flags;

	वापस num;
पूर्ण

अटल व्योम panel_simple_रुको(kसमय_प्रकार start_kसमय, अचिन्हित पूर्णांक min_ms)
अणु
	kसमय_प्रकार now_kसमय, min_kसमय;

	अगर (!min_ms)
		वापस;

	min_kसमय = kसमय_add(start_kसमय, ms_to_kसमय(min_ms));
	now_kसमय = kसमय_get();

	अगर (kसमय_beक्रमe(now_kसमय, min_kसमय))
		msleep(kसमय_प्रकारo_ms(kसमय_sub(min_kसमय, now_kसमय)) + 1);
पूर्ण

अटल पूर्णांक panel_simple_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा panel_simple *p = to_panel_simple(panel);

	अगर (!p->enabled)
		वापस 0;

	अगर (p->desc->delay.disable)
		msleep(p->desc->delay.disable);

	p->enabled = false;

	वापस 0;
पूर्ण

अटल पूर्णांक panel_simple_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा panel_simple *p = to_panel_simple(panel);

	अगर (p->prepared_समय == 0)
		वापस 0;

	gpiod_set_value_cansleep(p->enable_gpio, 0);

	regulator_disable(p->supply);

	p->prepared_समय = 0;
	p->unprepared_समय = kसमय_get();

	वापस 0;
पूर्ण

अटल पूर्णांक panel_simple_get_hpd_gpio(काष्ठा device *dev,
				     काष्ठा panel_simple *p, bool from_probe)
अणु
	पूर्णांक err;

	p->hpd_gpio = devm_gpiod_get_optional(dev, "hpd", GPIOD_IN);
	अगर (IS_ERR(p->hpd_gpio)) अणु
		err = PTR_ERR(p->hpd_gpio);

		/*
		 * If we're called from probe we won't consider '-EPROBE_DEFER'
		 * to be an error--we'll leave the error code in "hpd_gpio".
		 * When we try to use it we'll try again.  This allows क्रम
		 * circular dependencies where the component providing the
		 * hpd gpio needs the panel to init beक्रमe probing.
		 */
		अगर (err != -EPROBE_DEFER || !from_probe) अणु
			dev_err(dev, "failed to get 'hpd' GPIO: %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक panel_simple_prepare_once(काष्ठा drm_panel *panel)
अणु
	काष्ठा panel_simple *p = to_panel_simple(panel);
	अचिन्हित पूर्णांक delay;
	पूर्णांक err;
	पूर्णांक hpd_निश्चितed;
	अचिन्हित दीर्घ hpd_रुको_us;

	अगर (p->prepared_समय != 0)
		वापस 0;

	panel_simple_रुको(p->unprepared_समय, p->desc->delay.unprepare);

	err = regulator_enable(p->supply);
	अगर (err < 0) अणु
		dev_err(panel->dev, "failed to enable supply: %d\n", err);
		वापस err;
	पूर्ण

	gpiod_set_value_cansleep(p->enable_gpio, 1);

	delay = p->desc->delay.prepare;
	अगर (p->no_hpd)
		delay += p->desc->delay.hpd_असलent_delay;
	अगर (delay)
		msleep(delay);

	अगर (p->hpd_gpio) अणु
		अगर (IS_ERR(p->hpd_gpio)) अणु
			err = panel_simple_get_hpd_gpio(panel->dev, p, false);
			अगर (err)
				जाओ error;
		पूर्ण

		अगर (p->desc->delay.hpd_असलent_delay)
			hpd_रुको_us = p->desc->delay.hpd_असलent_delay * 1000UL;
		अन्यथा
			hpd_रुको_us = 2000000;

		err = पढ़ोx_poll_समयout(gpiod_get_value_cansleep, p->hpd_gpio,
					 hpd_निश्चितed, hpd_निश्चितed,
					 1000, hpd_रुको_us);
		अगर (hpd_निश्चितed < 0)
			err = hpd_निश्चितed;

		अगर (err) अणु
			अगर (err != -ETIMEDOUT)
				dev_err(panel->dev,
					"error waiting for hpd GPIO: %d\n", err);
			जाओ error;
		पूर्ण
	पूर्ण

	p->prepared_समय = kसमय_get();

	वापस 0;

error:
	gpiod_set_value_cansleep(p->enable_gpio, 0);
	regulator_disable(p->supply);
	p->unprepared_समय = kसमय_get();

	वापस err;
पूर्ण

/*
 * Some panels simply करोn't always come up and need to be घातer cycled to
 * work properly.  We'll allow क्रम a handful of retries.
 */
#घोषणा MAX_PANEL_PREPARE_TRIES		5

अटल पूर्णांक panel_simple_prepare(काष्ठा drm_panel *panel)
अणु
	पूर्णांक ret;
	पूर्णांक try;

	क्रम (try = 0; try < MAX_PANEL_PREPARE_TRIES; try++) अणु
		ret = panel_simple_prepare_once(panel);
		अगर (ret != -ETIMEDOUT)
			अवरोध;
	पूर्ण

	अगर (ret == -ETIMEDOUT)
		dev_err(panel->dev, "Prepare timeout after %d tries\n", try);
	अन्यथा अगर (try)
		dev_warn(panel->dev, "Prepare needed %d retries\n", try);

	वापस ret;
पूर्ण

अटल पूर्णांक panel_simple_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा panel_simple *p = to_panel_simple(panel);

	अगर (p->enabled)
		वापस 0;

	अगर (p->desc->delay.enable)
		msleep(p->desc->delay.enable);

	panel_simple_रुको(p->prepared_समय, p->desc->delay.prepare_to_enable);

	p->enabled = true;

	वापस 0;
पूर्ण

अटल पूर्णांक panel_simple_get_modes(काष्ठा drm_panel *panel,
				  काष्ठा drm_connector *connector)
अणु
	काष्ठा panel_simple *p = to_panel_simple(panel);
	पूर्णांक num = 0;

	/* probe EDID अगर a DDC bus is available */
	अगर (p->ddc) अणु
		काष्ठा edid *edid = drm_get_edid(connector, p->ddc);

		drm_connector_update_edid_property(connector, edid);
		अगर (edid) अणु
			num += drm_add_edid_modes(connector, edid);
			kमुक्त(edid);
		पूर्ण
	पूर्ण

	/* add hard-coded panel modes */
	num += panel_simple_get_non_edid_modes(p, connector);

	/* set up connector's "panel orientation" property */
	drm_connector_set_panel_orientation(connector, p->orientation);

	वापस num;
पूर्ण

अटल पूर्णांक panel_simple_get_timings(काष्ठा drm_panel *panel,
				    अचिन्हित पूर्णांक num_timings,
				    काष्ठा display_timing *timings)
अणु
	काष्ठा panel_simple *p = to_panel_simple(panel);
	अचिन्हित पूर्णांक i;

	अगर (p->desc->num_timings < num_timings)
		num_timings = p->desc->num_timings;

	अगर (timings)
		क्रम (i = 0; i < num_timings; i++)
			timings[i] = p->desc->timings[i];

	वापस p->desc->num_timings;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs panel_simple_funcs = अणु
	.disable = panel_simple_disable,
	.unprepare = panel_simple_unprepare,
	.prepare = panel_simple_prepare,
	.enable = panel_simple_enable,
	.get_modes = panel_simple_get_modes,
	.get_timings = panel_simple_get_timings,
पूर्ण;

अटल काष्ठा panel_desc panel_dpi;

अटल पूर्णांक panel_dpi_probe(काष्ठा device *dev,
			   काष्ठा panel_simple *panel)
अणु
	काष्ठा display_timing *timing;
	स्थिर काष्ठा device_node *np;
	काष्ठा panel_desc *desc;
	अचिन्हित पूर्णांक bus_flags;
	काष्ठा videomode vm;
	पूर्णांक ret;

	np = dev->of_node;
	desc = devm_kzalloc(dev, माप(*desc), GFP_KERNEL);
	अगर (!desc)
		वापस -ENOMEM;

	timing = devm_kzalloc(dev, माप(*timing), GFP_KERNEL);
	अगर (!timing)
		वापस -ENOMEM;

	ret = of_get_display_timing(np, "panel-timing", timing);
	अगर (ret < 0) अणु
		dev_err(dev, "%pOF: no panel-timing node found for \"panel-dpi\" binding\n",
			np);
		वापस ret;
	पूर्ण

	desc->timings = timing;
	desc->num_timings = 1;

	of_property_पढ़ो_u32(np, "width-mm", &desc->size.width);
	of_property_पढ़ो_u32(np, "height-mm", &desc->size.height);

	/* Extract bus_flags from display_timing */
	bus_flags = 0;
	vm.flags = timing->flags;
	drm_bus_flags_from_videomode(&vm, &bus_flags);
	desc->bus_flags = bus_flags;

	/* We करो not know the connector क्रम the DT node, so guess it */
	desc->connector_type = DRM_MODE_CONNECTOR_DPI;

	panel->desc = desc;

	वापस 0;
पूर्ण

#घोषणा PANEL_SIMPLE_BOUNDS_CHECK(to_check, bounds, field) \
	(to_check->field.typ >= bounds->field.min && \
	 to_check->field.typ <= bounds->field.max)
अटल व्योम panel_simple_parse_panel_timing_node(काष्ठा device *dev,
						 काष्ठा panel_simple *panel,
						 स्थिर काष्ठा display_timing *ot)
अणु
	स्थिर काष्ठा panel_desc *desc = panel->desc;
	काष्ठा videomode vm;
	अचिन्हित पूर्णांक i;

	अगर (WARN_ON(desc->num_modes)) अणु
		dev_err(dev, "Reject override mode: panel has a fixed mode\n");
		वापस;
	पूर्ण
	अगर (WARN_ON(!desc->num_timings)) अणु
		dev_err(dev, "Reject override mode: no timings specified\n");
		वापस;
	पूर्ण

	क्रम (i = 0; i < panel->desc->num_timings; i++) अणु
		स्थिर काष्ठा display_timing *dt = &panel->desc->timings[i];

		अगर (!PANEL_SIMPLE_BOUNDS_CHECK(ot, dt, hactive) ||
		    !PANEL_SIMPLE_BOUNDS_CHECK(ot, dt, hfront_porch) ||
		    !PANEL_SIMPLE_BOUNDS_CHECK(ot, dt, hback_porch) ||
		    !PANEL_SIMPLE_BOUNDS_CHECK(ot, dt, hsync_len) ||
		    !PANEL_SIMPLE_BOUNDS_CHECK(ot, dt, vactive) ||
		    !PANEL_SIMPLE_BOUNDS_CHECK(ot, dt, vfront_porch) ||
		    !PANEL_SIMPLE_BOUNDS_CHECK(ot, dt, vback_porch) ||
		    !PANEL_SIMPLE_BOUNDS_CHECK(ot, dt, vsync_len))
			जारी;

		अगर (ot->flags != dt->flags)
			जारी;

		videomode_from_timing(ot, &vm);
		drm_display_mode_from_videomode(&vm, &panel->override_mode);
		panel->override_mode.type |= DRM_MODE_TYPE_DRIVER |
					     DRM_MODE_TYPE_PREFERRED;
		अवरोध;
	पूर्ण

	अगर (WARN_ON(!panel->override_mode.type))
		dev_err(dev, "Reject override mode: No display_timing found\n");
पूर्ण

अटल पूर्णांक panel_simple_probe(काष्ठा device *dev, स्थिर काष्ठा panel_desc *desc)
अणु
	काष्ठा panel_simple *panel;
	काष्ठा display_timing dt;
	काष्ठा device_node *ddc;
	पूर्णांक connector_type;
	u32 bus_flags;
	पूर्णांक err;

	panel = devm_kzalloc(dev, माप(*panel), GFP_KERNEL);
	अगर (!panel)
		वापस -ENOMEM;

	panel->enabled = false;
	panel->prepared_समय = 0;
	panel->desc = desc;

	panel->no_hpd = of_property_पढ़ो_bool(dev->of_node, "no-hpd");
	अगर (!panel->no_hpd) अणु
		err = panel_simple_get_hpd_gpio(dev, panel, true);
		अगर (err)
			वापस err;
	पूर्ण

	panel->supply = devm_regulator_get(dev, "power");
	अगर (IS_ERR(panel->supply))
		वापस PTR_ERR(panel->supply);

	panel->enable_gpio = devm_gpiod_get_optional(dev, "enable",
						     GPIOD_OUT_LOW);
	अगर (IS_ERR(panel->enable_gpio)) अणु
		err = PTR_ERR(panel->enable_gpio);
		अगर (err != -EPROBE_DEFER)
			dev_err(dev, "failed to request GPIO: %d\n", err);
		वापस err;
	पूर्ण

	err = of_drm_get_panel_orientation(dev->of_node, &panel->orientation);
	अगर (err) अणु
		dev_err(dev, "%pOF: failed to get orientation %d\n", dev->of_node, err);
		वापस err;
	पूर्ण

	ddc = of_parse_phandle(dev->of_node, "ddc-i2c-bus", 0);
	अगर (ddc) अणु
		panel->ddc = of_find_i2c_adapter_by_node(ddc);
		of_node_put(ddc);

		अगर (!panel->ddc)
			वापस -EPROBE_DEFER;
	पूर्ण

	अगर (desc == &panel_dpi) अणु
		/* Handle the generic panel-dpi binding */
		err = panel_dpi_probe(dev, panel);
		अगर (err)
			जाओ मुक्त_ddc;
	पूर्ण अन्यथा अणु
		अगर (!of_get_display_timing(dev->of_node, "panel-timing", &dt))
			panel_simple_parse_panel_timing_node(dev, panel, &dt);
	पूर्ण

	connector_type = desc->connector_type;
	/* Catch common mistakes क्रम panels. */
	चयन (connector_type) अणु
	हाल 0:
		dev_warn(dev, "Specify missing connector_type\n");
		connector_type = DRM_MODE_CONNECTOR_DPI;
		अवरोध;
	हाल DRM_MODE_CONNECTOR_LVDS:
		WARN_ON(desc->bus_flags &
			~(DRM_BUS_FLAG_DE_LOW |
			  DRM_BUS_FLAG_DE_HIGH |
			  DRM_BUS_FLAG_DATA_MSB_TO_LSB |
			  DRM_BUS_FLAG_DATA_LSB_TO_MSB));
		WARN_ON(desc->bus_क्रमmat != MEDIA_BUS_FMT_RGB666_1X7X3_SPWG &&
			desc->bus_क्रमmat != MEDIA_BUS_FMT_RGB888_1X7X4_SPWG &&
			desc->bus_क्रमmat != MEDIA_BUS_FMT_RGB888_1X7X4_JEIDA);
		WARN_ON(desc->bus_क्रमmat == MEDIA_BUS_FMT_RGB666_1X7X3_SPWG &&
			desc->bpc != 6);
		WARN_ON((desc->bus_क्रमmat == MEDIA_BUS_FMT_RGB888_1X7X4_SPWG ||
			 desc->bus_क्रमmat == MEDIA_BUS_FMT_RGB888_1X7X4_JEIDA) &&
			desc->bpc != 8);
		अवरोध;
	हाल DRM_MODE_CONNECTOR_eDP:
		अगर (desc->bus_क्रमmat == 0)
			dev_warn(dev, "Specify missing bus_format\n");
		अगर (desc->bpc != 6 && desc->bpc != 8)
			dev_warn(dev, "Expected bpc in {6,8} but got: %u\n", desc->bpc);
		अवरोध;
	हाल DRM_MODE_CONNECTOR_DSI:
		अगर (desc->bpc != 6 && desc->bpc != 8)
			dev_warn(dev, "Expected bpc in {6,8} but got: %u\n", desc->bpc);
		अवरोध;
	हाल DRM_MODE_CONNECTOR_DPI:
		bus_flags = DRM_BUS_FLAG_DE_LOW |
			    DRM_BUS_FLAG_DE_HIGH |
			    DRM_BUS_FLAG_PIXDATA_SAMPLE_POSEDGE |
			    DRM_BUS_FLAG_PIXDATA_SAMPLE_NEGEDGE |
			    DRM_BUS_FLAG_DATA_MSB_TO_LSB |
			    DRM_BUS_FLAG_DATA_LSB_TO_MSB |
			    DRM_BUS_FLAG_SYNC_SAMPLE_POSEDGE |
			    DRM_BUS_FLAG_SYNC_SAMPLE_NEGEDGE;
		अगर (desc->bus_flags & ~bus_flags)
			dev_warn(dev, "Unexpected bus_flags(%d)\n", desc->bus_flags & ~bus_flags);
		अगर (!(desc->bus_flags & bus_flags))
			dev_warn(dev, "Specify missing bus_flags\n");
		अगर (desc->bus_क्रमmat == 0)
			dev_warn(dev, "Specify missing bus_format\n");
		अगर (desc->bpc != 6 && desc->bpc != 8)
			dev_warn(dev, "Expected bpc in {6,8} but got: %u\n", desc->bpc);
		अवरोध;
	शेष:
		dev_warn(dev, "Specify a valid connector_type: %d\n", desc->connector_type);
		connector_type = DRM_MODE_CONNECTOR_DPI;
		अवरोध;
	पूर्ण

	drm_panel_init(&panel->base, dev, &panel_simple_funcs, connector_type);

	err = drm_panel_of_backlight(&panel->base);
	अगर (err)
		जाओ मुक्त_ddc;

	drm_panel_add(&panel->base);

	dev_set_drvdata(dev, panel);

	वापस 0;

मुक्त_ddc:
	अगर (panel->ddc)
		put_device(&panel->ddc->dev);

	वापस err;
पूर्ण

अटल पूर्णांक panel_simple_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा panel_simple *panel = dev_get_drvdata(dev);

	drm_panel_हटाओ(&panel->base);
	drm_panel_disable(&panel->base);
	drm_panel_unprepare(&panel->base);

	अगर (panel->ddc)
		put_device(&panel->ddc->dev);

	वापस 0;
पूर्ण

अटल व्योम panel_simple_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा panel_simple *panel = dev_get_drvdata(dev);

	drm_panel_disable(&panel->base);
	drm_panel_unprepare(&panel->base);
पूर्ण

अटल स्थिर काष्ठा drm_display_mode ampire_am_1280800n3tzqw_t00h_mode = अणु
	.घड़ी = 71100,
	.hdisplay = 1280,
	.hsync_start = 1280 + 40,
	.hsync_end = 1280 + 40 + 80,
	.htotal = 1280 + 40 + 80 + 40,
	.vdisplay = 800,
	.vsync_start = 800 + 3,
	.vsync_end = 800 + 3 + 10,
	.vtotal = 800 + 3 + 10 + 10,
	.flags = DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc ampire_am_1280800n3tzqw_t00h = अणु
	.modes = &ampire_am_1280800n3tzqw_t00h_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = अणु
		.width = 217,
		.height = 136,
	पूर्ण,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X7X4_SPWG,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode ampire_am_480272h3पंचांगqw_t01h_mode = अणु
	.घड़ी = 9000,
	.hdisplay = 480,
	.hsync_start = 480 + 2,
	.hsync_end = 480 + 2 + 41,
	.htotal = 480 + 2 + 41 + 2,
	.vdisplay = 272,
	.vsync_start = 272 + 2,
	.vsync_end = 272 + 2 + 10,
	.vtotal = 272 + 2 + 10 + 2,
	.flags = DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc ampire_am_480272h3पंचांगqw_t01h = अणु
	.modes = &ampire_am_480272h3पंचांगqw_t01h_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 105,
		.height = 67,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode ampire_am800480r3पंचांगqwa1h_mode = अणु
	.घड़ी = 33333,
	.hdisplay = 800,
	.hsync_start = 800 + 0,
	.hsync_end = 800 + 0 + 255,
	.htotal = 800 + 0 + 255 + 0,
	.vdisplay = 480,
	.vsync_start = 480 + 2,
	.vsync_end = 480 + 2 + 45,
	.vtotal = 480 + 2 + 45 + 0,
	.flags = DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc ampire_am800480r3पंचांगqwa1h = अणु
	.modes = &ampire_am800480r3पंचांगqwa1h_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = अणु
		.width = 152,
		.height = 91,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X18,
पूर्ण;

अटल स्थिर काष्ठा display_timing santek_st0700i5y_rbslw_f_timing = अणु
	.pixelघड़ी = अणु 26400000, 33300000, 46800000 पूर्ण,
	.hactive = अणु 800, 800, 800 पूर्ण,
	.hfront_porch = अणु 16, 210, 354 पूर्ण,
	.hback_porch = अणु 45, 36, 6 पूर्ण,
	.hsync_len = अणु 1, 10, 40 पूर्ण,
	.vactive = अणु 480, 480, 480 पूर्ण,
	.vfront_porch = अणु 7, 22, 147 पूर्ण,
	.vback_porch = अणु 22, 13, 3 पूर्ण,
	.vsync_len = अणु 1, 10, 20 पूर्ण,
	.flags = DISPLAY_FLAGS_HSYNC_LOW | DISPLAY_FLAGS_VSYNC_LOW |
		DISPLAY_FLAGS_DE_HIGH | DISPLAY_FLAGS_PIXDATA_POSEDGE
पूर्ण;

अटल स्थिर काष्ठा panel_desc armadeus_st0700_adapt = अणु
	.timings = &santek_st0700i5y_rbslw_f_timing,
	.num_timings = 1,
	.bpc = 6,
	.size = अणु
		.width = 154,
		.height = 86,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X18,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH | DRM_BUS_FLAG_PIXDATA_SAMPLE_NEGEDGE,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode auo_b101aw03_mode = अणु
	.घड़ी = 51450,
	.hdisplay = 1024,
	.hsync_start = 1024 + 156,
	.hsync_end = 1024 + 156 + 8,
	.htotal = 1024 + 156 + 8 + 156,
	.vdisplay = 600,
	.vsync_start = 600 + 16,
	.vsync_end = 600 + 16 + 6,
	.vtotal = 600 + 16 + 6 + 16,
पूर्ण;

अटल स्थिर काष्ठा panel_desc auo_b101aw03 = अणु
	.modes = &auo_b101aw03_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = अणु
		.width = 223,
		.height = 125,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X7X3_SPWG,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा display_timing auo_b101ean01_timing = अणु
	.pixelघड़ी = अणु 65300000, 72500000, 75000000 पूर्ण,
	.hactive = अणु 1280, 1280, 1280 पूर्ण,
	.hfront_porch = अणु 18, 119, 119 पूर्ण,
	.hback_porch = अणु 21, 21, 21 पूर्ण,
	.hsync_len = अणु 32, 32, 32 पूर्ण,
	.vactive = अणु 800, 800, 800 पूर्ण,
	.vfront_porch = अणु 4, 4, 4 पूर्ण,
	.vback_porch = अणु 8, 8, 8 पूर्ण,
	.vsync_len = अणु 18, 20, 20 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा panel_desc auo_b101ean01 = अणु
	.timings = &auo_b101ean01_timing,
	.num_timings = 1,
	.bpc = 6,
	.size = अणु
		.width = 217,
		.height = 136,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode auo_b101xtn01_mode = अणु
	.घड़ी = 72000,
	.hdisplay = 1366,
	.hsync_start = 1366 + 20,
	.hsync_end = 1366 + 20 + 70,
	.htotal = 1366 + 20 + 70,
	.vdisplay = 768,
	.vsync_start = 768 + 14,
	.vsync_end = 768 + 14 + 42,
	.vtotal = 768 + 14 + 42,
	.flags = DRM_MODE_FLAG_NVSYNC | DRM_MODE_FLAG_NHSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc auo_b101xtn01 = अणु
	.modes = &auo_b101xtn01_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = अणु
		.width = 223,
		.height = 125,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode auo_b116xak01_mode = अणु
	.घड़ी = 69300,
	.hdisplay = 1366,
	.hsync_start = 1366 + 48,
	.hsync_end = 1366 + 48 + 32,
	.htotal = 1366 + 48 + 32 + 10,
	.vdisplay = 768,
	.vsync_start = 768 + 4,
	.vsync_end = 768 + 4 + 6,
	.vtotal = 768 + 4 + 6 + 15,
	.flags = DRM_MODE_FLAG_NVSYNC | DRM_MODE_FLAG_NHSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc auo_b116xak01 = अणु
	.modes = &auo_b116xak01_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = अणु
		.width = 256,
		.height = 144,
	पूर्ण,
	.delay = अणु
		.hpd_असलent_delay = 200,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X18,
	.connector_type = DRM_MODE_CONNECTOR_eDP,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode auo_b116xw03_mode = अणु
	.घड़ी = 70589,
	.hdisplay = 1366,
	.hsync_start = 1366 + 40,
	.hsync_end = 1366 + 40 + 40,
	.htotal = 1366 + 40 + 40 + 32,
	.vdisplay = 768,
	.vsync_start = 768 + 10,
	.vsync_end = 768 + 10 + 12,
	.vtotal = 768 + 10 + 12 + 6,
	.flags = DRM_MODE_FLAG_NVSYNC | DRM_MODE_FLAG_NHSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc auo_b116xw03 = अणु
	.modes = &auo_b116xw03_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = अणु
		.width = 256,
		.height = 144,
	पूर्ण,
	.delay = अणु
		.enable = 400,
	पूर्ण,
	.bus_flags = DRM_BUS_FLAG_SYNC_DRIVE_NEGEDGE,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X18,
	.connector_type = DRM_MODE_CONNECTOR_eDP,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode auo_b133xtn01_mode = अणु
	.घड़ी = 69500,
	.hdisplay = 1366,
	.hsync_start = 1366 + 48,
	.hsync_end = 1366 + 48 + 32,
	.htotal = 1366 + 48 + 32 + 20,
	.vdisplay = 768,
	.vsync_start = 768 + 3,
	.vsync_end = 768 + 3 + 6,
	.vtotal = 768 + 3 + 6 + 13,
पूर्ण;

अटल स्थिर काष्ठा panel_desc auo_b133xtn01 = अणु
	.modes = &auo_b133xtn01_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = अणु
		.width = 293,
		.height = 165,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode auo_b133htn01_mode = अणु
	.घड़ी = 150660,
	.hdisplay = 1920,
	.hsync_start = 1920 + 172,
	.hsync_end = 1920 + 172 + 80,
	.htotal = 1920 + 172 + 80 + 60,
	.vdisplay = 1080,
	.vsync_start = 1080 + 25,
	.vsync_end = 1080 + 25 + 10,
	.vtotal = 1080 + 25 + 10 + 10,
पूर्ण;

अटल स्थिर काष्ठा panel_desc auo_b133htn01 = अणु
	.modes = &auo_b133htn01_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = अणु
		.width = 293,
		.height = 165,
	पूर्ण,
	.delay = अणु
		.prepare = 105,
		.enable = 20,
		.unprepare = 50,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा display_timing auo_g070vvn01_timings = अणु
	.pixelघड़ी = अणु 33300000, 34209000, 45000000 पूर्ण,
	.hactive = अणु 800, 800, 800 पूर्ण,
	.hfront_porch = अणु 20, 40, 200 पूर्ण,
	.hback_porch = अणु 87, 40, 1 पूर्ण,
	.hsync_len = अणु 1, 48, 87 पूर्ण,
	.vactive = अणु 480, 480, 480 पूर्ण,
	.vfront_porch = अणु 5, 13, 200 पूर्ण,
	.vback_porch = अणु 31, 31, 29 पूर्ण,
	.vsync_len = अणु 1, 1, 3 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा panel_desc auo_g070vvn01 = अणु
	.timings = &auo_g070vvn01_timings,
	.num_timings = 1,
	.bpc = 8,
	.size = अणु
		.width = 152,
		.height = 91,
	पूर्ण,
	.delay = अणु
		.prepare = 200,
		.enable = 50,
		.disable = 50,
		.unprepare = 1000,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode auo_g101evn010_mode = अणु
	.घड़ी = 68930,
	.hdisplay = 1280,
	.hsync_start = 1280 + 82,
	.hsync_end = 1280 + 82 + 2,
	.htotal = 1280 + 82 + 2 + 84,
	.vdisplay = 800,
	.vsync_start = 800 + 8,
	.vsync_end = 800 + 8 + 2,
	.vtotal = 800 + 8 + 2 + 6,
पूर्ण;

अटल स्थिर काष्ठा panel_desc auo_g101evn010 = अणु
	.modes = &auo_g101evn010_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = अणु
		.width = 216,
		.height = 135,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X7X3_SPWG,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode auo_g104sn02_mode = अणु
	.घड़ी = 40000,
	.hdisplay = 800,
	.hsync_start = 800 + 40,
	.hsync_end = 800 + 40 + 216,
	.htotal = 800 + 40 + 216 + 128,
	.vdisplay = 600,
	.vsync_start = 600 + 10,
	.vsync_end = 600 + 10 + 35,
	.vtotal = 600 + 10 + 35 + 2,
पूर्ण;

अटल स्थिर काष्ठा panel_desc auo_g104sn02 = अणु
	.modes = &auo_g104sn02_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 211,
		.height = 158,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode auo_g121ean01_mode = अणु
	.घड़ी = 66700,
	.hdisplay = 1280,
	.hsync_start = 1280 + 58,
	.hsync_end = 1280 + 58 + 8,
	.htotal = 1280 + 58 + 8 + 70,
	.vdisplay = 800,
	.vsync_start = 800 + 6,
	.vsync_end = 800 + 6 + 4,
	.vtotal = 800 + 6 + 4 + 10,
पूर्ण;

अटल स्थिर काष्ठा panel_desc auo_g121ean01 = अणु
	.modes = &auo_g121ean01_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 261,
		.height = 163,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X7X4_SPWG,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा display_timing auo_g133han01_timings = अणु
	.pixelघड़ी = अणु 134000000, 141200000, 149000000 पूर्ण,
	.hactive = अणु 1920, 1920, 1920 पूर्ण,
	.hfront_porch = अणु 39, 58, 77 पूर्ण,
	.hback_porch = अणु 59, 88, 117 पूर्ण,
	.hsync_len = अणु 28, 42, 56 पूर्ण,
	.vactive = अणु 1080, 1080, 1080 पूर्ण,
	.vfront_porch = अणु 3, 8, 11 पूर्ण,
	.vback_porch = अणु 5, 14, 19 पूर्ण,
	.vsync_len = अणु 4, 14, 19 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा panel_desc auo_g133han01 = अणु
	.timings = &auo_g133han01_timings,
	.num_timings = 1,
	.bpc = 8,
	.size = अणु
		.width = 293,
		.height = 165,
	पूर्ण,
	.delay = अणु
		.prepare = 200,
		.enable = 50,
		.disable = 50,
		.unprepare = 1000,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X7X4_JEIDA,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode auo_g156xtn01_mode = अणु
	.घड़ी = 76000,
	.hdisplay = 1366,
	.hsync_start = 1366 + 33,
	.hsync_end = 1366 + 33 + 67,
	.htotal = 1560,
	.vdisplay = 768,
	.vsync_start = 768 + 4,
	.vsync_end = 768 + 4 + 4,
	.vtotal = 806,
पूर्ण;

अटल स्थिर काष्ठा panel_desc auo_g156xtn01 = अणु
	.modes = &auo_g156xtn01_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 344,
		.height = 194,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X7X4_SPWG,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा display_timing auo_g185han01_timings = अणु
	.pixelघड़ी = अणु 120000000, 144000000, 175000000 पूर्ण,
	.hactive = अणु 1920, 1920, 1920 पूर्ण,
	.hfront_porch = अणु 36, 120, 148 पूर्ण,
	.hback_porch = अणु 24, 88, 108 पूर्ण,
	.hsync_len = अणु 20, 48, 64 पूर्ण,
	.vactive = अणु 1080, 1080, 1080 पूर्ण,
	.vfront_porch = अणु 6, 10, 40 पूर्ण,
	.vback_porch = अणु 2, 5, 20 पूर्ण,
	.vsync_len = अणु 2, 5, 20 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा panel_desc auo_g185han01 = अणु
	.timings = &auo_g185han01_timings,
	.num_timings = 1,
	.bpc = 8,
	.size = अणु
		.width = 409,
		.height = 230,
	पूर्ण,
	.delay = अणु
		.prepare = 50,
		.enable = 200,
		.disable = 110,
		.unprepare = 1000,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X7X4_SPWG,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा display_timing auo_g190ean01_timings = अणु
	.pixelघड़ी = अणु 90000000, 108000000, 135000000 पूर्ण,
	.hactive = अणु 1280, 1280, 1280 पूर्ण,
	.hfront_porch = अणु 126, 184, 1266 पूर्ण,
	.hback_porch = अणु 84, 122, 844 पूर्ण,
	.hsync_len = अणु 70, 102, 704 पूर्ण,
	.vactive = अणु 1024, 1024, 1024 पूर्ण,
	.vfront_porch = अणु 4, 26, 76 पूर्ण,
	.vback_porch = अणु 2, 8, 25 पूर्ण,
	.vsync_len = अणु 2, 8, 25 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा panel_desc auo_g190ean01 = अणु
	.timings = &auo_g190ean01_timings,
	.num_timings = 1,
	.bpc = 8,
	.size = अणु
		.width = 376,
		.height = 301,
	पूर्ण,
	.delay = अणु
		.prepare = 50,
		.enable = 200,
		.disable = 110,
		.unprepare = 1000,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X7X4_SPWG,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा display_timing auo_p320hvn03_timings = अणु
	.pixelघड़ी = अणु 106000000, 148500000, 164000000 पूर्ण,
	.hactive = अणु 1920, 1920, 1920 पूर्ण,
	.hfront_porch = अणु 25, 50, 130 पूर्ण,
	.hback_porch = अणु 25, 50, 130 पूर्ण,
	.hsync_len = अणु 20, 40, 105 पूर्ण,
	.vactive = अणु 1080, 1080, 1080 पूर्ण,
	.vfront_porch = अणु 8, 17, 150 पूर्ण,
	.vback_porch = अणु 8, 17, 150 पूर्ण,
	.vsync_len = अणु 4, 11, 100 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा panel_desc auo_p320hvn03 = अणु
	.timings = &auo_p320hvn03_timings,
	.num_timings = 1,
	.bpc = 8,
	.size = अणु
		.width = 698,
		.height = 393,
	पूर्ण,
	.delay = अणु
		.prepare = 1,
		.enable = 450,
		.unprepare = 500,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X7X4_SPWG,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode auo_t215hvn01_mode = अणु
	.घड़ी = 148800,
	.hdisplay = 1920,
	.hsync_start = 1920 + 88,
	.hsync_end = 1920 + 88 + 44,
	.htotal = 1920 + 88 + 44 + 148,
	.vdisplay = 1080,
	.vsync_start = 1080 + 4,
	.vsync_end = 1080 + 4 + 5,
	.vtotal = 1080 + 4 + 5 + 36,
पूर्ण;

अटल स्थिर काष्ठा panel_desc auo_t215hvn01 = अणु
	.modes = &auo_t215hvn01_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 430,
		.height = 270,
	पूर्ण,
	.delay = अणु
		.disable = 5,
		.unprepare = 1000,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode avic_पंचांग070ddh03_mode = अणु
	.घड़ी = 51200,
	.hdisplay = 1024,
	.hsync_start = 1024 + 160,
	.hsync_end = 1024 + 160 + 4,
	.htotal = 1024 + 160 + 4 + 156,
	.vdisplay = 600,
	.vsync_start = 600 + 17,
	.vsync_end = 600 + 17 + 1,
	.vtotal = 600 + 17 + 1 + 17,
पूर्ण;

अटल स्थिर काष्ठा panel_desc avic_पंचांग070ddh03 = अणु
	.modes = &avic_पंचांग070ddh03_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 154,
		.height = 90,
	पूर्ण,
	.delay = अणु
		.prepare = 20,
		.enable = 200,
		.disable = 200,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode bananapi_s070wv20_ct16_mode = अणु
	.घड़ी = 30000,
	.hdisplay = 800,
	.hsync_start = 800 + 40,
	.hsync_end = 800 + 40 + 48,
	.htotal = 800 + 40 + 48 + 40,
	.vdisplay = 480,
	.vsync_start = 480 + 13,
	.vsync_end = 480 + 13 + 3,
	.vtotal = 480 + 13 + 3 + 29,
पूर्ण;

अटल स्थिर काष्ठा panel_desc bananapi_s070wv20_ct16 = अणु
	.modes = &bananapi_s070wv20_ct16_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = अणु
		.width = 154,
		.height = 86,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode boe_hv070wsa_mode = अणु
	.घड़ी = 42105,
	.hdisplay = 1024,
	.hsync_start = 1024 + 30,
	.hsync_end = 1024 + 30 + 30,
	.htotal = 1024 + 30 + 30 + 30,
	.vdisplay = 600,
	.vsync_start = 600 + 10,
	.vsync_end = 600 + 10 + 10,
	.vtotal = 600 + 10 + 10 + 10,
पूर्ण;

अटल स्थिर काष्ठा panel_desc boe_hv070wsa = अणु
	.modes = &boe_hv070wsa_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 154,
		.height = 90,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X7X4_SPWG,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode boe_nv101wxmn51_modes[] = अणु
	अणु
		.घड़ी = 71900,
		.hdisplay = 1280,
		.hsync_start = 1280 + 48,
		.hsync_end = 1280 + 48 + 32,
		.htotal = 1280 + 48 + 32 + 80,
		.vdisplay = 800,
		.vsync_start = 800 + 3,
		.vsync_end = 800 + 3 + 5,
		.vtotal = 800 + 3 + 5 + 24,
	पूर्ण,
	अणु
		.घड़ी = 57500,
		.hdisplay = 1280,
		.hsync_start = 1280 + 48,
		.hsync_end = 1280 + 48 + 32,
		.htotal = 1280 + 48 + 32 + 80,
		.vdisplay = 800,
		.vsync_start = 800 + 3,
		.vsync_end = 800 + 3 + 5,
		.vtotal = 800 + 3 + 5 + 24,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा panel_desc boe_nv101wxmn51 = अणु
	.modes = boe_nv101wxmn51_modes,
	.num_modes = ARRAY_SIZE(boe_nv101wxmn51_modes),
	.bpc = 8,
	.size = अणु
		.width = 217,
		.height = 136,
	पूर्ण,
	.delay = अणु
		.prepare = 210,
		.enable = 50,
		.unprepare = 160,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode boe_nv110wपंचांग_n61_modes[] = अणु
	अणु
		.घड़ी = 207800,
		.hdisplay = 2160,
		.hsync_start = 2160 + 48,
		.hsync_end = 2160 + 48 + 32,
		.htotal = 2160 + 48 + 32 + 100,
		.vdisplay = 1440,
		.vsync_start = 1440 + 3,
		.vsync_end = 1440 + 3 + 6,
		.vtotal = 1440 + 3 + 6 + 31,
		.flags = DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC,
	पूर्ण,
	अणु
		.घड़ी = 138500,
		.hdisplay = 2160,
		.hsync_start = 2160 + 48,
		.hsync_end = 2160 + 48 + 32,
		.htotal = 2160 + 48 + 32 + 100,
		.vdisplay = 1440,
		.vsync_start = 1440 + 3,
		.vsync_end = 1440 + 3 + 6,
		.vtotal = 1440 + 3 + 6 + 31,
		.flags = DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा panel_desc boe_nv110wपंचांग_n61 = अणु
	.modes = boe_nv110wपंचांग_n61_modes,
	.num_modes = ARRAY_SIZE(boe_nv110wपंचांग_n61_modes),
	.bpc = 8,
	.size = अणु
		.width = 233,
		.height = 155,
	पूर्ण,
	.delay = अणु
		.hpd_असलent_delay = 200,
		.prepare_to_enable = 80,
		.enable = 50,
		.unprepare = 500,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
	.bus_flags = DRM_BUS_FLAG_DATA_MSB_TO_LSB,
	.connector_type = DRM_MODE_CONNECTOR_eDP,
पूर्ण;

/* Also used क्रम boe_nv133fhm_n62 */
अटल स्थिर काष्ठा drm_display_mode boe_nv133fhm_n61_modes = अणु
	.घड़ी = 147840,
	.hdisplay = 1920,
	.hsync_start = 1920 + 48,
	.hsync_end = 1920 + 48 + 32,
	.htotal = 1920 + 48 + 32 + 200,
	.vdisplay = 1080,
	.vsync_start = 1080 + 3,
	.vsync_end = 1080 + 3 + 6,
	.vtotal = 1080 + 3 + 6 + 31,
	.flags = DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC,
पूर्ण;

/* Also used क्रम boe_nv133fhm_n62 */
अटल स्थिर काष्ठा panel_desc boe_nv133fhm_n61 = अणु
	.modes = &boe_nv133fhm_n61_modes,
	.num_modes = 1,
	.bpc = 6,
	.size = अणु
		.width = 294,
		.height = 165,
	पूर्ण,
	.delay = अणु
		/*
		 * When घातer is first given to the panel there's a लघु
		 * spike on the HPD line.  It was explained that this spike
		 * was until the TCON data करोwnload was complete.  On
		 * one प्रणाली this was measured at 8 ms.  We'll put 15 ms
		 * in the prepare delay just to be safe and take it away
		 * from the hpd_असलent_delay (which would otherwise be 200 ms)
		 * to handle this.  That means:
		 * - If HPD isn't hooked up you still have 200 ms delay.
		 * - If HPD is hooked up we won't try to look at it क्रम the
		 *   first 15 ms.
		 */
		.prepare = 15,
		.hpd_असलent_delay = 185,

		.unprepare = 500,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
	.bus_flags = DRM_BUS_FLAG_DATA_MSB_TO_LSB,
	.connector_type = DRM_MODE_CONNECTOR_eDP,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode boe_nv140fhmn49_modes[] = अणु
	अणु
		.घड़ी = 148500,
		.hdisplay = 1920,
		.hsync_start = 1920 + 48,
		.hsync_end = 1920 + 48 + 32,
		.htotal = 2200,
		.vdisplay = 1080,
		.vsync_start = 1080 + 3,
		.vsync_end = 1080 + 3 + 5,
		.vtotal = 1125,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा panel_desc boe_nv140fhmn49 = अणु
	.modes = boe_nv140fhmn49_modes,
	.num_modes = ARRAY_SIZE(boe_nv140fhmn49_modes),
	.bpc = 6,
	.size = अणु
		.width = 309,
		.height = 174,
	पूर्ण,
	.delay = अणु
		.prepare = 210,
		.enable = 50,
		.unprepare = 160,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X18,
	.connector_type = DRM_MODE_CONNECTOR_eDP,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode cdtech_s043wq26h_ct7_mode = अणु
	.घड़ी = 9000,
	.hdisplay = 480,
	.hsync_start = 480 + 5,
	.hsync_end = 480 + 5 + 5,
	.htotal = 480 + 5 + 5 + 40,
	.vdisplay = 272,
	.vsync_start = 272 + 8,
	.vsync_end = 272 + 8 + 8,
	.vtotal = 272 + 8 + 8 + 8,
	.flags = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc cdtech_s043wq26h_ct7 = अणु
	.modes = &cdtech_s043wq26h_ct7_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 95,
		.height = 54,
	पूर्ण,
	.bus_flags = DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE,
पूर्ण;

/* S070PWS19HP-FC21 2017/04/22 */
अटल स्थिर काष्ठा drm_display_mode cdtech_s070pws19hp_fc21_mode = अणु
	.घड़ी = 51200,
	.hdisplay = 1024,
	.hsync_start = 1024 + 160,
	.hsync_end = 1024 + 160 + 20,
	.htotal = 1024 + 160 + 20 + 140,
	.vdisplay = 600,
	.vsync_start = 600 + 12,
	.vsync_end = 600 + 12 + 3,
	.vtotal = 600 + 12 + 3 + 20,
	.flags = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc cdtech_s070pws19hp_fc21 = अणु
	.modes = &cdtech_s070pws19hp_fc21_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = अणु
		.width = 154,
		.height = 86,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X18,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH | DRM_BUS_FLAG_PIXDATA_SAMPLE_NEGEDGE,
	.connector_type = DRM_MODE_CONNECTOR_DPI,
पूर्ण;

/* S070SWV29HG-DC44 2017/09/21 */
अटल स्थिर काष्ठा drm_display_mode cdtech_s070swv29hg_dc44_mode = अणु
	.घड़ी = 33300,
	.hdisplay = 800,
	.hsync_start = 800 + 210,
	.hsync_end = 800 + 210 + 2,
	.htotal = 800 + 210 + 2 + 44,
	.vdisplay = 480,
	.vsync_start = 480 + 22,
	.vsync_end = 480 + 22 + 2,
	.vtotal = 480 + 22 + 2 + 21,
	.flags = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc cdtech_s070swv29hg_dc44 = अणु
	.modes = &cdtech_s070swv29hg_dc44_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = अणु
		.width = 154,
		.height = 86,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X18,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH | DRM_BUS_FLAG_PIXDATA_SAMPLE_NEGEDGE,
	.connector_type = DRM_MODE_CONNECTOR_DPI,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode cdtech_s070wv95_ct16_mode = अणु
	.घड़ी = 35000,
	.hdisplay = 800,
	.hsync_start = 800 + 40,
	.hsync_end = 800 + 40 + 40,
	.htotal = 800 + 40 + 40 + 48,
	.vdisplay = 480,
	.vsync_start = 480 + 29,
	.vsync_end = 480 + 29 + 13,
	.vtotal = 480 + 29 + 13 + 3,
	.flags = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc cdtech_s070wv95_ct16 = अणु
	.modes = &cdtech_s070wv95_ct16_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 154,
		.height = 85,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा display_timing cheमुक्त_ch101olhlwh_002_timing = अणु
	.pixelघड़ी = अणु 68900000, 71100000, 73400000 पूर्ण,
	.hactive = अणु 1280, 1280, 1280 पूर्ण,
	.hfront_porch = अणु 65, 80, 95 पूर्ण,
	.hback_porch = अणु 64, 79, 94 पूर्ण,
	.hsync_len = अणु 1, 1, 1 पूर्ण,
	.vactive = अणु 800, 800, 800 पूर्ण,
	.vfront_porch = अणु 7, 11, 14 पूर्ण,
	.vback_porch = अणु 7, 11, 14 पूर्ण,
	.vsync_len = अणु 1, 1, 1 पूर्ण,
	.flags = DISPLAY_FLAGS_DE_HIGH,
पूर्ण;

अटल स्थिर काष्ठा panel_desc cheमुक्त_ch101olhlwh_002 = अणु
	.timings = &cheमुक्त_ch101olhlwh_002_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = अणु
		.width = 217,
		.height = 135,
	पूर्ण,
	.delay = अणु
		.enable = 200,
		.disable = 200,
	पूर्ण,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X7X4_SPWG,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode chunghwa_claa070wp03xg_mode = अणु
	.घड़ी = 66770,
	.hdisplay = 800,
	.hsync_start = 800 + 49,
	.hsync_end = 800 + 49 + 33,
	.htotal = 800 + 49 + 33 + 17,
	.vdisplay = 1280,
	.vsync_start = 1280 + 1,
	.vsync_end = 1280 + 1 + 7,
	.vtotal = 1280 + 1 + 7 + 15,
	.flags = DRM_MODE_FLAG_NVSYNC | DRM_MODE_FLAG_NHSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc chunghwa_claa070wp03xg = अणु
	.modes = &chunghwa_claa070wp03xg_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = अणु
		.width = 94,
		.height = 150,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X7X3_SPWG,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode chunghwa_claa101wa01a_mode = अणु
	.घड़ी = 72070,
	.hdisplay = 1366,
	.hsync_start = 1366 + 58,
	.hsync_end = 1366 + 58 + 58,
	.htotal = 1366 + 58 + 58 + 58,
	.vdisplay = 768,
	.vsync_start = 768 + 4,
	.vsync_end = 768 + 4 + 4,
	.vtotal = 768 + 4 + 4 + 4,
पूर्ण;

अटल स्थिर काष्ठा panel_desc chunghwa_claa101wa01a = अणु
	.modes = &chunghwa_claa101wa01a_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = अणु
		.width = 220,
		.height = 120,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X7X3_SPWG,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode chunghwa_claa101wb01_mode = अणु
	.घड़ी = 69300,
	.hdisplay = 1366,
	.hsync_start = 1366 + 48,
	.hsync_end = 1366 + 48 + 32,
	.htotal = 1366 + 48 + 32 + 20,
	.vdisplay = 768,
	.vsync_start = 768 + 16,
	.vsync_end = 768 + 16 + 8,
	.vtotal = 768 + 16 + 8 + 16,
पूर्ण;

अटल स्थिर काष्ठा panel_desc chunghwa_claa101wb01 = अणु
	.modes = &chunghwa_claa101wb01_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = अणु
		.width = 223,
		.height = 125,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X7X3_SPWG,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode dataimage_scf0700c48ggu18_mode = अणु
	.घड़ी = 33260,
	.hdisplay = 800,
	.hsync_start = 800 + 40,
	.hsync_end = 800 + 40 + 128,
	.htotal = 800 + 40 + 128 + 88,
	.vdisplay = 480,
	.vsync_start = 480 + 10,
	.vsync_end = 480 + 10 + 2,
	.vtotal = 480 + 10 + 2 + 33,
	.flags = DRM_MODE_FLAG_NVSYNC | DRM_MODE_FLAG_NHSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc dataimage_scf0700c48ggu18 = अणु
	.modes = &dataimage_scf0700c48ggu18_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 152,
		.height = 91,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH | DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE,
पूर्ण;

अटल स्थिर काष्ठा display_timing dlc_dlc0700yzg_1_timing = अणु
	.pixelघड़ी = अणु 45000000, 51200000, 57000000 पूर्ण,
	.hactive = अणु 1024, 1024, 1024 पूर्ण,
	.hfront_porch = अणु 100, 106, 113 पूर्ण,
	.hback_porch = अणु 100, 106, 113 पूर्ण,
	.hsync_len = अणु 100, 108, 114 पूर्ण,
	.vactive = अणु 600, 600, 600 पूर्ण,
	.vfront_porch = अणु 8, 11, 15 पूर्ण,
	.vback_porch = अणु 8, 11, 15 पूर्ण,
	.vsync_len = अणु 9, 13, 15 पूर्ण,
	.flags = DISPLAY_FLAGS_DE_HIGH,
पूर्ण;

अटल स्थिर काष्ठा panel_desc dlc_dlc0700yzg_1 = अणु
	.timings = &dlc_dlc0700yzg_1_timing,
	.num_timings = 1,
	.bpc = 6,
	.size = अणु
		.width = 154,
		.height = 86,
	पूर्ण,
	.delay = अणु
		.prepare = 30,
		.enable = 200,
		.disable = 200,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X7X3_SPWG,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा display_timing dlc_dlc1010gig_timing = अणु
	.pixelघड़ी = अणु 68900000, 71100000, 73400000 पूर्ण,
	.hactive = अणु 1280, 1280, 1280 पूर्ण,
	.hfront_porch = अणु 43, 53, 63 पूर्ण,
	.hback_porch = अणु 43, 53, 63 पूर्ण,
	.hsync_len = अणु 44, 54, 64 पूर्ण,
	.vactive = अणु 800, 800, 800 पूर्ण,
	.vfront_porch = अणु 5, 8, 11 पूर्ण,
	.vback_porch = अणु 5, 8, 11 पूर्ण,
	.vsync_len = अणु 5, 7, 11 पूर्ण,
	.flags = DISPLAY_FLAGS_DE_HIGH,
पूर्ण;

अटल स्थिर काष्ठा panel_desc dlc_dlc1010gig = अणु
	.timings = &dlc_dlc1010gig_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = अणु
		.width = 216,
		.height = 135,
	पूर्ण,
	.delay = अणु
		.prepare = 60,
		.enable = 150,
		.disable = 100,
		.unprepare = 60,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X7X4_SPWG,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode edt_et035012dm6_mode = अणु
	.घड़ी = 6500,
	.hdisplay = 320,
	.hsync_start = 320 + 20,
	.hsync_end = 320 + 20 + 30,
	.htotal = 320 + 20 + 68,
	.vdisplay = 240,
	.vsync_start = 240 + 4,
	.vsync_end = 240 + 4 + 4,
	.vtotal = 240 + 4 + 4 + 14,
	.flags = DRM_MODE_FLAG_NVSYNC | DRM_MODE_FLAG_NHSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc edt_et035012dm6 = अणु
	.modes = &edt_et035012dm6_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 70,
		.height = 52,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
	.bus_flags = DRM_BUS_FLAG_DE_LOW | DRM_BUS_FLAG_PIXDATA_SAMPLE_POSEDGE,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode edt_eपंचांग043080dh6gp_mode = अणु
	.घड़ी = 10870,
	.hdisplay = 480,
	.hsync_start = 480 + 8,
	.hsync_end = 480 + 8 + 4,
	.htotal = 480 + 8 + 4 + 41,

	/*
	 * IWG22M: Y resolution changed क्रम "dc_linuxfb" module crashing जबतक
	 * fb_align
	 */

	.vdisplay = 288,
	.vsync_start = 288 + 2,
	.vsync_end = 288 + 2 + 4,
	.vtotal = 288 + 2 + 4 + 10,
पूर्ण;

अटल स्थिर काष्ठा panel_desc edt_eपंचांग043080dh6gp = अणु
	.modes = &edt_eपंचांग043080dh6gp_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 100,
		.height = 65,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X18,
	.connector_type = DRM_MODE_CONNECTOR_DPI,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode edt_eपंचांग0430g0dh6_mode = अणु
	.घड़ी = 9000,
	.hdisplay = 480,
	.hsync_start = 480 + 2,
	.hsync_end = 480 + 2 + 41,
	.htotal = 480 + 2 + 41 + 2,
	.vdisplay = 272,
	.vsync_start = 272 + 2,
	.vsync_end = 272 + 2 + 10,
	.vtotal = 272 + 2 + 10 + 2,
	.flags = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc edt_eपंचांग0430g0dh6 = अणु
	.modes = &edt_eपंचांग0430g0dh6_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = अणु
		.width = 95,
		.height = 54,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode edt_et057090dhu_mode = अणु
	.घड़ी = 25175,
	.hdisplay = 640,
	.hsync_start = 640 + 16,
	.hsync_end = 640 + 16 + 30,
	.htotal = 640 + 16 + 30 + 114,
	.vdisplay = 480,
	.vsync_start = 480 + 10,
	.vsync_end = 480 + 10 + 3,
	.vtotal = 480 + 10 + 3 + 32,
	.flags = DRM_MODE_FLAG_NVSYNC | DRM_MODE_FLAG_NHSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc edt_et057090dhu = अणु
	.modes = &edt_et057090dhu_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = अणु
		.width = 115,
		.height = 86,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X18,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH | DRM_BUS_FLAG_PIXDATA_DRIVE_NEGEDGE,
	.connector_type = DRM_MODE_CONNECTOR_DPI,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode edt_eपंचांग0700g0dh6_mode = अणु
	.घड़ी = 33260,
	.hdisplay = 800,
	.hsync_start = 800 + 40,
	.hsync_end = 800 + 40 + 128,
	.htotal = 800 + 40 + 128 + 88,
	.vdisplay = 480,
	.vsync_start = 480 + 10,
	.vsync_end = 480 + 10 + 2,
	.vtotal = 480 + 10 + 2 + 33,
	.flags = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc edt_eपंचांग0700g0dh6 = अणु
	.modes = &edt_eपंचांग0700g0dh6_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = अणु
		.width = 152,
		.height = 91,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X18,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH | DRM_BUS_FLAG_PIXDATA_DRIVE_NEGEDGE,
	.connector_type = DRM_MODE_CONNECTOR_DPI,
पूर्ण;

अटल स्थिर काष्ठा panel_desc edt_eपंचांग0700g0bdh6 = अणु
	.modes = &edt_eपंचांग0700g0dh6_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = अणु
		.width = 152,
		.height = 91,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X18,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH | DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE,
पूर्ण;

अटल स्थिर काष्ठा display_timing evervision_vgg804821_timing = अणु
	.pixelघड़ी = अणु 27600000, 33300000, 50000000 पूर्ण,
	.hactive = अणु 800, 800, 800 पूर्ण,
	.hfront_porch = अणु 40, 66, 70 पूर्ण,
	.hback_porch = अणु 40, 67, 70 पूर्ण,
	.hsync_len = अणु 40, 67, 70 पूर्ण,
	.vactive = अणु 480, 480, 480 पूर्ण,
	.vfront_porch = अणु 6, 10, 10 पूर्ण,
	.vback_porch = अणु 7, 11, 11 पूर्ण,
	.vsync_len = अणु 7, 11, 11 पूर्ण,
	.flags = DISPLAY_FLAGS_HSYNC_HIGH | DISPLAY_FLAGS_VSYNC_HIGH |
		 DISPLAY_FLAGS_DE_HIGH | DISPLAY_FLAGS_PIXDATA_NEGEDGE |
		 DISPLAY_FLAGS_SYNC_NEGEDGE,
पूर्ण;

अटल स्थिर काष्ठा panel_desc evervision_vgg804821 = अणु
	.timings = &evervision_vgg804821_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = अणु
		.width = 108,
		.height = 64,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH | DRM_BUS_FLAG_PIXDATA_SAMPLE_POSEDGE,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode foxlink_fl500wvr00_a0t_mode = अणु
	.घड़ी = 32260,
	.hdisplay = 800,
	.hsync_start = 800 + 168,
	.hsync_end = 800 + 168 + 64,
	.htotal = 800 + 168 + 64 + 88,
	.vdisplay = 480,
	.vsync_start = 480 + 37,
	.vsync_end = 480 + 37 + 2,
	.vtotal = 480 + 37 + 2 + 8,
पूर्ण;

अटल स्थिर काष्ठा panel_desc foxlink_fl500wvr00_a0t = अणु
	.modes = &foxlink_fl500wvr00_a0t_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 108,
		.height = 65,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode frida_frd350h54004_modes[] = अणु
	अणु /* 60 Hz */
		.घड़ी = 6000,
		.hdisplay = 320,
		.hsync_start = 320 + 44,
		.hsync_end = 320 + 44 + 16,
		.htotal = 320 + 44 + 16 + 20,
		.vdisplay = 240,
		.vsync_start = 240 + 2,
		.vsync_end = 240 + 2 + 6,
		.vtotal = 240 + 2 + 6 + 2,
		.flags = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC,
	पूर्ण,
	अणु /* 50 Hz */
		.घड़ी = 5400,
		.hdisplay = 320,
		.hsync_start = 320 + 56,
		.hsync_end = 320 + 56 + 16,
		.htotal = 320 + 56 + 16 + 40,
		.vdisplay = 240,
		.vsync_start = 240 + 2,
		.vsync_end = 240 + 2 + 6,
		.vtotal = 240 + 2 + 6 + 2,
		.flags = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा panel_desc frida_frd350h54004 = अणु
	.modes = frida_frd350h54004_modes,
	.num_modes = ARRAY_SIZE(frida_frd350h54004_modes),
	.bpc = 8,
	.size = अणु
		.width = 77,
		.height = 64,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH | DRM_BUS_FLAG_PIXDATA_SAMPLE_NEGEDGE,
	.connector_type = DRM_MODE_CONNECTOR_DPI,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode मित्रlyarm_hd702e_mode = अणु
	.घड़ी		= 67185,
	.hdisplay	= 800,
	.hsync_start	= 800 + 20,
	.hsync_end	= 800 + 20 + 24,
	.htotal		= 800 + 20 + 24 + 20,
	.vdisplay	= 1280,
	.vsync_start	= 1280 + 4,
	.vsync_end	= 1280 + 4 + 8,
	.vtotal		= 1280 + 4 + 8 + 4,
	.flags		= DRM_MODE_FLAG_NVSYNC | DRM_MODE_FLAG_NHSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc मित्रlyarm_hd702e = अणु
	.modes = &मित्रlyarm_hd702e_mode,
	.num_modes = 1,
	.size = अणु
		.width	= 94,
		.height	= 151,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode giantplus_gpg482739qs5_mode = अणु
	.घड़ी = 9000,
	.hdisplay = 480,
	.hsync_start = 480 + 5,
	.hsync_end = 480 + 5 + 1,
	.htotal = 480 + 5 + 1 + 40,
	.vdisplay = 272,
	.vsync_start = 272 + 8,
	.vsync_end = 272 + 8 + 1,
	.vtotal = 272 + 8 + 1 + 8,
पूर्ण;

अटल स्थिर काष्ठा panel_desc giantplus_gpg482739qs5 = अणु
	.modes = &giantplus_gpg482739qs5_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 95,
		.height = 54,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
पूर्ण;

अटल स्थिर काष्ठा display_timing giantplus_gpm940b0_timing = अणु
	.pixelघड़ी = अणु 13500000, 27000000, 27500000 पूर्ण,
	.hactive = अणु 320, 320, 320 पूर्ण,
	.hfront_porch = अणु 14, 686, 718 पूर्ण,
	.hback_porch = अणु 50, 70, 255 पूर्ण,
	.hsync_len = अणु 1, 1, 1 पूर्ण,
	.vactive = अणु 240, 240, 240 पूर्ण,
	.vfront_porch = अणु 1, 1, 179 पूर्ण,
	.vback_porch = अणु 1, 21, 31 पूर्ण,
	.vsync_len = अणु 1, 1, 6 पूर्ण,
	.flags = DISPLAY_FLAGS_HSYNC_LOW | DISPLAY_FLAGS_VSYNC_LOW,
पूर्ण;

अटल स्थिर काष्ठा panel_desc giantplus_gpm940b0 = अणु
	.timings = &giantplus_gpm940b0_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = अणु
		.width = 60,
		.height = 45,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_3X8,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH | DRM_BUS_FLAG_PIXDATA_SAMPLE_POSEDGE,
पूर्ण;

अटल स्थिर काष्ठा display_timing hannstar_hsd070pww1_timing = अणु
	.pixelघड़ी = अणु 64300000, 71100000, 82000000 पूर्ण,
	.hactive = अणु 1280, 1280, 1280 पूर्ण,
	.hfront_porch = अणु 1, 1, 10 पूर्ण,
	.hback_porch = अणु 1, 1, 10 पूर्ण,
	/*
	 * According to the data sheet, the minimum horizontal blanking पूर्णांकerval
	 * is 54 घड़ीs (1 + 52 + 1), but tests with a Nitrogen6X have shown the
	 * minimum working horizontal blanking पूर्णांकerval to be 60 घड़ीs.
	 */
	.hsync_len = अणु 58, 158, 661 पूर्ण,
	.vactive = अणु 800, 800, 800 पूर्ण,
	.vfront_porch = अणु 1, 1, 10 पूर्ण,
	.vback_porch = अणु 1, 1, 10 पूर्ण,
	.vsync_len = अणु 1, 21, 203 पूर्ण,
	.flags = DISPLAY_FLAGS_DE_HIGH,
पूर्ण;

अटल स्थिर काष्ठा panel_desc hannstar_hsd070pww1 = अणु
	.timings = &hannstar_hsd070pww1_timing,
	.num_timings = 1,
	.bpc = 6,
	.size = अणु
		.width = 151,
		.height = 94,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X7X3_SPWG,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा display_timing hannstar_hsd100pxn1_timing = अणु
	.pixelघड़ी = अणु 55000000, 65000000, 75000000 पूर्ण,
	.hactive = अणु 1024, 1024, 1024 पूर्ण,
	.hfront_porch = अणु 40, 40, 40 पूर्ण,
	.hback_porch = अणु 220, 220, 220 पूर्ण,
	.hsync_len = अणु 20, 60, 100 पूर्ण,
	.vactive = अणु 768, 768, 768 पूर्ण,
	.vfront_porch = अणु 7, 7, 7 पूर्ण,
	.vback_porch = अणु 21, 21, 21 पूर्ण,
	.vsync_len = अणु 10, 10, 10 पूर्ण,
	.flags = DISPLAY_FLAGS_DE_HIGH,
पूर्ण;

अटल स्थिर काष्ठा panel_desc hannstar_hsd100pxn1 = अणु
	.timings = &hannstar_hsd100pxn1_timing,
	.num_timings = 1,
	.bpc = 6,
	.size = अणु
		.width = 203,
		.height = 152,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X7X3_SPWG,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode hitachi_tx23d38vm0caa_mode = अणु
	.घड़ी = 33333,
	.hdisplay = 800,
	.hsync_start = 800 + 85,
	.hsync_end = 800 + 85 + 86,
	.htotal = 800 + 85 + 86 + 85,
	.vdisplay = 480,
	.vsync_start = 480 + 16,
	.vsync_end = 480 + 16 + 13,
	.vtotal = 480 + 16 + 13 + 16,
पूर्ण;

अटल स्थिर काष्ठा panel_desc hitachi_tx23d38vm0caa = अणु
	.modes = &hitachi_tx23d38vm0caa_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = अणु
		.width = 195,
		.height = 117,
	पूर्ण,
	.delay = अणु
		.enable = 160,
		.disable = 160,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode innolux_at043tn24_mode = अणु
	.घड़ी = 9000,
	.hdisplay = 480,
	.hsync_start = 480 + 2,
	.hsync_end = 480 + 2 + 41,
	.htotal = 480 + 2 + 41 + 2,
	.vdisplay = 272,
	.vsync_start = 272 + 2,
	.vsync_end = 272 + 2 + 10,
	.vtotal = 272 + 2 + 10 + 2,
	.flags = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc innolux_at043tn24 = अणु
	.modes = &innolux_at043tn24_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 95,
		.height = 54,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH | DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode innolux_at070tn92_mode = अणु
	.घड़ी = 33333,
	.hdisplay = 800,
	.hsync_start = 800 + 210,
	.hsync_end = 800 + 210 + 20,
	.htotal = 800 + 210 + 20 + 46,
	.vdisplay = 480,
	.vsync_start = 480 + 22,
	.vsync_end = 480 + 22 + 10,
	.vtotal = 480 + 22 + 23 + 10,
पूर्ण;

अटल स्थिर काष्ठा panel_desc innolux_at070tn92 = अणु
	.modes = &innolux_at070tn92_mode,
	.num_modes = 1,
	.size = अणु
		.width = 154,
		.height = 86,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
पूर्ण;

अटल स्थिर काष्ठा display_timing innolux_g070y2_l01_timing = अणु
	.pixelघड़ी = अणु 28000000, 29500000, 32000000 पूर्ण,
	.hactive = अणु 800, 800, 800 पूर्ण,
	.hfront_porch = अणु 61, 91, 141 पूर्ण,
	.hback_porch = अणु 60, 90, 140 पूर्ण,
	.hsync_len = अणु 12, 12, 12 पूर्ण,
	.vactive = अणु 480, 480, 480 पूर्ण,
	.vfront_porch = अणु 4, 9, 30 पूर्ण,
	.vback_porch = अणु 4, 8, 28 पूर्ण,
	.vsync_len = अणु 2, 2, 2 पूर्ण,
	.flags = DISPLAY_FLAGS_DE_HIGH,
पूर्ण;

अटल स्थिर काष्ठा panel_desc innolux_g070y2_l01 = अणु
	.timings = &innolux_g070y2_l01_timing,
	.num_timings = 1,
	.bpc = 6,
	.size = अणु
		.width = 152,
		.height = 91,
	पूर्ण,
	.delay = अणु
		.prepare = 10,
		.enable = 100,
		.disable = 100,
		.unprepare = 800,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X7X4_SPWG,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा display_timing innolux_g101ice_l01_timing = अणु
	.pixelघड़ी = अणु 60400000, 71100000, 74700000 पूर्ण,
	.hactive = अणु 1280, 1280, 1280 पूर्ण,
	.hfront_porch = अणु 41, 80, 100 पूर्ण,
	.hback_porch = अणु 40, 79, 99 पूर्ण,
	.hsync_len = अणु 1, 1, 1 पूर्ण,
	.vactive = अणु 800, 800, 800 पूर्ण,
	.vfront_porch = अणु 5, 11, 14 पूर्ण,
	.vback_porch = अणु 4, 11, 14 पूर्ण,
	.vsync_len = अणु 1, 1, 1 पूर्ण,
	.flags = DISPLAY_FLAGS_DE_HIGH,
पूर्ण;

अटल स्थिर काष्ठा panel_desc innolux_g101ice_l01 = अणु
	.timings = &innolux_g101ice_l01_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = अणु
		.width = 217,
		.height = 135,
	पूर्ण,
	.delay = अणु
		.enable = 200,
		.disable = 200,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X7X4_SPWG,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा display_timing innolux_g121i1_l01_timing = अणु
	.pixelघड़ी = अणु 67450000, 71000000, 74550000 पूर्ण,
	.hactive = अणु 1280, 1280, 1280 पूर्ण,
	.hfront_porch = अणु 40, 80, 160 पूर्ण,
	.hback_porch = अणु 39, 79, 159 पूर्ण,
	.hsync_len = अणु 1, 1, 1 पूर्ण,
	.vactive = अणु 800, 800, 800 पूर्ण,
	.vfront_porch = अणु 5, 11, 100 पूर्ण,
	.vback_porch = अणु 4, 11, 99 पूर्ण,
	.vsync_len = अणु 1, 1, 1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा panel_desc innolux_g121i1_l01 = अणु
	.timings = &innolux_g121i1_l01_timing,
	.num_timings = 1,
	.bpc = 6,
	.size = अणु
		.width = 261,
		.height = 163,
	पूर्ण,
	.delay = अणु
		.enable = 200,
		.disable = 20,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X7X4_SPWG,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode innolux_g121x1_l03_mode = अणु
	.घड़ी = 65000,
	.hdisplay = 1024,
	.hsync_start = 1024 + 0,
	.hsync_end = 1024 + 1,
	.htotal = 1024 + 0 + 1 + 320,
	.vdisplay = 768,
	.vsync_start = 768 + 38,
	.vsync_end = 768 + 38 + 1,
	.vtotal = 768 + 38 + 1 + 0,
	.flags = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc innolux_g121x1_l03 = अणु
	.modes = &innolux_g121x1_l03_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = अणु
		.width = 246,
		.height = 185,
	पूर्ण,
	.delay = अणु
		.enable = 200,
		.unprepare = 200,
		.disable = 400,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode innolux_n116bca_ea1_mode = अणु
	.घड़ी = 76420,
	.hdisplay = 1366,
	.hsync_start = 1366 + 136,
	.hsync_end = 1366 + 136 + 30,
	.htotal = 1366 + 136 + 30 + 60,
	.vdisplay = 768,
	.vsync_start = 768 + 8,
	.vsync_end = 768 + 8 + 12,
	.vtotal = 768 + 8 + 12 + 12,
	.flags = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc innolux_n116bca_ea1 = अणु
	.modes = &innolux_n116bca_ea1_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = अणु
		.width = 256,
		.height = 144,
	पूर्ण,
	.delay = अणु
		.hpd_असलent_delay = 200,
		.prepare_to_enable = 80,
		.unprepare = 500,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X18,
	.connector_type = DRM_MODE_CONNECTOR_eDP,
पूर्ण;

/*
 * Datasheet specअगरies that at 60 Hz refresh rate:
 * - total horizontal समय: अणु 1506, 1592, 1716 पूर्ण
 * - total vertical समय: अणु 788, 800, 868 पूर्ण
 *
 * ...but करोesn't go पूर्णांकo exactly how that should be split पूर्णांकo a front
 * porch, back porch, or sync length.  For now we'll leave a single setting
 * here which allows a bit of tweaking of the pixel घड़ी at the expense of
 * refresh rate.
 */
अटल स्थिर काष्ठा display_timing innolux_n116bge_timing = अणु
	.pixelघड़ी = अणु 72600000, 76420000, 80240000 पूर्ण,
	.hactive = अणु 1366, 1366, 1366 पूर्ण,
	.hfront_porch = अणु 136, 136, 136 पूर्ण,
	.hback_porch = अणु 60, 60, 60 पूर्ण,
	.hsync_len = अणु 30, 30, 30 पूर्ण,
	.vactive = अणु 768, 768, 768 पूर्ण,
	.vfront_porch = अणु 8, 8, 8 पूर्ण,
	.vback_porch = अणु 12, 12, 12 पूर्ण,
	.vsync_len = अणु 12, 12, 12 पूर्ण,
	.flags = DISPLAY_FLAGS_VSYNC_LOW | DISPLAY_FLAGS_HSYNC_LOW,
पूर्ण;

अटल स्थिर काष्ठा panel_desc innolux_n116bge = अणु
	.timings = &innolux_n116bge_timing,
	.num_timings = 1,
	.bpc = 6,
	.size = अणु
		.width = 256,
		.height = 144,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X18,
	.connector_type = DRM_MODE_CONNECTOR_eDP,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode innolux_n125hce_gn1_mode = अणु
	.घड़ी = 162000,
	.hdisplay = 1920,
	.hsync_start = 1920 + 40,
	.hsync_end = 1920 + 40 + 40,
	.htotal = 1920 + 40 + 40 + 80,
	.vdisplay = 1080,
	.vsync_start = 1080 + 4,
	.vsync_end = 1080 + 4 + 4,
	.vtotal = 1080 + 4 + 4 + 24,
पूर्ण;

अटल स्थिर काष्ठा panel_desc innolux_n125hce_gn1 = अणु
	.modes = &innolux_n125hce_gn1_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 276,
		.height = 155,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
	.bus_flags = DRM_BUS_FLAG_DATA_MSB_TO_LSB,
	.connector_type = DRM_MODE_CONNECTOR_eDP,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode innolux_n156bge_l21_mode = अणु
	.घड़ी = 69300,
	.hdisplay = 1366,
	.hsync_start = 1366 + 16,
	.hsync_end = 1366 + 16 + 34,
	.htotal = 1366 + 16 + 34 + 50,
	.vdisplay = 768,
	.vsync_start = 768 + 2,
	.vsync_end = 768 + 2 + 6,
	.vtotal = 768 + 2 + 6 + 12,
पूर्ण;

अटल स्थिर काष्ठा panel_desc innolux_n156bge_l21 = अणु
	.modes = &innolux_n156bge_l21_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = अणु
		.width = 344,
		.height = 193,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X7X3_SPWG,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode innolux_p120zdg_bf1_mode = अणु
	.घड़ी = 206016,
	.hdisplay = 2160,
	.hsync_start = 2160 + 48,
	.hsync_end = 2160 + 48 + 32,
	.htotal = 2160 + 48 + 32 + 80,
	.vdisplay = 1440,
	.vsync_start = 1440 + 3,
	.vsync_end = 1440 + 3 + 10,
	.vtotal = 1440 + 3 + 10 + 27,
	.flags = DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc innolux_p120zdg_bf1 = अणु
	.modes = &innolux_p120zdg_bf1_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 254,
		.height = 169,
	पूर्ण,
	.delay = अणु
		.hpd_असलent_delay = 200,
		.unprepare = 500,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode innolux_zj070na_01p_mode = अणु
	.घड़ी = 51501,
	.hdisplay = 1024,
	.hsync_start = 1024 + 128,
	.hsync_end = 1024 + 128 + 64,
	.htotal = 1024 + 128 + 64 + 128,
	.vdisplay = 600,
	.vsync_start = 600 + 16,
	.vsync_end = 600 + 16 + 4,
	.vtotal = 600 + 16 + 4 + 16,
पूर्ण;

अटल स्थिर काष्ठा panel_desc innolux_zj070na_01p = अणु
	.modes = &innolux_zj070na_01p_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = अणु
		.width = 154,
		.height = 90,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode ivo_m133nwf4_r0_mode = अणु
	.घड़ी = 138778,
	.hdisplay = 1920,
	.hsync_start = 1920 + 24,
	.hsync_end = 1920 + 24 + 48,
	.htotal = 1920 + 24 + 48 + 88,
	.vdisplay = 1080,
	.vsync_start = 1080 + 3,
	.vsync_end = 1080 + 3 + 12,
	.vtotal = 1080 + 3 + 12 + 17,
	.flags = DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc ivo_m133nwf4_r0 = अणु
	.modes = &ivo_m133nwf4_r0_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 294,
		.height = 165,
	पूर्ण,
	.delay = अणु
		.hpd_असलent_delay = 200,
		.unprepare = 500,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
	.bus_flags = DRM_BUS_FLAG_DATA_MSB_TO_LSB,
	.connector_type = DRM_MODE_CONNECTOR_eDP,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode kingdisplay_kd116n21_30nv_a010_mode = अणु
	.घड़ी = 81000,
	.hdisplay = 1366,
	.hsync_start = 1366 + 40,
	.hsync_end = 1366 + 40 + 32,
	.htotal = 1366 + 40 + 32 + 62,
	.vdisplay = 768,
	.vsync_start = 768 + 5,
	.vsync_end = 768 + 5 + 5,
	.vtotal = 768 + 5 + 5 + 122,
	.flags = DRM_MODE_FLAG_NVSYNC | DRM_MODE_FLAG_NHSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc kingdisplay_kd116n21_30nv_a010 = अणु
	.modes = &kingdisplay_kd116n21_30nv_a010_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = अणु
		.width = 256,
		.height = 144,
	पूर्ण,
	.delay = अणु
		.hpd_असलent_delay = 200,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X18,
	.connector_type = DRM_MODE_CONNECTOR_eDP,
पूर्ण;

अटल स्थिर काष्ठा display_timing koe_tx14d24vm1bpa_timing = अणु
	.pixelघड़ी = अणु 5580000, 5850000, 6200000 पूर्ण,
	.hactive = अणु 320, 320, 320 पूर्ण,
	.hfront_porch = अणु 30, 30, 30 पूर्ण,
	.hback_porch = अणु 30, 30, 30 पूर्ण,
	.hsync_len = अणु 1, 5, 17 पूर्ण,
	.vactive = अणु 240, 240, 240 पूर्ण,
	.vfront_porch = अणु 6, 6, 6 पूर्ण,
	.vback_porch = अणु 5, 5, 5 पूर्ण,
	.vsync_len = अणु 1, 2, 11 पूर्ण,
	.flags = DISPLAY_FLAGS_DE_HIGH,
पूर्ण;

अटल स्थिर काष्ठा panel_desc koe_tx14d24vm1bpa = अणु
	.timings = &koe_tx14d24vm1bpa_timing,
	.num_timings = 1,
	.bpc = 6,
	.size = अणु
		.width = 115,
		.height = 86,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा display_timing koe_tx26d202vm0bwa_timing = अणु
	.pixelघड़ी = अणु 151820000, 156720000, 159780000 पूर्ण,
	.hactive = अणु 1920, 1920, 1920 पूर्ण,
	.hfront_porch = अणु 105, 130, 142 पूर्ण,
	.hback_porch = अणु 45, 70, 82 पूर्ण,
	.hsync_len = अणु 30, 30, 30 पूर्ण,
	.vactive = अणु 1200, 1200, 1200पूर्ण,
	.vfront_porch = अणु 3, 5, 10 पूर्ण,
	.vback_porch = अणु 2, 5, 10 पूर्ण,
	.vsync_len = अणु 5, 5, 5 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा panel_desc koe_tx26d202vm0bwa = अणु
	.timings = &koe_tx26d202vm0bwa_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = अणु
		.width = 217,
		.height = 136,
	पूर्ण,
	.delay = अणु
		.prepare = 1000,
		.enable = 1000,
		.unprepare = 1000,
		.disable = 1000,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X7X4_SPWG,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा display_timing koe_tx31d200vm0baa_timing = अणु
	.pixelघड़ी = अणु 39600000, 43200000, 48000000 पूर्ण,
	.hactive = अणु 1280, 1280, 1280 पूर्ण,
	.hfront_porch = अणु 16, 36, 56 पूर्ण,
	.hback_porch = अणु 16, 36, 56 पूर्ण,
	.hsync_len = अणु 8, 8, 8 पूर्ण,
	.vactive = अणु 480, 480, 480 पूर्ण,
	.vfront_porch = अणु 6, 21, 33 पूर्ण,
	.vback_porch = अणु 6, 21, 33 पूर्ण,
	.vsync_len = अणु 8, 8, 8 पूर्ण,
	.flags = DISPLAY_FLAGS_DE_HIGH,
पूर्ण;

अटल स्थिर काष्ठा panel_desc koe_tx31d200vm0baa = अणु
	.timings = &koe_tx31d200vm0baa_timing,
	.num_timings = 1,
	.bpc = 6,
	.size = अणु
		.width = 292,
		.height = 109,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X7X3_SPWG,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा display_timing kyo_tcg121xglp_timing = अणु
	.pixelघड़ी = अणु 52000000, 65000000, 71000000 पूर्ण,
	.hactive = अणु 1024, 1024, 1024 पूर्ण,
	.hfront_porch = अणु 2, 2, 2 पूर्ण,
	.hback_porch = अणु 2, 2, 2 पूर्ण,
	.hsync_len = अणु 86, 124, 244 पूर्ण,
	.vactive = अणु 768, 768, 768 पूर्ण,
	.vfront_porch = अणु 2, 2, 2 पूर्ण,
	.vback_porch = अणु 2, 2, 2 पूर्ण,
	.vsync_len = अणु 6, 34, 73 पूर्ण,
	.flags = DISPLAY_FLAGS_DE_HIGH,
पूर्ण;

अटल स्थिर काष्ठा panel_desc kyo_tcg121xglp = अणु
	.timings = &kyo_tcg121xglp_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = अणु
		.width = 246,
		.height = 184,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X7X4_SPWG,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode lemaker_bl035_rgb_002_mode = अणु
	.घड़ी = 7000,
	.hdisplay = 320,
	.hsync_start = 320 + 20,
	.hsync_end = 320 + 20 + 30,
	.htotal = 320 + 20 + 30 + 38,
	.vdisplay = 240,
	.vsync_start = 240 + 4,
	.vsync_end = 240 + 4 + 3,
	.vtotal = 240 + 4 + 3 + 15,
पूर्ण;

अटल स्थिर काष्ठा panel_desc lemaker_bl035_rgb_002 = अणु
	.modes = &lemaker_bl035_rgb_002_mode,
	.num_modes = 1,
	.size = अणु
		.width = 70,
		.height = 52,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
	.bus_flags = DRM_BUS_FLAG_DE_LOW,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode lg_lb070wv8_mode = अणु
	.घड़ी = 33246,
	.hdisplay = 800,
	.hsync_start = 800 + 88,
	.hsync_end = 800 + 88 + 80,
	.htotal = 800 + 88 + 80 + 88,
	.vdisplay = 480,
	.vsync_start = 480 + 10,
	.vsync_end = 480 + 10 + 25,
	.vtotal = 480 + 10 + 25 + 10,
पूर्ण;

अटल स्थिर काष्ठा panel_desc lg_lb070wv8 = अणु
	.modes = &lg_lb070wv8_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 151,
		.height = 91,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X7X4_SPWG,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode lg_lp079qx1_sp0v_mode = अणु
	.घड़ी = 200000,
	.hdisplay = 1536,
	.hsync_start = 1536 + 12,
	.hsync_end = 1536 + 12 + 16,
	.htotal = 1536 + 12 + 16 + 48,
	.vdisplay = 2048,
	.vsync_start = 2048 + 8,
	.vsync_end = 2048 + 8 + 4,
	.vtotal = 2048 + 8 + 4 + 8,
	.flags = DRM_MODE_FLAG_NVSYNC | DRM_MODE_FLAG_NHSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc lg_lp079qx1_sp0v = अणु
	.modes = &lg_lp079qx1_sp0v_mode,
	.num_modes = 1,
	.size = अणु
		.width = 129,
		.height = 171,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode lg_lp097qx1_spa1_mode = अणु
	.घड़ी = 205210,
	.hdisplay = 2048,
	.hsync_start = 2048 + 150,
	.hsync_end = 2048 + 150 + 5,
	.htotal = 2048 + 150 + 5 + 5,
	.vdisplay = 1536,
	.vsync_start = 1536 + 3,
	.vsync_end = 1536 + 3 + 1,
	.vtotal = 1536 + 3 + 1 + 9,
पूर्ण;

अटल स्थिर काष्ठा panel_desc lg_lp097qx1_spa1 = अणु
	.modes = &lg_lp097qx1_spa1_mode,
	.num_modes = 1,
	.size = अणु
		.width = 208,
		.height = 147,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode lg_lp120up1_mode = अणु
	.घड़ी = 162300,
	.hdisplay = 1920,
	.hsync_start = 1920 + 40,
	.hsync_end = 1920 + 40 + 40,
	.htotal = 1920 + 40 + 40+ 80,
	.vdisplay = 1280,
	.vsync_start = 1280 + 4,
	.vsync_end = 1280 + 4 + 4,
	.vtotal = 1280 + 4 + 4 + 12,
पूर्ण;

अटल स्थिर काष्ठा panel_desc lg_lp120up1 = अणु
	.modes = &lg_lp120up1_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 267,
		.height = 183,
	पूर्ण,
	.connector_type = DRM_MODE_CONNECTOR_eDP,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode lg_lp129qe_mode = अणु
	.घड़ी = 285250,
	.hdisplay = 2560,
	.hsync_start = 2560 + 48,
	.hsync_end = 2560 + 48 + 32,
	.htotal = 2560 + 48 + 32 + 80,
	.vdisplay = 1700,
	.vsync_start = 1700 + 3,
	.vsync_end = 1700 + 3 + 10,
	.vtotal = 1700 + 3 + 10 + 36,
पूर्ण;

अटल स्थिर काष्ठा panel_desc lg_lp129qe = अणु
	.modes = &lg_lp129qe_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 272,
		.height = 181,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा display_timing logictechno_lt161010_2nh_timing = अणु
	.pixelघड़ी = अणु 26400000, 33300000, 46800000 पूर्ण,
	.hactive = अणु 800, 800, 800 पूर्ण,
	.hfront_porch = अणु 16, 210, 354 पूर्ण,
	.hback_porch = अणु 46, 46, 46 पूर्ण,
	.hsync_len = अणु 1, 20, 40 पूर्ण,
	.vactive = अणु 480, 480, 480 पूर्ण,
	.vfront_porch = अणु 7, 22, 147 पूर्ण,
	.vback_porch = अणु 23, 23, 23 पूर्ण,
	.vsync_len = अणु 1, 10, 20 पूर्ण,
	.flags = DISPLAY_FLAGS_HSYNC_LOW | DISPLAY_FLAGS_VSYNC_LOW |
		 DISPLAY_FLAGS_DE_HIGH | DISPLAY_FLAGS_PIXDATA_POSEDGE |
		 DISPLAY_FLAGS_SYNC_POSEDGE,
पूर्ण;

अटल स्थिर काष्ठा panel_desc logictechno_lt161010_2nh = अणु
	.timings = &logictechno_lt161010_2nh_timing,
	.num_timings = 1,
	.size = अणु
		.width = 154,
		.height = 86,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X18,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH |
		     DRM_BUS_FLAG_PIXDATA_SAMPLE_NEGEDGE |
		     DRM_BUS_FLAG_SYNC_SAMPLE_NEGEDGE,
	.connector_type = DRM_MODE_CONNECTOR_DPI,
पूर्ण;

अटल स्थिर काष्ठा display_timing logictechno_lt170410_2whc_timing = अणु
	.pixelघड़ी = अणु 68900000, 71100000, 73400000 पूर्ण,
	.hactive = अणु 1280, 1280, 1280 पूर्ण,
	.hfront_porch = अणु 23, 60, 71 पूर्ण,
	.hback_porch = अणु 23, 60, 71 पूर्ण,
	.hsync_len = अणु 15, 40, 47 पूर्ण,
	.vactive = अणु 800, 800, 800 पूर्ण,
	.vfront_porch = अणु 5, 7, 10 पूर्ण,
	.vback_porch = अणु 5, 7, 10 पूर्ण,
	.vsync_len = अणु 6, 9, 12 पूर्ण,
	.flags = DISPLAY_FLAGS_HSYNC_LOW | DISPLAY_FLAGS_VSYNC_LOW |
		 DISPLAY_FLAGS_DE_HIGH | DISPLAY_FLAGS_PIXDATA_POSEDGE |
		 DISPLAY_FLAGS_SYNC_POSEDGE,
पूर्ण;

अटल स्थिर काष्ठा panel_desc logictechno_lt170410_2whc = अणु
	.timings = &logictechno_lt170410_2whc_timing,
	.num_timings = 1,
	.size = अणु
		.width = 217,
		.height = 136,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X7X4_SPWG,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode mitsubishi_aa070mc01_mode = अणु
	.घड़ी = 30400,
	.hdisplay = 800,
	.hsync_start = 800 + 0,
	.hsync_end = 800 + 1,
	.htotal = 800 + 0 + 1 + 160,
	.vdisplay = 480,
	.vsync_start = 480 + 0,
	.vsync_end = 480 + 48 + 1,
	.vtotal = 480 + 48 + 1 + 0,
	.flags = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode logicpd_type_28_mode = अणु
	.घड़ी = 9107,
	.hdisplay = 480,
	.hsync_start = 480 + 3,
	.hsync_end = 480 + 3 + 42,
	.htotal = 480 + 3 + 42 + 2,

	.vdisplay = 272,
	.vsync_start = 272 + 2,
	.vsync_end = 272 + 2 + 11,
	.vtotal = 272 + 2 + 11 + 3,
	.flags = DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc logicpd_type_28 = अणु
	.modes = &logicpd_type_28_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 105,
		.height = 67,
	पूर्ण,
	.delay = अणु
		.prepare = 200,
		.enable = 200,
		.unprepare = 200,
		.disable = 200,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH | DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE |
		     DRM_BUS_FLAG_SYNC_DRIVE_NEGEDGE,
	.connector_type = DRM_MODE_CONNECTOR_DPI,
पूर्ण;

अटल स्थिर काष्ठा panel_desc mitsubishi_aa070mc01 = अणु
	.modes = &mitsubishi_aa070mc01_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 152,
		.height = 91,
	पूर्ण,

	.delay = अणु
		.enable = 200,
		.unprepare = 200,
		.disable = 400,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X7X4_SPWG,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH,
पूर्ण;

अटल स्थिर काष्ठा display_timing nec_nl12880bc20_05_timing = अणु
	.pixelघड़ी = अणु 67000000, 71000000, 75000000 पूर्ण,
	.hactive = अणु 1280, 1280, 1280 पूर्ण,
	.hfront_porch = अणु 2, 30, 30 पूर्ण,
	.hback_porch = अणु 6, 100, 100 पूर्ण,
	.hsync_len = अणु 2, 30, 30 पूर्ण,
	.vactive = अणु 800, 800, 800 पूर्ण,
	.vfront_porch = अणु 5, 5, 5 पूर्ण,
	.vback_porch = अणु 11, 11, 11 पूर्ण,
	.vsync_len = अणु 7, 7, 7 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा panel_desc nec_nl12880bc20_05 = अणु
	.timings = &nec_nl12880bc20_05_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = अणु
		.width = 261,
		.height = 163,
	पूर्ण,
	.delay = अणु
		.enable = 50,
		.disable = 50,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X7X4_SPWG,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode nec_nl4827hc19_05b_mode = अणु
	.घड़ी = 10870,
	.hdisplay = 480,
	.hsync_start = 480 + 2,
	.hsync_end = 480 + 2 + 41,
	.htotal = 480 + 2 + 41 + 2,
	.vdisplay = 272,
	.vsync_start = 272 + 2,
	.vsync_end = 272 + 2 + 4,
	.vtotal = 272 + 2 + 4 + 2,
	.flags = DRM_MODE_FLAG_NVSYNC | DRM_MODE_FLAG_NHSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc nec_nl4827hc19_05b = अणु
	.modes = &nec_nl4827hc19_05b_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 95,
		.height = 54,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
	.bus_flags = DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode netron_dy_e231732_mode = अणु
	.घड़ी = 66000,
	.hdisplay = 1024,
	.hsync_start = 1024 + 160,
	.hsync_end = 1024 + 160 + 70,
	.htotal = 1024 + 160 + 70 + 90,
	.vdisplay = 600,
	.vsync_start = 600 + 127,
	.vsync_end = 600 + 127 + 20,
	.vtotal = 600 + 127 + 20 + 3,
पूर्ण;

अटल स्थिर काष्ठा panel_desc netron_dy_e231732 = अणु
	.modes = &netron_dy_e231732_mode,
	.num_modes = 1,
	.size = अणु
		.width = 154,
		.height = 87,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X18,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode neweast_wjfh116008a_modes[] = अणु
	अणु
		.घड़ी = 138500,
		.hdisplay = 1920,
		.hsync_start = 1920 + 48,
		.hsync_end = 1920 + 48 + 32,
		.htotal = 1920 + 48 + 32 + 80,
		.vdisplay = 1080,
		.vsync_start = 1080 + 3,
		.vsync_end = 1080 + 3 + 5,
		.vtotal = 1080 + 3 + 5 + 23,
		.flags = DRM_MODE_FLAG_NVSYNC | DRM_MODE_FLAG_NHSYNC,
	पूर्ण, अणु
		.घड़ी = 110920,
		.hdisplay = 1920,
		.hsync_start = 1920 + 48,
		.hsync_end = 1920 + 48 + 32,
		.htotal = 1920 + 48 + 32 + 80,
		.vdisplay = 1080,
		.vsync_start = 1080 + 3,
		.vsync_end = 1080 + 3 + 5,
		.vtotal = 1080 + 3 + 5 + 23,
		.flags = DRM_MODE_FLAG_NVSYNC | DRM_MODE_FLAG_NHSYNC,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा panel_desc neweast_wjfh116008a = अणु
	.modes = neweast_wjfh116008a_modes,
	.num_modes = 2,
	.bpc = 6,
	.size = अणु
		.width = 260,
		.height = 150,
	पूर्ण,
	.delay = अणु
		.prepare = 110,
		.enable = 20,
		.unprepare = 500,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X18,
	.connector_type = DRM_MODE_CONNECTOR_eDP,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode newhaven_nhd_43_480272ef_atxl_mode = अणु
	.घड़ी = 9000,
	.hdisplay = 480,
	.hsync_start = 480 + 2,
	.hsync_end = 480 + 2 + 41,
	.htotal = 480 + 2 + 41 + 2,
	.vdisplay = 272,
	.vsync_start = 272 + 2,
	.vsync_end = 272 + 2 + 10,
	.vtotal = 272 + 2 + 10 + 2,
	.flags = DRM_MODE_FLAG_NVSYNC | DRM_MODE_FLAG_NHSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc newhaven_nhd_43_480272ef_atxl = अणु
	.modes = &newhaven_nhd_43_480272ef_atxl_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 95,
		.height = 54,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH | DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE |
		     DRM_BUS_FLAG_SYNC_DRIVE_POSEDGE,
	.connector_type = DRM_MODE_CONNECTOR_DPI,
पूर्ण;

अटल स्थिर काष्ठा display_timing nlt_nl192108ac18_02d_timing = अणु
	.pixelघड़ी = अणु 130000000, 148350000, 163000000 पूर्ण,
	.hactive = अणु 1920, 1920, 1920 पूर्ण,
	.hfront_porch = अणु 80, 100, 100 पूर्ण,
	.hback_porch = अणु 100, 120, 120 पूर्ण,
	.hsync_len = अणु 50, 60, 60 पूर्ण,
	.vactive = अणु 1080, 1080, 1080 पूर्ण,
	.vfront_porch = अणु 12, 30, 30 पूर्ण,
	.vback_porch = अणु 4, 10, 10 पूर्ण,
	.vsync_len = अणु 4, 5, 5 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा panel_desc nlt_nl192108ac18_02d = अणु
	.timings = &nlt_nl192108ac18_02d_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = अणु
		.width = 344,
		.height = 194,
	पूर्ण,
	.delay = अणु
		.unprepare = 500,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X7X4_SPWG,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode nvd_9128_mode = अणु
	.घड़ी = 29500,
	.hdisplay = 800,
	.hsync_start = 800 + 130,
	.hsync_end = 800 + 130 + 98,
	.htotal = 800 + 0 + 130 + 98,
	.vdisplay = 480,
	.vsync_start = 480 + 10,
	.vsync_end = 480 + 10 + 50,
	.vtotal = 480 + 0 + 10 + 50,
पूर्ण;

अटल स्थिर काष्ठा panel_desc nvd_9128 = अणु
	.modes = &nvd_9128_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 156,
		.height = 88,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X7X4_SPWG,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा display_timing okaya_rs800480t_7x0gp_timing = अणु
	.pixelघड़ी = अणु 30000000, 30000000, 40000000 पूर्ण,
	.hactive = अणु 800, 800, 800 पूर्ण,
	.hfront_porch = अणु 40, 40, 40 पूर्ण,
	.hback_porch = अणु 40, 40, 40 पूर्ण,
	.hsync_len = अणु 1, 48, 48 पूर्ण,
	.vactive = अणु 480, 480, 480 पूर्ण,
	.vfront_porch = अणु 13, 13, 13 पूर्ण,
	.vback_porch = अणु 29, 29, 29 पूर्ण,
	.vsync_len = अणु 3, 3, 3 पूर्ण,
	.flags = DISPLAY_FLAGS_DE_HIGH,
पूर्ण;

अटल स्थिर काष्ठा panel_desc okaya_rs800480t_7x0gp = अणु
	.timings = &okaya_rs800480t_7x0gp_timing,
	.num_timings = 1,
	.bpc = 6,
	.size = अणु
		.width = 154,
		.height = 87,
	पूर्ण,
	.delay = अणु
		.prepare = 41,
		.enable = 50,
		.unprepare = 41,
		.disable = 50,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X18,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode olimex_lcd_olinuxino_43ts_mode = अणु
	.घड़ी = 9000,
	.hdisplay = 480,
	.hsync_start = 480 + 5,
	.hsync_end = 480 + 5 + 30,
	.htotal = 480 + 5 + 30 + 10,
	.vdisplay = 272,
	.vsync_start = 272 + 8,
	.vsync_end = 272 + 8 + 5,
	.vtotal = 272 + 8 + 5 + 3,
पूर्ण;

अटल स्थिर काष्ठा panel_desc olimex_lcd_olinuxino_43ts = अणु
	.modes = &olimex_lcd_olinuxino_43ts_mode,
	.num_modes = 1,
	.size = अणु
		.width = 95,
		.height = 54,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
पूर्ण;

/*
 * 800x480 CVT. The panel appears to be quite accepting, at least as far as
 * pixel घड़ीs, but this is the timing that was being used in the Adafruit
 * installation inकाष्ठाions.
 */
अटल स्थिर काष्ठा drm_display_mode ontat_yx700wv03_mode = अणु
	.घड़ी = 29500,
	.hdisplay = 800,
	.hsync_start = 824,
	.hsync_end = 896,
	.htotal = 992,
	.vdisplay = 480,
	.vsync_start = 483,
	.vsync_end = 493,
	.vtotal = 500,
	.flags = DRM_MODE_FLAG_NVSYNC | DRM_MODE_FLAG_NHSYNC,
पूर्ण;

/*
 * Specअगरication at:
 * https://www.adafruit.com/images/product-files/2406/c3163.pdf
 */
अटल स्थिर काष्ठा panel_desc ontat_yx700wv03 = अणु
	.modes = &ontat_yx700wv03_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 154,
		.height = 83,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X18,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode ortustech_com37h3m_mode  = अणु
	.घड़ी = 22230,
	.hdisplay = 480,
	.hsync_start = 480 + 40,
	.hsync_end = 480 + 40 + 10,
	.htotal = 480 + 40 + 10 + 40,
	.vdisplay = 640,
	.vsync_start = 640 + 4,
	.vsync_end = 640 + 4 + 2,
	.vtotal = 640 + 4 + 2 + 4,
	.flags = DRM_MODE_FLAG_NVSYNC | DRM_MODE_FLAG_NHSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc ortustech_com37h3m = अणु
	.modes = &ortustech_com37h3m_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 56,	/* 56.16mm */
		.height = 75,	/* 74.88mm */
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH | DRM_BUS_FLAG_PIXDATA_SAMPLE_NEGEDGE |
		     DRM_BUS_FLAG_SYNC_DRIVE_POSEDGE,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode ortustech_com43h4m85ulc_mode  = अणु
	.घड़ी = 25000,
	.hdisplay = 480,
	.hsync_start = 480 + 10,
	.hsync_end = 480 + 10 + 10,
	.htotal = 480 + 10 + 10 + 15,
	.vdisplay = 800,
	.vsync_start = 800 + 3,
	.vsync_end = 800 + 3 + 3,
	.vtotal = 800 + 3 + 3 + 3,
पूर्ण;

अटल स्थिर काष्ठा panel_desc ortustech_com43h4m85ulc = अणु
	.modes = &ortustech_com43h4m85ulc_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = अणु
		.width = 56,
		.height = 93,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X18,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH | DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE,
	.connector_type = DRM_MODE_CONNECTOR_DPI,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode osddisplays_osd070t1718_19ts_mode  = अणु
	.घड़ी = 33000,
	.hdisplay = 800,
	.hsync_start = 800 + 210,
	.hsync_end = 800 + 210 + 30,
	.htotal = 800 + 210 + 30 + 16,
	.vdisplay = 480,
	.vsync_start = 480 + 22,
	.vsync_end = 480 + 22 + 13,
	.vtotal = 480 + 22 + 13 + 10,
	.flags = DRM_MODE_FLAG_NVSYNC | DRM_MODE_FLAG_NHSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc osddisplays_osd070t1718_19ts = अणु
	.modes = &osddisplays_osd070t1718_19ts_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 152,
		.height = 91,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH | DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE |
		DRM_BUS_FLAG_SYNC_DRIVE_POSEDGE,
	.connector_type = DRM_MODE_CONNECTOR_DPI,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode pda_91_00156_a0_mode = अणु
	.घड़ी = 33300,
	.hdisplay = 800,
	.hsync_start = 800 + 1,
	.hsync_end = 800 + 1 + 64,
	.htotal = 800 + 1 + 64 + 64,
	.vdisplay = 480,
	.vsync_start = 480 + 1,
	.vsync_end = 480 + 1 + 23,
	.vtotal = 480 + 1 + 23 + 22,
पूर्ण;

अटल स्थिर काष्ठा panel_desc pda_91_00156_a0  = अणु
	.modes = &pda_91_00156_a0_mode,
	.num_modes = 1,
	.size = अणु
		.width = 152,
		.height = 91,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode घातertip_ph800480t013_idf02_mode = अणु
	.घड़ी = 24750,
	.hdisplay = 800,
	.hsync_start = 800 + 54,
	.hsync_end = 800 + 54 + 2,
	.htotal = 800 + 54 + 2 + 44,
	.vdisplay = 480,
	.vsync_start = 480 + 49,
	.vsync_end = 480 + 49 + 2,
	.vtotal = 480 + 49 + 2 + 22,
पूर्ण;

अटल स्थिर काष्ठा panel_desc घातertip_ph800480t013_idf02  = अणु
	.modes = &घातertip_ph800480t013_idf02_mode,
	.num_modes = 1,
	.size = अणु
		.width = 152,
		.height = 91,
	पूर्ण,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH |
		     DRM_BUS_FLAG_PIXDATA_SAMPLE_NEGEDGE |
		     DRM_BUS_FLAG_SYNC_SAMPLE_NEGEDGE,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
	.connector_type = DRM_MODE_CONNECTOR_DPI,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode qd43003c0_40_mode = अणु
	.घड़ी = 9000,
	.hdisplay = 480,
	.hsync_start = 480 + 8,
	.hsync_end = 480 + 8 + 4,
	.htotal = 480 + 8 + 4 + 39,
	.vdisplay = 272,
	.vsync_start = 272 + 4,
	.vsync_end = 272 + 4 + 10,
	.vtotal = 272 + 4 + 10 + 2,
पूर्ण;

अटल स्थिर काष्ठा panel_desc qd43003c0_40 = अणु
	.modes = &qd43003c0_40_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 95,
		.height = 53,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
पूर्ण;

अटल स्थिर काष्ठा display_timing rocktech_rk070er9427_timing = अणु
	.pixelघड़ी = अणु 26400000, 33300000, 46800000 पूर्ण,
	.hactive = अणु 800, 800, 800 पूर्ण,
	.hfront_porch = अणु 16, 210, 354 पूर्ण,
	.hback_porch = अणु 46, 46, 46 पूर्ण,
	.hsync_len = अणु 1, 1, 1 पूर्ण,
	.vactive = अणु 480, 480, 480 पूर्ण,
	.vfront_porch = अणु 7, 22, 147 पूर्ण,
	.vback_porch = अणु 23, 23, 23 पूर्ण,
	.vsync_len = अणु 1, 1, 1 पूर्ण,
	.flags = DISPLAY_FLAGS_DE_HIGH,
पूर्ण;

अटल स्थिर काष्ठा panel_desc rocktech_rk070er9427 = अणु
	.timings = &rocktech_rk070er9427_timing,
	.num_timings = 1,
	.bpc = 6,
	.size = अणु
		.width = 154,
		.height = 86,
	पूर्ण,
	.delay = अणु
		.prepare = 41,
		.enable = 50,
		.unprepare = 41,
		.disable = 50,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X18,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode rocktech_rk101ii01d_ct_mode = अणु
	.घड़ी = 71100,
	.hdisplay = 1280,
	.hsync_start = 1280 + 48,
	.hsync_end = 1280 + 48 + 32,
	.htotal = 1280 + 48 + 32 + 80,
	.vdisplay = 800,
	.vsync_start = 800 + 2,
	.vsync_end = 800 + 2 + 5,
	.vtotal = 800 + 2 + 5 + 16,
पूर्ण;

अटल स्थिर काष्ठा panel_desc rocktech_rk101ii01d_ct = अणु
	.modes = &rocktech_rk101ii01d_ct_mode,
	.num_modes = 1,
	.size = अणु
		.width = 217,
		.height = 136,
	पूर्ण,
	.delay = अणु
		.prepare = 50,
		.disable = 50,
	पूर्ण,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X7X4_SPWG,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode samsung_lsn122dl01_c01_mode = अणु
	.घड़ी = 271560,
	.hdisplay = 2560,
	.hsync_start = 2560 + 48,
	.hsync_end = 2560 + 48 + 32,
	.htotal = 2560 + 48 + 32 + 80,
	.vdisplay = 1600,
	.vsync_start = 1600 + 2,
	.vsync_end = 1600 + 2 + 5,
	.vtotal = 1600 + 2 + 5 + 57,
पूर्ण;

अटल स्थिर काष्ठा panel_desc samsung_lsn122dl01_c01 = अणु
	.modes = &samsung_lsn122dl01_c01_mode,
	.num_modes = 1,
	.size = अणु
		.width = 263,
		.height = 164,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode samsung_ltn101nt05_mode = अणु
	.घड़ी = 54030,
	.hdisplay = 1024,
	.hsync_start = 1024 + 24,
	.hsync_end = 1024 + 24 + 136,
	.htotal = 1024 + 24 + 136 + 160,
	.vdisplay = 600,
	.vsync_start = 600 + 3,
	.vsync_end = 600 + 3 + 6,
	.vtotal = 600 + 3 + 6 + 61,
पूर्ण;

अटल स्थिर काष्ठा panel_desc samsung_ltn101nt05 = अणु
	.modes = &samsung_ltn101nt05_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = अणु
		.width = 223,
		.height = 125,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X7X3_SPWG,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode samsung_ltn140at29_301_mode = अणु
	.घड़ी = 76300,
	.hdisplay = 1366,
	.hsync_start = 1366 + 64,
	.hsync_end = 1366 + 64 + 48,
	.htotal = 1366 + 64 + 48 + 128,
	.vdisplay = 768,
	.vsync_start = 768 + 2,
	.vsync_end = 768 + 2 + 5,
	.vtotal = 768 + 2 + 5 + 17,
पूर्ण;

अटल स्थिर काष्ठा panel_desc samsung_ltn140at29_301 = अणु
	.modes = &samsung_ltn140at29_301_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = अणु
		.width = 320,
		.height = 187,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा display_timing satoz_sat050at40h12r2_timing = अणु
	.pixelघड़ी = अणु33300000, 33300000, 50000000पूर्ण,
	.hactive = अणु800, 800, 800पूर्ण,
	.hfront_porch = अणु16, 210, 354पूर्ण,
	.hback_porch = अणु46, 46, 46पूर्ण,
	.hsync_len = अणु1, 1, 40पूर्ण,
	.vactive = अणु480, 480, 480पूर्ण,
	.vfront_porch = अणु7, 22, 147पूर्ण,
	.vback_porch = अणु23, 23, 23पूर्ण,
	.vsync_len = अणु1, 1, 20पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा panel_desc satoz_sat050at40h12r2 = अणु
	.timings = &satoz_sat050at40h12r2_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = अणु
		.width = 108,
		.height = 65,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X7X4_SPWG,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode sharp_ld_d5116z01b_mode = अणु
	.घड़ी = 168480,
	.hdisplay = 1920,
	.hsync_start = 1920 + 48,
	.hsync_end = 1920 + 48 + 32,
	.htotal = 1920 + 48 + 32 + 80,
	.vdisplay = 1280,
	.vsync_start = 1280 + 3,
	.vsync_end = 1280 + 3 + 10,
	.vtotal = 1280 + 3 + 10 + 57,
	.flags = DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc sharp_ld_d5116z01b = अणु
	.modes = &sharp_ld_d5116z01b_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 260,
		.height = 120,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
	.bus_flags = DRM_BUS_FLAG_DATA_MSB_TO_LSB,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode sharp_lq070y3dg3b_mode = अणु
	.घड़ी = 33260,
	.hdisplay = 800,
	.hsync_start = 800 + 64,
	.hsync_end = 800 + 64 + 128,
	.htotal = 800 + 64 + 128 + 64,
	.vdisplay = 480,
	.vsync_start = 480 + 8,
	.vsync_end = 480 + 8 + 2,
	.vtotal = 480 + 8 + 2 + 35,
	.flags = DISPLAY_FLAGS_PIXDATA_POSEDGE,
पूर्ण;

अटल स्थिर काष्ठा panel_desc sharp_lq070y3dg3b = अणु
	.modes = &sharp_lq070y3dg3b_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 152,	/* 152.4mm */
		.height = 91,	/* 91.4mm */
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH | DRM_BUS_FLAG_PIXDATA_SAMPLE_NEGEDGE |
		     DRM_BUS_FLAG_SYNC_DRIVE_POSEDGE,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode sharp_lq035q7db03_mode = अणु
	.घड़ी = 5500,
	.hdisplay = 240,
	.hsync_start = 240 + 16,
	.hsync_end = 240 + 16 + 7,
	.htotal = 240 + 16 + 7 + 5,
	.vdisplay = 320,
	.vsync_start = 320 + 9,
	.vsync_end = 320 + 9 + 1,
	.vtotal = 320 + 9 + 1 + 7,
पूर्ण;

अटल स्थिर काष्ठा panel_desc sharp_lq035q7db03 = अणु
	.modes = &sharp_lq035q7db03_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = अणु
		.width = 54,
		.height = 72,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X18,
पूर्ण;

अटल स्थिर काष्ठा display_timing sharp_lq101k1ly04_timing = अणु
	.pixelघड़ी = अणु 60000000, 65000000, 80000000 पूर्ण,
	.hactive = अणु 1280, 1280, 1280 पूर्ण,
	.hfront_porch = अणु 20, 20, 20 पूर्ण,
	.hback_porch = अणु 20, 20, 20 पूर्ण,
	.hsync_len = अणु 10, 10, 10 पूर्ण,
	.vactive = अणु 800, 800, 800 पूर्ण,
	.vfront_porch = अणु 4, 4, 4 पूर्ण,
	.vback_porch = अणु 4, 4, 4 पूर्ण,
	.vsync_len = अणु 4, 4, 4 पूर्ण,
	.flags = DISPLAY_FLAGS_PIXDATA_POSEDGE,
पूर्ण;

अटल स्थिर काष्ठा panel_desc sharp_lq101k1ly04 = अणु
	.timings = &sharp_lq101k1ly04_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = अणु
		.width = 217,
		.height = 136,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X7X4_JEIDA,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा display_timing sharp_lq123p1jx31_timing = अणु
	.pixelघड़ी = अणु 252750000, 252750000, 266604720 पूर्ण,
	.hactive = अणु 2400, 2400, 2400 पूर्ण,
	.hfront_porch = अणु 48, 48, 48 पूर्ण,
	.hback_porch = अणु 80, 80, 84 पूर्ण,
	.hsync_len = अणु 32, 32, 32 पूर्ण,
	.vactive = अणु 1600, 1600, 1600 पूर्ण,
	.vfront_porch = अणु 3, 3, 3 पूर्ण,
	.vback_porch = अणु 33, 33, 120 पूर्ण,
	.vsync_len = अणु 10, 10, 10 पूर्ण,
	.flags = DISPLAY_FLAGS_VSYNC_LOW | DISPLAY_FLAGS_HSYNC_LOW,
पूर्ण;

अटल स्थिर काष्ठा panel_desc sharp_lq123p1jx31 = अणु
	.timings = &sharp_lq123p1jx31_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = अणु
		.width = 259,
		.height = 173,
	पूर्ण,
	.delay = अणु
		.prepare = 110,
		.enable = 50,
		.unprepare = 550,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode sharp_ls020b1dd01d_modes[] = अणु
	अणु /* 50 Hz */
		.घड़ी = 3000,
		.hdisplay = 240,
		.hsync_start = 240 + 58,
		.hsync_end = 240 + 58 + 1,
		.htotal = 240 + 58 + 1 + 1,
		.vdisplay = 160,
		.vsync_start = 160 + 24,
		.vsync_end = 160 + 24 + 10,
		.vtotal = 160 + 24 + 10 + 6,
		.flags = DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC,
	पूर्ण,
	अणु /* 60 Hz */
		.घड़ी = 3000,
		.hdisplay = 240,
		.hsync_start = 240 + 8,
		.hsync_end = 240 + 8 + 1,
		.htotal = 240 + 8 + 1 + 1,
		.vdisplay = 160,
		.vsync_start = 160 + 24,
		.vsync_end = 160 + 24 + 10,
		.vtotal = 160 + 24 + 10 + 6,
		.flags = DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा panel_desc sharp_ls020b1dd01d = अणु
	.modes = sharp_ls020b1dd01d_modes,
	.num_modes = ARRAY_SIZE(sharp_ls020b1dd01d_modes),
	.bpc = 6,
	.size = अणु
		.width = 42,
		.height = 28,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB565_1X16,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH
		   | DRM_BUS_FLAG_PIXDATA_SAMPLE_POSEDGE
		   | DRM_BUS_FLAG_SHARP_SIGNALS,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode shelly_sca07010_bfn_lnn_mode = अणु
	.घड़ी = 33300,
	.hdisplay = 800,
	.hsync_start = 800 + 1,
	.hsync_end = 800 + 1 + 64,
	.htotal = 800 + 1 + 64 + 64,
	.vdisplay = 480,
	.vsync_start = 480 + 1,
	.vsync_end = 480 + 1 + 23,
	.vtotal = 480 + 1 + 23 + 22,
पूर्ण;

अटल स्थिर काष्ठा panel_desc shelly_sca07010_bfn_lnn = अणु
	.modes = &shelly_sca07010_bfn_lnn_mode,
	.num_modes = 1,
	.size = अणु
		.width = 152,
		.height = 91,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X18,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode starry_kr070pe2t_mode = अणु
	.घड़ी = 33000,
	.hdisplay = 800,
	.hsync_start = 800 + 209,
	.hsync_end = 800 + 209 + 1,
	.htotal = 800 + 209 + 1 + 45,
	.vdisplay = 480,
	.vsync_start = 480 + 22,
	.vsync_end = 480 + 22 + 1,
	.vtotal = 480 + 22 + 1 + 22,
पूर्ण;

अटल स्थिर काष्ठा panel_desc starry_kr070pe2t = अणु
	.modes = &starry_kr070pe2t_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 152,
		.height = 86,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH | DRM_BUS_FLAG_PIXDATA_DRIVE_NEGEDGE,
	.connector_type = DRM_MODE_CONNECTOR_DPI,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode starry_kr122ea0sra_mode = अणु
	.घड़ी = 147000,
	.hdisplay = 1920,
	.hsync_start = 1920 + 16,
	.hsync_end = 1920 + 16 + 16,
	.htotal = 1920 + 16 + 16 + 32,
	.vdisplay = 1200,
	.vsync_start = 1200 + 15,
	.vsync_end = 1200 + 15 + 2,
	.vtotal = 1200 + 15 + 2 + 18,
	.flags = DRM_MODE_FLAG_NVSYNC | DRM_MODE_FLAG_NHSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc starry_kr122ea0sra = अणु
	.modes = &starry_kr122ea0sra_mode,
	.num_modes = 1,
	.size = अणु
		.width = 263,
		.height = 164,
	पूर्ण,
	.delay = अणु
		.prepare = 10 + 200,
		.enable = 50,
		.unprepare = 10 + 500,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode tfc_s9700rtwv43tr_01b_mode = अणु
	.घड़ी = 30000,
	.hdisplay = 800,
	.hsync_start = 800 + 39,
	.hsync_end = 800 + 39 + 47,
	.htotal = 800 + 39 + 47 + 39,
	.vdisplay = 480,
	.vsync_start = 480 + 13,
	.vsync_end = 480 + 13 + 2,
	.vtotal = 480 + 13 + 2 + 29,
पूर्ण;

अटल स्थिर काष्ठा panel_desc tfc_s9700rtwv43tr_01b = अणु
	.modes = &tfc_s9700rtwv43tr_01b_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 155,
		.height = 90,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH | DRM_BUS_FLAG_PIXDATA_SAMPLE_NEGEDGE,
पूर्ण;

अटल स्थिर काष्ठा display_timing tianma_पंचांग070jdhg30_timing = अणु
	.pixelघड़ी = अणु 62600000, 68200000, 78100000 पूर्ण,
	.hactive = अणु 1280, 1280, 1280 पूर्ण,
	.hfront_porch = अणु 15, 64, 159 पूर्ण,
	.hback_porch = अणु 5, 5, 5 पूर्ण,
	.hsync_len = अणु 1, 1, 256 पूर्ण,
	.vactive = अणु 800, 800, 800 पूर्ण,
	.vfront_porch = अणु 3, 40, 99 पूर्ण,
	.vback_porch = अणु 2, 2, 2 पूर्ण,
	.vsync_len = अणु 1, 1, 128 पूर्ण,
	.flags = DISPLAY_FLAGS_DE_HIGH,
पूर्ण;

अटल स्थिर काष्ठा panel_desc tianma_पंचांग070jdhg30 = अणु
	.timings = &tianma_पंचांग070jdhg30_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = अणु
		.width = 151,
		.height = 95,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X7X4_SPWG,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा panel_desc tianma_पंचांग070jvhg33 = अणु
	.timings = &tianma_पंचांग070jdhg30_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = अणु
		.width = 150,
		.height = 94,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X7X4_SPWG,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा display_timing tianma_पंचांग070rvhg71_timing = अणु
	.pixelघड़ी = अणु 27700000, 29200000, 39600000 पूर्ण,
	.hactive = अणु 800, 800, 800 पूर्ण,
	.hfront_porch = अणु 12, 40, 212 पूर्ण,
	.hback_porch = अणु 88, 88, 88 पूर्ण,
	.hsync_len = अणु 1, 1, 40 पूर्ण,
	.vactive = अणु 480, 480, 480 पूर्ण,
	.vfront_porch = अणु 1, 13, 88 पूर्ण,
	.vback_porch = अणु 32, 32, 32 पूर्ण,
	.vsync_len = अणु 1, 1, 3 पूर्ण,
	.flags = DISPLAY_FLAGS_DE_HIGH,
पूर्ण;

अटल स्थिर काष्ठा panel_desc tianma_पंचांग070rvhg71 = अणु
	.timings = &tianma_पंचांग070rvhg71_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = अणु
		.width = 154,
		.height = 86,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X7X4_SPWG,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode ti_nspire_cx_lcd_mode[] = अणु
	अणु
		.घड़ी = 10000,
		.hdisplay = 320,
		.hsync_start = 320 + 50,
		.hsync_end = 320 + 50 + 6,
		.htotal = 320 + 50 + 6 + 38,
		.vdisplay = 240,
		.vsync_start = 240 + 3,
		.vsync_end = 240 + 3 + 1,
		.vtotal = 240 + 3 + 1 + 17,
		.flags = DRM_MODE_FLAG_NVSYNC | DRM_MODE_FLAG_NHSYNC,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा panel_desc ti_nspire_cx_lcd_panel = अणु
	.modes = ti_nspire_cx_lcd_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 65,
		.height = 49,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
	.bus_flags = DRM_BUS_FLAG_PIXDATA_SAMPLE_POSEDGE,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode ti_nspire_classic_lcd_mode[] = अणु
	अणु
		.घड़ी = 10000,
		.hdisplay = 320,
		.hsync_start = 320 + 6,
		.hsync_end = 320 + 6 + 6,
		.htotal = 320 + 6 + 6 + 6,
		.vdisplay = 240,
		.vsync_start = 240 + 0,
		.vsync_end = 240 + 0 + 1,
		.vtotal = 240 + 0 + 1 + 0,
		.flags = DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा panel_desc ti_nspire_classic_lcd_panel = अणु
	.modes = ti_nspire_classic_lcd_mode,
	.num_modes = 1,
	/* The grayscale panel has 8 bit क्रम the color .. Y (black) */
	.bpc = 8,
	.size = अणु
		.width = 71,
		.height = 53,
	पूर्ण,
	/* This is the grayscale bus क्रमmat */
	.bus_क्रमmat = MEDIA_BUS_FMT_Y8_1X8,
	.bus_flags = DRM_BUS_FLAG_PIXDATA_SAMPLE_NEGEDGE,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode toshiba_lt089ac29000_mode = अणु
	.घड़ी = 79500,
	.hdisplay = 1280,
	.hsync_start = 1280 + 192,
	.hsync_end = 1280 + 192 + 128,
	.htotal = 1280 + 192 + 128 + 64,
	.vdisplay = 768,
	.vsync_start = 768 + 20,
	.vsync_end = 768 + 20 + 7,
	.vtotal = 768 + 20 + 7 + 3,
पूर्ण;

अटल स्थिर काष्ठा panel_desc toshiba_lt089ac29000 = अणु
	.modes = &toshiba_lt089ac29000_mode,
	.num_modes = 1,
	.size = अणु
		.width = 194,
		.height = 116,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X7X4_JEIDA,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode tpk_f07a_0102_mode = अणु
	.घड़ी = 33260,
	.hdisplay = 800,
	.hsync_start = 800 + 40,
	.hsync_end = 800 + 40 + 128,
	.htotal = 800 + 40 + 128 + 88,
	.vdisplay = 480,
	.vsync_start = 480 + 10,
	.vsync_end = 480 + 10 + 2,
	.vtotal = 480 + 10 + 2 + 33,
पूर्ण;

अटल स्थिर काष्ठा panel_desc tpk_f07a_0102 = अणु
	.modes = &tpk_f07a_0102_mode,
	.num_modes = 1,
	.size = अणु
		.width = 152,
		.height = 91,
	पूर्ण,
	.bus_flags = DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode tpk_f10a_0102_mode = अणु
	.घड़ी = 45000,
	.hdisplay = 1024,
	.hsync_start = 1024 + 176,
	.hsync_end = 1024 + 176 + 5,
	.htotal = 1024 + 176 + 5 + 88,
	.vdisplay = 600,
	.vsync_start = 600 + 20,
	.vsync_end = 600 + 20 + 5,
	.vtotal = 600 + 20 + 5 + 25,
पूर्ण;

अटल स्थिर काष्ठा panel_desc tpk_f10a_0102 = अणु
	.modes = &tpk_f10a_0102_mode,
	.num_modes = 1,
	.size = अणु
		.width = 223,
		.height = 125,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा display_timing urt_umsh_8596md_timing = अणु
	.pixelघड़ी = अणु 33260000, 33260000, 33260000 पूर्ण,
	.hactive = अणु 800, 800, 800 पूर्ण,
	.hfront_porch = अणु 41, 41, 41 पूर्ण,
	.hback_porch = अणु 216 - 128, 216 - 128, 216 - 128 पूर्ण,
	.hsync_len = अणु 71, 128, 128 पूर्ण,
	.vactive = अणु 480, 480, 480 पूर्ण,
	.vfront_porch = अणु 10, 10, 10 पूर्ण,
	.vback_porch = अणु 35 - 2, 35 - 2, 35 - 2 पूर्ण,
	.vsync_len = अणु 2, 2, 2 पूर्ण,
	.flags = DISPLAY_FLAGS_DE_HIGH | DISPLAY_FLAGS_PIXDATA_NEGEDGE |
		DISPLAY_FLAGS_HSYNC_LOW | DISPLAY_FLAGS_VSYNC_LOW,
पूर्ण;

अटल स्थिर काष्ठा panel_desc urt_umsh_8596md_lvds = अणु
	.timings = &urt_umsh_8596md_timing,
	.num_timings = 1,
	.bpc = 6,
	.size = अणु
		.width = 152,
		.height = 91,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X7X3_SPWG,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा panel_desc urt_umsh_8596md_parallel = अणु
	.timings = &urt_umsh_8596md_timing,
	.num_timings = 1,
	.bpc = 6,
	.size = अणु
		.width = 152,
		.height = 91,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X18,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode vl050_8048nt_c01_mode = अणु
	.घड़ी = 33333,
	.hdisplay = 800,
	.hsync_start = 800 + 210,
	.hsync_end = 800 + 210 + 20,
	.htotal = 800 + 210 + 20 + 46,
	.vdisplay =  480,
	.vsync_start = 480 + 22,
	.vsync_end = 480 + 22 + 10,
	.vtotal = 480 + 22 + 10 + 23,
	.flags = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc vl050_8048nt_c01 = अणु
	.modes = &vl050_8048nt_c01_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 120,
		.height = 76,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH | DRM_BUS_FLAG_PIXDATA_SAMPLE_NEGEDGE,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode winstar_wf35ltiacd_mode = अणु
	.घड़ी = 6410,
	.hdisplay = 320,
	.hsync_start = 320 + 20,
	.hsync_end = 320 + 20 + 30,
	.htotal = 320 + 20 + 30 + 38,
	.vdisplay = 240,
	.vsync_start = 240 + 4,
	.vsync_end = 240 + 4 + 3,
	.vtotal = 240 + 4 + 3 + 15,
	.flags = DRM_MODE_FLAG_NVSYNC | DRM_MODE_FLAG_NHSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc winstar_wf35ltiacd = अणु
	.modes = &winstar_wf35ltiacd_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 70,
		.height = 53,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode yes_optoelectronics_ytc700tlag_05_201c_mode = अणु
	.घड़ी = 51200,
	.hdisplay = 1024,
	.hsync_start = 1024 + 100,
	.hsync_end = 1024 + 100 + 100,
	.htotal = 1024 + 100 + 100 + 120,
	.vdisplay = 600,
	.vsync_start = 600 + 10,
	.vsync_end = 600 + 10 + 10,
	.vtotal = 600 + 10 + 10 + 15,
	.flags = DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc yes_optoelectronics_ytc700tlag_05_201c = अणु
	.modes = &yes_optoelectronics_ytc700tlag_05_201c_mode,
	.num_modes = 1,
	.bpc = 6,
	.size = अणु
		.width = 154,
		.height = 90,
	पूर्ण,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X7X4_SPWG,
	.connector_type = DRM_MODE_CONNECTOR_LVDS,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode arm_rtsm_mode[] = अणु
	अणु
		.घड़ी = 65000,
		.hdisplay = 1024,
		.hsync_start = 1024 + 24,
		.hsync_end = 1024 + 24 + 136,
		.htotal = 1024 + 24 + 136 + 160,
		.vdisplay = 768,
		.vsync_start = 768 + 3,
		.vsync_end = 768 + 3 + 6,
		.vtotal = 768 + 3 + 6 + 29,
		.flags = DRM_MODE_FLAG_NVSYNC | DRM_MODE_FLAG_NHSYNC,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा panel_desc arm_rtsm = अणु
	.modes = arm_rtsm_mode,
	.num_modes = 1,
	.bpc = 8,
	.size = अणु
		.width = 400,
		.height = 300,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
पूर्ण;

अटल स्थिर काष्ठा of_device_id platक्रमm_of_match[] = अणु
	अणु
		.compatible = "ampire,am-1280800n3tzqw-t00h",
		.data = &ampire_am_1280800n3tzqw_t00h,
	पूर्ण, अणु
		.compatible = "ampire,am-480272h3tmqw-t01h",
		.data = &ampire_am_480272h3पंचांगqw_t01h,
	पूर्ण, अणु
		.compatible = "ampire,am800480r3tmqwa1h",
		.data = &ampire_am800480r3पंचांगqwa1h,
	पूर्ण, अणु
		.compatible = "arm,rtsm-display",
		.data = &arm_rtsm,
	पूर्ण, अणु
		.compatible = "armadeus,st0700-adapt",
		.data = &armadeus_st0700_adapt,
	पूर्ण, अणु
		.compatible = "auo,b101aw03",
		.data = &auo_b101aw03,
	पूर्ण, अणु
		.compatible = "auo,b101ean01",
		.data = &auo_b101ean01,
	पूर्ण, अणु
		.compatible = "auo,b101xtn01",
		.data = &auo_b101xtn01,
	पूर्ण, अणु
		.compatible = "auo,b116xa01",
		.data = &auo_b116xak01,
	पूर्ण, अणु
		.compatible = "auo,b116xw03",
		.data = &auo_b116xw03,
	पूर्ण, अणु
		.compatible = "auo,b133htn01",
		.data = &auo_b133htn01,
	पूर्ण, अणु
		.compatible = "auo,b133xtn01",
		.data = &auo_b133xtn01,
	पूर्ण, अणु
		.compatible = "auo,g070vvn01",
		.data = &auo_g070vvn01,
	पूर्ण, अणु
		.compatible = "auo,g101evn010",
		.data = &auo_g101evn010,
	पूर्ण, अणु
		.compatible = "auo,g104sn02",
		.data = &auo_g104sn02,
	पूर्ण, अणु
		.compatible = "auo,g121ean01",
		.data = &auo_g121ean01,
	पूर्ण, अणु
		.compatible = "auo,g133han01",
		.data = &auo_g133han01,
	पूर्ण, अणु
		.compatible = "auo,g156xtn01",
		.data = &auo_g156xtn01,
	पूर्ण, अणु
		.compatible = "auo,g185han01",
		.data = &auo_g185han01,
	पूर्ण, अणु
		.compatible = "auo,g190ean01",
		.data = &auo_g190ean01,
	पूर्ण, अणु
		.compatible = "auo,p320hvn03",
		.data = &auo_p320hvn03,
	पूर्ण, अणु
		.compatible = "auo,t215hvn01",
		.data = &auo_t215hvn01,
	पूर्ण, अणु
		.compatible = "avic,tm070ddh03",
		.data = &avic_पंचांग070ddh03,
	पूर्ण, अणु
		.compatible = "bananapi,s070wv20-ct16",
		.data = &bananapi_s070wv20_ct16,
	पूर्ण, अणु
		.compatible = "boe,hv070wsa-100",
		.data = &boe_hv070wsa
	पूर्ण, अणु
		.compatible = "boe,nv101wxmn51",
		.data = &boe_nv101wxmn51,
	पूर्ण, अणु
		.compatible = "boe,nv110wtm-n61",
		.data = &boe_nv110wपंचांग_n61,
	पूर्ण, अणु
		.compatible = "boe,nv133fhm-n61",
		.data = &boe_nv133fhm_n61,
	पूर्ण, अणु
		.compatible = "boe,nv133fhm-n62",
		.data = &boe_nv133fhm_n61,
	पूर्ण, अणु
		.compatible = "boe,nv140fhmn49",
		.data = &boe_nv140fhmn49,
	पूर्ण, अणु
		.compatible = "cdtech,s043wq26h-ct7",
		.data = &cdtech_s043wq26h_ct7,
	पूर्ण, अणु
		.compatible = "cdtech,s070pws19hp-fc21",
		.data = &cdtech_s070pws19hp_fc21,
	पूर्ण, अणु
		.compatible = "cdtech,s070swv29hg-dc44",
		.data = &cdtech_s070swv29hg_dc44,
	पूर्ण, अणु
		.compatible = "cdtech,s070wv95-ct16",
		.data = &cdtech_s070wv95_ct16,
	पूर्ण, अणु
		.compatible = "chefree,ch101olhlwh-002",
		.data = &cheमुक्त_ch101olhlwh_002,
	पूर्ण, अणु
		.compatible = "chunghwa,claa070wp03xg",
		.data = &chunghwa_claa070wp03xg,
	पूर्ण, अणु
		.compatible = "chunghwa,claa101wa01a",
		.data = &chunghwa_claa101wa01a
	पूर्ण, अणु
		.compatible = "chunghwa,claa101wb01",
		.data = &chunghwa_claa101wb01
	पूर्ण, अणु
		.compatible = "dataimage,scf0700c48ggu18",
		.data = &dataimage_scf0700c48ggu18,
	पूर्ण, अणु
		.compatible = "dlc,dlc0700yzg-1",
		.data = &dlc_dlc0700yzg_1,
	पूर्ण, अणु
		.compatible = "dlc,dlc1010gig",
		.data = &dlc_dlc1010gig,
	पूर्ण, अणु
		.compatible = "edt,et035012dm6",
		.data = &edt_et035012dm6,
	पूर्ण, अणु
		.compatible = "edt,etm043080dh6gp",
		.data = &edt_eपंचांग043080dh6gp,
	पूर्ण, अणु
		.compatible = "edt,etm0430g0dh6",
		.data = &edt_eपंचांग0430g0dh6,
	पूर्ण, अणु
		.compatible = "edt,et057090dhu",
		.data = &edt_et057090dhu,
	पूर्ण, अणु
		.compatible = "edt,et070080dh6",
		.data = &edt_eपंचांग0700g0dh6,
	पूर्ण, अणु
		.compatible = "edt,etm0700g0dh6",
		.data = &edt_eपंचांग0700g0dh6,
	पूर्ण, अणु
		.compatible = "edt,etm0700g0bdh6",
		.data = &edt_eपंचांग0700g0bdh6,
	पूर्ण, अणु
		.compatible = "edt,etm0700g0edh6",
		.data = &edt_eपंचांग0700g0bdh6,
	पूर्ण, अणु
		.compatible = "evervision,vgg804821",
		.data = &evervision_vgg804821,
	पूर्ण, अणु
		.compatible = "foxlink,fl500wvr00-a0t",
		.data = &foxlink_fl500wvr00_a0t,
	पूर्ण, अणु
		.compatible = "frida,frd350h54004",
		.data = &frida_frd350h54004,
	पूर्ण, अणु
		.compatible = "friendlyarm,hd702e",
		.data = &मित्रlyarm_hd702e,
	पूर्ण, अणु
		.compatible = "giantplus,gpg482739qs5",
		.data = &giantplus_gpg482739qs5
	पूर्ण, अणु
		.compatible = "giantplus,gpm940b0",
		.data = &giantplus_gpm940b0,
	पूर्ण, अणु
		.compatible = "hannstar,hsd070pww1",
		.data = &hannstar_hsd070pww1,
	पूर्ण, अणु
		.compatible = "hannstar,hsd100pxn1",
		.data = &hannstar_hsd100pxn1,
	पूर्ण, अणु
		.compatible = "hit,tx23d38vm0caa",
		.data = &hitachi_tx23d38vm0caa
	पूर्ण, अणु
		.compatible = "innolux,at043tn24",
		.data = &innolux_at043tn24,
	पूर्ण, अणु
		.compatible = "innolux,at070tn92",
		.data = &innolux_at070tn92,
	पूर्ण, अणु
		.compatible = "innolux,g070y2-l01",
		.data = &innolux_g070y2_l01,
	पूर्ण, अणु
		.compatible = "innolux,g101ice-l01",
		.data = &innolux_g101ice_l01
	पूर्ण, अणु
		.compatible = "innolux,g121i1-l01",
		.data = &innolux_g121i1_l01
	पूर्ण, अणु
		.compatible = "innolux,g121x1-l03",
		.data = &innolux_g121x1_l03,
	पूर्ण, अणु
		.compatible = "innolux,n116bca-ea1",
		.data = &innolux_n116bca_ea1,
	पूर्ण, अणु
		.compatible = "innolux,n116bge",
		.data = &innolux_n116bge,
	पूर्ण, अणु
		.compatible = "innolux,n125hce-gn1",
		.data = &innolux_n125hce_gn1,
	पूर्ण, अणु
		.compatible = "innolux,n156bge-l21",
		.data = &innolux_n156bge_l21,
	पूर्ण, अणु
		.compatible = "innolux,p120zdg-bf1",
		.data = &innolux_p120zdg_bf1,
	पूर्ण, अणु
		.compatible = "innolux,zj070na-01p",
		.data = &innolux_zj070na_01p,
	पूर्ण, अणु
		.compatible = "ivo,m133nwf4-r0",
		.data = &ivo_m133nwf4_r0,
	पूर्ण, अणु
		.compatible = "kingdisplay,kd116n21-30nv-a010",
		.data = &kingdisplay_kd116n21_30nv_a010,
	पूर्ण, अणु
		.compatible = "koe,tx14d24vm1bpa",
		.data = &koe_tx14d24vm1bpa,
	पूर्ण, अणु
		.compatible = "koe,tx26d202vm0bwa",
		.data = &koe_tx26d202vm0bwa,
	पूर्ण, अणु
		.compatible = "koe,tx31d200vm0baa",
		.data = &koe_tx31d200vm0baa,
	पूर्ण, अणु
		.compatible = "kyo,tcg121xglp",
		.data = &kyo_tcg121xglp,
	पूर्ण, अणु
		.compatible = "lemaker,bl035-rgb-002",
		.data = &lemaker_bl035_rgb_002,
	पूर्ण, अणु
		.compatible = "lg,lb070wv8",
		.data = &lg_lb070wv8,
	पूर्ण, अणु
		.compatible = "lg,lp079qx1-sp0v",
		.data = &lg_lp079qx1_sp0v,
	पूर्ण, अणु
		.compatible = "lg,lp097qx1-spa1",
		.data = &lg_lp097qx1_spa1,
	पूर्ण, अणु
		.compatible = "lg,lp120up1",
		.data = &lg_lp120up1,
	पूर्ण, अणु
		.compatible = "lg,lp129qe",
		.data = &lg_lp129qe,
	पूर्ण, अणु
		.compatible = "logicpd,type28",
		.data = &logicpd_type_28,
	पूर्ण, अणु
		.compatible = "logictechno,lt161010-2nhc",
		.data = &logictechno_lt161010_2nh,
	पूर्ण, अणु
		.compatible = "logictechno,lt161010-2nhr",
		.data = &logictechno_lt161010_2nh,
	पूर्ण, अणु
		.compatible = "logictechno,lt170410-2whc",
		.data = &logictechno_lt170410_2whc,
	पूर्ण, अणु
		.compatible = "mitsubishi,aa070mc01-ca1",
		.data = &mitsubishi_aa070mc01,
	पूर्ण, अणु
		.compatible = "nec,nl12880bc20-05",
		.data = &nec_nl12880bc20_05,
	पूर्ण, अणु
		.compatible = "nec,nl4827hc19-05b",
		.data = &nec_nl4827hc19_05b,
	पूर्ण, अणु
		.compatible = "netron-dy,e231732",
		.data = &netron_dy_e231732,
	पूर्ण, अणु
		.compatible = "neweast,wjfh116008a",
		.data = &neweast_wjfh116008a,
	पूर्ण, अणु
		.compatible = "newhaven,nhd-4.3-480272ef-atxl",
		.data = &newhaven_nhd_43_480272ef_atxl,
	पूर्ण, अणु
		.compatible = "nlt,nl192108ac18-02d",
		.data = &nlt_nl192108ac18_02d,
	पूर्ण, अणु
		.compatible = "nvd,9128",
		.data = &nvd_9128,
	पूर्ण, अणु
		.compatible = "okaya,rs800480t-7x0gp",
		.data = &okaya_rs800480t_7x0gp,
	पूर्ण, अणु
		.compatible = "olimex,lcd-olinuxino-43-ts",
		.data = &olimex_lcd_olinuxino_43ts,
	पूर्ण, अणु
		.compatible = "ontat,yx700wv03",
		.data = &ontat_yx700wv03,
	पूर्ण, अणु
		.compatible = "ortustech,com37h3m05dtc",
		.data = &ortustech_com37h3m,
	पूर्ण, अणु
		.compatible = "ortustech,com37h3m99dtc",
		.data = &ortustech_com37h3m,
	पूर्ण, अणु
		.compatible = "ortustech,com43h4m85ulc",
		.data = &ortustech_com43h4m85ulc,
	पूर्ण, अणु
		.compatible = "osddisplays,osd070t1718-19ts",
		.data = &osddisplays_osd070t1718_19ts,
	पूर्ण, अणु
		.compatible = "pda,91-00156-a0",
		.data = &pda_91_00156_a0,
	पूर्ण, अणु
		.compatible = "powertip,ph800480t013-idf02",
		.data = &घातertip_ph800480t013_idf02,
	पूर्ण, अणु
		.compatible = "qiaodian,qd43003c0-40",
		.data = &qd43003c0_40,
	पूर्ण, अणु
		.compatible = "rocktech,rk070er9427",
		.data = &rocktech_rk070er9427,
	पूर्ण, अणु
		.compatible = "rocktech,rk101ii01d-ct",
		.data = &rocktech_rk101ii01d_ct,
	पूर्ण, अणु
		.compatible = "samsung,lsn122dl01-c01",
		.data = &samsung_lsn122dl01_c01,
	पूर्ण, अणु
		.compatible = "samsung,ltn101nt05",
		.data = &samsung_ltn101nt05,
	पूर्ण, अणु
		.compatible = "samsung,ltn140at29-301",
		.data = &samsung_ltn140at29_301,
	पूर्ण, अणु
		.compatible = "satoz,sat050at40h12r2",
		.data = &satoz_sat050at40h12r2,
	पूर्ण, अणु
		.compatible = "sharp,ld-d5116z01b",
		.data = &sharp_ld_d5116z01b,
	पूर्ण, अणु
		.compatible = "sharp,lq035q7db03",
		.data = &sharp_lq035q7db03,
	पूर्ण, अणु
		.compatible = "sharp,lq070y3dg3b",
		.data = &sharp_lq070y3dg3b,
	पूर्ण, अणु
		.compatible = "sharp,lq101k1ly04",
		.data = &sharp_lq101k1ly04,
	पूर्ण, अणु
		.compatible = "sharp,lq123p1jx31",
		.data = &sharp_lq123p1jx31,
	पूर्ण, अणु
		.compatible = "sharp,ls020b1dd01d",
		.data = &sharp_ls020b1dd01d,
	पूर्ण, अणु
		.compatible = "shelly,sca07010-bfn-lnn",
		.data = &shelly_sca07010_bfn_lnn,
	पूर्ण, अणु
		.compatible = "starry,kr070pe2t",
		.data = &starry_kr070pe2t,
	पूर्ण, अणु
		.compatible = "starry,kr122ea0sra",
		.data = &starry_kr122ea0sra,
	पूर्ण, अणु
		.compatible = "tfc,s9700rtwv43tr-01b",
		.data = &tfc_s9700rtwv43tr_01b,
	पूर्ण, अणु
		.compatible = "tianma,tm070jdhg30",
		.data = &tianma_पंचांग070jdhg30,
	पूर्ण, अणु
		.compatible = "tianma,tm070jvhg33",
		.data = &tianma_पंचांग070jvhg33,
	पूर्ण, अणु
		.compatible = "tianma,tm070rvhg71",
		.data = &tianma_पंचांग070rvhg71,
	पूर्ण, अणु
		.compatible = "ti,nspire-cx-lcd-panel",
		.data = &ti_nspire_cx_lcd_panel,
	पूर्ण, अणु
		.compatible = "ti,nspire-classic-lcd-panel",
		.data = &ti_nspire_classic_lcd_panel,
	पूर्ण, अणु
		.compatible = "toshiba,lt089ac29000",
		.data = &toshiba_lt089ac29000,
	पूर्ण, अणु
		.compatible = "tpk,f07a-0102",
		.data = &tpk_f07a_0102,
	पूर्ण, अणु
		.compatible = "tpk,f10a-0102",
		.data = &tpk_f10a_0102,
	पूर्ण, अणु
		.compatible = "urt,umsh-8596md-t",
		.data = &urt_umsh_8596md_parallel,
	पूर्ण, अणु
		.compatible = "urt,umsh-8596md-1t",
		.data = &urt_umsh_8596md_parallel,
	पूर्ण, अणु
		.compatible = "urt,umsh-8596md-7t",
		.data = &urt_umsh_8596md_parallel,
	पूर्ण, अणु
		.compatible = "urt,umsh-8596md-11t",
		.data = &urt_umsh_8596md_lvds,
	पूर्ण, अणु
		.compatible = "urt,umsh-8596md-19t",
		.data = &urt_umsh_8596md_lvds,
	पूर्ण, अणु
		.compatible = "urt,umsh-8596md-20t",
		.data = &urt_umsh_8596md_parallel,
	पूर्ण, अणु
		.compatible = "vxt,vl050-8048nt-c01",
		.data = &vl050_8048nt_c01,
	पूर्ण, अणु
		.compatible = "winstar,wf35ltiacd",
		.data = &winstar_wf35ltiacd,
	पूर्ण, अणु
		.compatible = "yes-optoelectronics,ytc700tlag-05-201c",
		.data = &yes_optoelectronics_ytc700tlag_05_201c,
	पूर्ण, अणु
		/* Must be the last entry */
		.compatible = "panel-dpi",
		.data = &panel_dpi,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, platक्रमm_of_match);

अटल पूर्णांक panel_simple_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *id;

	id = of_match_node(platक्रमm_of_match, pdev->dev.of_node);
	अगर (!id)
		वापस -ENODEV;

	वापस panel_simple_probe(&pdev->dev, id->data);
पूर्ण

अटल पूर्णांक panel_simple_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस panel_simple_हटाओ(&pdev->dev);
पूर्ण

अटल व्योम panel_simple_platक्रमm_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	panel_simple_shutकरोwn(&pdev->dev);
पूर्ण

अटल काष्ठा platक्रमm_driver panel_simple_platक्रमm_driver = अणु
	.driver = अणु
		.name = "panel-simple",
		.of_match_table = platक्रमm_of_match,
	पूर्ण,
	.probe = panel_simple_platक्रमm_probe,
	.हटाओ = panel_simple_platक्रमm_हटाओ,
	.shutकरोwn = panel_simple_platक्रमm_shutकरोwn,
पूर्ण;

काष्ठा panel_desc_dsi अणु
	काष्ठा panel_desc desc;

	अचिन्हित दीर्घ flags;
	क्रमागत mipi_dsi_pixel_क्रमmat क्रमmat;
	अचिन्हित पूर्णांक lanes;
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode auo_b080uan01_mode = अणु
	.घड़ी = 154500,
	.hdisplay = 1200,
	.hsync_start = 1200 + 62,
	.hsync_end = 1200 + 62 + 4,
	.htotal = 1200 + 62 + 4 + 62,
	.vdisplay = 1920,
	.vsync_start = 1920 + 9,
	.vsync_end = 1920 + 9 + 2,
	.vtotal = 1920 + 9 + 2 + 8,
पूर्ण;

अटल स्थिर काष्ठा panel_desc_dsi auo_b080uan01 = अणु
	.desc = अणु
		.modes = &auo_b080uan01_mode,
		.num_modes = 1,
		.bpc = 8,
		.size = अणु
			.width = 108,
			.height = 272,
		पूर्ण,
		.connector_type = DRM_MODE_CONNECTOR_DSI,
	पूर्ण,
	.flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_CLOCK_NON_CONTINUOUS,
	.क्रमmat = MIPI_DSI_FMT_RGB888,
	.lanes = 4,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode boe_tv080wum_nl0_mode = अणु
	.घड़ी = 160000,
	.hdisplay = 1200,
	.hsync_start = 1200 + 120,
	.hsync_end = 1200 + 120 + 20,
	.htotal = 1200 + 120 + 20 + 21,
	.vdisplay = 1920,
	.vsync_start = 1920 + 21,
	.vsync_end = 1920 + 21 + 3,
	.vtotal = 1920 + 21 + 3 + 18,
	.flags = DRM_MODE_FLAG_NVSYNC | DRM_MODE_FLAG_NHSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc_dsi boe_tv080wum_nl0 = अणु
	.desc = अणु
		.modes = &boe_tv080wum_nl0_mode,
		.num_modes = 1,
		.size = अणु
			.width = 107,
			.height = 172,
		पूर्ण,
		.connector_type = DRM_MODE_CONNECTOR_DSI,
	पूर्ण,
	.flags = MIPI_DSI_MODE_VIDEO |
		 MIPI_DSI_MODE_VIDEO_BURST |
		 MIPI_DSI_MODE_VIDEO_SYNC_PULSE,
	.क्रमmat = MIPI_DSI_FMT_RGB888,
	.lanes = 4,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode lg_ld070wx3_sl01_mode = अणु
	.घड़ी = 71000,
	.hdisplay = 800,
	.hsync_start = 800 + 32,
	.hsync_end = 800 + 32 + 1,
	.htotal = 800 + 32 + 1 + 57,
	.vdisplay = 1280,
	.vsync_start = 1280 + 28,
	.vsync_end = 1280 + 28 + 1,
	.vtotal = 1280 + 28 + 1 + 14,
पूर्ण;

अटल स्थिर काष्ठा panel_desc_dsi lg_ld070wx3_sl01 = अणु
	.desc = अणु
		.modes = &lg_ld070wx3_sl01_mode,
		.num_modes = 1,
		.bpc = 8,
		.size = अणु
			.width = 94,
			.height = 151,
		पूर्ण,
		.connector_type = DRM_MODE_CONNECTOR_DSI,
	पूर्ण,
	.flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_CLOCK_NON_CONTINUOUS,
	.क्रमmat = MIPI_DSI_FMT_RGB888,
	.lanes = 4,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode lg_lh500wx1_sd03_mode = अणु
	.घड़ी = 67000,
	.hdisplay = 720,
	.hsync_start = 720 + 12,
	.hsync_end = 720 + 12 + 4,
	.htotal = 720 + 12 + 4 + 112,
	.vdisplay = 1280,
	.vsync_start = 1280 + 8,
	.vsync_end = 1280 + 8 + 4,
	.vtotal = 1280 + 8 + 4 + 12,
पूर्ण;

अटल स्थिर काष्ठा panel_desc_dsi lg_lh500wx1_sd03 = अणु
	.desc = अणु
		.modes = &lg_lh500wx1_sd03_mode,
		.num_modes = 1,
		.bpc = 8,
		.size = अणु
			.width = 62,
			.height = 110,
		पूर्ण,
		.connector_type = DRM_MODE_CONNECTOR_DSI,
	पूर्ण,
	.flags = MIPI_DSI_MODE_VIDEO,
	.क्रमmat = MIPI_DSI_FMT_RGB888,
	.lanes = 4,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode panasonic_vvx10f004b00_mode = अणु
	.घड़ी = 157200,
	.hdisplay = 1920,
	.hsync_start = 1920 + 154,
	.hsync_end = 1920 + 154 + 16,
	.htotal = 1920 + 154 + 16 + 32,
	.vdisplay = 1200,
	.vsync_start = 1200 + 17,
	.vsync_end = 1200 + 17 + 2,
	.vtotal = 1200 + 17 + 2 + 16,
पूर्ण;

अटल स्थिर काष्ठा panel_desc_dsi panasonic_vvx10f004b00 = अणु
	.desc = अणु
		.modes = &panasonic_vvx10f004b00_mode,
		.num_modes = 1,
		.bpc = 8,
		.size = अणु
			.width = 217,
			.height = 136,
		पूर्ण,
		.connector_type = DRM_MODE_CONNECTOR_DSI,
	पूर्ण,
	.flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_SYNC_PULSE |
		 MIPI_DSI_CLOCK_NON_CONTINUOUS,
	.क्रमmat = MIPI_DSI_FMT_RGB888,
	.lanes = 4,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode lg_acx467akm_7_mode = अणु
	.घड़ी = 150000,
	.hdisplay = 1080,
	.hsync_start = 1080 + 2,
	.hsync_end = 1080 + 2 + 2,
	.htotal = 1080 + 2 + 2 + 2,
	.vdisplay = 1920,
	.vsync_start = 1920 + 2,
	.vsync_end = 1920 + 2 + 2,
	.vtotal = 1920 + 2 + 2 + 2,
पूर्ण;

अटल स्थिर काष्ठा panel_desc_dsi lg_acx467akm_7 = अणु
	.desc = अणु
		.modes = &lg_acx467akm_7_mode,
		.num_modes = 1,
		.bpc = 8,
		.size = अणु
			.width = 62,
			.height = 110,
		पूर्ण,
		.connector_type = DRM_MODE_CONNECTOR_DSI,
	पूर्ण,
	.flags = 0,
	.क्रमmat = MIPI_DSI_FMT_RGB888,
	.lanes = 4,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode osd101t2045_53ts_mode = अणु
	.घड़ी = 154500,
	.hdisplay = 1920,
	.hsync_start = 1920 + 112,
	.hsync_end = 1920 + 112 + 16,
	.htotal = 1920 + 112 + 16 + 32,
	.vdisplay = 1200,
	.vsync_start = 1200 + 16,
	.vsync_end = 1200 + 16 + 2,
	.vtotal = 1200 + 16 + 2 + 16,
	.flags = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC,
पूर्ण;

अटल स्थिर काष्ठा panel_desc_dsi osd101t2045_53ts = अणु
	.desc = अणु
		.modes = &osd101t2045_53ts_mode,
		.num_modes = 1,
		.bpc = 8,
		.size = अणु
			.width = 217,
			.height = 136,
		पूर्ण,
		.connector_type = DRM_MODE_CONNECTOR_DSI,
	पूर्ण,
	.flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
		 MIPI_DSI_MODE_VIDEO_SYNC_PULSE |
		 MIPI_DSI_MODE_EOT_PACKET,
	.क्रमmat = MIPI_DSI_FMT_RGB888,
	.lanes = 4,
पूर्ण;

अटल स्थिर काष्ठा of_device_id dsi_of_match[] = अणु
	अणु
		.compatible = "auo,b080uan01",
		.data = &auo_b080uan01
	पूर्ण, अणु
		.compatible = "boe,tv080wum-nl0",
		.data = &boe_tv080wum_nl0
	पूर्ण, अणु
		.compatible = "lg,ld070wx3-sl01",
		.data = &lg_ld070wx3_sl01
	पूर्ण, अणु
		.compatible = "lg,lh500wx1-sd03",
		.data = &lg_lh500wx1_sd03
	पूर्ण, अणु
		.compatible = "panasonic,vvx10f004b00",
		.data = &panasonic_vvx10f004b00
	पूर्ण, अणु
		.compatible = "lg,acx467akm-7",
		.data = &lg_acx467akm_7
	पूर्ण, अणु
		.compatible = "osddisplays,osd101t2045-53ts",
		.data = &osd101t2045_53ts
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dsi_of_match);

अटल पूर्णांक panel_simple_dsi_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	स्थिर काष्ठा panel_desc_dsi *desc;
	स्थिर काष्ठा of_device_id *id;
	पूर्णांक err;

	id = of_match_node(dsi_of_match, dsi->dev.of_node);
	अगर (!id)
		वापस -ENODEV;

	desc = id->data;

	err = panel_simple_probe(&dsi->dev, &desc->desc);
	अगर (err < 0)
		वापस err;

	dsi->mode_flags = desc->flags;
	dsi->क्रमmat = desc->क्रमmat;
	dsi->lanes = desc->lanes;

	err = mipi_dsi_attach(dsi);
	अगर (err) अणु
		काष्ठा panel_simple *panel = mipi_dsi_get_drvdata(dsi);

		drm_panel_हटाओ(&panel->base);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक panel_simple_dsi_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	पूर्णांक err;

	err = mipi_dsi_detach(dsi);
	अगर (err < 0)
		dev_err(&dsi->dev, "failed to detach from DSI host: %d\n", err);

	वापस panel_simple_हटाओ(&dsi->dev);
पूर्ण

अटल व्योम panel_simple_dsi_shutकरोwn(काष्ठा mipi_dsi_device *dsi)
अणु
	panel_simple_shutकरोwn(&dsi->dev);
पूर्ण

अटल काष्ठा mipi_dsi_driver panel_simple_dsi_driver = अणु
	.driver = अणु
		.name = "panel-simple-dsi",
		.of_match_table = dsi_of_match,
	पूर्ण,
	.probe = panel_simple_dsi_probe,
	.हटाओ = panel_simple_dsi_हटाओ,
	.shutकरोwn = panel_simple_dsi_shutकरोwn,
पूर्ण;

अटल पूर्णांक __init panel_simple_init(व्योम)
अणु
	पूर्णांक err;

	err = platक्रमm_driver_रेजिस्टर(&panel_simple_platक्रमm_driver);
	अगर (err < 0)
		वापस err;

	अगर (IS_ENABLED(CONFIG_DRM_MIPI_DSI)) अणु
		err = mipi_dsi_driver_रेजिस्टर(&panel_simple_dsi_driver);
		अगर (err < 0) अणु
			platक्रमm_driver_unरेजिस्टर(&panel_simple_platक्रमm_driver);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
module_init(panel_simple_init);

अटल व्योम __निकास panel_simple_निकास(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_DRM_MIPI_DSI))
		mipi_dsi_driver_unरेजिस्टर(&panel_simple_dsi_driver);

	platक्रमm_driver_unरेजिस्टर(&panel_simple_platक्रमm_driver);
पूर्ण
module_निकास(panel_simple_निकास);

MODULE_AUTHOR("Thierry Reding <treding@nvidia.com>");
MODULE_DESCRIPTION("DRM Driver for Simple Panels");
MODULE_LICENSE("GPL and additional rights");
