<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the NXP SAA7164 PCIe bridge
 *
 *  Copyright (c) 2010-2015 Steven Toth <stoth@kernelद_असल.com>
 */

#समावेश <linux/slab.h>

#समावेश "saa7164.h"

/* The PCI address space क्रम buffer handling looks like this:
 *
 * +-u32 wide-------------+
 * |                      +
 * +-u64 wide------------------------------------+
 * +                                             +
 * +----------------------+
 * | CurrentBufferPtr     + Poपूर्णांकer to current PCI buffer >-+
 * +----------------------+                                 |
 * | Unused               +                                 |
 * +----------------------+                                 |
 * | Pitch                + = 188 (bytes)                   |
 * +----------------------+                                 |
 * | PCI buffer size      + = pitch * number of lines (312) |
 * +----------------------+                                 |
 * |0| Buf0 Write Offset  +                                 |
 * +----------------------+                                 v
 * |1| Buf1 Write Offset  +                                 |
 * +----------------------+                                 |
 * |2| Buf2 Write Offset  +                                 |
 * +----------------------+                                 |
 * |3| Buf3 Write Offset  +                                 |
 * +----------------------+                                 |
 * ... More ग_लिखो offsets                                   |
 * +---------------------------------------------+          |
 * +0| set of ptrs to PCI pagetables             +          |
 * +---------------------------------------------+          |
 * +1| set of ptrs to PCI pagetables             + <--------+
 * +---------------------------------------------+
 * +2| set of ptrs to PCI pagetables             +
 * +---------------------------------------------+
 * +3| set of ptrs to PCI pagetables             + >--+
 * +---------------------------------------------+    |
 * ... More buffer poपूर्णांकers                           |  +----------------+
 *						    +->| pt[0] TS data  |
 *						    |  +----------------+
 *						    |
 *						    |  +----------------+
 *						    +->| pt[1] TS data  |
 *						    |  +----------------+
 *						    | etc
 */

व्योम saa7164_buffer_display(काष्ठा saa7164_buffer *buf)
अणु
	काष्ठा saa7164_dev *dev = buf->port->dev;
	पूर्णांक i;

	dprपूर्णांकk(DBGLVL_BUF, "%s()   buffer @ 0x%p nr=%d\n",
		__func__, buf, buf->idx);
	dprपूर्णांकk(DBGLVL_BUF, "  pci_cpu @ 0x%p    dma @ 0x%08llx len = 0x%x\n",
		buf->cpu, (दीर्घ दीर्घ)buf->dma, buf->pci_size);
	dprपूर्णांकk(DBGLVL_BUF, "   pt_cpu @ 0x%p pt_dma @ 0x%08llx len = 0x%x\n",
		buf->pt_cpu, (दीर्घ दीर्घ)buf->pt_dma, buf->pt_size);

	/* Format the Page Table Entries to poपूर्णांक पूर्णांकo the data buffer */
	क्रम (i = 0 ; i < SAA7164_PT_ENTRIES; i++) अणु

		dprपूर्णांकk(DBGLVL_BUF, "    pt[%02d] = 0x%p -> 0x%llx\n",
			i, buf->pt_cpu, (u64)*(buf->pt_cpu));

	पूर्ण
पूर्ण
/* Allocate a new buffer काष्ठाure and associated PCI space in bytes.
 * len must be a multiple of माप(u64)
 */
काष्ठा saa7164_buffer *saa7164_buffer_alloc(काष्ठा saa7164_port *port,
	u32 len)
अणु
	काष्ठा पंचांगHWStreamParameters *params = &port->hw_streamingparams;
	काष्ठा saa7164_buffer *buf = शून्य;
	काष्ठा saa7164_dev *dev = port->dev;
	पूर्णांक i;

	अगर ((len == 0) || (len >= 65536) || (len % माप(u64))) अणु
		log_warn("%s() SAA_ERR_BAD_PARAMETER\n", __func__);
		जाओ ret;
	पूर्ण

	buf = kzalloc(माप(*buf), GFP_KERNEL);
	अगर (!buf)
		जाओ ret;

	buf->idx = -1;
	buf->port = port;
	buf->flags = SAA7164_BUFFER_FREE;
	buf->pos = 0;
	buf->actual_size = params->pitch * params->numberoflines;
	buf->crc = 0;
	/* TODO: arg len is being ignored */
	buf->pci_size = SAA7164_PT_ENTRIES * 0x1000;
	buf->pt_size = (SAA7164_PT_ENTRIES * माप(u64)) + 0x1000;

	/* Allocate contiguous memory */
	buf->cpu = dma_alloc_coherent(&port->dev->pci->dev, buf->pci_size,
				      &buf->dma, GFP_KERNEL);
	अगर (!buf->cpu)
		जाओ fail1;

	buf->pt_cpu = dma_alloc_coherent(&port->dev->pci->dev, buf->pt_size,
					 &buf->pt_dma, GFP_KERNEL);
	अगर (!buf->pt_cpu)
		जाओ fail2;

	/* init the buffers to a known pattern, easier during debugging */
	स_रखो(buf->cpu, 0xff, buf->pci_size);
	buf->crc = crc32(0, buf->cpu, buf->actual_size);
	स_रखो(buf->pt_cpu, 0xff, buf->pt_size);

	dprपूर्णांकk(DBGLVL_BUF, "%s()   allocated buffer @ 0x%p (%d pageptrs)\n",
		__func__, buf, params->numpagetables);
	dprपूर्णांकk(DBGLVL_BUF, "  pci_cpu @ 0x%p    dma @ 0x%08lx len = 0x%x\n",
		buf->cpu, (दीर्घ)buf->dma, buf->pci_size);
	dprपूर्णांकk(DBGLVL_BUF, "   pt_cpu @ 0x%p pt_dma @ 0x%08lx len = 0x%x\n",
		buf->pt_cpu, (दीर्घ)buf->pt_dma, buf->pt_size);

	/* Format the Page Table Entries to poपूर्णांक पूर्णांकo the data buffer */
	क्रम (i = 0 ; i < params->numpagetables; i++) अणु

		*(buf->pt_cpu + i) = buf->dma + (i * 0x1000); /* TODO */
		dprपूर्णांकk(DBGLVL_BUF, "    pt[%02d] = 0x%p -> 0x%llx\n",
			i, buf->pt_cpu, (u64)*(buf->pt_cpu));

	पूर्ण

	जाओ ret;

fail2:
	dma_मुक्त_coherent(&port->dev->pci->dev, buf->pci_size, buf->cpu,
			  buf->dma);
fail1:
	kमुक्त(buf);

	buf = शून्य;
ret:
	वापस buf;
पूर्ण

पूर्णांक saa7164_buffer_dealloc(काष्ठा saa7164_buffer *buf)
अणु
	काष्ठा saa7164_dev *dev;

	अगर (!buf || !buf->port)
		वापस SAA_ERR_BAD_PARAMETER;
	dev = buf->port->dev;

	dprपूर्णांकk(DBGLVL_BUF, "%s() deallocating buffer @ 0x%p\n",
		__func__, buf);

	अगर (buf->flags != SAA7164_BUFFER_FREE)
		log_warn(" freeing a non-free buffer\n");

	dma_मुक्त_coherent(&dev->pci->dev, buf->pci_size, buf->cpu, buf->dma);
	dma_मुक्त_coherent(&dev->pci->dev, buf->pt_size, buf->pt_cpu,
			  buf->pt_dma);

	kमुक्त(buf);

	वापस SAA_OK;
पूर्ण

पूर्णांक saa7164_buffer_zero_offsets(काष्ठा saa7164_port *port, पूर्णांक i)
अणु
	काष्ठा saa7164_dev *dev = port->dev;

	अगर ((i < 0) || (i >= port->hwcfg.buffercount))
		वापस -EINVAL;

	dprपूर्णांकk(DBGLVL_BUF, "%s(idx = %d)\n", __func__, i);

	saa7164_ग_लिखोl(port->bufoffset + (माप(u32) * i), 0);

	वापस 0;
पूर्ण

/* Write a buffer पूर्णांकo the hardware */
पूर्णांक saa7164_buffer_activate(काष्ठा saa7164_buffer *buf, पूर्णांक i)
अणु
	काष्ठा saa7164_port *port = buf->port;
	काष्ठा saa7164_dev *dev = port->dev;

	अगर ((i < 0) || (i >= port->hwcfg.buffercount))
		वापस -EINVAL;

	dprपूर्णांकk(DBGLVL_BUF, "%s(idx = %d)\n", __func__, i);

	buf->idx = i; /* Note of which buffer list index position we occupy */
	buf->flags = SAA7164_BUFFER_BUSY;
	buf->pos = 0;

	/* TODO: Review this in light of 32v64 assignments */
	saa7164_ग_लिखोl(port->bufoffset + (माप(u32) * i), 0);
	saa7164_ग_लिखोl(port->bufptr32h + ((माप(u32) * 2) * i), buf->pt_dma);
	saa7164_ग_लिखोl(port->bufptr32l + ((माप(u32) * 2) * i), 0);

	dprपूर्णांकk(DBGLVL_BUF, "	buf[%d] offset 0x%llx (0x%x) buf 0x%llx/%llx (0x%x/%x) nr=%d\n",
		buf->idx,
		(u64)port->bufoffset + (i * माप(u32)),
		saa7164_पढ़ोl(port->bufoffset + (माप(u32) * i)),
		(u64)port->bufptr32h + ((माप(u32) * 2) * i),
		(u64)port->bufptr32l + ((माप(u32) * 2) * i),
		saa7164_पढ़ोl(port->bufptr32h + ((माप(u32) * i) * 2)),
		saa7164_पढ़ोl(port->bufptr32l + ((माप(u32) * i) * 2)),
		buf->idx);

	वापस 0;
पूर्ण

पूर्णांक saa7164_buffer_cfg_port(काष्ठा saa7164_port *port)
अणु
	काष्ठा पंचांगHWStreamParameters *params = &port->hw_streamingparams;
	काष्ठा saa7164_dev *dev = port->dev;
	काष्ठा saa7164_buffer *buf;
	काष्ठा list_head *c, *n;
	पूर्णांक i = 0;

	dprपूर्णांकk(DBGLVL_BUF, "%s(port=%d)\n", __func__, port->nr);

	saa7164_ग_लिखोl(port->bufcounter, 0);
	saa7164_ग_लिखोl(port->pitch, params->pitch);
	saa7164_ग_लिखोl(port->bufsize, params->pitch * params->numberoflines);

	dprपूर्णांकk(DBGLVL_BUF, " configured:\n");
	dprपूर्णांकk(DBGLVL_BUF, "   lmmio       0x%p\n", dev->lmmio);
	dprपूर्णांकk(DBGLVL_BUF, "   bufcounter  0x%x = 0x%x\n", port->bufcounter,
		saa7164_पढ़ोl(port->bufcounter));

	dprपूर्णांकk(DBGLVL_BUF, "   pitch       0x%x = %d\n", port->pitch,
		saa7164_पढ़ोl(port->pitch));

	dprपूर्णांकk(DBGLVL_BUF, "   bufsize     0x%x = %d\n", port->bufsize,
		saa7164_पढ़ोl(port->bufsize));

	dprपूर्णांकk(DBGLVL_BUF, "   buffercount = %d\n", port->hwcfg.buffercount);
	dprपूर्णांकk(DBGLVL_BUF, "   bufoffset = 0x%x\n", port->bufoffset);
	dprपूर्णांकk(DBGLVL_BUF, "   bufptr32h = 0x%x\n", port->bufptr32h);
	dprपूर्णांकk(DBGLVL_BUF, "   bufptr32l = 0x%x\n", port->bufptr32l);

	/* Poke the buffers and offsets पूर्णांकo PCI space */
	mutex_lock(&port->dmaqueue_lock);
	list_क्रम_each_safe(c, n, &port->dmaqueue.list) अणु
		buf = list_entry(c, काष्ठा saa7164_buffer, list);

		BUG_ON(buf->flags != SAA7164_BUFFER_FREE);

		/* Place the buffer in the h/w queue */
		saa7164_buffer_activate(buf, i);

		/* Don't exceed the device maximum # bufs */
		BUG_ON(i > port->hwcfg.buffercount);
		i++;

	पूर्ण
	mutex_unlock(&port->dmaqueue_lock);

	वापस 0;
पूर्ण

काष्ठा saa7164_user_buffer *saa7164_buffer_alloc_user(काष्ठा saa7164_dev *dev,
	u32 len)
अणु
	काष्ठा saa7164_user_buffer *buf;

	buf = kzalloc(माप(*buf), GFP_KERNEL);
	अगर (!buf)
		वापस शून्य;

	buf->data = kzalloc(len, GFP_KERNEL);

	अगर (!buf->data) अणु
		kमुक्त(buf);
		वापस शून्य;
	पूर्ण

	buf->actual_size = len;
	buf->pos = 0;
	buf->crc = 0;

	dprपूर्णांकk(DBGLVL_BUF, "%s()   allocated user buffer @ 0x%p\n",
		__func__, buf);

	वापस buf;
पूर्ण

व्योम saa7164_buffer_dealloc_user(काष्ठा saa7164_user_buffer *buf)
अणु
	अगर (!buf)
		वापस;

	kमुक्त(buf->data);
	buf->data = शून्य;

	kमुक्त(buf);
पूर्ण
