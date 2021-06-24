<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <माला.स>
#समावेश "debug.h"

#समावेश "demangle-rust.h"

/*
 * Mangled Rust symbols look like this:
 *
 *     _$LT$std..sys..fd..FileDesc$u20$as$u20$core..ops..Drop$GT$::drop::hc68340e1baa4987a
 *
 * The original symbol is:
 *
 *     <std::sys::fd::FileDesc as core::ops::Drop>::drop
 *
 * The last component of the path is a 64-bit hash in lowerहाल hex, prefixed
 * with "h". Rust करोes not have a global namespace between crates, an illusion
 * which Rust मुख्यtains by using the hash to distinguish things that would
 * otherwise have the same symbol.
 *
 * Any path component not starting with a XID_Start अक्षरacter is prefixed with
 * "_".
 *
 * The following escape sequences are used:
 *
 *     ","  =>  $C$
 *     "@"  =>  $SP$
 *     "*"  =>  $BP$
 *     "&"  =>  $RF$
 *     "<"  =>  $LT$
 *     ">"  =>  $GT$
 *     "("  =>  $LP$
 *     ")"  =>  $RP$
 *     " "  =>  $u20$
 *     "'"  =>  $u27$
 *     "["  =>  $u5b$
 *     "]"  =>  $u5d$
 *     "~"  =>  $u7e$
 *
 * A द्विगुन ".." means "::" and a single "." means "-".
 *
 * The only अक्षरacters allowed in the mangled symbol are a-zA-Z0-9 and _.:$
 */

अटल स्थिर अक्षर *hash_prefix = "::h";
अटल स्थिर माप_प्रकार hash_prefix_len = 3;
अटल स्थिर माप_प्रकार hash_len = 16;

अटल bool is_prefixed_hash(स्थिर अक्षर *start);
अटल bool looks_like_rust(स्थिर अक्षर *sym, माप_प्रकार len);
अटल bool unescape(स्थिर अक्षर **in, अक्षर **out, स्थिर अक्षर *seq, अक्षर value);

/*
 * INPUT:
 *     sym: symbol that has been through BFD-demangling
 *
 * This function looks क्रम the following indicators:
 *
 *  1. The hash must consist of "h" followed by 16 lowerहाल hex digits.
 *
 *  2. As a sanity check, the hash must use between 5 and 15 of the 16 possible
 *     hex digits. This is true of 99.9998% of hashes so once in your lअगरe you
 *     may see a false negative. The poपूर्णांक is to notice path components that
 *     could be Rust hashes but are probably not, like "haaaaaaaaaaaaaaaa". In
 *     this हाल a false positive (non-Rust symbol has an important path
 *     component हटाओd because it looks like a Rust hash) is worse than a
 *     false negative (the rare Rust symbol is not demangled) so this sets the
 *     balance in favor of false negatives.
 *
 *  3. There must be no अक्षरacters other than a-zA-Z0-9 and _.:$
 *
 *  4. There must be no unrecognized $-sign sequences.
 *
 *  5. There must be no sequence of three or more करोts in a row ("...").
 */
bool
rust_is_mangled(स्थिर अक्षर *sym)
अणु
	माप_प्रकार len, len_without_hash;

	अगर (!sym)
		वापस false;

	len = म_माप(sym);
	अगर (len <= hash_prefix_len + hash_len)
		/* Not दीर्घ enough to contain "::h" + hash + something अन्यथा */
		वापस false;

	len_without_hash = len - (hash_prefix_len + hash_len);
	अगर (!is_prefixed_hash(sym + len_without_hash))
		वापस false;

	वापस looks_like_rust(sym, len_without_hash);
पूर्ण

/*
 * A hash is the prefix "::h" followed by 16 lowerहाल hex digits. The hex
 * digits must comprise between 5 and 15 (inclusive) distinct digits.
 */
अटल bool is_prefixed_hash(स्थिर अक्षर *str)
अणु
	स्थिर अक्षर *end;
	bool seen[16];
	माप_प्रकार i;
	पूर्णांक count;

	अगर (म_भेदन(str, hash_prefix, hash_prefix_len))
		वापस false;
	str += hash_prefix_len;

	स_रखो(seen, false, माप(seen));
	क्रम (end = str + hash_len; str < end; str++)
		अगर (*str >= '0' && *str <= '9')
			seen[*str - '0'] = true;
		अन्यथा अगर (*str >= 'a' && *str <= 'f')
			seen[*str - 'a' + 10] = true;
		अन्यथा
			वापस false;

	/* Count how many distinct digits seen */
	count = 0;
	क्रम (i = 0; i < 16; i++)
		अगर (seen[i])
			count++;

	वापस count >= 5 && count <= 15;
पूर्ण

अटल bool looks_like_rust(स्थिर अक्षर *str, माप_प्रकार len)
अणु
	स्थिर अक्षर *end = str + len;

	जबतक (str < end)
		चयन (*str) अणु
		हाल '$':
			अगर (!म_भेदन(str, "$C$", 3))
				str += 3;
			अन्यथा अगर (!म_भेदन(str, "$SP$", 4)
					|| !म_भेदन(str, "$BP$", 4)
					|| !म_भेदन(str, "$RF$", 4)
					|| !म_भेदन(str, "$LT$", 4)
					|| !म_भेदन(str, "$GT$", 4)
					|| !म_भेदन(str, "$LP$", 4)
					|| !म_भेदन(str, "$RP$", 4))
				str += 4;
			अन्यथा अगर (!म_भेदन(str, "$u20$", 5)
					|| !म_भेदन(str, "$u27$", 5)
					|| !म_भेदन(str, "$u5b$", 5)
					|| !म_भेदन(str, "$u5d$", 5)
					|| !म_भेदन(str, "$u7e$", 5))
				str += 5;
			अन्यथा
				वापस false;
			अवरोध;
		हाल '.':
			/* Do not allow three or more consecutive करोts */
			अगर (!म_भेदन(str, "...", 3))
				वापस false;
			/* Fall through */
		हाल 'a' ... 'z':
		हाल 'A' ... 'Z':
		हाल '0' ... '9':
		हाल '_':
		हाल ':':
			str++;
			अवरोध;
		शेष:
			वापस false;
		पूर्ण

	वापस true;
पूर्ण

/*
 * INPUT:
 *     sym: symbol क्रम which rust_is_mangled(sym) वापसs true
 *
 * The input is demangled in-place because the mangled name is always दीर्घer
 * than the demangled one.
 */
व्योम
rust_demangle_sym(अक्षर *sym)
अणु
	स्थिर अक्षर *in;
	अक्षर *out;
	स्थिर अक्षर *end;

	अगर (!sym)
		वापस;

	in = sym;
	out = sym;
	end = sym + म_माप(sym) - (hash_prefix_len + hash_len);

	जबतक (in < end)
		चयन (*in) अणु
		हाल '$':
			अगर (!(unescape(&in, &out, "$C$", ',')
					|| unescape(&in, &out, "$SP$", '@')
					|| unescape(&in, &out, "$BP$", '*')
					|| unescape(&in, &out, "$RF$", '&')
					|| unescape(&in, &out, "$LT$", '<')
					|| unescape(&in, &out, "$GT$", '>')
					|| unescape(&in, &out, "$LP$", '(')
					|| unescape(&in, &out, "$RP$", ')')
					|| unescape(&in, &out, "$u20$", ' ')
					|| unescape(&in, &out, "$u27$", '\'')
					|| unescape(&in, &out, "$u5b$", '[')
					|| unescape(&in, &out, "$u5d$", ']')
					|| unescape(&in, &out, "$u7e$", '~'))) अणु
				pr_err("demangle-rust: unexpected escape sequence");
				जाओ करोne;
			पूर्ण
			अवरोध;
		हाल '_':
			/*
			 * If this is the start of a path component and the next
			 * अक्षरacter is an escape sequence, ignore the
			 * underscore. The mangler inserts an underscore to make
			 * sure the path component begins with a XID_Start
			 * अक्षरacter.
			 */
			अगर ((in == sym || in[-1] == ':') && in[1] == '$')
				in++;
			अन्यथा
				*out++ = *in++;
			अवरोध;
		हाल '.':
			अगर (in[1] == '.') अणु
				/* ".." becomes "::" */
				*out++ = ':';
				*out++ = ':';
				in += 2;
			पूर्ण अन्यथा अणु
				/* "." becomes "-" */
				*out++ = '-';
				in++;
			पूर्ण
			अवरोध;
		हाल 'a' ... 'z':
		हाल 'A' ... 'Z':
		हाल '0' ... '9':
		हाल ':':
			*out++ = *in++;
			अवरोध;
		शेष:
			pr_err("demangle-rust: unexpected character '%c' in symbol\n",
				*in);
			जाओ करोne;
		पूर्ण

करोne:
	*out = '\0';
पूर्ण

अटल bool unescape(स्थिर अक्षर **in, अक्षर **out, स्थिर अक्षर *seq, अक्षर value)
अणु
	माप_प्रकार len = म_माप(seq);

	अगर (म_भेदन(*in, seq, len))
		वापस false;

	**out = value;

	*in += len;
	*out += 1;

	वापस true;
पूर्ण
