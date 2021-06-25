<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Red Hat, Inc.
 * Author: Michael S. Tsirkin <mst@redhat.com>
 *
 * Simple descriptor-based ring. virtio 0.9 compatible event index is used क्रम
 * संकेतling, unconditionally.
 */
#घोषणा _GNU_SOURCE
#समावेश "main.h"
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>

/* Next - Where next entry will be written.
 * Prev - "Next" value when event triggered previously.
 * Event - Peer requested event after writing this entry.
 */
अटल अंतरभूत bool need_event(अचिन्हित लघु event,
			      अचिन्हित लघु next,
			      अचिन्हित लघु prev)
अणु
	वापस (अचिन्हित लघु)(next - event - 1) < (अचिन्हित लघु)(next - prev);
पूर्ण

/* Design:
 * Guest adds descriptors with unique index values and DESC_HW in flags.
 * Host overग_लिखोs used descriptors with correct len, index, and DESC_HW clear.
 * Flags are always set last.
 */
#घोषणा DESC_HW 0x1

काष्ठा desc अणु
	अचिन्हित लघु flags;
	अचिन्हित लघु index;
	अचिन्हित len;
	अचिन्हित दीर्घ दीर्घ addr;
पूर्ण;

/* how much padding is needed to aव्योम false cache sharing */
#घोषणा HOST_GUEST_PADDING 0x80

/* Mostly पढ़ो */
काष्ठा event अणु
	अचिन्हित लघु kick_index;
	अचिन्हित अक्षर reserved0[HOST_GUEST_PADDING - 2];
	अचिन्हित लघु call_index;
	अचिन्हित अक्षर reserved1[HOST_GUEST_PADDING - 2];
पूर्ण;

काष्ठा data अणु
	व्योम *buf; /* descriptor is ग_लिखोable, we can't get buf from there */
	व्योम *data;
पूर्ण *data;

काष्ठा desc *ring;
काष्ठा event *event;

काष्ठा guest अणु
	अचिन्हित avail_idx;
	अचिन्हित last_used_idx;
	अचिन्हित num_मुक्त;
	अचिन्हित kicked_avail_idx;
	अचिन्हित अक्षर reserved[HOST_GUEST_PADDING - 12];
पूर्ण guest;

काष्ठा host अणु
	/* we करो not need to track last avail index
	 * unless we have more than one in flight.
	 */
	अचिन्हित used_idx;
	अचिन्हित called_used_idx;
	अचिन्हित अक्षर reserved[HOST_GUEST_PADDING - 4];
पूर्ण host;

/* implemented by ring */
व्योम alloc_ring(व्योम)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	ret = posix_memalign((व्योम **)&ring, 0x1000, ring_size * माप *ring);
	अगर (ret) अणु
		लिखो_त्रुटि("Unable to allocate ring buffer.\n");
		निकास(3);
	पूर्ण
	event = सुस्मृति(1, माप(*event));
	अगर (!event) अणु
		लिखो_त्रुटि("Unable to allocate event buffer.\n");
		निकास(3);
	पूर्ण
	guest.avail_idx = 0;
	guest.kicked_avail_idx = -1;
	guest.last_used_idx = 0;
	host.used_idx = 0;
	host.called_used_idx = -1;
	क्रम (i = 0; i < ring_size; ++i) अणु
		काष्ठा desc desc = अणु
			.index = i,
		पूर्ण;
		ring[i] = desc;
	पूर्ण
	guest.num_मुक्त = ring_size;
	data = सुस्मृति(ring_size, माप(*data));
	अगर (!data) अणु
		लिखो_त्रुटि("Unable to allocate data buffer.\n");
		निकास(3);
	पूर्ण
पूर्ण

/* guest side */
पूर्णांक add_inbuf(अचिन्हित len, व्योम *buf, व्योम *datap)
अणु
	अचिन्हित head, index;

	अगर (!guest.num_मुक्त)
		वापस -1;

	guest.num_मुक्त--;
	head = (ring_size - 1) & (guest.avail_idx++);

	/* Start with a ग_लिखो. On MESI architectures this helps
	 * aव्योम a shared state with consumer that is polling this descriptor.
	 */
	ring[head].addr = (अचिन्हित दीर्घ)(व्योम*)buf;
	ring[head].len = len;
	/* पढ़ो below might bypass ग_लिखो above. That is OK because it's just an
	 * optimization. If this happens, we will get the cache line in a
	 * shared state which is unक्रमtunate, but probably not worth it to
	 * add an explicit full barrier to aव्योम this.
	 */
	barrier();
	index = ring[head].index;
	data[index].buf = buf;
	data[index].data = datap;
	/* Barrier A (क्रम pairing) */
	smp_release();
	ring[head].flags = DESC_HW;

	वापस 0;
पूर्ण

व्योम *get_buf(अचिन्हित *lenp, व्योम **bufp)
अणु
	अचिन्हित head = (ring_size - 1) & guest.last_used_idx;
	अचिन्हित index;
	व्योम *datap;

	अगर (ring[head].flags & DESC_HW)
		वापस शून्य;
	/* Barrier B (क्रम pairing) */
	smp_acquire();
	*lenp = ring[head].len;
	index = ring[head].index & (ring_size - 1);
	datap = data[index].data;
	*bufp = data[index].buf;
	data[index].buf = शून्य;
	data[index].data = शून्य;
	guest.num_मुक्त++;
	guest.last_used_idx++;
	वापस datap;
पूर्ण

bool used_empty()
अणु
	अचिन्हित head = (ring_size - 1) & guest.last_used_idx;

	वापस (ring[head].flags & DESC_HW);
पूर्ण

व्योम disable_call()
अणु
	/* Doing nothing to disable calls might cause
	 * extra पूर्णांकerrupts, but reduces the number of cache misses.
	 */
पूर्ण

bool enable_call()
अणु
	event->call_index = guest.last_used_idx;
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
	need = need_event(event->kick_index,
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
	event->kick_index = host.used_idx;
	/* Barrier C (क्रम pairing) */
	smp_mb();
	वापस avail_empty();
पूर्ण

bool avail_empty()
अणु
	अचिन्हित head = (ring_size - 1) & host.used_idx;

	वापस !(ring[head].flags & DESC_HW);
पूर्ण

bool use_buf(अचिन्हित *lenp, व्योम **bufp)
अणु
	अचिन्हित head = (ring_size - 1) & host.used_idx;

	अगर (!(ring[head].flags & DESC_HW))
		वापस false;

	/* make sure length पढ़ो below is not speculated */
	/* Barrier A (क्रम pairing) */
	smp_acquire();

	/* simple in-order completion: we करोn't need
	 * to touch index at all. This also means we
	 * can just modअगरy the descriptor in-place.
	 */
	ring[head].len--;
	/* Make sure len is valid beक्रमe flags.
	 * Note: alternative is to ग_लिखो len and flags in one access -
	 * possible on 64 bit architectures but wmb is मुक्त on Intel anyway
	 * so I have no way to test whether it's a gain.
	 */
	/* Barrier B (क्रम pairing) */
	smp_release();
	ring[head].flags = 0;
	host.used_idx++;
	वापस true;
पूर्ण

व्योम call_used(व्योम)
अणु
	bool need;

	/* Flush in previous flags ग_लिखो */
	/* Barrier D (क्रम pairing) */
	smp_mb();

	need = need_event(event->call_index,
			host.used_idx,
			host.called_used_idx);

	host.called_used_idx = host.used_idx;

	अगर (need)
		call();
पूर्ण
