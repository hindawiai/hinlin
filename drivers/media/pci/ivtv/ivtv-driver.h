<शैली गुरु>
/*
    ivtv driver पूर्णांकernal defines and काष्ठाures
    Copyright (C) 2003-2004  Kevin Thayer <nufan_wfk at yahoo.com>
    Copyright (C) 2004  Chris Kennedy <c@groovy.org>
    Copyright (C) 2005-2007  Hans Verkuil <hverkuil@xs4all.nl>

    This program is मुक्त software; you can redistribute it and/or modअगरy
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License क्रम more details.

    You should have received a copy of the GNU General Public License
    aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#अगर_अघोषित IVTV_DRIVER_H
#घोषणा IVTV_DRIVER_H

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

/* Internal header क्रम ivtv project:
 * Driver क्रम the cx23415/6 chip.
 * Author: Kevin Thayer (nufan_wfk at yahoo.com)
 * License: GPL
 *
 * -----
 * MPG600/MPG160 support by  T.Adachi <tadachi@tadachi-net.com>
 *                      and Takeru KOMORIYA<komoriya@paken.org>
 *
 * AVerMedia M179 GPIO info by Chris Pinkham <cpinkham@bc2va.org>
 *                using inक्रमmation provided by Jiun-Kuei Jung @ AVerMedia.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/fs.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <linux/list.h>
#समावेश <linux/unistd.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/byteorder.h>

#समावेश <linux/dvb/video.h>
#समावेश <linux/dvb/audपन.स>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/tuner.h>
#समावेश <media/drv-पूर्णांकf/cx2341x.h>
#समावेश <media/i2c/ir-kbd-i2c.h>

#समावेश <linux/ivtv.h>

/* Memory layout */
#घोषणा IVTV_ENCODER_OFFSET	0x00000000
#घोषणा IVTV_ENCODER_SIZE	0x00800000	/* Total size is 0x01000000, but only first half is used */
#घोषणा IVTV_DECODER_OFFSET	0x01000000
#घोषणा IVTV_DECODER_SIZE	0x00800000	/* Total size is 0x01000000, but only first half is used */
#घोषणा IVTV_REG_OFFSET		0x02000000
#घोषणा IVTV_REG_SIZE		0x00010000

/* Maximum ivtv driver instances. Some people have a huge number of
   capture cards, so set this to a high value. */
#घोषणा IVTV_MAX_CARDS 32

#घोषणा IVTV_ENC_STREAM_TYPE_MPG  0
#घोषणा IVTV_ENC_STREAM_TYPE_YUV  1
#घोषणा IVTV_ENC_STREAM_TYPE_VBI  2
#घोषणा IVTV_ENC_STREAM_TYPE_PCM  3
#घोषणा IVTV_ENC_STREAM_TYPE_RAD  4
#घोषणा IVTV_DEC_STREAM_TYPE_MPG  5
#घोषणा IVTV_DEC_STREAM_TYPE_VBI  6
#घोषणा IVTV_DEC_STREAM_TYPE_VOUT 7
#घोषणा IVTV_DEC_STREAM_TYPE_YUV  8
#घोषणा IVTV_MAX_STREAMS	  9

#घोषणा IVTV_DMA_SG_OSD_ENT	(2883584/PAGE_SIZE)	/* sg entities */

/* DMA Registers */
#घोषणा IVTV_REG_DMAXFER	(0x0000)
#घोषणा IVTV_REG_DMASTATUS	(0x0004)
#घोषणा IVTV_REG_DECDMAADDR	(0x0008)
#घोषणा IVTV_REG_ENCDMAADDR	(0x000c)
#घोषणा IVTV_REG_DMACONTROL	(0x0010)
#घोषणा IVTV_REG_IRQSTATUS	(0x0040)
#घोषणा IVTV_REG_IRQMASK	(0x0048)

/* Setup Registers */
#घोषणा IVTV_REG_ENC_SDRAM_REFRESH	(0x07F8)
#घोषणा IVTV_REG_ENC_SDRAM_PRECHARGE	(0x07FC)
#घोषणा IVTV_REG_DEC_SDRAM_REFRESH	(0x08F8)
#घोषणा IVTV_REG_DEC_SDRAM_PRECHARGE	(0x08FC)
#घोषणा IVTV_REG_VDM			(0x2800)
#घोषणा IVTV_REG_AO			(0x2D00)
#घोषणा IVTV_REG_BYTEFLUSH		(0x2D24)
#घोषणा IVTV_REG_SPU			(0x9050)
#घोषणा IVTV_REG_HW_BLOCKS		(0x9054)
#घोषणा IVTV_REG_VPU			(0x9058)
#घोषणा IVTV_REG_APU			(0xA064)

/* Other रेजिस्टरs */
#घोषणा IVTV_REG_DEC_LINE_FIELD		(0x28C0)

/* debugging */
बाह्य पूर्णांक ivtv_debug;
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
बाह्य पूर्णांक ivtv_fw_debug;
#पूर्ण_अगर

#घोषणा IVTV_DBGFLG_WARN    (1 << 0)
#घोषणा IVTV_DBGFLG_INFO    (1 << 1)
#घोषणा IVTV_DBGFLG_MB      (1 << 2)
#घोषणा IVTV_DBGFLG_IOCTL   (1 << 3)
#घोषणा IVTV_DBGFLG_खाता    (1 << 4)
#घोषणा IVTV_DBGFLG_DMA     (1 << 5)
#घोषणा IVTV_DBGFLG_IRQ     (1 << 6)
#घोषणा IVTV_DBGFLG_DEC     (1 << 7)
#घोषणा IVTV_DBGFLG_YUV     (1 << 8)
#घोषणा IVTV_DBGFLG_I2C     (1 << 9)
/* Flag to turn on high volume debugging */
#घोषणा IVTV_DBGFLG_HIGHVOL (1 << 10)

#घोषणा IVTV_DEBUG(x, type, fmt, args...) \
	करो अणु \
		अगर ((x) & ivtv_debug) \
			v4l2_info(&itv->v4l2_dev, " " type ": " fmt , ##args);	\
	पूर्ण जबतक (0)
#घोषणा IVTV_DEBUG_WARN(fmt, args...)  IVTV_DEBUG(IVTV_DBGFLG_WARN,  "warn",  fmt , ## args)
#घोषणा IVTV_DEBUG_INFO(fmt, args...)  IVTV_DEBUG(IVTV_DBGFLG_INFO,  "info",  fmt , ## args)
#घोषणा IVTV_DEBUG_MB(fmt, args...)    IVTV_DEBUG(IVTV_DBGFLG_MB,    "mb",    fmt , ## args)
#घोषणा IVTV_DEBUG_DMA(fmt, args...)   IVTV_DEBUG(IVTV_DBGFLG_DMA,   "dma",   fmt , ## args)
#घोषणा IVTV_DEBUG_IOCTL(fmt, args...) IVTV_DEBUG(IVTV_DBGFLG_IOCTL, "ioctl", fmt , ## args)
#घोषणा IVTV_DEBUG_खाता(fmt, args...)  IVTV_DEBUG(IVTV_DBGFLG_खाता,  "file",  fmt , ## args)
#घोषणा IVTV_DEBUG_I2C(fmt, args...)   IVTV_DEBUG(IVTV_DBGFLG_I2C,   "i2c",   fmt , ## args)
#घोषणा IVTV_DEBUG_IRQ(fmt, args...)   IVTV_DEBUG(IVTV_DBGFLG_IRQ,   "irq",   fmt , ## args)
#घोषणा IVTV_DEBUG_DEC(fmt, args...)   IVTV_DEBUG(IVTV_DBGFLG_DEC,   "dec",   fmt , ## args)
#घोषणा IVTV_DEBUG_YUV(fmt, args...)   IVTV_DEBUG(IVTV_DBGFLG_YUV,   "yuv",   fmt , ## args)

#घोषणा IVTV_DEBUG_HIGH_VOL(x, type, fmt, args...) \
	करो अणु \
		अगर (((x) & ivtv_debug) && (ivtv_debug & IVTV_DBGFLG_HIGHVOL))	\
			v4l2_info(&itv->v4l2_dev, " " type ": " fmt , ##args);	\
	पूर्ण जबतक (0)
#घोषणा IVTV_DEBUG_HI_WARN(fmt, args...)  IVTV_DEBUG_HIGH_VOL(IVTV_DBGFLG_WARN,  "warn",  fmt , ## args)
#घोषणा IVTV_DEBUG_HI_INFO(fmt, args...)  IVTV_DEBUG_HIGH_VOL(IVTV_DBGFLG_INFO,  "info",  fmt , ## args)
#घोषणा IVTV_DEBUG_HI_MB(fmt, args...)    IVTV_DEBUG_HIGH_VOL(IVTV_DBGFLG_MB,    "mb",    fmt , ## args)
#घोषणा IVTV_DEBUG_HI_DMA(fmt, args...)   IVTV_DEBUG_HIGH_VOL(IVTV_DBGFLG_DMA,   "dma",   fmt , ## args)
#घोषणा IVTV_DEBUG_HI_IOCTL(fmt, args...) IVTV_DEBUG_HIGH_VOL(IVTV_DBGFLG_IOCTL, "ioctl", fmt , ## args)
#घोषणा IVTV_DEBUG_HI_खाता(fmt, args...)  IVTV_DEBUG_HIGH_VOL(IVTV_DBGFLG_खाता,  "file",  fmt , ## args)
#घोषणा IVTV_DEBUG_HI_I2C(fmt, args...)   IVTV_DEBUG_HIGH_VOL(IVTV_DBGFLG_I2C,   "i2c",   fmt , ## args)
#घोषणा IVTV_DEBUG_HI_IRQ(fmt, args...)   IVTV_DEBUG_HIGH_VOL(IVTV_DBGFLG_IRQ,   "irq",   fmt , ## args)
#घोषणा IVTV_DEBUG_HI_DEC(fmt, args...)   IVTV_DEBUG_HIGH_VOL(IVTV_DBGFLG_DEC,   "dec",   fmt , ## args)
#घोषणा IVTV_DEBUG_HI_YUV(fmt, args...)   IVTV_DEBUG_HIGH_VOL(IVTV_DBGFLG_YUV,   "yuv",   fmt , ## args)

/* Standard kernel messages */
#घोषणा IVTV_ERR(fmt, args...)      v4l2_err(&itv->v4l2_dev, fmt , ## args)
#घोषणा IVTV_WARN(fmt, args...)     v4l2_warn(&itv->v4l2_dev, fmt , ## args)
#घोषणा IVTV_INFO(fmt, args...)     v4l2_info(&itv->v4l2_dev, fmt , ## args)

/* output modes (cx23415 only) */
#घोषणा OUT_NONE        0
#घोषणा OUT_MPG         1
#घोषणा OUT_YUV         2
#घोषणा OUT_UDMA_YUV    3
#घोषणा OUT_PASSTHROUGH 4

#घोषणा IVTV_MAX_PGM_INDEX (400)

/* Default I2C SCL period in microseconds */
#घोषणा IVTV_DEFAULT_I2C_CLOCK_PERIOD	20

काष्ठा ivtv_options अणु
	पूर्णांक kilobytes[IVTV_MAX_STREAMS];        /* size in kilobytes of each stream */
	पूर्णांक cardtype;				/* क्रमce card type on load */
	पूर्णांक tuner;				/* set tuner on load */
	पूर्णांक radio;				/* enable/disable radio */
	पूर्णांक newi2c;				/* new I2C algorithm */
	पूर्णांक i2c_घड़ी_period;			/* period of SCL क्रम I2C bus */
पूर्ण;

/* ivtv-specअगरic mailbox ढाँचा */
काष्ठा ivtv_mailbox अणु
	u32 flags;
	u32 cmd;
	u32 retval;
	u32 समयout;
	u32 data[CX2341X_MBOX_MAX_DATA];
पूर्ण;

काष्ठा ivtv_api_cache अणु
	अचिन्हित दीर्घ last_jअगरfies;		/* when last command was issued */
	u32 data[CX2341X_MBOX_MAX_DATA];	/* last sent api data */
पूर्ण;

काष्ठा ivtv_mailbox_data अणु
	अस्थिर काष्ठा ivtv_mailbox __iomem *mbox;
	/* Bits 0-2 are क्रम the encoder mailboxes, 0-1 are क्रम the decoder mailboxes.
	   If the bit is set, then the corresponding mailbox is in use by the driver. */
	अचिन्हित दीर्घ busy;
	u8 max_mbox;
पूर्ण;

/* per-buffer bit flags */
#घोषणा IVTV_F_B_NEED_BUF_SWAP  (1 << 0)	/* this buffer should be byte swapped */

/* per-stream, s_flags */
#घोषणा IVTV_F_S_DMA_PENDING	0	/* this stream has pending DMA */
#घोषणा IVTV_F_S_DMA_HAS_VBI	1       /* the current DMA request also requests VBI data */
#घोषणा IVTV_F_S_NEEDS_DATA	2	/* this decoding stream needs more data */

#घोषणा IVTV_F_S_CLAIMED	3	/* this stream is claimed */
#घोषणा IVTV_F_S_STREAMING      4	/* the fw is decoding/encoding this stream */
#घोषणा IVTV_F_S_INTERNAL_USE	5	/* this stream is used पूर्णांकernally (sliced VBI processing) */
#घोषणा IVTV_F_S_PASSTHROUGH	6	/* this stream is in passthrough mode */
#घोषणा IVTV_F_S_STREAMOFF	7	/* संकेत end of stream EOS */
#घोषणा IVTV_F_S_APPL_IO        8	/* this stream is used पढ़ो/written by an application */

#घोषणा IVTV_F_S_PIO_PENDING	9	/* this stream has pending PIO */
#घोषणा IVTV_F_S_PIO_HAS_VBI	1       /* the current PIO request also requests VBI data */

/* per-ivtv, i_flags */
#घोषणा IVTV_F_I_DMA		   0	/* DMA in progress */
#घोषणा IVTV_F_I_UDMA		   1	/* UDMA in progress */
#घोषणा IVTV_F_I_UDMA_PENDING	   2	/* UDMA pending */
#घोषणा IVTV_F_I_SPEED_CHANGE	   3	/* a speed change is in progress */
#घोषणा IVTV_F_I_EOS		   4	/* end of encoder stream reached */
#घोषणा IVTV_F_I_RADIO_USER	   5	/* the radio tuner is selected */
#घोषणा IVTV_F_I_DIG_RST	   6	/* reset digitizer */
#घोषणा IVTV_F_I_DEC_YUV	   7	/* YUV instead of MPG is being decoded */
#घोषणा IVTV_F_I_UPDATE_CC	   9	/* CC should be updated */
#घोषणा IVTV_F_I_UPDATE_WSS	   10	/* WSS should be updated */
#घोषणा IVTV_F_I_UPDATE_VPS	   11	/* VPS should be updated */
#घोषणा IVTV_F_I_DECODING_YUV	   12	/* this stream is YUV frame decoding */
#घोषणा IVTV_F_I_ENC_PAUSED	   13	/* the encoder is छोड़ोd */
#घोषणा IVTV_F_I_VALID_DEC_TIMINGS 14	/* last_dec_timing is valid */
#घोषणा IVTV_F_I_HAVE_WORK	   15	/* used in the पूर्णांकerrupt handler: there is work to be करोne */
#घोषणा IVTV_F_I_WORK_HANDLER_VBI  16	/* there is work to be करोne क्रम VBI */
#घोषणा IVTV_F_I_WORK_HANDLER_YUV  17	/* there is work to be करोne क्रम YUV */
#घोषणा IVTV_F_I_WORK_HANDLER_PIO  18	/* there is work to be करोne क्रम PIO */
#घोषणा IVTV_F_I_PIO		   19	/* PIO in progress */
#घोषणा IVTV_F_I_DEC_PAUSED	   20	/* the decoder is छोड़ोd */
#घोषणा IVTV_F_I_INITED		   21	/* set after first खोलो */
#घोषणा IVTV_F_I_FAILED		   22	/* set अगर first खोलो failed */
#घोषणा IVTV_F_I_WORK_HANDLER_PCM  23	/* there is work to be करोne क्रम PCM */

/* Event notअगरications */
#घोषणा IVTV_F_I_EV_DEC_STOPPED	   28	/* decoder stopped event */
#घोषणा IVTV_F_I_EV_VSYNC	   29	/* VSYNC event */
#घोषणा IVTV_F_I_EV_VSYNC_FIELD    30	/* VSYNC event field (0 = first, 1 = second field) */
#घोषणा IVTV_F_I_EV_VSYNC_ENABLED  31	/* VSYNC event enabled */

/* Scatter-Gather array element, used in DMA transfers */
काष्ठा ivtv_sg_element अणु
	__le32 src;
	__le32 dst;
	__le32 size;
पूर्ण;

काष्ठा ivtv_sg_host_element अणु
	u32 src;
	u32 dst;
	u32 size;
पूर्ण;

काष्ठा ivtv_user_dma अणु
	काष्ठा mutex lock;
	पूर्णांक page_count;
	काष्ठा page *map[IVTV_DMA_SG_OSD_ENT];
	/* Needed when dealing with highmem userspace buffers */
	काष्ठा page *bouncemap[IVTV_DMA_SG_OSD_ENT];

	/* Base Dev SG Array क्रम cx23415/6 */
	काष्ठा ivtv_sg_element SGarray[IVTV_DMA_SG_OSD_ENT];
	dma_addr_t SG_handle;
	पूर्णांक SG_length;

	/* SG List of Buffers */
	काष्ठा scatterlist SGlist[IVTV_DMA_SG_OSD_ENT];
पूर्ण;

काष्ठा ivtv_dma_page_info अणु
	अचिन्हित दीर्घ uaddr;
	अचिन्हित दीर्घ first;
	अचिन्हित दीर्घ last;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक tail;
	पूर्णांक page_count;
पूर्ण;

काष्ठा ivtv_buffer अणु
	काष्ठा list_head list;
	dma_addr_t dma_handle;
	अचिन्हित लघु b_flags;
	अचिन्हित लघु dma_xfer_cnt;
	अक्षर *buf;
	u32 bytesused;
	u32 पढ़ोpos;
पूर्ण;

काष्ठा ivtv_queue अणु
	काष्ठा list_head list;          /* the list of buffers in this queue */
	u32 buffers;                    /* number of buffers in this queue */
	u32 length;                     /* total number of bytes of available buffer space */
	u32 bytesused;                  /* total number of bytes used in this queue */
पूर्ण;

काष्ठा ivtv;				/* क्रमward reference */

काष्ठा ivtv_stream अणु
	/* These first four fields are always set, even अगर the stream
	   is not actually created. */
	काष्ठा video_device vdev;	/* vdev.v4l2_dev is शून्य अगर there is no device */
	काष्ठा ivtv *itv;		/* क्रम ease of use */
	स्थिर अक्षर *name;		/* name of the stream */
	पूर्णांक type;			/* stream type */
	u32 caps;			/* V4L2 capabilities */

	काष्ठा v4l2_fh *fh;		/* poपूर्णांकer to the streaming filehandle */
	spinlock_t qlock;		/* locks access to the queues */
	अचिन्हित दीर्घ s_flags;		/* status flags, see above */
	पूर्णांक dma;			/* can be PCI_DMA_TODEVICE, PCI_DMA_FROMDEVICE or PCI_DMA_NONE */
	u32 pending_offset;
	u32 pending_backup;
	u64 pending_pts;

	u32 dma_offset;
	u32 dma_backup;
	u64 dma_pts;

	पूर्णांक subtype;
	रुको_queue_head_t रुकोq;
	u32 dma_last_offset;

	/* Buffer Stats */
	u32 buffers;
	u32 buf_size;
	u32 buffers_stolen;

	/* Buffer Queues */
	काष्ठा ivtv_queue q_मुक्त;	/* मुक्त buffers */
	काष्ठा ivtv_queue q_full;	/* full buffers */
	काष्ठा ivtv_queue q_io;		/* रुकोing क्रम I/O */
	काष्ठा ivtv_queue q_dma;	/* रुकोing क्रम DMA */
	काष्ठा ivtv_queue q_predma;	/* रुकोing क्रम DMA */

	/* DMA xfer counter, buffers beदीर्घing to the same DMA
	   xfer will have the same dma_xfer_cnt. */
	u16 dma_xfer_cnt;

	/* Base Dev SG Array क्रम cx23415/6 */
	काष्ठा ivtv_sg_host_element *sg_pending;
	काष्ठा ivtv_sg_host_element *sg_processing;
	काष्ठा ivtv_sg_element *sg_dma;
	dma_addr_t sg_handle;
	पूर्णांक sg_pending_size;
	पूर्णांक sg_processing_size;
	पूर्णांक sg_processed;

	/* SG List of Buffers */
	काष्ठा scatterlist *SGlist;
पूर्ण;

काष्ठा ivtv_खोलो_id अणु
	काष्ठा v4l2_fh fh;
	पूर्णांक type;                       /* stream type */
	पूर्णांक yuv_frames;                 /* 1: started OUT_UDMA_YUV output mode */
	काष्ठा ivtv *itv;
पूर्ण;

अटल अंतरभूत काष्ठा ivtv_खोलो_id *fh2id(काष्ठा v4l2_fh *fh)
अणु
	वापस container_of(fh, काष्ठा ivtv_खोलो_id, fh);
पूर्ण

काष्ठा yuv_frame_info
अणु
	u32 update;
	s32 src_x;
	s32 src_y;
	u32 src_w;
	u32 src_h;
	s32 dst_x;
	s32 dst_y;
	u32 dst_w;
	u32 dst_h;
	s32 pan_x;
	s32 pan_y;
	u32 vis_w;
	u32 vis_h;
	u32 पूर्णांकerlaced_y;
	u32 पूर्णांकerlaced_uv;
	s32 tru_x;
	u32 tru_w;
	u32 tru_h;
	u32 offset_y;
	s32 lace_mode;
	u32 sync_field;
	u32 delay;
	u32 पूर्णांकerlaced;
पूर्ण;

#घोषणा IVTV_YUV_MODE_INTERLACED	0x00
#घोषणा IVTV_YUV_MODE_PROGRESSIVE	0x01
#घोषणा IVTV_YUV_MODE_AUTO		0x02
#घोषणा IVTV_YUV_MODE_MASK		0x03

#घोषणा IVTV_YUV_SYNC_EVEN		0x00
#घोषणा IVTV_YUV_SYNC_ODD		0x04
#घोषणा IVTV_YUV_SYNC_MASK		0x04

#घोषणा IVTV_YUV_BUFFERS 8

काष्ठा yuv_playback_info
अणु
	u32 reg_2834;
	u32 reg_2838;
	u32 reg_283c;
	u32 reg_2840;
	u32 reg_2844;
	u32 reg_2848;
	u32 reg_2854;
	u32 reg_285c;
	u32 reg_2864;

	u32 reg_2870;
	u32 reg_2874;
	u32 reg_2890;
	u32 reg_2898;
	u32 reg_289c;

	u32 reg_2918;
	u32 reg_291c;
	u32 reg_2920;
	u32 reg_2924;
	u32 reg_2928;
	u32 reg_292c;
	u32 reg_2930;

	u32 reg_2934;

	u32 reg_2938;
	u32 reg_293c;
	u32 reg_2940;
	u32 reg_2944;
	u32 reg_2948;
	u32 reg_294c;
	u32 reg_2950;
	u32 reg_2954;
	u32 reg_2958;
	u32 reg_295c;
	u32 reg_2960;
	u32 reg_2964;
	u32 reg_2968;
	u32 reg_296c;

	u32 reg_2970;

	पूर्णांक v_filter_1;
	पूर्णांक v_filter_2;
	पूर्णांक h_filter;

	u8 track_osd; /* Should yuv output track the OSD size & position */

	u32 osd_x_offset;
	u32 osd_y_offset;

	u32 osd_x_pan;
	u32 osd_y_pan;

	u32 osd_vis_w;
	u32 osd_vis_h;

	u32 osd_full_w;
	u32 osd_full_h;

	पूर्णांक decode_height;

	पूर्णांक lace_mode;
	पूर्णांक lace_threshold;
	पूर्णांक lace_sync_field;

	atomic_t next_dma_frame;
	atomic_t next_fill_frame;

	u32 yuv_क्रमced_update;
	पूर्णांक update_frame;

	u8 fields_lapsed;   /* Counter used when delaying a frame */

	काष्ठा yuv_frame_info new_frame_info[IVTV_YUV_BUFFERS];
	काष्ठा yuv_frame_info old_frame_info;
	काष्ठा yuv_frame_info old_frame_info_args;

	व्योम *blanking_ptr;
	dma_addr_t blanking_dmaptr;

	पूर्णांक stream_size;

	u8 draw_frame; /* PVR350 buffer to draw पूर्णांकo */
	u8 max_frames_buffered; /* Maximum number of frames to buffer */

	काष्ठा v4l2_rect मुख्य_rect;
	u32 v4l2_src_w;
	u32 v4l2_src_h;

	u8 running; /* Have any frames been displayed */
पूर्ण;

#घोषणा IVTV_VBI_FRAMES 32

/* VBI data */
काष्ठा vbi_cc अणु
	u8 odd[2];	/* two-byte payload of odd field */
	u8 even[2];	/* two-byte payload of even field */;
पूर्ण;

काष्ठा vbi_vps अणु
	u8 data[5];	/* five-byte VPS payload */
पूर्ण;

काष्ठा vbi_info अणु
	/* VBI general data, करोes not change during streaming */

	u32 raw_decoder_line_size;              /* raw VBI line size from digitizer */
	u8 raw_decoder_sav_odd_field;           /* raw VBI Start Active Video digitizer code of odd field */
	u8 raw_decoder_sav_even_field;          /* raw VBI Start Active Video digitizer code of even field */
	u32 sliced_decoder_line_size;           /* sliced VBI line size from digitizer */
	u8 sliced_decoder_sav_odd_field;        /* sliced VBI Start Active Video digitizer code of odd field */
	u8 sliced_decoder_sav_even_field;       /* sliced VBI Start Active Video digitizer code of even field */

	u32 start[2];				/* start of first VBI line in the odd/even fields */
	u32 count;				/* number of VBI lines per field */
	u32 raw_size;				/* size of raw VBI line from the digitizer */
	u32 sliced_size;			/* size of sliced VBI line from the digitizer */

	u32 dec_start;				/* start in decoder memory of VBI re-insertion buffers */
	u32 enc_start;				/* start in encoder memory of VBI capture buffers */
	u32 enc_size;				/* size of VBI capture area */
	पूर्णांक fpi;				/* number of VBI frames per पूर्णांकerrupt */

	काष्ठा v4l2_क्रमmat in;			/* current VBI capture क्रमmat */
	काष्ठा v4l2_sliced_vbi_क्रमmat *sliced_in; /* convenience poपूर्णांकer to sliced काष्ठा in vbi.in जोड़ */
	पूर्णांक insert_mpeg;			/* अगर non-zero, then embed VBI data in MPEG stream */

	/* Raw VBI compatibility hack */

	u32 frame;				/* frame counter hack needed क्रम backwards compatibility
						   of old VBI software */

	/* Sliced VBI output data */

	काष्ठा vbi_cc cc_payload[256];		/* sliced VBI CC payload array: it is an array to
						   prevent dropping CC data अगर they couldn't be
						   processed fast enough */
	पूर्णांक cc_payload_idx;			/* index in cc_payload */
	u8 cc_missing_cnt;			/* counts number of frames without CC क्रम passthrough mode */
	पूर्णांक wss_payload;			/* sliced VBI WSS payload */
	u8 wss_missing_cnt;			/* counts number of frames without WSS क्रम passthrough mode */
	काष्ठा vbi_vps vps_payload;		/* sliced VBI VPS payload */

	/* Sliced VBI capture data */

	काष्ठा v4l2_sliced_vbi_data sliced_data[36];	/* sliced VBI storage क्रम VBI encoder stream */
	काष्ठा v4l2_sliced_vbi_data sliced_dec_data[36];/* sliced VBI storage क्रम VBI decoder stream */

	/* VBI Embedding data */

	/* Buffer क्रम VBI data inserted पूर्णांकo MPEG stream.
	   The first byte is a dummy byte that's never used.
	   The next 16 bytes contain the MPEG header क्रम the VBI data,
	   the reमुख्यder is the actual VBI data.
	   The max size accepted by the MPEG VBI reinsertion turns out
	   to be 1552 bytes, which happens to be 4 + (1 + 42) * (2 * 18) bytes,
	   where 4 is a four byte header, 42 is the max sliced VBI payload, 1 is
	   a single line header byte and 2 * 18 is the number of VBI lines per frame.

	   However, it seems that the data must be 1K aligned, so we have to
	   pad the data until the 1 or 2 K boundary.

	   This poपूर्णांकer array will allocate 2049 bytes to store each VBI frame. */
	u8 *sliced_mpeg_data[IVTV_VBI_FRAMES];
	u32 sliced_mpeg_size[IVTV_VBI_FRAMES];
	काष्ठा ivtv_buffer sliced_mpeg_buf;	/* temporary buffer holding data from sliced_mpeg_data */
	u32 inserted_frame;			/* index in sliced_mpeg_size of next sliced data
						   to be inserted in the MPEG stream */
पूर्ण;

/* क्रमward declaration of काष्ठा defined in ivtv-cards.h */
काष्ठा ivtv_card;

/* Struct to hold info about ivtv cards */
काष्ठा ivtv अणु
	/* General fixed card data */
	काष्ठा pci_dev *pdev;		/* PCI device */
	स्थिर काष्ठा ivtv_card *card;	/* card inक्रमmation */
	स्थिर अक्षर *card_name;          /* full name of the card */
	स्थिर काष्ठा ivtv_card_tuner_i2c *card_i2c; /* i2c addresses to probe क्रम tuner */
	u8 has_cx23415;			/* 1 अगर it is a cx23415 based card, 0 क्रम cx23416 */
	u8 pvr150_workaround;           /* 1 अगर the cx25840 needs to workaround a PVR150 bug */
	u8 nof_inमाला_दो;			/* number of video inमाला_दो */
	u8 nof_audio_inमाला_दो;		/* number of audio inमाला_दो */
	u32 v4l2_cap;			/* V4L2 capabilities of card */
	u32 hw_flags;			/* hardware description of the board */
	v4l2_std_id tuner_std;		/* the norm of the card's tuner (fixed) */
	काष्ठा v4l2_subdev *sd_video;	/* controlling video decoder subdev */
	काष्ठा v4l2_subdev *sd_audio;	/* controlling audio subdev */
	काष्ठा v4l2_subdev *sd_muxer;	/* controlling audio muxer subdev */
	resource_माप_प्रकार base_addr;      /* PCI resource base address */
	अस्थिर व्योम __iomem *enc_mem; /* poपूर्णांकer to mapped encoder memory */
	अस्थिर व्योम __iomem *dec_mem; /* poपूर्णांकer to mapped decoder memory */
	अस्थिर व्योम __iomem *reg_mem; /* poपूर्णांकer to mapped रेजिस्टरs */
	काष्ठा ivtv_options options;	/* user options */

	काष्ठा v4l2_device v4l2_dev;
	काष्ठा cx2341x_handler cxhdl;
	काष्ठा अणु
		/* PTS/Frame count control cluster */
		काष्ठा v4l2_ctrl *ctrl_pts;
		काष्ठा v4l2_ctrl *ctrl_frame;
	पूर्ण;
	काष्ठा अणु
		/* Audio Playback control cluster */
		काष्ठा v4l2_ctrl *ctrl_audio_playback;
		काष्ठा v4l2_ctrl *ctrl_audio_multilingual_playback;
	पूर्ण;
	काष्ठा v4l2_ctrl_handler hdl_gpio;
	काष्ठा v4l2_subdev sd_gpio;	/* GPIO sub-device */
	u16 instance;

	/* High-level state info */
	अचिन्हित दीर्घ i_flags;          /* global ivtv flags */
	u8 is_50hz;                     /* 1 अगर the current capture standard is 50 Hz */
	u8 is_60hz                      /* 1 अगर the current capture standard is 60 Hz */;
	u8 is_out_50hz                  /* 1 अगर the current TV output standard is 50 Hz */;
	u8 is_out_60hz                  /* 1 अगर the current TV output standard is 60 Hz */;
	पूर्णांक output_mode;                /* decoder output mode: NONE, MPG, YUV, UDMA YUV, passthrough */
	u32 audio_input;                /* current audio input */
	u32 active_input;               /* current video input */
	u32 active_output;              /* current video output */
	v4l2_std_id std;                /* current capture TV standard */
	v4l2_std_id std_out;            /* current TV output standard */
	u8 audio_stereo_mode;           /* decoder setting how to handle stereo MPEG audio */
	u8 audio_bilingual_mode;        /* decoder setting how to handle bilingual MPEG audio */

	/* Locking */
	spinlock_t lock;                /* lock access to this काष्ठा */
	काष्ठा mutex serialize_lock;    /* mutex used to serialize खोलो/बंद/start/stop/ioctl operations */

	/* Streams */
	पूर्णांक stream_buf_size[IVTV_MAX_STREAMS];          /* stream buffer size */
	काष्ठा ivtv_stream streams[IVTV_MAX_STREAMS];	/* stream data */
	atomic_t capturing;		/* count number of active capture streams */
	atomic_t decoding;		/* count number of active decoding streams */

	/* ALSA पूर्णांकerface क्रम PCM capture stream */
	काष्ठा snd_ivtv_card *alsa;
	व्योम (*pcm_announce_callback)(काष्ठा snd_ivtv_card *card, u8 *pcm_data,
				      माप_प्रकार num_bytes);

	/* Used क्रम ivtv-alsa module loading */
	काष्ठा work_काष्ठा request_module_wk;

	/* Interrupts & DMA */
	u32 irqmask;                    /* active पूर्णांकerrupts */
	u32 irq_rr_idx;                 /* round-robin stream index */
	काष्ठा kthपढ़ो_worker irq_worker;		/* kthपढ़ो worker क्रम PIO/YUV/VBI actions */
	काष्ठा task_काष्ठा *irq_worker_task;		/* task क्रम irq_worker */
	काष्ठा kthपढ़ो_work irq_work;	/* kthपढ़ो work entry */
	spinlock_t dma_reg_lock;        /* lock access to DMA engine रेजिस्टरs */
	पूर्णांक cur_dma_stream;		/* index of current stream करोing DMA (-1 अगर none) */
	पूर्णांक cur_pio_stream;		/* index of current stream करोing PIO (-1 अगर none) */
	u32 dma_data_req_offset;        /* store offset in decoder memory of current DMA request */
	u32 dma_data_req_size;          /* store size of current DMA request */
	पूर्णांक dma_retries;                /* current DMA retry attempt */
	काष्ठा ivtv_user_dma udma;      /* user based DMA क्रम OSD */
	काष्ठा समयr_list dma_समयr;    /* समयr used to catch unfinished DMAs */
	u32 last_vsync_field;           /* last seen vsync field */
	रुको_queue_head_t dma_रुकोq;    /* wake up when the current DMA is finished */
	रुको_queue_head_t eos_रुकोq;    /* wake up when EOS arrives */
	रुको_queue_head_t event_रुकोq;  /* wake up when the next decoder event arrives */
	रुको_queue_head_t vsync_रुकोq;  /* wake up when the next decoder vsync arrives */


	/* Mailbox */
	काष्ठा ivtv_mailbox_data enc_mbox;              /* encoder mailboxes */
	काष्ठा ivtv_mailbox_data dec_mbox;              /* decoder mailboxes */
	काष्ठा ivtv_api_cache api_cache[256];		/* cached API commands */


	/* I2C */
	काष्ठा i2c_adapter i2c_adap;
	काष्ठा i2c_algo_bit_data i2c_algo;
	काष्ठा i2c_client i2c_client;
	पूर्णांक i2c_state;                  /* i2c bit state */
	काष्ठा mutex i2c_bus_lock;      /* lock i2c bus */

	काष्ठा IR_i2c_init_data ir_i2c_init_data;

	/* Program Index inक्रमmation */
	u32 pgm_info_offset;            /* start of pgm info in encoder memory */
	u32 pgm_info_num;               /* number of elements in the pgm cyclic buffer in encoder memory */
	u32 pgm_info_ग_लिखो_idx;         /* last index written by the card that was transferred to pgm_info[] */
	u32 pgm_info_पढ़ो_idx;          /* last index in pgm_info पढ़ो by the application */
	काष्ठा v4l2_enc_idx_entry pgm_info[IVTV_MAX_PGM_INDEX]; /* filled from the pgm cyclic buffer on the card */


	/* Miscellaneous */
	u32 खोलो_id;			/* incremented each समय an खोलो occurs, is >= 1 */
	पूर्णांक search_pack_header;         /* 1 अगर ivtv_copy_buf_to_user() is scanning क्रम a pack header (0xba) */
	पूर्णांक speed;                      /* current playback speed setting */
	u8 speed_mute_audio;            /* 1 अगर audio should be muted when fast क्रमward */
	u64 mpg_data_received;          /* number of bytes received from the MPEG stream */
	u64 vbi_data_inserted;          /* number of VBI bytes inserted पूर्णांकo the MPEG stream */
	u32 last_dec_timing[3];         /* cache last retrieved pts/scr/frame values */
	अचिन्हित दीर्घ dualwatch_jअगरfies;/* jअगरfies value of the previous dualwatch check */
	u32 dualwatch_stereo_mode;      /* current detected dualwatch stereo mode */


	/* VBI state info */
	काष्ठा vbi_info vbi;            /* VBI-specअगरic data */


	/* YUV playback */
	काष्ठा yuv_playback_info yuv_info;              /* YUV playback data */


	/* OSD support */
	अचिन्हित दीर्घ osd_video_pbase;
	पूर्णांक osd_global_alpha_state;     /* 1 = global alpha is on */
	पूर्णांक osd_local_alpha_state;      /* 1 = local alpha is on */
	पूर्णांक osd_chroma_key_state;       /* 1 = chroma-keying is on */
	u8  osd_global_alpha;           /* current global alpha */
	u32 osd_chroma_key;             /* current chroma key */
	काष्ठा v4l2_rect osd_rect;      /* current OSD position and size */
	काष्ठा v4l2_rect मुख्य_rect;     /* current Main winकरोw position and size */
	काष्ठा osd_info *osd_info;      /* ivtvfb निजी OSD info */
	व्योम (*ivtvfb_restore)(काष्ठा ivtv *itv); /* Used क्रम a warm start */
पूर्ण;

अटल अंतरभूत काष्ठा ivtv *to_ivtv(काष्ठा v4l2_device *v4l2_dev)
अणु
	वापस container_of(v4l2_dev, काष्ठा ivtv, v4l2_dev);
पूर्ण

/* ivtv extensions to be loaded */
बाह्य पूर्णांक (*ivtv_ext_init)(काष्ठा ivtv *);

/* Globals */
बाह्य पूर्णांक ivtv_first_minor;

/*==============Prototypes==================*/

/* Hardware/IRQ */
व्योम ivtv_set_irq_mask(काष्ठा ivtv *itv, u32 mask);
व्योम ivtv_clear_irq_mask(काष्ठा ivtv *itv, u32 mask);

/* try to set output mode, वापस current mode. */
पूर्णांक ivtv_set_output_mode(काष्ठा ivtv *itv, पूर्णांक mode);

/* वापस current output stream based on current mode */
काष्ठा ivtv_stream *ivtv_get_output_stream(काष्ठा ivtv *itv);

/* Return non-zero अगर a संकेत is pending */
पूर्णांक ivtv_msleep_समयout(अचिन्हित पूर्णांक msecs, पूर्णांक पूर्णांकr);

/* Wait on queue, वापसs -EINTR अगर पूर्णांकerrupted */
पूर्णांक ivtv_रुकोq(रुको_queue_head_t *रुकोq);

/* Read Hauppauge eeprom */
काष्ठा tveeprom; /* क्रमward reference */
व्योम ivtv_पढ़ो_eeprom(काष्ठा ivtv *itv, काष्ठा tveeprom *tv);

/* First-खोलो initialization: load firmware, init cx25840, etc. */
पूर्णांक ivtv_init_on_first_खोलो(काष्ठा ivtv *itv);

/* Test अगर the current VBI mode is raw (1) or sliced (0) */
अटल अंतरभूत पूर्णांक ivtv_raw_vbi(स्थिर काष्ठा ivtv *itv)
अणु
	वापस itv->vbi.in.type == V4L2_BUF_TYPE_VBI_CAPTURE;
पूर्ण

/* This is a PCI post thing, where अगर the pci रेजिस्टर is not पढ़ो, then
   the ग_लिखो करोesn't always take effect right away. By पढ़ोing back the
   रेजिस्टर any pending PCI ग_लिखोs will be perक्रमmed (in order), and so
   you can be sure that the ग_लिखोs are guaranteed to be करोne.

   Rarely needed, only in some timing sensitive हालs.
   Apparently अगर this is not करोne some motherboards seem
   to समाप्त the firmware and get पूर्णांकo the broken state until computer is
   rebooted. */
#घोषणा ग_लिखो_sync(val, reg) \
	करो अणु ग_लिखोl(val, reg); पढ़ोl(reg); पूर्ण जबतक (0)

#घोषणा पढ़ो_reg(reg) पढ़ोl(itv->reg_mem + (reg))
#घोषणा ग_लिखो_reg(val, reg) ग_लिखोl(val, itv->reg_mem + (reg))
#घोषणा ग_लिखो_reg_sync(val, reg) \
	करो अणु ग_लिखो_reg(val, reg); पढ़ो_reg(reg); पूर्ण जबतक (0)

#घोषणा पढ़ो_enc(addr) पढ़ोl(itv->enc_mem + (u32)(addr))
#घोषणा ग_लिखो_enc(val, addr) ग_लिखोl(val, itv->enc_mem + (u32)(addr))
#घोषणा ग_लिखो_enc_sync(val, addr) \
	करो अणु ग_लिखो_enc(val, addr); पढ़ो_enc(addr); पूर्ण जबतक (0)

#घोषणा पढ़ो_dec(addr) पढ़ोl(itv->dec_mem + (u32)(addr))
#घोषणा ग_लिखो_dec(val, addr) ग_लिखोl(val, itv->dec_mem + (u32)(addr))
#घोषणा ग_लिखो_dec_sync(val, addr) \
	करो अणु ग_लिखो_dec(val, addr); पढ़ो_dec(addr); पूर्ण जबतक (0)

/* Call the specअगरied callback क्रम all subdevs matching hw (अगर 0, then
   match them all). Ignore any errors. */
#घोषणा ivtv_call_hw(itv, hw, o, f, args...)				\
	v4l2_device_mask_call_all(&(itv)->v4l2_dev, hw, o, f, ##args)

#घोषणा ivtv_call_all(itv, o, f, args...) ivtv_call_hw(itv, 0, o, f , ##args)

/* Call the specअगरied callback क्रम all subdevs matching hw (अगर 0, then
   match them all). If the callback वापसs an error other than 0 or
   -ENOIOCTLCMD, then वापस with that error code. */
#घोषणा ivtv_call_hw_err(itv, hw, o, f, args...)			\
	v4l2_device_mask_call_until_err(&(itv)->v4l2_dev, hw, o, f, ##args)

#घोषणा ivtv_call_all_err(itv, o, f, args...) ivtv_call_hw_err(itv, 0, o, f , ##args)

#पूर्ण_अगर
