<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/amigahw.h>
#समावेश <यंत्र/amigaपूर्णांकs.h>
#समावेश <यंत्र/apollohw.h>
#समावेश <linux/fb.h>
#समावेश <linux/module.h>

/* apollo video HW definitions */

/*
 * Control Registers.   IOBASE + $x
 *
 * Note: these are the Memory/IO BASE definitions क्रम a mono card set to the
 * alternate address
 *
 * Control 3A and 3B serve identical functions except that 3A
 * deals with control 1 and 3b deals with Color LUT reg.
 */

#घोषणा AP_IOBASE       0x3b0	/* Base address of 1 plane board. */
#घोषणा AP_STATUS       isaIO2mem(AP_IOBASE+0)	/* Status रेजिस्टर.  Read */
#घोषणा AP_WRITE_ENABLE isaIO2mem(AP_IOBASE+0)	/* Write Enable Register Write */
#घोषणा AP_DEVICE_ID    isaIO2mem(AP_IOBASE+1)	/* Device ID Register. Read */
#घोषणा AP_ROP_1        isaIO2mem(AP_IOBASE+2)	/* Raster Operation reg. Write Word */
#घोषणा AP_DIAG_MEM_REQ isaIO2mem(AP_IOBASE+4)	/* Diagnostic Memory Request. Write Word */
#घोषणा AP_CONTROL_0    isaIO2mem(AP_IOBASE+8)	/* Control Register 0.  Read/Write */
#घोषणा AP_CONTROL_1    isaIO2mem(AP_IOBASE+0xa)	/* Control Register 1.  Read/Write */
#घोषणा AP_CONTROL_3A   isaIO2mem(AP_IOBASE+0xe)	/* Control Register 3a. Read/Write */
#घोषणा AP_CONTROL_2    isaIO2mem(AP_IOBASE+0xc)	/* Control Register 2. Read/Write */


#घोषणा FRAME_BUFFER_START 0x0FA0000
#घोषणा FRAME_BUFFER_LEN 0x40000

/* CREG 0 */
#घोषणा VECTOR_MODE 0x40	/* 010x.xxxx */
#घोषणा DBLT_MODE   0x80	/* 100x.xxxx */
#घोषणा NORMAL_MODE 0xE0	/* 111x.xxxx */
#घोषणा SHIFT_BITS  0x1F	/* xxx1.1111 */
	/* other bits are Shअगरt value */

/* CREG 1 */
#घोषणा AD_BLT      0x80	/* 1xxx.xxxx */
#घोषणा NORMAL      0x80 /* 1xxx.xxxx */	/* What is happening here ?? */
#घोषणा INVERSE     0x00 /* 0xxx.xxxx */	/* Clearing this reverses the screen */
#घोषणा PIX_BLT     0x00	/* 0xxx.xxxx */

#घोषणा AD_HIBIT        0x40	/* xIxx.xxxx */

#घोषणा ROP_EN          0x10	/* xxx1.xxxx */
#घोषणा DST_EQ_SRC      0x00	/* xxx0.xxxx */
#घोषणा nRESET_SYNC     0x08	/* xxxx.1xxx */
#घोषणा SYNC_ENAB       0x02	/* xxxx.xx1x */

#घोषणा BLANK_DISP      0x00	/* xxxx.xxx0 */
#घोषणा ENAB_DISP       0x01	/* xxxx.xxx1 */

#घोषणा NORM_CREG1      (nRESET_SYNC | SYNC_ENAB | ENAB_DISP)	/* no reset sync */

/* CREG 2 */

/*
 * Following 3 defines are common to 1, 4 and 8 plane.
 */

#घोषणा S_DATA_1s   0x00 /* 00xx.xxxx */	/* set source to all 1's -- vector drawing */
#घोषणा S_DATA_PIX  0x40 /* 01xx.xxxx */	/* takes source from ls-bits and replicates over 16 bits */
#घोषणा S_DATA_PLN  0xC0 /* 11xx.xxxx */	/* normal, each data access =16-bits in
						   one plane of image mem */

/* CREG 3A/CREG 3B */
#       define RESET_CREG 0x80	/* 1000.0000 */

/* ROP REG  -  all one nibble */
/*      ********* NOTE : this is used r0,r1,r2,r3 *********** */
#घोषणा ROP(r2,r3,r0,r1) ( (U_SHORT)((r0)|((r1)<<4)|((r2)<<8)|((r3)<<12)) )
#घोषणा DEST_ZERO               0x0
#घोषणा SRC_AND_DEST    0x1
#घोषणा SRC_AND_nDEST   0x2
#घोषणा SRC                             0x3
#घोषणा nSRC_AND_DEST   0x4
#घोषणा DEST                    0x5
#घोषणा SRC_XOR_DEST    0x6
#घोषणा SRC_OR_DEST             0x7
#घोषणा SRC_NOR_DEST    0x8
#घोषणा SRC_XNOR_DEST   0x9
#घोषणा nDEST                   0xA
#घोषणा SRC_OR_nDEST    0xB
#घोषणा nSRC                    0xC
#घोषणा nSRC_OR_DEST    0xD
#घोषणा SRC_न_अंकD_DEST   0xE
#घोषणा DEST_ONE                0xF

#घोषणा SWAP(A) ((A>>8) | ((A&0xff) <<8))

/* frame buffer operations */

अटल पूर्णांक dnfb_blank(पूर्णांक blank, काष्ठा fb_info *info);
अटल व्योम dnfb_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *area);

अटल स्थिर काष्ठा fb_ops dn_fb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_blank	= dnfb_blank,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= dnfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

अटल स्थिर काष्ठा fb_var_screeninfo dnfb_var = अणु
	.xres		= 1280,
	.yres		= 1024,
	.xres_भव	= 2048,
	.yres_भव	= 1024,
	.bits_per_pixel	= 1,
	.height		= -1,
	.width		= -1,
	.vmode		= FB_VMODE_NONINTERLACED,
पूर्ण;

अटल स्थिर काष्ठा fb_fix_screeninfo dnfb_fix = अणु
	.id		= "Apollo Mono",
	.smem_start	= (FRAME_BUFFER_START + IO_BASE),
	.smem_len	= FRAME_BUFFER_LEN,
	.type		= FB_TYPE_PACKED_PIXELS,
	.visual		= FB_VISUAL_MONO10,
	.line_length	= 256,
पूर्ण;

अटल पूर्णांक dnfb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	अगर (blank)
		out_8(AP_CONTROL_3A, 0x0);
	अन्यथा
		out_8(AP_CONTROL_3A, 0x1);
	वापस 0;
पूर्ण

अटल
व्योम dnfb_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *area)
अणु

	पूर्णांक incr, y_delta, pre_पढ़ो = 0, x_end, x_word_count;
	uपूर्णांक start_mask, end_mask, dest;
	uलघु *src, dummy;
	लघु i, j;

	incr = (area->dy <= area->sy) ? 1 : -1;

	src = (uलघु *)(info->screen_base + area->sy * info->fix.line_length +
			(area->sx >> 4));
	dest = area->dy * (info->fix.line_length >> 1) + (area->dx >> 4);

	अगर (incr > 0) अणु
		y_delta = (info->fix.line_length * 8) - area->sx - area->width;
		x_end = area->dx + area->width - 1;
		x_word_count = (x_end >> 4) - (area->dx >> 4) + 1;
		start_mask = 0xffff0000 >> (area->dx & 0xf);
		end_mask = 0x7ffff >> (x_end & 0xf);
		out_8(AP_CONTROL_0,
		     (((area->dx & 0xf) - (area->sx & 0xf)) % 16) | (0x4 << 5));
		अगर ((area->dx & 0xf) < (area->sx & 0xf))
			pre_पढ़ो = 1;
	पूर्ण अन्यथा अणु
		y_delta = -((info->fix.line_length * 8) - area->sx - area->width);
		x_end = area->dx - area->width + 1;
		x_word_count = (area->dx >> 4) - (x_end >> 4) + 1;
		start_mask = 0x7ffff >> (area->dx & 0xf);
		end_mask = 0xffff0000 >> (x_end & 0xf);
		out_8(AP_CONTROL_0,
		     ((-((area->sx & 0xf) - (area->dx & 0xf))) % 16) |
		     (0x4 << 5));
		अगर ((area->dx & 0xf) > (area->sx & 0xf))
			pre_पढ़ो = 1;
	पूर्ण

	क्रम (i = 0; i < area->height; i++) अणु

		out_8(AP_CONTROL_3A, 0xc | (dest >> 16));

		अगर (pre_पढ़ो) अणु
			dummy = *src;
			src += incr;
		पूर्ण

		अगर (x_word_count) अणु
			out_8(AP_WRITE_ENABLE, start_mask);
			*src = dest;
			src += incr;
			dest += incr;
			out_8(AP_WRITE_ENABLE, 0);

			क्रम (j = 1; j < (x_word_count - 1); j++) अणु
				*src = dest;
				src += incr;
				dest += incr;
			पूर्ण

			out_8(AP_WRITE_ENABLE, start_mask);
			*src = dest;
			dest += incr;
			src += incr;
		पूर्ण अन्यथा अणु
			out_8(AP_WRITE_ENABLE, start_mask | end_mask);
			*src = dest;
			dest += incr;
			src += incr;
		पूर्ण
		src += (y_delta / 16);
		dest += (y_delta / 16);
	पूर्ण
	out_8(AP_CONTROL_0, NORMAL_MODE);
पूर्ण

/*
 * Initialization
 */

अटल पूर्णांक dnfb_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fb_info *info;
	पूर्णांक err = 0;

	info = framebuffer_alloc(0, &dev->dev);
	अगर (!info)
		वापस -ENOMEM;

	info->fbops = &dn_fb_ops;
	info->fix = dnfb_fix;
	info->var = dnfb_var;
	info->var.red.length = 1;
	info->var.red.offset = 0;
	info->var.green = info->var.blue = info->var.red;
	info->screen_base = (u_अक्षर *) info->fix.smem_start;

	err = fb_alloc_cmap(&info->cmap, 2, 0);
	अगर (err < 0)
		जाओ release_framebuffer;

	err = रेजिस्टर_framebuffer(info);
	अगर (err < 0) अणु
		fb_dealloc_cmap(&info->cmap);
		जाओ release_framebuffer;
	पूर्ण
	platक्रमm_set_drvdata(dev, info);

	/* now we have रेजिस्टरed we can safely setup the hardware */
	out_8(AP_CONTROL_3A, RESET_CREG);
	out_be16(AP_WRITE_ENABLE, 0x0);
	out_8(AP_CONTROL_0, NORMAL_MODE);
	out_8(AP_CONTROL_1, (AD_BLT | DST_EQ_SRC | NORM_CREG1));
	out_8(AP_CONTROL_2, S_DATA_PLN);
	out_be16(AP_ROP_1, SWAP(0x3));

	prपूर्णांकk("apollo frame buffer alive and kicking !\n");
	वापस err;

release_framebuffer:
	framebuffer_release(info);
	वापस err;
पूर्ण

अटल काष्ठा platक्रमm_driver dnfb_driver = अणु
	.probe	= dnfb_probe,
	.driver	= अणु
		.name	= "dnfb",
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device dnfb_device = अणु
	.name	= "dnfb",
पूर्ण;

पूर्णांक __init dnfb_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!MACH_IS_APOLLO)
		वापस -ENODEV;

	अगर (fb_get_options("dnfb", शून्य))
		वापस -ENODEV;

	ret = platक्रमm_driver_रेजिस्टर(&dnfb_driver);

	अगर (!ret) अणु
		ret = platक्रमm_device_रेजिस्टर(&dnfb_device);
		अगर (ret)
			platक्रमm_driver_unरेजिस्टर(&dnfb_driver);
	पूर्ण
	वापस ret;
पूर्ण

module_init(dnfb_init);

MODULE_LICENSE("GPL");
