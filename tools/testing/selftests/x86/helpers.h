<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#अगर_अघोषित __SELFTESTS_X86_HELPERS_H
#घोषणा __SELFTESTS_X86_HELPERS_H

#समावेश <यंत्र/processor-flags.h>

अटल अंतरभूत अचिन्हित दीर्घ get_eflags(व्योम)
अणु
#अगर_घोषित __x86_64__
	वापस __builtin_ia32_पढ़ोeflags_u64();
#अन्यथा
	वापस __builtin_ia32_पढ़ोeflags_u32();
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम set_eflags(अचिन्हित दीर्घ eflags)
अणु
#अगर_घोषित __x86_64__
	__builtin_ia32_ग_लिखोeflags_u64(eflags);
#अन्यथा
	__builtin_ia32_ग_लिखोeflags_u32(eflags);
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* __SELFTESTS_X86_HELPERS_H */
