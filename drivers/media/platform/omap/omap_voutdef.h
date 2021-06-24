<शैली गुरु>
/*
 * omap_voutdef.h
 *
 * Copyright (C) 2010 Texas Instruments.
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#अगर_अघोषित OMAP_VOUTDEF_H
#घोषणा OMAP_VOUTDEF_H

#समावेश <media/videobuf2-dma-contig.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <video/omapfb_dss.h>
#समावेश <video/omapvrfb.h>
#समावेश <linux/dmaengine.h>

#घोषणा YUYV_BPP        2
#घोषणा RGB565_BPP      2
#घोषणा RGB24_BPP       3
#घोषणा RGB32_BPP       4
#घोषणा TILE_SIZE       32
#घोषणा YUYV_VRFB_BPP   2
#घोषणा RGB_VRFB_BPP    1
#घोषणा MAX_CID		3
#घोषणा MAC_VRFB_CTXS	4
#घोषणा MAX_VOUT_DEV	2
#घोषणा MAX_OVLS	3
#घोषणा MAX_DISPLAYS	10
#घोषणा MAX_MANAGERS	3

#घोषणा QQVGA_WIDTH		160
#घोषणा QQVGA_HEIGHT		120

/* Max Resolution supported by the driver */
#घोषणा VID_MAX_WIDTH		1280	/* Largest width */
#घोषणा VID_MAX_HEIGHT		720	/* Largest height */

/* Minimum requirement is 2x2 क्रम DSS */
#घोषणा VID_MIN_WIDTH		2
#घोषणा VID_MIN_HEIGHT		2

/* 2048 x 2048 is max res supported by OMAP display controller */
#घोषणा MAX_PIXELS_PER_LINE     2048

#घोषणा VRFB_TX_TIMEOUT         1000
#घोषणा VRFB_NUM_BUFS		4

/* Max buffer size tobe allocated during init */
#घोषणा OMAP_VOUT_MAX_BUF_SIZE (VID_MAX_WIDTH*VID_MAX_HEIGHT*4)

क्रमागत dma_channel_state अणु
	DMA_CHAN_NOT_ALLOTED,
	DMA_CHAN_ALLOTED,
पूर्ण;

/* Enum क्रम Rotation
 * DSS understands rotation in 0, 1, 2, 3 context
 * जबतक V4L2 driver understands it as 0, 90, 180, 270
 */
क्रमागत dss_rotation अणु
	dss_rotation_0_degree	= 0,
	dss_rotation_90_degree	= 1,
	dss_rotation_180_degree	= 2,
	dss_rotation_270_degree = 3,
पूर्ण;

/* Enum क्रम choosing rotation type क्रम vout
 * DSS2 करोesn't understand no rotation as an
 * option जबतक V4L2 driver करोesn't support
 * rotation in the हाल where VRFB is not built in
 * the kernel
 */
क्रमागत vout_rotaion_type अणु
	VOUT_ROT_NONE	= 0,
	VOUT_ROT_VRFB	= 1,
पूर्ण;

/*
 * This काष्ठाure is used to store the DMA transfer parameters
 * क्रम VRFB hidden buffer
 */
काष्ठा vid_vrfb_dma अणु
	काष्ठा dma_chan *chan;
	काष्ठा dma_पूर्णांकerleaved_ढाँचा *xt;

	पूर्णांक req_status;
	पूर्णांक tx_status;
	रुको_queue_head_t रुको;
पूर्ण;

काष्ठा omapvideo_info अणु
	पूर्णांक id;
	पूर्णांक num_overlays;
	काष्ठा omap_overlay *overlays[MAX_OVLS];
	क्रमागत vout_rotaion_type rotation_type;
पूर्ण;

काष्ठा omap2video_device अणु
	काष्ठा mutex  mtx;

	पूर्णांक state;

	काष्ठा v4l2_device v4l2_dev;
	काष्ठा omap_vout_device *vouts[MAX_VOUT_DEV];

	पूर्णांक num_displays;
	काष्ठा omap_dss_device *displays[MAX_DISPLAYS];
	पूर्णांक num_overlays;
	काष्ठा omap_overlay *overlays[MAX_OVLS];
	पूर्णांक num_managers;
	काष्ठा omap_overlay_manager *managers[MAX_MANAGERS];
पूर्ण;

/* buffer क्रम one video frame */
काष्ठा omap_vout_buffer अणु
	/* common v4l buffer stuff -- must be first */
	काष्ठा vb2_v4l2_buffer		vbuf;
	काष्ठा list_head		queue;
पूर्ण;

अटल अंतरभूत काष्ठा omap_vout_buffer *vb2_to_omap_vout_buffer(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);

	वापस container_of(vbuf, काष्ठा omap_vout_buffer, vbuf);
पूर्ण

/* per-device data काष्ठाure */
काष्ठा omap_vout_device अणु

	काष्ठा omapvideo_info vid_info;
	काष्ठा video_device *vfd;
	काष्ठा omap2video_device *vid_dev;
	काष्ठा v4l2_ctrl_handler ctrl_handler;
	पूर्णांक vid;

	/* allow to reuse previously allocated buffer which is big enough */
	पूर्णांक buffer_size;
	क्रमागत omap_color_mode dss_mode;

	u32 sequence;

	काष्ठा v4l2_pix_क्रमmat pix;
	काष्ठा v4l2_rect crop;
	काष्ठा v4l2_winकरोw win;
	काष्ठा v4l2_framebuffer fbuf;

	/* Lock to protect the shared data काष्ठाures in ioctl */
	काष्ठा mutex lock;

	क्रमागत dss_rotation rotation;
	bool mirror;
	पूर्णांक flicker_filter;

	पूर्णांक bpp; /* bytes per pixel */
	पूर्णांक vrfb_bpp; /* bytes per pixel with respect to VRFB */

	काष्ठा vid_vrfb_dma vrfb_dma_tx;
	अचिन्हित पूर्णांक smsshaकरो_phy_addr[MAC_VRFB_CTXS];
	अचिन्हित पूर्णांक smsshaकरो_virt_addr[MAC_VRFB_CTXS];
	काष्ठा vrfb vrfb_context[MAC_VRFB_CTXS];
	bool vrfb_अटल_allocation;
	अचिन्हित पूर्णांक smsshaकरो_size;
	अचिन्हित अक्षर pos;

	पूर्णांक ps, vr_ps, line_length, first_पूर्णांक, field_id;
	काष्ठा omap_vout_buffer *cur_frm, *next_frm;
	spinlock_t vbq_lock;            /* spinlock क्रम dma_queue */
	काष्ठा list_head dma_queue;
	u8 *queued_buf_addr[VIDEO_MAX_FRAME];
	u32 cropped_offset;
	s32 tv_field1_offset;
	व्योम *isr_handle;
	काष्ठा vb2_queue vq;

पूर्ण;

/*
 * Return true अगर rotation is 90 or 270
 */
अटल अंतरभूत पूर्णांक is_rotation_90_or_270(स्थिर काष्ठा omap_vout_device *vout)
अणु
	वापस (vout->rotation == dss_rotation_90_degree ||
			vout->rotation == dss_rotation_270_degree);
पूर्ण

/*
 * Return true अगर rotation is enabled
 */
अटल अंतरभूत पूर्णांक is_rotation_enabled(स्थिर काष्ठा omap_vout_device *vout)
अणु
	वापस vout->rotation || vout->mirror;
पूर्ण

/*
 * Reverse the rotation degree अगर mirroring is enabled
 */
अटल अंतरभूत पूर्णांक calc_rotation(स्थिर काष्ठा omap_vout_device *vout)
अणु
	अगर (!vout->mirror)
		वापस vout->rotation;

	चयन (vout->rotation) अणु
	हाल dss_rotation_90_degree:
		वापस dss_rotation_270_degree;
	हाल dss_rotation_270_degree:
		वापस dss_rotation_90_degree;
	हाल dss_rotation_180_degree:
		वापस dss_rotation_0_degree;
	शेष:
		वापस dss_rotation_180_degree;
	पूर्ण
पूर्ण

व्योम omap_vout_मुक्त_buffers(काष्ठा omap_vout_device *vout);
#पूर्ण_अगर	/* अगरndef OMAP_VOUTDEF_H */
