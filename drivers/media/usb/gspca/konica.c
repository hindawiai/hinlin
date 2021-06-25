<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम USB webcams based on Konica chipset. This
 * chipset is used in Intel YC76 camera.
 *
 * Copyright (C) 2010 Hans de Goede <hdegoede@redhat.com>
 *
 * Based on the usbvideo v4l1 konicawc driver which is:
 *
 * Copyright (C) 2002 Simon Evans <spse@secret.org.uk>
 *
 * The code क्रम making gspca work with a webcam with 2 isoc endpoपूर्णांकs was
 * taken from the benq gspca subdriver which is:
 *
 * Copyright (C) 2009 Jean-Francois Moine (http://moinejf.मुक्त.fr)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा MODULE_NAME "konica"

#समावेश <linux/input.h>
#समावेश "gspca.h"

MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_DESCRIPTION("Konica chipset USB Camera Driver");
MODULE_LICENSE("GPL");

#घोषणा WHITEBAL_REG   0x01
#घोषणा BRIGHTNESS_REG 0x02
#घोषणा SHARPNESS_REG  0x03
#घोषणा CONTRAST_REG   0x04
#घोषणा SATURATION_REG 0x05

/* specअगरic webcam descriptor */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;	/* !! must be the first item */
	काष्ठा urb *last_data_urb;
	u8 snapshot_pressed;
पूर्ण;


/* .priv is what goes to रेजिस्टर 8 क्रम this mode, known working values:
   0x00 -> 176x144, cropped
   0x01 -> 176x144, cropped
   0x02 -> 176x144, cropped
   0x03 -> 176x144, cropped
   0x04 -> 176x144, binned
   0x05 -> 320x240
   0x06 -> 320x240
   0x07 -> 160x120, cropped
   0x08 -> 160x120, cropped
   0x09 -> 160x120, binned (note has 136 lines)
   0x0a -> 160x120, binned (note has 136 lines)
   0x0b -> 160x120, cropped
*/
अटल स्थिर काष्ठा v4l2_pix_क्रमmat vga_mode[] = अणु
	अणु160, 120, V4L2_PIX_FMT_KONICA420, V4L2_FIELD_NONE,
		.bytesperline = 160,
		.sizeimage = 160 * 136 * 3 / 2 + 960,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0x0aपूर्ण,
	अणु176, 144, V4L2_PIX_FMT_KONICA420, V4L2_FIELD_NONE,
		.bytesperline = 176,
		.sizeimage = 176 * 144 * 3 / 2 + 960,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0x04पूर्ण,
	अणु320, 240, V4L2_PIX_FMT_KONICA420, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240 * 3 / 2 + 960,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0x05पूर्ण,
पूर्ण;

अटल व्योम sd_isoc_irq(काष्ठा urb *urb);

अटल व्योम reg_w(काष्ठा gspca_dev *gspca_dev, u16 value, u16 index)
अणु
	काष्ठा usb_device *dev = gspca_dev->dev;
	पूर्णांक ret;

	अगर (gspca_dev->usb_err < 0)
		वापस;
	ret = usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
			0x02,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			value,
			index,
			शून्य,
			0,
			1000);
	अगर (ret < 0) अणु
		pr_err("reg_w err writing %02x to %02x: %d\n",
		       value, index, ret);
		gspca_dev->usb_err = ret;
	पूर्ण
पूर्ण

अटल व्योम reg_r(काष्ठा gspca_dev *gspca_dev, u16 value, u16 index)
अणु
	काष्ठा usb_device *dev = gspca_dev->dev;
	पूर्णांक ret;

	अगर (gspca_dev->usb_err < 0)
		वापस;
	ret = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			0x03,
			USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			value,
			index,
			gspca_dev->usb_buf,
			2,
			1000);
	अगर (ret < 0) अणु
		pr_err("reg_r err %d\n", ret);
		gspca_dev->usb_err = ret;
		/*
		 * Make sure the buffer is zeroed to aव्योम uninitialized
		 * values.
		 */
		स_रखो(gspca_dev->usb_buf, 0, 2);
	पूर्ण
पूर्ण

अटल व्योम konica_stream_on(काष्ठा gspca_dev *gspca_dev)
अणु
	reg_w(gspca_dev, 1, 0x0b);
पूर्ण

अटल व्योम konica_stream_off(काष्ठा gspca_dev *gspca_dev)
अणु
	reg_w(gspca_dev, 0, 0x0b);
पूर्ण

/* this function is called at probe समय */
अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
			स्थिर काष्ठा usb_device_id *id)
अणु
	gspca_dev->cam.cam_mode = vga_mode;
	gspca_dev->cam.nmodes = ARRAY_SIZE(vga_mode);
	gspca_dev->cam.no_urb_create = 1;

	वापस 0;
पूर्ण

/* this function is called at probe and resume समय */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक i;

	/*
	 * The konica needs a freaking large समय to "boot" (approx 6.5 sec.),
	 * and करोes not want to be bothered जबतक करोing so :|
	 * Register 0x10 counts from 1 - 3, with 3 being "ready"
	 */
	msleep(6000);
	क्रम (i = 0; i < 20; i++) अणु
		reg_r(gspca_dev, 0, 0x10);
		अगर (gspca_dev->usb_buf[0] == 3)
			अवरोध;
		msleep(100);
	पूर्ण
	reg_w(gspca_dev, 0, 0x0d);

	वापस gspca_dev->usb_err;
पूर्ण

अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा urb *urb;
	पूर्णांक i, n, packet_size;
	काष्ठा usb_host_पूर्णांकerface *alt;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;

	पूर्णांकf = usb_अगरnum_to_अगर(sd->gspca_dev.dev, sd->gspca_dev.अगरace);
	alt = usb_altnum_to_altsetting(पूर्णांकf, sd->gspca_dev.alt);
	अगर (!alt) अणु
		pr_err("Couldn't get altsetting\n");
		वापस -EIO;
	पूर्ण

	अगर (alt->desc.bNumEndpoपूर्णांकs < 2)
		वापस -ENODEV;

	packet_size = le16_to_cpu(alt->endpoपूर्णांक[0].desc.wMaxPacketSize);

	n = gspca_dev->cam.cam_mode[gspca_dev->curr_mode].priv;
	reg_w(gspca_dev, n, 0x08);

	konica_stream_on(gspca_dev);

	अगर (gspca_dev->usb_err)
		वापस gspca_dev->usb_err;

	/* create 4 URBs - 2 on endpoपूर्णांक 0x83 and 2 on 0x082 */
#अगर MAX_NURBS < 4
#त्रुटि "Not enough URBs in the gspca table"
#पूर्ण_अगर
#घोषणा SD_NPKT 32
	क्रम (n = 0; n < 4; n++) अणु
		i = n & 1 ? 0 : 1;
		packet_size =
			le16_to_cpu(alt->endpoपूर्णांक[i].desc.wMaxPacketSize);
		urb = usb_alloc_urb(SD_NPKT, GFP_KERNEL);
		अगर (!urb)
			वापस -ENOMEM;
		gspca_dev->urb[n] = urb;
		urb->transfer_buffer = usb_alloc_coherent(gspca_dev->dev,
						packet_size * SD_NPKT,
						GFP_KERNEL,
						&urb->transfer_dma);
		अगर (urb->transfer_buffer == शून्य) अणु
			pr_err("usb_buffer_alloc failed\n");
			वापस -ENOMEM;
		पूर्ण

		urb->dev = gspca_dev->dev;
		urb->context = gspca_dev;
		urb->transfer_buffer_length = packet_size * SD_NPKT;
		urb->pipe = usb_rcvisocpipe(gspca_dev->dev,
					n & 1 ? 0x81 : 0x82);
		urb->transfer_flags = URB_ISO_ASAP
					| URB_NO_TRANSFER_DMA_MAP;
		urb->पूर्णांकerval = 1;
		urb->complete = sd_isoc_irq;
		urb->number_of_packets = SD_NPKT;
		क्रम (i = 0; i < SD_NPKT; i++) अणु
			urb->iso_frame_desc[i].length = packet_size;
			urb->iso_frame_desc[i].offset = packet_size * i;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sd_stopN(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd __maybe_unused = (काष्ठा sd *) gspca_dev;

	konica_stream_off(gspca_dev);
#अगर IS_ENABLED(CONFIG_INPUT)
	/* Don't keep the button in the pressed state "forever" अगर it was
	   pressed when streaming is stopped */
	अगर (sd->snapshot_pressed) अणु
		input_report_key(gspca_dev->input_dev, KEY_CAMERA, 0);
		input_sync(gspca_dev->input_dev);
		sd->snapshot_pressed = 0;
	पूर्ण
#पूर्ण_अगर
पूर्ण

/* reception of an URB */
अटल व्योम sd_isoc_irq(काष्ठा urb *urb)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *) urb->context;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा urb *data_urb, *status_urb;
	u8 *data;
	पूर्णांक i, st;

	gspca_dbg(gspca_dev, D_PACK, "sd isoc irq\n");
	अगर (!gspca_dev->streaming)
		वापस;

	अगर (urb->status != 0) अणु
		अगर (urb->status == -ESHUTDOWN)
			वापस;		/* disconnection */
#अगर_घोषित CONFIG_PM
		अगर (gspca_dev->frozen)
			वापस;
#पूर्ण_अगर
		gspca_err(gspca_dev, "urb status: %d\n", urb->status);
		st = usb_submit_urb(urb, GFP_ATOMIC);
		अगर (st < 0)
			pr_err("resubmit urb error %d\n", st);
		वापस;
	पूर्ण

	/* अगर this is a data URB (ep 0x82), रुको */
	अगर (urb->transfer_buffer_length > 32) अणु
		sd->last_data_urb = urb;
		वापस;
	पूर्ण

	status_urb = urb;
	data_urb   = sd->last_data_urb;
	sd->last_data_urb = शून्य;

	अगर (!data_urb || data_urb->start_frame != status_urb->start_frame) अणु
		gspca_err(gspca_dev, "lost sync on frames\n");
		जाओ resubmit;
	पूर्ण

	अगर (data_urb->number_of_packets != status_urb->number_of_packets) अणु
		gspca_err(gspca_dev, "no packets does not match, data: %d, status: %d\n",
			  data_urb->number_of_packets,
			  status_urb->number_of_packets);
		जाओ resubmit;
	पूर्ण

	क्रम (i = 0; i < status_urb->number_of_packets; i++) अणु
		अगर (data_urb->iso_frame_desc[i].status ||
		    status_urb->iso_frame_desc[i].status) अणु
			gspca_err(gspca_dev, "pkt %d data-status %d, status-status %d\n",
				  i,
				  data_urb->iso_frame_desc[i].status,
				  status_urb->iso_frame_desc[i].status);
			gspca_dev->last_packet_type = DISCARD_PACKET;
			जारी;
		पूर्ण

		अगर (status_urb->iso_frame_desc[i].actual_length != 1) अणु
			gspca_err(gspca_dev, "bad status packet length %d\n",
				  status_urb->iso_frame_desc[i].actual_length);
			gspca_dev->last_packet_type = DISCARD_PACKET;
			जारी;
		पूर्ण

		st = *((u8 *)status_urb->transfer_buffer
				+ status_urb->iso_frame_desc[i].offset);

		data = (u8 *)data_urb->transfer_buffer
				+ data_urb->iso_frame_desc[i].offset;

		/* st: 0x80-0xff: frame start with frame number (ie 0-7f)
		 * otherwise:
		 * bit 0 0: keep packet
		 *	 1: drop packet (padding data)
		 *
		 * bit 4 0 button not clicked
		 *       1 button clicked
		 * button is used to `take a picture' (in software)
		 */
		अगर (st & 0x80) अणु
			gspca_frame_add(gspca_dev, LAST_PACKET, शून्य, 0);
			gspca_frame_add(gspca_dev, FIRST_PACKET, शून्य, 0);
		पूर्ण अन्यथा अणु
#अगर IS_ENABLED(CONFIG_INPUT)
			u8 button_state = st & 0x40 ? 1 : 0;
			अगर (sd->snapshot_pressed != button_state) अणु
				input_report_key(gspca_dev->input_dev,
						 KEY_CAMERA,
						 button_state);
				input_sync(gspca_dev->input_dev);
				sd->snapshot_pressed = button_state;
			पूर्ण
#पूर्ण_अगर
			अगर (st & 0x01)
				जारी;
		पूर्ण
		gspca_frame_add(gspca_dev, INTER_PACKET, data,
				data_urb->iso_frame_desc[i].actual_length);
	पूर्ण

resubmit:
	अगर (data_urb) अणु
		st = usb_submit_urb(data_urb, GFP_ATOMIC);
		अगर (st < 0)
			gspca_err(gspca_dev, "usb_submit_urb(data_urb) ret %d\n",
				  st);
	पूर्ण
	st = usb_submit_urb(status_urb, GFP_ATOMIC);
	अगर (st < 0)
		gspca_err(gspca_dev, "usb_submit_urb(status_urb) ret %d\n", st);
पूर्ण

अटल पूर्णांक sd_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);

	gspca_dev->usb_err = 0;

	अगर (!gspca_dev->streaming)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		konica_stream_off(gspca_dev);
		reg_w(gspca_dev, ctrl->val, BRIGHTNESS_REG);
		konica_stream_on(gspca_dev);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		konica_stream_off(gspca_dev);
		reg_w(gspca_dev, ctrl->val, CONTRAST_REG);
		konica_stream_on(gspca_dev);
		अवरोध;
	हाल V4L2_CID_SATURATION:
		konica_stream_off(gspca_dev);
		reg_w(gspca_dev, ctrl->val, SATURATION_REG);
		konica_stream_on(gspca_dev);
		अवरोध;
	हाल V4L2_CID_WHITE_BALANCE_TEMPERATURE:
		konica_stream_off(gspca_dev);
		reg_w(gspca_dev, ctrl->val, WHITEBAL_REG);
		konica_stream_on(gspca_dev);
		अवरोध;
	हाल V4L2_CID_SHARPNESS:
		konica_stream_off(gspca_dev);
		reg_w(gspca_dev, ctrl->val, SHARPNESS_REG);
		konica_stream_on(gspca_dev);
		अवरोध;
	पूर्ण
	वापस gspca_dev->usb_err;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops sd_ctrl_ops = अणु
	.s_ctrl = sd_s_ctrl,
पूर्ण;

अटल पूर्णांक sd_init_controls(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा v4l2_ctrl_handler *hdl = &gspca_dev->ctrl_handler;

	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 5);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 9, 1, 4);
	/* Needs to be verअगरied */
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 9, 1, 4);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_SATURATION, 0, 9, 1, 4);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_WHITE_BALANCE_TEMPERATURE,
			0, 33, 1, 25);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_SHARPNESS, 0, 9, 1, 4);

	अगर (hdl->error) अणु
		pr_err("Could not initialize controls\n");
		वापस hdl->error;
	पूर्ण
	वापस 0;
पूर्ण

/* sub-driver description */
अटल स्थिर काष्ठा sd_desc sd_desc = अणु
	.name = MODULE_NAME,
	.config = sd_config,
	.init = sd_init,
	.init_controls = sd_init_controls,
	.start = sd_start,
	.stopN = sd_stopN,
#अगर IS_ENABLED(CONFIG_INPUT)
	.other_input = 1,
#पूर्ण_अगर
पूर्ण;

/* -- module initialisation -- */
अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणुUSB_DEVICE(0x04c8, 0x0720)पूर्ण, /* Intel YC 76 */
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, device_table);

/* -- device connect -- */
अटल पूर्णांक sd_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			स्थिर काष्ठा usb_device_id *id)
अणु
	वापस gspca_dev_probe(पूर्णांकf, id, &sd_desc, माप(काष्ठा sd),
				THIS_MODULE);
पूर्ण

अटल काष्ठा usb_driver sd_driver = अणु
	.name = MODULE_NAME,
	.id_table = device_table,
	.probe = sd_probe,
	.disconnect = gspca_disconnect,
#अगर_घोषित CONFIG_PM
	.suspend = gspca_suspend,
	.resume = gspca_resume,
	.reset_resume = gspca_resume,
#पूर्ण_अगर
पूर्ण;

module_usb_driver(sd_driver);
