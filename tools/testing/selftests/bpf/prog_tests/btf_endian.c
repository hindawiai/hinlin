<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#घोषणा _GNU_SOURCE
#समावेश <माला.स>
#समावेश <byteswap.h>
#समावेश <test_progs.h>
#समावेश <bpf/btf.h>

व्योम test_btf_endian() अणु
#अगर __BYTE_ORDER == __LITTLE_ENDIAN
	क्रमागत btf_endianness endian = BTF_LITTLE_ENDIAN;
#या_अगर __BYTE_ORDER == __BIG_ENDIAN
	क्रमागत btf_endianness endian = BTF_BIG_ENDIAN;
#अन्यथा
#त्रुटि "Unrecognized __BYTE_ORDER"
#पूर्ण_अगर
	क्रमागत btf_endianness swap_endian = 1 - endian;
	काष्ठा btf *btf = शून्य, *swap_btf = शून्य;
	स्थिर व्योम *raw_data, *swap_raw_data;
	स्थिर काष्ठा btf_type *t;
	स्थिर काष्ठा btf_header *hdr;
	__u32 raw_sz, swap_raw_sz;
	पूर्णांक var_id;

	/* Load BTF in native endianness */
	btf = btf__parse_elf("btf_dump_test_case_syntax.o", शून्य);
	अगर (!ASSERT_OK_PTR(btf, "parse_native_btf"))
		जाओ err_out;

	ASSERT_EQ(btf__endianness(btf), endian, "endian");
	btf__set_endianness(btf, swap_endian);
	ASSERT_EQ(btf__endianness(btf), swap_endian, "endian");

	/* Get raw BTF data in non-native endianness... */
	raw_data = btf__get_raw_data(btf, &raw_sz);
	अगर (!ASSERT_OK_PTR(raw_data, "raw_data_inverted"))
		जाओ err_out;

	/* ...and खोलो it as a new BTF instance */
	swap_btf = btf__new(raw_data, raw_sz);
	अगर (!ASSERT_OK_PTR(swap_btf, "parse_swap_btf"))
		जाओ err_out;

	ASSERT_EQ(btf__endianness(swap_btf), swap_endian, "endian");
	ASSERT_EQ(btf__get_nr_types(swap_btf), btf__get_nr_types(btf), "nr_types");

	swap_raw_data = btf__get_raw_data(swap_btf, &swap_raw_sz);
	अगर (!ASSERT_OK_PTR(swap_raw_data, "swap_raw_data"))
		जाओ err_out;

	/* both raw data should be identical (with non-native endianness) */
	ASSERT_OK(स_भेद(raw_data, swap_raw_data, raw_sz), "mem_identical");

	/* make sure that at least BTF header data is really swapped */
	hdr = swap_raw_data;
	ASSERT_EQ(bswap_16(hdr->magic), BTF_MAGIC, "btf_magic_swapped");
	ASSERT_EQ(raw_sz, swap_raw_sz, "raw_sizes");

	/* swap it back to native endianness */
	btf__set_endianness(swap_btf, endian);
	swap_raw_data = btf__get_raw_data(swap_btf, &swap_raw_sz);
	अगर (!ASSERT_OK_PTR(swap_raw_data, "swap_raw_data"))
		जाओ err_out;

	/* now header should have native BTF_MAGIC */
	hdr = swap_raw_data;
	ASSERT_EQ(hdr->magic, BTF_MAGIC, "btf_magic_native");
	ASSERT_EQ(raw_sz, swap_raw_sz, "raw_sizes");

	/* now modअगरy original BTF */
	var_id = btf__add_var(btf, "some_var", BTF_VAR_GLOBAL_ALLOCATED, 1);
	ASSERT_GT(var_id, 0, "var_id");

	btf__मुक्त(swap_btf);
	swap_btf = शून्य;

	btf__set_endianness(btf, swap_endian);
	raw_data = btf__get_raw_data(btf, &raw_sz);
	अगर (!ASSERT_OK_PTR(raw_data, "raw_data_inverted"))
		जाओ err_out;

	/* and re-खोलो swapped raw data again */
	swap_btf = btf__new(raw_data, raw_sz);
	अगर (!ASSERT_OK_PTR(swap_btf, "parse_swap_btf"))
		जाओ err_out;

	ASSERT_EQ(btf__endianness(swap_btf), swap_endian, "endian");
	ASSERT_EQ(btf__get_nr_types(swap_btf), btf__get_nr_types(btf), "nr_types");

	/* the type should appear as अगर it was stored in native endianness */
	t = btf__type_by_id(swap_btf, var_id);
	ASSERT_STREQ(btf__str_by_offset(swap_btf, t->name_off), "some_var", "var_name");
	ASSERT_EQ(btf_var(t)->linkage, BTF_VAR_GLOBAL_ALLOCATED, "var_linkage");
	ASSERT_EQ(t->type, 1, "var_type");

err_out:
	btf__मुक्त(btf);
	btf__मुक्त(swap_btf);
पूर्ण
