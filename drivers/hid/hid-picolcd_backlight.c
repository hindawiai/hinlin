<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/***************************************************************************
 *   Copyright (C) 2010-2012 by Bruno Prथऊmont <bonbons@linux-vserver.org>  *
 *                                                                         *
 *   Based on Logitech G13 driver (v0.4)                                   *
 *     Copyright (C) 2009 by Rick L. Vinyard, Jr. <rvinyard@cs.nmsu.edu>   *
 *                                                                         *
 ***************************************************************************/

#समावेश <linux/hid.h>

#समावेश <linux/fb.h>
#समावेश <linux/backlight.h>

#समावेश "hid-picolcd.h"

अटल पूर्णांक picolcd_get_brightness(काष्ठा backlight_device *bdev)
अणु
	काष्ठा picolcd_data *data = bl_get_data(bdev);
	वापस data->lcd_brightness;
पूर्ण

अटल पूर्णांक picolcd_set_brightness(काष्ठा backlight_device *bdev)
अणु
	काष्ठा picolcd_data *data = bl_get_data(bdev);
	काष्ठा hid_report *report = picolcd_out_report(REPORT_BRIGHTNESS, data->hdev);
	अचिन्हित दीर्घ flags;

	अगर (!report || report->maxfield != 1 || report->field[0]->report_count != 1)
		वापस -ENODEV;

	data->lcd_brightness = bdev->props.brightness & 0x0ff;
	data->lcd_घातer      = bdev->props.घातer;
	spin_lock_irqsave(&data->lock, flags);
	hid_set_field(report->field[0], 0, data->lcd_घातer == FB_BLANK_UNBLANK ? data->lcd_brightness : 0);
	अगर (!(data->status & PICOLCD_FAILED))
		hid_hw_request(data->hdev, report, HID_REQ_SET_REPORT);
	spin_unlock_irqrestore(&data->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक picolcd_check_bl_fb(काष्ठा backlight_device *bdev, काष्ठा fb_info *fb)
अणु
	वापस fb && fb == picolcd_fbinfo((काष्ठा picolcd_data *)bl_get_data(bdev));
पूर्ण

अटल स्थिर काष्ठा backlight_ops picolcd_blops = अणु
	.update_status  = picolcd_set_brightness,
	.get_brightness = picolcd_get_brightness,
	.check_fb       = picolcd_check_bl_fb,
पूर्ण;

पूर्णांक picolcd_init_backlight(काष्ठा picolcd_data *data, काष्ठा hid_report *report)
अणु
	काष्ठा device *dev = &data->hdev->dev;
	काष्ठा backlight_device *bdev;
	काष्ठा backlight_properties props;
	अगर (!report)
		वापस -ENODEV;
	अगर (report->maxfield != 1 || report->field[0]->report_count != 1 ||
			report->field[0]->report_size != 8) अणु
		dev_err(dev, "unsupported BRIGHTNESS report");
		वापस -EINVAL;
	पूर्ण

	स_रखो(&props, 0, माप(props));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = 0xff;
	bdev = backlight_device_रेजिस्टर(dev_name(dev), dev, data,
			&picolcd_blops, &props);
	अगर (IS_ERR(bdev)) अणु
		dev_err(dev, "failed to register backlight\n");
		वापस PTR_ERR(bdev);
	पूर्ण
	bdev->props.brightness     = 0xff;
	data->lcd_brightness       = 0xff;
	data->backlight            = bdev;
	picolcd_set_brightness(bdev);
	वापस 0;
पूर्ण

व्योम picolcd_निकास_backlight(काष्ठा picolcd_data *data)
अणु
	काष्ठा backlight_device *bdev = data->backlight;

	data->backlight = शून्य;
	backlight_device_unरेजिस्टर(bdev);
पूर्ण

पूर्णांक picolcd_resume_backlight(काष्ठा picolcd_data *data)
अणु
	अगर (!data->backlight)
		वापस 0;
	वापस picolcd_set_brightness(data->backlight);
पूर्ण

#अगर_घोषित CONFIG_PM
व्योम picolcd_suspend_backlight(काष्ठा picolcd_data *data)
अणु
	पूर्णांक bl_घातer = data->lcd_घातer;
	अगर (!data->backlight)
		वापस;

	data->backlight->props.घातer = FB_BLANK_POWERDOWN;
	picolcd_set_brightness(data->backlight);
	data->lcd_घातer = data->backlight->props.घातer = bl_घातer;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

