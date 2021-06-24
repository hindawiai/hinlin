<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Common/core components क्रम the Surface System Aggregator Module (SSAM) HID
 * transport driver. Provides support क्रम पूर्णांकegrated HID devices on Microsoft
 * Surface models.
 *
 * Copyright (C) 2019-2021 Maximilian Luz <luzmaximilian@gmail.com>
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/hid.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/usb/ch9.h>

#समावेश <linux/surface_aggregator/controller.h>

#समावेश "surface_hid_core.h"


/* -- Device descriptor access. --------------------------------------------- */

अटल पूर्णांक surface_hid_load_hid_descriptor(काष्ठा surface_hid_device *shid)
अणु
	पूर्णांक status;

	status = shid->ops.get_descriptor(shid, SURFACE_HID_DESC_HID,
			(u8 *)&shid->hid_desc, माप(shid->hid_desc));
	अगर (status)
		वापस status;

	अगर (shid->hid_desc.desc_len != माप(shid->hid_desc)) अणु
		dev_err(shid->dev, "unexpected HID descriptor length: got %u, expected %zu\n",
			shid->hid_desc.desc_len, माप(shid->hid_desc));
		वापस -EPROTO;
	पूर्ण

	अगर (shid->hid_desc.desc_type != HID_DT_HID) अणु
		dev_err(shid->dev, "unexpected HID descriptor type: got %#04x, expected %#04x\n",
			shid->hid_desc.desc_type, HID_DT_HID);
		वापस -EPROTO;
	पूर्ण

	अगर (shid->hid_desc.num_descriptors != 1) अणु
		dev_err(shid->dev, "unexpected number of descriptors: got %u, expected 1\n",
			shid->hid_desc.num_descriptors);
		वापस -EPROTO;
	पूर्ण

	अगर (shid->hid_desc.report_desc_type != HID_DT_REPORT) अणु
		dev_err(shid->dev, "unexpected report descriptor type: got %#04x, expected %#04x\n",
			shid->hid_desc.report_desc_type, HID_DT_REPORT);
		वापस -EPROTO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक surface_hid_load_device_attributes(काष्ठा surface_hid_device *shid)
अणु
	पूर्णांक status;

	status = shid->ops.get_descriptor(shid, SURFACE_HID_DESC_ATTRS,
			(u8 *)&shid->attrs, माप(shid->attrs));
	अगर (status)
		वापस status;

	अगर (get_unaligned_le32(&shid->attrs.length) != माप(shid->attrs)) अणु
		dev_err(shid->dev, "unexpected attribute length: got %u, expected %zu\n",
			get_unaligned_le32(&shid->attrs.length), माप(shid->attrs));
		वापस -EPROTO;
	पूर्ण

	वापस 0;
पूर्ण


/* -- Transport driver (common). -------------------------------------------- */

अटल पूर्णांक surface_hid_start(काष्ठा hid_device *hid)
अणु
	काष्ठा surface_hid_device *shid = hid->driver_data;

	वापस ssam_notअगरier_रेजिस्टर(shid->ctrl, &shid->notअगर);
पूर्ण

अटल व्योम surface_hid_stop(काष्ठा hid_device *hid)
अणु
	काष्ठा surface_hid_device *shid = hid->driver_data;

	/* Note: This call will log errors क्रम us, so ignore them here. */
	ssam_notअगरier_unरेजिस्टर(shid->ctrl, &shid->notअगर);
पूर्ण

अटल पूर्णांक surface_hid_खोलो(काष्ठा hid_device *hid)
अणु
	वापस 0;
पूर्ण

अटल व्योम surface_hid_बंद(काष्ठा hid_device *hid)
अणु
पूर्ण

अटल पूर्णांक surface_hid_parse(काष्ठा hid_device *hid)
अणु
	काष्ठा surface_hid_device *shid = hid->driver_data;
	माप_प्रकार len = get_unaligned_le16(&shid->hid_desc.report_desc_len);
	u8 *buf;
	पूर्णांक status;

	buf = kzalloc(len, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	status = shid->ops.get_descriptor(shid, SURFACE_HID_DESC_REPORT, buf, len);
	अगर (!status)
		status = hid_parse_report(hid, buf, len);

	kमुक्त(buf);
	वापस status;
पूर्ण

अटल पूर्णांक surface_hid_raw_request(काष्ठा hid_device *hid, अचिन्हित अक्षर reportnum, u8 *buf,
				   माप_प्रकार len, अचिन्हित अक्षर rtype, पूर्णांक reqtype)
अणु
	काष्ठा surface_hid_device *shid = hid->driver_data;

	अगर (rtype == HID_OUTPUT_REPORT && reqtype == HID_REQ_SET_REPORT)
		वापस shid->ops.output_report(shid, reportnum, buf, len);

	अन्यथा अगर (rtype == HID_FEATURE_REPORT && reqtype == HID_REQ_GET_REPORT)
		वापस shid->ops.get_feature_report(shid, reportnum, buf, len);

	अन्यथा अगर (rtype == HID_FEATURE_REPORT && reqtype == HID_REQ_SET_REPORT)
		वापस shid->ops.set_feature_report(shid, reportnum, buf, len);

	वापस -EIO;
पूर्ण

अटल काष्ठा hid_ll_driver surface_hid_ll_driver = अणु
	.start       = surface_hid_start,
	.stop        = surface_hid_stop,
	.खोलो        = surface_hid_खोलो,
	.बंद       = surface_hid_बंद,
	.parse       = surface_hid_parse,
	.raw_request = surface_hid_raw_request,
पूर्ण;


/* -- Common device setup. -------------------------------------------------- */

पूर्णांक surface_hid_device_add(काष्ठा surface_hid_device *shid)
अणु
	पूर्णांक status;

	status = surface_hid_load_hid_descriptor(shid);
	अगर (status)
		वापस status;

	status = surface_hid_load_device_attributes(shid);
	अगर (status)
		वापस status;

	shid->hid = hid_allocate_device();
	अगर (IS_ERR(shid->hid))
		वापस PTR_ERR(shid->hid);

	shid->hid->dev.parent = shid->dev;
	shid->hid->bus = BUS_HOST;
	shid->hid->venकरोr = get_unaligned_le16(&shid->attrs.venकरोr);
	shid->hid->product = get_unaligned_le16(&shid->attrs.product);
	shid->hid->version = get_unaligned_le16(&shid->hid_desc.hid_version);
	shid->hid->country = shid->hid_desc.country_code;

	snम_लिखो(shid->hid->name, माप(shid->hid->name), "Microsoft Surface %04X:%04X",
		 shid->hid->venकरोr, shid->hid->product);

	strscpy(shid->hid->phys, dev_name(shid->dev), माप(shid->hid->phys));

	shid->hid->driver_data = shid;
	shid->hid->ll_driver = &surface_hid_ll_driver;

	status = hid_add_device(shid->hid);
	अगर (status)
		hid_destroy_device(shid->hid);

	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(surface_hid_device_add);

व्योम surface_hid_device_destroy(काष्ठा surface_hid_device *shid)
अणु
	hid_destroy_device(shid->hid);
पूर्ण
EXPORT_SYMBOL_GPL(surface_hid_device_destroy);


/* -- PM ops. --------------------------------------------------------------- */

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक surface_hid_suspend(काष्ठा device *dev)
अणु
	काष्ठा surface_hid_device *d = dev_get_drvdata(dev);

	अगर (d->hid->driver && d->hid->driver->suspend)
		वापस d->hid->driver->suspend(d->hid, PMSG_SUSPEND);

	वापस 0;
पूर्ण

अटल पूर्णांक surface_hid_resume(काष्ठा device *dev)
अणु
	काष्ठा surface_hid_device *d = dev_get_drvdata(dev);

	अगर (d->hid->driver && d->hid->driver->resume)
		वापस d->hid->driver->resume(d->hid);

	वापस 0;
पूर्ण

अटल पूर्णांक surface_hid_मुक्तze(काष्ठा device *dev)
अणु
	काष्ठा surface_hid_device *d = dev_get_drvdata(dev);

	अगर (d->hid->driver && d->hid->driver->suspend)
		वापस d->hid->driver->suspend(d->hid, PMSG_FREEZE);

	वापस 0;
पूर्ण

अटल पूर्णांक surface_hid_घातeroff(काष्ठा device *dev)
अणु
	काष्ठा surface_hid_device *d = dev_get_drvdata(dev);

	अगर (d->hid->driver && d->hid->driver->suspend)
		वापस d->hid->driver->suspend(d->hid, PMSG_HIBERNATE);

	वापस 0;
पूर्ण

अटल पूर्णांक surface_hid_restore(काष्ठा device *dev)
अणु
	काष्ठा surface_hid_device *d = dev_get_drvdata(dev);

	अगर (d->hid->driver && d->hid->driver->reset_resume)
		वापस d->hid->driver->reset_resume(d->hid);

	वापस 0;
पूर्ण

स्थिर काष्ठा dev_pm_ops surface_hid_pm_ops = अणु
	.मुक्तze   = surface_hid_मुक्तze,
	.thaw     = surface_hid_resume,
	.suspend  = surface_hid_suspend,
	.resume   = surface_hid_resume,
	.घातeroff = surface_hid_घातeroff,
	.restore  = surface_hid_restore,
पूर्ण;
EXPORT_SYMBOL_GPL(surface_hid_pm_ops);

#अन्यथा /* CONFIG_PM_SLEEP */

स्थिर काष्ठा dev_pm_ops surface_hid_pm_ops = अणु पूर्ण;
EXPORT_SYMBOL_GPL(surface_hid_pm_ops);

#पूर्ण_अगर /* CONFIG_PM_SLEEP */

MODULE_AUTHOR("Maximilian Luz <luzmaximilian@gmail.com>");
MODULE_DESCRIPTION("HID transport driver core for Surface System Aggregator Module");
MODULE_LICENSE("GPL");
