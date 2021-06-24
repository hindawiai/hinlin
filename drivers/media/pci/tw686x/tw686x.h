<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2015 VanguardiaSur - www.vanguardiasur.com.ar
 *
 * Copyright (C) 2015 Industrial Research Institute क्रम Automation
 * and Measurements PIAP
 * Written by Krzysztof Ha?asa
 */

#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/समयr.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <sound/pcm.h>

#समावेश "tw686x-regs.h"

#घोषणा TYPE_MAX_CHANNELS	0x0f
#घोषणा TYPE_SECOND_GEN		0x10
#घोषणा TW686X_DEF_PHASE_REF	0x1518

#घोषणा TW686X_AUDIO_PAGE_MAX		16
#घोषणा TW686X_AUDIO_PERIODS_MIN	2
#घोषणा TW686X_AUDIO_PERIODS_MAX	TW686X_AUDIO_PAGE_MAX

#घोषणा TW686X_DMA_MODE_MEMCPY		0
#घोषणा TW686X_DMA_MODE_CONTIG		1
#घोषणा TW686X_DMA_MODE_SG		2

काष्ठा tw686x_क्रमmat अणु
	अक्षर *name;
	अचिन्हित पूर्णांक fourcc;
	अचिन्हित पूर्णांक depth;
	अचिन्हित पूर्णांक mode;
पूर्ण;

काष्ठा tw686x_dma_desc अणु
	dma_addr_t phys;
	व्योम *virt;
	अचिन्हित पूर्णांक size;
पूर्ण;

काष्ठा tw686x_sg_desc अणु
	/* 3 MSBits क्रम flags, 13 LSBits क्रम length */
	__le32 flags_length;
	__le32 phys;
पूर्ण;

काष्ठा tw686x_audio_buf अणु
	dma_addr_t dma;
	व्योम *virt;
	काष्ठा list_head list;
पूर्ण;

काष्ठा tw686x_v4l2_buf अणु
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head list;
पूर्ण;

काष्ठा tw686x_audio_channel अणु
	काष्ठा tw686x_dev *dev;
	काष्ठा snd_pcm_substream *ss;
	अचिन्हित पूर्णांक ch;
	काष्ठा tw686x_audio_buf *curr_bufs[2];
	काष्ठा tw686x_dma_desc dma_descs[2];
	dma_addr_t ptr;

	काष्ठा tw686x_audio_buf buf[TW686X_AUDIO_PAGE_MAX];
	काष्ठा list_head buf_list;
	spinlock_t lock;
पूर्ण;

काष्ठा tw686x_video_channel अणु
	काष्ठा tw686x_dev *dev;

	काष्ठा vb2_queue vidq;
	काष्ठा list_head vidq_queued;
	काष्ठा video_device *device;
	काष्ठा tw686x_v4l2_buf *curr_bufs[2];
	काष्ठा tw686x_dma_desc dma_descs[2];
	काष्ठा tw686x_sg_desc *sg_descs[2];

	काष्ठा v4l2_ctrl_handler ctrl_handler;
	स्थिर काष्ठा tw686x_क्रमmat *क्रमmat;
	काष्ठा mutex vb_mutex;
	spinlock_t qlock;
	v4l2_std_id video_standard;
	अचिन्हित पूर्णांक width, height;
	अचिन्हित पूर्णांक h_halve, v_halve;
	अचिन्हित पूर्णांक ch;
	अचिन्हित पूर्णांक num;
	अचिन्हित पूर्णांक fps;
	अचिन्हित पूर्णांक input;
	अचिन्हित पूर्णांक sequence;
	अचिन्हित पूर्णांक pb;
	bool no_संकेत;
पूर्ण;

काष्ठा tw686x_dma_ops अणु
	पूर्णांक (*setup)(काष्ठा tw686x_dev *dev);
	पूर्णांक (*alloc)(काष्ठा tw686x_video_channel *vc, अचिन्हित पूर्णांक pb);
	व्योम (*मुक्त)(काष्ठा tw686x_video_channel *vc, अचिन्हित पूर्णांक pb);
	व्योम (*buf_refill)(काष्ठा tw686x_video_channel *vc, अचिन्हित पूर्णांक pb);
	स्थिर काष्ठा vb2_mem_ops *mem_ops;
	क्रमागत v4l2_field field;
	u32 hw_dma_mode;
पूर्ण;

/* काष्ठा tw686x_dev - global device status */
काष्ठा tw686x_dev अणु
	/*
	 * spinlock controlling access to the shared device रेजिस्टरs
	 * (DMA enable/disable)
	 */
	spinlock_t lock;

	काष्ठा v4l2_device v4l2_dev;
	काष्ठा snd_card *snd_card;

	अक्षर name[32];
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक dma_mode;
	काष्ठा pci_dev *pci_dev;
	__u32 __iomem *mmio;

	स्थिर काष्ठा tw686x_dma_ops *dma_ops;
	काष्ठा tw686x_video_channel *video_channels;
	काष्ठा tw686x_audio_channel *audio_channels;

	/* Per-device audio parameters */
	पूर्णांक audio_rate;
	पूर्णांक period_size;
	पूर्णांक audio_enabled;

	काष्ठा समयr_list dma_delay_समयr;
	u32 pending_dma_en; /* must be रक्षित by lock */
	u32 pending_dma_cmd; /* must be रक्षित by lock */
पूर्ण;

अटल अंतरभूत uपूर्णांक32_t reg_पढ़ो(काष्ठा tw686x_dev *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl(dev->mmio + reg);
पूर्ण

अटल अंतरभूत व्योम reg_ग_लिखो(काष्ठा tw686x_dev *dev, अचिन्हित पूर्णांक reg,
			     uपूर्णांक32_t value)
अणु
	ग_लिखोl(value, dev->mmio + reg);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक max_channels(काष्ठा tw686x_dev *dev)
अणु
	वापस dev->type & TYPE_MAX_CHANNELS; /* 4 or 8 channels */
पूर्ण

अटल अंतरभूत अचिन्हित is_second_gen(काष्ठा tw686x_dev *dev)
अणु
	/* each channel has its own DMA SG table */
	वापस dev->type & TYPE_SECOND_GEN;
पूर्ण

व्योम tw686x_enable_channel(काष्ठा tw686x_dev *dev, अचिन्हित पूर्णांक channel);
व्योम tw686x_disable_channel(काष्ठा tw686x_dev *dev, अचिन्हित पूर्णांक channel);

पूर्णांक tw686x_video_init(काष्ठा tw686x_dev *dev);
व्योम tw686x_video_मुक्त(काष्ठा tw686x_dev *dev);
व्योम tw686x_video_irq(काष्ठा tw686x_dev *dev, अचिन्हित दीर्घ requests,
		      अचिन्हित पूर्णांक pb_status, अचिन्हित पूर्णांक fअगरo_status,
		      अचिन्हित पूर्णांक *reset_ch);

पूर्णांक tw686x_audio_init(काष्ठा tw686x_dev *dev);
व्योम tw686x_audio_मुक्त(काष्ठा tw686x_dev *dev);
व्योम tw686x_audio_irq(काष्ठा tw686x_dev *dev, अचिन्हित दीर्घ requests,
		      अचिन्हित पूर्णांक pb_status);
