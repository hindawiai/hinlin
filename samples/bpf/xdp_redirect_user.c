<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2016 John Fastabend <john.r.fastabend@पूर्णांकel.com>
 */
#समावेश <linux/bpf.h>
#समावेश <linux/अगर_link.h>
#समावेश <निश्चित.स>
#समावेश <त्रुटिसं.स>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <net/अगर.h>
#समावेश <unistd.h>
#समावेश <libgen.h>
#समावेश <sys/resource.h>

#समावेश "bpf_util.h"
#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>

अटल पूर्णांक अगरindex_in;
अटल पूर्णांक अगरindex_out;
अटल bool अगरindex_out_xdp_dummy_attached = true;
अटल __u32 prog_id;
अटल __u32 dummy_prog_id;

अटल __u32 xdp_flags = XDP_FLAGS_UPDATE_IF_NOEXIST;
अटल पूर्णांक rxcnt_map_fd;

अटल व्योम पूर्णांक_निकास(पूर्णांक sig)
अणु
	__u32 curr_prog_id = 0;

	अगर (bpf_get_link_xdp_id(अगरindex_in, &curr_prog_id, xdp_flags)) अणु
		म_लिखो("bpf_get_link_xdp_id failed\n");
		निकास(1);
	पूर्ण
	अगर (prog_id == curr_prog_id)
		bpf_set_link_xdp_fd(अगरindex_in, -1, xdp_flags);
	अन्यथा अगर (!curr_prog_id)
		म_लिखो("couldn't find a prog id on iface IN\n");
	अन्यथा
		म_लिखो("program on iface IN changed, not removing\n");

	अगर (अगरindex_out_xdp_dummy_attached) अणु
		curr_prog_id = 0;
		अगर (bpf_get_link_xdp_id(अगरindex_out, &curr_prog_id,
					xdp_flags)) अणु
			म_लिखो("bpf_get_link_xdp_id failed\n");
			निकास(1);
		पूर्ण
		अगर (dummy_prog_id == curr_prog_id)
			bpf_set_link_xdp_fd(अगरindex_out, -1, xdp_flags);
		अन्यथा अगर (!curr_prog_id)
			म_लिखो("couldn't find a prog id on iface OUT\n");
		अन्यथा
			म_लिखो("program on iface OUT changed, not removing\n");
	पूर्ण
	निकास(0);
पूर्ण

अटल व्योम poll_stats(पूर्णांक पूर्णांकerval, पूर्णांक अगरindex)
अणु
	अचिन्हित पूर्णांक nr_cpus = bpf_num_possible_cpus();
	__u64 values[nr_cpus], prev[nr_cpus];

	स_रखो(prev, 0, माप(prev));

	जबतक (1) अणु
		__u64 sum = 0;
		__u32 key = 0;
		पूर्णांक i;

		sleep(पूर्णांकerval);
		निश्चित(bpf_map_lookup_elem(rxcnt_map_fd, &key, values) == 0);
		क्रम (i = 0; i < nr_cpus; i++)
			sum += (values[i] - prev[i]);
		अगर (sum)
			म_लिखो("ifindex %i: %10llu pkt/s\n",
			       अगरindex, sum / पूर्णांकerval);
		स_नकल(prev, values, माप(values));
	पूर्ण
पूर्ण

अटल व्योम usage(स्थिर अक्षर *prog)
अणु
	ख_लिखो(मानक_त्रुटि,
		"usage: %s [OPTS] <IFNAME|IFINDEX>_IN <IFNAME|IFINDEX>_OUT\n\n"
		"OPTS:\n"
		"    -S    use skb-mode\n"
		"    -N    enforce native mode\n"
		"    -F    force loading prog\n",
		prog);
पूर्ण


पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा bpf_prog_load_attr prog_load_attr = अणु
		.prog_type	= BPF_PROG_TYPE_XDP,
	पूर्ण;
	काष्ठा bpf_program *prog, *dummy_prog;
	पूर्णांक prog_fd, tx_port_map_fd, opt;
	काष्ठा bpf_prog_info info = अणुपूर्ण;
	__u32 info_len = माप(info);
	स्थिर अक्षर *optstr = "FSN";
	काष्ठा bpf_object *obj;
	अक्षर filename[256];
	पूर्णांक dummy_prog_fd;
	पूर्णांक ret, key = 0;

	जबतक ((opt = getopt(argc, argv, optstr)) != -1) अणु
		चयन (opt) अणु
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
			usage(basename(argv[0]));
			वापस 1;
		पूर्ण
	पूर्ण

	अगर (!(xdp_flags & XDP_FLAGS_SKB_MODE))
		xdp_flags |= XDP_FLAGS_DRV_MODE;

	अगर (optind == argc) अणु
		म_लिखो("usage: %s <IFNAME|IFINDEX>_IN <IFNAME|IFINDEX>_OUT\n", argv[0]);
		वापस 1;
	पूर्ण

	अगरindex_in = अगर_nametoindex(argv[optind]);
	अगर (!अगरindex_in)
		अगरindex_in = म_से_अदीर्घ(argv[optind], शून्य, 0);

	अगरindex_out = अगर_nametoindex(argv[optind + 1]);
	अगर (!अगरindex_out)
		अगरindex_out = म_से_अदीर्घ(argv[optind + 1], शून्य, 0);

	म_लिखो("input: %d output: %d\n", अगरindex_in, अगरindex_out);

	snम_लिखो(filename, माप(filename), "%s_kern.o", argv[0]);
	prog_load_attr.file = filename;

	अगर (bpf_prog_load_xattr(&prog_load_attr, &obj, &prog_fd))
		वापस 1;

	prog = bpf_program__next(शून्य, obj);
	dummy_prog = bpf_program__next(prog, obj);
	अगर (!prog || !dummy_prog) अणु
		म_लिखो("finding a prog in obj file failed\n");
		वापस 1;
	पूर्ण
	/* bpf_prog_load_xattr gives us the poपूर्णांकer to first prog's fd,
	 * so we're missing only the fd क्रम dummy prog
	 */
	dummy_prog_fd = bpf_program__fd(dummy_prog);
	अगर (prog_fd < 0 || dummy_prog_fd < 0) अणु
		म_लिखो("bpf_prog_load_xattr: %s\n", म_त्रुटि(त्रुटि_सं));
		वापस 1;
	पूर्ण

	tx_port_map_fd = bpf_object__find_map_fd_by_name(obj, "tx_port");
	rxcnt_map_fd = bpf_object__find_map_fd_by_name(obj, "rxcnt");
	अगर (tx_port_map_fd < 0 || rxcnt_map_fd < 0) अणु
		म_लिखो("bpf_object__find_map_fd_by_name failed\n");
		वापस 1;
	पूर्ण

	अगर (bpf_set_link_xdp_fd(अगरindex_in, prog_fd, xdp_flags) < 0) अणु
		म_लिखो("ERROR: link set xdp fd failed on %d\n", अगरindex_in);
		वापस 1;
	पूर्ण

	ret = bpf_obj_get_info_by_fd(prog_fd, &info, &info_len);
	अगर (ret) अणु
		म_लिखो("can't get prog info - %s\n", म_त्रुटि(त्रुटि_सं));
		वापस ret;
	पूर्ण
	prog_id = info.id;

	/* Loading dummy XDP prog on out-device */
	अगर (bpf_set_link_xdp_fd(अगरindex_out, dummy_prog_fd,
			    (xdp_flags | XDP_FLAGS_UPDATE_IF_NOEXIST)) < 0) अणु
		म_लिखो("WARN: link set xdp fd failed on %d\n", अगरindex_out);
		अगरindex_out_xdp_dummy_attached = false;
	पूर्ण

	स_रखो(&info, 0, माप(info));
	ret = bpf_obj_get_info_by_fd(dummy_prog_fd, &info, &info_len);
	अगर (ret) अणु
		म_लिखो("can't get prog info - %s\n", म_त्रुटि(त्रुटि_सं));
		वापस ret;
	पूर्ण
	dummy_prog_id = info.id;

	संकेत(संक_विघ्न, पूर्णांक_निकास);
	संकेत(संक_इति, पूर्णांक_निकास);

	/* bpf redirect port */
	ret = bpf_map_update_elem(tx_port_map_fd, &key, &अगरindex_out, 0);
	अगर (ret) अणु
		लिखो_त्रुटि("bpf_update_elem");
		जाओ out;
	पूर्ण

	poll_stats(2, अगरindex_out);

out:
	वापस 0;
पूर्ण
