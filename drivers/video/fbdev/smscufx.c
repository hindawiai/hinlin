<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * smscufx.c -- Framebuffer driver क्रम SMSC UFX USB controller
 *
 * Copyright (C) 2011 Steve Glendinning <steve.glendinning@shawell.net>
 * Copyright (C) 2009 Roberto De Ioris <roberto@unbit.it>
 * Copyright (C) 2009 Jaya Kumar <jayakumar.lkml@gmail.com>
 * Copyright (C) 2009 Bernie Thompson <bernie@plugable.com>
 *
 * Based on udlfb, with work from Florian Echtler, Henrik Bjerregaard Pedersen,
 * and others.
 *
 * Works well with Bernie Thompson's X DAMAGE patch to xf86-video-fbdev
 * available from http://git.plugable.com
 *
 * Layout is based on skeletonfb by James Simmons and Geert Uytterhoeven,
 * usb-skeleton by GregKH.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/usb.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/mm.h>
#समावेश <linux/fb.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश "edid.h"

#घोषणा check_warn(status, fmt, args...) \
	(अणु अगर (status < 0) pr_warn(fmt, ##args); पूर्ण)

#घोषणा check_warn_वापस(status, fmt, args...) \
	(अणु अगर (status < 0) अणु pr_warn(fmt, ##args); वापस status; पूर्ण पूर्ण)

#घोषणा check_warn_जाओ_error(status, fmt, args...) \
	(अणु अगर (status < 0) अणु pr_warn(fmt, ##args); जाओ error; पूर्ण पूर्ण)

#घोषणा all_bits_set(x, bits) (((x) & (bits)) == (bits))

#घोषणा USB_VENDOR_REQUEST_WRITE_REGISTER	0xA0
#घोषणा USB_VENDOR_REQUEST_READ_REGISTER	0xA1

/*
 * TODO: Propose standard fb.h ioctl क्रम reporting damage,
 * using _IOWR() and one of the existing area काष्ठाs from fb.h
 * Consider these ioctls deprecated, but they're still used by the
 * DisplayLink X server as yet - need both to be modअगरied in tandem
 * when new ioctl(s) are पढ़ोy.
 */
#घोषणा UFX_IOCTL_RETURN_EDID	(0xAD)
#घोषणा UFX_IOCTL_REPORT_DAMAGE	(0xAA)

/* -BULK_SIZE as per usb-skeleton. Can we get full page and aव्योम overhead? */
#घोषणा BULK_SIZE		(512)
#घोषणा MAX_TRANSFER		(PAGE_SIZE*16 - BULK_SIZE)
#घोषणा WRITES_IN_FLIGHT	(4)

#घोषणा GET_URB_TIMEOUT		(HZ)
#घोषणा FREE_URB_TIMEOUT	(HZ*2)

#घोषणा BPP			2

#घोषणा UFX_DEFIO_WRITE_DELAY	5 /* fb_deferred_io.delay in jअगरfies */
#घोषणा UFX_DEFIO_WRITE_DISABLE	(HZ*60) /* "disable" with दीर्घ delay */

काष्ठा dloarea अणु
	पूर्णांक x, y;
	पूर्णांक w, h;
पूर्ण;

काष्ठा urb_node अणु
	काष्ठा list_head entry;
	काष्ठा ufx_data *dev;
	काष्ठा delayed_work release_urb_work;
	काष्ठा urb *urb;
पूर्ण;

काष्ठा urb_list अणु
	काष्ठा list_head list;
	spinlock_t lock;
	काष्ठा semaphore limit_sem;
	पूर्णांक available;
	पूर्णांक count;
	माप_प्रकार size;
पूर्ण;

काष्ठा ufx_data अणु
	काष्ठा usb_device *udev;
	काष्ठा device *gdev; /* &udev->dev */
	काष्ठा fb_info *info;
	काष्ठा urb_list urbs;
	काष्ठा kref kref;
	पूर्णांक fb_count;
	bool भवized; /* true when physical usb device not present */
	काष्ठा delayed_work मुक्त_framebuffer_work;
	atomic_t usb_active; /* 0 = update भव buffer, but no usb traffic */
	atomic_t lost_pixels; /* 1 = a render op failed. Need screen refresh */
	u8 *edid; /* null until we पढ़ो edid from hw or get from sysfs */
	माप_प्रकार edid_size;
	u32 pseuकरो_palette[256];
पूर्ण;

अटल काष्ठा fb_fix_screeninfo ufx_fix = अणु
	.id =           "smscufx",
	.type =         FB_TYPE_PACKED_PIXELS,
	.visual =       FB_VISUAL_TRUECOLOR,
	.xpanstep =     0,
	.ypanstep =     0,
	.ywrapstep =    0,
	.accel =        FB_ACCEL_NONE,
पूर्ण;

अटल स्थिर u32 smscufx_info_flags = FBINFO_DEFAULT | FBINFO_READS_FAST |
	FBINFO_VIRTFB |	FBINFO_HWACCEL_IMAGEBLIT | FBINFO_HWACCEL_FILLRECT |
	FBINFO_HWACCEL_COPYAREA | FBINFO_MISC_ALWAYS_SETPAR;

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणुUSB_DEVICE(0x0424, 0x9d00),पूर्ण,
	अणुUSB_DEVICE(0x0424, 0x9d01),पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

/* module options */
अटल bool console;   /* Optionally allow fbcon to consume first framebuffer */
अटल bool fb_defio = true;  /* Optionally enable fb_defio mmap support */

/* ufx keeps a list of urbs क्रम efficient bulk transfers */
अटल व्योम ufx_urb_completion(काष्ठा urb *urb);
अटल काष्ठा urb *ufx_get_urb(काष्ठा ufx_data *dev);
अटल पूर्णांक ufx_submit_urb(काष्ठा ufx_data *dev, काष्ठा urb * urb, माप_प्रकार len);
अटल पूर्णांक ufx_alloc_urb_list(काष्ठा ufx_data *dev, पूर्णांक count, माप_प्रकार size);
अटल व्योम ufx_मुक्त_urb_list(काष्ठा ufx_data *dev);

/* पढ़ोs a control रेजिस्टर */
अटल पूर्णांक ufx_reg_पढ़ो(काष्ठा ufx_data *dev, u32 index, u32 *data)
अणु
	u32 *buf = kदो_स्मृति(4, GFP_KERNEL);
	पूर्णांक ret;

	BUG_ON(!dev);

	अगर (!buf)
		वापस -ENOMEM;

	ret = usb_control_msg(dev->udev, usb_rcvctrlpipe(dev->udev, 0),
		USB_VENDOR_REQUEST_READ_REGISTER,
		USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
		00, index, buf, 4, USB_CTRL_GET_TIMEOUT);

	le32_to_cpus(buf);
	*data = *buf;
	kमुक्त(buf);

	अगर (unlikely(ret < 0))
		pr_warn("Failed to read register index 0x%08x\n", index);

	वापस ret;
पूर्ण

/* ग_लिखोs a control रेजिस्टर */
अटल पूर्णांक ufx_reg_ग_लिखो(काष्ठा ufx_data *dev, u32 index, u32 data)
अणु
	u32 *buf = kदो_स्मृति(4, GFP_KERNEL);
	पूर्णांक ret;

	BUG_ON(!dev);

	अगर (!buf)
		वापस -ENOMEM;

	*buf = data;
	cpu_to_le32s(buf);

	ret = usb_control_msg(dev->udev, usb_sndctrlpipe(dev->udev, 0),
		USB_VENDOR_REQUEST_WRITE_REGISTER,
		USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
		00, index, buf, 4, USB_CTRL_SET_TIMEOUT);

	kमुक्त(buf);

	अगर (unlikely(ret < 0))
		pr_warn("Failed to write register index 0x%08x with value "
			"0x%08x\n", index, data);

	वापस ret;
पूर्ण

अटल पूर्णांक ufx_reg_clear_and_set_bits(काष्ठा ufx_data *dev, u32 index,
	u32 bits_to_clear, u32 bits_to_set)
अणु
	u32 data;
	पूर्णांक status = ufx_reg_पढ़ो(dev, index, &data);
	check_warn_वापस(status, "ufx_reg_clear_and_set_bits error reading "
		"0x%x", index);

	data &= (~bits_to_clear);
	data |= bits_to_set;

	status = ufx_reg_ग_लिखो(dev, index, data);
	check_warn_वापस(status, "ufx_reg_clear_and_set_bits error writing "
		"0x%x", index);

	वापस 0;
पूर्ण

अटल पूर्णांक ufx_reg_set_bits(काष्ठा ufx_data *dev, u32 index, u32 bits)
अणु
	वापस ufx_reg_clear_and_set_bits(dev, index, 0, bits);
पूर्ण

अटल पूर्णांक ufx_reg_clear_bits(काष्ठा ufx_data *dev, u32 index, u32 bits)
अणु
	वापस ufx_reg_clear_and_set_bits(dev, index, bits, 0);
पूर्ण

अटल पूर्णांक ufx_lite_reset(काष्ठा ufx_data *dev)
अणु
	पूर्णांक status;
	u32 value;

	status = ufx_reg_ग_लिखो(dev, 0x3008, 0x00000001);
	check_warn_वापस(status, "ufx_lite_reset error writing 0x3008");

	status = ufx_reg_पढ़ो(dev, 0x3008, &value);
	check_warn_वापस(status, "ufx_lite_reset error reading 0x3008");

	वापस (value == 0) ? 0 : -EIO;
पूर्ण

/* If display is unblanked, then blank it */
अटल पूर्णांक ufx_blank(काष्ठा ufx_data *dev, bool रुको)
अणु
	u32 dc_ctrl, dc_sts;
	पूर्णांक i;

	पूर्णांक status = ufx_reg_पढ़ो(dev, 0x2004, &dc_sts);
	check_warn_वापस(status, "ufx_blank error reading 0x2004");

	status = ufx_reg_पढ़ो(dev, 0x2000, &dc_ctrl);
	check_warn_वापस(status, "ufx_blank error reading 0x2000");

	/* वापस success अगर display is alपढ़ोy blanked */
	अगर ((dc_sts & 0x00000100) || (dc_ctrl & 0x00000100))
		वापस 0;

	/* request the DC to blank the display */
	dc_ctrl |= 0x00000100;
	status = ufx_reg_ग_लिखो(dev, 0x2000, dc_ctrl);
	check_warn_वापस(status, "ufx_blank error writing 0x2000");

	/* वापस success immediately अगर we करोn't have to रुको */
	अगर (!रुको)
		वापस 0;

	क्रम (i = 0; i < 250; i++) अणु
		status = ufx_reg_पढ़ो(dev, 0x2004, &dc_sts);
		check_warn_वापस(status, "ufx_blank error reading 0x2004");

		अगर (dc_sts & 0x00000100)
			वापस 0;
	पूर्ण

	/* समयd out रुकोing क्रम display to blank */
	वापस -EIO;
पूर्ण

/* If display is blanked, then unblank it */
अटल पूर्णांक ufx_unblank(काष्ठा ufx_data *dev, bool रुको)
अणु
	u32 dc_ctrl, dc_sts;
	पूर्णांक i;

	पूर्णांक status = ufx_reg_पढ़ो(dev, 0x2004, &dc_sts);
	check_warn_वापस(status, "ufx_unblank error reading 0x2004");

	status = ufx_reg_पढ़ो(dev, 0x2000, &dc_ctrl);
	check_warn_वापस(status, "ufx_unblank error reading 0x2000");

	/* वापस success अगर display is alपढ़ोy unblanked */
	अगर (((dc_sts & 0x00000100) == 0) || ((dc_ctrl & 0x00000100) == 0))
		वापस 0;

	/* request the DC to unblank the display */
	dc_ctrl &= ~0x00000100;
	status = ufx_reg_ग_लिखो(dev, 0x2000, dc_ctrl);
	check_warn_वापस(status, "ufx_unblank error writing 0x2000");

	/* वापस success immediately अगर we करोn't have to रुको */
	अगर (!रुको)
		वापस 0;

	क्रम (i = 0; i < 250; i++) अणु
		status = ufx_reg_पढ़ो(dev, 0x2004, &dc_sts);
		check_warn_वापस(status, "ufx_unblank error reading 0x2004");

		अगर ((dc_sts & 0x00000100) == 0)
			वापस 0;
	पूर्ण

	/* समयd out रुकोing क्रम display to unblank */
	वापस -EIO;
पूर्ण

/* If display is enabled, then disable it */
अटल पूर्णांक ufx_disable(काष्ठा ufx_data *dev, bool रुको)
अणु
	u32 dc_ctrl, dc_sts;
	पूर्णांक i;

	पूर्णांक status = ufx_reg_पढ़ो(dev, 0x2004, &dc_sts);
	check_warn_वापस(status, "ufx_disable error reading 0x2004");

	status = ufx_reg_पढ़ो(dev, 0x2000, &dc_ctrl);
	check_warn_वापस(status, "ufx_disable error reading 0x2000");

	/* वापस success अगर display is alपढ़ोy disabled */
	अगर (((dc_sts & 0x00000001) == 0) || ((dc_ctrl & 0x00000001) == 0))
		वापस 0;

	/* request the DC to disable the display */
	dc_ctrl &= ~(0x00000001);
	status = ufx_reg_ग_लिखो(dev, 0x2000, dc_ctrl);
	check_warn_वापस(status, "ufx_disable error writing 0x2000");

	/* वापस success immediately अगर we करोn't have to रुको */
	अगर (!रुको)
		वापस 0;

	क्रम (i = 0; i < 250; i++) अणु
		status = ufx_reg_पढ़ो(dev, 0x2004, &dc_sts);
		check_warn_वापस(status, "ufx_disable error reading 0x2004");

		अगर ((dc_sts & 0x00000001) == 0)
			वापस 0;
	पूर्ण

	/* समयd out रुकोing क्रम display to disable */
	वापस -EIO;
पूर्ण

/* If display is disabled, then enable it */
अटल पूर्णांक ufx_enable(काष्ठा ufx_data *dev, bool रुको)
अणु
	u32 dc_ctrl, dc_sts;
	पूर्णांक i;

	पूर्णांक status = ufx_reg_पढ़ो(dev, 0x2004, &dc_sts);
	check_warn_वापस(status, "ufx_enable error reading 0x2004");

	status = ufx_reg_पढ़ो(dev, 0x2000, &dc_ctrl);
	check_warn_वापस(status, "ufx_enable error reading 0x2000");

	/* वापस success अगर display is alपढ़ोy enabled */
	अगर ((dc_sts & 0x00000001) || (dc_ctrl & 0x00000001))
		वापस 0;

	/* request the DC to enable the display */
	dc_ctrl |= 0x00000001;
	status = ufx_reg_ग_लिखो(dev, 0x2000, dc_ctrl);
	check_warn_वापस(status, "ufx_enable error writing 0x2000");

	/* वापस success immediately अगर we करोn't have to रुको */
	अगर (!रुको)
		वापस 0;

	क्रम (i = 0; i < 250; i++) अणु
		status = ufx_reg_पढ़ो(dev, 0x2004, &dc_sts);
		check_warn_वापस(status, "ufx_enable error reading 0x2004");

		अगर (dc_sts & 0x00000001)
			वापस 0;
	पूर्ण

	/* समयd out रुकोing क्रम display to enable */
	वापस -EIO;
पूर्ण

अटल पूर्णांक ufx_config_sys_clk(काष्ठा ufx_data *dev)
अणु
	पूर्णांक status = ufx_reg_ग_लिखो(dev, 0x700C, 0x8000000F);
	check_warn_वापस(status, "error writing 0x700C");

	status = ufx_reg_ग_लिखो(dev, 0x7014, 0x0010024F);
	check_warn_वापस(status, "error writing 0x7014");

	status = ufx_reg_ग_लिखो(dev, 0x7010, 0x00000000);
	check_warn_वापस(status, "error writing 0x7010");

	status = ufx_reg_clear_bits(dev, 0x700C, 0x0000000A);
	check_warn_वापस(status, "error clearing PLL1 bypass in 0x700C");
	msleep(1);

	status = ufx_reg_clear_bits(dev, 0x700C, 0x80000000);
	check_warn_वापस(status, "error clearing output gate in 0x700C");

	वापस 0;
पूर्ण

अटल पूर्णांक ufx_config_ddr2(काष्ठा ufx_data *dev)
अणु
	पूर्णांक status, i = 0;
	u32 पंचांगp;

	status = ufx_reg_ग_लिखो(dev, 0x0004, 0x001F0F77);
	check_warn_वापस(status, "error writing 0x0004");

	status = ufx_reg_ग_लिखो(dev, 0x0008, 0xFFF00000);
	check_warn_वापस(status, "error writing 0x0008");

	status = ufx_reg_ग_लिखो(dev, 0x000C, 0x0FFF2222);
	check_warn_वापस(status, "error writing 0x000C");

	status = ufx_reg_ग_लिखो(dev, 0x0010, 0x00030814);
	check_warn_वापस(status, "error writing 0x0010");

	status = ufx_reg_ग_लिखो(dev, 0x0014, 0x00500019);
	check_warn_वापस(status, "error writing 0x0014");

	status = ufx_reg_ग_लिखो(dev, 0x0018, 0x020D0F15);
	check_warn_वापस(status, "error writing 0x0018");

	status = ufx_reg_ग_लिखो(dev, 0x001C, 0x02532305);
	check_warn_वापस(status, "error writing 0x001C");

	status = ufx_reg_ग_लिखो(dev, 0x0020, 0x0B030905);
	check_warn_वापस(status, "error writing 0x0020");

	status = ufx_reg_ग_लिखो(dev, 0x0024, 0x00000827);
	check_warn_वापस(status, "error writing 0x0024");

	status = ufx_reg_ग_लिखो(dev, 0x0028, 0x00000000);
	check_warn_वापस(status, "error writing 0x0028");

	status = ufx_reg_ग_लिखो(dev, 0x002C, 0x00000042);
	check_warn_वापस(status, "error writing 0x002C");

	status = ufx_reg_ग_लिखो(dev, 0x0030, 0x09520000);
	check_warn_वापस(status, "error writing 0x0030");

	status = ufx_reg_ग_लिखो(dev, 0x0034, 0x02223314);
	check_warn_वापस(status, "error writing 0x0034");

	status = ufx_reg_ग_लिखो(dev, 0x0038, 0x00430043);
	check_warn_वापस(status, "error writing 0x0038");

	status = ufx_reg_ग_लिखो(dev, 0x003C, 0xF00F000F);
	check_warn_वापस(status, "error writing 0x003C");

	status = ufx_reg_ग_लिखो(dev, 0x0040, 0xF380F00F);
	check_warn_वापस(status, "error writing 0x0040");

	status = ufx_reg_ग_लिखो(dev, 0x0044, 0xF00F0496);
	check_warn_वापस(status, "error writing 0x0044");

	status = ufx_reg_ग_लिखो(dev, 0x0048, 0x03080406);
	check_warn_वापस(status, "error writing 0x0048");

	status = ufx_reg_ग_लिखो(dev, 0x004C, 0x00001000);
	check_warn_वापस(status, "error writing 0x004C");

	status = ufx_reg_ग_लिखो(dev, 0x005C, 0x00000007);
	check_warn_वापस(status, "error writing 0x005C");

	status = ufx_reg_ग_लिखो(dev, 0x0100, 0x54F00012);
	check_warn_वापस(status, "error writing 0x0100");

	status = ufx_reg_ग_लिखो(dev, 0x0104, 0x00004012);
	check_warn_वापस(status, "error writing 0x0104");

	status = ufx_reg_ग_लिखो(dev, 0x0118, 0x40404040);
	check_warn_वापस(status, "error writing 0x0118");

	status = ufx_reg_ग_लिखो(dev, 0x0000, 0x00000001);
	check_warn_वापस(status, "error writing 0x0000");

	जबतक (i++ < 500) अणु
		status = ufx_reg_पढ़ो(dev, 0x0000, &पंचांगp);
		check_warn_वापस(status, "error reading 0x0000");

		अगर (all_bits_set(पंचांगp, 0xC0000000))
			वापस 0;
	पूर्ण

	pr_err("DDR2 initialisation timed out, reg 0x0000=0x%08x", पंचांगp);
	वापस -ETIMEDOUT;
पूर्ण

काष्ठा pll_values अणु
	u32 भाग_r0;
	u32 भाग_f0;
	u32 भाग_q0;
	u32 range0;
	u32 भाग_r1;
	u32 भाग_f1;
	u32 भाग_q1;
	u32 range1;
पूर्ण;

अटल u32 ufx_calc_range(u32 ref_freq)
अणु
	अगर (ref_freq >= 88000000)
		वापस 7;

	अगर (ref_freq >= 54000000)
		वापस 6;

	अगर (ref_freq >= 34000000)
		वापस 5;

	अगर (ref_freq >= 21000000)
		वापस 4;

	अगर (ref_freq >= 13000000)
		वापस 3;

	अगर (ref_freq >= 8000000)
		वापस 2;

	वापस 1;
पूर्ण

/* calculates PLL भागider settings क्रम a desired target frequency */
अटल व्योम ufx_calc_pll_values(स्थिर u32 clk_pixel_pll, काष्ठा pll_values *asic_pll)
अणु
	स्थिर u32 ref_clk = 25000000;
	u32 भाग_r0, भाग_f0, भाग_q0, भाग_r1, भाग_f1, भाग_q1;
	u32 min_error = clk_pixel_pll;

	क्रम (भाग_r0 = 1; भाग_r0 <= 32; भाग_r0++) अणु
		u32 ref_freq0 = ref_clk / भाग_r0;
		अगर (ref_freq0 < 5000000)
			अवरोध;

		अगर (ref_freq0 > 200000000)
			जारी;

		क्रम (भाग_f0 = 1; भाग_f0 <= 256; भाग_f0++) अणु
			u32 vco_freq0 = ref_freq0 * भाग_f0;

			अगर (vco_freq0 < 350000000)
				जारी;

			अगर (vco_freq0 > 700000000)
				अवरोध;

			क्रम (भाग_q0 = 0; भाग_q0 < 7; भाग_q0++) अणु
				u32 pllout_freq0 = vco_freq0 / (1 << भाग_q0);

				अगर (pllout_freq0 < 5000000)
					अवरोध;

				अगर (pllout_freq0 > 200000000)
					जारी;

				क्रम (भाग_r1 = 1; भाग_r1 <= 32; भाग_r1++) अणु
					u32 ref_freq1 = pllout_freq0 / भाग_r1;

					अगर (ref_freq1 < 5000000)
						अवरोध;

					क्रम (भाग_f1 = 1; भाग_f1 <= 256; भाग_f1++) अणु
						u32 vco_freq1 = ref_freq1 * भाग_f1;

						अगर (vco_freq1 < 350000000)
							जारी;

						अगर (vco_freq1 > 700000000)
							अवरोध;

						क्रम (भाग_q1 = 0; भाग_q1 < 7; भाग_q1++) अणु
							u32 pllout_freq1 = vco_freq1 / (1 << भाग_q1);
							पूर्णांक error = असल(pllout_freq1 - clk_pixel_pll);

							अगर (pllout_freq1 < 5000000)
								अवरोध;

							अगर (pllout_freq1 > 700000000)
								जारी;

							अगर (error < min_error) अणु
								min_error = error;

								/* final वापसed value is equal to calculated value - 1
								 * because a value of 0 = भागide by 1 */
								asic_pll->भाग_r0 = भाग_r0 - 1;
								asic_pll->भाग_f0 = भाग_f0 - 1;
								asic_pll->भाग_q0 = भाग_q0;
								asic_pll->भाग_r1 = भाग_r1 - 1;
								asic_pll->भाग_f1 = भाग_f1 - 1;
								asic_pll->भाग_q1 = भाग_q1;

								asic_pll->range0 = ufx_calc_range(ref_freq0);
								asic_pll->range1 = ufx_calc_range(ref_freq1);

								अगर (min_error == 0)
									वापस;
							पूर्ण
						पूर्ण
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* sets analog bit PLL configuration values */
अटल पूर्णांक ufx_config_pix_clk(काष्ठा ufx_data *dev, u32 pixघड़ी)
अणु
	काष्ठा pll_values asic_pll = अणु0पूर्ण;
	u32 value, clk_pixel, clk_pixel_pll;
	पूर्णांक status;

	/* convert pixघड़ी (in ps) to frequency (in Hz) */
	clk_pixel = PICOS2KHZ(pixघड़ी) * 1000;
	pr_debug("pixclock %d ps = clk_pixel %d Hz", pixघड़ी, clk_pixel);

	/* clk_pixel = 1/2 clk_pixel_pll */
	clk_pixel_pll = clk_pixel * 2;

	ufx_calc_pll_values(clk_pixel_pll, &asic_pll);

	/* Keep BYPASS and RESET संकेतs निश्चितed until configured */
	status = ufx_reg_ग_लिखो(dev, 0x7000, 0x8000000F);
	check_warn_वापस(status, "error writing 0x7000");

	value = (asic_pll.भाग_f1 | (asic_pll.भाग_r1 << 8) |
		(asic_pll.भाग_q1 << 16) | (asic_pll.range1 << 20));
	status = ufx_reg_ग_लिखो(dev, 0x7008, value);
	check_warn_वापस(status, "error writing 0x7008");

	value = (asic_pll.भाग_f0 | (asic_pll.भाग_r0 << 8) |
		(asic_pll.भाग_q0 << 16) | (asic_pll.range0 << 20));
	status = ufx_reg_ग_लिखो(dev, 0x7004, value);
	check_warn_वापस(status, "error writing 0x7004");

	status = ufx_reg_clear_bits(dev, 0x7000, 0x00000005);
	check_warn_वापस(status,
		"error clearing PLL0 bypass bits in 0x7000");
	msleep(1);

	status = ufx_reg_clear_bits(dev, 0x7000, 0x0000000A);
	check_warn_वापस(status,
		"error clearing PLL1 bypass bits in 0x7000");
	msleep(1);

	status = ufx_reg_clear_bits(dev, 0x7000, 0x80000000);
	check_warn_वापस(status, "error clearing gate bits in 0x7000");

	वापस 0;
पूर्ण

अटल पूर्णांक ufx_set_vid_mode(काष्ठा ufx_data *dev, काष्ठा fb_var_screeninfo *var)
अणु
	u32 temp;
	u16 h_total, h_active, h_blank_start, h_blank_end, h_sync_start, h_sync_end;
	u16 v_total, v_active, v_blank_start, v_blank_end, v_sync_start, v_sync_end;

	पूर्णांक status = ufx_reg_ग_लिखो(dev, 0x8028, 0);
	check_warn_वापस(status, "ufx_set_vid_mode error disabling RGB pad");

	status = ufx_reg_ग_लिखो(dev, 0x8024, 0);
	check_warn_वापस(status, "ufx_set_vid_mode error disabling VDAC");

	/* shut everything करोwn beक्रमe changing timing */
	status = ufx_blank(dev, true);
	check_warn_वापस(status, "ufx_set_vid_mode error blanking display");

	status = ufx_disable(dev, true);
	check_warn_वापस(status, "ufx_set_vid_mode error disabling display");

	status = ufx_config_pix_clk(dev, var->pixघड़ी);
	check_warn_वापस(status, "ufx_set_vid_mode error configuring pixclock");

	status = ufx_reg_ग_लिखो(dev, 0x2000, 0x00000104);
	check_warn_वापस(status, "ufx_set_vid_mode error writing 0x2000");

	/* set horizontal timings */
	h_total = var->xres + var->right_margin + var->hsync_len + var->left_margin;
	h_active = var->xres;
	h_blank_start = var->xres + var->right_margin;
	h_blank_end = var->xres + var->right_margin + var->hsync_len;
	h_sync_start = var->xres + var->right_margin;
	h_sync_end = var->xres + var->right_margin + var->hsync_len;

	temp = ((h_total - 1) << 16) | (h_active - 1);
	status = ufx_reg_ग_लिखो(dev, 0x2008, temp);
	check_warn_वापस(status, "ufx_set_vid_mode error writing 0x2008");

	temp = ((h_blank_start - 1) << 16) | (h_blank_end - 1);
	status = ufx_reg_ग_लिखो(dev, 0x200C, temp);
	check_warn_वापस(status, "ufx_set_vid_mode error writing 0x200C");

	temp = ((h_sync_start - 1) << 16) | (h_sync_end - 1);
	status = ufx_reg_ग_लिखो(dev, 0x2010, temp);
	check_warn_वापस(status, "ufx_set_vid_mode error writing 0x2010");

	/* set vertical timings */
	v_total = var->upper_margin + var->yres + var->lower_margin + var->vsync_len;
	v_active = var->yres;
	v_blank_start = var->yres + var->lower_margin;
	v_blank_end = var->yres + var->lower_margin + var->vsync_len;
	v_sync_start = var->yres + var->lower_margin;
	v_sync_end = var->yres + var->lower_margin + var->vsync_len;

	temp = ((v_total - 1) << 16) | (v_active - 1);
	status = ufx_reg_ग_लिखो(dev, 0x2014, temp);
	check_warn_वापस(status, "ufx_set_vid_mode error writing 0x2014");

	temp = ((v_blank_start - 1) << 16) | (v_blank_end - 1);
	status = ufx_reg_ग_लिखो(dev, 0x2018, temp);
	check_warn_वापस(status, "ufx_set_vid_mode error writing 0x2018");

	temp = ((v_sync_start - 1) << 16) | (v_sync_end - 1);
	status = ufx_reg_ग_लिखो(dev, 0x201C, temp);
	check_warn_वापस(status, "ufx_set_vid_mode error writing 0x201C");

	status = ufx_reg_ग_लिखो(dev, 0x2020, 0x00000000);
	check_warn_वापस(status, "ufx_set_vid_mode error writing 0x2020");

	status = ufx_reg_ग_लिखो(dev, 0x2024, 0x00000000);
	check_warn_वापस(status, "ufx_set_vid_mode error writing 0x2024");

	/* Set the frame length रेजिस्टर (#pix * 2 bytes/pixel) */
	temp = var->xres * var->yres * 2;
	temp = (temp + 7) & (~0x7);
	status = ufx_reg_ग_लिखो(dev, 0x2028, temp);
	check_warn_वापस(status, "ufx_set_vid_mode error writing 0x2028");

	/* enable desired output पूर्णांकerface & disable others */
	status = ufx_reg_ग_लिखो(dev, 0x2040, 0);
	check_warn_वापस(status, "ufx_set_vid_mode error writing 0x2040");

	status = ufx_reg_ग_लिखो(dev, 0x2044, 0);
	check_warn_वापस(status, "ufx_set_vid_mode error writing 0x2044");

	status = ufx_reg_ग_लिखो(dev, 0x2048, 0);
	check_warn_वापस(status, "ufx_set_vid_mode error writing 0x2048");

	/* set the sync polarities & enable bit */
	temp = 0x00000001;
	अगर (var->sync & FB_SYNC_HOR_HIGH_ACT)
		temp |= 0x00000010;

	अगर (var->sync & FB_SYNC_VERT_HIGH_ACT)
		temp |= 0x00000008;

	status = ufx_reg_ग_लिखो(dev, 0x2040, temp);
	check_warn_वापस(status, "ufx_set_vid_mode error writing 0x2040");

	/* start everything back up */
	status = ufx_enable(dev, true);
	check_warn_वापस(status, "ufx_set_vid_mode error enabling display");

	/* Unblank the display */
	status = ufx_unblank(dev, true);
	check_warn_वापस(status, "ufx_set_vid_mode error unblanking display");

	/* enable RGB pad */
	status = ufx_reg_ग_लिखो(dev, 0x8028, 0x00000003);
	check_warn_वापस(status, "ufx_set_vid_mode error enabling RGB pad");

	/* enable VDAC */
	status = ufx_reg_ग_लिखो(dev, 0x8024, 0x00000007);
	check_warn_वापस(status, "ufx_set_vid_mode error enabling VDAC");

	वापस 0;
पूर्ण

अटल पूर्णांक ufx_ops_mmap(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ start = vma->vm_start;
	अचिन्हित दीर्घ size = vma->vm_end - vma->vm_start;
	अचिन्हित दीर्घ offset = vma->vm_pgoff << PAGE_SHIFT;
	अचिन्हित दीर्घ page, pos;

	अगर (vma->vm_pgoff > (~0UL >> PAGE_SHIFT))
		वापस -EINVAL;
	अगर (size > info->fix.smem_len)
		वापस -EINVAL;
	अगर (offset > info->fix.smem_len - size)
		वापस -EINVAL;

	pos = (अचिन्हित दीर्घ)info->fix.smem_start + offset;

	pr_debug("mmap() framebuffer addr:%lu size:%lu\n",
		  pos, size);

	जबतक (size > 0) अणु
		page = vदो_स्मृति_to_pfn((व्योम *)pos);
		अगर (remap_pfn_range(vma, start, page, PAGE_SIZE, PAGE_SHARED))
			वापस -EAGAIN;

		start += PAGE_SIZE;
		pos += PAGE_SIZE;
		अगर (size > PAGE_SIZE)
			size -= PAGE_SIZE;
		अन्यथा
			size = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ufx_raw_rect(काष्ठा ufx_data *dev, u16 *cmd, पूर्णांक x, पूर्णांक y,
	पूर्णांक width, पूर्णांक height)
अणु
	माप_प्रकार packed_line_len = ALIGN((width * 2), 4);
	माप_प्रकार packed_rect_len = packed_line_len * height;
	पूर्णांक line;

	BUG_ON(!dev);
	BUG_ON(!dev->info);

	/* command word */
	*((u32 *)&cmd[0]) = cpu_to_le32(0x01);

	/* length word */
	*((u32 *)&cmd[2]) = cpu_to_le32(packed_rect_len + 16);

	cmd[4] = cpu_to_le16(x);
	cmd[5] = cpu_to_le16(y);
	cmd[6] = cpu_to_le16(width);
	cmd[7] = cpu_to_le16(height);

	/* frame base address */
	*((u32 *)&cmd[8]) = cpu_to_le32(0);

	/* color mode and horizontal resolution */
	cmd[10] = cpu_to_le16(0x4000 | dev->info->var.xres);

	/* vertical resolution */
	cmd[11] = cpu_to_le16(dev->info->var.yres);

	/* packed data */
	क्रम (line = 0; line < height; line++) अणु
		स्थिर पूर्णांक line_offset = dev->info->fix.line_length * (y + line);
		स्थिर पूर्णांक byte_offset = line_offset + (x * BPP);
		स_नकल(&cmd[(24 + (packed_line_len * line)) / 2],
			(अक्षर *)dev->info->fix.smem_start + byte_offset, width * BPP);
	पूर्ण
पूर्ण

अटल पूर्णांक ufx_handle_damage(काष्ठा ufx_data *dev, पूर्णांक x, पूर्णांक y,
	पूर्णांक width, पूर्णांक height)
अणु
	माप_प्रकार packed_line_len = ALIGN((width * 2), 4);
	पूर्णांक len, status, urb_lines, start_line = 0;

	अगर ((width <= 0) || (height <= 0) ||
	    (x + width > dev->info->var.xres) ||
	    (y + height > dev->info->var.yres))
		वापस -EINVAL;

	अगर (!atomic_पढ़ो(&dev->usb_active))
		वापस 0;

	जबतक (start_line < height) अणु
		काष्ठा urb *urb = ufx_get_urb(dev);
		अगर (!urb) अणु
			pr_warn("ufx_handle_damage unable to get urb");
			वापस 0;
		पूर्ण

		/* assume we have enough space to transfer at least one line */
		BUG_ON(urb->transfer_buffer_length < (24 + (width * 2)));

		/* calculate the maximum number of lines we could fit in */
		urb_lines = (urb->transfer_buffer_length - 24) / packed_line_len;

		/* but we might not need this many */
		urb_lines = min(urb_lines, (height - start_line));

		स_रखो(urb->transfer_buffer, 0, urb->transfer_buffer_length);

		ufx_raw_rect(dev, urb->transfer_buffer, x, (y + start_line), width, urb_lines);
		len = 24 + (packed_line_len * urb_lines);

		status = ufx_submit_urb(dev, urb, len);
		check_warn_वापस(status, "Error submitting URB");

		start_line += urb_lines;
	पूर्ण

	वापस 0;
पूर्ण

/* Path triggered by usermode clients who ग_लिखो to fileप्रणाली
 * e.g. cat filename > /dev/fb1
 * Not used by X Winकरोws or text-mode console. But useful क्रम testing.
 * Slow because of extra copy and we must assume all pixels dirty. */
अटल sमाप_प्रकार ufx_ops_ग_लिखो(काष्ठा fb_info *info, स्थिर अक्षर __user *buf,
			  माप_प्रकार count, loff_t *ppos)
अणु
	sमाप_प्रकार result;
	काष्ठा ufx_data *dev = info->par;
	u32 offset = (u32) *ppos;

	result = fb_sys_ग_लिखो(info, buf, count, ppos);

	अगर (result > 0) अणु
		पूर्णांक start = max((पूर्णांक)(offset / info->fix.line_length), 0);
		पूर्णांक lines = min((u32)((result / info->fix.line_length) + 1),
				(u32)info->var.yres);

		ufx_handle_damage(dev, 0, start, info->var.xres, lines);
	पूर्ण

	वापस result;
पूर्ण

अटल व्योम ufx_ops_copyarea(काष्ठा fb_info *info,
				स्थिर काष्ठा fb_copyarea *area)
अणु

	काष्ठा ufx_data *dev = info->par;

	sys_copyarea(info, area);

	ufx_handle_damage(dev, area->dx, area->dy,
			area->width, area->height);
पूर्ण

अटल व्योम ufx_ops_imageblit(काष्ठा fb_info *info,
				स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा ufx_data *dev = info->par;

	sys_imageblit(info, image);

	ufx_handle_damage(dev, image->dx, image->dy,
			image->width, image->height);
पूर्ण

अटल व्योम ufx_ops_fillrect(काष्ठा fb_info *info,
			  स्थिर काष्ठा fb_fillrect *rect)
अणु
	काष्ठा ufx_data *dev = info->par;

	sys_fillrect(info, rect);

	ufx_handle_damage(dev, rect->dx, rect->dy, rect->width,
			      rect->height);
पूर्ण

/* NOTE: fb_defio.c is holding info->fbdefio.mutex
 *   Touching ANY framebuffer memory that triggers a page fault
 *   in fb_defio will cause a deadlock, when it also tries to
 *   grab the same mutex. */
अटल व्योम ufx_dpy_deferred_io(काष्ठा fb_info *info,
				काष्ठा list_head *pagelist)
अणु
	काष्ठा page *cur;
	काष्ठा fb_deferred_io *fbdefio = info->fbdefio;
	काष्ठा ufx_data *dev = info->par;

	अगर (!fb_defio)
		वापस;

	अगर (!atomic_पढ़ो(&dev->usb_active))
		वापस;

	/* walk the written page list and render each to device */
	list_क्रम_each_entry(cur, &fbdefio->pagelist, lru) अणु
		/* create a rectangle of full screen width that enबंदs the
		 * entire dirty framebuffer page */
		स्थिर पूर्णांक x = 0;
		स्थिर पूर्णांक width = dev->info->var.xres;
		स्थिर पूर्णांक y = (cur->index << PAGE_SHIFT) / (width * 2);
		पूर्णांक height = (PAGE_SIZE / (width * 2)) + 1;
		height = min(height, (पूर्णांक)(dev->info->var.yres - y));

		BUG_ON(y >= dev->info->var.yres);
		BUG_ON((y + height) > dev->info->var.yres);

		ufx_handle_damage(dev, x, y, width, height);
	पूर्ण
पूर्ण

अटल पूर्णांक ufx_ops_ioctl(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd,
			 अचिन्हित दीर्घ arg)
अणु
	काष्ठा ufx_data *dev = info->par;
	काष्ठा dloarea *area = शून्य;

	अगर (!atomic_पढ़ो(&dev->usb_active))
		वापस 0;

	/* TODO: Update X server to get this from sysfs instead */
	अगर (cmd == UFX_IOCTL_RETURN_EDID) अणु
		u8 __user *edid = (u8 __user *)arg;
		अगर (copy_to_user(edid, dev->edid, dev->edid_size))
			वापस -EFAULT;
		वापस 0;
	पूर्ण

	/* TODO: Help propose a standard fb.h ioctl to report mmap damage */
	अगर (cmd == UFX_IOCTL_REPORT_DAMAGE) अणु
		/* If we have a damage-aware client, turn fb_defio "off"
		 * To aव्योम perf imact of unnecessary page fault handling.
		 * Done by resetting the delay क्रम this fb_info to a very
		 * दीर्घ period. Pages will become writable and stay that way.
		 * Reset to normal value when all clients have बंदd this fb.
		 */
		अगर (info->fbdefio)
			info->fbdefio->delay = UFX_DEFIO_WRITE_DISABLE;

		area = (काष्ठा dloarea *)arg;

		अगर (area->x < 0)
			area->x = 0;

		अगर (area->x > info->var.xres)
			area->x = info->var.xres;

		अगर (area->y < 0)
			area->y = 0;

		अगर (area->y > info->var.yres)
			area->y = info->var.yres;

		ufx_handle_damage(dev, area->x, area->y, area->w, area->h);
	पूर्ण

	वापस 0;
पूर्ण

/* taken from vesafb */
अटल पूर्णांक
ufx_ops_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
	       अचिन्हित blue, अचिन्हित transp, काष्ठा fb_info *info)
अणु
	पूर्णांक err = 0;

	अगर (regno >= info->cmap.len)
		वापस 1;

	अगर (regno < 16) अणु
		अगर (info->var.red.offset == 10) अणु
			/* 1:5:5:5 */
			((u32 *) (info->pseuकरो_palette))[regno] =
			    ((red & 0xf800) >> 1) |
			    ((green & 0xf800) >> 6) | ((blue & 0xf800) >> 11);
		पूर्ण अन्यथा अणु
			/* 0:5:6:5 */
			((u32 *) (info->pseuकरो_palette))[regno] =
			    ((red & 0xf800)) |
			    ((green & 0xfc00) >> 5) | ((blue & 0xf800) >> 11);
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

/* It's common क्रम several clients to have framebuffer खोलो simultaneously.
 * e.g. both fbcon and X. Makes things पूर्णांकeresting.
 * Assumes caller is holding info->lock (क्रम खोलो and release at least) */
अटल पूर्णांक ufx_ops_खोलो(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा ufx_data *dev = info->par;

	/* fbcon aggressively connects to first framebuffer it finds,
	 * preventing other clients (X) from working properly. Usually
	 * not what the user wants. Fail by शेष with option to enable. */
	अगर (user == 0 && !console)
		वापस -EBUSY;

	/* If the USB device is gone, we करोn't accept new खोलोs */
	अगर (dev->भवized)
		वापस -ENODEV;

	dev->fb_count++;

	kref_get(&dev->kref);

	अगर (fb_defio && (info->fbdefio == शून्य)) अणु
		/* enable defio at last moment अगर not disabled by client */

		काष्ठा fb_deferred_io *fbdefio;

		fbdefio = kzalloc(माप(*fbdefio), GFP_KERNEL);
		अगर (fbdefio) अणु
			fbdefio->delay = UFX_DEFIO_WRITE_DELAY;
			fbdefio->deferred_io = ufx_dpy_deferred_io;
		पूर्ण

		info->fbdefio = fbdefio;
		fb_deferred_io_init(info);
	पूर्ण

	pr_debug("open /dev/fb%d user=%d fb_info=%p count=%d",
		info->node, user, info, dev->fb_count);

	वापस 0;
पूर्ण

/*
 * Called when all client पूर्णांकerfaces to start transactions have been disabled,
 * and all references to our device instance (ufx_data) are released.
 * Every transaction must have a reference, so we know are fully spun करोwn
 */
अटल व्योम ufx_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा ufx_data *dev = container_of(kref, काष्ठा ufx_data, kref);

	/* this function will रुको क्रम all in-flight urbs to complete */
	अगर (dev->urbs.count > 0)
		ufx_मुक्त_urb_list(dev);

	pr_debug("freeing ufx_data %p", dev);

	kमुक्त(dev);
पूर्ण

अटल व्योम ufx_release_urb_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा urb_node *unode = container_of(work, काष्ठा urb_node,
					      release_urb_work.work);

	up(&unode->dev->urbs.limit_sem);
पूर्ण

अटल व्योम ufx_मुक्त_framebuffer_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ufx_data *dev = container_of(work, काष्ठा ufx_data,
					    मुक्त_framebuffer_work.work);
	काष्ठा fb_info *info = dev->info;
	पूर्णांक node = info->node;

	unरेजिस्टर_framebuffer(info);

	अगर (info->cmap.len != 0)
		fb_dealloc_cmap(&info->cmap);
	अगर (info->monspecs.modedb)
		fb_destroy_modedb(info->monspecs.modedb);
	vमुक्त(info->screen_base);

	fb_destroy_modelist(&info->modelist);

	dev->info = शून्य;

	/* Assume info काष्ठाure is मुक्तd after this poपूर्णांक */
	framebuffer_release(info);

	pr_debug("fb_info for /dev/fb%d has been freed", node);

	/* ref taken in probe() as part of रेजिस्टरing framebfufer */
	kref_put(&dev->kref, ufx_मुक्त);
पूर्ण

/*
 * Assumes caller is holding info->lock mutex (क्रम खोलो and release at least)
 */
अटल पूर्णांक ufx_ops_release(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा ufx_data *dev = info->par;

	dev->fb_count--;

	/* We can't मुक्त fb_info here - fbmem will touch it when we वापस */
	अगर (dev->भवized && (dev->fb_count == 0))
		schedule_delayed_work(&dev->मुक्त_framebuffer_work, HZ);

	अगर ((dev->fb_count == 0) && (info->fbdefio)) अणु
		fb_deferred_io_cleanup(info);
		kमुक्त(info->fbdefio);
		info->fbdefio = शून्य;
	पूर्ण

	pr_debug("released /dev/fb%d user=%d count=%d",
		  info->node, user, dev->fb_count);

	kref_put(&dev->kref, ufx_मुक्त);

	वापस 0;
पूर्ण

/* Check whether a video mode is supported by the chip
 * We start from monitor's modes, so don't need to filter that here */
अटल पूर्णांक ufx_is_valid_mode(काष्ठा fb_videomode *mode,
		काष्ठा fb_info *info)
अणु
	अगर ((mode->xres * mode->yres) > (2048 * 1152)) अणु
		pr_debug("%dx%d too many pixels",
		       mode->xres, mode->yres);
		वापस 0;
	पूर्ण

	अगर (mode->pixघड़ी < 5000) अणु
		pr_debug("%dx%d %dps pixel clock too fast",
		       mode->xres, mode->yres, mode->pixघड़ी);
		वापस 0;
	पूर्ण

	pr_debug("%dx%d (pixclk %dps %dMHz) valid mode", mode->xres, mode->yres,
		mode->pixघड़ी, (1000000 / mode->pixघड़ी));
	वापस 1;
पूर्ण

अटल व्योम ufx_var_color_क्रमmat(काष्ठा fb_var_screeninfo *var)
अणु
	स्थिर काष्ठा fb_bitfield red = अणु 11, 5, 0 पूर्ण;
	स्थिर काष्ठा fb_bitfield green = अणु 5, 6, 0 पूर्ण;
	स्थिर काष्ठा fb_bitfield blue = अणु 0, 5, 0 पूर्ण;

	var->bits_per_pixel = 16;
	var->red = red;
	var->green = green;
	var->blue = blue;
पूर्ण

अटल पूर्णांक ufx_ops_check_var(काष्ठा fb_var_screeninfo *var,
				काष्ठा fb_info *info)
अणु
	काष्ठा fb_videomode mode;

	/* TODO: support dynamically changing framebuffer size */
	अगर ((var->xres * var->yres * 2) > info->fix.smem_len)
		वापस -EINVAL;

	/* set device-specअगरic elements of var unrelated to mode */
	ufx_var_color_क्रमmat(var);

	fb_var_to_videomode(&mode, var);

	अगर (!ufx_is_valid_mode(&mode, info))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक ufx_ops_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा ufx_data *dev = info->par;
	पूर्णांक result;
	u16 *pix_framebuffer;
	पूर्णांक i;

	pr_debug("set_par mode %dx%d", info->var.xres, info->var.yres);
	result = ufx_set_vid_mode(dev, &info->var);

	अगर ((result == 0) && (dev->fb_count == 0)) अणु
		/* paपूर्णांक greenscreen */
		pix_framebuffer = (u16 *) info->screen_base;
		क्रम (i = 0; i < info->fix.smem_len / 2; i++)
			pix_framebuffer[i] = 0x37e6;

		ufx_handle_damage(dev, 0, 0, info->var.xres, info->var.yres);
	पूर्ण

	/* re-enable defio अगर previously disabled by damage tracking */
	अगर (info->fbdefio)
		info->fbdefio->delay = UFX_DEFIO_WRITE_DELAY;

	वापस result;
पूर्ण

/* In order to come back from full DPMS off, we need to set the mode again */
अटल पूर्णांक ufx_ops_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	काष्ठा ufx_data *dev = info->par;
	ufx_set_vid_mode(dev, &info->var);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops ufx_ops = अणु
	.owner = THIS_MODULE,
	.fb_पढ़ो = fb_sys_पढ़ो,
	.fb_ग_लिखो = ufx_ops_ग_लिखो,
	.fb_setcolreg = ufx_ops_setcolreg,
	.fb_fillrect = ufx_ops_fillrect,
	.fb_copyarea = ufx_ops_copyarea,
	.fb_imageblit = ufx_ops_imageblit,
	.fb_mmap = ufx_ops_mmap,
	.fb_ioctl = ufx_ops_ioctl,
	.fb_खोलो = ufx_ops_खोलो,
	.fb_release = ufx_ops_release,
	.fb_blank = ufx_ops_blank,
	.fb_check_var = ufx_ops_check_var,
	.fb_set_par = ufx_ops_set_par,
पूर्ण;

/* Assumes &info->lock held by caller
 * Assumes no active clients have framebuffer खोलो */
अटल पूर्णांक ufx_पुनः_स्मृति_framebuffer(काष्ठा ufx_data *dev, काष्ठा fb_info *info)
अणु
	पूर्णांक old_len = info->fix.smem_len;
	पूर्णांक new_len;
	अचिन्हित अक्षर *old_fb = info->screen_base;
	अचिन्हित अक्षर *new_fb;

	pr_debug("Reallocating framebuffer. Addresses will change!");

	new_len = info->fix.line_length * info->var.yres;

	अगर (PAGE_ALIGN(new_len) > old_len) अणु
		/*
		 * Alloc प्रणाली memory क्रम भव framebuffer
		 */
		new_fb = vदो_स्मृति(new_len);
		अगर (!new_fb)
			वापस -ENOMEM;

		अगर (info->screen_base) अणु
			स_नकल(new_fb, old_fb, old_len);
			vमुक्त(info->screen_base);
		पूर्ण

		info->screen_base = new_fb;
		info->fix.smem_len = PAGE_ALIGN(new_len);
		info->fix.smem_start = (अचिन्हित दीर्घ) new_fb;
		info->flags = smscufx_info_flags;
	पूर्ण
	वापस 0;
पूर्ण

/* sets up I2C Controller क्रम 100 Kbps, std. speed, 7-bit addr, master,
 * restart enabled, but no start byte, enable controller */
अटल पूर्णांक ufx_i2c_init(काष्ठा ufx_data *dev)
अणु
	u32 पंचांगp;

	/* disable the controller beक्रमe it can be reprogrammed */
	पूर्णांक status = ufx_reg_ग_लिखो(dev, 0x106C, 0x00);
	check_warn_वापस(status, "failed to disable I2C");

	/* Setup the घड़ी count रेजिस्टरs
	 * (12+1) = 13 clks @ 2.5 MHz = 5.2 uS */
	status = ufx_reg_ग_लिखो(dev, 0x1018, 12);
	check_warn_वापस(status, "error writing 0x1018");

	/* (6+8) = 14 clks @ 2.5 MHz = 5.6 uS */
	status = ufx_reg_ग_लिखो(dev, 0x1014, 6);
	check_warn_वापस(status, "error writing 0x1014");

	status = ufx_reg_पढ़ो(dev, 0x1000, &पंचांगp);
	check_warn_वापस(status, "error reading 0x1000");

	/* set speed to std mode */
	पंचांगp &= ~(0x06);
	पंचांगp |= 0x02;

	/* 7-bit (not 10-bit) addressing */
	पंचांगp &= ~(0x10);

	/* enable restart conditions and master mode */
	पंचांगp |= 0x21;

	status = ufx_reg_ग_लिखो(dev, 0x1000, पंचांगp);
	check_warn_वापस(status, "error writing 0x1000");

	/* Set normal tx using target address 0 */
	status = ufx_reg_clear_and_set_bits(dev, 0x1004, 0xC00, 0x000);
	check_warn_वापस(status, "error setting TX mode bits in 0x1004");

	/* Enable the controller */
	status = ufx_reg_ग_लिखो(dev, 0x106C, 0x01);
	check_warn_वापस(status, "failed to enable I2C");

	वापस 0;
पूर्ण

/* sets the I2C port mux and target address */
अटल पूर्णांक ufx_i2c_configure(काष्ठा ufx_data *dev)
अणु
	पूर्णांक status = ufx_reg_ग_लिखो(dev, 0x106C, 0x00);
	check_warn_वापस(status, "failed to disable I2C");

	status = ufx_reg_ग_लिखो(dev, 0x3010, 0x00000000);
	check_warn_वापस(status, "failed to write 0x3010");

	/* A0h is std क्रम any EDID, right shअगरted by one */
	status = ufx_reg_clear_and_set_bits(dev, 0x1004, 0x3FF,	(0xA0 >> 1));
	check_warn_वापस(status, "failed to set TAR bits in 0x1004");

	status = ufx_reg_ग_लिखो(dev, 0x106C, 0x01);
	check_warn_वापस(status, "failed to enable I2C");

	वापस 0;
पूर्ण

/* रुको क्रम BUSY to clear, with a समयout of 50ms with 10ms sleeps. अगर no
 * monitor is connected, there is no error except क्रम समयout */
अटल पूर्णांक ufx_i2c_रुको_busy(काष्ठा ufx_data *dev)
अणु
	u32 पंचांगp;
	पूर्णांक i, status;

	क्रम (i = 0; i < 15; i++) अणु
		status = ufx_reg_पढ़ो(dev, 0x1100, &पंचांगp);
		check_warn_वापस(status, "0x1100 read failed");

		/* अगर BUSY is clear, check क्रम error */
		अगर ((पंचांगp & 0x80000000) == 0) अणु
			अगर (पंचांगp & 0x20000000) अणु
				pr_warn("I2C read failed, 0x1100=0x%08x", पंचांगp);
				वापस -EIO;
			पूर्ण

			वापस 0;
		पूर्ण

		/* perक्रमm the first 10 retries without delay */
		अगर (i >= 10)
			msleep(10);
	पूर्ण

	pr_warn("I2C access timed out, resetting I2C hardware");
	status =  ufx_reg_ग_लिखो(dev, 0x1100, 0x40000000);
	check_warn_वापस(status, "0x1100 write failed");

	वापस -ETIMEDOUT;
पूर्ण

/* पढ़ोs a 128-byte EDID block from the currently selected port and TAR */
अटल पूर्णांक ufx_पढ़ो_edid(काष्ठा ufx_data *dev, u8 *edid, पूर्णांक edid_len)
अणु
	पूर्णांक i, j, status;
	u32 *edid_u32 = (u32 *)edid;

	BUG_ON(edid_len != EDID_LENGTH);

	status = ufx_i2c_configure(dev);
	अगर (status < 0) अणु
		pr_err("ufx_i2c_configure failed");
		वापस status;
	पूर्ण

	स_रखो(edid, 0xff, EDID_LENGTH);

	/* Read the 128-byte EDID as 2 bursts of 64 bytes */
	क्रम (i = 0; i < 2; i++) अणु
		u32 temp = 0x28070000 | (63 << 20) | (((u32)(i * 64)) << 8);
		status = ufx_reg_ग_लिखो(dev, 0x1100, temp);
		check_warn_वापस(status, "Failed to write 0x1100");

		temp |= 0x80000000;
		status = ufx_reg_ग_लिखो(dev, 0x1100, temp);
		check_warn_वापस(status, "Failed to write 0x1100");

		status = ufx_i2c_रुको_busy(dev);
		check_warn_वापस(status, "Timeout waiting for I2C BUSY to clear");

		क्रम (j = 0; j < 16; j++) अणु
			u32 data_reg_addr = 0x1110 + (j * 4);
			status = ufx_reg_पढ़ो(dev, data_reg_addr, edid_u32++);
			check_warn_वापस(status, "Error reading i2c data");
		पूर्ण
	पूर्ण

	/* all FF's in the first 16 bytes indicates nothing is connected */
	क्रम (i = 0; i < 16; i++) अणु
		अगर (edid[i] != 0xFF) अणु
			pr_debug("edid data read successfully");
			वापस EDID_LENGTH;
		पूर्ण
	पूर्ण

	pr_warn("edid data contains all 0xff");
	वापस -ETIMEDOUT;
पूर्ण

/* 1) use sw शेष
 * 2) Parse पूर्णांकo various fb_info काष्ठाs
 * 3) Allocate भव framebuffer memory to back highest res mode
 *
 * Parses EDID पूर्णांकo three places used by various parts of fbdev:
 * fb_var_screeninfo contains the timing of the monitor's preferred mode
 * fb_info.monspecs is full parsed EDID info, including monspecs.modedb
 * fb_info.modelist is a linked list of all monitor & VESA modes which work
 *
 * If EDID is not पढ़ोable/valid, then modelist is all VESA modes,
 * monspecs is शून्य, and fb_var_screeninfo is set to safe VESA mode
 * Returns 0 अगर successful */
अटल पूर्णांक ufx_setup_modes(काष्ठा ufx_data *dev, काष्ठा fb_info *info,
	अक्षर *शेष_edid, माप_प्रकार शेष_edid_size)
अणु
	स्थिर काष्ठा fb_videomode *शेष_vmode = शून्य;
	u8 *edid;
	पूर्णांक i, result = 0, tries = 3;

	अगर (info->dev) /* only use mutex अगर info has been रेजिस्टरed */
		mutex_lock(&info->lock);

	edid = kदो_स्मृति(EDID_LENGTH, GFP_KERNEL);
	अगर (!edid) अणु
		result = -ENOMEM;
		जाओ error;
	पूर्ण

	fb_destroy_modelist(&info->modelist);
	स_रखो(&info->monspecs, 0, माप(info->monspecs));

	/* Try to (re)पढ़ो EDID from hardware first
	 * EDID data may वापस, but not parse as valid
	 * Try again a few बार, in हाल of e.g. analog cable noise */
	जबतक (tries--) अणु
		i = ufx_पढ़ो_edid(dev, edid, EDID_LENGTH);

		अगर (i >= EDID_LENGTH)
			fb_edid_to_monspecs(edid, &info->monspecs);

		अगर (info->monspecs.modedb_len > 0) अणु
			dev->edid = edid;
			dev->edid_size = i;
			अवरोध;
		पूर्ण
	पूर्ण

	/* If that fails, use a previously वापसed EDID अगर available */
	अगर (info->monspecs.modedb_len == 0) अणु
		pr_err("Unable to get valid EDID from device/display\n");

		अगर (dev->edid) अणु
			fb_edid_to_monspecs(dev->edid, &info->monspecs);
			अगर (info->monspecs.modedb_len > 0)
				pr_err("Using previously queried EDID\n");
		पूर्ण
	पूर्ण

	/* If that fails, use the शेष EDID we were handed */
	अगर (info->monspecs.modedb_len == 0) अणु
		अगर (शेष_edid_size >= EDID_LENGTH) अणु
			fb_edid_to_monspecs(शेष_edid, &info->monspecs);
			अगर (info->monspecs.modedb_len > 0) अणु
				स_नकल(edid, शेष_edid, शेष_edid_size);
				dev->edid = edid;
				dev->edid_size = शेष_edid_size;
				pr_err("Using default/backup EDID\n");
			पूर्ण
		पूर्ण
	पूर्ण

	/* If we've got modes, let's pick a best शेष mode */
	अगर (info->monspecs.modedb_len > 0) अणु

		क्रम (i = 0; i < info->monspecs.modedb_len; i++) अणु
			अगर (ufx_is_valid_mode(&info->monspecs.modedb[i], info))
				fb_add_videomode(&info->monspecs.modedb[i],
					&info->modelist);
			अन्यथा /* अगर we've हटाओd top/best mode */
				info->monspecs.misc &= ~FB_MISC_1ST_DETAIL;
		पूर्ण

		शेष_vmode = fb_find_best_display(&info->monspecs,
						     &info->modelist);
	पूर्ण

	/* If everything अन्यथा has failed, fall back to safe शेष mode */
	अगर (शेष_vmode == शून्य) अणु

		काष्ठा fb_videomode fb_vmode = अणु0पूर्ण;

		/* Add the standard VESA modes to our modelist
		 * Since we करोn't have EDID, there may be modes that
		 * overspec monitor and/or are incorrect aspect ratio, etc.
		 * But at least the user has a chance to choose
		 */
		क्रम (i = 0; i < VESA_MODEDB_SIZE; i++) अणु
			अगर (ufx_is_valid_mode((काष्ठा fb_videomode *)
						&vesa_modes[i], info))
				fb_add_videomode(&vesa_modes[i],
						 &info->modelist);
		पूर्ण

		/* शेष to resolution safe क्रम projectors
		 * (since they are most common हाल without EDID)
		 */
		fb_vmode.xres = 800;
		fb_vmode.yres = 600;
		fb_vmode.refresh = 60;
		शेष_vmode = fb_find_nearest_mode(&fb_vmode,
						     &info->modelist);
	पूर्ण

	/* If we have good mode and no active clients */
	अगर ((शेष_vmode != शून्य) && (dev->fb_count == 0)) अणु

		fb_videomode_to_var(&info->var, शेष_vmode);
		ufx_var_color_क्रमmat(&info->var);

		/* with mode size info, we can now alloc our framebuffer */
		स_नकल(&info->fix, &ufx_fix, माप(ufx_fix));
		info->fix.line_length = info->var.xres *
			(info->var.bits_per_pixel / 8);

		result = ufx_पुनः_स्मृति_framebuffer(dev, info);

	पूर्ण अन्यथा
		result = -EINVAL;

error:
	अगर (edid && (dev->edid != edid))
		kमुक्त(edid);

	अगर (info->dev)
		mutex_unlock(&info->lock);

	वापस result;
पूर्ण

अटल पूर्णांक ufx_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *usbdev;
	काष्ठा ufx_data *dev;
	काष्ठा fb_info *info;
	पूर्णांक retval;
	u32 id_rev, fpga_rev;

	/* usb initialization */
	usbdev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	BUG_ON(!usbdev);

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (dev == शून्य) अणु
		dev_err(&usbdev->dev, "ufx_usb_probe: failed alloc of dev struct\n");
		वापस -ENOMEM;
	पूर्ण

	/* we need to रुको क्रम both usb and fbdev to spin करोwn on disconnect */
	kref_init(&dev->kref); /* matching kref_put in usb .disconnect fn */
	kref_get(&dev->kref); /* matching kref_put in मुक्त_framebuffer_work */

	dev->udev = usbdev;
	dev->gdev = &usbdev->dev; /* our generic काष्ठा device * */
	usb_set_पूर्णांकfdata(पूर्णांकerface, dev);

	dev_dbg(dev->gdev, "%s %s - serial #%s\n",
		usbdev->manufacturer, usbdev->product, usbdev->serial);
	dev_dbg(dev->gdev, "vid_%04x&pid_%04x&rev_%04x driver's ufx_data struct at %p\n",
		le16_to_cpu(usbdev->descriptor.idVenकरोr),
		le16_to_cpu(usbdev->descriptor.idProduct),
		le16_to_cpu(usbdev->descriptor.bcdDevice), dev);
	dev_dbg(dev->gdev, "console enable=%d\n", console);
	dev_dbg(dev->gdev, "fb_defio enable=%d\n", fb_defio);

	अगर (!ufx_alloc_urb_list(dev, WRITES_IN_FLIGHT, MAX_TRANSFER)) अणु
		dev_err(dev->gdev, "ufx_alloc_urb_list failed\n");
		जाओ e_nomem;
	पूर्ण

	/* We करोn't रेजिस्टर a new USB class. Our client पूर्णांकerface is fbdev */

	/* allocates framebuffer driver काष्ठाure, not framebuffer memory */
	info = framebuffer_alloc(0, &usbdev->dev);
	अगर (!info)
		जाओ e_nomem;

	dev->info = info;
	info->par = dev;
	info->pseuकरो_palette = dev->pseuकरो_palette;
	info->fbops = &ufx_ops;

	retval = fb_alloc_cmap(&info->cmap, 256, 0);
	अगर (retval < 0) अणु
		dev_err(dev->gdev, "fb_alloc_cmap failed %x\n", retval);
		जाओ destroy_modedb;
	पूर्ण

	INIT_DELAYED_WORK(&dev->मुक्त_framebuffer_work,
			  ufx_मुक्त_framebuffer_work);

	INIT_LIST_HEAD(&info->modelist);

	retval = ufx_reg_पढ़ो(dev, 0x3000, &id_rev);
	check_warn_जाओ_error(retval, "error %d reading 0x3000 register from device", retval);
	dev_dbg(dev->gdev, "ID_REV register value 0x%08x", id_rev);

	retval = ufx_reg_पढ़ो(dev, 0x3004, &fpga_rev);
	check_warn_जाओ_error(retval, "error %d reading 0x3004 register from device", retval);
	dev_dbg(dev->gdev, "FPGA_REV register value 0x%08x", fpga_rev);

	dev_dbg(dev->gdev, "resetting device");
	retval = ufx_lite_reset(dev);
	check_warn_जाओ_error(retval, "error %d resetting device", retval);

	dev_dbg(dev->gdev, "configuring system clock");
	retval = ufx_config_sys_clk(dev);
	check_warn_जाओ_error(retval, "error %d configuring system clock", retval);

	dev_dbg(dev->gdev, "configuring DDR2 controller");
	retval = ufx_config_ddr2(dev);
	check_warn_जाओ_error(retval, "error %d initialising DDR2 controller", retval);

	dev_dbg(dev->gdev, "configuring I2C controller");
	retval = ufx_i2c_init(dev);
	check_warn_जाओ_error(retval, "error %d initialising I2C controller", retval);

	dev_dbg(dev->gdev, "selecting display mode");
	retval = ufx_setup_modes(dev, info, शून्य, 0);
	check_warn_जाओ_error(retval, "unable to find common mode for display and adapter");

	retval = ufx_reg_set_bits(dev, 0x4000, 0x00000001);
	check_warn_जाओ_error(retval, "error %d enabling graphics engine", retval);

	/* पढ़ोy to begin using device */
	atomic_set(&dev->usb_active, 1);

	dev_dbg(dev->gdev, "checking var");
	retval = ufx_ops_check_var(&info->var, info);
	check_warn_जाओ_error(retval, "error %d ufx_ops_check_var", retval);

	dev_dbg(dev->gdev, "setting par");
	retval = ufx_ops_set_par(info);
	check_warn_जाओ_error(retval, "error %d ufx_ops_set_par", retval);

	dev_dbg(dev->gdev, "registering framebuffer");
	retval = रेजिस्टर_framebuffer(info);
	check_warn_जाओ_error(retval, "error %d register_framebuffer", retval);

	dev_info(dev->gdev, "SMSC UDX USB device /dev/fb%d attached. %dx%d resolution."
		" Using %dK framebuffer memory\n", info->node,
		info->var.xres, info->var.yres, info->fix.smem_len >> 10);

	वापस 0;

error:
	fb_dealloc_cmap(&info->cmap);
destroy_modedb:
	fb_destroy_modedb(info->monspecs.modedb);
	vमुक्त(info->screen_base);
	fb_destroy_modelist(&info->modelist);
	framebuffer_release(info);
put_ref:
	kref_put(&dev->kref, ufx_मुक्त); /* ref क्रम framebuffer */
	kref_put(&dev->kref, ufx_मुक्त); /* last ref from kref_init */
	वापस retval;

e_nomem:
	retval = -ENOMEM;
	जाओ put_ref;
पूर्ण

अटल व्योम ufx_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा ufx_data *dev;

	dev = usb_get_पूर्णांकfdata(पूर्णांकerface);

	pr_debug("USB disconnect starting\n");

	/* we भवize until all fb clients release. Then we मुक्त */
	dev->भवized = true;

	/* When non-active we'll update भव framebuffer, but no new urbs */
	atomic_set(&dev->usb_active, 0);

	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);

	/* अगर clients still have us खोलो, will be मुक्तd on last बंद */
	अगर (dev->fb_count == 0)
		schedule_delayed_work(&dev->मुक्त_framebuffer_work, 0);

	/* release reference taken by kref_init in probe() */
	kref_put(&dev->kref, ufx_मुक्त);

	/* consider ufx_data मुक्तd */
पूर्ण

अटल काष्ठा usb_driver ufx_driver = अणु
	.name = "smscufx",
	.probe = ufx_usb_probe,
	.disconnect = ufx_usb_disconnect,
	.id_table = id_table,
पूर्ण;

module_usb_driver(ufx_driver);

अटल व्योम ufx_urb_completion(काष्ठा urb *urb)
अणु
	काष्ठा urb_node *unode = urb->context;
	काष्ठा ufx_data *dev = unode->dev;
	अचिन्हित दीर्घ flags;

	/* sync/async unlink faults aren't errors */
	अगर (urb->status) अणु
		अगर (!(urb->status == -ENOENT ||
		    urb->status == -ECONNRESET ||
		    urb->status == -ESHUTDOWN)) अणु
			pr_err("%s - nonzero write bulk status received: %d\n",
				__func__, urb->status);
			atomic_set(&dev->lost_pixels, 1);
		पूर्ण
	पूर्ण

	urb->transfer_buffer_length = dev->urbs.size; /* reset to actual */

	spin_lock_irqsave(&dev->urbs.lock, flags);
	list_add_tail(&unode->entry, &dev->urbs.list);
	dev->urbs.available++;
	spin_unlock_irqrestore(&dev->urbs.lock, flags);

	/* When using fb_defio, we deadlock अगर up() is called
	 * जबतक another is रुकोing. So queue to another process */
	अगर (fb_defio)
		schedule_delayed_work(&unode->release_urb_work, 0);
	अन्यथा
		up(&dev->urbs.limit_sem);
पूर्ण

अटल व्योम ufx_मुक्त_urb_list(काष्ठा ufx_data *dev)
अणु
	पूर्णांक count = dev->urbs.count;
	काष्ठा list_head *node;
	काष्ठा urb_node *unode;
	काष्ठा urb *urb;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	pr_debug("Waiting for completes and freeing all render urbs\n");

	/* keep रुकोing and मुक्तing, until we've got 'em all */
	जबतक (count--) अणु
		/* Getting पूर्णांकerrupted means a leak, but ok at shutकरोwn*/
		ret = करोwn_पूर्णांकerruptible(&dev->urbs.limit_sem);
		अगर (ret)
			अवरोध;

		spin_lock_irqsave(&dev->urbs.lock, flags);

		node = dev->urbs.list.next; /* have reserved one with sem */
		list_del_init(node);

		spin_unlock_irqrestore(&dev->urbs.lock, flags);

		unode = list_entry(node, काष्ठा urb_node, entry);
		urb = unode->urb;

		/* Free each separately allocated piece */
		usb_मुक्त_coherent(urb->dev, dev->urbs.size,
				  urb->transfer_buffer, urb->transfer_dma);
		usb_मुक्त_urb(urb);
		kमुक्त(node);
	पूर्ण
पूर्ण

अटल पूर्णांक ufx_alloc_urb_list(काष्ठा ufx_data *dev, पूर्णांक count, माप_प्रकार size)
अणु
	पूर्णांक i = 0;
	काष्ठा urb *urb;
	काष्ठा urb_node *unode;
	अक्षर *buf;

	spin_lock_init(&dev->urbs.lock);

	dev->urbs.size = size;
	INIT_LIST_HEAD(&dev->urbs.list);

	जबतक (i < count) अणु
		unode = kzalloc(माप(*unode), GFP_KERNEL);
		अगर (!unode)
			अवरोध;
		unode->dev = dev;

		INIT_DELAYED_WORK(&unode->release_urb_work,
			  ufx_release_urb_work);

		urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!urb) अणु
			kमुक्त(unode);
			अवरोध;
		पूर्ण
		unode->urb = urb;

		buf = usb_alloc_coherent(dev->udev, size, GFP_KERNEL,
					 &urb->transfer_dma);
		अगर (!buf) अणु
			kमुक्त(unode);
			usb_मुक्त_urb(urb);
			अवरोध;
		पूर्ण

		/* urb->transfer_buffer_length set to actual beक्रमe submit */
		usb_fill_bulk_urb(urb, dev->udev, usb_sndbulkpipe(dev->udev, 1),
			buf, size, ufx_urb_completion, unode);
		urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

		list_add_tail(&unode->entry, &dev->urbs.list);

		i++;
	पूर्ण

	sema_init(&dev->urbs.limit_sem, i);
	dev->urbs.count = i;
	dev->urbs.available = i;

	pr_debug("allocated %d %d byte urbs\n", i, (पूर्णांक) size);

	वापस i;
पूर्ण

अटल काष्ठा urb *ufx_get_urb(काष्ठा ufx_data *dev)
अणु
	पूर्णांक ret = 0;
	काष्ठा list_head *entry;
	काष्ठा urb_node *unode;
	काष्ठा urb *urb = शून्य;
	अचिन्हित दीर्घ flags;

	/* Wait क्रम an in-flight buffer to complete and get re-queued */
	ret = करोwn_समयout(&dev->urbs.limit_sem, GET_URB_TIMEOUT);
	अगर (ret) अणु
		atomic_set(&dev->lost_pixels, 1);
		pr_warn("wait for urb interrupted: %x available: %d\n",
		       ret, dev->urbs.available);
		जाओ error;
	पूर्ण

	spin_lock_irqsave(&dev->urbs.lock, flags);

	BUG_ON(list_empty(&dev->urbs.list)); /* reserved one with limit_sem */
	entry = dev->urbs.list.next;
	list_del_init(entry);
	dev->urbs.available--;

	spin_unlock_irqrestore(&dev->urbs.lock, flags);

	unode = list_entry(entry, काष्ठा urb_node, entry);
	urb = unode->urb;

error:
	वापस urb;
पूर्ण

अटल पूर्णांक ufx_submit_urb(काष्ठा ufx_data *dev, काष्ठा urb *urb, माप_प्रकार len)
अणु
	पूर्णांक ret;

	BUG_ON(len > dev->urbs.size);

	urb->transfer_buffer_length = len; /* set to actual payload len */
	ret = usb_submit_urb(urb, GFP_KERNEL);
	अगर (ret) अणु
		ufx_urb_completion(urb); /* because no one अन्यथा will */
		atomic_set(&dev->lost_pixels, 1);
		pr_err("usb_submit_urb error %x\n", ret);
	पूर्ण
	वापस ret;
पूर्ण

module_param(console, bool, S_IWUSR | S_IRUSR | S_IWGRP | S_IRGRP);
MODULE_PARM_DESC(console, "Allow fbcon to be used on this display");

module_param(fb_defio, bool, S_IWUSR | S_IRUSR | S_IWGRP | S_IRGRP);
MODULE_PARM_DESC(fb_defio, "Enable fb_defio mmap support");

MODULE_AUTHOR("Steve Glendinning <steve.glendinning@shawell.net>");
MODULE_DESCRIPTION("SMSC UFX kernel framebuffer driver");
MODULE_LICENSE("GPL");
