<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * helpers क्रम managing a buffer क्रम many packets
 *
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 */

#समावेश <linux/firewire.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश "packets-buffer.h"

/**
 * iso_packets_buffer_init - allocates the memory क्रम packets
 * @b: the buffer काष्ठाure to initialize
 * @unit: the device at the other end of the stream
 * @count: the number of packets
 * @packet_size: the (maximum) size of a packet, in bytes
 * @direction: %DMA_TO_DEVICE or %DMA_FROM_DEVICE
 */
पूर्णांक iso_packets_buffer_init(काष्ठा iso_packets_buffer *b, काष्ठा fw_unit *unit,
			    अचिन्हित पूर्णांक count, अचिन्हित पूर्णांक packet_size,
			    क्रमागत dma_data_direction direction)
अणु
	अचिन्हित पूर्णांक packets_per_page, pages;
	अचिन्हित पूर्णांक i, page_index, offset_in_page;
	व्योम *p;
	पूर्णांक err;

	b->packets = kदो_स्मृति_array(count, माप(*b->packets), GFP_KERNEL);
	अगर (!b->packets) अणु
		err = -ENOMEM;
		जाओ error;
	पूर्ण

	packet_size = L1_CACHE_ALIGN(packet_size);
	packets_per_page = PAGE_SIZE / packet_size;
	अगर (WARN_ON(!packets_per_page)) अणु
		err = -EINVAL;
		जाओ err_packets;
	पूर्ण
	pages = DIV_ROUND_UP(count, packets_per_page);

	err = fw_iso_buffer_init(&b->iso_buffer, fw_parent_device(unit)->card,
				 pages, direction);
	अगर (err < 0)
		जाओ err_packets;

	क्रम (i = 0; i < count; ++i) अणु
		page_index = i / packets_per_page;
		p = page_address(b->iso_buffer.pages[page_index]);
		offset_in_page = (i % packets_per_page) * packet_size;
		b->packets[i].buffer = p + offset_in_page;
		b->packets[i].offset = page_index * PAGE_SIZE + offset_in_page;
	पूर्ण

	वापस 0;

err_packets:
	kमुक्त(b->packets);
error:
	वापस err;
पूर्ण
EXPORT_SYMBOL(iso_packets_buffer_init);

/**
 * iso_packets_buffer_destroy - मुक्तs packet buffer resources
 * @b: the buffer काष्ठाure to मुक्त
 * @unit: the device at the other end of the stream
 */
व्योम iso_packets_buffer_destroy(काष्ठा iso_packets_buffer *b,
				काष्ठा fw_unit *unit)
अणु
	fw_iso_buffer_destroy(&b->iso_buffer, fw_parent_device(unit)->card);
	kमुक्त(b->packets);
पूर्ण
EXPORT_SYMBOL(iso_packets_buffer_destroy);
