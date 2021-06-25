<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2018 Facebook */

#समावेश <uapi/linux/btf.h>
#समावेश <uapi/linux/bpf.h>
#समावेश <uapi/linux/bpf_perf_event.h>
#समावेश <uapi/linux/types.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/compiler.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/anon_inodes.h>
#समावेश <linux/file.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kernel.h>
#समावेश <linux/idr.h>
#समावेश <linux/sort.h>
#समावेश <linux/bpf_verअगरier.h>
#समावेश <linux/btf.h>
#समावेश <linux/btf_ids.h>
#समावेश <linux/skmsg.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/द्वा_खोज.h>
#समावेश <linux/kobject.h>
#समावेश <linux/sysfs.h>
#समावेश <net/sock.h>

/* BTF (BPF Type Format) is the meta data क्रमmat which describes
 * the data types of BPF program/map.  Hence, it basically focus
 * on the C programming language which the modern BPF is primary
 * using.
 *
 * ELF Section:
 * ~~~~~~~~~~~
 * The BTF data is stored under the ".BTF" ELF section
 *
 * काष्ठा btf_type:
 * ~~~~~~~~~~~~~~~
 * Each 'struct btf_type' object describes a C data type.
 * Depending on the type it is describing, a 'struct btf_type'
 * object may be followed by more data.  F.e.
 * To describe an array, 'struct btf_type' is followed by
 * 'struct btf_array'.
 *
 * 'struct btf_type' and any extra data following it are
 * 4 bytes aligned.
 *
 * Type section:
 * ~~~~~~~~~~~~~
 * The BTF type section contains a list of 'struct btf_type' objects.
 * Each one describes a C type.  Recall from the above section
 * that a 'struct btf_type' object could be immediately followed by extra
 * data in order to desribe some particular C types.
 *
 * type_id:
 * ~~~~~~~
 * Each btf_type object is identअगरied by a type_id.  The type_id
 * is implicitly implied by the location of the btf_type object in
 * the BTF type section.  The first one has type_id 1.  The second
 * one has type_id 2...etc.  Hence, an earlier btf_type has
 * a smaller type_id.
 *
 * A btf_type object may refer to another btf_type object by using
 * type_id (i.e. the "type" in the "struct btf_type").
 *
 * NOTE that we cannot assume any reference-order.
 * A btf_type object can refer to an earlier btf_type object
 * but it can also refer to a later btf_type object.
 *
 * For example, to describe "const void *".  A btf_type
 * object describing "const" may refer to another btf_type
 * object describing "void *".  This type-reference is करोne
 * by specअगरying type_id:
 *
 * [1] CONST (anon) type_id=2
 * [2] PTR (anon) type_id=0
 *
 * The above is the btf_verअगरier debug log:
 *   - Each line started with "[?]" is a btf_type object
 *   - [?] is the type_id of the btf_type object.
 *   - CONST/PTR is the BTF_KIND_XXX
 *   - "(anon)" is the name of the type.  It just
 *     happens that CONST and PTR has no name.
 *   - type_id=XXX is the 'u32 type' in btf_type
 *
 * NOTE: "void" has type_id 0
 *
 * String section:
 * ~~~~~~~~~~~~~~
 * The BTF string section contains the names used by the type section.
 * Each string is referred by an "offset" from the beginning of the
 * string section.
 *
 * Each string is '\0' terminated.
 *
 * The first अक्षरacter in the string section must be '\0'
 * which is used to mean 'anonymous'. Some btf_type may not
 * have a name.
 */

/* BTF verअगरication:
 *
 * To verअगरy BTF data, two passes are needed.
 *
 * Pass #1
 * ~~~~~~~
 * The first pass is to collect all btf_type objects to
 * an array: "btf->types".
 *
 * Depending on the C type that a btf_type is describing,
 * a btf_type may be followed by extra data.  We करोn't know
 * how many btf_type is there, and more importantly we करोn't
 * know where each btf_type is located in the type section.
 *
 * Without knowing the location of each type_id, most verअगरications
 * cannot be करोne.  e.g. an earlier btf_type may refer to a later
 * btf_type (recall the "const void *" above), so we cannot
 * check this type-reference in the first pass.
 *
 * In the first pass, it still करोes some verअगरications (e.g.
 * checking the name is a valid offset to the string section).
 *
 * Pass #2
 * ~~~~~~~
 * The मुख्य focus is to resolve a btf_type that is referring
 * to another type.
 *
 * We have to ensure the referring type:
 * 1) करोes exist in the BTF (i.e. in btf->types[])
 * 2) करोes not cause a loop:
 *	काष्ठा A अणु
 *		काष्ठा B b;
 *	पूर्ण;
 *
 *	काष्ठा B अणु
 *		काष्ठा A a;
 *	पूर्ण;
 *
 * btf_type_needs_resolve() decides अगर a btf_type needs
 * to be resolved.
 *
 * The needs_resolve type implements the "resolve()" ops which
 * essentially करोes a DFS and detects backedge.
 *
 * During resolve (or DFS), dअगरferent C types have dअगरferent
 * "RESOLVED" conditions.
 *
 * When resolving a BTF_KIND_STRUCT, we need to resolve all its
 * members because a member is always referring to another
 * type.  A काष्ठा's member can be treated as "RESOLVED" अगर
 * it is referring to a BTF_KIND_PTR.  Otherwise, the
 * following valid C काष्ठा would be rejected:
 *
 *	काष्ठा A अणु
 *		पूर्णांक m;
 *		काष्ठा A *a;
 *	पूर्ण;
 *
 * When resolving a BTF_KIND_PTR, it needs to keep resolving अगर
 * it is referring to another BTF_KIND_PTR.  Otherwise, we cannot
 * detect a poपूर्णांकer loop, e.g.:
 * BTF_KIND_CONST -> BTF_KIND_PTR -> BTF_KIND_CONST -> BTF_KIND_PTR +
 *                        ^                                         |
 *                        +-----------------------------------------+
 *
 */

#घोषणा BITS_PER_U128 (माप(u64) * BITS_PER_BYTE * 2)
#घोषणा BITS_PER_BYTE_MASK (BITS_PER_BYTE - 1)
#घोषणा BITS_PER_BYTE_MASKED(bits) ((bits) & BITS_PER_BYTE_MASK)
#घोषणा BITS_ROUNDDOWN_BYTES(bits) ((bits) >> 3)
#घोषणा BITS_ROUNDUP_BYTES(bits) \
	(BITS_ROUNDDOWN_BYTES(bits) + !!BITS_PER_BYTE_MASKED(bits))

#घोषणा BTF_INFO_MASK 0x9f00ffff
#घोषणा BTF_INT_MASK 0x0fffffff
#घोषणा BTF_TYPE_ID_VALID(type_id) ((type_id) <= BTF_MAX_TYPE)
#घोषणा BTF_STR_OFFSET_VALID(name_off) ((name_off) <= BTF_MAX_NAME_OFFSET)

/* 16MB क्रम 64k काष्ठाs and each has 16 members and
 * a few MB spaces क्रम the string section.
 * The hard limit is S32_MAX.
 */
#घोषणा BTF_MAX_SIZE (16 * 1024 * 1024)

#घोषणा क्रम_each_member_from(i, from, काष्ठा_type, member)		\
	क्रम (i = from, member = btf_type_member(काष्ठा_type) + from;	\
	     i < btf_type_vlen(काष्ठा_type);				\
	     i++, member++)

#घोषणा क्रम_each_vsi_from(i, from, काष्ठा_type, member)				\
	क्रम (i = from, member = btf_type_var_secinfo(काष्ठा_type) + from;	\
	     i < btf_type_vlen(काष्ठा_type);					\
	     i++, member++)

DEFINE_IDR(btf_idr);
DEFINE_SPINLOCK(btf_idr_lock);

काष्ठा btf अणु
	व्योम *data;
	काष्ठा btf_type **types;
	u32 *resolved_ids;
	u32 *resolved_sizes;
	स्थिर अक्षर *strings;
	व्योम *nohdr_data;
	काष्ठा btf_header hdr;
	u32 nr_types; /* includes VOID क्रम base BTF */
	u32 types_size;
	u32 data_size;
	refcount_t refcnt;
	u32 id;
	काष्ठा rcu_head rcu;

	/* split BTF support */
	काष्ठा btf *base_btf;
	u32 start_id; /* first type ID in this BTF (0 क्रम base BTF) */
	u32 start_str_off; /* first string offset (0 क्रम base BTF) */
	अक्षर name[MODULE_NAME_LEN];
	bool kernel_btf;
पूर्ण;

क्रमागत verअगरier_phase अणु
	CHECK_META,
	CHECK_TYPE,
पूर्ण;

काष्ठा resolve_vertex अणु
	स्थिर काष्ठा btf_type *t;
	u32 type_id;
	u16 next_member;
पूर्ण;

क्रमागत visit_state अणु
	NOT_VISITED,
	VISITED,
	RESOLVED,
पूर्ण;

क्रमागत resolve_mode अणु
	RESOLVE_TBD,	/* To Be Determined */
	RESOLVE_PTR,	/* Resolving क्रम Poपूर्णांकer */
	RESOLVE_STRUCT_OR_ARRAY,	/* Resolving क्रम काष्ठा/जोड़
					 * or array
					 */
पूर्ण;

#घोषणा MAX_RESOLVE_DEPTH 32

काष्ठा btf_sec_info अणु
	u32 off;
	u32 len;
पूर्ण;

काष्ठा btf_verअगरier_env अणु
	काष्ठा btf *btf;
	u8 *visit_states;
	काष्ठा resolve_vertex stack[MAX_RESOLVE_DEPTH];
	काष्ठा bpf_verअगरier_log log;
	u32 log_type_id;
	u32 top_stack;
	क्रमागत verअगरier_phase phase;
	क्रमागत resolve_mode resolve_mode;
पूर्ण;

अटल स्थिर अक्षर * स्थिर btf_kind_str[NR_BTF_KINDS] = अणु
	[BTF_KIND_UNKN]		= "UNKNOWN",
	[BTF_KIND_INT]		= "INT",
	[BTF_KIND_PTR]		= "PTR",
	[BTF_KIND_ARRAY]	= "ARRAY",
	[BTF_KIND_STRUCT]	= "STRUCT",
	[BTF_KIND_UNION]	= "UNION",
	[BTF_KIND_ENUM]		= "ENUM",
	[BTF_KIND_FWD]		= "FWD",
	[BTF_KIND_TYPEDEF]	= "TYPEDEF",
	[BTF_KIND_VOLATILE]	= "VOLATILE",
	[BTF_KIND_CONST]	= "CONST",
	[BTF_KIND_RESTRICT]	= "RESTRICT",
	[BTF_KIND_FUNC]		= "FUNC",
	[BTF_KIND_FUNC_PROTO]	= "FUNC_PROTO",
	[BTF_KIND_VAR]		= "VAR",
	[BTF_KIND_DATASEC]	= "DATASEC",
	[BTF_KIND_FLOAT]	= "FLOAT",
पूर्ण;

स्थिर अक्षर *btf_type_str(स्थिर काष्ठा btf_type *t)
अणु
	वापस btf_kind_str[BTF_INFO_KIND(t->info)];
पूर्ण

/* Chunk size we use in safe copy of data to be shown. */
#घोषणा BTF_SHOW_OBJ_SAFE_SIZE		32

/*
 * This is the maximum size of a base type value (equivalent to a
 * 128-bit पूर्णांक); अगर we are at the end of our safe buffer and have
 * less than 16 bytes space we can't be assured of being able
 * to copy the next type safely, so in such हालs we will initiate
 * a new copy.
 */
#घोषणा BTF_SHOW_OBJ_BASE_TYPE_SIZE	16

/* Type name size */
#घोषणा BTF_SHOW_NAME_SIZE		80

/*
 * Common data to all BTF show operations. Private show functions can add
 * their own data to a काष्ठाure containing a काष्ठा btf_show and consult it
 * in the show callback.  See btf_type_show() below.
 *
 * One challenge with showing nested data is we want to skip 0-valued
 * data, but in order to figure out whether a nested object is all zeros
 * we need to walk through it.  As a result, we need to make two passes
 * when handling काष्ठाs, जोड़s and arrays; the first path simply looks
 * क्रम nonzero data, जबतक the second actually करोes the display.  The first
 * pass is संकेतled by show->state.depth_check being set, and अगर we
 * encounter a non-zero value we set show->state.depth_to_show to
 * the depth at which we encountered it.  When we have completed the
 * first pass, we will know अगर anything needs to be displayed अगर
 * depth_to_show > depth.  See btf_[काष्ठा,array]_show() क्रम the
 * implementation of this.
 *
 * Another problem is we want to ensure the data क्रम display is safe to
 * access.  To support this, the anonymous "struct {} obj" tracks the data
 * object and our safe copy of it.  We copy portions of the data needed
 * to the object "copy" buffer, but because its size is limited to
 * BTF_SHOW_OBJ_COPY_LEN bytes, multiple copies may be required as we
 * traverse larger objects क्रम display.
 *
 * The various data type show functions all start with a call to
 * btf_show_start_type() which वापसs a poपूर्णांकer to the safe copy
 * of the data needed (or अगर BTF_SHOW_UNSAFE is specअगरied, to the
 * raw data itself).  btf_show_obj_safe() is responsible क्रम
 * using copy_from_kernel_nofault() to update the safe data अगर necessary
 * as we traverse the object's data.  skbuff-like semantics are
 * used:
 *
 * - obj.head poपूर्णांकs to the start of the toplevel object क्रम display
 * - obj.size is the size of the toplevel object
 * - obj.data poपूर्णांकs to the current poपूर्णांक in the original data at
 *   which our safe data starts.  obj.data will advance as we copy
 *   portions of the data.
 *
 * In most हालs a single copy will suffice, but larger data काष्ठाures
 * such as "struct task_struct" will require many copies.  The logic in
 * btf_show_obj_safe() handles the logic that determines अगर a new
 * copy_from_kernel_nofault() is needed.
 */
काष्ठा btf_show अणु
	u64 flags;
	व्योम *target;	/* target of show operation (seq file, buffer) */
	व्योम (*showfn)(काष्ठा btf_show *show, स्थिर अक्षर *fmt, बहु_सूची args);
	स्थिर काष्ठा btf *btf;
	/* below are used during iteration */
	काष्ठा अणु
		u8 depth;
		u8 depth_to_show;
		u8 depth_check;
		u8 array_member:1,
		   array_terminated:1;
		u16 array_encoding;
		u32 type_id;
		पूर्णांक status;			/* non-zero क्रम error */
		स्थिर काष्ठा btf_type *type;
		स्थिर काष्ठा btf_member *member;
		अक्षर name[BTF_SHOW_NAME_SIZE];	/* space क्रम member name/type */
	पूर्ण state;
	काष्ठा अणु
		u32 size;
		व्योम *head;
		व्योम *data;
		u8 safe[BTF_SHOW_OBJ_SAFE_SIZE];
	पूर्ण obj;
पूर्ण;

काष्ठा btf_kind_operations अणु
	s32 (*check_meta)(काष्ठा btf_verअगरier_env *env,
			  स्थिर काष्ठा btf_type *t,
			  u32 meta_left);
	पूर्णांक (*resolve)(काष्ठा btf_verअगरier_env *env,
		       स्थिर काष्ठा resolve_vertex *v);
	पूर्णांक (*check_member)(काष्ठा btf_verअगरier_env *env,
			    स्थिर काष्ठा btf_type *काष्ठा_type,
			    स्थिर काष्ठा btf_member *member,
			    स्थिर काष्ठा btf_type *member_type);
	पूर्णांक (*check_kflag_member)(काष्ठा btf_verअगरier_env *env,
				  स्थिर काष्ठा btf_type *काष्ठा_type,
				  स्थिर काष्ठा btf_member *member,
				  स्थिर काष्ठा btf_type *member_type);
	व्योम (*log_details)(काष्ठा btf_verअगरier_env *env,
			    स्थिर काष्ठा btf_type *t);
	व्योम (*show)(स्थिर काष्ठा btf *btf, स्थिर काष्ठा btf_type *t,
			 u32 type_id, व्योम *data, u8 bits_offsets,
			 काष्ठा btf_show *show);
पूर्ण;

अटल स्थिर काष्ठा btf_kind_operations * स्थिर kind_ops[NR_BTF_KINDS];
अटल काष्ठा btf_type btf_व्योम;

अटल पूर्णांक btf_resolve(काष्ठा btf_verअगरier_env *env,
		       स्थिर काष्ठा btf_type *t, u32 type_id);

अटल bool btf_type_is_modअगरier(स्थिर काष्ठा btf_type *t)
अणु
	/* Some of them is not strictly a C modअगरier
	 * but they are grouped पूर्णांकo the same bucket
	 * क्रम BTF concern:
	 *   A type (t) that refers to another
	 *   type through t->type AND its size cannot
	 *   be determined without following the t->type.
	 *
	 * ptr करोes not fall पूर्णांकo this bucket
	 * because its size is always माप(व्योम *).
	 */
	चयन (BTF_INFO_KIND(t->info)) अणु
	हाल BTF_KIND_TYPEDEF:
	हाल BTF_KIND_VOLATILE:
	हाल BTF_KIND_CONST:
	हाल BTF_KIND_RESTRICT:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

bool btf_type_is_व्योम(स्थिर काष्ठा btf_type *t)
अणु
	वापस t == &btf_व्योम;
पूर्ण

अटल bool btf_type_is_fwd(स्थिर काष्ठा btf_type *t)
अणु
	वापस BTF_INFO_KIND(t->info) == BTF_KIND_FWD;
पूर्ण

अटल bool btf_type_nosize(स्थिर काष्ठा btf_type *t)
अणु
	वापस btf_type_is_व्योम(t) || btf_type_is_fwd(t) ||
	       btf_type_is_func(t) || btf_type_is_func_proto(t);
पूर्ण

अटल bool btf_type_nosize_or_null(स्थिर काष्ठा btf_type *t)
अणु
	वापस !t || btf_type_nosize(t);
पूर्ण

अटल bool __btf_type_is_काष्ठा(स्थिर काष्ठा btf_type *t)
अणु
	वापस BTF_INFO_KIND(t->info) == BTF_KIND_STRUCT;
पूर्ण

अटल bool btf_type_is_array(स्थिर काष्ठा btf_type *t)
अणु
	वापस BTF_INFO_KIND(t->info) == BTF_KIND_ARRAY;
पूर्ण

अटल bool btf_type_is_datasec(स्थिर काष्ठा btf_type *t)
अणु
	वापस BTF_INFO_KIND(t->info) == BTF_KIND_DATASEC;
पूर्ण

u32 btf_nr_types(स्थिर काष्ठा btf *btf)
अणु
	u32 total = 0;

	जबतक (btf) अणु
		total += btf->nr_types;
		btf = btf->base_btf;
	पूर्ण

	वापस total;
पूर्ण

s32 btf_find_by_name_kind(स्थिर काष्ठा btf *btf, स्थिर अक्षर *name, u8 kind)
अणु
	स्थिर काष्ठा btf_type *t;
	स्थिर अक्षर *tname;
	u32 i, total;

	total = btf_nr_types(btf);
	क्रम (i = 1; i < total; i++) अणु
		t = btf_type_by_id(btf, i);
		अगर (BTF_INFO_KIND(t->info) != kind)
			जारी;

		tname = btf_name_by_offset(btf, t->name_off);
		अगर (!म_भेद(tname, name))
			वापस i;
	पूर्ण

	वापस -ENOENT;
पूर्ण

स्थिर काष्ठा btf_type *btf_type_skip_modअगरiers(स्थिर काष्ठा btf *btf,
					       u32 id, u32 *res_id)
अणु
	स्थिर काष्ठा btf_type *t = btf_type_by_id(btf, id);

	जबतक (btf_type_is_modअगरier(t)) अणु
		id = t->type;
		t = btf_type_by_id(btf, t->type);
	पूर्ण

	अगर (res_id)
		*res_id = id;

	वापस t;
पूर्ण

स्थिर काष्ठा btf_type *btf_type_resolve_ptr(स्थिर काष्ठा btf *btf,
					    u32 id, u32 *res_id)
अणु
	स्थिर काष्ठा btf_type *t;

	t = btf_type_skip_modअगरiers(btf, id, शून्य);
	अगर (!btf_type_is_ptr(t))
		वापस शून्य;

	वापस btf_type_skip_modअगरiers(btf, t->type, res_id);
पूर्ण

स्थिर काष्ठा btf_type *btf_type_resolve_func_ptr(स्थिर काष्ठा btf *btf,
						 u32 id, u32 *res_id)
अणु
	स्थिर काष्ठा btf_type *ptype;

	ptype = btf_type_resolve_ptr(btf, id, res_id);
	अगर (ptype && btf_type_is_func_proto(ptype))
		वापस ptype;

	वापस शून्य;
पूर्ण

/* Types that act only as a source, not sink or पूर्णांकermediate
 * type when resolving.
 */
अटल bool btf_type_is_resolve_source_only(स्थिर काष्ठा btf_type *t)
अणु
	वापस btf_type_is_var(t) ||
	       btf_type_is_datasec(t);
पूर्ण

/* What types need to be resolved?
 *
 * btf_type_is_modअगरier() is an obvious one.
 *
 * btf_type_is_काष्ठा() because its member refers to
 * another type (through member->type).
 *
 * btf_type_is_var() because the variable refers to
 * another type. btf_type_is_datasec() holds multiple
 * btf_type_is_var() types that need resolving.
 *
 * btf_type_is_array() because its element (array->type)
 * refers to another type.  Array can be thought of a
 * special हाल of काष्ठा जबतक array just has the same
 * member-type repeated by array->nelems of बार.
 */
अटल bool btf_type_needs_resolve(स्थिर काष्ठा btf_type *t)
अणु
	वापस btf_type_is_modअगरier(t) ||
	       btf_type_is_ptr(t) ||
	       btf_type_is_काष्ठा(t) ||
	       btf_type_is_array(t) ||
	       btf_type_is_var(t) ||
	       btf_type_is_datasec(t);
पूर्ण

/* t->size can be used */
अटल bool btf_type_has_size(स्थिर काष्ठा btf_type *t)
अणु
	चयन (BTF_INFO_KIND(t->info)) अणु
	हाल BTF_KIND_INT:
	हाल BTF_KIND_STRUCT:
	हाल BTF_KIND_UNION:
	हाल BTF_KIND_ENUM:
	हाल BTF_KIND_DATASEC:
	हाल BTF_KIND_FLOAT:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल स्थिर अक्षर *btf_पूर्णांक_encoding_str(u8 encoding)
अणु
	अगर (encoding == 0)
		वापस "(none)";
	अन्यथा अगर (encoding == BTF_INT_SIGNED)
		वापस "SIGNED";
	अन्यथा अगर (encoding == BTF_INT_CHAR)
		वापस "CHAR";
	अन्यथा अगर (encoding == BTF_INT_BOOL)
		वापस "BOOL";
	अन्यथा
		वापस "UNKN";
पूर्ण

अटल u32 btf_type_पूर्णांक(स्थिर काष्ठा btf_type *t)
अणु
	वापस *(u32 *)(t + 1);
पूर्ण

अटल स्थिर काष्ठा btf_array *btf_type_array(स्थिर काष्ठा btf_type *t)
अणु
	वापस (स्थिर काष्ठा btf_array *)(t + 1);
पूर्ण

अटल स्थिर काष्ठा btf_क्रमागत *btf_type_क्रमागत(स्थिर काष्ठा btf_type *t)
अणु
	वापस (स्थिर काष्ठा btf_क्रमागत *)(t + 1);
पूर्ण

अटल स्थिर काष्ठा btf_var *btf_type_var(स्थिर काष्ठा btf_type *t)
अणु
	वापस (स्थिर काष्ठा btf_var *)(t + 1);
पूर्ण

अटल स्थिर काष्ठा btf_kind_operations *btf_type_ops(स्थिर काष्ठा btf_type *t)
अणु
	वापस kind_ops[BTF_INFO_KIND(t->info)];
पूर्ण

अटल bool btf_name_offset_valid(स्थिर काष्ठा btf *btf, u32 offset)
अणु
	अगर (!BTF_STR_OFFSET_VALID(offset))
		वापस false;

	जबतक (offset < btf->start_str_off)
		btf = btf->base_btf;

	offset -= btf->start_str_off;
	वापस offset < btf->hdr.str_len;
पूर्ण

अटल bool __btf_name_अक्षर_ok(अक्षर c, bool first, bool करोt_ok)
अणु
	अगर ((first ? !है_अक्षर(c) :
		     !है_अक्षर_अंक(c)) &&
	    c != '_' &&
	    ((c == '.' && !करोt_ok) ||
	      c != '.'))
		वापस false;
	वापस true;
पूर्ण

अटल स्थिर अक्षर *btf_str_by_offset(स्थिर काष्ठा btf *btf, u32 offset)
अणु
	जबतक (offset < btf->start_str_off)
		btf = btf->base_btf;

	offset -= btf->start_str_off;
	अगर (offset < btf->hdr.str_len)
		वापस &btf->strings[offset];

	वापस शून्य;
पूर्ण

अटल bool __btf_name_valid(स्थिर काष्ठा btf *btf, u32 offset, bool करोt_ok)
अणु
	/* offset must be valid */
	स्थिर अक्षर *src = btf_str_by_offset(btf, offset);
	स्थिर अक्षर *src_limit;

	अगर (!__btf_name_अक्षर_ok(*src, true, करोt_ok))
		वापस false;

	/* set a limit on identअगरier length */
	src_limit = src + KSYM_NAME_LEN;
	src++;
	जबतक (*src && src < src_limit) अणु
		अगर (!__btf_name_अक्षर_ok(*src, false, करोt_ok))
			वापस false;
		src++;
	पूर्ण

	वापस !*src;
पूर्ण

/* Only C-style identअगरier is permitted. This can be relaxed अगर
 * necessary.
 */
अटल bool btf_name_valid_identअगरier(स्थिर काष्ठा btf *btf, u32 offset)
अणु
	वापस __btf_name_valid(btf, offset, false);
पूर्ण

अटल bool btf_name_valid_section(स्थिर काष्ठा btf *btf, u32 offset)
अणु
	वापस __btf_name_valid(btf, offset, true);
पूर्ण

अटल स्थिर अक्षर *__btf_name_by_offset(स्थिर काष्ठा btf *btf, u32 offset)
अणु
	स्थिर अक्षर *name;

	अगर (!offset)
		वापस "(anon)";

	name = btf_str_by_offset(btf, offset);
	वापस name ?: "(invalid-name-offset)";
पूर्ण

स्थिर अक्षर *btf_name_by_offset(स्थिर काष्ठा btf *btf, u32 offset)
अणु
	वापस btf_str_by_offset(btf, offset);
पूर्ण

स्थिर काष्ठा btf_type *btf_type_by_id(स्थिर काष्ठा btf *btf, u32 type_id)
अणु
	जबतक (type_id < btf->start_id)
		btf = btf->base_btf;

	type_id -= btf->start_id;
	अगर (type_id >= btf->nr_types)
		वापस शून्य;
	वापस btf->types[type_id];
पूर्ण

/*
 * Regular पूर्णांक is not a bit field and it must be either
 * u8/u16/u32/u64 or __पूर्णांक128.
 */
अटल bool btf_type_पूर्णांक_is_regular(स्थिर काष्ठा btf_type *t)
अणु
	u8 nr_bits, nr_bytes;
	u32 पूर्णांक_data;

	पूर्णांक_data = btf_type_पूर्णांक(t);
	nr_bits = BTF_INT_BITS(पूर्णांक_data);
	nr_bytes = BITS_ROUNDUP_BYTES(nr_bits);
	अगर (BITS_PER_BYTE_MASKED(nr_bits) ||
	    BTF_INT_OFFSET(पूर्णांक_data) ||
	    (nr_bytes != माप(u8) && nr_bytes != माप(u16) &&
	     nr_bytes != माप(u32) && nr_bytes != माप(u64) &&
	     nr_bytes != (2 * माप(u64)))) अणु
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * Check that given काष्ठा member is a regular पूर्णांक with expected
 * offset and size.
 */
bool btf_member_is_reg_पूर्णांक(स्थिर काष्ठा btf *btf, स्थिर काष्ठा btf_type *s,
			   स्थिर काष्ठा btf_member *m,
			   u32 expected_offset, u32 expected_size)
अणु
	स्थिर काष्ठा btf_type *t;
	u32 id, पूर्णांक_data;
	u8 nr_bits;

	id = m->type;
	t = btf_type_id_size(btf, &id, शून्य);
	अगर (!t || !btf_type_is_पूर्णांक(t))
		वापस false;

	पूर्णांक_data = btf_type_पूर्णांक(t);
	nr_bits = BTF_INT_BITS(पूर्णांक_data);
	अगर (btf_type_kflag(s)) अणु
		u32 bitfield_size = BTF_MEMBER_BITFIELD_SIZE(m->offset);
		u32 bit_offset = BTF_MEMBER_BIT_OFFSET(m->offset);

		/* अगर kflag set, पूर्णांक should be a regular पूर्णांक and
		 * bit offset should be at byte boundary.
		 */
		वापस !bitfield_size &&
		       BITS_ROUNDUP_BYTES(bit_offset) == expected_offset &&
		       BITS_ROUNDUP_BYTES(nr_bits) == expected_size;
	पूर्ण

	अगर (BTF_INT_OFFSET(पूर्णांक_data) ||
	    BITS_PER_BYTE_MASKED(m->offset) ||
	    BITS_ROUNDUP_BYTES(m->offset) != expected_offset ||
	    BITS_PER_BYTE_MASKED(nr_bits) ||
	    BITS_ROUNDUP_BYTES(nr_bits) != expected_size)
		वापस false;

	वापस true;
पूर्ण

/* Similar to btf_type_skip_modअगरiers() but करोes not skip प्रकारs. */
अटल स्थिर काष्ठा btf_type *btf_type_skip_qualअगरiers(स्थिर काष्ठा btf *btf,
						       u32 id)
अणु
	स्थिर काष्ठा btf_type *t = btf_type_by_id(btf, id);

	जबतक (btf_type_is_modअगरier(t) &&
	       BTF_INFO_KIND(t->info) != BTF_KIND_TYPEDEF) अणु
		t = btf_type_by_id(btf, t->type);
	पूर्ण

	वापस t;
पूर्ण

#घोषणा BTF_SHOW_MAX_ITER	10

#घोषणा BTF_KIND_BIT(kind)	(1ULL << kind)

/*
 * Populate show->state.name with type name inक्रमmation.
 * Format of type name is
 *
 * [.member_name = ] (type_name)
 */
अटल स्थिर अक्षर *btf_show_name(काष्ठा btf_show *show)
अणु
	/* BTF_MAX_ITER array suffixes "[]" */
	स्थिर अक्षर *array_suffixes = "[][][][][][][][][][]";
	स्थिर अक्षर *array_suffix = &array_suffixes[म_माप(array_suffixes)];
	/* BTF_MAX_ITER poपूर्णांकer suffixes "*" */
	स्थिर अक्षर *ptr_suffixes = "**********";
	स्थिर अक्षर *ptr_suffix = &ptr_suffixes[म_माप(ptr_suffixes)];
	स्थिर अक्षर *name = शून्य, *prefix = "", *parens = "";
	स्थिर काष्ठा btf_member *m = show->state.member;
	स्थिर काष्ठा btf_type *t = show->state.type;
	स्थिर काष्ठा btf_array *array;
	u32 id = show->state.type_id;
	स्थिर अक्षर *member = शून्य;
	bool show_member = false;
	u64 kinds = 0;
	पूर्णांक i;

	show->state.name[0] = '\0';

	/*
	 * Don't show type name if we're showing an array member;
	 * in that हाल we show the array type so करोn't need to repeat
	 * ourselves क्रम each member.
	 */
	अगर (show->state.array_member)
		वापस "";

	/* Retrieve member name, अगर any. */
	अगर (m) अणु
		member = btf_name_by_offset(show->btf, m->name_off);
		show_member = म_माप(member) > 0;
		id = m->type;
	पूर्ण

	/*
	 * Start with type_id, as we have resolved the काष्ठा btf_type *
	 * via btf_modअगरier_show() past the parent प्रकार to the child
	 * काष्ठा, पूर्णांक etc it is defined as.  In such हालs, the type_id
	 * still represents the starting type जबतक the काष्ठा btf_type *
	 * in our show->state poपूर्णांकs at the resolved type of the प्रकार.
	 */
	t = btf_type_by_id(show->btf, id);
	अगर (!t)
		वापस "";

	/*
	 * The goal here is to build up the right number of poपूर्णांकer and
	 * array suffixes जबतक ensuring the type name क्रम a प्रकार
	 * is represented.  Aदीर्घ the way we accumulate a list of
	 * BTF kinds we have encountered, since these will inक्रमm later
	 * display; क्रम example, poपूर्णांकer types will not require an
	 * खोलोing "{" क्रम काष्ठा, we will just display the poपूर्णांकer value.
	 *
	 * We also want to accumulate the right number of poपूर्णांकer or array
	 * indices in the क्रमmat string जबतक iterating until we get to
	 * the प्रकार/poपूर्णांकee/array member target type.
	 *
	 * We start by poपूर्णांकing at the end of poपूर्णांकer and array suffix
	 * strings; as we accumulate poपूर्णांकers and arrays we move the poपूर्णांकer
	 * or array string backwards so it will show the expected number of
	 * '*' or '[]' क्रम the type.  BTF_SHOW_MAX_ITER of nesting of poपूर्णांकers
	 * and/or arrays and प्रकारs are supported as a precaution.
	 *
	 * We also want to get प्रकार name जबतक proceeding to resolve
	 * type it poपूर्णांकs to so that we can add parentheses अगर it is a
	 * "typedef struct" etc.
	 */
	क्रम (i = 0; i < BTF_SHOW_MAX_ITER; i++) अणु

		चयन (BTF_INFO_KIND(t->info)) अणु
		हाल BTF_KIND_TYPEDEF:
			अगर (!name)
				name = btf_name_by_offset(show->btf,
							       t->name_off);
			kinds |= BTF_KIND_BIT(BTF_KIND_TYPEDEF);
			id = t->type;
			अवरोध;
		हाल BTF_KIND_ARRAY:
			kinds |= BTF_KIND_BIT(BTF_KIND_ARRAY);
			parens = "[";
			अगर (!t)
				वापस "";
			array = btf_type_array(t);
			अगर (array_suffix > array_suffixes)
				array_suffix -= 2;
			id = array->type;
			अवरोध;
		हाल BTF_KIND_PTR:
			kinds |= BTF_KIND_BIT(BTF_KIND_PTR);
			अगर (ptr_suffix > ptr_suffixes)
				ptr_suffix -= 1;
			id = t->type;
			अवरोध;
		शेष:
			id = 0;
			अवरोध;
		पूर्ण
		अगर (!id)
			अवरोध;
		t = btf_type_skip_qualअगरiers(show->btf, id);
	पूर्ण
	/* We may not be able to represent this type; bail to be safe */
	अगर (i == BTF_SHOW_MAX_ITER)
		वापस "";

	अगर (!name)
		name = btf_name_by_offset(show->btf, t->name_off);

	चयन (BTF_INFO_KIND(t->info)) अणु
	हाल BTF_KIND_STRUCT:
	हाल BTF_KIND_UNION:
		prefix = BTF_INFO_KIND(t->info) == BTF_KIND_STRUCT ?
			 "struct" : "union";
		/* अगर it's an array of काष्ठा/जोड़, parens is alपढ़ोy set */
		अगर (!(kinds & (BTF_KIND_BIT(BTF_KIND_ARRAY))))
			parens = "{";
		अवरोध;
	हाल BTF_KIND_ENUM:
		prefix = "enum";
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* poपूर्णांकer करोes not require parens */
	अगर (kinds & BTF_KIND_BIT(BTF_KIND_PTR))
		parens = "";
	/* प्रकार करोes not require काष्ठा/जोड़/क्रमागत prefix */
	अगर (kinds & BTF_KIND_BIT(BTF_KIND_TYPEDEF))
		prefix = "";

	अगर (!name)
		name = "";

	/* Even अगर we करोn't want type name info, we want parentheses etc */
	अगर (show->flags & BTF_SHOW_NONAME)
		snम_लिखो(show->state.name, माप(show->state.name), "%s",
			 parens);
	अन्यथा
		snम_लिखो(show->state.name, माप(show->state.name),
			 "%s%s%s(%s%s%s%s%s%s)%s",
			 /* first 3 strings comprise ".member = " */
			 show_member ? "." : "",
			 show_member ? member : "",
			 show_member ? " = " : "",
			 /* ...next is our prefix (काष्ठा, क्रमागत, etc) */
			 prefix,
			 म_माप(prefix) > 0 && म_माप(name) > 0 ? " " : "",
			 /* ...this is the type name itself */
			 name,
			 /* ...suffixed by the appropriate '*', '[]' suffixes */
			 म_माप(ptr_suffix) > 0 ? " " : "", ptr_suffix,
			 array_suffix, parens);

	वापस show->state.name;
पूर्ण

अटल स्थिर अक्षर *__btf_show_indent(काष्ठा btf_show *show)
अणु
	स्थिर अक्षर *indents = "                                ";
	स्थिर अक्षर *indent = &indents[म_माप(indents)];

	अगर ((indent - show->state.depth) >= indents)
		वापस indent - show->state.depth;
	वापस indents;
पूर्ण

अटल स्थिर अक्षर *btf_show_indent(काष्ठा btf_show *show)
अणु
	वापस show->flags & BTF_SHOW_COMPACT ? "" : __btf_show_indent(show);
पूर्ण

अटल स्थिर अक्षर *btf_show_newline(काष्ठा btf_show *show)
अणु
	वापस show->flags & BTF_SHOW_COMPACT ? "" : "\n";
पूर्ण

अटल स्थिर अक्षर *btf_show_delim(काष्ठा btf_show *show)
अणु
	अगर (show->state.depth == 0)
		वापस "";

	अगर ((show->flags & BTF_SHOW_COMPACT) && show->state.type &&
		BTF_INFO_KIND(show->state.type->info) == BTF_KIND_UNION)
		वापस "|";

	वापस ",";
पूर्ण

__म_लिखो(2, 3) अटल व्योम btf_show(काष्ठा btf_show *show, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;

	अगर (!show->state.depth_check) अणु
		बहु_शुरू(args, fmt);
		show->showfn(show, fmt, args);
		बहु_पूर्ण(args);
	पूर्ण
पूर्ण

/* Macros are used here as btf_show_type_value[s]() prepends and appends
 * क्रमmat specअगरiers to the क्रमmat specअगरier passed in; these करो the work of
 * adding indentation, delimiters etc जबतक the caller simply has to specअगरy
 * the type value(s) in the क्रमmat specअगरier + value(s).
 */
#घोषणा btf_show_type_value(show, fmt, value)				       \
	करो अणु								       \
		अगर ((value) != 0 || (show->flags & BTF_SHOW_ZERO) ||	       \
		    show->state.depth == 0) अणु				       \
			btf_show(show, "%s%s" fmt "%s%s",		       \
				 btf_show_indent(show),			       \
				 btf_show_name(show),			       \
				 value, btf_show_delim(show),		       \
				 btf_show_newline(show));		       \
			अगर (show->state.depth > show->state.depth_to_show)     \
				show->state.depth_to_show = show->state.depth; \
		पूर्ण							       \
	पूर्ण जबतक (0)

#घोषणा btf_show_type_values(show, fmt, ...)				       \
	करो अणु								       \
		btf_show(show, "%s%s" fmt "%s%s", btf_show_indent(show),       \
			 btf_show_name(show),				       \
			 __VA_ARGS__, btf_show_delim(show),		       \
			 btf_show_newline(show));			       \
		अगर (show->state.depth > show->state.depth_to_show)	       \
			show->state.depth_to_show = show->state.depth;	       \
	पूर्ण जबतक (0)

/* How much is left to copy to safe buffer after @data? */
अटल पूर्णांक btf_show_obj_size_left(काष्ठा btf_show *show, व्योम *data)
अणु
	वापस show->obj.head + show->obj.size - data;
पूर्ण

/* Is object poपूर्णांकed to by @data of @size alपढ़ोy copied to our safe buffer? */
अटल bool btf_show_obj_is_safe(काष्ठा btf_show *show, व्योम *data, पूर्णांक size)
अणु
	वापस data >= show->obj.data &&
	       (data + size) < (show->obj.data + BTF_SHOW_OBJ_SAFE_SIZE);
पूर्ण

/*
 * If object poपूर्णांकed to by @data of @size falls within our safe buffer, वापस
 * the equivalent poपूर्णांकer to the same safe data.  Assumes
 * copy_from_kernel_nofault() has alपढ़ोy happened and our safe buffer is
 * populated.
 */
अटल व्योम *__btf_show_obj_safe(काष्ठा btf_show *show, व्योम *data, पूर्णांक size)
अणु
	अगर (btf_show_obj_is_safe(show, data, size))
		वापस show->obj.safe + (data - show->obj.data);
	वापस शून्य;
पूर्ण

/*
 * Return a safe-to-access version of data poपूर्णांकed to by @data.
 * We करो this by copying the relevant amount of inक्रमmation
 * to the काष्ठा btf_show obj.safe buffer using copy_from_kernel_nofault().
 *
 * If BTF_SHOW_UNSAFE is specअगरied, just वापस data as-is; no
 * safe copy is needed.
 *
 * Otherwise we need to determine अगर we have the required amount
 * of data (determined by the @data poपूर्णांकer and the size of the
 * largest base type we can encounter (represented by
 * BTF_SHOW_OBJ_BASE_TYPE_SIZE). Having that much data ensures
 * that we will be able to prपूर्णांक some of the current object,
 * and अगर more is needed a copy will be triggered.
 * Some objects such as काष्ठाs will not fit पूर्णांकo the buffer;
 * in such हालs additional copies when we iterate over their
 * members may be needed.
 *
 * btf_show_obj_safe() is used to वापस a safe buffer क्रम
 * btf_show_start_type(); this ensures that as we recurse पूर्णांकo
 * nested types we always have safe data क्रम the given type.
 * This approach is somewhat wasteful; it's possible क्रम example
 * that when iterating over a large जोड़ we'll end up copying the
 * same data repeatedly, but the goal is safety not perक्रमmance.
 * We use stack data as opposed to per-CPU buffers because the
 * iteration over a type can take some समय, and preemption handling
 * would greatly complicate use of the safe buffer.
 */
अटल व्योम *btf_show_obj_safe(काष्ठा btf_show *show,
			       स्थिर काष्ठा btf_type *t,
			       व्योम *data)
अणु
	स्थिर काष्ठा btf_type *rt;
	पूर्णांक size_left, size;
	व्योम *safe = शून्य;

	अगर (show->flags & BTF_SHOW_UNSAFE)
		वापस data;

	rt = btf_resolve_size(show->btf, t, &size);
	अगर (IS_ERR(rt)) अणु
		show->state.status = PTR_ERR(rt);
		वापस शून्य;
	पूर्ण

	/*
	 * Is this toplevel object? If so, set total object size and
	 * initialize poपूर्णांकers.  Otherwise check अगर we still fall within
	 * our safe object data.
	 */
	अगर (show->state.depth == 0) अणु
		show->obj.size = size;
		show->obj.head = data;
	पूर्ण अन्यथा अणु
		/*
		 * If the size of the current object is > our reमुख्यing
		 * safe buffer we _may_ need to करो a new copy.  However
		 * consider the हाल of a nested काष्ठा; it's size pushes
		 * us over the safe buffer limit, but showing any inभागidual
		 * काष्ठा members करोes not.  In such हालs, we करोn't need
		 * to initiate a fresh copy yet; however we definitely need
		 * at least BTF_SHOW_OBJ_BASE_TYPE_SIZE bytes left
		 * in our buffer, regardless of the current object size.
		 * The logic here is that as we resolve types we will
		 * hit a base type at some poपूर्णांक, and we need to be sure
		 * the next chunk of data is safely available to display
		 * that type info safely.  We cannot rely on the size of
		 * the current object here because it may be much larger
		 * than our current buffer (e.g. task_काष्ठा is 8k).
		 * All we want to करो here is ensure that we can prपूर्णांक the
		 * next basic type, which we can अगर either
		 * - the current type size is within the safe buffer; or
		 * - at least BTF_SHOW_OBJ_BASE_TYPE_SIZE bytes are left in
		 *   the safe buffer.
		 */
		safe = __btf_show_obj_safe(show, data,
					   min(size,
					       BTF_SHOW_OBJ_BASE_TYPE_SIZE));
	पूर्ण

	/*
	 * We need a new copy to our safe object, either because we haven't
	 * yet copied and are पूर्णांकializing safe data, or because the data
	 * we want falls outside the boundaries of the safe object.
	 */
	अगर (!safe) अणु
		size_left = btf_show_obj_size_left(show, data);
		अगर (size_left > BTF_SHOW_OBJ_SAFE_SIZE)
			size_left = BTF_SHOW_OBJ_SAFE_SIZE;
		show->state.status = copy_from_kernel_nofault(show->obj.safe,
							      data, size_left);
		अगर (!show->state.status) अणु
			show->obj.data = data;
			safe = show->obj.safe;
		पूर्ण
	पूर्ण

	वापस safe;
पूर्ण

/*
 * Set the type we are starting to show and वापस a safe data poपूर्णांकer
 * to be used क्रम showing the associated data.
 */
अटल व्योम *btf_show_start_type(काष्ठा btf_show *show,
				 स्थिर काष्ठा btf_type *t,
				 u32 type_id, व्योम *data)
अणु
	show->state.type = t;
	show->state.type_id = type_id;
	show->state.name[0] = '\0';

	वापस btf_show_obj_safe(show, t, data);
पूर्ण

अटल व्योम btf_show_end_type(काष्ठा btf_show *show)
अणु
	show->state.type = शून्य;
	show->state.type_id = 0;
	show->state.name[0] = '\0';
पूर्ण

अटल व्योम *btf_show_start_aggr_type(काष्ठा btf_show *show,
				      स्थिर काष्ठा btf_type *t,
				      u32 type_id, व्योम *data)
अणु
	व्योम *safe_data = btf_show_start_type(show, t, type_id, data);

	अगर (!safe_data)
		वापस safe_data;

	btf_show(show, "%s%s%s", btf_show_indent(show),
		 btf_show_name(show),
		 btf_show_newline(show));
	show->state.depth++;
	वापस safe_data;
पूर्ण

अटल व्योम btf_show_end_aggr_type(काष्ठा btf_show *show,
				   स्थिर अक्षर *suffix)
अणु
	show->state.depth--;
	btf_show(show, "%s%s%s%s", btf_show_indent(show), suffix,
		 btf_show_delim(show), btf_show_newline(show));
	btf_show_end_type(show);
पूर्ण

अटल व्योम btf_show_start_member(काष्ठा btf_show *show,
				  स्थिर काष्ठा btf_member *m)
अणु
	show->state.member = m;
पूर्ण

अटल व्योम btf_show_start_array_member(काष्ठा btf_show *show)
अणु
	show->state.array_member = 1;
	btf_show_start_member(show, शून्य);
पूर्ण

अटल व्योम btf_show_end_member(काष्ठा btf_show *show)
अणु
	show->state.member = शून्य;
पूर्ण

अटल व्योम btf_show_end_array_member(काष्ठा btf_show *show)
अणु
	show->state.array_member = 0;
	btf_show_end_member(show);
पूर्ण

अटल व्योम *btf_show_start_array_type(काष्ठा btf_show *show,
				       स्थिर काष्ठा btf_type *t,
				       u32 type_id,
				       u16 array_encoding,
				       व्योम *data)
अणु
	show->state.array_encoding = array_encoding;
	show->state.array_terminated = 0;
	वापस btf_show_start_aggr_type(show, t, type_id, data);
पूर्ण

अटल व्योम btf_show_end_array_type(काष्ठा btf_show *show)
अणु
	show->state.array_encoding = 0;
	show->state.array_terminated = 0;
	btf_show_end_aggr_type(show, "]");
पूर्ण

अटल व्योम *btf_show_start_काष्ठा_type(काष्ठा btf_show *show,
					स्थिर काष्ठा btf_type *t,
					u32 type_id,
					व्योम *data)
अणु
	वापस btf_show_start_aggr_type(show, t, type_id, data);
पूर्ण

अटल व्योम btf_show_end_काष्ठा_type(काष्ठा btf_show *show)
अणु
	btf_show_end_aggr_type(show, "}");
पूर्ण

__म_लिखो(2, 3) अटल व्योम __btf_verअगरier_log(काष्ठा bpf_verअगरier_log *log,
					      स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	bpf_verअगरier_vlog(log, fmt, args);
	बहु_पूर्ण(args);
पूर्ण

__म_लिखो(2, 3) अटल व्योम btf_verअगरier_log(काष्ठा btf_verअगरier_env *env,
					    स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा bpf_verअगरier_log *log = &env->log;
	बहु_सूची args;

	अगर (!bpf_verअगरier_log_needed(log))
		वापस;

	बहु_शुरू(args, fmt);
	bpf_verअगरier_vlog(log, fmt, args);
	बहु_पूर्ण(args);
पूर्ण

__म_लिखो(4, 5) अटल व्योम __btf_verअगरier_log_type(काष्ठा btf_verअगरier_env *env,
						   स्थिर काष्ठा btf_type *t,
						   bool log_details,
						   स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा bpf_verअगरier_log *log = &env->log;
	u8 kind = BTF_INFO_KIND(t->info);
	काष्ठा btf *btf = env->btf;
	बहु_सूची args;

	अगर (!bpf_verअगरier_log_needed(log))
		वापस;

	/* btf verअगरier prपूर्णांकs all types it is processing via
	 * btf_verअगरier_log_type(..., fmt = शून्य).
	 * Skip those prपूर्णांकs क्रम in-kernel BTF verअगरication.
	 */
	अगर (log->level == BPF_LOG_KERNEL && !fmt)
		वापस;

	__btf_verअगरier_log(log, "[%u] %s %s%s",
			   env->log_type_id,
			   btf_kind_str[kind],
			   __btf_name_by_offset(btf, t->name_off),
			   log_details ? " " : "");

	अगर (log_details)
		btf_type_ops(t)->log_details(env, t);

	अगर (fmt && *fmt) अणु
		__btf_verअगरier_log(log, " ");
		बहु_शुरू(args, fmt);
		bpf_verअगरier_vlog(log, fmt, args);
		बहु_पूर्ण(args);
	पूर्ण

	__btf_verअगरier_log(log, "\n");
पूर्ण

#घोषणा btf_verअगरier_log_type(env, t, ...) \
	__btf_verअगरier_log_type((env), (t), true, __VA_ARGS__)
#घोषणा btf_verअगरier_log_basic(env, t, ...) \
	__btf_verअगरier_log_type((env), (t), false, __VA_ARGS__)

__म_लिखो(4, 5)
अटल व्योम btf_verअगरier_log_member(काष्ठा btf_verअगरier_env *env,
				    स्थिर काष्ठा btf_type *काष्ठा_type,
				    स्थिर काष्ठा btf_member *member,
				    स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा bpf_verअगरier_log *log = &env->log;
	काष्ठा btf *btf = env->btf;
	बहु_सूची args;

	अगर (!bpf_verअगरier_log_needed(log))
		वापस;

	अगर (log->level == BPF_LOG_KERNEL && !fmt)
		वापस;
	/* The CHECK_META phase alपढ़ोy did a btf dump.
	 *
	 * If member is logged again, it must hit an error in
	 * parsing this member.  It is useful to prपूर्णांक out which
	 * काष्ठा this member beदीर्घs to.
	 */
	अगर (env->phase != CHECK_META)
		btf_verअगरier_log_type(env, काष्ठा_type, शून्य);

	अगर (btf_type_kflag(काष्ठा_type))
		__btf_verअगरier_log(log,
				   "\t%s type_id=%u bitfield_size=%u bits_offset=%u",
				   __btf_name_by_offset(btf, member->name_off),
				   member->type,
				   BTF_MEMBER_BITFIELD_SIZE(member->offset),
				   BTF_MEMBER_BIT_OFFSET(member->offset));
	अन्यथा
		__btf_verअगरier_log(log, "\t%s type_id=%u bits_offset=%u",
				   __btf_name_by_offset(btf, member->name_off),
				   member->type, member->offset);

	अगर (fmt && *fmt) अणु
		__btf_verअगरier_log(log, " ");
		बहु_शुरू(args, fmt);
		bpf_verअगरier_vlog(log, fmt, args);
		बहु_पूर्ण(args);
	पूर्ण

	__btf_verअगरier_log(log, "\n");
पूर्ण

__म_लिखो(4, 5)
अटल व्योम btf_verअगरier_log_vsi(काष्ठा btf_verअगरier_env *env,
				 स्थिर काष्ठा btf_type *datasec_type,
				 स्थिर काष्ठा btf_var_secinfo *vsi,
				 स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा bpf_verअगरier_log *log = &env->log;
	बहु_सूची args;

	अगर (!bpf_verअगरier_log_needed(log))
		वापस;
	अगर (log->level == BPF_LOG_KERNEL && !fmt)
		वापस;
	अगर (env->phase != CHECK_META)
		btf_verअगरier_log_type(env, datasec_type, शून्य);

	__btf_verअगरier_log(log, "\t type_id=%u offset=%u size=%u",
			   vsi->type, vsi->offset, vsi->size);
	अगर (fmt && *fmt) अणु
		__btf_verअगरier_log(log, " ");
		बहु_शुरू(args, fmt);
		bpf_verअगरier_vlog(log, fmt, args);
		बहु_पूर्ण(args);
	पूर्ण

	__btf_verअगरier_log(log, "\n");
पूर्ण

अटल व्योम btf_verअगरier_log_hdr(काष्ठा btf_verअगरier_env *env,
				 u32 btf_data_size)
अणु
	काष्ठा bpf_verअगरier_log *log = &env->log;
	स्थिर काष्ठा btf *btf = env->btf;
	स्थिर काष्ठा btf_header *hdr;

	अगर (!bpf_verअगरier_log_needed(log))
		वापस;

	अगर (log->level == BPF_LOG_KERNEL)
		वापस;
	hdr = &btf->hdr;
	__btf_verअगरier_log(log, "magic: 0x%x\n", hdr->magic);
	__btf_verअगरier_log(log, "version: %u\n", hdr->version);
	__btf_verअगरier_log(log, "flags: 0x%x\n", hdr->flags);
	__btf_verअगरier_log(log, "hdr_len: %u\n", hdr->hdr_len);
	__btf_verअगरier_log(log, "type_off: %u\n", hdr->type_off);
	__btf_verअगरier_log(log, "type_len: %u\n", hdr->type_len);
	__btf_verअगरier_log(log, "str_off: %u\n", hdr->str_off);
	__btf_verअगरier_log(log, "str_len: %u\n", hdr->str_len);
	__btf_verअगरier_log(log, "btf_total_size: %u\n", btf_data_size);
पूर्ण

अटल पूर्णांक btf_add_type(काष्ठा btf_verअगरier_env *env, काष्ठा btf_type *t)
अणु
	काष्ठा btf *btf = env->btf;

	अगर (btf->types_size == btf->nr_types) अणु
		/* Expand 'types' array */

		काष्ठा btf_type **new_types;
		u32 expand_by, new_size;

		अगर (btf->start_id + btf->types_size == BTF_MAX_TYPE) अणु
			btf_verअगरier_log(env, "Exceeded max num of types");
			वापस -E2BIG;
		पूर्ण

		expand_by = max_t(u32, btf->types_size >> 2, 16);
		new_size = min_t(u32, BTF_MAX_TYPE,
				 btf->types_size + expand_by);

		new_types = kvसुस्मृति(new_size, माप(*new_types),
				     GFP_KERNEL | __GFP_NOWARN);
		अगर (!new_types)
			वापस -ENOMEM;

		अगर (btf->nr_types == 0) अणु
			अगर (!btf->base_btf) अणु
				/* lazily init VOID type */
				new_types[0] = &btf_व्योम;
				btf->nr_types++;
			पूर्ण
		पूर्ण अन्यथा अणु
			स_नकल(new_types, btf->types,
			       माप(*btf->types) * btf->nr_types);
		पूर्ण

		kvमुक्त(btf->types);
		btf->types = new_types;
		btf->types_size = new_size;
	पूर्ण

	btf->types[btf->nr_types++] = t;

	वापस 0;
पूर्ण

अटल पूर्णांक btf_alloc_id(काष्ठा btf *btf)
अणु
	पूर्णांक id;

	idr_preload(GFP_KERNEL);
	spin_lock_bh(&btf_idr_lock);
	id = idr_alloc_cyclic(&btf_idr, btf, 1, पूर्णांक_उच्च, GFP_ATOMIC);
	अगर (id > 0)
		btf->id = id;
	spin_unlock_bh(&btf_idr_lock);
	idr_preload_end();

	अगर (WARN_ON_ONCE(!id))
		वापस -ENOSPC;

	वापस id > 0 ? 0 : id;
पूर्ण

अटल व्योम btf_मुक्त_id(काष्ठा btf *btf)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * In map-in-map, calling map_delete_elem() on outer
	 * map will call bpf_map_put on the inner map.
	 * It will then eventually call btf_मुक्त_id()
	 * on the inner map.  Some of the map_delete_elem()
	 * implementation may have irq disabled, so
	 * we need to use the _irqsave() version instead
	 * of the _bh() version.
	 */
	spin_lock_irqsave(&btf_idr_lock, flags);
	idr_हटाओ(&btf_idr, btf->id);
	spin_unlock_irqrestore(&btf_idr_lock, flags);
पूर्ण

अटल व्योम btf_मुक्त(काष्ठा btf *btf)
अणु
	kvमुक्त(btf->types);
	kvमुक्त(btf->resolved_sizes);
	kvमुक्त(btf->resolved_ids);
	kvमुक्त(btf->data);
	kमुक्त(btf);
पूर्ण

अटल व्योम btf_मुक्त_rcu(काष्ठा rcu_head *rcu)
अणु
	काष्ठा btf *btf = container_of(rcu, काष्ठा btf, rcu);

	btf_मुक्त(btf);
पूर्ण

व्योम btf_get(काष्ठा btf *btf)
अणु
	refcount_inc(&btf->refcnt);
पूर्ण

व्योम btf_put(काष्ठा btf *btf)
अणु
	अगर (btf && refcount_dec_and_test(&btf->refcnt)) अणु
		btf_मुक्त_id(btf);
		call_rcu(&btf->rcu, btf_मुक्त_rcu);
	पूर्ण
पूर्ण

अटल पूर्णांक env_resolve_init(काष्ठा btf_verअगरier_env *env)
अणु
	काष्ठा btf *btf = env->btf;
	u32 nr_types = btf->nr_types;
	u32 *resolved_sizes = शून्य;
	u32 *resolved_ids = शून्य;
	u8 *visit_states = शून्य;

	resolved_sizes = kvसुस्मृति(nr_types, माप(*resolved_sizes),
				  GFP_KERNEL | __GFP_NOWARN);
	अगर (!resolved_sizes)
		जाओ nomem;

	resolved_ids = kvसुस्मृति(nr_types, माप(*resolved_ids),
				GFP_KERNEL | __GFP_NOWARN);
	अगर (!resolved_ids)
		जाओ nomem;

	visit_states = kvसुस्मृति(nr_types, माप(*visit_states),
				GFP_KERNEL | __GFP_NOWARN);
	अगर (!visit_states)
		जाओ nomem;

	btf->resolved_sizes = resolved_sizes;
	btf->resolved_ids = resolved_ids;
	env->visit_states = visit_states;

	वापस 0;

nomem:
	kvमुक्त(resolved_sizes);
	kvमुक्त(resolved_ids);
	kvमुक्त(visit_states);
	वापस -ENOMEM;
पूर्ण

अटल व्योम btf_verअगरier_env_मुक्त(काष्ठा btf_verअगरier_env *env)
अणु
	kvमुक्त(env->visit_states);
	kमुक्त(env);
पूर्ण

अटल bool env_type_is_resolve_sink(स्थिर काष्ठा btf_verअगरier_env *env,
				     स्थिर काष्ठा btf_type *next_type)
अणु
	चयन (env->resolve_mode) अणु
	हाल RESOLVE_TBD:
		/* पूर्णांक, क्रमागत or व्योम is a sink */
		वापस !btf_type_needs_resolve(next_type);
	हाल RESOLVE_PTR:
		/* पूर्णांक, क्रमागत, व्योम, काष्ठा, array, func or func_proto is a sink
		 * क्रम ptr
		 */
		वापस !btf_type_is_modअगरier(next_type) &&
			!btf_type_is_ptr(next_type);
	हाल RESOLVE_STRUCT_OR_ARRAY:
		/* पूर्णांक, क्रमागत, व्योम, ptr, func or func_proto is a sink
		 * क्रम काष्ठा and array
		 */
		वापस !btf_type_is_modअगरier(next_type) &&
			!btf_type_is_array(next_type) &&
			!btf_type_is_काष्ठा(next_type);
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल bool env_type_is_resolved(स्थिर काष्ठा btf_verअगरier_env *env,
				 u32 type_id)
अणु
	/* base BTF types should be resolved by now */
	अगर (type_id < env->btf->start_id)
		वापस true;

	वापस env->visit_states[type_id - env->btf->start_id] == RESOLVED;
पूर्ण

अटल पूर्णांक env_stack_push(काष्ठा btf_verअगरier_env *env,
			  स्थिर काष्ठा btf_type *t, u32 type_id)
अणु
	स्थिर काष्ठा btf *btf = env->btf;
	काष्ठा resolve_vertex *v;

	अगर (env->top_stack == MAX_RESOLVE_DEPTH)
		वापस -E2BIG;

	अगर (type_id < btf->start_id
	    || env->visit_states[type_id - btf->start_id] != NOT_VISITED)
		वापस -EEXIST;

	env->visit_states[type_id - btf->start_id] = VISITED;

	v = &env->stack[env->top_stack++];
	v->t = t;
	v->type_id = type_id;
	v->next_member = 0;

	अगर (env->resolve_mode == RESOLVE_TBD) अणु
		अगर (btf_type_is_ptr(t))
			env->resolve_mode = RESOLVE_PTR;
		अन्यथा अगर (btf_type_is_काष्ठा(t) || btf_type_is_array(t))
			env->resolve_mode = RESOLVE_STRUCT_OR_ARRAY;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम env_stack_set_next_member(काष्ठा btf_verअगरier_env *env,
				      u16 next_member)
अणु
	env->stack[env->top_stack - 1].next_member = next_member;
पूर्ण

अटल व्योम env_stack_pop_resolved(काष्ठा btf_verअगरier_env *env,
				   u32 resolved_type_id,
				   u32 resolved_size)
अणु
	u32 type_id = env->stack[--(env->top_stack)].type_id;
	काष्ठा btf *btf = env->btf;

	type_id -= btf->start_id; /* adjust to local type id */
	btf->resolved_sizes[type_id] = resolved_size;
	btf->resolved_ids[type_id] = resolved_type_id;
	env->visit_states[type_id] = RESOLVED;
पूर्ण

अटल स्थिर काष्ठा resolve_vertex *env_stack_peak(काष्ठा btf_verअगरier_env *env)
अणु
	वापस env->top_stack ? &env->stack[env->top_stack - 1] : शून्य;
पूर्ण

/* Resolve the size of a passed-in "type"
 *
 * type: is an array (e.g. u32 array[x][y])
 * वापस type: type "u32[x][y]", i.e. BTF_KIND_ARRAY,
 * *type_size: (x * y * माप(u32)).  Hence, *type_size always
 *             corresponds to the वापस type.
 * *elem_type: u32
 * *elem_id: id of u32
 * *total_nelems: (x * y).  Hence, inभागidual elem size is
 *                (*type_size / *total_nelems)
 * *type_id: id of type अगर it's changed within the function, 0 अगर not
 *
 * type: is not an array (e.g. स्थिर काष्ठा X)
 * वापस type: type "struct X"
 * *type_size: माप(काष्ठा X)
 * *elem_type: same as वापस type ("struct X")
 * *elem_id: 0
 * *total_nelems: 1
 * *type_id: id of type अगर it's changed within the function, 0 अगर not
 */
अटल स्थिर काष्ठा btf_type *
__btf_resolve_size(स्थिर काष्ठा btf *btf, स्थिर काष्ठा btf_type *type,
		   u32 *type_size, स्थिर काष्ठा btf_type **elem_type,
		   u32 *elem_id, u32 *total_nelems, u32 *type_id)
अणु
	स्थिर काष्ठा btf_type *array_type = शून्य;
	स्थिर काष्ठा btf_array *array = शून्य;
	u32 i, size, nelems = 1, id = 0;

	क्रम (i = 0; i < MAX_RESOLVE_DEPTH; i++) अणु
		चयन (BTF_INFO_KIND(type->info)) अणु
		/* type->size can be used */
		हाल BTF_KIND_INT:
		हाल BTF_KIND_STRUCT:
		हाल BTF_KIND_UNION:
		हाल BTF_KIND_ENUM:
		हाल BTF_KIND_FLOAT:
			size = type->size;
			जाओ resolved;

		हाल BTF_KIND_PTR:
			size = माप(व्योम *);
			जाओ resolved;

		/* Modअगरiers */
		हाल BTF_KIND_TYPEDEF:
		हाल BTF_KIND_VOLATILE:
		हाल BTF_KIND_CONST:
		हाल BTF_KIND_RESTRICT:
			id = type->type;
			type = btf_type_by_id(btf, type->type);
			अवरोध;

		हाल BTF_KIND_ARRAY:
			अगर (!array_type)
				array_type = type;
			array = btf_type_array(type);
			अगर (nelems && array->nelems > U32_MAX / nelems)
				वापस ERR_PTR(-EINVAL);
			nelems *= array->nelems;
			type = btf_type_by_id(btf, array->type);
			अवरोध;

		/* type without size */
		शेष:
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण

	वापस ERR_PTR(-EINVAL);

resolved:
	अगर (nelems && size > U32_MAX / nelems)
		वापस ERR_PTR(-EINVAL);

	*type_size = nelems * size;
	अगर (total_nelems)
		*total_nelems = nelems;
	अगर (elem_type)
		*elem_type = type;
	अगर (elem_id)
		*elem_id = array ? array->type : 0;
	अगर (type_id && id)
		*type_id = id;

	वापस array_type ? : type;
पूर्ण

स्थिर काष्ठा btf_type *
btf_resolve_size(स्थिर काष्ठा btf *btf, स्थिर काष्ठा btf_type *type,
		 u32 *type_size)
अणु
	वापस __btf_resolve_size(btf, type, type_size, शून्य, शून्य, शून्य, शून्य);
पूर्ण

अटल u32 btf_resolved_type_id(स्थिर काष्ठा btf *btf, u32 type_id)
अणु
	जबतक (type_id < btf->start_id)
		btf = btf->base_btf;

	वापस btf->resolved_ids[type_id - btf->start_id];
पूर्ण

/* The input param "type_id" must poपूर्णांक to a needs_resolve type */
अटल स्थिर काष्ठा btf_type *btf_type_id_resolve(स्थिर काष्ठा btf *btf,
						  u32 *type_id)
अणु
	*type_id = btf_resolved_type_id(btf, *type_id);
	वापस btf_type_by_id(btf, *type_id);
पूर्ण

अटल u32 btf_resolved_type_size(स्थिर काष्ठा btf *btf, u32 type_id)
अणु
	जबतक (type_id < btf->start_id)
		btf = btf->base_btf;

	वापस btf->resolved_sizes[type_id - btf->start_id];
पूर्ण

स्थिर काष्ठा btf_type *btf_type_id_size(स्थिर काष्ठा btf *btf,
					u32 *type_id, u32 *ret_size)
अणु
	स्थिर काष्ठा btf_type *माप_प्रकारype;
	u32 माप_प्रकारype_id = *type_id;
	u32 size = 0;

	माप_प्रकारype = btf_type_by_id(btf, माप_प्रकारype_id);
	अगर (btf_type_nosize_or_null(माप_प्रकारype))
		वापस शून्य;

	अगर (btf_type_has_size(माप_प्रकारype)) अणु
		size = माप_प्रकारype->size;
	पूर्ण अन्यथा अगर (btf_type_is_array(माप_प्रकारype)) अणु
		size = btf_resolved_type_size(btf, माप_प्रकारype_id);
	पूर्ण अन्यथा अगर (btf_type_is_ptr(माप_प्रकारype)) अणु
		size = माप(व्योम *);
	पूर्ण अन्यथा अणु
		अगर (WARN_ON_ONCE(!btf_type_is_modअगरier(माप_प्रकारype) &&
				 !btf_type_is_var(माप_प्रकारype)))
			वापस शून्य;

		माप_प्रकारype_id = btf_resolved_type_id(btf, माप_प्रकारype_id);
		माप_प्रकारype = btf_type_by_id(btf, माप_प्रकारype_id);
		अगर (btf_type_nosize_or_null(माप_प्रकारype))
			वापस शून्य;
		अन्यथा अगर (btf_type_has_size(माप_प्रकारype))
			size = माप_प्रकारype->size;
		अन्यथा अगर (btf_type_is_array(माप_प्रकारype))
			size = btf_resolved_type_size(btf, माप_प्रकारype_id);
		अन्यथा अगर (btf_type_is_ptr(माप_प्रकारype))
			size = माप(व्योम *);
		अन्यथा
			वापस शून्य;
	पूर्ण

	*type_id = माप_प्रकारype_id;
	अगर (ret_size)
		*ret_size = size;

	वापस माप_प्रकारype;
पूर्ण

अटल पूर्णांक btf_df_check_member(काष्ठा btf_verअगरier_env *env,
			       स्थिर काष्ठा btf_type *काष्ठा_type,
			       स्थिर काष्ठा btf_member *member,
			       स्थिर काष्ठा btf_type *member_type)
अणु
	btf_verअगरier_log_basic(env, काष्ठा_type,
			       "Unsupported check_member");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक btf_df_check_kflag_member(काष्ठा btf_verअगरier_env *env,
				     स्थिर काष्ठा btf_type *काष्ठा_type,
				     स्थिर काष्ठा btf_member *member,
				     स्थिर काष्ठा btf_type *member_type)
अणु
	btf_verअगरier_log_basic(env, काष्ठा_type,
			       "Unsupported check_kflag_member");
	वापस -EINVAL;
पूर्ण

/* Used क्रम ptr, array काष्ठा/जोड़ and भग्न type members.
 * पूर्णांक, क्रमागत and modअगरier types have their specअगरic callback functions.
 */
अटल पूर्णांक btf_generic_check_kflag_member(काष्ठा btf_verअगरier_env *env,
					  स्थिर काष्ठा btf_type *काष्ठा_type,
					  स्थिर काष्ठा btf_member *member,
					  स्थिर काष्ठा btf_type *member_type)
अणु
	अगर (BTF_MEMBER_BITFIELD_SIZE(member->offset)) अणु
		btf_verअगरier_log_member(env, काष्ठा_type, member,
					"Invalid member bitfield_size");
		वापस -EINVAL;
	पूर्ण

	/* bitfield size is 0, so member->offset represents bit offset only.
	 * It is safe to call non kflag check_member variants.
	 */
	वापस btf_type_ops(member_type)->check_member(env, काष्ठा_type,
						       member,
						       member_type);
पूर्ण

अटल पूर्णांक btf_df_resolve(काष्ठा btf_verअगरier_env *env,
			  स्थिर काष्ठा resolve_vertex *v)
अणु
	btf_verअगरier_log_basic(env, v->t, "Unsupported resolve");
	वापस -EINVAL;
पूर्ण

अटल व्योम btf_df_show(स्थिर काष्ठा btf *btf, स्थिर काष्ठा btf_type *t,
			u32 type_id, व्योम *data, u8 bits_offsets,
			काष्ठा btf_show *show)
अणु
	btf_show(show, "<unsupported kind:%u>", BTF_INFO_KIND(t->info));
पूर्ण

अटल पूर्णांक btf_पूर्णांक_check_member(काष्ठा btf_verअगरier_env *env,
				स्थिर काष्ठा btf_type *काष्ठा_type,
				स्थिर काष्ठा btf_member *member,
				स्थिर काष्ठा btf_type *member_type)
अणु
	u32 पूर्णांक_data = btf_type_पूर्णांक(member_type);
	u32 काष्ठा_bits_off = member->offset;
	u32 काष्ठा_size = काष्ठा_type->size;
	u32 nr_copy_bits;
	u32 bytes_offset;

	अगर (U32_MAX - काष्ठा_bits_off < BTF_INT_OFFSET(पूर्णांक_data)) अणु
		btf_verअगरier_log_member(env, काष्ठा_type, member,
					"bits_offset exceeds U32_MAX");
		वापस -EINVAL;
	पूर्ण

	काष्ठा_bits_off += BTF_INT_OFFSET(पूर्णांक_data);
	bytes_offset = BITS_ROUNDDOWN_BYTES(काष्ठा_bits_off);
	nr_copy_bits = BTF_INT_BITS(पूर्णांक_data) +
		BITS_PER_BYTE_MASKED(काष्ठा_bits_off);

	अगर (nr_copy_bits > BITS_PER_U128) अणु
		btf_verअगरier_log_member(env, काष्ठा_type, member,
					"nr_copy_bits exceeds 128");
		वापस -EINVAL;
	पूर्ण

	अगर (काष्ठा_size < bytes_offset ||
	    काष्ठा_size - bytes_offset < BITS_ROUNDUP_BYTES(nr_copy_bits)) अणु
		btf_verअगरier_log_member(env, काष्ठा_type, member,
					"Member exceeds struct_size");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक btf_पूर्णांक_check_kflag_member(काष्ठा btf_verअगरier_env *env,
				      स्थिर काष्ठा btf_type *काष्ठा_type,
				      स्थिर काष्ठा btf_member *member,
				      स्थिर काष्ठा btf_type *member_type)
अणु
	u32 काष्ठा_bits_off, nr_bits, nr_पूर्णांक_data_bits, bytes_offset;
	u32 पूर्णांक_data = btf_type_पूर्णांक(member_type);
	u32 काष्ठा_size = काष्ठा_type->size;
	u32 nr_copy_bits;

	/* a regular पूर्णांक type is required क्रम the kflag पूर्णांक member */
	अगर (!btf_type_पूर्णांक_is_regular(member_type)) अणु
		btf_verअगरier_log_member(env, काष्ठा_type, member,
					"Invalid member base type");
		वापस -EINVAL;
	पूर्ण

	/* check sanity of bitfield size */
	nr_bits = BTF_MEMBER_BITFIELD_SIZE(member->offset);
	काष्ठा_bits_off = BTF_MEMBER_BIT_OFFSET(member->offset);
	nr_पूर्णांक_data_bits = BTF_INT_BITS(पूर्णांक_data);
	अगर (!nr_bits) अणु
		/* Not a bitfield member, member offset must be at byte
		 * boundary.
		 */
		अगर (BITS_PER_BYTE_MASKED(काष्ठा_bits_off)) अणु
			btf_verअगरier_log_member(env, काष्ठा_type, member,
						"Invalid member offset");
			वापस -EINVAL;
		पूर्ण

		nr_bits = nr_पूर्णांक_data_bits;
	पूर्ण अन्यथा अगर (nr_bits > nr_पूर्णांक_data_bits) अणु
		btf_verअगरier_log_member(env, काष्ठा_type, member,
					"Invalid member bitfield_size");
		वापस -EINVAL;
	पूर्ण

	bytes_offset = BITS_ROUNDDOWN_BYTES(काष्ठा_bits_off);
	nr_copy_bits = nr_bits + BITS_PER_BYTE_MASKED(काष्ठा_bits_off);
	अगर (nr_copy_bits > BITS_PER_U128) अणु
		btf_verअगरier_log_member(env, काष्ठा_type, member,
					"nr_copy_bits exceeds 128");
		वापस -EINVAL;
	पूर्ण

	अगर (काष्ठा_size < bytes_offset ||
	    काष्ठा_size - bytes_offset < BITS_ROUNDUP_BYTES(nr_copy_bits)) अणु
		btf_verअगरier_log_member(env, काष्ठा_type, member,
					"Member exceeds struct_size");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल s32 btf_पूर्णांक_check_meta(काष्ठा btf_verअगरier_env *env,
			      स्थिर काष्ठा btf_type *t,
			      u32 meta_left)
अणु
	u32 पूर्णांक_data, nr_bits, meta_needed = माप(पूर्णांक_data);
	u16 encoding;

	अगर (meta_left < meta_needed) अणु
		btf_verअगरier_log_basic(env, t,
				       "meta_left:%u meta_needed:%u",
				       meta_left, meta_needed);
		वापस -EINVAL;
	पूर्ण

	अगर (btf_type_vlen(t)) अणु
		btf_verअगरier_log_type(env, t, "vlen != 0");
		वापस -EINVAL;
	पूर्ण

	अगर (btf_type_kflag(t)) अणु
		btf_verअगरier_log_type(env, t, "Invalid btf_info kind_flag");
		वापस -EINVAL;
	पूर्ण

	पूर्णांक_data = btf_type_पूर्णांक(t);
	अगर (पूर्णांक_data & ~BTF_INT_MASK) अणु
		btf_verअगरier_log_basic(env, t, "Invalid int_data:%x",
				       पूर्णांक_data);
		वापस -EINVAL;
	पूर्ण

	nr_bits = BTF_INT_BITS(पूर्णांक_data) + BTF_INT_OFFSET(पूर्णांक_data);

	अगर (nr_bits > BITS_PER_U128) अणु
		btf_verअगरier_log_type(env, t, "nr_bits exceeds %zu",
				      BITS_PER_U128);
		वापस -EINVAL;
	पूर्ण

	अगर (BITS_ROUNDUP_BYTES(nr_bits) > t->size) अणु
		btf_verअगरier_log_type(env, t, "nr_bits exceeds type_size");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Only one of the encoding bits is allowed and it
	 * should be sufficient क्रम the pretty prपूर्णांक purpose (i.e. decoding).
	 * Multiple bits can be allowed later अगर it is found
	 * to be insufficient.
	 */
	encoding = BTF_INT_ENCODING(पूर्णांक_data);
	अगर (encoding &&
	    encoding != BTF_INT_SIGNED &&
	    encoding != BTF_INT_CHAR &&
	    encoding != BTF_INT_BOOL) अणु
		btf_verअगरier_log_type(env, t, "Unsupported encoding");
		वापस -ENOTSUPP;
	पूर्ण

	btf_verअगरier_log_type(env, t, शून्य);

	वापस meta_needed;
पूर्ण

अटल व्योम btf_पूर्णांक_log(काष्ठा btf_verअगरier_env *env,
			स्थिर काष्ठा btf_type *t)
अणु
	पूर्णांक पूर्णांक_data = btf_type_पूर्णांक(t);

	btf_verअगरier_log(env,
			 "size=%u bits_offset=%u nr_bits=%u encoding=%s",
			 t->size, BTF_INT_OFFSET(पूर्णांक_data),
			 BTF_INT_BITS(पूर्णांक_data),
			 btf_पूर्णांक_encoding_str(BTF_INT_ENCODING(पूर्णांक_data)));
पूर्ण

अटल व्योम btf_पूर्णांक128_prपूर्णांक(काष्ठा btf_show *show, व्योम *data)
अणु
	/* data poपूर्णांकs to a __पूर्णांक128 number.
	 * Suppose
	 *     पूर्णांक128_num = *(__पूर्णांक128 *)data;
	 * The below क्रमmulas shows what upper_num and lower_num represents:
	 *     upper_num = पूर्णांक128_num >> 64;
	 *     lower_num = पूर्णांक128_num & 0xffffffffFFFFFFFFULL;
	 */
	u64 upper_num, lower_num;

#अगर_घोषित __BIG_ENDIAN_BITFIELD
	upper_num = *(u64 *)data;
	lower_num = *(u64 *)(data + 8);
#अन्यथा
	upper_num = *(u64 *)(data + 8);
	lower_num = *(u64 *)data;
#पूर्ण_अगर
	अगर (upper_num == 0)
		btf_show_type_value(show, "0x%llx", lower_num);
	अन्यथा
		btf_show_type_values(show, "0x%llx%016llx", upper_num,
				     lower_num);
पूर्ण

अटल व्योम btf_पूर्णांक128_shअगरt(u64 *prपूर्णांक_num, u16 left_shअगरt_bits,
			     u16 right_shअगरt_bits)
अणु
	u64 upper_num, lower_num;

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

अटल व्योम btf_bitfield_show(व्योम *data, u8 bits_offset,
			      u8 nr_bits, काष्ठा btf_show *show)
अणु
	u16 left_shअगरt_bits, right_shअगरt_bits;
	u8 nr_copy_bytes;
	u8 nr_copy_bits;
	u64 prपूर्णांक_num[2] = अणुपूर्ण;

	nr_copy_bits = nr_bits + bits_offset;
	nr_copy_bytes = BITS_ROUNDUP_BYTES(nr_copy_bits);

	स_नकल(prपूर्णांक_num, data, nr_copy_bytes);

#अगर_घोषित __BIG_ENDIAN_BITFIELD
	left_shअगरt_bits = bits_offset;
#अन्यथा
	left_shअगरt_bits = BITS_PER_U128 - nr_copy_bits;
#पूर्ण_अगर
	right_shअगरt_bits = BITS_PER_U128 - nr_bits;

	btf_पूर्णांक128_shअगरt(prपूर्णांक_num, left_shअगरt_bits, right_shअगरt_bits);
	btf_पूर्णांक128_prपूर्णांक(show, prपूर्णांक_num);
पूर्ण


अटल व्योम btf_पूर्णांक_bits_show(स्थिर काष्ठा btf *btf,
			      स्थिर काष्ठा btf_type *t,
			      व्योम *data, u8 bits_offset,
			      काष्ठा btf_show *show)
अणु
	u32 पूर्णांक_data = btf_type_पूर्णांक(t);
	u8 nr_bits = BTF_INT_BITS(पूर्णांक_data);
	u8 total_bits_offset;

	/*
	 * bits_offset is at most 7.
	 * BTF_INT_OFFSET() cannot exceed 128 bits.
	 */
	total_bits_offset = bits_offset + BTF_INT_OFFSET(पूर्णांक_data);
	data += BITS_ROUNDDOWN_BYTES(total_bits_offset);
	bits_offset = BITS_PER_BYTE_MASKED(total_bits_offset);
	btf_bitfield_show(data, bits_offset, nr_bits, show);
पूर्ण

अटल व्योम btf_पूर्णांक_show(स्थिर काष्ठा btf *btf, स्थिर काष्ठा btf_type *t,
			 u32 type_id, व्योम *data, u8 bits_offset,
			 काष्ठा btf_show *show)
अणु
	u32 पूर्णांक_data = btf_type_पूर्णांक(t);
	u8 encoding = BTF_INT_ENCODING(पूर्णांक_data);
	bool sign = encoding & BTF_INT_SIGNED;
	u8 nr_bits = BTF_INT_BITS(पूर्णांक_data);
	व्योम *safe_data;

	safe_data = btf_show_start_type(show, t, type_id, data);
	अगर (!safe_data)
		वापस;

	अगर (bits_offset || BTF_INT_OFFSET(पूर्णांक_data) ||
	    BITS_PER_BYTE_MASKED(nr_bits)) अणु
		btf_पूर्णांक_bits_show(btf, t, safe_data, bits_offset, show);
		जाओ out;
	पूर्ण

	चयन (nr_bits) अणु
	हाल 128:
		btf_पूर्णांक128_prपूर्णांक(show, safe_data);
		अवरोध;
	हाल 64:
		अगर (sign)
			btf_show_type_value(show, "%lld", *(s64 *)safe_data);
		अन्यथा
			btf_show_type_value(show, "%llu", *(u64 *)safe_data);
		अवरोध;
	हाल 32:
		अगर (sign)
			btf_show_type_value(show, "%d", *(s32 *)safe_data);
		अन्यथा
			btf_show_type_value(show, "%u", *(u32 *)safe_data);
		अवरोध;
	हाल 16:
		अगर (sign)
			btf_show_type_value(show, "%d", *(s16 *)safe_data);
		अन्यथा
			btf_show_type_value(show, "%u", *(u16 *)safe_data);
		अवरोध;
	हाल 8:
		अगर (show->state.array_encoding == BTF_INT_CHAR) अणु
			/* check क्रम null terminator */
			अगर (show->state.array_terminated)
				अवरोध;
			अगर (*(अक्षर *)data == '\0') अणु
				show->state.array_terminated = 1;
				अवरोध;
			पूर्ण
			अगर (है_छाप(*(अक्षर *)data)) अणु
				btf_show_type_value(show, "'%c'",
						    *(अक्षर *)safe_data);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (sign)
			btf_show_type_value(show, "%d", *(s8 *)safe_data);
		अन्यथा
			btf_show_type_value(show, "%u", *(u8 *)safe_data);
		अवरोध;
	शेष:
		btf_पूर्णांक_bits_show(btf, t, safe_data, bits_offset, show);
		अवरोध;
	पूर्ण
out:
	btf_show_end_type(show);
पूर्ण

अटल स्थिर काष्ठा btf_kind_operations पूर्णांक_ops = अणु
	.check_meta = btf_पूर्णांक_check_meta,
	.resolve = btf_df_resolve,
	.check_member = btf_पूर्णांक_check_member,
	.check_kflag_member = btf_पूर्णांक_check_kflag_member,
	.log_details = btf_पूर्णांक_log,
	.show = btf_पूर्णांक_show,
पूर्ण;

अटल पूर्णांक btf_modअगरier_check_member(काष्ठा btf_verअगरier_env *env,
				     स्थिर काष्ठा btf_type *काष्ठा_type,
				     स्थिर काष्ठा btf_member *member,
				     स्थिर काष्ठा btf_type *member_type)
अणु
	स्थिर काष्ठा btf_type *resolved_type;
	u32 resolved_type_id = member->type;
	काष्ठा btf_member resolved_member;
	काष्ठा btf *btf = env->btf;

	resolved_type = btf_type_id_size(btf, &resolved_type_id, शून्य);
	अगर (!resolved_type) अणु
		btf_verअगरier_log_member(env, काष्ठा_type, member,
					"Invalid member");
		वापस -EINVAL;
	पूर्ण

	resolved_member = *member;
	resolved_member.type = resolved_type_id;

	वापस btf_type_ops(resolved_type)->check_member(env, काष्ठा_type,
							 &resolved_member,
							 resolved_type);
पूर्ण

अटल पूर्णांक btf_modअगरier_check_kflag_member(काष्ठा btf_verअगरier_env *env,
					   स्थिर काष्ठा btf_type *काष्ठा_type,
					   स्थिर काष्ठा btf_member *member,
					   स्थिर काष्ठा btf_type *member_type)
अणु
	स्थिर काष्ठा btf_type *resolved_type;
	u32 resolved_type_id = member->type;
	काष्ठा btf_member resolved_member;
	काष्ठा btf *btf = env->btf;

	resolved_type = btf_type_id_size(btf, &resolved_type_id, शून्य);
	अगर (!resolved_type) अणु
		btf_verअगरier_log_member(env, काष्ठा_type, member,
					"Invalid member");
		वापस -EINVAL;
	पूर्ण

	resolved_member = *member;
	resolved_member.type = resolved_type_id;

	वापस btf_type_ops(resolved_type)->check_kflag_member(env, काष्ठा_type,
							       &resolved_member,
							       resolved_type);
पूर्ण

अटल पूर्णांक btf_ptr_check_member(काष्ठा btf_verअगरier_env *env,
				स्थिर काष्ठा btf_type *काष्ठा_type,
				स्थिर काष्ठा btf_member *member,
				स्थिर काष्ठा btf_type *member_type)
अणु
	u32 काष्ठा_size, काष्ठा_bits_off, bytes_offset;

	काष्ठा_size = काष्ठा_type->size;
	काष्ठा_bits_off = member->offset;
	bytes_offset = BITS_ROUNDDOWN_BYTES(काष्ठा_bits_off);

	अगर (BITS_PER_BYTE_MASKED(काष्ठा_bits_off)) अणु
		btf_verअगरier_log_member(env, काष्ठा_type, member,
					"Member is not byte aligned");
		वापस -EINVAL;
	पूर्ण

	अगर (काष्ठा_size - bytes_offset < माप(व्योम *)) अणु
		btf_verअगरier_log_member(env, काष्ठा_type, member,
					"Member exceeds struct_size");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक btf_ref_type_check_meta(काष्ठा btf_verअगरier_env *env,
				   स्थिर काष्ठा btf_type *t,
				   u32 meta_left)
अणु
	अगर (btf_type_vlen(t)) अणु
		btf_verअगरier_log_type(env, t, "vlen != 0");
		वापस -EINVAL;
	पूर्ण

	अगर (btf_type_kflag(t)) अणु
		btf_verअगरier_log_type(env, t, "Invalid btf_info kind_flag");
		वापस -EINVAL;
	पूर्ण

	अगर (!BTF_TYPE_ID_VALID(t->type)) अणु
		btf_verअगरier_log_type(env, t, "Invalid type_id");
		वापस -EINVAL;
	पूर्ण

	/* प्रकार type must have a valid name, and other ref types,
	 * अस्थिर, स्थिर, restrict, should have a null name.
	 */
	अगर (BTF_INFO_KIND(t->info) == BTF_KIND_TYPEDEF) अणु
		अगर (!t->name_off ||
		    !btf_name_valid_identअगरier(env->btf, t->name_off)) अणु
			btf_verअगरier_log_type(env, t, "Invalid name");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (t->name_off) अणु
			btf_verअगरier_log_type(env, t, "Invalid name");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	btf_verअगरier_log_type(env, t, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक btf_modअगरier_resolve(काष्ठा btf_verअगरier_env *env,
				स्थिर काष्ठा resolve_vertex *v)
अणु
	स्थिर काष्ठा btf_type *t = v->t;
	स्थिर काष्ठा btf_type *next_type;
	u32 next_type_id = t->type;
	काष्ठा btf *btf = env->btf;

	next_type = btf_type_by_id(btf, next_type_id);
	अगर (!next_type || btf_type_is_resolve_source_only(next_type)) अणु
		btf_verअगरier_log_type(env, v->t, "Invalid type_id");
		वापस -EINVAL;
	पूर्ण

	अगर (!env_type_is_resolve_sink(env, next_type) &&
	    !env_type_is_resolved(env, next_type_id))
		वापस env_stack_push(env, next_type, next_type_id);

	/* Figure out the resolved next_type_id with size.
	 * They will be stored in the current modअगरier's
	 * resolved_ids and resolved_sizes such that it can
	 * save us a few type-following when we use it later (e.g. in
	 * pretty prपूर्णांक).
	 */
	अगर (!btf_type_id_size(btf, &next_type_id, शून्य)) अणु
		अगर (env_type_is_resolved(env, next_type_id))
			next_type = btf_type_id_resolve(btf, &next_type_id);

		/* "typedef void new_void", "const void"...etc */
		अगर (!btf_type_is_व्योम(next_type) &&
		    !btf_type_is_fwd(next_type) &&
		    !btf_type_is_func_proto(next_type)) अणु
			btf_verअगरier_log_type(env, v->t, "Invalid type_id");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	env_stack_pop_resolved(env, next_type_id, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक btf_var_resolve(काष्ठा btf_verअगरier_env *env,
			   स्थिर काष्ठा resolve_vertex *v)
अणु
	स्थिर काष्ठा btf_type *next_type;
	स्थिर काष्ठा btf_type *t = v->t;
	u32 next_type_id = t->type;
	काष्ठा btf *btf = env->btf;

	next_type = btf_type_by_id(btf, next_type_id);
	अगर (!next_type || btf_type_is_resolve_source_only(next_type)) अणु
		btf_verअगरier_log_type(env, v->t, "Invalid type_id");
		वापस -EINVAL;
	पूर्ण

	अगर (!env_type_is_resolve_sink(env, next_type) &&
	    !env_type_is_resolved(env, next_type_id))
		वापस env_stack_push(env, next_type, next_type_id);

	अगर (btf_type_is_modअगरier(next_type)) अणु
		स्थिर काष्ठा btf_type *resolved_type;
		u32 resolved_type_id;

		resolved_type_id = next_type_id;
		resolved_type = btf_type_id_resolve(btf, &resolved_type_id);

		अगर (btf_type_is_ptr(resolved_type) &&
		    !env_type_is_resolve_sink(env, resolved_type) &&
		    !env_type_is_resolved(env, resolved_type_id))
			वापस env_stack_push(env, resolved_type,
					      resolved_type_id);
	पूर्ण

	/* We must resolve to something concrete at this poपूर्णांक, no
	 * क्रमward types or similar that would resolve to size of
	 * zero is allowed.
	 */
	अगर (!btf_type_id_size(btf, &next_type_id, शून्य)) अणु
		btf_verअगरier_log_type(env, v->t, "Invalid type_id");
		वापस -EINVAL;
	पूर्ण

	env_stack_pop_resolved(env, next_type_id, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक btf_ptr_resolve(काष्ठा btf_verअगरier_env *env,
			   स्थिर काष्ठा resolve_vertex *v)
अणु
	स्थिर काष्ठा btf_type *next_type;
	स्थिर काष्ठा btf_type *t = v->t;
	u32 next_type_id = t->type;
	काष्ठा btf *btf = env->btf;

	next_type = btf_type_by_id(btf, next_type_id);
	अगर (!next_type || btf_type_is_resolve_source_only(next_type)) अणु
		btf_verअगरier_log_type(env, v->t, "Invalid type_id");
		वापस -EINVAL;
	पूर्ण

	अगर (!env_type_is_resolve_sink(env, next_type) &&
	    !env_type_is_resolved(env, next_type_id))
		वापस env_stack_push(env, next_type, next_type_id);

	/* If the modअगरier was RESOLVED during RESOLVE_STRUCT_OR_ARRAY,
	 * the modअगरier may have stopped resolving when it was resolved
	 * to a ptr (last-resolved-ptr).
	 *
	 * We now need to जारी from the last-resolved-ptr to
	 * ensure the last-resolved-ptr will not referring back to
	 * the currenct ptr (t).
	 */
	अगर (btf_type_is_modअगरier(next_type)) अणु
		स्थिर काष्ठा btf_type *resolved_type;
		u32 resolved_type_id;

		resolved_type_id = next_type_id;
		resolved_type = btf_type_id_resolve(btf, &resolved_type_id);

		अगर (btf_type_is_ptr(resolved_type) &&
		    !env_type_is_resolve_sink(env, resolved_type) &&
		    !env_type_is_resolved(env, resolved_type_id))
			वापस env_stack_push(env, resolved_type,
					      resolved_type_id);
	पूर्ण

	अगर (!btf_type_id_size(btf, &next_type_id, शून्य)) अणु
		अगर (env_type_is_resolved(env, next_type_id))
			next_type = btf_type_id_resolve(btf, &next_type_id);

		अगर (!btf_type_is_व्योम(next_type) &&
		    !btf_type_is_fwd(next_type) &&
		    !btf_type_is_func_proto(next_type)) अणु
			btf_verअगरier_log_type(env, v->t, "Invalid type_id");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	env_stack_pop_resolved(env, next_type_id, 0);

	वापस 0;
पूर्ण

अटल व्योम btf_modअगरier_show(स्थिर काष्ठा btf *btf,
			      स्थिर काष्ठा btf_type *t,
			      u32 type_id, व्योम *data,
			      u8 bits_offset, काष्ठा btf_show *show)
अणु
	अगर (btf->resolved_ids)
		t = btf_type_id_resolve(btf, &type_id);
	अन्यथा
		t = btf_type_skip_modअगरiers(btf, type_id, शून्य);

	btf_type_ops(t)->show(btf, t, type_id, data, bits_offset, show);
पूर्ण

अटल व्योम btf_var_show(स्थिर काष्ठा btf *btf, स्थिर काष्ठा btf_type *t,
			 u32 type_id, व्योम *data, u8 bits_offset,
			 काष्ठा btf_show *show)
अणु
	t = btf_type_id_resolve(btf, &type_id);

	btf_type_ops(t)->show(btf, t, type_id, data, bits_offset, show);
पूर्ण

अटल व्योम btf_ptr_show(स्थिर काष्ठा btf *btf, स्थिर काष्ठा btf_type *t,
			 u32 type_id, व्योम *data, u8 bits_offset,
			 काष्ठा btf_show *show)
अणु
	व्योम *safe_data;

	safe_data = btf_show_start_type(show, t, type_id, data);
	अगर (!safe_data)
		वापस;

	/* It is a hashed value unless BTF_SHOW_PTR_RAW is specअगरied */
	अगर (show->flags & BTF_SHOW_PTR_RAW)
		btf_show_type_value(show, "0x%px", *(व्योम **)safe_data);
	अन्यथा
		btf_show_type_value(show, "0x%p", *(व्योम **)safe_data);
	btf_show_end_type(show);
पूर्ण

अटल व्योम btf_ref_type_log(काष्ठा btf_verअगरier_env *env,
			     स्थिर काष्ठा btf_type *t)
अणु
	btf_verअगरier_log(env, "type_id=%u", t->type);
पूर्ण

अटल काष्ठा btf_kind_operations modअगरier_ops = अणु
	.check_meta = btf_ref_type_check_meta,
	.resolve = btf_modअगरier_resolve,
	.check_member = btf_modअगरier_check_member,
	.check_kflag_member = btf_modअगरier_check_kflag_member,
	.log_details = btf_ref_type_log,
	.show = btf_modअगरier_show,
पूर्ण;

अटल काष्ठा btf_kind_operations ptr_ops = अणु
	.check_meta = btf_ref_type_check_meta,
	.resolve = btf_ptr_resolve,
	.check_member = btf_ptr_check_member,
	.check_kflag_member = btf_generic_check_kflag_member,
	.log_details = btf_ref_type_log,
	.show = btf_ptr_show,
पूर्ण;

अटल s32 btf_fwd_check_meta(काष्ठा btf_verअगरier_env *env,
			      स्थिर काष्ठा btf_type *t,
			      u32 meta_left)
अणु
	अगर (btf_type_vlen(t)) अणु
		btf_verअगरier_log_type(env, t, "vlen != 0");
		वापस -EINVAL;
	पूर्ण

	अगर (t->type) अणु
		btf_verअगरier_log_type(env, t, "type != 0");
		वापस -EINVAL;
	पूर्ण

	/* fwd type must have a valid name */
	अगर (!t->name_off ||
	    !btf_name_valid_identअगरier(env->btf, t->name_off)) अणु
		btf_verअगरier_log_type(env, t, "Invalid name");
		वापस -EINVAL;
	पूर्ण

	btf_verअगरier_log_type(env, t, शून्य);

	वापस 0;
पूर्ण

अटल व्योम btf_fwd_type_log(काष्ठा btf_verअगरier_env *env,
			     स्थिर काष्ठा btf_type *t)
अणु
	btf_verअगरier_log(env, "%s", btf_type_kflag(t) ? "union" : "struct");
पूर्ण

अटल काष्ठा btf_kind_operations fwd_ops = अणु
	.check_meta = btf_fwd_check_meta,
	.resolve = btf_df_resolve,
	.check_member = btf_df_check_member,
	.check_kflag_member = btf_df_check_kflag_member,
	.log_details = btf_fwd_type_log,
	.show = btf_df_show,
पूर्ण;

अटल पूर्णांक btf_array_check_member(काष्ठा btf_verअगरier_env *env,
				  स्थिर काष्ठा btf_type *काष्ठा_type,
				  स्थिर काष्ठा btf_member *member,
				  स्थिर काष्ठा btf_type *member_type)
अणु
	u32 काष्ठा_bits_off = member->offset;
	u32 काष्ठा_size, bytes_offset;
	u32 array_type_id, array_size;
	काष्ठा btf *btf = env->btf;

	अगर (BITS_PER_BYTE_MASKED(काष्ठा_bits_off)) अणु
		btf_verअगरier_log_member(env, काष्ठा_type, member,
					"Member is not byte aligned");
		वापस -EINVAL;
	पूर्ण

	array_type_id = member->type;
	btf_type_id_size(btf, &array_type_id, &array_size);
	काष्ठा_size = काष्ठा_type->size;
	bytes_offset = BITS_ROUNDDOWN_BYTES(काष्ठा_bits_off);
	अगर (काष्ठा_size - bytes_offset < array_size) अणु
		btf_verअगरier_log_member(env, काष्ठा_type, member,
					"Member exceeds struct_size");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल s32 btf_array_check_meta(काष्ठा btf_verअगरier_env *env,
				स्थिर काष्ठा btf_type *t,
				u32 meta_left)
अणु
	स्थिर काष्ठा btf_array *array = btf_type_array(t);
	u32 meta_needed = माप(*array);

	अगर (meta_left < meta_needed) अणु
		btf_verअगरier_log_basic(env, t,
				       "meta_left:%u meta_needed:%u",
				       meta_left, meta_needed);
		वापस -EINVAL;
	पूर्ण

	/* array type should not have a name */
	अगर (t->name_off) अणु
		btf_verअगरier_log_type(env, t, "Invalid name");
		वापस -EINVAL;
	पूर्ण

	अगर (btf_type_vlen(t)) अणु
		btf_verअगरier_log_type(env, t, "vlen != 0");
		वापस -EINVAL;
	पूर्ण

	अगर (btf_type_kflag(t)) अणु
		btf_verअगरier_log_type(env, t, "Invalid btf_info kind_flag");
		वापस -EINVAL;
	पूर्ण

	अगर (t->size) अणु
		btf_verअगरier_log_type(env, t, "size != 0");
		वापस -EINVAL;
	पूर्ण

	/* Array elem type and index type cannot be in type व्योम,
	 * so !array->type and !array->index_type are not allowed.
	 */
	अगर (!array->type || !BTF_TYPE_ID_VALID(array->type)) अणु
		btf_verअगरier_log_type(env, t, "Invalid elem");
		वापस -EINVAL;
	पूर्ण

	अगर (!array->index_type || !BTF_TYPE_ID_VALID(array->index_type)) अणु
		btf_verअगरier_log_type(env, t, "Invalid index");
		वापस -EINVAL;
	पूर्ण

	btf_verअगरier_log_type(env, t, शून्य);

	वापस meta_needed;
पूर्ण

अटल पूर्णांक btf_array_resolve(काष्ठा btf_verअगरier_env *env,
			     स्थिर काष्ठा resolve_vertex *v)
अणु
	स्थिर काष्ठा btf_array *array = btf_type_array(v->t);
	स्थिर काष्ठा btf_type *elem_type, *index_type;
	u32 elem_type_id, index_type_id;
	काष्ठा btf *btf = env->btf;
	u32 elem_size;

	/* Check array->index_type */
	index_type_id = array->index_type;
	index_type = btf_type_by_id(btf, index_type_id);
	अगर (btf_type_nosize_or_null(index_type) ||
	    btf_type_is_resolve_source_only(index_type)) अणु
		btf_verअगरier_log_type(env, v->t, "Invalid index");
		वापस -EINVAL;
	पूर्ण

	अगर (!env_type_is_resolve_sink(env, index_type) &&
	    !env_type_is_resolved(env, index_type_id))
		वापस env_stack_push(env, index_type, index_type_id);

	index_type = btf_type_id_size(btf, &index_type_id, शून्य);
	अगर (!index_type || !btf_type_is_पूर्णांक(index_type) ||
	    !btf_type_पूर्णांक_is_regular(index_type)) अणु
		btf_verअगरier_log_type(env, v->t, "Invalid index");
		वापस -EINVAL;
	पूर्ण

	/* Check array->type */
	elem_type_id = array->type;
	elem_type = btf_type_by_id(btf, elem_type_id);
	अगर (btf_type_nosize_or_null(elem_type) ||
	    btf_type_is_resolve_source_only(elem_type)) अणु
		btf_verअगरier_log_type(env, v->t,
				      "Invalid elem");
		वापस -EINVAL;
	पूर्ण

	अगर (!env_type_is_resolve_sink(env, elem_type) &&
	    !env_type_is_resolved(env, elem_type_id))
		वापस env_stack_push(env, elem_type, elem_type_id);

	elem_type = btf_type_id_size(btf, &elem_type_id, &elem_size);
	अगर (!elem_type) अणु
		btf_verअगरier_log_type(env, v->t, "Invalid elem");
		वापस -EINVAL;
	पूर्ण

	अगर (btf_type_is_पूर्णांक(elem_type) && !btf_type_पूर्णांक_is_regular(elem_type)) अणु
		btf_verअगरier_log_type(env, v->t, "Invalid array of int");
		वापस -EINVAL;
	पूर्ण

	अगर (array->nelems && elem_size > U32_MAX / array->nelems) अणु
		btf_verअगरier_log_type(env, v->t,
				      "Array size overflows U32_MAX");
		वापस -EINVAL;
	पूर्ण

	env_stack_pop_resolved(env, elem_type_id, elem_size * array->nelems);

	वापस 0;
पूर्ण

अटल व्योम btf_array_log(काष्ठा btf_verअगरier_env *env,
			  स्थिर काष्ठा btf_type *t)
अणु
	स्थिर काष्ठा btf_array *array = btf_type_array(t);

	btf_verअगरier_log(env, "type_id=%u index_type_id=%u nr_elems=%u",
			 array->type, array->index_type, array->nelems);
पूर्ण

अटल व्योम __btf_array_show(स्थिर काष्ठा btf *btf, स्थिर काष्ठा btf_type *t,
			     u32 type_id, व्योम *data, u8 bits_offset,
			     काष्ठा btf_show *show)
अणु
	स्थिर काष्ठा btf_array *array = btf_type_array(t);
	स्थिर काष्ठा btf_kind_operations *elem_ops;
	स्थिर काष्ठा btf_type *elem_type;
	u32 i, elem_size = 0, elem_type_id;
	u16 encoding = 0;

	elem_type_id = array->type;
	elem_type = btf_type_skip_modअगरiers(btf, elem_type_id, शून्य);
	अगर (elem_type && btf_type_has_size(elem_type))
		elem_size = elem_type->size;

	अगर (elem_type && btf_type_is_पूर्णांक(elem_type)) अणु
		u32 पूर्णांक_type = btf_type_पूर्णांक(elem_type);

		encoding = BTF_INT_ENCODING(पूर्णांक_type);

		/*
		 * BTF_INT_CHAR encoding never seems to be set क्रम
		 * अक्षर arrays, so अगर size is 1 and element is
		 * prपूर्णांकable as a अक्षर, we'll करो that.
		 */
		अगर (elem_size == 1)
			encoding = BTF_INT_CHAR;
	पूर्ण

	अगर (!btf_show_start_array_type(show, t, type_id, encoding, data))
		वापस;

	अगर (!elem_type)
		जाओ out;
	elem_ops = btf_type_ops(elem_type);

	क्रम (i = 0; i < array->nelems; i++) अणु

		btf_show_start_array_member(show);

		elem_ops->show(btf, elem_type, elem_type_id, data,
			       bits_offset, show);
		data += elem_size;

		btf_show_end_array_member(show);

		अगर (show->state.array_terminated)
			अवरोध;
	पूर्ण
out:
	btf_show_end_array_type(show);
पूर्ण

अटल व्योम btf_array_show(स्थिर काष्ठा btf *btf, स्थिर काष्ठा btf_type *t,
			   u32 type_id, व्योम *data, u8 bits_offset,
			   काष्ठा btf_show *show)
अणु
	स्थिर काष्ठा btf_member *m = show->state.member;

	/*
	 * First check अगर any members would be shown (are non-zero).
	 * See comments above "struct btf_show" definition क्रम more
	 * details on how this works at a high-level.
	 */
	अगर (show->state.depth > 0 && !(show->flags & BTF_SHOW_ZERO)) अणु
		अगर (!show->state.depth_check) अणु
			show->state.depth_check = show->state.depth + 1;
			show->state.depth_to_show = 0;
		पूर्ण
		__btf_array_show(btf, t, type_id, data, bits_offset, show);
		show->state.member = m;

		अगर (show->state.depth_check != show->state.depth + 1)
			वापस;
		show->state.depth_check = 0;

		अगर (show->state.depth_to_show <= show->state.depth)
			वापस;
		/*
		 * Reaching here indicates we have recursed and found
		 * non-zero array member(s).
		 */
	पूर्ण
	__btf_array_show(btf, t, type_id, data, bits_offset, show);
पूर्ण

अटल काष्ठा btf_kind_operations array_ops = अणु
	.check_meta = btf_array_check_meta,
	.resolve = btf_array_resolve,
	.check_member = btf_array_check_member,
	.check_kflag_member = btf_generic_check_kflag_member,
	.log_details = btf_array_log,
	.show = btf_array_show,
पूर्ण;

अटल पूर्णांक btf_काष्ठा_check_member(काष्ठा btf_verअगरier_env *env,
				   स्थिर काष्ठा btf_type *काष्ठा_type,
				   स्थिर काष्ठा btf_member *member,
				   स्थिर काष्ठा btf_type *member_type)
अणु
	u32 काष्ठा_bits_off = member->offset;
	u32 काष्ठा_size, bytes_offset;

	अगर (BITS_PER_BYTE_MASKED(काष्ठा_bits_off)) अणु
		btf_verअगरier_log_member(env, काष्ठा_type, member,
					"Member is not byte aligned");
		वापस -EINVAL;
	पूर्ण

	काष्ठा_size = काष्ठा_type->size;
	bytes_offset = BITS_ROUNDDOWN_BYTES(काष्ठा_bits_off);
	अगर (काष्ठा_size - bytes_offset < member_type->size) अणु
		btf_verअगरier_log_member(env, काष्ठा_type, member,
					"Member exceeds struct_size");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल s32 btf_काष्ठा_check_meta(काष्ठा btf_verअगरier_env *env,
				 स्थिर काष्ठा btf_type *t,
				 u32 meta_left)
अणु
	bool is_जोड़ = BTF_INFO_KIND(t->info) == BTF_KIND_UNION;
	स्थिर काष्ठा btf_member *member;
	u32 meta_needed, last_offset;
	काष्ठा btf *btf = env->btf;
	u32 काष्ठा_size = t->size;
	u32 offset;
	u16 i;

	meta_needed = btf_type_vlen(t) * माप(*member);
	अगर (meta_left < meta_needed) अणु
		btf_verअगरier_log_basic(env, t,
				       "meta_left:%u meta_needed:%u",
				       meta_left, meta_needed);
		वापस -EINVAL;
	पूर्ण

	/* काष्ठा type either no name or a valid one */
	अगर (t->name_off &&
	    !btf_name_valid_identअगरier(env->btf, t->name_off)) अणु
		btf_verअगरier_log_type(env, t, "Invalid name");
		वापस -EINVAL;
	पूर्ण

	btf_verअगरier_log_type(env, t, शून्य);

	last_offset = 0;
	क्रम_each_member(i, t, member) अणु
		अगर (!btf_name_offset_valid(btf, member->name_off)) अणु
			btf_verअगरier_log_member(env, t, member,
						"Invalid member name_offset:%u",
						member->name_off);
			वापस -EINVAL;
		पूर्ण

		/* काष्ठा member either no name or a valid one */
		अगर (member->name_off &&
		    !btf_name_valid_identअगरier(btf, member->name_off)) अणु
			btf_verअगरier_log_member(env, t, member, "Invalid name");
			वापस -EINVAL;
		पूर्ण
		/* A member cannot be in type व्योम */
		अगर (!member->type || !BTF_TYPE_ID_VALID(member->type)) अणु
			btf_verअगरier_log_member(env, t, member,
						"Invalid type_id");
			वापस -EINVAL;
		पूर्ण

		offset = btf_member_bit_offset(t, member);
		अगर (is_जोड़ && offset) अणु
			btf_verअगरier_log_member(env, t, member,
						"Invalid member bits_offset");
			वापस -EINVAL;
		पूर्ण

		/*
		 * ">" instead of ">=" because the last member could be
		 * "char a[0];"
		 */
		अगर (last_offset > offset) अणु
			btf_verअगरier_log_member(env, t, member,
						"Invalid member bits_offset");
			वापस -EINVAL;
		पूर्ण

		अगर (BITS_ROUNDUP_BYTES(offset) > काष्ठा_size) अणु
			btf_verअगरier_log_member(env, t, member,
						"Member bits_offset exceeds its struct size");
			वापस -EINVAL;
		पूर्ण

		btf_verअगरier_log_member(env, t, member, शून्य);
		last_offset = offset;
	पूर्ण

	वापस meta_needed;
पूर्ण

अटल पूर्णांक btf_काष्ठा_resolve(काष्ठा btf_verअगरier_env *env,
			      स्थिर काष्ठा resolve_vertex *v)
अणु
	स्थिर काष्ठा btf_member *member;
	पूर्णांक err;
	u16 i;

	/* Beक्रमe जारी resolving the next_member,
	 * ensure the last member is indeed resolved to a
	 * type with size info.
	 */
	अगर (v->next_member) अणु
		स्थिर काष्ठा btf_type *last_member_type;
		स्थिर काष्ठा btf_member *last_member;
		u16 last_member_type_id;

		last_member = btf_type_member(v->t) + v->next_member - 1;
		last_member_type_id = last_member->type;
		अगर (WARN_ON_ONCE(!env_type_is_resolved(env,
						       last_member_type_id)))
			वापस -EINVAL;

		last_member_type = btf_type_by_id(env->btf,
						  last_member_type_id);
		अगर (btf_type_kflag(v->t))
			err = btf_type_ops(last_member_type)->check_kflag_member(env, v->t,
								last_member,
								last_member_type);
		अन्यथा
			err = btf_type_ops(last_member_type)->check_member(env, v->t,
								last_member,
								last_member_type);
		अगर (err)
			वापस err;
	पूर्ण

	क्रम_each_member_from(i, v->next_member, v->t, member) अणु
		u32 member_type_id = member->type;
		स्थिर काष्ठा btf_type *member_type = btf_type_by_id(env->btf,
								member_type_id);

		अगर (btf_type_nosize_or_null(member_type) ||
		    btf_type_is_resolve_source_only(member_type)) अणु
			btf_verअगरier_log_member(env, v->t, member,
						"Invalid member");
			वापस -EINVAL;
		पूर्ण

		अगर (!env_type_is_resolve_sink(env, member_type) &&
		    !env_type_is_resolved(env, member_type_id)) अणु
			env_stack_set_next_member(env, i + 1);
			वापस env_stack_push(env, member_type, member_type_id);
		पूर्ण

		अगर (btf_type_kflag(v->t))
			err = btf_type_ops(member_type)->check_kflag_member(env, v->t,
									    member,
									    member_type);
		अन्यथा
			err = btf_type_ops(member_type)->check_member(env, v->t,
								      member,
								      member_type);
		अगर (err)
			वापस err;
	पूर्ण

	env_stack_pop_resolved(env, 0, 0);

	वापस 0;
पूर्ण

अटल व्योम btf_काष्ठा_log(काष्ठा btf_verअगरier_env *env,
			   स्थिर काष्ठा btf_type *t)
अणु
	btf_verअगरier_log(env, "size=%u vlen=%u", t->size, btf_type_vlen(t));
पूर्ण

/* find 'struct bpf_spin_lock' in map value.
 * वापस >= 0 offset अगर found
 * and < 0 in हाल of error
 */
पूर्णांक btf_find_spin_lock(स्थिर काष्ठा btf *btf, स्थिर काष्ठा btf_type *t)
अणु
	स्थिर काष्ठा btf_member *member;
	u32 i, off = -ENOENT;

	अगर (!__btf_type_is_काष्ठा(t))
		वापस -EINVAL;

	क्रम_each_member(i, t, member) अणु
		स्थिर काष्ठा btf_type *member_type = btf_type_by_id(btf,
								    member->type);
		अगर (!__btf_type_is_काष्ठा(member_type))
			जारी;
		अगर (member_type->size != माप(काष्ठा bpf_spin_lock))
			जारी;
		अगर (म_भेद(__btf_name_by_offset(btf, member_type->name_off),
			   "bpf_spin_lock"))
			जारी;
		अगर (off != -ENOENT)
			/* only one 'struct bpf_spin_lock' is allowed */
			वापस -E2BIG;
		off = btf_member_bit_offset(t, member);
		अगर (off % 8)
			/* valid C code cannot generate such BTF */
			वापस -EINVAL;
		off /= 8;
		अगर (off % __alignof__(काष्ठा bpf_spin_lock))
			/* valid काष्ठा bpf_spin_lock will be 4 byte aligned */
			वापस -EINVAL;
	पूर्ण
	वापस off;
पूर्ण

अटल व्योम __btf_काष्ठा_show(स्थिर काष्ठा btf *btf, स्थिर काष्ठा btf_type *t,
			      u32 type_id, व्योम *data, u8 bits_offset,
			      काष्ठा btf_show *show)
अणु
	स्थिर काष्ठा btf_member *member;
	व्योम *safe_data;
	u32 i;

	safe_data = btf_show_start_काष्ठा_type(show, t, type_id, data);
	अगर (!safe_data)
		वापस;

	क्रम_each_member(i, t, member) अणु
		स्थिर काष्ठा btf_type *member_type = btf_type_by_id(btf,
								member->type);
		स्थिर काष्ठा btf_kind_operations *ops;
		u32 member_offset, bitfield_size;
		u32 bytes_offset;
		u8 bits8_offset;

		btf_show_start_member(show, member);

		member_offset = btf_member_bit_offset(t, member);
		bitfield_size = btf_member_bitfield_size(t, member);
		bytes_offset = BITS_ROUNDDOWN_BYTES(member_offset);
		bits8_offset = BITS_PER_BYTE_MASKED(member_offset);
		अगर (bitfield_size) अणु
			safe_data = btf_show_start_type(show, member_type,
							member->type,
							data + bytes_offset);
			अगर (safe_data)
				btf_bitfield_show(safe_data,
						  bits8_offset,
						  bitfield_size, show);
			btf_show_end_type(show);
		पूर्ण अन्यथा अणु
			ops = btf_type_ops(member_type);
			ops->show(btf, member_type, member->type,
				  data + bytes_offset, bits8_offset, show);
		पूर्ण

		btf_show_end_member(show);
	पूर्ण

	btf_show_end_काष्ठा_type(show);
पूर्ण

अटल व्योम btf_काष्ठा_show(स्थिर काष्ठा btf *btf, स्थिर काष्ठा btf_type *t,
			    u32 type_id, व्योम *data, u8 bits_offset,
			    काष्ठा btf_show *show)
अणु
	स्थिर काष्ठा btf_member *m = show->state.member;

	/*
	 * First check अगर any members would be shown (are non-zero).
	 * See comments above "struct btf_show" definition क्रम more
	 * details on how this works at a high-level.
	 */
	अगर (show->state.depth > 0 && !(show->flags & BTF_SHOW_ZERO)) अणु
		अगर (!show->state.depth_check) अणु
			show->state.depth_check = show->state.depth + 1;
			show->state.depth_to_show = 0;
		पूर्ण
		__btf_काष्ठा_show(btf, t, type_id, data, bits_offset, show);
		/* Restore saved member data here */
		show->state.member = m;
		अगर (show->state.depth_check != show->state.depth + 1)
			वापस;
		show->state.depth_check = 0;

		अगर (show->state.depth_to_show <= show->state.depth)
			वापस;
		/*
		 * Reaching here indicates we have recursed and found
		 * non-zero child values.
		 */
	पूर्ण

	__btf_काष्ठा_show(btf, t, type_id, data, bits_offset, show);
पूर्ण

अटल काष्ठा btf_kind_operations काष्ठा_ops = अणु
	.check_meta = btf_काष्ठा_check_meta,
	.resolve = btf_काष्ठा_resolve,
	.check_member = btf_काष्ठा_check_member,
	.check_kflag_member = btf_generic_check_kflag_member,
	.log_details = btf_काष्ठा_log,
	.show = btf_काष्ठा_show,
पूर्ण;

अटल पूर्णांक btf_क्रमागत_check_member(काष्ठा btf_verअगरier_env *env,
				 स्थिर काष्ठा btf_type *काष्ठा_type,
				 स्थिर काष्ठा btf_member *member,
				 स्थिर काष्ठा btf_type *member_type)
अणु
	u32 काष्ठा_bits_off = member->offset;
	u32 काष्ठा_size, bytes_offset;

	अगर (BITS_PER_BYTE_MASKED(काष्ठा_bits_off)) अणु
		btf_verअगरier_log_member(env, काष्ठा_type, member,
					"Member is not byte aligned");
		वापस -EINVAL;
	पूर्ण

	काष्ठा_size = काष्ठा_type->size;
	bytes_offset = BITS_ROUNDDOWN_BYTES(काष्ठा_bits_off);
	अगर (काष्ठा_size - bytes_offset < member_type->size) अणु
		btf_verअगरier_log_member(env, काष्ठा_type, member,
					"Member exceeds struct_size");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक btf_क्रमागत_check_kflag_member(काष्ठा btf_verअगरier_env *env,
				       स्थिर काष्ठा btf_type *काष्ठा_type,
				       स्थिर काष्ठा btf_member *member,
				       स्थिर काष्ठा btf_type *member_type)
अणु
	u32 काष्ठा_bits_off, nr_bits, bytes_end, काष्ठा_size;
	u32 पूर्णांक_bitsize = माप(पूर्णांक) * BITS_PER_BYTE;

	काष्ठा_bits_off = BTF_MEMBER_BIT_OFFSET(member->offset);
	nr_bits = BTF_MEMBER_BITFIELD_SIZE(member->offset);
	अगर (!nr_bits) अणु
		अगर (BITS_PER_BYTE_MASKED(काष्ठा_bits_off)) अणु
			btf_verअगरier_log_member(env, काष्ठा_type, member,
						"Member is not byte aligned");
			वापस -EINVAL;
		पूर्ण

		nr_bits = पूर्णांक_bitsize;
	पूर्ण अन्यथा अगर (nr_bits > पूर्णांक_bitsize) अणु
		btf_verअगरier_log_member(env, काष्ठा_type, member,
					"Invalid member bitfield_size");
		वापस -EINVAL;
	पूर्ण

	काष्ठा_size = काष्ठा_type->size;
	bytes_end = BITS_ROUNDUP_BYTES(काष्ठा_bits_off + nr_bits);
	अगर (काष्ठा_size < bytes_end) अणु
		btf_verअगरier_log_member(env, काष्ठा_type, member,
					"Member exceeds struct_size");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल s32 btf_क्रमागत_check_meta(काष्ठा btf_verअगरier_env *env,
			       स्थिर काष्ठा btf_type *t,
			       u32 meta_left)
अणु
	स्थिर काष्ठा btf_क्रमागत *क्रमागतs = btf_type_क्रमागत(t);
	काष्ठा btf *btf = env->btf;
	u16 i, nr_क्रमागतs;
	u32 meta_needed;

	nr_क्रमागतs = btf_type_vlen(t);
	meta_needed = nr_क्रमागतs * माप(*क्रमागतs);

	अगर (meta_left < meta_needed) अणु
		btf_verअगरier_log_basic(env, t,
				       "meta_left:%u meta_needed:%u",
				       meta_left, meta_needed);
		वापस -EINVAL;
	पूर्ण

	अगर (btf_type_kflag(t)) अणु
		btf_verअगरier_log_type(env, t, "Invalid btf_info kind_flag");
		वापस -EINVAL;
	पूर्ण

	अगर (t->size > 8 || !is_घातer_of_2(t->size)) अणु
		btf_verअगरier_log_type(env, t, "Unexpected size");
		वापस -EINVAL;
	पूर्ण

	/* क्रमागत type either no name or a valid one */
	अगर (t->name_off &&
	    !btf_name_valid_identअगरier(env->btf, t->name_off)) अणु
		btf_verअगरier_log_type(env, t, "Invalid name");
		वापस -EINVAL;
	पूर्ण

	btf_verअगरier_log_type(env, t, शून्य);

	क्रम (i = 0; i < nr_क्रमागतs; i++) अणु
		अगर (!btf_name_offset_valid(btf, क्रमागतs[i].name_off)) अणु
			btf_verअगरier_log(env, "\tInvalid name_offset:%u",
					 क्रमागतs[i].name_off);
			वापस -EINVAL;
		पूर्ण

		/* क्रमागत member must have a valid name */
		अगर (!क्रमागतs[i].name_off ||
		    !btf_name_valid_identअगरier(btf, क्रमागतs[i].name_off)) अणु
			btf_verअगरier_log_type(env, t, "Invalid name");
			वापस -EINVAL;
		पूर्ण

		अगर (env->log.level == BPF_LOG_KERNEL)
			जारी;
		btf_verअगरier_log(env, "\t%s val=%d\n",
				 __btf_name_by_offset(btf, क्रमागतs[i].name_off),
				 क्रमागतs[i].val);
	पूर्ण

	वापस meta_needed;
पूर्ण

अटल व्योम btf_क्रमागत_log(काष्ठा btf_verअगरier_env *env,
			 स्थिर काष्ठा btf_type *t)
अणु
	btf_verअगरier_log(env, "size=%u vlen=%u", t->size, btf_type_vlen(t));
पूर्ण

अटल व्योम btf_क्रमागत_show(स्थिर काष्ठा btf *btf, स्थिर काष्ठा btf_type *t,
			  u32 type_id, व्योम *data, u8 bits_offset,
			  काष्ठा btf_show *show)
अणु
	स्थिर काष्ठा btf_क्रमागत *क्रमागतs = btf_type_क्रमागत(t);
	u32 i, nr_क्रमागतs = btf_type_vlen(t);
	व्योम *safe_data;
	पूर्णांक v;

	safe_data = btf_show_start_type(show, t, type_id, data);
	अगर (!safe_data)
		वापस;

	v = *(पूर्णांक *)safe_data;

	क्रम (i = 0; i < nr_क्रमागतs; i++) अणु
		अगर (v != क्रमागतs[i].val)
			जारी;

		btf_show_type_value(show, "%s",
				    __btf_name_by_offset(btf,
							 क्रमागतs[i].name_off));

		btf_show_end_type(show);
		वापस;
	पूर्ण

	btf_show_type_value(show, "%d", v);
	btf_show_end_type(show);
पूर्ण

अटल काष्ठा btf_kind_operations क्रमागत_ops = अणु
	.check_meta = btf_क्रमागत_check_meta,
	.resolve = btf_df_resolve,
	.check_member = btf_क्रमागत_check_member,
	.check_kflag_member = btf_क्रमागत_check_kflag_member,
	.log_details = btf_क्रमागत_log,
	.show = btf_क्रमागत_show,
पूर्ण;

अटल s32 btf_func_proto_check_meta(काष्ठा btf_verअगरier_env *env,
				     स्थिर काष्ठा btf_type *t,
				     u32 meta_left)
अणु
	u32 meta_needed = btf_type_vlen(t) * माप(काष्ठा btf_param);

	अगर (meta_left < meta_needed) अणु
		btf_verअगरier_log_basic(env, t,
				       "meta_left:%u meta_needed:%u",
				       meta_left, meta_needed);
		वापस -EINVAL;
	पूर्ण

	अगर (t->name_off) अणु
		btf_verअगरier_log_type(env, t, "Invalid name");
		वापस -EINVAL;
	पूर्ण

	अगर (btf_type_kflag(t)) अणु
		btf_verअगरier_log_type(env, t, "Invalid btf_info kind_flag");
		वापस -EINVAL;
	पूर्ण

	btf_verअगरier_log_type(env, t, शून्य);

	वापस meta_needed;
पूर्ण

अटल व्योम btf_func_proto_log(काष्ठा btf_verअगरier_env *env,
			       स्थिर काष्ठा btf_type *t)
अणु
	स्थिर काष्ठा btf_param *args = (स्थिर काष्ठा btf_param *)(t + 1);
	u16 nr_args = btf_type_vlen(t), i;

	btf_verअगरier_log(env, "return=%u args=(", t->type);
	अगर (!nr_args) अणु
		btf_verअगरier_log(env, "void");
		जाओ करोne;
	पूर्ण

	अगर (nr_args == 1 && !args[0].type) अणु
		/* Only one vararg */
		btf_verअगरier_log(env, "vararg");
		जाओ करोne;
	पूर्ण

	btf_verअगरier_log(env, "%u %s", args[0].type,
			 __btf_name_by_offset(env->btf,
					      args[0].name_off));
	क्रम (i = 1; i < nr_args - 1; i++)
		btf_verअगरier_log(env, ", %u %s", args[i].type,
				 __btf_name_by_offset(env->btf,
						      args[i].name_off));

	अगर (nr_args > 1) अणु
		स्थिर काष्ठा btf_param *last_arg = &args[nr_args - 1];

		अगर (last_arg->type)
			btf_verअगरier_log(env, ", %u %s", last_arg->type,
					 __btf_name_by_offset(env->btf,
							      last_arg->name_off));
		अन्यथा
			btf_verअगरier_log(env, ", vararg");
	पूर्ण

करोne:
	btf_verअगरier_log(env, ")");
पूर्ण

अटल काष्ठा btf_kind_operations func_proto_ops = अणु
	.check_meta = btf_func_proto_check_meta,
	.resolve = btf_df_resolve,
	/*
	 * BTF_KIND_FUNC_PROTO cannot be directly referred by
	 * a काष्ठा's member.
	 *
	 * It should be a funciton poपूर्णांकer instead.
	 * (i.e. काष्ठा's member -> BTF_KIND_PTR -> BTF_KIND_FUNC_PROTO)
	 *
	 * Hence, there is no btf_func_check_member().
	 */
	.check_member = btf_df_check_member,
	.check_kflag_member = btf_df_check_kflag_member,
	.log_details = btf_func_proto_log,
	.show = btf_df_show,
पूर्ण;

अटल s32 btf_func_check_meta(काष्ठा btf_verअगरier_env *env,
			       स्थिर काष्ठा btf_type *t,
			       u32 meta_left)
अणु
	अगर (!t->name_off ||
	    !btf_name_valid_identअगरier(env->btf, t->name_off)) अणु
		btf_verअगरier_log_type(env, t, "Invalid name");
		वापस -EINVAL;
	पूर्ण

	अगर (btf_type_vlen(t) > BTF_FUNC_GLOBAL) अणु
		btf_verअगरier_log_type(env, t, "Invalid func linkage");
		वापस -EINVAL;
	पूर्ण

	अगर (btf_type_kflag(t)) अणु
		btf_verअगरier_log_type(env, t, "Invalid btf_info kind_flag");
		वापस -EINVAL;
	पूर्ण

	btf_verअगरier_log_type(env, t, शून्य);

	वापस 0;
पूर्ण

अटल काष्ठा btf_kind_operations func_ops = अणु
	.check_meta = btf_func_check_meta,
	.resolve = btf_df_resolve,
	.check_member = btf_df_check_member,
	.check_kflag_member = btf_df_check_kflag_member,
	.log_details = btf_ref_type_log,
	.show = btf_df_show,
पूर्ण;

अटल s32 btf_var_check_meta(काष्ठा btf_verअगरier_env *env,
			      स्थिर काष्ठा btf_type *t,
			      u32 meta_left)
अणु
	स्थिर काष्ठा btf_var *var;
	u32 meta_needed = माप(*var);

	अगर (meta_left < meta_needed) अणु
		btf_verअगरier_log_basic(env, t,
				       "meta_left:%u meta_needed:%u",
				       meta_left, meta_needed);
		वापस -EINVAL;
	पूर्ण

	अगर (btf_type_vlen(t)) अणु
		btf_verअगरier_log_type(env, t, "vlen != 0");
		वापस -EINVAL;
	पूर्ण

	अगर (btf_type_kflag(t)) अणु
		btf_verअगरier_log_type(env, t, "Invalid btf_info kind_flag");
		वापस -EINVAL;
	पूर्ण

	अगर (!t->name_off ||
	    !__btf_name_valid(env->btf, t->name_off, true)) अणु
		btf_verअगरier_log_type(env, t, "Invalid name");
		वापस -EINVAL;
	पूर्ण

	/* A var cannot be in type व्योम */
	अगर (!t->type || !BTF_TYPE_ID_VALID(t->type)) अणु
		btf_verअगरier_log_type(env, t, "Invalid type_id");
		वापस -EINVAL;
	पूर्ण

	var = btf_type_var(t);
	अगर (var->linkage != BTF_VAR_STATIC &&
	    var->linkage != BTF_VAR_GLOBAL_ALLOCATED) अणु
		btf_verअगरier_log_type(env, t, "Linkage not supported");
		वापस -EINVAL;
	पूर्ण

	btf_verअगरier_log_type(env, t, शून्य);

	वापस meta_needed;
पूर्ण

अटल व्योम btf_var_log(काष्ठा btf_verअगरier_env *env, स्थिर काष्ठा btf_type *t)
अणु
	स्थिर काष्ठा btf_var *var = btf_type_var(t);

	btf_verअगरier_log(env, "type_id=%u linkage=%u", t->type, var->linkage);
पूर्ण

अटल स्थिर काष्ठा btf_kind_operations var_ops = अणु
	.check_meta		= btf_var_check_meta,
	.resolve		= btf_var_resolve,
	.check_member		= btf_df_check_member,
	.check_kflag_member	= btf_df_check_kflag_member,
	.log_details		= btf_var_log,
	.show			= btf_var_show,
पूर्ण;

अटल s32 btf_datasec_check_meta(काष्ठा btf_verअगरier_env *env,
				  स्थिर काष्ठा btf_type *t,
				  u32 meta_left)
अणु
	स्थिर काष्ठा btf_var_secinfo *vsi;
	u64 last_vsi_end_off = 0, sum = 0;
	u32 i, meta_needed;

	meta_needed = btf_type_vlen(t) * माप(*vsi);
	अगर (meta_left < meta_needed) अणु
		btf_verअगरier_log_basic(env, t,
				       "meta_left:%u meta_needed:%u",
				       meta_left, meta_needed);
		वापस -EINVAL;
	पूर्ण

	अगर (!t->size) अणु
		btf_verअगरier_log_type(env, t, "size == 0");
		वापस -EINVAL;
	पूर्ण

	अगर (btf_type_kflag(t)) अणु
		btf_verअगरier_log_type(env, t, "Invalid btf_info kind_flag");
		वापस -EINVAL;
	पूर्ण

	अगर (!t->name_off ||
	    !btf_name_valid_section(env->btf, t->name_off)) अणु
		btf_verअगरier_log_type(env, t, "Invalid name");
		वापस -EINVAL;
	पूर्ण

	btf_verअगरier_log_type(env, t, शून्य);

	क्रम_each_vsi(i, t, vsi) अणु
		/* A var cannot be in type व्योम */
		अगर (!vsi->type || !BTF_TYPE_ID_VALID(vsi->type)) अणु
			btf_verअगरier_log_vsi(env, t, vsi,
					     "Invalid type_id");
			वापस -EINVAL;
		पूर्ण

		अगर (vsi->offset < last_vsi_end_off || vsi->offset >= t->size) अणु
			btf_verअगरier_log_vsi(env, t, vsi,
					     "Invalid offset");
			वापस -EINVAL;
		पूर्ण

		अगर (!vsi->size || vsi->size > t->size) अणु
			btf_verअगरier_log_vsi(env, t, vsi,
					     "Invalid size");
			वापस -EINVAL;
		पूर्ण

		last_vsi_end_off = vsi->offset + vsi->size;
		अगर (last_vsi_end_off > t->size) अणु
			btf_verअगरier_log_vsi(env, t, vsi,
					     "Invalid offset+size");
			वापस -EINVAL;
		पूर्ण

		btf_verअगरier_log_vsi(env, t, vsi, शून्य);
		sum += vsi->size;
	पूर्ण

	अगर (t->size < sum) अणु
		btf_verअगरier_log_type(env, t, "Invalid btf_info size");
		वापस -EINVAL;
	पूर्ण

	वापस meta_needed;
पूर्ण

अटल पूर्णांक btf_datasec_resolve(काष्ठा btf_verअगरier_env *env,
			       स्थिर काष्ठा resolve_vertex *v)
अणु
	स्थिर काष्ठा btf_var_secinfo *vsi;
	काष्ठा btf *btf = env->btf;
	u16 i;

	क्रम_each_vsi_from(i, v->next_member, v->t, vsi) अणु
		u32 var_type_id = vsi->type, type_id, type_size = 0;
		स्थिर काष्ठा btf_type *var_type = btf_type_by_id(env->btf,
								 var_type_id);
		अगर (!var_type || !btf_type_is_var(var_type)) अणु
			btf_verअगरier_log_vsi(env, v->t, vsi,
					     "Not a VAR kind member");
			वापस -EINVAL;
		पूर्ण

		अगर (!env_type_is_resolve_sink(env, var_type) &&
		    !env_type_is_resolved(env, var_type_id)) अणु
			env_stack_set_next_member(env, i + 1);
			वापस env_stack_push(env, var_type, var_type_id);
		पूर्ण

		type_id = var_type->type;
		अगर (!btf_type_id_size(btf, &type_id, &type_size)) अणु
			btf_verअगरier_log_vsi(env, v->t, vsi, "Invalid type");
			वापस -EINVAL;
		पूर्ण

		अगर (vsi->size < type_size) अणु
			btf_verअगरier_log_vsi(env, v->t, vsi, "Invalid size");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	env_stack_pop_resolved(env, 0, 0);
	वापस 0;
पूर्ण

अटल व्योम btf_datasec_log(काष्ठा btf_verअगरier_env *env,
			    स्थिर काष्ठा btf_type *t)
अणु
	btf_verअगरier_log(env, "size=%u vlen=%u", t->size, btf_type_vlen(t));
पूर्ण

अटल व्योम btf_datasec_show(स्थिर काष्ठा btf *btf,
			     स्थिर काष्ठा btf_type *t, u32 type_id,
			     व्योम *data, u8 bits_offset,
			     काष्ठा btf_show *show)
अणु
	स्थिर काष्ठा btf_var_secinfo *vsi;
	स्थिर काष्ठा btf_type *var;
	u32 i;

	अगर (!btf_show_start_type(show, t, type_id, data))
		वापस;

	btf_show_type_value(show, "section (\"%s\") = {",
			    __btf_name_by_offset(btf, t->name_off));
	क्रम_each_vsi(i, t, vsi) अणु
		var = btf_type_by_id(btf, vsi->type);
		अगर (i)
			btf_show(show, ",");
		btf_type_ops(var)->show(btf, var, vsi->type,
					data + vsi->offset, bits_offset, show);
	पूर्ण
	btf_show_end_type(show);
पूर्ण

अटल स्थिर काष्ठा btf_kind_operations datasec_ops = अणु
	.check_meta		= btf_datasec_check_meta,
	.resolve		= btf_datasec_resolve,
	.check_member		= btf_df_check_member,
	.check_kflag_member	= btf_df_check_kflag_member,
	.log_details		= btf_datasec_log,
	.show			= btf_datasec_show,
पूर्ण;

अटल s32 btf_भग्न_check_meta(काष्ठा btf_verअगरier_env *env,
				स्थिर काष्ठा btf_type *t,
				u32 meta_left)
अणु
	अगर (btf_type_vlen(t)) अणु
		btf_verअगरier_log_type(env, t, "vlen != 0");
		वापस -EINVAL;
	पूर्ण

	अगर (btf_type_kflag(t)) अणु
		btf_verअगरier_log_type(env, t, "Invalid btf_info kind_flag");
		वापस -EINVAL;
	पूर्ण

	अगर (t->size != 2 && t->size != 4 && t->size != 8 && t->size != 12 &&
	    t->size != 16) अणु
		btf_verअगरier_log_type(env, t, "Invalid type_size");
		वापस -EINVAL;
	पूर्ण

	btf_verअगरier_log_type(env, t, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक btf_भग्न_check_member(काष्ठा btf_verअगरier_env *env,
				  स्थिर काष्ठा btf_type *काष्ठा_type,
				  स्थिर काष्ठा btf_member *member,
				  स्थिर काष्ठा btf_type *member_type)
अणु
	u64 start_offset_bytes;
	u64 end_offset_bytes;
	u64 misalign_bits;
	u64 align_bytes;
	u64 align_bits;

	/* Dअगरferent architectures have dअगरferent alignment requirements, so
	 * here we check only क्रम the reasonable minimum. This way we ensure
	 * that types after CO-RE can pass the kernel BTF verअगरier.
	 */
	align_bytes = min_t(u64, माप(व्योम *), member_type->size);
	align_bits = align_bytes * BITS_PER_BYTE;
	भाग64_u64_rem(member->offset, align_bits, &misalign_bits);
	अगर (misalign_bits) अणु
		btf_verअगरier_log_member(env, काष्ठा_type, member,
					"Member is not properly aligned");
		वापस -EINVAL;
	पूर्ण

	start_offset_bytes = member->offset / BITS_PER_BYTE;
	end_offset_bytes = start_offset_bytes + member_type->size;
	अगर (end_offset_bytes > काष्ठा_type->size) अणु
		btf_verअगरier_log_member(env, काष्ठा_type, member,
					"Member exceeds struct_size");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम btf_भग्न_log(काष्ठा btf_verअगरier_env *env,
			  स्थिर काष्ठा btf_type *t)
अणु
	btf_verअगरier_log(env, "size=%u", t->size);
पूर्ण

अटल स्थिर काष्ठा btf_kind_operations भग्न_ops = अणु
	.check_meta = btf_भग्न_check_meta,
	.resolve = btf_df_resolve,
	.check_member = btf_भग्न_check_member,
	.check_kflag_member = btf_generic_check_kflag_member,
	.log_details = btf_भग्न_log,
	.show = btf_df_show,
पूर्ण;

अटल पूर्णांक btf_func_proto_check(काष्ठा btf_verअगरier_env *env,
				स्थिर काष्ठा btf_type *t)
अणु
	स्थिर काष्ठा btf_type *ret_type;
	स्थिर काष्ठा btf_param *args;
	स्थिर काष्ठा btf *btf;
	u16 nr_args, i;
	पूर्णांक err;

	btf = env->btf;
	args = (स्थिर काष्ठा btf_param *)(t + 1);
	nr_args = btf_type_vlen(t);

	/* Check func वापस type which could be "void" (t->type == 0) */
	अगर (t->type) अणु
		u32 ret_type_id = t->type;

		ret_type = btf_type_by_id(btf, ret_type_id);
		अगर (!ret_type) अणु
			btf_verअगरier_log_type(env, t, "Invalid return type");
			वापस -EINVAL;
		पूर्ण

		अगर (btf_type_needs_resolve(ret_type) &&
		    !env_type_is_resolved(env, ret_type_id)) अणु
			err = btf_resolve(env, ret_type, ret_type_id);
			अगर (err)
				वापस err;
		पूर्ण

		/* Ensure the वापस type is a type that has a size */
		अगर (!btf_type_id_size(btf, &ret_type_id, शून्य)) अणु
			btf_verअगरier_log_type(env, t, "Invalid return type");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!nr_args)
		वापस 0;

	/* Last func arg type_id could be 0 अगर it is a vararg */
	अगर (!args[nr_args - 1].type) अणु
		अगर (args[nr_args - 1].name_off) अणु
			btf_verअगरier_log_type(env, t, "Invalid arg#%u",
					      nr_args);
			वापस -EINVAL;
		पूर्ण
		nr_args--;
	पूर्ण

	err = 0;
	क्रम (i = 0; i < nr_args; i++) अणु
		स्थिर काष्ठा btf_type *arg_type;
		u32 arg_type_id;

		arg_type_id = args[i].type;
		arg_type = btf_type_by_id(btf, arg_type_id);
		अगर (!arg_type) अणु
			btf_verअगरier_log_type(env, t, "Invalid arg#%u", i + 1);
			err = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (args[i].name_off &&
		    (!btf_name_offset_valid(btf, args[i].name_off) ||
		     !btf_name_valid_identअगरier(btf, args[i].name_off))) अणु
			btf_verअगरier_log_type(env, t,
					      "Invalid arg#%u", i + 1);
			err = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (btf_type_needs_resolve(arg_type) &&
		    !env_type_is_resolved(env, arg_type_id)) अणु
			err = btf_resolve(env, arg_type, arg_type_id);
			अगर (err)
				अवरोध;
		पूर्ण

		अगर (!btf_type_id_size(btf, &arg_type_id, शून्य)) अणु
			btf_verअगरier_log_type(env, t, "Invalid arg#%u", i + 1);
			err = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक btf_func_check(काष्ठा btf_verअगरier_env *env,
			  स्थिर काष्ठा btf_type *t)
अणु
	स्थिर काष्ठा btf_type *proto_type;
	स्थिर काष्ठा btf_param *args;
	स्थिर काष्ठा btf *btf;
	u16 nr_args, i;

	btf = env->btf;
	proto_type = btf_type_by_id(btf, t->type);

	अगर (!proto_type || !btf_type_is_func_proto(proto_type)) अणु
		btf_verअगरier_log_type(env, t, "Invalid type_id");
		वापस -EINVAL;
	पूर्ण

	args = (स्थिर काष्ठा btf_param *)(proto_type + 1);
	nr_args = btf_type_vlen(proto_type);
	क्रम (i = 0; i < nr_args; i++) अणु
		अगर (!args[i].name_off && args[i].type) अणु
			btf_verअगरier_log_type(env, t, "Invalid arg#%u", i + 1);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा btf_kind_operations * स्थिर kind_ops[NR_BTF_KINDS] = अणु
	[BTF_KIND_INT] = &पूर्णांक_ops,
	[BTF_KIND_PTR] = &ptr_ops,
	[BTF_KIND_ARRAY] = &array_ops,
	[BTF_KIND_STRUCT] = &काष्ठा_ops,
	[BTF_KIND_UNION] = &काष्ठा_ops,
	[BTF_KIND_ENUM] = &क्रमागत_ops,
	[BTF_KIND_FWD] = &fwd_ops,
	[BTF_KIND_TYPEDEF] = &modअगरier_ops,
	[BTF_KIND_VOLATILE] = &modअगरier_ops,
	[BTF_KIND_CONST] = &modअगरier_ops,
	[BTF_KIND_RESTRICT] = &modअगरier_ops,
	[BTF_KIND_FUNC] = &func_ops,
	[BTF_KIND_FUNC_PROTO] = &func_proto_ops,
	[BTF_KIND_VAR] = &var_ops,
	[BTF_KIND_DATASEC] = &datasec_ops,
	[BTF_KIND_FLOAT] = &भग्न_ops,
पूर्ण;

अटल s32 btf_check_meta(काष्ठा btf_verअगरier_env *env,
			  स्थिर काष्ठा btf_type *t,
			  u32 meta_left)
अणु
	u32 saved_meta_left = meta_left;
	s32 var_meta_size;

	अगर (meta_left < माप(*t)) अणु
		btf_verअगरier_log(env, "[%u] meta_left:%u meta_needed:%zu",
				 env->log_type_id, meta_left, माप(*t));
		वापस -EINVAL;
	पूर्ण
	meta_left -= माप(*t);

	अगर (t->info & ~BTF_INFO_MASK) अणु
		btf_verअगरier_log(env, "[%u] Invalid btf_info:%x",
				 env->log_type_id, t->info);
		वापस -EINVAL;
	पूर्ण

	अगर (BTF_INFO_KIND(t->info) > BTF_KIND_MAX ||
	    BTF_INFO_KIND(t->info) == BTF_KIND_UNKN) अणु
		btf_verअगरier_log(env, "[%u] Invalid kind:%u",
				 env->log_type_id, BTF_INFO_KIND(t->info));
		वापस -EINVAL;
	पूर्ण

	अगर (!btf_name_offset_valid(env->btf, t->name_off)) अणु
		btf_verअगरier_log(env, "[%u] Invalid name_offset:%u",
				 env->log_type_id, t->name_off);
		वापस -EINVAL;
	पूर्ण

	var_meta_size = btf_type_ops(t)->check_meta(env, t, meta_left);
	अगर (var_meta_size < 0)
		वापस var_meta_size;

	meta_left -= var_meta_size;

	वापस saved_meta_left - meta_left;
पूर्ण

अटल पूर्णांक btf_check_all_metas(काष्ठा btf_verअगरier_env *env)
अणु
	काष्ठा btf *btf = env->btf;
	काष्ठा btf_header *hdr;
	व्योम *cur, *end;

	hdr = &btf->hdr;
	cur = btf->nohdr_data + hdr->type_off;
	end = cur + hdr->type_len;

	env->log_type_id = btf->base_btf ? btf->start_id : 1;
	जबतक (cur < end) अणु
		काष्ठा btf_type *t = cur;
		s32 meta_size;

		meta_size = btf_check_meta(env, t, end - cur);
		अगर (meta_size < 0)
			वापस meta_size;

		btf_add_type(env, t);
		cur += meta_size;
		env->log_type_id++;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool btf_resolve_valid(काष्ठा btf_verअगरier_env *env,
			      स्थिर काष्ठा btf_type *t,
			      u32 type_id)
अणु
	काष्ठा btf *btf = env->btf;

	अगर (!env_type_is_resolved(env, type_id))
		वापस false;

	अगर (btf_type_is_काष्ठा(t) || btf_type_is_datasec(t))
		वापस !btf_resolved_type_id(btf, type_id) &&
		       !btf_resolved_type_size(btf, type_id);

	अगर (btf_type_is_modअगरier(t) || btf_type_is_ptr(t) ||
	    btf_type_is_var(t)) अणु
		t = btf_type_id_resolve(btf, &type_id);
		वापस t &&
		       !btf_type_is_modअगरier(t) &&
		       !btf_type_is_var(t) &&
		       !btf_type_is_datasec(t);
	पूर्ण

	अगर (btf_type_is_array(t)) अणु
		स्थिर काष्ठा btf_array *array = btf_type_array(t);
		स्थिर काष्ठा btf_type *elem_type;
		u32 elem_type_id = array->type;
		u32 elem_size;

		elem_type = btf_type_id_size(btf, &elem_type_id, &elem_size);
		वापस elem_type && !btf_type_is_modअगरier(elem_type) &&
			(array->nelems * elem_size ==
			 btf_resolved_type_size(btf, type_id));
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक btf_resolve(काष्ठा btf_verअगरier_env *env,
		       स्थिर काष्ठा btf_type *t, u32 type_id)
अणु
	u32 save_log_type_id = env->log_type_id;
	स्थिर काष्ठा resolve_vertex *v;
	पूर्णांक err = 0;

	env->resolve_mode = RESOLVE_TBD;
	env_stack_push(env, t, type_id);
	जबतक (!err && (v = env_stack_peak(env))) अणु
		env->log_type_id = v->type_id;
		err = btf_type_ops(v->t)->resolve(env, v);
	पूर्ण

	env->log_type_id = type_id;
	अगर (err == -E2BIG) अणु
		btf_verअगरier_log_type(env, t,
				      "Exceeded max resolving depth:%u",
				      MAX_RESOLVE_DEPTH);
	पूर्ण अन्यथा अगर (err == -EEXIST) अणु
		btf_verअगरier_log_type(env, t, "Loop detected");
	पूर्ण

	/* Final sanity check */
	अगर (!err && !btf_resolve_valid(env, t, type_id)) अणु
		btf_verअगरier_log_type(env, t, "Invalid resolve state");
		err = -EINVAL;
	पूर्ण

	env->log_type_id = save_log_type_id;
	वापस err;
पूर्ण

अटल पूर्णांक btf_check_all_types(काष्ठा btf_verअगरier_env *env)
अणु
	काष्ठा btf *btf = env->btf;
	स्थिर काष्ठा btf_type *t;
	u32 type_id, i;
	पूर्णांक err;

	err = env_resolve_init(env);
	अगर (err)
		वापस err;

	env->phase++;
	क्रम (i = btf->base_btf ? 0 : 1; i < btf->nr_types; i++) अणु
		type_id = btf->start_id + i;
		t = btf_type_by_id(btf, type_id);

		env->log_type_id = type_id;
		अगर (btf_type_needs_resolve(t) &&
		    !env_type_is_resolved(env, type_id)) अणु
			err = btf_resolve(env, t, type_id);
			अगर (err)
				वापस err;
		पूर्ण

		अगर (btf_type_is_func_proto(t)) अणु
			err = btf_func_proto_check(env, t);
			अगर (err)
				वापस err;
		पूर्ण

		अगर (btf_type_is_func(t)) अणु
			err = btf_func_check(env, t);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक btf_parse_type_sec(काष्ठा btf_verअगरier_env *env)
अणु
	स्थिर काष्ठा btf_header *hdr = &env->btf->hdr;
	पूर्णांक err;

	/* Type section must align to 4 bytes */
	अगर (hdr->type_off & (माप(u32) - 1)) अणु
		btf_verअगरier_log(env, "Unaligned type_off");
		वापस -EINVAL;
	पूर्ण

	अगर (!env->btf->base_btf && !hdr->type_len) अणु
		btf_verअगरier_log(env, "No type found");
		वापस -EINVAL;
	पूर्ण

	err = btf_check_all_metas(env);
	अगर (err)
		वापस err;

	वापस btf_check_all_types(env);
पूर्ण

अटल पूर्णांक btf_parse_str_sec(काष्ठा btf_verअगरier_env *env)
अणु
	स्थिर काष्ठा btf_header *hdr;
	काष्ठा btf *btf = env->btf;
	स्थिर अक्षर *start, *end;

	hdr = &btf->hdr;
	start = btf->nohdr_data + hdr->str_off;
	end = start + hdr->str_len;

	अगर (end != btf->data + btf->data_size) अणु
		btf_verअगरier_log(env, "String section is not at the end");
		वापस -EINVAL;
	पूर्ण

	btf->strings = start;

	अगर (btf->base_btf && !hdr->str_len)
		वापस 0;
	अगर (!hdr->str_len || hdr->str_len - 1 > BTF_MAX_NAME_OFFSET || end[-1]) अणु
		btf_verअगरier_log(env, "Invalid string section");
		वापस -EINVAL;
	पूर्ण
	अगर (!btf->base_btf && start[0]) अणु
		btf_verअगरier_log(env, "Invalid string section");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर माप_प्रकार btf_sec_info_offset[] = अणु
	दुरत्व(काष्ठा btf_header, type_off),
	दुरत्व(काष्ठा btf_header, str_off),
पूर्ण;

अटल पूर्णांक btf_sec_info_cmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा btf_sec_info *x = a;
	स्थिर काष्ठा btf_sec_info *y = b;

	वापस (पूर्णांक)(x->off - y->off) ? : (पूर्णांक)(x->len - y->len);
पूर्ण

अटल पूर्णांक btf_check_sec_info(काष्ठा btf_verअगरier_env *env,
			      u32 btf_data_size)
अणु
	काष्ठा btf_sec_info secs[ARRAY_SIZE(btf_sec_info_offset)];
	u32 total, expected_total, i;
	स्थिर काष्ठा btf_header *hdr;
	स्थिर काष्ठा btf *btf;

	btf = env->btf;
	hdr = &btf->hdr;

	/* Populate the secs from hdr */
	क्रम (i = 0; i < ARRAY_SIZE(btf_sec_info_offset); i++)
		secs[i] = *(काष्ठा btf_sec_info *)((व्योम *)hdr +
						   btf_sec_info_offset[i]);

	sort(secs, ARRAY_SIZE(btf_sec_info_offset),
	     माप(काष्ठा btf_sec_info), btf_sec_info_cmp, शून्य);

	/* Check क्रम gaps and overlap among sections */
	total = 0;
	expected_total = btf_data_size - hdr->hdr_len;
	क्रम (i = 0; i < ARRAY_SIZE(btf_sec_info_offset); i++) अणु
		अगर (expected_total < secs[i].off) अणु
			btf_verअगरier_log(env, "Invalid section offset");
			वापस -EINVAL;
		पूर्ण
		अगर (total < secs[i].off) अणु
			/* gap */
			btf_verअगरier_log(env, "Unsupported section found");
			वापस -EINVAL;
		पूर्ण
		अगर (total > secs[i].off) अणु
			btf_verअगरier_log(env, "Section overlap found");
			वापस -EINVAL;
		पूर्ण
		अगर (expected_total - total < secs[i].len) अणु
			btf_verअगरier_log(env,
					 "Total section length too long");
			वापस -EINVAL;
		पूर्ण
		total += secs[i].len;
	पूर्ण

	/* There is data other than hdr and known sections */
	अगर (expected_total != total) अणु
		btf_verअगरier_log(env, "Unsupported section found");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक btf_parse_hdr(काष्ठा btf_verअगरier_env *env)
अणु
	u32 hdr_len, hdr_copy, btf_data_size;
	स्थिर काष्ठा btf_header *hdr;
	काष्ठा btf *btf;
	पूर्णांक err;

	btf = env->btf;
	btf_data_size = btf->data_size;

	अगर (btf_data_size <
	    दुरत्व(काष्ठा btf_header, hdr_len) + माप(hdr->hdr_len)) अणु
		btf_verअगरier_log(env, "hdr_len not found");
		वापस -EINVAL;
	पूर्ण

	hdr = btf->data;
	hdr_len = hdr->hdr_len;
	अगर (btf_data_size < hdr_len) अणु
		btf_verअगरier_log(env, "btf_header not found");
		वापस -EINVAL;
	पूर्ण

	/* Ensure the unsupported header fields are zero */
	अगर (hdr_len > माप(btf->hdr)) अणु
		u8 *expected_zero = btf->data + माप(btf->hdr);
		u8 *end = btf->data + hdr_len;

		क्रम (; expected_zero < end; expected_zero++) अणु
			अगर (*expected_zero) अणु
				btf_verअगरier_log(env, "Unsupported btf_header");
				वापस -E2BIG;
			पूर्ण
		पूर्ण
	पूर्ण

	hdr_copy = min_t(u32, hdr_len, माप(btf->hdr));
	स_नकल(&btf->hdr, btf->data, hdr_copy);

	hdr = &btf->hdr;

	btf_verअगरier_log_hdr(env, btf_data_size);

	अगर (hdr->magic != BTF_MAGIC) अणु
		btf_verअगरier_log(env, "Invalid magic");
		वापस -EINVAL;
	पूर्ण

	अगर (hdr->version != BTF_VERSION) अणु
		btf_verअगरier_log(env, "Unsupported version");
		वापस -ENOTSUPP;
	पूर्ण

	अगर (hdr->flags) अणु
		btf_verअगरier_log(env, "Unsupported flags");
		वापस -ENOTSUPP;
	पूर्ण

	अगर (!btf->base_btf && btf_data_size == hdr->hdr_len) अणु
		btf_verअगरier_log(env, "No data");
		वापस -EINVAL;
	पूर्ण

	err = btf_check_sec_info(env, btf_data_size);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल काष्ठा btf *btf_parse(व्योम __user *btf_data, u32 btf_data_size,
			     u32 log_level, अक्षर __user *log_ubuf, u32 log_size)
अणु
	काष्ठा btf_verअगरier_env *env = शून्य;
	काष्ठा bpf_verअगरier_log *log;
	काष्ठा btf *btf = शून्य;
	u8 *data;
	पूर्णांक err;

	अगर (btf_data_size > BTF_MAX_SIZE)
		वापस ERR_PTR(-E2BIG);

	env = kzalloc(माप(*env), GFP_KERNEL | __GFP_NOWARN);
	अगर (!env)
		वापस ERR_PTR(-ENOMEM);

	log = &env->log;
	अगर (log_level || log_ubuf || log_size) अणु
		/* user requested verbose verअगरier output
		 * and supplied buffer to store the verअगरication trace
		 */
		log->level = log_level;
		log->ubuf = log_ubuf;
		log->len_total = log_size;

		/* log attributes have to be sane */
		अगर (log->len_total < 128 || log->len_total > अच_पूर्णांक_उच्च >> 8 ||
		    !log->level || !log->ubuf) अणु
			err = -EINVAL;
			जाओ errout;
		पूर्ण
	पूर्ण

	btf = kzalloc(माप(*btf), GFP_KERNEL | __GFP_NOWARN);
	अगर (!btf) अणु
		err = -ENOMEM;
		जाओ errout;
	पूर्ण
	env->btf = btf;

	data = kvदो_स्मृति(btf_data_size, GFP_KERNEL | __GFP_NOWARN);
	अगर (!data) अणु
		err = -ENOMEM;
		जाओ errout;
	पूर्ण

	btf->data = data;
	btf->data_size = btf_data_size;

	अगर (copy_from_user(data, btf_data, btf_data_size)) अणु
		err = -EFAULT;
		जाओ errout;
	पूर्ण

	err = btf_parse_hdr(env);
	अगर (err)
		जाओ errout;

	btf->nohdr_data = btf->data + btf->hdr.hdr_len;

	err = btf_parse_str_sec(env);
	अगर (err)
		जाओ errout;

	err = btf_parse_type_sec(env);
	अगर (err)
		जाओ errout;

	अगर (log->level && bpf_verअगरier_log_full(log)) अणु
		err = -ENOSPC;
		जाओ errout;
	पूर्ण

	btf_verअगरier_env_मुक्त(env);
	refcount_set(&btf->refcnt, 1);
	वापस btf;

errout:
	btf_verअगरier_env_मुक्त(env);
	अगर (btf)
		btf_मुक्त(btf);
	वापस ERR_PTR(err);
पूर्ण

बाह्य अक्षर __weak __start_BTF[];
बाह्य अक्षर __weak __stop_BTF[];
बाह्य काष्ठा btf *btf_vmlinux;

#घोषणा BPF_MAP_TYPE(_id, _ops)
#घोषणा BPF_LINK_TYPE(_id, _name)
अटल जोड़ अणु
	काष्ठा bpf_ctx_convert अणु
#घोषणा BPF_PROG_TYPE(_id, _name, prog_ctx_type, kern_ctx_type) \
	prog_ctx_type _id##_prog; \
	kern_ctx_type _id##_kern;
#समावेश <linux/bpf_types.h>
#अघोषित BPF_PROG_TYPE
	पूर्ण *__t;
	/* 't' is written once under lock. Read many बार. */
	स्थिर काष्ठा btf_type *t;
पूर्ण bpf_ctx_convert;
क्रमागत अणु
#घोषणा BPF_PROG_TYPE(_id, _name, prog_ctx_type, kern_ctx_type) \
	__ctx_convert##_id,
#समावेश <linux/bpf_types.h>
#अघोषित BPF_PROG_TYPE
	__ctx_convert_unused, /* to aव्योम empty क्रमागत in extreme .config */
पूर्ण;
अटल u8 bpf_ctx_convert_map[] = अणु
#घोषणा BPF_PROG_TYPE(_id, _name, prog_ctx_type, kern_ctx_type) \
	[_id] = __ctx_convert##_id,
#समावेश <linux/bpf_types.h>
#अघोषित BPF_PROG_TYPE
	0, /* aव्योम empty array */
पूर्ण;
#अघोषित BPF_MAP_TYPE
#अघोषित BPF_LINK_TYPE

अटल स्थिर काष्ठा btf_member *
btf_get_prog_ctx_type(काष्ठा bpf_verअगरier_log *log, स्थिर काष्ठा btf *btf,
		      स्थिर काष्ठा btf_type *t, क्रमागत bpf_prog_type prog_type,
		      पूर्णांक arg)
अणु
	स्थिर काष्ठा btf_type *conv_काष्ठा;
	स्थिर काष्ठा btf_type *ctx_काष्ठा;
	स्थिर काष्ठा btf_member *ctx_type;
	स्थिर अक्षर *tname, *ctx_tname;

	conv_काष्ठा = bpf_ctx_convert.t;
	अगर (!conv_काष्ठा) अणु
		bpf_log(log, "btf_vmlinux is malformed\n");
		वापस शून्य;
	पूर्ण
	t = btf_type_by_id(btf, t->type);
	जबतक (btf_type_is_modअगरier(t))
		t = btf_type_by_id(btf, t->type);
	अगर (!btf_type_is_काष्ठा(t)) अणु
		/* Only poपूर्णांकer to काष्ठा is supported क्रम now.
		 * That means that BPF_PROG_TYPE_TRACEPOINT with BTF
		 * is not supported yet.
		 * BPF_PROG_TYPE_RAW_TRACEPOINT is fine.
		 */
		वापस शून्य;
	पूर्ण
	tname = btf_name_by_offset(btf, t->name_off);
	अगर (!tname) अणु
		bpf_log(log, "arg#%d struct doesn't have a name\n", arg);
		वापस शून्य;
	पूर्ण
	/* prog_type is valid bpf program type. No need क्रम bounds check. */
	ctx_type = btf_type_member(conv_काष्ठा) + bpf_ctx_convert_map[prog_type] * 2;
	/* ctx_काष्ठा is a poपूर्णांकer to prog_ctx_type in vmlinux.
	 * Like 'struct __sk_buff'
	 */
	ctx_काष्ठा = btf_type_by_id(btf_vmlinux, ctx_type->type);
	अगर (!ctx_काष्ठा)
		/* should not happen */
		वापस शून्य;
	ctx_tname = btf_name_by_offset(btf_vmlinux, ctx_काष्ठा->name_off);
	अगर (!ctx_tname) अणु
		/* should not happen */
		bpf_log(log, "Please fix kernel include/linux/bpf_types.h\n");
		वापस शून्य;
	पूर्ण
	/* only compare that prog's ctx type name is the same as
	 * kernel expects. No need to compare field by field.
	 * It's ok क्रम bpf prog to करो:
	 * काष्ठा __sk_buff अणुपूर्ण;
	 * पूर्णांक socket_filter_bpf_prog(काष्ठा __sk_buff *skb)
	 * अणु // no fields of skb are ever used पूर्ण
	 */
	अगर (म_भेद(ctx_tname, tname))
		वापस शून्य;
	वापस ctx_type;
पूर्ण

अटल स्थिर काष्ठा bpf_map_ops * स्थिर btf_vmlinux_map_ops[] = अणु
#घोषणा BPF_PROG_TYPE(_id, _name, prog_ctx_type, kern_ctx_type)
#घोषणा BPF_LINK_TYPE(_id, _name)
#घोषणा BPF_MAP_TYPE(_id, _ops) \
	[_id] = &_ops,
#समावेश <linux/bpf_types.h>
#अघोषित BPF_PROG_TYPE
#अघोषित BPF_LINK_TYPE
#अघोषित BPF_MAP_TYPE
पूर्ण;

अटल पूर्णांक btf_vmlinux_map_ids_init(स्थिर काष्ठा btf *btf,
				    काष्ठा bpf_verअगरier_log *log)
अणु
	स्थिर काष्ठा bpf_map_ops *ops;
	पूर्णांक i, btf_id;

	क्रम (i = 0; i < ARRAY_SIZE(btf_vmlinux_map_ops); ++i) अणु
		ops = btf_vmlinux_map_ops[i];
		अगर (!ops || (!ops->map_btf_name && !ops->map_btf_id))
			जारी;
		अगर (!ops->map_btf_name || !ops->map_btf_id) अणु
			bpf_log(log, "map type %d is misconfigured\n", i);
			वापस -EINVAL;
		पूर्ण
		btf_id = btf_find_by_name_kind(btf, ops->map_btf_name,
					       BTF_KIND_STRUCT);
		अगर (btf_id < 0)
			वापस btf_id;
		*ops->map_btf_id = btf_id;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक btf_translate_to_vmlinux(काष्ठा bpf_verअगरier_log *log,
				     काष्ठा btf *btf,
				     स्थिर काष्ठा btf_type *t,
				     क्रमागत bpf_prog_type prog_type,
				     पूर्णांक arg)
अणु
	स्थिर काष्ठा btf_member *prog_ctx_type, *kern_ctx_type;

	prog_ctx_type = btf_get_prog_ctx_type(log, btf, t, prog_type, arg);
	अगर (!prog_ctx_type)
		वापस -ENOENT;
	kern_ctx_type = prog_ctx_type + 1;
	वापस kern_ctx_type->type;
पूर्ण

BTF_ID_LIST(bpf_ctx_convert_btf_id)
BTF_ID(काष्ठा, bpf_ctx_convert)

काष्ठा btf *btf_parse_vmlinux(व्योम)
अणु
	काष्ठा btf_verअगरier_env *env = शून्य;
	काष्ठा bpf_verअगरier_log *log;
	काष्ठा btf *btf = शून्य;
	पूर्णांक err;

	env = kzalloc(माप(*env), GFP_KERNEL | __GFP_NOWARN);
	अगर (!env)
		वापस ERR_PTR(-ENOMEM);

	log = &env->log;
	log->level = BPF_LOG_KERNEL;

	btf = kzalloc(माप(*btf), GFP_KERNEL | __GFP_NOWARN);
	अगर (!btf) अणु
		err = -ENOMEM;
		जाओ errout;
	पूर्ण
	env->btf = btf;

	btf->data = __start_BTF;
	btf->data_size = __stop_BTF - __start_BTF;
	btf->kernel_btf = true;
	snम_लिखो(btf->name, माप(btf->name), "vmlinux");

	err = btf_parse_hdr(env);
	अगर (err)
		जाओ errout;

	btf->nohdr_data = btf->data + btf->hdr.hdr_len;

	err = btf_parse_str_sec(env);
	अगर (err)
		जाओ errout;

	err = btf_check_all_metas(env);
	अगर (err)
		जाओ errout;

	/* btf_parse_vmlinux() runs under bpf_verअगरier_lock */
	bpf_ctx_convert.t = btf_type_by_id(btf, bpf_ctx_convert_btf_id[0]);

	/* find bpf map काष्ठाs क्रम map_ptr access checking */
	err = btf_vmlinux_map_ids_init(btf, log);
	अगर (err < 0)
		जाओ errout;

	bpf_काष्ठा_ops_init(btf, log);

	refcount_set(&btf->refcnt, 1);

	err = btf_alloc_id(btf);
	अगर (err)
		जाओ errout;

	btf_verअगरier_env_मुक्त(env);
	वापस btf;

errout:
	btf_verअगरier_env_मुक्त(env);
	अगर (btf) अणु
		kvमुक्त(btf->types);
		kमुक्त(btf);
	पूर्ण
	वापस ERR_PTR(err);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_INFO_BTF_MODULES

अटल काष्ठा btf *btf_parse_module(स्थिर अक्षर *module_name, स्थिर व्योम *data, अचिन्हित पूर्णांक data_size)
अणु
	काष्ठा btf_verअगरier_env *env = शून्य;
	काष्ठा bpf_verअगरier_log *log;
	काष्ठा btf *btf = शून्य, *base_btf;
	पूर्णांक err;

	base_btf = bpf_get_btf_vmlinux();
	अगर (IS_ERR(base_btf))
		वापस base_btf;
	अगर (!base_btf)
		वापस ERR_PTR(-EINVAL);

	env = kzalloc(माप(*env), GFP_KERNEL | __GFP_NOWARN);
	अगर (!env)
		वापस ERR_PTR(-ENOMEM);

	log = &env->log;
	log->level = BPF_LOG_KERNEL;

	btf = kzalloc(माप(*btf), GFP_KERNEL | __GFP_NOWARN);
	अगर (!btf) अणु
		err = -ENOMEM;
		जाओ errout;
	पूर्ण
	env->btf = btf;

	btf->base_btf = base_btf;
	btf->start_id = base_btf->nr_types;
	btf->start_str_off = base_btf->hdr.str_len;
	btf->kernel_btf = true;
	snम_लिखो(btf->name, माप(btf->name), "%s", module_name);

	btf->data = kvदो_स्मृति(data_size, GFP_KERNEL | __GFP_NOWARN);
	अगर (!btf->data) अणु
		err = -ENOMEM;
		जाओ errout;
	पूर्ण
	स_नकल(btf->data, data, data_size);
	btf->data_size = data_size;

	err = btf_parse_hdr(env);
	अगर (err)
		जाओ errout;

	btf->nohdr_data = btf->data + btf->hdr.hdr_len;

	err = btf_parse_str_sec(env);
	अगर (err)
		जाओ errout;

	err = btf_check_all_metas(env);
	अगर (err)
		जाओ errout;

	btf_verअगरier_env_मुक्त(env);
	refcount_set(&btf->refcnt, 1);
	वापस btf;

errout:
	btf_verअगरier_env_मुक्त(env);
	अगर (btf) अणु
		kvमुक्त(btf->data);
		kvमुक्त(btf->types);
		kमुक्त(btf);
	पूर्ण
	वापस ERR_PTR(err);
पूर्ण

#पूर्ण_अगर /* CONFIG_DEBUG_INFO_BTF_MODULES */

काष्ठा btf *bpf_prog_get_target_btf(स्थिर काष्ठा bpf_prog *prog)
अणु
	काष्ठा bpf_prog *tgt_prog = prog->aux->dst_prog;

	अगर (tgt_prog)
		वापस tgt_prog->aux->btf;
	अन्यथा
		वापस prog->aux->attach_btf;
पूर्ण

अटल bool is_string_ptr(काष्ठा btf *btf, स्थिर काष्ठा btf_type *t)
अणु
	/* t comes in alपढ़ोy as a poपूर्णांकer */
	t = btf_type_by_id(btf, t->type);

	/* allow स्थिर */
	अगर (BTF_INFO_KIND(t->info) == BTF_KIND_CONST)
		t = btf_type_by_id(btf, t->type);

	/* अक्षर, चिन्हित अक्षर, अचिन्हित अक्षर */
	वापस btf_type_is_पूर्णांक(t) && t->size == 1;
पूर्ण

bool btf_ctx_access(पूर्णांक off, पूर्णांक size, क्रमागत bpf_access_type type,
		    स्थिर काष्ठा bpf_prog *prog,
		    काष्ठा bpf_insn_access_aux *info)
अणु
	स्थिर काष्ठा btf_type *t = prog->aux->attach_func_proto;
	काष्ठा bpf_prog *tgt_prog = prog->aux->dst_prog;
	काष्ठा btf *btf = bpf_prog_get_target_btf(prog);
	स्थिर अक्षर *tname = prog->aux->attach_func_name;
	काष्ठा bpf_verअगरier_log *log = info->log;
	स्थिर काष्ठा btf_param *args;
	u32 nr_args, arg;
	पूर्णांक i, ret;

	अगर (off % 8) अणु
		bpf_log(log, "func '%s' offset %d is not multiple of 8\n",
			tname, off);
		वापस false;
	पूर्ण
	arg = off / 8;
	args = (स्थिर काष्ठा btf_param *)(t + 1);
	/* अगर (t == शून्य) Fall back to शेष BPF prog with
	 * MAX_BPF_FUNC_REG_ARGS u64 arguments.
	 */
	nr_args = t ? btf_type_vlen(t) : MAX_BPF_FUNC_REG_ARGS;
	अगर (prog->aux->attach_btf_trace) अणु
		/* skip first 'void *__data' argument in btf_trace_##name प्रकार */
		args++;
		nr_args--;
	पूर्ण

	अगर (arg > nr_args) अणु
		bpf_log(log, "func '%s' doesn't have %d-th argument\n",
			tname, arg + 1);
		वापस false;
	पूर्ण

	अगर (arg == nr_args) अणु
		चयन (prog->expected_attach_type) अणु
		हाल BPF_LSM_MAC:
		हाल BPF_TRACE_FEXIT:
			/* When LSM programs are attached to व्योम LSM hooks
			 * they use FEXIT trampolines and when attached to
			 * पूर्णांक LSM hooks, they use MODIFY_RETURN trampolines.
			 *
			 * While the LSM programs are BPF_MODIFY_RETURN-like
			 * the check:
			 *
			 *	अगर (ret_type != 'int')
			 *		वापस -EINVAL;
			 *
			 * is _not_ करोne here. This is still safe as LSM hooks
			 * have only व्योम and पूर्णांक वापस types.
			 */
			अगर (!t)
				वापस true;
			t = btf_type_by_id(btf, t->type);
			अवरोध;
		हाल BPF_MODIFY_RETURN:
			/* For now the BPF_MODIFY_RETURN can only be attached to
			 * functions that वापस an पूर्णांक.
			 */
			अगर (!t)
				वापस false;

			t = btf_type_skip_modअगरiers(btf, t->type, शून्य);
			अगर (!btf_type_is_small_पूर्णांक(t)) अणु
				bpf_log(log,
					"ret type %s not allowed for fmod_ret\n",
					btf_kind_str[BTF_INFO_KIND(t->info)]);
				वापस false;
			पूर्ण
			अवरोध;
		शेष:
			bpf_log(log, "func '%s' doesn't have %d-th argument\n",
				tname, arg + 1);
			वापस false;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!t)
			/* Default prog with MAX_BPF_FUNC_REG_ARGS args */
			वापस true;
		t = btf_type_by_id(btf, args[arg].type);
	पूर्ण

	/* skip modअगरiers */
	जबतक (btf_type_is_modअगरier(t))
		t = btf_type_by_id(btf, t->type);
	अगर (btf_type_is_small_पूर्णांक(t) || btf_type_is_क्रमागत(t))
		/* accessing a scalar */
		वापस true;
	अगर (!btf_type_is_ptr(t)) अणु
		bpf_log(log,
			"func '%s' arg%d '%s' has type %s. Only pointer access is allowed\n",
			tname, arg,
			__btf_name_by_offset(btf, t->name_off),
			btf_kind_str[BTF_INFO_KIND(t->info)]);
		वापस false;
	पूर्ण

	/* check क्रम PTR_TO_RDONLY_BUF_OR_शून्य or PTR_TO_RDWR_BUF_OR_शून्य */
	क्रम (i = 0; i < prog->aux->ctx_arg_info_size; i++) अणु
		स्थिर काष्ठा bpf_ctx_arg_aux *ctx_arg_info = &prog->aux->ctx_arg_info[i];

		अगर (ctx_arg_info->offset == off &&
		    (ctx_arg_info->reg_type == PTR_TO_RDONLY_BUF_OR_शून्य ||
		     ctx_arg_info->reg_type == PTR_TO_RDWR_BUF_OR_शून्य)) अणु
			info->reg_type = ctx_arg_info->reg_type;
			वापस true;
		पूर्ण
	पूर्ण

	अगर (t->type == 0)
		/* This is a poपूर्णांकer to व्योम.
		 * It is the same as scalar from the verअगरier safety pov.
		 * No further poपूर्णांकer walking is allowed.
		 */
		वापस true;

	अगर (is_string_ptr(btf, t))
		वापस true;

	/* this is a poपूर्णांकer to another type */
	क्रम (i = 0; i < prog->aux->ctx_arg_info_size; i++) अणु
		स्थिर काष्ठा bpf_ctx_arg_aux *ctx_arg_info = &prog->aux->ctx_arg_info[i];

		अगर (ctx_arg_info->offset == off) अणु
			info->reg_type = ctx_arg_info->reg_type;
			info->btf = btf_vmlinux;
			info->btf_id = ctx_arg_info->btf_id;
			वापस true;
		पूर्ण
	पूर्ण

	info->reg_type = PTR_TO_BTF_ID;
	अगर (tgt_prog) अणु
		क्रमागत bpf_prog_type tgt_type;

		अगर (tgt_prog->type == BPF_PROG_TYPE_EXT)
			tgt_type = tgt_prog->aux->saved_dst_prog_type;
		अन्यथा
			tgt_type = tgt_prog->type;

		ret = btf_translate_to_vmlinux(log, btf, t, tgt_type, arg);
		अगर (ret > 0) अणु
			info->btf = btf_vmlinux;
			info->btf_id = ret;
			वापस true;
		पूर्ण अन्यथा अणु
			वापस false;
		पूर्ण
	पूर्ण

	info->btf = btf;
	info->btf_id = t->type;
	t = btf_type_by_id(btf, t->type);
	/* skip modअगरiers */
	जबतक (btf_type_is_modअगरier(t)) अणु
		info->btf_id = t->type;
		t = btf_type_by_id(btf, t->type);
	पूर्ण
	अगर (!btf_type_is_काष्ठा(t)) अणु
		bpf_log(log,
			"func '%s' arg%d type %s is not a struct\n",
			tname, arg, btf_kind_str[BTF_INFO_KIND(t->info)]);
		वापस false;
	पूर्ण
	bpf_log(log, "func '%s' arg%d has btf_id %d type %s '%s'\n",
		tname, arg, info->btf_id, btf_kind_str[BTF_INFO_KIND(t->info)],
		__btf_name_by_offset(btf, t->name_off));
	वापस true;
पूर्ण

क्रमागत bpf_काष्ठा_walk_result अणु
	/* < 0 error */
	WALK_SCALAR = 0,
	WALK_PTR,
	WALK_STRUCT,
पूर्ण;

अटल पूर्णांक btf_काष्ठा_walk(काष्ठा bpf_verअगरier_log *log, स्थिर काष्ठा btf *btf,
			   स्थिर काष्ठा btf_type *t, पूर्णांक off, पूर्णांक size,
			   u32 *next_btf_id)
अणु
	u32 i, moff, mtrue_end, msize = 0, total_nelems = 0;
	स्थिर काष्ठा btf_type *mtype, *elem_type = शून्य;
	स्थिर काष्ठा btf_member *member;
	स्थिर अक्षर *tname, *mname;
	u32 vlen, elem_id, mid;

again:
	tname = __btf_name_by_offset(btf, t->name_off);
	अगर (!btf_type_is_काष्ठा(t)) अणु
		bpf_log(log, "Type '%s' is not a struct\n", tname);
		वापस -EINVAL;
	पूर्ण

	vlen = btf_type_vlen(t);
	अगर (off + size > t->size) अणु
		/* If the last element is a variable size array, we may
		 * need to relax the rule.
		 */
		काष्ठा btf_array *array_elem;

		अगर (vlen == 0)
			जाओ error;

		member = btf_type_member(t) + vlen - 1;
		mtype = btf_type_skip_modअगरiers(btf, member->type,
						शून्य);
		अगर (!btf_type_is_array(mtype))
			जाओ error;

		array_elem = (काष्ठा btf_array *)(mtype + 1);
		अगर (array_elem->nelems != 0)
			जाओ error;

		moff = btf_member_bit_offset(t, member) / 8;
		अगर (off < moff)
			जाओ error;

		/* Only allow काष्ठाure क्रम now, can be relaxed क्रम
		 * other types later.
		 */
		t = btf_type_skip_modअगरiers(btf, array_elem->type,
					    शून्य);
		अगर (!btf_type_is_काष्ठा(t))
			जाओ error;

		off = (off - moff) % t->size;
		जाओ again;

error:
		bpf_log(log, "access beyond struct %s at off %u size %u\n",
			tname, off, size);
		वापस -EACCES;
	पूर्ण

	क्रम_each_member(i, t, member) अणु
		/* offset of the field in bytes */
		moff = btf_member_bit_offset(t, member) / 8;
		अगर (off + size <= moff)
			/* won't find anything, field is alपढ़ोy too far */
			अवरोध;

		अगर (btf_member_bitfield_size(t, member)) अणु
			u32 end_bit = btf_member_bit_offset(t, member) +
				btf_member_bitfield_size(t, member);

			/* off <= moff instead of off == moff because clang
			 * करोes not generate a BTF member क्रम anonymous
			 * bitfield like the ":16" here:
			 * काष्ठा अणु
			 *	पूर्णांक :16;
			 *	पूर्णांक x:8;
			 * पूर्ण;
			 */
			अगर (off <= moff &&
			    BITS_ROUNDUP_BYTES(end_bit) <= off + size)
				वापस WALK_SCALAR;

			/* off may be accessing a following member
			 *
			 * or
			 *
			 * Doing partial access at either end of this
			 * bitfield.  Continue on this हाल also to
			 * treat it as not accessing this bitfield
			 * and eventually error out as field not
			 * found to keep it simple.
			 * It could be relaxed अगर there was a legit
			 * partial access हाल later.
			 */
			जारी;
		पूर्ण

		/* In हाल of "off" is poपूर्णांकing to holes of a काष्ठा */
		अगर (off < moff)
			अवरोध;

		/* type of the field */
		mid = member->type;
		mtype = btf_type_by_id(btf, member->type);
		mname = __btf_name_by_offset(btf, member->name_off);

		mtype = __btf_resolve_size(btf, mtype, &msize,
					   &elem_type, &elem_id, &total_nelems,
					   &mid);
		अगर (IS_ERR(mtype)) अणु
			bpf_log(log, "field %s doesn't have size\n", mname);
			वापस -EFAULT;
		पूर्ण

		mtrue_end = moff + msize;
		अगर (off >= mtrue_end)
			/* no overlap with member, keep iterating */
			जारी;

		अगर (btf_type_is_array(mtype)) अणु
			u32 elem_idx;

			/* __btf_resolve_size() above helps to
			 * linearize a multi-dimensional array.
			 *
			 * The logic here is treating an array
			 * in a काष्ठा as the following way:
			 *
			 * काष्ठा outer अणु
			 *	काष्ठा inner array[2][2];
			 * पूर्ण;
			 *
			 * looks like:
			 *
			 * काष्ठा outer अणु
			 *	काष्ठा inner array_elem0;
			 *	काष्ठा inner array_elem1;
			 *	काष्ठा inner array_elem2;
			 *	काष्ठा inner array_elem3;
			 * पूर्ण;
			 *
			 * When accessing outer->array[1][0], it moves
			 * moff to "array_elem2", set mtype to
			 * "struct inner", and msize also becomes
			 * माप(काष्ठा inner).  Then most of the
			 * reमुख्यing logic will fall through without
			 * caring the current member is an array or
			 * not.
			 *
			 * Unlike mtype/msize/moff, mtrue_end करोes not
			 * change.  The naming dअगरference ("_true") tells
			 * that it is not always corresponding to
			 * the current mtype/msize/moff.
			 * It is the true end of the current
			 * member (i.e. array in this हाल).  That
			 * will allow an पूर्णांक array to be accessed like
			 * a scratch space,
			 * i.e. allow access beyond the size of
			 *      the array's element as दीर्घ as it is
			 *      within the mtrue_end boundary.
			 */

			/* skip empty array */
			अगर (moff == mtrue_end)
				जारी;

			msize /= total_nelems;
			elem_idx = (off - moff) / msize;
			moff += elem_idx * msize;
			mtype = elem_type;
			mid = elem_id;
		पूर्ण

		/* the 'off' we're looking क्रम is either equal to start
		 * of this field or inside of this काष्ठा
		 */
		अगर (btf_type_is_काष्ठा(mtype)) अणु
			/* our field must be inside that जोड़ or काष्ठा */
			t = mtype;

			/* वापस अगर the offset matches the member offset */
			अगर (off == moff) अणु
				*next_btf_id = mid;
				वापस WALK_STRUCT;
			पूर्ण

			/* adjust offset we're looking क्रम */
			off -= moff;
			जाओ again;
		पूर्ण

		अगर (btf_type_is_ptr(mtype)) अणु
			स्थिर काष्ठा btf_type *stype;
			u32 id;

			अगर (msize != size || off != moff) अणु
				bpf_log(log,
					"cannot access ptr member %s with moff %u in struct %s with off %u size %u\n",
					mname, moff, tname, off, size);
				वापस -EACCES;
			पूर्ण
			stype = btf_type_skip_modअगरiers(btf, mtype->type, &id);
			अगर (btf_type_is_काष्ठा(stype)) अणु
				*next_btf_id = id;
				वापस WALK_PTR;
			पूर्ण
		पूर्ण

		/* Allow more flexible access within an पूर्णांक as दीर्घ as
		 * it is within mtrue_end.
		 * Since mtrue_end could be the end of an array,
		 * that also allows using an array of पूर्णांक as a scratch
		 * space. e.g. skb->cb[].
		 */
		अगर (off + size > mtrue_end) अणु
			bpf_log(log,
				"access beyond the end of member %s (mend:%u) in struct %s with off %u size %u\n",
				mname, mtrue_end, tname, off, size);
			वापस -EACCES;
		पूर्ण

		वापस WALK_SCALAR;
	पूर्ण
	bpf_log(log, "struct %s doesn't have field at offset %d\n", tname, off);
	वापस -EINVAL;
पूर्ण

पूर्णांक btf_काष्ठा_access(काष्ठा bpf_verअगरier_log *log, स्थिर काष्ठा btf *btf,
		      स्थिर काष्ठा btf_type *t, पूर्णांक off, पूर्णांक size,
		      क्रमागत bpf_access_type atype __maybe_unused,
		      u32 *next_btf_id)
अणु
	पूर्णांक err;
	u32 id;

	करो अणु
		err = btf_काष्ठा_walk(log, btf, t, off, size, &id);

		चयन (err) अणु
		हाल WALK_PTR:
			/* If we found the poपूर्णांकer or scalar on t+off,
			 * we're करोne.
			 */
			*next_btf_id = id;
			वापस PTR_TO_BTF_ID;
		हाल WALK_SCALAR:
			वापस SCALAR_VALUE;
		हाल WALK_STRUCT:
			/* We found nested काष्ठा, so जारी the search
			 * by भागing in it. At this poपूर्णांक the offset is
			 * aligned with the new type, so set it to 0.
			 */
			t = btf_type_by_id(btf, id);
			off = 0;
			अवरोध;
		शेष:
			/* It's either error or unknown वापस value..
			 * scream and leave.
			 */
			अगर (WARN_ONCE(err > 0, "unknown btf_struct_walk return value"))
				वापस -EINVAL;
			वापस err;
		पूर्ण
	पूर्ण जबतक (t);

	वापस -EINVAL;
पूर्ण

/* Check that two BTF types, each specअगरied as an BTF object + id, are exactly
 * the same. Trivial ID check is not enough due to module BTFs, because we can
 * end up with two dअगरferent module BTFs, but IDs poपूर्णांक to the common type in
 * vmlinux BTF.
 */
अटल bool btf_types_are_same(स्थिर काष्ठा btf *btf1, u32 id1,
			       स्थिर काष्ठा btf *btf2, u32 id2)
अणु
	अगर (id1 != id2)
		वापस false;
	अगर (btf1 == btf2)
		वापस true;
	वापस btf_type_by_id(btf1, id1) == btf_type_by_id(btf2, id2);
पूर्ण

bool btf_काष्ठा_ids_match(काष्ठा bpf_verअगरier_log *log,
			  स्थिर काष्ठा btf *btf, u32 id, पूर्णांक off,
			  स्थिर काष्ठा btf *need_btf, u32 need_type_id)
अणु
	स्थिर काष्ठा btf_type *type;
	पूर्णांक err;

	/* Are we alपढ़ोy करोne? */
	अगर (off == 0 && btf_types_are_same(btf, id, need_btf, need_type_id))
		वापस true;

again:
	type = btf_type_by_id(btf, id);
	अगर (!type)
		वापस false;
	err = btf_काष्ठा_walk(log, btf, type, off, 1, &id);
	अगर (err != WALK_STRUCT)
		वापस false;

	/* We found nested काष्ठा object. If it matches
	 * the requested ID, we're done. Otherwise let's
	 * जारी the search with offset 0 in the new
	 * type.
	 */
	अगर (!btf_types_are_same(btf, id, need_btf, need_type_id)) अणु
		off = 0;
		जाओ again;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक __get_type_size(काष्ठा btf *btf, u32 btf_id,
			   स्थिर काष्ठा btf_type **bad_type)
अणु
	स्थिर काष्ठा btf_type *t;

	अगर (!btf_id)
		/* व्योम */
		वापस 0;
	t = btf_type_by_id(btf, btf_id);
	जबतक (t && btf_type_is_modअगरier(t))
		t = btf_type_by_id(btf, t->type);
	अगर (!t) अणु
		*bad_type = btf_type_by_id(btf, 0);
		वापस -EINVAL;
	पूर्ण
	अगर (btf_type_is_ptr(t))
		/* kernel size of poपूर्णांकer. Not BPF's size of poपूर्णांकer*/
		वापस माप(व्योम *);
	अगर (btf_type_is_पूर्णांक(t) || btf_type_is_क्रमागत(t))
		वापस t->size;
	*bad_type = t;
	वापस -EINVAL;
पूर्ण

पूर्णांक btf_distill_func_proto(काष्ठा bpf_verअगरier_log *log,
			   काष्ठा btf *btf,
			   स्थिर काष्ठा btf_type *func,
			   स्थिर अक्षर *tname,
			   काष्ठा btf_func_model *m)
अणु
	स्थिर काष्ठा btf_param *args;
	स्थिर काष्ठा btf_type *t;
	u32 i, nargs;
	पूर्णांक ret;

	अगर (!func) अणु
		/* BTF function prototype करोesn't match the verअगरier types.
		 * Fall back to MAX_BPF_FUNC_REG_ARGS u64 args.
		 */
		क्रम (i = 0; i < MAX_BPF_FUNC_REG_ARGS; i++)
			m->arg_size[i] = 8;
		m->ret_size = 8;
		m->nr_args = MAX_BPF_FUNC_REG_ARGS;
		वापस 0;
	पूर्ण
	args = (स्थिर काष्ठा btf_param *)(func + 1);
	nargs = btf_type_vlen(func);
	अगर (nargs >= MAX_BPF_FUNC_ARGS) अणु
		bpf_log(log,
			"The function %s has %d arguments. Too many.\n",
			tname, nargs);
		वापस -EINVAL;
	पूर्ण
	ret = __get_type_size(btf, func->type, &t);
	अगर (ret < 0) अणु
		bpf_log(log,
			"The function %s return type %s is unsupported.\n",
			tname, btf_kind_str[BTF_INFO_KIND(t->info)]);
		वापस -EINVAL;
	पूर्ण
	m->ret_size = ret;

	क्रम (i = 0; i < nargs; i++) अणु
		अगर (i == nargs - 1 && args[i].type == 0) अणु
			bpf_log(log,
				"The function %s with variable args is unsupported.\n",
				tname);
			वापस -EINVAL;
		पूर्ण
		ret = __get_type_size(btf, args[i].type, &t);
		अगर (ret < 0) अणु
			bpf_log(log,
				"The function %s arg%d type %s is unsupported.\n",
				tname, i, btf_kind_str[BTF_INFO_KIND(t->info)]);
			वापस -EINVAL;
		पूर्ण
		अगर (ret == 0) अणु
			bpf_log(log,
				"The function %s has malformed void argument.\n",
				tname);
			वापस -EINVAL;
		पूर्ण
		m->arg_size[i] = ret;
	पूर्ण
	m->nr_args = nargs;
	वापस 0;
पूर्ण

/* Compare BTFs of two functions assuming only scalars and poपूर्णांकers to context.
 * t1 poपूर्णांकs to BTF_KIND_FUNC in btf1
 * t2 poपूर्णांकs to BTF_KIND_FUNC in btf2
 * Returns:
 * EINVAL - function prototype mismatch
 * EFAULT - verअगरier bug
 * 0 - 99% match. The last 1% is validated by the verअगरier.
 */
अटल पूर्णांक btf_check_func_type_match(काष्ठा bpf_verअगरier_log *log,
				     काष्ठा btf *btf1, स्थिर काष्ठा btf_type *t1,
				     काष्ठा btf *btf2, स्थिर काष्ठा btf_type *t2)
अणु
	स्थिर काष्ठा btf_param *args1, *args2;
	स्थिर अक्षर *fn1, *fn2, *s1, *s2;
	u32 nargs1, nargs2, i;

	fn1 = btf_name_by_offset(btf1, t1->name_off);
	fn2 = btf_name_by_offset(btf2, t2->name_off);

	अगर (btf_func_linkage(t1) != BTF_FUNC_GLOBAL) अणु
		bpf_log(log, "%s() is not a global function\n", fn1);
		वापस -EINVAL;
	पूर्ण
	अगर (btf_func_linkage(t2) != BTF_FUNC_GLOBAL) अणु
		bpf_log(log, "%s() is not a global function\n", fn2);
		वापस -EINVAL;
	पूर्ण

	t1 = btf_type_by_id(btf1, t1->type);
	अगर (!t1 || !btf_type_is_func_proto(t1))
		वापस -EFAULT;
	t2 = btf_type_by_id(btf2, t2->type);
	अगर (!t2 || !btf_type_is_func_proto(t2))
		वापस -EFAULT;

	args1 = (स्थिर काष्ठा btf_param *)(t1 + 1);
	nargs1 = btf_type_vlen(t1);
	args2 = (स्थिर काष्ठा btf_param *)(t2 + 1);
	nargs2 = btf_type_vlen(t2);

	अगर (nargs1 != nargs2) अणु
		bpf_log(log, "%s() has %d args while %s() has %d args\n",
			fn1, nargs1, fn2, nargs2);
		वापस -EINVAL;
	पूर्ण

	t1 = btf_type_skip_modअगरiers(btf1, t1->type, शून्य);
	t2 = btf_type_skip_modअगरiers(btf2, t2->type, शून्य);
	अगर (t1->info != t2->info) अणु
		bpf_log(log,
			"Return type %s of %s() doesn't match type %s of %s()\n",
			btf_type_str(t1), fn1,
			btf_type_str(t2), fn2);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < nargs1; i++) अणु
		t1 = btf_type_skip_modअगरiers(btf1, args1[i].type, शून्य);
		t2 = btf_type_skip_modअगरiers(btf2, args2[i].type, शून्य);

		अगर (t1->info != t2->info) अणु
			bpf_log(log, "arg%d in %s() is %s while %s() has %s\n",
				i, fn1, btf_type_str(t1),
				fn2, btf_type_str(t2));
			वापस -EINVAL;
		पूर्ण
		अगर (btf_type_has_size(t1) && t1->size != t2->size) अणु
			bpf_log(log,
				"arg%d in %s() has size %d while %s() has %d\n",
				i, fn1, t1->size,
				fn2, t2->size);
			वापस -EINVAL;
		पूर्ण

		/* global functions are validated with scalars and poपूर्णांकers
		 * to context only. And only global functions can be replaced.
		 * Hence type check only those types.
		 */
		अगर (btf_type_is_पूर्णांक(t1) || btf_type_is_क्रमागत(t1))
			जारी;
		अगर (!btf_type_is_ptr(t1)) अणु
			bpf_log(log,
				"arg%d in %s() has unrecognized type\n",
				i, fn1);
			वापस -EINVAL;
		पूर्ण
		t1 = btf_type_skip_modअगरiers(btf1, t1->type, शून्य);
		t2 = btf_type_skip_modअगरiers(btf2, t2->type, शून्य);
		अगर (!btf_type_is_काष्ठा(t1)) अणु
			bpf_log(log,
				"arg%d in %s() is not a pointer to context\n",
				i, fn1);
			वापस -EINVAL;
		पूर्ण
		अगर (!btf_type_is_काष्ठा(t2)) अणु
			bpf_log(log,
				"arg%d in %s() is not a pointer to context\n",
				i, fn2);
			वापस -EINVAL;
		पूर्ण
		/* This is an optional check to make program writing easier.
		 * Compare names of काष्ठाs and report an error to the user.
		 * btf_prepare_func_args() alपढ़ोy checked that t2 काष्ठा
		 * is a context type. btf_prepare_func_args() will check
		 * later that t1 काष्ठा is a context type as well.
		 */
		s1 = btf_name_by_offset(btf1, t1->name_off);
		s2 = btf_name_by_offset(btf2, t2->name_off);
		अगर (म_भेद(s1, s2)) अणु
			bpf_log(log,
				"arg%d %s(struct %s *) doesn't match %s(struct %s *)\n",
				i, fn1, s1, fn2, s2);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* Compare BTFs of given program with BTF of target program */
पूर्णांक btf_check_type_match(काष्ठा bpf_verअगरier_log *log, स्थिर काष्ठा bpf_prog *prog,
			 काष्ठा btf *btf2, स्थिर काष्ठा btf_type *t2)
अणु
	काष्ठा btf *btf1 = prog->aux->btf;
	स्थिर काष्ठा btf_type *t1;
	u32 btf_id = 0;

	अगर (!prog->aux->func_info) अणु
		bpf_log(log, "Program extension requires BTF\n");
		वापस -EINVAL;
	पूर्ण

	btf_id = prog->aux->func_info[0].type_id;
	अगर (!btf_id)
		वापस -EFAULT;

	t1 = btf_type_by_id(btf1, btf_id);
	अगर (!t1 || !btf_type_is_func(t1))
		वापस -EFAULT;

	वापस btf_check_func_type_match(log, btf1, t1, btf2, t2);
पूर्ण

अटल u32 *reg2btf_ids[__BPF_REG_TYPE_MAX] = अणु
#अगर_घोषित CONFIG_NET
	[PTR_TO_SOCKET] = &btf_sock_ids[BTF_SOCK_TYPE_SOCK],
	[PTR_TO_SOCK_COMMON] = &btf_sock_ids[BTF_SOCK_TYPE_SOCK_COMMON],
	[PTR_TO_TCP_SOCK] = &btf_sock_ids[BTF_SOCK_TYPE_TCP],
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक btf_check_func_arg_match(काष्ठा bpf_verअगरier_env *env,
				    स्थिर काष्ठा btf *btf, u32 func_id,
				    काष्ठा bpf_reg_state *regs,
				    bool ptr_to_mem_ok)
अणु
	काष्ठा bpf_verअगरier_log *log = &env->log;
	स्थिर अक्षर *func_name, *ref_tname;
	स्थिर काष्ठा btf_type *t, *ref_t;
	स्थिर काष्ठा btf_param *args;
	u32 i, nargs, ref_id;

	t = btf_type_by_id(btf, func_id);
	अगर (!t || !btf_type_is_func(t)) अणु
		/* These checks were alपढ़ोy करोne by the verअगरier जबतक loading
		 * काष्ठा bpf_func_info or in add_kfunc_call().
		 */
		bpf_log(log, "BTF of func_id %u doesn't point to KIND_FUNC\n",
			func_id);
		वापस -EFAULT;
	पूर्ण
	func_name = btf_name_by_offset(btf, t->name_off);

	t = btf_type_by_id(btf, t->type);
	अगर (!t || !btf_type_is_func_proto(t)) अणु
		bpf_log(log, "Invalid BTF of func %s\n", func_name);
		वापस -EFAULT;
	पूर्ण
	args = (स्थिर काष्ठा btf_param *)(t + 1);
	nargs = btf_type_vlen(t);
	अगर (nargs > MAX_BPF_FUNC_REG_ARGS) अणु
		bpf_log(log, "Function %s has %d > %d args\n", func_name, nargs,
			MAX_BPF_FUNC_REG_ARGS);
		वापस -EINVAL;
	पूर्ण

	/* check that BTF function arguments match actual types that the
	 * verअगरier sees.
	 */
	क्रम (i = 0; i < nargs; i++) अणु
		u32 regno = i + 1;
		काष्ठा bpf_reg_state *reg = &regs[regno];

		t = btf_type_skip_modअगरiers(btf, args[i].type, शून्य);
		अगर (btf_type_is_scalar(t)) अणु
			अगर (reg->type == SCALAR_VALUE)
				जारी;
			bpf_log(log, "R%d is not a scalar\n", regno);
			वापस -EINVAL;
		पूर्ण

		अगर (!btf_type_is_ptr(t)) अणु
			bpf_log(log, "Unrecognized arg#%d type %s\n",
				i, btf_type_str(t));
			वापस -EINVAL;
		पूर्ण

		ref_t = btf_type_skip_modअगरiers(btf, t->type, &ref_id);
		ref_tname = btf_name_by_offset(btf, ref_t->name_off);
		अगर (btf_is_kernel(btf)) अणु
			स्थिर काष्ठा btf_type *reg_ref_t;
			स्थिर काष्ठा btf *reg_btf;
			स्थिर अक्षर *reg_ref_tname;
			u32 reg_ref_id;

			अगर (!btf_type_is_काष्ठा(ref_t)) अणु
				bpf_log(log, "kernel function %s args#%d pointer type %s %s is not supported\n",
					func_name, i, btf_type_str(ref_t),
					ref_tname);
				वापस -EINVAL;
			पूर्ण

			अगर (reg->type == PTR_TO_BTF_ID) अणु
				reg_btf = reg->btf;
				reg_ref_id = reg->btf_id;
			पूर्ण अन्यथा अगर (reg2btf_ids[reg->type]) अणु
				reg_btf = btf_vmlinux;
				reg_ref_id = *reg2btf_ids[reg->type];
			पूर्ण अन्यथा अणु
				bpf_log(log, "kernel function %s args#%d expected pointer to %s %s but R%d is not a pointer to btf_id\n",
					func_name, i,
					btf_type_str(ref_t), ref_tname, regno);
				वापस -EINVAL;
			पूर्ण

			reg_ref_t = btf_type_skip_modअगरiers(reg_btf, reg_ref_id,
							    &reg_ref_id);
			reg_ref_tname = btf_name_by_offset(reg_btf,
							   reg_ref_t->name_off);
			अगर (!btf_काष्ठा_ids_match(log, reg_btf, reg_ref_id,
						  reg->off, btf, ref_id)) अणु
				bpf_log(log, "kernel function %s args#%d expected pointer to %s %s but R%d has a pointer to %s %s\n",
					func_name, i,
					btf_type_str(ref_t), ref_tname,
					regno, btf_type_str(reg_ref_t),
					reg_ref_tname);
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अगर (btf_get_prog_ctx_type(log, btf, t,
						 env->prog->type, i)) अणु
			/* If function expects ctx type in BTF check that caller
			 * is passing PTR_TO_CTX.
			 */
			अगर (reg->type != PTR_TO_CTX) अणु
				bpf_log(log,
					"arg#%d expected pointer to ctx, but got %s\n",
					i, btf_type_str(t));
				वापस -EINVAL;
			पूर्ण
			अगर (check_ctx_reg(env, reg, regno))
				वापस -EINVAL;
		पूर्ण अन्यथा अगर (ptr_to_mem_ok) अणु
			स्थिर काष्ठा btf_type *resolve_ret;
			u32 type_size;

			resolve_ret = btf_resolve_size(btf, ref_t, &type_size);
			अगर (IS_ERR(resolve_ret)) अणु
				bpf_log(log,
					"arg#%d reference type('%s %s') size cannot be determined: %ld\n",
					i, btf_type_str(ref_t), ref_tname,
					PTR_ERR(resolve_ret));
				वापस -EINVAL;
			पूर्ण

			अगर (check_mem_reg(env, reg, regno, type_size))
				वापस -EINVAL;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Compare BTF of a function with given bpf_reg_state.
 * Returns:
 * EFAULT - there is a verअगरier bug. Abort verअगरication.
 * EINVAL - there is a type mismatch or BTF is not available.
 * 0 - BTF matches with what bpf_reg_state expects.
 * Only PTR_TO_CTX and SCALAR_VALUE states are recognized.
 */
पूर्णांक btf_check_subprog_arg_match(काष्ठा bpf_verअगरier_env *env, पूर्णांक subprog,
				काष्ठा bpf_reg_state *regs)
अणु
	काष्ठा bpf_prog *prog = env->prog;
	काष्ठा btf *btf = prog->aux->btf;
	bool is_global;
	u32 btf_id;
	पूर्णांक err;

	अगर (!prog->aux->func_info)
		वापस -EINVAL;

	btf_id = prog->aux->func_info[subprog].type_id;
	अगर (!btf_id)
		वापस -EFAULT;

	अगर (prog->aux->func_info_aux[subprog].unreliable)
		वापस -EINVAL;

	is_global = prog->aux->func_info_aux[subprog].linkage == BTF_FUNC_GLOBAL;
	err = btf_check_func_arg_match(env, btf, btf_id, regs, is_global);

	/* Compiler optimizations can हटाओ arguments from अटल functions
	 * or mismatched type can be passed पूर्णांकo a global function.
	 * In such हालs mark the function as unreliable from BTF poपूर्णांक of view.
	 */
	अगर (err)
		prog->aux->func_info_aux[subprog].unreliable = true;
	वापस err;
पूर्ण

पूर्णांक btf_check_kfunc_arg_match(काष्ठा bpf_verअगरier_env *env,
			      स्थिर काष्ठा btf *btf, u32 func_id,
			      काष्ठा bpf_reg_state *regs)
अणु
	वापस btf_check_func_arg_match(env, btf, func_id, regs, false);
पूर्ण

/* Convert BTF of a function पूर्णांकo bpf_reg_state अगर possible
 * Returns:
 * EFAULT - there is a verअगरier bug. Abort verअगरication.
 * EINVAL - cannot convert BTF.
 * 0 - Successfully converted BTF पूर्णांकo bpf_reg_state
 * (either PTR_TO_CTX or SCALAR_VALUE).
 */
पूर्णांक btf_prepare_func_args(काष्ठा bpf_verअगरier_env *env, पूर्णांक subprog,
			  काष्ठा bpf_reg_state *regs)
अणु
	काष्ठा bpf_verअगरier_log *log = &env->log;
	काष्ठा bpf_prog *prog = env->prog;
	क्रमागत bpf_prog_type prog_type = prog->type;
	काष्ठा btf *btf = prog->aux->btf;
	स्थिर काष्ठा btf_param *args;
	स्थिर काष्ठा btf_type *t, *ref_t;
	u32 i, nargs, btf_id;
	स्थिर अक्षर *tname;

	अगर (!prog->aux->func_info ||
	    prog->aux->func_info_aux[subprog].linkage != BTF_FUNC_GLOBAL) अणु
		bpf_log(log, "Verifier bug\n");
		वापस -EFAULT;
	पूर्ण

	btf_id = prog->aux->func_info[subprog].type_id;
	अगर (!btf_id) अणु
		bpf_log(log, "Global functions need valid BTF\n");
		वापस -EFAULT;
	पूर्ण

	t = btf_type_by_id(btf, btf_id);
	अगर (!t || !btf_type_is_func(t)) अणु
		/* These checks were alपढ़ोy करोne by the verअगरier जबतक loading
		 * काष्ठा bpf_func_info
		 */
		bpf_log(log, "BTF of func#%d doesn't point to KIND_FUNC\n",
			subprog);
		वापस -EFAULT;
	पूर्ण
	tname = btf_name_by_offset(btf, t->name_off);

	अगर (log->level & BPF_LOG_LEVEL)
		bpf_log(log, "Validating %s() func#%d...\n",
			tname, subprog);

	अगर (prog->aux->func_info_aux[subprog].unreliable) अणु
		bpf_log(log, "Verifier bug in function %s()\n", tname);
		वापस -EFAULT;
	पूर्ण
	अगर (prog_type == BPF_PROG_TYPE_EXT)
		prog_type = prog->aux->dst_prog->type;

	t = btf_type_by_id(btf, t->type);
	अगर (!t || !btf_type_is_func_proto(t)) अणु
		bpf_log(log, "Invalid type of function %s()\n", tname);
		वापस -EFAULT;
	पूर्ण
	args = (स्थिर काष्ठा btf_param *)(t + 1);
	nargs = btf_type_vlen(t);
	अगर (nargs > MAX_BPF_FUNC_REG_ARGS) अणु
		bpf_log(log, "Global function %s() with %d > %d args. Buggy compiler.\n",
			tname, nargs, MAX_BPF_FUNC_REG_ARGS);
		वापस -EINVAL;
	पूर्ण
	/* check that function वापसs पूर्णांक */
	t = btf_type_by_id(btf, t->type);
	जबतक (btf_type_is_modअगरier(t))
		t = btf_type_by_id(btf, t->type);
	अगर (!btf_type_is_पूर्णांक(t) && !btf_type_is_क्रमागत(t)) अणु
		bpf_log(log,
			"Global function %s() doesn't return scalar. Only those are supported.\n",
			tname);
		वापस -EINVAL;
	पूर्ण
	/* Convert BTF function arguments पूर्णांकo verअगरier types.
	 * Only PTR_TO_CTX and SCALAR are supported aपंचांग.
	 */
	क्रम (i = 0; i < nargs; i++) अणु
		काष्ठा bpf_reg_state *reg = &regs[i + 1];

		t = btf_type_by_id(btf, args[i].type);
		जबतक (btf_type_is_modअगरier(t))
			t = btf_type_by_id(btf, t->type);
		अगर (btf_type_is_पूर्णांक(t) || btf_type_is_क्रमागत(t)) अणु
			reg->type = SCALAR_VALUE;
			जारी;
		पूर्ण
		अगर (btf_type_is_ptr(t)) अणु
			अगर (btf_get_prog_ctx_type(log, btf, t, prog_type, i)) अणु
				reg->type = PTR_TO_CTX;
				जारी;
			पूर्ण

			t = btf_type_skip_modअगरiers(btf, t->type, शून्य);

			ref_t = btf_resolve_size(btf, t, &reg->mem_size);
			अगर (IS_ERR(ref_t)) अणु
				bpf_log(log,
				    "arg#%d reference type('%s %s') size cannot be determined: %ld\n",
				    i, btf_type_str(t), btf_name_by_offset(btf, t->name_off),
					PTR_ERR(ref_t));
				वापस -EINVAL;
			पूर्ण

			reg->type = PTR_TO_MEM_OR_शून्य;
			reg->id = ++env->id_gen;

			जारी;
		पूर्ण
		bpf_log(log, "Arg#%d type %s in %s() is not supported yet.\n",
			i, btf_kind_str[BTF_INFO_KIND(t->info)], tname);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम btf_type_show(स्थिर काष्ठा btf *btf, u32 type_id, व्योम *obj,
			  काष्ठा btf_show *show)
अणु
	स्थिर काष्ठा btf_type *t = btf_type_by_id(btf, type_id);

	show->btf = btf;
	स_रखो(&show->state, 0, माप(show->state));
	स_रखो(&show->obj, 0, माप(show->obj));

	btf_type_ops(t)->show(btf, t, type_id, obj, 0, show);
पूर्ण

अटल व्योम btf_seq_show(काष्ठा btf_show *show, स्थिर अक्षर *fmt,
			 बहु_सूची args)
अणु
	seq_भ_लिखो((काष्ठा seq_file *)show->target, fmt, args);
पूर्ण

पूर्णांक btf_type_seq_show_flags(स्थिर काष्ठा btf *btf, u32 type_id,
			    व्योम *obj, काष्ठा seq_file *m, u64 flags)
अणु
	काष्ठा btf_show sseq;

	sseq.target = m;
	sseq.showfn = btf_seq_show;
	sseq.flags = flags;

	btf_type_show(btf, type_id, obj, &sseq);

	वापस sseq.state.status;
पूर्ण

व्योम btf_type_seq_show(स्थिर काष्ठा btf *btf, u32 type_id, व्योम *obj,
		       काष्ठा seq_file *m)
अणु
	(व्योम) btf_type_seq_show_flags(btf, type_id, obj, m,
				       BTF_SHOW_NONAME | BTF_SHOW_COMPACT |
				       BTF_SHOW_ZERO | BTF_SHOW_UNSAFE);
पूर्ण

काष्ठा btf_show_snम_लिखो अणु
	काष्ठा btf_show show;
	पूर्णांक len_left;		/* space left in string */
	पूर्णांक len;		/* length we would have written */
पूर्ण;

अटल व्योम btf_snम_लिखो_show(काष्ठा btf_show *show, स्थिर अक्षर *fmt,
			      बहु_सूची args)
अणु
	काष्ठा btf_show_snम_लिखो *ssnम_लिखो = (काष्ठा btf_show_snम_लिखो *)show;
	पूर्णांक len;

	len = vsnम_लिखो(show->target, ssnम_लिखो->len_left, fmt, args);

	अगर (len < 0) अणु
		ssnम_लिखो->len_left = 0;
		ssnम_लिखो->len = len;
	पूर्ण अन्यथा अगर (len > ssnम_लिखो->len_left) अणु
		/* no space, drive on to get length we would have written */
		ssnम_लिखो->len_left = 0;
		ssnम_लिखो->len += len;
	पूर्ण अन्यथा अणु
		ssnम_लिखो->len_left -= len;
		ssnम_लिखो->len += len;
		show->target += len;
	पूर्ण
पूर्ण

पूर्णांक btf_type_snम_लिखो_show(स्थिर काष्ठा btf *btf, u32 type_id, व्योम *obj,
			   अक्षर *buf, पूर्णांक len, u64 flags)
अणु
	काष्ठा btf_show_snम_लिखो ssnम_लिखो;

	ssnम_लिखो.show.target = buf;
	ssnम_लिखो.show.flags = flags;
	ssnम_लिखो.show.showfn = btf_snम_लिखो_show;
	ssnम_लिखो.len_left = len;
	ssnम_लिखो.len = 0;

	btf_type_show(btf, type_id, obj, (काष्ठा btf_show *)&ssnम_लिखो);

	/* If we encontered an error, वापस it. */
	अगर (ssnम_लिखो.show.state.status)
		वापस ssnम_लिखो.show.state.status;

	/* Otherwise वापस length we would have written */
	वापस ssnम_लिखो.len;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल व्योम bpf_btf_show_fdinfo(काष्ठा seq_file *m, काष्ठा file *filp)
अणु
	स्थिर काष्ठा btf *btf = filp->निजी_data;

	seq_म_लिखो(m, "btf_id:\t%u\n", btf->id);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक btf_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	btf_put(filp->निजी_data);
	वापस 0;
पूर्ण

स्थिर काष्ठा file_operations btf_fops = अणु
#अगर_घोषित CONFIG_PROC_FS
	.show_fdinfo	= bpf_btf_show_fdinfo,
#पूर्ण_अगर
	.release	= btf_release,
पूर्ण;

अटल पूर्णांक __btf_new_fd(काष्ठा btf *btf)
अणु
	वापस anon_inode_getfd("btf", &btf_fops, btf, O_RDONLY | O_CLOEXEC);
पूर्ण

पूर्णांक btf_new_fd(स्थिर जोड़ bpf_attr *attr)
अणु
	काष्ठा btf *btf;
	पूर्णांक ret;

	btf = btf_parse(u64_to_user_ptr(attr->btf),
			attr->btf_size, attr->btf_log_level,
			u64_to_user_ptr(attr->btf_log_buf),
			attr->btf_log_size);
	अगर (IS_ERR(btf))
		वापस PTR_ERR(btf);

	ret = btf_alloc_id(btf);
	अगर (ret) अणु
		btf_मुक्त(btf);
		वापस ret;
	पूर्ण

	/*
	 * The BTF ID is published to the userspace.
	 * All BTF मुक्त must go through call_rcu() from
	 * now on (i.e. मुक्त by calling btf_put()).
	 */

	ret = __btf_new_fd(btf);
	अगर (ret < 0)
		btf_put(btf);

	वापस ret;
पूर्ण

काष्ठा btf *btf_get_by_fd(पूर्णांक fd)
अणु
	काष्ठा btf *btf;
	काष्ठा fd f;

	f = fdget(fd);

	अगर (!f.file)
		वापस ERR_PTR(-EBADF);

	अगर (f.file->f_op != &btf_fops) अणु
		fdput(f);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	btf = f.file->निजी_data;
	refcount_inc(&btf->refcnt);
	fdput(f);

	वापस btf;
पूर्ण

पूर्णांक btf_get_info_by_fd(स्थिर काष्ठा btf *btf,
		       स्थिर जोड़ bpf_attr *attr,
		       जोड़ bpf_attr __user *uattr)
अणु
	काष्ठा bpf_btf_info __user *uinfo;
	काष्ठा bpf_btf_info info;
	u32 info_copy, btf_copy;
	व्योम __user *ubtf;
	अक्षर __user *uname;
	u32 uinfo_len, uname_len, name_len;
	पूर्णांक ret = 0;

	uinfo = u64_to_user_ptr(attr->info.info);
	uinfo_len = attr->info.info_len;

	info_copy = min_t(u32, uinfo_len, माप(info));
	स_रखो(&info, 0, माप(info));
	अगर (copy_from_user(&info, uinfo, info_copy))
		वापस -EFAULT;

	info.id = btf->id;
	ubtf = u64_to_user_ptr(info.btf);
	btf_copy = min_t(u32, btf->data_size, info.btf_size);
	अगर (copy_to_user(ubtf, btf->data, btf_copy))
		वापस -EFAULT;
	info.btf_size = btf->data_size;

	info.kernel_btf = btf->kernel_btf;

	uname = u64_to_user_ptr(info.name);
	uname_len = info.name_len;
	अगर (!uname ^ !uname_len)
		वापस -EINVAL;

	name_len = म_माप(btf->name);
	info.name_len = name_len;

	अगर (uname) अणु
		अगर (uname_len >= name_len + 1) अणु
			अगर (copy_to_user(uname, btf->name, name_len + 1))
				वापस -EFAULT;
		पूर्ण अन्यथा अणु
			अक्षर zero = '\0';

			अगर (copy_to_user(uname, btf->name, uname_len - 1))
				वापस -EFAULT;
			अगर (put_user(zero, uname + uname_len - 1))
				वापस -EFAULT;
			/* let user-space know about too लघु buffer */
			ret = -ENOSPC;
		पूर्ण
	पूर्ण

	अगर (copy_to_user(uinfo, &info, info_copy) ||
	    put_user(info_copy, &uattr->info.info_len))
		वापस -EFAULT;

	वापस ret;
पूर्ण

पूर्णांक btf_get_fd_by_id(u32 id)
अणु
	काष्ठा btf *btf;
	पूर्णांक fd;

	rcu_पढ़ो_lock();
	btf = idr_find(&btf_idr, id);
	अगर (!btf || !refcount_inc_not_zero(&btf->refcnt))
		btf = ERR_PTR(-ENOENT);
	rcu_पढ़ो_unlock();

	अगर (IS_ERR(btf))
		वापस PTR_ERR(btf);

	fd = __btf_new_fd(btf);
	अगर (fd < 0)
		btf_put(btf);

	वापस fd;
पूर्ण

u32 btf_obj_id(स्थिर काष्ठा btf *btf)
अणु
	वापस btf->id;
पूर्ण

bool btf_is_kernel(स्थिर काष्ठा btf *btf)
अणु
	वापस btf->kernel_btf;
पूर्ण

bool btf_is_module(स्थिर काष्ठा btf *btf)
अणु
	वापस btf->kernel_btf && म_भेद(btf->name, "vmlinux") != 0;
पूर्ण

अटल पूर्णांक btf_id_cmp_func(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर पूर्णांक *pa = a, *pb = b;

	वापस *pa - *pb;
पूर्ण

bool btf_id_set_contains(स्थिर काष्ठा btf_id_set *set, u32 id)
अणु
	वापस द्वा_खोज(&id, set->ids, set->cnt, माप(u32), btf_id_cmp_func) != शून्य;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_INFO_BTF_MODULES
काष्ठा btf_module अणु
	काष्ठा list_head list;
	काष्ठा module *module;
	काष्ठा btf *btf;
	काष्ठा bin_attribute *sysfs_attr;
पूर्ण;

अटल LIST_HEAD(btf_modules);
अटल DEFINE_MUTEX(btf_module_mutex);

अटल sमाप_प्रकार
btf_module_पढ़ो(काष्ठा file *file, काष्ठा kobject *kobj,
		काष्ठा bin_attribute *bin_attr,
		अक्षर *buf, loff_t off, माप_प्रकार len)
अणु
	स्थिर काष्ठा btf *btf = bin_attr->निजी;

	स_नकल(buf, btf->data + off, len);
	वापस len;
पूर्ण

अटल पूर्णांक btf_module_notअगरy(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ op,
			     व्योम *module)
अणु
	काष्ठा btf_module *btf_mod, *पंचांगp;
	काष्ठा module *mod = module;
	काष्ठा btf *btf;
	पूर्णांक err = 0;

	अगर (mod->btf_data_size == 0 ||
	    (op != MODULE_STATE_COMING && op != MODULE_STATE_GOING))
		जाओ out;

	चयन (op) अणु
	हाल MODULE_STATE_COMING:
		btf_mod = kzalloc(माप(*btf_mod), GFP_KERNEL);
		अगर (!btf_mod) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण
		btf = btf_parse_module(mod->name, mod->btf_data, mod->btf_data_size);
		अगर (IS_ERR(btf)) अणु
			pr_warn("failed to validate module [%s] BTF: %ld\n",
				mod->name, PTR_ERR(btf));
			kमुक्त(btf_mod);
			err = PTR_ERR(btf);
			जाओ out;
		पूर्ण
		err = btf_alloc_id(btf);
		अगर (err) अणु
			btf_मुक्त(btf);
			kमुक्त(btf_mod);
			जाओ out;
		पूर्ण

		mutex_lock(&btf_module_mutex);
		btf_mod->module = module;
		btf_mod->btf = btf;
		list_add(&btf_mod->list, &btf_modules);
		mutex_unlock(&btf_module_mutex);

		अगर (IS_ENABLED(CONFIG_SYSFS)) अणु
			काष्ठा bin_attribute *attr;

			attr = kzalloc(माप(*attr), GFP_KERNEL);
			अगर (!attr)
				जाओ out;

			sysfs_bin_attr_init(attr);
			attr->attr.name = btf->name;
			attr->attr.mode = 0444;
			attr->size = btf->data_size;
			attr->निजी = btf;
			attr->पढ़ो = btf_module_पढ़ो;

			err = sysfs_create_bin_file(btf_kobj, attr);
			अगर (err) अणु
				pr_warn("failed to register module [%s] BTF in sysfs: %d\n",
					mod->name, err);
				kमुक्त(attr);
				err = 0;
				जाओ out;
			पूर्ण

			btf_mod->sysfs_attr = attr;
		पूर्ण

		अवरोध;
	हाल MODULE_STATE_GOING:
		mutex_lock(&btf_module_mutex);
		list_क्रम_each_entry_safe(btf_mod, पंचांगp, &btf_modules, list) अणु
			अगर (btf_mod->module != module)
				जारी;

			list_del(&btf_mod->list);
			अगर (btf_mod->sysfs_attr)
				sysfs_हटाओ_bin_file(btf_kobj, btf_mod->sysfs_attr);
			btf_put(btf_mod->btf);
			kमुक्त(btf_mod->sysfs_attr);
			kमुक्त(btf_mod);
			अवरोध;
		पूर्ण
		mutex_unlock(&btf_module_mutex);
		अवरोध;
	पूर्ण
out:
	वापस notअगरier_from_त्रुटि_सं(err);
पूर्ण

अटल काष्ठा notअगरier_block btf_module_nb = अणु
	.notअगरier_call = btf_module_notअगरy,
पूर्ण;

अटल पूर्णांक __init btf_module_init(व्योम)
अणु
	रेजिस्टर_module_notअगरier(&btf_module_nb);
	वापस 0;
पूर्ण

fs_initcall(btf_module_init);
#पूर्ण_अगर /* CONFIG_DEBUG_INFO_BTF_MODULES */

काष्ठा module *btf_try_get_module(स्थिर काष्ठा btf *btf)
अणु
	काष्ठा module *res = शून्य;
#अगर_घोषित CONFIG_DEBUG_INFO_BTF_MODULES
	काष्ठा btf_module *btf_mod, *पंचांगp;

	mutex_lock(&btf_module_mutex);
	list_क्रम_each_entry_safe(btf_mod, पंचांगp, &btf_modules, list) अणु
		अगर (btf_mod->btf != btf)
			जारी;

		अगर (try_module_get(btf_mod->module))
			res = btf_mod->module;

		अवरोध;
	पूर्ण
	mutex_unlock(&btf_module_mutex);
#पूर्ण_अगर

	वापस res;
पूर्ण
