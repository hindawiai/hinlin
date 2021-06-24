<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Red Hat, Inc.
 * Author: Michael S. Tsirkin <mst@redhat.com>
 *
 * Partial implementation of virtio 0.9. event index is used क्रम संकेतling,
 * unconditionally. Design roughly follows linux kernel implementation in order
 * to be able to judge its perक्रमmance.
 */
#घोषणा _GNU_SOURCE
#समावेश "main.h"
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <निश्चित.स>
#समावेश <माला.स>
#समावेश <linux/virtio_ring.h>

काष्ठा data अणु
	व्योम *data;
पूर्ण *data;

काष्ठा vring ring;

/* enabling the below activates experimental ring polling code
 * (which skips index पढ़ोs on consumer in favor of looking at
 * high bits of ring id ^ 0x8000).
 */
/* #अगर_घोषित RING_POLL */
/* enabling the below activates experimental in-order code
 * (which skips ring updates and पढ़ोs and ग_लिखोs len in descriptor).
 */
/* #अगर_घोषित INORDER */

#अगर defined(RING_POLL) && defined(INORDER)
#त्रुटि "RING_POLL and INORDER are mutually exclusive"
#पूर्ण_अगर

/* how much padding is needed to aव्योम false cache sharing */
#घोषणा HOST_GUEST_PADDING 0x80

काष्ठा guest अणु
	अचिन्हित लघु avail_idx;
	अचिन्हित लघु last_used_idx;
	अचिन्हित लघु num_मुक्त;
	अचिन्हित लघु kicked_avail_idx;
#अगर_अघोषित INORDER
	अचिन्हित लघु मुक्त_head;
#अन्यथा
	अचिन्हित लघु reserved_मुक्त_head;
#पूर्ण_अगर
	अचिन्हित अक्षर reserved[HOST_GUEST_PADDING - 10];
पूर्ण guest;

काष्ठा host अणु
	/* we करो not need to track last avail index
	 * unless we have more than one in flight.
	 */
	अचिन्हित लघु used_idx;
	अचिन्हित लघु called_used_idx;
	अचिन्हित अक्षर reserved[HOST_GUEST_PADDING - 4];
पूर्ण host;

/* implemented by ring */
व्योम alloc_ring(व्योम)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	व्योम *p;

	ret = posix_memalign(&p, 0x1000, vring_size(ring_size, 0x1000));
	अगर (ret) अणु
		लिखो_त्रुटि("Unable to allocate ring buffer.\n");
		निकास(3);
	पूर्ण
	स_रखो(p, 0, vring_size(ring_size, 0x1000));
	vring_init(&ring, ring_size, p, 0x1000);

	guest.avail_idx = 0;
	guest.kicked_avail_idx = -1;
	guest.last_used_idx = 0;
#अगर_अघोषित INORDER
	/* Put everything in मुक्त lists. */
	guest.मुक्त_head = 0;
#पूर्ण_अगर
	क्रम (i = 0; i < ring_size - 1; i++)
		ring.desc[i].next = i + 1;
	host.used_idx = 0;
	host.called_used_idx = -1;
	guest.num_मुक्त = ring_size;
	data = दो_स्मृति(ring_size * माप *data);
	अगर (!data) अणु
		लिखो_त्रुटि("Unable to allocate data buffer.\n");
		निकास(3);
	पूर्ण
	स_रखो(data, 0, ring_size * माप *data);
पूर्ण

/* guest side */
पूर्णांक add_inbuf(अचिन्हित len, व्योम *buf, व्योम *datap)
अणु
	अचिन्हित head;
#अगर_अघोषित INORDER
	अचिन्हित avail;
#पूर्ण_अगर
	काष्ठा vring_desc *desc;

	अगर (!guest.num_मुक्त)
		वापस -1;

#अगर_घोषित INORDER
	head = (ring_size - 1) & (guest.avail_idx++);
#अन्यथा
	head = guest.मुक्त_head;
#पूर्ण_अगर
	guest.num_मुक्त--;

	desc = ring.desc;
	desc[head].flags = VRING_DESC_F_NEXT;
	desc[head].addr = (अचिन्हित दीर्घ)(व्योम *)buf;
	desc[head].len = len;
	/* We करो it like this to simulate the way
	 * we'd have to flip it अगर we had multiple
	 * descriptors.
	 */
	desc[head].flags &= ~VRING_DESC_F_NEXT;
#अगर_अघोषित INORDER
	guest.मुक्त_head = desc[head].next;
#पूर्ण_अगर

	data[head].data = datap;

#अगर_घोषित RING_POLL
	/* Barrier A (क्रम pairing) */
	smp_release();
	avail = guest.avail_idx++;
	ring.avail->ring[avail & (ring_size - 1)] =
		(head | (avail & ~(ring_size - 1))) ^ 0x8000;
#अन्यथा
#अगर_अघोषित INORDER
	/* Barrier A (क्रम pairing) */
	smp_release();
	avail = (ring_size - 1) & (guest.avail_idx++);
	ring.avail->ring[avail] = head;
#पूर्ण_अगर
	/* Barrier A (क्रम pairing) */
	smp_release();
#पूर्ण_अगर
	ring.avail->idx = guest.avail_idx;
	वापस 0;
पूर्ण

व्योम *get_buf(अचिन्हित *lenp, व्योम **bufp)
अणु
	अचिन्हित head;
	अचिन्हित index;
	व्योम *datap;

#अगर_घोषित RING_POLL
	head = (ring_size - 1) & guest.last_used_idx;
	index = ring.used->ring[head].id;
	अगर ((index ^ guest.last_used_idx ^ 0x8000) & ~(ring_size - 1))
		वापस शून्य;
	/* Barrier B (क्रम pairing) */
	smp_acquire();
	index &= ring_size - 1;
#अन्यथा
	अगर (ring.used->idx == guest.last_used_idx)
		वापस शून्य;
	/* Barrier B (क्रम pairing) */
	smp_acquire();
#अगर_घोषित INORDER
	head = (ring_size - 1) & guest.last_used_idx;
	index = head;
#अन्यथा
	head = (ring_size - 1) & guest.last_used_idx;
	index = ring.used->ring[head].id;
#पूर्ण_अगर

#पूर्ण_अगर
#अगर_घोषित INORDER
	*lenp = ring.desc[index].len;
#अन्यथा
	*lenp = ring.used->ring[head].len;
#पूर्ण_अगर
	datap = data[index].data;
	*bufp = (व्योम*)(अचिन्हित दीर्घ)ring.desc[index].addr;
	data[index].data = शून्य;
#अगर_अघोषित INORDER
	ring.desc[index].next = guest.मुक्त_head;
	guest.मुक्त_head = index;
#पूर्ण_अगर
	guest.num_मुक्त++;
	guest.last_used_idx++;
	वापस datap;
पूर्ण

bool used_empty()
अणु
	अचिन्हित लघु last_used_idx = guest.last_used_idx;
#अगर_घोषित RING_POLL
	अचिन्हित लघु head = last_used_idx & (ring_size - 1);
	अचिन्हित index = ring.used->ring[head].id;

	वापस (index ^ last_used_idx ^ 0x8000) & ~(ring_size - 1);
#अन्यथा
	वापस ring.used->idx == last_used_idx;
#पूर्ण_अगर
पूर्ण

व्योम disable_call()
अणु
	/* Doing nothing to disable calls might cause
	 * extra पूर्णांकerrupts, but reduces the number of cache misses.
	 */
पूर्ण

bool enable_call()
अणु
	vring_used_event(&ring) = guest.last_used_idx;
	/* Flush call index ग_लिखो */
	/* Barrier D (क्रम pairing) */
	smp_mb();
	वापस used_empty();
पूर्ण

व्योम kick_available(व्योम)
अणु
	bool need;

	/* Flush in previous flags ग_लिखो */
	/* Barrier C (क्रम pairing) */
	smp_mb();
	need = vring_need_event(vring_avail_event(&ring),
				guest.avail_idx,
				guest.kicked_avail_idx);

	guest.kicked_avail_idx = guest.avail_idx;
	अगर (need)
		kick();
पूर्ण

/* host side */
व्योम disable_kick()
अणु
	/* Doing nothing to disable kicks might cause
	 * extra पूर्णांकerrupts, but reduces the number of cache misses.
	 */
पूर्ण

bool enable_kick()
अणु
	vring_avail_event(&ring) = host.used_idx;
	/* Barrier C (क्रम pairing) */
	smp_mb();
	वापस avail_empty();
पूर्ण

bool avail_empty()
अणु
	अचिन्हित head = host.used_idx;
#अगर_घोषित RING_POLL
	अचिन्हित index = ring.avail->ring[head & (ring_size - 1)];

	वापस ((index ^ head ^ 0x8000) & ~(ring_size - 1));
#अन्यथा
	वापस head == ring.avail->idx;
#पूर्ण_अगर
पूर्ण

bool use_buf(अचिन्हित *lenp, व्योम **bufp)
अणु
	अचिन्हित used_idx = host.used_idx;
	काष्ठा vring_desc *desc;
	अचिन्हित head;

#अगर_घोषित RING_POLL
	head = ring.avail->ring[used_idx & (ring_size - 1)];
	अगर ((used_idx ^ head ^ 0x8000) & ~(ring_size - 1))
		वापस false;
	/* Barrier A (क्रम pairing) */
	smp_acquire();

	used_idx &= ring_size - 1;
	desc = &ring.desc[head & (ring_size - 1)];
#अन्यथा
	अगर (used_idx == ring.avail->idx)
		वापस false;

	/* Barrier A (क्रम pairing) */
	smp_acquire();

	used_idx &= ring_size - 1;
#अगर_घोषित INORDER
	head = used_idx;
#अन्यथा
	head = ring.avail->ring[used_idx];
#पूर्ण_अगर
	desc = &ring.desc[head];
#पूर्ण_अगर

	*lenp = desc->len;
	*bufp = (व्योम *)(अचिन्हित दीर्घ)desc->addr;

#अगर_घोषित INORDER
	desc->len = desc->len - 1;
#अन्यथा
	/* now update used ring */
	ring.used->ring[used_idx].id = head;
	ring.used->ring[used_idx].len = desc->len - 1;
#पूर्ण_अगर
	/* Barrier B (क्रम pairing) */
	smp_release();
	host.used_idx++;
	ring.used->idx = host.used_idx;
	
	वापस true;
पूर्ण

व्योम call_used(व्योम)
अणु
	bool need;

	/* Flush in previous flags ग_लिखो */
	/* Barrier D (क्रम pairing) */
	smp_mb();
	need = vring_need_event(vring_used_event(&ring),
				host.used_idx,
				host.called_used_idx);

	host.called_used_idx = host.used_idx;
	अगर (need)
		call();
पूर्ण
