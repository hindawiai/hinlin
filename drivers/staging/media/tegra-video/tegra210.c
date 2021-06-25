<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 NVIDIA CORPORATION.  All rights reserved.
 */

/*
 * This source file contains Tegra210 supported video क्रमmats,
 * VI and CSI SoC specअगरic data, operations and रेजिस्टरs accessors.
 */
#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk/tegra.h>
#समावेश <linux/delay.h>
#समावेश <linux/host1x.h>
#समावेश <linux/kthपढ़ो.h>

#समावेश "csi.h"
#समावेश "vi.h"

#घोषणा TEGRA_VI_SYNCPT_WAIT_TIMEOUT			msecs_to_jअगरfies(200)

/* Tegra210 VI रेजिस्टरs */
#घोषणा TEGRA_VI_CFG_VI_INCR_SYNCPT			0x000
#घोषणा   VI_CFG_VI_INCR_SYNCPT_COND(x)			(((x) & 0xff) << 8)
#घोषणा   VI_CSI_PP_FRAME_START(port)			(5 + (port) * 4)
#घोषणा   VI_CSI_MW_ACK_DONE(port)			(7 + (port) * 4)
#घोषणा TEGRA_VI_CFG_VI_INCR_SYNCPT_CNTRL		0x004
#घोषणा   VI_INCR_SYNCPT_NO_STALL			BIT(8)
#घोषणा TEGRA_VI_CFG_VI_INCR_SYNCPT_ERROR		0x008
#घोषणा TEGRA_VI_CFG_CG_CTRL				0x0b8
#घोषणा   VI_CG_2ND_LEVEL_EN				0x1

/* Tegra210 VI CSI रेजिस्टरs */
#घोषणा TEGRA_VI_CSI_SW_RESET				0x000
#घोषणा TEGRA_VI_CSI_SINGLE_SHOT			0x004
#घोषणा   SINGLE_SHOT_CAPTURE				0x1
#घोषणा TEGRA_VI_CSI_IMAGE_DEF				0x00c
#घोषणा   BYPASS_PXL_TRANSFORM_OFFSET			24
#घोषणा   IMAGE_DEF_FORMAT_OFFSET			16
#घोषणा   IMAGE_DEF_DEST_MEM				0x1
#घोषणा TEGRA_VI_CSI_IMAGE_SIZE				0x018
#घोषणा   IMAGE_SIZE_HEIGHT_OFFSET			16
#घोषणा TEGRA_VI_CSI_IMAGE_SIZE_WC			0x01c
#घोषणा TEGRA_VI_CSI_IMAGE_DT				0x020
#घोषणा TEGRA_VI_CSI_SURFACE0_OFFSET_MSB		0x024
#घोषणा TEGRA_VI_CSI_SURFACE0_OFFSET_LSB		0x028
#घोषणा TEGRA_VI_CSI_SURFACE1_OFFSET_MSB		0x02c
#घोषणा TEGRA_VI_CSI_SURFACE1_OFFSET_LSB		0x030
#घोषणा TEGRA_VI_CSI_SURFACE2_OFFSET_MSB		0x034
#घोषणा TEGRA_VI_CSI_SURFACE2_OFFSET_LSB		0x038
#घोषणा TEGRA_VI_CSI_SURFACE0_STRIDE			0x054
#घोषणा TEGRA_VI_CSI_SURFACE1_STRIDE			0x058
#घोषणा TEGRA_VI_CSI_SURFACE2_STRIDE			0x05c
#घोषणा TEGRA_VI_CSI_SURFACE_HEIGHT0			0x060
#घोषणा TEGRA_VI_CSI_ERROR_STATUS			0x084

/* Tegra210 CSI Pixel Parser रेजिस्टरs: Starts from 0x838, offset 0x0 */
#घोषणा TEGRA_CSI_INPUT_STREAM_CONTROL                  0x000
#घोषणा   CSI_SKIP_PACKET_THRESHOLD_OFFSET		16
#घोषणा TEGRA_CSI_PIXEL_STREAM_CONTROL0			0x004
#घोषणा   CSI_PP_PACKET_HEADER_SENT			BIT(4)
#घोषणा   CSI_PP_DATA_IDENTIFIER_ENABLE			BIT(5)
#घोषणा   CSI_PP_WORD_COUNT_SELECT_HEADER		BIT(6)
#घोषणा   CSI_PP_CRC_CHECK_ENABLE			BIT(7)
#घोषणा   CSI_PP_WC_CHECK				BIT(8)
#घोषणा   CSI_PP_OUTPUT_FORMAT_STORE			(0x3 << 16)
#घोषणा   CSI_PPA_PAD_LINE_NOPAD			(0x2 << 24)
#घोषणा   CSI_PP_HEADER_EC_DISABLE			(0x1 << 27)
#घोषणा   CSI_PPA_PAD_FRAME_NOPAD			(0x2 << 28)
#घोषणा TEGRA_CSI_PIXEL_STREAM_CONTROL1                 0x008
#घोषणा   CSI_PP_TOP_FIELD_FRAME_OFFSET			0
#घोषणा   CSI_PP_TOP_FIELD_FRAME_MASK_OFFSET		4
#घोषणा TEGRA_CSI_PIXEL_STREAM_GAP                      0x00c
#घोषणा   PP_FRAME_MIN_GAP_OFFSET			16
#घोषणा TEGRA_CSI_PIXEL_STREAM_PP_COMMAND               0x010
#घोषणा   CSI_PP_ENABLE					0x1
#घोषणा   CSI_PP_DISABLE				0x2
#घोषणा   CSI_PP_RST					0x3
#घोषणा   CSI_PP_SINGLE_SHOT_ENABLE			(0x1 << 2)
#घोषणा   CSI_PP_START_MARKER_FRAME_MAX_OFFSET		12
#घोषणा TEGRA_CSI_PIXEL_STREAM_EXPECTED_FRAME           0x014
#घोषणा TEGRA_CSI_PIXEL_PARSER_INTERRUPT_MASK           0x018
#घोषणा TEGRA_CSI_PIXEL_PARSER_STATUS                   0x01c

/* Tegra210 CSI PHY रेजिस्टरs */
/* CSI_PHY_CIL_COMMAND_0 offset 0x0d0 from TEGRA_CSI_PIXEL_PARSER_0_BASE */
#घोषणा TEGRA_CSI_PHY_CIL_COMMAND                       0x0d0
#घोषणा   CSI_A_PHY_CIL_NOP				0x0
#घोषणा   CSI_A_PHY_CIL_ENABLE				0x1
#घोषणा   CSI_A_PHY_CIL_DISABLE				0x2
#घोषणा   CSI_A_PHY_CIL_ENABLE_MASK			0x3
#घोषणा   CSI_B_PHY_CIL_NOP				(0x0 << 8)
#घोषणा   CSI_B_PHY_CIL_ENABLE				(0x1 << 8)
#घोषणा   CSI_B_PHY_CIL_DISABLE				(0x2 << 8)
#घोषणा   CSI_B_PHY_CIL_ENABLE_MASK			(0x3 << 8)

#घोषणा TEGRA_CSI_CIL_PAD_CONFIG0                       0x000
#घोषणा   BRICK_CLOCK_A_4X				(0x1 << 16)
#घोषणा   BRICK_CLOCK_B_4X				(0x2 << 16)
#घोषणा TEGRA_CSI_CIL_PAD_CONFIG1                       0x004
#घोषणा TEGRA_CSI_CIL_PHY_CONTROL                       0x008
#घोषणा   CLK_SETTLE_MASK				GENMASK(13, 8)
#घोषणा   THS_SETTLE_MASK				GENMASK(5, 0)
#घोषणा TEGRA_CSI_CIL_INTERRUPT_MASK                    0x00c
#घोषणा TEGRA_CSI_CIL_STATUS                            0x010
#घोषणा TEGRA_CSI_CILX_STATUS                           0x014
#घोषणा TEGRA_CSI_CIL_SW_SENSOR_RESET                   0x020

#घोषणा TEGRA_CSI_PATTERN_GENERATOR_CTRL		0x000
#घोषणा   PG_MODE_OFFSET				2
#घोषणा   PG_ENABLE					0x1
#घोषणा   PG_DISABLE					0x0
#घोषणा TEGRA_CSI_PG_BLANK				0x004
#घोषणा   PG_VBLANK_OFFSET				16
#घोषणा TEGRA_CSI_PG_PHASE				0x008
#घोषणा TEGRA_CSI_PG_RED_FREQ				0x00c
#घोषणा   PG_RED_VERT_INIT_FREQ_OFFSET			16
#घोषणा   PG_RED_HOR_INIT_FREQ_OFFSET			0
#घोषणा TEGRA_CSI_PG_RED_FREQ_RATE			0x010
#घोषणा TEGRA_CSI_PG_GREEN_FREQ				0x014
#घोषणा   PG_GREEN_VERT_INIT_FREQ_OFFSET		16
#घोषणा   PG_GREEN_HOR_INIT_FREQ_OFFSET			0
#घोषणा TEGRA_CSI_PG_GREEN_FREQ_RATE			0x018
#घोषणा TEGRA_CSI_PG_BLUE_FREQ				0x01c
#घोषणा   PG_BLUE_VERT_INIT_FREQ_OFFSET			16
#घोषणा   PG_BLUE_HOR_INIT_FREQ_OFFSET			0
#घोषणा TEGRA_CSI_PG_BLUE_FREQ_RATE			0x020
#घोषणा TEGRA_CSI_PG_AOHDR				0x024
#घोषणा TEGRA_CSI_CSI_SW_STATUS_RESET			0x214
#घोषणा TEGRA_CSI_CLKEN_OVERRIDE			0x218

#घोषणा TEGRA210_CSI_PORT_OFFSET			0x34
#घोषणा TEGRA210_CSI_CIL_OFFSET				0x0f4
#घोषणा TEGRA210_CSI_TPG_OFFSET				0x18c

#घोषणा CSI_PP_OFFSET(block)				((block) * 0x800)
#घोषणा TEGRA210_VI_CSI_BASE(x)				(0x100 + (x) * 0x100)

/* Tegra210 VI रेजिस्टरs accessors */
अटल व्योम tegra_vi_ग_लिखो(काष्ठा tegra_vi_channel *chan, अचिन्हित पूर्णांक addr,
			   u32 val)
अणु
	ग_लिखोl_relaxed(val, chan->vi->iomem + addr);
पूर्ण

अटल u32 tegra_vi_पढ़ो(काष्ठा tegra_vi_channel *chan, अचिन्हित पूर्णांक addr)
अणु
	वापस पढ़ोl_relaxed(chan->vi->iomem + addr);
पूर्ण

/* Tegra210 VI_CSI रेजिस्टरs accessors */
अटल व्योम vi_csi_ग_लिखो(काष्ठा tegra_vi_channel *chan, u8 portno,
			 अचिन्हित पूर्णांक addr, u32 val)
अणु
	व्योम __iomem *vi_csi_base;

	vi_csi_base = chan->vi->iomem + TEGRA210_VI_CSI_BASE(portno);

	ग_लिखोl_relaxed(val, vi_csi_base + addr);
पूर्ण

अटल u32 vi_csi_पढ़ो(काष्ठा tegra_vi_channel *chan, u8 portno,
		       अचिन्हित पूर्णांक addr)
अणु
	व्योम __iomem *vi_csi_base;

	vi_csi_base = chan->vi->iomem + TEGRA210_VI_CSI_BASE(portno);

	वापस पढ़ोl_relaxed(vi_csi_base + addr);
पूर्ण

/*
 * Tegra210 VI channel capture operations
 */
अटल पूर्णांक tegra_channel_capture_setup(काष्ठा tegra_vi_channel *chan,
				       u8 portno)
अणु
	u32 height = chan->क्रमmat.height;
	u32 width = chan->क्रमmat.width;
	u32 क्रमmat = chan->fmtinfo->img_fmt;
	u32 data_type = chan->fmtinfo->img_dt;
	u32 word_count = (width * chan->fmtinfo->bit_width) / 8;
	u32 bypass_pixel_transक्रमm = BIT(BYPASS_PXL_TRANSFORM_OFFSET);

	/*
	 * VI Pixel transक्रमmation unit converts source pixels data क्रमmat
	 * पूर्णांकo selected destination pixel क्रमmat and aligns properly जबतक
	 * पूर्णांकerfacing with memory packer.
	 * This pixel transक्रमmation should be enabled क्रम YUV and RGB
	 * क्रमmats and should be bypassed क्रम RAW क्रमmats as RAW क्रमmats
	 * only support direct to memory.
	 */
	अगर (chan->pg_mode || data_type == TEGRA_IMAGE_DT_YUV422_8 ||
	    data_type == TEGRA_IMAGE_DT_RGB888)
		bypass_pixel_transक्रमm = 0;

	/*
	 * For x8 source streaming, the source image is split onto two x4 ports
	 * with left half to first x4 port and right half to second x4 port.
	 * So, use split width and corresponding word count क्रम each x4 port.
	 */
	अगर (chan->numgangports > 1) अणु
		width = width >> 1;
		word_count = (width * chan->fmtinfo->bit_width) / 8;
	पूर्ण

	vi_csi_ग_लिखो(chan, portno, TEGRA_VI_CSI_ERROR_STATUS, 0xffffffff);
	vi_csi_ग_लिखो(chan, portno, TEGRA_VI_CSI_IMAGE_DEF,
		     bypass_pixel_transक्रमm |
		     (क्रमmat << IMAGE_DEF_FORMAT_OFFSET) |
		     IMAGE_DEF_DEST_MEM);
	vi_csi_ग_लिखो(chan, portno, TEGRA_VI_CSI_IMAGE_DT, data_type);
	vi_csi_ग_लिखो(chan, portno, TEGRA_VI_CSI_IMAGE_SIZE_WC, word_count);
	vi_csi_ग_लिखो(chan, portno, TEGRA_VI_CSI_IMAGE_SIZE,
		     (height << IMAGE_SIZE_HEIGHT_OFFSET) | width);
	वापस 0;
पूर्ण

अटल व्योम tegra_channel_vi_soft_reset(काष्ठा tegra_vi_channel *chan,
					u8 portno)
अणु
	/* disable घड़ी gating to enable continuous घड़ी */
	tegra_vi_ग_लिखो(chan, TEGRA_VI_CFG_CG_CTRL, 0);
	/*
	 * Soft reset memory client पूर्णांकerface, pixel क्रमmat logic, sensor
	 * control logic, and a shaकरोw copy logic to bring VI to clean state.
	 */
	vi_csi_ग_लिखो(chan, portno, TEGRA_VI_CSI_SW_RESET, 0xf);
	usleep_range(100, 200);
	vi_csi_ग_लिखो(chan, portno, TEGRA_VI_CSI_SW_RESET, 0x0);

	/* enable back VI घड़ी gating */
	tegra_vi_ग_लिखो(chan, TEGRA_VI_CFG_CG_CTRL, VI_CG_2ND_LEVEL_EN);
पूर्ण

अटल व्योम tegra_channel_capture_error_recover(काष्ठा tegra_vi_channel *chan,
						u8 portno)
अणु
	काष्ठा v4l2_subdev *subdev;
	u32 val;

	/*
	 * Recover VI and CSI hardware blocks in हाल of missing frame start
	 * events due to source not streaming or noisy csi inमाला_दो from the
	 * बाह्यal source or many outstanding frame start or MW_ACK_DONE
	 * events which can cause CSI and VI hardware hang.
	 * This helps to have a clean capture क्रम next frame.
	 */
	val = vi_csi_पढ़ो(chan, portno, TEGRA_VI_CSI_ERROR_STATUS);
	dev_dbg(&chan->video.dev, "TEGRA_VI_CSI_ERROR_STATUS 0x%08x\n", val);
	vi_csi_ग_लिखो(chan, portno, TEGRA_VI_CSI_ERROR_STATUS, val);

	val = tegra_vi_पढ़ो(chan, TEGRA_VI_CFG_VI_INCR_SYNCPT_ERROR);
	dev_dbg(&chan->video.dev,
		"TEGRA_VI_CFG_VI_INCR_SYNCPT_ERROR 0x%08x\n", val);
	tegra_vi_ग_लिखो(chan, TEGRA_VI_CFG_VI_INCR_SYNCPT_ERROR, val);

	/* recover VI by issuing software reset and re-setup क्रम capture */
	tegra_channel_vi_soft_reset(chan, portno);
	tegra_channel_capture_setup(chan, portno);

	/* recover CSI block */
	subdev = tegra_channel_get_remote_csi_subdev(chan);
	tegra_csi_error_recover(subdev);
पूर्ण

अटल काष्ठा tegra_channel_buffer *
dequeue_buf_करोne(काष्ठा tegra_vi_channel *chan)
अणु
	काष्ठा tegra_channel_buffer *buf = शून्य;

	spin_lock(&chan->करोne_lock);
	अगर (list_empty(&chan->करोne)) अणु
		spin_unlock(&chan->करोne_lock);
		वापस शून्य;
	पूर्ण

	buf = list_first_entry(&chan->करोne,
			       काष्ठा tegra_channel_buffer, queue);
	अगर (buf)
		list_del_init(&buf->queue);
	spin_unlock(&chan->करोne_lock);

	वापस buf;
पूर्ण

अटल व्योम release_buffer(काष्ठा tegra_vi_channel *chan,
			   काष्ठा tegra_channel_buffer *buf,
			   क्रमागत vb2_buffer_state state)
अणु
	काष्ठा vb2_v4l2_buffer *vb = &buf->buf;

	vb->sequence = chan->sequence++;
	vb->field = V4L2_FIELD_NONE;
	vb->vb2_buf.बारtamp = kसमय_get_ns();
	vb2_buffer_करोne(&vb->vb2_buf, state);
पूर्ण

अटल व्योम tegra_channel_vi_buffer_setup(काष्ठा tegra_vi_channel *chan,
					  u8 portno, u32 buf_offset,
					  काष्ठा tegra_channel_buffer *buf)
अणु
	पूर्णांक bytesperline = chan->क्रमmat.bytesperline;
	u32 sizeimage = chan->क्रमmat.sizeimage;

	/* program buffer address by using surface 0 */
	vi_csi_ग_लिखो(chan, portno, TEGRA_VI_CSI_SURFACE0_OFFSET_MSB,
		     ((u64)buf->addr + buf_offset) >> 32);
	vi_csi_ग_लिखो(chan, portno, TEGRA_VI_CSI_SURFACE0_OFFSET_LSB,
		     buf->addr + buf_offset);
	vi_csi_ग_लिखो(chan, portno, TEGRA_VI_CSI_SURFACE0_STRIDE, bytesperline);

	अगर (chan->fmtinfo->fourcc != V4L2_PIX_FMT_NV16)
		वापस;
	/*
	 * Program surface 1 क्रम UV plane with offset sizeimage from Y plane.
	 */
	vi_csi_ग_लिखो(chan, portno, TEGRA_VI_CSI_SURFACE1_OFFSET_MSB,
		     (((u64)buf->addr + sizeimage / 2) + buf_offset) >> 32);
	vi_csi_ग_लिखो(chan, portno, TEGRA_VI_CSI_SURFACE1_OFFSET_LSB,
		     buf->addr + sizeimage / 2 + buf_offset);
	vi_csi_ग_लिखो(chan, portno, TEGRA_VI_CSI_SURFACE1_STRIDE, bytesperline);
पूर्ण

अटल पूर्णांक tegra_channel_capture_frame(काष्ठा tegra_vi_channel *chan,
				       काष्ठा tegra_channel_buffer *buf)
अणु
	u32 thresh, value, frame_start, mw_ack_करोne;
	u32 fs_thresh[GANG_PORTS_MAX];
	u8 *portnos = chan->portnos;
	पूर्णांक gang_bpl = (chan->क्रमmat.width >> 1) * chan->fmtinfo->bpp;
	u32 buf_offset;
	bool capture_समयकरोut = false;
	पूर्णांक err, i;

	क्रम (i = 0; i < chan->numgangports; i++) अणु
		/*
		 * Align buffers side-by-side क्रम all consecutive x4 ports
		 * in gang ports using bytes per line based on source split
		 * width.
		 */
		buf_offset = i * roundup(gang_bpl, SURFACE_ALIGN_BYTES);
		tegra_channel_vi_buffer_setup(chan, portnos[i], buf_offset,
					      buf);

		/*
		 * Tegra VI block पूर्णांकeracts with host1x syncpt to synchronize
		 * programmed condition and hardware operation क्रम capture.
		 * Frame start and Memory ग_लिखो acknowledge syncpts has their
		 * own FIFO of depth 2.
		 *
		 * Syncpoपूर्णांक trigger conditions set through VI_INCR_SYNCPT
		 * रेजिस्टर are added to HW syncpt FIFO and when HW triggers,
		 * syncpt condition is हटाओd from the FIFO and counter at
		 * syncpoपूर्णांक index will be incremented by the hardware and
		 * software can रुको क्रम counter to reach threshold to
		 * synchronize capturing frame with hardware capture events.
		 */

		/* increase channel syncpoपूर्णांक threshold क्रम FRAME_START */
		thresh = host1x_syncpt_incr_max(chan->frame_start_sp[i], 1);
		fs_thresh[i] = thresh;

		/* Program FRAME_START trigger condition syncpt request */
		frame_start = VI_CSI_PP_FRAME_START(portnos[i]);
		value = VI_CFG_VI_INCR_SYNCPT_COND(frame_start) |
			host1x_syncpt_id(chan->frame_start_sp[i]);
		tegra_vi_ग_लिखो(chan, TEGRA_VI_CFG_VI_INCR_SYNCPT, value);

		/* increase channel syncpoपूर्णांक threshold क्रम MW_ACK_DONE */
		thresh = host1x_syncpt_incr_max(chan->mw_ack_sp[i], 1);
		buf->mw_ack_sp_thresh[i] = thresh;

		/* Program MW_ACK_DONE trigger condition syncpt request */
		mw_ack_करोne = VI_CSI_MW_ACK_DONE(portnos[i]);
		value = VI_CFG_VI_INCR_SYNCPT_COND(mw_ack_करोne) |
			host1x_syncpt_id(chan->mw_ack_sp[i]);
		tegra_vi_ग_लिखो(chan, TEGRA_VI_CFG_VI_INCR_SYNCPT, value);
	पूर्ण

	/* enable single shot capture after all ganged ports are पढ़ोy */
	क्रम (i = 0; i < chan->numgangports; i++)
		vi_csi_ग_लिखो(chan, portnos[i], TEGRA_VI_CSI_SINGLE_SHOT,
			     SINGLE_SHOT_CAPTURE);

	क्रम (i = 0; i < chan->numgangports; i++) अणु
		/*
		 * Wait क्रम syncpt counter to reach frame start event threshold
		 */
		err = host1x_syncpt_रुको(chan->frame_start_sp[i], fs_thresh[i],
					 TEGRA_VI_SYNCPT_WAIT_TIMEOUT, &value);
		अगर (err) अणु
			capture_समयकरोut = true;
			/* increment syncpoपूर्णांक counter क्रम समयकरोut events */
			host1x_syncpt_incr(chan->frame_start_sp[i]);
			spin_lock(&chan->sp_incr_lock[i]);
			host1x_syncpt_incr(chan->mw_ack_sp[i]);
			spin_unlock(&chan->sp_incr_lock[i]);
			/* clear errors and recover */
			tegra_channel_capture_error_recover(chan, portnos[i]);
		पूर्ण
	पूर्ण

	अगर (capture_समयकरोut) अणु
		dev_err_ratelimited(&chan->video.dev,
				    "frame start syncpt timeout: %d\n", err);
		release_buffer(chan, buf, VB2_BUF_STATE_ERROR);
		वापस err;
	पूर्ण

	/* move buffer to capture करोne queue */
	spin_lock(&chan->करोne_lock);
	list_add_tail(&buf->queue, &chan->करोne);
	spin_unlock(&chan->करोne_lock);

	/* रुको up kthपढ़ो क्रम capture करोne */
	wake_up_पूर्णांकerruptible(&chan->करोne_रुको);

	वापस 0;
पूर्ण

अटल व्योम tegra_channel_capture_करोne(काष्ठा tegra_vi_channel *chan,
				       काष्ठा tegra_channel_buffer *buf)
अणु
	क्रमागत vb2_buffer_state state = VB2_BUF_STATE_DONE;
	u32 value;
	bool capture_समयकरोut = false;
	पूर्णांक ret, i;

	क्रम (i = 0; i < chan->numgangports; i++) अणु
		/*
		 * Wait क्रम syncpt counter to reach MW_ACK_DONE event threshold
		 */
		ret = host1x_syncpt_रुको(chan->mw_ack_sp[i],
					 buf->mw_ack_sp_thresh[i],
					 TEGRA_VI_SYNCPT_WAIT_TIMEOUT, &value);
		अगर (ret) अणु
			capture_समयकरोut = true;
			state = VB2_BUF_STATE_ERROR;
			/* increment syncpoपूर्णांक counter क्रम समयकरोut event */
			spin_lock(&chan->sp_incr_lock[i]);
			host1x_syncpt_incr(chan->mw_ack_sp[i]);
			spin_unlock(&chan->sp_incr_lock[i]);
		पूर्ण
	पूर्ण

	अगर (capture_समयकरोut)
		dev_err_ratelimited(&chan->video.dev,
				    "MW_ACK_DONE syncpt timeout: %d\n", ret);
	release_buffer(chan, buf, state);
पूर्ण

अटल पूर्णांक chan_capture_kthपढ़ो_start(व्योम *data)
अणु
	काष्ठा tegra_vi_channel *chan = data;
	काष्ठा tegra_channel_buffer *buf;
	अचिन्हित पूर्णांक retries = 0;
	पूर्णांक err = 0;

	जबतक (1) अणु
		/*
		 * Source is not streaming अगर error is non-zero.
		 * So, करो not dequeue buffers on error and let the thपढ़ो sleep
		 * till kthपढ़ो stop संकेत is received.
		 */
		रुको_event_पूर्णांकerruptible(chan->start_रुको,
					 kthपढ़ो_should_stop() ||
					 (!list_empty(&chan->capture) &&
					 !err));

		अगर (kthपढ़ो_should_stop())
			अवरोध;

		/* dequeue the buffer and start capture */
		spin_lock(&chan->start_lock);
		अगर (list_empty(&chan->capture)) अणु
			spin_unlock(&chan->start_lock);
			जारी;
		पूर्ण

		buf = list_first_entry(&chan->capture,
				       काष्ठा tegra_channel_buffer, queue);
		list_del_init(&buf->queue);
		spin_unlock(&chan->start_lock);

		err = tegra_channel_capture_frame(chan, buf);
		अगर (!err) अणु
			retries = 0;
			जारी;
		पूर्ण

		अगर (retries++ > chan->syncpt_समयout_retry)
			vb2_queue_error(&chan->queue);
		अन्यथा
			err = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक chan_capture_kthपढ़ो_finish(व्योम *data)
अणु
	काष्ठा tegra_vi_channel *chan = data;
	काष्ठा tegra_channel_buffer *buf;

	जबतक (1) अणु
		रुको_event_पूर्णांकerruptible(chan->करोne_रुको,
					 !list_empty(&chan->करोne) ||
					 kthपढ़ो_should_stop());

		/* dequeue buffers and finish capture */
		buf = dequeue_buf_करोne(chan);
		जबतक (buf) अणु
			tegra_channel_capture_करोne(chan, buf);
			buf = dequeue_buf_करोne(chan);
		पूर्ण

		अगर (kthपढ़ो_should_stop())
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_vi_start_streaming(काष्ठा vb2_queue *vq, u32 count)
अणु
	काष्ठा tegra_vi_channel *chan = vb2_get_drv_priv(vq);
	काष्ठा media_pipeline *pipe = &chan->video.pipe;
	u32 val;
	u8 *portnos = chan->portnos;
	पूर्णांक ret, i;

	tegra_vi_ग_लिखो(chan, TEGRA_VI_CFG_CG_CTRL, VI_CG_2ND_LEVEL_EN);

	/* clear syncpt errors */
	val = tegra_vi_पढ़ो(chan, TEGRA_VI_CFG_VI_INCR_SYNCPT_ERROR);
	tegra_vi_ग_लिखो(chan, TEGRA_VI_CFG_VI_INCR_SYNCPT_ERROR, val);

	/*
	 * Sync poपूर्णांक FIFO full stalls the host पूर्णांकerface.
	 * Setting NO_STALL will drop INCR_SYNCPT methods when fअगरos are
	 * full and the corresponding condition bits in INCR_SYNCPT_ERROR
	 * रेजिस्टर will be set.
	 * This allows SW to process error recovery.
	 */
	tegra_vi_ग_लिखो(chan, TEGRA_VI_CFG_VI_INCR_SYNCPT_CNTRL,
		       VI_INCR_SYNCPT_NO_STALL);

	/* start the pipeline */
	ret = media_pipeline_start(&chan->video.entity, pipe);
	अगर (ret < 0)
		जाओ error_pipeline_start;

	/* clear csi errors and करो capture setup क्रम all ports in gang mode */
	क्रम (i = 0; i < chan->numgangports; i++) अणु
		val = vi_csi_पढ़ो(chan, portnos[i], TEGRA_VI_CSI_ERROR_STATUS);
		vi_csi_ग_लिखो(chan, portnos[i], TEGRA_VI_CSI_ERROR_STATUS, val);

		tegra_channel_capture_setup(chan, portnos[i]);
	पूर्ण

	ret = tegra_channel_set_stream(chan, true);
	अगर (ret < 0)
		जाओ error_set_stream;

	chan->sequence = 0;

	/* start kthपढ़ोs to capture data to buffer and वापस them */
	chan->kthपढ़ो_start_capture = kthपढ़ो_run(chan_capture_kthपढ़ो_start,
						  chan, "%s:0",
						  chan->video.name);
	अगर (IS_ERR(chan->kthपढ़ो_start_capture)) अणु
		ret = PTR_ERR(chan->kthपढ़ो_start_capture);
		chan->kthपढ़ो_start_capture = शून्य;
		dev_err(&chan->video.dev,
			"failed to run capture start kthread: %d\n", ret);
		जाओ error_kthपढ़ो_start;
	पूर्ण

	chan->kthपढ़ो_finish_capture = kthपढ़ो_run(chan_capture_kthपढ़ो_finish,
						   chan, "%s:1",
						   chan->video.name);
	अगर (IS_ERR(chan->kthपढ़ो_finish_capture)) अणु
		ret = PTR_ERR(chan->kthपढ़ो_finish_capture);
		chan->kthपढ़ो_finish_capture = शून्य;
		dev_err(&chan->video.dev,
			"failed to run capture finish kthread: %d\n", ret);
		जाओ error_kthपढ़ो_करोne;
	पूर्ण

	वापस 0;

error_kthपढ़ो_करोne:
	kthपढ़ो_stop(chan->kthपढ़ो_start_capture);
error_kthपढ़ो_start:
	tegra_channel_set_stream(chan, false);
error_set_stream:
	media_pipeline_stop(&chan->video.entity);
error_pipeline_start:
	tegra_channel_release_buffers(chan, VB2_BUF_STATE_QUEUED);
	वापस ret;
पूर्ण

अटल व्योम tegra210_vi_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा tegra_vi_channel *chan = vb2_get_drv_priv(vq);

	अगर (chan->kthपढ़ो_start_capture) अणु
		kthपढ़ो_stop(chan->kthपढ़ो_start_capture);
		chan->kthपढ़ो_start_capture = शून्य;
	पूर्ण

	अगर (chan->kthपढ़ो_finish_capture) अणु
		kthपढ़ो_stop(chan->kthपढ़ो_finish_capture);
		chan->kthपढ़ो_finish_capture = शून्य;
	पूर्ण

	tegra_channel_release_buffers(chan, VB2_BUF_STATE_ERROR);
	tegra_channel_set_stream(chan, false);
	media_pipeline_stop(&chan->video.entity);
पूर्ण

/*
 * Tegra210 VI Pixel memory क्रमmat क्रमागत.
 * These क्रमmat क्रमागत value माला_लो programmed पूर्णांकo corresponding Tegra VI
 * channel रेजिस्टर bits.
 */
क्रमागत tegra210_image_क्रमmat अणु
	TEGRA210_IMAGE_FORMAT_T_L8 = 16,

	TEGRA210_IMAGE_FORMAT_T_R16_I = 32,
	TEGRA210_IMAGE_FORMAT_T_B5G6R5,
	TEGRA210_IMAGE_FORMAT_T_R5G6B5,
	TEGRA210_IMAGE_FORMAT_T_A1B5G5R5,
	TEGRA210_IMAGE_FORMAT_T_A1R5G5B5,
	TEGRA210_IMAGE_FORMAT_T_B5G5R5A1,
	TEGRA210_IMAGE_FORMAT_T_R5G5B5A1,
	TEGRA210_IMAGE_FORMAT_T_A4B4G4R4,
	TEGRA210_IMAGE_FORMAT_T_A4R4G4B4,
	TEGRA210_IMAGE_FORMAT_T_B4G4R4A4,
	TEGRA210_IMAGE_FORMAT_T_R4G4B4A4,

	TEGRA210_IMAGE_FORMAT_T_A8B8G8R8 = 64,
	TEGRA210_IMAGE_FORMAT_T_A8R8G8B8,
	TEGRA210_IMAGE_FORMAT_T_B8G8R8A8,
	TEGRA210_IMAGE_FORMAT_T_R8G8B8A8,
	TEGRA210_IMAGE_FORMAT_T_A2B10G10R10,
	TEGRA210_IMAGE_FORMAT_T_A2R10G10B10,
	TEGRA210_IMAGE_FORMAT_T_B10G10R10A2,
	TEGRA210_IMAGE_FORMAT_T_R10G10B10A2,

	TEGRA210_IMAGE_FORMAT_T_A8Y8U8V8 = 193,
	TEGRA210_IMAGE_FORMAT_T_V8U8Y8A8,

	TEGRA210_IMAGE_FORMAT_T_A2Y10U10V10 = 197,
	TEGRA210_IMAGE_FORMAT_T_V10U10Y10A2,
	TEGRA210_IMAGE_FORMAT_T_Y8_U8__Y8_V8,
	TEGRA210_IMAGE_FORMAT_T_Y8_V8__Y8_U8,
	TEGRA210_IMAGE_FORMAT_T_U8_Y8__V8_Y8,
	TEGRA210_IMAGE_FORMAT_T_V8_Y8__U8_Y8,

	TEGRA210_IMAGE_FORMAT_T_Y8__U8__V8_N444 = 224,
	TEGRA210_IMAGE_FORMAT_T_Y8__U8V8_N444,
	TEGRA210_IMAGE_FORMAT_T_Y8__V8U8_N444,
	TEGRA210_IMAGE_FORMAT_T_Y8__U8__V8_N422,
	TEGRA210_IMAGE_FORMAT_T_Y8__U8V8_N422,
	TEGRA210_IMAGE_FORMAT_T_Y8__V8U8_N422,
	TEGRA210_IMAGE_FORMAT_T_Y8__U8__V8_N420,
	TEGRA210_IMAGE_FORMAT_T_Y8__U8V8_N420,
	TEGRA210_IMAGE_FORMAT_T_Y8__V8U8_N420,
	TEGRA210_IMAGE_FORMAT_T_X2LC10LB10LA10,
	TEGRA210_IMAGE_FORMAT_T_A2R6R6R6R6R6,
पूर्ण;

#घोषणा TEGRA210_VIDEO_FMT(DATA_TYPE, BIT_WIDTH, MBUS_CODE, BPP,	\
			   FORMAT, FOURCC)				\
अणु									\
	TEGRA_IMAGE_DT_##DATA_TYPE,					\
	BIT_WIDTH,							\
	MEDIA_BUS_FMT_##MBUS_CODE,					\
	BPP,								\
	TEGRA210_IMAGE_FORMAT_##FORMAT,					\
	V4L2_PIX_FMT_##FOURCC,						\
पूर्ण

/* Tegra210 supported video क्रमmats */
अटल स्थिर काष्ठा tegra_video_क्रमmat tegra210_video_क्रमmats[] = अणु
	/* RAW 8 */
	TEGRA210_VIDEO_FMT(RAW8, 8, SRGGB8_1X8, 1, T_L8, SRGGB8),
	TEGRA210_VIDEO_FMT(RAW8, 8, SGRBG8_1X8, 1, T_L8, SGRBG8),
	TEGRA210_VIDEO_FMT(RAW8, 8, SGBRG8_1X8, 1, T_L8, SGBRG8),
	TEGRA210_VIDEO_FMT(RAW8, 8, SBGGR8_1X8, 1, T_L8, SBGGR8),
	/* RAW 10 */
	TEGRA210_VIDEO_FMT(RAW10, 10, SRGGB10_1X10, 2, T_R16_I, SRGGB10),
	TEGRA210_VIDEO_FMT(RAW10, 10, SGRBG10_1X10, 2, T_R16_I, SGRBG10),
	TEGRA210_VIDEO_FMT(RAW10, 10, SGBRG10_1X10, 2, T_R16_I, SGBRG10),
	TEGRA210_VIDEO_FMT(RAW10, 10, SBGGR10_1X10, 2, T_R16_I, SBGGR10),
	/* RAW 12 */
	TEGRA210_VIDEO_FMT(RAW12, 12, SRGGB12_1X12, 2, T_R16_I, SRGGB12),
	TEGRA210_VIDEO_FMT(RAW12, 12, SGRBG12_1X12, 2, T_R16_I, SGRBG12),
	TEGRA210_VIDEO_FMT(RAW12, 12, SGBRG12_1X12, 2, T_R16_I, SGBRG12),
	TEGRA210_VIDEO_FMT(RAW12, 12, SBGGR12_1X12, 2, T_R16_I, SBGGR12),
	/* RGB888 */
	TEGRA210_VIDEO_FMT(RGB888, 24, RGB888_1X24, 4, T_A8R8G8B8, XBGR32),
	TEGRA210_VIDEO_FMT(RGB888, 24, RGB888_1X32_PADHI, 4, T_A8B8G8R8,
			   RGBX32),
	/* YUV422 */
	TEGRA210_VIDEO_FMT(YUV422_8, 16, UYVY8_1X16, 2, T_U8_Y8__V8_Y8, YVYU),
	TEGRA210_VIDEO_FMT(YUV422_8, 16, VYUY8_1X16, 2, T_V8_Y8__U8_Y8, YUYV),
	TEGRA210_VIDEO_FMT(YUV422_8, 16, YUYV8_1X16, 2, T_Y8_U8__Y8_V8, VYUY),
	TEGRA210_VIDEO_FMT(YUV422_8, 16, YVYU8_1X16, 2, T_Y8_V8__Y8_U8, UYVY),
	TEGRA210_VIDEO_FMT(YUV422_8, 16, UYVY8_1X16, 1, T_Y8__V8U8_N422, NV16),
	TEGRA210_VIDEO_FMT(YUV422_8, 16, UYVY8_2X8, 2, T_U8_Y8__V8_Y8, YVYU),
	TEGRA210_VIDEO_FMT(YUV422_8, 16, VYUY8_2X8, 2, T_V8_Y8__U8_Y8, YUYV),
	TEGRA210_VIDEO_FMT(YUV422_8, 16, YUYV8_2X8, 2, T_Y8_U8__Y8_V8, VYUY),
	TEGRA210_VIDEO_FMT(YUV422_8, 16, YVYU8_2X8, 2, T_Y8_V8__Y8_U8, UYVY),
पूर्ण;

/* Tegra210 VI operations */
अटल स्थिर काष्ठा tegra_vi_ops tegra210_vi_ops = अणु
	.vi_start_streaming = tegra210_vi_start_streaming,
	.vi_stop_streaming = tegra210_vi_stop_streaming,
पूर्ण;

/* Tegra210 VI SoC data */
स्थिर काष्ठा tegra_vi_soc tegra210_vi_soc = अणु
	.video_क्रमmats = tegra210_video_क्रमmats,
	.nक्रमmats = ARRAY_SIZE(tegra210_video_क्रमmats),
	.ops = &tegra210_vi_ops,
	.hw_revision = 3,
	.vi_max_channels = 6,
#अगर IS_ENABLED(CONFIG_VIDEO_TEGRA_TPG)
	.vi_max_clk_hz = 499200000,
#अन्यथा
	.vi_max_clk_hz = 998400000,
#पूर्ण_अगर
पूर्ण;

/* Tegra210 CSI PHY रेजिस्टरs accessors */
अटल व्योम csi_ग_लिखो(काष्ठा tegra_csi *csi, u8 portno, अचिन्हित पूर्णांक addr,
		      u32 val)
अणु
	व्योम __iomem *csi_pp_base;

	csi_pp_base = csi->iomem + CSI_PP_OFFSET(portno >> 1);

	ग_लिखोl_relaxed(val, csi_pp_base + addr);
पूर्ण

/* Tegra210 CSI Pixel parser रेजिस्टरs accessors */
अटल व्योम pp_ग_लिखो(काष्ठा tegra_csi *csi, u8 portno, u32 addr, u32 val)
अणु
	व्योम __iomem *csi_pp_base;
	अचिन्हित पूर्णांक offset;

	csi_pp_base = csi->iomem + CSI_PP_OFFSET(portno >> 1);
	offset = (portno % CSI_PORTS_PER_BRICK) * TEGRA210_CSI_PORT_OFFSET;

	ग_लिखोl_relaxed(val, csi_pp_base + offset + addr);
पूर्ण

अटल u32 pp_पढ़ो(काष्ठा tegra_csi *csi, u8 portno, u32 addr)
अणु
	व्योम __iomem *csi_pp_base;
	अचिन्हित पूर्णांक offset;

	csi_pp_base = csi->iomem + CSI_PP_OFFSET(portno >> 1);
	offset = (portno % CSI_PORTS_PER_BRICK) * TEGRA210_CSI_PORT_OFFSET;

	वापस पढ़ोl_relaxed(csi_pp_base + offset + addr);
पूर्ण

/* Tegra210 CSI CIL A/B port रेजिस्टरs accessors */
अटल व्योम cil_ग_लिखो(काष्ठा tegra_csi *csi, u8 portno, u32 addr, u32 val)
अणु
	व्योम __iomem *csi_cil_base;
	अचिन्हित पूर्णांक offset;

	csi_cil_base = csi->iomem + CSI_PP_OFFSET(portno >> 1) +
		       TEGRA210_CSI_CIL_OFFSET;
	offset = (portno % CSI_PORTS_PER_BRICK) * TEGRA210_CSI_PORT_OFFSET;

	ग_लिखोl_relaxed(val, csi_cil_base + offset + addr);
पूर्ण

अटल u32 cil_पढ़ो(काष्ठा tegra_csi *csi, u8 portno, u32 addr)
अणु
	व्योम __iomem *csi_cil_base;
	अचिन्हित पूर्णांक offset;

	csi_cil_base = csi->iomem + CSI_PP_OFFSET(portno >> 1) +
		       TEGRA210_CSI_CIL_OFFSET;
	offset = (portno % CSI_PORTS_PER_BRICK) * TEGRA210_CSI_PORT_OFFSET;

	वापस पढ़ोl_relaxed(csi_cil_base + offset + addr);
पूर्ण

/* Tegra210 CSI Test pattern generator रेजिस्टरs accessor */
अटल व्योम tpg_ग_लिखो(काष्ठा tegra_csi *csi, u8 portno, अचिन्हित पूर्णांक addr,
		      u32 val)
अणु
	व्योम __iomem *csi_pp_base;
	अचिन्हित पूर्णांक offset;

	csi_pp_base = csi->iomem + CSI_PP_OFFSET(portno >> 1);
	offset = (portno % CSI_PORTS_PER_BRICK) * TEGRA210_CSI_PORT_OFFSET +
		 TEGRA210_CSI_TPG_OFFSET;

	ग_लिखोl_relaxed(val, csi_pp_base + offset + addr);
पूर्ण

/*
 * Tegra210 CSI operations
 */
अटल व्योम tegra210_csi_port_recover(काष्ठा tegra_csi_channel *csi_chan,
				      u8 portno)
अणु
	काष्ठा tegra_csi *csi = csi_chan->csi;
	u32 val;

	/*
	 * Recover CSI hardware in हाल of capture errors by issuing
	 * software reset to CSICIL sensor, pixel parser, and clear errors
	 * to have clean capture on  next streaming.
	 */
	val = pp_पढ़ो(csi, portno, TEGRA_CSI_PIXEL_PARSER_STATUS);
	dev_dbg(csi->dev, "TEGRA_CSI_PIXEL_PARSER_STATUS 0x%08x\n", val);

	val = cil_पढ़ो(csi, portno, TEGRA_CSI_CIL_STATUS);
	dev_dbg(csi->dev, "TEGRA_CSI_CIL_STATUS 0x%08x\n", val);

	val = cil_पढ़ो(csi, portno, TEGRA_CSI_CILX_STATUS);
	dev_dbg(csi->dev, "TEGRA_CSI_CILX_STATUS 0x%08x\n", val);

	अगर (csi_chan->numlanes == 4) अणु
		/* reset CSI CIL sensor */
		cil_ग_लिखो(csi, portno, TEGRA_CSI_CIL_SW_SENSOR_RESET, 0x1);
		cil_ग_लिखो(csi, portno + 1, TEGRA_CSI_CIL_SW_SENSOR_RESET, 0x1);
		/*
		 * SW_STATUS_RESET resets all status bits of PPA, PPB, CILA,
		 * CILB status रेजिस्टरs and debug counters.
		 * So, SW_STATUS_RESET can be used only when CSI brick is in
		 * x4 mode.
		 */
		csi_ग_लिखो(csi, portno, TEGRA_CSI_CSI_SW_STATUS_RESET, 0x1);

		/* sleep क्रम 20 घड़ी cycles to drain the FIFO */
		usleep_range(10, 20);

		cil_ग_लिखो(csi, portno + 1, TEGRA_CSI_CIL_SW_SENSOR_RESET, 0x0);
		cil_ग_लिखो(csi, portno, TEGRA_CSI_CIL_SW_SENSOR_RESET, 0x0);
		csi_ग_लिखो(csi, portno, TEGRA_CSI_CSI_SW_STATUS_RESET, 0x0);
	पूर्ण अन्यथा अणु
		/* reset CSICIL sensor */
		cil_ग_लिखो(csi, portno, TEGRA_CSI_CIL_SW_SENSOR_RESET, 0x1);
		usleep_range(10, 20);
		cil_ग_लिखो(csi, portno, TEGRA_CSI_CIL_SW_SENSOR_RESET, 0x0);

		/* clear the errors */
		pp_ग_लिखो(csi, portno, TEGRA_CSI_PIXEL_PARSER_STATUS,
			 0xffffffff);
		cil_ग_लिखो(csi, portno, TEGRA_CSI_CIL_STATUS, 0xffffffff);
		cil_ग_लिखो(csi, portno, TEGRA_CSI_CILX_STATUS, 0xffffffff);
	पूर्ण
पूर्ण

अटल व्योम tegra210_csi_error_recover(काष्ठा tegra_csi_channel *csi_chan)
अणु
	u8 *portnos = csi_chan->csi_port_nums;
	पूर्णांक i;

	क्रम (i = 0; i < csi_chan->numgangports; i++)
		tegra210_csi_port_recover(csi_chan, portnos[i]);
पूर्ण

अटल पूर्णांक
tegra210_csi_port_start_streaming(काष्ठा tegra_csi_channel *csi_chan,
				  u8 portno)
अणु
	काष्ठा tegra_csi *csi = csi_chan->csi;
	u8 clk_settle_समय = 0;
	u8 ths_settle_समय = 10;
	u32 val;

	अगर (!csi_chan->pg_mode)
		tegra_csi_calc_settle_समय(csi_chan, portno, &clk_settle_समय,
					   &ths_settle_समय);

	csi_ग_लिखो(csi, portno, TEGRA_CSI_CLKEN_OVERRIDE, 0);

	/* clean up status */
	pp_ग_लिखो(csi, portno, TEGRA_CSI_PIXEL_PARSER_STATUS, 0xffffffff);
	cil_ग_लिखो(csi, portno, TEGRA_CSI_CIL_STATUS, 0xffffffff);
	cil_ग_लिखो(csi, portno, TEGRA_CSI_CILX_STATUS, 0xffffffff);
	cil_ग_लिखो(csi, portno, TEGRA_CSI_CIL_INTERRUPT_MASK, 0x0);

	/* CIL PHY रेजिस्टरs setup */
	cil_ग_लिखो(csi, portno, TEGRA_CSI_CIL_PAD_CONFIG0, 0x0);
	cil_ग_लिखो(csi, portno, TEGRA_CSI_CIL_PHY_CONTROL,
		  FIELD_PREP(CLK_SETTLE_MASK, clk_settle_समय) |
		  FIELD_PREP(THS_SETTLE_MASK, ths_settle_समय));

	/*
	 * The CSI unit provides क्रम connection of up to six cameras in
	 * the प्रणाली and is organized as three identical instances of
	 * two MIPI support blocks, each with a separate 4-lane
	 * पूर्णांकerface that can be configured as a single camera with 4
	 * lanes or as a dual camera with 2 lanes available क्रम each
	 * camera.
	 */
	अगर (csi_chan->numlanes == 4) अणु
		cil_ग_लिखो(csi, portno + 1, TEGRA_CSI_CIL_STATUS, 0xffffffff);
		cil_ग_लिखो(csi, portno + 1, TEGRA_CSI_CILX_STATUS, 0xffffffff);
		cil_ग_लिखो(csi, portno + 1, TEGRA_CSI_CIL_INTERRUPT_MASK, 0x0);

		cil_ग_लिखो(csi, portno, TEGRA_CSI_CIL_PAD_CONFIG0,
			  BRICK_CLOCK_A_4X);
		cil_ग_लिखो(csi, portno + 1, TEGRA_CSI_CIL_PAD_CONFIG0, 0x0);
		cil_ग_लिखो(csi, portno + 1, TEGRA_CSI_CIL_INTERRUPT_MASK, 0x0);
		cil_ग_लिखो(csi, portno + 1, TEGRA_CSI_CIL_PHY_CONTROL,
			  FIELD_PREP(CLK_SETTLE_MASK, clk_settle_समय) |
			  FIELD_PREP(THS_SETTLE_MASK, ths_settle_समय));
		csi_ग_लिखो(csi, portno, TEGRA_CSI_PHY_CIL_COMMAND,
			  CSI_A_PHY_CIL_ENABLE | CSI_B_PHY_CIL_ENABLE);
	पूर्ण अन्यथा अणु
		val = ((portno & 1) == PORT_A) ?
		      CSI_A_PHY_CIL_ENABLE | CSI_B_PHY_CIL_NOP :
		      CSI_B_PHY_CIL_ENABLE | CSI_A_PHY_CIL_NOP;
		csi_ग_लिखो(csi, portno, TEGRA_CSI_PHY_CIL_COMMAND, val);
	पूर्ण

	/* CSI pixel parser रेजिस्टरs setup */
	pp_ग_लिखो(csi, portno, TEGRA_CSI_PIXEL_STREAM_PP_COMMAND,
		 (0xf << CSI_PP_START_MARKER_FRAME_MAX_OFFSET) |
		 CSI_PP_SINGLE_SHOT_ENABLE | CSI_PP_RST);
	pp_ग_लिखो(csi, portno, TEGRA_CSI_PIXEL_PARSER_INTERRUPT_MASK, 0x0);
	pp_ग_लिखो(csi, portno, TEGRA_CSI_PIXEL_STREAM_CONTROL0,
		 CSI_PP_PACKET_HEADER_SENT |
		 CSI_PP_DATA_IDENTIFIER_ENABLE |
		 CSI_PP_WORD_COUNT_SELECT_HEADER |
		 CSI_PP_CRC_CHECK_ENABLE |  CSI_PP_WC_CHECK |
		 CSI_PP_OUTPUT_FORMAT_STORE | CSI_PPA_PAD_LINE_NOPAD |
		 CSI_PP_HEADER_EC_DISABLE | CSI_PPA_PAD_FRAME_NOPAD |
		 (portno & 1));
	pp_ग_लिखो(csi, portno, TEGRA_CSI_PIXEL_STREAM_CONTROL1,
		 (0x1 << CSI_PP_TOP_FIELD_FRAME_OFFSET) |
		 (0x1 << CSI_PP_TOP_FIELD_FRAME_MASK_OFFSET));
	pp_ग_लिखो(csi, portno, TEGRA_CSI_PIXEL_STREAM_GAP,
		 0x14 << PP_FRAME_MIN_GAP_OFFSET);
	pp_ग_लिखो(csi, portno, TEGRA_CSI_PIXEL_STREAM_EXPECTED_FRAME, 0x0);
	pp_ग_लिखो(csi, portno, TEGRA_CSI_INPUT_STREAM_CONTROL,
		 (0x3f << CSI_SKIP_PACKET_THRESHOLD_OFFSET) |
		 (csi_chan->numlanes - 1));

	/* TPG setup */
	अगर (csi_chan->pg_mode) अणु
		tpg_ग_लिखो(csi, portno, TEGRA_CSI_PATTERN_GENERATOR_CTRL,
			  ((csi_chan->pg_mode - 1) << PG_MODE_OFFSET) |
			  PG_ENABLE);
		tpg_ग_लिखो(csi, portno, TEGRA_CSI_PG_BLANK,
			  csi_chan->v_blank << PG_VBLANK_OFFSET |
			  csi_chan->h_blank);
		tpg_ग_लिखो(csi, portno, TEGRA_CSI_PG_PHASE, 0x0);
		tpg_ग_लिखो(csi, portno, TEGRA_CSI_PG_RED_FREQ,
			  (0x10 << PG_RED_VERT_INIT_FREQ_OFFSET) |
			  (0x10 << PG_RED_HOR_INIT_FREQ_OFFSET));
		tpg_ग_लिखो(csi, portno, TEGRA_CSI_PG_RED_FREQ_RATE, 0x0);
		tpg_ग_लिखो(csi, portno, TEGRA_CSI_PG_GREEN_FREQ,
			  (0x10 << PG_GREEN_VERT_INIT_FREQ_OFFSET) |
			  (0x10 << PG_GREEN_HOR_INIT_FREQ_OFFSET));
		tpg_ग_लिखो(csi, portno, TEGRA_CSI_PG_GREEN_FREQ_RATE, 0x0);
		tpg_ग_लिखो(csi, portno, TEGRA_CSI_PG_BLUE_FREQ,
			  (0x10 << PG_BLUE_VERT_INIT_FREQ_OFFSET) |
			  (0x10 << PG_BLUE_HOR_INIT_FREQ_OFFSET));
		tpg_ग_लिखो(csi, portno, TEGRA_CSI_PG_BLUE_FREQ_RATE, 0x0);
	पूर्ण

	pp_ग_लिखो(csi, portno, TEGRA_CSI_PIXEL_STREAM_PP_COMMAND,
		 (0xf << CSI_PP_START_MARKER_FRAME_MAX_OFFSET) |
		 CSI_PP_SINGLE_SHOT_ENABLE | CSI_PP_ENABLE);

	वापस 0;
पूर्ण

अटल व्योम
tegra210_csi_port_stop_streaming(काष्ठा tegra_csi_channel *csi_chan, u8 portno)
अणु
	काष्ठा tegra_csi *csi = csi_chan->csi;
	u32 val;

	val = pp_पढ़ो(csi, portno, TEGRA_CSI_PIXEL_PARSER_STATUS);

	dev_dbg(csi->dev, "TEGRA_CSI_PIXEL_PARSER_STATUS 0x%08x\n", val);
	pp_ग_लिखो(csi, portno, TEGRA_CSI_PIXEL_PARSER_STATUS, val);

	val = cil_पढ़ो(csi, portno, TEGRA_CSI_CIL_STATUS);
	dev_dbg(csi->dev, "TEGRA_CSI_CIL_STATUS 0x%08x\n", val);
	cil_ग_लिखो(csi, portno, TEGRA_CSI_CIL_STATUS, val);

	val = cil_पढ़ो(csi, portno, TEGRA_CSI_CILX_STATUS);
	dev_dbg(csi->dev, "TEGRA_CSI_CILX_STATUS 0x%08x\n", val);
	cil_ग_लिखो(csi, portno, TEGRA_CSI_CILX_STATUS, val);

	pp_ग_लिखो(csi, portno, TEGRA_CSI_PIXEL_STREAM_PP_COMMAND,
		 (0xf << CSI_PP_START_MARKER_FRAME_MAX_OFFSET) |
		 CSI_PP_DISABLE);

	अगर (csi_chan->pg_mode) अणु
		tpg_ग_लिखो(csi, portno, TEGRA_CSI_PATTERN_GENERATOR_CTRL,
			  PG_DISABLE);
		वापस;
	पूर्ण

	अगर (csi_chan->numlanes == 4) अणु
		csi_ग_लिखो(csi, portno, TEGRA_CSI_PHY_CIL_COMMAND,
			  CSI_A_PHY_CIL_DISABLE |
			  CSI_B_PHY_CIL_DISABLE);
	पूर्ण अन्यथा अणु
		val = ((portno & 1) == PORT_A) ?
		      CSI_A_PHY_CIL_DISABLE | CSI_B_PHY_CIL_NOP :
		      CSI_B_PHY_CIL_DISABLE | CSI_A_PHY_CIL_NOP;
		csi_ग_लिखो(csi, portno, TEGRA_CSI_PHY_CIL_COMMAND, val);
	पूर्ण
पूर्ण

अटल पूर्णांक tegra210_csi_start_streaming(काष्ठा tegra_csi_channel *csi_chan)
अणु
	u8 *portnos = csi_chan->csi_port_nums;
	पूर्णांक ret, i;

	क्रम (i = 0; i < csi_chan->numgangports; i++) अणु
		ret = tegra210_csi_port_start_streaming(csi_chan, portnos[i]);
		अगर (ret)
			जाओ stream_start_fail;
	पूर्ण

	वापस 0;

stream_start_fail:
	क्रम (i = i - 1; i >= 0; i--)
		tegra210_csi_port_stop_streaming(csi_chan, portnos[i]);

	वापस ret;
पूर्ण

अटल व्योम tegra210_csi_stop_streaming(काष्ठा tegra_csi_channel *csi_chan)
अणु
	u8 *portnos = csi_chan->csi_port_nums;
	पूर्णांक i;

	क्रम (i = 0; i < csi_chan->numgangports; i++)
		tegra210_csi_port_stop_streaming(csi_chan, portnos[i]);
पूर्ण

/*
 * Tegra210 CSI TPG frame rate table with horizontal and vertical
 * blanking पूर्णांकervals क्रम corresponding क्रमmat and resolution.
 * Blanking पूर्णांकervals are tuned values from design team क्रम max TPG
 * घड़ी rate.
 */
अटल स्थिर काष्ठा tpg_framerate tegra210_tpg_frmrate_table[] = अणु
	अणु
		.frmsize = अणु 1280, 720 पूर्ण,
		.code = MEDIA_BUS_FMT_SRGGB10_1X10,
		.framerate = 120,
		.h_blank = 512,
		.v_blank = 8,
	पूर्ण,
	अणु
		.frmsize = अणु 1920, 1080 पूर्ण,
		.code = MEDIA_BUS_FMT_SRGGB10_1X10,
		.framerate = 60,
		.h_blank = 512,
		.v_blank = 8,
	पूर्ण,
	अणु
		.frmsize = अणु 3840, 2160 पूर्ण,
		.code = MEDIA_BUS_FMT_SRGGB10_1X10,
		.framerate = 20,
		.h_blank = 8,
		.v_blank = 8,
	पूर्ण,
	अणु
		.frmsize = अणु 1280, 720 पूर्ण,
		.code = MEDIA_BUS_FMT_RGB888_1X32_PADHI,
		.framerate = 60,
		.h_blank = 512,
		.v_blank = 8,
	पूर्ण,
	अणु
		.frmsize = अणु 1920, 1080 पूर्ण,
		.code = MEDIA_BUS_FMT_RGB888_1X32_PADHI,
		.framerate = 30,
		.h_blank = 512,
		.v_blank = 8,
	पूर्ण,
	अणु
		.frmsize = अणु 3840, 2160 पूर्ण,
		.code = MEDIA_BUS_FMT_RGB888_1X32_PADHI,
		.framerate = 8,
		.h_blank = 8,
		.v_blank = 8,
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra210_csi_cil_clks[] = अणु
	"csi",
	"cilab",
	"cilcd",
	"cile",
#अगर IS_ENABLED(CONFIG_VIDEO_TEGRA_TPG)
	"csi_tpg",
#पूर्ण_अगर
पूर्ण;

/* Tegra210 CSI operations */
अटल स्थिर काष्ठा tegra_csi_ops tegra210_csi_ops = अणु
	.csi_start_streaming = tegra210_csi_start_streaming,
	.csi_stop_streaming = tegra210_csi_stop_streaming,
	.csi_err_recover = tegra210_csi_error_recover,
पूर्ण;

/* Tegra210 CSI SoC data */
स्थिर काष्ठा tegra_csi_soc tegra210_csi_soc = अणु
	.ops = &tegra210_csi_ops,
	.csi_max_channels = 6,
	.clk_names = tegra210_csi_cil_clks,
	.num_clks = ARRAY_SIZE(tegra210_csi_cil_clks),
	.tpg_frmrate_table = tegra210_tpg_frmrate_table,
	.tpg_frmrate_table_size = ARRAY_SIZE(tegra210_tpg_frmrate_table),
पूर्ण;
