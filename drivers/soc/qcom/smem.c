<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, Sony Mobile Communications AB.
 * Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/hwspinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/soc/qcom/sस्मृति.स>

/*
 * The Qualcomm shared memory प्रणाली is a allocate only heap काष्ठाure that
 * consists of one of more memory areas that can be accessed by the processors
 * in the SoC.
 *
 * All प्रणालीs contains a global heap, accessible by all processors in the SoC,
 * with a table of contents data काष्ठाure (@smem_header) at the beginning of
 * the मुख्य shared memory block.
 *
 * The global header contains meta data क्रम allocations as well as a fixed list
 * of 512 entries (@smem_global_entry) that can be initialized to reference
 * parts of the shared memory space.
 *
 *
 * In addition to this global heap a set of "private" heaps can be set up at
 * boot समय with access restrictions so that only certain processor pairs can
 * access the data.
 *
 * These partitions are referenced from an optional partition table
 * (@smem_ptable), that is found 4kB from the end of the मुख्य smem region. The
 * partition table entries (@smem_ptable_entry) lists the involved processors
 * (or hosts) and their location in the मुख्य shared memory region.
 *
 * Each partition starts with a header (@smem_partition_header) that identअगरies
 * the partition and holds properties क्रम the two पूर्णांकernal memory regions. The
 * two regions are cached and non-cached memory respectively. Each region
 * contain a link list of allocation headers (@smem_निजी_entry) followed by
 * their data.
 *
 * Items in the non-cached region are allocated from the start of the partition
 * जबतक items in the cached region are allocated from the end. The मुक्त area
 * is hence the region between the cached and non-cached offsets. The header of
 * cached items comes after the data.
 *
 * Version 12 (SMEM_GLOBAL_PART_VERSION) changes the item alloc/get procedure
 * क्रम the global heap. A new global partition is created from the global heap
 * region with partition type (SMEM_GLOBAL_HOST) and the max smem item count is
 * set by the bootloader.
 *
 * To synchronize allocations in the shared memory heaps a remote spinlock must
 * be held - currently lock number 3 of the sfpb or tcsr is used क्रम this on all
 * platक्रमms.
 *
 */

/*
 * The version member of the smem header contains an array of versions क्रम the
 * various software components in the SoC. We verअगरy that the boot loader
 * version is a valid version as a sanity check.
 */
#घोषणा SMEM_MASTER_SBL_VERSION_INDEX	7
#घोषणा SMEM_GLOBAL_HEAP_VERSION	11
#घोषणा SMEM_GLOBAL_PART_VERSION	12

/*
 * The first 8 items are only to be allocated by the boot loader जबतक
 * initializing the heap.
 */
#घोषणा SMEM_ITEM_LAST_FIXED	8

/* Highest accepted item number, क्रम both global and निजी heaps */
#घोषणा SMEM_ITEM_COUNT		512

/* Processor/host identअगरier क्रम the application processor */
#घोषणा SMEM_HOST_APPS		0

/* Processor/host identअगरier क्रम the global partition */
#घोषणा SMEM_GLOBAL_HOST	0xfffe

/* Max number of processors/hosts in a प्रणाली */
#घोषणा SMEM_HOST_COUNT		14

/**
  * काष्ठा smem_proc_comm - proc_comm communication काष्ठा (legacy)
  * @command:	current command to be executed
  * @status:	status of the currently requested command
  * @params:	parameters to the command
  */
काष्ठा smem_proc_comm अणु
	__le32 command;
	__le32 status;
	__le32 params[2];
पूर्ण;

/**
 * काष्ठा smem_global_entry - entry to reference smem items on the heap
 * @allocated:	boolean to indicate अगर this entry is used
 * @offset:	offset to the allocated space
 * @size:	size of the allocated space, 8 byte aligned
 * @aux_base:	base address क्रम the memory region used by this unit, or 0 क्रम
 *		the शेष region. bits 0,1 are reserved
 */
काष्ठा smem_global_entry अणु
	__le32 allocated;
	__le32 offset;
	__le32 size;
	__le32 aux_base; /* bits 1:0 reserved */
पूर्ण;
#घोषणा AUX_BASE_MASK		0xfffffffc

/**
 * काष्ठा smem_header - header found in beginning of primary smem region
 * @proc_comm:		proc_comm communication पूर्णांकerface (legacy)
 * @version:		array of versions क्रम the various subप्रणालीs
 * @initialized:	boolean to indicate that smem is initialized
 * @मुक्त_offset:	index of the first unallocated byte in smem
 * @available:		number of bytes available क्रम allocation
 * @reserved:		reserved field, must be 0
 * @toc:		array of references to items
 */
काष्ठा smem_header अणु
	काष्ठा smem_proc_comm proc_comm[4];
	__le32 version[32];
	__le32 initialized;
	__le32 मुक्त_offset;
	__le32 available;
	__le32 reserved;
	काष्ठा smem_global_entry toc[SMEM_ITEM_COUNT];
पूर्ण;

/**
 * काष्ठा smem_ptable_entry - one entry in the @smem_ptable list
 * @offset:	offset, within the मुख्य shared memory region, of the partition
 * @size:	size of the partition
 * @flags:	flags क्रम the partition (currently unused)
 * @host0:	first processor/host with access to this partition
 * @host1:	second processor/host with access to this partition
 * @cacheline:	alignment क्रम "cached" entries
 * @reserved:	reserved entries क्रम later use
 */
काष्ठा smem_ptable_entry अणु
	__le32 offset;
	__le32 size;
	__le32 flags;
	__le16 host0;
	__le16 host1;
	__le32 cacheline;
	__le32 reserved[7];
पूर्ण;

/**
 * काष्ठा smem_ptable - partition table क्रम the निजी partitions
 * @magic:	magic number, must be SMEM_PTABLE_MAGIC
 * @version:	version of the partition table
 * @num_entries: number of partitions in the table
 * @reserved:	क्रम now reserved entries
 * @entry:	list of @smem_ptable_entry क्रम the @num_entries partitions
 */
काष्ठा smem_ptable अणु
	u8 magic[4];
	__le32 version;
	__le32 num_entries;
	__le32 reserved[5];
	काष्ठा smem_ptable_entry entry[];
पूर्ण;

अटल स्थिर u8 SMEM_PTABLE_MAGIC[] = अणु 0x24, 0x54, 0x4f, 0x43 पूर्ण; /* "$TOC" */

/**
 * काष्ठा smem_partition_header - header of the partitions
 * @magic:	magic number, must be SMEM_PART_MAGIC
 * @host0:	first processor/host with access to this partition
 * @host1:	second processor/host with access to this partition
 * @size:	size of the partition
 * @offset_मुक्त_uncached: offset to the first मुक्त byte of uncached memory in
 *		this partition
 * @offset_मुक्त_cached: offset to the first मुक्त byte of cached memory in this
 *		partition
 * @reserved:	क्रम now reserved entries
 */
काष्ठा smem_partition_header अणु
	u8 magic[4];
	__le16 host0;
	__le16 host1;
	__le32 size;
	__le32 offset_मुक्त_uncached;
	__le32 offset_मुक्त_cached;
	__le32 reserved[3];
पूर्ण;

अटल स्थिर u8 SMEM_PART_MAGIC[] = अणु 0x24, 0x50, 0x52, 0x54 पूर्ण;

/**
 * काष्ठा smem_निजी_entry - header of each item in the निजी partition
 * @canary:	magic number, must be SMEM_PRIVATE_CANARY
 * @item:	identअगरying number of the smem item
 * @size:	size of the data, including padding bytes
 * @padding_data: number of bytes of padding of data
 * @padding_hdr: number of bytes of padding between the header and the data
 * @reserved:	क्रम now reserved entry
 */
काष्ठा smem_निजी_entry अणु
	u16 canary; /* bytes are the same so no swapping needed */
	__le16 item;
	__le32 size; /* includes padding bytes */
	__le16 padding_data;
	__le16 padding_hdr;
	__le32 reserved;
पूर्ण;
#घोषणा SMEM_PRIVATE_CANARY	0xa5a5

/**
 * काष्ठा smem_info - smem region info located after the table of contents
 * @magic:	magic number, must be SMEM_INFO_MAGIC
 * @size:	size of the smem region
 * @base_addr:	base address of the smem region
 * @reserved:	क्रम now reserved entry
 * @num_items:	highest accepted item number
 */
काष्ठा smem_info अणु
	u8 magic[4];
	__le32 size;
	__le32 base_addr;
	__le32 reserved;
	__le16 num_items;
पूर्ण;

अटल स्थिर u8 SMEM_INFO_MAGIC[] = अणु 0x53, 0x49, 0x49, 0x49 पूर्ण; /* SIII */

/**
 * काष्ठा smem_region - representation of a chunk of memory used क्रम smem
 * @aux_base:	identअगरier of aux_mem base
 * @virt_base:	भव base address of memory with this aux_mem identअगरier
 * @size:	size of the memory region
 */
काष्ठा smem_region अणु
	u32 aux_base;
	व्योम __iomem *virt_base;
	माप_प्रकार size;
पूर्ण;

/**
 * काष्ठा qcom_smem - device data क्रम the smem device
 * @dev:	device poपूर्णांकer
 * @hwlock:	reference to a hwspinlock
 * @global_partition:	poपूर्णांकer to global partition when in use
 * @global_cacheline:	cacheline size क्रम global partition
 * @partitions:	list of poपूर्णांकers to partitions affecting the current
 *		processor/host
 * @cacheline:	list of cacheline sizes क्रम each host
 * @item_count: max accepted item number
 * @socinfo:	platक्रमm device poपूर्णांकer
 * @num_regions: number of @regions
 * @regions:	list of the memory regions defining the shared memory
 */
काष्ठा qcom_smem अणु
	काष्ठा device *dev;

	काष्ठा hwspinlock *hwlock;

	काष्ठा smem_partition_header *global_partition;
	माप_प्रकार global_cacheline;
	काष्ठा smem_partition_header *partitions[SMEM_HOST_COUNT];
	माप_प्रकार cacheline[SMEM_HOST_COUNT];
	u32 item_count;
	काष्ठा platक्रमm_device *socinfo;

	अचिन्हित num_regions;
	काष्ठा smem_region regions[];
पूर्ण;

अटल व्योम *
phdr_to_last_uncached_entry(काष्ठा smem_partition_header *phdr)
अणु
	व्योम *p = phdr;

	वापस p + le32_to_cpu(phdr->offset_मुक्त_uncached);
पूर्ण

अटल काष्ठा smem_निजी_entry *
phdr_to_first_cached_entry(काष्ठा smem_partition_header *phdr,
					माप_प्रकार cacheline)
अणु
	व्योम *p = phdr;
	काष्ठा smem_निजी_entry *e;

	वापस p + le32_to_cpu(phdr->size) - ALIGN(माप(*e), cacheline);
पूर्ण

अटल व्योम *
phdr_to_last_cached_entry(काष्ठा smem_partition_header *phdr)
अणु
	व्योम *p = phdr;

	वापस p + le32_to_cpu(phdr->offset_मुक्त_cached);
पूर्ण

अटल काष्ठा smem_निजी_entry *
phdr_to_first_uncached_entry(काष्ठा smem_partition_header *phdr)
अणु
	व्योम *p = phdr;

	वापस p + माप(*phdr);
पूर्ण

अटल काष्ठा smem_निजी_entry *
uncached_entry_next(काष्ठा smem_निजी_entry *e)
अणु
	व्योम *p = e;

	वापस p + माप(*e) + le16_to_cpu(e->padding_hdr) +
	       le32_to_cpu(e->size);
पूर्ण

अटल काष्ठा smem_निजी_entry *
cached_entry_next(काष्ठा smem_निजी_entry *e, माप_प्रकार cacheline)
अणु
	व्योम *p = e;

	वापस p - le32_to_cpu(e->size) - ALIGN(माप(*e), cacheline);
पूर्ण

अटल व्योम *uncached_entry_to_item(काष्ठा smem_निजी_entry *e)
अणु
	व्योम *p = e;

	वापस p + माप(*e) + le16_to_cpu(e->padding_hdr);
पूर्ण

अटल व्योम *cached_entry_to_item(काष्ठा smem_निजी_entry *e)
अणु
	व्योम *p = e;

	वापस p - le32_to_cpu(e->size);
पूर्ण

/* Poपूर्णांकer to the one and only smem handle */
अटल काष्ठा qcom_smem *__smem;

/* Timeout (ms) क्रम the trylock of remote spinlocks */
#घोषणा HWSPINLOCK_TIMEOUT	1000

अटल पूर्णांक qcom_smem_alloc_निजी(काष्ठा qcom_smem *smem,
				   काष्ठा smem_partition_header *phdr,
				   अचिन्हित item,
				   माप_प्रकार size)
अणु
	काष्ठा smem_निजी_entry *hdr, *end;
	माप_प्रकार alloc_size;
	व्योम *cached;

	hdr = phdr_to_first_uncached_entry(phdr);
	end = phdr_to_last_uncached_entry(phdr);
	cached = phdr_to_last_cached_entry(phdr);

	जबतक (hdr < end) अणु
		अगर (hdr->canary != SMEM_PRIVATE_CANARY)
			जाओ bad_canary;
		अगर (le16_to_cpu(hdr->item) == item)
			वापस -EEXIST;

		hdr = uncached_entry_next(hdr);
	पूर्ण

	/* Check that we करोn't grow पूर्णांकo the cached region */
	alloc_size = माप(*hdr) + ALIGN(size, 8);
	अगर ((व्योम *)hdr + alloc_size > cached) अणु
		dev_err(smem->dev, "Out of memory\n");
		वापस -ENOSPC;
	पूर्ण

	hdr->canary = SMEM_PRIVATE_CANARY;
	hdr->item = cpu_to_le16(item);
	hdr->size = cpu_to_le32(ALIGN(size, 8));
	hdr->padding_data = cpu_to_le16(le32_to_cpu(hdr->size) - size);
	hdr->padding_hdr = 0;

	/*
	 * Ensure the header is written beक्रमe we advance the मुक्त offset, so
	 * that remote processors that करोes not take the remote spinlock still
	 * माला_लो a consistent view of the linked list.
	 */
	wmb();
	le32_add_cpu(&phdr->offset_मुक्त_uncached, alloc_size);

	वापस 0;
bad_canary:
	dev_err(smem->dev, "Found invalid canary in hosts %hu:%hu partition\n",
		le16_to_cpu(phdr->host0), le16_to_cpu(phdr->host1));

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक qcom_smem_alloc_global(काष्ठा qcom_smem *smem,
				  अचिन्हित item,
				  माप_प्रकार size)
अणु
	काष्ठा smem_global_entry *entry;
	काष्ठा smem_header *header;

	header = smem->regions[0].virt_base;
	entry = &header->toc[item];
	अगर (entry->allocated)
		वापस -EEXIST;

	size = ALIGN(size, 8);
	अगर (WARN_ON(size > le32_to_cpu(header->available)))
		वापस -ENOMEM;

	entry->offset = header->मुक्त_offset;
	entry->size = cpu_to_le32(size);

	/*
	 * Ensure the header is consistent beक्रमe we mark the item allocated,
	 * so that remote processors will get a consistent view of the item
	 * even though they करो not take the spinlock on पढ़ो.
	 */
	wmb();
	entry->allocated = cpu_to_le32(1);

	le32_add_cpu(&header->मुक्त_offset, size);
	le32_add_cpu(&header->available, -size);

	वापस 0;
पूर्ण

/**
 * qcom_smem_alloc() - allocate space क्रम a smem item
 * @host:	remote processor id, or -1
 * @item:	smem item handle
 * @size:	number of bytes to be allocated
 *
 * Allocate space क्रम a given smem item of size @size, given that the item is
 * not yet allocated.
 */
पूर्णांक qcom_smem_alloc(अचिन्हित host, अचिन्हित item, माप_प्रकार size)
अणु
	काष्ठा smem_partition_header *phdr;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!__smem)
		वापस -EPROBE_DEFER;

	अगर (item < SMEM_ITEM_LAST_FIXED) अणु
		dev_err(__smem->dev,
			"Rejecting allocation of static entry %d\n", item);
		वापस -EINVAL;
	पूर्ण

	अगर (WARN_ON(item >= __smem->item_count))
		वापस -EINVAL;

	ret = hwspin_lock_समयout_irqsave(__smem->hwlock,
					  HWSPINLOCK_TIMEOUT,
					  &flags);
	अगर (ret)
		वापस ret;

	अगर (host < SMEM_HOST_COUNT && __smem->partitions[host]) अणु
		phdr = __smem->partitions[host];
		ret = qcom_smem_alloc_निजी(__smem, phdr, item, size);
	पूर्ण अन्यथा अगर (__smem->global_partition) अणु
		phdr = __smem->global_partition;
		ret = qcom_smem_alloc_निजी(__smem, phdr, item, size);
	पूर्ण अन्यथा अणु
		ret = qcom_smem_alloc_global(__smem, item, size);
	पूर्ण

	hwspin_unlock_irqrestore(__smem->hwlock, &flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(qcom_smem_alloc);

अटल व्योम *qcom_smem_get_global(काष्ठा qcom_smem *smem,
				  अचिन्हित item,
				  माप_प्रकार *size)
अणु
	काष्ठा smem_header *header;
	काष्ठा smem_region *region;
	काष्ठा smem_global_entry *entry;
	u32 aux_base;
	अचिन्हित i;

	header = smem->regions[0].virt_base;
	entry = &header->toc[item];
	अगर (!entry->allocated)
		वापस ERR_PTR(-ENXIO);

	aux_base = le32_to_cpu(entry->aux_base) & AUX_BASE_MASK;

	क्रम (i = 0; i < smem->num_regions; i++) अणु
		region = &smem->regions[i];

		अगर (region->aux_base == aux_base || !aux_base) अणु
			अगर (size != शून्य)
				*size = le32_to_cpu(entry->size);
			वापस region->virt_base + le32_to_cpu(entry->offset);
		पूर्ण
	पूर्ण

	वापस ERR_PTR(-ENOENT);
पूर्ण

अटल व्योम *qcom_smem_get_निजी(काष्ठा qcom_smem *smem,
				   काष्ठा smem_partition_header *phdr,
				   माप_प्रकार cacheline,
				   अचिन्हित item,
				   माप_प्रकार *size)
अणु
	काष्ठा smem_निजी_entry *e, *end;

	e = phdr_to_first_uncached_entry(phdr);
	end = phdr_to_last_uncached_entry(phdr);

	जबतक (e < end) अणु
		अगर (e->canary != SMEM_PRIVATE_CANARY)
			जाओ invalid_canary;

		अगर (le16_to_cpu(e->item) == item) अणु
			अगर (size != शून्य)
				*size = le32_to_cpu(e->size) -
					le16_to_cpu(e->padding_data);

			वापस uncached_entry_to_item(e);
		पूर्ण

		e = uncached_entry_next(e);
	पूर्ण

	/* Item was not found in the uncached list, search the cached list */

	e = phdr_to_first_cached_entry(phdr, cacheline);
	end = phdr_to_last_cached_entry(phdr);

	जबतक (e > end) अणु
		अगर (e->canary != SMEM_PRIVATE_CANARY)
			जाओ invalid_canary;

		अगर (le16_to_cpu(e->item) == item) अणु
			अगर (size != शून्य)
				*size = le32_to_cpu(e->size) -
					le16_to_cpu(e->padding_data);

			वापस cached_entry_to_item(e);
		पूर्ण

		e = cached_entry_next(e, cacheline);
	पूर्ण

	वापस ERR_PTR(-ENOENT);

invalid_canary:
	dev_err(smem->dev, "Found invalid canary in hosts %hu:%hu partition\n",
			le16_to_cpu(phdr->host0), le16_to_cpu(phdr->host1));

	वापस ERR_PTR(-EINVAL);
पूर्ण

/**
 * qcom_smem_get() - resolve ptr of size of a smem item
 * @host:	the remote processor, or -1
 * @item:	smem item handle
 * @size:	poपूर्णांकer to be filled out with size of the item
 *
 * Looks up smem item and वापसs poपूर्णांकer to it. Size of smem
 * item is वापसed in @size.
 */
व्योम *qcom_smem_get(अचिन्हित host, अचिन्हित item, माप_प्रकार *size)
अणु
	काष्ठा smem_partition_header *phdr;
	अचिन्हित दीर्घ flags;
	माप_प्रकार cacheln;
	पूर्णांक ret;
	व्योम *ptr = ERR_PTR(-EPROBE_DEFER);

	अगर (!__smem)
		वापस ptr;

	अगर (WARN_ON(item >= __smem->item_count))
		वापस ERR_PTR(-EINVAL);

	ret = hwspin_lock_समयout_irqsave(__smem->hwlock,
					  HWSPINLOCK_TIMEOUT,
					  &flags);
	अगर (ret)
		वापस ERR_PTR(ret);

	अगर (host < SMEM_HOST_COUNT && __smem->partitions[host]) अणु
		phdr = __smem->partitions[host];
		cacheln = __smem->cacheline[host];
		ptr = qcom_smem_get_निजी(__smem, phdr, cacheln, item, size);
	पूर्ण अन्यथा अगर (__smem->global_partition) अणु
		phdr = __smem->global_partition;
		cacheln = __smem->global_cacheline;
		ptr = qcom_smem_get_निजी(__smem, phdr, cacheln, item, size);
	पूर्ण अन्यथा अणु
		ptr = qcom_smem_get_global(__smem, item, size);
	पूर्ण

	hwspin_unlock_irqrestore(__smem->hwlock, &flags);

	वापस ptr;

पूर्ण
EXPORT_SYMBOL(qcom_smem_get);

/**
 * qcom_smem_get_मुक्त_space() - retrieve amount of मुक्त space in a partition
 * @host:	the remote processor identअगरying a partition, or -1
 *
 * To be used by smem clients as a quick way to determine अगर any new
 * allocations has been made.
 */
पूर्णांक qcom_smem_get_मुक्त_space(अचिन्हित host)
अणु
	काष्ठा smem_partition_header *phdr;
	काष्ठा smem_header *header;
	अचिन्हित ret;

	अगर (!__smem)
		वापस -EPROBE_DEFER;

	अगर (host < SMEM_HOST_COUNT && __smem->partitions[host]) अणु
		phdr = __smem->partitions[host];
		ret = le32_to_cpu(phdr->offset_मुक्त_cached) -
		      le32_to_cpu(phdr->offset_मुक्त_uncached);
	पूर्ण अन्यथा अगर (__smem->global_partition) अणु
		phdr = __smem->global_partition;
		ret = le32_to_cpu(phdr->offset_मुक्त_cached) -
		      le32_to_cpu(phdr->offset_मुक्त_uncached);
	पूर्ण अन्यथा अणु
		header = __smem->regions[0].virt_base;
		ret = le32_to_cpu(header->available);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(qcom_smem_get_मुक्त_space);

/**
 * qcom_smem_virt_to_phys() - वापस the physical address associated
 * with an smem item poपूर्णांकer (previously वापसed by qcom_smem_get()
 * @p:	the भव address to convert
 *
 * Returns 0 अगर the poपूर्णांकer provided is not within any smem region.
 */
phys_addr_t qcom_smem_virt_to_phys(व्योम *p)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < __smem->num_regions; i++) अणु
		काष्ठा smem_region *region = &__smem->regions[i];

		अगर (p < region->virt_base)
			जारी;
		अगर (p < region->virt_base + region->size) अणु
			u64 offset = p - region->virt_base;

			वापस (phys_addr_t)region->aux_base + offset;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(qcom_smem_virt_to_phys);

अटल पूर्णांक qcom_smem_get_sbl_version(काष्ठा qcom_smem *smem)
अणु
	काष्ठा smem_header *header;
	__le32 *versions;

	header = smem->regions[0].virt_base;
	versions = header->version;

	वापस le32_to_cpu(versions[SMEM_MASTER_SBL_VERSION_INDEX]);
पूर्ण

अटल काष्ठा smem_ptable *qcom_smem_get_ptable(काष्ठा qcom_smem *smem)
अणु
	काष्ठा smem_ptable *ptable;
	u32 version;

	ptable = smem->regions[0].virt_base + smem->regions[0].size - SZ_4K;
	अगर (स_भेद(ptable->magic, SMEM_PTABLE_MAGIC, माप(ptable->magic)))
		वापस ERR_PTR(-ENOENT);

	version = le32_to_cpu(ptable->version);
	अगर (version != 1) अणु
		dev_err(smem->dev,
			"Unsupported partition header version %d\n", version);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	वापस ptable;
पूर्ण

अटल u32 qcom_smem_get_item_count(काष्ठा qcom_smem *smem)
अणु
	काष्ठा smem_ptable *ptable;
	काष्ठा smem_info *info;

	ptable = qcom_smem_get_ptable(smem);
	अगर (IS_ERR_OR_शून्य(ptable))
		वापस SMEM_ITEM_COUNT;

	info = (काष्ठा smem_info *)&ptable->entry[ptable->num_entries];
	अगर (स_भेद(info->magic, SMEM_INFO_MAGIC, माप(info->magic)))
		वापस SMEM_ITEM_COUNT;

	वापस le16_to_cpu(info->num_items);
पूर्ण

/*
 * Validate the partition header क्रम a partition whose partition
 * table entry is supplied.  Returns a poपूर्णांकer to its header अगर
 * valid, or a null poपूर्णांकer otherwise.
 */
अटल काष्ठा smem_partition_header *
qcom_smem_partition_header(काष्ठा qcom_smem *smem,
		काष्ठा smem_ptable_entry *entry, u16 host0, u16 host1)
अणु
	काष्ठा smem_partition_header *header;
	u32 size;

	header = smem->regions[0].virt_base + le32_to_cpu(entry->offset);

	अगर (स_भेद(header->magic, SMEM_PART_MAGIC, माप(header->magic))) अणु
		dev_err(smem->dev, "bad partition magic %4ph\n", header->magic);
		वापस शून्य;
	पूर्ण

	अगर (host0 != le16_to_cpu(header->host0)) अणु
		dev_err(smem->dev, "bad host0 (%hu != %hu)\n",
				host0, le16_to_cpu(header->host0));
		वापस शून्य;
	पूर्ण
	अगर (host1 != le16_to_cpu(header->host1)) अणु
		dev_err(smem->dev, "bad host1 (%hu != %hu)\n",
				host1, le16_to_cpu(header->host1));
		वापस शून्य;
	पूर्ण

	size = le32_to_cpu(header->size);
	अगर (size != le32_to_cpu(entry->size)) अणु
		dev_err(smem->dev, "bad partition size (%u != %u)\n",
			size, le32_to_cpu(entry->size));
		वापस शून्य;
	पूर्ण

	अगर (le32_to_cpu(header->offset_मुक्त_uncached) > size) अणु
		dev_err(smem->dev, "bad partition free uncached (%u > %u)\n",
			le32_to_cpu(header->offset_मुक्त_uncached), size);
		वापस शून्य;
	पूर्ण

	वापस header;
पूर्ण

अटल पूर्णांक qcom_smem_set_global_partition(काष्ठा qcom_smem *smem)
अणु
	काष्ठा smem_partition_header *header;
	काष्ठा smem_ptable_entry *entry;
	काष्ठा smem_ptable *ptable;
	bool found = false;
	पूर्णांक i;

	अगर (smem->global_partition) अणु
		dev_err(smem->dev, "Already found the global partition\n");
		वापस -EINVAL;
	पूर्ण

	ptable = qcom_smem_get_ptable(smem);
	अगर (IS_ERR(ptable))
		वापस PTR_ERR(ptable);

	क्रम (i = 0; i < le32_to_cpu(ptable->num_entries); i++) अणु
		entry = &ptable->entry[i];
		अगर (!le32_to_cpu(entry->offset))
			जारी;
		अगर (!le32_to_cpu(entry->size))
			जारी;

		अगर (le16_to_cpu(entry->host0) != SMEM_GLOBAL_HOST)
			जारी;

		अगर (le16_to_cpu(entry->host1) == SMEM_GLOBAL_HOST) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		dev_err(smem->dev, "Missing entry for global partition\n");
		वापस -EINVAL;
	पूर्ण

	header = qcom_smem_partition_header(smem, entry,
				SMEM_GLOBAL_HOST, SMEM_GLOBAL_HOST);
	अगर (!header)
		वापस -EINVAL;

	smem->global_partition = header;
	smem->global_cacheline = le32_to_cpu(entry->cacheline);

	वापस 0;
पूर्ण

अटल पूर्णांक
qcom_smem_क्रमागतerate_partitions(काष्ठा qcom_smem *smem, u16 local_host)
अणु
	काष्ठा smem_partition_header *header;
	काष्ठा smem_ptable_entry *entry;
	काष्ठा smem_ptable *ptable;
	अचिन्हित पूर्णांक remote_host;
	u16 host0, host1;
	पूर्णांक i;

	ptable = qcom_smem_get_ptable(smem);
	अगर (IS_ERR(ptable))
		वापस PTR_ERR(ptable);

	क्रम (i = 0; i < le32_to_cpu(ptable->num_entries); i++) अणु
		entry = &ptable->entry[i];
		अगर (!le32_to_cpu(entry->offset))
			जारी;
		अगर (!le32_to_cpu(entry->size))
			जारी;

		host0 = le16_to_cpu(entry->host0);
		host1 = le16_to_cpu(entry->host1);
		अगर (host0 == local_host)
			remote_host = host1;
		अन्यथा अगर (host1 == local_host)
			remote_host = host0;
		अन्यथा
			जारी;

		अगर (remote_host >= SMEM_HOST_COUNT) अणु
			dev_err(smem->dev, "bad host %hu\n", remote_host);
			वापस -EINVAL;
		पूर्ण

		अगर (smem->partitions[remote_host]) अणु
			dev_err(smem->dev, "duplicate host %hu\n", remote_host);
			वापस -EINVAL;
		पूर्ण

		header = qcom_smem_partition_header(smem, entry, host0, host1);
		अगर (!header)
			वापस -EINVAL;

		smem->partitions[remote_host] = header;
		smem->cacheline[remote_host] = le32_to_cpu(entry->cacheline);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_smem_map_memory(काष्ठा qcom_smem *smem, काष्ठा device *dev,
				स्थिर अक्षर *name, पूर्णांक i)
अणु
	काष्ठा device_node *np;
	काष्ठा resource r;
	resource_माप_प्रकार size;
	पूर्णांक ret;

	np = of_parse_phandle(dev->of_node, name, 0);
	अगर (!np) अणु
		dev_err(dev, "No %s specified\n", name);
		वापस -EINVAL;
	पूर्ण

	ret = of_address_to_resource(np, 0, &r);
	of_node_put(np);
	अगर (ret)
		वापस ret;
	size = resource_size(&r);

	smem->regions[i].virt_base = devm_ioremap_wc(dev, r.start, size);
	अगर (!smem->regions[i].virt_base)
		वापस -ENOMEM;
	smem->regions[i].aux_base = (u32)r.start;
	smem->regions[i].size = size;

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_smem_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा smem_header *header;
	काष्ठा qcom_smem *smem;
	माप_प्रकार array_size;
	पूर्णांक num_regions;
	पूर्णांक hwlock_id;
	u32 version;
	पूर्णांक ret;

	num_regions = 1;
	अगर (of_find_property(pdev->dev.of_node, "qcom,rpm-msg-ram", शून्य))
		num_regions++;

	array_size = num_regions * माप(काष्ठा smem_region);
	smem = devm_kzalloc(&pdev->dev, माप(*smem) + array_size, GFP_KERNEL);
	अगर (!smem)
		वापस -ENOMEM;

	smem->dev = &pdev->dev;
	smem->num_regions = num_regions;

	ret = qcom_smem_map_memory(smem, &pdev->dev, "memory-region", 0);
	अगर (ret)
		वापस ret;

	अगर (num_regions > 1 && (ret = qcom_smem_map_memory(smem, &pdev->dev,
					"qcom,rpm-msg-ram", 1)))
		वापस ret;

	header = smem->regions[0].virt_base;
	अगर (le32_to_cpu(header->initialized) != 1 ||
	    le32_to_cpu(header->reserved)) अणु
		dev_err(&pdev->dev, "SMEM is not initialized by SBL\n");
		वापस -EINVAL;
	पूर्ण

	version = qcom_smem_get_sbl_version(smem);
	चयन (version >> 16) अणु
	हाल SMEM_GLOBAL_PART_VERSION:
		ret = qcom_smem_set_global_partition(smem);
		अगर (ret < 0)
			वापस ret;
		smem->item_count = qcom_smem_get_item_count(smem);
		अवरोध;
	हाल SMEM_GLOBAL_HEAP_VERSION:
		smem->item_count = SMEM_ITEM_COUNT;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Unsupported SMEM version 0x%x\n", version);
		वापस -EINVAL;
	पूर्ण

	BUILD_BUG_ON(SMEM_HOST_APPS >= SMEM_HOST_COUNT);
	ret = qcom_smem_क्रमागतerate_partitions(smem, SMEM_HOST_APPS);
	अगर (ret < 0 && ret != -ENOENT)
		वापस ret;

	hwlock_id = of_hwspin_lock_get_id(pdev->dev.of_node, 0);
	अगर (hwlock_id < 0) अणु
		अगर (hwlock_id != -EPROBE_DEFER)
			dev_err(&pdev->dev, "failed to retrieve hwlock\n");
		वापस hwlock_id;
	पूर्ण

	smem->hwlock = hwspin_lock_request_specअगरic(hwlock_id);
	अगर (!smem->hwlock)
		वापस -ENXIO;

	__smem = smem;

	smem->socinfo = platक्रमm_device_रेजिस्टर_data(&pdev->dev, "qcom-socinfo",
						      PLATFORM_DEVID_NONE, शून्य,
						      0);
	अगर (IS_ERR(smem->socinfo))
		dev_dbg(&pdev->dev, "failed to register socinfo device\n");

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_smem_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	platक्रमm_device_unरेजिस्टर(__smem->socinfo);

	hwspin_lock_मुक्त(__smem->hwlock);
	__smem = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id qcom_smem_of_match[] = अणु
	अणु .compatible = "qcom,smem" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_smem_of_match);

अटल काष्ठा platक्रमm_driver qcom_smem_driver = अणु
	.probe = qcom_smem_probe,
	.हटाओ = qcom_smem_हटाओ,
	.driver  = अणु
		.name = "qcom-smem",
		.of_match_table = qcom_smem_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init qcom_smem_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&qcom_smem_driver);
पूर्ण
arch_initcall(qcom_smem_init);

अटल व्योम __निकास qcom_smem_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&qcom_smem_driver);
पूर्ण
module_निकास(qcom_smem_निकास)

MODULE_AUTHOR("Bjorn Andersson <bjorn.andersson@sonymobile.com>");
MODULE_DESCRIPTION("Qualcomm Shared Memory Manager");
MODULE_LICENSE("GPL v2");
