<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  tw68 driver common header file
 *
 *  Much of this code is derived from the cx88 and sa7134 drivers, which
 *  were in turn derived from the bt87x driver.  The original work was by
 *  Gerd Knorr; more recently the code was enhanced by Mauro Carvalho Chehab,
 *  Hans Verkuil, Andy Walls and many others.  Their work is gratefully
 *  acknowledged.  Full credit goes to them - any problems within this code
 *  are mine.
 *
 *  Copyright (C) 2009  William M. Brack
 *
 *  Refactored and updated to the latest v4l core frameworks:
 *
 *  Copyright (C) 2014 Hans Verkuil <hverkuil@xs4all.nl>
 */

#समावेश <linux/pci.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/पन.स>

#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-dma-sg.h>

#समावेश "tw68-reg.h"

#घोषणा	UNSET	(-1U)

#घोषणा TW68_NORMS ( \
	V4L2_STD_NTSC    | V4L2_STD_PAL       | V4L2_STD_SECAM    | \
	V4L2_STD_PAL_M   | V4L2_STD_PAL_Nc    | V4L2_STD_PAL_60)

#घोषणा	TW68_VID_INTS	(TW68_FFERR | TW68_PABORT | TW68_DMAPERR | \
			 TW68_FFOF   | TW68_DMAPI)
/* TW6800 chips have trouble with these, so we करोn't set them क्रम that chip */
#घोषणा	TW68_VID_INTSX	(TW68_FDMIS | TW68_HLOCK | TW68_VLOCK)

#घोषणा	TW68_I2C_INTS	(TW68_SBERR | TW68_SBDONE | TW68_SBERR2  | \
			 TW68_SBDONE2)

क्रमागत tw68_decoder_type अणु
	TW6800,
	TW6801,
	TW6804,
	TWXXXX,
पूर्ण;

/* ----------------------------------------------------------- */
/* अटल data                                                 */

काष्ठा tw68_tvnorm अणु
	अक्षर		*name;
	v4l2_std_id	id;

	/* video decoder */
	u32	sync_control;
	u32	luma_control;
	u32	chroma_ctrl1;
	u32	chroma_gain;
	u32	chroma_ctrl2;
	u32	vgate_misc;

	/* video scaler */
	u32	h_delay;
	u32	h_delay0;	/* क्रम TW6800 */
	u32	h_start;
	u32	h_stop;
	u32	v_delay;
	u32	video_v_start;
	u32	video_v_stop;
	u32	vbi_v_start_0;
	u32	vbi_v_stop_0;
	u32	vbi_v_start_1;

	/* Techwell specअगरic */
	u32	क्रमmat;
पूर्ण;

काष्ठा tw68_क्रमmat अणु
	u32	fourcc;
	u32	depth;
	u32	twक्रमmat;
पूर्ण;

/* ----------------------------------------------------------- */
/* card configuration					  */

#घोषणा TW68_BOARD_NOAUTO		UNSET
#घोषणा TW68_BOARD_UNKNOWN		0
#घोषणा	TW68_BOARD_GENERIC_6802		1

#घोषणा	TW68_MAXBOARDS			16
#घोषणा	TW68_INPUT_MAX			4

/* ----------------------------------------------------------- */
/* device / file handle status                                 */

#घोषणा	BUFFER_TIMEOUT	msecs_to_jअगरfies(500)	/* 0.5 seconds */

काष्ठा tw68_dev;	/* क्रमward delclaration */

/* buffer क्रम one video/vbi/ts frame */
काष्ठा tw68_buf अणु
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head list;

	अचिन्हित पूर्णांक   size;
	__le32         *cpu;
	__le32         *jmp;
	dma_addr_t     dma;
पूर्ण;

काष्ठा tw68_fmt अणु
	अक्षर			*name;
	u32			fourcc;	/* v4l2 क्रमmat id */
	पूर्णांक			depth;
	पूर्णांक			flags;
	u32			twक्रमmat;
पूर्ण;

/* global device status */
काष्ठा tw68_dev अणु
	काष्ठा mutex		lock;
	spinlock_t		slock;
	u16			instance;
	काष्ठा v4l2_device	v4l2_dev;

	/* various device info */
	क्रमागत tw68_decoder_type	vdecoder;
	काष्ठा video_device	vdev;
	काष्ठा v4l2_ctrl_handler hdl;

	/* pci i/o */
	अक्षर			*name;
	काष्ठा pci_dev		*pci;
	अचिन्हित अक्षर		pci_rev, pci_lat;
	u32			__iomem *lmmio;
	u8			__iomem *bmmio;
	u32			pci_irqmask;
	/* The irq mask to be used will depend upon the chip type */
	u32			board_virqmask;

	/* video capture */
	स्थिर काष्ठा tw68_क्रमmat *fmt;
	अचिन्हित		width, height;
	अचिन्हित		seqnr;
	अचिन्हित		field;
	काष्ठा vb2_queue	vidq;
	काष्ठा list_head	active;

	/* various v4l controls */
	स्थिर काष्ठा tw68_tvnorm *tvnorm;	/* video */

	पूर्णांक			input;
पूर्ण;

/* ----------------------------------------------------------- */

#घोषणा tw_पढ़ोl(reg)		पढ़ोl(dev->lmmio + ((reg) >> 2))
#घोषणा	tw_पढ़ोb(reg)		पढ़ोb(dev->bmmio + (reg))
#घोषणा tw_ग_लिखोl(reg, value)	ग_लिखोl((value), dev->lmmio + ((reg) >> 2))
#घोषणा	tw_ग_लिखोb(reg, value)	ग_लिखोb((value), dev->bmmio + (reg))

#घोषणा tw_anकरोrl(reg, mask, value) \
		ग_लिखोl((पढ़ोl(dev->lmmio+((reg)>>2)) & ~(mask)) |\
		((value) & (mask)), dev->lmmio+((reg)>>2))
#घोषणा	tw_anकरोrb(reg, mask, value) \
		ग_लिखोb((पढ़ोb(dev->bmmio + (reg)) & ~(mask)) |\
		((value) & (mask)), dev->bmmio+(reg))
#घोषणा tw_setl(reg, bit)	tw_anकरोrl((reg), (bit), (bit))
#घोषणा	tw_setb(reg, bit)	tw_anकरोrb((reg), (bit), (bit))
#घोषणा	tw_clearl(reg, bit)	\
		ग_लिखोl((पढ़ोl(dev->lmmio + ((reg) >> 2)) & ~(bit)), \
		dev->lmmio + ((reg) >> 2))
#घोषणा	tw_clearb(reg, bit)	\
		ग_लिखोb((पढ़ोb(dev->bmmio+(reg)) & ~(bit)), \
		dev->bmmio + (reg))

#घोषणा tw_रुको(us) अणु udelay(us); पूर्ण

/* ----------------------------------------------------------- */
/* tw68-video.c                                                */

व्योम tw68_set_tvnorm_hw(काष्ठा tw68_dev *dev);

पूर्णांक tw68_video_init1(काष्ठा tw68_dev *dev);
पूर्णांक tw68_video_init2(काष्ठा tw68_dev *dev, पूर्णांक video_nr);
व्योम tw68_irq_video_करोne(काष्ठा tw68_dev *dev, अचिन्हित दीर्घ status);
पूर्णांक tw68_video_start_dma(काष्ठा tw68_dev *dev, काष्ठा tw68_buf *buf);

/* ----------------------------------------------------------- */
/* tw68-risc.c                                                 */

पूर्णांक tw68_risc_buffer(काष्ठा pci_dev *pci, काष्ठा tw68_buf *buf,
	काष्ठा scatterlist *sglist, अचिन्हित पूर्णांक top_offset,
	अचिन्हित पूर्णांक bottom_offset, अचिन्हित पूर्णांक bpl,
	अचिन्हित पूर्णांक padding, अचिन्हित पूर्णांक lines);
