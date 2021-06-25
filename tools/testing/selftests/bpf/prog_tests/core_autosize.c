<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */

#समावेश <test_progs.h>
#समावेश <bpf/btf.h>

/* real layout and sizes according to test's (32-bit) BTF
 * needs to be defined beक्रमe skeleton is included */
काष्ठा test_काष्ठा___real अणु
	अचिन्हित पूर्णांक ptr; /* can't use `व्योम *`, it is always 8 byte in BPF target */
	अचिन्हित पूर्णांक val2;
	अचिन्हित दीर्घ दीर्घ val1;
	अचिन्हित लघु val3;
	अचिन्हित अक्षर val4;
	अचिन्हित अक्षर _pad;
पूर्ण;

#समावेश "test_core_autosize.skel.h"

अटल पूर्णांक duration = 0;

अटल काष्ठा अणु
	अचिन्हित दीर्घ दीर्घ ptr_samesized;
	अचिन्हित दीर्घ दीर्घ val1_samesized;
	अचिन्हित दीर्घ दीर्घ val2_samesized;
	अचिन्हित दीर्घ दीर्घ val3_samesized;
	अचिन्हित दीर्घ दीर्घ val4_samesized;
	काष्ठा test_काष्ठा___real output_samesized;

	अचिन्हित दीर्घ दीर्घ ptr_करोwnsized;
	अचिन्हित दीर्घ दीर्घ val1_करोwnsized;
	अचिन्हित दीर्घ दीर्घ val2_करोwnsized;
	अचिन्हित दीर्घ दीर्घ val3_करोwnsized;
	अचिन्हित दीर्घ दीर्घ val4_करोwnsized;
	काष्ठा test_काष्ठा___real output_करोwnsized;

	अचिन्हित दीर्घ दीर्घ ptr_probed;
	अचिन्हित दीर्घ दीर्घ val1_probed;
	अचिन्हित दीर्घ दीर्घ val2_probed;
	अचिन्हित दीर्घ दीर्घ val3_probed;
	अचिन्हित दीर्घ दीर्घ val4_probed;

	अचिन्हित दीर्घ दीर्घ ptr_चिन्हित;
	अचिन्हित दीर्घ दीर्घ val1_चिन्हित;
	अचिन्हित दीर्घ दीर्घ val2_चिन्हित;
	अचिन्हित दीर्घ दीर्घ val3_चिन्हित;
	अचिन्हित दीर्घ दीर्घ val4_चिन्हित;
	काष्ठा test_काष्ठा___real output_चिन्हित;
पूर्ण out;

व्योम test_core_स्वतःsize(व्योम)
अणु
	अक्षर btf_file[] = "/tmp/core_autosize.btf.XXXXXX";
	पूर्णांक err, fd = -1, zero = 0;
	पूर्णांक अक्षर_id, लघु_id, पूर्णांक_id, दीर्घ_दीर्घ_id, व्योम_ptr_id, id;
	काष्ठा test_core_स्वतःsize* skel = शून्य;
	काष्ठा bpf_object_load_attr load_attr = अणुपूर्ण;
	काष्ठा bpf_program *prog;
	काष्ठा bpf_map *bss_map;
	काष्ठा btf *btf = शून्य;
	माप_प्रकार written;
	स्थिर व्योम *raw_data;
	__u32 raw_sz;
	खाता *f = शून्य;

	btf = btf__new_empty();
	अगर (!ASSERT_OK_PTR(btf, "empty_btf"))
		वापस;
	/* Emit the following काष्ठा with 32-bit poपूर्णांकer size:
	 *
	 * काष्ठा test_काष्ठा अणु
	 *     व्योम *ptr;
	 *     अचिन्हित दीर्घ val2;
	 *     अचिन्हित दीर्घ दीर्घ val1;
	 *     अचिन्हित लघु val3;
	 *     अचिन्हित अक्षर val4;
	 *     अक्षर: 8;
	 * पूर्ण;
	 *
	 * This काष्ठा is going to be used as the "kernel BTF" क्रम this test.
	 * It's equivalent memory-layout-wise to test_काष्ठा__real above.
	 */

	/* क्रमce 32-bit poपूर्णांकer size */
	btf__set_poपूर्णांकer_size(btf, 4);

	अक्षर_id = btf__add_पूर्णांक(btf, "unsigned char", 1, 0);
	ASSERT_EQ(अक्षर_id, 1, "char_id");
	लघु_id = btf__add_पूर्णांक(btf, "unsigned short", 2, 0);
	ASSERT_EQ(लघु_id, 2, "short_id");
	/* "long unsigned int" of 4 byte size tells BTF that माप(व्योम *) == 4 */
	पूर्णांक_id = btf__add_पूर्णांक(btf, "long unsigned int", 4, 0);
	ASSERT_EQ(पूर्णांक_id, 3, "int_id");
	दीर्घ_दीर्घ_id = btf__add_पूर्णांक(btf, "unsigned long long", 8, 0);
	ASSERT_EQ(दीर्घ_दीर्घ_id, 4, "long_long_id");
	व्योम_ptr_id = btf__add_ptr(btf, 0);
	ASSERT_EQ(व्योम_ptr_id, 5, "void_ptr_id");

	id = btf__add_काष्ठा(btf, "test_struct", 20 /* bytes */);
	ASSERT_EQ(id, 6, "struct_id");
	err = btf__add_field(btf, "ptr", व्योम_ptr_id, 0, 0);
	err = err ?: btf__add_field(btf, "val2", पूर्णांक_id, 32, 0);
	err = err ?: btf__add_field(btf, "val1", दीर्घ_दीर्घ_id, 64, 0);
	err = err ?: btf__add_field(btf, "val3", लघु_id, 128, 0);
	err = err ?: btf__add_field(btf, "val4", अक्षर_id, 144, 0);
	ASSERT_OK(err, "struct_fields");

	fd = mkstemp(btf_file);
	अगर (CHECK(fd < 0, "btf_tmp", "failed to create file: %d\n", fd))
		जाओ cleanup;
	f = fकरोpen(fd, "w");
	अगर (!ASSERT_OK_PTR(f, "btf_fdopen"))
		जाओ cleanup;

	raw_data = btf__get_raw_data(btf, &raw_sz);
	अगर (!ASSERT_OK_PTR(raw_data, "raw_data"))
		जाओ cleanup;
	written = ख_डालो(raw_data, 1, raw_sz, f);
	अगर (CHECK(written != raw_sz, "btf_write", "written: %zu, errno: %d\n", written, त्रुटि_सं))
		जाओ cleanup;
	ख_साफ(f);
	ख_बंद(f);
	f = शून्य;
	बंद(fd);
	fd = -1;

	/* खोलो and load BPF program with custom BTF as the kernel BTF */
	skel = test_core_स्वतःsize__खोलो();
	अगर (!ASSERT_OK_PTR(skel, "skel_open"))
		वापस;

	/* disable handle_चिन्हित() क्रम now */
	prog = bpf_object__find_program_by_name(skel->obj, "handle_signed");
	अगर (!ASSERT_OK_PTR(prog, "prog_find"))
		जाओ cleanup;
	bpf_program__set_स्वतःload(prog, false);

	load_attr.obj = skel->obj;
	load_attr.target_btf_path = btf_file;
	err = bpf_object__load_xattr(&load_attr);
	अगर (!ASSERT_OK(err, "prog_load"))
		जाओ cleanup;

	prog = bpf_object__find_program_by_name(skel->obj, "handle_samesize");
	अगर (!ASSERT_OK_PTR(prog, "prog_find"))
		जाओ cleanup;
	skel->links.handle_samesize = bpf_program__attach(prog);
	अगर (!ASSERT_OK_PTR(skel->links.handle_samesize, "prog_attach"))
		जाओ cleanup;

	prog = bpf_object__find_program_by_name(skel->obj, "handle_downsize");
	अगर (!ASSERT_OK_PTR(prog, "prog_find"))
		जाओ cleanup;
	skel->links.handle_करोwnsize = bpf_program__attach(prog);
	अगर (!ASSERT_OK_PTR(skel->links.handle_करोwnsize, "prog_attach"))
		जाओ cleanup;

	prog = bpf_object__find_program_by_name(skel->obj, "handle_probed");
	अगर (!ASSERT_OK_PTR(prog, "prog_find"))
		जाओ cleanup;
	skel->links.handle_probed = bpf_program__attach(prog);
	अगर (!ASSERT_OK_PTR(skel->links.handle_probed, "prog_attach"))
		जाओ cleanup;

	usleep(1);

	bss_map = bpf_object__find_map_by_name(skel->obj, "test_cor.bss");
	अगर (!ASSERT_OK_PTR(bss_map, "bss_map_find"))
		जाओ cleanup;

	err = bpf_map_lookup_elem(bpf_map__fd(bss_map), &zero, (व्योम *)&out);
	अगर (!ASSERT_OK(err, "bss_lookup"))
		जाओ cleanup;

	ASSERT_EQ(out.ptr_samesized, 0x01020304, "ptr_samesized");
	ASSERT_EQ(out.val1_samesized, 0x1020304050607080, "val1_samesized");
	ASSERT_EQ(out.val2_samesized, 0x0a0b0c0d, "val2_samesized");
	ASSERT_EQ(out.val3_samesized, 0xfeed, "val3_samesized");
	ASSERT_EQ(out.val4_samesized, 0xb9, "val4_samesized");
	ASSERT_EQ(out.output_samesized.ptr, 0x01020304, "ptr_samesized");
	ASSERT_EQ(out.output_samesized.val1, 0x1020304050607080, "val1_samesized");
	ASSERT_EQ(out.output_samesized.val2, 0x0a0b0c0d, "val2_samesized");
	ASSERT_EQ(out.output_samesized.val3, 0xfeed, "val3_samesized");
	ASSERT_EQ(out.output_samesized.val4, 0xb9, "val4_samesized");

	ASSERT_EQ(out.ptr_करोwnsized, 0x01020304, "ptr_downsized");
	ASSERT_EQ(out.val1_करोwnsized, 0x1020304050607080, "val1_downsized");
	ASSERT_EQ(out.val2_करोwnsized, 0x0a0b0c0d, "val2_downsized");
	ASSERT_EQ(out.val3_करोwnsized, 0xfeed, "val3_downsized");
	ASSERT_EQ(out.val4_करोwnsized, 0xb9, "val4_downsized");
	ASSERT_EQ(out.output_करोwnsized.ptr, 0x01020304, "ptr_downsized");
	ASSERT_EQ(out.output_करोwnsized.val1, 0x1020304050607080, "val1_downsized");
	ASSERT_EQ(out.output_करोwnsized.val2, 0x0a0b0c0d, "val2_downsized");
	ASSERT_EQ(out.output_करोwnsized.val3, 0xfeed, "val3_downsized");
	ASSERT_EQ(out.output_करोwnsized.val4, 0xb9, "val4_downsized");

	ASSERT_EQ(out.ptr_probed, 0x01020304, "ptr_probed");
	ASSERT_EQ(out.val1_probed, 0x1020304050607080, "val1_probed");
	ASSERT_EQ(out.val2_probed, 0x0a0b0c0d, "val2_probed");
	ASSERT_EQ(out.val3_probed, 0xfeed, "val3_probed");
	ASSERT_EQ(out.val4_probed, 0xb9, "val4_probed");

	test_core_स्वतःsize__destroy(skel);
	skel = शून्य;

	/* now re-load with handle_चिन्हित() enabled, it should fail loading */
	skel = test_core_स्वतःsize__खोलो();
	अगर (!ASSERT_OK_PTR(skel, "skel_open"))
		वापस;

	load_attr.obj = skel->obj;
	load_attr.target_btf_path = btf_file;
	err = bpf_object__load_xattr(&load_attr);
	अगर (!ASSERT_ERR(err, "bad_prog_load"))
		जाओ cleanup;

cleanup:
	अगर (f)
		ख_बंद(f);
	अगर (fd >= 0)
		बंद(fd);
	हटाओ(btf_file);
	btf__मुक्त(btf);
	test_core_स्वतःsize__destroy(skel);
पूर्ण
