<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_IOMMU_TABLE_H
#घोषणा _ASM_X86_IOMMU_TABLE_H

#समावेश <यंत्र/swiotlb.h>

/*
 * History lesson:
 * The execution chain of IOMMUs in 2.6.36 looks as so:
 *
 *            [xen-swiotlb]
 *                 |
 *         +----[swiotlb *]--+
 *        /         |         \
 *       /          |          \
 *    [GART]     [Calgary]  [Intel VT-d]
 *     /
 *    /
 * [AMD-Vi]
 *
 * *: अगर SWIOTLB detected 'iommu=soft'/'swiotlb=force' it would skip
 * over the rest of IOMMUs and unconditionally initialize the SWIOTLB.
 * Also it would surreptitiously initialize set the swiotlb=1 अगर there were
 * more than 4GB and अगर the user did not pass in 'iommu=off'. The swiotlb
 * flag would be turned off by all IOMMUs except the Calgary one.
 *
 * The IOMMU_INIT* macros allow a similar tree (or more complex अगर desired)
 * to be built by defining who we depend on.
 *
 * And all that needs to be करोne is to use one of the macros in the IOMMU
 * and the pci-dma.c will take care of the rest.
 */

काष्ठा iommu_table_entry अणु
	initcall_t	detect;
	initcall_t	depend;
	व्योम		(*early_init)(व्योम); /* No memory allocate available. */
	व्योम		(*late_init)(व्योम); /* Yes, can allocate memory. */
#घोषणा IOMMU_FINISH_IF_DETECTED (1<<0)
#घोषणा IOMMU_DETECTED		 (1<<1)
	पूर्णांक		flags;
पूर्ण;
/*
 * Macro fills out an entry in the .iommu_table that is equivalent
 * to the fields that 'struct iommu_table_entry' has. The entries
 * that are put in the .iommu_table section are not put in any order
 * hence during boot-समय we will have to resort them based on
 * dependency. */


#घोषणा __IOMMU_INIT(_detect, _depend, _early_init, _late_init, _finish)\
	अटल स्थिर काष्ठा iommu_table_entry				\
		__iommu_entry_##_detect __used				\
	__attribute__ ((unused, __section__(".iommu_table"),		\
			aligned((माप(व्योम *)))))	\
	= अणु_detect, _depend, _early_init, _late_init,			\
	   _finish ? IOMMU_FINISH_IF_DETECTED : 0पूर्ण
/*
 * The simplest IOMMU definition. Provide the detection routine
 * and it will be run after the SWIOTLB and the other IOMMUs
 * that utilize this macro. If the IOMMU is detected (ie, the
 * detect routine वापसs a positive value), the other IOMMUs
 * are also checked. You can use IOMMU_INIT_POST_FINISH अगर you prefer
 * to stop detecting the other IOMMUs after yours has been detected.
 */
#घोषणा IOMMU_INIT_POST(_detect)					\
	__IOMMU_INIT(_detect, pci_swiotlb_detect_4gb,  शून्य, शून्य, 0)

#घोषणा IOMMU_INIT_POST_FINISH(detect)					\
	__IOMMU_INIT(_detect, pci_swiotlb_detect_4gb,  शून्य, शून्य, 1)

/*
 * A more sophisticated version of IOMMU_INIT. This variant requires:
 *  a). A detection routine function.
 *  b). The name of the detection routine we depend on to get called
 *      beक्रमe us.
 *  c). The init routine which माला_लो called अगर the detection routine
 *      वापसs a positive value from the pci_iommu_alloc. This means
 *      no presence of a memory allocator.
 *  d). Similar to the 'init', except that this माला_लो called from pci_iommu_init
 *      where we करो have a memory allocator.
 *
 * The standard IOMMU_INIT dअगरfers from the IOMMU_INIT_FINISH variant
 * in that the क्रमmer will जारी detecting other IOMMUs in the call
 * list after the detection routine वापसs a positive number, जबतक the
 * latter will stop the execution chain upon first successful detection.
 * Both variants will still call the 'init' and 'late_init' functions अगर
 * they are set.
 */
#घोषणा IOMMU_INIT_FINISH(_detect, _depend, _init, _late_init)		\
	__IOMMU_INIT(_detect, _depend, _init, _late_init, 1)

#घोषणा IOMMU_INIT(_detect, _depend, _init, _late_init)			\
	__IOMMU_INIT(_detect, _depend, _init, _late_init, 0)

व्योम sort_iommu_table(काष्ठा iommu_table_entry *start,
		      काष्ठा iommu_table_entry *finish);

व्योम check_iommu_entries(काष्ठा iommu_table_entry *start,
			 काष्ठा iommu_table_entry *finish);

#पूर्ण_अगर /* _ASM_X86_IOMMU_TABLE_H */
