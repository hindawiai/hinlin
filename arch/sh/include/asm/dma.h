<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * include/यंत्र-sh/dma.h
 *
 * Copyright (C) 2003, 2004  Paul Mundt
 */
#अगर_अघोषित __ASM_SH_DMA_H
#घोषणा __ASM_SH_DMA_H

#समावेश <linux/spinlock.h>
#समावेश <linux/रुको.h>
#समावेश <linux/sched.h>
#समावेश <linux/device.h>
#समावेश <यंत्र-generic/dma.h>

/*
 * Read and ग_लिखो modes can mean drastically dअगरferent things depending on the
 * channel configuration. Consult your DMAC करोcumentation and module
 * implementation क्रम further clues.
 */
#घोषणा DMA_MODE_READ		0x00
#घोषणा DMA_MODE_WRITE		0x01
#घोषणा DMA_MODE_MASK		0x01

#घोषणा DMA_AUTOINIT		0x10

/*
 * DMAC (dma_info) flags
 */
क्रमागत अणु
	DMAC_CHANNELS_CONFIGURED	= 0x01,
	DMAC_CHANNELS_TEI_CAPABLE	= 0x02,	/* Transfer end पूर्णांकerrupt */
पूर्ण;

/*
 * DMA channel capabilities / flags
 */
क्रमागत अणु
	DMA_CONFIGURED			= 0x01,

	/*
	 * Transfer end पूर्णांकerrupt, inherited from DMAC.
	 * रुको_queue used in dma_रुको_क्रम_completion.
	 */
	DMA_TEI_CAPABLE			= 0x02,
पूर्ण;

बाह्य spinlock_t dma_spin_lock;

काष्ठा dma_channel;

काष्ठा dma_ops अणु
	पूर्णांक (*request)(काष्ठा dma_channel *chan);
	व्योम (*मुक्त)(काष्ठा dma_channel *chan);

	पूर्णांक (*get_residue)(काष्ठा dma_channel *chan);
	पूर्णांक (*xfer)(काष्ठा dma_channel *chan);
	पूर्णांक (*configure)(काष्ठा dma_channel *chan, अचिन्हित दीर्घ flags);
	पूर्णांक (*extend)(काष्ठा dma_channel *chan, अचिन्हित दीर्घ op, व्योम *param);
पूर्ण;

काष्ठा dma_channel अणु
	अक्षर dev_id[16];		/* unique name per DMAC of channel */

	अचिन्हित पूर्णांक chan;		/* DMAC channel number */
	अचिन्हित पूर्णांक vchan;		/* Virtual channel number */

	अचिन्हित पूर्णांक mode;
	अचिन्हित पूर्णांक count;

	अचिन्हित दीर्घ sar;
	अचिन्हित दीर्घ dar;

	स्थिर अक्षर **caps;

	अचिन्हित दीर्घ flags;
	atomic_t busy;

	रुको_queue_head_t रुको_queue;

	काष्ठा device dev;
	व्योम *priv_data;
पूर्ण;

काष्ठा dma_info अणु
	काष्ठा platक्रमm_device *pdev;

	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक nr_channels;
	अचिन्हित दीर्घ flags;

	काष्ठा dma_ops *ops;
	काष्ठा dma_channel *channels;

	काष्ठा list_head list;
	पूर्णांक first_channel_nr;
	पूर्णांक first_vchannel_nr;
पूर्ण;

काष्ठा dma_chan_caps अणु
	पूर्णांक ch_num;
	स्थिर अक्षर **caplist;
पूर्ण;

#घोषणा to_dma_channel(channel) container_of(channel, काष्ठा dma_channel, dev)

/* arch/sh/drivers/dma/dma-api.c */
बाह्य पूर्णांक dma_xfer(अचिन्हित पूर्णांक chan, अचिन्हित दीर्घ from,
		    अचिन्हित दीर्घ to, माप_प्रकार size, अचिन्हित पूर्णांक mode);

#घोषणा dma_ग_लिखो(chan, from, to, size)	\
	dma_xfer(chan, from, to, size, DMA_MODE_WRITE)
#घोषणा dma_ग_लिखो_page(chan, from, to)	\
	dma_ग_लिखो(chan, from, to, PAGE_SIZE)

#घोषणा dma_पढ़ो(chan, from, to, size)	\
	dma_xfer(chan, from, to, size, DMA_MODE_READ)
#घोषणा dma_पढ़ो_page(chan, from, to)	\
	dma_पढ़ो(chan, from, to, PAGE_SIZE)

बाह्य पूर्णांक request_dma_bycap(स्थिर अक्षर **dmac, स्थिर अक्षर **caps,
			     स्थिर अक्षर *dev_id);
बाह्य पूर्णांक get_dma_residue(अचिन्हित पूर्णांक chan);
बाह्य काष्ठा dma_info *get_dma_info(अचिन्हित पूर्णांक chan);
बाह्य काष्ठा dma_channel *get_dma_channel(अचिन्हित पूर्णांक chan);
बाह्य व्योम dma_रुको_क्रम_completion(अचिन्हित पूर्णांक chan);
बाह्य व्योम dma_configure_channel(अचिन्हित पूर्णांक chan, अचिन्हित दीर्घ flags);

बाह्य पूर्णांक रेजिस्टर_dmac(काष्ठा dma_info *info);
बाह्य व्योम unरेजिस्टर_dmac(काष्ठा dma_info *info);
बाह्य काष्ठा dma_info *get_dma_info_by_name(स्थिर अक्षर *dmac_name);

बाह्य पूर्णांक dma_extend(अचिन्हित पूर्णांक chan, अचिन्हित दीर्घ op, व्योम *param);
बाह्य पूर्णांक रेजिस्टर_chan_caps(स्थिर अक्षर *dmac, काष्ठा dma_chan_caps *capslist);

/* arch/sh/drivers/dma/dma-sysfs.c */
बाह्य पूर्णांक dma_create_sysfs_files(काष्ठा dma_channel *, काष्ठा dma_info *);
बाह्य व्योम dma_हटाओ_sysfs_files(काष्ठा dma_channel *, काष्ठा dma_info *);

#अगर_घोषित CONFIG_PCI
बाह्य पूर्णांक isa_dma_bridge_buggy;
#अन्यथा
#घोषणा isa_dma_bridge_buggy	(0)
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_SH_DMA_H */
