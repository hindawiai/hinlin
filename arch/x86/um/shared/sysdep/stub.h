<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <यंत्र/unistd.h>
#समावेश <sys/mman.h>
#समावेश <संकेत.स>
#समावेश <as-layout.h>
#समावेश <stub-data.h>

#अगर_घोषित __i386__
#समावेश "stub_32.h"
#अन्यथा
#समावेश "stub_64.h"
#पूर्ण_अगर

बाह्य व्योम stub_segv_handler(पूर्णांक, siginfo_t *, व्योम *);
बाह्य व्योम stub_clone_handler(व्योम);
