<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * v4l2-tpg-core.c - Test Pattern Generator
 *
 * Note: gen_twopix and tpg_gen_text are based on code from vivi.c. See the
 * vivi.c source क्रम the copyright inक्रमmation of those functions.
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <media/tpg/v4l2-tpg.h>

/* Must reमुख्य in sync with क्रमागत tpg_pattern */
स्थिर अक्षर * स्थिर tpg_pattern_strings[] = अणु
	"75% Colorbar",
	"100% Colorbar",
	"CSC Colorbar",
	"Horizontal 100% Colorbar",
	"100% Color Squares",
	"100% Black",
	"100% White",
	"100% Red",
	"100% Green",
	"100% Blue",
	"16x16 Checkers",
	"2x2 Checkers",
	"1x1 Checkers",
	"2x2 Red/Green Checkers",
	"1x1 Red/Green Checkers",
	"Alternating Hor Lines",
	"Alternating Vert Lines",
	"One Pixel Wide Cross",
	"Two Pixels Wide Cross",
	"Ten Pixels Wide Cross",
	"Gray Ramp",
	"Noise",
	शून्य
पूर्ण;
EXPORT_SYMBOL_GPL(tpg_pattern_strings);

/* Must reमुख्य in sync with क्रमागत tpg_aspect */
स्थिर अक्षर * स्थिर tpg_aspect_strings[] = अणु
	"Source Width x Height",
	"4x3",
	"14x9",
	"16x9",
	"16x9 Anamorphic",
	शून्य
पूर्ण;
EXPORT_SYMBOL_GPL(tpg_aspect_strings);

/*
 * Sine table: sin[0] = 127 * sin(-180 degrees)
 *             sin[128] = 127 * sin(0 degrees)
 *             sin[256] = 127 * sin(180 degrees)
 */
अटल स्थिर s8 sin[257] = अणु
	   0,   -4,   -7,  -11,  -13,  -18,  -20,  -22,  -26,  -29,  -33,  -35,  -37,  -41,  -43,  -48,
	 -50,  -52,  -56,  -58,  -62,  -63,  -65,  -69,  -71,  -75,  -76,  -78,  -82,  -83,  -87,  -88,
	 -90,  -93,  -94,  -97,  -99, -101, -103, -104, -107, -108, -110, -111, -112, -114, -115, -117,
	-118, -119, -120, -121, -122, -123, -123, -124, -125, -125, -126, -126, -127, -127, -127, -127,
	-127, -127, -127, -127, -126, -126, -125, -125, -124, -124, -123, -122, -121, -120, -119, -118,
	-117, -116, -114, -113, -111, -110, -109, -107, -105, -103, -101, -100,  -97,  -96,  -93,  -91,
	 -90,  -87,  -85,  -82,  -80,  -76,  -75,  -73,  -69,  -67,  -63,  -62,  -60,  -56,  -54,  -50,
	 -48,  -46,  -41,  -39,  -35,  -33,  -31,  -26,  -24,  -20,  -18,  -15,  -11,   -9,   -4,   -2,
	   0,    2,    4,    9,   11,   15,   18,   20,   24,   26,   31,   33,   35,   39,   41,   46,
	  48,   50,   54,   56,   60,   62,   64,   67,   69,   73,   75,   76,   80,   82,   85,   87,
	  90,   91,   93,   96,   97,  100,  101,  103,  105,  107,  109,  110,  111,  113,  114,  116,
	 117,  118,  119,  120,  121,  122,  123,  124,  124,  125,  125,  126,  126,  127,  127,  127,
	 127,  127,  127,  127,  127,  126,  126,  125,  125,  124,  123,  123,  122,  121,  120,  119,
	 118,  117,  115,  114,  112,  111,  110,  108,  107,  104,  103,  101,   99,   97,   94,   93,
	  90,   88,   87,   83,   82,   78,   76,   75,   71,   69,   65,   64,   62,   58,   56,   52,
	  50,   48,   43,   41,   37,   35,   33,   29,   26,   22,   20,   18,   13,   11,    7,    4,
	   0,
पूर्ण;

#घोषणा cos(idx) sin[((idx) + 64) % माप(sin)]

/* Global font descriptor */
अटल स्थिर u8 *font8x16;

व्योम tpg_set_font(स्थिर u8 *f)
अणु
	font8x16 = f;
पूर्ण
EXPORT_SYMBOL_GPL(tpg_set_font);

व्योम tpg_init(काष्ठा tpg_data *tpg, अचिन्हित w, अचिन्हित h)
अणु
	स_रखो(tpg, 0, माप(*tpg));
	tpg->scaled_width = tpg->src_width = w;
	tpg->src_height = tpg->buf_height = h;
	tpg->crop.width = tpg->compose.width = w;
	tpg->crop.height = tpg->compose.height = h;
	tpg->recalc_colors = true;
	tpg->recalc_square_border = true;
	tpg->brightness = 128;
	tpg->contrast = 128;
	tpg->saturation = 128;
	tpg->hue = 0;
	tpg->mv_hor_mode = TPG_MOVE_NONE;
	tpg->mv_vert_mode = TPG_MOVE_NONE;
	tpg->field = V4L2_FIELD_NONE;
	tpg_s_fourcc(tpg, V4L2_PIX_FMT_RGB24);
	tpg->colorspace = V4L2_COLORSPACE_SRGB;
	tpg->perc_fill = 100;
	tpg->hsv_enc = V4L2_HSV_ENC_180;
पूर्ण
EXPORT_SYMBOL_GPL(tpg_init);

पूर्णांक tpg_alloc(काष्ठा tpg_data *tpg, अचिन्हित max_w)
अणु
	अचिन्हित pat;
	अचिन्हित plane;

	tpg->max_line_width = max_w;
	क्रम (pat = 0; pat < TPG_MAX_PAT_LINES; pat++) अणु
		क्रम (plane = 0; plane < TPG_MAX_PLANES; plane++) अणु
			अचिन्हित pixelsz = plane ? 2 : 4;

			tpg->lines[pat][plane] =
				vzalloc(array3_size(max_w, 2, pixelsz));
			अगर (!tpg->lines[pat][plane])
				वापस -ENOMEM;
			अगर (plane == 0)
				जारी;
			tpg->करोwnsampled_lines[pat][plane] =
				vzalloc(array3_size(max_w, 2, pixelsz));
			अगर (!tpg->करोwnsampled_lines[pat][plane])
				वापस -ENOMEM;
		पूर्ण
	पूर्ण
	क्रम (plane = 0; plane < TPG_MAX_PLANES; plane++) अणु
		अचिन्हित pixelsz = plane ? 2 : 4;

		tpg->contrast_line[plane] =
			vzalloc(array_size(pixelsz, max_w));
		अगर (!tpg->contrast_line[plane])
			वापस -ENOMEM;
		tpg->black_line[plane] =
			vzalloc(array_size(pixelsz, max_w));
		अगर (!tpg->black_line[plane])
			वापस -ENOMEM;
		tpg->अक्रमom_line[plane] =
			vzalloc(array3_size(max_w, 2, pixelsz));
		अगर (!tpg->अक्रमom_line[plane])
			वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tpg_alloc);

व्योम tpg_मुक्त(काष्ठा tpg_data *tpg)
अणु
	अचिन्हित pat;
	अचिन्हित plane;

	क्रम (pat = 0; pat < TPG_MAX_PAT_LINES; pat++)
		क्रम (plane = 0; plane < TPG_MAX_PLANES; plane++) अणु
			vमुक्त(tpg->lines[pat][plane]);
			tpg->lines[pat][plane] = शून्य;
			अगर (plane == 0)
				जारी;
			vमुक्त(tpg->करोwnsampled_lines[pat][plane]);
			tpg->करोwnsampled_lines[pat][plane] = शून्य;
		पूर्ण
	क्रम (plane = 0; plane < TPG_MAX_PLANES; plane++) अणु
		vमुक्त(tpg->contrast_line[plane]);
		vमुक्त(tpg->black_line[plane]);
		vमुक्त(tpg->अक्रमom_line[plane]);
		tpg->contrast_line[plane] = शून्य;
		tpg->black_line[plane] = शून्य;
		tpg->अक्रमom_line[plane] = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(tpg_मुक्त);

bool tpg_s_fourcc(काष्ठा tpg_data *tpg, u32 fourcc)
अणु
	tpg->fourcc = fourcc;
	tpg->planes = 1;
	tpg->buffers = 1;
	tpg->recalc_colors = true;
	tpg->पूर्णांकerleaved = false;
	tpg->vकरोwnsampling[0] = 1;
	tpg->hकरोwnsampling[0] = 1;
	tpg->hmask[0] = ~0;
	tpg->hmask[1] = ~0;
	tpg->hmask[2] = ~0;

	चयन (fourcc) अणु
	हाल V4L2_PIX_FMT_SBGGR8:
	हाल V4L2_PIX_FMT_SGBRG8:
	हाल V4L2_PIX_FMT_SGRBG8:
	हाल V4L2_PIX_FMT_SRGGB8:
	हाल V4L2_PIX_FMT_SBGGR10:
	हाल V4L2_PIX_FMT_SGBRG10:
	हाल V4L2_PIX_FMT_SGRBG10:
	हाल V4L2_PIX_FMT_SRGGB10:
	हाल V4L2_PIX_FMT_SBGGR12:
	हाल V4L2_PIX_FMT_SGBRG12:
	हाल V4L2_PIX_FMT_SGRBG12:
	हाल V4L2_PIX_FMT_SRGGB12:
	हाल V4L2_PIX_FMT_SBGGR16:
	हाल V4L2_PIX_FMT_SGBRG16:
	हाल V4L2_PIX_FMT_SGRBG16:
	हाल V4L2_PIX_FMT_SRGGB16:
		tpg->पूर्णांकerleaved = true;
		tpg->vकरोwnsampling[1] = 1;
		tpg->hकरोwnsampling[1] = 1;
		tpg->planes = 2;
		fallthrough;
	हाल V4L2_PIX_FMT_RGB332:
	हाल V4L2_PIX_FMT_RGB565:
	हाल V4L2_PIX_FMT_RGB565X:
	हाल V4L2_PIX_FMT_RGB444:
	हाल V4L2_PIX_FMT_XRGB444:
	हाल V4L2_PIX_FMT_ARGB444:
	हाल V4L2_PIX_FMT_RGBX444:
	हाल V4L2_PIX_FMT_RGBA444:
	हाल V4L2_PIX_FMT_XBGR444:
	हाल V4L2_PIX_FMT_ABGR444:
	हाल V4L2_PIX_FMT_BGRX444:
	हाल V4L2_PIX_FMT_BGRA444:
	हाल V4L2_PIX_FMT_RGB555:
	हाल V4L2_PIX_FMT_XRGB555:
	हाल V4L2_PIX_FMT_ARGB555:
	हाल V4L2_PIX_FMT_RGBX555:
	हाल V4L2_PIX_FMT_RGBA555:
	हाल V4L2_PIX_FMT_XBGR555:
	हाल V4L2_PIX_FMT_ABGR555:
	हाल V4L2_PIX_FMT_BGRX555:
	हाल V4L2_PIX_FMT_BGRA555:
	हाल V4L2_PIX_FMT_RGB555X:
	हाल V4L2_PIX_FMT_XRGB555X:
	हाल V4L2_PIX_FMT_ARGB555X:
	हाल V4L2_PIX_FMT_BGR666:
	हाल V4L2_PIX_FMT_RGB24:
	हाल V4L2_PIX_FMT_BGR24:
	हाल V4L2_PIX_FMT_RGB32:
	हाल V4L2_PIX_FMT_BGR32:
	हाल V4L2_PIX_FMT_XRGB32:
	हाल V4L2_PIX_FMT_XBGR32:
	हाल V4L2_PIX_FMT_ARGB32:
	हाल V4L2_PIX_FMT_ABGR32:
	हाल V4L2_PIX_FMT_RGBX32:
	हाल V4L2_PIX_FMT_BGRX32:
	हाल V4L2_PIX_FMT_RGBA32:
	हाल V4L2_PIX_FMT_BGRA32:
		tpg->color_enc = TGP_COLOR_ENC_RGB;
		अवरोध;
	हाल V4L2_PIX_FMT_GREY:
	हाल V4L2_PIX_FMT_Y10:
	हाल V4L2_PIX_FMT_Y12:
	हाल V4L2_PIX_FMT_Y16:
	हाल V4L2_PIX_FMT_Y16_BE:
	हाल V4L2_PIX_FMT_Z16:
		tpg->color_enc = TGP_COLOR_ENC_LUMA;
		अवरोध;
	हाल V4L2_PIX_FMT_YUV444:
	हाल V4L2_PIX_FMT_YUV555:
	हाल V4L2_PIX_FMT_YUV565:
	हाल V4L2_PIX_FMT_YUV32:
	हाल V4L2_PIX_FMT_AYUV32:
	हाल V4L2_PIX_FMT_XYUV32:
	हाल V4L2_PIX_FMT_VUYA32:
	हाल V4L2_PIX_FMT_VUYX32:
		tpg->color_enc = TGP_COLOR_ENC_YCBCR;
		अवरोध;
	हाल V4L2_PIX_FMT_YUV420M:
	हाल V4L2_PIX_FMT_YVU420M:
		tpg->buffers = 3;
		fallthrough;
	हाल V4L2_PIX_FMT_YUV420:
	हाल V4L2_PIX_FMT_YVU420:
		tpg->vकरोwnsampling[1] = 2;
		tpg->vकरोwnsampling[2] = 2;
		tpg->hकरोwnsampling[1] = 2;
		tpg->hकरोwnsampling[2] = 2;
		tpg->planes = 3;
		tpg->color_enc = TGP_COLOR_ENC_YCBCR;
		अवरोध;
	हाल V4L2_PIX_FMT_YUV422M:
	हाल V4L2_PIX_FMT_YVU422M:
		tpg->buffers = 3;
		fallthrough;
	हाल V4L2_PIX_FMT_YUV422P:
		tpg->vकरोwnsampling[1] = 1;
		tpg->vकरोwnsampling[2] = 1;
		tpg->hकरोwnsampling[1] = 2;
		tpg->hकरोwnsampling[2] = 2;
		tpg->planes = 3;
		tpg->color_enc = TGP_COLOR_ENC_YCBCR;
		अवरोध;
	हाल V4L2_PIX_FMT_NV16M:
	हाल V4L2_PIX_FMT_NV61M:
		tpg->buffers = 2;
		fallthrough;
	हाल V4L2_PIX_FMT_NV16:
	हाल V4L2_PIX_FMT_NV61:
		tpg->vकरोwnsampling[1] = 1;
		tpg->hकरोwnsampling[1] = 1;
		tpg->hmask[1] = ~1;
		tpg->planes = 2;
		tpg->color_enc = TGP_COLOR_ENC_YCBCR;
		अवरोध;
	हाल V4L2_PIX_FMT_NV12M:
	हाल V4L2_PIX_FMT_NV21M:
		tpg->buffers = 2;
		fallthrough;
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV21:
		tpg->vकरोwnsampling[1] = 2;
		tpg->hकरोwnsampling[1] = 1;
		tpg->hmask[1] = ~1;
		tpg->planes = 2;
		tpg->color_enc = TGP_COLOR_ENC_YCBCR;
		अवरोध;
	हाल V4L2_PIX_FMT_YUV444M:
	हाल V4L2_PIX_FMT_YVU444M:
		tpg->buffers = 3;
		tpg->planes = 3;
		tpg->vकरोwnsampling[1] = 1;
		tpg->vकरोwnsampling[2] = 1;
		tpg->hकरोwnsampling[1] = 1;
		tpg->hकरोwnsampling[2] = 1;
		tpg->color_enc = TGP_COLOR_ENC_YCBCR;
		अवरोध;
	हाल V4L2_PIX_FMT_NV24:
	हाल V4L2_PIX_FMT_NV42:
		tpg->vकरोwnsampling[1] = 1;
		tpg->hकरोwnsampling[1] = 1;
		tpg->planes = 2;
		tpg->color_enc = TGP_COLOR_ENC_YCBCR;
		अवरोध;
	हाल V4L2_PIX_FMT_YUYV:
	हाल V4L2_PIX_FMT_UYVY:
	हाल V4L2_PIX_FMT_YVYU:
	हाल V4L2_PIX_FMT_VYUY:
		tpg->hmask[0] = ~1;
		tpg->color_enc = TGP_COLOR_ENC_YCBCR;
		अवरोध;
	हाल V4L2_PIX_FMT_HSV24:
	हाल V4L2_PIX_FMT_HSV32:
		tpg->color_enc = TGP_COLOR_ENC_HSV;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	चयन (fourcc) अणु
	हाल V4L2_PIX_FMT_GREY:
	हाल V4L2_PIX_FMT_RGB332:
		tpg->twopixelsize[0] = 2;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB565:
	हाल V4L2_PIX_FMT_RGB565X:
	हाल V4L2_PIX_FMT_RGB444:
	हाल V4L2_PIX_FMT_XRGB444:
	हाल V4L2_PIX_FMT_ARGB444:
	हाल V4L2_PIX_FMT_RGBX444:
	हाल V4L2_PIX_FMT_RGBA444:
	हाल V4L2_PIX_FMT_XBGR444:
	हाल V4L2_PIX_FMT_ABGR444:
	हाल V4L2_PIX_FMT_BGRX444:
	हाल V4L2_PIX_FMT_BGRA444:
	हाल V4L2_PIX_FMT_RGB555:
	हाल V4L2_PIX_FMT_XRGB555:
	हाल V4L2_PIX_FMT_ARGB555:
	हाल V4L2_PIX_FMT_RGBX555:
	हाल V4L2_PIX_FMT_RGBA555:
	हाल V4L2_PIX_FMT_XBGR555:
	हाल V4L2_PIX_FMT_ABGR555:
	हाल V4L2_PIX_FMT_BGRX555:
	हाल V4L2_PIX_FMT_BGRA555:
	हाल V4L2_PIX_FMT_RGB555X:
	हाल V4L2_PIX_FMT_XRGB555X:
	हाल V4L2_PIX_FMT_ARGB555X:
	हाल V4L2_PIX_FMT_YUYV:
	हाल V4L2_PIX_FMT_UYVY:
	हाल V4L2_PIX_FMT_YVYU:
	हाल V4L2_PIX_FMT_VYUY:
	हाल V4L2_PIX_FMT_YUV444:
	हाल V4L2_PIX_FMT_YUV555:
	हाल V4L2_PIX_FMT_YUV565:
	हाल V4L2_PIX_FMT_Y10:
	हाल V4L2_PIX_FMT_Y12:
	हाल V4L2_PIX_FMT_Y16:
	हाल V4L2_PIX_FMT_Y16_BE:
	हाल V4L2_PIX_FMT_Z16:
		tpg->twopixelsize[0] = 2 * 2;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB24:
	हाल V4L2_PIX_FMT_BGR24:
	हाल V4L2_PIX_FMT_HSV24:
		tpg->twopixelsize[0] = 2 * 3;
		अवरोध;
	हाल V4L2_PIX_FMT_BGR666:
	हाल V4L2_PIX_FMT_RGB32:
	हाल V4L2_PIX_FMT_BGR32:
	हाल V4L2_PIX_FMT_XRGB32:
	हाल V4L2_PIX_FMT_XBGR32:
	हाल V4L2_PIX_FMT_ARGB32:
	हाल V4L2_PIX_FMT_ABGR32:
	हाल V4L2_PIX_FMT_RGBX32:
	हाल V4L2_PIX_FMT_BGRX32:
	हाल V4L2_PIX_FMT_RGBA32:
	हाल V4L2_PIX_FMT_BGRA32:
	हाल V4L2_PIX_FMT_YUV32:
	हाल V4L2_PIX_FMT_AYUV32:
	हाल V4L2_PIX_FMT_XYUV32:
	हाल V4L2_PIX_FMT_VUYA32:
	हाल V4L2_PIX_FMT_VUYX32:
	हाल V4L2_PIX_FMT_HSV32:
		tpg->twopixelsize[0] = 2 * 4;
		अवरोध;
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV21:
	हाल V4L2_PIX_FMT_NV12M:
	हाल V4L2_PIX_FMT_NV21M:
	हाल V4L2_PIX_FMT_NV16:
	हाल V4L2_PIX_FMT_NV61:
	हाल V4L2_PIX_FMT_NV16M:
	हाल V4L2_PIX_FMT_NV61M:
	हाल V4L2_PIX_FMT_SBGGR8:
	हाल V4L2_PIX_FMT_SGBRG8:
	हाल V4L2_PIX_FMT_SGRBG8:
	हाल V4L2_PIX_FMT_SRGGB8:
		tpg->twopixelsize[0] = 2;
		tpg->twopixelsize[1] = 2;
		अवरोध;
	हाल V4L2_PIX_FMT_SRGGB10:
	हाल V4L2_PIX_FMT_SGRBG10:
	हाल V4L2_PIX_FMT_SGBRG10:
	हाल V4L2_PIX_FMT_SBGGR10:
	हाल V4L2_PIX_FMT_SRGGB12:
	हाल V4L2_PIX_FMT_SGRBG12:
	हाल V4L2_PIX_FMT_SGBRG12:
	हाल V4L2_PIX_FMT_SBGGR12:
	हाल V4L2_PIX_FMT_SRGGB16:
	हाल V4L2_PIX_FMT_SGRBG16:
	हाल V4L2_PIX_FMT_SGBRG16:
	हाल V4L2_PIX_FMT_SBGGR16:
		tpg->twopixelsize[0] = 4;
		tpg->twopixelsize[1] = 4;
		अवरोध;
	हाल V4L2_PIX_FMT_YUV444M:
	हाल V4L2_PIX_FMT_YVU444M:
	हाल V4L2_PIX_FMT_YUV422M:
	हाल V4L2_PIX_FMT_YVU422M:
	हाल V4L2_PIX_FMT_YUV422P:
	हाल V4L2_PIX_FMT_YUV420:
	हाल V4L2_PIX_FMT_YVU420:
	हाल V4L2_PIX_FMT_YUV420M:
	हाल V4L2_PIX_FMT_YVU420M:
		tpg->twopixelsize[0] = 2;
		tpg->twopixelsize[1] = 2;
		tpg->twopixelsize[2] = 2;
		अवरोध;
	हाल V4L2_PIX_FMT_NV24:
	हाल V4L2_PIX_FMT_NV42:
		tpg->twopixelsize[0] = 2;
		tpg->twopixelsize[1] = 4;
		अवरोध;
	पूर्ण
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(tpg_s_fourcc);

व्योम tpg_s_crop_compose(काष्ठा tpg_data *tpg, स्थिर काष्ठा v4l2_rect *crop,
		स्थिर काष्ठा v4l2_rect *compose)
अणु
	tpg->crop = *crop;
	tpg->compose = *compose;
	tpg->scaled_width = (tpg->src_width * tpg->compose.width +
				 tpg->crop.width - 1) / tpg->crop.width;
	tpg->scaled_width &= ~1;
	अगर (tpg->scaled_width > tpg->max_line_width)
		tpg->scaled_width = tpg->max_line_width;
	अगर (tpg->scaled_width < 2)
		tpg->scaled_width = 2;
	tpg->recalc_lines = true;
पूर्ण
EXPORT_SYMBOL_GPL(tpg_s_crop_compose);

व्योम tpg_reset_source(काष्ठा tpg_data *tpg, अचिन्हित width, अचिन्हित height,
		       u32 field)
अणु
	अचिन्हित p;

	tpg->src_width = width;
	tpg->src_height = height;
	tpg->field = field;
	tpg->buf_height = height;
	अगर (V4L2_FIELD_HAS_T_OR_B(field))
		tpg->buf_height /= 2;
	tpg->scaled_width = width;
	tpg->crop.top = tpg->crop.left = 0;
	tpg->crop.width = width;
	tpg->crop.height = height;
	tpg->compose.top = tpg->compose.left = 0;
	tpg->compose.width = width;
	tpg->compose.height = tpg->buf_height;
	क्रम (p = 0; p < tpg->planes; p++)
		tpg->bytesperline[p] = (width * tpg->twopixelsize[p]) /
				       (2 * tpg->hकरोwnsampling[p]);
	tpg->recalc_square_border = true;
पूर्ण
EXPORT_SYMBOL_GPL(tpg_reset_source);

अटल क्रमागत tpg_color tpg_get_textbg_color(काष्ठा tpg_data *tpg)
अणु
	चयन (tpg->pattern) अणु
	हाल TPG_PAT_BLACK:
		वापस TPG_COLOR_100_WHITE;
	हाल TPG_PAT_CSC_COLORBAR:
		वापस TPG_COLOR_CSC_BLACK;
	शेष:
		वापस TPG_COLOR_100_BLACK;
	पूर्ण
पूर्ण

अटल क्रमागत tpg_color tpg_get_textfg_color(काष्ठा tpg_data *tpg)
अणु
	चयन (tpg->pattern) अणु
	हाल TPG_PAT_75_COLORBAR:
	हाल TPG_PAT_CSC_COLORBAR:
		वापस TPG_COLOR_CSC_WHITE;
	हाल TPG_PAT_BLACK:
		वापस TPG_COLOR_100_BLACK;
	शेष:
		वापस TPG_COLOR_100_WHITE;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक rec709_to_linear(पूर्णांक v)
अणु
	v = clamp(v, 0, 0xff0);
	वापस tpg_rec709_to_linear[v];
पूर्ण

अटल अंतरभूत पूर्णांक linear_to_rec709(पूर्णांक v)
अणु
	v = clamp(v, 0, 0xff0);
	वापस tpg_linear_to_rec709[v];
पूर्ण

अटल व्योम color_to_hsv(काष्ठा tpg_data *tpg, पूर्णांक r, पूर्णांक g, पूर्णांक b,
			   पूर्णांक *h, पूर्णांक *s, पूर्णांक *v)
अणु
	पूर्णांक max_rgb, min_rgb, dअगरf_rgb;
	पूर्णांक aux;
	पूर्णांक third;
	पूर्णांक third_size;

	r >>= 4;
	g >>= 4;
	b >>= 4;

	/* Value */
	max_rgb = max3(r, g, b);
	*v = max_rgb;
	अगर (!max_rgb) अणु
		*h = 0;
		*s = 0;
		वापस;
	पूर्ण

	/* Saturation */
	min_rgb = min3(r, g, b);
	dअगरf_rgb = max_rgb - min_rgb;
	aux = 255 * dअगरf_rgb;
	aux += max_rgb / 2;
	aux /= max_rgb;
	*s = aux;
	अगर (!aux) अणु
		*h = 0;
		वापस;
	पूर्ण

	third_size = (tpg->real_hsv_enc == V4L2_HSV_ENC_180) ? 60 : 85;

	/* Hue */
	अगर (max_rgb == r) अणु
		aux =  g - b;
		third = 0;
	पूर्ण अन्यथा अगर (max_rgb == g) अणु
		aux =  b - r;
		third = third_size;
	पूर्ण अन्यथा अणु
		aux =  r - g;
		third = third_size * 2;
	पूर्ण

	aux *= third_size / 2;
	aux += dअगरf_rgb / 2;
	aux /= dअगरf_rgb;
	aux += third;

	/* Clamp Hue */
	अगर (tpg->real_hsv_enc == V4L2_HSV_ENC_180) अणु
		अगर (aux < 0)
			aux += 180;
		अन्यथा अगर (aux > 180)
			aux -= 180;
	पूर्ण अन्यथा अणु
		aux = aux & 0xff;
	पूर्ण

	*h = aux;
पूर्ण

अटल व्योम rgb2ycbcr(स्थिर पूर्णांक m[3][3], पूर्णांक r, पूर्णांक g, पूर्णांक b,
			पूर्णांक y_offset, पूर्णांक *y, पूर्णांक *cb, पूर्णांक *cr)
अणु
	*y  = ((m[0][0] * r + m[0][1] * g + m[0][2] * b) >> 16) + (y_offset << 4);
	*cb = ((m[1][0] * r + m[1][1] * g + m[1][2] * b) >> 16) + (128 << 4);
	*cr = ((m[2][0] * r + m[2][1] * g + m[2][2] * b) >> 16) + (128 << 4);
पूर्ण

अटल व्योम color_to_ycbcr(काष्ठा tpg_data *tpg, पूर्णांक r, पूर्णांक g, पूर्णांक b,
			   पूर्णांक *y, पूर्णांक *cb, पूर्णांक *cr)
अणु
#घोषणा COEFF(v, r) ((पूर्णांक)(0.5 + (v) * (r) * 256.0))

	अटल स्थिर पूर्णांक bt601[3][3] = अणु
		अणु COEFF(0.299, 219),   COEFF(0.587, 219),   COEFF(0.114, 219)   पूर्ण,
		अणु COEFF(-0.1687, 224), COEFF(-0.3313, 224), COEFF(0.5, 224)     पूर्ण,
		अणु COEFF(0.5, 224),     COEFF(-0.4187, 224), COEFF(-0.0813, 224) पूर्ण,
	पूर्ण;
	अटल स्थिर पूर्णांक bt601_full[3][3] = अणु
		अणु COEFF(0.299, 255),   COEFF(0.587, 255),   COEFF(0.114, 255)   पूर्ण,
		अणु COEFF(-0.1687, 255), COEFF(-0.3313, 255), COEFF(0.5, 255)     पूर्ण,
		अणु COEFF(0.5, 255),     COEFF(-0.4187, 255), COEFF(-0.0813, 255) पूर्ण,
	पूर्ण;
	अटल स्थिर पूर्णांक rec709[3][3] = अणु
		अणु COEFF(0.2126, 219),  COEFF(0.7152, 219),  COEFF(0.0722, 219)  पूर्ण,
		अणु COEFF(-0.1146, 224), COEFF(-0.3854, 224), COEFF(0.5, 224)     पूर्ण,
		अणु COEFF(0.5, 224),     COEFF(-0.4542, 224), COEFF(-0.0458, 224) पूर्ण,
	पूर्ण;
	अटल स्थिर पूर्णांक rec709_full[3][3] = अणु
		अणु COEFF(0.2126, 255),  COEFF(0.7152, 255),  COEFF(0.0722, 255)  पूर्ण,
		अणु COEFF(-0.1146, 255), COEFF(-0.3854, 255), COEFF(0.5, 255)     पूर्ण,
		अणु COEFF(0.5, 255),     COEFF(-0.4542, 255), COEFF(-0.0458, 255) पूर्ण,
	पूर्ण;
	अटल स्थिर पूर्णांक smpte240m[3][3] = अणु
		अणु COEFF(0.212, 219),  COEFF(0.701, 219),  COEFF(0.087, 219)  पूर्ण,
		अणु COEFF(-0.116, 224), COEFF(-0.384, 224), COEFF(0.5, 224)    पूर्ण,
		अणु COEFF(0.5, 224),    COEFF(-0.445, 224), COEFF(-0.055, 224) पूर्ण,
	पूर्ण;
	अटल स्थिर पूर्णांक smpte240m_full[3][3] = अणु
		अणु COEFF(0.212, 255),  COEFF(0.701, 255),  COEFF(0.087, 255)  पूर्ण,
		अणु COEFF(-0.116, 255), COEFF(-0.384, 255), COEFF(0.5, 255)    पूर्ण,
		अणु COEFF(0.5, 255),    COEFF(-0.445, 255), COEFF(-0.055, 255) पूर्ण,
	पूर्ण;
	अटल स्थिर पूर्णांक bt2020[3][3] = अणु
		अणु COEFF(0.2627, 219),  COEFF(0.6780, 219),  COEFF(0.0593, 219)  पूर्ण,
		अणु COEFF(-0.1396, 224), COEFF(-0.3604, 224), COEFF(0.5, 224)     पूर्ण,
		अणु COEFF(0.5, 224),     COEFF(-0.4598, 224), COEFF(-0.0402, 224) पूर्ण,
	पूर्ण;
	अटल स्थिर पूर्णांक bt2020_full[3][3] = अणु
		अणु COEFF(0.2627, 255),  COEFF(0.6780, 255),  COEFF(0.0593, 255)  पूर्ण,
		अणु COEFF(-0.1396, 255), COEFF(-0.3604, 255), COEFF(0.5, 255)     पूर्ण,
		अणु COEFF(0.5, 255),     COEFF(-0.4598, 255), COEFF(-0.0402, 255) पूर्ण,
	पूर्ण;
	अटल स्थिर पूर्णांक bt2020c[4] = अणु
		COEFF(1.0 / 1.9404, 224), COEFF(1.0 / 1.5816, 224),
		COEFF(1.0 / 1.7184, 224), COEFF(1.0 / 0.9936, 224),
	पूर्ण;
	अटल स्थिर पूर्णांक bt2020c_full[4] = अणु
		COEFF(1.0 / 1.9404, 255), COEFF(1.0 / 1.5816, 255),
		COEFF(1.0 / 1.7184, 255), COEFF(1.0 / 0.9936, 255),
	पूर्ण;

	bool full = tpg->real_quantization == V4L2_QUANTIZATION_FULL_RANGE;
	अचिन्हित y_offset = full ? 0 : 16;
	पूर्णांक lin_y, yc;

	चयन (tpg->real_ycbcr_enc) अणु
	हाल V4L2_YCBCR_ENC_601:
		rgb2ycbcr(full ? bt601_full : bt601, r, g, b, y_offset, y, cb, cr);
		अवरोध;
	हाल V4L2_YCBCR_ENC_XV601:
		/* Ignore quantization range, there is only one possible
		 * Y'CbCr encoding. */
		rgb2ycbcr(bt601, r, g, b, 16, y, cb, cr);
		अवरोध;
	हाल V4L2_YCBCR_ENC_XV709:
		/* Ignore quantization range, there is only one possible
		 * Y'CbCr encoding. */
		rgb2ycbcr(rec709, r, g, b, 16, y, cb, cr);
		अवरोध;
	हाल V4L2_YCBCR_ENC_BT2020:
		rgb2ycbcr(full ? bt2020_full : bt2020, r, g, b, y_offset, y, cb, cr);
		अवरोध;
	हाल V4L2_YCBCR_ENC_BT2020_CONST_LUM:
		lin_y = (COEFF(0.2627, 255) * rec709_to_linear(r) +
			 COEFF(0.6780, 255) * rec709_to_linear(g) +
			 COEFF(0.0593, 255) * rec709_to_linear(b)) >> 16;
		yc = linear_to_rec709(lin_y);
		*y = full ? yc : (yc * 219) / 255 + (16 << 4);
		अगर (b <= yc)
			*cb = (((b - yc) * (full ? bt2020c_full[0] : bt2020c[0])) >> 16) + (128 << 4);
		अन्यथा
			*cb = (((b - yc) * (full ? bt2020c_full[1] : bt2020c[1])) >> 16) + (128 << 4);
		अगर (r <= yc)
			*cr = (((r - yc) * (full ? bt2020c_full[2] : bt2020c[2])) >> 16) + (128 << 4);
		अन्यथा
			*cr = (((r - yc) * (full ? bt2020c_full[3] : bt2020c[3])) >> 16) + (128 << 4);
		अवरोध;
	हाल V4L2_YCBCR_ENC_SMPTE240M:
		rgb2ycbcr(full ? smpte240m_full : smpte240m, r, g, b, y_offset, y, cb, cr);
		अवरोध;
	हाल V4L2_YCBCR_ENC_709:
	शेष:
		rgb2ycbcr(full ? rec709_full : rec709, r, g, b, y_offset, y, cb, cr);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ycbcr2rgb(स्थिर पूर्णांक m[3][3], पूर्णांक y, पूर्णांक cb, पूर्णांक cr,
			पूर्णांक y_offset, पूर्णांक *r, पूर्णांक *g, पूर्णांक *b)
अणु
	y -= y_offset << 4;
	cb -= 128 << 4;
	cr -= 128 << 4;
	*r = m[0][0] * y + m[0][1] * cb + m[0][2] * cr;
	*g = m[1][0] * y + m[1][1] * cb + m[1][2] * cr;
	*b = m[2][0] * y + m[2][1] * cb + m[2][2] * cr;
	*r = clamp(*r >> 12, 0, 0xff0);
	*g = clamp(*g >> 12, 0, 0xff0);
	*b = clamp(*b >> 12, 0, 0xff0);
पूर्ण

अटल व्योम ycbcr_to_color(काष्ठा tpg_data *tpg, पूर्णांक y, पूर्णांक cb, पूर्णांक cr,
			   पूर्णांक *r, पूर्णांक *g, पूर्णांक *b)
अणु
#अघोषित COEFF
#घोषणा COEFF(v, r) ((पूर्णांक)(0.5 + (v) * ((255.0 * 255.0 * 16.0) / (r))))
	अटल स्थिर पूर्णांक bt601[3][3] = अणु
		अणु COEFF(1, 219), COEFF(0, 224),       COEFF(1.4020, 224)  पूर्ण,
		अणु COEFF(1, 219), COEFF(-0.3441, 224), COEFF(-0.7141, 224) पूर्ण,
		अणु COEFF(1, 219), COEFF(1.7720, 224),  COEFF(0, 224)       पूर्ण,
	पूर्ण;
	अटल स्थिर पूर्णांक bt601_full[3][3] = अणु
		अणु COEFF(1, 255), COEFF(0, 255),       COEFF(1.4020, 255)  पूर्ण,
		अणु COEFF(1, 255), COEFF(-0.3441, 255), COEFF(-0.7141, 255) पूर्ण,
		अणु COEFF(1, 255), COEFF(1.7720, 255),  COEFF(0, 255)       पूर्ण,
	पूर्ण;
	अटल स्थिर पूर्णांक rec709[3][3] = अणु
		अणु COEFF(1, 219), COEFF(0, 224),       COEFF(1.5748, 224)  पूर्ण,
		अणु COEFF(1, 219), COEFF(-0.1873, 224), COEFF(-0.4681, 224) पूर्ण,
		अणु COEFF(1, 219), COEFF(1.8556, 224),  COEFF(0, 224)       पूर्ण,
	पूर्ण;
	अटल स्थिर पूर्णांक rec709_full[3][3] = अणु
		अणु COEFF(1, 255), COEFF(0, 255),       COEFF(1.5748, 255)  पूर्ण,
		अणु COEFF(1, 255), COEFF(-0.1873, 255), COEFF(-0.4681, 255) पूर्ण,
		अणु COEFF(1, 255), COEFF(1.8556, 255),  COEFF(0, 255)       पूर्ण,
	पूर्ण;
	अटल स्थिर पूर्णांक smpte240m[3][3] = अणु
		अणु COEFF(1, 219), COEFF(0, 224),       COEFF(1.5756, 224)  पूर्ण,
		अणु COEFF(1, 219), COEFF(-0.2253, 224), COEFF(-0.4767, 224) पूर्ण,
		अणु COEFF(1, 219), COEFF(1.8270, 224),  COEFF(0, 224)       पूर्ण,
	पूर्ण;
	अटल स्थिर पूर्णांक smpte240m_full[3][3] = अणु
		अणु COEFF(1, 255), COEFF(0, 255),       COEFF(1.5756, 255)  पूर्ण,
		अणु COEFF(1, 255), COEFF(-0.2253, 255), COEFF(-0.4767, 255) पूर्ण,
		अणु COEFF(1, 255), COEFF(1.8270, 255),  COEFF(0, 255)       पूर्ण,
	पूर्ण;
	अटल स्थिर पूर्णांक bt2020[3][3] = अणु
		अणु COEFF(1, 219), COEFF(0, 224),       COEFF(1.4746, 224)  पूर्ण,
		अणु COEFF(1, 219), COEFF(-0.1646, 224), COEFF(-0.5714, 224) पूर्ण,
		अणु COEFF(1, 219), COEFF(1.8814, 224),  COEFF(0, 224)       पूर्ण,
	पूर्ण;
	अटल स्थिर पूर्णांक bt2020_full[3][3] = अणु
		अणु COEFF(1, 255), COEFF(0, 255),       COEFF(1.4746, 255)  पूर्ण,
		अणु COEFF(1, 255), COEFF(-0.1646, 255), COEFF(-0.5714, 255) पूर्ण,
		अणु COEFF(1, 255), COEFF(1.8814, 255),  COEFF(0, 255)       पूर्ण,
	पूर्ण;
	अटल स्थिर पूर्णांक bt2020c[4] = अणु
		COEFF(1.9404, 224), COEFF(1.5816, 224),
		COEFF(1.7184, 224), COEFF(0.9936, 224),
	पूर्ण;
	अटल स्थिर पूर्णांक bt2020c_full[4] = अणु
		COEFF(1.9404, 255), COEFF(1.5816, 255),
		COEFF(1.7184, 255), COEFF(0.9936, 255),
	पूर्ण;

	bool full = tpg->real_quantization == V4L2_QUANTIZATION_FULL_RANGE;
	अचिन्हित y_offset = full ? 0 : 16;
	पूर्णांक y_fac = full ? COEFF(1.0, 255) : COEFF(1.0, 219);
	पूर्णांक lin_r, lin_g, lin_b, lin_y;

	चयन (tpg->real_ycbcr_enc) अणु
	हाल V4L2_YCBCR_ENC_601:
		ycbcr2rgb(full ? bt601_full : bt601, y, cb, cr, y_offset, r, g, b);
		अवरोध;
	हाल V4L2_YCBCR_ENC_XV601:
		/* Ignore quantization range, there is only one possible
		 * Y'CbCr encoding. */
		ycbcr2rgb(bt601, y, cb, cr, 16, r, g, b);
		अवरोध;
	हाल V4L2_YCBCR_ENC_XV709:
		/* Ignore quantization range, there is only one possible
		 * Y'CbCr encoding. */
		ycbcr2rgb(rec709, y, cb, cr, 16, r, g, b);
		अवरोध;
	हाल V4L2_YCBCR_ENC_BT2020:
		ycbcr2rgb(full ? bt2020_full : bt2020, y, cb, cr, y_offset, r, g, b);
		अवरोध;
	हाल V4L2_YCBCR_ENC_BT2020_CONST_LUM:
		y -= full ? 0 : 16 << 4;
		cb -= 128 << 4;
		cr -= 128 << 4;

		अगर (cb <= 0)
			*b = y_fac * y + (full ? bt2020c_full[0] : bt2020c[0]) * cb;
		अन्यथा
			*b = y_fac * y + (full ? bt2020c_full[1] : bt2020c[1]) * cb;
		*b = *b >> 12;
		अगर (cr <= 0)
			*r = y_fac * y + (full ? bt2020c_full[2] : bt2020c[2]) * cr;
		अन्यथा
			*r = y_fac * y + (full ? bt2020c_full[3] : bt2020c[3]) * cr;
		*r = *r >> 12;
		lin_r = rec709_to_linear(*r);
		lin_b = rec709_to_linear(*b);
		lin_y = rec709_to_linear((y * 255) / (full ? 255 : 219));

		lin_g = COEFF(1.0 / 0.6780, 255) * lin_y -
			COEFF(0.2627 / 0.6780, 255) * lin_r -
			COEFF(0.0593 / 0.6780, 255) * lin_b;
		*g = linear_to_rec709(lin_g >> 12);
		अवरोध;
	हाल V4L2_YCBCR_ENC_SMPTE240M:
		ycbcr2rgb(full ? smpte240m_full : smpte240m, y, cb, cr, y_offset, r, g, b);
		अवरोध;
	हाल V4L2_YCBCR_ENC_709:
	शेष:
		ycbcr2rgb(full ? rec709_full : rec709, y, cb, cr, y_offset, r, g, b);
		अवरोध;
	पूर्ण
पूर्ण

/* precalculate color bar values to speed up rendering */
अटल व्योम precalculate_color(काष्ठा tpg_data *tpg, पूर्णांक k)
अणु
	पूर्णांक col = k;
	पूर्णांक r = tpg_colors[col].r;
	पूर्णांक g = tpg_colors[col].g;
	पूर्णांक b = tpg_colors[col].b;
	पूर्णांक y, cb, cr;
	bool ycbcr_valid = false;

	अगर (k == TPG_COLOR_TEXTBG) अणु
		col = tpg_get_textbg_color(tpg);

		r = tpg_colors[col].r;
		g = tpg_colors[col].g;
		b = tpg_colors[col].b;
	पूर्ण अन्यथा अगर (k == TPG_COLOR_TEXTFG) अणु
		col = tpg_get_textfg_color(tpg);

		r = tpg_colors[col].r;
		g = tpg_colors[col].g;
		b = tpg_colors[col].b;
	पूर्ण अन्यथा अगर (tpg->pattern == TPG_PAT_NOISE) अणु
		r = g = b = pअक्रमom_u32_max(256);
	पूर्ण अन्यथा अगर (k == TPG_COLOR_RANDOM) अणु
		r = g = b = tpg->qual_offset + pअक्रमom_u32_max(196);
	पूर्ण अन्यथा अगर (k >= TPG_COLOR_RAMP) अणु
		r = g = b = k - TPG_COLOR_RAMP;
	पूर्ण

	अगर (tpg->pattern == TPG_PAT_CSC_COLORBAR && col <= TPG_COLOR_CSC_BLACK) अणु
		r = tpg_csc_colors[tpg->colorspace][tpg->real_xfer_func][col].r;
		g = tpg_csc_colors[tpg->colorspace][tpg->real_xfer_func][col].g;
		b = tpg_csc_colors[tpg->colorspace][tpg->real_xfer_func][col].b;
	पूर्ण अन्यथा अणु
		r <<= 4;
		g <<= 4;
		b <<= 4;
	पूर्ण

	अगर (tpg->qual == TPG_QUAL_GRAY ||
	    tpg->color_enc ==  TGP_COLOR_ENC_LUMA) अणु
		/* Rec. 709 Luma function */
		/* (0.2126, 0.7152, 0.0722) * (255 * 256) */
		r = g = b = (13879 * r + 46688 * g + 4713 * b) >> 16;
	पूर्ण

	/*
	 * The assumption is that the RGB output is always full range,
	 * so only अगर the rgb_range overrides the 'real' rgb range करो
	 * we need to convert the RGB values.
	 *
	 * Remember that r, g and b are still in the 0 - 0xff0 range.
	 */
	अगर (tpg->real_rgb_range == V4L2_DV_RGB_RANGE_LIMITED &&
	    tpg->rgb_range == V4L2_DV_RGB_RANGE_FULL &&
	    tpg->color_enc == TGP_COLOR_ENC_RGB) अणु
		/*
		 * Convert from full range (which is what r, g and b are)
		 * to limited range (which is the 'real' RGB range), which
		 * is then पूर्णांकerpreted as full range.
		 */
		r = (r * 219) / 255 + (16 << 4);
		g = (g * 219) / 255 + (16 << 4);
		b = (b * 219) / 255 + (16 << 4);
	पूर्ण अन्यथा अगर (tpg->real_rgb_range != V4L2_DV_RGB_RANGE_LIMITED &&
		   tpg->rgb_range == V4L2_DV_RGB_RANGE_LIMITED &&
		   tpg->color_enc == TGP_COLOR_ENC_RGB) अणु

		/*
		 * Clamp r, g and b to the limited range and convert to full
		 * range since that's what we deliver.
		 */
		r = clamp(r, 16 << 4, 235 << 4);
		g = clamp(g, 16 << 4, 235 << 4);
		b = clamp(b, 16 << 4, 235 << 4);
		r = (r - (16 << 4)) * 255 / 219;
		g = (g - (16 << 4)) * 255 / 219;
		b = (b - (16 << 4)) * 255 / 219;
	पूर्ण

	अगर ((tpg->brightness != 128 || tpg->contrast != 128 ||
	     tpg->saturation != 128 || tpg->hue) &&
	    tpg->color_enc != TGP_COLOR_ENC_LUMA) अणु
		/* Implement these operations */
		पूर्णांक पंचांगp_cb, पंचांगp_cr;

		/* First convert to YCbCr */

		color_to_ycbcr(tpg, r, g, b, &y, &cb, &cr);

		y = (16 << 4) + ((y - (16 << 4)) * tpg->contrast) / 128;
		y += (tpg->brightness << 4) - (128 << 4);

		cb -= 128 << 4;
		cr -= 128 << 4;
		पंचांगp_cb = (cb * cos(128 + tpg->hue)) / 127 + (cr * sin[128 + tpg->hue]) / 127;
		पंचांगp_cr = (cr * cos(128 + tpg->hue)) / 127 - (cb * sin[128 + tpg->hue]) / 127;

		cb = (128 << 4) + (पंचांगp_cb * tpg->contrast * tpg->saturation) / (128 * 128);
		cr = (128 << 4) + (पंचांगp_cr * tpg->contrast * tpg->saturation) / (128 * 128);
		अगर (tpg->color_enc == TGP_COLOR_ENC_YCBCR)
			ycbcr_valid = true;
		अन्यथा
			ycbcr_to_color(tpg, y, cb, cr, &r, &g, &b);
	पूर्ण अन्यथा अगर ((tpg->brightness != 128 || tpg->contrast != 128) &&
		   tpg->color_enc == TGP_COLOR_ENC_LUMA) अणु
		r = (16 << 4) + ((r - (16 << 4)) * tpg->contrast) / 128;
		r += (tpg->brightness << 4) - (128 << 4);
	पूर्ण

	चयन (tpg->color_enc) अणु
	हाल TGP_COLOR_ENC_HSV:
	अणु
		पूर्णांक h, s, v;

		color_to_hsv(tpg, r, g, b, &h, &s, &v);
		tpg->colors[k][0] = h;
		tpg->colors[k][1] = s;
		tpg->colors[k][2] = v;
		अवरोध;
	पूर्ण
	हाल TGP_COLOR_ENC_YCBCR:
	अणु
		/* Convert to YCbCr */
		अगर (!ycbcr_valid)
			color_to_ycbcr(tpg, r, g, b, &y, &cb, &cr);

		y >>= 4;
		cb >>= 4;
		cr >>= 4;
		/*
		 * XV601/709 use the header/footer margins to encode R', G'
		 * and B' values outside the range [0-1]. So करो not clamp
		 * XV601/709 values.
		 */
		अगर (tpg->real_quantization == V4L2_QUANTIZATION_LIM_RANGE &&
		    tpg->real_ycbcr_enc != V4L2_YCBCR_ENC_XV601 &&
		    tpg->real_ycbcr_enc != V4L2_YCBCR_ENC_XV709) अणु
			y = clamp(y, 16, 235);
			cb = clamp(cb, 16, 240);
			cr = clamp(cr, 16, 240);
		पूर्ण अन्यथा अणु
			y = clamp(y, 1, 254);
			cb = clamp(cb, 1, 254);
			cr = clamp(cr, 1, 254);
		पूर्ण
		चयन (tpg->fourcc) अणु
		हाल V4L2_PIX_FMT_YUV444:
			y >>= 4;
			cb >>= 4;
			cr >>= 4;
			अवरोध;
		हाल V4L2_PIX_FMT_YUV555:
			y >>= 3;
			cb >>= 3;
			cr >>= 3;
			अवरोध;
		हाल V4L2_PIX_FMT_YUV565:
			y >>= 3;
			cb >>= 2;
			cr >>= 3;
			अवरोध;
		पूर्ण
		tpg->colors[k][0] = y;
		tpg->colors[k][1] = cb;
		tpg->colors[k][2] = cr;
		अवरोध;
	पूर्ण
	हाल TGP_COLOR_ENC_LUMA:
	अणु
		tpg->colors[k][0] = r >> 4;
		अवरोध;
	पूर्ण
	हाल TGP_COLOR_ENC_RGB:
	अणु
		अगर (tpg->real_quantization == V4L2_QUANTIZATION_LIM_RANGE) अणु
			r = (r * 219) / 255 + (16 << 4);
			g = (g * 219) / 255 + (16 << 4);
			b = (b * 219) / 255 + (16 << 4);
		पूर्ण
		चयन (tpg->fourcc) अणु
		हाल V4L2_PIX_FMT_RGB332:
			r >>= 9;
			g >>= 9;
			b >>= 10;
			अवरोध;
		हाल V4L2_PIX_FMT_RGB565:
		हाल V4L2_PIX_FMT_RGB565X:
			r >>= 7;
			g >>= 6;
			b >>= 7;
			अवरोध;
		हाल V4L2_PIX_FMT_RGB444:
		हाल V4L2_PIX_FMT_XRGB444:
		हाल V4L2_PIX_FMT_ARGB444:
		हाल V4L2_PIX_FMT_RGBX444:
		हाल V4L2_PIX_FMT_RGBA444:
		हाल V4L2_PIX_FMT_XBGR444:
		हाल V4L2_PIX_FMT_ABGR444:
		हाल V4L2_PIX_FMT_BGRX444:
		हाल V4L2_PIX_FMT_BGRA444:
			r >>= 8;
			g >>= 8;
			b >>= 8;
			अवरोध;
		हाल V4L2_PIX_FMT_RGB555:
		हाल V4L2_PIX_FMT_XRGB555:
		हाल V4L2_PIX_FMT_ARGB555:
		हाल V4L2_PIX_FMT_RGBX555:
		हाल V4L2_PIX_FMT_RGBA555:
		हाल V4L2_PIX_FMT_XBGR555:
		हाल V4L2_PIX_FMT_ABGR555:
		हाल V4L2_PIX_FMT_BGRX555:
		हाल V4L2_PIX_FMT_BGRA555:
		हाल V4L2_PIX_FMT_RGB555X:
		हाल V4L2_PIX_FMT_XRGB555X:
		हाल V4L2_PIX_FMT_ARGB555X:
			r >>= 7;
			g >>= 7;
			b >>= 7;
			अवरोध;
		हाल V4L2_PIX_FMT_BGR666:
			r >>= 6;
			g >>= 6;
			b >>= 6;
			अवरोध;
		शेष:
			r >>= 4;
			g >>= 4;
			b >>= 4;
			अवरोध;
		पूर्ण

		tpg->colors[k][0] = r;
		tpg->colors[k][1] = g;
		tpg->colors[k][2] = b;
		अवरोध;
	पूर्ण
	पूर्ण
पूर्ण

अटल व्योम tpg_precalculate_colors(काष्ठा tpg_data *tpg)
अणु
	पूर्णांक k;

	क्रम (k = 0; k < TPG_COLOR_MAX; k++)
		precalculate_color(tpg, k);
पूर्ण

/* 'odd' is true क्रम pixels 1, 3, 5, etc. and false क्रम pixels 0, 2, 4, etc. */
अटल व्योम gen_twopix(काष्ठा tpg_data *tpg,
		u8 buf[TPG_MAX_PLANES][8], पूर्णांक color, bool odd)
अणु
	अचिन्हित offset = odd * tpg->twopixelsize[0] / 2;
	u8 alpha = tpg->alpha_component;
	u8 r_y_h, g_u_s, b_v;

	अगर (tpg->alpha_red_only && color != TPG_COLOR_CSC_RED &&
				   color != TPG_COLOR_100_RED &&
				   color != TPG_COLOR_75_RED)
		alpha = 0;
	अगर (color == TPG_COLOR_RANDOM)
		precalculate_color(tpg, color);
	r_y_h = tpg->colors[color][0]; /* R or precalculated Y, H */
	g_u_s = tpg->colors[color][1]; /* G or precalculated U, V */
	b_v = tpg->colors[color][2]; /* B or precalculated V */

	चयन (tpg->fourcc) अणु
	हाल V4L2_PIX_FMT_GREY:
		buf[0][offset] = r_y_h;
		अवरोध;
	हाल V4L2_PIX_FMT_Y10:
		buf[0][offset] = (r_y_h << 2) & 0xff;
		buf[0][offset+1] = r_y_h >> 6;
		अवरोध;
	हाल V4L2_PIX_FMT_Y12:
		buf[0][offset] = (r_y_h << 4) & 0xff;
		buf[0][offset+1] = r_y_h >> 4;
		अवरोध;
	हाल V4L2_PIX_FMT_Y16:
	हाल V4L2_PIX_FMT_Z16:
		/*
		 * Ideally both bytes should be set to r_y_h, but then you won't
		 * be able to detect endian problems. So keep it 0 except क्रम
		 * the corner हाल where r_y_h is 0xff so white really will be
		 * white (0xffff).
		 */
		buf[0][offset] = r_y_h == 0xff ? r_y_h : 0;
		buf[0][offset+1] = r_y_h;
		अवरोध;
	हाल V4L2_PIX_FMT_Y16_BE:
		/* See comment क्रम V4L2_PIX_FMT_Y16 above */
		buf[0][offset] = r_y_h;
		buf[0][offset+1] = r_y_h == 0xff ? r_y_h : 0;
		अवरोध;
	हाल V4L2_PIX_FMT_YUV422M:
	हाल V4L2_PIX_FMT_YUV422P:
	हाल V4L2_PIX_FMT_YUV420:
	हाल V4L2_PIX_FMT_YUV420M:
		buf[0][offset] = r_y_h;
		अगर (odd) अणु
			buf[1][0] = (buf[1][0] + g_u_s) / 2;
			buf[2][0] = (buf[2][0] + b_v) / 2;
			buf[1][1] = buf[1][0];
			buf[2][1] = buf[2][0];
			अवरोध;
		पूर्ण
		buf[1][0] = g_u_s;
		buf[2][0] = b_v;
		अवरोध;
	हाल V4L2_PIX_FMT_YVU422M:
	हाल V4L2_PIX_FMT_YVU420:
	हाल V4L2_PIX_FMT_YVU420M:
		buf[0][offset] = r_y_h;
		अगर (odd) अणु
			buf[1][0] = (buf[1][0] + b_v) / 2;
			buf[2][0] = (buf[2][0] + g_u_s) / 2;
			buf[1][1] = buf[1][0];
			buf[2][1] = buf[2][0];
			अवरोध;
		पूर्ण
		buf[1][0] = b_v;
		buf[2][0] = g_u_s;
		अवरोध;

	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV12M:
	हाल V4L2_PIX_FMT_NV16:
	हाल V4L2_PIX_FMT_NV16M:
		buf[0][offset] = r_y_h;
		अगर (odd) अणु
			buf[1][0] = (buf[1][0] + g_u_s) / 2;
			buf[1][1] = (buf[1][1] + b_v) / 2;
			अवरोध;
		पूर्ण
		buf[1][0] = g_u_s;
		buf[1][1] = b_v;
		अवरोध;
	हाल V4L2_PIX_FMT_NV21:
	हाल V4L2_PIX_FMT_NV21M:
	हाल V4L2_PIX_FMT_NV61:
	हाल V4L2_PIX_FMT_NV61M:
		buf[0][offset] = r_y_h;
		अगर (odd) अणु
			buf[1][0] = (buf[1][0] + b_v) / 2;
			buf[1][1] = (buf[1][1] + g_u_s) / 2;
			अवरोध;
		पूर्ण
		buf[1][0] = b_v;
		buf[1][1] = g_u_s;
		अवरोध;

	हाल V4L2_PIX_FMT_YUV444M:
		buf[0][offset] = r_y_h;
		buf[1][offset] = g_u_s;
		buf[2][offset] = b_v;
		अवरोध;

	हाल V4L2_PIX_FMT_YVU444M:
		buf[0][offset] = r_y_h;
		buf[1][offset] = b_v;
		buf[2][offset] = g_u_s;
		अवरोध;

	हाल V4L2_PIX_FMT_NV24:
		buf[0][offset] = r_y_h;
		buf[1][2 * offset] = g_u_s;
		buf[1][(2 * offset + 1) % 8] = b_v;
		अवरोध;

	हाल V4L2_PIX_FMT_NV42:
		buf[0][offset] = r_y_h;
		buf[1][2 * offset] = b_v;
		buf[1][(2 * offset + 1) % 8] = g_u_s;
		अवरोध;

	हाल V4L2_PIX_FMT_YUYV:
		buf[0][offset] = r_y_h;
		अगर (odd) अणु
			buf[0][1] = (buf[0][1] + g_u_s) / 2;
			buf[0][3] = (buf[0][3] + b_v) / 2;
			अवरोध;
		पूर्ण
		buf[0][1] = g_u_s;
		buf[0][3] = b_v;
		अवरोध;
	हाल V4L2_PIX_FMT_UYVY:
		buf[0][offset + 1] = r_y_h;
		अगर (odd) अणु
			buf[0][0] = (buf[0][0] + g_u_s) / 2;
			buf[0][2] = (buf[0][2] + b_v) / 2;
			अवरोध;
		पूर्ण
		buf[0][0] = g_u_s;
		buf[0][2] = b_v;
		अवरोध;
	हाल V4L2_PIX_FMT_YVYU:
		buf[0][offset] = r_y_h;
		अगर (odd) अणु
			buf[0][1] = (buf[0][1] + b_v) / 2;
			buf[0][3] = (buf[0][3] + g_u_s) / 2;
			अवरोध;
		पूर्ण
		buf[0][1] = b_v;
		buf[0][3] = g_u_s;
		अवरोध;
	हाल V4L2_PIX_FMT_VYUY:
		buf[0][offset + 1] = r_y_h;
		अगर (odd) अणु
			buf[0][0] = (buf[0][0] + b_v) / 2;
			buf[0][2] = (buf[0][2] + g_u_s) / 2;
			अवरोध;
		पूर्ण
		buf[0][0] = b_v;
		buf[0][2] = g_u_s;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB332:
		buf[0][offset] = (r_y_h << 5) | (g_u_s << 2) | b_v;
		अवरोध;
	हाल V4L2_PIX_FMT_YUV565:
	हाल V4L2_PIX_FMT_RGB565:
		buf[0][offset] = (g_u_s << 5) | b_v;
		buf[0][offset + 1] = (r_y_h << 3) | (g_u_s >> 3);
		अवरोध;
	हाल V4L2_PIX_FMT_RGB565X:
		buf[0][offset] = (r_y_h << 3) | (g_u_s >> 3);
		buf[0][offset + 1] = (g_u_s << 5) | b_v;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB444:
	हाल V4L2_PIX_FMT_XRGB444:
		alpha = 0;
		fallthrough;
	हाल V4L2_PIX_FMT_YUV444:
	हाल V4L2_PIX_FMT_ARGB444:
		buf[0][offset] = (g_u_s << 4) | b_v;
		buf[0][offset + 1] = (alpha & 0xf0) | r_y_h;
		अवरोध;
	हाल V4L2_PIX_FMT_RGBX444:
		alpha = 0;
		fallthrough;
	हाल V4L2_PIX_FMT_RGBA444:
		buf[0][offset] = (b_v << 4) | (alpha >> 4);
		buf[0][offset + 1] = (r_y_h << 4) | g_u_s;
		अवरोध;
	हाल V4L2_PIX_FMT_XBGR444:
		alpha = 0;
		fallthrough;
	हाल V4L2_PIX_FMT_ABGR444:
		buf[0][offset] = (g_u_s << 4) | r_y_h;
		buf[0][offset + 1] = (alpha & 0xf0) | b_v;
		अवरोध;
	हाल V4L2_PIX_FMT_BGRX444:
		alpha = 0;
		fallthrough;
	हाल V4L2_PIX_FMT_BGRA444:
		buf[0][offset] = (r_y_h << 4) | (alpha >> 4);
		buf[0][offset + 1] = (b_v << 4) | g_u_s;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB555:
	हाल V4L2_PIX_FMT_XRGB555:
		alpha = 0;
		fallthrough;
	हाल V4L2_PIX_FMT_YUV555:
	हाल V4L2_PIX_FMT_ARGB555:
		buf[0][offset] = (g_u_s << 5) | b_v;
		buf[0][offset + 1] = (alpha & 0x80) | (r_y_h << 2)
						    | (g_u_s >> 3);
		अवरोध;
	हाल V4L2_PIX_FMT_RGBX555:
		alpha = 0;
		fallthrough;
	हाल V4L2_PIX_FMT_RGBA555:
		buf[0][offset] = (g_u_s << 6) | (b_v << 1) |
				 ((alpha & 0x80) >> 7);
		buf[0][offset + 1] = (r_y_h << 3) | (g_u_s >> 2);
		अवरोध;
	हाल V4L2_PIX_FMT_XBGR555:
		alpha = 0;
		fallthrough;
	हाल V4L2_PIX_FMT_ABGR555:
		buf[0][offset] = (g_u_s << 5) | r_y_h;
		buf[0][offset + 1] = (alpha & 0x80) | (b_v << 2)
						    | (g_u_s >> 3);
		अवरोध;
	हाल V4L2_PIX_FMT_BGRX555:
		alpha = 0;
		fallthrough;
	हाल V4L2_PIX_FMT_BGRA555:
		buf[0][offset] = (g_u_s << 6) | (r_y_h << 1) |
				 ((alpha & 0x80) >> 7);
		buf[0][offset + 1] = (b_v << 3) | (g_u_s >> 2);
		अवरोध;
	हाल V4L2_PIX_FMT_RGB555X:
	हाल V4L2_PIX_FMT_XRGB555X:
		alpha = 0;
		fallthrough;
	हाल V4L2_PIX_FMT_ARGB555X:
		buf[0][offset] = (alpha & 0x80) | (r_y_h << 2) | (g_u_s >> 3);
		buf[0][offset + 1] = (g_u_s << 5) | b_v;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB24:
	हाल V4L2_PIX_FMT_HSV24:
		buf[0][offset] = r_y_h;
		buf[0][offset + 1] = g_u_s;
		buf[0][offset + 2] = b_v;
		अवरोध;
	हाल V4L2_PIX_FMT_BGR24:
		buf[0][offset] = b_v;
		buf[0][offset + 1] = g_u_s;
		buf[0][offset + 2] = r_y_h;
		अवरोध;
	हाल V4L2_PIX_FMT_BGR666:
		buf[0][offset] = (b_v << 2) | (g_u_s >> 4);
		buf[0][offset + 1] = (g_u_s << 4) | (r_y_h >> 2);
		buf[0][offset + 2] = r_y_h << 6;
		buf[0][offset + 3] = 0;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB32:
	हाल V4L2_PIX_FMT_XRGB32:
	हाल V4L2_PIX_FMT_HSV32:
	हाल V4L2_PIX_FMT_XYUV32:
		alpha = 0;
		fallthrough;
	हाल V4L2_PIX_FMT_YUV32:
	हाल V4L2_PIX_FMT_ARGB32:
	हाल V4L2_PIX_FMT_AYUV32:
		buf[0][offset] = alpha;
		buf[0][offset + 1] = r_y_h;
		buf[0][offset + 2] = g_u_s;
		buf[0][offset + 3] = b_v;
		अवरोध;
	हाल V4L2_PIX_FMT_RGBX32:
		alpha = 0;
		fallthrough;
	हाल V4L2_PIX_FMT_RGBA32:
		buf[0][offset] = r_y_h;
		buf[0][offset + 1] = g_u_s;
		buf[0][offset + 2] = b_v;
		buf[0][offset + 3] = alpha;
		अवरोध;
	हाल V4L2_PIX_FMT_BGR32:
	हाल V4L2_PIX_FMT_XBGR32:
	हाल V4L2_PIX_FMT_VUYX32:
		alpha = 0;
		fallthrough;
	हाल V4L2_PIX_FMT_ABGR32:
	हाल V4L2_PIX_FMT_VUYA32:
		buf[0][offset] = b_v;
		buf[0][offset + 1] = g_u_s;
		buf[0][offset + 2] = r_y_h;
		buf[0][offset + 3] = alpha;
		अवरोध;
	हाल V4L2_PIX_FMT_BGRX32:
		alpha = 0;
		fallthrough;
	हाल V4L2_PIX_FMT_BGRA32:
		buf[0][offset] = alpha;
		buf[0][offset + 1] = b_v;
		buf[0][offset + 2] = g_u_s;
		buf[0][offset + 3] = r_y_h;
		अवरोध;
	हाल V4L2_PIX_FMT_SBGGR8:
		buf[0][offset] = odd ? g_u_s : b_v;
		buf[1][offset] = odd ? r_y_h : g_u_s;
		अवरोध;
	हाल V4L2_PIX_FMT_SGBRG8:
		buf[0][offset] = odd ? b_v : g_u_s;
		buf[1][offset] = odd ? g_u_s : r_y_h;
		अवरोध;
	हाल V4L2_PIX_FMT_SGRBG8:
		buf[0][offset] = odd ? r_y_h : g_u_s;
		buf[1][offset] = odd ? g_u_s : b_v;
		अवरोध;
	हाल V4L2_PIX_FMT_SRGGB8:
		buf[0][offset] = odd ? g_u_s : r_y_h;
		buf[1][offset] = odd ? b_v : g_u_s;
		अवरोध;
	हाल V4L2_PIX_FMT_SBGGR10:
		buf[0][offset] = odd ? g_u_s << 2 : b_v << 2;
		buf[0][offset + 1] = odd ? g_u_s >> 6 : b_v >> 6;
		buf[1][offset] = odd ? r_y_h << 2 : g_u_s << 2;
		buf[1][offset + 1] = odd ? r_y_h >> 6 : g_u_s >> 6;
		buf[0][offset] |= (buf[0][offset] >> 2) & 3;
		buf[1][offset] |= (buf[1][offset] >> 2) & 3;
		अवरोध;
	हाल V4L2_PIX_FMT_SGBRG10:
		buf[0][offset] = odd ? b_v << 2 : g_u_s << 2;
		buf[0][offset + 1] = odd ? b_v >> 6 : g_u_s >> 6;
		buf[1][offset] = odd ? g_u_s << 2 : r_y_h << 2;
		buf[1][offset + 1] = odd ? g_u_s >> 6 : r_y_h >> 6;
		buf[0][offset] |= (buf[0][offset] >> 2) & 3;
		buf[1][offset] |= (buf[1][offset] >> 2) & 3;
		अवरोध;
	हाल V4L2_PIX_FMT_SGRBG10:
		buf[0][offset] = odd ? r_y_h << 2 : g_u_s << 2;
		buf[0][offset + 1] = odd ? r_y_h >> 6 : g_u_s >> 6;
		buf[1][offset] = odd ? g_u_s << 2 : b_v << 2;
		buf[1][offset + 1] = odd ? g_u_s >> 6 : b_v >> 6;
		buf[0][offset] |= (buf[0][offset] >> 2) & 3;
		buf[1][offset] |= (buf[1][offset] >> 2) & 3;
		अवरोध;
	हाल V4L2_PIX_FMT_SRGGB10:
		buf[0][offset] = odd ? g_u_s << 2 : r_y_h << 2;
		buf[0][offset + 1] = odd ? g_u_s >> 6 : r_y_h >> 6;
		buf[1][offset] = odd ? b_v << 2 : g_u_s << 2;
		buf[1][offset + 1] = odd ? b_v >> 6 : g_u_s >> 6;
		buf[0][offset] |= (buf[0][offset] >> 2) & 3;
		buf[1][offset] |= (buf[1][offset] >> 2) & 3;
		अवरोध;
	हाल V4L2_PIX_FMT_SBGGR12:
		buf[0][offset] = odd ? g_u_s << 4 : b_v << 4;
		buf[0][offset + 1] = odd ? g_u_s >> 4 : b_v >> 4;
		buf[1][offset] = odd ? r_y_h << 4 : g_u_s << 4;
		buf[1][offset + 1] = odd ? r_y_h >> 4 : g_u_s >> 4;
		buf[0][offset] |= (buf[0][offset] >> 4) & 0xf;
		buf[1][offset] |= (buf[1][offset] >> 4) & 0xf;
		अवरोध;
	हाल V4L2_PIX_FMT_SGBRG12:
		buf[0][offset] = odd ? b_v << 4 : g_u_s << 4;
		buf[0][offset + 1] = odd ? b_v >> 4 : g_u_s >> 4;
		buf[1][offset] = odd ? g_u_s << 4 : r_y_h << 4;
		buf[1][offset + 1] = odd ? g_u_s >> 4 : r_y_h >> 4;
		buf[0][offset] |= (buf[0][offset] >> 4) & 0xf;
		buf[1][offset] |= (buf[1][offset] >> 4) & 0xf;
		अवरोध;
	हाल V4L2_PIX_FMT_SGRBG12:
		buf[0][offset] = odd ? r_y_h << 4 : g_u_s << 4;
		buf[0][offset + 1] = odd ? r_y_h >> 4 : g_u_s >> 4;
		buf[1][offset] = odd ? g_u_s << 4 : b_v << 4;
		buf[1][offset + 1] = odd ? g_u_s >> 4 : b_v >> 4;
		buf[0][offset] |= (buf[0][offset] >> 4) & 0xf;
		buf[1][offset] |= (buf[1][offset] >> 4) & 0xf;
		अवरोध;
	हाल V4L2_PIX_FMT_SRGGB12:
		buf[0][offset] = odd ? g_u_s << 4 : r_y_h << 4;
		buf[0][offset + 1] = odd ? g_u_s >> 4 : r_y_h >> 4;
		buf[1][offset] = odd ? b_v << 4 : g_u_s << 4;
		buf[1][offset + 1] = odd ? b_v >> 4 : g_u_s >> 4;
		buf[0][offset] |= (buf[0][offset] >> 4) & 0xf;
		buf[1][offset] |= (buf[1][offset] >> 4) & 0xf;
		अवरोध;
	हाल V4L2_PIX_FMT_SBGGR16:
		buf[0][offset] = buf[0][offset + 1] = odd ? g_u_s : b_v;
		buf[1][offset] = buf[1][offset + 1] = odd ? r_y_h : g_u_s;
		अवरोध;
	हाल V4L2_PIX_FMT_SGBRG16:
		buf[0][offset] = buf[0][offset + 1] = odd ? b_v : g_u_s;
		buf[1][offset] = buf[1][offset + 1] = odd ? g_u_s : r_y_h;
		अवरोध;
	हाल V4L2_PIX_FMT_SGRBG16:
		buf[0][offset] = buf[0][offset + 1] = odd ? r_y_h : g_u_s;
		buf[1][offset] = buf[1][offset + 1] = odd ? g_u_s : b_v;
		अवरोध;
	हाल V4L2_PIX_FMT_SRGGB16:
		buf[0][offset] = buf[0][offset + 1] = odd ? g_u_s : r_y_h;
		buf[1][offset] = buf[1][offset + 1] = odd ? b_v : g_u_s;
		अवरोध;
	पूर्ण
पूर्ण

अचिन्हित tpg_g_पूर्णांकerleaved_plane(स्थिर काष्ठा tpg_data *tpg, अचिन्हित buf_line)
अणु
	चयन (tpg->fourcc) अणु
	हाल V4L2_PIX_FMT_SBGGR8:
	हाल V4L2_PIX_FMT_SGBRG8:
	हाल V4L2_PIX_FMT_SGRBG8:
	हाल V4L2_PIX_FMT_SRGGB8:
	हाल V4L2_PIX_FMT_SBGGR10:
	हाल V4L2_PIX_FMT_SGBRG10:
	हाल V4L2_PIX_FMT_SGRBG10:
	हाल V4L2_PIX_FMT_SRGGB10:
	हाल V4L2_PIX_FMT_SBGGR12:
	हाल V4L2_PIX_FMT_SGBRG12:
	हाल V4L2_PIX_FMT_SGRBG12:
	हाल V4L2_PIX_FMT_SRGGB12:
	हाल V4L2_PIX_FMT_SBGGR16:
	हाल V4L2_PIX_FMT_SGBRG16:
	हाल V4L2_PIX_FMT_SGRBG16:
	हाल V4L2_PIX_FMT_SRGGB16:
		वापस buf_line & 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(tpg_g_पूर्णांकerleaved_plane);

/* Return how many pattern lines are used by the current pattern. */
अटल अचिन्हित tpg_get_pat_lines(स्थिर काष्ठा tpg_data *tpg)
अणु
	चयन (tpg->pattern) अणु
	हाल TPG_PAT_CHECKERS_16X16:
	हाल TPG_PAT_CHECKERS_2X2:
	हाल TPG_PAT_CHECKERS_1X1:
	हाल TPG_PAT_COLOR_CHECKERS_2X2:
	हाल TPG_PAT_COLOR_CHECKERS_1X1:
	हाल TPG_PAT_ALTERNATING_HLINES:
	हाल TPG_PAT_CROSS_1_PIXEL:
	हाल TPG_PAT_CROSS_2_PIXELS:
	हाल TPG_PAT_CROSS_10_PIXELS:
		वापस 2;
	हाल TPG_PAT_100_COLORSQUARES:
	हाल TPG_PAT_100_HCOLORBAR:
		वापस 8;
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

/* Which pattern line should be used क्रम the given frame line. */
अटल अचिन्हित tpg_get_pat_line(स्थिर काष्ठा tpg_data *tpg, अचिन्हित line)
अणु
	चयन (tpg->pattern) अणु
	हाल TPG_PAT_CHECKERS_16X16:
		वापस (line >> 4) & 1;
	हाल TPG_PAT_CHECKERS_1X1:
	हाल TPG_PAT_COLOR_CHECKERS_1X1:
	हाल TPG_PAT_ALTERNATING_HLINES:
		वापस line & 1;
	हाल TPG_PAT_CHECKERS_2X2:
	हाल TPG_PAT_COLOR_CHECKERS_2X2:
		वापस (line & 2) >> 1;
	हाल TPG_PAT_100_COLORSQUARES:
	हाल TPG_PAT_100_HCOLORBAR:
		वापस (line * 8) / tpg->src_height;
	हाल TPG_PAT_CROSS_1_PIXEL:
		वापस line == tpg->src_height / 2;
	हाल TPG_PAT_CROSS_2_PIXELS:
		वापस (line + 1) / 2 == tpg->src_height / 4;
	हाल TPG_PAT_CROSS_10_PIXELS:
		वापस (line + 10) / 20 == tpg->src_height / 40;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/*
 * Which color should be used क्रम the given pattern line and X coordinate.
 * Note: x is in the range 0 to 2 * tpg->src_width.
 */
अटल क्रमागत tpg_color tpg_get_color(स्थिर काष्ठा tpg_data *tpg,
				    अचिन्हित pat_line, अचिन्हित x)
अणु
	/* Maximum number of bars are TPG_COLOR_MAX - otherwise, the input prपूर्णांक code
	   should be modअगरied */
	अटल स्थिर क्रमागत tpg_color bars[3][8] = अणु
		/* Standard ITU-R 75% color bar sequence */
		अणु TPG_COLOR_CSC_WHITE,   TPG_COLOR_75_YELLOW,
		  TPG_COLOR_75_CYAN,     TPG_COLOR_75_GREEN,
		  TPG_COLOR_75_MAGENTA,  TPG_COLOR_75_RED,
		  TPG_COLOR_75_BLUE,     TPG_COLOR_100_BLACK, पूर्ण,
		/* Standard ITU-R 100% color bar sequence */
		अणु TPG_COLOR_100_WHITE,   TPG_COLOR_100_YELLOW,
		  TPG_COLOR_100_CYAN,    TPG_COLOR_100_GREEN,
		  TPG_COLOR_100_MAGENTA, TPG_COLOR_100_RED,
		  TPG_COLOR_100_BLUE,    TPG_COLOR_100_BLACK, पूर्ण,
		/* Color bar sequence suitable to test CSC */
		अणु TPG_COLOR_CSC_WHITE,   TPG_COLOR_CSC_YELLOW,
		  TPG_COLOR_CSC_CYAN,    TPG_COLOR_CSC_GREEN,
		  TPG_COLOR_CSC_MAGENTA, TPG_COLOR_CSC_RED,
		  TPG_COLOR_CSC_BLUE,    TPG_COLOR_CSC_BLACK, पूर्ण,
	पूर्ण;

	चयन (tpg->pattern) अणु
	हाल TPG_PAT_75_COLORBAR:
	हाल TPG_PAT_100_COLORBAR:
	हाल TPG_PAT_CSC_COLORBAR:
		वापस bars[tpg->pattern][((x * 8) / tpg->src_width) % 8];
	हाल TPG_PAT_100_COLORSQUARES:
		वापस bars[1][(pat_line + (x * 8) / tpg->src_width) % 8];
	हाल TPG_PAT_100_HCOLORBAR:
		वापस bars[1][pat_line];
	हाल TPG_PAT_BLACK:
		वापस TPG_COLOR_100_BLACK;
	हाल TPG_PAT_WHITE:
		वापस TPG_COLOR_100_WHITE;
	हाल TPG_PAT_RED:
		वापस TPG_COLOR_100_RED;
	हाल TPG_PAT_GREEN:
		वापस TPG_COLOR_100_GREEN;
	हाल TPG_PAT_BLUE:
		वापस TPG_COLOR_100_BLUE;
	हाल TPG_PAT_CHECKERS_16X16:
		वापस (((x >> 4) & 1) ^ (pat_line & 1)) ?
			TPG_COLOR_100_BLACK : TPG_COLOR_100_WHITE;
	हाल TPG_PAT_CHECKERS_1X1:
		वापस ((x & 1) ^ (pat_line & 1)) ?
			TPG_COLOR_100_WHITE : TPG_COLOR_100_BLACK;
	हाल TPG_PAT_COLOR_CHECKERS_1X1:
		वापस ((x & 1) ^ (pat_line & 1)) ?
			TPG_COLOR_100_RED : TPG_COLOR_100_BLUE;
	हाल TPG_PAT_CHECKERS_2X2:
		वापस (((x >> 1) & 1) ^ (pat_line & 1)) ?
			TPG_COLOR_100_WHITE : TPG_COLOR_100_BLACK;
	हाल TPG_PAT_COLOR_CHECKERS_2X2:
		वापस (((x >> 1) & 1) ^ (pat_line & 1)) ?
			TPG_COLOR_100_RED : TPG_COLOR_100_BLUE;
	हाल TPG_PAT_ALTERNATING_HLINES:
		वापस pat_line ? TPG_COLOR_100_WHITE : TPG_COLOR_100_BLACK;
	हाल TPG_PAT_ALTERNATING_VLINES:
		वापस (x & 1) ? TPG_COLOR_100_WHITE : TPG_COLOR_100_BLACK;
	हाल TPG_PAT_CROSS_1_PIXEL:
		अगर (pat_line || (x % tpg->src_width) == tpg->src_width / 2)
			वापस TPG_COLOR_100_BLACK;
		वापस TPG_COLOR_100_WHITE;
	हाल TPG_PAT_CROSS_2_PIXELS:
		अगर (pat_line || ((x % tpg->src_width) + 1) / 2 == tpg->src_width / 4)
			वापस TPG_COLOR_100_BLACK;
		वापस TPG_COLOR_100_WHITE;
	हाल TPG_PAT_CROSS_10_PIXELS:
		अगर (pat_line || ((x % tpg->src_width) + 10) / 20 == tpg->src_width / 40)
			वापस TPG_COLOR_100_BLACK;
		वापस TPG_COLOR_100_WHITE;
	हाल TPG_PAT_GRAY_RAMP:
		वापस TPG_COLOR_RAMP + ((x % tpg->src_width) * 256) / tpg->src_width;
	शेष:
		वापस TPG_COLOR_100_RED;
	पूर्ण
पूर्ण

/*
 * Given the pixel aspect ratio and video aspect ratio calculate the
 * coordinates of a centered square and the coordinates of the border of
 * the active video area. The coordinates are relative to the source
 * frame rectangle.
 */
अटल व्योम tpg_calculate_square_border(काष्ठा tpg_data *tpg)
अणु
	अचिन्हित w = tpg->src_width;
	अचिन्हित h = tpg->src_height;
	अचिन्हित sq_w, sq_h;

	sq_w = (w * 2 / 5) & ~1;
	अगर (((w - sq_w) / 2) & 1)
		sq_w += 2;
	sq_h = sq_w;
	tpg->square.width = sq_w;
	अगर (tpg->vid_aspect == TPG_VIDEO_ASPECT_16X9_ANAMORPHIC) अणु
		अचिन्हित ana_sq_w = (sq_w / 4) * 3;

		अगर (((w - ana_sq_w) / 2) & 1)
			ana_sq_w += 2;
		tpg->square.width = ana_sq_w;
	पूर्ण
	tpg->square.left = (w - tpg->square.width) / 2;
	अगर (tpg->pix_aspect == TPG_PIXEL_ASPECT_NTSC)
		sq_h = sq_w * 10 / 11;
	अन्यथा अगर (tpg->pix_aspect == TPG_PIXEL_ASPECT_PAL)
		sq_h = sq_w * 59 / 54;
	tpg->square.height = sq_h;
	tpg->square.top = (h - sq_h) / 2;
	tpg->border.left = 0;
	tpg->border.width = w;
	tpg->border.top = 0;
	tpg->border.height = h;
	चयन (tpg->vid_aspect) अणु
	हाल TPG_VIDEO_ASPECT_4X3:
		अगर (tpg->pix_aspect)
			वापस;
		अगर (3 * w >= 4 * h) अणु
			tpg->border.width = ((4 * h) / 3) & ~1;
			अगर (((w - tpg->border.width) / 2) & ~1)
				tpg->border.width -= 2;
			tpg->border.left = (w - tpg->border.width) / 2;
			अवरोध;
		पूर्ण
		tpg->border.height = ((3 * w) / 4) & ~1;
		tpg->border.top = (h - tpg->border.height) / 2;
		अवरोध;
	हाल TPG_VIDEO_ASPECT_14X9_CENTRE:
		अगर (tpg->pix_aspect) अणु
			tpg->border.height = tpg->pix_aspect == TPG_PIXEL_ASPECT_NTSC ? 420 : 506;
			tpg->border.top = (h - tpg->border.height) / 2;
			अवरोध;
		पूर्ण
		अगर (9 * w >= 14 * h) अणु
			tpg->border.width = ((14 * h) / 9) & ~1;
			अगर (((w - tpg->border.width) / 2) & ~1)
				tpg->border.width -= 2;
			tpg->border.left = (w - tpg->border.width) / 2;
			अवरोध;
		पूर्ण
		tpg->border.height = ((9 * w) / 14) & ~1;
		tpg->border.top = (h - tpg->border.height) / 2;
		अवरोध;
	हाल TPG_VIDEO_ASPECT_16X9_CENTRE:
		अगर (tpg->pix_aspect) अणु
			tpg->border.height = tpg->pix_aspect == TPG_PIXEL_ASPECT_NTSC ? 368 : 442;
			tpg->border.top = (h - tpg->border.height) / 2;
			अवरोध;
		पूर्ण
		अगर (9 * w >= 16 * h) अणु
			tpg->border.width = ((16 * h) / 9) & ~1;
			अगर (((w - tpg->border.width) / 2) & ~1)
				tpg->border.width -= 2;
			tpg->border.left = (w - tpg->border.width) / 2;
			अवरोध;
		पूर्ण
		tpg->border.height = ((9 * w) / 16) & ~1;
		tpg->border.top = (h - tpg->border.height) / 2;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम tpg_precalculate_line(काष्ठा tpg_data *tpg)
अणु
	क्रमागत tpg_color contrast;
	u8 pix[TPG_MAX_PLANES][8];
	अचिन्हित pat;
	अचिन्हित p;
	अचिन्हित x;

	चयन (tpg->pattern) अणु
	हाल TPG_PAT_GREEN:
		contrast = TPG_COLOR_100_RED;
		अवरोध;
	हाल TPG_PAT_CSC_COLORBAR:
		contrast = TPG_COLOR_CSC_GREEN;
		अवरोध;
	शेष:
		contrast = TPG_COLOR_100_GREEN;
		अवरोध;
	पूर्ण

	क्रम (pat = 0; pat < tpg_get_pat_lines(tpg); pat++) अणु
		/* Coarse scaling with Bresenham */
		अचिन्हित पूर्णांक_part = tpg->src_width / tpg->scaled_width;
		अचिन्हित fract_part = tpg->src_width % tpg->scaled_width;
		अचिन्हित src_x = 0;
		अचिन्हित error = 0;

		क्रम (x = 0; x < tpg->scaled_width * 2; x += 2) अणु
			अचिन्हित real_x = src_x;
			क्रमागत tpg_color color1, color2;

			real_x = tpg->hflip ? tpg->src_width * 2 - real_x - 2 : real_x;
			color1 = tpg_get_color(tpg, pat, real_x);

			src_x += पूर्णांक_part;
			error += fract_part;
			अगर (error >= tpg->scaled_width) अणु
				error -= tpg->scaled_width;
				src_x++;
			पूर्ण

			real_x = src_x;
			real_x = tpg->hflip ? tpg->src_width * 2 - real_x - 2 : real_x;
			color2 = tpg_get_color(tpg, pat, real_x);

			src_x += पूर्णांक_part;
			error += fract_part;
			अगर (error >= tpg->scaled_width) अणु
				error -= tpg->scaled_width;
				src_x++;
			पूर्ण

			gen_twopix(tpg, pix, tpg->hflip ? color2 : color1, 0);
			gen_twopix(tpg, pix, tpg->hflip ? color1 : color2, 1);
			क्रम (p = 0; p < tpg->planes; p++) अणु
				अचिन्हित twopixsize = tpg->twopixelsize[p];
				अचिन्हित hभाग = tpg->hकरोwnsampling[p];
				u8 *pos = tpg->lines[pat][p] + tpg_hभाग(tpg, p, x);

				स_नकल(pos, pix[p], twopixsize / hभाग);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (tpg->vकरोwnsampling[tpg->planes - 1] > 1) अणु
		अचिन्हित pat_lines = tpg_get_pat_lines(tpg);

		क्रम (pat = 0; pat < pat_lines; pat++) अणु
			अचिन्हित next_pat = (pat + 1) % pat_lines;

			क्रम (p = 1; p < tpg->planes; p++) अणु
				अचिन्हित w = tpg_hभाग(tpg, p, tpg->scaled_width * 2);
				u8 *pos1 = tpg->lines[pat][p];
				u8 *pos2 = tpg->lines[next_pat][p];
				u8 *dest = tpg->करोwnsampled_lines[pat][p];

				क्रम (x = 0; x < w; x++, pos1++, pos2++, dest++)
					*dest = ((u16)*pos1 + (u16)*pos2) / 2;
			पूर्ण
		पूर्ण
	पूर्ण

	gen_twopix(tpg, pix, contrast, 0);
	gen_twopix(tpg, pix, contrast, 1);
	क्रम (p = 0; p < tpg->planes; p++) अणु
		अचिन्हित twopixsize = tpg->twopixelsize[p];
		u8 *pos = tpg->contrast_line[p];

		क्रम (x = 0; x < tpg->scaled_width; x += 2, pos += twopixsize)
			स_नकल(pos, pix[p], twopixsize);
	पूर्ण

	gen_twopix(tpg, pix, TPG_COLOR_100_BLACK, 0);
	gen_twopix(tpg, pix, TPG_COLOR_100_BLACK, 1);
	क्रम (p = 0; p < tpg->planes; p++) अणु
		अचिन्हित twopixsize = tpg->twopixelsize[p];
		u8 *pos = tpg->black_line[p];

		क्रम (x = 0; x < tpg->scaled_width; x += 2, pos += twopixsize)
			स_नकल(pos, pix[p], twopixsize);
	पूर्ण

	क्रम (x = 0; x < tpg->scaled_width * 2; x += 2) अणु
		gen_twopix(tpg, pix, TPG_COLOR_RANDOM, 0);
		gen_twopix(tpg, pix, TPG_COLOR_RANDOM, 1);
		क्रम (p = 0; p < tpg->planes; p++) अणु
			अचिन्हित twopixsize = tpg->twopixelsize[p];
			u8 *pos = tpg->अक्रमom_line[p] + x * twopixsize / 2;

			स_नकल(pos, pix[p], twopixsize);
		पूर्ण
	पूर्ण

	gen_twopix(tpg, tpg->textbg, TPG_COLOR_TEXTBG, 0);
	gen_twopix(tpg, tpg->textbg, TPG_COLOR_TEXTBG, 1);
	gen_twopix(tpg, tpg->textfg, TPG_COLOR_TEXTFG, 0);
	gen_twopix(tpg, tpg->textfg, TPG_COLOR_TEXTFG, 1);
पूर्ण

/* need this to करो rgb24 rendering */
प्रकार काष्ठा अणु u16 __; u8 _; पूर्ण __packed x24;

#घोषणा PRINTSTR(PIXTYPE) करो अणु	\
	अचिन्हित vभाग = tpg->vकरोwnsampling[p]; \
	अचिन्हित hभाग = tpg->hकरोwnsampling[p]; \
	पूर्णांक line;	\
	PIXTYPE fg;	\
	PIXTYPE bg;	\
	स_नकल(&fg, tpg->textfg[p], माप(PIXTYPE));	\
	स_नकल(&bg, tpg->textbg[p], माप(PIXTYPE));	\
	\
	क्रम (line = first; line < 16; line += vभाग * step) अणु	\
		पूर्णांक l = tpg->vflip ? 15 - line : line; \
		PIXTYPE *pos = (PIXTYPE *)(basep[p][(line / vभाग) & 1] + \
			       ((y * step + l) / (vभाग * भाग)) * tpg->bytesperline[p] + \
			       (x / hभाग) * माप(PIXTYPE));	\
		अचिन्हित s;	\
	\
		क्रम (s = 0; s < len; s++) अणु	\
			u8 chr = font8x16[(u8)text[s] * 16 + line];	\
	\
			अगर (hभाग == 2 && tpg->hflip) अणु \
				pos[3] = (chr & (0x01 << 6) ? fg : bg);	\
				pos[2] = (chr & (0x01 << 4) ? fg : bg);	\
				pos[1] = (chr & (0x01 << 2) ? fg : bg);	\
				pos[0] = (chr & (0x01 << 0) ? fg : bg);	\
			पूर्ण अन्यथा अगर (hभाग == 2) अणु \
				pos[0] = (chr & (0x01 << 7) ? fg : bg);	\
				pos[1] = (chr & (0x01 << 5) ? fg : bg);	\
				pos[2] = (chr & (0x01 << 3) ? fg : bg);	\
				pos[3] = (chr & (0x01 << 1) ? fg : bg);	\
			पूर्ण अन्यथा अगर (tpg->hflip) अणु \
				pos[7] = (chr & (0x01 << 7) ? fg : bg);	\
				pos[6] = (chr & (0x01 << 6) ? fg : bg);	\
				pos[5] = (chr & (0x01 << 5) ? fg : bg);	\
				pos[4] = (chr & (0x01 << 4) ? fg : bg);	\
				pos[3] = (chr & (0x01 << 3) ? fg : bg);	\
				pos[2] = (chr & (0x01 << 2) ? fg : bg);	\
				pos[1] = (chr & (0x01 << 1) ? fg : bg);	\
				pos[0] = (chr & (0x01 << 0) ? fg : bg);	\
			पूर्ण अन्यथा अणु \
				pos[0] = (chr & (0x01 << 7) ? fg : bg);	\
				pos[1] = (chr & (0x01 << 6) ? fg : bg);	\
				pos[2] = (chr & (0x01 << 5) ? fg : bg);	\
				pos[3] = (chr & (0x01 << 4) ? fg : bg);	\
				pos[4] = (chr & (0x01 << 3) ? fg : bg);	\
				pos[5] = (chr & (0x01 << 2) ? fg : bg);	\
				pos[6] = (chr & (0x01 << 1) ? fg : bg);	\
				pos[7] = (chr & (0x01 << 0) ? fg : bg);	\
			पूर्ण \
	\
			pos += (tpg->hflip ? -8 : 8) / (पूर्णांक)hभाग;	\
		पूर्ण	\
	पूर्ण	\
पूर्ण जबतक (0)

अटल noअंतरभूत व्योम tpg_prपूर्णांक_str_2(स्थिर काष्ठा tpg_data *tpg, u8 *basep[TPG_MAX_PLANES][2],
			अचिन्हित p, अचिन्हित first, अचिन्हित भाग, अचिन्हित step,
			पूर्णांक y, पूर्णांक x, स्थिर अक्षर *text, अचिन्हित len)
अणु
	PRINTSTR(u8);
पूर्ण

अटल noअंतरभूत व्योम tpg_prपूर्णांक_str_4(स्थिर काष्ठा tpg_data *tpg, u8 *basep[TPG_MAX_PLANES][2],
			अचिन्हित p, अचिन्हित first, अचिन्हित भाग, अचिन्हित step,
			पूर्णांक y, पूर्णांक x, स्थिर अक्षर *text, अचिन्हित len)
अणु
	PRINTSTR(u16);
पूर्ण

अटल noअंतरभूत व्योम tpg_prपूर्णांक_str_6(स्थिर काष्ठा tpg_data *tpg, u8 *basep[TPG_MAX_PLANES][2],
			अचिन्हित p, अचिन्हित first, अचिन्हित भाग, अचिन्हित step,
			पूर्णांक y, पूर्णांक x, स्थिर अक्षर *text, अचिन्हित len)
अणु
	PRINTSTR(x24);
पूर्ण

अटल noअंतरभूत व्योम tpg_prपूर्णांक_str_8(स्थिर काष्ठा tpg_data *tpg, u8 *basep[TPG_MAX_PLANES][2],
			अचिन्हित p, अचिन्हित first, अचिन्हित भाग, अचिन्हित step,
			पूर्णांक y, पूर्णांक x, स्थिर अक्षर *text, अचिन्हित len)
अणु
	PRINTSTR(u32);
पूर्ण

व्योम tpg_gen_text(स्थिर काष्ठा tpg_data *tpg, u8 *basep[TPG_MAX_PLANES][2],
		  पूर्णांक y, पूर्णांक x, स्थिर अक्षर *text)
अणु
	अचिन्हित step = V4L2_FIELD_HAS_T_OR_B(tpg->field) ? 2 : 1;
	अचिन्हित भाग = step;
	अचिन्हित first = 0;
	अचिन्हित len;
	अचिन्हित p;

	अगर (font8x16 == शून्य || basep == शून्य || text == शून्य)
		वापस;

	len = म_माप(text);

	/* Checks अगर it is possible to show string */
	अगर (y + 16 >= tpg->compose.height || x + 8 >= tpg->compose.width)
		वापस;

	अगर (len > (tpg->compose.width - x) / 8)
		len = (tpg->compose.width - x) / 8;
	अगर (tpg->vflip)
		y = tpg->compose.height - y - 16;
	अगर (tpg->hflip)
		x = tpg->compose.width - x - 8;
	y += tpg->compose.top;
	x += tpg->compose.left;
	अगर (tpg->field == V4L2_FIELD_BOTTOM)
		first = 1;
	अन्यथा अगर (tpg->field == V4L2_FIELD_SEQ_TB || tpg->field == V4L2_FIELD_SEQ_BT)
		भाग = 2;

	क्रम (p = 0; p < tpg->planes; p++) अणु
		/* Prपूर्णांक text */
		चयन (tpg->twopixelsize[p]) अणु
		हाल 2:
			tpg_prपूर्णांक_str_2(tpg, basep, p, first, भाग, step, y, x,
					text, len);
			अवरोध;
		हाल 4:
			tpg_prपूर्णांक_str_4(tpg, basep, p, first, भाग, step, y, x,
					text, len);
			अवरोध;
		हाल 6:
			tpg_prपूर्णांक_str_6(tpg, basep, p, first, भाग, step, y, x,
					text, len);
			अवरोध;
		हाल 8:
			tpg_prपूर्णांक_str_8(tpg, basep, p, first, भाग, step, y, x,
					text, len);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(tpg_gen_text);

स्थिर अक्षर *tpg_g_color_order(स्थिर काष्ठा tpg_data *tpg)
अणु
	चयन (tpg->pattern) अणु
	हाल TPG_PAT_75_COLORBAR:
	हाल TPG_PAT_100_COLORBAR:
	हाल TPG_PAT_CSC_COLORBAR:
	हाल TPG_PAT_100_HCOLORBAR:
		वापस "White, yellow, cyan, green, magenta, red, blue, black";
	हाल TPG_PAT_BLACK:
		वापस "Black";
	हाल TPG_PAT_WHITE:
		वापस "White";
	हाल TPG_PAT_RED:
		वापस "Red";
	हाल TPG_PAT_GREEN:
		वापस "Green";
	हाल TPG_PAT_BLUE:
		वापस "Blue";
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(tpg_g_color_order);

व्योम tpg_update_mv_step(काष्ठा tpg_data *tpg)
अणु
	पूर्णांक factor = tpg->mv_hor_mode > TPG_MOVE_NONE ? -1 : 1;

	अगर (tpg->hflip)
		factor = -factor;
	चयन (tpg->mv_hor_mode) अणु
	हाल TPG_MOVE_NEG_FAST:
	हाल TPG_MOVE_POS_FAST:
		tpg->mv_hor_step = ((tpg->src_width + 319) / 320) * 4;
		अवरोध;
	हाल TPG_MOVE_NEG:
	हाल TPG_MOVE_POS:
		tpg->mv_hor_step = ((tpg->src_width + 639) / 640) * 4;
		अवरोध;
	हाल TPG_MOVE_NEG_SLOW:
	हाल TPG_MOVE_POS_SLOW:
		tpg->mv_hor_step = 2;
		अवरोध;
	हाल TPG_MOVE_NONE:
		tpg->mv_hor_step = 0;
		अवरोध;
	पूर्ण
	अगर (factor < 0)
		tpg->mv_hor_step = tpg->src_width - tpg->mv_hor_step;

	factor = tpg->mv_vert_mode > TPG_MOVE_NONE ? -1 : 1;
	चयन (tpg->mv_vert_mode) अणु
	हाल TPG_MOVE_NEG_FAST:
	हाल TPG_MOVE_POS_FAST:
		tpg->mv_vert_step = ((tpg->src_width + 319) / 320) * 4;
		अवरोध;
	हाल TPG_MOVE_NEG:
	हाल TPG_MOVE_POS:
		tpg->mv_vert_step = ((tpg->src_width + 639) / 640) * 4;
		अवरोध;
	हाल TPG_MOVE_NEG_SLOW:
	हाल TPG_MOVE_POS_SLOW:
		tpg->mv_vert_step = 1;
		अवरोध;
	हाल TPG_MOVE_NONE:
		tpg->mv_vert_step = 0;
		अवरोध;
	पूर्ण
	अगर (factor < 0)
		tpg->mv_vert_step = tpg->src_height - tpg->mv_vert_step;
पूर्ण
EXPORT_SYMBOL_GPL(tpg_update_mv_step);

/* Map the line number relative to the crop rectangle to a frame line number */
अटल अचिन्हित tpg_calc_frameline(स्थिर काष्ठा tpg_data *tpg, अचिन्हित src_y,
				    अचिन्हित field)
अणु
	चयन (field) अणु
	हाल V4L2_FIELD_TOP:
		वापस tpg->crop.top + src_y * 2;
	हाल V4L2_FIELD_BOTTOM:
		वापस tpg->crop.top + src_y * 2 + 1;
	शेष:
		वापस src_y + tpg->crop.top;
	पूर्ण
पूर्ण

/*
 * Map the line number relative to the compose rectangle to a destination
 * buffer line number.
 */
अटल अचिन्हित tpg_calc_buffer_line(स्थिर काष्ठा tpg_data *tpg, अचिन्हित y,
				    अचिन्हित field)
अणु
	y += tpg->compose.top;
	चयन (field) अणु
	हाल V4L2_FIELD_SEQ_TB:
		अगर (y & 1)
			वापस tpg->buf_height / 2 + y / 2;
		वापस y / 2;
	हाल V4L2_FIELD_SEQ_BT:
		अगर (y & 1)
			वापस y / 2;
		वापस tpg->buf_height / 2 + y / 2;
	शेष:
		वापस y;
	पूर्ण
पूर्ण

अटल व्योम tpg_recalc(काष्ठा tpg_data *tpg)
अणु
	अगर (tpg->recalc_colors) अणु
		tpg->recalc_colors = false;
		tpg->recalc_lines = true;
		tpg->real_xfer_func = tpg->xfer_func;
		tpg->real_ycbcr_enc = tpg->ycbcr_enc;
		tpg->real_hsv_enc = tpg->hsv_enc;
		tpg->real_quantization = tpg->quantization;

		अगर (tpg->xfer_func == V4L2_XFER_FUNC_DEFAULT)
			tpg->real_xfer_func =
				V4L2_MAP_XFER_FUNC_DEFAULT(tpg->colorspace);

		अगर (tpg->ycbcr_enc == V4L2_YCBCR_ENC_DEFAULT)
			tpg->real_ycbcr_enc =
				V4L2_MAP_YCBCR_ENC_DEFAULT(tpg->colorspace);

		अगर (tpg->quantization == V4L2_QUANTIZATION_DEFAULT)
			tpg->real_quantization =
				V4L2_MAP_QUANTIZATION_DEFAULT(
					tpg->color_enc != TGP_COLOR_ENC_YCBCR,
					tpg->colorspace, tpg->real_ycbcr_enc);

		tpg_precalculate_colors(tpg);
	पूर्ण
	अगर (tpg->recalc_square_border) अणु
		tpg->recalc_square_border = false;
		tpg_calculate_square_border(tpg);
	पूर्ण
	अगर (tpg->recalc_lines) अणु
		tpg->recalc_lines = false;
		tpg_precalculate_line(tpg);
	पूर्ण
पूर्ण

व्योम tpg_calc_text_basep(काष्ठा tpg_data *tpg,
		u8 *basep[TPG_MAX_PLANES][2], अचिन्हित p, u8 *vbuf)
अणु
	अचिन्हित stride = tpg->bytesperline[p];
	अचिन्हित h = tpg->buf_height;

	tpg_recalc(tpg);

	basep[p][0] = vbuf;
	basep[p][1] = vbuf;
	h /= tpg->vकरोwnsampling[p];
	अगर (tpg->field == V4L2_FIELD_SEQ_TB)
		basep[p][1] += h * stride / 2;
	अन्यथा अगर (tpg->field == V4L2_FIELD_SEQ_BT)
		basep[p][0] += h * stride / 2;
	अगर (p == 0 && tpg->पूर्णांकerleaved)
		tpg_calc_text_basep(tpg, basep, 1, vbuf);
पूर्ण
EXPORT_SYMBOL_GPL(tpg_calc_text_basep);

अटल पूर्णांक tpg_pattern_avg(स्थिर काष्ठा tpg_data *tpg,
			   अचिन्हित pat1, अचिन्हित pat2)
अणु
	अचिन्हित pat_lines = tpg_get_pat_lines(tpg);

	अगर (pat1 == (pat2 + 1) % pat_lines)
		वापस pat2;
	अगर (pat2 == (pat1 + 1) % pat_lines)
		वापस pat1;
	वापस -1;
पूर्ण

अटल स्थिर अक्षर *tpg_color_enc_str(क्रमागत tgp_color_enc
						 color_enc)
अणु
	चयन (color_enc) अणु
	हाल TGP_COLOR_ENC_HSV:
		वापस "HSV";
	हाल TGP_COLOR_ENC_YCBCR:
		वापस "Y'CbCr";
	हाल TGP_COLOR_ENC_LUMA:
		वापस "Luma";
	हाल TGP_COLOR_ENC_RGB:
	शेष:
		वापस "R'G'B";

	पूर्ण
पूर्ण

व्योम tpg_log_status(काष्ठा tpg_data *tpg)
अणु
	pr_info("tpg source WxH: %ux%u (%s)\n",
		tpg->src_width, tpg->src_height,
		tpg_color_enc_str(tpg->color_enc));
	pr_info("tpg field: %u\n", tpg->field);
	pr_info("tpg crop: %ux%u@%dx%d\n", tpg->crop.width, tpg->crop.height,
			tpg->crop.left, tpg->crop.top);
	pr_info("tpg compose: %ux%u@%dx%d\n", tpg->compose.width, tpg->compose.height,
			tpg->compose.left, tpg->compose.top);
	pr_info("tpg colorspace: %d\n", tpg->colorspace);
	pr_info("tpg transfer function: %d/%d\n", tpg->xfer_func, tpg->real_xfer_func);
	अगर (tpg->color_enc == TGP_COLOR_ENC_HSV)
		pr_info("tpg HSV encoding: %d/%d\n",
			tpg->hsv_enc, tpg->real_hsv_enc);
	अन्यथा अगर (tpg->color_enc == TGP_COLOR_ENC_YCBCR)
		pr_info("tpg Y'CbCr encoding: %d/%d\n",
			tpg->ycbcr_enc, tpg->real_ycbcr_enc);
	pr_info("tpg quantization: %d/%d\n", tpg->quantization, tpg->real_quantization);
	pr_info("tpg RGB range: %d/%d\n", tpg->rgb_range, tpg->real_rgb_range);
पूर्ण
EXPORT_SYMBOL_GPL(tpg_log_status);

/*
 * This काष्ठा contains common parameters used by both the drawing of the
 * test pattern and the drawing of the extras (borders, square, etc.)
 */
काष्ठा tpg_draw_params अणु
	/* common data */
	bool is_tv;
	bool is_60hz;
	अचिन्हित twopixsize;
	अचिन्हित img_width;
	अचिन्हित stride;
	अचिन्हित hmax;
	अचिन्हित frame_line;
	अचिन्हित frame_line_next;

	/* test pattern */
	अचिन्हित mv_hor_old;
	अचिन्हित mv_hor_new;
	अचिन्हित mv_vert_old;
	अचिन्हित mv_vert_new;

	/* extras */
	अचिन्हित wss_width;
	अचिन्हित wss_अक्रमom_offset;
	अचिन्हित sav_eav_f;
	अचिन्हित left_pillar_width;
	अचिन्हित right_pillar_start;
पूर्ण;

अटल व्योम tpg_fill_params_pattern(स्थिर काष्ठा tpg_data *tpg, अचिन्हित p,
				    काष्ठा tpg_draw_params *params)
अणु
	params->mv_hor_old =
		tpg_hscale_भाग(tpg, p, tpg->mv_hor_count % tpg->src_width);
	params->mv_hor_new =
		tpg_hscale_भाग(tpg, p, (tpg->mv_hor_count + tpg->mv_hor_step) %
			       tpg->src_width);
	params->mv_vert_old = tpg->mv_vert_count % tpg->src_height;
	params->mv_vert_new =
		(tpg->mv_vert_count + tpg->mv_vert_step) % tpg->src_height;
पूर्ण

अटल व्योम tpg_fill_params_extras(स्थिर काष्ठा tpg_data *tpg,
				   अचिन्हित p,
				   काष्ठा tpg_draw_params *params)
अणु
	अचिन्हित left_pillar_width = 0;
	अचिन्हित right_pillar_start = params->img_width;

	params->wss_width = tpg->crop.left < tpg->src_width / 2 ?
		tpg->src_width / 2 - tpg->crop.left : 0;
	अगर (params->wss_width > tpg->crop.width)
		params->wss_width = tpg->crop.width;
	params->wss_width = tpg_hscale_भाग(tpg, p, params->wss_width);
	params->wss_अक्रमom_offset =
		params->twopixsize * pअक्रमom_u32_max(tpg->src_width / 2);

	अगर (tpg->crop.left < tpg->border.left) अणु
		left_pillar_width = tpg->border.left - tpg->crop.left;
		अगर (left_pillar_width > tpg->crop.width)
			left_pillar_width = tpg->crop.width;
		left_pillar_width = tpg_hscale_भाग(tpg, p, left_pillar_width);
	पूर्ण
	params->left_pillar_width = left_pillar_width;

	अगर (tpg->crop.left + tpg->crop.width >
	    tpg->border.left + tpg->border.width) अणु
		right_pillar_start =
			tpg->border.left + tpg->border.width - tpg->crop.left;
		right_pillar_start =
			tpg_hscale_भाग(tpg, p, right_pillar_start);
		अगर (right_pillar_start > params->img_width)
			right_pillar_start = params->img_width;
	पूर्ण
	params->right_pillar_start = right_pillar_start;

	params->sav_eav_f = tpg->field ==
			(params->is_60hz ? V4L2_FIELD_TOP : V4L2_FIELD_BOTTOM);
पूर्ण

अटल व्योम tpg_fill_plane_extras(स्थिर काष्ठा tpg_data *tpg,
				  स्थिर काष्ठा tpg_draw_params *params,
				  अचिन्हित p, अचिन्हित h, u8 *vbuf)
अणु
	अचिन्हित twopixsize = params->twopixsize;
	अचिन्हित img_width = params->img_width;
	अचिन्हित frame_line = params->frame_line;
	स्थिर काष्ठा v4l2_rect *sq = &tpg->square;
	स्थिर काष्ठा v4l2_rect *b = &tpg->border;
	स्थिर काष्ठा v4l2_rect *c = &tpg->crop;

	अगर (params->is_tv && !params->is_60hz &&
	    frame_line == 0 && params->wss_width) अणु
		/*
		 * Replace the first half of the top line of a 50 Hz frame
		 * with अक्रमom data to simulate a WSS संकेत.
		 */
		u8 *wss = tpg->अक्रमom_line[p] + params->wss_अक्रमom_offset;

		स_नकल(vbuf, wss, params->wss_width);
	पूर्ण

	अगर (tpg->show_border && frame_line >= b->top &&
	    frame_line < b->top + b->height) अणु
		अचिन्हित bottom = b->top + b->height - 1;
		अचिन्हित left = params->left_pillar_width;
		अचिन्हित right = params->right_pillar_start;

		अगर (frame_line == b->top || frame_line == b->top + 1 ||
		    frame_line == bottom || frame_line == bottom - 1) अणु
			स_नकल(vbuf + left, tpg->contrast_line[p],
					right - left);
		पूर्ण अन्यथा अणु
			अगर (b->left >= c->left &&
			    b->left < c->left + c->width)
				स_नकल(vbuf + left,
					tpg->contrast_line[p], twopixsize);
			अगर (b->left + b->width > c->left &&
			    b->left + b->width <= c->left + c->width)
				स_नकल(vbuf + right - twopixsize,
					tpg->contrast_line[p], twopixsize);
		पूर्ण
	पूर्ण
	अगर (tpg->qual != TPG_QUAL_NOISE && frame_line >= b->top &&
	    frame_line < b->top + b->height) अणु
		स_नकल(vbuf, tpg->black_line[p], params->left_pillar_width);
		स_नकल(vbuf + params->right_pillar_start, tpg->black_line[p],
		       img_width - params->right_pillar_start);
	पूर्ण
	अगर (tpg->show_square && frame_line >= sq->top &&
	    frame_line < sq->top + sq->height &&
	    sq->left < c->left + c->width &&
	    sq->left + sq->width >= c->left) अणु
		अचिन्हित left = sq->left;
		अचिन्हित width = sq->width;

		अगर (c->left > left) अणु
			width -= c->left - left;
			left = c->left;
		पूर्ण
		अगर (c->left + c->width < left + width)
			width -= left + width - c->left - c->width;
		left -= c->left;
		left = tpg_hscale_भाग(tpg, p, left);
		width = tpg_hscale_भाग(tpg, p, width);
		स_नकल(vbuf + left, tpg->contrast_line[p], width);
	पूर्ण
	अगर (tpg->insert_sav) अणु
		अचिन्हित offset = tpg_hभाग(tpg, p, tpg->compose.width / 3);
		u8 *p = vbuf + offset;
		अचिन्हित vact = 0, hact = 0;

		p[0] = 0xff;
		p[1] = 0;
		p[2] = 0;
		p[3] = 0x80 | (params->sav_eav_f << 6) |
			(vact << 5) | (hact << 4) |
			((hact ^ vact) << 3) |
			((hact ^ params->sav_eav_f) << 2) |
			((params->sav_eav_f ^ vact) << 1) |
			(hact ^ vact ^ params->sav_eav_f);
	पूर्ण
	अगर (tpg->insert_eav) अणु
		अचिन्हित offset = tpg_hभाग(tpg, p, tpg->compose.width * 2 / 3);
		u8 *p = vbuf + offset;
		अचिन्हित vact = 0, hact = 1;

		p[0] = 0xff;
		p[1] = 0;
		p[2] = 0;
		p[3] = 0x80 | (params->sav_eav_f << 6) |
			(vact << 5) | (hact << 4) |
			((hact ^ vact) << 3) |
			((hact ^ params->sav_eav_f) << 2) |
			((params->sav_eav_f ^ vact) << 1) |
			(hact ^ vact ^ params->sav_eav_f);
	पूर्ण
पूर्ण

अटल व्योम tpg_fill_plane_pattern(स्थिर काष्ठा tpg_data *tpg,
				   स्थिर काष्ठा tpg_draw_params *params,
				   अचिन्हित p, अचिन्हित h, u8 *vbuf)
अणु
	अचिन्हित twopixsize = params->twopixsize;
	अचिन्हित img_width = params->img_width;
	अचिन्हित mv_hor_old = params->mv_hor_old;
	अचिन्हित mv_hor_new = params->mv_hor_new;
	अचिन्हित mv_vert_old = params->mv_vert_old;
	अचिन्हित mv_vert_new = params->mv_vert_new;
	अचिन्हित frame_line = params->frame_line;
	अचिन्हित frame_line_next = params->frame_line_next;
	अचिन्हित line_offset = tpg_hscale_भाग(tpg, p, tpg->crop.left);
	bool even;
	bool fill_blank = false;
	अचिन्हित pat_line_old;
	अचिन्हित pat_line_new;
	u8 *linestart_older;
	u8 *linestart_newer;
	u8 *linestart_top;
	u8 *linestart_bottom;

	even = !(frame_line & 1);

	अगर (h >= params->hmax) अणु
		अगर (params->hmax == tpg->compose.height)
			वापस;
		अगर (!tpg->perc_fill_blank)
			वापस;
		fill_blank = true;
	पूर्ण

	अगर (tpg->vflip) अणु
		frame_line = tpg->src_height - frame_line - 1;
		frame_line_next = tpg->src_height - frame_line_next - 1;
	पूर्ण

	अगर (fill_blank) अणु
		linestart_older = tpg->contrast_line[p];
		linestart_newer = tpg->contrast_line[p];
	पूर्ण अन्यथा अगर (tpg->qual != TPG_QUAL_NOISE &&
		   (frame_line < tpg->border.top ||
		    frame_line >= tpg->border.top + tpg->border.height)) अणु
		linestart_older = tpg->black_line[p];
		linestart_newer = tpg->black_line[p];
	पूर्ण अन्यथा अगर (tpg->pattern == TPG_PAT_NOISE || tpg->qual == TPG_QUAL_NOISE) अणु
		linestart_older = tpg->अक्रमom_line[p] +
				  twopixsize * pअक्रमom_u32_max(tpg->src_width / 2);
		linestart_newer = tpg->अक्रमom_line[p] +
				  twopixsize * pअक्रमom_u32_max(tpg->src_width / 2);
	पूर्ण अन्यथा अणु
		अचिन्हित frame_line_old =
			(frame_line + mv_vert_old) % tpg->src_height;
		अचिन्हित frame_line_new =
			(frame_line + mv_vert_new) % tpg->src_height;
		अचिन्हित pat_line_next_old;
		अचिन्हित pat_line_next_new;

		pat_line_old = tpg_get_pat_line(tpg, frame_line_old);
		pat_line_new = tpg_get_pat_line(tpg, frame_line_new);
		linestart_older = tpg->lines[pat_line_old][p] + mv_hor_old;
		linestart_newer = tpg->lines[pat_line_new][p] + mv_hor_new;

		अगर (tpg->vकरोwnsampling[p] > 1 && frame_line != frame_line_next) अणु
			पूर्णांक avg_pat;

			/*
			 * Now decide whether we need to use करोwnsampled_lines[].
			 * That's necessary अगर the two lines use dअगरferent patterns.
			 */
			pat_line_next_old = tpg_get_pat_line(tpg,
					(frame_line_next + mv_vert_old) % tpg->src_height);
			pat_line_next_new = tpg_get_pat_line(tpg,
					(frame_line_next + mv_vert_new) % tpg->src_height);

			चयन (tpg->field) अणु
			हाल V4L2_FIELD_INTERLACED:
			हाल V4L2_FIELD_INTERLACED_BT:
			हाल V4L2_FIELD_INTERLACED_TB:
				avg_pat = tpg_pattern_avg(tpg, pat_line_old, pat_line_new);
				अगर (avg_pat < 0)
					अवरोध;
				linestart_older = tpg->करोwnsampled_lines[avg_pat][p] + mv_hor_old;
				linestart_newer = linestart_older;
				अवरोध;
			हाल V4L2_FIELD_NONE:
			हाल V4L2_FIELD_TOP:
			हाल V4L2_FIELD_BOTTOM:
			हाल V4L2_FIELD_SEQ_BT:
			हाल V4L2_FIELD_SEQ_TB:
				avg_pat = tpg_pattern_avg(tpg, pat_line_old, pat_line_next_old);
				अगर (avg_pat >= 0)
					linestart_older = tpg->करोwnsampled_lines[avg_pat][p] +
						mv_hor_old;
				avg_pat = tpg_pattern_avg(tpg, pat_line_new, pat_line_next_new);
				अगर (avg_pat >= 0)
					linestart_newer = tpg->करोwnsampled_lines[avg_pat][p] +
						mv_hor_new;
				अवरोध;
			पूर्ण
		पूर्ण
		linestart_older += line_offset;
		linestart_newer += line_offset;
	पूर्ण
	अगर (tpg->field_alternate) अणु
		linestart_top = linestart_bottom = linestart_older;
	पूर्ण अन्यथा अगर (params->is_60hz) अणु
		linestart_top = linestart_newer;
		linestart_bottom = linestart_older;
	पूर्ण अन्यथा अणु
		linestart_top = linestart_older;
		linestart_bottom = linestart_newer;
	पूर्ण

	चयन (tpg->field) अणु
	हाल V4L2_FIELD_INTERLACED:
	हाल V4L2_FIELD_INTERLACED_TB:
	हाल V4L2_FIELD_SEQ_TB:
	हाल V4L2_FIELD_SEQ_BT:
		अगर (even)
			स_नकल(vbuf, linestart_top, img_width);
		अन्यथा
			स_नकल(vbuf, linestart_bottom, img_width);
		अवरोध;
	हाल V4L2_FIELD_INTERLACED_BT:
		अगर (even)
			स_नकल(vbuf, linestart_bottom, img_width);
		अन्यथा
			स_नकल(vbuf, linestart_top, img_width);
		अवरोध;
	हाल V4L2_FIELD_TOP:
		स_नकल(vbuf, linestart_top, img_width);
		अवरोध;
	हाल V4L2_FIELD_BOTTOM:
		स_नकल(vbuf, linestart_bottom, img_width);
		अवरोध;
	हाल V4L2_FIELD_NONE:
	शेष:
		स_नकल(vbuf, linestart_older, img_width);
		अवरोध;
	पूर्ण
पूर्ण

व्योम tpg_fill_plane_buffer(काष्ठा tpg_data *tpg, v4l2_std_id std,
			   अचिन्हित p, u8 *vbuf)
अणु
	काष्ठा tpg_draw_params params;
	अचिन्हित factor = V4L2_FIELD_HAS_T_OR_B(tpg->field) ? 2 : 1;

	/* Coarse scaling with Bresenham */
	अचिन्हित पूर्णांक_part = (tpg->crop.height / factor) / tpg->compose.height;
	अचिन्हित fract_part = (tpg->crop.height / factor) % tpg->compose.height;
	अचिन्हित src_y = 0;
	अचिन्हित error = 0;
	अचिन्हित h;

	tpg_recalc(tpg);

	params.is_tv = std;
	params.is_60hz = std & V4L2_STD_525_60;
	params.twopixsize = tpg->twopixelsize[p];
	params.img_width = tpg_hभाग(tpg, p, tpg->compose.width);
	params.stride = tpg->bytesperline[p];
	params.hmax = (tpg->compose.height * tpg->perc_fill) / 100;

	tpg_fill_params_pattern(tpg, p, &params);
	tpg_fill_params_extras(tpg, p, &params);

	vbuf += tpg_hभाग(tpg, p, tpg->compose.left);

	क्रम (h = 0; h < tpg->compose.height; h++) अणु
		अचिन्हित buf_line;

		params.frame_line = tpg_calc_frameline(tpg, src_y, tpg->field);
		params.frame_line_next = params.frame_line;
		buf_line = tpg_calc_buffer_line(tpg, h, tpg->field);
		src_y += पूर्णांक_part;
		error += fract_part;
		अगर (error >= tpg->compose.height) अणु
			error -= tpg->compose.height;
			src_y++;
		पूर्ण

		/*
		 * For line-पूर्णांकerleaved क्रमmats determine the 'plane'
		 * based on the buffer line.
		 */
		अगर (tpg_g_पूर्णांकerleaved(tpg))
			p = tpg_g_पूर्णांकerleaved_plane(tpg, buf_line);

		अगर (tpg->vकरोwnsampling[p] > 1) अणु
			/*
			 * When करोing vertical करोwnsampling the field setting
			 * matters: क्रम SEQ_BT/TB we करोwnsample each field
			 * separately (i.e. lines 0+2 are combined, as are
			 * lines 1+3), क्रम the other field settings we combine
			 * odd and even lines. Doing that क्रम SEQ_BT/TB would
			 * be really weird.
			 */
			अगर (tpg->field == V4L2_FIELD_SEQ_BT ||
			    tpg->field == V4L2_FIELD_SEQ_TB) अणु
				अचिन्हित next_src_y = src_y;

				अगर ((h & 3) >= 2)
					जारी;
				next_src_y += पूर्णांक_part;
				अगर (error + fract_part >= tpg->compose.height)
					next_src_y++;
				params.frame_line_next =
					tpg_calc_frameline(tpg, next_src_y, tpg->field);
			पूर्ण अन्यथा अणु
				अगर (h & 1)
					जारी;
				params.frame_line_next =
					tpg_calc_frameline(tpg, src_y, tpg->field);
			पूर्ण

			buf_line /= tpg->vकरोwnsampling[p];
		पूर्ण
		tpg_fill_plane_pattern(tpg, &params, p, h,
				vbuf + buf_line * params.stride);
		tpg_fill_plane_extras(tpg, &params, p, h,
				vbuf + buf_line * params.stride);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(tpg_fill_plane_buffer);

व्योम tpg_fillbuffer(काष्ठा tpg_data *tpg, v4l2_std_id std, अचिन्हित p, u8 *vbuf)
अणु
	अचिन्हित offset = 0;
	अचिन्हित i;

	अगर (tpg->buffers > 1) अणु
		tpg_fill_plane_buffer(tpg, std, p, vbuf);
		वापस;
	पूर्ण

	क्रम (i = 0; i < tpg_g_planes(tpg); i++) अणु
		tpg_fill_plane_buffer(tpg, std, i, vbuf + offset);
		offset += tpg_calc_plane_size(tpg, i);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(tpg_fillbuffer);

MODULE_DESCRIPTION("V4L2 Test Pattern Generator");
MODULE_AUTHOR("Hans Verkuil");
MODULE_LICENSE("GPL");
