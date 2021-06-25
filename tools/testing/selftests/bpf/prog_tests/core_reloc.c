<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश "progs/core_reloc_types.h"
#समावेश "bpf_testmod/bpf_testmod.h"
#समावेश <sys/mman.h>
#समावेश <sys/syscall.h>
#समावेश <bpf/btf.h>

अटल पूर्णांक duration = 0;

#घोषणा STRUCT_TO_CHAR_PTR(काष्ठा_name) (स्थिर अक्षर *)&(काष्ठा काष्ठा_name)

#घोषणा MODULES_CASE(name, sec_name, tp_name) अणु				\
	.हाल_name = name,						\
	.bpf_obj_file = "test_core_reloc_module.o",			\
	.btf_src_file = शून्य, /* find in kernel module BTFs */		\
	.input = "",							\
	.input_len = 0,							\
	.output = STRUCT_TO_CHAR_PTR(core_reloc_module_output) अणु	\
		.पढ़ो_ctx_sz = माप(काष्ठा bpf_tesपंचांगod_test_पढ़ो_ctx),\
		.पढ़ो_ctx_exists = true,				\
		.buf_exists = true,					\
		.len_exists = true,					\
		.off_exists = true,					\
		.len = 123,						\
		.off = 0,						\
		.comm = "test_progs",					\
		.comm_len = माप("test_progs"),			\
	पूर्ण,								\
	.output_len = माप(काष्ठा core_reloc_module_output),		\
	.prog_sec_name = sec_name,					\
	.raw_tp_name = tp_name,						\
	.trigger = trigger_module_test_पढ़ो,				\
	.needs_tesपंचांगod = true,						\
पूर्ण

#घोषणा FLAVORS_DATA(काष्ठा_name) STRUCT_TO_CHAR_PTR(काष्ठा_name) अणु	\
	.a = 42,							\
	.b = 0xc001,							\
	.c = 0xbeef,							\
पूर्ण

#घोषणा FLAVORS_CASE_COMMON(name)					\
	.हाल_name = #name,						\
	.bpf_obj_file = "test_core_reloc_flavors.o",			\
	.btf_src_file = "btf__core_reloc_" #name ".o"			\

#घोषणा FLAVORS_CASE(name) अणु						\
	FLAVORS_CASE_COMMON(name),					\
	.input = FLAVORS_DATA(core_reloc_##name),			\
	.input_len = माप(काष्ठा core_reloc_##name),			\
	.output = FLAVORS_DATA(core_reloc_flavors),			\
	.output_len = माप(काष्ठा core_reloc_flavors),		\
पूर्ण

#घोषणा FLAVORS_ERR_CASE(name) अणु					\
	FLAVORS_CASE_COMMON(name),					\
	.fails = true,							\
पूर्ण

#घोषणा NESTING_DATA(काष्ठा_name) STRUCT_TO_CHAR_PTR(काष्ठा_name) अणु	\
	.a = अणु .a = अणु .a = 42 पूर्ण पूर्ण,					\
	.b = अणु .b = अणु .b = 0xc001 पूर्ण पूर्ण,					\
पूर्ण

#घोषणा NESTING_CASE_COMMON(name)					\
	.हाल_name = #name,						\
	.bpf_obj_file = "test_core_reloc_nesting.o",			\
	.btf_src_file = "btf__core_reloc_" #name ".o"

#घोषणा NESTING_CASE(name) अणु						\
	NESTING_CASE_COMMON(name),					\
	.input = NESTING_DATA(core_reloc_##name),			\
	.input_len = माप(काष्ठा core_reloc_##name),			\
	.output = NESTING_DATA(core_reloc_nesting),			\
	.output_len = माप(काष्ठा core_reloc_nesting)			\
पूर्ण

#घोषणा NESTING_ERR_CASE(name) अणु					\
	NESTING_CASE_COMMON(name),					\
	.fails = true,							\
पूर्ण

#घोषणा ARRAYS_DATA(काष्ठा_name) STRUCT_TO_CHAR_PTR(काष्ठा_name) अणु	\
	.a = अणु [2] = 1 पूर्ण,						\
	.b = अणु [1] = अणु [2] = अणु [3] = 2 पूर्ण पूर्ण पूर्ण,				\
	.c = अणु [1] = अणु .c =  3 पूर्ण पूर्ण,					\
	.d = अणु [0] = अणु [0] = अणु .d = 4 पूर्ण पूर्ण पूर्ण,				\
पूर्ण

#घोषणा ARRAYS_CASE_COMMON(name)					\
	.हाल_name = #name,						\
	.bpf_obj_file = "test_core_reloc_arrays.o",			\
	.btf_src_file = "btf__core_reloc_" #name ".o"

#घोषणा ARRAYS_CASE(name) अणु						\
	ARRAYS_CASE_COMMON(name),					\
	.input = ARRAYS_DATA(core_reloc_##name),			\
	.input_len = माप(काष्ठा core_reloc_##name),			\
	.output = STRUCT_TO_CHAR_PTR(core_reloc_arrays_output) अणु	\
		.a2   = 1,						\
		.b123 = 2,						\
		.c1c  = 3,						\
		.d00d = 4,						\
		.f10c = 0,						\
	पूर्ण,								\
	.output_len = माप(काष्ठा core_reloc_arrays_output)		\
पूर्ण

#घोषणा ARRAYS_ERR_CASE(name) अणु						\
	ARRAYS_CASE_COMMON(name),					\
	.fails = true,							\
पूर्ण

#घोषणा PRIMITIVES_DATA(काष्ठा_name) STRUCT_TO_CHAR_PTR(काष्ठा_name) अणु	\
	.a = 1,								\
	.b = 2,								\
	.c = 3,								\
	.d = (व्योम *)4,							\
	.f = (व्योम *)5,							\
पूर्ण

#घोषणा PRIMITIVES_CASE_COMMON(name)					\
	.हाल_name = #name,						\
	.bpf_obj_file = "test_core_reloc_primitives.o",			\
	.btf_src_file = "btf__core_reloc_" #name ".o"

#घोषणा PRIMITIVES_CASE(name) अणु						\
	PRIMITIVES_CASE_COMMON(name),					\
	.input = PRIMITIVES_DATA(core_reloc_##name),			\
	.input_len = माप(काष्ठा core_reloc_##name),			\
	.output = PRIMITIVES_DATA(core_reloc_primitives),		\
	.output_len = माप(काष्ठा core_reloc_primitives),		\
पूर्ण

#घोषणा PRIMITIVES_ERR_CASE(name) अणु					\
	PRIMITIVES_CASE_COMMON(name),					\
	.fails = true,							\
पूर्ण

#घोषणा MODS_CASE(name) अणु						\
	.हाल_name = #name,						\
	.bpf_obj_file = "test_core_reloc_mods.o",			\
	.btf_src_file = "btf__core_reloc_" #name ".o",			\
	.input = STRUCT_TO_CHAR_PTR(core_reloc_##name) अणु		\
		.a = 1,							\
		.b = 2,							\
		.c = (व्योम *)3,						\
		.d = (व्योम *)4,						\
		.e = अणु [2] = 5 पूर्ण,					\
		.f = अणु [1] = 6 पूर्ण,					\
		.g = अणु .x = 7 पूर्ण,					\
		.h = अणु .y = 8 पूर्ण,					\
	पूर्ण,								\
	.input_len = माप(काष्ठा core_reloc_##name),			\
	.output = STRUCT_TO_CHAR_PTR(core_reloc_mods_output) अणु		\
		.a = 1, .b = 2, .c = 3, .d = 4,				\
		.e = 5, .f = 6, .g = 7, .h = 8,				\
	पूर्ण,								\
	.output_len = माप(काष्ठा core_reloc_mods_output),		\
पूर्ण

#घोषणा PTR_AS_ARR_CASE(name) अणु						\
	.हाल_name = #name,						\
	.bpf_obj_file = "test_core_reloc_ptr_as_arr.o",			\
	.btf_src_file = "btf__core_reloc_" #name ".o",			\
	.input = (स्थिर अक्षर *)&(काष्ठा core_reloc_##name [])अणु		\
		अणु .a = 1 पूर्ण,						\
		अणु .a = 2 पूर्ण,						\
		अणु .a = 3 पूर्ण,						\
	पूर्ण,								\
	.input_len = 3 * माप(काष्ठा core_reloc_##name),		\
	.output = STRUCT_TO_CHAR_PTR(core_reloc_ptr_as_arr) अणु		\
		.a = 3,							\
	पूर्ण,								\
	.output_len = माप(काष्ठा core_reloc_ptr_as_arr),		\
पूर्ण

#घोषणा INTS_DATA(काष्ठा_name) STRUCT_TO_CHAR_PTR(काष्ठा_name) अणु	\
	.u8_field = 1,							\
	.s8_field = 2,							\
	.u16_field = 3,							\
	.s16_field = 4,							\
	.u32_field = 5,							\
	.s32_field = 6,							\
	.u64_field = 7,							\
	.s64_field = 8,							\
पूर्ण

#घोषणा INTS_CASE_COMMON(name)						\
	.हाल_name = #name,						\
	.bpf_obj_file = "test_core_reloc_ints.o",			\
	.btf_src_file = "btf__core_reloc_" #name ".o"

#घोषणा INTS_CASE(name) अणु						\
	INTS_CASE_COMMON(name),						\
	.input = INTS_DATA(core_reloc_##name),				\
	.input_len = माप(काष्ठा core_reloc_##name),			\
	.output = INTS_DATA(core_reloc_पूर्णांकs),				\
	.output_len = माप(काष्ठा core_reloc_पूर्णांकs),			\
पूर्ण

#घोषणा INTS_ERR_CASE(name) अणु						\
	INTS_CASE_COMMON(name),						\
	.fails = true,							\
पूर्ण

#घोषणा FIELD_EXISTS_CASE_COMMON(name)					\
	.हाल_name = #name,						\
	.bpf_obj_file = "test_core_reloc_existence.o",			\
	.btf_src_file = "btf__core_reloc_" #name ".o"			\

#घोषणा BITFIELDS_CASE_COMMON(objfile, test_name_prefix,  name)		\
	.हाल_name = test_name_prefix#name,				\
	.bpf_obj_file = objfile,					\
	.btf_src_file = "btf__core_reloc_" #name ".o"

#घोषणा BITFIELDS_CASE(name, ...) अणु					\
	BITFIELDS_CASE_COMMON("test_core_reloc_bitfields_probed.o",	\
			      "probed:", name),				\
	.input = STRUCT_TO_CHAR_PTR(core_reloc_##name) __VA_ARGS__,	\
	.input_len = माप(काष्ठा core_reloc_##name),			\
	.output = STRUCT_TO_CHAR_PTR(core_reloc_bitfields_output)	\
		__VA_ARGS__,						\
	.output_len = माप(काष्ठा core_reloc_bitfields_output),	\
पूर्ण, अणु									\
	BITFIELDS_CASE_COMMON("test_core_reloc_bitfields_direct.o",	\
			      "direct:", name),				\
	.input = STRUCT_TO_CHAR_PTR(core_reloc_##name) __VA_ARGS__,	\
	.input_len = माप(काष्ठा core_reloc_##name),			\
	.output = STRUCT_TO_CHAR_PTR(core_reloc_bitfields_output)	\
		__VA_ARGS__,						\
	.output_len = माप(काष्ठा core_reloc_bitfields_output),	\
	.prog_sec_name = "tp_btf/sys_enter",				\
पूर्ण


#घोषणा BITFIELDS_ERR_CASE(name) अणु					\
	BITFIELDS_CASE_COMMON("test_core_reloc_bitfields_probed.o",	\
			      "probed:", name),				\
	.fails = true,							\
पूर्ण, अणु									\
	BITFIELDS_CASE_COMMON("test_core_reloc_bitfields_direct.o",	\
			      "direct:", name),				\
	.prog_sec_name = "tp_btf/sys_enter",				\
	.fails = true,							\
पूर्ण

#घोषणा SIZE_CASE_COMMON(name)						\
	.हाल_name = #name,						\
	.bpf_obj_file = "test_core_reloc_size.o",			\
	.btf_src_file = "btf__core_reloc_" #name ".o",			\
	.relaxed_core_relocs = true

#घोषणा SIZE_OUTPUT_DATA(type)						\
	STRUCT_TO_CHAR_PTR(core_reloc_size_output) अणु			\
		.पूर्णांक_sz = माप(((type *)0)->पूर्णांक_field),		\
		.काष्ठा_sz = माप(((type *)0)->काष्ठा_field),		\
		.जोड़_sz = माप(((type *)0)->जोड़_field),		\
		.arr_sz = माप(((type *)0)->arr_field),		\
		.arr_elem_sz = माप(((type *)0)->arr_field[0]),	\
		.ptr_sz = 8, /* always 8-byte poपूर्णांकer क्रम BPF */	\
		.क्रमागत_sz = माप(((type *)0)->क्रमागत_field),		\
		.भग्न_sz = माप(((type *)0)->भग्न_field),		\
	पूर्ण

#घोषणा SIZE_CASE(name) अणु						\
	SIZE_CASE_COMMON(name),						\
	.input_len = 0,							\
	.output = SIZE_OUTPUT_DATA(काष्ठा core_reloc_##name),		\
	.output_len = माप(काष्ठा core_reloc_size_output),		\
पूर्ण

#घोषणा SIZE_ERR_CASE(name) अणु						\
	SIZE_CASE_COMMON(name),						\
	.fails = true,							\
पूर्ण

#घोषणा TYPE_BASED_CASE_COMMON(name)					\
	.हाल_name = #name,						\
	.bpf_obj_file = "test_core_reloc_type_based.o",		\
	.btf_src_file = "btf__core_reloc_" #name ".o"			\

#घोषणा TYPE_BASED_CASE(name, ...) अणु					\
	TYPE_BASED_CASE_COMMON(name),					\
	.output = STRUCT_TO_CHAR_PTR(core_reloc_type_based_output)	\
			__VA_ARGS__,					\
	.output_len = माप(काष्ठा core_reloc_type_based_output),	\
पूर्ण

#घोषणा TYPE_BASED_ERR_CASE(name) अणु					\
	TYPE_BASED_CASE_COMMON(name),					\
	.fails = true,							\
पूर्ण

#घोषणा TYPE_ID_CASE_COMMON(name)					\
	.हाल_name = #name,						\
	.bpf_obj_file = "test_core_reloc_type_id.o",			\
	.btf_src_file = "btf__core_reloc_" #name ".o"			\

#घोषणा TYPE_ID_CASE(name, setup_fn) अणु					\
	TYPE_ID_CASE_COMMON(name),					\
	.output = STRUCT_TO_CHAR_PTR(core_reloc_type_id_output) अणुपूर्ण,	\
	.output_len = माप(काष्ठा core_reloc_type_id_output),		\
	.setup = setup_fn,						\
पूर्ण

#घोषणा TYPE_ID_ERR_CASE(name) अणु					\
	TYPE_ID_CASE_COMMON(name),					\
	.fails = true,							\
पूर्ण

#घोषणा ENUMVAL_CASE_COMMON(name)					\
	.हाल_name = #name,						\
	.bpf_obj_file = "test_core_reloc_enumval.o",			\
	.btf_src_file = "btf__core_reloc_" #name ".o"			\

#घोषणा ENUMVAL_CASE(name, ...) अणु					\
	ENUMVAL_CASE_COMMON(name),					\
	.output = STRUCT_TO_CHAR_PTR(core_reloc_क्रमागतval_output)		\
			__VA_ARGS__,					\
	.output_len = माप(काष्ठा core_reloc_क्रमागतval_output),		\
पूर्ण

#घोषणा ENUMVAL_ERR_CASE(name) अणु					\
	ENUMVAL_CASE_COMMON(name),					\
	.fails = true,							\
पूर्ण

काष्ठा core_reloc_test_हाल;

प्रकार पूर्णांक (*setup_test_fn)(काष्ठा core_reloc_test_हाल *test);
प्रकार पूर्णांक (*trigger_test_fn)(स्थिर काष्ठा core_reloc_test_हाल *test);

काष्ठा core_reloc_test_हाल अणु
	स्थिर अक्षर *हाल_name;
	स्थिर अक्षर *bpf_obj_file;
	स्थिर अक्षर *btf_src_file;
	स्थिर अक्षर *input;
	पूर्णांक input_len;
	स्थिर अक्षर *output;
	पूर्णांक output_len;
	bool fails;
	bool needs_tesपंचांगod;
	bool relaxed_core_relocs;
	स्थिर अक्षर *prog_sec_name;
	स्थिर अक्षर *raw_tp_name;
	setup_test_fn setup;
	trigger_test_fn trigger;
पूर्ण;

अटल पूर्णांक find_btf_type(स्थिर काष्ठा btf *btf, स्थिर अक्षर *name, __u32 kind)
अणु
	पूर्णांक id;

	id = btf__find_by_name_kind(btf, name, kind);
	अगर (CHECK(id <= 0, "find_type_id", "failed to find '%s', kind %d: %d\n", name, kind, id))
		वापस -1;

	वापस id;
पूर्ण

अटल पूर्णांक setup_type_id_हाल_local(काष्ठा core_reloc_test_हाल *test)
अणु
	काष्ठा core_reloc_type_id_output *exp = (व्योम *)test->output;
	काष्ठा btf *local_btf = btf__parse(test->bpf_obj_file, शून्य);
	काष्ठा btf *targ_btf = btf__parse(test->btf_src_file, शून्य);
	स्थिर काष्ठा btf_type *t;
	स्थिर अक्षर *name;
	पूर्णांक i;

	अगर (CHECK(IS_ERR(local_btf), "local_btf", "failed: %ld\n", PTR_ERR(local_btf)) ||
	    CHECK(IS_ERR(targ_btf), "targ_btf", "failed: %ld\n", PTR_ERR(targ_btf))) अणु
		btf__मुक्त(local_btf);
		btf__मुक्त(targ_btf);
		वापस -EINVAL;
	पूर्ण

	exp->local_anon_काष्ठा = -1;
	exp->local_anon_जोड़ = -1;
	exp->local_anon_क्रमागत = -1;
	exp->local_anon_func_proto_ptr = -1;
	exp->local_anon_व्योम_ptr = -1;
	exp->local_anon_arr = -1;

	क्रम (i = 1; i <= btf__get_nr_types(local_btf); i++)
	अणु
		t = btf__type_by_id(local_btf, i);
		/* we are पूर्णांकerested only in anonymous types */
		अगर (t->name_off)
			जारी;

		अगर (btf_is_काष्ठा(t) && btf_vlen(t) &&
		    (name = btf__name_by_offset(local_btf, btf_members(t)[0].name_off)) &&
		    म_भेद(name, "marker_field") == 0) अणु
			exp->local_anon_काष्ठा = i;
		पूर्ण अन्यथा अगर (btf_is_जोड़(t) && btf_vlen(t) &&
			 (name = btf__name_by_offset(local_btf, btf_members(t)[0].name_off)) &&
			 म_भेद(name, "marker_field") == 0) अणु
			exp->local_anon_जोड़ = i;
		पूर्ण अन्यथा अगर (btf_is_क्रमागत(t) && btf_vlen(t) &&
			 (name = btf__name_by_offset(local_btf, btf_क्रमागत(t)[0].name_off)) &&
			 म_भेद(name, "MARKER_ENUM_VAL") == 0) अणु
			exp->local_anon_क्रमागत = i;
		पूर्ण अन्यथा अगर (btf_is_ptr(t) && (t = btf__type_by_id(local_btf, t->type))) अणु
			अगर (btf_is_func_proto(t) && (t = btf__type_by_id(local_btf, t->type)) &&
			    btf_is_पूर्णांक(t) && (name = btf__name_by_offset(local_btf, t->name_off)) &&
			    म_भेद(name, "_Bool") == 0) अणु
				/* ptr -> func_proto -> _Bool */
				exp->local_anon_func_proto_ptr = i;
			पूर्ण अन्यथा अगर (btf_is_व्योम(t)) अणु
				/* ptr -> व्योम */
				exp->local_anon_व्योम_ptr = i;
			पूर्ण
		पूर्ण अन्यथा अगर (btf_is_array(t) && (t = btf__type_by_id(local_btf, btf_array(t)->type)) &&
			   btf_is_पूर्णांक(t) && (name = btf__name_by_offset(local_btf, t->name_off)) &&
			   म_भेद(name, "_Bool") == 0) अणु
			/* _Bool[] */
			exp->local_anon_arr = i;
		पूर्ण
	पूर्ण

	exp->local_काष्ठा = find_btf_type(local_btf, "a_struct", BTF_KIND_STRUCT);
	exp->local_जोड़ = find_btf_type(local_btf, "a_union", BTF_KIND_UNION);
	exp->local_क्रमागत = find_btf_type(local_btf, "an_enum", BTF_KIND_ENUM);
	exp->local_पूर्णांक = find_btf_type(local_btf, "int", BTF_KIND_INT);
	exp->local_काष्ठा_प्रकार = find_btf_type(local_btf, "named_struct_typedef", BTF_KIND_TYPEDEF);
	exp->local_func_proto_प्रकार = find_btf_type(local_btf, "func_proto_typedef", BTF_KIND_TYPEDEF);
	exp->local_arr_प्रकार = find_btf_type(local_btf, "arr_typedef", BTF_KIND_TYPEDEF);

	btf__मुक्त(local_btf);
	btf__मुक्त(targ_btf);
	वापस 0;
पूर्ण

अटल पूर्णांक setup_type_id_हाल_success(काष्ठा core_reloc_test_हाल *test) अणु
	काष्ठा core_reloc_type_id_output *exp = (व्योम *)test->output;
	काष्ठा btf *targ_btf = btf__parse(test->btf_src_file, शून्य);
	पूर्णांक err;

	err = setup_type_id_हाल_local(test);
	अगर (err)
		वापस err;

	targ_btf = btf__parse(test->btf_src_file, शून्य);

	exp->targ_काष्ठा = find_btf_type(targ_btf, "a_struct", BTF_KIND_STRUCT);
	exp->targ_जोड़ = find_btf_type(targ_btf, "a_union", BTF_KIND_UNION);
	exp->targ_क्रमागत = find_btf_type(targ_btf, "an_enum", BTF_KIND_ENUM);
	exp->targ_पूर्णांक = find_btf_type(targ_btf, "int", BTF_KIND_INT);
	exp->targ_काष्ठा_प्रकार = find_btf_type(targ_btf, "named_struct_typedef", BTF_KIND_TYPEDEF);
	exp->targ_func_proto_प्रकार = find_btf_type(targ_btf, "func_proto_typedef", BTF_KIND_TYPEDEF);
	exp->targ_arr_प्रकार = find_btf_type(targ_btf, "arr_typedef", BTF_KIND_TYPEDEF);

	btf__मुक्त(targ_btf);
	वापस 0;
पूर्ण

अटल पूर्णांक setup_type_id_हाल_failure(काष्ठा core_reloc_test_हाल *test)
अणु
	काष्ठा core_reloc_type_id_output *exp = (व्योम *)test->output;
	पूर्णांक err;

	err = setup_type_id_हाल_local(test);
	अगर (err)
		वापस err;

	exp->targ_काष्ठा = 0;
	exp->targ_जोड़ = 0;
	exp->targ_क्रमागत = 0;
	exp->targ_पूर्णांक = 0;
	exp->targ_काष्ठा_प्रकार = 0;
	exp->targ_func_proto_प्रकार = 0;
	exp->targ_arr_प्रकार = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक trigger_module_test_पढ़ो(स्थिर काष्ठा core_reloc_test_हाल *test)
अणु
	काष्ठा core_reloc_module_output *exp = (व्योम *)test->output;
	पूर्णांक fd, err;

	fd = खोलो("/sys/kernel/bpf_testmod", O_RDONLY);
	err = -त्रुटि_सं;
	अगर (CHECK(fd < 0, "testmod_file_open", "failed: %d\n", err))
		वापस err;

	पढ़ो(fd, शून्य, exp->len); /* request expected number of bytes */
	बंद(fd);

	वापस 0;
पूर्ण


अटल काष्ठा core_reloc_test_हाल test_हालs[] = अणु
	/* validate we can find kernel image and use its BTF क्रम relocs */
	अणु
		.हाल_name = "kernel",
		.bpf_obj_file = "test_core_reloc_kernel.o",
		.btf_src_file = शून्य, /* load from /lib/modules/$(uname -r) */
		.input = "",
		.input_len = 0,
		.output = STRUCT_TO_CHAR_PTR(core_reloc_kernel_output) अणु
			.valid = अणु 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, पूर्ण,
			.comm = "test_progs",
			.comm_len = माप("test_progs"),
		पूर्ण,
		.output_len = माप(काष्ठा core_reloc_kernel_output),
	पूर्ण,

	/* validate we can find kernel module BTF types क्रम relocs/attach */
	MODULES_CASE("module_probed", "raw_tp/bpf_testmod_test_read", "bpf_testmod_test_read"),
	MODULES_CASE("module_direct", "tp_btf/bpf_testmod_test_read", शून्य),

	/* validate BPF program can use multiple flavors to match against
	 * single target BTF type
	 */
	FLAVORS_CASE(flavors),

	FLAVORS_ERR_CASE(flavors__err_wrong_name),

	/* various काष्ठा/क्रमागत nesting and resolution scenarios */
	NESTING_CASE(nesting),
	NESTING_CASE(nesting___anon_embed),
	NESTING_CASE(nesting___काष्ठा_जोड़_mixup),
	NESTING_CASE(nesting___extra_nesting),
	NESTING_CASE(nesting___dup_compat_types),

	NESTING_ERR_CASE(nesting___err_missing_field),
	NESTING_ERR_CASE(nesting___err_array_field),
	NESTING_ERR_CASE(nesting___err_missing_container),
	NESTING_ERR_CASE(nesting___err_nonकाष्ठा_container),
	NESTING_ERR_CASE(nesting___err_array_container),
	NESTING_ERR_CASE(nesting___err_dup_incompat_types),
	NESTING_ERR_CASE(nesting___err_partial_match_dups),
	NESTING_ERR_CASE(nesting___err_too_deep),

	/* various array access relocation scenarios */
	ARRAYS_CASE(arrays),
	ARRAYS_CASE(arrays___dअगरf_arr_dim),
	ARRAYS_CASE(arrays___dअगरf_arr_val_sz),
	ARRAYS_CASE(arrays___equiv_zero_sz_arr),
	ARRAYS_CASE(arrays___fixed_arr),

	ARRAYS_ERR_CASE(arrays___err_too_small),
	ARRAYS_ERR_CASE(arrays___err_too_shallow),
	ARRAYS_ERR_CASE(arrays___err_non_array),
	ARRAYS_ERR_CASE(arrays___err_wrong_val_type),
	ARRAYS_ERR_CASE(arrays___err_bad_zero_sz_arr),

	/* क्रमागत/ptr/पूर्णांक handling scenarios */
	PRIMITIVES_CASE(primitives),
	PRIMITIVES_CASE(primitives___dअगरf_क्रमागत_def),
	PRIMITIVES_CASE(primitives___dअगरf_func_proto),
	PRIMITIVES_CASE(primitives___dअगरf_ptr_type),

	PRIMITIVES_ERR_CASE(primitives___err_non_क्रमागत),
	PRIMITIVES_ERR_CASE(primitives___err_non_पूर्णांक),
	PRIMITIVES_ERR_CASE(primitives___err_non_ptr),

	/* स्थिर/अस्थिर/restrict and प्रकारs scenarios */
	MODS_CASE(mods),
	MODS_CASE(mods___mod_swap),
	MODS_CASE(mods___प्रकारs),

	/* handling "ptr is an array" semantics */
	PTR_AS_ARR_CASE(ptr_as_arr),
	PTR_AS_ARR_CASE(ptr_as_arr___dअगरf_sz),

	/* पूर्णांक चिन्हितness/sizing/bitfield handling */
	INTS_CASE(पूर्णांकs),
	INTS_CASE(पूर्णांकs___bool),
	INTS_CASE(पूर्णांकs___reverse_sign),

	/* validate edge हालs of capturing relocations */
	अणु
		.हाल_name = "misc",
		.bpf_obj_file = "test_core_reloc_misc.o",
		.btf_src_file = "btf__core_reloc_misc.o",
		.input = (स्थिर अक्षर *)&(काष्ठा core_reloc_misc_extensible[])अणु
			अणु .a = 1 पूर्ण,
			अणु .a = 2 पूर्ण, /* not पढ़ो */
			अणु .a = 3 पूर्ण,
		पूर्ण,
		.input_len = 4 * माप(पूर्णांक),
		.output = STRUCT_TO_CHAR_PTR(core_reloc_misc_output) अणु
			.a = 1,
			.b = 1,
			.c = 0, /* BUG in clang, should be 3 */
		पूर्ण,
		.output_len = माप(काष्ठा core_reloc_misc_output),
	पूर्ण,

	/* validate field existence checks */
	अणु
		FIELD_EXISTS_CASE_COMMON(existence),
		.input = STRUCT_TO_CHAR_PTR(core_reloc_existence) अणु
			.a = 1,
			.b = 2,
			.c = 3,
			.arr = अणु 4 पूर्ण,
			.s = अणु .x = 5 पूर्ण,
		पूर्ण,
		.input_len = माप(काष्ठा core_reloc_existence),
		.output = STRUCT_TO_CHAR_PTR(core_reloc_existence_output) अणु
			.a_exists = 1,
			.b_exists = 1,
			.c_exists = 1,
			.arr_exists = 1,
			.s_exists = 1,
			.a_value = 1,
			.b_value = 2,
			.c_value = 3,
			.arr_value = 4,
			.s_value = 5,
		पूर्ण,
		.output_len = माप(काष्ठा core_reloc_existence_output),
	पूर्ण,
	अणु
		FIELD_EXISTS_CASE_COMMON(existence___minimal),
		.input = STRUCT_TO_CHAR_PTR(core_reloc_existence___minimal) अणु
			.a = 42,
		पूर्ण,
		.input_len = माप(काष्ठा core_reloc_existence___minimal),
		.output = STRUCT_TO_CHAR_PTR(core_reloc_existence_output) अणु
			.a_exists = 1,
			.b_exists = 0,
			.c_exists = 0,
			.arr_exists = 0,
			.s_exists = 0,
			.a_value = 42,
			.b_value = 0xff000002u,
			.c_value = 0xff000003u,
			.arr_value = 0xff000004u,
			.s_value = 0xff000005u,
		पूर्ण,
		.output_len = माप(काष्ठा core_reloc_existence_output),
	पूर्ण,
	अणु
		FIELD_EXISTS_CASE_COMMON(existence___wrong_field_defs),
		.input = STRUCT_TO_CHAR_PTR(core_reloc_existence___wrong_field_defs) अणु
		पूर्ण,
		.input_len = माप(काष्ठा core_reloc_existence___wrong_field_defs),
		.output = STRUCT_TO_CHAR_PTR(core_reloc_existence_output) अणु
			.a_exists = 0,
			.b_exists = 0,
			.c_exists = 0,
			.arr_exists = 0,
			.s_exists = 0,
			.a_value = 0xff000001u,
			.b_value = 0xff000002u,
			.c_value = 0xff000003u,
			.arr_value = 0xff000004u,
			.s_value = 0xff000005u,
		पूर्ण,
		.output_len = माप(काष्ठा core_reloc_existence_output),
	पूर्ण,

	/* bitfield relocation checks */
	BITFIELDS_CASE(bitfields, अणु
		.ub1 = 1,
		.ub2 = 2,
		.ub7 = 96,
		.sb4 = -7,
		.sb20 = -0x76543,
		.u32 = 0x80000000,
		.s32 = -0x76543210,
	पूर्ण),
	BITFIELDS_CASE(bitfields___bit_sz_change, अणु
		.ub1 = 6,
		.ub2 = 0xABCDE,
		.ub7 = 1,
		.sb4 = -1,
		.sb20 = -0x17654321,
		.u32 = 0xBEEF,
		.s32 = -0x3FEDCBA987654321LL,
	पूर्ण),
	BITFIELDS_CASE(bitfields___bitfield_vs_पूर्णांक, अणु
		.ub1 = 0xFEDCBA9876543210LL,
		.ub2 = 0xA6,
		.ub7 = -0x7EDCBA987654321LL,
		.sb4 = -0x6123456789ABCDELL,
		.sb20 = 0xD00DLL,
		.u32 = -0x76543,
		.s32 = 0x0ADEADBEEFBADB0BLL,
	पूर्ण),
	BITFIELDS_CASE(bitfields___just_big_enough, अणु
		.ub1 = 0xFLL,
		.ub2 = 0x0812345678FEDCBALL,
	पूर्ण),
	BITFIELDS_ERR_CASE(bitfields___err_too_big_bitfield),

	/* size relocation checks */
	SIZE_CASE(size),
	SIZE_CASE(size___dअगरf_sz),
	SIZE_ERR_CASE(size___err_ambiguous),

	/* validate type existence and size relocations */
	TYPE_BASED_CASE(type_based, अणु
		.काष्ठा_exists = 1,
		.जोड़_exists = 1,
		.क्रमागत_exists = 1,
		.प्रकार_named_काष्ठा_exists = 1,
		.प्रकार_anon_काष्ठा_exists = 1,
		.प्रकार_काष्ठा_ptr_exists = 1,
		.प्रकार_पूर्णांक_exists = 1,
		.प्रकार_क्रमागत_exists = 1,
		.प्रकार_व्योम_ptr_exists = 1,
		.प्रकार_func_proto_exists = 1,
		.प्रकार_arr_exists = 1,
		.काष्ठा_sz = माप(काष्ठा a_काष्ठा),
		.जोड़_sz = माप(जोड़ a_जोड़),
		.क्रमागत_sz = माप(क्रमागत an_क्रमागत),
		.प्रकार_named_काष्ठा_sz = माप(named_काष्ठा_प्रकार),
		.प्रकार_anon_काष्ठा_sz = माप(anon_काष्ठा_प्रकार),
		.प्रकार_काष्ठा_ptr_sz = माप(काष्ठा_ptr_प्रकार),
		.प्रकार_पूर्णांक_sz = माप(पूर्णांक_प्रकार),
		.प्रकार_क्रमागत_sz = माप(क्रमागत_प्रकार),
		.प्रकार_व्योम_ptr_sz = माप(व्योम_ptr_प्रकार),
		.प्रकार_func_proto_sz = माप(func_proto_प्रकार),
		.प्रकार_arr_sz = माप(arr_प्रकार),
	पूर्ण),
	TYPE_BASED_CASE(type_based___all_missing, अणु
		/* all zeros */
	पूर्ण),
	TYPE_BASED_CASE(type_based___dअगरf_sz, अणु
		.काष्ठा_exists = 1,
		.जोड़_exists = 1,
		.क्रमागत_exists = 1,
		.प्रकार_named_काष्ठा_exists = 1,
		.प्रकार_anon_काष्ठा_exists = 1,
		.प्रकार_काष्ठा_ptr_exists = 1,
		.प्रकार_पूर्णांक_exists = 1,
		.प्रकार_क्रमागत_exists = 1,
		.प्रकार_व्योम_ptr_exists = 1,
		.प्रकार_func_proto_exists = 1,
		.प्रकार_arr_exists = 1,
		.काष्ठा_sz = माप(काष्ठा a_काष्ठा___dअगरf_sz),
		.जोड़_sz = माप(जोड़ a_जोड़___dअगरf_sz),
		.क्रमागत_sz = माप(क्रमागत an_क्रमागत___dअगरf_sz),
		.प्रकार_named_काष्ठा_sz = माप(named_काष्ठा_प्रकार___dअगरf_sz),
		.प्रकार_anon_काष्ठा_sz = माप(anon_काष्ठा_प्रकार___dअगरf_sz),
		.प्रकार_काष्ठा_ptr_sz = माप(काष्ठा_ptr_प्रकार___dअगरf_sz),
		.प्रकार_पूर्णांक_sz = माप(पूर्णांक_प्रकार___dअगरf_sz),
		.प्रकार_क्रमागत_sz = माप(क्रमागत_प्रकार___dअगरf_sz),
		.प्रकार_व्योम_ptr_sz = माप(व्योम_ptr_प्रकार___dअगरf_sz),
		.प्रकार_func_proto_sz = माप(func_proto_प्रकार___dअगरf_sz),
		.प्रकार_arr_sz = माप(arr_प्रकार___dअगरf_sz),
	पूर्ण),
	TYPE_BASED_CASE(type_based___incompat, अणु
		.क्रमागत_exists = 1,
		.क्रमागत_sz = माप(क्रमागत an_क्रमागत),
	पूर्ण),
	TYPE_BASED_CASE(type_based___fn_wrong_args, अणु
		.काष्ठा_exists = 1,
		.काष्ठा_sz = माप(काष्ठा a_काष्ठा),
	पूर्ण),

	/* BTF_TYPE_ID_LOCAL/BTF_TYPE_ID_TARGET tests */
	TYPE_ID_CASE(type_id, setup_type_id_हाल_success),
	TYPE_ID_CASE(type_id___missing_tarमाला_लो, setup_type_id_हाल_failure),

	/* Enumerator value existence and value relocations */
	ENUMVAL_CASE(क्रमागतval, अणु
		.named_val1_exists = true,
		.named_val2_exists = true,
		.named_val3_exists = true,
		.anon_val1_exists = true,
		.anon_val2_exists = true,
		.anon_val3_exists = true,
		.named_val1 = 1,
		.named_val2 = 2,
		.anon_val1 = 0x10,
		.anon_val2 = 0x20,
	पूर्ण),
	ENUMVAL_CASE(क्रमागतval___dअगरf, अणु
		.named_val1_exists = true,
		.named_val2_exists = true,
		.named_val3_exists = true,
		.anon_val1_exists = true,
		.anon_val2_exists = true,
		.anon_val3_exists = true,
		.named_val1 = 101,
		.named_val2 = 202,
		.anon_val1 = 0x11,
		.anon_val2 = 0x22,
	पूर्ण),
	ENUMVAL_CASE(क्रमागतval___val3_missing, अणु
		.named_val1_exists = true,
		.named_val2_exists = true,
		.named_val3_exists = false,
		.anon_val1_exists = true,
		.anon_val2_exists = true,
		.anon_val3_exists = false,
		.named_val1 = 111,
		.named_val2 = 222,
		.anon_val1 = 0x111,
		.anon_val2 = 0x222,
	पूर्ण),
	ENUMVAL_ERR_CASE(क्रमागतval___err_missing),
पूर्ण;

काष्ठा data अणु
	अक्षर in[256];
	अक्षर out[256];
	bool skip;
	uपूर्णांक64_t my_pid_tgid;
पूर्ण;

अटल माप_प्रकार roundup_page(माप_प्रकार sz)
अणु
	दीर्घ page_size = sysconf(_SC_PAGE_SIZE);
	वापस (sz + page_size - 1) / page_size * page_size;
पूर्ण

व्योम test_core_reloc(व्योम)
अणु
	स्थिर माप_प्रकार mmap_sz = roundup_page(माप(काष्ठा data));
	काष्ठा bpf_object_load_attr load_attr = अणुपूर्ण;
	काष्ठा core_reloc_test_हाल *test_हाल;
	स्थिर अक्षर *tp_name, *probe_name;
	पूर्णांक err, i, equal;
	काष्ठा bpf_link *link = शून्य;
	काष्ठा bpf_map *data_map;
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	uपूर्णांक64_t my_pid_tgid;
	काष्ठा data *data;
	व्योम *mmap_data = शून्य;

	my_pid_tgid = getpid() | ((uपूर्णांक64_t)syscall(SYS_gettid) << 32);

	क्रम (i = 0; i < ARRAY_SIZE(test_हालs); i++) अणु
		test_हाल = &test_हालs[i];
		अगर (!test__start_subtest(test_हाल->हाल_name))
			जारी;

		अगर (test_हाल->needs_tesपंचांगod && !env.has_tesपंचांगod) अणु
			test__skip();
			जारी;
		पूर्ण

		अगर (test_हाल->setup) अणु
			err = test_हाल->setup(test_हाल);
			अगर (CHECK(err, "test_setup", "test #%d setup failed: %d\n", i, err))
				जारी;
		पूर्ण

		obj = bpf_object__खोलो_file(test_हाल->bpf_obj_file, शून्य);
		अगर (CHECK(IS_ERR(obj), "obj_open", "failed to open '%s': %ld\n",
			  test_हाल->bpf_obj_file, PTR_ERR(obj)))
			जारी;

		probe_name = "raw_tracepoint/sys_enter";
		tp_name = "sys_enter";
		अगर (test_हाल->prog_sec_name) अणु
			probe_name = test_हाल->prog_sec_name;
			tp_name = test_हाल->raw_tp_name; /* शून्य क्रम tp_btf */
		पूर्ण

		prog = bpf_object__find_program_by_title(obj, probe_name);
		अगर (CHECK(!prog, "find_probe",
			  "prog '%s' not found\n", probe_name))
			जाओ cleanup;


		अगर (test_हाल->btf_src_file) अणु
			err = access(test_हाल->btf_src_file, R_OK);
			अगर (!ASSERT_OK(err, "btf_src_file"))
				जाओ cleanup;
		पूर्ण

		load_attr.obj = obj;
		load_attr.log_level = 0;
		load_attr.target_btf_path = test_हाल->btf_src_file;
		err = bpf_object__load_xattr(&load_attr);
		अगर (err) अणु
			अगर (!test_हाल->fails)
				ASSERT_OK(err, "obj_load");
			जाओ cleanup;
		पूर्ण

		data_map = bpf_object__find_map_by_name(obj, "test_cor.bss");
		अगर (CHECK(!data_map, "find_data_map", "data map not found\n"))
			जाओ cleanup;

		mmap_data = mmap(शून्य, mmap_sz, PROT_READ | PROT_WRITE,
				 MAP_SHARED, bpf_map__fd(data_map), 0);
		अगर (CHECK(mmap_data == MAP_FAILED, "mmap",
			  ".bss mmap failed: %d", त्रुटि_सं)) अणु
			mmap_data = शून्य;
			जाओ cleanup;
		पूर्ण
		data = mmap_data;

		स_रखो(mmap_data, 0, माप(*data));
		स_नकल(data->in, test_हाल->input, test_हाल->input_len);
		data->my_pid_tgid = my_pid_tgid;

		link = bpf_program__attach_raw_tracepoपूर्णांक(prog, tp_name);
		अगर (CHECK(IS_ERR(link), "attach_raw_tp", "err %ld\n",
			  PTR_ERR(link)))
			जाओ cleanup;

		/* trigger test run */
		अगर (test_हाल->trigger) अणु
			अगर (!ASSERT_OK(test_हाल->trigger(test_हाल), "test_trigger"))
				जाओ cleanup;
		पूर्ण अन्यथा अणु
			usleep(1);
		पूर्ण

		अगर (data->skip) अणु
			test__skip();
			जाओ cleanup;
		पूर्ण

		अगर (!ASSERT_FALSE(test_हाल->fails, "obj_load_should_fail"))
			जाओ cleanup;

		equal = स_भेद(data->out, test_हाल->output,
			       test_हाल->output_len) == 0;
		अगर (CHECK(!equal, "check_result",
			  "input/output data don't match\n")) अणु
			पूर्णांक j;

			क्रम (j = 0; j < test_हाल->input_len; j++) अणु
				म_लिखो("input byte #%d: 0x%02hhx\n",
				       j, test_हाल->input[j]);
			पूर्ण
			क्रम (j = 0; j < test_हाल->output_len; j++) अणु
				म_लिखो("output byte #%d: EXP 0x%02hhx GOT 0x%02hhx\n",
				       j, test_हाल->output[j], data->out[j]);
			पूर्ण
			जाओ cleanup;
		पूर्ण

cleanup:
		अगर (mmap_data) अणु
			CHECK_FAIL(munmap(mmap_data, mmap_sz));
			mmap_data = शून्य;
		पूर्ण
		अगर (!IS_ERR_OR_शून्य(link)) अणु
			bpf_link__destroy(link);
			link = शून्य;
		पूर्ण
		bpf_object__बंद(obj);
	पूर्ण
पूर्ण
