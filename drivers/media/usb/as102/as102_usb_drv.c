<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Abilis Systems Single DVB-T Receiver
 * Copyright (C) 2008 Pierrick Hascoet <pierrick.hascoet@abilis.com>
 * Copyright (C) 2010 Devin Heiपंचांगueller <dheiपंचांगueller@kernelद_असल.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/usb.h>

#समावेश "as102_drv.h"
#समावेश "as102_usb_drv.h"
#समावेश "as102_fw.h"

अटल व्योम as102_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface);
अटल पूर्णांक as102_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			   स्थिर काष्ठा usb_device_id *id);

अटल पूर्णांक as102_usb_start_stream(काष्ठा as102_dev_t *dev);
अटल व्योम as102_usb_stop_stream(काष्ठा as102_dev_t *dev);

अटल पूर्णांक as102_खोलो(काष्ठा inode *inode, काष्ठा file *file);
अटल पूर्णांक as102_release(काष्ठा inode *inode, काष्ठा file *file);

अटल स्थिर काष्ठा usb_device_id as102_usb_id_table[] = अणु
	अणु USB_DEVICE(AS102_USB_DEVICE_VENDOR_ID, AS102_USB_DEVICE_PID_0001) पूर्ण,
	अणु USB_DEVICE(PCTV_74E_USB_VID, PCTV_74E_USB_PID) पूर्ण,
	अणु USB_DEVICE(ELGATO_EYETV_DTT_USB_VID, ELGATO_EYETV_DTT_USB_PID) पूर्ण,
	अणु USB_DEVICE(NBOX_DVBT_DONGLE_USB_VID, NBOX_DVBT_DONGLE_USB_PID) पूर्ण,
	अणु USB_DEVICE(SKY_IT_DIGITAL_KEY_USB_VID, SKY_IT_DIGITAL_KEY_USB_PID) पूर्ण,
	अणु पूर्ण /* Terminating entry */
पूर्ण;

/* Note that this table must always have the same number of entries as the
   as102_usb_id_table काष्ठा */
अटल स्थिर अक्षर * स्थिर as102_device_names[] = अणु
	AS102_REFERENCE_DESIGN,
	AS102_PCTV_74E,
	AS102_ELGATO_EYETV_DTT_NAME,
	AS102_NBOX_DVBT_DONGLE_NAME,
	AS102_SKY_IT_DIGITAL_KEY_NAME,
	शून्य /* Terminating entry */
पूर्ण;

/* eLNA configuration: devices built on the reference design work best
   with 0xA0, जबतक custom designs seem to require 0xC0 */
अटल uपूर्णांक8_t स्थिर as102_elna_cfg[] = अणु
	0xA0,
	0xC0,
	0xC0,
	0xA0,
	0xA0,
	0x00 /* Terminating entry */
पूर्ण;

काष्ठा usb_driver as102_usb_driver = अणु
	.name		= DRIVER_FULL_NAME,
	.probe		= as102_usb_probe,
	.disconnect	= as102_usb_disconnect,
	.id_table	= as102_usb_id_table
पूर्ण;

अटल स्थिर काष्ठा file_operations as102_dev_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= as102_खोलो,
	.release	= as102_release,
पूर्ण;

अटल काष्ठा usb_class_driver as102_usb_class_driver = अणु
	.name		= "aton2-%d",
	.fops		= &as102_dev_fops,
	.minor_base	= AS102_DEVICE_MAJOR,
पूर्ण;

अटल पूर्णांक as102_usb_xfer_cmd(काष्ठा as10x_bus_adapter_t *bus_adap,
			      अचिन्हित अक्षर *send_buf, पूर्णांक send_buf_len,
			      अचिन्हित अक्षर *recv_buf, पूर्णांक recv_buf_len)
अणु
	पूर्णांक ret = 0;

	अगर (send_buf != शून्य) अणु
		ret = usb_control_msg(bus_adap->usb_dev,
				      usb_sndctrlpipe(bus_adap->usb_dev, 0),
				      AS102_USB_DEVICE_TX_CTRL_CMD,
				      USB_सूची_OUT | USB_TYPE_VENDOR |
				      USB_RECIP_DEVICE,
				      bus_adap->cmd_xid, /* value */
				      0, /* index */
				      send_buf, send_buf_len,
				      USB_CTRL_SET_TIMEOUT /* 200 */);
		अगर (ret < 0) अणु
			dev_dbg(&bus_adap->usb_dev->dev,
				"usb_control_msg(send) failed, err %i\n", ret);
			वापस ret;
		पूर्ण

		अगर (ret != send_buf_len) अणु
			dev_dbg(&bus_adap->usb_dev->dev,
			"only wrote %d of %d bytes\n", ret, send_buf_len);
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (recv_buf != शून्य) अणु
#अगर_घोषित TRACE
		dev_dbg(bus_adap->usb_dev->dev,
			"want to read: %d bytes\n", recv_buf_len);
#पूर्ण_अगर
		ret = usb_control_msg(bus_adap->usb_dev,
				      usb_rcvctrlpipe(bus_adap->usb_dev, 0),
				      AS102_USB_DEVICE_RX_CTRL_CMD,
				      USB_सूची_IN | USB_TYPE_VENDOR |
				      USB_RECIP_DEVICE,
				      bus_adap->cmd_xid, /* value */
				      0, /* index */
				      recv_buf, recv_buf_len,
				      USB_CTRL_GET_TIMEOUT /* 200 */);
		अगर (ret < 0) अणु
			dev_dbg(&bus_adap->usb_dev->dev,
				"usb_control_msg(recv) failed, err %i\n", ret);
			वापस ret;
		पूर्ण
#अगर_घोषित TRACE
		dev_dbg(bus_adap->usb_dev->dev,
			"read %d bytes\n", recv_buf_len);
#पूर्ण_अगर
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक as102_send_ep1(काष्ठा as10x_bus_adapter_t *bus_adap,
			  अचिन्हित अक्षर *send_buf,
			  पूर्णांक send_buf_len,
			  पूर्णांक swap32)
अणु
	पूर्णांक ret, actual_len;

	ret = usb_bulk_msg(bus_adap->usb_dev,
			   usb_sndbulkpipe(bus_adap->usb_dev, 1),
			   send_buf, send_buf_len, &actual_len, 200);
	अगर (ret) अणु
		dev_dbg(&bus_adap->usb_dev->dev,
			"usb_bulk_msg(send) failed, err %i\n", ret);
		वापस ret;
	पूर्ण

	अगर (actual_len != send_buf_len) अणु
		dev_dbg(&bus_adap->usb_dev->dev, "only wrote %d of %d bytes\n",
			actual_len, send_buf_len);
		वापस -1;
	पूर्ण
	वापस actual_len;
पूर्ण

अटल पूर्णांक as102_पढ़ो_ep2(काष्ठा as10x_bus_adapter_t *bus_adap,
		   अचिन्हित अक्षर *recv_buf, पूर्णांक recv_buf_len)
अणु
	पूर्णांक ret, actual_len;

	अगर (recv_buf == शून्य)
		वापस -EINVAL;

	ret = usb_bulk_msg(bus_adap->usb_dev,
			   usb_rcvbulkpipe(bus_adap->usb_dev, 2),
			   recv_buf, recv_buf_len, &actual_len, 200);
	अगर (ret) अणु
		dev_dbg(&bus_adap->usb_dev->dev,
			"usb_bulk_msg(recv) failed, err %i\n", ret);
		वापस ret;
	पूर्ण

	अगर (actual_len != recv_buf_len) अणु
		dev_dbg(&bus_adap->usb_dev->dev, "only read %d of %d bytes\n",
			actual_len, recv_buf_len);
		वापस -1;
	पूर्ण
	वापस actual_len;
पूर्ण

अटल स्थिर काष्ठा as102_priv_ops_t as102_priv_ops = अणु
	.upload_fw_pkt	= as102_send_ep1,
	.xfer_cmd	= as102_usb_xfer_cmd,
	.as102_पढ़ो_ep2	= as102_पढ़ो_ep2,
	.start_stream	= as102_usb_start_stream,
	.stop_stream	= as102_usb_stop_stream,
पूर्ण;

अटल पूर्णांक as102_submit_urb_stream(काष्ठा as102_dev_t *dev, काष्ठा urb *urb)
अणु
	पूर्णांक err;

	usb_fill_bulk_urb(urb,
			  dev->bus_adap.usb_dev,
			  usb_rcvbulkpipe(dev->bus_adap.usb_dev, 0x2),
			  urb->transfer_buffer,
			  AS102_USB_BUF_SIZE,
			  as102_urb_stream_irq,
			  dev);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (err)
		dev_dbg(&urb->dev->dev,
			"%s: usb_submit_urb failed\n", __func__);

	वापस err;
पूर्ण

व्योम as102_urb_stream_irq(काष्ठा urb *urb)
अणु
	काष्ठा as102_dev_t *as102_dev = urb->context;

	अगर (urb->actual_length > 0) अणु
		dvb_dmx_swfilter(&as102_dev->dvb_dmx,
				 urb->transfer_buffer,
				 urb->actual_length);
	पूर्ण अन्यथा अणु
		अगर (urb->actual_length == 0)
			स_रखो(urb->transfer_buffer, 0, AS102_USB_BUF_SIZE);
	पूर्ण

	/* is not stopped, re-submit urb */
	अगर (as102_dev->streaming)
		as102_submit_urb_stream(as102_dev, urb);
पूर्ण

अटल व्योम as102_मुक्त_usb_stream_buffer(काष्ठा as102_dev_t *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_STREAM_URB; i++)
		usb_मुक्त_urb(dev->stream_urb[i]);

	usb_मुक्त_coherent(dev->bus_adap.usb_dev,
			MAX_STREAM_URB * AS102_USB_BUF_SIZE,
			dev->stream,
			dev->dma_addr);
पूर्ण

अटल पूर्णांक as102_alloc_usb_stream_buffer(काष्ठा as102_dev_t *dev)
अणु
	पूर्णांक i;

	dev->stream = usb_alloc_coherent(dev->bus_adap.usb_dev,
				       MAX_STREAM_URB * AS102_USB_BUF_SIZE,
				       GFP_KERNEL,
				       &dev->dma_addr);
	अगर (!dev->stream) अणु
		dev_dbg(&dev->bus_adap.usb_dev->dev,
			"%s: usb_buffer_alloc failed\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	स_रखो(dev->stream, 0, MAX_STREAM_URB * AS102_USB_BUF_SIZE);

	/* init urb buffers */
	क्रम (i = 0; i < MAX_STREAM_URB; i++) अणु
		काष्ठा urb *urb;

		urb = usb_alloc_urb(0, GFP_ATOMIC);
		अगर (urb == शून्य) अणु
			as102_मुक्त_usb_stream_buffer(dev);
			वापस -ENOMEM;
		पूर्ण

		urb->transfer_buffer = dev->stream + (i * AS102_USB_BUF_SIZE);
		urb->transfer_dma = dev->dma_addr + (i * AS102_USB_BUF_SIZE);
		urb->transfer_flags = URB_NO_TRANSFER_DMA_MAP;
		urb->transfer_buffer_length = AS102_USB_BUF_SIZE;

		dev->stream_urb[i] = urb;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम as102_usb_stop_stream(काष्ठा as102_dev_t *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_STREAM_URB; i++)
		usb_समाप्त_urb(dev->stream_urb[i]);
पूर्ण

अटल पूर्णांक as102_usb_start_stream(काष्ठा as102_dev_t *dev)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < MAX_STREAM_URB; i++) अणु
		ret = as102_submit_urb_stream(dev, dev->stream_urb[i]);
		अगर (ret) अणु
			as102_usb_stop_stream(dev);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम as102_usb_release(काष्ठा kref *kref)
अणु
	काष्ठा as102_dev_t *as102_dev;

	as102_dev = container_of(kref, काष्ठा as102_dev_t, kref);
	अगर (as102_dev != शून्य) अणु
		usb_put_dev(as102_dev->bus_adap.usb_dev);
		kमुक्त(as102_dev);
	पूर्ण
पूर्ण

अटल व्योम as102_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा as102_dev_t *as102_dev;

	/* extract as102_dev_t from usb_device निजी data */
	as102_dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	/* unरेजिस्टर dvb layer */
	as102_dvb_unरेजिस्टर(as102_dev);

	/* मुक्त usb buffers */
	as102_मुक्त_usb_stream_buffer(as102_dev);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	/* usb unरेजिस्टर device */
	usb_deरेजिस्टर_dev(पूर्णांकf, &as102_usb_class_driver);

	/* decrement usage counter */
	kref_put(&as102_dev->kref, as102_usb_release);

	pr_info("%s: device has been disconnected\n", DRIVER_NAME);
पूर्ण

अटल पूर्णांक as102_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			   स्थिर काष्ठा usb_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा as102_dev_t *as102_dev;
	पूर्णांक i;

	/* This should never actually happen */
	अगर (ARRAY_SIZE(as102_usb_id_table) !=
	    (माप(as102_device_names) / माप(स्थिर अक्षर *))) अणु
		pr_err("Device names table invalid size");
		वापस -EINVAL;
	पूर्ण

	as102_dev = kzalloc(माप(काष्ठा as102_dev_t), GFP_KERNEL);
	अगर (as102_dev == शून्य)
		वापस -ENOMEM;

	/* Assign the user-मित्रly device name */
	क्रम (i = 0; i < ARRAY_SIZE(as102_usb_id_table); i++) अणु
		अगर (id == &as102_usb_id_table[i]) अणु
			as102_dev->name = as102_device_names[i];
			as102_dev->elna_cfg = as102_elna_cfg[i];
		पूर्ण
	पूर्ण

	अगर (as102_dev->name == शून्य)
		as102_dev->name = "Unknown AS102 device";

	/* set निजी callback functions */
	as102_dev->bus_adap.ops = &as102_priv_ops;

	/* init cmd token क्रम usb bus */
	as102_dev->bus_adap.cmd = &as102_dev->bus_adap.token.usb.c;
	as102_dev->bus_adap.rsp = &as102_dev->bus_adap.token.usb.r;

	/* init kernel device reference */
	kref_init(&as102_dev->kref);

	/* store as102 device to usb_device निजी data */
	usb_set_पूर्णांकfdata(पूर्णांकf, (व्योम *) as102_dev);

	/* store in as102 device the usb_device poपूर्णांकer */
	as102_dev->bus_adap.usb_dev = usb_get_dev(पूर्णांकerface_to_usbdev(पूर्णांकf));

	/* we can रेजिस्टर the device now, as it is पढ़ोy */
	ret = usb_रेजिस्टर_dev(पूर्णांकf, &as102_usb_class_driver);
	अगर (ret < 0) अणु
		/* something prevented us from रेजिस्टरing this driver */
		dev_err(&पूर्णांकf->dev,
			"%s: usb_register_dev() failed (errno = %d)\n",
			__func__, ret);
		जाओ failed;
	पूर्ण

	pr_info("%s: device has been detected\n", DRIVER_NAME);

	/* request buffer allocation क्रम streaming */
	ret = as102_alloc_usb_stream_buffer(as102_dev);
	अगर (ret != 0)
		जाओ failed_stream;

	/* रेजिस्टर dvb layer */
	ret = as102_dvb_रेजिस्टर(as102_dev);
	अगर (ret != 0)
		जाओ failed_dvb;

	वापस ret;

failed_dvb:
	as102_मुक्त_usb_stream_buffer(as102_dev);
failed_stream:
	usb_deरेजिस्टर_dev(पूर्णांकf, &as102_usb_class_driver);
failed:
	usb_put_dev(as102_dev->bus_adap.usb_dev);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	kमुक्त(as102_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक as102_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret = 0, minor = 0;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = शून्य;
	काष्ठा as102_dev_t *dev = शून्य;

	/* पढ़ो minor from inode */
	minor = iminor(inode);

	/* fetch device from usb पूर्णांकerface */
	पूर्णांकf = usb_find_पूर्णांकerface(&as102_usb_driver, minor);
	अगर (पूर्णांकf == शून्य) अणु
		pr_err("%s: can't find device for minor %d\n",
		       __func__, minor);
		ret = -ENODEV;
		जाओ निकास;
	पूर्ण

	/* get our device */
	dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	अगर (dev == शून्य) अणु
		ret = -EFAULT;
		जाओ निकास;
	पूर्ण

	/* save our device object in the file's निजी काष्ठाure */
	file->निजी_data = dev;

	/* increment our usage count क्रम the device */
	kref_get(&dev->kref);

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक as102_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा as102_dev_t *dev = शून्य;

	dev = file->निजी_data;
	अगर (dev != शून्य) अणु
		/* decrement the count on our device */
		kref_put(&dev->kref, as102_usb_release);
	पूर्ण

	वापस 0;
पूर्ण

MODULE_DEVICE_TABLE(usb, as102_usb_id_table);
