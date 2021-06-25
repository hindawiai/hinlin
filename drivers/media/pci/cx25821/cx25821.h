<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Driver क्रम the Conexant CX25821 PCIe bridge
 *
 *  Copyright (C) 2009 Conexant Systems Inc.
 *  Authors  <shu.lin@conexant.com>, <hiep.huynh@conexant.com>
 *  Based on Steven Toth <stoth@linuxtv.org> cx23885 driver
 */

#अगर_अघोषित CX25821_H_
#घोषणा CX25821_H_

#समावेश <linux/pci.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/kdev_t.h>

#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-dma-sg.h>

#समावेश "cx25821-reg.h"
#समावेश "cx25821-medusa-reg.h"
#समावेश "cx25821-sram.h"
#समावेश "cx25821-audio.h"

#समावेश <linux/mutex.h>

#घोषणा UNSET (-1U)
#घोषणा NO_SYNC_LINE (-1U)

#घोषणा CX25821_MAXBOARDS 2

#घोषणा LINE_SIZE_D1    1440

/* Number of decoders and encoders */
#घोषणा MAX_DECODERS            8
#घोषणा MAX_ENCODERS            2
#घोषणा QUAD_DECODERS           4
#घोषणा MAX_CAMERAS             16

/* Max number of inमाला_दो by card */
#घोषणा MAX_CX25821_INPUT     8
#घोषणा RESOURCE_VIDEO0       1
#घोषणा RESOURCE_VIDEO1       2
#घोषणा RESOURCE_VIDEO2       4
#घोषणा RESOURCE_VIDEO3       8
#घोषणा RESOURCE_VIDEO4       16
#घोषणा RESOURCE_VIDEO5       32
#घोषणा RESOURCE_VIDEO6       64
#घोषणा RESOURCE_VIDEO7       128
#घोषणा RESOURCE_VIDEO8       256
#घोषणा RESOURCE_VIDEO9       512
#घोषणा RESOURCE_VIDEO10      1024
#घोषणा RESOURCE_VIDEO11      2048

#घोषणा BUFFER_TIMEOUT     (HZ)	/* 0.5 seconds */

#घोषणा UNKNOWN_BOARD        0
#घोषणा CX25821_BOARD        1

/* Currently supported by the driver */
#घोषणा CX25821_NORMS (\
	V4L2_STD_NTSC_M |  V4L2_STD_NTSC_M_JP | V4L2_STD_NTSC_M_KR | \
	V4L2_STD_PAL_BG |  V4L2_STD_PAL_DK    |  V4L2_STD_PAL_I    | \
	V4L2_STD_PAL_M  |  V4L2_STD_PAL_N     |  V4L2_STD_PAL_H    | \
	V4L2_STD_PAL_Nc)

#घोषणा CX25821_BOARD_CONEXANT_ATHENA10 1
#घोषणा MAX_VID_CHANNEL_NUM     12

/*
 * Maximum capture-only channels. This can go away once video/audio output
 * is fully supported in this driver.
 */
#घोषणा MAX_VID_CAP_CHANNEL_NUM     10

#घोषणा VID_CHANNEL_NUM 8

काष्ठा cx25821_fmt अणु
	u32 fourcc;		/* v4l2 क्रमmat id */
	पूर्णांक depth;
	पूर्णांक flags;
	u32 cxक्रमmat;
पूर्ण;

काष्ठा cx25821_tvnorm अणु
	अक्षर *name;
	v4l2_std_id id;
	u32 cxअगरormat;
	u32 cxoक्रमmat;
पूर्ण;

क्रमागत cx25821_src_sel_type अणु
	CX25821_SRC_SEL_EXT_656_VIDEO = 0,
	CX25821_SRC_SEL_PARALLEL_MPEG_VIDEO
पूर्ण;

काष्ठा cx25821_riscmem अणु
	अचिन्हित पूर्णांक   size;
	__le32         *cpu;
	__le32         *jmp;
	dma_addr_t     dma;
पूर्ण;

/* buffer क्रम one video frame */
काष्ठा cx25821_buffer अणु
	/* common v4l buffer stuff -- must be first */
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head queue;

	/* cx25821 specअगरic */
	अचिन्हित पूर्णांक bpl;
	काष्ठा cx25821_riscmem risc;
	स्थिर काष्ठा cx25821_fmt *fmt;
पूर्ण;

क्रमागत port अणु
	CX25821_UNDEFINED = 0,
	CX25821_RAW,
	CX25821_264
पूर्ण;

काष्ठा cx25821_board अणु
	स्थिर अक्षर *name;
	क्रमागत port porta;
	क्रमागत port portb;
	क्रमागत port portc;

	u32 clk_freq;
पूर्ण;

काष्ठा cx25821_i2c अणु
	काष्ठा cx25821_dev *dev;

	पूर्णांक nr;

	/* i2c i/o */
	काष्ठा i2c_adapter i2c_adap;
	काष्ठा i2c_client i2c_client;
	u32 i2c_rc;

	/* cx25821 रेजिस्टरs used क्रम raw address */
	u32 i2c_period;
	u32 reg_ctrl;
	u32 reg_stat;
	u32 reg_addr;
	u32 reg_rdata;
	u32 reg_wdata;
पूर्ण;

काष्ठा cx25821_dmaqueue अणु
	काष्ठा list_head active;
	u32 count;
पूर्ण;

काष्ठा cx25821_dev;

काष्ठा cx25821_channel;

काष्ठा cx25821_video_out_data अणु
	काष्ठा cx25821_channel *chan;
	पूर्णांक _line_size;
	पूर्णांक _prog_cnt;
	पूर्णांक _pixel_क्रमmat;
	पूर्णांक _is_first_frame;
	पूर्णांक _is_running;
	पूर्णांक _file_status;
	पूर्णांक _lines_count;
	पूर्णांक _frame_count;
	अचिन्हित पूर्णांक _risc_size;

	__le32 *_dma_virt_start_addr;
	__le32 *_dma_virt_addr;
	dma_addr_t _dma_phys_addr;
	dma_addr_t _dma_phys_start_addr;

	अचिन्हित पूर्णांक _data_buf_size;
	__le32 *_data_buf_virt_addr;
	dma_addr_t _data_buf_phys_addr;

	u32 upstream_riscbuf_size;
	u32 upstream_databuf_size;
	पूर्णांक is_60hz;
	पूर्णांक _frame_index;
	पूर्णांक cur_frame_index;
	पूर्णांक curpos;
	रुको_queue_head_t रुकोq;
पूर्ण;

काष्ठा cx25821_channel अणु
	अचिन्हित id;
	काष्ठा cx25821_dev *dev;

	काष्ठा v4l2_ctrl_handler hdl;

	काष्ठा video_device vdev;
	काष्ठा cx25821_dmaqueue dma_vidq;
	काष्ठा vb2_queue vidq;

	स्थिर काष्ठा sram_channel *sram_channels;

	स्थिर काष्ठा cx25821_fmt *fmt;
	अचिन्हित field;
	अचिन्हित पूर्णांक width, height;
	पूर्णांक pixel_क्रमmats;
	पूर्णांक use_cअगर_resolution;
	पूर्णांक cअगर_width;

	/* video output data क्रम the video output channel */
	काष्ठा cx25821_video_out_data *out;
पूर्ण;

काष्ठा snd_card;

काष्ठा cx25821_dev अणु
	काष्ठा v4l2_device v4l2_dev;

	/* pci stuff */
	काष्ठा pci_dev *pci;
	अचिन्हित अक्षर pci_rev, pci_lat;
	पूर्णांक pci_bus, pci_slot;
	u32 base_io_addr;
	u32 __iomem *lmmio;
	u8 __iomem *bmmio;
	पूर्णांक pci_irqmask;
	पूर्णांक hwrevision;
	/* used by cx25821-alsa */
	काष्ठा snd_card *card;

	u32 clk_freq;

	/* I2C adapters: Master 1 & 2 (External) & Master 3 (Internal only) */
	काष्ठा cx25821_i2c i2c_bus[3];

	पूर्णांक nr;
	काष्ठा mutex lock;

	काष्ठा cx25821_channel channels[MAX_VID_CHANNEL_NUM];

	/* board details */
	अचिन्हित पूर्णांक board;
	अक्षर name[32];

	/* Analog video */
	अचिन्हित पूर्णांक input;
	v4l2_std_id tvnorm;
	अचिन्हित लघु _max_num_decoders;

	/* Analog Audio Upstream */
	पूर्णांक _audio_is_running;
	पूर्णांक _audiopixel_क्रमmat;
	पूर्णांक _is_first_audio_frame;
	पूर्णांक _audiofile_status;
	पूर्णांक _audio_lines_count;
	पूर्णांक _audioframe_count;
	पूर्णांक _audio_upstream_channel;
	पूर्णांक _last_index_irq;    /* The last पूर्णांकerrupt index processed. */

	__le32 *_risc_audio_jmp_addr;
	__le32 *_risc_virt_start_addr;
	__le32 *_risc_virt_addr;
	dma_addr_t _risc_phys_addr;
	dma_addr_t _risc_phys_start_addr;

	अचिन्हित पूर्णांक _audiorisc_size;
	अचिन्हित पूर्णांक _audiodata_buf_size;
	__le32 *_audiodata_buf_virt_addr;
	dma_addr_t _audiodata_buf_phys_addr;
	अक्षर *_audiofilename;
	u32 audio_upstream_riscbuf_size;
	u32 audio_upstream_databuf_size;
	पूर्णांक _audioframe_index;
	काष्ठा work_काष्ठा _audio_work_entry;
	अक्षर *input_audiofilename;

	/* V4l */
	spinlock_t slock;

	/* Video Upstream */
	काष्ठा cx25821_video_out_data vid_out_data[2];
पूर्ण;

अटल अंतरभूत काष्ठा cx25821_dev *get_cx25821(काष्ठा v4l2_device *v4l2_dev)
अणु
	वापस container_of(v4l2_dev, काष्ठा cx25821_dev, v4l2_dev);
पूर्ण

बाह्य काष्ठा cx25821_board cx25821_boards[];

#घोषणा SRAM_CH00  0		/* Video A */
#घोषणा SRAM_CH01  1		/* Video B */
#घोषणा SRAM_CH02  2		/* Video C */
#घोषणा SRAM_CH03  3		/* Video D */
#घोषणा SRAM_CH04  4		/* Video E */
#घोषणा SRAM_CH05  5		/* Video F */
#घोषणा SRAM_CH06  6		/* Video G */
#घोषणा SRAM_CH07  7		/* Video H */

#घोषणा SRAM_CH08  8		/* Audio A */
#घोषणा SRAM_CH09  9		/* Video Upstream I */
#घोषणा SRAM_CH10  10		/* Video Upstream J */
#घोषणा SRAM_CH11  11		/* Audio Upstream AUD_CHANNEL_B */

#घोषणा VID_UPSTREAM_SRAM_CHANNEL_I     SRAM_CH09
#घोषणा VID_UPSTREAM_SRAM_CHANNEL_J     SRAM_CH10
#घोषणा AUDIO_UPSTREAM_SRAM_CHANNEL_B   SRAM_CH11

काष्ठा sram_channel अणु
	अक्षर *name;
	u32 i;
	u32 cmds_start;
	u32 ctrl_start;
	u32 cdt;
	u32 fअगरo_start;
	u32 fअगरo_size;
	u32 ptr1_reg;
	u32 ptr2_reg;
	u32 cnt1_reg;
	u32 cnt2_reg;
	u32 पूर्णांक_msk;
	u32 पूर्णांक_stat;
	u32 पूर्णांक_mstat;
	u32 dma_ctl;
	u32 gpcnt_ctl;
	u32 gpcnt;
	u32 aud_length;
	u32 aud_cfg;
	u32 fld_aud_fअगरo_en;
	u32 fld_aud_risc_en;

	/* For Upstream Video */
	u32 vid_fmt_ctl;
	u32 vid_active_ctl1;
	u32 vid_active_ctl2;
	u32 vid_cdt_size;

	u32 vip_ctl;
	u32 pix_frmt;
	u32 jumponly;
	u32 irq_bit;
पूर्ण;

बाह्य स्थिर काष्ठा sram_channel cx25821_sram_channels[];

#घोषणा cx_पढ़ो(reg)             पढ़ोl(dev->lmmio + ((reg)>>2))
#घोषणा cx_ग_लिखो(reg, value)     ग_लिखोl((value), dev->lmmio + ((reg)>>2))

#घोषणा cx_anकरोr(reg, mask, value) \
	ग_लिखोl((पढ़ोl(dev->lmmio+((reg)>>2)) & ~(mask)) |\
	((value) & (mask)), dev->lmmio+((reg)>>2))

#घोषणा cx_set(reg, bit)          cx_anकरोr((reg), (bit), (bit))
#घोषणा cx_clear(reg, bit)        cx_anकरोr((reg), (bit), 0)

#घोषणा Set_GPIO_Bit(Bit)                       (1 << Bit)
#घोषणा Clear_GPIO_Bit(Bit)                     (~(1 << Bit))

#घोषणा CX25821_ERR(fmt, args...)			\
	pr_err("(%d): " fmt, dev->board, ##args)
#घोषणा CX25821_WARN(fmt, args...)			\
	pr_warn("(%d): " fmt, dev->board, ##args)
#घोषणा CX25821_INFO(fmt, args...)			\
	pr_info("(%d): " fmt, dev->board, ##args)

बाह्य पूर्णांक cx25821_i2c_रेजिस्टर(काष्ठा cx25821_i2c *bus);
बाह्य पूर्णांक cx25821_i2c_पढ़ो(काष्ठा cx25821_i2c *bus, u16 reg_addr, पूर्णांक *value);
बाह्य पूर्णांक cx25821_i2c_ग_लिखो(काष्ठा cx25821_i2c *bus, u16 reg_addr, पूर्णांक value);
बाह्य पूर्णांक cx25821_i2c_unरेजिस्टर(काष्ठा cx25821_i2c *bus);
बाह्य व्योम cx25821_gpio_init(काष्ठा cx25821_dev *dev);
बाह्य व्योम cx25821_set_gpiopin_direction(काष्ठा cx25821_dev *dev,
					  पूर्णांक pin_number, पूर्णांक pin_logic_value);

बाह्य पूर्णांक medusa_video_init(काष्ठा cx25821_dev *dev);
बाह्य पूर्णांक medusa_set_videostandard(काष्ठा cx25821_dev *dev);
बाह्य व्योम medusa_set_resolution(काष्ठा cx25821_dev *dev, पूर्णांक width,
				  पूर्णांक decoder_select);
बाह्य पूर्णांक medusa_set_brightness(काष्ठा cx25821_dev *dev, पूर्णांक brightness,
				 पूर्णांक decoder);
बाह्य पूर्णांक medusa_set_contrast(काष्ठा cx25821_dev *dev, पूर्णांक contrast,
			       पूर्णांक decoder);
बाह्य पूर्णांक medusa_set_hue(काष्ठा cx25821_dev *dev, पूर्णांक hue, पूर्णांक decoder);
बाह्य पूर्णांक medusa_set_saturation(काष्ठा cx25821_dev *dev, पूर्णांक saturation,
				 पूर्णांक decoder);

बाह्य पूर्णांक cx25821_sram_channel_setup(काष्ठा cx25821_dev *dev,
				      स्थिर काष्ठा sram_channel *ch, अचिन्हित पूर्णांक bpl,
				      u32 risc);

बाह्य पूर्णांक cx25821_riscmem_alloc(काष्ठा pci_dev *pci,
				 काष्ठा cx25821_riscmem *risc,
				 अचिन्हित पूर्णांक size);
बाह्य पूर्णांक cx25821_risc_buffer(काष्ठा pci_dev *pci, काष्ठा cx25821_riscmem *risc,
			       काष्ठा scatterlist *sglist,
			       अचिन्हित पूर्णांक top_offset,
			       अचिन्हित पूर्णांक bottom_offset,
			       अचिन्हित पूर्णांक bpl,
			       अचिन्हित पूर्णांक padding, अचिन्हित पूर्णांक lines);
बाह्य पूर्णांक cx25821_risc_databuffer_audio(काष्ठा pci_dev *pci,
					 काष्ठा cx25821_riscmem *risc,
					 काष्ठा scatterlist *sglist,
					 अचिन्हित पूर्णांक bpl,
					 अचिन्हित पूर्णांक lines, अचिन्हित पूर्णांक lpi);
बाह्य व्योम cx25821_मुक्त_buffer(काष्ठा cx25821_dev *dev,
				काष्ठा cx25821_buffer *buf);
बाह्य व्योम cx25821_sram_channel_dump(काष्ठा cx25821_dev *dev,
				      स्थिर काष्ठा sram_channel *ch);
बाह्य व्योम cx25821_sram_channel_dump_audio(काष्ठा cx25821_dev *dev,
					    स्थिर काष्ठा sram_channel *ch);

बाह्य काष्ठा cx25821_dev *cx25821_dev_get(काष्ठा pci_dev *pci);
बाह्य व्योम cx25821_prपूर्णांक_irqbits(अक्षर *name, अक्षर *tag, अक्षर **strings,
				  पूर्णांक len, u32 bits, u32 mask);
बाह्य व्योम cx25821_dev_unरेजिस्टर(काष्ठा cx25821_dev *dev);
बाह्य पूर्णांक cx25821_sram_channel_setup_audio(काष्ठा cx25821_dev *dev,
					    स्थिर काष्ठा sram_channel *ch,
					    अचिन्हित पूर्णांक bpl, u32 risc);

बाह्य व्योम cx25821_set_pixel_क्रमmat(काष्ठा cx25821_dev *dev, पूर्णांक channel,
				     u32 क्रमmat);

#पूर्ण_अगर
