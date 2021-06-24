<शैली गुरु>
/*
 *
 * Copyright (c) 2012 Gilles Dartigueदीर्घue, Thomas Richter
 *
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#समावेश "i915_drv.h"
#समावेश "i915_reg.h"
#समावेश "intel_display_types.h"
#समावेश "intel_dvo_dev.h"

#घोषणा NS2501_VID 0x1305
#घोषणा NS2501_DID 0x6726

#घोषणा NS2501_VID_LO 0x00
#घोषणा NS2501_VID_HI 0x01
#घोषणा NS2501_DID_LO 0x02
#घोषणा NS2501_DID_HI 0x03
#घोषणा NS2501_REV 0x04
#घोषणा NS2501_RSVD 0x05
#घोषणा NS2501_FREQ_LO 0x06
#घोषणा NS2501_FREQ_HI 0x07

#घोषणा NS2501_REG8 0x08
#घोषणा NS2501_8_VEN (1<<5)
#घोषणा NS2501_8_HEN (1<<4)
#घोषणा NS2501_8_DSEL (1<<3)
#घोषणा NS2501_8_BPAS (1<<2)
#घोषणा NS2501_8_RSVD (1<<1)
#घोषणा NS2501_8_PD (1<<0)

#घोषणा NS2501_REG9 0x09
#घोषणा NS2501_9_VLOW (1<<7)
#घोषणा NS2501_9_MSEL_MASK (0x7<<4)
#घोषणा NS2501_9_TSEL (1<<3)
#घोषणा NS2501_9_RSEN (1<<2)
#घोषणा NS2501_9_RSVD (1<<1)
#घोषणा NS2501_9_MDI (1<<0)

#घोषणा NS2501_REGC 0x0c

/*
 * The following रेजिस्टरs are not part of the official datasheet
 * and are the result of reverse engineering.
 */

/*
 * Register c0 controls how the DVO synchronizes with
 * its input.
 */
#घोषणा NS2501_REGC0 0xc0
#घोषणा NS2501_C0_ENABLE (1<<0)	/* enable the DVO sync in general */
#घोषणा NS2501_C0_HSYNC (1<<1)	/* synchronize horizontal with input */
#घोषणा NS2501_C0_VSYNC (1<<2)	/* synchronize vertical with input */
#घोषणा NS2501_C0_RESET (1<<7)	/* reset the synchronization flip/flops */

/*
 * Register 41 is somehow related to the sync रेजिस्टर and sync
 * configuration. It should be 0x32 whenever regC0 is 0x05 (hsync off)
 * and 0x00 otherwise.
 */
#घोषणा NS2501_REG41 0x41

/*
 * this रेजिस्टर controls the dithering of the DVO
 * One bit enables it, the other define the dithering depth.
 * The higher the value, the lower the dithering depth.
 */
#घोषणा NS2501_F9_REG 0xf9
#घोषणा NS2501_F9_ENABLE (1<<0)		/* अगर set, dithering is enabled */
#घोषणा NS2501_F9_DITHER_MASK (0x7f<<1)	/* controls the dither depth */
#घोषणा NS2501_F9_DITHER_SHIFT 1	/* shअगरts the dither mask */

/*
 * PLL configuration रेजिस्टर. This is a pair of रेजिस्टरs,
 * one single byte रेजिस्टर at 1B, and a pair at 1C,1D.
 * These रेजिस्टरs are counters/भागiders.
 */
#घोषणा NS2501_REG1B 0x1b /* one byte PLL control रेजिस्टर */
#घोषणा NS2501_REG1C 0x1c /* low-part of the second रेजिस्टर */
#घोषणा NS2501_REG1D 0x1d /* high-part of the second रेजिस्टर */

/*
 * Scaler control रेजिस्टरs. Horizontal at b8,b9,
 * vertical at 10,11. The scale factor is computed as
 * 2^16/control-value. The low-byte comes first.
 */
#घोषणा NS2501_REG10 0x10 /* low-byte vertical scaler */
#घोषणा NS2501_REG11 0x11 /* high-byte vertical scaler */
#घोषणा NS2501_REGB8 0xb8 /* low-byte horizontal scaler */
#घोषणा NS2501_REGB9 0xb9 /* high-byte horizontal scaler */

/*
 * Display winकरोw definition. This consists of four रेजिस्टरs
 * per dimension. One रेजिस्टर pair defines the start of the
 * display, one the end.
 * As far as I understand, this defines the winकरोw within which
 * the scaler samples the input.
 */
#घोषणा NS2501_REGC1 0xc1 /* low-byte horizontal display start */
#घोषणा NS2501_REGC2 0xc2 /* high-byte horizontal display start */
#घोषणा NS2501_REGC3 0xc3 /* low-byte horizontal display stop */
#घोषणा NS2501_REGC4 0xc4 /* high-byte horizontal display stop */
#घोषणा NS2501_REGC5 0xc5 /* low-byte vertical display start */
#घोषणा NS2501_REGC6 0xc6 /* high-byte vertical display start */
#घोषणा NS2501_REGC7 0xc7 /* low-byte vertical display stop */
#घोषणा NS2501_REGC8 0xc8 /* high-byte vertical display stop */

/*
 * The following रेजिस्टर pair seems to define the start of
 * the vertical sync. If स्वतःmatic syncing is enabled, and the
 * रेजिस्टर value defines a sync pulse that is later than the
 * incoming sync, then the रेजिस्टर value is ignored and the
 * बाह्यal hsync triggers the synchronization.
 */
#घोषणा NS2501_REG80 0x80 /* low-byte vsync-start */
#घोषणा NS2501_REG81 0x81 /* high-byte vsync-start */

/*
 * The following रेजिस्टर pair seems to define the total number
 * of lines created at the output side of the scaler.
 * This is again a low-high रेजिस्टर pair.
 */
#घोषणा NS2501_REG82 0x82 /* output display height, low byte */
#घोषणा NS2501_REG83 0x83 /* output display height, high byte */

/*
 * The following रेजिस्टरs define the end of the front-porch
 * in horizontal and vertical position and hence allow to shअगरt
 * the image left/right or up/करोwn.
 */
#घोषणा NS2501_REG98 0x98 /* horizontal start of display + 256, low */
#घोषणा NS2501_REG99 0x99 /* horizontal start of display + 256, high */
#घोषणा NS2501_REG8E 0x8e /* vertical start of the display, low byte */
#घोषणा NS2501_REG8F 0x8f /* vertical start of the display, high byte */

/*
 * The following रेजिस्टर pair control the function of the
 * backlight and the DVO output. To enable the corresponding
 * function, the corresponding bit must be set in both रेजिस्टरs.
 */
#घोषणा NS2501_REG34 0x34 /* DVO enable functions, first रेजिस्टर */
#घोषणा NS2501_REG35 0x35 /* DVO enable functions, second रेजिस्टर */
#घोषणा NS2501_34_ENABLE_OUTPUT (1<<0) /* enable DVO output */
#घोषणा NS2501_34_ENABLE_BACKLIGHT (1<<1) /* enable backlight */

/*
 * Registers 9C and 9D define the vertical output offset
 * of the visible region.
 */
#घोषणा NS2501_REG9C 0x9c
#घोषणा NS2501_REG9D 0x9d

/*
 * The रेजिस्टर 9F defines the dithering. This requires the
 * scaler to be ON. Bit 0 enables dithering, the reमुख्यing
 * bits control the depth of the dither. The higher the value,
 * the LOWER the dithering amplitude. A good value seems to be
 * 15 (total रेजिस्टर value).
 */
#घोषणा NS2501_REGF9 0xf9
#घोषणा NS2501_F9_ENABLE_DITHER (1<<0) /* enable dithering */
#घोषणा NS2501_F9_DITHER_MASK (0x7f<<1) /* dither masking */
#घोषणा NS2501_F9_DITHER_SHIFT 1	/* upshअगरt of the dither mask */

क्रमागत अणु
	MODE_640x480,
	MODE_800x600,
	MODE_1024x768,
पूर्ण;

काष्ठा ns2501_reg अणु
	u8 offset;
	u8 value;
पूर्ण;

/*
 * The following काष्ठाure keeps the complete configuration of
 * the DVO, given a specअगरic output configuration.
 * This is pretty much guess-work from reverse-engineering, so
 * पढ़ो all this with a grain of salt.
 */
काष्ठा ns2501_configuration अणु
	u8 sync;		/* configuration of the C0 रेजिस्टर */
	u8 conf;		/* configuration रेजिस्टर 8 */
	u8 syncb;		/* configuration रेजिस्टर 41 */
	u8 dither;		/* configuration of the dithering */
	u8 pll_a;		/* PLL configuration, रेजिस्टर A, 1B */
	u16 pll_b;		/* PLL configuration, रेजिस्टर B, 1C/1D */
	u16 hstart;		/* horizontal start, रेजिस्टरs C1/C2 */
	u16 hstop;		/* horizontal total, रेजिस्टरs C3/C4 */
	u16 vstart;		/* vertical start, रेजिस्टरs C5/C6 */
	u16 vstop;		/* vertical total, रेजिस्टरs C7/C8 */
	u16 vsync;		/* manual vertical sync start, 80/81 */
	u16 vtotal;		/* number of lines generated, 82/83 */
	u16 hpos;		/* horizontal position + 256, 98/99  */
	u16 vpos;		/* vertical position, 8e/8f */
	u16 voffs;		/* vertical output offset, 9c/9d */
	u16 hscale;		/* horizontal scaling factor, b8/b9 */
	u16 vscale;		/* vertical scaling factor, 10/11 */
पूर्ण;

/*
 * DVO configuration values, partially based on what the BIOS
 * of the Fujitsu Lअगरebook S6010 ग_लिखोs पूर्णांकo रेजिस्टरs,
 * partially found by manual tweaking. These configurations assume
 * a 1024x768 panel.
 */
अटल स्थिर काष्ठा ns2501_configuration ns2501_modes[] = अणु
	[MODE_640x480] = अणु
		.sync	= NS2501_C0_ENABLE | NS2501_C0_VSYNC,
		.conf	= NS2501_8_VEN | NS2501_8_HEN | NS2501_8_PD,
		.syncb	= 0x32,
		.dither	= 0x0f,
		.pll_a	= 17,
		.pll_b	= 852,
		.hstart	= 144,
		.hstop	= 783,
		.vstart	= 22,
		.vstop	= 514,
		.vsync	= 2047, /* actually, ignored with this config */
		.vtotal	= 1341,
		.hpos	= 0,
		.vpos	= 16,
		.voffs	= 36,
		.hscale	= 40960,
		.vscale	= 40960
	पूर्ण,
	[MODE_800x600] = अणु
		.sync	= NS2501_C0_ENABLE |
			  NS2501_C0_HSYNC | NS2501_C0_VSYNC,
		.conf   = NS2501_8_VEN | NS2501_8_HEN | NS2501_8_PD,
		.syncb	= 0x00,
		.dither	= 0x0f,
		.pll_a	= 25,
		.pll_b	= 612,
		.hstart	= 215,
		.hstop	= 1016,
		.vstart	= 26,
		.vstop	= 627,
		.vsync	= 807,
		.vtotal	= 1341,
		.hpos	= 0,
		.vpos	= 4,
		.voffs	= 35,
		.hscale	= 51248,
		.vscale	= 51232
	पूर्ण,
	[MODE_1024x768] = अणु
		.sync	= NS2501_C0_ENABLE | NS2501_C0_VSYNC,
		.conf   = NS2501_8_VEN | NS2501_8_HEN | NS2501_8_PD,
		.syncb	= 0x32,
		.dither	= 0x0f,
		.pll_a	= 11,
		.pll_b	= 1350,
		.hstart	= 276,
		.hstop	= 1299,
		.vstart	= 15,
		.vstop	= 1056,
		.vsync	= 2047,
		.vtotal	= 1341,
		.hpos	= 0,
		.vpos	= 7,
		.voffs	= 27,
		.hscale	= 65535,
		.vscale	= 65535
	पूर्ण
पूर्ण;

/*
 * Other configuration values left by the BIOS of the
 * Fujitsu S6010 in the DVO control रेजिस्टरs. Their
 * value करोes not depend on the BIOS and their meaning
 * is unknown.
 */

अटल स्थिर काष्ठा ns2501_reg mode_agnostic_values[] = अणु
	/* 08 is mode specअगरic */
	[0] = अणु .offset = 0x0a, .value = 0x81, पूर्ण,
	/* 10,11 are part of the mode specअगरic configuration */
	[1] = अणु .offset = 0x12, .value = 0x02, पूर्ण,
	[2] = अणु .offset = 0x18, .value = 0x07, पूर्ण,
	[3] = अणु .offset = 0x19, .value = 0x00, पूर्ण,
	[4] = अणु .offset = 0x1a, .value = 0x00, पूर्ण, /* PLL?, ignored */
	/* 1b,1c,1d are part of the mode specअगरic configuration */
	[5] = अणु .offset = 0x1e, .value = 0x02, पूर्ण,
	[6] = अणु .offset = 0x1f, .value = 0x40, पूर्ण,
	[7] = अणु .offset = 0x20, .value = 0x00, पूर्ण,
	[8] = अणु .offset = 0x21, .value = 0x00, पूर्ण,
	[9] = अणु .offset = 0x22, .value = 0x00, पूर्ण,
	[10] = अणु .offset = 0x23, .value = 0x00, पूर्ण,
	[11] = अणु .offset = 0x24, .value = 0x00, पूर्ण,
	[12] = अणु .offset = 0x25, .value = 0x00, पूर्ण,
	[13] = अणु .offset = 0x26, .value = 0x00, पूर्ण,
	[14] = अणु .offset = 0x27, .value = 0x00, पूर्ण,
	[15] = अणु .offset = 0x7e, .value = 0x18, पूर्ण,
	/* 80-84 are part of the mode-specअगरic configuration */
	[16] = अणु .offset = 0x84, .value = 0x00, पूर्ण,
	[17] = अणु .offset = 0x85, .value = 0x00, पूर्ण,
	[18] = अणु .offset = 0x86, .value = 0x00, पूर्ण,
	[19] = अणु .offset = 0x87, .value = 0x00, पूर्ण,
	[20] = अणु .offset = 0x88, .value = 0x00, पूर्ण,
	[21] = अणु .offset = 0x89, .value = 0x00, पूर्ण,
	[22] = अणु .offset = 0x8a, .value = 0x00, पूर्ण,
	[23] = अणु .offset = 0x8b, .value = 0x00, पूर्ण,
	[24] = अणु .offset = 0x8c, .value = 0x10, पूर्ण,
	[25] = अणु .offset = 0x8d, .value = 0x02, पूर्ण,
	/* 8e,8f are part of the mode-specअगरic configuration */
	[26] = अणु .offset = 0x90, .value = 0xff, पूर्ण,
	[27] = अणु .offset = 0x91, .value = 0x07, पूर्ण,
	[28] = अणु .offset = 0x92, .value = 0xa0, पूर्ण,
	[29] = अणु .offset = 0x93, .value = 0x02, पूर्ण,
	[30] = अणु .offset = 0x94, .value = 0x00, पूर्ण,
	[31] = अणु .offset = 0x95, .value = 0x00, पूर्ण,
	[32] = अणु .offset = 0x96, .value = 0x05, पूर्ण,
	[33] = अणु .offset = 0x97, .value = 0x00, पूर्ण,
	/* 98,99 are part of the mode-specअगरic configuration */
	[34] = अणु .offset = 0x9a, .value = 0x88, पूर्ण,
	[35] = अणु .offset = 0x9b, .value = 0x00, पूर्ण,
	/* 9c,9d are part of the mode-specअगरic configuration */
	[36] = अणु .offset = 0x9e, .value = 0x25, पूर्ण,
	[37] = अणु .offset = 0x9f, .value = 0x03, पूर्ण,
	[38] = अणु .offset = 0xa0, .value = 0x28, पूर्ण,
	[39] = अणु .offset = 0xa1, .value = 0x01, पूर्ण,
	[40] = अणु .offset = 0xa2, .value = 0x28, पूर्ण,
	[41] = अणु .offset = 0xa3, .value = 0x05, पूर्ण,
	/* रेजिस्टर 0xa4 is mode specअगरic, but 0x80..0x84 works always */
	[42] = अणु .offset = 0xa4, .value = 0x84, पूर्ण,
	[43] = अणु .offset = 0xa5, .value = 0x00, पूर्ण,
	[44] = अणु .offset = 0xa6, .value = 0x00, पूर्ण,
	[45] = अणु .offset = 0xa7, .value = 0x00, पूर्ण,
	[46] = अणु .offset = 0xa8, .value = 0x00, पूर्ण,
	/* 0xa9 to 0xab are mode specअगरic, but have no visible effect */
	[47] = अणु .offset = 0xa9, .value = 0x04, पूर्ण,
	[48] = अणु .offset = 0xaa, .value = 0x70, पूर्ण,
	[49] = अणु .offset = 0xab, .value = 0x4f, पूर्ण,
	[50] = अणु .offset = 0xac, .value = 0x00, पूर्ण,
	[51] = अणु .offset = 0xad, .value = 0x00, पूर्ण,
	[52] = अणु .offset = 0xb6, .value = 0x09, पूर्ण,
	[53] = अणु .offset = 0xb7, .value = 0x03, पूर्ण,
	/* b8,b9 are part of the mode-specअगरic configuration */
	[54] = अणु .offset = 0xba, .value = 0x00, पूर्ण,
	[55] = अणु .offset = 0xbb, .value = 0x20, पूर्ण,
	[56] = अणु .offset = 0xf3, .value = 0x90, पूर्ण,
	[57] = अणु .offset = 0xf4, .value = 0x00, पूर्ण,
	[58] = अणु .offset = 0xf7, .value = 0x88, पूर्ण,
	/* f8 is mode specअगरic, but the value करोes not matter */
	[59] = अणु .offset = 0xf8, .value = 0x0a, पूर्ण,
	[60] = अणु .offset = 0xf9, .value = 0x00, पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ns2501_reg regs_init[] = अणु
	[0] = अणु .offset = 0x35, .value = 0xff, पूर्ण,
	[1] = अणु .offset = 0x34, .value = 0x00, पूर्ण,
	[2] = अणु .offset = 0x08, .value = 0x30, पूर्ण,
पूर्ण;

काष्ठा ns2501_priv अणु
	bool quiet;
	स्थिर काष्ठा ns2501_configuration *conf;
पूर्ण;

#घोषणा NSPTR(d) ((NS2501Ptr)(d->DriverPrivate.ptr))

/*
** Read a रेजिस्टर from the ns2501.
** Returns true अगर successful, false otherwise.
** If it वापसs false, it might be wise to enable the
** DVO with the above function.
*/
अटल bool ns2501_पढ़ोb(काष्ठा पूर्णांकel_dvo_device *dvo, पूर्णांक addr, u8 *ch)
अणु
	काष्ठा ns2501_priv *ns = dvo->dev_priv;
	काष्ठा i2c_adapter *adapter = dvo->i2c_bus;
	u8 out_buf[2];
	u8 in_buf[2];

	काष्ठा i2c_msg msgs[] = अणु
		अणु
		 .addr = dvo->slave_addr,
		 .flags = 0,
		 .len = 1,
		 .buf = out_buf,
		 पूर्ण,
		अणु
		 .addr = dvo->slave_addr,
		 .flags = I2C_M_RD,
		 .len = 1,
		 .buf = in_buf,
		 पूर्ण
	पूर्ण;

	out_buf[0] = addr;
	out_buf[1] = 0;

	अगर (i2c_transfer(adapter, msgs, 2) == 2) अणु
		*ch = in_buf[0];
		वापस true;
	पूर्ण

	अगर (!ns->quiet) अणु
		DRM_DEBUG_KMS
		    ("Unable to read register 0x%02x from %s:0x%02x.\n", addr,
		     adapter->name, dvo->slave_addr);
	पूर्ण

	वापस false;
पूर्ण

/*
** Write a रेजिस्टर to the ns2501.
** Returns true अगर successful, false otherwise.
** If it वापसs false, it might be wise to enable the
** DVO with the above function.
*/
अटल bool ns2501_ग_लिखोb(काष्ठा पूर्णांकel_dvo_device *dvo, पूर्णांक addr, u8 ch)
अणु
	काष्ठा ns2501_priv *ns = dvo->dev_priv;
	काष्ठा i2c_adapter *adapter = dvo->i2c_bus;
	u8 out_buf[2];

	काष्ठा i2c_msg msg = अणु
		.addr = dvo->slave_addr,
		.flags = 0,
		.len = 2,
		.buf = out_buf,
	पूर्ण;

	out_buf[0] = addr;
	out_buf[1] = ch;

	अगर (i2c_transfer(adapter, &msg, 1) == 1) अणु
		वापस true;
	पूर्ण

	अगर (!ns->quiet) अणु
		DRM_DEBUG_KMS("Unable to write register 0x%02x to %s:%d\n",
			      addr, adapter->name, dvo->slave_addr);
	पूर्ण

	वापस false;
पूर्ण

/* National Semiconductor 2501 driver क्रम chip on i2c bus
 * scan क्रम the chip on the bus.
 * Hope the VBIOS initialized the PLL correctly so we can
 * talk to it. If not, it will not be seen and not detected.
 * Bummer!
 */
अटल bool ns2501_init(काष्ठा पूर्णांकel_dvo_device *dvo,
			काष्ठा i2c_adapter *adapter)
अणु
	/* this will detect the NS2501 chip on the specअगरied i2c bus */
	काष्ठा ns2501_priv *ns;
	अचिन्हित अक्षर ch;

	ns = kzalloc(माप(काष्ठा ns2501_priv), GFP_KERNEL);
	अगर (ns == शून्य)
		वापस false;

	dvo->i2c_bus = adapter;
	dvo->dev_priv = ns;
	ns->quiet = true;

	अगर (!ns2501_पढ़ोb(dvo, NS2501_VID_LO, &ch))
		जाओ out;

	अगर (ch != (NS2501_VID & 0xff)) अणु
		DRM_DEBUG_KMS("ns2501 not detected got %d: from %s Slave %d.\n",
			      ch, adapter->name, dvo->slave_addr);
		जाओ out;
	पूर्ण

	अगर (!ns2501_पढ़ोb(dvo, NS2501_DID_LO, &ch))
		जाओ out;

	अगर (ch != (NS2501_DID & 0xff)) अणु
		DRM_DEBUG_KMS("ns2501 not detected got %d: from %s Slave %d.\n",
			      ch, adapter->name, dvo->slave_addr);
		जाओ out;
	पूर्ण
	ns->quiet = false;

	DRM_DEBUG_KMS("init ns2501 dvo controller successfully!\n");

	वापस true;

out:
	kमुक्त(ns);
	वापस false;
पूर्ण

अटल क्रमागत drm_connector_status ns2501_detect(काष्ठा पूर्णांकel_dvo_device *dvo)
अणु
	/*
	 * This is a Laptop display, it करोesn't have hotplugging.
	 * Even अगर not, the detection bit of the 2501 is unreliable as
	 * it only works क्रम some display types.
	 * It is even more unreliable as the PLL must be active क्रम
	 * allowing पढ़ोing from the chiop.
	 */
	वापस connector_status_connected;
पूर्ण

अटल क्रमागत drm_mode_status ns2501_mode_valid(काष्ठा पूर्णांकel_dvo_device *dvo,
					      काष्ठा drm_display_mode *mode)
अणु
	DRM_DEBUG_KMS
	    ("is mode valid (hdisplay=%d,htotal=%d,vdisplay=%d,vtotal=%d)\n",
	     mode->hdisplay, mode->htotal, mode->vdisplay, mode->vtotal);

	/*
	 * Currently, these are all the modes I have data from.
	 * More might exist. Unclear how to find the native resolution
	 * of the panel in here so we could always accept it
	 * by disabling the scaler.
	 */
	अगर ((mode->hdisplay == 640 && mode->vdisplay == 480 && mode->घड़ी == 25175) ||
	    (mode->hdisplay == 800 && mode->vdisplay == 600 && mode->घड़ी == 40000) ||
	    (mode->hdisplay == 1024 && mode->vdisplay == 768 && mode->घड़ी == 65000)) अणु
		वापस MODE_OK;
	पूर्ण अन्यथा अणु
		वापस MODE_ONE_SIZE;	/* Is this a reasonable error? */
	पूर्ण
पूर्ण

अटल व्योम ns2501_mode_set(काष्ठा पूर्णांकel_dvo_device *dvo,
			    स्थिर काष्ठा drm_display_mode *mode,
			    स्थिर काष्ठा drm_display_mode *adjusted_mode)
अणु
	स्थिर काष्ठा ns2501_configuration *conf;
	काष्ठा ns2501_priv *ns = (काष्ठा ns2501_priv *)(dvo->dev_priv);
	पूर्णांक mode_idx, i;

	DRM_DEBUG_KMS
	    ("set mode (hdisplay=%d,htotal=%d,vdisplay=%d,vtotal=%d).\n",
	     mode->hdisplay, mode->htotal, mode->vdisplay, mode->vtotal);

	DRM_DEBUG_KMS("Detailed requested mode settings are:\n"
			"clock		: %d kHz\n"
			"hdisplay	: %d\n"
			"hblank start	: %d\n"
			"hblank end	: %d\n"
			"hsync start	: %d\n"
			"hsync end	: %d\n"
			"htotal		: %d\n"
			"hskew		: %d\n"
			"vdisplay	: %d\n"
			"vblank start	: %d\n"
			"hblank end	: %d\n"
			"vsync start	: %d\n"
			"vsync end	: %d\n"
			"vtotal		: %d\n",
			adjusted_mode->crtc_घड़ी,
			adjusted_mode->crtc_hdisplay,
			adjusted_mode->crtc_hblank_start,
			adjusted_mode->crtc_hblank_end,
			adjusted_mode->crtc_hsync_start,
			adjusted_mode->crtc_hsync_end,
			adjusted_mode->crtc_htotal,
			adjusted_mode->crtc_hskew,
			adjusted_mode->crtc_vdisplay,
			adjusted_mode->crtc_vblank_start,
			adjusted_mode->crtc_vblank_end,
			adjusted_mode->crtc_vsync_start,
			adjusted_mode->crtc_vsync_end,
			adjusted_mode->crtc_vtotal);

	अगर (mode->hdisplay == 640 && mode->vdisplay == 480)
		mode_idx = MODE_640x480;
	अन्यथा अगर (mode->hdisplay == 800 && mode->vdisplay == 600)
		mode_idx = MODE_800x600;
	अन्यथा अगर (mode->hdisplay == 1024 && mode->vdisplay == 768)
		mode_idx = MODE_1024x768;
	अन्यथा
		वापस;

	/* Hopefully करोing it every समय won't hurt... */
	क्रम (i = 0; i < ARRAY_SIZE(regs_init); i++)
		ns2501_ग_लिखोb(dvo, regs_init[i].offset, regs_init[i].value);

	/* Write the mode-agnostic values */
	क्रम (i = 0; i < ARRAY_SIZE(mode_agnostic_values); i++)
		ns2501_ग_लिखोb(dvo, mode_agnostic_values[i].offset,
				mode_agnostic_values[i].value);

	/* Write now the mode-specअगरic configuration */
	conf = ns2501_modes + mode_idx;
	ns->conf = conf;

	ns2501_ग_लिखोb(dvo, NS2501_REG8, conf->conf);
	ns2501_ग_लिखोb(dvo, NS2501_REG1B, conf->pll_a);
	ns2501_ग_लिखोb(dvo, NS2501_REG1C, conf->pll_b & 0xff);
	ns2501_ग_लिखोb(dvo, NS2501_REG1D, conf->pll_b >> 8);
	ns2501_ग_लिखोb(dvo, NS2501_REGC1, conf->hstart & 0xff);
	ns2501_ग_लिखोb(dvo, NS2501_REGC2, conf->hstart >> 8);
	ns2501_ग_लिखोb(dvo, NS2501_REGC3, conf->hstop & 0xff);
	ns2501_ग_लिखोb(dvo, NS2501_REGC4, conf->hstop >> 8);
	ns2501_ग_लिखोb(dvo, NS2501_REGC5, conf->vstart & 0xff);
	ns2501_ग_लिखोb(dvo, NS2501_REGC6, conf->vstart >> 8);
	ns2501_ग_लिखोb(dvo, NS2501_REGC7, conf->vstop & 0xff);
	ns2501_ग_लिखोb(dvo, NS2501_REGC8, conf->vstop >> 8);
	ns2501_ग_लिखोb(dvo, NS2501_REG80, conf->vsync & 0xff);
	ns2501_ग_लिखोb(dvo, NS2501_REG81, conf->vsync >> 8);
	ns2501_ग_लिखोb(dvo, NS2501_REG82, conf->vtotal & 0xff);
	ns2501_ग_लिखोb(dvo, NS2501_REG83, conf->vtotal >> 8);
	ns2501_ग_लिखोb(dvo, NS2501_REG98, conf->hpos & 0xff);
	ns2501_ग_लिखोb(dvo, NS2501_REG99, conf->hpos >> 8);
	ns2501_ग_लिखोb(dvo, NS2501_REG8E, conf->vpos & 0xff);
	ns2501_ग_लिखोb(dvo, NS2501_REG8F, conf->vpos >> 8);
	ns2501_ग_लिखोb(dvo, NS2501_REG9C, conf->voffs & 0xff);
	ns2501_ग_लिखोb(dvo, NS2501_REG9D, conf->voffs >> 8);
	ns2501_ग_लिखोb(dvo, NS2501_REGB8, conf->hscale & 0xff);
	ns2501_ग_लिखोb(dvo, NS2501_REGB9, conf->hscale >> 8);
	ns2501_ग_लिखोb(dvo, NS2501_REG10, conf->vscale & 0xff);
	ns2501_ग_लिखोb(dvo, NS2501_REG11, conf->vscale >> 8);
	ns2501_ग_लिखोb(dvo, NS2501_REGF9, conf->dither);
	ns2501_ग_लिखोb(dvo, NS2501_REG41, conf->syncb);
	ns2501_ग_लिखोb(dvo, NS2501_REGC0, conf->sync);
पूर्ण

/* set the NS2501 घातer state */
अटल bool ns2501_get_hw_state(काष्ठा पूर्णांकel_dvo_device *dvo)
अणु
	अचिन्हित अक्षर ch;

	अगर (!ns2501_पढ़ोb(dvo, NS2501_REG8, &ch))
		वापस false;

	वापस ch & NS2501_8_PD;
पूर्ण

/* set the NS2501 घातer state */
अटल व्योम ns2501_dpms(काष्ठा पूर्णांकel_dvo_device *dvo, bool enable)
अणु
	काष्ठा ns2501_priv *ns = (काष्ठा ns2501_priv *)(dvo->dev_priv);

	DRM_DEBUG_KMS("Trying set the dpms of the DVO to %i\n", enable);

	अगर (enable) अणु
		ns2501_ग_लिखोb(dvo, NS2501_REGC0, ns->conf->sync | 0x08);

		ns2501_ग_लिखोb(dvo, NS2501_REG41, ns->conf->syncb);

		ns2501_ग_लिखोb(dvo, NS2501_REG34, NS2501_34_ENABLE_OUTPUT);
		msleep(15);

		ns2501_ग_लिखोb(dvo, NS2501_REG8,
				ns->conf->conf | NS2501_8_BPAS);
		अगर (!(ns->conf->conf & NS2501_8_BPAS))
			ns2501_ग_लिखोb(dvo, NS2501_REG8, ns->conf->conf);
		msleep(200);

		ns2501_ग_लिखोb(dvo, NS2501_REG34,
			NS2501_34_ENABLE_OUTPUT | NS2501_34_ENABLE_BACKLIGHT);

		ns2501_ग_लिखोb(dvo, NS2501_REGC0, ns->conf->sync);
	पूर्ण अन्यथा अणु
		ns2501_ग_लिखोb(dvo, NS2501_REG34, NS2501_34_ENABLE_OUTPUT);
		msleep(200);

		ns2501_ग_लिखोb(dvo, NS2501_REG8, NS2501_8_VEN | NS2501_8_HEN |
				NS2501_8_BPAS);
		msleep(15);

		ns2501_ग_लिखोb(dvo, NS2501_REG34, 0x00);
	पूर्ण
पूर्ण

अटल व्योम ns2501_destroy(काष्ठा पूर्णांकel_dvo_device *dvo)
अणु
	काष्ठा ns2501_priv *ns = dvo->dev_priv;

	अगर (ns) अणु
		kमुक्त(ns);
		dvo->dev_priv = शून्य;
	पूर्ण
पूर्ण

स्थिर काष्ठा पूर्णांकel_dvo_dev_ops ns2501_ops = अणु
	.init = ns2501_init,
	.detect = ns2501_detect,
	.mode_valid = ns2501_mode_valid,
	.mode_set = ns2501_mode_set,
	.dpms = ns2501_dpms,
	.get_hw_state = ns2501_get_hw_state,
	.destroy = ns2501_destroy,
पूर्ण;
