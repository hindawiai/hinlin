<शैली गुरु>
// SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause)
/*
 * Ring buffer operations.
 *
 * Copyright (C) 2020 Facebook, Inc.
 */
#अगर_अघोषित _GNU_SOURCE
#घोषणा _GNU_SOURCE
#पूर्ण_अगर
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>
#समावेश <linux/err.h>
#समावेश <linux/bpf.h>
#समावेश <यंत्र/barrier.h>
#समावेश <sys/mman.h>
#समावेश <sys/epoll.h>

#समावेश "libbpf.h"
#समावेश "libbpf_internal.h"
#समावेश "bpf.h"

काष्ठा ring अणु
	ring_buffer_sample_fn sample_cb;
	व्योम *ctx;
	व्योम *data;
	अचिन्हित दीर्घ *consumer_pos;
	अचिन्हित दीर्घ *producer_pos;
	अचिन्हित दीर्घ mask;
	पूर्णांक map_fd;
पूर्ण;

काष्ठा ring_buffer अणु
	काष्ठा epoll_event *events;
	काष्ठा ring *rings;
	माप_प्रकार page_size;
	पूर्णांक epoll_fd;
	पूर्णांक ring_cnt;
पूर्ण;

अटल व्योम ringbuf_unmap_ring(काष्ठा ring_buffer *rb, काष्ठा ring *r)
अणु
	अगर (r->consumer_pos) अणु
		munmap(r->consumer_pos, rb->page_size);
		r->consumer_pos = शून्य;
	पूर्ण
	अगर (r->producer_pos) अणु
		munmap(r->producer_pos, rb->page_size + 2 * (r->mask + 1));
		r->producer_pos = शून्य;
	पूर्ण
पूर्ण

/* Add extra RINGBUF maps to this ring buffer manager */
पूर्णांक ring_buffer__add(काष्ठा ring_buffer *rb, पूर्णांक map_fd,
		     ring_buffer_sample_fn sample_cb, व्योम *ctx)
अणु
	काष्ठा bpf_map_info info;
	__u32 len = माप(info);
	काष्ठा epoll_event *e;
	काष्ठा ring *r;
	व्योम *पंचांगp;
	पूर्णांक err;

	स_रखो(&info, 0, माप(info));

	err = bpf_obj_get_info_by_fd(map_fd, &info, &len);
	अगर (err) अणु
		err = -त्रुटि_सं;
		pr_warn("ringbuf: failed to get map info for fd=%d: %d\n",
			map_fd, err);
		वापस err;
	पूर्ण

	अगर (info.type != BPF_MAP_TYPE_RINGBUF) अणु
		pr_warn("ringbuf: map fd=%d is not BPF_MAP_TYPE_RINGBUF\n",
			map_fd);
		वापस -EINVAL;
	पूर्ण

	पंचांगp = libbpf_पुनः_स्मृतिarray(rb->rings, rb->ring_cnt + 1, माप(*rb->rings));
	अगर (!पंचांगp)
		वापस -ENOMEM;
	rb->rings = पंचांगp;

	पंचांगp = libbpf_पुनः_स्मृतिarray(rb->events, rb->ring_cnt + 1, माप(*rb->events));
	अगर (!पंचांगp)
		वापस -ENOMEM;
	rb->events = पंचांगp;

	r = &rb->rings[rb->ring_cnt];
	स_रखो(r, 0, माप(*r));

	r->map_fd = map_fd;
	r->sample_cb = sample_cb;
	r->ctx = ctx;
	r->mask = info.max_entries - 1;

	/* Map writable consumer page */
	पंचांगp = mmap(शून्य, rb->page_size, PROT_READ | PROT_WRITE, MAP_SHARED,
		   map_fd, 0);
	अगर (पंचांगp == MAP_FAILED) अणु
		err = -त्रुटि_सं;
		pr_warn("ringbuf: failed to mmap consumer page for map fd=%d: %d\n",
			map_fd, err);
		वापस err;
	पूर्ण
	r->consumer_pos = पंचांगp;

	/* Map पढ़ो-only producer page and data pages. We map twice as big
	 * data size to allow simple पढ़ोing of samples that wrap around the
	 * end of a ring buffer. See kernel implementation क्रम details.
	 * */
	पंचांगp = mmap(शून्य, rb->page_size + 2 * info.max_entries, PROT_READ,
		   MAP_SHARED, map_fd, rb->page_size);
	अगर (पंचांगp == MAP_FAILED) अणु
		err = -त्रुटि_सं;
		ringbuf_unmap_ring(rb, r);
		pr_warn("ringbuf: failed to mmap data pages for map fd=%d: %d\n",
			map_fd, err);
		वापस err;
	पूर्ण
	r->producer_pos = पंचांगp;
	r->data = पंचांगp + rb->page_size;

	e = &rb->events[rb->ring_cnt];
	स_रखो(e, 0, माप(*e));

	e->events = EPOLLIN;
	e->data.fd = rb->ring_cnt;
	अगर (epoll_ctl(rb->epoll_fd, EPOLL_CTL_ADD, map_fd, e) < 0) अणु
		err = -त्रुटि_सं;
		ringbuf_unmap_ring(rb, r);
		pr_warn("ringbuf: failed to epoll add map fd=%d: %d\n",
			map_fd, err);
		वापस err;
	पूर्ण

	rb->ring_cnt++;
	वापस 0;
पूर्ण

व्योम ring_buffer__मुक्त(काष्ठा ring_buffer *rb)
अणु
	पूर्णांक i;

	अगर (!rb)
		वापस;

	क्रम (i = 0; i < rb->ring_cnt; ++i)
		ringbuf_unmap_ring(rb, &rb->rings[i]);
	अगर (rb->epoll_fd >= 0)
		बंद(rb->epoll_fd);

	मुक्त(rb->events);
	मुक्त(rb->rings);
	मुक्त(rb);
पूर्ण

काष्ठा ring_buffer *
ring_buffer__new(पूर्णांक map_fd, ring_buffer_sample_fn sample_cb, व्योम *ctx,
		 स्थिर काष्ठा ring_buffer_opts *opts)
अणु
	काष्ठा ring_buffer *rb;
	पूर्णांक err;

	अगर (!OPTS_VALID(opts, ring_buffer_opts))
		वापस शून्य;

	rb = सुस्मृति(1, माप(*rb));
	अगर (!rb)
		वापस शून्य;

	rb->page_size = getpagesize();

	rb->epoll_fd = epoll_create1(EPOLL_CLOEXEC);
	अगर (rb->epoll_fd < 0) अणु
		err = -त्रुटि_सं;
		pr_warn("ringbuf: failed to create epoll instance: %d\n", err);
		जाओ err_out;
	पूर्ण

	err = ring_buffer__add(rb, map_fd, sample_cb, ctx);
	अगर (err)
		जाओ err_out;

	वापस rb;

err_out:
	ring_buffer__मुक्त(rb);
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक roundup_len(__u32 len)
अणु
	/* clear out top 2 bits (discard and busy, अगर set) */
	len <<= 2;
	len >>= 2;
	/* add length prefix */
	len += BPF_RINGBUF_HDR_SZ;
	/* round up to 8 byte alignment */
	वापस (len + 7) / 8 * 8;
पूर्ण

अटल पूर्णांक64_t ringbuf_process_ring(काष्ठा ring* r)
अणु
	पूर्णांक *len_ptr, len, err;
	/* 64-bit to aव्योम overflow in हाल of extreme application behavior */
	पूर्णांक64_t cnt = 0;
	अचिन्हित दीर्घ cons_pos, prod_pos;
	bool got_new_data;
	व्योम *sample;

	cons_pos = smp_load_acquire(r->consumer_pos);
	करो अणु
		got_new_data = false;
		prod_pos = smp_load_acquire(r->producer_pos);
		जबतक (cons_pos < prod_pos) अणु
			len_ptr = r->data + (cons_pos & r->mask);
			len = smp_load_acquire(len_ptr);

			/* sample not committed yet, bail out क्रम now */
			अगर (len & BPF_RINGBUF_BUSY_BIT)
				जाओ करोne;

			got_new_data = true;
			cons_pos += roundup_len(len);

			अगर ((len & BPF_RINGBUF_DISCARD_BIT) == 0) अणु
				sample = (व्योम *)len_ptr + BPF_RINGBUF_HDR_SZ;
				err = r->sample_cb(r->ctx, sample, len);
				अगर (err < 0) अणु
					/* update consumer pos and bail out */
					smp_store_release(r->consumer_pos,
							  cons_pos);
					वापस err;
				पूर्ण
				cnt++;
			पूर्ण

			smp_store_release(r->consumer_pos, cons_pos);
		पूर्ण
	पूर्ण जबतक (got_new_data);
करोne:
	वापस cnt;
पूर्ण

/* Consume available ring buffer(s) data without event polling.
 * Returns number of records consumed across all रेजिस्टरed ring buffers (or
 * पूर्णांक_उच्च, whichever is less), or negative number अगर any of the callbacks
 * वापस error.
 */
पूर्णांक ring_buffer__consume(काष्ठा ring_buffer *rb)
अणु
	पूर्णांक64_t err, res = 0;
	पूर्णांक i;

	क्रम (i = 0; i < rb->ring_cnt; i++) अणु
		काष्ठा ring *ring = &rb->rings[i];

		err = ringbuf_process_ring(ring);
		अगर (err < 0)
			वापस err;
		res += err;
	पूर्ण
	अगर (res > पूर्णांक_उच्च)
		वापस पूर्णांक_उच्च;
	वापस res;
पूर्ण

/* Poll क्रम available data and consume records, अगर any are available.
 * Returns number of records consumed (or पूर्णांक_उच्च, whichever is less), or
 * negative number, अगर any of the रेजिस्टरed callbacks वापसed error.
 */
पूर्णांक ring_buffer__poll(काष्ठा ring_buffer *rb, पूर्णांक समयout_ms)
अणु
	पूर्णांक i, cnt;
	पूर्णांक64_t err, res = 0;

	cnt = epoll_रुको(rb->epoll_fd, rb->events, rb->ring_cnt, समयout_ms);
	अगर (cnt < 0)
		वापस -त्रुटि_सं;

	क्रम (i = 0; i < cnt; i++) अणु
		__u32 ring_id = rb->events[i].data.fd;
		काष्ठा ring *ring = &rb->rings[ring_id];

		err = ringbuf_process_ring(ring);
		अगर (err < 0)
			वापस err;
		res += err;
	पूर्ण
	अगर (res > पूर्णांक_उच्च)
		वापस पूर्णांक_उच्च;
	वापस res;
पूर्ण

/* Get an fd that can be used to sleep until data is available in the ring(s) */
पूर्णांक ring_buffer__epoll_fd(स्थिर काष्ठा ring_buffer *rb)
अणु
	वापस rb->epoll_fd;
पूर्ण
