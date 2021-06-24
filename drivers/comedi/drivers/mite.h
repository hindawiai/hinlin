<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * module/mite.h
 * Hardware driver क्रम NI Mite PCI पूर्णांकerface chip
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1999 David A. Schleef <ds@schleef.org>
 */

#अगर_अघोषित _MITE_H_
#घोषणा _MITE_H_

#समावेश <linux/spinlock.h>

#घोषणा MAX_MITE_DMA_CHANNELS 8

काष्ठा comedi_device;
काष्ठा comedi_subdevice;
काष्ठा device;
काष्ठा pci_dev;

काष्ठा mite_dma_desc अणु
	__le32 count;
	__le32 addr;
	__le32 next;
	u32 dar;
पूर्ण;

काष्ठा mite_ring अणु
	काष्ठा device *hw_dev;
	अचिन्हित पूर्णांक n_links;
	काष्ठा mite_dma_desc *descs;
	dma_addr_t dma_addr;
पूर्ण;

काष्ठा mite_channel अणु
	काष्ठा mite *mite;
	अचिन्हित पूर्णांक channel;
	पूर्णांक dir;
	पूर्णांक करोne;
	काष्ठा mite_ring *ring;
पूर्ण;

काष्ठा mite अणु
	काष्ठा pci_dev *pcidev;
	व्योम __iomem *mmio;
	काष्ठा mite_channel channels[MAX_MITE_DMA_CHANNELS];
	पूर्णांक num_channels;
	अचिन्हित पूर्णांक fअगरo_size;
	/* protects mite_channel from being released by the driver */
	spinlock_t lock;
पूर्ण;

u32 mite_bytes_in_transit(काष्ठा mite_channel *mite_chan);

व्योम mite_sync_dma(काष्ठा mite_channel *mite_chan, काष्ठा comedi_subdevice *s);
व्योम mite_ack_linkc(काष्ठा mite_channel *mite_chan, काष्ठा comedi_subdevice *s,
		    bool sync);
पूर्णांक mite_करोne(काष्ठा mite_channel *mite_chan);

व्योम mite_dma_arm(काष्ठा mite_channel *mite_chan);
व्योम mite_dma_disarm(काष्ठा mite_channel *mite_chan);

व्योम mite_prep_dma(काष्ठा mite_channel *mite_chan,
		   अचिन्हित पूर्णांक num_device_bits, अचिन्हित पूर्णांक num_memory_bits);

काष्ठा mite_channel *mite_request_channel_in_range(काष्ठा mite *mite,
						   काष्ठा mite_ring *ring,
						   अचिन्हित पूर्णांक min_channel,
						   अचिन्हित पूर्णांक max_channel);
काष्ठा mite_channel *mite_request_channel(काष्ठा mite *mite,
					  काष्ठा mite_ring *ring);
व्योम mite_release_channel(काष्ठा mite_channel *mite_chan);

पूर्णांक mite_init_ring_descriptors(काष्ठा mite_ring *ring,
			       काष्ठा comedi_subdevice *s, अचिन्हित पूर्णांक nbytes);
पूर्णांक mite_buf_change(काष्ठा mite_ring *ring, काष्ठा comedi_subdevice *s);

काष्ठा mite_ring *mite_alloc_ring(काष्ठा mite *mite);
व्योम mite_मुक्त_ring(काष्ठा mite_ring *ring);

काष्ठा mite *mite_attach(काष्ठा comedi_device *dev, bool use_win1);
व्योम mite_detach(काष्ठा mite *mite);

/*
 * Mite रेजिस्टरs (used outside of the mite driver)
 */
#घोषणा MITE_IODWBSR		0xc0	/* IO Device Winकरोw Base Size */
#घोषणा MITE_IODWBSR_1		0xc4	/* IO Device Winकरोw1 Base Size */
#घोषणा WENAB			BIT(7)	/* winकरोw enable */
#घोषणा MITE_IODWCR_1		0xf4

#पूर्ण_अगर
