<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2010-2013 Bluecherry, LLC <https://www.bluecherrydvr.com>
 *
 * Original author:
 * Ben Collins <bcollins@ubuntu.com>
 *
 * Additional work by:
 * John Brooks <john.brooks@bluecherry.net>
 */

#अगर_अघोषित __SOLO6X10_H
#घोषणा __SOLO6X10_H

#समावेश <linux/pci.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/रुको.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/पन.स>
#समावेश <linux/atomic.h>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/gpio/driver.h>

#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/videobuf2-v4l2.h>

#समावेश "solo6x10-regs.h"

#अगर_अघोषित PCI_VENDOR_ID_SOFTLOGIC
#घोषणा PCI_VENDOR_ID_SOFTLOGIC		0x9413
#घोषणा PCI_DEVICE_ID_SOLO6010		0x6010
#घोषणा PCI_DEVICE_ID_SOLO6110		0x6110
#पूर्ण_अगर

#अगर_अघोषित PCI_VENDOR_ID_BLUECHERRY
#घोषणा PCI_VENDOR_ID_BLUECHERRY	0x1BB3
/* Neugent Softlogic 6010 based cards */
#घोषणा PCI_DEVICE_ID_NEUSOLO_4		0x4304
#घोषणा PCI_DEVICE_ID_NEUSOLO_9		0x4309
#घोषणा PCI_DEVICE_ID_NEUSOLO_16	0x4310
/* Bluecherry Softlogic 6010 based cards */
#घोषणा PCI_DEVICE_ID_BC_SOLO_4		0x4E04
#घोषणा PCI_DEVICE_ID_BC_SOLO_9		0x4E09
#घोषणा PCI_DEVICE_ID_BC_SOLO_16	0x4E10
/* Bluecherry Softlogic 6110 based cards */
#घोषणा PCI_DEVICE_ID_BC_6110_4		0x5304
#घोषणा PCI_DEVICE_ID_BC_6110_8		0x5308
#घोषणा PCI_DEVICE_ID_BC_6110_16	0x5310
#पूर्ण_अगर /* Bluecherry */

/* Used in pci_device_id, and solo_dev->type */
#घोषणा SOLO_DEV_6010			0
#घोषणा SOLO_DEV_6110			1

#घोषणा SOLO6X10_NAME			"solo6x10"

#घोषणा SOLO_MAX_CHANNELS		16

#घोषणा SOLO6X10_VERSION		"3.0.0"

/*
 * The SOLO6x10 actually has 8 i2c channels, but we only use 2.
 * 0 - Techwell chip(s)
 * 1 - SAA7128
 */
#घोषणा SOLO_I2C_ADAPTERS		2
#घोषणा SOLO_I2C_TW			0
#घोषणा SOLO_I2C_SAA			1

/* DMA Engine setup */
#घोषणा SOLO_NR_P2M			4
#घोषणा SOLO_NR_P2M_DESC		256
#घोषणा SOLO_P2M_DESC_SIZE		(SOLO_NR_P2M_DESC * 16)

/* Encoder standard modes */
#घोषणा SOLO_ENC_MODE_CIF		2
#घोषणा SOLO_ENC_MODE_HD1		1
#घोषणा SOLO_ENC_MODE_D1		9

#घोषणा SOLO_DEFAULT_QP			3

#घोषणा SOLO_CID_CUSTOM_BASE		(V4L2_CID_USER_BASE | 0xf000)
#घोषणा V4L2_CID_MOTION_TRACE		(SOLO_CID_CUSTOM_BASE+2)
#घोषणा V4L2_CID_OSD_TEXT		(SOLO_CID_CUSTOM_BASE+3)

/*
 * Motion thresholds are in a table of 64x64 samples, with
 * each sample representing 16x16 pixels of the source. In
 * effect, 44x30 samples are used क्रम NTSC, and 44x36 क्रम PAL.
 * The 5th sample on the 10th row is (10*64)+5 = 645.
 *
 * Internally it is stored as a 45x45 array (45*16 = 720, which is the
 * maximum PAL/NTSC width).
 */
#घोषणा SOLO_MOTION_SZ (45)

क्रमागत SOLO_I2C_STATE अणु
	IIC_STATE_IDLE,
	IIC_STATE_START,
	IIC_STATE_READ,
	IIC_STATE_WRITE,
	IIC_STATE_STOP
पूर्ण;

/* Defined in Table 4-16, Page 68-69 of the 6010 Datasheet */
काष्ठा solo_p2m_desc अणु
	u32	ctrl;
	u32	cfg;
	u32	dma_addr;
	u32	ext_addr;
पूर्ण;

काष्ठा solo_p2m_dev अणु
	काष्ठा mutex		mutex;
	काष्ठा completion	completion;
	पूर्णांक			desc_count;
	पूर्णांक			desc_idx;
	काष्ठा solo_p2m_desc	*descs;
	पूर्णांक			error;
पूर्ण;

#घोषणा OSD_TEXT_MAX		44

काष्ठा solo_vb2_buf अणु
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head list;
पूर्ण;

क्रमागत solo_enc_types अणु
	SOLO_ENC_TYPE_STD,
	SOLO_ENC_TYPE_EXT,
पूर्ण;

काष्ठा solo_enc_dev अणु
	काष्ठा solo_dev	*solo_dev;
	/* V4L2 Items */
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा v4l2_ctrl *md_thresholds;
	काष्ठा video_device	*vfd;
	/* General accounting */
	काष्ठा mutex		lock;
	spinlock_t		motion_lock;
	u8			ch;
	u8			mode, gop, qp, पूर्णांकerlaced, पूर्णांकerval;
	u8			bw_weight;
	u16			motion_thresh;
	bool			motion_global;
	bool			motion_enabled;
	u16			width;
	u16			height;

	/* OSD buffers */
	अक्षर			osd_text[OSD_TEXT_MAX + 1];
	u8			osd_buf[SOLO_EOSD_EXT_SIZE_MAX]
					__aligned(4);

	/* VOP stuff */
	u8			vop[64];
	पूर्णांक			vop_len;
	u8			jpeg_header[1024];
	पूर्णांक			jpeg_len;

	u32			fmt;
	क्रमागत solo_enc_types	type;
	u32			sequence;
	काष्ठा vb2_queue	vidq;
	काष्ठा list_head	vidq_active;
	पूर्णांक			desc_count;
	पूर्णांक			desc_nelts;
	काष्ठा solo_p2m_desc	*desc_items;
	dma_addr_t		desc_dma;
	spinlock_t		av_lock;
पूर्ण;

/* The SOLO6x10 PCI Device */
काष्ठा solo_dev अणु
	/* General stuff */
	काष्ठा pci_dev		*pdev;
	पूर्णांक			type;
	अचिन्हित पूर्णांक		समय_sync;
	अचिन्हित पूर्णांक		usec_lsb;
	अचिन्हित पूर्णांक		घड़ी_mhz;
	u8 __iomem		*reg_base;
	पूर्णांक			nr_chans;
	पूर्णांक			nr_ext;
	u32			irq_mask;
	u32			motion_mask;
	काष्ठा v4l2_device	v4l2_dev;
#अगर_घोषित CONFIG_GPIOLIB
	/* GPIO */
	काष्ठा gpio_chip	gpio_dev;
#पूर्ण_अगर

	/* tw28xx accounting */
	u8			tw2865, tw2864, tw2815;
	u8			tw28_cnt;

	/* i2c related items */
	काष्ठा i2c_adapter	i2c_adap[SOLO_I2C_ADAPTERS];
	क्रमागत SOLO_I2C_STATE	i2c_state;
	काष्ठा mutex		i2c_mutex;
	पूर्णांक			i2c_id;
	रुको_queue_head_t	i2c_रुको;
	काष्ठा i2c_msg		*i2c_msg;
	अचिन्हित पूर्णांक		i2c_msg_num;
	अचिन्हित पूर्णांक		i2c_msg_ptr;

	/* P2M DMA Engine */
	काष्ठा solo_p2m_dev	p2m_dev[SOLO_NR_P2M];
	atomic_t		p2m_count;
	पूर्णांक			p2m_jअगरfies;
	अचिन्हित पूर्णांक		p2m_समयouts;

	/* V4L2 Display items */
	काष्ठा video_device	*vfd;
	अचिन्हित पूर्णांक		erasing;
	अचिन्हित पूर्णांक		frame_blank;
	u8			cur_disp_ch;
	रुको_queue_head_t	disp_thपढ़ो_रुको;
	काष्ठा v4l2_ctrl_handler disp_hdl;

	/* V4L2 Encoder items */
	काष्ठा solo_enc_dev	*v4l2_enc[SOLO_MAX_CHANNELS];
	u16			enc_bw_reमुख्य;
	/* IDX पूर्णांकo hw mp4 encoder */
	u8			enc_idx;

	/* Current video settings */
	u32			video_type;
	u16			video_hsize, video_vsize;
	u16			vout_hstart, vout_vstart;
	u16			vin_hstart, vin_vstart;
	u8			fps;

	/* JPEG Qp setting */
	spinlock_t      jpeg_qp_lock;
	u32		jpeg_qp[2];

	/* Audio components */
	काष्ठा snd_card		*snd_card;
	काष्ठा snd_pcm		*snd_pcm;
	atomic_t		snd_users;
	पूर्णांक			g723_hw_idx;

	/* sysfs stuffs */
	काष्ठा device		dev;
	पूर्णांक			sdram_size;
	काष्ठा bin_attribute	sdram_attr;
	अचिन्हित पूर्णांक		sys_config;

	/* Ring thपढ़ो */
	काष्ठा task_काष्ठा	*ring_thपढ़ो;
	रुको_queue_head_t	ring_thपढ़ो_रुको;

	/* VOP_HEADER handling */
	व्योम                    *vh_buf;
	dma_addr_t		vh_dma;
	पूर्णांक			vh_size;

	/* Buffer handling */
	काष्ठा vb2_queue	vidq;
	u32			sequence;
	काष्ठा task_काष्ठा      *kthपढ़ो;
	काष्ठा mutex		lock;
	spinlock_t		slock;
	पूर्णांक			old_ग_लिखो;
	काष्ठा list_head	vidq_active;
पूर्ण;

अटल अंतरभूत u32 solo_reg_पढ़ो(काष्ठा solo_dev *solo_dev, पूर्णांक reg)
अणु
	वापस पढ़ोl(solo_dev->reg_base + reg);
पूर्ण

अटल अंतरभूत व्योम solo_reg_ग_लिखो(काष्ठा solo_dev *solo_dev, पूर्णांक reg,
				  u32 data)
अणु
	u16 val;

	ग_लिखोl(data, solo_dev->reg_base + reg);
	pci_पढ़ो_config_word(solo_dev->pdev, PCI_STATUS, &val);
पूर्ण

अटल अंतरभूत व्योम solo_irq_on(काष्ठा solo_dev *dev, u32 mask)
अणु
	dev->irq_mask |= mask;
	solo_reg_ग_लिखो(dev, SOLO_IRQ_MASK, dev->irq_mask);
पूर्ण

अटल अंतरभूत व्योम solo_irq_off(काष्ठा solo_dev *dev, u32 mask)
अणु
	dev->irq_mask &= ~mask;
	solo_reg_ग_लिखो(dev, SOLO_IRQ_MASK, dev->irq_mask);
पूर्ण

/* Init/निकास routines क्रम subप्रणालीs */
पूर्णांक solo_disp_init(काष्ठा solo_dev *solo_dev);
व्योम solo_disp_निकास(काष्ठा solo_dev *solo_dev);

पूर्णांक solo_gpio_init(काष्ठा solo_dev *solo_dev);
व्योम solo_gpio_निकास(काष्ठा solo_dev *solo_dev);

पूर्णांक solo_i2c_init(काष्ठा solo_dev *solo_dev);
व्योम solo_i2c_निकास(काष्ठा solo_dev *solo_dev);

पूर्णांक solo_p2m_init(काष्ठा solo_dev *solo_dev);
व्योम solo_p2m_निकास(काष्ठा solo_dev *solo_dev);

पूर्णांक solo_v4l2_init(काष्ठा solo_dev *solo_dev, अचिन्हित nr);
व्योम solo_v4l2_निकास(काष्ठा solo_dev *solo_dev);

पूर्णांक solo_enc_init(काष्ठा solo_dev *solo_dev);
व्योम solo_enc_निकास(काष्ठा solo_dev *solo_dev);

पूर्णांक solo_enc_v4l2_init(काष्ठा solo_dev *solo_dev, अचिन्हित nr);
व्योम solo_enc_v4l2_निकास(काष्ठा solo_dev *solo_dev);

पूर्णांक solo_g723_init(काष्ठा solo_dev *solo_dev);
व्योम solo_g723_निकास(काष्ठा solo_dev *solo_dev);

/* ISR's */
पूर्णांक solo_i2c_isr(काष्ठा solo_dev *solo_dev);
व्योम solo_p2m_isr(काष्ठा solo_dev *solo_dev, पूर्णांक id);
व्योम solo_p2m_error_isr(काष्ठा solo_dev *solo_dev);
व्योम solo_enc_v4l2_isr(काष्ठा solo_dev *solo_dev);
व्योम solo_g723_isr(काष्ठा solo_dev *solo_dev);
व्योम solo_motion_isr(काष्ठा solo_dev *solo_dev);
व्योम solo_video_in_isr(काष्ठा solo_dev *solo_dev);

/* i2c पढ़ो/ग_लिखो */
u8 solo_i2c_पढ़ोbyte(काष्ठा solo_dev *solo_dev, पूर्णांक id, u8 addr, u8 off);
व्योम solo_i2c_ग_लिखोbyte(काष्ठा solo_dev *solo_dev, पूर्णांक id, u8 addr, u8 off,
			u8 data);

/* P2M DMA */
पूर्णांक solo_p2m_dma_t(काष्ठा solo_dev *solo_dev, पूर्णांक wr,
		   dma_addr_t dma_addr, u32 ext_addr, u32 size,
		   पूर्णांक repeat, u32 ext_size);
पूर्णांक solo_p2m_dma(काष्ठा solo_dev *solo_dev, पूर्णांक wr,
		 व्योम *sys_addr, u32 ext_addr, u32 size,
		 पूर्णांक repeat, u32 ext_size);
व्योम solo_p2m_fill_desc(काष्ठा solo_p2m_desc *desc, पूर्णांक wr,
			dma_addr_t dma_addr, u32 ext_addr, u32 size,
			पूर्णांक repeat, u32 ext_size);
पूर्णांक solo_p2m_dma_desc(काष्ठा solo_dev *solo_dev,
		      काष्ठा solo_p2m_desc *desc, dma_addr_t desc_dma,
		      पूर्णांक desc_cnt);

/* Global s_std ioctl */
पूर्णांक solo_set_video_type(काष्ठा solo_dev *solo_dev, bool is_50hz);
व्योम solo_update_mode(काष्ठा solo_enc_dev *solo_enc);

/* Set the threshold क्रम motion detection */
पूर्णांक solo_set_motion_threshold(काष्ठा solo_dev *solo_dev, u8 ch, u16 val);
पूर्णांक solo_set_motion_block(काष्ठा solo_dev *solo_dev, u8 ch,
		स्थिर u16 *thresholds);
#घोषणा SOLO_DEF_MOT_THRESH		0x0300

/* Write text on OSD */
पूर्णांक solo_osd_prपूर्णांक(काष्ठा solo_enc_dev *solo_enc);

/* EEPROM commands */
अचिन्हित पूर्णांक solo_eeprom_ewen(काष्ठा solo_dev *solo_dev, पूर्णांक w_en);
__be16 solo_eeprom_पढ़ो(काष्ठा solo_dev *solo_dev, पूर्णांक loc);
पूर्णांक solo_eeprom_ग_लिखो(काष्ठा solo_dev *solo_dev, पूर्णांक loc,
		      __be16 data);

/* JPEG Qp functions */
व्योम solo_s_jpeg_qp(काष्ठा solo_dev *solo_dev, अचिन्हित पूर्णांक ch,
		    अचिन्हित पूर्णांक qp);
पूर्णांक solo_g_jpeg_qp(काष्ठा solo_dev *solo_dev, अचिन्हित पूर्णांक ch);

#घोषणा CHK_FLAGS(v, flags) (((v) & (flags)) == (flags))

#पूर्ण_अगर /* __SOLO6X10_H */
