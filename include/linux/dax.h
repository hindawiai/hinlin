<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_DAX_H
#घोषणा _LINUX_DAX_H

#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/radix-tree.h>

/* Flag क्रम synchronous flush */
#घोषणा DAXDEV_F_SYNC (1UL << 0)

प्रकार अचिन्हित दीर्घ dax_entry_t;

काष्ठा iomap_ops;
काष्ठा iomap;
काष्ठा dax_device;
काष्ठा dax_operations अणु
	/*
	 * direct_access: translate a device-relative
	 * logical-page-offset पूर्णांकo an असलolute physical pfn. Return the
	 * number of pages available क्रम DAX at that pfn.
	 */
	दीर्घ (*direct_access)(काष्ठा dax_device *, pgoff_t, दीर्घ,
			व्योम **, pfn_t *);
	/*
	 * Validate whether this device is usable as an fsdax backing
	 * device.
	 */
	bool (*dax_supported)(काष्ठा dax_device *, काष्ठा block_device *, पूर्णांक,
			sector_t, sector_t);
	/* copy_from_iter: required operation क्रम fs-dax direct-i/o */
	माप_प्रकार (*copy_from_iter)(काष्ठा dax_device *, pgoff_t, व्योम *, माप_प्रकार,
			काष्ठा iov_iter *);
	/* copy_to_iter: required operation क्रम fs-dax direct-i/o */
	माप_प्रकार (*copy_to_iter)(काष्ठा dax_device *, pgoff_t, व्योम *, माप_प्रकार,
			काष्ठा iov_iter *);
	/* zero_page_range: required operation. Zero page range   */
	पूर्णांक (*zero_page_range)(काष्ठा dax_device *, pgoff_t, माप_प्रकार);
पूर्ण;

बाह्य काष्ठा attribute_group dax_attribute_group;

#अगर IS_ENABLED(CONFIG_DAX)
काष्ठा dax_device *dax_get_by_host(स्थिर अक्षर *host);
काष्ठा dax_device *alloc_dax(व्योम *निजी, स्थिर अक्षर *host,
		स्थिर काष्ठा dax_operations *ops, अचिन्हित दीर्घ flags);
व्योम put_dax(काष्ठा dax_device *dax_dev);
व्योम समाप्त_dax(काष्ठा dax_device *dax_dev);
व्योम dax_ग_लिखो_cache(काष्ठा dax_device *dax_dev, bool wc);
bool dax_ग_लिखो_cache_enabled(काष्ठा dax_device *dax_dev);
bool __dax_synchronous(काष्ठा dax_device *dax_dev);
अटल अंतरभूत bool dax_synchronous(काष्ठा dax_device *dax_dev)
अणु
	वापस  __dax_synchronous(dax_dev);
पूर्ण
व्योम __set_dax_synchronous(काष्ठा dax_device *dax_dev);
अटल अंतरभूत व्योम set_dax_synchronous(काष्ठा dax_device *dax_dev)
अणु
	__set_dax_synchronous(dax_dev);
पूर्ण
bool dax_supported(काष्ठा dax_device *dax_dev, काष्ठा block_device *bdev,
		पूर्णांक blocksize, sector_t start, sector_t len);
/*
 * Check अगर given mapping is supported by the file / underlying device.
 */
अटल अंतरभूत bool daxdev_mapping_supported(काष्ठा vm_area_काष्ठा *vma,
					     काष्ठा dax_device *dax_dev)
अणु
	अगर (!(vma->vm_flags & VM_SYNC))
		वापस true;
	अगर (!IS_DAX(file_inode(vma->vm_file)))
		वापस false;
	वापस dax_synchronous(dax_dev);
पूर्ण
#अन्यथा
अटल अंतरभूत काष्ठा dax_device *dax_get_by_host(स्थिर अक्षर *host)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत काष्ठा dax_device *alloc_dax(व्योम *निजी, स्थिर अक्षर *host,
		स्थिर काष्ठा dax_operations *ops, अचिन्हित दीर्घ flags)
अणु
	/*
	 * Callers should check IS_ENABLED(CONFIG_DAX) to know अगर this
	 * शून्य is an error or expected.
	 */
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम put_dax(काष्ठा dax_device *dax_dev)
अणु
पूर्ण
अटल अंतरभूत व्योम समाप्त_dax(काष्ठा dax_device *dax_dev)
अणु
पूर्ण
अटल अंतरभूत व्योम dax_ग_लिखो_cache(काष्ठा dax_device *dax_dev, bool wc)
अणु
पूर्ण
अटल अंतरभूत bool dax_ग_लिखो_cache_enabled(काष्ठा dax_device *dax_dev)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत bool dax_synchronous(काष्ठा dax_device *dax_dev)
अणु
	वापस true;
पूर्ण
अटल अंतरभूत व्योम set_dax_synchronous(काष्ठा dax_device *dax_dev)
अणु
पूर्ण
अटल अंतरभूत bool dax_supported(काष्ठा dax_device *dax_dev,
		काष्ठा block_device *bdev, पूर्णांक blocksize, sector_t start,
		sector_t len)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत bool daxdev_mapping_supported(काष्ठा vm_area_काष्ठा *vma,
				काष्ठा dax_device *dax_dev)
अणु
	वापस !(vma->vm_flags & VM_SYNC);
पूर्ण
#पूर्ण_अगर

काष्ठा ग_लिखोback_control;
पूर्णांक bdev_dax_pgoff(काष्ठा block_device *, sector_t, माप_प्रकार, pgoff_t *pgoff);
#अगर IS_ENABLED(CONFIG_FS_DAX)
bool __bdev_dax_supported(काष्ठा block_device *bdev, पूर्णांक blocksize);
अटल अंतरभूत bool bdev_dax_supported(काष्ठा block_device *bdev, पूर्णांक blocksize)
अणु
	वापस __bdev_dax_supported(bdev, blocksize);
पूर्ण

bool __generic_fsdax_supported(काष्ठा dax_device *dax_dev,
		काष्ठा block_device *bdev, पूर्णांक blocksize, sector_t start,
		sector_t sectors);
अटल अंतरभूत bool generic_fsdax_supported(काष्ठा dax_device *dax_dev,
		काष्ठा block_device *bdev, पूर्णांक blocksize, sector_t start,
		sector_t sectors)
अणु
	वापस __generic_fsdax_supported(dax_dev, bdev, blocksize, start,
			sectors);
पूर्ण

अटल अंतरभूत व्योम fs_put_dax(काष्ठा dax_device *dax_dev)
अणु
	put_dax(dax_dev);
पूर्ण

काष्ठा dax_device *fs_dax_get_by_bdev(काष्ठा block_device *bdev);
पूर्णांक dax_ग_लिखोback_mapping_range(काष्ठा address_space *mapping,
		काष्ठा dax_device *dax_dev, काष्ठा ग_लिखोback_control *wbc);

काष्ठा page *dax_layout_busy_page(काष्ठा address_space *mapping);
काष्ठा page *dax_layout_busy_page_range(काष्ठा address_space *mapping, loff_t start, loff_t end);
dax_entry_t dax_lock_page(काष्ठा page *page);
व्योम dax_unlock_page(काष्ठा page *page, dax_entry_t cookie);
#अन्यथा
अटल अंतरभूत bool bdev_dax_supported(काष्ठा block_device *bdev,
		पूर्णांक blocksize)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool generic_fsdax_supported(काष्ठा dax_device *dax_dev,
		काष्ठा block_device *bdev, पूर्णांक blocksize, sector_t start,
		sector_t sectors)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम fs_put_dax(काष्ठा dax_device *dax_dev)
अणु
पूर्ण

अटल अंतरभूत काष्ठा dax_device *fs_dax_get_by_bdev(काष्ठा block_device *bdev)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा page *dax_layout_busy_page(काष्ठा address_space *mapping)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा page *dax_layout_busy_page_range(काष्ठा address_space *mapping, pgoff_t start, pgoff_t nr_pages)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक dax_ग_लिखोback_mapping_range(काष्ठा address_space *mapping,
		काष्ठा dax_device *dax_dev, काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत dax_entry_t dax_lock_page(काष्ठा page *page)
अणु
	अगर (IS_DAX(page->mapping->host))
		वापस ~0UL;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम dax_unlock_page(काष्ठा page *page, dax_entry_t cookie)
अणु
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_DAX)
पूर्णांक dax_पढ़ो_lock(व्योम);
व्योम dax_पढ़ो_unlock(पूर्णांक id);
#अन्यथा
अटल अंतरभूत पूर्णांक dax_पढ़ो_lock(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम dax_पढ़ो_unlock(पूर्णांक id)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_DAX */
bool dax_alive(काष्ठा dax_device *dax_dev);
व्योम *dax_get_निजी(काष्ठा dax_device *dax_dev);
दीर्घ dax_direct_access(काष्ठा dax_device *dax_dev, pgoff_t pgoff, दीर्घ nr_pages,
		व्योम **kaddr, pfn_t *pfn);
माप_प्रकार dax_copy_from_iter(काष्ठा dax_device *dax_dev, pgoff_t pgoff, व्योम *addr,
		माप_प्रकार bytes, काष्ठा iov_iter *i);
माप_प्रकार dax_copy_to_iter(काष्ठा dax_device *dax_dev, pgoff_t pgoff, व्योम *addr,
		माप_प्रकार bytes, काष्ठा iov_iter *i);
पूर्णांक dax_zero_page_range(काष्ठा dax_device *dax_dev, pgoff_t pgoff,
			माप_प्रकार nr_pages);
व्योम dax_flush(काष्ठा dax_device *dax_dev, व्योम *addr, माप_प्रकार size);

sमाप_प्रकार dax_iomap_rw(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter,
		स्थिर काष्ठा iomap_ops *ops);
vm_fault_t dax_iomap_fault(काष्ठा vm_fault *vmf, क्रमागत page_entry_size pe_size,
		    pfn_t *pfnp, पूर्णांक *errp, स्थिर काष्ठा iomap_ops *ops);
vm_fault_t dax_finish_sync_fault(काष्ठा vm_fault *vmf,
		क्रमागत page_entry_size pe_size, pfn_t pfn);
पूर्णांक dax_delete_mapping_entry(काष्ठा address_space *mapping, pgoff_t index);
पूर्णांक dax_invalidate_mapping_entry_sync(काष्ठा address_space *mapping,
				      pgoff_t index);
s64 dax_iomap_zero(loff_t pos, u64 length, काष्ठा iomap *iomap);
अटल अंतरभूत bool dax_mapping(काष्ठा address_space *mapping)
अणु
	वापस mapping->host && IS_DAX(mapping->host);
पूर्ण

#अगर_घोषित CONFIG_DEV_DAX_HMEM_DEVICES
व्योम hmem_रेजिस्टर_device(पूर्णांक target_nid, काष्ठा resource *r);
#अन्यथा
अटल अंतरभूत व्योम hmem_रेजिस्टर_device(पूर्णांक target_nid, काष्ठा resource *r)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
