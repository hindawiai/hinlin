<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * bpf-script-test-relocation.c
 * Test BPF loader checking relocation
 */
#अगर_अघोषित LINUX_VERSION_CODE
# error Need LINUX_VERSION_CODE
# error Example: क्रम 4.2 kernel, put 'clang-opt="-DLINUX_VERSION_CODE=0x40200" into llvm section of ~/.perfconfig'
#पूर्ण_अगर
#घोषणा BPF_ANY 0
#घोषणा BPF_MAP_TYPE_ARRAY 2
#घोषणा BPF_FUNC_map_lookup_elem 1
#घोषणा BPF_FUNC_map_update_elem 2

अटल व्योम *(*bpf_map_lookup_elem)(व्योम *map, व्योम *key) =
	(व्योम *) BPF_FUNC_map_lookup_elem;
अटल व्योम *(*bpf_map_update_elem)(व्योम *map, व्योम *key, व्योम *value, पूर्णांक flags) =
	(व्योम *) BPF_FUNC_map_update_elem;

काष्ठा bpf_map_def अणु
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक key_size;
	अचिन्हित पूर्णांक value_size;
	अचिन्हित पूर्णांक max_entries;
पूर्ण;

#घोषणा SEC(NAME) __attribute__((section(NAME), used))
काष्ठा bpf_map_def SEC("maps") my_table = अणु
	.type = BPF_MAP_TYPE_ARRAY,
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.max_entries = 1,
पूर्ण;

पूर्णांक this_is_a_global_val;

SEC("func=sys_write")
पूर्णांक bpf_func__sys_ग_लिखो(व्योम *ctx)
अणु
	पूर्णांक key = 0;
	पूर्णांक value = 0;

	/*
	 * Incorrect relocation. Should not allow this program be
	 * loaded पूर्णांकo kernel.
	 */
	bpf_map_update_elem(&this_is_a_global_val, &key, &value, 0);
	वापस 0;
पूर्ण
अक्षर _license[] SEC("license") = "GPL";
पूर्णांक _version SEC("version") = LINUX_VERSION_CODE;
