<शैली गुरु>
/*
 * Copyright (C) 2009 Francisco Jerez.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining
 * a copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#समावेश <drm/drm_crtc_helper.h>
#समावेश "nouveau_drv.h"
#समावेश "nouveau_encoder.h"
#समावेश "nouveau_crtc.h"
#समावेश "hw.h"
#समावेश "tvnv17.h"

स्थिर अक्षर * स्थिर nv17_tv_norm_names[NUM_TV_NORMS] = अणु
	[TV_NORM_PAL] = "PAL",
	[TV_NORM_PAL_M] = "PAL-M",
	[TV_NORM_PAL_N] = "PAL-N",
	[TV_NORM_PAL_NC] = "PAL-Nc",
	[TV_NORM_NTSC_M] = "NTSC-M",
	[TV_NORM_NTSC_J] = "NTSC-J",
	[TV_NORM_HD480I] = "hd480i",
	[TV_NORM_HD480P] = "hd480p",
	[TV_NORM_HD576I] = "hd576i",
	[TV_NORM_HD576P] = "hd576p",
	[TV_NORM_HD720P] = "hd720p",
	[TV_NORM_HD1080I] = "hd1080i"
पूर्ण;

/* TV standard specअगरic parameters */

काष्ठा nv17_tv_norm_params nv17_tv_norms[NUM_TV_NORMS] = अणु
	[TV_NORM_PAL] = अणु TV_ENC_MODE, अणु
			.tv_enc_mode = अणु 720, 576, 50000, अणु
					0x2a, 0x9, 0x8a, 0xcb, 0x0, 0x0, 0xb, 0x18,
					0x7e, 0x40, 0x8a, 0x35, 0x27, 0x0, 0x34, 0x3,
					0x3e, 0x3, 0x17, 0x21, 0x1b, 0x1b, 0x24, 0x9c,
					0x1, 0x0, 0xf, 0xf, 0x60, 0x5, 0xd3, 0x3,
					0xd3, 0x4, 0xd4, 0x1, 0x2, 0x0, 0xa, 0x5,
					0x0, 0x1a, 0xff, 0x3, 0x18, 0xf, 0x78, 0x0,
					0x0, 0xb4, 0x0, 0x15, 0x49, 0x10, 0x0, 0x9b,
					0xbd, 0x15, 0x5, 0x15, 0x3e, 0x3, 0x0, 0x0
				पूर्ण पूर्ण पूर्ण पूर्ण,

	[TV_NORM_PAL_M] = अणु TV_ENC_MODE, अणु
			.tv_enc_mode = अणु 720, 480, 59940, अणु
					0x21, 0xe6, 0xef, 0xe3, 0x0, 0x0, 0xb, 0x18,
					0x7e, 0x44, 0x76, 0x32, 0x25, 0x0, 0x3c, 0x0,
					0x3c, 0x0, 0x17, 0x21, 0x1b, 0x1b, 0x24, 0x83,
					0x1, 0x0, 0xf, 0xf, 0x60, 0x5, 0xd3, 0x1,
					0xc5, 0x4, 0xc5, 0x1, 0x2, 0x0, 0xa, 0x5,
					0x0, 0x18, 0xff, 0x3, 0x20, 0xf, 0x78, 0x0,
					0x0, 0xb4, 0x0, 0x15, 0x40, 0x10, 0x0, 0x9c,
					0xc8, 0x15, 0x5, 0x15, 0x3c, 0x0, 0x0, 0x0
				पूर्ण पूर्ण पूर्ण पूर्ण,

	[TV_NORM_PAL_N] = अणु TV_ENC_MODE, अणु
			.tv_enc_mode = अणु 720, 576, 50000, अणु
					0x2a, 0x9, 0x8a, 0xcb, 0x0, 0x0, 0xb, 0x18,
					0x7e, 0x40, 0x8a, 0x32, 0x25, 0x0, 0x3c, 0x0,
					0x3c, 0x0, 0x17, 0x21, 0x1b, 0x1b, 0x24, 0x9c,
					0x1, 0x0, 0xf, 0xf, 0x60, 0x5, 0xd3, 0x1,
					0xc5, 0x4, 0xc5, 0x1, 0x2, 0x0, 0xa, 0x5,
					0x0, 0x1a, 0xff, 0x3, 0x18, 0xf, 0x78, 0x0,
					0x0, 0xb4, 0x0, 0x15, 0x49, 0x10, 0x0, 0x9b,
					0xbd, 0x15, 0x5, 0x15, 0x3c, 0x0, 0x0, 0x0
				पूर्ण पूर्ण पूर्ण पूर्ण,

	[TV_NORM_PAL_NC] = अणु TV_ENC_MODE, अणु
			.tv_enc_mode = अणु 720, 576, 50000, अणु
					0x21, 0xf6, 0x94, 0x46, 0x0, 0x0, 0xb, 0x18,
					0x7e, 0x44, 0x8a, 0x35, 0x27, 0x0, 0x34, 0x3,
					0x3e, 0x3, 0x17, 0x21, 0x1b, 0x1b, 0x24, 0x9c,
					0x1, 0x0, 0xf, 0xf, 0x60, 0x5, 0xd3, 0x3,
					0xd3, 0x4, 0xd4, 0x1, 0x2, 0x0, 0xa, 0x5,
					0x0, 0x1a, 0xff, 0x3, 0x18, 0xf, 0x78, 0x0,
					0x0, 0xb4, 0x0, 0x15, 0x49, 0x10, 0x0, 0x9b,
					0xbd, 0x15, 0x5, 0x15, 0x3e, 0x3, 0x0, 0x0
				पूर्ण पूर्ण पूर्ण पूर्ण,

	[TV_NORM_NTSC_M] = अणु TV_ENC_MODE, अणु
			.tv_enc_mode = अणु 720, 480, 59940, अणु
					0x21, 0xf0, 0x7c, 0x1f, 0x0, 0x0, 0xb, 0x18,
					0x7e, 0x44, 0x76, 0x48, 0x0, 0x0, 0x3c, 0x0,
					0x3c, 0x0, 0x17, 0x21, 0x1b, 0x1b, 0x24, 0x83,
					0x1, 0x0, 0xf, 0xf, 0x60, 0x5, 0xd3, 0x1,
					0xc5, 0x4, 0xc5, 0x1, 0x2, 0x0, 0xa, 0x5,
					0x0, 0x16, 0xff, 0x3, 0x20, 0xf, 0x78, 0x0,
					0x0, 0xb4, 0x0, 0x15, 0x4, 0x10, 0x0, 0x9c,
					0xc8, 0x15, 0x5, 0x15, 0x3c, 0x0, 0x0, 0x0
				पूर्ण पूर्ण पूर्ण पूर्ण,

	[TV_NORM_NTSC_J] = अणु TV_ENC_MODE, अणु
			.tv_enc_mode = अणु 720, 480, 59940, अणु
					0x21, 0xf0, 0x7c, 0x1f, 0x0, 0x0, 0xb, 0x18,
					0x7e, 0x44, 0x76, 0x48, 0x0, 0x0, 0x32, 0x0,
					0x3c, 0x0, 0x17, 0x21, 0x1b, 0x1b, 0x24, 0x83,
					0x1, 0x0, 0xf, 0xf, 0x60, 0x5, 0xd3, 0x1,
					0xcf, 0x4, 0xcf, 0x1, 0x2, 0x0, 0xa, 0x5,
					0x0, 0x16, 0xff, 0x3, 0x20, 0xf, 0x78, 0x0,
					0x0, 0xb4, 0x0, 0x15, 0x4, 0x10, 0x0, 0xa4,
					0xc8, 0x15, 0x5, 0x15, 0x3c, 0x0, 0x0, 0x0
				पूर्ण पूर्ण पूर्ण पूर्ण,

	[TV_NORM_HD480I] = अणु TV_ENC_MODE, अणु
			.tv_enc_mode = अणु 720, 480, 59940, अणु
					0x21, 0xf0, 0x7c, 0x1f, 0x0, 0x0, 0xb, 0x18,
					0x7e, 0x44, 0x76, 0x48, 0x0, 0x0, 0x32, 0x0,
					0x3c, 0x0, 0x17, 0x21, 0x1b, 0x1b, 0x24, 0x83,
					0x1, 0x0, 0xf, 0xf, 0x60, 0x5, 0xd3, 0x1,
					0xcf, 0x4, 0xcf, 0x1, 0x2, 0x0, 0xa, 0x5,
					0x0, 0x16, 0xff, 0x3, 0x20, 0xf, 0x78, 0x0,
					0x0, 0xb4, 0x0, 0x15, 0x4, 0x10, 0x0, 0xa4,
					0xc8, 0x15, 0x5, 0x15, 0x3c, 0x0, 0x0, 0x0
				पूर्ण पूर्ण पूर्ण पूर्ण,

	[TV_NORM_HD576I] = अणु TV_ENC_MODE, अणु
			.tv_enc_mode = अणु 720, 576, 50000, अणु
					0x2a, 0x9, 0x8a, 0xcb, 0x0, 0x0, 0xb, 0x18,
					0x7e, 0x40, 0x8a, 0x35, 0x27, 0x0, 0x34, 0x3,
					0x3e, 0x3, 0x17, 0x21, 0x1b, 0x1b, 0x24, 0x9c,
					0x1, 0x0, 0xf, 0xf, 0x60, 0x5, 0xd3, 0x3,
					0xd3, 0x4, 0xd4, 0x1, 0x2, 0x0, 0xa, 0x5,
					0x0, 0x1a, 0xff, 0x3, 0x18, 0xf, 0x78, 0x0,
					0x0, 0xb4, 0x0, 0x15, 0x49, 0x10, 0x0, 0x9b,
					0xbd, 0x15, 0x5, 0x15, 0x3e, 0x3, 0x0, 0x0
				पूर्ण पूर्ण पूर्ण पूर्ण,


	[TV_NORM_HD480P] = अणु CTV_ENC_MODE, अणु
			.ctv_enc_mode = अणु
				.mode = अणु DRM_MODE("720x480", DRM_MODE_TYPE_DRIVER, 27000,
						   720, 735, 743, 858, 0, 480, 490, 494, 525, 0,
						   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
				.ctv_regs = अणु 0x3540000, 0x0, 0x0, 0x314,
					      0x354003a, 0x40000, 0x6f0344, 0x18100000,
					      0x10160004, 0x10060005, 0x1006000c, 0x10060020,
					      0x10060021, 0x140e0022, 0x10060202, 0x1802020a,
					      0x1810020b, 0x10000fff, 0x10000fff, 0x10000fff,
					      0x10000fff, 0x10000fff, 0x10000fff, 0x70,
					      0x3ff0000, 0x57, 0x2e001e, 0x258012c,
					      0xa0aa04ec, 0x30, 0x80960019, 0x12c0300,
					      0x2019, 0x600, 0x32060019, 0x0, 0x0, 0x400
				पूर्ण पूर्ण पूर्ण पूर्ण,

	[TV_NORM_HD576P] = अणु CTV_ENC_MODE, अणु
			.ctv_enc_mode = अणु
				.mode = अणु DRM_MODE("720x576", DRM_MODE_TYPE_DRIVER, 27000,
						   720, 730, 738, 864, 0, 576, 581, 585, 625, 0,
						   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
				.ctv_regs = अणु 0x3540000, 0x0, 0x0, 0x314,
					      0x354003a, 0x40000, 0x6f0344, 0x18100000,
					      0x10060001, 0x10060009, 0x10060026, 0x10060027,
					      0x140e0028, 0x10060268, 0x1810026d, 0x10000fff,
					      0x10000fff, 0x10000fff, 0x10000fff, 0x10000fff,
					      0x10000fff, 0x10000fff, 0x10000fff, 0x69,
					      0x3ff0000, 0x57, 0x2e001e, 0x258012c,
					      0xa0aa04ec, 0x30, 0x80960019, 0x12c0300,
					      0x2019, 0x600, 0x32060019, 0x0, 0x0, 0x400
				पूर्ण पूर्ण पूर्ण पूर्ण,

	[TV_NORM_HD720P] = अणु CTV_ENC_MODE, अणु
			.ctv_enc_mode = अणु
				.mode = अणु DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250,
						   1280, 1349, 1357, 1650, 0, 720, 725, 730, 750, 0,
						   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
				.ctv_regs = अणु 0x1260394, 0x0, 0x0, 0x622,
					      0x66b0021, 0x6004a, 0x1210626, 0x8170000,
					      0x70004, 0x70016, 0x70017, 0x40f0018,
					      0x702e8, 0x81702ed, 0xfff, 0xfff,
					      0xfff, 0xfff, 0xfff, 0xfff,
					      0xfff, 0xfff, 0xfff, 0x0,
					      0x2e40001, 0x58, 0x2e001e, 0x258012c,
					      0xa0aa04ec, 0x30, 0x810c0039, 0x12c0300,
					      0xc0002039, 0x600, 0x32060039, 0x0, 0x0, 0x0
				पूर्ण पूर्ण पूर्ण पूर्ण,

	[TV_NORM_HD1080I] = अणु CTV_ENC_MODE, अणु
			.ctv_enc_mode = अणु
				.mode = अणु DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 74250,
						   1920, 1961, 2049, 2200, 0, 1080, 1084, 1088, 1125, 0,
						   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC
						   | DRM_MODE_FLAG_INTERLACE) पूर्ण,
				.ctv_regs = अणु 0xac0420, 0x44c0478, 0x4a4, 0x4fc0868,
					      0x8940028, 0x60054, 0xe80870, 0xbf70000,
					      0xbc70004, 0x70005, 0x70012, 0x70013,
					      0x40f0014, 0x70230, 0xbf70232, 0xbf70233,
					      0x1c70237, 0x70238, 0x70244, 0x70245,
					      0x40f0246, 0x70462, 0x1f70464, 0x0,
					      0x2e40001, 0x58, 0x2e001e, 0x258012c,
					      0xa0aa04ec, 0x30, 0x815f004c, 0x12c0300,
					      0xc000204c, 0x600, 0x3206004c, 0x0, 0x0, 0x0
				पूर्ण पूर्ण पूर्ण पूर्ण
पूर्ण;

/*
 * The following is some guesswork on how the TV encoder flicker
 * filter/rescaler works:
 *
 * It seems to use some sort of resampling filter, it is controlled
 * through the रेजिस्टरs at NV_PTV_HFILTER and NV_PTV_VFILTER, they
 * control the horizontal and vertical stage respectively, there is
 * also NV_PTV_HFILTER2 the blob fills identically to NV_PTV_HFILTER,
 * but they seem to करो nothing. A rough guess might be that they could
 * be used to independently control the filtering of each पूर्णांकerlaced
 * field, but I करोn't know how they are enabled. The whole filtering
 * process seems to be disabled with bits 26:27 of PTV_200, but we
 * aren't करोing that.
 *
 * The layout of both रेजिस्टर sets is the same:
 *
 * A: [BASE+0x18]...[BASE+0x0] [BASE+0x58]..[BASE+0x40]
 * B: [BASE+0x34]...[BASE+0x1c] [BASE+0x74]..[BASE+0x5c]
 *
 * Each coefficient is stored in bits [31],[15:9] in two's complement
 * क्रमmat. They seem to be some kind of weights used in a low-pass
 * filter. Both A and B coefficients are applied to the 14 nearest
 * samples on each side (Listed from nearest to furthermost.  They
 * roughly cover 2 framebuffer pixels on each side).  They are
 * probably multiplied with some more hardwired weights beक्रमe being
 * used: B-coefficients are applied the same on both sides,
 * A-coefficients are inverted beक्रमe being applied to the opposite
 * side.
 *
 * After all the hassle, I got the following क्रमmula by empirical
 * means...
 */

#घोषणा calc_overscan(o) पूर्णांकerpolate(0x100, 0xe1, 0xc1, o)

#घोषणा id1 (1LL << 8)
#घोषणा id2 (1LL << 16)
#घोषणा id3 (1LL << 24)
#घोषणा id4 (1LL << 32)
#घोषणा id5 (1LL << 48)

अटल काष्ठा filter_paramsअणु
	पूर्णांक64_t k1;
	पूर्णांक64_t ki;
	पूर्णांक64_t ki2;
	पूर्णांक64_t ki3;
	पूर्णांक64_t kr;
	पूर्णांक64_t kir;
	पूर्णांक64_t ki2r;
	पूर्णांक64_t ki3r;
	पूर्णांक64_t kf;
	पूर्णांक64_t kअगर;
	पूर्णांक64_t ki2f;
	पूर्णांक64_t ki3f;
	पूर्णांक64_t krf;
	पूर्णांक64_t kirf;
	पूर्णांक64_t ki2rf;
	पूर्णांक64_t ki3rf;
पूर्ण fparams[2][4] = अणु
	/* Horizontal filter parameters */
	अणु
		अणु64.311690 * id5, -39.516924 * id5, 6.586143 * id5, 0.000002 * id5,
		 0.051285 * id4, 26.168746 * id4, -4.361449 * id4, -0.000001 * id4,
		 9.308169 * id3, 78.180965 * id3, -13.030158 * id3, -0.000001 * id3,
		 -8.801540 * id1, -46.572890 * id1, 7.762145 * id1, -0.000000 * id1पूर्ण,
		अणु-44.565569 * id5, -68.081246 * id5, 39.812074 * id5, -4.009316 * id5,
		 29.832207 * id4, 50.047322 * id4, -25.380017 * id4, 2.546422 * id4,
		 104.605622 * id3, 141.908641 * id3, -74.322319 * id3, 7.484316 * id3,
		 -37.081621 * id1, -90.397510 * id1, 42.784229 * id1, -4.289952 * id1पूर्ण,
		अणु-56.793244 * id5, 31.153584 * id5, -5.192247 * id5, -0.000003 * id5,
		 33.541131 * id4, -34.149302 * id4, 5.691537 * id4, 0.000002 * id4,
		 87.196610 * id3, -88.995169 * id3, 14.832456 * id3, 0.000012 * id3,
		 17.288138 * id1, 71.864786 * id1, -11.977408 * id1, -0.000009 * id1पूर्ण,
		अणु51.787796 * id5, 21.211771 * id5, -18.993730 * id5, 1.853310 * id5,
		 -41.470726 * id4, -17.775823 * id4, 13.057821 * id4, -1.15823 * id4,
		 -154.235673 * id3, -44.878641 * id3, 40.656077 * id3, -3.695595 * id3,
		 112.201065 * id1, 39.992155 * id1, -25.155714 * id1, 2.113984 * id1पूर्ण,
	पूर्ण,

	/* Vertical filter parameters */
	अणु
		अणु67.601979 * id5, 0.428319 * id5, -0.071318 * id5, -0.000012 * id5,
		 -3.402339 * id4, 0.000209 * id4, -0.000092 * id4, 0.000010 * id4,
		 -9.180996 * id3, 6.111270 * id3, -1.024457 * id3, 0.001043 * id3,
		 6.060315 * id1, -0.017425 * id1, 0.007830 * id1, -0.000869 * id1पूर्ण,
		अणु6.755647 * id5, 5.841348 * id5, 1.469734 * id5, -0.149656 * id5,
		 8.293120 * id4, -1.192888 * id4, -0.947652 * id4, 0.094507 * id4,
		 37.526655 * id3, 10.257875 * id3, -10.823275 * id3, 1.081497 * id3,
		 -2.361928 * id1, -2.059432 * id1, 1.840671 * id1, -0.168100 * id1पूर्ण,
		अणु-14.780391 * id5, -16.042148 * id5, 2.673692 * id5, -0.000000 * id5,
		 39.541978 * id4, 5.680053 * id4, -0.946676 * id4, 0.000000 * id4,
		 152.994486 * id3, 12.625439 * id3, -2.119579 * id3, 0.002708 * id3,
		 -38.125089 * id1, -0.855880 * id1, 0.155359 * id1, -0.002245 * id1पूर्ण,
		अणु-27.476193 * id5, -1.454976 * id5, 1.286557 * id5, 0.025346 * id5,
		 20.687300 * id4, 3.014003 * id4, -0.557786 * id4, -0.01311 * id4,
		 60.008737 * id3, -0.738273 * id3, 5.408217 * id3, -0.796798 * id3,
		 -17.296835 * id1, 4.438577 * id1, -2.809420 * id1, 0.385491 * id1पूर्ण,
	पूर्ण
पूर्ण;

अटल व्योम tv_setup_filter(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा nv17_tv_encoder *tv_enc = to_tv_enc(encoder);
	काष्ठा nv17_tv_norm_params *tv_norm = get_tv_norm(encoder);
	काष्ठा drm_display_mode *mode = &encoder->crtc->mode;
	uपूर्णांक32_t (*filters[])[4][7] = अणु&tv_enc->state.hfilter,
				       &tv_enc->state.vfilterपूर्ण;
	पूर्णांक i, j, k;
	पूर्णांक32_t overscan = calc_overscan(tv_enc->overscan);
	पूर्णांक64_t flicker = (tv_enc->flicker - 50) * (id3 / 100);
	uपूर्णांक64_t rs[] = अणुmode->hdisplay * id3,
			 mode->vdisplay * id3पूर्ण;

	करो_भाग(rs[0], overscan * tv_norm->tv_enc_mode.hdisplay);
	करो_भाग(rs[1], overscan * tv_norm->tv_enc_mode.vdisplay);

	क्रम (k = 0; k < 2; k++) अणु
		rs[k] = max((पूर्णांक64_t)rs[k], id2);

		क्रम (j = 0; j < 4; j++) अणु
			काष्ठा filter_params *p = &fparams[k][j];

			क्रम (i = 0; i < 7; i++) अणु
				पूर्णांक64_t c = (p->k1 + p->ki*i + p->ki2*i*i +
					     p->ki3*i*i*i)
					+ (p->kr + p->kir*i + p->ki2r*i*i +
					   p->ki3r*i*i*i) * rs[k]
					+ (p->kf + p->kअगर*i + p->ki2f*i*i +
					   p->ki3f*i*i*i) * flicker
					+ (p->krf + p->kirf*i + p->ki2rf*i*i +
					   p->ki3rf*i*i*i) * flicker * rs[k];

				(*filters[k])[j][i] = (c + id5/2) >> 39
					& (0x1 << 31 | 0x7f << 9);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* Hardware state saving/restoring */

अटल व्योम tv_save_filter(काष्ठा drm_device *dev, uपूर्णांक32_t base,
			   uपूर्णांक32_t regs[4][7])
अणु
	पूर्णांक i, j;
	uपूर्णांक32_t offsets[] = अणु base, base + 0x1c, base + 0x40, base + 0x5c पूर्ण;

	क्रम (i = 0; i < 4; i++) अणु
		क्रम (j = 0; j < 7; j++)
			regs[i][j] = nv_पढ़ो_ptv(dev, offsets[i]+4*j);
	पूर्ण
पूर्ण

अटल व्योम tv_load_filter(काष्ठा drm_device *dev, uपूर्णांक32_t base,
			   uपूर्णांक32_t regs[4][7])
अणु
	पूर्णांक i, j;
	uपूर्णांक32_t offsets[] = अणु base, base + 0x1c, base + 0x40, base + 0x5c पूर्ण;

	क्रम (i = 0; i < 4; i++) अणु
		क्रम (j = 0; j < 7; j++)
			nv_ग_लिखो_ptv(dev, offsets[i]+4*j, regs[i][j]);
	पूर्ण
पूर्ण

व्योम nv17_tv_state_save(काष्ठा drm_device *dev, काष्ठा nv17_tv_state *state)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 0x40; i++)
		state->tv_enc[i] = nv_पढ़ो_tv_enc(dev, i);

	tv_save_filter(dev, NV_PTV_HFILTER, state->hfilter);
	tv_save_filter(dev, NV_PTV_HFILTER2, state->hfilter2);
	tv_save_filter(dev, NV_PTV_VFILTER, state->vfilter);

	nv_save_ptv(dev, state, 200);
	nv_save_ptv(dev, state, 204);
	nv_save_ptv(dev, state, 208);
	nv_save_ptv(dev, state, 20c);
	nv_save_ptv(dev, state, 304);
	nv_save_ptv(dev, state, 500);
	nv_save_ptv(dev, state, 504);
	nv_save_ptv(dev, state, 508);
	nv_save_ptv(dev, state, 600);
	nv_save_ptv(dev, state, 604);
	nv_save_ptv(dev, state, 608);
	nv_save_ptv(dev, state, 60c);
	nv_save_ptv(dev, state, 610);
	nv_save_ptv(dev, state, 614);
पूर्ण

व्योम nv17_tv_state_load(काष्ठा drm_device *dev, काष्ठा nv17_tv_state *state)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 0x40; i++)
		nv_ग_लिखो_tv_enc(dev, i, state->tv_enc[i]);

	tv_load_filter(dev, NV_PTV_HFILTER, state->hfilter);
	tv_load_filter(dev, NV_PTV_HFILTER2, state->hfilter2);
	tv_load_filter(dev, NV_PTV_VFILTER, state->vfilter);

	nv_load_ptv(dev, state, 200);
	nv_load_ptv(dev, state, 204);
	nv_load_ptv(dev, state, 208);
	nv_load_ptv(dev, state, 20c);
	nv_load_ptv(dev, state, 304);
	nv_load_ptv(dev, state, 500);
	nv_load_ptv(dev, state, 504);
	nv_load_ptv(dev, state, 508);
	nv_load_ptv(dev, state, 600);
	nv_load_ptv(dev, state, 604);
	nv_load_ptv(dev, state, 608);
	nv_load_ptv(dev, state, 60c);
	nv_load_ptv(dev, state, 610);
	nv_load_ptv(dev, state, 614);

	/* This is required क्रम some settings to kick in. */
	nv_ग_लिखो_tv_enc(dev, 0x3e, 1);
	nv_ग_लिखो_tv_enc(dev, 0x3e, 0);
पूर्ण

/* Timings similar to the ones the blob sets */

स्थिर काष्ठा drm_display_mode nv17_tv_modes[] = अणु
	अणु DRM_MODE("320x200", DRM_MODE_TYPE_DRIVER, 0,
		   320, 344, 392, 560, 0, 200, 200, 202, 220, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC
		   | DRM_MODE_FLAG_DBLSCAN | DRM_MODE_FLAG_CLKDIV2) पूर्ण,
	अणु DRM_MODE("320x240", DRM_MODE_TYPE_DRIVER, 0,
		   320, 344, 392, 560, 0, 240, 240, 246, 263, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC
		   | DRM_MODE_FLAG_DBLSCAN | DRM_MODE_FLAG_CLKDIV2) पूर्ण,
	अणु DRM_MODE("400x300", DRM_MODE_TYPE_DRIVER, 0,
		   400, 432, 496, 640, 0, 300, 300, 303, 314, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC
		   | DRM_MODE_FLAG_DBLSCAN | DRM_MODE_FLAG_CLKDIV2) पूर्ण,
	अणु DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 0,
		   640, 672, 768, 880, 0, 480, 480, 492, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	अणु DRM_MODE("720x480", DRM_MODE_TYPE_DRIVER, 0,
		   720, 752, 872, 960, 0, 480, 480, 493, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	अणु DRM_MODE("720x576", DRM_MODE_TYPE_DRIVER, 0,
		   720, 776, 856, 960, 0, 576, 576, 588, 597, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	अणु DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 0,
		   800, 840, 920, 1040, 0, 600, 600, 604, 618, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	अणु DRM_MODE("1024x768", DRM_MODE_TYPE_DRIVER, 0,
		   1024, 1064, 1200, 1344, 0, 768, 768, 777, 806, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	अणुपूर्ण
पूर्ण;

व्योम nv17_tv_update_properties(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा nv17_tv_encoder *tv_enc = to_tv_enc(encoder);
	काष्ठा nv17_tv_state *regs = &tv_enc->state;
	काष्ठा nv17_tv_norm_params *tv_norm = get_tv_norm(encoder);
	पूर्णांक subconnector = tv_enc->select_subconnector ?
						tv_enc->select_subconnector :
						tv_enc->subconnector;

	चयन (subconnector) अणु
	हाल DRM_MODE_SUBCONNECTOR_Composite:
	अणु
		regs->ptv_204 = 0x2;

		/* The composite connector may be found on either pin. */
		अगर (tv_enc->pin_mask & 0x4)
			regs->ptv_204 |= 0x010000;
		अन्यथा अगर (tv_enc->pin_mask & 0x2)
			regs->ptv_204 |= 0x100000;
		अन्यथा
			regs->ptv_204 |= 0x110000;

		regs->tv_enc[0x7] = 0x10;
		अवरोध;
	पूर्ण
	हाल DRM_MODE_SUBCONNECTOR_SVIDEO:
		regs->ptv_204 = 0x11012;
		regs->tv_enc[0x7] = 0x18;
		अवरोध;

	हाल DRM_MODE_SUBCONNECTOR_Component:
		regs->ptv_204 = 0x111333;
		regs->tv_enc[0x7] = 0x14;
		अवरोध;

	हाल DRM_MODE_SUBCONNECTOR_SCART:
		regs->ptv_204 = 0x111012;
		regs->tv_enc[0x7] = 0x18;
		अवरोध;
	पूर्ण

	regs->tv_enc[0x20] = पूर्णांकerpolate(0, tv_norm->tv_enc_mode.tv_enc[0x20],
					 255, tv_enc->saturation);
	regs->tv_enc[0x22] = पूर्णांकerpolate(0, tv_norm->tv_enc_mode.tv_enc[0x22],
					 255, tv_enc->saturation);
	regs->tv_enc[0x25] = tv_enc->hue * 255 / 100;

	nv_load_ptv(dev, regs, 204);
	nv_load_tv_enc(dev, regs, 7);
	nv_load_tv_enc(dev, regs, 20);
	nv_load_tv_enc(dev, regs, 22);
	nv_load_tv_enc(dev, regs, 25);
पूर्ण

व्योम nv17_tv_update_rescaler(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा nv17_tv_encoder *tv_enc = to_tv_enc(encoder);
	काष्ठा nv17_tv_state *regs = &tv_enc->state;

	regs->ptv_208 = 0x40 | (calc_overscan(tv_enc->overscan) << 8);

	tv_setup_filter(encoder);

	nv_load_ptv(dev, regs, 208);
	tv_load_filter(dev, NV_PTV_HFILTER, regs->hfilter);
	tv_load_filter(dev, NV_PTV_HFILTER2, regs->hfilter2);
	tv_load_filter(dev, NV_PTV_VFILTER, regs->vfilter);
पूर्ण

व्योम nv17_ctv_update_rescaler(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा nv17_tv_encoder *tv_enc = to_tv_enc(encoder);
	पूर्णांक head = nouveau_crtc(encoder->crtc)->index;
	काष्ठा nv04_crtc_reg *regs = &nv04_display(dev)->mode_reg.crtc_reg[head];
	काष्ठा drm_display_mode *crtc_mode = &encoder->crtc->mode;
	काष्ठा drm_display_mode *output_mode =
		&get_tv_norm(encoder)->ctv_enc_mode.mode;
	पूर्णांक overscan, hmargin, vmargin, hratio, vratio;

	/* The rescaler करोesn't करो the right thing क्रम पूर्णांकerlaced modes. */
	अगर (output_mode->flags & DRM_MODE_FLAG_INTERLACE)
		overscan = 100;
	अन्यथा
		overscan = tv_enc->overscan;

	hmargin = (output_mode->hdisplay - crtc_mode->hdisplay) / 2;
	vmargin = (output_mode->vdisplay - crtc_mode->vdisplay) / 2;

	hmargin = पूर्णांकerpolate(0, min(hmargin, output_mode->hdisplay/20),
			      hmargin, overscan);
	vmargin = पूर्णांकerpolate(0, min(vmargin, output_mode->vdisplay/20),
			      vmargin, overscan);

	hratio = crtc_mode->hdisplay * 0x800 /
		(output_mode->hdisplay - 2*hmargin);
	vratio = crtc_mode->vdisplay * 0x800 /
		(output_mode->vdisplay - 2*vmargin) & ~3;

	regs->fp_horiz_regs[FP_VALID_START] = hmargin;
	regs->fp_horiz_regs[FP_VALID_END] = output_mode->hdisplay - hmargin - 1;
	regs->fp_vert_regs[FP_VALID_START] = vmargin;
	regs->fp_vert_regs[FP_VALID_END] = output_mode->vdisplay - vmargin - 1;

	regs->fp_debug_1 = NV_PRAMDAC_FP_DEBUG_1_YSCALE_TESTMODE_ENABLE |
		XLATE(vratio, 0, NV_PRAMDAC_FP_DEBUG_1_YSCALE_VALUE) |
		NV_PRAMDAC_FP_DEBUG_1_XSCALE_TESTMODE_ENABLE |
		XLATE(hratio, 0, NV_PRAMDAC_FP_DEBUG_1_XSCALE_VALUE);

	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_HVALID_START,
		      regs->fp_horiz_regs[FP_VALID_START]);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_HVALID_END,
		      regs->fp_horiz_regs[FP_VALID_END]);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_VVALID_START,
		      regs->fp_vert_regs[FP_VALID_START]);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_VVALID_END,
		      regs->fp_vert_regs[FP_VALID_END]);
	NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_DEBUG_1, regs->fp_debug_1);
पूर्ण
