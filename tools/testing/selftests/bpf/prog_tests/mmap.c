<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश <sys/mman.h>
#समावेश "test_mmap.skel.h"

काष्ठा map_data अणु
	__u64 val[512 * 4];
पूर्ण;

अटल माप_प्रकार roundup_page(माप_प्रकार sz)
अणु
	दीर्घ page_size = sysconf(_SC_PAGE_SIZE);
	वापस (sz + page_size - 1) / page_size * page_size;
पूर्ण

व्योम test_mmap(व्योम)
अणु
	स्थिर माप_प्रकार bss_sz = roundup_page(माप(काष्ठा test_mmap__bss));
	स्थिर माप_प्रकार map_sz = roundup_page(माप(काष्ठा map_data));
	स्थिर पूर्णांक zero = 0, one = 1, two = 2, far = 1500;
	स्थिर दीर्घ page_size = sysconf(_SC_PAGE_SIZE);
	पूर्णांक err, duration = 0, i, data_map_fd, data_map_id, पंचांगp_fd, rdmap_fd;
	काष्ठा bpf_map *data_map, *bss_map;
	व्योम *bss_mmaped = शून्य, *map_mmaped = शून्य, *पंचांगp0, *पंचांगp1, *पंचांगp2;
	काष्ठा test_mmap__bss *bss_data;
	काष्ठा bpf_map_info map_info;
	__u32 map_info_sz = माप(map_info);
	काष्ठा map_data *map_data;
	काष्ठा test_mmap *skel;
	__u64 val = 0;

	skel = test_mmap__खोलो();
	अगर (CHECK(!skel, "skel_open", "skeleton open failed\n"))
		वापस;

	err = bpf_map__set_max_entries(skel->maps.rकरोnly_map, page_size);
	अगर (CHECK(err != 0, "bpf_map__set_max_entries", "bpf_map__set_max_entries failed\n"))
		जाओ cleanup;

	/* at least 4 pages of data */
	err = bpf_map__set_max_entries(skel->maps.data_map,
				       4 * (page_size / माप(u64)));
	अगर (CHECK(err != 0, "bpf_map__set_max_entries", "bpf_map__set_max_entries failed\n"))
		जाओ cleanup;

	err = test_mmap__load(skel);
	अगर (CHECK(err != 0, "skel_load", "skeleton load failed\n"))
		जाओ cleanup;

	bss_map = skel->maps.bss;
	data_map = skel->maps.data_map;
	data_map_fd = bpf_map__fd(data_map);

	rdmap_fd = bpf_map__fd(skel->maps.rकरोnly_map);
	पंचांगp1 = mmap(शून्य, page_size, PROT_READ | PROT_WRITE, MAP_SHARED, rdmap_fd, 0);
	अगर (CHECK(पंचांगp1 != MAP_FAILED, "rdonly_write_mmap", "unexpected success\n")) अणु
		munmap(पंचांगp1, page_size);
		जाओ cleanup;
	पूर्ण
	/* now द्विगुन-check अगर it's mmap()'able at all */
	पंचांगp1 = mmap(शून्य, page_size, PROT_READ, MAP_SHARED, rdmap_fd, 0);
	अगर (CHECK(पंचांगp1 == MAP_FAILED, "rdonly_read_mmap", "failed: %d\n", त्रुटि_सं))
		जाओ cleanup;

	/* get map's ID */
	स_रखो(&map_info, 0, map_info_sz);
	err = bpf_obj_get_info_by_fd(data_map_fd, &map_info, &map_info_sz);
	अगर (CHECK(err, "map_get_info", "failed %d\n", त्रुटि_सं))
		जाओ cleanup;
	data_map_id = map_info.id;

	/* mmap BSS map */
	bss_mmaped = mmap(शून्य, bss_sz, PROT_READ | PROT_WRITE, MAP_SHARED,
			  bpf_map__fd(bss_map), 0);
	अगर (CHECK(bss_mmaped == MAP_FAILED, "bss_mmap",
		  ".bss mmap failed: %d\n", त्रुटि_सं)) अणु
		bss_mmaped = शून्य;
		जाओ cleanup;
	पूर्ण
	/* map as R/W first */
	map_mmaped = mmap(शून्य, map_sz, PROT_READ | PROT_WRITE, MAP_SHARED,
			  data_map_fd, 0);
	अगर (CHECK(map_mmaped == MAP_FAILED, "data_mmap",
		  "data_map mmap failed: %d\n", त्रुटि_सं)) अणु
		map_mmaped = शून्य;
		जाओ cleanup;
	पूर्ण

	bss_data = bss_mmaped;
	map_data = map_mmaped;

	CHECK_FAIL(bss_data->in_val);
	CHECK_FAIL(bss_data->out_val);
	CHECK_FAIL(skel->bss->in_val);
	CHECK_FAIL(skel->bss->out_val);
	CHECK_FAIL(map_data->val[0]);
	CHECK_FAIL(map_data->val[1]);
	CHECK_FAIL(map_data->val[2]);
	CHECK_FAIL(map_data->val[far]);

	err = test_mmap__attach(skel);
	अगर (CHECK(err, "attach_raw_tp", "err %d\n", err))
		जाओ cleanup;

	bss_data->in_val = 123;
	val = 111;
	CHECK_FAIL(bpf_map_update_elem(data_map_fd, &zero, &val, 0));

	usleep(1);

	CHECK_FAIL(bss_data->in_val != 123);
	CHECK_FAIL(bss_data->out_val != 123);
	CHECK_FAIL(skel->bss->in_val != 123);
	CHECK_FAIL(skel->bss->out_val != 123);
	CHECK_FAIL(map_data->val[0] != 111);
	CHECK_FAIL(map_data->val[1] != 222);
	CHECK_FAIL(map_data->val[2] != 123);
	CHECK_FAIL(map_data->val[far] != 3 * 123);

	CHECK_FAIL(bpf_map_lookup_elem(data_map_fd, &zero, &val));
	CHECK_FAIL(val != 111);
	CHECK_FAIL(bpf_map_lookup_elem(data_map_fd, &one, &val));
	CHECK_FAIL(val != 222);
	CHECK_FAIL(bpf_map_lookup_elem(data_map_fd, &two, &val));
	CHECK_FAIL(val != 123);
	CHECK_FAIL(bpf_map_lookup_elem(data_map_fd, &far, &val));
	CHECK_FAIL(val != 3 * 123);

	/* data_map मुक्तze should fail due to R/W mmap() */
	err = bpf_map_मुक्तze(data_map_fd);
	अगर (CHECK(!err || त्रुटि_सं != EBUSY, "no_freeze",
		  "data_map freeze succeeded: err=%d, errno=%d\n", err, त्रुटि_सं))
		जाओ cleanup;

	err = mprotect(map_mmaped, map_sz, PROT_READ);
	अगर (CHECK(err, "mprotect_ro", "mprotect to r/o failed %d\n", त्रुटि_सं))
		जाओ cleanup;

	/* unmap R/W mapping */
	err = munmap(map_mmaped, map_sz);
	map_mmaped = शून्य;
	अगर (CHECK(err, "data_map_munmap", "data_map munmap failed: %d\n", त्रुटि_सं))
		जाओ cleanup;

	/* re-map as R/O now */
	map_mmaped = mmap(शून्य, map_sz, PROT_READ, MAP_SHARED, data_map_fd, 0);
	अगर (CHECK(map_mmaped == MAP_FAILED, "data_mmap",
		  "data_map R/O mmap failed: %d\n", त्रुटि_सं)) अणु
		map_mmaped = शून्य;
		जाओ cleanup;
	पूर्ण
	err = mprotect(map_mmaped, map_sz, PROT_WRITE);
	अगर (CHECK(!err, "mprotect_wr", "mprotect() succeeded unexpectedly!\n"))
		जाओ cleanup;
	err = mprotect(map_mmaped, map_sz, PROT_EXEC);
	अगर (CHECK(!err, "mprotect_ex", "mprotect() succeeded unexpectedly!\n"))
		जाओ cleanup;
	map_data = map_mmaped;

	/* map/unmap in a loop to test ref counting */
	क्रम (i = 0; i < 10; i++) अणु
		पूर्णांक flags = i % 2 ? PROT_READ : PROT_WRITE;
		व्योम *p;

		p = mmap(शून्य, map_sz, flags, MAP_SHARED, data_map_fd, 0);
		अगर (CHECK_FAIL(p == MAP_FAILED))
			जाओ cleanup;
		err = munmap(p, map_sz);
		अगर (CHECK_FAIL(err))
			जाओ cleanup;
	पूर्ण

	/* data_map मुक्तze should now succeed due to no R/W mapping */
	err = bpf_map_मुक्तze(data_map_fd);
	अगर (CHECK(err, "freeze", "data_map freeze failed: err=%d, errno=%d\n",
		  err, त्रुटि_सं))
		जाओ cleanup;

	/* mapping as R/W now should fail */
	पंचांगp1 = mmap(शून्य, map_sz, PROT_READ | PROT_WRITE, MAP_SHARED,
		    data_map_fd, 0);
	अगर (CHECK(पंचांगp1 != MAP_FAILED, "data_mmap", "mmap succeeded\n")) अणु
		munmap(पंचांगp1, map_sz);
		जाओ cleanup;
	पूर्ण

	bss_data->in_val = 321;
	usleep(1);
	CHECK_FAIL(bss_data->in_val != 321);
	CHECK_FAIL(bss_data->out_val != 321);
	CHECK_FAIL(skel->bss->in_val != 321);
	CHECK_FAIL(skel->bss->out_val != 321);
	CHECK_FAIL(map_data->val[0] != 111);
	CHECK_FAIL(map_data->val[1] != 222);
	CHECK_FAIL(map_data->val[2] != 321);
	CHECK_FAIL(map_data->val[far] != 3 * 321);

	/* check some more advanced mmap() manipulations */

	पंचांगp0 = mmap(शून्य, 4 * page_size, PROT_READ, MAP_SHARED | MAP_ANONYMOUS,
			  -1, 0);
	अगर (CHECK(पंचांगp0 == MAP_FAILED, "adv_mmap0", "errno %d\n", त्रुटि_सं))
		जाओ cleanup;

	/* map all but last page: pages 1-3 mapped */
	पंचांगp1 = mmap(पंचांगp0, 3 * page_size, PROT_READ, MAP_SHARED | MAP_FIXED,
			  data_map_fd, 0);
	अगर (CHECK(पंचांगp0 != पंचांगp1, "adv_mmap1", "tmp0: %p, tmp1: %p\n", पंचांगp0, पंचांगp1)) अणु
		munmap(पंचांगp0, 4 * page_size);
		जाओ cleanup;
	पूर्ण

	/* unmap second page: pages 1, 3 mapped */
	err = munmap(पंचांगp1 + page_size, page_size);
	अगर (CHECK(err, "adv_mmap2", "errno %d\n", त्रुटि_सं)) अणु
		munmap(पंचांगp1, 4 * page_size);
		जाओ cleanup;
	पूर्ण

	/* map page 2 back */
	पंचांगp2 = mmap(पंचांगp1 + page_size, page_size, PROT_READ,
		    MAP_SHARED | MAP_FIXED, data_map_fd, 0);
	अगर (CHECK(पंचांगp2 == MAP_FAILED, "adv_mmap3", "errno %d\n", त्रुटि_सं)) अणु
		munmap(पंचांगp1, page_size);
		munmap(पंचांगp1 + 2*page_size, 2 * page_size);
		जाओ cleanup;
	पूर्ण
	CHECK(पंचांगp1 + page_size != पंचांगp2, "adv_mmap4",
	      "tmp1: %p, tmp2: %p\n", पंचांगp1, पंचांगp2);

	/* re-map all 4 pages */
	पंचांगp2 = mmap(पंचांगp1, 4 * page_size, PROT_READ, MAP_SHARED | MAP_FIXED,
		    data_map_fd, 0);
	अगर (CHECK(पंचांगp2 == MAP_FAILED, "adv_mmap5", "errno %d\n", त्रुटि_सं)) अणु
		munmap(पंचांगp1, 4 * page_size); /* unmap page 1 */
		जाओ cleanup;
	पूर्ण
	CHECK(पंचांगp1 != पंचांगp2, "adv_mmap6", "tmp1: %p, tmp2: %p\n", पंचांगp1, पंचांगp2);

	map_data = पंचांगp2;
	CHECK_FAIL(bss_data->in_val != 321);
	CHECK_FAIL(bss_data->out_val != 321);
	CHECK_FAIL(skel->bss->in_val != 321);
	CHECK_FAIL(skel->bss->out_val != 321);
	CHECK_FAIL(map_data->val[0] != 111);
	CHECK_FAIL(map_data->val[1] != 222);
	CHECK_FAIL(map_data->val[2] != 321);
	CHECK_FAIL(map_data->val[far] != 3 * 321);

	munmap(पंचांगp2, 4 * page_size);

	/* map all 4 pages, but with pg_off=1 page, should fail */
	पंचांगp1 = mmap(शून्य, 4 * page_size, PROT_READ, MAP_SHARED | MAP_FIXED,
		    data_map_fd, page_size /* initial page shअगरt */);
	अगर (CHECK(पंचांगp1 != MAP_FAILED, "adv_mmap7", "unexpected success")) अणु
		munmap(पंचांगp1, 4 * page_size);
		जाओ cleanup;
	पूर्ण

	पंचांगp1 = mmap(शून्य, map_sz, PROT_READ, MAP_SHARED, data_map_fd, 0);
	अगर (CHECK(पंचांगp1 == MAP_FAILED, "last_mmap", "failed %d\n", त्रुटि_सं))
		जाओ cleanup;

	test_mmap__destroy(skel);
	skel = शून्य;
	CHECK_FAIL(munmap(bss_mmaped, bss_sz));
	bss_mmaped = शून्य;
	CHECK_FAIL(munmap(map_mmaped, map_sz));
	map_mmaped = शून्य;

	/* map should be still held by active mmap */
	पंचांगp_fd = bpf_map_get_fd_by_id(data_map_id);
	अगर (CHECK(पंचांगp_fd < 0, "get_map_by_id", "failed %d\n", त्रुटि_सं)) अणु
		munmap(पंचांगp1, map_sz);
		जाओ cleanup;
	पूर्ण
	बंद(पंचांगp_fd);

	/* this should release data map finally */
	munmap(पंचांगp1, map_sz);

	/* we need to रुको क्रम RCU grace period */
	क्रम (i = 0; i < 10000; i++) अणु
		__u32 id = data_map_id - 1;
		अगर (bpf_map_get_next_id(id, &id) || id > data_map_id)
			अवरोध;
		usleep(1);
	पूर्ण

	/* should fail to get map FD by non-existing ID */
	पंचांगp_fd = bpf_map_get_fd_by_id(data_map_id);
	अगर (CHECK(पंचांगp_fd >= 0, "get_map_by_id_after",
		  "unexpectedly succeeded %d\n", पंचांगp_fd)) अणु
		बंद(पंचांगp_fd);
		जाओ cleanup;
	पूर्ण

cleanup:
	अगर (bss_mmaped)
		CHECK_FAIL(munmap(bss_mmaped, bss_sz));
	अगर (map_mmaped)
		CHECK_FAIL(munmap(map_mmaped, map_sz));
	test_mmap__destroy(skel);
पूर्ण
