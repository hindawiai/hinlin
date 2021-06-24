<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  TW5864 driver  - common header file
 *
 *  Copyright (C) 2016 Bluecherry, LLC <मुख्यtainers@bluecherrydvr.com>
 */

#समावेश <linux/pci.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/videobuf2-dma-sg.h>

#समावेश "tw5864-reg.h"

#घोषणा PCI_DEVICE_ID_TECHWELL_5864 0x5864

#घोषणा TW5864_NORMS V4L2_STD_ALL

/* ----------------------------------------------------------- */
/* card configuration   */

#घोषणा TW5864_INPUTS 4

/* The TW5864 uses 192 (16x12) detection cells in full screen क्रम motion
 * detection. Each detection cell is composed of 44 pixels and 20 lines क्रम
 * NTSC and 24 lines क्रम PAL.
 */
#घोषणा MD_CELLS_HOR 16
#घोषणा MD_CELLS_VERT 12
#घोषणा MD_CELLS (MD_CELLS_HOR * MD_CELLS_VERT)

#घोषणा H264_VLC_BUF_SIZE 0x80000
#घोषणा H264_MV_BUF_SIZE 0x2000 /* device ग_लिखोs 5396 bytes */
#घोषणा QP_VALUE 28
#घोषणा MAX_GOP_SIZE 255
#घोषणा GOP_SIZE MAX_GOP_SIZE

क्रमागत resolution अणु
	D1 = 1,
	HD1 = 2, /* half d1 - 360x(240|288) */
	CIF = 3,
	QCIF = 4,
पूर्ण;

/* ----------------------------------------------------------- */
/* device / file handle status                                 */

काष्ठा tw5864_dev; /* क्रमward delclaration */

/* buffer क्रम one video/vbi/ts frame */
काष्ठा tw5864_buf अणु
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head list;

	अचिन्हित पूर्णांक size;
पूर्ण;

काष्ठा tw5864_dma_buf अणु
	व्योम *addr;
	dma_addr_t dma_addr;
पूर्ण;

क्रमागत tw5864_vid_std अणु
	STD_NTSC = 0, /* NTSC (M) */
	STD_PAL = 1, /* PAL (B, D, G, H, I) */
	STD_SECAM = 2, /* SECAM */
	STD_NTSC443 = 3, /* NTSC4.43 */
	STD_PAL_M = 4, /* PAL (M) */
	STD_PAL_CN = 5, /* PAL (CN) */
	STD_PAL_60 = 6, /* PAL 60 */
	STD_INVALID = 7,
	STD_AUTO = 7,
पूर्ण;

काष्ठा tw5864_input अणु
	पूर्णांक nr; /* input number */
	काष्ठा tw5864_dev *root;
	काष्ठा mutex lock; /* used क्रम vidq and vdev */
	spinlock_t slock; /* used क्रम sync between ISR, tasklet & V4L2 API */
	काष्ठा video_device vdev;
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा vb2_queue vidq;
	काष्ठा list_head active;
	क्रमागत resolution resolution;
	अचिन्हित पूर्णांक width, height;
	अचिन्हित पूर्णांक frame_seqno;
	अचिन्हित पूर्णांक frame_gop_seqno;
	अचिन्हित पूर्णांक h264_idr_pic_id;
	पूर्णांक enabled;
	क्रमागत tw5864_vid_std std;
	v4l2_std_id v4l2_std;
	पूर्णांक tail_nb_bits;
	u8 tail;
	u8 *buf_cur_ptr;
	पूर्णांक buf_cur_space_left;

	u32 reg_पूर्णांकerlacing;
	u32 reg_vlc;
	u32 reg_dsp_codec;
	u32 reg_dsp;
	u32 reg_emu;
	u32 reg_dsp_qp;
	u32 reg_dsp_ref_mvp_lambda;
	u32 reg_dsp_i4x4_weight;
	u32 buf_id;

	काष्ठा tw5864_buf *vb;

	काष्ठा v4l2_ctrl *md_threshold_grid_ctrl;
	u16 md_threshold_grid_values[12 * 16];
	पूर्णांक qp;
	पूर्णांक gop;

	/*
	 * In (1/MAX_FPS) units.
	 * For max FPS (शेष), set to 1.
	 * For 1 FPS, set to e.g. 32.
	 */
	पूर्णांक frame_पूर्णांकerval;
	अचिन्हित दीर्घ new_frame_deadline;
पूर्ण;

काष्ठा tw5864_h264_frame अणु
	काष्ठा tw5864_dma_buf vlc;
	काष्ठा tw5864_dma_buf mv;
	पूर्णांक vlc_len;
	u32 checksum;
	काष्ठा tw5864_input *input;
	u64 बारtamp;
	अचिन्हित पूर्णांक seqno;
	अचिन्हित पूर्णांक gop_seqno;
पूर्ण;

/* global device status */
काष्ठा tw5864_dev अणु
	spinlock_t slock; /* used क्रम sync between ISR, tasklet & V4L2 API */
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा tw5864_input inमाला_दो[TW5864_INPUTS];
#घोषणा H264_BUF_CNT 4
	काष्ठा tw5864_h264_frame h264_buf[H264_BUF_CNT];
	पूर्णांक h264_buf_r_index;
	पूर्णांक h264_buf_w_index;

	काष्ठा tasklet_काष्ठा tasklet;

	पूर्णांक encoder_busy;
	/* Input number to check next क्रम पढ़ोy raw picture (in RR fashion) */
	पूर्णांक next_input;

	/* pci i/o */
	अक्षर name[64];
	काष्ठा pci_dev *pci;
	व्योम __iomem *mmio;
	u32 irqmask;
पूर्ण;

#घोषणा tw_पढ़ोl(reg) पढ़ोl(dev->mmio + reg)
#घोषणा tw_mask_पढ़ोl(reg, mask) \
	(tw_पढ़ोl(reg) & (mask))
#घोषणा tw_mask_shअगरt_पढ़ोl(reg, mask, shअगरt) \
	(tw_mask_पढ़ोl((reg), ((mask) << (shअगरt))) >> (shअगरt))

#घोषणा tw_ग_लिखोl(reg, value) ग_लिखोl((value), dev->mmio + reg)
#घोषणा tw_mask_ग_लिखोl(reg, mask, value) \
	tw_ग_लिखोl(reg, (tw_पढ़ोl(reg) & ~(mask)) | ((value) & (mask)))
#घोषणा tw_mask_shअगरt_ग_लिखोl(reg, mask, shअगरt, value) \
	tw_mask_ग_लिखोl((reg), ((mask) << (shअगरt)), ((value) << (shअगरt)))

#घोषणा tw_setl(reg, bit) tw_ग_लिखोl((reg), tw_पढ़ोl(reg) | (bit))
#घोषणा tw_clearl(reg, bit) tw_ग_लिखोl((reg), tw_पढ़ोl(reg) & ~(bit))

u8 tw5864_indir_पढ़ोb(काष्ठा tw5864_dev *dev, u16 addr);
#घोषणा tw_indir_पढ़ोb(addr) tw5864_indir_पढ़ोb(dev, addr)
व्योम tw5864_indir_ग_लिखोb(काष्ठा tw5864_dev *dev, u16 addr, u8 data);
#घोषणा tw_indir_ग_लिखोb(addr, data) tw5864_indir_ग_लिखोb(dev, addr, data)

व्योम tw5864_irqmask_apply(काष्ठा tw5864_dev *dev);
पूर्णांक tw5864_video_init(काष्ठा tw5864_dev *dev, पूर्णांक *video_nr);
व्योम tw5864_video_fini(काष्ठा tw5864_dev *dev);
व्योम tw5864_prepare_frame_headers(काष्ठा tw5864_input *input);
व्योम tw5864_h264_put_stream_header(u8 **buf, माप_प्रकार *space_left, पूर्णांक qp,
				   पूर्णांक width, पूर्णांक height);
व्योम tw5864_h264_put_slice_header(u8 **buf, माप_प्रकार *space_left,
				  अचिन्हित पूर्णांक idr_pic_id,
				  अचिन्हित पूर्णांक frame_gop_seqno,
				  पूर्णांक *tail_nb_bits, u8 *tail);
व्योम tw5864_request_encoded_frame(काष्ठा tw5864_input *input);
