<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  cx18 driver पूर्णांकernal defines and काष्ठाures
 *
 *  Derived from ivtv-driver.h
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 *  Copyright (C) 2008  Andy Walls <awalls@md.metrocast.net>
 */

#अगर_अघोषित CX18_DRIVER_H
#घोषणा CX18_DRIVER_H

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
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
#समावेश <linux/workqueue.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/byteorder.h>

#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/tuner.h>
#समावेश <media/i2c/ir-kbd-i2c.h>
#समावेश "cx18-mailbox.h"
#समावेश "cx18-av-core.h"
#समावेश "cx23418.h"

/* DVB */
#समावेश <media/demux.h>
#समावेश <media/dmxdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_net.h>
#समावेश <media/dvbdev.h>

/* Videobuf / YUV support */
#समावेश <media/videobuf-core.h>
#समावेश <media/videobuf-vदो_स्मृति.h>

#अगर_अघोषित CONFIG_PCI
#  error "This driver requires kernel PCI support."
#पूर्ण_अगर

#घोषणा CX18_MEM_OFFSET	0x00000000
#घोषणा CX18_MEM_SIZE	0x04000000
#घोषणा CX18_REG_OFFSET	0x02000000

/* Maximum cx18 driver instances. */
#घोषणा CX18_MAX_CARDS 32

/* Supported cards */
#घोषणा CX18_CARD_HVR_1600_ESMT	      0	/* Hauppauge HVR 1600 (ESMT memory) */
#घोषणा CX18_CARD_HVR_1600_SAMSUNG    1	/* Hauppauge HVR 1600 (Samsung memory) */
#घोषणा CX18_CARD_COMPRO_H900	      2	/* Compro VideoMate H900 */
#घोषणा CX18_CARD_YUAN_MPC718	      3	/* Yuan MPC718 */
#घोषणा CX18_CARD_CNXT_RAPTOR_PAL     4	/* Conexant Raptor PAL */
#घोषणा CX18_CARD_TOSHIBA_QOSMIO_DVBT 5 /* Toshiba Qosmio Interal DVB-T/Analog*/
#घोषणा CX18_CARD_LEADTEK_PVR2100     6 /* Leadtek WinFast PVR2100 */
#घोषणा CX18_CARD_LEADTEK_DVR3100H    7 /* Leadtek WinFast DVR3100 H */
#घोषणा CX18_CARD_GOTVIEW_PCI_DVD3    8 /* GoTView PCI DVD3 Hybrid */
#घोषणा CX18_CARD_HVR_1600_S5H1411    9 /* Hauppauge HVR 1600 s5h1411/tda18271*/
#घोषणा CX18_CARD_LAST		      9

#घोषणा CX18_ENC_STREAM_TYPE_MPG  0
#घोषणा CX18_ENC_STREAM_TYPE_TS   1
#घोषणा CX18_ENC_STREAM_TYPE_YUV  2
#घोषणा CX18_ENC_STREAM_TYPE_VBI  3
#घोषणा CX18_ENC_STREAM_TYPE_PCM  4
#घोषणा CX18_ENC_STREAM_TYPE_IDX  5
#घोषणा CX18_ENC_STREAM_TYPE_RAD  6
#घोषणा CX18_MAX_STREAMS	  7

/* प्रणाली venकरोr and device IDs */
#घोषणा PCI_VENDOR_ID_CX      0x14f1
#घोषणा PCI_DEVICE_ID_CX23418 0x5b7a

/* subप्रणाली venकरोr ID */
#घोषणा CX18_PCI_ID_HAUPPAUGE		0x0070
#घोषणा CX18_PCI_ID_COMPRO		0x185b
#घोषणा CX18_PCI_ID_YUAN		0x12ab
#घोषणा CX18_PCI_ID_CONEXANT		0x14f1
#घोषणा CX18_PCI_ID_TOSHIBA		0x1179
#घोषणा CX18_PCI_ID_LEADTEK		0x107D
#घोषणा CX18_PCI_ID_GOTVIEW		0x5854

/* ======================================================================== */
/* ========================== START USER SETTABLE DMA VARIABLES =========== */
/* ======================================================================== */

/* DMA Buffers, Default size in MB allocated */
#घोषणा CX18_DEFAULT_ENC_TS_BUFFERS  1
#घोषणा CX18_DEFAULT_ENC_MPG_BUFFERS 2
#घोषणा CX18_DEFAULT_ENC_IDX_BUFFERS 1
#घोषणा CX18_DEFAULT_ENC_YUV_BUFFERS 2
#घोषणा CX18_DEFAULT_ENC_VBI_BUFFERS 1
#घोषणा CX18_DEFAULT_ENC_PCM_BUFFERS 1

/* Maximum firmware DMA buffers per stream */
#घोषणा CX18_MAX_FW_MDLS_PER_STREAM 63

/* YUV buffer sizes in bytes to ensure पूर्णांकeger # of frames per buffer */
#घोषणा CX18_UNIT_ENC_YUV_बफ_मानE	(720 *  32 * 3 / 2) /* bytes */
#घोषणा CX18_625_LINE_ENC_YUV_बफ_मानE	(CX18_UNIT_ENC_YUV_बफ_मानE * 576/32)
#घोषणा CX18_525_LINE_ENC_YUV_बफ_मानE	(CX18_UNIT_ENC_YUV_बफ_मानE * 480/32)

/* IDX buffer size should be a multiple of the index entry size from the chip */
काष्ठा cx18_enc_idx_entry अणु
	__le32 length;
	__le32 offset_low;
	__le32 offset_high;
	__le32 flags;
	__le32 pts_low;
	__le32 pts_high;
पूर्ण __attribute__ ((packed));
#घोषणा CX18_UNIT_ENC_IDX_बफ_मानE \
	(माप(काष्ठा cx18_enc_idx_entry) * V4L2_ENC_IDX_ENTRIES)

/* DMA buffer, शेष size in kB allocated */
#घोषणा CX18_DEFAULT_ENC_TS_बफ_मानE   32
#घोषणा CX18_DEFAULT_ENC_MPG_बफ_मानE  32
#घोषणा CX18_DEFAULT_ENC_IDX_बफ_मानE  (CX18_UNIT_ENC_IDX_बफ_मानE * 1 / 1024 + 1)
#घोषणा CX18_DEFAULT_ENC_YUV_बफ_मानE  (CX18_UNIT_ENC_YUV_बफ_मानE * 3 / 1024 + 1)
#घोषणा CX18_DEFAULT_ENC_PCM_बफ_मानE   4

/* i2c stuff */
#घोषणा I2C_CLIENTS_MAX 16

/* debugging */

/* Flag to turn on high volume debugging */
#घोषणा CX18_DBGFLG_WARN  (1 << 0)
#घोषणा CX18_DBGFLG_INFO  (1 << 1)
#घोषणा CX18_DBGFLG_API   (1 << 2)
#घोषणा CX18_DBGFLG_DMA   (1 << 3)
#घोषणा CX18_DBGFLG_IOCTL (1 << 4)
#घोषणा CX18_DBGFLG_खाता  (1 << 5)
#घोषणा CX18_DBGFLG_I2C   (1 << 6)
#घोषणा CX18_DBGFLG_IRQ   (1 << 7)
/* Flag to turn on high volume debugging */
#घोषणा CX18_DBGFLG_HIGHVOL (1 << 8)

/* NOTE: extra space beक्रमe comma in 'fmt , ## args' is required क्रम
   gcc-2.95, otherwise it won't compile. */
#घोषणा CX18_DEBUG(x, type, fmt, args...) \
	करो अणु \
		अगर ((x) & cx18_debug) \
			v4l2_info(&cx->v4l2_dev, " " type ": " fmt , ## args); \
	पूर्ण जबतक (0)
#घोषणा CX18_DEBUG_WARN(fmt, args...)  CX18_DEBUG(CX18_DBGFLG_WARN, "warning", fmt , ## args)
#घोषणा CX18_DEBUG_INFO(fmt, args...)  CX18_DEBUG(CX18_DBGFLG_INFO, "info", fmt , ## args)
#घोषणा CX18_DEBUG_API(fmt, args...)   CX18_DEBUG(CX18_DBGFLG_API, "api", fmt , ## args)
#घोषणा CX18_DEBUG_DMA(fmt, args...)   CX18_DEBUG(CX18_DBGFLG_DMA, "dma", fmt , ## args)
#घोषणा CX18_DEBUG_IOCTL(fmt, args...) CX18_DEBUG(CX18_DBGFLG_IOCTL, "ioctl", fmt , ## args)
#घोषणा CX18_DEBUG_खाता(fmt, args...)  CX18_DEBUG(CX18_DBGFLG_खाता, "file", fmt , ## args)
#घोषणा CX18_DEBUG_I2C(fmt, args...)   CX18_DEBUG(CX18_DBGFLG_I2C, "i2c", fmt , ## args)
#घोषणा CX18_DEBUG_IRQ(fmt, args...)   CX18_DEBUG(CX18_DBGFLG_IRQ, "irq", fmt , ## args)

#घोषणा CX18_DEBUG_HIGH_VOL(x, type, fmt, args...) \
	करो अणु \
		अगर (((x) & cx18_debug) && (cx18_debug & CX18_DBGFLG_HIGHVOL)) \
			v4l2_info(&cx->v4l2_dev, " " type ": " fmt , ## args); \
	पूर्ण जबतक (0)
#घोषणा CX18_DEBUG_HI_WARN(fmt, args...)  CX18_DEBUG_HIGH_VOL(CX18_DBGFLG_WARN, "warning", fmt , ## args)
#घोषणा CX18_DEBUG_HI_INFO(fmt, args...)  CX18_DEBUG_HIGH_VOL(CX18_DBGFLG_INFO, "info", fmt , ## args)
#घोषणा CX18_DEBUG_HI_API(fmt, args...)   CX18_DEBUG_HIGH_VOL(CX18_DBGFLG_API, "api", fmt , ## args)
#घोषणा CX18_DEBUG_HI_DMA(fmt, args...)   CX18_DEBUG_HIGH_VOL(CX18_DBGFLG_DMA, "dma", fmt , ## args)
#घोषणा CX18_DEBUG_HI_IOCTL(fmt, args...) CX18_DEBUG_HIGH_VOL(CX18_DBGFLG_IOCTL, "ioctl", fmt , ## args)
#घोषणा CX18_DEBUG_HI_खाता(fmt, args...)  CX18_DEBUG_HIGH_VOL(CX18_DBGFLG_खाता, "file", fmt , ## args)
#घोषणा CX18_DEBUG_HI_I2C(fmt, args...)   CX18_DEBUG_HIGH_VOL(CX18_DBGFLG_I2C, "i2c", fmt , ## args)
#घोषणा CX18_DEBUG_HI_IRQ(fmt, args...)   CX18_DEBUG_HIGH_VOL(CX18_DBGFLG_IRQ, "irq", fmt , ## args)

/* Standard kernel messages */
#घोषणा CX18_ERR(fmt, args...)      v4l2_err(&cx->v4l2_dev, fmt , ## args)
#घोषणा CX18_WARN(fmt, args...)     v4l2_warn(&cx->v4l2_dev, fmt , ## args)
#घोषणा CX18_INFO(fmt, args...)     v4l2_info(&cx->v4l2_dev, fmt , ## args)

/* Messages क्रम पूर्णांकernal subdevs to use */
#घोषणा CX18_DEBUG_DEV(x, dev, type, fmt, args...) \
	करो अणु \
		अगर ((x) & cx18_debug) \
			v4l2_info(dev, " " type ": " fmt , ## args); \
	पूर्ण जबतक (0)
#घोषणा CX18_DEBUG_WARN_DEV(dev, fmt, args...) \
		CX18_DEBUG_DEV(CX18_DBGFLG_WARN, dev, "warning", fmt , ## args)
#घोषणा CX18_DEBUG_INFO_DEV(dev, fmt, args...) \
		CX18_DEBUG_DEV(CX18_DBGFLG_INFO, dev, "info", fmt , ## args)
#घोषणा CX18_DEBUG_API_DEV(dev, fmt, args...) \
		CX18_DEBUG_DEV(CX18_DBGFLG_API, dev, "api", fmt , ## args)
#घोषणा CX18_DEBUG_DMA_DEV(dev, fmt, args...) \
		CX18_DEBUG_DEV(CX18_DBGFLG_DMA, dev, "dma", fmt , ## args)
#घोषणा CX18_DEBUG_IOCTL_DEV(dev, fmt, args...) \
		CX18_DEBUG_DEV(CX18_DBGFLG_IOCTL, dev, "ioctl", fmt , ## args)
#घोषणा CX18_DEBUG_खाता_DEV(dev, fmt, args...) \
		CX18_DEBUG_DEV(CX18_DBGFLG_खाता, dev, "file", fmt , ## args)
#घोषणा CX18_DEBUG_I2C_DEV(dev, fmt, args...) \
		CX18_DEBUG_DEV(CX18_DBGFLG_I2C, dev, "i2c", fmt , ## args)
#घोषणा CX18_DEBUG_IRQ_DEV(dev, fmt, args...) \
		CX18_DEBUG_DEV(CX18_DBGFLG_IRQ, dev, "irq", fmt , ## args)

#घोषणा CX18_DEBUG_HIGH_VOL_DEV(x, dev, type, fmt, args...) \
	करो अणु \
		अगर (((x) & cx18_debug) && (cx18_debug & CX18_DBGFLG_HIGHVOL)) \
			v4l2_info(dev, " " type ": " fmt , ## args); \
	पूर्ण जबतक (0)
#घोषणा CX18_DEBUG_HI_WARN_DEV(dev, fmt, args...) \
	CX18_DEBUG_HIGH_VOL_DEV(CX18_DBGFLG_WARN, dev, "warning", fmt , ## args)
#घोषणा CX18_DEBUG_HI_INFO_DEV(dev, fmt, args...) \
	CX18_DEBUG_HIGH_VOL_DEV(CX18_DBGFLG_INFO, dev, "info", fmt , ## args)
#घोषणा CX18_DEBUG_HI_API_DEV(dev, fmt, args...) \
	CX18_DEBUG_HIGH_VOL_DEV(CX18_DBGFLG_API, dev, "api", fmt , ## args)
#घोषणा CX18_DEBUG_HI_DMA_DEV(dev, fmt, args...) \
	CX18_DEBUG_HIGH_VOL_DEV(CX18_DBGFLG_DMA, dev, "dma", fmt , ## args)
#घोषणा CX18_DEBUG_HI_IOCTL_DEV(dev, fmt, args...) \
	CX18_DEBUG_HIGH_VOL_DEV(CX18_DBGFLG_IOCTL, dev, "ioctl", fmt , ## args)
#घोषणा CX18_DEBUG_HI_खाता_DEV(dev, fmt, args...) \
	CX18_DEBUG_HIGH_VOL_DEV(CX18_DBGFLG_खाता, dev, "file", fmt , ## args)
#घोषणा CX18_DEBUG_HI_I2C_DEV(dev, fmt, args...) \
	CX18_DEBUG_HIGH_VOL_DEV(CX18_DBGFLG_I2C, dev, "i2c", fmt , ## args)
#घोषणा CX18_DEBUG_HI_IRQ_DEV(dev, fmt, args...) \
	CX18_DEBUG_HIGH_VOL_DEV(CX18_DBGFLG_IRQ, dev, "irq", fmt , ## args)

#घोषणा CX18_ERR_DEV(dev, fmt, args...)      v4l2_err(dev, fmt , ## args)
#घोषणा CX18_WARN_DEV(dev, fmt, args...)     v4l2_warn(dev, fmt , ## args)
#घोषणा CX18_INFO_DEV(dev, fmt, args...)     v4l2_info(dev, fmt , ## args)

बाह्य पूर्णांक cx18_debug;

काष्ठा cx18_options अणु
	पूर्णांक megabytes[CX18_MAX_STREAMS]; /* Size in megabytes of each stream */
	पूर्णांक cardtype;		/* क्रमce card type on load */
	पूर्णांक tuner;		/* set tuner on load */
	पूर्णांक radio;		/* enable/disable radio */
पूर्ण;

/* per-mdl bit flags */
#घोषणा CX18_F_M_NEED_SWAP  0	/* mdl buffer data must be endianness swapped */

/* per-stream, s_flags */
#घोषणा CX18_F_S_CLAIMED	3	/* this stream is claimed */
#घोषणा CX18_F_S_STREAMING      4	/* the fw is decoding/encoding this stream */
#घोषणा CX18_F_S_INTERNAL_USE	5	/* this stream is used पूर्णांकernally (sliced VBI processing) */
#घोषणा CX18_F_S_STREAMOFF	7	/* संकेत end of stream EOS */
#घोषणा CX18_F_S_APPL_IO        8	/* this stream is used पढ़ो/written by an application */
#घोषणा CX18_F_S_STOPPING	9	/* telling the fw to stop capturing */

/* per-cx18, i_flags */
#घोषणा CX18_F_I_LOADED_FW		0	/* Loaded firmware 1st समय */
#घोषणा CX18_F_I_EOS			4	/* End of encoder stream */
#घोषणा CX18_F_I_RADIO_USER		5	/* radio tuner is selected */
#घोषणा CX18_F_I_ENC_PAUSED		13	/* the encoder is छोड़ोd */
#घोषणा CX18_F_I_INITED			21	/* set after first खोलो */
#घोषणा CX18_F_I_FAILED			22	/* set अगर first खोलो failed */

/* These are the VBI types as they appear in the embedded VBI निजी packets. */
#घोषणा CX18_SLICED_TYPE_TELETEXT_B     (1)
#घोषणा CX18_SLICED_TYPE_CAPTION_525    (4)
#घोषणा CX18_SLICED_TYPE_WSS_625        (5)
#घोषणा CX18_SLICED_TYPE_VPS            (7)

/**
 * list_entry_is_past_end - check अगर a previous loop cursor is off list end
 * @pos:	the type * previously used as a loop cursor.
 * @head:	the head क्रम your list.
 * @member:	the name of the list_head within the काष्ठा.
 *
 * Check अगर the entry's list_head is the head of the list, thus it's not a
 * real entry but was the loop cursor that walked past the end
 */
#घोषणा list_entry_is_past_end(pos, head, member) \
	(&pos->member == (head))

काष्ठा cx18_buffer अणु
	काष्ठा list_head list;
	dma_addr_t dma_handle;
	अक्षर *buf;

	u32 bytesused;
	u32 पढ़ोpos;
पूर्ण;

काष्ठा cx18_mdl अणु
	काष्ठा list_head list;
	u32 id;		/* index पूर्णांकo cx->scb->cpu_mdl[] of 1st cx18_mdl_ent */

	अचिन्हित पूर्णांक skipped;
	अचिन्हित दीर्घ m_flags;

	काष्ठा list_head buf_list;
	काष्ठा cx18_buffer *curr_buf; /* current buffer in list क्रम पढ़ोing */

	u32 bytesused;
	u32 पढ़ोpos;
पूर्ण;

काष्ठा cx18_queue अणु
	काष्ठा list_head list;
	atomic_t depth;
	u32 bytesused;
	spinlock_t lock;
पूर्ण;

काष्ठा cx18_stream; /* क्रमward reference */

काष्ठा cx18_dvb अणु
	काष्ठा cx18_stream *stream;
	काष्ठा dmx_frontend hw_frontend;
	काष्ठा dmx_frontend mem_frontend;
	काष्ठा dmxdev dmxdev;
	काष्ठा dvb_adapter dvb_adapter;
	काष्ठा dvb_demux demux;
	काष्ठा dvb_frontend *fe;
	काष्ठा dvb_net dvbnet;
	पूर्णांक enabled;
	पूर्णांक feeding;
	काष्ठा mutex feedlock;
पूर्ण;

काष्ठा cx18;	 /* क्रमward reference */
काष्ठा cx18_scb; /* क्रमward reference */


#घोषणा CX18_MAX_MDL_ACKS 2
#घोषणा CX18_MAX_IN_WORK_ORDERS (CX18_MAX_FW_MDLS_PER_STREAM + 7)
/* CPU_DE_RELEASE_MDL can burst CX18_MAX_FW_MDLS_PER_STREAM orders in a group */

#घोषणा CX18_F_EWO_MB_STALE_UPON_RECEIPT 0x1
#घोषणा CX18_F_EWO_MB_STALE_WHILE_PROC   0x2
#घोषणा CX18_F_EWO_MB_STALE \
	     (CX18_F_EWO_MB_STALE_UPON_RECEIPT | CX18_F_EWO_MB_STALE_WHILE_PROC)

काष्ठा cx18_in_work_order अणु
	काष्ठा work_काष्ठा work;
	atomic_t pending;
	काष्ठा cx18 *cx;
	अचिन्हित दीर्घ flags;
	पूर्णांक rpu;
	काष्ठा cx18_mailbox mb;
	काष्ठा cx18_mdl_ack mdl_ack[CX18_MAX_MDL_ACKS];
	अक्षर *str;
पूर्ण;

#घोषणा CX18_INVALID_TASK_HANDLE 0xffffffff

काष्ठा cx18_stream अणु
	/* These first five fields are always set, even अगर the stream
	   is not actually created. */
	काष्ठा video_device video_dev;	/* v4l2_dev is शून्य when stream not created */
	काष्ठा cx18_dvb *dvb;		/* DVB / Digital Transport */
	काष्ठा cx18 *cx;		/* क्रम ease of use */
	स्थिर अक्षर *name;		/* name of the stream */
	पूर्णांक type;			/* stream type */
	u32 handle;			/* task handle */
	u32 v4l2_dev_caps;		/* device capabilities */
	अचिन्हित पूर्णांक mdl_base_idx;

	u32 id;
	अचिन्हित दीर्घ s_flags;	/* status flags, see above */
	पूर्णांक dma;		/* can be PCI_DMA_TODEVICE,
				   PCI_DMA_FROMDEVICE or
				   PCI_DMA_NONE */
	रुको_queue_head_t रुकोq;

	/* Buffers */
	काष्ठा list_head buf_pool;	/* buffers not attached to an MDL */
	u32 buffers;			/* total buffers owned by this stream */
	u32 buf_size;			/* size in bytes of a single buffer */

	/* MDL sizes - all stream MDLs are the same size */
	u32 bufs_per_mdl;
	u32 mdl_size;		/* total bytes in all buffers in a mdl */

	/* MDL Queues */
	काष्ठा cx18_queue q_मुक्त;	/* मुक्त - in rotation, not committed */
	काष्ठा cx18_queue q_busy;	/* busy - in use by firmware */
	काष्ठा cx18_queue q_full;	/* full - data क्रम user apps */
	काष्ठा cx18_queue q_idle;	/* idle - not in rotation */

	काष्ठा work_काष्ठा out_work_order;

	/* Videobuf क्रम YUV video */
	u32 pixelक्रमmat;
	u32 vb_bytes_per_frame;
	u32 vb_bytes_per_line;
	काष्ठा list_head vb_capture;    /* video capture queue */
	spinlock_t vb_lock;
	काष्ठा समयr_list vb_समयout;

	काष्ठा videobuf_queue vbuf_q;
	spinlock_t vbuf_q_lock; /* Protect vbuf_q */
	क्रमागत v4l2_buf_type vb_type;
पूर्ण;

काष्ठा cx18_videobuf_buffer अणु
	/* Common video buffer sub-प्रणाली काष्ठा */
	काष्ठा videobuf_buffer vb;
	v4l2_std_id tvnorm; /* selected tv norm */
	u32 bytes_used;
पूर्ण;

काष्ठा cx18_खोलो_id अणु
	काष्ठा v4l2_fh fh;
	u32 खोलो_id;
	पूर्णांक type;
	काष्ठा cx18 *cx;
पूर्ण;

अटल अंतरभूत काष्ठा cx18_खोलो_id *fh2id(काष्ठा v4l2_fh *fh)
अणु
	वापस container_of(fh, काष्ठा cx18_खोलो_id, fh);
पूर्ण

अटल अंतरभूत काष्ठा cx18_खोलो_id *file2id(काष्ठा file *file)
अणु
	वापस fh2id(file->निजी_data);
पूर्ण

/* क्रमward declaration of काष्ठा defined in cx18-cards.h */
काष्ठा cx18_card;

/*
 * A note about "sliced" VBI data as implemented in this driver:
 *
 * Currently we collect the sliced VBI in the क्रमm of Ancillary Data
 * packets, inserted by the AV core decoder/digitizer/slicer in the
 * horizontal blanking region of the VBI lines, in "raw" mode as far as
 * the Encoder is concerned.  We करोn't ever tell the Encoder itself
 * to provide sliced VBI. (AV Core: sliced mode - Encoder: raw mode)
 *
 * We then process the ancillary data ourselves to send the sliced data
 * to the user application directly or build up MPEG-2 निजी stream 1
 * packets to splice पूर्णांकo (only!) MPEG-2 PS streams क्रम the user app.
 *
 * (That's how ivtv essentially करोes it.)
 *
 * The Encoder should be able to extract certain sliced VBI data क्रम
 * us and provide it in a separate stream or splice it पूर्णांकo any type of
 * MPEG PS or TS stream, but this isn't implemented yet.
 */

/*
 * Number of "raw" VBI samples per horizontal line we tell the Encoder to
 * grab from the decoder/digitizer/slicer output क्रम raw or sliced VBI.
 * It depends on the pixel घड़ी and the horiz rate:
 *
 * (1/Fh)*(2*Fp) = Samples/line
 *     = 4 bytes EAV + Anc data in hblank + 4 bytes SAV + active samples
 *
 *  Sliced VBI data is sent as ancillary data during horizontal blanking
 *  Raw VBI is sent as active video samples during vertcal blanking
 *
 *  We use a  BT.656 pxiel घड़ी of 13.5 MHz and a BT.656 active line
 *  length of 720 pixels @ 4:2:2 sampling.  Thus...
 *
 *  For प्रणालीs that use a 15.734 kHz horizontal rate, such as
 *  NTSC-M, PAL-M, PAL-60, and other 60 Hz/525 line प्रणालीs, we have:
 *
 *  (1/15.734 kHz) * 2 * 13.5 MHz = 1716 samples/line =
 *  4 bytes SAV + 268 bytes anc data + 4 bytes SAV + 1440 active samples
 *
 *  For प्रणालीs that use a 15.625 kHz horizontal rate, such as
 *  PAL-B/G/H, PAL-I, SECAM-L and other 50 Hz/625 line प्रणालीs, we have:
 *
 *  (1/15.625 kHz) * 2 * 13.5 MHz = 1728 samples/line =
 *  4 bytes SAV + 280 bytes anc data + 4 bytes SAV + 1440 active samples
 */
#घोषणा VBI_ACTIVE_SAMPLES	1444 /* 4 byte SAV + 720 Y + 720 U/V */
#घोषणा VBI_HBLANK_SAMPLES_60HZ	272 /* 4 byte EAV + 268 anc/fill */
#घोषणा VBI_HBLANK_SAMPLES_50HZ	284 /* 4 byte EAV + 280 anc/fill */

#घोषणा CX18_VBI_FRAMES 32

काष्ठा vbi_info अणु
	/* Current state of v4l2 VBI settings क्रम this device */
	काष्ठा v4l2_क्रमmat in;
	काष्ठा v4l2_sliced_vbi_क्रमmat *sliced_in; /* poपूर्णांकer to in.fmt.sliced */
	u32 count;    /* Count of VBI data lines: 60 Hz: 12 or 50 Hz: 18 */
	u32 start[2]; /* First VBI data line per field: 10 & 273 or 6 & 318 */

	u32 frame; /* Count of VBI buffers/frames received from Encoder */

	/*
	 * Vars क्रम creation and insertion of MPEG Private Stream 1 packets
	 * of sliced VBI data पूर्णांकo an MPEG PS
	 */

	/* Boolean: create and insert Private Stream 1 packets पूर्णांकo the PS */
	पूर्णांक insert_mpeg;

	/*
	 * Buffer क्रम the maximum of 2 * 18 * packet_size sliced VBI lines.
	 * Used in cx18-vbi.c only क्रम collecting sliced data, and as a source
	 * during conversion of sliced VBI data पूर्णांकo MPEG Priv Stream 1 packets.
	 * We करोn't need to save state here, but the array may have been a bit
	 * too big (2304 bytes) to alloc from the stack.
	 */
	काष्ठा v4l2_sliced_vbi_data sliced_data[36];

	/*
	 * A ring buffer of driver-generated MPEG-2 PS
	 * Program Pack/Private Stream 1 packets क्रम sliced VBI data insertion
	 * पूर्णांकo the MPEG PS stream.
	 *
	 * In each sliced_mpeg_data[] buffer is:
	 *	16 byte MPEG-2 PS Program Pack Header
	 *	16 byte MPEG-2 Private Stream 1 PES Header
	 *	 4 byte magic number: "itv0" or "ITV0"
	 *	 4 byte first  field line mask, अगर "itv0"
	 *	 4 byte second field line mask, अगर "itv0"
	 *	36 lines, अगर "ITV0"; or <36 lines, अगर "itv0"; of sliced VBI data
	 *
	 *	Each line in the payload is
	 *	 1 byte line header derived from the SDID (WSS, CC, VPS, etc.)
	 *	42 bytes of line data
	 *
	 * That's a maximum 1552 bytes of payload in the Private Stream 1 packet
	 * which is the payload size a PVR-350 (CX23415) MPEG decoder will
	 * accept क्रम VBI data. So, including the headers, it's a maximum 1584
	 * bytes total.
	 */
#घोषणा CX18_SLICED_MPEG_DATA_MAXSZ	1584
	/* copy_vbi_buf() needs 8 temp bytes on the end क्रम the worst हाल */
#घोषणा CX18_SLICED_MPEG_DATA_BUFSZ	(CX18_SLICED_MPEG_DATA_MAXSZ+8)
	u8 *sliced_mpeg_data[CX18_VBI_FRAMES];
	u32 sliced_mpeg_size[CX18_VBI_FRAMES];

	/* Count of Program Pack/Program Stream 1 packets inserted पूर्णांकo PS */
	u32 inserted_frame;

	/*
	 * A dummy driver stream transfer mdl & buffer with a copy of the next
	 * sliced_mpeg_data[] buffer क्रम output to userland apps.
	 * Only used in cx18-fileops.c, but its state needs to persist at बार.
	 */
	काष्ठा cx18_mdl sliced_mpeg_mdl;
	काष्ठा cx18_buffer sliced_mpeg_buf;
पूर्ण;

/* Per cx23418, per I2C bus निजी algo callback data */
काष्ठा cx18_i2c_algo_callback_data अणु
	काष्ठा cx18 *cx;
	पूर्णांक bus_index;   /* 0 or 1 क्रम the cx23418's 1st or 2nd I2C bus */
पूर्ण;

#घोषणा CX18_MAX_MMIO_WR_RETRIES 10

/* Struct to hold info about cx18 cards */
काष्ठा cx18 अणु
	पूर्णांक instance;
	काष्ठा pci_dev *pci_dev;
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा v4l2_subdev *sd_av;     /* A/V decoder/digitizer sub-device */
	काष्ठा v4l2_subdev *sd_exपंचांगux; /* External multiplexer sub-dev */

	स्थिर काष्ठा cx18_card *card;	/* card inक्रमmation */
	स्थिर अक्षर *card_name;  /* full name of the card */
	स्थिर काष्ठा cx18_card_tuner_i2c *card_i2c; /* i2c addresses to probe क्रम tuner */
	u8 is_50hz;
	u8 is_60hz;
	u8 nof_inमाला_दो;		/* number of video inमाला_दो */
	u8 nof_audio_inमाला_दो;	/* number of audio inमाला_दो */
	u32 v4l2_cap;		/* V4L2 capabilities of card */
	u32 hw_flags;		/* Hardware description of the board */
	अचिन्हित पूर्णांक मुक्त_mdl_idx;
	काष्ठा cx18_scb __iomem *scb; /* poपूर्णांकer to SCB */
	काष्ठा mutex epu2apu_mb_lock; /* protect driver to chip mailbox in SCB*/
	काष्ठा mutex epu2cpu_mb_lock; /* protect driver to chip mailbox in SCB*/

	काष्ठा cx18_av_state av_state;

	/* codec settings */
	काष्ठा cx2341x_handler cxhdl;
	u32 filter_mode;
	u32 temporal_strength;
	u32 spatial_strength;

	/* dualwatch */
	अचिन्हित दीर्घ dualwatch_jअगरfies;
	u32 dualwatch_stereo_mode;

	काष्ठा mutex serialize_lock;    /* mutex used to serialize खोलो/बंद/start/stop/ioctl operations */
	काष्ठा cx18_options options;	/* User options */
	पूर्णांक stream_buffers[CX18_MAX_STREAMS]; /* # of buffers क्रम each stream */
	पूर्णांक stream_buf_size[CX18_MAX_STREAMS]; /* Stream buffer size */
	काष्ठा cx18_stream streams[CX18_MAX_STREAMS];	/* Stream data */
	काष्ठा snd_cx18_card *alsa; /* ALSA पूर्णांकerface क्रम PCM capture stream */
	व्योम (*pcm_announce_callback)(काष्ठा snd_cx18_card *card, u8 *pcm_data,
				      माप_प्रकार num_bytes);

	अचिन्हित दीर्घ i_flags;  /* global cx18 flags */
	atomic_t ana_capturing;	/* count number of active analog capture streams */
	atomic_t tot_capturing;	/* total count number of active capture streams */
	पूर्णांक search_pack_header;

	पूर्णांक खोलो_id;		/* incremented each समय an खोलो occurs, used as
				   unique ID. Starts at 1, so 0 can be used as
				   uninitialized value in the stream->id. */

	resource_माप_प्रकार base_addr;

	u8 card_rev;
	व्योम __iomem *enc_mem, *reg_mem;

	काष्ठा vbi_info vbi;

	u64 mpg_data_received;
	u64 vbi_data_inserted;

	रुको_queue_head_t mb_apu_रुकोq;
	रुको_queue_head_t mb_cpu_रुकोq;
	रुको_queue_head_t cap_w;
	/* when the current DMA is finished this queue is woken up */
	रुको_queue_head_t dma_रुकोq;

	u32 sw1_irq_mask;
	u32 sw2_irq_mask;
	u32 hw2_irq_mask;

	काष्ठा workqueue_काष्ठा *in_work_queue;
	अक्षर in_workq_name[11]; /* "cx18-NN-in" */
	काष्ठा cx18_in_work_order in_work_order[CX18_MAX_IN_WORK_ORDERS];
	अक्षर epu_debug_str[256]; /* CX18_EPU_DEBUG is rare: use shared space */

	/* i2c */
	काष्ठा i2c_adapter i2c_adap[2];
	काष्ठा i2c_algo_bit_data i2c_algo[2];
	काष्ठा cx18_i2c_algo_callback_data i2c_algo_cb_data[2];

	काष्ठा IR_i2c_init_data ir_i2c_init_data;

	/* gpio */
	u32 gpio_dir;
	u32 gpio_val;
	काष्ठा mutex gpio_lock;
	काष्ठा v4l2_subdev sd_gpiomux;
	काष्ठा v4l2_subdev sd_resetctrl;

	/* v4l2 and User settings */

	/* codec settings */
	u32 audio_input;
	u32 active_input;
	v4l2_std_id std;
	v4l2_std_id tuner_std;	/* The norm of the tuner (fixed) */

	/* Used क्रम cx18-alsa module loading */
	काष्ठा work_काष्ठा request_module_wk;
पूर्ण;

अटल अंतरभूत काष्ठा cx18 *to_cx18(काष्ठा v4l2_device *v4l2_dev)
अणु
	वापस container_of(v4l2_dev, काष्ठा cx18, v4l2_dev);
पूर्ण

/* cx18 extensions to be loaded */
बाह्य पूर्णांक (*cx18_ext_init)(काष्ठा cx18 *);

/* Globals */
बाह्य पूर्णांक cx18_first_minor;

/*==============Prototypes==================*/

/* Return non-zero अगर a संकेत is pending */
पूर्णांक cx18_msleep_समयout(अचिन्हित पूर्णांक msecs, पूर्णांक पूर्णांकr);

/* Read Hauppauge eeprom */
काष्ठा tveeprom; /* क्रमward reference */
व्योम cx18_पढ़ो_eeprom(काष्ठा cx18 *cx, काष्ठा tveeprom *tv);

/* First-खोलो initialization: load firmware, etc. */
पूर्णांक cx18_init_on_first_खोलो(काष्ठा cx18 *cx);

/* Test अगर the current VBI mode is raw (1) or sliced (0) */
अटल अंतरभूत पूर्णांक cx18_raw_vbi(स्थिर काष्ठा cx18 *cx)
अणु
	वापस cx->vbi.in.type == V4L2_BUF_TYPE_VBI_CAPTURE;
पूर्ण

/* Call the specअगरied callback क्रम all subdevs with a grp_id bit matching the
 * mask in hw (अगर 0, then match them all). Ignore any errors. */
#घोषणा cx18_call_hw(cx, hw, o, f, args...)				\
	v4l2_device_mask_call_all(&(cx)->v4l2_dev, hw, o, f, ##args)

#घोषणा cx18_call_all(cx, o, f, args...) cx18_call_hw(cx, 0, o, f , ##args)

/* Call the specअगरied callback क्रम all subdevs with a grp_id bit matching the
 * mask in hw (अगर 0, then match them all). If the callback वापसs an error
 * other than 0 or -ENOIOCTLCMD, then वापस with that error code. */
#घोषणा cx18_call_hw_err(cx, hw, o, f, args...)				\
	v4l2_device_mask_call_until_err(&(cx)->v4l2_dev, hw, o, f, ##args)

#घोषणा cx18_call_all_err(cx, o, f, args...) \
	cx18_call_hw_err(cx, 0, o, f , ##args)

#पूर्ण_अगर /* CX18_DRIVER_H */
