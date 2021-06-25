<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2017 IBM Corp.
 */

#समावेश <linux/hugetlb.h>
#समावेश <linux/sched/mm.h>
#समावेश <यंत्र/pnv-pci.h>
#समावेश <misc/cxllib.h>

#समावेश "cxl.h"

#घोषणा CXL_INVALID_DRA                 ~0ull
#घोषणा CXL_DUMMY_READ_SIZE             128
#घोषणा CXL_DUMMY_READ_ALIGN            8
#घोषणा CXL_CAPI_WINDOW_START           0x2000000000000ull
#घोषणा CXL_CAPI_WINDOW_LOG_SIZE        48
#घोषणा CXL_XSL_CONFIG_CURRENT_VERSION  CXL_XSL_CONFIG_VERSION1


bool cxllib_slot_is_supported(काष्ठा pci_dev *dev, अचिन्हित दीर्घ flags)
अणु
	पूर्णांक rc;
	u32 phb_index;
	u64 chip_id, capp_unit_id;

	/* No flags currently supported */
	अगर (flags)
		वापस false;

	अगर (!cpu_has_feature(CPU_FTR_HVMODE))
		वापस false;

	अगर (!cxl_is_घातer9())
		वापस false;

	अगर (cxl_slot_is_चयनed(dev))
		वापस false;

	/* on p9, some pci slots are not connected to a CAPP unit */
	rc = cxl_calc_capp_routing(dev, &chip_id, &phb_index, &capp_unit_id);
	अगर (rc)
		वापस false;

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(cxllib_slot_is_supported);

अटल DEFINE_MUTEX(dra_mutex);
अटल u64 dummy_पढ़ो_addr = CXL_INVALID_DRA;

अटल पूर्णांक allocate_dummy_पढ़ो_buf(व्योम)
अणु
	u64 buf, vaddr;
	माप_प्रकार buf_size;

	/*
	 * Dummy पढ़ो buffer is 128-byte दीर्घ, aligned on a
	 * 256-byte boundary and we need the physical address.
	 */
	buf_size = CXL_DUMMY_READ_SIZE + (1ull << CXL_DUMMY_READ_ALIGN);
	buf = (u64) kzalloc(buf_size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	vaddr = (buf + (1ull << CXL_DUMMY_READ_ALIGN) - 1) &
					(~0ull << CXL_DUMMY_READ_ALIGN);

	WARN((vaddr + CXL_DUMMY_READ_SIZE) > (buf + buf_size),
		"Dummy read buffer alignment issue");
	dummy_पढ़ो_addr = virt_to_phys((व्योम *) vaddr);
	वापस 0;
पूर्ण

पूर्णांक cxllib_get_xsl_config(काष्ठा pci_dev *dev, काष्ठा cxllib_xsl_config *cfg)
अणु
	पूर्णांक rc;
	u32 phb_index;
	u64 chip_id, capp_unit_id;

	अगर (!cpu_has_feature(CPU_FTR_HVMODE))
		वापस -EINVAL;

	mutex_lock(&dra_mutex);
	अगर (dummy_पढ़ो_addr == CXL_INVALID_DRA) अणु
		rc = allocate_dummy_पढ़ो_buf();
		अगर (rc) अणु
			mutex_unlock(&dra_mutex);
			वापस rc;
		पूर्ण
	पूर्ण
	mutex_unlock(&dra_mutex);

	rc = cxl_calc_capp_routing(dev, &chip_id, &phb_index, &capp_unit_id);
	अगर (rc)
		वापस rc;

	rc = cxl_get_xsl9_dsnctl(dev, capp_unit_id, &cfg->dsnctl);
	अगर (rc)
		वापस rc;

	cfg->version  = CXL_XSL_CONFIG_CURRENT_VERSION;
	cfg->log_bar_size = CXL_CAPI_WINDOW_LOG_SIZE;
	cfg->bar_addr = CXL_CAPI_WINDOW_START;
	cfg->dra = dummy_पढ़ो_addr;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cxllib_get_xsl_config);

पूर्णांक cxllib_चयन_phb_mode(काष्ठा pci_dev *dev, क्रमागत cxllib_mode mode,
			अचिन्हित दीर्घ flags)
अणु
	पूर्णांक rc = 0;

	अगर (!cpu_has_feature(CPU_FTR_HVMODE))
		वापस -EINVAL;

	चयन (mode) अणु
	हाल CXL_MODE_PCI:
		/*
		 * We currently करोn't support going back to PCI mode
		 * However, we'll turn the invalidations off, so that
		 * the firmware करोesn't have to ack them and can करो
		 * things like reset, etc.. with no worries.
		 * So always वापस EPERM (can't go back to PCI) or
		 * EBUSY अगर we couldn't even turn off snooping
		 */
		rc = pnv_phb_to_cxl_mode(dev, OPAL_PHB_CAPI_MODE_SNOOP_OFF);
		अगर (rc)
			rc = -EBUSY;
		अन्यथा
			rc = -EPERM;
		अवरोध;
	हाल CXL_MODE_CXL:
		/* DMA only supported on TVT1 क्रम the समय being */
		अगर (flags != CXL_MODE_DMA_TVT1)
			वापस -EINVAL;
		rc = pnv_phb_to_cxl_mode(dev, OPAL_PHB_CAPI_MODE_DMA_TVT1);
		अगर (rc)
			वापस rc;
		rc = pnv_phb_to_cxl_mode(dev, OPAL_PHB_CAPI_MODE_SNOOP_ON);
		अवरोध;
	शेष:
		rc = -EINVAL;
	पूर्ण
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(cxllib_चयन_phb_mode);

/*
 * When चयनing the PHB to capi mode, the TVT#1 entry क्रम
 * the Partitionable Endpoपूर्णांक is set in bypass mode, like
 * in PCI mode.
 * Configure the device dma to use TVT#1, which is करोne
 * by calling dma_set_mask() with a mask large enough.
 */
पूर्णांक cxllib_set_device_dma(काष्ठा pci_dev *dev, अचिन्हित दीर्घ flags)
अणु
	पूर्णांक rc;

	अगर (flags)
		वापस -EINVAL;

	rc = dma_set_mask(&dev->dev, DMA_BIT_MASK(64));
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(cxllib_set_device_dma);

पूर्णांक cxllib_get_PE_attributes(काष्ठा task_काष्ठा *task,
			     अचिन्हित दीर्घ translation_mode,
			     काष्ठा cxllib_pe_attributes *attr)
अणु
	अगर (translation_mode != CXL_TRANSLATED_MODE &&
		translation_mode != CXL_REAL_MODE)
		वापस -EINVAL;

	attr->sr = cxl_calculate_sr(false,
				task == शून्य,
				translation_mode == CXL_REAL_MODE,
				true);
	attr->lpid = mfspr(SPRN_LPID);
	अगर (task) अणु
		काष्ठा mm_काष्ठा *mm = get_task_mm(task);
		अगर (mm == शून्य)
			वापस -EINVAL;
		/*
		 * Caller is keeping a reference on mm_users क्रम as दीर्घ
		 * as XSL uses the memory context
		 */
		attr->pid = mm->context.id;
		mmput(mm);
		attr->tid = task->thपढ़ो.tidr;
	पूर्ण अन्यथा अणु
		attr->pid = 0;
		attr->tid = 0;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cxllib_get_PE_attributes);

अटल पूर्णांक get_vma_info(काष्ठा mm_काष्ठा *mm, u64 addr,
			u64 *vma_start, u64 *vma_end,
			अचिन्हित दीर्घ *page_size)
अणु
	काष्ठा vm_area_काष्ठा *vma = शून्य;
	पूर्णांक rc = 0;

	mmap_पढ़ो_lock(mm);

	vma = find_vma(mm, addr);
	अगर (!vma) अणु
		rc = -EFAULT;
		जाओ out;
	पूर्ण
	*page_size = vma_kernel_pagesize(vma);
	*vma_start = vma->vm_start;
	*vma_end = vma->vm_end;
out:
	mmap_पढ़ो_unlock(mm);
	वापस rc;
पूर्ण

पूर्णांक cxllib_handle_fault(काष्ठा mm_काष्ठा *mm, u64 addr, u64 size, u64 flags)
अणु
	पूर्णांक rc;
	u64 dar, vma_start, vma_end;
	अचिन्हित दीर्घ page_size;

	अगर (mm == शून्य)
		वापस -EFAULT;

	/*
	 * The buffer we have to process can extend over several pages
	 * and may also cover several VMAs.
	 * We iterate over all the pages. The page size could vary
	 * between VMAs.
	 */
	rc = get_vma_info(mm, addr, &vma_start, &vma_end, &page_size);
	अगर (rc)
		वापस rc;

	क्रम (dar = (addr & ~(page_size - 1)); dar < (addr + size);
	     dar += page_size) अणु
		अगर (dar < vma_start || dar >= vma_end) अणु
			/*
			 * We करोn't hold mm->mmap_lock जबतक iterating, since
			 * the lock is required by one of the lower-level page
			 * fault processing functions and it could
			 * create a deadlock.
			 *
			 * It means the VMAs can be altered between 2
			 * loop iterations and we could theoretically
			 * miss a page (however unlikely). But that's
			 * not really a problem, as the driver will
			 * retry access, get another page fault on the
			 * missing page and call us again.
			 */
			rc = get_vma_info(mm, dar, &vma_start, &vma_end,
					&page_size);
			अगर (rc)
				वापस rc;
		पूर्ण

		rc = cxl_handle_mm_fault(mm, flags, dar);
		अगर (rc)
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cxllib_handle_fault);
