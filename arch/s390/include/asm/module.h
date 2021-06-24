<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_S390_MODULE_H
#घोषणा _ASM_S390_MODULE_H

#समावेश <यंत्र-generic/module.h>

/*
 * This file contains the s390 architecture specअगरic module code.
 */

काष्ठा mod_arch_syminfo
अणु
	अचिन्हित दीर्घ got_offset;
	अचिन्हित दीर्घ plt_offset;
	पूर्णांक got_initialized;
	पूर्णांक plt_initialized;
पूर्ण;

काष्ठा mod_arch_specअगरic
अणु
	/* Starting offset of got in the module core memory. */
	अचिन्हित दीर्घ got_offset;
	/* Starting offset of plt in the module core memory. */
	अचिन्हित दीर्घ plt_offset;
	/* Size of the got. */
	अचिन्हित दीर्घ got_size;
	/* Size of the plt. */
	अचिन्हित दीर्घ plt_size;
	/* Number of symbols in syminfo. */
	पूर्णांक nsyms;
	/* Additional symbol inक्रमmation (got and plt offsets). */
	काष्ठा mod_arch_syminfo *syminfo;
पूर्ण;

#पूर्ण_अगर /* _ASM_S390_MODULE_H */
