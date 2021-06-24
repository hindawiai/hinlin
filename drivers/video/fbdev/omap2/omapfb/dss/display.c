<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/video/omap2/dss/display.c
 *
 * Copyright (C) 2009 Nokia Corporation
 * Author: Tomi Valkeinen <tomi.valkeinen@nokia.com>
 *
 * Some code and ideas taken from drivers/video/omap/ driver
 * by Imre Deak.
 */

#घोषणा DSS_SUBSYS_NAME "DISPLAY"

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>

#समावेश <video/omapfb_dss.h>
#समावेश "dss.h"
#समावेश "dss_features.h"

व्योम omapdss_शेष_get_resolution(काष्ठा omap_dss_device *dssdev,
			u16 *xres, u16 *yres)
अणु
	*xres = dssdev->panel.timings.x_res;
	*yres = dssdev->panel.timings.y_res;
पूर्ण
EXPORT_SYMBOL(omapdss_शेष_get_resolution);

पूर्णांक omapdss_शेष_get_recommended_bpp(काष्ठा omap_dss_device *dssdev)
अणु
	चयन (dssdev->type) अणु
	हाल OMAP_DISPLAY_TYPE_DPI:
		अगर (dssdev->phy.dpi.data_lines == 24)
			वापस 24;
		अन्यथा
			वापस 16;

	हाल OMAP_DISPLAY_TYPE_DBI:
		अगर (dssdev->ctrl.pixel_size == 24)
			वापस 24;
		अन्यथा
			वापस 16;
	हाल OMAP_DISPLAY_TYPE_DSI:
		अगर (dsi_get_pixel_size(dssdev->panel.dsi_pix_fmt) > 16)
			वापस 24;
		अन्यथा
			वापस 16;
	हाल OMAP_DISPLAY_TYPE_VENC:
	हाल OMAP_DISPLAY_TYPE_SDI:
	हाल OMAP_DISPLAY_TYPE_HDMI:
	हाल OMAP_DISPLAY_TYPE_DVI:
		वापस 24;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(omapdss_शेष_get_recommended_bpp);

व्योम omapdss_शेष_get_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	*timings = dssdev->panel.timings;
पूर्ण
EXPORT_SYMBOL(omapdss_शेष_get_timings);

पूर्णांक dss_suspend_all_devices(व्योम)
अणु
	काष्ठा omap_dss_device *dssdev = शून्य;

	क्रम_each_dss_dev(dssdev) अणु
		अगर (!dssdev->driver)
			जारी;

		अगर (dssdev->state == OMAP_DSS_DISPLAY_ACTIVE) अणु
			dssdev->driver->disable(dssdev);
			dssdev->activate_after_resume = true;
		पूर्ण अन्यथा अणु
			dssdev->activate_after_resume = false;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dss_resume_all_devices(व्योम)
अणु
	काष्ठा omap_dss_device *dssdev = शून्य;

	क्रम_each_dss_dev(dssdev) अणु
		अगर (!dssdev->driver)
			जारी;

		अगर (dssdev->activate_after_resume) अणु
			dssdev->driver->enable(dssdev);
			dssdev->activate_after_resume = false;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम dss_disable_all_devices(व्योम)
अणु
	काष्ठा omap_dss_device *dssdev = शून्य;

	क्रम_each_dss_dev(dssdev) अणु
		अगर (!dssdev->driver)
			जारी;

		अगर (dssdev->state == OMAP_DSS_DISPLAY_ACTIVE)
			dssdev->driver->disable(dssdev);
	पूर्ण
पूर्ण

अटल LIST_HEAD(panel_list);
अटल DEFINE_MUTEX(panel_list_mutex);
अटल पूर्णांक disp_num_counter;

पूर्णांक omapdss_रेजिस्टर_display(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा omap_dss_driver *drv = dssdev->driver;
	पूर्णांक id;

	/*
	 * Note: this presumes all the displays are either using DT or non-DT,
	 * which normally should be the हाल. This also presumes that all
	 * displays either have an DT alias, or none has.
	 */

	अगर (dssdev->dev->of_node) अणु
		id = of_alias_get_id(dssdev->dev->of_node, "display");

		अगर (id < 0)
			id = disp_num_counter++;
	पूर्ण अन्यथा अणु
		id = disp_num_counter++;
	पूर्ण

	snम_लिखो(dssdev->alias, माप(dssdev->alias), "display%d", id);

	/* Use 'label' property क्रम name, अगर it exists */
	अगर (dssdev->dev->of_node)
		of_property_पढ़ो_string(dssdev->dev->of_node, "label",
			&dssdev->name);

	अगर (dssdev->name == शून्य)
		dssdev->name = dssdev->alias;

	अगर (drv && drv->get_resolution == शून्य)
		drv->get_resolution = omapdss_शेष_get_resolution;
	अगर (drv && drv->get_recommended_bpp == शून्य)
		drv->get_recommended_bpp = omapdss_शेष_get_recommended_bpp;
	अगर (drv && drv->get_timings == शून्य)
		drv->get_timings = omapdss_शेष_get_timings;

	mutex_lock(&panel_list_mutex);
	list_add_tail(&dssdev->panel_list, &panel_list);
	mutex_unlock(&panel_list_mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(omapdss_रेजिस्टर_display);

व्योम omapdss_unरेजिस्टर_display(काष्ठा omap_dss_device *dssdev)
अणु
	mutex_lock(&panel_list_mutex);
	list_del(&dssdev->panel_list);
	mutex_unlock(&panel_list_mutex);
पूर्ण
EXPORT_SYMBOL(omapdss_unरेजिस्टर_display);

काष्ठा omap_dss_device *omap_dss_get_device(काष्ठा omap_dss_device *dssdev)
अणु
	अगर (!try_module_get(dssdev->owner))
		वापस शून्य;

	अगर (get_device(dssdev->dev) == शून्य) अणु
		module_put(dssdev->owner);
		वापस शून्य;
	पूर्ण

	वापस dssdev;
पूर्ण
EXPORT_SYMBOL(omap_dss_get_device);

व्योम omap_dss_put_device(काष्ठा omap_dss_device *dssdev)
अणु
	put_device(dssdev->dev);
	module_put(dssdev->owner);
पूर्ण
EXPORT_SYMBOL(omap_dss_put_device);

/*
 * ref count of the found device is incremented.
 * ref count of from-device is decremented.
 */
काष्ठा omap_dss_device *omap_dss_get_next_device(काष्ठा omap_dss_device *from)
अणु
	काष्ठा list_head *l;
	काष्ठा omap_dss_device *dssdev;

	mutex_lock(&panel_list_mutex);

	अगर (list_empty(&panel_list)) अणु
		dssdev = शून्य;
		जाओ out;
	पूर्ण

	अगर (from == शून्य) अणु
		dssdev = list_first_entry(&panel_list, काष्ठा omap_dss_device,
				panel_list);
		omap_dss_get_device(dssdev);
		जाओ out;
	पूर्ण

	omap_dss_put_device(from);

	list_क्रम_each(l, &panel_list) अणु
		dssdev = list_entry(l, काष्ठा omap_dss_device, panel_list);
		अगर (dssdev == from) अणु
			अगर (list_is_last(l, &panel_list)) अणु
				dssdev = शून्य;
				जाओ out;
			पूर्ण

			dssdev = list_entry(l->next, काष्ठा omap_dss_device,
					panel_list);
			omap_dss_get_device(dssdev);
			जाओ out;
		पूर्ण
	पूर्ण

	WARN(1, "'from' dssdev not found\n");

	dssdev = शून्य;
out:
	mutex_unlock(&panel_list_mutex);
	वापस dssdev;
पूर्ण
EXPORT_SYMBOL(omap_dss_get_next_device);

काष्ठा omap_dss_device *omap_dss_find_device(व्योम *data,
		पूर्णांक (*match)(काष्ठा omap_dss_device *dssdev, व्योम *data))
अणु
	काष्ठा omap_dss_device *dssdev = शून्य;

	जबतक ((dssdev = omap_dss_get_next_device(dssdev)) != शून्य) अणु
		अगर (match(dssdev, data))
			वापस dssdev;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(omap_dss_find_device);

व्योम videomode_to_omap_video_timings(स्थिर काष्ठा videomode *vm,
		काष्ठा omap_video_timings *ovt)
अणु
	स_रखो(ovt, 0, माप(*ovt));

	ovt->pixelघड़ी = vm->pixelघड़ी;
	ovt->x_res = vm->hactive;
	ovt->hbp = vm->hback_porch;
	ovt->hfp = vm->hfront_porch;
	ovt->hsw = vm->hsync_len;
	ovt->y_res = vm->vactive;
	ovt->vbp = vm->vback_porch;
	ovt->vfp = vm->vfront_porch;
	ovt->vsw = vm->vsync_len;

	ovt->vsync_level = vm->flags & DISPLAY_FLAGS_VSYNC_HIGH ?
		OMAPDSS_SIG_ACTIVE_HIGH :
		OMAPDSS_SIG_ACTIVE_LOW;
	ovt->hsync_level = vm->flags & DISPLAY_FLAGS_HSYNC_HIGH ?
		OMAPDSS_SIG_ACTIVE_HIGH :
		OMAPDSS_SIG_ACTIVE_LOW;
	ovt->de_level = vm->flags & DISPLAY_FLAGS_DE_HIGH ?
		OMAPDSS_SIG_ACTIVE_HIGH :
		OMAPDSS_SIG_ACTIVE_LOW;
	ovt->data_pclk_edge = vm->flags & DISPLAY_FLAGS_PIXDATA_POSEDGE ?
		OMAPDSS_DRIVE_SIG_RISING_EDGE :
		OMAPDSS_DRIVE_SIG_FALLING_EDGE;

	ovt->sync_pclk_edge = ovt->data_pclk_edge;
पूर्ण
EXPORT_SYMBOL(videomode_to_omap_video_timings);

व्योम omap_video_timings_to_videomode(स्थिर काष्ठा omap_video_timings *ovt,
		काष्ठा videomode *vm)
अणु
	स_रखो(vm, 0, माप(*vm));

	vm->pixelघड़ी = ovt->pixelघड़ी;

	vm->hactive = ovt->x_res;
	vm->hback_porch = ovt->hbp;
	vm->hfront_porch = ovt->hfp;
	vm->hsync_len = ovt->hsw;
	vm->vactive = ovt->y_res;
	vm->vback_porch = ovt->vbp;
	vm->vfront_porch = ovt->vfp;
	vm->vsync_len = ovt->vsw;

	अगर (ovt->hsync_level == OMAPDSS_SIG_ACTIVE_HIGH)
		vm->flags |= DISPLAY_FLAGS_HSYNC_HIGH;
	अन्यथा
		vm->flags |= DISPLAY_FLAGS_HSYNC_LOW;

	अगर (ovt->vsync_level == OMAPDSS_SIG_ACTIVE_HIGH)
		vm->flags |= DISPLAY_FLAGS_VSYNC_HIGH;
	अन्यथा
		vm->flags |= DISPLAY_FLAGS_VSYNC_LOW;

	अगर (ovt->de_level == OMAPDSS_SIG_ACTIVE_HIGH)
		vm->flags |= DISPLAY_FLAGS_DE_HIGH;
	अन्यथा
		vm->flags |= DISPLAY_FLAGS_DE_LOW;

	अगर (ovt->data_pclk_edge == OMAPDSS_DRIVE_SIG_RISING_EDGE)
		vm->flags |= DISPLAY_FLAGS_PIXDATA_POSEDGE;
	अन्यथा
		vm->flags |= DISPLAY_FLAGS_PIXDATA_NEGEDGE;
पूर्ण
EXPORT_SYMBOL(omap_video_timings_to_videomode);
