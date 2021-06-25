<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2012-2016 Mentor Graphics Inc.
 *
 * Queued image conversion support, with tiling and rotation.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <video/imx-ipu-image-convert.h>
#समावेश "ipu-prv.h"

/*
 * The IC Resizer has a restriction that the output frame from the
 * resizer must be 1024 or less in both width (pixels) and height
 * (lines).
 *
 * The image converter attempts to split up a conversion when
 * the desired output (converted) frame resolution exceeds the
 * IC resizer limit of 1024 in either dimension.
 *
 * If either dimension of the output frame exceeds the limit, the
 * dimension is split पूर्णांकo 1, 2, or 4 equal stripes, क्रम a maximum
 * of 4*4 or 16 tiles. A conversion is then carried out क्रम each
 * tile (but taking care to pass the full frame stride length to
 * the DMA channel's parameter memory!). IDMA द्विगुन-buffering is used
 * to convert each tile back-to-back when possible (see note below
 * when द्विगुन_buffering boolean is set).
 *
 * Note that the input frame must be split up पूर्णांकo the same number
 * of tiles as the output frame:
 *
 *                       +---------+-----+
 *   +-----+---+         |  A      | B   |
 *   | A   | B |         |         |     |
 *   +-----+---+   -->   +---------+-----+
 *   | C   | D |         |  C      | D   |
 *   +-----+---+         |         |     |
 *                       +---------+-----+
 *
 * Clockwise 90तओ rotations are handled by first rescaling पूर्णांकo a
 * reusable temporary tile buffer and then rotating with the 8x8
 * block rotator, writing to the correct destination:
 *
 *                                         +-----+-----+
 *                                         |     |     |
 *   +-----+---+         +---------+       | C   | A   |
 *   | A   | B |         | A,B, |  |       |     |     |
 *   +-----+---+   -->   | C,D  |  |  -->  |     |     |
 *   | C   | D |         +---------+       +-----+-----+
 *   +-----+---+                           | D   | B   |
 *                                         |     |     |
 *                                         +-----+-----+
 *
 * If the 8x8 block rotator is used, horizontal or vertical flipping
 * is करोne during the rotation step, otherwise flipping is करोne
 * during the scaling step.
 * With rotation or flipping, tile order changes between input and
 * output image. Tiles are numbered row major from top left to bottom
 * right क्रम both input and output image.
 */

#घोषणा MAX_STRIPES_W    4
#घोषणा MAX_STRIPES_H    4
#घोषणा MAX_TILES (MAX_STRIPES_W * MAX_STRIPES_H)

#घोषणा MIN_W     16
#घोषणा MIN_H     8
#घोषणा MAX_W     4096
#घोषणा MAX_H     4096

क्रमागत ipu_image_convert_type अणु
	IMAGE_CONVERT_IN = 0,
	IMAGE_CONVERT_OUT,
पूर्ण;

काष्ठा ipu_image_convert_dma_buf अणु
	व्योम          *virt;
	dma_addr_t    phys;
	अचिन्हित दीर्घ len;
पूर्ण;

काष्ठा ipu_image_convert_dma_chan अणु
	पूर्णांक in;
	पूर्णांक out;
	पूर्णांक rot_in;
	पूर्णांक rot_out;
	पूर्णांक vdi_in_p;
	पूर्णांक vdi_in;
	पूर्णांक vdi_in_n;
पूर्ण;

/* dimensions of one tile */
काष्ठा ipu_image_tile अणु
	u32 width;
	u32 height;
	u32 left;
	u32 top;
	/* size and strides are in bytes */
	u32 size;
	u32 stride;
	u32 rot_stride;
	/* start Y or packed offset of this tile */
	u32 offset;
	/* offset from start to tile in U plane, क्रम planar क्रमmats */
	u32 u_off;
	/* offset from start to tile in V plane, क्रम planar क्रमmats */
	u32 v_off;
पूर्ण;

काष्ठा ipu_image_convert_image अणु
	काष्ठा ipu_image base;
	क्रमागत ipu_image_convert_type type;

	स्थिर काष्ठा ipu_image_pixfmt *fmt;
	अचिन्हित पूर्णांक stride;

	/* # of rows (horizontal stripes) अगर dest height is > 1024 */
	अचिन्हित पूर्णांक num_rows;
	/* # of columns (vertical stripes) अगर dest width is > 1024 */
	अचिन्हित पूर्णांक num_cols;

	काष्ठा ipu_image_tile tile[MAX_TILES];
पूर्ण;

काष्ठा ipu_image_pixfmt अणु
	u32	fourcc;        /* V4L2 fourcc */
	पूर्णांक     bpp;           /* total bpp */
	पूर्णांक     uv_width_dec;  /* decimation in width क्रम U/V planes */
	पूर्णांक     uv_height_dec; /* decimation in height क्रम U/V planes */
	bool    planar;        /* planar क्रमmat */
	bool    uv_swapped;    /* U and V planes are swapped */
	bool    uv_packed;     /* partial planar (U and V in same plane) */
पूर्ण;

काष्ठा ipu_image_convert_ctx;
काष्ठा ipu_image_convert_chan;
काष्ठा ipu_image_convert_priv;

क्रमागत eof_irq_mask अणु
	खातापूर्ण_IRQ_IN      = BIT(0),
	खातापूर्ण_IRQ_ROT_IN  = BIT(1),
	खातापूर्ण_IRQ_OUT     = BIT(2),
	खातापूर्ण_IRQ_ROT_OUT = BIT(3),
पूर्ण;

#घोषणा खातापूर्ण_IRQ_COMPLETE (खातापूर्ण_IRQ_IN | खातापूर्ण_IRQ_OUT)
#घोषणा खातापूर्ण_IRQ_ROT_COMPLETE (खातापूर्ण_IRQ_IN | खातापूर्ण_IRQ_OUT |	\
			      खातापूर्ण_IRQ_ROT_IN | खातापूर्ण_IRQ_ROT_OUT)

काष्ठा ipu_image_convert_ctx अणु
	काष्ठा ipu_image_convert_chan *chan;

	ipu_image_convert_cb_t complete;
	व्योम *complete_context;

	/* Source/destination image data and rotation mode */
	काष्ठा ipu_image_convert_image in;
	काष्ठा ipu_image_convert_image out;
	काष्ठा ipu_ic_csc csc;
	क्रमागत ipu_rotate_mode rot_mode;
	u32 करोwnsize_coeff_h;
	u32 करोwnsize_coeff_v;
	u32 image_resize_coeff_h;
	u32 image_resize_coeff_v;
	u32 resize_coeffs_h[MAX_STRIPES_W];
	u32 resize_coeffs_v[MAX_STRIPES_H];

	/* पूर्णांकermediate buffer क्रम rotation */
	काष्ठा ipu_image_convert_dma_buf rot_पूर्णांकermediate[2];

	/* current buffer number क्रम द्विगुन buffering */
	पूर्णांक cur_buf_num;

	bool पातing;
	काष्ठा completion पातed;

	/* can we use द्विगुन-buffering क्रम this conversion operation? */
	bool द्विगुन_buffering;
	/* num_rows * num_cols */
	अचिन्हित पूर्णांक num_tiles;
	/* next tile to process */
	अचिन्हित पूर्णांक next_tile;
	/* where to place converted tile in dest image */
	अचिन्हित पूर्णांक out_tile_map[MAX_TILES];

	/* mask of completed खातापूर्ण irqs at every tile conversion */
	क्रमागत eof_irq_mask eof_mask;

	काष्ठा list_head list;
पूर्ण;

काष्ठा ipu_image_convert_chan अणु
	काष्ठा ipu_image_convert_priv *priv;

	क्रमागत ipu_ic_task ic_task;
	स्थिर काष्ठा ipu_image_convert_dma_chan *dma_ch;

	काष्ठा ipu_ic *ic;
	काष्ठा ipuv3_channel *in_chan;
	काष्ठा ipuv3_channel *out_chan;
	काष्ठा ipuv3_channel *rotation_in_chan;
	काष्ठा ipuv3_channel *rotation_out_chan;

	/* the IPU end-of-frame irqs */
	पूर्णांक in_eof_irq;
	पूर्णांक rot_in_eof_irq;
	पूर्णांक out_eof_irq;
	पूर्णांक rot_out_eof_irq;

	spinlock_t irqlock;

	/* list of convert contexts */
	काष्ठा list_head ctx_list;
	/* queue of conversion runs */
	काष्ठा list_head pending_q;
	/* queue of completed runs */
	काष्ठा list_head करोne_q;

	/* the current conversion run */
	काष्ठा ipu_image_convert_run *current_run;
पूर्ण;

काष्ठा ipu_image_convert_priv अणु
	काष्ठा ipu_image_convert_chan chan[IC_NUM_TASKS];
	काष्ठा ipu_soc *ipu;
पूर्ण;

अटल स्थिर काष्ठा ipu_image_convert_dma_chan
image_convert_dma_chan[IC_NUM_TASKS] = अणु
	[IC_TASK_VIEWFINDER] = अणु
		.in = IPUV3_CHANNEL_MEM_IC_PRP_VF,
		.out = IPUV3_CHANNEL_IC_PRP_VF_MEM,
		.rot_in = IPUV3_CHANNEL_MEM_ROT_VF,
		.rot_out = IPUV3_CHANNEL_ROT_VF_MEM,
		.vdi_in_p = IPUV3_CHANNEL_MEM_VDI_PREV,
		.vdi_in = IPUV3_CHANNEL_MEM_VDI_CUR,
		.vdi_in_n = IPUV3_CHANNEL_MEM_VDI_NEXT,
	पूर्ण,
	[IC_TASK_POST_PROCESSOR] = अणु
		.in = IPUV3_CHANNEL_MEM_IC_PP,
		.out = IPUV3_CHANNEL_IC_PP_MEM,
		.rot_in = IPUV3_CHANNEL_MEM_ROT_PP,
		.rot_out = IPUV3_CHANNEL_ROT_PP_MEM,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ipu_image_pixfmt image_convert_क्रमmats[] = अणु
	अणु
		.fourcc	= V4L2_PIX_FMT_RGB565,
		.bpp    = 16,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_RGB24,
		.bpp    = 24,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_BGR24,
		.bpp    = 24,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_RGB32,
		.bpp    = 32,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_BGR32,
		.bpp    = 32,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_XRGB32,
		.bpp    = 32,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_XBGR32,
		.bpp    = 32,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_BGRX32,
		.bpp    = 32,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_RGBX32,
		.bpp    = 32,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_YUYV,
		.bpp    = 16,
		.uv_width_dec = 2,
		.uv_height_dec = 1,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_UYVY,
		.bpp    = 16,
		.uv_width_dec = 2,
		.uv_height_dec = 1,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_YUV420,
		.bpp    = 12,
		.planar = true,
		.uv_width_dec = 2,
		.uv_height_dec = 2,
	पूर्ण, अणु
		.fourcc	= V4L2_PIX_FMT_YVU420,
		.bpp    = 12,
		.planar = true,
		.uv_width_dec = 2,
		.uv_height_dec = 2,
		.uv_swapped = true,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_NV12,
		.bpp    = 12,
		.planar = true,
		.uv_width_dec = 2,
		.uv_height_dec = 2,
		.uv_packed = true,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_YUV422P,
		.bpp    = 16,
		.planar = true,
		.uv_width_dec = 2,
		.uv_height_dec = 1,
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_NV16,
		.bpp    = 16,
		.planar = true,
		.uv_width_dec = 2,
		.uv_height_dec = 1,
		.uv_packed = true,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ipu_image_pixfmt *get_क्रमmat(u32 fourcc)
अणु
	स्थिर काष्ठा ipu_image_pixfmt *ret = शून्य;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(image_convert_क्रमmats); i++) अणु
		अगर (image_convert_क्रमmats[i].fourcc == fourcc) अणु
			ret = &image_convert_क्रमmats[i];
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम dump_क्रमmat(काष्ठा ipu_image_convert_ctx *ctx,
			काष्ठा ipu_image_convert_image *ic_image)
अणु
	काष्ठा ipu_image_convert_chan *chan = ctx->chan;
	काष्ठा ipu_image_convert_priv *priv = chan->priv;

	dev_dbg(priv->ipu->dev,
		"task %u: ctx %p: %s format: %dx%d (%dx%d tiles), %c%c%c%c\n",
		chan->ic_task, ctx,
		ic_image->type == IMAGE_CONVERT_OUT ? "Output" : "Input",
		ic_image->base.pix.width, ic_image->base.pix.height,
		ic_image->num_cols, ic_image->num_rows,
		ic_image->fmt->fourcc & 0xff,
		(ic_image->fmt->fourcc >> 8) & 0xff,
		(ic_image->fmt->fourcc >> 16) & 0xff,
		(ic_image->fmt->fourcc >> 24) & 0xff);
पूर्ण

पूर्णांक ipu_image_convert_क्रमागत_क्रमmat(पूर्णांक index, u32 *fourcc)
अणु
	स्थिर काष्ठा ipu_image_pixfmt *fmt;

	अगर (index >= (पूर्णांक)ARRAY_SIZE(image_convert_क्रमmats))
		वापस -EINVAL;

	/* Format found */
	fmt = &image_convert_क्रमmats[index];
	*fourcc = fmt->fourcc;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_image_convert_क्रमागत_क्रमmat);

अटल व्योम मुक्त_dma_buf(काष्ठा ipu_image_convert_priv *priv,
			 काष्ठा ipu_image_convert_dma_buf *buf)
अणु
	अगर (buf->virt)
		dma_मुक्त_coherent(priv->ipu->dev,
				  buf->len, buf->virt, buf->phys);
	buf->virt = शून्य;
	buf->phys = 0;
पूर्ण

अटल पूर्णांक alloc_dma_buf(काष्ठा ipu_image_convert_priv *priv,
			 काष्ठा ipu_image_convert_dma_buf *buf,
			 पूर्णांक size)
अणु
	buf->len = PAGE_ALIGN(size);
	buf->virt = dma_alloc_coherent(priv->ipu->dev, buf->len, &buf->phys,
				       GFP_DMA | GFP_KERNEL);
	अगर (!buf->virt) अणु
		dev_err(priv->ipu->dev, "failed to alloc dma buffer\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक num_stripes(पूर्णांक dim)
अणु
	वापस (dim - 1) / 1024 + 1;
पूर्ण

/*
 * Calculate करोwnsizing coefficients, which are the same क्रम all tiles,
 * and initial bilinear resizing coefficients, which are used to find the
 * best seam positions.
 * Also determine the number of tiles necessary to guarantee that no tile
 * is larger than 1024 pixels in either dimension at the output and between
 * IC करोwnsizing and मुख्य processing sections.
 */
अटल पूर्णांक calc_image_resize_coefficients(काष्ठा ipu_image_convert_ctx *ctx,
					  काष्ठा ipu_image *in,
					  काष्ठा ipu_image *out)
अणु
	u32 करोwnsized_width = in->rect.width;
	u32 करोwnsized_height = in->rect.height;
	u32 करोwnsize_coeff_v = 0;
	u32 करोwnsize_coeff_h = 0;
	u32 resized_width = out->rect.width;
	u32 resized_height = out->rect.height;
	u32 resize_coeff_h;
	u32 resize_coeff_v;
	u32 cols;
	u32 rows;

	अगर (ipu_rot_mode_is_irt(ctx->rot_mode)) अणु
		resized_width = out->rect.height;
		resized_height = out->rect.width;
	पूर्ण

	/* Do not let invalid input lead to an endless loop below */
	अगर (WARN_ON(resized_width == 0 || resized_height == 0))
		वापस -EINVAL;

	जबतक (करोwnsized_width >= resized_width * 2) अणु
		करोwnsized_width >>= 1;
		करोwnsize_coeff_h++;
	पूर्ण

	जबतक (करोwnsized_height >= resized_height * 2) अणु
		करोwnsized_height >>= 1;
		करोwnsize_coeff_v++;
	पूर्ण

	/*
	 * Calculate the bilinear resizing coefficients that could be used अगर
	 * we were converting with a single tile. The bottom right output pixel
	 * should sample as बंद as possible to the bottom right input pixel
	 * out of the decimator, but not overshoot it:
	 */
	resize_coeff_h = 8192 * (करोwnsized_width - 1) / (resized_width - 1);
	resize_coeff_v = 8192 * (करोwnsized_height - 1) / (resized_height - 1);

	/*
	 * Both the output of the IC करोwnsizing section beक्रमe being passed to
	 * the IC मुख्य processing section and the final output of the IC मुख्य
	 * processing section must be <= 1024 pixels in both dimensions.
	 */
	cols = num_stripes(max_t(u32, करोwnsized_width, resized_width));
	rows = num_stripes(max_t(u32, करोwnsized_height, resized_height));

	dev_dbg(ctx->chan->priv->ipu->dev,
		"%s: hscale: >>%u, *8192/%u vscale: >>%u, *8192/%u, %ux%u tiles\n",
		__func__, करोwnsize_coeff_h, resize_coeff_h, करोwnsize_coeff_v,
		resize_coeff_v, cols, rows);

	अगर (करोwnsize_coeff_h > 2 || करोwnsize_coeff_v  > 2 ||
	    resize_coeff_h > 0x3fff || resize_coeff_v > 0x3fff)
		वापस -EINVAL;

	ctx->करोwnsize_coeff_h = करोwnsize_coeff_h;
	ctx->करोwnsize_coeff_v = करोwnsize_coeff_v;
	ctx->image_resize_coeff_h = resize_coeff_h;
	ctx->image_resize_coeff_v = resize_coeff_v;
	ctx->in.num_cols = cols;
	ctx->in.num_rows = rows;

	वापस 0;
पूर्ण

#घोषणा round_बंदst(x, y) round_करोwn((x) + (y)/2, (y))

/*
 * Find the best aligned seam position क्रम the given column / row index.
 * Rotation and image offsets are out of scope.
 *
 * @index: column / row index, used to calculate valid पूर्णांकerval
 * @in_edge: input right / bottom edge
 * @out_edge: output right / bottom edge
 * @in_align: input alignment, either horizontal 8-byte line start address
 *            alignment, or pixel alignment due to image क्रमmat
 * @out_align: output alignment, either horizontal 8-byte line start address
 *             alignment, or pixel alignment due to image क्रमmat or rotator
 *             block size
 * @in_burst: horizontal input burst size in हाल of horizontal flip
 * @out_burst: horizontal output burst size or rotator block size
 * @करोwnsize_coeff: करोwnsizing section coefficient
 * @resize_coeff: मुख्य processing section resizing coefficient
 * @_in_seam: aligned input seam position वापस value
 * @_out_seam: aligned output seam position वापस value
 */
अटल व्योम find_best_seam(काष्ठा ipu_image_convert_ctx *ctx,
			   अचिन्हित पूर्णांक index,
			   अचिन्हित पूर्णांक in_edge,
			   अचिन्हित पूर्णांक out_edge,
			   अचिन्हित पूर्णांक in_align,
			   अचिन्हित पूर्णांक out_align,
			   अचिन्हित पूर्णांक in_burst,
			   अचिन्हित पूर्णांक out_burst,
			   अचिन्हित पूर्णांक करोwnsize_coeff,
			   अचिन्हित पूर्णांक resize_coeff,
			   u32 *_in_seam,
			   u32 *_out_seam)
अणु
	काष्ठा device *dev = ctx->chan->priv->ipu->dev;
	अचिन्हित पूर्णांक out_pos;
	/* Input / output seam position candidates */
	अचिन्हित पूर्णांक out_seam = 0;
	अचिन्हित पूर्णांक in_seam = 0;
	अचिन्हित पूर्णांक min_dअगरf = अच_पूर्णांक_उच्च;
	अचिन्हित पूर्णांक out_start;
	अचिन्हित पूर्णांक out_end;
	अचिन्हित पूर्णांक in_start;
	अचिन्हित पूर्णांक in_end;

	/* Start within 1024 pixels of the right / bottom edge */
	out_start = max_t(पूर्णांक, index * out_align, out_edge - 1024);
	/* End beक्रमe having to add more columns to the left / rows above */
	out_end = min_t(अचिन्हित पूर्णांक, out_edge, index * 1024 + 1);

	/*
	 * Limit input seam position to make sure that the करोwnsized input tile
	 * to the right or bottom करोes not exceed 1024 pixels.
	 */
	in_start = max_t(पूर्णांक, index * in_align,
			 in_edge - (1024 << करोwnsize_coeff));
	in_end = min_t(अचिन्हित पूर्णांक, in_edge,
		       index * (1024 << करोwnsize_coeff) + 1);

	/*
	 * Output tiles must start at a multiple of 8 bytes horizontally and
	 * possibly at an even line horizontally depending on the pixel क्रमmat.
	 * Only consider output aligned positions क्रम the seam.
	 */
	out_start = round_up(out_start, out_align);
	क्रम (out_pos = out_start; out_pos < out_end; out_pos += out_align) अणु
		अचिन्हित पूर्णांक in_pos;
		अचिन्हित पूर्णांक in_pos_aligned;
		अचिन्हित पूर्णांक in_pos_rounded;
		अचिन्हित पूर्णांक असल_dअगरf;

		/*
		 * Tiles in the right row / bottom column may not be allowed to
		 * overshoot horizontally / vertically. out_burst may be the
		 * actual DMA burst size, or the rotator block size.
		 */
		अगर ((out_burst > 1) && (out_edge - out_pos) % out_burst)
			जारी;

		/*
		 * Input sample position, corresponding to out_pos, 19.13 fixed
		 * poपूर्णांक.
		 */
		in_pos = (out_pos * resize_coeff) << करोwnsize_coeff;
		/*
		 * The बंदst input sample position that we could actually
		 * start the input tile at, 19.13 fixed poपूर्णांक.
		 */
		in_pos_aligned = round_बंदst(in_pos, 8192U * in_align);
		/* Convert 19.13 fixed poपूर्णांक to पूर्णांकeger */
		in_pos_rounded = in_pos_aligned / 8192U;

		अगर (in_pos_rounded < in_start)
			जारी;
		अगर (in_pos_rounded >= in_end)
			अवरोध;

		अगर ((in_burst > 1) &&
		    (in_edge - in_pos_rounded) % in_burst)
			जारी;

		अगर (in_pos < in_pos_aligned)
			असल_dअगरf = in_pos_aligned - in_pos;
		अन्यथा
			असल_dअगरf = in_pos - in_pos_aligned;

		अगर (असल_dअगरf < min_dअगरf) अणु
			in_seam = in_pos_rounded;
			out_seam = out_pos;
			min_dअगरf = असल_dअगरf;
		पूर्ण
	पूर्ण

	*_out_seam = out_seam;
	*_in_seam = in_seam;

	dev_dbg(dev, "%s: out_seam %u(%u) in [%u, %u], in_seam %u(%u) in [%u, %u] diff %u.%03u\n",
		__func__, out_seam, out_align, out_start, out_end,
		in_seam, in_align, in_start, in_end, min_dअगरf / 8192,
		DIV_ROUND_CLOSEST(min_dअगरf % 8192 * 1000, 8192));
पूर्ण

/*
 * Tile left edges are required to be aligned to multiples of 8 bytes
 * by the IDMAC.
 */
अटल अंतरभूत u32 tile_left_align(स्थिर काष्ठा ipu_image_pixfmt *fmt)
अणु
	अगर (fmt->planar)
		वापस fmt->uv_packed ? 8 : 8 * fmt->uv_width_dec;
	अन्यथा
		वापस fmt->bpp == 32 ? 2 : fmt->bpp == 16 ? 4 : 8;
पूर्ण

/*
 * Tile top edge alignment is only limited by chroma subsampling.
 */
अटल अंतरभूत u32 tile_top_align(स्थिर काष्ठा ipu_image_pixfmt *fmt)
अणु
	वापस fmt->uv_height_dec > 1 ? 2 : 1;
पूर्ण

अटल अंतरभूत u32 tile_width_align(क्रमागत ipu_image_convert_type type,
				   स्थिर काष्ठा ipu_image_pixfmt *fmt,
				   क्रमागत ipu_rotate_mode rot_mode)
अणु
	अगर (type == IMAGE_CONVERT_IN) अणु
		/*
		 * The IC burst पढ़ोs 8 pixels at a समय. Reading beyond the
		 * end of the line is usually acceptable. Those pixels are
		 * ignored, unless the IC has to ग_लिखो the scaled line in
		 * reverse.
		 */
		वापस (!ipu_rot_mode_is_irt(rot_mode) &&
			(rot_mode & IPU_ROT_BIT_HFLIP)) ? 8 : 2;
	पूर्ण

	/*
	 * Align to 16x16 pixel blocks क्रम planar 4:2:0 chroma subsampled
	 * क्रमmats to guarantee 8-byte aligned line start addresses in the
	 * chroma planes when IRT is used. Align to 8x8 pixel IRT block size
	 * क्रम all other क्रमmats.
	 */
	वापस (ipu_rot_mode_is_irt(rot_mode) &&
		fmt->planar && !fmt->uv_packed) ?
		8 * fmt->uv_width_dec : 8;
पूर्ण

अटल अंतरभूत u32 tile_height_align(क्रमागत ipu_image_convert_type type,
				    स्थिर काष्ठा ipu_image_pixfmt *fmt,
				    क्रमागत ipu_rotate_mode rot_mode)
अणु
	अगर (type == IMAGE_CONVERT_IN || !ipu_rot_mode_is_irt(rot_mode))
		वापस 2;

	/*
	 * Align to 16x16 pixel blocks क्रम planar 4:2:0 chroma subsampled
	 * क्रमmats to guarantee 8-byte aligned line start addresses in the
	 * chroma planes when IRT is used. Align to 8x8 pixel IRT block size
	 * क्रम all other क्रमmats.
	 */
	वापस (fmt->planar && !fmt->uv_packed) ? 8 * fmt->uv_width_dec : 8;
पूर्ण

/*
 * Fill in left position and width and क्रम all tiles in an input column, and
 * क्रम all corresponding output tiles. If the 90तओ rotator is used, the output
 * tiles are in a row, and output tile top position and height are set.
 */
अटल व्योम fill_tile_column(काष्ठा ipu_image_convert_ctx *ctx,
			     अचिन्हित पूर्णांक col,
			     काष्ठा ipu_image_convert_image *in,
			     अचिन्हित पूर्णांक in_left, अचिन्हित पूर्णांक in_width,
			     काष्ठा ipu_image_convert_image *out,
			     अचिन्हित पूर्णांक out_left, अचिन्हित पूर्णांक out_width)
अणु
	अचिन्हित पूर्णांक row, tile_idx;
	काष्ठा ipu_image_tile *in_tile, *out_tile;

	क्रम (row = 0; row < in->num_rows; row++) अणु
		tile_idx = in->num_cols * row + col;
		in_tile = &in->tile[tile_idx];
		out_tile = &out->tile[ctx->out_tile_map[tile_idx]];

		in_tile->left = in_left;
		in_tile->width = in_width;

		अगर (ipu_rot_mode_is_irt(ctx->rot_mode)) अणु
			out_tile->top = out_left;
			out_tile->height = out_width;
		पूर्ण अन्यथा अणु
			out_tile->left = out_left;
			out_tile->width = out_width;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Fill in top position and height and क्रम all tiles in an input row, and
 * क्रम all corresponding output tiles. If the 90तओ rotator is used, the output
 * tiles are in a column, and output tile left position and width are set.
 */
अटल व्योम fill_tile_row(काष्ठा ipu_image_convert_ctx *ctx, अचिन्हित पूर्णांक row,
			  काष्ठा ipu_image_convert_image *in,
			  अचिन्हित पूर्णांक in_top, अचिन्हित पूर्णांक in_height,
			  काष्ठा ipu_image_convert_image *out,
			  अचिन्हित पूर्णांक out_top, अचिन्हित पूर्णांक out_height)
अणु
	अचिन्हित पूर्णांक col, tile_idx;
	काष्ठा ipu_image_tile *in_tile, *out_tile;

	क्रम (col = 0; col < in->num_cols; col++) अणु
		tile_idx = in->num_cols * row + col;
		in_tile = &in->tile[tile_idx];
		out_tile = &out->tile[ctx->out_tile_map[tile_idx]];

		in_tile->top = in_top;
		in_tile->height = in_height;

		अगर (ipu_rot_mode_is_irt(ctx->rot_mode)) अणु
			out_tile->left = out_top;
			out_tile->width = out_height;
		पूर्ण अन्यथा अणु
			out_tile->top = out_top;
			out_tile->height = out_height;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Find the best horizontal and vertical seam positions to split पूर्णांकo tiles.
 * Minimize the fractional part of the input sampling position क्रम the
 * top / left pixels of each tile.
 */
अटल व्योम find_seams(काष्ठा ipu_image_convert_ctx *ctx,
		       काष्ठा ipu_image_convert_image *in,
		       काष्ठा ipu_image_convert_image *out)
अणु
	काष्ठा device *dev = ctx->chan->priv->ipu->dev;
	अचिन्हित पूर्णांक resized_width = out->base.rect.width;
	अचिन्हित पूर्णांक resized_height = out->base.rect.height;
	अचिन्हित पूर्णांक col;
	अचिन्हित पूर्णांक row;
	अचिन्हित पूर्णांक in_left_align = tile_left_align(in->fmt);
	अचिन्हित पूर्णांक in_top_align = tile_top_align(in->fmt);
	अचिन्हित पूर्णांक out_left_align = tile_left_align(out->fmt);
	अचिन्हित पूर्णांक out_top_align = tile_top_align(out->fmt);
	अचिन्हित पूर्णांक out_width_align = tile_width_align(out->type, out->fmt,
							ctx->rot_mode);
	अचिन्हित पूर्णांक out_height_align = tile_height_align(out->type, out->fmt,
							  ctx->rot_mode);
	अचिन्हित पूर्णांक in_right = in->base.rect.width;
	अचिन्हित पूर्णांक in_bottom = in->base.rect.height;
	अचिन्हित पूर्णांक out_right = out->base.rect.width;
	अचिन्हित पूर्णांक out_bottom = out->base.rect.height;
	अचिन्हित पूर्णांक flipped_out_left;
	अचिन्हित पूर्णांक flipped_out_top;

	अगर (ipu_rot_mode_is_irt(ctx->rot_mode)) अणु
		/* Switch width/height and align top left to IRT block size */
		resized_width = out->base.rect.height;
		resized_height = out->base.rect.width;
		out_left_align = out_height_align;
		out_top_align = out_width_align;
		out_width_align = out_left_align;
		out_height_align = out_top_align;
		out_right = out->base.rect.height;
		out_bottom = out->base.rect.width;
	पूर्ण

	क्रम (col = in->num_cols - 1; col > 0; col--) अणु
		bool allow_in_overshoot = ipu_rot_mode_is_irt(ctx->rot_mode) ||
					  !(ctx->rot_mode & IPU_ROT_BIT_HFLIP);
		bool allow_out_overshoot = (col < in->num_cols - 1) &&
					   !(ctx->rot_mode & IPU_ROT_BIT_HFLIP);
		अचिन्हित पूर्णांक in_left;
		अचिन्हित पूर्णांक out_left;

		/*
		 * Align input width to burst length अगर the scaling step flips
		 * horizontally.
		 */

		find_best_seam(ctx, col,
			       in_right, out_right,
			       in_left_align, out_left_align,
			       allow_in_overshoot ? 1 : 8 /* burst length */,
			       allow_out_overshoot ? 1 : out_width_align,
			       ctx->करोwnsize_coeff_h, ctx->image_resize_coeff_h,
			       &in_left, &out_left);

		अगर (ctx->rot_mode & IPU_ROT_BIT_HFLIP)
			flipped_out_left = resized_width - out_right;
		अन्यथा
			flipped_out_left = out_left;

		fill_tile_column(ctx, col, in, in_left, in_right - in_left,
				 out, flipped_out_left, out_right - out_left);

		dev_dbg(dev, "%s: col %u: %u, %u -> %u, %u\n", __func__, col,
			in_left, in_right - in_left,
			flipped_out_left, out_right - out_left);

		in_right = in_left;
		out_right = out_left;
	पूर्ण

	flipped_out_left = (ctx->rot_mode & IPU_ROT_BIT_HFLIP) ?
			   resized_width - out_right : 0;

	fill_tile_column(ctx, 0, in, 0, in_right,
			 out, flipped_out_left, out_right);

	dev_dbg(dev, "%s: col 0: 0, %u -> %u, %u\n", __func__,
		in_right, flipped_out_left, out_right);

	क्रम (row = in->num_rows - 1; row > 0; row--) अणु
		bool allow_overshoot = row < in->num_rows - 1;
		अचिन्हित पूर्णांक in_top;
		अचिन्हित पूर्णांक out_top;

		find_best_seam(ctx, row,
			       in_bottom, out_bottom,
			       in_top_align, out_top_align,
			       1, allow_overshoot ? 1 : out_height_align,
			       ctx->करोwnsize_coeff_v, ctx->image_resize_coeff_v,
			       &in_top, &out_top);

		अगर ((ctx->rot_mode & IPU_ROT_BIT_VFLIP) ^
		    ipu_rot_mode_is_irt(ctx->rot_mode))
			flipped_out_top = resized_height - out_bottom;
		अन्यथा
			flipped_out_top = out_top;

		fill_tile_row(ctx, row, in, in_top, in_bottom - in_top,
			      out, flipped_out_top, out_bottom - out_top);

		dev_dbg(dev, "%s: row %u: %u, %u -> %u, %u\n", __func__, row,
			in_top, in_bottom - in_top,
			flipped_out_top, out_bottom - out_top);

		in_bottom = in_top;
		out_bottom = out_top;
	पूर्ण

	अगर ((ctx->rot_mode & IPU_ROT_BIT_VFLIP) ^
	    ipu_rot_mode_is_irt(ctx->rot_mode))
		flipped_out_top = resized_height - out_bottom;
	अन्यथा
		flipped_out_top = 0;

	fill_tile_row(ctx, 0, in, 0, in_bottom,
		      out, flipped_out_top, out_bottom);

	dev_dbg(dev, "%s: row 0: 0, %u -> %u, %u\n", __func__,
		in_bottom, flipped_out_top, out_bottom);
पूर्ण

अटल पूर्णांक calc_tile_dimensions(काष्ठा ipu_image_convert_ctx *ctx,
				काष्ठा ipu_image_convert_image *image)
अणु
	काष्ठा ipu_image_convert_chan *chan = ctx->chan;
	काष्ठा ipu_image_convert_priv *priv = chan->priv;
	अचिन्हित पूर्णांक max_width = 1024;
	अचिन्हित पूर्णांक max_height = 1024;
	अचिन्हित पूर्णांक i;

	अगर (image->type == IMAGE_CONVERT_IN) अणु
		/* Up to 4096x4096 input tile size */
		max_width <<= ctx->करोwnsize_coeff_h;
		max_height <<= ctx->करोwnsize_coeff_v;
	पूर्ण

	क्रम (i = 0; i < ctx->num_tiles; i++) अणु
		काष्ठा ipu_image_tile *tile;
		स्थिर अचिन्हित पूर्णांक row = i / image->num_cols;
		स्थिर अचिन्हित पूर्णांक col = i % image->num_cols;

		अगर (image->type == IMAGE_CONVERT_OUT)
			tile = &image->tile[ctx->out_tile_map[i]];
		अन्यथा
			tile = &image->tile[i];

		tile->size = ((tile->height * image->fmt->bpp) >> 3) *
			tile->width;

		अगर (image->fmt->planar) अणु
			tile->stride = tile->width;
			tile->rot_stride = tile->height;
		पूर्ण अन्यथा अणु
			tile->stride =
				(image->fmt->bpp * tile->width) >> 3;
			tile->rot_stride =
				(image->fmt->bpp * tile->height) >> 3;
		पूर्ण

		dev_dbg(priv->ipu->dev,
			"task %u: ctx %p: %s@[%u,%u]: %ux%u@%u,%u\n",
			chan->ic_task, ctx,
			image->type == IMAGE_CONVERT_IN ? "Input" : "Output",
			row, col,
			tile->width, tile->height, tile->left, tile->top);

		अगर (!tile->width || tile->width > max_width ||
		    !tile->height || tile->height > max_height) अणु
			dev_err(priv->ipu->dev, "invalid %s tile size: %ux%u\n",
				image->type == IMAGE_CONVERT_IN ? "input" :
				"output", tile->width, tile->height);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Use the rotation transक्रमmation to find the tile coordinates
 * (row, col) of a tile in the destination frame that corresponds
 * to the given tile coordinates of a source frame. The destination
 * coordinate is then converted to a tile index.
 */
अटल पूर्णांक transक्रमm_tile_index(काष्ठा ipu_image_convert_ctx *ctx,
				पूर्णांक src_row, पूर्णांक src_col)
अणु
	काष्ठा ipu_image_convert_chan *chan = ctx->chan;
	काष्ठा ipu_image_convert_priv *priv = chan->priv;
	काष्ठा ipu_image_convert_image *s_image = &ctx->in;
	काष्ठा ipu_image_convert_image *d_image = &ctx->out;
	पूर्णांक dst_row, dst_col;

	/* with no rotation it's a 1:1 mapping */
	अगर (ctx->rot_mode == IPU_ROTATE_NONE)
		वापस src_row * s_image->num_cols + src_col;

	/*
	 * beक्रमe करोing the transक्रमm, first we have to translate
	 * source row,col क्रम an origin in the center of s_image
	 */
	src_row = src_row * 2 - (s_image->num_rows - 1);
	src_col = src_col * 2 - (s_image->num_cols - 1);

	/* करो the rotation transक्रमm */
	अगर (ctx->rot_mode & IPU_ROT_BIT_90) अणु
		dst_col = -src_row;
		dst_row = src_col;
	पूर्ण अन्यथा अणु
		dst_col = src_col;
		dst_row = src_row;
	पूर्ण

	/* apply flip */
	अगर (ctx->rot_mode & IPU_ROT_BIT_HFLIP)
		dst_col = -dst_col;
	अगर (ctx->rot_mode & IPU_ROT_BIT_VFLIP)
		dst_row = -dst_row;

	dev_dbg(priv->ipu->dev, "task %u: ctx %p: [%d,%d] --> [%d,%d]\n",
		chan->ic_task, ctx, src_col, src_row, dst_col, dst_row);

	/*
	 * finally translate dest row,col using an origin in upper
	 * left of d_image
	 */
	dst_row += d_image->num_rows - 1;
	dst_col += d_image->num_cols - 1;
	dst_row /= 2;
	dst_col /= 2;

	वापस dst_row * d_image->num_cols + dst_col;
पूर्ण

/*
 * Fill the out_tile_map[] with transक्रमmed destination tile indeces.
 */
अटल व्योम calc_out_tile_map(काष्ठा ipu_image_convert_ctx *ctx)
अणु
	काष्ठा ipu_image_convert_image *s_image = &ctx->in;
	अचिन्हित पूर्णांक row, col, tile = 0;

	क्रम (row = 0; row < s_image->num_rows; row++) अणु
		क्रम (col = 0; col < s_image->num_cols; col++) अणु
			ctx->out_tile_map[tile] =
				transक्रमm_tile_index(ctx, row, col);
			tile++;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक calc_tile_offsets_planar(काष्ठा ipu_image_convert_ctx *ctx,
				    काष्ठा ipu_image_convert_image *image)
अणु
	काष्ठा ipu_image_convert_chan *chan = ctx->chan;
	काष्ठा ipu_image_convert_priv *priv = chan->priv;
	स्थिर काष्ठा ipu_image_pixfmt *fmt = image->fmt;
	अचिन्हित पूर्णांक row, col, tile = 0;
	u32 H, top, y_stride, uv_stride;
	u32 uv_row_off, uv_col_off, uv_off, u_off, v_off, पंचांगp;
	u32 y_row_off, y_col_off, y_off;
	u32 y_size, uv_size;

	/* setup some convenience vars */
	H = image->base.pix.height;

	y_stride = image->stride;
	uv_stride = y_stride / fmt->uv_width_dec;
	अगर (fmt->uv_packed)
		uv_stride *= 2;

	y_size = H * y_stride;
	uv_size = y_size / (fmt->uv_width_dec * fmt->uv_height_dec);

	क्रम (row = 0; row < image->num_rows; row++) अणु
		top = image->tile[tile].top;
		y_row_off = top * y_stride;
		uv_row_off = (top * uv_stride) / fmt->uv_height_dec;

		क्रम (col = 0; col < image->num_cols; col++) अणु
			y_col_off = image->tile[tile].left;
			uv_col_off = y_col_off / fmt->uv_width_dec;
			अगर (fmt->uv_packed)
				uv_col_off *= 2;

			y_off = y_row_off + y_col_off;
			uv_off = uv_row_off + uv_col_off;

			u_off = y_size - y_off + uv_off;
			v_off = (fmt->uv_packed) ? 0 : u_off + uv_size;
			अगर (fmt->uv_swapped) अणु
				पंचांगp = u_off;
				u_off = v_off;
				v_off = पंचांगp;
			पूर्ण

			image->tile[tile].offset = y_off;
			image->tile[tile].u_off = u_off;
			image->tile[tile++].v_off = v_off;

			अगर ((y_off & 0x7) || (u_off & 0x7) || (v_off & 0x7)) अणु
				dev_err(priv->ipu->dev,
					"task %u: ctx %p: %s@[%d,%d]: "
					"y_off %08x, u_off %08x, v_off %08x\n",
					chan->ic_task, ctx,
					image->type == IMAGE_CONVERT_IN ?
					"Input" : "Output", row, col,
					y_off, u_off, v_off);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक calc_tile_offsets_packed(काष्ठा ipu_image_convert_ctx *ctx,
				    काष्ठा ipu_image_convert_image *image)
अणु
	काष्ठा ipu_image_convert_chan *chan = ctx->chan;
	काष्ठा ipu_image_convert_priv *priv = chan->priv;
	स्थिर काष्ठा ipu_image_pixfmt *fmt = image->fmt;
	अचिन्हित पूर्णांक row, col, tile = 0;
	u32 bpp, stride, offset;
	u32 row_off, col_off;

	/* setup some convenience vars */
	stride = image->stride;
	bpp = fmt->bpp;

	क्रम (row = 0; row < image->num_rows; row++) अणु
		row_off = image->tile[tile].top * stride;

		क्रम (col = 0; col < image->num_cols; col++) अणु
			col_off = (image->tile[tile].left * bpp) >> 3;

			offset = row_off + col_off;

			image->tile[tile].offset = offset;
			image->tile[tile].u_off = 0;
			image->tile[tile++].v_off = 0;

			अगर (offset & 0x7) अणु
				dev_err(priv->ipu->dev,
					"task %u: ctx %p: %s@[%d,%d]: "
					"phys %08x\n",
					chan->ic_task, ctx,
					image->type == IMAGE_CONVERT_IN ?
					"Input" : "Output", row, col,
					row_off + col_off);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक calc_tile_offsets(काष्ठा ipu_image_convert_ctx *ctx,
			      काष्ठा ipu_image_convert_image *image)
अणु
	अगर (image->fmt->planar)
		वापस calc_tile_offsets_planar(ctx, image);

	वापस calc_tile_offsets_packed(ctx, image);
पूर्ण

/*
 * Calculate the resizing ratio क्रम the IC मुख्य processing section given input
 * size, fixed करोwnsizing coefficient, and output size.
 * Either round to बंदst क्रम the next tile's first pixel to minimize seams
 * and distortion (क्रम all but right column / bottom row), or round करोwn to
 * aव्योम sampling beyond the edges of the input image क्रम this tile's last
 * pixel.
 * Returns the resizing coefficient, resizing ratio is 8192.0 / resize_coeff.
 */
अटल u32 calc_resize_coeff(u32 input_size, u32 करोwnsize_coeff,
			     u32 output_size, bool allow_overshoot)
अणु
	u32 करोwnsized = input_size >> करोwnsize_coeff;

	अगर (allow_overshoot)
		वापस DIV_ROUND_CLOSEST(8192 * करोwnsized, output_size);
	अन्यथा
		वापस 8192 * (करोwnsized - 1) / (output_size - 1);
पूर्ण

/*
 * Slightly modअगरy resize coefficients per tile to hide the bilinear
 * पूर्णांकerpolator reset at tile borders, shअगरting the right / bottom edge
 * by up to a half input pixel. This हटाओs noticeable seams between
 * tiles at higher upscaling factors.
 */
अटल व्योम calc_tile_resize_coefficients(काष्ठा ipu_image_convert_ctx *ctx)
अणु
	काष्ठा ipu_image_convert_chan *chan = ctx->chan;
	काष्ठा ipu_image_convert_priv *priv = chan->priv;
	काष्ठा ipu_image_tile *in_tile, *out_tile;
	अचिन्हित पूर्णांक col, row, tile_idx;
	अचिन्हित पूर्णांक last_output;

	क्रम (col = 0; col < ctx->in.num_cols; col++) अणु
		bool बंदst = (col < ctx->in.num_cols - 1) &&
			       !(ctx->rot_mode & IPU_ROT_BIT_HFLIP);
		u32 resized_width;
		u32 resize_coeff_h;
		u32 in_width;

		tile_idx = col;
		in_tile = &ctx->in.tile[tile_idx];
		out_tile = &ctx->out.tile[ctx->out_tile_map[tile_idx]];

		अगर (ipu_rot_mode_is_irt(ctx->rot_mode))
			resized_width = out_tile->height;
		अन्यथा
			resized_width = out_tile->width;

		resize_coeff_h = calc_resize_coeff(in_tile->width,
						   ctx->करोwnsize_coeff_h,
						   resized_width, बंदst);

		dev_dbg(priv->ipu->dev, "%s: column %u hscale: *8192/%u\n",
			__func__, col, resize_coeff_h);

		/*
		 * With the horizontal scaling factor known, round up resized
		 * width (output width or height) to burst size.
		 */
		resized_width = round_up(resized_width, 8);

		/*
		 * Calculate input width from the last accessed input pixel
		 * given resized width and scaling coefficients. Round up to
		 * burst size.
		 */
		last_output = resized_width - 1;
		अगर (बंदst && ((last_output * resize_coeff_h) % 8192))
			last_output++;
		in_width = round_up(
			(DIV_ROUND_UP(last_output * resize_coeff_h, 8192) + 1)
			<< ctx->करोwnsize_coeff_h, 8);

		क्रम (row = 0; row < ctx->in.num_rows; row++) अणु
			tile_idx = row * ctx->in.num_cols + col;
			in_tile = &ctx->in.tile[tile_idx];
			out_tile = &ctx->out.tile[ctx->out_tile_map[tile_idx]];

			अगर (ipu_rot_mode_is_irt(ctx->rot_mode))
				out_tile->height = resized_width;
			अन्यथा
				out_tile->width = resized_width;

			in_tile->width = in_width;
		पूर्ण

		ctx->resize_coeffs_h[col] = resize_coeff_h;
	पूर्ण

	क्रम (row = 0; row < ctx->in.num_rows; row++) अणु
		bool बंदst = (row < ctx->in.num_rows - 1) &&
			       !(ctx->rot_mode & IPU_ROT_BIT_VFLIP);
		u32 resized_height;
		u32 resize_coeff_v;
		u32 in_height;

		tile_idx = row * ctx->in.num_cols;
		in_tile = &ctx->in.tile[tile_idx];
		out_tile = &ctx->out.tile[ctx->out_tile_map[tile_idx]];

		अगर (ipu_rot_mode_is_irt(ctx->rot_mode))
			resized_height = out_tile->width;
		अन्यथा
			resized_height = out_tile->height;

		resize_coeff_v = calc_resize_coeff(in_tile->height,
						   ctx->करोwnsize_coeff_v,
						   resized_height, बंदst);

		dev_dbg(priv->ipu->dev, "%s: row %u vscale: *8192/%u\n",
			__func__, row, resize_coeff_v);

		/*
		 * With the vertical scaling factor known, round up resized
		 * height (output width or height) to IDMAC limitations.
		 */
		resized_height = round_up(resized_height, 2);

		/*
		 * Calculate input width from the last accessed input pixel
		 * given resized height and scaling coefficients. Align to
		 * IDMAC restrictions.
		 */
		last_output = resized_height - 1;
		अगर (बंदst && ((last_output * resize_coeff_v) % 8192))
			last_output++;
		in_height = round_up(
			(DIV_ROUND_UP(last_output * resize_coeff_v, 8192) + 1)
			<< ctx->करोwnsize_coeff_v, 2);

		क्रम (col = 0; col < ctx->in.num_cols; col++) अणु
			tile_idx = row * ctx->in.num_cols + col;
			in_tile = &ctx->in.tile[tile_idx];
			out_tile = &ctx->out.tile[ctx->out_tile_map[tile_idx]];

			अगर (ipu_rot_mode_is_irt(ctx->rot_mode))
				out_tile->width = resized_height;
			अन्यथा
				out_tile->height = resized_height;

			in_tile->height = in_height;
		पूर्ण

		ctx->resize_coeffs_v[row] = resize_coeff_v;
	पूर्ण
पूर्ण

/*
 * वापस the number of runs in given queue (pending_q or करोne_q)
 * क्रम this context. hold irqlock when calling.
 */
अटल पूर्णांक get_run_count(काष्ठा ipu_image_convert_ctx *ctx,
			 काष्ठा list_head *q)
अणु
	काष्ठा ipu_image_convert_run *run;
	पूर्णांक count = 0;

	lockdep_निश्चित_held(&ctx->chan->irqlock);

	list_क्रम_each_entry(run, q, list) अणु
		अगर (run->ctx == ctx)
			count++;
	पूर्ण

	वापस count;
पूर्ण

अटल व्योम convert_stop(काष्ठा ipu_image_convert_run *run)
अणु
	काष्ठा ipu_image_convert_ctx *ctx = run->ctx;
	काष्ठा ipu_image_convert_chan *chan = ctx->chan;
	काष्ठा ipu_image_convert_priv *priv = chan->priv;

	dev_dbg(priv->ipu->dev, "%s: task %u: stopping ctx %p run %p\n",
		__func__, chan->ic_task, ctx, run);

	/* disable IC tasks and the channels */
	ipu_ic_task_disable(chan->ic);
	ipu_idmac_disable_channel(chan->in_chan);
	ipu_idmac_disable_channel(chan->out_chan);

	अगर (ipu_rot_mode_is_irt(ctx->rot_mode)) अणु
		ipu_idmac_disable_channel(chan->rotation_in_chan);
		ipu_idmac_disable_channel(chan->rotation_out_chan);
		ipu_idmac_unlink(chan->out_chan, chan->rotation_in_chan);
	पूर्ण

	ipu_ic_disable(chan->ic);
पूर्ण

अटल व्योम init_idmac_channel(काष्ठा ipu_image_convert_ctx *ctx,
			       काष्ठा ipuv3_channel *channel,
			       काष्ठा ipu_image_convert_image *image,
			       क्रमागत ipu_rotate_mode rot_mode,
			       bool rot_swap_width_height,
			       अचिन्हित पूर्णांक tile)
अणु
	काष्ठा ipu_image_convert_chan *chan = ctx->chan;
	अचिन्हित पूर्णांक burst_size;
	u32 width, height, stride;
	dma_addr_t addr0, addr1 = 0;
	काष्ठा ipu_image tile_image;
	अचिन्हित पूर्णांक tile_idx[2];

	अगर (image->type == IMAGE_CONVERT_OUT) अणु
		tile_idx[0] = ctx->out_tile_map[tile];
		tile_idx[1] = ctx->out_tile_map[1];
	पूर्ण अन्यथा अणु
		tile_idx[0] = tile;
		tile_idx[1] = 1;
	पूर्ण

	अगर (rot_swap_width_height) अणु
		width = image->tile[tile_idx[0]].height;
		height = image->tile[tile_idx[0]].width;
		stride = image->tile[tile_idx[0]].rot_stride;
		addr0 = ctx->rot_पूर्णांकermediate[0].phys;
		अगर (ctx->द्विगुन_buffering)
			addr1 = ctx->rot_पूर्णांकermediate[1].phys;
	पूर्ण अन्यथा अणु
		width = image->tile[tile_idx[0]].width;
		height = image->tile[tile_idx[0]].height;
		stride = image->stride;
		addr0 = image->base.phys0 +
			image->tile[tile_idx[0]].offset;
		अगर (ctx->द्विगुन_buffering)
			addr1 = image->base.phys0 +
				image->tile[tile_idx[1]].offset;
	पूर्ण

	ipu_cpmem_zero(channel);

	स_रखो(&tile_image, 0, माप(tile_image));
	tile_image.pix.width = tile_image.rect.width = width;
	tile_image.pix.height = tile_image.rect.height = height;
	tile_image.pix.bytesperline = stride;
	tile_image.pix.pixelक्रमmat =  image->fmt->fourcc;
	tile_image.phys0 = addr0;
	tile_image.phys1 = addr1;
	अगर (image->fmt->planar && !rot_swap_width_height) अणु
		tile_image.u_offset = image->tile[tile_idx[0]].u_off;
		tile_image.v_offset = image->tile[tile_idx[0]].v_off;
	पूर्ण

	ipu_cpmem_set_image(channel, &tile_image);

	अगर (rot_mode)
		ipu_cpmem_set_rotation(channel, rot_mode);

	/*
	 * Skip writing U and V components to odd rows in the output
	 * channels क्रम planar 4:2:0.
	 */
	अगर ((channel == chan->out_chan ||
	     channel == chan->rotation_out_chan) &&
	    image->fmt->planar && image->fmt->uv_height_dec == 2)
		ipu_cpmem_skip_odd_chroma_rows(channel);

	अगर (channel == chan->rotation_in_chan ||
	    channel == chan->rotation_out_chan) अणु
		burst_size = 8;
		ipu_cpmem_set_block_mode(channel);
	पूर्ण अन्यथा
		burst_size = (width % 16) ? 8 : 16;

	ipu_cpmem_set_burstsize(channel, burst_size);

	ipu_ic_task_idma_init(chan->ic, channel, width, height,
			      burst_size, rot_mode);

	/*
	 * Setting a non-zero AXI ID collides with the PRG AXI snooping, so
	 * only करो this when there is no PRG present.
	 */
	अगर (!channel->ipu->prg_priv)
		ipu_cpmem_set_axi_id(channel, 1);

	ipu_idmac_set_द्विगुन_buffer(channel, ctx->द्विगुन_buffering);
पूर्ण

अटल पूर्णांक convert_start(काष्ठा ipu_image_convert_run *run, अचिन्हित पूर्णांक tile)
अणु
	काष्ठा ipu_image_convert_ctx *ctx = run->ctx;
	काष्ठा ipu_image_convert_chan *chan = ctx->chan;
	काष्ठा ipu_image_convert_priv *priv = chan->priv;
	काष्ठा ipu_image_convert_image *s_image = &ctx->in;
	काष्ठा ipu_image_convert_image *d_image = &ctx->out;
	अचिन्हित पूर्णांक dst_tile = ctx->out_tile_map[tile];
	अचिन्हित पूर्णांक dest_width, dest_height;
	अचिन्हित पूर्णांक col, row;
	u32 rsc;
	पूर्णांक ret;

	dev_dbg(priv->ipu->dev, "%s: task %u: starting ctx %p run %p tile %u -> %u\n",
		__func__, chan->ic_task, ctx, run, tile, dst_tile);

	/* clear खातापूर्ण irq mask */
	ctx->eof_mask = 0;

	अगर (ipu_rot_mode_is_irt(ctx->rot_mode)) अणु
		/* swap width/height क्रम resizer */
		dest_width = d_image->tile[dst_tile].height;
		dest_height = d_image->tile[dst_tile].width;
	पूर्ण अन्यथा अणु
		dest_width = d_image->tile[dst_tile].width;
		dest_height = d_image->tile[dst_tile].height;
	पूर्ण

	row = tile / s_image->num_cols;
	col = tile % s_image->num_cols;

	rsc =  (ctx->करोwnsize_coeff_v << 30) |
	       (ctx->resize_coeffs_v[row] << 16) |
	       (ctx->करोwnsize_coeff_h << 14) |
	       (ctx->resize_coeffs_h[col]);

	dev_dbg(priv->ipu->dev, "%s: %ux%u -> %ux%u (rsc = 0x%x)\n",
		__func__, s_image->tile[tile].width,
		s_image->tile[tile].height, dest_width, dest_height, rsc);

	/* setup the IC resizer and CSC */
	ret = ipu_ic_task_init_rsc(chan->ic, &ctx->csc,
				   s_image->tile[tile].width,
				   s_image->tile[tile].height,
				   dest_width,
				   dest_height,
				   rsc);
	अगर (ret) अणु
		dev_err(priv->ipu->dev, "ipu_ic_task_init failed, %d\n", ret);
		वापस ret;
	पूर्ण

	/* init the source MEM-->IC PP IDMAC channel */
	init_idmac_channel(ctx, chan->in_chan, s_image,
			   IPU_ROTATE_NONE, false, tile);

	अगर (ipu_rot_mode_is_irt(ctx->rot_mode)) अणु
		/* init the IC PP-->MEM IDMAC channel */
		init_idmac_channel(ctx, chan->out_chan, d_image,
				   IPU_ROTATE_NONE, true, tile);

		/* init the MEM-->IC PP ROT IDMAC channel */
		init_idmac_channel(ctx, chan->rotation_in_chan, d_image,
				   ctx->rot_mode, true, tile);

		/* init the destination IC PP ROT-->MEM IDMAC channel */
		init_idmac_channel(ctx, chan->rotation_out_chan, d_image,
				   IPU_ROTATE_NONE, false, tile);

		/* now link IC PP-->MEM to MEM-->IC PP ROT */
		ipu_idmac_link(chan->out_chan, chan->rotation_in_chan);
	पूर्ण अन्यथा अणु
		/* init the destination IC PP-->MEM IDMAC channel */
		init_idmac_channel(ctx, chan->out_chan, d_image,
				   ctx->rot_mode, false, tile);
	पूर्ण

	/* enable the IC */
	ipu_ic_enable(chan->ic);

	/* set buffers पढ़ोy */
	ipu_idmac_select_buffer(chan->in_chan, 0);
	ipu_idmac_select_buffer(chan->out_chan, 0);
	अगर (ipu_rot_mode_is_irt(ctx->rot_mode))
		ipu_idmac_select_buffer(chan->rotation_out_chan, 0);
	अगर (ctx->द्विगुन_buffering) अणु
		ipu_idmac_select_buffer(chan->in_chan, 1);
		ipu_idmac_select_buffer(chan->out_chan, 1);
		अगर (ipu_rot_mode_is_irt(ctx->rot_mode))
			ipu_idmac_select_buffer(chan->rotation_out_chan, 1);
	पूर्ण

	/* enable the channels! */
	ipu_idmac_enable_channel(chan->in_chan);
	ipu_idmac_enable_channel(chan->out_chan);
	अगर (ipu_rot_mode_is_irt(ctx->rot_mode)) अणु
		ipu_idmac_enable_channel(chan->rotation_in_chan);
		ipu_idmac_enable_channel(chan->rotation_out_chan);
	पूर्ण

	ipu_ic_task_enable(chan->ic);

	ipu_cpmem_dump(chan->in_chan);
	ipu_cpmem_dump(chan->out_chan);
	अगर (ipu_rot_mode_is_irt(ctx->rot_mode)) अणु
		ipu_cpmem_dump(chan->rotation_in_chan);
		ipu_cpmem_dump(chan->rotation_out_chan);
	पूर्ण

	ipu_dump(priv->ipu);

	वापस 0;
पूर्ण

/* hold irqlock when calling */
अटल पूर्णांक करो_run(काष्ठा ipu_image_convert_run *run)
अणु
	काष्ठा ipu_image_convert_ctx *ctx = run->ctx;
	काष्ठा ipu_image_convert_chan *chan = ctx->chan;

	lockdep_निश्चित_held(&chan->irqlock);

	ctx->in.base.phys0 = run->in_phys;
	ctx->out.base.phys0 = run->out_phys;

	ctx->cur_buf_num = 0;
	ctx->next_tile = 1;

	/* हटाओ run from pending_q and set as current */
	list_del(&run->list);
	chan->current_run = run;

	वापस convert_start(run, 0);
पूर्ण

/* hold irqlock when calling */
अटल व्योम run_next(काष्ठा ipu_image_convert_chan *chan)
अणु
	काष्ठा ipu_image_convert_priv *priv = chan->priv;
	काष्ठा ipu_image_convert_run *run, *पंचांगp;
	पूर्णांक ret;

	lockdep_निश्चित_held(&chan->irqlock);

	list_क्रम_each_entry_safe(run, पंचांगp, &chan->pending_q, list) अणु
		/* skip contexts that are पातing */
		अगर (run->ctx->पातing) अणु
			dev_dbg(priv->ipu->dev,
				"%s: task %u: skipping aborting ctx %p run %p\n",
				__func__, chan->ic_task, run->ctx, run);
			जारी;
		पूर्ण

		ret = करो_run(run);
		अगर (!ret)
			अवरोध;

		/*
		 * something went wrong with start, add the run
		 * to करोne q and जारी to the next run in the
		 * pending q.
		 */
		run->status = ret;
		list_add_tail(&run->list, &chan->करोne_q);
		chan->current_run = शून्य;
	पूर्ण
पूर्ण

अटल व्योम empty_करोne_q(काष्ठा ipu_image_convert_chan *chan)
अणु
	काष्ठा ipu_image_convert_priv *priv = chan->priv;
	काष्ठा ipu_image_convert_run *run;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->irqlock, flags);

	जबतक (!list_empty(&chan->करोne_q)) अणु
		run = list_entry(chan->करोne_q.next,
				 काष्ठा ipu_image_convert_run,
				 list);

		list_del(&run->list);

		dev_dbg(priv->ipu->dev,
			"%s: task %u: completing ctx %p run %p with %d\n",
			__func__, chan->ic_task, run->ctx, run, run->status);

		/* call the completion callback and मुक्त the run */
		spin_unlock_irqrestore(&chan->irqlock, flags);
		run->ctx->complete(run, run->ctx->complete_context);
		spin_lock_irqsave(&chan->irqlock, flags);
	पूर्ण

	spin_unlock_irqrestore(&chan->irqlock, flags);
पूर्ण

/*
 * the bottom half thपढ़ो clears out the करोne_q, calling the
 * completion handler क्रम each.
 */
अटल irqवापस_t करो_bh(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ipu_image_convert_chan *chan = dev_id;
	काष्ठा ipu_image_convert_priv *priv = chan->priv;
	काष्ठा ipu_image_convert_ctx *ctx;
	अचिन्हित दीर्घ flags;

	dev_dbg(priv->ipu->dev, "%s: task %u: enter\n", __func__,
		chan->ic_task);

	empty_करोne_q(chan);

	spin_lock_irqsave(&chan->irqlock, flags);

	/*
	 * the करोne_q is cleared out, संकेत any contexts
	 * that are पातing that पात can complete.
	 */
	list_क्रम_each_entry(ctx, &chan->ctx_list, list) अणु
		अगर (ctx->पातing) अणु
			dev_dbg(priv->ipu->dev,
				"%s: task %u: signaling abort for ctx %p\n",
				__func__, chan->ic_task, ctx);
			complete_all(&ctx->पातed);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&chan->irqlock, flags);

	dev_dbg(priv->ipu->dev, "%s: task %u: exit\n", __func__,
		chan->ic_task);

	वापस IRQ_HANDLED;
पूर्ण

अटल bool ic_settings_changed(काष्ठा ipu_image_convert_ctx *ctx)
अणु
	अचिन्हित पूर्णांक cur_tile = ctx->next_tile - 1;
	अचिन्हित पूर्णांक next_tile = ctx->next_tile;

	अगर (ctx->resize_coeffs_h[cur_tile % ctx->in.num_cols] !=
	    ctx->resize_coeffs_h[next_tile % ctx->in.num_cols] ||
	    ctx->resize_coeffs_v[cur_tile / ctx->in.num_cols] !=
	    ctx->resize_coeffs_v[next_tile / ctx->in.num_cols] ||
	    ctx->in.tile[cur_tile].width != ctx->in.tile[next_tile].width ||
	    ctx->in.tile[cur_tile].height != ctx->in.tile[next_tile].height ||
	    ctx->out.tile[cur_tile].width != ctx->out.tile[next_tile].width ||
	    ctx->out.tile[cur_tile].height != ctx->out.tile[next_tile].height)
		वापस true;

	वापस false;
पूर्ण

/* hold irqlock when calling */
अटल irqवापस_t करो_tile_complete(काष्ठा ipu_image_convert_run *run)
अणु
	काष्ठा ipu_image_convert_ctx *ctx = run->ctx;
	काष्ठा ipu_image_convert_chan *chan = ctx->chan;
	काष्ठा ipu_image_tile *src_tile, *dst_tile;
	काष्ठा ipu_image_convert_image *s_image = &ctx->in;
	काष्ठा ipu_image_convert_image *d_image = &ctx->out;
	काष्ठा ipuv3_channel *outch;
	अचिन्हित पूर्णांक dst_idx;

	lockdep_निश्चित_held(&chan->irqlock);

	outch = ipu_rot_mode_is_irt(ctx->rot_mode) ?
		chan->rotation_out_chan : chan->out_chan;

	/*
	 * It is dअगरficult to stop the channel DMA beक्रमe the channels
	 * enter the छोड़ोd state. Without द्विगुन-buffering the channels
	 * are always in a छोड़ोd state when the खातापूर्ण irq occurs, so it
	 * is safe to stop the channels now. For द्विगुन-buffering we
	 * just ignore the पात until the operation completes, when it
	 * is safe to shut करोwn.
	 */
	अगर (ctx->पातing && !ctx->द्विगुन_buffering) अणु
		convert_stop(run);
		run->status = -EIO;
		जाओ करोne;
	पूर्ण

	अगर (ctx->next_tile == ctx->num_tiles) अणु
		/*
		 * the conversion is complete
		 */
		convert_stop(run);
		run->status = 0;
		जाओ करोne;
	पूर्ण

	/*
	 * not करोne, place the next tile buffers.
	 */
	अगर (!ctx->द्विगुन_buffering) अणु
		अगर (ic_settings_changed(ctx)) अणु
			convert_stop(run);
			convert_start(run, ctx->next_tile);
		पूर्ण अन्यथा अणु
			src_tile = &s_image->tile[ctx->next_tile];
			dst_idx = ctx->out_tile_map[ctx->next_tile];
			dst_tile = &d_image->tile[dst_idx];

			ipu_cpmem_set_buffer(chan->in_chan, 0,
					     s_image->base.phys0 +
					     src_tile->offset);
			ipu_cpmem_set_buffer(outch, 0,
					     d_image->base.phys0 +
					     dst_tile->offset);
			अगर (s_image->fmt->planar)
				ipu_cpmem_set_uv_offset(chan->in_chan,
							src_tile->u_off,
							src_tile->v_off);
			अगर (d_image->fmt->planar)
				ipu_cpmem_set_uv_offset(outch,
							dst_tile->u_off,
							dst_tile->v_off);

			ipu_idmac_select_buffer(chan->in_chan, 0);
			ipu_idmac_select_buffer(outch, 0);
		पूर्ण
	पूर्ण अन्यथा अगर (ctx->next_tile < ctx->num_tiles - 1) अणु

		src_tile = &s_image->tile[ctx->next_tile + 1];
		dst_idx = ctx->out_tile_map[ctx->next_tile + 1];
		dst_tile = &d_image->tile[dst_idx];

		ipu_cpmem_set_buffer(chan->in_chan, ctx->cur_buf_num,
				     s_image->base.phys0 + src_tile->offset);
		ipu_cpmem_set_buffer(outch, ctx->cur_buf_num,
				     d_image->base.phys0 + dst_tile->offset);

		ipu_idmac_select_buffer(chan->in_chan, ctx->cur_buf_num);
		ipu_idmac_select_buffer(outch, ctx->cur_buf_num);

		ctx->cur_buf_num ^= 1;
	पूर्ण

	ctx->eof_mask = 0; /* clear खातापूर्ण irq mask क्रम next tile */
	ctx->next_tile++;
	वापस IRQ_HANDLED;
करोne:
	list_add_tail(&run->list, &chan->करोne_q);
	chan->current_run = शून्य;
	run_next(chan);
	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t eof_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ipu_image_convert_chan *chan = data;
	काष्ठा ipu_image_convert_priv *priv = chan->priv;
	काष्ठा ipu_image_convert_ctx *ctx;
	काष्ठा ipu_image_convert_run *run;
	irqवापस_t ret = IRQ_HANDLED;
	bool tile_complete = false;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->irqlock, flags);

	/* get current run and its context */
	run = chan->current_run;
	अगर (!run) अणु
		ret = IRQ_NONE;
		जाओ out;
	पूर्ण

	ctx = run->ctx;

	अगर (irq == chan->in_eof_irq) अणु
		ctx->eof_mask |= खातापूर्ण_IRQ_IN;
	पूर्ण अन्यथा अगर (irq == chan->out_eof_irq) अणु
		ctx->eof_mask |= खातापूर्ण_IRQ_OUT;
	पूर्ण अन्यथा अगर (irq == chan->rot_in_eof_irq ||
		   irq == chan->rot_out_eof_irq) अणु
		अगर (!ipu_rot_mode_is_irt(ctx->rot_mode)) अणु
			/* this was NOT a rotation op, shouldn't happen */
			dev_err(priv->ipu->dev,
				"Unexpected rotation interrupt\n");
			जाओ out;
		पूर्ण
		ctx->eof_mask |= (irq == chan->rot_in_eof_irq) ?
			खातापूर्ण_IRQ_ROT_IN : खातापूर्ण_IRQ_ROT_OUT;
	पूर्ण अन्यथा अणु
		dev_err(priv->ipu->dev, "Received unknown irq %d\n", irq);
		ret = IRQ_NONE;
		जाओ out;
	पूर्ण

	अगर (ipu_rot_mode_is_irt(ctx->rot_mode))
		tile_complete =	(ctx->eof_mask == खातापूर्ण_IRQ_ROT_COMPLETE);
	अन्यथा
		tile_complete = (ctx->eof_mask == खातापूर्ण_IRQ_COMPLETE);

	अगर (tile_complete)
		ret = करो_tile_complete(run);
out:
	spin_unlock_irqrestore(&chan->irqlock, flags);
	वापस ret;
पूर्ण

/*
 * try to क्रमce the completion of runs क्रम this ctx. Called when
 * पात रुको बार out in ipu_image_convert_पात().
 */
अटल व्योम क्रमce_पात(काष्ठा ipu_image_convert_ctx *ctx)
अणु
	काष्ठा ipu_image_convert_chan *chan = ctx->chan;
	काष्ठा ipu_image_convert_run *run;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->irqlock, flags);

	run = chan->current_run;
	अगर (run && run->ctx == ctx) अणु
		convert_stop(run);
		run->status = -EIO;
		list_add_tail(&run->list, &chan->करोne_q);
		chan->current_run = शून्य;
		run_next(chan);
	पूर्ण

	spin_unlock_irqrestore(&chan->irqlock, flags);

	empty_करोne_q(chan);
पूर्ण

अटल व्योम release_ipu_resources(काष्ठा ipu_image_convert_chan *chan)
अणु
	अगर (chan->in_eof_irq >= 0)
		मुक्त_irq(chan->in_eof_irq, chan);
	अगर (chan->rot_in_eof_irq >= 0)
		मुक्त_irq(chan->rot_in_eof_irq, chan);
	अगर (chan->out_eof_irq >= 0)
		मुक्त_irq(chan->out_eof_irq, chan);
	अगर (chan->rot_out_eof_irq >= 0)
		मुक्त_irq(chan->rot_out_eof_irq, chan);

	अगर (!IS_ERR_OR_शून्य(chan->in_chan))
		ipu_idmac_put(chan->in_chan);
	अगर (!IS_ERR_OR_शून्य(chan->out_chan))
		ipu_idmac_put(chan->out_chan);
	अगर (!IS_ERR_OR_शून्य(chan->rotation_in_chan))
		ipu_idmac_put(chan->rotation_in_chan);
	अगर (!IS_ERR_OR_शून्य(chan->rotation_out_chan))
		ipu_idmac_put(chan->rotation_out_chan);
	अगर (!IS_ERR_OR_शून्य(chan->ic))
		ipu_ic_put(chan->ic);

	chan->in_chan = chan->out_chan = chan->rotation_in_chan =
		chan->rotation_out_chan = शून्य;
	chan->in_eof_irq = -1;
	chan->rot_in_eof_irq = -1;
	chan->out_eof_irq = -1;
	chan->rot_out_eof_irq = -1;
पूर्ण

अटल पूर्णांक get_eof_irq(काष्ठा ipu_image_convert_chan *chan,
		       काष्ठा ipuv3_channel *channel)
अणु
	काष्ठा ipu_image_convert_priv *priv = chan->priv;
	पूर्णांक ret, irq;

	irq = ipu_idmac_channel_irq(priv->ipu, channel, IPU_IRQ_खातापूर्ण);

	ret = request_thपढ़ोed_irq(irq, eof_irq, करो_bh, 0, "ipu-ic", chan);
	अगर (ret < 0) अणु
		dev_err(priv->ipu->dev, "could not acquire irq %d\n", irq);
		वापस ret;
	पूर्ण

	वापस irq;
पूर्ण

अटल पूर्णांक get_ipu_resources(काष्ठा ipu_image_convert_chan *chan)
अणु
	स्थिर काष्ठा ipu_image_convert_dma_chan *dma = chan->dma_ch;
	काष्ठा ipu_image_convert_priv *priv = chan->priv;
	पूर्णांक ret;

	/* get IC */
	chan->ic = ipu_ic_get(priv->ipu, chan->ic_task);
	अगर (IS_ERR(chan->ic)) अणु
		dev_err(priv->ipu->dev, "could not acquire IC\n");
		ret = PTR_ERR(chan->ic);
		जाओ err;
	पूर्ण

	/* get IDMAC channels */
	chan->in_chan = ipu_idmac_get(priv->ipu, dma->in);
	chan->out_chan = ipu_idmac_get(priv->ipu, dma->out);
	अगर (IS_ERR(chan->in_chan) || IS_ERR(chan->out_chan)) अणु
		dev_err(priv->ipu->dev, "could not acquire idmac channels\n");
		ret = -EBUSY;
		जाओ err;
	पूर्ण

	chan->rotation_in_chan = ipu_idmac_get(priv->ipu, dma->rot_in);
	chan->rotation_out_chan = ipu_idmac_get(priv->ipu, dma->rot_out);
	अगर (IS_ERR(chan->rotation_in_chan) || IS_ERR(chan->rotation_out_chan)) अणु
		dev_err(priv->ipu->dev,
			"could not acquire idmac rotation channels\n");
		ret = -EBUSY;
		जाओ err;
	पूर्ण

	/* acquire the खातापूर्ण पूर्णांकerrupts */
	ret = get_eof_irq(chan, chan->in_chan);
	अगर (ret < 0) अणु
		chan->in_eof_irq = -1;
		जाओ err;
	पूर्ण
	chan->in_eof_irq = ret;

	ret = get_eof_irq(chan, chan->rotation_in_chan);
	अगर (ret < 0) अणु
		chan->rot_in_eof_irq = -1;
		जाओ err;
	पूर्ण
	chan->rot_in_eof_irq = ret;

	ret = get_eof_irq(chan, chan->out_chan);
	अगर (ret < 0) अणु
		chan->out_eof_irq = -1;
		जाओ err;
	पूर्ण
	chan->out_eof_irq = ret;

	ret = get_eof_irq(chan, chan->rotation_out_chan);
	अगर (ret < 0) अणु
		chan->rot_out_eof_irq = -1;
		जाओ err;
	पूर्ण
	chan->rot_out_eof_irq = ret;

	वापस 0;
err:
	release_ipu_resources(chan);
	वापस ret;
पूर्ण

अटल पूर्णांक fill_image(काष्ठा ipu_image_convert_ctx *ctx,
		      काष्ठा ipu_image_convert_image *ic_image,
		      काष्ठा ipu_image *image,
		      क्रमागत ipu_image_convert_type type)
अणु
	काष्ठा ipu_image_convert_priv *priv = ctx->chan->priv;

	ic_image->base = *image;
	ic_image->type = type;

	ic_image->fmt = get_क्रमmat(image->pix.pixelक्रमmat);
	अगर (!ic_image->fmt) अणु
		dev_err(priv->ipu->dev, "pixelformat not supported for %s\n",
			type == IMAGE_CONVERT_OUT ? "Output" : "Input");
		वापस -EINVAL;
	पूर्ण

	अगर (ic_image->fmt->planar)
		ic_image->stride = ic_image->base.pix.width;
	अन्यथा
		ic_image->stride  = ic_image->base.pix.bytesperline;

	वापस 0;
पूर्ण

/* borrowed from drivers/media/v4l2-core/v4l2-common.c */
अटल अचिन्हित पूर्णांक clamp_align(अचिन्हित पूर्णांक x, अचिन्हित पूर्णांक min,
				अचिन्हित पूर्णांक max, अचिन्हित पूर्णांक align)
अणु
	/* Bits that must be zero to be aligned */
	अचिन्हित पूर्णांक mask = ~((1 << align) - 1);

	/* Clamp to aligned min and max */
	x = clamp(x, (min + ~mask) & mask, max & mask);

	/* Round to nearest aligned value */
	अगर (align)
		x = (x + (1 << (align - 1))) & mask;

	वापस x;
पूर्ण

/* Adjusts input/output images to IPU restrictions */
व्योम ipu_image_convert_adjust(काष्ठा ipu_image *in, काष्ठा ipu_image *out,
			      क्रमागत ipu_rotate_mode rot_mode)
अणु
	स्थिर काष्ठा ipu_image_pixfmt *infmt, *outfmt;
	u32 w_align_out, h_align_out;
	u32 w_align_in, h_align_in;

	infmt = get_क्रमmat(in->pix.pixelक्रमmat);
	outfmt = get_क्रमmat(out->pix.pixelक्रमmat);

	/* set some शेष pixel क्रमmats अगर needed */
	अगर (!infmt) अणु
		in->pix.pixelक्रमmat = V4L2_PIX_FMT_RGB24;
		infmt = get_क्रमmat(V4L2_PIX_FMT_RGB24);
	पूर्ण
	अगर (!outfmt) अणु
		out->pix.pixelक्रमmat = V4L2_PIX_FMT_RGB24;
		outfmt = get_क्रमmat(V4L2_PIX_FMT_RGB24);
	पूर्ण

	/* image converter करोes not handle fields */
	in->pix.field = out->pix.field = V4L2_FIELD_NONE;

	/* resizer cannot करोwnsize more than 4:1 */
	अगर (ipu_rot_mode_is_irt(rot_mode)) अणु
		out->pix.height = max_t(__u32, out->pix.height,
					in->pix.width / 4);
		out->pix.width = max_t(__u32, out->pix.width,
				       in->pix.height / 4);
	पूर्ण अन्यथा अणु
		out->pix.width = max_t(__u32, out->pix.width,
				       in->pix.width / 4);
		out->pix.height = max_t(__u32, out->pix.height,
					in->pix.height / 4);
	पूर्ण

	/* align input width/height */
	w_align_in = ilog2(tile_width_align(IMAGE_CONVERT_IN, infmt,
					    rot_mode));
	h_align_in = ilog2(tile_height_align(IMAGE_CONVERT_IN, infmt,
					     rot_mode));
	in->pix.width = clamp_align(in->pix.width, MIN_W, MAX_W,
				    w_align_in);
	in->pix.height = clamp_align(in->pix.height, MIN_H, MAX_H,
				     h_align_in);

	/* align output width/height */
	w_align_out = ilog2(tile_width_align(IMAGE_CONVERT_OUT, outfmt,
					     rot_mode));
	h_align_out = ilog2(tile_height_align(IMAGE_CONVERT_OUT, outfmt,
					      rot_mode));
	out->pix.width = clamp_align(out->pix.width, MIN_W, MAX_W,
				     w_align_out);
	out->pix.height = clamp_align(out->pix.height, MIN_H, MAX_H,
				      h_align_out);

	/* set input/output strides and image sizes */
	in->pix.bytesperline = infmt->planar ?
		clamp_align(in->pix.width, 2 << w_align_in, MAX_W,
			    w_align_in) :
		clamp_align((in->pix.width * infmt->bpp) >> 3,
			    ((2 << w_align_in) * infmt->bpp) >> 3,
			    (MAX_W * infmt->bpp) >> 3,
			    w_align_in);
	in->pix.sizeimage = infmt->planar ?
		(in->pix.height * in->pix.bytesperline * infmt->bpp) >> 3 :
		in->pix.height * in->pix.bytesperline;
	out->pix.bytesperline = outfmt->planar ? out->pix.width :
		(out->pix.width * outfmt->bpp) >> 3;
	out->pix.sizeimage = outfmt->planar ?
		(out->pix.height * out->pix.bytesperline * outfmt->bpp) >> 3 :
		out->pix.height * out->pix.bytesperline;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_image_convert_adjust);

/*
 * this is used by ipu_image_convert_prepare() to verअगरy set input and
 * output images are valid beक्रमe starting the conversion. Clients can
 * also call it beक्रमe calling ipu_image_convert_prepare().
 */
पूर्णांक ipu_image_convert_verअगरy(काष्ठा ipu_image *in, काष्ठा ipu_image *out,
			     क्रमागत ipu_rotate_mode rot_mode)
अणु
	काष्ठा ipu_image testin, testout;

	testin = *in;
	testout = *out;

	ipu_image_convert_adjust(&testin, &testout, rot_mode);

	अगर (testin.pix.width != in->pix.width ||
	    testin.pix.height != in->pix.height ||
	    testout.pix.width != out->pix.width ||
	    testout.pix.height != out->pix.height)
		वापस -EINVAL;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_image_convert_verअगरy);

/*
 * Call ipu_image_convert_prepare() to prepare क्रम the conversion of
 * given images and rotation mode. Returns a new conversion context.
 */
काष्ठा ipu_image_convert_ctx *
ipu_image_convert_prepare(काष्ठा ipu_soc *ipu, क्रमागत ipu_ic_task ic_task,
			  काष्ठा ipu_image *in, काष्ठा ipu_image *out,
			  क्रमागत ipu_rotate_mode rot_mode,
			  ipu_image_convert_cb_t complete,
			  व्योम *complete_context)
अणु
	काष्ठा ipu_image_convert_priv *priv = ipu->image_convert_priv;
	काष्ठा ipu_image_convert_image *s_image, *d_image;
	काष्ठा ipu_image_convert_chan *chan;
	काष्ठा ipu_image_convert_ctx *ctx;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;
	bool get_res;
	पूर्णांक ret;

	अगर (!in || !out || !complete ||
	    (ic_task != IC_TASK_VIEWFINDER &&
	     ic_task != IC_TASK_POST_PROCESSOR))
		वापस ERR_PTR(-EINVAL);

	/* verअगरy the in/out images beक्रमe continuing */
	ret = ipu_image_convert_verअगरy(in, out, rot_mode);
	अगर (ret) अणु
		dev_err(priv->ipu->dev, "%s: in/out formats invalid\n",
			__func__);
		वापस ERR_PTR(ret);
	पूर्ण

	chan = &priv->chan[ic_task];

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस ERR_PTR(-ENOMEM);

	dev_dbg(priv->ipu->dev, "%s: task %u: ctx %p\n", __func__,
		chan->ic_task, ctx);

	ctx->chan = chan;
	init_completion(&ctx->पातed);

	ctx->rot_mode = rot_mode;

	/* Sets ctx->in.num_rows/cols as well */
	ret = calc_image_resize_coefficients(ctx, in, out);
	अगर (ret)
		जाओ out_मुक्त;

	s_image = &ctx->in;
	d_image = &ctx->out;

	/* set tiling and rotation */
	अगर (ipu_rot_mode_is_irt(rot_mode)) अणु
		d_image->num_rows = s_image->num_cols;
		d_image->num_cols = s_image->num_rows;
	पूर्ण अन्यथा अणु
		d_image->num_rows = s_image->num_rows;
		d_image->num_cols = s_image->num_cols;
	पूर्ण

	ctx->num_tiles = d_image->num_cols * d_image->num_rows;

	ret = fill_image(ctx, s_image, in, IMAGE_CONVERT_IN);
	अगर (ret)
		जाओ out_मुक्त;
	ret = fill_image(ctx, d_image, out, IMAGE_CONVERT_OUT);
	अगर (ret)
		जाओ out_मुक्त;

	calc_out_tile_map(ctx);

	find_seams(ctx, s_image, d_image);

	ret = calc_tile_dimensions(ctx, s_image);
	अगर (ret)
		जाओ out_मुक्त;

	ret = calc_tile_offsets(ctx, s_image);
	अगर (ret)
		जाओ out_मुक्त;

	calc_tile_dimensions(ctx, d_image);
	ret = calc_tile_offsets(ctx, d_image);
	अगर (ret)
		जाओ out_मुक्त;

	calc_tile_resize_coefficients(ctx);

	ret = ipu_ic_calc_csc(&ctx->csc,
			s_image->base.pix.ycbcr_enc,
			s_image->base.pix.quantization,
			ipu_pixelक्रमmat_to_colorspace(s_image->fmt->fourcc),
			d_image->base.pix.ycbcr_enc,
			d_image->base.pix.quantization,
			ipu_pixelक्रमmat_to_colorspace(d_image->fmt->fourcc));
	अगर (ret)
		जाओ out_मुक्त;

	dump_क्रमmat(ctx, s_image);
	dump_क्रमmat(ctx, d_image);

	ctx->complete = complete;
	ctx->complete_context = complete_context;

	/*
	 * Can we use द्विगुन-buffering क्रम this operation? If there is
	 * only one tile (the whole image can be converted in a single
	 * operation) there's no poपूर्णांक in using द्विगुन-buffering. Also,
	 * the IPU's IDMAC channels allow only a single U and V plane
	 * offset shared between both buffers, but these offsets change
	 * क्रम every tile, and thereक्रमe would have to be updated क्रम
	 * each buffer which is not possible. So द्विगुन-buffering is
	 * impossible when either the source or destination images are
	 * a planar क्रमmat (YUV420, YUV422P, etc.). Further, dअगरferently
	 * sized tiles or dअगरferent resizing coefficients per tile
	 * prevent द्विगुन-buffering as well.
	 */
	ctx->द्विगुन_buffering = (ctx->num_tiles > 1 &&
				 !s_image->fmt->planar &&
				 !d_image->fmt->planar);
	क्रम (i = 1; i < ctx->num_tiles; i++) अणु
		अगर (ctx->in.tile[i].width != ctx->in.tile[0].width ||
		    ctx->in.tile[i].height != ctx->in.tile[0].height ||
		    ctx->out.tile[i].width != ctx->out.tile[0].width ||
		    ctx->out.tile[i].height != ctx->out.tile[0].height) अणु
			ctx->द्विगुन_buffering = false;
			अवरोध;
		पूर्ण
	पूर्ण
	क्रम (i = 1; i < ctx->in.num_cols; i++) अणु
		अगर (ctx->resize_coeffs_h[i] != ctx->resize_coeffs_h[0]) अणु
			ctx->द्विगुन_buffering = false;
			अवरोध;
		पूर्ण
	पूर्ण
	क्रम (i = 1; i < ctx->in.num_rows; i++) अणु
		अगर (ctx->resize_coeffs_v[i] != ctx->resize_coeffs_v[0]) अणु
			ctx->द्विगुन_buffering = false;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ipu_rot_mode_is_irt(ctx->rot_mode)) अणु
		अचिन्हित दीर्घ पूर्णांकermediate_size = d_image->tile[0].size;

		क्रम (i = 1; i < ctx->num_tiles; i++) अणु
			अगर (d_image->tile[i].size > पूर्णांकermediate_size)
				पूर्णांकermediate_size = d_image->tile[i].size;
		पूर्ण

		ret = alloc_dma_buf(priv, &ctx->rot_पूर्णांकermediate[0],
				    पूर्णांकermediate_size);
		अगर (ret)
			जाओ out_मुक्त;
		अगर (ctx->द्विगुन_buffering) अणु
			ret = alloc_dma_buf(priv,
					    &ctx->rot_पूर्णांकermediate[1],
					    पूर्णांकermediate_size);
			अगर (ret)
				जाओ out_मुक्त_dmabuf0;
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&chan->irqlock, flags);

	get_res = list_empty(&chan->ctx_list);

	list_add_tail(&ctx->list, &chan->ctx_list);

	spin_unlock_irqrestore(&chan->irqlock, flags);

	अगर (get_res) अणु
		ret = get_ipu_resources(chan);
		अगर (ret)
			जाओ out_मुक्त_dmabuf1;
	पूर्ण

	वापस ctx;

out_मुक्त_dmabuf1:
	मुक्त_dma_buf(priv, &ctx->rot_पूर्णांकermediate[1]);
	spin_lock_irqsave(&chan->irqlock, flags);
	list_del(&ctx->list);
	spin_unlock_irqrestore(&chan->irqlock, flags);
out_मुक्त_dmabuf0:
	मुक्त_dma_buf(priv, &ctx->rot_पूर्णांकermediate[0]);
out_मुक्त:
	kमुक्त(ctx);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_image_convert_prepare);

/*
 * Carry out a single image conversion run. Only the physaddr's of the input
 * and output image buffers are needed. The conversion context must have
 * been created previously with ipu_image_convert_prepare().
 */
पूर्णांक ipu_image_convert_queue(काष्ठा ipu_image_convert_run *run)
अणु
	काष्ठा ipu_image_convert_chan *chan;
	काष्ठा ipu_image_convert_priv *priv;
	काष्ठा ipu_image_convert_ctx *ctx;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (!run || !run->ctx || !run->in_phys || !run->out_phys)
		वापस -EINVAL;

	ctx = run->ctx;
	chan = ctx->chan;
	priv = chan->priv;

	dev_dbg(priv->ipu->dev, "%s: task %u: ctx %p run %p\n", __func__,
		chan->ic_task, ctx, run);

	INIT_LIST_HEAD(&run->list);

	spin_lock_irqsave(&chan->irqlock, flags);

	अगर (ctx->पातing) अणु
		ret = -EIO;
		जाओ unlock;
	पूर्ण

	list_add_tail(&run->list, &chan->pending_q);

	अगर (!chan->current_run) अणु
		ret = करो_run(run);
		अगर (ret)
			chan->current_run = शून्य;
	पूर्ण
unlock:
	spin_unlock_irqrestore(&chan->irqlock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_image_convert_queue);

/* Abort any active or pending conversions क्रम this context */
अटल व्योम __ipu_image_convert_पात(काष्ठा ipu_image_convert_ctx *ctx)
अणु
	काष्ठा ipu_image_convert_chan *chan = ctx->chan;
	काष्ठा ipu_image_convert_priv *priv = chan->priv;
	काष्ठा ipu_image_convert_run *run, *active_run, *पंचांगp;
	अचिन्हित दीर्घ flags;
	पूर्णांक run_count, ret;

	spin_lock_irqsave(&chan->irqlock, flags);

	/* move all reमुख्यing pending runs in this context to करोne_q */
	list_क्रम_each_entry_safe(run, पंचांगp, &chan->pending_q, list) अणु
		अगर (run->ctx != ctx)
			जारी;
		run->status = -EIO;
		list_move_tail(&run->list, &chan->करोne_q);
	पूर्ण

	run_count = get_run_count(ctx, &chan->करोne_q);
	active_run = (chan->current_run && chan->current_run->ctx == ctx) ?
		chan->current_run : शून्य;

	अगर (active_run)
		reinit_completion(&ctx->पातed);

	ctx->पातing = true;

	spin_unlock_irqrestore(&chan->irqlock, flags);

	अगर (!run_count && !active_run) अणु
		dev_dbg(priv->ipu->dev,
			"%s: task %u: no abort needed for ctx %p\n",
			__func__, chan->ic_task, ctx);
		वापस;
	पूर्ण

	अगर (!active_run) अणु
		empty_करोne_q(chan);
		वापस;
	पूर्ण

	dev_dbg(priv->ipu->dev,
		"%s: task %u: wait for completion: %d runs\n",
		__func__, chan->ic_task, run_count);

	ret = रुको_क्रम_completion_समयout(&ctx->पातed,
					  msecs_to_jअगरfies(10000));
	अगर (ret == 0) अणु
		dev_warn(priv->ipu->dev, "%s: timeout\n", __func__);
		क्रमce_पात(ctx);
	पूर्ण
पूर्ण

व्योम ipu_image_convert_पात(काष्ठा ipu_image_convert_ctx *ctx)
अणु
	__ipu_image_convert_पात(ctx);
	ctx->पातing = false;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_image_convert_पात);

/* Unprepare image conversion context */
व्योम ipu_image_convert_unprepare(काष्ठा ipu_image_convert_ctx *ctx)
अणु
	काष्ठा ipu_image_convert_chan *chan = ctx->chan;
	काष्ठा ipu_image_convert_priv *priv = chan->priv;
	अचिन्हित दीर्घ flags;
	bool put_res;

	/* make sure no runs are hanging around */
	__ipu_image_convert_पात(ctx);

	dev_dbg(priv->ipu->dev, "%s: task %u: removing ctx %p\n", __func__,
		chan->ic_task, ctx);

	spin_lock_irqsave(&chan->irqlock, flags);

	list_del(&ctx->list);

	put_res = list_empty(&chan->ctx_list);

	spin_unlock_irqrestore(&chan->irqlock, flags);

	अगर (put_res)
		release_ipu_resources(chan);

	मुक्त_dma_buf(priv, &ctx->rot_पूर्णांकermediate[1]);
	मुक्त_dma_buf(priv, &ctx->rot_पूर्णांकermediate[0]);

	kमुक्त(ctx);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_image_convert_unprepare);

/*
 * "Canned" asynchronous single image conversion. Allocates and वापसs
 * a new conversion run.  On successful वापस the caller must मुक्त the
 * run and call ipu_image_convert_unprepare() after conversion completes.
 */
काष्ठा ipu_image_convert_run *
ipu_image_convert(काष्ठा ipu_soc *ipu, क्रमागत ipu_ic_task ic_task,
		  काष्ठा ipu_image *in, काष्ठा ipu_image *out,
		  क्रमागत ipu_rotate_mode rot_mode,
		  ipu_image_convert_cb_t complete,
		  व्योम *complete_context)
अणु
	काष्ठा ipu_image_convert_ctx *ctx;
	काष्ठा ipu_image_convert_run *run;
	पूर्णांक ret;

	ctx = ipu_image_convert_prepare(ipu, ic_task, in, out, rot_mode,
					complete, complete_context);
	अगर (IS_ERR(ctx))
		वापस ERR_CAST(ctx);

	run = kzalloc(माप(*run), GFP_KERNEL);
	अगर (!run) अणु
		ipu_image_convert_unprepare(ctx);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	run->ctx = ctx;
	run->in_phys = in->phys0;
	run->out_phys = out->phys0;

	ret = ipu_image_convert_queue(run);
	अगर (ret) अणु
		ipu_image_convert_unprepare(ctx);
		kमुक्त(run);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस run;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_image_convert);

/* "Canned" synchronous single image conversion */
अटल व्योम image_convert_sync_complete(काष्ठा ipu_image_convert_run *run,
					व्योम *data)
अणु
	काष्ठा completion *comp = data;

	complete(comp);
पूर्ण

पूर्णांक ipu_image_convert_sync(काष्ठा ipu_soc *ipu, क्रमागत ipu_ic_task ic_task,
			   काष्ठा ipu_image *in, काष्ठा ipu_image *out,
			   क्रमागत ipu_rotate_mode rot_mode)
अणु
	काष्ठा ipu_image_convert_run *run;
	काष्ठा completion comp;
	पूर्णांक ret;

	init_completion(&comp);

	run = ipu_image_convert(ipu, ic_task, in, out, rot_mode,
				image_convert_sync_complete, &comp);
	अगर (IS_ERR(run))
		वापस PTR_ERR(run);

	ret = रुको_क्रम_completion_समयout(&comp, msecs_to_jअगरfies(10000));
	ret = (ret == 0) ? -ETIMEDOUT : 0;

	ipu_image_convert_unprepare(run->ctx);
	kमुक्त(run);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_image_convert_sync);

पूर्णांक ipu_image_convert_init(काष्ठा ipu_soc *ipu, काष्ठा device *dev)
अणु
	काष्ठा ipu_image_convert_priv *priv;
	पूर्णांक i;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	ipu->image_convert_priv = priv;
	priv->ipu = ipu;

	क्रम (i = 0; i < IC_NUM_TASKS; i++) अणु
		काष्ठा ipu_image_convert_chan *chan = &priv->chan[i];

		chan->ic_task = i;
		chan->priv = priv;
		chan->dma_ch = &image_convert_dma_chan[i];
		chan->in_eof_irq = -1;
		chan->rot_in_eof_irq = -1;
		chan->out_eof_irq = -1;
		chan->rot_out_eof_irq = -1;

		spin_lock_init(&chan->irqlock);
		INIT_LIST_HEAD(&chan->ctx_list);
		INIT_LIST_HEAD(&chan->pending_q);
		INIT_LIST_HEAD(&chan->करोne_q);
	पूर्ण

	वापस 0;
पूर्ण

व्योम ipu_image_convert_निकास(काष्ठा ipu_soc *ipu)
अणु
पूर्ण
