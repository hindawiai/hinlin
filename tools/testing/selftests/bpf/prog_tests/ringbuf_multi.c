<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE
#समावेश <test_progs.h>
#समावेश <sys/epoll.h>
#समावेश "test_ringbuf_multi.skel.h"

अटल पूर्णांक duration = 0;

काष्ठा sample अणु
	पूर्णांक pid;
	पूर्णांक seq;
	दीर्घ value;
	अक्षर comm[16];
पूर्ण;

अटल पूर्णांक process_sample(व्योम *ctx, व्योम *data, माप_प्रकार len)
अणु
	पूर्णांक ring = (अचिन्हित दीर्घ)ctx;
	काष्ठा sample *s = data;

	चयन (s->seq) अणु
	हाल 0:
		CHECK(ring != 1, "sample1_ring", "exp %d, got %d\n", 1, ring);
		CHECK(s->value != 333, "sample1_value", "exp %ld, got %ld\n",
		      333L, s->value);
		अवरोध;
	हाल 1:
		CHECK(ring != 2, "sample2_ring", "exp %d, got %d\n", 2, ring);
		CHECK(s->value != 777, "sample2_value", "exp %ld, got %ld\n",
		      777L, s->value);
		अवरोध;
	शेष:
		CHECK(true, "extra_sample", "unexpected sample seq %d, val %ld\n",
		      s->seq, s->value);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

व्योम test_ringbuf_multi(व्योम)
अणु
	काष्ठा test_ringbuf_multi *skel;
	काष्ठा ring_buffer *ringbuf = शून्य;
	पूर्णांक err;
	पूर्णांक page_size = getpagesize();
	पूर्णांक proto_fd = -1;

	skel = test_ringbuf_multi__खोलो();
	अगर (CHECK(!skel, "skel_open", "skeleton open failed\n"))
		वापस;

	err = bpf_map__set_max_entries(skel->maps.ringbuf1, page_size);
	अगर (CHECK(err != 0, "bpf_map__set_max_entries", "bpf_map__set_max_entries failed\n"))
		जाओ cleanup;

	err = bpf_map__set_max_entries(skel->maps.ringbuf2, page_size);
	अगर (CHECK(err != 0, "bpf_map__set_max_entries", "bpf_map__set_max_entries failed\n"))
		जाओ cleanup;

	err = bpf_map__set_max_entries(bpf_map__inner_map(skel->maps.ringbuf_arr), page_size);
	अगर (CHECK(err != 0, "bpf_map__set_max_entries", "bpf_map__set_max_entries failed\n"))
		जाओ cleanup;

	proto_fd = bpf_create_map(BPF_MAP_TYPE_RINGBUF, 0, 0, page_size, 0);
	अगर (CHECK(proto_fd == -1, "bpf_create_map", "bpf_create_map failed\n"))
		जाओ cleanup;

	err = bpf_map__set_inner_map_fd(skel->maps.ringbuf_hash, proto_fd);
	अगर (CHECK(err != 0, "bpf_map__set_inner_map_fd", "bpf_map__set_inner_map_fd failed\n"))
		जाओ cleanup;

	err = test_ringbuf_multi__load(skel);
	अगर (CHECK(err != 0, "skel_load", "skeleton load failed\n"))
		जाओ cleanup;

	बंद(proto_fd);
	proto_fd = -1;

	/* only trigger BPF program क्रम current process */
	skel->bss->pid = getpid();

	ringbuf = ring_buffer__new(bpf_map__fd(skel->maps.ringbuf1),
				   process_sample, (व्योम *)(दीर्घ)1, शून्य);
	अगर (CHECK(!ringbuf, "ringbuf_create", "failed to create ringbuf\n"))
		जाओ cleanup;

	err = ring_buffer__add(ringbuf, bpf_map__fd(skel->maps.ringbuf2),
			      process_sample, (व्योम *)(दीर्घ)2);
	अगर (CHECK(err, "ringbuf_add", "failed to add another ring\n"))
		जाओ cleanup;

	err = test_ringbuf_multi__attach(skel);
	अगर (CHECK(err, "skel_attach", "skeleton attachment failed: %d\n", err))
		जाओ cleanup;

	/* trigger few samples, some will be skipped */
	skel->bss->target_ring = 0;
	skel->bss->value = 333;
	syscall(__NR_getpgid);

	/* skipped, no ringbuf in slot 1 */
	skel->bss->target_ring = 1;
	skel->bss->value = 555;
	syscall(__NR_getpgid);

	skel->bss->target_ring = 2;
	skel->bss->value = 777;
	syscall(__NR_getpgid);

	/* poll क्रम samples, should get 2 ringbufs back */
	err = ring_buffer__poll(ringbuf, -1);
	अगर (CHECK(err != 2, "poll_res", "expected 2 records, got %d\n", err))
		जाओ cleanup;

	/* expect extra polling to वापस nothing */
	err = ring_buffer__poll(ringbuf, 0);
	अगर (CHECK(err < 0, "extra_samples", "poll result: %d\n", err))
		जाओ cleanup;

	CHECK(skel->bss->dropped != 0, "err_dropped", "exp %ld, got %ld\n",
	      0L, skel->bss->dropped);
	CHECK(skel->bss->skipped != 1, "err_skipped", "exp %ld, got %ld\n",
	      1L, skel->bss->skipped);
	CHECK(skel->bss->total != 2, "err_total", "exp %ld, got %ld\n",
	      2L, skel->bss->total);

cleanup:
	अगर (proto_fd >= 0)
		बंद(proto_fd);
	ring_buffer__मुक्त(ringbuf);
	test_ringbuf_multi__destroy(skel);
पूर्ण
