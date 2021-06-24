<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_PARISC_MODULE_H
#घोषणा _ASM_PARISC_MODULE_H

#समावेश <यंत्र-generic/module.h>

/*
 * This file contains the parisc architecture specअगरic module code.
 */

काष्ठा unwind_table;

काष्ठा mod_arch_specअगरic
अणु
	अचिन्हित दीर्घ got_offset, got_count, got_max;
	अचिन्हित दीर्घ fdesc_offset, fdesc_count, fdesc_max;
	काष्ठा अणु
		अचिन्हित दीर्घ stub_offset;
		अचिन्हित पूर्णांक stub_entries;
		पूर्ण *section;
	पूर्णांक unwind_section;
	काष्ठा unwind_table *unwind;
पूर्ण;

#पूर्ण_अगर /* _ASM_PARISC_MODULE_H */
