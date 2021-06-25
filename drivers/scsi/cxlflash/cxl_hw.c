<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * CXL Flash Device Driver
 *
 * Written by: Matthew R. Ochs <mrochs@linux.vnet.ibm.com>, IBM Corporation
 *             Uma Krishnan <ukrishn@linux.vnet.ibm.com>, IBM Corporation
 *
 * Copyright (C) 2018 IBM Corporation
 */

#समावेश <misc/cxl.h>

#समावेश "backend.h"

/*
 * The following routines map the cxlflash backend operations to existing CXL
 * kernel API function and are largely simple shims that provide an असलtraction
 * क्रम converting generic context and AFU cookies पूर्णांकo cxl_context or cxl_afu
 * poपूर्णांकers.
 */

अटल व्योम __iomem *cxlflash_psa_map(व्योम *ctx_cookie)
अणु
	वापस cxl_psa_map(ctx_cookie);
पूर्ण

अटल व्योम cxlflash_psa_unmap(व्योम __iomem *addr)
अणु
	cxl_psa_unmap(addr);
पूर्ण

अटल पूर्णांक cxlflash_process_element(व्योम *ctx_cookie)
अणु
	वापस cxl_process_element(ctx_cookie);
पूर्ण

अटल पूर्णांक cxlflash_map_afu_irq(व्योम *ctx_cookie, पूर्णांक num,
				irq_handler_t handler, व्योम *cookie, अक्षर *name)
अणु
	वापस cxl_map_afu_irq(ctx_cookie, num, handler, cookie, name);
पूर्ण

अटल व्योम cxlflash_unmap_afu_irq(व्योम *ctx_cookie, पूर्णांक num, व्योम *cookie)
अणु
	cxl_unmap_afu_irq(ctx_cookie, num, cookie);
पूर्ण

अटल u64 cxlflash_get_irq_objhndl(व्योम *ctx_cookie, पूर्णांक irq)
अणु
	/* Dummy fop क्रम cxl */
	वापस 0;
पूर्ण

अटल पूर्णांक cxlflash_start_context(व्योम *ctx_cookie)
अणु
	वापस cxl_start_context(ctx_cookie, 0, शून्य);
पूर्ण

अटल पूर्णांक cxlflash_stop_context(व्योम *ctx_cookie)
अणु
	वापस cxl_stop_context(ctx_cookie);
पूर्ण

अटल पूर्णांक cxlflash_afu_reset(व्योम *ctx_cookie)
अणु
	वापस cxl_afu_reset(ctx_cookie);
पूर्ण

अटल व्योम cxlflash_set_master(व्योम *ctx_cookie)
अणु
	cxl_set_master(ctx_cookie);
पूर्ण

अटल व्योम *cxlflash_get_context(काष्ठा pci_dev *dev, व्योम *afu_cookie)
अणु
	वापस cxl_get_context(dev);
पूर्ण

अटल व्योम *cxlflash_dev_context_init(काष्ठा pci_dev *dev, व्योम *afu_cookie)
अणु
	वापस cxl_dev_context_init(dev);
पूर्ण

अटल पूर्णांक cxlflash_release_context(व्योम *ctx_cookie)
अणु
	वापस cxl_release_context(ctx_cookie);
पूर्ण

अटल व्योम cxlflash_perst_reloads_same_image(व्योम *afu_cookie, bool image)
अणु
	cxl_perst_reloads_same_image(afu_cookie, image);
पूर्ण

अटल sमाप_प्रकार cxlflash_पढ़ो_adapter_vpd(काष्ठा pci_dev *dev,
					 व्योम *buf, माप_प्रकार count)
अणु
	वापस cxl_पढ़ो_adapter_vpd(dev, buf, count);
पूर्ण

अटल पूर्णांक cxlflash_allocate_afu_irqs(व्योम *ctx_cookie, पूर्णांक num)
अणु
	वापस cxl_allocate_afu_irqs(ctx_cookie, num);
पूर्ण

अटल व्योम cxlflash_मुक्त_afu_irqs(व्योम *ctx_cookie)
अणु
	cxl_मुक्त_afu_irqs(ctx_cookie);
पूर्ण

अटल व्योम *cxlflash_create_afu(काष्ठा pci_dev *dev)
अणु
	वापस cxl_pci_to_afu(dev);
पूर्ण

अटल व्योम cxlflash_destroy_afu(व्योम *afu)
अणु
	/* Dummy fop क्रम cxl */
पूर्ण

अटल काष्ठा file *cxlflash_get_fd(व्योम *ctx_cookie,
				    काष्ठा file_operations *fops, पूर्णांक *fd)
अणु
	वापस cxl_get_fd(ctx_cookie, fops, fd);
पूर्ण

अटल व्योम *cxlflash_fops_get_context(काष्ठा file *file)
अणु
	वापस cxl_fops_get_context(file);
पूर्ण

अटल पूर्णांक cxlflash_start_work(व्योम *ctx_cookie, u64 irqs)
अणु
	काष्ठा cxl_ioctl_start_work work = अणु 0 पूर्ण;

	work.num_पूर्णांकerrupts = irqs;
	work.flags = CXL_START_WORK_NUM_IRQS;

	वापस cxl_start_work(ctx_cookie, &work);
पूर्ण

अटल पूर्णांक cxlflash_fd_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vm)
अणु
	वापस cxl_fd_mmap(file, vm);
पूर्ण

अटल पूर्णांक cxlflash_fd_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस cxl_fd_release(inode, file);
पूर्ण

स्थिर काष्ठा cxlflash_backend_ops cxlflash_cxl_ops = अणु
	.module			= THIS_MODULE,
	.psa_map		= cxlflash_psa_map,
	.psa_unmap		= cxlflash_psa_unmap,
	.process_element	= cxlflash_process_element,
	.map_afu_irq		= cxlflash_map_afu_irq,
	.unmap_afu_irq		= cxlflash_unmap_afu_irq,
	.get_irq_objhndl	= cxlflash_get_irq_objhndl,
	.start_context		= cxlflash_start_context,
	.stop_context		= cxlflash_stop_context,
	.afu_reset		= cxlflash_afu_reset,
	.set_master		= cxlflash_set_master,
	.get_context		= cxlflash_get_context,
	.dev_context_init	= cxlflash_dev_context_init,
	.release_context	= cxlflash_release_context,
	.perst_reloads_same_image = cxlflash_perst_reloads_same_image,
	.पढ़ो_adapter_vpd	= cxlflash_पढ़ो_adapter_vpd,
	.allocate_afu_irqs	= cxlflash_allocate_afu_irqs,
	.मुक्त_afu_irqs		= cxlflash_मुक्त_afu_irqs,
	.create_afu		= cxlflash_create_afu,
	.destroy_afu		= cxlflash_destroy_afu,
	.get_fd			= cxlflash_get_fd,
	.fops_get_context	= cxlflash_fops_get_context,
	.start_work		= cxlflash_start_work,
	.fd_mmap		= cxlflash_fd_mmap,
	.fd_release		= cxlflash_fd_release,
पूर्ण;
