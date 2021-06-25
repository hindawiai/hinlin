<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/console.h>
#अगर_घोषित CONFIG_MTRR
#समावेश <यंत्र/mtrr.h>
#पूर्ण_अगर
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/screen_info.h>
#समावेश <linux/sizes.h>

#समावेश "sm750.h"
#समावेश "ddk750.h"
#समावेश "sm750_accel.h"

व्योम __iomem *mmio750;

पूर्णांक hw_sm750_map(काष्ठा sm750_dev *sm750_dev, काष्ठा pci_dev *pdev)
अणु
	पूर्णांक ret;

	ret = 0;

	sm750_dev->vidreg_start  = pci_resource_start(pdev, 1);
	sm750_dev->vidreg_size = SZ_2M;

	pr_info("mmio phyAddr = %lx\n", sm750_dev->vidreg_start);

	/*
	 * reserve the vidreg space of smi adaptor
	 * अगर you करो this, you need to add release region code
	 * in lynxfb_हटाओ, or memory will not be mapped again
	 * successfully
	 */
	ret = pci_request_region(pdev, 1, "sm750fb");
	अगर (ret) अणु
		pr_err("Can not request PCI regions.\n");
		जाओ निकास;
	पूर्ण

	/* now map mmio and vidmem */
	sm750_dev->pvReg = ioremap(sm750_dev->vidreg_start,
				   sm750_dev->vidreg_size);
	अगर (!sm750_dev->pvReg) अणु
		pr_err("mmio failed\n");
		ret = -EFAULT;
		जाओ निकास;
	पूर्ण अन्यथा अणु
		pr_info("mmio virtual addr = %p\n", sm750_dev->pvReg);
	पूर्ण

	sm750_dev->accel.dprBase = sm750_dev->pvReg + DE_BASE_ADDR_TYPE1;
	sm750_dev->accel.dpPortBase = sm750_dev->pvReg + DE_PORT_ADDR_TYPE1;

	mmio750 = sm750_dev->pvReg;
	sm750_set_chip_type(sm750_dev->devid, sm750_dev->revid);

	sm750_dev->vidmem_start = pci_resource_start(pdev, 0);
	/*
	 * करोn't use pdev_resource[x].end - resource[x].start to
	 * calculate the resource size, it's only the maximum available
	 * size but not the actual size, using
	 * @ddk750_get_vm_size function can be safe.
	 */
	sm750_dev->vidmem_size = ddk750_get_vm_size();
	pr_info("video memory phyAddr = %lx, size = %u bytes\n",
		sm750_dev->vidmem_start, sm750_dev->vidmem_size);

	/* reserve the vidmem space of smi adaptor */
	sm750_dev->pvMem = ioremap_wc(sm750_dev->vidmem_start,
				      sm750_dev->vidmem_size);
	अगर (!sm750_dev->pvMem) अणु
		pr_err("Map video memory failed\n");
		ret = -EFAULT;
		जाओ निकास;
	पूर्ण अन्यथा अणु
		pr_info("video memory vaddr = %p\n", sm750_dev->pvMem);
	पूर्ण
निकास:
	वापस ret;
पूर्ण

पूर्णांक hw_sm750_inithw(काष्ठा sm750_dev *sm750_dev, काष्ठा pci_dev *pdev)
अणु
	काष्ठा init_status *parm;

	parm = &sm750_dev->initParm;
	अगर (parm->chip_clk == 0)
		parm->chip_clk = (sm750_get_chip_type() == SM750LE) ?
						DEFAULT_SM750LE_CHIP_CLOCK :
						DEFAULT_SM750_CHIP_CLOCK;

	अगर (parm->mem_clk == 0)
		parm->mem_clk = parm->chip_clk;
	अगर (parm->master_clk == 0)
		parm->master_clk = parm->chip_clk / 3;

	ddk750_init_hw((काष्ठा initchip_param *)&sm750_dev->initParm);
	/* क्रम sm718, खोलो pci burst */
	अगर (sm750_dev->devid == 0x718) अणु
		poke32(SYSTEM_CTRL,
		       peek32(SYSTEM_CTRL) | SYSTEM_CTRL_PCI_BURST);
	पूर्ण

	अगर (sm750_get_chip_type() != SM750LE) अणु
		अचिन्हित पूर्णांक val;
		/* करोes user need CRT? */
		अगर (sm750_dev->nocrt) अणु
			poke32(MISC_CTRL,
			       peek32(MISC_CTRL) | MISC_CTRL_DAC_POWER_OFF);
			/* shut off dpms */
			val = peek32(SYSTEM_CTRL) & ~SYSTEM_CTRL_DPMS_MASK;
			val |= SYSTEM_CTRL_DPMS_VPHN;
			poke32(SYSTEM_CTRL, val);
		पूर्ण अन्यथा अणु
			poke32(MISC_CTRL,
			       peek32(MISC_CTRL) & ~MISC_CTRL_DAC_POWER_OFF);
			/* turn on dpms */
			val = peek32(SYSTEM_CTRL) & ~SYSTEM_CTRL_DPMS_MASK;
			val |= SYSTEM_CTRL_DPMS_VPHP;
			poke32(SYSTEM_CTRL, val);
		पूर्ण

		val = peek32(PANEL_DISPLAY_CTRL) &
			~(PANEL_DISPLAY_CTRL_DUAL_DISPLAY |
			  PANEL_DISPLAY_CTRL_DOUBLE_PIXEL);
		चयन (sm750_dev->pnltype) अणु
		हाल sm750_24TFT:
			अवरोध;
		हाल sm750_द्विगुनTFT:
			val |= PANEL_DISPLAY_CTRL_DOUBLE_PIXEL;
			अवरोध;
		हाल sm750_dualTFT:
			val |= PANEL_DISPLAY_CTRL_DUAL_DISPLAY;
			अवरोध;
		पूर्ण
		poke32(PANEL_DISPLAY_CTRL, val);
	पूर्ण अन्यथा अणु
		/*
		 * क्रम 750LE, no DVI chip initialization
		 * makes Monitor no संकेत
		 *
		 * Set up GPIO क्रम software I2C to program DVI chip in the
		 * Xilinx SP605 board, in order to have video संकेत.
		 */
		sm750_sw_i2c_init(0, 1);

		/*
		 * Customer may NOT use CH7301 DVI chip, which has to be
		 * initialized dअगरferently.
		 */
		अगर (sm750_sw_i2c_पढ़ो_reg(0xec, 0x4a) == 0x95) अणु
			/*
			 * The following रेजिस्टर values क्रम CH7301 are from
			 * Chrontel app note and our experiment.
			 */
			pr_info("yes,CH7301 DVI chip found\n");
			sm750_sw_i2c_ग_लिखो_reg(0xec, 0x1d, 0x16);
			sm750_sw_i2c_ग_लिखो_reg(0xec, 0x21, 0x9);
			sm750_sw_i2c_ग_लिखो_reg(0xec, 0x49, 0xC0);
			pr_info("okay,CH7301 DVI chip setup done\n");
		पूर्ण
	पूर्ण

	/* init 2d engine */
	अगर (!sm750_dev->accel_off)
		hw_sm750_initAccel(sm750_dev);

	वापस 0;
पूर्ण

पूर्णांक hw_sm750_output_setMode(काष्ठा lynxfb_output *output,
			    काष्ठा fb_var_screeninfo *var,
			    काष्ठा fb_fix_screeninfo *fix)
अणु
	पूर्णांक ret;
	क्रमागत disp_output disp_set;
	पूर्णांक channel;

	ret = 0;
	disp_set = 0;
	channel = *output->channel;

	अगर (sm750_get_chip_type() != SM750LE) अणु
		अगर (channel == sm750_primary) अणु
			pr_info("primary channel\n");
			अगर (output->paths & sm750_panel)
				disp_set |= करो_LCD1_PRI;
			अगर (output->paths & sm750_crt)
				disp_set |= करो_CRT_PRI;

		पूर्ण अन्यथा अणु
			pr_info("secondary channel\n");
			अगर (output->paths & sm750_panel)
				disp_set |= करो_LCD1_SEC;
			अगर (output->paths & sm750_crt)
				disp_set |= करो_CRT_SEC;
		पूर्ण
		ddk750_set_logical_disp_out(disp_set);
	पूर्ण अन्यथा अणु
		/* just खोलो DISPLAY_CONTROL_750LE रेजिस्टर bit 3:0 */
		u32 reg;

		reg = peek32(DISPLAY_CONTROL_750LE);
		reg |= 0xf;
		poke32(DISPLAY_CONTROL_750LE, reg);
	पूर्ण

	pr_info("ddk setlogicdispout done\n");
	वापस ret;
पूर्ण

पूर्णांक hw_sm750_crtc_checkMode(काष्ठा lynxfb_crtc *crtc,
			    काष्ठा fb_var_screeninfo *var)
अणु
	काष्ठा sm750_dev *sm750_dev;
	काष्ठा lynxfb_par *par = container_of(crtc, काष्ठा lynxfb_par, crtc);

	sm750_dev = par->dev;

	चयन (var->bits_per_pixel) अणु
	हाल 8:
	हाल 16:
		अवरोध;
	हाल 32:
		अगर (sm750_dev->revid == SM750LE_REVISION_ID) अणु
			pr_debug("750le do not support 32bpp\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* set the controller's mode क्रम @crtc अक्षरged with @var and @fix parameters */
पूर्णांक hw_sm750_crtc_setMode(काष्ठा lynxfb_crtc *crtc,
			  काष्ठा fb_var_screeninfo *var,
			  काष्ठा fb_fix_screeninfo *fix)
अणु
	पूर्णांक ret, fmt;
	u32 reg;
	काष्ठा mode_parameter modparm;
	क्रमागत घड़ी_प्रकारype घड़ी;
	काष्ठा sm750_dev *sm750_dev;
	काष्ठा lynxfb_par *par;

	ret = 0;
	par = container_of(crtc, काष्ठा lynxfb_par, crtc);
	sm750_dev = par->dev;

	अगर (!sm750_dev->accel_off) अणु
		/* set 2d engine pixel क्रमmat according to mode bpp */
		चयन (var->bits_per_pixel) अणु
		हाल 8:
			fmt = 0;
			अवरोध;
		हाल 16:
			fmt = 1;
			अवरोध;
		हाल 32:
		शेष:
			fmt = 2;
			अवरोध;
		पूर्ण
		sm750_hw_set2dक्रमmat(&sm750_dev->accel, fmt);
	पूर्ण

	/* set timing */
	modparm.pixel_घड़ी = ps_to_hz(var->pixघड़ी);
	modparm.vertical_sync_polarity = (var->sync & FB_SYNC_HOR_HIGH_ACT)
					 ? POS : NEG;
	modparm.horizontal_sync_polarity = (var->sync & FB_SYNC_VERT_HIGH_ACT)
					   ? POS : NEG;
	modparm.घड़ी_phase_polarity = (var->sync & FB_SYNC_COMP_HIGH_ACT)
				       ? POS : NEG;
	modparm.horizontal_display_end = var->xres;
	modparm.horizontal_sync_width = var->hsync_len;
	modparm.horizontal_sync_start = var->xres + var->right_margin;
	modparm.horizontal_total = var->xres + var->left_margin +
				   var->right_margin + var->hsync_len;
	modparm.vertical_display_end = var->yres;
	modparm.vertical_sync_height = var->vsync_len;
	modparm.vertical_sync_start = var->yres + var->lower_margin;
	modparm.vertical_total = var->yres + var->upper_margin +
				 var->lower_margin + var->vsync_len;

	/* choose pll */
	अगर (crtc->channel != sm750_secondary)
		घड़ी = PRIMARY_PLL;
	अन्यथा
		घड़ी = SECONDARY_PLL;

	pr_debug("Request pixel clock = %lu\n", modparm.pixel_घड़ी);
	ret = ddk750_setModeTiming(&modparm, घड़ी);
	अगर (ret) अणु
		pr_err("Set mode timing failed\n");
		जाओ निकास;
	पूर्ण

	अगर (crtc->channel != sm750_secondary) अणु
		/* set pitch, offset, width, start address, etc... */
		poke32(PANEL_FB_ADDRESS,
		       crtc->oScreen & PANEL_FB_ADDRESS_ADDRESS_MASK);

		reg = var->xres * (var->bits_per_pixel >> 3);
		/*
		 * crtc->channel is not equal to par->index on numeric,
		 * be aware of that
		 */
		reg = ALIGN(reg, crtc->line_pad);
		reg = (reg << PANEL_FB_WIDTH_WIDTH_SHIFT) &
		       PANEL_FB_WIDTH_WIDTH_MASK;
		reg |= (fix->line_length & PANEL_FB_WIDTH_OFFSET_MASK);
		poke32(PANEL_FB_WIDTH, reg);

		reg = ((var->xres - 1) << PANEL_WINDOW_WIDTH_WIDTH_SHIFT) &
		       PANEL_WINDOW_WIDTH_WIDTH_MASK;
		reg |= (var->xoffset & PANEL_WINDOW_WIDTH_X_MASK);
		poke32(PANEL_WINDOW_WIDTH, reg);

		reg = (var->yres_भव - 1) <<
		      PANEL_WINDOW_HEIGHT_HEIGHT_SHIFT;
		reg &= PANEL_WINDOW_HEIGHT_HEIGHT_MASK;
		reg |= (var->yoffset & PANEL_WINDOW_HEIGHT_Y_MASK);
		poke32(PANEL_WINDOW_HEIGHT, reg);

		poke32(PANEL_PLANE_TL, 0);

		reg = ((var->yres - 1) << PANEL_PLANE_BR_BOTTOM_SHIFT) &
		       PANEL_PLANE_BR_BOTTOM_MASK;
		reg |= ((var->xres - 1) & PANEL_PLANE_BR_RIGHT_MASK);
		poke32(PANEL_PLANE_BR, reg);

		/* set pixel क्रमmat */
		reg = peek32(PANEL_DISPLAY_CTRL);
		poke32(PANEL_DISPLAY_CTRL, reg | (var->bits_per_pixel >> 4));
	पूर्ण अन्यथा अणु
		/* not implemented now */
		poke32(CRT_FB_ADDRESS, crtc->oScreen);
		reg = var->xres * (var->bits_per_pixel >> 3);
		/*
		 * crtc->channel is not equal to par->index on numeric,
		 * be aware of that
		 */
		reg = ALIGN(reg, crtc->line_pad) << CRT_FB_WIDTH_WIDTH_SHIFT;
		reg &= CRT_FB_WIDTH_WIDTH_MASK;
		reg |= (fix->line_length & CRT_FB_WIDTH_OFFSET_MASK);
		poke32(CRT_FB_WIDTH, reg);

		/* SET PIXEL FORMAT */
		reg = peek32(CRT_DISPLAY_CTRL);
		reg |= ((var->bits_per_pixel >> 4) &
			CRT_DISPLAY_CTRL_FORMAT_MASK);
		poke32(CRT_DISPLAY_CTRL, reg);
	पूर्ण

निकास:
	वापस ret;
पूर्ण

पूर्णांक hw_sm750_setColReg(काष्ठा lynxfb_crtc *crtc, uलघु index,
		       uलघु red, uलघु green, uलघु blue)
अणु
	अटल अचिन्हित पूर्णांक add[] = अणुPANEL_PALETTE_RAM, CRT_PALETTE_RAMपूर्ण;

	poke32(add[crtc->channel] + index * 4,
	       (red << 16) | (green << 8) | blue);
	वापस 0;
पूर्ण

पूर्णांक hw_sm750le_setBLANK(काष्ठा lynxfb_output *output, पूर्णांक blank)
अणु
	पूर्णांक dpms, crtdb;

	चयन (blank) अणु
	हाल FB_BLANK_UNBLANK:
		dpms = CRT_DISPLAY_CTRL_DPMS_0;
		crtdb = 0;
		अवरोध;
	हाल FB_BLANK_NORMAL:
		dpms = CRT_DISPLAY_CTRL_DPMS_0;
		crtdb = CRT_DISPLAY_CTRL_BLANK;
		अवरोध;
	हाल FB_BLANK_VSYNC_SUSPEND:
		dpms = CRT_DISPLAY_CTRL_DPMS_2;
		crtdb = CRT_DISPLAY_CTRL_BLANK;
		अवरोध;
	हाल FB_BLANK_HSYNC_SUSPEND:
		dpms = CRT_DISPLAY_CTRL_DPMS_1;
		crtdb = CRT_DISPLAY_CTRL_BLANK;
		अवरोध;
	हाल FB_BLANK_POWERDOWN:
		dpms = CRT_DISPLAY_CTRL_DPMS_3;
		crtdb = CRT_DISPLAY_CTRL_BLANK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (output->paths & sm750_crt) अणु
		अचिन्हित पूर्णांक val;

		val = peek32(CRT_DISPLAY_CTRL) & ~CRT_DISPLAY_CTRL_DPMS_MASK;
		poke32(CRT_DISPLAY_CTRL, val | dpms);

		val = peek32(CRT_DISPLAY_CTRL) & ~CRT_DISPLAY_CTRL_BLANK;
		poke32(CRT_DISPLAY_CTRL, val | crtdb);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक hw_sm750_setBLANK(काष्ठा lynxfb_output *output, पूर्णांक blank)
अणु
	अचिन्हित पूर्णांक dpms, pps, crtdb;

	dpms = 0;
	pps = 0;
	crtdb = 0;

	चयन (blank) अणु
	हाल FB_BLANK_UNBLANK:
		pr_debug("flag = FB_BLANK_UNBLANK\n");
		dpms = SYSTEM_CTRL_DPMS_VPHP;
		pps = PANEL_DISPLAY_CTRL_DATA;
		अवरोध;
	हाल FB_BLANK_NORMAL:
		pr_debug("flag = FB_BLANK_NORMAL\n");
		dpms = SYSTEM_CTRL_DPMS_VPHP;
		crtdb = CRT_DISPLAY_CTRL_BLANK;
		अवरोध;
	हाल FB_BLANK_VSYNC_SUSPEND:
		dpms = SYSTEM_CTRL_DPMS_VNHP;
		crtdb = CRT_DISPLAY_CTRL_BLANK;
		अवरोध;
	हाल FB_BLANK_HSYNC_SUSPEND:
		dpms = SYSTEM_CTRL_DPMS_VPHN;
		crtdb = CRT_DISPLAY_CTRL_BLANK;
		अवरोध;
	हाल FB_BLANK_POWERDOWN:
		dpms = SYSTEM_CTRL_DPMS_VNHN;
		crtdb = CRT_DISPLAY_CTRL_BLANK;
		अवरोध;
	पूर्ण

	अगर (output->paths & sm750_crt) अणु
		अचिन्हित पूर्णांक val = peek32(SYSTEM_CTRL) & ~SYSTEM_CTRL_DPMS_MASK;

		poke32(SYSTEM_CTRL, val | dpms);

		val = peek32(CRT_DISPLAY_CTRL) & ~CRT_DISPLAY_CTRL_BLANK;
		poke32(CRT_DISPLAY_CTRL, val | crtdb);
	पूर्ण

	अगर (output->paths & sm750_panel) अणु
		अचिन्हित पूर्णांक val = peek32(PANEL_DISPLAY_CTRL);

		val &= ~PANEL_DISPLAY_CTRL_DATA;
		val |= pps;
		poke32(PANEL_DISPLAY_CTRL, val);
	पूर्ण

	वापस 0;
पूर्ण

व्योम hw_sm750_initAccel(काष्ठा sm750_dev *sm750_dev)
अणु
	u32 reg;

	sm750_enable_2d_engine(1);

	अगर (sm750_get_chip_type() == SM750LE) अणु
		reg = peek32(DE_STATE1);
		reg |= DE_STATE1_DE_ABORT;
		poke32(DE_STATE1, reg);

		reg = peek32(DE_STATE1);
		reg &= ~DE_STATE1_DE_ABORT;
		poke32(DE_STATE1, reg);

	पूर्ण अन्यथा अणु
		/* engine reset */
		reg = peek32(SYSTEM_CTRL);
		reg |= SYSTEM_CTRL_DE_ABORT;
		poke32(SYSTEM_CTRL, reg);

		reg = peek32(SYSTEM_CTRL);
		reg &= ~SYSTEM_CTRL_DE_ABORT;
		poke32(SYSTEM_CTRL, reg);
	पूर्ण

	/* call 2d init */
	sm750_dev->accel.de_init(&sm750_dev->accel);
पूर्ण

पूर्णांक hw_sm750le_deWait(व्योम)
अणु
	पूर्णांक i = 0x10000000;
	अचिन्हित पूर्णांक mask = DE_STATE2_DE_STATUS_BUSY | DE_STATE2_DE_FIFO_EMPTY |
		DE_STATE2_DE_MEM_FIFO_EMPTY;

	जबतक (i--) अणु
		अचिन्हित पूर्णांक val = peek32(DE_STATE2);

		अगर ((val & mask) ==
		    (DE_STATE2_DE_FIFO_EMPTY | DE_STATE2_DE_MEM_FIFO_EMPTY))
			वापस 0;
	पूर्ण
	/* समयout error */
	वापस -1;
पूर्ण

पूर्णांक hw_sm750_deWait(व्योम)
अणु
	पूर्णांक i = 0x10000000;
	अचिन्हित पूर्णांक mask = SYSTEM_CTRL_DE_STATUS_BUSY |
		SYSTEM_CTRL_DE_FIFO_EMPTY |
		SYSTEM_CTRL_DE_MEM_FIFO_EMPTY;

	जबतक (i--) अणु
		अचिन्हित पूर्णांक val = peek32(SYSTEM_CTRL);

		अगर ((val & mask) ==
		    (SYSTEM_CTRL_DE_FIFO_EMPTY | SYSTEM_CTRL_DE_MEM_FIFO_EMPTY))
			वापस 0;
	पूर्ण
	/* समयout error */
	वापस -1;
पूर्ण

पूर्णांक hw_sm750_pan_display(काष्ठा lynxfb_crtc *crtc,
			 स्थिर काष्ठा fb_var_screeninfo *var,
			 स्थिर काष्ठा fb_info *info)
अणु
	u32 total;
	/* check params */
	अगर ((var->xoffset + var->xres > var->xres_भव) ||
	    (var->yoffset + var->yres > var->yres_भव)) अणु
		वापस -EINVAL;
	पूर्ण

	total = var->yoffset * info->fix.line_length +
		((var->xoffset * var->bits_per_pixel) >> 3);
	total += crtc->oScreen;
	अगर (crtc->channel == sm750_primary) अणु
		poke32(PANEL_FB_ADDRESS,
		       peek32(PANEL_FB_ADDRESS) |
		       (total & PANEL_FB_ADDRESS_ADDRESS_MASK));
	पूर्ण अन्यथा अणु
		poke32(CRT_FB_ADDRESS,
		       peek32(CRT_FB_ADDRESS) |
		       (total & CRT_FB_ADDRESS_ADDRESS_MASK));
	पूर्ण
	वापस 0;
पूर्ण
