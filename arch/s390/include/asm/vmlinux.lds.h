<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <यंत्र/page.h>

/*
 * .boot.data section is shared between the decompressor code and the
 * decompressed kernel. The decompressor will store values in it, and copy
 * over to the decompressed image beक्रमe starting it.
 *
 * .boot.data variables are kept in separate .boot.data.<var name> sections,
 * which are sorted by alignment first, then by name beक्रमe being merged
 * पूर्णांकo single .boot.data section. This way big holes हालd by page aligned
 * काष्ठाs are aव्योमed and linker produces consistent result.
 */
#घोषणा BOOT_DATA							\
	. = ALIGN(PAGE_SIZE);						\
	.boot.data : अणु							\
		__boot_data_start = .;					\
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.boot.data*)))		\
		__boot_data_end = .;					\
	पूर्ण

/*
 * .boot.preserved.data is similar to .boot.data, but it is not part of the
 * .init section and thus will be preserved क्रम later use in the decompressed
 * kernel.
 */
#घोषणा BOOT_DATA_PRESERVED						\
	. = ALIGN(PAGE_SIZE);						\
	.boot.preserved.data : अणु					\
		__boot_data_preserved_start = .;			\
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.boot.preserved.data*))) \
		__boot_data_preserved_end = .;				\
	पूर्ण
