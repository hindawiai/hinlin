<शैली गुरु>
/*
 *  linux/drivers/video/fm2fb.c -- BSC FrameMaster II/Rainbow II frame buffer
 *				   device
 *
 *	Copyright (C) 1998 Steffen A. Mork (linux-dev@morknet.de)
 *	Copyright (C) 1999 Geert Uytterhoeven
 *
 *  Written क्रम 2.0.x by Steffen A. Mork
 *  Ported to 2.1.x by Geert Uytterhoeven
 *  Ported to new api by James Simmons
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/zorro.h>
#समावेश <यंत्र/पन.स>

/*
 *	Some technical notes:
 *
 *	The BSC FrameMaster II (or Rainbow II) is a simple very dumb
 *	frame buffer which allows to display 24 bit true color images.
 *	Each pixel is 32 bit width so it's very easy to मुख्यtain the
 *	frame buffer. One दीर्घ word has the following layout:
 *	AARRGGBB which means: AA the alpha channel byte, RR the red
 *	channel, GG the green channel and BB the blue channel.
 *
 *	The FrameMaster II supports the following video modes.
 *	- PAL/NTSC
 *	- पूर्णांकerlaced/non पूर्णांकerlaced
 *	- composite sync/sync/sync over green
 *
 *	The resolution is to the following both ones:
 *	- 768x576 (PAL)
 *	- 768x480 (NTSC)
 *
 *	This means that pixel access per line is fixed due to the
 *	fixed line width. In हाल of maximal resolution the frame
 *	buffer needs an amount of memory of 1.769.472 bytes which
 *	is near to 2 MByte (the allocated address space of Zorro2).
 *	The memory is channel पूर्णांकerleaved. That means every channel
 *	owns four VRAMs. Unक्रमtunately most FrameMasters II are
 *	not assembled with memory क्रम the alpha channel. In this
 *	हाल it could be possible to add the frame buffer पूर्णांकo the
 *	normal memory pool.
 *
 *	At relative address 0x1ffff8 of the frame buffers base address
 *	there exists a control रेजिस्टर with the number of
 *	four control bits. They have the following meaning:
 *	bit value meaning
 *
 *	 0    1   0=पूर्णांकerlaced/1=non पूर्णांकerlaced
 *	 1    2   0=video out disabled/1=video out enabled
 *	 2    4   0=normal mode as jumpered via JP8/1=complement mode
 *	 3    8   0=पढ़ो  onboard ROM/1 normal operation (required)
 *
 *	As mentioned above there are several jumper. I think there
 *	is not very much inक्रमmation about the FrameMaster II in
 *	the world so I add these inक्रमmation क्रम completeness.
 *
 *	JP1  पूर्णांकerlace selection (1-2 non पूर्णांकerlaced/2-3 पूर्णांकerlaced)
 *	JP2  रुको state creation (leave as is!)
 *	JP3  रुको state creation (leave as is!)
 *	JP4  modulate composite sync on green output (1-2 composite
 *	     sync on green channel/2-3 normal composite sync)
 *	JP5  create test संकेत, लघुing this jumper will create
 *	     a white screen
 *	JP6  sync creation (1-2 composite sync/2-3 H-sync output)
 *	JP8  video mode (1-2 PAL/2-3 NTSC)
 *
 *	With the following jumpering table you can connect the
 *	FrameMaster II to a normal TV via SCART connector:
 *	JP1:  2-3
 *	JP4:  2-3
 *	JP6:  2-3
 *	JP8:  1-2 (means PAL क्रम Europe)
 *
 *	NOTE:
 *	There is no other possibility to change the video timings
 *	except the पूर्णांकerlaced/non पूर्णांकerlaced, sync control and the
 *	video mode PAL (50 Hz)/NTSC (60 Hz). Inside this
 *	FrameMaster II driver are assumed values to aव्योम anomalies
 *	to a future X server. Except the pixel घड़ी is really
 *	स्थिरant at 30 MHz.
 *
 *	9 pin female video connector:
 *
 *	1  analog red 0.7 Vss
 *	2  analog green 0.7 Vss
 *	3  analog blue 0.7 Vss
 *	4  H-sync TTL
 *	5  V-sync TTL
 *	6  ground
 *	7  ground
 *	8  ground
 *	9  ground
 *
 *	Some perक्रमmance notes:
 *	The FrameMaster II was not deचिन्हित to display a console
 *	this driver would करो! It was deचिन्हित to display still true
 *	color images. Imagine: When scroll up a text line there
 *	must copied ca. 1.7 MBytes to another place inside this
 *	frame buffer. This means 1.7 MByte पढ़ो and 1.7 MByte ग_लिखो
 *	over the slow 16 bit wide Zorro2 bus! A scroll of one
 *	line needs 1 second so करो not expect to much from this
 *	driver - he is at the limit!
 *
 */

/*
 *	definitions
 */

#घोषणा FRAMEMASTER_SIZE	0x200000
#घोषणा FRAMEMASTER_REG		0x1ffff8

#घोषणा FRAMEMASTER_NOLACE	1
#घोषणा FRAMEMASTER_ENABLE	2
#घोषणा FRAMEMASTER_COMPL	4
#घोषणा FRAMEMASTER_ROM		8

अटल अस्थिर अचिन्हित अक्षर *fm2fb_reg;

अटल काष्ठा fb_fix_screeninfo fb_fix = अणु
	.smem_len =	FRAMEMASTER_REG,
	.type =		FB_TYPE_PACKED_PIXELS,
	.visual =	FB_VISUAL_TRUECOLOR,
	.line_length =	(768 << 2),
	.mmio_len =	(8),
	.accel =	FB_ACCEL_NONE,
पूर्ण;

अटल पूर्णांक fm2fb_mode = -1;

#घोषणा FM2FB_MODE_PAL	0
#घोषणा FM2FB_MODE_NTSC	1

अटल काष्ठा fb_var_screeninfo fb_var_modes[] = अणु
    अणु
	/* 768 x 576, 32 bpp (PAL) */
	768, 576, 768, 576, 0, 0, 32, 0,
	अणु 16, 8, 0 पूर्ण, अणु 8, 8, 0 पूर्ण, अणु 0, 8, 0 पूर्ण, अणु 24, 8, 0 पूर्ण,
	0, FB_ACTIVATE_NOW, -1, -1, FB_ACCEL_NONE,
	33333, 10, 102, 10, 5, 80, 34, FB_SYNC_COMP_HIGH_ACT, 0
    पूर्ण, अणु
	/* 768 x 480, 32 bpp (NTSC - not supported yet */
	768, 480, 768, 480, 0, 0, 32, 0,
	अणु 16, 8, 0 पूर्ण, अणु 8, 8, 0 पूर्ण, अणु 0, 8, 0 पूर्ण, अणु 24, 8, 0 पूर्ण,
	0, FB_ACTIVATE_NOW, -1, -1, FB_ACCEL_NONE,
	33333, 10, 102, 10, 5, 80, 34, FB_SYNC_COMP_HIGH_ACT, 0
    पूर्ण
पूर्ण;

    /*
     *  Interface used by the world
     */

अटल पूर्णांक fm2fb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
                           u_पूर्णांक transp, काष्ठा fb_info *info);
अटल पूर्णांक fm2fb_blank(पूर्णांक blank, काष्ठा fb_info *info);

अटल स्थिर काष्ठा fb_ops fm2fb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_setcolreg	= fm2fb_setcolreg,
	.fb_blank	= fm2fb_blank,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

    /*
     *  Blank the display.
     */
अटल पूर्णांक fm2fb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	अचिन्हित अक्षर t = FRAMEMASTER_ROM;

	अगर (!blank)
		t |= FRAMEMASTER_ENABLE | FRAMEMASTER_NOLACE;
	fm2fb_reg[0] = t;
	वापस 0;
पूर्ण

    /*
     *  Set a single color रेजिस्टर. The values supplied are alपढ़ोy
     *  rounded करोwn to the hardware's capabilities (according to the
     *  entries in the var काष्ठाure). Return != 0 क्रम invalid regno.
     */
अटल पूर्णांक fm2fb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
                         u_पूर्णांक transp, काष्ठा fb_info *info)
अणु
	अगर (regno < 16) अणु
		red >>= 8;
		green >>= 8;
		blue >>= 8;

		((u32*)(info->pseuकरो_palette))[regno] = (red << 16) |
			(green << 8) | blue;
	पूर्ण

	वापस 0;
पूर्ण

    /*
     *  Initialisation
     */

अटल पूर्णांक fm2fb_probe(काष्ठा zorro_dev *z, स्थिर काष्ठा zorro_device_id *id);

अटल स्थिर काष्ठा zorro_device_id fm2fb_devices[] = अणु
	अणु ZORRO_PROD_BSC_FRAMEMASTER_II पूर्ण,
	अणु ZORRO_PROD_HELFRICH_RAINBOW_II पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(zorro, fm2fb_devices);

अटल काष्ठा zorro_driver fm2fb_driver = अणु
	.name		= "fm2fb",
	.id_table	= fm2fb_devices,
	.probe		= fm2fb_probe,
पूर्ण;

अटल पूर्णांक fm2fb_probe(काष्ठा zorro_dev *z, स्थिर काष्ठा zorro_device_id *id)
अणु
	काष्ठा fb_info *info;
	अचिन्हित दीर्घ *ptr;
	पूर्णांक is_fm;
	पूर्णांक x, y;

	is_fm = z->id == ZORRO_PROD_BSC_FRAMEMASTER_II;

	अगर (!zorro_request_device(z,"fm2fb"))
		वापस -ENXIO;

	info = framebuffer_alloc(16 * माप(u32), &z->dev);
	अगर (!info) अणु
		zorro_release_device(z);
		वापस -ENOMEM;
	पूर्ण

	अगर (fb_alloc_cmap(&info->cmap, 256, 0) < 0) अणु
		framebuffer_release(info);
		zorro_release_device(z);
		वापस -ENOMEM;
	पूर्ण

	/* assigning memory to kernel space */
	fb_fix.smem_start = zorro_resource_start(z);
	info->screen_base = ioremap(fb_fix.smem_start, FRAMEMASTER_SIZE);
	fb_fix.mmio_start = fb_fix.smem_start + FRAMEMASTER_REG;
	fm2fb_reg  = (अचिन्हित अक्षर *)(info->screen_base+FRAMEMASTER_REG);

	म_नकल(fb_fix.id, is_fm ? "FrameMaster II" : "Rainbow II");

	/* make EBU color bars on display */
	ptr = (अचिन्हित दीर्घ *)fb_fix.smem_start;
	क्रम (y = 0; y < 576; y++) अणु
		क्रम (x = 0; x < 96; x++) *ptr++ = 0xffffff;/* white */
		क्रम (x = 0; x < 96; x++) *ptr++ = 0xffff00;/* yellow */
		क्रम (x = 0; x < 96; x++) *ptr++ = 0x00ffff;/* cyan */
		क्रम (x = 0; x < 96; x++) *ptr++ = 0x00ff00;/* green */
		क्रम (x = 0; x < 96; x++) *ptr++ = 0xff00ff;/* magenta */
		क्रम (x = 0; x < 96; x++) *ptr++ = 0xff0000;/* red */
		क्रम (x = 0; x < 96; x++) *ptr++ = 0x0000ff;/* blue */
		क्रम (x = 0; x < 96; x++) *ptr++ = 0x000000;/* black */
	पूर्ण
	fm2fb_blank(0, info);

	अगर (fm2fb_mode == -1)
		fm2fb_mode = FM2FB_MODE_PAL;

	info->fbops = &fm2fb_ops;
	info->var = fb_var_modes[fm2fb_mode];
	info->pseuकरो_palette = info->par;
	info->par = शून्य;
	info->fix = fb_fix;
	info->flags = FBINFO_DEFAULT;

	अगर (रेजिस्टर_framebuffer(info) < 0) अणु
		fb_dealloc_cmap(&info->cmap);
		iounmap(info->screen_base);
		framebuffer_release(info);
		zorro_release_device(z);
		वापस -EINVAL;
	पूर्ण
	fb_info(info, "%s frame buffer device\n", fb_fix.id);
	वापस 0;
पूर्ण

पूर्णांक __init fm2fb_setup(अक्षर *options)
अणु
	अक्षर *this_opt;

	अगर (!options || !*options)
		वापस 0;

	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!म_भेदन(this_opt, "pal", 3))
			fm2fb_mode = FM2FB_MODE_PAL;
		अन्यथा अगर (!म_भेदन(this_opt, "ntsc", 4))
			fm2fb_mode = FM2FB_MODE_NTSC;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक __init fm2fb_init(व्योम)
अणु
	अक्षर *option = शून्य;

	अगर (fb_get_options("fm2fb", &option))
		वापस -ENODEV;
	fm2fb_setup(option);
	वापस zorro_रेजिस्टर_driver(&fm2fb_driver);
पूर्ण

module_init(fm2fb_init);
MODULE_LICENSE("GPL");
