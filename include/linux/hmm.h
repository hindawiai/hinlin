<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2013 Red Hat Inc.
 *
 * Authors: Jथऊrथखme Glisse <jglisse@redhat.com>
 *
 * See Documentation/vm/hmm.rst क्रम reasons and overview of what HMM is.
 */
#अगर_अघोषित LINUX_HMM_H
#घोषणा LINUX_HMM_H

#समावेश <linux/kconfig.h>
#समावेश <linux/pgtable.h>

#समावेश <linux/device.h>
#समावेश <linux/migrate.h>
#समावेश <linux/memremap.h>
#समावेश <linux/completion.h>
#समावेश <linux/mmu_notअगरier.h>

/*
 * On output:
 * 0             - The page is faultable and a future call with 
 *                 HMM_PFN_REQ_FAULT could succeed.
 * HMM_PFN_VALID - the pfn field poपूर्णांकs to a valid PFN. This PFN is at
 *                 least पढ़ोable. If dev_निजी_owner is !शून्य then this could
 *                 poपूर्णांक at a DEVICE_PRIVATE page.
 * HMM_PFN_WRITE - अगर the page memory can be written to (requires HMM_PFN_VALID)
 * HMM_PFN_ERROR - accessing the pfn is impossible and the device should
 *                 fail. ie poisoned memory, special pages, no vma, etc
 *
 * On input:
 * 0                 - Return the current state of the page, करो not fault it.
 * HMM_PFN_REQ_FAULT - The output must have HMM_PFN_VALID or hmm_range_fault()
 *                     will fail
 * HMM_PFN_REQ_WRITE - The output must have HMM_PFN_WRITE or hmm_range_fault()
 *                     will fail. Must be combined with HMM_PFN_REQ_FAULT.
 */
क्रमागत hmm_pfn_flags अणु
	/* Output fields and flags */
	HMM_PFN_VALID = 1UL << (BITS_PER_LONG - 1),
	HMM_PFN_WRITE = 1UL << (BITS_PER_LONG - 2),
	HMM_PFN_ERROR = 1UL << (BITS_PER_LONG - 3),
	HMM_PFN_ORDER_SHIFT = (BITS_PER_LONG - 8),

	/* Input flags */
	HMM_PFN_REQ_FAULT = HMM_PFN_VALID,
	HMM_PFN_REQ_WRITE = HMM_PFN_WRITE,

	HMM_PFN_FLAGS = 0xFFUL << HMM_PFN_ORDER_SHIFT,
पूर्ण;

/*
 * hmm_pfn_to_page() - वापस काष्ठा page poपूर्णांकed to by a device entry
 *
 * This must be called under the caller 'user_lock' after a successful
 * mmu_पूर्णांकerval_पढ़ो_begin(). The caller must have tested क्रम HMM_PFN_VALID
 * alपढ़ोy.
 */
अटल अंतरभूत काष्ठा page *hmm_pfn_to_page(अचिन्हित दीर्घ hmm_pfn)
अणु
	वापस pfn_to_page(hmm_pfn & ~HMM_PFN_FLAGS);
पूर्ण

/*
 * hmm_pfn_to_map_order() - वापस the CPU mapping size order
 *
 * This is optionally useful to optimize processing of the pfn result
 * array. It indicates that the page starts at the order aligned VA and is
 * 1<<order bytes दीर्घ.  Every pfn within an high order page will have the
 * same pfn flags, both access protections and the map_order.  The caller must
 * be careful with edge हालs as the start and end VA of the given page may
 * extend past the range used with hmm_range_fault().
 *
 * This must be called under the caller 'user_lock' after a successful
 * mmu_पूर्णांकerval_पढ़ो_begin(). The caller must have tested क्रम HMM_PFN_VALID
 * alपढ़ोy.
 */
अटल अंतरभूत अचिन्हित पूर्णांक hmm_pfn_to_map_order(अचिन्हित दीर्घ hmm_pfn)
अणु
	वापस (hmm_pfn >> HMM_PFN_ORDER_SHIFT) & 0x1F;
पूर्ण

/*
 * काष्ठा hmm_range - track invalidation lock on भव address range
 *
 * @notअगरier: a mmu_पूर्णांकerval_notअगरier that includes the start/end
 * @notअगरier_seq: result of mmu_पूर्णांकerval_पढ़ो_begin()
 * @start: range भव start address (inclusive)
 * @end: range भव end address (exclusive)
 * @hmm_pfns: array of pfns (big enough क्रम the range)
 * @शेष_flags: शेष flags क्रम the range (ग_लिखो, पढ़ो, ... see hmm करोc)
 * @pfn_flags_mask: allows to mask pfn flags so that only शेष_flags matter
 * @dev_निजी_owner: owner of device निजी pages
 */
काष्ठा hmm_range अणु
	काष्ठा mmu_पूर्णांकerval_notअगरier *notअगरier;
	अचिन्हित दीर्घ		notअगरier_seq;
	अचिन्हित दीर्घ		start;
	अचिन्हित दीर्घ		end;
	अचिन्हित दीर्घ		*hmm_pfns;
	अचिन्हित दीर्घ		शेष_flags;
	अचिन्हित दीर्घ		pfn_flags_mask;
	व्योम			*dev_निजी_owner;
पूर्ण;

/*
 * Please see Documentation/vm/hmm.rst क्रम how to use the range API.
 */
पूर्णांक hmm_range_fault(काष्ठा hmm_range *range);

/*
 * HMM_RANGE_DEFAULT_TIMEOUT - शेष समयout (ms) when रुकोing क्रम a range
 *
 * When रुकोing क्रम mmu notअगरiers we need some kind of समय out otherwise we
 * could potentialy रुको क्रम ever, 1000ms ie 1s sounds like a दीर्घ समय to
 * रुको alपढ़ोy.
 */
#घोषणा HMM_RANGE_DEFAULT_TIMEOUT 1000

#पूर्ण_अगर /* LINUX_HMM_H */
