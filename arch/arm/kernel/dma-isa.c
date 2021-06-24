<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/kernel/dma-isa.c
 *
 *  Copyright (C) 1999-2000 Russell King
 *
 *  ISA DMA primitives
 *  Taken from various sources, including:
 *   linux/include/यंत्र/dma.h: Defines क्रम using and allocating dma channels.
 *     Written by Hennus Bergman, 1992.
 *     High DMA channel support & info by Hannu Savolainen and John Boyd,
 *     Nov. 1992.
 *   arch/arm/kernel/dma-ebsa285.c
 *   Copyright (C) 1998 Phil Blundell
 */
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/mach/dma.h>

#घोषणा ISA_DMA_MASK		0
#घोषणा ISA_DMA_MODE		1
#घोषणा ISA_DMA_CLRFF		2
#घोषणा ISA_DMA_PGHI		3
#घोषणा ISA_DMA_PGLO		4
#घोषणा ISA_DMA_ADDR		5
#घोषणा ISA_DMA_COUNT		6

अटल अचिन्हित पूर्णांक isa_dma_port[8][7] = अणु
	/* MASK   MODE   CLRFF  PAGE_HI PAGE_LO ADDR COUNT */
	अणु  0x0a,  0x0b,  0x0c,  0x487,  0x087,  0x00, 0x01 पूर्ण,
	अणु  0x0a,  0x0b,  0x0c,  0x483,  0x083,  0x02, 0x03 पूर्ण,
	अणु  0x0a,  0x0b,  0x0c,  0x481,  0x081,  0x04, 0x05 पूर्ण,
	अणु  0x0a,  0x0b,  0x0c,  0x482,  0x082,  0x06, 0x07 पूर्ण,
	अणु  0xd4,  0xd6,  0xd8,  0x000,  0x000,  0xc0, 0xc2 पूर्ण,
	अणु  0xd4,  0xd6,  0xd8,  0x48b,  0x08b,  0xc4, 0xc6 पूर्ण,
	अणु  0xd4,  0xd6,  0xd8,  0x489,  0x089,  0xc8, 0xca पूर्ण,
	अणु  0xd4,  0xd6,  0xd8,  0x48a,  0x08a,  0xcc, 0xce पूर्ण
पूर्ण;

अटल पूर्णांक isa_get_dma_residue(अचिन्हित पूर्णांक chan, dma_t *dma)
अणु
	अचिन्हित पूर्णांक io_port = isa_dma_port[chan][ISA_DMA_COUNT];
	पूर्णांक count;

	count = 1 + inb(io_port);
	count |= inb(io_port) << 8;

	वापस chan < 4 ? count : (count << 1);
पूर्ण

अटल काष्ठा device isa_dma_dev = अणु
	.init_name		= "fallback device",
	.coherent_dma_mask	= ~(dma_addr_t)0,
	.dma_mask		= &isa_dma_dev.coherent_dma_mask,
पूर्ण;

अटल व्योम isa_enable_dma(अचिन्हित पूर्णांक chan, dma_t *dma)
अणु
	अगर (dma->invalid) अणु
		अचिन्हित दीर्घ address, length;
		अचिन्हित पूर्णांक mode;
		क्रमागत dma_data_direction direction;

		mode = (chan & 3) | dma->dma_mode;
		चयन (dma->dma_mode & DMA_MODE_MASK) अणु
		हाल DMA_MODE_READ:
			direction = DMA_FROM_DEVICE;
			अवरोध;

		हाल DMA_MODE_WRITE:
			direction = DMA_TO_DEVICE;
			अवरोध;

		हाल DMA_MODE_CASCADE:
			direction = DMA_BIसूचीECTIONAL;
			अवरोध;

		शेष:
			direction = DMA_NONE;
			अवरोध;
		पूर्ण

		अगर (!dma->sg) अणु
			/*
			 * Cope with ISA-style drivers which expect cache
			 * coherence.
			 */
			dma->sg = &dma->buf;
			dma->sgcount = 1;
			dma->buf.length = dma->count;
			dma->buf.dma_address = dma_map_single(&isa_dma_dev,
				dma->addr, dma->count,
				direction);
		पूर्ण

		address = dma->buf.dma_address;
		length  = dma->buf.length - 1;

		outb(address >> 16, isa_dma_port[chan][ISA_DMA_PGLO]);
		outb(address >> 24, isa_dma_port[chan][ISA_DMA_PGHI]);

		अगर (chan >= 4) अणु
			address >>= 1;
			length >>= 1;
		पूर्ण

		outb(0, isa_dma_port[chan][ISA_DMA_CLRFF]);

		outb(address, isa_dma_port[chan][ISA_DMA_ADDR]);
		outb(address >> 8, isa_dma_port[chan][ISA_DMA_ADDR]);

		outb(length, isa_dma_port[chan][ISA_DMA_COUNT]);
		outb(length >> 8, isa_dma_port[chan][ISA_DMA_COUNT]);

		outb(mode, isa_dma_port[chan][ISA_DMA_MODE]);
		dma->invalid = 0;
	पूर्ण
	outb(chan & 3, isa_dma_port[chan][ISA_DMA_MASK]);
पूर्ण

अटल व्योम isa_disable_dma(अचिन्हित पूर्णांक chan, dma_t *dma)
अणु
	outb(chan | 4, isa_dma_port[chan][ISA_DMA_MASK]);
पूर्ण

अटल काष्ठा dma_ops isa_dma_ops = अणु
	.type		= "ISA",
	.enable		= isa_enable_dma,
	.disable	= isa_disable_dma,
	.residue	= isa_get_dma_residue,
पूर्ण;

अटल काष्ठा resource dma_resources[] = अणु अणु
	.name	= "dma1",
	.start	= 0x0000,
	.end	= 0x000f
पूर्ण, अणु
	.name	= "dma low page",
	.start	= 0x0080,
	.end 	= 0x008f
पूर्ण, अणु
	.name	= "dma2",
	.start	= 0x00c0,
	.end	= 0x00df
पूर्ण, अणु
	.name	= "dma high page",
	.start	= 0x0480,
	.end	= 0x048f
पूर्ण पूर्ण;

अटल dma_t isa_dma[8];

/*
 * ISA DMA always starts at channel 0
 */
व्योम __init isa_init_dma(व्योम)
अणु
	/*
	 * Try to स्वतःdetect presence of an ISA DMA controller.
	 * We करो some minimal initialisation, and check that
	 * channel 0's DMA address रेजिस्टरs are ग_लिखोable.
	 */
	outb(0xff, 0x0d);
	outb(0xff, 0xda);

	/*
	 * Write high and low address, and then पढ़ो them back
	 * in the same order.
	 */
	outb(0x55, 0x00);
	outb(0xaa, 0x00);

	अगर (inb(0) == 0x55 && inb(0) == 0xaa) अणु
		अचिन्हित पूर्णांक chan, i;

		क्रम (chan = 0; chan < 8; chan++) अणु
			isa_dma[chan].d_ops = &isa_dma_ops;
			isa_disable_dma(chan, शून्य);
		पूर्ण

		outb(0x40, 0x0b);
		outb(0x41, 0x0b);
		outb(0x42, 0x0b);
		outb(0x43, 0x0b);

		outb(0xc0, 0xd6);
		outb(0x41, 0xd6);
		outb(0x42, 0xd6);
		outb(0x43, 0xd6);

		outb(0, 0xd4);

		outb(0x10, 0x08);
		outb(0x10, 0xd0);

		/*
		 * Is this correct?  According to my करोcumentation, it
		 * करोesn't appear to be.  It should be:
		 *  outb(0x3f, 0x40b); outb(0x3f, 0x4d6);
		 */
		outb(0x30, 0x40b);
		outb(0x31, 0x40b);
		outb(0x32, 0x40b);
		outb(0x33, 0x40b);
		outb(0x31, 0x4d6);
		outb(0x32, 0x4d6);
		outb(0x33, 0x4d6);

		क्रम (i = 0; i < ARRAY_SIZE(dma_resources); i++)
			request_resource(&ioport_resource, dma_resources + i);

		क्रम (chan = 0; chan < 8; chan++) अणु
			पूर्णांक ret = isa_dma_add(chan, &isa_dma[chan]);
			अगर (ret)
				pr_err("ISADMA%u: unable to register: %d\n",
				       chan, ret);
		पूर्ण

		request_dma(DMA_ISA_CASCADE, "cascade");
	पूर्ण
पूर्ण
