<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_PFN_H_
#घोषणा _LINUX_PFN_H_

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/types.h>

/*
 * pfn_t: encapsulates a page-frame number that is optionally backed
 * by memmap (काष्ठा page).  Whether a pfn_t has a 'struct page'
 * backing is indicated by flags in the high bits of the value.
 */
प्रकार काष्ठा अणु
	u64 val;
पूर्ण pfn_t;
#पूर्ण_अगर

#घोषणा PFN_ALIGN(x)	(((अचिन्हित दीर्घ)(x) + (PAGE_SIZE - 1)) & PAGE_MASK)
#घोषणा PFN_UP(x)	(((x) + PAGE_SIZE-1) >> PAGE_SHIFT)
#घोषणा PFN_DOWN(x)	((x) >> PAGE_SHIFT)
#घोषणा PFN_PHYS(x)	((phys_addr_t)(x) << PAGE_SHIFT)
#घोषणा PHYS_PFN(x)	((अचिन्हित दीर्घ)((x) >> PAGE_SHIFT))

#पूर्ण_अगर
