<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * i2sbus driver -- निजी definitions
 *
 * Copyright 2006 Johannes Berg <johannes@sipsolutions.net>
 */
#अगर_अघोषित __I2SBUS_H
#घोषणा __I2SBUS_H
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/completion.h>

#समावेश <sound/pcm.h>

#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/pmac_feature.h>
#समावेश <यंत्र/dbdma.h>

#समावेश "interface.h"
#समावेश "../soundbus.h"

काष्ठा i2sbus_control अणु
	काष्ठा list_head list;
	काष्ठा macio_chip *macio;
पूर्ण;

#घोषणा MAX_DBDMA_COMMANDS	32

काष्ठा dbdma_command_mem अणु
	dma_addr_t bus_addr;
	dma_addr_t bus_cmd_start;
	काष्ठा dbdma_cmd *cmds;
	व्योम *space;
	पूर्णांक size;
	u32 running:1;
	u32 stopping:1;
पूर्ण;

काष्ठा pcm_info अणु
	u32 created:1, /* has this direction been created with alsa? */
	    active:1;  /* is this stream active? */
	/* runसमय inक्रमmation */
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक current_period;
	u32 frame_count;
	काष्ठा dbdma_command_mem dbdma_ring;
	अस्थिर काष्ठा dbdma_regs __iomem *dbdma;
	काष्ठा completion *stop_completion;
पूर्ण;

क्रमागत अणु
	aoa_resource_i2smmio = 0,
	aoa_resource_txdbdma,
	aoa_resource_rxdbdma,
पूर्ण;

काष्ठा i2sbus_dev अणु
	काष्ठा soundbus_dev sound;
	काष्ठा macio_dev *macio;
	काष्ठा i2sbus_control *control;
	अस्थिर काष्ठा i2s_पूर्णांकerface_regs __iomem *पूर्णांकfregs;

	काष्ठा resource resources[3];
	काष्ठा resource *allocated_resource[3];
	पूर्णांक पूर्णांकerrupts[3];
	अक्षर rnames[3][32];

	/* info about currently active substreams */
	काष्ठा pcm_info out, in;
	snd_pcm_क्रमmat_t क्रमmat;
	अचिन्हित पूर्णांक rate;

	/* list क्रम a single controller */
	काष्ठा list_head item;
	/* number of bus on controller */
	पूर्णांक bus_number;
	/* क्रम use by control layer */
	काष्ठा pmf_function *enable,
			    *cell_enable,
			    *cell_disable,
			    *घड़ी_enable,
			    *घड़ी_disable;

	/* locks */
	/* spinlock क्रम low-level पूर्णांकerrupt locking */
	spinlock_t low_lock;
	/* mutex क्रम high-level consistency */
	काष्ठा mutex lock;
पूर्ण;

#घोषणा soundbus_dev_to_i2sbus_dev(sdev) \
		container_of(sdev, काष्ठा i2sbus_dev, sound)

/* pcm specअगरic functions */
बाह्य पूर्णांक
i2sbus_attach_codec(काष्ठा soundbus_dev *dev, काष्ठा snd_card *card,
		    काष्ठा codec_info *ci, व्योम *data);
बाह्य व्योम
i2sbus_detach_codec(काष्ठा soundbus_dev *dev, व्योम *data);
बाह्य irqवापस_t
i2sbus_tx_पूर्णांकr(पूर्णांक irq, व्योम *devid);
बाह्य irqवापस_t
i2sbus_rx_पूर्णांकr(पूर्णांक irq, व्योम *devid);

बाह्य व्योम i2sbus_रुको_क्रम_stop_both(काष्ठा i2sbus_dev *i2sdev);
बाह्य व्योम i2sbus_pcm_prepare_both(काष्ठा i2sbus_dev *i2sdev);

/* control specअगरic functions */
बाह्य पूर्णांक i2sbus_control_init(काष्ठा macio_dev* dev,
			       काष्ठा i2sbus_control **c);
बाह्य व्योम i2sbus_control_destroy(काष्ठा i2sbus_control *c);
बाह्य पूर्णांक i2sbus_control_add_dev(काष्ठा i2sbus_control *c,
				  काष्ठा i2sbus_dev *i2sdev);
बाह्य व्योम i2sbus_control_हटाओ_dev(काष्ठा i2sbus_control *c,
				      काष्ठा i2sbus_dev *i2sdev);
बाह्य पूर्णांक i2sbus_control_enable(काष्ठा i2sbus_control *c,
				 काष्ठा i2sbus_dev *i2sdev);
बाह्य पूर्णांक i2sbus_control_cell(काष्ठा i2sbus_control *c,
			       काष्ठा i2sbus_dev *i2sdev,
			       पूर्णांक enable);
बाह्य पूर्णांक i2sbus_control_घड़ी(काष्ठा i2sbus_control *c,
				काष्ठा i2sbus_dev *i2sdev,
				पूर्णांक enable);
#पूर्ण_अगर /* __I2SBUS_H */
