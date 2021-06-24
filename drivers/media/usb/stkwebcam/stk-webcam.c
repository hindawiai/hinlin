<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * stk-webcam.c : Driver क्रम Syntek 1125 USB webcam controller
 *
 * Copyright (C) 2006 Nicolas VIVIEN
 * Copyright 2007-2008 Jaime Velasco Juan <jsagarribay@gmail.com>
 *
 * Some parts are inspired from cafe_ccic.c
 * Copyright 2006-2007 Jonathan Corbet
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>

#समावेश <linux/dmi.h>
#समावेश <linux/usb.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-event.h>

#समावेश "stk-webcam.h"


अटल पूर्णांक hflip = -1;
module_param(hflip, पूर्णांक, 0444);
MODULE_PARM_DESC(hflip, "Horizontal image flip (mirror). Defaults to 0");

अटल पूर्णांक vflip = -1;
module_param(vflip, पूर्णांक, 0444);
MODULE_PARM_DESC(vflip, "Vertical image flip. Defaults to 0");

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0444);
MODULE_PARM_DESC(debug, "Debug v4l ioctls. Defaults to 0");

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jaime Velasco Juan <jsagarribay@gmail.com> and Nicolas VIVIEN");
MODULE_DESCRIPTION("Syntek DC1125 webcam driver");

/* Some cameras have audio पूर्णांकerfaces, we aren't पूर्णांकerested in those */
अटल स्थिर काष्ठा usb_device_id stkwebcam_table[] = अणु
	अणु USB_DEVICE_AND_INTERFACE_INFO(0x174f, 0xa311, 0xff, 0xff, 0xff) पूर्ण,
	अणु USB_DEVICE_AND_INTERFACE_INFO(0x05e1, 0x0501, 0xff, 0xff, 0xff) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, stkwebcam_table);

/*
 * The stk webcam laptop module is mounted upside करोwn in some laptops :(
 *
 * Some background inक्रमmation (thanks to Hans de Goede क्रम providing this):
 *
 * 1) Once upon a समय the stkwebcam driver was written
 *
 * 2) The webcam in question was used mostly in Asus laptop models, including
 * the laptop of the original author of the driver, and in these models, in
 * typical Asus fashion (see the दीर्घ दीर्घ list क्रम uvc cams inside v4l-utils),
 * they mounted the webcam-module the wrong way up. So the hflip and vflip
 * module options were given a शेष value of 1 (the correct value क्रम
 * upside करोwn mounted models)
 *
 * 3) Years later I got a bug report from a user with a laptop with stkwebcam,
 * where the module was actually mounted the right way up, and thus showed
 * upside करोwn under Linux. So now I was facing the choice of 2 options:
 *
 * a) Add a not-upside-करोwn list to stkwebcam, which overrules the शेष.
 *
 * b) Do it like all the other drivers करो, and make the शेष right क्रम
 *    cams mounted the proper way and add an upside-करोwn model list, with
 *    models where we need to flip-by-शेष.
 *
 * Despite knowing that going b) would cause a period of pain where we were
 * building the table I opted to go क्रम option b), since a) is just too ugly,
 * and worse dअगरferent from how every other driver करोes it leading to
 * confusion in the दीर्घ run. This change was made in kernel 3.6.
 *
 * So क्रम any user report about upside-करोwn images since kernel 3.6 ask them
 * to provide the output of 'sudo dmidecode' so the laptop can be added in
 * the table below.
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id stk_upside_करोwn_dmi_table[] = अणु
	अणु
		.ident = "ASUS G1",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK Computer Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "G1")
		पूर्ण
	पूर्ण, अणु
		.ident = "ASUS F3JC",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK Computer Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "F3JC")
		पूर्ण
	पूर्ण,
	अणु
		.ident = "T12Rg-H",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "HCL Infosystems Limited"),
			DMI_MATCH(DMI_PRODUCT_NAME, "T12Rg-H")
		पूर्ण
	पूर्ण,
	अणु
		.ident = "ASUS A6VM",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK Computer Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "A6VM")
		पूर्ण
	पूर्ण,
	अणुपूर्ण
पूर्ण;


/*
 * Basic stuff
 */
पूर्णांक stk_camera_ग_लिखो_reg(काष्ठा stk_camera *dev, u16 index, u8 value)
अणु
	काष्ठा usb_device *udev = dev->udev;
	पूर्णांक ret;

	ret =  usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			0x01,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			value,
			index,
			शून्य,
			0,
			500);
	अगर (ret < 0)
		वापस ret;
	अन्यथा
		वापस 0;
पूर्ण

पूर्णांक stk_camera_पढ़ो_reg(काष्ठा stk_camera *dev, u16 index, u8 *value)
अणु
	काष्ठा usb_device *udev = dev->udev;
	अचिन्हित अक्षर *buf;
	पूर्णांक ret;

	buf = kदो_स्मृति(माप(u8), GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
			0x00,
			USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0x00,
			index,
			buf,
			माप(u8),
			500);
	अगर (ret >= 0)
		*value = *buf;

	kमुक्त(buf);

	अगर (ret < 0)
		वापस ret;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक stk_start_stream(काष्ठा stk_camera *dev)
अणु
	u8 value;
	पूर्णांक i, ret;
	u8 value_116, value_117;


	अगर (!is_present(dev))
		वापस -ENODEV;
	अगर (!is_meदो_स्मृतिd(dev) || !is_initialised(dev)) अणु
		pr_err("FIXME: Buffers are not allocated\n");
		वापस -EFAULT;
	पूर्ण
	ret = usb_set_पूर्णांकerface(dev->udev, 0, 5);

	अगर (ret < 0)
		pr_err("usb_set_interface failed !\n");
	अगर (stk_sensor_wakeup(dev))
		pr_err("error awaking the sensor\n");

	stk_camera_पढ़ो_reg(dev, 0x0116, &value_116);
	stk_camera_पढ़ो_reg(dev, 0x0117, &value_117);

	stk_camera_ग_लिखो_reg(dev, 0x0116, 0x0000);
	stk_camera_ग_लिखो_reg(dev, 0x0117, 0x0000);

	stk_camera_पढ़ो_reg(dev, 0x0100, &value);
	stk_camera_ग_लिखो_reg(dev, 0x0100, value | 0x80);

	stk_camera_ग_लिखो_reg(dev, 0x0116, value_116);
	stk_camera_ग_लिखो_reg(dev, 0x0117, value_117);
	क्रम (i = 0; i < MAX_ISO_BUFS; i++) अणु
		अगर (dev->isobufs[i].urb) अणु
			ret = usb_submit_urb(dev->isobufs[i].urb, GFP_KERNEL);
			atomic_inc(&dev->urbs_used);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण
	set_streaming(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक stk_stop_stream(काष्ठा stk_camera *dev)
अणु
	u8 value;
	पूर्णांक i;
	अगर (is_present(dev)) अणु
		stk_camera_पढ़ो_reg(dev, 0x0100, &value);
		stk_camera_ग_लिखो_reg(dev, 0x0100, value & ~0x80);
		अगर (dev->isobufs != शून्य) अणु
			क्रम (i = 0; i < MAX_ISO_BUFS; i++) अणु
				अगर (dev->isobufs[i].urb)
					usb_समाप्त_urb(dev->isobufs[i].urb);
			पूर्ण
		पूर्ण
		unset_streaming(dev);

		अगर (usb_set_पूर्णांकerface(dev->udev, 0, 0))
			pr_err("usb_set_interface failed !\n");
		अगर (stk_sensor_sleep(dev))
			pr_err("error suspending the sensor\n");
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This seems to be the लघुest init sequence we
 * must करो in order to find the sensor
 * Bit 5 of reg. 0x0000 here is important, when reset to 0 the sensor
 * is also reset. Maybe घातers करोwn it?
 * Rest of values करोn't make a dअगरference
 */

अटल काष्ठा regval stk1125_initvals[] = अणु
	/*TODO: What means this sequence? */
	अणु0x0000, 0x24पूर्ण,
	अणु0x0100, 0x21पूर्ण,
	अणु0x0002, 0x68पूर्ण,
	अणु0x0003, 0x80पूर्ण,
	अणु0x0005, 0x00पूर्ण,
	अणु0x0007, 0x03पूर्ण,
	अणु0x000d, 0x00पूर्ण,
	अणु0x000f, 0x02पूर्ण,
	अणु0x0300, 0x12पूर्ण,
	अणु0x0350, 0x41पूर्ण,
	अणु0x0351, 0x00पूर्ण,
	अणु0x0352, 0x00पूर्ण,
	अणु0x0353, 0x00पूर्ण,
	अणु0x0018, 0x10पूर्ण,
	अणु0x0019, 0x00पूर्ण,
	अणु0x001b, 0x0eपूर्ण,
	अणु0x001c, 0x46पूर्ण,
	अणु0x0300, 0x80पूर्ण,
	अणु0x001a, 0x04पूर्ण,
	अणु0x0110, 0x00पूर्ण,
	अणु0x0111, 0x00पूर्ण,
	अणु0x0112, 0x00पूर्ण,
	अणु0x0113, 0x00पूर्ण,

	अणु0xffff, 0xffपूर्ण,
पूर्ण;


अटल पूर्णांक stk_initialise(काष्ठा stk_camera *dev)
अणु
	काष्ठा regval *rv;
	पूर्णांक ret;
	अगर (!is_present(dev))
		वापस -ENODEV;
	अगर (is_initialised(dev))
		वापस 0;
	rv = stk1125_initvals;
	जबतक (rv->reg != 0xffff) अणु
		ret = stk_camera_ग_लिखो_reg(dev, rv->reg, rv->val);
		अगर (ret)
			वापस ret;
		rv++;
	पूर्ण
	अगर (stk_sensor_init(dev) == 0) अणु
		set_initialised(dev);
		वापस 0;
	पूर्ण अन्यथा
		वापस -1;
पूर्ण

/* *********************************************** */
/*
 * This function is called as an URB transfert is complete (Isochronous pipe).
 * So, the traitement is करोne in पूर्णांकerrupt समय, so it has be fast, not crash,
 * and not stall. Neat.
 */
अटल व्योम stk_isoc_handler(काष्ठा urb *urb)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	पूर्णांक framelen;
	अचिन्हित दीर्घ flags;

	अचिन्हित अक्षर *fill = शून्य;
	अचिन्हित अक्षर *iso_buf = शून्य;

	काष्ठा stk_camera *dev;
	काष्ठा stk_sio_buffer *fb;

	dev = (काष्ठा stk_camera *) urb->context;

	अगर (dev == शून्य) अणु
		pr_err("isoc_handler called with NULL device !\n");
		वापस;
	पूर्ण

	अगर (urb->status == -ENOENT || urb->status == -ECONNRESET
		|| urb->status == -ESHUTDOWN) अणु
		atomic_dec(&dev->urbs_used);
		वापस;
	पूर्ण

	spin_lock_irqsave(&dev->spinlock, flags);

	अगर (urb->status != -EINPROGRESS && urb->status != 0) अणु
		pr_err("isoc_handler: urb->status == %d\n", urb->status);
		जाओ resubmit;
	पूर्ण

	अगर (list_empty(&dev->sio_avail)) अणु
		/*FIXME Stop streaming after a जबतक */
		pr_err_ratelimited("isoc_handler without available buffer!\n");
		जाओ resubmit;
	पूर्ण
	fb = list_first_entry(&dev->sio_avail,
			काष्ठा stk_sio_buffer, list);
	fill = fb->buffer + fb->v4lbuf.bytesused;

	क्रम (i = 0; i < urb->number_of_packets; i++) अणु
		अगर (urb->iso_frame_desc[i].status != 0) अणु
			अगर (urb->iso_frame_desc[i].status != -EXDEV)
				pr_err("Frame %d has error %d\n",
				       i, urb->iso_frame_desc[i].status);
			जारी;
		पूर्ण
		framelen = urb->iso_frame_desc[i].actual_length;
		iso_buf = urb->transfer_buffer + urb->iso_frame_desc[i].offset;

		अगर (framelen <= 4)
			जारी; /* no data */

		/*
		 * we found something inक्रमmational from there
		 * the isoc frames have to type of headers
		 * type1: 00 xx 00 00 or 20 xx 00 00
		 * type2: 80 xx 00 00 00 00 00 00 or a0 xx 00 00 00 00 00 00
		 * xx is a sequencer which has never been seen over 0x3f
		 * imho data written करोwn looks like bayer, i see similarities
		 * after every 640 bytes
		 */
		अगर (*iso_buf & 0x80) अणु
			framelen -= 8;
			iso_buf += 8;
			/* This marks a new frame */
			अगर (fb->v4lbuf.bytesused != 0
				&& fb->v4lbuf.bytesused != dev->frame_size) अणु
				pr_err_ratelimited("frame %d, bytesused=%d, skipping\n",
						   i, fb->v4lbuf.bytesused);
				fb->v4lbuf.bytesused = 0;
				fill = fb->buffer;
			पूर्ण अन्यथा अगर (fb->v4lbuf.bytesused == dev->frame_size) अणु
				अगर (list_is_singular(&dev->sio_avail)) अणु
					/* Always reuse the last buffer */
					fb->v4lbuf.bytesused = 0;
					fill = fb->buffer;
				पूर्ण अन्यथा अणु
					list_move_tail(dev->sio_avail.next,
						&dev->sio_full);
					wake_up(&dev->रुको_frame);
					fb = list_first_entry(&dev->sio_avail,
						काष्ठा stk_sio_buffer, list);
					fb->v4lbuf.bytesused = 0;
					fill = fb->buffer;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			framelen -= 4;
			iso_buf += 4;
		पूर्ण

		/* Our buffer is full !!! */
		अगर (framelen + fb->v4lbuf.bytesused > dev->frame_size) अणु
			pr_err_ratelimited("Frame buffer overflow, lost sync\n");
			/*FIXME Do something here? */
			जारी;
		पूर्ण
		spin_unlock_irqrestore(&dev->spinlock, flags);
		स_नकल(fill, iso_buf, framelen);
		spin_lock_irqsave(&dev->spinlock, flags);
		fill += framelen;

		/* New size of our buffer */
		fb->v4lbuf.bytesused += framelen;
	पूर्ण

resubmit:
	spin_unlock_irqrestore(&dev->spinlock, flags);
	urb->dev = dev->udev;
	ret = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (ret != 0) अणु
		pr_err("Error (%d) re-submitting urb in stk_isoc_handler\n",
		       ret);
	पूर्ण
पूर्ण

/* -------------------------------------------- */

अटल पूर्णांक stk_prepare_iso(काष्ठा stk_camera *dev)
अणु
	व्योम *kbuf;
	पूर्णांक i, j;
	काष्ठा urb *urb;
	काष्ठा usb_device *udev;

	अगर (dev == शून्य)
		वापस -ENXIO;
	udev = dev->udev;

	अगर (dev->isobufs)
		pr_err("isobufs already allocated. Bad\n");
	अन्यथा
		dev->isobufs = kसुस्मृति(MAX_ISO_BUFS, माप(*dev->isobufs),
				       GFP_KERNEL);
	अगर (dev->isobufs == शून्य) अणु
		pr_err("Unable to allocate iso buffers\n");
		वापस -ENOMEM;
	पूर्ण
	क्रम (i = 0; i < MAX_ISO_BUFS; i++) अणु
		अगर (dev->isobufs[i].data == शून्य) अणु
			kbuf = kzalloc(ISO_BUFFER_SIZE, GFP_KERNEL);
			अगर (kbuf == शून्य) अणु
				pr_err("Failed to allocate iso buffer %d\n", i);
				जाओ isobufs_out;
			पूर्ण
			dev->isobufs[i].data = kbuf;
		पूर्ण अन्यथा
			pr_err("isobuf data already allocated\n");
		अगर (dev->isobufs[i].urb == शून्य) अणु
			urb = usb_alloc_urb(ISO_FRAMES_PER_DESC, GFP_KERNEL);
			अगर (urb == शून्य)
				जाओ isobufs_out;
			dev->isobufs[i].urb = urb;
		पूर्ण अन्यथा अणु
			pr_err("Killing URB\n");
			usb_समाप्त_urb(dev->isobufs[i].urb);
			urb = dev->isobufs[i].urb;
		पूर्ण
		urb->पूर्णांकerval = 1;
		urb->dev = udev;
		urb->pipe = usb_rcvisocpipe(udev, dev->isoc_ep);
		urb->transfer_flags = URB_ISO_ASAP;
		urb->transfer_buffer = dev->isobufs[i].data;
		urb->transfer_buffer_length = ISO_BUFFER_SIZE;
		urb->complete = stk_isoc_handler;
		urb->context = dev;
		urb->start_frame = 0;
		urb->number_of_packets = ISO_FRAMES_PER_DESC;

		क्रम (j = 0; j < ISO_FRAMES_PER_DESC; j++) अणु
			urb->iso_frame_desc[j].offset = j * ISO_MAX_FRAME_SIZE;
			urb->iso_frame_desc[j].length = ISO_MAX_FRAME_SIZE;
		पूर्ण
	पूर्ण
	set_meदो_स्मृतिd(dev);
	वापस 0;

isobufs_out:
	क्रम (i = 0; i < MAX_ISO_BUFS && dev->isobufs[i].data; i++)
		kमुक्त(dev->isobufs[i].data);
	क्रम (i = 0; i < MAX_ISO_BUFS && dev->isobufs[i].urb; i++)
		usb_मुक्त_urb(dev->isobufs[i].urb);
	kमुक्त(dev->isobufs);
	dev->isobufs = शून्य;
	वापस -ENOMEM;
पूर्ण

अटल व्योम stk_clean_iso(काष्ठा stk_camera *dev)
अणु
	पूर्णांक i;

	अगर (dev == शून्य || dev->isobufs == शून्य)
		वापस;

	क्रम (i = 0; i < MAX_ISO_BUFS; i++) अणु
		काष्ठा urb *urb;

		urb = dev->isobufs[i].urb;
		अगर (urb) अणु
			अगर (atomic_पढ़ो(&dev->urbs_used) && is_present(dev))
				usb_समाप्त_urb(urb);
			usb_मुक्त_urb(urb);
		पूर्ण
		kमुक्त(dev->isobufs[i].data);
	पूर्ण
	kमुक्त(dev->isobufs);
	dev->isobufs = शून्य;
	unset_meदो_स्मृतिd(dev);
पूर्ण

अटल पूर्णांक stk_setup_siobuf(काष्ठा stk_camera *dev, पूर्णांक index)
अणु
	काष्ठा stk_sio_buffer *buf = dev->sio_bufs + index;
	INIT_LIST_HEAD(&buf->list);
	buf->v4lbuf.length = PAGE_ALIGN(dev->frame_size);
	buf->buffer = vदो_स्मृति_user(buf->v4lbuf.length);
	अगर (buf->buffer == शून्य)
		वापस -ENOMEM;
	buf->mapcount = 0;
	buf->dev = dev;
	buf->v4lbuf.index = index;
	buf->v4lbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	buf->v4lbuf.flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	buf->v4lbuf.field = V4L2_FIELD_NONE;
	buf->v4lbuf.memory = V4L2_MEMORY_MMAP;
	buf->v4lbuf.m.offset = 2*index*buf->v4lbuf.length;
	वापस 0;
पूर्ण

अटल पूर्णांक stk_मुक्त_sio_buffers(काष्ठा stk_camera *dev)
अणु
	पूर्णांक i;
	पूर्णांक nbufs;
	अचिन्हित दीर्घ flags;
	अगर (dev->n_sbufs == 0 || dev->sio_bufs == शून्य)
		वापस 0;
	/*
	* If any buffers are mapped, we cannot मुक्त them at all.
	*/
	क्रम (i = 0; i < dev->n_sbufs; i++) अणु
		अगर (dev->sio_bufs[i].mapcount > 0)
			वापस -EBUSY;
	पूर्ण
	/*
	* OK, let's करो it.
	*/
	spin_lock_irqsave(&dev->spinlock, flags);
	INIT_LIST_HEAD(&dev->sio_avail);
	INIT_LIST_HEAD(&dev->sio_full);
	nbufs = dev->n_sbufs;
	dev->n_sbufs = 0;
	spin_unlock_irqrestore(&dev->spinlock, flags);
	क्रम (i = 0; i < nbufs; i++)
		vमुक्त(dev->sio_bufs[i].buffer);
	kमुक्त(dev->sio_bufs);
	dev->sio_bufs = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक stk_prepare_sio_buffers(काष्ठा stk_camera *dev, अचिन्हित n_sbufs)
अणु
	पूर्णांक i;
	अगर (dev->sio_bufs != शून्य)
		pr_err("sio_bufs already allocated\n");
	अन्यथा अणु
		dev->sio_bufs = kसुस्मृति(n_sbufs,
					माप(काष्ठा stk_sio_buffer),
					GFP_KERNEL);
		अगर (dev->sio_bufs == शून्य)
			वापस -ENOMEM;
		क्रम (i = 0; i < n_sbufs; i++) अणु
			अगर (stk_setup_siobuf(dev, i))
				वापस (dev->n_sbufs > 1 ? 0 : -ENOMEM);
			dev->n_sbufs = i+1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक stk_allocate_buffers(काष्ठा stk_camera *dev, अचिन्हित n_sbufs)
अणु
	पूर्णांक err;
	err = stk_prepare_iso(dev);
	अगर (err) अणु
		stk_clean_iso(dev);
		वापस err;
	पूर्ण
	err = stk_prepare_sio_buffers(dev, n_sbufs);
	अगर (err) अणु
		stk_मुक्त_sio_buffers(dev);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम stk_मुक्त_buffers(काष्ठा stk_camera *dev)
अणु
	stk_clean_iso(dev);
	stk_मुक्त_sio_buffers(dev);
पूर्ण
/* -------------------------------------------- */

/* v4l file operations */

अटल पूर्णांक v4l_stk_खोलो(काष्ठा file *fp)
अणु
	काष्ठा stk_camera *dev = video_drvdata(fp);
	पूर्णांक err;

	अगर (dev == शून्य || !is_present(dev))
		वापस -ENXIO;

	अगर (mutex_lock_पूर्णांकerruptible(&dev->lock))
		वापस -ERESTARTSYS;
	अगर (!dev->first_init)
		stk_camera_ग_लिखो_reg(dev, 0x0, 0x24);
	अन्यथा
		dev->first_init = 0;

	err = v4l2_fh_खोलो(fp);
	अगर (!err)
		usb_स्वतःpm_get_पूर्णांकerface(dev->पूर्णांकerface);
	mutex_unlock(&dev->lock);
	वापस err;
पूर्ण

अटल पूर्णांक v4l_stk_release(काष्ठा file *fp)
अणु
	काष्ठा stk_camera *dev = video_drvdata(fp);

	mutex_lock(&dev->lock);
	अगर (dev->owner == fp) अणु
		stk_stop_stream(dev);
		stk_मुक्त_buffers(dev);
		stk_camera_ग_लिखो_reg(dev, 0x0, 0x49); /* turn off the LED */
		unset_initialised(dev);
		dev->owner = शून्य;
	पूर्ण

	usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकerface);
	mutex_unlock(&dev->lock);
	वापस v4l2_fh_release(fp);
पूर्ण

अटल sमाप_प्रकार stk_पढ़ो(काष्ठा file *fp, अक्षर __user *buf,
		माप_प्रकार count, loff_t *f_pos)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	काष्ठा stk_sio_buffer *sbuf;
	काष्ठा stk_camera *dev = video_drvdata(fp);

	अगर (!is_present(dev))
		वापस -EIO;
	अगर (dev->owner && (!dev->पढ़ोing || dev->owner != fp))
		वापस -EBUSY;
	dev->owner = fp;
	अगर (!is_streaming(dev)) अणु
		अगर (stk_initialise(dev)
			|| stk_allocate_buffers(dev, 3)
			|| stk_start_stream(dev))
			वापस -ENOMEM;
		dev->पढ़ोing = 1;
		spin_lock_irqsave(&dev->spinlock, flags);
		क्रम (i = 0; i < dev->n_sbufs; i++) अणु
			list_add_tail(&dev->sio_bufs[i].list, &dev->sio_avail);
			dev->sio_bufs[i].v4lbuf.flags = V4L2_BUF_FLAG_QUEUED;
		पूर्ण
		spin_unlock_irqrestore(&dev->spinlock, flags);
	पूर्ण
	अगर (*f_pos == 0) अणु
		अगर (fp->f_flags & O_NONBLOCK && list_empty(&dev->sio_full))
			वापस -EWOULDBLOCK;
		ret = रुको_event_पूर्णांकerruptible(dev->रुको_frame,
			!list_empty(&dev->sio_full) || !is_present(dev));
		अगर (ret)
			वापस ret;
		अगर (!is_present(dev))
			वापस -EIO;
	पूर्ण
	अगर (count + *f_pos > dev->frame_size)
		count = dev->frame_size - *f_pos;
	spin_lock_irqsave(&dev->spinlock, flags);
	अगर (list_empty(&dev->sio_full)) अणु
		spin_unlock_irqrestore(&dev->spinlock, flags);
		pr_err("BUG: No siobufs ready\n");
		वापस 0;
	पूर्ण
	sbuf = list_first_entry(&dev->sio_full, काष्ठा stk_sio_buffer, list);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	अगर (copy_to_user(buf, sbuf->buffer + *f_pos, count))
		वापस -EFAULT;

	*f_pos += count;

	अगर (*f_pos >= dev->frame_size) अणु
		*f_pos = 0;
		spin_lock_irqsave(&dev->spinlock, flags);
		list_move_tail(&sbuf->list, &dev->sio_avail);
		spin_unlock_irqrestore(&dev->spinlock, flags);
	पूर्ण
	वापस count;
पूर्ण

अटल sमाप_प्रकार v4l_stk_पढ़ो(काष्ठा file *fp, अक्षर __user *buf,
		माप_प्रकार count, loff_t *f_pos)
अणु
	काष्ठा stk_camera *dev = video_drvdata(fp);
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&dev->lock))
		वापस -ERESTARTSYS;
	ret = stk_पढ़ो(fp, buf, count, f_pos);
	mutex_unlock(&dev->lock);
	वापस ret;
पूर्ण

अटल __poll_t v4l_stk_poll(काष्ठा file *fp, poll_table *रुको)
अणु
	काष्ठा stk_camera *dev = video_drvdata(fp);
	__poll_t res = v4l2_ctrl_poll(fp, रुको);

	poll_रुको(fp, &dev->रुको_frame, रुको);

	अगर (!is_present(dev))
		वापस EPOLLERR;

	अगर (!list_empty(&dev->sio_full))
		वापस res | EPOLLIN | EPOLLRDNORM;

	वापस res;
पूर्ण


अटल व्योम stk_v4l_vm_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा stk_sio_buffer *sbuf = vma->vm_निजी_data;
	sbuf->mapcount++;
पूर्ण
अटल व्योम stk_v4l_vm_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा stk_sio_buffer *sbuf = vma->vm_निजी_data;
	sbuf->mapcount--;
	अगर (sbuf->mapcount == 0)
		sbuf->v4lbuf.flags &= ~V4L2_BUF_FLAG_MAPPED;
पूर्ण
अटल स्थिर काष्ठा vm_operations_काष्ठा stk_v4l_vm_ops = अणु
	.खोलो = stk_v4l_vm_खोलो,
	.बंद = stk_v4l_vm_बंद
पूर्ण;

अटल पूर्णांक v4l_stk_mmap(काष्ठा file *fp, काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;
	अचिन्हित दीर्घ offset = vma->vm_pgoff << PAGE_SHIFT;
	काष्ठा stk_camera *dev = video_drvdata(fp);
	काष्ठा stk_sio_buffer *sbuf = शून्य;

	अगर (!(vma->vm_flags & VM_WRITE) || !(vma->vm_flags & VM_SHARED))
		वापस -EINVAL;

	क्रम (i = 0; i < dev->n_sbufs; i++) अणु
		अगर (dev->sio_bufs[i].v4lbuf.m.offset == offset) अणु
			sbuf = dev->sio_bufs + i;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (sbuf == शून्य)
		वापस -EINVAL;
	ret = remap_vदो_स्मृति_range(vma, sbuf->buffer, 0);
	अगर (ret)
		वापस ret;
	vma->vm_flags |= VM_DONTEXPAND;
	vma->vm_निजी_data = sbuf;
	vma->vm_ops = &stk_v4l_vm_ops;
	sbuf->v4lbuf.flags |= V4L2_BUF_FLAG_MAPPED;
	stk_v4l_vm_खोलो(vma);
	वापस 0;
पूर्ण

/* v4l ioctl handlers */

अटल पूर्णांक stk_vidioc_querycap(काष्ठा file *filp,
		व्योम *priv, काष्ठा v4l2_capability *cap)
अणु
	काष्ठा stk_camera *dev = video_drvdata(filp);

	strscpy(cap->driver, "stk", माप(cap->driver));
	strscpy(cap->card, "stk", माप(cap->card));
	usb_make_path(dev->udev, cap->bus_info, माप(cap->bus_info));
	वापस 0;
पूर्ण

अटल पूर्णांक stk_vidioc_क्रमागत_input(काष्ठा file *filp,
		व्योम *priv, काष्ठा v4l2_input *input)
अणु
	अगर (input->index != 0)
		वापस -EINVAL;

	strscpy(input->name, "Syntek USB Camera", माप(input->name));
	input->type = V4L2_INPUT_TYPE_CAMERA;
	वापस 0;
पूर्ण


अटल पूर्णांक stk_vidioc_g_input(काष्ठा file *filp, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	*i = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक stk_vidioc_s_input(काष्ठा file *filp, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	वापस i ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक stk_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा stk_camera *dev =
		container_of(ctrl->handler, काष्ठा stk_camera, hdl);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		वापस stk_sensor_set_brightness(dev, ctrl->val);
	हाल V4L2_CID_HFLIP:
		अगर (dmi_check_प्रणाली(stk_upside_करोwn_dmi_table))
			dev->vsettings.hflip = !ctrl->val;
		अन्यथा
			dev->vsettings.hflip = ctrl->val;
		वापस 0;
	हाल V4L2_CID_VFLIP:
		अगर (dmi_check_प्रणाली(stk_upside_करोwn_dmi_table))
			dev->vsettings.vflip = !ctrl->val;
		अन्यथा
			dev->vsettings.vflip = ctrl->val;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक stk_vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *filp,
		व्योम *priv, काष्ठा v4l2_fmtdesc *fmtd)
अणु
	चयन (fmtd->index) अणु
	हाल 0:
		fmtd->pixelक्रमmat = V4L2_PIX_FMT_RGB565;
		अवरोध;
	हाल 1:
		fmtd->pixelक्रमmat = V4L2_PIX_FMT_RGB565X;
		अवरोध;
	हाल 2:
		fmtd->pixelक्रमmat = V4L2_PIX_FMT_UYVY;
		अवरोध;
	हाल 3:
		fmtd->pixelक्रमmat = V4L2_PIX_FMT_SBGGR8;
		अवरोध;
	हाल 4:
		fmtd->pixelक्रमmat = V4L2_PIX_FMT_YUYV;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा stk_size अणु
	अचिन्हित w;
	अचिन्हित h;
	क्रमागत stk_mode m;
पूर्ण stk_sizes[] = अणु
	अणु .w = 1280, .h = 1024, .m = MODE_SXGA, पूर्ण,
	अणु .w = 640,  .h = 480,  .m = MODE_VGA,  पूर्ण,
	अणु .w = 352,  .h = 288,  .m = MODE_CIF,  पूर्ण,
	अणु .w = 320,  .h = 240,  .m = MODE_QVGA, पूर्ण,
	अणु .w = 176,  .h = 144,  .m = MODE_QCIF, पूर्ण,
पूर्ण;

अटल पूर्णांक stk_vidioc_g_fmt_vid_cap(काष्ठा file *filp,
		व्योम *priv, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा v4l2_pix_क्रमmat *pix_क्रमmat = &f->fmt.pix;
	काष्ठा stk_camera *dev = video_drvdata(filp);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(stk_sizes) &&
			stk_sizes[i].m != dev->vsettings.mode; i++)
		;
	अगर (i == ARRAY_SIZE(stk_sizes)) अणु
		pr_err("ERROR: mode invalid\n");
		वापस -EINVAL;
	पूर्ण
	pix_क्रमmat->width = stk_sizes[i].w;
	pix_क्रमmat->height = stk_sizes[i].h;
	pix_क्रमmat->field = V4L2_FIELD_NONE;
	pix_क्रमmat->colorspace = V4L2_COLORSPACE_SRGB;
	pix_क्रमmat->pixelक्रमmat = dev->vsettings.palette;
	अगर (dev->vsettings.palette == V4L2_PIX_FMT_SBGGR8)
		pix_क्रमmat->bytesperline = pix_क्रमmat->width;
	अन्यथा
		pix_क्रमmat->bytesperline = 2 * pix_क्रमmat->width;
	pix_क्रमmat->sizeimage = pix_क्रमmat->bytesperline
				* pix_क्रमmat->height;
	वापस 0;
पूर्ण

अटल पूर्णांक stk_try_fmt_vid_cap(काष्ठा file *filp,
		काष्ठा v4l2_क्रमmat *fmtd, पूर्णांक *idx)
अणु
	पूर्णांक i;
	चयन (fmtd->fmt.pix.pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_RGB565:
	हाल V4L2_PIX_FMT_RGB565X:
	हाल V4L2_PIX_FMT_UYVY:
	हाल V4L2_PIX_FMT_YUYV:
	हाल V4L2_PIX_FMT_SBGGR8:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	क्रम (i = 1; i < ARRAY_SIZE(stk_sizes); i++) अणु
		अगर (fmtd->fmt.pix.width > stk_sizes[i].w)
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(stk_sizes)
		|| (असल(fmtd->fmt.pix.width - stk_sizes[i-1].w)
			< असल(fmtd->fmt.pix.width - stk_sizes[i].w))) अणु
		fmtd->fmt.pix.height = stk_sizes[i-1].h;
		fmtd->fmt.pix.width = stk_sizes[i-1].w;
		अगर (idx)
			*idx = i - 1;
	पूर्ण अन्यथा अणु
		fmtd->fmt.pix.height = stk_sizes[i].h;
		fmtd->fmt.pix.width = stk_sizes[i].w;
		अगर (idx)
			*idx = i;
	पूर्ण

	fmtd->fmt.pix.field = V4L2_FIELD_NONE;
	fmtd->fmt.pix.colorspace = V4L2_COLORSPACE_SRGB;
	अगर (fmtd->fmt.pix.pixelक्रमmat == V4L2_PIX_FMT_SBGGR8)
		fmtd->fmt.pix.bytesperline = fmtd->fmt.pix.width;
	अन्यथा
		fmtd->fmt.pix.bytesperline = 2 * fmtd->fmt.pix.width;
	fmtd->fmt.pix.sizeimage = fmtd->fmt.pix.bytesperline
		* fmtd->fmt.pix.height;
	वापस 0;
पूर्ण

अटल पूर्णांक stk_vidioc_try_fmt_vid_cap(काष्ठा file *filp,
		व्योम *priv, काष्ठा v4l2_क्रमmat *fmtd)
अणु
	वापस stk_try_fmt_vid_cap(filp, fmtd, शून्य);
पूर्ण

अटल पूर्णांक stk_setup_क्रमmat(काष्ठा stk_camera *dev)
अणु
	पूर्णांक i = 0;
	पूर्णांक depth;
	अगर (dev->vsettings.palette == V4L2_PIX_FMT_SBGGR8)
		depth = 1;
	अन्यथा
		depth = 2;
	जबतक (i < ARRAY_SIZE(stk_sizes) &&
			stk_sizes[i].m != dev->vsettings.mode)
		i++;
	अगर (i == ARRAY_SIZE(stk_sizes)) अणु
		pr_err("Something is broken in %s\n", __func__);
		वापस -EFAULT;
	पूर्ण
	/* This रेजिस्टरs controls some timings, not sure of what. */
	stk_camera_ग_लिखो_reg(dev, 0x001b, 0x0e);
	अगर (dev->vsettings.mode == MODE_SXGA)
		stk_camera_ग_लिखो_reg(dev, 0x001c, 0x0e);
	अन्यथा
		stk_camera_ग_लिखो_reg(dev, 0x001c, 0x46);
	/*
	 * Registers 0x0115 0x0114 are the size of each line (bytes),
	 * regs 0x0117 0x0116 are the height of the image.
	 */
	stk_camera_ग_लिखो_reg(dev, 0x0115,
		((stk_sizes[i].w * depth) >> 8) & 0xff);
	stk_camera_ग_लिखो_reg(dev, 0x0114,
		(stk_sizes[i].w * depth) & 0xff);
	stk_camera_ग_लिखो_reg(dev, 0x0117,
		(stk_sizes[i].h >> 8) & 0xff);
	stk_camera_ग_लिखो_reg(dev, 0x0116,
		stk_sizes[i].h & 0xff);
	वापस stk_sensor_configure(dev);
पूर्ण

अटल पूर्णांक stk_vidioc_s_fmt_vid_cap(काष्ठा file *filp,
		व्योम *priv, काष्ठा v4l2_क्रमmat *fmtd)
अणु
	पूर्णांक ret;
	पूर्णांक idx;
	काष्ठा stk_camera *dev = video_drvdata(filp);

	अगर (dev == शून्य)
		वापस -ENODEV;
	अगर (!is_present(dev))
		वापस -ENODEV;
	अगर (is_streaming(dev))
		वापस -EBUSY;
	अगर (dev->owner)
		वापस -EBUSY;
	ret = stk_try_fmt_vid_cap(filp, fmtd, &idx);
	अगर (ret)
		वापस ret;

	dev->vsettings.palette = fmtd->fmt.pix.pixelक्रमmat;
	stk_मुक्त_buffers(dev);
	dev->frame_size = fmtd->fmt.pix.sizeimage;
	dev->vsettings.mode = stk_sizes[idx].m;

	stk_initialise(dev);
	वापस stk_setup_क्रमmat(dev);
पूर्ण

अटल पूर्णांक stk_vidioc_reqbufs(काष्ठा file *filp,
		व्योम *priv, काष्ठा v4l2_requestbuffers *rb)
अणु
	काष्ठा stk_camera *dev = video_drvdata(filp);

	अगर (dev == शून्य)
		वापस -ENODEV;
	अगर (rb->memory != V4L2_MEMORY_MMAP)
		वापस -EINVAL;
	अगर (is_streaming(dev)
		|| (dev->owner && dev->owner != filp))
		वापस -EBUSY;
	stk_मुक्त_buffers(dev);
	अगर (rb->count == 0) अणु
		stk_camera_ग_लिखो_reg(dev, 0x0, 0x49); /* turn off the LED */
		unset_initialised(dev);
		dev->owner = शून्य;
		वापस 0;
	पूर्ण
	dev->owner = filp;

	/*FIXME If they ask क्रम zero, we must stop streaming and मुक्त */
	अगर (rb->count < 3)
		rb->count = 3;
	/* Arbitrary limit */
	अन्यथा अगर (rb->count > 5)
		rb->count = 5;

	stk_allocate_buffers(dev, rb->count);
	rb->count = dev->n_sbufs;
	वापस 0;
पूर्ण

अटल पूर्णांक stk_vidioc_querybuf(काष्ठा file *filp,
		व्योम *priv, काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा stk_camera *dev = video_drvdata(filp);
	काष्ठा stk_sio_buffer *sbuf;

	अगर (buf->index >= dev->n_sbufs)
		वापस -EINVAL;
	sbuf = dev->sio_bufs + buf->index;
	*buf = sbuf->v4lbuf;
	वापस 0;
पूर्ण

अटल पूर्णांक stk_vidioc_qbuf(काष्ठा file *filp,
		व्योम *priv, काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा stk_camera *dev = video_drvdata(filp);
	काष्ठा stk_sio_buffer *sbuf;
	अचिन्हित दीर्घ flags;

	अगर (buf->memory != V4L2_MEMORY_MMAP)
		वापस -EINVAL;

	अगर (buf->index >= dev->n_sbufs)
		वापस -EINVAL;
	sbuf = dev->sio_bufs + buf->index;
	अगर (sbuf->v4lbuf.flags & V4L2_BUF_FLAG_QUEUED)
		वापस 0;
	sbuf->v4lbuf.flags |= V4L2_BUF_FLAG_QUEUED;
	sbuf->v4lbuf.flags &= ~V4L2_BUF_FLAG_DONE;
	spin_lock_irqsave(&dev->spinlock, flags);
	list_add_tail(&sbuf->list, &dev->sio_avail);
	*buf = sbuf->v4lbuf;
	spin_unlock_irqrestore(&dev->spinlock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक stk_vidioc_dqbuf(काष्ठा file *filp,
		व्योम *priv, काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा stk_camera *dev = video_drvdata(filp);
	काष्ठा stk_sio_buffer *sbuf;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!is_streaming(dev))
		वापस -EINVAL;

	अगर (filp->f_flags & O_NONBLOCK && list_empty(&dev->sio_full))
		वापस -EWOULDBLOCK;
	ret = रुको_event_पूर्णांकerruptible(dev->रुको_frame,
		!list_empty(&dev->sio_full) || !is_present(dev));
	अगर (ret)
		वापस ret;
	अगर (!is_present(dev))
		वापस -EIO;

	spin_lock_irqsave(&dev->spinlock, flags);
	sbuf = list_first_entry(&dev->sio_full, काष्ठा stk_sio_buffer, list);
	list_del_init(&sbuf->list);
	spin_unlock_irqrestore(&dev->spinlock, flags);
	sbuf->v4lbuf.flags &= ~V4L2_BUF_FLAG_QUEUED;
	sbuf->v4lbuf.flags |= V4L2_BUF_FLAG_DONE;
	sbuf->v4lbuf.sequence = ++dev->sequence;
	v4l2_buffer_set_बारtamp(&sbuf->v4lbuf, kसमय_get_ns());

	*buf = sbuf->v4lbuf;
	वापस 0;
पूर्ण

अटल पूर्णांक stk_vidioc_streamon(काष्ठा file *filp,
		व्योम *priv, क्रमागत v4l2_buf_type type)
अणु
	काष्ठा stk_camera *dev = video_drvdata(filp);
	अगर (is_streaming(dev))
		वापस 0;
	अगर (dev->sio_bufs == शून्य)
		वापस -EINVAL;
	dev->sequence = 0;
	वापस stk_start_stream(dev);
पूर्ण

अटल पूर्णांक stk_vidioc_streamoff(काष्ठा file *filp,
		व्योम *priv, क्रमागत v4l2_buf_type type)
अणु
	काष्ठा stk_camera *dev = video_drvdata(filp);
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	stk_stop_stream(dev);
	spin_lock_irqsave(&dev->spinlock, flags);
	INIT_LIST_HEAD(&dev->sio_avail);
	INIT_LIST_HEAD(&dev->sio_full);
	क्रम (i = 0; i < dev->n_sbufs; i++) अणु
		INIT_LIST_HEAD(&dev->sio_bufs[i].list);
		dev->sio_bufs[i].v4lbuf.flags = 0;
	पूर्ण
	spin_unlock_irqrestore(&dev->spinlock, flags);
	वापस 0;
पूर्ण


अटल पूर्णांक stk_vidioc_g_parm(काष्ठा file *filp,
		व्योम *priv, काष्ठा v4l2_streamparm *sp)
अणु
	/*FIXME This is not correct */
	sp->parm.capture.समयperframe.numerator = 1;
	sp->parm.capture.समयperframe.denominator = 30;
	sp->parm.capture.पढ़ोbuffers = 2;
	वापस 0;
पूर्ण

अटल पूर्णांक stk_vidioc_क्रमागत_framesizes(काष्ठा file *filp,
		व्योम *priv, काष्ठा v4l2_frmsizeक्रमागत *frms)
अणु
	अगर (frms->index >= ARRAY_SIZE(stk_sizes))
		वापस -EINVAL;
	चयन (frms->pixel_क्रमmat) अणु
	हाल V4L2_PIX_FMT_RGB565:
	हाल V4L2_PIX_FMT_RGB565X:
	हाल V4L2_PIX_FMT_UYVY:
	हाल V4L2_PIX_FMT_YUYV:
	हाल V4L2_PIX_FMT_SBGGR8:
		frms->type = V4L2_FRMSIZE_TYPE_DISCRETE;
		frms->discrete.width = stk_sizes[frms->index].w;
		frms->discrete.height = stk_sizes[frms->index].h;
		वापस 0;
	शेष: वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops stk_ctrl_ops = अणु
	.s_ctrl = stk_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations v4l_stk_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = v4l_stk_खोलो,
	.release = v4l_stk_release,
	.पढ़ो = v4l_stk_पढ़ो,
	.poll = v4l_stk_poll,
	.mmap = v4l_stk_mmap,
	.unlocked_ioctl = video_ioctl2,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops v4l_stk_ioctl_ops = अणु
	.vidioc_querycap = stk_vidioc_querycap,
	.vidioc_क्रमागत_fmt_vid_cap = stk_vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap = stk_vidioc_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap = stk_vidioc_s_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap = stk_vidioc_g_fmt_vid_cap,
	.vidioc_क्रमागत_input = stk_vidioc_क्रमागत_input,
	.vidioc_s_input = stk_vidioc_s_input,
	.vidioc_g_input = stk_vidioc_g_input,
	.vidioc_reqbufs = stk_vidioc_reqbufs,
	.vidioc_querybuf = stk_vidioc_querybuf,
	.vidioc_qbuf = stk_vidioc_qbuf,
	.vidioc_dqbuf = stk_vidioc_dqbuf,
	.vidioc_streamon = stk_vidioc_streamon,
	.vidioc_streamoff = stk_vidioc_streamoff,
	.vidioc_g_parm = stk_vidioc_g_parm,
	.vidioc_क्रमागत_framesizes = stk_vidioc_क्रमागत_framesizes,
	.vidioc_log_status = v4l2_ctrl_log_status,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल व्योम stk_v4l_dev_release(काष्ठा video_device *vd)
अणु
	काष्ठा stk_camera *dev = vdev_to_camera(vd);

	अगर (dev->sio_bufs != शून्य || dev->isobufs != शून्य)
		pr_err("We are leaking memory\n");
	usb_put_पूर्णांकf(dev->पूर्णांकerface);
पूर्ण

अटल स्थिर काष्ठा video_device stk_v4l_data = अणु
	.name = "stkwebcam",
	.fops = &v4l_stk_fops,
	.ioctl_ops = &v4l_stk_ioctl_ops,
	.release = stk_v4l_dev_release,
पूर्ण;


अटल पूर्णांक stk_रेजिस्टर_video_device(काष्ठा stk_camera *dev)
अणु
	पूर्णांक err;

	dev->vdev = stk_v4l_data;
	dev->vdev.lock = &dev->lock;
	dev->vdev.v4l2_dev = &dev->v4l2_dev;
	dev->vdev.device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_READWRITE |
				V4L2_CAP_STREAMING;
	video_set_drvdata(&dev->vdev, dev);
	err = video_रेजिस्टर_device(&dev->vdev, VFL_TYPE_VIDEO, -1);
	अगर (err)
		pr_err("v4l registration failed\n");
	अन्यथा
		pr_info("Syntek USB2.0 Camera is now controlling device %s\n",
			video_device_node_name(&dev->vdev));
	वापस err;
पूर्ण


/* USB Stuff */

अटल पूर्णांक stk_camera_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
		स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा v4l2_ctrl_handler *hdl;
	पूर्णांक err = 0;
	पूर्णांक i;

	काष्ठा stk_camera *dev = शून्य;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;

	dev = kzalloc(माप(काष्ठा stk_camera), GFP_KERNEL);
	अगर (dev == शून्य) अणु
		pr_err("Out of memory !\n");
		वापस -ENOMEM;
	पूर्ण
	err = v4l2_device_रेजिस्टर(&पूर्णांकerface->dev, &dev->v4l2_dev);
	अगर (err < 0) अणु
		dev_err(&udev->dev, "couldn't register v4l2_device\n");
		kमुक्त(dev);
		वापस err;
	पूर्ण
	hdl = &dev->hdl;
	v4l2_ctrl_handler_init(hdl, 3);
	v4l2_ctrl_new_std(hdl, &stk_ctrl_ops,
			  V4L2_CID_BRIGHTNESS, 0, 0xff, 0x1, 0x60);
	v4l2_ctrl_new_std(hdl, &stk_ctrl_ops,
			  V4L2_CID_HFLIP, 0, 1, 1, 1);
	v4l2_ctrl_new_std(hdl, &stk_ctrl_ops,
			  V4L2_CID_VFLIP, 0, 1, 1, 1);
	अगर (hdl->error) अणु
		err = hdl->error;
		dev_err(&udev->dev, "couldn't register control\n");
		जाओ error;
	पूर्ण
	dev->v4l2_dev.ctrl_handler = hdl;

	spin_lock_init(&dev->spinlock);
	mutex_init(&dev->lock);
	init_रुकोqueue_head(&dev->रुको_frame);
	dev->first_init = 1; /* webcam LED management */

	dev->udev = udev;
	dev->पूर्णांकerface = पूर्णांकerface;
	usb_get_पूर्णांकf(पूर्णांकerface);

	अगर (hflip != -1)
		dev->vsettings.hflip = hflip;
	अन्यथा अगर (dmi_check_प्रणाली(stk_upside_करोwn_dmi_table))
		dev->vsettings.hflip = 1;
	अन्यथा
		dev->vsettings.hflip = 0;
	अगर (vflip != -1)
		dev->vsettings.vflip = vflip;
	अन्यथा अगर (dmi_check_प्रणाली(stk_upside_करोwn_dmi_table))
		dev->vsettings.vflip = 1;
	अन्यथा
		dev->vsettings.vflip = 0;
	dev->n_sbufs = 0;
	set_present(dev);

	/* Set up the endpoपूर्णांक inक्रमmation
	 * use only the first isoc-in endpoपूर्णांक
	 * क्रम the current alternate setting */
	अगरace_desc = पूर्णांकerface->cur_altsetting;

	क्रम (i = 0; i < अगरace_desc->desc.bNumEndpoपूर्णांकs; ++i) अणु
		endpoपूर्णांक = &अगरace_desc->endpoपूर्णांक[i].desc;

		अगर (!dev->isoc_ep
			&& usb_endpoपूर्णांक_is_isoc_in(endpoपूर्णांक)) अणु
			/* we found an isoc in endpoपूर्णांक */
			dev->isoc_ep = usb_endpoपूर्णांक_num(endpoपूर्णांक);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!dev->isoc_ep) अणु
		pr_err("Could not find isoc-in endpoint\n");
		err = -ENODEV;
		जाओ error;
	पूर्ण
	dev->vsettings.palette = V4L2_PIX_FMT_RGB565;
	dev->vsettings.mode = MODE_VGA;
	dev->frame_size = 640 * 480 * 2;

	INIT_LIST_HEAD(&dev->sio_avail);
	INIT_LIST_HEAD(&dev->sio_full);

	usb_set_पूर्णांकfdata(पूर्णांकerface, dev);

	err = stk_रेजिस्टर_video_device(dev);
	अगर (err)
		जाओ error;

	वापस 0;

error:
	v4l2_ctrl_handler_मुक्त(hdl);
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
	kमुक्त(dev);
	वापस err;
पूर्ण

अटल व्योम stk_camera_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा stk_camera *dev = usb_get_पूर्णांकfdata(पूर्णांकerface);

	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);
	unset_present(dev);

	wake_up_पूर्णांकerruptible(&dev->रुको_frame);

	pr_info("Syntek USB2.0 Camera release resources device %s\n",
		video_device_node_name(&dev->vdev));

	video_unरेजिस्टर_device(&dev->vdev);
	v4l2_ctrl_handler_मुक्त(&dev->hdl);
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
	kमुक्त(dev);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक stk_camera_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा stk_camera *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	अगर (is_streaming(dev)) अणु
		stk_stop_stream(dev);
		/* yes, this is ugly */
		set_streaming(dev);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक stk_camera_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा stk_camera *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	अगर (!is_initialised(dev))
		वापस 0;
	unset_initialised(dev);
	stk_initialise(dev);
	stk_camera_ग_लिखो_reg(dev, 0x0, 0x49);
	stk_setup_क्रमmat(dev);
	अगर (is_streaming(dev))
		stk_start_stream(dev);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा usb_driver stk_camera_driver = अणु
	.name = "stkwebcam",
	.probe = stk_camera_probe,
	.disconnect = stk_camera_disconnect,
	.id_table = stkwebcam_table,
#अगर_घोषित CONFIG_PM
	.suspend = stk_camera_suspend,
	.resume = stk_camera_resume,
#पूर्ण_अगर
पूर्ण;

module_usb_driver(stk_camera_driver);
