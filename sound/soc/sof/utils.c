<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
//
// This file is provided under a dual BSD/GPLv2 license.  When using or
// redistributing this file, you may करो so under either license.
//
// Copyright(c) 2018 Intel Corporation. All rights reserved.
//
// Author: Keyon Jie <yang.jie@linux.पूर्णांकel.com>
//

#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <sound/soc.h>
#समावेश <sound/sof.h>
#समावेश "sof-priv.h"

/*
 * Register IO
 *
 * The sof_io_xyz() wrappers are typically referenced in snd_sof_dsp_ops
 * काष्ठाures and cannot be अंतरभूतd.
 */

व्योम sof_io_ग_लिखो(काष्ठा snd_sof_dev *sdev, व्योम __iomem *addr, u32 value)
अणु
	ग_लिखोl(value, addr);
पूर्ण
EXPORT_SYMBOL(sof_io_ग_लिखो);

u32 sof_io_पढ़ो(काष्ठा snd_sof_dev *sdev, व्योम __iomem *addr)
अणु
	वापस पढ़ोl(addr);
पूर्ण
EXPORT_SYMBOL(sof_io_पढ़ो);

व्योम sof_io_ग_लिखो64(काष्ठा snd_sof_dev *sdev, व्योम __iomem *addr, u64 value)
अणु
	ग_लिखोq(value, addr);
पूर्ण
EXPORT_SYMBOL(sof_io_ग_लिखो64);

u64 sof_io_पढ़ो64(काष्ठा snd_sof_dev *sdev, व्योम __iomem *addr)
अणु
	वापस पढ़ोq(addr);
पूर्ण
EXPORT_SYMBOL(sof_io_पढ़ो64);

/*
 * IPC Mailbox IO
 */

व्योम sof_mailbox_ग_लिखो(काष्ठा snd_sof_dev *sdev, u32 offset,
		       व्योम *message, माप_प्रकार bytes)
अणु
	व्योम __iomem *dest = sdev->bar[sdev->mailbox_bar] + offset;

	स_नकल_toio(dest, message, bytes);
पूर्ण
EXPORT_SYMBOL(sof_mailbox_ग_लिखो);

व्योम sof_mailbox_पढ़ो(काष्ठा snd_sof_dev *sdev, u32 offset,
		      व्योम *message, माप_प्रकार bytes)
अणु
	व्योम __iomem *src = sdev->bar[sdev->mailbox_bar] + offset;

	स_नकल_fromio(message, src, bytes);
पूर्ण
EXPORT_SYMBOL(sof_mailbox_पढ़ो);

/*
 * Memory copy.
 */

व्योम sof_block_ग_लिखो(काष्ठा snd_sof_dev *sdev, u32 bar, u32 offset, व्योम *src,
		     माप_प्रकार size)
अणु
	व्योम __iomem *dest = sdev->bar[bar] + offset;
	स्थिर u8 *src_byte = src;
	u32 affected_mask;
	u32 पंचांगp;
	पूर्णांक m, n;

	m = size / 4;
	n = size % 4;

	/* __ioग_लिखो32_copy use 32bit size values so भागide by 4 */
	__ioग_लिखो32_copy(dest, src, m);

	अगर (n) अणु
		affected_mask = (1 << (8 * n)) - 1;

		/* first पढ़ो the 32bit data of dest, then change affected
		 * bytes, and ग_लिखो back to dest. For unaffected bytes, it
		 * should not be changed
		 */
		पंचांगp = ioपढ़ो32(dest + m * 4);
		पंचांगp &= ~affected_mask;

		पंचांगp |= *(u32 *)(src_byte + m * 4) & affected_mask;
		ioग_लिखो32(पंचांगp, dest + m * 4);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(sof_block_ग_लिखो);

व्योम sof_block_पढ़ो(काष्ठा snd_sof_dev *sdev, u32 bar, u32 offset, व्योम *dest,
		    माप_प्रकार size)
अणु
	व्योम __iomem *src = sdev->bar[bar] + offset;

	स_नकल_fromio(dest, src, size);
पूर्ण
EXPORT_SYMBOL(sof_block_पढ़ो);

/*
 * Generic buffer page table creation.
 * Take the each physical page address and drop the least signअगरicant unused
 * bits from each (based on PAGE_SIZE). Then pack valid page address bits
 * पूर्णांकo compressed page table.
 */

पूर्णांक snd_sof_create_page_table(काष्ठा device *dev,
			      काष्ठा snd_dma_buffer *dmab,
			      अचिन्हित अक्षर *page_table, माप_प्रकार size)
अणु
	पूर्णांक i, pages;

	pages = snd_sgbuf_aligned_pages(size);

	dev_dbg(dev, "generating page table for %p size 0x%zx pages %d\n",
		dmab->area, size, pages);

	क्रम (i = 0; i < pages; i++) अणु
		/*
		 * The number of valid address bits क्रम each page is 20.
		 * idx determines the byte position within page_table
		 * where the current page's address is stored
		 * in the compressed page_table.
		 * This can be calculated by multiplying the page number by 2.5.
		 */
		u32 idx = (5 * i) >> 1;
		u32 pfn = snd_sgbuf_get_addr(dmab, i * PAGE_SIZE) >> PAGE_SHIFT;
		u8 *pg_table;

		dev_vdbg(dev, "pfn i %i idx %d pfn %x\n", i, idx, pfn);

		pg_table = (u8 *)(page_table + idx);

		/*
		 * pagetable compression:
		 * byte 0     byte 1     byte 2     byte 3     byte 4     byte 5
		 * ___________pfn 0__________ __________pfn 1___________  _pfn 2...
		 * .... ....  .... ....  .... ....  .... ....  .... ....  ....
		 * It is created by:
		 * 1. set current location to 0, PFN index i to 0
		 * 2. put pfn[i] at current location in Little Endian byte order
		 * 3. calculate an पूर्णांकermediate value as
		 *    x = (pfn[i+1] << 4) | (pfn[i] & 0xf)
		 * 4. put x at offset (current location + 2) in LE byte order
		 * 5. increment current location by 5 bytes, increment i by 2
		 * 6. जारी to (2)
		 */
		अगर (i & 1)
			put_unaligned_le32((pg_table[0] & 0xf) | pfn << 4,
					   pg_table);
		अन्यथा
			put_unaligned_le32(pfn, pg_table);
	पूर्ण

	वापस pages;
पूर्ण
EXPORT_SYMBOL(snd_sof_create_page_table);
