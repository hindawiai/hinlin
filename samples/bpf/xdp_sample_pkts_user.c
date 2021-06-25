<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <linux/perf_event.h>
#समावेश <linux/bpf.h>
#समावेश <net/अगर.h>
#समावेश <त्रुटिसं.स>
#समावेश <निश्चित.स>
#समावेश <sys/sysinfo.h>
#समावेश <sys/ioctl.h>
#समावेश <संकेत.स>
#समावेश <bpf/libbpf.h>
#समावेश <bpf/bpf.h>
#समावेश <sys/resource.h>
#समावेश <libgen.h>
#समावेश <linux/अगर_link.h>

#समावेश "perf-sys.h"

अटल पूर्णांक अगर_idx;
अटल अक्षर *अगर_name;
अटल __u32 xdp_flags = XDP_FLAGS_UPDATE_IF_NOEXIST;
अटल __u32 prog_id;
अटल काष्ठा perf_buffer *pb = शून्य;

अटल पूर्णांक करो_attach(पूर्णांक idx, पूर्णांक fd, स्थिर अक्षर *name)
अणु
	काष्ठा bpf_prog_info info = अणुपूर्ण;
	__u32 info_len = माप(info);
	पूर्णांक err;

	err = bpf_set_link_xdp_fd(idx, fd, xdp_flags);
	अगर (err < 0) अणु
		म_लिखो("ERROR: failed to attach program to %s\n", name);
		वापस err;
	पूर्ण

	err = bpf_obj_get_info_by_fd(fd, &info, &info_len);
	अगर (err) अणु
		म_लिखो("can't get prog info - %s\n", म_त्रुटि(त्रुटि_सं));
		वापस err;
	पूर्ण
	prog_id = info.id;

	वापस err;
पूर्ण

अटल पूर्णांक करो_detach(पूर्णांक idx, स्थिर अक्षर *name)
अणु
	__u32 curr_prog_id = 0;
	पूर्णांक err = 0;

	err = bpf_get_link_xdp_id(idx, &curr_prog_id, xdp_flags);
	अगर (err) अणु
		म_लिखो("bpf_get_link_xdp_id failed\n");
		वापस err;
	पूर्ण
	अगर (prog_id == curr_prog_id) अणु
		err = bpf_set_link_xdp_fd(idx, -1, xdp_flags);
		अगर (err < 0)
			म_लिखो("ERROR: failed to detach prog from %s\n", name);
	पूर्ण अन्यथा अगर (!curr_prog_id) अणु
		म_लिखो("couldn't find a prog id on a %s\n", name);
	पूर्ण अन्यथा अणु
		म_लिखो("program on interface changed, not removing\n");
	पूर्ण

	वापस err;
पूर्ण

#घोषणा SAMPLE_SIZE 64

अटल व्योम prपूर्णांक_bpf_output(व्योम *ctx, पूर्णांक cpu, व्योम *data, __u32 size)
अणु
	काष्ठा अणु
		__u16 cookie;
		__u16 pkt_len;
		__u8  pkt_data[SAMPLE_SIZE];
	पूर्ण __packed *e = data;
	पूर्णांक i;

	अगर (e->cookie != 0xdead) अणु
		म_लिखो("BUG cookie %x sized %d\n", e->cookie, size);
		वापस;
	पूर्ण

	म_लिखो("Pkt len: %-5d bytes. Ethernet hdr: ", e->pkt_len);
	क्रम (i = 0; i < 14 && i < e->pkt_len; i++)
		म_लिखो("%02x ", e->pkt_data[i]);
	म_लिखो("\n");
पूर्ण

अटल व्योम sig_handler(पूर्णांक signo)
अणु
	करो_detach(अगर_idx, अगर_name);
	perf_buffer__मुक्त(pb);
	निकास(0);
पूर्ण

अटल व्योम usage(स्थिर अक्षर *prog)
अणु
	ख_लिखो(मानक_त्रुटि,
		"%s: %s [OPTS] <ifname|ifindex>\n\n"
		"OPTS:\n"
		"    -F    force loading prog\n",
		__func__, prog);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा bpf_prog_load_attr prog_load_attr = अणु
		.prog_type	= BPF_PROG_TYPE_XDP,
	पूर्ण;
	काष्ठा perf_buffer_opts pb_opts = अणुपूर्ण;
	स्थिर अक्षर *optstr = "FS";
	पूर्णांक prog_fd, map_fd, opt;
	काष्ठा bpf_object *obj;
	काष्ठा bpf_map *map;
	अक्षर filename[256];
	पूर्णांक ret, err;

	जबतक ((opt = getopt(argc, argv, optstr)) != -1) अणु
		चयन (opt) अणु
		हाल 'F':
			xdp_flags &= ~XDP_FLAGS_UPDATE_IF_NOEXIST;
			अवरोध;
		हाल 'S':
			xdp_flags |= XDP_FLAGS_SKB_MODE;
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

	snम_लिखो(filename, माप(filename), "%s_kern.o", argv[0]);
	prog_load_attr.file = filename;

	अगर (bpf_prog_load_xattr(&prog_load_attr, &obj, &prog_fd))
		वापस 1;

	अगर (!prog_fd) अणु
		म_लिखो("bpf_prog_load_xattr: %s\n", म_त्रुटि(त्रुटि_सं));
		वापस 1;
	पूर्ण

	map = bpf_map__next(शून्य, obj);
	अगर (!map) अणु
		म_लिखो("finding a map in obj file failed\n");
		वापस 1;
	पूर्ण
	map_fd = bpf_map__fd(map);

	अगर_idx = अगर_nametoindex(argv[optind]);
	अगर (!अगर_idx)
		अगर_idx = म_से_अदीर्घ(argv[optind], शून्य, 0);

	अगर (!अगर_idx) अणु
		ख_लिखो(मानक_त्रुटि, "Invalid ifname\n");
		वापस 1;
	पूर्ण
	अगर_name = argv[optind];
	err = करो_attach(अगर_idx, prog_fd, अगर_name);
	अगर (err)
		वापस err;

	अगर (संकेत(संक_विघ्न, sig_handler) ||
	    संकेत(SIGHUP, sig_handler) ||
	    संकेत(संक_इति, sig_handler)) अणु
		लिखो_त्रुटि("signal");
		वापस 1;
	पूर्ण

	pb_opts.sample_cb = prपूर्णांक_bpf_output;
	pb = perf_buffer__new(map_fd, 8, &pb_opts);
	err = libbpf_get_error(pb);
	अगर (err) अणु
		लिखो_त्रुटि("perf_buffer setup failed");
		वापस 1;
	पूर्ण

	जबतक ((ret = perf_buffer__poll(pb, 1000)) >= 0) अणु
	पूर्ण

	समाप्त(0, संक_विघ्न);
	वापस ret;
पूर्ण
