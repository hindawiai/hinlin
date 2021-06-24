<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <fcntl.h>
#समावेश <sys/resource.h>
#समावेश <bpf/libbpf.h>
#समावेश <bpf/bpf.h>
#समावेश <sys/mount.h>
#समावेश "iterators.skel.h"
#समावेश "bpf_preload_common.h"

पूर्णांक to_kernel = -1;
पूर्णांक from_kernel = 0;

अटल पूर्णांक send_link_to_kernel(काष्ठा bpf_link *link, स्थिर अक्षर *link_name)
अणु
	काष्ठा bpf_preload_info obj = अणुपूर्ण;
	काष्ठा bpf_link_info info = अणुपूर्ण;
	__u32 info_len = माप(info);
	पूर्णांक err;

	err = bpf_obj_get_info_by_fd(bpf_link__fd(link), &info, &info_len);
	अगर (err)
		वापस err;
	obj.link_id = info.id;
	अगर (म_माप(link_name) >= माप(obj.link_name))
		वापस -E2BIG;
	म_नकल(obj.link_name, link_name);
	अगर (ग_लिखो(to_kernel, &obj, माप(obj)) != माप(obj))
		वापस -EPIPE;
	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा rlimit rlim = अणु RLIM_अनन्त, RLIM_अनन्त पूर्ण;
	काष्ठा iterators_bpf *skel;
	पूर्णांक err, magic;
	पूर्णांक debug_fd;

	debug_fd = खोलो("/dev/console", O_WRONLY | O_NOCTTY | O_CLOEXEC);
	अगर (debug_fd < 0)
		वापस 1;
	to_kernel = dup(1);
	बंद(1);
	dup(debug_fd);
	/* now मानक_निवेश and मानक_त्रुटि poपूर्णांक to /dev/console */

	पढ़ो(from_kernel, &magic, माप(magic));
	अगर (magic != BPF_PRELOAD_START) अणु
		म_लिखो("bad start magic %d\n", magic);
		वापस 1;
	पूर्ण
	setrlimit(RLIMIT_MEMLOCK, &rlim);
	/* libbpf खोलोs BPF object and loads it पूर्णांकo the kernel */
	skel = iterators_bpf__खोलो_and_load();
	अगर (!skel) अणु
		/* iterators.skel.h is little endian.
		 * libbpf करोesn't support स्वतःmatic little->big conversion
		 * of BPF bytecode yet.
		 * The program load will fail in such हाल.
		 */
		म_लिखो("Failed load could be due to wrong endianness\n");
		वापस 1;
	पूर्ण
	err = iterators_bpf__attach(skel);
	अगर (err)
		जाओ cleanup;

	/* send two bpf_link IDs with names to the kernel */
	err = send_link_to_kernel(skel->links.dump_bpf_map, "maps.debug");
	अगर (err)
		जाओ cleanup;
	err = send_link_to_kernel(skel->links.dump_bpf_prog, "progs.debug");
	अगर (err)
		जाओ cleanup;

	/* The kernel will proceed with pinnging the links in bpffs.
	 * UMD will रुको on पढ़ो from pipe.
	 */
	पढ़ो(from_kernel, &magic, माप(magic));
	अगर (magic != BPF_PRELOAD_END) अणु
		म_लिखो("bad final magic %d\n", magic);
		err = -EINVAL;
	पूर्ण
cleanup:
	iterators_bpf__destroy(skel);

	वापस err != 0;
पूर्ण
