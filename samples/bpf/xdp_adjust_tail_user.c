<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 * Copyright (c) 2018 Facebook
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */
#समावेश <linux/bpf.h>
#समावेश <linux/अगर_link.h>
#समावेश <निश्चित.स>
#समावेश <त्रुटिसं.स>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <net/अगर.h>
#समावेश <sys/resource.h>
#समावेश <arpa/inet.h>
#समावेश <netinet/ether.h>
#समावेश <unistd.h>
#समावेश <समय.स>
#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>

#घोषणा STATS_INTERVAL_S 2U
#घोषणा MAX_PCKT_SIZE 600

अटल पूर्णांक अगरindex = -1;
अटल __u32 xdp_flags = XDP_FLAGS_UPDATE_IF_NOEXIST;
अटल __u32 prog_id;

अटल व्योम पूर्णांक_निकास(पूर्णांक sig)
अणु
	__u32 curr_prog_id = 0;

	अगर (अगरindex > -1) अणु
		अगर (bpf_get_link_xdp_id(अगरindex, &curr_prog_id, xdp_flags)) अणु
			म_लिखो("bpf_get_link_xdp_id failed\n");
			निकास(1);
		पूर्ण
		अगर (prog_id == curr_prog_id)
			bpf_set_link_xdp_fd(अगरindex, -1, xdp_flags);
		अन्यथा अगर (!curr_prog_id)
			म_लिखो("couldn't find a prog id on a given iface\n");
		अन्यथा
			म_लिखो("program on interface changed, not removing\n");
	पूर्ण
	निकास(0);
पूर्ण

/* simple "icmp packet too big sent" counter
 */
अटल व्योम poll_stats(अचिन्हित पूर्णांक map_fd, अचिन्हित पूर्णांक समाप्त_after_s)
अणु
	समय_प्रकार started_at = समय(शून्य);
	__u64 value = 0;
	पूर्णांक key = 0;


	जबतक (!समाप्त_after_s || समय(शून्य) - started_at <= समाप्त_after_s) अणु
		sleep(STATS_INTERVAL_S);

		निश्चित(bpf_map_lookup_elem(map_fd, &key, &value) == 0);

		म_लिखो("icmp \"packet too big\" sent: %10llu pkts\n", value);
	पूर्ण
पूर्ण

अटल व्योम usage(स्थिर अक्षर *cmd)
अणु
	म_लिखो("Start a XDP prog which send ICMP \"packet too big\" \n"
		"messages if ingress packet is bigger then MAX_SIZE bytes\n");
	म_लिखो("Usage: %s [...]\n", cmd);
	म_लिखो("    -i <ifname|ifindex> Interface\n");
	म_लिखो("    -T <stop-after-X-seconds> Default: 0 (forever)\n");
	म_लिखो("    -P <MAX_PCKT_SIZE> Default: %u\n", MAX_PCKT_SIZE);
	म_लिखो("    -S use skb-mode\n");
	म_लिखो("    -N enforce native mode\n");
	म_लिखो("    -F force loading prog\n");
	म_लिखो("    -h Display this help\n");
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा bpf_prog_load_attr prog_load_attr = अणु
		.prog_type	= BPF_PROG_TYPE_XDP,
	पूर्ण;
	अचिन्हित अक्षर opt_flags[256] = अणुपूर्ण;
	स्थिर अक्षर *optstr = "i:T:P:SNFh";
	काष्ठा bpf_prog_info info = अणुपूर्ण;
	__u32 info_len = माप(info);
	अचिन्हित पूर्णांक समाप्त_after_s = 0;
	पूर्णांक i, prog_fd, map_fd, opt;
	काष्ठा bpf_object *obj;
	__u32 max_pckt_size = 0;
	__u32 key = 0;
	अक्षर filename[256];
	पूर्णांक err;

	क्रम (i = 0; i < म_माप(optstr); i++)
		अगर (optstr[i] != 'h' && 'a' <= optstr[i] && optstr[i] <= 'z')
			opt_flags[(अचिन्हित अक्षर)optstr[i]] = 1;

	जबतक ((opt = getopt(argc, argv, optstr)) != -1) अणु

		चयन (opt) अणु
		हाल 'i':
			अगरindex = अगर_nametoindex(optarg);
			अगर (!अगरindex)
				अगरindex = म_से_प(optarg);
			अवरोध;
		हाल 'T':
			समाप्त_after_s = म_से_प(optarg);
			अवरोध;
		हाल 'P':
			max_pckt_size = म_से_प(optarg);
			अवरोध;
		हाल 'S':
			xdp_flags |= XDP_FLAGS_SKB_MODE;
			अवरोध;
		हाल 'N':
			/* शेष, set below */
			अवरोध;
		हाल 'F':
			xdp_flags &= ~XDP_FLAGS_UPDATE_IF_NOEXIST;
			अवरोध;
		शेष:
			usage(argv[0]);
			वापस 1;
		पूर्ण
		opt_flags[opt] = 0;
	पूर्ण

	अगर (!(xdp_flags & XDP_FLAGS_SKB_MODE))
		xdp_flags |= XDP_FLAGS_DRV_MODE;

	क्रम (i = 0; i < म_माप(optstr); i++) अणु
		अगर (opt_flags[(अचिन्हित पूर्णांक)optstr[i]]) अणु
			ख_लिखो(मानक_त्रुटि, "Missing argument -%c\n", optstr[i]);
			usage(argv[0]);
			वापस 1;
		पूर्ण
	पूर्ण

	अगर (!अगरindex) अणु
		ख_लिखो(मानक_त्रुटि, "Invalid ifname\n");
		वापस 1;
	पूर्ण

	snम_लिखो(filename, माप(filename), "%s_kern.o", argv[0]);
	prog_load_attr.file = filename;

	अगर (bpf_prog_load_xattr(&prog_load_attr, &obj, &prog_fd))
		वापस 1;

	/* अटल global var 'max_pcktsz' is accessible from .data section */
	अगर (max_pckt_size) अणु
		map_fd = bpf_object__find_map_fd_by_name(obj, "xdp_adju.data");
		अगर (map_fd < 0) अणु
			म_लिखो("finding a max_pcktsz map in obj file failed\n");
			वापस 1;
		पूर्ण
		bpf_map_update_elem(map_fd, &key, &max_pckt_size, BPF_ANY);
	पूर्ण

	/* fetch icmpcnt map */
	map_fd = bpf_object__find_map_fd_by_name(obj, "icmpcnt");
	अगर (map_fd < 0) अणु
		म_लिखो("finding a icmpcnt map in obj file failed\n");
		वापस 1;
	पूर्ण

	संकेत(संक_विघ्न, पूर्णांक_निकास);
	संकेत(संक_इति, पूर्णांक_निकास);

	अगर (bpf_set_link_xdp_fd(अगरindex, prog_fd, xdp_flags) < 0) अणु
		म_लिखो("link set xdp fd failed\n");
		वापस 1;
	पूर्ण

	err = bpf_obj_get_info_by_fd(prog_fd, &info, &info_len);
	अगर (err) अणु
		म_लिखो("can't get prog info - %s\n", म_त्रुटि(त्रुटि_सं));
		वापस 1;
	पूर्ण
	prog_id = info.id;

	poll_stats(map_fd, समाप्त_after_s);
	पूर्णांक_निकास(0);

	वापस 0;
पूर्ण
