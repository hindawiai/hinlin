<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_POISON_H
#घोषणा _LINUX_POISON_H

/********** include/linux/list.h **********/

/*
 * Architectures might want to move the poison poपूर्णांकer offset
 * पूर्णांकo some well-recognized area such as 0xdead000000000000,
 * that is also not mappable by user-space exploits:
 */
#अगर_घोषित CONFIG_ILLEGAL_POINTER_VALUE
# define POISON_POINTER_DELTA _AC(CONFIG_ILLEGAL_POINTER_VALUE, UL)
#अन्यथा
# define POISON_POINTER_DELTA 0
#पूर्ण_अगर

/*
 * These are non-शून्य poपूर्णांकers that will result in page faults
 * under normal circumstances, used to verअगरy that nobody uses
 * non-initialized list entries.
 */
#घोषणा LIST_POISON1  ((व्योम *) 0x100 + POISON_POINTER_DELTA)
#घोषणा LIST_POISON2  ((व्योम *) 0x122 + POISON_POINTER_DELTA)

/********** include/linux/समयr.h **********/
#घोषणा TIMER_ENTRY_STATIC	((व्योम *) 0x300 + POISON_POINTER_DELTA)

/********** mm/page_poison.c **********/
#घोषणा PAGE_POISON 0xaa

/********** mm/page_alloc.c ************/

#घोषणा TAIL_MAPPING	((व्योम *) 0x400 + POISON_POINTER_DELTA)

/********** mm/slab.c **********/
/*
 * Magic nums क्रम obj red zoning.
 * Placed in the first word beक्रमe and the first word after an obj.
 */
#घोषणा	RED_INACTIVE	0x09F911029D74E35BULL	/* when obj is inactive */
#घोषणा	RED_ACTIVE	0xD84156C5635688C0ULL	/* when obj is active */

#घोषणा SLUB_RED_INACTIVE	0xbb
#घोषणा SLUB_RED_ACTIVE		0xcc

/* ...and क्रम poisoning */
#घोषणा	POISON_INUSE	0x5a	/* क्रम use-uninitialised poisoning */
#घोषणा POISON_FREE	0x6b	/* क्रम use-after-मुक्त poisoning */
#घोषणा	POISON_END	0xa5	/* end-byte of poisoning */

/********** arch/$ARCH/mm/init.c **********/
#घोषणा POISON_FREE_INITMEM	0xcc

/********** arch/ia64/hp/common/sba_iommu.c **********/
/*
 * arch/ia64/hp/common/sba_iommu.c uses a 16-byte poison string with a
 * value of "SBAIOMMU POISON\0" क्रम spill-over poisoning.
 */

/********** fs/jbd/journal.c **********/
#घोषणा JBD_POISON_FREE		0x5b
#घोषणा JBD2_POISON_FREE	0x5c

/********** drivers/base/dmapool.c **********/
#घोषणा	POOL_POISON_FREED	0xa7	/* !inuse */
#घोषणा	POOL_POISON_ALLOCATED	0xa9	/* !initted */

/********** drivers/aपंचांग/ **********/
#घोषणा ATM_POISON_FREE		0x12
#घोषणा ATM_POISON		0xdeadbeef

/********** kernel/mutexes **********/
#घोषणा MUTEX_DEBUG_INIT	0x11
#घोषणा MUTEX_DEBUG_FREE	0x22
#घोषणा MUTEX_POISON_WW_CTX	((व्योम *) 0x500 + POISON_POINTER_DELTA)

/********** security/ **********/
#घोषणा KEY_DESTROY		0xbd

#पूर्ण_अगर
