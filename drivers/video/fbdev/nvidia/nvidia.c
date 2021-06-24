<शैली गुरु>
/*
 * linux/drivers/video/nvidia/nvidia.c - nVidia fb driver
 *
 * Copyright 2004 Antonino Daplas <adaplas@pol.net>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
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
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/console.h>
#समावेश <linux/backlight.h>
#अगर_घोषित CONFIG_BOOTX_TEXT
#समावेश <यंत्र/btext.h>
#पूर्ण_अगर

#समावेश "nv_local.h"
#समावेश "nv_type.h"
#समावेश "nv_proto.h"
#समावेश "nv_dma.h"

#अगर_घोषित CONFIG_FB_NVIDIA_DEBUG
#घोषणा NVTRACE          prपूर्णांकk
#अन्यथा
#घोषणा NVTRACE          अगर (0) prपूर्णांकk
#पूर्ण_अगर

#घोषणा NVTRACE_ENTER(...)  NVTRACE("%s START\n", __func__)
#घोषणा NVTRACE_LEAVE(...)  NVTRACE("%s END\n", __func__)

#अगर_घोषित CONFIG_FB_NVIDIA_DEBUG
#घोषणा निश्चित(expr) \
	अगर (!(expr)) अणु \
	prपूर्णांकk( "Assertion failed! %s,%s,%s,line=%d\n",\
	#expr,__खाता__,__func__,__LINE__); \
	BUG(); \
	पूर्ण
#अन्यथा
#घोषणा निश्चित(expr)
#पूर्ण_अगर

#घोषणा PFX "nvidiafb: "

/* HW cursor parameters */
#घोषणा MAX_CURS		32

अटल स्थिर काष्ठा pci_device_id nvidiafb_pci_tbl[] = अणु
	अणुPCI_VENDOR_ID_NVIDIA, PCI_ANY_ID, PCI_ANY_ID, PCI_ANY_ID,
	 PCI_BASE_CLASS_DISPLAY << 16, 0xff0000, 0पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, nvidiafb_pci_tbl);

/* command line data, set in nvidiafb_setup() */
अटल पूर्णांक flatpanel = -1;	/* Autodetect later */
अटल पूर्णांक fpdither = -1;
अटल पूर्णांक क्रमceCRTC = -1;
अटल पूर्णांक hwcur = 0;
अटल पूर्णांक noaccel = 0;
अटल पूर्णांक noscale = 0;
अटल पूर्णांक paneltweak = 0;
अटल पूर्णांक vram = 0;
अटल पूर्णांक bpp = 8;
अटल पूर्णांक reverse_i2c;
अटल bool nomtrr = false;
अटल पूर्णांक backlight = IS_BUILTIN(CONFIG_PMAC_BACKLIGHT);

अटल अक्षर *mode_option = शून्य;

अटल काष्ठा fb_fix_screeninfo nvidiafb_fix = अणु
	.type = FB_TYPE_PACKED_PIXELS,
	.xpanstep = 8,
	.ypanstep = 1,
पूर्ण;

अटल काष्ठा fb_var_screeninfo nvidiafb_शेष_var = अणु
	.xres = 640,
	.yres = 480,
	.xres_भव = 640,
	.yres_भव = 480,
	.bits_per_pixel = 8,
	.red = अणु0, 8, 0पूर्ण,
	.green = अणु0, 8, 0पूर्ण,
	.blue = अणु0, 8, 0पूर्ण,
	.transp = अणु0, 0, 0पूर्ण,
	.activate = FB_ACTIVATE_NOW,
	.height = -1,
	.width = -1,
	.pixघड़ी = 39721,
	.left_margin = 40,
	.right_margin = 24,
	.upper_margin = 32,
	.lower_margin = 11,
	.hsync_len = 96,
	.vsync_len = 2,
	.vmode = FB_VMODE_NONINTERLACED
पूर्ण;

अटल व्योम nvidiafb_load_cursor_image(काष्ठा nvidia_par *par, u8 * data8,
				       u16 bg, u16 fg, u32 w, u32 h)
अणु
	u32 *data = (u32 *) data8;
	पूर्णांक i, j, k = 0;
	u32 b, पंचांगp;

	w = (w + 1) & ~1;

	क्रम (i = 0; i < h; i++) अणु
		b = *data++;
		reverse_order(&b);

		क्रम (j = 0; j < w / 2; j++) अणु
			पंचांगp = 0;
#अगर defined (__BIG_ENDIAN)
			पंचांगp = (b & (1 << 31)) ? fg << 16 : bg << 16;
			b <<= 1;
			पंचांगp |= (b & (1 << 31)) ? fg : bg;
			b <<= 1;
#अन्यथा
			पंचांगp = (b & 1) ? fg : bg;
			b >>= 1;
			पंचांगp |= (b & 1) ? fg << 16 : bg << 16;
			b >>= 1;
#पूर्ण_अगर
			NV_WR32(&par->CURSOR[k++], 0, पंचांगp);
		पूर्ण
		k += (MAX_CURS - w) / 2;
	पूर्ण
पूर्ण

अटल व्योम nvidia_ग_लिखो_clut(काष्ठा nvidia_par *par,
			      u8 regnum, u8 red, u8 green, u8 blue)
अणु
	NVWriteDacMask(par, 0xff);
	NVWriteDacWriteAddr(par, regnum);
	NVWriteDacData(par, red);
	NVWriteDacData(par, green);
	NVWriteDacData(par, blue);
पूर्ण

अटल व्योम nvidia_पढ़ो_clut(काष्ठा nvidia_par *par,
			     u8 regnum, u8 * red, u8 * green, u8 * blue)
अणु
	NVWriteDacMask(par, 0xff);
	NVWriteDacReadAddr(par, regnum);
	*red = NVReadDacData(par);
	*green = NVReadDacData(par);
	*blue = NVReadDacData(par);
पूर्ण

अटल पूर्णांक nvidia_panel_tweak(काष्ठा nvidia_par *par,
			      काष्ठा _riva_hw_state *state)
अणु
	पूर्णांक tweak = 0;

	अगर (par->paneltweak) अणु
		tweak = par->paneltweak;
	पूर्ण अन्यथा अणु
		/* Begin flat panel hacks.
		 * This is unक्रमtunate, but some chips need this रेजिस्टर
		 * tweaked or अन्यथा you get artअगरacts where adjacent pixels are
		 * swapped.  There are no hard rules क्रम what to set here so all
		 * we can करो is experiment and apply hacks.
		 */
		अगर (((par->Chipset & 0xffff) == 0x0328) && (state->bpp == 32)) अणु
			/* At least one NV34 laptop needs this workaround. */
			tweak = -1;
		पूर्ण

		अगर ((par->Chipset & 0xfff0) == 0x0310)
			tweak = 1;
		/* end flat panel hacks */
	पूर्ण

	वापस tweak;
पूर्ण

अटल व्योम nvidia_screen_off(काष्ठा nvidia_par *par, पूर्णांक on)
अणु
	अचिन्हित अक्षर पंचांगp;

	अगर (on) अणु
		/*
		 * Turn off screen and disable sequencer.
		 */
		पंचांगp = NVReadSeq(par, 0x01);

		NVWriteSeq(par, 0x00, 0x01);		/* Synchronous Reset */
		NVWriteSeq(par, 0x01, पंचांगp | 0x20);	/* disable the display */
	पूर्ण अन्यथा अणु
		/*
		 * Reenable sequencer, then turn on screen.
		 */

		पंचांगp = NVReadSeq(par, 0x01);

		NVWriteSeq(par, 0x01, पंचांगp & ~0x20);	/* reenable display */
		NVWriteSeq(par, 0x00, 0x03);		/* End Reset */
	पूर्ण
पूर्ण

अटल व्योम nvidia_save_vga(काष्ठा nvidia_par *par,
			    काष्ठा _riva_hw_state *state)
अणु
	पूर्णांक i;

	NVTRACE_ENTER();
	NVLockUnlock(par, 0);

	NVUnloadStateExt(par, state);

	state->misc_output = NVReadMiscOut(par);

	क्रम (i = 0; i < NUM_CRT_REGS; i++)
		state->crtc[i] = NVReadCrtc(par, i);

	क्रम (i = 0; i < NUM_ATC_REGS; i++)
		state->attr[i] = NVReadAttr(par, i);

	क्रम (i = 0; i < NUM_GRC_REGS; i++)
		state->gra[i] = NVReadGr(par, i);

	क्रम (i = 0; i < NUM_SEQ_REGS; i++)
		state->seq[i] = NVReadSeq(par, i);
	NVTRACE_LEAVE();
पूर्ण

#अघोषित DUMP_REG

अटल व्योम nvidia_ग_लिखो_regs(काष्ठा nvidia_par *par,
			      काष्ठा _riva_hw_state *state)
अणु
	पूर्णांक i;

	NVTRACE_ENTER();

	NVLoadStateExt(par, state);

	NVWriteMiscOut(par, state->misc_output);

	क्रम (i = 1; i < NUM_SEQ_REGS; i++) अणु
#अगर_घोषित DUMP_REG
		prपूर्णांकk(" SEQ[%02x] = %08x\n", i, state->seq[i]);
#पूर्ण_अगर
		NVWriteSeq(par, i, state->seq[i]);
	पूर्ण

	/* Ensure CRTC रेजिस्टरs 0-7 are unlocked by clearing bit 7 of CRTC[17] */
	NVWriteCrtc(par, 0x11, state->crtc[0x11] & ~0x80);

	क्रम (i = 0; i < NUM_CRT_REGS; i++) अणु
		चयन (i) अणु
		हाल 0x19:
		हाल 0x20 ... 0x40:
			अवरोध;
		शेष:
#अगर_घोषित DUMP_REG
			prपूर्णांकk("CRTC[%02x] = %08x\n", i, state->crtc[i]);
#पूर्ण_अगर
			NVWriteCrtc(par, i, state->crtc[i]);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < NUM_GRC_REGS; i++) अणु
#अगर_घोषित DUMP_REG
		prपूर्णांकk(" GRA[%02x] = %08x\n", i, state->gra[i]);
#पूर्ण_अगर
		NVWriteGr(par, i, state->gra[i]);
	पूर्ण

	क्रम (i = 0; i < NUM_ATC_REGS; i++) अणु
#अगर_घोषित DUMP_REG
		prपूर्णांकk("ATTR[%02x] = %08x\n", i, state->attr[i]);
#पूर्ण_अगर
		NVWriteAttr(par, i, state->attr[i]);
	पूर्ण

	NVTRACE_LEAVE();
पूर्ण

अटल पूर्णांक nvidia_calc_regs(काष्ठा fb_info *info)
अणु
	काष्ठा nvidia_par *par = info->par;
	काष्ठा _riva_hw_state *state = &par->ModeReg;
	पूर्णांक i, depth = fb_get_color_depth(&info->var, &info->fix);
	पूर्णांक h_display = info->var.xres / 8 - 1;
	पूर्णांक h_start = (info->var.xres + info->var.right_margin) / 8 - 1;
	पूर्णांक h_end = (info->var.xres + info->var.right_margin +
		     info->var.hsync_len) / 8 - 1;
	पूर्णांक h_total = (info->var.xres + info->var.right_margin +
		       info->var.hsync_len + info->var.left_margin) / 8 - 5;
	पूर्णांक h_blank_s = h_display;
	पूर्णांक h_blank_e = h_total + 4;
	पूर्णांक v_display = info->var.yres - 1;
	पूर्णांक v_start = info->var.yres + info->var.lower_margin - 1;
	पूर्णांक v_end = (info->var.yres + info->var.lower_margin +
		     info->var.vsync_len) - 1;
	पूर्णांक v_total = (info->var.yres + info->var.lower_margin +
		       info->var.vsync_len + info->var.upper_margin) - 2;
	पूर्णांक v_blank_s = v_display;
	पूर्णांक v_blank_e = v_total + 1;

	/*
	 * Set all CRTC values.
	 */

	अगर (info->var.vmode & FB_VMODE_INTERLACED)
		v_total |= 1;

	अगर (par->FlatPanel == 1) अणु
		v_start = v_total - 3;
		v_end = v_total - 2;
		v_blank_s = v_start;
		h_start = h_total - 5;
		h_end = h_total - 2;
		h_blank_e = h_total + 4;
	पूर्ण

	state->crtc[0x0] = Set8Bits(h_total);
	state->crtc[0x1] = Set8Bits(h_display);
	state->crtc[0x2] = Set8Bits(h_blank_s);
	state->crtc[0x3] = SetBitField(h_blank_e, 4: 0, 4:0)
		| SetBit(7);
	state->crtc[0x4] = Set8Bits(h_start);
	state->crtc[0x5] = SetBitField(h_blank_e, 5: 5, 7:7)
		| SetBitField(h_end, 4: 0, 4:0);
	state->crtc[0x6] = SetBitField(v_total, 7: 0, 7:0);
	state->crtc[0x7] = SetBitField(v_total, 8: 8, 0:0)
		| SetBitField(v_display, 8: 8, 1:1)
		| SetBitField(v_start, 8: 8, 2:2)
		| SetBitField(v_blank_s, 8: 8, 3:3)
		| SetBit(4)
		| SetBitField(v_total, 9: 9, 5:5)
		| SetBitField(v_display, 9: 9, 6:6)
		| SetBitField(v_start, 9: 9, 7:7);
	state->crtc[0x9] = SetBitField(v_blank_s, 9: 9, 5:5)
		| SetBit(6)
		| ((info->var.vmode & FB_VMODE_DOUBLE) ? 0x80 : 0x00);
	state->crtc[0x10] = Set8Bits(v_start);
	state->crtc[0x11] = SetBitField(v_end, 3: 0, 3:0) | SetBit(5);
	state->crtc[0x12] = Set8Bits(v_display);
	state->crtc[0x13] = ((info->var.xres_भव / 8) *
			     (info->var.bits_per_pixel / 8));
	state->crtc[0x15] = Set8Bits(v_blank_s);
	state->crtc[0x16] = Set8Bits(v_blank_e);

	state->attr[0x10] = 0x01;

	अगर (par->Television)
		state->attr[0x11] = 0x00;

	state->screen = SetBitField(h_blank_e, 6: 6, 4:4)
		| SetBitField(v_blank_s, 10: 10, 3:3)
		| SetBitField(v_start, 10: 10, 2:2)
		| SetBitField(v_display, 10: 10, 1:1)
		| SetBitField(v_total, 10: 10, 0:0);

	state->horiz = SetBitField(h_total, 8: 8, 0:0)
		| SetBitField(h_display, 8: 8, 1:1)
		| SetBitField(h_blank_s, 8: 8, 2:2)
		| SetBitField(h_start, 8: 8, 3:3);

	state->extra = SetBitField(v_total, 11: 11, 0:0)
		| SetBitField(v_display, 11: 11, 2:2)
		| SetBitField(v_start, 11: 11, 4:4)
		| SetBitField(v_blank_s, 11: 11, 6:6);

	अगर (info->var.vmode & FB_VMODE_INTERLACED) अणु
		h_total = (h_total >> 1) & ~1;
		state->पूर्णांकerlace = Set8Bits(h_total);
		state->horiz |= SetBitField(h_total, 8: 8, 4:4);
	पूर्ण अन्यथा अणु
		state->पूर्णांकerlace = 0xff;	/* पूर्णांकerlace off */
	पूर्ण

	/*
	 * Calculate the extended रेजिस्टरs.
	 */

	अगर (depth < 24)
		i = depth;
	अन्यथा
		i = 32;

	अगर (par->Architecture >= NV_ARCH_10)
		par->CURSOR = (अस्थिर u32 __iomem *)(info->screen_base +
						       par->CursorStart);

	अगर (info->var.sync & FB_SYNC_HOR_HIGH_ACT)
		state->misc_output &= ~0x40;
	अन्यथा
		state->misc_output |= 0x40;
	अगर (info->var.sync & FB_SYNC_VERT_HIGH_ACT)
		state->misc_output &= ~0x80;
	अन्यथा
		state->misc_output |= 0x80;

	NVCalcStateExt(par, state, i, info->var.xres_भव,
		       info->var.xres, info->var.yres_भव,
		       1000000000 / info->var.pixघड़ी, info->var.vmode);

	state->scale = NV_RD32(par->PRAMDAC, 0x00000848) & 0xfff000ff;
	अगर (par->FlatPanel == 1) अणु
		state->pixel |= (1 << 7);

		अगर (!par->fpScaler || (par->fpWidth <= info->var.xres)
		    || (par->fpHeight <= info->var.yres)) अणु
			state->scale |= (1 << 8);
		पूर्ण

		अगर (!par->crtcSync_पढ़ो) अणु
			state->crtcSync = NV_RD32(par->PRAMDAC, 0x0828);
			par->crtcSync_पढ़ो = 1;
		पूर्ण

		par->PanelTweak = nvidia_panel_tweak(par, state);
	पूर्ण

	state->vpll = state->pll;
	state->vpll2 = state->pll;
	state->vpllB = state->pllB;
	state->vpll2B = state->pllB;

	VGA_WR08(par->PCIO, 0x03D4, 0x1C);
	state->fअगरo = VGA_RD08(par->PCIO, 0x03D5) & ~(1<<5);

	अगर (par->CRTCnumber) अणु
		state->head = NV_RD32(par->PCRTC0, 0x00000860) & ~0x00001000;
		state->head2 = NV_RD32(par->PCRTC0, 0x00002860) | 0x00001000;
		state->crtcOwner = 3;
		state->pllsel |= 0x20000800;
		state->vpll = NV_RD32(par->PRAMDAC0, 0x00000508);
		अगर (par->twoStagePLL)
			state->vpllB = NV_RD32(par->PRAMDAC0, 0x00000578);
	पूर्ण अन्यथा अगर (par->twoHeads) अणु
		state->head = NV_RD32(par->PCRTC0, 0x00000860) | 0x00001000;
		state->head2 = NV_RD32(par->PCRTC0, 0x00002860) & ~0x00001000;
		state->crtcOwner = 0;
		state->vpll2 = NV_RD32(par->PRAMDAC0, 0x0520);
		अगर (par->twoStagePLL)
			state->vpll2B = NV_RD32(par->PRAMDAC0, 0x057C);
	पूर्ण

	state->cursorConfig = 0x00000100;

	अगर (info->var.vmode & FB_VMODE_DOUBLE)
		state->cursorConfig |= (1 << 4);

	अगर (par->alphaCursor) अणु
		अगर ((par->Chipset & 0x0ff0) != 0x0110)
			state->cursorConfig |= 0x04011000;
		अन्यथा
			state->cursorConfig |= 0x14011000;
		state->general |= (1 << 29);
	पूर्ण अन्यथा
		state->cursorConfig |= 0x02000000;

	अगर (par->twoHeads) अणु
		अगर ((par->Chipset & 0x0ff0) == 0x0110) अणु
			state->dither = NV_RD32(par->PRAMDAC, 0x0528) &
			    ~0x00010000;
			अगर (par->FPDither)
				state->dither |= 0x00010000;
		पूर्ण अन्यथा अणु
			state->dither = NV_RD32(par->PRAMDAC, 0x083C) & ~1;
			अगर (par->FPDither)
				state->dither |= 1;
		पूर्ण
	पूर्ण

	state->timingH = 0;
	state->timingV = 0;
	state->displayV = info->var.xres;

	वापस 0;
पूर्ण

अटल व्योम nvidia_init_vga(काष्ठा fb_info *info)
अणु
	काष्ठा nvidia_par *par = info->par;
	काष्ठा _riva_hw_state *state = &par->ModeReg;
	पूर्णांक i;

	क्रम (i = 0; i < 0x10; i++)
		state->attr[i] = i;
	state->attr[0x10] = 0x41;
	state->attr[0x11] = 0xff;
	state->attr[0x12] = 0x0f;
	state->attr[0x13] = 0x00;
	state->attr[0x14] = 0x00;

	स_रखो(state->crtc, 0x00, NUM_CRT_REGS);
	state->crtc[0x0a] = 0x20;
	state->crtc[0x17] = 0xe3;
	state->crtc[0x18] = 0xff;
	state->crtc[0x28] = 0x40;

	स_रखो(state->gra, 0x00, NUM_GRC_REGS);
	state->gra[0x05] = 0x40;
	state->gra[0x06] = 0x05;
	state->gra[0x07] = 0x0f;
	state->gra[0x08] = 0xff;

	state->seq[0x00] = 0x03;
	state->seq[0x01] = 0x01;
	state->seq[0x02] = 0x0f;
	state->seq[0x03] = 0x00;
	state->seq[0x04] = 0x0e;

	state->misc_output = 0xeb;
पूर्ण

अटल पूर्णांक nvidiafb_cursor(काष्ठा fb_info *info, काष्ठा fb_cursor *cursor)
अणु
	काष्ठा nvidia_par *par = info->par;
	u8 data[MAX_CURS * MAX_CURS / 8];
	पूर्णांक i, set = cursor->set;
	u16 fg, bg;

	अगर (cursor->image.width > MAX_CURS || cursor->image.height > MAX_CURS)
		वापस -ENXIO;

	NVShowHideCursor(par, 0);

	अगर (par->cursor_reset) अणु
		set = FB_CUR_SETALL;
		par->cursor_reset = 0;
	पूर्ण

	अगर (set & FB_CUR_SETSIZE)
		स_रखो_io(par->CURSOR, 0, MAX_CURS * MAX_CURS * 2);

	अगर (set & FB_CUR_SETPOS) अणु
		u32 xx, yy, temp;

		yy = cursor->image.dy - info->var.yoffset;
		xx = cursor->image.dx - info->var.xoffset;
		temp = xx & 0xFFFF;
		temp |= yy << 16;

		NV_WR32(par->PRAMDAC, 0x0000300, temp);
	पूर्ण

	अगर (set & (FB_CUR_SETSHAPE | FB_CUR_SETCMAP | FB_CUR_SETIMAGE)) अणु
		u32 bg_idx = cursor->image.bg_color;
		u32 fg_idx = cursor->image.fg_color;
		u32 s_pitch = (cursor->image.width + 7) >> 3;
		u32 d_pitch = MAX_CURS / 8;
		u8 *dat = (u8 *) cursor->image.data;
		u8 *msk = (u8 *) cursor->mask;
		u8 *src;

		src = kदो_स्मृति_array(s_pitch, cursor->image.height, GFP_ATOMIC);

		अगर (src) अणु
			चयन (cursor->rop) अणु
			हाल ROP_XOR:
				क्रम (i = 0; i < s_pitch * cursor->image.height; i++)
					src[i] = dat[i] ^ msk[i];
				अवरोध;
			हाल ROP_COPY:
			शेष:
				क्रम (i = 0; i < s_pitch * cursor->image.height; i++)
					src[i] = dat[i] & msk[i];
				अवरोध;
			पूर्ण

			fb_pad_aligned_buffer(data, d_pitch, src, s_pitch,
						cursor->image.height);

			bg = ((info->cmap.red[bg_idx] & 0xf8) << 7) |
			    ((info->cmap.green[bg_idx] & 0xf8) << 2) |
			    ((info->cmap.blue[bg_idx] & 0xf8) >> 3) | 1 << 15;

			fg = ((info->cmap.red[fg_idx] & 0xf8) << 7) |
			    ((info->cmap.green[fg_idx] & 0xf8) << 2) |
			    ((info->cmap.blue[fg_idx] & 0xf8) >> 3) | 1 << 15;

			NVLockUnlock(par, 0);

			nvidiafb_load_cursor_image(par, data, bg, fg,
						   cursor->image.width,
						   cursor->image.height);
			kमुक्त(src);
		पूर्ण
	पूर्ण

	अगर (cursor->enable)
		NVShowHideCursor(par, 1);

	वापस 0;
पूर्ण

अटल काष्ठा fb_ops nvidia_fb_ops;

अटल पूर्णांक nvidiafb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा nvidia_par *par = info->par;

	NVTRACE_ENTER();

	NVLockUnlock(par, 1);
	अगर (!par->FlatPanel || !par->twoHeads)
		par->FPDither = 0;

	अगर (par->FPDither < 0) अणु
		अगर ((par->Chipset & 0x0ff0) == 0x0110)
			par->FPDither = !!(NV_RD32(par->PRAMDAC, 0x0528)
					   & 0x00010000);
		अन्यथा
			par->FPDither = !!(NV_RD32(par->PRAMDAC, 0x083C) & 1);
		prपूर्णांकk(KERN_INFO PFX "Flat panel dithering %s\n",
		       par->FPDither ? "enabled" : "disabled");
	पूर्ण

	info->fix.visual = (info->var.bits_per_pixel == 8) ?
	    FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_सूचीECTCOLOR;

	nvidia_init_vga(info);
	nvidia_calc_regs(info);

	NVLockUnlock(par, 0);
	अगर (par->twoHeads) अणु
		VGA_WR08(par->PCIO, 0x03D4, 0x44);
		VGA_WR08(par->PCIO, 0x03D5, par->ModeReg.crtcOwner);
		NVLockUnlock(par, 0);
	पूर्ण

	nvidia_screen_off(par, 1);

	nvidia_ग_लिखो_regs(par, &par->ModeReg);
	NVSetStartAddress(par, 0);

#अगर defined (__BIG_ENDIAN)
	/* turn on LFB swapping */
	अणु
		अचिन्हित अक्षर पंचांगp;

		VGA_WR08(par->PCIO, 0x3d4, 0x46);
		पंचांगp = VGA_RD08(par->PCIO, 0x3d5);
		पंचांगp |= (1 << 7);
		VGA_WR08(par->PCIO, 0x3d5, पंचांगp);
    पूर्ण
#पूर्ण_अगर

	info->fix.line_length = (info->var.xres_भव *
				 info->var.bits_per_pixel) >> 3;
	अगर (info->var.accel_flags) अणु
		nvidia_fb_ops.fb_imageblit = nvidiafb_imageblit;
		nvidia_fb_ops.fb_fillrect = nvidiafb_fillrect;
		nvidia_fb_ops.fb_copyarea = nvidiafb_copyarea;
		nvidia_fb_ops.fb_sync = nvidiafb_sync;
		info->pixmap.scan_align = 4;
		info->flags &= ~FBINFO_HWACCEL_DISABLED;
		info->flags |= FBINFO_READS_FAST;
		NVResetGraphics(info);
	पूर्ण अन्यथा अणु
		nvidia_fb_ops.fb_imageblit = cfb_imageblit;
		nvidia_fb_ops.fb_fillrect = cfb_fillrect;
		nvidia_fb_ops.fb_copyarea = cfb_copyarea;
		nvidia_fb_ops.fb_sync = शून्य;
		info->pixmap.scan_align = 1;
		info->flags |= FBINFO_HWACCEL_DISABLED;
		info->flags &= ~FBINFO_READS_FAST;
	पूर्ण

	par->cursor_reset = 1;

	nvidia_screen_off(par, 0);

#अगर_घोषित CONFIG_BOOTX_TEXT
	/* Update debug text engine */
	btext_update_display(info->fix.smem_start,
			     info->var.xres, info->var.yres,
			     info->var.bits_per_pixel, info->fix.line_length);
#पूर्ण_अगर

	NVLockUnlock(par, 0);
	NVTRACE_LEAVE();
	वापस 0;
पूर्ण

अटल पूर्णांक nvidiafb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			      अचिन्हित blue, अचिन्हित transp,
			      काष्ठा fb_info *info)
अणु
	काष्ठा nvidia_par *par = info->par;
	पूर्णांक i;

	NVTRACE_ENTER();
	अगर (regno >= (1 << info->var.green.length))
		वापस -EINVAL;

	अगर (info->var.grayscale) अणु
		/* gray = 0.30*R + 0.59*G + 0.11*B */
		red = green = blue = (red * 77 + green * 151 + blue * 28) >> 8;
	पूर्ण

	अगर (regno < 16 && info->fix.visual == FB_VISUAL_सूचीECTCOLOR) अणु
		((u32 *) info->pseuकरो_palette)[regno] =
		    (regno << info->var.red.offset) |
		    (regno << info->var.green.offset) |
		    (regno << info->var.blue.offset);
	पूर्ण

	चयन (info->var.bits_per_pixel) अणु
	हाल 8:
		/* "transparent" stuff is completely ignored. */
		nvidia_ग_लिखो_clut(par, regno, red >> 8, green >> 8, blue >> 8);
		अवरोध;
	हाल 16:
		अगर (info->var.green.length == 5) अणु
			क्रम (i = 0; i < 8; i++) अणु
				nvidia_ग_लिखो_clut(par, regno * 8 + i, red >> 8,
						  green >> 8, blue >> 8);
			पूर्ण
		पूर्ण अन्यथा अणु
			u8 r, g, b;

			अगर (regno < 32) अणु
				क्रम (i = 0; i < 8; i++) अणु
					nvidia_ग_लिखो_clut(par, regno * 8 + i,
							  red >> 8, green >> 8,
							  blue >> 8);
				पूर्ण
			पूर्ण

			nvidia_पढ़ो_clut(par, regno * 4, &r, &g, &b);

			क्रम (i = 0; i < 4; i++)
				nvidia_ग_लिखो_clut(par, regno * 4 + i, r,
						  green >> 8, b);
		पूर्ण
		अवरोध;
	हाल 32:
		nvidia_ग_लिखो_clut(par, regno, red >> 8, green >> 8, blue >> 8);
		अवरोध;
	शेष:
		/* करो nothing */
		अवरोध;
	पूर्ण

	NVTRACE_LEAVE();
	वापस 0;
पूर्ण

अटल पूर्णांक nvidiafb_check_var(काष्ठा fb_var_screeninfo *var,
			      काष्ठा fb_info *info)
अणु
	काष्ठा nvidia_par *par = info->par;
	पूर्णांक memlen, vramlen, mode_valid = 0;
	पूर्णांक pitch, err = 0;

	NVTRACE_ENTER();

	var->transp.offset = 0;
	var->transp.length = 0;

	var->xres &= ~7;

	अगर (var->bits_per_pixel <= 8)
		var->bits_per_pixel = 8;
	अन्यथा अगर (var->bits_per_pixel <= 16)
		var->bits_per_pixel = 16;
	अन्यथा
		var->bits_per_pixel = 32;

	चयन (var->bits_per_pixel) अणु
	हाल 8:
		var->red.offset = 0;
		var->red.length = 8;
		var->green.offset = 0;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		var->transp.offset = 0;
		var->transp.length = 0;
		अवरोध;
	हाल 16:
		var->green.length = (var->green.length < 6) ? 5 : 6;
		var->red.length = 5;
		var->blue.length = 5;
		var->transp.length = 6 - var->green.length;
		var->blue.offset = 0;
		var->green.offset = 5;
		var->red.offset = 5 + var->green.length;
		var->transp.offset = (5 + var->red.offset) & 15;
		अवरोध;
	हाल 32:		/* RGBA 8888 */
		var->red.offset = 16;
		var->red.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		var->transp.length = 8;
		var->transp.offset = 24;
		अवरोध;
	पूर्ण

	var->red.msb_right = 0;
	var->green.msb_right = 0;
	var->blue.msb_right = 0;
	var->transp.msb_right = 0;

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
			fb_videomode_to_var(var, mode);
			mode_valid = 1;
		पूर्ण
	पूर्ण

	अगर (!mode_valid && info->monspecs.modedb_len)
		वापस -EINVAL;

	/*
	 * If we're on a flat panel, check अगर the mode is outside of the
	 * panel dimensions. If so, cap it and try क्रम the next best mode
	 * beक्रमe bailing out.
	 */
	अगर (par->fpWidth && par->fpHeight && (par->fpWidth < var->xres ||
					      par->fpHeight < var->yres)) अणु
		स्थिर काष्ठा fb_videomode *mode;

		var->xres = par->fpWidth;
		var->yres = par->fpHeight;

		mode = fb_find_best_mode(var, &info->modelist);
		अगर (!mode) अणु
			prपूर्णांकk(KERN_ERR PFX "mode out of range of flat "
			       "panel dimensions\n");
			वापस -EINVAL;
		पूर्ण

		fb_videomode_to_var(var, mode);
	पूर्ण

	अगर (var->yres_भव < var->yres)
		var->yres_भव = var->yres;

	अगर (var->xres_भव < var->xres)
		var->xres_भव = var->xres;

	var->xres_भव = (var->xres_भव + 63) & ~63;

	vramlen = info->screen_size;
	pitch = ((var->xres_भव * var->bits_per_pixel) + 7) / 8;
	memlen = pitch * var->yres_भव;

	अगर (memlen > vramlen) अणु
		var->yres_भव = vramlen / pitch;

		अगर (var->yres_भव < var->yres) अणु
			var->yres_भव = var->yres;
			var->xres_भव = vramlen / var->yres_भव;
			var->xres_भव /= var->bits_per_pixel / 8;
			var->xres_भव &= ~63;
			pitch = (var->xres_भव *
				 var->bits_per_pixel + 7) / 8;
			memlen = pitch * var->yres;

			अगर (var->xres_भव < var->xres) अणु
				prपूर्णांकk("nvidiafb: required video memory, "
				       "%d bytes, for %dx%d-%d (virtual) "
				       "is out of range\n",
				       memlen, var->xres_भव,
				       var->yres_भव, var->bits_per_pixel);
				err = -ENOMEM;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (var->accel_flags) अणु
		अगर (var->yres_भव > 0x7fff)
			var->yres_भव = 0x7fff;
		अगर (var->xres_भव > 0x7fff)
			var->xres_भव = 0x7fff;
	पूर्ण

	var->xres_भव &= ~63;

	NVTRACE_LEAVE();

	वापस err;
पूर्ण

अटल पूर्णांक nvidiafb_pan_display(काष्ठा fb_var_screeninfo *var,
				काष्ठा fb_info *info)
अणु
	काष्ठा nvidia_par *par = info->par;
	u32 total;

	total = var->yoffset * info->fix.line_length + var->xoffset;

	NVSetStartAddress(par, total);

	वापस 0;
पूर्ण

अटल पूर्णांक nvidiafb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा nvidia_par *par = info->par;
	अचिन्हित अक्षर पंचांगp, vesa;

	पंचांगp = NVReadSeq(par, 0x01) & ~0x20;	/* screen on/off */
	vesa = NVReadCrtc(par, 0x1a) & ~0xc0;	/* sync on/off */

	NVTRACE_ENTER();

	अगर (blank)
		पंचांगp |= 0x20;

	चयन (blank) अणु
	हाल FB_BLANK_UNBLANK:
	हाल FB_BLANK_NORMAL:
		अवरोध;
	हाल FB_BLANK_VSYNC_SUSPEND:
		vesa |= 0x80;
		अवरोध;
	हाल FB_BLANK_HSYNC_SUSPEND:
		vesa |= 0x40;
		अवरोध;
	हाल FB_BLANK_POWERDOWN:
		vesa |= 0xc0;
		अवरोध;
	पूर्ण

	NVWriteSeq(par, 0x01, पंचांगp);
	NVWriteCrtc(par, 0x1a, vesa);

	NVTRACE_LEAVE();

	वापस 0;
पूर्ण

/*
 * Because the VGA रेजिस्टरs are not mapped linearly in its MMIO space,
 * restrict VGA रेजिस्टर saving and restore to x86 only, where legacy VGA IO
 * access is legal. Consequently, we must also check अगर the device is the
 * primary display.
 */
#अगर_घोषित CONFIG_X86
अटल व्योम save_vga_x86(काष्ठा nvidia_par *par)
अणु
	काष्ठा resource *res= &par->pci_dev->resource[PCI_ROM_RESOURCE];

	अगर (res && res->flags & IORESOURCE_ROM_SHADOW) अणु
		स_रखो(&par->vgastate, 0, माप(par->vgastate));
		par->vgastate.flags = VGA_SAVE_MODE | VGA_SAVE_FONTS |
			VGA_SAVE_CMAP;
		save_vga(&par->vgastate);
	पूर्ण
पूर्ण

अटल व्योम restore_vga_x86(काष्ठा nvidia_par *par)
अणु
	काष्ठा resource *res= &par->pci_dev->resource[PCI_ROM_RESOURCE];

	अगर (res && res->flags & IORESOURCE_ROM_SHADOW)
		restore_vga(&par->vgastate);
पूर्ण
#अन्यथा
#घोषणा save_vga_x86(x) करो अणुपूर्ण जबतक (0)
#घोषणा restore_vga_x86(x) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर /* X86 */

अटल पूर्णांक nvidiafb_खोलो(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा nvidia_par *par = info->par;

	अगर (!par->खोलो_count) अणु
		save_vga_x86(par);
		nvidia_save_vga(par, &par->initial_state);
	पूर्ण

	par->खोलो_count++;
	वापस 0;
पूर्ण

अटल पूर्णांक nvidiafb_release(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा nvidia_par *par = info->par;
	पूर्णांक err = 0;

	अगर (!par->खोलो_count) अणु
		err = -EINVAL;
		जाओ करोne;
	पूर्ण

	अगर (par->खोलो_count == 1) अणु
		nvidia_ग_लिखो_regs(par, &par->initial_state);
		restore_vga_x86(par);
	पूर्ण

	par->खोलो_count--;
करोne:
	वापस err;
पूर्ण

अटल काष्ठा fb_ops nvidia_fb_ops = अणु
	.owner          = THIS_MODULE,
	.fb_खोलो        = nvidiafb_खोलो,
	.fb_release     = nvidiafb_release,
	.fb_check_var   = nvidiafb_check_var,
	.fb_set_par     = nvidiafb_set_par,
	.fb_setcolreg   = nvidiafb_setcolreg,
	.fb_pan_display = nvidiafb_pan_display,
	.fb_blank       = nvidiafb_blank,
	.fb_fillrect    = nvidiafb_fillrect,
	.fb_copyarea    = nvidiafb_copyarea,
	.fb_imageblit   = nvidiafb_imageblit,
	.fb_cursor      = nvidiafb_cursor,
	.fb_sync        = nvidiafb_sync,
पूर्ण;

अटल पूर्णांक nvidiafb_suspend_late(काष्ठा device *dev, pm_message_t mesg)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा nvidia_par *par = info->par;

	अगर (mesg.event == PM_EVENT_PRETHAW)
		mesg.event = PM_EVENT_FREEZE;
	console_lock();
	par->pm_state = mesg.event;

	अगर (mesg.event & PM_EVENT_SLEEP) अणु
		fb_set_suspend(info, 1);
		nvidiafb_blank(FB_BLANK_POWERDOWN, info);
		nvidia_ग_लिखो_regs(par, &par->SavedReg);
	पूर्ण
	dev->घातer.घातer_state = mesg;

	console_unlock();
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused nvidiafb_suspend(काष्ठा device *dev)
अणु
	वापस nvidiafb_suspend_late(dev, PMSG_SUSPEND);
पूर्ण

अटल पूर्णांक __maybe_unused nvidiafb_hibernate(काष्ठा device *dev)
अणु
	वापस nvidiafb_suspend_late(dev, PMSG_HIBERNATE);
पूर्ण

अटल पूर्णांक __maybe_unused nvidiafb_मुक्तze(काष्ठा device *dev)
अणु
	वापस nvidiafb_suspend_late(dev, PMSG_FREEZE);
पूर्ण

अटल पूर्णांक __maybe_unused nvidiafb_resume(काष्ठा device *dev)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा nvidia_par *par = info->par;

	console_lock();

	par->pm_state = PM_EVENT_ON;
	nvidiafb_set_par(info);
	fb_set_suspend (info, 0);
	nvidiafb_blank(FB_BLANK_UNBLANK, info);

	console_unlock();
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops nvidiafb_pm_ops = अणु
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= nvidiafb_suspend,
	.resume		= nvidiafb_resume,
	.मुक्तze		= nvidiafb_मुक्तze,
	.thaw		= nvidiafb_resume,
	.घातeroff	= nvidiafb_hibernate,
	.restore	= nvidiafb_resume,
#पूर्ण_अगर /* CONFIG_PM_SLEEP */
पूर्ण;

अटल पूर्णांक nvidia_set_fbinfo(काष्ठा fb_info *info)
अणु
	काष्ठा fb_monspecs *specs = &info->monspecs;
	काष्ठा fb_videomode modedb;
	काष्ठा nvidia_par *par = info->par;
	पूर्णांक lpitch;

	NVTRACE_ENTER();
	info->flags = FBINFO_DEFAULT
	    | FBINFO_HWACCEL_IMAGEBLIT
	    | FBINFO_HWACCEL_FILLRECT
	    | FBINFO_HWACCEL_COPYAREA
	    | FBINFO_HWACCEL_YPAN;

	fb_videomode_to_modelist(info->monspecs.modedb,
				 info->monspecs.modedb_len, &info->modelist);
	fb_var_to_videomode(&modedb, &nvidiafb_शेष_var);

	चयन (bpp) अणु
	हाल 0 ... 8:
		bpp = 8;
		अवरोध;
	हाल 9 ... 16:
		bpp = 16;
		अवरोध;
	शेष:
		bpp = 32;
		अवरोध;
	पूर्ण

	अगर (specs->modedb != शून्य) अणु
		स्थिर काष्ठा fb_videomode *mode;

		mode = fb_find_best_display(specs, &info->modelist);
		fb_videomode_to_var(&nvidiafb_शेष_var, mode);
		nvidiafb_शेष_var.bits_per_pixel = bpp;
	पूर्ण अन्यथा अगर (par->fpWidth && par->fpHeight) अणु
		अक्षर buf[16];

		स_रखो(buf, 0, 16);
		snम_लिखो(buf, 15, "%dx%dMR", par->fpWidth, par->fpHeight);
		fb_find_mode(&nvidiafb_शेष_var, info, buf, specs->modedb,
			     specs->modedb_len, &modedb, bpp);
	पूर्ण

	अगर (mode_option)
		fb_find_mode(&nvidiafb_शेष_var, info, mode_option,
			     specs->modedb, specs->modedb_len, &modedb, bpp);

	info->var = nvidiafb_शेष_var;
	info->fix.visual = (info->var.bits_per_pixel == 8) ?
		FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_सूचीECTCOLOR;
	info->pseuकरो_palette = par->pseuकरो_palette;
	fb_alloc_cmap(&info->cmap, 256, 0);
	fb_destroy_modedb(info->monspecs.modedb);
	info->monspecs.modedb = शून्य;

	/* maximize भव vertical length */
	lpitch = info->var.xres_भव *
		((info->var.bits_per_pixel + 7) >> 3);
	info->var.yres_भव = info->screen_size / lpitch;

	info->pixmap.scan_align = 4;
	info->pixmap.buf_align = 4;
	info->pixmap.access_align = 32;
	info->pixmap.size = 8 * 1024;
	info->pixmap.flags = FB_PIXMAP_SYSTEM;

	अगर (!hwcur)
	    nvidia_fb_ops.fb_cursor = शून्य;

	info->var.accel_flags = (!noaccel);

	चयन (par->Architecture) अणु
	हाल NV_ARCH_04:
		info->fix.accel = FB_ACCEL_NV4;
		अवरोध;
	हाल NV_ARCH_10:
		info->fix.accel = FB_ACCEL_NV_10;
		अवरोध;
	हाल NV_ARCH_20:
		info->fix.accel = FB_ACCEL_NV_20;
		अवरोध;
	हाल NV_ARCH_30:
		info->fix.accel = FB_ACCEL_NV_30;
		अवरोध;
	हाल NV_ARCH_40:
		info->fix.accel = FB_ACCEL_NV_40;
		अवरोध;
	पूर्ण

	NVTRACE_LEAVE();

	वापस nvidiafb_check_var(&info->var, info);
पूर्ण

अटल u32 nvidia_get_chipset(काष्ठा fb_info *info)
अणु
	काष्ठा nvidia_par *par = info->par;
	u32 id = (par->pci_dev->venकरोr << 16) | par->pci_dev->device;

	prपूर्णांकk(KERN_INFO PFX "Device ID: %x \n", id);

	अगर ((id & 0xfff0) == 0x00f0 ||
	    (id & 0xfff0) == 0x02e0) अणु
		/* pci-e */
		id = NV_RD32(par->REGS, 0x1800);

		अगर ((id & 0x0000ffff) == 0x000010DE)
			id = 0x10DE0000 | (id >> 16);
		अन्यथा अगर ((id & 0xffff0000) == 0xDE100000) /* wrong endian */
			id = 0x10DE0000 | ((id << 8) & 0x0000ff00) |
                            ((id >> 8) & 0x000000ff);
		prपूर्णांकk(KERN_INFO PFX "Subsystem ID: %x \n", id);
	पूर्ण

	वापस id;
पूर्ण

अटल u32 nvidia_get_arch(काष्ठा fb_info *info)
अणु
	काष्ठा nvidia_par *par = info->par;
	u32 arch = 0;

	चयन (par->Chipset & 0x0ff0) अणु
	हाल 0x0100:		/* GeForce 256 */
	हाल 0x0110:		/* GeForce2 MX */
	हाल 0x0150:		/* GeForce2 */
	हाल 0x0170:		/* GeForce4 MX */
	हाल 0x0180:		/* GeForce4 MX (8x AGP) */
	हाल 0x01A0:		/* nForce */
	हाल 0x01F0:		/* nForce2 */
		arch = NV_ARCH_10;
		अवरोध;
	हाल 0x0200:		/* GeForce3 */
	हाल 0x0250:		/* GeForce4 Ti */
	हाल 0x0280:		/* GeForce4 Ti (8x AGP) */
		arch = NV_ARCH_20;
		अवरोध;
	हाल 0x0300:		/* GeForceFX 5800 */
	हाल 0x0310:		/* GeForceFX 5600 */
	हाल 0x0320:		/* GeForceFX 5200 */
	हाल 0x0330:		/* GeForceFX 5900 */
	हाल 0x0340:		/* GeForceFX 5700 */
		arch = NV_ARCH_30;
		अवरोध;
	हाल 0x0040:		/* GeForce 6800 */
	हाल 0x00C0:		/* GeForce 6800 */
	हाल 0x0120:		/* GeForce 6800 */
	हाल 0x0140:		/* GeForce 6600 */
	हाल 0x0160:		/* GeForce 6200 */
	हाल 0x01D0:		/* GeForce 7200, 7300, 7400 */
	हाल 0x0090:		/* GeForce 7800 */
	हाल 0x0210:		/* GeForce 6800 */
	हाल 0x0220:		/* GeForce 6200 */
	हाल 0x0240:		/* GeForce 6100 */
	हाल 0x0290:		/* GeForce 7900 */
	हाल 0x0390:		/* GeForce 7600 */
	हाल 0x03D0:
		arch = NV_ARCH_40;
		अवरोध;
	हाल 0x0020:		/* TNT, TNT2 */
		arch = NV_ARCH_04;
		अवरोध;
	शेष:		/* unknown architecture */
		अवरोध;
	पूर्ण

	वापस arch;
पूर्ण

अटल पूर्णांक nvidiafb_probe(काष्ठा pci_dev *pd, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा nvidia_par *par;
	काष्ठा fb_info *info;
	अचिन्हित लघु cmd;


	NVTRACE_ENTER();
	निश्चित(pd != शून्य);

	info = framebuffer_alloc(माप(काष्ठा nvidia_par), &pd->dev);

	अगर (!info)
		जाओ err_out;

	par = info->par;
	par->pci_dev = pd;
	info->pixmap.addr = kzalloc(8 * 1024, GFP_KERNEL);

	अगर (info->pixmap.addr == शून्य)
		जाओ err_out_kमुक्त;

	अगर (pci_enable_device(pd)) अणु
		prपूर्णांकk(KERN_ERR PFX "cannot enable PCI device\n");
		जाओ err_out_enable;
	पूर्ण

	अगर (pci_request_regions(pd, "nvidiafb")) अणु
		prपूर्णांकk(KERN_ERR PFX "cannot request PCI regions\n");
		जाओ err_out_enable;
	पूर्ण

	par->FlatPanel = flatpanel;
	अगर (flatpanel == 1)
		prपूर्णांकk(KERN_INFO PFX "flatpanel support enabled\n");
	par->FPDither = fpdither;

	par->CRTCnumber = क्रमceCRTC;
	par->FpScale = (!noscale);
	par->paneltweak = paneltweak;
	par->reverse_i2c = reverse_i2c;

	/* enable IO and mem अगर not alपढ़ोy करोne */
	pci_पढ़ो_config_word(pd, PCI_COMMAND, &cmd);
	cmd |= (PCI_COMMAND_IO | PCI_COMMAND_MEMORY);
	pci_ग_लिखो_config_word(pd, PCI_COMMAND, cmd);

	nvidiafb_fix.mmio_start = pci_resource_start(pd, 0);
	nvidiafb_fix.smem_start = pci_resource_start(pd, 1);
	nvidiafb_fix.mmio_len = pci_resource_len(pd, 0);

	par->REGS = ioremap(nvidiafb_fix.mmio_start, nvidiafb_fix.mmio_len);

	अगर (!par->REGS) अणु
		prपूर्णांकk(KERN_ERR PFX "cannot ioremap MMIO base\n");
		जाओ err_out_मुक्त_base0;
	पूर्ण

	par->Chipset = nvidia_get_chipset(info);
	par->Architecture = nvidia_get_arch(info);

	अगर (par->Architecture == 0) अणु
		prपूर्णांकk(KERN_ERR PFX "unknown NV_ARCH\n");
		जाओ err_out_arch;
	पूर्ण

	प्र_लिखो(nvidiafb_fix.id, "NV%x", (pd->device & 0x0ff0) >> 4);

	अगर (NVCommonSetup(info))
		जाओ err_out_arch;

	par->FbAddress = nvidiafb_fix.smem_start;
	par->FbMapSize = par->RamAmountKBytes * 1024;
	अगर (vram && vram * 1024 * 1024 < par->FbMapSize)
		par->FbMapSize = vram * 1024 * 1024;

	/* Limit amount of vram to 64 MB */
	अगर (par->FbMapSize > 64 * 1024 * 1024)
		par->FbMapSize = 64 * 1024 * 1024;

	अगर(par->Architecture >= NV_ARCH_40)
  	        par->FbUsableSize = par->FbMapSize - (560 * 1024);
	अन्यथा
		par->FbUsableSize = par->FbMapSize - (128 * 1024);
	par->ScratchBufferSize = (par->Architecture < NV_ARCH_10) ? 8 * 1024 :
	    16 * 1024;
	par->ScratchBufferStart = par->FbUsableSize - par->ScratchBufferSize;
	par->CursorStart = par->FbUsableSize + (32 * 1024);

	info->screen_base = ioremap_wc(nvidiafb_fix.smem_start,
				       par->FbMapSize);
	info->screen_size = par->FbUsableSize;
	nvidiafb_fix.smem_len = par->RamAmountKBytes * 1024;

	अगर (!info->screen_base) अणु
		prपूर्णांकk(KERN_ERR PFX "cannot ioremap FB base\n");
		जाओ err_out_मुक्त_base1;
	पूर्ण

	par->FbStart = info->screen_base;

	अगर (!nomtrr)
		par->wc_cookie = arch_phys_wc_add(nvidiafb_fix.smem_start,
						  par->RamAmountKBytes * 1024);

	info->fbops = &nvidia_fb_ops;
	info->fix = nvidiafb_fix;

	अगर (nvidia_set_fbinfo(info) < 0) अणु
		prपूर्णांकk(KERN_ERR PFX "error setting initial video mode\n");
		जाओ err_out_iounmap_fb;
	पूर्ण

	nvidia_save_vga(par, &par->SavedReg);

	pci_set_drvdata(pd, info);

	अगर (backlight)
		nvidia_bl_init(par);

	अगर (रेजिस्टर_framebuffer(info) < 0) अणु
		prपूर्णांकk(KERN_ERR PFX "error registering nVidia framebuffer\n");
		जाओ err_out_iounmap_fb;
	पूर्ण


	prपूर्णांकk(KERN_INFO PFX
	       "PCI nVidia %s framebuffer (%dMB @ 0x%lX)\n",
	       info->fix.id,
	       par->FbMapSize / (1024 * 1024), info->fix.smem_start);

	NVTRACE_LEAVE();
	वापस 0;

err_out_iounmap_fb:
	iounmap(info->screen_base);
err_out_मुक्त_base1:
	fb_destroy_modedb(info->monspecs.modedb);
	nvidia_delete_i2c_busses(par);
err_out_arch:
	iounmap(par->REGS);
 err_out_मुक्त_base0:
	pci_release_regions(pd);
err_out_enable:
	kमुक्त(info->pixmap.addr);
err_out_kमुक्त:
	framebuffer_release(info);
err_out:
	वापस -ENODEV;
पूर्ण

अटल व्योम nvidiafb_हटाओ(काष्ठा pci_dev *pd)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(pd);
	काष्ठा nvidia_par *par = info->par;

	NVTRACE_ENTER();

	unरेजिस्टर_framebuffer(info);

	nvidia_bl_निकास(par);
	arch_phys_wc_del(par->wc_cookie);
	iounmap(info->screen_base);
	fb_destroy_modedb(info->monspecs.modedb);
	nvidia_delete_i2c_busses(par);
	iounmap(par->REGS);
	pci_release_regions(pd);
	kमुक्त(info->pixmap.addr);
	framebuffer_release(info);
	NVTRACE_LEAVE();
पूर्ण

/* ------------------------------------------------------------------------- *
 *
 * initialization
 *
 * ------------------------------------------------------------------------- */

#अगर_अघोषित MODULE
अटल पूर्णांक nvidiafb_setup(अक्षर *options)
अणु
	अक्षर *this_opt;

	NVTRACE_ENTER();
	अगर (!options || !*options)
		वापस 0;

	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!म_भेदन(this_opt, "forceCRTC", 9)) अणु
			अक्षर *p;

			p = this_opt + 9;
			अगर (!*p || !*(++p))
				जारी;
			क्रमceCRTC = *p - '0';
			अगर (क्रमceCRTC < 0 || क्रमceCRTC > 1)
				क्रमceCRTC = -1;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "flatpanel", 9)) अणु
			flatpanel = 1;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "hwcur", 5)) अणु
			hwcur = 1;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "noaccel", 6)) अणु
			noaccel = 1;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "noscale", 7)) अणु
			noscale = 1;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "reverse_i2c", 11)) अणु
			reverse_i2c = 1;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "paneltweak:", 11)) अणु
			paneltweak = simple_म_से_अदीर्घ(this_opt+11, शून्य, 0);
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "vram:", 5)) अणु
			vram = simple_म_से_अदीर्घ(this_opt+5, शून्य, 0);
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "backlight:", 10)) अणु
			backlight = simple_म_से_अदीर्घ(this_opt+10, शून्य, 0);
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "nomtrr", 6)) अणु
			nomtrr = true;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "fpdither:", 9)) अणु
			fpdither = simple_म_से_दीर्घ(this_opt+9, शून्य, 0);
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "bpp:", 4)) अणु
			bpp = simple_म_से_अदीर्घ(this_opt+4, शून्य, 0);
		पूर्ण अन्यथा
			mode_option = this_opt;
	पूर्ण
	NVTRACE_LEAVE();
	वापस 0;
पूर्ण
#पूर्ण_अगर				/* !MODULE */

अटल काष्ठा pci_driver nvidiafb_driver = अणु
	.name      = "nvidiafb",
	.id_table  = nvidiafb_pci_tbl,
	.probe     = nvidiafb_probe,
	.driver.pm = &nvidiafb_pm_ops,
	.हटाओ    = nvidiafb_हटाओ,
पूर्ण;

/* ------------------------------------------------------------------------- *
 *
 * modularization
 *
 * ------------------------------------------------------------------------- */

अटल पूर्णांक nvidiafb_init(व्योम)
अणु
#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("nvidiafb", &option))
		वापस -ENODEV;
	nvidiafb_setup(option);
#पूर्ण_अगर
	वापस pci_रेजिस्टर_driver(&nvidiafb_driver);
पूर्ण

module_init(nvidiafb_init);

अटल व्योम __निकास nvidiafb_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&nvidiafb_driver);
पूर्ण

module_निकास(nvidiafb_निकास);

module_param(flatpanel, पूर्णांक, 0);
MODULE_PARM_DESC(flatpanel,
		 "Enables experimental flat panel support for some chipsets. "
		 "(0=disabled, 1=enabled, -1=autodetect) (default=-1)");
module_param(fpdither, पूर्णांक, 0);
MODULE_PARM_DESC(fpdither,
		 "Enables dithering of flat panel for 6 bits panels. "
		 "(0=disabled, 1=enabled, -1=autodetect) (default=-1)");
module_param(hwcur, पूर्णांक, 0);
MODULE_PARM_DESC(hwcur,
		 "Enables hardware cursor implementation. (0 or 1=enabled) "
		 "(default=0)");
module_param(noaccel, पूर्णांक, 0);
MODULE_PARM_DESC(noaccel,
		 "Disables hardware acceleration. (0 or 1=disable) "
		 "(default=0)");
module_param(noscale, पूर्णांक, 0);
MODULE_PARM_DESC(noscale,
		 "Disables screen scaling. (0 or 1=disable) "
		 "(default=0, do scaling)");
module_param(paneltweak, पूर्णांक, 0);
MODULE_PARM_DESC(paneltweak,
		 "Tweak display settings for flatpanels. "
		 "(default=0, no tweaks)");
module_param(क्रमceCRTC, पूर्णांक, 0);
MODULE_PARM_DESC(क्रमceCRTC,
		 "Forces usage of a particular CRTC in case autodetection "
		 "fails. (0 or 1) (default=autodetect)");
module_param(vram, पूर्णांक, 0);
MODULE_PARM_DESC(vram,
		 "amount of framebuffer memory to remap in MiB"
		 "(default=0 - remap entire memory)");
module_param(mode_option, अक्षरp, 0);
MODULE_PARM_DESC(mode_option, "Specify initial video mode");
module_param(bpp, पूर्णांक, 0);
MODULE_PARM_DESC(bpp, "pixel width in bits"
		 "(default=8)");
module_param(reverse_i2c, पूर्णांक, 0);
MODULE_PARM_DESC(reverse_i2c, "reverse port assignment of the i2c bus");
module_param(nomtrr, bool, false);
MODULE_PARM_DESC(nomtrr, "Disables MTRR support (0 or 1=disabled) "
		 "(default=0)");

MODULE_AUTHOR("Antonino Daplas");
MODULE_DESCRIPTION("Framebuffer driver for nVidia graphics chipset");
MODULE_LICENSE("GPL");
