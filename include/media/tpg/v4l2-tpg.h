<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * v4l2-tpg.h - Test Pattern Generator
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#अगर_अघोषित _V4L2_TPG_H_
#घोषणा _V4L2_TPG_H_

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/videodev2.h>

काष्ठा tpg_rbg_color8 अणु
	अचिन्हित अक्षर r, g, b;
पूर्ण;

काष्ठा tpg_rbg_color16 अणु
	__u16 r, g, b;
पूर्ण;

क्रमागत tpg_color अणु
	TPG_COLOR_CSC_WHITE,
	TPG_COLOR_CSC_YELLOW,
	TPG_COLOR_CSC_CYAN,
	TPG_COLOR_CSC_GREEN,
	TPG_COLOR_CSC_MAGENTA,
	TPG_COLOR_CSC_RED,
	TPG_COLOR_CSC_BLUE,
	TPG_COLOR_CSC_BLACK,
	TPG_COLOR_75_YELLOW,
	TPG_COLOR_75_CYAN,
	TPG_COLOR_75_GREEN,
	TPG_COLOR_75_MAGENTA,
	TPG_COLOR_75_RED,
	TPG_COLOR_75_BLUE,
	TPG_COLOR_100_WHITE,
	TPG_COLOR_100_YELLOW,
	TPG_COLOR_100_CYAN,
	TPG_COLOR_100_GREEN,
	TPG_COLOR_100_MAGENTA,
	TPG_COLOR_100_RED,
	TPG_COLOR_100_BLUE,
	TPG_COLOR_100_BLACK,
	TPG_COLOR_TEXTFG,
	TPG_COLOR_TEXTBG,
	TPG_COLOR_RANDOM,
	TPG_COLOR_RAMP,
	TPG_COLOR_MAX = TPG_COLOR_RAMP + 256
पूर्ण;

बाह्य स्थिर काष्ठा tpg_rbg_color8 tpg_colors[TPG_COLOR_MAX];
बाह्य स्थिर अचिन्हित लघु tpg_rec709_to_linear[255 * 16 + 1];
बाह्य स्थिर अचिन्हित लघु tpg_linear_to_rec709[255 * 16 + 1];
बाह्य स्थिर काष्ठा tpg_rbg_color16 tpg_csc_colors[V4L2_COLORSPACE_DCI_P3 + 1]
					  [V4L2_XFER_FUNC_SMPTE2084 + 1]
					  [TPG_COLOR_CSC_BLACK + 1];
क्रमागत tpg_pattern अणु
	TPG_PAT_75_COLORBAR,
	TPG_PAT_100_COLORBAR,
	TPG_PAT_CSC_COLORBAR,
	TPG_PAT_100_HCOLORBAR,
	TPG_PAT_100_COLORSQUARES,
	TPG_PAT_BLACK,
	TPG_PAT_WHITE,
	TPG_PAT_RED,
	TPG_PAT_GREEN,
	TPG_PAT_BLUE,
	TPG_PAT_CHECKERS_16X16,
	TPG_PAT_CHECKERS_2X2,
	TPG_PAT_CHECKERS_1X1,
	TPG_PAT_COLOR_CHECKERS_2X2,
	TPG_PAT_COLOR_CHECKERS_1X1,
	TPG_PAT_ALTERNATING_HLINES,
	TPG_PAT_ALTERNATING_VLINES,
	TPG_PAT_CROSS_1_PIXEL,
	TPG_PAT_CROSS_2_PIXELS,
	TPG_PAT_CROSS_10_PIXELS,
	TPG_PAT_GRAY_RAMP,

	/* Must be the last pattern */
	TPG_PAT_NOISE,
पूर्ण;

बाह्य स्थिर अक्षर * स्थिर tpg_pattern_strings[];

क्रमागत tpg_quality अणु
	TPG_QUAL_COLOR,
	TPG_QUAL_GRAY,
	TPG_QUAL_NOISE
पूर्ण;

क्रमागत tpg_video_aspect अणु
	TPG_VIDEO_ASPECT_IMAGE,
	TPG_VIDEO_ASPECT_4X3,
	TPG_VIDEO_ASPECT_14X9_CENTRE,
	TPG_VIDEO_ASPECT_16X9_CENTRE,
	TPG_VIDEO_ASPECT_16X9_ANAMORPHIC,
पूर्ण;

क्रमागत tpg_pixel_aspect अणु
	TPG_PIXEL_ASPECT_SQUARE,
	TPG_PIXEL_ASPECT_NTSC,
	TPG_PIXEL_ASPECT_PAL,
पूर्ण;

क्रमागत tpg_move_mode अणु
	TPG_MOVE_NEG_FAST,
	TPG_MOVE_NEG,
	TPG_MOVE_NEG_SLOW,
	TPG_MOVE_NONE,
	TPG_MOVE_POS_SLOW,
	TPG_MOVE_POS,
	TPG_MOVE_POS_FAST,
पूर्ण;

क्रमागत tgp_color_enc अणु
	TGP_COLOR_ENC_RGB,
	TGP_COLOR_ENC_YCBCR,
	TGP_COLOR_ENC_HSV,
	TGP_COLOR_ENC_LUMA,
पूर्ण;

बाह्य स्थिर अक्षर * स्थिर tpg_aspect_strings[];

#घोषणा TPG_MAX_PLANES 3
#घोषणा TPG_MAX_PAT_LINES 8

काष्ठा tpg_data अणु
	/* Source frame size */
	अचिन्हित			src_width, src_height;
	/* Buffer height */
	अचिन्हित			buf_height;
	/* Scaled output frame size */
	अचिन्हित			scaled_width;
	u32				field;
	bool				field_alternate;
	/* crop coordinates are frame-based */
	काष्ठा v4l2_rect		crop;
	/* compose coordinates are क्रमmat-based */
	काष्ठा v4l2_rect		compose;
	/* border and square coordinates are frame-based */
	काष्ठा v4l2_rect		border;
	काष्ठा v4l2_rect		square;

	/* Color-related fields */
	क्रमागत tpg_quality		qual;
	अचिन्हित			qual_offset;
	u8				alpha_component;
	bool				alpha_red_only;
	u8				brightness;
	u8				contrast;
	u8				saturation;
	s16				hue;
	u32				fourcc;
	क्रमागत tgp_color_enc		color_enc;
	u32				colorspace;
	u32				xfer_func;
	u32				ycbcr_enc;
	u32				hsv_enc;
	/*
	 * Stores the actual transfer function, i.e. will never be
	 * V4L2_XFER_FUNC_DEFAULT.
	 */
	u32				real_xfer_func;
	/*
	 * Stores the actual Y'CbCr encoding, i.e. will never be
	 * V4L2_YCBCR_ENC_DEFAULT.
	 */
	u32				real_hsv_enc;
	u32				real_ycbcr_enc;
	u32				quantization;
	/*
	 * Stores the actual quantization, i.e. will never be
	 * V4L2_QUANTIZATION_DEFAULT.
	 */
	u32				real_quantization;
	क्रमागत tpg_video_aspect		vid_aspect;
	क्रमागत tpg_pixel_aspect		pix_aspect;
	अचिन्हित			rgb_range;
	अचिन्हित			real_rgb_range;
	अचिन्हित			buffers;
	अचिन्हित			planes;
	bool				पूर्णांकerleaved;
	u8				vकरोwnsampling[TPG_MAX_PLANES];
	u8				hकरोwnsampling[TPG_MAX_PLANES];
	/*
	 * horizontal positions must be ANDed with this value to enक्रमce
	 * correct boundaries क्रम packed YUYV values.
	 */
	अचिन्हित			hmask[TPG_MAX_PLANES];
	/* Used to store the colors in native क्रमmat, either RGB or YUV */
	u8				colors[TPG_COLOR_MAX][3];
	u8				textfg[TPG_MAX_PLANES][8], textbg[TPG_MAX_PLANES][8];
	/* size in bytes क्रम two pixels in each plane */
	अचिन्हित			twopixelsize[TPG_MAX_PLANES];
	अचिन्हित			bytesperline[TPG_MAX_PLANES];

	/* Configuration */
	क्रमागत tpg_pattern		pattern;
	bool				hflip;
	bool				vflip;
	अचिन्हित			perc_fill;
	bool				perc_fill_blank;
	bool				show_border;
	bool				show_square;
	bool				insert_sav;
	bool				insert_eav;

	/* Test pattern movement */
	क्रमागत tpg_move_mode		mv_hor_mode;
	पूर्णांक				mv_hor_count;
	पूर्णांक				mv_hor_step;
	क्रमागत tpg_move_mode		mv_vert_mode;
	पूर्णांक				mv_vert_count;
	पूर्णांक				mv_vert_step;

	bool				recalc_colors;
	bool				recalc_lines;
	bool				recalc_square_border;

	/* Used to store TPG_MAX_PAT_LINES lines, each with up to two planes */
	अचिन्हित			max_line_width;
	u8				*lines[TPG_MAX_PAT_LINES][TPG_MAX_PLANES];
	u8				*करोwnsampled_lines[TPG_MAX_PAT_LINES][TPG_MAX_PLANES];
	u8				*अक्रमom_line[TPG_MAX_PLANES];
	u8				*contrast_line[TPG_MAX_PLANES];
	u8				*black_line[TPG_MAX_PLANES];
पूर्ण;

व्योम tpg_init(काष्ठा tpg_data *tpg, अचिन्हित w, अचिन्हित h);
पूर्णांक tpg_alloc(काष्ठा tpg_data *tpg, अचिन्हित max_w);
व्योम tpg_मुक्त(काष्ठा tpg_data *tpg);
व्योम tpg_reset_source(काष्ठा tpg_data *tpg, अचिन्हित width, अचिन्हित height,
		       u32 field);
व्योम tpg_log_status(काष्ठा tpg_data *tpg);

व्योम tpg_set_font(स्थिर u8 *f);
व्योम tpg_gen_text(स्थिर काष्ठा tpg_data *tpg,
		u8 *basep[TPG_MAX_PLANES][2], पूर्णांक y, पूर्णांक x, स्थिर अक्षर *text);
व्योम tpg_calc_text_basep(काष्ठा tpg_data *tpg,
		u8 *basep[TPG_MAX_PLANES][2], अचिन्हित p, u8 *vbuf);
अचिन्हित tpg_g_पूर्णांकerleaved_plane(स्थिर काष्ठा tpg_data *tpg, अचिन्हित buf_line);
व्योम tpg_fill_plane_buffer(काष्ठा tpg_data *tpg, v4l2_std_id std,
			   अचिन्हित p, u8 *vbuf);
व्योम tpg_fillbuffer(काष्ठा tpg_data *tpg, v4l2_std_id std,
		    अचिन्हित p, u8 *vbuf);
bool tpg_s_fourcc(काष्ठा tpg_data *tpg, u32 fourcc);
व्योम tpg_s_crop_compose(काष्ठा tpg_data *tpg, स्थिर काष्ठा v4l2_rect *crop,
		स्थिर काष्ठा v4l2_rect *compose);
स्थिर अक्षर *tpg_g_color_order(स्थिर काष्ठा tpg_data *tpg);

अटल अंतरभूत व्योम tpg_s_pattern(काष्ठा tpg_data *tpg, क्रमागत tpg_pattern pattern)
अणु
	अगर (tpg->pattern == pattern)
		वापस;
	tpg->pattern = pattern;
	tpg->recalc_colors = true;
पूर्ण

अटल अंतरभूत व्योम tpg_s_quality(काष्ठा tpg_data *tpg,
				    क्रमागत tpg_quality qual, अचिन्हित qual_offset)
अणु
	अगर (tpg->qual == qual && tpg->qual_offset == qual_offset)
		वापस;
	tpg->qual = qual;
	tpg->qual_offset = qual_offset;
	tpg->recalc_colors = true;
पूर्ण

अटल अंतरभूत क्रमागत tpg_quality tpg_g_quality(स्थिर काष्ठा tpg_data *tpg)
अणु
	वापस tpg->qual;
पूर्ण

अटल अंतरभूत व्योम tpg_s_alpha_component(काष्ठा tpg_data *tpg,
					    u8 alpha_component)
अणु
	अगर (tpg->alpha_component == alpha_component)
		वापस;
	tpg->alpha_component = alpha_component;
	tpg->recalc_colors = true;
पूर्ण

अटल अंतरभूत व्योम tpg_s_alpha_mode(काष्ठा tpg_data *tpg,
					    bool red_only)
अणु
	अगर (tpg->alpha_red_only == red_only)
		वापस;
	tpg->alpha_red_only = red_only;
	tpg->recalc_colors = true;
पूर्ण

अटल अंतरभूत व्योम tpg_s_brightness(काष्ठा tpg_data *tpg,
					u8 brightness)
अणु
	अगर (tpg->brightness == brightness)
		वापस;
	tpg->brightness = brightness;
	tpg->recalc_colors = true;
पूर्ण

अटल अंतरभूत व्योम tpg_s_contrast(काष्ठा tpg_data *tpg,
					u8 contrast)
अणु
	अगर (tpg->contrast == contrast)
		वापस;
	tpg->contrast = contrast;
	tpg->recalc_colors = true;
पूर्ण

अटल अंतरभूत व्योम tpg_s_saturation(काष्ठा tpg_data *tpg,
					u8 saturation)
अणु
	अगर (tpg->saturation == saturation)
		वापस;
	tpg->saturation = saturation;
	tpg->recalc_colors = true;
पूर्ण

अटल अंतरभूत व्योम tpg_s_hue(काष्ठा tpg_data *tpg,
					s16 hue)
अणु
	hue = clamp_t(s16, hue, -128, 128);
	अगर (tpg->hue == hue)
		वापस;
	tpg->hue = hue;
	tpg->recalc_colors = true;
पूर्ण

अटल अंतरभूत व्योम tpg_s_rgb_range(काष्ठा tpg_data *tpg,
					अचिन्हित rgb_range)
अणु
	अगर (tpg->rgb_range == rgb_range)
		वापस;
	tpg->rgb_range = rgb_range;
	tpg->recalc_colors = true;
पूर्ण

अटल अंतरभूत व्योम tpg_s_real_rgb_range(काष्ठा tpg_data *tpg,
					अचिन्हित rgb_range)
अणु
	अगर (tpg->real_rgb_range == rgb_range)
		वापस;
	tpg->real_rgb_range = rgb_range;
	tpg->recalc_colors = true;
पूर्ण

अटल अंतरभूत व्योम tpg_s_colorspace(काष्ठा tpg_data *tpg, u32 colorspace)
अणु
	अगर (tpg->colorspace == colorspace)
		वापस;
	tpg->colorspace = colorspace;
	tpg->recalc_colors = true;
पूर्ण

अटल अंतरभूत u32 tpg_g_colorspace(स्थिर काष्ठा tpg_data *tpg)
अणु
	वापस tpg->colorspace;
पूर्ण

अटल अंतरभूत व्योम tpg_s_ycbcr_enc(काष्ठा tpg_data *tpg, u32 ycbcr_enc)
अणु
	अगर (tpg->ycbcr_enc == ycbcr_enc)
		वापस;
	tpg->ycbcr_enc = ycbcr_enc;
	tpg->recalc_colors = true;
पूर्ण

अटल अंतरभूत u32 tpg_g_ycbcr_enc(स्थिर काष्ठा tpg_data *tpg)
अणु
	वापस tpg->ycbcr_enc;
पूर्ण

अटल अंतरभूत व्योम tpg_s_hsv_enc(काष्ठा tpg_data *tpg, u32 hsv_enc)
अणु
	अगर (tpg->hsv_enc == hsv_enc)
		वापस;
	tpg->hsv_enc = hsv_enc;
	tpg->recalc_colors = true;
पूर्ण

अटल अंतरभूत u32 tpg_g_hsv_enc(स्थिर काष्ठा tpg_data *tpg)
अणु
	वापस tpg->hsv_enc;
पूर्ण

अटल अंतरभूत व्योम tpg_s_xfer_func(काष्ठा tpg_data *tpg, u32 xfer_func)
अणु
	अगर (tpg->xfer_func == xfer_func)
		वापस;
	tpg->xfer_func = xfer_func;
	tpg->recalc_colors = true;
पूर्ण

अटल अंतरभूत u32 tpg_g_xfer_func(स्थिर काष्ठा tpg_data *tpg)
अणु
	वापस tpg->xfer_func;
पूर्ण

अटल अंतरभूत व्योम tpg_s_quantization(काष्ठा tpg_data *tpg, u32 quantization)
अणु
	अगर (tpg->quantization == quantization)
		वापस;
	tpg->quantization = quantization;
	tpg->recalc_colors = true;
पूर्ण

अटल अंतरभूत u32 tpg_g_quantization(स्थिर काष्ठा tpg_data *tpg)
अणु
	वापस tpg->quantization;
पूर्ण

अटल अंतरभूत अचिन्हित tpg_g_buffers(स्थिर काष्ठा tpg_data *tpg)
अणु
	वापस tpg->buffers;
पूर्ण

अटल अंतरभूत अचिन्हित tpg_g_planes(स्थिर काष्ठा tpg_data *tpg)
अणु
	वापस tpg->पूर्णांकerleaved ? 1 : tpg->planes;
पूर्ण

अटल अंतरभूत bool tpg_g_पूर्णांकerleaved(स्थिर काष्ठा tpg_data *tpg)
अणु
	वापस tpg->पूर्णांकerleaved;
पूर्ण

अटल अंतरभूत अचिन्हित tpg_g_twopixelsize(स्थिर काष्ठा tpg_data *tpg, अचिन्हित plane)
अणु
	वापस tpg->twopixelsize[plane];
पूर्ण

अटल अंतरभूत अचिन्हित tpg_hभाग(स्थिर काष्ठा tpg_data *tpg,
				  अचिन्हित plane, अचिन्हित x)
अणु
	वापस ((x / tpg->hकरोwnsampling[plane]) & tpg->hmask[plane]) *
		tpg->twopixelsize[plane] / 2;
पूर्ण

अटल अंतरभूत अचिन्हित tpg_hscale(स्थिर काष्ठा tpg_data *tpg, अचिन्हित x)
अणु
	वापस (x * tpg->scaled_width) / tpg->src_width;
पूर्ण

अटल अंतरभूत अचिन्हित tpg_hscale_भाग(स्थिर काष्ठा tpg_data *tpg,
				      अचिन्हित plane, अचिन्हित x)
अणु
	वापस tpg_hभाग(tpg, plane, tpg_hscale(tpg, x));
पूर्ण

अटल अंतरभूत अचिन्हित tpg_g_bytesperline(स्थिर काष्ठा tpg_data *tpg, अचिन्हित plane)
अणु
	वापस tpg->bytesperline[plane];
पूर्ण

अटल अंतरभूत व्योम tpg_s_bytesperline(काष्ठा tpg_data *tpg, अचिन्हित plane, अचिन्हित bpl)
अणु
	अचिन्हित p;

	अगर (tpg->buffers > 1) अणु
		tpg->bytesperline[plane] = bpl;
		वापस;
	पूर्ण

	क्रम (p = 0; p < tpg_g_planes(tpg); p++) अणु
		अचिन्हित plane_w = bpl * tpg->twopixelsize[p] / tpg->twopixelsize[0];

		tpg->bytesperline[p] = plane_w / tpg->hकरोwnsampling[p];
	पूर्ण
	अगर (tpg_g_पूर्णांकerleaved(tpg))
		tpg->bytesperline[1] = tpg->bytesperline[0];
पूर्ण


अटल अंतरभूत अचिन्हित tpg_g_line_width(स्थिर काष्ठा tpg_data *tpg, अचिन्हित plane)
अणु
	अचिन्हित w = 0;
	अचिन्हित p;

	अगर (tpg->buffers > 1)
		वापस tpg_g_bytesperline(tpg, plane);
	क्रम (p = 0; p < tpg_g_planes(tpg); p++) अणु
		अचिन्हित plane_w = tpg_g_bytesperline(tpg, p);

		w += plane_w / tpg->vकरोwnsampling[p];
	पूर्ण
	वापस w;
पूर्ण

अटल अंतरभूत अचिन्हित tpg_calc_line_width(स्थिर काष्ठा tpg_data *tpg,
					   अचिन्हित plane, अचिन्हित bpl)
अणु
	अचिन्हित w = 0;
	अचिन्हित p;

	अगर (tpg->buffers > 1)
		वापस bpl;
	क्रम (p = 0; p < tpg_g_planes(tpg); p++) अणु
		अचिन्हित plane_w = bpl * tpg->twopixelsize[p] / tpg->twopixelsize[0];

		plane_w /= tpg->hकरोwnsampling[p];
		w += plane_w / tpg->vकरोwnsampling[p];
	पूर्ण
	वापस w;
पूर्ण

अटल अंतरभूत अचिन्हित tpg_calc_plane_size(स्थिर काष्ठा tpg_data *tpg, अचिन्हित plane)
अणु
	अगर (plane >= tpg_g_planes(tpg))
		वापस 0;

	वापस tpg_g_bytesperline(tpg, plane) * tpg->buf_height /
	       tpg->vकरोwnsampling[plane];
पूर्ण

अटल अंतरभूत व्योम tpg_s_buf_height(काष्ठा tpg_data *tpg, अचिन्हित h)
अणु
	tpg->buf_height = h;
पूर्ण

अटल अंतरभूत व्योम tpg_s_field(काष्ठा tpg_data *tpg, अचिन्हित field, bool alternate)
अणु
	tpg->field = field;
	tpg->field_alternate = alternate;
पूर्ण

अटल अंतरभूत व्योम tpg_s_perc_fill(काष्ठा tpg_data *tpg,
				      अचिन्हित perc_fill)
अणु
	tpg->perc_fill = perc_fill;
पूर्ण

अटल अंतरभूत अचिन्हित tpg_g_perc_fill(स्थिर काष्ठा tpg_data *tpg)
अणु
	वापस tpg->perc_fill;
पूर्ण

अटल अंतरभूत व्योम tpg_s_perc_fill_blank(काष्ठा tpg_data *tpg,
					 bool perc_fill_blank)
अणु
	tpg->perc_fill_blank = perc_fill_blank;
पूर्ण

अटल अंतरभूत व्योम tpg_s_video_aspect(काष्ठा tpg_data *tpg,
					क्रमागत tpg_video_aspect vid_aspect)
अणु
	अगर (tpg->vid_aspect == vid_aspect)
		वापस;
	tpg->vid_aspect = vid_aspect;
	tpg->recalc_square_border = true;
पूर्ण

अटल अंतरभूत क्रमागत tpg_video_aspect tpg_g_video_aspect(स्थिर काष्ठा tpg_data *tpg)
अणु
	वापस tpg->vid_aspect;
पूर्ण

अटल अंतरभूत व्योम tpg_s_pixel_aspect(काष्ठा tpg_data *tpg,
					क्रमागत tpg_pixel_aspect pix_aspect)
अणु
	अगर (tpg->pix_aspect == pix_aspect)
		वापस;
	tpg->pix_aspect = pix_aspect;
	tpg->recalc_square_border = true;
पूर्ण

अटल अंतरभूत व्योम tpg_s_show_border(काष्ठा tpg_data *tpg,
					bool show_border)
अणु
	tpg->show_border = show_border;
पूर्ण

अटल अंतरभूत व्योम tpg_s_show_square(काष्ठा tpg_data *tpg,
					bool show_square)
अणु
	tpg->show_square = show_square;
पूर्ण

अटल अंतरभूत व्योम tpg_s_insert_sav(काष्ठा tpg_data *tpg, bool insert_sav)
अणु
	tpg->insert_sav = insert_sav;
पूर्ण

अटल अंतरभूत व्योम tpg_s_insert_eav(काष्ठा tpg_data *tpg, bool insert_eav)
अणु
	tpg->insert_eav = insert_eav;
पूर्ण

व्योम tpg_update_mv_step(काष्ठा tpg_data *tpg);

अटल अंतरभूत व्योम tpg_s_mv_hor_mode(काष्ठा tpg_data *tpg,
				क्रमागत tpg_move_mode mv_hor_mode)
अणु
	tpg->mv_hor_mode = mv_hor_mode;
	tpg_update_mv_step(tpg);
पूर्ण

अटल अंतरभूत व्योम tpg_s_mv_vert_mode(काष्ठा tpg_data *tpg,
				क्रमागत tpg_move_mode mv_vert_mode)
अणु
	tpg->mv_vert_mode = mv_vert_mode;
	tpg_update_mv_step(tpg);
पूर्ण

अटल अंतरभूत व्योम tpg_init_mv_count(काष्ठा tpg_data *tpg)
अणु
	tpg->mv_hor_count = tpg->mv_vert_count = 0;
पूर्ण

अटल अंतरभूत व्योम tpg_update_mv_count(काष्ठा tpg_data *tpg, bool frame_is_field)
अणु
	tpg->mv_hor_count += tpg->mv_hor_step * (frame_is_field ? 1 : 2);
	tpg->mv_vert_count += tpg->mv_vert_step * (frame_is_field ? 1 : 2);
पूर्ण

अटल अंतरभूत व्योम tpg_s_hflip(काष्ठा tpg_data *tpg, bool hflip)
अणु
	अगर (tpg->hflip == hflip)
		वापस;
	tpg->hflip = hflip;
	tpg_update_mv_step(tpg);
	tpg->recalc_lines = true;
पूर्ण

अटल अंतरभूत bool tpg_g_hflip(स्थिर काष्ठा tpg_data *tpg)
अणु
	वापस tpg->hflip;
पूर्ण

अटल अंतरभूत व्योम tpg_s_vflip(काष्ठा tpg_data *tpg, bool vflip)
अणु
	tpg->vflip = vflip;
पूर्ण

अटल अंतरभूत bool tpg_g_vflip(स्थिर काष्ठा tpg_data *tpg)
अणु
	वापस tpg->vflip;
पूर्ण

अटल अंतरभूत bool tpg_pattern_is_अटल(स्थिर काष्ठा tpg_data *tpg)
अणु
	वापस tpg->pattern != TPG_PAT_NOISE &&
	       tpg->mv_hor_mode == TPG_MOVE_NONE &&
	       tpg->mv_vert_mode == TPG_MOVE_NONE;
पूर्ण

#पूर्ण_अगर
