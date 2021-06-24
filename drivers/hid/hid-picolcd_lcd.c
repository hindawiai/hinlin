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
#समावेश <linux/lcd.h>

#समावेश "hid-picolcd.h"

/*
 * lcd class device
 */
अटल पूर्णांक picolcd_get_contrast(काष्ठा lcd_device *ldev)
अणु
	काष्ठा picolcd_data *data = lcd_get_data(ldev);
	वापस data->lcd_contrast;
पूर्ण

अटल पूर्णांक picolcd_set_contrast(काष्ठा lcd_device *ldev, पूर्णांक contrast)
अणु
	काष्ठा picolcd_data *data = lcd_get_data(ldev);
	काष्ठा hid_report *report = picolcd_out_report(REPORT_CONTRAST, data->hdev);
	अचिन्हित दीर्घ flags;

	अगर (!report || report->maxfield != 1 || report->field[0]->report_count != 1)
		वापस -ENODEV;

	data->lcd_contrast = contrast & 0x0ff;
	spin_lock_irqsave(&data->lock, flags);
	hid_set_field(report->field[0], 0, data->lcd_contrast);
	अगर (!(data->status & PICOLCD_FAILED))
		hid_hw_request(data->hdev, report, HID_REQ_SET_REPORT);
	spin_unlock_irqrestore(&data->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक picolcd_check_lcd_fb(काष्ठा lcd_device *ldev, काष्ठा fb_info *fb)
अणु
	वापस fb && fb == picolcd_fbinfo((काष्ठा picolcd_data *)lcd_get_data(ldev));
पूर्ण

अटल काष्ठा lcd_ops picolcd_lcकरोps = अणु
	.get_contrast   = picolcd_get_contrast,
	.set_contrast   = picolcd_set_contrast,
	.check_fb       = picolcd_check_lcd_fb,
पूर्ण;

पूर्णांक picolcd_init_lcd(काष्ठा picolcd_data *data, काष्ठा hid_report *report)
अणु
	काष्ठा device *dev = &data->hdev->dev;
	काष्ठा lcd_device *ldev;

	अगर (!report)
		वापस -ENODEV;
	अगर (report->maxfield != 1 || report->field[0]->report_count != 1 ||
			report->field[0]->report_size != 8) अणु
		dev_err(dev, "unsupported CONTRAST report");
		वापस -EINVAL;
	पूर्ण

	ldev = lcd_device_रेजिस्टर(dev_name(dev), dev, data, &picolcd_lcकरोps);
	अगर (IS_ERR(ldev)) अणु
		dev_err(dev, "failed to register LCD\n");
		वापस PTR_ERR(ldev);
	पूर्ण
	ldev->props.max_contrast = 0x0ff;
	data->lcd_contrast = 0xe5;
	data->lcd = ldev;
	picolcd_set_contrast(ldev, 0xe5);
	वापस 0;
पूर्ण

व्योम picolcd_निकास_lcd(काष्ठा picolcd_data *data)
अणु
	काष्ठा lcd_device *ldev = data->lcd;

	data->lcd = शून्य;
	lcd_device_unरेजिस्टर(ldev);
पूर्ण

पूर्णांक picolcd_resume_lcd(काष्ठा picolcd_data *data)
अणु
	अगर (!data->lcd)
		वापस 0;
	वापस picolcd_set_contrast(data->lcd, data->lcd_contrast);
पूर्ण

