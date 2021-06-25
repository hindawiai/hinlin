<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2016 Facebook
 */
#समावेश <linux/unistd.h>
#समावेश <linux/bpf.h>

#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>

#समावेश <bpf/bpf.h>

अटल व्योम usage(व्योम)
अणु
	म_लिखो("Usage: tc_l2_ipip_redirect [...]\n");
	म_लिखो("       -U <file>   Update an already pinned BPF array\n");
	म_लिखो("       -i <ifindex> Interface index\n");
	म_लिखो("       -h          Display this help\n");
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	स्थिर अक्षर *pinned_file = शून्य;
	पूर्णांक अगरindex = -1;
	पूर्णांक array_key = 0;
	पूर्णांक array_fd = -1;
	पूर्णांक ret = -1;
	पूर्णांक opt;

	जबतक ((opt = getopt(argc, argv, "F:U:i:")) != -1) अणु
		चयन (opt) अणु
		/* General args */
		हाल 'U':
			pinned_file = optarg;
			अवरोध;
		हाल 'i':
			अगरindex = म_से_प(optarg);
			अवरोध;
		शेष:
			usage();
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (अगरindex < 0 || !pinned_file) अणु
		usage();
		जाओ out;
	पूर्ण

	array_fd = bpf_obj_get(pinned_file);
	अगर (array_fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "bpf_obj_get(%s): %s(%d)\n",
			pinned_file, म_त्रुटि(त्रुटि_सं), त्रुटि_सं);
		जाओ out;
	पूर्ण

	/* bpf_tunnel_key.remote_ipv4 expects host byte orders */
	ret = bpf_map_update_elem(array_fd, &array_key, &अगरindex, 0);
	अगर (ret) अणु
		लिखो_त्रुटि("bpf_map_update_elem");
		जाओ out;
	पूर्ण

out:
	अगर (array_fd != -1)
		बंद(array_fd);
	वापस ret;
पूर्ण
