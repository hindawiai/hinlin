<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
अटल काष्ठा resword अणु
	स्थिर अक्षर *name;
	पूर्णांक token;
पूर्ण keywords[] = अणु
	अणु "__GENKSYMS_EXPORT_SYMBOL", EXPORT_SYMBOL_KEYW पूर्ण,
	अणु "__asm", ASM_KEYW पूर्ण,
	अणु "__asm__", ASM_KEYW पूर्ण,
	अणु "__attribute", ATTRIBUTE_KEYW पूर्ण,
	अणु "__attribute__", ATTRIBUTE_KEYW पूर्ण,
	अणु "__const", CONST_KEYW पूर्ण,
	अणु "__const__", CONST_KEYW पूर्ण,
	अणु "__extension__", EXTENSION_KEYW पूर्ण,
	अणु "__inline", INLINE_KEYW पूर्ण,
	अणु "__inline__", INLINE_KEYW पूर्ण,
	अणु "__signed", SIGNED_KEYW पूर्ण,
	अणु "__signed__", SIGNED_KEYW पूर्ण,
	अणु "__typeof", TYPखातापूर्ण_KEYW पूर्ण,
	अणु "__typeof__", TYPखातापूर्ण_KEYW पूर्ण,
	अणु "__volatile", VOLATILE_KEYW पूर्ण,
	अणु "__volatile__", VOLATILE_KEYW पूर्ण,
	अणु "__builtin_va_list", VA_LIST_KEYW पूर्ण,

	अणु "__int128", BUILTIN_INT_KEYW पूर्ण,
	अणु "__int128_t", BUILTIN_INT_KEYW पूर्ण,
	अणु "__uint128_t", BUILTIN_INT_KEYW पूर्ण,

	// According to rth, c99 defines "_Bool", "__restrict", "__restrict__", "restrict".  KAO
	अणु "_Bool", BOOL_KEYW पूर्ण,
	अणु "__restrict", RESTRICT_KEYW पूर्ण,
	अणु "__restrict__", RESTRICT_KEYW पूर्ण,
	अणु "restrict", RESTRICT_KEYW पूर्ण,
	अणु "asm", ASM_KEYW पूर्ण,

	// c11 keywords that can be used at module scope
	अणु "_Static_assert", STATIC_ASSERT_KEYW पूर्ण,

	// attribute commented out in modutils 2.4.2.  People are using 'attribute' as a
	// field name which अवरोधs the genksyms parser.  It is not a gcc keyword anyway.
	// KAO. पूर्ण,
	// अणु "attribute", ATTRIBUTE_KEYW पूर्ण,

	अणु "auto", AUTO_KEYW पूर्ण,
	अणु "char", CHAR_KEYW पूर्ण,
	अणु "const", CONST_KEYW पूर्ण,
	अणु "double", DOUBLE_KEYW पूर्ण,
	अणु "enum", ENUM_KEYW पूर्ण,
	अणु "extern", EXTERN_KEYW पूर्ण,
	अणु "float", FLOAT_KEYW पूर्ण,
	अणु "inline", INLINE_KEYW पूर्ण,
	अणु "int", INT_KEYW पूर्ण,
	अणु "long", LONG_KEYW पूर्ण,
	अणु "register", REGISTER_KEYW पूर्ण,
	अणु "short", SHORT_KEYW पूर्ण,
	अणु "signed", SIGNED_KEYW पूर्ण,
	अणु "static", STATIC_KEYW पूर्ण,
	अणु "struct", STRUCT_KEYW पूर्ण,
	अणु "typedef", TYPEDEF_KEYW पूर्ण,
	अणु "typeof", TYPखातापूर्ण_KEYW पूर्ण,
	अणु "union", UNION_KEYW पूर्ण,
	अणु "unsigned", UNSIGNED_KEYW पूर्ण,
	अणु "void", VOID_KEYW पूर्ण,
	अणु "volatile", VOLATILE_KEYW पूर्ण,
पूर्ण;

#घोषणा NR_KEYWORDS (माप(keywords)/माप(काष्ठा resword))

अटल पूर्णांक is_reserved_word(रेजिस्टर स्थिर अक्षर *str, रेजिस्टर अचिन्हित पूर्णांक len)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < NR_KEYWORDS; i++) अणु
		काष्ठा resword *r = keywords + i;
		पूर्णांक l = म_माप(r->name);
		अगर (len == l && !स_भेद(str, r->name, len))
			वापस r->token;
	पूर्ण
	वापस -1;
पूर्ण
