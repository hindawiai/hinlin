<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019, Oracle and/or its affiliates. All rights reserved. */

#समावेश <linux/bpf.h>
#समावेश <linux/अगर_link.h>
#समावेश <arpa/inet.h>
#समावेश <निश्चित.स>
#समावेश <त्रुटिसं.स>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <libgen.h>
#समावेश <sys/resource.h>
#समावेश <net/अगर.h>
#समावेश <sys/types.h>
#समावेश <sys/socket.h>
#समावेश <netdb.h>

#समावेश "bpf/bpf.h"
#समावेश "bpf/libbpf.h"

#समावेश "xdping.h"

अटल पूर्णांक अगरindex;
अटल __u32 xdp_flags = XDP_FLAGS_UPDATE_IF_NOEXIST;

अटल व्योम cleanup(पूर्णांक sig)
अणु
	bpf_set_link_xdp_fd(अगरindex, -1, xdp_flags);
	अगर (sig)
		निकास(1);
पूर्ण

अटल पूर्णांक get_stats(पूर्णांक fd, __u16 count, __u32 raddr)
अणु
	काष्ठा pinginfo pinginfo = अणु 0 पूर्ण;
	अक्षर inaddrbuf[INET_ADDRSTRLEN];
	काष्ठा in_addr inaddr;
	__u16 i;

	inaddr.s_addr = raddr;

	म_लिखो("\nXDP RTT data:\n");

	अगर (bpf_map_lookup_elem(fd, &raddr, &pinginfo)) अणु
		लिखो_त्रुटि("bpf_map_lookup elem");
		वापस 1;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		अगर (pinginfo.बार[i] == 0)
			अवरोध;

		म_लिखो("64 bytes from %s: icmp_seq=%d ttl=64 time=%#.5f ms\n",
		       inet_ntop(AF_INET, &inaddr, inaddrbuf,
				 माप(inaddrbuf)),
		       count + i + 1,
		       (द्विगुन)pinginfo.बार[i]/1000000);
	पूर्ण

	अगर (i < count) अणु
		ख_लिखो(मानक_त्रुटि, "Expected %d samples, got %d.\n", count, i);
		वापस 1;
	पूर्ण

	bpf_map_delete_elem(fd, &raddr);

	वापस 0;
पूर्ण

अटल व्योम show_usage(स्थिर अक्षर *prog)
अणु
	ख_लिखो(मानक_त्रुटि,
		"usage: %s [OPTS] -I interface destination\n\n"
		"OPTS:\n"
		"    -c count		Stop after sending count requests\n"
		"			(default %d, max %d)\n"
		"    -I interface	interface name\n"
		"    -N			Run in driver mode\n"
		"    -s			Server mode\n"
		"    -S			Run in skb mode\n",
		prog, XDPING_DEFAULT_COUNT, XDPING_MAX_COUNT);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	__u32 mode_flags = XDP_FLAGS_DRV_MODE | XDP_FLAGS_SKB_MODE;
	काष्ठा addrinfo *a, hपूर्णांकs = अणु .ai_family = AF_INET पूर्ण;
	काष्ठा rlimit r = अणुRLIM_अनन्त, RLIM_अनन्तपूर्ण;
	__u16 count = XDPING_DEFAULT_COUNT;
	काष्ठा pinginfo pinginfo = अणु 0 पूर्ण;
	स्थिर अक्षर *optstr = "c:I:NsS";
	काष्ठा bpf_program *मुख्य_prog;
	पूर्णांक prog_fd = -1, map_fd = -1;
	काष्ठा sockaddr_in rin;
	काष्ठा bpf_object *obj;
	काष्ठा bpf_map *map;
	अक्षर *अगरname = शून्य;
	अक्षर filename[256];
	पूर्णांक opt, ret = 1;
	__u32 raddr = 0;
	पूर्णांक server = 0;
	अक्षर cmd[256];

	जबतक ((opt = getopt(argc, argv, optstr)) != -1) अणु
		चयन (opt) अणु
		हाल 'c':
			count = म_से_प(optarg);
			अगर (count < 1 || count > XDPING_MAX_COUNT) अणु
				ख_लिखो(मानक_त्रुटि,
					"min count is 1, max count is %d\n",
					XDPING_MAX_COUNT);
				वापस 1;
			पूर्ण
			अवरोध;
		हाल 'I':
			अगरname = optarg;
			अगरindex = अगर_nametoindex(अगरname);
			अगर (!अगरindex) अणु
				ख_लिखो(मानक_त्रुटि, "Could not get interface %s\n",
					अगरname);
				वापस 1;
			पूर्ण
			अवरोध;
		हाल 'N':
			xdp_flags |= XDP_FLAGS_DRV_MODE;
			अवरोध;
		हाल 's':
			/* use server program */
			server = 1;
			अवरोध;
		हाल 'S':
			xdp_flags |= XDP_FLAGS_SKB_MODE;
			अवरोध;
		शेष:
			show_usage(basename(argv[0]));
			वापस 1;
		पूर्ण
	पूर्ण

	अगर (!अगरname) अणु
		show_usage(basename(argv[0]));
		वापस 1;
	पूर्ण
	अगर (!server && optind == argc) अणु
		show_usage(basename(argv[0]));
		वापस 1;
	पूर्ण

	अगर ((xdp_flags & mode_flags) == mode_flags) अणु
		ख_लिखो(मानक_त्रुटि, "-N or -S can be specified, not both.\n");
		show_usage(basename(argv[0]));
		वापस 1;
	पूर्ण

	अगर (!server) अणु
		/* Only supports IPv4; see hपूर्णांकs initiailization above. */
		अगर (getaddrinfo(argv[optind], शून्य, &hपूर्णांकs, &a) || !a) अणु
			ख_लिखो(मानक_त्रुटि, "Could not resolve %s\n", argv[optind]);
			वापस 1;
		पूर्ण
		स_नकल(&rin, a->ai_addr, माप(rin));
		raddr = rin.sin_addr.s_addr;
		मुक्तaddrinfo(a);
	पूर्ण

	अगर (setrlimit(RLIMIT_MEMLOCK, &r)) अणु
		लिखो_त्रुटि("setrlimit(RLIMIT_MEMLOCK)");
		वापस 1;
	पूर्ण

	snम_लिखो(filename, माप(filename), "%s_kern.o", argv[0]);

	अगर (bpf_prog_load(filename, BPF_PROG_TYPE_XDP, &obj, &prog_fd)) अणु
		ख_लिखो(मानक_त्रुटि, "load of %s failed\n", filename);
		वापस 1;
	पूर्ण

	मुख्य_prog = bpf_object__find_program_by_title(obj,
						      server ? "xdpserver" :
							       "xdpclient");
	अगर (मुख्य_prog)
		prog_fd = bpf_program__fd(मुख्य_prog);
	अगर (!मुख्य_prog || prog_fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "could not find xdping program");
		वापस 1;
	पूर्ण

	map = bpf_map__next(शून्य, obj);
	अगर (map)
		map_fd = bpf_map__fd(map);
	अगर (!map || map_fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Could not find ping map");
		जाओ करोne;
	पूर्ण

	संकेत(संक_विघ्न, cleanup);
	संकेत(संक_इति, cleanup);

	म_लिखो("Setting up XDP for %s, please wait...\n", अगरname);

	म_लिखो("XDP setup disrupts network connectivity, hit Ctrl+C to quit\n");

	अगर (bpf_set_link_xdp_fd(अगरindex, prog_fd, xdp_flags) < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Link set xdp fd failed for %s\n", अगरname);
		जाओ करोne;
	पूर्ण

	अगर (server) अणु
		बंद(prog_fd);
		बंद(map_fd);
		म_लिखो("Running server on %s; press Ctrl+C to exit...\n",
		       अगरname);
		करो अणु पूर्ण जबतक (1);
	पूर्ण

	/* Start xdping-ing from last regular ping reply, e.g. क्रम a count
	 * of 10 ICMP requests, we start xdping-ing using reply with seq number
	 * 10.  The reason the last "real" ping RTT is much higher is that
	 * the ping program sees the ICMP reply associated with the last
	 * XDP-generated packet, so ping करोesn't get a reply until XDP is करोne.
	 */
	pinginfo.seq = htons(count);
	pinginfo.count = count;

	अगर (bpf_map_update_elem(map_fd, &raddr, &pinginfo, BPF_ANY)) अणु
		ख_लिखो(मानक_त्रुटि, "could not communicate with BPF map: %s\n",
			म_त्रुटि(त्रुटि_सं));
		cleanup(0);
		जाओ करोne;
	पूर्ण

	/* We need to रुको क्रम XDP setup to complete. */
	sleep(10);

	snम_लिखो(cmd, माप(cmd), "ping -c %d -I %s %s",
		 count, अगरname, argv[optind]);

	म_लिखो("\nNormal ping RTT data\n");
	म_लिखो("[Ignore final RTT; it is distorted by XDP using the reply]\n");

	ret = प्रणाली(cmd);

	अगर (!ret)
		ret = get_stats(map_fd, count, raddr);

	cleanup(0);

करोne:
	अगर (prog_fd > 0)
		बंद(prog_fd);
	अगर (map_fd > 0)
		बंद(map_fd);

	वापस ret;
पूर्ण
