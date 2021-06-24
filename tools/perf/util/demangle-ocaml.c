<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश "util/string2.h"

#समावेश "demangle-ocaml.h"

#समावेश <linux/प्रकार.स>

अटल स्थिर अक्षर *caml_prefix = "caml";
अटल स्थिर माप_प्रकार caml_prefix_len = 4;

/* mangled OCaml symbols start with "caml" followed by an upper-हाल letter */
अटल bool
ocaml_is_mangled(स्थिर अक्षर *sym)
अणु
	वापस 0 == म_भेदन(sym, caml_prefix, caml_prefix_len)
		&& है_बड़ा(sym[caml_prefix_len]);
पूर्ण

/*
 * input:
 *     sym: a symbol which may have been mangled by the OCaml compiler
 * वापस:
 *     अगर the input करोesn't look like a mangled OCaml symbol, शून्य is वापसed
 *     otherwise, a newly allocated string containing the demangled symbol is वापसed
 */
अक्षर *
ocaml_demangle_sym(स्थिर अक्षर *sym)
अणु
	अक्षर *result;
	पूर्णांक j = 0;
	पूर्णांक i;
	पूर्णांक len;

	अगर (!ocaml_is_mangled(sym)) अणु
		वापस शून्य;
	पूर्ण

	len = म_माप(sym);

	/* the demangled symbol is always smaller than the mangled symbol */
	result = दो_स्मृति(len + 1);
	अगर (!result)
		वापस शून्य;

	/* skip "caml" prefix */
	i = caml_prefix_len;

	जबतक (i < len) अणु
		अगर (sym[i] == '_' && sym[i + 1] == '_') अणु
			/* "__" -> "." */
			result[j++] = '.';
			i += 2;
		पूर्ण
		अन्यथा अगर (sym[i] == '$' && है_षष्ठादशक(sym[i + 1]) && है_षष्ठादशक(sym[i + 2])) अणु
			/* "$xx" is a hex-encoded अक्षरacter */
			result[j++] = (hex(sym[i + 1]) << 4) | hex(sym[i + 2]);
			i += 3;
		पूर्ण
		अन्यथा अणु
			result[j++] = sym[i++];
		पूर्ण
	पूर्ण
	result[j] = '\0';

	वापस result;
पूर्ण
