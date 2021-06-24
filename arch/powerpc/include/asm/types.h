<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * This file is never included by application software unless
 * explicitly requested (e.g., via linux/types.h) in which हाल the
 * application is Linux specअगरic so (user-) name space pollution is
 * not a major issue.  However, क्रम पूर्णांकeroperability, libraries still
 * need to be careful to aव्योम a name clashes.
 */
#अगर_अघोषित _ASM_POWERPC_TYPES_H
#घोषणा _ASM_POWERPC_TYPES_H

#समावेश <uapi/यंत्र/types.h>

#अगर_घोषित __घातerpc64__
#अगर defined(_CALL_ELF) && _CALL_ELF == 2
#घोषणा PPC64_ELF_ABI_v2
#अन्यथा
#घोषणा PPC64_ELF_ABI_v1
#पूर्ण_अगर
#पूर्ण_अगर /* __घातerpc64__ */

#अगर_अघोषित __ASSEMBLY__

प्रकार __vector128 vector128;

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ entry;
	अचिन्हित दीर्घ toc;
	अचिन्हित दीर्घ env;
पूर्ण func_descr_t;

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_POWERPC_TYPES_H */
