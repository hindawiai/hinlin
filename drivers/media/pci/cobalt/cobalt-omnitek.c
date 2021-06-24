<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Omnitek Scatter-Gather DMA Controller
 *
 *  Copyright 2012-2015 Cisco Systems, Inc. and/or its affiliates.
 *  All rights reserved.
 */

#समावेश <linux/माला.स>
#समावेश <linux/पन.स>
#समावेश <linux/pci_regs.h>
#समावेश <linux/spinlock.h>

#समावेश "cobalt-driver.h"
#समावेश "cobalt-omnitek.h"

/* descriptor */
#घोषणा END_OF_CHAIN		(1 << 1)
#घोषणा INTERRUPT_ENABLE	(1 << 2)
#घोषणा WRITE_TO_PCI		(1 << 3)
#घोषणा READ_FROM_PCI		(0 << 3)
#घोषणा DESCRIPTOR_FLAG_MSK	(END_OF_CHAIN | INTERRUPT_ENABLE | WRITE_TO_PCI)
#घोषणा NEXT_ADRS_MSK		0xffffffe0

/* control/status रेजिस्टर */
#घोषणा ENABLE                  (1 << 0)
#घोषणा START                   (1 << 1)
#घोषणा ABORT                   (1 << 2)
#घोषणा DONE                    (1 << 4)
#घोषणा SG_INTERRUPT            (1 << 5)
#घोषणा EVENT_INTERRUPT         (1 << 6)
#घोषणा SCATTER_GATHER_MODE     (1 << 8)
#घोषणा DISABLE_VIDEO_RESYNC    (1 << 9)
#घोषणा EVENT_INTERRUPT_ENABLE  (1 << 10)
#घोषणा सूचीECTIONAL_MSK         (3 << 16)
#घोषणा INPUT_ONLY              (0 << 16)
#घोषणा OUTPUT_ONLY             (1 << 16)
#घोषणा BIसूचीECTIONAL           (2 << 16)
#घोषणा DMA_TYPE_MEMORY         (0 << 18)
#घोषणा DMA_TYPE_FIFO		(1 << 18)

#घोषणा BASE			(cobalt->bar0)
#घोषणा CAPABILITY_HEADER	(BASE)
#घोषणा CAPABILITY_REGISTER	(BASE + 0x04)
#घोषणा PCI_64BIT		(1 << 8)
#घोषणा LOCAL_64BIT		(1 << 9)
#घोषणा INTERRUPT_STATUS	(BASE + 0x08)
#घोषणा PCI(c)			(BASE + 0x40 + ((c) * 0x40))
#घोषणा SIZE(c)			(BASE + 0x58 + ((c) * 0x40))
#घोषणा DESCRIPTOR(c)		(BASE + 0x50 + ((c) * 0x40))
#घोषणा CS_REG(c)		(BASE + 0x60 + ((c) * 0x40))
#घोषणा BYTES_TRANSFERRED(c)	(BASE + 0x64 + ((c) * 0x40))


अटल अक्षर *get_dma_direction(u32 status)
अणु
	चयन (status & सूचीECTIONAL_MSK) अणु
	हाल INPUT_ONLY: वापस "Input";
	हाल OUTPUT_ONLY: वापस "Output";
	हाल BIसूचीECTIONAL: वापस "Bidirectional";
	पूर्ण
	वापस "";
पूर्ण

अटल व्योम show_dma_capability(काष्ठा cobalt *cobalt)
अणु
	u32 header = ioपढ़ो32(CAPABILITY_HEADER);
	u32 capa = ioपढ़ो32(CAPABILITY_REGISTER);
	u32 i;

	cobalt_info("Omnitek DMA capability: ID 0x%02x Version 0x%02x Next 0x%x Size 0x%x\n",
		    header & 0xff, (header >> 8) & 0xff,
		    (header >> 16) & 0xffff, (capa >> 24) & 0xff);

	चयन ((capa >> 8) & 0x3) अणु
	हाल 0:
		cobalt_info("Omnitek DMA: 32 bits PCIe and Local\n");
		अवरोध;
	हाल 1:
		cobalt_info("Omnitek DMA: 64 bits PCIe, 32 bits Local\n");
		अवरोध;
	हाल 3:
		cobalt_info("Omnitek DMA: 64 bits PCIe and Local\n");
		अवरोध;
	पूर्ण

	क्रम (i = 0;  i < (capa & 0xf);  i++) अणु
		u32 status = ioपढ़ो32(CS_REG(i));

		cobalt_info("Omnitek DMA channel #%d: %s %s\n", i,
			    status & DMA_TYPE_FIFO ? "FIFO" : "MEMORY",
			    get_dma_direction(status));
	पूर्ण
पूर्ण

व्योम omni_sg_dma_start(काष्ठा cobalt_stream *s, काष्ठा sg_dma_desc_info *desc)
अणु
	काष्ठा cobalt *cobalt = s->cobalt;

	ioग_लिखो32((u32)((u64)desc->bus >> 32), DESCRIPTOR(s->dma_channel) + 4);
	ioग_लिखो32((u32)desc->bus & NEXT_ADRS_MSK, DESCRIPTOR(s->dma_channel));
	ioग_लिखो32(ENABLE | SCATTER_GATHER_MODE | START, CS_REG(s->dma_channel));
पूर्ण

bool is_dma_करोne(काष्ठा cobalt_stream *s)
अणु
	काष्ठा cobalt *cobalt = s->cobalt;

	अगर (ioपढ़ो32(CS_REG(s->dma_channel)) & DONE)
		वापस true;

	वापस false;
पूर्ण

व्योम omni_sg_dma_पात_channel(काष्ठा cobalt_stream *s)
अणु
	काष्ठा cobalt *cobalt = s->cobalt;

	अगर (!is_dma_करोne(s))
		ioग_लिखो32(ABORT, CS_REG(s->dma_channel));
पूर्ण

पूर्णांक omni_sg_dma_init(काष्ठा cobalt *cobalt)
अणु
	u32 capa = ioपढ़ो32(CAPABILITY_REGISTER);
	पूर्णांक i;

	cobalt->first_fअगरo_channel = 0;
	cobalt->dma_channels = capa & 0xf;
	अगर (capa & PCI_64BIT)
		cobalt->pci_32_bit = false;
	अन्यथा
		cobalt->pci_32_bit = true;

	क्रम (i = 0; i < cobalt->dma_channels; i++) अणु
		u32 status = ioपढ़ो32(CS_REG(i));
		u32 ctrl = ioपढ़ो32(CS_REG(i));

		अगर (!(ctrl & DONE))
			ioग_लिखो32(ABORT, CS_REG(i));

		अगर (!(status & DMA_TYPE_FIFO))
			cobalt->first_fअगरo_channel++;
	पूर्ण
	show_dma_capability(cobalt);
	वापस 0;
पूर्ण

पूर्णांक descriptor_list_create(काष्ठा cobalt *cobalt,
		काष्ठा scatterlist *scatter_list, bool to_pci, अचिन्हित sglen,
		अचिन्हित size, अचिन्हित width, अचिन्हित stride,
		काष्ठा sg_dma_desc_info *desc)
अणु
	काष्ठा sg_dma_descriptor *d = (काष्ठा sg_dma_descriptor *)desc->virt;
	dma_addr_t next = desc->bus;
	अचिन्हित offset = 0;
	अचिन्हित copy_bytes = width;
	अचिन्हित copied = 0;
	bool first = true;

	/* Must be 4-byte aligned */
	WARN_ON(sg_dma_address(scatter_list) & 3);
	WARN_ON(size & 3);
	WARN_ON(next & 3);
	WARN_ON(stride & 3);
	WARN_ON(stride < width);
	अगर (width >= stride)
		copy_bytes = stride = size;

	जबतक (size) अणु
		dma_addr_t addr = sg_dma_address(scatter_list) + offset;
		अचिन्हित bytes;

		अगर (addr == 0)
			वापस -EFAULT;
		अगर (cobalt->pci_32_bit) अणु
			WARN_ON((u64)addr >> 32);
			अगर ((u64)addr >> 32)
				वापस -EFAULT;
		पूर्ण

		/* PCIe address */
		d->pci_l = addr & 0xffffffff;
		/* If dma_addr_t is 32 bits, then addr >> 32 is actually the
		   equivalent of addr >> 0 in gcc. So must cast to u64. */
		d->pci_h = (u64)addr >> 32;

		/* Sync to start of streaming frame */
		d->local = 0;
		d->reserved0 = 0;

		/* Transfer bytes */
		bytes = min(sg_dma_len(scatter_list) - offset,
				copy_bytes - copied);

		अगर (first) अणु
			अगर (to_pci)
				d->local = 0x11111111;
			first = false;
			अगर (sglen == 1) अणु
				/* Make sure there are always at least two
				 * descriptors */
				d->bytes = (bytes / 2) & ~3;
				d->reserved1 = 0;
				size -= d->bytes;
				copied += d->bytes;
				offset += d->bytes;
				addr += d->bytes;
				next += माप(काष्ठा sg_dma_descriptor);
				d->next_h = (u32)((u64)next >> 32);
				d->next_l = (u32)next |
					(to_pci ? WRITE_TO_PCI : 0);
				bytes -= d->bytes;
				d++;
				/* PCIe address */
				d->pci_l = addr & 0xffffffff;
				/* If dma_addr_t is 32 bits, then addr >> 32
				 * is actually the equivalent of addr >> 0 in
				 * gcc. So must cast to u64. */
				d->pci_h = (u64)addr >> 32;

				/* Sync to start of streaming frame */
				d->local = 0;
				d->reserved0 = 0;
			पूर्ण
		पूर्ण

		d->bytes = bytes;
		d->reserved1 = 0;
		size -= bytes;
		copied += bytes;
		offset += bytes;

		अगर (copied == copy_bytes) अणु
			जबतक (copied < stride) अणु
				bytes = min(sg_dma_len(scatter_list) - offset,
						stride - copied);
				copied += bytes;
				offset += bytes;
				size -= bytes;
				अगर (sg_dma_len(scatter_list) == offset) अणु
					offset = 0;
					scatter_list = sg_next(scatter_list);
				पूर्ण
			पूर्ण
			copied = 0;
		पूर्ण अन्यथा अणु
			offset = 0;
			scatter_list = sg_next(scatter_list);
		पूर्ण

		/* Next descriptor + control bits */
		next += माप(काष्ठा sg_dma_descriptor);
		अगर (size == 0) अणु
			/* Loopback to the first descriptor */
			d->next_h = (u32)((u64)desc->bus >> 32);
			d->next_l = (u32)desc->bus |
				(to_pci ? WRITE_TO_PCI : 0) | INTERRUPT_ENABLE;
			अगर (!to_pci)
				d->local = 0x22222222;
			desc->last_desc_virt = d;
		पूर्ण अन्यथा अणु
			d->next_h = (u32)((u64)next >> 32);
			d->next_l = (u32)next | (to_pci ? WRITE_TO_PCI : 0);
		पूर्ण
		d++;
	पूर्ण
	वापस 0;
पूर्ण

व्योम descriptor_list_chain(काष्ठा sg_dma_desc_info *this,
			   काष्ठा sg_dma_desc_info *next)
अणु
	काष्ठा sg_dma_descriptor *d = this->last_desc_virt;
	u32 direction = d->next_l & WRITE_TO_PCI;

	अगर (next == शून्य) अणु
		d->next_h = 0;
		d->next_l = direction | INTERRUPT_ENABLE | END_OF_CHAIN;
	पूर्ण अन्यथा अणु
		d->next_h = (u32)((u64)next->bus >> 32);
		d->next_l = (u32)next->bus | direction | INTERRUPT_ENABLE;
	पूर्ण
पूर्ण

व्योम *descriptor_list_allocate(काष्ठा sg_dma_desc_info *desc, माप_प्रकार bytes)
अणु
	desc->size = bytes;
	desc->virt = dma_alloc_coherent(desc->dev, bytes,
					&desc->bus, GFP_KERNEL);
	वापस desc->virt;
पूर्ण

व्योम descriptor_list_मुक्त(काष्ठा sg_dma_desc_info *desc)
अणु
	अगर (desc->virt)
		dma_मुक्त_coherent(desc->dev, desc->size,
				  desc->virt, desc->bus);
	desc->virt = शून्य;
पूर्ण

व्योम descriptor_list_पूर्णांकerrupt_enable(काष्ठा sg_dma_desc_info *desc)
अणु
	काष्ठा sg_dma_descriptor *d = desc->last_desc_virt;

	d->next_l |= INTERRUPT_ENABLE;
पूर्ण

व्योम descriptor_list_पूर्णांकerrupt_disable(काष्ठा sg_dma_desc_info *desc)
अणु
	काष्ठा sg_dma_descriptor *d = desc->last_desc_virt;

	d->next_l &= ~INTERRUPT_ENABLE;
पूर्ण

व्योम descriptor_list_loopback(काष्ठा sg_dma_desc_info *desc)
अणु
	काष्ठा sg_dma_descriptor *d = desc->last_desc_virt;

	d->next_h = (u32)((u64)desc->bus >> 32);
	d->next_l = (u32)desc->bus | (d->next_l & DESCRIPTOR_FLAG_MSK);
पूर्ण

व्योम descriptor_list_end_of_chain(काष्ठा sg_dma_desc_info *desc)
अणु
	काष्ठा sg_dma_descriptor *d = desc->last_desc_virt;

	d->next_l |= END_OF_CHAIN;
पूर्ण
