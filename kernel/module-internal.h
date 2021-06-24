<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Module पूर्णांकernals
 *
 * Copyright (C) 2012 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/elf.h>
#समावेश <यंत्र/module.h>

काष्ठा load_info अणु
	स्थिर अक्षर *name;
	/* poपूर्णांकer to module in temporary copy, मुक्तd at end of load_module() */
	काष्ठा module *mod;
	Elf_Ehdr *hdr;
	अचिन्हित दीर्घ len;
	Elf_Shdr *sechdrs;
	अक्षर *secstrings, *strtab;
	अचिन्हित दीर्घ symoffs, stroffs, init_typeoffs, core_typeoffs;
	काष्ठा _ddebug *debug;
	अचिन्हित पूर्णांक num_debug;
	bool sig_ok;
#अगर_घोषित CONFIG_KALLSYMS
	अचिन्हित दीर्घ mod_kallsyms_init_off;
#पूर्ण_अगर
	काष्ठा अणु
		अचिन्हित पूर्णांक sym, str, mod, vers, info, pcpu;
	पूर्ण index;
पूर्ण;

बाह्य पूर्णांक mod_verअगरy_sig(स्थिर व्योम *mod, काष्ठा load_info *info);
