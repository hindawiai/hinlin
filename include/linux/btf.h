<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2018 Facebook */

#अगर_अघोषित _LINUX_BTF_H
#घोषणा _LINUX_BTF_H 1

#समावेश <linux/types.h>
#समावेश <uapi/linux/btf.h>
#समावेश <uapi/linux/bpf.h>

#घोषणा BTF_TYPE_EMIT(type) ((व्योम)(type *)0)
#घोषणा BTF_TYPE_EMIT_ENUM(क्रमागत_val) ((व्योम)क्रमागत_val)

काष्ठा btf;
काष्ठा btf_member;
काष्ठा btf_type;
जोड़ bpf_attr;
काष्ठा btf_show;

बाह्य स्थिर काष्ठा file_operations btf_fops;

व्योम btf_get(काष्ठा btf *btf);
व्योम btf_put(काष्ठा btf *btf);
पूर्णांक btf_new_fd(स्थिर जोड़ bpf_attr *attr);
काष्ठा btf *btf_get_by_fd(पूर्णांक fd);
पूर्णांक btf_get_info_by_fd(स्थिर काष्ठा btf *btf,
		       स्थिर जोड़ bpf_attr *attr,
		       जोड़ bpf_attr __user *uattr);
/* Figure out the size of a type_id.  If type_id is a modअगरier
 * (e.g. स्थिर), it will be resolved to find out the type with size.
 *
 * For example:
 * In describing "const void *",  type_id is "const" and "const"
 * refers to "void *".  The वापस type will be "void *".
 *
 * If type_id is a simple "int", then वापस type will be "int".
 *
 * @btf: काष्ठा btf object
 * @type_id: Find out the size of type_id. The type_id of the वापस
 *           type is set to *type_id.
 * @ret_size: It can be शून्य.  If not शून्य, the size of the वापस
 *            type is set to *ret_size.
 * Return: The btf_type (resolved to another type with size info अगर needed).
 *         शून्य is वापसed अगर type_id itself करोes not have size info
 *         (e.g. व्योम) or it cannot be resolved to another type that
 *         has size info.
 *         *type_id and *ret_size will not be changed in the
 *         शून्य वापस हाल.
 */
स्थिर काष्ठा btf_type *btf_type_id_size(स्थिर काष्ठा btf *btf,
					u32 *type_id,
					u32 *ret_size);

/*
 * Options to control show behaviour.
 *	- BTF_SHOW_COMPACT: no क्रमmatting around type inक्रमmation
 *	- BTF_SHOW_NONAME: no काष्ठा/जोड़ member names/types
 *	- BTF_SHOW_PTR_RAW: show raw (unobfuscated) poपूर्णांकer values;
 *	  equivalent to %px.
 *	- BTF_SHOW_ZERO: show zero-valued काष्ठा/जोड़ members; they
 *	  are not displayed by शेष
 *	- BTF_SHOW_UNSAFE: skip use of bpf_probe_पढ़ो() to safely पढ़ो
 *	  data beक्रमe displaying it.
 */
#घोषणा BTF_SHOW_COMPACT	BTF_F_COMPACT
#घोषणा BTF_SHOW_NONAME		BTF_F_NONAME
#घोषणा BTF_SHOW_PTR_RAW	BTF_F_PTR_RAW
#घोषणा BTF_SHOW_ZERO		BTF_F_ZERO
#घोषणा BTF_SHOW_UNSAFE		(1ULL << 4)

व्योम btf_type_seq_show(स्थिर काष्ठा btf *btf, u32 type_id, व्योम *obj,
		       काष्ठा seq_file *m);
पूर्णांक btf_type_seq_show_flags(स्थिर काष्ठा btf *btf, u32 type_id, व्योम *obj,
			    काष्ठा seq_file *m, u64 flags);

/*
 * Copy len bytes of string representation of obj of BTF type_id पूर्णांकo buf.
 *
 * @btf: काष्ठा btf object
 * @type_id: type id of type obj poपूर्णांकs to
 * @obj: poपूर्णांकer to typed data
 * @buf: buffer to ग_लिखो to
 * @len: maximum length to ग_लिखो to buf
 * @flags: show options (see above)
 *
 * Return: length that would have been/was copied as per snम_लिखो, or
 *	   negative error.
 */
पूर्णांक btf_type_snम_लिखो_show(स्थिर काष्ठा btf *btf, u32 type_id, व्योम *obj,
			   अक्षर *buf, पूर्णांक len, u64 flags);

पूर्णांक btf_get_fd_by_id(u32 id);
u32 btf_obj_id(स्थिर काष्ठा btf *btf);
bool btf_is_kernel(स्थिर काष्ठा btf *btf);
bool btf_is_module(स्थिर काष्ठा btf *btf);
काष्ठा module *btf_try_get_module(स्थिर काष्ठा btf *btf);
u32 btf_nr_types(स्थिर काष्ठा btf *btf);
bool btf_member_is_reg_पूर्णांक(स्थिर काष्ठा btf *btf, स्थिर काष्ठा btf_type *s,
			   स्थिर काष्ठा btf_member *m,
			   u32 expected_offset, u32 expected_size);
पूर्णांक btf_find_spin_lock(स्थिर काष्ठा btf *btf, स्थिर काष्ठा btf_type *t);
bool btf_type_is_व्योम(स्थिर काष्ठा btf_type *t);
s32 btf_find_by_name_kind(स्थिर काष्ठा btf *btf, स्थिर अक्षर *name, u8 kind);
स्थिर काष्ठा btf_type *btf_type_skip_modअगरiers(स्थिर काष्ठा btf *btf,
					       u32 id, u32 *res_id);
स्थिर काष्ठा btf_type *btf_type_resolve_ptr(स्थिर काष्ठा btf *btf,
					    u32 id, u32 *res_id);
स्थिर काष्ठा btf_type *btf_type_resolve_func_ptr(स्थिर काष्ठा btf *btf,
						 u32 id, u32 *res_id);
स्थिर काष्ठा btf_type *
btf_resolve_size(स्थिर काष्ठा btf *btf, स्थिर काष्ठा btf_type *type,
		 u32 *type_size);
स्थिर अक्षर *btf_type_str(स्थिर काष्ठा btf_type *t);

#घोषणा क्रम_each_member(i, काष्ठा_type, member)			\
	क्रम (i = 0, member = btf_type_member(काष्ठा_type);	\
	     i < btf_type_vlen(काष्ठा_type);			\
	     i++, member++)

#घोषणा क्रम_each_vsi(i, datasec_type, member)			\
	क्रम (i = 0, member = btf_type_var_secinfo(datasec_type);	\
	     i < btf_type_vlen(datasec_type);			\
	     i++, member++)

अटल अंतरभूत bool btf_type_is_ptr(स्थिर काष्ठा btf_type *t)
अणु
	वापस BTF_INFO_KIND(t->info) == BTF_KIND_PTR;
पूर्ण

अटल अंतरभूत bool btf_type_is_पूर्णांक(स्थिर काष्ठा btf_type *t)
अणु
	वापस BTF_INFO_KIND(t->info) == BTF_KIND_INT;
पूर्ण

अटल अंतरभूत bool btf_type_is_small_पूर्णांक(स्थिर काष्ठा btf_type *t)
अणु
	वापस btf_type_is_पूर्णांक(t) && t->size <= माप(u64);
पूर्ण

अटल अंतरभूत bool btf_type_is_क्रमागत(स्थिर काष्ठा btf_type *t)
अणु
	वापस BTF_INFO_KIND(t->info) == BTF_KIND_ENUM;
पूर्ण

अटल अंतरभूत bool btf_type_is_scalar(स्थिर काष्ठा btf_type *t)
अणु
	वापस btf_type_is_पूर्णांक(t) || btf_type_is_क्रमागत(t);
पूर्ण

अटल अंतरभूत bool btf_type_is_प्रकार(स्थिर काष्ठा btf_type *t)
अणु
	वापस BTF_INFO_KIND(t->info) == BTF_KIND_TYPEDEF;
पूर्ण

अटल अंतरभूत bool btf_type_is_func(स्थिर काष्ठा btf_type *t)
अणु
	वापस BTF_INFO_KIND(t->info) == BTF_KIND_FUNC;
पूर्ण

अटल अंतरभूत bool btf_type_is_func_proto(स्थिर काष्ठा btf_type *t)
अणु
	वापस BTF_INFO_KIND(t->info) == BTF_KIND_FUNC_PROTO;
पूर्ण

अटल अंतरभूत bool btf_type_is_var(स्थिर काष्ठा btf_type *t)
अणु
	वापस BTF_INFO_KIND(t->info) == BTF_KIND_VAR;
पूर्ण

/* जोड़ is only a special हाल of काष्ठा:
 * all its दुरत्व(member) == 0
 */
अटल अंतरभूत bool btf_type_is_काष्ठा(स्थिर काष्ठा btf_type *t)
अणु
	u8 kind = BTF_INFO_KIND(t->info);

	वापस kind == BTF_KIND_STRUCT || kind == BTF_KIND_UNION;
पूर्ण

अटल अंतरभूत u16 btf_type_vlen(स्थिर काष्ठा btf_type *t)
अणु
	वापस BTF_INFO_VLEN(t->info);
पूर्ण

अटल अंतरभूत u16 btf_func_linkage(स्थिर काष्ठा btf_type *t)
अणु
	वापस BTF_INFO_VLEN(t->info);
पूर्ण

अटल अंतरभूत bool btf_type_kflag(स्थिर काष्ठा btf_type *t)
अणु
	वापस BTF_INFO_KFLAG(t->info);
पूर्ण

अटल अंतरभूत u32 btf_member_bit_offset(स्थिर काष्ठा btf_type *काष्ठा_type,
					स्थिर काष्ठा btf_member *member)
अणु
	वापस btf_type_kflag(काष्ठा_type) ? BTF_MEMBER_BIT_OFFSET(member->offset)
					   : member->offset;
पूर्ण

अटल अंतरभूत u32 btf_member_bitfield_size(स्थिर काष्ठा btf_type *काष्ठा_type,
					   स्थिर काष्ठा btf_member *member)
अणु
	वापस btf_type_kflag(काष्ठा_type) ? BTF_MEMBER_BITFIELD_SIZE(member->offset)
					   : 0;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा btf_member *btf_type_member(स्थिर काष्ठा btf_type *t)
अणु
	वापस (स्थिर काष्ठा btf_member *)(t + 1);
पूर्ण

अटल अंतरभूत स्थिर काष्ठा btf_var_secinfo *btf_type_var_secinfo(
		स्थिर काष्ठा btf_type *t)
अणु
	वापस (स्थिर काष्ठा btf_var_secinfo *)(t + 1);
पूर्ण

#अगर_घोषित CONFIG_BPF_SYSCALL
काष्ठा bpf_prog;

स्थिर काष्ठा btf_type *btf_type_by_id(स्थिर काष्ठा btf *btf, u32 type_id);
स्थिर अक्षर *btf_name_by_offset(स्थिर काष्ठा btf *btf, u32 offset);
काष्ठा btf *btf_parse_vmlinux(व्योम);
काष्ठा btf *bpf_prog_get_target_btf(स्थिर काष्ठा bpf_prog *prog);
#अन्यथा
अटल अंतरभूत स्थिर काष्ठा btf_type *btf_type_by_id(स्थिर काष्ठा btf *btf,
						    u32 type_id)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत स्थिर अक्षर *btf_name_by_offset(स्थिर काष्ठा btf *btf,
					     u32 offset)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
