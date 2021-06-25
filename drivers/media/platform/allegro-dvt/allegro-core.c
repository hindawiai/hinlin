<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 Pengutronix, Michael Tretter <kernel@pengutronix.de>
 *
 * Allegro DVT video encoder driver
 */

#समावेश <linux/bits.h>
#समावेश <linux/firmware.h>
#समावेश <linux/gcd.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/log2.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/videobuf2-dma-contig.h>
#समावेश <media/videobuf2-v4l2.h>

#समावेश "allegro-mail.h"
#समावेश "nal-h264.h"
#समावेश "nal-hevc.h"

/*
 * Support up to 4k video streams. The hardware actually supports higher
 * resolutions, which are specअगरied in PG252 June 6, 2018 (H.264/H.265 Video
 * Codec Unit v1.1) Chapter 3.
 */
#घोषणा ALLEGRO_WIDTH_MIN 128
#घोषणा ALLEGRO_WIDTH_DEFAULT 1920
#घोषणा ALLEGRO_WIDTH_MAX 3840
#घोषणा ALLEGRO_HEIGHT_MIN 64
#घोषणा ALLEGRO_HEIGHT_DEFAULT 1080
#घोषणा ALLEGRO_HEIGHT_MAX 2160

#घोषणा ALLEGRO_FRAMERATE_DEFAULT ((काष्ठा v4l2_fract) अणु 30, 1 पूर्ण)

#घोषणा ALLEGRO_GOP_SIZE_DEFAULT 25
#घोषणा ALLEGRO_GOP_SIZE_MAX 1000

/*
 * MCU Control Registers
 *
 * The Zynq UltraScale+ Devices Register Reference करोcuments the रेजिस्टरs
 * with an offset of 0x9000, which equals the size of the SRAM and one page
 * gap. The driver handles SRAM and रेजिस्टरs separately and, thereक्रमe, is
 * oblivious of the offset.
 */
#घोषणा AL5_MCU_RESET                   0x0000
#घोषणा AL5_MCU_RESET_SOFT              BIT(0)
#घोषणा AL5_MCU_RESET_REGS              BIT(1)
#घोषणा AL5_MCU_RESET_MODE              0x0004
#घोषणा AL5_MCU_RESET_MODE_SLEEP        BIT(0)
#घोषणा AL5_MCU_RESET_MODE_HALT         BIT(1)
#घोषणा AL5_MCU_STA                     0x0008
#घोषणा AL5_MCU_STA_SLEEP               BIT(0)
#घोषणा AL5_MCU_WAKEUP                  0x000c

#घोषणा AL5_ICACHE_ADDR_OFFSET_MSB      0x0010
#घोषणा AL5_ICACHE_ADDR_OFFSET_LSB      0x0014
#घोषणा AL5_DCACHE_ADDR_OFFSET_MSB      0x0018
#घोषणा AL5_DCACHE_ADDR_OFFSET_LSB      0x001c

#घोषणा AL5_MCU_INTERRUPT               0x0100
#घोषणा AL5_ITC_CPU_IRQ_MSK             0x0104
#घोषणा AL5_ITC_CPU_IRQ_CLR             0x0108
#घोषणा AL5_ITC_CPU_IRQ_STA             0x010C
#घोषणा AL5_ITC_CPU_IRQ_STA_TRIGGERED   BIT(0)

#घोषणा AXI_ADDR_OFFSET_IP              0x0208

/*
 * The MCU accesses the प्रणाली memory with a 2G offset compared to CPU
 * physical addresses.
 */
#घोषणा MCU_CACHE_OFFSET SZ_2G

/*
 * The driver needs to reserve some space at the beginning of capture buffers,
 * because it needs to ग_लिखो SPS/PPS NAL units. The encoder ग_लिखोs the actual
 * frame data after the offset.
 */
#घोषणा ENCODER_STREAM_OFFSET SZ_128

#घोषणा SIZE_MACROBLOCK 16

/* Encoding options */
#घोषणा LOG2_MAX_FRAME_NUM		4
#घोषणा LOG2_MAX_PIC_ORDER_CNT		10
#घोषणा BETA_OFFSET_DIV_2		-1
#घोषणा TC_OFFSET_DIV_2			-1

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Debug level (0-2)");

काष्ठा allegro_buffer अणु
	व्योम *vaddr;
	dma_addr_t paddr;
	माप_प्रकार size;
	काष्ठा list_head head;
पूर्ण;

काष्ठा allegro_dev;
काष्ठा allegro_channel;

काष्ठा allegro_mbox अणु
	काष्ठा allegro_dev *dev;
	अचिन्हित पूर्णांक head;
	अचिन्हित पूर्णांक tail;
	अचिन्हित पूर्णांक data;
	माप_प्रकार size;
	/* protect mailbox from simultaneous accesses */
	काष्ठा mutex lock;
पूर्ण;

काष्ठा allegro_dev अणु
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा video_device video_dev;
	काष्ठा v4l2_m2m_dev *m2m_dev;
	काष्ठा platक्रमm_device *plat_dev;

	/* mutex protecting vb2_queue काष्ठाure */
	काष्ठा mutex lock;

	काष्ठा regmap *regmap;
	काष्ठा regmap *sram;

	स्थिर काष्ठा fw_info *fw_info;
	काष्ठा allegro_buffer firmware;
	काष्ठा allegro_buffer suballocator;

	काष्ठा completion init_complete;

	/* The mailbox पूर्णांकerface */
	काष्ठा allegro_mbox *mbox_command;
	काष्ठा allegro_mbox *mbox_status;

	/*
	 * The करोwnstream driver limits the users to 64 users, thus I can use
	 * a bitfield क्रम the user_ids that are in use. See also user_id in
	 * काष्ठा allegro_channel.
	 */
	अचिन्हित दीर्घ channel_user_ids;
	काष्ठा list_head channels;
पूर्ण;

अटल काष्ठा regmap_config allegro_regmap_config = अणु
	.name = "regmap",
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = 0xfff,
	.cache_type = REGCACHE_NONE,
पूर्ण;

अटल काष्ठा regmap_config allegro_sram_config = अणु
	.name = "sram",
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = 0x7fff,
	.cache_type = REGCACHE_NONE,
पूर्ण;

#घोषणा fh_to_channel(__fh) container_of(__fh, काष्ठा allegro_channel, fh)

काष्ठा allegro_channel अणु
	काष्ठा allegro_dev *dev;
	काष्ठा v4l2_fh fh;
	काष्ठा v4l2_ctrl_handler ctrl_handler;

	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;
	अचिन्हित पूर्णांक stride;
	काष्ठा v4l2_fract framerate;

	क्रमागत v4l2_colorspace colorspace;
	क्रमागत v4l2_ycbcr_encoding ycbcr_enc;
	क्रमागत v4l2_quantization quantization;
	क्रमागत v4l2_xfer_func xfer_func;

	u32 pixelक्रमmat;
	अचिन्हित पूर्णांक sizeimage_raw;
	अचिन्हित पूर्णांक osequence;

	u32 codec;
	अचिन्हित पूर्णांक sizeimage_encoded;
	अचिन्हित पूर्णांक csequence;

	bool frame_rc_enable;
	अचिन्हित पूर्णांक bitrate;
	अचिन्हित पूर्णांक bitrate_peak;

	काष्ठा allegro_buffer config_blob;

	अचिन्हित पूर्णांक log2_max_frame_num;
	bool temporal_mvp_enable;

	bool enable_loop_filter_across_tiles;
	bool enable_loop_filter_across_slices;
	bool enable_deblocking_filter_override;
	bool enable_reordering;
	bool dbf_ovr_en;

	अचिन्हित पूर्णांक num_ref_idx_l0;
	अचिन्हित पूर्णांक num_ref_idx_l1;

	/* Maximum range क्रम motion estimation */
	पूर्णांक b_hrz_me_range;
	पूर्णांक b_vrt_me_range;
	पूर्णांक p_hrz_me_range;
	पूर्णांक p_vrt_me_range;
	/* Size limits of coding unit */
	पूर्णांक min_cu_size;
	पूर्णांक max_cu_size;
	/* Size limits of transक्रमm unit */
	पूर्णांक min_tu_size;
	पूर्णांक max_tu_size;
	पूर्णांक max_transfo_depth_पूर्णांकra;
	पूर्णांक max_transfo_depth_पूर्णांकer;

	काष्ठा v4l2_ctrl *mpeg_video_h264_profile;
	काष्ठा v4l2_ctrl *mpeg_video_h264_level;
	काष्ठा v4l2_ctrl *mpeg_video_h264_i_frame_qp;
	काष्ठा v4l2_ctrl *mpeg_video_h264_max_qp;
	काष्ठा v4l2_ctrl *mpeg_video_h264_min_qp;
	काष्ठा v4l2_ctrl *mpeg_video_h264_p_frame_qp;
	काष्ठा v4l2_ctrl *mpeg_video_h264_b_frame_qp;

	काष्ठा v4l2_ctrl *mpeg_video_hevc_profile;
	काष्ठा v4l2_ctrl *mpeg_video_hevc_level;
	काष्ठा v4l2_ctrl *mpeg_video_hevc_tier;
	काष्ठा v4l2_ctrl *mpeg_video_hevc_i_frame_qp;
	काष्ठा v4l2_ctrl *mpeg_video_hevc_max_qp;
	काष्ठा v4l2_ctrl *mpeg_video_hevc_min_qp;
	काष्ठा v4l2_ctrl *mpeg_video_hevc_p_frame_qp;
	काष्ठा v4l2_ctrl *mpeg_video_hevc_b_frame_qp;

	काष्ठा v4l2_ctrl *mpeg_video_frame_rc_enable;
	काष्ठा अणु /* video bitrate mode control cluster */
		काष्ठा v4l2_ctrl *mpeg_video_bitrate_mode;
		काष्ठा v4l2_ctrl *mpeg_video_bitrate;
		काष्ठा v4l2_ctrl *mpeg_video_bitrate_peak;
	पूर्ण;
	काष्ठा v4l2_ctrl *mpeg_video_cpb_size;
	काष्ठा v4l2_ctrl *mpeg_video_gop_size;

	/* user_id is used to identअगरy the channel during CREATE_CHANNEL */
	/* not sure, what to set here and अगर this is actually required */
	पूर्णांक user_id;
	/* channel_id is set by the mcu and used by all later commands */
	पूर्णांक mcu_channel_id;

	काष्ठा list_head buffers_reference;
	काष्ठा list_head buffers_पूर्णांकermediate;

	काष्ठा list_head source_shaकरोw_list;
	काष्ठा list_head stream_shaकरोw_list;
	/* protect shaकरोw lists of buffers passed to firmware */
	काष्ठा mutex shaकरोw_list_lock;

	काष्ठा list_head list;
	काष्ठा completion completion;

	अचिन्हित पूर्णांक error;
पूर्ण;

अटल अंतरभूत पूर्णांक
allegro_channel_get_i_frame_qp(काष्ठा allegro_channel *channel)
अणु
	अगर (channel->codec == V4L2_PIX_FMT_HEVC)
		वापस v4l2_ctrl_g_ctrl(channel->mpeg_video_hevc_i_frame_qp);
	अन्यथा
		वापस v4l2_ctrl_g_ctrl(channel->mpeg_video_h264_i_frame_qp);
पूर्ण

अटल अंतरभूत पूर्णांक
allegro_channel_get_p_frame_qp(काष्ठा allegro_channel *channel)
अणु
	अगर (channel->codec == V4L2_PIX_FMT_HEVC)
		वापस v4l2_ctrl_g_ctrl(channel->mpeg_video_hevc_p_frame_qp);
	अन्यथा
		वापस v4l2_ctrl_g_ctrl(channel->mpeg_video_h264_p_frame_qp);
पूर्ण

अटल अंतरभूत पूर्णांक
allegro_channel_get_b_frame_qp(काष्ठा allegro_channel *channel)
अणु
	अगर (channel->codec == V4L2_PIX_FMT_HEVC)
		वापस v4l2_ctrl_g_ctrl(channel->mpeg_video_hevc_b_frame_qp);
	अन्यथा
		वापस v4l2_ctrl_g_ctrl(channel->mpeg_video_h264_b_frame_qp);
पूर्ण

अटल अंतरभूत पूर्णांक
allegro_channel_get_min_qp(काष्ठा allegro_channel *channel)
अणु
	अगर (channel->codec == V4L2_PIX_FMT_HEVC)
		वापस v4l2_ctrl_g_ctrl(channel->mpeg_video_hevc_min_qp);
	अन्यथा
		वापस v4l2_ctrl_g_ctrl(channel->mpeg_video_h264_min_qp);
पूर्ण

अटल अंतरभूत पूर्णांक
allegro_channel_get_max_qp(काष्ठा allegro_channel *channel)
अणु
	अगर (channel->codec == V4L2_PIX_FMT_HEVC)
		वापस v4l2_ctrl_g_ctrl(channel->mpeg_video_hevc_max_qp);
	अन्यथा
		वापस v4l2_ctrl_g_ctrl(channel->mpeg_video_h264_max_qp);
पूर्ण

काष्ठा allegro_m2m_buffer अणु
	काष्ठा v4l2_m2m_buffer buf;
	काष्ठा list_head head;
पूर्ण;

#घोषणा to_allegro_m2m_buffer(__buf) \
	container_of(__buf, काष्ठा allegro_m2m_buffer, buf)

काष्ठा fw_info अणु
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक id_codec;
	अक्षर *version;
	अचिन्हित पूर्णांक mailbox_cmd;
	अचिन्हित पूर्णांक mailbox_status;
	माप_प्रकार mailbox_size;
	क्रमागत mcu_msg_version mailbox_version;
	माप_प्रकार suballocator_size;
पूर्ण;

अटल स्थिर काष्ठा fw_info supported_firmware[] = अणु
	अणु
		.id = 18296,
		.id_codec = 96272,
		.version = "v2018.2",
		.mailbox_cmd = 0x7800,
		.mailbox_status = 0x7c00,
		.mailbox_size = 0x400 - 0x8,
		.mailbox_version = MCU_MSG_VERSION_2018_2,
		.suballocator_size = SZ_16M,
	पूर्ण, अणु
		.id = 14680,
		.id_codec = 126572,
		.version = "v2019.2",
		.mailbox_cmd = 0x7000,
		.mailbox_status = 0x7800,
		.mailbox_size = 0x800 - 0x8,
		.mailbox_version = MCU_MSG_VERSION_2019_2,
		.suballocator_size = SZ_32M,
	पूर्ण,
पूर्ण;

अटल अंतरभूत u32 to_mcu_addr(काष्ठा allegro_dev *dev, dma_addr_t phys)
अणु
	अगर (upper_32_bits(phys) || (lower_32_bits(phys) & MCU_CACHE_OFFSET))
		v4l2_warn(&dev->v4l2_dev,
			  "address %pad is outside mcu window\n", &phys);

	वापस lower_32_bits(phys) | MCU_CACHE_OFFSET;
पूर्ण

अटल अंतरभूत u32 to_mcu_size(काष्ठा allegro_dev *dev, माप_प्रकार size)
अणु
	वापस lower_32_bits(size);
पूर्ण

अटल अंतरभूत u32 to_codec_addr(काष्ठा allegro_dev *dev, dma_addr_t phys)
अणु
	अगर (upper_32_bits(phys))
		v4l2_warn(&dev->v4l2_dev,
			  "address %pad cannot be used by codec\n", &phys);

	वापस lower_32_bits(phys);
पूर्ण

अटल अंतरभूत u64 ptr_to_u64(स्थिर व्योम *ptr)
अणु
	वापस (uपूर्णांकptr_t)ptr;
पूर्ण

/* Helper functions क्रम channel and user operations */

अटल अचिन्हित दीर्घ allegro_next_user_id(काष्ठा allegro_dev *dev)
अणु
	अगर (dev->channel_user_ids == ~0UL)
		वापस -EBUSY;

	वापस ffz(dev->channel_user_ids);
पूर्ण

अटल काष्ठा allegro_channel *
allegro_find_channel_by_user_id(काष्ठा allegro_dev *dev,
				अचिन्हित पूर्णांक user_id)
अणु
	काष्ठा allegro_channel *channel;

	list_क्रम_each_entry(channel, &dev->channels, list) अणु
		अगर (channel->user_id == user_id)
			वापस channel;
	पूर्ण

	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल काष्ठा allegro_channel *
allegro_find_channel_by_channel_id(काष्ठा allegro_dev *dev,
				   अचिन्हित पूर्णांक channel_id)
अणु
	काष्ठा allegro_channel *channel;

	list_क्रम_each_entry(channel, &dev->channels, list) अणु
		अगर (channel->mcu_channel_id == channel_id)
			वापस channel;
	पूर्ण

	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल अंतरभूत bool channel_exists(काष्ठा allegro_channel *channel)
अणु
	वापस channel->mcu_channel_id != -1;
पूर्ण

#घोषणा AL_ERROR			0x80
#घोषणा AL_ERR_INIT_FAILED		0x81
#घोषणा AL_ERR_NO_FRAME_DECODED		0x82
#घोषणा AL_ERR_RESOLUTION_CHANGE	0x85
#घोषणा AL_ERR_NO_MEMORY		0x87
#घोषणा AL_ERR_STREAM_OVERFLOW		0x88
#घोषणा AL_ERR_TOO_MANY_SLICES		0x89
#घोषणा AL_ERR_BUF_NOT_READY		0x8c
#घोषणा AL_ERR_NO_CHANNEL_AVAILABLE	0x8d
#घोषणा AL_ERR_RESOURCE_UNAVAILABLE	0x8e
#घोषणा AL_ERR_NOT_ENOUGH_CORES		0x8f
#घोषणा AL_ERR_REQUEST_MALFORMED	0x90
#घोषणा AL_ERR_CMD_NOT_ALLOWED		0x91
#घोषणा AL_ERR_INVALID_CMD_VALUE	0x92

अटल अंतरभूत स्थिर अक्षर *allegro_err_to_string(अचिन्हित पूर्णांक err)
अणु
	चयन (err) अणु
	हाल AL_ERR_INIT_FAILED:
		वापस "initialization failed";
	हाल AL_ERR_NO_FRAME_DECODED:
		वापस "no frame decoded";
	हाल AL_ERR_RESOLUTION_CHANGE:
		वापस "resolution change";
	हाल AL_ERR_NO_MEMORY:
		वापस "out of memory";
	हाल AL_ERR_STREAM_OVERFLOW:
		वापस "stream buffer overflow";
	हाल AL_ERR_TOO_MANY_SLICES:
		वापस "too many slices";
	हाल AL_ERR_BUF_NOT_READY:
		वापस "buffer not ready";
	हाल AL_ERR_NO_CHANNEL_AVAILABLE:
		वापस "no channel available";
	हाल AL_ERR_RESOURCE_UNAVAILABLE:
		वापस "resource unavailable";
	हाल AL_ERR_NOT_ENOUGH_CORES:
		वापस "not enough cores";
	हाल AL_ERR_REQUEST_MALFORMED:
		वापस "request malformed";
	हाल AL_ERR_CMD_NOT_ALLOWED:
		वापस "command not allowed";
	हाल AL_ERR_INVALID_CMD_VALUE:
		वापस "invalid command value";
	हाल AL_ERROR:
	शेष:
		वापस "unknown error";
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक estimate_stream_size(अचिन्हित पूर्णांक width,
					 अचिन्हित पूर्णांक height)
अणु
	अचिन्हित पूर्णांक offset = ENCODER_STREAM_OFFSET;
	अचिन्हित पूर्णांक num_blocks = DIV_ROUND_UP(width, SIZE_MACROBLOCK) *
					DIV_ROUND_UP(height, SIZE_MACROBLOCK);
	अचिन्हित पूर्णांक pcm_size = SZ_256;
	अचिन्हित पूर्णांक partition_table = SZ_256;

	वापस round_up(offset + num_blocks * pcm_size + partition_table, 32);
पूर्ण

अटल क्रमागत v4l2_mpeg_video_h264_level
select_minimum_h264_level(अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height)
अणु
	अचिन्हित पूर्णांक pic_width_in_mb = DIV_ROUND_UP(width, SIZE_MACROBLOCK);
	अचिन्हित पूर्णांक frame_height_in_mb = DIV_ROUND_UP(height, SIZE_MACROBLOCK);
	अचिन्हित पूर्णांक frame_size_in_mb = pic_width_in_mb * frame_height_in_mb;
	क्रमागत v4l2_mpeg_video_h264_level level = V4L2_MPEG_VIDEO_H264_LEVEL_4_0;

	/*
	 * The level limits are specअगरied in Rec. ITU-T H.264 Annex A.3.1 and
	 * also specअगरy limits regarding bit rate and CBP size. Only approximate
	 * the levels using the frame size.
	 *
	 * Level 5.1 allows up to 4k video resolution.
	 */
	अगर (frame_size_in_mb <= 99)
		level = V4L2_MPEG_VIDEO_H264_LEVEL_1_0;
	अन्यथा अगर (frame_size_in_mb <= 396)
		level = V4L2_MPEG_VIDEO_H264_LEVEL_1_1;
	अन्यथा अगर (frame_size_in_mb <= 792)
		level = V4L2_MPEG_VIDEO_H264_LEVEL_2_1;
	अन्यथा अगर (frame_size_in_mb <= 1620)
		level = V4L2_MPEG_VIDEO_H264_LEVEL_2_2;
	अन्यथा अगर (frame_size_in_mb <= 3600)
		level = V4L2_MPEG_VIDEO_H264_LEVEL_3_1;
	अन्यथा अगर (frame_size_in_mb <= 5120)
		level = V4L2_MPEG_VIDEO_H264_LEVEL_3_2;
	अन्यथा अगर (frame_size_in_mb <= 8192)
		level = V4L2_MPEG_VIDEO_H264_LEVEL_4_0;
	अन्यथा अगर (frame_size_in_mb <= 8704)
		level = V4L2_MPEG_VIDEO_H264_LEVEL_4_2;
	अन्यथा अगर (frame_size_in_mb <= 22080)
		level = V4L2_MPEG_VIDEO_H264_LEVEL_5_0;
	अन्यथा
		level = V4L2_MPEG_VIDEO_H264_LEVEL_5_1;

	वापस level;
पूर्ण

अटल अचिन्हित पूर्णांक h264_maximum_bitrate(क्रमागत v4l2_mpeg_video_h264_level level)
अणु
	चयन (level) अणु
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_1_0:
		वापस 64000;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_1B:
		वापस 128000;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_1_1:
		वापस 192000;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_1_2:
		वापस 384000;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_1_3:
		वापस 768000;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_2_0:
		वापस 2000000;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_2_1:
		वापस 4000000;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_2_2:
		वापस 4000000;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_3_0:
		वापस 10000000;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_3_1:
		वापस 14000000;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_3_2:
		वापस 20000000;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_4_0:
		वापस 20000000;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_4_1:
		वापस 50000000;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_4_2:
		वापस 50000000;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_5_0:
		वापस 135000000;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_5_1:
	शेष:
		वापस 240000000;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक h264_maximum_cpb_size(क्रमागत v4l2_mpeg_video_h264_level level)
अणु
	चयन (level) अणु
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_1_0:
		वापस 175;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_1B:
		वापस 350;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_1_1:
		वापस 500;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_1_2:
		वापस 1000;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_1_3:
		वापस 2000;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_2_0:
		वापस 2000;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_2_1:
		वापस 4000;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_2_2:
		वापस 4000;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_3_0:
		वापस 10000;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_3_1:
		वापस 14000;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_3_2:
		वापस 20000;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_4_0:
		वापस 25000;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_4_1:
		वापस 62500;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_4_2:
		वापस 62500;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_5_0:
		वापस 135000;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_5_1:
	शेष:
		वापस 240000;
	पूर्ण
पूर्ण

अटल क्रमागत v4l2_mpeg_video_hevc_level
select_minimum_hevc_level(अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height)
अणु
	अचिन्हित पूर्णांक luma_picture_size = width * height;
	क्रमागत v4l2_mpeg_video_hevc_level level;

	अगर (luma_picture_size <= 36864)
		level = V4L2_MPEG_VIDEO_HEVC_LEVEL_1;
	अन्यथा अगर (luma_picture_size <= 122880)
		level = V4L2_MPEG_VIDEO_HEVC_LEVEL_2;
	अन्यथा अगर (luma_picture_size <= 245760)
		level = V4L2_MPEG_VIDEO_HEVC_LEVEL_2_1;
	अन्यथा अगर (luma_picture_size <= 552960)
		level = V4L2_MPEG_VIDEO_HEVC_LEVEL_3;
	अन्यथा अगर (luma_picture_size <= 983040)
		level = V4L2_MPEG_VIDEO_HEVC_LEVEL_3_1;
	अन्यथा अगर (luma_picture_size <= 2228224)
		level = V4L2_MPEG_VIDEO_HEVC_LEVEL_4;
	अन्यथा अगर (luma_picture_size <= 8912896)
		level = V4L2_MPEG_VIDEO_HEVC_LEVEL_5;
	अन्यथा
		level = V4L2_MPEG_VIDEO_HEVC_LEVEL_6;

	वापस level;
पूर्ण

अटल अचिन्हित पूर्णांक hevc_maximum_bitrate(क्रमागत v4l2_mpeg_video_hevc_level level)
अणु
	/*
	 * See Rec. ITU-T H.265 v5 (02/2018), A.4.2 Profile-specअगरic level
	 * limits क्रम the video profiles.
	 */
	चयन (level) अणु
	हाल V4L2_MPEG_VIDEO_HEVC_LEVEL_1:
		वापस 128;
	हाल V4L2_MPEG_VIDEO_HEVC_LEVEL_2:
		वापस 1500;
	हाल V4L2_MPEG_VIDEO_HEVC_LEVEL_2_1:
		वापस 3000;
	हाल V4L2_MPEG_VIDEO_HEVC_LEVEL_3:
		वापस 6000;
	हाल V4L2_MPEG_VIDEO_HEVC_LEVEL_3_1:
		वापस 10000;
	हाल V4L2_MPEG_VIDEO_HEVC_LEVEL_4:
		वापस 12000;
	हाल V4L2_MPEG_VIDEO_HEVC_LEVEL_4_1:
		वापस 20000;
	हाल V4L2_MPEG_VIDEO_HEVC_LEVEL_5:
		वापस 25000;
	शेष:
	हाल V4L2_MPEG_VIDEO_HEVC_LEVEL_5_1:
		वापस 40000;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक hevc_maximum_cpb_size(क्रमागत v4l2_mpeg_video_hevc_level level)
अणु
	चयन (level) अणु
	हाल V4L2_MPEG_VIDEO_HEVC_LEVEL_1:
		वापस 350;
	हाल V4L2_MPEG_VIDEO_HEVC_LEVEL_2:
		वापस 1500;
	हाल V4L2_MPEG_VIDEO_HEVC_LEVEL_2_1:
		वापस 3000;
	हाल V4L2_MPEG_VIDEO_HEVC_LEVEL_3:
		वापस 6000;
	हाल V4L2_MPEG_VIDEO_HEVC_LEVEL_3_1:
		वापस 10000;
	हाल V4L2_MPEG_VIDEO_HEVC_LEVEL_4:
		वापस 12000;
	हाल V4L2_MPEG_VIDEO_HEVC_LEVEL_4_1:
		वापस 20000;
	हाल V4L2_MPEG_VIDEO_HEVC_LEVEL_5:
		वापस 25000;
	शेष:
	हाल V4L2_MPEG_VIDEO_HEVC_LEVEL_5_1:
		वापस 40000;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा fw_info *
allegro_get_firmware_info(काष्ठा allegro_dev *dev,
			  स्थिर काष्ठा firmware *fw,
			  स्थिर काष्ठा firmware *fw_codec)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक id = fw->size;
	अचिन्हित पूर्णांक id_codec = fw_codec->size;

	क्रम (i = 0; i < ARRAY_SIZE(supported_firmware); i++)
		अगर (supported_firmware[i].id == id &&
		    supported_firmware[i].id_codec == id_codec)
			वापस &supported_firmware[i];

	वापस शून्य;
पूर्ण

/*
 * Buffers that are used पूर्णांकernally by the MCU.
 */

अटल पूर्णांक allegro_alloc_buffer(काष्ठा allegro_dev *dev,
				काष्ठा allegro_buffer *buffer, माप_प्रकार size)
अणु
	buffer->vaddr = dma_alloc_coherent(&dev->plat_dev->dev, size,
					   &buffer->paddr, GFP_KERNEL);
	अगर (!buffer->vaddr)
		वापस -ENOMEM;
	buffer->size = size;

	वापस 0;
पूर्ण

अटल व्योम allegro_मुक्त_buffer(काष्ठा allegro_dev *dev,
				काष्ठा allegro_buffer *buffer)
अणु
	अगर (buffer->vaddr) अणु
		dma_मुक्त_coherent(&dev->plat_dev->dev, buffer->size,
				  buffer->vaddr, buffer->paddr);
		buffer->vaddr = शून्य;
		buffer->size = 0;
	पूर्ण
पूर्ण

/*
 * Mailbox पूर्णांकerface to send messages to the MCU.
 */

अटल व्योम allegro_mcu_पूर्णांकerrupt(काष्ठा allegro_dev *dev);
अटल व्योम allegro_handle_message(काष्ठा allegro_dev *dev,
				   जोड़ mcu_msg_response *msg);

अटल काष्ठा allegro_mbox *allegro_mbox_init(काष्ठा allegro_dev *dev,
					      अचिन्हित पूर्णांक base, माप_प्रकार size)
अणु
	काष्ठा allegro_mbox *mbox;

	mbox = devm_kदो_स्मृति(&dev->plat_dev->dev, माप(*mbox), GFP_KERNEL);
	अगर (!mbox)
		वापस ERR_PTR(-ENOMEM);

	mbox->dev = dev;

	mbox->head = base;
	mbox->tail = base + 0x4;
	mbox->data = base + 0x8;
	mbox->size = size;
	mutex_init(&mbox->lock);

	regmap_ग_लिखो(dev->sram, mbox->head, 0);
	regmap_ग_लिखो(dev->sram, mbox->tail, 0);

	वापस mbox;
पूर्ण

अटल पूर्णांक allegro_mbox_ग_लिखो(काष्ठा allegro_mbox *mbox,
			      स्थिर u32 *src, माप_प्रकार size)
अणु
	काष्ठा regmap *sram = mbox->dev->sram;
	अचिन्हित पूर्णांक tail;
	माप_प्रकार size_no_wrap;
	पूर्णांक err = 0;
	पूर्णांक stride = regmap_get_reg_stride(sram);

	अगर (!src)
		वापस -EINVAL;

	अगर (size > mbox->size)
		वापस -EINVAL;

	mutex_lock(&mbox->lock);
	regmap_पढ़ो(sram, mbox->tail, &tail);
	अगर (tail > mbox->size) अणु
		err = -EIO;
		जाओ out;
	पूर्ण
	size_no_wrap = min(size, mbox->size - (माप_प्रकार)tail);
	regmap_bulk_ग_लिखो(sram, mbox->data + tail,
			  src, size_no_wrap / stride);
	regmap_bulk_ग_लिखो(sram, mbox->data,
			  src + (size_no_wrap / माप(*src)),
			  (size - size_no_wrap) / stride);
	regmap_ग_लिखो(sram, mbox->tail, (tail + size) % mbox->size);

out:
	mutex_unlock(&mbox->lock);

	वापस err;
पूर्ण

अटल sमाप_प्रकार allegro_mbox_पढ़ो(काष्ठा allegro_mbox *mbox,
				 u32 *dst, माप_प्रकार nbyte)
अणु
	काष्ठा अणु
		u16 length;
		u16 type;
	पूर्ण __attribute__ ((__packed__)) *header;
	काष्ठा regmap *sram = mbox->dev->sram;
	अचिन्हित पूर्णांक head;
	sमाप_प्रकार size;
	माप_प्रकार body_no_wrap;
	पूर्णांक stride = regmap_get_reg_stride(sram);

	regmap_पढ़ो(sram, mbox->head, &head);
	अगर (head > mbox->size)
		वापस -EIO;

	/* Assume that the header करोes not wrap. */
	regmap_bulk_पढ़ो(sram, mbox->data + head,
			 dst, माप(*header) / stride);
	header = (व्योम *)dst;
	size = header->length + माप(*header);
	अगर (size > mbox->size || size & 0x3)
		वापस -EIO;
	अगर (size > nbyte)
		वापस -EINVAL;

	/*
	 * The message might wrap within the mailbox. If the message करोes not
	 * wrap, the first पढ़ो will पढ़ो the entire message, otherwise the
	 * first पढ़ो will पढ़ो message until the end of the mailbox and the
	 * second पढ़ो will पढ़ो the reमुख्यing bytes from the beginning of the
	 * mailbox.
	 *
	 * Skip the header, as was alपढ़ोy पढ़ो to get the size of the body.
	 */
	body_no_wrap = min((माप_प्रकार)header->length,
			   (माप_प्रकार)(mbox->size - (head + माप(*header))));
	regmap_bulk_पढ़ो(sram, mbox->data + head + माप(*header),
			 dst + (माप(*header) / माप(*dst)),
			 body_no_wrap / stride);
	regmap_bulk_पढ़ो(sram, mbox->data,
			 dst + (माप(*header) + body_no_wrap) / माप(*dst),
			 (header->length - body_no_wrap) / stride);

	regmap_ग_लिखो(sram, mbox->head, (head + size) % mbox->size);

	वापस size;
पूर्ण

/**
 * allegro_mbox_send() - Send a message via the mailbox
 * @mbox: the mailbox which is used to send the message
 * @msg: the message to send
 */
अटल पूर्णांक allegro_mbox_send(काष्ठा allegro_mbox *mbox, व्योम *msg)
अणु
	काष्ठा allegro_dev *dev = mbox->dev;
	sमाप_प्रकार size;
	पूर्णांक err;
	u32 *पंचांगp;

	पंचांगp = kzalloc(mbox->size, GFP_KERNEL);
	अगर (!पंचांगp) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	size = allegro_encode_mail(पंचांगp, msg);

	err = allegro_mbox_ग_लिखो(mbox, पंचांगp, size);
	kमुक्त(पंचांगp);
	अगर (err)
		जाओ out;

	allegro_mcu_पूर्णांकerrupt(dev);

out:
	वापस err;
पूर्ण

/**
 * allegro_mbox_notअगरy() - Notअगरy the mailbox about a new message
 * @mbox: The allegro_mbox to notअगरy
 */
अटल व्योम allegro_mbox_notअगरy(काष्ठा allegro_mbox *mbox)
अणु
	काष्ठा allegro_dev *dev = mbox->dev;
	जोड़ mcu_msg_response *msg;
	sमाप_प्रकार size;
	u32 *पंचांगp;
	पूर्णांक err;

	msg = kदो_स्मृति(माप(*msg), GFP_KERNEL);
	अगर (!msg)
		वापस;

	msg->header.version = dev->fw_info->mailbox_version;

	पंचांगp = kदो_स्मृति(mbox->size, GFP_KERNEL);
	अगर (!पंचांगp)
		जाओ out;

	size = allegro_mbox_पढ़ो(mbox, पंचांगp, mbox->size);
	अगर (size < 0)
		जाओ out;

	err = allegro_decode_mail(msg, पंचांगp);
	अगर (err)
		जाओ out;

	allegro_handle_message(dev, msg);

out:
	kमुक्त(पंचांगp);
	kमुक्त(msg);
पूर्ण

अटल व्योम allegro_mcu_send_init(काष्ठा allegro_dev *dev,
				  dma_addr_t suballoc_dma, माप_प्रकार suballoc_size)
अणु
	काष्ठा mcu_msg_init_request msg;

	स_रखो(&msg, 0, माप(msg));

	msg.header.type = MCU_MSG_TYPE_INIT;
	msg.header.version = dev->fw_info->mailbox_version;

	msg.suballoc_dma = to_mcu_addr(dev, suballoc_dma);
	msg.suballoc_size = to_mcu_size(dev, suballoc_size);

	/* disable L2 cache */
	msg.l2_cache[0] = -1;
	msg.l2_cache[1] = -1;
	msg.l2_cache[2] = -1;

	allegro_mbox_send(dev->mbox_command, &msg);
पूर्ण

अटल u32 v4l2_pixelक्रमmat_to_mcu_क्रमmat(u32 pixelक्रमmat)
अणु
	चयन (pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_NV12:
		/* AL_420_8BITS: 0x100 -> NV12, 0x88 -> 8 bit */
		वापस 0x100 | 0x88;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल u32 v4l2_colorspace_to_mcu_colorspace(क्रमागत v4l2_colorspace colorspace)
अणु
	चयन (colorspace) अणु
	हाल V4L2_COLORSPACE_REC709:
		वापस 2;
	हाल V4L2_COLORSPACE_SMPTE170M:
		वापस 3;
	हाल V4L2_COLORSPACE_SMPTE240M:
		वापस 4;
	हाल V4L2_COLORSPACE_SRGB:
		वापस 7;
	शेष:
		/* UNKNOWN */
		वापस 0;
	पूर्ण
पूर्ण

अटल u8 v4l2_profile_to_mcu_profile(क्रमागत v4l2_mpeg_video_h264_profile profile)
अणु
	चयन (profile) अणु
	हाल V4L2_MPEG_VIDEO_H264_PROखाता_BASELINE:
	शेष:
		वापस 66;
	पूर्ण
पूर्ण

अटल u16 v4l2_level_to_mcu_level(क्रमागत v4l2_mpeg_video_h264_level level)
अणु
	चयन (level) अणु
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_1_0:
		वापस 10;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_1_1:
		वापस 11;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_1_2:
		वापस 12;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_1_3:
		वापस 13;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_2_0:
		वापस 20;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_2_1:
		वापस 21;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_2_2:
		वापस 22;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_3_0:
		वापस 30;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_3_1:
		वापस 31;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_3_2:
		वापस 32;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_4_0:
		वापस 40;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_4_1:
		वापस 41;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_4_2:
		वापस 42;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_5_0:
		वापस 50;
	हाल V4L2_MPEG_VIDEO_H264_LEVEL_5_1:
	शेष:
		वापस 51;
	पूर्ण
पूर्ण

अटल u8 hevc_profile_to_mcu_profile(क्रमागत v4l2_mpeg_video_hevc_profile profile)
अणु
	चयन (profile) अणु
	शेष:
	हाल V4L2_MPEG_VIDEO_HEVC_PROखाता_MAIN:
		वापस 1;
	हाल V4L2_MPEG_VIDEO_HEVC_PROखाता_MAIN_10:
		वापस 2;
	हाल V4L2_MPEG_VIDEO_HEVC_PROखाता_MAIN_STILL_PICTURE:
		वापस 3;
	पूर्ण
पूर्ण

अटल u16 hevc_level_to_mcu_level(क्रमागत v4l2_mpeg_video_hevc_level level)
अणु
	चयन (level) अणु
	हाल V4L2_MPEG_VIDEO_HEVC_LEVEL_1:
		वापस 10;
	हाल V4L2_MPEG_VIDEO_HEVC_LEVEL_2:
		वापस 20;
	हाल V4L2_MPEG_VIDEO_HEVC_LEVEL_2_1:
		वापस 21;
	हाल V4L2_MPEG_VIDEO_HEVC_LEVEL_3:
		वापस 30;
	हाल V4L2_MPEG_VIDEO_HEVC_LEVEL_3_1:
		वापस 31;
	हाल V4L2_MPEG_VIDEO_HEVC_LEVEL_4:
		वापस 40;
	हाल V4L2_MPEG_VIDEO_HEVC_LEVEL_4_1:
		वापस 41;
	हाल V4L2_MPEG_VIDEO_HEVC_LEVEL_5:
		वापस 50;
	शेष:
	हाल V4L2_MPEG_VIDEO_HEVC_LEVEL_5_1:
		वापस 51;
	पूर्ण
पूर्ण

अटल u8 hevc_tier_to_mcu_tier(क्रमागत v4l2_mpeg_video_hevc_tier tier)
अणु
	चयन (tier) अणु
	शेष:
	हाल V4L2_MPEG_VIDEO_HEVC_TIER_MAIN:
		वापस 0;
	हाल V4L2_MPEG_VIDEO_HEVC_TIER_HIGH:
		वापस 1;
	पूर्ण
पूर्ण

अटल u32
v4l2_bitrate_mode_to_mcu_mode(क्रमागत v4l2_mpeg_video_bitrate_mode mode)
अणु
	चयन (mode) अणु
	हाल V4L2_MPEG_VIDEO_BITRATE_MODE_VBR:
		वापस 2;
	हाल V4L2_MPEG_VIDEO_BITRATE_MODE_CBR:
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

अटल u32 v4l2_cpb_माप_प्रकारo_mcu(अचिन्हित पूर्णांक cpb_size, अचिन्हित पूर्णांक bitrate)
अणु
	अचिन्हित पूर्णांक cpb_size_kbit;
	अचिन्हित पूर्णांक bitrate_kbps;

	/*
	 * The mcu expects the CPB size in units of a 90 kHz घड़ी, but the
	 * channel follows the V4L2_CID_MPEG_VIDEO_H264_CPB_SIZE and stores
	 * the CPB size in kilobytes.
	 */
	cpb_size_kbit = cpb_size * BITS_PER_BYTE;
	bitrate_kbps = bitrate / 1000;

	वापस (cpb_size_kbit * 90000) / bitrate_kbps;
पूर्ण

अटल s16 get_qp_delta(पूर्णांक minuend, पूर्णांक subtrahend)
अणु
	अगर (minuend == subtrahend)
		वापस -1;
	अन्यथा
		वापस minuend - subtrahend;
पूर्ण

अटल u32 allegro_channel_get_entropy_mode(काष्ठा allegro_channel *channel)
अणु
#घोषणा ALLEGRO_ENTROPY_MODE_CAVLC 0
#घोषणा ALLEGRO_ENTROPY_MODE_CABAC 1

	/* HEVC always uses CABAC, but this has to be explicitly set */
	अगर (channel->codec == V4L2_PIX_FMT_HEVC)
		वापस ALLEGRO_ENTROPY_MODE_CABAC;

	वापस ALLEGRO_ENTROPY_MODE_CAVLC;
पूर्ण

अटल पूर्णांक fill_create_channel_param(काष्ठा allegro_channel *channel,
				     काष्ठा create_channel_param *param)
अणु
	पूर्णांक i_frame_qp = allegro_channel_get_i_frame_qp(channel);
	पूर्णांक p_frame_qp = allegro_channel_get_p_frame_qp(channel);
	पूर्णांक b_frame_qp = allegro_channel_get_b_frame_qp(channel);
	पूर्णांक bitrate_mode = v4l2_ctrl_g_ctrl(channel->mpeg_video_bitrate_mode);
	अचिन्हित पूर्णांक cpb_size = v4l2_ctrl_g_ctrl(channel->mpeg_video_cpb_size);

	param->width = channel->width;
	param->height = channel->height;
	param->क्रमmat = v4l2_pixelक्रमmat_to_mcu_क्रमmat(channel->pixelक्रमmat);
	param->colorspace =
		v4l2_colorspace_to_mcu_colorspace(channel->colorspace);
	param->src_mode = 0x0;

	param->codec = channel->codec;
	अगर (channel->codec == V4L2_PIX_FMT_H264) अणु
		क्रमागत v4l2_mpeg_video_h264_profile profile;
		क्रमागत v4l2_mpeg_video_h264_level level;

		profile = v4l2_ctrl_g_ctrl(channel->mpeg_video_h264_profile);
		level = v4l2_ctrl_g_ctrl(channel->mpeg_video_h264_level);

		param->profile = v4l2_profile_to_mcu_profile(profile);
		param->स्थिरraपूर्णांक_set_flags = BIT(1);
		param->level = v4l2_level_to_mcu_level(level);
	पूर्ण अन्यथा अणु
		क्रमागत v4l2_mpeg_video_hevc_profile profile;
		क्रमागत v4l2_mpeg_video_hevc_level level;
		क्रमागत v4l2_mpeg_video_hevc_tier tier;

		profile = v4l2_ctrl_g_ctrl(channel->mpeg_video_hevc_profile);
		level = v4l2_ctrl_g_ctrl(channel->mpeg_video_hevc_level);
		tier = v4l2_ctrl_g_ctrl(channel->mpeg_video_hevc_tier);

		param->profile = hevc_profile_to_mcu_profile(profile);
		param->level = hevc_level_to_mcu_level(level);
		param->tier = hevc_tier_to_mcu_tier(tier);
	पूर्ण

	param->log2_max_poc = LOG2_MAX_PIC_ORDER_CNT;
	param->log2_max_frame_num = channel->log2_max_frame_num;
	param->temporal_mvp_enable = channel->temporal_mvp_enable;

	param->dbf_ovr_en = channel->dbf_ovr_en;
	param->override_lf = channel->enable_deblocking_filter_override;
	param->enable_reordering = channel->enable_reordering;
	param->entropy_mode = allegro_channel_get_entropy_mode(channel);
	param->rकरो_cost_mode = 1;
	param->custom_lda = 1;
	param->lf = 1;
	param->lf_x_tile = channel->enable_loop_filter_across_tiles;
	param->lf_x_slice = channel->enable_loop_filter_across_slices;

	param->src_bit_depth = 8;

	param->beta_offset = BETA_OFFSET_DIV_2;
	param->tc_offset = TC_OFFSET_DIV_2;
	param->num_slices = 1;
	param->me_range[0] = channel->b_hrz_me_range;
	param->me_range[1] = channel->b_vrt_me_range;
	param->me_range[2] = channel->p_hrz_me_range;
	param->me_range[3] = channel->p_vrt_me_range;
	param->max_cu_size = channel->max_cu_size;
	param->min_cu_size = channel->min_cu_size;
	param->max_tu_size = channel->max_tu_size;
	param->min_tu_size = channel->min_tu_size;
	param->max_transfo_depth_पूर्णांकra = channel->max_transfo_depth_पूर्णांकra;
	param->max_transfo_depth_पूर्णांकer = channel->max_transfo_depth_पूर्णांकer;

	param->prefetch_स्वतः = 0;
	param->prefetch_mem_offset = 0;
	param->prefetch_mem_size = 0;

	param->rate_control_mode = channel->frame_rc_enable ?
		v4l2_bitrate_mode_to_mcu_mode(bitrate_mode) : 0;

	param->cpb_size = v4l2_cpb_माप_प्रकारo_mcu(cpb_size, channel->bitrate_peak);
	/* Shall be ]0;cpb_size in 90 kHz units]. Use maximum value. */
	param->initial_rem_delay = param->cpb_size;
	param->framerate = DIV_ROUND_UP(channel->framerate.numerator,
					channel->framerate.denominator);
	param->clk_ratio = channel->framerate.denominator == 1001 ? 1001 : 1000;
	param->target_bitrate = channel->bitrate;
	param->max_bitrate = channel->bitrate_peak;
	param->initial_qp = i_frame_qp;
	param->min_qp = allegro_channel_get_min_qp(channel);
	param->max_qp = allegro_channel_get_max_qp(channel);
	param->ip_delta = get_qp_delta(i_frame_qp, p_frame_qp);
	param->pb_delta = get_qp_delta(p_frame_qp, b_frame_qp);
	param->golden_ref = 0;
	param->golden_delta = 2;
	param->golden_ref_frequency = 10;
	param->rate_control_option = 0x00000000;

	param->num_pixel = channel->width + channel->height;
	param->max_psnr = 4200;
	param->max_pixel_value = 255;

	param->gop_ctrl_mode = 0x00000002;
	param->freq_idr = v4l2_ctrl_g_ctrl(channel->mpeg_video_gop_size);
	param->freq_lt = 0;
	param->gdr_mode = 0x00000000;
	param->gop_length = v4l2_ctrl_g_ctrl(channel->mpeg_video_gop_size);
	param->subframe_latency = 0x00000000;

	param->lda_factors[0] = 51;
	param->lda_factors[1] = 90;
	param->lda_factors[2] = 151;
	param->lda_factors[3] = 151;
	param->lda_factors[4] = 151;
	param->lda_factors[5] = 151;

	param->max_num_merge_cand = 5;

	वापस 0;
पूर्ण

अटल पूर्णांक allegro_mcu_send_create_channel(काष्ठा allegro_dev *dev,
					   काष्ठा allegro_channel *channel)
अणु
	काष्ठा mcu_msg_create_channel msg;
	काष्ठा allegro_buffer *blob = &channel->config_blob;
	काष्ठा create_channel_param param;
	माप_प्रकार size;

	स_रखो(&param, 0, माप(param));
	fill_create_channel_param(channel, &param);
	allegro_alloc_buffer(dev, blob, माप(काष्ठा create_channel_param));
	param.version = dev->fw_info->mailbox_version;
	size = allegro_encode_config_blob(blob->vaddr, &param);

	स_रखो(&msg, 0, माप(msg));

	msg.header.type = MCU_MSG_TYPE_CREATE_CHANNEL;
	msg.header.version = dev->fw_info->mailbox_version;

	msg.user_id = channel->user_id;

	msg.blob = blob->vaddr;
	msg.blob_size = size;
	msg.blob_mcu_addr = to_mcu_addr(dev, blob->paddr);

	allegro_mbox_send(dev->mbox_command, &msg);

	वापस 0;
पूर्ण

अटल पूर्णांक allegro_mcu_send_destroy_channel(काष्ठा allegro_dev *dev,
					    काष्ठा allegro_channel *channel)
अणु
	काष्ठा mcu_msg_destroy_channel msg;

	स_रखो(&msg, 0, माप(msg));

	msg.header.type = MCU_MSG_TYPE_DESTROY_CHANNEL;
	msg.header.version = dev->fw_info->mailbox_version;

	msg.channel_id = channel->mcu_channel_id;

	allegro_mbox_send(dev->mbox_command, &msg);

	वापस 0;
पूर्ण

अटल पूर्णांक allegro_mcu_send_put_stream_buffer(काष्ठा allegro_dev *dev,
					      काष्ठा allegro_channel *channel,
					      dma_addr_t paddr,
					      अचिन्हित दीर्घ size,
					      u64 dst_handle)
अणु
	काष्ठा mcu_msg_put_stream_buffer msg;

	स_रखो(&msg, 0, माप(msg));

	msg.header.type = MCU_MSG_TYPE_PUT_STREAM_BUFFER;
	msg.header.version = dev->fw_info->mailbox_version;

	msg.channel_id = channel->mcu_channel_id;
	msg.dma_addr = to_codec_addr(dev, paddr);
	msg.mcu_addr = to_mcu_addr(dev, paddr);
	msg.size = size;
	msg.offset = ENCODER_STREAM_OFFSET;
	/* copied to mcu_msg_encode_frame_response */
	msg.dst_handle = dst_handle;

	allegro_mbox_send(dev->mbox_command, &msg);

	वापस 0;
पूर्ण

अटल पूर्णांक allegro_mcu_send_encode_frame(काष्ठा allegro_dev *dev,
					 काष्ठा allegro_channel *channel,
					 dma_addr_t src_y, dma_addr_t src_uv,
					 u64 src_handle)
अणु
	काष्ठा mcu_msg_encode_frame msg;

	स_रखो(&msg, 0, माप(msg));

	msg.header.type = MCU_MSG_TYPE_ENCODE_FRAME;
	msg.header.version = dev->fw_info->mailbox_version;

	msg.channel_id = channel->mcu_channel_id;
	msg.encoding_options = AL_OPT_FORCE_LOAD;
	msg.pps_qp = 26; /* qp are relative to 26 */
	msg.user_param = 0; /* copied to mcu_msg_encode_frame_response */
	/* src_handle is copied to mcu_msg_encode_frame_response */
	msg.src_handle = src_handle;
	msg.src_y = to_codec_addr(dev, src_y);
	msg.src_uv = to_codec_addr(dev, src_uv);
	msg.stride = channel->stride;
	msg.ep2 = 0x0;
	msg.ep2_v = to_mcu_addr(dev, msg.ep2);

	allegro_mbox_send(dev->mbox_command, &msg);

	वापस 0;
पूर्ण

अटल पूर्णांक allegro_mcu_रुको_क्रम_init_समयout(काष्ठा allegro_dev *dev,
					     अचिन्हित दीर्घ समयout_ms)
अणु
	अचिन्हित दीर्घ पंचांगo;

	पंचांगo = रुको_क्रम_completion_समयout(&dev->init_complete,
					  msecs_to_jअगरfies(समयout_ms));
	अगर (पंचांगo == 0)
		वापस -ETIMEDOUT;

	reinit_completion(&dev->init_complete);
	वापस 0;
पूर्ण

अटल पूर्णांक allegro_mcu_push_buffer_पूर्णांकernal(काष्ठा allegro_channel *channel,
					    क्रमागत mcu_msg_type type)
अणु
	काष्ठा allegro_dev *dev = channel->dev;
	काष्ठा mcu_msg_push_buffers_पूर्णांकernal *msg;
	काष्ठा mcu_msg_push_buffers_पूर्णांकernal_buffer *buffer;
	अचिन्हित पूर्णांक num_buffers = 0;
	माप_प्रकार size;
	काष्ठा allegro_buffer *al_buffer;
	काष्ठा list_head *list;
	पूर्णांक err;

	चयन (type) अणु
	हाल MCU_MSG_TYPE_PUSH_BUFFER_REFERENCE:
		list = &channel->buffers_reference;
		अवरोध;
	हाल MCU_MSG_TYPE_PUSH_BUFFER_INTERMEDIATE:
		list = &channel->buffers_पूर्णांकermediate;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	list_क्रम_each_entry(al_buffer, list, head)
		num_buffers++;
	size = काष्ठा_size(msg, buffer, num_buffers);

	msg = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	msg->header.type = type;
	msg->header.version = dev->fw_info->mailbox_version;

	msg->channel_id = channel->mcu_channel_id;
	msg->num_buffers = num_buffers;

	buffer = msg->buffer;
	list_क्रम_each_entry(al_buffer, list, head) अणु
		buffer->dma_addr = to_codec_addr(dev, al_buffer->paddr);
		buffer->mcu_addr = to_mcu_addr(dev, al_buffer->paddr);
		buffer->size = to_mcu_size(dev, al_buffer->size);
		buffer++;
	पूर्ण

	err = allegro_mbox_send(dev->mbox_command, msg);

	kमुक्त(msg);
	वापस err;
पूर्ण

अटल पूर्णांक allegro_mcu_push_buffer_पूर्णांकermediate(काष्ठा allegro_channel *channel)
अणु
	क्रमागत mcu_msg_type type = MCU_MSG_TYPE_PUSH_BUFFER_INTERMEDIATE;

	वापस allegro_mcu_push_buffer_पूर्णांकernal(channel, type);
पूर्ण

अटल पूर्णांक allegro_mcu_push_buffer_reference(काष्ठा allegro_channel *channel)
अणु
	क्रमागत mcu_msg_type type = MCU_MSG_TYPE_PUSH_BUFFER_REFERENCE;

	वापस allegro_mcu_push_buffer_पूर्णांकernal(channel, type);
पूर्ण

अटल पूर्णांक allocate_buffers_पूर्णांकernal(काष्ठा allegro_channel *channel,
				     काष्ठा list_head *list,
				     माप_प्रकार n, माप_प्रकार size)
अणु
	काष्ठा allegro_dev *dev = channel->dev;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;
	काष्ठा allegro_buffer *buffer, *पंचांगp;

	क्रम (i = 0; i < n; i++) अणु
		buffer = kदो_स्मृति(माप(*buffer), GFP_KERNEL);
		अगर (!buffer) अणु
			err = -ENOMEM;
			जाओ err;
		पूर्ण
		INIT_LIST_HEAD(&buffer->head);

		err = allegro_alloc_buffer(dev, buffer, size);
		अगर (err)
			जाओ err;
		list_add(&buffer->head, list);
	पूर्ण

	वापस 0;

err:
	list_क्रम_each_entry_safe(buffer, पंचांगp, list, head) अणु
		list_del(&buffer->head);
		allegro_मुक्त_buffer(dev, buffer);
		kमुक्त(buffer);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम destroy_buffers_पूर्णांकernal(काष्ठा allegro_channel *channel,
				     काष्ठा list_head *list)
अणु
	काष्ठा allegro_dev *dev = channel->dev;
	काष्ठा allegro_buffer *buffer, *पंचांगp;

	list_क्रम_each_entry_safe(buffer, पंचांगp, list, head) अणु
		list_del(&buffer->head);
		allegro_मुक्त_buffer(dev, buffer);
		kमुक्त(buffer);
	पूर्ण
पूर्ण

अटल व्योम destroy_reference_buffers(काष्ठा allegro_channel *channel)
अणु
	वापस destroy_buffers_पूर्णांकernal(channel, &channel->buffers_reference);
पूर्ण

अटल व्योम destroy_पूर्णांकermediate_buffers(काष्ठा allegro_channel *channel)
अणु
	वापस destroy_buffers_पूर्णांकernal(channel,
					&channel->buffers_पूर्णांकermediate);
पूर्ण

अटल पूर्णांक allocate_पूर्णांकermediate_buffers(काष्ठा allegro_channel *channel,
					 माप_प्रकार n, माप_प्रकार size)
अणु
	वापस allocate_buffers_पूर्णांकernal(channel,
					 &channel->buffers_पूर्णांकermediate,
					 n, size);
पूर्ण

अटल पूर्णांक allocate_reference_buffers(काष्ठा allegro_channel *channel,
				      माप_प्रकार n, माप_प्रकार size)
अणु
	वापस allocate_buffers_पूर्णांकernal(channel,
					 &channel->buffers_reference,
					 n, PAGE_ALIGN(size));
पूर्ण

अटल sमाप_प्रकार allegro_h264_ग_लिखो_sps(काष्ठा allegro_channel *channel,
				      व्योम *dest, माप_प्रकार n)
अणु
	काष्ठा allegro_dev *dev = channel->dev;
	काष्ठा nal_h264_sps *sps;
	sमाप_प्रकार size;
	अचिन्हित पूर्णांक size_mb = SIZE_MACROBLOCK;
	/* Calculation of crop units in Rec. ITU-T H.264 (04/2017) p. 76 */
	अचिन्हित पूर्णांक crop_unit_x = 2;
	अचिन्हित पूर्णांक crop_unit_y = 2;
	क्रमागत v4l2_mpeg_video_h264_profile profile;
	क्रमागत v4l2_mpeg_video_h264_level level;
	अचिन्हित पूर्णांक cpb_size;
	अचिन्हित पूर्णांक cpb_size_scale;

	sps = kzalloc(माप(*sps), GFP_KERNEL);
	अगर (!sps)
		वापस -ENOMEM;

	profile = v4l2_ctrl_g_ctrl(channel->mpeg_video_h264_profile);
	level = v4l2_ctrl_g_ctrl(channel->mpeg_video_h264_level);

	sps->profile_idc = nal_h264_profile_from_v4l2(profile);
	sps->स्थिरraपूर्णांक_set0_flag = 0;
	sps->स्थिरraपूर्णांक_set1_flag = 1;
	sps->स्थिरraपूर्णांक_set2_flag = 0;
	sps->स्थिरraपूर्णांक_set3_flag = 0;
	sps->स्थिरraपूर्णांक_set4_flag = 0;
	sps->स्थिरraपूर्णांक_set5_flag = 0;
	sps->level_idc = nal_h264_level_from_v4l2(level);
	sps->seq_parameter_set_id = 0;
	sps->log2_max_frame_num_minus4 = LOG2_MAX_FRAME_NUM - 4;
	sps->pic_order_cnt_type = 0;
	sps->log2_max_pic_order_cnt_lsb_minus4 = LOG2_MAX_PIC_ORDER_CNT - 4;
	sps->max_num_ref_frames = 3;
	sps->gaps_in_frame_num_value_allowed_flag = 0;
	sps->pic_width_in_mbs_minus1 =
		DIV_ROUND_UP(channel->width, size_mb) - 1;
	sps->pic_height_in_map_units_minus1 =
		DIV_ROUND_UP(channel->height, size_mb) - 1;
	sps->frame_mbs_only_flag = 1;
	sps->mb_adaptive_frame_field_flag = 0;
	sps->direct_8x8_inference_flag = 1;
	sps->frame_cropping_flag =
		(channel->width % size_mb) || (channel->height % size_mb);
	अगर (sps->frame_cropping_flag) अणु
		sps->crop_left = 0;
		sps->crop_right = (round_up(channel->width, size_mb) - channel->width) / crop_unit_x;
		sps->crop_top = 0;
		sps->crop_bottom = (round_up(channel->height, size_mb) - channel->height) / crop_unit_y;
	पूर्ण
	sps->vui_parameters_present_flag = 1;
	sps->vui.aspect_ratio_info_present_flag = 0;
	sps->vui.overscan_info_present_flag = 0;
	sps->vui.video_संकेत_type_present_flag = 1;
	sps->vui.video_क्रमmat = 1;
	sps->vui.video_full_range_flag = 0;
	sps->vui.colour_description_present_flag = 1;
	sps->vui.colour_primaries = 5;
	sps->vui.transfer_अक्षरacteristics = 5;
	sps->vui.matrix_coefficients = 5;
	sps->vui.chroma_loc_info_present_flag = 1;
	sps->vui.chroma_sample_loc_type_top_field = 0;
	sps->vui.chroma_sample_loc_type_bottom_field = 0;

	sps->vui.timing_info_present_flag = 1;
	sps->vui.num_units_in_tick = channel->framerate.denominator;
	sps->vui.समय_scale = 2 * channel->framerate.numerator;

	sps->vui.fixed_frame_rate_flag = 1;
	sps->vui.nal_hrd_parameters_present_flag = 0;
	sps->vui.vcl_hrd_parameters_present_flag = 1;
	sps->vui.vcl_hrd_parameters.cpb_cnt_minus1 = 0;
	sps->vui.vcl_hrd_parameters.bit_rate_scale = 0;
	/* See Rec. ITU-T H.264 (04/2017) p. 410 E-53 */
	sps->vui.vcl_hrd_parameters.bit_rate_value_minus1[0] =
		channel->bitrate_peak / (1 << (6 + sps->vui.vcl_hrd_parameters.bit_rate_scale)) - 1;
	/* See Rec. ITU-T H.264 (04/2017) p. 410 E-54 */
	cpb_size = v4l2_ctrl_g_ctrl(channel->mpeg_video_cpb_size);
	cpb_size_scale = ffs(cpb_size) - 4;
	sps->vui.vcl_hrd_parameters.cpb_size_scale = cpb_size_scale;
	sps->vui.vcl_hrd_parameters.cpb_size_value_minus1[0] =
		(cpb_size * 1000) / (1 << (4 + cpb_size_scale)) - 1;
	sps->vui.vcl_hrd_parameters.cbr_flag[0] =
		!v4l2_ctrl_g_ctrl(channel->mpeg_video_frame_rc_enable);
	sps->vui.vcl_hrd_parameters.initial_cpb_removal_delay_length_minus1 = 31;
	sps->vui.vcl_hrd_parameters.cpb_removal_delay_length_minus1 = 31;
	sps->vui.vcl_hrd_parameters.dpb_output_delay_length_minus1 = 31;
	sps->vui.vcl_hrd_parameters.समय_offset_length = 0;
	sps->vui.low_delay_hrd_flag = 0;
	sps->vui.pic_काष्ठा_present_flag = 1;
	sps->vui.bitstream_restriction_flag = 0;

	size = nal_h264_ग_लिखो_sps(&dev->plat_dev->dev, dest, n, sps);

	kमुक्त(sps);

	वापस size;
पूर्ण

अटल sमाप_प्रकार allegro_h264_ग_लिखो_pps(काष्ठा allegro_channel *channel,
				      व्योम *dest, माप_प्रकार n)
अणु
	काष्ठा allegro_dev *dev = channel->dev;
	काष्ठा nal_h264_pps *pps;
	sमाप_प्रकार size;

	pps = kzalloc(माप(*pps), GFP_KERNEL);
	अगर (!pps)
		वापस -ENOMEM;

	pps->pic_parameter_set_id = 0;
	pps->seq_parameter_set_id = 0;
	pps->entropy_coding_mode_flag = 0;
	pps->bottom_field_pic_order_in_frame_present_flag = 0;
	pps->num_slice_groups_minus1 = 0;
	pps->num_ref_idx_l0_शेष_active_minus1 = channel->num_ref_idx_l0 - 1;
	pps->num_ref_idx_l1_शेष_active_minus1 = channel->num_ref_idx_l1 - 1;
	pps->weighted_pred_flag = 0;
	pps->weighted_bipred_idc = 0;
	pps->pic_init_qp_minus26 = 0;
	pps->pic_init_qs_minus26 = 0;
	pps->chroma_qp_index_offset = 0;
	pps->deblocking_filter_control_present_flag = 1;
	pps->स्थिरrained_पूर्णांकra_pred_flag = 0;
	pps->redundant_pic_cnt_present_flag = 0;
	pps->transक्रमm_8x8_mode_flag = 0;
	pps->pic_scaling_matrix_present_flag = 0;
	pps->second_chroma_qp_index_offset = 0;

	size = nal_h264_ग_लिखो_pps(&dev->plat_dev->dev, dest, n, pps);

	kमुक्त(pps);

	वापस size;
पूर्ण

अटल व्योम allegro_channel_eos_event(काष्ठा allegro_channel *channel)
अणु
	स्थिर काष्ठा v4l2_event eos_event = अणु
		.type = V4L2_EVENT_EOS
	पूर्ण;

	v4l2_event_queue_fh(&channel->fh, &eos_event);
पूर्ण

अटल sमाप_प्रकार allegro_hevc_ग_लिखो_vps(काष्ठा allegro_channel *channel,
				      व्योम *dest, माप_प्रकार n)
अणु
	काष्ठा allegro_dev *dev = channel->dev;
	काष्ठा nal_hevc_vps *vps;
	काष्ठा nal_hevc_profile_tier_level *ptl;
	sमाप_प्रकार size;
	अचिन्हित पूर्णांक num_ref_frames = channel->num_ref_idx_l0;
	s32 profile = v4l2_ctrl_g_ctrl(channel->mpeg_video_hevc_profile);
	s32 level = v4l2_ctrl_g_ctrl(channel->mpeg_video_hevc_level);
	s32 tier = v4l2_ctrl_g_ctrl(channel->mpeg_video_hevc_tier);

	vps = kzalloc(माप(*vps), GFP_KERNEL);
	अगर (!vps)
		वापस -ENOMEM;

	vps->base_layer_पूर्णांकernal_flag = 1;
	vps->base_layer_available_flag = 1;
	vps->temporal_id_nesting_flag = 1;

	ptl = &vps->profile_tier_level;
	ptl->general_profile_idc = nal_hevc_profile_from_v4l2(profile);
	ptl->general_profile_compatibility_flag[ptl->general_profile_idc] = 1;
	ptl->general_tier_flag = nal_hevc_tier_from_v4l2(tier);
	ptl->general_progressive_source_flag = 1;
	ptl->general_frame_only_स्थिरraपूर्णांक_flag = 1;
	ptl->general_level_idc = nal_hevc_level_from_v4l2(level);

	vps->sub_layer_ordering_info_present_flag = 0;
	vps->max_dec_pic_buffering_minus1[0] = num_ref_frames;
	vps->max_num_reorder_pics[0] = num_ref_frames;

	size = nal_hevc_ग_लिखो_vps(&dev->plat_dev->dev, dest, n, vps);

	kमुक्त(vps);

	वापस size;
पूर्ण

अटल sमाप_प्रकार allegro_hevc_ग_लिखो_sps(काष्ठा allegro_channel *channel,
				      व्योम *dest, माप_प्रकार n)
अणु
	काष्ठा allegro_dev *dev = channel->dev;
	काष्ठा nal_hevc_sps *sps;
	काष्ठा nal_hevc_profile_tier_level *ptl;
	sमाप_प्रकार size;
	अचिन्हित पूर्णांक num_ref_frames = channel->num_ref_idx_l0;
	s32 profile = v4l2_ctrl_g_ctrl(channel->mpeg_video_hevc_profile);
	s32 level = v4l2_ctrl_g_ctrl(channel->mpeg_video_hevc_level);
	s32 tier = v4l2_ctrl_g_ctrl(channel->mpeg_video_hevc_tier);

	sps = kzalloc(माप(*sps), GFP_KERNEL);
	अगर (!sps)
		वापस -ENOMEM;

	sps->temporal_id_nesting_flag = 1;

	ptl = &sps->profile_tier_level;
	ptl->general_profile_idc = nal_hevc_profile_from_v4l2(profile);
	ptl->general_profile_compatibility_flag[ptl->general_profile_idc] = 1;
	ptl->general_tier_flag = nal_hevc_tier_from_v4l2(tier);
	ptl->general_progressive_source_flag = 1;
	ptl->general_frame_only_स्थिरraपूर्णांक_flag = 1;
	ptl->general_level_idc = nal_hevc_level_from_v4l2(level);

	sps->seq_parameter_set_id = 0;
	sps->chroma_क्रमmat_idc = 1; /* Only 4:2:0 sampling supported */
	sps->pic_width_in_luma_samples = round_up(channel->width, 8);
	sps->pic_height_in_luma_samples = round_up(channel->height, 8);
	sps->conf_win_right_offset =
		sps->pic_width_in_luma_samples - channel->width;
	sps->conf_win_bottom_offset =
		sps->pic_height_in_luma_samples - channel->height;
	sps->conक्रमmance_winकरोw_flag =
		sps->conf_win_right_offset || sps->conf_win_bottom_offset;

	sps->log2_max_pic_order_cnt_lsb_minus4 = LOG2_MAX_PIC_ORDER_CNT - 4;

	sps->sub_layer_ordering_info_present_flag = 1;
	sps->max_dec_pic_buffering_minus1[0] = num_ref_frames;
	sps->max_num_reorder_pics[0] = num_ref_frames;

	sps->log2_min_luma_coding_block_size_minus3 =
		channel->min_cu_size - 3;
	sps->log2_dअगरf_max_min_luma_coding_block_size =
		channel->max_cu_size - channel->min_cu_size;
	sps->log2_min_luma_transक्रमm_block_size_minus2 =
		channel->min_tu_size - 2;
	sps->log2_dअगरf_max_min_luma_transक्रमm_block_size =
		channel->max_tu_size - channel->min_tu_size;
	sps->max_transक्रमm_hierarchy_depth_पूर्णांकra =
		channel->max_transfo_depth_पूर्णांकra;
	sps->max_transक्रमm_hierarchy_depth_पूर्णांकer =
		channel->max_transfo_depth_पूर्णांकer;

	sps->sps_temporal_mvp_enabled_flag = channel->temporal_mvp_enable;
	sps->strong_पूर्णांकra_smoothing_enabled_flag = channel->max_cu_size > 4;

	size = nal_hevc_ग_लिखो_sps(&dev->plat_dev->dev, dest, n, sps);

	kमुक्त(sps);

	वापस size;
पूर्ण

अटल sमाप_प्रकार allegro_hevc_ग_लिखो_pps(काष्ठा allegro_channel *channel,
				      काष्ठा mcu_msg_encode_frame_response *msg,
				      व्योम *dest, माप_प्रकार n)
अणु
	काष्ठा allegro_dev *dev = channel->dev;
	काष्ठा nal_hevc_pps *pps;
	sमाप_प्रकार size;
	पूर्णांक i;

	pps = kzalloc(माप(*pps), GFP_KERNEL);
	अगर (!pps)
		वापस -ENOMEM;

	pps->pps_pic_parameter_set_id = 0;
	pps->pps_seq_parameter_set_id = 0;

	अगर (msg->num_column > 1 || msg->num_row > 1) अणु
		pps->tiles_enabled_flag = 1;
		pps->num_tile_columns_minus1 = msg->num_column - 1;
		pps->num_tile_rows_minus1 = msg->num_row - 1;

		क्रम (i = 0; i < msg->num_column; i++)
			pps->column_width_minus1[i] = msg->tile_width[i] - 1;

		क्रम (i = 0; i < msg->num_row; i++)
			pps->row_height_minus1[i] = msg->tile_height[i] - 1;
	पूर्ण

	pps->loop_filter_across_tiles_enabled_flag =
		channel->enable_loop_filter_across_tiles;
	pps->pps_loop_filter_across_slices_enabled_flag =
		channel->enable_loop_filter_across_slices;
	pps->deblocking_filter_control_present_flag = 1;
	pps->deblocking_filter_override_enabled_flag =
		channel->enable_deblocking_filter_override;
	pps->pps_beta_offset_भाग2 = BETA_OFFSET_DIV_2;
	pps->pps_tc_offset_भाग2 = TC_OFFSET_DIV_2;

	pps->lists_modअगरication_present_flag = channel->enable_reordering;

	size = nal_hevc_ग_लिखो_pps(&dev->plat_dev->dev, dest, n, pps);

	kमुक्त(pps);

	वापस size;
पूर्ण

अटल u64 allegro_put_buffer(काष्ठा allegro_channel *channel,
			      काष्ठा list_head *list,
			      काष्ठा vb2_v4l2_buffer *buffer)
अणु
	काष्ठा v4l2_m2m_buffer *b = container_of(buffer,
						 काष्ठा v4l2_m2m_buffer, vb);
	काष्ठा allegro_m2m_buffer *shaकरोw = to_allegro_m2m_buffer(b);

	mutex_lock(&channel->shaकरोw_list_lock);
	list_add_tail(&shaकरोw->head, list);
	mutex_unlock(&channel->shaकरोw_list_lock);

	वापस ptr_to_u64(buffer);
पूर्ण

अटल काष्ठा vb2_v4l2_buffer *
allegro_get_buffer(काष्ठा allegro_channel *channel,
		   काष्ठा list_head *list, u64 handle)
अणु
	काष्ठा allegro_m2m_buffer *shaकरोw, *पंचांगp;
	काष्ठा vb2_v4l2_buffer *buffer = शून्य;

	mutex_lock(&channel->shaकरोw_list_lock);
	list_क्रम_each_entry_safe(shaकरोw, पंचांगp, list, head) अणु
		अगर (handle == ptr_to_u64(&shaकरोw->buf.vb)) अणु
			buffer = &shaकरोw->buf.vb;
			list_del_init(&shaकरोw->head);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&channel->shaकरोw_list_lock);

	वापस buffer;
पूर्ण

अटल व्योम allegro_channel_finish_frame(काष्ठा allegro_channel *channel,
		काष्ठा mcu_msg_encode_frame_response *msg)
अणु
	काष्ठा allegro_dev *dev = channel->dev;
	काष्ठा vb2_v4l2_buffer *src_buf;
	काष्ठा vb2_v4l2_buffer *dst_buf;
	काष्ठा अणु
		u32 offset;
		u32 size;
	पूर्ण *partition;
	क्रमागत vb2_buffer_state state = VB2_BUF_STATE_ERROR;
	अक्षर *curr;
	sमाप_प्रकार len;
	sमाप_प्रकार मुक्त;

	src_buf = allegro_get_buffer(channel, &channel->source_shaकरोw_list,
				     msg->src_handle);
	अगर (!src_buf)
		v4l2_warn(&dev->v4l2_dev,
			  "channel %d: invalid source buffer\n",
			  channel->mcu_channel_id);

	dst_buf = allegro_get_buffer(channel, &channel->stream_shaकरोw_list,
				     msg->dst_handle);
	अगर (!dst_buf)
		v4l2_warn(&dev->v4l2_dev,
			  "channel %d: invalid stream buffer\n",
			  channel->mcu_channel_id);

	अगर (!src_buf || !dst_buf)
		जाओ err;

	अगर (v4l2_m2m_is_last_draining_src_buf(channel->fh.m2m_ctx, src_buf)) अणु
		dst_buf->flags |= V4L2_BUF_FLAG_LAST;
		allegro_channel_eos_event(channel);
		v4l2_m2m_mark_stopped(channel->fh.m2m_ctx);
	पूर्ण

	dst_buf->sequence = channel->csequence++;

	अगर (msg->error_code & AL_ERROR) अणु
		v4l2_err(&dev->v4l2_dev,
			 "channel %d: failed to encode frame: %s (%x)\n",
			 channel->mcu_channel_id,
			 allegro_err_to_string(msg->error_code),
			 msg->error_code);
		जाओ err;
	पूर्ण

	अगर (msg->partition_table_size != 1) अणु
		v4l2_warn(&dev->v4l2_dev,
			  "channel %d: only handling first partition table entry (%d entries)\n",
			  channel->mcu_channel_id, msg->partition_table_size);
	पूर्ण

	अगर (msg->partition_table_offset +
	    msg->partition_table_size * माप(*partition) >
	    vb2_plane_size(&dst_buf->vb2_buf, 0)) अणु
		v4l2_err(&dev->v4l2_dev,
			 "channel %d: partition table outside of dst_buf\n",
			 channel->mcu_channel_id);
		जाओ err;
	पूर्ण

	partition =
	    vb2_plane_vaddr(&dst_buf->vb2_buf, 0) + msg->partition_table_offset;
	अगर (partition->offset + partition->size >
	    vb2_plane_size(&dst_buf->vb2_buf, 0)) अणु
		v4l2_err(&dev->v4l2_dev,
			 "channel %d: encoded frame is outside of dst_buf (offset 0x%x, size 0x%x)\n",
			 channel->mcu_channel_id, partition->offset,
			 partition->size);
		जाओ err;
	पूर्ण

	v4l2_dbg(2, debug, &dev->v4l2_dev,
		 "channel %d: encoded frame of size %d is at offset 0x%x\n",
		 channel->mcu_channel_id, partition->size, partition->offset);

	/*
	 * The payload must include the data beक्रमe the partition offset,
	 * because we will put the sps and pps data there.
	 */
	vb2_set_plane_payload(&dst_buf->vb2_buf, 0,
			      partition->offset + partition->size);

	curr = vb2_plane_vaddr(&dst_buf->vb2_buf, 0);
	मुक्त = partition->offset;

	अगर (channel->codec == V4L2_PIX_FMT_HEVC && msg->is_idr) अणु
		len = allegro_hevc_ग_लिखो_vps(channel, curr, मुक्त);
		अगर (len < 0) अणु
			v4l2_err(&dev->v4l2_dev,
				 "not enough space for video parameter set: %zd left\n",
				 मुक्त);
			जाओ err;
		पूर्ण
		curr += len;
		मुक्त -= len;
		v4l2_dbg(1, debug, &dev->v4l2_dev,
			 "channel %d: wrote %zd byte VPS nal unit\n",
			 channel->mcu_channel_id, len);
	पूर्ण

	अगर (msg->is_idr) अणु
		अगर (channel->codec == V4L2_PIX_FMT_H264)
			len = allegro_h264_ग_लिखो_sps(channel, curr, मुक्त);
		अन्यथा
			len = allegro_hevc_ग_लिखो_sps(channel, curr, मुक्त);
		अगर (len < 0) अणु
			v4l2_err(&dev->v4l2_dev,
				 "not enough space for sequence parameter set: %zd left\n",
				 मुक्त);
			जाओ err;
		पूर्ण
		curr += len;
		मुक्त -= len;
		v4l2_dbg(1, debug, &dev->v4l2_dev,
			 "channel %d: wrote %zd byte SPS nal unit\n",
			 channel->mcu_channel_id, len);
	पूर्ण

	अगर (msg->slice_type == AL_ENC_SLICE_TYPE_I) अणु
		अगर (channel->codec == V4L2_PIX_FMT_H264)
			len = allegro_h264_ग_लिखो_pps(channel, curr, मुक्त);
		अन्यथा
			len = allegro_hevc_ग_लिखो_pps(channel, msg, curr, मुक्त);
		अगर (len < 0) अणु
			v4l2_err(&dev->v4l2_dev,
				 "not enough space for picture parameter set: %zd left\n",
				 मुक्त);
			जाओ err;
		पूर्ण
		curr += len;
		मुक्त -= len;
		v4l2_dbg(1, debug, &dev->v4l2_dev,
			 "channel %d: wrote %zd byte PPS nal unit\n",
			 channel->mcu_channel_id, len);
	पूर्ण

	अगर (msg->slice_type != AL_ENC_SLICE_TYPE_I && !msg->is_idr) अणु
		dst_buf->vb2_buf.planes[0].data_offset = मुक्त;
		मुक्त = 0;
	पूर्ण अन्यथा अणु
		अगर (channel->codec == V4L2_PIX_FMT_H264)
			len = nal_h264_ग_लिखो_filler(&dev->plat_dev->dev, curr, मुक्त);
		अन्यथा
			len = nal_hevc_ग_लिखो_filler(&dev->plat_dev->dev, curr, मुक्त);
		अगर (len < 0) अणु
			v4l2_err(&dev->v4l2_dev,
				 "failed to write %zd filler data\n", मुक्त);
			जाओ err;
		पूर्ण
		curr += len;
		मुक्त -= len;
		v4l2_dbg(2, debug, &dev->v4l2_dev,
			 "channel %d: wrote %zd bytes filler nal unit\n",
			 channel->mcu_channel_id, len);
	पूर्ण

	अगर (मुक्त != 0) अणु
		v4l2_err(&dev->v4l2_dev,
			 "non-VCL NAL units do not fill space until VCL NAL unit: %zd bytes left\n",
			 मुक्त);
		जाओ err;
	पूर्ण

	state = VB2_BUF_STATE_DONE;

	v4l2_m2m_buf_copy_metadata(src_buf, dst_buf, false);
	अगर (msg->is_idr)
		dst_buf->flags |= V4L2_BUF_FLAG_KEYFRAME;
	अन्यथा
		dst_buf->flags |= V4L2_BUF_FLAG_PFRAME;

	v4l2_dbg(1, debug, &dev->v4l2_dev,
		 "channel %d: encoded frame #%03d (%s%s, QP %d, %d bytes)\n",
		 channel->mcu_channel_id,
		 dst_buf->sequence,
		 msg->is_idr ? "IDR, " : "",
		 msg->slice_type == AL_ENC_SLICE_TYPE_I ? "I slice" :
		 msg->slice_type == AL_ENC_SLICE_TYPE_P ? "P slice" : "unknown",
		 msg->qp, partition->size);

err:
	अगर (src_buf)
		v4l2_m2m_buf_करोne(src_buf, VB2_BUF_STATE_DONE);

	अगर (dst_buf)
		v4l2_m2m_buf_करोne(dst_buf, state);
पूर्ण

अटल पूर्णांक allegro_handle_init(काष्ठा allegro_dev *dev,
			       काष्ठा mcu_msg_init_response *msg)
अणु
	complete(&dev->init_complete);

	वापस 0;
पूर्ण

अटल पूर्णांक
allegro_handle_create_channel(काष्ठा allegro_dev *dev,
			      काष्ठा mcu_msg_create_channel_response *msg)
अणु
	काष्ठा allegro_channel *channel;
	पूर्णांक err = 0;
	काष्ठा create_channel_param param;

	channel = allegro_find_channel_by_user_id(dev, msg->user_id);
	अगर (IS_ERR(channel)) अणु
		v4l2_warn(&dev->v4l2_dev,
			  "received %s for unknown user %d\n",
			  msg_type_name(msg->header.type),
			  msg->user_id);
		वापस -EINVAL;
	पूर्ण

	अगर (msg->error_code) अणु
		v4l2_err(&dev->v4l2_dev,
			 "user %d: mcu failed to create channel: %s (%x)\n",
			 channel->user_id,
			 allegro_err_to_string(msg->error_code),
			 msg->error_code);
		err = -EIO;
		जाओ out;
	पूर्ण

	channel->mcu_channel_id = msg->channel_id;
	v4l2_dbg(1, debug, &dev->v4l2_dev,
		 "user %d: channel has channel id %d\n",
		 channel->user_id, channel->mcu_channel_id);

	err = allegro_decode_config_blob(&param, msg, channel->config_blob.vaddr);
	allegro_मुक्त_buffer(channel->dev, &channel->config_blob);
	अगर (err)
		जाओ out;

	channel->num_ref_idx_l0 = param.num_ref_idx_l0;
	channel->num_ref_idx_l1 = param.num_ref_idx_l1;

	v4l2_dbg(1, debug, &dev->v4l2_dev,
		 "channel %d: intermediate buffers: %d x %d bytes\n",
		 channel->mcu_channel_id,
		 msg->पूर्णांक_buffers_count, msg->पूर्णांक_buffers_size);
	err = allocate_पूर्णांकermediate_buffers(channel, msg->पूर्णांक_buffers_count,
					    msg->पूर्णांक_buffers_size);
	अगर (err) अणु
		v4l2_err(&dev->v4l2_dev,
			 "channel %d: failed to allocate intermediate buffers\n",
			 channel->mcu_channel_id);
		जाओ out;
	पूर्ण
	err = allegro_mcu_push_buffer_पूर्णांकermediate(channel);
	अगर (err)
		जाओ out;

	v4l2_dbg(1, debug, &dev->v4l2_dev,
		 "channel %d: reference buffers: %d x %d bytes\n",
		 channel->mcu_channel_id,
		 msg->rec_buffers_count, msg->rec_buffers_size);
	err = allocate_reference_buffers(channel, msg->rec_buffers_count,
					 msg->rec_buffers_size);
	अगर (err) अणु
		v4l2_err(&dev->v4l2_dev,
			 "channel %d: failed to allocate reference buffers\n",
			 channel->mcu_channel_id);
		जाओ out;
	पूर्ण
	err = allegro_mcu_push_buffer_reference(channel);
	अगर (err)
		जाओ out;

out:
	channel->error = err;
	complete(&channel->completion);

	/* Handled successfully, error is passed via channel->error */
	वापस 0;
पूर्ण

अटल पूर्णांक
allegro_handle_destroy_channel(काष्ठा allegro_dev *dev,
			       काष्ठा mcu_msg_destroy_channel_response *msg)
अणु
	काष्ठा allegro_channel *channel;

	channel = allegro_find_channel_by_channel_id(dev, msg->channel_id);
	अगर (IS_ERR(channel)) अणु
		v4l2_err(&dev->v4l2_dev,
			 "received %s for unknown channel %d\n",
			 msg_type_name(msg->header.type),
			 msg->channel_id);
		वापस -EINVAL;
	पूर्ण

	v4l2_dbg(2, debug, &dev->v4l2_dev,
		 "user %d: vcu destroyed channel %d\n",
		 channel->user_id, channel->mcu_channel_id);
	complete(&channel->completion);

	वापस 0;
पूर्ण

अटल पूर्णांक
allegro_handle_encode_frame(काष्ठा allegro_dev *dev,
			    काष्ठा mcu_msg_encode_frame_response *msg)
अणु
	काष्ठा allegro_channel *channel;

	channel = allegro_find_channel_by_channel_id(dev, msg->channel_id);
	अगर (IS_ERR(channel)) अणु
		v4l2_err(&dev->v4l2_dev,
			 "received %s for unknown channel %d\n",
			 msg_type_name(msg->header.type),
			 msg->channel_id);
		वापस -EINVAL;
	पूर्ण

	allegro_channel_finish_frame(channel, msg);

	वापस 0;
पूर्ण

अटल व्योम allegro_handle_message(काष्ठा allegro_dev *dev,
				   जोड़ mcu_msg_response *msg)
अणु
	चयन (msg->header.type) अणु
	हाल MCU_MSG_TYPE_INIT:
		allegro_handle_init(dev, &msg->init);
		अवरोध;
	हाल MCU_MSG_TYPE_CREATE_CHANNEL:
		allegro_handle_create_channel(dev, &msg->create_channel);
		अवरोध;
	हाल MCU_MSG_TYPE_DESTROY_CHANNEL:
		allegro_handle_destroy_channel(dev, &msg->destroy_channel);
		अवरोध;
	हाल MCU_MSG_TYPE_ENCODE_FRAME:
		allegro_handle_encode_frame(dev, &msg->encode_frame);
		अवरोध;
	शेष:
		v4l2_warn(&dev->v4l2_dev,
			  "%s: unknown message %s\n",
			  __func__, msg_type_name(msg->header.type));
		अवरोध;
	पूर्ण
पूर्ण

अटल irqवापस_t allegro_hardirq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा allegro_dev *dev = data;
	अचिन्हित पूर्णांक status;

	regmap_पढ़ो(dev->regmap, AL5_ITC_CPU_IRQ_STA, &status);
	अगर (!(status & AL5_ITC_CPU_IRQ_STA_TRIGGERED))
		वापस IRQ_NONE;

	regmap_ग_लिखो(dev->regmap, AL5_ITC_CPU_IRQ_CLR, status);

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t allegro_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा allegro_dev *dev = data;

	allegro_mbox_notअगरy(dev->mbox_status);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम allegro_copy_firmware(काष्ठा allegro_dev *dev,
				  स्थिर u8 * स्थिर buf, माप_प्रकार size)
अणु
	पूर्णांक err = 0;

	v4l2_dbg(1, debug, &dev->v4l2_dev,
		 "copy mcu firmware (%zu B) to SRAM\n", size);
	err = regmap_bulk_ग_लिखो(dev->sram, 0x0, buf, size / 4);
	अगर (err)
		v4l2_err(&dev->v4l2_dev,
			 "failed to copy firmware: %d\n", err);
पूर्ण

अटल व्योम allegro_copy_fw_codec(काष्ठा allegro_dev *dev,
				  स्थिर u8 * स्थिर buf, माप_प्रकार size)
अणु
	पूर्णांक err;
	dma_addr_t icache_offset, dcache_offset;

	/*
	 * The करोwnstream allocates 600 KB क्रम the codec firmware to have some
	 * extra space क्रम "possible extensions." My tests were fine with
	 * allocating just enough memory क्रम the actual firmware, but I am not
	 * sure that the firmware really करोes not use the reमुख्यing space.
	 */
	err = allegro_alloc_buffer(dev, &dev->firmware, size);
	अगर (err) अणु
		v4l2_err(&dev->v4l2_dev,
			 "failed to allocate %zu bytes for firmware\n", size);
		वापस;
	पूर्ण

	v4l2_dbg(1, debug, &dev->v4l2_dev,
		 "copy codec firmware (%zd B) to phys %pad\n",
		 size, &dev->firmware.paddr);
	स_नकल(dev->firmware.vaddr, buf, size);

	regmap_ग_लिखो(dev->regmap, AXI_ADDR_OFFSET_IP,
		     upper_32_bits(dev->firmware.paddr));

	icache_offset = dev->firmware.paddr - MCU_CACHE_OFFSET;
	v4l2_dbg(2, debug, &dev->v4l2_dev,
		 "icache_offset: msb = 0x%x, lsb = 0x%x\n",
		 upper_32_bits(icache_offset), lower_32_bits(icache_offset));
	regmap_ग_लिखो(dev->regmap, AL5_ICACHE_ADDR_OFFSET_MSB,
		     upper_32_bits(icache_offset));
	regmap_ग_लिखो(dev->regmap, AL5_ICACHE_ADDR_OFFSET_LSB,
		     lower_32_bits(icache_offset));

	dcache_offset =
	    (dev->firmware.paddr & 0xffffffff00000000ULL) - MCU_CACHE_OFFSET;
	v4l2_dbg(2, debug, &dev->v4l2_dev,
		 "dcache_offset: msb = 0x%x, lsb = 0x%x\n",
		 upper_32_bits(dcache_offset), lower_32_bits(dcache_offset));
	regmap_ग_लिखो(dev->regmap, AL5_DCACHE_ADDR_OFFSET_MSB,
		     upper_32_bits(dcache_offset));
	regmap_ग_लिखो(dev->regmap, AL5_DCACHE_ADDR_OFFSET_LSB,
		     lower_32_bits(dcache_offset));
पूर्ण

अटल व्योम allegro_मुक्त_fw_codec(काष्ठा allegro_dev *dev)
अणु
	allegro_मुक्त_buffer(dev, &dev->firmware);
पूर्ण

/*
 * Control functions क्रम the MCU
 */

अटल पूर्णांक allegro_mcu_enable_पूर्णांकerrupts(काष्ठा allegro_dev *dev)
अणु
	वापस regmap_ग_लिखो(dev->regmap, AL5_ITC_CPU_IRQ_MSK, BIT(0));
पूर्ण

अटल पूर्णांक allegro_mcu_disable_पूर्णांकerrupts(काष्ठा allegro_dev *dev)
अणु
	वापस regmap_ग_लिखो(dev->regmap, AL5_ITC_CPU_IRQ_MSK, 0);
पूर्ण

अटल पूर्णांक allegro_mcu_रुको_क्रम_sleep(काष्ठा allegro_dev *dev)
अणु
	अचिन्हित दीर्घ समयout;
	अचिन्हित पूर्णांक status;

	समयout = jअगरfies + msecs_to_jअगरfies(100);
	जबतक (regmap_पढ़ो(dev->regmap, AL5_MCU_STA, &status) == 0 &&
	       status != AL5_MCU_STA_SLEEP) अणु
		अगर (समय_after(jअगरfies, समयout))
			वापस -ETIMEDOUT;
		cpu_relax();
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक allegro_mcu_start(काष्ठा allegro_dev *dev)
अणु
	अचिन्हित दीर्घ समयout;
	अचिन्हित पूर्णांक status;
	पूर्णांक err;

	err = regmap_ग_लिखो(dev->regmap, AL5_MCU_WAKEUP, BIT(0));
	अगर (err)
		वापस err;

	समयout = jअगरfies + msecs_to_jअगरfies(100);
	जबतक (regmap_पढ़ो(dev->regmap, AL5_MCU_STA, &status) == 0 &&
	       status == AL5_MCU_STA_SLEEP) अणु
		अगर (समय_after(jअगरfies, समयout))
			वापस -ETIMEDOUT;
		cpu_relax();
	पूर्ण

	err = regmap_ग_लिखो(dev->regmap, AL5_MCU_WAKEUP, 0);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक allegro_mcu_reset(काष्ठा allegro_dev *dev)
अणु
	पूर्णांक err;

	/*
	 * Ensure that the AL5_MCU_WAKEUP bit is set to 0 otherwise the mcu
	 * करोes not go to sleep after the reset.
	 */
	err = regmap_ग_लिखो(dev->regmap, AL5_MCU_WAKEUP, 0);
	अगर (err)
		वापस err;

	err = regmap_ग_लिखो(dev->regmap,
			   AL5_MCU_RESET_MODE, AL5_MCU_RESET_MODE_SLEEP);
	अगर (err < 0)
		वापस err;

	err = regmap_ग_लिखो(dev->regmap, AL5_MCU_RESET, AL5_MCU_RESET_SOFT);
	अगर (err < 0)
		वापस err;

	वापस allegro_mcu_रुको_क्रम_sleep(dev);
पूर्ण

अटल व्योम allegro_mcu_पूर्णांकerrupt(काष्ठा allegro_dev *dev)
अणु
	regmap_ग_लिखो(dev->regmap, AL5_MCU_INTERRUPT, BIT(0));
पूर्ण

अटल व्योम allegro_destroy_channel(काष्ठा allegro_channel *channel)
अणु
	काष्ठा allegro_dev *dev = channel->dev;
	अचिन्हित दीर्घ समयout;

	अगर (channel_exists(channel)) अणु
		reinit_completion(&channel->completion);
		allegro_mcu_send_destroy_channel(dev, channel);
		समयout = रुको_क्रम_completion_समयout(&channel->completion,
						      msecs_to_jअगरfies(5000));
		अगर (समयout == 0)
			v4l2_warn(&dev->v4l2_dev,
				  "channel %d: timeout while destroying\n",
				  channel->mcu_channel_id);

		channel->mcu_channel_id = -1;
	पूर्ण

	destroy_पूर्णांकermediate_buffers(channel);
	destroy_reference_buffers(channel);

	v4l2_ctrl_grab(channel->mpeg_video_h264_profile, false);
	v4l2_ctrl_grab(channel->mpeg_video_h264_level, false);
	v4l2_ctrl_grab(channel->mpeg_video_h264_i_frame_qp, false);
	v4l2_ctrl_grab(channel->mpeg_video_h264_max_qp, false);
	v4l2_ctrl_grab(channel->mpeg_video_h264_min_qp, false);
	v4l2_ctrl_grab(channel->mpeg_video_h264_p_frame_qp, false);
	v4l2_ctrl_grab(channel->mpeg_video_h264_b_frame_qp, false);

	v4l2_ctrl_grab(channel->mpeg_video_hevc_profile, false);
	v4l2_ctrl_grab(channel->mpeg_video_hevc_level, false);
	v4l2_ctrl_grab(channel->mpeg_video_hevc_tier, false);
	v4l2_ctrl_grab(channel->mpeg_video_hevc_i_frame_qp, false);
	v4l2_ctrl_grab(channel->mpeg_video_hevc_max_qp, false);
	v4l2_ctrl_grab(channel->mpeg_video_hevc_min_qp, false);
	v4l2_ctrl_grab(channel->mpeg_video_hevc_p_frame_qp, false);
	v4l2_ctrl_grab(channel->mpeg_video_hevc_b_frame_qp, false);

	v4l2_ctrl_grab(channel->mpeg_video_frame_rc_enable, false);
	v4l2_ctrl_grab(channel->mpeg_video_bitrate_mode, false);
	v4l2_ctrl_grab(channel->mpeg_video_bitrate, false);
	v4l2_ctrl_grab(channel->mpeg_video_bitrate_peak, false);
	v4l2_ctrl_grab(channel->mpeg_video_cpb_size, false);
	v4l2_ctrl_grab(channel->mpeg_video_gop_size, false);

	अगर (channel->user_id != -1) अणु
		clear_bit(channel->user_id, &dev->channel_user_ids);
		channel->user_id = -1;
	पूर्ण
पूर्ण

/*
 * Create the MCU channel
 *
 * After the channel has been created, the picture size, क्रमmat, colorspace
 * and framerate are fixed. Also the codec, profile, bitrate, etc. cannot be
 * changed anymore.
 *
 * The channel can be created only once. The MCU will accept source buffers
 * and stream buffers only after a channel has been created.
 */
अटल पूर्णांक allegro_create_channel(काष्ठा allegro_channel *channel)
अणु
	काष्ठा allegro_dev *dev = channel->dev;
	अचिन्हित दीर्घ समयout;

	अगर (channel_exists(channel)) अणु
		v4l2_warn(&dev->v4l2_dev,
			  "channel already exists\n");
		वापस 0;
	पूर्ण

	channel->user_id = allegro_next_user_id(dev);
	अगर (channel->user_id < 0) अणु
		v4l2_err(&dev->v4l2_dev,
			 "no free channels available\n");
		वापस -EBUSY;
	पूर्ण
	set_bit(channel->user_id, &dev->channel_user_ids);

	v4l2_dbg(1, debug, &dev->v4l2_dev,
		 "user %d: creating channel (%4.4s, %dx%d@%d)\n",
		 channel->user_id,
		 (अक्षर *)&channel->codec, channel->width, channel->height,
		 DIV_ROUND_UP(channel->framerate.numerator,
			      channel->framerate.denominator));

	v4l2_ctrl_grab(channel->mpeg_video_h264_profile, true);
	v4l2_ctrl_grab(channel->mpeg_video_h264_level, true);
	v4l2_ctrl_grab(channel->mpeg_video_h264_i_frame_qp, true);
	v4l2_ctrl_grab(channel->mpeg_video_h264_max_qp, true);
	v4l2_ctrl_grab(channel->mpeg_video_h264_min_qp, true);
	v4l2_ctrl_grab(channel->mpeg_video_h264_p_frame_qp, true);
	v4l2_ctrl_grab(channel->mpeg_video_h264_b_frame_qp, true);

	v4l2_ctrl_grab(channel->mpeg_video_hevc_profile, true);
	v4l2_ctrl_grab(channel->mpeg_video_hevc_level, true);
	v4l2_ctrl_grab(channel->mpeg_video_hevc_tier, true);
	v4l2_ctrl_grab(channel->mpeg_video_hevc_i_frame_qp, true);
	v4l2_ctrl_grab(channel->mpeg_video_hevc_max_qp, true);
	v4l2_ctrl_grab(channel->mpeg_video_hevc_min_qp, true);
	v4l2_ctrl_grab(channel->mpeg_video_hevc_p_frame_qp, true);
	v4l2_ctrl_grab(channel->mpeg_video_hevc_b_frame_qp, true);

	v4l2_ctrl_grab(channel->mpeg_video_frame_rc_enable, true);
	v4l2_ctrl_grab(channel->mpeg_video_bitrate_mode, true);
	v4l2_ctrl_grab(channel->mpeg_video_bitrate, true);
	v4l2_ctrl_grab(channel->mpeg_video_bitrate_peak, true);
	v4l2_ctrl_grab(channel->mpeg_video_cpb_size, true);
	v4l2_ctrl_grab(channel->mpeg_video_gop_size, true);

	reinit_completion(&channel->completion);
	allegro_mcu_send_create_channel(dev, channel);
	समयout = रुको_क्रम_completion_समयout(&channel->completion,
					      msecs_to_jअगरfies(5000));
	अगर (समयout == 0)
		channel->error = -ETIMEDOUT;
	अगर (channel->error)
		जाओ err;

	v4l2_dbg(1, debug, &dev->v4l2_dev,
		 "channel %d: accepting buffers\n",
		 channel->mcu_channel_id);

	वापस 0;

err:
	allegro_destroy_channel(channel);

	वापस channel->error;
पूर्ण

/**
 * allegro_channel_adjust() - Adjust channel parameters to current क्रमmat
 * @channel: the channel to adjust
 *
 * Various parameters of a channel and their limits depend on the currently
 * set क्रमmat. Adjust the parameters after a क्रमmat change in one go.
 */
अटल व्योम allegro_channel_adjust(काष्ठा allegro_channel *channel)
अणु
	काष्ठा allegro_dev *dev = channel->dev;
	u32 codec = channel->codec;
	काष्ठा v4l2_ctrl *ctrl;
	s64 min;
	s64 max;

	channel->sizeimage_encoded =
		estimate_stream_size(channel->width, channel->height);

	अगर (codec == V4L2_PIX_FMT_H264) अणु
		ctrl = channel->mpeg_video_h264_level;
		min = select_minimum_h264_level(channel->width, channel->height);
	पूर्ण अन्यथा अणु
		ctrl = channel->mpeg_video_hevc_level;
		min = select_minimum_hevc_level(channel->width, channel->height);
	पूर्ण
	अगर (ctrl->minimum > min)
		v4l2_dbg(1, debug, &dev->v4l2_dev,
			 "%s.minimum: %lld -> %lld\n",
			 v4l2_ctrl_get_name(ctrl->id), ctrl->minimum, min);
	v4l2_ctrl_lock(ctrl);
	__v4l2_ctrl_modअगरy_range(ctrl, min, ctrl->maximum,
				 ctrl->step, ctrl->शेष_value);
	v4l2_ctrl_unlock(ctrl);

	ctrl = channel->mpeg_video_bitrate;
	अगर (codec == V4L2_PIX_FMT_H264)
		max = h264_maximum_bitrate(v4l2_ctrl_g_ctrl(channel->mpeg_video_h264_level));
	अन्यथा
		max = hevc_maximum_bitrate(v4l2_ctrl_g_ctrl(channel->mpeg_video_hevc_level));
	अगर (ctrl->maximum < max)
		v4l2_dbg(1, debug, &dev->v4l2_dev,
			 "%s: maximum: %lld -> %lld\n",
			 v4l2_ctrl_get_name(ctrl->id), ctrl->maximum, max);
	v4l2_ctrl_lock(ctrl);
	__v4l2_ctrl_modअगरy_range(ctrl, ctrl->minimum, max,
				 ctrl->step, ctrl->शेष_value);
	v4l2_ctrl_unlock(ctrl);

	ctrl = channel->mpeg_video_bitrate_peak;
	v4l2_ctrl_lock(ctrl);
	__v4l2_ctrl_modअगरy_range(ctrl, ctrl->minimum, max,
				 ctrl->step, ctrl->शेष_value);
	v4l2_ctrl_unlock(ctrl);

	v4l2_ctrl_activate(channel->mpeg_video_h264_profile,
			   codec == V4L2_PIX_FMT_H264);
	v4l2_ctrl_activate(channel->mpeg_video_h264_level,
			   codec == V4L2_PIX_FMT_H264);
	v4l2_ctrl_activate(channel->mpeg_video_h264_i_frame_qp,
			   codec == V4L2_PIX_FMT_H264);
	v4l2_ctrl_activate(channel->mpeg_video_h264_max_qp,
			   codec == V4L2_PIX_FMT_H264);
	v4l2_ctrl_activate(channel->mpeg_video_h264_min_qp,
			   codec == V4L2_PIX_FMT_H264);
	v4l2_ctrl_activate(channel->mpeg_video_h264_p_frame_qp,
			   codec == V4L2_PIX_FMT_H264);
	v4l2_ctrl_activate(channel->mpeg_video_h264_b_frame_qp,
			   codec == V4L2_PIX_FMT_H264);

	v4l2_ctrl_activate(channel->mpeg_video_hevc_profile,
			   codec == V4L2_PIX_FMT_HEVC);
	v4l2_ctrl_activate(channel->mpeg_video_hevc_level,
			   codec == V4L2_PIX_FMT_HEVC);
	v4l2_ctrl_activate(channel->mpeg_video_hevc_tier,
			   codec == V4L2_PIX_FMT_HEVC);
	v4l2_ctrl_activate(channel->mpeg_video_hevc_i_frame_qp,
			   codec == V4L2_PIX_FMT_HEVC);
	v4l2_ctrl_activate(channel->mpeg_video_hevc_max_qp,
			   codec == V4L2_PIX_FMT_HEVC);
	v4l2_ctrl_activate(channel->mpeg_video_hevc_min_qp,
			   codec == V4L2_PIX_FMT_HEVC);
	v4l2_ctrl_activate(channel->mpeg_video_hevc_p_frame_qp,
			   codec == V4L2_PIX_FMT_HEVC);
	v4l2_ctrl_activate(channel->mpeg_video_hevc_b_frame_qp,
			   codec == V4L2_PIX_FMT_HEVC);

	अगर (codec == V4L2_PIX_FMT_H264)
		channel->log2_max_frame_num = LOG2_MAX_FRAME_NUM;
	channel->temporal_mvp_enable = true;
	channel->dbf_ovr_en = (codec == V4L2_PIX_FMT_H264);
	channel->enable_deblocking_filter_override = (codec == V4L2_PIX_FMT_HEVC);
	channel->enable_reordering = (codec == V4L2_PIX_FMT_HEVC);
	channel->enable_loop_filter_across_tiles = true;
	channel->enable_loop_filter_across_slices = true;

	अगर (codec == V4L2_PIX_FMT_H264) अणु
		channel->b_hrz_me_range = 8;
		channel->b_vrt_me_range = 8;
		channel->p_hrz_me_range = 16;
		channel->p_vrt_me_range = 16;
		channel->max_cu_size = ilog2(16);
		channel->min_cu_size = ilog2(8);
		channel->max_tu_size = ilog2(4);
		channel->min_tu_size = ilog2(4);
	पूर्ण अन्यथा अणु
		channel->b_hrz_me_range = 16;
		channel->b_vrt_me_range = 16;
		channel->p_hrz_me_range = 32;
		channel->p_vrt_me_range = 32;
		channel->max_cu_size = ilog2(32);
		channel->min_cu_size = ilog2(8);
		channel->max_tu_size = ilog2(32);
		channel->min_tu_size = ilog2(4);
	पूर्ण
	channel->max_transfo_depth_पूर्णांकra = 1;
	channel->max_transfo_depth_पूर्णांकer = 1;
पूर्ण

अटल व्योम allegro_set_शेष_params(काष्ठा allegro_channel *channel)
अणु
	channel->width = ALLEGRO_WIDTH_DEFAULT;
	channel->height = ALLEGRO_HEIGHT_DEFAULT;
	channel->stride = round_up(channel->width, 32);
	channel->framerate = ALLEGRO_FRAMERATE_DEFAULT;

	channel->colorspace = V4L2_COLORSPACE_REC709;
	channel->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
	channel->quantization = V4L2_QUANTIZATION_DEFAULT;
	channel->xfer_func = V4L2_XFER_FUNC_DEFAULT;

	channel->pixelक्रमmat = V4L2_PIX_FMT_NV12;
	channel->sizeimage_raw = channel->stride * channel->height * 3 / 2;

	channel->codec = V4L2_PIX_FMT_H264;
पूर्ण

अटल पूर्णांक allegro_queue_setup(काष्ठा vb2_queue *vq,
			       अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
			       अचिन्हित पूर्णांक sizes[],
			       काष्ठा device *alloc_devs[])
अणु
	काष्ठा allegro_channel *channel = vb2_get_drv_priv(vq);
	काष्ठा allegro_dev *dev = channel->dev;

	v4l2_dbg(2, debug, &dev->v4l2_dev,
		 "%s: queue setup[%s]: nplanes = %d\n",
		 V4L2_TYPE_IS_OUTPUT(vq->type) ? "output" : "capture",
		 *nplanes == 0 ? "REQBUFS" : "CREATE_BUFS", *nplanes);

	अगर (*nplanes != 0) अणु
		अगर (V4L2_TYPE_IS_OUTPUT(vq->type)) अणु
			अगर (sizes[0] < channel->sizeimage_raw)
				वापस -EINVAL;
		पूर्ण अन्यथा अणु
			अगर (sizes[0] < channel->sizeimage_encoded)
				वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		*nplanes = 1;
		अगर (V4L2_TYPE_IS_OUTPUT(vq->type))
			sizes[0] = channel->sizeimage_raw;
		अन्यथा
			sizes[0] = channel->sizeimage_encoded;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक allegro_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा allegro_channel *channel = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा allegro_dev *dev = channel->dev;

	अगर (V4L2_TYPE_IS_OUTPUT(vb->vb2_queue->type)) अणु
		अगर (vbuf->field == V4L2_FIELD_ANY)
			vbuf->field = V4L2_FIELD_NONE;
		अगर (vbuf->field != V4L2_FIELD_NONE) अणु
			v4l2_err(&dev->v4l2_dev,
				 "channel %d: unsupported field\n",
				 channel->mcu_channel_id);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम allegro_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा allegro_channel *channel = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vb2_queue *q = vb->vb2_queue;

	अगर (V4L2_TYPE_IS_CAPTURE(q->type) &&
	    vb2_is_streaming(q) &&
	    v4l2_m2m_dst_buf_is_last(channel->fh.m2m_ctx)) अणु
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < vb->num_planes; i++)
			vb->planes[i].bytesused = 0;

		vbuf->field = V4L2_FIELD_NONE;
		vbuf->sequence = channel->csequence++;

		v4l2_m2m_last_buffer_करोne(channel->fh.m2m_ctx, vbuf);
		allegro_channel_eos_event(channel);
		वापस;
	पूर्ण

	v4l2_m2m_buf_queue(channel->fh.m2m_ctx, vbuf);
पूर्ण

अटल पूर्णांक allegro_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा allegro_channel *channel = vb2_get_drv_priv(q);
	काष्ठा allegro_dev *dev = channel->dev;

	v4l2_dbg(2, debug, &dev->v4l2_dev,
		 "%s: start streaming\n",
		 V4L2_TYPE_IS_OUTPUT(q->type) ? "output" : "capture");

	v4l2_m2m_update_start_streaming_state(channel->fh.m2m_ctx, q);

	अगर (V4L2_TYPE_IS_OUTPUT(q->type))
		channel->osequence = 0;
	अन्यथा
		channel->csequence = 0;

	वापस 0;
पूर्ण

अटल व्योम allegro_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा allegro_channel *channel = vb2_get_drv_priv(q);
	काष्ठा allegro_dev *dev = channel->dev;
	काष्ठा vb2_v4l2_buffer *buffer;
	काष्ठा allegro_m2m_buffer *shaकरोw, *पंचांगp;

	v4l2_dbg(2, debug, &dev->v4l2_dev,
		 "%s: stop streaming\n",
		 V4L2_TYPE_IS_OUTPUT(q->type) ? "output" : "capture");

	अगर (V4L2_TYPE_IS_OUTPUT(q->type)) अणु
		mutex_lock(&channel->shaकरोw_list_lock);
		list_क्रम_each_entry_safe(shaकरोw, पंचांगp,
					 &channel->source_shaकरोw_list, head) अणु
			list_del(&shaकरोw->head);
			v4l2_m2m_buf_करोne(&shaकरोw->buf.vb, VB2_BUF_STATE_ERROR);
		पूर्ण
		mutex_unlock(&channel->shaकरोw_list_lock);

		जबतक ((buffer = v4l2_m2m_src_buf_हटाओ(channel->fh.m2m_ctx)))
			v4l2_m2m_buf_करोne(buffer, VB2_BUF_STATE_ERROR);
	पूर्ण अन्यथा अणु
		mutex_lock(&channel->shaकरोw_list_lock);
		list_क्रम_each_entry_safe(shaकरोw, पंचांगp,
					 &channel->stream_shaकरोw_list, head) अणु
			list_del(&shaकरोw->head);
			v4l2_m2m_buf_करोne(&shaकरोw->buf.vb, VB2_BUF_STATE_ERROR);
		पूर्ण
		mutex_unlock(&channel->shaकरोw_list_lock);

		allegro_destroy_channel(channel);
		जबतक ((buffer = v4l2_m2m_dst_buf_हटाओ(channel->fh.m2m_ctx)))
			v4l2_m2m_buf_करोne(buffer, VB2_BUF_STATE_ERROR);
	पूर्ण

	v4l2_m2m_update_stop_streaming_state(channel->fh.m2m_ctx, q);

	अगर (V4L2_TYPE_IS_OUTPUT(q->type) &&
	    v4l2_m2m_has_stopped(channel->fh.m2m_ctx))
		allegro_channel_eos_event(channel);
पूर्ण

अटल स्थिर काष्ठा vb2_ops allegro_queue_ops = अणु
	.queue_setup = allegro_queue_setup,
	.buf_prepare = allegro_buf_prepare,
	.buf_queue = allegro_buf_queue,
	.start_streaming = allegro_start_streaming,
	.stop_streaming = allegro_stop_streaming,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
पूर्ण;

अटल पूर्णांक allegro_queue_init(व्योम *priv,
			      काष्ठा vb2_queue *src_vq,
			      काष्ठा vb2_queue *dst_vq)
अणु
	पूर्णांक err;
	काष्ठा allegro_channel *channel = priv;

	src_vq->dev = &channel->dev->plat_dev->dev;
	src_vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	src_vq->io_modes = VB2_DMABUF | VB2_MMAP;
	src_vq->mem_ops = &vb2_dma_contig_memops;
	src_vq->drv_priv = channel;
	src_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	src_vq->ops = &allegro_queue_ops;
	src_vq->buf_काष्ठा_size = माप(काष्ठा allegro_m2m_buffer);
	src_vq->lock = &channel->dev->lock;
	err = vb2_queue_init(src_vq);
	अगर (err)
		वापस err;

	dst_vq->dev = &channel->dev->plat_dev->dev;
	dst_vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	dst_vq->io_modes = VB2_DMABUF | VB2_MMAP;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->drv_priv = channel;
	dst_vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	dst_vq->ops = &allegro_queue_ops;
	dst_vq->buf_काष्ठा_size = माप(काष्ठा allegro_m2m_buffer);
	dst_vq->lock = &channel->dev->lock;
	err = vb2_queue_init(dst_vq);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक allegro_clamp_qp(काष्ठा allegro_channel *channel,
			    काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_ctrl *next_ctrl;

	अगर (ctrl->id == V4L2_CID_MPEG_VIDEO_H264_I_FRAME_QP)
		next_ctrl = channel->mpeg_video_h264_p_frame_qp;
	अन्यथा अगर (ctrl->id == V4L2_CID_MPEG_VIDEO_H264_P_FRAME_QP)
		next_ctrl = channel->mpeg_video_h264_b_frame_qp;
	अन्यथा
		वापस 0;

	/* Modअगरy range स्वतःmatically updates the value */
	__v4l2_ctrl_modअगरy_range(next_ctrl, ctrl->val, 51, 1, ctrl->val);

	वापस allegro_clamp_qp(channel, next_ctrl);
पूर्ण

अटल पूर्णांक allegro_clamp_bitrate(काष्ठा allegro_channel *channel,
				 काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_ctrl *ctrl_bitrate = channel->mpeg_video_bitrate;
	काष्ठा v4l2_ctrl *ctrl_bitrate_peak = channel->mpeg_video_bitrate_peak;

	अगर (ctrl->val == V4L2_MPEG_VIDEO_BITRATE_MODE_VBR &&
	    ctrl_bitrate_peak->val < ctrl_bitrate->val)
		ctrl_bitrate_peak->val = ctrl_bitrate->val;

	वापस 0;
पूर्ण

अटल पूर्णांक allegro_try_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा allegro_channel *channel = container_of(ctrl->handler,
						       काष्ठा allegro_channel,
						       ctrl_handler);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_MPEG_VIDEO_BITRATE_MODE:
		allegro_clamp_bitrate(channel, ctrl);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक allegro_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा allegro_channel *channel = container_of(ctrl->handler,
						       काष्ठा allegro_channel,
						       ctrl_handler);
	काष्ठा allegro_dev *dev = channel->dev;

	v4l2_dbg(1, debug, &dev->v4l2_dev,
		 "s_ctrl: %s = %d\n", v4l2_ctrl_get_name(ctrl->id), ctrl->val);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_MPEG_VIDEO_FRAME_RC_ENABLE:
		channel->frame_rc_enable = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_BITRATE_MODE:
		channel->bitrate = channel->mpeg_video_bitrate->val;
		channel->bitrate_peak = channel->mpeg_video_bitrate_peak->val;
		v4l2_ctrl_activate(channel->mpeg_video_bitrate_peak,
				   ctrl->val == V4L2_MPEG_VIDEO_BITRATE_MODE_VBR);
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_I_FRAME_QP:
	हाल V4L2_CID_MPEG_VIDEO_H264_P_FRAME_QP:
	हाल V4L2_CID_MPEG_VIDEO_H264_B_FRAME_QP:
		allegro_clamp_qp(channel, ctrl);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops allegro_ctrl_ops = अणु
	.try_ctrl = allegro_try_ctrl,
	.s_ctrl = allegro_s_ctrl,
पूर्ण;

अटल पूर्णांक allegro_खोलो(काष्ठा file *file)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा allegro_dev *dev = video_get_drvdata(vdev);
	काष्ठा allegro_channel *channel = शून्य;
	काष्ठा v4l2_ctrl_handler *handler;
	u64 mask;
	पूर्णांक ret;
	अचिन्हित पूर्णांक bitrate_max;
	अचिन्हित पूर्णांक bitrate_def;
	अचिन्हित पूर्णांक cpb_size_max;
	अचिन्हित पूर्णांक cpb_size_def;

	channel = kzalloc(माप(*channel), GFP_KERNEL);
	अगर (!channel)
		वापस -ENOMEM;

	v4l2_fh_init(&channel->fh, vdev);

	init_completion(&channel->completion);
	INIT_LIST_HEAD(&channel->source_shaकरोw_list);
	INIT_LIST_HEAD(&channel->stream_shaकरोw_list);
	mutex_init(&channel->shaकरोw_list_lock);

	channel->dev = dev;

	allegro_set_शेष_params(channel);

	handler = &channel->ctrl_handler;
	v4l2_ctrl_handler_init(handler, 0);
	channel->mpeg_video_h264_profile = v4l2_ctrl_new_std_menu(handler,
			&allegro_ctrl_ops,
			V4L2_CID_MPEG_VIDEO_H264_PROखाता,
			V4L2_MPEG_VIDEO_H264_PROखाता_BASELINE, 0x0,
			V4L2_MPEG_VIDEO_H264_PROखाता_BASELINE);
	mask = 1 << V4L2_MPEG_VIDEO_H264_LEVEL_1B;
	channel->mpeg_video_h264_level = v4l2_ctrl_new_std_menu(handler,
			&allegro_ctrl_ops,
			V4L2_CID_MPEG_VIDEO_H264_LEVEL,
			V4L2_MPEG_VIDEO_H264_LEVEL_5_1, mask,
			V4L2_MPEG_VIDEO_H264_LEVEL_5_1);
	channel->mpeg_video_h264_i_frame_qp =
		v4l2_ctrl_new_std(handler,
				  &allegro_ctrl_ops,
				  V4L2_CID_MPEG_VIDEO_H264_I_FRAME_QP,
				  0, 51, 1, 30);
	channel->mpeg_video_h264_max_qp =
		v4l2_ctrl_new_std(handler,
				  &allegro_ctrl_ops,
				  V4L2_CID_MPEG_VIDEO_H264_MAX_QP,
				  0, 51, 1, 51);
	channel->mpeg_video_h264_min_qp =
		v4l2_ctrl_new_std(handler,
				  &allegro_ctrl_ops,
				  V4L2_CID_MPEG_VIDEO_H264_MIN_QP,
				  0, 51, 1, 0);
	channel->mpeg_video_h264_p_frame_qp =
		v4l2_ctrl_new_std(handler,
				  &allegro_ctrl_ops,
				  V4L2_CID_MPEG_VIDEO_H264_P_FRAME_QP,
				  0, 51, 1, 30);
	channel->mpeg_video_h264_b_frame_qp =
		v4l2_ctrl_new_std(handler,
				  &allegro_ctrl_ops,
				  V4L2_CID_MPEG_VIDEO_H264_B_FRAME_QP,
				  0, 51, 1, 30);

	channel->mpeg_video_hevc_profile =
		v4l2_ctrl_new_std_menu(handler,
				       &allegro_ctrl_ops,
				       V4L2_CID_MPEG_VIDEO_HEVC_PROखाता,
				       V4L2_MPEG_VIDEO_HEVC_PROखाता_MAIN, 0x0,
				       V4L2_MPEG_VIDEO_HEVC_PROखाता_MAIN);
	channel->mpeg_video_hevc_level =
		v4l2_ctrl_new_std_menu(handler,
				       &allegro_ctrl_ops,
				       V4L2_CID_MPEG_VIDEO_HEVC_LEVEL,
				       V4L2_MPEG_VIDEO_HEVC_LEVEL_5_1, 0x0,
				       V4L2_MPEG_VIDEO_HEVC_LEVEL_5_1);
	channel->mpeg_video_hevc_tier =
		v4l2_ctrl_new_std_menu(handler,
				       &allegro_ctrl_ops,
				       V4L2_CID_MPEG_VIDEO_HEVC_TIER,
				       V4L2_MPEG_VIDEO_HEVC_TIER_HIGH, 0x0,
				       V4L2_MPEG_VIDEO_HEVC_TIER_MAIN);
	channel->mpeg_video_hevc_i_frame_qp =
		v4l2_ctrl_new_std(handler,
				  &allegro_ctrl_ops,
				  V4L2_CID_MPEG_VIDEO_HEVC_I_FRAME_QP,
				  0, 51, 1, 30);
	channel->mpeg_video_hevc_max_qp =
		v4l2_ctrl_new_std(handler,
				  &allegro_ctrl_ops,
				  V4L2_CID_MPEG_VIDEO_HEVC_MAX_QP,
				  0, 51, 1, 51);
	channel->mpeg_video_hevc_min_qp =
		v4l2_ctrl_new_std(handler,
				  &allegro_ctrl_ops,
				  V4L2_CID_MPEG_VIDEO_HEVC_MIN_QP,
				  0, 51, 1, 0);
	channel->mpeg_video_hevc_p_frame_qp =
		v4l2_ctrl_new_std(handler,
				  &allegro_ctrl_ops,
				  V4L2_CID_MPEG_VIDEO_HEVC_P_FRAME_QP,
				  0, 51, 1, 30);
	channel->mpeg_video_hevc_b_frame_qp =
		v4l2_ctrl_new_std(handler,
				  &allegro_ctrl_ops,
				  V4L2_CID_MPEG_VIDEO_HEVC_B_FRAME_QP,
				  0, 51, 1, 30);

	channel->mpeg_video_frame_rc_enable =
		v4l2_ctrl_new_std(handler,
				  &allegro_ctrl_ops,
				  V4L2_CID_MPEG_VIDEO_FRAME_RC_ENABLE,
				  false, 0x1,
				  true, false);
	channel->mpeg_video_bitrate_mode = v4l2_ctrl_new_std_menu(handler,
			&allegro_ctrl_ops,
			V4L2_CID_MPEG_VIDEO_BITRATE_MODE,
			V4L2_MPEG_VIDEO_BITRATE_MODE_CBR, 0,
			V4L2_MPEG_VIDEO_BITRATE_MODE_CBR);

	अगर (channel->codec == V4L2_PIX_FMT_H264) अणु
		bitrate_max = h264_maximum_bitrate(V4L2_MPEG_VIDEO_H264_LEVEL_5_1);
		bitrate_def = h264_maximum_bitrate(V4L2_MPEG_VIDEO_H264_LEVEL_5_1);
		cpb_size_max = h264_maximum_cpb_size(V4L2_MPEG_VIDEO_H264_LEVEL_5_1);
		cpb_size_def = h264_maximum_cpb_size(V4L2_MPEG_VIDEO_H264_LEVEL_5_1);
	पूर्ण अन्यथा अणु
		bitrate_max = hevc_maximum_bitrate(V4L2_MPEG_VIDEO_HEVC_LEVEL_5_1);
		bitrate_def = hevc_maximum_bitrate(V4L2_MPEG_VIDEO_HEVC_LEVEL_5_1);
		cpb_size_max = hevc_maximum_cpb_size(V4L2_MPEG_VIDEO_HEVC_LEVEL_5_1);
		cpb_size_def = hevc_maximum_cpb_size(V4L2_MPEG_VIDEO_HEVC_LEVEL_5_1);
	पूर्ण
	channel->mpeg_video_bitrate = v4l2_ctrl_new_std(handler,
			&allegro_ctrl_ops,
			V4L2_CID_MPEG_VIDEO_BITRATE,
			0, bitrate_max, 1, bitrate_def);
	channel->mpeg_video_bitrate_peak = v4l2_ctrl_new_std(handler,
			&allegro_ctrl_ops,
			V4L2_CID_MPEG_VIDEO_BITRATE_PEAK,
			0, bitrate_max, 1, bitrate_def);
	channel->mpeg_video_cpb_size = v4l2_ctrl_new_std(handler,
			&allegro_ctrl_ops,
			V4L2_CID_MPEG_VIDEO_H264_CPB_SIZE,
			0, cpb_size_max, 1, cpb_size_def);
	channel->mpeg_video_gop_size = v4l2_ctrl_new_std(handler,
			&allegro_ctrl_ops,
			V4L2_CID_MPEG_VIDEO_GOP_SIZE,
			0, ALLEGRO_GOP_SIZE_MAX,
			1, ALLEGRO_GOP_SIZE_DEFAULT);
	v4l2_ctrl_new_std(handler,
			  &allegro_ctrl_ops,
			  V4L2_CID_MIN_BUFFERS_FOR_OUTPUT,
			  1, 32,
			  1, 1);
	अगर (handler->error != 0) अणु
		ret = handler->error;
		जाओ error;
	पूर्ण

	channel->fh.ctrl_handler = handler;

	v4l2_ctrl_cluster(3, &channel->mpeg_video_bitrate_mode);

	v4l2_ctrl_handler_setup(handler);

	channel->mcu_channel_id = -1;
	channel->user_id = -1;

	INIT_LIST_HEAD(&channel->buffers_reference);
	INIT_LIST_HEAD(&channel->buffers_पूर्णांकermediate);

	channel->fh.m2m_ctx = v4l2_m2m_ctx_init(dev->m2m_dev, channel,
						allegro_queue_init);

	अगर (IS_ERR(channel->fh.m2m_ctx)) अणु
		ret = PTR_ERR(channel->fh.m2m_ctx);
		जाओ error;
	पूर्ण

	list_add(&channel->list, &dev->channels);
	file->निजी_data = &channel->fh;
	v4l2_fh_add(&channel->fh);

	allegro_channel_adjust(channel);

	वापस 0;

error:
	v4l2_ctrl_handler_मुक्त(handler);
	kमुक्त(channel);
	वापस ret;
पूर्ण

अटल पूर्णांक allegro_release(काष्ठा file *file)
अणु
	काष्ठा allegro_channel *channel = fh_to_channel(file->निजी_data);

	v4l2_m2m_ctx_release(channel->fh.m2m_ctx);

	list_del(&channel->list);

	v4l2_ctrl_handler_मुक्त(&channel->ctrl_handler);

	v4l2_fh_del(&channel->fh);
	v4l2_fh_निकास(&channel->fh);

	kमुक्त(channel);

	वापस 0;
पूर्ण

अटल पूर्णांक allegro_querycap(काष्ठा file *file, व्योम *fh,
			    काष्ठा v4l2_capability *cap)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा allegro_dev *dev = video_get_drvdata(vdev);

	strscpy(cap->driver, KBUILD_MODNAME, माप(cap->driver));
	strscpy(cap->card, "Allegro DVT Video Encoder", माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "platform:%s",
		 dev_name(&dev->plat_dev->dev));

	वापस 0;
पूर्ण

अटल पूर्णांक allegro_क्रमागत_fmt_vid(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_fmtdesc *f)
अणु
	चयन (f->type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT:
		अगर (f->index >= 1)
			वापस -EINVAL;
		f->pixelक्रमmat = V4L2_PIX_FMT_NV12;
		अवरोध;
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
		अगर (f->index >= 2)
			वापस -EINVAL;
		अगर (f->index == 0)
			f->pixelक्रमmat = V4L2_PIX_FMT_H264;
		अगर (f->index == 1)
			f->pixelक्रमmat = V4L2_PIX_FMT_HEVC;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक allegro_g_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
				 काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा allegro_channel *channel = fh_to_channel(fh);

	f->fmt.pix.field = V4L2_FIELD_NONE;
	f->fmt.pix.width = channel->width;
	f->fmt.pix.height = channel->height;

	f->fmt.pix.colorspace = channel->colorspace;
	f->fmt.pix.ycbcr_enc = channel->ycbcr_enc;
	f->fmt.pix.quantization = channel->quantization;
	f->fmt.pix.xfer_func = channel->xfer_func;

	f->fmt.pix.pixelक्रमmat = channel->codec;
	f->fmt.pix.bytesperline = 0;
	f->fmt.pix.sizeimage = channel->sizeimage_encoded;

	वापस 0;
पूर्ण

अटल पूर्णांक allegro_try_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
				   काष्ठा v4l2_क्रमmat *f)
अणु
	f->fmt.pix.field = V4L2_FIELD_NONE;

	f->fmt.pix.width = clamp_t(__u32, f->fmt.pix.width,
				   ALLEGRO_WIDTH_MIN, ALLEGRO_WIDTH_MAX);
	f->fmt.pix.height = clamp_t(__u32, f->fmt.pix.height,
				    ALLEGRO_HEIGHT_MIN, ALLEGRO_HEIGHT_MAX);

	अगर (f->fmt.pix.pixelक्रमmat != V4L2_PIX_FMT_HEVC &&
	    f->fmt.pix.pixelक्रमmat != V4L2_PIX_FMT_H264)
		f->fmt.pix.pixelक्रमmat = V4L2_PIX_FMT_H264;

	f->fmt.pix.bytesperline = 0;
	f->fmt.pix.sizeimage =
		estimate_stream_size(f->fmt.pix.width, f->fmt.pix.height);

	वापस 0;
पूर्ण

अटल पूर्णांक allegro_s_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
				 काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा allegro_channel *channel = fh_to_channel(fh);
	काष्ठा vb2_queue *vq;
	पूर्णांक err;

	err = allegro_try_fmt_vid_cap(file, fh, f);
	अगर (err)
		वापस err;

	vq = v4l2_m2m_get_vq(channel->fh.m2m_ctx, f->type);
	अगर (!vq)
		वापस -EINVAL;
	अगर (vb2_is_busy(vq))
		वापस -EBUSY;

	channel->codec = f->fmt.pix.pixelक्रमmat;

	allegro_channel_adjust(channel);

	वापस 0;
पूर्ण

अटल पूर्णांक allegro_g_fmt_vid_out(काष्ठा file *file, व्योम *fh,
				 काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा allegro_channel *channel = fh_to_channel(fh);

	f->fmt.pix.field = V4L2_FIELD_NONE;

	f->fmt.pix.width = channel->width;
	f->fmt.pix.height = channel->height;

	f->fmt.pix.colorspace = channel->colorspace;
	f->fmt.pix.ycbcr_enc = channel->ycbcr_enc;
	f->fmt.pix.quantization = channel->quantization;
	f->fmt.pix.xfer_func = channel->xfer_func;

	f->fmt.pix.pixelक्रमmat = channel->pixelक्रमmat;
	f->fmt.pix.bytesperline = channel->stride;
	f->fmt.pix.sizeimage = channel->sizeimage_raw;

	वापस 0;
पूर्ण

अटल पूर्णांक allegro_try_fmt_vid_out(काष्ठा file *file, व्योम *fh,
				   काष्ठा v4l2_क्रमmat *f)
अणु
	f->fmt.pix.field = V4L2_FIELD_NONE;

	/*
	 * The firmware of the Allegro codec handles the padding पूर्णांकernally
	 * and expects the visual frame size when configuring a channel.
	 * Thereक्रमe, unlike other encoder drivers, this driver करोes not round
	 * up the width and height to macroblock alignment and करोes not
	 * implement the selection api.
	 */
	f->fmt.pix.width = clamp_t(__u32, f->fmt.pix.width,
				   ALLEGRO_WIDTH_MIN, ALLEGRO_WIDTH_MAX);
	f->fmt.pix.height = clamp_t(__u32, f->fmt.pix.height,
				    ALLEGRO_HEIGHT_MIN, ALLEGRO_HEIGHT_MAX);

	f->fmt.pix.pixelक्रमmat = V4L2_PIX_FMT_NV12;
	f->fmt.pix.bytesperline = round_up(f->fmt.pix.width, 32);
	f->fmt.pix.sizeimage =
		f->fmt.pix.bytesperline * f->fmt.pix.height * 3 / 2;

	वापस 0;
पूर्ण

अटल पूर्णांक allegro_s_fmt_vid_out(काष्ठा file *file, व्योम *fh,
				 काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा allegro_channel *channel = fh_to_channel(fh);
	पूर्णांक err;

	err = allegro_try_fmt_vid_out(file, fh, f);
	अगर (err)
		वापस err;

	channel->width = f->fmt.pix.width;
	channel->height = f->fmt.pix.height;
	channel->stride = f->fmt.pix.bytesperline;
	channel->sizeimage_raw = f->fmt.pix.sizeimage;

	channel->colorspace = f->fmt.pix.colorspace;
	channel->ycbcr_enc = f->fmt.pix.ycbcr_enc;
	channel->quantization = f->fmt.pix.quantization;
	channel->xfer_func = f->fmt.pix.xfer_func;

	allegro_channel_adjust(channel);

	वापस 0;
पूर्ण

अटल पूर्णांक allegro_channel_cmd_stop(काष्ठा allegro_channel *channel)
अणु
	अगर (v4l2_m2m_has_stopped(channel->fh.m2m_ctx))
		allegro_channel_eos_event(channel);

	वापस 0;
पूर्ण

अटल पूर्णांक allegro_channel_cmd_start(काष्ठा allegro_channel *channel)
अणु
	अगर (v4l2_m2m_has_stopped(channel->fh.m2m_ctx))
		vb2_clear_last_buffer_dequeued(&channel->fh.m2m_ctx->cap_q_ctx.q);

	वापस 0;
पूर्ण

अटल पूर्णांक allegro_encoder_cmd(काष्ठा file *file, व्योम *fh,
			       काष्ठा v4l2_encoder_cmd *cmd)
अणु
	काष्ठा allegro_channel *channel = fh_to_channel(fh);
	पूर्णांक err;

	err = v4l2_m2m_ioctl_try_encoder_cmd(file, fh, cmd);
	अगर (err)
		वापस err;

	err = v4l2_m2m_ioctl_encoder_cmd(file, fh, cmd);
	अगर (err)
		वापस err;

	अगर (cmd->cmd == V4L2_ENC_CMD_STOP)
		err = allegro_channel_cmd_stop(channel);

	अगर (cmd->cmd == V4L2_ENC_CMD_START)
		err = allegro_channel_cmd_start(channel);

	वापस err;
पूर्ण

अटल पूर्णांक allegro_क्रमागत_framesizes(काष्ठा file *file, व्योम *fh,
				   काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	चयन (fsize->pixel_क्रमmat) अणु
	हाल V4L2_PIX_FMT_HEVC:
	हाल V4L2_PIX_FMT_H264:
	हाल V4L2_PIX_FMT_NV12:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (fsize->index)
		वापस -EINVAL;

	fsize->type = V4L2_FRMSIZE_TYPE_CONTINUOUS;
	fsize->stepwise.min_width = ALLEGRO_WIDTH_MIN;
	fsize->stepwise.max_width = ALLEGRO_WIDTH_MAX;
	fsize->stepwise.step_width = 1;
	fsize->stepwise.min_height = ALLEGRO_HEIGHT_MIN;
	fsize->stepwise.max_height = ALLEGRO_HEIGHT_MAX;
	fsize->stepwise.step_height = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक allegro_ioctl_streamon(काष्ठा file *file, व्योम *priv,
				  क्रमागत v4l2_buf_type type)
अणु
	काष्ठा v4l2_fh *fh = file->निजी_data;
	काष्ठा allegro_channel *channel = fh_to_channel(fh);
	पूर्णांक err;

	अगर (type == V4L2_BUF_TYPE_VIDEO_CAPTURE) अणु
		err = allegro_create_channel(channel);
		अगर (err)
			वापस err;
	पूर्ण

	वापस v4l2_m2m_streamon(file, fh->m2m_ctx, type);
पूर्ण

अटल पूर्णांक allegro_g_parm(काष्ठा file *file, व्योम *fh,
			  काष्ठा v4l2_streamparm *a)
अणु
	काष्ठा allegro_channel *channel = fh_to_channel(fh);
	काष्ठा v4l2_fract *समयperframe;

	अगर (a->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		वापस -EINVAL;

	a->parm.output.capability = V4L2_CAP_TIMEPERFRAME;
	समयperframe = &a->parm.output.समयperframe;
	समयperframe->numerator = channel->framerate.denominator;
	समयperframe->denominator = channel->framerate.numerator;

	वापस 0;
पूर्ण

अटल पूर्णांक allegro_s_parm(काष्ठा file *file, व्योम *fh,
			  काष्ठा v4l2_streamparm *a)
अणु
	काष्ठा allegro_channel *channel = fh_to_channel(fh);
	काष्ठा v4l2_fract *समयperframe;
	पूर्णांक भाग;

	अगर (a->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		वापस -EINVAL;

	a->parm.output.capability = V4L2_CAP_TIMEPERFRAME;
	समयperframe = &a->parm.output.समयperframe;

	अगर (समयperframe->numerator == 0 || समयperframe->denominator == 0)
		वापस allegro_g_parm(file, fh, a);

	भाग = gcd(समयperframe->denominator, समयperframe->numerator);
	channel->framerate.numerator = समयperframe->denominator / भाग;
	channel->framerate.denominator = समयperframe->numerator / भाग;

	वापस 0;
पूर्ण

अटल पूर्णांक allegro_subscribe_event(काष्ठा v4l2_fh *fh,
				   स्थिर काष्ठा v4l2_event_subscription *sub)
अणु
	चयन (sub->type) अणु
	हाल V4L2_EVENT_EOS:
		वापस v4l2_event_subscribe(fh, sub, 0, शून्य);
	शेष:
		वापस v4l2_ctrl_subscribe_event(fh, sub);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops allegro_ioctl_ops = अणु
	.vidioc_querycap = allegro_querycap,
	.vidioc_क्रमागत_fmt_vid_cap = allegro_क्रमागत_fmt_vid,
	.vidioc_क्रमागत_fmt_vid_out = allegro_क्रमागत_fmt_vid,
	.vidioc_g_fmt_vid_cap = allegro_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap = allegro_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap = allegro_s_fmt_vid_cap,
	.vidioc_g_fmt_vid_out = allegro_g_fmt_vid_out,
	.vidioc_try_fmt_vid_out = allegro_try_fmt_vid_out,
	.vidioc_s_fmt_vid_out = allegro_s_fmt_vid_out,

	.vidioc_create_bufs = v4l2_m2m_ioctl_create_bufs,
	.vidioc_reqbufs = v4l2_m2m_ioctl_reqbufs,

	.vidioc_expbuf = v4l2_m2m_ioctl_expbuf,
	.vidioc_querybuf = v4l2_m2m_ioctl_querybuf,
	.vidioc_qbuf = v4l2_m2m_ioctl_qbuf,
	.vidioc_dqbuf = v4l2_m2m_ioctl_dqbuf,
	.vidioc_prepare_buf = v4l2_m2m_ioctl_prepare_buf,

	.vidioc_streamon = allegro_ioctl_streamon,
	.vidioc_streamoff = v4l2_m2m_ioctl_streamoff,

	.vidioc_try_encoder_cmd = v4l2_m2m_ioctl_try_encoder_cmd,
	.vidioc_encoder_cmd = allegro_encoder_cmd,
	.vidioc_क्रमागत_framesizes = allegro_क्रमागत_framesizes,

	.vidioc_g_parm		= allegro_g_parm,
	.vidioc_s_parm		= allegro_s_parm,

	.vidioc_subscribe_event = allegro_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations allegro_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = allegro_खोलो,
	.release = allegro_release,
	.poll = v4l2_m2m_fop_poll,
	.unlocked_ioctl = video_ioctl2,
	.mmap = v4l2_m2m_fop_mmap,
पूर्ण;

अटल पूर्णांक allegro_रेजिस्टर_device(काष्ठा allegro_dev *dev)
अणु
	काष्ठा video_device *video_dev = &dev->video_dev;

	strscpy(video_dev->name, "allegro", माप(video_dev->name));
	video_dev->fops = &allegro_fops;
	video_dev->ioctl_ops = &allegro_ioctl_ops;
	video_dev->release = video_device_release_empty;
	video_dev->lock = &dev->lock;
	video_dev->v4l2_dev = &dev->v4l2_dev;
	video_dev->vfl_dir = VFL_सूची_M2M;
	video_dev->device_caps = V4L2_CAP_VIDEO_M2M | V4L2_CAP_STREAMING;
	video_set_drvdata(video_dev, dev);

	वापस video_रेजिस्टर_device(video_dev, VFL_TYPE_VIDEO, 0);
पूर्ण

अटल व्योम allegro_device_run(व्योम *priv)
अणु
	काष्ठा allegro_channel *channel = priv;
	काष्ठा allegro_dev *dev = channel->dev;
	काष्ठा vb2_v4l2_buffer *src_buf;
	काष्ठा vb2_v4l2_buffer *dst_buf;
	dma_addr_t src_y;
	dma_addr_t src_uv;
	dma_addr_t dst_addr;
	अचिन्हित दीर्घ dst_size;
	u64 src_handle;
	u64 dst_handle;

	dst_buf = v4l2_m2m_dst_buf_हटाओ(channel->fh.m2m_ctx);
	dst_addr = vb2_dma_contig_plane_dma_addr(&dst_buf->vb2_buf, 0);
	dst_size = vb2_plane_size(&dst_buf->vb2_buf, 0);
	dst_handle = allegro_put_buffer(channel, &channel->stream_shaकरोw_list,
					dst_buf);
	allegro_mcu_send_put_stream_buffer(dev, channel, dst_addr, dst_size,
					   dst_handle);

	src_buf = v4l2_m2m_src_buf_हटाओ(channel->fh.m2m_ctx);
	src_buf->sequence = channel->osequence++;
	src_y = vb2_dma_contig_plane_dma_addr(&src_buf->vb2_buf, 0);
	src_uv = src_y + (channel->stride * channel->height);
	src_handle = allegro_put_buffer(channel, &channel->source_shaकरोw_list,
					src_buf);
	allegro_mcu_send_encode_frame(dev, channel, src_y, src_uv, src_handle);

	v4l2_m2m_job_finish(dev->m2m_dev, channel->fh.m2m_ctx);
पूर्ण

अटल स्थिर काष्ठा v4l2_m2m_ops allegro_m2m_ops = अणु
	.device_run = allegro_device_run,
पूर्ण;

अटल पूर्णांक allegro_mcu_hw_init(काष्ठा allegro_dev *dev,
			       स्थिर काष्ठा fw_info *info)
अणु
	पूर्णांक err;

	dev->mbox_command = allegro_mbox_init(dev, info->mailbox_cmd,
					      info->mailbox_size);
	dev->mbox_status = allegro_mbox_init(dev, info->mailbox_status,
					     info->mailbox_size);
	अगर (IS_ERR(dev->mbox_command) || IS_ERR(dev->mbox_status)) अणु
		v4l2_err(&dev->v4l2_dev,
			 "failed to initialize mailboxes\n");
		वापस -EIO;
	पूर्ण

	allegro_mcu_enable_पूर्णांकerrupts(dev);

	/* The mcu sends INIT after reset. */
	allegro_mcu_start(dev);
	err = allegro_mcu_रुको_क्रम_init_समयout(dev, 5000);
	अगर (err < 0) अणु
		v4l2_err(&dev->v4l2_dev,
			 "mcu did not send INIT after reset\n");
		err = -EIO;
		जाओ err_disable_पूर्णांकerrupts;
	पूर्ण

	err = allegro_alloc_buffer(dev, &dev->suballocator,
				   info->suballocator_size);
	अगर (err) अणु
		v4l2_err(&dev->v4l2_dev,
			 "failed to allocate %zu bytes for suballocator\n",
			 info->suballocator_size);
		जाओ err_reset_mcu;
	पूर्ण

	allegro_mcu_send_init(dev, dev->suballocator.paddr,
			      dev->suballocator.size);
	err = allegro_mcu_रुको_क्रम_init_समयout(dev, 5000);
	अगर (err < 0) अणु
		v4l2_err(&dev->v4l2_dev,
			 "mcu failed to configure sub-allocator\n");
		err = -EIO;
		जाओ err_मुक्त_suballocator;
	पूर्ण

	वापस 0;

err_मुक्त_suballocator:
	allegro_मुक्त_buffer(dev, &dev->suballocator);
err_reset_mcu:
	allegro_mcu_reset(dev);
err_disable_पूर्णांकerrupts:
	allegro_mcu_disable_पूर्णांकerrupts(dev);

	वापस err;
पूर्ण

अटल पूर्णांक allegro_mcu_hw_deinit(काष्ठा allegro_dev *dev)
अणु
	पूर्णांक err;

	err = allegro_mcu_reset(dev);
	अगर (err)
		v4l2_warn(&dev->v4l2_dev,
			  "mcu failed to enter sleep state\n");

	err = allegro_mcu_disable_पूर्णांकerrupts(dev);
	अगर (err)
		v4l2_warn(&dev->v4l2_dev,
			  "failed to disable interrupts\n");

	allegro_मुक्त_buffer(dev, &dev->suballocator);

	वापस 0;
पूर्ण

अटल व्योम allegro_fw_callback(स्थिर काष्ठा firmware *fw, व्योम *context)
अणु
	काष्ठा allegro_dev *dev = context;
	स्थिर अक्षर *fw_codec_name = "al5e.fw";
	स्थिर काष्ठा firmware *fw_codec;
	पूर्णांक err;

	अगर (!fw)
		वापस;

	v4l2_dbg(1, debug, &dev->v4l2_dev,
		 "requesting codec firmware '%s'\n", fw_codec_name);
	err = request_firmware(&fw_codec, fw_codec_name, &dev->plat_dev->dev);
	अगर (err)
		जाओ err_release_firmware;

	dev->fw_info = allegro_get_firmware_info(dev, fw, fw_codec);
	अगर (!dev->fw_info) अणु
		v4l2_err(&dev->v4l2_dev, "firmware is not supported\n");
		जाओ err_release_firmware_codec;
	पूर्ण

	v4l2_info(&dev->v4l2_dev,
		  "using mcu firmware version '%s'\n", dev->fw_info->version);

	/* Ensure that the mcu is sleeping at the reset vector */
	err = allegro_mcu_reset(dev);
	अगर (err) अणु
		v4l2_err(&dev->v4l2_dev, "failed to reset mcu\n");
		जाओ err_release_firmware_codec;
	पूर्ण

	allegro_copy_firmware(dev, fw->data, fw->size);
	allegro_copy_fw_codec(dev, fw_codec->data, fw_codec->size);

	err = allegro_mcu_hw_init(dev, dev->fw_info);
	अगर (err) अणु
		v4l2_err(&dev->v4l2_dev, "failed to initialize mcu\n");
		जाओ err_मुक्त_fw_codec;
	पूर्ण

	dev->m2m_dev = v4l2_m2m_init(&allegro_m2m_ops);
	अगर (IS_ERR(dev->m2m_dev)) अणु
		v4l2_err(&dev->v4l2_dev, "failed to init mem2mem device\n");
		जाओ err_mcu_hw_deinit;
	पूर्ण

	err = allegro_रेजिस्टर_device(dev);
	अगर (err) अणु
		v4l2_err(&dev->v4l2_dev, "failed to register video device\n");
		जाओ err_m2m_release;
	पूर्ण

	v4l2_dbg(1, debug, &dev->v4l2_dev,
		 "allegro codec registered as /dev/video%d\n",
		 dev->video_dev.num);

	release_firmware(fw_codec);
	release_firmware(fw);

	वापस;

err_m2m_release:
	v4l2_m2m_release(dev->m2m_dev);
	dev->m2m_dev = शून्य;
err_mcu_hw_deinit:
	allegro_mcu_hw_deinit(dev);
err_मुक्त_fw_codec:
	allegro_मुक्त_fw_codec(dev);
err_release_firmware_codec:
	release_firmware(fw_codec);
err_release_firmware:
	release_firmware(fw);
पूर्ण

अटल पूर्णांक allegro_firmware_request_noरुको(काष्ठा allegro_dev *dev)
अणु
	स्थिर अक्षर *fw = "al5e_b.fw";

	v4l2_dbg(1, debug, &dev->v4l2_dev,
		 "requesting firmware '%s'\n", fw);
	वापस request_firmware_noरुको(THIS_MODULE, true, fw,
				       &dev->plat_dev->dev, GFP_KERNEL, dev,
				       allegro_fw_callback);
पूर्ण

अटल पूर्णांक allegro_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा allegro_dev *dev;
	काष्ठा resource *res, *sram_res;
	पूर्णांक ret;
	पूर्णांक irq;
	व्योम __iomem *regs, *sram_regs;

	dev = devm_kzalloc(&pdev->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;
	dev->plat_dev = pdev;
	init_completion(&dev->init_complete);
	INIT_LIST_HEAD(&dev->channels);

	mutex_init(&dev->lock);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "regs");
	अगर (!res) अणु
		dev_err(&pdev->dev,
			"regs resource missing from device tree\n");
		वापस -EINVAL;
	पूर्ण
	regs = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	अगर (!regs) अणु
		dev_err(&pdev->dev, "failed to map registers\n");
		वापस -ENOMEM;
	पूर्ण
	dev->regmap = devm_regmap_init_mmio(&pdev->dev, regs,
					    &allegro_regmap_config);
	अगर (IS_ERR(dev->regmap)) अणु
		dev_err(&pdev->dev, "failed to init regmap\n");
		वापस PTR_ERR(dev->regmap);
	पूर्ण

	sram_res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "sram");
	अगर (!sram_res) अणु
		dev_err(&pdev->dev,
			"sram resource missing from device tree\n");
		वापस -EINVAL;
	पूर्ण
	sram_regs = devm_ioremap(&pdev->dev,
				 sram_res->start,
				 resource_size(sram_res));
	अगर (!sram_regs) अणु
		dev_err(&pdev->dev, "failed to map sram\n");
		वापस -ENOMEM;
	पूर्ण
	dev->sram = devm_regmap_init_mmio(&pdev->dev, sram_regs,
					  &allegro_sram_config);
	अगर (IS_ERR(dev->sram)) अणु
		dev_err(&pdev->dev, "failed to init sram\n");
		वापस PTR_ERR(dev->sram);
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;
	ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq,
					allegro_hardirq,
					allegro_irq_thपढ़ो,
					IRQF_SHARED, dev_name(&pdev->dev), dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to request irq: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = v4l2_device_रेजिस्टर(&pdev->dev, &dev->v4l2_dev);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, dev);

	ret = allegro_firmware_request_noरुको(dev);
	अगर (ret < 0) अणु
		v4l2_err(&dev->v4l2_dev,
			 "failed to request firmware: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक allegro_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा allegro_dev *dev = platक्रमm_get_drvdata(pdev);

	video_unरेजिस्टर_device(&dev->video_dev);
	अगर (dev->m2m_dev)
		v4l2_m2m_release(dev->m2m_dev);
	allegro_mcu_hw_deinit(dev);
	allegro_मुक्त_fw_codec(dev);

	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id allegro_dt_ids[] = अणु
	अणु .compatible = "allegro,al5e-1.1" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, allegro_dt_ids);

अटल काष्ठा platक्रमm_driver allegro_driver = अणु
	.probe = allegro_probe,
	.हटाओ = allegro_हटाओ,
	.driver = अणु
		.name = "allegro",
		.of_match_table = of_match_ptr(allegro_dt_ids),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(allegro_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Michael Tretter <kernel@pengutronix.de>");
MODULE_DESCRIPTION("Allegro DVT encoder driver");
