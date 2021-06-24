<शैली गुरु>
/*
 * linux/drivers/video/fbmon.c
 *
 * Copyright (C) 2002 James Simmons <jsimmons@users.sf.net>
 *
 * Credits:
 *
 * The EDID Parser is a conglomeration from the following sources:
 *
 *   1. SciTech SNAP Graphics Architecture
 *      Copyright (C) 1991-2002 SciTech Software, Inc. All rights reserved.
 *
 *   2. XFree86 4.3.0, पूर्णांकerpret_edid.c
 *      Copyright 1998 by Egbert Eich <Egbert.Eich@Physik.TU-Darmstadt.DE>
 *
 *   3. John Fremlin <vii@users.sourceक्रमge.net> and
 *      Ani Joshi <ajoshi@unixbox.com>
 *
 * Generalized Timing Formula is derived from:
 *
 *      GTF Spपढ़ोsheet by Andy Morrish (1/5/97)
 *      available at https://www.vesa.org
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 *
 */
#समावेश <linux/fb.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <video/edid.h>
#समावेश <video/of_videomode.h>
#समावेश <video/videomode.h>
#समावेश "../edid.h"

/*
 * EDID parser
 */

#अघोषित DEBUG  /* define this क्रम verbose EDID parsing output */

#अगर_घोषित DEBUG
#घोषणा DPRINTK(fmt, args...) prपूर्णांकk(fmt,## args)
#अन्यथा
#घोषणा DPRINTK(fmt, args...) no_prपूर्णांकk(fmt, ##args)
#पूर्ण_अगर

#घोषणा FBMON_FIX_HEADER  1
#घोषणा FBMON_FIX_INPUT   2
#घोषणा FBMON_FIX_TIMINGS 3

#अगर_घोषित CONFIG_FB_MODE_HELPERS
काष्ठा broken_edid अणु
	u8  manufacturer[4];
	u32 model;
	u32 fix;
पूर्ण;

अटल स्थिर काष्ठा broken_edid brokendb[] = अणु
	/* DEC FR-PCXAV-YZ */
	अणु
		.manufacturer = "DEC",
		.model        = 0x073a,
		.fix          = FBMON_FIX_HEADER,
	पूर्ण,
	/* ViewSonic PF775a */
	अणु
		.manufacturer = "VSC",
		.model        = 0x5a44,
		.fix          = FBMON_FIX_INPUT,
	पूर्ण,
	/* Sharp UXGA? */
	अणु
		.manufacturer = "SHP",
		.model        = 0x138e,
		.fix          = FBMON_FIX_TIMINGS,
	पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर edid_v1_header[] = अणु 0x00, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0x00
पूर्ण;

अटल व्योम copy_string(अचिन्हित अक्षर *c, अचिन्हित अक्षर *s)
अणु
  पूर्णांक i;
  c = c + 5;
  क्रम (i = 0; (i < 13 && *c != 0x0A); i++)
    *(s++) = *(c++);
  *s = 0;
  जबतक (i-- && (*--s == 0x20)) *s = 0;
पूर्ण

अटल पूर्णांक edid_is_serial_block(अचिन्हित अक्षर *block)
अणु
	अगर ((block[0] == 0x00) && (block[1] == 0x00) &&
	    (block[2] == 0x00) && (block[3] == 0xff) &&
	    (block[4] == 0x00))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक edid_is_ascii_block(अचिन्हित अक्षर *block)
अणु
	अगर ((block[0] == 0x00) && (block[1] == 0x00) &&
	    (block[2] == 0x00) && (block[3] == 0xfe) &&
	    (block[4] == 0x00))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक edid_is_limits_block(अचिन्हित अक्षर *block)
अणु
	अगर ((block[0] == 0x00) && (block[1] == 0x00) &&
	    (block[2] == 0x00) && (block[3] == 0xfd) &&
	    (block[4] == 0x00))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक edid_is_monitor_block(अचिन्हित अक्षर *block)
अणु
	अगर ((block[0] == 0x00) && (block[1] == 0x00) &&
	    (block[2] == 0x00) && (block[3] == 0xfc) &&
	    (block[4] == 0x00))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक edid_is_timing_block(अचिन्हित अक्षर *block)
अणु
	अगर ((block[0] != 0x00) || (block[1] != 0x00) ||
	    (block[2] != 0x00) || (block[4] != 0x00))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक check_edid(अचिन्हित अक्षर *edid)
अणु
	अचिन्हित अक्षर *block = edid + ID_MANUFACTURER_NAME, manufacturer[4];
	अचिन्हित अक्षर *b;
	u32 model;
	पूर्णांक i, fix = 0, ret = 0;

	manufacturer[0] = ((block[0] & 0x7c) >> 2) + '@';
	manufacturer[1] = ((block[0] & 0x03) << 3) +
		((block[1] & 0xe0) >> 5) + '@';
	manufacturer[2] = (block[1] & 0x1f) + '@';
	manufacturer[3] = 0;
	model = block[2] + (block[3] << 8);

	क्रम (i = 0; i < ARRAY_SIZE(brokendb); i++) अणु
		अगर (!म_भेदन(manufacturer, brokendb[i].manufacturer, 4) &&
			brokendb[i].model == model) अणु
			fix = brokendb[i].fix;
			अवरोध;
		पूर्ण
	पूर्ण

	चयन (fix) अणु
	हाल FBMON_FIX_HEADER:
		क्रम (i = 0; i < 8; i++) अणु
			अगर (edid[i] != edid_v1_header[i]) अणु
				ret = fix;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल FBMON_FIX_INPUT:
		b = edid + EDID_STRUCT_DISPLAY;
		/* Only अगर display is GTF capable will
		   the input type be reset to analog */
		अगर (b[4] & 0x01 && b[0] & 0x80)
			ret = fix;
		अवरोध;
	हाल FBMON_FIX_TIMINGS:
		b = edid + DETAILED_TIMING_DESCRIPTIONS_START;
		ret = fix;

		क्रम (i = 0; i < 4; i++) अणु
			अगर (edid_is_limits_block(b)) अणु
				ret = 0;
				अवरोध;
			पूर्ण

			b += DETAILED_TIMING_DESCRIPTION_SIZE;
		पूर्ण

		अवरोध;
	पूर्ण

	अगर (ret)
		prपूर्णांकk("fbmon: The EDID Block of "
		       "Manufacturer: %s Model: 0x%x is known to "
		       "be broken,\n",  manufacturer, model);

	वापस ret;
पूर्ण

अटल व्योम fix_edid(अचिन्हित अक्षर *edid, पूर्णांक fix)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर *b, csum = 0;

	चयन (fix) अणु
	हाल FBMON_FIX_HEADER:
		prपूर्णांकk("fbmon: trying a header reconstruct\n");
		स_नकल(edid, edid_v1_header, 8);
		अवरोध;
	हाल FBMON_FIX_INPUT:
		prपूर्णांकk("fbmon: trying to fix input type\n");
		b = edid + EDID_STRUCT_DISPLAY;
		b[0] &= ~0x80;
		edid[127] += 0x80;
		अवरोध;
	हाल FBMON_FIX_TIMINGS:
		prपूर्णांकk("fbmon: trying to fix monitor timings\n");
		b = edid + DETAILED_TIMING_DESCRIPTIONS_START;
		क्रम (i = 0; i < 4; i++) अणु
			अगर (!(edid_is_serial_block(b) ||
			      edid_is_ascii_block(b) ||
			      edid_is_monitor_block(b) ||
			      edid_is_timing_block(b))) अणु
				b[0] = 0x00;
				b[1] = 0x00;
				b[2] = 0x00;
				b[3] = 0xfd;
				b[4] = 0x00;
				b[5] = 60;   /* vfmin */
				b[6] = 60;   /* vfmax */
				b[7] = 30;   /* hfmin */
				b[8] = 75;   /* hfmax */
				b[9] = 17;   /* pixघड़ी - 170 MHz*/
				b[10] = 0;   /* GTF */
				अवरोध;
			पूर्ण

			b += DETAILED_TIMING_DESCRIPTION_SIZE;
		पूर्ण

		क्रम (i = 0; i < EDID_LENGTH - 1; i++)
			csum += edid[i];

		edid[127] = 256 - csum;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक edid_checksum(अचिन्हित अक्षर *edid)
अणु
	अचिन्हित अक्षर csum = 0, all_null = 0;
	पूर्णांक i, err = 0, fix = check_edid(edid);

	अगर (fix)
		fix_edid(edid, fix);

	क्रम (i = 0; i < EDID_LENGTH; i++) अणु
		csum += edid[i];
		all_null |= edid[i];
	पूर्ण

	अगर (csum == 0x00 && all_null) अणु
		/* checksum passed, everything's good */
		err = 1;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक edid_check_header(अचिन्हित अक्षर *edid)
अणु
	पूर्णांक i, err = 1, fix = check_edid(edid);

	अगर (fix)
		fix_edid(edid, fix);

	क्रम (i = 0; i < 8; i++) अणु
		अगर (edid[i] != edid_v1_header[i])
			err = 0;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम parse_venकरोr_block(अचिन्हित अक्षर *block, काष्ठा fb_monspecs *specs)
अणु
	specs->manufacturer[0] = ((block[0] & 0x7c) >> 2) + '@';
	specs->manufacturer[1] = ((block[0] & 0x03) << 3) +
		((block[1] & 0xe0) >> 5) + '@';
	specs->manufacturer[2] = (block[1] & 0x1f) + '@';
	specs->manufacturer[3] = 0;
	specs->model = block[2] + (block[3] << 8);
	specs->serial = block[4] + (block[5] << 8) +
	       (block[6] << 16) + (block[7] << 24);
	specs->year = block[9] + 1990;
	specs->week = block[8];
	DPRINTK("   Manufacturer: %s\n", specs->manufacturer);
	DPRINTK("   Model: %x\n", specs->model);
	DPRINTK("   Serial#: %u\n", specs->serial);
	DPRINTK("   Year: %u Week %u\n", specs->year, specs->week);
पूर्ण

अटल व्योम get_dpms_capabilities(अचिन्हित अक्षर flags,
				  काष्ठा fb_monspecs *specs)
अणु
	specs->dpms = 0;
	अगर (flags & DPMS_ACTIVE_OFF)
		specs->dpms |= FB_DPMS_ACTIVE_OFF;
	अगर (flags & DPMS_SUSPEND)
		specs->dpms |= FB_DPMS_SUSPEND;
	अगर (flags & DPMS_STANDBY)
		specs->dpms |= FB_DPMS_STANDBY;
	DPRINTK("      DPMS: Active %s, Suspend %s, Standby %s\n",
	       (flags & DPMS_ACTIVE_OFF) ? "yes" : "no",
	       (flags & DPMS_SUSPEND)    ? "yes" : "no",
	       (flags & DPMS_STANDBY)    ? "yes" : "no");
पूर्ण

अटल व्योम get_chroma(अचिन्हित अक्षर *block, काष्ठा fb_monspecs *specs)
अणु
	पूर्णांक पंचांगp;

	DPRINTK("      Chroma\n");
	/* Chromaticity data */
	पंचांगp = ((block[5] & (3 << 6)) >> 6) | (block[0x7] << 2);
	पंचांगp *= 1000;
	पंचांगp += 512;
	specs->chroma.redx = पंचांगp/1024;
	DPRINTK("         RedX:     0.%03d ", specs->chroma.redx);

	पंचांगp = ((block[5] & (3 << 4)) >> 4) | (block[0x8] << 2);
	पंचांगp *= 1000;
	पंचांगp += 512;
	specs->chroma.redy = पंचांगp/1024;
	DPRINTK("RedY:     0.%03d\n", specs->chroma.redy);

	पंचांगp = ((block[5] & (3 << 2)) >> 2) | (block[0x9] << 2);
	पंचांगp *= 1000;
	पंचांगp += 512;
	specs->chroma.greenx = पंचांगp/1024;
	DPRINTK("         GreenX:   0.%03d ", specs->chroma.greenx);

	पंचांगp = (block[5] & 3) | (block[0xa] << 2);
	पंचांगp *= 1000;
	पंचांगp += 512;
	specs->chroma.greeny = पंचांगp/1024;
	DPRINTK("GreenY:   0.%03d\n", specs->chroma.greeny);

	पंचांगp = ((block[6] & (3 << 6)) >> 6) | (block[0xb] << 2);
	पंचांगp *= 1000;
	पंचांगp += 512;
	specs->chroma.bluex = पंचांगp/1024;
	DPRINTK("         BlueX:    0.%03d ", specs->chroma.bluex);

	पंचांगp = ((block[6] & (3 << 4)) >> 4) | (block[0xc] << 2);
	पंचांगp *= 1000;
	पंचांगp += 512;
	specs->chroma.bluey = पंचांगp/1024;
	DPRINTK("BlueY:    0.%03d\n", specs->chroma.bluey);

	पंचांगp = ((block[6] & (3 << 2)) >> 2) | (block[0xd] << 2);
	पंचांगp *= 1000;
	पंचांगp += 512;
	specs->chroma.whitex = पंचांगp/1024;
	DPRINTK("         WhiteX:   0.%03d ", specs->chroma.whitex);

	पंचांगp = (block[6] & 3) | (block[0xe] << 2);
	पंचांगp *= 1000;
	पंचांगp += 512;
	specs->chroma.whitey = पंचांगp/1024;
	DPRINTK("WhiteY:   0.%03d\n", specs->chroma.whitey);
पूर्ण

अटल व्योम calc_mode_timings(पूर्णांक xres, पूर्णांक yres, पूर्णांक refresh,
			      काष्ठा fb_videomode *mode)
अणु
	काष्ठा fb_var_screeninfo *var;

	var = kzalloc(माप(काष्ठा fb_var_screeninfo), GFP_KERNEL);

	अगर (var) अणु
		var->xres = xres;
		var->yres = yres;
		fb_get_mode(FB_VSYNCTIMINGS | FB_IGNOREMON,
			    refresh, var, शून्य);
		mode->xres = xres;
		mode->yres = yres;
		mode->pixघड़ी = var->pixघड़ी;
		mode->refresh = refresh;
		mode->left_margin = var->left_margin;
		mode->right_margin = var->right_margin;
		mode->upper_margin = var->upper_margin;
		mode->lower_margin = var->lower_margin;
		mode->hsync_len = var->hsync_len;
		mode->vsync_len = var->vsync_len;
		mode->vmode = 0;
		mode->sync = 0;
		kमुक्त(var);
	पूर्ण
पूर्ण

अटल पूर्णांक get_est_timing(अचिन्हित अक्षर *block, काष्ठा fb_videomode *mode)
अणु
	पूर्णांक num = 0;
	अचिन्हित अक्षर c;

	c = block[0];
	अगर (c&0x80) अणु
		calc_mode_timings(720, 400, 70, &mode[num]);
		mode[num++].flag = FB_MODE_IS_CALCULATED;
		DPRINTK("      720x400@70Hz\n");
	पूर्ण
	अगर (c&0x40) अणु
		calc_mode_timings(720, 400, 88, &mode[num]);
		mode[num++].flag = FB_MODE_IS_CALCULATED;
		DPRINTK("      720x400@88Hz\n");
	पूर्ण
	अगर (c&0x20) अणु
		mode[num++] = vesa_modes[3];
		DPRINTK("      640x480@60Hz\n");
	पूर्ण
	अगर (c&0x10) अणु
		calc_mode_timings(640, 480, 67, &mode[num]);
		mode[num++].flag = FB_MODE_IS_CALCULATED;
		DPRINTK("      640x480@67Hz\n");
	पूर्ण
	अगर (c&0x08) अणु
		mode[num++] = vesa_modes[4];
		DPRINTK("      640x480@72Hz\n");
	पूर्ण
	अगर (c&0x04) अणु
		mode[num++] = vesa_modes[5];
		DPRINTK("      640x480@75Hz\n");
	पूर्ण
	अगर (c&0x02) अणु
		mode[num++] = vesa_modes[7];
		DPRINTK("      800x600@56Hz\n");
	पूर्ण
	अगर (c&0x01) अणु
		mode[num++] = vesa_modes[8];
		DPRINTK("      800x600@60Hz\n");
	पूर्ण

	c = block[1];
	अगर (c&0x80) अणु
		mode[num++] = vesa_modes[9];
		DPRINTK("      800x600@72Hz\n");
	पूर्ण
	अगर (c&0x40) अणु
		mode[num++] = vesa_modes[10];
		DPRINTK("      800x600@75Hz\n");
	पूर्ण
	अगर (c&0x20) अणु
		calc_mode_timings(832, 624, 75, &mode[num]);
		mode[num++].flag = FB_MODE_IS_CALCULATED;
		DPRINTK("      832x624@75Hz\n");
	पूर्ण
	अगर (c&0x10) अणु
		mode[num++] = vesa_modes[12];
		DPRINTK("      1024x768@87Hz Interlaced\n");
	पूर्ण
	अगर (c&0x08) अणु
		mode[num++] = vesa_modes[13];
		DPRINTK("      1024x768@60Hz\n");
	पूर्ण
	अगर (c&0x04) अणु
		mode[num++] = vesa_modes[14];
		DPRINTK("      1024x768@70Hz\n");
	पूर्ण
	अगर (c&0x02) अणु
		mode[num++] = vesa_modes[15];
		DPRINTK("      1024x768@75Hz\n");
	पूर्ण
	अगर (c&0x01) अणु
		mode[num++] = vesa_modes[21];
		DPRINTK("      1280x1024@75Hz\n");
	पूर्ण
	c = block[2];
	अगर (c&0x80) अणु
		mode[num++] = vesa_modes[17];
		DPRINTK("      1152x870@75Hz\n");
	पूर्ण
	DPRINTK("      Manufacturer's mask: %x\n",c&0x7F);
	वापस num;
पूर्ण

अटल पूर्णांक get_std_timing(अचिन्हित अक्षर *block, काष्ठा fb_videomode *mode,
			  पूर्णांक ver, पूर्णांक rev, स्थिर काष्ठा fb_monspecs *specs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < DMT_SIZE; i++) अणु
		u32 std_2byte_code = block[0] << 8 | block[1];
		अगर (std_2byte_code == dmt_modes[i].std_2byte_code)
			अवरोध;
	पूर्ण

	अगर (i < DMT_SIZE && dmt_modes[i].mode) अणु
		/* DMT mode found */
		*mode = *dmt_modes[i].mode;
		mode->flag |= FB_MODE_IS_STANDARD;
		DPRINTK("        DMT id=%d\n", dmt_modes[i].dmt_id);

	पूर्ण अन्यथा अणु
		पूर्णांक xres, yres = 0, refresh, ratio;

		xres = (block[0] + 31) * 8;
		अगर (xres <= 256)
			वापस 0;

		ratio = (block[1] & 0xc0) >> 6;
		चयन (ratio) अणु
		हाल 0:
			/* in EDID 1.3 the meaning of 0 changed to 16:10 (prior 1:1) */
			अगर (ver < 1 || (ver == 1 && rev < 3))
				yres = xres;
			अन्यथा
				yres = (xres * 10)/16;
			अवरोध;
		हाल 1:
			yres = (xres * 3)/4;
			अवरोध;
		हाल 2:
			yres = (xres * 4)/5;
			अवरोध;
		हाल 3:
			yres = (xres * 9)/16;
			अवरोध;
		पूर्ण
		refresh = (block[1] & 0x3f) + 60;
		DPRINTK("      %dx%d@%dHz\n", xres, yres, refresh);

		calc_mode_timings(xres, yres, refresh, mode);
	पूर्ण

	/* Check the mode we got is within valid spec of the monitor */
	अगर (specs && specs->dclkmax
	    && PICOS2KHZ(mode->pixघड़ी) * 1000 > specs->dclkmax) अणु
		DPRINTK("        mode exceed max DCLK\n");
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक get_dst_timing(अचिन्हित अक्षर *block, काष्ठा fb_videomode *mode,
			  पूर्णांक ver, पूर्णांक rev, स्थिर काष्ठा fb_monspecs *specs)
अणु
	पूर्णांक j, num = 0;

	क्रम (j = 0; j < 6; j++, block += STD_TIMING_DESCRIPTION_SIZE)
		num += get_std_timing(block, &mode[num], ver, rev, specs);

	वापस num;
पूर्ण

अटल व्योम get_detailed_timing(अचिन्हित अक्षर *block,
				काष्ठा fb_videomode *mode)
अणु
	mode->xres = H_ACTIVE;
	mode->yres = V_ACTIVE;
	mode->pixघड़ी = PIXEL_CLOCK;
	mode->pixघड़ी /= 1000;
	mode->pixघड़ी = KHZ2PICOS(mode->pixघड़ी);
	mode->right_margin = H_SYNC_OFFSET;
	mode->left_margin = (H_ACTIVE + H_BLANKING) -
		(H_ACTIVE + H_SYNC_OFFSET + H_SYNC_WIDTH);
	mode->upper_margin = V_BLANKING - V_SYNC_OFFSET -
		V_SYNC_WIDTH;
	mode->lower_margin = V_SYNC_OFFSET;
	mode->hsync_len = H_SYNC_WIDTH;
	mode->vsync_len = V_SYNC_WIDTH;
	अगर (HSYNC_POSITIVE)
		mode->sync |= FB_SYNC_HOR_HIGH_ACT;
	अगर (VSYNC_POSITIVE)
		mode->sync |= FB_SYNC_VERT_HIGH_ACT;
	mode->refresh = PIXEL_CLOCK/((H_ACTIVE + H_BLANKING) *
				     (V_ACTIVE + V_BLANKING));
	अगर (INTERLACED) अणु
		mode->yres *= 2;
		mode->upper_margin *= 2;
		mode->lower_margin *= 2;
		mode->vsync_len *= 2;
		mode->vmode |= FB_VMODE_INTERLACED;
	पूर्ण
	mode->flag = FB_MODE_IS_DETAILED;

	DPRINTK("      %d MHz ",  PIXEL_CLOCK/1000000);
	DPRINTK("%d %d %d %d ", H_ACTIVE, H_ACTIVE + H_SYNC_OFFSET,
	       H_ACTIVE + H_SYNC_OFFSET + H_SYNC_WIDTH, H_ACTIVE + H_BLANKING);
	DPRINTK("%d %d %d %d ", V_ACTIVE, V_ACTIVE + V_SYNC_OFFSET,
	       V_ACTIVE + V_SYNC_OFFSET + V_SYNC_WIDTH, V_ACTIVE + V_BLANKING);
	DPRINTK("%sHSync %sVSync\n\n", (HSYNC_POSITIVE) ? "+" : "-",
	       (VSYNC_POSITIVE) ? "+" : "-");
पूर्ण

/**
 * fb_create_modedb - create video mode database
 * @edid: EDID data
 * @dbsize: database size
 * @specs: monitor specअगरications, may be शून्य
 *
 * RETURNS: काष्ठा fb_videomode, @dbsize contains length of database
 *
 * DESCRIPTION:
 * This function builds a mode database using the contents of the EDID
 * data
 */
अटल काष्ठा fb_videomode *fb_create_modedb(अचिन्हित अक्षर *edid, पूर्णांक *dbsize,
					     स्थिर काष्ठा fb_monspecs *specs)
अणु
	काष्ठा fb_videomode *mode, *m;
	अचिन्हित अक्षर *block;
	पूर्णांक num = 0, i, first = 1;
	पूर्णांक ver, rev;

	mode = kसुस्मृति(50, माप(काष्ठा fb_videomode), GFP_KERNEL);
	अगर (mode == शून्य)
		वापस शून्य;

	अगर (edid == शून्य || !edid_checksum(edid) ||
	    !edid_check_header(edid)) अणु
		kमुक्त(mode);
		वापस शून्य;
	पूर्ण

	ver = edid[EDID_STRUCT_VERSION];
	rev = edid[EDID_STRUCT_REVISION];

	*dbsize = 0;

	DPRINTK("   Detailed Timings\n");
	block = edid + DETAILED_TIMING_DESCRIPTIONS_START;
	क्रम (i = 0; i < 4; i++, block+= DETAILED_TIMING_DESCRIPTION_SIZE) अणु
		अगर (!(block[0] == 0x00 && block[1] == 0x00)) अणु
			get_detailed_timing(block, &mode[num]);
			अगर (first) अणु
			        mode[num].flag |= FB_MODE_IS_FIRST;
				first = 0;
			पूर्ण
			num++;
		पूर्ण
	पूर्ण

	DPRINTK("   Supported VESA Modes\n");
	block = edid + ESTABLISHED_TIMING_1;
	num += get_est_timing(block, &mode[num]);

	DPRINTK("   Standard Timings\n");
	block = edid + STD_TIMING_DESCRIPTIONS_START;
	क्रम (i = 0; i < STD_TIMING; i++, block += STD_TIMING_DESCRIPTION_SIZE)
		num += get_std_timing(block, &mode[num], ver, rev, specs);

	block = edid + DETAILED_TIMING_DESCRIPTIONS_START;
	क्रम (i = 0; i < 4; i++, block+= DETAILED_TIMING_DESCRIPTION_SIZE) अणु
		अगर (block[0] == 0x00 && block[1] == 0x00 && block[3] == 0xfa)
			num += get_dst_timing(block + 5, &mode[num],
					      ver, rev, specs);
	पूर्ण

	/* Yikes, EDID data is totally useless */
	अगर (!num) अणु
		kमुक्त(mode);
		वापस शून्य;
	पूर्ण

	*dbsize = num;
	m = kदो_स्मृति_array(num, माप(काष्ठा fb_videomode), GFP_KERNEL);
	अगर (!m)
		वापस mode;
	स_हटाओ(m, mode, num * माप(काष्ठा fb_videomode));
	kमुक्त(mode);
	वापस m;
पूर्ण

/**
 * fb_destroy_modedb - destroys mode database
 * @modedb: mode database to destroy
 *
 * DESCRIPTION:
 * Destroy mode database created by fb_create_modedb
 */
व्योम fb_destroy_modedb(काष्ठा fb_videomode *modedb)
अणु
	kमुक्त(modedb);
पूर्ण

अटल पूर्णांक fb_get_monitor_limits(अचिन्हित अक्षर *edid, काष्ठा fb_monspecs *specs)
अणु
	पूर्णांक i, retval = 1;
	अचिन्हित अक्षर *block;

	block = edid + DETAILED_TIMING_DESCRIPTIONS_START;

	DPRINTK("      Monitor Operating Limits: ");

	क्रम (i = 0; i < 4; i++, block += DETAILED_TIMING_DESCRIPTION_SIZE) अणु
		अगर (edid_is_limits_block(block)) अणु
			specs->hfmin = H_MIN_RATE * 1000;
			specs->hfmax = H_MAX_RATE * 1000;
			specs->vfmin = V_MIN_RATE;
			specs->vfmax = V_MAX_RATE;
			specs->dclkmax = MAX_PIXEL_CLOCK * 1000000;
			specs->gtf = (GTF_SUPPORT) ? 1 : 0;
			retval = 0;
			DPRINTK("From EDID\n");
			अवरोध;
		पूर्ण
	पूर्ण

	/* estimate monitor limits based on modes supported */
	अगर (retval) अणु
		काष्ठा fb_videomode *modes, *mode;
		पूर्णांक num_modes, hz, hscan, pixघड़ी;
		पूर्णांक vtotal, htotal;

		modes = fb_create_modedb(edid, &num_modes, specs);
		अगर (!modes) अणु
			DPRINTK("None Available\n");
			वापस 1;
		पूर्ण

		retval = 0;
		क्रम (i = 0; i < num_modes; i++) अणु
			mode = &modes[i];
			pixघड़ी = PICOS2KHZ(modes[i].pixघड़ी) * 1000;
			htotal = mode->xres + mode->right_margin + mode->hsync_len
				+ mode->left_margin;
			vtotal = mode->yres + mode->lower_margin + mode->vsync_len
				+ mode->upper_margin;

			अगर (mode->vmode & FB_VMODE_INTERLACED)
				vtotal /= 2;

			अगर (mode->vmode & FB_VMODE_DOUBLE)
				vtotal *= 2;

			hscan = (pixघड़ी + htotal / 2) / htotal;
			hscan = (hscan + 500) / 1000 * 1000;
			hz = (hscan + vtotal / 2) / vtotal;

			अगर (specs->dclkmax == 0 || specs->dclkmax < pixघड़ी)
				specs->dclkmax = pixघड़ी;

			अगर (specs->dclkmin == 0 || specs->dclkmin > pixघड़ी)
				specs->dclkmin = pixघड़ी;

			अगर (specs->hfmax == 0 || specs->hfmax < hscan)
				specs->hfmax = hscan;

			अगर (specs->hfmin == 0 || specs->hfmin > hscan)
				specs->hfmin = hscan;

			अगर (specs->vfmax == 0 || specs->vfmax < hz)
				specs->vfmax = hz;

			अगर (specs->vfmin == 0 || specs->vfmin > hz)
				specs->vfmin = hz;
		पूर्ण
		DPRINTK("Extrapolated\n");
		fb_destroy_modedb(modes);
	पूर्ण
	DPRINTK("           H: %d-%dKHz V: %d-%dHz DCLK: %dMHz\n",
		specs->hfmin/1000, specs->hfmax/1000, specs->vfmin,
		specs->vfmax, specs->dclkmax/1000000);
	वापस retval;
पूर्ण

अटल व्योम get_monspecs(अचिन्हित अक्षर *edid, काष्ठा fb_monspecs *specs)
अणु
	अचिन्हित अक्षर c, *block;

	block = edid + EDID_STRUCT_DISPLAY;

	fb_get_monitor_limits(edid, specs);

	c = block[0] & 0x80;
	specs->input = 0;
	अगर (c) अणु
		specs->input |= FB_DISP_DDI;
		DPRINTK("      Digital Display Input");
	पूर्ण अन्यथा अणु
		DPRINTK("      Analog Display Input: Input Voltage - ");
		चयन ((block[0] & 0x60) >> 5) अणु
		हाल 0:
			DPRINTK("0.700V/0.300V");
			specs->input |= FB_DISP_ANA_700_300;
			अवरोध;
		हाल 1:
			DPRINTK("0.714V/0.286V");
			specs->input |= FB_DISP_ANA_714_286;
			अवरोध;
		हाल 2:
			DPRINTK("1.000V/0.400V");
			specs->input |= FB_DISP_ANA_1000_400;
			अवरोध;
		हाल 3:
			DPRINTK("0.700V/0.000V");
			specs->input |= FB_DISP_ANA_700_000;
			अवरोध;
		पूर्ण
	पूर्ण
	DPRINTK("\n      Sync: ");
	c = block[0] & 0x10;
	अगर (c)
		DPRINTK("      Configurable signal level\n");
	c = block[0] & 0x0f;
	specs->संकेत = 0;
	अगर (c & 0x10) अणु
		DPRINTK("Blank to Blank ");
		specs->संकेत |= FB_SIGNAL_BLANK_BLANK;
	पूर्ण
	अगर (c & 0x08) अणु
		DPRINTK("Separate ");
		specs->संकेत |= FB_SIGNAL_SEPARATE;
	पूर्ण
	अगर (c & 0x04) अणु
		DPRINTK("Composite ");
		specs->संकेत |= FB_SIGNAL_COMPOSITE;
	पूर्ण
	अगर (c & 0x02) अणु
		DPRINTK("Sync on Green ");
		specs->संकेत |= FB_SIGNAL_SYNC_ON_GREEN;
	पूर्ण
	अगर (c & 0x01) अणु
		DPRINTK("Serration on ");
		specs->संकेत |= FB_SIGNAL_SERRATION_ON;
	पूर्ण
	DPRINTK("\n");
	specs->max_x = block[1];
	specs->max_y = block[2];
	DPRINTK("      Max H-size in cm: ");
	अगर (specs->max_x)
		DPRINTK("%d\n", specs->max_x);
	अन्यथा
		DPRINTK("variable\n");
	DPRINTK("      Max V-size in cm: ");
	अगर (specs->max_y)
		DPRINTK("%d\n", specs->max_y);
	अन्यथा
		DPRINTK("variable\n");

	c = block[3];
	specs->gamma = c+100;
	DPRINTK("      Gamma: ");
	DPRINTK("%d.%d\n", specs->gamma/100, specs->gamma % 100);

	get_dpms_capabilities(block[4], specs);

	चयन ((block[4] & 0x18) >> 3) अणु
	हाल 0:
		DPRINTK("      Monochrome/Grayscale\n");
		specs->input |= FB_DISP_MONO;
		अवरोध;
	हाल 1:
		DPRINTK("      RGB Color Display\n");
		specs->input |= FB_DISP_RGB;
		अवरोध;
	हाल 2:
		DPRINTK("      Non-RGB Multicolor Display\n");
		specs->input |= FB_DISP_MULTI;
		अवरोध;
	शेष:
		DPRINTK("      Unknown\n");
		specs->input |= FB_DISP_UNKNOWN;
		अवरोध;
	पूर्ण

	get_chroma(block, specs);

	specs->misc = 0;
	c = block[4] & 0x7;
	अगर (c & 0x04) अणु
		DPRINTK("      Default color format is primary\n");
		specs->misc |= FB_MISC_PRIM_COLOR;
	पूर्ण
	अगर (c & 0x02) अणु
		DPRINTK("      First DETAILED Timing is preferred\n");
		specs->misc |= FB_MISC_1ST_DETAIL;
	पूर्ण
	अगर (c & 0x01) अणु
		prपूर्णांकk("      Display is GTF capable\n");
		specs->gtf = 1;
	पूर्ण
पूर्ण

पूर्णांक fb_parse_edid(अचिन्हित अक्षर *edid, काष्ठा fb_var_screeninfo *var)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर *block;

	अगर (edid == शून्य || var == शून्य)
		वापस 1;

	अगर (!(edid_checksum(edid)))
		वापस 1;

	अगर (!(edid_check_header(edid)))
		वापस 1;

	block = edid + DETAILED_TIMING_DESCRIPTIONS_START;

	क्रम (i = 0; i < 4; i++, block += DETAILED_TIMING_DESCRIPTION_SIZE) अणु
		अगर (edid_is_timing_block(block)) अणु
			var->xres = var->xres_भव = H_ACTIVE;
			var->yres = var->yres_भव = V_ACTIVE;
			var->height = var->width = 0;
			var->right_margin = H_SYNC_OFFSET;
			var->left_margin = (H_ACTIVE + H_BLANKING) -
				(H_ACTIVE + H_SYNC_OFFSET + H_SYNC_WIDTH);
			var->upper_margin = V_BLANKING - V_SYNC_OFFSET -
				V_SYNC_WIDTH;
			var->lower_margin = V_SYNC_OFFSET;
			var->hsync_len = H_SYNC_WIDTH;
			var->vsync_len = V_SYNC_WIDTH;
			var->pixघड़ी = PIXEL_CLOCK;
			var->pixघड़ी /= 1000;
			var->pixघड़ी = KHZ2PICOS(var->pixघड़ी);

			अगर (HSYNC_POSITIVE)
				var->sync |= FB_SYNC_HOR_HIGH_ACT;
			अगर (VSYNC_POSITIVE)
				var->sync |= FB_SYNC_VERT_HIGH_ACT;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

व्योम fb_edid_to_monspecs(अचिन्हित अक्षर *edid, काष्ठा fb_monspecs *specs)
अणु
	अचिन्हित अक्षर *block;
	पूर्णांक i, found = 0;

	अगर (edid == शून्य)
		वापस;

	अगर (!(edid_checksum(edid)))
		वापस;

	अगर (!(edid_check_header(edid)))
		वापस;

	स_रखो(specs, 0, माप(काष्ठा fb_monspecs));

	specs->version = edid[EDID_STRUCT_VERSION];
	specs->revision = edid[EDID_STRUCT_REVISION];

	DPRINTK("========================================\n");
	DPRINTK("Display Information (EDID)\n");
	DPRINTK("========================================\n");
	DPRINTK("   EDID Version %d.%d\n", (पूर्णांक) specs->version,
	       (पूर्णांक) specs->revision);

	parse_venकरोr_block(edid + ID_MANUFACTURER_NAME, specs);

	block = edid + DETAILED_TIMING_DESCRIPTIONS_START;
	क्रम (i = 0; i < 4; i++, block += DETAILED_TIMING_DESCRIPTION_SIZE) अणु
		अगर (edid_is_serial_block(block)) अणु
			copy_string(block, specs->serial_no);
			DPRINTK("   Serial Number: %s\n", specs->serial_no);
		पूर्ण अन्यथा अगर (edid_is_ascii_block(block)) अणु
			copy_string(block, specs->ascii);
			DPRINTK("   ASCII Block: %s\n", specs->ascii);
		पूर्ण अन्यथा अगर (edid_is_monitor_block(block)) अणु
			copy_string(block, specs->monitor);
			DPRINTK("   Monitor Name: %s\n", specs->monitor);
		पूर्ण
	पूर्ण

	DPRINTK("   Display Characteristics:\n");
	get_monspecs(edid, specs);

	specs->modedb = fb_create_modedb(edid, &specs->modedb_len, specs);
	अगर (!specs->modedb)
		वापस;

	/*
	 * Workaround क्रम buggy EDIDs that sets that the first
	 * detailed timing is preferred but has not detailed
	 * timing specअगरied
	 */
	क्रम (i = 0; i < specs->modedb_len; i++) अणु
		अगर (specs->modedb[i].flag & FB_MODE_IS_DETAILED) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found)
		specs->misc &= ~FB_MISC_1ST_DETAIL;

	DPRINTK("========================================\n");
पूर्ण

/*
 * VESA Generalized Timing Formula (GTF)
 */

#घोषणा FLYBACK                     550
#घोषणा V_FRONTPORCH                1
#घोषणा H_OFFSET                    40
#घोषणा H_SCALEFACTOR               20
#घोषणा H_BLANKSCALE                128
#घोषणा H_GRADIENT                  600
#घोषणा C_VAL                       30
#घोषणा M_VAL                       300

काष्ठा __fb_timings अणु
	u32 dclk;
	u32 hfreq;
	u32 vfreq;
	u32 hactive;
	u32 vactive;
	u32 hblank;
	u32 vblank;
	u32 htotal;
	u32 vtotal;
पूर्ण;

/**
 * fb_get_vblank - get vertical blank समय
 * @hfreq: horizontal freq
 *
 * DESCRIPTION:
 * vblank = right_margin + vsync_len + left_margin
 *
 *    given: right_margin = 1 (V_FRONTPORCH)
 *           vsync_len    = 3
 *           flyback      = 550
 *
 *                          flyback * hfreq
 *           left_margin  = --------------- - vsync_len
 *                           1000000
 */
अटल u32 fb_get_vblank(u32 hfreq)
अणु
	u32 vblank;

	vblank = (hfreq * FLYBACK)/1000;
	vblank = (vblank + 500)/1000;
	वापस (vblank + V_FRONTPORCH);
पूर्ण

/**
 * fb_get_hblank_by_freq - get horizontal blank समय given hfreq
 * @hfreq: horizontal freq
 * @xres: horizontal resolution in pixels
 *
 * DESCRIPTION:
 *
 *           xres * duty_cycle
 * hblank = ------------------
 *           100 - duty_cycle
 *
 * duty cycle = percent of htotal asचिन्हित to inactive display
 * duty cycle = C - (M/Hfreq)
 *
 * where: C = ((offset - scale factor) * blank_scale)
 *            -------------------------------------- + scale factor
 *                        256
 *        M = blank_scale * gradient
 *
 */
अटल u32 fb_get_hblank_by_hfreq(u32 hfreq, u32 xres)
अणु
	u32 c_val, m_val, duty_cycle, hblank;

	c_val = (((H_OFFSET - H_SCALEFACTOR) * H_BLANKSCALE)/256 +
		 H_SCALEFACTOR) * 1000;
	m_val = (H_BLANKSCALE * H_GRADIENT)/256;
	m_val = (m_val * 1000000)/hfreq;
	duty_cycle = c_val - m_val;
	hblank = (xres * duty_cycle)/(100000 - duty_cycle);
	वापस (hblank);
पूर्ण

/**
 * fb_get_hblank_by_dclk - get horizontal blank समय given pixelघड़ी
 * @dclk: pixelघड़ी in Hz
 * @xres: horizontal resolution in pixels
 *
 * DESCRIPTION:
 *
 *           xres * duty_cycle
 * hblank = ------------------
 *           100 - duty_cycle
 *
 * duty cycle = percent of htotal asचिन्हित to inactive display
 * duty cycle = C - (M * h_period)
 *
 * where: h_period = SQRT(100 - C + (0.4 * xres * M)/dclk) + C - 100
 *                   -----------------------------------------------
 *                                    2 * M
 *        M = 300;
 *        C = 30;
 */
अटल u32 fb_get_hblank_by_dclk(u32 dclk, u32 xres)
अणु
	u32 duty_cycle, h_period, hblank;

	dclk /= 1000;
	h_period = 100 - C_VAL;
	h_period *= h_period;
	h_period += (M_VAL * xres * 2 * 1000)/(5 * dclk);
	h_period *= 10000;

	h_period = पूर्णांक_वर्ग_मूल(h_period);
	h_period -= (100 - C_VAL) * 100;
	h_period *= 1000;
	h_period /= 2 * M_VAL;

	duty_cycle = C_VAL * 1000 - (M_VAL * h_period)/100;
	hblank = (xres * duty_cycle)/(100000 - duty_cycle) + 8;
	hblank &= ~15;
	वापस (hblank);
पूर्ण

/**
 * fb_get_hfreq - estimate hsync
 * @vfreq: vertical refresh rate
 * @yres: vertical resolution
 *
 * DESCRIPTION:
 *
 *          (yres + front_port) * vfreq * 1000000
 * hfreq = -------------------------------------
 *          (1000000 - (vfreq * FLYBACK)
 *
 */

अटल u32 fb_get_hfreq(u32 vfreq, u32 yres)
अणु
	u32 भागisor, hfreq;

	भागisor = (1000000 - (vfreq * FLYBACK))/1000;
	hfreq = (yres + V_FRONTPORCH) * vfreq  * 1000;
	वापस (hfreq/भागisor);
पूर्ण

अटल व्योम fb_timings_vfreq(काष्ठा __fb_timings *timings)
अणु
	timings->hfreq = fb_get_hfreq(timings->vfreq, timings->vactive);
	timings->vblank = fb_get_vblank(timings->hfreq);
	timings->vtotal = timings->vactive + timings->vblank;
	timings->hblank = fb_get_hblank_by_hfreq(timings->hfreq,
						 timings->hactive);
	timings->htotal = timings->hactive + timings->hblank;
	timings->dclk = timings->htotal * timings->hfreq;
पूर्ण

अटल व्योम fb_timings_hfreq(काष्ठा __fb_timings *timings)
अणु
	timings->vblank = fb_get_vblank(timings->hfreq);
	timings->vtotal = timings->vactive + timings->vblank;
	timings->vfreq = timings->hfreq/timings->vtotal;
	timings->hblank = fb_get_hblank_by_hfreq(timings->hfreq,
						 timings->hactive);
	timings->htotal = timings->hactive + timings->hblank;
	timings->dclk = timings->htotal * timings->hfreq;
पूर्ण

अटल व्योम fb_timings_dclk(काष्ठा __fb_timings *timings)
अणु
	timings->hblank = fb_get_hblank_by_dclk(timings->dclk,
						timings->hactive);
	timings->htotal = timings->hactive + timings->hblank;
	timings->hfreq = timings->dclk/timings->htotal;
	timings->vblank = fb_get_vblank(timings->hfreq);
	timings->vtotal = timings->vactive + timings->vblank;
	timings->vfreq = timings->hfreq/timings->vtotal;
पूर्ण

/*
 * fb_get_mode - calculates video mode using VESA GTF
 * @flags: अगर: 0 - maximize vertical refresh rate
 *             1 - vrefresh-driven calculation;
 *             2 - hscan-driven calculation;
 *             3 - pixelघड़ी-driven calculation;
 * @val: depending on @flags, ignored, vrefresh, hsync or pixelघड़ी
 * @var: poपूर्णांकer to fb_var_screeninfo
 * @info: poपूर्णांकer to fb_info
 *
 * DESCRIPTION:
 * Calculates video mode based on monitor specs using VESA GTF.
 * The GTF is best क्रम VESA GTF compliant monitors but is
 * specअगरically क्रमmulated to work क्रम older monitors as well.
 *
 * If @flag==0, the function will attempt to maximize the
 * refresh rate.  Otherwise, it will calculate timings based on
 * the flag and accompanying value.
 *
 * If FB_IGNOREMON bit is set in @flags, monitor specs will be
 * ignored and @var will be filled with the calculated timings.
 *
 * All calculations are based on the VESA GTF Spपढ़ोsheet
 * available at VESA's खुला ftp (https://www.vesa.org).
 *
 * NOTES:
 * The timings generated by the GTF will be dअगरferent from VESA
 * DMT.  It might be a good idea to keep a table of standard
 * VESA modes as well.  The GTF may also not work क्रम some displays,
 * such as, and especially, analog TV.
 *
 * REQUIRES:
 * A valid info->monspecs, otherwise 'safe numbers' will be used.
 */
पूर्णांक fb_get_mode(पूर्णांक flags, u32 val, काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा __fb_timings *timings;
	u32 पूर्णांकerlace = 1, dscan = 1;
	u32 hfmin, hfmax, vfmin, vfmax, dclkmin, dclkmax, err = 0;


	timings = kzalloc(माप(काष्ठा __fb_timings), GFP_KERNEL);

	अगर (!timings)
		वापस -ENOMEM;

	/*
	 * If monspecs are invalid, use values that are enough
	 * क्रम 640x480@60
	 */
	अगर (!info || !info->monspecs.hfmax || !info->monspecs.vfmax ||
	    !info->monspecs.dclkmax ||
	    info->monspecs.hfmax < info->monspecs.hfmin ||
	    info->monspecs.vfmax < info->monspecs.vfmin ||
	    info->monspecs.dclkmax < info->monspecs.dclkmin) अणु
		hfmin = 29000; hfmax = 30000;
		vfmin = 60; vfmax = 60;
		dclkmin = 0; dclkmax = 25000000;
	पूर्ण अन्यथा अणु
		hfmin = info->monspecs.hfmin;
		hfmax = info->monspecs.hfmax;
		vfmin = info->monspecs.vfmin;
		vfmax = info->monspecs.vfmax;
		dclkmin = info->monspecs.dclkmin;
		dclkmax = info->monspecs.dclkmax;
	पूर्ण

	timings->hactive = var->xres;
	timings->vactive = var->yres;
	अगर (var->vmode & FB_VMODE_INTERLACED) अणु
		timings->vactive /= 2;
		पूर्णांकerlace = 2;
	पूर्ण
	अगर (var->vmode & FB_VMODE_DOUBLE) अणु
		timings->vactive *= 2;
		dscan = 2;
	पूर्ण

	चयन (flags & ~FB_IGNOREMON) अणु
	हाल FB_MAXTIMINGS: /* maximize refresh rate */
		timings->hfreq = hfmax;
		fb_timings_hfreq(timings);
		अगर (timings->vfreq > vfmax) अणु
			timings->vfreq = vfmax;
			fb_timings_vfreq(timings);
		पूर्ण
		अगर (timings->dclk > dclkmax) अणु
			timings->dclk = dclkmax;
			fb_timings_dclk(timings);
		पूर्ण
		अवरोध;
	हाल FB_VSYNCTIMINGS: /* vrefresh driven */
		timings->vfreq = val;
		fb_timings_vfreq(timings);
		अवरोध;
	हाल FB_HSYNCTIMINGS: /* hsync driven */
		timings->hfreq = val;
		fb_timings_hfreq(timings);
		अवरोध;
	हाल FB_DCLKTIMINGS: /* pixelघड़ी driven */
		timings->dclk = PICOS2KHZ(val) * 1000;
		fb_timings_dclk(timings);
		अवरोध;
	शेष:
		err = -EINVAL;

	पूर्ण

	अगर (err || (!(flags & FB_IGNOREMON) &&
	    (timings->vfreq < vfmin || timings->vfreq > vfmax ||
	     timings->hfreq < hfmin || timings->hfreq > hfmax ||
	     timings->dclk < dclkmin || timings->dclk > dclkmax))) अणु
		err = -EINVAL;
	पूर्ण अन्यथा अणु
		var->pixघड़ी = KHZ2PICOS(timings->dclk/1000);
		var->hsync_len = (timings->htotal * 8)/100;
		var->right_margin = (timings->hblank/2) - var->hsync_len;
		var->left_margin = timings->hblank - var->right_margin -
			var->hsync_len;
		var->vsync_len = (3 * पूर्णांकerlace)/dscan;
		var->lower_margin = (1 * पूर्णांकerlace)/dscan;
		var->upper_margin = (timings->vblank * पूर्णांकerlace)/dscan -
			(var->vsync_len + var->lower_margin);
	पूर्ण

	kमुक्त(timings);
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_VIDEOMODE_HELPERS
पूर्णांक fb_videomode_from_videomode(स्थिर काष्ठा videomode *vm,
				काष्ठा fb_videomode *fbmode)
अणु
	अचिन्हित पूर्णांक htotal, vtotal;

	fbmode->xres = vm->hactive;
	fbmode->left_margin = vm->hback_porch;
	fbmode->right_margin = vm->hfront_porch;
	fbmode->hsync_len = vm->hsync_len;

	fbmode->yres = vm->vactive;
	fbmode->upper_margin = vm->vback_porch;
	fbmode->lower_margin = vm->vfront_porch;
	fbmode->vsync_len = vm->vsync_len;

	/* prevent भागision by zero in KHZ2PICOS macro */
	fbmode->pixघड़ी = vm->pixelघड़ी ?
			KHZ2PICOS(vm->pixelघड़ी / 1000) : 0;

	fbmode->sync = 0;
	fbmode->vmode = 0;
	अगर (vm->flags & DISPLAY_FLAGS_HSYNC_HIGH)
		fbmode->sync |= FB_SYNC_HOR_HIGH_ACT;
	अगर (vm->flags & DISPLAY_FLAGS_VSYNC_HIGH)
		fbmode->sync |= FB_SYNC_VERT_HIGH_ACT;
	अगर (vm->flags & DISPLAY_FLAGS_INTERLACED)
		fbmode->vmode |= FB_VMODE_INTERLACED;
	अगर (vm->flags & DISPLAY_FLAGS_DOUBLESCAN)
		fbmode->vmode |= FB_VMODE_DOUBLE;
	fbmode->flag = 0;

	htotal = vm->hactive + vm->hfront_porch + vm->hback_porch +
		 vm->hsync_len;
	vtotal = vm->vactive + vm->vfront_porch + vm->vback_porch +
		 vm->vsync_len;
	/* prevent भागision by zero */
	अगर (htotal && vtotal) अणु
		fbmode->refresh = vm->pixelघड़ी / (htotal * vtotal);
	/* a mode must have htotal and vtotal != 0 or it is invalid */
	पूर्ण अन्यथा अणु
		fbmode->refresh = 0;
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fb_videomode_from_videomode);

#अगर_घोषित CONFIG_OF
अटल अंतरभूत व्योम dump_fb_videomode(स्थिर काष्ठा fb_videomode *m)
अणु
	pr_debug("fb_videomode = %ux%u@%uHz (%ukHz) %u %u %u %u %u %u %u %u %u\n",
		 m->xres, m->yres, m->refresh, m->pixघड़ी, m->left_margin,
		 m->right_margin, m->upper_margin, m->lower_margin,
		 m->hsync_len, m->vsync_len, m->sync, m->vmode, m->flag);
पूर्ण

/**
 * of_get_fb_videomode - get a fb_videomode from devicetree
 * @np: device_node with the timing specअगरication
 * @fb: will be set to the वापस value
 * @index: index पूर्णांकo the list of display timings in devicetree
 *
 * DESCRIPTION:
 * This function is expensive and should only be used, अगर only one mode is to be
 * पढ़ो from DT. To get multiple modes start with of_get_display_timings ond
 * work with that instead.
 */
पूर्णांक of_get_fb_videomode(काष्ठा device_node *np, काष्ठा fb_videomode *fb,
			पूर्णांक index)
अणु
	काष्ठा videomode vm;
	पूर्णांक ret;

	ret = of_get_videomode(np, &vm, index);
	अगर (ret)
		वापस ret;

	ret = fb_videomode_from_videomode(&vm, fb);
	अगर (ret)
		वापस ret;

	pr_debug("%pOF: got %dx%d display mode\n",
		np, vm.hactive, vm.vactive);
	dump_fb_videomode(fb);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(of_get_fb_videomode);
#पूर्ण_अगर /* CONFIG_OF */
#पूर्ण_अगर /* CONFIG_VIDEOMODE_HELPERS */

#अन्यथा
पूर्णांक fb_parse_edid(अचिन्हित अक्षर *edid, काष्ठा fb_var_screeninfo *var)
अणु
	वापस 1;
पूर्ण
व्योम fb_edid_to_monspecs(अचिन्हित अक्षर *edid, काष्ठा fb_monspecs *specs)
अणु
पूर्ण
व्योम fb_destroy_modedb(काष्ठा fb_videomode *modedb)
अणु
पूर्ण
पूर्णांक fb_get_mode(पूर्णांक flags, u32 val, काष्ठा fb_var_screeninfo *var,
		काष्ठा fb_info *info)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर /* CONFIG_FB_MODE_HELPERS */

/*
 * fb_validate_mode - validates var against monitor capabilities
 * @var: poपूर्णांकer to fb_var_screeninfo
 * @info: poपूर्णांकer to fb_info
 *
 * DESCRIPTION:
 * Validates video mode against monitor capabilities specअगरied in
 * info->monspecs.
 *
 * REQUIRES:
 * A valid info->monspecs.
 */
पूर्णांक fb_validate_mode(स्थिर काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	u32 hfreq, vfreq, htotal, vtotal, pixघड़ी;
	u32 hfmin, hfmax, vfmin, vfmax, dclkmin, dclkmax;

	/*
	 * If monspecs are invalid, use values that are enough
	 * क्रम 640x480@60
	 */
	अगर (!info->monspecs.hfmax || !info->monspecs.vfmax ||
	    !info->monspecs.dclkmax ||
	    info->monspecs.hfmax < info->monspecs.hfmin ||
	    info->monspecs.vfmax < info->monspecs.vfmin ||
	    info->monspecs.dclkmax < info->monspecs.dclkmin) अणु
		hfmin = 29000; hfmax = 30000;
		vfmin = 60; vfmax = 60;
		dclkmin = 0; dclkmax = 25000000;
	पूर्ण अन्यथा अणु
		hfmin = info->monspecs.hfmin;
		hfmax = info->monspecs.hfmax;
		vfmin = info->monspecs.vfmin;
		vfmax = info->monspecs.vfmax;
		dclkmin = info->monspecs.dclkmin;
		dclkmax = info->monspecs.dclkmax;
	पूर्ण

	अगर (!var->pixघड़ी)
		वापस -EINVAL;
	pixघड़ी = PICOS2KHZ(var->pixघड़ी) * 1000;

	htotal = var->xres + var->right_margin + var->hsync_len +
		var->left_margin;
	vtotal = var->yres + var->lower_margin + var->vsync_len +
		var->upper_margin;

	अगर (var->vmode & FB_VMODE_INTERLACED)
		vtotal /= 2;
	अगर (var->vmode & FB_VMODE_DOUBLE)
		vtotal *= 2;

	hfreq = pixघड़ी/htotal;
	hfreq = (hfreq + 500) / 1000 * 1000;

	vfreq = hfreq/vtotal;

	वापस (vfreq < vfmin || vfreq > vfmax ||
		hfreq < hfmin || hfreq > hfmax ||
		pixघड़ी < dclkmin || pixघड़ी > dclkmax) ?
		-EINVAL : 0;
पूर्ण

#अगर defined(CONFIG_FIRMWARE_EDID) && defined(CONFIG_X86)

/*
 * We need to ensure that the EDID block is only वापसed क्रम
 * the primary graphics adapter.
 */

स्थिर अचिन्हित अक्षर *fb_firmware_edid(काष्ठा device *device)
अणु
	काष्ठा pci_dev *dev = शून्य;
	काष्ठा resource *res = शून्य;
	अचिन्हित अक्षर *edid = शून्य;

	अगर (device)
		dev = to_pci_dev(device);

	अगर (dev)
		res = &dev->resource[PCI_ROM_RESOURCE];

	अगर (res && res->flags & IORESOURCE_ROM_SHADOW)
		edid = edid_info.dummy;

	वापस edid;
पूर्ण
#अन्यथा
स्थिर अचिन्हित अक्षर *fb_firmware_edid(काष्ठा device *device)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर
EXPORT_SYMBOL(fb_firmware_edid);

EXPORT_SYMBOL(fb_parse_edid);
EXPORT_SYMBOL(fb_edid_to_monspecs);
EXPORT_SYMBOL(fb_get_mode);
EXPORT_SYMBOL(fb_validate_mode);
EXPORT_SYMBOL(fb_destroy_modedb);
