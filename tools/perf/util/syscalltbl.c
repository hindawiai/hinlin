<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * System call table mapper
 *
 * (C) 2016 Arnalकरो Carvalho de Melo <acme@redhat.com>
 */

#समावेश "syscalltbl.h"
#समावेश <मानककोष.स>
#समावेश <linux/compiler.h>
#समावेश <linux/zभाग.स>

#अगर_घोषित HAVE_SYSCALL_TABLE_SUPPORT
#समावेश <माला.स>
#समावेश "string2.h"

#अगर defined(__x86_64__)
#समावेश <यंत्र/syscalls_64.c>
स्थिर पूर्णांक syscalltbl_native_max_id = SYSCALLTBL_x86_64_MAX_ID;
अटल स्थिर अक्षर **syscalltbl_native = syscalltbl_x86_64;
#या_अगर defined(__s390x__)
#समावेश <यंत्र/syscalls_64.c>
स्थिर पूर्णांक syscalltbl_native_max_id = SYSCALLTBL_S390_64_MAX_ID;
अटल स्थिर अक्षर **syscalltbl_native = syscalltbl_s390_64;
#या_अगर defined(__घातerpc64__)
#समावेश <यंत्र/syscalls_64.c>
स्थिर पूर्णांक syscalltbl_native_max_id = SYSCALLTBL_POWERPC_64_MAX_ID;
अटल स्थिर अक्षर **syscalltbl_native = syscalltbl_घातerpc_64;
#या_अगर defined(__घातerpc__)
#समावेश <यंत्र/syscalls_32.c>
स्थिर पूर्णांक syscalltbl_native_max_id = SYSCALLTBL_POWERPC_32_MAX_ID;
अटल स्थिर अक्षर **syscalltbl_native = syscalltbl_घातerpc_32;
#या_अगर defined(__aarch64__)
#समावेश <यंत्र/syscalls.c>
स्थिर पूर्णांक syscalltbl_native_max_id = SYSCALLTBL_ARM64_MAX_ID;
अटल स्थिर अक्षर **syscalltbl_native = syscalltbl_arm64;
#या_अगर defined(__mips__)
#समावेश <यंत्र/syscalls_n64.c>
स्थिर पूर्णांक syscalltbl_native_max_id = SYSCALLTBL_MIPS_N64_MAX_ID;
अटल स्थिर अक्षर **syscalltbl_native = syscalltbl_mips_n64;
#पूर्ण_अगर

काष्ठा syscall अणु
	पूर्णांक id;
	स्थिर अक्षर *name;
पूर्ण;

अटल पूर्णांक syscallcmpname(स्थिर व्योम *vkey, स्थिर व्योम *ventry)
अणु
	स्थिर अक्षर *key = vkey;
	स्थिर काष्ठा syscall *entry = ventry;

	वापस म_भेद(key, entry->name);
पूर्ण

अटल पूर्णांक syscallcmp(स्थिर व्योम *va, स्थिर व्योम *vb)
अणु
	स्थिर काष्ठा syscall *a = va, *b = vb;

	वापस म_भेद(a->name, b->name);
पूर्ण

अटल पूर्णांक syscalltbl__init_native(काष्ठा syscalltbl *tbl)
अणु
	पूर्णांक nr_entries = 0, i, j;
	काष्ठा syscall *entries;

	क्रम (i = 0; i <= syscalltbl_native_max_id; ++i)
		अगर (syscalltbl_native[i])
			++nr_entries;

	entries = tbl->syscalls.entries = दो_स्मृति(माप(काष्ठा syscall) * nr_entries);
	अगर (tbl->syscalls.entries == शून्य)
		वापस -1;

	क्रम (i = 0, j = 0; i <= syscalltbl_native_max_id; ++i) अणु
		अगर (syscalltbl_native[i]) अणु
			entries[j].name = syscalltbl_native[i];
			entries[j].id = i;
			++j;
		पूर्ण
	पूर्ण

	क्विक(tbl->syscalls.entries, nr_entries, माप(काष्ठा syscall), syscallcmp);
	tbl->syscalls.nr_entries = nr_entries;
	tbl->syscalls.max_id	 = syscalltbl_native_max_id;
	वापस 0;
पूर्ण

काष्ठा syscalltbl *syscalltbl__new(व्योम)
अणु
	काष्ठा syscalltbl *tbl = दो_स्मृति(माप(*tbl));
	अगर (tbl) अणु
		अगर (syscalltbl__init_native(tbl)) अणु
			मुक्त(tbl);
			वापस शून्य;
		पूर्ण
	पूर्ण
	वापस tbl;
पूर्ण

व्योम syscalltbl__delete(काष्ठा syscalltbl *tbl)
अणु
	zमुक्त(&tbl->syscalls.entries);
	मुक्त(tbl);
पूर्ण

स्थिर अक्षर *syscalltbl__name(स्थिर काष्ठा syscalltbl *tbl __maybe_unused, पूर्णांक id)
अणु
	वापस id <= syscalltbl_native_max_id ? syscalltbl_native[id]: शून्य;
पूर्ण

पूर्णांक syscalltbl__id(काष्ठा syscalltbl *tbl, स्थिर अक्षर *name)
अणु
	काष्ठा syscall *sc = द्वा_खोज(name, tbl->syscalls.entries,
				     tbl->syscalls.nr_entries, माप(*sc),
				     syscallcmpname);

	वापस sc ? sc->id : -1;
पूर्ण

पूर्णांक syscalltbl__strglobmatch_next(काष्ठा syscalltbl *tbl, स्थिर अक्षर *syscall_glob, पूर्णांक *idx)
अणु
	पूर्णांक i;
	काष्ठा syscall *syscalls = tbl->syscalls.entries;

	क्रम (i = *idx + 1; i < tbl->syscalls.nr_entries; ++i) अणु
		अगर (strglobmatch(syscalls[i].name, syscall_glob)) अणु
			*idx = i;
			वापस syscalls[i].id;
		पूर्ण
	पूर्ण

	वापस -1;
पूर्ण

पूर्णांक syscalltbl__strglobmatch_first(काष्ठा syscalltbl *tbl, स्थिर अक्षर *syscall_glob, पूर्णांक *idx)
अणु
	*idx = -1;
	वापस syscalltbl__strglobmatch_next(tbl, syscall_glob, idx);
पूर्ण

#अन्यथा /* HAVE_SYSCALL_TABLE_SUPPORT */

#समावेश <libaudit.h>

काष्ठा syscalltbl *syscalltbl__new(व्योम)
अणु
	काष्ठा syscalltbl *tbl = zalloc(माप(*tbl));
	अगर (tbl)
		tbl->audit_machine = audit_detect_machine();
	वापस tbl;
पूर्ण

व्योम syscalltbl__delete(काष्ठा syscalltbl *tbl)
अणु
	मुक्त(tbl);
पूर्ण

स्थिर अक्षर *syscalltbl__name(स्थिर काष्ठा syscalltbl *tbl, पूर्णांक id)
अणु
	वापस audit_syscall_to_name(id, tbl->audit_machine);
पूर्ण

पूर्णांक syscalltbl__id(काष्ठा syscalltbl *tbl, स्थिर अक्षर *name)
अणु
	वापस audit_name_to_syscall(name, tbl->audit_machine);
पूर्ण

पूर्णांक syscalltbl__strglobmatch_next(काष्ठा syscalltbl *tbl __maybe_unused,
				  स्थिर अक्षर *syscall_glob __maybe_unused, पूर्णांक *idx __maybe_unused)
अणु
	वापस -1;
पूर्ण

पूर्णांक syscalltbl__strglobmatch_first(काष्ठा syscalltbl *tbl, स्थिर अक्षर *syscall_glob, पूर्णांक *idx)
अणु
	वापस syscalltbl__strglobmatch_next(tbl, syscall_glob, idx);
पूर्ण
#पूर्ण_अगर /* HAVE_SYSCALL_TABLE_SUPPORT */
