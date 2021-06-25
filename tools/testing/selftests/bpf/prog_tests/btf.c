<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2018 Facebook */

#समावेश <linux/bpf.h>
#समावेश <linux/btf.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/filter.h>
#समावेश <linux/unistd.h>
#समावेश <bpf/bpf.h>
#समावेश <sys/resource.h>
#समावेश <libelf.h>
#समावेश <gelf.h>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <मानकतर्क.स>
#समावेश <unistd.h>
#समावेश <fcntl.h>
#समावेश <त्रुटिसं.स>
#समावेश <निश्चित.स>
#समावेश <bpf/libbpf.h>
#समावेश <bpf/btf.h>

#समावेश "bpf_rlimit.h"
#समावेश "bpf_util.h"
#समावेश "../test_btf.h"
#समावेश "test_progs.h"

#घोषणा MAX_INSNS	512
#घोषणा MAX_SUBPROGS	16

अटल पूर्णांक duration = 0;
अटल bool always_log;

#अघोषित CHECK
#घोषणा CHECK(condition, क्रमmat...) _CHECK(condition, "check", duration, क्रमmat)

#घोषणा BTF_END_RAW 0xdeadbeef
#घोषणा NAME_TBD 0xdeadb33f

#घोषणा NAME_NTH(N) (0xffff0000 | N)
#घोषणा IS_NAME_NTH(X) ((X & 0xffff0000) == 0xffff0000)
#घोषणा GET_NAME_NTH_IDX(X) (X & 0x0000ffff)

#घोषणा MAX_NR_RAW_U32 1024
#घोषणा BTF_LOG_BUF_SIZE 65535

अटल अक्षर btf_log_buf[BTF_LOG_BUF_SIZE];

अटल काष्ठा btf_header hdr_पंचांगpl = अणु
	.magic = BTF_MAGIC,
	.version = BTF_VERSION,
	.hdr_len = माप(काष्ठा btf_header),
पूर्ण;

/* several dअगरferent mapv kinds(types) supported by pprपूर्णांक */
क्रमागत pprपूर्णांक_mapv_kind_t अणु
	PPRINT_MAPV_KIND_BASIC = 0,
	PPRINT_MAPV_KIND_INT128,
पूर्ण;

काष्ठा btf_raw_test अणु
	स्थिर अक्षर *descr;
	स्थिर अक्षर *str_sec;
	स्थिर अक्षर *map_name;
	स्थिर अक्षर *err_str;
	__u32 raw_types[MAX_NR_RAW_U32];
	__u32 str_sec_size;
	क्रमागत bpf_map_type map_type;
	__u32 key_size;
	__u32 value_size;
	__u32 key_type_id;
	__u32 value_type_id;
	__u32 max_entries;
	bool btf_load_err;
	bool map_create_err;
	bool ordered_map;
	bool lossless_map;
	bool percpu_map;
	पूर्णांक hdr_len_delta;
	पूर्णांक type_off_delta;
	पूर्णांक str_off_delta;
	पूर्णांक str_len_delta;
	क्रमागत pprपूर्णांक_mapv_kind_t mapv_kind;
पूर्ण;

#घोषणा BTF_STR_SEC(str) \
	.str_sec = str, .str_sec_size = माप(str)

अटल काष्ठा btf_raw_test raw_tests[] = अणु
/* क्रमागत E अणु
 *     E0,
 *     E1,
 * पूर्ण;
 *
 * काष्ठा A अणु
 *	अचिन्हित दीर्घ दीर्घ m;
 *	पूर्णांक n;
 *	अक्षर o;
 *	[3 bytes hole]
 *	पूर्णांक p[8];
 *	पूर्णांक q[4][8];
 *	क्रमागत E r;
 * पूर्ण;
 */
अणु
	.descr = "struct test #1",
	.raw_types = अणु
		/* पूर्णांक */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		/* अचिन्हित दीर्घ दीर्घ */
		BTF_TYPE_INT_ENC(0, 0, 0, 64, 8),		/* [2] */
		/* अक्षर */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 8, 1),	/* [3] */
		/* पूर्णांक[8] */
		BTF_TYPE_ARRAY_ENC(1, 1, 8),			/* [4] */
		/* काष्ठा A अणु */				/* [5] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 6), 180),
		BTF_MEMBER_ENC(NAME_TBD, 2, 0),	/* अचिन्हित दीर्घ दीर्घ m;*/
		BTF_MEMBER_ENC(NAME_TBD, 1, 64),/* पूर्णांक n;		*/
		BTF_MEMBER_ENC(NAME_TBD, 3, 96),/* अक्षर o;		*/
		BTF_MEMBER_ENC(NAME_TBD, 4, 128),/* पूर्णांक p[8]		*/
		BTF_MEMBER_ENC(NAME_TBD, 6, 384),/* पूर्णांक q[4][8]		*/
		BTF_MEMBER_ENC(NAME_TBD, 7, 1408), /* क्रमागत E r		*/
		/* पूर्ण */
		/* पूर्णांक[4][8] */
		BTF_TYPE_ARRAY_ENC(4, 1, 4),			/* [6] */
		/* क्रमागत E */					/* [7] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_ENUM, 0, 2), माप(पूर्णांक)),
		BTF_ENUM_ENC(NAME_TBD, 0),
		BTF_ENUM_ENC(NAME_TBD, 1),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0m\0n\0o\0p\0q\0r\0E\0E0\0E1",
	.str_sec_size = माप("\0A\0m\0n\0o\0p\0q\0r\0E\0E0\0E1"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "struct_test1_map",
	.key_size = माप(पूर्णांक),
	.value_size = 180,
	.key_type_id = 1,
	.value_type_id = 5,
	.max_entries = 4,
पूर्ण,

/* प्रकार काष्ठा b Struct_B;
 *
 * काष्ठा A अणु
 *     पूर्णांक m;
 *     काष्ठा b n[4];
 *     स्थिर Struct_B o[4];
 * पूर्ण;
 *
 * काष्ठा B अणु
 *     पूर्णांक m;
 *     पूर्णांक n;
 * पूर्ण;
 */
अणु
	.descr = "struct test #2",
	.raw_types = अणु
		/* पूर्णांक */					/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		/* काष्ठा b [4] */				/* [2] */
		BTF_TYPE_ARRAY_ENC(4, 1, 4),

		/* काष्ठा A अणु */				/* [3] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 3), 68),
		BTF_MEMBER_ENC(NAME_TBD, 1, 0),	/* पूर्णांक m;		*/
		BTF_MEMBER_ENC(NAME_TBD, 2, 32),/* काष्ठा B n[4]	*/
		BTF_MEMBER_ENC(NAME_TBD, 8, 288),/* स्थिर Struct_B o[4];*/
		/* पूर्ण */

		/* काष्ठा B अणु */				/* [4] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 2), 8),
		BTF_MEMBER_ENC(NAME_TBD, 1, 0),	/* पूर्णांक m; */
		BTF_MEMBER_ENC(NAME_TBD, 1, 32),/* पूर्णांक n; */
		/* पूर्ण */

		/* स्थिर पूर्णांक */					/* [5] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_CONST, 0, 0), 1),
		/* प्रकार काष्ठा b Struct_B */	/* [6] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_TYPEDEF, 0, 0), 4),
		/* स्थिर Struct_B */				/* [7] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_CONST, 0, 0), 6),
		/* स्थिर Struct_B [4] */			/* [8] */
		BTF_TYPE_ARRAY_ENC(7, 1, 4),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0m\0n\0o\0B\0m\0n\0Struct_B",
	.str_sec_size = माप("\0A\0m\0n\0o\0B\0m\0n\0Struct_B"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "struct_test2_map",
	.key_size = माप(पूर्णांक),
	.value_size = 68,
	.key_type_id = 1,
	.value_type_id = 3,
	.max_entries = 4,
पूर्ण,
अणु
	.descr = "struct test #3 Invalid member offset",
	.raw_types = अणु
		/* पूर्णांक */					/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		/* पूर्णांक64 */					/* [2] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 64, 8),

		/* काष्ठा A अणु */				/* [3] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 2), 16),
		BTF_MEMBER_ENC(NAME_TBD, 1, 64),	/* पूर्णांक m;		*/
		BTF_MEMBER_ENC(NAME_TBD, 2, 0),		/* पूर्णांक64 n; */
		/* पूर्ण */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0m\0n\0",
	.str_sec_size = माप("\0A\0m\0n\0"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "struct_test3_map",
	.key_size = माप(पूर्णांक),
	.value_size = 16,
	.key_type_id = 1,
	.value_type_id = 3,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid member bits_offset",
पूर्ण,
/*
 * काष्ठा A अणु
 *	अचिन्हित दीर्घ दीर्घ m;
 *	पूर्णांक n;
 *	अक्षर o;
 *	[3 bytes hole]
 *	पूर्णांक p[8];
 * पूर्ण;
 */
अणु
	.descr = "global data test #1",
	.raw_types = अणु
		/* पूर्णांक */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		/* अचिन्हित दीर्घ दीर्घ */
		BTF_TYPE_INT_ENC(0, 0, 0, 64, 8),		/* [2] */
		/* अक्षर */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 8, 1),	/* [3] */
		/* पूर्णांक[8] */
		BTF_TYPE_ARRAY_ENC(1, 1, 8),			/* [4] */
		/* काष्ठा A अणु */				/* [5] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 4), 48),
		BTF_MEMBER_ENC(NAME_TBD, 2, 0),	/* अचिन्हित दीर्घ दीर्घ m;*/
		BTF_MEMBER_ENC(NAME_TBD, 1, 64),/* पूर्णांक n;		*/
		BTF_MEMBER_ENC(NAME_TBD, 3, 96),/* अक्षर o;		*/
		BTF_MEMBER_ENC(NAME_TBD, 4, 128),/* पूर्णांक p[8]		*/
		/* पूर्ण */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0m\0n\0o\0p",
	.str_sec_size = माप("\0A\0m\0n\0o\0p"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "struct_test1_map",
	.key_size = माप(पूर्णांक),
	.value_size = 48,
	.key_type_id = 1,
	.value_type_id = 5,
	.max_entries = 4,
पूर्ण,
/*
 * काष्ठा A अणु
 *	अचिन्हित दीर्घ दीर्घ m;
 *	पूर्णांक n;
 *	अक्षर o;
 *	[3 bytes hole]
 *	पूर्णांक p[8];
 * पूर्ण;
 * अटल काष्ठा A t; <- in .bss
 */
अणु
	.descr = "global data test #2",
	.raw_types = अणु
		/* पूर्णांक */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		/* अचिन्हित दीर्घ दीर्घ */
		BTF_TYPE_INT_ENC(0, 0, 0, 64, 8),		/* [2] */
		/* अक्षर */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 8, 1),	/* [3] */
		/* पूर्णांक[8] */
		BTF_TYPE_ARRAY_ENC(1, 1, 8),			/* [4] */
		/* काष्ठा A अणु */				/* [5] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 4), 48),
		BTF_MEMBER_ENC(NAME_TBD, 2, 0),	/* अचिन्हित दीर्घ दीर्घ m;*/
		BTF_MEMBER_ENC(NAME_TBD, 1, 64),/* पूर्णांक n;		*/
		BTF_MEMBER_ENC(NAME_TBD, 3, 96),/* अक्षर o;		*/
		BTF_MEMBER_ENC(NAME_TBD, 4, 128),/* पूर्णांक p[8]		*/
		/* पूर्ण */
		/* अटल काष्ठा A t */
		BTF_VAR_ENC(NAME_TBD, 5, 0),			/* [6] */
		/* .bss section */				/* [7] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_DATASEC, 0, 1), 48),
		BTF_VAR_SECINFO_ENC(6, 0, 48),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0m\0n\0o\0p\0t\0.bss",
	.str_sec_size = माप("\0A\0m\0n\0o\0p\0t\0.bss"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = ".bss",
	.key_size = माप(पूर्णांक),
	.value_size = 48,
	.key_type_id = 0,
	.value_type_id = 7,
	.max_entries = 1,
पूर्ण,
अणु
	.descr = "global data test #3",
	.raw_types = अणु
		/* पूर्णांक */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		/* अटल पूर्णांक t */
		BTF_VAR_ENC(NAME_TBD, 1, 0),			/* [2] */
		/* .bss section */				/* [3] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_DATASEC, 0, 1), 4),
		BTF_VAR_SECINFO_ENC(2, 0, 4),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0t\0.bss",
	.str_sec_size = माप("\0t\0.bss"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = ".bss",
	.key_size = माप(पूर्णांक),
	.value_size = 4,
	.key_type_id = 0,
	.value_type_id = 3,
	.max_entries = 1,
पूर्ण,
अणु
	.descr = "global data test #4, unsupported linkage",
	.raw_types = अणु
		/* पूर्णांक */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		/* अटल पूर्णांक t */
		BTF_VAR_ENC(NAME_TBD, 1, 2),			/* [2] */
		/* .bss section */				/* [3] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_DATASEC, 0, 1), 4),
		BTF_VAR_SECINFO_ENC(2, 0, 4),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0t\0.bss",
	.str_sec_size = माप("\0t\0.bss"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = ".bss",
	.key_size = माप(पूर्णांक),
	.value_size = 4,
	.key_type_id = 0,
	.value_type_id = 3,
	.max_entries = 1,
	.btf_load_err = true,
	.err_str = "Linkage not supported",
पूर्ण,
अणु
	.descr = "global data test #5, invalid var type",
	.raw_types = अणु
		/* अटल व्योम t */
		BTF_VAR_ENC(NAME_TBD, 0, 0),			/* [1] */
		/* .bss section */				/* [2] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_DATASEC, 0, 1), 4),
		BTF_VAR_SECINFO_ENC(1, 0, 4),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0t\0.bss",
	.str_sec_size = माप("\0t\0.bss"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = ".bss",
	.key_size = माप(पूर्णांक),
	.value_size = 4,
	.key_type_id = 0,
	.value_type_id = 2,
	.max_entries = 1,
	.btf_load_err = true,
	.err_str = "Invalid type_id",
पूर्ण,
अणु
	.descr = "global data test #6, invalid var type (fwd type)",
	.raw_types = अणु
		/* जोड़ A */
		BTF_TYPE_ENC(NAME_TBD,
			     BTF_INFO_ENC(BTF_KIND_FWD, 1, 0), 0), /* [1] */
		/* अटल जोड़ A t */
		BTF_VAR_ENC(NAME_TBD, 1, 0),			/* [2] */
		/* .bss section */				/* [3] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_DATASEC, 0, 1), 4),
		BTF_VAR_SECINFO_ENC(2, 0, 4),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0t\0.bss",
	.str_sec_size = माप("\0A\0t\0.bss"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = ".bss",
	.key_size = माप(पूर्णांक),
	.value_size = 4,
	.key_type_id = 0,
	.value_type_id = 2,
	.max_entries = 1,
	.btf_load_err = true,
	.err_str = "Invalid type",
पूर्ण,
अणु
	.descr = "global data test #7, invalid var type (fwd type)",
	.raw_types = अणु
		/* जोड़ A */
		BTF_TYPE_ENC(NAME_TBD,
			     BTF_INFO_ENC(BTF_KIND_FWD, 1, 0), 0), /* [1] */
		/* अटल जोड़ A t */
		BTF_VAR_ENC(NAME_TBD, 1, 0),			/* [2] */
		/* .bss section */				/* [3] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_DATASEC, 0, 1), 4),
		BTF_VAR_SECINFO_ENC(1, 0, 4),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0t\0.bss",
	.str_sec_size = माप("\0A\0t\0.bss"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = ".bss",
	.key_size = माप(पूर्णांक),
	.value_size = 4,
	.key_type_id = 0,
	.value_type_id = 2,
	.max_entries = 1,
	.btf_load_err = true,
	.err_str = "Invalid type",
पूर्ण,
अणु
	.descr = "global data test #8, invalid var size",
	.raw_types = अणु
		/* पूर्णांक */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		/* अचिन्हित दीर्घ दीर्घ */
		BTF_TYPE_INT_ENC(0, 0, 0, 64, 8),		/* [2] */
		/* अक्षर */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 8, 1),	/* [3] */
		/* पूर्णांक[8] */
		BTF_TYPE_ARRAY_ENC(1, 1, 8),			/* [4] */
		/* काष्ठा A अणु */				/* [5] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 4), 48),
		BTF_MEMBER_ENC(NAME_TBD, 2, 0),	/* अचिन्हित दीर्घ दीर्घ m;*/
		BTF_MEMBER_ENC(NAME_TBD, 1, 64),/* पूर्णांक n;		*/
		BTF_MEMBER_ENC(NAME_TBD, 3, 96),/* अक्षर o;		*/
		BTF_MEMBER_ENC(NAME_TBD, 4, 128),/* पूर्णांक p[8]		*/
		/* पूर्ण */
		/* अटल काष्ठा A t */
		BTF_VAR_ENC(NAME_TBD, 5, 0),			/* [6] */
		/* .bss section */				/* [7] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_DATASEC, 0, 1), 48),
		BTF_VAR_SECINFO_ENC(6, 0, 47),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0m\0n\0o\0p\0t\0.bss",
	.str_sec_size = माप("\0A\0m\0n\0o\0p\0t\0.bss"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = ".bss",
	.key_size = माप(पूर्णांक),
	.value_size = 48,
	.key_type_id = 0,
	.value_type_id = 7,
	.max_entries = 1,
	.btf_load_err = true,
	.err_str = "Invalid size",
पूर्ण,
अणु
	.descr = "global data test #9, invalid var size",
	.raw_types = अणु
		/* पूर्णांक */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		/* अचिन्हित दीर्घ दीर्घ */
		BTF_TYPE_INT_ENC(0, 0, 0, 64, 8),		/* [2] */
		/* अक्षर */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 8, 1),	/* [3] */
		/* पूर्णांक[8] */
		BTF_TYPE_ARRAY_ENC(1, 1, 8),			/* [4] */
		/* काष्ठा A अणु */				/* [5] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 4), 48),
		BTF_MEMBER_ENC(NAME_TBD, 2, 0),	/* अचिन्हित दीर्घ दीर्घ m;*/
		BTF_MEMBER_ENC(NAME_TBD, 1, 64),/* पूर्णांक n;		*/
		BTF_MEMBER_ENC(NAME_TBD, 3, 96),/* अक्षर o;		*/
		BTF_MEMBER_ENC(NAME_TBD, 4, 128),/* पूर्णांक p[8]		*/
		/* पूर्ण */
		/* अटल काष्ठा A t */
		BTF_VAR_ENC(NAME_TBD, 5, 0),			/* [6] */
		/* .bss section */				/* [7] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_DATASEC, 0, 1), 46),
		BTF_VAR_SECINFO_ENC(6, 0, 48),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0m\0n\0o\0p\0t\0.bss",
	.str_sec_size = माप("\0A\0m\0n\0o\0p\0t\0.bss"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = ".bss",
	.key_size = माप(पूर्णांक),
	.value_size = 48,
	.key_type_id = 0,
	.value_type_id = 7,
	.max_entries = 1,
	.btf_load_err = true,
	.err_str = "Invalid size",
पूर्ण,
अणु
	.descr = "global data test #10, invalid var size",
	.raw_types = अणु
		/* पूर्णांक */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		/* अचिन्हित दीर्घ दीर्घ */
		BTF_TYPE_INT_ENC(0, 0, 0, 64, 8),		/* [2] */
		/* अक्षर */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 8, 1),	/* [3] */
		/* पूर्णांक[8] */
		BTF_TYPE_ARRAY_ENC(1, 1, 8),			/* [4] */
		/* काष्ठा A अणु */				/* [5] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 4), 48),
		BTF_MEMBER_ENC(NAME_TBD, 2, 0),	/* अचिन्हित दीर्घ दीर्घ m;*/
		BTF_MEMBER_ENC(NAME_TBD, 1, 64),/* पूर्णांक n;		*/
		BTF_MEMBER_ENC(NAME_TBD, 3, 96),/* अक्षर o;		*/
		BTF_MEMBER_ENC(NAME_TBD, 4, 128),/* पूर्णांक p[8]		*/
		/* पूर्ण */
		/* अटल काष्ठा A t */
		BTF_VAR_ENC(NAME_TBD, 5, 0),			/* [6] */
		/* .bss section */				/* [7] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_DATASEC, 0, 1), 46),
		BTF_VAR_SECINFO_ENC(6, 0, 46),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0m\0n\0o\0p\0t\0.bss",
	.str_sec_size = माप("\0A\0m\0n\0o\0p\0t\0.bss"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = ".bss",
	.key_size = माप(पूर्णांक),
	.value_size = 48,
	.key_type_id = 0,
	.value_type_id = 7,
	.max_entries = 1,
	.btf_load_err = true,
	.err_str = "Invalid size",
पूर्ण,
अणु
	.descr = "global data test #11, multiple section members",
	.raw_types = अणु
		/* पूर्णांक */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		/* अचिन्हित दीर्घ दीर्घ */
		BTF_TYPE_INT_ENC(0, 0, 0, 64, 8),		/* [2] */
		/* अक्षर */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 8, 1),	/* [3] */
		/* पूर्णांक[8] */
		BTF_TYPE_ARRAY_ENC(1, 1, 8),			/* [4] */
		/* काष्ठा A अणु */				/* [5] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 4), 48),
		BTF_MEMBER_ENC(NAME_TBD, 2, 0),	/* अचिन्हित दीर्घ दीर्घ m;*/
		BTF_MEMBER_ENC(NAME_TBD, 1, 64),/* पूर्णांक n;		*/
		BTF_MEMBER_ENC(NAME_TBD, 3, 96),/* अक्षर o;		*/
		BTF_MEMBER_ENC(NAME_TBD, 4, 128),/* पूर्णांक p[8]		*/
		/* पूर्ण */
		/* अटल काष्ठा A t */
		BTF_VAR_ENC(NAME_TBD, 5, 0),			/* [6] */
		/* अटल पूर्णांक u */
		BTF_VAR_ENC(NAME_TBD, 1, 0),			/* [7] */
		/* .bss section */				/* [8] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_DATASEC, 0, 2), 62),
		BTF_VAR_SECINFO_ENC(6, 10, 48),
		BTF_VAR_SECINFO_ENC(7, 58, 4),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0m\0n\0o\0p\0t\0u\0.bss",
	.str_sec_size = माप("\0A\0m\0n\0o\0p\0t\0u\0.bss"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = ".bss",
	.key_size = माप(पूर्णांक),
	.value_size = 62,
	.key_type_id = 0,
	.value_type_id = 8,
	.max_entries = 1,
पूर्ण,
अणु
	.descr = "global data test #12, invalid offset",
	.raw_types = अणु
		/* पूर्णांक */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		/* अचिन्हित दीर्घ दीर्घ */
		BTF_TYPE_INT_ENC(0, 0, 0, 64, 8),		/* [2] */
		/* अक्षर */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 8, 1),	/* [3] */
		/* पूर्णांक[8] */
		BTF_TYPE_ARRAY_ENC(1, 1, 8),			/* [4] */
		/* काष्ठा A अणु */				/* [5] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 4), 48),
		BTF_MEMBER_ENC(NAME_TBD, 2, 0),	/* अचिन्हित दीर्घ दीर्घ m;*/
		BTF_MEMBER_ENC(NAME_TBD, 1, 64),/* पूर्णांक n;		*/
		BTF_MEMBER_ENC(NAME_TBD, 3, 96),/* अक्षर o;		*/
		BTF_MEMBER_ENC(NAME_TBD, 4, 128),/* पूर्णांक p[8]		*/
		/* पूर्ण */
		/* अटल काष्ठा A t */
		BTF_VAR_ENC(NAME_TBD, 5, 0),			/* [6] */
		/* अटल पूर्णांक u */
		BTF_VAR_ENC(NAME_TBD, 1, 0),			/* [7] */
		/* .bss section */				/* [8] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_DATASEC, 0, 2), 62),
		BTF_VAR_SECINFO_ENC(6, 10, 48),
		BTF_VAR_SECINFO_ENC(7, 60, 4),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0m\0n\0o\0p\0t\0u\0.bss",
	.str_sec_size = माप("\0A\0m\0n\0o\0p\0t\0u\0.bss"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = ".bss",
	.key_size = माप(पूर्णांक),
	.value_size = 62,
	.key_type_id = 0,
	.value_type_id = 8,
	.max_entries = 1,
	.btf_load_err = true,
	.err_str = "Invalid offset+size",
पूर्ण,
अणु
	.descr = "global data test #13, invalid offset",
	.raw_types = अणु
		/* पूर्णांक */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		/* अचिन्हित दीर्घ दीर्घ */
		BTF_TYPE_INT_ENC(0, 0, 0, 64, 8),		/* [2] */
		/* अक्षर */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 8, 1),	/* [3] */
		/* पूर्णांक[8] */
		BTF_TYPE_ARRAY_ENC(1, 1, 8),			/* [4] */
		/* काष्ठा A अणु */				/* [5] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 4), 48),
		BTF_MEMBER_ENC(NAME_TBD, 2, 0),	/* अचिन्हित दीर्घ दीर्घ m;*/
		BTF_MEMBER_ENC(NAME_TBD, 1, 64),/* पूर्णांक n;		*/
		BTF_MEMBER_ENC(NAME_TBD, 3, 96),/* अक्षर o;		*/
		BTF_MEMBER_ENC(NAME_TBD, 4, 128),/* पूर्णांक p[8]		*/
		/* पूर्ण */
		/* अटल काष्ठा A t */
		BTF_VAR_ENC(NAME_TBD, 5, 0),			/* [6] */
		/* अटल पूर्णांक u */
		BTF_VAR_ENC(NAME_TBD, 1, 0),			/* [7] */
		/* .bss section */				/* [8] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_DATASEC, 0, 2), 62),
		BTF_VAR_SECINFO_ENC(6, 10, 48),
		BTF_VAR_SECINFO_ENC(7, 12, 4),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0m\0n\0o\0p\0t\0u\0.bss",
	.str_sec_size = माप("\0A\0m\0n\0o\0p\0t\0u\0.bss"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = ".bss",
	.key_size = माप(पूर्णांक),
	.value_size = 62,
	.key_type_id = 0,
	.value_type_id = 8,
	.max_entries = 1,
	.btf_load_err = true,
	.err_str = "Invalid offset",
पूर्ण,
अणु
	.descr = "global data test #14, invalid offset",
	.raw_types = अणु
		/* पूर्णांक */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		/* अचिन्हित दीर्घ दीर्घ */
		BTF_TYPE_INT_ENC(0, 0, 0, 64, 8),		/* [2] */
		/* अक्षर */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 8, 1),	/* [3] */
		/* पूर्णांक[8] */
		BTF_TYPE_ARRAY_ENC(1, 1, 8),			/* [4] */
		/* काष्ठा A अणु */				/* [5] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 4), 48),
		BTF_MEMBER_ENC(NAME_TBD, 2, 0),	/* अचिन्हित दीर्घ दीर्घ m;*/
		BTF_MEMBER_ENC(NAME_TBD, 1, 64),/* पूर्णांक n;		*/
		BTF_MEMBER_ENC(NAME_TBD, 3, 96),/* अक्षर o;		*/
		BTF_MEMBER_ENC(NAME_TBD, 4, 128),/* पूर्णांक p[8]		*/
		/* पूर्ण */
		/* अटल काष्ठा A t */
		BTF_VAR_ENC(NAME_TBD, 5, 0),			/* [6] */
		/* अटल पूर्णांक u */
		BTF_VAR_ENC(NAME_TBD, 1, 0),			/* [7] */
		/* .bss section */				/* [8] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_DATASEC, 0, 2), 62),
		BTF_VAR_SECINFO_ENC(7, 58, 4),
		BTF_VAR_SECINFO_ENC(6, 10, 48),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0m\0n\0o\0p\0t\0u\0.bss",
	.str_sec_size = माप("\0A\0m\0n\0o\0p\0t\0u\0.bss"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = ".bss",
	.key_size = माप(पूर्णांक),
	.value_size = 62,
	.key_type_id = 0,
	.value_type_id = 8,
	.max_entries = 1,
	.btf_load_err = true,
	.err_str = "Invalid offset",
पूर्ण,
अणु
	.descr = "global data test #15, not var kind",
	.raw_types = अणु
		/* पूर्णांक */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_VAR_ENC(NAME_TBD, 1, 0),			/* [2] */
		/* .bss section */				/* [3] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_DATASEC, 0, 1), 4),
		BTF_VAR_SECINFO_ENC(1, 0, 4),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0t\0.bss",
	.str_sec_size = माप("\0A\0t\0.bss"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = ".bss",
	.key_size = माप(पूर्णांक),
	.value_size = 4,
	.key_type_id = 0,
	.value_type_id = 3,
	.max_entries = 1,
	.btf_load_err = true,
	.err_str = "Not a VAR kind member",
पूर्ण,
अणु
	.descr = "global data test #16, invalid var referencing sec",
	.raw_types = अणु
		/* पूर्णांक */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_VAR_ENC(NAME_TBD, 5, 0),			/* [2] */
		BTF_VAR_ENC(NAME_TBD, 2, 0),			/* [3] */
		/* a section */					/* [4] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_DATASEC, 0, 1), 4),
		BTF_VAR_SECINFO_ENC(3, 0, 4),
		/* a section */					/* [5] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_DATASEC, 0, 1), 4),
		BTF_VAR_SECINFO_ENC(6, 0, 4),
		BTF_VAR_ENC(NAME_TBD, 1, 0),			/* [6] */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0t\0s\0a\0a",
	.str_sec_size = माप("\0A\0t\0s\0a\0a"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = ".bss",
	.key_size = माप(पूर्णांक),
	.value_size = 4,
	.key_type_id = 0,
	.value_type_id = 4,
	.max_entries = 1,
	.btf_load_err = true,
	.err_str = "Invalid type_id",
पूर्ण,
अणु
	.descr = "global data test #17, invalid var referencing var",
	.raw_types = अणु
		/* पूर्णांक */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_VAR_ENC(NAME_TBD, 1, 0),			/* [2] */
		BTF_VAR_ENC(NAME_TBD, 2, 0),			/* [3] */
		/* a section */					/* [4] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_DATASEC, 0, 1), 4),
		BTF_VAR_SECINFO_ENC(3, 0, 4),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0t\0s\0a\0a",
	.str_sec_size = माप("\0A\0t\0s\0a\0a"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = ".bss",
	.key_size = माप(पूर्णांक),
	.value_size = 4,
	.key_type_id = 0,
	.value_type_id = 4,
	.max_entries = 1,
	.btf_load_err = true,
	.err_str = "Invalid type_id",
पूर्ण,
अणु
	.descr = "global data test #18, invalid var loop",
	.raw_types = अणु
		/* पूर्णांक */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_VAR_ENC(NAME_TBD, 2, 0),			/* [2] */
		/* .bss section */				/* [3] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_DATASEC, 0, 1), 4),
		BTF_VAR_SECINFO_ENC(2, 0, 4),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0t\0aaa",
	.str_sec_size = माप("\0A\0t\0aaa"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = ".bss",
	.key_size = माप(पूर्णांक),
	.value_size = 4,
	.key_type_id = 0,
	.value_type_id = 4,
	.max_entries = 1,
	.btf_load_err = true,
	.err_str = "Invalid type_id",
पूर्ण,
अणु
	.descr = "global data test #19, invalid var referencing var",
	.raw_types = अणु
		/* पूर्णांक */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_VAR_ENC(NAME_TBD, 3, 0),			/* [2] */
		BTF_VAR_ENC(NAME_TBD, 1, 0),			/* [3] */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0t\0s\0a\0a",
	.str_sec_size = माप("\0A\0t\0s\0a\0a"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = ".bss",
	.key_size = माप(पूर्णांक),
	.value_size = 4,
	.key_type_id = 0,
	.value_type_id = 4,
	.max_entries = 1,
	.btf_load_err = true,
	.err_str = "Invalid type_id",
पूर्ण,
अणु
	.descr = "global data test #20, invalid ptr referencing var",
	.raw_types = अणु
		/* पूर्णांक */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		/* PTR type_id=3	*/			/* [2] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_PTR, 0, 0), 3),
		BTF_VAR_ENC(NAME_TBD, 1, 0),			/* [3] */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0t\0s\0a\0a",
	.str_sec_size = माप("\0A\0t\0s\0a\0a"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = ".bss",
	.key_size = माप(पूर्णांक),
	.value_size = 4,
	.key_type_id = 0,
	.value_type_id = 4,
	.max_entries = 1,
	.btf_load_err = true,
	.err_str = "Invalid type_id",
पूर्ण,
अणु
	.descr = "global data test #21, var included in struct",
	.raw_types = अणु
		/* पूर्णांक */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		/* काष्ठा A अणु */				/* [2] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 2), माप(पूर्णांक) * 2),
		BTF_MEMBER_ENC(NAME_TBD, 1, 0),	/* पूर्णांक m; */
		BTF_MEMBER_ENC(NAME_TBD, 3, 32),/* VAR type_id=3; */
		/* पूर्ण */
		BTF_VAR_ENC(NAME_TBD, 1, 0),			/* [3] */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0t\0s\0a\0a",
	.str_sec_size = माप("\0A\0t\0s\0a\0a"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = ".bss",
	.key_size = माप(पूर्णांक),
	.value_size = 4,
	.key_type_id = 0,
	.value_type_id = 4,
	.max_entries = 1,
	.btf_load_err = true,
	.err_str = "Invalid member",
पूर्ण,
अणु
	.descr = "global data test #22, array of var",
	.raw_types = अणु
		/* पूर्णांक */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_TYPE_ARRAY_ENC(3, 1, 4),			/* [2] */
		BTF_VAR_ENC(NAME_TBD, 1, 0),			/* [3] */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0t\0s\0a\0a",
	.str_sec_size = माप("\0A\0t\0s\0a\0a"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = ".bss",
	.key_size = माप(पूर्णांक),
	.value_size = 4,
	.key_type_id = 0,
	.value_type_id = 4,
	.max_entries = 1,
	.btf_load_err = true,
	.err_str = "Invalid elem",
पूर्ण,
/* Test member exceeds the size of काष्ठा.
 *
 * काष्ठा A अणु
 *     पूर्णांक m;
 *     पूर्णांक n;
 * पूर्ण;
 */
अणु
	.descr = "size check test #1",
	.raw_types = अणु
		/* पूर्णांक */					/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		/* काष्ठा A अणु */				/* [2] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 2), माप(पूर्णांक) * 2 -  1),
		BTF_MEMBER_ENC(NAME_TBD, 1, 0),	/* पूर्णांक m; */
		BTF_MEMBER_ENC(NAME_TBD, 1, 32),/* पूर्णांक n; */
		/* पूर्ण */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0m\0n",
	.str_sec_size = माप("\0A\0m\0n"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "size_check1_map",
	.key_size = माप(पूर्णांक),
	.value_size = 1,
	.key_type_id = 1,
	.value_type_id = 2,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Member exceeds struct_size",
पूर्ण,

/* Test member exceeds the size of काष्ठा
 *
 * काष्ठा A अणु
 *     पूर्णांक m;
 *     पूर्णांक n[2];
 * पूर्ण;
 */
अणु
	.descr = "size check test #2",
	.raw_types = अणु
		/* पूर्णांक */					/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, माप(पूर्णांक)),
		/* पूर्णांक[2] */					/* [2] */
		BTF_TYPE_ARRAY_ENC(1, 1, 2),
		/* काष्ठा A अणु */				/* [3] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 2), माप(पूर्णांक) * 3 - 1),
		BTF_MEMBER_ENC(NAME_TBD, 1, 0),	/* पूर्णांक m; */
		BTF_MEMBER_ENC(NAME_TBD, 2, 32),/* पूर्णांक n[2]; */
		/* पूर्ण */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0m\0n",
	.str_sec_size = माप("\0A\0m\0n"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "size_check2_map",
	.key_size = माप(पूर्णांक),
	.value_size = 1,
	.key_type_id = 1,
	.value_type_id = 3,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Member exceeds struct_size",
पूर्ण,

/* Test member exceeds the size of काष्ठा
 *
 * काष्ठा A अणु
 *     पूर्णांक m;
 *     व्योम *n;
 * पूर्ण;
 */
अणु
	.descr = "size check test #3",
	.raw_types = अणु
		/* पूर्णांक */					/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, माप(पूर्णांक)),
		/* व्योम* */					/* [2] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_PTR, 0, 0), 0),
		/* काष्ठा A अणु */				/* [3] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 2), माप(पूर्णांक) + माप(व्योम *) - 1),
		BTF_MEMBER_ENC(NAME_TBD, 1, 0),	/* पूर्णांक m; */
		BTF_MEMBER_ENC(NAME_TBD, 2, 32),/* व्योम *n; */
		/* पूर्ण */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0m\0n",
	.str_sec_size = माप("\0A\0m\0n"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "size_check3_map",
	.key_size = माप(पूर्णांक),
	.value_size = 1,
	.key_type_id = 1,
	.value_type_id = 3,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Member exceeds struct_size",
पूर्ण,

/* Test member exceeds the size of काष्ठा
 *
 * क्रमागत E अणु
 *     E0,
 *     E1,
 * पूर्ण;
 *
 * काष्ठा A अणु
 *     पूर्णांक m;
 *     क्रमागत E n;
 * पूर्ण;
 */
अणु
	.descr = "size check test #4",
	.raw_types = अणु
		/* पूर्णांक */			/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, माप(पूर्णांक)),
		/* क्रमागत E अणु */			/* [2] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_ENUM, 0, 2), माप(पूर्णांक)),
		BTF_ENUM_ENC(NAME_TBD, 0),
		BTF_ENUM_ENC(NAME_TBD, 1),
		/* पूर्ण */
		/* काष्ठा A अणु */		/* [3] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 2), माप(पूर्णांक) * 2 - 1),
		BTF_MEMBER_ENC(NAME_TBD, 1, 0),	/* पूर्णांक m; */
		BTF_MEMBER_ENC(NAME_TBD, 2, 32),/* क्रमागत E n; */
		/* पूर्ण */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0E\0E0\0E1\0A\0m\0n",
	.str_sec_size = माप("\0E\0E0\0E1\0A\0m\0n"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "size_check4_map",
	.key_size = माप(पूर्णांक),
	.value_size = 1,
	.key_type_id = 1,
	.value_type_id = 3,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Member exceeds struct_size",
पूर्ण,

/* Test member unexceeds the size of काष्ठा
 *
 * क्रमागत E अणु
 *     E0,
 *     E1,
 * पूर्ण;
 *
 * काष्ठा A अणु
 *     अक्षर m;
 *     क्रमागत E __attribute__((packed)) n;
 * पूर्ण;
 */
अणु
	.descr = "size check test #5",
	.raw_types = अणु
		/* पूर्णांक */			/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, माप(पूर्णांक)),
		/* अक्षर */			/* [2] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 8, 1),
		/* क्रमागत E अणु */			/* [3] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_ENUM, 0, 2), 1),
		BTF_ENUM_ENC(NAME_TBD, 0),
		BTF_ENUM_ENC(NAME_TBD, 1),
		/* पूर्ण */
		/* काष्ठा A अणु */		/* [4] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 2), 2),
		BTF_MEMBER_ENC(NAME_TBD, 2, 0),	/* अक्षर m; */
		BTF_MEMBER_ENC(NAME_TBD, 3, 8),/* क्रमागत E __attribute__((packed)) n; */
		/* पूर्ण */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0E\0E0\0E1\0A\0m\0n",
	.str_sec_size = माप("\0E\0E0\0E1\0A\0m\0n"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "size_check5_map",
	.key_size = माप(पूर्णांक),
	.value_size = 2,
	.key_type_id = 1,
	.value_type_id = 4,
	.max_entries = 4,
पूर्ण,

/* प्रकार स्थिर व्योम * स्थिर_व्योम_ptr;
 * काष्ठा A अणु
 *	स्थिर_व्योम_ptr m;
 * पूर्ण;
 */
अणु
	.descr = "void test #1",
	.raw_types = अणु
		/* पूर्णांक */		/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		/* स्थिर व्योम */	/* [2] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_CONST, 0, 0), 0),
		/* स्थिर व्योम* */	/* [3] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_PTR, 0, 0), 2),
		/* प्रकार स्थिर व्योम * स्थिर_व्योम_ptr */
		BTF_TYPEDEF_ENC(NAME_TBD, 3),	/* [4] */
		/* काष्ठा A अणु */	/* [5] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 1), माप(व्योम *)),
		/* स्थिर_व्योम_ptr m; */
		BTF_MEMBER_ENC(NAME_TBD, 4, 0),
		/* पूर्ण */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0const_void_ptr\0A\0m",
	.str_sec_size = माप("\0const_void_ptr\0A\0m"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "void_test1_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(व्योम *),
	.key_type_id = 1,
	.value_type_id = 4,
	.max_entries = 4,
पूर्ण,

/* काष्ठा A अणु
 *     स्थिर व्योम m;
 * पूर्ण;
 */
अणु
	.descr = "void test #2",
	.raw_types = अणु
		/* पूर्णांक */		/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		/* स्थिर व्योम */	/* [2] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_CONST, 0, 0), 0),
		/* काष्ठा A अणु */	/* [3] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 1), 8),
		/* स्थिर व्योम m; */
		BTF_MEMBER_ENC(NAME_TBD, 2, 0),
		/* पूर्ण */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0m",
	.str_sec_size = माप("\0A\0m"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "void_test2_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(व्योम *),
	.key_type_id = 1,
	.value_type_id = 3,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid member",
पूर्ण,

/* प्रकार स्थिर व्योम * स्थिर_व्योम_ptr;
 * स्थिर_व्योम_ptr[4]
 */
अणु
	.descr = "void test #3",
	.raw_types = अणु
		/* पूर्णांक */		/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		/* स्थिर व्योम */	/* [2] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_CONST, 0, 0), 0),
		/* स्थिर व्योम* */	/* [3] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_PTR, 0, 0), 2),
		/* प्रकार स्थिर व्योम * स्थिर_व्योम_ptr */
		BTF_TYPEDEF_ENC(NAME_TBD, 3),	/* [4] */
		/* स्थिर_व्योम_ptr[4] */
		BTF_TYPE_ARRAY_ENC(4, 1, 4),	/* [5] */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0const_void_ptr",
	.str_sec_size = माप("\0const_void_ptr"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "void_test3_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(व्योम *) * 4,
	.key_type_id = 1,
	.value_type_id = 5,
	.max_entries = 4,
पूर्ण,

/* स्थिर व्योम[4]  */
अणु
	.descr = "void test #4",
	.raw_types = अणु
		/* पूर्णांक */		/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		/* स्थिर व्योम */	/* [2] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_CONST, 0, 0), 0),
		/* स्थिर व्योम[4] */	/* [3] */
		BTF_TYPE_ARRAY_ENC(2, 1, 4),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0m",
	.str_sec_size = माप("\0A\0m"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "void_test4_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(व्योम *) * 4,
	.key_type_id = 1,
	.value_type_id = 3,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid elem",
पूर्ण,

/* Array_A  <------------------+
 *     elem_type == Array_B    |
 *                    |        |
 *                    |        |
 * Array_B  <-------- +        |
 *      elem_type == Array A --+
 */
अणु
	.descr = "loop test #1",
	.raw_types = अणु
		/* पूर्णांक */			/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		/* Array_A */			/* [2] */
		BTF_TYPE_ARRAY_ENC(3, 1, 8),
		/* Array_B */			/* [3] */
		BTF_TYPE_ARRAY_ENC(2, 1, 8),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "",
	.str_sec_size = माप(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "loop_test1_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(माप(पूर्णांक) * 8),
	.key_type_id = 1,
	.value_type_id = 2,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Loop detected",
पूर्ण,

/* प्रकार is _beक्रमe_ the BTF type of Array_A and Array_B
 *
 * प्रकार Array_B पूर्णांक_array;
 *
 * Array_A  <------------------+
 *     elem_type == पूर्णांक_array  |
 *                    |        |
 *                    |        |
 * Array_B  <-------- +        |
 *      elem_type == Array_A --+
 */
अणु
	.descr = "loop test #2",
	.raw_types = अणु
		/* पूर्णांक */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		/* प्रकार Array_B पूर्णांक_array */
		BTF_TYPEDEF_ENC(1, 4),				/* [2] */
		/* Array_A */
		BTF_TYPE_ARRAY_ENC(2, 1, 8),			/* [3] */
		/* Array_B */
		BTF_TYPE_ARRAY_ENC(3, 1, 8),			/* [4] */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0int_array\0",
	.str_sec_size = माप("\0int_array"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "loop_test2_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(माप(पूर्णांक) * 8),
	.key_type_id = 1,
	.value_type_id = 2,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Loop detected",
पूर्ण,

/* Array_A  <------------------+
 *     elem_type == Array_B    |
 *                    |        |
 *                    |        |
 * Array_B  <-------- +        |
 *      elem_type == Array_A --+
 */
अणु
	.descr = "loop test #3",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		/* Array_A */				/* [2] */
		BTF_TYPE_ARRAY_ENC(3, 1, 8),
		/* Array_B */				/* [3] */
		BTF_TYPE_ARRAY_ENC(2, 1, 8),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "",
	.str_sec_size = माप(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "loop_test3_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(माप(पूर्णांक) * 8),
	.key_type_id = 1,
	.value_type_id = 2,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Loop detected",
पूर्ण,

/* प्रकार is _between_ the BTF type of Array_A and Array_B
 *
 * प्रकार Array_B पूर्णांक_array;
 *
 * Array_A  <------------------+
 *     elem_type == पूर्णांक_array  |
 *                    |        |
 *                    |        |
 * Array_B  <-------- +        |
 *      elem_type == Array_A --+
 */
अणु
	.descr = "loop test #4",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		/* Array_A */				/* [2] */
		BTF_TYPE_ARRAY_ENC(3, 1, 8),
		/* प्रकार Array_B पूर्णांक_array */		/* [3] */
		BTF_TYPEDEF_ENC(NAME_TBD, 4),
		/* Array_B */				/* [4] */
		BTF_TYPE_ARRAY_ENC(2, 1, 8),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0int_array\0",
	.str_sec_size = माप("\0int_array"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "loop_test4_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(माप(पूर्णांक) * 8),
	.key_type_id = 1,
	.value_type_id = 2,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Loop detected",
पूर्ण,

/* प्रकार काष्ठा B Struct_B
 *
 * काष्ठा A अणु
 *     पूर्णांक x;
 *     Struct_B y;
 * पूर्ण;
 *
 * काष्ठा B अणु
 *     पूर्णांक x;
 *     काष्ठा A y;
 * पूर्ण;
 */
अणु
	.descr = "loop test #5",
	.raw_types = अणु
		/* पूर्णांक */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		/* काष्ठा A */					/* [2] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 2), 8),
		BTF_MEMBER_ENC(NAME_TBD, 1, 0),	/* पूर्णांक x;	*/
		BTF_MEMBER_ENC(NAME_TBD, 3, 32),/* Struct_B y;	*/
		/* प्रकार काष्ठा B Struct_B */
		BTF_TYPEDEF_ENC(NAME_TBD, 4),			/* [3] */
		/* काष्ठा B */					/* [4] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 2), 8),
		BTF_MEMBER_ENC(NAME_TBD, 1, 0),	/* पूर्णांक x;	*/
		BTF_MEMBER_ENC(NAME_TBD, 2, 32),/* काष्ठा A y;	*/
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0x\0y\0Struct_B\0B\0x\0y",
	.str_sec_size = माप("\0A\0x\0y\0Struct_B\0B\0x\0y"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "loop_test5_map",
	.key_size = माप(पूर्णांक),
	.value_size = 8,
	.key_type_id = 1,
	.value_type_id = 2,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Loop detected",
पूर्ण,

/* काष्ठा A अणु
 *     पूर्णांक x;
 *     काष्ठा A array_a[4];
 * पूर्ण;
 */
अणु
	.descr = "loop test #6",
	.raw_types = अणु
		/* पूर्णांक */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_TYPE_ARRAY_ENC(3, 1, 4),			/* [2] */
		/* काष्ठा A */					/* [3] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 2), 8),
		BTF_MEMBER_ENC(NAME_TBD, 1, 0),	/* पूर्णांक x;		*/
		BTF_MEMBER_ENC(NAME_TBD, 2, 32),/* काष्ठा A array_a[4];	*/
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0x\0y",
	.str_sec_size = माप("\0A\0x\0y"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "loop_test6_map",
	.key_size = माप(पूर्णांक),
	.value_size = 8,
	.key_type_id = 1,
	.value_type_id = 2,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Loop detected",
पूर्ण,

अणु
	.descr = "loop test #7",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		/* काष्ठा A अणु */			/* [2] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 1), माप(व्योम *)),
		/*     स्थिर व्योम *m;	*/
		BTF_MEMBER_ENC(NAME_TBD, 3, 0),
		/* CONST type_id=3	*/		/* [3] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_CONST, 0, 0), 4),
		/* PTR type_id=2	*/		/* [4] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_PTR, 0, 0), 3),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0m",
	.str_sec_size = माप("\0A\0m"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "loop_test7_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(व्योम *),
	.key_type_id = 1,
	.value_type_id = 2,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Loop detected",
पूर्ण,

अणु
	.descr = "loop test #8",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		/* काष्ठा A अणु */			/* [2] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 1), माप(व्योम *)),
		/*     स्थिर व्योम *m;	*/
		BTF_MEMBER_ENC(NAME_TBD, 4, 0),
		/* काष्ठा B अणु */			/* [3] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 1), माप(व्योम *)),
		/*     स्थिर व्योम *n;	*/
		BTF_MEMBER_ENC(NAME_TBD, 6, 0),
		/* CONST type_id=5	*/		/* [4] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_CONST, 0, 0), 5),
		/* PTR type_id=6	*/		/* [5] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_PTR, 0, 0), 6),
		/* CONST type_id=7	*/		/* [6] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_CONST, 0, 0), 7),
		/* PTR type_id=4	*/		/* [7] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_PTR, 0, 0), 4),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0m\0B\0n",
	.str_sec_size = माप("\0A\0m\0B\0n"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "loop_test8_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(व्योम *),
	.key_type_id = 1,
	.value_type_id = 2,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Loop detected",
पूर्ण,

अणु
	.descr = "string section does not end with null",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0int",
	.str_sec_size = माप("\0int") - 1,
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "hdr_test_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid string section",
पूर्ण,

अणु
	.descr = "empty string section",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "",
	.str_sec_size = 0,
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "hdr_test_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid string section",
पूर्ण,

अणु
	.descr = "empty type section",
	.raw_types = अणु
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0int",
	.str_sec_size = माप("\0int"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "hdr_test_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "No type found",
पूर्ण,

अणु
	.descr = "btf_header test. Longer hdr_len",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0int",
	.str_sec_size = माप("\0int"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "hdr_test_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.hdr_len_delta = 4,
	.err_str = "Unsupported btf_header",
पूर्ण,

अणु
	.descr = "btf_header test. Gap between hdr and type",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0int",
	.str_sec_size = माप("\0int"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "hdr_test_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.type_off_delta = 4,
	.err_str = "Unsupported section found",
पूर्ण,

अणु
	.descr = "btf_header test. Gap between type and str",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0int",
	.str_sec_size = माप("\0int"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "hdr_test_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.str_off_delta = 4,
	.err_str = "Unsupported section found",
पूर्ण,

अणु
	.descr = "btf_header test. Overlap between type and str",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0int",
	.str_sec_size = माप("\0int"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "hdr_test_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.str_off_delta = -4,
	.err_str = "Section overlap found",
पूर्ण,

अणु
	.descr = "btf_header test. Larger BTF size",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0int",
	.str_sec_size = माप("\0int"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "hdr_test_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.str_len_delta = -4,
	.err_str = "Unsupported section found",
पूर्ण,

अणु
	.descr = "btf_header test. Smaller BTF size",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0int",
	.str_sec_size = माप("\0int"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "hdr_test_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.str_len_delta = 4,
	.err_str = "Total section length too long",
पूर्ण,

अणु
	.descr = "array test. index_type/elem_type \"int\"",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		/* पूर्णांक[16] */				/* [2] */
		BTF_TYPE_ARRAY_ENC(1, 1, 16),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "",
	.str_sec_size = माप(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "array_test_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
पूर्ण,

अणु
	.descr = "array test. index_type/elem_type \"const int\"",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		/* पूर्णांक[16] */				/* [2] */
		BTF_TYPE_ARRAY_ENC(3, 3, 16),
		/* CONST type_id=1 */			/* [3] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_CONST, 0, 0), 1),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "",
	.str_sec_size = माप(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "array_test_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
पूर्ण,

अणु
	.descr = "array test. index_type \"const int:31\"",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		/* पूर्णांक:31 */				/* [2] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 31, 4),
		/* पूर्णांक[16] */				/* [3] */
		BTF_TYPE_ARRAY_ENC(1, 4, 16),
		/* CONST type_id=2 */			/* [4] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_CONST, 0, 0), 2),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "",
	.str_sec_size = माप(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "array_test_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid index",
पूर्ण,

अणु
	.descr = "array test. elem_type \"const int:31\"",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		/* पूर्णांक:31 */				/* [2] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 31, 4),
		/* पूर्णांक[16] */				/* [3] */
		BTF_TYPE_ARRAY_ENC(4, 1, 16),
		/* CONST type_id=2 */			/* [4] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_CONST, 0, 0), 2),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "",
	.str_sec_size = माप(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "array_test_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid array of int",
पूर्ण,

अणु
	.descr = "array test. index_type \"void\"",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		/* पूर्णांक[16] */				/* [2] */
		BTF_TYPE_ARRAY_ENC(1, 0, 16),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "",
	.str_sec_size = माप(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "array_test_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid index",
पूर्ण,

अणु
	.descr = "array test. index_type \"const void\"",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		/* पूर्णांक[16] */				/* [2] */
		BTF_TYPE_ARRAY_ENC(1, 3, 16),
		/* CONST type_id=0 (व्योम) */		/* [3] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_CONST, 0, 0), 0),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "",
	.str_sec_size = माप(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "array_test_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid index",
पूर्ण,

अणु
	.descr = "array test. elem_type \"const void\"",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		/* पूर्णांक[16] */				/* [2] */
		BTF_TYPE_ARRAY_ENC(3, 1, 16),
		/* CONST type_id=0 (व्योम) */		/* [3] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_CONST, 0, 0), 0),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "",
	.str_sec_size = माप(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "array_test_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid elem",
पूर्ण,

अणु
	.descr = "array test. elem_type \"const void *\"",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		/* स्थिर व्योम *[16] */			/* [2] */
		BTF_TYPE_ARRAY_ENC(3, 1, 16),
		/* CONST type_id=4 */			/* [3] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_CONST, 0, 0), 4),
		/* व्योम* */				/* [4] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_PTR, 0, 0), 0),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "",
	.str_sec_size = माप(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "array_test_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
पूर्ण,

अणु
	.descr = "array test. index_type \"const void *\"",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		/* स्थिर व्योम *[16] */			/* [2] */
		BTF_TYPE_ARRAY_ENC(3, 3, 16),
		/* CONST type_id=4 */			/* [3] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_CONST, 0, 0), 4),
		/* व्योम* */				/* [4] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_PTR, 0, 0), 0),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "",
	.str_sec_size = माप(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "array_test_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid index",
पूर्ण,

अणु
	.descr = "array test. t->size != 0\"",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		/* पूर्णांक[16] */				/* [2] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_ARRAY, 0, 0), 1),
		BTF_ARRAY_ENC(1, 1, 16),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "",
	.str_sec_size = माप(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "array_test_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "size != 0",
पूर्ण,

अणु
	.descr = "int test. invalid int_data",
	.raw_types = अणु
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_INT, 0, 0), 4),
		0x10000000,
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "",
	.str_sec_size = माप(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "array_test_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid int_data",
पूर्ण,

अणु
	.descr = "invalid BTF_INFO",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		BTF_TYPE_ENC(0, 0x20000000, 4),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "",
	.str_sec_size = माप(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "array_test_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid btf_info",
पूर्ण,

अणु
	.descr = "fwd test. t->type != 0\"",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		/* fwd type */				/* [2] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_FWD, 0, 0), 1),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "",
	.str_sec_size = माप(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "fwd_test_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "type != 0",
पूर्ण,

अणु
	.descr = "typedef (invalid name, name_off = 0)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_TYPEDEF_ENC(0, 1),				/* [2] */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0__int",
	.str_sec_size = माप("\0__int"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "typedef_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid name",
पूर्ण,

अणु
	.descr = "typedef (invalid name, invalid identifier)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_TYPEDEF_ENC(NAME_TBD, 1),			/* [2] */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0__!int",
	.str_sec_size = माप("\0__!int"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "typedef_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid name",
पूर्ण,

अणु
	.descr = "ptr type (invalid name, name_off <> 0)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),		/* [1] */
		BTF_TYPE_ENC(NAME_TBD,
			     BTF_INFO_ENC(BTF_KIND_PTR, 0, 0), 1),	/* [2] */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0__int",
	.str_sec_size = माप("\0__int"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "ptr_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid name",
पूर्ण,

अणु
	.descr = "volatile type (invalid name, name_off <> 0)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),		/* [1] */
		BTF_TYPE_ENC(NAME_TBD,
			     BTF_INFO_ENC(BTF_KIND_VOLATILE, 0, 0), 1),	/* [2] */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0__int",
	.str_sec_size = माप("\0__int"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "volatile_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid name",
पूर्ण,

अणु
	.descr = "const type (invalid name, name_off <> 0)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),		/* [1] */
		BTF_TYPE_ENC(NAME_TBD,
			     BTF_INFO_ENC(BTF_KIND_CONST, 0, 0), 1),	/* [2] */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0__int",
	.str_sec_size = माप("\0__int"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "const_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid name",
पूर्ण,

अणु
	.descr = "restrict type (invalid name, name_off <> 0)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),		/* [1] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_PTR, 0, 0), 1),	/* [2] */
		BTF_TYPE_ENC(NAME_TBD,
			     BTF_INFO_ENC(BTF_KIND_RESTRICT, 0, 0), 2),	/* [3] */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0__int",
	.str_sec_size = माप("\0__int"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "restrict_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid name",
पूर्ण,

अणु
	.descr = "fwd type (invalid name, name_off = 0)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),		/* [1] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_FWD, 0, 0), 0),	/* [2] */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0__skb",
	.str_sec_size = माप("\0__skb"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "fwd_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid name",
पूर्ण,

अणु
	.descr = "fwd type (invalid name, invalid identifier)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),		/* [1] */
		BTF_TYPE_ENC(NAME_TBD,
			     BTF_INFO_ENC(BTF_KIND_FWD, 0, 0), 0),	/* [2] */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0__!skb",
	.str_sec_size = माप("\0__!skb"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "fwd_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid name",
पूर्ण,

अणु
	.descr = "array type (invalid name, name_off <> 0)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),		/* [1] */
		BTF_TYPE_ENC(NAME_TBD,
			     BTF_INFO_ENC(BTF_KIND_ARRAY, 0, 0), 0),	/* [2] */
		BTF_ARRAY_ENC(1, 1, 4),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0__skb",
	.str_sec_size = माप("\0__skb"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "array_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid name",
पूर्ण,

अणु
	.descr = "struct type (name_off = 0)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),		/* [1] */
		BTF_TYPE_ENC(0,
			     BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 1), 4),	/* [2] */
		BTF_MEMBER_ENC(NAME_TBD, 1, 0),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A",
	.str_sec_size = माप("\0A"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "struct_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
पूर्ण,

अणु
	.descr = "struct type (invalid name, invalid identifier)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),		/* [1] */
		BTF_TYPE_ENC(NAME_TBD,
			     BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 1), 4),	/* [2] */
		BTF_MEMBER_ENC(NAME_TBD, 1, 0),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A!\0B",
	.str_sec_size = माप("\0A!\0B"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "struct_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid name",
पूर्ण,

अणु
	.descr = "struct member (name_off = 0)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),		/* [1] */
		BTF_TYPE_ENC(0,
			     BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 1), 4),	/* [2] */
		BTF_MEMBER_ENC(NAME_TBD, 1, 0),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A",
	.str_sec_size = माप("\0A"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "struct_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
पूर्ण,

अणु
	.descr = "struct member (invalid name, invalid identifier)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),		/* [1] */
		BTF_TYPE_ENC(NAME_TBD,
			     BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 1), 4),	/* [2] */
		BTF_MEMBER_ENC(NAME_TBD, 1, 0),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0B*",
	.str_sec_size = माप("\0A\0B*"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "struct_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid name",
पूर्ण,

अणु
	.descr = "enum type (name_off = 0)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),		/* [1] */
		BTF_TYPE_ENC(0,
			     BTF_INFO_ENC(BTF_KIND_ENUM, 0, 1),
			     माप(पूर्णांक)),				/* [2] */
		BTF_ENUM_ENC(NAME_TBD, 0),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A\0B",
	.str_sec_size = माप("\0A\0B"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "enum_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
पूर्ण,

अणु
	.descr = "enum type (invalid name, invalid identifier)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),		/* [1] */
		BTF_TYPE_ENC(NAME_TBD,
			     BTF_INFO_ENC(BTF_KIND_ENUM, 0, 1),
			     माप(पूर्णांक)),				/* [2] */
		BTF_ENUM_ENC(NAME_TBD, 0),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A!\0B",
	.str_sec_size = माप("\0A!\0B"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "enum_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid name",
पूर्ण,

अणु
	.descr = "enum member (invalid name, name_off = 0)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),		/* [1] */
		BTF_TYPE_ENC(0,
			     BTF_INFO_ENC(BTF_KIND_ENUM, 0, 1),
			     माप(पूर्णांक)),				/* [2] */
		BTF_ENUM_ENC(0, 0),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "",
	.str_sec_size = माप(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "enum_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid name",
पूर्ण,

अणु
	.descr = "enum member (invalid name, invalid identifier)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),		/* [1] */
		BTF_TYPE_ENC(0,
			     BTF_INFO_ENC(BTF_KIND_ENUM, 0, 1),
			     माप(पूर्णांक)),				/* [2] */
		BTF_ENUM_ENC(NAME_TBD, 0),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0A!",
	.str_sec_size = माप("\0A!"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "enum_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid name",
पूर्ण,
अणु
	.descr = "arraymap invalid btf key (a bit field)",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		/* 32 bit पूर्णांक with 32 bit offset */	/* [2] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 32, 32, 8),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "",
	.str_sec_size = माप(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "array_map_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 2,
	.value_type_id = 1,
	.max_entries = 4,
	.map_create_err = true,
पूर्ण,

अणु
	.descr = "arraymap invalid btf key (!= 32 bits)",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		/* 16 bit पूर्णांक with 0 bit offset */	/* [2] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 16, 2),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "",
	.str_sec_size = माप(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "array_map_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 2,
	.value_type_id = 1,
	.max_entries = 4,
	.map_create_err = true,
पूर्ण,

अणु
	.descr = "arraymap invalid btf value (too small)",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "",
	.str_sec_size = माप(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "array_map_check_btf",
	.key_size = माप(पूर्णांक),
	/* btf_value_size < map->value_size */
	.value_size = माप(__u64),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.map_create_err = true,
पूर्ण,

अणु
	.descr = "arraymap invalid btf value (too big)",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "",
	.str_sec_size = माप(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "array_map_check_btf",
	.key_size = माप(पूर्णांक),
	/* btf_value_size > map->value_size */
	.value_size = माप(__u16),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.map_create_err = true,
पूर्ण,

अणु
	.descr = "func proto (int (*)(int, unsigned int))",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4), /* [1] */
		BTF_TYPE_INT_ENC(0, 0, 0, 32, 4),		/* [2] */
		/* पूर्णांक (*)(पूर्णांक, अचिन्हित पूर्णांक) */
		BTF_FUNC_PROTO_ENC(1, 2),			/* [3] */
			BTF_FUNC_PROTO_ARG_ENC(0, 1),
			BTF_FUNC_PROTO_ARG_ENC(0, 2),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "",
	.str_sec_size = माप(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "func_proto_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
पूर्ण,

अणु
	.descr = "func proto (vararg)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_TYPE_INT_ENC(0, 0, 0, 32, 4),		/* [2] */
		/* व्योम (*)(पूर्णांक, अचिन्हित पूर्णांक, ...) */
		BTF_FUNC_PROTO_ENC(0, 3),			/* [3] */
			BTF_FUNC_PROTO_ARG_ENC(0, 1),
			BTF_FUNC_PROTO_ARG_ENC(0, 2),
			BTF_FUNC_PROTO_ARG_ENC(0, 0),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "",
	.str_sec_size = माप(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "func_proto_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
पूर्ण,

अणु
	.descr = "func proto (vararg with name)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_TYPE_INT_ENC(0, 0, 0, 32, 4),		/* [2] */
		/* व्योम (*)(पूर्णांक a, अचिन्हित पूर्णांक b, ... c) */
		BTF_FUNC_PROTO_ENC(0, 3),			/* [3] */
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 1),
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 2),
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 0),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0a\0b\0c",
	.str_sec_size = माप("\0a\0b\0c"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "func_proto_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid arg#3",
पूर्ण,

अणु
	.descr = "func proto (arg after vararg)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_TYPE_INT_ENC(0, 0, 0, 32, 4),		/* [2] */
		/* व्योम (*)(पूर्णांक a, ..., अचिन्हित पूर्णांक b) */
		BTF_FUNC_PROTO_ENC(0, 3),			/* [3] */
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 1),
			BTF_FUNC_PROTO_ARG_ENC(0, 0),
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 2),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0a\0b",
	.str_sec_size = माप("\0a\0b"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "func_proto_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid arg#2",
पूर्ण,

अणु
	.descr = "func proto (CONST=>TYPEDEF=>PTR=>FUNC_PROTO)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_TYPE_INT_ENC(0, 0, 0, 32, 4),		/* [2] */
		/* प्रकार व्योम (*func_ptr)(पूर्णांक, अचिन्हित पूर्णांक) */
		BTF_TYPEDEF_ENC(NAME_TBD, 5),			/* [3] */
		/* स्थिर func_ptr */
		BTF_CONST_ENC(3),				/* [4] */
		BTF_PTR_ENC(6),					/* [5] */
		BTF_FUNC_PROTO_ENC(0, 2),			/* [6] */
			BTF_FUNC_PROTO_ARG_ENC(0, 1),
			BTF_FUNC_PROTO_ARG_ENC(0, 2),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0func_ptr",
	.str_sec_size = माप("\0func_ptr"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "func_proto_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
पूर्ण,

अणु
	.descr = "func proto (TYPEDEF=>FUNC_PROTO)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_TYPE_INT_ENC(0, 0, 0, 32, 4),		/* [2] */
		BTF_TYPEDEF_ENC(NAME_TBD, 4),			/* [3] */
		BTF_FUNC_PROTO_ENC(0, 2),			/* [4] */
			BTF_FUNC_PROTO_ARG_ENC(0, 1),
			BTF_FUNC_PROTO_ARG_ENC(0, 2),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0func_typedef",
	.str_sec_size = माप("\0func_typedef"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "func_proto_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
पूर्ण,

अणु
	.descr = "func proto (btf_resolve(arg))",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		/* व्योम (*)(स्थिर व्योम *) */
		BTF_FUNC_PROTO_ENC(0, 1),			/* [2] */
			BTF_FUNC_PROTO_ARG_ENC(0, 3),
		BTF_CONST_ENC(4),				/* [3] */
		BTF_PTR_ENC(0),					/* [4] */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "",
	.str_sec_size = माप(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "func_proto_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
पूर्ण,

अणु
	.descr = "func proto (Not all arg has name)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_TYPE_INT_ENC(0, 0, 0, 32, 4),		/* [2] */
		/* व्योम (*)(पूर्णांक, अचिन्हित पूर्णांक b) */
		BTF_FUNC_PROTO_ENC(0, 2),			/* [3] */
			BTF_FUNC_PROTO_ARG_ENC(0, 1),
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 2),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0b",
	.str_sec_size = माप("\0b"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "func_proto_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
पूर्ण,

अणु
	.descr = "func proto (Bad arg name_off)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_TYPE_INT_ENC(0, 0, 0, 32, 4),		/* [2] */
		/* व्योम (*)(पूर्णांक a, अचिन्हित पूर्णांक <bad_name_off>) */
		BTF_FUNC_PROTO_ENC(0, 2),			/* [3] */
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 1),
			BTF_FUNC_PROTO_ARG_ENC(0x0fffffff, 2),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0a",
	.str_sec_size = माप("\0a"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "func_proto_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid arg#2",
पूर्ण,

अणु
	.descr = "func proto (Bad arg name)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_TYPE_INT_ENC(0, 0, 0, 32, 4),		/* [2] */
		/* व्योम (*)(पूर्णांक a, अचिन्हित पूर्णांक !!!) */
		BTF_FUNC_PROTO_ENC(0, 2),			/* [3] */
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 1),
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 2),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0a\0!!!",
	.str_sec_size = माप("\0a\0!!!"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "func_proto_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid arg#2",
पूर्ण,

अणु
	.descr = "func proto (Invalid return type)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_TYPE_INT_ENC(0, 0, 0, 32, 4),		/* [2] */
		/* <bad_ret_type> (*)(पूर्णांक, अचिन्हित पूर्णांक) */
		BTF_FUNC_PROTO_ENC(100, 2),			/* [3] */
			BTF_FUNC_PROTO_ARG_ENC(0, 1),
			BTF_FUNC_PROTO_ARG_ENC(0, 2),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "",
	.str_sec_size = माप(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "func_proto_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid return type",
पूर्ण,

अणु
	.descr = "func proto (with func name)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_TYPE_INT_ENC(0, 0, 0, 32, 4),		/* [2] */
		/* व्योम func_proto(पूर्णांक, अचिन्हित पूर्णांक) */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_FUNC_PROTO, 0, 2), 0),	/* [3] */
			BTF_FUNC_PROTO_ARG_ENC(0, 1),
			BTF_FUNC_PROTO_ARG_ENC(0, 2),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0func_proto",
	.str_sec_size = माप("\0func_proto"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "func_proto_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid name",
पूर्ण,

अणु
	.descr = "func proto (const void arg)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_TYPE_INT_ENC(0, 0, 0, 32, 4),		/* [2] */
		/* व्योम (*)(स्थिर व्योम) */
		BTF_FUNC_PROTO_ENC(0, 1),			/* [3] */
			BTF_FUNC_PROTO_ARG_ENC(0, 4),
		BTF_CONST_ENC(0),				/* [4] */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "",
	.str_sec_size = माप(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "func_proto_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid arg#1",
पूर्ण,

अणु
	.descr = "func (void func(int a, unsigned int b))",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_TYPE_INT_ENC(0, 0, 0, 32, 4),		/* [2] */
		/* व्योम (*)(पूर्णांक a, अचिन्हित पूर्णांक b) */
		BTF_FUNC_PROTO_ENC(0, 2),			/* [3] */
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 1),
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 2),
		/* व्योम func(पूर्णांक a, अचिन्हित पूर्णांक b) */
		BTF_FUNC_ENC(NAME_TBD, 3),			/* [4] */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0a\0b\0func",
	.str_sec_size = माप("\0a\0b\0func"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "func_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
पूर्ण,

अणु
	.descr = "func (No func name)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_TYPE_INT_ENC(0, 0, 0, 32, 4),		/* [2] */
		/* व्योम (*)(पूर्णांक a, अचिन्हित पूर्णांक b) */
		BTF_FUNC_PROTO_ENC(0, 2),			/* [3] */
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 1),
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 2),
		/* व्योम <no_name>(पूर्णांक a, अचिन्हित पूर्णांक b) */
		BTF_FUNC_ENC(0, 3),				/* [4] */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0a\0b",
	.str_sec_size = माप("\0a\0b"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "func_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid name",
पूर्ण,

अणु
	.descr = "func (Invalid func name)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_TYPE_INT_ENC(0, 0, 0, 32, 4),		/* [2] */
		/* व्योम (*)(पूर्णांक a, अचिन्हित पूर्णांक b) */
		BTF_FUNC_PROTO_ENC(0, 2),			/* [3] */
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 1),
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 2),
		/* व्योम !!!(पूर्णांक a, अचिन्हित पूर्णांक b) */
		BTF_FUNC_ENC(NAME_TBD, 3),			/* [4] */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0a\0b\0!!!",
	.str_sec_size = माप("\0a\0b\0!!!"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "func_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid name",
पूर्ण,

अणु
	.descr = "func (Some arg has no name)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_TYPE_INT_ENC(0, 0, 0, 32, 4),		/* [2] */
		/* व्योम (*)(पूर्णांक a, अचिन्हित पूर्णांक) */
		BTF_FUNC_PROTO_ENC(0, 2),			/* [3] */
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 1),
			BTF_FUNC_PROTO_ARG_ENC(0, 2),
		/* व्योम func(पूर्णांक a, अचिन्हित पूर्णांक) */
		BTF_FUNC_ENC(NAME_TBD, 3),			/* [4] */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0a\0func",
	.str_sec_size = माप("\0a\0func"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "func_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid arg#2",
पूर्ण,

अणु
	.descr = "func (Non zero vlen)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_TYPE_INT_ENC(0, 0, 0, 32, 4),		/* [2] */
		/* व्योम (*)(पूर्णांक a, अचिन्हित पूर्णांक b) */
		BTF_FUNC_PROTO_ENC(0, 2),			/* [3] */
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 1),
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 2),
		/* व्योम func(पूर्णांक a, अचिन्हित पूर्णांक b) */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_FUNC, 0, 2), 3), 	/* [4] */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0a\0b\0func",
	.str_sec_size = माप("\0a\0b\0func"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "func_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid func linkage",
पूर्ण,

अणु
	.descr = "func (Not referring to FUNC_PROTO)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_FUNC_ENC(NAME_TBD, 1),			/* [2] */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0func",
	.str_sec_size = माप("\0func"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "func_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid type_id",
पूर्ण,

अणु
	.descr = "invalid int kind_flag",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),		/* [1] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_INT, 1, 0), 4),	/* [2] */
		BTF_INT_ENC(0, 0, 32),
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "int_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid btf_info kind_flag",
पूर्ण,

अणु
	.descr = "invalid ptr kind_flag",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),		/* [1] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_PTR, 1, 0), 1),	/* [2] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "ptr_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid btf_info kind_flag",
पूर्ण,

अणु
	.descr = "invalid array kind_flag",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),		/* [1] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_ARRAY, 1, 0), 0),	/* [2] */
		BTF_ARRAY_ENC(1, 1, 1),
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "array_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid btf_info kind_flag",
पूर्ण,

अणु
	.descr = "invalid enum kind_flag",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),		/* [1] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_ENUM, 1, 1), 4),	/* [2] */
		BTF_ENUM_ENC(NAME_TBD, 0),
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0A"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "enum_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid btf_info kind_flag",
पूर्ण,

अणु
	.descr = "valid fwd kind_flag",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),		/* [1] */
		BTF_TYPE_ENC(NAME_TBD,
			     BTF_INFO_ENC(BTF_KIND_FWD, 1, 0), 0),	/* [2] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0A"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "fwd_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
पूर्ण,

अणु
	.descr = "invalid typedef kind_flag",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),		/* [1] */
		BTF_TYPE_ENC(NAME_TBD,
			     BTF_INFO_ENC(BTF_KIND_TYPEDEF, 1, 0), 1),	/* [2] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0A"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "typedef_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid btf_info kind_flag",
पूर्ण,

अणु
	.descr = "invalid volatile kind_flag",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),			/* [1] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_VOLATILE, 1, 0), 1),	/* [2] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "volatile_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid btf_info kind_flag",
पूर्ण,

अणु
	.descr = "invalid const kind_flag",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),		/* [1] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_CONST, 1, 0), 1),	/* [2] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "const_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid btf_info kind_flag",
पूर्ण,

अणु
	.descr = "invalid restrict kind_flag",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),			/* [1] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_RESTRICT, 1, 0), 1),	/* [2] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "restrict_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid btf_info kind_flag",
पूर्ण,

अणु
	.descr = "invalid func kind_flag",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),			/* [1] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_FUNC_PROTO, 0, 0), 0),	/* [2] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_FUNC, 1, 0), 2),	/* [3] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0A"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "func_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid btf_info kind_flag",
पूर्ण,

अणु
	.descr = "invalid func_proto kind_flag",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),			/* [1] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_FUNC_PROTO, 1, 0), 0),	/* [2] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC(""),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "func_proto_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid btf_info kind_flag",
पूर्ण,

अणु
	.descr = "valid struct, kind_flag, bitfield_size = 0",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),			/* [1] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_STRUCT, 1, 2), 8),	/* [2] */
		BTF_MEMBER_ENC(NAME_TBD, 1, BTF_MEMBER_OFFSET(0, 0)),
		BTF_MEMBER_ENC(NAME_TBD, 1, BTF_MEMBER_OFFSET(0, 32)),
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0A\0B"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "struct_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
पूर्ण,

अणु
	.descr = "valid struct, kind_flag, int member, bitfield_size != 0",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),			/* [1] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_STRUCT, 1, 2), 4),	/* [2] */
		BTF_MEMBER_ENC(NAME_TBD, 1, BTF_MEMBER_OFFSET(4, 0)),
		BTF_MEMBER_ENC(NAME_TBD, 1, BTF_MEMBER_OFFSET(4, 4)),
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0A\0B"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "struct_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
पूर्ण,

अणु
	.descr = "valid union, kind_flag, int member, bitfield_size != 0",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),		/* [1] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_UNION, 1, 2), 4),	/* [2] */
		BTF_MEMBER_ENC(NAME_TBD, 1, BTF_MEMBER_OFFSET(4, 0)),
		BTF_MEMBER_ENC(NAME_TBD, 1, BTF_MEMBER_OFFSET(4, 0)),
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0A\0B"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "union_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
पूर्ण,

अणु
	.descr = "valid struct, kind_flag, enum member, bitfield_size != 0",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),		/* [1] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_ENUM, 0, 1), 4),	/* [2] */
		BTF_ENUM_ENC(NAME_TBD, 0),
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_STRUCT, 1, 2), 4),/* [3] */
		BTF_MEMBER_ENC(NAME_TBD, 2, BTF_MEMBER_OFFSET(4, 0)),
		BTF_MEMBER_ENC(NAME_TBD, 2, BTF_MEMBER_OFFSET(4, 4)),
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0A\0B\0C"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "struct_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
पूर्ण,

अणु
	.descr = "valid union, kind_flag, enum member, bitfield_size != 0",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),		/* [1] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_ENUM, 0, 1), 4),	/* [2] */
		BTF_ENUM_ENC(NAME_TBD, 0),
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_UNION, 1, 2), 4),	/* [3] */
		BTF_MEMBER_ENC(NAME_TBD, 2, BTF_MEMBER_OFFSET(4, 0)),
		BTF_MEMBER_ENC(NAME_TBD, 2, BTF_MEMBER_OFFSET(4, 0)),
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0A\0B\0C"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "union_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
पूर्ण,

अणु
	.descr = "valid struct, kind_flag, typedef member, bitfield_size != 0",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),		/* [1] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_ENUM, 0, 1), 4),	/* [2] */
		BTF_ENUM_ENC(NAME_TBD, 0),
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_STRUCT, 1, 2), 4),/* [3] */
		BTF_MEMBER_ENC(NAME_TBD, 4, BTF_MEMBER_OFFSET(4, 0)),
		BTF_MEMBER_ENC(NAME_TBD, 5, BTF_MEMBER_OFFSET(4, 4)),
		BTF_TYPEDEF_ENC(NAME_TBD, 1),				/* [4] */
		BTF_TYPEDEF_ENC(NAME_TBD, 2),				/* [5] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0A\0B\0C\0D\0E"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "struct_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
पूर्ण,

अणु
	.descr = "valid union, kind_flag, typedef member, bitfield_size != 0",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),		/* [1] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_ENUM, 0, 1), 4),	/* [2] */
		BTF_ENUM_ENC(NAME_TBD, 0),
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_UNION, 1, 2), 4),	/* [3] */
		BTF_MEMBER_ENC(NAME_TBD, 4, BTF_MEMBER_OFFSET(4, 0)),
		BTF_MEMBER_ENC(NAME_TBD, 5, BTF_MEMBER_OFFSET(4, 0)),
		BTF_TYPEDEF_ENC(NAME_TBD, 1),				/* [4] */
		BTF_TYPEDEF_ENC(NAME_TBD, 2),				/* [5] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0A\0B\0C\0D\0E"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "union_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
पूर्ण,

अणु
	.descr = "invalid struct, kind_flag, bitfield_size greater than struct size",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),			/* [1] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_STRUCT, 1, 2), 4),	/* [2] */
		BTF_MEMBER_ENC(NAME_TBD, 1, BTF_MEMBER_OFFSET(20, 0)),
		BTF_MEMBER_ENC(NAME_TBD, 1, BTF_MEMBER_OFFSET(20, 20)),
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0A\0B"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "struct_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Member exceeds struct_size",
पूर्ण,

अणु
	.descr = "invalid struct, kind_flag, bitfield base_type int not regular",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),			/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 20, 4),			/* [2] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_STRUCT, 1, 2), 4),	/* [3] */
		BTF_MEMBER_ENC(NAME_TBD, 2, BTF_MEMBER_OFFSET(20, 0)),
		BTF_MEMBER_ENC(NAME_TBD, 2, BTF_MEMBER_OFFSET(20, 20)),
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0A\0B"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "struct_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid member base type",
पूर्ण,

अणु
	.descr = "invalid struct, kind_flag, base_type int not regular",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),			/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 12, 4),			/* [2] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_STRUCT, 1, 2), 4),	/* [3] */
		BTF_MEMBER_ENC(NAME_TBD, 2, BTF_MEMBER_OFFSET(8, 0)),
		BTF_MEMBER_ENC(NAME_TBD, 2, BTF_MEMBER_OFFSET(8, 8)),
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0A\0B"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "struct_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid member base type",
पूर्ण,

अणु
	.descr = "invalid union, kind_flag, bitfield_size greater than struct size",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),		/* [1] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_UNION, 1, 2), 2),	/* [2] */
		BTF_MEMBER_ENC(NAME_TBD, 1, BTF_MEMBER_OFFSET(8, 0)),
		BTF_MEMBER_ENC(NAME_TBD, 1, BTF_MEMBER_OFFSET(20, 0)),
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0A\0B"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "union_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Member exceeds struct_size",
पूर्ण,

अणु
	.descr = "invalid struct, kind_flag, int member, bitfield_size = 0, wrong byte alignment",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),			/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),			/* [2] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_STRUCT, 1, 2), 12),	/* [3] */
		BTF_MEMBER_ENC(NAME_TBD, 2, BTF_MEMBER_OFFSET(0, 0)),
		BTF_MEMBER_ENC(NAME_TBD, 2, BTF_MEMBER_OFFSET(0, 36)),
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0A\0B"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "struct_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid member offset",
पूर्ण,

अणु
	.descr = "invalid struct, kind_flag, enum member, bitfield_size = 0, wrong byte alignment",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),			/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),			/* [2] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_ENUM, 0, 1), 4),	/* [2] */
		BTF_ENUM_ENC(NAME_TBD, 0),
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_STRUCT, 1, 2), 12),	/* [3] */
		BTF_MEMBER_ENC(NAME_TBD, 2, BTF_MEMBER_OFFSET(0, 0)),
		BTF_MEMBER_ENC(NAME_TBD, 2, BTF_MEMBER_OFFSET(0, 36)),
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0A\0B\0C"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "struct_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
	.btf_load_err = true,
	.err_str = "Invalid member offset",
पूर्ण,

अणु
	.descr = "128-bit int",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),			/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 128, 16),		/* [2] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0A"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "int_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
पूर्ण,

अणु
	.descr = "struct, 128-bit int member",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),			/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 128, 16),		/* [2] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 1), 16),	/* [3] */
		BTF_MEMBER_ENC(NAME_TBD, 2, 0),
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0A"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "struct_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
पूर्ण,

अणु
	.descr = "struct, 120-bit int member bitfield",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),			/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 120, 16),		/* [2] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 1), 16),	/* [3] */
		BTF_MEMBER_ENC(NAME_TBD, 2, 0),
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0A"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "struct_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
पूर्ण,

अणु
	.descr = "struct, kind_flag, 128-bit int member",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),			/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 128, 16),		/* [2] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_STRUCT, 1, 1), 16),	/* [3] */
		BTF_MEMBER_ENC(NAME_TBD, 2, BTF_MEMBER_OFFSET(0, 0)),
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0A"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "struct_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
पूर्ण,

अणु
	.descr = "struct, kind_flag, 120-bit int member bitfield",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),			/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 128, 16),		/* [2] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_STRUCT, 1, 1), 16),	/* [3] */
		BTF_MEMBER_ENC(NAME_TBD, 2, BTF_MEMBER_OFFSET(120, 0)),
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0A"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "struct_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 4,
पूर्ण,
/*
 * प्रकार पूर्णांक arr_t[16];
 * काष्ठा s अणु
 *	arr_t *a;
 * पूर्ण;
 */
अणु
	.descr = "struct->ptr->typedef->array->int size resolution",
	.raw_types = अणु
		BTF_STRUCT_ENC(NAME_TBD, 1, 8),			/* [1] */
		BTF_MEMBER_ENC(NAME_TBD, 2, 0),
		BTF_PTR_ENC(3),					/* [2] */
		BTF_TYPEDEF_ENC(NAME_TBD, 4),			/* [3] */
		BTF_TYPE_ARRAY_ENC(5, 5, 16),			/* [4] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [5] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0s\0a\0arr_t"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "ptr_mod_chain_size_resolve_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक) * 16,
	.key_type_id = 5 /* पूर्णांक */,
	.value_type_id = 3 /* arr_t */,
	.max_entries = 4,
पूर्ण,
/*
 * प्रकार पूर्णांक arr_t[16][8][4];
 * काष्ठा s अणु
 *	arr_t *a;
 * पूर्ण;
 */
अणु
	.descr = "struct->ptr->typedef->multi-array->int size resolution",
	.raw_types = अणु
		BTF_STRUCT_ENC(NAME_TBD, 1, 8),			/* [1] */
		BTF_MEMBER_ENC(NAME_TBD, 2, 0),
		BTF_PTR_ENC(3),					/* [2] */
		BTF_TYPEDEF_ENC(NAME_TBD, 4),			/* [3] */
		BTF_TYPE_ARRAY_ENC(5, 7, 16),			/* [4] */
		BTF_TYPE_ARRAY_ENC(6, 7, 8),			/* [5] */
		BTF_TYPE_ARRAY_ENC(7, 7, 4),			/* [6] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [7] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0s\0a\0arr_t"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "multi_arr_size_resolve_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक) * 16 * 8 * 4,
	.key_type_id = 7 /* पूर्णांक */,
	.value_type_id = 3 /* arr_t */,
	.max_entries = 4,
पूर्ण,
/*
 * प्रकार पूर्णांक पूर्णांक_t;
 * प्रकार पूर्णांक_t arr3_t[4];
 * प्रकार arr3_t arr2_t[8];
 * प्रकार arr2_t arr1_t[16];
 * काष्ठा s अणु
 *	arr1_t *a;
 * पूर्ण;
 */
अणु
	.descr = "typedef/multi-arr mix size resolution",
	.raw_types = अणु
		BTF_STRUCT_ENC(NAME_TBD, 1, 8),			/* [1] */
		BTF_MEMBER_ENC(NAME_TBD, 2, 0),
		BTF_PTR_ENC(3),					/* [2] */
		BTF_TYPEDEF_ENC(NAME_TBD, 4),			/* [3] */
		BTF_TYPE_ARRAY_ENC(5, 10, 16),			/* [4] */
		BTF_TYPEDEF_ENC(NAME_TBD, 6),			/* [5] */
		BTF_TYPE_ARRAY_ENC(7, 10, 8),			/* [6] */
		BTF_TYPEDEF_ENC(NAME_TBD, 8),			/* [7] */
		BTF_TYPE_ARRAY_ENC(9, 10, 4),			/* [8] */
		BTF_TYPEDEF_ENC(NAME_TBD, 10),			/* [9] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [10] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0s\0a\0arr1_t\0arr2_t\0arr3_t\0int_t"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "typedef_arra_mix_size_resolve_map",
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक) * 16 * 8 * 4,
	.key_type_id = 10 /* पूर्णांक */,
	.value_type_id = 3 /* arr_t */,
	.max_entries = 4,
पूर्ण,
/*
 * elf .rodata section size 4 and btf .rodata section vlen 0.
 */
अणु
	.descr = "datasec: vlen == 0",
	.raw_types = अणु
		/* पूर्णांक */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		/* .rodata section */
		BTF_TYPE_ENC(NAME_NTH(1), BTF_INFO_ENC(BTF_KIND_DATASEC, 0, 0), 4),
								 /* [2] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0.rodata"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.key_size = माप(पूर्णांक),
	.value_size = माप(पूर्णांक),
	.key_type_id = 1,
	.value_type_id = 1,
	.max_entries = 1,
पूर्ण,

अणु
	.descr = "float test #1, well-formed",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),
								/* [1] */
		BTF_TYPE_FLOAT_ENC(NAME_TBD, 2),		/* [2] */
		BTF_TYPE_FLOAT_ENC(NAME_TBD, 4),		/* [3] */
		BTF_TYPE_FLOAT_ENC(NAME_TBD, 8),		/* [4] */
		BTF_TYPE_FLOAT_ENC(NAME_TBD, 12),		/* [5] */
		BTF_TYPE_FLOAT_ENC(NAME_TBD, 16),		/* [6] */
		BTF_STRUCT_ENC(NAME_TBD, 5, 48),		/* [7] */
		BTF_MEMBER_ENC(NAME_TBD, 2, 0),
		BTF_MEMBER_ENC(NAME_TBD, 3, 32),
		BTF_MEMBER_ENC(NAME_TBD, 4, 64),
		BTF_MEMBER_ENC(NAME_TBD, 5, 128),
		BTF_MEMBER_ENC(NAME_TBD, 6, 256),
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0int\0_Float16\0float\0double\0_Float80\0long_double"
		    "\0floats\0a\0b\0c\0d\0e"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "float_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = 48,
	.key_type_id = 1,
	.value_type_id = 7,
	.max_entries = 1,
पूर्ण,
अणु
	.descr = "float test #2, invalid vlen",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),
								/* [1] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_FLOAT, 0, 1), 4),
								/* [2] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0int\0float"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "float_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = 4,
	.key_type_id = 1,
	.value_type_id = 2,
	.max_entries = 1,
	.btf_load_err = true,
	.err_str = "vlen != 0",
पूर्ण,
अणु
	.descr = "float test #3, invalid kind_flag",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),
								/* [1] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_FLOAT, 1, 0), 4),
								/* [2] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0int\0float"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "float_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = 4,
	.key_type_id = 1,
	.value_type_id = 2,
	.max_entries = 1,
	.btf_load_err = true,
	.err_str = "Invalid btf_info kind_flag",
पूर्ण,
अणु
	.descr = "float test #4, member does not fit",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),
								/* [1] */
		BTF_TYPE_FLOAT_ENC(NAME_TBD, 4),		/* [2] */
		BTF_STRUCT_ENC(NAME_TBD, 1, 2),			/* [3] */
		BTF_MEMBER_ENC(NAME_TBD, 2, 0),
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0int\0float\0floats\0x"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "float_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = 4,
	.key_type_id = 1,
	.value_type_id = 3,
	.max_entries = 1,
	.btf_load_err = true,
	.err_str = "Member exceeds struct_size",
पूर्ण,
अणु
	.descr = "float test #5, member is not properly aligned",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),
								/* [1] */
		BTF_TYPE_FLOAT_ENC(NAME_TBD, 4),		/* [2] */
		BTF_STRUCT_ENC(NAME_TBD, 1, 8),			/* [3] */
		BTF_MEMBER_ENC(NAME_TBD, 2, 8),
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0int\0float\0floats\0x"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "float_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = 4,
	.key_type_id = 1,
	.value_type_id = 3,
	.max_entries = 1,
	.btf_load_err = true,
	.err_str = "Member is not properly aligned",
पूर्ण,
अणु
	.descr = "float test #6, invalid size",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),
								/* [1] */
		BTF_TYPE_FLOAT_ENC(NAME_TBD, 6),		/* [2] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0int\0float"),
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "float_type_check_btf",
	.key_size = माप(पूर्णांक),
	.value_size = 6,
	.key_type_id = 1,
	.value_type_id = 2,
	.max_entries = 1,
	.btf_load_err = true,
	.err_str = "Invalid type_size",
पूर्ण,

पूर्ण; /* काष्ठा btf_raw_test raw_tests[] */

अटल स्थिर अक्षर *get_next_str(स्थिर अक्षर *start, स्थिर अक्षर *end)
अणु
	वापस start < end - 1 ? start + 1 : शून्य;
पूर्ण

अटल पूर्णांक get_raw_sec_size(स्थिर __u32 *raw_types)
अणु
	पूर्णांक i;

	क्रम (i = MAX_NR_RAW_U32 - 1;
	     i >= 0 && raw_types[i] != BTF_END_RAW;
	     i--)
		;

	वापस i < 0 ? i : i * माप(raw_types[0]);
पूर्ण

अटल व्योम *btf_raw_create(स्थिर काष्ठा btf_header *hdr,
			    स्थिर __u32 *raw_types,
			    स्थिर अक्षर *str,
			    अचिन्हित पूर्णांक str_sec_size,
			    अचिन्हित पूर्णांक *btf_size,
			    स्थिर अक्षर **ret_next_str)
अणु
	स्थिर अक्षर *next_str = str, *end_str = str + str_sec_size;
	स्थिर अक्षर **strs_idx = शून्य, **पंचांगp_strs_idx;
	पूर्णांक strs_cap = 0, strs_cnt = 0, next_str_idx = 0;
	अचिन्हित पूर्णांक size_needed, offset;
	काष्ठा btf_header *ret_hdr;
	पूर्णांक i, type_sec_size, err = 0;
	uपूर्णांक32_t *ret_types;
	व्योम *raw_btf = शून्य;

	type_sec_size = get_raw_sec_size(raw_types);
	अगर (CHECK(type_sec_size < 0, "Cannot get nr_raw_types"))
		वापस शून्य;

	size_needed = माप(*hdr) + type_sec_size + str_sec_size;
	raw_btf = दो_स्मृति(size_needed);
	अगर (CHECK(!raw_btf, "Cannot allocate memory for raw_btf"))
		वापस शून्य;

	/* Copy header */
	स_नकल(raw_btf, hdr, माप(*hdr));
	offset = माप(*hdr);

	/* Index strings */
	जबतक ((next_str = get_next_str(next_str, end_str))) अणु
		अगर (strs_cnt == strs_cap) अणु
			strs_cap += max(16, strs_cap / 2);
			पंचांगp_strs_idx = पुनः_स्मृति(strs_idx,
					       माप(*strs_idx) * strs_cap);
			अगर (CHECK(!पंचांगp_strs_idx,
				  "Cannot allocate memory for strs_idx")) अणु
				err = -1;
				जाओ करोne;
			पूर्ण
			strs_idx = पंचांगp_strs_idx;
		पूर्ण
		strs_idx[strs_cnt++] = next_str;
		next_str += म_माप(next_str);
	पूर्ण

	/* Copy type section */
	ret_types = raw_btf + offset;
	क्रम (i = 0; i < type_sec_size / माप(raw_types[0]); i++) अणु
		अगर (raw_types[i] == NAME_TBD) अणु
			अगर (CHECK(next_str_idx == strs_cnt,
				  "Error in getting next_str #%d",
				  next_str_idx)) अणु
				err = -1;
				जाओ करोne;
			पूर्ण
			ret_types[i] = strs_idx[next_str_idx++] - str;
		पूर्ण अन्यथा अगर (IS_NAME_NTH(raw_types[i])) अणु
			पूर्णांक idx = GET_NAME_NTH_IDX(raw_types[i]);

			अगर (CHECK(idx <= 0 || idx > strs_cnt,
				  "Error getting string #%d, strs_cnt:%d",
				  idx, strs_cnt)) अणु
				err = -1;
				जाओ करोne;
			पूर्ण
			ret_types[i] = strs_idx[idx-1] - str;
		पूर्ण अन्यथा अणु
			ret_types[i] = raw_types[i];
		पूर्ण
	पूर्ण
	offset += type_sec_size;

	/* Copy string section */
	स_नकल(raw_btf + offset, str, str_sec_size);

	ret_hdr = (काष्ठा btf_header *)raw_btf;
	ret_hdr->type_len = type_sec_size;
	ret_hdr->str_off = type_sec_size;
	ret_hdr->str_len = str_sec_size;

	*btf_size = size_needed;
	अगर (ret_next_str)
		*ret_next_str =
			next_str_idx < strs_cnt ? strs_idx[next_str_idx] : शून्य;

करोne:
	अगर (err) अणु
		अगर (raw_btf)
			मुक्त(raw_btf);
		अगर (strs_idx)
			मुक्त(strs_idx);
		वापस शून्य;
	पूर्ण
	वापस raw_btf;
पूर्ण

अटल व्योम करो_test_raw(अचिन्हित पूर्णांक test_num)
अणु
	काष्ठा btf_raw_test *test = &raw_tests[test_num - 1];
	काष्ठा bpf_create_map_attr create_attr = अणुपूर्ण;
	पूर्णांक map_fd = -1, btf_fd = -1;
	अचिन्हित पूर्णांक raw_btf_size;
	काष्ठा btf_header *hdr;
	व्योम *raw_btf;
	पूर्णांक err;

	अगर (!test__start_subtest(test->descr))
		वापस;

	raw_btf = btf_raw_create(&hdr_पंचांगpl,
				 test->raw_types,
				 test->str_sec,
				 test->str_sec_size,
				 &raw_btf_size, शून्य);
	अगर (!raw_btf)
		वापस;

	hdr = raw_btf;

	hdr->hdr_len = (पूर्णांक)hdr->hdr_len + test->hdr_len_delta;
	hdr->type_off = (पूर्णांक)hdr->type_off + test->type_off_delta;
	hdr->str_off = (पूर्णांक)hdr->str_off + test->str_off_delta;
	hdr->str_len = (पूर्णांक)hdr->str_len + test->str_len_delta;

	*btf_log_buf = '\0';
	btf_fd = bpf_load_btf(raw_btf, raw_btf_size,
			      btf_log_buf, BTF_LOG_BUF_SIZE,
			      always_log);
	मुक्त(raw_btf);

	err = ((btf_fd == -1) != test->btf_load_err);
	अगर (CHECK(err, "btf_fd:%d test->btf_load_err:%u",
		  btf_fd, test->btf_load_err) ||
	    CHECK(test->err_str && !म_माला(btf_log_buf, test->err_str),
		  "expected err_str:%s", test->err_str)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	अगर (err || btf_fd == -1)
		जाओ करोne;

	create_attr.name = test->map_name;
	create_attr.map_type = test->map_type;
	create_attr.key_size = test->key_size;
	create_attr.value_size = test->value_size;
	create_attr.max_entries = test->max_entries;
	create_attr.btf_fd = btf_fd;
	create_attr.btf_key_type_id = test->key_type_id;
	create_attr.btf_value_type_id = test->value_type_id;

	map_fd = bpf_create_map_xattr(&create_attr);

	err = ((map_fd == -1) != test->map_create_err);
	CHECK(err, "map_fd:%d test->map_create_err:%u",
	      map_fd, test->map_create_err);

करोne:
	अगर (*btf_log_buf && (err || always_log))
		ख_लिखो(मानक_त्रुटि, "\n%s", btf_log_buf);
	अगर (btf_fd != -1)
		बंद(btf_fd);
	अगर (map_fd != -1)
		बंद(map_fd);
पूर्ण

काष्ठा btf_get_info_test अणु
	स्थिर अक्षर *descr;
	स्थिर अक्षर *str_sec;
	__u32 raw_types[MAX_NR_RAW_U32];
	__u32 str_sec_size;
	पूर्णांक btf_size_delta;
	पूर्णांक (*special_test)(अचिन्हित पूर्णांक test_num);
पूर्ण;

अटल पूर्णांक test_big_btf_info(अचिन्हित पूर्णांक test_num);
अटल पूर्णांक test_btf_id(अचिन्हित पूर्णांक test_num);

स्थिर काष्ठा btf_get_info_test get_info_tests[] = अणु
अणु
	.descr = "== raw_btf_size+1",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "",
	.str_sec_size = माप(""),
	.btf_size_delta = 1,
पूर्ण,
अणु
	.descr = "== raw_btf_size-3",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "",
	.str_sec_size = माप(""),
	.btf_size_delta = -3,
पूर्ण,
अणु
	.descr = "Large bpf_btf_info",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "",
	.str_sec_size = माप(""),
	.special_test = test_big_btf_info,
पूर्ण,
अणु
	.descr = "BTF ID",
	.raw_types = अणु
		/* पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),
		/* अचिन्हित पूर्णांक */			/* [2] */
		BTF_TYPE_INT_ENC(0, 0, 0, 32, 4),
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "",
	.str_sec_size = माप(""),
	.special_test = test_btf_id,
पूर्ण,
पूर्ण;

अटल पूर्णांक test_big_btf_info(अचिन्हित पूर्णांक test_num)
अणु
	स्थिर काष्ठा btf_get_info_test *test = &get_info_tests[test_num - 1];
	uपूर्णांक8_t *raw_btf = शून्य, *user_btf = शून्य;
	अचिन्हित पूर्णांक raw_btf_size;
	काष्ठा अणु
		काष्ठा bpf_btf_info info;
		uपूर्णांक64_t garbage;
	पूर्ण info_garbage;
	काष्ठा bpf_btf_info *info;
	पूर्णांक btf_fd = -1, err;
	uपूर्णांक32_t info_len;

	raw_btf = btf_raw_create(&hdr_पंचांगpl,
				 test->raw_types,
				 test->str_sec,
				 test->str_sec_size,
				 &raw_btf_size, शून्य);

	अगर (!raw_btf)
		वापस -1;

	*btf_log_buf = '\0';

	user_btf = दो_स्मृति(raw_btf_size);
	अगर (CHECK(!user_btf, "!user_btf")) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	btf_fd = bpf_load_btf(raw_btf, raw_btf_size,
			      btf_log_buf, BTF_LOG_BUF_SIZE,
			      always_log);
	अगर (CHECK(btf_fd == -1, "errno:%d", त्रुटि_सं)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	/*
	 * GET_INFO should error out अगर the userspace info
	 * has non zero tailing bytes.
	 */
	info = &info_garbage.info;
	स_रखो(info, 0, माप(*info));
	info_garbage.garbage = 0xdeadbeef;
	info_len = माप(info_garbage);
	info->btf = ptr_to_u64(user_btf);
	info->btf_size = raw_btf_size;

	err = bpf_obj_get_info_by_fd(btf_fd, info, &info_len);
	अगर (CHECK(!err, "!err")) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	/*
	 * GET_INFO should succeed even info_len is larger than
	 * the kernel supported as दीर्घ as tailing bytes are zero.
	 * The kernel supported info len should also be वापसed
	 * to userspace.
	 */
	info_garbage.garbage = 0;
	err = bpf_obj_get_info_by_fd(btf_fd, info, &info_len);
	अगर (CHECK(err || info_len != माप(*info),
		  "err:%d errno:%d info_len:%u sizeof(*info):%zu",
		  err, त्रुटि_सं, info_len, माप(*info))) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	ख_लिखो(मानक_त्रुटि, "OK");

करोne:
	अगर (*btf_log_buf && (err || always_log))
		ख_लिखो(मानक_त्रुटि, "\n%s", btf_log_buf);

	मुक्त(raw_btf);
	मुक्त(user_btf);

	अगर (btf_fd != -1)
		बंद(btf_fd);

	वापस err;
पूर्ण

अटल पूर्णांक test_btf_id(अचिन्हित पूर्णांक test_num)
अणु
	स्थिर काष्ठा btf_get_info_test *test = &get_info_tests[test_num - 1];
	काष्ठा bpf_create_map_attr create_attr = अणुपूर्ण;
	uपूर्णांक8_t *raw_btf = शून्य, *user_btf[2] = अणुपूर्ण;
	पूर्णांक btf_fd[2] = अणु-1, -1पूर्ण, map_fd = -1;
	काष्ठा bpf_map_info map_info = अणुपूर्ण;
	काष्ठा bpf_btf_info info[2] = अणुपूर्ण;
	अचिन्हित पूर्णांक raw_btf_size;
	uपूर्णांक32_t info_len;
	पूर्णांक err, i, ret;

	raw_btf = btf_raw_create(&hdr_पंचांगpl,
				 test->raw_types,
				 test->str_sec,
				 test->str_sec_size,
				 &raw_btf_size, शून्य);

	अगर (!raw_btf)
		वापस -1;

	*btf_log_buf = '\0';

	क्रम (i = 0; i < 2; i++) अणु
		user_btf[i] = दो_स्मृति(raw_btf_size);
		अगर (CHECK(!user_btf[i], "!user_btf[%d]", i)) अणु
			err = -1;
			जाओ करोne;
		पूर्ण
		info[i].btf = ptr_to_u64(user_btf[i]);
		info[i].btf_size = raw_btf_size;
	पूर्ण

	btf_fd[0] = bpf_load_btf(raw_btf, raw_btf_size,
				 btf_log_buf, BTF_LOG_BUF_SIZE,
				 always_log);
	अगर (CHECK(btf_fd[0] == -1, "errno:%d", त्रुटि_सं)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	/* Test BPF_OBJ_GET_INFO_BY_ID on btf_id */
	info_len = माप(info[0]);
	err = bpf_obj_get_info_by_fd(btf_fd[0], &info[0], &info_len);
	अगर (CHECK(err, "errno:%d", त्रुटि_सं)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	btf_fd[1] = bpf_btf_get_fd_by_id(info[0].id);
	अगर (CHECK(btf_fd[1] == -1, "errno:%d", त्रुटि_सं)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	ret = 0;
	err = bpf_obj_get_info_by_fd(btf_fd[1], &info[1], &info_len);
	अगर (CHECK(err || info[0].id != info[1].id ||
		  info[0].btf_size != info[1].btf_size ||
		  (ret = स_भेद(user_btf[0], user_btf[1], info[0].btf_size)),
		  "err:%d errno:%d id0:%u id1:%u btf_size0:%u btf_size1:%u memcmp:%d",
		  err, त्रुटि_सं, info[0].id, info[1].id,
		  info[0].btf_size, info[1].btf_size, ret)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	/* Test btf members in काष्ठा bpf_map_info */
	create_attr.name = "test_btf_id";
	create_attr.map_type = BPF_MAP_TYPE_ARRAY;
	create_attr.key_size = माप(पूर्णांक);
	create_attr.value_size = माप(अचिन्हित पूर्णांक);
	create_attr.max_entries = 4;
	create_attr.btf_fd = btf_fd[0];
	create_attr.btf_key_type_id = 1;
	create_attr.btf_value_type_id = 2;

	map_fd = bpf_create_map_xattr(&create_attr);
	अगर (CHECK(map_fd == -1, "errno:%d", त्रुटि_सं)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	info_len = माप(map_info);
	err = bpf_obj_get_info_by_fd(map_fd, &map_info, &info_len);
	अगर (CHECK(err || map_info.btf_id != info[0].id ||
		  map_info.btf_key_type_id != 1 || map_info.btf_value_type_id != 2,
		  "err:%d errno:%d info.id:%u btf_id:%u btf_key_type_id:%u btf_value_type_id:%u",
		  err, त्रुटि_सं, info[0].id, map_info.btf_id, map_info.btf_key_type_id,
		  map_info.btf_value_type_id)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	क्रम (i = 0; i < 2; i++) अणु
		बंद(btf_fd[i]);
		btf_fd[i] = -1;
	पूर्ण

	/* Test BTF ID is हटाओd from the kernel */
	btf_fd[0] = bpf_btf_get_fd_by_id(map_info.btf_id);
	अगर (CHECK(btf_fd[0] == -1, "errno:%d", त्रुटि_सं)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण
	बंद(btf_fd[0]);
	btf_fd[0] = -1;

	/* The map holds the last ref to BTF and its btf_id */
	बंद(map_fd);
	map_fd = -1;
	btf_fd[0] = bpf_btf_get_fd_by_id(map_info.btf_id);
	अगर (CHECK(btf_fd[0] != -1, "BTF lingers")) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	ख_लिखो(मानक_त्रुटि, "OK");

करोne:
	अगर (*btf_log_buf && (err || always_log))
		ख_लिखो(मानक_त्रुटि, "\n%s", btf_log_buf);

	मुक्त(raw_btf);
	अगर (map_fd != -1)
		बंद(map_fd);
	क्रम (i = 0; i < 2; i++) अणु
		मुक्त(user_btf[i]);
		अगर (btf_fd[i] != -1)
			बंद(btf_fd[i]);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम करो_test_get_info(अचिन्हित पूर्णांक test_num)
अणु
	स्थिर काष्ठा btf_get_info_test *test = &get_info_tests[test_num - 1];
	अचिन्हित पूर्णांक raw_btf_size, user_btf_size, expected_nbytes;
	uपूर्णांक8_t *raw_btf = शून्य, *user_btf = शून्य;
	काष्ठा bpf_btf_info info = अणुपूर्ण;
	पूर्णांक btf_fd = -1, err, ret;
	uपूर्णांक32_t info_len;

	अगर (!test__start_subtest(test->descr))
		वापस;

	अगर (test->special_test) अणु
		err = test->special_test(test_num);
		अगर (CHECK(err, "failed: %d\n", err))
			वापस;
	पूर्ण

	raw_btf = btf_raw_create(&hdr_पंचांगpl,
				 test->raw_types,
				 test->str_sec,
				 test->str_sec_size,
				 &raw_btf_size, शून्य);

	अगर (!raw_btf)
		वापस;

	*btf_log_buf = '\0';

	user_btf = दो_स्मृति(raw_btf_size);
	अगर (CHECK(!user_btf, "!user_btf")) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	btf_fd = bpf_load_btf(raw_btf, raw_btf_size,
			      btf_log_buf, BTF_LOG_BUF_SIZE,
			      always_log);
	अगर (CHECK(btf_fd == -1, "errno:%d", त्रुटि_सं)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	user_btf_size = (पूर्णांक)raw_btf_size + test->btf_size_delta;
	expected_nbytes = min(raw_btf_size, user_btf_size);
	अगर (raw_btf_size > expected_nbytes)
		स_रखो(user_btf + expected_nbytes, 0xff,
		       raw_btf_size - expected_nbytes);

	info_len = माप(info);
	info.btf = ptr_to_u64(user_btf);
	info.btf_size = user_btf_size;

	ret = 0;
	err = bpf_obj_get_info_by_fd(btf_fd, &info, &info_len);
	अगर (CHECK(err || !info.id || info_len != माप(info) ||
		  info.btf_size != raw_btf_size ||
		  (ret = स_भेद(raw_btf, user_btf, expected_nbytes)),
		  "err:%d errno:%d info.id:%u info_len:%u sizeof(info):%zu raw_btf_size:%u info.btf_size:%u expected_nbytes:%u memcmp:%d",
		  err, त्रुटि_सं, info.id, info_len, माप(info),
		  raw_btf_size, info.btf_size, expected_nbytes, ret)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	जबतक (expected_nbytes < raw_btf_size) अणु
		ख_लिखो(मानक_त्रुटि, "%u...", expected_nbytes);
		अगर (CHECK(user_btf[expected_nbytes++] != 0xff,
			  "user_btf[%u]:%x != 0xff", expected_nbytes - 1,
			  user_btf[expected_nbytes - 1])) अणु
			err = -1;
			जाओ करोne;
		पूर्ण
	पूर्ण

	ख_लिखो(मानक_त्रुटि, "OK");

करोne:
	अगर (*btf_log_buf && (err || always_log))
		ख_लिखो(मानक_त्रुटि, "\n%s", btf_log_buf);

	मुक्त(raw_btf);
	मुक्त(user_btf);

	अगर (btf_fd != -1)
		बंद(btf_fd);
पूर्ण

काष्ठा btf_file_test अणु
	स्थिर अक्षर *file;
	bool btf_kv_notfound;
पूर्ण;

अटल काष्ठा btf_file_test file_tests[] = अणु
	अणु .file = "test_btf_haskv.o", पूर्ण,
	अणु .file = "test_btf_newkv.o", पूर्ण,
	अणु .file = "test_btf_nokv.o", .btf_kv_notfound = true, पूर्ण,
पूर्ण;

अटल व्योम करो_test_file(अचिन्हित पूर्णांक test_num)
अणु
	स्थिर काष्ठा btf_file_test *test = &file_tests[test_num - 1];
	स्थिर अक्षर *expected_fnames[] = अणु"_dummy_tracepoint",
					 "test_long_fname_1",
					 "test_long_fname_2"पूर्ण;
	काष्ठा btf_ext *btf_ext = शून्य;
	काष्ठा bpf_prog_info info = अणुपूर्ण;
	काष्ठा bpf_object *obj = शून्य;
	काष्ठा bpf_func_info *finfo;
	काष्ठा bpf_program *prog;
	__u32 info_len, rec_size;
	bool has_btf_ext = false;
	काष्ठा btf *btf = शून्य;
	व्योम *func_info = शून्य;
	काष्ठा bpf_map *map;
	पूर्णांक i, err, prog_fd;

	अगर (!test__start_subtest(test->file))
		वापस;

	btf = btf__parse_elf(test->file, &btf_ext);
	अगर (IS_ERR(btf)) अणु
		अगर (PTR_ERR(btf) == -ENOENT) अणु
			म_लिखो("%s:SKIP: No ELF %s found", __func__, BTF_ELF_SEC);
			test__skip();
			वापस;
		पूर्ण
		वापस;
	पूर्ण
	btf__मुक्त(btf);

	has_btf_ext = btf_ext != शून्य;
	btf_ext__मुक्त(btf_ext);

	obj = bpf_object__खोलो(test->file);
	अगर (CHECK(IS_ERR(obj), "obj: %ld", PTR_ERR(obj)))
		वापस;

	prog = bpf_program__next(शून्य, obj);
	अगर (CHECK(!prog, "Cannot find bpf_prog")) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	bpf_program__set_type(prog, BPF_PROG_TYPE_TRACEPOINT);
	err = bpf_object__load(obj);
	अगर (CHECK(err < 0, "bpf_object__load: %d", err))
		जाओ करोne;
	prog_fd = bpf_program__fd(prog);

	map = bpf_object__find_map_by_name(obj, "btf_map");
	अगर (CHECK(!map, "btf_map not found")) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	err = (bpf_map__btf_key_type_id(map) == 0 || bpf_map__btf_value_type_id(map) == 0)
		!= test->btf_kv_notfound;
	अगर (CHECK(err, "btf_key_type_id:%u btf_value_type_id:%u test->btf_kv_notfound:%u",
		  bpf_map__btf_key_type_id(map), bpf_map__btf_value_type_id(map),
		  test->btf_kv_notfound))
		जाओ करोne;

	अगर (!has_btf_ext)
		जाओ skip;

	/* get necessary program info */
	info_len = माप(काष्ठा bpf_prog_info);
	err = bpf_obj_get_info_by_fd(prog_fd, &info, &info_len);

	अगर (CHECK(err == -1, "invalid get info (1st) errno:%d", त्रुटि_सं)) अणु
		ख_लिखो(मानक_त्रुटि, "%s\n", btf_log_buf);
		err = -1;
		जाओ करोne;
	पूर्ण
	अगर (CHECK(info.nr_func_info != 3,
		  "incorrect info.nr_func_info (1st) %d",
		  info.nr_func_info)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण
	rec_size = info.func_info_rec_size;
	अगर (CHECK(rec_size != माप(काष्ठा bpf_func_info),
		  "incorrect info.func_info_rec_size (1st) %d\n", rec_size)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	func_info = दो_स्मृति(info.nr_func_info * rec_size);
	अगर (CHECK(!func_info, "out of memory")) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	/* reset info to only retrieve func_info related data */
	स_रखो(&info, 0, माप(info));
	info.nr_func_info = 3;
	info.func_info_rec_size = rec_size;
	info.func_info = ptr_to_u64(func_info);

	err = bpf_obj_get_info_by_fd(prog_fd, &info, &info_len);

	अगर (CHECK(err == -1, "invalid get info (2nd) errno:%d", त्रुटि_सं)) अणु
		ख_लिखो(मानक_त्रुटि, "%s\n", btf_log_buf);
		err = -1;
		जाओ करोne;
	पूर्ण
	अगर (CHECK(info.nr_func_info != 3,
		  "incorrect info.nr_func_info (2nd) %d",
		  info.nr_func_info)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण
	अगर (CHECK(info.func_info_rec_size != rec_size,
		  "incorrect info.func_info_rec_size (2nd) %d",
		  info.func_info_rec_size)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	err = btf__get_from_id(info.btf_id, &btf);
	अगर (CHECK(err, "cannot get btf from kernel, err: %d", err))
		जाओ करोne;

	/* check three functions */
	finfo = func_info;
	क्रम (i = 0; i < 3; i++) अणु
		स्थिर काष्ठा btf_type *t;
		स्थिर अक्षर *fname;

		t = btf__type_by_id(btf, finfo->type_id);
		अगर (CHECK(!t, "btf__type_by_id failure: id %u",
			  finfo->type_id)) अणु
			err = -1;
			जाओ करोne;
		पूर्ण

		fname = btf__name_by_offset(btf, t->name_off);
		err = म_भेद(fname, expected_fnames[i]);
		/* क्रम the second and third functions in .text section,
		 * the compiler may order them either way.
		 */
		अगर (i && err)
			err = म_भेद(fname, expected_fnames[3 - i]);
		अगर (CHECK(err, "incorrect fname %s", fname ? : "")) अणु
			err = -1;
			जाओ करोne;
		पूर्ण

		finfo = (व्योम *)finfo + rec_size;
	पूर्ण

skip:
	ख_लिखो(मानक_त्रुटि, "OK");

करोne:
	मुक्त(func_info);
	bpf_object__बंद(obj);
पूर्ण

स्थिर अक्षर *pprपूर्णांक_क्रमागत_str[] = अणु
	"ENUM_ZERO",
	"ENUM_ONE",
	"ENUM_TWO",
	"ENUM_THREE",
पूर्ण;

काष्ठा pprपूर्णांक_mapv अणु
	uपूर्णांक32_t ui32;
	uपूर्णांक16_t ui16;
	/* 2 bytes hole */
	पूर्णांक32_t si32;
	uपूर्णांक32_t unused_bits2a:2,
		bits28:28,
		unused_bits2b:2;
	जोड़ अणु
		uपूर्णांक64_t ui64;
		uपूर्णांक8_t ui8a[8];
	पूर्ण;
	क्रमागत अणु
		ENUM_ZERO,
		ENUM_ONE,
		ENUM_TWO,
		ENUM_THREE,
	पूर्ण aक्रमागत;
	uपूर्णांक32_t ui32b;
	uपूर्णांक32_t bits2c:2;
	uपूर्णांक8_t si8_4[2][2];
पूर्ण;

#अगर_घोषित __SIZखातापूर्ण_INT128__
काष्ठा pprपूर्णांक_mapv_पूर्णांक128 अणु
	__पूर्णांक128 si128a;
	__पूर्णांक128 si128b;
	अचिन्हित __पूर्णांक128 bits3:3;
	अचिन्हित __पूर्णांक128 bits80:80;
	अचिन्हित __पूर्णांक128 ui128;
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा btf_raw_test pprपूर्णांक_test_ढाँचा[] = अणु
अणु
	.raw_types = अणु
		/* unsighed अक्षर */			/* [1] */
		BTF_TYPE_INT_ENC(NAME_TBD, 0, 0, 8, 1),
		/* अचिन्हित लघु */			/* [2] */
		BTF_TYPE_INT_ENC(NAME_TBD, 0, 0, 16, 2),
		/* अचिन्हित पूर्णांक */			/* [3] */
		BTF_TYPE_INT_ENC(NAME_TBD, 0, 0, 32, 4),
		/* पूर्णांक */				/* [4] */
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),
		/* अचिन्हित दीर्घ दीर्घ */		/* [5] */
		BTF_TYPE_INT_ENC(NAME_TBD, 0, 0, 64, 8),
		/* 2 bits */				/* [6] */
		BTF_TYPE_INT_ENC(0, 0, 0, 2, 2),
		/* 28 bits */				/* [7] */
		BTF_TYPE_INT_ENC(0, 0, 0, 28, 4),
		/* uपूर्णांक8_t[8] */			/* [8] */
		BTF_TYPE_ARRAY_ENC(9, 1, 8),
		/* प्रकार अचिन्हित अक्षर uपूर्णांक8_t */	/* [9] */
		BTF_TYPEDEF_ENC(NAME_TBD, 1),
		/* प्रकार अचिन्हित लघु uपूर्णांक16_t */	/* [10] */
		BTF_TYPEDEF_ENC(NAME_TBD, 2),
		/* प्रकार अचिन्हित पूर्णांक uपूर्णांक32_t */	/* [11] */
		BTF_TYPEDEF_ENC(NAME_TBD, 3),
		/* प्रकार पूर्णांक पूर्णांक32_t */		/* [12] */
		BTF_TYPEDEF_ENC(NAME_TBD, 4),
		/* प्रकार अचिन्हित दीर्घ दीर्घ uपूर्णांक64_t *//* [13] */
		BTF_TYPEDEF_ENC(NAME_TBD, 5),
		/* जोड़ (anon) */			/* [14] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_UNION, 0, 2), 8),
		BTF_MEMBER_ENC(NAME_TBD, 13, 0),/* uपूर्णांक64_t ui64; */
		BTF_MEMBER_ENC(NAME_TBD, 8, 0),	/* uपूर्णांक8_t ui8a[8]; */
		/* क्रमागत (anon) */			/* [15] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_ENUM, 0, 4), 4),
		BTF_ENUM_ENC(NAME_TBD, 0),
		BTF_ENUM_ENC(NAME_TBD, 1),
		BTF_ENUM_ENC(NAME_TBD, 2),
		BTF_ENUM_ENC(NAME_TBD, 3),
		/* काष्ठा pprपूर्णांक_mapv */		/* [16] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 0, 11), 40),
		BTF_MEMBER_ENC(NAME_TBD, 11, 0),	/* uपूर्णांक32_t ui32 */
		BTF_MEMBER_ENC(NAME_TBD, 10, 32),	/* uपूर्णांक16_t ui16 */
		BTF_MEMBER_ENC(NAME_TBD, 12, 64),	/* पूर्णांक32_t si32 */
		BTF_MEMBER_ENC(NAME_TBD, 6, 96),	/* unused_bits2a */
		BTF_MEMBER_ENC(NAME_TBD, 7, 98),	/* bits28 */
		BTF_MEMBER_ENC(NAME_TBD, 6, 126),	/* unused_bits2b */
		BTF_MEMBER_ENC(0, 14, 128),		/* जोड़ (anon) */
		BTF_MEMBER_ENC(NAME_TBD, 15, 192),	/* aक्रमागत */
		BTF_MEMBER_ENC(NAME_TBD, 11, 224),	/* uपूर्णांक32_t ui32b */
		BTF_MEMBER_ENC(NAME_TBD, 6, 256),	/* bits2c */
		BTF_MEMBER_ENC(NAME_TBD, 17, 264),	/* si8_4 */
		BTF_TYPE_ARRAY_ENC(18, 1, 2),		/* [17] */
		BTF_TYPE_ARRAY_ENC(1, 1, 2),		/* [18] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0unsigned char\0unsigned short\0unsigned int\0int\0unsigned long long\0uint8_t\0uint16_t\0uint32_t\0int32_t\0uint64_t\0ui64\0ui8a\0ENUM_ZERO\0ENUM_ONE\0ENUM_TWO\0ENUM_THREE\0pprint_mapv\0ui32\0ui16\0si32\0unused_bits2a\0bits28\0unused_bits2b\0aenum\0ui32b\0bits2c\0si8_4"),
	.key_size = माप(अचिन्हित पूर्णांक),
	.value_size = माप(काष्ठा pprपूर्णांक_mapv),
	.key_type_id = 3,	/* अचिन्हित पूर्णांक */
	.value_type_id = 16,	/* काष्ठा pprपूर्णांक_mapv */
	.max_entries = 128,
पूर्ण,

अणु
	/* this type will have the same type as the
	 * first .raw_types definition, but काष्ठा type will
	 * be encoded with kind_flag set.
	 */
	.raw_types = अणु
		/* unsighed अक्षर */			/* [1] */
		BTF_TYPE_INT_ENC(NAME_TBD, 0, 0, 8, 1),
		/* अचिन्हित लघु */			/* [2] */
		BTF_TYPE_INT_ENC(NAME_TBD, 0, 0, 16, 2),
		/* अचिन्हित पूर्णांक */			/* [3] */
		BTF_TYPE_INT_ENC(NAME_TBD, 0, 0, 32, 4),
		/* पूर्णांक */				/* [4] */
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),
		/* अचिन्हित दीर्घ दीर्घ */		/* [5] */
		BTF_TYPE_INT_ENC(NAME_TBD, 0, 0, 64, 8),
		BTF_TYPE_INT_ENC(0, 0, 0, 32, 4),	/* [6] */
		BTF_TYPE_INT_ENC(0, 0, 0, 32, 4),	/* [7] */
		/* uपूर्णांक8_t[8] */			/* [8] */
		BTF_TYPE_ARRAY_ENC(9, 1, 8),
		/* प्रकार अचिन्हित अक्षर uपूर्णांक8_t */	/* [9] */
		BTF_TYPEDEF_ENC(NAME_TBD, 1),
		/* प्रकार अचिन्हित लघु uपूर्णांक16_t */	/* [10] */
		BTF_TYPEDEF_ENC(NAME_TBD, 2),
		/* प्रकार अचिन्हित पूर्णांक uपूर्णांक32_t */	/* [11] */
		BTF_TYPEDEF_ENC(NAME_TBD, 3),
		/* प्रकार पूर्णांक पूर्णांक32_t */		/* [12] */
		BTF_TYPEDEF_ENC(NAME_TBD, 4),
		/* प्रकार अचिन्हित दीर्घ दीर्घ uपूर्णांक64_t *//* [13] */
		BTF_TYPEDEF_ENC(NAME_TBD, 5),
		/* जोड़ (anon) */			/* [14] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_UNION, 0, 2), 8),
		BTF_MEMBER_ENC(NAME_TBD, 13, 0),/* uपूर्णांक64_t ui64; */
		BTF_MEMBER_ENC(NAME_TBD, 8, 0),	/* uपूर्णांक8_t ui8a[8]; */
		/* क्रमागत (anon) */			/* [15] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_ENUM, 0, 4), 4),
		BTF_ENUM_ENC(NAME_TBD, 0),
		BTF_ENUM_ENC(NAME_TBD, 1),
		BTF_ENUM_ENC(NAME_TBD, 2),
		BTF_ENUM_ENC(NAME_TBD, 3),
		/* काष्ठा pprपूर्णांक_mapv */		/* [16] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 1, 11), 40),
		BTF_MEMBER_ENC(NAME_TBD, 11, BTF_MEMBER_OFFSET(0, 0)),	/* uपूर्णांक32_t ui32 */
		BTF_MEMBER_ENC(NAME_TBD, 10, BTF_MEMBER_OFFSET(0, 32)),	/* uपूर्णांक16_t ui16 */
		BTF_MEMBER_ENC(NAME_TBD, 12, BTF_MEMBER_OFFSET(0, 64)),	/* पूर्णांक32_t si32 */
		BTF_MEMBER_ENC(NAME_TBD, 6, BTF_MEMBER_OFFSET(2, 96)),	/* unused_bits2a */
		BTF_MEMBER_ENC(NAME_TBD, 7, BTF_MEMBER_OFFSET(28, 98)),	/* bits28 */
		BTF_MEMBER_ENC(NAME_TBD, 6, BTF_MEMBER_OFFSET(2, 126)),	/* unused_bits2b */
		BTF_MEMBER_ENC(0, 14, BTF_MEMBER_OFFSET(0, 128)),	/* जोड़ (anon) */
		BTF_MEMBER_ENC(NAME_TBD, 15, BTF_MEMBER_OFFSET(0, 192)),	/* aक्रमागत */
		BTF_MEMBER_ENC(NAME_TBD, 11, BTF_MEMBER_OFFSET(0, 224)),	/* uपूर्णांक32_t ui32b */
		BTF_MEMBER_ENC(NAME_TBD, 6, BTF_MEMBER_OFFSET(2, 256)),	/* bits2c */
		BTF_MEMBER_ENC(NAME_TBD, 17, 264),	/* si8_4 */
		BTF_TYPE_ARRAY_ENC(18, 1, 2),		/* [17] */
		BTF_TYPE_ARRAY_ENC(1, 1, 2),		/* [18] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0unsigned char\0unsigned short\0unsigned int\0int\0unsigned long long\0uint8_t\0uint16_t\0uint32_t\0int32_t\0uint64_t\0ui64\0ui8a\0ENUM_ZERO\0ENUM_ONE\0ENUM_TWO\0ENUM_THREE\0pprint_mapv\0ui32\0ui16\0si32\0unused_bits2a\0bits28\0unused_bits2b\0aenum\0ui32b\0bits2c\0si8_4"),
	.key_size = माप(अचिन्हित पूर्णांक),
	.value_size = माप(काष्ठा pprपूर्णांक_mapv),
	.key_type_id = 3,	/* अचिन्हित पूर्णांक */
	.value_type_id = 16,	/* काष्ठा pprपूर्णांक_mapv */
	.max_entries = 128,
पूर्ण,

अणु
	/* this type will have the same layout as the
	 * first .raw_types definition. The काष्ठा type will
	 * be encoded with kind_flag set, bitfield members
	 * are added प्रकार/स्थिर/अस्थिर, and bitfield members
	 * will have both पूर्णांक and क्रमागत types.
	 */
	.raw_types = अणु
		/* unsighed अक्षर */			/* [1] */
		BTF_TYPE_INT_ENC(NAME_TBD, 0, 0, 8, 1),
		/* अचिन्हित लघु */			/* [2] */
		BTF_TYPE_INT_ENC(NAME_TBD, 0, 0, 16, 2),
		/* अचिन्हित पूर्णांक */			/* [3] */
		BTF_TYPE_INT_ENC(NAME_TBD, 0, 0, 32, 4),
		/* पूर्णांक */				/* [4] */
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),
		/* अचिन्हित दीर्घ दीर्घ */		/* [5] */
		BTF_TYPE_INT_ENC(NAME_TBD, 0, 0, 64, 8),
		BTF_TYPE_INT_ENC(0, 0, 0, 32, 4),	/* [6] */
		BTF_TYPE_INT_ENC(0, 0, 0, 32, 4),	/* [7] */
		/* uपूर्णांक8_t[8] */			/* [8] */
		BTF_TYPE_ARRAY_ENC(9, 1, 8),
		/* प्रकार अचिन्हित अक्षर uपूर्णांक8_t */	/* [9] */
		BTF_TYPEDEF_ENC(NAME_TBD, 1),
		/* प्रकार अचिन्हित लघु uपूर्णांक16_t */	/* [10] */
		BTF_TYPEDEF_ENC(NAME_TBD, 2),
		/* प्रकार अचिन्हित पूर्णांक uपूर्णांक32_t */	/* [11] */
		BTF_TYPEDEF_ENC(NAME_TBD, 3),
		/* प्रकार पूर्णांक पूर्णांक32_t */		/* [12] */
		BTF_TYPEDEF_ENC(NAME_TBD, 4),
		/* प्रकार अचिन्हित दीर्घ दीर्घ uपूर्णांक64_t *//* [13] */
		BTF_TYPEDEF_ENC(NAME_TBD, 5),
		/* जोड़ (anon) */			/* [14] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_UNION, 0, 2), 8),
		BTF_MEMBER_ENC(NAME_TBD, 13, 0),/* uपूर्णांक64_t ui64; */
		BTF_MEMBER_ENC(NAME_TBD, 8, 0),	/* uपूर्णांक8_t ui8a[8]; */
		/* क्रमागत (anon) */			/* [15] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_ENUM, 0, 4), 4),
		BTF_ENUM_ENC(NAME_TBD, 0),
		BTF_ENUM_ENC(NAME_TBD, 1),
		BTF_ENUM_ENC(NAME_TBD, 2),
		BTF_ENUM_ENC(NAME_TBD, 3),
		/* काष्ठा pprपूर्णांक_mapv */		/* [16] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 1, 11), 40),
		BTF_MEMBER_ENC(NAME_TBD, 11, BTF_MEMBER_OFFSET(0, 0)),	/* uपूर्णांक32_t ui32 */
		BTF_MEMBER_ENC(NAME_TBD, 10, BTF_MEMBER_OFFSET(0, 32)),	/* uपूर्णांक16_t ui16 */
		BTF_MEMBER_ENC(NAME_TBD, 12, BTF_MEMBER_OFFSET(0, 64)),	/* पूर्णांक32_t si32 */
		BTF_MEMBER_ENC(NAME_TBD, 17, BTF_MEMBER_OFFSET(2, 96)),	/* unused_bits2a */
		BTF_MEMBER_ENC(NAME_TBD, 7, BTF_MEMBER_OFFSET(28, 98)),	/* bits28 */
		BTF_MEMBER_ENC(NAME_TBD, 19, BTF_MEMBER_OFFSET(2, 126)),/* unused_bits2b */
		BTF_MEMBER_ENC(0, 14, BTF_MEMBER_OFFSET(0, 128)),	/* जोड़ (anon) */
		BTF_MEMBER_ENC(NAME_TBD, 15, BTF_MEMBER_OFFSET(0, 192)),	/* aक्रमागत */
		BTF_MEMBER_ENC(NAME_TBD, 11, BTF_MEMBER_OFFSET(0, 224)),	/* uपूर्णांक32_t ui32b */
		BTF_MEMBER_ENC(NAME_TBD, 17, BTF_MEMBER_OFFSET(2, 256)),	/* bits2c */
		BTF_MEMBER_ENC(NAME_TBD, 20, BTF_MEMBER_OFFSET(0, 264)),	/* si8_4 */
		/* प्रकार अचिन्हित पूर्णांक ___पूर्णांक */	/* [17] */
		BTF_TYPEDEF_ENC(NAME_TBD, 18),
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_VOLATILE, 0, 0), 6),	/* [18] */
		BTF_TYPE_ENC(0, BTF_INFO_ENC(BTF_KIND_CONST, 0, 0), 15),	/* [19] */
		BTF_TYPE_ARRAY_ENC(21, 1, 2),					/* [20] */
		BTF_TYPE_ARRAY_ENC(1, 1, 2),					/* [21] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0unsigned char\0unsigned short\0unsigned int\0int\0unsigned long long\0uint8_t\0uint16_t\0uint32_t\0int32_t\0uint64_t\0ui64\0ui8a\0ENUM_ZERO\0ENUM_ONE\0ENUM_TWO\0ENUM_THREE\0pprint_mapv\0ui32\0ui16\0si32\0unused_bits2a\0bits28\0unused_bits2b\0aenum\0ui32b\0bits2c\0___int\0si8_4"),
	.key_size = माप(अचिन्हित पूर्णांक),
	.value_size = माप(काष्ठा pprपूर्णांक_mapv),
	.key_type_id = 3,	/* अचिन्हित पूर्णांक */
	.value_type_id = 16,	/* काष्ठा pprपूर्णांक_mapv */
	.max_entries = 128,
पूर्ण,

#अगर_घोषित __SIZखातापूर्ण_INT128__
अणु
	/* test पूर्णांक128 */
	.raw_types = अणु
		/* अचिन्हित पूर्णांक */				/* [1] */
		BTF_TYPE_INT_ENC(NAME_TBD, 0, 0, 32, 4),
		/* __पूर्णांक128 */					/* [2] */
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 128, 16),
		/* अचिन्हित __पूर्णांक128 */				/* [3] */
		BTF_TYPE_INT_ENC(NAME_TBD, 0, 0, 128, 16),
		/* काष्ठा pprपूर्णांक_mapv_पूर्णांक128 */			/* [4] */
		BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_STRUCT, 1, 5), 64),
		BTF_MEMBER_ENC(NAME_TBD, 2, BTF_MEMBER_OFFSET(0, 0)),		/* si128a */
		BTF_MEMBER_ENC(NAME_TBD, 2, BTF_MEMBER_OFFSET(0, 128)),		/* si128b */
		BTF_MEMBER_ENC(NAME_TBD, 3, BTF_MEMBER_OFFSET(3, 256)),		/* bits3 */
		BTF_MEMBER_ENC(NAME_TBD, 3, BTF_MEMBER_OFFSET(80, 259)),	/* bits80 */
		BTF_MEMBER_ENC(NAME_TBD, 3, BTF_MEMBER_OFFSET(0, 384)),		/* ui128 */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0unsigned int\0__int128\0unsigned __int128\0pprint_mapv_int128\0si128a\0si128b\0bits3\0bits80\0ui128"),
	.key_size = माप(अचिन्हित पूर्णांक),
	.value_size = माप(काष्ठा pprपूर्णांक_mapv_पूर्णांक128),
	.key_type_id = 1,
	.value_type_id = 4,
	.max_entries = 128,
	.mapv_kind = PPRINT_MAPV_KIND_INT128,
पूर्ण,
#पूर्ण_अगर

पूर्ण;

अटल काष्ठा btf_pprपूर्णांक_test_meta अणु
	स्थिर अक्षर *descr;
	क्रमागत bpf_map_type map_type;
	स्थिर अक्षर *map_name;
	bool ordered_map;
	bool lossless_map;
	bool percpu_map;
पूर्ण pprपूर्णांक_tests_meta[] = अणु
अणु
	.descr = "BTF pretty print array",
	.map_type = BPF_MAP_TYPE_ARRAY,
	.map_name = "pprint_test_array",
	.ordered_map = true,
	.lossless_map = true,
	.percpu_map = false,
पूर्ण,

अणु
	.descr = "BTF pretty print hash",
	.map_type = BPF_MAP_TYPE_HASH,
	.map_name = "pprint_test_hash",
	.ordered_map = false,
	.lossless_map = true,
	.percpu_map = false,
पूर्ण,

अणु
	.descr = "BTF pretty print lru hash",
	.map_type = BPF_MAP_TYPE_LRU_HASH,
	.map_name = "pprint_test_lru_hash",
	.ordered_map = false,
	.lossless_map = false,
	.percpu_map = false,
पूर्ण,

अणु
	.descr = "BTF pretty print percpu array",
	.map_type = BPF_MAP_TYPE_PERCPU_ARRAY,
	.map_name = "pprint_test_percpu_array",
	.ordered_map = true,
	.lossless_map = true,
	.percpu_map = true,
पूर्ण,

अणु
	.descr = "BTF pretty print percpu hash",
	.map_type = BPF_MAP_TYPE_PERCPU_HASH,
	.map_name = "pprint_test_percpu_hash",
	.ordered_map = false,
	.lossless_map = true,
	.percpu_map = true,
पूर्ण,

अणु
	.descr = "BTF pretty print lru percpu hash",
	.map_type = BPF_MAP_TYPE_LRU_PERCPU_HASH,
	.map_name = "pprint_test_lru_percpu_hash",
	.ordered_map = false,
	.lossless_map = false,
	.percpu_map = true,
पूर्ण,

पूर्ण;

अटल माप_प्रकार get_pprपूर्णांक_mapv_size(क्रमागत pprपूर्णांक_mapv_kind_t mapv_kind)
अणु
	अगर (mapv_kind == PPRINT_MAPV_KIND_BASIC)
		वापस माप(काष्ठा pprपूर्णांक_mapv);

#अगर_घोषित __SIZखातापूर्ण_INT128__
	अगर (mapv_kind == PPRINT_MAPV_KIND_INT128)
		वापस माप(काष्ठा pprपूर्णांक_mapv_पूर्णांक128);
#पूर्ण_अगर

	निश्चित(0);
पूर्ण

अटल व्योम set_pprपूर्णांक_mapv(क्रमागत pprपूर्णांक_mapv_kind_t mapv_kind,
			    व्योम *mapv, uपूर्णांक32_t i,
			    पूर्णांक num_cpus, पूर्णांक rounded_value_size)
अणु
	पूर्णांक cpu;

	अगर (mapv_kind == PPRINT_MAPV_KIND_BASIC) अणु
		काष्ठा pprपूर्णांक_mapv *v = mapv;

		क्रम (cpu = 0; cpu < num_cpus; cpu++) अणु
			v->ui32 = i + cpu;
			v->si32 = -i;
			v->unused_bits2a = 3;
			v->bits28 = i;
			v->unused_bits2b = 3;
			v->ui64 = i;
			v->aक्रमागत = i & 0x03;
			v->ui32b = 4;
			v->bits2c = 1;
			v->si8_4[0][0] = (cpu + i) & 0xff;
			v->si8_4[0][1] = (cpu + i + 1) & 0xff;
			v->si8_4[1][0] = (cpu + i + 2) & 0xff;
			v->si8_4[1][1] = (cpu + i + 3) & 0xff;
			v = (व्योम *)v + rounded_value_size;
		पूर्ण
	पूर्ण

#अगर_घोषित __SIZखातापूर्ण_INT128__
	अगर (mapv_kind == PPRINT_MAPV_KIND_INT128) अणु
		काष्ठा pprपूर्णांक_mapv_पूर्णांक128 *v = mapv;

		क्रम (cpu = 0; cpu < num_cpus; cpu++) अणु
			v->si128a = i;
			v->si128b = -i;
			v->bits3 = i & 0x07;
			v->bits80 = (((अचिन्हित __पूर्णांक128)1) << 64) + i;
			v->ui128 = (((अचिन्हित __पूर्णांक128)2) << 64) + i;
			v = (व्योम *)v + rounded_value_size;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

sमाप_प्रकार get_pprपूर्णांक_expected_line(क्रमागत pprपूर्णांक_mapv_kind_t mapv_kind,
				 अक्षर *expected_line, sमाप_प्रकार line_size,
				 bool percpu_map, अचिन्हित पूर्णांक next_key,
				 पूर्णांक cpu, व्योम *mapv)
अणु
	sमाप_प्रकार nexpected_line = -1;

	अगर (mapv_kind == PPRINT_MAPV_KIND_BASIC) अणु
		काष्ठा pprपूर्णांक_mapv *v = mapv;

		nexpected_line = snम_लिखो(expected_line, line_size,
					  "%s%u: {%u,0,%d,0x%x,0x%x,0x%x,"
					  "{%llu|[%u,%u,%u,%u,%u,%u,%u,%u]},%s,"
					  "%u,0x%x,[[%d,%d],[%d,%d]]}\n",
					  percpu_map ? "\tcpu" : "",
					  percpu_map ? cpu : next_key,
					  v->ui32, v->si32,
					  v->unused_bits2a,
					  v->bits28,
					  v->unused_bits2b,
					  (__u64)v->ui64,
					  v->ui8a[0], v->ui8a[1],
					  v->ui8a[2], v->ui8a[3],
					  v->ui8a[4], v->ui8a[5],
					  v->ui8a[6], v->ui8a[7],
					  pprपूर्णांक_क्रमागत_str[v->aक्रमागत],
					  v->ui32b,
					  v->bits2c,
					  v->si8_4[0][0], v->si8_4[0][1],
					  v->si8_4[1][0], v->si8_4[1][1]);
	पूर्ण

#अगर_घोषित __SIZखातापूर्ण_INT128__
	अगर (mapv_kind == PPRINT_MAPV_KIND_INT128) अणु
		काष्ठा pprपूर्णांक_mapv_पूर्णांक128 *v = mapv;

		nexpected_line = snम_लिखो(expected_line, line_size,
					  "%s%u: {0x%lx,0x%lx,0x%lx,"
					  "0x%lx%016lx,0x%lx%016lx}\n",
					  percpu_map ? "\tcpu" : "",
					  percpu_map ? cpu : next_key,
					  (uपूर्णांक64_t)v->si128a,
					  (uपूर्णांक64_t)v->si128b,
					  (uपूर्णांक64_t)v->bits3,
					  (uपूर्णांक64_t)(v->bits80 >> 64),
					  (uपूर्णांक64_t)v->bits80,
					  (uपूर्णांक64_t)(v->ui128 >> 64),
					  (uपूर्णांक64_t)v->ui128);
	पूर्ण
#पूर्ण_अगर

	वापस nexpected_line;
पूर्ण

अटल पूर्णांक check_line(स्थिर अक्षर *expected_line, पूर्णांक nexpected_line,
		      पूर्णांक expected_line_len, स्थिर अक्षर *line)
अणु
	अगर (CHECK(nexpected_line == expected_line_len,
		  "expected_line is too long"))
		वापस -1;

	अगर (म_भेद(expected_line, line)) अणु
		ख_लिखो(मानक_त्रुटि, "unexpected pprint output\n");
		ख_लिखो(मानक_त्रुटि, "expected: %s", expected_line);
		ख_लिखो(मानक_त्रुटि, "    read: %s", line);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण


अटल व्योम करो_test_pprपूर्णांक(पूर्णांक test_num)
अणु
	स्थिर काष्ठा btf_raw_test *test = &pprपूर्णांक_test_ढाँचा[test_num];
	क्रमागत pprपूर्णांक_mapv_kind_t mapv_kind = test->mapv_kind;
	काष्ठा bpf_create_map_attr create_attr = अणुपूर्ण;
	bool ordered_map, lossless_map, percpu_map;
	पूर्णांक err, ret, num_cpus, rounded_value_size;
	अचिन्हित पूर्णांक key, nr_पढ़ो_elems;
	पूर्णांक map_fd = -1, btf_fd = -1;
	अचिन्हित पूर्णांक raw_btf_size;
	अक्षर expected_line[255];
	खाता *pin_file = शून्य;
	अक्षर pin_path[255];
	माप_प्रकार line_len = 0;
	अक्षर *line = शून्य;
	व्योम *mapv = शून्य;
	uपूर्णांक8_t *raw_btf;
	sमाप_प्रकार nपढ़ो;

	अगर (!test__start_subtest(test->descr))
		वापस;

	raw_btf = btf_raw_create(&hdr_पंचांगpl, test->raw_types,
				 test->str_sec, test->str_sec_size,
				 &raw_btf_size, शून्य);

	अगर (!raw_btf)
		वापस;

	*btf_log_buf = '\0';
	btf_fd = bpf_load_btf(raw_btf, raw_btf_size,
			      btf_log_buf, BTF_LOG_BUF_SIZE,
			      always_log);
	मुक्त(raw_btf);

	अगर (CHECK(btf_fd == -1, "errno:%d", त्रुटि_सं)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	create_attr.name = test->map_name;
	create_attr.map_type = test->map_type;
	create_attr.key_size = test->key_size;
	create_attr.value_size = test->value_size;
	create_attr.max_entries = test->max_entries;
	create_attr.btf_fd = btf_fd;
	create_attr.btf_key_type_id = test->key_type_id;
	create_attr.btf_value_type_id = test->value_type_id;

	map_fd = bpf_create_map_xattr(&create_attr);
	अगर (CHECK(map_fd == -1, "errno:%d", त्रुटि_सं)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	ret = snम_लिखो(pin_path, माप(pin_path), "%s/%s",
		       "/sys/fs/bpf", test->map_name);

	अगर (CHECK(ret == माप(pin_path), "pin_path %s/%s is too long",
		  "/sys/fs/bpf", test->map_name)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	err = bpf_obj_pin(map_fd, pin_path);
	अगर (CHECK(err, "bpf_obj_pin(%s): errno:%d.", pin_path, त्रुटि_सं))
		जाओ करोne;

	percpu_map = test->percpu_map;
	num_cpus = percpu_map ? bpf_num_possible_cpus() : 1;
	rounded_value_size = round_up(get_pprपूर्णांक_mapv_size(mapv_kind), 8);
	mapv = सुस्मृति(num_cpus, rounded_value_size);
	अगर (CHECK(!mapv, "mapv allocation failure")) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	क्रम (key = 0; key < test->max_entries; key++) अणु
		set_pprपूर्णांक_mapv(mapv_kind, mapv, key, num_cpus, rounded_value_size);
		bpf_map_update_elem(map_fd, &key, mapv, 0);
	पूर्ण

	pin_file = ख_खोलो(pin_path, "r");
	अगर (CHECK(!pin_file, "fopen(%s): errno:%d", pin_path, त्रुटि_सं)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	/* Skip lines start with '#' */
	जबतक ((nपढ़ो = getline(&line, &line_len, pin_file)) > 0 &&
	       *line == '#')
		;

	अगर (CHECK(nपढ़ो <= 0, "Unexpected EOF")) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	nr_पढ़ो_elems = 0;
	ordered_map = test->ordered_map;
	lossless_map = test->lossless_map;
	करो अणु
		sमाप_प्रकार nexpected_line;
		अचिन्हित पूर्णांक next_key;
		व्योम *cmapv;
		पूर्णांक cpu;

		next_key = ordered_map ? nr_पढ़ो_elems : म_से_प(line);
		set_pprपूर्णांक_mapv(mapv_kind, mapv, next_key, num_cpus, rounded_value_size);
		cmapv = mapv;

		क्रम (cpu = 0; cpu < num_cpus; cpu++) अणु
			अगर (percpu_map) अणु
				/* क्रम percpu map, the क्रमmat looks like:
				 * <key>: अणु
				 *	cpu0: <value_on_cpu0>
				 *	cpu1: <value_on_cpu1>
				 *	...
				 *	cpun: <value_on_cpun>
				 * पूर्ण
				 *
				 * let us verअगरy the line containing the key here.
				 */
				अगर (cpu == 0) अणु
					nexpected_line = snम_लिखो(expected_line,
								  माप(expected_line),
								  "%u: {\n",
								  next_key);

					err = check_line(expected_line, nexpected_line,
							 माप(expected_line), line);
					अगर (err == -1)
						जाओ करोne;
				पूर्ण

				/* पढ़ो value@cpu */
				nपढ़ो = getline(&line, &line_len, pin_file);
				अगर (nपढ़ो < 0)
					अवरोध;
			पूर्ण

			nexpected_line = get_pprपूर्णांक_expected_line(mapv_kind, expected_line,
								  माप(expected_line),
								  percpu_map, next_key,
								  cpu, cmapv);
			err = check_line(expected_line, nexpected_line,
					 माप(expected_line), line);
			अगर (err == -1)
				जाओ करोne;

			cmapv = cmapv + rounded_value_size;
		पूर्ण

		अगर (percpu_map) अणु
			/* skip the last bracket क्रम the percpu map */
			nपढ़ो = getline(&line, &line_len, pin_file);
			अगर (nपढ़ो < 0)
				अवरोध;
		पूर्ण

		nपढ़ो = getline(&line, &line_len, pin_file);
	पूर्ण जबतक (++nr_पढ़ो_elems < test->max_entries && nपढ़ो > 0);

	अगर (lossless_map &&
	    CHECK(nr_पढ़ो_elems < test->max_entries,
		  "Unexpected EOF. nr_read_elems:%u test->max_entries:%u",
		  nr_पढ़ो_elems, test->max_entries)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	अगर (CHECK(nपढ़ो > 0, "Unexpected extra pprint output: %s", line)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	err = 0;

करोne:
	अगर (mapv)
		मुक्त(mapv);
	अगर (!err)
		ख_लिखो(मानक_त्रुटि, "OK");
	अगर (*btf_log_buf && (err || always_log))
		ख_लिखो(मानक_त्रुटि, "\n%s", btf_log_buf);
	अगर (btf_fd != -1)
		बंद(btf_fd);
	अगर (map_fd != -1)
		बंद(map_fd);
	अगर (pin_file)
		ख_बंद(pin_file);
	unlink(pin_path);
	मुक्त(line);
पूर्ण

अटल व्योम test_pprपूर्णांक(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	/* test various maps with the first test ढाँचा */
	क्रम (i = 0; i < ARRAY_SIZE(pprपूर्णांक_tests_meta); i++) अणु
		pprपूर्णांक_test_ढाँचा[0].descr = pprपूर्णांक_tests_meta[i].descr;
		pprपूर्णांक_test_ढाँचा[0].map_type = pprपूर्णांक_tests_meta[i].map_type;
		pprपूर्णांक_test_ढाँचा[0].map_name = pprपूर्णांक_tests_meta[i].map_name;
		pprपूर्णांक_test_ढाँचा[0].ordered_map = pprपूर्णांक_tests_meta[i].ordered_map;
		pprपूर्णांक_test_ढाँचा[0].lossless_map = pprपूर्णांक_tests_meta[i].lossless_map;
		pprपूर्णांक_test_ढाँचा[0].percpu_map = pprपूर्णांक_tests_meta[i].percpu_map;

		करो_test_pprपूर्णांक(0);
	पूर्ण

	/* test rest test ढाँचाs with the first map */
	क्रम (i = 1; i < ARRAY_SIZE(pprपूर्णांक_test_ढाँचा); i++) अणु
		pprपूर्णांक_test_ढाँचा[i].descr = pprपूर्णांक_tests_meta[0].descr;
		pprपूर्णांक_test_ढाँचा[i].map_type = pprपूर्णांक_tests_meta[0].map_type;
		pprपूर्णांक_test_ढाँचा[i].map_name = pprपूर्णांक_tests_meta[0].map_name;
		pprपूर्णांक_test_ढाँचा[i].ordered_map = pprपूर्णांक_tests_meta[0].ordered_map;
		pprपूर्णांक_test_ढाँचा[i].lossless_map = pprपूर्णांक_tests_meta[0].lossless_map;
		pprपूर्णांक_test_ढाँचा[i].percpu_map = pprपूर्णांक_tests_meta[0].percpu_map;
		करो_test_pprपूर्णांक(i);
	पूर्ण
पूर्ण

#घोषणा BPF_LINE_INFO_ENC(insn_off, file_off, line_off, line_num, line_col) \
	(insn_off), (file_off), (line_off), ((line_num) << 10 | ((line_col) & 0x3ff))

अटल काष्ठा prog_info_raw_test अणु
	स्थिर अक्षर *descr;
	स्थिर अक्षर *str_sec;
	स्थिर अक्षर *err_str;
	__u32 raw_types[MAX_NR_RAW_U32];
	__u32 str_sec_size;
	काष्ठा bpf_insn insns[MAX_INSNS];
	__u32 prog_type;
	__u32 func_info[MAX_SUBPROGS][2];
	__u32 func_info_rec_size;
	__u32 func_info_cnt;
	__u32 line_info[MAX_NR_RAW_U32];
	__u32 line_info_rec_size;
	__u32 nr_jited_ksyms;
	bool expected_prog_load_failure;
	__u32 dead_code_cnt;
	__u32 dead_code_mask;
	__u32 dead_func_cnt;
	__u32 dead_func_mask;
पूर्ण info_raw_tests[] = अणु
अणु
	.descr = "func_type (main func + one sub)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_TYPE_INT_ENC(NAME_TBD, 0, 0, 32, 4),	/* [2] */
		BTF_FUNC_PROTO_ENC(1, 2),			/* [3] */
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 1),
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 2),
		BTF_FUNC_PROTO_ENC(1, 2),			/* [4] */
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 2),
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 1),
		BTF_FUNC_ENC(NAME_TBD, 3),			/* [5] */
		BTF_FUNC_ENC(NAME_TBD, 4),			/* [6] */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0int\0unsigned int\0a\0b\0c\0d\0funcA\0funcB",
	.str_sec_size = माप("\0int\0unsigned int\0a\0b\0c\0d\0funcA\0funcB"),
	.insns = अणु
		BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 2),
		BPF_MOV64_IMM(BPF_REG_0, 1),
		BPF_EXIT_INSN(),
		BPF_MOV64_IMM(BPF_REG_0, 2),
		BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.func_info = अणु अणु0, 5पूर्ण, अणु3, 6पूर्ण पूर्ण,
	.func_info_rec_size = 8,
	.func_info_cnt = 2,
	.line_info = अणु BTF_END_RAW पूर्ण,
पूर्ण,

अणु
	.descr = "func_type (Incorrect func_info_rec_size)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_TYPE_INT_ENC(NAME_TBD, 0, 0, 32, 4),	/* [2] */
		BTF_FUNC_PROTO_ENC(1, 2),			/* [3] */
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 1),
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 2),
		BTF_FUNC_PROTO_ENC(1, 2),			/* [4] */
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 2),
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 1),
		BTF_FUNC_ENC(NAME_TBD, 3),			/* [5] */
		BTF_FUNC_ENC(NAME_TBD, 4),			/* [6] */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0int\0unsigned int\0a\0b\0c\0d\0funcA\0funcB",
	.str_sec_size = माप("\0int\0unsigned int\0a\0b\0c\0d\0funcA\0funcB"),
	.insns = अणु
		BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 2),
		BPF_MOV64_IMM(BPF_REG_0, 1),
		BPF_EXIT_INSN(),
		BPF_MOV64_IMM(BPF_REG_0, 2),
		BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.func_info = अणु अणु0, 5पूर्ण, अणु3, 6पूर्ण पूर्ण,
	.func_info_rec_size = 4,
	.func_info_cnt = 2,
	.line_info = अणु BTF_END_RAW पूर्ण,
	.expected_prog_load_failure = true,
पूर्ण,

अणु
	.descr = "func_type (Incorrect func_info_cnt)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_TYPE_INT_ENC(NAME_TBD, 0, 0, 32, 4),	/* [2] */
		BTF_FUNC_PROTO_ENC(1, 2),			/* [3] */
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 1),
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 2),
		BTF_FUNC_PROTO_ENC(1, 2),			/* [4] */
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 2),
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 1),
		BTF_FUNC_ENC(NAME_TBD, 3),			/* [5] */
		BTF_FUNC_ENC(NAME_TBD, 4),			/* [6] */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0int\0unsigned int\0a\0b\0c\0d\0funcA\0funcB",
	.str_sec_size = माप("\0int\0unsigned int\0a\0b\0c\0d\0funcA\0funcB"),
	.insns = अणु
		BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 2),
		BPF_MOV64_IMM(BPF_REG_0, 1),
		BPF_EXIT_INSN(),
		BPF_MOV64_IMM(BPF_REG_0, 2),
		BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.func_info = अणु अणु0, 5पूर्ण, अणु3, 6पूर्ण पूर्ण,
	.func_info_rec_size = 8,
	.func_info_cnt = 1,
	.line_info = अणु BTF_END_RAW पूर्ण,
	.expected_prog_load_failure = true,
पूर्ण,

अणु
	.descr = "func_type (Incorrect bpf_func_info.insn_off)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_TYPE_INT_ENC(NAME_TBD, 0, 0, 32, 4),	/* [2] */
		BTF_FUNC_PROTO_ENC(1, 2),			/* [3] */
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 1),
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 2),
		BTF_FUNC_PROTO_ENC(1, 2),			/* [4] */
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 2),
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 1),
		BTF_FUNC_ENC(NAME_TBD, 3),			/* [5] */
		BTF_FUNC_ENC(NAME_TBD, 4),			/* [6] */
		BTF_END_RAW,
	पूर्ण,
	.str_sec = "\0int\0unsigned int\0a\0b\0c\0d\0funcA\0funcB",
	.str_sec_size = माप("\0int\0unsigned int\0a\0b\0c\0d\0funcA\0funcB"),
	.insns = अणु
		BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 2),
		BPF_MOV64_IMM(BPF_REG_0, 1),
		BPF_EXIT_INSN(),
		BPF_MOV64_IMM(BPF_REG_0, 2),
		BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.func_info = अणु अणु0, 5पूर्ण, अणु2, 6पूर्ण पूर्ण,
	.func_info_rec_size = 8,
	.func_info_cnt = 2,
	.line_info = अणु BTF_END_RAW पूर्ण,
	.expected_prog_load_failure = true,
पूर्ण,

अणु
	.descr = "line_info (No subprog)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0int\0int a=1;\0int b=2;\0return a + b;\0return a + b;"),
	.insns = अणु
		BPF_MOV64_IMM(BPF_REG_0, 1),
		BPF_MOV64_IMM(BPF_REG_1, 2),
		BPF_ALU64_REG(BPF_ADD, BPF_REG_0, BPF_REG_1),
		BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.func_info_cnt = 0,
	.line_info = अणु
		BPF_LINE_INFO_ENC(0, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(1, 0, NAME_TBD, 2, 9),
		BPF_LINE_INFO_ENC(2, 0, NAME_TBD, 3, 8),
		BPF_LINE_INFO_ENC(3, 0, NAME_TBD, 4, 7),
		BTF_END_RAW,
	पूर्ण,
	.line_info_rec_size = माप(काष्ठा bpf_line_info),
	.nr_jited_ksyms = 1,
पूर्ण,

अणु
	.descr = "line_info (No subprog. insn_off >= prog->len)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0int\0int a=1;\0int b=2;\0return a + b;\0return a + b;"),
	.insns = अणु
		BPF_MOV64_IMM(BPF_REG_0, 1),
		BPF_MOV64_IMM(BPF_REG_1, 2),
		BPF_ALU64_REG(BPF_ADD, BPF_REG_0, BPF_REG_1),
		BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.func_info_cnt = 0,
	.line_info = अणु
		BPF_LINE_INFO_ENC(0, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(1, 0, NAME_TBD, 2, 9),
		BPF_LINE_INFO_ENC(2, 0, NAME_TBD, 3, 8),
		BPF_LINE_INFO_ENC(3, 0, NAME_TBD, 4, 7),
		BPF_LINE_INFO_ENC(4, 0, 0, 5, 6),
		BTF_END_RAW,
	पूर्ण,
	.line_info_rec_size = माप(काष्ठा bpf_line_info),
	.nr_jited_ksyms = 1,
	.err_str = "line_info[4].insn_off",
	.expected_prog_load_failure = true,
पूर्ण,

अणु
	.descr = "line_info (Zero bpf insn code)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_TYPE_INT_ENC(NAME_TBD, 0, 0, 64, 8),	/* [2] */
		BTF_TYPEDEF_ENC(NAME_TBD, 2),			/* [3] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0int\0unsigned long\0u64\0u64 a=1;\0return a;"),
	.insns = अणु
		BPF_LD_IMM64(BPF_REG_0, 1),
		BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.func_info_cnt = 0,
	.line_info = अणु
		BPF_LINE_INFO_ENC(0, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(1, 0, 0, 2, 9),
		BPF_LINE_INFO_ENC(2, 0, NAME_TBD, 3, 8),
		BTF_END_RAW,
	पूर्ण,
	.line_info_rec_size = माप(काष्ठा bpf_line_info),
	.nr_jited_ksyms = 1,
	.err_str = "Invalid insn code at line_info[1]",
	.expected_prog_load_failure = true,
पूर्ण,

अणु
	.descr = "line_info (No subprog. zero tailing line_info",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0int\0int a=1;\0int b=2;\0return a + b;\0return a + b;"),
	.insns = अणु
		BPF_MOV64_IMM(BPF_REG_0, 1),
		BPF_MOV64_IMM(BPF_REG_1, 2),
		BPF_ALU64_REG(BPF_ADD, BPF_REG_0, BPF_REG_1),
		BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.func_info_cnt = 0,
	.line_info = अणु
		BPF_LINE_INFO_ENC(0, 0, NAME_TBD, 1, 10), 0,
		BPF_LINE_INFO_ENC(1, 0, NAME_TBD, 2, 9), 0,
		BPF_LINE_INFO_ENC(2, 0, NAME_TBD, 3, 8), 0,
		BPF_LINE_INFO_ENC(3, 0, NAME_TBD, 4, 7), 0,
		BTF_END_RAW,
	पूर्ण,
	.line_info_rec_size = माप(काष्ठा bpf_line_info) + माप(__u32),
	.nr_jited_ksyms = 1,
पूर्ण,

अणु
	.descr = "line_info (No subprog. nonzero tailing line_info)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0int\0int a=1;\0int b=2;\0return a + b;\0return a + b;"),
	.insns = अणु
		BPF_MOV64_IMM(BPF_REG_0, 1),
		BPF_MOV64_IMM(BPF_REG_1, 2),
		BPF_ALU64_REG(BPF_ADD, BPF_REG_0, BPF_REG_1),
		BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.func_info_cnt = 0,
	.line_info = अणु
		BPF_LINE_INFO_ENC(0, 0, NAME_TBD, 1, 10), 0,
		BPF_LINE_INFO_ENC(1, 0, NAME_TBD, 2, 9), 0,
		BPF_LINE_INFO_ENC(2, 0, NAME_TBD, 3, 8), 0,
		BPF_LINE_INFO_ENC(3, 0, NAME_TBD, 4, 7), 1,
		BTF_END_RAW,
	पूर्ण,
	.line_info_rec_size = माप(काष्ठा bpf_line_info) + माप(__u32),
	.nr_jited_ksyms = 1,
	.err_str = "nonzero tailing record in line_info",
	.expected_prog_load_failure = true,
पूर्ण,

अणु
	.descr = "line_info (subprog)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0int\0int a=1+1;\0return func(a);\0b+=1;\0return b;"),
	.insns = अणु
		BPF_MOV64_IMM(BPF_REG_2, 1),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, 1),
		BPF_MOV64_REG(BPF_REG_1, BPF_REG_2),
		BPF_CALL_REL(1),
		BPF_EXIT_INSN(),
		BPF_MOV64_REG(BPF_REG_0, BPF_REG_1),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 1),
		BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.func_info_cnt = 0,
	.line_info = अणु
		BPF_LINE_INFO_ENC(0, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(2, 0, NAME_TBD, 2, 9),
		BPF_LINE_INFO_ENC(5, 0, NAME_TBD, 3, 8),
		BPF_LINE_INFO_ENC(7, 0, NAME_TBD, 4, 7),
		BTF_END_RAW,
	पूर्ण,
	.line_info_rec_size = माप(काष्ठा bpf_line_info),
	.nr_jited_ksyms = 2,
पूर्ण,

अणु
	.descr = "line_info (subprog + func_info)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_FUNC_PROTO_ENC(1, 1),			/* [2] */
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 1),
		BTF_FUNC_ENC(NAME_TBD, 2),			/* [3] */
		BTF_FUNC_ENC(NAME_TBD, 2),			/* [4] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0int\0x\0sub\0main\0int a=1+1;\0return func(a);\0b+=1;\0return b;"),
	.insns = अणु
		BPF_MOV64_IMM(BPF_REG_2, 1),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, 1),
		BPF_MOV64_REG(BPF_REG_1, BPF_REG_2),
		BPF_CALL_REL(1),
		BPF_EXIT_INSN(),
		BPF_MOV64_REG(BPF_REG_0, BPF_REG_1),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 1),
		BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.func_info_cnt = 2,
	.func_info_rec_size = 8,
	.func_info = अणु अणु0, 4पूर्ण, अणु5, 3पूर्ण पूर्ण,
	.line_info = अणु
		BPF_LINE_INFO_ENC(0, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(2, 0, NAME_TBD, 2, 9),
		BPF_LINE_INFO_ENC(5, 0, NAME_TBD, 3, 8),
		BPF_LINE_INFO_ENC(7, 0, NAME_TBD, 4, 7),
		BTF_END_RAW,
	पूर्ण,
	.line_info_rec_size = माप(काष्ठा bpf_line_info),
	.nr_jited_ksyms = 2,
पूर्ण,

अणु
	.descr = "line_info (subprog. missing 1st func line info)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0int\0int a=1+1;\0return func(a);\0b+=1;\0return b;"),
	.insns = अणु
		BPF_MOV64_IMM(BPF_REG_2, 1),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, 1),
		BPF_MOV64_REG(BPF_REG_1, BPF_REG_2),
		BPF_CALL_REL(1),
		BPF_EXIT_INSN(),
		BPF_MOV64_REG(BPF_REG_0, BPF_REG_1),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 1),
		BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.func_info_cnt = 0,
	.line_info = अणु
		BPF_LINE_INFO_ENC(1, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(2, 0, NAME_TBD, 2, 9),
		BPF_LINE_INFO_ENC(5, 0, NAME_TBD, 3, 8),
		BPF_LINE_INFO_ENC(7, 0, NAME_TBD, 4, 7),
		BTF_END_RAW,
	पूर्ण,
	.line_info_rec_size = माप(काष्ठा bpf_line_info),
	.nr_jited_ksyms = 2,
	.err_str = "missing bpf_line_info for func#0",
	.expected_prog_load_failure = true,
पूर्ण,

अणु
	.descr = "line_info (subprog. missing 2nd func line info)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0int\0int a=1+1;\0return func(a);\0b+=1;\0return b;"),
	.insns = अणु
		BPF_MOV64_IMM(BPF_REG_2, 1),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, 1),
		BPF_MOV64_REG(BPF_REG_1, BPF_REG_2),
		BPF_CALL_REL(1),
		BPF_EXIT_INSN(),
		BPF_MOV64_REG(BPF_REG_0, BPF_REG_1),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 1),
		BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.func_info_cnt = 0,
	.line_info = अणु
		BPF_LINE_INFO_ENC(0, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(2, 0, NAME_TBD, 2, 9),
		BPF_LINE_INFO_ENC(6, 0, NAME_TBD, 3, 8),
		BPF_LINE_INFO_ENC(7, 0, NAME_TBD, 4, 7),
		BTF_END_RAW,
	पूर्ण,
	.line_info_rec_size = माप(काष्ठा bpf_line_info),
	.nr_jited_ksyms = 2,
	.err_str = "missing bpf_line_info for func#1",
	.expected_prog_load_failure = true,
पूर्ण,

अणु
	.descr = "line_info (subprog. unordered insn offset)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0int\0int a=1+1;\0return func(a);\0b+=1;\0return b;"),
	.insns = अणु
		BPF_MOV64_IMM(BPF_REG_2, 1),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, 1),
		BPF_MOV64_REG(BPF_REG_1, BPF_REG_2),
		BPF_CALL_REL(1),
		BPF_EXIT_INSN(),
		BPF_MOV64_REG(BPF_REG_0, BPF_REG_1),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 1),
		BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.func_info_cnt = 0,
	.line_info = अणु
		BPF_LINE_INFO_ENC(0, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(5, 0, NAME_TBD, 2, 9),
		BPF_LINE_INFO_ENC(2, 0, NAME_TBD, 3, 8),
		BPF_LINE_INFO_ENC(7, 0, NAME_TBD, 4, 7),
		BTF_END_RAW,
	पूर्ण,
	.line_info_rec_size = माप(काष्ठा bpf_line_info),
	.nr_jited_ksyms = 2,
	.err_str = "Invalid line_info[2].insn_off",
	.expected_prog_load_failure = true,
पूर्ण,

अणु
	.descr = "line_info (dead start)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0int\0/* dead jmp */\0int a=1;\0int b=2;\0return a + b;\0return a + b;"),
	.insns = अणु
		BPF_JMP_IMM(BPF_JA, 0, 0, 0),
		BPF_MOV64_IMM(BPF_REG_0, 1),
		BPF_MOV64_IMM(BPF_REG_1, 2),
		BPF_ALU64_REG(BPF_ADD, BPF_REG_0, BPF_REG_1),
		BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.func_info_cnt = 0,
	.line_info = अणु
		BPF_LINE_INFO_ENC(0, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(1, 0, NAME_TBD, 2, 9),
		BPF_LINE_INFO_ENC(2, 0, NAME_TBD, 3, 8),
		BPF_LINE_INFO_ENC(3, 0, NAME_TBD, 4, 7),
		BPF_LINE_INFO_ENC(4, 0, NAME_TBD, 5, 6),
		BTF_END_RAW,
	पूर्ण,
	.line_info_rec_size = माप(काष्ठा bpf_line_info),
	.nr_jited_ksyms = 1,
	.dead_code_cnt = 1,
	.dead_code_mask = 0x01,
पूर्ण,

अणु
	.descr = "line_info (dead end)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0int\0int a=1;\0int b=2;\0return a + b;\0/* dead jmp */\0return a + b;\0/* dead exit */"),
	.insns = अणु
		BPF_MOV64_IMM(BPF_REG_0, 1),
		BPF_MOV64_IMM(BPF_REG_1, 2),
		BPF_ALU64_REG(BPF_ADD, BPF_REG_0, BPF_REG_1),
		BPF_JMP_IMM(BPF_JGE, BPF_REG_0, 10, 1),
		BPF_EXIT_INSN(),
		BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.func_info_cnt = 0,
	.line_info = अणु
		BPF_LINE_INFO_ENC(0, 0, NAME_TBD, 1, 12),
		BPF_LINE_INFO_ENC(1, 0, NAME_TBD, 2, 11),
		BPF_LINE_INFO_ENC(2, 0, NAME_TBD, 3, 10),
		BPF_LINE_INFO_ENC(3, 0, NAME_TBD, 4, 9),
		BPF_LINE_INFO_ENC(4, 0, NAME_TBD, 5, 8),
		BPF_LINE_INFO_ENC(5, 0, NAME_TBD, 6, 7),
		BTF_END_RAW,
	पूर्ण,
	.line_info_rec_size = माप(काष्ठा bpf_line_info),
	.nr_jited_ksyms = 1,
	.dead_code_cnt = 2,
	.dead_code_mask = 0x28,
पूर्ण,

अणु
	.descr = "line_info (dead code + subprog + func_info)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_FUNC_PROTO_ENC(1, 1),			/* [2] */
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 1),
		BTF_FUNC_ENC(NAME_TBD, 2),			/* [3] */
		BTF_FUNC_ENC(NAME_TBD, 2),			/* [4] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0int\0x\0sub\0main\0int a=1+1;\0/* dead jmp */"
		    "\0/* dead */\0/* dead */\0/* dead */\0/* dead */"
		    "\0/* dead */\0/* dead */\0/* dead */\0/* dead */"
		    "\0return func(a);\0b+=1;\0return b;"),
	.insns = अणु
		BPF_MOV64_IMM(BPF_REG_2, 1),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, 1),
		BPF_MOV64_REG(BPF_REG_1, BPF_REG_2),
		BPF_JMP_IMM(BPF_JGE, BPF_REG_2, 0, 8),
		BPF_MOV64_IMM(BPF_REG_2, 1),
		BPF_MOV64_IMM(BPF_REG_2, 1),
		BPF_MOV64_IMM(BPF_REG_2, 1),
		BPF_MOV64_IMM(BPF_REG_2, 1),
		BPF_MOV64_IMM(BPF_REG_2, 1),
		BPF_MOV64_IMM(BPF_REG_2, 1),
		BPF_MOV64_IMM(BPF_REG_2, 1),
		BPF_MOV64_IMM(BPF_REG_2, 1),
		BPF_CALL_REL(1),
		BPF_EXIT_INSN(),
		BPF_MOV64_REG(BPF_REG_0, BPF_REG_1),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 1),
		BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.func_info_cnt = 2,
	.func_info_rec_size = 8,
	.func_info = अणु अणु0, 4पूर्ण, अणु14, 3पूर्ण पूर्ण,
	.line_info = अणु
		BPF_LINE_INFO_ENC(0, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(3, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(4, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(5, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(6, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(7, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(8, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(9, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(10, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(11, 0, NAME_TBD, 2, 9),
		BPF_LINE_INFO_ENC(12, 0, NAME_TBD, 2, 9),
		BPF_LINE_INFO_ENC(14, 0, NAME_TBD, 3, 8),
		BPF_LINE_INFO_ENC(16, 0, NAME_TBD, 4, 7),
		BTF_END_RAW,
	पूर्ण,
	.line_info_rec_size = माप(काष्ठा bpf_line_info),
	.nr_jited_ksyms = 2,
	.dead_code_cnt = 9,
	.dead_code_mask = 0x3fe,
पूर्ण,

अणु
	.descr = "line_info (dead subprog)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_FUNC_PROTO_ENC(1, 1),			/* [2] */
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 1),
		BTF_FUNC_ENC(NAME_TBD, 2),			/* [3] */
		BTF_FUNC_ENC(NAME_TBD, 2),			/* [4] */
		BTF_FUNC_ENC(NAME_TBD, 2),			/* [5] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0int\0x\0dead\0main\0func\0int a=1+1;\0/* live call */"
		    "\0return 0;\0return 0;\0/* dead */\0/* dead */"
		    "\0/* dead */\0return bla + 1;\0return bla + 1;"
		    "\0return bla + 1;\0return func(a);\0b+=1;\0return b;"),
	.insns = अणु
		BPF_MOV64_IMM(BPF_REG_2, 1),
		BPF_JMP_IMM(BPF_JGE, BPF_REG_2, 0, 1),
		BPF_CALL_REL(3),
		BPF_CALL_REL(5),
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_EXIT_INSN(),
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_CALL_REL(1),
		BPF_EXIT_INSN(),
		BPF_MOV64_REG(BPF_REG_0, 2),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 1),
		BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.func_info_cnt = 3,
	.func_info_rec_size = 8,
		.func_info = अणु अणु0, 4पूर्ण, अणु6, 3पूर्ण, अणु9, 5पूर्ण पूर्ण,
	.line_info = अणु
		BPF_LINE_INFO_ENC(0, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(3, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(4, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(5, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(6, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(7, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(8, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(9, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(10, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(11, 0, NAME_TBD, 2, 9),
		BTF_END_RAW,
	पूर्ण,
	.line_info_rec_size = माप(काष्ठा bpf_line_info),
	.nr_jited_ksyms = 2,
	.dead_code_cnt = 3,
	.dead_code_mask = 0x70,
	.dead_func_cnt = 1,
	.dead_func_mask = 0x2,
पूर्ण,

अणु
	.descr = "line_info (dead last subprog)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_FUNC_PROTO_ENC(1, 1),			/* [2] */
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 1),
		BTF_FUNC_ENC(NAME_TBD, 2),			/* [3] */
		BTF_FUNC_ENC(NAME_TBD, 2),			/* [5] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0int\0x\0dead\0main\0int a=1+1;\0/* live call */"
		    "\0return 0;\0/* dead */\0/* dead */"),
	.insns = अणु
		BPF_MOV64_IMM(BPF_REG_2, 1),
		BPF_JMP_IMM(BPF_JGE, BPF_REG_2, 0, 1),
		BPF_CALL_REL(2),
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_EXIT_INSN(),
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.func_info_cnt = 2,
	.func_info_rec_size = 8,
		.func_info = अणु अणु0, 4पूर्ण, अणु5, 3पूर्ण पूर्ण,
	.line_info = अणु
		BPF_LINE_INFO_ENC(0, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(3, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(4, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(5, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(6, 0, NAME_TBD, 1, 10),
		BTF_END_RAW,
	पूर्ण,
	.line_info_rec_size = माप(काष्ठा bpf_line_info),
	.nr_jited_ksyms = 1,
	.dead_code_cnt = 2,
	.dead_code_mask = 0x18,
	.dead_func_cnt = 1,
	.dead_func_mask = 0x2,
पूर्ण,

अणु
	.descr = "line_info (dead subprog + dead start)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_FUNC_PROTO_ENC(1, 1),			/* [2] */
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 1),
		BTF_FUNC_ENC(NAME_TBD, 2),			/* [3] */
		BTF_FUNC_ENC(NAME_TBD, 2),			/* [4] */
		BTF_FUNC_ENC(NAME_TBD, 2),			/* [5] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0int\0x\0dead\0main\0func\0int a=1+1;\0/* dead */"
		    "\0return 0;\0return 0;\0return 0;"
		    "\0/* dead */\0/* dead */\0/* dead */\0/* dead */"
		    "\0return b + 1;\0return b + 1;\0return b + 1;"),
	.insns = अणु
		BPF_JMP_IMM(BPF_JA, 0, 0, 0),
		BPF_MOV64_IMM(BPF_REG_2, 1),
		BPF_JMP_IMM(BPF_JGE, BPF_REG_2, 0, 1),
		BPF_CALL_REL(3),
		BPF_CALL_REL(5),
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_EXIT_INSN(),
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_CALL_REL(1),
		BPF_EXIT_INSN(),
		BPF_JMP_IMM(BPF_JA, 0, 0, 0),
		BPF_MOV64_REG(BPF_REG_0, 2),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 1),
		BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.func_info_cnt = 3,
	.func_info_rec_size = 8,
		.func_info = अणु अणु0, 4पूर्ण, अणु7, 3पूर्ण, अणु10, 5पूर्ण पूर्ण,
	.line_info = अणु
		BPF_LINE_INFO_ENC(0, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(3, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(4, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(5, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(6, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(7, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(8, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(9, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(10, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(11, 0, NAME_TBD, 2, 9),
		BPF_LINE_INFO_ENC(12, 0, NAME_TBD, 2, 9),
		BPF_LINE_INFO_ENC(13, 0, NAME_TBD, 2, 9),
		BTF_END_RAW,
	पूर्ण,
	.line_info_rec_size = माप(काष्ठा bpf_line_info),
	.nr_jited_ksyms = 2,
	.dead_code_cnt = 5,
	.dead_code_mask = 0x1e2,
	.dead_func_cnt = 1,
	.dead_func_mask = 0x2,
पूर्ण,

अणु
	.descr = "line_info (dead subprog + dead start w/ move)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_FUNC_PROTO_ENC(1, 1),			/* [2] */
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 1),
		BTF_FUNC_ENC(NAME_TBD, 2),			/* [3] */
		BTF_FUNC_ENC(NAME_TBD, 2),			/* [4] */
		BTF_FUNC_ENC(NAME_TBD, 2),			/* [5] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0int\0x\0dead\0main\0func\0int a=1+1;\0/* live call */"
		    "\0return 0;\0return 0;\0/* dead */\0/* dead */"
		    "\0/* dead */\0return bla + 1;\0return bla + 1;"
		    "\0return bla + 1;\0return func(a);\0b+=1;\0return b;"),
	.insns = अणु
		BPF_MOV64_IMM(BPF_REG_2, 1),
		BPF_JMP_IMM(BPF_JGE, BPF_REG_2, 0, 1),
		BPF_CALL_REL(3),
		BPF_CALL_REL(5),
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_EXIT_INSN(),
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_CALL_REL(1),
		BPF_EXIT_INSN(),
		BPF_JMP_IMM(BPF_JA, 0, 0, 0),
		BPF_MOV64_REG(BPF_REG_0, 2),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 1),
		BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.func_info_cnt = 3,
	.func_info_rec_size = 8,
		.func_info = अणु अणु0, 4पूर्ण, अणु6, 3पूर्ण, अणु9, 5पूर्ण पूर्ण,
	.line_info = अणु
		BPF_LINE_INFO_ENC(0, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(3, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(4, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(5, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(6, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(7, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(8, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(9, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(11, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(12, 0, NAME_TBD, 2, 9),
		BTF_END_RAW,
	पूर्ण,
	.line_info_rec_size = माप(काष्ठा bpf_line_info),
	.nr_jited_ksyms = 2,
	.dead_code_cnt = 3,
	.dead_code_mask = 0x70,
	.dead_func_cnt = 1,
	.dead_func_mask = 0x2,
पूर्ण,

अणु
	.descr = "line_info (dead end + subprog start w/ no linfo)",
	.raw_types = अणु
		BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
		BTF_FUNC_PROTO_ENC(1, 1),			/* [2] */
			BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 1),
		BTF_FUNC_ENC(NAME_TBD, 2),			/* [3] */
		BTF_FUNC_ENC(NAME_TBD, 2),			/* [4] */
		BTF_END_RAW,
	पूर्ण,
	BTF_STR_SEC("\0int\0x\0main\0func\0/* main linfo */\0/* func linfo */"),
	.insns = अणु
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_JMP_IMM(BPF_JGE, BPF_REG_0, 1, 3),
		BPF_CALL_REL(3),
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_EXIT_INSN(),
		BPF_EXIT_INSN(),
		BPF_JMP_IMM(BPF_JA, 0, 0, 0),
		BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.func_info_cnt = 2,
	.func_info_rec_size = 8,
	.func_info = अणु अणु0, 3पूर्ण, अणु6, 4पूर्ण, पूर्ण,
	.line_info = अणु
		BPF_LINE_INFO_ENC(0, 0, NAME_TBD, 1, 10),
		BPF_LINE_INFO_ENC(6, 0, NAME_TBD, 1, 10),
		BTF_END_RAW,
	पूर्ण,
	.line_info_rec_size = माप(काष्ठा bpf_line_info),
	.nr_jited_ksyms = 2,
पूर्ण,

पूर्ण;

अटल माप_प्रकार probe_prog_length(स्थिर काष्ठा bpf_insn *fp)
अणु
	माप_प्रकार len;

	क्रम (len = MAX_INSNS - 1; len > 0; --len)
		अगर (fp[len].code != 0 || fp[len].imm != 0)
			अवरोध;
	वापस len + 1;
पूर्ण

अटल __u32 *patch_name_tbd(स्थिर __u32 *raw_u32,
			     स्थिर अक्षर *str, __u32 str_off,
			     अचिन्हित पूर्णांक str_sec_size,
			     अचिन्हित पूर्णांक *ret_size)
अणु
	पूर्णांक i, raw_u32_size = get_raw_sec_size(raw_u32);
	स्थिर अक्षर *end_str = str + str_sec_size;
	स्थिर अक्षर *next_str = str + str_off;
	__u32 *new_u32 = शून्य;

	अगर (raw_u32_size == -1)
		वापस ERR_PTR(-EINVAL);

	अगर (!raw_u32_size) अणु
		*ret_size = 0;
		वापस शून्य;
	पूर्ण

	new_u32 = दो_स्मृति(raw_u32_size);
	अगर (!new_u32)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0; i < raw_u32_size / माप(raw_u32[0]); i++) अणु
		अगर (raw_u32[i] == NAME_TBD) अणु
			next_str = get_next_str(next_str, end_str);
			अगर (CHECK(!next_str, "Error in getting next_str\n")) अणु
				मुक्त(new_u32);
				वापस ERR_PTR(-EINVAL);
			पूर्ण
			new_u32[i] = next_str - str;
			next_str += म_माप(next_str);
		पूर्ण अन्यथा अणु
			new_u32[i] = raw_u32[i];
		पूर्ण
	पूर्ण

	*ret_size = raw_u32_size;
	वापस new_u32;
पूर्ण

अटल पूर्णांक test_get_finfo(स्थिर काष्ठा prog_info_raw_test *test,
			  पूर्णांक prog_fd)
अणु
	काष्ठा bpf_prog_info info = अणुपूर्ण;
	काष्ठा bpf_func_info *finfo;
	__u32 info_len, rec_size, i;
	व्योम *func_info = शून्य;
	__u32 nr_func_info;
	पूर्णांक err;

	/* get necessary lens */
	info_len = माप(काष्ठा bpf_prog_info);
	err = bpf_obj_get_info_by_fd(prog_fd, &info, &info_len);
	अगर (CHECK(err == -1, "invalid get info (1st) errno:%d", त्रुटि_सं)) अणु
		ख_लिखो(मानक_त्रुटि, "%s\n", btf_log_buf);
		वापस -1;
	पूर्ण
	nr_func_info = test->func_info_cnt - test->dead_func_cnt;
	अगर (CHECK(info.nr_func_info != nr_func_info,
		  "incorrect info.nr_func_info (1st) %d",
		  info.nr_func_info)) अणु
		वापस -1;
	पूर्ण

	rec_size = info.func_info_rec_size;
	अगर (CHECK(rec_size != माप(काष्ठा bpf_func_info),
		  "incorrect info.func_info_rec_size (1st) %d", rec_size)) अणु
		वापस -1;
	पूर्ण

	अगर (!info.nr_func_info)
		वापस 0;

	func_info = दो_स्मृति(info.nr_func_info * rec_size);
	अगर (CHECK(!func_info, "out of memory"))
		वापस -1;

	/* reset info to only retrieve func_info related data */
	स_रखो(&info, 0, माप(info));
	info.nr_func_info = nr_func_info;
	info.func_info_rec_size = rec_size;
	info.func_info = ptr_to_u64(func_info);
	err = bpf_obj_get_info_by_fd(prog_fd, &info, &info_len);
	अगर (CHECK(err == -1, "invalid get info (2nd) errno:%d", त्रुटि_सं)) अणु
		ख_लिखो(मानक_त्रुटि, "%s\n", btf_log_buf);
		err = -1;
		जाओ करोne;
	पूर्ण
	अगर (CHECK(info.nr_func_info != nr_func_info,
		  "incorrect info.nr_func_info (2nd) %d",
		  info.nr_func_info)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण
	अगर (CHECK(info.func_info_rec_size != rec_size,
		  "incorrect info.func_info_rec_size (2nd) %d",
		  info.func_info_rec_size)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	finfo = func_info;
	क्रम (i = 0; i < nr_func_info; i++) अणु
		अगर (test->dead_func_mask & (1 << i))
			जारी;
		अगर (CHECK(finfo->type_id != test->func_info[i][1],
			  "incorrect func_type %u expected %u",
			  finfo->type_id, test->func_info[i][1])) अणु
			err = -1;
			जाओ करोne;
		पूर्ण
		finfo = (व्योम *)finfo + rec_size;
	पूर्ण

	err = 0;

करोne:
	मुक्त(func_info);
	वापस err;
पूर्ण

अटल पूर्णांक test_get_linfo(स्थिर काष्ठा prog_info_raw_test *test,
			  स्थिर व्योम *patched_linfo,
			  __u32 cnt, पूर्णांक prog_fd)
अणु
	__u32 i, info_len, nr_jited_ksyms, nr_jited_func_lens;
	__u64 *jited_linfo = शून्य, *jited_ksyms = शून्य;
	__u32 rec_size, jited_rec_size, jited_cnt;
	काष्ठा bpf_line_info *linfo = शून्य;
	__u32 cur_func_len, ksyms_found;
	काष्ठा bpf_prog_info info = अणुपूर्ण;
	__u32 *jited_func_lens = शून्य;
	__u64 cur_func_ksyms;
	__u32 dead_insns;
	पूर्णांक err;

	jited_cnt = cnt;
	rec_size = माप(*linfo);
	jited_rec_size = माप(*jited_linfo);
	अगर (test->nr_jited_ksyms)
		nr_jited_ksyms = test->nr_jited_ksyms;
	अन्यथा
		nr_jited_ksyms = test->func_info_cnt - test->dead_func_cnt;
	nr_jited_func_lens = nr_jited_ksyms;

	info_len = माप(काष्ठा bpf_prog_info);
	err = bpf_obj_get_info_by_fd(prog_fd, &info, &info_len);
	अगर (CHECK(err == -1, "err:%d errno:%d", err, त्रुटि_सं)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	अगर (!info.jited_prog_len) अणु
		/* prog is not jited */
		jited_cnt = 0;
		nr_jited_ksyms = 1;
		nr_jited_func_lens = 1;
	पूर्ण

	अगर (CHECK(info.nr_line_info != cnt ||
		  info.nr_jited_line_info != jited_cnt ||
		  info.nr_jited_ksyms != nr_jited_ksyms ||
		  info.nr_jited_func_lens != nr_jited_func_lens ||
		  (!info.nr_line_info && info.nr_jited_line_info),
		  "info: nr_line_info:%u(expected:%u) nr_jited_line_info:%u(expected:%u) nr_jited_ksyms:%u(expected:%u) nr_jited_func_lens:%u(expected:%u)",
		  info.nr_line_info, cnt,
		  info.nr_jited_line_info, jited_cnt,
		  info.nr_jited_ksyms, nr_jited_ksyms,
		  info.nr_jited_func_lens, nr_jited_func_lens)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	अगर (CHECK(info.line_info_rec_size != माप(काष्ठा bpf_line_info) ||
		  info.jited_line_info_rec_size != माप(__u64),
		  "info: line_info_rec_size:%u(userspace expected:%u) jited_line_info_rec_size:%u(userspace expected:%u)",
		  info.line_info_rec_size, rec_size,
		  info.jited_line_info_rec_size, jited_rec_size)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	अगर (!cnt)
		वापस 0;

	rec_size = info.line_info_rec_size;
	jited_rec_size = info.jited_line_info_rec_size;

	स_रखो(&info, 0, माप(info));

	linfo = सुस्मृति(cnt, rec_size);
	अगर (CHECK(!linfo, "!linfo")) अणु
		err = -1;
		जाओ करोne;
	पूर्ण
	info.nr_line_info = cnt;
	info.line_info_rec_size = rec_size;
	info.line_info = ptr_to_u64(linfo);

	अगर (jited_cnt) अणु
		jited_linfo = सुस्मृति(jited_cnt, jited_rec_size);
		jited_ksyms = सुस्मृति(nr_jited_ksyms, माप(*jited_ksyms));
		jited_func_lens = सुस्मृति(nr_jited_func_lens,
					 माप(*jited_func_lens));
		अगर (CHECK(!jited_linfo || !jited_ksyms || !jited_func_lens,
			  "jited_linfo:%p jited_ksyms:%p jited_func_lens:%p",
			  jited_linfo, jited_ksyms, jited_func_lens)) अणु
			err = -1;
			जाओ करोne;
		पूर्ण

		info.nr_jited_line_info = jited_cnt;
		info.jited_line_info_rec_size = jited_rec_size;
		info.jited_line_info = ptr_to_u64(jited_linfo);
		info.nr_jited_ksyms = nr_jited_ksyms;
		info.jited_ksyms = ptr_to_u64(jited_ksyms);
		info.nr_jited_func_lens = nr_jited_func_lens;
		info.jited_func_lens = ptr_to_u64(jited_func_lens);
	पूर्ण

	err = bpf_obj_get_info_by_fd(prog_fd, &info, &info_len);

	/*
	 * Only recheck the info.*line_info* fields.
	 * Other fields are not the concern of this test.
	 */
	अगर (CHECK(err == -1 ||
		  info.nr_line_info != cnt ||
		  (jited_cnt && !info.jited_line_info) ||
		  info.nr_jited_line_info != jited_cnt ||
		  info.line_info_rec_size != rec_size ||
		  info.jited_line_info_rec_size != jited_rec_size,
		  "err:%d errno:%d info: nr_line_info:%u(expected:%u) nr_jited_line_info:%u(expected:%u) line_info_rec_size:%u(expected:%u) jited_linfo_rec_size:%u(expected:%u) line_info:%p jited_line_info:%p",
		  err, त्रुटि_सं,
		  info.nr_line_info, cnt,
		  info.nr_jited_line_info, jited_cnt,
		  info.line_info_rec_size, rec_size,
		  info.jited_line_info_rec_size, jited_rec_size,
		  (व्योम *)(दीर्घ)info.line_info,
		  (व्योम *)(दीर्घ)info.jited_line_info)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	dead_insns = 0;
	जबतक (test->dead_code_mask & (1 << dead_insns))
		dead_insns++;

	CHECK(linfo[0].insn_off, "linfo[0].insn_off:%u",
	      linfo[0].insn_off);
	क्रम (i = 1; i < cnt; i++) अणु
		स्थिर काष्ठा bpf_line_info *expected_linfo;

		जबतक (test->dead_code_mask & (1 << (i + dead_insns)))
			dead_insns++;

		expected_linfo = patched_linfo +
			((i + dead_insns) * test->line_info_rec_size);
		अगर (CHECK(linfo[i].insn_off <= linfo[i - 1].insn_off,
			  "linfo[%u].insn_off:%u <= linfo[%u].insn_off:%u",
			  i, linfo[i].insn_off,
			  i - 1, linfo[i - 1].insn_off)) अणु
			err = -1;
			जाओ करोne;
		पूर्ण
		अगर (CHECK(linfo[i].file_name_off != expected_linfo->file_name_off ||
			  linfo[i].line_off != expected_linfo->line_off ||
			  linfo[i].line_col != expected_linfo->line_col,
			  "linfo[%u] (%u, %u, %u) != (%u, %u, %u)", i,
			  linfo[i].file_name_off,
			  linfo[i].line_off,
			  linfo[i].line_col,
			  expected_linfo->file_name_off,
			  expected_linfo->line_off,
			  expected_linfo->line_col)) अणु
			err = -1;
			जाओ करोne;
		पूर्ण
	पूर्ण

	अगर (!jited_cnt) अणु
		ख_लिखो(मानक_त्रुटि, "not jited. skipping jited_line_info check. ");
		err = 0;
		जाओ करोne;
	पूर्ण

	अगर (CHECK(jited_linfo[0] != jited_ksyms[0],
		  "jited_linfo[0]:%lx != jited_ksyms[0]:%lx",
		  (दीर्घ)(jited_linfo[0]), (दीर्घ)(jited_ksyms[0]))) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	ksyms_found = 1;
	cur_func_len = jited_func_lens[0];
	cur_func_ksyms = jited_ksyms[0];
	क्रम (i = 1; i < jited_cnt; i++) अणु
		अगर (ksyms_found < nr_jited_ksyms &&
		    jited_linfo[i] == jited_ksyms[ksyms_found]) अणु
			cur_func_ksyms = jited_ksyms[ksyms_found];
			cur_func_len = jited_ksyms[ksyms_found];
			ksyms_found++;
			जारी;
		पूर्ण

		अगर (CHECK(jited_linfo[i] <= jited_linfo[i - 1],
			  "jited_linfo[%u]:%lx <= jited_linfo[%u]:%lx",
			  i, (दीर्घ)jited_linfo[i],
			  i - 1, (दीर्घ)(jited_linfo[i - 1]))) अणु
			err = -1;
			जाओ करोne;
		पूर्ण

		अगर (CHECK(jited_linfo[i] - cur_func_ksyms > cur_func_len,
			  "jited_linfo[%u]:%lx - %lx > %u",
			  i, (दीर्घ)jited_linfo[i], (दीर्घ)cur_func_ksyms,
			  cur_func_len)) अणु
			err = -1;
			जाओ करोne;
		पूर्ण
	पूर्ण

	अगर (CHECK(ksyms_found != nr_jited_ksyms,
		  "ksyms_found:%u != nr_jited_ksyms:%u",
		  ksyms_found, nr_jited_ksyms)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	err = 0;

करोne:
	मुक्त(linfo);
	मुक्त(jited_linfo);
	मुक्त(jited_ksyms);
	मुक्त(jited_func_lens);
	वापस err;
पूर्ण

अटल व्योम करो_test_info_raw(अचिन्हित पूर्णांक test_num)
अणु
	स्थिर काष्ठा prog_info_raw_test *test = &info_raw_tests[test_num - 1];
	अचिन्हित पूर्णांक raw_btf_size, linfo_str_off, linfo_size;
	पूर्णांक btf_fd = -1, prog_fd = -1, err = 0;
	व्योम *raw_btf, *patched_linfo = शून्य;
	स्थिर अक्षर *ret_next_str;
	जोड़ bpf_attr attr = अणुपूर्ण;

	अगर (!test__start_subtest(test->descr))
		वापस;

	raw_btf = btf_raw_create(&hdr_पंचांगpl, test->raw_types,
				 test->str_sec, test->str_sec_size,
				 &raw_btf_size, &ret_next_str);
	अगर (!raw_btf)
		वापस;

	*btf_log_buf = '\0';
	btf_fd = bpf_load_btf(raw_btf, raw_btf_size,
			      btf_log_buf, BTF_LOG_BUF_SIZE,
			      always_log);
	मुक्त(raw_btf);

	अगर (CHECK(btf_fd == -1, "invalid btf_fd errno:%d", त्रुटि_सं)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	अगर (*btf_log_buf && always_log)
		ख_लिखो(मानक_त्रुटि, "\n%s", btf_log_buf);
	*btf_log_buf = '\0';

	linfo_str_off = ret_next_str - test->str_sec;
	patched_linfo = patch_name_tbd(test->line_info,
				       test->str_sec, linfo_str_off,
				       test->str_sec_size, &linfo_size);
	अगर (IS_ERR(patched_linfo)) अणु
		ख_लिखो(मानक_त्रुटि, "error in creating raw bpf_line_info");
		err = -1;
		जाओ करोne;
	पूर्ण

	attr.prog_type = test->prog_type;
	attr.insns = ptr_to_u64(test->insns);
	attr.insn_cnt = probe_prog_length(test->insns);
	attr.license = ptr_to_u64("GPL");
	attr.prog_btf_fd = btf_fd;
	attr.func_info_rec_size = test->func_info_rec_size;
	attr.func_info_cnt = test->func_info_cnt;
	attr.func_info = ptr_to_u64(test->func_info);
	attr.log_buf = ptr_to_u64(btf_log_buf);
	attr.log_size = BTF_LOG_BUF_SIZE;
	attr.log_level = 1;
	अगर (linfo_size) अणु
		attr.line_info_rec_size = test->line_info_rec_size;
		attr.line_info = ptr_to_u64(patched_linfo);
		attr.line_info_cnt = linfo_size / attr.line_info_rec_size;
	पूर्ण

	prog_fd = syscall(__NR_bpf, BPF_PROG_LOAD, &attr, माप(attr));
	err = ((prog_fd == -1) != test->expected_prog_load_failure);
	अगर (CHECK(err, "prog_fd:%d expected_prog_load_failure:%u errno:%d",
		  prog_fd, test->expected_prog_load_failure, त्रुटि_सं) ||
	    CHECK(test->err_str && !म_माला(btf_log_buf, test->err_str),
		  "expected err_str:%s", test->err_str)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	अगर (prog_fd == -1)
		जाओ करोne;

	err = test_get_finfo(test, prog_fd);
	अगर (err)
		जाओ करोne;

	err = test_get_linfo(test, patched_linfo,
			     attr.line_info_cnt - test->dead_code_cnt,
			     prog_fd);
	अगर (err)
		जाओ करोne;

करोne:
	अगर (*btf_log_buf && (err || always_log))
		ख_लिखो(मानक_त्रुटि, "\n%s", btf_log_buf);

	अगर (btf_fd != -1)
		बंद(btf_fd);
	अगर (prog_fd != -1)
		बंद(prog_fd);

	अगर (!IS_ERR(patched_linfo))
		मुक्त(patched_linfo);
पूर्ण

काष्ठा btf_raw_data अणु
	__u32 raw_types[MAX_NR_RAW_U32];
	स्थिर अक्षर *str_sec;
	__u32 str_sec_size;
पूर्ण;

काष्ठा btf_dedup_test अणु
	स्थिर अक्षर *descr;
	काष्ठा btf_raw_data input;
	काष्ठा btf_raw_data expect;
	काष्ठा btf_dedup_opts opts;
पूर्ण;

स्थिर काष्ठा btf_dedup_test dedup_tests[] = अणु

अणु
	.descr = "dedup: unused strings filtering",
	.input = अणु
		.raw_types = अणु
			BTF_TYPE_INT_ENC(NAME_NTH(2), BTF_INT_SIGNED, 0, 32, 4),
			BTF_TYPE_INT_ENC(NAME_NTH(5), BTF_INT_SIGNED, 0, 64, 8),
			BTF_END_RAW,
		पूर्ण,
		BTF_STR_SEC("\0unused\0int\0foo\0bar\0long"),
	पूर्ण,
	.expect = अणु
		.raw_types = अणु
			BTF_TYPE_INT_ENC(NAME_NTH(1), BTF_INT_SIGNED, 0, 32, 4),
			BTF_TYPE_INT_ENC(NAME_NTH(2), BTF_INT_SIGNED, 0, 64, 8),
			BTF_END_RAW,
		पूर्ण,
		BTF_STR_SEC("\0int\0long"),
	पूर्ण,
	.opts = अणु
		.करोnt_resolve_fwds = false,
	पूर्ण,
पूर्ण,
अणु
	.descr = "dedup: strings deduplication",
	.input = अणु
		.raw_types = अणु
			BTF_TYPE_INT_ENC(NAME_NTH(1), BTF_INT_SIGNED, 0, 32, 4),
			BTF_TYPE_INT_ENC(NAME_NTH(2), BTF_INT_SIGNED, 0, 64, 8),
			BTF_TYPE_INT_ENC(NAME_NTH(3), BTF_INT_SIGNED, 0, 32, 4),
			BTF_TYPE_INT_ENC(NAME_NTH(4), BTF_INT_SIGNED, 0, 64, 8),
			BTF_TYPE_INT_ENC(NAME_NTH(5), BTF_INT_SIGNED, 0, 32, 4),
			BTF_END_RAW,
		पूर्ण,
		BTF_STR_SEC("\0int\0long int\0int\0long int\0int"),
	पूर्ण,
	.expect = अणु
		.raw_types = अणु
			BTF_TYPE_INT_ENC(NAME_NTH(1), BTF_INT_SIGNED, 0, 32, 4),
			BTF_TYPE_INT_ENC(NAME_NTH(2), BTF_INT_SIGNED, 0, 64, 8),
			BTF_END_RAW,
		पूर्ण,
		BTF_STR_SEC("\0int\0long int"),
	पूर्ण,
	.opts = अणु
		.करोnt_resolve_fwds = false,
	पूर्ण,
पूर्ण,
अणु
	.descr = "dedup: struct example #1",
	/*
	 * काष्ठा s अणु
	 *	काष्ठा s *next;
	 *	स्थिर पूर्णांक *a;
	 *	पूर्णांक b[16];
	 *	पूर्णांक c;
	 * पूर्ण
	 */
	.input = अणु
		.raw_types = अणु
			/* पूर्णांक */
			BTF_TYPE_INT_ENC(NAME_NTH(1), BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
			/* पूर्णांक[16] */
			BTF_TYPE_ARRAY_ENC(1, 1, 16),					/* [2] */
			/* काष्ठा s अणु */
			BTF_STRUCT_ENC(NAME_NTH(2), 5, 88),				/* [3] */
				BTF_MEMBER_ENC(NAME_NTH(3), 4, 0),	/* काष्ठा s *next;	*/
				BTF_MEMBER_ENC(NAME_NTH(4), 5, 64),	/* स्थिर पूर्णांक *a;	*/
				BTF_MEMBER_ENC(NAME_NTH(5), 2, 128),	/* पूर्णांक b[16];		*/
				BTF_MEMBER_ENC(NAME_NTH(6), 1, 640),	/* पूर्णांक c;		*/
				BTF_MEMBER_ENC(NAME_NTH(8), 13, 672),	/* भग्न d;		*/
			/* ptr -> [3] काष्ठा s */
			BTF_PTR_ENC(3),							/* [4] */
			/* ptr -> [6] स्थिर पूर्णांक */
			BTF_PTR_ENC(6),							/* [5] */
			/* स्थिर -> [1] पूर्णांक */
			BTF_CONST_ENC(1),						/* [6] */

			/* full copy of the above */
			BTF_TYPE_INT_ENC(NAME_NTH(1), BTF_INT_SIGNED, 0, 32, 4),	/* [7] */
			BTF_TYPE_ARRAY_ENC(7, 7, 16),					/* [8] */
			BTF_STRUCT_ENC(NAME_NTH(2), 5, 88),				/* [9] */
				BTF_MEMBER_ENC(NAME_NTH(3), 10, 0),
				BTF_MEMBER_ENC(NAME_NTH(4), 11, 64),
				BTF_MEMBER_ENC(NAME_NTH(5), 8, 128),
				BTF_MEMBER_ENC(NAME_NTH(6), 7, 640),
				BTF_MEMBER_ENC(NAME_NTH(8), 13, 672),
			BTF_PTR_ENC(9),							/* [10] */
			BTF_PTR_ENC(12),						/* [11] */
			BTF_CONST_ENC(7),						/* [12] */
			BTF_TYPE_FLOAT_ENC(NAME_NTH(7), 4),				/* [13] */
			BTF_END_RAW,
		पूर्ण,
		BTF_STR_SEC("\0int\0s\0next\0a\0b\0c\0float\0d"),
	पूर्ण,
	.expect = अणु
		.raw_types = अणु
			/* पूर्णांक */
			BTF_TYPE_INT_ENC(NAME_NTH(5), BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
			/* पूर्णांक[16] */
			BTF_TYPE_ARRAY_ENC(1, 1, 16),					/* [2] */
			/* काष्ठा s अणु */
			BTF_STRUCT_ENC(NAME_NTH(8), 5, 88),				/* [3] */
				BTF_MEMBER_ENC(NAME_NTH(7), 4, 0),	/* काष्ठा s *next;	*/
				BTF_MEMBER_ENC(NAME_NTH(1), 5, 64),	/* स्थिर पूर्णांक *a;	*/
				BTF_MEMBER_ENC(NAME_NTH(2), 2, 128),	/* पूर्णांक b[16];		*/
				BTF_MEMBER_ENC(NAME_NTH(3), 1, 640),	/* पूर्णांक c;		*/
				BTF_MEMBER_ENC(NAME_NTH(4), 7, 672),	/* भग्न d;		*/
			/* ptr -> [3] काष्ठा s */
			BTF_PTR_ENC(3),							/* [4] */
			/* ptr -> [6] स्थिर पूर्णांक */
			BTF_PTR_ENC(6),							/* [5] */
			/* स्थिर -> [1] पूर्णांक */
			BTF_CONST_ENC(1),						/* [6] */
			BTF_TYPE_FLOAT_ENC(NAME_NTH(7), 4),				/* [7] */
			BTF_END_RAW,
		पूर्ण,
		BTF_STR_SEC("\0a\0b\0c\0d\0int\0float\0next\0s"),
	पूर्ण,
	.opts = अणु
		.करोnt_resolve_fwds = false,
	पूर्ण,
पूर्ण,
अणु
	.descr = "dedup: struct <-> fwd resolution w/ hash collision",
	/*
	 * // CU 1:
	 * काष्ठा x;
	 * काष्ठा s अणु
	 *	काष्ठा x *x;
	 * पूर्ण;
	 * // CU 2:
	 * काष्ठा x अणुपूर्ण;
	 * काष्ठा s अणु
	 *	काष्ठा x *x;
	 * पूर्ण;
	 */
	.input = अणु
		.raw_types = अणु
			/* CU 1 */
			BTF_FWD_ENC(NAME_TBD, 0 /* काष्ठा fwd */),	/* [1] fwd x      */
			BTF_PTR_ENC(1),					/* [2] ptr -> [1] */
			BTF_STRUCT_ENC(NAME_TBD, 1, 8),			/* [3] काष्ठा s   */
				BTF_MEMBER_ENC(NAME_TBD, 2, 0),
			/* CU 2 */
			BTF_STRUCT_ENC(NAME_TBD, 0, 0),			/* [4] काष्ठा x   */
			BTF_PTR_ENC(4),					/* [5] ptr -> [4] */
			BTF_STRUCT_ENC(NAME_TBD, 1, 8),			/* [6] काष्ठा s   */
				BTF_MEMBER_ENC(NAME_TBD, 5, 0),
			BTF_END_RAW,
		पूर्ण,
		BTF_STR_SEC("\0x\0s\0x\0x\0s\0x\0"),
	पूर्ण,
	.expect = अणु
		.raw_types = अणु
			BTF_PTR_ENC(3),					/* [1] ptr -> [3] */
			BTF_STRUCT_ENC(NAME_TBD, 1, 8),			/* [2] काष्ठा s   */
				BTF_MEMBER_ENC(NAME_TBD, 1, 0),
			BTF_STRUCT_ENC(NAME_NTH(2), 0, 0),		/* [3] काष्ठा x   */
			BTF_END_RAW,
		पूर्ण,
		BTF_STR_SEC("\0s\0x"),
	पूर्ण,
	.opts = अणु
		.करोnt_resolve_fwds = false,
		.dedup_table_size = 1, /* क्रमce hash collisions */
	पूर्ण,
पूर्ण,
अणु
	.descr = "dedup: void equiv check",
	/*
	 * // CU 1:
	 * काष्ठा s अणु
	 *	काष्ठा अणुपूर्ण *x;
	 * पूर्ण;
	 * // CU 2:
	 * काष्ठा s अणु
	 *	पूर्णांक *x;
	 * पूर्ण;
	 */
	.input = अणु
		.raw_types = अणु
			/* CU 1 */
			BTF_STRUCT_ENC(0, 0, 1),				/* [1] काष्ठा अणुपूर्ण  */
			BTF_PTR_ENC(1),						/* [2] ptr -> [1] */
			BTF_STRUCT_ENC(NAME_NTH(1), 1, 8),			/* [3] काष्ठा s   */
				BTF_MEMBER_ENC(NAME_NTH(2), 2, 0),
			/* CU 2 */
			BTF_PTR_ENC(0),						/* [4] ptr -> व्योम */
			BTF_STRUCT_ENC(NAME_NTH(1), 1, 8),			/* [5] काष्ठा s   */
				BTF_MEMBER_ENC(NAME_NTH(2), 4, 0),
			BTF_END_RAW,
		पूर्ण,
		BTF_STR_SEC("\0s\0x"),
	पूर्ण,
	.expect = अणु
		.raw_types = अणु
			/* CU 1 */
			BTF_STRUCT_ENC(0, 0, 1),				/* [1] काष्ठा अणुपूर्ण  */
			BTF_PTR_ENC(1),						/* [2] ptr -> [1] */
			BTF_STRUCT_ENC(NAME_NTH(1), 1, 8),			/* [3] काष्ठा s   */
				BTF_MEMBER_ENC(NAME_NTH(2), 2, 0),
			/* CU 2 */
			BTF_PTR_ENC(0),						/* [4] ptr -> व्योम */
			BTF_STRUCT_ENC(NAME_NTH(1), 1, 8),			/* [5] काष्ठा s   */
				BTF_MEMBER_ENC(NAME_NTH(2), 4, 0),
			BTF_END_RAW,
		पूर्ण,
		BTF_STR_SEC("\0s\0x"),
	पूर्ण,
	.opts = अणु
		.करोnt_resolve_fwds = false,
		.dedup_table_size = 1, /* क्रमce hash collisions */
	पूर्ण,
पूर्ण,
अणु
	.descr = "dedup: all possible kinds (no duplicates)",
	.input = अणु
		.raw_types = अणु
			BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 8),		/* [1] पूर्णांक */
			BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_ENUM, 0, 2), 4),	/* [2] क्रमागत */
				BTF_ENUM_ENC(NAME_TBD, 0),
				BTF_ENUM_ENC(NAME_TBD, 1),
			BTF_FWD_ENC(NAME_TBD, 1 /* जोड़ kind_flag */),			/* [3] fwd */
			BTF_TYPE_ARRAY_ENC(2, 1, 7),					/* [4] array */
			BTF_STRUCT_ENC(NAME_TBD, 1, 4),					/* [5] काष्ठा */
				BTF_MEMBER_ENC(NAME_TBD, 1, 0),
			BTF_UNION_ENC(NAME_TBD, 1, 4),					/* [6] जोड़ */
				BTF_MEMBER_ENC(NAME_TBD, 1, 0),
			BTF_TYPEDEF_ENC(NAME_TBD, 1),					/* [7] प्रकार */
			BTF_PTR_ENC(0),							/* [8] ptr */
			BTF_CONST_ENC(8),						/* [9] स्थिर */
			BTF_VOLATILE_ENC(8),						/* [10] अस्थिर */
			BTF_RESTRICT_ENC(8),						/* [11] restrict */
			BTF_FUNC_PROTO_ENC(1, 2),					/* [12] func_proto */
				BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 1),
				BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 8),
			BTF_FUNC_ENC(NAME_TBD, 12),					/* [13] func */
			BTF_TYPE_FLOAT_ENC(NAME_TBD, 2),				/* [14] भग्न */
			BTF_END_RAW,
		पूर्ण,
		BTF_STR_SEC("\0A\0B\0C\0D\0E\0F\0G\0H\0I\0J\0K\0L\0M\0N"),
	पूर्ण,
	.expect = अणु
		.raw_types = अणु
			BTF_TYPE_INT_ENC(NAME_TBD, BTF_INT_SIGNED, 0, 32, 8),		/* [1] पूर्णांक */
			BTF_TYPE_ENC(NAME_TBD, BTF_INFO_ENC(BTF_KIND_ENUM, 0, 2), 4),	/* [2] क्रमागत */
				BTF_ENUM_ENC(NAME_TBD, 0),
				BTF_ENUM_ENC(NAME_TBD, 1),
			BTF_FWD_ENC(NAME_TBD, 1 /* जोड़ kind_flag */),			/* [3] fwd */
			BTF_TYPE_ARRAY_ENC(2, 1, 7),					/* [4] array */
			BTF_STRUCT_ENC(NAME_TBD, 1, 4),					/* [5] काष्ठा */
				BTF_MEMBER_ENC(NAME_TBD, 1, 0),
			BTF_UNION_ENC(NAME_TBD, 1, 4),					/* [6] जोड़ */
				BTF_MEMBER_ENC(NAME_TBD, 1, 0),
			BTF_TYPEDEF_ENC(NAME_TBD, 1),					/* [7] प्रकार */
			BTF_PTR_ENC(0),							/* [8] ptr */
			BTF_CONST_ENC(8),						/* [9] स्थिर */
			BTF_VOLATILE_ENC(8),						/* [10] अस्थिर */
			BTF_RESTRICT_ENC(8),						/* [11] restrict */
			BTF_FUNC_PROTO_ENC(1, 2),					/* [12] func_proto */
				BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 1),
				BTF_FUNC_PROTO_ARG_ENC(NAME_TBD, 8),
			BTF_FUNC_ENC(NAME_TBD, 12),					/* [13] func */
			BTF_TYPE_FLOAT_ENC(NAME_TBD, 2),				/* [14] भग्न */
			BTF_END_RAW,
		पूर्ण,
		BTF_STR_SEC("\0A\0B\0C\0D\0E\0F\0G\0H\0I\0J\0K\0L\0M\0N"),
	पूर्ण,
	.opts = अणु
		.करोnt_resolve_fwds = false,
	पूर्ण,
पूर्ण,
अणु
	.descr = "dedup: no int/float duplicates",
	.input = अणु
		.raw_types = अणु
			BTF_TYPE_INT_ENC(NAME_NTH(1), BTF_INT_SIGNED, 0, 32, 8),
			/* dअगरferent name */
			BTF_TYPE_INT_ENC(NAME_NTH(2), BTF_INT_SIGNED, 0, 32, 8),
			/* dअगरferent encoding */
			BTF_TYPE_INT_ENC(NAME_NTH(1), BTF_INT_CHAR, 0, 32, 8),
			BTF_TYPE_INT_ENC(NAME_NTH(1), BTF_INT_BOOL, 0, 32, 8),
			/* dअगरferent bit offset */
			BTF_TYPE_INT_ENC(NAME_NTH(1), BTF_INT_SIGNED, 8, 32, 8),
			/* dअगरferent bit size */
			BTF_TYPE_INT_ENC(NAME_NTH(1), BTF_INT_SIGNED, 0, 27, 8),
			/* dअगरferent byte size */
			BTF_TYPE_INT_ENC(NAME_NTH(1), BTF_INT_SIGNED, 0, 32, 4),
			/* all allowed sizes */
			BTF_TYPE_FLOAT_ENC(NAME_NTH(3), 2),
			BTF_TYPE_FLOAT_ENC(NAME_NTH(3), 4),
			BTF_TYPE_FLOAT_ENC(NAME_NTH(3), 8),
			BTF_TYPE_FLOAT_ENC(NAME_NTH(3), 12),
			BTF_TYPE_FLOAT_ENC(NAME_NTH(3), 16),
			BTF_END_RAW,
		पूर्ण,
		BTF_STR_SEC("\0int\0some other int\0float"),
	पूर्ण,
	.expect = अणु
		.raw_types = अणु
			BTF_TYPE_INT_ENC(NAME_NTH(1), BTF_INT_SIGNED, 0, 32, 8),
			/* dअगरferent name */
			BTF_TYPE_INT_ENC(NAME_NTH(2), BTF_INT_SIGNED, 0, 32, 8),
			/* dअगरferent encoding */
			BTF_TYPE_INT_ENC(NAME_NTH(1), BTF_INT_CHAR, 0, 32, 8),
			BTF_TYPE_INT_ENC(NAME_NTH(1), BTF_INT_BOOL, 0, 32, 8),
			/* dअगरferent bit offset */
			BTF_TYPE_INT_ENC(NAME_NTH(1), BTF_INT_SIGNED, 8, 32, 8),
			/* dअगरferent bit size */
			BTF_TYPE_INT_ENC(NAME_NTH(1), BTF_INT_SIGNED, 0, 27, 8),
			/* dअगरferent byte size */
			BTF_TYPE_INT_ENC(NAME_NTH(1), BTF_INT_SIGNED, 0, 32, 4),
			/* all allowed sizes */
			BTF_TYPE_FLOAT_ENC(NAME_NTH(3), 2),
			BTF_TYPE_FLOAT_ENC(NAME_NTH(3), 4),
			BTF_TYPE_FLOAT_ENC(NAME_NTH(3), 8),
			BTF_TYPE_FLOAT_ENC(NAME_NTH(3), 12),
			BTF_TYPE_FLOAT_ENC(NAME_NTH(3), 16),
			BTF_END_RAW,
		पूर्ण,
		BTF_STR_SEC("\0int\0some other int\0float"),
	पूर्ण,
	.opts = अणु
		.करोnt_resolve_fwds = false,
	पूर्ण,
पूर्ण,
अणु
	.descr = "dedup: enum fwd resolution",
	.input = अणु
		.raw_types = अणु
			/* [1] fwd क्रमागत 'e1' beक्रमe full क्रमागत */
			BTF_TYPE_ENC(NAME_NTH(1), BTF_INFO_ENC(BTF_KIND_ENUM, 0, 0), 4),
			/* [2] full क्रमागत 'e1' after fwd */
			BTF_TYPE_ENC(NAME_NTH(1), BTF_INFO_ENC(BTF_KIND_ENUM, 0, 1), 4),
				BTF_ENUM_ENC(NAME_NTH(2), 123),
			/* [3] full क्रमागत 'e2' beक्रमe fwd */
			BTF_TYPE_ENC(NAME_NTH(3), BTF_INFO_ENC(BTF_KIND_ENUM, 0, 1), 4),
				BTF_ENUM_ENC(NAME_NTH(4), 456),
			/* [4] fwd क्रमागत 'e2' after full क्रमागत */
			BTF_TYPE_ENC(NAME_NTH(3), BTF_INFO_ENC(BTF_KIND_ENUM, 0, 0), 4),
			/* [5] incompatible fwd क्रमागत with dअगरferent size */
			BTF_TYPE_ENC(NAME_NTH(1), BTF_INFO_ENC(BTF_KIND_ENUM, 0, 0), 1),
			/* [6] incompatible full क्रमागत with dअगरferent value */
			BTF_TYPE_ENC(NAME_NTH(1), BTF_INFO_ENC(BTF_KIND_ENUM, 0, 1), 4),
				BTF_ENUM_ENC(NAME_NTH(2), 321),
			BTF_END_RAW,
		पूर्ण,
		BTF_STR_SEC("\0e1\0e1_val\0e2\0e2_val"),
	पूर्ण,
	.expect = अणु
		.raw_types = अणु
			/* [1] full क्रमागत 'e1' */
			BTF_TYPE_ENC(NAME_NTH(1), BTF_INFO_ENC(BTF_KIND_ENUM, 0, 1), 4),
				BTF_ENUM_ENC(NAME_NTH(2), 123),
			/* [2] full क्रमागत 'e2' */
			BTF_TYPE_ENC(NAME_NTH(3), BTF_INFO_ENC(BTF_KIND_ENUM, 0, 1), 4),
				BTF_ENUM_ENC(NAME_NTH(4), 456),
			/* [3] incompatible fwd क्रमागत with dअगरferent size */
			BTF_TYPE_ENC(NAME_NTH(1), BTF_INFO_ENC(BTF_KIND_ENUM, 0, 0), 1),
			/* [4] incompatible full क्रमागत with dअगरferent value */
			BTF_TYPE_ENC(NAME_NTH(1), BTF_INFO_ENC(BTF_KIND_ENUM, 0, 1), 4),
				BTF_ENUM_ENC(NAME_NTH(2), 321),
			BTF_END_RAW,
		पूर्ण,
		BTF_STR_SEC("\0e1\0e1_val\0e2\0e2_val"),
	पूर्ण,
	.opts = अणु
		.करोnt_resolve_fwds = false,
	पूर्ण,
पूर्ण,
अणु
	.descr = "dedup: datasec and vars pass-through",
	.input = अणु
		.raw_types = अणु
			/* पूर्णांक */
			BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
			/* अटल पूर्णांक t */
			BTF_VAR_ENC(NAME_NTH(2), 1, 0),			/* [2] */
			/* .bss section */				/* [3] */
			BTF_TYPE_ENC(NAME_NTH(1), BTF_INFO_ENC(BTF_KIND_DATASEC, 0, 1), 4),
			BTF_VAR_SECINFO_ENC(2, 0, 4),
			/* पूर्णांक, referenced from [5] */
			BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [4] */
			/* another अटल पूर्णांक t */
			BTF_VAR_ENC(NAME_NTH(2), 4, 0),			/* [5] */
			/* another .bss section */			/* [6] */
			BTF_TYPE_ENC(NAME_NTH(1), BTF_INFO_ENC(BTF_KIND_DATASEC, 0, 1), 4),
			BTF_VAR_SECINFO_ENC(5, 0, 4),
			BTF_END_RAW,
		पूर्ण,
		BTF_STR_SEC("\0.bss\0t"),
	पूर्ण,
	.expect = अणु
		.raw_types = अणु
			/* पूर्णांक */
			BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),	/* [1] */
			/* अटल पूर्णांक t */
			BTF_VAR_ENC(NAME_NTH(2), 1, 0),			/* [2] */
			/* .bss section */				/* [3] */
			BTF_TYPE_ENC(NAME_NTH(1), BTF_INFO_ENC(BTF_KIND_DATASEC, 0, 1), 4),
			BTF_VAR_SECINFO_ENC(2, 0, 4),
			/* another अटल पूर्णांक t */
			BTF_VAR_ENC(NAME_NTH(2), 1, 0),			/* [4] */
			/* another .bss section */			/* [5] */
			BTF_TYPE_ENC(NAME_NTH(1), BTF_INFO_ENC(BTF_KIND_DATASEC, 0, 1), 4),
			BTF_VAR_SECINFO_ENC(4, 0, 4),
			BTF_END_RAW,
		पूर्ण,
		BTF_STR_SEC("\0.bss\0t"),
	पूर्ण,
	.opts = अणु
		.करोnt_resolve_fwds = false,
		.dedup_table_size = 1
	पूर्ण,
पूर्ण,

पूर्ण;

अटल पूर्णांक btf_type_size(स्थिर काष्ठा btf_type *t)
अणु
	पूर्णांक base_size = माप(काष्ठा btf_type);
	__u16 vlen = BTF_INFO_VLEN(t->info);
	__u16 kind = BTF_INFO_KIND(t->info);

	चयन (kind) अणु
	हाल BTF_KIND_FWD:
	हाल BTF_KIND_CONST:
	हाल BTF_KIND_VOLATILE:
	हाल BTF_KIND_RESTRICT:
	हाल BTF_KIND_PTR:
	हाल BTF_KIND_TYPEDEF:
	हाल BTF_KIND_FUNC:
	हाल BTF_KIND_FLOAT:
		वापस base_size;
	हाल BTF_KIND_INT:
		वापस base_size + माप(__u32);
	हाल BTF_KIND_ENUM:
		वापस base_size + vlen * माप(काष्ठा btf_क्रमागत);
	हाल BTF_KIND_ARRAY:
		वापस base_size + माप(काष्ठा btf_array);
	हाल BTF_KIND_STRUCT:
	हाल BTF_KIND_UNION:
		वापस base_size + vlen * माप(काष्ठा btf_member);
	हाल BTF_KIND_FUNC_PROTO:
		वापस base_size + vlen * माप(काष्ठा btf_param);
	हाल BTF_KIND_VAR:
		वापस base_size + माप(काष्ठा btf_var);
	हाल BTF_KIND_DATASEC:
		वापस base_size + vlen * माप(काष्ठा btf_var_secinfo);
	शेष:
		ख_लिखो(मानक_त्रुटि, "Unsupported BTF_KIND:%u\n", kind);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम dump_btf_strings(स्थिर अक्षर *strs, __u32 len)
अणु
	स्थिर अक्षर *cur = strs;
	पूर्णांक i = 0;

	जबतक (cur < strs + len) अणु
		ख_लिखो(मानक_त्रुटि, "string #%d: '%s'\n", i, cur);
		cur += म_माप(cur) + 1;
		i++;
	पूर्ण
पूर्ण

अटल व्योम करो_test_dedup(अचिन्हित पूर्णांक test_num)
अणु
	स्थिर काष्ठा btf_dedup_test *test = &dedup_tests[test_num - 1];
	__u32 test_nr_types, expect_nr_types, test_btf_size, expect_btf_size;
	स्थिर काष्ठा btf_header *test_hdr, *expect_hdr;
	काष्ठा btf *test_btf = शून्य, *expect_btf = शून्य;
	स्थिर व्योम *test_btf_data, *expect_btf_data;
	स्थिर अक्षर *ret_test_next_str, *ret_expect_next_str;
	स्थिर अक्षर *test_strs, *expect_strs;
	स्थिर अक्षर *test_str_cur;
	स्थिर अक्षर *expect_str_cur, *expect_str_end;
	अचिन्हित पूर्णांक raw_btf_size;
	व्योम *raw_btf;
	पूर्णांक err = 0, i;

	अगर (!test__start_subtest(test->descr))
		वापस;

	raw_btf = btf_raw_create(&hdr_पंचांगpl, test->input.raw_types,
				 test->input.str_sec, test->input.str_sec_size,
				 &raw_btf_size, &ret_test_next_str);
	अगर (!raw_btf)
		वापस;

	test_btf = btf__new((__u8 *)raw_btf, raw_btf_size);
	मुक्त(raw_btf);
	अगर (CHECK(IS_ERR(test_btf), "invalid test_btf errno:%ld",
		  PTR_ERR(test_btf))) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	raw_btf = btf_raw_create(&hdr_पंचांगpl, test->expect.raw_types,
				 test->expect.str_sec,
				 test->expect.str_sec_size,
				 &raw_btf_size, &ret_expect_next_str);
	अगर (!raw_btf)
		वापस;
	expect_btf = btf__new((__u8 *)raw_btf, raw_btf_size);
	मुक्त(raw_btf);
	अगर (CHECK(IS_ERR(expect_btf), "invalid expect_btf errno:%ld",
		  PTR_ERR(expect_btf))) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	err = btf__dedup(test_btf, शून्य, &test->opts);
	अगर (CHECK(err, "btf_dedup failed errno:%d", err)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	test_btf_data = btf__get_raw_data(test_btf, &test_btf_size);
	expect_btf_data = btf__get_raw_data(expect_btf, &expect_btf_size);
	अगर (CHECK(test_btf_size != expect_btf_size,
		  "test_btf_size:%u != expect_btf_size:%u",
		  test_btf_size, expect_btf_size)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	test_hdr = test_btf_data;
	test_strs = test_btf_data + माप(*test_hdr) + test_hdr->str_off;
	expect_hdr = expect_btf_data;
	expect_strs = expect_btf_data + माप(*test_hdr) + expect_hdr->str_off;
	अगर (CHECK(test_hdr->str_len != expect_hdr->str_len,
		  "test_hdr->str_len:%u != expect_hdr->str_len:%u",
		  test_hdr->str_len, expect_hdr->str_len)) अणु
		ख_लिखो(मानक_त्रुटि, "\ntest strings:\n");
		dump_btf_strings(test_strs, test_hdr->str_len);
		ख_लिखो(मानक_त्रुटि, "\nexpected strings:\n");
		dump_btf_strings(expect_strs, expect_hdr->str_len);
		err = -1;
		जाओ करोne;
	पूर्ण

	expect_str_cur = expect_strs;
	expect_str_end = expect_strs + expect_hdr->str_len;
	जबतक (expect_str_cur < expect_str_end) अणु
		माप_प्रकार test_len, expect_len;
		पूर्णांक off;

		off = btf__find_str(test_btf, expect_str_cur);
		अगर (CHECK(off < 0, "exp str '%s' not found: %d\n", expect_str_cur, off)) अणु
			err = -1;
			जाओ करोne;
		पूर्ण
		test_str_cur = btf__str_by_offset(test_btf, off);

		test_len = म_माप(test_str_cur);
		expect_len = म_माप(expect_str_cur);
		अगर (CHECK(test_len != expect_len,
			  "test_len:%zu != expect_len:%zu "
			  "(test_str:%s, expect_str:%s)",
			  test_len, expect_len, test_str_cur, expect_str_cur)) अणु
			err = -1;
			जाओ करोne;
		पूर्ण
		अगर (CHECK(म_भेद(test_str_cur, expect_str_cur),
			  "test_str:%s != expect_str:%s",
			  test_str_cur, expect_str_cur)) अणु
			err = -1;
			जाओ करोne;
		पूर्ण
		expect_str_cur += expect_len + 1;
	पूर्ण

	test_nr_types = btf__get_nr_types(test_btf);
	expect_nr_types = btf__get_nr_types(expect_btf);
	अगर (CHECK(test_nr_types != expect_nr_types,
		  "test_nr_types:%u != expect_nr_types:%u",
		  test_nr_types, expect_nr_types)) अणु
		err = -1;
		जाओ करोne;
	पूर्ण

	क्रम (i = 1; i <= test_nr_types; i++) अणु
		स्थिर काष्ठा btf_type *test_type, *expect_type;
		पूर्णांक test_size, expect_size;

		test_type = btf__type_by_id(test_btf, i);
		expect_type = btf__type_by_id(expect_btf, i);
		test_size = btf_type_size(test_type);
		expect_size = btf_type_size(expect_type);

		अगर (CHECK(test_size != expect_size,
			  "type #%d: test_size:%d != expect_size:%u",
			  i, test_size, expect_size)) अणु
			err = -1;
			जाओ करोne;
		पूर्ण
		अगर (CHECK(btf_kind(test_type) != btf_kind(expect_type),
			  "type %d kind: exp %d != got %u\n",
			  i, btf_kind(expect_type), btf_kind(test_type))) अणु
			err = -1;
			जाओ करोne;
		पूर्ण
		अगर (CHECK(test_type->info != expect_type->info,
			  "type %d info: exp %d != got %u\n",
			  i, expect_type->info, test_type->info)) अणु
			err = -1;
			जाओ करोne;
		पूर्ण
		अगर (CHECK(test_type->size != expect_type->size,
			  "type %d size/type: exp %d != got %u\n",
			  i, expect_type->size, test_type->size)) अणु
			err = -1;
			जाओ करोne;
		पूर्ण
	पूर्ण

करोne:
	अगर (!IS_ERR(test_btf))
		btf__मुक्त(test_btf);
	अगर (!IS_ERR(expect_btf))
		btf__मुक्त(expect_btf);
पूर्ण

व्योम test_btf(व्योम)
अणु
	पूर्णांक i;

	always_log = env.verbosity > VERBOSE_NONE;

	क्रम (i = 1; i <= ARRAY_SIZE(raw_tests); i++)
		करो_test_raw(i);
	क्रम (i = 1; i <= ARRAY_SIZE(get_info_tests); i++)
		करो_test_get_info(i);
	क्रम (i = 1; i <= ARRAY_SIZE(file_tests); i++)
		करो_test_file(i);
	क्रम (i = 1; i <= ARRAY_SIZE(info_raw_tests); i++)
		करो_test_info_raw(i);
	क्रम (i = 1; i <= ARRAY_SIZE(dedup_tests); i++)
		करो_test_dedup(i);
	test_pprपूर्णांक();
पूर्ण
