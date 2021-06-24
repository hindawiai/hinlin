<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */

#अगर_अघोषित PARSE_VDSO_H
#घोषणा PARSE_VDSO_H

#समावेश <मानक_निवेशt.h>

/*
 * To use this vDSO parser, first call one of the vdso_init_* functions.
 * If you've alपढ़ोy parsed auxv, then pass the value of AT_SYSINFO_EHDR
 * to vdso_init_from_sysinfo_ehdr.  Otherwise pass auxv to vdso_init_from_auxv.
 * Then call vdso_sym क्रम each symbol you want.  For example, to look up
 * समय_लोofday on x86_64, use:
 *
 *     <some poपूर्णांकer> = vdso_sym("LINUX_2.6", "gettimeofday");
 * or
 *     <some poपूर्णांकer> = vdso_sym("LINUX_2.6", "__vdso_gettimeofday");
 *
 * vdso_sym will वापस 0 अगर the symbol करोesn't exist or अगर the init function
 * failed or was not called.  vdso_sym is a little slow, so its वापस value
 * should be cached.
 *
 * vdso_sym is thपढ़ोsafe; the init functions are not.
 *
 * These are the prototypes:
 */
व्योम *vdso_sym(स्थिर अक्षर *version, स्थिर अक्षर *name);
व्योम vdso_init_from_sysinfo_ehdr(uपूर्णांकptr_t base);
व्योम vdso_init_from_auxv(व्योम *auxv);

#पूर्ण_अगर
