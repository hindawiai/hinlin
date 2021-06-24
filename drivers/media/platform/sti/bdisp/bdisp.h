<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Authors: Fabien Dessenne <fabien.dessenne@st.com> क्रम STMicroelectronics.
 */

#समावेश <linux/clk.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-mem2स्मृति.स>

#समावेश <media/videobuf2-dma-contig.h>

#घोषणा BDISP_NAME              "bdisp"

/*
 *  Max nb of nodes in node-list:
 *   - 2 nodes to handle wide 4K pictures
 *   - 2 nodes to handle two planes (Y & CbCr) */
#घोषणा MAX_OUTPUT_PLANES       2
#घोषणा MAX_VERTICAL_STRIDES    2
#घोषणा MAX_NB_NODE             (MAX_OUTPUT_PLANES * MAX_VERTICAL_STRIDES)

/* काष्ठा bdisp_ctrls - bdisp control set
 * @hflip:      horizontal flip
 * @vflip:      vertical flip
 */
काष्ठा bdisp_ctrls अणु
	काष्ठा v4l2_ctrl        *hflip;
	काष्ठा v4l2_ctrl        *vflip;
पूर्ण;

/**
 * काष्ठा bdisp_fmt - driver's पूर्णांकernal color क्रमmat data
 * @pixelक्रमmat:fourcc code क्रम this क्रमmat
 * @nb_planes:  number of planes  (ex: [0]=RGB/Y - [1]=Cb/Cr, ...)
 * @bpp:        bits per pixel (general)
 * @bpp_plane0: byte per pixel क्रम the 1st plane
 * @w_align:    width alignment in pixel (multiple of)
 * @h_align:    height alignment in pixel (multiple of)
 */
काष्ठा bdisp_fmt अणु
	u32                     pixelक्रमmat;
	u8                      nb_planes;
	u8                      bpp;
	u8                      bpp_plane0;
	u8                      w_align;
	u8                      h_align;
पूर्ण;

/**
 * काष्ठा bdisp_frame - frame properties
 *
 * @width:      frame width (including padding)
 * @height:     frame height (including padding)
 * @fmt:        poपूर्णांकer to frame क्रमmat descriptor
 * @field:      frame / field type
 * @bytesperline: stride of the 1st plane
 * @sizeimage:  image size in bytes
 * @colorspace: colorspace
 * @crop:       crop area
 * @paddr:      image physical addresses per plane ([0]=RGB/Y - [1]=Cb/Cr, ...)
 */
काष्ठा bdisp_frame अणु
	u32                     width;
	u32                     height;
	स्थिर काष्ठा bdisp_fmt  *fmt;
	क्रमागत v4l2_field         field;
	u32                     bytesperline;
	u32                     sizeimage;
	क्रमागत v4l2_colorspace    colorspace;
	काष्ठा v4l2_rect        crop;
	dma_addr_t              paddr[4];
पूर्ण;

/**
 * काष्ठा bdisp_request - bdisp request
 *
 * @src:        source frame properties
 * @dst:        destination frame properties
 * @hflip:      horizontal flip
 * @vflip:      vertical flip
 * @nb_req:     number of run request
 */
काष्ठा bdisp_request अणु
	काष्ठा bdisp_frame      src;
	काष्ठा bdisp_frame      dst;
	अचिन्हित पूर्णांक            hflip:1;
	अचिन्हित पूर्णांक            vflip:1;
	पूर्णांक                     nb_req;
पूर्ण;

/**
 * काष्ठा bdisp_ctx - device context data
 *
 * @src:        source frame properties
 * @dst:        destination frame properties
 * @state:      flags to keep track of user configuration
 * @hflip:      horizontal flip
 * @vflip:      vertical flip
 * @bdisp_dev:  the device this context applies to
 * @node:       node array
 * @node_paddr: node physical address array
 * @fh:         v4l2 file handle
 * @ctrl_handler: v4l2 controls handler
 * @bdisp_ctrls: bdisp control set
 * @ctrls_rdy:  true अगर the control handler is initialized
 */
काष्ठा bdisp_ctx अणु
	काष्ठा bdisp_frame      src;
	काष्ठा bdisp_frame      dst;
	u32                     state;
	अचिन्हित पूर्णांक            hflip:1;
	अचिन्हित पूर्णांक            vflip:1;
	काष्ठा bdisp_dev        *bdisp_dev;
	काष्ठा bdisp_node       *node[MAX_NB_NODE];
	dma_addr_t              node_paddr[MAX_NB_NODE];
	काष्ठा v4l2_fh          fh;
	काष्ठा v4l2_ctrl_handler ctrl_handler;
	काष्ठा bdisp_ctrls      bdisp_ctrls;
	bool                    ctrls_rdy;
पूर्ण;

/**
 * काष्ठा bdisp_m2m_device - v4l2 memory-to-memory device data
 *
 * @vdev:       video device node क्रम v4l2 m2m mode
 * @m2m_dev:    v4l2 m2m device data
 * @ctx:        hardware context data
 * @refcnt:     reference counter
 */
काष्ठा bdisp_m2m_device अणु
	काष्ठा video_device     *vdev;
	काष्ठा v4l2_m2m_dev     *m2m_dev;
	काष्ठा bdisp_ctx        *ctx;
	पूर्णांक                     refcnt;
पूर्ण;

/**
 * काष्ठा bdisp_dbg - debug info
 *
 * @debugfs_entry: debugfs
 * @copy_node:     array of last used nodes
 * @copy_request:  last bdisp request
 * @hw_start:      start समय of last HW request
 * @last_duration: last HW processing duration in microsecs
 * @min_duration:  min HW processing duration in microsecs
 * @max_duration:  max HW processing duration in microsecs
 * @tot_duration:  total HW processing duration in microsecs
 */
काष्ठा bdisp_dbg अणु
	काष्ठा dentry           *debugfs_entry;
	काष्ठा bdisp_node       *copy_node[MAX_NB_NODE];
	काष्ठा bdisp_request    copy_request;
	kसमय_प्रकार                 hw_start;
	s64                     last_duration;
	s64                     min_duration;
	s64                     max_duration;
	s64                     tot_duration;
पूर्ण;

/**
 * काष्ठा bdisp_dev - असलtraction क्रम bdisp entity
 *
 * @v4l2_dev:   v4l2 device
 * @vdev:       video device
 * @pdev:       platक्रमm device
 * @dev:        device
 * @lock:       mutex protecting this data काष्ठाure
 * @slock:      spinlock protecting this data काष्ठाure
 * @id:         device index
 * @m2m:        memory-to-memory V4L2 device inक्रमmation
 * @state:      flags used to synchronize m2m and capture mode operation
 * @घड़ी:      IP घड़ी
 * @regs:       रेजिस्टरs
 * @irq_queue:  पूर्णांकerrupt handler रुकोqueue
 * @work_queue: workqueue to handle समयouts
 * @समयout_work: IRQ समयout काष्ठाure
 * @dbg:        debug info
 */
काष्ठा bdisp_dev अणु
	काष्ठा v4l2_device      v4l2_dev;
	काष्ठा video_device     vdev;
	काष्ठा platक्रमm_device  *pdev;
	काष्ठा device           *dev;
	spinlock_t              slock;
	काष्ठा mutex            lock;
	u16                     id;
	काष्ठा bdisp_m2m_device m2m;
	अचिन्हित दीर्घ           state;
	काष्ठा clk              *घड़ी;
	व्योम __iomem            *regs;
	रुको_queue_head_t       irq_queue;
	काष्ठा workqueue_काष्ठा *work_queue;
	काष्ठा delayed_work     समयout_work;
	काष्ठा bdisp_dbg        dbg;
पूर्ण;

व्योम bdisp_hw_मुक्त_nodes(काष्ठा bdisp_ctx *ctx);
पूर्णांक bdisp_hw_alloc_nodes(काष्ठा bdisp_ctx *ctx);
व्योम bdisp_hw_मुक्त_filters(काष्ठा device *dev);
पूर्णांक bdisp_hw_alloc_filters(काष्ठा device *dev);
पूर्णांक bdisp_hw_reset(काष्ठा bdisp_dev *bdisp);
पूर्णांक bdisp_hw_get_and_clear_irq(काष्ठा bdisp_dev *bdisp);
पूर्णांक bdisp_hw_update(काष्ठा bdisp_ctx *ctx);

व्योम bdisp_debugfs_हटाओ(काष्ठा bdisp_dev *bdisp);
व्योम bdisp_debugfs_create(काष्ठा bdisp_dev *bdisp);
व्योम bdisp_dbg_perf_begin(काष्ठा bdisp_dev *bdisp);
व्योम bdisp_dbg_perf_end(काष्ठा bdisp_dev *bdisp);
