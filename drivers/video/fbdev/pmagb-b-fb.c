<शैली गुरु>
/*
 *	linux/drivers/video/pmagb-b-fb.c
 *
 *	PMAGB-B TURBOchannel Smart Frame Buffer (SFB) card support,
 *	derived from:
 *	"HP300 Topcat framebuffer support (derived from macfb of all things)
 *	Phil Blundell <philb@gnu.org> 1998", the original code can be
 *	found in the file hpfb.c in the same directory.
 *
 *	DECstation related code Copyright (C) 1999, 2000, 2001 by
 *	Michael Engel <engel@unix-ag.org>,
 *	Karsten Merker <merker@linuxtag.org> and
 *	Harald Koerfgen.
 *	Copyright (c) 2005, 2006  Maciej W. Rozycki
 *
 *	This file is subject to the terms and conditions of the GNU General
 *	Public License.  See the file COPYING in the मुख्य directory of this
 *	archive क्रम more details.
 */

#समावेश <linux/compiler.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/tc.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/पन.स>

#समावेश <video/pmagb-b-fb.h>


काष्ठा pmagbbfb_par अणु
	अस्थिर व्योम __iomem *mmio;
	अस्थिर व्योम __iomem *smem;
	अस्थिर u32 __iomem *sfb;
	अस्थिर u32 __iomem *dac;
	अचिन्हित पूर्णांक osc0;
	अचिन्हित पूर्णांक osc1;
	पूर्णांक slot;
पूर्ण;


अटल स्थिर काष्ठा fb_var_screeninfo pmagbbfb_defined = अणु
	.bits_per_pixel	= 8,
	.red.length	= 8,
	.green.length	= 8,
	.blue.length	= 8,
	.activate	= FB_ACTIVATE_NOW,
	.height		= -1,
	.width		= -1,
	.accel_flags	= FB_ACCEL_NONE,
	.sync		= FB_SYNC_ON_GREEN,
	.vmode		= FB_VMODE_NONINTERLACED,
पूर्ण;

अटल स्थिर काष्ठा fb_fix_screeninfo pmagbbfb_fix = अणु
	.id		= "PMAGB-BA",
	.smem_len	= (2048 * 1024),
	.type		= FB_TYPE_PACKED_PIXELS,
	.visual		= FB_VISUAL_PSEUDOCOLOR,
	.mmio_len	= PMAGB_B_FBMEM,
पूर्ण;


अटल अंतरभूत व्योम sfb_ग_लिखो(काष्ठा pmagbbfb_par *par, अचिन्हित पूर्णांक reg, u32 v)
अणु
	ग_लिखोl(v, par->sfb + reg / 4);
पूर्ण

अटल अंतरभूत u32 sfb_पढ़ो(काष्ठा pmagbbfb_par *par, अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl(par->sfb + reg / 4);
पूर्ण

अटल अंतरभूत व्योम dac_ग_लिखो(काष्ठा pmagbbfb_par *par, अचिन्हित पूर्णांक reg, u8 v)
अणु
	ग_लिखोb(v, par->dac + reg / 4);
पूर्ण

अटल अंतरभूत u8 dac_पढ़ो(काष्ठा pmagbbfb_par *par, अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोb(par->dac + reg / 4);
पूर्ण

अटल अंतरभूत व्योम gp0_ग_लिखो(काष्ठा pmagbbfb_par *par, u32 v)
अणु
	ग_लिखोl(v, par->mmio + PMAGB_B_GP0);
पूर्ण


/*
 * Set the palette.
 */
अटल पूर्णांक pmagbbfb_setcolreg(अचिन्हित पूर्णांक regno, अचिन्हित पूर्णांक red,
			      अचिन्हित पूर्णांक green, अचिन्हित पूर्णांक blue,
			      अचिन्हित पूर्णांक transp, काष्ठा fb_info *info)
अणु
	काष्ठा pmagbbfb_par *par = info->par;

	अगर (regno >= info->cmap.len)
		वापस 1;

	red   >>= 8;	/* The cmap fields are 16 bits    */
	green >>= 8;	/* wide, but the hardware colormap */
	blue  >>= 8;	/* रेजिस्टरs are only 8 bits wide */

	mb();
	dac_ग_लिखो(par, BT459_ADDR_LO, regno);
	dac_ग_लिखो(par, BT459_ADDR_HI, 0x00);
	wmb();
	dac_ग_लिखो(par, BT459_CMAP, red);
	wmb();
	dac_ग_लिखो(par, BT459_CMAP, green);
	wmb();
	dac_ग_लिखो(par, BT459_CMAP, blue);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops pmagbbfb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_setcolreg	= pmagbbfb_setcolreg,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;


/*
 * Turn the hardware cursor off.
 */
अटल व्योम pmagbbfb_erase_cursor(काष्ठा fb_info *info)
अणु
	काष्ठा pmagbbfb_par *par = info->par;

	mb();
	dac_ग_लिखो(par, BT459_ADDR_LO, 0x00);
	dac_ग_लिखो(par, BT459_ADDR_HI, 0x03);
	wmb();
	dac_ग_लिखो(par, BT459_DATA, 0x00);
पूर्ण

/*
 * Set up screen parameters.
 */
अटल व्योम pmagbbfb_screen_setup(काष्ठा fb_info *info)
अणु
	काष्ठा pmagbbfb_par *par = info->par;

	info->var.xres = ((sfb_पढ़ो(par, SFB_REG_VID_HOR) >>
			   SFB_VID_HOR_PIX_SHIFT) & SFB_VID_HOR_PIX_MASK) * 4;
	info->var.xres_भव = info->var.xres;
	info->var.yres = (sfb_पढ़ो(par, SFB_REG_VID_VER) >>
			  SFB_VID_VER_SL_SHIFT) & SFB_VID_VER_SL_MASK;
	info->var.yres_भव = info->var.yres;
	info->var.left_margin = ((sfb_पढ़ो(par, SFB_REG_VID_HOR) >>
				  SFB_VID_HOR_BP_SHIFT) &
				 SFB_VID_HOR_BP_MASK) * 4;
	info->var.right_margin = ((sfb_पढ़ो(par, SFB_REG_VID_HOR) >>
				   SFB_VID_HOR_FP_SHIFT) &
				  SFB_VID_HOR_FP_MASK) * 4;
	info->var.upper_margin = (sfb_पढ़ो(par, SFB_REG_VID_VER) >>
				  SFB_VID_VER_BP_SHIFT) & SFB_VID_VER_BP_MASK;
	info->var.lower_margin = (sfb_पढ़ो(par, SFB_REG_VID_VER) >>
				  SFB_VID_VER_FP_SHIFT) & SFB_VID_VER_FP_MASK;
	info->var.hsync_len = ((sfb_पढ़ो(par, SFB_REG_VID_HOR) >>
				SFB_VID_HOR_SYN_SHIFT) &
			       SFB_VID_HOR_SYN_MASK) * 4;
	info->var.vsync_len = (sfb_पढ़ो(par, SFB_REG_VID_VER) >>
			       SFB_VID_VER_SYN_SHIFT) & SFB_VID_VER_SYN_MASK;

	info->fix.line_length = info->var.xres;
पूर्ण;

/*
 * Determine oscillator configuration.
 */
अटल व्योम pmagbbfb_osc_setup(काष्ठा fb_info *info)
अणु
	अटल अचिन्हित पूर्णांक pmagbbfb_freqs[] = अणु
		130808, 119843, 104000, 92980, 74370, 72800,
		69197, 66000, 65000, 50350, 36000, 32000, 25175
	पूर्ण;
	काष्ठा pmagbbfb_par *par = info->par;
	काष्ठा tc_bus *tbus = to_tc_dev(info->device)->bus;
	u32 count0 = 8, count1 = 8, counttc = 16 * 256 + 8;
	u32 freq0, freq1, freqtc = tc_get_speed(tbus) / 250;
	पूर्णांक i, j;

	gp0_ग_लिखो(par, 0);				/* select Osc0 */
	क्रम (j = 0; j < 16; j++) अणु
		mb();
		sfb_ग_लिखो(par, SFB_REG_TCCLK_COUNT, 0);
		mb();
		क्रम (i = 0; i < 100; i++) अणु	/* nominally max. 20.5us */
			अगर (sfb_पढ़ो(par, SFB_REG_TCCLK_COUNT) == 0)
				अवरोध;
			udelay(1);
		पूर्ण
		count0 += sfb_पढ़ो(par, SFB_REG_VIDCLK_COUNT);
	पूर्ण

	gp0_ग_लिखो(par, 1);				/* select Osc1 */
	क्रम (j = 0; j < 16; j++) अणु
		mb();
		sfb_ग_लिखो(par, SFB_REG_TCCLK_COUNT, 0);

		क्रम (i = 0; i < 100; i++) अणु	/* nominally max. 20.5us */
			अगर (sfb_पढ़ो(par, SFB_REG_TCCLK_COUNT) == 0)
				अवरोध;
			udelay(1);
		पूर्ण
		count1 += sfb_पढ़ो(par, SFB_REG_VIDCLK_COUNT);
	पूर्ण

	freq0 = (freqtc * count0 + counttc / 2) / counttc;
	par->osc0 = freq0;
	अगर (freq0 >= pmagbbfb_freqs[0] - (pmagbbfb_freqs[0] + 32) / 64 &&
	    freq0 <= pmagbbfb_freqs[0] + (pmagbbfb_freqs[0] + 32) / 64)
		par->osc0 = pmagbbfb_freqs[0];

	freq1 = (par->osc0 * count1 + count0 / 2) / count0;
	par->osc1 = freq1;
	क्रम (i = 0; i < ARRAY_SIZE(pmagbbfb_freqs); i++)
		अगर (freq1 >= pmagbbfb_freqs[i] -
			     (pmagbbfb_freqs[i] + 128) / 256 &&
		    freq1 <= pmagbbfb_freqs[i] +
			     (pmagbbfb_freqs[i] + 128) / 256) अणु
			par->osc1 = pmagbbfb_freqs[i];
			अवरोध;
		पूर्ण

	अगर (par->osc0 - par->osc1 <= (par->osc0 + par->osc1 + 256) / 512 ||
	    par->osc1 - par->osc0 <= (par->osc0 + par->osc1 + 256) / 512)
		par->osc1 = 0;

	gp0_ग_लिखो(par, par->osc1 != 0);			/* reselect OscX */

	info->var.pixघड़ी = par->osc1 ?
			     (1000000000 + par->osc1 / 2) / par->osc1 :
			     (1000000000 + par->osc0 / 2) / par->osc0;
पूर्ण;


अटल पूर्णांक pmagbbfb_probe(काष्ठा device *dev)
अणु
	काष्ठा tc_dev *tdev = to_tc_dev(dev);
	resource_माप_प्रकार start, len;
	काष्ठा fb_info *info;
	काष्ठा pmagbbfb_par *par;
	अक्षर freq0[12], freq1[12];
	u32 vid_base;
	पूर्णांक err;

	info = framebuffer_alloc(माप(काष्ठा pmagbbfb_par), dev);
	अगर (!info)
		वापस -ENOMEM;

	par = info->par;
	dev_set_drvdata(dev, info);

	अगर (fb_alloc_cmap(&info->cmap, 256, 0) < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: Cannot allocate color map\n",
		       dev_name(dev));
		err = -ENOMEM;
		जाओ err_alloc;
	पूर्ण

	info->fbops = &pmagbbfb_ops;
	info->fix = pmagbbfb_fix;
	info->var = pmagbbfb_defined;
	info->flags = FBINFO_DEFAULT;

	/* Request the I/O MEM resource.  */
	start = tdev->resource.start;
	len = tdev->resource.end - start + 1;
	अगर (!request_mem_region(start, len, dev_name(dev))) अणु
		prपूर्णांकk(KERN_ERR "%s: Cannot reserve FB region\n",
		       dev_name(dev));
		err = -EBUSY;
		जाओ err_cmap;
	पूर्ण

	/* MMIO mapping setup.  */
	info->fix.mmio_start = start;
	par->mmio = ioremap(info->fix.mmio_start, info->fix.mmio_len);
	अगर (!par->mmio) अणु
		prपूर्णांकk(KERN_ERR "%s: Cannot map MMIO\n", dev_name(dev));
		err = -ENOMEM;
		जाओ err_resource;
	पूर्ण
	par->sfb = par->mmio + PMAGB_B_SFB;
	par->dac = par->mmio + PMAGB_B_BT459;

	/* Frame buffer mapping setup.  */
	info->fix.smem_start = start + PMAGB_B_FBMEM;
	par->smem = ioremap(info->fix.smem_start, info->fix.smem_len);
	अगर (!par->smem) अणु
		prपूर्णांकk(KERN_ERR "%s: Cannot map FB\n", dev_name(dev));
		err = -ENOMEM;
		जाओ err_mmio_map;
	पूर्ण
	vid_base = sfb_पढ़ो(par, SFB_REG_VID_BASE);
	info->screen_base = (व्योम __iomem *)par->smem + vid_base * 0x1000;
	info->screen_size = info->fix.smem_len - 2 * vid_base * 0x1000;

	pmagbbfb_erase_cursor(info);
	pmagbbfb_screen_setup(info);
	pmagbbfb_osc_setup(info);

	err = रेजिस्टर_framebuffer(info);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: Cannot register framebuffer\n",
		       dev_name(dev));
		जाओ err_smem_map;
	पूर्ण

	get_device(dev);

	snम_लिखो(freq0, माप(freq0), "%u.%03uMHz",
		 par->osc0 / 1000, par->osc0 % 1000);
	snम_लिखो(freq1, माप(freq1), "%u.%03uMHz",
		 par->osc1 / 1000, par->osc1 % 1000);

	fb_info(info, "%s frame buffer device at %s\n",
		info->fix.id, dev_name(dev));
	fb_info(info, "Osc0: %s, Osc1: %s, Osc%u selected\n",
		freq0, par->osc1 ? freq1 : "disabled", par->osc1 != 0);

	वापस 0;


err_smem_map:
	iounmap(par->smem);

err_mmio_map:
	iounmap(par->mmio);

err_resource:
	release_mem_region(start, len);

err_cmap:
	fb_dealloc_cmap(&info->cmap);

err_alloc:
	framebuffer_release(info);
	वापस err;
पूर्ण

अटल पूर्णांक pmagbbfb_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा tc_dev *tdev = to_tc_dev(dev);
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा pmagbbfb_par *par = info->par;
	resource_माप_प्रकार start, len;

	put_device(dev);
	unरेजिस्टर_framebuffer(info);
	iounmap(par->smem);
	iounmap(par->mmio);
	start = tdev->resource.start;
	len = tdev->resource.end - start + 1;
	release_mem_region(start, len);
	fb_dealloc_cmap(&info->cmap);
	framebuffer_release(info);
	वापस 0;
पूर्ण


/*
 * Initialize the framebuffer.
 */
अटल स्थिर काष्ठा tc_device_id pmagbbfb_tc_table[] = अणु
	अणु "DEC     ", "PMAGB-BA" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(tc, pmagbbfb_tc_table);

अटल काष्ठा tc_driver pmagbbfb_driver = अणु
	.id_table	= pmagbbfb_tc_table,
	.driver		= अणु
		.name	= "pmagbbfb",
		.bus	= &tc_bus_type,
		.probe	= pmagbbfb_probe,
		.हटाओ	= pmagbbfb_हटाओ,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init pmagbbfb_init(व्योम)
अणु
#अगर_अघोषित MODULE
	अगर (fb_get_options("pmagbbfb", शून्य))
		वापस -ENXIO;
#पूर्ण_अगर
	वापस tc_रेजिस्टर_driver(&pmagbbfb_driver);
पूर्ण

अटल व्योम __निकास pmagbbfb_निकास(व्योम)
अणु
	tc_unरेजिस्टर_driver(&pmagbbfb_driver);
पूर्ण


module_init(pmagbbfb_init);
module_निकास(pmagbbfb_निकास);

MODULE_LICENSE("GPL");
