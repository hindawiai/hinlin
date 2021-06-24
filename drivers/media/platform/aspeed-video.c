<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
// Copyright 2020 IBM Corp.
// Copyright (c) 2019-2020 Intel Corporation

#समावेश <linux/atomic.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/v4l2-controls.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/रुको.h>
#समावेश <linux/workqueue.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-dv-timings.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf2-dma-contig.h>

#घोषणा DEVICE_NAME			"aspeed-video"

#घोषणा ASPEED_VIDEO_JPEG_NUM_QUALITIES	12
#घोषणा ASPEED_VIDEO_JPEG_HEADER_SIZE	10
#घोषणा ASPEED_VIDEO_JPEG_QUANT_SIZE	116
#घोषणा ASPEED_VIDEO_JPEG_DCT_SIZE	34

#घोषणा MAX_FRAME_RATE			60
#घोषणा MAX_HEIGHT			1200
#घोषणा MAX_WIDTH			1920
#घोषणा MIN_HEIGHT			480
#घोषणा MIN_WIDTH			640

#घोषणा NUM_POLARITY_CHECKS		10
#घोषणा INVALID_RESOLUTION_RETRIES	2
#घोषणा INVALID_RESOLUTION_DELAY	msecs_to_jअगरfies(250)
#घोषणा RESOLUTION_CHANGE_DELAY		msecs_to_jअगरfies(500)
#घोषणा MODE_DETECT_TIMEOUT		msecs_to_jअगरfies(500)
#घोषणा STOP_TIMEOUT			msecs_to_jअगरfies(1000)
#घोषणा सूचीECT_FETCH_THRESHOLD		0x0c0000 /* 1024 * 768 */

#घोषणा VE_MAX_SRC_BUFFER_SIZE		0x8ca000 /* 1920 * 1200, 32bpp */
#घोषणा VE_JPEG_HEADER_SIZE		0x006000 /* 512 * 12 * 4 */

#घोषणा VE_PROTECTION_KEY		0x000
#घोषणा  VE_PROTECTION_KEY_UNLOCK	0x1a038aa8

#घोषणा VE_SEQ_CTRL			0x004
#घोषणा  VE_SEQ_CTRL_TRIG_MODE_DET	BIT(0)
#घोषणा  VE_SEQ_CTRL_TRIG_CAPTURE	BIT(1)
#घोषणा  VE_SEQ_CTRL_FORCE_IDLE		BIT(2)
#घोषणा  VE_SEQ_CTRL_MULT_FRAME		BIT(3)
#घोषणा  VE_SEQ_CTRL_TRIG_COMP		BIT(4)
#घोषणा  VE_SEQ_CTRL_AUTO_COMP		BIT(5)
#घोषणा  VE_SEQ_CTRL_EN_WATCHDOG	BIT(7)
#घोषणा  VE_SEQ_CTRL_YUV420		BIT(10)
#घोषणा  VE_SEQ_CTRL_COMP_FMT		GENMASK(11, 10)
#घोषणा  VE_SEQ_CTRL_HALT		BIT(12)
#घोषणा  VE_SEQ_CTRL_EN_WATCHDOG_COMP	BIT(14)
#घोषणा  VE_SEQ_CTRL_TRIG_JPG		BIT(15)
#घोषणा  VE_SEQ_CTRL_CAP_BUSY		BIT(16)
#घोषणा  VE_SEQ_CTRL_COMP_BUSY		BIT(18)

#घोषणा AST2500_VE_SEQ_CTRL_JPEG_MODE	BIT(13)
#घोषणा AST2400_VE_SEQ_CTRL_JPEG_MODE	BIT(8)

#घोषणा VE_CTRL				0x008
#घोषणा  VE_CTRL_HSYNC_POL		BIT(0)
#घोषणा  VE_CTRL_VSYNC_POL		BIT(1)
#घोषणा  VE_CTRL_SOURCE			BIT(2)
#घोषणा  VE_CTRL_INT_DE			BIT(4)
#घोषणा  VE_CTRL_सूचीECT_FETCH		BIT(5)
#घोषणा  VE_CTRL_YUV			BIT(6)
#घोषणा  VE_CTRL_RGB			BIT(7)
#घोषणा  VE_CTRL_CAPTURE_FMT		GENMASK(7, 6)
#घोषणा  VE_CTRL_AUTO_OR_CURSOR		BIT(8)
#घोषणा  VE_CTRL_CLK_INVERSE		BIT(11)
#घोषणा  VE_CTRL_CLK_DELAY		GENMASK(11, 9)
#घोषणा  VE_CTRL_INTERLACE		BIT(14)
#घोषणा  VE_CTRL_HSYNC_POL_CTRL		BIT(15)
#घोषणा  VE_CTRL_FRC			GENMASK(23, 16)

#घोषणा VE_TGS_0			0x00c
#घोषणा VE_TGS_1			0x010
#घोषणा  VE_TGS_FIRST			GENMASK(28, 16)
#घोषणा  VE_TGS_LAST			GENMASK(12, 0)

#घोषणा VE_SCALING_FACTOR		0x014
#घोषणा VE_SCALING_FILTER0		0x018
#घोषणा VE_SCALING_FILTER1		0x01c
#घोषणा VE_SCALING_FILTER2		0x020
#घोषणा VE_SCALING_FILTER3		0x024

#घोषणा VE_CAP_WINDOW			0x030
#घोषणा VE_COMP_WINDOW			0x034
#घोषणा VE_COMP_PROC_OFFSET		0x038
#घोषणा VE_COMP_OFFSET			0x03c
#घोषणा VE_JPEG_ADDR			0x040
#घोषणा VE_SRC0_ADDR			0x044
#घोषणा VE_SRC_SCANLINE_OFFSET		0x048
#घोषणा VE_SRC1_ADDR			0x04c
#घोषणा VE_COMP_ADDR			0x054

#घोषणा VE_STREAM_BUF_SIZE		0x058
#घोषणा  VE_STREAM_BUF_SIZE_N_PACKETS	GENMASK(5, 3)
#घोषणा  VE_STREAM_BUF_SIZE_P_SIZE	GENMASK(2, 0)

#घोषणा VE_COMP_CTRL			0x060
#घोषणा  VE_COMP_CTRL_VQ_DCT_ONLY	BIT(0)
#घोषणा  VE_COMP_CTRL_VQ_4COLOR		BIT(1)
#घोषणा  VE_COMP_CTRL_QUANTIZE		BIT(2)
#घोषणा  VE_COMP_CTRL_EN_BQ		BIT(4)
#घोषणा  VE_COMP_CTRL_EN_CRYPTO		BIT(5)
#घोषणा  VE_COMP_CTRL_DCT_CHR		GENMASK(10, 6)
#घोषणा  VE_COMP_CTRL_DCT_LUM		GENMASK(15, 11)
#घोषणा  VE_COMP_CTRL_EN_HQ		BIT(16)
#घोषणा  VE_COMP_CTRL_RSVD		BIT(19)
#घोषणा  VE_COMP_CTRL_ENCODE		GENMASK(21, 20)
#घोषणा  VE_COMP_CTRL_HQ_DCT_CHR	GENMASK(26, 22)
#घोषणा  VE_COMP_CTRL_HQ_DCT_LUM	GENMASK(31, 27)

#घोषणा AST2400_VE_COMP_SIZE_READ_BACK	0x078
#घोषणा AST2600_VE_COMP_SIZE_READ_BACK	0x084

#घोषणा VE_SRC_LR_EDGE_DET		0x090
#घोषणा  VE_SRC_LR_EDGE_DET_LEFT	GENMASK(11, 0)
#घोषणा  VE_SRC_LR_EDGE_DET_NO_V	BIT(12)
#घोषणा  VE_SRC_LR_EDGE_DET_NO_H	BIT(13)
#घोषणा  VE_SRC_LR_EDGE_DET_NO_DISP	BIT(14)
#घोषणा  VE_SRC_LR_EDGE_DET_NO_CLK	BIT(15)
#घोषणा  VE_SRC_LR_EDGE_DET_RT_SHF	16
#घोषणा  VE_SRC_LR_EDGE_DET_RT		GENMASK(27, VE_SRC_LR_EDGE_DET_RT_SHF)
#घोषणा  VE_SRC_LR_EDGE_DET_INTERLACE	BIT(31)

#घोषणा VE_SRC_TB_EDGE_DET		0x094
#घोषणा  VE_SRC_TB_EDGE_DET_TOP		GENMASK(12, 0)
#घोषणा  VE_SRC_TB_EDGE_DET_BOT_SHF	16
#घोषणा  VE_SRC_TB_EDGE_DET_BOT		GENMASK(28, VE_SRC_TB_EDGE_DET_BOT_SHF)

#घोषणा VE_MODE_DETECT_STATUS		0x098
#घोषणा  VE_MODE_DETECT_H_PIXELS	GENMASK(11, 0)
#घोषणा  VE_MODE_DETECT_V_LINES_SHF	16
#घोषणा  VE_MODE_DETECT_V_LINES		GENMASK(27, VE_MODE_DETECT_V_LINES_SHF)
#घोषणा  VE_MODE_DETECT_STATUS_VSYNC	BIT(28)
#घोषणा  VE_MODE_DETECT_STATUS_HSYNC	BIT(29)

#घोषणा VE_SYNC_STATUS			0x09c
#घोषणा  VE_SYNC_STATUS_HSYNC		GENMASK(11, 0)
#घोषणा  VE_SYNC_STATUS_VSYNC_SHF	16
#घोषणा  VE_SYNC_STATUS_VSYNC		GENMASK(27, VE_SYNC_STATUS_VSYNC_SHF)

#घोषणा VE_INTERRUPT_CTRL		0x304
#घोषणा VE_INTERRUPT_STATUS		0x308
#घोषणा  VE_INTERRUPT_MODE_DETECT_WD	BIT(0)
#घोषणा  VE_INTERRUPT_CAPTURE_COMPLETE	BIT(1)
#घोषणा  VE_INTERRUPT_COMP_READY	BIT(2)
#घोषणा  VE_INTERRUPT_COMP_COMPLETE	BIT(3)
#घोषणा  VE_INTERRUPT_MODE_DETECT	BIT(4)
#घोषणा  VE_INTERRUPT_FRAME_COMPLETE	BIT(5)
#घोषणा  VE_INTERRUPT_DECODE_ERR	BIT(6)
#घोषणा  VE_INTERRUPT_HALT_READY	BIT(8)
#घोषणा  VE_INTERRUPT_HANG_WD		BIT(9)
#घोषणा  VE_INTERRUPT_STREAM_DESC	BIT(10)
#घोषणा  VE_INTERRUPT_VSYNC_DESC	BIT(11)

#घोषणा VE_MODE_DETECT			0x30c
#घोषणा VE_MEM_RESTRICT_START		0x310
#घोषणा VE_MEM_RESTRICT_END		0x314

क्रमागत अणु
	VIDEO_MODE_DETECT_DONE,
	VIDEO_RES_CHANGE,
	VIDEO_RES_DETECT,
	VIDEO_STREAMING,
	VIDEO_FRAME_INPRG,
	VIDEO_STOPPED,
	VIDEO_CLOCKS_ON,
पूर्ण;

काष्ठा aspeed_video_addr अणु
	अचिन्हित पूर्णांक size;
	dma_addr_t dma;
	व्योम *virt;
पूर्ण;

काष्ठा aspeed_video_buffer अणु
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head link;
पूर्ण;

#घोषणा to_aspeed_video_buffer(x) \
	container_of((x), काष्ठा aspeed_video_buffer, vb)

काष्ठा aspeed_video अणु
	व्योम __iomem *base;
	काष्ठा clk *eclk;
	काष्ठा clk *vclk;

	काष्ठा device *dev;
	काष्ठा v4l2_ctrl_handler ctrl_handler;
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा v4l2_pix_क्रमmat pix_fmt;
	काष्ठा v4l2_bt_timings active_timings;
	काष्ठा v4l2_bt_timings detected_timings;
	u32 v4l2_input_status;
	काष्ठा vb2_queue queue;
	काष्ठा video_device vdev;
	काष्ठा mutex video_lock;	/* v4l2 and videobuf2 lock */

	u32 jpeg_mode;
	u32 comp_size_पढ़ो;

	रुको_queue_head_t रुको;
	spinlock_t lock;		/* buffer list lock */
	काष्ठा delayed_work res_work;
	काष्ठा list_head buffers;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक sequence;

	अचिन्हित पूर्णांक max_compressed_size;
	काष्ठा aspeed_video_addr srcs[2];
	काष्ठा aspeed_video_addr jpeg;

	bool yuv420;
	अचिन्हित पूर्णांक frame_rate;
	अचिन्हित पूर्णांक jpeg_quality;

	अचिन्हित पूर्णांक frame_bottom;
	अचिन्हित पूर्णांक frame_left;
	अचिन्हित पूर्णांक frame_right;
	अचिन्हित पूर्णांक frame_top;
पूर्ण;

#घोषणा to_aspeed_video(x) container_of((x), काष्ठा aspeed_video, v4l2_dev)

काष्ठा aspeed_video_config अणु
	u32 jpeg_mode;
	u32 comp_size_पढ़ो;
पूर्ण;

अटल स्थिर काष्ठा aspeed_video_config ast2400_config = अणु
	.jpeg_mode = AST2400_VE_SEQ_CTRL_JPEG_MODE,
	.comp_size_पढ़ो = AST2400_VE_COMP_SIZE_READ_BACK,
पूर्ण;

अटल स्थिर काष्ठा aspeed_video_config ast2500_config = अणु
	.jpeg_mode = AST2500_VE_SEQ_CTRL_JPEG_MODE,
	.comp_size_पढ़ो = AST2400_VE_COMP_SIZE_READ_BACK,
पूर्ण;

अटल स्थिर काष्ठा aspeed_video_config ast2600_config = अणु
	.jpeg_mode = AST2500_VE_SEQ_CTRL_JPEG_MODE,
	.comp_size_पढ़ो = AST2600_VE_COMP_SIZE_READ_BACK,
पूर्ण;

अटल स्थिर u32 aspeed_video_jpeg_header[ASPEED_VIDEO_JPEG_HEADER_SIZE] = अणु
	0xe0ffd8ff, 0x464a1000, 0x01004649, 0x60000101, 0x00006000, 0x0f00feff,
	0x00002d05, 0x00000000, 0x00000000, 0x00dbff00
पूर्ण;

अटल स्थिर u32 aspeed_video_jpeg_quant[ASPEED_VIDEO_JPEG_QUANT_SIZE] = अणु
	0x081100c0, 0x00000000, 0x00110103, 0x03011102, 0xc4ff0111, 0x00001f00,
	0x01010501, 0x01010101, 0x00000000, 0x00000000, 0x04030201, 0x08070605,
	0xff0b0a09, 0x10b500c4, 0x03010200, 0x03040203, 0x04040505, 0x7d010000,
	0x00030201, 0x12051104, 0x06413121, 0x07615113, 0x32147122, 0x08a19181,
	0xc1b14223, 0xf0d15215, 0x72623324, 0x160a0982, 0x1a191817, 0x28272625,
	0x35342a29, 0x39383736, 0x4544433a, 0x49484746, 0x5554534a, 0x59585756,
	0x6564635a, 0x69686766, 0x7574736a, 0x79787776, 0x8584837a, 0x89888786,
	0x9493928a, 0x98979695, 0xa3a29a99, 0xa7a6a5a4, 0xb2aaa9a8, 0xb6b5b4b3,
	0xbab9b8b7, 0xc5c4c3c2, 0xc9c8c7c6, 0xd4d3d2ca, 0xd8d7d6d5, 0xe2e1dad9,
	0xe6e5e4e3, 0xeae9e8e7, 0xf4f3f2f1, 0xf8f7f6f5, 0xc4fffaf9, 0x00011f00,
	0x01010103, 0x01010101, 0x00000101, 0x00000000, 0x04030201, 0x08070605,
	0xff0b0a09, 0x11b500c4, 0x02010200, 0x04030404, 0x04040507, 0x77020100,
	0x03020100, 0x21050411, 0x41120631, 0x71610751, 0x81322213, 0x91421408,
	0x09c1b1a1, 0xf0523323, 0xd1726215, 0x3424160a, 0x17f125e1, 0x261a1918,
	0x2a292827, 0x38373635, 0x44433a39, 0x48474645, 0x54534a49, 0x58575655,
	0x64635a59, 0x68676665, 0x74736a69, 0x78777675, 0x83827a79, 0x87868584,
	0x928a8988, 0x96959493, 0x9a999897, 0xa5a4a3a2, 0xa9a8a7a6, 0xb4b3b2aa,
	0xb8b7b6b5, 0xc3c2bab9, 0xc7c6c5c4, 0xd2cac9c8, 0xd6d5d4d3, 0xdad9d8d7,
	0xe5e4e3e2, 0xe9e8e7e6, 0xf4f3f2ea, 0xf8f7f6f5, 0xdafffaf9, 0x01030c00,
	0x03110200, 0x003f0011
पूर्ण;

अटल स्थिर u32 aspeed_video_jpeg_dct[ASPEED_VIDEO_JPEG_NUM_QUALITIES]
				      [ASPEED_VIDEO_JPEG_DCT_SIZE] = अणु
	अणु 0x0d140043, 0x0c0f110f, 0x11101114, 0x17141516, 0x1e20321e,
	  0x3d1e1b1b, 0x32242e2b, 0x4b4c3f48, 0x44463f47, 0x61735a50,
	  0x566c5550, 0x88644644, 0x7a766c65, 0x4d808280, 0x8c978d60,
	  0x7e73967d, 0xdbff7b80, 0x1f014300, 0x272d2121, 0x3030582d,
	  0x697bb958, 0xb8b9b97b, 0xb9b8a6a6, 0xb9b9b9b9, 0xb9b9b9b9,
	  0xb9b9b9b9, 0xb9b9b9b9, 0xb9b9b9b9, 0xb9b9b9b9, 0xb9b9b9b9,
	  0xb9b9b9b9, 0xb9b9b9b9, 0xb9b9b9b9, 0xffb9b9b9 पूर्ण,
	अणु 0x0c110043, 0x0a0d0f0d, 0x0f0e0f11, 0x14111213, 0x1a1c2b1a,
	  0x351a1818, 0x2b1f2826, 0x4142373f, 0x3c3d373e, 0x55644e46,
	  0x4b5f4a46, 0x77573d3c, 0x6b675f58, 0x43707170, 0x7a847b54,
	  0x6e64836d, 0xdbff6c70, 0x1b014300, 0x22271d1d, 0x2a2a4c27,
	  0x5b6ba04c, 0xa0a0a06b, 0xa0a0a0a0, 0xa0a0a0a0, 0xa0a0a0a0,
	  0xa0a0a0a0, 0xa0a0a0a0, 0xa0a0a0a0, 0xa0a0a0a0, 0xa0a0a0a0,
	  0xa0a0a0a0, 0xa0a0a0a0, 0xa0a0a0a0, 0xffa0a0a0 पूर्ण,
	अणु 0x090e0043, 0x090a0c0a, 0x0c0b0c0e, 0x110e0f10, 0x15172415,
	  0x2c151313, 0x241a211f, 0x36372e34, 0x31322e33, 0x4653413a,
	  0x3e4e3d3a, 0x62483231, 0x58564e49, 0x385d5e5d, 0x656d6645,
	  0x5b536c5a, 0xdbff595d, 0x16014300, 0x1c201818, 0x22223f20,
	  0x4b58853f, 0x85858558, 0x85858585, 0x85858585, 0x85858585,
	  0x85858585, 0x85858585, 0x85858585, 0x85858585, 0x85858585,
	  0x85858585, 0x85858585, 0x85858585, 0xff858585 पूर्ण,
	अणु 0x070b0043, 0x07080a08, 0x0a090a0b, 0x0d0b0c0c, 0x11121c11,
	  0x23110f0f, 0x1c141a19, 0x2b2b2429, 0x27282428, 0x3842332e,
	  0x313e302e, 0x4e392827, 0x46443e3a, 0x2c4a4a4a, 0x50565137,
	  0x48425647, 0xdbff474a, 0x12014300, 0x161a1313, 0x1c1c331a,
	  0x3d486c33, 0x6c6c6c48, 0x6c6c6c6c, 0x6c6c6c6c, 0x6c6c6c6c,
	  0x6c6c6c6c, 0x6c6c6c6c, 0x6c6c6c6c, 0x6c6c6c6c, 0x6c6c6c6c,
	  0x6c6c6c6c, 0x6c6c6c6c, 0x6c6c6c6c, 0xff6c6c6c पूर्ण,
	अणु 0x06090043, 0x05060706, 0x07070709, 0x0a09090a, 0x0d0e160d,
	  0x1b0d0c0c, 0x16101413, 0x21221c20, 0x1e1f1c20, 0x2b332824,
	  0x26302624, 0x3d2d1f1e, 0x3735302d, 0x22393a39, 0x3f443f2b,
	  0x38334338, 0xdbff3739, 0x0d014300, 0x11130e0e, 0x15152613,
	  0x2d355026, 0x50505035, 0x50505050, 0x50505050, 0x50505050,
	  0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050,
	  0x50505050, 0x50505050, 0x50505050, 0xff505050 पूर्ण,
	अणु 0x04060043, 0x03040504, 0x05040506, 0x07060606, 0x09090f09,
	  0x12090808, 0x0f0a0d0d, 0x16161315, 0x14151315, 0x1d221b18,
	  0x19201918, 0x281e1514, 0x2423201e, 0x17262726, 0x2a2d2a1c,
	  0x25222d25, 0xdbff2526, 0x09014300, 0x0b0d0a0a, 0x0e0e1a0d,
	  0x1f25371a, 0x37373725, 0x37373737, 0x37373737, 0x37373737,
	  0x37373737, 0x37373737, 0x37373737, 0x37373737, 0x37373737,
	  0x37373737, 0x37373737, 0x37373737, 0xff373737 पूर्ण,
	अणु 0x02030043, 0x01020202, 0x02020203, 0x03030303, 0x04040704,
	  0x09040404, 0x07050606, 0x0b0b090a, 0x0a0a090a, 0x0e110d0c,
	  0x0c100c0c, 0x140f0a0a, 0x1211100f, 0x0b131313, 0x1516150e,
	  0x12111612, 0xdbff1213, 0x04014300, 0x05060505, 0x07070d06,
	  0x0f121b0d, 0x1b1b1b12, 0x1b1b1b1b, 0x1b1b1b1b, 0x1b1b1b1b,
	  0x1b1b1b1b, 0x1b1b1b1b, 0x1b1b1b1b, 0x1b1b1b1b, 0x1b1b1b1b,
	  0x1b1b1b1b, 0x1b1b1b1b, 0x1b1b1b1b, 0xff1b1b1b पूर्ण,
	अणु 0x01020043, 0x01010101, 0x01010102, 0x02020202, 0x03030503,
	  0x06030202, 0x05030404, 0x07070607, 0x06070607, 0x090b0908,
	  0x080a0808, 0x0d0a0706, 0x0c0b0a0a, 0x070c0d0c, 0x0e0f0e09,
	  0x0c0b0f0c, 0xdbff0c0c, 0x03014300, 0x03040303, 0x04040804,
	  0x0a0c1208, 0x1212120c, 0x12121212, 0x12121212, 0x12121212,
	  0x12121212, 0x12121212, 0x12121212, 0x12121212, 0x12121212,
	  0x12121212, 0x12121212, 0x12121212, 0xff121212 पूर्ण,
	अणु 0x01020043, 0x01010101, 0x01010102, 0x02020202, 0x03030503,
	  0x06030202, 0x05030404, 0x07070607, 0x06070607, 0x090b0908,
	  0x080a0808, 0x0d0a0706, 0x0c0b0a0a, 0x070c0d0c, 0x0e0f0e09,
	  0x0c0b0f0c, 0xdbff0c0c, 0x02014300, 0x03030202, 0x04040703,
	  0x080a0f07, 0x0f0f0f0a, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f,
	  0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f,
	  0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0xff0f0f0f पूर्ण,
	अणु 0x01010043, 0x01010101, 0x01010101, 0x01010101, 0x02020302,
	  0x04020202, 0x03020303, 0x05050405, 0x05050405, 0x07080606,
	  0x06080606, 0x0a070505, 0x09080807, 0x05090909, 0x0a0b0a07,
	  0x09080b09, 0xdbff0909, 0x02014300, 0x02030202, 0x03030503,
	  0x07080c05, 0x0c0c0c08, 0x0c0c0c0c, 0x0c0c0c0c, 0x0c0c0c0c,
	  0x0c0c0c0c, 0x0c0c0c0c, 0x0c0c0c0c, 0x0c0c0c0c, 0x0c0c0c0c,
	  0x0c0c0c0c, 0x0c0c0c0c, 0x0c0c0c0c, 0xff0c0c0c पूर्ण,
	अणु 0x01010043, 0x01010101, 0x01010101, 0x01010101, 0x01010201,
	  0x03010101, 0x02010202, 0x03030303, 0x03030303, 0x04050404,
	  0x04050404, 0x06050303, 0x06050505, 0x03060606, 0x07070704,
	  0x06050706, 0xdbff0606, 0x01014300, 0x01020101, 0x02020402,
	  0x05060904, 0x09090906, 0x09090909, 0x09090909, 0x09090909,
	  0x09090909, 0x09090909, 0x09090909, 0x09090909, 0x09090909,
	  0x09090909, 0x09090909, 0x09090909, 0xff090909 पूर्ण,
	अणु 0x01010043, 0x01010101, 0x01010101, 0x01010101, 0x01010101,
	  0x01010101, 0x01010101, 0x01010101, 0x01010101, 0x02020202,
	  0x02020202, 0x03020101, 0x03020202, 0x01030303, 0x03030302,
	  0x03020303, 0xdbff0403, 0x01014300, 0x01010101, 0x01010201,
	  0x03040602, 0x06060604, 0x06060606, 0x06060606, 0x06060606,
	  0x06060606, 0x06060606, 0x06060606, 0x06060606, 0x06060606,
	  0x06060606, 0x06060606, 0x06060606, 0xff060606 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा v4l2_dv_timings_cap aspeed_video_timings_cap = अणु
	.type = V4L2_DV_BT_656_1120,
	.bt = अणु
		.min_width = MIN_WIDTH,
		.max_width = MAX_WIDTH,
		.min_height = MIN_HEIGHT,
		.max_height = MAX_HEIGHT,
		.min_pixelघड़ी = 6574080, /* 640 x 480 x 24Hz */
		.max_pixelघड़ी = 138240000, /* 1920 x 1200 x 60Hz */
		.standards = V4L2_DV_BT_STD_CEA861 | V4L2_DV_BT_STD_DMT |
			V4L2_DV_BT_STD_CVT | V4L2_DV_BT_STD_GTF,
		.capabilities = V4L2_DV_BT_CAP_PROGRESSIVE |
			V4L2_DV_BT_CAP_REDUCED_BLANKING |
			V4L2_DV_BT_CAP_CUSTOM,
	पूर्ण,
पूर्ण;

अटल व्योम aspeed_video_init_jpeg_table(u32 *table, bool yuv420)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक base;

	क्रम (i = 0; i < ASPEED_VIDEO_JPEG_NUM_QUALITIES; i++) अणु
		base = 256 * i;	/* AST HW requires this header spacing */
		स_नकल(&table[base], aspeed_video_jpeg_header,
		       माप(aspeed_video_jpeg_header));

		base += ASPEED_VIDEO_JPEG_HEADER_SIZE;
		स_नकल(&table[base], aspeed_video_jpeg_dct[i],
		       माप(aspeed_video_jpeg_dct[i]));

		base += ASPEED_VIDEO_JPEG_DCT_SIZE;
		स_नकल(&table[base], aspeed_video_jpeg_quant,
		       माप(aspeed_video_jpeg_quant));

		अगर (yuv420)
			table[base + 2] = 0x00220103;
	पूर्ण
पूर्ण

अटल व्योम aspeed_video_update(काष्ठा aspeed_video *video, u32 reg, u32 clear,
				u32 bits)
अणु
	u32 t = पढ़ोl(video->base + reg);
	u32 beक्रमe = t;

	t &= ~clear;
	t |= bits;
	ग_लिखोl(t, video->base + reg);
	dev_dbg(video->dev, "update %03x[%08x -> %08x]\n", reg, beक्रमe,
		पढ़ोl(video->base + reg));
पूर्ण

अटल u32 aspeed_video_पढ़ो(काष्ठा aspeed_video *video, u32 reg)
अणु
	u32 t = पढ़ोl(video->base + reg);

	dev_dbg(video->dev, "read %03x[%08x]\n", reg, t);
	वापस t;
पूर्ण

अटल व्योम aspeed_video_ग_लिखो(काष्ठा aspeed_video *video, u32 reg, u32 val)
अणु
	ग_लिखोl(val, video->base + reg);
	dev_dbg(video->dev, "write %03x[%08x]\n", reg,
		पढ़ोl(video->base + reg));
पूर्ण

अटल पूर्णांक aspeed_video_start_frame(काष्ठा aspeed_video *video)
अणु
	dma_addr_t addr;
	अचिन्हित दीर्घ flags;
	काष्ठा aspeed_video_buffer *buf;
	u32 seq_ctrl = aspeed_video_पढ़ो(video, VE_SEQ_CTRL);

	अगर (video->v4l2_input_status) अणु
		dev_dbg(video->dev, "No signal; don't start frame\n");
		वापस 0;
	पूर्ण

	अगर (!(seq_ctrl & VE_SEQ_CTRL_COMP_BUSY) ||
	    !(seq_ctrl & VE_SEQ_CTRL_CAP_BUSY)) अणु
		dev_dbg(video->dev, "Engine busy; don't start frame\n");
		वापस -EBUSY;
	पूर्ण

	spin_lock_irqsave(&video->lock, flags);
	buf = list_first_entry_or_null(&video->buffers,
				       काष्ठा aspeed_video_buffer, link);
	अगर (!buf) अणु
		spin_unlock_irqrestore(&video->lock, flags);
		dev_dbg(video->dev, "No buffers; don't start frame\n");
		वापस -EPROTO;
	पूर्ण

	set_bit(VIDEO_FRAME_INPRG, &video->flags);
	addr = vb2_dma_contig_plane_dma_addr(&buf->vb.vb2_buf, 0);
	spin_unlock_irqrestore(&video->lock, flags);

	aspeed_video_ग_लिखो(video, VE_COMP_PROC_OFFSET, 0);
	aspeed_video_ग_लिखो(video, VE_COMP_OFFSET, 0);
	aspeed_video_ग_लिखो(video, VE_COMP_ADDR, addr);

	aspeed_video_update(video, VE_INTERRUPT_CTRL, 0,
			    VE_INTERRUPT_COMP_COMPLETE);

	aspeed_video_update(video, VE_SEQ_CTRL, 0,
			    VE_SEQ_CTRL_TRIG_CAPTURE | VE_SEQ_CTRL_TRIG_COMP);

	वापस 0;
पूर्ण

अटल व्योम aspeed_video_enable_mode_detect(काष्ठा aspeed_video *video)
अणु
	/* Enable mode detect पूर्णांकerrupts */
	aspeed_video_update(video, VE_INTERRUPT_CTRL, 0,
			    VE_INTERRUPT_MODE_DETECT);

	/* Trigger mode detect */
	aspeed_video_update(video, VE_SEQ_CTRL, 0, VE_SEQ_CTRL_TRIG_MODE_DET);
पूर्ण

अटल व्योम aspeed_video_off(काष्ठा aspeed_video *video)
अणु
	अगर (!test_bit(VIDEO_CLOCKS_ON, &video->flags))
		वापस;

	/* Disable पूर्णांकerrupts */
	aspeed_video_ग_लिखो(video, VE_INTERRUPT_CTRL, 0);
	aspeed_video_ग_लिखो(video, VE_INTERRUPT_STATUS, 0xffffffff);

	/* Turn off the relevant घड़ीs */
	clk_disable(video->eclk);
	clk_disable(video->vclk);

	clear_bit(VIDEO_CLOCKS_ON, &video->flags);
पूर्ण

अटल व्योम aspeed_video_on(काष्ठा aspeed_video *video)
अणु
	अगर (test_bit(VIDEO_CLOCKS_ON, &video->flags))
		वापस;

	/* Turn on the relevant घड़ीs */
	clk_enable(video->vclk);
	clk_enable(video->eclk);

	set_bit(VIDEO_CLOCKS_ON, &video->flags);
पूर्ण

अटल व्योम aspeed_video_bufs_करोne(काष्ठा aspeed_video *video,
				   क्रमागत vb2_buffer_state state)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा aspeed_video_buffer *buf;

	spin_lock_irqsave(&video->lock, flags);
	list_क्रम_each_entry(buf, &video->buffers, link)
		vb2_buffer_करोne(&buf->vb.vb2_buf, state);
	INIT_LIST_HEAD(&video->buffers);
	spin_unlock_irqrestore(&video->lock, flags);
पूर्ण

अटल व्योम aspeed_video_irq_res_change(काष्ठा aspeed_video *video, uदीर्घ delay)
अणु
	dev_dbg(video->dev, "Resolution changed; resetting\n");

	set_bit(VIDEO_RES_CHANGE, &video->flags);
	clear_bit(VIDEO_FRAME_INPRG, &video->flags);

	aspeed_video_off(video);
	aspeed_video_bufs_करोne(video, VB2_BUF_STATE_ERROR);

	schedule_delayed_work(&video->res_work, delay);
पूर्ण

अटल irqवापस_t aspeed_video_irq(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा aspeed_video *video = arg;
	u32 sts = aspeed_video_पढ़ो(video, VE_INTERRUPT_STATUS);

	/*
	 * Resolution changed or संकेत was lost; reset the engine and
	 * re-initialize
	 */
	अगर (sts & VE_INTERRUPT_MODE_DETECT_WD) अणु
		aspeed_video_irq_res_change(video, 0);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (sts & VE_INTERRUPT_MODE_DETECT) अणु
		अगर (test_bit(VIDEO_RES_DETECT, &video->flags)) अणु
			aspeed_video_update(video, VE_INTERRUPT_CTRL,
					    VE_INTERRUPT_MODE_DETECT, 0);
			aspeed_video_ग_लिखो(video, VE_INTERRUPT_STATUS,
					   VE_INTERRUPT_MODE_DETECT);
			sts &= ~VE_INTERRUPT_MODE_DETECT;
			set_bit(VIDEO_MODE_DETECT_DONE, &video->flags);
			wake_up_पूर्णांकerruptible_all(&video->रुको);
		पूर्ण अन्यथा अणु
			/*
			 * Signal acquired जबतक NOT करोing resolution
			 * detection; reset the engine and re-initialize
			 */
			aspeed_video_irq_res_change(video,
						    RESOLUTION_CHANGE_DELAY);
			वापस IRQ_HANDLED;
		पूर्ण
	पूर्ण

	अगर (sts & VE_INTERRUPT_COMP_COMPLETE) अणु
		काष्ठा aspeed_video_buffer *buf;
		u32 frame_size = aspeed_video_पढ़ो(video,
						   video->comp_size_पढ़ो);

		spin_lock(&video->lock);
		clear_bit(VIDEO_FRAME_INPRG, &video->flags);
		buf = list_first_entry_or_null(&video->buffers,
					       काष्ठा aspeed_video_buffer,
					       link);
		अगर (buf) अणु
			vb2_set_plane_payload(&buf->vb.vb2_buf, 0, frame_size);

			अगर (!list_is_last(&buf->link, &video->buffers)) अणु
				buf->vb.vb2_buf.बारtamp = kसमय_get_ns();
				buf->vb.sequence = video->sequence++;
				buf->vb.field = V4L2_FIELD_NONE;
				vb2_buffer_करोne(&buf->vb.vb2_buf,
						VB2_BUF_STATE_DONE);
				list_del(&buf->link);
			पूर्ण
		पूर्ण
		spin_unlock(&video->lock);

		aspeed_video_update(video, VE_SEQ_CTRL,
				    VE_SEQ_CTRL_TRIG_CAPTURE |
				    VE_SEQ_CTRL_FORCE_IDLE |
				    VE_SEQ_CTRL_TRIG_COMP, 0);
		aspeed_video_update(video, VE_INTERRUPT_CTRL,
				    VE_INTERRUPT_COMP_COMPLETE, 0);
		aspeed_video_ग_लिखो(video, VE_INTERRUPT_STATUS,
				   VE_INTERRUPT_COMP_COMPLETE);
		sts &= ~VE_INTERRUPT_COMP_COMPLETE;
		अगर (test_bit(VIDEO_STREAMING, &video->flags) && buf)
			aspeed_video_start_frame(video);
	पूर्ण

	/*
	 * CAPTURE_COMPLETE and FRAME_COMPLETE पूर्णांकerrupts come even when these
	 * are disabled in the VE_INTERRUPT_CTRL रेजिस्टर so clear them to
	 * prevent unnecessary पूर्णांकerrupt calls.
	 */
	अगर (sts & VE_INTERRUPT_CAPTURE_COMPLETE)
		sts &= ~VE_INTERRUPT_CAPTURE_COMPLETE;
	अगर (sts & VE_INTERRUPT_FRAME_COMPLETE)
		sts &= ~VE_INTERRUPT_FRAME_COMPLETE;

	वापस sts ? IRQ_NONE : IRQ_HANDLED;
पूर्ण

अटल व्योम aspeed_video_check_and_set_polarity(काष्ठा aspeed_video *video)
अणु
	पूर्णांक i;
	पूर्णांक hsync_counter = 0;
	पूर्णांक vsync_counter = 0;
	u32 sts, ctrl;

	क्रम (i = 0; i < NUM_POLARITY_CHECKS; ++i) अणु
		sts = aspeed_video_पढ़ो(video, VE_MODE_DETECT_STATUS);
		अगर (sts & VE_MODE_DETECT_STATUS_VSYNC)
			vsync_counter--;
		अन्यथा
			vsync_counter++;

		अगर (sts & VE_MODE_DETECT_STATUS_HSYNC)
			hsync_counter--;
		अन्यथा
			hsync_counter++;
	पूर्ण

	ctrl = aspeed_video_पढ़ो(video, VE_CTRL);

	अगर (hsync_counter < 0) अणु
		ctrl |= VE_CTRL_HSYNC_POL;
		video->detected_timings.polarities &=
			~V4L2_DV_HSYNC_POS_POL;
	पूर्ण अन्यथा अणु
		ctrl &= ~VE_CTRL_HSYNC_POL;
		video->detected_timings.polarities |=
			V4L2_DV_HSYNC_POS_POL;
	पूर्ण

	अगर (vsync_counter < 0) अणु
		ctrl |= VE_CTRL_VSYNC_POL;
		video->detected_timings.polarities &=
			~V4L2_DV_VSYNC_POS_POL;
	पूर्ण अन्यथा अणु
		ctrl &= ~VE_CTRL_VSYNC_POL;
		video->detected_timings.polarities |=
			V4L2_DV_VSYNC_POS_POL;
	पूर्ण

	aspeed_video_ग_लिखो(video, VE_CTRL, ctrl);
पूर्ण

अटल bool aspeed_video_alloc_buf(काष्ठा aspeed_video *video,
				   काष्ठा aspeed_video_addr *addr,
				   अचिन्हित पूर्णांक size)
अणु
	addr->virt = dma_alloc_coherent(video->dev, size, &addr->dma,
					GFP_KERNEL);
	अगर (!addr->virt)
		वापस false;

	addr->size = size;
	वापस true;
पूर्ण

अटल व्योम aspeed_video_मुक्त_buf(काष्ठा aspeed_video *video,
				  काष्ठा aspeed_video_addr *addr)
अणु
	dma_मुक्त_coherent(video->dev, addr->size, addr->virt, addr->dma);
	addr->size = 0;
	addr->dma = 0ULL;
	addr->virt = शून्य;
पूर्ण

/*
 * Get the minimum HW-supported compression buffer size क्रम the frame size.
 * Assume worst-हाल JPEG compression size is 1/8 raw size. This should be
 * plenty even क्रम maximum quality; any worse and the engine will simply वापस
 * incomplete JPEGs.
 */
अटल व्योम aspeed_video_calc_compressed_size(काष्ठा aspeed_video *video,
					      अचिन्हित पूर्णांक frame_size)
अणु
	पूर्णांक i, j;
	u32 compression_buffer_size_reg = 0;
	अचिन्हित पूर्णांक size;
	स्थिर अचिन्हित पूर्णांक num_compression_packets = 4;
	स्थिर अचिन्हित पूर्णांक compression_packet_size = 1024;
	स्थिर अचिन्हित पूर्णांक max_compressed_size = frame_size / 2; /* 4bpp / 8 */

	video->max_compressed_size = अच_पूर्णांक_उच्च;

	क्रम (i = 0; i < 6; ++i) अणु
		क्रम (j = 0; j < 8; ++j) अणु
			size = (num_compression_packets << i) *
				(compression_packet_size << j);
			अगर (size < max_compressed_size)
				जारी;

			अगर (size < video->max_compressed_size) अणु
				compression_buffer_size_reg = (i << 3) | j;
				video->max_compressed_size = size;
			पूर्ण
		पूर्ण
	पूर्ण

	aspeed_video_ग_लिखो(video, VE_STREAM_BUF_SIZE,
			   compression_buffer_size_reg);

	dev_dbg(video->dev, "Max compressed size: %x\n",
		video->max_compressed_size);
पूर्ण

#घोषणा res_check(v) test_and_clear_bit(VIDEO_MODE_DETECT_DONE, &(v)->flags)

अटल व्योम aspeed_video_get_resolution(काष्ठा aspeed_video *video)
अणु
	bool invalid_resolution = true;
	पूर्णांक rc;
	पूर्णांक tries = 0;
	u32 mds;
	u32 src_lr_edge;
	u32 src_tb_edge;
	u32 sync;
	काष्ठा v4l2_bt_timings *det = &video->detected_timings;

	det->width = MIN_WIDTH;
	det->height = MIN_HEIGHT;
	video->v4l2_input_status = V4L2_IN_ST_NO_SIGNAL;

	करो अणु
		अगर (tries) अणु
			set_current_state(TASK_INTERRUPTIBLE);
			अगर (schedule_समयout(INVALID_RESOLUTION_DELAY))
				वापस;
		पूर्ण

		set_bit(VIDEO_RES_DETECT, &video->flags);
		aspeed_video_update(video, VE_CTRL,
				    VE_CTRL_VSYNC_POL | VE_CTRL_HSYNC_POL, 0);
		aspeed_video_enable_mode_detect(video);

		rc = रुको_event_पूर्णांकerruptible_समयout(video->रुको,
						      res_check(video),
						      MODE_DETECT_TIMEOUT);
		अगर (!rc) अणु
			dev_dbg(video->dev, "Timed out; first mode detect\n");
			clear_bit(VIDEO_RES_DETECT, &video->flags);
			वापस;
		पूर्ण

		/* Disable mode detect in order to re-trigger */
		aspeed_video_update(video, VE_SEQ_CTRL,
				    VE_SEQ_CTRL_TRIG_MODE_DET, 0);

		aspeed_video_check_and_set_polarity(video);

		aspeed_video_enable_mode_detect(video);

		rc = रुको_event_पूर्णांकerruptible_समयout(video->रुको,
						      res_check(video),
						      MODE_DETECT_TIMEOUT);
		clear_bit(VIDEO_RES_DETECT, &video->flags);
		अगर (!rc) अणु
			dev_dbg(video->dev, "Timed out; second mode detect\n");
			वापस;
		पूर्ण

		src_lr_edge = aspeed_video_पढ़ो(video, VE_SRC_LR_EDGE_DET);
		src_tb_edge = aspeed_video_पढ़ो(video, VE_SRC_TB_EDGE_DET);
		mds = aspeed_video_पढ़ो(video, VE_MODE_DETECT_STATUS);
		sync = aspeed_video_पढ़ो(video, VE_SYNC_STATUS);

		video->frame_bottom = (src_tb_edge & VE_SRC_TB_EDGE_DET_BOT) >>
			VE_SRC_TB_EDGE_DET_BOT_SHF;
		video->frame_top = src_tb_edge & VE_SRC_TB_EDGE_DET_TOP;
		det->vfrontporch = video->frame_top;
		det->vbackporch = ((mds & VE_MODE_DETECT_V_LINES) >>
			VE_MODE_DETECT_V_LINES_SHF) - video->frame_bottom;
		det->vsync = (sync & VE_SYNC_STATUS_VSYNC) >>
			VE_SYNC_STATUS_VSYNC_SHF;
		अगर (video->frame_top > video->frame_bottom)
			जारी;

		video->frame_right = (src_lr_edge & VE_SRC_LR_EDGE_DET_RT) >>
			VE_SRC_LR_EDGE_DET_RT_SHF;
		video->frame_left = src_lr_edge & VE_SRC_LR_EDGE_DET_LEFT;
		det->hfrontporch = video->frame_left;
		det->hbackporch = (mds & VE_MODE_DETECT_H_PIXELS) -
			video->frame_right;
		det->hsync = sync & VE_SYNC_STATUS_HSYNC;
		अगर (video->frame_left > video->frame_right)
			जारी;

		invalid_resolution = false;
	पूर्ण जबतक (invalid_resolution && (tries++ < INVALID_RESOLUTION_RETRIES));

	अगर (invalid_resolution) अणु
		dev_dbg(video->dev, "Invalid resolution detected\n");
		वापस;
	पूर्ण

	det->height = (video->frame_bottom - video->frame_top) + 1;
	det->width = (video->frame_right - video->frame_left) + 1;
	video->v4l2_input_status = 0;

	/*
	 * Enable mode-detect watchकरोg, resolution-change watchकरोg and
	 * स्वतःmatic compression after frame capture.
	 */
	aspeed_video_update(video, VE_INTERRUPT_CTRL, 0,
			    VE_INTERRUPT_MODE_DETECT_WD);
	aspeed_video_update(video, VE_SEQ_CTRL, 0,
			    VE_SEQ_CTRL_AUTO_COMP | VE_SEQ_CTRL_EN_WATCHDOG);

	dev_dbg(video->dev, "Got resolution: %dx%d\n", det->width,
		det->height);
पूर्ण

अटल व्योम aspeed_video_set_resolution(काष्ठा aspeed_video *video)
अणु
	काष्ठा v4l2_bt_timings *act = &video->active_timings;
	अचिन्हित पूर्णांक size = act->width * act->height;

	/* Set capture/compression frame sizes */
	aspeed_video_calc_compressed_size(video, size);

	अगर (video->active_timings.width == 1680) अणु
		/*
		 * This is a workaround to fix a silicon bug on A1 and A2
		 * revisions. Since it करोesn't अवरोध capturing operation of
		 * other revisions, use it क्रम all revisions without checking
		 * the revision ID. It picked 1728 which is a very next
		 * 64-pixels aligned value to 1680 to minimize memory bandwidth
		 * and to get better access speed from video engine.
		 */
		aspeed_video_ग_लिखो(video, VE_CAP_WINDOW,
				   1728 << 16 | act->height);
		size += (1728 - 1680) * video->active_timings.height;
	पूर्ण अन्यथा अणु
		aspeed_video_ग_लिखो(video, VE_CAP_WINDOW,
				   act->width << 16 | act->height);
	पूर्ण
	aspeed_video_ग_लिखो(video, VE_COMP_WINDOW,
			   act->width << 16 | act->height);
	aspeed_video_ग_लिखो(video, VE_SRC_SCANLINE_OFFSET, act->width * 4);

	/* Don't use direct mode below 1024 x 768 (irqs don't fire) */
	अगर (size < सूचीECT_FETCH_THRESHOLD) अणु
		aspeed_video_ग_लिखो(video, VE_TGS_0,
				   FIELD_PREP(VE_TGS_FIRST,
					      video->frame_left - 1) |
				   FIELD_PREP(VE_TGS_LAST,
					      video->frame_right));
		aspeed_video_ग_लिखो(video, VE_TGS_1,
				   FIELD_PREP(VE_TGS_FIRST, video->frame_top) |
				   FIELD_PREP(VE_TGS_LAST,
					      video->frame_bottom + 1));
		aspeed_video_update(video, VE_CTRL, 0, VE_CTRL_INT_DE);
	पूर्ण अन्यथा अणु
		aspeed_video_update(video, VE_CTRL, 0, VE_CTRL_सूचीECT_FETCH);
	पूर्ण

	size *= 4;

	अगर (size != video->srcs[0].size) अणु
		अगर (video->srcs[0].size)
			aspeed_video_मुक्त_buf(video, &video->srcs[0]);
		अगर (video->srcs[1].size)
			aspeed_video_मुक्त_buf(video, &video->srcs[1]);

		अगर (!aspeed_video_alloc_buf(video, &video->srcs[0], size))
			जाओ err_mem;
		अगर (!aspeed_video_alloc_buf(video, &video->srcs[1], size))
			जाओ err_mem;

		aspeed_video_ग_लिखो(video, VE_SRC0_ADDR, video->srcs[0].dma);
		aspeed_video_ग_लिखो(video, VE_SRC1_ADDR, video->srcs[1].dma);
	पूर्ण

	वापस;

err_mem:
	dev_err(video->dev, "Failed to allocate source buffers\n");

	अगर (video->srcs[0].size)
		aspeed_video_मुक्त_buf(video, &video->srcs[0]);
पूर्ण

अटल व्योम aspeed_video_init_regs(काष्ठा aspeed_video *video)
अणु
	u32 comp_ctrl = VE_COMP_CTRL_RSVD |
		FIELD_PREP(VE_COMP_CTRL_DCT_LUM, video->jpeg_quality) |
		FIELD_PREP(VE_COMP_CTRL_DCT_CHR, video->jpeg_quality | 0x10);
	u32 ctrl = VE_CTRL_AUTO_OR_CURSOR;
	u32 seq_ctrl = video->jpeg_mode;

	अगर (video->frame_rate)
		ctrl |= FIELD_PREP(VE_CTRL_FRC, video->frame_rate);

	अगर (video->yuv420)
		seq_ctrl |= VE_SEQ_CTRL_YUV420;

	/* Unlock VE रेजिस्टरs */
	aspeed_video_ग_लिखो(video, VE_PROTECTION_KEY, VE_PROTECTION_KEY_UNLOCK);

	/* Disable पूर्णांकerrupts */
	aspeed_video_ग_लिखो(video, VE_INTERRUPT_CTRL, 0);
	aspeed_video_ग_लिखो(video, VE_INTERRUPT_STATUS, 0xffffffff);

	/* Clear the offset */
	aspeed_video_ग_लिखो(video, VE_COMP_PROC_OFFSET, 0);
	aspeed_video_ग_लिखो(video, VE_COMP_OFFSET, 0);

	aspeed_video_ग_लिखो(video, VE_JPEG_ADDR, video->jpeg.dma);

	/* Set control रेजिस्टरs */
	aspeed_video_ग_लिखो(video, VE_SEQ_CTRL, seq_ctrl);
	aspeed_video_ग_लिखो(video, VE_CTRL, ctrl);
	aspeed_video_ग_लिखो(video, VE_COMP_CTRL, comp_ctrl);

	/* Don't करोwnscale */
	aspeed_video_ग_लिखो(video, VE_SCALING_FACTOR, 0x10001000);
	aspeed_video_ग_लिखो(video, VE_SCALING_FILTER0, 0x00200000);
	aspeed_video_ग_लिखो(video, VE_SCALING_FILTER1, 0x00200000);
	aspeed_video_ग_लिखो(video, VE_SCALING_FILTER2, 0x00200000);
	aspeed_video_ग_लिखो(video, VE_SCALING_FILTER3, 0x00200000);

	/* Set mode detection शेषs */
	aspeed_video_ग_लिखो(video, VE_MODE_DETECT, 0x22666500);
पूर्ण

अटल व्योम aspeed_video_start(काष्ठा aspeed_video *video)
अणु
	aspeed_video_on(video);

	aspeed_video_init_regs(video);

	/* Resolution set to 640x480 अगर no संकेत found */
	aspeed_video_get_resolution(video);

	/* Set timings since the device is being खोलोed क्रम the first समय */
	video->active_timings = video->detected_timings;
	aspeed_video_set_resolution(video);

	video->pix_fmt.width = video->active_timings.width;
	video->pix_fmt.height = video->active_timings.height;
	video->pix_fmt.sizeimage = video->max_compressed_size;
पूर्ण

अटल व्योम aspeed_video_stop(काष्ठा aspeed_video *video)
अणु
	set_bit(VIDEO_STOPPED, &video->flags);
	cancel_delayed_work_sync(&video->res_work);

	aspeed_video_off(video);

	अगर (video->srcs[0].size)
		aspeed_video_मुक्त_buf(video, &video->srcs[0]);

	अगर (video->srcs[1].size)
		aspeed_video_मुक्त_buf(video, &video->srcs[1]);

	video->v4l2_input_status = V4L2_IN_ST_NO_SIGNAL;
	video->flags = 0;
पूर्ण

अटल पूर्णांक aspeed_video_querycap(काष्ठा file *file, व्योम *fh,
				 काष्ठा v4l2_capability *cap)
अणु
	strscpy(cap->driver, DEVICE_NAME, माप(cap->driver));
	strscpy(cap->card, "Aspeed Video Engine", माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "platform:%s",
		 DEVICE_NAME);

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_video_क्रमागत_क्रमmat(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index)
		वापस -EINVAL;

	f->pixelक्रमmat = V4L2_PIX_FMT_JPEG;

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_video_get_क्रमmat(काष्ठा file *file, व्योम *fh,
				   काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा aspeed_video *video = video_drvdata(file);

	f->fmt.pix = video->pix_fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_video_क्रमागत_input(काष्ठा file *file, व्योम *fh,
				   काष्ठा v4l2_input *inp)
अणु
	काष्ठा aspeed_video *video = video_drvdata(file);

	अगर (inp->index)
		वापस -EINVAL;

	strscpy(inp->name, "Host VGA capture", माप(inp->name));
	inp->type = V4L2_INPUT_TYPE_CAMERA;
	inp->capabilities = V4L2_IN_CAP_DV_TIMINGS;
	inp->status = video->v4l2_input_status;

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_video_get_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक *i)
अणु
	*i = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_video_set_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक i)
अणु
	अगर (i)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_video_get_parm(काष्ठा file *file, व्योम *fh,
				 काष्ठा v4l2_streamparm *a)
अणु
	काष्ठा aspeed_video *video = video_drvdata(file);

	a->parm.capture.capability = V4L2_CAP_TIMEPERFRAME;
	a->parm.capture.पढ़ोbuffers = 3;
	a->parm.capture.समयperframe.numerator = 1;
	अगर (!video->frame_rate)
		a->parm.capture.समयperframe.denominator = MAX_FRAME_RATE;
	अन्यथा
		a->parm.capture.समयperframe.denominator = video->frame_rate;

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_video_set_parm(काष्ठा file *file, व्योम *fh,
				 काष्ठा v4l2_streamparm *a)
अणु
	अचिन्हित पूर्णांक frame_rate = 0;
	काष्ठा aspeed_video *video = video_drvdata(file);

	a->parm.capture.capability = V4L2_CAP_TIMEPERFRAME;
	a->parm.capture.पढ़ोbuffers = 3;

	अगर (a->parm.capture.समयperframe.numerator)
		frame_rate = a->parm.capture.समयperframe.denominator /
			a->parm.capture.समयperframe.numerator;

	अगर (!frame_rate || frame_rate > MAX_FRAME_RATE) अणु
		frame_rate = 0;
		a->parm.capture.समयperframe.denominator = MAX_FRAME_RATE;
		a->parm.capture.समयperframe.numerator = 1;
	पूर्ण

	अगर (video->frame_rate != frame_rate) अणु
		video->frame_rate = frame_rate;
		aspeed_video_update(video, VE_CTRL, VE_CTRL_FRC,
				    FIELD_PREP(VE_CTRL_FRC, frame_rate));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_video_क्रमागत_framesizes(काष्ठा file *file, व्योम *fh,
					काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	काष्ठा aspeed_video *video = video_drvdata(file);

	अगर (fsize->index)
		वापस -EINVAL;

	अगर (fsize->pixel_क्रमmat != V4L2_PIX_FMT_JPEG)
		वापस -EINVAL;

	fsize->discrete.width = video->pix_fmt.width;
	fsize->discrete.height = video->pix_fmt.height;
	fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_video_क्रमागत_frameपूर्णांकervals(काष्ठा file *file, व्योम *fh,
					    काष्ठा v4l2_frmivalक्रमागत *fival)
अणु
	काष्ठा aspeed_video *video = video_drvdata(file);

	अगर (fival->index)
		वापस -EINVAL;

	अगर (fival->width != video->detected_timings.width ||
	    fival->height != video->detected_timings.height)
		वापस -EINVAL;

	अगर (fival->pixel_क्रमmat != V4L2_PIX_FMT_JPEG)
		वापस -EINVAL;

	fival->type = V4L2_FRMIVAL_TYPE_CONTINUOUS;

	fival->stepwise.min.denominator = MAX_FRAME_RATE;
	fival->stepwise.min.numerator = 1;
	fival->stepwise.max.denominator = 1;
	fival->stepwise.max.numerator = 1;
	fival->stepwise.step = fival->stepwise.max;

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_video_set_dv_timings(काष्ठा file *file, व्योम *fh,
				       काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा aspeed_video *video = video_drvdata(file);

	अगर (timings->bt.width == video->active_timings.width &&
	    timings->bt.height == video->active_timings.height)
		वापस 0;

	अगर (vb2_is_busy(&video->queue))
		वापस -EBUSY;

	video->active_timings = timings->bt;

	aspeed_video_set_resolution(video);

	video->pix_fmt.width = timings->bt.width;
	video->pix_fmt.height = timings->bt.height;
	video->pix_fmt.sizeimage = video->max_compressed_size;

	timings->type = V4L2_DV_BT_656_1120;

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_video_get_dv_timings(काष्ठा file *file, व्योम *fh,
				       काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा aspeed_video *video = video_drvdata(file);

	timings->type = V4L2_DV_BT_656_1120;
	timings->bt = video->active_timings;

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_video_query_dv_timings(काष्ठा file *file, व्योम *fh,
					 काष्ठा v4l2_dv_timings *timings)
अणु
	पूर्णांक rc;
	काष्ठा aspeed_video *video = video_drvdata(file);

	/*
	 * This blocks only अगर the driver is currently in the process of
	 * detecting a new resolution; in the event of no संकेत or समयout
	 * this function is woken up.
	 */
	अगर (file->f_flags & O_NONBLOCK) अणु
		अगर (test_bit(VIDEO_RES_CHANGE, &video->flags))
			वापस -EAGAIN;
	पूर्ण अन्यथा अणु
		rc = रुको_event_पूर्णांकerruptible(video->रुको,
					      !test_bit(VIDEO_RES_CHANGE,
							&video->flags));
		अगर (rc)
			वापस -EINTR;
	पूर्ण

	timings->type = V4L2_DV_BT_656_1120;
	timings->bt = video->detected_timings;

	वापस video->v4l2_input_status ? -ENOLINK : 0;
पूर्ण

अटल पूर्णांक aspeed_video_क्रमागत_dv_timings(काष्ठा file *file, व्योम *fh,
					काष्ठा v4l2_क्रमागत_dv_timings *timings)
अणु
	वापस v4l2_क्रमागत_dv_timings_cap(timings, &aspeed_video_timings_cap,
					शून्य, शून्य);
पूर्ण

अटल पूर्णांक aspeed_video_dv_timings_cap(काष्ठा file *file, व्योम *fh,
				       काष्ठा v4l2_dv_timings_cap *cap)
अणु
	*cap = aspeed_video_timings_cap;

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_video_sub_event(काष्ठा v4l2_fh *fh,
				  स्थिर काष्ठा v4l2_event_subscription *sub)
अणु
	चयन (sub->type) अणु
	हाल V4L2_EVENT_SOURCE_CHANGE:
		वापस v4l2_src_change_event_subscribe(fh, sub);
	पूर्ण

	वापस v4l2_ctrl_subscribe_event(fh, sub);
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops aspeed_video_ioctl_ops = अणु
	.vidioc_querycap = aspeed_video_querycap,

	.vidioc_क्रमागत_fmt_vid_cap = aspeed_video_क्रमागत_क्रमmat,
	.vidioc_g_fmt_vid_cap = aspeed_video_get_क्रमmat,
	.vidioc_s_fmt_vid_cap = aspeed_video_get_क्रमmat,
	.vidioc_try_fmt_vid_cap = aspeed_video_get_क्रमmat,

	.vidioc_reqbufs = vb2_ioctl_reqbufs,
	.vidioc_querybuf = vb2_ioctl_querybuf,
	.vidioc_qbuf = vb2_ioctl_qbuf,
	.vidioc_expbuf = vb2_ioctl_expbuf,
	.vidioc_dqbuf = vb2_ioctl_dqbuf,
	.vidioc_create_bufs = vb2_ioctl_create_bufs,
	.vidioc_prepare_buf = vb2_ioctl_prepare_buf,
	.vidioc_streamon = vb2_ioctl_streamon,
	.vidioc_streamoff = vb2_ioctl_streamoff,

	.vidioc_क्रमागत_input = aspeed_video_क्रमागत_input,
	.vidioc_g_input = aspeed_video_get_input,
	.vidioc_s_input = aspeed_video_set_input,

	.vidioc_g_parm = aspeed_video_get_parm,
	.vidioc_s_parm = aspeed_video_set_parm,
	.vidioc_क्रमागत_framesizes = aspeed_video_क्रमागत_framesizes,
	.vidioc_क्रमागत_frameपूर्णांकervals = aspeed_video_क्रमागत_frameपूर्णांकervals,

	.vidioc_s_dv_timings = aspeed_video_set_dv_timings,
	.vidioc_g_dv_timings = aspeed_video_get_dv_timings,
	.vidioc_query_dv_timings = aspeed_video_query_dv_timings,
	.vidioc_क्रमागत_dv_timings = aspeed_video_क्रमागत_dv_timings,
	.vidioc_dv_timings_cap = aspeed_video_dv_timings_cap,

	.vidioc_subscribe_event = aspeed_video_sub_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल व्योम aspeed_video_update_jpeg_quality(काष्ठा aspeed_video *video)
अणु
	u32 comp_ctrl = FIELD_PREP(VE_COMP_CTRL_DCT_LUM, video->jpeg_quality) |
		FIELD_PREP(VE_COMP_CTRL_DCT_CHR, video->jpeg_quality | 0x10);

	aspeed_video_update(video, VE_COMP_CTRL,
			    VE_COMP_CTRL_DCT_LUM | VE_COMP_CTRL_DCT_CHR,
			    comp_ctrl);
पूर्ण

अटल व्योम aspeed_video_update_subsampling(काष्ठा aspeed_video *video)
अणु
	अगर (video->jpeg.virt)
		aspeed_video_init_jpeg_table(video->jpeg.virt, video->yuv420);

	अगर (video->yuv420)
		aspeed_video_update(video, VE_SEQ_CTRL, 0, VE_SEQ_CTRL_YUV420);
	अन्यथा
		aspeed_video_update(video, VE_SEQ_CTRL, VE_SEQ_CTRL_YUV420, 0);
पूर्ण

अटल पूर्णांक aspeed_video_set_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा aspeed_video *video = container_of(ctrl->handler,
						  काष्ठा aspeed_video,
						  ctrl_handler);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_JPEG_COMPRESSION_QUALITY:
		video->jpeg_quality = ctrl->val;
		aspeed_video_update_jpeg_quality(video);
		अवरोध;
	हाल V4L2_CID_JPEG_CHROMA_SUBSAMPLING:
		अगर (ctrl->val == V4L2_JPEG_CHROMA_SUBSAMPLING_420) अणु
			video->yuv420 = true;
			aspeed_video_update_subsampling(video);
		पूर्ण अन्यथा अणु
			video->yuv420 = false;
			aspeed_video_update_subsampling(video);
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops aspeed_video_ctrl_ops = अणु
	.s_ctrl = aspeed_video_set_ctrl,
पूर्ण;

अटल व्योम aspeed_video_resolution_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा aspeed_video *video = container_of(dwork, काष्ठा aspeed_video,
						  res_work);
	u32 input_status = video->v4l2_input_status;

	aspeed_video_on(video);

	/* Exit early in हाल no clients reमुख्य */
	अगर (test_bit(VIDEO_STOPPED, &video->flags))
		जाओ करोne;

	aspeed_video_init_regs(video);

	aspeed_video_get_resolution(video);

	अगर (video->detected_timings.width != video->active_timings.width ||
	    video->detected_timings.height != video->active_timings.height ||
	    input_status != video->v4l2_input_status) अणु
		अटल स्थिर काष्ठा v4l2_event ev = अणु
			.type = V4L2_EVENT_SOURCE_CHANGE,
			.u.src_change.changes = V4L2_EVENT_SRC_CH_RESOLUTION,
		पूर्ण;

		v4l2_event_queue(&video->vdev, &ev);
	पूर्ण अन्यथा अगर (test_bit(VIDEO_STREAMING, &video->flags)) अणु
		/* No resolution change so just restart streaming */
		aspeed_video_start_frame(video);
	पूर्ण

करोne:
	clear_bit(VIDEO_RES_CHANGE, &video->flags);
	wake_up_पूर्णांकerruptible_all(&video->रुको);
पूर्ण

अटल पूर्णांक aspeed_video_खोलो(काष्ठा file *file)
अणु
	पूर्णांक rc;
	काष्ठा aspeed_video *video = video_drvdata(file);

	mutex_lock(&video->video_lock);

	rc = v4l2_fh_खोलो(file);
	अगर (rc) अणु
		mutex_unlock(&video->video_lock);
		वापस rc;
	पूर्ण

	अगर (v4l2_fh_is_singular_file(file))
		aspeed_video_start(video);

	mutex_unlock(&video->video_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_video_release(काष्ठा file *file)
अणु
	पूर्णांक rc;
	काष्ठा aspeed_video *video = video_drvdata(file);

	mutex_lock(&video->video_lock);

	अगर (v4l2_fh_is_singular_file(file))
		aspeed_video_stop(video);

	rc = _vb2_fop_release(file, शून्य);

	mutex_unlock(&video->video_lock);

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations aspeed_video_v4l2_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = vb2_fop_पढ़ो,
	.poll = vb2_fop_poll,
	.unlocked_ioctl = video_ioctl2,
	.mmap = vb2_fop_mmap,
	.खोलो = aspeed_video_खोलो,
	.release = aspeed_video_release,
पूर्ण;

अटल पूर्णांक aspeed_video_queue_setup(काष्ठा vb2_queue *q,
				    अचिन्हित पूर्णांक *num_buffers,
				    अचिन्हित पूर्णांक *num_planes,
				    अचिन्हित पूर्णांक sizes[],
				    काष्ठा device *alloc_devs[])
अणु
	काष्ठा aspeed_video *video = vb2_get_drv_priv(q);

	अगर (*num_planes) अणु
		अगर (sizes[0] < video->max_compressed_size)
			वापस -EINVAL;

		वापस 0;
	पूर्ण

	*num_planes = 1;
	sizes[0] = video->max_compressed_size;

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_video_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा aspeed_video *video = vb2_get_drv_priv(vb->vb2_queue);

	अगर (vb2_plane_size(vb, 0) < video->max_compressed_size)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_video_start_streaming(काष्ठा vb2_queue *q,
					अचिन्हित पूर्णांक count)
अणु
	पूर्णांक rc;
	काष्ठा aspeed_video *video = vb2_get_drv_priv(q);

	video->sequence = 0;

	rc = aspeed_video_start_frame(video);
	अगर (rc) अणु
		aspeed_video_bufs_करोne(video, VB2_BUF_STATE_QUEUED);
		वापस rc;
	पूर्ण

	set_bit(VIDEO_STREAMING, &video->flags);
	वापस 0;
पूर्ण

अटल व्योम aspeed_video_stop_streaming(काष्ठा vb2_queue *q)
अणु
	पूर्णांक rc;
	काष्ठा aspeed_video *video = vb2_get_drv_priv(q);

	clear_bit(VIDEO_STREAMING, &video->flags);

	rc = रुको_event_समयout(video->रुको,
				!test_bit(VIDEO_FRAME_INPRG, &video->flags),
				STOP_TIMEOUT);
	अगर (!rc) अणु
		dev_dbg(video->dev, "Timed out when stopping streaming\n");

		/*
		 * Need to क्रमce stop any DMA and try and get HW पूर्णांकo a good
		 * state क्रम future calls to start streaming again.
		 */
		aspeed_video_off(video);
		aspeed_video_on(video);

		aspeed_video_init_regs(video);

		aspeed_video_get_resolution(video);
	पूर्ण

	aspeed_video_bufs_करोne(video, VB2_BUF_STATE_ERROR);
पूर्ण

अटल व्योम aspeed_video_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	bool empty;
	काष्ठा aspeed_video *video = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा aspeed_video_buffer *avb = to_aspeed_video_buffer(vbuf);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&video->lock, flags);
	empty = list_empty(&video->buffers);
	list_add_tail(&avb->link, &video->buffers);
	spin_unlock_irqrestore(&video->lock, flags);

	अगर (test_bit(VIDEO_STREAMING, &video->flags) &&
	    !test_bit(VIDEO_FRAME_INPRG, &video->flags) && empty)
		aspeed_video_start_frame(video);
पूर्ण

अटल स्थिर काष्ठा vb2_ops aspeed_video_vb2_ops = अणु
	.queue_setup = aspeed_video_queue_setup,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
	.buf_prepare = aspeed_video_buf_prepare,
	.start_streaming = aspeed_video_start_streaming,
	.stop_streaming = aspeed_video_stop_streaming,
	.buf_queue =  aspeed_video_buf_queue,
पूर्ण;

अटल पूर्णांक aspeed_video_setup_video(काष्ठा aspeed_video *video)
अणु
	स्थिर u64 mask = ~(BIT(V4L2_JPEG_CHROMA_SUBSAMPLING_444) |
			   BIT(V4L2_JPEG_CHROMA_SUBSAMPLING_420));
	काष्ठा v4l2_device *v4l2_dev = &video->v4l2_dev;
	काष्ठा vb2_queue *vbq = &video->queue;
	काष्ठा video_device *vdev = &video->vdev;
	पूर्णांक rc;

	video->pix_fmt.pixelक्रमmat = V4L2_PIX_FMT_JPEG;
	video->pix_fmt.field = V4L2_FIELD_NONE;
	video->pix_fmt.colorspace = V4L2_COLORSPACE_SRGB;
	video->pix_fmt.quantization = V4L2_QUANTIZATION_FULL_RANGE;
	video->v4l2_input_status = V4L2_IN_ST_NO_SIGNAL;

	rc = v4l2_device_रेजिस्टर(video->dev, v4l2_dev);
	अगर (rc) अणु
		dev_err(video->dev, "Failed to register v4l2 device\n");
		वापस rc;
	पूर्ण

	v4l2_ctrl_handler_init(&video->ctrl_handler, 2);
	v4l2_ctrl_new_std(&video->ctrl_handler, &aspeed_video_ctrl_ops,
			  V4L2_CID_JPEG_COMPRESSION_QUALITY, 0,
			  ASPEED_VIDEO_JPEG_NUM_QUALITIES - 1, 1, 0);
	v4l2_ctrl_new_std_menu(&video->ctrl_handler, &aspeed_video_ctrl_ops,
			       V4L2_CID_JPEG_CHROMA_SUBSAMPLING,
			       V4L2_JPEG_CHROMA_SUBSAMPLING_420, mask,
			       V4L2_JPEG_CHROMA_SUBSAMPLING_444);

	rc = video->ctrl_handler.error;
	अगर (rc) अणु
		v4l2_ctrl_handler_मुक्त(&video->ctrl_handler);
		v4l2_device_unरेजिस्टर(v4l2_dev);

		dev_err(video->dev, "Failed to init controls: %d\n", rc);
		वापस rc;
	पूर्ण

	v4l2_dev->ctrl_handler = &video->ctrl_handler;

	vbq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	vbq->io_modes = VB2_MMAP | VB2_READ | VB2_DMABUF;
	vbq->dev = v4l2_dev->dev;
	vbq->lock = &video->video_lock;
	vbq->ops = &aspeed_video_vb2_ops;
	vbq->mem_ops = &vb2_dma_contig_memops;
	vbq->drv_priv = video;
	vbq->buf_काष्ठा_size = माप(काष्ठा aspeed_video_buffer);
	vbq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	vbq->min_buffers_needed = 3;

	rc = vb2_queue_init(vbq);
	अगर (rc) अणु
		v4l2_ctrl_handler_मुक्त(&video->ctrl_handler);
		v4l2_device_unरेजिस्टर(v4l2_dev);

		dev_err(video->dev, "Failed to init vb2 queue\n");
		वापस rc;
	पूर्ण

	vdev->queue = vbq;
	vdev->fops = &aspeed_video_v4l2_fops;
	vdev->device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_READWRITE |
		V4L2_CAP_STREAMING;
	vdev->v4l2_dev = v4l2_dev;
	strscpy(vdev->name, DEVICE_NAME, माप(vdev->name));
	vdev->vfl_type = VFL_TYPE_VIDEO;
	vdev->vfl_dir = VFL_सूची_RX;
	vdev->release = video_device_release_empty;
	vdev->ioctl_ops = &aspeed_video_ioctl_ops;
	vdev->lock = &video->video_lock;

	video_set_drvdata(vdev, video);
	rc = video_रेजिस्टर_device(vdev, VFL_TYPE_VIDEO, 0);
	अगर (rc) अणु
		v4l2_ctrl_handler_मुक्त(&video->ctrl_handler);
		v4l2_device_unरेजिस्टर(v4l2_dev);

		dev_err(video->dev, "Failed to register video device\n");
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_video_init(काष्ठा aspeed_video *video)
अणु
	पूर्णांक irq;
	पूर्णांक rc;
	काष्ठा device *dev = video->dev;

	irq = irq_of_parse_and_map(dev->of_node, 0);
	अगर (!irq) अणु
		dev_err(dev, "Unable to find IRQ\n");
		वापस -ENODEV;
	पूर्ण

	rc = devm_request_thपढ़ोed_irq(dev, irq, शून्य, aspeed_video_irq,
				       IRQF_ONESHOT, DEVICE_NAME, video);
	अगर (rc < 0) अणु
		dev_err(dev, "Unable to request IRQ %d\n", irq);
		वापस rc;
	पूर्ण

	video->eclk = devm_clk_get(dev, "eclk");
	अगर (IS_ERR(video->eclk)) अणु
		dev_err(dev, "Unable to get ECLK\n");
		वापस PTR_ERR(video->eclk);
	पूर्ण

	rc = clk_prepare(video->eclk);
	अगर (rc)
		वापस rc;

	video->vclk = devm_clk_get(dev, "vclk");
	अगर (IS_ERR(video->vclk)) अणु
		dev_err(dev, "Unable to get VCLK\n");
		rc = PTR_ERR(video->vclk);
		जाओ err_unprepare_eclk;
	पूर्ण

	rc = clk_prepare(video->vclk);
	अगर (rc)
		जाओ err_unprepare_eclk;

	of_reserved_mem_device_init(dev);

	rc = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));
	अगर (rc) अणु
		dev_err(dev, "Failed to set DMA mask\n");
		जाओ err_release_reserved_mem;
	पूर्ण

	अगर (!aspeed_video_alloc_buf(video, &video->jpeg,
				    VE_JPEG_HEADER_SIZE)) अणु
		dev_err(dev, "Failed to allocate DMA for JPEG header\n");
		rc = -ENOMEM;
		जाओ err_release_reserved_mem;
	पूर्ण

	aspeed_video_init_jpeg_table(video->jpeg.virt, video->yuv420);

	वापस 0;

err_release_reserved_mem:
	of_reserved_mem_device_release(dev);
	clk_unprepare(video->vclk);
err_unprepare_eclk:
	clk_unprepare(video->eclk);

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा of_device_id aspeed_video_of_match[] = अणु
	अणु .compatible = "aspeed,ast2400-video-engine", .data = &ast2400_config पूर्ण,
	अणु .compatible = "aspeed,ast2500-video-engine", .data = &ast2500_config पूर्ण,
	अणु .compatible = "aspeed,ast2600-video-engine", .data = &ast2600_config पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, aspeed_video_of_match);

अटल पूर्णांक aspeed_video_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा aspeed_video_config *config;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा aspeed_video *video;
	पूर्णांक rc;

	video = devm_kzalloc(&pdev->dev, माप(*video), GFP_KERNEL);
	अगर (!video)
		वापस -ENOMEM;

	video->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(video->base))
		वापस PTR_ERR(video->base);

	match = of_match_node(aspeed_video_of_match, pdev->dev.of_node);
	अगर (!match)
		वापस -EINVAL;

	config = match->data;
	video->jpeg_mode = config->jpeg_mode;
	video->comp_size_पढ़ो = config->comp_size_पढ़ो;

	video->frame_rate = 30;
	video->dev = &pdev->dev;
	spin_lock_init(&video->lock);
	mutex_init(&video->video_lock);
	init_रुकोqueue_head(&video->रुको);
	INIT_DELAYED_WORK(&video->res_work, aspeed_video_resolution_work);
	INIT_LIST_HEAD(&video->buffers);

	rc = aspeed_video_init(video);
	अगर (rc)
		वापस rc;

	rc = aspeed_video_setup_video(video);
	अगर (rc) अणु
		clk_unprepare(video->vclk);
		clk_unprepare(video->eclk);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_video_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा v4l2_device *v4l2_dev = dev_get_drvdata(dev);
	काष्ठा aspeed_video *video = to_aspeed_video(v4l2_dev);

	aspeed_video_off(video);

	clk_unprepare(video->vclk);
	clk_unprepare(video->eclk);

	vb2_video_unरेजिस्टर_device(&video->vdev);

	v4l2_ctrl_handler_मुक्त(&video->ctrl_handler);

	v4l2_device_unरेजिस्टर(v4l2_dev);

	dma_मुक्त_coherent(video->dev, VE_JPEG_HEADER_SIZE, video->jpeg.virt,
			  video->jpeg.dma);

	of_reserved_mem_device_release(dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver aspeed_video_driver = अणु
	.driver = अणु
		.name = DEVICE_NAME,
		.of_match_table = aspeed_video_of_match,
	पूर्ण,
	.probe = aspeed_video_probe,
	.हटाओ = aspeed_video_हटाओ,
पूर्ण;

module_platक्रमm_driver(aspeed_video_driver);

MODULE_DESCRIPTION("ASPEED Video Engine Driver");
MODULE_AUTHOR("Eddie James");
MODULE_LICENSE("GPL v2");
