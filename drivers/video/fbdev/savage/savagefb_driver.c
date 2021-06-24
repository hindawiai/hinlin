<शैली गुरु>
/*
 * linux/drivers/video/savagefb.c -- S3 Savage Framebuffer Driver
 *
 * Copyright (c) 2001-2002  Denis Oliver Kropp <करोk@directfb.org>
 *                          Sven Neumann <neo@directfb.org>
 *
 *
 * Card specअगरic code is based on XFree86's savage driver.
 * Framebuffer framework code is based on code of cyber2000fb and tdfxfb.
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file COPYING in the मुख्य directory of this
 * archive क्रम more details.
 *
 * 0.4.0 (neo)
 *  - hardware accelerated clear and move
 *
 * 0.3.2 (करोk)
 *  - रुको क्रम vertical retrace beक्रमe writing to cr67
 *    at the beginning of savagefb_set_par
 *  - use synchronization रेजिस्टरs cr23 and cr26
 *
 * 0.3.1 (करोk)
 *  - reset 3D engine
 *  - करोn't वापस alpha bits क्रम 32bit क्रमmat
 *
 * 0.3.0 (करोk)
 *  - added WaitIdle functions क्रम all Savage types
 *  - करो WaitIdle beक्रमe mode चयनing
 *  - code cleanup
 *
 * 0.2.0 (करोk)
 *  - first working version
 *
 *
 * TODO
 * - घड़ी validations in decode_var
 *
 * BUGS
 * - white margin on bootup
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/console.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>

#समावेश "savagefb.h"


#घोषणा SAVAGEFB_VERSION "0.4.0_2.6"

/* --------------------------------------------------------------------- */


अटल अक्षर *mode_option = शून्य;

#अगर_घोषित MODULE

MODULE_AUTHOR("(c) 2001-2002  Denis Oliver Kropp <dok@directfb.org>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("FBDev driver for S3 Savage PCI/AGP Chips");

#पूर्ण_अगर


/* --------------------------------------------------------------------- */

अटल व्योम vgaHWSeqReset(काष्ठा savagefb_par *par, पूर्णांक start)
अणु
	अगर (start)
		VGAwSEQ(0x00, 0x01, par);	/* Synchronous Reset */
	अन्यथा
		VGAwSEQ(0x00, 0x03, par);	/* End Reset */
पूर्ण

अटल व्योम vgaHWProtect(काष्ठा savagefb_par *par, पूर्णांक on)
अणु
	अचिन्हित अक्षर पंचांगp;

	अगर (on) अणु
		/*
		 * Turn off screen and disable sequencer.
		 */
		पंचांगp = VGArSEQ(0x01, par);

		vgaHWSeqReset(par, 1);	        /* start synchronous reset */
		VGAwSEQ(0x01, पंचांगp | 0x20, par);/* disable the display */

		VGAenablePalette(par);
	पूर्ण अन्यथा अणु
		/*
		 * Reenable sequencer, then turn on screen.
		 */

		पंचांगp = VGArSEQ(0x01, par);

		VGAwSEQ(0x01, पंचांगp & ~0x20, par);/* reenable display */
		vgaHWSeqReset(par, 0);	        /* clear synchronous reset */

		VGAdisablePalette(par);
	पूर्ण
पूर्ण

अटल व्योम vgaHWRestore(काष्ठा savagefb_par  *par, काष्ठा savage_reg *reg)
अणु
	पूर्णांक i;

	VGAwMISC(reg->MiscOutReg, par);

	क्रम (i = 1; i < 5; i++)
		VGAwSEQ(i, reg->Sequencer[i], par);

	/* Ensure CRTC रेजिस्टरs 0-7 are unlocked by clearing bit 7 or
	   CRTC[17] */
	VGAwCR(17, reg->CRTC[17] & ~0x80, par);

	क्रम (i = 0; i < 25; i++)
		VGAwCR(i, reg->CRTC[i], par);

	क्रम (i = 0; i < 9; i++)
		VGAwGR(i, reg->Graphics[i], par);

	VGAenablePalette(par);

	क्रम (i = 0; i < 21; i++)
		VGAwATTR(i, reg->Attribute[i], par);

	VGAdisablePalette(par);
पूर्ण

अटल व्योम vgaHWInit(काष्ठा fb_var_screeninfo *var,
		      काष्ठा savagefb_par            *par,
		      काष्ठा xtimings                *timings,
		      काष्ठा savage_reg              *reg)
अणु
	reg->MiscOutReg = 0x23;

	अगर (!(timings->sync & FB_SYNC_HOR_HIGH_ACT))
		reg->MiscOutReg |= 0x40;

	अगर (!(timings->sync & FB_SYNC_VERT_HIGH_ACT))
		reg->MiscOutReg |= 0x80;

	/*
	 * Time Sequencer
	 */
	reg->Sequencer[0x00] = 0x00;
	reg->Sequencer[0x01] = 0x01;
	reg->Sequencer[0x02] = 0x0F;
	reg->Sequencer[0x03] = 0x00;          /* Font select */
	reg->Sequencer[0x04] = 0x0E;          /* Misc */

	/*
	 * CRTC Controller
	 */
	reg->CRTC[0x00] = (timings->HTotal >> 3) - 5;
	reg->CRTC[0x01] = (timings->HDisplay >> 3) - 1;
	reg->CRTC[0x02] = (timings->HSyncStart >> 3) - 1;
	reg->CRTC[0x03] = (((timings->HSyncEnd >> 3)  - 1) & 0x1f) | 0x80;
	reg->CRTC[0x04] = (timings->HSyncStart >> 3);
	reg->CRTC[0x05] = ((((timings->HSyncEnd >> 3) - 1) & 0x20) << 2) |
		(((timings->HSyncEnd >> 3)) & 0x1f);
	reg->CRTC[0x06] = (timings->VTotal - 2) & 0xFF;
	reg->CRTC[0x07] = (((timings->VTotal - 2) & 0x100) >> 8) |
		(((timings->VDisplay - 1) & 0x100) >> 7) |
		((timings->VSyncStart & 0x100) >> 6) |
		(((timings->VSyncStart - 1) & 0x100) >> 5) |
		0x10 |
		(((timings->VTotal - 2) & 0x200) >> 4) |
		(((timings->VDisplay - 1) & 0x200) >> 3) |
		((timings->VSyncStart & 0x200) >> 2);
	reg->CRTC[0x08] = 0x00;
	reg->CRTC[0x09] = (((timings->VSyncStart - 1) & 0x200) >> 4) | 0x40;

	अगर (timings->dblscan)
		reg->CRTC[0x09] |= 0x80;

	reg->CRTC[0x0a] = 0x00;
	reg->CRTC[0x0b] = 0x00;
	reg->CRTC[0x0c] = 0x00;
	reg->CRTC[0x0d] = 0x00;
	reg->CRTC[0x0e] = 0x00;
	reg->CRTC[0x0f] = 0x00;
	reg->CRTC[0x10] = timings->VSyncStart & 0xff;
	reg->CRTC[0x11] = (timings->VSyncEnd & 0x0f) | 0x20;
	reg->CRTC[0x12] = (timings->VDisplay - 1) & 0xff;
	reg->CRTC[0x13] = var->xres_भव >> 4;
	reg->CRTC[0x14] = 0x00;
	reg->CRTC[0x15] = (timings->VSyncStart - 1) & 0xff;
	reg->CRTC[0x16] = (timings->VSyncEnd - 1) & 0xff;
	reg->CRTC[0x17] = 0xc3;
	reg->CRTC[0x18] = 0xff;

	/*
	 * are these unnecessary?
	 * vgaHWHBlankKGA(mode, regp, 0, KGA_FIX_OVERSCAN|KGA_ENABLE_ON_ZERO);
	 * vgaHWVBlankKGA(mode, regp, 0, KGA_FIX_OVERSCAN|KGA_ENABLE_ON_ZERO);
	 */

	/*
	 * Graphics Display Controller
	 */
	reg->Graphics[0x00] = 0x00;
	reg->Graphics[0x01] = 0x00;
	reg->Graphics[0x02] = 0x00;
	reg->Graphics[0x03] = 0x00;
	reg->Graphics[0x04] = 0x00;
	reg->Graphics[0x05] = 0x40;
	reg->Graphics[0x06] = 0x05;   /* only map 64k VGA memory !!!! */
	reg->Graphics[0x07] = 0x0F;
	reg->Graphics[0x08] = 0xFF;


	reg->Attribute[0x00]  = 0x00; /* standard colormap translation */
	reg->Attribute[0x01]  = 0x01;
	reg->Attribute[0x02]  = 0x02;
	reg->Attribute[0x03]  = 0x03;
	reg->Attribute[0x04]  = 0x04;
	reg->Attribute[0x05]  = 0x05;
	reg->Attribute[0x06]  = 0x06;
	reg->Attribute[0x07]  = 0x07;
	reg->Attribute[0x08]  = 0x08;
	reg->Attribute[0x09]  = 0x09;
	reg->Attribute[0x0a] = 0x0A;
	reg->Attribute[0x0b] = 0x0B;
	reg->Attribute[0x0c] = 0x0C;
	reg->Attribute[0x0d] = 0x0D;
	reg->Attribute[0x0e] = 0x0E;
	reg->Attribute[0x0f] = 0x0F;
	reg->Attribute[0x10] = 0x41;
	reg->Attribute[0x11] = 0xFF;
	reg->Attribute[0x12] = 0x0F;
	reg->Attribute[0x13] = 0x00;
	reg->Attribute[0x14] = 0x00;
पूर्ण

/* -------------------- Hardware specअगरic routines ------------------------- */

/*
 * Hardware Acceleration क्रम SavageFB
 */

/* Wait क्रम fअगरo space */
अटल व्योम
savage3D_रुकोfअगरo(काष्ठा savagefb_par *par, पूर्णांक space)
अणु
	पूर्णांक slots = MAXFIFO - space;

	जबतक ((savage_in32(0x48C00, par) & 0x0000ffff) > slots);
पूर्ण

अटल व्योम
savage4_रुकोfअगरo(काष्ठा savagefb_par *par, पूर्णांक space)
अणु
	पूर्णांक slots = MAXFIFO - space;

	जबतक ((savage_in32(0x48C60, par) & 0x001fffff) > slots);
पूर्ण

अटल व्योम
savage2000_रुकोfअगरo(काष्ठा savagefb_par *par, पूर्णांक space)
अणु
	पूर्णांक slots = MAXFIFO - space;

	जबतक ((savage_in32(0x48C60, par) & 0x0000ffff) > slots);
पूर्ण

/* Wait क्रम idle accelerator */
अटल व्योम
savage3D_रुकोidle(काष्ठा savagefb_par *par)
अणु
	जबतक ((savage_in32(0x48C00, par) & 0x0008ffff) != 0x80000);
पूर्ण

अटल व्योम
savage4_रुकोidle(काष्ठा savagefb_par *par)
अणु
	जबतक ((savage_in32(0x48C60, par) & 0x00a00000) != 0x00a00000);
पूर्ण

अटल व्योम
savage2000_रुकोidle(काष्ठा savagefb_par *par)
अणु
	जबतक ((savage_in32(0x48C60, par) & 0x009fffff));
पूर्ण

#अगर_घोषित CONFIG_FB_SAVAGE_ACCEL
अटल व्योम
SavageSetup2DEngine(काष्ठा savagefb_par  *par)
अणु
	अचिन्हित दीर्घ GlobalBiपंचांगapDescriptor;

	GlobalBiपंचांगapDescriptor = 1 | 8 | BCI_BD_BW_DISABLE;
	BCI_BD_SET_BPP(GlobalBiपंचांगapDescriptor, par->depth);
	BCI_BD_SET_STRIDE(GlobalBiपंचांगapDescriptor, par->vwidth);

	चयन(par->chip) अणु
	हाल S3_SAVAGE3D:
	हाल S3_SAVAGE_MX:
		/* Disable BCI */
		savage_out32(0x48C18, savage_in32(0x48C18, par) & 0x3FF0, par);
		/* Setup BCI command overflow buffer */
		savage_out32(0x48C14,
			     (par->cob_offset >> 11) | (par->cob_index << 29),
			     par);
		/* Program shaकरोw status update. */
		savage_out32(0x48C10, 0x78207220, par);
		savage_out32(0x48C0C, 0, par);
		/* Enable BCI and command overflow buffer */
		savage_out32(0x48C18, savage_in32(0x48C18, par) | 0x0C, par);
		अवरोध;
	हाल S3_SAVAGE4:
	हाल S3_TWISTER:
	हाल S3_PROSAVAGE:
	हाल S3_PROSAVAGEDDR:
	हाल S3_SUPERSAVAGE:
		/* Disable BCI */
		savage_out32(0x48C18, savage_in32(0x48C18, par) & 0x3FF0, par);
		/* Program shaकरोw status update */
		savage_out32(0x48C10, 0x00700040, par);
		savage_out32(0x48C0C, 0, par);
		/* Enable BCI without the COB */
		savage_out32(0x48C18, savage_in32(0x48C18, par) | 0x08, par);
		अवरोध;
	हाल S3_SAVAGE2000:
		/* Disable BCI */
		savage_out32(0x48C18, 0, par);
		/* Setup BCI command overflow buffer */
		savage_out32(0x48C18,
			     (par->cob_offset >> 7) | (par->cob_index),
			     par);
		/* Disable shaकरोw status update */
		savage_out32(0x48A30, 0, par);
		/* Enable BCI and command overflow buffer */
		savage_out32(0x48C18, savage_in32(0x48C18, par) | 0x00280000,
			     par);
		अवरोध;
	    शेष:
		अवरोध;
	पूर्ण
	/* Turn on 16-bit रेजिस्टर access. */
	vga_out8(0x3d4, 0x31, par);
	vga_out8(0x3d5, 0x0c, par);

	/* Set stride to use GBD. */
	vga_out8(0x3d4, 0x50, par);
	vga_out8(0x3d5, vga_in8(0x3d5, par) | 0xC1, par);

	/* Enable 2D engine. */
	vga_out8(0x3d4, 0x40, par);
	vga_out8(0x3d5, 0x01, par);

	savage_out32(MONO_PAT_0, ~0, par);
	savage_out32(MONO_PAT_1, ~0, par);

	/* Setup plane masks */
	savage_out32(0x8128, ~0, par); /* enable all ग_लिखो planes */
	savage_out32(0x812C, ~0, par); /* enable all पढ़ो planes */
	savage_out16(0x8134, 0x27, par);
	savage_out16(0x8136, 0x07, par);

	/* Now set the GBD */
	par->bci_ptr = 0;
	par->SavageWaitFअगरo(par, 4);

	BCI_SEND(BCI_CMD_SETREG | (1 << 16) | BCI_GBD1);
	BCI_SEND(0);
	BCI_SEND(BCI_CMD_SETREG | (1 << 16) | BCI_GBD2);
	BCI_SEND(GlobalBiपंचांगapDescriptor);

	/*
	 * I करोn't know why, sending this twice fixes the initial black screen,
	 * prevents X from crashing at least in Toshiba laptops with SavageIX.
	 * --Tony
	 */
	par->bci_ptr = 0;
	par->SavageWaitFअगरo(par, 4);

	BCI_SEND(BCI_CMD_SETREG | (1 << 16) | BCI_GBD1);
	BCI_SEND(0);
	BCI_SEND(BCI_CMD_SETREG | (1 << 16) | BCI_GBD2);
	BCI_SEND(GlobalBiपंचांगapDescriptor);
पूर्ण

अटल व्योम savagefb_set_clip(काष्ठा fb_info *info)
अणु
	काष्ठा savagefb_par *par = info->par;
	पूर्णांक cmd;

	cmd = BCI_CMD_NOP | BCI_CMD_CLIP_NEW;
	par->bci_ptr = 0;
	par->SavageWaitFअगरo(par,3);
	BCI_SEND(cmd);
	BCI_SEND(BCI_CLIP_TL(0, 0));
	BCI_SEND(BCI_CLIP_BR(0xfff, 0xfff));
पूर्ण
#अन्यथा
अटल व्योम SavageSetup2DEngine(काष्ठा savagefb_par  *par) अणुपूर्ण

#पूर्ण_अगर

अटल व्योम SavageCalcClock(दीर्घ freq, पूर्णांक min_m, पूर्णांक min_n1, पूर्णांक max_n1,
			    पूर्णांक min_n2, पूर्णांक max_n2, दीर्घ freq_min,
			    दीर्घ freq_max, अचिन्हित पूर्णांक *mभाग,
			    अचिन्हित पूर्णांक *nभाग, अचिन्हित पूर्णांक *r)
अणु
	दीर्घ dअगरf, best_dअगरf;
	अचिन्हित पूर्णांक m;
	अचिन्हित अक्षर n1, n2, best_n1=16+2, best_n2=2, best_m=125+2;

	अगर (freq < freq_min / (1 << max_n2)) अणु
		prपूर्णांकk(KERN_ERR "invalid frequency %ld Khz\n", freq);
		freq = freq_min / (1 << max_n2);
	पूर्ण
	अगर (freq > freq_max / (1 << min_n2)) अणु
		prपूर्णांकk(KERN_ERR "invalid frequency %ld Khz\n", freq);
		freq = freq_max / (1 << min_n2);
	पूर्ण

	/* work out suitable timings */
	best_dअगरf = freq;

	क्रम (n2=min_n2; n2<=max_n2; n2++) अणु
		क्रम (n1=min_n1+2; n1<=max_n1+2; n1++) अणु
			m = (freq * n1 * (1 << n2) + HALF_BASE_FREQ) /
				BASE_FREQ;
			अगर (m < min_m+2 || m > 127+2)
				जारी;
			अगर ((m * BASE_FREQ >= freq_min * n1) &&
			    (m * BASE_FREQ <= freq_max * n1)) अणु
				dअगरf = freq * (1 << n2) * n1 - BASE_FREQ * m;
				अगर (dअगरf < 0)
					dअगरf = -dअगरf;
				अगर (dअगरf < best_dअगरf) अणु
					best_dअगरf = dअगरf;
					best_m = m;
					best_n1 = n1;
					best_n2 = n2;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	*nभाग = best_n1 - 2;
	*r = best_n2;
	*mभाग = best_m - 2;
पूर्ण

अटल पूर्णांक common_calc_घड़ी(दीर्घ freq, पूर्णांक min_m, पूर्णांक min_n1, पूर्णांक max_n1,
			     पूर्णांक min_n2, पूर्णांक max_n2, दीर्घ freq_min,
			     दीर्घ freq_max, अचिन्हित अक्षर *mभाग,
			     अचिन्हित अक्षर *nभाग)
अणु
	दीर्घ dअगरf, best_dअगरf;
	अचिन्हित पूर्णांक m;
	अचिन्हित अक्षर n1, n2;
	अचिन्हित अक्षर best_n1 = 16+2, best_n2 = 2, best_m = 125+2;

	best_dअगरf = freq;

	क्रम (n2 = min_n2; n2 <= max_n2; n2++) अणु
		क्रम (n1 = min_n1+2; n1 <= max_n1+2; n1++) अणु
			m = (freq * n1 * (1 << n2) + HALF_BASE_FREQ) /
				BASE_FREQ;
			अगर (m < min_m + 2 || m > 127+2)
				जारी;
			अगर ((m * BASE_FREQ >= freq_min * n1) &&
			    (m * BASE_FREQ <= freq_max * n1)) अणु
				dअगरf = freq * (1 << n2) * n1 - BASE_FREQ * m;
				अगर (dअगरf < 0)
					dअगरf = -dअगरf;
				अगर (dअगरf < best_dअगरf) अणु
					best_dअगरf = dअगरf;
					best_m = m;
					best_n1 = n1;
					best_n2 = n2;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (max_n1 == 63)
		*nभाग = (best_n1 - 2) | (best_n2 << 6);
	अन्यथा
		*nभाग = (best_n1 - 2) | (best_n2 << 5);

	*mभाग = best_m - 2;

	वापस 0;
पूर्ण

#अगर_घोषित SAVAGEFB_DEBUG
/* This function is used to debug, it prपूर्णांकs out the contents of s3 regs */

अटल व्योम SavagePrपूर्णांकRegs(काष्ठा savagefb_par *par)
अणु
	अचिन्हित अक्षर i;
	पूर्णांक vgaCRIndex = 0x3d4;
	पूर्णांक vgaCRReg = 0x3d5;

	prपूर्णांकk(KERN_DEBUG "SR    x0 x1 x2 x3 x4 x5 x6 x7 x8 x9 xA xB xC xD xE "
	       "xF");

	क्रम (i = 0; i < 0x70; i++) अणु
		अगर (!(i % 16))
			prपूर्णांकk(KERN_DEBUG "\nSR%xx ", i >> 4);
		vga_out8(0x3c4, i, par);
		prपूर्णांकk(KERN_DEBUG " %02x", vga_in8(0x3c5, par));
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "\n\nCR    x0 x1 x2 x3 x4 x5 x6 x7 x8 x9 xA xB xC "
	       "xD xE xF");

	क्रम (i = 0; i < 0xB7; i++) अणु
		अगर (!(i % 16))
			prपूर्णांकk(KERN_DEBUG "\nCR%xx ", i >> 4);
		vga_out8(vgaCRIndex, i, par);
		prपूर्णांकk(KERN_DEBUG " %02x", vga_in8(vgaCRReg, par));
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "\n\n");
पूर्ण
#पूर्ण_अगर

/* --------------------------------------------------------------------- */

अटल व्योम savage_get_शेष_par(काष्ठा savagefb_par *par, काष्ठा savage_reg *reg)
अणु
	अचिन्हित अक्षर cr3a, cr53, cr66;

	vga_out16(0x3d4, 0x4838, par);
	vga_out16(0x3d4, 0xa039, par);
	vga_out16(0x3c4, 0x0608, par);

	vga_out8(0x3d4, 0x66, par);
	cr66 = vga_in8(0x3d5, par);
	vga_out8(0x3d5, cr66 | 0x80, par);
	vga_out8(0x3d4, 0x3a, par);
	cr3a = vga_in8(0x3d5, par);
	vga_out8(0x3d5, cr3a | 0x80, par);
	vga_out8(0x3d4, 0x53, par);
	cr53 = vga_in8(0x3d5, par);
	vga_out8(0x3d5, cr53 & 0x7f, par);

	vga_out8(0x3d4, 0x66, par);
	vga_out8(0x3d5, cr66, par);
	vga_out8(0x3d4, 0x3a, par);
	vga_out8(0x3d5, cr3a, par);

	vga_out8(0x3d4, 0x66, par);
	vga_out8(0x3d5, cr66, par);
	vga_out8(0x3d4, 0x3a, par);
	vga_out8(0x3d5, cr3a, par);

	/* unlock extended seq regs */
	vga_out8(0x3c4, 0x08, par);
	reg->SR08 = vga_in8(0x3c5, par);
	vga_out8(0x3c5, 0x06, par);

	/* now save all the extended regs we need */
	vga_out8(0x3d4, 0x31, par);
	reg->CR31 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x32, par);
	reg->CR32 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x34, par);
	reg->CR34 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x36, par);
	reg->CR36 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x3a, par);
	reg->CR3A = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x40, par);
	reg->CR40 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x42, par);
	reg->CR42 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x45, par);
	reg->CR45 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x50, par);
	reg->CR50 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x51, par);
	reg->CR51 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x53, par);
	reg->CR53 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x58, par);
	reg->CR58 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x60, par);
	reg->CR60 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x66, par);
	reg->CR66 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x67, par);
	reg->CR67 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x68, par);
	reg->CR68 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x69, par);
	reg->CR69 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x6f, par);
	reg->CR6F = vga_in8(0x3d5, par);

	vga_out8(0x3d4, 0x33, par);
	reg->CR33 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x86, par);
	reg->CR86 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x88, par);
	reg->CR88 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x90, par);
	reg->CR90 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x91, par);
	reg->CR91 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0xb0, par);
	reg->CRB0 = vga_in8(0x3d5, par) | 0x80;

	/* extended mode timing regs */
	vga_out8(0x3d4, 0x3b, par);
	reg->CR3B = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x3c, par);
	reg->CR3C = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x43, par);
	reg->CR43 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x5d, par);
	reg->CR5D = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x5e, par);
	reg->CR5E = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x65, par);
	reg->CR65 = vga_in8(0x3d5, par);

	/* save seq extended regs क्रम DCLK PLL programming */
	vga_out8(0x3c4, 0x0e, par);
	reg->SR0E = vga_in8(0x3c5, par);
	vga_out8(0x3c4, 0x0f, par);
	reg->SR0F = vga_in8(0x3c5, par);
	vga_out8(0x3c4, 0x10, par);
	reg->SR10 = vga_in8(0x3c5, par);
	vga_out8(0x3c4, 0x11, par);
	reg->SR11 = vga_in8(0x3c5, par);
	vga_out8(0x3c4, 0x12, par);
	reg->SR12 = vga_in8(0x3c5, par);
	vga_out8(0x3c4, 0x13, par);
	reg->SR13 = vga_in8(0x3c5, par);
	vga_out8(0x3c4, 0x29, par);
	reg->SR29 = vga_in8(0x3c5, par);

	vga_out8(0x3c4, 0x15, par);
	reg->SR15 = vga_in8(0x3c5, par);
	vga_out8(0x3c4, 0x30, par);
	reg->SR30 = vga_in8(0x3c5, par);
	vga_out8(0x3c4, 0x18, par);
	reg->SR18 = vga_in8(0x3c5, par);

	/* Save flat panel expansion रेजिस्टरs. */
	अगर (par->chip == S3_SAVAGE_MX) अणु
		पूर्णांक i;

		क्रम (i = 0; i < 8; i++) अणु
			vga_out8(0x3c4, 0x54+i, par);
			reg->SR54[i] = vga_in8(0x3c5, par);
		पूर्ण
	पूर्ण

	vga_out8(0x3d4, 0x66, par);
	cr66 = vga_in8(0x3d5, par);
	vga_out8(0x3d5, cr66 | 0x80, par);
	vga_out8(0x3d4, 0x3a, par);
	cr3a = vga_in8(0x3d5, par);
	vga_out8(0x3d5, cr3a | 0x80, par);

	/* now save MIU regs */
	अगर (par->chip != S3_SAVAGE_MX) अणु
		reg->MMPR0 = savage_in32(FIFO_CONTROL_REG, par);
		reg->MMPR1 = savage_in32(MIU_CONTROL_REG, par);
		reg->MMPR2 = savage_in32(STREAMS_TIMEOUT_REG, par);
		reg->MMPR3 = savage_in32(MISC_TIMEOUT_REG, par);
	पूर्ण

	vga_out8(0x3d4, 0x3a, par);
	vga_out8(0x3d5, cr3a, par);
	vga_out8(0x3d4, 0x66, par);
	vga_out8(0x3d5, cr66, par);
पूर्ण

अटल व्योम savage_set_शेष_par(काष्ठा savagefb_par *par,
				काष्ठा savage_reg *reg)
अणु
	अचिन्हित अक्षर cr3a, cr53, cr66;

	vga_out16(0x3d4, 0x4838, par);
	vga_out16(0x3d4, 0xa039, par);
	vga_out16(0x3c4, 0x0608, par);

	vga_out8(0x3d4, 0x66, par);
	cr66 = vga_in8(0x3d5, par);
	vga_out8(0x3d5, cr66 | 0x80, par);
	vga_out8(0x3d4, 0x3a, par);
	cr3a = vga_in8(0x3d5, par);
	vga_out8(0x3d5, cr3a | 0x80, par);
	vga_out8(0x3d4, 0x53, par);
	cr53 = vga_in8(0x3d5, par);
	vga_out8(0x3d5, cr53 & 0x7f, par);

	vga_out8(0x3d4, 0x66, par);
	vga_out8(0x3d5, cr66, par);
	vga_out8(0x3d4, 0x3a, par);
	vga_out8(0x3d5, cr3a, par);

	vga_out8(0x3d4, 0x66, par);
	vga_out8(0x3d5, cr66, par);
	vga_out8(0x3d4, 0x3a, par);
	vga_out8(0x3d5, cr3a, par);

	/* unlock extended seq regs */
	vga_out8(0x3c4, 0x08, par);
	vga_out8(0x3c5, reg->SR08, par);
	vga_out8(0x3c5, 0x06, par);

	/* now restore all the extended regs we need */
	vga_out8(0x3d4, 0x31, par);
	vga_out8(0x3d5, reg->CR31, par);
	vga_out8(0x3d4, 0x32, par);
	vga_out8(0x3d5, reg->CR32, par);
	vga_out8(0x3d4, 0x34, par);
	vga_out8(0x3d5, reg->CR34, par);
	vga_out8(0x3d4, 0x36, par);
	vga_out8(0x3d5,reg->CR36, par);
	vga_out8(0x3d4, 0x3a, par);
	vga_out8(0x3d5, reg->CR3A, par);
	vga_out8(0x3d4, 0x40, par);
	vga_out8(0x3d5, reg->CR40, par);
	vga_out8(0x3d4, 0x42, par);
	vga_out8(0x3d5, reg->CR42, par);
	vga_out8(0x3d4, 0x45, par);
	vga_out8(0x3d5, reg->CR45, par);
	vga_out8(0x3d4, 0x50, par);
	vga_out8(0x3d5, reg->CR50, par);
	vga_out8(0x3d4, 0x51, par);
	vga_out8(0x3d5, reg->CR51, par);
	vga_out8(0x3d4, 0x53, par);
	vga_out8(0x3d5, reg->CR53, par);
	vga_out8(0x3d4, 0x58, par);
	vga_out8(0x3d5, reg->CR58, par);
	vga_out8(0x3d4, 0x60, par);
	vga_out8(0x3d5, reg->CR60, par);
	vga_out8(0x3d4, 0x66, par);
	vga_out8(0x3d5, reg->CR66, par);
	vga_out8(0x3d4, 0x67, par);
	vga_out8(0x3d5, reg->CR67, par);
	vga_out8(0x3d4, 0x68, par);
	vga_out8(0x3d5, reg->CR68, par);
	vga_out8(0x3d4, 0x69, par);
	vga_out8(0x3d5, reg->CR69, par);
	vga_out8(0x3d4, 0x6f, par);
	vga_out8(0x3d5, reg->CR6F, par);

	vga_out8(0x3d4, 0x33, par);
	vga_out8(0x3d5, reg->CR33, par);
	vga_out8(0x3d4, 0x86, par);
	vga_out8(0x3d5, reg->CR86, par);
	vga_out8(0x3d4, 0x88, par);
	vga_out8(0x3d5, reg->CR88, par);
	vga_out8(0x3d4, 0x90, par);
	vga_out8(0x3d5, reg->CR90, par);
	vga_out8(0x3d4, 0x91, par);
	vga_out8(0x3d5, reg->CR91, par);
	vga_out8(0x3d4, 0xb0, par);
	vga_out8(0x3d5, reg->CRB0, par);

	/* extended mode timing regs */
	vga_out8(0x3d4, 0x3b, par);
	vga_out8(0x3d5, reg->CR3B, par);
	vga_out8(0x3d4, 0x3c, par);
	vga_out8(0x3d5, reg->CR3C, par);
	vga_out8(0x3d4, 0x43, par);
	vga_out8(0x3d5, reg->CR43, par);
	vga_out8(0x3d4, 0x5d, par);
	vga_out8(0x3d5, reg->CR5D, par);
	vga_out8(0x3d4, 0x5e, par);
	vga_out8(0x3d5, reg->CR5E, par);
	vga_out8(0x3d4, 0x65, par);
	vga_out8(0x3d5, reg->CR65, par);

	/* save seq extended regs क्रम DCLK PLL programming */
	vga_out8(0x3c4, 0x0e, par);
	vga_out8(0x3c5, reg->SR0E, par);
	vga_out8(0x3c4, 0x0f, par);
	vga_out8(0x3c5, reg->SR0F, par);
	vga_out8(0x3c4, 0x10, par);
	vga_out8(0x3c5, reg->SR10, par);
	vga_out8(0x3c4, 0x11, par);
	vga_out8(0x3c5, reg->SR11, par);
	vga_out8(0x3c4, 0x12, par);
	vga_out8(0x3c5, reg->SR12, par);
	vga_out8(0x3c4, 0x13, par);
	vga_out8(0x3c5, reg->SR13, par);
	vga_out8(0x3c4, 0x29, par);
	vga_out8(0x3c5, reg->SR29, par);

	vga_out8(0x3c4, 0x15, par);
	vga_out8(0x3c5, reg->SR15, par);
	vga_out8(0x3c4, 0x30, par);
	vga_out8(0x3c5, reg->SR30, par);
	vga_out8(0x3c4, 0x18, par);
	vga_out8(0x3c5, reg->SR18, par);

	/* Save flat panel expansion रेजिस्टरs. */
	अगर (par->chip == S3_SAVAGE_MX) अणु
		पूर्णांक i;

		क्रम (i = 0; i < 8; i++) अणु
			vga_out8(0x3c4, 0x54+i, par);
			vga_out8(0x3c5, reg->SR54[i], par);
		पूर्ण
	पूर्ण

	vga_out8(0x3d4, 0x66, par);
	cr66 = vga_in8(0x3d5, par);
	vga_out8(0x3d5, cr66 | 0x80, par);
	vga_out8(0x3d4, 0x3a, par);
	cr3a = vga_in8(0x3d5, par);
	vga_out8(0x3d5, cr3a | 0x80, par);

	/* now save MIU regs */
	अगर (par->chip != S3_SAVAGE_MX) अणु
		savage_out32(FIFO_CONTROL_REG, reg->MMPR0, par);
		savage_out32(MIU_CONTROL_REG, reg->MMPR1, par);
		savage_out32(STREAMS_TIMEOUT_REG, reg->MMPR2, par);
		savage_out32(MISC_TIMEOUT_REG, reg->MMPR3, par);
	पूर्ण

	vga_out8(0x3d4, 0x3a, par);
	vga_out8(0x3d5, cr3a, par);
	vga_out8(0x3d4, 0x66, par);
	vga_out8(0x3d5, cr66, par);
पूर्ण

अटल व्योम savage_update_var(काष्ठा fb_var_screeninfo *var,
			      स्थिर काष्ठा fb_videomode *modedb)
अणु
	var->xres = var->xres_भव = modedb->xres;
	var->yres = modedb->yres;
        अगर (var->yres_भव < var->yres)
	    var->yres_भव = var->yres;
        var->xoffset = var->yoffset = 0;
        var->pixघड़ी = modedb->pixघड़ी;
        var->left_margin = modedb->left_margin;
        var->right_margin = modedb->right_margin;
        var->upper_margin = modedb->upper_margin;
        var->lower_margin = modedb->lower_margin;
        var->hsync_len = modedb->hsync_len;
        var->vsync_len = modedb->vsync_len;
        var->sync = modedb->sync;
        var->vmode = modedb->vmode;
पूर्ण

अटल पूर्णांक savagefb_check_var(काष्ठा fb_var_screeninfo   *var,
			      काष्ठा fb_info *info)
अणु
	काष्ठा savagefb_par *par = info->par;
	पूर्णांक memlen, vramlen, mode_valid = 0;

	DBG("savagefb_check_var");

	var->transp.offset = 0;
	var->transp.length = 0;
	चयन (var->bits_per_pixel) अणु
	हाल 8:
		var->red.offset = var->green.offset =
			var->blue.offset = 0;
		var->red.length = var->green.length =
			var->blue.length = var->bits_per_pixel;
		अवरोध;
	हाल 16:
		var->red.offset = 11;
		var->red.length = 5;
		var->green.offset = 5;
		var->green.length = 6;
		var->blue.offset = 0;
		var->blue.length = 5;
		अवरोध;
	हाल 32:
		var->transp.offset = 24;
		var->transp.length = 8;
		var->red.offset = 16;
		var->red.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!info->monspecs.hfmax || !info->monspecs.vfmax ||
	    !info->monspecs.dclkmax || !fb_validate_mode(var, info))
		mode_valid = 1;

	/* calculate modeline अगर supported by monitor */
	अगर (!mode_valid && info->monspecs.gtf) अणु
		अगर (!fb_get_mode(FB_MAXTIMINGS, 0, var, info))
			mode_valid = 1;
	पूर्ण

	अगर (!mode_valid) अणु
		स्थिर काष्ठा fb_videomode *mode;

		mode = fb_find_best_mode(var, &info->modelist);
		अगर (mode) अणु
			savage_update_var(var, mode);
			mode_valid = 1;
		पूर्ण
	पूर्ण

	अगर (!mode_valid && info->monspecs.modedb_len)
		वापस -EINVAL;

	/* Is the mode larger than the LCD panel? */
	अगर (par->SavagePanelWidth &&
	    (var->xres > par->SavagePanelWidth ||
	     var->yres > par->SavagePanelHeight)) अणु
		prपूर्णांकk(KERN_INFO "Mode (%dx%d) larger than the LCD panel "
		       "(%dx%d)\n", var->xres,  var->yres,
		       par->SavagePanelWidth,
		       par->SavagePanelHeight);
		वापस -1;
	पूर्ण

	अगर (var->yres_भव < var->yres)
		var->yres_भव = var->yres;
	अगर (var->xres_भव < var->xres)
		var->xres_भव = var->xres;

	vramlen = info->fix.smem_len;

	memlen = var->xres_भव * var->bits_per_pixel *
		var->yres_भव / 8;
	अगर (memlen > vramlen) अणु
		var->yres_भव = vramlen * 8 /
			(var->xres_भव * var->bits_per_pixel);
		memlen = var->xres_भव * var->bits_per_pixel *
			var->yres_भव / 8;
	पूर्ण

	/* we must round yres/xres करोwn, we alपढ़ोy rounded y/xres_भव up
	   अगर it was possible. We should वापस -EINVAL, but I disagree */
	अगर (var->yres_भव < var->yres)
		var->yres = var->yres_भव;
	अगर (var->xres_भव < var->xres)
		var->xres = var->xres_भव;
	अगर (var->xoffset + var->xres > var->xres_भव)
		var->xoffset = var->xres_भव - var->xres;
	अगर (var->yoffset + var->yres > var->yres_भव)
		var->yoffset = var->yres_भव - var->yres;

	वापस 0;
पूर्ण


अटल पूर्णांक savagefb_decode_var(काष्ठा fb_var_screeninfo   *var,
			       काष्ठा savagefb_par        *par,
			       काष्ठा savage_reg          *reg)
अणु
	काष्ठा xtimings timings;
	पूर्णांक width, dclk, i, j; /*, refresh; */
	अचिन्हित पूर्णांक m, n, r;
	अचिन्हित अक्षर पंचांगp = 0;
	अचिन्हित पूर्णांक pixघड़ी = var->pixघड़ी;

	DBG("savagefb_decode_var");

	स_रखो(&timings, 0, माप(timings));

	अगर (!pixघड़ी) pixघड़ी = 10000;	/* 10ns = 100MHz */
	timings.Clock = 1000000000 / pixघड़ी;
	अगर (timings.Clock < 1) timings.Clock = 1;
	timings.dblscan = var->vmode & FB_VMODE_DOUBLE;
	timings.पूर्णांकerlaced = var->vmode & FB_VMODE_INTERLACED;
	timings.HDisplay = var->xres;
	timings.HSyncStart = timings.HDisplay + var->right_margin;
	timings.HSyncEnd = timings.HSyncStart + var->hsync_len;
	timings.HTotal = timings.HSyncEnd + var->left_margin;
	timings.VDisplay = var->yres;
	timings.VSyncStart = timings.VDisplay + var->lower_margin;
	timings.VSyncEnd = timings.VSyncStart + var->vsync_len;
	timings.VTotal = timings.VSyncEnd + var->upper_margin;
	timings.sync = var->sync;


	par->depth  = var->bits_per_pixel;
	par->vwidth = var->xres_भव;

	अगर (var->bits_per_pixel == 16  &&  par->chip == S3_SAVAGE3D) अणु
		timings.HDisplay *= 2;
		timings.HSyncStart *= 2;
		timings.HSyncEnd *= 2;
		timings.HTotal *= 2;
	पूर्ण

	/*
	 * This will allocate the dataकाष्ठाure and initialize all of the
	 * generic VGA रेजिस्टरs.
	 */
	vgaHWInit(var, par, &timings, reg);

	/* We need to set CR67 whether or not we use the BIOS. */

	dclk = timings.Clock;
	reg->CR67 = 0x00;

	चयन(var->bits_per_pixel) अणु
	हाल 8:
		अगर ((par->chip == S3_SAVAGE2000) && (dclk >= 230000))
			reg->CR67 = 0x10;	/* 8bpp, 2 pixels/घड़ी */
		अन्यथा
			reg->CR67 = 0x00;	/* 8bpp, 1 pixel/घड़ी */
		अवरोध;
	हाल 15:
		अगर (S3_SAVAGE_MOBILE_SERIES(par->chip) ||
		    ((par->chip == S3_SAVAGE2000) && (dclk >= 230000)))
			reg->CR67 = 0x30;	/* 15bpp, 2 pixel/घड़ी */
		अन्यथा
			reg->CR67 = 0x20;	/* 15bpp, 1 pixels/घड़ी */
		अवरोध;
	हाल 16:
		अगर (S3_SAVAGE_MOBILE_SERIES(par->chip) ||
		   ((par->chip == S3_SAVAGE2000) && (dclk >= 230000)))
			reg->CR67 = 0x50;	/* 16bpp, 2 pixel/घड़ी */
		अन्यथा
			reg->CR67 = 0x40;	/* 16bpp, 1 pixels/घड़ी */
		अवरोध;
	हाल 24:
		reg->CR67 = 0x70;
		अवरोध;
	हाल 32:
		reg->CR67 = 0xd0;
		अवरोध;
	पूर्ण

	/*
	 * Either BIOS use is disabled, or we failed to find a suitable
	 * match.  Fall back to traditional रेजिस्टर-crunching.
	 */

	vga_out8(0x3d4, 0x3a, par);
	पंचांगp = vga_in8(0x3d5, par);
	अगर (1 /*FIXME:psav->pci_burst*/)
		reg->CR3A = (पंचांगp & 0x7f) | 0x15;
	अन्यथा
		reg->CR3A = पंचांगp | 0x95;

	reg->CR53 = 0x00;
	reg->CR31 = 0x8c;
	reg->CR66 = 0x89;

	vga_out8(0x3d4, 0x58, par);
	reg->CR58 = vga_in8(0x3d5, par) & 0x80;
	reg->CR58 |= 0x13;

	reg->SR15 = 0x03 | 0x80;
	reg->SR18 = 0x00;
	reg->CR43 = reg->CR45 = reg->CR65 = 0x00;

	vga_out8(0x3d4, 0x40, par);
	reg->CR40 = vga_in8(0x3d5, par) & ~0x01;

	reg->MMPR0 = 0x010400;
	reg->MMPR1 = 0x00;
	reg->MMPR2 = 0x0808;
	reg->MMPR3 = 0x08080810;

	SavageCalcClock(dclk, 1, 1, 127, 0, 4, 180000, 360000, &m, &n, &r);
	/* m = 107; n = 4; r = 2; */

	अगर (par->MCLK <= 0) अणु
		reg->SR10 = 255;
		reg->SR11 = 255;
	पूर्ण अन्यथा अणु
		common_calc_घड़ी(par->MCLK, 1, 1, 31, 0, 3, 135000, 270000,
				   &reg->SR11, &reg->SR10);
		/*      reg->SR10 = 80; // MCLK == 286000 */
		/*      reg->SR11 = 125; */
	पूर्ण

	reg->SR12 = (r << 6) | (n & 0x3f);
	reg->SR13 = m & 0xff;
	reg->SR29 = (r & 4) | (m & 0x100) >> 5 | (n & 0x40) >> 2;

	अगर (var->bits_per_pixel < 24)
		reg->MMPR0 -= 0x8000;
	अन्यथा
		reg->MMPR0 -= 0x4000;

	अगर (timings.पूर्णांकerlaced)
		reg->CR42 = 0x20;
	अन्यथा
		reg->CR42 = 0x00;

	reg->CR34 = 0x10; /* display fअगरo */

	i = ((((timings.HTotal >> 3) - 5) & 0x100) >> 8) |
		((((timings.HDisplay >> 3) - 1) & 0x100) >> 7) |
		((((timings.HSyncStart >> 3) - 1) & 0x100) >> 6) |
		((timings.HSyncStart & 0x800) >> 7);

	अगर ((timings.HSyncEnd >> 3) - (timings.HSyncStart >> 3) > 64)
		i |= 0x08;
	अगर ((timings.HSyncEnd >> 3) - (timings.HSyncStart >> 3) > 32)
		i |= 0x20;

	j = (reg->CRTC[0] + ((i & 0x01) << 8) +
	     reg->CRTC[4] + ((i & 0x10) << 4) + 1) / 2;

	अगर (j - (reg->CRTC[4] + ((i & 0x10) << 4)) < 4) अणु
		अगर (reg->CRTC[4] + ((i & 0x10) << 4) + 4 <=
		    reg->CRTC[0] + ((i & 0x01) << 8))
			j = reg->CRTC[4] + ((i & 0x10) << 4) + 4;
		अन्यथा
			j = reg->CRTC[0] + ((i & 0x01) << 8) + 1;
	पूर्ण

	reg->CR3B = j & 0xff;
	i |= (j & 0x100) >> 2;
	reg->CR3C = (reg->CRTC[0] + ((i & 0x01) << 8)) / 2;
	reg->CR5D = i;
	reg->CR5E = (((timings.VTotal - 2) & 0x400) >> 10) |
		(((timings.VDisplay - 1) & 0x400) >> 9) |
		(((timings.VSyncStart) & 0x400) >> 8) |
		(((timings.VSyncStart) & 0x400) >> 6) | 0x40;
	width = (var->xres_भव * ((var->bits_per_pixel+7) / 8)) >> 3;
	reg->CR91 = reg->CRTC[19] = 0xff & width;
	reg->CR51 = (0x300 & width) >> 4;
	reg->CR90 = 0x80 | (width >> 8);
	reg->MiscOutReg |= 0x0c;

	/* Set frame buffer description. */

	अगर (var->bits_per_pixel <= 8)
		reg->CR50 = 0;
	अन्यथा अगर (var->bits_per_pixel <= 16)
		reg->CR50 = 0x10;
	अन्यथा
		reg->CR50 = 0x30;

	अगर (var->xres_भव <= 640)
		reg->CR50 |= 0x40;
	अन्यथा अगर (var->xres_भव == 800)
		reg->CR50 |= 0x80;
	अन्यथा अगर (var->xres_भव == 1024)
		reg->CR50 |= 0x00;
	अन्यथा अगर (var->xres_भव == 1152)
		reg->CR50 |= 0x01;
	अन्यथा अगर (var->xres_भव == 1280)
		reg->CR50 |= 0xc0;
	अन्यथा अगर (var->xres_भव == 1600)
		reg->CR50 |= 0x81;
	अन्यथा
		reg->CR50 |= 0xc1;	/* Use GBD */

	अगर (par->chip == S3_SAVAGE2000)
		reg->CR33 = 0x08;
	अन्यथा
		reg->CR33 = 0x20;

	reg->CRTC[0x17] = 0xeb;

	reg->CR67 |= 1;

	vga_out8(0x3d4, 0x36, par);
	reg->CR36 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x68, par);
	reg->CR68 = vga_in8(0x3d5, par);
	reg->CR69 = 0;
	vga_out8(0x3d4, 0x6f, par);
	reg->CR6F = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x86, par);
	reg->CR86 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x88, par);
	reg->CR88 = vga_in8(0x3d5, par) | 0x08;
	vga_out8(0x3d4, 0xb0, par);
	reg->CRB0 = vga_in8(0x3d5, par) | 0x80;

	वापस 0;
पूर्ण

/* --------------------------------------------------------------------- */

/*
 *    Set a single color रेजिस्टर. Return != 0 क्रम invalid regno.
 */
अटल पूर्णांक savagefb_setcolreg(अचिन्हित        regno,
			      अचिन्हित        red,
			      अचिन्हित        green,
			      अचिन्हित        blue,
			      अचिन्हित        transp,
			      काष्ठा fb_info *info)
अणु
	काष्ठा savagefb_par *par = info->par;

	अगर (regno >= NR_PALETTE)
		वापस -EINVAL;

	par->palette[regno].red    = red;
	par->palette[regno].green  = green;
	par->palette[regno].blue   = blue;
	par->palette[regno].transp = transp;

	चयन (info->var.bits_per_pixel) अणु
	हाल 8:
		vga_out8(0x3c8, regno, par);

		vga_out8(0x3c9, red   >> 10, par);
		vga_out8(0x3c9, green >> 10, par);
		vga_out8(0x3c9, blue  >> 10, par);
		अवरोध;

	हाल 16:
		अगर (regno < 16)
			((u32 *)info->pseuकरो_palette)[regno] =
				((red   & 0xf800)      ) |
				((green & 0xfc00) >>  5) |
				((blue  & 0xf800) >> 11);
		अवरोध;

	हाल 24:
		अगर (regno < 16)
			((u32 *)info->pseuकरो_palette)[regno] =
				((red    & 0xff00) <<  8) |
				((green  & 0xff00)      ) |
				((blue   & 0xff00) >>  8);
		अवरोध;
	हाल 32:
		अगर (regno < 16)
			((u32 *)info->pseuकरो_palette)[regno] =
				((transp & 0xff00) << 16) |
				((red    & 0xff00) <<  8) |
				((green  & 0xff00)      ) |
				((blue   & 0xff00) >>  8);
		अवरोध;

	शेष:
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम savagefb_set_par_पूर्णांक(काष्ठा savagefb_par  *par, काष्ठा savage_reg *reg)
अणु
	अचिन्हित अक्षर पंचांगp, cr3a, cr66, cr67;

	DBG("savagefb_set_par_int");

	par->SavageWaitIdle(par);

	vga_out8(0x3c2, 0x23, par);

	vga_out16(0x3d4, 0x4838, par);
	vga_out16(0x3d4, 0xa539, par);
	vga_out16(0x3c4, 0x0608, par);

	vgaHWProtect(par, 1);

	/*
	 * Some Savage/MX and /IX प्रणालीs go nuts when trying to निकास the
	 * server after WinकरोwMaker has displayed a gradient background.  I
	 * haven't been able to find what causes it, but a non-deकाष्ठाive
	 * चयन to mode 3 here seems to eliminate the issue.
	 */

	VerticalRetraceWait(par);
	vga_out8(0x3d4, 0x67, par);
	cr67 = vga_in8(0x3d5, par);
	vga_out8(0x3d5, cr67/*par->CR67*/ & ~0x0c, par); /* no STREAMS yet */

	vga_out8(0x3d4, 0x23, par);
	vga_out8(0x3d5, 0x00, par);
	vga_out8(0x3d4, 0x26, par);
	vga_out8(0x3d5, 0x00, par);

	/* restore extended regs */
	vga_out8(0x3d4, 0x66, par);
	vga_out8(0x3d5, reg->CR66, par);
	vga_out8(0x3d4, 0x3a, par);
	vga_out8(0x3d5, reg->CR3A, par);
	vga_out8(0x3d4, 0x31, par);
	vga_out8(0x3d5, reg->CR31, par);
	vga_out8(0x3d4, 0x32, par);
	vga_out8(0x3d5, reg->CR32, par);
	vga_out8(0x3d4, 0x58, par);
	vga_out8(0x3d5, reg->CR58, par);
	vga_out8(0x3d4, 0x53, par);
	vga_out8(0x3d5, reg->CR53 & 0x7f, par);

	vga_out16(0x3c4, 0x0608, par);

	/* Restore DCLK रेजिस्टरs. */

	vga_out8(0x3c4, 0x0e, par);
	vga_out8(0x3c5, reg->SR0E, par);
	vga_out8(0x3c4, 0x0f, par);
	vga_out8(0x3c5, reg->SR0F, par);
	vga_out8(0x3c4, 0x29, par);
	vga_out8(0x3c5, reg->SR29, par);
	vga_out8(0x3c4, 0x15, par);
	vga_out8(0x3c5, reg->SR15, par);

	/* Restore flat panel expansion रेजिस्टरs. */
	अगर (par->chip == S3_SAVAGE_MX) अणु
		पूर्णांक i;

		क्रम (i = 0; i < 8; i++) अणु
			vga_out8(0x3c4, 0x54+i, par);
			vga_out8(0x3c5, reg->SR54[i], par);
		पूर्ण
	पूर्ण

	vgaHWRestore (par, reg);

	/* extended mode timing रेजिस्टरs */
	vga_out8(0x3d4, 0x53, par);
	vga_out8(0x3d5, reg->CR53, par);
	vga_out8(0x3d4, 0x5d, par);
	vga_out8(0x3d5, reg->CR5D, par);
	vga_out8(0x3d4, 0x5e, par);
	vga_out8(0x3d5, reg->CR5E, par);
	vga_out8(0x3d4, 0x3b, par);
	vga_out8(0x3d5, reg->CR3B, par);
	vga_out8(0x3d4, 0x3c, par);
	vga_out8(0x3d5, reg->CR3C, par);
	vga_out8(0x3d4, 0x43, par);
	vga_out8(0x3d5, reg->CR43, par);
	vga_out8(0x3d4, 0x65, par);
	vga_out8(0x3d5, reg->CR65, par);

	/* restore the desired video mode with cr67 */
	vga_out8(0x3d4, 0x67, par);
	/* following part not present in X11 driver */
	cr67 = vga_in8(0x3d5, par) & 0xf;
	vga_out8(0x3d5, 0x50 | cr67, par);
	mdelay(10);
	vga_out8(0x3d4, 0x67, par);
	/* end of part */
	vga_out8(0x3d5, reg->CR67 & ~0x0c, par);

	/* other mode timing and extended regs */
	vga_out8(0x3d4, 0x34, par);
	vga_out8(0x3d5, reg->CR34, par);
	vga_out8(0x3d4, 0x40, par);
	vga_out8(0x3d5, reg->CR40, par);
	vga_out8(0x3d4, 0x42, par);
	vga_out8(0x3d5, reg->CR42, par);
	vga_out8(0x3d4, 0x45, par);
	vga_out8(0x3d5, reg->CR45, par);
	vga_out8(0x3d4, 0x50, par);
	vga_out8(0x3d5, reg->CR50, par);
	vga_out8(0x3d4, 0x51, par);
	vga_out8(0x3d5, reg->CR51, par);

	/* memory timings */
	vga_out8(0x3d4, 0x36, par);
	vga_out8(0x3d5, reg->CR36, par);
	vga_out8(0x3d4, 0x60, par);
	vga_out8(0x3d5, reg->CR60, par);
	vga_out8(0x3d4, 0x68, par);
	vga_out8(0x3d5, reg->CR68, par);
	vga_out8(0x3d4, 0x69, par);
	vga_out8(0x3d5, reg->CR69, par);
	vga_out8(0x3d4, 0x6f, par);
	vga_out8(0x3d5, reg->CR6F, par);

	vga_out8(0x3d4, 0x33, par);
	vga_out8(0x3d5, reg->CR33, par);
	vga_out8(0x3d4, 0x86, par);
	vga_out8(0x3d5, reg->CR86, par);
	vga_out8(0x3d4, 0x88, par);
	vga_out8(0x3d5, reg->CR88, par);
	vga_out8(0x3d4, 0x90, par);
	vga_out8(0x3d5, reg->CR90, par);
	vga_out8(0x3d4, 0x91, par);
	vga_out8(0x3d5, reg->CR91, par);

	अगर (par->chip == S3_SAVAGE4) अणु
		vga_out8(0x3d4, 0xb0, par);
		vga_out8(0x3d5, reg->CRB0, par);
	पूर्ण

	vga_out8(0x3d4, 0x32, par);
	vga_out8(0x3d5, reg->CR32, par);

	/* unlock extended seq regs */
	vga_out8(0x3c4, 0x08, par);
	vga_out8(0x3c5, 0x06, par);

	/* Restore extended sequencer regs क्रम MCLK. SR10 == 255 indicates
	 * that we should leave the शेष SR10 and SR11 values there.
	 */
	अगर (reg->SR10 != 255) अणु
		vga_out8(0x3c4, 0x10, par);
		vga_out8(0x3c5, reg->SR10, par);
		vga_out8(0x3c4, 0x11, par);
		vga_out8(0x3c5, reg->SR11, par);
	पूर्ण

	/* restore extended seq regs क्रम dclk */
	vga_out8(0x3c4, 0x0e, par);
	vga_out8(0x3c5, reg->SR0E, par);
	vga_out8(0x3c4, 0x0f, par);
	vga_out8(0x3c5, reg->SR0F, par);
	vga_out8(0x3c4, 0x12, par);
	vga_out8(0x3c5, reg->SR12, par);
	vga_out8(0x3c4, 0x13, par);
	vga_out8(0x3c5, reg->SR13, par);
	vga_out8(0x3c4, 0x29, par);
	vga_out8(0x3c5, reg->SR29, par);
	vga_out8(0x3c4, 0x18, par);
	vga_out8(0x3c5, reg->SR18, par);

	/* load new m, n pll values क्रम dclk & mclk */
	vga_out8(0x3c4, 0x15, par);
	पंचांगp = vga_in8(0x3c5, par) & ~0x21;

	vga_out8(0x3c5, पंचांगp | 0x03, par);
	vga_out8(0x3c5, पंचांगp | 0x23, par);
	vga_out8(0x3c5, पंचांगp | 0x03, par);
	vga_out8(0x3c5, reg->SR15, par);
	udelay(100);

	vga_out8(0x3c4, 0x30, par);
	vga_out8(0x3c5, reg->SR30, par);
	vga_out8(0x3c4, 0x08, par);
	vga_out8(0x3c5, reg->SR08, par);

	/* now ग_लिखो out cr67 in full, possibly starting STREAMS */
	VerticalRetraceWait(par);
	vga_out8(0x3d4, 0x67, par);
	vga_out8(0x3d5, reg->CR67, par);

	vga_out8(0x3d4, 0x66, par);
	cr66 = vga_in8(0x3d5, par);
	vga_out8(0x3d5, cr66 | 0x80, par);
	vga_out8(0x3d4, 0x3a, par);
	cr3a = vga_in8(0x3d5, par);
	vga_out8(0x3d5, cr3a | 0x80, par);

	अगर (par->chip != S3_SAVAGE_MX) अणु
		VerticalRetraceWait(par);
		savage_out32(FIFO_CONTROL_REG, reg->MMPR0, par);
		par->SavageWaitIdle(par);
		savage_out32(MIU_CONTROL_REG, reg->MMPR1, par);
		par->SavageWaitIdle(par);
		savage_out32(STREAMS_TIMEOUT_REG, reg->MMPR2, par);
		par->SavageWaitIdle(par);
		savage_out32(MISC_TIMEOUT_REG, reg->MMPR3, par);
	पूर्ण

	vga_out8(0x3d4, 0x66, par);
	vga_out8(0x3d5, cr66, par);
	vga_out8(0x3d4, 0x3a, par);
	vga_out8(0x3d5, cr3a, par);

	SavageSetup2DEngine(par);
	vgaHWProtect(par, 0);
पूर्ण

अटल व्योम savagefb_update_start(काष्ठा savagefb_par *par, पूर्णांक base)
अणु
	/* program the start address रेजिस्टरs */
	vga_out16(0x3d4, (base & 0x00ff00) | 0x0c, par);
	vga_out16(0x3d4, ((base & 0x00ff) << 8) | 0x0d, par);
	vga_out8(0x3d4, 0x69, par);
	vga_out8(0x3d5, (base & 0x7f0000) >> 16, par);
पूर्ण


अटल व्योम savagefb_set_fix(काष्ठा fb_info *info)
अणु
	info->fix.line_length = info->var.xres_भव *
		info->var.bits_per_pixel / 8;

	अगर (info->var.bits_per_pixel == 8) अणु
		info->fix.visual      = FB_VISUAL_PSEUDOCOLOR;
		info->fix.xpanstep    = 4;
	पूर्ण अन्यथा अणु
		info->fix.visual      = FB_VISUAL_TRUECOLOR;
		info->fix.xpanstep    = 2;
	पूर्ण

पूर्ण

अटल पूर्णांक savagefb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा savagefb_par *par = info->par;
	काष्ठा fb_var_screeninfo *var = &info->var;
	पूर्णांक err;

	DBG("savagefb_set_par");
	err = savagefb_decode_var(var, par, &par->state);
	अगर (err)
		वापस err;

	अगर (par->dacSpeedBpp <= 0) अणु
		अगर (var->bits_per_pixel > 24)
			par->dacSpeedBpp = par->घड़ी[3];
		अन्यथा अगर (var->bits_per_pixel >= 24)
			par->dacSpeedBpp = par->घड़ी[2];
		अन्यथा अगर ((var->bits_per_pixel > 8) && (var->bits_per_pixel < 24))
			par->dacSpeedBpp = par->घड़ी[1];
		अन्यथा अगर (var->bits_per_pixel <= 8)
			par->dacSpeedBpp = par->घड़ी[0];
	पूर्ण

	/* Set ramdac limits */
	par->maxClock = par->dacSpeedBpp;
	par->minClock = 10000;

	savagefb_set_par_पूर्णांक(par, &par->state);
	fb_set_cmap(&info->cmap, info);
	savagefb_set_fix(info);
	savagefb_set_clip(info);

	SavagePrपूर्णांकRegs(par);
	वापस 0;
पूर्ण

/*
 *    Pan or Wrap the Display
 */
अटल पूर्णांक savagefb_pan_display(काष्ठा fb_var_screeninfo *var,
				काष्ठा fb_info           *info)
अणु
	काष्ठा savagefb_par *par = info->par;
	पूर्णांक base;

	base = (var->yoffset * info->fix.line_length
	     + (var->xoffset & ~1) * ((info->var.bits_per_pixel+7) / 8)) >> 2;

	savagefb_update_start(par, base);
	वापस 0;
पूर्ण

अटल पूर्णांक savagefb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा savagefb_par *par = info->par;
	u8 sr8 = 0, srd = 0;

	अगर (par->display_type == DISP_CRT) अणु
		vga_out8(0x3c4, 0x08, par);
		sr8 = vga_in8(0x3c5, par);
		sr8 |= 0x06;
		vga_out8(0x3c5, sr8, par);
		vga_out8(0x3c4, 0x0d, par);
		srd = vga_in8(0x3c5, par);
		srd &= 0x50;

		चयन (blank) अणु
		हाल FB_BLANK_UNBLANK:
		हाल FB_BLANK_NORMAL:
			अवरोध;
		हाल FB_BLANK_VSYNC_SUSPEND:
			srd |= 0x10;
			अवरोध;
		हाल FB_BLANK_HSYNC_SUSPEND:
			srd |= 0x40;
			अवरोध;
		हाल FB_BLANK_POWERDOWN:
			srd |= 0x50;
			अवरोध;
		पूर्ण

		vga_out8(0x3c4, 0x0d, par);
		vga_out8(0x3c5, srd, par);
	पूर्ण

	अगर (par->display_type == DISP_LCD ||
	    par->display_type == DISP_DFP) अणु
		चयन(blank) अणु
		हाल FB_BLANK_UNBLANK:
		हाल FB_BLANK_NORMAL:
			vga_out8(0x3c4, 0x31, par); /* SR31 bit 4 - FP enable */
			vga_out8(0x3c5, vga_in8(0x3c5, par) | 0x10, par);
			अवरोध;
		हाल FB_BLANK_VSYNC_SUSPEND:
		हाल FB_BLANK_HSYNC_SUSPEND:
		हाल FB_BLANK_POWERDOWN:
			vga_out8(0x3c4, 0x31, par); /* SR31 bit 4 - FP enable */
			vga_out8(0x3c5, vga_in8(0x3c5, par) & ~0x10, par);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस (blank == FB_BLANK_NORMAL) ? 1 : 0;
पूर्ण

अटल पूर्णांक savagefb_खोलो(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा savagefb_par *par = info->par;

	mutex_lock(&par->खोलो_lock);

	अगर (!par->खोलो_count) अणु
		स_रखो(&par->vgastate, 0, माप(par->vgastate));
		par->vgastate.flags = VGA_SAVE_CMAP | VGA_SAVE_FONTS |
			VGA_SAVE_MODE;
		par->vgastate.vgabase = par->mmio.vbase + 0x8000;
		save_vga(&par->vgastate);
		savage_get_शेष_par(par, &par->initial);
	पूर्ण

	par->खोलो_count++;
	mutex_unlock(&par->खोलो_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक savagefb_release(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा savagefb_par *par = info->par;

	mutex_lock(&par->खोलो_lock);

	अगर (par->खोलो_count == 1) अणु
		savage_set_शेष_par(par, &par->initial);
		restore_vga(&par->vgastate);
	पूर्ण

	par->खोलो_count--;
	mutex_unlock(&par->खोलो_lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops savagefb_ops = अणु
	.owner          = THIS_MODULE,
	.fb_खोलो        = savagefb_खोलो,
	.fb_release     = savagefb_release,
	.fb_check_var   = savagefb_check_var,
	.fb_set_par     = savagefb_set_par,
	.fb_setcolreg   = savagefb_setcolreg,
	.fb_pan_display = savagefb_pan_display,
	.fb_blank       = savagefb_blank,
#अगर defined(CONFIG_FB_SAVAGE_ACCEL)
	.fb_fillrect    = savagefb_fillrect,
	.fb_copyarea    = savagefb_copyarea,
	.fb_imageblit   = savagefb_imageblit,
	.fb_sync        = savagefb_sync,
#अन्यथा
	.fb_fillrect    = cfb_fillrect,
	.fb_copyarea    = cfb_copyarea,
	.fb_imageblit   = cfb_imageblit,
#पूर्ण_अगर
पूर्ण;

/* --------------------------------------------------------------------- */

अटल स्थिर काष्ठा fb_var_screeninfo savagefb_var800x600x8 = अणु
	.accel_flags =	FB_ACCELF_TEXT,
	.xres =		800,
	.yres =		600,
	.xres_भव =  800,
	.yres_भव =  600,
	.bits_per_pixel = 8,
	.pixघड़ी =	25000,
	.left_margin =	88,
	.right_margin =	40,
	.upper_margin =	23,
	.lower_margin =	1,
	.hsync_len =	128,
	.vsync_len =	4,
	.sync =		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	.vmode =	FB_VMODE_NONINTERLACED
पूर्ण;

अटल व्योम savage_enable_mmio(काष्ठा savagefb_par *par)
अणु
	अचिन्हित अक्षर val;

	DBG("savage_enable_mmio\n");

	val = vga_in8(0x3c3, par);
	vga_out8(0x3c3, val | 0x01, par);
	val = vga_in8(0x3cc, par);
	vga_out8(0x3c2, val | 0x01, par);

	अगर (par->chip >= S3_SAVAGE4) अणु
		vga_out8(0x3d4, 0x40, par);
		val = vga_in8(0x3d5, par);
		vga_out8(0x3d5, val | 1, par);
	पूर्ण
पूर्ण


अटल व्योम savage_disable_mmio(काष्ठा savagefb_par *par)
अणु
	अचिन्हित अक्षर val;

	DBG("savage_disable_mmio\n");

	अगर (par->chip >= S3_SAVAGE4) अणु
		vga_out8(0x3d4, 0x40, par);
		val = vga_in8(0x3d5, par);
		vga_out8(0x3d5, val | 1, par);
	पूर्ण
पूर्ण


अटल पूर्णांक savage_map_mmio(काष्ठा fb_info *info)
अणु
	काष्ठा savagefb_par *par = info->par;
	DBG("savage_map_mmio");

	अगर (S3_SAVAGE3D_SERIES(par->chip))
		par->mmio.pbase = pci_resource_start(par->pcidev, 0) +
			SAVAGE_NEWMMIO_REGBASE_S3;
	अन्यथा
		par->mmio.pbase = pci_resource_start(par->pcidev, 0) +
			SAVAGE_NEWMMIO_REGBASE_S4;

	par->mmio.len = SAVAGE_NEWMMIO_REGSIZE;

	par->mmio.vbase = ioremap(par->mmio.pbase, par->mmio.len);
	अगर (!par->mmio.vbase) अणु
		prपूर्णांकk("savagefb: unable to map memory mapped IO\n");
		वापस -ENOMEM;
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_INFO "savagefb: mapped io at %p\n",
			par->mmio.vbase);

	info->fix.mmio_start = par->mmio.pbase;
	info->fix.mmio_len   = par->mmio.len;

	par->bci_base = (u32 __iomem *)(par->mmio.vbase + BCI_BUFFER_OFFSET);
	par->bci_ptr  = 0;

	savage_enable_mmio(par);

	वापस 0;
पूर्ण

अटल व्योम savage_unmap_mmio(काष्ठा fb_info *info)
अणु
	काष्ठा savagefb_par *par = info->par;
	DBG("savage_unmap_mmio");

	savage_disable_mmio(par);

	अगर (par->mmio.vbase) अणु
		iounmap(par->mmio.vbase);
		par->mmio.vbase = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक savage_map_video(काष्ठा fb_info *info, पूर्णांक video_len)
अणु
	काष्ठा savagefb_par *par = info->par;
	पूर्णांक resource;

	DBG("savage_map_video");

	अगर (S3_SAVAGE3D_SERIES(par->chip))
		resource = 0;
	अन्यथा
		resource = 1;

	par->video.pbase = pci_resource_start(par->pcidev, resource);
	par->video.len   = video_len;
	par->video.vbase = ioremap_wc(par->video.pbase, par->video.len);

	अगर (!par->video.vbase) अणु
		prपूर्णांकk("savagefb: unable to map screen memory\n");
		वापस -ENOMEM;
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_INFO "savagefb: mapped framebuffer at %p, "
		       "pbase == %x\n", par->video.vbase, par->video.pbase);

	info->fix.smem_start = par->video.pbase;
	info->fix.smem_len   = par->video.len - par->cob_size;
	info->screen_base    = par->video.vbase;
	par->video.wc_cookie = arch_phys_wc_add(par->video.pbase, video_len);

	/* Clear framebuffer, it's all white in memory after boot */
	स_रखो_io(par->video.vbase, 0, par->video.len);

	वापस 0;
पूर्ण

अटल व्योम savage_unmap_video(काष्ठा fb_info *info)
अणु
	काष्ठा savagefb_par *par = info->par;

	DBG("savage_unmap_video");

	अगर (par->video.vbase) अणु
		arch_phys_wc_del(par->video.wc_cookie);
		iounmap(par->video.vbase);
		par->video.vbase = शून्य;
		info->screen_base = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक savage_init_hw(काष्ठा savagefb_par *par)
अणु
	अचिन्हित अक्षर config1, m, n, n1, n2, sr8, cr3f, cr66 = 0, पंचांगp;

	अटल अचिन्हित अक्षर RamSavage3D[] = अणु 8, 4, 4, 2 पूर्ण;
	अटल अचिन्हित अक्षर RamSavage4[] =  अणु 2, 4, 8, 12, 16, 32, 64, 32 पूर्ण;
	अटल अचिन्हित अक्षर RamSavageMX[] = अणु 2, 8, 4, 16, 8, 16, 4, 16 पूर्ण;
	अटल अचिन्हित अक्षर RamSavageNB[] = अणु 0, 2, 4, 8, 16, 32, 2, 2 पूर्ण;
	पूर्णांक videoRam, videoRambytes, dvi;

	DBG("savage_init_hw");

	/* unprotect CRTC[0-7] */
	vga_out8(0x3d4, 0x11, par);
	पंचांगp = vga_in8(0x3d5, par);
	vga_out8(0x3d5, पंचांगp & 0x7f, par);

	/* unlock extended regs */
	vga_out16(0x3d4, 0x4838, par);
	vga_out16(0x3d4, 0xa039, par);
	vga_out16(0x3c4, 0x0608, par);

	vga_out8(0x3d4, 0x40, par);
	पंचांगp = vga_in8(0x3d5, par);
	vga_out8(0x3d5, पंचांगp & ~0x01, par);

	/* unlock sys regs */
	vga_out8(0x3d4, 0x38, par);
	vga_out8(0x3d5, 0x48, par);

	/* Unlock प्रणाली रेजिस्टरs. */
	vga_out16(0x3d4, 0x4838, par);

	/* Next go on to detect amount of installed ram */

	vga_out8(0x3d4, 0x36, par);            /* क्रम रेजिस्टर CR36 (CONFG_REG1), */
	config1 = vga_in8(0x3d5, par);    /* get amount of vram installed */

	/* Compute the amount of video memory and offscreen memory. */

	चयन  (par->chip) अणु
	हाल S3_SAVAGE3D:
		videoRam = RamSavage3D[(config1 & 0xC0) >> 6 ] * 1024;
		अवरोध;

	हाल S3_SAVAGE4:
		/*
		 * The Savage4 has one ugly special हाल to consider.  On
		 * प्रणालीs with 4 banks of 2Mx32 SDRAM, the BIOS says 4MB
		 * when it really means 8MB.  Why करो it the same when you
		 * can करो it dअगरferent...
		 */
		vga_out8(0x3d4, 0x68, par);	/* memory control 1 */
		अगर ((vga_in8(0x3d5, par) & 0xC0) == (0x01 << 6))
			RamSavage4[1] = 8;
		fallthrough;

	हाल S3_SAVAGE2000:
		videoRam = RamSavage4[(config1 & 0xE0) >> 5] * 1024;
		अवरोध;

	हाल S3_SAVAGE_MX:
	हाल S3_SUPERSAVAGE:
		videoRam = RamSavageMX[(config1 & 0x0E) >> 1] * 1024;
		अवरोध;

	हाल S3_PROSAVAGE:
	हाल S3_PROSAVAGEDDR:
	हाल S3_TWISTER:
		videoRam = RamSavageNB[(config1 & 0xE0) >> 5] * 1024;
		अवरोध;

	शेष:
		/* How did we get here? */
		videoRam = 0;
		अवरोध;
	पूर्ण

	videoRambytes = videoRam * 1024;

	prपूर्णांकk(KERN_INFO "savagefb: probed videoram:  %dk\n", videoRam);

	/* reset graphics engine to aव्योम memory corruption */
	vga_out8(0x3d4, 0x66, par);
	cr66 = vga_in8(0x3d5, par);
	vga_out8(0x3d5, cr66 | 0x02, par);
	usleep_range(10000, 11000);

	vga_out8(0x3d4, 0x66, par);
	vga_out8(0x3d5, cr66 & ~0x02, par);	/* clear reset flag */
	usleep_range(10000, 11000);


	/*
	 * reset memory पूर्णांकerface, 3D engine, AGP master, PCI master,
	 * master engine unit, motion compensation/LPB
	 */
	vga_out8(0x3d4, 0x3f, par);
	cr3f = vga_in8(0x3d5, par);
	vga_out8(0x3d5, cr3f | 0x08, par);
	usleep_range(10000, 11000);

	vga_out8(0x3d4, 0x3f, par);
	vga_out8(0x3d5, cr3f & ~0x08, par);	/* clear reset flags */
	usleep_range(10000, 11000);

	/* Savage ramdac speeds */
	par->numClocks = 4;
	par->घड़ी[0] = 250000;
	par->घड़ी[1] = 250000;
	par->घड़ी[2] = 220000;
	par->घड़ी[3] = 220000;

	/* detect current mclk */
	vga_out8(0x3c4, 0x08, par);
	sr8 = vga_in8(0x3c5, par);
	vga_out8(0x3c5, 0x06, par);
	vga_out8(0x3c4, 0x10, par);
	n = vga_in8(0x3c5, par);
	vga_out8(0x3c4, 0x11, par);
	m = vga_in8(0x3c5, par);
	vga_out8(0x3c4, 0x08, par);
	vga_out8(0x3c5, sr8, par);
	m &= 0x7f;
	n1 = n & 0x1f;
	n2 = (n >> 5) & 0x03;
	par->MCLK = ((1431818 * (m+2)) / (n1+2) / (1 << n2) + 50) / 100;
	prपूर्णांकk(KERN_INFO "savagefb: Detected current MCLK value of %d kHz\n",
		par->MCLK);

	/* check क्रम DVI/flat panel */
	dvi = 0;

	अगर (par->chip == S3_SAVAGE4) अणु
		अचिन्हित अक्षर sr30 = 0x00;

		vga_out8(0x3c4, 0x30, par);
		/* clear bit 1 */
		vga_out8(0x3c5, vga_in8(0x3c5, par) & ~0x02, par);
		sr30 = vga_in8(0x3c5, par);
		अगर (sr30 & 0x02 /*0x04 */) अणु
			dvi = 1;
			prपूर्णांकk("savagefb: Digital Flat Panel Detected\n");
		पूर्ण
	पूर्ण

	अगर ((S3_SAVAGE_MOBILE_SERIES(par->chip) ||
	     S3_MOBILE_TWISTER_SERIES(par->chip)) && !par->crtonly)
		par->display_type = DISP_LCD;
	अन्यथा अगर (dvi || (par->chip == S3_SAVAGE4 && par->dvi))
		par->display_type = DISP_DFP;
	अन्यथा
		par->display_type = DISP_CRT;

	/* Check LCD panel parrmation */

	अगर (par->display_type == DISP_LCD) अणु
		अचिन्हित अक्षर cr6b = VGArCR(0x6b, par);

		पूर्णांक panelX = (VGArSEQ(0x61, par) +
			      ((VGArSEQ(0x66, par) & 0x02) << 7) + 1) * 8;
		पूर्णांक panelY = (VGArSEQ(0x69, par) +
			      ((VGArSEQ(0x6e, par) & 0x70) << 4) + 1);

		अक्षर * sTechnology = "Unknown";

		/* OK, I admit it.  I करोn't know how to limit the max करोt घड़ी
		 * क्रम LCD panels of various sizes.  I thought I copied the
		 * क्रमmula from the BIOS, but many users have parrmed me of
		 * my folly.
		 *
		 * Instead, I'll abanकरोn any attempt to स्वतःmatically limit the
		 * घड़ी, and add an LCDClock option to XF86Config.  Some day,
		 * I should come back to this.
		 */

		क्रमागत ACTIVE_DISPLAYS अणु /* These are the bits in CR6B */
			ActiveCRT = 0x01,
			ActiveLCD = 0x02,
			ActiveTV = 0x04,
			ActiveCRT2 = 0x20,
			ActiveDUO = 0x80
		पूर्ण;

		अगर ((VGArSEQ(0x39, par) & 0x03) == 0) अणु
			sTechnology = "TFT";
		पूर्ण अन्यथा अगर ((VGArSEQ(0x30, par) & 0x01) == 0) अणु
			sTechnology = "DSTN";
		पूर्ण अन्यथा 	अणु
			sTechnology = "STN";
		पूर्ण

		prपूर्णांकk(KERN_INFO "savagefb: %dx%d %s LCD panel detected %s\n",
		       panelX, panelY, sTechnology,
		       cr6b & ActiveLCD ? "and active" : "but not active");

		अगर (cr6b & ActiveLCD) 	अणु
			/*
			 * If the LCD is active and panel expansion is enabled,
			 * we probably want to समाप्त the HW cursor.
			 */

			prपूर्णांकk(KERN_INFO "savagefb: Limiting video mode to "
				"%dx%d\n", panelX, panelY);

			par->SavagePanelWidth = panelX;
			par->SavagePanelHeight = panelY;

		पूर्ण अन्यथा
			par->display_type = DISP_CRT;
	पूर्ण

	savage_get_शेष_par(par, &par->state);
	par->save = par->state;

	अगर (S3_SAVAGE4_SERIES(par->chip)) अणु
		/*
		 * The Savage4 and ProSavage have COB coherency bugs which
		 * render the buffer useless.  We disable it.
		 */
		par->cob_index = 2;
		par->cob_size = 0x8000 << par->cob_index;
		par->cob_offset = videoRambytes;
	पूर्ण अन्यथा अणु
		/* We use 128kB क्रम the COB on all chips. */

		par->cob_index  = 7;
		par->cob_size   = 0x400 << par->cob_index;
		par->cob_offset = videoRambytes - par->cob_size;
	पूर्ण

	वापस videoRambytes;
पूर्ण

अटल पूर्णांक savage_init_fb_info(काष्ठा fb_info *info, काष्ठा pci_dev *dev,
			       स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा savagefb_par *par = info->par;
	पूर्णांक err = 0;

	par->pcidev  = dev;

	info->fix.type	   = FB_TYPE_PACKED_PIXELS;
	info->fix.type_aux	   = 0;
	info->fix.ypanstep	   = 1;
	info->fix.ywrapstep   = 0;
	info->fix.accel       = id->driver_data;

	चयन (info->fix.accel) अणु
	हाल FB_ACCEL_SUPERSAVAGE:
		par->chip = S3_SUPERSAVAGE;
		snम_लिखो(info->fix.id, 16, "SuperSavage");
		अवरोध;
	हाल FB_ACCEL_SAVAGE4:
		par->chip = S3_SAVAGE4;
		snम_लिखो(info->fix.id, 16, "Savage4");
		अवरोध;
	हाल FB_ACCEL_SAVAGE3D:
		par->chip = S3_SAVAGE3D;
		snम_लिखो(info->fix.id, 16, "Savage3D");
		अवरोध;
	हाल FB_ACCEL_SAVAGE3D_MV:
		par->chip = S3_SAVAGE3D;
		snम_लिखो(info->fix.id, 16, "Savage3D-MV");
		अवरोध;
	हाल FB_ACCEL_SAVAGE2000:
		par->chip = S3_SAVAGE2000;
		snम_लिखो(info->fix.id, 16, "Savage2000");
		अवरोध;
	हाल FB_ACCEL_SAVAGE_MX_MV:
		par->chip = S3_SAVAGE_MX;
		snम_लिखो(info->fix.id, 16, "Savage/MX-MV");
		अवरोध;
	हाल FB_ACCEL_SAVAGE_MX:
		par->chip = S3_SAVAGE_MX;
		snम_लिखो(info->fix.id, 16, "Savage/MX");
		अवरोध;
	हाल FB_ACCEL_SAVAGE_IX_MV:
		par->chip = S3_SAVAGE_MX;
		snम_लिखो(info->fix.id, 16, "Savage/IX-MV");
		अवरोध;
	हाल FB_ACCEL_SAVAGE_IX:
		par->chip = S3_SAVAGE_MX;
		snम_लिखो(info->fix.id, 16, "Savage/IX");
		अवरोध;
	हाल FB_ACCEL_PROSAVAGE_PM:
		par->chip = S3_PROSAVAGE;
		snम_लिखो(info->fix.id, 16, "ProSavagePM");
		अवरोध;
	हाल FB_ACCEL_PROSAVAGE_KM:
		par->chip = S3_PROSAVAGE;
		snम_लिखो(info->fix.id, 16, "ProSavageKM");
		अवरोध;
	हाल FB_ACCEL_S3TWISTER_P:
		par->chip = S3_TWISTER;
		snम_लिखो(info->fix.id, 16, "TwisterP");
		अवरोध;
	हाल FB_ACCEL_S3TWISTER_K:
		par->chip = S3_TWISTER;
		snम_लिखो(info->fix.id, 16, "TwisterK");
		अवरोध;
	हाल FB_ACCEL_PROSAVAGE_DDR:
		par->chip = S3_PROSAVAGEDDR;
		snम_लिखो(info->fix.id, 16, "ProSavageDDR");
		अवरोध;
	हाल FB_ACCEL_PROSAVAGE_DDRK:
		par->chip = S3_PROSAVAGEDDR;
		snम_लिखो(info->fix.id, 16, "ProSavage8");
		अवरोध;
	पूर्ण

	अगर (S3_SAVAGE3D_SERIES(par->chip)) अणु
		par->SavageWaitIdle = savage3D_रुकोidle;
		par->SavageWaitFअगरo = savage3D_रुकोfअगरo;
	पूर्ण अन्यथा अगर (S3_SAVAGE4_SERIES(par->chip) ||
		   S3_SUPERSAVAGE == par->chip) अणु
		par->SavageWaitIdle = savage4_रुकोidle;
		par->SavageWaitFअगरo = savage4_रुकोfअगरo;
	पूर्ण अन्यथा अणु
		par->SavageWaitIdle = savage2000_रुकोidle;
		par->SavageWaitFअगरo = savage2000_रुकोfअगरo;
	पूर्ण

	info->var.nonstd      = 0;
	info->var.activate    = FB_ACTIVATE_NOW;
	info->var.width       = -1;
	info->var.height      = -1;
	info->var.accel_flags = 0;

	info->fbops          = &savagefb_ops;
	info->flags          = FBINFO_DEFAULT |
		               FBINFO_HWACCEL_YPAN |
		               FBINFO_HWACCEL_XPAN;

	info->pseuकरो_palette = par->pseuकरो_palette;

#अगर defined(CONFIG_FB_SAVAGE_ACCEL)
	/* FIFO size + padding क्रम commands */
	info->pixmap.addr = kसुस्मृति(8, 1024, GFP_KERNEL);

	err = -ENOMEM;
	अगर (info->pixmap.addr) अणु
		info->pixmap.size = 8*1024;
		info->pixmap.scan_align = 4;
		info->pixmap.buf_align = 4;
		info->pixmap.access_align = 32;

		err = fb_alloc_cmap(&info->cmap, NR_PALETTE, 0);
		अगर (!err)
			info->flags |= FBINFO_HWACCEL_COPYAREA |
				       FBINFO_HWACCEL_FILLRECT |
				       FBINFO_HWACCEL_IMAGEBLIT;
		अन्यथा
			kमुक्त(info->pixmap.addr);
	पूर्ण
#पूर्ण_अगर
	वापस err;
पूर्ण

/* --------------------------------------------------------------------- */

अटल पूर्णांक savagefb_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा fb_info *info;
	काष्ठा savagefb_par *par;
	u_पूर्णांक h_sync, v_sync;
	पूर्णांक err, lpitch;
	पूर्णांक video_len;

	DBG("savagefb_probe");

	info = framebuffer_alloc(माप(काष्ठा savagefb_par), &dev->dev);
	अगर (!info)
		वापस -ENOMEM;
	par = info->par;
	mutex_init(&par->खोलो_lock);
	err = pci_enable_device(dev);
	अगर (err)
		जाओ failed_enable;

	अगर ((err = pci_request_regions(dev, "savagefb"))) अणु
		prपूर्णांकk(KERN_ERR "cannot request PCI regions\n");
		जाओ failed_enable;
	पूर्ण

	err = -ENOMEM;

	अगर ((err = savage_init_fb_info(info, dev, id)))
		जाओ failed_init;

	err = savage_map_mmio(info);
	अगर (err)
		जाओ failed_mmio;

	video_len = savage_init_hw(par);
	/* FIXME: can't be negative */
	अगर (video_len < 0) अणु
		err = video_len;
		जाओ failed_mmio;
	पूर्ण

	err = savage_map_video(info, video_len);
	अगर (err)
		जाओ failed_video;

	INIT_LIST_HEAD(&info->modelist);
#अगर defined(CONFIG_FB_SAVAGE_I2C)
	savagefb_create_i2c_busses(info);
	savagefb_probe_i2c_connector(info, &par->edid);
	fb_edid_to_monspecs(par->edid, &info->monspecs);
	kमुक्त(par->edid);
	fb_videomode_to_modelist(info->monspecs.modedb,
				 info->monspecs.modedb_len,
				 &info->modelist);
#पूर्ण_अगर
	info->var = savagefb_var800x600x8;
	/* अगर a panel was detected, शेष to a CVT mode instead */
	अगर (par->SavagePanelWidth) अणु
		काष्ठा fb_videomode cvt_mode;

		स_रखो(&cvt_mode, 0, माप(cvt_mode));
		cvt_mode.xres = par->SavagePanelWidth;
		cvt_mode.yres = par->SavagePanelHeight;
		cvt_mode.refresh = 60;
		/* FIXME: अगर we know there is only the panel
		 * we can enable reduced blanking as well */
		अगर (fb_find_mode_cvt(&cvt_mode, 0, 0))
			prपूर्णांकk(KERN_WARNING "No CVT mode found for panel\n");
		अन्यथा अगर (fb_find_mode(&info->var, info, शून्य, शून्य, 0,
				      &cvt_mode, 0) != 3)
			info->var = savagefb_var800x600x8;
	पूर्ण

	अगर (mode_option) अणु
		fb_find_mode(&info->var, info, mode_option,
			     info->monspecs.modedb, info->monspecs.modedb_len,
			     शून्य, 8);
	पूर्ण अन्यथा अगर (info->monspecs.modedb != शून्य) अणु
		स्थिर काष्ठा fb_videomode *mode;

		mode = fb_find_best_display(&info->monspecs, &info->modelist);
		savage_update_var(&info->var, mode);
	पूर्ण

	/* maximize भव vertical length */
	lpitch = info->var.xres_भव*((info->var.bits_per_pixel + 7) >> 3);
	info->var.yres_भव = info->fix.smem_len/lpitch;

	अगर (info->var.yres_भव < info->var.yres) अणु
		err = -ENOMEM;
		जाओ failed;
	पूर्ण

#अगर defined(CONFIG_FB_SAVAGE_ACCEL)
	/*
	 * The clipping coordinates are masked with 0xFFF, so limit our
	 * भव resolutions to these sizes.
	 */
	अगर (info->var.yres_भव > 0x1000)
		info->var.yres_भव = 0x1000;

	अगर (info->var.xres_भव > 0x1000)
		info->var.xres_भव = 0x1000;
#पूर्ण_अगर
	savagefb_check_var(&info->var, info);
	savagefb_set_fix(info);

	/*
	 * Calculate the hsync and vsync frequencies.  Note that
	 * we split the 1e12 स्थिरant up so that we can preserve
	 * the precision and fit the results पूर्णांकo 32-bit रेजिस्टरs.
	 *  (1953125000 * 512 = 1e12)
	 */
	h_sync = 1953125000 / info->var.pixघड़ी;
	h_sync = h_sync * 512 / (info->var.xres + info->var.left_margin +
				 info->var.right_margin +
				 info->var.hsync_len);
	v_sync = h_sync / (info->var.yres + info->var.upper_margin +
			   info->var.lower_margin + info->var.vsync_len);

	prपूर्णांकk(KERN_INFO "savagefb v" SAVAGEFB_VERSION ": "
	       "%dkB VRAM, using %dx%d, %d.%03dkHz, %dHz\n",
	       info->fix.smem_len >> 10,
	       info->var.xres, info->var.yres,
	       h_sync / 1000, h_sync % 1000, v_sync);


	fb_destroy_modedb(info->monspecs.modedb);
	info->monspecs.modedb = शून्य;

	err = रेजिस्टर_framebuffer(info);
	अगर (err < 0)
		जाओ failed;

	prपूर्णांकk(KERN_INFO "fb: S3 %s frame buffer device\n",
	       info->fix.id);

	/*
	 * Our driver data
	 */
	pci_set_drvdata(dev, info);

	वापस 0;

 failed:
#अगर_घोषित CONFIG_FB_SAVAGE_I2C
	savagefb_delete_i2c_busses(info);
#पूर्ण_अगर
	fb_alloc_cmap(&info->cmap, 0, 0);
	savage_unmap_video(info);
 failed_video:
	savage_unmap_mmio(info);
 failed_mmio:
	kमुक्त(info->pixmap.addr);
 failed_init:
	pci_release_regions(dev);
 failed_enable:
	framebuffer_release(info);

	वापस err;
पूर्ण

अटल व्योम savagefb_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(dev);

	DBG("savagefb_remove");

	अगर (info) अणु
		unरेजिस्टर_framebuffer(info);

#अगर_घोषित CONFIG_FB_SAVAGE_I2C
		savagefb_delete_i2c_busses(info);
#पूर्ण_अगर
		fb_alloc_cmap(&info->cmap, 0, 0);
		savage_unmap_video(info);
		savage_unmap_mmio(info);
		kमुक्त(info->pixmap.addr);
		pci_release_regions(dev);
		framebuffer_release(info);
	पूर्ण
पूर्ण

अटल पूर्णांक savagefb_suspend_late(काष्ठा device *dev, pm_message_t mesg)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा savagefb_par *par = info->par;

	DBG("savagefb_suspend");

	अगर (mesg.event == PM_EVENT_PRETHAW)
		mesg.event = PM_EVENT_FREEZE;
	par->pm_state = mesg.event;
	dev->घातer.घातer_state = mesg;

	/*
	 * For PM_EVENT_FREEZE, करो not घातer करोwn so the console
	 * can reमुख्य active.
	 */
	अगर (mesg.event == PM_EVENT_FREEZE)
		वापस 0;

	console_lock();
	fb_set_suspend(info, 1);

	अगर (info->fbops->fb_sync)
		info->fbops->fb_sync(info);

	savagefb_blank(FB_BLANK_POWERDOWN, info);
	savage_set_शेष_par(par, &par->save);
	savage_disable_mmio(par);
	console_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused savagefb_suspend(काष्ठा device *dev)
अणु
	वापस savagefb_suspend_late(dev, PMSG_SUSPEND);
पूर्ण

अटल पूर्णांक __maybe_unused savagefb_hibernate(काष्ठा device *dev)
अणु
	वापस savagefb_suspend_late(dev, PMSG_HIBERNATE);
पूर्ण

अटल पूर्णांक __maybe_unused savagefb_मुक्तze(काष्ठा device *dev)
अणु
	वापस savagefb_suspend_late(dev, PMSG_FREEZE);
पूर्ण

अटल पूर्णांक __maybe_unused savagefb_resume(काष्ठा device *dev)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा savagefb_par *par = info->par;
	पूर्णांक cur_state = par->pm_state;

	DBG("savage_resume");

	par->pm_state = PM_EVENT_ON;

	/*
	 * The adapter was not घातered करोwn coming back from a
	 * PM_EVENT_FREEZE.
	 */
	अगर (cur_state == PM_EVENT_FREEZE)
		वापस 0;

	console_lock();

	savage_enable_mmio(par);
	savage_init_hw(par);
	savagefb_set_par(info);
	fb_set_suspend(info, 0);
	savagefb_blank(FB_BLANK_UNBLANK, info);
	console_unlock();

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops savagefb_pm_ops = अणु
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= savagefb_suspend,
	.resume		= savagefb_resume,
	.मुक्तze		= savagefb_मुक्तze,
	.thaw		= savagefb_resume,
	.घातeroff	= savagefb_hibernate,
	.restore	= savagefb_resume,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा pci_device_id savagefb_devices[] = अणु
	अणुPCI_VENDOR_ID_S3, PCI_CHIP_SUPSAV_MX128,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_SUPERSAVAGEपूर्ण,

	अणुPCI_VENDOR_ID_S3, PCI_CHIP_SUPSAV_MX64,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_SUPERSAVAGEपूर्ण,

	अणुPCI_VENDOR_ID_S3, PCI_CHIP_SUPSAV_MX64C,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_SUPERSAVAGEपूर्ण,

	अणुPCI_VENDOR_ID_S3, PCI_CHIP_SUPSAV_IX128SDR,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_SUPERSAVAGEपूर्ण,

	अणुPCI_VENDOR_ID_S3, PCI_CHIP_SUPSAV_IX128DDR,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_SUPERSAVAGEपूर्ण,

	अणुPCI_VENDOR_ID_S3, PCI_CHIP_SUPSAV_IX64SDR,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_SUPERSAVAGEपूर्ण,

	अणुPCI_VENDOR_ID_S3, PCI_CHIP_SUPSAV_IX64DDR,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_SUPERSAVAGEपूर्ण,

	अणुPCI_VENDOR_ID_S3, PCI_CHIP_SUPSAV_IXCSDR,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_SUPERSAVAGEपूर्ण,

	अणुPCI_VENDOR_ID_S3, PCI_CHIP_SUPSAV_IXCDDR,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_SUPERSAVAGEपूर्ण,

	अणुPCI_VENDOR_ID_S3, PCI_CHIP_SAVAGE4,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_SAVAGE4पूर्ण,

	अणुPCI_VENDOR_ID_S3, PCI_CHIP_SAVAGE3D,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_SAVAGE3Dपूर्ण,

	अणुPCI_VENDOR_ID_S3, PCI_CHIP_SAVAGE3D_MV,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_SAVAGE3D_MVपूर्ण,

	अणुPCI_VENDOR_ID_S3, PCI_CHIP_SAVAGE2000,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_SAVAGE2000पूर्ण,

	अणुPCI_VENDOR_ID_S3, PCI_CHIP_SAVAGE_MX_MV,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_SAVAGE_MX_MVपूर्ण,

	अणुPCI_VENDOR_ID_S3, PCI_CHIP_SAVAGE_MX,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_SAVAGE_MXपूर्ण,

	अणुPCI_VENDOR_ID_S3, PCI_CHIP_SAVAGE_IX_MV,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_SAVAGE_IX_MVपूर्ण,

	अणुPCI_VENDOR_ID_S3, PCI_CHIP_SAVAGE_IX,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_SAVAGE_IXपूर्ण,

	अणुPCI_VENDOR_ID_S3, PCI_CHIP_PROSAVAGE_PM,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_PROSAVAGE_PMपूर्ण,

	अणुPCI_VENDOR_ID_S3, PCI_CHIP_PROSAVAGE_KM,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_PROSAVAGE_KMपूर्ण,

	अणुPCI_VENDOR_ID_S3, PCI_CHIP_S3TWISTER_P,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_S3TWISTER_Pपूर्ण,

	अणुPCI_VENDOR_ID_S3, PCI_CHIP_S3TWISTER_K,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_S3TWISTER_Kपूर्ण,

	अणुPCI_VENDOR_ID_S3, PCI_CHIP_PROSAVAGE_DDR,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_PROSAVAGE_DDRपूर्ण,

	अणुPCI_VENDOR_ID_S3, PCI_CHIP_PROSAVAGE_DDRK,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEL_PROSAVAGE_DDRKपूर्ण,

	अणु0, 0, 0, 0, 0, 0, 0पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, savagefb_devices);

अटल काष्ठा pci_driver savagefb_driver = अणु
	.name =     "savagefb",
	.id_table = savagefb_devices,
	.probe =    savagefb_probe,
	.driver.pm = &savagefb_pm_ops,
	.हटाओ =   savagefb_हटाओ,
पूर्ण;

/* **************************** निकास-समय only **************************** */

अटल व्योम __निकास savage_करोne(व्योम)
अणु
	DBG("savage_done");
	pci_unरेजिस्टर_driver(&savagefb_driver);
पूर्ण


/* ************************* init in-kernel code ************************** */

अटल पूर्णांक __init savagefb_setup(अक्षर *options)
अणु
#अगर_अघोषित MODULE
	अक्षर *this_opt;

	अगर (!options || !*options)
		वापस 0;

	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
		mode_option = this_opt;
	पूर्ण
#पूर्ण_अगर /* !MODULE */
	वापस 0;
पूर्ण

अटल पूर्णांक __init savagefb_init(व्योम)
अणु
	अक्षर *option;

	DBG("savagefb_init");

	अगर (fb_get_options("savagefb", &option))
		वापस -ENODEV;

	savagefb_setup(option);
	वापस pci_रेजिस्टर_driver(&savagefb_driver);

पूर्ण

module_init(savagefb_init);
module_निकास(savage_करोne);

module_param(mode_option, अक्षरp, 0);
MODULE_PARM_DESC(mode_option, "Specify initial video mode");
