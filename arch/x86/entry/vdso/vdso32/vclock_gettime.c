<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा BUILD_VDSO32

#अगर_घोषित CONFIG_X86_64

/*
 * in हाल of a 32 bit VDSO क्रम a 64 bit kernel fake a 32 bit kernel
 * configuration
 */
#अघोषित CONFIG_64BIT
#अघोषित CONFIG_X86_64
#अघोषित CONFIG_COMPAT
#अघोषित CONFIG_PGTABLE_LEVELS
#अघोषित CONFIG_ILLEGAL_POINTER_VALUE
#अघोषित CONFIG_SPARSEMEM_VMEMMAP
#अघोषित CONFIG_NR_CPUS
#अघोषित CONFIG_PARAVIRT_XXL

#घोषणा CONFIG_X86_32 1
#घोषणा CONFIG_PGTABLE_LEVELS 2
#घोषणा CONFIG_PAGE_OFFSET 0
#घोषणा CONFIG_ILLEGAL_POINTER_VALUE 0
#घोषणा CONFIG_NR_CPUS 1

#घोषणा BUILD_VDSO32_64

#पूर्ण_अगर

#समावेश "../vclock_gettime.c"
