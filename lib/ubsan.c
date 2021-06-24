<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * UBSAN error reporting functions
 *
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 * Author: Andrey Ryabinin <ryabinin.a.a@gmail.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/bug.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/uaccess.h>

#समावेश "ubsan.h"

अटल स्थिर अक्षर * स्थिर type_check_kinds[] = अणु
	"load of",
	"store to",
	"reference binding to",
	"member access within",
	"member call on",
	"constructor call on",
	"downcast of",
	"downcast of"
पूर्ण;

#घोषणा REPORTED_BIT 31

#अगर (BITS_PER_LONG == 64) && defined(__BIG_ENDIAN)
#घोषणा COLUMN_MASK (~(1U << REPORTED_BIT))
#घोषणा LINE_MASK   (~0U)
#अन्यथा
#घोषणा COLUMN_MASK   (~0U)
#घोषणा LINE_MASK (~(1U << REPORTED_BIT))
#पूर्ण_अगर

#घोषणा VALUE_LENGTH 40

अटल bool was_reported(काष्ठा source_location *location)
अणु
	वापस test_and_set_bit(REPORTED_BIT, &location->reported);
पूर्ण

अटल bool suppress_report(काष्ठा source_location *loc)
अणु
	वापस current->in_ubsan || was_reported(loc);
पूर्ण

अटल bool type_is_पूर्णांक(काष्ठा type_descriptor *type)
अणु
	वापस type->type_kind == type_kind_पूर्णांक;
पूर्ण

अटल bool type_is_चिन्हित(काष्ठा type_descriptor *type)
अणु
	WARN_ON(!type_is_पूर्णांक(type));
	वापस  type->type_info & 1;
पूर्ण

अटल अचिन्हित type_bit_width(काष्ठा type_descriptor *type)
अणु
	वापस 1 << (type->type_info >> 1);
पूर्ण

अटल bool is_अंतरभूत_पूर्णांक(काष्ठा type_descriptor *type)
अणु
	अचिन्हित अंतरभूत_bits = माप(अचिन्हित दीर्घ)*8;
	अचिन्हित bits = type_bit_width(type);

	WARN_ON(!type_is_पूर्णांक(type));

	वापस bits <= अंतरभूत_bits;
पूर्ण

अटल s_max get_चिन्हित_val(काष्ठा type_descriptor *type, व्योम *val)
अणु
	अगर (is_अंतरभूत_पूर्णांक(type)) अणु
		अचिन्हित extra_bits = माप(s_max)*8 - type_bit_width(type);
		अचिन्हित दीर्घ uदीर्घ_val = (अचिन्हित दीर्घ)val;

		वापस ((s_max)uदीर्घ_val) << extra_bits >> extra_bits;
	पूर्ण

	अगर (type_bit_width(type) == 64)
		वापस *(s64 *)val;

	वापस *(s_max *)val;
पूर्ण

अटल bool val_is_negative(काष्ठा type_descriptor *type, व्योम *val)
अणु
	वापस type_is_चिन्हित(type) && get_चिन्हित_val(type, val) < 0;
पूर्ण

अटल u_max get_अचिन्हित_val(काष्ठा type_descriptor *type, व्योम *val)
अणु
	अगर (is_अंतरभूत_पूर्णांक(type))
		वापस (अचिन्हित दीर्घ)val;

	अगर (type_bit_width(type) == 64)
		वापस *(u64 *)val;

	वापस *(u_max *)val;
पूर्ण

अटल व्योम val_to_string(अक्षर *str, माप_प्रकार size, काष्ठा type_descriptor *type,
			व्योम *value)
अणु
	अगर (type_is_पूर्णांक(type)) अणु
		अगर (type_bit_width(type) == 128) अणु
#अगर defined(CONFIG_ARCH_SUPPORTS_INT128)
			u_max val = get_अचिन्हित_val(type, value);

			scnम_लिखो(str, size, "0x%08x%08x%08x%08x",
				(u32)(val >> 96),
				(u32)(val >> 64),
				(u32)(val >> 32),
				(u32)(val));
#अन्यथा
			WARN_ON(1);
#पूर्ण_अगर
		पूर्ण अन्यथा अगर (type_is_चिन्हित(type)) अणु
			scnम_लिखो(str, size, "%lld",
				(s64)get_चिन्हित_val(type, value));
		पूर्ण अन्यथा अणु
			scnम_लिखो(str, size, "%llu",
				(u64)get_अचिन्हित_val(type, value));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ubsan_prologue(काष्ठा source_location *loc, स्थिर अक्षर *reason)
अणु
	current->in_ubsan++;

	pr_err("========================================"
		"========================================\n");
	pr_err("UBSAN: %s in %s:%d:%d\n", reason, loc->file_name,
		loc->line & LINE_MASK, loc->column & COLUMN_MASK);
पूर्ण

अटल व्योम ubsan_epilogue(व्योम)
अणु
	dump_stack();
	pr_err("========================================"
		"========================================\n");

	current->in_ubsan--;

	अगर (panic_on_warn) अणु
		/*
		 * This thपढ़ो may hit another WARN() in the panic path.
		 * Resetting this prevents additional WARN() from panicking the
		 * प्रणाली on this thपढ़ो.  Other thपढ़ोs are blocked by the
		 * panic_mutex in panic().
		 */
		panic_on_warn = 0;
		panic("panic_on_warn set ...\n");
	पूर्ण
पूर्ण

व्योम __ubsan_handle_भागrem_overflow(व्योम *_data, व्योम *lhs, व्योम *rhs)
अणु
	काष्ठा overflow_data *data = _data;
	अक्षर rhs_val_str[VALUE_LENGTH];

	अगर (suppress_report(&data->location))
		वापस;

	ubsan_prologue(&data->location, "division-overflow");

	val_to_string(rhs_val_str, माप(rhs_val_str), data->type, rhs);

	अगर (type_is_चिन्हित(data->type) && get_चिन्हित_val(data->type, rhs) == -1)
		pr_err("division of %s by -1 cannot be represented in type %s\n",
			rhs_val_str, data->type->type_name);
	अन्यथा
		pr_err("division by zero\n");

	ubsan_epilogue();
पूर्ण
EXPORT_SYMBOL(__ubsan_handle_भागrem_overflow);

अटल व्योम handle_null_ptr_deref(काष्ठा type_mismatch_data_common *data)
अणु
	अगर (suppress_report(data->location))
		वापस;

	ubsan_prologue(data->location, "null-ptr-deref");

	pr_err("%s null pointer of type %s\n",
		type_check_kinds[data->type_check_kind],
		data->type->type_name);

	ubsan_epilogue();
पूर्ण

अटल व्योम handle_misaligned_access(काष्ठा type_mismatch_data_common *data,
				अचिन्हित दीर्घ ptr)
अणु
	अगर (suppress_report(data->location))
		वापस;

	ubsan_prologue(data->location, "misaligned-access");

	pr_err("%s misaligned address %p for type %s\n",
		type_check_kinds[data->type_check_kind],
		(व्योम *)ptr, data->type->type_name);
	pr_err("which requires %ld byte alignment\n", data->alignment);

	ubsan_epilogue();
पूर्ण

अटल व्योम handle_object_size_mismatch(काष्ठा type_mismatch_data_common *data,
					अचिन्हित दीर्घ ptr)
अणु
	अगर (suppress_report(data->location))
		वापस;

	ubsan_prologue(data->location, "object-size-mismatch");
	pr_err("%s address %p with insufficient space\n",
		type_check_kinds[data->type_check_kind],
		(व्योम *) ptr);
	pr_err("for an object of type %s\n", data->type->type_name);
	ubsan_epilogue();
पूर्ण

अटल व्योम ubsan_type_mismatch_common(काष्ठा type_mismatch_data_common *data,
				अचिन्हित दीर्घ ptr)
अणु
	अचिन्हित दीर्घ flags = user_access_save();

	अगर (!ptr)
		handle_null_ptr_deref(data);
	अन्यथा अगर (data->alignment && !IS_ALIGNED(ptr, data->alignment))
		handle_misaligned_access(data, ptr);
	अन्यथा
		handle_object_size_mismatch(data, ptr);

	user_access_restore(flags);
पूर्ण

व्योम __ubsan_handle_type_mismatch(काष्ठा type_mismatch_data *data,
				व्योम *ptr)
अणु
	काष्ठा type_mismatch_data_common common_data = अणु
		.location = &data->location,
		.type = data->type,
		.alignment = data->alignment,
		.type_check_kind = data->type_check_kind
	पूर्ण;

	ubsan_type_mismatch_common(&common_data, (अचिन्हित दीर्घ)ptr);
पूर्ण
EXPORT_SYMBOL(__ubsan_handle_type_mismatch);

व्योम __ubsan_handle_type_mismatch_v1(व्योम *_data, व्योम *ptr)
अणु
	काष्ठा type_mismatch_data_v1 *data = _data;
	काष्ठा type_mismatch_data_common common_data = अणु
		.location = &data->location,
		.type = data->type,
		.alignment = 1UL << data->log_alignment,
		.type_check_kind = data->type_check_kind
	पूर्ण;

	ubsan_type_mismatch_common(&common_data, (अचिन्हित दीर्घ)ptr);
पूर्ण
EXPORT_SYMBOL(__ubsan_handle_type_mismatch_v1);

व्योम __ubsan_handle_out_of_bounds(व्योम *_data, व्योम *index)
अणु
	काष्ठा out_of_bounds_data *data = _data;
	अक्षर index_str[VALUE_LENGTH];

	अगर (suppress_report(&data->location))
		वापस;

	ubsan_prologue(&data->location, "array-index-out-of-bounds");

	val_to_string(index_str, माप(index_str), data->index_type, index);
	pr_err("index %s is out of range for type %s\n", index_str,
		data->array_type->type_name);
	ubsan_epilogue();
पूर्ण
EXPORT_SYMBOL(__ubsan_handle_out_of_bounds);

व्योम __ubsan_handle_shअगरt_out_of_bounds(व्योम *_data, व्योम *lhs, व्योम *rhs)
अणु
	काष्ठा shअगरt_out_of_bounds_data *data = _data;
	काष्ठा type_descriptor *rhs_type = data->rhs_type;
	काष्ठा type_descriptor *lhs_type = data->lhs_type;
	अक्षर rhs_str[VALUE_LENGTH];
	अक्षर lhs_str[VALUE_LENGTH];
	अचिन्हित दीर्घ ua_flags = user_access_save();

	अगर (suppress_report(&data->location))
		जाओ out;

	ubsan_prologue(&data->location, "shift-out-of-bounds");

	val_to_string(rhs_str, माप(rhs_str), rhs_type, rhs);
	val_to_string(lhs_str, माप(lhs_str), lhs_type, lhs);

	अगर (val_is_negative(rhs_type, rhs))
		pr_err("shift exponent %s is negative\n", rhs_str);

	अन्यथा अगर (get_अचिन्हित_val(rhs_type, rhs) >=
		type_bit_width(lhs_type))
		pr_err("shift exponent %s is too large for %u-bit type %s\n",
			rhs_str,
			type_bit_width(lhs_type),
			lhs_type->type_name);
	अन्यथा अगर (val_is_negative(lhs_type, lhs))
		pr_err("left shift of negative value %s\n",
			lhs_str);
	अन्यथा
		pr_err("left shift of %s by %s places cannot be"
			" represented in type %s\n",
			lhs_str, rhs_str,
			lhs_type->type_name);

	ubsan_epilogue();
out:
	user_access_restore(ua_flags);
पूर्ण
EXPORT_SYMBOL(__ubsan_handle_shअगरt_out_of_bounds);


व्योम __ubsan_handle_builtin_unreachable(व्योम *_data)
अणु
	काष्ठा unreachable_data *data = _data;
	ubsan_prologue(&data->location, "unreachable");
	pr_err("calling __builtin_unreachable()\n");
	ubsan_epilogue();
	panic("can't return from __builtin_unreachable()");
पूर्ण
EXPORT_SYMBOL(__ubsan_handle_builtin_unreachable);

व्योम __ubsan_handle_load_invalid_value(व्योम *_data, व्योम *val)
अणु
	काष्ठा invalid_value_data *data = _data;
	अक्षर val_str[VALUE_LENGTH];

	अगर (suppress_report(&data->location))
		वापस;

	ubsan_prologue(&data->location, "invalid-load");

	val_to_string(val_str, माप(val_str), data->type, val);

	pr_err("load of value %s is not a valid value for type %s\n",
		val_str, data->type->type_name);

	ubsan_epilogue();
पूर्ण
EXPORT_SYMBOL(__ubsan_handle_load_invalid_value);

व्योम __ubsan_handle_alignment_assumption(व्योम *_data, अचिन्हित दीर्घ ptr,
					 अचिन्हित दीर्घ align,
					 अचिन्हित दीर्घ offset);
व्योम __ubsan_handle_alignment_assumption(व्योम *_data, अचिन्हित दीर्घ ptr,
					 अचिन्हित दीर्घ align,
					 अचिन्हित दीर्घ offset)
अणु
	काष्ठा alignment_assumption_data *data = _data;
	अचिन्हित दीर्घ real_ptr;

	अगर (suppress_report(&data->location))
		वापस;

	ubsan_prologue(&data->location, "alignment-assumption");

	अगर (offset)
		pr_err("assumption of %lu byte alignment (with offset of %lu byte) for pointer of type %s failed",
		       align, offset, data->type->type_name);
	अन्यथा
		pr_err("assumption of %lu byte alignment for pointer of type %s failed",
		       align, data->type->type_name);

	real_ptr = ptr - offset;
	pr_err("%saddress is %lu aligned, misalignment offset is %lu bytes",
	       offset ? "offset " : "", BIT(real_ptr ? __ffs(real_ptr) : 0),
	       real_ptr & (align - 1));

	ubsan_epilogue();
पूर्ण
EXPORT_SYMBOL(__ubsan_handle_alignment_assumption);
