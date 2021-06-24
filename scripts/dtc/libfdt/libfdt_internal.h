<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-or-later OR BSD-2-Clause) */
#अगर_अघोषित LIBFDT_INTERNAL_H
#घोषणा LIBFDT_INTERNAL_H
/*
 * libfdt - Flat Device Tree manipulation
 * Copyright (C) 2006 David Gibson, IBM Corporation.
 */
#समावेश <fdt.h>

#घोषणा FDT_ALIGN(x, a)		(((x) + (a) - 1) & ~((a) - 1))
#घोषणा FDT_TAGALIGN(x)		(FDT_ALIGN((x), FDT_TAGSIZE))

पूर्णांक32_t fdt_ro_probe_(स्थिर व्योम *fdt);
#घोषणा FDT_RO_PROBE(fdt)					\
	अणु							\
		पूर्णांक32_t totalsize_;				\
		अगर ((totalsize_ = fdt_ro_probe_(fdt)) < 0)	\
			वापस totalsize_;			\
	पूर्ण

पूर्णांक fdt_check_node_offset_(स्थिर व्योम *fdt, पूर्णांक offset);
पूर्णांक fdt_check_prop_offset_(स्थिर व्योम *fdt, पूर्णांक offset);
स्थिर अक्षर *fdt_find_string_(स्थिर अक्षर *strtab, पूर्णांक tअसलize, स्थिर अक्षर *s);
पूर्णांक fdt_node_end_offset_(व्योम *fdt, पूर्णांक nodeoffset);

अटल अंतरभूत स्थिर व्योम *fdt_offset_ptr_(स्थिर व्योम *fdt, पूर्णांक offset)
अणु
	वापस (स्थिर अक्षर *)fdt + fdt_off_dt_काष्ठा(fdt) + offset;
पूर्ण

अटल अंतरभूत व्योम *fdt_offset_ptr_w_(व्योम *fdt, पूर्णांक offset)
अणु
	वापस (व्योम *)(uपूर्णांकptr_t)fdt_offset_ptr_(fdt, offset);
पूर्ण

अटल अंतरभूत स्थिर काष्ठा fdt_reserve_entry *fdt_mem_rsv_(स्थिर व्योम *fdt, पूर्णांक n)
अणु
	स्थिर काष्ठा fdt_reserve_entry *rsv_table =
		(स्थिर काष्ठा fdt_reserve_entry *)
		((स्थिर अक्षर *)fdt + fdt_off_mem_rsvmap(fdt));

	वापस rsv_table + n;
पूर्ण
अटल अंतरभूत काष्ठा fdt_reserve_entry *fdt_mem_rsv_w_(व्योम *fdt, पूर्णांक n)
अणु
	वापस (व्योम *)(uपूर्णांकptr_t)fdt_mem_rsv_(fdt, n);
पूर्ण

/*
 * Internal helpers to access tructural elements of the device tree
 * blob (rather than क्रम exaple पढ़ोing पूर्णांकegers from within property
 * values).  We assume that we are either given a naturally aligned
 * address क्रम the platक्रमm or अगर we are not, we are on a platक्रमm
 * where unaligned memory पढ़ोs will be handled in a graceful manner.
 * If not the बाह्यal helpers fdtXX_ld() from libfdt.h can be used
 * instead.
 */
अटल अंतरभूत uपूर्णांक32_t fdt32_ld_(स्थिर fdt32_t *p)
अणु
	वापस fdt32_to_cpu(*p);
पूर्ण

अटल अंतरभूत uपूर्णांक64_t fdt64_ld_(स्थिर fdt64_t *p)
अणु
	वापस fdt64_to_cpu(*p);
पूर्ण

#घोषणा FDT_SW_MAGIC		(~FDT_MAGIC)

/**********************************************************************/
/* Checking controls                                                  */
/**********************************************************************/

#अगर_अघोषित FDT_ASSUME_MASK
#घोषणा FDT_ASSUME_MASK 0
#पूर्ण_अगर

/*
 * Defines assumptions which can be enabled. Each of these can be enabled
 * inभागidually. For maximum safety, करोn't enable any assumptions!
 *
 * For minimal code size and no safety, use ASSUME_PERFECT at your own risk.
 * You should have another method of validating the device tree, such as a
 * signature or hash check beक्रमe using libfdt.
 *
 * For situations where security is not a concern it may be safe to enable
 * ASSUME_SANE.
 */
क्रमागत अणु
	/*
	 * This करोes essentially no checks. Only the latest device-tree
	 * version is correctly handled. Inconsistencies or errors in the device
	 * tree may cause undefined behaviour or crashes. Invalid parameters
	 * passed to libfdt may करो the same.
	 *
	 * If an error occurs when modअगरying the tree it may leave the tree in
	 * an पूर्णांकermediate (but valid) state. As an example, adding a property
	 * where there is insufficient space may result in the property name
	 * being added to the string table even though the property itself is
	 * not added to the काष्ठा section.
	 *
	 * Only use this अगर you have a fully validated device tree with
	 * the latest supported version and wish to minimise code size.
	 */
	ASSUME_PERFECT		= 0xff,

	/*
	 * This assumes that the device tree is sane. i.e. header metadata
	 * and basic hierarchy are correct.
	 *
	 * With this assumption enabled, normal device trees produced by libfdt
	 * and the compiler should be handled safely. Malicious device trees and
	 * complete garbage may cause libfdt to behave badly or crash. Truncated
	 * device trees (e.g. those only partially loaded) can also cause
	 * problems.
	 *
	 * Note: Only checks that relate exclusively to the device tree itself
	 * (not the parameters passed to libfdt) are disabled by this
	 * assumption. This includes checking headers, tags and the like.
	 */
	ASSUME_VALID_DTB	= 1 << 0,

	/*
	 * This builds on ASSUME_VALID_DTB and further assumes that libfdt
	 * functions are called with valid parameters, i.e. not trigger
	 * FDT_ERR_BADOFFSET or offsets that are out of bounds. It disables any
	 * extensive checking of parameters and the device tree, making various
	 * assumptions about correctness.
	 *
	 * It करोesn't make sense to enable this assumption unless
	 * ASSUME_VALID_DTB is also enabled.
	 */
	ASSUME_VALID_INPUT	= 1 << 1,

	/*
	 * This disables checks क्रम device-tree version and हटाओs all code
	 * which handles older versions.
	 *
	 * Only enable this अगर you know you have a device tree with the latest
	 * version.
	 */
	ASSUME_LATEST		= 1 << 2,

	/*
	 * This assumes that it is OK क्रम a failed addition to the device tree,
	 * due to lack of space or some other problem, to skip any rollback
	 * steps (such as dropping the property name from the string table).
	 * This is safe to enable in most circumstances, even though it may
	 * leave the tree in a sub-optimal state.
	 */
	ASSUME_NO_ROLLBACK	= 1 << 3,

	/*
	 * This assumes that the device tree components appear in a 'convenient'
	 * order, i.e. the memory reservation block first, then the काष्ठाure
	 * block and finally the string block.
	 *
	 * This order is not specअगरied by the device-tree specअगरication,
	 * but is expected by libfdt. The device-tree compiler always created
	 * device trees with this order.
	 *
	 * This assumption disables a check in fdt_खोलो_पूर्णांकo() and हटाओs the
	 * ability to fix the problem there. This is safe अगर you know that the
	 * device tree is correctly ordered. See fdt_blocks_misordered_().
	 */
	ASSUME_LIBFDT_ORDER	= 1 << 4,

	/*
	 * This assumes that libfdt itself करोes not have any पूर्णांकernal bugs. It
	 * drops certain checks that should never be needed unless libfdt has an
	 * undiscovered bug.
	 *
	 * This can generally be considered safe to enable.
	 */
	ASSUME_LIBFDT_FLAWLESS	= 1 << 5,
पूर्ण;

/**
 * can_assume_() - check अगर a particular assumption is enabled
 *
 * @mask: Mask to check (ASSUME_...)
 * @वापस true अगर that assumption is enabled, अन्यथा false
 */
अटल अंतरभूत bool can_assume_(पूर्णांक mask)
अणु
	वापस FDT_ASSUME_MASK & mask;
पूर्ण

/** helper macros क्रम checking assumptions */
#घोषणा can_assume(_assume)	can_assume_(ASSUME_ ## _assume)

#पूर्ण_अगर /* LIBFDT_INTERNAL_H */
