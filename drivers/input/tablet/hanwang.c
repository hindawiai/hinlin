<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  USB Hanwang tablet support
 *
 *  Copyright (c) 2010 Xing Wei <weixing@hanwang.com.cn>
 */

/*
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/usb/input.h>

MODULE_AUTHOR("Xing Wei <weixing@hanwang.com.cn>");
MODULE_DESCRIPTION("USB Hanwang tablet driver");
MODULE_LICENSE("GPL");

#घोषणा USB_VENDOR_ID_HANWANG		0x0b57
#घोषणा HANWANG_TABLET_INT_CLASS	0x0003
#घोषणा HANWANG_TABLET_INT_SUB_CLASS	0x0001
#घोषणा HANWANG_TABLET_INT_PROTOCOL	0x0002

#घोषणा ART_MASTER_PKGLEN_MAX	10

/* device IDs */
#घोषणा STYLUS_DEVICE_ID	0x02
#घोषणा TOUCH_DEVICE_ID		0x03
#घोषणा CURSOR_DEVICE_ID	0x06
#घोषणा ERASER_DEVICE_ID	0x0A
#घोषणा PAD_DEVICE_ID		0x0F

/* match venकरोr and पूर्णांकerface info  */
#घोषणा HANWANG_TABLET_DEVICE(vend, cl, sc, pr) \
	.match_flags = USB_DEVICE_ID_MATCH_VENDOR \
		| USB_DEVICE_ID_MATCH_INT_INFO, \
	.idVenकरोr = (vend), \
	.bInterfaceClass = (cl), \
	.bInterfaceSubClass = (sc), \
	.bInterfaceProtocol = (pr)

क्रमागत hanwang_tablet_type अणु
	HANWANG_ART_MASTER_III,
	HANWANG_ART_MASTER_HD,
	HANWANG_ART_MASTER_II,
पूर्ण;

काष्ठा hanwang अणु
	अचिन्हित अक्षर *data;
	dma_addr_t data_dma;
	काष्ठा input_dev *dev;
	काष्ठा usb_device *usbdev;
	काष्ठा urb *irq;
	स्थिर काष्ठा hanwang_features *features;
	अचिन्हित पूर्णांक current_tool;
	अचिन्हित पूर्णांक current_id;
	अक्षर name[64];
	अक्षर phys[32];
पूर्ण;

काष्ठा hanwang_features अणु
	अचिन्हित लघु pid;
	अक्षर *name;
	क्रमागत hanwang_tablet_type type;
	पूर्णांक pkg_len;
	पूर्णांक max_x;
	पूर्णांक max_y;
	पूर्णांक max_tilt_x;
	पूर्णांक max_tilt_y;
	पूर्णांक max_pressure;
पूर्ण;

अटल स्थिर काष्ठा hanwang_features features_array[] = अणु
	अणु 0x8528, "Hanwang Art Master III 0906", HANWANG_ART_MASTER_III,
	  ART_MASTER_PKGLEN_MAX, 0x5757, 0x3692, 0x3f, 0x7f, 2048 पूर्ण,
	अणु 0x8529, "Hanwang Art Master III 0604", HANWANG_ART_MASTER_III,
	  ART_MASTER_PKGLEN_MAX, 0x3d84, 0x2672, 0x3f, 0x7f, 2048 पूर्ण,
	अणु 0x852a, "Hanwang Art Master III 1308", HANWANG_ART_MASTER_III,
	  ART_MASTER_PKGLEN_MAX, 0x7f00, 0x4f60, 0x3f, 0x7f, 2048 पूर्ण,
	अणु 0x8401, "Hanwang Art Master HD 5012", HANWANG_ART_MASTER_HD,
	  ART_MASTER_PKGLEN_MAX, 0x678e, 0x4150, 0x3f, 0x7f, 1024 पूर्ण,
	अणु 0x8503, "Hanwang Art Master II", HANWANG_ART_MASTER_II,
	  ART_MASTER_PKGLEN_MAX, 0x27de, 0x1cfe, 0x3f, 0x7f, 1024 पूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक hw_eventtypes[] = अणु
	EV_KEY, EV_ABS, EV_MSC,
पूर्ण;

अटल स्थिर पूर्णांक hw_असलevents[] = अणु
	ABS_X, ABS_Y, ABS_TILT_X, ABS_TILT_Y, ABS_WHEEL,
	ABS_RX, ABS_RY, ABS_PRESSURE, ABS_MISC,
पूर्ण;

अटल स्थिर पूर्णांक hw_btnevents[] = अणु
	BTN_STYLUS, BTN_STYLUS2, BTN_TOOL_PEN, BTN_TOOL_RUBBER,
	BTN_TOOL_MOUSE, BTN_TOOL_FINGER,
	BTN_0, BTN_1, BTN_2, BTN_3, BTN_4, BTN_5, BTN_6, BTN_7, BTN_8,
पूर्ण;

अटल स्थिर पूर्णांक hw_mscevents[] = अणु
	MSC_SERIAL,
पूर्ण;

अटल व्योम hanwang_parse_packet(काष्ठा hanwang *hanwang)
अणु
	अचिन्हित अक्षर *data = hanwang->data;
	काष्ठा input_dev *input_dev = hanwang->dev;
	काष्ठा usb_device *dev = hanwang->usbdev;
	क्रमागत hanwang_tablet_type type = hanwang->features->type;
	पूर्णांक i;
	u16 p;

	अगर (type == HANWANG_ART_MASTER_II) अणु
		hanwang->current_tool = BTN_TOOL_PEN;
		hanwang->current_id = STYLUS_DEVICE_ID;
	पूर्ण

	चयन (data[0]) अणु
	हाल 0x02:	/* data packet */
		चयन (data[1]) अणु
		हाल 0x80:	/* tool prox out */
			अगर (type != HANWANG_ART_MASTER_II) अणु
				hanwang->current_id = 0;
				input_report_key(input_dev,
						 hanwang->current_tool, 0);
			पूर्ण
			अवरोध;

		हाल 0x00:	/* arपंचांगaster ii pen leave */
			अगर (type == HANWANG_ART_MASTER_II) अणु
				hanwang->current_id = 0;
				input_report_key(input_dev,
						 hanwang->current_tool, 0);
			पूर्ण
			अवरोध;

		हाल 0xc2:	/* first समय tool prox in */
			चयन (data[3] & 0xf0) अणु
			हाल 0x20:	/* art_master III */
			हाल 0x30:	/* art_master_HD */
				hanwang->current_id = STYLUS_DEVICE_ID;
				hanwang->current_tool = BTN_TOOL_PEN;
				input_report_key(input_dev, BTN_TOOL_PEN, 1);
				अवरोध;
			हाल 0xa0:	/* art_master III */
			हाल 0xb0:	/* art_master_HD */
				hanwang->current_id = ERASER_DEVICE_ID;
				hanwang->current_tool = BTN_TOOL_RUBBER;
				input_report_key(input_dev, BTN_TOOL_RUBBER, 1);
				अवरोध;
			शेष:
				hanwang->current_id = 0;
				dev_dbg(&dev->dev,
					"unknown tablet tool %02x\n", data[0]);
				अवरोध;
			पूर्ण
			अवरोध;

		शेष:	/* tool data packet */
			चयन (type) अणु
			हाल HANWANG_ART_MASTER_III:
				p = (data[6] << 3) |
				    ((data[7] & 0xc0) >> 5) |
				    (data[1] & 0x01);
				अवरोध;

			हाल HANWANG_ART_MASTER_HD:
			हाल HANWANG_ART_MASTER_II:
				p = (data[7] >> 6) | (data[6] << 2);
				अवरोध;

			शेष:
				p = 0;
				अवरोध;
			पूर्ण

			input_report_असल(input_dev, ABS_X,
					 be16_to_cpup((__be16 *)&data[2]));
			input_report_असल(input_dev, ABS_Y,
					 be16_to_cpup((__be16 *)&data[4]));
			input_report_असल(input_dev, ABS_PRESSURE, p);
			input_report_असल(input_dev, ABS_TILT_X, data[7] & 0x3f);
			input_report_असल(input_dev, ABS_TILT_Y, data[8] & 0x7f);
			input_report_key(input_dev, BTN_STYLUS, data[1] & 0x02);

			अगर (type != HANWANG_ART_MASTER_II)
				input_report_key(input_dev, BTN_STYLUS2,
						 data[1] & 0x04);
			अन्यथा
				input_report_key(input_dev, BTN_TOOL_PEN, 1);

			अवरोध;
		पूर्ण

		input_report_असल(input_dev, ABS_MISC, hanwang->current_id);
		input_event(input_dev, EV_MSC, MSC_SERIAL,
				hanwang->features->pid);
		अवरोध;

	हाल 0x0c:
		/* roll wheel */
		hanwang->current_id = PAD_DEVICE_ID;

		चयन (type) अणु
		हाल HANWANG_ART_MASTER_III:
			input_report_key(input_dev, BTN_TOOL_FINGER,
					 data[1] || data[2] || data[3]);
			input_report_असल(input_dev, ABS_WHEEL, data[1]);
			input_report_key(input_dev, BTN_0, data[2]);
			क्रम (i = 0; i < 8; i++)
				input_report_key(input_dev,
					 BTN_1 + i, data[3] & (1 << i));
			अवरोध;

		हाल HANWANG_ART_MASTER_HD:
			input_report_key(input_dev, BTN_TOOL_FINGER, data[1] ||
					data[2] || data[3] || data[4] ||
					data[5] || data[6]);
			input_report_असल(input_dev, ABS_RX,
					((data[1] & 0x1f) << 8) | data[2]);
			input_report_असल(input_dev, ABS_RY,
					((data[3] & 0x1f) << 8) | data[4]);
			input_report_key(input_dev, BTN_0, data[5] & 0x01);
			क्रम (i = 0; i < 4; i++) अणु
				input_report_key(input_dev,
					 BTN_1 + i, data[5] & (1 << i));
				input_report_key(input_dev,
					 BTN_5 + i, data[6] & (1 << i));
			पूर्ण
			अवरोध;

		हाल HANWANG_ART_MASTER_II:
			dev_dbg(&dev->dev, "error packet  %02x\n", data[0]);
			वापस;
		पूर्ण

		input_report_असल(input_dev, ABS_MISC, hanwang->current_id);
		input_event(input_dev, EV_MSC, MSC_SERIAL, 0xffffffff);
		अवरोध;

	शेष:
		dev_dbg(&dev->dev, "error packet  %02x\n", data[0]);
		अवरोध;
	पूर्ण

	input_sync(input_dev);
पूर्ण

अटल व्योम hanwang_irq(काष्ठा urb *urb)
अणु
	काष्ठा hanwang *hanwang = urb->context;
	काष्ठा usb_device *dev = hanwang->usbdev;
	पूर्णांक retval;

	चयन (urb->status) अणु
	हाल 0:
		/* success */;
		hanwang_parse_packet(hanwang);
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* this urb is terminated, clean up */
		dev_err(&dev->dev, "%s - urb shutting down with status: %d",
			__func__, urb->status);
		वापस;
	शेष:
		dev_err(&dev->dev, "%s - nonzero urb status received: %d",
			__func__, urb->status);
		अवरोध;
	पूर्ण

	retval = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (retval)
		dev_err(&dev->dev, "%s - usb_submit_urb failed with result %d",
			__func__, retval);
पूर्ण

अटल पूर्णांक hanwang_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा hanwang *hanwang = input_get_drvdata(dev);

	hanwang->irq->dev = hanwang->usbdev;
	अगर (usb_submit_urb(hanwang->irq, GFP_KERNEL))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल व्योम hanwang_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा hanwang *hanwang = input_get_drvdata(dev);

	usb_समाप्त_urb(hanwang->irq);
पूर्ण

अटल bool get_features(काष्ठा usb_device *dev, काष्ठा hanwang *hanwang)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(features_array); i++) अणु
		अगर (le16_to_cpu(dev->descriptor.idProduct) ==
				features_array[i].pid) अणु
			hanwang->features = &features_array[i];
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण


अटल पूर्णांक hanwang_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	काष्ठा hanwang *hanwang;
	काष्ठा input_dev *input_dev;
	पूर्णांक error;
	पूर्णांक i;

	अगर (पूर्णांकf->cur_altsetting->desc.bNumEndpoपूर्णांकs < 1)
		वापस -ENODEV;

	hanwang = kzalloc(माप(काष्ठा hanwang), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!hanwang || !input_dev) अणु
		error = -ENOMEM;
		जाओ fail1;
	पूर्ण

	अगर (!get_features(dev, hanwang)) अणु
		error = -ENXIO;
		जाओ fail1;
	पूर्ण

	hanwang->data = usb_alloc_coherent(dev, hanwang->features->pkg_len,
					GFP_KERNEL, &hanwang->data_dma);
	अगर (!hanwang->data) अणु
		error = -ENOMEM;
		जाओ fail1;
	पूर्ण

	hanwang->irq = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!hanwang->irq) अणु
		error = -ENOMEM;
		जाओ fail2;
	पूर्ण

	hanwang->usbdev = dev;
	hanwang->dev = input_dev;

	usb_make_path(dev, hanwang->phys, माप(hanwang->phys));
	strlcat(hanwang->phys, "/input0", माप(hanwang->phys));

	strlcpy(hanwang->name, hanwang->features->name, माप(hanwang->name));
	input_dev->name = hanwang->name;
	input_dev->phys = hanwang->phys;
	usb_to_input_id(dev, &input_dev->id);
	input_dev->dev.parent = &पूर्णांकf->dev;

	input_set_drvdata(input_dev, hanwang);

	input_dev->खोलो = hanwang_खोलो;
	input_dev->बंद = hanwang_बंद;

	क्रम (i = 0; i < ARRAY_SIZE(hw_eventtypes); ++i)
		__set_bit(hw_eventtypes[i], input_dev->evbit);

	क्रम (i = 0; i < ARRAY_SIZE(hw_असलevents); ++i)
		__set_bit(hw_असलevents[i], input_dev->असलbit);

	क्रम (i = 0; i < ARRAY_SIZE(hw_btnevents); ++i)
		__set_bit(hw_btnevents[i], input_dev->keybit);

	क्रम (i = 0; i < ARRAY_SIZE(hw_mscevents); ++i)
		__set_bit(hw_mscevents[i], input_dev->mscbit);

	input_set_असल_params(input_dev, ABS_X,
			     0, hanwang->features->max_x, 4, 0);
	input_set_असल_params(input_dev, ABS_Y,
			     0, hanwang->features->max_y, 4, 0);
	input_set_असल_params(input_dev, ABS_TILT_X,
			     0, hanwang->features->max_tilt_x, 0, 0);
	input_set_असल_params(input_dev, ABS_TILT_Y,
			     0, hanwang->features->max_tilt_y, 0, 0);
	input_set_असल_params(input_dev, ABS_PRESSURE,
			     0, hanwang->features->max_pressure, 0, 0);

	endpoपूर्णांक = &पूर्णांकf->cur_altsetting->endpoपूर्णांक[0].desc;
	usb_fill_पूर्णांक_urb(hanwang->irq, dev,
			usb_rcvपूर्णांकpipe(dev, endpoपूर्णांक->bEndpoपूर्णांकAddress),
			hanwang->data, hanwang->features->pkg_len,
			hanwang_irq, hanwang, endpoपूर्णांक->bInterval);
	hanwang->irq->transfer_dma = hanwang->data_dma;
	hanwang->irq->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	error = input_रेजिस्टर_device(hanwang->dev);
	अगर (error)
		जाओ fail3;

	usb_set_पूर्णांकfdata(पूर्णांकf, hanwang);

	वापस 0;

 fail3:	usb_मुक्त_urb(hanwang->irq);
 fail2:	usb_मुक्त_coherent(dev, hanwang->features->pkg_len,
			hanwang->data, hanwang->data_dma);
 fail1:	input_मुक्त_device(input_dev);
	kमुक्त(hanwang);
	वापस error;

पूर्ण

अटल व्योम hanwang_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा hanwang *hanwang = usb_get_पूर्णांकfdata(पूर्णांकf);

	input_unरेजिस्टर_device(hanwang->dev);
	usb_मुक्त_urb(hanwang->irq);
	usb_मुक्त_coherent(पूर्णांकerface_to_usbdev(पूर्णांकf),
			hanwang->features->pkg_len, hanwang->data,
			hanwang->data_dma);
	kमुक्त(hanwang);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
पूर्ण

अटल स्थिर काष्ठा usb_device_id hanwang_ids[] = अणु
	अणु HANWANG_TABLET_DEVICE(USB_VENDOR_ID_HANWANG, HANWANG_TABLET_INT_CLASS,
		HANWANG_TABLET_INT_SUB_CLASS, HANWANG_TABLET_INT_PROTOCOL) पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, hanwang_ids);

अटल काष्ठा usb_driver hanwang_driver = अणु
	.name		= "hanwang",
	.probe		= hanwang_probe,
	.disconnect	= hanwang_disconnect,
	.id_table	= hanwang_ids,
पूर्ण;

module_usb_driver(hanwang_driver);
