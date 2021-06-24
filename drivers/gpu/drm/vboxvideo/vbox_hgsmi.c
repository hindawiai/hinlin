<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright (C) 2017 Oracle Corporation
 * Authors: Hans de Goede <hdegoede@redhat.com>
 */

#समावेश "vbox_drv.h"
#समावेश "vboxvideo_vbe.h"
#समावेश "hgsmi_defs.h"

/* One-at-a-Time Hash from https://www.burtleburtle.net/bob/hash/करोobs.hपंचांगl */
अटल u32 hgsmi_hash_process(u32 hash, स्थिर u8 *data, पूर्णांक size)
अणु
	जबतक (size--) अणु
		hash += *data++;
		hash += (hash << 10);
		hash ^= (hash >> 6);
	पूर्ण

	वापस hash;
पूर्ण

अटल u32 hgsmi_hash_end(u32 hash)
अणु
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);

	वापस hash;
पूर्ण

/* Not really a checksum but that is the naming used in all vbox code */
अटल u32 hgsmi_checksum(u32 offset,
			  स्थिर काष्ठा hgsmi_buffer_header *header,
			  स्थिर काष्ठा hgsmi_buffer_tail *tail)
अणु
	u32 checksum;

	checksum = hgsmi_hash_process(0, (u8 *)&offset, माप(offset));
	checksum = hgsmi_hash_process(checksum, (u8 *)header, माप(*header));
	/* 4 -> Do not checksum the checksum itself */
	checksum = hgsmi_hash_process(checksum, (u8 *)tail, 4);

	वापस hgsmi_hash_end(checksum);
पूर्ण

व्योम *hgsmi_buffer_alloc(काष्ठा gen_pool *guest_pool, माप_प्रकार size,
			 u8 channel, u16 channel_info)
अणु
	काष्ठा hgsmi_buffer_header *h;
	काष्ठा hgsmi_buffer_tail *t;
	माप_प्रकार total_size;
	dma_addr_t offset;

	total_size = size + माप(*h) + माप(*t);
	h = gen_pool_dma_alloc(guest_pool, total_size, &offset);
	अगर (!h)
		वापस शून्य;

	t = (काष्ठा hgsmi_buffer_tail *)((u8 *)h + माप(*h) + size);

	h->flags = HGSMI_BUFFER_HEADER_F_SEQ_SINGLE;
	h->data_size = size;
	h->channel = channel;
	h->channel_info = channel_info;
	स_रखो(&h->u.header_data, 0, माप(h->u.header_data));

	t->reserved = 0;
	t->checksum = hgsmi_checksum(offset, h, t);

	वापस (u8 *)h + माप(*h);
पूर्ण

व्योम hgsmi_buffer_मुक्त(काष्ठा gen_pool *guest_pool, व्योम *buf)
अणु
	काष्ठा hgsmi_buffer_header *h =
		(काष्ठा hgsmi_buffer_header *)((u8 *)buf - माप(*h));
	माप_प्रकार total_size = h->data_size + माप(*h) +
					     माप(काष्ठा hgsmi_buffer_tail);

	gen_pool_मुक्त(guest_pool, (अचिन्हित दीर्घ)h, total_size);
पूर्ण

पूर्णांक hgsmi_buffer_submit(काष्ठा gen_pool *guest_pool, व्योम *buf)
अणु
	phys_addr_t offset;

	offset = gen_pool_virt_to_phys(guest_pool, (अचिन्हित दीर्घ)buf -
				       माप(काष्ठा hgsmi_buffer_header));
	outl(offset, VGA_PORT_HGSMI_GUEST);
	/* Make the compiler aware that the host has changed memory. */
	mb();

	वापस 0;
पूर्ण
