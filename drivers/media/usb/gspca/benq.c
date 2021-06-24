<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Benq DC E300 subdriver
 *
 * Copyright (C) 2009 Jean-Francois Moine (http://moinejf.मुक्त.fr)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा MODULE_NAME "benq"

#समावेश "gspca.h"

MODULE_AUTHOR("Jean-Francois Moine <http://moinejf.free.fr>");
MODULE_DESCRIPTION("Benq DC E300 USB Camera Driver");
MODULE_LICENSE("GPL");

/* specअगरic webcam descriptor */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;	/* !! must be the first item */
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat vga_mode[] = अणु
	अणु320, 240, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEGपूर्ण,
पूर्ण;

अटल व्योम sd_isoc_irq(काष्ठा urb *urb);

/* -- ग_लिखो a रेजिस्टर -- */
अटल व्योम reg_w(काष्ठा gspca_dev *gspca_dev,
			u16 value, u16 index)
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
			500);
	अगर (ret < 0) अणु
		pr_err("reg_w err %d\n", ret);
		gspca_dev->usb_err = ret;
	पूर्ण
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
	वापस 0;
पूर्ण

/* -- start the camera -- */
अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा urb *urb;
	पूर्णांक i, n;

	/* create 4 URBs - 2 on endpoपूर्णांक 0x83 and 2 on 0x082 */
#अगर MAX_NURBS < 4
#त्रुटि "Not enough URBs in the gspca table"
#पूर्ण_अगर
#घोषणा SD_PKT_SZ 64
#घोषणा SD_NPKT 32
	क्रम (n = 0; n < 4; n++) अणु
		urb = usb_alloc_urb(SD_NPKT, GFP_KERNEL);
		अगर (!urb)
			वापस -ENOMEM;
		gspca_dev->urb[n] = urb;
		urb->transfer_buffer = usb_alloc_coherent(gspca_dev->dev,
						SD_PKT_SZ * SD_NPKT,
						GFP_KERNEL,
						&urb->transfer_dma);

		अगर (urb->transfer_buffer == शून्य) अणु
			pr_err("usb_alloc_coherent failed\n");
			वापस -ENOMEM;
		पूर्ण
		urb->dev = gspca_dev->dev;
		urb->context = gspca_dev;
		urb->transfer_buffer_length = SD_PKT_SZ * SD_NPKT;
		urb->pipe = usb_rcvisocpipe(gspca_dev->dev,
					n & 1 ? 0x82 : 0x83);
		urb->transfer_flags = URB_ISO_ASAP
					| URB_NO_TRANSFER_DMA_MAP;
		urb->पूर्णांकerval = 1;
		urb->complete = sd_isoc_irq;
		urb->number_of_packets = SD_NPKT;
		क्रम (i = 0; i < SD_NPKT; i++) अणु
			urb->iso_frame_desc[i].length = SD_PKT_SZ;
			urb->iso_frame_desc[i].offset = SD_PKT_SZ * i;
		पूर्ण
	पूर्ण

	वापस gspca_dev->usb_err;
पूर्ण

अटल व्योम sd_stopN(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;

	reg_w(gspca_dev, 0x003c, 0x0003);
	reg_w(gspca_dev, 0x003c, 0x0004);
	reg_w(gspca_dev, 0x003c, 0x0005);
	reg_w(gspca_dev, 0x003c, 0x0006);
	reg_w(gspca_dev, 0x003c, 0x0007);

	पूर्णांकf = usb_अगरnum_to_अगर(gspca_dev->dev, gspca_dev->अगरace);
	usb_set_पूर्णांकerface(gspca_dev->dev, gspca_dev->अगरace,
					पूर्णांकf->num_altsetting - 1);
पूर्ण

अटल व्योम sd_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,		/* isoc packet */
			पूर्णांक len)		/* iso packet length */
अणु
	/* unused */
पूर्ण

/* reception of an URB */
अटल व्योम sd_isoc_irq(काष्ठा urb *urb)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *) urb->context;
	काष्ठा urb *urb0;
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
		pr_err("urb status: %d\n", urb->status);
		वापस;
	पूर्ण

	/* अगर this is a control URN (ep 0x83), रुको */
	अगर (urb == gspca_dev->urb[0] || urb == gspca_dev->urb[2])
		वापस;

	/* scan both received URBs */
	अगर (urb == gspca_dev->urb[1])
		urb0 = gspca_dev->urb[0];
	अन्यथा
		urb0 = gspca_dev->urb[2];
	क्रम (i = 0; i < urb->number_of_packets; i++) अणु

		/* check the packet status and length */
		अगर (urb0->iso_frame_desc[i].actual_length != SD_PKT_SZ
		    || urb->iso_frame_desc[i].actual_length != SD_PKT_SZ) अणु
			gspca_err(gspca_dev, "ISOC bad lengths %d / %d\n",
				  urb0->iso_frame_desc[i].actual_length,
				  urb->iso_frame_desc[i].actual_length);
			gspca_dev->last_packet_type = DISCARD_PACKET;
			जारी;
		पूर्ण
		st = urb0->iso_frame_desc[i].status;
		अगर (st == 0)
			st = urb->iso_frame_desc[i].status;
		अगर (st) अणु
			pr_err("ISOC data error: [%d] status=%d\n",
				i, st);
			gspca_dev->last_packet_type = DISCARD_PACKET;
			जारी;
		पूर्ण

		/*
		 * The images are received in URBs of dअगरferent endpoपूर्णांकs
		 * (0x83 and 0x82).
		 * Image pieces in URBs of ep 0x83 are continuated in URBs of
		 * ep 0x82 of the same index.
		 * The packets in the URBs of endpoपूर्णांक 0x83 start with:
		 *	- 80 ba/bb 00 00 = start of image followed by 'ff d8'
		 *	- 04 ba/bb oo oo = image piece
		 *		where 'oo oo' is the image offset
						(not checked)
		 *	- (other -> bad frame)
		 * The images are JPEG encoded with full header and
		 * normal ff escape.
		 * The end of image ('ff d9') may occur in any URB.
		 * (not checked)
		 */
		data = (u8 *) urb0->transfer_buffer
					+ urb0->iso_frame_desc[i].offset;
		अगर (data[0] == 0x80 && (data[1] & 0xfe) == 0xba) अणु

			/* new image */
			gspca_frame_add(gspca_dev, LAST_PACKET,
					शून्य, 0);
			gspca_frame_add(gspca_dev, FIRST_PACKET,
					data + 4, SD_PKT_SZ - 4);
		पूर्ण अन्यथा अगर (data[0] == 0x04 && (data[1] & 0xfe) == 0xba) अणु
			gspca_frame_add(gspca_dev, INTER_PACKET,
					data + 4, SD_PKT_SZ - 4);
		पूर्ण अन्यथा अणु
			gspca_dev->last_packet_type = DISCARD_PACKET;
			जारी;
		पूर्ण
		data = (u8 *) urb->transfer_buffer
					+ urb->iso_frame_desc[i].offset;
		gspca_frame_add(gspca_dev, INTER_PACKET,
				data, SD_PKT_SZ);
	पूर्ण

	/* resubmit the URBs */
	st = usb_submit_urb(urb0, GFP_ATOMIC);
	अगर (st < 0)
		pr_err("usb_submit_urb(0) ret %d\n", st);
	st = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (st < 0)
		pr_err("usb_submit_urb() ret %d\n", st);
पूर्ण

/* sub-driver description */
अटल स्थिर काष्ठा sd_desc sd_desc = अणु
	.name = MODULE_NAME,
	.config = sd_config,
	.init = sd_init,
	.start = sd_start,
	.stopN = sd_stopN,
	.pkt_scan = sd_pkt_scan,
पूर्ण;

/* -- module initialisation -- */
अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणुUSB_DEVICE(0x04a5, 0x3035)पूर्ण,
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
