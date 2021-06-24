<शैली गुरु>
/*
 * पूर्णांकelfb
 *
 * Linux framebuffer driver क्रम Intel(R) 865G पूर्णांकegrated graphics chips.
 *
 * Copyright तऊ 2002, 2003 David Dawes <dawes@xमुक्त86.org>
 *                   2004 Sylvain Meyer
 *
 * This driver consists of two parts.  The first part (पूर्णांकelfbdrv.c) provides
 * the basic fbdev पूर्णांकerfaces, is derived in part from the radeonfb and
 * vesafb drivers, and is covered by the GPL.  The second part (पूर्णांकelfbhw.c)
 * provides the code to program the hardware.  Most of it is derived from
 * the i810/i830 XFree86 driver.  The HW-specअगरic code is covered here
 * under a dual license (GPL and MIT/XFree86 license).
 *
 * Author: David Dawes
 *
 */

/* $DHD: पूर्णांकelfb/पूर्णांकelfbhw.c,v 1.9 2003/06/27 15:06:25 dawes Exp $ */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/पन.स>

#समावेश "intelfb.h"
#समावेश "intelfbhw.h"

काष्ठा pll_min_max अणु
	पूर्णांक min_m, max_m, min_m1, max_m1;
	पूर्णांक min_m2, max_m2, min_n, max_n;
	पूर्णांक min_p, max_p, min_p1, max_p1;
	पूर्णांक min_vco, max_vco, p_transition_clk, ref_clk;
	पूर्णांक p_inc_lo, p_inc_hi;
पूर्ण;

#घोषणा PLLS_I8xx 0
#घोषणा PLLS_I9xx 1
#घोषणा PLLS_MAX 2

अटल काष्ठा pll_min_max plls[PLLS_MAX] = अणु
	अणु 108, 140, 18, 26,
	  6, 16, 3, 16,
	  4, 128, 0, 31,
	  930000, 1400000, 165000, 48000,
	  4, 2 पूर्ण,		/* I8xx */

	अणु 75, 120, 10, 20,
	  5, 9, 4, 7,
	  5, 80, 1, 8,
	  1400000, 2800000, 200000, 96000,
	  10, 5 पूर्ण		/* I9xx */
पूर्ण;

पूर्णांक पूर्णांकelfbhw_get_chipset(काष्ठा pci_dev *pdev, काष्ठा पूर्णांकelfb_info *dinfo)
अणु
	u32 पंचांगp;
	अगर (!pdev || !dinfo)
		वापस 1;

	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_INTEL_830M:
		dinfo->name = "Intel(R) 830M";
		dinfo->chipset = INTEL_830M;
		dinfo->mobile = 1;
		dinfo->pll_index = PLLS_I8xx;
		वापस 0;
	हाल PCI_DEVICE_ID_INTEL_845G:
		dinfo->name = "Intel(R) 845G";
		dinfo->chipset = INTEL_845G;
		dinfo->mobile = 0;
		dinfo->pll_index = PLLS_I8xx;
		वापस 0;
	हाल PCI_DEVICE_ID_INTEL_854:
		dinfo->mobile = 1;
		dinfo->name = "Intel(R) 854";
		dinfo->chipset = INTEL_854;
		वापस 0;
	हाल PCI_DEVICE_ID_INTEL_85XGM:
		पंचांगp = 0;
		dinfo->mobile = 1;
		dinfo->pll_index = PLLS_I8xx;
		pci_पढ़ो_config_dword(pdev, INTEL_85X_CAPID, &पंचांगp);
		चयन ((पंचांगp >> INTEL_85X_VARIANT_SHIFT) &
			INTEL_85X_VARIANT_MASK) अणु
		हाल INTEL_VAR_855GME:
			dinfo->name = "Intel(R) 855GME";
			dinfo->chipset = INTEL_855GME;
			वापस 0;
		हाल INTEL_VAR_855GM:
			dinfo->name = "Intel(R) 855GM";
			dinfo->chipset = INTEL_855GM;
			वापस 0;
		हाल INTEL_VAR_852GME:
			dinfo->name = "Intel(R) 852GME";
			dinfo->chipset = INTEL_852GME;
			वापस 0;
		हाल INTEL_VAR_852GM:
			dinfo->name = "Intel(R) 852GM";
			dinfo->chipset = INTEL_852GM;
			वापस 0;
		शेष:
			dinfo->name = "Intel(R) 852GM/855GM";
			dinfo->chipset = INTEL_85XGM;
			वापस 0;
		पूर्ण
		अवरोध;
	हाल PCI_DEVICE_ID_INTEL_865G:
		dinfo->name = "Intel(R) 865G";
		dinfo->chipset = INTEL_865G;
		dinfo->mobile = 0;
		dinfo->pll_index = PLLS_I8xx;
		वापस 0;
	हाल PCI_DEVICE_ID_INTEL_915G:
		dinfo->name = "Intel(R) 915G";
		dinfo->chipset = INTEL_915G;
		dinfo->mobile = 0;
		dinfo->pll_index = PLLS_I9xx;
		वापस 0;
	हाल PCI_DEVICE_ID_INTEL_915GM:
		dinfo->name = "Intel(R) 915GM";
		dinfo->chipset = INTEL_915GM;
		dinfo->mobile = 1;
		dinfo->pll_index = PLLS_I9xx;
		वापस 0;
	हाल PCI_DEVICE_ID_INTEL_945G:
		dinfo->name = "Intel(R) 945G";
		dinfo->chipset = INTEL_945G;
		dinfo->mobile = 0;
		dinfo->pll_index = PLLS_I9xx;
		वापस 0;
	हाल PCI_DEVICE_ID_INTEL_945GM:
		dinfo->name = "Intel(R) 945GM";
		dinfo->chipset = INTEL_945GM;
		dinfo->mobile = 1;
		dinfo->pll_index = PLLS_I9xx;
		वापस 0;
	हाल PCI_DEVICE_ID_INTEL_945GME:
		dinfo->name = "Intel(R) 945GME";
		dinfo->chipset = INTEL_945GME;
		dinfo->mobile = 1;
		dinfo->pll_index = PLLS_I9xx;
		वापस 0;
	हाल PCI_DEVICE_ID_INTEL_965G:
		dinfo->name = "Intel(R) 965G";
		dinfo->chipset = INTEL_965G;
		dinfo->mobile = 0;
		dinfo->pll_index = PLLS_I9xx;
		वापस 0;
	हाल PCI_DEVICE_ID_INTEL_965GM:
		dinfo->name = "Intel(R) 965GM";
		dinfo->chipset = INTEL_965GM;
		dinfo->mobile = 1;
		dinfo->pll_index = PLLS_I9xx;
		वापस 0;
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

पूर्णांक पूर्णांकelfbhw_get_memory(काष्ठा pci_dev *pdev, पूर्णांक *aperture_size,
			 पूर्णांक *stolen_size)
अणु
	काष्ठा pci_dev *bridge_dev;
	u16 पंचांगp;
	पूर्णांक stolen_overhead;

	अगर (!pdev || !aperture_size || !stolen_size)
		वापस 1;

	/* Find the bridge device.  It is always 0:0.0 */
	bridge_dev = pci_get_करोमुख्य_bus_and_slot(pci_करोमुख्य_nr(pdev->bus), 0,
						 PCI_DEVFN(0, 0));
	अगर (!bridge_dev) अणु
		ERR_MSG("cannot find bridge device\n");
		वापस 1;
	पूर्ण

	/* Get the fb aperture size and "stolen" memory amount. */
	पंचांगp = 0;
	pci_पढ़ो_config_word(bridge_dev, INTEL_GMCH_CTRL, &पंचांगp);
	pci_dev_put(bridge_dev);

	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_INTEL_915G:
	हाल PCI_DEVICE_ID_INTEL_915GM:
	हाल PCI_DEVICE_ID_INTEL_945G:
	हाल PCI_DEVICE_ID_INTEL_945GM:
	हाल PCI_DEVICE_ID_INTEL_945GME:
	हाल PCI_DEVICE_ID_INTEL_965G:
	हाल PCI_DEVICE_ID_INTEL_965GM:
		/* 915, 945 and 965 chipsets support a 256MB aperture.
		   Aperture size is determined by inspected the
		   base address of the aperture. */
		अगर (pci_resource_start(pdev, 2) & 0x08000000)
			*aperture_size = MB(128);
		अन्यथा
			*aperture_size = MB(256);
		अवरोध;
	शेष:
		अगर ((पंचांगp & INTEL_GMCH_MEM_MASK) == INTEL_GMCH_MEM_64M)
			*aperture_size = MB(64);
		अन्यथा
			*aperture_size = MB(128);
		अवरोध;
	पूर्ण

	/* Stolen memory size is reduced by the GTT and the popup.
	   GTT is 1K per MB of aperture size, and popup is 4K. */
	stolen_overhead = (*aperture_size / MB(1)) + 4;
	चयन(pdev->device) अणु
	हाल PCI_DEVICE_ID_INTEL_830M:
	हाल PCI_DEVICE_ID_INTEL_845G:
		चयन (पंचांगp & INTEL_830_GMCH_GMS_MASK) अणु
		हाल INTEL_830_GMCH_GMS_STOLEN_512:
			*stolen_size = KB(512) - KB(stolen_overhead);
			वापस 0;
		हाल INTEL_830_GMCH_GMS_STOLEN_1024:
			*stolen_size = MB(1) - KB(stolen_overhead);
			वापस 0;
		हाल INTEL_830_GMCH_GMS_STOLEN_8192:
			*stolen_size = MB(8) - KB(stolen_overhead);
			वापस 0;
		हाल INTEL_830_GMCH_GMS_LOCAL:
			ERR_MSG("only local memory found\n");
			वापस 1;
		हाल INTEL_830_GMCH_GMS_DISABLED:
			ERR_MSG("video memory is disabled\n");
			वापस 1;
		शेष:
			ERR_MSG("unexpected GMCH_GMS value: 0x%02x\n",
				पंचांगp & INTEL_830_GMCH_GMS_MASK);
			वापस 1;
		पूर्ण
		अवरोध;
	शेष:
		चयन (पंचांगp & INTEL_855_GMCH_GMS_MASK) अणु
		हाल INTEL_855_GMCH_GMS_STOLEN_1M:
			*stolen_size = MB(1) - KB(stolen_overhead);
			वापस 0;
		हाल INTEL_855_GMCH_GMS_STOLEN_4M:
			*stolen_size = MB(4) - KB(stolen_overhead);
			वापस 0;
		हाल INTEL_855_GMCH_GMS_STOLEN_8M:
			*stolen_size = MB(8) - KB(stolen_overhead);
			वापस 0;
		हाल INTEL_855_GMCH_GMS_STOLEN_16M:
			*stolen_size = MB(16) - KB(stolen_overhead);
			वापस 0;
		हाल INTEL_855_GMCH_GMS_STOLEN_32M:
			*stolen_size = MB(32) - KB(stolen_overhead);
			वापस 0;
		हाल INTEL_915G_GMCH_GMS_STOLEN_48M:
			*stolen_size = MB(48) - KB(stolen_overhead);
			वापस 0;
		हाल INTEL_915G_GMCH_GMS_STOLEN_64M:
			*stolen_size = MB(64) - KB(stolen_overhead);
			वापस 0;
		हाल INTEL_855_GMCH_GMS_DISABLED:
			ERR_MSG("video memory is disabled\n");
			वापस 0;
		शेष:
			ERR_MSG("unexpected GMCH_GMS value: 0x%02x\n",
				पंचांगp & INTEL_855_GMCH_GMS_MASK);
			वापस 1;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक पूर्णांकelfbhw_check_non_crt(काष्ठा पूर्णांकelfb_info *dinfo)
अणु
	पूर्णांक dvo = 0;

	अगर (INREG(LVDS) & PORT_ENABLE)
		dvo |= LVDS_PORT;
	अगर (INREG(DVOA) & PORT_ENABLE)
		dvo |= DVOA_PORT;
	अगर (INREG(DVOB) & PORT_ENABLE)
		dvo |= DVOB_PORT;
	अगर (INREG(DVOC) & PORT_ENABLE)
		dvo |= DVOC_PORT;

	वापस dvo;
पूर्ण

स्थिर अक्षर * पूर्णांकelfbhw_dvo_to_string(पूर्णांक dvo)
अणु
	अगर (dvo & DVOA_PORT)
		वापस "DVO port A";
	अन्यथा अगर (dvo & DVOB_PORT)
		वापस "DVO port B";
	अन्यथा अगर (dvo & DVOC_PORT)
		वापस "DVO port C";
	अन्यथा अगर (dvo & LVDS_PORT)
		वापस "LVDS port";
	अन्यथा
		वापस शून्य;
पूर्ण


पूर्णांक पूर्णांकelfbhw_validate_mode(काष्ठा पूर्णांकelfb_info *dinfo,
			    काष्ठा fb_var_screeninfo *var)
अणु
	पूर्णांक bytes_per_pixel;
	पूर्णांक पंचांगp;

#अगर VERBOSE > 0
	DBG_MSG("intelfbhw_validate_mode\n");
#पूर्ण_अगर

	bytes_per_pixel = var->bits_per_pixel / 8;
	अगर (bytes_per_pixel == 3)
		bytes_per_pixel = 4;

	/* Check अगर enough video memory. */
	पंचांगp = var->yres_भव * var->xres_भव * bytes_per_pixel;
	अगर (पंचांगp > dinfo->fb.size) अणु
		WRN_MSG("Not enough video ram for mode "
			"(%d KByte vs %d KByte).\n",
			BtoKB(पंचांगp), BtoKB(dinfo->fb.size));
		वापस 1;
	पूर्ण

	/* Check अगर x/y limits are OK. */
	अगर (var->xres - 1 > HACTIVE_MASK) अणु
		WRN_MSG("X resolution too large (%d vs %d).\n",
			var->xres, HACTIVE_MASK + 1);
		वापस 1;
	पूर्ण
	अगर (var->yres - 1 > VACTIVE_MASK) अणु
		WRN_MSG("Y resolution too large (%d vs %d).\n",
			var->yres, VACTIVE_MASK + 1);
		वापस 1;
	पूर्ण
	अगर (var->xres < 4) अणु
		WRN_MSG("X resolution too small (%d vs 4).\n", var->xres);
		वापस 1;
	पूर्ण
	अगर (var->yres < 4) अणु
		WRN_MSG("Y resolution too small (%d vs 4).\n", var->yres);
		वापस 1;
	पूर्ण

	/* Check क्रम द्विगुनscan modes. */
	अगर (var->vmode & FB_VMODE_DOUBLE) अणु
		WRN_MSG("Mode is double-scan.\n");
		वापस 1;
	पूर्ण

	अगर ((var->vmode & FB_VMODE_INTERLACED) && (var->yres & 1)) अणु
		WRN_MSG("Odd number of lines in interlaced mode\n");
		वापस 1;
	पूर्ण

	/* Check अगर घड़ी is OK. */
	पंचांगp = 1000000000 / var->pixघड़ी;
	अगर (पंचांगp < MIN_CLOCK) अणु
		WRN_MSG("Pixel clock is too low (%d MHz vs %d MHz).\n",
			(पंचांगp + 500) / 1000, MIN_CLOCK / 1000);
		वापस 1;
	पूर्ण
	अगर (पंचांगp > MAX_CLOCK) अणु
		WRN_MSG("Pixel clock is too high (%d MHz vs %d MHz).\n",
			(पंचांगp + 500) / 1000, MAX_CLOCK / 1000);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकelfbhw_pan_display(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा पूर्णांकelfb_info *dinfo = GET_DINFO(info);
	u32 offset, xoffset, yoffset;

#अगर VERBOSE > 0
	DBG_MSG("intelfbhw_pan_display\n");
#पूर्ण_अगर

	xoffset = ROUND_DOWN_TO(var->xoffset, 8);
	yoffset = var->yoffset;

	अगर ((xoffset + info->var.xres > info->var.xres_भव) ||
	    (yoffset + info->var.yres > info->var.yres_भव))
		वापस -EINVAL;

	offset = (yoffset * dinfo->pitch) +
		 (xoffset * info->var.bits_per_pixel) / 8;

	offset += dinfo->fb.offset << 12;

	dinfo->vsync.pan_offset = offset;
	अगर ((var->activate & FB_ACTIVATE_VBL) &&
	    !पूर्णांकelfbhw_enable_irq(dinfo))
		dinfo->vsync.pan_display = 1;
	अन्यथा अणु
		dinfo->vsync.pan_display = 0;
		OUTREG(DSPABASE, offset);
	पूर्ण

	वापस 0;
पूर्ण

/* Blank the screen. */
व्योम पूर्णांकelfbhw_करो_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा पूर्णांकelfb_info *dinfo = GET_DINFO(info);
	u32 पंचांगp;

#अगर VERBOSE > 0
	DBG_MSG("intelfbhw_do_blank: blank is %d\n", blank);
#पूर्ण_अगर

	/* Turn plane A on or off */
	पंचांगp = INREG(DSPACNTR);
	अगर (blank)
		पंचांगp &= ~DISPPLANE_PLANE_ENABLE;
	अन्यथा
		पंचांगp |= DISPPLANE_PLANE_ENABLE;
	OUTREG(DSPACNTR, पंचांगp);
	/* Flush */
	पंचांगp = INREG(DSPABASE);
	OUTREG(DSPABASE, पंचांगp);

	/* Turn off/on the HW cursor */
#अगर VERBOSE > 0
	DBG_MSG("cursor_on is %d\n", dinfo->cursor_on);
#पूर्ण_अगर
	अगर (dinfo->cursor_on) अणु
		अगर (blank)
			पूर्णांकelfbhw_cursor_hide(dinfo);
		अन्यथा
			पूर्णांकelfbhw_cursor_show(dinfo);
		dinfo->cursor_on = 1;
	पूर्ण
	dinfo->cursor_blanked = blank;

	/* Set DPMS level */
	पंचांगp = INREG(ADPA) & ~ADPA_DPMS_CONTROL_MASK;
	चयन (blank) अणु
	हाल FB_BLANK_UNBLANK:
	हाल FB_BLANK_NORMAL:
		पंचांगp |= ADPA_DPMS_D0;
		अवरोध;
	हाल FB_BLANK_VSYNC_SUSPEND:
		पंचांगp |= ADPA_DPMS_D1;
		अवरोध;
	हाल FB_BLANK_HSYNC_SUSPEND:
		पंचांगp |= ADPA_DPMS_D2;
		अवरोध;
	हाल FB_BLANK_POWERDOWN:
		पंचांगp |= ADPA_DPMS_D3;
		अवरोध;
	पूर्ण
	OUTREG(ADPA, पंचांगp);

	वापस;
पूर्ण


/* Check which pipe is connected to an active display plane. */
पूर्णांक पूर्णांकelfbhw_active_pipe(स्थिर काष्ठा पूर्णांकelfb_hwstate *hw)
अणु
	पूर्णांक pipe = -1;

	/* keep old शेष behaviour - prefer PIPE_A */
	अगर (hw->disp_b_ctrl & DISPPLANE_PLANE_ENABLE) अणु
		pipe = (hw->disp_b_ctrl >> DISPPLANE_SEL_PIPE_SHIFT);
		pipe &= PIPE_MASK;
		अगर (unlikely(pipe == PIPE_A))
			वापस PIPE_A;
	पूर्ण
	अगर (hw->disp_a_ctrl & DISPPLANE_PLANE_ENABLE) अणु
		pipe = (hw->disp_a_ctrl >> DISPPLANE_SEL_PIPE_SHIFT);
		pipe &= PIPE_MASK;
		अगर (likely(pipe == PIPE_A))
			वापस PIPE_A;
	पूर्ण
	/* Impossible that no pipe is selected - वापस PIPE_A */
	WARN_ON(pipe == -1);
	अगर (unlikely(pipe == -1))
		pipe = PIPE_A;

	वापस pipe;
पूर्ण

व्योम पूर्णांकelfbhw_setcolreg(काष्ठा पूर्णांकelfb_info *dinfo, अचिन्हित regno,
			 अचिन्हित red, अचिन्हित green, अचिन्हित blue,
			 अचिन्हित transp)
अणु
	u32 palette_reg = (dinfo->pipe == PIPE_A) ?
			  PALETTE_A : PALETTE_B;

#अगर VERBOSE > 0
	DBG_MSG("intelfbhw_setcolreg: %d: (%d, %d, %d)\n",
		regno, red, green, blue);
#पूर्ण_अगर

	OUTREG(palette_reg + (regno << 2),
	       (red << PALETTE_8_RED_SHIFT) |
	       (green << PALETTE_8_GREEN_SHIFT) |
	       (blue << PALETTE_8_BLUE_SHIFT));
पूर्ण


पूर्णांक पूर्णांकelfbhw_पढ़ो_hw_state(काष्ठा पूर्णांकelfb_info *dinfo,
			    काष्ठा पूर्णांकelfb_hwstate *hw, पूर्णांक flag)
अणु
	पूर्णांक i;

#अगर VERBOSE > 0
	DBG_MSG("intelfbhw_read_hw_state\n");
#पूर्ण_अगर

	अगर (!hw || !dinfo)
		वापस -1;

	/* Read in as much of the HW state as possible. */
	hw->vga0_भागisor = INREG(VGA0_DIVISOR);
	hw->vga1_भागisor = INREG(VGA1_DIVISOR);
	hw->vga_pd = INREG(VGAPD);
	hw->dpll_a = INREG(DPLL_A);
	hw->dpll_b = INREG(DPLL_B);
	hw->fpa0 = INREG(FPA0);
	hw->fpa1 = INREG(FPA1);
	hw->fpb0 = INREG(FPB0);
	hw->fpb1 = INREG(FPB1);

	अगर (flag == 1)
		वापस flag;

#अगर 0
	/* This seems to be a problem with the 852GM/855GM */
	क्रम (i = 0; i < PALETTE_8_ENTRIES; i++) अणु
		hw->palette_a[i] = INREG(PALETTE_A + (i << 2));
		hw->palette_b[i] = INREG(PALETTE_B + (i << 2));
	पूर्ण
#पूर्ण_अगर

	अगर (flag == 2)
		वापस flag;

	hw->htotal_a = INREG(HTOTAL_A);
	hw->hblank_a = INREG(HBLANK_A);
	hw->hsync_a = INREG(HSYNC_A);
	hw->vtotal_a = INREG(VTOTAL_A);
	hw->vblank_a = INREG(VBLANK_A);
	hw->vsync_a = INREG(VSYNC_A);
	hw->src_size_a = INREG(SRC_SIZE_A);
	hw->bclrpat_a = INREG(BCLRPAT_A);
	hw->htotal_b = INREG(HTOTAL_B);
	hw->hblank_b = INREG(HBLANK_B);
	hw->hsync_b = INREG(HSYNC_B);
	hw->vtotal_b = INREG(VTOTAL_B);
	hw->vblank_b = INREG(VBLANK_B);
	hw->vsync_b = INREG(VSYNC_B);
	hw->src_size_b = INREG(SRC_SIZE_B);
	hw->bclrpat_b = INREG(BCLRPAT_B);

	अगर (flag == 3)
		वापस flag;

	hw->adpa = INREG(ADPA);
	hw->dvoa = INREG(DVOA);
	hw->dvob = INREG(DVOB);
	hw->dvoc = INREG(DVOC);
	hw->dvoa_srcdim = INREG(DVOA_SRCDIM);
	hw->dvob_srcdim = INREG(DVOB_SRCDIM);
	hw->dvoc_srcdim = INREG(DVOC_SRCDIM);
	hw->lvds = INREG(LVDS);

	अगर (flag == 4)
		वापस flag;

	hw->pipe_a_conf = INREG(PIPEACONF);
	hw->pipe_b_conf = INREG(PIPEBCONF);
	hw->disp_arb = INREG(DISPARB);

	अगर (flag == 5)
		वापस flag;

	hw->cursor_a_control = INREG(CURSOR_A_CONTROL);
	hw->cursor_b_control = INREG(CURSOR_B_CONTROL);
	hw->cursor_a_base = INREG(CURSOR_A_BASEADDR);
	hw->cursor_b_base = INREG(CURSOR_B_BASEADDR);

	अगर (flag == 6)
		वापस flag;

	क्रम (i = 0; i < 4; i++) अणु
		hw->cursor_a_palette[i] = INREG(CURSOR_A_PALETTE0 + (i << 2));
		hw->cursor_b_palette[i] = INREG(CURSOR_B_PALETTE0 + (i << 2));
	पूर्ण

	अगर (flag == 7)
		वापस flag;

	hw->cursor_size = INREG(CURSOR_SIZE);

	अगर (flag == 8)
		वापस flag;

	hw->disp_a_ctrl = INREG(DSPACNTR);
	hw->disp_b_ctrl = INREG(DSPBCNTR);
	hw->disp_a_base = INREG(DSPABASE);
	hw->disp_b_base = INREG(DSPBBASE);
	hw->disp_a_stride = INREG(DSPASTRIDE);
	hw->disp_b_stride = INREG(DSPBSTRIDE);

	अगर (flag == 9)
		वापस flag;

	hw->vgacntrl = INREG(VGACNTRL);

	अगर (flag == 10)
		वापस flag;

	hw->add_id = INREG(ADD_ID);

	अगर (flag == 11)
		वापस flag;

	क्रम (i = 0; i < 7; i++) अणु
		hw->swf0x[i] = INREG(SWF00 + (i << 2));
		hw->swf1x[i] = INREG(SWF10 + (i << 2));
		अगर (i < 3)
			hw->swf3x[i] = INREG(SWF30 + (i << 2));
	पूर्ण

	क्रम (i = 0; i < 8; i++)
		hw->fence[i] = INREG(FENCE + (i << 2));

	hw->instpm = INREG(INSTPM);
	hw->mem_mode = INREG(MEM_MODE);
	hw->fw_blc_0 = INREG(FW_BLC_0);
	hw->fw_blc_1 = INREG(FW_BLC_1);

	hw->hwstam = INREG16(HWSTAM);
	hw->ier = INREG16(IER);
	hw->iir = INREG16(IIR);
	hw->imr = INREG16(IMR);

	वापस 0;
पूर्ण


अटल पूर्णांक calc_vघड़ी3(पूर्णांक index, पूर्णांक m, पूर्णांक n, पूर्णांक p)
अणु
	अगर (p == 0 || n == 0)
		वापस 0;
	वापस plls[index].ref_clk * m / n / p;
पूर्ण

अटल पूर्णांक calc_vघड़ी(पूर्णांक index, पूर्णांक m1, पूर्णांक m2, पूर्णांक n, पूर्णांक p1, पूर्णांक p2,
		       पूर्णांक lvds)
अणु
	काष्ठा pll_min_max *pll = &plls[index];
	u32 m, vco, p;

	m = (5 * (m1 + 2)) + (m2 + 2);
	n += 2;
	vco = pll->ref_clk * m / n;

	अगर (index == PLLS_I8xx)
		p = ((p1 + 2) * (1 << (p2 + 1)));
	अन्यथा
		p = ((p1) * (p2 ? 5 : 10));
	वापस vco / p;
पूर्ण

#अगर REGDUMP
अटल व्योम पूर्णांकelfbhw_get_p1p2(काष्ठा पूर्णांकelfb_info *dinfo, पूर्णांक dpll,
			       पूर्णांक *o_p1, पूर्णांक *o_p2)
अणु
	पूर्णांक p1, p2;

	अगर (IS_I9XX(dinfo)) अणु
		अगर (dpll & DPLL_P1_FORCE_DIV2)
			p1 = 1;
		अन्यथा
			p1 = (dpll >> DPLL_P1_SHIFT) & 0xff;

		p1 = ffs(p1);

		p2 = (dpll >> DPLL_I9XX_P2_SHIFT) & DPLL_P2_MASK;
	पूर्ण अन्यथा अणु
		अगर (dpll & DPLL_P1_FORCE_DIV2)
			p1 = 0;
		अन्यथा
			p1 = (dpll >> DPLL_P1_SHIFT) & DPLL_P1_MASK;
		p2 = (dpll >> DPLL_P2_SHIFT) & DPLL_P2_MASK;
	पूर्ण

	*o_p1 = p1;
	*o_p2 = p2;
पूर्ण
#पूर्ण_अगर


व्योम पूर्णांकelfbhw_prपूर्णांक_hw_state(काष्ठा पूर्णांकelfb_info *dinfo,
			      काष्ठा पूर्णांकelfb_hwstate *hw)
अणु
#अगर REGDUMP
	पूर्णांक i, m1, m2, n, p1, p2;
	पूर्णांक index = dinfo->pll_index;
	DBG_MSG("intelfbhw_print_hw_state\n");

	अगर (!hw)
		वापस;
	/* Read in as much of the HW state as possible. */
	prपूर्णांकk("hw state dump start\n");
	prपूर्णांकk("	VGA0_DIVISOR:		0x%08x\n", hw->vga0_भागisor);
	prपूर्णांकk("	VGA1_DIVISOR:		0x%08x\n", hw->vga1_भागisor);
	prपूर्णांकk("	VGAPD:			0x%08x\n", hw->vga_pd);
	n = (hw->vga0_भागisor >> FP_N_DIVISOR_SHIFT) & FP_DIVISOR_MASK;
	m1 = (hw->vga0_भागisor >> FP_M1_DIVISOR_SHIFT) & FP_DIVISOR_MASK;
	m2 = (hw->vga0_भागisor >> FP_M2_DIVISOR_SHIFT) & FP_DIVISOR_MASK;

	पूर्णांकelfbhw_get_p1p2(dinfo, hw->vga_pd, &p1, &p2);

	prपूर्णांकk("	VGA0: (m1, m2, n, p1, p2) = (%d, %d, %d, %d, %d)\n",
	       m1, m2, n, p1, p2);
	prपूर्णांकk("	VGA0: clock is %d\n",
	       calc_vघड़ी(index, m1, m2, n, p1, p2, 0));

	n = (hw->vga1_भागisor >> FP_N_DIVISOR_SHIFT) & FP_DIVISOR_MASK;
	m1 = (hw->vga1_भागisor >> FP_M1_DIVISOR_SHIFT) & FP_DIVISOR_MASK;
	m2 = (hw->vga1_भागisor >> FP_M2_DIVISOR_SHIFT) & FP_DIVISOR_MASK;

	पूर्णांकelfbhw_get_p1p2(dinfo, hw->vga_pd, &p1, &p2);
	prपूर्णांकk("	VGA1: (m1, m2, n, p1, p2) = (%d, %d, %d, %d, %d)\n",
	       m1, m2, n, p1, p2);
	prपूर्णांकk("	VGA1: clock is %d\n",
	       calc_vघड़ी(index, m1, m2, n, p1, p2, 0));

	prपूर्णांकk("	DPLL_A:			0x%08x\n", hw->dpll_a);
	prपूर्णांकk("	DPLL_B:			0x%08x\n", hw->dpll_b);
	prपूर्णांकk("	FPA0:			0x%08x\n", hw->fpa0);
	prपूर्णांकk("	FPA1:			0x%08x\n", hw->fpa1);
	prपूर्णांकk("	FPB0:			0x%08x\n", hw->fpb0);
	prपूर्णांकk("	FPB1:			0x%08x\n", hw->fpb1);

	n = (hw->fpa0 >> FP_N_DIVISOR_SHIFT) & FP_DIVISOR_MASK;
	m1 = (hw->fpa0 >> FP_M1_DIVISOR_SHIFT) & FP_DIVISOR_MASK;
	m2 = (hw->fpa0 >> FP_M2_DIVISOR_SHIFT) & FP_DIVISOR_MASK;

	पूर्णांकelfbhw_get_p1p2(dinfo, hw->dpll_a, &p1, &p2);

	prपूर्णांकk("	PLLA0: (m1, m2, n, p1, p2) = (%d, %d, %d, %d, %d)\n",
	       m1, m2, n, p1, p2);
	prपूर्णांकk("	PLLA0: clock is %d\n",
	       calc_vघड़ी(index, m1, m2, n, p1, p2, 0));

	n = (hw->fpa1 >> FP_N_DIVISOR_SHIFT) & FP_DIVISOR_MASK;
	m1 = (hw->fpa1 >> FP_M1_DIVISOR_SHIFT) & FP_DIVISOR_MASK;
	m2 = (hw->fpa1 >> FP_M2_DIVISOR_SHIFT) & FP_DIVISOR_MASK;

	पूर्णांकelfbhw_get_p1p2(dinfo, hw->dpll_a, &p1, &p2);

	prपूर्णांकk("	PLLA1: (m1, m2, n, p1, p2) = (%d, %d, %d, %d, %d)\n",
	       m1, m2, n, p1, p2);
	prपूर्णांकk("	PLLA1: clock is %d\n",
	       calc_vघड़ी(index, m1, m2, n, p1, p2, 0));

#अगर 0
	prपूर्णांकk("	PALETTE_A:\n");
	क्रम (i = 0; i < PALETTE_8_ENTRIES)
		prपूर्णांकk("	%3d:	0x%08x\n", i, hw->palette_a[i]);
	prपूर्णांकk("	PALETTE_B:\n");
	क्रम (i = 0; i < PALETTE_8_ENTRIES)
		prपूर्णांकk("	%3d:	0x%08x\n", i, hw->palette_b[i]);
#पूर्ण_अगर

	prपूर्णांकk("	HTOTAL_A:		0x%08x\n", hw->htotal_a);
	prपूर्णांकk("	HBLANK_A:		0x%08x\n", hw->hblank_a);
	prपूर्णांकk("	HSYNC_A:		0x%08x\n", hw->hsync_a);
	prपूर्णांकk("	VTOTAL_A:		0x%08x\n", hw->vtotal_a);
	prपूर्णांकk("	VBLANK_A:		0x%08x\n", hw->vblank_a);
	prपूर्णांकk("	VSYNC_A:		0x%08x\n", hw->vsync_a);
	prपूर्णांकk("	SRC_SIZE_A:		0x%08x\n", hw->src_size_a);
	prपूर्णांकk("	BCLRPAT_A:		0x%08x\n", hw->bclrpat_a);
	prपूर्णांकk("	HTOTAL_B:		0x%08x\n", hw->htotal_b);
	prपूर्णांकk("	HBLANK_B:		0x%08x\n", hw->hblank_b);
	prपूर्णांकk("	HSYNC_B:		0x%08x\n", hw->hsync_b);
	prपूर्णांकk("	VTOTAL_B:		0x%08x\n", hw->vtotal_b);
	prपूर्णांकk("	VBLANK_B:		0x%08x\n", hw->vblank_b);
	prपूर्णांकk("	VSYNC_B:		0x%08x\n", hw->vsync_b);
	prपूर्णांकk("	SRC_SIZE_B:		0x%08x\n", hw->src_size_b);
	prपूर्णांकk("	BCLRPAT_B:		0x%08x\n", hw->bclrpat_b);

	prपूर्णांकk("	ADPA:			0x%08x\n", hw->adpa);
	prपूर्णांकk("	DVOA:			0x%08x\n", hw->dvoa);
	prपूर्णांकk("	DVOB:			0x%08x\n", hw->dvob);
	prपूर्णांकk("	DVOC:			0x%08x\n", hw->dvoc);
	prपूर्णांकk("	DVOA_SRCDIM:		0x%08x\n", hw->dvoa_srcdim);
	prपूर्णांकk("	DVOB_SRCDIM:		0x%08x\n", hw->dvob_srcdim);
	prपूर्णांकk("	DVOC_SRCDIM:		0x%08x\n", hw->dvoc_srcdim);
	prपूर्णांकk("	LVDS:			0x%08x\n", hw->lvds);

	prपूर्णांकk("	PIPEACONF:		0x%08x\n", hw->pipe_a_conf);
	prपूर्णांकk("	PIPEBCONF:		0x%08x\n", hw->pipe_b_conf);
	prपूर्णांकk("	DISPARB:		0x%08x\n", hw->disp_arb);

	prपूर्णांकk("	CURSOR_A_CONTROL:	0x%08x\n", hw->cursor_a_control);
	prपूर्णांकk("	CURSOR_B_CONTROL:	0x%08x\n", hw->cursor_b_control);
	prपूर्णांकk("	CURSOR_A_BASEADDR:	0x%08x\n", hw->cursor_a_base);
	prपूर्णांकk("	CURSOR_B_BASEADDR:	0x%08x\n", hw->cursor_b_base);

	prपूर्णांकk("	CURSOR_A_PALETTE:	");
	क्रम (i = 0; i < 4; i++) अणु
		prपूर्णांकk("0x%08x", hw->cursor_a_palette[i]);
		अगर (i < 3)
			prपूर्णांकk(", ");
	पूर्ण
	prपूर्णांकk("\n");
	prपूर्णांकk("	CURSOR_B_PALETTE:	");
	क्रम (i = 0; i < 4; i++) अणु
		prपूर्णांकk("0x%08x", hw->cursor_b_palette[i]);
		अगर (i < 3)
			prपूर्णांकk(", ");
	पूर्ण
	prपूर्णांकk("\n");

	prपूर्णांकk("	CURSOR_SIZE:		0x%08x\n", hw->cursor_size);

	prपूर्णांकk("	DSPACNTR:		0x%08x\n", hw->disp_a_ctrl);
	prपूर्णांकk("	DSPBCNTR:		0x%08x\n", hw->disp_b_ctrl);
	prपूर्णांकk("	DSPABASE:		0x%08x\n", hw->disp_a_base);
	prपूर्णांकk("	DSPBBASE:		0x%08x\n", hw->disp_b_base);
	prपूर्णांकk("	DSPASTRIDE:		0x%08x\n", hw->disp_a_stride);
	prपूर्णांकk("	DSPBSTRIDE:		0x%08x\n", hw->disp_b_stride);

	prपूर्णांकk("	VGACNTRL:		0x%08x\n", hw->vgacntrl);
	prपूर्णांकk("	ADD_ID:			0x%08x\n", hw->add_id);

	क्रम (i = 0; i < 7; i++) अणु
		prपूर्णांकk("	SWF0%d			0x%08x\n", i,
			hw->swf0x[i]);
	पूर्ण
	क्रम (i = 0; i < 7; i++) अणु
		prपूर्णांकk("	SWF1%d			0x%08x\n", i,
			hw->swf1x[i]);
	पूर्ण
	क्रम (i = 0; i < 3; i++) अणु
		prपूर्णांकk("	SWF3%d			0x%08x\n", i,
		       hw->swf3x[i]);
	पूर्ण
	क्रम (i = 0; i < 8; i++)
		prपूर्णांकk("	FENCE%d			0x%08x\n", i,
		       hw->fence[i]);

	prपूर्णांकk("	INSTPM			0x%08x\n", hw->instpm);
	prपूर्णांकk("	MEM_MODE		0x%08x\n", hw->mem_mode);
	prपूर्णांकk("	FW_BLC_0		0x%08x\n", hw->fw_blc_0);
	prपूर्णांकk("	FW_BLC_1		0x%08x\n", hw->fw_blc_1);

	prपूर्णांकk("	HWSTAM			0x%04x\n", hw->hwstam);
	prपूर्णांकk("	IER			0x%04x\n", hw->ier);
	prपूर्णांकk("	IIR			0x%04x\n", hw->iir);
	prपूर्णांकk("	IMR			0x%04x\n", hw->imr);
	prपूर्णांकk("hw state dump end\n");
#पूर्ण_अगर
पूर्ण



/* Split the M parameter पूर्णांकo M1 and M2. */
अटल पूर्णांक spliपंचांग(पूर्णांक index, अचिन्हित पूर्णांक m, अचिन्हित पूर्णांक *reपंचांग1,
		  अचिन्हित पूर्णांक *reपंचांग2)
अणु
	पूर्णांक m1, m2;
	पूर्णांक tesपंचांग;
	काष्ठा pll_min_max *pll = &plls[index];

	/* no poपूर्णांक optimising too much - brute क्रमce m */
	क्रम (m1 = pll->min_m1; m1 < pll->max_m1 + 1; m1++) अणु
		क्रम (m2 = pll->min_m2; m2 < pll->max_m2 + 1; m2++) अणु
			tesपंचांग = (5 * (m1 + 2)) + (m2 + 2);
			अगर (tesपंचांग == m) अणु
				*reपंचांग1 = (अचिन्हित पूर्णांक)m1;
				*reपंचांग2 = (अचिन्हित पूर्णांक)m2;
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

/* Split the P parameter पूर्णांकo P1 and P2. */
अटल पूर्णांक splitp(पूर्णांक index, अचिन्हित पूर्णांक p, अचिन्हित पूर्णांक *retp1,
		  अचिन्हित पूर्णांक *retp2)
अणु
	पूर्णांक p1, p2;
	काष्ठा pll_min_max *pll = &plls[index];

	अगर (index == PLLS_I9xx) अणु
		p2 = (p % 10) ? 1 : 0;

		p1 = p / (p2 ? 5 : 10);

		*retp1 = (अचिन्हित पूर्णांक)p1;
		*retp2 = (अचिन्हित पूर्णांक)p2;
		वापस 0;
	पूर्ण

	अगर (p % 4 == 0)
		p2 = 1;
	अन्यथा
		p2 = 0;
	p1 = (p / (1 << (p2 + 1))) - 2;
	अगर (p % 4 == 0 && p1 < pll->min_p1) अणु
		p2 = 0;
		p1 = (p / (1 << (p2 + 1))) - 2;
	पूर्ण
	अगर (p1 < pll->min_p1 || p1 > pll->max_p1 ||
	    (p1 + 2) * (1 << (p2 + 1)) != p) अणु
		वापस 1;
	पूर्ण अन्यथा अणु
		*retp1 = (अचिन्हित पूर्णांक)p1;
		*retp2 = (अचिन्हित पूर्णांक)p2;
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक calc_pll_params(पूर्णांक index, पूर्णांक घड़ी, u32 *reपंचांग1, u32 *reपंचांग2,
			   u32 *retn, u32 *retp1, u32 *retp2, u32 *retघड़ी)
अणु
	u32 m1, m2, n, p1, p2, n1, tesपंचांग;
	u32 f_vco, p, p_best = 0, m, f_out = 0;
	u32 err_best = 10000000;
	u32 n_best = 0, m_best = 0, f_err;
	u32 p_min, p_max, p_inc, भाग_max;
	काष्ठा pll_min_max *pll = &plls[index];

	DBG_MSG("Clock is %d\n", घड़ी);

	भाग_max = pll->max_vco / घड़ी;

	p_inc = (घड़ी <= pll->p_transition_clk) ? pll->p_inc_lo : pll->p_inc_hi;
	p_min = p_inc;
	p_max = ROUND_DOWN_TO(भाग_max, p_inc);
	अगर (p_min < pll->min_p)
		p_min = pll->min_p;
	अगर (p_max > pll->max_p)
		p_max = pll->max_p;

	DBG_MSG("p range is %d-%d (%d)\n", p_min, p_max, p_inc);

	p = p_min;
	करो अणु
		अगर (splitp(index, p, &p1, &p2)) अणु
			WRN_MSG("cannot split p = %d\n", p);
			p += p_inc;
			जारी;
		पूर्ण
		n = pll->min_n;
		f_vco = घड़ी * p;

		करो अणु
			m = ROUND_UP_TO(f_vco * n, pll->ref_clk) / pll->ref_clk;
			अगर (m < pll->min_m)
				m = pll->min_m + 1;
			अगर (m > pll->max_m)
				m = pll->max_m - 1;
			क्रम (tesपंचांग = m - 1; tesपंचांग <= m; tesपंचांग++) अणु
				f_out = calc_vघड़ी3(index, tesपंचांग, n, p);
				अगर (spliपंचांग(index, tesपंचांग, &m1, &m2)) अणु
					WRN_MSG("cannot split m = %d\n",
						tesपंचांग);
					जारी;
				पूर्ण
				अगर (घड़ी > f_out)
					f_err = घड़ी - f_out;
				अन्यथा/* slightly bias the error क्रम bigger घड़ीs */
					f_err = f_out - घड़ी + 1;

				अगर (f_err < err_best) अणु
					m_best = tesपंचांग;
					n_best = n;
					p_best = p;
					err_best = f_err;
				पूर्ण
			पूर्ण
			n++;
		पूर्ण जबतक ((n <= pll->max_n) && (f_out >= घड़ी));
		p += p_inc;
	पूर्ण जबतक ((p <= p_max));

	अगर (!m_best) अणु
		WRN_MSG("cannot find parameters for clock %d\n", घड़ी);
		वापस 1;
	पूर्ण
	m = m_best;
	n = n_best;
	p = p_best;
	spliपंचांग(index, m, &m1, &m2);
	splitp(index, p, &p1, &p2);
	n1 = n - 2;

	DBG_MSG("m, n, p: %d (%d,%d), %d (%d), %d (%d,%d), "
		"f: %d (%d), VCO: %d\n",
		m, m1, m2, n, n1, p, p1, p2,
		calc_vघड़ी3(index, m, n, p),
		calc_vघड़ी(index, m1, m2, n1, p1, p2, 0),
		calc_vघड़ी3(index, m, n, p) * p);
	*reपंचांग1 = m1;
	*reपंचांग2 = m2;
	*retn = n1;
	*retp1 = p1;
	*retp2 = p2;
	*retघड़ी = calc_vघड़ी(index, m1, m2, n1, p1, p2, 0);

	वापस 0;
पूर्ण

अटल __अंतरभूत__ पूर्णांक check_overflow(u32 value, u32 limit,
				     स्थिर अक्षर *description)
अणु
	अगर (value > limit) अणु
		WRN_MSG("%s value %d exceeds limit %d\n",
			description, value, limit);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* It is assumed that hw is filled in with the initial state inक्रमmation. */
पूर्णांक पूर्णांकelfbhw_mode_to_hw(काष्ठा पूर्णांकelfb_info *dinfo,
			 काष्ठा पूर्णांकelfb_hwstate *hw,
			 काष्ठा fb_var_screeninfo *var)
अणु
	पूर्णांक pipe = पूर्णांकelfbhw_active_pipe(hw);
	u32 *dpll, *fp0, *fp1;
	u32 m1, m2, n, p1, p2, घड़ी_प्रकारarget, घड़ी;
	u32 hsync_start, hsync_end, hblank_start, hblank_end, htotal, hactive;
	u32 vsync_start, vsync_end, vblank_start, vblank_end, vtotal, vactive;
	u32 vsync_pol, hsync_pol;
	u32 *vs, *vb, *vt, *hs, *hb, *ht, *ss, *pipe_conf;
	u32 stride_alignment;

	DBG_MSG("intelfbhw_mode_to_hw\n");

	/* Disable VGA */
	hw->vgacntrl |= VGA_DISABLE;

	/* Set which pipe's रेजिस्टरs will be set. */
	अगर (pipe == PIPE_B) अणु
		dpll = &hw->dpll_b;
		fp0 = &hw->fpb0;
		fp1 = &hw->fpb1;
		hs = &hw->hsync_b;
		hb = &hw->hblank_b;
		ht = &hw->htotal_b;
		vs = &hw->vsync_b;
		vb = &hw->vblank_b;
		vt = &hw->vtotal_b;
		ss = &hw->src_size_b;
		pipe_conf = &hw->pipe_b_conf;
	पूर्ण अन्यथा अणु
		dpll = &hw->dpll_a;
		fp0 = &hw->fpa0;
		fp1 = &hw->fpa1;
		hs = &hw->hsync_a;
		hb = &hw->hblank_a;
		ht = &hw->htotal_a;
		vs = &hw->vsync_a;
		vb = &hw->vblank_a;
		vt = &hw->vtotal_a;
		ss = &hw->src_size_a;
		pipe_conf = &hw->pipe_a_conf;
	पूर्ण

	/* Use ADPA रेजिस्टर क्रम sync control. */
	hw->adpa &= ~ADPA_USE_VGA_HVPOLARITY;

	/* sync polarity */
	hsync_pol = (var->sync & FB_SYNC_HOR_HIGH_ACT) ?
			ADPA_SYNC_ACTIVE_HIGH : ADPA_SYNC_ACTIVE_LOW;
	vsync_pol = (var->sync & FB_SYNC_VERT_HIGH_ACT) ?
			ADPA_SYNC_ACTIVE_HIGH : ADPA_SYNC_ACTIVE_LOW;
	hw->adpa &= ~((ADPA_SYNC_ACTIVE_MASK << ADPA_VSYNC_ACTIVE_SHIFT) |
		      (ADPA_SYNC_ACTIVE_MASK << ADPA_HSYNC_ACTIVE_SHIFT));
	hw->adpa |= (hsync_pol << ADPA_HSYNC_ACTIVE_SHIFT) |
		    (vsync_pol << ADPA_VSYNC_ACTIVE_SHIFT);

	/* Connect correct pipe to the analog port DAC */
	hw->adpa &= ~(PIPE_MASK << ADPA_PIPE_SELECT_SHIFT);
	hw->adpa |= (pipe << ADPA_PIPE_SELECT_SHIFT);

	/* Set DPMS state to D0 (on) */
	hw->adpa &= ~ADPA_DPMS_CONTROL_MASK;
	hw->adpa |= ADPA_DPMS_D0;

	hw->adpa |= ADPA_DAC_ENABLE;

	*dpll |= (DPLL_VCO_ENABLE | DPLL_VGA_MODE_DISABLE);
	*dpll &= ~(DPLL_RATE_SELECT_MASK | DPLL_REFERENCE_SELECT_MASK);
	*dpll |= (DPLL_REFERENCE_DEFAULT | DPLL_RATE_SELECT_FP0);

	/* Desired घड़ी in kHz */
	घड़ी_प्रकारarget = 1000000000 / var->pixघड़ी;

	अगर (calc_pll_params(dinfo->pll_index, घड़ी_प्रकारarget, &m1, &m2,
			    &n, &p1, &p2, &घड़ी)) अणु
		WRN_MSG("calc_pll_params failed\n");
		वापस 1;
	पूर्ण

	/* Check क्रम overflow. */
	अगर (check_overflow(p1, DPLL_P1_MASK, "PLL P1 parameter"))
		वापस 1;
	अगर (check_overflow(p2, DPLL_P2_MASK, "PLL P2 parameter"))
		वापस 1;
	अगर (check_overflow(m1, FP_DIVISOR_MASK, "PLL M1 parameter"))
		वापस 1;
	अगर (check_overflow(m2, FP_DIVISOR_MASK, "PLL M2 parameter"))
		वापस 1;
	अगर (check_overflow(n, FP_DIVISOR_MASK, "PLL N parameter"))
		वापस 1;

	*dpll &= ~DPLL_P1_FORCE_DIV2;
	*dpll &= ~((DPLL_P2_MASK << DPLL_P2_SHIFT) |
		   (DPLL_P1_MASK << DPLL_P1_SHIFT));

	अगर (IS_I9XX(dinfo)) अणु
		*dpll |= (p2 << DPLL_I9XX_P2_SHIFT);
		*dpll |= (1 << (p1 - 1)) << DPLL_P1_SHIFT;
	पूर्ण अन्यथा
		*dpll |= (p2 << DPLL_P2_SHIFT) | (p1 << DPLL_P1_SHIFT);

	*fp0 = (n << FP_N_DIVISOR_SHIFT) |
	       (m1 << FP_M1_DIVISOR_SHIFT) |
	       (m2 << FP_M2_DIVISOR_SHIFT);
	*fp1 = *fp0;

	hw->dvob &= ~PORT_ENABLE;
	hw->dvoc &= ~PORT_ENABLE;

	/* Use display plane A. */
	hw->disp_a_ctrl |= DISPPLANE_PLANE_ENABLE;
	hw->disp_a_ctrl &= ~DISPPLANE_GAMMA_ENABLE;
	hw->disp_a_ctrl &= ~DISPPLANE_PIXFORMAT_MASK;
	चयन (पूर्णांकelfb_var_to_depth(var)) अणु
	हाल 8:
		hw->disp_a_ctrl |= DISPPLANE_8BPP | DISPPLANE_GAMMA_ENABLE;
		अवरोध;
	हाल 15:
		hw->disp_a_ctrl |= DISPPLANE_15_16BPP;
		अवरोध;
	हाल 16:
		hw->disp_a_ctrl |= DISPPLANE_16BPP;
		अवरोध;
	हाल 24:
		hw->disp_a_ctrl |= DISPPLANE_32BPP_NO_ALPHA;
		अवरोध;
	पूर्ण
	hw->disp_a_ctrl &= ~(PIPE_MASK << DISPPLANE_SEL_PIPE_SHIFT);
	hw->disp_a_ctrl |= (pipe << DISPPLANE_SEL_PIPE_SHIFT);

	/* Set CRTC रेजिस्टरs. */
	hactive = var->xres;
	hsync_start = hactive + var->right_margin;
	hsync_end = hsync_start + var->hsync_len;
	htotal = hsync_end + var->left_margin;
	hblank_start = hactive;
	hblank_end = htotal;

	DBG_MSG("H: act %d, ss %d, se %d, tot %d bs %d, be %d\n",
		hactive, hsync_start, hsync_end, htotal, hblank_start,
		hblank_end);

	vactive = var->yres;
	अगर (var->vmode & FB_VMODE_INTERLACED)
		vactive--; /* the chip adds 2 halflines स्वतःmatically */
	vsync_start = vactive + var->lower_margin;
	vsync_end = vsync_start + var->vsync_len;
	vtotal = vsync_end + var->upper_margin;
	vblank_start = vactive;
	vblank_end = vsync_end + 1;

	DBG_MSG("V: act %d, ss %d, se %d, tot %d bs %d, be %d\n",
		vactive, vsync_start, vsync_end, vtotal, vblank_start,
		vblank_end);

	/* Adjust क्रम रेजिस्टर values, and check क्रम overflow. */
	hactive--;
	अगर (check_overflow(hactive, HACTIVE_MASK, "CRTC hactive"))
		वापस 1;
	hsync_start--;
	अगर (check_overflow(hsync_start, HSYNCSTART_MASK, "CRTC hsync_start"))
		वापस 1;
	hsync_end--;
	अगर (check_overflow(hsync_end, HSYNCEND_MASK, "CRTC hsync_end"))
		वापस 1;
	htotal--;
	अगर (check_overflow(htotal, HTOTAL_MASK, "CRTC htotal"))
		वापस 1;
	hblank_start--;
	अगर (check_overflow(hblank_start, HBLANKSTART_MASK, "CRTC hblank_start"))
		वापस 1;
	hblank_end--;
	अगर (check_overflow(hblank_end, HBLANKEND_MASK, "CRTC hblank_end"))
		वापस 1;

	vactive--;
	अगर (check_overflow(vactive, VACTIVE_MASK, "CRTC vactive"))
		वापस 1;
	vsync_start--;
	अगर (check_overflow(vsync_start, VSYNCSTART_MASK, "CRTC vsync_start"))
		वापस 1;
	vsync_end--;
	अगर (check_overflow(vsync_end, VSYNCEND_MASK, "CRTC vsync_end"))
		वापस 1;
	vtotal--;
	अगर (check_overflow(vtotal, VTOTAL_MASK, "CRTC vtotal"))
		वापस 1;
	vblank_start--;
	अगर (check_overflow(vblank_start, VBLANKSTART_MASK, "CRTC vblank_start"))
		वापस 1;
	vblank_end--;
	अगर (check_overflow(vblank_end, VBLANKEND_MASK, "CRTC vblank_end"))
		वापस 1;

	*ht = (htotal << HTOTAL_SHIFT) | (hactive << HACTIVE_SHIFT);
	*hb = (hblank_start << HBLANKSTART_SHIFT) |
	      (hblank_end << HSYNCEND_SHIFT);
	*hs = (hsync_start << HSYNCSTART_SHIFT) | (hsync_end << HSYNCEND_SHIFT);

	*vt = (vtotal << VTOTAL_SHIFT) | (vactive << VACTIVE_SHIFT);
	*vb = (vblank_start << VBLANKSTART_SHIFT) |
	      (vblank_end << VSYNCEND_SHIFT);
	*vs = (vsync_start << VSYNCSTART_SHIFT) | (vsync_end << VSYNCEND_SHIFT);
	*ss = (hactive << SRC_SIZE_HORIZ_SHIFT) |
	      (vactive << SRC_SIZE_VERT_SHIFT);

	hw->disp_a_stride = dinfo->pitch;
	DBG_MSG("pitch is %d\n", hw->disp_a_stride);

	hw->disp_a_base = hw->disp_a_stride * var->yoffset +
			  var->xoffset * var->bits_per_pixel / 8;

	hw->disp_a_base += dinfo->fb.offset << 12;

	/* Check stride alignment. */
	stride_alignment = IS_I9XX(dinfo) ? STRIDE_ALIGNMENT_I9XX :
					    STRIDE_ALIGNMENT;
	अगर (hw->disp_a_stride % stride_alignment != 0) अणु
		WRN_MSG("display stride %d has bad alignment %d\n",
			hw->disp_a_stride, stride_alignment);
		वापस 1;
	पूर्ण

	/* Set the palette to 8-bit mode. */
	*pipe_conf &= ~PIPECONF_GAMMA;

	अगर (var->vmode & FB_VMODE_INTERLACED)
		*pipe_conf |= PIPECONF_INTERLACE_W_FIELD_INDICATION;
	अन्यथा
		*pipe_conf &= ~PIPECONF_INTERLACE_MASK;

	वापस 0;
पूर्ण

/* Program a (non-VGA) video mode. */
पूर्णांक पूर्णांकelfbhw_program_mode(काष्ठा पूर्णांकelfb_info *dinfo,
			   स्थिर काष्ठा पूर्णांकelfb_hwstate *hw, पूर्णांक blank)
अणु
	u32 पंचांगp;
	स्थिर u32 *dpll, *fp0, *fp1, *pipe_conf;
	स्थिर u32 *hs, *ht, *hb, *vs, *vt, *vb, *ss;
	u32 dpll_reg, fp0_reg, fp1_reg, pipe_conf_reg, pipe_stat_reg;
	u32 hsync_reg, htotal_reg, hblank_reg;
	u32 vsync_reg, vtotal_reg, vblank_reg;
	u32 src_size_reg;
	u32 count, पंचांगp_val[3];

	/* Assume single pipe */

#अगर VERBOSE > 0
	DBG_MSG("intelfbhw_program_mode\n");
#पूर्ण_अगर

	/* Disable VGA */
	पंचांगp = INREG(VGACNTRL);
	पंचांगp |= VGA_DISABLE;
	OUTREG(VGACNTRL, पंचांगp);

	dinfo->pipe = पूर्णांकelfbhw_active_pipe(hw);

	अगर (dinfo->pipe == PIPE_B) अणु
		dpll = &hw->dpll_b;
		fp0 = &hw->fpb0;
		fp1 = &hw->fpb1;
		pipe_conf = &hw->pipe_b_conf;
		hs = &hw->hsync_b;
		hb = &hw->hblank_b;
		ht = &hw->htotal_b;
		vs = &hw->vsync_b;
		vb = &hw->vblank_b;
		vt = &hw->vtotal_b;
		ss = &hw->src_size_b;
		dpll_reg = DPLL_B;
		fp0_reg = FPB0;
		fp1_reg = FPB1;
		pipe_conf_reg = PIPEBCONF;
		pipe_stat_reg = PIPEBSTAT;
		hsync_reg = HSYNC_B;
		htotal_reg = HTOTAL_B;
		hblank_reg = HBLANK_B;
		vsync_reg = VSYNC_B;
		vtotal_reg = VTOTAL_B;
		vblank_reg = VBLANK_B;
		src_size_reg = SRC_SIZE_B;
	पूर्ण अन्यथा अणु
		dpll = &hw->dpll_a;
		fp0 = &hw->fpa0;
		fp1 = &hw->fpa1;
		pipe_conf = &hw->pipe_a_conf;
		hs = &hw->hsync_a;
		hb = &hw->hblank_a;
		ht = &hw->htotal_a;
		vs = &hw->vsync_a;
		vb = &hw->vblank_a;
		vt = &hw->vtotal_a;
		ss = &hw->src_size_a;
		dpll_reg = DPLL_A;
		fp0_reg = FPA0;
		fp1_reg = FPA1;
		pipe_conf_reg = PIPEACONF;
		pipe_stat_reg = PIPEASTAT;
		hsync_reg = HSYNC_A;
		htotal_reg = HTOTAL_A;
		hblank_reg = HBLANK_A;
		vsync_reg = VSYNC_A;
		vtotal_reg = VTOTAL_A;
		vblank_reg = VBLANK_A;
		src_size_reg = SRC_SIZE_A;
	पूर्ण

	/* turn off pipe */
	पंचांगp = INREG(pipe_conf_reg);
	पंचांगp &= ~PIPECONF_ENABLE;
	OUTREG(pipe_conf_reg, पंचांगp);

	count = 0;
	करो अणु
		पंचांगp_val[count % 3] = INREG(PIPEA_DSL);
		अगर ((पंचांगp_val[0] == पंचांगp_val[1]) && (पंचांगp_val[1] == पंचांगp_val[2]))
			अवरोध;
		count++;
		udelay(1);
		अगर (count % 200 == 0) अणु
			पंचांगp = INREG(pipe_conf_reg);
			पंचांगp &= ~PIPECONF_ENABLE;
			OUTREG(pipe_conf_reg, पंचांगp);
		पूर्ण
	पूर्ण जबतक (count < 2000);

	OUTREG(ADPA, INREG(ADPA) & ~ADPA_DAC_ENABLE);

	/* Disable planes A and B. */
	पंचांगp = INREG(DSPACNTR);
	पंचांगp &= ~DISPPLANE_PLANE_ENABLE;
	OUTREG(DSPACNTR, पंचांगp);
	पंचांगp = INREG(DSPBCNTR);
	पंचांगp &= ~DISPPLANE_PLANE_ENABLE;
	OUTREG(DSPBCNTR, पंचांगp);

	/* Wait क्रम vblank. For now, just रुको क्रम a 50Hz cycle (20ms)) */
	mdelay(20);

	OUTREG(DVOB, INREG(DVOB) & ~PORT_ENABLE);
	OUTREG(DVOC, INREG(DVOC) & ~PORT_ENABLE);
	OUTREG(ADPA, INREG(ADPA) & ~ADPA_DAC_ENABLE);

	/* Disable Sync */
	पंचांगp = INREG(ADPA);
	पंचांगp &= ~ADPA_DPMS_CONTROL_MASK;
	पंचांगp |= ADPA_DPMS_D3;
	OUTREG(ADPA, पंचांगp);

	/* करो some funky magic - xyzzy */
	OUTREG(0x61204, 0xabcd0000);

	/* turn off PLL */
	पंचांगp = INREG(dpll_reg);
	पंचांगp &= ~DPLL_VCO_ENABLE;
	OUTREG(dpll_reg, पंचांगp);

	/* Set PLL parameters */
	OUTREG(fp0_reg, *fp0);
	OUTREG(fp1_reg, *fp1);

	/* Enable PLL */
	OUTREG(dpll_reg, *dpll);

	/* Set DVOs B/C */
	OUTREG(DVOB, hw->dvob);
	OUTREG(DVOC, hw->dvoc);

	/* unकरो funky magic */
	OUTREG(0x61204, 0x00000000);

	/* Set ADPA */
	OUTREG(ADPA, INREG(ADPA) | ADPA_DAC_ENABLE);
	OUTREG(ADPA, (hw->adpa & ~(ADPA_DPMS_CONTROL_MASK)) | ADPA_DPMS_D3);

	/* Set pipe parameters */
	OUTREG(hsync_reg, *hs);
	OUTREG(hblank_reg, *hb);
	OUTREG(htotal_reg, *ht);
	OUTREG(vsync_reg, *vs);
	OUTREG(vblank_reg, *vb);
	OUTREG(vtotal_reg, *vt);
	OUTREG(src_size_reg, *ss);

	चयन (dinfo->info->var.vmode & (FB_VMODE_INTERLACED |
					  FB_VMODE_ODD_FLD_FIRST)) अणु
	हाल FB_VMODE_INTERLACED | FB_VMODE_ODD_FLD_FIRST:
		OUTREG(pipe_stat_reg, 0xFFFF | PIPESTAT_FLD_EVT_ODD_EN);
		अवरोध;
	हाल FB_VMODE_INTERLACED: /* even lines first */
		OUTREG(pipe_stat_reg, 0xFFFF | PIPESTAT_FLD_EVT_EVEN_EN);
		अवरोध;
	शेष:		/* non-पूर्णांकerlaced */
		OUTREG(pipe_stat_reg, 0xFFFF); /* clear all status bits only */
	पूर्ण
	/* Enable pipe */
	OUTREG(pipe_conf_reg, *pipe_conf | PIPECONF_ENABLE);

	/* Enable sync */
	पंचांगp = INREG(ADPA);
	पंचांगp &= ~ADPA_DPMS_CONTROL_MASK;
	पंचांगp |= ADPA_DPMS_D0;
	OUTREG(ADPA, पंचांगp);

	/* setup display plane */
	अगर (dinfo->pdev->device == PCI_DEVICE_ID_INTEL_830M) अणु
		/*
		 *      i830M errata: the display plane must be enabled
		 *      to allow ग_लिखोs to the other bits in the plane
		 *      control रेजिस्टर.
		 */
		पंचांगp = INREG(DSPACNTR);
		अगर ((पंचांगp & DISPPLANE_PLANE_ENABLE) != DISPPLANE_PLANE_ENABLE) अणु
			पंचांगp |= DISPPLANE_PLANE_ENABLE;
			OUTREG(DSPACNTR, पंचांगp);
			OUTREG(DSPACNTR,
			       hw->disp_a_ctrl|DISPPLANE_PLANE_ENABLE);
			mdelay(1);
		पूर्ण
	पूर्ण

	OUTREG(DSPACNTR, hw->disp_a_ctrl & ~DISPPLANE_PLANE_ENABLE);
	OUTREG(DSPASTRIDE, hw->disp_a_stride);
	OUTREG(DSPABASE, hw->disp_a_base);

	/* Enable plane */
	अगर (!blank) अणु
		पंचांगp = INREG(DSPACNTR);
		पंचांगp |= DISPPLANE_PLANE_ENABLE;
		OUTREG(DSPACNTR, पंचांगp);
		OUTREG(DSPABASE, hw->disp_a_base);
	पूर्ण

	वापस 0;
पूर्ण

/* क्रमward declarations */
अटल व्योम refresh_ring(काष्ठा पूर्णांकelfb_info *dinfo);
अटल व्योम reset_state(काष्ठा पूर्णांकelfb_info *dinfo);
अटल व्योम करो_flush(काष्ठा पूर्णांकelfb_info *dinfo);

अटल  u32 get_ring_space(काष्ठा पूर्णांकelfb_info *dinfo)
अणु
	u32 ring_space;

	अगर (dinfo->ring_tail >= dinfo->ring_head)
		ring_space = dinfo->ring.size -
			(dinfo->ring_tail - dinfo->ring_head);
	अन्यथा
		ring_space = dinfo->ring_head - dinfo->ring_tail;

	अगर (ring_space > RING_MIN_FREE)
		ring_space -= RING_MIN_FREE;
	अन्यथा
		ring_space = 0;

	वापस ring_space;
पूर्ण

अटल पूर्णांक रुको_ring(काष्ठा पूर्णांकelfb_info *dinfo, पूर्णांक n)
अणु
	पूर्णांक i = 0;
	अचिन्हित दीर्घ end;
	u32 last_head = INREG(PRI_RING_HEAD) & RING_HEAD_MASK;

#अगर VERBOSE > 0
	DBG_MSG("wait_ring: %d\n", n);
#पूर्ण_अगर

	end = jअगरfies + (HZ * 3);
	जबतक (dinfo->ring_space < n) अणु
		dinfo->ring_head = INREG(PRI_RING_HEAD) & RING_HEAD_MASK;
		dinfo->ring_space = get_ring_space(dinfo);

		अगर (dinfo->ring_head != last_head) अणु
			end = jअगरfies + (HZ * 3);
			last_head = dinfo->ring_head;
		पूर्ण
		i++;
		अगर (समय_beक्रमe(end, jअगरfies)) अणु
			अगर (!i) अणु
				/* Try again */
				reset_state(dinfo);
				refresh_ring(dinfo);
				करो_flush(dinfo);
				end = jअगरfies + (HZ * 3);
				i = 1;
			पूर्ण अन्यथा अणु
				WRN_MSG("ring buffer : space: %d wanted %d\n",
					dinfo->ring_space, n);
				WRN_MSG("lockup - turning off hardware "
					"acceleration\n");
				dinfo->ring_lockup = 1;
				अवरोध;
			पूर्ण
		पूर्ण
		udelay(1);
	पूर्ण
	वापस i;
पूर्ण

अटल व्योम करो_flush(काष्ठा पूर्णांकelfb_info *dinfo)
अणु
	START_RING(2);
	OUT_RING(MI_FLUSH | MI_WRITE_सूचीTY_STATE | MI_INVALIDATE_MAP_CACHE);
	OUT_RING(MI_NOOP);
	ADVANCE_RING();
पूर्ण

व्योम पूर्णांकelfbhw_करो_sync(काष्ठा पूर्णांकelfb_info *dinfo)
अणु
#अगर VERBOSE > 0
	DBG_MSG("intelfbhw_do_sync\n");
#पूर्ण_अगर

	अगर (!dinfo->accel)
		वापस;

	/*
	 * Send a flush, then रुको until the ring is empty.  This is what
	 * the XFree86 driver करोes, and actually it करोesn't seem a lot worse
	 * than the recommended method (both have problems).
	 */
	करो_flush(dinfo);
	रुको_ring(dinfo, dinfo->ring.size - RING_MIN_FREE);
	dinfo->ring_space = dinfo->ring.size - RING_MIN_FREE;
पूर्ण

अटल व्योम refresh_ring(काष्ठा पूर्णांकelfb_info *dinfo)
अणु
#अगर VERBOSE > 0
	DBG_MSG("refresh_ring\n");
#पूर्ण_अगर

	dinfo->ring_head = INREG(PRI_RING_HEAD) & RING_HEAD_MASK;
	dinfo->ring_tail = INREG(PRI_RING_TAIL) & RING_TAIL_MASK;
	dinfo->ring_space = get_ring_space(dinfo);
पूर्ण

अटल व्योम reset_state(काष्ठा पूर्णांकelfb_info *dinfo)
अणु
	पूर्णांक i;
	u32 पंचांगp;

#अगर VERBOSE > 0
	DBG_MSG("reset_state\n");
#पूर्ण_अगर

	क्रम (i = 0; i < FENCE_NUM; i++)
		OUTREG(FENCE + (i << 2), 0);

	/* Flush the ring buffer अगर it's enabled. */
	पंचांगp = INREG(PRI_RING_LENGTH);
	अगर (पंचांगp & RING_ENABLE) अणु
#अगर VERBOSE > 0
		DBG_MSG("reset_state: ring was enabled\n");
#पूर्ण_अगर
		refresh_ring(dinfo);
		पूर्णांकelfbhw_करो_sync(dinfo);
		DO_RING_IDLE();
	पूर्ण

	OUTREG(PRI_RING_LENGTH, 0);
	OUTREG(PRI_RING_HEAD, 0);
	OUTREG(PRI_RING_TAIL, 0);
	OUTREG(PRI_RING_START, 0);
पूर्ण

/* Stop the 2D engine, and turn off the ring buffer. */
व्योम पूर्णांकelfbhw_2d_stop(काष्ठा पूर्णांकelfb_info *dinfo)
अणु
#अगर VERBOSE > 0
	DBG_MSG("intelfbhw_2d_stop: accel: %d, ring_active: %d\n",
		dinfo->accel, dinfo->ring_active);
#पूर्ण_अगर

	अगर (!dinfo->accel)
		वापस;

	dinfo->ring_active = 0;
	reset_state(dinfo);
पूर्ण

/*
 * Enable the ring buffer, and initialise the 2D engine.
 * It is assumed that the graphics engine has been stopped by previously
 * calling पूर्णांकelfb_2d_stop().
 */
व्योम पूर्णांकelfbhw_2d_start(काष्ठा पूर्णांकelfb_info *dinfo)
अणु
#अगर VERBOSE > 0
	DBG_MSG("intelfbhw_2d_start: accel: %d, ring_active: %d\n",
		dinfo->accel, dinfo->ring_active);
#पूर्ण_अगर

	अगर (!dinfo->accel)
		वापस;

	/* Initialise the primary ring buffer. */
	OUTREG(PRI_RING_LENGTH, 0);
	OUTREG(PRI_RING_TAIL, 0);
	OUTREG(PRI_RING_HEAD, 0);

	OUTREG(PRI_RING_START, dinfo->ring.physical & RING_START_MASK);
	OUTREG(PRI_RING_LENGTH,
		((dinfo->ring.size - GTT_PAGE_SIZE) & RING_LENGTH_MASK) |
		RING_NO_REPORT | RING_ENABLE);
	refresh_ring(dinfo);
	dinfo->ring_active = 1;
पूर्ण

/* 2D fillrect (solid fill or invert) */
व्योम पूर्णांकelfbhw_करो_fillrect(काष्ठा पूर्णांकelfb_info *dinfo, u32 x, u32 y, u32 w,
			   u32 h, u32 color, u32 pitch, u32 bpp, u32 rop)
अणु
	u32 br00, br09, br13, br14, br16;

#अगर VERBOSE > 0
	DBG_MSG("intelfbhw_do_fillrect: (%d,%d) %dx%d, c 0x%06x, p %d bpp %d, "
		"rop 0x%02x\n", x, y, w, h, color, pitch, bpp, rop);
#पूर्ण_अगर

	br00 = COLOR_BLT_CMD;
	br09 = dinfo->fb_start + (y * pitch + x * (bpp / 8));
	br13 = (rop << ROP_SHIFT) | pitch;
	br14 = (h << HEIGHT_SHIFT) | ((w * (bpp / 8)) << WIDTH_SHIFT);
	br16 = color;

	चयन (bpp) अणु
	हाल 8:
		br13 |= COLOR_DEPTH_8;
		अवरोध;
	हाल 16:
		br13 |= COLOR_DEPTH_16;
		अवरोध;
	हाल 32:
		br13 |= COLOR_DEPTH_32;
		br00 |= WRITE_ALPHA | WRITE_RGB;
		अवरोध;
	पूर्ण

	START_RING(6);
	OUT_RING(br00);
	OUT_RING(br13);
	OUT_RING(br14);
	OUT_RING(br09);
	OUT_RING(br16);
	OUT_RING(MI_NOOP);
	ADVANCE_RING();

#अगर VERBOSE > 0
	DBG_MSG("ring = 0x%08x, 0x%08x (%d)\n", dinfo->ring_head,
		dinfo->ring_tail, dinfo->ring_space);
#पूर्ण_अगर
पूर्ण

व्योम
पूर्णांकelfbhw_करो_bitblt(काष्ठा पूर्णांकelfb_info *dinfo, u32 curx, u32 cury,
		    u32 dstx, u32 dsty, u32 w, u32 h, u32 pitch, u32 bpp)
अणु
	u32 br00, br09, br11, br12, br13, br22, br23, br26;

#अगर VERBOSE > 0
	DBG_MSG("intelfbhw_do_bitblt: (%d,%d)->(%d,%d) %dx%d, p %d bpp %d\n",
		curx, cury, dstx, dsty, w, h, pitch, bpp);
#पूर्ण_अगर

	br00 = XY_SRC_COPY_BLT_CMD;
	br09 = dinfo->fb_start;
	br11 = (pitch << PITCH_SHIFT);
	br12 = dinfo->fb_start;
	br13 = (SRC_ROP_GXCOPY << ROP_SHIFT) | (pitch << PITCH_SHIFT);
	br22 = (dstx << WIDTH_SHIFT) | (dsty << HEIGHT_SHIFT);
	br23 = ((dstx + w) << WIDTH_SHIFT) |
	       ((dsty + h) << HEIGHT_SHIFT);
	br26 = (curx << WIDTH_SHIFT) | (cury << HEIGHT_SHIFT);

	चयन (bpp) अणु
	हाल 8:
		br13 |= COLOR_DEPTH_8;
		अवरोध;
	हाल 16:
		br13 |= COLOR_DEPTH_16;
		अवरोध;
	हाल 32:
		br13 |= COLOR_DEPTH_32;
		br00 |= WRITE_ALPHA | WRITE_RGB;
		अवरोध;
	पूर्ण

	START_RING(8);
	OUT_RING(br00);
	OUT_RING(br13);
	OUT_RING(br22);
	OUT_RING(br23);
	OUT_RING(br09);
	OUT_RING(br26);
	OUT_RING(br11);
	OUT_RING(br12);
	ADVANCE_RING();
पूर्ण

पूर्णांक पूर्णांकelfbhw_करो_drawglyph(काष्ठा पूर्णांकelfb_info *dinfo, u32 fg, u32 bg, u32 w,
			   u32 h, स्थिर u8* cdat, u32 x, u32 y, u32 pitch,
			   u32 bpp)
अणु
	पूर्णांक nbytes, ndwords, pad, पंचांगp;
	u32 br00, br09, br13, br18, br19, br22, br23;
	पूर्णांक dat, ix, iy, iw;
	पूर्णांक i, j;

#अगर VERBOSE > 0
	DBG_MSG("intelfbhw_do_drawglyph: (%d,%d) %dx%d\n", x, y, w, h);
#पूर्ण_अगर

	/* size in bytes of a padded scanline */
	nbytes = ROUND_UP_TO(w, 16) / 8;

	/* Total bytes of padded scanline data to ग_लिखो out. */
	nbytes = nbytes * h;

	/*
	 * Check अगर the glyph data exceeds the immediate mode limit.
	 * It would take a large font (1K pixels) to hit this limit.
	 */
	अगर (nbytes > MAX_MONO_IMM_SIZE)
		वापस 0;

	/* Src data is packaged a dword (32-bit) at a समय. */
	ndwords = ROUND_UP_TO(nbytes, 4) / 4;

	/*
	 * Ring has to be padded to a quad word. But because the command starts
	   with 7 bytes, pad only अगर there is an even number of ndwords
	 */
	pad = !(ndwords % 2);

	पंचांगp = (XY_MONO_SRC_IMM_BLT_CMD & DW_LENGTH_MASK) + ndwords;
	br00 = (XY_MONO_SRC_IMM_BLT_CMD & ~DW_LENGTH_MASK) | पंचांगp;
	br09 = dinfo->fb_start;
	br13 = (SRC_ROP_GXCOPY << ROP_SHIFT) | (pitch << PITCH_SHIFT);
	br18 = bg;
	br19 = fg;
	br22 = (x << WIDTH_SHIFT) | (y << HEIGHT_SHIFT);
	br23 = ((x + w) << WIDTH_SHIFT) | ((y + h) << HEIGHT_SHIFT);

	चयन (bpp) अणु
	हाल 8:
		br13 |= COLOR_DEPTH_8;
		अवरोध;
	हाल 16:
		br13 |= COLOR_DEPTH_16;
		अवरोध;
	हाल 32:
		br13 |= COLOR_DEPTH_32;
		br00 |= WRITE_ALPHA | WRITE_RGB;
		अवरोध;
	पूर्ण

	START_RING(8 + ndwords);
	OUT_RING(br00);
	OUT_RING(br13);
	OUT_RING(br22);
	OUT_RING(br23);
	OUT_RING(br09);
	OUT_RING(br18);
	OUT_RING(br19);
	ix = iy = 0;
	iw = ROUND_UP_TO(w, 8) / 8;
	जबतक (ndwords--) अणु
		dat = 0;
		क्रम (j = 0; j < 2; ++j) अणु
			क्रम (i = 0; i < 2; ++i) अणु
				अगर (ix != iw || i == 0)
					dat |= cdat[iy*iw + ix++] << (i+j*2)*8;
			पूर्ण
			अगर (ix == iw && iy != (h-1)) अणु
				ix = 0;
				++iy;
			पूर्ण
		पूर्ण
		OUT_RING(dat);
	पूर्ण
	अगर (pad)
		OUT_RING(MI_NOOP);
	ADVANCE_RING();

	वापस 1;
पूर्ण

/* HW cursor functions. */
व्योम पूर्णांकelfbhw_cursor_init(काष्ठा पूर्णांकelfb_info *dinfo)
अणु
	u32 पंचांगp;

#अगर VERBOSE > 0
	DBG_MSG("intelfbhw_cursor_init\n");
#पूर्ण_अगर

	अगर (dinfo->mobile || IS_I9XX(dinfo)) अणु
		अगर (!dinfo->cursor.physical)
			वापस;
		पंचांगp = INREG(CURSOR_A_CONTROL);
		पंचांगp &= ~(CURSOR_MODE_MASK | CURSOR_MOBILE_GAMMA_ENABLE |
			 CURSOR_MEM_TYPE_LOCAL |
			 (1 << CURSOR_PIPE_SELECT_SHIFT));
		पंचांगp |= CURSOR_MODE_DISABLE;
		OUTREG(CURSOR_A_CONTROL, पंचांगp);
		OUTREG(CURSOR_A_BASEADDR, dinfo->cursor.physical);
	पूर्ण अन्यथा अणु
		पंचांगp = INREG(CURSOR_CONTROL);
		पंचांगp &= ~(CURSOR_FORMAT_MASK | CURSOR_GAMMA_ENABLE |
			 CURSOR_ENABLE | CURSOR_STRIDE_MASK);
		पंचांगp |= CURSOR_FORMAT_3C;
		OUTREG(CURSOR_CONTROL, पंचांगp);
		OUTREG(CURSOR_A_BASEADDR, dinfo->cursor.offset << 12);
		पंचांगp = (64 << CURSOR_SIZE_H_SHIFT) |
		      (64 << CURSOR_SIZE_V_SHIFT);
		OUTREG(CURSOR_SIZE, पंचांगp);
	पूर्ण
पूर्ण

व्योम पूर्णांकelfbhw_cursor_hide(काष्ठा पूर्णांकelfb_info *dinfo)
अणु
	u32 पंचांगp;

#अगर VERBOSE > 0
	DBG_MSG("intelfbhw_cursor_hide\n");
#पूर्ण_अगर

	dinfo->cursor_on = 0;
	अगर (dinfo->mobile || IS_I9XX(dinfo)) अणु
		अगर (!dinfo->cursor.physical)
			वापस;
		पंचांगp = INREG(CURSOR_A_CONTROL);
		पंचांगp &= ~CURSOR_MODE_MASK;
		पंचांगp |= CURSOR_MODE_DISABLE;
		OUTREG(CURSOR_A_CONTROL, पंचांगp);
		/* Flush changes */
		OUTREG(CURSOR_A_BASEADDR, dinfo->cursor.physical);
	पूर्ण अन्यथा अणु
		पंचांगp = INREG(CURSOR_CONTROL);
		पंचांगp &= ~CURSOR_ENABLE;
		OUTREG(CURSOR_CONTROL, पंचांगp);
	पूर्ण
पूर्ण

व्योम पूर्णांकelfbhw_cursor_show(काष्ठा पूर्णांकelfb_info *dinfo)
अणु
	u32 पंचांगp;

#अगर VERBOSE > 0
	DBG_MSG("intelfbhw_cursor_show\n");
#पूर्ण_अगर

	dinfo->cursor_on = 1;

	अगर (dinfo->cursor_blanked)
		वापस;

	अगर (dinfo->mobile || IS_I9XX(dinfo)) अणु
		अगर (!dinfo->cursor.physical)
			वापस;
		पंचांगp = INREG(CURSOR_A_CONTROL);
		पंचांगp &= ~CURSOR_MODE_MASK;
		पंचांगp |= CURSOR_MODE_64_4C_AX;
		OUTREG(CURSOR_A_CONTROL, पंचांगp);
		/* Flush changes */
		OUTREG(CURSOR_A_BASEADDR, dinfo->cursor.physical);
	पूर्ण अन्यथा अणु
		पंचांगp = INREG(CURSOR_CONTROL);
		पंचांगp |= CURSOR_ENABLE;
		OUTREG(CURSOR_CONTROL, पंचांगp);
	पूर्ण
पूर्ण

व्योम पूर्णांकelfbhw_cursor_setpos(काष्ठा पूर्णांकelfb_info *dinfo, पूर्णांक x, पूर्णांक y)
अणु
	u32 पंचांगp;

#अगर VERBOSE > 0
	DBG_MSG("intelfbhw_cursor_setpos: (%d, %d)\n", x, y);
#पूर्ण_अगर

	/*
	 * Sets the position. The coordinates are assumed to alपढ़ोy
	 * have any offset adjusted. Assume that the cursor is never
	 * completely off-screen, and that x, y are always >= 0.
	 */

	पंचांगp = ((x & CURSOR_POS_MASK) << CURSOR_X_SHIFT) |
	      ((y & CURSOR_POS_MASK) << CURSOR_Y_SHIFT);
	OUTREG(CURSOR_A_POSITION, पंचांगp);

	अगर (IS_I9XX(dinfo))
		OUTREG(CURSOR_A_BASEADDR, dinfo->cursor.physical);
पूर्ण

व्योम पूर्णांकelfbhw_cursor_setcolor(काष्ठा पूर्णांकelfb_info *dinfo, u32 bg, u32 fg)
अणु
#अगर VERBOSE > 0
	DBG_MSG("intelfbhw_cursor_setcolor\n");
#पूर्ण_अगर

	OUTREG(CURSOR_A_PALETTE0, bg & CURSOR_PALETTE_MASK);
	OUTREG(CURSOR_A_PALETTE1, fg & CURSOR_PALETTE_MASK);
	OUTREG(CURSOR_A_PALETTE2, fg & CURSOR_PALETTE_MASK);
	OUTREG(CURSOR_A_PALETTE3, bg & CURSOR_PALETTE_MASK);
पूर्ण

व्योम पूर्णांकelfbhw_cursor_load(काष्ठा पूर्णांकelfb_info *dinfo, पूर्णांक width, पूर्णांक height,
			   u8 *data)
अणु
	u8 __iomem *addr = (u8 __iomem *)dinfo->cursor.भव;
	पूर्णांक i, j, w = width / 8;
	पूर्णांक mod = width % 8, t_mask, d_mask;

#अगर VERBOSE > 0
	DBG_MSG("intelfbhw_cursor_load\n");
#पूर्ण_अगर

	अगर (!dinfo->cursor.भव)
		वापस;

	t_mask = 0xff >> mod;
	d_mask = ~(0xff >> mod);
	क्रम (i = height; i--; ) अणु
		क्रम (j = 0; j < w; j++) अणु
			ग_लिखोb(0x00, addr + j);
			ग_लिखोb(*(data++), addr + j+8);
		पूर्ण
		अगर (mod) अणु
			ग_लिखोb(t_mask, addr + j);
			ग_लिखोb(*(data++) & d_mask, addr + j+8);
		पूर्ण
		addr += 16;
	पूर्ण
पूर्ण

व्योम पूर्णांकelfbhw_cursor_reset(काष्ठा पूर्णांकelfb_info *dinfo)
अणु
	u8 __iomem *addr = (u8 __iomem *)dinfo->cursor.भव;
	पूर्णांक i, j;

#अगर VERBOSE > 0
	DBG_MSG("intelfbhw_cursor_reset\n");
#पूर्ण_अगर

	अगर (!dinfo->cursor.भव)
		वापस;

	क्रम (i = 64; i--; ) अणु
		क्रम (j = 0; j < 8; j++) अणु
			ग_लिखोb(0xff, addr + j+0);
			ग_लिखोb(0x00, addr + j+8);
		पूर्ण
		addr += 16;
	पूर्ण
पूर्ण

अटल irqवापस_t पूर्णांकelfbhw_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	u16 पंचांगp;
	काष्ठा पूर्णांकelfb_info *dinfo = dev_id;

	spin_lock(&dinfo->पूर्णांक_lock);

	पंचांगp = INREG16(IIR);
	अगर (dinfo->info->var.vmode & FB_VMODE_INTERLACED)
		पंचांगp &= PIPE_A_EVENT_INTERRUPT;
	अन्यथा
		पंचांगp &= VSYNC_PIPE_A_INTERRUPT; /* non-पूर्णांकerlaced */

	अगर (पंचांगp == 0) अणु
		spin_unlock(&dinfo->पूर्णांक_lock);
		वापस IRQ_RETVAL(0); /* not us */
	पूर्ण

	/* clear status bits 0-15 ASAP and करोn't touch bits 16-31 */
	OUTREG(PIPEASTAT, INREG(PIPEASTAT));

	OUTREG16(IIR, पंचांगp);
	अगर (dinfo->vsync.pan_display) अणु
		dinfo->vsync.pan_display = 0;
		OUTREG(DSPABASE, dinfo->vsync.pan_offset);
	पूर्ण

	dinfo->vsync.count++;
	wake_up_पूर्णांकerruptible(&dinfo->vsync.रुको);

	spin_unlock(&dinfo->पूर्णांक_lock);

	वापस IRQ_RETVAL(1);
पूर्ण

पूर्णांक पूर्णांकelfbhw_enable_irq(काष्ठा पूर्णांकelfb_info *dinfo)
अणु
	u16 पंचांगp;
	अगर (!test_and_set_bit(0, &dinfo->irq_flags)) अणु
		अगर (request_irq(dinfo->pdev->irq, पूर्णांकelfbhw_irq, IRQF_SHARED,
				"intelfb", dinfo)) अणु
			clear_bit(0, &dinfo->irq_flags);
			वापस -EINVAL;
		पूर्ण

		spin_lock_irq(&dinfo->पूर्णांक_lock);
		OUTREG16(HWSTAM, 0xfffe); /* i830 DRM uses ffff */
		OUTREG16(IMR, 0);
	पूर्ण अन्यथा
		spin_lock_irq(&dinfo->पूर्णांक_lock);

	अगर (dinfo->info->var.vmode & FB_VMODE_INTERLACED)
		पंचांगp = PIPE_A_EVENT_INTERRUPT;
	अन्यथा
		पंचांगp = VSYNC_PIPE_A_INTERRUPT; /* non-पूर्णांकerlaced */
	अगर (पंचांगp != INREG16(IER)) अणु
		DBG_MSG("changing IER to 0x%X\n", पंचांगp);
		OUTREG16(IER, पंचांगp);
	पूर्ण

	spin_unlock_irq(&dinfo->पूर्णांक_lock);
	वापस 0;
पूर्ण

व्योम पूर्णांकelfbhw_disable_irq(काष्ठा पूर्णांकelfb_info *dinfo)
अणु
	अगर (test_and_clear_bit(0, &dinfo->irq_flags)) अणु
		अगर (dinfo->vsync.pan_display) अणु
			dinfo->vsync.pan_display = 0;
			OUTREG(DSPABASE, dinfo->vsync.pan_offset);
		पूर्ण
		spin_lock_irq(&dinfo->पूर्णांक_lock);
		OUTREG16(HWSTAM, 0xffff);
		OUTREG16(IMR, 0xffff);
		OUTREG16(IER, 0x0);

		OUTREG16(IIR, INREG16(IIR)); /* clear IRQ requests */
		spin_unlock_irq(&dinfo->पूर्णांक_lock);

		मुक्त_irq(dinfo->pdev->irq, dinfo);
	पूर्ण
पूर्ण

पूर्णांक पूर्णांकelfbhw_रुको_क्रम_vsync(काष्ठा पूर्णांकelfb_info *dinfo, u32 pipe)
अणु
	काष्ठा पूर्णांकelfb_vsync *vsync;
	अचिन्हित पूर्णांक count;
	पूर्णांक ret;

	चयन (pipe) अणु
		हाल 0:
			vsync = &dinfo->vsync;
			अवरोध;
		शेष:
			वापस -ENODEV;
	पूर्ण

	ret = पूर्णांकelfbhw_enable_irq(dinfo);
	अगर (ret)
		वापस ret;

	count = vsync->count;
	ret = रुको_event_पूर्णांकerruptible_समयout(vsync->रुको,
					       count != vsync->count, HZ / 10);
	अगर (ret < 0)
		वापस ret;
	अगर (ret == 0) अणु
		DBG_MSG("wait_for_vsync timed out!\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण
