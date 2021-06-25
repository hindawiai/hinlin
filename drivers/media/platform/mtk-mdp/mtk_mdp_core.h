<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015-2016 MediaTek Inc.
 * Author: Houदीर्घ Wei <houदीर्घ.wei@mediatek.com>
 *         Ming Hsiu Tsai <minghsiu.tsai@mediatek.com>
 */

#अगर_अघोषित __MTK_MDP_CORE_H__
#घोषणा __MTK_MDP_CORE_H__

#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/videobuf2-core.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "mtk_mdp_vpu.h"
#समावेश "mtk_mdp_comp.h"


#घोषणा MTK_MDP_MODULE_NAME		"mtk-mdp"

#घोषणा MTK_MDP_SHUTDOWN_TIMEOUT	((100*HZ)/1000) /* 100ms */
#घोषणा MTK_MDP_MAX_CTRL_NUM		10

#घोषणा MTK_MDP_FMT_FLAG_OUTPUT		BIT(0)
#घोषणा MTK_MDP_FMT_FLAG_CAPTURE	BIT(1)

#घोषणा MTK_MDP_VPU_INIT		BIT(0)
#घोषणा MTK_MDP_CTX_ERROR		BIT(5)

/**
 *  काष्ठा mtk_mdp_pix_align - alignment of image
 *  @org_w: source alignment of width
 *  @org_h: source alignment of height
 *  @target_w: dst alignment of width
 *  @target_h: dst alignment of height
 */
काष्ठा mtk_mdp_pix_align अणु
	u16 org_w;
	u16 org_h;
	u16 target_w;
	u16 target_h;
पूर्ण;

/**
 * काष्ठा mtk_mdp_fmt - the driver's पूर्णांकernal color क्रमmat data
 * @pixelक्रमmat: the fourcc code क्रम this क्रमmat, 0 अगर not applicable
 * @num_planes: number of physically non-contiguous data planes
 * @num_comp: number of logical data planes
 * @depth: per plane driver's private 'number of bits per pixel'
 * @row_depth: per plane driver's private 'number of bits per pixel per row'
 * @flags: flags indicating which operation mode क्रमmat applies to
 *	   MTK_MDP_FMT_FLAG_OUTPUT is used in OUTPUT stream
 *	   MTK_MDP_FMT_FLAG_CAPTURE is used in CAPTURE stream
 * @align: poपूर्णांकer to a pixel alignment काष्ठा, शून्य अगर using शेष value
 */
काष्ठा mtk_mdp_fmt अणु
	u32	pixelक्रमmat;
	u16	num_planes;
	u16	num_comp;
	u8	depth[VIDEO_MAX_PLANES];
	u8	row_depth[VIDEO_MAX_PLANES];
	u32	flags;
	काष्ठा mtk_mdp_pix_align *align;
पूर्ण;

/**
 * काष्ठा mtk_mdp_addr - the image processor physical address set
 * @addr:	address of planes
 */
काष्ठा mtk_mdp_addr अणु
	dma_addr_t addr[MTK_MDP_MAX_NUM_PLANE];
पूर्ण;

/* काष्ठा mtk_mdp_ctrls - the image processor control set
 * @rotate: rotation degree
 * @hflip: horizontal flip
 * @vflip: vertical flip
 * @global_alpha: the alpha value of current frame
 */
काष्ठा mtk_mdp_ctrls अणु
	काष्ठा v4l2_ctrl *rotate;
	काष्ठा v4l2_ctrl *hflip;
	काष्ठा v4l2_ctrl *vflip;
	काष्ठा v4l2_ctrl *global_alpha;
पूर्ण;

/**
 * काष्ठा mtk_mdp_frame - source/target frame properties
 * @width:	SRC : SRCIMG_WIDTH, DST : OUTPUTDMA_WHOLE_IMG_WIDTH
 * @height:	SRC : SRCIMG_HEIGHT, DST : OUTPUTDMA_WHOLE_IMG_HEIGHT
 * @crop:	cropped(source)/scaled(destination) size
 * @payload:	image size in bytes (w x h x bpp)
 * @pitch:	bytes per line of image in memory
 * @addr:	image frame buffer physical addresses
 * @fmt:	color क्रमmat poपूर्णांकer
 * @alpha:	frame's alpha value
 */
काष्ठा mtk_mdp_frame अणु
	u32				width;
	u32				height;
	काष्ठा v4l2_rect		crop;
	अचिन्हित दीर्घ			payload[VIDEO_MAX_PLANES];
	अचिन्हित पूर्णांक			pitch[VIDEO_MAX_PLANES];
	काष्ठा mtk_mdp_addr		addr;
	स्थिर काष्ठा mtk_mdp_fmt	*fmt;
	u8				alpha;
पूर्ण;

/**
 * काष्ठा mtk_mdp_variant - image processor variant inक्रमmation
 * @pix_max:		maximum limit of image size
 * @pix_min:		minimum limit of image size
 * @pix_align:		alignment of image
 * @h_scale_up_max:	maximum scale-up in horizontal
 * @v_scale_up_max:	maximum scale-up in vertical
 * @h_scale_करोwn_max:	maximum scale-करोwn in horizontal
 * @v_scale_करोwn_max:	maximum scale-करोwn in vertical
 */
काष्ठा mtk_mdp_variant अणु
	काष्ठा mtk_mdp_pix_limit	*pix_max;
	काष्ठा mtk_mdp_pix_limit	*pix_min;
	काष्ठा mtk_mdp_pix_align	*pix_align;
	u16				h_scale_up_max;
	u16				v_scale_up_max;
	u16				h_scale_करोwn_max;
	u16				v_scale_करोwn_max;
पूर्ण;

/**
 * काष्ठा mtk_mdp_dev - असलtraction क्रम image processor entity
 * @lock:	the mutex protecting this data काष्ठाure
 * @vpulock:	the mutex protecting the communication with VPU
 * @pdev:	poपूर्णांकer to the image processor platक्रमm device
 * @variant:	the IP variant inक्रमmation
 * @id:		image processor device index (0..MTK_MDP_MAX_DEVS)
 * @comp_list:	list of MDP function components
 * @m2m_dev:	v4l2 memory-to-memory device data
 * @ctx_list:	list of काष्ठा mtk_mdp_ctx
 * @vdev:	video device क्रम image processor driver
 * @v4l2_dev:	V4L2 device to रेजिस्टर video devices क्रम.
 * @job_wq:	processor work queue
 * @vpu_dev:	VPU platक्रमm device
 * @ctx_num:	counter of active MTK MDP context
 * @id_counter:	An पूर्णांकeger id given to the next खोलोed context
 * @wdt_wq:	work queue क्रम VPU watchकरोg
 * @wdt_work:	worker क्रम VPU watchकरोg
 */
काष्ठा mtk_mdp_dev अणु
	काष्ठा mutex			lock;
	काष्ठा mutex			vpulock;
	काष्ठा platक्रमm_device		*pdev;
	काष्ठा mtk_mdp_variant		*variant;
	u16				id;
	काष्ठा list_head		comp_list;
	काष्ठा v4l2_m2m_dev		*m2m_dev;
	काष्ठा list_head		ctx_list;
	काष्ठा video_device		*vdev;
	काष्ठा v4l2_device		v4l2_dev;
	काष्ठा workqueue_काष्ठा		*job_wq;
	काष्ठा platक्रमm_device		*vpu_dev;
	पूर्णांक				ctx_num;
	अचिन्हित दीर्घ			id_counter;
	काष्ठा workqueue_काष्ठा		*wdt_wq;
	काष्ठा work_काष्ठा		wdt_work;
पूर्ण;

/**
 * काष्ठा mtk_mdp_ctx - the device context data
 * @list:		link to ctx_list of mtk_mdp_dev
 * @s_frame:		source frame properties
 * @d_frame:		destination frame properties
 * @id:			index of the context that this काष्ठाure describes
 * @flags:		additional flags क्रम image conversion
 * @state:		flags to keep track of user configuration
 *			Protected by slock
 * @rotation:		rotates the image by specअगरied angle
 * @hflip:		mirror the picture horizontally
 * @vflip:		mirror the picture vertically
 * @mdp_dev:		the image processor device this context applies to
 * @m2m_ctx:		memory-to-memory device context
 * @fh:			v4l2 file handle
 * @ctrl_handler:	v4l2 controls handler
 * @ctrls:		image processor control set
 * @ctrls_rdy:		true अगर the control handler is initialized
 * @colorspace:		क्रमागत v4l2_colorspace; supplemental to pixelक्रमmat
 * @ycbcr_enc:		क्रमागत v4l2_ycbcr_encoding, Y'CbCr encoding
 * @xfer_func:		क्रमागत v4l2_xfer_func, colorspace transfer function
 * @quant:		क्रमागत v4l2_quantization, colorspace quantization
 * @vpu:		VPU instance
 * @slock:		the mutex protecting mtp_mdp_ctx.state
 * @work:		worker क्रम image processing
 */
काष्ठा mtk_mdp_ctx अणु
	काष्ठा list_head		list;
	काष्ठा mtk_mdp_frame		s_frame;
	काष्ठा mtk_mdp_frame		d_frame;
	u32				flags;
	u32				state;
	पूर्णांक				id;
	पूर्णांक				rotation;
	u32				hflip:1;
	u32				vflip:1;
	काष्ठा mtk_mdp_dev		*mdp_dev;
	काष्ठा v4l2_m2m_ctx		*m2m_ctx;
	काष्ठा v4l2_fh			fh;
	काष्ठा v4l2_ctrl_handler	ctrl_handler;
	काष्ठा mtk_mdp_ctrls		ctrls;
	bool				ctrls_rdy;
	क्रमागत v4l2_colorspace		colorspace;
	क्रमागत v4l2_ycbcr_encoding	ycbcr_enc;
	क्रमागत v4l2_xfer_func		xfer_func;
	क्रमागत v4l2_quantization		quant;

	काष्ठा mtk_mdp_vpu		vpu;
	काष्ठा mutex			slock;
	काष्ठा work_काष्ठा		work;
पूर्ण;

बाह्य पूर्णांक mtk_mdp_dbg_level;

व्योम mtk_mdp_रेजिस्टर_component(काष्ठा mtk_mdp_dev *mdp,
				काष्ठा mtk_mdp_comp *comp);

व्योम mtk_mdp_unरेजिस्टर_component(काष्ठा mtk_mdp_dev *mdp,
				  काष्ठा mtk_mdp_comp *comp);

#अगर defined(DEBUG)

#घोषणा mtk_mdp_dbg(level, fmt, args...)				 \
	करो अणु								 \
		अगर (mtk_mdp_dbg_level >= level)				 \
			pr_info("[MTK_MDP] level=%d %s(),%d: " fmt "\n", \
				level, __func__, __LINE__, ##args);	 \
	पूर्ण जबतक (0)

#घोषणा mtk_mdp_err(fmt, args...)					\
	pr_err("[MTK_MDP][ERROR] %s:%d: " fmt "\n", __func__, __LINE__, \
	       ##args)


#घोषणा mtk_mdp_dbg_enter()  mtk_mdp_dbg(3, "+")
#घोषणा mtk_mdp_dbg_leave()  mtk_mdp_dbg(3, "-")

#अन्यथा

#घोषणा mtk_mdp_dbg(level, fmt, args...) अणुपूर्ण
#घोषणा mtk_mdp_err(fmt, args...)
#घोषणा mtk_mdp_dbg_enter()
#घोषणा mtk_mdp_dbg_leave()

#पूर्ण_अगर

#पूर्ण_अगर /* __MTK_MDP_CORE_H__ */
