<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * R-Car Gen3 Digital Radio Interface (DRIF) driver
 *
 * Copyright (C) 2017 Renesas Electronics Corporation
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

/*
 * The R-Car DRIF is a receive only MSIOF like controller with an
 * बाह्यal master device driving the SCK. It receives data पूर्णांकo a FIFO,
 * then this driver uses the SYS-DMAC engine to move the data from
 * the device to memory.
 *
 * Each DRIF channel DRIFx (as per datasheet) contains two पूर्णांकernal
 * channels DRIFx0 & DRIFx1 within itself with each having its own resources
 * like module clk, रेजिस्टर set, irq and dma. These पूर्णांकernal channels share
 * common CLK & SYNC from master. The two data pins D0 & D1 shall be
 * considered to represent the two पूर्णांकernal channels. This पूर्णांकernal split
 * is not visible to the master device.
 *
 * Depending on the master device, a DRIF channel can use
 *  (1) both पूर्णांकernal channels (D0 & D1) to receive data in parallel (or)
 *  (2) one पूर्णांकernal channel (D0 or D1) to receive data
 *
 * The primary design goal of this controller is to act as a Digital Radio
 * Interface that receives digital samples from a tuner device. Hence the
 * driver exposes the device as a V4L2 SDR device. In order to qualअगरy as
 * a V4L2 SDR device, it should possess a tuner पूर्णांकerface as mandated by the
 * framework. This driver expects a tuner driver (sub-device) to bind
 * asynchronously with this device and the combined drivers shall expose
 * a V4L2 compliant SDR device. The DRIF driver is independent of the
 * tuner venकरोr.
 *
 * The DRIF h/w can support I2S mode and Frame start synchronization pulse mode.
 * This driver is tested क्रम I2S mode only because of the availability of
 * suitable master devices. Hence, not all configurable options of DRIF h/w
 * like lsb/msb first, syncdl, dtdl etc. are exposed via DT and I2S शेषs
 * are used. These can be exposed later अगर needed after testing.
 */
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>

/* DRIF रेजिस्टर offsets */
#घोषणा RCAR_DRIF_SITMDR1			0x00
#घोषणा RCAR_DRIF_SITMDR2			0x04
#घोषणा RCAR_DRIF_SITMDR3			0x08
#घोषणा RCAR_DRIF_SIRMDR1			0x10
#घोषणा RCAR_DRIF_SIRMDR2			0x14
#घोषणा RCAR_DRIF_SIRMDR3			0x18
#घोषणा RCAR_DRIF_SICTR				0x28
#घोषणा RCAR_DRIF_SIFCTR			0x30
#घोषणा RCAR_DRIF_SISTR				0x40
#घोषणा RCAR_DRIF_SIIER				0x44
#घोषणा RCAR_DRIF_SIRFDR			0x60

#घोषणा RCAR_DRIF_RFOVF			BIT(3)	/* Receive FIFO overflow */
#घोषणा RCAR_DRIF_RFUDF			BIT(4)	/* Receive FIFO underflow */
#घोषणा RCAR_DRIF_RFSERR		BIT(5)	/* Receive frame sync error */
#घोषणा RCAR_DRIF_Rखातापूर्ण			BIT(7)	/* Frame reception end */
#घोषणा RCAR_DRIF_RDREQ			BIT(12) /* Receive data xfer req */
#घोषणा RCAR_DRIF_RFFUL			BIT(13)	/* Receive FIFO full */

/* SIRMDR1 */
#घोषणा RCAR_DRIF_SIRMDR1_SYNCMD_FRAME		(0 << 28)
#घोषणा RCAR_DRIF_SIRMDR1_SYNCMD_LR		(3 << 28)

#घोषणा RCAR_DRIF_SIRMDR1_SYNCAC_POL_HIGH	(0 << 25)
#घोषणा RCAR_DRIF_SIRMDR1_SYNCAC_POL_LOW	(1 << 25)

#घोषणा RCAR_DRIF_SIRMDR1_MSB_FIRST		(0 << 24)
#घोषणा RCAR_DRIF_SIRMDR1_LSB_FIRST		(1 << 24)

#घोषणा RCAR_DRIF_SIRMDR1_DTDL_0		(0 << 20)
#घोषणा RCAR_DRIF_SIRMDR1_DTDL_1		(1 << 20)
#घोषणा RCAR_DRIF_SIRMDR1_DTDL_2		(2 << 20)
#घोषणा RCAR_DRIF_SIRMDR1_DTDL_0PT5		(5 << 20)
#घोषणा RCAR_DRIF_SIRMDR1_DTDL_1PT5		(6 << 20)

#घोषणा RCAR_DRIF_SIRMDR1_SYNCDL_0		(0 << 20)
#घोषणा RCAR_DRIF_SIRMDR1_SYNCDL_1		(1 << 20)
#घोषणा RCAR_DRIF_SIRMDR1_SYNCDL_2		(2 << 20)
#घोषणा RCAR_DRIF_SIRMDR1_SYNCDL_3		(3 << 20)
#घोषणा RCAR_DRIF_SIRMDR1_SYNCDL_0PT5		(5 << 20)
#घोषणा RCAR_DRIF_SIRMDR1_SYNCDL_1PT5		(6 << 20)

#घोषणा RCAR_DRIF_MDR_GRPCNT(n)			(((n) - 1) << 30)
#घोषणा RCAR_DRIF_MDR_BITLEN(n)			(((n) - 1) << 24)
#घोषणा RCAR_DRIF_MDR_WDCNT(n)			(((n) - 1) << 16)

/* Hidden Transmit रेजिस्टर that controls CLK & SYNC */
#घोषणा RCAR_DRIF_SITMDR1_PCON			BIT(30)

#घोषणा RCAR_DRIF_SICTR_RX_RISING_EDGE		BIT(26)
#घोषणा RCAR_DRIF_SICTR_RX_EN			BIT(8)
#घोषणा RCAR_DRIF_SICTR_RESET			BIT(0)

/* Constants */
#घोषणा RCAR_DRIF_NUM_HWBUFS			32
#घोषणा RCAR_DRIF_MAX_DEVS			4
#घोषणा RCAR_DRIF_DEFAULT_NUM_HWBUFS		16
#घोषणा RCAR_DRIF_DEFAULT_HWBUF_SIZE		(4 * PAGE_SIZE)
#घोषणा RCAR_DRIF_MAX_CHANNEL			2
#घोषणा RCAR_SDR_BUFFER_SIZE			SZ_64K

/* Internal buffer status flags */
#घोषणा RCAR_DRIF_BUF_DONE			BIT(0)	/* DMA completed */
#घोषणा RCAR_DRIF_BUF_OVERFLOW			BIT(1)	/* Overflow detected */

#घोषणा to_rcar_drअगर_buf_pair(sdr, ch_num, idx)			\
	(&((sdr)->ch[!(ch_num)]->buf[(idx)]))

#घोषणा क्रम_each_rcar_drअगर_channel(ch, ch_mask)			\
	क्रम_each_set_bit(ch, ch_mask, RCAR_DRIF_MAX_CHANNEL)

/* Debug */
#घोषणा rdrअगर_dbg(sdr, fmt, arg...)				\
	dev_dbg(sdr->v4l2_dev.dev, fmt, ## arg)

#घोषणा rdrअगर_err(sdr, fmt, arg...)				\
	dev_err(sdr->v4l2_dev.dev, fmt, ## arg)

/* Stream क्रमmats */
काष्ठा rcar_drअगर_क्रमmat अणु
	u32	pixelक्रमmat;
	u32	buffersize;
	u32	bitlen;
	u32	wdcnt;
	u32	num_ch;
पूर्ण;

/* Format descriptions क्रम capture */
अटल स्थिर काष्ठा rcar_drअगर_क्रमmat क्रमmats[] = अणु
	अणु
		.pixelक्रमmat	= V4L2_SDR_FMT_PCU16BE,
		.buffersize	= RCAR_SDR_BUFFER_SIZE,
		.bitlen		= 16,
		.wdcnt		= 1,
		.num_ch		= 2,
	पूर्ण,
	अणु
		.pixelक्रमmat	= V4L2_SDR_FMT_PCU18BE,
		.buffersize	= RCAR_SDR_BUFFER_SIZE,
		.bitlen		= 18,
		.wdcnt		= 1,
		.num_ch		= 2,
	पूर्ण,
	अणु
		.pixelक्रमmat	= V4L2_SDR_FMT_PCU20BE,
		.buffersize	= RCAR_SDR_BUFFER_SIZE,
		.bitlen		= 20,
		.wdcnt		= 1,
		.num_ch		= 2,
	पूर्ण,
पूर्ण;

/* Buffer क्रम a received frame from one or both पूर्णांकernal channels */
काष्ठा rcar_drअगर_frame_buf अणु
	/* Common v4l buffer stuff -- must be first */
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head list;
पूर्ण;

/* OF graph endpoपूर्णांक's V4L2 async data */
काष्ठा rcar_drअगर_graph_ep अणु
	काष्ठा v4l2_subdev *subdev;	/* Async matched subdev */
पूर्ण;

/* DMA buffer */
काष्ठा rcar_drअगर_hwbuf अणु
	व्योम *addr;			/* CPU-side address */
	अचिन्हित पूर्णांक status;		/* Buffer status flags */
पूर्ण;

/* Internal channel */
काष्ठा rcar_drअगर अणु
	काष्ठा rcar_drअगर_sdr *sdr;	/* Group device */
	काष्ठा platक्रमm_device *pdev;	/* Channel's pdev */
	व्योम __iomem *base;		/* Base रेजिस्टर address */
	resource_माप_प्रकार start;		/* I/O resource offset */
	काष्ठा dma_chan *dmach;		/* Reserved DMA channel */
	काष्ठा clk *clk;		/* Module घड़ी */
	काष्ठा rcar_drअगर_hwbuf buf[RCAR_DRIF_NUM_HWBUFS]; /* H/W bufs */
	dma_addr_t dma_handle;		/* Handle क्रम all bufs */
	अचिन्हित पूर्णांक num;		/* Channel number */
	bool acting_sdr;		/* Channel acting as SDR device */
पूर्ण;

/* DRIF V4L2 SDR */
काष्ठा rcar_drअगर_sdr अणु
	काष्ठा device *dev;		/* Platक्रमm device */
	काष्ठा video_device *vdev;	/* V4L2 SDR device */
	काष्ठा v4l2_device v4l2_dev;	/* V4L2 device */

	/* Videobuf2 queue and queued buffers list */
	काष्ठा vb2_queue vb_queue;
	काष्ठा list_head queued_bufs;
	spinlock_t queued_bufs_lock;	/* Protects queued_bufs */
	spinlock_t dma_lock;		/* To serialize DMA cb of channels */

	काष्ठा mutex v4l2_mutex;	/* To serialize ioctls */
	काष्ठा mutex vb_queue_mutex;	/* To serialize streaming ioctls */
	काष्ठा v4l2_ctrl_handler ctrl_hdl;	/* SDR control handler */
	काष्ठा v4l2_async_notअगरier notअगरier;	/* For subdev (tuner) */
	काष्ठा rcar_drअगर_graph_ep ep;	/* Endpoपूर्णांक V4L2 async data */

	/* Current V4L2 SDR क्रमmat ptr */
	स्थिर काष्ठा rcar_drअगर_क्रमmat *fmt;

	/* Device tree SYNC properties */
	u32 mdr1;

	/* Internals */
	काष्ठा rcar_drअगर *ch[RCAR_DRIF_MAX_CHANNEL]; /* DRIFx0,1 */
	अचिन्हित दीर्घ hw_ch_mask;	/* Enabled channels per DT */
	अचिन्हित दीर्घ cur_ch_mask;	/* Used channels क्रम an SDR FMT */
	u32 num_hw_ch;			/* Num of DT enabled channels */
	u32 num_cur_ch;			/* Num of used channels */
	u32 hwbuf_size;			/* Each DMA buffer size */
	u32 produced;			/* Buffers produced by sdr dev */
पूर्ण;

/* Register access functions */
अटल व्योम rcar_drअगर_ग_लिखो(काष्ठा rcar_drअगर *ch, u32 offset, u32 data)
अणु
	ग_लिखोl(data, ch->base + offset);
पूर्ण

अटल u32 rcar_drअगर_पढ़ो(काष्ठा rcar_drअगर *ch, u32 offset)
अणु
	वापस पढ़ोl(ch->base + offset);
पूर्ण

/* Release DMA channels */
अटल व्योम rcar_drअगर_release_dmachannels(काष्ठा rcar_drअगर_sdr *sdr)
अणु
	अचिन्हित पूर्णांक i;

	क्रम_each_rcar_drअगर_channel(i, &sdr->cur_ch_mask)
		अगर (sdr->ch[i]->dmach) अणु
			dma_release_channel(sdr->ch[i]->dmach);
			sdr->ch[i]->dmach = शून्य;
		पूर्ण
पूर्ण

/* Allocate DMA channels */
अटल पूर्णांक rcar_drअगर_alloc_dmachannels(काष्ठा rcar_drअगर_sdr *sdr)
अणु
	काष्ठा dma_slave_config dma_cfg;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम_each_rcar_drअगर_channel(i, &sdr->cur_ch_mask) अणु
		काष्ठा rcar_drअगर *ch = sdr->ch[i];

		ch->dmach = dma_request_chan(&ch->pdev->dev, "rx");
		अगर (IS_ERR(ch->dmach)) अणु
			ret = PTR_ERR(ch->dmach);
			अगर (ret != -EPROBE_DEFER)
				rdrअगर_err(sdr,
					  "ch%u: dma channel req failed: %pe\n",
					  i, ch->dmach);
			ch->dmach = शून्य;
			जाओ dmach_error;
		पूर्ण

		/* Configure slave */
		स_रखो(&dma_cfg, 0, माप(dma_cfg));
		dma_cfg.src_addr = (phys_addr_t)(ch->start + RCAR_DRIF_SIRFDR);
		dma_cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		ret = dmaengine_slave_config(ch->dmach, &dma_cfg);
		अगर (ret) अणु
			rdrअगर_err(sdr, "ch%u: dma slave config failed\n", i);
			जाओ dmach_error;
		पूर्ण
	पूर्ण
	वापस 0;

dmach_error:
	rcar_drअगर_release_dmachannels(sdr);
	वापस ret;
पूर्ण

/* Release queued vb2 buffers */
अटल व्योम rcar_drअगर_release_queued_bufs(काष्ठा rcar_drअगर_sdr *sdr,
					  क्रमागत vb2_buffer_state state)
अणु
	काष्ठा rcar_drअगर_frame_buf *fbuf, *पंचांगp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sdr->queued_bufs_lock, flags);
	list_क्रम_each_entry_safe(fbuf, पंचांगp, &sdr->queued_bufs, list) अणु
		list_del(&fbuf->list);
		vb2_buffer_करोne(&fbuf->vb.vb2_buf, state);
	पूर्ण
	spin_unlock_irqrestore(&sdr->queued_bufs_lock, flags);
पूर्ण

/* Set MDR शेषs */
अटल अंतरभूत व्योम rcar_drअगर_set_mdr1(काष्ठा rcar_drअगर_sdr *sdr)
अणु
	अचिन्हित पूर्णांक i;

	/* Set शेषs क्रम enabled पूर्णांकernal channels */
	क्रम_each_rcar_drअगर_channel(i, &sdr->cur_ch_mask) अणु
		/* Refer MSIOF section in manual क्रम this रेजिस्टर setting */
		rcar_drअगर_ग_लिखो(sdr->ch[i], RCAR_DRIF_SITMDR1,
				RCAR_DRIF_SITMDR1_PCON);

		/* Setup MDR1 value */
		rcar_drअगर_ग_लिखो(sdr->ch[i], RCAR_DRIF_SIRMDR1, sdr->mdr1);

		rdrअगर_dbg(sdr, "ch%u: mdr1 = 0x%08x",
			  i, rcar_drअगर_पढ़ो(sdr->ch[i], RCAR_DRIF_SIRMDR1));
	पूर्ण
पूर्ण

/* Set DRIF receive क्रमmat */
अटल पूर्णांक rcar_drअगर_set_क्रमmat(काष्ठा rcar_drअगर_sdr *sdr)
अणु
	अचिन्हित पूर्णांक i;

	rdrअगर_dbg(sdr, "setfmt: bitlen %u wdcnt %u num_ch %u\n",
		  sdr->fmt->bitlen, sdr->fmt->wdcnt, sdr->fmt->num_ch);

	/* Sanity check */
	अगर (sdr->fmt->num_ch > sdr->num_cur_ch) अणु
		rdrअगर_err(sdr, "fmt num_ch %u cur_ch %u mismatch\n",
			  sdr->fmt->num_ch, sdr->num_cur_ch);
		वापस -EINVAL;
	पूर्ण

	/* Setup group, bitlen & wdcnt */
	क्रम_each_rcar_drअगर_channel(i, &sdr->cur_ch_mask) अणु
		u32 mdr;

		/* Two groups */
		mdr = RCAR_DRIF_MDR_GRPCNT(2) |
			RCAR_DRIF_MDR_BITLEN(sdr->fmt->bitlen) |
			RCAR_DRIF_MDR_WDCNT(sdr->fmt->wdcnt);
		rcar_drअगर_ग_लिखो(sdr->ch[i], RCAR_DRIF_SIRMDR2, mdr);

		mdr = RCAR_DRIF_MDR_BITLEN(sdr->fmt->bitlen) |
			RCAR_DRIF_MDR_WDCNT(sdr->fmt->wdcnt);
		rcar_drअगर_ग_लिखो(sdr->ch[i], RCAR_DRIF_SIRMDR3, mdr);

		rdrअगर_dbg(sdr, "ch%u: new mdr[2,3] = 0x%08x, 0x%08x\n",
			  i, rcar_drअगर_पढ़ो(sdr->ch[i], RCAR_DRIF_SIRMDR2),
			  rcar_drअगर_पढ़ो(sdr->ch[i], RCAR_DRIF_SIRMDR3));
	पूर्ण
	वापस 0;
पूर्ण

/* Release DMA buffers */
अटल व्योम rcar_drअगर_release_buf(काष्ठा rcar_drअगर_sdr *sdr)
अणु
	अचिन्हित पूर्णांक i;

	क्रम_each_rcar_drअगर_channel(i, &sdr->cur_ch_mask) अणु
		काष्ठा rcar_drअगर *ch = sdr->ch[i];

		/* First entry contains the dma buf ptr */
		अगर (ch->buf[0].addr) अणु
			dma_मुक्त_coherent(&ch->pdev->dev,
				sdr->hwbuf_size * RCAR_DRIF_NUM_HWBUFS,
				ch->buf[0].addr, ch->dma_handle);
			ch->buf[0].addr = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/* Request DMA buffers */
अटल पूर्णांक rcar_drअगर_request_buf(काष्ठा rcar_drअगर_sdr *sdr)
अणु
	पूर्णांक ret = -ENOMEM;
	अचिन्हित पूर्णांक i, j;
	व्योम *addr;

	क्रम_each_rcar_drअगर_channel(i, &sdr->cur_ch_mask) अणु
		काष्ठा rcar_drअगर *ch = sdr->ch[i];

		/* Allocate DMA buffers */
		addr = dma_alloc_coherent(&ch->pdev->dev,
				sdr->hwbuf_size * RCAR_DRIF_NUM_HWBUFS,
				&ch->dma_handle, GFP_KERNEL);
		अगर (!addr) अणु
			rdrअगर_err(sdr,
			"ch%u: dma alloc failed. num hwbufs %u size %u\n",
			i, RCAR_DRIF_NUM_HWBUFS, sdr->hwbuf_size);
			जाओ error;
		पूर्ण

		/* Split the chunk and populate bufctxt */
		क्रम (j = 0; j < RCAR_DRIF_NUM_HWBUFS; j++) अणु
			ch->buf[j].addr = addr + (j * sdr->hwbuf_size);
			ch->buf[j].status = 0;
		पूर्ण
	पूर्ण
	वापस 0;
error:
	वापस ret;
पूर्ण

/* Setup vb_queue minimum buffer requirements */
अटल पूर्णांक rcar_drअगर_queue_setup(काष्ठा vb2_queue *vq,
			अचिन्हित पूर्णांक *num_buffers, अचिन्हित पूर्णांक *num_planes,
			अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा rcar_drअगर_sdr *sdr = vb2_get_drv_priv(vq);

	/* Need at least 16 buffers */
	अगर (vq->num_buffers + *num_buffers < 16)
		*num_buffers = 16 - vq->num_buffers;

	*num_planes = 1;
	sizes[0] = PAGE_ALIGN(sdr->fmt->buffersize);
	rdrअगर_dbg(sdr, "num_bufs %d sizes[0] %d\n", *num_buffers, sizes[0]);

	वापस 0;
पूर्ण

/* Enqueue buffer */
अटल व्योम rcar_drअगर_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा rcar_drअगर_sdr *sdr = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा rcar_drअगर_frame_buf *fbuf =
			container_of(vbuf, काष्ठा rcar_drअगर_frame_buf, vb);
	अचिन्हित दीर्घ flags;

	rdrअगर_dbg(sdr, "buf_queue idx %u\n", vb->index);
	spin_lock_irqsave(&sdr->queued_bufs_lock, flags);
	list_add_tail(&fbuf->list, &sdr->queued_bufs);
	spin_unlock_irqrestore(&sdr->queued_bufs_lock, flags);
पूर्ण

/* Get a frame buf from list */
अटल काष्ठा rcar_drअगर_frame_buf *
rcar_drअगर_get_fbuf(काष्ठा rcar_drअगर_sdr *sdr)
अणु
	काष्ठा rcar_drअगर_frame_buf *fbuf;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sdr->queued_bufs_lock, flags);
	fbuf = list_first_entry_or_null(&sdr->queued_bufs, काष्ठा
					rcar_drअगर_frame_buf, list);
	अगर (!fbuf) अणु
		/*
		 * App is late in enqueing buffers. Samples lost & there will
		 * be a gap in sequence number when app recovers
		 */
		rdrअगर_dbg(sdr, "\napp late: prod %u\n", sdr->produced);
		spin_unlock_irqrestore(&sdr->queued_bufs_lock, flags);
		वापस शून्य;
	पूर्ण
	list_del(&fbuf->list);
	spin_unlock_irqrestore(&sdr->queued_bufs_lock, flags);

	वापस fbuf;
पूर्ण

/* Helpers to set/clear buf pair status */
अटल अंतरभूत bool rcar_drअगर_bufs_करोne(काष्ठा rcar_drअगर_hwbuf **buf)
अणु
	वापस (buf[0]->status & buf[1]->status & RCAR_DRIF_BUF_DONE);
पूर्ण

अटल अंतरभूत bool rcar_drअगर_bufs_overflow(काष्ठा rcar_drअगर_hwbuf **buf)
अणु
	वापस ((buf[0]->status | buf[1]->status) & RCAR_DRIF_BUF_OVERFLOW);
पूर्ण

अटल अंतरभूत व्योम rcar_drअगर_bufs_clear(काष्ठा rcar_drअगर_hwbuf **buf,
					अचिन्हित पूर्णांक bit)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < RCAR_DRIF_MAX_CHANNEL; i++)
		buf[i]->status &= ~bit;
पूर्ण

/* Channel DMA complete */
अटल व्योम rcar_drअगर_channel_complete(काष्ठा rcar_drअगर *ch, u32 idx)
अणु
	u32 str;

	ch->buf[idx].status |= RCAR_DRIF_BUF_DONE;

	/* Check क्रम DRIF errors */
	str = rcar_drअगर_पढ़ो(ch, RCAR_DRIF_SISTR);
	अगर (unlikely(str & RCAR_DRIF_RFOVF)) अणु
		/* Writing the same clears it */
		rcar_drअगर_ग_लिखो(ch, RCAR_DRIF_SISTR, str);

		/* Overflow: some samples are lost */
		ch->buf[idx].status |= RCAR_DRIF_BUF_OVERFLOW;
	पूर्ण
पूर्ण

/* DMA callback क्रम each stage */
अटल व्योम rcar_drअगर_dma_complete(व्योम *dma_async_param)
अणु
	काष्ठा rcar_drअगर *ch = dma_async_param;
	काष्ठा rcar_drअगर_sdr *sdr = ch->sdr;
	काष्ठा rcar_drअगर_hwbuf *buf[RCAR_DRIF_MAX_CHANNEL];
	काष्ठा rcar_drअगर_frame_buf *fbuf;
	bool overflow = false;
	u32 idx, produced;
	अचिन्हित पूर्णांक i;

	spin_lock(&sdr->dma_lock);

	/* DMA can be terminated जबतक the callback was रुकोing on lock */
	अगर (!vb2_is_streaming(&sdr->vb_queue)) अणु
		spin_unlock(&sdr->dma_lock);
		वापस;
	पूर्ण

	idx = sdr->produced % RCAR_DRIF_NUM_HWBUFS;
	rcar_drअगर_channel_complete(ch, idx);

	अगर (sdr->num_cur_ch == RCAR_DRIF_MAX_CHANNEL) अणु
		buf[0] = ch->num ? to_rcar_drअगर_buf_pair(sdr, ch->num, idx) :
				&ch->buf[idx];
		buf[1] = ch->num ? &ch->buf[idx] :
				to_rcar_drअगर_buf_pair(sdr, ch->num, idx);

		/* Check अगर both DMA buffers are करोne */
		अगर (!rcar_drअगर_bufs_करोne(buf)) अणु
			spin_unlock(&sdr->dma_lock);
			वापस;
		पूर्ण

		/* Clear buf करोne status */
		rcar_drअगर_bufs_clear(buf, RCAR_DRIF_BUF_DONE);

		अगर (rcar_drअगर_bufs_overflow(buf)) अणु
			overflow = true;
			/* Clear the flag in status */
			rcar_drअगर_bufs_clear(buf, RCAR_DRIF_BUF_OVERFLOW);
		पूर्ण
	पूर्ण अन्यथा अणु
		buf[0] = &ch->buf[idx];
		अगर (buf[0]->status & RCAR_DRIF_BUF_OVERFLOW) अणु
			overflow = true;
			/* Clear the flag in status */
			buf[0]->status &= ~RCAR_DRIF_BUF_OVERFLOW;
		पूर्ण
	पूर्ण

	/* Buffer produced क्रम consumption */
	produced = sdr->produced++;
	spin_unlock(&sdr->dma_lock);

	rdrअगर_dbg(sdr, "ch%u: prod %u\n", ch->num, produced);

	/* Get fbuf */
	fbuf = rcar_drअगर_get_fbuf(sdr);
	अगर (!fbuf)
		वापस;

	क्रम (i = 0; i < RCAR_DRIF_MAX_CHANNEL; i++)
		स_नकल(vb2_plane_vaddr(&fbuf->vb.vb2_buf, 0) +
		       i * sdr->hwbuf_size, buf[i]->addr, sdr->hwbuf_size);

	fbuf->vb.field = V4L2_FIELD_NONE;
	fbuf->vb.sequence = produced;
	fbuf->vb.vb2_buf.बारtamp = kसमय_get_ns();
	vb2_set_plane_payload(&fbuf->vb.vb2_buf, 0, sdr->fmt->buffersize);

	/* Set error state on overflow */
	vb2_buffer_करोne(&fbuf->vb.vb2_buf,
			overflow ? VB2_BUF_STATE_ERROR : VB2_BUF_STATE_DONE);
पूर्ण

अटल पूर्णांक rcar_drअगर_qbuf(काष्ठा rcar_drअगर *ch)
अणु
	काष्ठा rcar_drअगर_sdr *sdr = ch->sdr;
	dma_addr_t addr = ch->dma_handle;
	काष्ठा dma_async_tx_descriptor *rxd;
	dma_cookie_t cookie;
	पूर्णांक ret = -EIO;

	/* Setup cyclic DMA with given buffers */
	rxd = dmaengine_prep_dma_cyclic(ch->dmach, addr,
					sdr->hwbuf_size * RCAR_DRIF_NUM_HWBUFS,
					sdr->hwbuf_size, DMA_DEV_TO_MEM,
					DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!rxd) अणु
		rdrअगर_err(sdr, "ch%u: prep dma cyclic failed\n", ch->num);
		वापस ret;
	पूर्ण

	/* Submit descriptor */
	rxd->callback = rcar_drअगर_dma_complete;
	rxd->callback_param = ch;
	cookie = dmaengine_submit(rxd);
	अगर (dma_submit_error(cookie)) अणु
		rdrअगर_err(sdr, "ch%u: dma submit failed\n", ch->num);
		वापस ret;
	पूर्ण

	dma_async_issue_pending(ch->dmach);
	वापस 0;
पूर्ण

/* Enable reception */
अटल पूर्णांक rcar_drअगर_enable_rx(काष्ठा rcar_drअगर_sdr *sdr)
अणु
	अचिन्हित पूर्णांक i;
	u32 ctr;
	पूर्णांक ret = -EINVAL;

	/*
	 * When both पूर्णांकernal channels are enabled, they can be synchronized
	 * only by the master
	 */

	/* Enable receive */
	क्रम_each_rcar_drअगर_channel(i, &sdr->cur_ch_mask) अणु
		ctr = rcar_drअगर_पढ़ो(sdr->ch[i], RCAR_DRIF_SICTR);
		ctr |= (RCAR_DRIF_SICTR_RX_RISING_EDGE |
			 RCAR_DRIF_SICTR_RX_EN);
		rcar_drअगर_ग_लिखो(sdr->ch[i], RCAR_DRIF_SICTR, ctr);
	पूर्ण

	/* Check receive enabled */
	क्रम_each_rcar_drअगर_channel(i, &sdr->cur_ch_mask) अणु
		ret = पढ़ोl_poll_समयout(sdr->ch[i]->base + RCAR_DRIF_SICTR,
				ctr, ctr & RCAR_DRIF_SICTR_RX_EN, 7, 100000);
		अगर (ret) अणु
			rdrअगर_err(sdr, "ch%u: rx en failed. ctr 0x%08x\n", i,
				  rcar_drअगर_पढ़ो(sdr->ch[i], RCAR_DRIF_SICTR));
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/* Disable reception */
अटल व्योम rcar_drअगर_disable_rx(काष्ठा rcar_drअगर_sdr *sdr)
अणु
	अचिन्हित पूर्णांक i;
	u32 ctr;
	पूर्णांक ret;

	/* Disable receive */
	क्रम_each_rcar_drअगर_channel(i, &sdr->cur_ch_mask) अणु
		ctr = rcar_drअगर_पढ़ो(sdr->ch[i], RCAR_DRIF_SICTR);
		ctr &= ~RCAR_DRIF_SICTR_RX_EN;
		rcar_drअगर_ग_लिखो(sdr->ch[i], RCAR_DRIF_SICTR, ctr);
	पूर्ण

	/* Check receive disabled */
	क्रम_each_rcar_drअगर_channel(i, &sdr->cur_ch_mask) अणु
		ret = पढ़ोl_poll_समयout(sdr->ch[i]->base + RCAR_DRIF_SICTR,
				ctr, !(ctr & RCAR_DRIF_SICTR_RX_EN), 7, 100000);
		अगर (ret)
			dev_warn(&sdr->vdev->dev,
			"ch%u: failed to disable rx. ctr 0x%08x\n",
			i, rcar_drअगर_पढ़ो(sdr->ch[i], RCAR_DRIF_SICTR));
	पूर्ण
पूर्ण

/* Stop channel */
अटल व्योम rcar_drअगर_stop_channel(काष्ठा rcar_drअगर *ch)
अणु
	/* Disable DMA receive पूर्णांकerrupt */
	rcar_drअगर_ग_लिखो(ch, RCAR_DRIF_SIIER, 0x00000000);

	/* Terminate all DMA transfers */
	dmaengine_terminate_sync(ch->dmach);
पूर्ण

/* Stop receive operation */
अटल व्योम rcar_drअगर_stop(काष्ठा rcar_drअगर_sdr *sdr)
अणु
	अचिन्हित पूर्णांक i;

	/* Disable Rx */
	rcar_drअगर_disable_rx(sdr);

	क्रम_each_rcar_drअगर_channel(i, &sdr->cur_ch_mask)
		rcar_drअगर_stop_channel(sdr->ch[i]);
पूर्ण

/* Start channel */
अटल पूर्णांक rcar_drअगर_start_channel(काष्ठा rcar_drअगर *ch)
अणु
	काष्ठा rcar_drअगर_sdr *sdr = ch->sdr;
	u32 ctr, str;
	पूर्णांक ret;

	/* Reset receive */
	rcar_drअगर_ग_लिखो(ch, RCAR_DRIF_SICTR, RCAR_DRIF_SICTR_RESET);
	ret = पढ़ोl_poll_समयout(ch->base + RCAR_DRIF_SICTR, ctr,
				 !(ctr & RCAR_DRIF_SICTR_RESET), 7, 100000);
	अगर (ret) अणु
		rdrअगर_err(sdr, "ch%u: failed to reset rx. ctr 0x%08x\n",
			  ch->num, rcar_drअगर_पढ़ो(ch, RCAR_DRIF_SICTR));
		वापस ret;
	पूर्ण

	/* Queue buffers क्रम DMA */
	ret = rcar_drअगर_qbuf(ch);
	अगर (ret)
		वापस ret;

	/* Clear status रेजिस्टर flags */
	str = RCAR_DRIF_RFFUL | RCAR_DRIF_Rखातापूर्ण | RCAR_DRIF_RFSERR |
		RCAR_DRIF_RFUDF | RCAR_DRIF_RFOVF;
	rcar_drअगर_ग_लिखो(ch, RCAR_DRIF_SISTR, str);

	/* Enable DMA receive पूर्णांकerrupt */
	rcar_drअगर_ग_लिखो(ch, RCAR_DRIF_SIIER, 0x00009000);

	वापस ret;
पूर्ण

/* Start receive operation */
अटल पूर्णांक rcar_drअगर_start(काष्ठा rcar_drअगर_sdr *sdr)
अणु
	अचिन्हित दीर्घ enabled = 0;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम_each_rcar_drअगर_channel(i, &sdr->cur_ch_mask) अणु
		ret = rcar_drअगर_start_channel(sdr->ch[i]);
		अगर (ret)
			जाओ start_error;
		enabled |= BIT(i);
	पूर्ण

	ret = rcar_drअगर_enable_rx(sdr);
	अगर (ret)
		जाओ enable_error;

	sdr->produced = 0;
	वापस ret;

enable_error:
	rcar_drअगर_disable_rx(sdr);
start_error:
	क्रम_each_rcar_drअगर_channel(i, &enabled)
		rcar_drअगर_stop_channel(sdr->ch[i]);

	वापस ret;
पूर्ण

/* Start streaming */
अटल पूर्णांक rcar_drअगर_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा rcar_drअगर_sdr *sdr = vb2_get_drv_priv(vq);
	अचिन्हित दीर्घ enabled = 0;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	mutex_lock(&sdr->v4l2_mutex);

	क्रम_each_rcar_drअगर_channel(i, &sdr->cur_ch_mask) अणु
		ret = clk_prepare_enable(sdr->ch[i]->clk);
		अगर (ret)
			जाओ error;
		enabled |= BIT(i);
	पूर्ण

	/* Set शेष MDRx settings */
	rcar_drअगर_set_mdr1(sdr);

	/* Set new क्रमmat */
	ret = rcar_drअगर_set_क्रमmat(sdr);
	अगर (ret)
		जाओ error;

	अगर (sdr->num_cur_ch == RCAR_DRIF_MAX_CHANNEL)
		sdr->hwbuf_size = sdr->fmt->buffersize / RCAR_DRIF_MAX_CHANNEL;
	अन्यथा
		sdr->hwbuf_size = sdr->fmt->buffersize;

	rdrअगर_dbg(sdr, "num hwbufs %u, hwbuf_size %u\n",
		RCAR_DRIF_NUM_HWBUFS, sdr->hwbuf_size);

	/* Alloc DMA channel */
	ret = rcar_drअगर_alloc_dmachannels(sdr);
	अगर (ret)
		जाओ error;

	/* Request buffers */
	ret = rcar_drअगर_request_buf(sdr);
	अगर (ret)
		जाओ error;

	/* Start Rx */
	ret = rcar_drअगर_start(sdr);
	अगर (ret)
		जाओ error;

	mutex_unlock(&sdr->v4l2_mutex);

	वापस ret;

error:
	rcar_drअगर_release_queued_bufs(sdr, VB2_BUF_STATE_QUEUED);
	rcar_drअगर_release_buf(sdr);
	rcar_drअगर_release_dmachannels(sdr);
	क्रम_each_rcar_drअगर_channel(i, &enabled)
		clk_disable_unprepare(sdr->ch[i]->clk);

	mutex_unlock(&sdr->v4l2_mutex);

	वापस ret;
पूर्ण

/* Stop streaming */
अटल व्योम rcar_drअगर_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा rcar_drअगर_sdr *sdr = vb2_get_drv_priv(vq);
	अचिन्हित पूर्णांक i;

	mutex_lock(&sdr->v4l2_mutex);

	/* Stop hardware streaming */
	rcar_drअगर_stop(sdr);

	/* Return all queued buffers to vb2 */
	rcar_drअगर_release_queued_bufs(sdr, VB2_BUF_STATE_ERROR);

	/* Release buf */
	rcar_drअगर_release_buf(sdr);

	/* Release DMA channel resources */
	rcar_drअगर_release_dmachannels(sdr);

	क्रम_each_rcar_drअगर_channel(i, &sdr->cur_ch_mask)
		clk_disable_unprepare(sdr->ch[i]->clk);

	mutex_unlock(&sdr->v4l2_mutex);
पूर्ण

/* Vb2 ops */
अटल स्थिर काष्ठा vb2_ops rcar_drअगर_vb2_ops = अणु
	.queue_setup            = rcar_drअगर_queue_setup,
	.buf_queue              = rcar_drअगर_buf_queue,
	.start_streaming        = rcar_drअगर_start_streaming,
	.stop_streaming         = rcar_drअगर_stop_streaming,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

अटल पूर्णांक rcar_drअगर_querycap(काष्ठा file *file, व्योम *fh,
			      काष्ठा v4l2_capability *cap)
अणु
	काष्ठा rcar_drअगर_sdr *sdr = video_drvdata(file);

	strscpy(cap->driver, KBUILD_MODNAME, माप(cap->driver));
	strscpy(cap->card, sdr->vdev->name, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "platform:%s",
		 sdr->vdev->name);

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_drअगर_set_शेष_क्रमmat(काष्ठा rcar_drअगर_sdr *sdr)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats); i++) अणु
		/* Matching fmt based on required channels is set as शेष */
		अगर (sdr->num_hw_ch == क्रमmats[i].num_ch) अणु
			sdr->fmt = &क्रमmats[i];
			sdr->cur_ch_mask = sdr->hw_ch_mask;
			sdr->num_cur_ch = sdr->num_hw_ch;
			dev_dbg(sdr->dev, "default fmt[%u]: mask %lu num %u\n",
				i, sdr->cur_ch_mask, sdr->num_cur_ch);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक rcar_drअगर_क्रमागत_fmt_sdr_cap(काष्ठा file *file, व्योम *priv,
				      काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index >= ARRAY_SIZE(क्रमmats))
		वापस -EINVAL;

	f->pixelक्रमmat = क्रमmats[f->index].pixelक्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_drअगर_g_fmt_sdr_cap(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा rcar_drअगर_sdr *sdr = video_drvdata(file);

	f->fmt.sdr.pixelक्रमmat = sdr->fmt->pixelक्रमmat;
	f->fmt.sdr.buffersize = sdr->fmt->buffersize;

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_drअगर_s_fmt_sdr_cap(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा rcar_drअगर_sdr *sdr = video_drvdata(file);
	काष्ठा vb2_queue *q = &sdr->vb_queue;
	अचिन्हित पूर्णांक i;

	अगर (vb2_is_busy(q))
		वापस -EBUSY;

	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats); i++) अणु
		अगर (क्रमmats[i].pixelक्रमmat == f->fmt.sdr.pixelक्रमmat)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(क्रमmats))
		i = 0;		/* Set the 1st क्रमmat as शेष on no match */

	sdr->fmt = &क्रमmats[i];
	f->fmt.sdr.pixelक्रमmat = sdr->fmt->pixelक्रमmat;
	f->fmt.sdr.buffersize = क्रमmats[i].buffersize;
	स_रखो(f->fmt.sdr.reserved, 0, माप(f->fmt.sdr.reserved));

	/*
	 * If a क्रमmat demands one channel only out of two
	 * enabled channels, pick the 0th channel.
	 */
	अगर (क्रमmats[i].num_ch < sdr->num_hw_ch) अणु
		sdr->cur_ch_mask = BIT(0);
		sdr->num_cur_ch = क्रमmats[i].num_ch;
	पूर्ण अन्यथा अणु
		sdr->cur_ch_mask = sdr->hw_ch_mask;
		sdr->num_cur_ch = sdr->num_hw_ch;
	पूर्ण

	rdrअगर_dbg(sdr, "cur: idx %u mask %lu num %u\n",
		  i, sdr->cur_ch_mask, sdr->num_cur_ch);

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_drअगर_try_fmt_sdr_cap(काष्ठा file *file, व्योम *priv,
				     काष्ठा v4l2_क्रमmat *f)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats); i++) अणु
		अगर (क्रमmats[i].pixelक्रमmat == f->fmt.sdr.pixelक्रमmat) अणु
			f->fmt.sdr.buffersize = क्रमmats[i].buffersize;
			वापस 0;
		पूर्ण
	पूर्ण

	f->fmt.sdr.pixelक्रमmat = क्रमmats[0].pixelक्रमmat;
	f->fmt.sdr.buffersize = क्रमmats[0].buffersize;
	स_रखो(f->fmt.sdr.reserved, 0, माप(f->fmt.sdr.reserved));

	वापस 0;
पूर्ण

/* Tuner subdev ioctls */
अटल पूर्णांक rcar_drअगर_क्रमागत_freq_bands(काष्ठा file *file, व्योम *priv,
				     काष्ठा v4l2_frequency_band *band)
अणु
	काष्ठा rcar_drअगर_sdr *sdr = video_drvdata(file);

	वापस v4l2_subdev_call(sdr->ep.subdev, tuner, क्रमागत_freq_bands, band);
पूर्ण

अटल पूर्णांक rcar_drअगर_g_frequency(काष्ठा file *file, व्योम *priv,
				 काष्ठा v4l2_frequency *f)
अणु
	काष्ठा rcar_drअगर_sdr *sdr = video_drvdata(file);

	वापस v4l2_subdev_call(sdr->ep.subdev, tuner, g_frequency, f);
पूर्ण

अटल पूर्णांक rcar_drअगर_s_frequency(काष्ठा file *file, व्योम *priv,
				 स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा rcar_drअगर_sdr *sdr = video_drvdata(file);

	वापस v4l2_subdev_call(sdr->ep.subdev, tuner, s_frequency, f);
पूर्ण

अटल पूर्णांक rcar_drअगर_g_tuner(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा rcar_drअगर_sdr *sdr = video_drvdata(file);

	वापस v4l2_subdev_call(sdr->ep.subdev, tuner, g_tuner, vt);
पूर्ण

अटल पूर्णांक rcar_drअगर_s_tuner(काष्ठा file *file, व्योम *priv,
			     स्थिर काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा rcar_drअगर_sdr *sdr = video_drvdata(file);

	वापस v4l2_subdev_call(sdr->ep.subdev, tuner, s_tuner, vt);
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops rcar_drअगर_ioctl_ops = अणु
	.vidioc_querycap          = rcar_drअगर_querycap,

	.vidioc_क्रमागत_fmt_sdr_cap  = rcar_drअगर_क्रमागत_fmt_sdr_cap,
	.vidioc_g_fmt_sdr_cap     = rcar_drअगर_g_fmt_sdr_cap,
	.vidioc_s_fmt_sdr_cap     = rcar_drअगर_s_fmt_sdr_cap,
	.vidioc_try_fmt_sdr_cap   = rcar_drअगर_try_fmt_sdr_cap,

	.vidioc_reqbufs           = vb2_ioctl_reqbufs,
	.vidioc_create_bufs       = vb2_ioctl_create_bufs,
	.vidioc_prepare_buf       = vb2_ioctl_prepare_buf,
	.vidioc_querybuf          = vb2_ioctl_querybuf,
	.vidioc_qbuf              = vb2_ioctl_qbuf,
	.vidioc_dqbuf             = vb2_ioctl_dqbuf,

	.vidioc_streamon          = vb2_ioctl_streamon,
	.vidioc_streamoff         = vb2_ioctl_streamoff,

	.vidioc_s_frequency       = rcar_drअगर_s_frequency,
	.vidioc_g_frequency       = rcar_drअगर_g_frequency,
	.vidioc_s_tuner		  = rcar_drअगर_s_tuner,
	.vidioc_g_tuner		  = rcar_drअगर_g_tuner,
	.vidioc_क्रमागत_freq_bands   = rcar_drअगर_क्रमागत_freq_bands,
	.vidioc_subscribe_event   = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
	.vidioc_log_status        = v4l2_ctrl_log_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations rcar_drअगर_fops = अणु
	.owner                    = THIS_MODULE,
	.खोलो                     = v4l2_fh_खोलो,
	.release                  = vb2_fop_release,
	.पढ़ो                     = vb2_fop_पढ़ो,
	.poll                     = vb2_fop_poll,
	.mmap                     = vb2_fop_mmap,
	.unlocked_ioctl           = video_ioctl2,
पूर्ण;

अटल पूर्णांक rcar_drअगर_sdr_रेजिस्टर(काष्ठा rcar_drअगर_sdr *sdr)
अणु
	पूर्णांक ret;

	/* Init video_device काष्ठाure */
	sdr->vdev = video_device_alloc();
	अगर (!sdr->vdev)
		वापस -ENOMEM;

	snम_लिखो(sdr->vdev->name, माप(sdr->vdev->name), "R-Car DRIF");
	sdr->vdev->fops = &rcar_drअगर_fops;
	sdr->vdev->ioctl_ops = &rcar_drअगर_ioctl_ops;
	sdr->vdev->release = video_device_release;
	sdr->vdev->lock = &sdr->v4l2_mutex;
	sdr->vdev->queue = &sdr->vb_queue;
	sdr->vdev->queue->lock = &sdr->vb_queue_mutex;
	sdr->vdev->ctrl_handler = &sdr->ctrl_hdl;
	sdr->vdev->v4l2_dev = &sdr->v4l2_dev;
	sdr->vdev->device_caps = V4L2_CAP_SDR_CAPTURE | V4L2_CAP_TUNER |
		V4L2_CAP_STREAMING | V4L2_CAP_READWRITE;
	video_set_drvdata(sdr->vdev, sdr);

	/* Register V4L2 SDR device */
	ret = video_रेजिस्टर_device(sdr->vdev, VFL_TYPE_SDR, -1);
	अगर (ret) अणु
		video_device_release(sdr->vdev);
		sdr->vdev = शून्य;
		dev_err(sdr->dev, "failed video_register_device (%d)\n", ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम rcar_drअगर_sdr_unरेजिस्टर(काष्ठा rcar_drअगर_sdr *sdr)
अणु
	video_unरेजिस्टर_device(sdr->vdev);
	sdr->vdev = शून्य;
पूर्ण

/* Sub-device bound callback */
अटल पूर्णांक rcar_drअगर_notअगरy_bound(काष्ठा v4l2_async_notअगरier *notअगरier,
				   काष्ठा v4l2_subdev *subdev,
				   काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा rcar_drअगर_sdr *sdr =
		container_of(notअगरier, काष्ठा rcar_drअगर_sdr, notअगरier);

	v4l2_set_subdev_hostdata(subdev, sdr);
	sdr->ep.subdev = subdev;
	rdrअगर_dbg(sdr, "bound asd %s\n", subdev->name);

	वापस 0;
पूर्ण

/* Sub-device unbind callback */
अटल व्योम rcar_drअगर_notअगरy_unbind(काष्ठा v4l2_async_notअगरier *notअगरier,
				   काष्ठा v4l2_subdev *subdev,
				   काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा rcar_drअगर_sdr *sdr =
		container_of(notअगरier, काष्ठा rcar_drअगर_sdr, notअगरier);

	अगर (sdr->ep.subdev != subdev) अणु
		rdrअगर_err(sdr, "subdev %s is not bound\n", subdev->name);
		वापस;
	पूर्ण

	/* Free ctrl handler अगर initialized */
	v4l2_ctrl_handler_मुक्त(&sdr->ctrl_hdl);
	sdr->v4l2_dev.ctrl_handler = शून्य;
	sdr->ep.subdev = शून्य;

	rcar_drअगर_sdr_unरेजिस्टर(sdr);
	rdrअगर_dbg(sdr, "unbind asd %s\n", subdev->name);
पूर्ण

/* Sub-device रेजिस्टरed notअगरication callback */
अटल पूर्णांक rcar_drअगर_notअगरy_complete(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	काष्ठा rcar_drअगर_sdr *sdr =
		container_of(notअगरier, काष्ठा rcar_drअगर_sdr, notअगरier);
	पूर्णांक ret;

	/*
	 * The subdev tested at this poपूर्णांक uses 4 controls. Using 10 as a worst
	 * हाल scenario hपूर्णांक. When less controls are needed there will be some
	 * unused memory and when more controls are needed the framework uses
	 * hash to manage controls within this number.
	 */
	ret = v4l2_ctrl_handler_init(&sdr->ctrl_hdl, 10);
	अगर (ret)
		वापस -ENOMEM;

	sdr->v4l2_dev.ctrl_handler = &sdr->ctrl_hdl;
	ret = v4l2_device_रेजिस्टर_subdev_nodes(&sdr->v4l2_dev);
	अगर (ret) अणु
		rdrअगर_err(sdr, "failed: register subdev nodes ret %d\n", ret);
		जाओ error;
	पूर्ण

	ret = v4l2_ctrl_add_handler(&sdr->ctrl_hdl,
				    sdr->ep.subdev->ctrl_handler, शून्य, true);
	अगर (ret) अणु
		rdrअगर_err(sdr, "failed: ctrl add hdlr ret %d\n", ret);
		जाओ error;
	पूर्ण

	ret = rcar_drअगर_sdr_रेजिस्टर(sdr);
	अगर (ret)
		जाओ error;

	वापस ret;

error:
	v4l2_ctrl_handler_मुक्त(&sdr->ctrl_hdl);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_async_notअगरier_operations rcar_drअगर_notअगरy_ops = अणु
	.bound = rcar_drअगर_notअगरy_bound,
	.unbind = rcar_drअगर_notअगरy_unbind,
	.complete = rcar_drअगर_notअगरy_complete,
पूर्ण;

/* Read endpoपूर्णांक properties */
अटल व्योम rcar_drअगर_get_ep_properties(काष्ठा rcar_drअगर_sdr *sdr,
					काष्ठा fwnode_handle *fwnode)
अणु
	u32 val;

	/* Set the I2S शेषs क्रम SIRMDR1*/
	sdr->mdr1 = RCAR_DRIF_SIRMDR1_SYNCMD_LR | RCAR_DRIF_SIRMDR1_MSB_FIRST |
		RCAR_DRIF_SIRMDR1_DTDL_1 | RCAR_DRIF_SIRMDR1_SYNCDL_0;

	/* Parse sync polarity from endpoपूर्णांक */
	अगर (!fwnode_property_पढ़ो_u32(fwnode, "sync-active", &val))
		sdr->mdr1 |= val ? RCAR_DRIF_SIRMDR1_SYNCAC_POL_HIGH :
			RCAR_DRIF_SIRMDR1_SYNCAC_POL_LOW;
	अन्यथा
		sdr->mdr1 |= RCAR_DRIF_SIRMDR1_SYNCAC_POL_HIGH; /* शेष */

	dev_dbg(sdr->dev, "mdr1 0x%08x\n", sdr->mdr1);
पूर्ण

/* Parse sub-devs (tuner) to find a matching device */
अटल पूर्णांक rcar_drअगर_parse_subdevs(काष्ठा rcar_drअगर_sdr *sdr)
अणु
	काष्ठा v4l2_async_notअगरier *notअगरier = &sdr->notअगरier;
	काष्ठा fwnode_handle *fwnode, *ep;
	काष्ठा v4l2_async_subdev *asd;

	v4l2_async_notअगरier_init(notअगरier);

	ep = fwnode_graph_get_next_endpoपूर्णांक(of_fwnode_handle(sdr->dev->of_node),
					    शून्य);
	अगर (!ep)
		वापस 0;

	/* Get the endpoपूर्णांक properties */
	rcar_drअगर_get_ep_properties(sdr, ep);

	fwnode = fwnode_graph_get_remote_port_parent(ep);
	fwnode_handle_put(ep);
	अगर (!fwnode) अणु
		dev_warn(sdr->dev, "bad remote port parent\n");
		वापस -EINVAL;
	पूर्ण

	asd = v4l2_async_notअगरier_add_fwnode_subdev(notअगरier, fwnode,
						    काष्ठा v4l2_async_subdev);
	fwnode_handle_put(fwnode);
	अगर (IS_ERR(asd))
		वापस PTR_ERR(asd);

	वापस 0;
पूर्ण

/* Check अगर the given device is the primary bond */
अटल bool rcar_drअगर_primary_bond(काष्ठा platक्रमm_device *pdev)
अणु
	वापस of_property_पढ़ो_bool(pdev->dev.of_node, "renesas,primary-bond");
पूर्ण

/* Check अगर both devices of the bond are enabled */
अटल काष्ठा device_node *rcar_drअगर_bond_enabled(काष्ठा platक्रमm_device *p)
अणु
	काष्ठा device_node *np;

	np = of_parse_phandle(p->dev.of_node, "renesas,bonding", 0);
	अगर (np && of_device_is_available(np))
		वापस np;

	वापस शून्य;
पूर्ण

/* Check अगर the bonded device is probed */
अटल पूर्णांक rcar_drअगर_bond_available(काष्ठा rcar_drअगर_sdr *sdr,
				    काष्ठा device_node *np)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा rcar_drअगर *ch;
	पूर्णांक ret = 0;

	pdev = of_find_device_by_node(np);
	अगर (!pdev) अणु
		dev_err(sdr->dev, "failed to get bonded device from node\n");
		वापस -ENODEV;
	पूर्ण

	device_lock(&pdev->dev);
	ch = platक्रमm_get_drvdata(pdev);
	अगर (ch) अणु
		/* Update sdr data in the bonded device */
		ch->sdr = sdr;

		/* Update sdr with bonded device data */
		sdr->ch[ch->num] = ch;
		sdr->hw_ch_mask |= BIT(ch->num);
	पूर्ण अन्यथा अणु
		/* Defer */
		dev_info(sdr->dev, "defer probe\n");
		ret = -EPROBE_DEFER;
	पूर्ण
	device_unlock(&pdev->dev);

	put_device(&pdev->dev);

	वापस ret;
पूर्ण

/* V4L2 SDR device probe */
अटल पूर्णांक rcar_drअगर_sdr_probe(काष्ठा rcar_drअगर_sdr *sdr)
अणु
	पूर्णांक ret;

	/* Validate any supported क्रमmat क्रम enabled channels */
	ret = rcar_drअगर_set_शेष_क्रमmat(sdr);
	अगर (ret) अणु
		dev_err(sdr->dev, "failed to set default format\n");
		वापस ret;
	पूर्ण

	/* Set शेषs */
	sdr->hwbuf_size = RCAR_DRIF_DEFAULT_HWBUF_SIZE;

	mutex_init(&sdr->v4l2_mutex);
	mutex_init(&sdr->vb_queue_mutex);
	spin_lock_init(&sdr->queued_bufs_lock);
	spin_lock_init(&sdr->dma_lock);
	INIT_LIST_HEAD(&sdr->queued_bufs);

	/* Init videobuf2 queue काष्ठाure */
	sdr->vb_queue.type = V4L2_BUF_TYPE_SDR_CAPTURE;
	sdr->vb_queue.io_modes = VB2_READ | VB2_MMAP | VB2_DMABUF;
	sdr->vb_queue.drv_priv = sdr;
	sdr->vb_queue.buf_काष्ठा_size = माप(काष्ठा rcar_drअगर_frame_buf);
	sdr->vb_queue.ops = &rcar_drअगर_vb2_ops;
	sdr->vb_queue.mem_ops = &vb2_vदो_स्मृति_memops;
	sdr->vb_queue.बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;

	/* Init videobuf2 queue */
	ret = vb2_queue_init(&sdr->vb_queue);
	अगर (ret) अणु
		dev_err(sdr->dev, "failed: vb2_queue_init ret %d\n", ret);
		वापस ret;
	पूर्ण

	/* Register the v4l2_device */
	ret = v4l2_device_रेजिस्टर(sdr->dev, &sdr->v4l2_dev);
	अगर (ret) अणु
		dev_err(sdr->dev, "failed: v4l2_device_register ret %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * Parse subdevs after v4l2_device_रेजिस्टर because अगर the subdev
	 * is alपढ़ोy probed, bound and complete will be called immediately
	 */
	ret = rcar_drअगर_parse_subdevs(sdr);
	अगर (ret)
		जाओ error;

	sdr->notअगरier.ops = &rcar_drअगर_notअगरy_ops;

	/* Register notअगरier */
	ret = v4l2_async_notअगरier_रेजिस्टर(&sdr->v4l2_dev, &sdr->notअगरier);
	अगर (ret < 0) अणु
		dev_err(sdr->dev, "failed: notifier register ret %d\n", ret);
		जाओ cleanup;
	पूर्ण

	वापस ret;

cleanup:
	v4l2_async_notअगरier_cleanup(&sdr->notअगरier);
error:
	v4l2_device_unरेजिस्टर(&sdr->v4l2_dev);

	वापस ret;
पूर्ण

/* V4L2 SDR device हटाओ */
अटल व्योम rcar_drअगर_sdr_हटाओ(काष्ठा rcar_drअगर_sdr *sdr)
अणु
	v4l2_async_notअगरier_unरेजिस्टर(&sdr->notअगरier);
	v4l2_async_notअगरier_cleanup(&sdr->notअगरier);
	v4l2_device_unरेजिस्टर(&sdr->v4l2_dev);
पूर्ण

/* DRIF channel probe */
अटल पूर्णांक rcar_drअगर_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rcar_drअगर_sdr *sdr;
	काष्ठा device_node *np;
	काष्ठा rcar_drअगर *ch;
	काष्ठा resource	*res;
	पूर्णांक ret;

	/* Reserve memory क्रम enabled channel */
	ch = devm_kzalloc(&pdev->dev, माप(*ch), GFP_KERNEL);
	अगर (!ch)
		वापस -ENOMEM;

	ch->pdev = pdev;

	/* Module घड़ी */
	ch->clk = devm_clk_get(&pdev->dev, "fck");
	अगर (IS_ERR(ch->clk)) अणु
		ret = PTR_ERR(ch->clk);
		dev_err(&pdev->dev, "clk get failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	/* Register map */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ch->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(ch->base))
		वापस PTR_ERR(ch->base);

	ch->start = res->start;
	platक्रमm_set_drvdata(pdev, ch);

	/* Check अगर both channels of the bond are enabled */
	np = rcar_drअगर_bond_enabled(pdev);
	अगर (np) अणु
		/* Check अगर current channel acting as primary-bond */
		अगर (!rcar_drअगर_primary_bond(pdev)) अणु
			ch->num = 1;	/* Primary bond is channel 0 always */
			of_node_put(np);
			वापस 0;
		पूर्ण
	पूर्ण

	/* Reserve memory क्रम SDR काष्ठाure */
	sdr = devm_kzalloc(&pdev->dev, माप(*sdr), GFP_KERNEL);
	अगर (!sdr) अणु
		of_node_put(np);
		वापस -ENOMEM;
	पूर्ण
	ch->sdr = sdr;
	sdr->dev = &pdev->dev;

	/* Establish links between SDR and channel(s) */
	sdr->ch[ch->num] = ch;
	sdr->hw_ch_mask = BIT(ch->num);
	अगर (np) अणु
		/* Check अगर bonded device is पढ़ोy */
		ret = rcar_drअगर_bond_available(sdr, np);
		of_node_put(np);
		अगर (ret)
			वापस ret;
	पूर्ण
	sdr->num_hw_ch = hweight_दीर्घ(sdr->hw_ch_mask);

	वापस rcar_drअगर_sdr_probe(sdr);
पूर्ण

/* DRIF channel हटाओ */
अटल पूर्णांक rcar_drअगर_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rcar_drअगर *ch = platक्रमm_get_drvdata(pdev);
	काष्ठा rcar_drअगर_sdr *sdr = ch->sdr;

	/* Channel 0 will be the SDR instance */
	अगर (ch->num)
		वापस 0;

	/* SDR instance */
	rcar_drअगर_sdr_हटाओ(sdr);

	वापस 0;
पूर्ण

/* FIXME: Implement suspend/resume support */
अटल पूर्णांक __maybe_unused rcar_drअगर_suspend(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rcar_drअगर_resume(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(rcar_drअगर_pm_ops, rcar_drअगर_suspend,
			 rcar_drअगर_resume);

अटल स्थिर काष्ठा of_device_id rcar_drअगर_of_table[] = अणु
	अणु .compatible = "renesas,rcar-gen3-drif" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rcar_drअगर_of_table);

#घोषणा RCAR_DRIF_DRV_NAME "rcar_drif"
अटल काष्ठा platक्रमm_driver rcar_drअगर_driver = अणु
	.driver = अणु
		.name = RCAR_DRIF_DRV_NAME,
		.of_match_table = of_match_ptr(rcar_drअगर_of_table),
		.pm = &rcar_drअगर_pm_ops,
		पूर्ण,
	.probe = rcar_drअगर_probe,
	.हटाओ = rcar_drअगर_हटाओ,
पूर्ण;

module_platक्रमm_driver(rcar_drअगर_driver);

MODULE_DESCRIPTION("Renesas R-Car Gen3 DRIF driver");
MODULE_ALIAS("platform:" RCAR_DRIF_DRV_NAME);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ramesh Shanmugasundaram <ramesh.shanmugasundaram@bp.renesas.com>");
