<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2016 PLUMgrid
 */
#समावेश <linux/bpf.h>
#समावेश <linux/अगर_link.h>
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

#समावेश "bpf_util.h"
#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>

अटल पूर्णांक अगरindex;
अटल __u32 xdp_flags = XDP_FLAGS_UPDATE_IF_NOEXIST;
अटल __u32 prog_id;

अटल व्योम पूर्णांक_निकास(पूर्णांक sig)
अणु
	__u32 curr_prog_id = 0;

	अगर (bpf_get_link_xdp_id(अगरindex, &curr_prog_id, xdp_flags)) अणु
		म_लिखो("bpf_get_link_xdp_id failed\n");
		निकास(1);
	पूर्ण
	अगर (prog_id == curr_prog_id)
		bpf_set_link_xdp_fd(अगरindex, -1, xdp_flags);
	अन्यथा अगर (!curr_prog_id)
		म_लिखो("couldn't find a prog id on a given interface\n");
	अन्यथा
		म_लिखो("program on interface changed, not removing\n");
	निकास(0);
पूर्ण

/* simple per-protocol drop counter
 */
अटल व्योम poll_stats(पूर्णांक map_fd, पूर्णांक पूर्णांकerval)
अणु
	अचिन्हित पूर्णांक nr_cpus = bpf_num_possible_cpus();
	__u64 values[nr_cpus], prev[UINT8_MAX] = अणु 0 पूर्ण;
	पूर्णांक i;

	जबतक (1) अणु
		__u32 key = UINT32_MAX;

		sleep(पूर्णांकerval);

		जबतक (bpf_map_get_next_key(map_fd, &key, &key) != -1) अणु
			__u64 sum = 0;

			निश्चित(bpf_map_lookup_elem(map_fd, &key, values) == 0);
			क्रम (i = 0; i < nr_cpus; i++)
				sum += values[i];
			अगर (sum > prev[key])
				म_लिखो("proto %u: %10llu pkt/s\n",
				       key, (sum - prev[key]) / पूर्णांकerval);
			prev[key] = sum;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम usage(स्थिर अक्षर *prog)
अणु
	ख_लिखो(मानक_त्रुटि,
		"usage: %s [OPTS] IFACE\n\n"
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
	काष्ठा bpf_prog_info info = अणुपूर्ण;
	__u32 info_len = माप(info);
	स्थिर अक्षर *optstr = "FSN";
	पूर्णांक prog_fd, map_fd, opt;
	काष्ठा bpf_object *obj;
	काष्ठा bpf_map *map;
	अक्षर filename[256];
	पूर्णांक err;

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
		usage(basename(argv[0]));
		वापस 1;
	पूर्ण

	अगरindex = अगर_nametoindex(argv[optind]);
	अगर (!अगरindex) अणु
		लिखो_त्रुटि("if_nametoindex");
		वापस 1;
	पूर्ण

	snम_लिखो(filename, माप(filename), "%s_kern.o", argv[0]);
	prog_load_attr.file = filename;

	अगर (bpf_prog_load_xattr(&prog_load_attr, &obj, &prog_fd))
		वापस 1;

	map = bpf_map__next(शून्य, obj);
	अगर (!map) अणु
		म_लिखो("finding a map in obj file failed\n");
		वापस 1;
	पूर्ण
	map_fd = bpf_map__fd(map);

	अगर (!prog_fd) अणु
		म_लिखो("bpf_prog_load_xattr: %s\n", म_त्रुटि(त्रुटि_सं));
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
		वापस err;
	पूर्ण
	prog_id = info.id;

	poll_stats(map_fd, 2);

	वापस 0;
पूर्ण
