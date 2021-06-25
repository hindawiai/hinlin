<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_SYMSRC_
#घोषणा __PERF_SYMSRC_ 1

#समावेश <stdbool.h>
#समावेश <मानकघोष.स>
#समावेश "dso.h"

#अगर_घोषित HAVE_LIBELF_SUPPORT
#समावेश <libelf.h>
#समावेश <gelf.h>
#पूर्ण_अगर
#समावेश <elf.h>

काष्ठा symsrc अणु
	अक्षर		     *name;
	पूर्णांक		     fd;
	क्रमागत dso_binary_type type;

#अगर_घोषित HAVE_LIBELF_SUPPORT
	Elf		     *elf;
	GElf_Ehdr	     ehdr;

	Elf_Scn		     *opdsec;
	माप_प्रकार		     opdidx;
	GElf_Shdr	     opdshdr;

	Elf_Scn		     *symtab;
	GElf_Shdr	     symshdr;

	Elf_Scn		     *dynsym;
	माप_प्रकार		     dynsym_idx;
	GElf_Shdr	     dynshdr;

	bool		     adjust_symbols;
	bool		     is_64_bit;
#पूर्ण_अगर
पूर्ण;

पूर्णांक symsrc__init(काष्ठा symsrc *ss, काष्ठा dso *dso, स्थिर अक्षर *name, क्रमागत dso_binary_type type);
व्योम symsrc__destroy(काष्ठा symsrc *ss);

bool symsrc__has_symtab(काष्ठा symsrc *ss);
bool symsrc__possibly_runसमय(काष्ठा symsrc *ss);

#पूर्ण_अगर /* __PERF_SYMSRC_ */
