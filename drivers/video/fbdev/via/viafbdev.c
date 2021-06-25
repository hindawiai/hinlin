<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 1998-2009 VIA Technologies, Inc. All Rights Reserved.
 * Copyright 2001-2008 S3 Graphics, Inc. All Rights Reserved.

 */

#समावेश <linux/compiler.h>
#समावेश <linux/module.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/via-core.h>
#समावेश <linux/via_i2c.h>

#घोषणा _MASTER_खाता
#समावेश "global.h"

अटल अक्षर *viafb_name = "Via";
अटल u32 pseuकरो_pal[17];

/* video mode */
अटल अक्षर *viafb_mode;
अटल अक्षर *viafb_mode1;
अटल पूर्णांक viafb_bpp = 32;
अटल पूर्णांक viafb_bpp1 = 32;

अटल अचिन्हित पूर्णांक viafb_second_offset;
अटल पूर्णांक viafb_second_size;

अटल पूर्णांक viafb_accel = 1;

/* Added क्रम specअगरying active devices.*/
अटल अक्षर *viafb_active_dev;

/*Added क्रम specअगरy lcd output port*/
अटल अक्षर *viafb_lcd_port = "";
अटल अक्षर *viafb_dvi_port = "";

अटल व्योम retrieve_device_setting(काष्ठा viafb_ioctl_setting
	*setting_info);
अटल पूर्णांक viafb_pan_display(काष्ठा fb_var_screeninfo *var,
	काष्ठा fb_info *info);

अटल काष्ठा fb_ops viafb_ops;

/* supported output devices on each IGP
 * only CX700, VX800, VX855, VX900 were करोcumented
 * VIA_CRT should be everywhere
 * VIA_6C can be onle pre-CX700 (probably only on CLE266) as 6C is used क्रम PLL
 * source selection on CX700 and later
 * K400 seems to support VIA_96, VIA_DVP1, VIA_LVDSअणु1,2पूर्ण as in viamode.c
 */
अटल स्थिर u32 supported_odev_map[] = अणु
	[UNICHROME_CLE266]	= VIA_CRT | VIA_LDVP0 | VIA_LDVP1,
	[UNICHROME_K400]	= VIA_CRT | VIA_DVP0 | VIA_DVP1 | VIA_LVDS1
				| VIA_LVDS2,
	[UNICHROME_K800]	= VIA_CRT | VIA_DVP0 | VIA_DVP1 | VIA_LVDS1
				| VIA_LVDS2,
	[UNICHROME_PM800]	= VIA_CRT | VIA_DVP0 | VIA_DVP1 | VIA_LVDS1
				| VIA_LVDS2,
	[UNICHROME_CN700]	= VIA_CRT | VIA_DVP0 | VIA_DVP1 | VIA_LVDS1
				| VIA_LVDS2,
	[UNICHROME_CX700]	= VIA_CRT | VIA_DVP1 | VIA_LVDS1 | VIA_LVDS2,
	[UNICHROME_CN750]	= VIA_CRT | VIA_DVP1 | VIA_LVDS1 | VIA_LVDS2,
	[UNICHROME_K8M890]	= VIA_CRT | VIA_DVP1 | VIA_LVDS1 | VIA_LVDS2,
	[UNICHROME_P4M890]	= VIA_CRT | VIA_DVP1 | VIA_LVDS1 | VIA_LVDS2,
	[UNICHROME_P4M900]	= VIA_CRT | VIA_DVP1 | VIA_LVDS1 | VIA_LVDS2,
	[UNICHROME_VX800]	= VIA_CRT | VIA_DVP1 | VIA_LVDS1 | VIA_LVDS2,
	[UNICHROME_VX855]	= VIA_CRT | VIA_DVP1 | VIA_LVDS1 | VIA_LVDS2,
	[UNICHROME_VX900]	= VIA_CRT | VIA_DVP1 | VIA_LVDS1 | VIA_LVDS2,
पूर्ण;

अटल व्योम viafb_fill_var_color_info(काष्ठा fb_var_screeninfo *var, u8 depth)
अणु
	var->grayscale = 0;
	var->red.msb_right = 0;
	var->green.msb_right = 0;
	var->blue.msb_right = 0;
	var->transp.offset = 0;
	var->transp.length = 0;
	var->transp.msb_right = 0;
	var->nonstd = 0;
	चयन (depth) अणु
	हाल 8:
		var->bits_per_pixel = 8;
		var->red.offset = 0;
		var->green.offset = 0;
		var->blue.offset = 0;
		var->red.length = 8;
		var->green.length = 8;
		var->blue.length = 8;
		अवरोध;
	हाल 15:
		var->bits_per_pixel = 16;
		var->red.offset = 10;
		var->green.offset = 5;
		var->blue.offset = 0;
		var->red.length = 5;
		var->green.length = 5;
		var->blue.length = 5;
		अवरोध;
	हाल 16:
		var->bits_per_pixel = 16;
		var->red.offset = 11;
		var->green.offset = 5;
		var->blue.offset = 0;
		var->red.length = 5;
		var->green.length = 6;
		var->blue.length = 5;
		अवरोध;
	हाल 24:
		var->bits_per_pixel = 32;
		var->red.offset = 16;
		var->green.offset = 8;
		var->blue.offset = 0;
		var->red.length = 8;
		var->green.length = 8;
		var->blue.length = 8;
		अवरोध;
	हाल 30:
		var->bits_per_pixel = 32;
		var->red.offset = 20;
		var->green.offset = 10;
		var->blue.offset = 0;
		var->red.length = 10;
		var->green.length = 10;
		var->blue.length = 10;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम viafb_update_fix(काष्ठा fb_info *info)
अणु
	u32 bpp = info->var.bits_per_pixel;

	info->fix.visual =
		bpp == 8 ? FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_TRUECOLOR;
	info->fix.line_length = ALIGN(info->var.xres_भव * bpp / 8,
		VIA_PITCH_SIZE);
पूर्ण

अटल व्योम viafb_setup_fixinfo(काष्ठा fb_fix_screeninfo *fix,
	काष्ठा viafb_par *viaparinfo)
अणु
	स_रखो(fix, 0, माप(काष्ठा fb_fix_screeninfo));
	म_नकल(fix->id, viafb_name);

	fix->smem_start = viaparinfo->fbmem;
	fix->smem_len = viaparinfo->fbmem_मुक्त;

	fix->type = FB_TYPE_PACKED_PIXELS;
	fix->type_aux = 0;
	fix->visual = FB_VISUAL_TRUECOLOR;

	fix->xpanstep = fix->ywrapstep = 0;
	fix->ypanstep = 1;

	/* Just tell the accel name */
	viafbinfo->fix.accel = FB_ACCEL_VIA_UNICHROME;
पूर्ण
अटल पूर्णांक viafb_खोलो(काष्ठा fb_info *info, पूर्णांक user)
अणु
	DEBUG_MSG(KERN_INFO "viafb_open!\n");
	वापस 0;
पूर्ण

अटल पूर्णांक viafb_release(काष्ठा fb_info *info, पूर्णांक user)
अणु
	DEBUG_MSG(KERN_INFO "viafb_release!\n");
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक get_var_refresh(काष्ठा fb_var_screeninfo *var)
अणु
	u32 htotal, vtotal;

	htotal = var->left_margin + var->xres + var->right_margin
		+ var->hsync_len;
	vtotal = var->upper_margin + var->yres + var->lower_margin
		+ var->vsync_len;
	वापस PICOS2KHZ(var->pixघड़ी) * 1000 / (htotal * vtotal);
पूर्ण

अटल पूर्णांक viafb_check_var(काष्ठा fb_var_screeninfo *var,
	काष्ठा fb_info *info)
अणु
	पूर्णांक depth, refresh;
	काष्ठा viafb_par *ppar = info->par;
	u32 line;

	DEBUG_MSG(KERN_INFO "viafb_check_var!\n");
	/* Sanity check */
	/* HW neither support पूर्णांकerlacte nor द्विगुन-scaned mode */
	अगर (var->vmode & FB_VMODE_INTERLACED || var->vmode & FB_VMODE_DOUBLE)
		वापस -EINVAL;

	/* the refresh rate is not important here, as we only want to know
	 * whether the resolution exists
	 */
	अगर (!viafb_get_best_mode(var->xres, var->yres, 60)) अणु
		DEBUG_MSG(KERN_INFO
			  "viafb: Mode %dx%dx%d not supported!!\n",
			  var->xres, var->yres, var->bits_per_pixel);
		वापस -EINVAL;
	पूर्ण

	depth = fb_get_color_depth(var, &info->fix);
	अगर (!depth)
		depth = var->bits_per_pixel;

	अगर (depth < 0 || depth > 32)
		वापस -EINVAL;
	अन्यथा अगर (!depth)
		depth = 24;
	अन्यथा अगर (depth == 15 && viafb_dual_fb && ppar->iga_path == IGA1)
		depth = 15;
	अन्यथा अगर (depth == 30)
		depth = 30;
	अन्यथा अगर (depth <= 8)
		depth = 8;
	अन्यथा अगर (depth <= 16)
		depth = 16;
	अन्यथा
		depth = 24;

	viafb_fill_var_color_info(var, depth);
	अगर (var->xres_भव < var->xres)
		var->xres_भव = var->xres;

	line = ALIGN(var->xres_भव * var->bits_per_pixel / 8,
		VIA_PITCH_SIZE);
	अगर (line > VIA_PITCH_MAX || line * var->yres_भव > ppar->memsize)
		वापस -EINVAL;

	/* Based on var passed in to calculate the refresh,
	 * because our driver use some modes special.
	 */
	refresh = viafb_get_refresh(var->xres, var->yres,
		get_var_refresh(var));

	/* Adjust var according to our driver's own table */
	viafb_fill_var_timing_info(var,
		viafb_get_best_mode(var->xres, var->yres, refresh));
	अगर (var->accel_flags & FB_ACCELF_TEXT &&
		!ppar->shared->vdev->engine_mmio)
		var->accel_flags = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक viafb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा viafb_par *viapar = info->par;
	पूर्णांक refresh;
	DEBUG_MSG(KERN_INFO "viafb_set_par!\n");

	viafb_update_fix(info);
	viapar->depth = fb_get_color_depth(&info->var, &info->fix);
	viafb_update_device_setting(viafbinfo->var.xres, viafbinfo->var.yres,
		viafbinfo->var.bits_per_pixel, 0);

	अगर (viafb_dual_fb) अणु
		viafb_update_device_setting(viafbinfo1->var.xres,
			viafbinfo1->var.yres, viafbinfo1->var.bits_per_pixel,
			1);
	पूर्ण अन्यथा अगर (viafb_SAMM_ON == 1) अणु
		DEBUG_MSG(KERN_INFO
		"viafb_second_xres = %d, viafb_second_yres = %d, bpp = %d\n",
			  viafb_second_xres, viafb_second_yres, viafb_bpp1);

		viafb_update_device_setting(viafb_second_xres,
			viafb_second_yres, viafb_bpp1, 1);
	पूर्ण

	refresh = get_var_refresh(&info->var);
	अगर (viafb_dual_fb && viapar->iga_path == IGA2) अणु
		viafb_bpp1 = info->var.bits_per_pixel;
		viafb_refresh1 = refresh;
	पूर्ण अन्यथा अणु
		viafb_bpp = info->var.bits_per_pixel;
		viafb_refresh = refresh;
	पूर्ण

	अगर (info->var.accel_flags & FB_ACCELF_TEXT)
		info->flags &= ~FBINFO_HWACCEL_DISABLED;
	अन्यथा
		info->flags |= FBINFO_HWACCEL_DISABLED;
	viafb_seपंचांगode();
	viafb_pan_display(&info->var, info);

	वापस 0;
पूर्ण

/* Set one color रेजिस्टर */
अटल पूर्णांक viafb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
अचिन्हित blue, अचिन्हित transp, काष्ठा fb_info *info)
अणु
	काष्ठा viafb_par *viapar = info->par;
	u32 r, g, b;

	अगर (info->fix.visual == FB_VISUAL_PSEUDOCOLOR) अणु
		अगर (regno > 255)
			वापस -EINVAL;

		अगर (!viafb_dual_fb || viapar->iga_path == IGA1)
			viafb_set_primary_color_रेजिस्टर(regno, red >> 8,
				green >> 8, blue >> 8);

		अगर (!viafb_dual_fb || viapar->iga_path == IGA2)
			viafb_set_secondary_color_रेजिस्टर(regno, red >> 8,
				green >> 8, blue >> 8);
	पूर्ण अन्यथा अणु
		अगर (regno > 15)
			वापस -EINVAL;

		r = (red >> (16 - info->var.red.length))
			<< info->var.red.offset;
		b = (blue >> (16 - info->var.blue.length))
			<< info->var.blue.offset;
		g = (green >> (16 - info->var.green.length))
			<< info->var.green.offset;
		((u32 *) info->pseuकरो_palette)[regno] = r | g | b;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक viafb_pan_display(काष्ठा fb_var_screeninfo *var,
	काष्ठा fb_info *info)
अणु
	काष्ठा viafb_par *viapar = info->par;
	u32 vram_addr = viapar->vram_addr
		+ var->yoffset * info->fix.line_length
		+ var->xoffset * info->var.bits_per_pixel / 8;

	DEBUG_MSG(KERN_DEBUG "viafb_pan_display, address = %d\n", vram_addr);
	अगर (!viafb_dual_fb) अणु
		via_set_primary_address(vram_addr);
		via_set_secondary_address(vram_addr);
	पूर्ण अन्यथा अगर (viapar->iga_path == IGA1)
		via_set_primary_address(vram_addr);
	अन्यथा
		via_set_secondary_address(vram_addr);

	वापस 0;
पूर्ण

अटल पूर्णांक viafb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	DEBUG_MSG(KERN_INFO "viafb_blank!\n");
	/* clear DPMS setting */

	चयन (blank_mode) अणु
	हाल FB_BLANK_UNBLANK:
		/* Screen: On, HSync: On, VSync: On */
		/* control CRT monitor घातer management */
		via_set_state(VIA_CRT, VIA_STATE_ON);
		अवरोध;
	हाल FB_BLANK_HSYNC_SUSPEND:
		/* Screen: Off, HSync: Off, VSync: On */
		/* control CRT monitor घातer management */
		via_set_state(VIA_CRT, VIA_STATE_STANDBY);
		अवरोध;
	हाल FB_BLANK_VSYNC_SUSPEND:
		/* Screen: Off, HSync: On, VSync: Off */
		/* control CRT monitor घातer management */
		via_set_state(VIA_CRT, VIA_STATE_SUSPEND);
		अवरोध;
	हाल FB_BLANK_POWERDOWN:
		/* Screen: Off, HSync: Off, VSync: Off */
		/* control CRT monitor घातer management */
		via_set_state(VIA_CRT, VIA_STATE_OFF);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक viafb_ioctl(काष्ठा fb_info *info, u_पूर्णांक cmd, u_दीर्घ arg)
अणु
	जोड़ अणु
		काष्ठा viafb_ioctl_mode viamode;
		काष्ठा viafb_ioctl_samm viasamm;
		काष्ठा viafb_driver_version driver_version;
		काष्ठा fb_var_screeninfo sec_var;
		काष्ठा _panel_size_pos_info panel_pos_size_para;
		काष्ठा viafb_ioctl_setting viafb_setting;
		काष्ठा device_t active_dev;
	पूर्ण u;
	u32 state_info = 0;
	u32 *viafb_gamma_table;
	अक्षर driver_name[] = "viafb";

	u32 __user *argp = (u32 __user *) arg;
	u32 gpu32;

	DEBUG_MSG(KERN_INFO "viafb_ioctl: 0x%X !!\n", cmd);
	prपूर्णांकk(KERN_WARNING "viafb_ioctl: Please avoid this interface as it is unstable and might change or vanish at any time!\n");
	स_रखो(&u, 0, माप(u));

	चयन (cmd) अणु
	हाल VIAFB_GET_CHIP_INFO:
		अगर (copy_to_user(argp, viaparinfo->chip_info,
				माप(काष्ठा chip_inक्रमmation)))
			वापस -EFAULT;
		अवरोध;
	हाल VIAFB_GET_INFO_SIZE:
		वापस put_user((u32)माप(काष्ठा viafb_ioctl_info), argp);
	हाल VIAFB_GET_INFO:
		वापस viafb_ioctl_get_viafb_info(arg);
	हाल VIAFB_HOTPLUG:
		वापस put_user(viafb_ioctl_hotplug(info->var.xres,
					      info->var.yres,
					      info->var.bits_per_pixel), argp);
	हाल VIAFB_SET_HOTPLUG_FLAG:
		अगर (copy_from_user(&gpu32, argp, माप(gpu32)))
			वापस -EFAULT;
		viafb_hotplug = (gpu32) ? 1 : 0;
		अवरोध;
	हाल VIAFB_GET_RESOLUTION:
		u.viamode.xres = (u32) viafb_hotplug_Xres;
		u.viamode.yres = (u32) viafb_hotplug_Yres;
		u.viamode.refresh = (u32) viafb_hotplug_refresh;
		u.viamode.bpp = (u32) viafb_hotplug_bpp;
		अगर (viafb_SAMM_ON == 1) अणु
			u.viamode.xres_sec = viafb_second_xres;
			u.viamode.yres_sec = viafb_second_yres;
			u.viamode.भव_xres_sec = viafb_dual_fb ? viafbinfo1->var.xres_भव : viafbinfo->var.xres_भव;
			u.viamode.भव_yres_sec = viafb_dual_fb ? viafbinfo1->var.yres_भव : viafbinfo->var.yres_भव;
			u.viamode.refresh_sec = viafb_refresh1;
			u.viamode.bpp_sec = viafb_bpp1;
		पूर्ण अन्यथा अणु
			u.viamode.xres_sec = 0;
			u.viamode.yres_sec = 0;
			u.viamode.भव_xres_sec = 0;
			u.viamode.भव_yres_sec = 0;
			u.viamode.refresh_sec = 0;
			u.viamode.bpp_sec = 0;
		पूर्ण
		अगर (copy_to_user(argp, &u.viamode, माप(u.viamode)))
			वापस -EFAULT;
		अवरोध;
	हाल VIAFB_GET_SAMM_INFO:
		u.viasamm.samm_status = viafb_SAMM_ON;

		अगर (viafb_SAMM_ON == 1) अणु
			अगर (viafb_dual_fb) अणु
				u.viasamm.size_prim = viaparinfo->fbmem_मुक्त;
				u.viasamm.size_sec = viaparinfo1->fbmem_मुक्त;
			पूर्ण अन्यथा अणु
				अगर (viafb_second_size) अणु
					u.viasamm.size_prim =
					    viaparinfo->fbmem_मुक्त -
					    viafb_second_size * 1024 * 1024;
					u.viasamm.size_sec =
					    viafb_second_size * 1024 * 1024;
				पूर्ण अन्यथा अणु
					u.viasamm.size_prim =
					    viaparinfo->fbmem_मुक्त >> 1;
					u.viasamm.size_sec =
					    (viaparinfo->fbmem_मुक्त >> 1);
				पूर्ण
			पूर्ण
			u.viasamm.mem_base = viaparinfo->fbmem;
			u.viasamm.offset_sec = viafb_second_offset;
		पूर्ण अन्यथा अणु
			u.viasamm.size_prim =
			    viaparinfo->memsize - viaparinfo->fbmem_used;
			u.viasamm.size_sec = 0;
			u.viasamm.mem_base = viaparinfo->fbmem;
			u.viasamm.offset_sec = 0;
		पूर्ण

		अगर (copy_to_user(argp, &u.viasamm, माप(u.viasamm)))
			वापस -EFAULT;

		अवरोध;
	हाल VIAFB_TURN_ON_OUTPUT_DEVICE:
		अगर (copy_from_user(&gpu32, argp, माप(gpu32)))
			वापस -EFAULT;
		अगर (gpu32 & CRT_Device)
			via_set_state(VIA_CRT, VIA_STATE_ON);
		अगर (gpu32 & DVI_Device)
			viafb_dvi_enable();
		अगर (gpu32 & LCD_Device)
			viafb_lcd_enable();
		अवरोध;
	हाल VIAFB_TURN_OFF_OUTPUT_DEVICE:
		अगर (copy_from_user(&gpu32, argp, माप(gpu32)))
			वापस -EFAULT;
		अगर (gpu32 & CRT_Device)
			via_set_state(VIA_CRT, VIA_STATE_OFF);
		अगर (gpu32 & DVI_Device)
			viafb_dvi_disable();
		अगर (gpu32 & LCD_Device)
			viafb_lcd_disable();
		अवरोध;
	हाल VIAFB_GET_DEVICE:
		u.active_dev.crt = viafb_CRT_ON;
		u.active_dev.dvi = viafb_DVI_ON;
		u.active_dev.lcd = viafb_LCD_ON;
		u.active_dev.samm = viafb_SAMM_ON;
		u.active_dev.primary_dev = viafb_primary_dev;

		u.active_dev.lcd_dsp_cent = viafb_lcd_dsp_method;
		u.active_dev.lcd_panel_id = viafb_lcd_panel_id;
		u.active_dev.lcd_mode = viafb_lcd_mode;

		u.active_dev.xres = viafb_hotplug_Xres;
		u.active_dev.yres = viafb_hotplug_Yres;

		u.active_dev.xres1 = viafb_second_xres;
		u.active_dev.yres1 = viafb_second_yres;

		u.active_dev.bpp = viafb_bpp;
		u.active_dev.bpp1 = viafb_bpp1;
		u.active_dev.refresh = viafb_refresh;
		u.active_dev.refresh1 = viafb_refresh1;

		u.active_dev.epia_dvi = viafb_platक्रमm_epia_dvi;
		u.active_dev.lcd_dual_edge = viafb_device_lcd_dualedge;
		u.active_dev.bus_width = viafb_bus_width;

		अगर (copy_to_user(argp, &u.active_dev, माप(u.active_dev)))
			वापस -EFAULT;
		अवरोध;

	हाल VIAFB_GET_DRIVER_VERSION:
		u.driver_version.iMajorNum = VERSION_MAJOR;
		u.driver_version.iKernelNum = VERSION_KERNEL;
		u.driver_version.iOSNum = VERSION_OS;
		u.driver_version.iMinorNum = VERSION_MINOR;

		अगर (copy_to_user(argp, &u.driver_version,
			माप(u.driver_version)))
			वापस -EFAULT;

		अवरोध;

	हाल VIAFB_GET_DEVICE_INFO:

		retrieve_device_setting(&u.viafb_setting);

		अगर (copy_to_user(argp, &u.viafb_setting,
				 माप(u.viafb_setting)))
			वापस -EFAULT;

		अवरोध;

	हाल VIAFB_GET_DEVICE_SUPPORT:
		viafb_get_device_support_state(&state_info);
		अगर (put_user(state_info, argp))
			वापस -EFAULT;
		अवरोध;

	हाल VIAFB_GET_DEVICE_CONNECT:
		viafb_get_device_connect_state(&state_info);
		अगर (put_user(state_info, argp))
			वापस -EFAULT;
		अवरोध;

	हाल VIAFB_GET_PANEL_SUPPORT_EXPAND:
		state_info =
		    viafb_lcd_get_support_expand_state(info->var.xres,
						 info->var.yres);
		अगर (put_user(state_info, argp))
			वापस -EFAULT;
		अवरोध;

	हाल VIAFB_GET_DRIVER_NAME:
		अगर (copy_to_user(argp, driver_name, माप(driver_name)))
			वापस -EFAULT;
		अवरोध;

	हाल VIAFB_SET_GAMMA_LUT:
		viafb_gamma_table = memdup_user(argp, 256 * माप(u32));
		अगर (IS_ERR(viafb_gamma_table))
			वापस PTR_ERR(viafb_gamma_table);
		viafb_set_gamma_table(viafb_bpp, viafb_gamma_table);
		kमुक्त(viafb_gamma_table);
		अवरोध;

	हाल VIAFB_GET_GAMMA_LUT:
		viafb_gamma_table = kदो_स्मृति_array(256, माप(u32),
						  GFP_KERNEL);
		अगर (!viafb_gamma_table)
			वापस -ENOMEM;
		viafb_get_gamma_table(viafb_gamma_table);
		अगर (copy_to_user(argp, viafb_gamma_table,
			256 * माप(u32))) अणु
			kमुक्त(viafb_gamma_table);
			वापस -EFAULT;
		पूर्ण
		kमुक्त(viafb_gamma_table);
		अवरोध;

	हाल VIAFB_GET_GAMMA_SUPPORT_STATE:
		viafb_get_gamma_support_state(viafb_bpp, &state_info);
		अगर (put_user(state_info, argp))
			वापस -EFAULT;
		अवरोध;
	हाल VIAFB_SYNC_SURFACE:
		DEBUG_MSG(KERN_INFO "lobo VIAFB_SYNC_SURFACE\n");
		अवरोध;
	हाल VIAFB_GET_DRIVER_CAPS:
		अवरोध;

	हाल VIAFB_GET_PANEL_MAX_SIZE:
		अगर (copy_from_user(&u.panel_pos_size_para, argp,
				   माप(u.panel_pos_size_para)))
			वापस -EFAULT;
		u.panel_pos_size_para.x = u.panel_pos_size_para.y = 0;
		अगर (copy_to_user(argp, &u.panel_pos_size_para,
		     माप(u.panel_pos_size_para)))
			वापस -EFAULT;
		अवरोध;
	हाल VIAFB_GET_PANEL_MAX_POSITION:
		अगर (copy_from_user(&u.panel_pos_size_para, argp,
				   माप(u.panel_pos_size_para)))
			वापस -EFAULT;
		u.panel_pos_size_para.x = u.panel_pos_size_para.y = 0;
		अगर (copy_to_user(argp, &u.panel_pos_size_para,
				 माप(u.panel_pos_size_para)))
			वापस -EFAULT;
		अवरोध;

	हाल VIAFB_GET_PANEL_POSITION:
		अगर (copy_from_user(&u.panel_pos_size_para, argp,
				   माप(u.panel_pos_size_para)))
			वापस -EFAULT;
		u.panel_pos_size_para.x = u.panel_pos_size_para.y = 0;
		अगर (copy_to_user(argp, &u.panel_pos_size_para,
				 माप(u.panel_pos_size_para)))
			वापस -EFAULT;
		अवरोध;
	हाल VIAFB_GET_PANEL_SIZE:
		अगर (copy_from_user(&u.panel_pos_size_para, argp,
				   माप(u.panel_pos_size_para)))
			वापस -EFAULT;
		u.panel_pos_size_para.x = u.panel_pos_size_para.y = 0;
		अगर (copy_to_user(argp, &u.panel_pos_size_para,
				 माप(u.panel_pos_size_para)))
			वापस -EFAULT;
		अवरोध;

	हाल VIAFB_SET_PANEL_POSITION:
		अगर (copy_from_user(&u.panel_pos_size_para, argp,
				   माप(u.panel_pos_size_para)))
			वापस -EFAULT;
		अवरोध;
	हाल VIAFB_SET_PANEL_SIZE:
		अगर (copy_from_user(&u.panel_pos_size_para, argp,
				   माप(u.panel_pos_size_para)))
			वापस -EFAULT;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम viafb_fillrect(काष्ठा fb_info *info,
	स्थिर काष्ठा fb_fillrect *rect)
अणु
	काष्ठा viafb_par *viapar = info->par;
	काष्ठा viafb_shared *shared = viapar->shared;
	u32 fg_color;
	u8 rop;

	अगर (info->flags & FBINFO_HWACCEL_DISABLED || !shared->hw_bitblt) अणु
		cfb_fillrect(info, rect);
		वापस;
	पूर्ण

	अगर (!rect->width || !rect->height)
		वापस;

	अगर (info->fix.visual == FB_VISUAL_TRUECOLOR)
		fg_color = ((u32 *)info->pseuकरो_palette)[rect->color];
	अन्यथा
		fg_color = rect->color;

	अगर (rect->rop == ROP_XOR)
		rop = 0x5A;
	अन्यथा
		rop = 0xF0;

	DEBUG_MSG(KERN_DEBUG "viafb 2D engine: fillrect\n");
	अगर (shared->hw_bitblt(shared->vdev->engine_mmio, VIA_BITBLT_FILL,
		rect->width, rect->height, info->var.bits_per_pixel,
		viapar->vram_addr, info->fix.line_length, rect->dx, rect->dy,
		शून्य, 0, 0, 0, 0, fg_color, 0, rop))
		cfb_fillrect(info, rect);
पूर्ण

अटल व्योम viafb_copyarea(काष्ठा fb_info *info,
	स्थिर काष्ठा fb_copyarea *area)
अणु
	काष्ठा viafb_par *viapar = info->par;
	काष्ठा viafb_shared *shared = viapar->shared;

	अगर (info->flags & FBINFO_HWACCEL_DISABLED || !shared->hw_bitblt) अणु
		cfb_copyarea(info, area);
		वापस;
	पूर्ण

	अगर (!area->width || !area->height)
		वापस;

	DEBUG_MSG(KERN_DEBUG "viafb 2D engine: copyarea\n");
	अगर (shared->hw_bitblt(shared->vdev->engine_mmio, VIA_BITBLT_COLOR,
		area->width, area->height, info->var.bits_per_pixel,
		viapar->vram_addr, info->fix.line_length, area->dx, area->dy,
		शून्य, viapar->vram_addr, info->fix.line_length,
		area->sx, area->sy, 0, 0, 0))
		cfb_copyarea(info, area);
पूर्ण

अटल व्योम viafb_imageblit(काष्ठा fb_info *info,
	स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा viafb_par *viapar = info->par;
	काष्ठा viafb_shared *shared = viapar->shared;
	u32 fg_color = 0, bg_color = 0;
	u8 op;

	अगर (info->flags & FBINFO_HWACCEL_DISABLED || !shared->hw_bitblt ||
		(image->depth != 1 && image->depth != viapar->depth)) अणु
		cfb_imageblit(info, image);
		वापस;
	पूर्ण

	अगर (image->depth == 1) अणु
		op = VIA_BITBLT_MONO;
		अगर (info->fix.visual == FB_VISUAL_TRUECOLOR) अणु
			fg_color =
				((u32 *)info->pseuकरो_palette)[image->fg_color];
			bg_color =
				((u32 *)info->pseuकरो_palette)[image->bg_color];
		पूर्ण अन्यथा अणु
			fg_color = image->fg_color;
			bg_color = image->bg_color;
		पूर्ण
	पूर्ण अन्यथा
		op = VIA_BITBLT_COLOR;

	DEBUG_MSG(KERN_DEBUG "viafb 2D engine: imageblit\n");
	अगर (shared->hw_bitblt(shared->vdev->engine_mmio, op,
		image->width, image->height, info->var.bits_per_pixel,
		viapar->vram_addr, info->fix.line_length, image->dx, image->dy,
		(u32 *)image->data, 0, 0, 0, 0, fg_color, bg_color, 0))
		cfb_imageblit(info, image);
पूर्ण

अटल पूर्णांक viafb_cursor(काष्ठा fb_info *info, काष्ठा fb_cursor *cursor)
अणु
	काष्ठा viafb_par *viapar = info->par;
	व्योम __iomem *engine = viapar->shared->vdev->engine_mmio;
	u32 temp, xx, yy, bg_color = 0, fg_color = 0,
		chip_name = viapar->shared->chip_info.gfx_chip_name;
	पूर्णांक i, j = 0, cur_size = 64;

	अगर (info->flags & FBINFO_HWACCEL_DISABLED || info != viafbinfo)
		वापस -ENODEV;

	/* LCD ouput करोes not support hw cursors (at least on VN896) */
	अगर ((chip_name == UNICHROME_CLE266 && viapar->iga_path == IGA2) ||
		viafb_LCD_ON)
		वापस -ENODEV;

	viafb_show_hw_cursor(info, HW_Cursor_OFF);

	अगर (cursor->set & FB_CUR_SETHOT) अणु
		temp = (cursor->hot.x << 16) + cursor->hot.y;
		ग_लिखोl(temp, engine + VIA_REG_CURSOR_ORG);
	पूर्ण

	अगर (cursor->set & FB_CUR_SETPOS) अणु
		yy = cursor->image.dy - info->var.yoffset;
		xx = cursor->image.dx - info->var.xoffset;
		temp = yy & 0xFFFF;
		temp |= (xx << 16);
		ग_लिखोl(temp, engine + VIA_REG_CURSOR_POS);
	पूर्ण

	अगर (cursor->image.width <= 32 && cursor->image.height <= 32)
		cur_size = 32;
	अन्यथा अगर (cursor->image.width <= 64 && cursor->image.height <= 64)
		cur_size = 64;
	अन्यथा अणु
		prपूर्णांकk(KERN_WARNING "viafb_cursor: The cursor is too large "
			"%dx%d", cursor->image.width, cursor->image.height);
		वापस -ENXIO;
	पूर्ण

	अगर (cursor->set & FB_CUR_SETSIZE) अणु
		temp = पढ़ोl(engine + VIA_REG_CURSOR_MODE);
		अगर (cur_size == 32)
			temp |= 0x2;
		अन्यथा
			temp &= ~0x2;

		ग_लिखोl(temp, engine + VIA_REG_CURSOR_MODE);
	पूर्ण

	अगर (cursor->set & FB_CUR_SETCMAP) अणु
		fg_color = cursor->image.fg_color;
		bg_color = cursor->image.bg_color;
		अगर (chip_name == UNICHROME_CX700 ||
			chip_name == UNICHROME_VX800 ||
			chip_name == UNICHROME_VX855 ||
			chip_name == UNICHROME_VX900) अणु
			fg_color =
				((info->cmap.red[fg_color] & 0xFFC0) << 14) |
				((info->cmap.green[fg_color] & 0xFFC0) << 4) |
				((info->cmap.blue[fg_color] & 0xFFC0) >> 6);
			bg_color =
				((info->cmap.red[bg_color] & 0xFFC0) << 14) |
				((info->cmap.green[bg_color] & 0xFFC0) << 4) |
				((info->cmap.blue[bg_color] & 0xFFC0) >> 6);
		पूर्ण अन्यथा अणु
			fg_color =
				((info->cmap.red[fg_color] & 0xFF00) << 8) |
				(info->cmap.green[fg_color] & 0xFF00) |
				((info->cmap.blue[fg_color] & 0xFF00) >> 8);
			bg_color =
				((info->cmap.red[bg_color] & 0xFF00) << 8) |
				(info->cmap.green[bg_color] & 0xFF00) |
				((info->cmap.blue[bg_color] & 0xFF00) >> 8);
		पूर्ण

		ग_लिखोl(bg_color, engine + VIA_REG_CURSOR_BG);
		ग_लिखोl(fg_color, engine + VIA_REG_CURSOR_FG);
	पूर्ण

	अगर (cursor->set & FB_CUR_SETSHAPE) अणु
		काष्ठा अणु
			u8 data[CURSOR_SIZE];
			u32 bak[CURSOR_SIZE / 4];
		पूर्ण *cr_data = kzalloc(माप(*cr_data), GFP_ATOMIC);
		पूर्णांक size = ((cursor->image.width + 7) >> 3) *
			cursor->image.height;

		अगर (!cr_data)
			वापस -ENOMEM;

		अगर (cur_size == 32) अणु
			क्रम (i = 0; i < (CURSOR_SIZE / 4); i++) अणु
				cr_data->bak[i] = 0x0;
				cr_data->bak[i + 1] = 0xFFFFFFFF;
				i += 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < (CURSOR_SIZE / 4); i++) अणु
				cr_data->bak[i] = 0x0;
				cr_data->bak[i + 1] = 0x0;
				cr_data->bak[i + 2] = 0xFFFFFFFF;
				cr_data->bak[i + 3] = 0xFFFFFFFF;
				i += 3;
			पूर्ण
		पूर्ण

		चयन (cursor->rop) अणु
		हाल ROP_XOR:
			क्रम (i = 0; i < size; i++)
				cr_data->data[i] = cursor->mask[i];
			अवरोध;
		हाल ROP_COPY:

			क्रम (i = 0; i < size; i++)
				cr_data->data[i] = cursor->mask[i];
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अगर (cur_size == 32) अणु
			क्रम (i = 0; i < size; i++) अणु
				cr_data->bak[j] = (u32) cr_data->data[i];
				cr_data->bak[j + 1] = ~cr_data->bak[j];
				j += 2;
			पूर्ण
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < size; i++) अणु
				cr_data->bak[j] = (u32) cr_data->data[i];
				cr_data->bak[j + 1] = 0x0;
				cr_data->bak[j + 2] = ~cr_data->bak[j];
				cr_data->bak[j + 3] = ~cr_data->bak[j + 1];
				j += 4;
			पूर्ण
		पूर्ण

		स_नकल_toio(viafbinfo->screen_base + viapar->shared->
			cursor_vram_addr, cr_data->bak, CURSOR_SIZE);
		kमुक्त(cr_data);
	पूर्ण

	अगर (cursor->enable)
		viafb_show_hw_cursor(info, HW_Cursor_ON);

	वापस 0;
पूर्ण

अटल पूर्णांक viafb_sync(काष्ठा fb_info *info)
अणु
	अगर (!(info->flags & FBINFO_HWACCEL_DISABLED))
		viafb_रुको_engine_idle(info);
	वापस 0;
पूर्ण

अटल पूर्णांक get_primary_device(व्योम)
अणु
	पूर्णांक primary_device = 0;
	/* Rule: device on iga1 path are the primary device. */
	अगर (viafb_SAMM_ON) अणु
		अगर (viafb_CRT_ON) अणु
			अगर (viaparinfo->shared->iga1_devices & VIA_CRT) अणु
				DEBUG_MSG(KERN_INFO "CRT IGA Path:%d\n", IGA1);
				primary_device = CRT_Device;
			पूर्ण
		पूर्ण
		अगर (viafb_DVI_ON) अणु
			अगर (viaparinfo->पंचांगds_setting_info->iga_path == IGA1) अणु
				DEBUG_MSG(KERN_INFO "DVI IGA Path:%d\n",
					viaparinfo->
					पंचांगds_setting_info->iga_path);
				primary_device = DVI_Device;
			पूर्ण
		पूर्ण
		अगर (viafb_LCD_ON) अणु
			अगर (viaparinfo->lvds_setting_info->iga_path == IGA1) अणु
				DEBUG_MSG(KERN_INFO "LCD IGA Path:%d\n",
					viaparinfo->
					lvds_setting_info->iga_path);
				primary_device = LCD_Device;
			पूर्ण
		पूर्ण
		अगर (viafb_LCD2_ON) अणु
			अगर (viaparinfo->lvds_setting_info2->iga_path == IGA1) अणु
				DEBUG_MSG(KERN_INFO "LCD2 IGA Path:%d\n",
					viaparinfo->
					lvds_setting_info2->iga_path);
				primary_device = LCD2_Device;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस primary_device;
पूर्ण

अटल व्योम retrieve_device_setting(काष्ठा viafb_ioctl_setting
	*setting_info)
अणु

	/* get device status */
	अगर (viafb_CRT_ON == 1)
		setting_info->device_status = CRT_Device;
	अगर (viafb_DVI_ON == 1)
		setting_info->device_status |= DVI_Device;
	अगर (viafb_LCD_ON == 1)
		setting_info->device_status |= LCD_Device;
	अगर (viafb_LCD2_ON == 1)
		setting_info->device_status |= LCD2_Device;

	setting_info->samm_status = viafb_SAMM_ON;
	setting_info->primary_device = get_primary_device();

	setting_info->first_dev_bpp = viafb_bpp;
	setting_info->second_dev_bpp = viafb_bpp1;

	setting_info->first_dev_refresh = viafb_refresh;
	setting_info->second_dev_refresh = viafb_refresh1;

	setting_info->first_dev_hor_res = viafb_hotplug_Xres;
	setting_info->first_dev_ver_res = viafb_hotplug_Yres;
	setting_info->second_dev_hor_res = viafb_second_xres;
	setting_info->second_dev_ver_res = viafb_second_yres;

	/* Get lcd attributes */
	setting_info->lcd_attributes.display_center = viafb_lcd_dsp_method;
	setting_info->lcd_attributes.panel_id = viafb_lcd_panel_id;
	setting_info->lcd_attributes.lcd_mode = viafb_lcd_mode;
पूर्ण

अटल पूर्णांक __init parse_active_dev(व्योम)
अणु
	viafb_CRT_ON = STATE_OFF;
	viafb_DVI_ON = STATE_OFF;
	viafb_LCD_ON = STATE_OFF;
	viafb_LCD2_ON = STATE_OFF;
	/* 1. Modअगरy the active status of devices. */
	/* 2. Keep the order of devices, so we can set corresponding
	   IGA path to devices in SAMM हाल. */
	/*    Note: The previous of active_dev is primary device,
	   and the following is secondary device. */
	अगर (!viafb_active_dev) अणु
		अगर (machine_is_olpc()) अणु /* LCD only */
			viafb_LCD_ON = STATE_ON;
			viafb_SAMM_ON = STATE_OFF;
		पूर्ण अन्यथा अणु
			viafb_CRT_ON = STATE_ON;
			viafb_SAMM_ON = STATE_OFF;
		पूर्ण
	पूर्ण अन्यथा अगर (!म_भेद(viafb_active_dev, "CRT+DVI")) अणु
		/* CRT+DVI */
		viafb_CRT_ON = STATE_ON;
		viafb_DVI_ON = STATE_ON;
		viafb_primary_dev = CRT_Device;
	पूर्ण अन्यथा अगर (!म_भेद(viafb_active_dev, "DVI+CRT")) अणु
		/* DVI+CRT */
		viafb_CRT_ON = STATE_ON;
		viafb_DVI_ON = STATE_ON;
		viafb_primary_dev = DVI_Device;
	पूर्ण अन्यथा अगर (!म_भेद(viafb_active_dev, "CRT+LCD")) अणु
		/* CRT+LCD */
		viafb_CRT_ON = STATE_ON;
		viafb_LCD_ON = STATE_ON;
		viafb_primary_dev = CRT_Device;
	पूर्ण अन्यथा अगर (!म_भेद(viafb_active_dev, "LCD+CRT")) अणु
		/* LCD+CRT */
		viafb_CRT_ON = STATE_ON;
		viafb_LCD_ON = STATE_ON;
		viafb_primary_dev = LCD_Device;
	पूर्ण अन्यथा अगर (!म_भेद(viafb_active_dev, "DVI+LCD")) अणु
		/* DVI+LCD */
		viafb_DVI_ON = STATE_ON;
		viafb_LCD_ON = STATE_ON;
		viafb_primary_dev = DVI_Device;
	पूर्ण अन्यथा अगर (!म_भेद(viafb_active_dev, "LCD+DVI")) अणु
		/* LCD+DVI */
		viafb_DVI_ON = STATE_ON;
		viafb_LCD_ON = STATE_ON;
		viafb_primary_dev = LCD_Device;
	पूर्ण अन्यथा अगर (!म_भेद(viafb_active_dev, "LCD+LCD2")) अणु
		viafb_LCD_ON = STATE_ON;
		viafb_LCD2_ON = STATE_ON;
		viafb_primary_dev = LCD_Device;
	पूर्ण अन्यथा अगर (!म_भेद(viafb_active_dev, "LCD2+LCD")) अणु
		viafb_LCD_ON = STATE_ON;
		viafb_LCD2_ON = STATE_ON;
		viafb_primary_dev = LCD2_Device;
	पूर्ण अन्यथा अगर (!म_भेद(viafb_active_dev, "CRT")) अणु
		/* CRT only */
		viafb_CRT_ON = STATE_ON;
		viafb_SAMM_ON = STATE_OFF;
	पूर्ण अन्यथा अगर (!म_भेद(viafb_active_dev, "DVI")) अणु
		/* DVI only */
		viafb_DVI_ON = STATE_ON;
		viafb_SAMM_ON = STATE_OFF;
	पूर्ण अन्यथा अगर (!म_भेद(viafb_active_dev, "LCD")) अणु
		/* LCD only */
		viafb_LCD_ON = STATE_ON;
		viafb_SAMM_ON = STATE_OFF;
	पूर्ण अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक parse_port(अक्षर *opt_str, पूर्णांक *output_पूर्णांकerface)
अणु
	अगर (!म_भेदन(opt_str, "DVP0", 4))
		*output_पूर्णांकerface = INTERFACE_DVP0;
	अन्यथा अगर (!म_भेदन(opt_str, "DVP1", 4))
		*output_पूर्णांकerface = INTERFACE_DVP1;
	अन्यथा अगर (!म_भेदन(opt_str, "DFP_HIGHLOW", 11))
		*output_पूर्णांकerface = INTERFACE_DFP;
	अन्यथा अगर (!म_भेदन(opt_str, "DFP_HIGH", 8))
		*output_पूर्णांकerface = INTERFACE_DFP_HIGH;
	अन्यथा अगर (!म_भेदन(opt_str, "DFP_LOW", 7))
		*output_पूर्णांकerface = INTERFACE_DFP_LOW;
	अन्यथा
		*output_पूर्णांकerface = INTERFACE_NONE;
	वापस 0;
पूर्ण

अटल व्योम parse_lcd_port(व्योम)
अणु
	parse_port(viafb_lcd_port, &viaparinfo->chip_info->lvds_chip_info.
		output_पूर्णांकerface);
	/*Initialize to aव्योम unexpected behavior */
	viaparinfo->chip_info->lvds_chip_info2.output_पूर्णांकerface =
	INTERFACE_NONE;

	DEBUG_MSG(KERN_INFO "parse_lcd_port: viafb_lcd_port:%s,interface:%d\n",
		  viafb_lcd_port, viaparinfo->chip_info->lvds_chip_info.
		  output_पूर्णांकerface);
पूर्ण

अटल व्योम parse_dvi_port(व्योम)
अणु
	parse_port(viafb_dvi_port, &viaparinfo->chip_info->पंचांगds_chip_info.
		output_पूर्णांकerface);

	DEBUG_MSG(KERN_INFO "parse_dvi_port: viafb_dvi_port:%s,interface:%d\n",
		  viafb_dvi_port, viaparinfo->chip_info->पंचांगds_chip_info.
		  output_पूर्णांकerface);
पूर्ण

#अगर_घोषित CONFIG_FB_VIA_सूचीECT_PROCFS

/*
 * The proc fileप्रणाली पढ़ो/ग_लिखो function, a simple proc implement to
 * get/set the value of DPA  DVP0,   DVP0DataDriving,  DVP0ClockDriving, DVP1,
 * DVP1Driving, DFPHigh, DFPLow CR96,   SR2A[5], SR1B[1], SR2A[4], SR1E[2],
 * CR9B,    SR65,    CR97,    CR99
 */
अटल पूर्णांक viafb_dvp0_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	u8 dvp0_data_dri = 0, dvp0_clk_dri = 0, dvp0 = 0;
	dvp0_data_dri =
	    (viafb_पढ़ो_reg(VIASR, SR2A) & BIT5) >> 4 |
	    (viafb_पढ़ो_reg(VIASR, SR1B) & BIT1) >> 1;
	dvp0_clk_dri =
	    (viafb_पढ़ो_reg(VIASR, SR2A) & BIT4) >> 3 |
	    (viafb_पढ़ो_reg(VIASR, SR1E) & BIT2) >> 2;
	dvp0 = viafb_पढ़ो_reg(VIACR, CR96) & 0x0f;
	seq_म_लिखो(m, "%x %x %x\n", dvp0, dvp0_data_dri, dvp0_clk_dri);
	वापस 0;
पूर्ण

अटल पूर्णांक viafb_dvp0_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, viafb_dvp0_proc_show, शून्य);
पूर्ण

अटल sमाप_प्रकार viafb_dvp0_proc_ग_लिखो(काष्ठा file *file,
	स्थिर अक्षर __user *buffer, माप_प्रकार count, loff_t *pos)
अणु
	अक्षर buf[20], *value, *pbuf;
	u8 reg_val = 0;
	अचिन्हित दीर्घ length, i;
	अगर (count < 1)
		वापस -EINVAL;
	length = count > 20 ? 20 : count;
	अगर (copy_from_user(&buf[0], buffer, length))
		वापस -EFAULT;
	buf[length - 1] = '\0';	/*Ensure end string */
	pbuf = &buf[0];
	क्रम (i = 0; i < 3; i++) अणु
		value = strsep(&pbuf, " ");
		अगर (value != शून्य) अणु
			अगर (kstrtou8(value, 0, &reg_val) < 0)
				वापस -EINVAL;
			DEBUG_MSG(KERN_INFO "DVP0:reg_val[%lu]=:%x\n", i,
				  reg_val);
			चयन (i) अणु
			हाल 0:
				viafb_ग_लिखो_reg_mask(CR96, VIACR,
					reg_val, 0x0f);
				अवरोध;
			हाल 1:
				viafb_ग_लिखो_reg_mask(SR2A, VIASR,
					reg_val << 4, BIT5);
				viafb_ग_लिखो_reg_mask(SR1B, VIASR,
					reg_val << 1, BIT1);
				अवरोध;
			हाल 2:
				viafb_ग_लिखो_reg_mask(SR2A, VIASR,
					reg_val << 3, BIT4);
				viafb_ग_लिखो_reg_mask(SR1E, VIASR,
					reg_val << 2, BIT2);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण
	वापस count;
पूर्ण

अटल स्थिर काष्ठा proc_ops viafb_dvp0_proc_ops = अणु
	.proc_खोलो	= viafb_dvp0_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= viafb_dvp0_proc_ग_लिखो,
पूर्ण;

अटल पूर्णांक viafb_dvp1_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	u8 dvp1 = 0, dvp1_data_dri = 0, dvp1_clk_dri = 0;
	dvp1 = viafb_पढ़ो_reg(VIACR, CR9B) & 0x0f;
	dvp1_data_dri = (viafb_पढ़ो_reg(VIASR, SR65) & 0x0c) >> 2;
	dvp1_clk_dri = viafb_पढ़ो_reg(VIASR, SR65) & 0x03;
	seq_म_लिखो(m, "%x %x %x\n", dvp1, dvp1_data_dri, dvp1_clk_dri);
	वापस 0;
पूर्ण

अटल पूर्णांक viafb_dvp1_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, viafb_dvp1_proc_show, शून्य);
पूर्ण

अटल sमाप_प्रकार viafb_dvp1_proc_ग_लिखो(काष्ठा file *file,
	स्थिर अक्षर __user *buffer, माप_प्रकार count, loff_t *pos)
अणु
	अक्षर buf[20], *value, *pbuf;
	u8 reg_val = 0;
	अचिन्हित दीर्घ length, i;
	अगर (count < 1)
		वापस -EINVAL;
	length = count > 20 ? 20 : count;
	अगर (copy_from_user(&buf[0], buffer, length))
		वापस -EFAULT;
	buf[length - 1] = '\0';	/*Ensure end string */
	pbuf = &buf[0];
	क्रम (i = 0; i < 3; i++) अणु
		value = strsep(&pbuf, " ");
		अगर (value != शून्य) अणु
			अगर (kstrtou8(value, 0, &reg_val) < 0)
				वापस -EINVAL;
			चयन (i) अणु
			हाल 0:
				viafb_ग_लिखो_reg_mask(CR9B, VIACR,
					reg_val, 0x0f);
				अवरोध;
			हाल 1:
				viafb_ग_लिखो_reg_mask(SR65, VIASR,
					reg_val << 2, 0x0c);
				अवरोध;
			हाल 2:
				viafb_ग_लिखो_reg_mask(SR65, VIASR,
					reg_val, 0x03);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण
	वापस count;
पूर्ण

अटल स्थिर काष्ठा proc_ops viafb_dvp1_proc_ops = अणु
	.proc_खोलो	= viafb_dvp1_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= viafb_dvp1_proc_ग_लिखो,
पूर्ण;

अटल पूर्णांक viafb_dfph_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	u8 dfp_high = 0;
	dfp_high = viafb_पढ़ो_reg(VIACR, CR97) & 0x0f;
	seq_म_लिखो(m, "%x\n", dfp_high);
	वापस 0;
पूर्ण

अटल पूर्णांक viafb_dfph_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, viafb_dfph_proc_show, शून्य);
पूर्ण

अटल sमाप_प्रकार viafb_dfph_proc_ग_लिखो(काष्ठा file *file,
	स्थिर अक्षर __user *buffer, माप_प्रकार count, loff_t *pos)
अणु
	पूर्णांक err;
	u8 reg_val;
	err = kstrtou8_from_user(buffer, count, 0, &reg_val);
	अगर (err)
		वापस err;

	viafb_ग_लिखो_reg_mask(CR97, VIACR, reg_val, 0x0f);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा proc_ops viafb_dfph_proc_ops = अणु
	.proc_खोलो	= viafb_dfph_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= viafb_dfph_proc_ग_लिखो,
पूर्ण;

अटल पूर्णांक viafb_dfpl_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	u8 dfp_low = 0;
	dfp_low = viafb_पढ़ो_reg(VIACR, CR99) & 0x0f;
	seq_म_लिखो(m, "%x\n", dfp_low);
	वापस 0;
पूर्ण

अटल पूर्णांक viafb_dfpl_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, viafb_dfpl_proc_show, शून्य);
पूर्ण

अटल sमाप_प्रकार viafb_dfpl_proc_ग_लिखो(काष्ठा file *file,
	स्थिर अक्षर __user *buffer, माप_प्रकार count, loff_t *pos)
अणु
	पूर्णांक err;
	u8 reg_val;
	err = kstrtou8_from_user(buffer, count, 0, &reg_val);
	अगर (err)
		वापस err;

	viafb_ग_लिखो_reg_mask(CR99, VIACR, reg_val, 0x0f);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा proc_ops viafb_dfpl_proc_ops = अणु
	.proc_खोलो	= viafb_dfpl_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= viafb_dfpl_proc_ग_लिखो,
पूर्ण;

अटल पूर्णांक viafb_vt1636_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	u8 vt1636_08 = 0, vt1636_09 = 0;
	चयन (viaparinfo->chip_info->lvds_chip_info.lvds_chip_name) अणु
	हाल VT1636_LVDS:
		vt1636_08 =
		    viafb_gpio_i2c_पढ़ो_lvds(viaparinfo->lvds_setting_info,
		    &viaparinfo->chip_info->lvds_chip_info, 0x08) & 0x0f;
		vt1636_09 =
		    viafb_gpio_i2c_पढ़ो_lvds(viaparinfo->lvds_setting_info,
		    &viaparinfo->chip_info->lvds_chip_info, 0x09) & 0x1f;
		seq_म_लिखो(m, "%x %x\n", vt1636_08, vt1636_09);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	चयन (viaparinfo->chip_info->lvds_chip_info2.lvds_chip_name) अणु
	हाल VT1636_LVDS:
		vt1636_08 =
		    viafb_gpio_i2c_पढ़ो_lvds(viaparinfo->lvds_setting_info2,
			&viaparinfo->chip_info->lvds_chip_info2, 0x08) & 0x0f;
		vt1636_09 =
		    viafb_gpio_i2c_पढ़ो_lvds(viaparinfo->lvds_setting_info2,
			&viaparinfo->chip_info->lvds_chip_info2, 0x09) & 0x1f;
		seq_म_लिखो(m, " %x %x\n", vt1636_08, vt1636_09);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक viafb_vt1636_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, viafb_vt1636_proc_show, शून्य);
पूर्ण

अटल sमाप_प्रकार viafb_vt1636_proc_ग_लिखो(काष्ठा file *file,
	स्थिर अक्षर __user *buffer, माप_प्रकार count, loff_t *pos)
अणु
	अक्षर buf[30], *value, *pbuf;
	काष्ठा IODATA reg_val;
	अचिन्हित दीर्घ length, i;
	अगर (count < 1)
		वापस -EINVAL;
	length = count > 30 ? 30 : count;
	अगर (copy_from_user(&buf[0], buffer, length))
		वापस -EFAULT;
	buf[length - 1] = '\0';	/*Ensure end string */
	pbuf = &buf[0];
	चयन (viaparinfo->chip_info->lvds_chip_info.lvds_chip_name) अणु
	हाल VT1636_LVDS:
		क्रम (i = 0; i < 2; i++) अणु
			value = strsep(&pbuf, " ");
			अगर (value != शून्य) अणु
				अगर (kstrtou8(value, 0, &reg_val.Data) < 0)
					वापस -EINVAL;
				चयन (i) अणु
				हाल 0:
					reg_val.Index = 0x08;
					reg_val.Mask = 0x0f;
					viafb_gpio_i2c_ग_लिखो_mask_lvds
					    (viaparinfo->lvds_setting_info,
					    &viaparinfo->
					    chip_info->lvds_chip_info,
					     reg_val);
					अवरोध;
				हाल 1:
					reg_val.Index = 0x09;
					reg_val.Mask = 0x1f;
					viafb_gpio_i2c_ग_लिखो_mask_lvds
					    (viaparinfo->lvds_setting_info,
					    &viaparinfo->
					    chip_info->lvds_chip_info,
					     reg_val);
					अवरोध;
				शेष:
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	चयन (viaparinfo->chip_info->lvds_chip_info2.lvds_chip_name) अणु
	हाल VT1636_LVDS:
		क्रम (i = 0; i < 2; i++) अणु
			value = strsep(&pbuf, " ");
			अगर (value != शून्य) अणु
				अगर (kstrtou8(value, 0, &reg_val.Data) < 0)
					वापस -EINVAL;
				चयन (i) अणु
				हाल 0:
					reg_val.Index = 0x08;
					reg_val.Mask = 0x0f;
					viafb_gpio_i2c_ग_लिखो_mask_lvds
					    (viaparinfo->lvds_setting_info2,
					    &viaparinfo->
					    chip_info->lvds_chip_info2,
					     reg_val);
					अवरोध;
				हाल 1:
					reg_val.Index = 0x09;
					reg_val.Mask = 0x1f;
					viafb_gpio_i2c_ग_लिखो_mask_lvds
					    (viaparinfo->lvds_setting_info2,
					    &viaparinfo->
					    chip_info->lvds_chip_info2,
					     reg_val);
					अवरोध;
				शेष:
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस count;
पूर्ण

अटल स्थिर काष्ठा proc_ops viafb_vt1636_proc_ops = अणु
	.proc_खोलो	= viafb_vt1636_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= viafb_vt1636_proc_ग_लिखो,
पूर्ण;

#पूर्ण_अगर /* CONFIG_FB_VIA_सूचीECT_PROCFS */

अटल पूर्णांक __maybe_unused viafb_sup_odev_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	via_odev_to_seq(m, supported_odev_map[
		viaparinfo->shared->chip_info.gfx_chip_name]);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार odev_update(स्थिर अक्षर __user *buffer, माप_प्रकार count, u32 *odev)
अणु
	अक्षर buf[64], *ptr = buf;
	u32 devices;
	bool add, sub;

	अगर (count < 1 || count > 63)
		वापस -EINVAL;
	अगर (copy_from_user(&buf[0], buffer, count))
		वापस -EFAULT;
	buf[count] = '\0';
	add = buf[0] == '+';
	sub = buf[0] == '-';
	अगर (add || sub)
		ptr++;
	devices = via_parse_odev(ptr, &ptr);
	अगर (*ptr == '\n')
		ptr++;
	अगर (*ptr != 0)
		वापस -EINVAL;
	अगर (add)
		*odev |= devices;
	अन्यथा अगर (sub)
		*odev &= ~devices;
	अन्यथा
		*odev = devices;
	वापस count;
पूर्ण

अटल पूर्णांक viafb_iga1_odev_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	via_odev_to_seq(m, viaparinfo->shared->iga1_devices);
	वापस 0;
पूर्ण

अटल पूर्णांक viafb_iga1_odev_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, viafb_iga1_odev_proc_show, शून्य);
पूर्ण

अटल sमाप_प्रकार viafb_iga1_odev_proc_ग_लिखो(काष्ठा file *file,
	स्थिर अक्षर __user *buffer, माप_प्रकार count, loff_t *pos)
अणु
	u32 dev_on, dev_off, dev_old, dev_new;
	sमाप_प्रकार res;

	dev_old = dev_new = viaparinfo->shared->iga1_devices;
	res = odev_update(buffer, count, &dev_new);
	अगर (res != count)
		वापस res;
	dev_off = dev_old & ~dev_new;
	dev_on = dev_new & ~dev_old;
	viaparinfo->shared->iga1_devices = dev_new;
	viaparinfo->shared->iga2_devices &= ~dev_new;
	via_set_state(dev_off, VIA_STATE_OFF);
	via_set_source(dev_new, IGA1);
	via_set_state(dev_on, VIA_STATE_ON);
	वापस res;
पूर्ण

अटल स्थिर काष्ठा proc_ops viafb_iga1_odev_proc_ops = अणु
	.proc_खोलो	= viafb_iga1_odev_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= viafb_iga1_odev_proc_ग_लिखो,
पूर्ण;

अटल पूर्णांक viafb_iga2_odev_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	via_odev_to_seq(m, viaparinfo->shared->iga2_devices);
	वापस 0;
पूर्ण

अटल पूर्णांक viafb_iga2_odev_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, viafb_iga2_odev_proc_show, शून्य);
पूर्ण

अटल sमाप_प्रकार viafb_iga2_odev_proc_ग_लिखो(काष्ठा file *file,
	स्थिर अक्षर __user *buffer, माप_प्रकार count, loff_t *pos)
अणु
	u32 dev_on, dev_off, dev_old, dev_new;
	sमाप_प्रकार res;

	dev_old = dev_new = viaparinfo->shared->iga2_devices;
	res = odev_update(buffer, count, &dev_new);
	अगर (res != count)
		वापस res;
	dev_off = dev_old & ~dev_new;
	dev_on = dev_new & ~dev_old;
	viaparinfo->shared->iga2_devices = dev_new;
	viaparinfo->shared->iga1_devices &= ~dev_new;
	via_set_state(dev_off, VIA_STATE_OFF);
	via_set_source(dev_new, IGA2);
	via_set_state(dev_on, VIA_STATE_ON);
	वापस res;
पूर्ण

अटल स्थिर काष्ठा proc_ops viafb_iga2_odev_proc_ops = अणु
	.proc_खोलो	= viafb_iga2_odev_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= viafb_iga2_odev_proc_ग_लिखो,
पूर्ण;

#घोषणा IS_VT1636(lvds_chip)	((lvds_chip).lvds_chip_name == VT1636_LVDS)
अटल व्योम viafb_init_proc(काष्ठा viafb_shared *shared)
अणु
	काष्ठा proc_dir_entry *iga1_entry, *iga2_entry,
		*viafb_entry = proc_सूची_गढ़ो("viafb", शून्य);

	shared->proc_entry = viafb_entry;
	अगर (viafb_entry) अणु
#अगर_घोषित CONFIG_FB_VIA_सूचीECT_PROCFS
		proc_create("dvp0", 0, viafb_entry, &viafb_dvp0_proc_ops);
		proc_create("dvp1", 0, viafb_entry, &viafb_dvp1_proc_ops);
		proc_create("dfph", 0, viafb_entry, &viafb_dfph_proc_ops);
		proc_create("dfpl", 0, viafb_entry, &viafb_dfpl_proc_ops);
		अगर (IS_VT1636(shared->chip_info.lvds_chip_info)
			|| IS_VT1636(shared->chip_info.lvds_chip_info2))
			proc_create("vt1636", 0, viafb_entry,
				    &viafb_vt1636_proc_ops);
#पूर्ण_अगर /* CONFIG_FB_VIA_सूचीECT_PROCFS */

		proc_create_single("supported_output_devices", 0, viafb_entry,
			viafb_sup_odev_proc_show);
		iga1_entry = proc_सूची_गढ़ो("iga1", viafb_entry);
		shared->iga1_proc_entry = iga1_entry;
		proc_create("output_devices", 0, iga1_entry,
			    &viafb_iga1_odev_proc_ops);
		iga2_entry = proc_सूची_गढ़ो("iga2", viafb_entry);
		shared->iga2_proc_entry = iga2_entry;
		proc_create("output_devices", 0, iga2_entry,
			    &viafb_iga2_odev_proc_ops);
	पूर्ण
पूर्ण
अटल व्योम viafb_हटाओ_proc(काष्ठा viafb_shared *shared)
अणु
	काष्ठा proc_dir_entry *viafb_entry = shared->proc_entry;

	अगर (!viafb_entry)
		वापस;

	हटाओ_proc_entry("output_devices", shared->iga2_proc_entry);
	हटाओ_proc_entry("iga2", viafb_entry);
	हटाओ_proc_entry("output_devices", shared->iga1_proc_entry);
	हटाओ_proc_entry("iga1", viafb_entry);
	हटाओ_proc_entry("supported_output_devices", viafb_entry);

#अगर_घोषित CONFIG_FB_VIA_सूचीECT_PROCFS
	हटाओ_proc_entry("dvp0", viafb_entry);/* parent dir */
	हटाओ_proc_entry("dvp1", viafb_entry);
	हटाओ_proc_entry("dfph", viafb_entry);
	हटाओ_proc_entry("dfpl", viafb_entry);
	अगर (IS_VT1636(shared->chip_info.lvds_chip_info)
		|| IS_VT1636(shared->chip_info.lvds_chip_info2))
		हटाओ_proc_entry("vt1636", viafb_entry);
#पूर्ण_अगर /* CONFIG_FB_VIA_सूचीECT_PROCFS */

	हटाओ_proc_entry("viafb", शून्य);
पूर्ण
#अघोषित IS_VT1636

अटल पूर्णांक parse_mode(स्थिर अक्षर *str, u32 devices, u32 *xres, u32 *yres)
अणु
	स्थिर काष्ठा fb_videomode *mode = शून्य;
	अक्षर *ptr;

	अगर (!str) अणु
		अगर (devices == VIA_CRT)
			mode = via_aux_get_preferred_mode(
				viaparinfo->shared->i2c_26);
		अन्यथा अगर (devices == VIA_DVP1)
			mode = via_aux_get_preferred_mode(
				viaparinfo->shared->i2c_31);

		अगर (mode) अणु
			*xres = mode->xres;
			*yres = mode->yres;
		पूर्ण अन्यथा अगर (machine_is_olpc()) अणु
			*xres = 1200;
			*yres = 900;
		पूर्ण अन्यथा अणु
			*xres = 640;
			*yres = 480;
		पूर्ण
		वापस 0;
	पूर्ण

	*xres = simple_म_से_अदीर्घ(str, &ptr, 10);
	अगर (ptr[0] != 'x')
		वापस -EINVAL;

	*yres = simple_म_से_अदीर्घ(&ptr[1], &ptr, 10);
	अगर (ptr[0])
		वापस -EINVAL;

	वापस 0;
पूर्ण


#अगर_घोषित CONFIG_PM
अटल पूर्णांक viafb_suspend(व्योम *unused)
अणु
	console_lock();
	fb_set_suspend(viafbinfo, 1);
	viafb_sync(viafbinfo);
	console_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक viafb_resume(व्योम *unused)
अणु
	console_lock();
	अगर (viaparinfo->shared->vdev->engine_mmio)
		viafb_reset_engine(viaparinfo);
	viafb_set_par(viafbinfo);
	अगर (viafb_dual_fb)
		viafb_set_par(viafbinfo1);
	fb_set_suspend(viafbinfo, 0);

	console_unlock();
	वापस 0;
पूर्ण

अटल काष्ठा viafb_pm_hooks viafb_fb_pm_hooks = अणु
	.suspend = viafb_suspend,
	.resume = viafb_resume
पूर्ण;

#पूर्ण_अगर

अटल व्योम i2c_bus_probe(काष्ठा viafb_shared *shared)
अणु
	/* should be always CRT */
	prपूर्णांकk(KERN_INFO "viafb: Probing I2C bus 0x26\n");
	shared->i2c_26 = via_aux_probe(viafb_find_i2c_adapter(VIA_PORT_26));

	/* seems to be usually DVP1 */
	prपूर्णांकk(KERN_INFO "viafb: Probing I2C bus 0x31\n");
	shared->i2c_31 = via_aux_probe(viafb_find_i2c_adapter(VIA_PORT_31));

	/* FIXME: what is this? */
	अगर (!machine_is_olpc()) अणु
		prपूर्णांकk(KERN_INFO "viafb: Probing I2C bus 0x2C\n");
		shared->i2c_2C = via_aux_probe(viafb_find_i2c_adapter(VIA_PORT_2C));
	पूर्ण

	prपूर्णांकk(KERN_INFO "viafb: Finished I2C bus probing");
पूर्ण

अटल व्योम i2c_bus_मुक्त(काष्ठा viafb_shared *shared)
अणु
	via_aux_मुक्त(shared->i2c_26);
	via_aux_मुक्त(shared->i2c_31);
	via_aux_मुक्त(shared->i2c_2C);
पूर्ण

पूर्णांक via_fb_pci_probe(काष्ठा viafb_dev *vdev)
अणु
	u32 शेष_xres, शेष_yres;
	काष्ठा fb_var_screeninfo शेष_var;
	पूर्णांक rc;
	u32 viafb_par_length;

	DEBUG_MSG(KERN_INFO "VIAFB PCI Probe!!\n");
	स_रखो(&शेष_var, 0, माप(शेष_var));
	viafb_par_length = ALIGN(माप(काष्ठा viafb_par), BITS_PER_LONG/8);

	/* Allocate fb_info and ***_par here, also including some other needed
	 * variables
	*/
	viafbinfo = framebuffer_alloc(viafb_par_length +
		ALIGN(माप(काष्ठा viafb_shared), BITS_PER_LONG/8),
		&vdev->pdev->dev);
	अगर (!viafbinfo)
		वापस -ENOMEM;

	viaparinfo = (काष्ठा viafb_par *)viafbinfo->par;
	viaparinfo->shared = viafbinfo->par + viafb_par_length;
	viaparinfo->shared->vdev = vdev;
	viaparinfo->vram_addr = 0;
	viaparinfo->पंचांगds_setting_info = &viaparinfo->shared->पंचांगds_setting_info;
	viaparinfo->lvds_setting_info = &viaparinfo->shared->lvds_setting_info;
	viaparinfo->lvds_setting_info2 =
		&viaparinfo->shared->lvds_setting_info2;
	viaparinfo->chip_info = &viaparinfo->shared->chip_info;

	i2c_bus_probe(viaparinfo->shared);
	अगर (viafb_dual_fb)
		viafb_SAMM_ON = 1;
	parse_lcd_port();
	parse_dvi_port();

	viafb_init_chip_info(vdev->chip_type);
	/*
	 * The framebuffer will have been successfully mapped by
	 * the core (or we'd not be here), but we still need to
	 * set up our own accounting.
	 */
	viaparinfo->fbmem = vdev->fbmem_start;
	viaparinfo->memsize = vdev->fbmem_len;
	viaparinfo->fbmem_मुक्त = viaparinfo->memsize;
	viaparinfo->fbmem_used = 0;
	viafbinfo->screen_base = vdev->fbmem;

	viafbinfo->fix.mmio_start = vdev->engine_start;
	viafbinfo->fix.mmio_len = vdev->engine_len;
	viafbinfo->node = 0;
	viafbinfo->fbops = &viafb_ops;
	viafbinfo->flags = FBINFO_DEFAULT | FBINFO_HWACCEL_YPAN;

	viafbinfo->pseuकरो_palette = pseuकरो_pal;
	अगर (viafb_accel && !viafb_setup_engine(viafbinfo)) अणु
		viafbinfo->flags |= FBINFO_HWACCEL_COPYAREA |
			FBINFO_HWACCEL_FILLRECT |  FBINFO_HWACCEL_IMAGEBLIT;
		शेष_var.accel_flags = FB_ACCELF_TEXT;
	पूर्ण अन्यथा अणु
		viafbinfo->flags |= FBINFO_HWACCEL_DISABLED;
		शेष_var.accel_flags = 0;
	पूर्ण

	अगर (viafb_second_size && (viafb_second_size < 8)) अणु
		viafb_second_offset = viaparinfo->fbmem_मुक्त -
			viafb_second_size * 1024 * 1024;
	पूर्ण अन्यथा अणु
		viafb_second_size = 8;
		viafb_second_offset = viaparinfo->fbmem_मुक्त -
			viafb_second_size * 1024 * 1024;
	पूर्ण

	parse_mode(viafb_mode, viaparinfo->shared->iga1_devices,
		&शेष_xres, &शेष_yres);
	अगर (viafb_SAMM_ON == 1)
		parse_mode(viafb_mode1, viaparinfo->shared->iga2_devices,
			&viafb_second_xres, &viafb_second_yres);

	शेष_var.xres = शेष_xres;
	शेष_var.yres = शेष_yres;
	शेष_var.xres_भव = शेष_xres;
	शेष_var.yres_भव = शेष_yres;
	शेष_var.bits_per_pixel = viafb_bpp;
	viafb_fill_var_timing_info(&शेष_var, viafb_get_best_mode(
		शेष_var.xres, शेष_var.yres, viafb_refresh));
	viafb_setup_fixinfo(&viafbinfo->fix, viaparinfo);
	viafbinfo->var = शेष_var;

	अगर (viafb_dual_fb) अणु
		viafbinfo1 = framebuffer_alloc(viafb_par_length,
				&vdev->pdev->dev);
		अगर (!viafbinfo1) अणु
			rc = -ENOMEM;
			जाओ out_fb_release;
		पूर्ण
		viaparinfo1 = viafbinfo1->par;
		स_नकल(viaparinfo1, viaparinfo, viafb_par_length);
		viaparinfo1->vram_addr = viafb_second_offset;
		viaparinfo1->memsize = viaparinfo->memsize -
			viafb_second_offset;
		viaparinfo->memsize = viafb_second_offset;
		viaparinfo1->fbmem = viaparinfo->fbmem + viafb_second_offset;

		viaparinfo1->fbmem_used = viaparinfo->fbmem_used;
		viaparinfo1->fbmem_मुक्त = viaparinfo1->memsize -
			viaparinfo1->fbmem_used;
		viaparinfo->fbmem_मुक्त = viaparinfo->memsize;
		viaparinfo->fbmem_used = 0;

		viaparinfo->iga_path = IGA1;
		viaparinfo1->iga_path = IGA2;
		स_नकल(viafbinfo1, viafbinfo, माप(काष्ठा fb_info));
		viafbinfo1->par = viaparinfo1;
		viafbinfo1->screen_base = viafbinfo->screen_base +
			viafb_second_offset;

		शेष_var.xres = viafb_second_xres;
		शेष_var.yres = viafb_second_yres;
		शेष_var.xres_भव = viafb_second_xres;
		शेष_var.yres_भव = viafb_second_yres;
		शेष_var.bits_per_pixel = viafb_bpp1;
		viafb_fill_var_timing_info(&शेष_var, viafb_get_best_mode(
			शेष_var.xres, शेष_var.yres, viafb_refresh1));

		viafb_setup_fixinfo(&viafbinfo1->fix, viaparinfo1);
		viafb_check_var(&शेष_var, viafbinfo1);
		viafbinfo1->var = शेष_var;
		viafb_update_fix(viafbinfo1);
		viaparinfo1->depth = fb_get_color_depth(&viafbinfo1->var,
			&viafbinfo1->fix);
	पूर्ण

	viafb_check_var(&viafbinfo->var, viafbinfo);
	viafb_update_fix(viafbinfo);
	viaparinfo->depth = fb_get_color_depth(&viafbinfo->var,
		&viafbinfo->fix);
	शेष_var.activate = FB_ACTIVATE_NOW;
	rc = fb_alloc_cmap(&viafbinfo->cmap, 256, 0);
	अगर (rc)
		जाओ out_fb1_release;

	अगर (viafb_dual_fb && (viafb_primary_dev == LCD_Device)
	    && (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CLE266)) अणु
		rc = रेजिस्टर_framebuffer(viafbinfo1);
		अगर (rc)
			जाओ out_dealloc_cmap;
	पूर्ण
	rc = रेजिस्टर_framebuffer(viafbinfo);
	अगर (rc)
		जाओ out_fb1_unreg_lcd_cle266;

	अगर (viafb_dual_fb && ((viafb_primary_dev != LCD_Device)
			|| (viaparinfo->chip_info->gfx_chip_name !=
			UNICHROME_CLE266))) अणु
		rc = रेजिस्टर_framebuffer(viafbinfo1);
		अगर (rc)
			जाओ out_fb_unreg;
	पूर्ण
	DEBUG_MSG(KERN_INFO "fb%d: %s frame buffer device %dx%d-%dbpp\n",
		  viafbinfo->node, viafbinfo->fix.id, शेष_var.xres,
		  शेष_var.yres, शेष_var.bits_per_pixel);

	viafb_init_proc(viaparinfo->shared);
	viafb_init_dac(IGA2);

#अगर_घोषित CONFIG_PM
	viafb_pm_रेजिस्टर(&viafb_fb_pm_hooks);
#पूर्ण_अगर
	वापस 0;

out_fb_unreg:
	unरेजिस्टर_framebuffer(viafbinfo);
out_fb1_unreg_lcd_cle266:
	अगर (viafb_dual_fb && (viafb_primary_dev == LCD_Device)
	    && (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CLE266))
		unरेजिस्टर_framebuffer(viafbinfo1);
out_dealloc_cmap:
	fb_dealloc_cmap(&viafbinfo->cmap);
out_fb1_release:
	framebuffer_release(viafbinfo1);
out_fb_release:
	i2c_bus_मुक्त(viaparinfo->shared);
	framebuffer_release(viafbinfo);
	वापस rc;
पूर्ण

व्योम via_fb_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	DEBUG_MSG(KERN_INFO "via_pci_remove!\n");
	fb_dealloc_cmap(&viafbinfo->cmap);
	unरेजिस्टर_framebuffer(viafbinfo);
	अगर (viafb_dual_fb)
		unरेजिस्टर_framebuffer(viafbinfo1);
	viafb_हटाओ_proc(viaparinfo->shared);
	i2c_bus_मुक्त(viaparinfo->shared);
	framebuffer_release(viafbinfo);
	अगर (viafb_dual_fb)
		framebuffer_release(viafbinfo1);
पूर्ण

#अगर_अघोषित MODULE
अटल पूर्णांक __init viafb_setup(व्योम)
अणु
	अक्षर *this_opt;
	अक्षर *options;

	DEBUG_MSG(KERN_INFO "viafb_setup!\n");

	अगर (fb_get_options("viafb", &options))
		वापस -ENODEV;

	अगर (!options || !*options)
		वापस 0;

	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!*this_opt)
			जारी;

		अगर (!म_भेदन(this_opt, "viafb_mode1=", 12)) अणु
			viafb_mode1 = kstrdup(this_opt + 12, GFP_KERNEL);
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "viafb_mode=", 11)) अणु
			viafb_mode = kstrdup(this_opt + 11, GFP_KERNEL);
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "viafb_bpp1=", 11)) अणु
			अगर (kstrtouपूर्णांक(this_opt + 11, 0, &viafb_bpp1) < 0)
				वापस -EINVAL;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "viafb_bpp=", 10)) अणु
			अगर (kstrtouपूर्णांक(this_opt + 10, 0, &viafb_bpp) < 0)
				वापस -EINVAL;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "viafb_refresh1=", 15)) अणु
			अगर (kstrtoपूर्णांक(this_opt + 15, 0, &viafb_refresh1) < 0)
				वापस -EINVAL;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "viafb_refresh=", 14)) अणु
			अगर (kstrtoपूर्णांक(this_opt + 14, 0, &viafb_refresh) < 0)
				वापस -EINVAL;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "viafb_lcd_dsp_method=", 21)) अणु
			अगर (kstrtoपूर्णांक(this_opt + 21, 0,
				      &viafb_lcd_dsp_method) < 0)
				वापस -EINVAL;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "viafb_lcd_panel_id=", 19)) अणु
			अगर (kstrtoपूर्णांक(this_opt + 19, 0,
				      &viafb_lcd_panel_id) < 0)
				वापस -EINVAL;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "viafb_accel=", 12)) अणु
			अगर (kstrtoपूर्णांक(this_opt + 12, 0, &viafb_accel) < 0)
				वापस -EINVAL;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "viafb_SAMM_ON=", 14)) अणु
			अगर (kstrtoपूर्णांक(this_opt + 14, 0, &viafb_SAMM_ON) < 0)
				वापस -EINVAL;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "viafb_active_dev=", 17)) अणु
			viafb_active_dev = kstrdup(this_opt + 17, GFP_KERNEL);
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt,
			"viafb_display_hardware_layout=", 30)) अणु
			अगर (kstrtoपूर्णांक(this_opt + 30, 0,
				      &viafb_display_hardware_layout) < 0)
				वापस -EINVAL;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "viafb_second_size=", 18)) अणु
			अगर (kstrtoपूर्णांक(this_opt + 18, 0, &viafb_second_size) < 0)
				वापस -EINVAL;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt,
			"viafb_platform_epia_dvi=", 24)) अणु
			अगर (kstrtoपूर्णांक(this_opt + 24, 0,
				      &viafb_platक्रमm_epia_dvi) < 0)
				वापस -EINVAL;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt,
			"viafb_device_lcd_dualedge=", 26)) अणु
			अगर (kstrtoपूर्णांक(this_opt + 26, 0,
				      &viafb_device_lcd_dualedge) < 0)
				वापस -EINVAL;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "viafb_bus_width=", 16)) अणु
			अगर (kstrtoपूर्णांक(this_opt + 16, 0, &viafb_bus_width) < 0)
				वापस -EINVAL;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "viafb_lcd_mode=", 15)) अणु
			अगर (kstrtoपूर्णांक(this_opt + 15, 0, &viafb_lcd_mode) < 0)
				वापस -EINVAL;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "viafb_lcd_port=", 15)) अणु
			viafb_lcd_port = kstrdup(this_opt + 15, GFP_KERNEL);
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "viafb_dvi_port=", 15)) अणु
			viafb_dvi_port = kstrdup(this_opt + 15, GFP_KERNEL);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * These are called out of via-core क्रम now.
 */
पूर्णांक __init viafb_init(व्योम)
अणु
	u32 dummy_x, dummy_y;
	पूर्णांक r = 0;

	अगर (machine_is_olpc())
		/* Apply XO-1.5-specअगरic configuration. */
		viafb_lcd_panel_id = 23;

#अगर_अघोषित MODULE
	r = viafb_setup();
	अगर (r < 0)
		वापस r;
#पूर्ण_अगर
	अगर (parse_mode(viafb_mode, 0, &dummy_x, &dummy_y)
		|| !viafb_get_best_mode(dummy_x, dummy_y, viafb_refresh)
		|| parse_mode(viafb_mode1, 0, &dummy_x, &dummy_y)
		|| !viafb_get_best_mode(dummy_x, dummy_y, viafb_refresh1)
		|| viafb_bpp < 0 || viafb_bpp > 32
		|| viafb_bpp1 < 0 || viafb_bpp1 > 32
		|| parse_active_dev())
		वापस -EINVAL;

	prपूर्णांकk(KERN_INFO
       "VIA Graphics Integration Chipset framebuffer %d.%d initializing\n",
	       VERSION_MAJOR, VERSION_MINOR);
	वापस r;
पूर्ण

व्योम __निकास viafb_निकास(व्योम)
अणु
	DEBUG_MSG(KERN_INFO "viafb_exit!\n");
पूर्ण

अटल काष्ठा fb_ops viafb_ops = अणु
	.owner = THIS_MODULE,
	.fb_खोलो = viafb_खोलो,
	.fb_release = viafb_release,
	.fb_check_var = viafb_check_var,
	.fb_set_par = viafb_set_par,
	.fb_setcolreg = viafb_setcolreg,
	.fb_pan_display = viafb_pan_display,
	.fb_blank = viafb_blank,
	.fb_fillrect = viafb_fillrect,
	.fb_copyarea = viafb_copyarea,
	.fb_imageblit = viafb_imageblit,
	.fb_cursor = viafb_cursor,
	.fb_ioctl = viafb_ioctl,
	.fb_sync = viafb_sync,
पूर्ण;


#अगर_घोषित MODULE
module_param(viafb_mode, अक्षरp, S_IRUSR);
MODULE_PARM_DESC(viafb_mode, "Set resolution (default=640x480)");

module_param(viafb_mode1, अक्षरp, S_IRUSR);
MODULE_PARM_DESC(viafb_mode1, "Set resolution (default=640x480)");

module_param(viafb_bpp, पूर्णांक, S_IRUSR);
MODULE_PARM_DESC(viafb_bpp, "Set color depth (default=32bpp)");

module_param(viafb_bpp1, पूर्णांक, S_IRUSR);
MODULE_PARM_DESC(viafb_bpp1, "Set color depth (default=32bpp)");

module_param(viafb_refresh, पूर्णांक, S_IRUSR);
MODULE_PARM_DESC(viafb_refresh,
	"Set CRT viafb_refresh rate (default = 60)");

module_param(viafb_refresh1, पूर्णांक, S_IRUSR);
MODULE_PARM_DESC(viafb_refresh1,
	"Set CRT refresh rate (default = 60)");

module_param(viafb_lcd_panel_id, पूर्णांक, S_IRUSR);
MODULE_PARM_DESC(viafb_lcd_panel_id,
	"Set Flat Panel type(Default=1024x768)");

module_param(viafb_lcd_dsp_method, पूर्णांक, S_IRUSR);
MODULE_PARM_DESC(viafb_lcd_dsp_method,
	"Set Flat Panel display scaling method.(Default=Expansion)");

module_param(viafb_SAMM_ON, पूर्णांक, S_IRUSR);
MODULE_PARM_DESC(viafb_SAMM_ON,
	"Turn on/off flag of SAMM(Default=OFF)");

module_param(viafb_accel, पूर्णांक, S_IRUSR);
MODULE_PARM_DESC(viafb_accel,
	"Set 2D Hardware Acceleration: 0 = OFF, 1 = ON (default)");

module_param(viafb_active_dev, अक्षरp, S_IRUSR);
MODULE_PARM_DESC(viafb_active_dev, "Specify active devices.");

module_param(viafb_display_hardware_layout, पूर्णांक, S_IRUSR);
MODULE_PARM_DESC(viafb_display_hardware_layout,
	"Display Hardware Layout (LCD Only, DVI Only...,etc)");

module_param(viafb_second_size, पूर्णांक, S_IRUSR);
MODULE_PARM_DESC(viafb_second_size,
	"Set secondary device memory size");

module_param(viafb_dual_fb, पूर्णांक, S_IRUSR);
MODULE_PARM_DESC(viafb_dual_fb,
	"Turn on/off flag of dual framebuffer devices.(Default = OFF)");

module_param(viafb_platक्रमm_epia_dvi, पूर्णांक, S_IRUSR);
MODULE_PARM_DESC(viafb_platक्रमm_epia_dvi,
	"Turn on/off flag of DVI devices on EPIA board.(Default = OFF)");

module_param(viafb_device_lcd_dualedge, पूर्णांक, S_IRUSR);
MODULE_PARM_DESC(viafb_device_lcd_dualedge,
	"Turn on/off flag of dual edge panel.(Default = OFF)");

module_param(viafb_bus_width, पूर्णांक, S_IRUSR);
MODULE_PARM_DESC(viafb_bus_width,
	"Set bus width of panel.(Default = 12)");

module_param(viafb_lcd_mode, पूर्णांक, S_IRUSR);
MODULE_PARM_DESC(viafb_lcd_mode,
	"Set Flat Panel mode(Default=OPENLDI)");

module_param(viafb_lcd_port, अक्षरp, S_IRUSR);
MODULE_PARM_DESC(viafb_lcd_port, "Specify LCD output port.");

module_param(viafb_dvi_port, अक्षरp, S_IRUSR);
MODULE_PARM_DESC(viafb_dvi_port, "Specify DVI output port.");

MODULE_LICENSE("GPL");
#पूर्ण_अगर
