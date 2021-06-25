<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 Facebook  */
#समावेश <linux/compiler.h>
#समावेश <linux/err.h>

#समावेश <sys/resource.h>
#समावेश <sys/socket.h>
#समावेश <sys/types.h>
#समावेश <linux/btf.h>
#समावेश <unistd.h>
#समावेश <संकेत.स>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <pthपढ़ो.h>

#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>

#समावेश <test_btf.h>
#समावेश <test_maps.h>

अटल काष्ठा bpf_create_map_attr xattr = अणु
	.name = "sk_storage_map",
	.map_type = BPF_MAP_TYPE_SK_STORAGE,
	.map_flags = BPF_F_NO_PREALLOC,
	.max_entries = 0,
	.key_size = 4,
	.value_size = 8,
	.btf_key_type_id = 1,
	.btf_value_type_id = 3,
	.btf_fd = -1,
पूर्ण;

अटल अचिन्हित पूर्णांक nr_sk_thपढ़ोs_करोne;
अटल अचिन्हित पूर्णांक nr_sk_thपढ़ोs_err;
अटल अचिन्हित पूर्णांक nr_sk_per_thपढ़ो = 4096;
अटल अचिन्हित पूर्णांक nr_sk_thपढ़ोs = 4;
अटल पूर्णांक sk_storage_map = -1;
अटल अचिन्हित पूर्णांक stop;
अटल पूर्णांक runसमय_s = 5;

अटल bool is_stopped(व्योम)
अणु
	वापस READ_ONCE(stop);
पूर्ण

अटल अचिन्हित पूर्णांक thपढ़ोs_err(व्योम)
अणु
	वापस READ_ONCE(nr_sk_thपढ़ोs_err);
पूर्ण

अटल व्योम notअगरy_thपढ़ो_err(व्योम)
अणु
	__sync_add_and_fetch(&nr_sk_thपढ़ोs_err, 1);
पूर्ण

अटल bool रुको_क्रम_thपढ़ोs_err(व्योम)
अणु
	जबतक (!is_stopped() && !thपढ़ोs_err())
		usleep(500);

	वापस !is_stopped();
पूर्ण

अटल अचिन्हित पूर्णांक thपढ़ोs_करोne(व्योम)
अणु
	वापस READ_ONCE(nr_sk_thपढ़ोs_करोne);
पूर्ण

अटल व्योम notअगरy_thपढ़ो_करोne(व्योम)
अणु
	__sync_add_and_fetch(&nr_sk_thपढ़ोs_करोne, 1);
पूर्ण

अटल व्योम notअगरy_thपढ़ो_reकरो(व्योम)
अणु
	__sync_sub_and_fetch(&nr_sk_thपढ़ोs_करोne, 1);
पूर्ण

अटल bool रुको_क्रम_thपढ़ोs_करोne(व्योम)
अणु
	जबतक (thपढ़ोs_करोne() != nr_sk_thपढ़ोs && !is_stopped() &&
	       !thपढ़ोs_err())
		usleep(50);

	वापस !is_stopped() && !thपढ़ोs_err();
पूर्ण

अटल bool रुको_क्रम_thपढ़ोs_reकरो(व्योम)
अणु
	जबतक (thपढ़ोs_करोne() && !is_stopped() && !thपढ़ोs_err())
		usleep(50);

	वापस !is_stopped() && !thपढ़ोs_err();
पूर्ण

अटल bool रुको_क्रम_map(व्योम)
अणु
	जबतक (READ_ONCE(sk_storage_map) == -1 && !is_stopped())
		usleep(50);

	वापस !is_stopped();
पूर्ण

अटल bool रुको_क्रम_map_बंद(व्योम)
अणु
	जबतक (READ_ONCE(sk_storage_map) != -1 && !is_stopped())
		;

	वापस !is_stopped();
पूर्ण

अटल पूर्णांक load_btf(व्योम)
अणु
	स्थिर अक्षर btf_str_sec[] = "\0bpf_spin_lock\0val\0cnt\0l";
	__u32 btf_raw_types[] = अणु
		/* पूर्णांक */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),  /* [1] */
		/* काष्ठा bpf_spin_lock */                      /* [2] */
		BTF_TYPE_ENC(1, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 1), 4),
		BTF_MEMBER_ENC(15, 1, 0), /* पूर्णांक val; */
		/* काष्ठा val */                                /* [3] */
		BTF_TYPE_ENC(15, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 2), 8),
		BTF_MEMBER_ENC(19, 1, 0), /* पूर्णांक cnt; */
		BTF_MEMBER_ENC(23, 2, 32),/* काष्ठा bpf_spin_lock l; */
	पूर्ण;
	काष्ठा btf_header btf_hdr = अणु
		.magic = BTF_MAGIC,
		.version = BTF_VERSION,
		.hdr_len = माप(काष्ठा btf_header),
		.type_len = माप(btf_raw_types),
		.str_off = माप(btf_raw_types),
		.str_len = माप(btf_str_sec),
	पूर्ण;
	__u8 raw_btf[माप(काष्ठा btf_header) + माप(btf_raw_types) +
		     माप(btf_str_sec)];

	स_नकल(raw_btf, &btf_hdr, माप(btf_hdr));
	स_नकल(raw_btf + माप(btf_hdr), btf_raw_types, माप(btf_raw_types));
	स_नकल(raw_btf + माप(btf_hdr) + माप(btf_raw_types),
	       btf_str_sec, माप(btf_str_sec));

	वापस bpf_load_btf(raw_btf, माप(raw_btf), 0, 0, 0);
पूर्ण

अटल पूर्णांक create_sk_storage_map(व्योम)
अणु
	पूर्णांक btf_fd, map_fd;

	btf_fd = load_btf();
	CHECK(btf_fd == -1, "bpf_load_btf", "btf_fd:%d errno:%d\n",
	      btf_fd, त्रुटि_सं);
	xattr.btf_fd = btf_fd;

	map_fd = bpf_create_map_xattr(&xattr);
	xattr.btf_fd = -1;
	बंद(btf_fd);
	CHECK(map_fd == -1,
	      "bpf_create_map_xattr()", "errno:%d\n", त्रुटि_सं);

	वापस map_fd;
पूर्ण

अटल व्योम *insert_बंद_thपढ़ो(व्योम *arg)
अणु
	काष्ठा अणु
		पूर्णांक cnt;
		पूर्णांक lock;
	पूर्ण value = अणु .cnt = 0xeB9F, .lock = 0, पूर्ण;
	पूर्णांक i, map_fd, err, *sk_fds;

	sk_fds = दो_स्मृति(माप(*sk_fds) * nr_sk_per_thपढ़ो);
	अगर (!sk_fds) अणु
		notअगरy_thपढ़ो_err();
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	क्रम (i = 0; i < nr_sk_per_thपढ़ो; i++)
		sk_fds[i] = -1;

	जबतक (!is_stopped()) अणु
		अगर (!रुको_क्रम_map())
			जाओ बंद_all;

		map_fd = READ_ONCE(sk_storage_map);
		क्रम (i = 0; i < nr_sk_per_thपढ़ो && !is_stopped(); i++) अणु
			sk_fds[i] = socket(AF_INET6, SOCK_STREAM, 0);
			अगर (sk_fds[i] == -1) अणु
				err = -त्रुटि_सं;
				ख_लिखो(मानक_त्रुटि, "socket(): errno:%d\n", त्रुटि_सं);
				जाओ errout;
			पूर्ण
			err = bpf_map_update_elem(map_fd, &sk_fds[i], &value,
						  BPF_NOEXIST);
			अगर (err) अणु
				err = -त्रुटि_सं;
				ख_लिखो(मानक_त्रुटि,
					"bpf_map_update_elem(): errno:%d\n",
					त्रुटि_सं);
				जाओ errout;
			पूर्ण
		पूर्ण

		notअगरy_thपढ़ो_करोne();
		रुको_क्रम_map_बंद();

बंद_all:
		क्रम (i = 0; i < nr_sk_per_thपढ़ो; i++) अणु
			बंद(sk_fds[i]);
			sk_fds[i] = -1;
		पूर्ण

		notअगरy_thपढ़ो_reकरो();
	पूर्ण

	मुक्त(sk_fds);
	वापस शून्य;

errout:
	क्रम (i = 0; i < nr_sk_per_thपढ़ो && sk_fds[i] != -1; i++)
		बंद(sk_fds[i]);
	मुक्त(sk_fds);
	notअगरy_thपढ़ो_err();
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक करो_sk_storage_map_stress_मुक्त(व्योम)
अणु
	पूर्णांक i, map_fd = -1, err = 0, nr_thपढ़ोs_created = 0;
	pthपढ़ो_t *sk_thपढ़ो_ids;
	व्योम *thपढ़ो_ret;

	sk_thपढ़ो_ids = दो_स्मृति(माप(pthपढ़ो_t) * nr_sk_thपढ़ोs);
	अगर (!sk_thपढ़ो_ids) अणु
		ख_लिखो(मानक_त्रुटि, "malloc(sk_threads): NULL\n");
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < nr_sk_thपढ़ोs; i++) अणु
		err = pthपढ़ो_create(&sk_thपढ़ो_ids[i], शून्य,
				     insert_बंद_thपढ़ो, शून्य);
		अगर (err) अणु
			err = -त्रुटि_सं;
			जाओ करोne;
		पूर्ण
		nr_thपढ़ोs_created++;
	पूर्ण

	जबतक (!is_stopped()) अणु
		map_fd = create_sk_storage_map();
		WRITE_ONCE(sk_storage_map, map_fd);

		अगर (!रुको_क्रम_thपढ़ोs_करोne())
			अवरोध;

		WRITE_ONCE(sk_storage_map, -1);
		बंद(map_fd);
		map_fd = -1;

		अगर (!रुको_क्रम_thपढ़ोs_reकरो())
			अवरोध;
	पूर्ण

करोne:
	WRITE_ONCE(stop, 1);
	क्रम (i = 0; i < nr_thपढ़ोs_created; i++) अणु
		pthपढ़ो_join(sk_thपढ़ो_ids[i], &thपढ़ो_ret);
		अगर (IS_ERR(thपढ़ो_ret) && !err) अणु
			err = PTR_ERR(thपढ़ो_ret);
			ख_लिखो(मानक_त्रुटि, "threads#%u: err:%d\n", i, err);
		पूर्ण
	पूर्ण
	मुक्त(sk_thपढ़ो_ids);

	अगर (map_fd != -1)
		बंद(map_fd);

	वापस err;
पूर्ण

अटल व्योम *update_thपढ़ो(व्योम *arg)
अणु
	काष्ठा अणु
		पूर्णांक cnt;
		पूर्णांक lock;
	पूर्ण value = अणु .cnt = 0xeB9F, .lock = 0, पूर्ण;
	पूर्णांक map_fd = READ_ONCE(sk_storage_map);
	पूर्णांक sk_fd = *(पूर्णांक *)arg;
	पूर्णांक err = 0; /* Suppress compiler false alarm */

	जबतक (!is_stopped()) अणु
		err = bpf_map_update_elem(map_fd, &sk_fd, &value, 0);
		अगर (err && त्रुटि_सं != EAGAIN) अणु
			err = -त्रुटि_सं;
			ख_लिखो(मानक_त्रुटि, "bpf_map_update_elem: %d %d\n",
				err, त्रुटि_सं);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!is_stopped()) अणु
		notअगरy_thपढ़ो_err();
		वापस ERR_PTR(err);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम *delete_thपढ़ो(व्योम *arg)
अणु
	पूर्णांक map_fd = READ_ONCE(sk_storage_map);
	पूर्णांक sk_fd = *(पूर्णांक *)arg;
	पूर्णांक err = 0; /* Suppress compiler false alarm */

	जबतक (!is_stopped()) अणु
		err = bpf_map_delete_elem(map_fd, &sk_fd);
		अगर (err && त्रुटि_सं != ENOENT) अणु
			err = -त्रुटि_सं;
			ख_लिखो(मानक_त्रुटि, "bpf_map_delete_elem: %d %d\n",
				err, त्रुटि_सं);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!is_stopped()) अणु
		notअगरy_thपढ़ो_err();
		वापस ERR_PTR(err);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक करो_sk_storage_map_stress_change(व्योम)
अणु
	पूर्णांक i, sk_fd, map_fd = -1, err = 0, nr_thपढ़ोs_created = 0;
	pthपढ़ो_t *sk_thपढ़ो_ids;
	व्योम *thपढ़ो_ret;

	sk_thपढ़ो_ids = दो_स्मृति(माप(pthपढ़ो_t) * nr_sk_thपढ़ोs);
	अगर (!sk_thपढ़ो_ids) अणु
		ख_लिखो(मानक_त्रुटि, "malloc(sk_threads): NULL\n");
		वापस -ENOMEM;
	पूर्ण

	sk_fd = socket(AF_INET6, SOCK_STREAM, 0);
	अगर (sk_fd == -1) अणु
		err = -त्रुटि_सं;
		जाओ करोne;
	पूर्ण

	map_fd = create_sk_storage_map();
	WRITE_ONCE(sk_storage_map, map_fd);

	क्रम (i = 0; i < nr_sk_thपढ़ोs; i++) अणु
		अगर (i & 0x1)
			err = pthपढ़ो_create(&sk_thपढ़ो_ids[i], शून्य,
					     update_thपढ़ो, &sk_fd);
		अन्यथा
			err = pthपढ़ो_create(&sk_thपढ़ो_ids[i], शून्य,
					     delete_thपढ़ो, &sk_fd);
		अगर (err) अणु
			err = -त्रुटि_सं;
			जाओ करोne;
		पूर्ण
		nr_thपढ़ोs_created++;
	पूर्ण

	रुको_क्रम_thपढ़ोs_err();

करोne:
	WRITE_ONCE(stop, 1);
	क्रम (i = 0; i < nr_thपढ़ोs_created; i++) अणु
		pthपढ़ो_join(sk_thपढ़ो_ids[i], &thपढ़ो_ret);
		अगर (IS_ERR(thपढ़ो_ret) && !err) अणु
			err = PTR_ERR(thपढ़ो_ret);
			ख_लिखो(मानक_त्रुटि, "threads#%u: err:%d\n", i, err);
		पूर्ण
	पूर्ण
	मुक्त(sk_thपढ़ो_ids);

	अगर (sk_fd != -1)
		बंद(sk_fd);
	बंद(map_fd);

	वापस err;
पूर्ण

अटल व्योम stop_handler(पूर्णांक signum)
अणु
	अगर (signum != SIGALRM)
		म_लिखो("stopping...\n");
	WRITE_ONCE(stop, 1);
पूर्ण

#घोषणा BPF_SK_STORAGE_MAP_TEST_NR_THREADS "BPF_SK_STORAGE_MAP_TEST_NR_THREADS"
#घोषणा BPF_SK_STORAGE_MAP_TEST_SK_PER_THREAD "BPF_SK_STORAGE_MAP_TEST_SK_PER_THREAD"
#घोषणा BPF_SK_STORAGE_MAP_TEST_RUNTIME_S "BPF_SK_STORAGE_MAP_TEST_RUNTIME_S"
#घोषणा BPF_SK_STORAGE_MAP_TEST_NAME "BPF_SK_STORAGE_MAP_TEST_NAME"

अटल व्योम test_sk_storage_map_stress_मुक्त(व्योम)
अणु
	काष्ठा rlimit rlim_old, rlim_new = अणुपूर्ण;
	पूर्णांक err;

	getrlimit(RLIMIT_NOखाता, &rlim_old);

	संकेत(संक_इति, stop_handler);
	संकेत(संक_विघ्न, stop_handler);
	अगर (runसमय_s > 0) अणु
		संकेत(SIGALRM, stop_handler);
		alarm(runसमय_s);
	पूर्ण

	अगर (rlim_old.rlim_cur < nr_sk_thपढ़ोs * nr_sk_per_thपढ़ो) अणु
		rlim_new.rlim_cur = nr_sk_thपढ़ोs * nr_sk_per_thपढ़ो + 128;
		rlim_new.rlim_max = rlim_new.rlim_cur + 128;
		err = setrlimit(RLIMIT_NOखाता, &rlim_new);
		CHECK(err, "setrlimit(RLIMIT_NOFILE)", "rlim_new:%lu errno:%d",
		      rlim_new.rlim_cur, त्रुटि_सं);
	पूर्ण

	err = करो_sk_storage_map_stress_मुक्त();

	संकेत(संक_इति, संक_पूर्व);
	संकेत(संक_विघ्न, संक_पूर्व);
	अगर (runसमय_s > 0) अणु
		संकेत(SIGALRM, संक_पूर्व);
		alarm(0);
	पूर्ण

	अगर (rlim_new.rlim_cur)
		setrlimit(RLIMIT_NOखाता, &rlim_old);

	CHECK(err, "test_sk_storage_map_stress_free", "err:%d\n", err);
पूर्ण

अटल व्योम test_sk_storage_map_stress_change(व्योम)
अणु
	पूर्णांक err;

	संकेत(संक_इति, stop_handler);
	संकेत(संक_विघ्न, stop_handler);
	अगर (runसमय_s > 0) अणु
		संकेत(SIGALRM, stop_handler);
		alarm(runसमय_s);
	पूर्ण

	err = करो_sk_storage_map_stress_change();

	संकेत(संक_इति, संक_पूर्व);
	संकेत(संक_विघ्न, संक_पूर्व);
	अगर (runसमय_s > 0) अणु
		संकेत(SIGALRM, संक_पूर्व);
		alarm(0);
	पूर्ण

	CHECK(err, "test_sk_storage_map_stress_change", "err:%d\n", err);
पूर्ण

अटल व्योम test_sk_storage_map_basic(व्योम)
अणु
	काष्ठा अणु
		पूर्णांक cnt;
		पूर्णांक lock;
	पूर्ण value = अणु .cnt = 0xeB9f, .lock = 0, पूर्ण, lookup_value;
	काष्ठा bpf_create_map_attr bad_xattr;
	पूर्णांक btf_fd, map_fd, sk_fd, err;

	btf_fd = load_btf();
	CHECK(btf_fd == -1, "bpf_load_btf", "btf_fd:%d errno:%d\n",
	      btf_fd, त्रुटि_सं);
	xattr.btf_fd = btf_fd;

	sk_fd = socket(AF_INET6, SOCK_STREAM, 0);
	CHECK(sk_fd == -1, "socket()", "sk_fd:%d errno:%d\n",
	      sk_fd, त्रुटि_सं);

	map_fd = bpf_create_map_xattr(&xattr);
	CHECK(map_fd == -1, "bpf_create_map_xattr(good_xattr)",
	      "map_fd:%d errno:%d\n", map_fd, त्रुटि_सं);

	/* Add new elem */
	स_नकल(&lookup_value, &value, माप(value));
	err = bpf_map_update_elem(map_fd, &sk_fd, &value,
				  BPF_NOEXIST | BPF_F_LOCK);
	CHECK(err, "bpf_map_update_elem(BPF_NOEXIST|BPF_F_LOCK)",
	      "err:%d errno:%d\n", err, त्रुटि_सं);
	err = bpf_map_lookup_elem_flags(map_fd, &sk_fd, &lookup_value,
					BPF_F_LOCK);
	CHECK(err || lookup_value.cnt != value.cnt,
	      "bpf_map_lookup_elem_flags(BPF_F_LOCK)",
	      "err:%d errno:%d cnt:%x(%x)\n",
	      err, त्रुटि_सं, lookup_value.cnt, value.cnt);

	/* Bump the cnt and update with BPF_EXIST | BPF_F_LOCK */
	value.cnt += 1;
	err = bpf_map_update_elem(map_fd, &sk_fd, &value,
				  BPF_EXIST | BPF_F_LOCK);
	CHECK(err, "bpf_map_update_elem(BPF_EXIST|BPF_F_LOCK)",
	      "err:%d errno:%d\n", err, त्रुटि_सं);
	err = bpf_map_lookup_elem_flags(map_fd, &sk_fd, &lookup_value,
					BPF_F_LOCK);
	CHECK(err || lookup_value.cnt != value.cnt,
	      "bpf_map_lookup_elem_flags(BPF_F_LOCK)",
	      "err:%d errno:%d cnt:%x(%x)\n",
	      err, त्रुटि_सं, lookup_value.cnt, value.cnt);

	/* Bump the cnt and update with BPF_EXIST */
	value.cnt += 1;
	err = bpf_map_update_elem(map_fd, &sk_fd, &value, BPF_EXIST);
	CHECK(err, "bpf_map_update_elem(BPF_EXIST)",
	      "err:%d errno:%d\n", err, त्रुटि_सं);
	err = bpf_map_lookup_elem_flags(map_fd, &sk_fd, &lookup_value,
					BPF_F_LOCK);
	CHECK(err || lookup_value.cnt != value.cnt,
	      "bpf_map_lookup_elem_flags(BPF_F_LOCK)",
	      "err:%d errno:%d cnt:%x(%x)\n",
	      err, त्रुटि_सं, lookup_value.cnt, value.cnt);

	/* Update with BPF_NOEXIST */
	value.cnt += 1;
	err = bpf_map_update_elem(map_fd, &sk_fd, &value,
				  BPF_NOEXIST | BPF_F_LOCK);
	CHECK(!err || त्रुटि_सं != EEXIST,
	      "bpf_map_update_elem(BPF_NOEXIST|BPF_F_LOCK)",
	      "err:%d errno:%d\n", err, त्रुटि_सं);
	err = bpf_map_update_elem(map_fd, &sk_fd, &value, BPF_NOEXIST);
	CHECK(!err || त्रुटि_सं != EEXIST, "bpf_map_update_elem(BPF_NOEXIST)",
	      "err:%d errno:%d\n", err, त्रुटि_सं);
	value.cnt -= 1;
	err = bpf_map_lookup_elem_flags(map_fd, &sk_fd, &lookup_value,
					BPF_F_LOCK);
	CHECK(err || lookup_value.cnt != value.cnt,
	      "bpf_map_lookup_elem_flags(BPF_F_LOCK)",
	      "err:%d errno:%d cnt:%x(%x)\n",
	      err, त्रुटि_सं, lookup_value.cnt, value.cnt);

	/* Bump the cnt again and update with map_flags == 0 */
	value.cnt += 1;
	err = bpf_map_update_elem(map_fd, &sk_fd, &value, 0);
	CHECK(err, "bpf_map_update_elem()", "err:%d errno:%d\n",
	      err, त्रुटि_सं);
	err = bpf_map_lookup_elem_flags(map_fd, &sk_fd, &lookup_value,
					BPF_F_LOCK);
	CHECK(err || lookup_value.cnt != value.cnt,
	      "bpf_map_lookup_elem_flags(BPF_F_LOCK)",
	      "err:%d errno:%d cnt:%x(%x)\n",
	      err, त्रुटि_सं, lookup_value.cnt, value.cnt);

	/* Test delete elem */
	err = bpf_map_delete_elem(map_fd, &sk_fd);
	CHECK(err, "bpf_map_delete_elem()", "err:%d errno:%d\n",
	      err, त्रुटि_सं);
	err = bpf_map_lookup_elem_flags(map_fd, &sk_fd, &lookup_value,
					BPF_F_LOCK);
	CHECK(!err || त्रुटि_सं != ENOENT,
	      "bpf_map_lookup_elem_flags(BPF_F_LOCK)",
	      "err:%d errno:%d\n", err, त्रुटि_सं);
	err = bpf_map_delete_elem(map_fd, &sk_fd);
	CHECK(!err || त्रुटि_सं != ENOENT, "bpf_map_delete_elem()",
	      "err:%d errno:%d\n", err, त्रुटि_सं);

	स_नकल(&bad_xattr, &xattr, माप(xattr));
	bad_xattr.btf_key_type_id = 0;
	err = bpf_create_map_xattr(&bad_xattr);
	CHECK(!err || त्रुटि_सं != EINVAL, "bap_create_map_xattr(bad_xattr)",
	      "err:%d errno:%d\n", err, त्रुटि_सं);

	स_नकल(&bad_xattr, &xattr, माप(xattr));
	bad_xattr.btf_key_type_id = 3;
	err = bpf_create_map_xattr(&bad_xattr);
	CHECK(!err || त्रुटि_सं != EINVAL, "bap_create_map_xattr(bad_xattr)",
	      "err:%d errno:%d\n", err, त्रुटि_सं);

	स_नकल(&bad_xattr, &xattr, माप(xattr));
	bad_xattr.max_entries = 1;
	err = bpf_create_map_xattr(&bad_xattr);
	CHECK(!err || त्रुटि_सं != EINVAL, "bap_create_map_xattr(bad_xattr)",
	      "err:%d errno:%d\n", err, त्रुटि_सं);

	स_नकल(&bad_xattr, &xattr, माप(xattr));
	bad_xattr.map_flags = 0;
	err = bpf_create_map_xattr(&bad_xattr);
	CHECK(!err || त्रुटि_सं != EINVAL, "bap_create_map_xattr(bad_xattr)",
	      "err:%d errno:%d\n", err, त्रुटि_सं);

	xattr.btf_fd = -1;
	बंद(btf_fd);
	बंद(map_fd);
	बंद(sk_fd);
पूर्ण

व्योम test_sk_storage_map(व्योम)
अणु
	स्थिर अक्षर *test_name, *env_opt;
	bool test_ran = false;

	test_name = दो_पर्या(BPF_SK_STORAGE_MAP_TEST_NAME);

	env_opt = दो_पर्या(BPF_SK_STORAGE_MAP_TEST_NR_THREADS);
	अगर (env_opt)
		nr_sk_thपढ़ोs = म_से_प(env_opt);

	env_opt = दो_पर्या(BPF_SK_STORAGE_MAP_TEST_SK_PER_THREAD);
	अगर (env_opt)
		nr_sk_per_thपढ़ो = म_से_प(env_opt);

	env_opt = दो_पर्या(BPF_SK_STORAGE_MAP_TEST_RUNTIME_S);
	अगर (env_opt)
		runसमय_s = म_से_प(env_opt);

	अगर (!test_name || !म_भेद(test_name, "basic")) अणु
		test_sk_storage_map_basic();
		test_ran = true;
	पूर्ण
	अगर (!test_name || !म_भेद(test_name, "stress_free")) अणु
		test_sk_storage_map_stress_मुक्त();
		test_ran = true;
	पूर्ण
	अगर (!test_name || !म_भेद(test_name, "stress_change")) अणु
		test_sk_storage_map_stress_change();
		test_ran = true;
	पूर्ण

	अगर (test_ran)
		म_लिखो("%s:PASS\n", __func__);
	अन्यथा
		CHECK(1, "Invalid test_name", "%s\n", test_name);
पूर्ण
