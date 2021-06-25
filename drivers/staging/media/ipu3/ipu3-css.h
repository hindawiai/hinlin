<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2018 Intel Corporation */

#अगर_अघोषित __IPU3_CSS_H
#घोषणा __IPU3_CSS_H

#समावेश <linux/videodev2.h>
#समावेश <linux/types.h>

#समावेश "ipu3-abi.h"
#समावेश "ipu3-css-pool.h"

/* 2 stages क्रम split isp pipeline, 1 क्रम scaling */
#घोषणा IMGU_NUM_SP			2
#घोषणा IMGU_MAX_PIPELINE_NUM		20
#घोषणा IMGU_MAX_PIPE_NUM		2

/* For DVS etc., क्रमmat FRAME_FMT_YUV420_16 */
#घोषणा IPU3_CSS_AUX_FRAME_REF		0
/* For temporal noise reduction DVS etc., क्रमmat FRAME_FMT_YUV_LINE */
#घोषणा IPU3_CSS_AUX_FRAME_TNR		1
#घोषणा IPU3_CSS_AUX_FRAME_TYPES	2	/* REF and TNR */
#घोषणा IPU3_CSS_AUX_FRAMES		2	/* 2 क्रम REF and 2 क्रम TNR */

#घोषणा IPU3_CSS_QUEUE_IN		0
#घोषणा IPU3_CSS_QUEUE_PARAMS		1
#घोषणा IPU3_CSS_QUEUE_OUT		2
#घोषणा IPU3_CSS_QUEUE_VF		3
#घोषणा IPU3_CSS_QUEUE_STAT_3A		4
#घोषणा IPU3_CSS_QUEUES			5

#घोषणा IPU3_CSS_RECT_EFFECTIVE		0	/* Effective resolution */
#घोषणा IPU3_CSS_RECT_BDS		1	/* Resolution after BDS */
#घोषणा IPU3_CSS_RECT_ENVELOPE		2	/* DVS envelope size */
#घोषणा IPU3_CSS_RECT_GDC		3	/* gdc output res */
#घोषणा IPU3_CSS_RECTS			4	/* number of rects */

#घोषणा IA_CSS_BINARY_MODE_PRIMARY	2
#घोषणा IA_CSS_BINARY_MODE_VIDEO	3
#घोषणा IPU3_CSS_DEFAULT_BINARY		3	/* शेष binary index */

/*
 * The pipe id type, distinguishes the kind of pipes that
 * can be run in parallel.
 */
क्रमागत imgu_css_pipe_id अणु
	IPU3_CSS_PIPE_ID_PREVIEW,
	IPU3_CSS_PIPE_ID_COPY,
	IPU3_CSS_PIPE_ID_VIDEO,
	IPU3_CSS_PIPE_ID_CAPTURE,
	IPU3_CSS_PIPE_ID_YUVPP,
	IPU3_CSS_PIPE_ID_ACC,
	IPU3_CSS_PIPE_ID_NUM
पूर्ण;

काष्ठा imgu_css_resolution अणु
	u32 w;
	u32 h;
पूर्ण;

क्रमागत imgu_css_buffer_state अणु
	IPU3_CSS_BUFFER_NEW,	/* Not yet queued */
	IPU3_CSS_BUFFER_QUEUED,	/* Queued, रुकोing to be filled */
	IPU3_CSS_BUFFER_DONE,	/* Finished processing, हटाओd from queue */
	IPU3_CSS_BUFFER_FAILED,	/* Was not processed, हटाओd from queue */
पूर्ण;

काष्ठा imgu_css_buffer अणु
	/* Private fields: user करोesn't touch */
	dma_addr_t daddr;
	अचिन्हित पूर्णांक queue;
	क्रमागत imgu_css_buffer_state state;
	काष्ठा list_head list;
	u8 queue_pos;
	अचिन्हित पूर्णांक pipe;
पूर्ण;

काष्ठा imgu_css_क्रमmat अणु
	u32 pixelक्रमmat;
	क्रमागत v4l2_colorspace colorspace;
	क्रमागत imgu_abi_frame_क्रमmat frame_क्रमmat;
	क्रमागत imgu_abi_bayer_order bayer_order;
	क्रमागत imgu_abi_osys_क्रमmat osys_क्रमmat;
	क्रमागत imgu_abi_osys_tiling osys_tiling;
	u32 bytesperpixel_num;	/* Bytes per pixel in first plane * 50 */
	u8 bit_depth;		/* Effective bits per pixel */
	u8 chroma_decim;	/* Chroma plane decimation, 0=no chroma plane */
	u8 width_align;		/* Alignment requirement क्रम width_pad */
	u8 flags;
पूर्ण;

काष्ठा imgu_css_queue अणु
	जोड़ अणु
		काष्ठा v4l2_pix_क्रमmat_mplane mpix;
		काष्ठा v4l2_meta_क्रमmat	meta;

	पूर्ण fmt;
	स्थिर काष्ठा imgu_css_क्रमmat *css_fmt;
	अचिन्हित पूर्णांक width_pad;
	काष्ठा list_head bufs;
पूर्ण;

काष्ठा imgu_css_pipe अणु
	क्रमागत imgu_css_pipe_id pipe_id;
	अचिन्हित पूर्णांक bindex;

	काष्ठा imgu_css_queue queue[IPU3_CSS_QUEUES];
	काष्ठा v4l2_rect rect[IPU3_CSS_RECTS];

	bool vf_output_en;
	/* Protect access to queue[IPU3_CSS_QUEUES] */
	spinlock_t qlock;

	/* Data काष्ठाures shared with IMGU and driver, always allocated */
	काष्ठा imgu_css_map sp_ddr_ptrs;
	काष्ठा imgu_css_map xmem_sp_stage_ptrs[IPU3_CSS_PIPE_ID_NUM]
					    [IMGU_ABI_MAX_STAGES];
	काष्ठा imgu_css_map xmem_isp_stage_ptrs[IPU3_CSS_PIPE_ID_NUM]
					    [IMGU_ABI_MAX_STAGES];

	/*
	 * Data काष्ठाures shared with IMGU and driver, binary specअगरic.
	 * PARAM_CLASS_CONFIG and PARAM_CLASS_STATE parameters.
	 */
	काष्ठा imgu_css_map binary_params_cs[IMGU_ABI_PARAM_CLASS_NUM - 1]
					    [IMGU_ABI_NUM_MEMORIES];

	काष्ठा अणु
		काष्ठा imgu_css_map mem[IPU3_CSS_AUX_FRAMES];
		अचिन्हित पूर्णांक width;
		अचिन्हित पूर्णांक height;
		अचिन्हित पूर्णांक bytesperline;
		अचिन्हित पूर्णांक bytesperpixel;
	पूर्ण aux_frames[IPU3_CSS_AUX_FRAME_TYPES];

	काष्ठा अणु
		काष्ठा imgu_css_pool parameter_set_info;
		काष्ठा imgu_css_pool acc;
		काष्ठा imgu_css_pool gdc;
		काष्ठा imgu_css_pool obgrid;
		/* PARAM_CLASS_PARAM parameters क्रम binding जबतक streaming */
		काष्ठा imgu_css_pool binary_params_p[IMGU_ABI_NUM_MEMORIES];
	पूर्ण pool;

	काष्ठा imgu_css_map abi_buffers[IPU3_CSS_QUEUES]
				    [IMGU_ABI_HOST2SP_BUFQ_SIZE];
पूर्ण;

/* IPU3 Camera Sub System काष्ठाure */
काष्ठा imgu_css अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	स्थिर काष्ठा firmware *fw;
	काष्ठा imgu_fw_header *fwp;
	पूर्णांक iomem_length;
	पूर्णांक fw_bl, fw_sp[IMGU_NUM_SP];	/* Indices of bl and SP binaries */
	काष्ठा imgu_css_map *binary;	/* fw binaries mapped to device */
	bool streaming;		/* true when streaming is enabled */

	काष्ठा imgu_css_pipe pipes[IMGU_MAX_PIPE_NUM];
	काष्ठा imgu_css_map xmem_sp_group_ptrs;

	/* enabled pipe(s) */
	DECLARE_BITMAP(enabled_pipes, IMGU_MAX_PIPE_NUM);
पूर्ण;

/******************* css v4l *******************/
पूर्णांक imgu_css_init(काष्ठा device *dev, काष्ठा imgu_css *css,
		  व्योम __iomem *base, पूर्णांक length);
व्योम imgu_css_cleanup(काष्ठा imgu_css *css);
पूर्णांक imgu_css_fmt_try(काष्ठा imgu_css *css,
		     काष्ठा v4l2_pix_क्रमmat_mplane *fmts[IPU3_CSS_QUEUES],
		     काष्ठा v4l2_rect *rects[IPU3_CSS_RECTS],
		     अचिन्हित पूर्णांक pipe);
पूर्णांक imgu_css_fmt_set(काष्ठा imgu_css *css,
		     काष्ठा v4l2_pix_क्रमmat_mplane *fmts[IPU3_CSS_QUEUES],
		     काष्ठा v4l2_rect *rects[IPU3_CSS_RECTS],
		     अचिन्हित पूर्णांक pipe);
पूर्णांक imgu_css_meta_fmt_set(काष्ठा v4l2_meta_क्रमmat *fmt);
पूर्णांक imgu_css_buf_queue(काष्ठा imgu_css *css, अचिन्हित पूर्णांक pipe,
		       काष्ठा imgu_css_buffer *b);
काष्ठा imgu_css_buffer *imgu_css_buf_dequeue(काष्ठा imgu_css *css);
पूर्णांक imgu_css_start_streaming(काष्ठा imgu_css *css);
व्योम imgu_css_stop_streaming(काष्ठा imgu_css *css);
bool imgu_css_queue_empty(काष्ठा imgu_css *css);
bool imgu_css_is_streaming(काष्ठा imgu_css *css);
bool imgu_css_pipe_queue_empty(काष्ठा imgu_css *css, अचिन्हित पूर्णांक pipe);

/******************* css hw *******************/
पूर्णांक imgu_css_set_घातerup(काष्ठा device *dev, व्योम __iomem *base,
			 अचिन्हित पूर्णांक freq);
व्योम imgu_css_set_घातerकरोwn(काष्ठा device *dev, व्योम __iomem *base);
पूर्णांक imgu_css_irq_ack(काष्ठा imgu_css *css);

/******************* set parameters ************/
पूर्णांक imgu_css_set_parameters(काष्ठा imgu_css *css, अचिन्हित पूर्णांक pipe,
			    काष्ठा ipu3_uapi_params *set_params);

/******************* auxiliary helpers *******************/
अटल अंतरभूत क्रमागत imgu_css_buffer_state
imgu_css_buf_state(काष्ठा imgu_css_buffer *b)
अणु
	वापस b->state;
पूर्ण

/* Initialize given buffer. May be called several बार. */
अटल अंतरभूत व्योम imgu_css_buf_init(काष्ठा imgu_css_buffer *b,
				     अचिन्हित पूर्णांक queue, dma_addr_t daddr)
अणु
	b->state = IPU3_CSS_BUFFER_NEW;
	b->queue = queue;
	b->daddr = daddr;
पूर्ण
#पूर्ण_अगर
