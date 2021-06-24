<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020, Oracle and/or its affiliates. */

#समावेश "btf_ptr.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>
#समावेश <bpf/bpf_core_पढ़ो.h>

#समावेश <त्रुटिसं.स>

दीर्घ ret = 0;
पूर्णांक num_subtests = 0;
पूर्णांक ran_subtests = 0;
bool skip = false;

#घोषणा STRSIZE			2048
#घोषणा EXPECTED_STRSIZE	256

#अगर defined(bpf_target_s390)
/* शून्य poपूर्णांकs to a पढ़ोable काष्ठा lowcore on s390, so take the last page */
#घोषणा BADPTR			((व्योम *)0xFFFFFFFFFFFFF000ULL)
#अन्यथा
#घोषणा BADPTR			0
#पूर्ण_अगर

#अगर_अघोषित ARRAY_SIZE
#घोषणा ARRAY_SIZE(x)	(माप(x) / माप((x)[0]))
#पूर्ण_अगर

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, __u32);
	__type(value, अक्षर[STRSIZE]);
पूर्ण strdata SEC(".maps");

अटल पूर्णांक __म_भेदन(स्थिर व्योम *m1, स्थिर व्योम *m2, माप_प्रकार len)
अणु
	स्थिर अचिन्हित अक्षर *s1 = m1;
	स्थिर अचिन्हित अक्षर *s2 = m2;
	पूर्णांक i, delta = 0;

	क्रम (i = 0; i < len; i++) अणु
		delta = s1[i] - s2[i];
		अगर (delta || s1[i] == 0 || s2[i] == 0)
			अवरोध;
	पूर्ण
	वापस delta;
पूर्ण

#अगर __has_builtin(__builtin_btf_type_id)
#घोषणा	TEST_BTF(_str, _type, _flags, _expected, ...)			\
	करो अणु								\
		अटल स्थिर अक्षर _expectedval[EXPECTED_STRSIZE] =	\
							_expected;	\
		अटल स्थिर अक्षर _ptrtype[64] = #_type;		\
		__u64 _hflags = _flags | BTF_F_COMPACT;			\
		अटल _type _ptrdata = __VA_ARGS__;			\
		अटल काष्ठा btf_ptr _ptr = अणु पूर्ण;			\
		पूर्णांक _cmp;						\
									\
		++num_subtests;						\
		अगर (ret < 0)						\
			अवरोध;						\
		++ran_subtests;						\
		_ptr.ptr = &_ptrdata;					\
		_ptr.type_id = bpf_core_type_id_kernel(_type);		\
		अगर (_ptr.type_id <= 0) अणु				\
			ret = -EINVAL;					\
			अवरोध;						\
		पूर्ण							\
		ret = bpf_snम_लिखो_btf(_str, STRSIZE,			\
				       &_ptr, माप(_ptr), _hflags);	\
		अगर (ret)						\
			अवरोध;						\
		_cmp = __म_भेदन(_str, _expectedval, EXPECTED_STRSIZE);	\
		अगर (_cmp != 0) अणु					\
			bpf_prपूर्णांकk("(%d) got %s", _cmp, _str);		\
			bpf_prपूर्णांकk("(%d) expected %s", _cmp,		\
				   _expectedval);			\
			ret = -EBADMSG;					\
			अवरोध;						\
		पूर्ण							\
	पूर्ण जबतक (0)
#पूर्ण_अगर

/* Use where expected data string matches its stringअगरied declaration */
#घोषणा TEST_BTF_C(_str, _type, _flags, ...)				\
	TEST_BTF(_str, _type, _flags, "(" #_type ")" #__VA_ARGS__,	\
		 __VA_ARGS__)

/* TRACE_EVENT(netअगर_receive_skb,
 *	TP_PROTO(काष्ठा sk_buff *skb),
 */
SEC("tp_btf/netif_receive_skb")
पूर्णांक BPF_PROG(trace_netअगर_receive_skb, काष्ठा sk_buff *skb)
अणु
	अटल __u64 flags[] = अणु 0, BTF_F_COMPACT, BTF_F_ZERO, BTF_F_PTR_RAW,
				 BTF_F_NONAME, BTF_F_COMPACT | BTF_F_ZERO |
				 BTF_F_PTR_RAW | BTF_F_NONAME पूर्ण;
	अटल काष्ठा btf_ptr p = अणु पूर्ण;
	__u32 key = 0;
	पूर्णांक i, __ret;
	अक्षर *str;

#अगर __has_builtin(__builtin_btf_type_id)
	str = bpf_map_lookup_elem(&strdata, &key);
	अगर (!str)
		वापस 0;

	/* Ensure we can ग_लिखो skb string representation */
	p.type_id = bpf_core_type_id_kernel(काष्ठा sk_buff);
	p.ptr = skb;
	क्रम (i = 0; i < ARRAY_SIZE(flags); i++) अणु
		++num_subtests;
		ret = bpf_snम_लिखो_btf(str, STRSIZE, &p, माप(p), 0);
		अगर (ret < 0)
			bpf_prपूर्णांकk("returned %d when writing skb", ret);
		++ran_subtests;
	पूर्ण

	/* Check invalid ptr value */
	p.ptr = BADPTR;
	__ret = bpf_snम_लिखो_btf(str, STRSIZE, &p, माप(p), 0);
	अगर (__ret >= 0) अणु
		bpf_prपूर्णांकk("printing %llx should generate error, got (%d)",
			   (अचिन्हित दीर्घ दीर्घ)BADPTR, __ret);
		ret = -दुस्फल;
	पूर्ण

	/* Verअगरy type display क्रम various types. */

	/* simple पूर्णांक */
	TEST_BTF_C(str, पूर्णांक, 0, 1234);
	TEST_BTF(str, पूर्णांक, BTF_F_NONAME, "1234", 1234);
	/* zero value should be prपूर्णांकed at toplevel */
	TEST_BTF(str, पूर्णांक, 0, "(int)0", 0);
	TEST_BTF(str, पूर्णांक, BTF_F_NONAME, "0", 0);
	TEST_BTF(str, पूर्णांक, BTF_F_ZERO, "(int)0", 0);
	TEST_BTF(str, पूर्णांक, BTF_F_NONAME | BTF_F_ZERO, "0", 0);
	TEST_BTF_C(str, पूर्णांक, 0, -4567);
	TEST_BTF(str, पूर्णांक, BTF_F_NONAME, "-4567", -4567);

	/* simple अक्षर */
	TEST_BTF_C(str, अक्षर, 0, 100);
	TEST_BTF(str, अक्षर, BTF_F_NONAME, "100", 100);
	/* zero value should be prपूर्णांकed at toplevel */
	TEST_BTF(str, अक्षर, 0, "(char)0", 0);
	TEST_BTF(str, अक्षर, BTF_F_NONAME, "0", 0);
	TEST_BTF(str, अक्षर, BTF_F_ZERO, "(char)0", 0);
	TEST_BTF(str, अक्षर, BTF_F_NONAME | BTF_F_ZERO, "0", 0);

	/* simple प्रकार */
	TEST_BTF_C(str, uपूर्णांक64_t, 0, 100);
	TEST_BTF(str, u64, BTF_F_NONAME, "1", 1);
	/* zero value should be prपूर्णांकed at toplevel */
	TEST_BTF(str, u64, 0, "(u64)0", 0);
	TEST_BTF(str, u64, BTF_F_NONAME, "0", 0);
	TEST_BTF(str, u64, BTF_F_ZERO, "(u64)0", 0);
	TEST_BTF(str, u64, BTF_F_NONAME|BTF_F_ZERO, "0", 0);

	/* प्रकार काष्ठा */
	TEST_BTF_C(str, atomic_t, 0, अणु.counter = (पूर्णांक)1,पूर्ण);
	TEST_BTF(str, atomic_t, BTF_F_NONAME, "{1,}", अणु.counter = 1,पूर्ण);
	/* प्रकार with 0 value should be prपूर्णांकed at toplevel */
	TEST_BTF(str, atomic_t, 0, "(atomic_t){}", अणु.counter = 0,पूर्ण);
	TEST_BTF(str, atomic_t, BTF_F_NONAME, "{}", अणु.counter = 0,पूर्ण);
	TEST_BTF(str, atomic_t, BTF_F_ZERO, "(atomic_t){.counter = (int)0,}",
		 अणु.counter = 0,पूर्ण);
	TEST_BTF(str, atomic_t, BTF_F_NONAME|BTF_F_ZERO,
		 "{0,}", अणु.counter = 0,पूर्ण);

	/* क्रमागत where क्रमागत value करोes (and करोes not) exist */
	TEST_BTF_C(str, क्रमागत bpf_cmd, 0, BPF_MAP_CREATE);
	TEST_BTF(str, क्रमागत bpf_cmd, 0, "(enum bpf_cmd)BPF_MAP_CREATE", 0);
	TEST_BTF(str, क्रमागत bpf_cmd, BTF_F_NONAME, "BPF_MAP_CREATE",
		 BPF_MAP_CREATE);
	TEST_BTF(str, क्रमागत bpf_cmd, BTF_F_NONAME|BTF_F_ZERO,
		 "BPF_MAP_CREATE", 0);

	TEST_BTF(str, क्रमागत bpf_cmd, BTF_F_ZERO, "(enum bpf_cmd)BPF_MAP_CREATE",
		 BPF_MAP_CREATE);
	TEST_BTF(str, क्रमागत bpf_cmd, BTF_F_NONAME|BTF_F_ZERO,
		 "BPF_MAP_CREATE", BPF_MAP_CREATE);
	TEST_BTF_C(str, क्रमागत bpf_cmd, 0, 2000);
	TEST_BTF(str, क्रमागत bpf_cmd, BTF_F_NONAME, "2000", 2000);

	/* simple काष्ठा */
	TEST_BTF_C(str, काष्ठा btf_क्रमागत, 0,
		   अणु.name_off = (__u32)3,.val = (__s32)-1,पूर्ण);
	TEST_BTF(str, काष्ठा btf_क्रमागत, BTF_F_NONAME, "{3,-1,}",
		 अणु .name_off = 3, .val = -1,पूर्ण);
	TEST_BTF(str, काष्ठा btf_क्रमागत, BTF_F_NONAME, "{-1,}",
		 अणु .name_off = 0, .val = -1,पूर्ण);
	TEST_BTF(str, काष्ठा btf_क्रमागत, BTF_F_NONAME|BTF_F_ZERO, "{0,-1,}",
		 अणु .name_off = 0, .val = -1,पूर्ण);
	/* empty काष्ठा should be prपूर्णांकed */
	TEST_BTF(str, काष्ठा btf_क्रमागत, 0, "(struct btf_enum){}",
		 अणु .name_off = 0, .val = 0,पूर्ण);
	TEST_BTF(str, काष्ठा btf_क्रमागत, BTF_F_NONAME, "{}",
		 अणु .name_off = 0, .val = 0,पूर्ण);
	TEST_BTF(str, काष्ठा btf_क्रमागत, BTF_F_ZERO,
		 "(struct btf_enum){.name_off = (__u32)0,.val = (__s32)0,}",
		 अणु .name_off = 0, .val = 0,पूर्ण);

	/* काष्ठा with poपूर्णांकers */
	TEST_BTF(str, काष्ठा list_head, BTF_F_PTR_RAW,
		 "(struct list_head){.next = (struct list_head *)0x0000000000000001,}",
		 अणु .next = (काष्ठा list_head *)1 पूर्ण);
	/* शून्य poपूर्णांकer should not be displayed */
	TEST_BTF(str, काष्ठा list_head, BTF_F_PTR_RAW,
		 "(struct list_head){}",
		 अणु .next = (काष्ठा list_head *)0 पूर्ण);

	/* काष्ठा with अक्षर array */
	TEST_BTF(str, काष्ठा bpf_prog_info, 0,
		 "(struct bpf_prog_info){.name = (char[])['f','o','o',],}",
		 अणु .name = "foo",पूर्ण);
	TEST_BTF(str, काष्ठा bpf_prog_info, BTF_F_NONAME,
		 "{['f','o','o',],}",
		 अणु.name = "foo",पूर्ण);
	/* leading null अक्षर means करो not display string */
	TEST_BTF(str, काष्ठा bpf_prog_info, 0,
		 "(struct bpf_prog_info){}",
		 अणु.name = अणु'\0', 'f', 'o', 'o'पूर्णपूर्ण);
	/* handle non-prपूर्णांकable अक्षरacters */
	TEST_BTF(str, काष्ठा bpf_prog_info, 0,
		 "(struct bpf_prog_info){.name = (char[])[1,2,3,],}",
		 अणु .name = अणु1, 2, 3, 0पूर्णपूर्ण);

	/* काष्ठा with non-अक्षर array */
	TEST_BTF(str, काष्ठा __sk_buff, 0,
		 "(struct __sk_buff){.cb = (__u32[])[1,2,3,4,5,],}",
		 अणु .cb = अणु1, 2, 3, 4, 5,पूर्ण,पूर्ण);
	TEST_BTF(str, काष्ठा __sk_buff, BTF_F_NONAME,
		 "{[1,2,3,4,5,],}",
		 अणु .cb = अणु 1, 2, 3, 4, 5पूर्ण,पूर्ण);
	/* For non-अक्षर, arrays, show non-zero values only */
	TEST_BTF(str, काष्ठा __sk_buff, 0,
		 "(struct __sk_buff){.cb = (__u32[])[1,],}",
		 अणु .cb = अणु 0, 0, 1, 0, 0पूर्ण,पूर्ण);

	/* काष्ठा with bitfields */
	TEST_BTF_C(str, काष्ठा bpf_insn, 0,
		   अणु.code = (__u8)1,.dst_reg = (__u8)0x2,.src_reg = (__u8)0x3,.off = (__s16)4,.imm = (__s32)5,पूर्ण);
	TEST_BTF(str, काष्ठा bpf_insn, BTF_F_NONAME, "{1,0x2,0x3,4,5,}",
		 अणु.code = 1, .dst_reg = 0x2, .src_reg = 0x3, .off = 4,
		  .imm = 5,पूर्ण);
#अन्यथा
	skip = true;
#पूर्ण_अगर

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
