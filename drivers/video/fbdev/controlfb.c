<शैली गुरु>
/*
 *  controlfb.c -- frame buffer device क्रम the PowerMac 'control' display
 *
 *  Created 12 July 1998 by Dan Jacobowitz <dan@debian.org>
 *  Copyright (C) 1998 Dan Jacobowitz
 *  Copyright (C) 2001 Takashi Oe
 *
 *  Mmap code by Michel Lanners <mlan@cpu.lu>
 *
 *  Frame buffer काष्ठाure from:
 *    drivers/video/chipsfb.c -- frame buffer device क्रम
 *    Chips & Technologies 65550 chip.
 *
 *    Copyright (C) 1998 Paul Mackerras
 *
 *    This file is derived from the Powermac "chips" driver:
 *    Copyright (C) 1997 Fabio Riccardi.
 *    And from the frame buffer device क्रम Open Firmware-initialized devices:
 *    Copyright (C) 1997 Geert Uytterhoeven.
 *
 *  Hardware inक्रमmation from:
 *    control.c: Console support क्रम PowerMac "control" display adaptor.
 *    Copyright (C) 1996 Paul Mackerras
 *
 *  Updated to 2.5 framebuffer API by Ben Herrenschmidt
 *  <benh@kernel.crashing.org>, Paul Mackerras <paulus@samba.org>,
 *  and James Simmons <jsimmons@infradead.org>.
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/nvram.h>
#समावेश <linux/adb.h>
#समावेश <linux/cuda.h>
#अगर_घोषित CONFIG_PPC_PMAC
#समावेश <यंत्र/prom.h>
#पूर्ण_अगर
#अगर_घोषित CONFIG_BOOTX_TEXT
#समावेश <यंत्र/btext.h>
#पूर्ण_अगर

#समावेश "macmodes.h"
#समावेश "controlfb.h"

#अगर !defined(CONFIG_PPC_PMAC) || !defined(CONFIG_PPC32)
#घोषणा invalid_vram_cache(addr)
#अघोषित in_8
#अघोषित out_8
#अघोषित in_le32
#अघोषित out_le32
#घोषणा in_8(addr)		0
#घोषणा out_8(addr, val)	(व्योम)(val)
#घोषणा in_le32(addr)		0
#घोषणा out_le32(addr, val)	(व्योम)(val)
#घोषणा pgprot_cached_wthru(prot) (prot)
#अन्यथा
अटल व्योम invalid_vram_cache(व्योम __क्रमce *addr)
अणु
	eieio();
	dcbf(addr);
	mb();
	eieio();
	dcbf(addr);
	mb();
पूर्ण
#पूर्ण_अगर

काष्ठा fb_par_control अणु
	पूर्णांक	vmode, cmode;
	पूर्णांक	xres, yres;
	पूर्णांक	vxres, vyres;
	पूर्णांक	xoffset, yoffset;
	पूर्णांक	pitch;
	काष्ठा control_regvals	regvals;
	अचिन्हित दीर्घ sync;
	अचिन्हित अक्षर ctrl;
पूर्ण;

#घोषणा सूचीTY(z) ((x)->z != (y)->z)
#घोषणा सूचीTY_CMAP(z) (स_भेद(&((x)->z), &((y)->z), माप((y)->z)))
अटल अंतरभूत पूर्णांक PAR_EQUAL(काष्ठा fb_par_control *x, काष्ठा fb_par_control *y)
अणु
	पूर्णांक i, results;

	results = 1;
	क्रम (i = 0; i < 3; i++)
		results &= !सूचीTY(regvals.घड़ी_params[i]);
	अगर (!results)
		वापस 0;
	क्रम (i = 0; i < 16; i++)
		results &= !सूचीTY(regvals.regs[i]);
	अगर (!results)
		वापस 0;
	वापस (!सूचीTY(cmode) && !सूचीTY(xres) && !सूचीTY(yres)
		&& !सूचीTY(vxres) && !सूचीTY(vyres));
पूर्ण
अटल अंतरभूत पूर्णांक VAR_MATCH(काष्ठा fb_var_screeninfo *x, काष्ठा fb_var_screeninfo *y)
अणु
	वापस (!सूचीTY(bits_per_pixel) && !सूचीTY(xres)
		&& !सूचीTY(yres) && !सूचीTY(xres_भव)
		&& !सूचीTY(yres_भव)
		&& !सूचीTY_CMAP(red) && !सूचीTY_CMAP(green) && !सूचीTY_CMAP(blue));
पूर्ण

काष्ठा fb_info_control अणु
	काष्ठा fb_info		info;
	काष्ठा fb_par_control	par;
	u32			pseuकरो_palette[16];
		
	काष्ठा cmap_regs	__iomem *cmap_regs;
	अचिन्हित दीर्घ		cmap_regs_phys;
	
	काष्ठा control_regs	__iomem *control_regs;
	अचिन्हित दीर्घ		control_regs_phys;
	अचिन्हित दीर्घ		control_regs_size;
	
	__u8			__iomem *frame_buffer;
	अचिन्हित दीर्घ		frame_buffer_phys;
	अचिन्हित दीर्घ		fb_orig_base;
	अचिन्हित दीर्घ		fb_orig_size;

	पूर्णांक			control_use_bank2;
	अचिन्हित दीर्घ		total_vram;
	अचिन्हित अक्षर		vram_attr;
पूर्ण;

/* control रेजिस्टर access macro */
#घोषणा CNTRL_REG(INFO,REG) (&(((INFO)->control_regs->REG).r))


/************************** Internal variables *******************************/

अटल काष्ठा fb_info_control *control_fb;

अटल पूर्णांक शेष_vmode __initdata = VMODE_NVRAM;
अटल पूर्णांक शेष_cmode __initdata = CMODE_NVRAM;


अटल पूर्णांक controlfb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
			     u_पूर्णांक transp, काष्ठा fb_info *info)
अणु
	काष्ठा fb_info_control *p =
		container_of(info, काष्ठा fb_info_control, info);
	__u8 r, g, b;

	अगर (regno > 255)
		वापस 1;

	r = red >> 8;
	g = green >> 8;
	b = blue >> 8;

	out_8(&p->cmap_regs->addr, regno);	/* tell clut what addr to fill	*/
	out_8(&p->cmap_regs->lut, r);		/* send one color channel at	*/
	out_8(&p->cmap_regs->lut, g);		/* a समय...			*/
	out_8(&p->cmap_regs->lut, b);

	अगर (regno < 16) अणु
		पूर्णांक i;
		चयन (p->par.cmode) अणु
		हाल CMODE_16:
			p->pseuकरो_palette[regno] =
			    (regno << 10) | (regno << 5) | regno;
			अवरोध;
		हाल CMODE_32:
			i = (regno << 8) | regno;
			p->pseuकरो_palette[regno] = (i << 16) | i;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण


/********************  End of controlfb_ops implementation  ******************/



अटल व्योम set_control_घड़ी(अचिन्हित अक्षर *params)
अणु
#अगर_घोषित CONFIG_ADB_CUDA
	काष्ठा adb_request req;
	पूर्णांक i;

	क्रम (i = 0; i < 3; ++i) अणु
		cuda_request(&req, शून्य, 5, CUDA_PACKET, CUDA_GET_SET_IIC,
			     0x50, i + 1, params[i]);
		जबतक (!req.complete)
			cuda_poll();
	पूर्ण
#पूर्ण_अगर	
पूर्ण

/*
 * Set screen start address according to var offset values
 */
अटल अंतरभूत व्योम set_screen_start(पूर्णांक xoffset, पूर्णांक yoffset,
	काष्ठा fb_info_control *p)
अणु
	काष्ठा fb_par_control *par = &p->par;

	par->xoffset = xoffset;
	par->yoffset = yoffset;
	out_le32(CNTRL_REG(p,start_addr),
		 par->yoffset * par->pitch + (par->xoffset << par->cmode));
पूर्ण

#घोषणा RADACAL_WRITE(a,d) \
	out_8(&p->cmap_regs->addr, (a)); \
	out_8(&p->cmap_regs->dat,   (d))

/* Now how about actually saying, Make it so! */
/* Some things in here probably करोn't need to be करोne each समय. */
अटल व्योम control_set_hardware(काष्ठा fb_info_control *p, काष्ठा fb_par_control *par)
अणु
	काष्ठा control_regvals	*r;
	अस्थिर काष्ठा preg	__iomem *rp;
	पूर्णांक			i, cmode;

	अगर (PAR_EQUAL(&p->par, par)) अणु
		/*
		 * check अगर only xoffset or yoffset dअगरfers.
		 * this prevents flickers in typical VT चयन हाल.
		 */
		अगर (p->par.xoffset != par->xoffset ||
		    p->par.yoffset != par->yoffset)
			set_screen_start(par->xoffset, par->yoffset, p);
			
		वापस;
	पूर्ण
	
	p->par = *par;
	cmode = p->par.cmode;
	r = &par->regvals;
	
	/* Turn off display */
	out_le32(CNTRL_REG(p,ctrl), 0x400 | par->ctrl);
	
	set_control_घड़ी(r->घड़ी_params);
	
	RADACAL_WRITE(0x20, r->radacal_ctrl);
	RADACAL_WRITE(0x21, p->control_use_bank2 ? 0 : 1);
	RADACAL_WRITE(0x10, 0);
	RADACAL_WRITE(0x11, 0);

	rp = &p->control_regs->vswin;
	क्रम (i = 0; i < 16; ++i, ++rp)
		out_le32(&rp->r, r->regs[i]);
	
	out_le32(CNTRL_REG(p,pitch), par->pitch);
	out_le32(CNTRL_REG(p,mode), r->mode);
	out_le32(CNTRL_REG(p,vram_attr), p->vram_attr);
	out_le32(CNTRL_REG(p,start_addr), par->yoffset * par->pitch
		 + (par->xoffset << cmode));
	out_le32(CNTRL_REG(p,rfrcnt), 0x1e5);
	out_le32(CNTRL_REG(p,पूर्णांकr_ena), 0);

	/* Turn on display */
	out_le32(CNTRL_REG(p,ctrl), par->ctrl);

#अगर_घोषित CONFIG_BOOTX_TEXT
	btext_update_display(p->frame_buffer_phys + CTRLFB_OFF,
			     p->par.xres, p->par.yres,
			     (cmode == CMODE_32? 32: cmode == CMODE_16? 16: 8),
			     p->par.pitch);
#पूर्ण_अगर /* CONFIG_BOOTX_TEXT */
पूर्ण

/* Work out which banks of VRAM we have installed. */
/* danj: I guess the card just ignores ग_लिखोs to nonexistant VRAM... */

अटल व्योम __init find_vram_size(काष्ठा fb_info_control *p)
अणु
	पूर्णांक bank1, bank2;

	/*
	 * Set VRAM in 2MB (bank 1) mode
	 * VRAM Bank 2 will be accessible through offset 0x600000 अगर present
	 * and VRAM Bank 1 will not respond at that offset even अगर present
	 */
	out_le32(CNTRL_REG(p,vram_attr), 0x31);

	out_8(&p->frame_buffer[0x600000], 0xb3);
	out_8(&p->frame_buffer[0x600001], 0x71);
	invalid_vram_cache(&p->frame_buffer[0x600000]);

	bank2 = (in_8(&p->frame_buffer[0x600000]) == 0xb3)
		&& (in_8(&p->frame_buffer[0x600001]) == 0x71);

	/*
	 * Set VRAM in 2MB (bank 2) mode
	 * VRAM Bank 1 will be accessible through offset 0x000000 अगर present
	 * and VRAM Bank 2 will not respond at that offset even अगर present
	 */
	out_le32(CNTRL_REG(p,vram_attr), 0x39);

	out_8(&p->frame_buffer[0], 0x5a);
	out_8(&p->frame_buffer[1], 0xc7);
	invalid_vram_cache(&p->frame_buffer[0]);

	bank1 = (in_8(&p->frame_buffer[0]) == 0x5a)
		&& (in_8(&p->frame_buffer[1]) == 0xc7);

	अगर (bank2) अणु
		अगर (!bank1) अणु
			/*
			 * vram bank 2 only
			 */
			p->control_use_bank2 = 1;
			p->vram_attr = 0x39;
			p->frame_buffer += 0x600000;
			p->frame_buffer_phys += 0x600000;
		पूर्ण अन्यथा अणु
			/*
			 * 4 MB vram
			 */
			p->vram_attr = 0x51;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * vram bank 1 only
		 */
		p->vram_attr = 0x31;
	पूर्ण

        p->total_vram = (bank1 + bank2) * 0x200000;

	prपूर्णांकk(KERN_INFO "controlfb: VRAM Total = %dMB "
			"(%dMB @ bank 1, %dMB @ bank 2)\n",
			(bank1 + bank2) << 1, bank1 << 1, bank2 << 1);
पूर्ण

/*
 * Get the monitor sense value.
 * Note that this can be called beक्रमe calibrate_delay,
 * so we can't use udelay.
 */
अटल पूर्णांक पढ़ो_control_sense(काष्ठा fb_info_control *p)
अणु
	पूर्णांक sense;

	out_le32(CNTRL_REG(p,mon_sense), 7);	/* drive all lines high */
	__delay(200);
	out_le32(CNTRL_REG(p,mon_sense), 077);	/* turn off drivers */
	__delay(2000);
	sense = (in_le32(CNTRL_REG(p,mon_sense)) & 0x1c0) << 2;

	/* drive each sense line low in turn and collect the other 2 */
	out_le32(CNTRL_REG(p,mon_sense), 033);	/* drive A low */
	__delay(2000);
	sense |= (in_le32(CNTRL_REG(p,mon_sense)) & 0xc0) >> 2;
	out_le32(CNTRL_REG(p,mon_sense), 055);	/* drive B low */
	__delay(2000);
	sense |= ((in_le32(CNTRL_REG(p,mon_sense)) & 0x100) >> 5)
		| ((in_le32(CNTRL_REG(p,mon_sense)) & 0x40) >> 4);
	out_le32(CNTRL_REG(p,mon_sense), 066);	/* drive C low */
	__delay(2000);
	sense |= (in_le32(CNTRL_REG(p,mon_sense)) & 0x180) >> 7;

	out_le32(CNTRL_REG(p,mon_sense), 077);	/* turn off drivers */
	
	वापस sense;
पूर्ण

/**********************  Various translation functions  **********************/

#घोषणा CONTROL_PIXCLOCK_BASE	256016
#घोषणा CONTROL_PIXCLOCK_MIN	5000	/* ~ 200 MHz करोt घड़ी */

/*
 * calculate the घड़ी paramaters to be sent to CUDA according to given
 * pixघड़ी in pico second.
 */
अटल पूर्णांक calc_घड़ी_params(अचिन्हित दीर्घ clk, अचिन्हित अक्षर *param)
अणु
	अचिन्हित दीर्घ p0, p1, p2, k, l, m, n, min;

	अगर (clk > (CONTROL_PIXCLOCK_BASE << 3))
		वापस 1;

	p2 = ((clk << 4) < CONTROL_PIXCLOCK_BASE)? 3: 2;
	l = clk << p2;
	p0 = 0;
	p1 = 0;
	क्रम (k = 1, min = l; k < 32; k++) अणु
		अचिन्हित दीर्घ rem;

		m = CONTROL_PIXCLOCK_BASE * k;
		n = m / l;
		rem = m % l;
		अगर (n && (n < 128) && rem < min) अणु
			p0 = k;
			p1 = n;
			min = rem;
		पूर्ण
	पूर्ण
	अगर (!p0 || !p1)
		वापस 1;

	param[0] = p0;
	param[1] = p1;
	param[2] = p2;

	वापस 0;
पूर्ण


/*
 * This routine takes a user-supplied var, and picks the best vmode/cmode
 * from it.
 */

अटल पूर्णांक control_var_to_par(काष्ठा fb_var_screeninfo *var,
	काष्ठा fb_par_control *par, स्थिर काष्ठा fb_info *fb_info)
अणु
	पूर्णांक cmode, piped_dअगरf, hstep;
	अचिन्हित hperiod, hssync, hsblank, hesync, heblank, piped, heq, hlfln,
		 hserr, vperiod, vssync, vesync, veblank, vsblank, vswin, vewin;
	अचिन्हित दीर्घ pixघड़ी;
	काष्ठा fb_info_control *p =
		container_of(fb_info, काष्ठा fb_info_control, info);
	काष्ठा control_regvals *r = &par->regvals;

	चयन (var->bits_per_pixel) अणु
	हाल 8:
		par->cmode = CMODE_8;
		अगर (p->total_vram > 0x200000) अणु
			r->mode = 3;
			r->radacal_ctrl = 0x20;
			piped_dअगरf = 13;
		पूर्ण अन्यथा अणु
			r->mode = 2;
			r->radacal_ctrl = 0x10;
			piped_dअगरf = 9;
		पूर्ण
		अवरोध;
	हाल 15:
	हाल 16:
		par->cmode = CMODE_16;
		अगर (p->total_vram > 0x200000) अणु
			r->mode = 2;
			r->radacal_ctrl = 0x24;
			piped_dअगरf = 5;
		पूर्ण अन्यथा अणु
			r->mode = 1;
			r->radacal_ctrl = 0x14;
			piped_dअगरf = 3;
		पूर्ण
		अवरोध;
	हाल 32:
		par->cmode = CMODE_32;
		अगर (p->total_vram > 0x200000) अणु
			r->mode = 1;
			r->radacal_ctrl = 0x28;
		पूर्ण अन्यथा अणु
			r->mode = 0;
			r->radacal_ctrl = 0x18;
		पूर्ण
		piped_dअगरf = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * adjust xres and vxres so that the corresponding memory widths are
	 * 32-byte aligned
	 */
	hstep = 31 >> par->cmode;
	par->xres = (var->xres + hstep) & ~hstep;
	par->vxres = (var->xres_भव + hstep) & ~hstep;
	par->xoffset = (var->xoffset + hstep) & ~hstep;
	अगर (par->vxres < par->xres)
		par->vxres = par->xres;
	par->pitch = par->vxres << par->cmode;

	par->yres = var->yres;
	par->vyres = var->yres_भव;
	par->yoffset = var->yoffset;
	अगर (par->vyres < par->yres)
		par->vyres = par->yres;

	par->sync = var->sync;

	अगर (par->pitch * par->vyres + CTRLFB_OFF > p->total_vram)
		वापस -EINVAL;

	अगर (par->xoffset + par->xres > par->vxres)
		par->xoffset = par->vxres - par->xres;
	अगर (par->yoffset + par->yres > par->vyres)
		par->yoffset = par->vyres - par->yres;

	pixघड़ी = (var->pixघड़ी < CONTROL_PIXCLOCK_MIN)? CONTROL_PIXCLOCK_MIN:
		   var->pixघड़ी;
	अगर (calc_घड़ी_params(pixघड़ी, r->घड़ी_params))
		वापस -EINVAL;

	hperiod = ((var->left_margin + par->xres + var->right_margin
		    + var->hsync_len) >> 1) - 2;
	hssync = hperiod + 1;
	hsblank = hssync - (var->right_margin >> 1);
	hesync = (var->hsync_len >> 1) - 1;
	heblank = (var->left_margin >> 1) + hesync;
	piped = heblank - piped_dअगरf;
	heq = var->hsync_len >> 2;
	hlfln = (hperiod+2) >> 1;
	hserr = hssync-hesync;
	vperiod = (var->vsync_len + var->lower_margin + par->yres
		   + var->upper_margin) << 1;
	vssync = vperiod - 2;
	vesync = (var->vsync_len << 1) - vperiod + vssync;
	veblank = (var->upper_margin << 1) + vesync;
	vsblank = vssync - (var->lower_margin << 1);
	vswin = (vsblank+vssync) >> 1;
	vewin = (vesync+veblank) >> 1;

	r->regs[0] = vswin;
	r->regs[1] = vsblank;
	r->regs[2] = veblank;
	r->regs[3] = vewin;
	r->regs[4] = vesync;
	r->regs[5] = vssync;
	r->regs[6] = vperiod;
	r->regs[7] = piped;
	r->regs[8] = hperiod;
	r->regs[9] = hsblank;
	r->regs[10] = heblank;
	r->regs[11] = hesync;
	r->regs[12] = hssync;
	r->regs[13] = heq;
	r->regs[14] = hlfln;
	r->regs[15] = hserr;

	अगर (par->xres >= 1280 && par->cmode >= CMODE_16)
		par->ctrl = 0x7f;
	अन्यथा
		par->ctrl = 0x3b;

	अगर (mac_var_to_vmode(var, &par->vmode, &cmode))
		par->vmode = 0;

	वापस 0;
पूर्ण


/*
 * Convert hardware data in par to an fb_var_screeninfo
 */

अटल व्योम control_par_to_var(काष्ठा fb_par_control *par, काष्ठा fb_var_screeninfo *var)
अणु
	काष्ठा control_regपूर्णांकs *rv;
	
	rv = (काष्ठा control_regपूर्णांकs *) par->regvals.regs;
	
	स_रखो(var, 0, माप(*var));
	var->xres = par->xres;
	var->yres = par->yres;
	var->xres_भव = par->vxres;
	var->yres_भव = par->vyres;
	var->xoffset = par->xoffset;
	var->yoffset = par->yoffset;
	
	चयन(par->cmode) अणु
	शेष:
	हाल CMODE_8:
		var->bits_per_pixel = 8;
		var->red.length = 8;
		var->green.length = 8;
		var->blue.length = 8;
		अवरोध;
	हाल CMODE_16:	/* RGB 555 */
		var->bits_per_pixel = 16;
		var->red.offset = 10;
		var->red.length = 5;
		var->green.offset = 5;
		var->green.length = 5;
		var->blue.length = 5;
		अवरोध;
	हाल CMODE_32:	/* RGB 888 */
		var->bits_per_pixel = 32;
		var->red.offset = 16;
		var->red.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->blue.length = 8;
		var->transp.offset = 24;
		var->transp.length = 8;
		अवरोध;
	पूर्ण
	var->height = -1;
	var->width = -1;
	var->vmode = FB_VMODE_NONINTERLACED;

	var->left_margin = (rv->heblank - rv->hesync) << 1;
	var->right_margin = (rv->hssync - rv->hsblank) << 1;
	var->hsync_len = (rv->hperiod + 2 - rv->hssync + rv->hesync) << 1;

	var->upper_margin = (rv->veblank - rv->vesync) >> 1;
	var->lower_margin = (rv->vssync - rv->vsblank) >> 1;
	var->vsync_len = (rv->vperiod - rv->vssync + rv->vesync) >> 1;

	var->sync = par->sync;

	/*
	 * 10^12 * घड़ी_params[0] / (3906400 * घड़ी_params[1]
	 *			      * 2^घड़ी_params[2])
	 * (10^12 * घड़ी_params[0] / (3906400 * घड़ी_params[1]))
	 * >> घड़ी_params[2]
	 */
	/* (255990.17 * घड़ी_params[0] / घड़ी_params[1]) >> घड़ी_params[2] */
	var->pixघड़ी = CONTROL_PIXCLOCK_BASE * par->regvals.घड़ी_params[0];
	var->pixघड़ी /= par->regvals.घड़ी_params[1];
	var->pixघड़ी >>= par->regvals.घड़ी_params[2];
पूर्ण

/********************  The functions क्रम controlfb_ops ********************/

/*
 * Checks a var काष्ठाure
 */
अटल पूर्णांक controlfb_check_var (काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा fb_par_control par;
	पूर्णांक err;

	err = control_var_to_par(var, &par, info);
	अगर (err)
		वापस err;	
	control_par_to_var(&par, var);

	वापस 0;
पूर्ण

/*
 * Applies current var to display
 */
अटल पूर्णांक controlfb_set_par (काष्ठा fb_info *info)
अणु
	काष्ठा fb_info_control *p =
		container_of(info, काष्ठा fb_info_control, info);
	काष्ठा fb_par_control par;
	पूर्णांक err;

	अगर((err = control_var_to_par(&info->var, &par, info))) अणु
		prपूर्णांकk (KERN_ERR "controlfb_set_par: error calling"
				 " control_var_to_par: %d.\n", err);
		वापस err;
	पूर्ण
	
	control_set_hardware(p, &par);

	info->fix.visual = (p->par.cmode == CMODE_8) ?
		FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_सूचीECTCOLOR;
	info->fix.line_length = p->par.pitch;
	info->fix.xpanstep = 32 >> p->par.cmode;
	info->fix.ypanstep = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक controlfb_pan_display(काष्ठा fb_var_screeninfo *var,
				 काष्ठा fb_info *info)
अणु
	अचिन्हित पूर्णांक xoffset, hstep;
	काष्ठा fb_info_control *p =
		container_of(info, काष्ठा fb_info_control, info);
	काष्ठा fb_par_control *par = &p->par;

	/*
	 * make sure start addr will be 32-byte aligned
	 */
	hstep = 0x1f >> par->cmode;
	xoffset = (var->xoffset + hstep) & ~hstep;

	अगर (xoffset+par->xres > par->vxres ||
	    var->yoffset+par->yres > par->vyres)
		वापस -EINVAL;

	set_screen_start(xoffset, var->yoffset, p);

	वापस 0;
पूर्ण

अटल पूर्णांक controlfb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	काष्ठा fb_info_control __maybe_unused *p =
		container_of(info, काष्ठा fb_info_control, info);
	अचिन्हित ctrl;

	ctrl = in_le32(CNTRL_REG(p, ctrl));
	अगर (blank_mode > 0)
		चयन (blank_mode) अणु
		हाल FB_BLANK_VSYNC_SUSPEND:
			ctrl &= ~3;
			अवरोध;
		हाल FB_BLANK_HSYNC_SUSPEND:
			ctrl &= ~0x30;
			अवरोध;
		हाल FB_BLANK_POWERDOWN:
			ctrl &= ~0x33;
			fallthrough;
		हाल FB_BLANK_NORMAL:
			ctrl |= 0x400;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	अन्यथा अणु
		ctrl &= ~0x400;
		ctrl |= 0x33;
	पूर्ण
	out_le32(CNTRL_REG(p,ctrl), ctrl);

	वापस 0;
पूर्ण

/*
 * Private mmap since we want to have a dअगरferent caching on the framebuffer
 * क्रम controlfb.
 * Note there's no locking in here; it's करोne in fb_mmap() in fbmem.c.
 */
अटल पूर्णांक controlfb_mmap(काष्ठा fb_info *info,
                       काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ mmio_pgoff;
	अचिन्हित दीर्घ start;
	u32 len;

	start = info->fix.smem_start;
	len = info->fix.smem_len;
	mmio_pgoff = PAGE_ALIGN((start & ~PAGE_MASK) + len) >> PAGE_SHIFT;
	अगर (vma->vm_pgoff >= mmio_pgoff) अणु
		अगर (info->var.accel_flags)
			वापस -EINVAL;
		vma->vm_pgoff -= mmio_pgoff;
		start = info->fix.mmio_start;
		len = info->fix.mmio_len;
		vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	पूर्ण अन्यथा अणु
		/* framebuffer */
		vma->vm_page_prot = pgprot_cached_wthru(vma->vm_page_prot);
	पूर्ण

	वापस vm_iomap_memory(vma, start, len);
पूर्ण

अटल स्थिर काष्ठा fb_ops controlfb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_check_var	= controlfb_check_var,
	.fb_set_par	= controlfb_set_par,
	.fb_setcolreg	= controlfb_setcolreg,
	.fb_pan_display = controlfb_pan_display,
	.fb_blank	= controlfb_blank,
	.fb_mmap	= controlfb_mmap,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

/*
 * Set misc info vars क्रम this driver
 */
अटल व्योम __init control_init_info(काष्ठा fb_info *info, काष्ठा fb_info_control *p)
अणु
	/* Fill fb_info */
	info->par = &p->par;
	info->fbops = &controlfb_ops;
	info->pseuकरो_palette = p->pseuकरो_palette;
        info->flags = FBINFO_DEFAULT | FBINFO_HWACCEL_YPAN;
	info->screen_base = p->frame_buffer + CTRLFB_OFF;

	fb_alloc_cmap(&info->cmap, 256, 0);

	/* Fill fix common fields */
	म_नकल(info->fix.id, "control");
	info->fix.mmio_start = p->control_regs_phys;
	info->fix.mmio_len = माप(काष्ठा control_regs);
	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.smem_start = p->frame_buffer_phys + CTRLFB_OFF;
	info->fix.smem_len = p->total_vram - CTRLFB_OFF;
        info->fix.ywrapstep = 0;
        info->fix.type_aux = 0;
        info->fix.accel = FB_ACCEL_NONE;
पूर्ण

/*
 * Parse user specअगरied options (`video=controlfb:')
 */
अटल व्योम __init control_setup(अक्षर *options)
अणु
	अक्षर *this_opt;

	अगर (!options || !*options)
		वापस;

	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!म_भेदन(this_opt, "vmode:", 6)) अणु
			पूर्णांक vmode = simple_म_से_अदीर्घ(this_opt+6, शून्य, 0);
			अगर (vmode > 0 && vmode <= VMODE_MAX &&
			    control_mac_modes[vmode - 1].m[1] >= 0)
				शेष_vmode = vmode;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "cmode:", 6)) अणु
			पूर्णांक depth = simple_म_से_अदीर्घ(this_opt+6, शून्य, 0);
			चयन (depth) अणु
			 हाल CMODE_8:
			 हाल CMODE_16:
			 हाल CMODE_32:
			 	शेष_cmode = depth;
			 	अवरोध;
			 हाल 8:
				शेष_cmode = CMODE_8;
				अवरोध;
			 हाल 15:
			 हाल 16:
				शेष_cmode = CMODE_16;
				अवरोध;
			 हाल 24:
			 हाल 32:
				शेष_cmode = CMODE_32;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * finish off the driver initialization and रेजिस्टर
 */
अटल पूर्णांक __init init_control(काष्ठा fb_info_control *p)
अणु
	पूर्णांक full, sense, vmode, cmode, vyres;
	काष्ठा fb_var_screeninfo var;
	पूर्णांक rc;
	
	prपूर्णांकk(KERN_INFO "controlfb: ");

	full = p->total_vram == 0x400000;

	/* Try to pick a video mode out of NVRAM अगर we have one. */
	cmode = शेष_cmode;
	अगर (IS_REACHABLE(CONFIG_NVRAM) && cmode == CMODE_NVRAM)
		cmode = nvram_पढ़ो_byte(NV_CMODE);
	अगर (cmode < CMODE_8 || cmode > CMODE_32)
		cmode = CMODE_8;

	vmode = शेष_vmode;
	अगर (IS_REACHABLE(CONFIG_NVRAM) && vmode == VMODE_NVRAM)
		vmode = nvram_पढ़ो_byte(NV_VMODE);
	अगर (vmode < 1 || vmode > VMODE_MAX ||
	    control_mac_modes[vmode - 1].m[full] < cmode) अणु
		sense = पढ़ो_control_sense(p);
		prपूर्णांकk(KERN_CONT "Monitor sense value = 0x%x, ", sense);
		vmode = mac_map_monitor_sense(sense);
		अगर (control_mac_modes[vmode - 1].m[full] < 0)
			vmode = VMODE_640_480_60;
		cmode = min(cmode, control_mac_modes[vmode - 1].m[full]);
	पूर्ण

	/* Initialize info काष्ठाure */
	control_init_info(&p->info, p);

	/* Setup शेष var */
	अगर (mac_vmode_to_var(vmode, cmode, &var) < 0) अणु
		/* This shouldn't happen! */
		prपूर्णांकk("mac_vmode_to_var(%d, %d,) failed\n", vmode, cmode);
try_again:
		vmode = VMODE_640_480_60;
		cmode = CMODE_8;
		अगर (mac_vmode_to_var(vmode, cmode, &var) < 0) अणु
			prपूर्णांकk(KERN_ERR "controlfb: mac_vmode_to_var() failed\n");
			वापस -ENXIO;
		पूर्ण
		prपूर्णांकk(KERN_INFO "controlfb: ");
	पूर्ण
	prपूर्णांकk("using video mode %d and color mode %d.\n", vmode, cmode);

	vyres = (p->total_vram - CTRLFB_OFF) / (var.xres << cmode);
	अगर (vyres > var.yres)
		var.yres_भव = vyres;

	/* Apply शेष var */
	var.activate = FB_ACTIVATE_NOW;
	rc = fb_set_var(&p->info, &var);
	अगर (rc && (vmode != VMODE_640_480_60 || cmode != CMODE_8))
		जाओ try_again;

	/* Register with fbdev layer */
	अगर (रेजिस्टर_framebuffer(&p->info) < 0)
		वापस -ENXIO;

	fb_info(&p->info, "control display adapter\n");

	वापस 0;
पूर्ण

अटल व्योम control_cleanup(व्योम)
अणु
	काष्ठा fb_info_control	*p = control_fb;

	अगर (!p)
		वापस;

	अगर (p->cmap_regs)
		iounmap(p->cmap_regs);
	अगर (p->control_regs)
		iounmap(p->control_regs);
	अगर (p->frame_buffer) अणु
		अगर (p->control_use_bank2)
			p->frame_buffer -= 0x600000;
		iounmap(p->frame_buffer);
	पूर्ण
	अगर (p->cmap_regs_phys)
		release_mem_region(p->cmap_regs_phys, 0x1000);
	अगर (p->control_regs_phys)
		release_mem_region(p->control_regs_phys, p->control_regs_size);
	अगर (p->fb_orig_base)
		release_mem_region(p->fb_orig_base, p->fb_orig_size);
	kमुक्त(p);
पूर्ण

/*
 * find "control" and initialize
 */
अटल पूर्णांक __init control_of_init(काष्ठा device_node *dp)
अणु
	काष्ठा fb_info_control	*p;
	काष्ठा resource		fb_res, reg_res;

	अगर (control_fb) अणु
		prपूर्णांकk(KERN_ERR "controlfb: only one control is supported\n");
		वापस -ENXIO;
	पूर्ण

	अगर (of_pci_address_to_resource(dp, 2, &fb_res) ||
	    of_pci_address_to_resource(dp, 1, &reg_res)) अणु
		prपूर्णांकk(KERN_ERR "can't get 2 addresses for control\n");
		वापस -ENXIO;
	पूर्ण
	p = kzalloc(माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;
	control_fb = p;	/* save it क्रम cleanups */

	/* Map in frame buffer and रेजिस्टरs */
	p->fb_orig_base = fb_res.start;
	p->fb_orig_size = resource_size(&fb_res);
	/* use the big-endian aperture (??) */
	p->frame_buffer_phys = fb_res.start + 0x800000;
	p->control_regs_phys = reg_res.start;
	p->control_regs_size = resource_size(&reg_res);

	अगर (!p->fb_orig_base ||
	    !request_mem_region(p->fb_orig_base,p->fb_orig_size,"controlfb")) अणु
		p->fb_orig_base = 0;
		जाओ error_out;
	पूर्ण
	/* map at most 8MB क्रम the frame buffer */
	p->frame_buffer = ioremap_wt(p->frame_buffer_phys, 0x800000);

	अगर (!p->control_regs_phys ||
	    !request_mem_region(p->control_regs_phys, p->control_regs_size,
	    "controlfb regs")) अणु
		p->control_regs_phys = 0;
		जाओ error_out;
	पूर्ण
	p->control_regs = ioremap(p->control_regs_phys, p->control_regs_size);

	p->cmap_regs_phys = 0xf301b000;	 /* XXX not in prom? */
	अगर (!request_mem_region(p->cmap_regs_phys, 0x1000, "controlfb cmap")) अणु
		p->cmap_regs_phys = 0;
		जाओ error_out;
	पूर्ण
	p->cmap_regs = ioremap(p->cmap_regs_phys, 0x1000);

	अगर (!p->cmap_regs || !p->control_regs || !p->frame_buffer)
		जाओ error_out;

	find_vram_size(p);
	अगर (!p->total_vram)
		जाओ error_out;

	अगर (init_control(p) < 0)
		जाओ error_out;

	वापस 0;

error_out:
	control_cleanup();
	वापस -ENXIO;
पूर्ण

अटल पूर्णांक __init control_init(व्योम)
अणु
	काष्ठा device_node *dp;
	अक्षर *option = शून्य;
	पूर्णांक ret = -ENXIO;

	अगर (fb_get_options("controlfb", &option))
		वापस -ENODEV;
	control_setup(option);

	dp = of_find_node_by_name(शून्य, "control");
	अगर (dp && !control_of_init(dp))
		ret = 0;
	of_node_put(dp);

	वापस ret;
पूर्ण

device_initcall(control_init);
