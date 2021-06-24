<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
#समावेश <linux/futex.h>

#अगर_अघोषित FUTEX_BITSET_MATCH_ANY
#घोषणा FUTEX_BITSET_MATCH_ANY 0xffffffff
#पूर्ण_अगर

अटल माप_प्रकार syscall_arg__scnम_लिखो_futex_val3(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	स्थिर अक्षर *prefix = "FUTEX_BITSET_";
	अचिन्हित पूर्णांक bitset = arg->val;

	अगर (bitset == FUTEX_BITSET_MATCH_ANY)
		वापस scnम_लिखो(bf, size, "%s%s", arg->show_string_prefix ? prefix : "", "MATCH_ANY");

	वापस scnम_लिखो(bf, size, "%#xd", bitset);
पूर्ण

#घोषणा SCA_FUTEX_VAL3  syscall_arg__scnम_लिखो_futex_val3
