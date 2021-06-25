<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NVDIMM_PMEM_H__
#घोषणा __NVDIMM_PMEM_H__
#समावेश <linux/page-flags.h>
#समावेश <linux/badblocks.h>
#समावेश <linux/types.h>
#समावेश <linux/pfn_t.h>
#समावेश <linux/fs.h>

/* this definition is in it's own header क्रम tools/testing/nvdimm to consume */
काष्ठा pmem_device अणु
	/* One contiguous memory region per device */
	phys_addr_t		phys_addr;
	/* when non-zero this device is hosting a 'pfn' instance */
	phys_addr_t		data_offset;
	u64			pfn_flags;
	व्योम			*virt_addr;
	/* immutable base size of the namespace */
	माप_प्रकार			size;
	/* trim size when namespace capacity has been section aligned */
	u32			pfn_pad;
	काष्ठा kernfs_node	*bb_state;
	काष्ठा badblocks	bb;
	काष्ठा dax_device	*dax_dev;
	काष्ठा gendisk		*disk;
	काष्ठा dev_pagemap	pgmap;
पूर्ण;

दीर्घ __pmem_direct_access(काष्ठा pmem_device *pmem, pgoff_t pgoff,
		दीर्घ nr_pages, व्योम **kaddr, pfn_t *pfn);

#अगर_घोषित CONFIG_MEMORY_FAILURE
अटल अंतरभूत bool test_and_clear_pmem_poison(काष्ठा page *page)
अणु
	वापस TestClearPageHWPoison(page);
पूर्ण
#अन्यथा
अटल अंतरभूत bool test_and_clear_pmem_poison(काष्ठा page *page)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* __NVDIMM_PMEM_H__ */
