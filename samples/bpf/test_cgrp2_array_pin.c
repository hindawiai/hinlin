<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2016 Facebook
 */
#समावेश <linux/unistd.h>
#समावेश <linux/bpf.h>

#समावेश <मानकपन.स>
#समावेश <मानक_निवेशt.h>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>

#समावेश <bpf/bpf.h>

अटल व्योम usage(व्योम)
अणु
	म_लिखो("Usage: test_cgrp2_array_pin [...]\n");
	म_लिखो("       -F <file>   File to pin an BPF cgroup array\n");
	म_लिखो("       -U <file>   Update an already pinned BPF cgroup array\n");
	म_लिखो("       -v <value>  Full path of the cgroup2\n");
	म_लिखो("       -h          Display this help\n");
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	स्थिर अक्षर *pinned_file = शून्य, *cg2 = शून्य;
	पूर्णांक create_array = 1;
	पूर्णांक array_key = 0;
	पूर्णांक array_fd = -1;
	पूर्णांक cg2_fd = -1;
	पूर्णांक ret = -1;
	पूर्णांक opt;

	जबतक ((opt = getopt(argc, argv, "F:U:v:")) != -1) अणु
		चयन (opt) अणु
		/* General args */
		हाल 'F':
			pinned_file = optarg;
			अवरोध;
		हाल 'U':
			pinned_file = optarg;
			create_array = 0;
			अवरोध;
		हाल 'v':
			cg2 = optarg;
			अवरोध;
		शेष:
			usage();
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (!cg2 || !pinned_file) अणु
		usage();
		जाओ out;
	पूर्ण

	cg2_fd = खोलो(cg2, O_RDONLY);
	अगर (cg2_fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "open(%s,...): %s(%d)\n",
			cg2, म_त्रुटि(त्रुटि_सं), त्रुटि_सं);
		जाओ out;
	पूर्ण

	अगर (create_array) अणु
		array_fd = bpf_create_map(BPF_MAP_TYPE_CGROUP_ARRAY,
					  माप(uपूर्णांक32_t), माप(uपूर्णांक32_t),
					  1, 0);
		अगर (array_fd < 0) अणु
			ख_लिखो(मानक_त्रुटि,
				"bpf_create_map(BPF_MAP_TYPE_CGROUP_ARRAY,...): %s(%d)\n",
				म_त्रुटि(त्रुटि_सं), त्रुटि_सं);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		array_fd = bpf_obj_get(pinned_file);
		अगर (array_fd < 0) अणु
			ख_लिखो(मानक_त्रुटि, "bpf_obj_get(%s): %s(%d)\n",
				pinned_file, म_त्रुटि(त्रुटि_सं), त्रुटि_सं);
			जाओ out;
		पूर्ण
	पूर्ण

	ret = bpf_map_update_elem(array_fd, &array_key, &cg2_fd, 0);
	अगर (ret) अणु
		लिखो_त्रुटि("bpf_map_update_elem");
		जाओ out;
	पूर्ण

	अगर (create_array) अणु
		ret = bpf_obj_pin(array_fd, pinned_file);
		अगर (ret) अणु
			ख_लिखो(मानक_त्रुटि, "bpf_obj_pin(..., %s): %s(%d)\n",
				pinned_file, म_त्रुटि(त्रुटि_सं), त्रुटि_सं);
			जाओ out;
		पूर्ण
	पूर्ण

out:
	अगर (array_fd != -1)
		बंद(array_fd);
	अगर (cg2_fd != -1)
		बंद(cg2_fd);
	वापस ret;
पूर्ण
