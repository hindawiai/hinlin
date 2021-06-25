<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (c) 2018 Facebook */

#समावेश <प्रकार.स>
#समावेश <मानकपन.स> /* क्रम (खाता *) used by json_ग_लिखोr */
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/bitops.h>
#समावेश <linux/btf.h>
#समावेश <linux/err.h>
#समावेश <bpf/btf.h>
#समावेश <bpf/bpf.h>

#समावेश "json_writer.h"
#समावेश "main.h"

#घोषणा BITS_PER_BYTE_MASK (BITS_PER_BYTE - 1)
#घोषणा BITS_PER_BYTE_MASKED(bits) ((bits) & BITS_PER_BYTE_MASK)
#घोषणा BITS_ROUNDDOWN_BYTES(bits) ((bits) >> 3)
#घोषणा BITS_ROUNDUP_BYTES(bits) \
	(BITS_ROUNDDOWN_BYTES(bits) + !!BITS_PER_BYTE_MASKED(bits))

अटल पूर्णांक btf_dumper_करो_type(स्थिर काष्ठा btf_dumper *d, __u32 type_id,
			      __u8 bit_offset, स्थिर व्योम *data);

अटल पूर्णांक btf_dump_func(स्थिर काष्ठा btf *btf, अक्षर *func_sig,
			 स्थिर काष्ठा btf_type *func_proto,
			 स्थिर काष्ठा btf_type *func, पूर्णांक pos, पूर्णांक size);

अटल पूर्णांक dump_prog_id_as_func_ptr(स्थिर काष्ठा btf_dumper *d,
				    स्थिर काष्ठा btf_type *func_proto,
				    __u32 prog_id)
अणु
	काष्ठा bpf_prog_info_linear *prog_info = शून्य;
	स्थिर काष्ठा btf_type *func_type;
	स्थिर अक्षर *prog_name = शून्य;
	काष्ठा bpf_func_info *finfo;
	काष्ठा btf *prog_btf = शून्य;
	काष्ठा bpf_prog_info *info;
	पूर्णांक prog_fd, func_sig_len;
	अक्षर prog_str[1024];

	/* Get the ptr's func_proto */
	func_sig_len = btf_dump_func(d->btf, prog_str, func_proto, शून्य, 0,
				     माप(prog_str));
	अगर (func_sig_len == -1)
		वापस -1;

	अगर (!prog_id)
		जाओ prपूर्णांक;

	/* Get the bpf_prog's name.  Obtain from func_info. */
	prog_fd = bpf_prog_get_fd_by_id(prog_id);
	अगर (prog_fd == -1)
		जाओ prपूर्णांक;

	prog_info = bpf_program__get_prog_info_linear(prog_fd,
						1UL << BPF_PROG_INFO_FUNC_INFO);
	बंद(prog_fd);
	अगर (IS_ERR(prog_info)) अणु
		prog_info = शून्य;
		जाओ prपूर्णांक;
	पूर्ण
	info = &prog_info->info;

	अगर (!info->btf_id || !info->nr_func_info ||
	    btf__get_from_id(info->btf_id, &prog_btf))
		जाओ prपूर्णांक;
	finfo = u64_to_ptr(info->func_info);
	func_type = btf__type_by_id(prog_btf, finfo->type_id);
	अगर (!func_type || !btf_is_func(func_type))
		जाओ prपूर्णांक;

	prog_name = btf__name_by_offset(prog_btf, func_type->name_off);

prपूर्णांक:
	अगर (!prog_id)
		snम_लिखो(&prog_str[func_sig_len],
			 माप(prog_str) - func_sig_len, " 0");
	अन्यथा अगर (prog_name)
		snम_लिखो(&prog_str[func_sig_len],
			 माप(prog_str) - func_sig_len,
			 " %s/prog_id:%u", prog_name, prog_id);
	अन्यथा
		snम_लिखो(&prog_str[func_sig_len],
			 माप(prog_str) - func_sig_len,
			 " <unknown_prog_name>/prog_id:%u", prog_id);

	prog_str[माप(prog_str) - 1] = '\0';
	jsonw_string(d->jw, prog_str);
	btf__मुक्त(prog_btf);
	मुक्त(prog_info);
	वापस 0;
पूर्ण

अटल व्योम btf_dumper_ptr(स्थिर काष्ठा btf_dumper *d,
			   स्थिर काष्ठा btf_type *t,
			   स्थिर व्योम *data)
अणु
	अचिन्हित दीर्घ value = *(अचिन्हित दीर्घ *)data;
	स्थिर काष्ठा btf_type *ptr_type;
	__s32 ptr_type_id;

	अगर (!d->prog_id_as_func_ptr || value > UINT32_MAX)
		जाओ prपूर्णांक_ptr_value;

	ptr_type_id = btf__resolve_type(d->btf, t->type);
	अगर (ptr_type_id < 0)
		जाओ prपूर्णांक_ptr_value;
	ptr_type = btf__type_by_id(d->btf, ptr_type_id);
	अगर (!ptr_type || !btf_is_func_proto(ptr_type))
		जाओ prपूर्णांक_ptr_value;

	अगर (!dump_prog_id_as_func_ptr(d, ptr_type, value))
		वापस;

prपूर्णांक_ptr_value:
	अगर (d->is_plain_text)
		jsonw_म_लिखो(d->jw, "%p", (व्योम *)value);
	अन्यथा
		jsonw_म_लिखो(d->jw, "%lu", value);
पूर्ण

अटल पूर्णांक btf_dumper_modअगरier(स्थिर काष्ठा btf_dumper *d, __u32 type_id,
			       __u8 bit_offset, स्थिर व्योम *data)
अणु
	पूर्णांक actual_type_id;

	actual_type_id = btf__resolve_type(d->btf, type_id);
	अगर (actual_type_id < 0)
		वापस actual_type_id;

	वापस btf_dumper_करो_type(d, actual_type_id, bit_offset, data);
पूर्ण

अटल पूर्णांक btf_dumper_क्रमागत(स्थिर काष्ठा btf_dumper *d,
			    स्थिर काष्ठा btf_type *t,
			    स्थिर व्योम *data)
अणु
	स्थिर काष्ठा btf_क्रमागत *क्रमागतs = btf_क्रमागत(t);
	__s64 value;
	__u16 i;

	चयन (t->size) अणु
	हाल 8:
		value = *(__s64 *)data;
		अवरोध;
	हाल 4:
		value = *(__s32 *)data;
		अवरोध;
	हाल 2:
		value = *(__s16 *)data;
		अवरोध;
	हाल 1:
		value = *(__s8 *)data;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < btf_vlen(t); i++) अणु
		अगर (value == क्रमागतs[i].val) अणु
			jsonw_string(d->jw,
				     btf__name_by_offset(d->btf,
							 क्रमागतs[i].name_off));
			वापस 0;
		पूर्ण
	पूर्ण

	jsonw_पूर्णांक(d->jw, value);
	वापस 0;
पूर्ण

अटल bool is_str_array(स्थिर काष्ठा btf *btf, स्थिर काष्ठा btf_array *arr,
			 स्थिर अक्षर *s)
अणु
	स्थिर काष्ठा btf_type *elem_type;
	स्थिर अक्षर *end_s;

	अगर (!arr->nelems)
		वापस false;

	elem_type = btf__type_by_id(btf, arr->type);
	/* Not skipping प्रकार.  प्रकार to अक्षर करोes not count as
	 * a string now.
	 */
	जबतक (elem_type && btf_is_mod(elem_type))
		elem_type = btf__type_by_id(btf, elem_type->type);

	अगर (!elem_type || !btf_is_पूर्णांक(elem_type) || elem_type->size != 1)
		वापस false;

	अगर (btf_पूर्णांक_encoding(elem_type) != BTF_INT_CHAR &&
	    म_भेद("char", btf__name_by_offset(btf, elem_type->name_off)))
		वापस false;

	end_s = s + arr->nelems;
	जबतक (s < end_s) अणु
		अगर (!*s)
			वापस true;
		अगर (*s <= 0x1f || *s >= 0x7f)
			वापस false;
		s++;
	पूर्ण

	/* '\0' is not found */
	वापस false;
पूर्ण

अटल पूर्णांक btf_dumper_array(स्थिर काष्ठा btf_dumper *d, __u32 type_id,
			    स्थिर व्योम *data)
अणु
	स्थिर काष्ठा btf_type *t = btf__type_by_id(d->btf, type_id);
	काष्ठा btf_array *arr = (काष्ठा btf_array *)(t + 1);
	दीर्घ दीर्घ elem_size;
	पूर्णांक ret = 0;
	__u32 i;

	अगर (is_str_array(d->btf, arr, data)) अणु
		jsonw_string(d->jw, data);
		वापस 0;
	पूर्ण

	elem_size = btf__resolve_size(d->btf, arr->type);
	अगर (elem_size < 0)
		वापस elem_size;

	jsonw_start_array(d->jw);
	क्रम (i = 0; i < arr->nelems; i++) अणु
		ret = btf_dumper_करो_type(d, arr->type, 0,
					 data + i * elem_size);
		अगर (ret)
			अवरोध;
	पूर्ण

	jsonw_end_array(d->jw);
	वापस ret;
पूर्ण

अटल व्योम btf_पूर्णांक128_prपूर्णांक(json_ग_लिखोr_t *jw, स्थिर व्योम *data,
			     bool is_plain_text)
अणु
	/* data poपूर्णांकs to a __पूर्णांक128 number.
	 * Suppose
	 *     पूर्णांक128_num = *(__पूर्णांक128 *)data;
	 * The below क्रमmulas shows what upper_num and lower_num represents:
	 *     upper_num = पूर्णांक128_num >> 64;
	 *     lower_num = पूर्णांक128_num & 0xffffffffFFFFFFFFULL;
	 */
	__u64 upper_num, lower_num;

#अगर_घोषित __BIG_ENDIAN_BITFIELD
	upper_num = *(__u64 *)data;
	lower_num = *(__u64 *)(data + 8);
#अन्यथा
	upper_num = *(__u64 *)(data + 8);
	lower_num = *(__u64 *)data;
#पूर्ण_अगर

	अगर (is_plain_text) अणु
		अगर (upper_num == 0)
			jsonw_म_लिखो(jw, "0x%llx", lower_num);
		अन्यथा
			jsonw_म_लिखो(jw, "0x%llx%016llx", upper_num, lower_num);
	पूर्ण अन्यथा अणु
		अगर (upper_num == 0)
			jsonw_म_लिखो(jw, "\"0x%llx\"", lower_num);
		अन्यथा
			jsonw_म_लिखो(jw, "\"0x%llx%016llx\"", upper_num, lower_num);
	पूर्ण
पूर्ण

अटल व्योम btf_पूर्णांक128_shअगरt(__u64 *prपूर्णांक_num, __u16 left_shअगरt_bits,
			     __u16 right_shअगरt_bits)
अणु
	__u64 upper_num, lower_num;

#अगर_घोषित __BIG_ENDIAN_BITFIELD
	upper_num = prपूर्णांक_num[0];
	lower_num = prपूर्णांक_num[1];
#अन्यथा
	upper_num = prपूर्णांक_num[1];
	lower_num = prपूर्णांक_num[0];
#पूर्ण_अगर

	/* shake out un-needed bits by shअगरt/or operations */
	अगर (left_shअगरt_bits >= 64) अणु
		upper_num = lower_num << (left_shअगरt_bits - 64);
		lower_num = 0;
	पूर्ण अन्यथा अणु
		upper_num = (upper_num << left_shअगरt_bits) |
			    (lower_num >> (64 - left_shअगरt_bits));
		lower_num = lower_num << left_shअगरt_bits;
	पूर्ण

	अगर (right_shअगरt_bits >= 64) अणु
		lower_num = upper_num >> (right_shअगरt_bits - 64);
		upper_num = 0;
	पूर्ण अन्यथा अणु
		lower_num = (lower_num >> right_shअगरt_bits) |
			    (upper_num << (64 - right_shअगरt_bits));
		upper_num = upper_num >> right_shअगरt_bits;
	पूर्ण

#अगर_घोषित __BIG_ENDIAN_BITFIELD
	prपूर्णांक_num[0] = upper_num;
	prपूर्णांक_num[1] = lower_num;
#अन्यथा
	prपूर्णांक_num[0] = lower_num;
	prपूर्णांक_num[1] = upper_num;
#पूर्ण_अगर
पूर्ण

अटल व्योम btf_dumper_bitfield(__u32 nr_bits, __u8 bit_offset,
				स्थिर व्योम *data, json_ग_लिखोr_t *jw,
				bool is_plain_text)
अणु
	पूर्णांक left_shअगरt_bits, right_shअगरt_bits;
	__u64 prपूर्णांक_num[2] = अणुपूर्ण;
	पूर्णांक bytes_to_copy;
	पूर्णांक bits_to_copy;

	bits_to_copy = bit_offset + nr_bits;
	bytes_to_copy = BITS_ROUNDUP_BYTES(bits_to_copy);

	स_नकल(prपूर्णांक_num, data, bytes_to_copy);
#अगर defined(__BIG_ENDIAN_BITFIELD)
	left_shअगरt_bits = bit_offset;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	left_shअगरt_bits = 128 - bits_to_copy;
#अन्यथा
#त्रुटि neither big nor little endian
#पूर्ण_अगर
	right_shअगरt_bits = 128 - nr_bits;

	btf_पूर्णांक128_shअगरt(prपूर्णांक_num, left_shअगरt_bits, right_shअगरt_bits);
	btf_पूर्णांक128_prपूर्णांक(jw, prपूर्णांक_num, is_plain_text);
पूर्ण


अटल व्योम btf_dumper_पूर्णांक_bits(__u32 पूर्णांक_type, __u8 bit_offset,
				स्थिर व्योम *data, json_ग_लिखोr_t *jw,
				bool is_plain_text)
अणु
	पूर्णांक nr_bits = BTF_INT_BITS(पूर्णांक_type);
	पूर्णांक total_bits_offset;

	/* bits_offset is at most 7.
	 * BTF_INT_OFFSET() cannot exceed 128 bits.
	 */
	total_bits_offset = bit_offset + BTF_INT_OFFSET(पूर्णांक_type);
	data += BITS_ROUNDDOWN_BYTES(total_bits_offset);
	bit_offset = BITS_PER_BYTE_MASKED(total_bits_offset);
	btf_dumper_bitfield(nr_bits, bit_offset, data, jw,
			    is_plain_text);
पूर्ण

अटल पूर्णांक btf_dumper_पूर्णांक(स्थिर काष्ठा btf_type *t, __u8 bit_offset,
			  स्थिर व्योम *data, json_ग_लिखोr_t *jw,
			  bool is_plain_text)
अणु
	__u32 *पूर्णांक_type;
	__u32 nr_bits;

	पूर्णांक_type = (__u32 *)(t + 1);
	nr_bits = BTF_INT_BITS(*पूर्णांक_type);
	/* अगर this is bit field */
	अगर (bit_offset || BTF_INT_OFFSET(*पूर्णांक_type) ||
	    BITS_PER_BYTE_MASKED(nr_bits)) अणु
		btf_dumper_पूर्णांक_bits(*पूर्णांक_type, bit_offset, data, jw,
				    is_plain_text);
		वापस 0;
	पूर्ण

	अगर (nr_bits == 128) अणु
		btf_पूर्णांक128_prपूर्णांक(jw, data, is_plain_text);
		वापस 0;
	पूर्ण

	चयन (BTF_INT_ENCODING(*पूर्णांक_type)) अणु
	हाल 0:
		अगर (BTF_INT_BITS(*पूर्णांक_type) == 64)
			jsonw_म_लिखो(jw, "%llu", *(__u64 *)data);
		अन्यथा अगर (BTF_INT_BITS(*पूर्णांक_type) == 32)
			jsonw_म_लिखो(jw, "%u", *(__u32 *)data);
		अन्यथा अगर (BTF_INT_BITS(*पूर्णांक_type) == 16)
			jsonw_म_लिखो(jw, "%hu", *(__u16 *)data);
		अन्यथा अगर (BTF_INT_BITS(*पूर्णांक_type) == 8)
			jsonw_म_लिखो(jw, "%hhu", *(__u8 *)data);
		अन्यथा
			btf_dumper_पूर्णांक_bits(*पूर्णांक_type, bit_offset, data, jw,
					    is_plain_text);
		अवरोध;
	हाल BTF_INT_SIGNED:
		अगर (BTF_INT_BITS(*पूर्णांक_type) == 64)
			jsonw_म_लिखो(jw, "%lld", *(दीर्घ दीर्घ *)data);
		अन्यथा अगर (BTF_INT_BITS(*पूर्णांक_type) == 32)
			jsonw_म_लिखो(jw, "%d", *(पूर्णांक *)data);
		अन्यथा अगर (BTF_INT_BITS(*पूर्णांक_type) == 16)
			jsonw_म_लिखो(jw, "%hd", *(लघु *)data);
		अन्यथा अगर (BTF_INT_BITS(*पूर्णांक_type) == 8)
			jsonw_म_लिखो(jw, "%hhd", *(अक्षर *)data);
		अन्यथा
			btf_dumper_पूर्णांक_bits(*पूर्णांक_type, bit_offset, data, jw,
					    is_plain_text);
		अवरोध;
	हाल BTF_INT_CHAR:
		अगर (है_छाप(*(अक्षर *)data))
			jsonw_म_लिखो(jw, "\"%c\"", *(अक्षर *)data);
		अन्यथा
			अगर (is_plain_text)
				jsonw_म_लिखो(jw, "0x%hhx", *(अक्षर *)data);
			अन्यथा
				jsonw_म_लिखो(jw, "\"\\u00%02hhx\"",
					     *(अक्षर *)data);
		अवरोध;
	हाल BTF_INT_BOOL:
		jsonw_bool(jw, *(पूर्णांक *)data);
		अवरोध;
	शेष:
		/* shouldn't happen */
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक btf_dumper_काष्ठा(स्थिर काष्ठा btf_dumper *d, __u32 type_id,
			     स्थिर व्योम *data)
अणु
	स्थिर काष्ठा btf_type *t;
	काष्ठा btf_member *m;
	स्थिर व्योम *data_off;
	पूर्णांक kind_flag;
	पूर्णांक ret = 0;
	पूर्णांक i, vlen;

	t = btf__type_by_id(d->btf, type_id);
	अगर (!t)
		वापस -EINVAL;

	kind_flag = BTF_INFO_KFLAG(t->info);
	vlen = BTF_INFO_VLEN(t->info);
	jsonw_start_object(d->jw);
	m = (काष्ठा btf_member *)(t + 1);

	क्रम (i = 0; i < vlen; i++) अणु
		__u32 bit_offset = m[i].offset;
		__u32 bitfield_size = 0;

		अगर (kind_flag) अणु
			bitfield_size = BTF_MEMBER_BITFIELD_SIZE(bit_offset);
			bit_offset = BTF_MEMBER_BIT_OFFSET(bit_offset);
		पूर्ण

		jsonw_name(d->jw, btf__name_by_offset(d->btf, m[i].name_off));
		data_off = data + BITS_ROUNDDOWN_BYTES(bit_offset);
		अगर (bitfield_size) अणु
			btf_dumper_bitfield(bitfield_size,
					    BITS_PER_BYTE_MASKED(bit_offset),
					    data_off, d->jw, d->is_plain_text);
		पूर्ण अन्यथा अणु
			ret = btf_dumper_करो_type(d, m[i].type,
						 BITS_PER_BYTE_MASKED(bit_offset),
						 data_off);
			अगर (ret)
				अवरोध;
		पूर्ण
	पूर्ण

	jsonw_end_object(d->jw);

	वापस ret;
पूर्ण

अटल पूर्णांक btf_dumper_var(स्थिर काष्ठा btf_dumper *d, __u32 type_id,
			  __u8 bit_offset, स्थिर व्योम *data)
अणु
	स्थिर काष्ठा btf_type *t = btf__type_by_id(d->btf, type_id);
	पूर्णांक ret;

	jsonw_start_object(d->jw);
	jsonw_name(d->jw, btf__name_by_offset(d->btf, t->name_off));
	ret = btf_dumper_करो_type(d, t->type, bit_offset, data);
	jsonw_end_object(d->jw);

	वापस ret;
पूर्ण

अटल पूर्णांक btf_dumper_datasec(स्थिर काष्ठा btf_dumper *d, __u32 type_id,
			      स्थिर व्योम *data)
अणु
	काष्ठा btf_var_secinfo *vsi;
	स्थिर काष्ठा btf_type *t;
	पूर्णांक ret = 0, i, vlen;

	t = btf__type_by_id(d->btf, type_id);
	अगर (!t)
		वापस -EINVAL;

	vlen = BTF_INFO_VLEN(t->info);
	vsi = (काष्ठा btf_var_secinfo *)(t + 1);

	jsonw_start_object(d->jw);
	jsonw_name(d->jw, btf__name_by_offset(d->btf, t->name_off));
	jsonw_start_array(d->jw);
	क्रम (i = 0; i < vlen; i++) अणु
		ret = btf_dumper_करो_type(d, vsi[i].type, 0, data + vsi[i].offset);
		अगर (ret)
			अवरोध;
	पूर्ण
	jsonw_end_array(d->jw);
	jsonw_end_object(d->jw);

	वापस ret;
पूर्ण

अटल पूर्णांक btf_dumper_करो_type(स्थिर काष्ठा btf_dumper *d, __u32 type_id,
			      __u8 bit_offset, स्थिर व्योम *data)
अणु
	स्थिर काष्ठा btf_type *t = btf__type_by_id(d->btf, type_id);

	चयन (BTF_INFO_KIND(t->info)) अणु
	हाल BTF_KIND_INT:
		वापस btf_dumper_पूर्णांक(t, bit_offset, data, d->jw,
				     d->is_plain_text);
	हाल BTF_KIND_STRUCT:
	हाल BTF_KIND_UNION:
		वापस btf_dumper_काष्ठा(d, type_id, data);
	हाल BTF_KIND_ARRAY:
		वापस btf_dumper_array(d, type_id, data);
	हाल BTF_KIND_ENUM:
		वापस btf_dumper_क्रमागत(d, t, data);
	हाल BTF_KIND_PTR:
		btf_dumper_ptr(d, t, data);
		वापस 0;
	हाल BTF_KIND_UNKN:
		jsonw_म_लिखो(d->jw, "(unknown)");
		वापस 0;
	हाल BTF_KIND_FWD:
		/* map key or value can't be क्रमward */
		jsonw_म_लिखो(d->jw, "(fwd-kind-invalid)");
		वापस -EINVAL;
	हाल BTF_KIND_TYPEDEF:
	हाल BTF_KIND_VOLATILE:
	हाल BTF_KIND_CONST:
	हाल BTF_KIND_RESTRICT:
		वापस btf_dumper_modअगरier(d, type_id, bit_offset, data);
	हाल BTF_KIND_VAR:
		वापस btf_dumper_var(d, type_id, bit_offset, data);
	हाल BTF_KIND_DATASEC:
		वापस btf_dumper_datasec(d, type_id, data);
	शेष:
		jsonw_म_लिखो(d->jw, "(unsupported-kind");
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक btf_dumper_type(स्थिर काष्ठा btf_dumper *d, __u32 type_id,
		    स्थिर व्योम *data)
अणु
	वापस btf_dumper_करो_type(d, type_id, 0, data);
पूर्ण

#घोषणा BTF_PRINT_ARG(...)						\
	करो अणु								\
		pos += snम_लिखो(func_sig + pos, size - pos,		\
				__VA_ARGS__);				\
		अगर (pos >= size)					\
			वापस -1;					\
	पूर्ण जबतक (0)
#घोषणा BTF_PRINT_TYPE(type)					\
	करो अणु								\
		pos = __btf_dumper_type_only(btf, type, func_sig,	\
					     pos, size);		\
		अगर (pos == -1)						\
			वापस -1;					\
	पूर्ण जबतक (0)

अटल पूर्णांक __btf_dumper_type_only(स्थिर काष्ठा btf *btf, __u32 type_id,
				  अक्षर *func_sig, पूर्णांक pos, पूर्णांक size)
अणु
	स्थिर काष्ठा btf_type *proto_type;
	स्थिर काष्ठा btf_array *array;
	स्थिर काष्ठा btf_var *var;
	स्थिर काष्ठा btf_type *t;

	अगर (!type_id) अणु
		BTF_PRINT_ARG("void ");
		वापस pos;
	पूर्ण

	t = btf__type_by_id(btf, type_id);

	चयन (BTF_INFO_KIND(t->info)) अणु
	हाल BTF_KIND_INT:
	हाल BTF_KIND_TYPEDEF:
	हाल BTF_KIND_FLOAT:
		BTF_PRINT_ARG("%s ", btf__name_by_offset(btf, t->name_off));
		अवरोध;
	हाल BTF_KIND_STRUCT:
		BTF_PRINT_ARG("struct %s ",
			      btf__name_by_offset(btf, t->name_off));
		अवरोध;
	हाल BTF_KIND_UNION:
		BTF_PRINT_ARG("union %s ",
			      btf__name_by_offset(btf, t->name_off));
		अवरोध;
	हाल BTF_KIND_ENUM:
		BTF_PRINT_ARG("enum %s ",
			      btf__name_by_offset(btf, t->name_off));
		अवरोध;
	हाल BTF_KIND_ARRAY:
		array = (काष्ठा btf_array *)(t + 1);
		BTF_PRINT_TYPE(array->type);
		BTF_PRINT_ARG("[%d]", array->nelems);
		अवरोध;
	हाल BTF_KIND_PTR:
		BTF_PRINT_TYPE(t->type);
		BTF_PRINT_ARG("* ");
		अवरोध;
	हाल BTF_KIND_FWD:
		BTF_PRINT_ARG("%s %s ",
			      BTF_INFO_KFLAG(t->info) ? "union" : "struct",
			      btf__name_by_offset(btf, t->name_off));
		अवरोध;
	हाल BTF_KIND_VOLATILE:
		BTF_PRINT_ARG("volatile ");
		BTF_PRINT_TYPE(t->type);
		अवरोध;
	हाल BTF_KIND_CONST:
		BTF_PRINT_ARG("const ");
		BTF_PRINT_TYPE(t->type);
		अवरोध;
	हाल BTF_KIND_RESTRICT:
		BTF_PRINT_ARG("restrict ");
		BTF_PRINT_TYPE(t->type);
		अवरोध;
	हाल BTF_KIND_FUNC_PROTO:
		pos = btf_dump_func(btf, func_sig, t, शून्य, pos, size);
		अगर (pos == -1)
			वापस -1;
		अवरोध;
	हाल BTF_KIND_FUNC:
		proto_type = btf__type_by_id(btf, t->type);
		pos = btf_dump_func(btf, func_sig, proto_type, t, pos, size);
		अगर (pos == -1)
			वापस -1;
		अवरोध;
	हाल BTF_KIND_VAR:
		var = (काष्ठा btf_var *)(t + 1);
		अगर (var->linkage == BTF_VAR_STATIC)
			BTF_PRINT_ARG("static ");
		BTF_PRINT_TYPE(t->type);
		BTF_PRINT_ARG(" %s",
			      btf__name_by_offset(btf, t->name_off));
		अवरोध;
	हाल BTF_KIND_DATASEC:
		BTF_PRINT_ARG("section (\"%s\") ",
			      btf__name_by_offset(btf, t->name_off));
		अवरोध;
	हाल BTF_KIND_UNKN:
	शेष:
		वापस -1;
	पूर्ण

	वापस pos;
पूर्ण

अटल पूर्णांक btf_dump_func(स्थिर काष्ठा btf *btf, अक्षर *func_sig,
			 स्थिर काष्ठा btf_type *func_proto,
			 स्थिर काष्ठा btf_type *func, पूर्णांक pos, पूर्णांक size)
अणु
	पूर्णांक i, vlen;

	BTF_PRINT_TYPE(func_proto->type);
	अगर (func)
		BTF_PRINT_ARG("%s(", btf__name_by_offset(btf, func->name_off));
	अन्यथा
		BTF_PRINT_ARG("(");
	vlen = BTF_INFO_VLEN(func_proto->info);
	क्रम (i = 0; i < vlen; i++) अणु
		काष्ठा btf_param *arg = &((काष्ठा btf_param *)(func_proto + 1))[i];

		अगर (i)
			BTF_PRINT_ARG(", ");
		अगर (arg->type) अणु
			BTF_PRINT_TYPE(arg->type);
			अगर (arg->name_off)
				BTF_PRINT_ARG("%s",
					      btf__name_by_offset(btf, arg->name_off));
			अन्यथा अगर (pos && func_sig[pos - 1] == ' ')
				/* Remove unnecessary space क्रम
				 * FUNC_PROTO that करोes not have
				 * arg->name_off
				 */
				func_sig[--pos] = '\0';
		पूर्ण अन्यथा अणु
			BTF_PRINT_ARG("...");
		पूर्ण
	पूर्ण
	BTF_PRINT_ARG(")");

	वापस pos;
पूर्ण

व्योम btf_dumper_type_only(स्थिर काष्ठा btf *btf, __u32 type_id, अक्षर *func_sig,
			  पूर्णांक size)
अणु
	पूर्णांक err;

	func_sig[0] = '\0';
	अगर (!btf)
		वापस;

	err = __btf_dumper_type_only(btf, type_id, func_sig, 0, size);
	अगर (err < 0)
		func_sig[0] = '\0';
पूर्ण

अटल स्थिर अक्षर *ltrim(स्थिर अक्षर *s)
अणु
	जबतक (है_खाली(*s))
		s++;

	वापस s;
पूर्ण

व्योम btf_dump_linfo_plain(स्थिर काष्ठा btf *btf,
			  स्थिर काष्ठा bpf_line_info *linfo,
			  स्थिर अक्षर *prefix, bool linum)
अणु
	स्थिर अक्षर *line = btf__name_by_offset(btf, linfo->line_off);

	अगर (!line)
		वापस;
	line = ltrim(line);

	अगर (!prefix)
		prefix = "";

	अगर (linum) अणु
		स्थिर अक्षर *file = btf__name_by_offset(btf, linfo->file_name_off);

		/* More क्रमgiving on file because linum option is
		 * expected to provide more info than the alपढ़ोy
		 * available src line.
		 */
		अगर (!file)
			file = "";

		म_लिखो("%s%s [file:%s line_num:%u line_col:%u]\n",
		       prefix, line, file,
		       BPF_LINE_INFO_LINE_NUM(linfo->line_col),
		       BPF_LINE_INFO_LINE_COL(linfo->line_col));
	पूर्ण अन्यथा अणु
		म_लिखो("%s%s\n", prefix, line);
	पूर्ण
पूर्ण

व्योम btf_dump_linfo_json(स्थिर काष्ठा btf *btf,
			 स्थिर काष्ठा bpf_line_info *linfo, bool linum)
अणु
	स्थिर अक्षर *line = btf__name_by_offset(btf, linfo->line_off);

	अगर (line)
		jsonw_string_field(json_wtr, "src", ltrim(line));

	अगर (linum) अणु
		स्थिर अक्षर *file = btf__name_by_offset(btf, linfo->file_name_off);

		अगर (file)
			jsonw_string_field(json_wtr, "file", file);

		अगर (BPF_LINE_INFO_LINE_NUM(linfo->line_col))
			jsonw_पूर्णांक_field(json_wtr, "line_num",
					BPF_LINE_INFO_LINE_NUM(linfo->line_col));

		अगर (BPF_LINE_INFO_LINE_COL(linfo->line_col))
			jsonw_पूर्णांक_field(json_wtr, "line_col",
					BPF_LINE_INFO_LINE_COL(linfo->line_col));
	पूर्ण
पूर्ण
