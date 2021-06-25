<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2020 NVIDIA CORPORATION.  All rights reserved.
 */

#अगर_अघोषित __TEGRA_VI_H__
#घोषणा __TEGRA_VI_H__

#समावेश <linux/host1x.h>
#समावेश <linux/list.h>

#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/रुको.h>

#समावेश <media/media-entity.h>
#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/videobuf2-v4l2.h>

#समावेश "csi.h"

#घोषणा V4L2_CID_TEGRA_SYNCPT_TIMEOUT_RETRY	(V4L2_CTRL_CLASS_CAMERA | 0x1001)

#घोषणा TEGRA_MIN_WIDTH		32U
#घोषणा TEGRA_MAX_WIDTH		32768U
#घोषणा TEGRA_MIN_HEIGHT	32U
#घोषणा TEGRA_MAX_HEIGHT	32768U

#घोषणा TEGRA_DEF_WIDTH		1920
#घोषणा TEGRA_DEF_HEIGHT	1080
#घोषणा TEGRA_IMAGE_FORMAT_DEF	32

#घोषणा MAX_FORMAT_NUM		64
#घोषणा SURFACE_ALIGN_BYTES	64

क्रमागत tegra_vi_pg_mode अणु
	TEGRA_VI_PG_DISABLED = 0,
	TEGRA_VI_PG_सूचीECT,
	TEGRA_VI_PG_PATCH,
पूर्ण;

/**
 * काष्ठा tegra_vi_ops - Tegra VI operations
 * @vi_start_streaming: starts media pipeline, subdevice streaming, sets up
 *		VI क्रम capture and runs capture start and capture finish
 *		kthपढ़ोs क्रम capturing frames to buffer and वापसs them back.
 * @vi_stop_streaming: stops media pipeline and subdevice streaming and वापसs
 *		back any queued buffers.
 */
काष्ठा tegra_vi_ops अणु
	पूर्णांक (*vi_start_streaming)(काष्ठा vb2_queue *vq, u32 count);
	व्योम (*vi_stop_streaming)(काष्ठा vb2_queue *vq);
पूर्ण;

/**
 * काष्ठा tegra_vi_soc - NVIDIA Tegra Video Input SoC काष्ठाure
 *
 * @video_क्रमmats: supported video क्रमmats
 * @nक्रमmats: total video क्रमmats
 * @ops: vi operations
 * @hw_revision: VI hw_revision
 * @vi_max_channels: supported max streaming channels
 * @vi_max_clk_hz: VI घड़ी max frequency
 */
काष्ठा tegra_vi_soc अणु
	स्थिर काष्ठा tegra_video_क्रमmat *video_क्रमmats;
	स्थिर अचिन्हित पूर्णांक nक्रमmats;
	स्थिर काष्ठा tegra_vi_ops *ops;
	u32 hw_revision;
	अचिन्हित पूर्णांक vi_max_channels;
	अचिन्हित पूर्णांक vi_max_clk_hz;
पूर्ण;

/**
 * काष्ठा tegra_vi - NVIDIA Tegra Video Input device काष्ठाure
 *
 * @dev: device काष्ठा
 * @client: host1x_client काष्ठा
 * @iomem: रेजिस्टर base
 * @clk: मुख्य घड़ी क्रम VI block
 * @vdd: vdd regulator क्रम VI hardware, normally it is avdd_dsi_csi
 * @soc: poपूर्णांकer to SoC data काष्ठाure
 * @ops: vi operations
 * @vi_chans: list head क्रम VI channels
 */
काष्ठा tegra_vi अणु
	काष्ठा device *dev;
	काष्ठा host1x_client client;
	व्योम __iomem *iomem;
	काष्ठा clk *clk;
	काष्ठा regulator *vdd;
	स्थिर काष्ठा tegra_vi_soc *soc;
	स्थिर काष्ठा tegra_vi_ops *ops;
	काष्ठा list_head vi_chans;
पूर्ण;

/**
 * काष्ठा tegra_vi_graph_entity - Entity in the video graph
 *
 * @asd: subdev asynchronous registration inक्रमmation
 * @entity: media entity from the corresponding V4L2 subdev
 * @subdev: V4L2 subdev
 */
काष्ठा tegra_vi_graph_entity अणु
	काष्ठा v4l2_async_subdev asd;
	काष्ठा media_entity *entity;
	काष्ठा v4l2_subdev *subdev;
पूर्ण;

/**
 * काष्ठा tegra_vi_channel - Tegra video channel
 *
 * @list: list head क्रम this entry
 * @video: V4L2 video device associated with the video channel
 * @video_lock: protects the @क्रमmat and @queue fields
 * @pad: media pad क्रम the video device entity
 *
 * @vi: Tegra video input device काष्ठाure
 * @frame_start_sp: host1x syncpoपूर्णांक poपूर्णांकer to synchronize programmed capture
 *		start condition with hardware frame start events through host1x
 *		syncpoपूर्णांक counters.
 * @mw_ack_sp: host1x syncpoपूर्णांक poपूर्णांकer to synchronize programmed memory ग_लिखो
 *		ack trigger condition with hardware memory ग_लिखो करोne at end of
 *		frame through host1x syncpoपूर्णांक counters.
 * @sp_incr_lock: protects cpu syncpoपूर्णांक increment.
 *
 * @kthपढ़ो_start_capture: kthपढ़ो to start capture of single frame when
 *		vb buffer is available. This thपढ़ो programs VI CSI hardware
 *		क्रम single frame capture and रुकोs क्रम frame start event from
 *		the hardware. On receiving frame start event, it wakes up
 *		kthपढ़ो_finish_capture thपढ़ो to रुको क्रम finishing frame data
 *		ग_लिखो to the memory. In हाल of missing frame start event, this
 *		thपढ़ो वापसs buffer back to vb with VB2_BUF_STATE_ERROR.
 * @start_रुको: रुकोqueue क्रम starting frame capture when buffer is available.
 * @kthपढ़ो_finish_capture: kthपढ़ो to finish the buffer capture and वापस to.
 *		This thपढ़ो is woken up by kthपढ़ो_start_capture on receiving
 *		frame start event from the hardware and this thपढ़ो रुकोs क्रम
 *		MW_ACK_DONE event which indicates completion of writing frame
 *		data to the memory. On receiving MW_ACK_DONE event, buffer is
 *		वापसed back to vb with VB2_BUF_STATE_DONE and in हाल of
 *		missing MW_ACK_DONE event, buffer is वापसed back to vb with
 *		VB2_BUF_STATE_ERROR.
 * @करोne_रुको: रुकोqueue क्रम finishing capture data ग_लिखोs to memory.
 *
 * @क्रमmat: active V4L2 pixel क्रमmat
 * @fmtinfo: क्रमmat inक्रमmation corresponding to the active @क्रमmat
 * @queue: vb2 buffers queue
 * @sequence: V4L2 buffers sequence number
 *
 * @capture: list of queued buffers क्रम capture
 * @start_lock: protects the capture queued list
 * @करोne: list of capture करोne queued buffers
 * @करोne_lock: protects the capture करोne queue list
 *
 * @portnos: VI channel port numbers
 * @totalports: total number of ports used क्रम this channel
 * @numgangports: number of ports combined together as a gang क्रम capture
 * @of_node: device node of VI channel
 *
 * @ctrl_handler: V4L2 control handler of this video channel
 * @syncpt_समयout_retry: syncpt समयout retry count क्रम the capture
 * @fmts_biपंचांगap: a biपंचांगap क्रम supported क्रमmats matching v4l2 subdev क्रमmats
 * @tpg_fmts_biपंचांगap: a biपंचांगap क्रम supported TPG क्रमmats
 * @pg_mode: test pattern generator mode (disabled/direct/patch)
 * @notअगरier: V4L2 asynchronous subdevs notअगरier
 */
काष्ठा tegra_vi_channel अणु
	काष्ठा list_head list;
	काष्ठा video_device video;
	/* protects the @क्रमmat and @queue fields */
	काष्ठा mutex video_lock;
	काष्ठा media_pad pad;

	काष्ठा tegra_vi *vi;
	काष्ठा host1x_syncpt *frame_start_sp[GANG_PORTS_MAX];
	काष्ठा host1x_syncpt *mw_ack_sp[GANG_PORTS_MAX];
	/* protects the cpu syncpoपूर्णांक increment */
	spinlock_t sp_incr_lock[GANG_PORTS_MAX];

	काष्ठा task_काष्ठा *kthपढ़ो_start_capture;
	रुको_queue_head_t start_रुको;
	काष्ठा task_काष्ठा *kthपढ़ो_finish_capture;
	रुको_queue_head_t करोne_रुको;

	काष्ठा v4l2_pix_क्रमmat क्रमmat;
	स्थिर काष्ठा tegra_video_क्रमmat *fmtinfo;
	काष्ठा vb2_queue queue;
	u32 sequence;

	काष्ठा list_head capture;
	/* protects the capture queued list */
	spinlock_t start_lock;
	काष्ठा list_head करोne;
	/* protects the capture करोne queue list */
	spinlock_t करोne_lock;

	अचिन्हित अक्षर portnos[GANG_PORTS_MAX];
	u8 totalports;
	u8 numgangports;
	काष्ठा device_node *of_node;

	काष्ठा v4l2_ctrl_handler ctrl_handler;
	अचिन्हित पूर्णांक syncpt_समयout_retry;
	DECLARE_BITMAP(fmts_biपंचांगap, MAX_FORMAT_NUM);
	DECLARE_BITMAP(tpg_fmts_biपंचांगap, MAX_FORMAT_NUM);
	क्रमागत tegra_vi_pg_mode pg_mode;

	काष्ठा v4l2_async_notअगरier notअगरier;
पूर्ण;

/**
 * काष्ठा tegra_channel_buffer - video channel buffer
 *
 * @buf: vb2 buffer base object
 * @queue: buffer list entry in the channel queued buffers list
 * @chan: channel that uses the buffer
 * @addr: Tegra IOVA buffer address क्रम VI output
 * @mw_ack_sp_thresh: MW_ACK_DONE syncpoपूर्णांक threshold corresponding
 *		      to the capture buffer.
 */
काष्ठा tegra_channel_buffer अणु
	काष्ठा vb2_v4l2_buffer buf;
	काष्ठा list_head queue;
	काष्ठा tegra_vi_channel *chan;
	dma_addr_t addr;
	u32 mw_ack_sp_thresh[GANG_PORTS_MAX];
पूर्ण;

/*
 * VI channel input data type क्रमागत.
 * These data type क्रमागत value माला_लो programmed पूर्णांकo corresponding Tegra VI
 * channel रेजिस्टर bits.
 */
क्रमागत tegra_image_dt अणु
	TEGRA_IMAGE_DT_YUV420_8 = 24,
	TEGRA_IMAGE_DT_YUV420_10,

	TEGRA_IMAGE_DT_YUV420CSPS_8 = 28,
	TEGRA_IMAGE_DT_YUV420CSPS_10,
	TEGRA_IMAGE_DT_YUV422_8,
	TEGRA_IMAGE_DT_YUV422_10,
	TEGRA_IMAGE_DT_RGB444,
	TEGRA_IMAGE_DT_RGB555,
	TEGRA_IMAGE_DT_RGB565,
	TEGRA_IMAGE_DT_RGB666,
	TEGRA_IMAGE_DT_RGB888,

	TEGRA_IMAGE_DT_RAW6 = 40,
	TEGRA_IMAGE_DT_RAW7,
	TEGRA_IMAGE_DT_RAW8,
	TEGRA_IMAGE_DT_RAW10,
	TEGRA_IMAGE_DT_RAW12,
	TEGRA_IMAGE_DT_RAW14,
पूर्ण;

/**
 * काष्ठा tegra_video_क्रमmat - Tegra video क्रमmat description
 *
 * @img_dt: image data type
 * @bit_width: क्रमmat width in bits per component
 * @code: media bus क्रमmat code
 * @bpp: bytes per pixel (when stored in memory)
 * @img_fmt: image क्रमmat
 * @fourcc: V4L2 pixel क्रमmat FCC identअगरier
 */
काष्ठा tegra_video_क्रमmat अणु
	क्रमागत tegra_image_dt img_dt;
	अचिन्हित पूर्णांक bit_width;
	अचिन्हित पूर्णांक code;
	अचिन्हित पूर्णांक bpp;
	u32 img_fmt;
	u32 fourcc;
पूर्ण;

#अगर defined(CONFIG_ARCH_TEGRA_210_SOC)
बाह्य स्थिर काष्ठा tegra_vi_soc tegra210_vi_soc;
#पूर्ण_अगर

काष्ठा v4l2_subdev *
tegra_channel_get_remote_csi_subdev(काष्ठा tegra_vi_channel *chan);
काष्ठा v4l2_subdev *
tegra_channel_get_remote_source_subdev(काष्ठा tegra_vi_channel *chan);
पूर्णांक tegra_channel_set_stream(काष्ठा tegra_vi_channel *chan, bool on);
व्योम tegra_channel_release_buffers(काष्ठा tegra_vi_channel *chan,
				   क्रमागत vb2_buffer_state state);
व्योम tegra_channels_cleanup(काष्ठा tegra_vi *vi);
#पूर्ण_अगर
