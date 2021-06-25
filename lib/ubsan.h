<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LIB_UBSAN_H
#घोषणा _LIB_UBSAN_H

क्रमागत अणु
	type_kind_पूर्णांक = 0,
	type_kind_भग्न = 1,
	type_unknown = 0xffff
पूर्ण;

काष्ठा type_descriptor अणु
	u16 type_kind;
	u16 type_info;
	अक्षर type_name[1];
पूर्ण;

काष्ठा source_location अणु
	स्थिर अक्षर *file_name;
	जोड़ अणु
		अचिन्हित दीर्घ reported;
		काष्ठा अणु
			u32 line;
			u32 column;
		पूर्ण;
	पूर्ण;
पूर्ण;

काष्ठा overflow_data अणु
	काष्ठा source_location location;
	काष्ठा type_descriptor *type;
पूर्ण;

काष्ठा type_mismatch_data अणु
	काष्ठा source_location location;
	काष्ठा type_descriptor *type;
	अचिन्हित दीर्घ alignment;
	अचिन्हित अक्षर type_check_kind;
पूर्ण;

काष्ठा type_mismatch_data_v1 अणु
	काष्ठा source_location location;
	काष्ठा type_descriptor *type;
	अचिन्हित अक्षर log_alignment;
	अचिन्हित अक्षर type_check_kind;
पूर्ण;

काष्ठा type_mismatch_data_common अणु
	काष्ठा source_location *location;
	काष्ठा type_descriptor *type;
	अचिन्हित दीर्घ alignment;
	अचिन्हित अक्षर type_check_kind;
पूर्ण;

काष्ठा nonnull_arg_data अणु
	काष्ठा source_location location;
	काष्ठा source_location attr_location;
	पूर्णांक arg_index;
पूर्ण;

काष्ठा out_of_bounds_data अणु
	काष्ठा source_location location;
	काष्ठा type_descriptor *array_type;
	काष्ठा type_descriptor *index_type;
पूर्ण;

काष्ठा shअगरt_out_of_bounds_data अणु
	काष्ठा source_location location;
	काष्ठा type_descriptor *lhs_type;
	काष्ठा type_descriptor *rhs_type;
पूर्ण;

काष्ठा unreachable_data अणु
	काष्ठा source_location location;
पूर्ण;

काष्ठा invalid_value_data अणु
	काष्ठा source_location location;
	काष्ठा type_descriptor *type;
पूर्ण;

काष्ठा alignment_assumption_data अणु
	काष्ठा source_location location;
	काष्ठा source_location assumption_location;
	काष्ठा type_descriptor *type;
पूर्ण;

#अगर defined(CONFIG_ARCH_SUPPORTS_INT128)
प्रकार __पूर्णांक128 s_max;
प्रकार अचिन्हित __पूर्णांक128 u_max;
#अन्यथा
प्रकार s64 s_max;
प्रकार u64 u_max;
#पूर्ण_अगर

#पूर्ण_अगर
