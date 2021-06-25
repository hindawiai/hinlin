<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <linux/module.h>

/* Some of this are builtin function (some are not but could in the future),
 * so I *must* declare good prototypes क्रम them and then EXPORT them.
 * The kernel code uses the macro defined by include/linux/माला.स,
 * so I undef macros; the userspace code करोes not include that and I
 * add an EXPORT क्रम the glibc one.
 */

#अघोषित म_माप
#अघोषित म_माला
#अघोषित स_नकल
#अघोषित स_रखो

बाह्य माप_प्रकार म_माप(स्थिर अक्षर *);
बाह्य व्योम *स_हटाओ(व्योम *, स्थिर व्योम *, माप_प्रकार);
बाह्य व्योम *स_रखो(व्योम *, पूर्णांक, माप_प्रकार);
बाह्य पूर्णांक म_लिखो(स्थिर अक्षर *, ...);

/* If it's not defined, the export is included in lib/string.c.*/
#अगर_घोषित __HAVE_ARCH_STRSTR
EXPORT_SYMBOL(म_माला);
#पूर्ण_अगर

#अगर_अघोषित __x86_64__
बाह्य व्योम *स_नकल(व्योम *, स्थिर व्योम *, माप_प्रकार);
EXPORT_SYMBOL(स_नकल);
#पूर्ण_अगर

EXPORT_SYMBOL(स_हटाओ);
EXPORT_SYMBOL(स_रखो);
EXPORT_SYMBOL(म_लिखो);

/* Here, instead, I can provide a fake prototype. Yes, someone cares: genksyms.
 * However, the modules will use the CRC defined *here*, no matter अगर it is
 * good; so the versions of these symbols will always match
 */
#घोषणा EXPORT_SYMBOL_PROTO(sym)       \
	पूर्णांक sym(व्योम);                  \
	EXPORT_SYMBOL(sym);

बाह्य व्योम सूची_पढ़ो64(व्योम) __attribute__((weak));
EXPORT_SYMBOL(सूची_पढ़ो64);
बाह्य व्योम truncate64(व्योम) __attribute__((weak));
EXPORT_SYMBOL(truncate64);

#अगर_घोषित CONFIG_ARCH_REUSE_HOST_VSYSCALL_AREA
EXPORT_SYMBOL(vsyscall_ehdr);
EXPORT_SYMBOL(vsyscall_end);
#पूर्ण_अगर

EXPORT_SYMBOL_PROTO(__त्रुटि_सं_location);

EXPORT_SYMBOL_PROTO(access);
EXPORT_SYMBOL_PROTO(खोलो);
EXPORT_SYMBOL_PROTO(खोलो64);
EXPORT_SYMBOL_PROTO(बंद);
EXPORT_SYMBOL_PROTO(पढ़ो);
EXPORT_SYMBOL_PROTO(ग_लिखो);
EXPORT_SYMBOL_PROTO(dup2);
EXPORT_SYMBOL_PROTO(__xstat);
EXPORT_SYMBOL_PROTO(__lxstat);
EXPORT_SYMBOL_PROTO(__lxstat64);
EXPORT_SYMBOL_PROTO(__fxstat64);
EXPORT_SYMBOL_PROTO(lseek);
EXPORT_SYMBOL_PROTO(lseek64);
EXPORT_SYMBOL_PROTO(chown);
EXPORT_SYMBOL_PROTO(fchown);
EXPORT_SYMBOL_PROTO(truncate);
EXPORT_SYMBOL_PROTO(ftruncate64);
EXPORT_SYMBOL_PROTO(uसमय);
EXPORT_SYMBOL_PROTO(uबार);
EXPORT_SYMBOL_PROTO(fuबार);
EXPORT_SYMBOL_PROTO(chmod);
EXPORT_SYMBOL_PROTO(fchmod);
EXPORT_SYMBOL_PROTO(नाम);
EXPORT_SYMBOL_PROTO(__xmknod);

EXPORT_SYMBOL_PROTO(symlink);
EXPORT_SYMBOL_PROTO(link);
EXPORT_SYMBOL_PROTO(unlink);
EXPORT_SYMBOL_PROTO(पढ़ोlink);

EXPORT_SYMBOL_PROTO(सूची_गढ़ो);
EXPORT_SYMBOL_PROTO(सूची_हटाओ);
EXPORT_SYMBOL_PROTO(सूची_खोलो);
EXPORT_SYMBOL_PROTO(सूची_पढ़ो);
EXPORT_SYMBOL_PROTO(बंद_सूची);
EXPORT_SYMBOL_PROTO(seekdir);
EXPORT_SYMBOL_PROTO(telldir);

EXPORT_SYMBOL_PROTO(ioctl);

EXPORT_SYMBOL_PROTO(pपढ़ो64);
EXPORT_SYMBOL_PROTO(pग_लिखो64);

EXPORT_SYMBOL_PROTO(statfs);
EXPORT_SYMBOL_PROTO(statfs64);

EXPORT_SYMBOL_PROTO(getuid);

EXPORT_SYMBOL_PROTO(fsync);
EXPORT_SYMBOL_PROTO(fdatasync);

EXPORT_SYMBOL_PROTO(lstat64);
EXPORT_SYMBOL_PROTO(ख_स्थिति64);
EXPORT_SYMBOL_PROTO(mknod);

/* Export symbols used by GCC क्रम the stack protector. */
बाह्य व्योम __stack_smash_handler(व्योम *) __attribute__((weak));
EXPORT_SYMBOL(__stack_smash_handler);

बाह्य दीर्घ __guard __attribute__((weak));
EXPORT_SYMBOL(__guard);

#अगर_घोषित _FORTIFY_SOURCE
बाह्य पूर्णांक __प्र_लिखो_chk(अक्षर *str, पूर्णांक flag, माप_प्रकार म_माप, स्थिर अक्षर *क्रमmat);
EXPORT_SYMBOL(__प्र_लिखो_chk);
#पूर्ण_अगर
