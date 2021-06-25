<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* -*- linux-c -*- ------------------------------------------------------- *
 *
 *   Copyright (C) 1991, 1992 Linus Torvalds
 *   Copyright 2007 rPath, Inc. - All Rights Reserved
 *   Copyright 2009 Intel Corporation; author H. Peter Anvin
 *
 * ----------------------------------------------------------------------- */

/*
 * VESA text modes
 */

#समावेश "boot.h"
#समावेश "video.h"
#समावेश "vesa.h"
#समावेश "string.h"

/* VESA inक्रमmation */
अटल काष्ठा vesa_general_info vginfo;
अटल काष्ठा vesa_mode_info vminfo;

अटल __videocard video_vesa;

#अगर_अघोषित _WAKEUP
अटल व्योम vesa_store_mode_params_graphics(व्योम);
#अन्यथा /* _WAKEUP */
अटल अंतरभूत व्योम vesa_store_mode_params_graphics(व्योम) अणुपूर्ण
#पूर्ण_अगर /* _WAKEUP */

अटल पूर्णांक vesa_probe(व्योम)
अणु
	काष्ठा biosregs ireg, oreg;
	u16 mode;
	addr_t mode_ptr;
	काष्ठा mode_info *mi;
	पूर्णांक nmodes = 0;

	video_vesa.modes = GET_HEAP(काष्ठा mode_info, 0);

	initregs(&ireg);
	ireg.ax = 0x4f00;
	ireg.di = (माप_प्रकार)&vginfo;
	पूर्णांकcall(0x10, &ireg, &oreg);

	अगर (oreg.ax != 0x004f ||
	    vginfo.signature != VESA_MAGIC ||
	    vginfo.version < 0x0102)
		वापस 0;	/* Not present */

	set_fs(vginfo.video_mode_ptr.seg);
	mode_ptr = vginfo.video_mode_ptr.off;

	जबतक ((mode = rdfs16(mode_ptr)) != 0xffff) अणु
		mode_ptr += 2;

		अगर (!heap_मुक्त(माप(काष्ठा mode_info)))
			अवरोध;	/* Heap full, can't save mode info */

		अगर (mode & ~0x1ff)
			जारी;

		स_रखो(&vminfo, 0, माप(vminfo)); /* Just in हाल... */

		ireg.ax = 0x4f01;
		ireg.cx = mode;
		ireg.di = (माप_प्रकार)&vminfo;
		पूर्णांकcall(0x10, &ireg, &oreg);

		अगर (oreg.ax != 0x004f)
			जारी;

		अगर ((vminfo.mode_attr & 0x15) == 0x05) अणु
			/* Text Mode, TTY BIOS supported,
			   supported by hardware */
			mi = GET_HEAP(काष्ठा mode_info, 1);
			mi->mode  = mode + VIDEO_FIRST_VESA;
			mi->depth = 0; /* text */
			mi->x     = vminfo.h_res;
			mi->y     = vminfo.v_res;
			nmodes++;
		पूर्ण अन्यथा अगर ((vminfo.mode_attr & 0x99) == 0x99 &&
			   (vminfo.memory_layout == 4 ||
			    vminfo.memory_layout == 6) &&
			   vminfo.memory_planes == 1) अणु
#अगर_घोषित CONFIG_FB_BOOT_VESA_SUPPORT
			/* Graphics mode, color, linear frame buffer
			   supported.  Only रेजिस्टर the mode अगर
			   अगर framebuffer is configured, however,
			   otherwise the user will be left without a screen. */
			mi = GET_HEAP(काष्ठा mode_info, 1);
			mi->mode = mode + VIDEO_FIRST_VESA;
			mi->depth = vminfo.bpp;
			mi->x = vminfo.h_res;
			mi->y = vminfo.v_res;
			nmodes++;
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	वापस nmodes;
पूर्ण

अटल पूर्णांक vesa_set_mode(काष्ठा mode_info *mode)
अणु
	काष्ठा biosregs ireg, oreg;
	पूर्णांक is_graphic;
	u16 vesa_mode = mode->mode - VIDEO_FIRST_VESA;

	स_रखो(&vminfo, 0, माप(vminfo)); /* Just in हाल... */

	initregs(&ireg);
	ireg.ax = 0x4f01;
	ireg.cx = vesa_mode;
	ireg.di = (माप_प्रकार)&vminfo;
	पूर्णांकcall(0x10, &ireg, &oreg);

	अगर (oreg.ax != 0x004f)
		वापस -1;

	अगर ((vminfo.mode_attr & 0x15) == 0x05) अणु
		/* It's a supported text mode */
		is_graphic = 0;
#अगर_घोषित CONFIG_FB_BOOT_VESA_SUPPORT
	पूर्ण अन्यथा अगर ((vminfo.mode_attr & 0x99) == 0x99) अणु
		/* It's a graphics mode with linear frame buffer */
		is_graphic = 1;
		vesa_mode |= 0x4000; /* Request linear frame buffer */
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		वापस -1;	/* Invalid mode */
	पूर्ण


	initregs(&ireg);
	ireg.ax = 0x4f02;
	ireg.bx = vesa_mode;
	पूर्णांकcall(0x10, &ireg, &oreg);

	अगर (oreg.ax != 0x004f)
		वापस -1;

	graphic_mode = is_graphic;
	अगर (!is_graphic) अणु
		/* Text mode */
		क्रमce_x = mode->x;
		क्रमce_y = mode->y;
		करो_restore = 1;
	पूर्ण अन्यथा अणु
		/* Graphics mode */
		vesa_store_mode_params_graphics();
	पूर्ण

	वापस 0;
पूर्ण


#अगर_अघोषित _WAKEUP

/* Switch DAC to 8-bit mode */
अटल व्योम vesa_dac_set_8bits(व्योम)
अणु
	काष्ठा biosregs ireg, oreg;
	u8 dac_size = 6;

	/* If possible, चयन the DAC to 8-bit mode */
	अगर (vginfo.capabilities & 1) अणु
		initregs(&ireg);
		ireg.ax = 0x4f08;
		ireg.bh = 0x08;
		पूर्णांकcall(0x10, &ireg, &oreg);
		अगर (oreg.ax == 0x004f)
			dac_size = oreg.bh;
	पूर्ण

	/* Set the color sizes to the DAC size, and offsets to 0 */
	boot_params.screen_info.red_size   = dac_size;
	boot_params.screen_info.green_size = dac_size;
	boot_params.screen_info.blue_size  = dac_size;
	boot_params.screen_info.rsvd_size  = dac_size;

	boot_params.screen_info.red_pos    = 0;
	boot_params.screen_info.green_pos  = 0;
	boot_params.screen_info.blue_pos   = 0;
	boot_params.screen_info.rsvd_pos   = 0;
पूर्ण

/* Save the VESA रक्षित mode info */
अटल व्योम vesa_store_pm_info(व्योम)
अणु
	काष्ठा biosregs ireg, oreg;

	initregs(&ireg);
	ireg.ax = 0x4f0a;
	पूर्णांकcall(0x10, &ireg, &oreg);

	अगर (oreg.ax != 0x004f)
		वापस;

	boot_params.screen_info.vesapm_seg = oreg.es;
	boot_params.screen_info.vesapm_off = oreg.di;
पूर्ण

/*
 * Save video mode parameters क्रम graphics mode
 */
अटल व्योम vesa_store_mode_params_graphics(व्योम)
अणु
	/* Tell the kernel we're in VESA graphics mode */
	boot_params.screen_info.orig_video_isVGA = VIDEO_TYPE_VLFB;

	/* Mode parameters */
	boot_params.screen_info.vesa_attributes = vminfo.mode_attr;
	boot_params.screen_info.lfb_linelength = vminfo.logical_scan;
	boot_params.screen_info.lfb_width = vminfo.h_res;
	boot_params.screen_info.lfb_height = vminfo.v_res;
	boot_params.screen_info.lfb_depth = vminfo.bpp;
	boot_params.screen_info.pages = vminfo.image_planes;
	boot_params.screen_info.lfb_base = vminfo.lfb_ptr;
	स_नकल(&boot_params.screen_info.red_size,
	       &vminfo.rmask, 8);

	/* General parameters */
	boot_params.screen_info.lfb_size = vginfo.total_memory;

	अगर (vminfo.bpp <= 8)
		vesa_dac_set_8bits();

	vesa_store_pm_info();
पूर्ण

/*
 * Save EDID inक्रमmation क्रम the kernel; this is invoked, separately,
 * after mode-setting.
 */
व्योम vesa_store_edid(व्योम)
अणु
#अगर_घोषित CONFIG_FIRMWARE_EDID
	काष्ठा biosregs ireg, oreg;

	/* Apparently used as a nonsense token... */
	स_रखो(&boot_params.edid_info, 0x13, माप(boot_params.edid_info));

	अगर (vginfo.version < 0x0200)
		वापस;		/* EDID requires VBE 2.0+ */

	initregs(&ireg);
	ireg.ax = 0x4f15;		/* VBE DDC */
	/* ireg.bx = 0x0000; */		/* Report DDC capabilities */
	/* ireg.cx = 0;	*/		/* Controller 0 */
	ireg.es = 0;			/* ES:DI must be 0 by spec */
	पूर्णांकcall(0x10, &ireg, &oreg);

	अगर (oreg.ax != 0x004f)
		वापस;		/* No EDID */

	/* BH = समय in seconds to transfer EDD inक्रमmation */
	/* BL = DDC level supported */

	ireg.ax = 0x4f15;		/* VBE DDC */
	ireg.bx = 0x0001;		/* Read EDID */
	/* ireg.cx = 0; */		/* Controller 0 */
	/* ireg.dx = 0;	*/		/* EDID block number */
	ireg.es = ds();
	ireg.di =(माप_प्रकार)&boot_params.edid_info; /* (ES:)Poपूर्णांकer to block */
	पूर्णांकcall(0x10, &ireg, &oreg);
#पूर्ण_अगर /* CONFIG_FIRMWARE_EDID */
पूर्ण

#पूर्ण_अगर /* not _WAKEUP */

अटल __videocard video_vesa =
अणु
	.card_name	= "VESA",
	.probe		= vesa_probe,
	.set_mode	= vesa_set_mode,
	.xmode_first	= VIDEO_FIRST_VESA,
	.xmode_n	= 0x200,
पूर्ण;
