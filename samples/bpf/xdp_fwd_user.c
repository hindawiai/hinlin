<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2017-18 David Ahern <dsahern@gmail.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License क्रम more details.
 */

#समावेश <linux/bpf.h>
#समावेश <linux/अगर_link.h>
#समावेश <linux/सीमा.स>
#समावेश <net/अगर.h>
#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <fcntl.h>
#समावेश <libgen.h>

#समावेश <bpf/libbpf.h>
#समावेश <bpf/bpf.h>

अटल __u32 xdp_flags = XDP_FLAGS_UPDATE_IF_NOEXIST;

अटल पूर्णांक करो_attach(पूर्णांक idx, पूर्णांक prog_fd, पूर्णांक map_fd, स्थिर अक्षर *name)
अणु
	पूर्णांक err;

	err = bpf_set_link_xdp_fd(idx, prog_fd, xdp_flags);
	अगर (err < 0) अणु
		म_लिखो("ERROR: failed to attach program to %s\n", name);
		वापस err;
	पूर्ण

	/* Adding अगरindex as a possible egress TX port */
	err = bpf_map_update_elem(map_fd, &idx, &idx, 0);
	अगर (err)
		म_लिखो("ERROR: failed using device %s as TX-port\n", name);

	वापस err;
पूर्ण

अटल पूर्णांक करो_detach(पूर्णांक idx, स्थिर अक्षर *name)
अणु
	पूर्णांक err;

	err = bpf_set_link_xdp_fd(idx, -1, xdp_flags);
	अगर (err < 0)
		म_लिखो("ERROR: failed to detach program from %s\n", name);

	/* TODO: Remember to cleanup map, when adding use of shared map
	 *  bpf_map_delete_elem((map_fd, &idx);
	 */
	वापस err;
पूर्ण

अटल व्योम usage(स्थिर अक्षर *prog)
अणु
	ख_लिखो(मानक_त्रुटि,
		"usage: %s [OPTS] interface-list\n"
		"\nOPTS:\n"
		"    -d    detach program\n"
		"    -D    direct table lookups (skip fib rules)\n",
		prog);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा bpf_prog_load_attr prog_load_attr = अणु
		.prog_type	= BPF_PROG_TYPE_XDP,
	पूर्ण;
	स्थिर अक्षर *prog_name = "xdp_fwd";
	काष्ठा bpf_program *prog;
	पूर्णांक prog_fd, map_fd = -1;
	अक्षर filename[PATH_MAX];
	काष्ठा bpf_object *obj;
	पूर्णांक opt, i, idx, err;
	पूर्णांक attach = 1;
	पूर्णांक ret = 0;

	जबतक ((opt = getopt(argc, argv, ":dDSF")) != -1) अणु
		चयन (opt) अणु
		हाल 'd':
			attach = 0;
			अवरोध;
		हाल 'S':
			xdp_flags |= XDP_FLAGS_SKB_MODE;
			अवरोध;
		हाल 'F':
			xdp_flags &= ~XDP_FLAGS_UPDATE_IF_NOEXIST;
			अवरोध;
		हाल 'D':
			prog_name = "xdp_fwd_direct";
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

	अगर (attach) अणु
		snम_लिखो(filename, माप(filename), "%s_kern.o", argv[0]);
		prog_load_attr.file = filename;

		अगर (access(filename, O_RDONLY) < 0) अणु
			म_लिखो("error accessing file %s: %s\n",
				filename, म_त्रुटि(त्रुटि_सं));
			वापस 1;
		पूर्ण

		err = bpf_prog_load_xattr(&prog_load_attr, &obj, &prog_fd);
		अगर (err) अणु
			म_लिखो("Does kernel support devmap lookup?\n");
			/* If not, the error message will be:
			 *  "cannot pass map_type 14 into func bpf_map_lookup_elem#1"
			 */
			वापस 1;
		पूर्ण

		prog = bpf_object__find_program_by_title(obj, prog_name);
		prog_fd = bpf_program__fd(prog);
		अगर (prog_fd < 0) अणु
			म_लिखो("program not found: %s\n", म_त्रुटि(prog_fd));
			वापस 1;
		पूर्ण
		map_fd = bpf_map__fd(bpf_object__find_map_by_name(obj,
							"xdp_tx_ports"));
		अगर (map_fd < 0) अणु
			म_लिखो("map not found: %s\n", म_त्रुटि(map_fd));
			वापस 1;
		पूर्ण
	पूर्ण

	क्रम (i = optind; i < argc; ++i) अणु
		idx = अगर_nametoindex(argv[i]);
		अगर (!idx)
			idx = म_से_अदीर्घ(argv[i], शून्य, 0);

		अगर (!idx) अणु
			ख_लिखो(मानक_त्रुटि, "Invalid arg\n");
			वापस 1;
		पूर्ण
		अगर (!attach) अणु
			err = करो_detach(idx, argv[i]);
			अगर (err)
				ret = err;
		पूर्ण अन्यथा अणु
			err = करो_attach(idx, prog_fd, map_fd, argv[i]);
			अगर (err)
				ret = err;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
