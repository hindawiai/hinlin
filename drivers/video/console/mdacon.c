<शैली गुरु>
/*
 *  linux/drivers/video/mdacon.c -- Low level MDA based console driver
 *
 *	(c) 1998 Andrew Apted <ajapted@netspace.net.au>
 *
 *      including portions (c) 1995-1998 Patrick Caulfield.
 *
 *      slight improvements (c) 2000 Edward Betts <edward@debian.org>
 *
 *  This file is based on the VGA console driver (vgacon.c):
 *	
 *	Created 28 Sep 1997 by Geert Uytterhoeven
 *
 *	Rewritten by Martin Mares <mj@ucw.cz>, July 1998
 *
 *  and on the old console.c, vga.c and vesa_blank.c drivers:
 *
 *	Copyright (C) 1991, 1992  Linus Torvalds
 *			    1995  Jay Estabrook
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 *
 *  Changelog:
 *  Paul G. (03/2001) Fix mdacon= boot prompt to use __setup().
 */

#समावेश <linux/types.h>
#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/console.h>
#समावेश <linux/माला.स>
#समावेश <linux/kd.h>
#समावेश <linux/vt_kern.h>
#समावेश <linux/vt_buffer.h>
#समावेश <linux/selection.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/vga.h>

अटल DEFINE_SPINLOCK(mda_lock);

/* description of the hardware layout */

अटल u16		*mda_vram_base;		/* Base of video memory */
अटल अचिन्हित दीर्घ	mda_vram_len;		/* Size of video memory */
अटल अचिन्हित पूर्णांक	mda_num_columns;	/* Number of text columns */
अटल अचिन्हित पूर्णांक	mda_num_lines;		/* Number of text lines */

अटल अचिन्हित पूर्णांक	mda_index_port;		/* Register select port */
अटल अचिन्हित पूर्णांक	mda_value_port;		/* Register value port */
अटल अचिन्हित पूर्णांक	mda_mode_port;		/* Mode control port */
अटल अचिन्हित पूर्णांक	mda_status_port;	/* Status and Config port */
अटल अचिन्हित पूर्णांक	mda_gfx_port;		/* Graphics control port */

/* current hardware state */

अटल पूर्णांक	mda_cursor_loc=-1;
अटल पूर्णांक	mda_cursor_size_from=-1;
अटल पूर्णांक	mda_cursor_माप_प्रकारo=-1;

अटल क्रमागत अणु TYPE_MDA, TYPE_HERC, TYPE_HERCPLUS, TYPE_HERCCOLOR पूर्ण mda_type;
अटल अक्षर *mda_type_name;

/* console inक्रमmation */

अटल पूर्णांक	mda_first_vc = 13;
अटल पूर्णांक	mda_last_vc  = 16;

अटल काष्ठा vc_data	*mda_display_fg = शून्य;

module_param(mda_first_vc, पूर्णांक, 0);
MODULE_PARM_DESC(mda_first_vc, "First virtual console. Default: 13");
module_param(mda_last_vc, पूर्णांक, 0);
MODULE_PARM_DESC(mda_last_vc, "Last virtual console. Default: 16");

/* MDA रेजिस्टर values
 */

#घोषणा MDA_CURSOR_BLINKING	0x00
#घोषणा MDA_CURSOR_OFF		0x20
#घोषणा MDA_CURSOR_SLOWBLINK	0x60

#घोषणा MDA_MODE_GRAPHICS	0x02
#घोषणा MDA_MODE_VIDEO_EN	0x08
#घोषणा MDA_MODE_BLINK_EN	0x20
#घोषणा MDA_MODE_GFX_PAGE1	0x80

#घोषणा MDA_STATUS_HSYNC	0x01
#घोषणा MDA_STATUS_VSYNC	0x80
#घोषणा MDA_STATUS_VIDEO	0x08

#घोषणा MDA_CONFIG_COL132	0x08
#घोषणा MDA_GFX_MODE_EN		0x01
#घोषणा MDA_GFX_PAGE_EN		0x02


/*
 * MDA could easily be classअगरied as "pre-dinosaur hardware".
 */

अटल व्योम ग_लिखो_mda_b(अचिन्हित पूर्णांक val, अचिन्हित अक्षर reg)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mda_lock, flags);	

	outb_p(reg, mda_index_port); 
	outb_p(val, mda_value_port);

	spin_unlock_irqrestore(&mda_lock, flags);
पूर्ण

अटल व्योम ग_लिखो_mda_w(अचिन्हित पूर्णांक val, अचिन्हित अक्षर reg)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mda_lock, flags);

	outb_p(reg,   mda_index_port); outb_p(val >> 8,   mda_value_port);
	outb_p(reg+1, mda_index_port); outb_p(val & 0xff, mda_value_port);

	spin_unlock_irqrestore(&mda_lock, flags);
पूर्ण

#अगर_घोषित TEST_MDA_B
अटल पूर्णांक test_mda_b(अचिन्हित अक्षर val, अचिन्हित अक्षर reg)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mda_lock, flags);

	outb_p(reg, mda_index_port); 
	outb  (val, mda_value_port);

	udelay(20); val = (inb_p(mda_value_port) == val);

	spin_unlock_irqrestore(&mda_lock, flags);
	वापस val;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम mda_set_cursor(अचिन्हित पूर्णांक location) 
अणु
	अगर (mda_cursor_loc == location)
		वापस;

	ग_लिखो_mda_w(location >> 1, 0x0e);

	mda_cursor_loc = location;
पूर्ण

अटल अंतरभूत व्योम mda_set_cursor_size(पूर्णांक from, पूर्णांक to)
अणु
	अगर (mda_cursor_size_from==from && mda_cursor_माप_प्रकारo==to)
		वापस;
	
	अगर (from > to) अणु
		ग_लिखो_mda_b(MDA_CURSOR_OFF, 0x0a);	/* disable cursor */
	पूर्ण अन्यथा अणु
		ग_लिखो_mda_b(from, 0x0a);	/* cursor start */
		ग_लिखो_mda_b(to,   0x0b);	/* cursor end */
	पूर्ण

	mda_cursor_size_from = from;
	mda_cursor_माप_प्रकारo   = to;
पूर्ण


#अगर_अघोषित MODULE
अटल पूर्णांक __init mdacon_setup(अक्षर *str)
अणु
	/* command line क्रमmat: mdacon=<first>,<last> */

	पूर्णांक पूर्णांकs[3];

	str = get_options(str, ARRAY_SIZE(पूर्णांकs), पूर्णांकs);

	अगर (पूर्णांकs[0] < 2)
		वापस 0;

	अगर (पूर्णांकs[1] < 1 || पूर्णांकs[1] > MAX_NR_CONSOLES || 
	    पूर्णांकs[2] < 1 || पूर्णांकs[2] > MAX_NR_CONSOLES)
		वापस 0;

	mda_first_vc = पूर्णांकs[1];
	mda_last_vc  = पूर्णांकs[2];
	वापस 1;
पूर्ण

__setup("mdacon=", mdacon_setup);
#पूर्ण_अगर

अटल पूर्णांक mda_detect(व्योम)
अणु
	पूर्णांक count=0;
	u16 *p, p_save;
	u16 *q, q_save;

	/* करो a memory check */

	p = mda_vram_base;
	q = mda_vram_base + 0x01000 / 2;

	p_save = scr_पढ़ोw(p);
	q_save = scr_पढ़ोw(q);

	scr_ग_लिखोw(0xAA55, p);
	अगर (scr_पढ़ोw(p) == 0xAA55)
		count++;

	scr_ग_लिखोw(0x55AA, p);
	अगर (scr_पढ़ोw(p) == 0x55AA)
		count++;

	scr_ग_लिखोw(p_save, p);

	अगर (count != 2) अणु
		वापस 0;
	पूर्ण

	/* check अगर we have 4K or 8K */

	scr_ग_लिखोw(0xA55A, q);
	scr_ग_लिखोw(0x0000, p);
	अगर (scr_पढ़ोw(q) == 0xA55A)
		count++;
	
	scr_ग_लिखोw(0x5AA5, q);
	scr_ग_लिखोw(0x0000, p);
	अगर (scr_पढ़ोw(q) == 0x5AA5)
		count++;

	scr_ग_लिखोw(p_save, p);
	scr_ग_लिखोw(q_save, q);
	
	अगर (count == 4) अणु
		mda_vram_len = 0x02000;
	पूर्ण
	
	/* Ok, there is definitely a card रेजिस्टरing at the correct
	 * memory location, so now we करो an I/O port test.
	 */

#अगर_घोषित TEST_MDA_B
	/* Edward: These two mess `tests' mess up my cursor on bootup */

	/* cursor low रेजिस्टर */
	अगर (!test_mda_b(0x66, 0x0f))
		वापस 0;

	/* cursor low रेजिस्टर */
	अगर (!test_mda_b(0x99, 0x0f))
		वापस 0;
#पूर्ण_अगर

	/* See अगर the card is a Hercules, by checking whether the vsync
	 * bit of the status रेजिस्टर is changing.  This test lasts क्रम
	 * approximately 1/10th of a second.
	 */
	
	p_save = q_save = inb_p(mda_status_port) & MDA_STATUS_VSYNC;

	क्रम (count = 0; count < 50000 && p_save == q_save; count++) अणु
		q_save = inb(mda_status_port) & MDA_STATUS_VSYNC;
		udelay(2);
	पूर्ण

	अगर (p_save != q_save) अणु
		चयन (inb_p(mda_status_port) & 0x70) अणु
		हाल 0x10:
			mda_type = TYPE_HERCPLUS;
			mda_type_name = "HerculesPlus";
			अवरोध;
		हाल 0x50:
			mda_type = TYPE_HERCCOLOR;
			mda_type_name = "HerculesColor";
			अवरोध;
		शेष:
			mda_type = TYPE_HERC;
			mda_type_name = "Hercules";
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम mda_initialize(व्योम)
अणु
	ग_लिखो_mda_b(97, 0x00);		/* horizontal total */
	ग_लिखो_mda_b(80, 0x01);		/* horizontal displayed */
	ग_लिखो_mda_b(82, 0x02);		/* horizontal sync pos */
	ग_लिखो_mda_b(15, 0x03);		/* horizontal sync width */

	ग_लिखो_mda_b(25, 0x04);		/* vertical total */
	ग_लिखो_mda_b(6,  0x05);		/* vertical total adjust */
	ग_लिखो_mda_b(25, 0x06);		/* vertical displayed */
	ग_लिखो_mda_b(25, 0x07);		/* vertical sync pos */

	ग_लिखो_mda_b(2,  0x08);		/* पूर्णांकerlace mode */
	ग_लिखो_mda_b(13, 0x09);		/* maximum scanline */
	ग_लिखो_mda_b(12, 0x0a);		/* cursor start */
	ग_लिखो_mda_b(13, 0x0b);		/* cursor end */

	ग_लिखो_mda_w(0x0000, 0x0c);	/* start address */
	ग_लिखो_mda_w(0x0000, 0x0e);	/* cursor location */

	outb_p(MDA_MODE_VIDEO_EN | MDA_MODE_BLINK_EN, mda_mode_port);
	outb_p(0x00, mda_status_port);
	outb_p(0x00, mda_gfx_port);
पूर्ण

अटल स्थिर अक्षर *mdacon_startup(व्योम)
अणु
	mda_num_columns = 80;
	mda_num_lines   = 25;

	mda_vram_len  = 0x01000;
	mda_vram_base = (u16 *)VGA_MAP_MEM(0xb0000, mda_vram_len);

	mda_index_port  = 0x3b4;
	mda_value_port  = 0x3b5;
	mda_mode_port   = 0x3b8;
	mda_status_port = 0x3ba;
	mda_gfx_port    = 0x3bf;

	mda_type = TYPE_MDA;
	mda_type_name = "MDA";

	अगर (! mda_detect()) अणु
		prपूर्णांकk("mdacon: MDA card not detected.\n");
		वापस शून्य;
	पूर्ण

	अगर (mda_type != TYPE_MDA) अणु
		mda_initialize();
	पूर्ण

	/* cursor looks ugly during boot-up, so turn it off */
	mda_set_cursor(mda_vram_len - 1);

	prपूर्णांकk("mdacon: %s with %ldK of memory detected.\n",
		mda_type_name, mda_vram_len/1024);

	वापस "MDA-2";
पूर्ण

अटल व्योम mdacon_init(काष्ठा vc_data *c, पूर्णांक init)
अणु
	c->vc_complement_mask = 0x0800;	 /* reverse video */
	c->vc_display_fg = &mda_display_fg;

	अगर (init) अणु
		c->vc_cols = mda_num_columns;
		c->vc_rows = mda_num_lines;
	पूर्ण अन्यथा
		vc_resize(c, mda_num_columns, mda_num_lines);

	/* make the first MDA console visible */

	अगर (mda_display_fg == शून्य)
		mda_display_fg = c;
पूर्ण

अटल व्योम mdacon_deinit(काष्ठा vc_data *c)
अणु
	/* con_set_शेष_unimap(c->vc_num); */

	अगर (mda_display_fg == c)
		mda_display_fg = शून्य;
पूर्ण

अटल अंतरभूत u16 mda_convert_attr(u16 ch)
अणु
	u16 attr = 0x0700;

	/* Underline and reverse-video are mutually exclusive on MDA.
	 * Since reverse-video is used क्रम cursors and selected areas,
	 * it takes precedence. 
	 */

	अगर (ch & 0x0800)	attr = 0x7000;	/* reverse */
	अन्यथा अगर (ch & 0x0400)	attr = 0x0100;	/* underline */

	वापस ((ch & 0x0200) << 2) | 		/* पूर्णांकensity */ 
		(ch & 0x8000) |			/* blink */ 
		(ch & 0x00ff) | attr;
पूर्ण

अटल u8 mdacon_build_attr(काष्ठा vc_data *c, u8 color,
			    क्रमागत vc_पूर्णांकensity पूर्णांकensity,
			    bool blink, bool underline, bool reverse,
			    bool italic)
अणु
	/* The attribute is just a bit vector:
	 *
	 *	Bit 0..1 : पूर्णांकensity (0..2)
	 *	Bit 2    : underline
	 *	Bit 3    : reverse
	 *	Bit 7    : blink
	 */

	वापस (पूर्णांकensity & VCI_MASK) |
		(underline << 2) |
		(reverse << 3) |
		(italic << 4) |
		(blink << 7);
पूर्ण

अटल व्योम mdacon_invert_region(काष्ठा vc_data *c, u16 *p, पूर्णांक count)
अणु
	क्रम (; count > 0; count--) अणु
		scr_ग_लिखोw(scr_पढ़ोw(p) ^ 0x0800, p);
		p++;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 *mda_addr(अचिन्हित पूर्णांक x, अचिन्हित पूर्णांक y)
अणु
	वापस mda_vram_base + y * mda_num_columns + x;
पूर्ण

अटल व्योम mdacon_अ_दो(काष्ठा vc_data *c, पूर्णांक ch, पूर्णांक y, पूर्णांक x)
अणु
	scr_ग_लिखोw(mda_convert_attr(ch), mda_addr(x, y));
पूर्ण

अटल व्योम mdacon_अ_दोs(काष्ठा vc_data *c, स्थिर अचिन्हित लघु *s,
		         पूर्णांक count, पूर्णांक y, पूर्णांक x)
अणु
	u16 *dest = mda_addr(x, y);

	क्रम (; count > 0; count--) अणु
		scr_ग_लिखोw(mda_convert_attr(scr_पढ़ोw(s++)), dest++);
	पूर्ण
पूर्ण

अटल व्योम mdacon_clear(काष्ठा vc_data *c, पूर्णांक y, पूर्णांक x, 
			  पूर्णांक height, पूर्णांक width)
अणु
	u16 *dest = mda_addr(x, y);
	u16 eattr = mda_convert_attr(c->vc_video_erase_अक्षर);

	अगर (width <= 0 || height <= 0)
		वापस;

	अगर (x==0 && width==mda_num_columns) अणु
		scr_स_रखोw(dest, eattr, height*width*2);
	पूर्ण अन्यथा अणु
		क्रम (; height > 0; height--, dest+=mda_num_columns)
			scr_स_रखोw(dest, eattr, width*2);
	पूर्ण
पूर्ण
                        
अटल पूर्णांक mdacon_चयन(काष्ठा vc_data *c)
अणु
	वापस 1;	/* redrawing needed */
पूर्ण

अटल पूर्णांक mdacon_blank(काष्ठा vc_data *c, पूर्णांक blank, पूर्णांक mode_चयन)
अणु
	अगर (mda_type == TYPE_MDA) अणु
		अगर (blank) 
			scr_स_रखोw(mda_vram_base,
				mda_convert_attr(c->vc_video_erase_अक्षर),
				c->vc_screenbuf_size);
		/* Tell console.c that it has to restore the screen itself */
		वापस 1;
	पूर्ण अन्यथा अणु
		अगर (blank)
			outb_p(0x00, mda_mode_port);	/* disable video */
		अन्यथा
			outb_p(MDA_MODE_VIDEO_EN | MDA_MODE_BLINK_EN, 
				mda_mode_port);
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम mdacon_cursor(काष्ठा vc_data *c, पूर्णांक mode)
अणु
	अगर (mode == CM_ERASE) अणु
		mda_set_cursor(mda_vram_len - 1);
		वापस;
	पूर्ण

	mda_set_cursor(c->state.y * mda_num_columns * 2 + c->state.x * 2);

	चयन (CUR_SIZE(c->vc_cursor_type)) अणु

		हाल CUR_LOWER_THIRD:	mda_set_cursor_size(10, 13); अवरोध;
		हाल CUR_LOWER_HALF:	mda_set_cursor_size(7,  13); अवरोध;
		हाल CUR_TWO_THIRDS:	mda_set_cursor_size(4,  13); अवरोध;
		हाल CUR_BLOCK:		mda_set_cursor_size(1,  13); अवरोध;
		हाल CUR_NONE:		mda_set_cursor_size(14, 13); अवरोध;
		शेष:		mda_set_cursor_size(12, 13); अवरोध;
	पूर्ण
पूर्ण

अटल bool mdacon_scroll(काष्ठा vc_data *c, अचिन्हित पूर्णांक t, अचिन्हित पूर्णांक b,
		क्रमागत con_scroll dir, अचिन्हित पूर्णांक lines)
अणु
	u16 eattr = mda_convert_attr(c->vc_video_erase_अक्षर);

	अगर (!lines)
		वापस false;

	अगर (lines > c->vc_rows)   /* maximum realistic size */
		lines = c->vc_rows;

	चयन (dir) अणु

	हाल SM_UP:
		scr_स_हटाओw(mda_addr(0, t), mda_addr(0, t + lines),
				(b-t-lines)*mda_num_columns*2);
		scr_स_रखोw(mda_addr(0, b - lines), eattr,
				lines*mda_num_columns*2);
		अवरोध;

	हाल SM_DOWN:
		scr_स_हटाओw(mda_addr(0, t + lines), mda_addr(0, t),
				(b-t-lines)*mda_num_columns*2);
		scr_स_रखोw(mda_addr(0, t), eattr, lines*mda_num_columns*2);
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण


/*
 *  The console `चयन' काष्ठाure क्रम the MDA based console
 */

अटल स्थिर काष्ठा consw mda_con = अणु
	.owner =		THIS_MODULE,
	.con_startup =		mdacon_startup,
	.con_init =		mdacon_init,
	.con_deinit =		mdacon_deinit,
	.con_clear =		mdacon_clear,
	.con_अ_दो =		mdacon_अ_दो,
	.con_अ_दोs =		mdacon_अ_दोs,
	.con_cursor =		mdacon_cursor,
	.con_scroll =		mdacon_scroll,
	.con_चयन =		mdacon_चयन,
	.con_blank =		mdacon_blank,
	.con_build_attr =	mdacon_build_attr,
	.con_invert_region =	mdacon_invert_region,
पूर्ण;

पूर्णांक __init mda_console_init(व्योम)
अणु
	पूर्णांक err;

	अगर (mda_first_vc > mda_last_vc)
		वापस 1;
	console_lock();
	err = करो_take_over_console(&mda_con, mda_first_vc-1, mda_last_vc-1, 0);
	console_unlock();
	वापस err;
पूर्ण

अटल व्योम __निकास mda_console_निकास(व्योम)
अणु
	give_up_console(&mda_con);
पूर्ण

module_init(mda_console_init);
module_निकास(mda_console_निकास);

MODULE_LICENSE("GPL");

