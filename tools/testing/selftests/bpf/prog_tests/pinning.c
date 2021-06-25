<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <unistd.h>
#समावेश <test_progs.h>

__u32 get_map_id(काष्ठा bpf_object *obj, स्थिर अक्षर *name)
अणु
	काष्ठा bpf_map_info map_info = अणुपूर्ण;
	__u32 map_info_len, duration = 0;
	काष्ठा bpf_map *map;
	पूर्णांक err;

	map_info_len = माप(map_info);

	map = bpf_object__find_map_by_name(obj, name);
	अगर (CHECK(!map, "find map", "NULL map"))
		वापस 0;

	err = bpf_obj_get_info_by_fd(bpf_map__fd(map),
				     &map_info, &map_info_len);
	CHECK(err, "get map info", "err %d errno %d", err, त्रुटि_सं);
	वापस map_info.id;
पूर्ण

व्योम test_pinning(व्योम)
अणु
	स्थिर अक्षर *file_invalid = "./test_pinning_invalid.o";
	स्थिर अक्षर *custpinpath = "/sys/fs/bpf/custom/pinmap";
	स्थिर अक्षर *nopinpath = "/sys/fs/bpf/nopinmap";
	स्थिर अक्षर *nopinpath2 = "/sys/fs/bpf/nopinmap2";
	स्थिर अक्षर *custpath = "/sys/fs/bpf/custom";
	स्थिर अक्षर *pinpath = "/sys/fs/bpf/pinmap";
	स्थिर अक्षर *file = "./test_pinning.o";
	__u32 map_id, map_id2, duration = 0;
	काष्ठा stat statbuf = अणुपूर्ण;
	काष्ठा bpf_object *obj;
	काष्ठा bpf_map *map;
	पूर्णांक err, map_fd;
	DECLARE_LIBBPF_OPTS(bpf_object_खोलो_opts, opts,
		.pin_root_path = custpath,
	);

	/* check that खोलोing fails with invalid pinning value in map def */
	obj = bpf_object__खोलो_file(file_invalid, शून्य);
	err = libbpf_get_error(obj);
	अगर (CHECK(err != -EINVAL, "invalid open", "err %d errno %d\n", err, त्रुटि_सं)) अणु
		obj = शून्य;
		जाओ out;
	पूर्ण

	/* खोलो the valid object file  */
	obj = bpf_object__खोलो_file(file, शून्य);
	err = libbpf_get_error(obj);
	अगर (CHECK(err, "default open", "err %d errno %d\n", err, त्रुटि_सं)) अणु
		obj = शून्य;
		जाओ out;
	पूर्ण

	err = bpf_object__load(obj);
	अगर (CHECK(err, "default load", "err %d errno %d\n", err, त्रुटि_सं))
		जाओ out;

	/* check that pinmap was pinned */
	err = stat(pinpath, &statbuf);
	अगर (CHECK(err, "stat pinpath", "err %d errno %d\n", err, त्रुटि_सं))
		जाओ out;

	/* check that nopinmap was *not* pinned */
	err = stat(nopinpath, &statbuf);
	अगर (CHECK(!err || त्रुटि_सं != ENOENT, "stat nopinpath",
		  "err %d errno %d\n", err, त्रुटि_सं))
		जाओ out;

	/* check that nopinmap2 was *not* pinned */
	err = stat(nopinpath2, &statbuf);
	अगर (CHECK(!err || त्रुटि_सं != ENOENT, "stat nopinpath2",
		  "err %d errno %d\n", err, त्रुटि_सं))
		जाओ out;

	map_id = get_map_id(obj, "pinmap");
	अगर (!map_id)
		जाओ out;

	bpf_object__बंद(obj);

	obj = bpf_object__खोलो_file(file, शून्य);
	अगर (CHECK_FAIL(libbpf_get_error(obj))) अणु
		obj = शून्य;
		जाओ out;
	पूर्ण

	err = bpf_object__load(obj);
	अगर (CHECK(err, "default load", "err %d errno %d\n", err, त्रुटि_सं))
		जाओ out;

	/* check that same map ID was reused क्रम second load */
	map_id2 = get_map_id(obj, "pinmap");
	अगर (CHECK(map_id != map_id2, "check reuse",
		  "err %d errno %d id %d id2 %d\n", err, त्रुटि_सं, map_id, map_id2))
		जाओ out;

	/* should be no-op to re-pin same map */
	map = bpf_object__find_map_by_name(obj, "pinmap");
	अगर (CHECK(!map, "find map", "NULL map"))
		जाओ out;

	err = bpf_map__pin(map, शून्य);
	अगर (CHECK(err, "re-pin map", "err %d errno %d\n", err, त्रुटि_सं))
		जाओ out;

	/* but error to pin at dअगरferent location */
	err = bpf_map__pin(map, "/sys/fs/bpf/other");
	अगर (CHECK(!err, "pin map different", "err %d errno %d\n", err, त्रुटि_सं))
		जाओ out;

	/* unpin maps with a pin_path set */
	err = bpf_object__unpin_maps(obj, शून्य);
	अगर (CHECK(err, "unpin maps", "err %d errno %d\n", err, त्रुटि_सं))
		जाओ out;

	/* and re-pin them... */
	err = bpf_object__pin_maps(obj, शून्य);
	अगर (CHECK(err, "pin maps", "err %d errno %d\n", err, त्रुटि_सं))
		जाओ out;

	/* set pinning path of other map and re-pin all */
	map = bpf_object__find_map_by_name(obj, "nopinmap");
	अगर (CHECK(!map, "find map", "NULL map"))
		जाओ out;

	err = bpf_map__set_pin_path(map, custpinpath);
	अगर (CHECK(err, "set pin path", "err %d errno %d\n", err, त्रुटि_सं))
		जाओ out;

	/* should only pin the one unpinned map */
	err = bpf_object__pin_maps(obj, शून्य);
	अगर (CHECK(err, "pin maps", "err %d errno %d\n", err, त्रुटि_सं))
		जाओ out;

	/* check that nopinmap was pinned at the custom path */
	err = stat(custpinpath, &statbuf);
	अगर (CHECK(err, "stat custpinpath", "err %d errno %d\n", err, त्रुटि_सं))
		जाओ out;

	/* हटाओ the custom pin path to re-test it with स्वतः-pinning below */
	err = unlink(custpinpath);
	अगर (CHECK(err, "unlink custpinpath", "err %d errno %d\n", err, त्रुटि_सं))
		जाओ out;

	err = सूची_हटाओ(custpath);
	अगर (CHECK(err, "rmdir custpindir", "err %d errno %d\n", err, त्रुटि_सं))
		जाओ out;

	bpf_object__बंद(obj);

	/* खोलो the valid object file again */
	obj = bpf_object__खोलो_file(file, शून्य);
	err = libbpf_get_error(obj);
	अगर (CHECK(err, "default open", "err %d errno %d\n", err, त्रुटि_सं)) अणु
		obj = शून्य;
		जाओ out;
	पूर्ण

	/* set pin paths so that nopinmap2 will attempt to reuse the map at
	 * pinpath (which will fail), but not beक्रमe pinmap has alपढ़ोy been
	 * reused
	 */
	bpf_object__क्रम_each_map(map, obj) अणु
		अगर (!म_भेद(bpf_map__name(map), "nopinmap"))
			err = bpf_map__set_pin_path(map, nopinpath2);
		अन्यथा अगर (!म_भेद(bpf_map__name(map), "nopinmap2"))
			err = bpf_map__set_pin_path(map, pinpath);
		अन्यथा
			जारी;

		अगर (CHECK(err, "set pin path", "err %d errno %d\n", err, त्रुटि_सं))
			जाओ out;
	पूर्ण

	/* should fail because of map parameter mismatch */
	err = bpf_object__load(obj);
	अगर (CHECK(err != -EINVAL, "param mismatch load", "err %d errno %d\n", err, त्रुटि_सं))
		जाओ out;

	/* nopinmap2 should have been pinned and cleaned up again */
	err = stat(nopinpath2, &statbuf);
	अगर (CHECK(!err || त्रुटि_सं != ENOENT, "stat nopinpath2",
		  "err %d errno %d\n", err, त्रुटि_सं))
		जाओ out;

	/* pinmap should still be there */
	err = stat(pinpath, &statbuf);
	अगर (CHECK(err, "stat pinpath", "err %d errno %d\n", err, त्रुटि_सं))
		जाओ out;

	bpf_object__बंद(obj);

	/* test स्वतः-pinning at custom path with खोलो opt */
	obj = bpf_object__खोलो_file(file, &opts);
	अगर (CHECK_FAIL(libbpf_get_error(obj))) अणु
		obj = शून्य;
		जाओ out;
	पूर्ण

	err = bpf_object__load(obj);
	अगर (CHECK(err, "custom load", "err %d errno %d\n", err, त्रुटि_सं))
		जाओ out;

	/* check that pinmap was pinned at the custom path */
	err = stat(custpinpath, &statbuf);
	अगर (CHECK(err, "stat custpinpath", "err %d errno %d\n", err, त्रुटि_सं))
		जाओ out;

	/* हटाओ the custom pin path to re-test it with reuse fd below */
	err = unlink(custpinpath);
	अगर (CHECK(err, "unlink custpinpath", "err %d errno %d\n", err, त्रुटि_सं))
		जाओ out;

	err = सूची_हटाओ(custpath);
	अगर (CHECK(err, "rmdir custpindir", "err %d errno %d\n", err, त्रुटि_सं))
		जाओ out;

	bpf_object__बंद(obj);

	/* test pinning at custom path with reuse fd */
	obj = bpf_object__खोलो_file(file, शून्य);
	err = libbpf_get_error(obj);
	अगर (CHECK(err, "default open", "err %d errno %d\n", err, त्रुटि_सं)) अणु
		obj = शून्य;
		जाओ out;
	पूर्ण

	map_fd = bpf_create_map(BPF_MAP_TYPE_ARRAY, माप(__u32),
				माप(__u64), 1, 0);
	अगर (CHECK(map_fd < 0, "create pinmap manually", "fd %d\n", map_fd))
		जाओ out;

	map = bpf_object__find_map_by_name(obj, "pinmap");
	अगर (CHECK(!map, "find map", "NULL map"))
		जाओ बंद_map_fd;

	err = bpf_map__reuse_fd(map, map_fd);
	अगर (CHECK(err, "reuse pinmap fd", "err %d errno %d\n", err, त्रुटि_सं))
		जाओ बंद_map_fd;

	err = bpf_map__set_pin_path(map, custpinpath);
	अगर (CHECK(err, "set pin path", "err %d errno %d\n", err, त्रुटि_सं))
		जाओ बंद_map_fd;

	err = bpf_object__load(obj);
	अगर (CHECK(err, "custom load", "err %d errno %d\n", err, त्रुटि_सं))
		जाओ बंद_map_fd;

	/* check that pinmap was pinned at the custom path */
	err = stat(custpinpath, &statbuf);
	अगर (CHECK(err, "stat custpinpath", "err %d errno %d\n", err, त्रुटि_सं))
		जाओ बंद_map_fd;

बंद_map_fd:
	बंद(map_fd);
out:
	unlink(pinpath);
	unlink(nopinpath);
	unlink(nopinpath2);
	unlink(custpinpath);
	सूची_हटाओ(custpath);
	अगर (obj)
		bpf_object__बंद(obj);
पूर्ण
