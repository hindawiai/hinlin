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

#समावेश <linux/file.h>
#समावेश <linux/idr.h>
#समावेश <linux/module.h>
#समावेश <linux/mount.h>
#समावेश <linux/pseuकरो_fs.h>
#समावेश <linux/poll.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/xive.h>
#समावेश <misc/ocxl.h>

#समावेश <uapi/misc/cxl.h>

#समावेश "backend.h"
#समावेश "ocxl_hw.h"

/*
 * Pseuकरो-fileप्रणाली to allocate inodes.
 */

#घोषणा OCXLFLASH_FS_MAGIC      0x1697698f

अटल पूर्णांक ocxlflash_fs_cnt;
अटल काष्ठा vfsmount *ocxlflash_vfs_mount;

अटल पूर्णांक ocxlflash_fs_init_fs_context(काष्ठा fs_context *fc)
अणु
	वापस init_pseuकरो(fc, OCXLFLASH_FS_MAGIC) ? 0 : -ENOMEM;
पूर्ण

अटल काष्ठा file_प्रणाली_type ocxlflash_fs_type = अणु
	.name		= "ocxlflash",
	.owner		= THIS_MODULE,
	.init_fs_context = ocxlflash_fs_init_fs_context,
	.समाप्त_sb	= समाप्त_anon_super,
पूर्ण;

/*
 * ocxlflash_release_mapping() - release the memory mapping
 * @ctx:	Context whose mapping is to be released.
 */
अटल व्योम ocxlflash_release_mapping(काष्ठा ocxlflash_context *ctx)
अणु
	अगर (ctx->mapping)
		simple_release_fs(&ocxlflash_vfs_mount, &ocxlflash_fs_cnt);
	ctx->mapping = शून्य;
पूर्ण

/*
 * ocxlflash_getfile() - allocate pseuकरो fileप्रणाली, inode, and the file
 * @dev:	Generic device of the host.
 * @name:	Name of the pseuकरो fileप्रणाली.
 * @fops:	File operations.
 * @priv:	Private data.
 * @flags:	Flags क्रम the file.
 *
 * Return: poपूर्णांकer to the file on success, ERR_PTR on failure
 */
अटल काष्ठा file *ocxlflash_getfile(काष्ठा device *dev, स्थिर अक्षर *name,
				      स्थिर काष्ठा file_operations *fops,
				      व्योम *priv, पूर्णांक flags)
अणु
	काष्ठा file *file;
	काष्ठा inode *inode;
	पूर्णांक rc;

	अगर (fops->owner && !try_module_get(fops->owner)) अणु
		dev_err(dev, "%s: Owner does not exist\n", __func__);
		rc = -ENOENT;
		जाओ err1;
	पूर्ण

	rc = simple_pin_fs(&ocxlflash_fs_type, &ocxlflash_vfs_mount,
			   &ocxlflash_fs_cnt);
	अगर (unlikely(rc < 0)) अणु
		dev_err(dev, "%s: Cannot mount ocxlflash pseudofs rc=%d\n",
			__func__, rc);
		जाओ err2;
	पूर्ण

	inode = alloc_anon_inode(ocxlflash_vfs_mount->mnt_sb);
	अगर (IS_ERR(inode)) अणु
		rc = PTR_ERR(inode);
		dev_err(dev, "%s: alloc_anon_inode failed rc=%d\n",
			__func__, rc);
		जाओ err3;
	पूर्ण

	file = alloc_file_pseuकरो(inode, ocxlflash_vfs_mount, name,
				 flags & (O_ACCMODE | O_NONBLOCK), fops);
	अगर (IS_ERR(file)) अणु
		rc = PTR_ERR(file);
		dev_err(dev, "%s: alloc_file failed rc=%d\n",
			__func__, rc);
		जाओ err4;
	पूर्ण

	file->निजी_data = priv;
out:
	वापस file;
err4:
	iput(inode);
err3:
	simple_release_fs(&ocxlflash_vfs_mount, &ocxlflash_fs_cnt);
err2:
	module_put(fops->owner);
err1:
	file = ERR_PTR(rc);
	जाओ out;
पूर्ण

/**
 * ocxlflash_psa_map() - map the process specअगरic MMIO space
 * @ctx_cookie:	Adapter context क्रम which the mapping needs to be करोne.
 *
 * Return: MMIO poपूर्णांकer of the mapped region
 */
अटल व्योम __iomem *ocxlflash_psa_map(व्योम *ctx_cookie)
अणु
	काष्ठा ocxlflash_context *ctx = ctx_cookie;
	काष्ठा device *dev = ctx->hw_afu->dev;

	mutex_lock(&ctx->state_mutex);
	अगर (ctx->state != STARTED) अणु
		dev_err(dev, "%s: Context not started, state=%d\n", __func__,
			ctx->state);
		mutex_unlock(&ctx->state_mutex);
		वापस शून्य;
	पूर्ण
	mutex_unlock(&ctx->state_mutex);

	वापस ioremap(ctx->psn_phys, ctx->psn_size);
पूर्ण

/**
 * ocxlflash_psa_unmap() - unmap the process specअगरic MMIO space
 * @addr:	MMIO poपूर्णांकer to unmap.
 */
अटल व्योम ocxlflash_psa_unmap(व्योम __iomem *addr)
अणु
	iounmap(addr);
पूर्ण

/**
 * ocxlflash_process_element() - get process element of the adapter context
 * @ctx_cookie:	Adapter context associated with the process element.
 *
 * Return: process element of the adapter context
 */
अटल पूर्णांक ocxlflash_process_element(व्योम *ctx_cookie)
अणु
	काष्ठा ocxlflash_context *ctx = ctx_cookie;

	वापस ctx->pe;
पूर्ण

/**
 * afu_map_irq() - map the पूर्णांकerrupt of the adapter context
 * @flags:	Flags.
 * @ctx:	Adapter context.
 * @num:	Per-context AFU पूर्णांकerrupt number.
 * @handler:	Interrupt handler to रेजिस्टर.
 * @cookie:	Interrupt handler निजी data.
 * @name:	Name of the पूर्णांकerrupt.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक afu_map_irq(u64 flags, काष्ठा ocxlflash_context *ctx, पूर्णांक num,
		       irq_handler_t handler, व्योम *cookie, अक्षर *name)
अणु
	काष्ठा ocxl_hw_afu *afu = ctx->hw_afu;
	काष्ठा device *dev = afu->dev;
	काष्ठा ocxlflash_irqs *irq;
	काष्ठा xive_irq_data *xd;
	u32 virq;
	पूर्णांक rc = 0;

	अगर (num < 0 || num >= ctx->num_irqs) अणु
		dev_err(dev, "%s: Interrupt %d not allocated\n", __func__, num);
		rc = -ENOENT;
		जाओ out;
	पूर्ण

	irq = &ctx->irqs[num];
	virq = irq_create_mapping(शून्य, irq->hwirq);
	अगर (unlikely(!virq)) अणु
		dev_err(dev, "%s: irq_create_mapping failed\n", __func__);
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	rc = request_irq(virq, handler, 0, name, cookie);
	अगर (unlikely(rc)) अणु
		dev_err(dev, "%s: request_irq failed rc=%d\n", __func__, rc);
		जाओ err1;
	पूर्ण

	xd = irq_get_handler_data(virq);
	अगर (unlikely(!xd)) अणु
		dev_err(dev, "%s: Can't get interrupt data\n", __func__);
		rc = -ENXIO;
		जाओ err2;
	पूर्ण

	irq->virq = virq;
	irq->vtrig = xd->trig_mmio;
out:
	वापस rc;
err2:
	मुक्त_irq(virq, cookie);
err1:
	irq_dispose_mapping(virq);
	जाओ out;
पूर्ण

/**
 * ocxlflash_map_afu_irq() - map the पूर्णांकerrupt of the adapter context
 * @ctx_cookie:	Adapter context.
 * @num:	Per-context AFU पूर्णांकerrupt number.
 * @handler:	Interrupt handler to रेजिस्टर.
 * @cookie:	Interrupt handler निजी data.
 * @name:	Name of the पूर्णांकerrupt.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक ocxlflash_map_afu_irq(व्योम *ctx_cookie, पूर्णांक num,
				 irq_handler_t handler, व्योम *cookie,
				 अक्षर *name)
अणु
	वापस afu_map_irq(0, ctx_cookie, num, handler, cookie, name);
पूर्ण

/**
 * afu_unmap_irq() - unmap the पूर्णांकerrupt
 * @flags:	Flags.
 * @ctx:	Adapter context.
 * @num:	Per-context AFU पूर्णांकerrupt number.
 * @cookie:	Interrupt handler निजी data.
 */
अटल व्योम afu_unmap_irq(u64 flags, काष्ठा ocxlflash_context *ctx, पूर्णांक num,
			  व्योम *cookie)
अणु
	काष्ठा ocxl_hw_afu *afu = ctx->hw_afu;
	काष्ठा device *dev = afu->dev;
	काष्ठा ocxlflash_irqs *irq;

	अगर (num < 0 || num >= ctx->num_irqs) अणु
		dev_err(dev, "%s: Interrupt %d not allocated\n", __func__, num);
		वापस;
	पूर्ण

	irq = &ctx->irqs[num];

	अगर (irq_find_mapping(शून्य, irq->hwirq)) अणु
		मुक्त_irq(irq->virq, cookie);
		irq_dispose_mapping(irq->virq);
	पूर्ण

	स_रखो(irq, 0, माप(*irq));
पूर्ण

/**
 * ocxlflash_unmap_afu_irq() - unmap the पूर्णांकerrupt
 * @ctx_cookie:	Adapter context.
 * @num:	Per-context AFU पूर्णांकerrupt number.
 * @cookie:	Interrupt handler निजी data.
 */
अटल व्योम ocxlflash_unmap_afu_irq(व्योम *ctx_cookie, पूर्णांक num, व्योम *cookie)
अणु
	वापस afu_unmap_irq(0, ctx_cookie, num, cookie);
पूर्ण

/**
 * ocxlflash_get_irq_objhndl() - get the object handle क्रम an पूर्णांकerrupt
 * @ctx_cookie:	Context associated with the पूर्णांकerrupt.
 * @irq:	Interrupt number.
 *
 * Return: effective address of the mapped region
 */
अटल u64 ocxlflash_get_irq_objhndl(व्योम *ctx_cookie, पूर्णांक irq)
अणु
	काष्ठा ocxlflash_context *ctx = ctx_cookie;

	अगर (irq < 0 || irq >= ctx->num_irqs)
		वापस 0;

	वापस (__क्रमce u64)ctx->irqs[irq].vtrig;
पूर्ण

/**
 * ocxlflash_xsl_fault() - callback when translation error is triggered
 * @data:	Private data provided at callback registration, the context.
 * @addr:	Address that triggered the error.
 * @dsisr:	Value of dsisr रेजिस्टर.
 */
अटल व्योम ocxlflash_xsl_fault(व्योम *data, u64 addr, u64 dsisr)
अणु
	काष्ठा ocxlflash_context *ctx = data;

	spin_lock(&ctx->slock);
	ctx->fault_addr = addr;
	ctx->fault_dsisr = dsisr;
	ctx->pending_fault = true;
	spin_unlock(&ctx->slock);

	wake_up_all(&ctx->wq);
पूर्ण

/**
 * start_context() - local routine to start a context
 * @ctx:	Adapter context to be started.
 *
 * Assign the context specअगरic MMIO space, add and enable the PE.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक start_context(काष्ठा ocxlflash_context *ctx)
अणु
	काष्ठा ocxl_hw_afu *afu = ctx->hw_afu;
	काष्ठा ocxl_afu_config *acfg = &afu->acfg;
	व्योम *link_token = afu->link_token;
	काष्ठा pci_dev *pdev = afu->pdev;
	काष्ठा device *dev = afu->dev;
	bool master = ctx->master;
	काष्ठा mm_काष्ठा *mm;
	पूर्णांक rc = 0;
	u32 pid;

	mutex_lock(&ctx->state_mutex);
	अगर (ctx->state != OPENED) अणु
		dev_err(dev, "%s: Context state invalid, state=%d\n",
			__func__, ctx->state);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (master) अणु
		ctx->psn_size = acfg->global_mmio_size;
		ctx->psn_phys = afu->gmmio_phys;
	पूर्ण अन्यथा अणु
		ctx->psn_size = acfg->pp_mmio_stride;
		ctx->psn_phys = afu->ppmmio_phys + (ctx->pe * ctx->psn_size);
	पूर्ण

	/* pid and mm not set क्रम master contexts */
	अगर (master) अणु
		pid = 0;
		mm = शून्य;
	पूर्ण अन्यथा अणु
		pid = current->mm->context.id;
		mm = current->mm;
	पूर्ण

	rc = ocxl_link_add_pe(link_token, ctx->pe, pid, 0, 0,
			      pci_dev_id(pdev), mm, ocxlflash_xsl_fault,
			      ctx);
	अगर (unlikely(rc)) अणु
		dev_err(dev, "%s: ocxl_link_add_pe failed rc=%d\n",
			__func__, rc);
		जाओ out;
	पूर्ण

	ctx->state = STARTED;
out:
	mutex_unlock(&ctx->state_mutex);
	वापस rc;
पूर्ण

/**
 * ocxlflash_start_context() - start a kernel context
 * @ctx_cookie:	Adapter context to be started.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक ocxlflash_start_context(व्योम *ctx_cookie)
अणु
	काष्ठा ocxlflash_context *ctx = ctx_cookie;

	वापस start_context(ctx);
पूर्ण

/**
 * ocxlflash_stop_context() - stop a context
 * @ctx_cookie:	Adapter context to be stopped.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक ocxlflash_stop_context(व्योम *ctx_cookie)
अणु
	काष्ठा ocxlflash_context *ctx = ctx_cookie;
	काष्ठा ocxl_hw_afu *afu = ctx->hw_afu;
	काष्ठा ocxl_afu_config *acfg = &afu->acfg;
	काष्ठा pci_dev *pdev = afu->pdev;
	काष्ठा device *dev = afu->dev;
	क्रमागत ocxlflash_ctx_state state;
	पूर्णांक rc = 0;

	mutex_lock(&ctx->state_mutex);
	state = ctx->state;
	ctx->state = CLOSED;
	mutex_unlock(&ctx->state_mutex);
	अगर (state != STARTED)
		जाओ out;

	rc = ocxl_config_terminate_pasid(pdev, acfg->dvsec_afu_control_pos,
					 ctx->pe);
	अगर (unlikely(rc)) अणु
		dev_err(dev, "%s: ocxl_config_terminate_pasid failed rc=%d\n",
			__func__, rc);
		/* If EBUSY, PE could be referenced in future by the AFU */
		अगर (rc == -EBUSY)
			जाओ out;
	पूर्ण

	rc = ocxl_link_हटाओ_pe(afu->link_token, ctx->pe);
	अगर (unlikely(rc)) अणु
		dev_err(dev, "%s: ocxl_link_remove_pe failed rc=%d\n",
			__func__, rc);
		जाओ out;
	पूर्ण
out:
	वापस rc;
पूर्ण

/**
 * ocxlflash_afu_reset() - reset the AFU
 * @ctx_cookie:	Adapter context.
 */
अटल पूर्णांक ocxlflash_afu_reset(व्योम *ctx_cookie)
अणु
	काष्ठा ocxlflash_context *ctx = ctx_cookie;
	काष्ठा device *dev = ctx->hw_afu->dev;

	/* Pending implementation from OCXL transport services */
	dev_err_once(dev, "%s: afu_reset() fop not supported\n", __func__);

	/* Silently वापस success until it is implemented */
	वापस 0;
पूर्ण

/**
 * ocxlflash_set_master() - sets the context as master
 * @ctx_cookie:	Adapter context to set as master.
 */
अटल व्योम ocxlflash_set_master(व्योम *ctx_cookie)
अणु
	काष्ठा ocxlflash_context *ctx = ctx_cookie;

	ctx->master = true;
पूर्ण

/**
 * ocxlflash_get_context() - obtains the context associated with the host
 * @pdev:	PCI device associated with the host.
 * @afu_cookie:	Hardware AFU associated with the host.
 *
 * Return: वापसs the poपूर्णांकer to host adapter context
 */
अटल व्योम *ocxlflash_get_context(काष्ठा pci_dev *pdev, व्योम *afu_cookie)
अणु
	काष्ठा ocxl_hw_afu *afu = afu_cookie;

	वापस afu->ocxl_ctx;
पूर्ण

/**
 * ocxlflash_dev_context_init() - allocate and initialize an adapter context
 * @pdev:	PCI device associated with the host.
 * @afu_cookie:	Hardware AFU associated with the host.
 *
 * Return: वापसs the adapter context on success, ERR_PTR on failure
 */
अटल व्योम *ocxlflash_dev_context_init(काष्ठा pci_dev *pdev, व्योम *afu_cookie)
अणु
	काष्ठा ocxl_hw_afu *afu = afu_cookie;
	काष्ठा device *dev = afu->dev;
	काष्ठा ocxlflash_context *ctx;
	पूर्णांक rc;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (unlikely(!ctx)) अणु
		dev_err(dev, "%s: Context allocation failed\n", __func__);
		rc = -ENOMEM;
		जाओ err1;
	पूर्ण

	idr_preload(GFP_KERNEL);
	rc = idr_alloc(&afu->idr, ctx, 0, afu->max_pasid, GFP_NOWAIT);
	idr_preload_end();
	अगर (unlikely(rc < 0)) अणु
		dev_err(dev, "%s: idr_alloc failed rc=%d\n", __func__, rc);
		जाओ err2;
	पूर्ण

	spin_lock_init(&ctx->slock);
	init_रुकोqueue_head(&ctx->wq);
	mutex_init(&ctx->state_mutex);

	ctx->state = OPENED;
	ctx->pe = rc;
	ctx->master = false;
	ctx->mapping = शून्य;
	ctx->hw_afu = afu;
	ctx->irq_biपंचांगap = 0;
	ctx->pending_irq = false;
	ctx->pending_fault = false;
out:
	वापस ctx;
err2:
	kमुक्त(ctx);
err1:
	ctx = ERR_PTR(rc);
	जाओ out;
पूर्ण

/**
 * ocxlflash_release_context() - releases an adapter context
 * @ctx_cookie:	Adapter context to be released.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक ocxlflash_release_context(व्योम *ctx_cookie)
अणु
	काष्ठा ocxlflash_context *ctx = ctx_cookie;
	काष्ठा device *dev;
	पूर्णांक rc = 0;

	अगर (!ctx)
		जाओ out;

	dev = ctx->hw_afu->dev;
	mutex_lock(&ctx->state_mutex);
	अगर (ctx->state >= STARTED) अणु
		dev_err(dev, "%s: Context in use, state=%d\n", __func__,
			ctx->state);
		mutex_unlock(&ctx->state_mutex);
		rc = -EBUSY;
		जाओ out;
	पूर्ण
	mutex_unlock(&ctx->state_mutex);

	idr_हटाओ(&ctx->hw_afu->idr, ctx->pe);
	ocxlflash_release_mapping(ctx);
	kमुक्त(ctx);
out:
	वापस rc;
पूर्ण

/**
 * ocxlflash_perst_reloads_same_image() - sets the image reload policy
 * @afu_cookie:	Hardware AFU associated with the host.
 * @image:	Whether to load the same image on PERST.
 */
अटल व्योम ocxlflash_perst_reloads_same_image(व्योम *afu_cookie, bool image)
अणु
	काष्ठा ocxl_hw_afu *afu = afu_cookie;

	afu->perst_same_image = image;
पूर्ण

/**
 * ocxlflash_पढ़ो_adapter_vpd() - पढ़ोs the adapter VPD
 * @pdev:	PCI device associated with the host.
 * @buf:	Buffer to get the VPD data.
 * @count:	Size of buffer (maximum bytes that can be पढ़ो).
 *
 * Return: size of VPD on success, -त्रुटि_सं on failure
 */
अटल sमाप_प्रकार ocxlflash_पढ़ो_adapter_vpd(काष्ठा pci_dev *pdev, व्योम *buf,
					  माप_प्रकार count)
अणु
	वापस pci_पढ़ो_vpd(pdev, 0, count, buf);
पूर्ण

/**
 * मुक्त_afu_irqs() - पूर्णांकernal service to मुक्त पूर्णांकerrupts
 * @ctx:	Adapter context.
 */
अटल व्योम मुक्त_afu_irqs(काष्ठा ocxlflash_context *ctx)
अणु
	काष्ठा ocxl_hw_afu *afu = ctx->hw_afu;
	काष्ठा device *dev = afu->dev;
	पूर्णांक i;

	अगर (!ctx->irqs) अणु
		dev_err(dev, "%s: Interrupts not allocated\n", __func__);
		वापस;
	पूर्ण

	क्रम (i = ctx->num_irqs; i >= 0; i--)
		ocxl_link_मुक्त_irq(afu->link_token, ctx->irqs[i].hwirq);

	kमुक्त(ctx->irqs);
	ctx->irqs = शून्य;
पूर्ण

/**
 * alloc_afu_irqs() - पूर्णांकernal service to allocate पूर्णांकerrupts
 * @ctx:	Context associated with the request.
 * @num:	Number of पूर्णांकerrupts requested.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक alloc_afu_irqs(काष्ठा ocxlflash_context *ctx, पूर्णांक num)
अणु
	काष्ठा ocxl_hw_afu *afu = ctx->hw_afu;
	काष्ठा device *dev = afu->dev;
	काष्ठा ocxlflash_irqs *irqs;
	पूर्णांक rc = 0;
	पूर्णांक hwirq;
	पूर्णांक i;

	अगर (ctx->irqs) अणु
		dev_err(dev, "%s: Interrupts already allocated\n", __func__);
		rc = -EEXIST;
		जाओ out;
	पूर्ण

	अगर (num > OCXL_MAX_IRQS) अणु
		dev_err(dev, "%s: Too many interrupts num=%d\n", __func__, num);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	irqs = kसुस्मृति(num, माप(*irqs), GFP_KERNEL);
	अगर (unlikely(!irqs)) अणु
		dev_err(dev, "%s: Context irqs allocation failed\n", __func__);
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < num; i++) अणु
		rc = ocxl_link_irq_alloc(afu->link_token, &hwirq);
		अगर (unlikely(rc)) अणु
			dev_err(dev, "%s: ocxl_link_irq_alloc failed rc=%d\n",
				__func__, rc);
			जाओ err;
		पूर्ण

		irqs[i].hwirq = hwirq;
	पूर्ण

	ctx->irqs = irqs;
	ctx->num_irqs = num;
out:
	वापस rc;
err:
	क्रम (i = i-1; i >= 0; i--)
		ocxl_link_मुक्त_irq(afu->link_token, irqs[i].hwirq);
	kमुक्त(irqs);
	जाओ out;
पूर्ण

/**
 * ocxlflash_allocate_afu_irqs() - allocates the requested number of पूर्णांकerrupts
 * @ctx_cookie:	Context associated with the request.
 * @num:	Number of पूर्णांकerrupts requested.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक ocxlflash_allocate_afu_irqs(व्योम *ctx_cookie, पूर्णांक num)
अणु
	वापस alloc_afu_irqs(ctx_cookie, num);
पूर्ण

/**
 * ocxlflash_मुक्त_afu_irqs() - मुक्तs the पूर्णांकerrupts of an adapter context
 * @ctx_cookie:	Adapter context.
 */
अटल व्योम ocxlflash_मुक्त_afu_irqs(व्योम *ctx_cookie)
अणु
	मुक्त_afu_irqs(ctx_cookie);
पूर्ण

/**
 * ocxlflash_unconfig_afu() - unconfigure the AFU
 * @afu: AFU associated with the host.
 */
अटल व्योम ocxlflash_unconfig_afu(काष्ठा ocxl_hw_afu *afu)
अणु
	अगर (afu->gmmio_virt) अणु
		iounmap(afu->gmmio_virt);
		afu->gmmio_virt = शून्य;
	पूर्ण
पूर्ण

/**
 * ocxlflash_destroy_afu() - destroy the AFU काष्ठाure
 * @afu_cookie:	AFU to be मुक्तd.
 */
अटल व्योम ocxlflash_destroy_afu(व्योम *afu_cookie)
अणु
	काष्ठा ocxl_hw_afu *afu = afu_cookie;
	पूर्णांक pos;

	अगर (!afu)
		वापस;

	ocxlflash_release_context(afu->ocxl_ctx);
	idr_destroy(&afu->idr);

	/* Disable the AFU */
	pos = afu->acfg.dvsec_afu_control_pos;
	ocxl_config_set_afu_state(afu->pdev, pos, 0);

	ocxlflash_unconfig_afu(afu);
	kमुक्त(afu);
पूर्ण

/**
 * ocxlflash_config_fn() - configure the host function
 * @pdev:	PCI device associated with the host.
 * @afu:	AFU associated with the host.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक ocxlflash_config_fn(काष्ठा pci_dev *pdev, काष्ठा ocxl_hw_afu *afu)
अणु
	काष्ठा ocxl_fn_config *fcfg = &afu->fcfg;
	काष्ठा device *dev = &pdev->dev;
	u16 base, enabled, supported;
	पूर्णांक rc = 0;

	/* Read DVSEC config of the function */
	rc = ocxl_config_पढ़ो_function(pdev, fcfg);
	अगर (unlikely(rc)) अणु
		dev_err(dev, "%s: ocxl_config_read_function failed rc=%d\n",
			__func__, rc);
		जाओ out;
	पूर्ण

	/* Check अगर function has AFUs defined, only 1 per function supported */
	अगर (fcfg->max_afu_index >= 0) अणु
		afu->is_present = true;
		अगर (fcfg->max_afu_index != 0)
			dev_warn(dev, "%s: Unexpected AFU index value %d\n",
				 __func__, fcfg->max_afu_index);
	पूर्ण

	rc = ocxl_config_get_actag_info(pdev, &base, &enabled, &supported);
	अगर (unlikely(rc)) अणु
		dev_err(dev, "%s: ocxl_config_get_actag_info failed rc=%d\n",
			__func__, rc);
		जाओ out;
	पूर्ण

	afu->fn_actag_base = base;
	afu->fn_actag_enabled = enabled;

	ocxl_config_set_actag(pdev, fcfg->dvsec_function_pos, base, enabled);
	dev_dbg(dev, "%s: Function acTag range base=%u enabled=%u\n",
		__func__, base, enabled);

	rc = ocxl_link_setup(pdev, 0, &afu->link_token);
	अगर (unlikely(rc)) अणु
		dev_err(dev, "%s: ocxl_link_setup failed rc=%d\n",
			__func__, rc);
		जाओ out;
	पूर्ण

	rc = ocxl_config_set_TL(pdev, fcfg->dvsec_tl_pos);
	अगर (unlikely(rc)) अणु
		dev_err(dev, "%s: ocxl_config_set_TL failed rc=%d\n",
			__func__, rc);
		जाओ err;
	पूर्ण
out:
	वापस rc;
err:
	ocxl_link_release(pdev, afu->link_token);
	जाओ out;
पूर्ण

/**
 * ocxlflash_unconfig_fn() - unconfigure the host function
 * @pdev:	PCI device associated with the host.
 * @afu:	AFU associated with the host.
 */
अटल व्योम ocxlflash_unconfig_fn(काष्ठा pci_dev *pdev, काष्ठा ocxl_hw_afu *afu)
अणु
	ocxl_link_release(pdev, afu->link_token);
पूर्ण

/**
 * ocxlflash_map_mmio() - map the AFU MMIO space
 * @afu: AFU associated with the host.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक ocxlflash_map_mmio(काष्ठा ocxl_hw_afu *afu)
अणु
	काष्ठा ocxl_afu_config *acfg = &afu->acfg;
	काष्ठा pci_dev *pdev = afu->pdev;
	काष्ठा device *dev = afu->dev;
	phys_addr_t gmmio, ppmmio;
	पूर्णांक rc = 0;

	rc = pci_request_region(pdev, acfg->global_mmio_bar, "ocxlflash");
	अगर (unlikely(rc)) अणु
		dev_err(dev, "%s: pci_request_region for global failed rc=%d\n",
			__func__, rc);
		जाओ out;
	पूर्ण
	gmmio = pci_resource_start(pdev, acfg->global_mmio_bar);
	gmmio += acfg->global_mmio_offset;

	rc = pci_request_region(pdev, acfg->pp_mmio_bar, "ocxlflash");
	अगर (unlikely(rc)) अणु
		dev_err(dev, "%s: pci_request_region for pp bar failed rc=%d\n",
			__func__, rc);
		जाओ err1;
	पूर्ण
	ppmmio = pci_resource_start(pdev, acfg->pp_mmio_bar);
	ppmmio += acfg->pp_mmio_offset;

	afu->gmmio_virt = ioremap(gmmio, acfg->global_mmio_size);
	अगर (unlikely(!afu->gmmio_virt)) अणु
		dev_err(dev, "%s: MMIO mapping failed\n", __func__);
		rc = -ENOMEM;
		जाओ err2;
	पूर्ण

	afu->gmmio_phys = gmmio;
	afu->ppmmio_phys = ppmmio;
out:
	वापस rc;
err2:
	pci_release_region(pdev, acfg->pp_mmio_bar);
err1:
	pci_release_region(pdev, acfg->global_mmio_bar);
	जाओ out;
पूर्ण

/**
 * ocxlflash_config_afu() - configure the host AFU
 * @pdev:	PCI device associated with the host.
 * @afu:	AFU associated with the host.
 *
 * Must be called _after_ host function configuration.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक ocxlflash_config_afu(काष्ठा pci_dev *pdev, काष्ठा ocxl_hw_afu *afu)
अणु
	काष्ठा ocxl_afu_config *acfg = &afu->acfg;
	काष्ठा ocxl_fn_config *fcfg = &afu->fcfg;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक count;
	पूर्णांक base;
	पूर्णांक pos;
	पूर्णांक rc = 0;

	/* This HW AFU function करोes not have any AFUs defined */
	अगर (!afu->is_present)
		जाओ out;

	/* Read AFU config at index 0 */
	rc = ocxl_config_पढ़ो_afu(pdev, fcfg, acfg, 0);
	अगर (unlikely(rc)) अणु
		dev_err(dev, "%s: ocxl_config_read_afu failed rc=%d\n",
			__func__, rc);
		जाओ out;
	पूर्ण

	/* Only one AFU per function is supported, so actag_base is same */
	base = afu->fn_actag_base;
	count = min_t(पूर्णांक, acfg->actag_supported, afu->fn_actag_enabled);
	pos = acfg->dvsec_afu_control_pos;

	ocxl_config_set_afu_actag(pdev, pos, base, count);
	dev_dbg(dev, "%s: acTag base=%d enabled=%d\n", __func__, base, count);
	afu->afu_actag_base = base;
	afu->afu_actag_enabled = count;
	afu->max_pasid = 1 << acfg->pasid_supported_log;

	ocxl_config_set_afu_pasid(pdev, pos, 0, acfg->pasid_supported_log);

	rc = ocxlflash_map_mmio(afu);
	अगर (unlikely(rc)) अणु
		dev_err(dev, "%s: ocxlflash_map_mmio failed rc=%d\n",
			__func__, rc);
		जाओ out;
	पूर्ण

	/* Enable the AFU */
	ocxl_config_set_afu_state(pdev, acfg->dvsec_afu_control_pos, 1);
out:
	वापस rc;
पूर्ण

/**
 * ocxlflash_create_afu() - create the AFU क्रम OCXL
 * @pdev:	PCI device associated with the host.
 *
 * Return: AFU on success, शून्य on failure
 */
अटल व्योम *ocxlflash_create_afu(काष्ठा pci_dev *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ocxlflash_context *ctx;
	काष्ठा ocxl_hw_afu *afu;
	पूर्णांक rc;

	afu = kzalloc(माप(*afu), GFP_KERNEL);
	अगर (unlikely(!afu)) अणु
		dev_err(dev, "%s: HW AFU allocation failed\n", __func__);
		जाओ out;
	पूर्ण

	afu->pdev = pdev;
	afu->dev = dev;
	idr_init(&afu->idr);

	rc = ocxlflash_config_fn(pdev, afu);
	अगर (unlikely(rc)) अणु
		dev_err(dev, "%s: Function configuration failed rc=%d\n",
			__func__, rc);
		जाओ err1;
	पूर्ण

	rc = ocxlflash_config_afu(pdev, afu);
	अगर (unlikely(rc)) अणु
		dev_err(dev, "%s: AFU configuration failed rc=%d\n",
			__func__, rc);
		जाओ err2;
	पूर्ण

	ctx = ocxlflash_dev_context_init(pdev, afu);
	अगर (IS_ERR(ctx)) अणु
		rc = PTR_ERR(ctx);
		dev_err(dev, "%s: ocxlflash_dev_context_init failed rc=%d\n",
			__func__, rc);
		जाओ err3;
	पूर्ण

	afu->ocxl_ctx = ctx;
out:
	वापस afu;
err3:
	ocxlflash_unconfig_afu(afu);
err2:
	ocxlflash_unconfig_fn(pdev, afu);
err1:
	idr_destroy(&afu->idr);
	kमुक्त(afu);
	afu = शून्य;
	जाओ out;
पूर्ण

/**
 * ctx_event_pending() - check क्रम any event pending on the context
 * @ctx:	Context to be checked.
 *
 * Return: true अगर there is an event pending, false अगर none pending
 */
अटल अंतरभूत bool ctx_event_pending(काष्ठा ocxlflash_context *ctx)
अणु
	अगर (ctx->pending_irq || ctx->pending_fault)
		वापस true;

	वापस false;
पूर्ण

/**
 * afu_poll() - poll the AFU क्रम events on the context
 * @file:	File associated with the adapter context.
 * @poll:	Poll काष्ठाure from the user.
 *
 * Return: poll mask
 */
अटल अचिन्हित पूर्णांक afu_poll(काष्ठा file *file, काष्ठा poll_table_काष्ठा *poll)
अणु
	काष्ठा ocxlflash_context *ctx = file->निजी_data;
	काष्ठा device *dev = ctx->hw_afu->dev;
	uदीर्घ lock_flags;
	पूर्णांक mask = 0;

	poll_रुको(file, &ctx->wq, poll);

	spin_lock_irqsave(&ctx->slock, lock_flags);
	अगर (ctx_event_pending(ctx))
		mask |= POLLIN | POLLRDNORM;
	अन्यथा अगर (ctx->state == CLOSED)
		mask |= POLLERR;
	spin_unlock_irqrestore(&ctx->slock, lock_flags);

	dev_dbg(dev, "%s: Poll wait completed for pe %i mask %i\n",
		__func__, ctx->pe, mask);

	वापस mask;
पूर्ण

/**
 * afu_पढ़ो() - perक्रमm a पढ़ो on the context क्रम any event
 * @file:	File associated with the adapter context.
 * @buf:	Buffer to receive the data.
 * @count:	Size of buffer (maximum bytes that can be पढ़ो).
 * @off:	Offset.
 *
 * Return: size of the data पढ़ो on success, -त्रुटि_सं on failure
 */
अटल sमाप_प्रकार afu_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
			loff_t *off)
अणु
	काष्ठा ocxlflash_context *ctx = file->निजी_data;
	काष्ठा device *dev = ctx->hw_afu->dev;
	काष्ठा cxl_event event;
	uदीर्घ lock_flags;
	sमाप_प्रकार esize;
	sमाप_प्रकार rc;
	पूर्णांक bit;
	DEFINE_WAIT(event_रुको);

	अगर (*off != 0) अणु
		dev_err(dev, "%s: Non-zero offset not supported, off=%lld\n",
			__func__, *off);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	spin_lock_irqsave(&ctx->slock, lock_flags);

	क्रम (;;) अणु
		prepare_to_रुको(&ctx->wq, &event_रुको, TASK_INTERRUPTIBLE);

		अगर (ctx_event_pending(ctx) || (ctx->state == CLOSED))
			अवरोध;

		अगर (file->f_flags & O_NONBLOCK) अणु
			dev_err(dev, "%s: File cannot be blocked on I/O\n",
				__func__);
			rc = -EAGAIN;
			जाओ err;
		पूर्ण

		अगर (संकेत_pending(current)) अणु
			dev_err(dev, "%s: Signal pending on the process\n",
				__func__);
			rc = -ERESTARTSYS;
			जाओ err;
		पूर्ण

		spin_unlock_irqrestore(&ctx->slock, lock_flags);
		schedule();
		spin_lock_irqsave(&ctx->slock, lock_flags);
	पूर्ण

	finish_रुको(&ctx->wq, &event_रुको);

	स_रखो(&event, 0, माप(event));
	event.header.process_element = ctx->pe;
	event.header.size = माप(काष्ठा cxl_event_header);
	अगर (ctx->pending_irq) अणु
		esize = माप(काष्ठा cxl_event_afu_पूर्णांकerrupt);
		event.header.size += esize;
		event.header.type = CXL_EVENT_AFU_INTERRUPT;

		bit = find_first_bit(&ctx->irq_biपंचांगap, ctx->num_irqs);
		clear_bit(bit, &ctx->irq_biपंचांगap);
		event.irq.irq = bit + 1;
		अगर (biपंचांगap_empty(&ctx->irq_biपंचांगap, ctx->num_irqs))
			ctx->pending_irq = false;
	पूर्ण अन्यथा अगर (ctx->pending_fault) अणु
		event.header.size += माप(काष्ठा cxl_event_data_storage);
		event.header.type = CXL_EVENT_DATA_STORAGE;
		event.fault.addr = ctx->fault_addr;
		event.fault.dsisr = ctx->fault_dsisr;
		ctx->pending_fault = false;
	पूर्ण

	spin_unlock_irqrestore(&ctx->slock, lock_flags);

	अगर (copy_to_user(buf, &event, event.header.size)) अणु
		dev_err(dev, "%s: copy_to_user failed\n", __func__);
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	rc = event.header.size;
out:
	वापस rc;
err:
	finish_रुको(&ctx->wq, &event_रुको);
	spin_unlock_irqrestore(&ctx->slock, lock_flags);
	जाओ out;
पूर्ण

/**
 * afu_release() - release and मुक्त the context
 * @inode:	File inode poपूर्णांकer.
 * @file:	File associated with the context.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक afu_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ocxlflash_context *ctx = file->निजी_data;
	पूर्णांक i;

	/* Unmap and मुक्त the पूर्णांकerrupts associated with the context */
	क्रम (i = ctx->num_irqs; i >= 0; i--)
		afu_unmap_irq(0, ctx, i, ctx);
	मुक्त_afu_irqs(ctx);

	वापस ocxlflash_release_context(ctx);
पूर्ण

/**
 * ocxlflash_mmap_fault() - mmap fault handler
 * @vmf:	VM fault associated with current fault.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल vm_fault_t ocxlflash_mmap_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा ocxlflash_context *ctx = vma->vm_file->निजी_data;
	काष्ठा device *dev = ctx->hw_afu->dev;
	u64 mmio_area, offset;

	offset = vmf->pgoff << PAGE_SHIFT;
	अगर (offset >= ctx->psn_size)
		वापस VM_FAULT_SIGBUS;

	mutex_lock(&ctx->state_mutex);
	अगर (ctx->state != STARTED) अणु
		dev_err(dev, "%s: Context not started, state=%d\n",
			__func__, ctx->state);
		mutex_unlock(&ctx->state_mutex);
		वापस VM_FAULT_SIGBUS;
	पूर्ण
	mutex_unlock(&ctx->state_mutex);

	mmio_area = ctx->psn_phys;
	mmio_area += offset;

	वापस vmf_insert_pfn(vma, vmf->address, mmio_area >> PAGE_SHIFT);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा ocxlflash_vmops = अणु
	.fault = ocxlflash_mmap_fault,
पूर्ण;

/**
 * afu_mmap() - map the fault handler operations
 * @file:	File associated with the context.
 * @vma:	VM area associated with mapping.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक afu_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा ocxlflash_context *ctx = file->निजी_data;

	अगर ((vma_pages(vma) + vma->vm_pgoff) >
	    (ctx->psn_size >> PAGE_SHIFT))
		वापस -EINVAL;

	vma->vm_flags |= VM_IO | VM_PFNMAP;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	vma->vm_ops = &ocxlflash_vmops;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations ocxl_afu_fops = अणु
	.owner		= THIS_MODULE,
	.poll		= afu_poll,
	.पढ़ो		= afu_पढ़ो,
	.release	= afu_release,
	.mmap		= afu_mmap,
पूर्ण;

#घोषणा PATCH_FOPS(NAME)						\
	करो अणु अगर (!fops->NAME) fops->NAME = ocxl_afu_fops.NAME; पूर्ण जबतक (0)

/**
 * ocxlflash_get_fd() - get file descriptor क्रम an adapter context
 * @ctx_cookie:	Adapter context.
 * @fops:	File operations to be associated.
 * @fd:		File descriptor to be वापसed back.
 *
 * Return: poपूर्णांकer to the file on success, ERR_PTR on failure
 */
अटल काष्ठा file *ocxlflash_get_fd(व्योम *ctx_cookie,
				     काष्ठा file_operations *fops, पूर्णांक *fd)
अणु
	काष्ठा ocxlflash_context *ctx = ctx_cookie;
	काष्ठा device *dev = ctx->hw_afu->dev;
	काष्ठा file *file;
	पूर्णांक flags, fdपंचांगp;
	पूर्णांक rc = 0;
	अक्षर *name = शून्य;

	/* Only allow one fd per context */
	अगर (ctx->mapping) अणु
		dev_err(dev, "%s: Context is already mapped to an fd\n",
			__func__);
		rc = -EEXIST;
		जाओ err1;
	पूर्ण

	flags = O_RDWR | O_CLOEXEC;

	/* This code is similar to anon_inode_getfd() */
	rc = get_unused_fd_flags(flags);
	अगर (unlikely(rc < 0)) अणु
		dev_err(dev, "%s: get_unused_fd_flags failed rc=%d\n",
			__func__, rc);
		जाओ err1;
	पूर्ण
	fdपंचांगp = rc;

	/* Patch the file ops that are not defined */
	अगर (fops) अणु
		PATCH_FOPS(poll);
		PATCH_FOPS(पढ़ो);
		PATCH_FOPS(release);
		PATCH_FOPS(mmap);
	पूर्ण अन्यथा /* Use शेष ops */
		fops = (काष्ठा file_operations *)&ocxl_afu_fops;

	name = kaप्र_लिखो(GFP_KERNEL, "ocxlflash:%d", ctx->pe);
	file = ocxlflash_getfile(dev, name, fops, ctx, flags);
	kमुक्त(name);
	अगर (IS_ERR(file)) अणु
		rc = PTR_ERR(file);
		dev_err(dev, "%s: ocxlflash_getfile failed rc=%d\n",
			__func__, rc);
		जाओ err2;
	पूर्ण

	ctx->mapping = file->f_mapping;
	*fd = fdपंचांगp;
out:
	वापस file;
err2:
	put_unused_fd(fdपंचांगp);
err1:
	file = ERR_PTR(rc);
	जाओ out;
पूर्ण

/**
 * ocxlflash_fops_get_context() - get the context associated with the file
 * @file:	File associated with the adapter context.
 *
 * Return: poपूर्णांकer to the context
 */
अटल व्योम *ocxlflash_fops_get_context(काष्ठा file *file)
अणु
	वापस file->निजी_data;
पूर्ण

/**
 * ocxlflash_afu_irq() - पूर्णांकerrupt handler क्रम user contexts
 * @irq:	Interrupt number.
 * @data:	Private data provided at पूर्णांकerrupt registration, the context.
 *
 * Return: Always वापस IRQ_HANDLED.
 */
अटल irqवापस_t ocxlflash_afu_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ocxlflash_context *ctx = data;
	काष्ठा device *dev = ctx->hw_afu->dev;
	पूर्णांक i;

	dev_dbg(dev, "%s: Interrupt raised for pe %i virq %i\n",
		__func__, ctx->pe, irq);

	क्रम (i = 0; i < ctx->num_irqs; i++) अणु
		अगर (ctx->irqs[i].virq == irq)
			अवरोध;
	पूर्ण
	अगर (unlikely(i >= ctx->num_irqs)) अणु
		dev_err(dev, "%s: Received AFU IRQ out of range\n", __func__);
		जाओ out;
	पूर्ण

	spin_lock(&ctx->slock);
	set_bit(i - 1, &ctx->irq_biपंचांगap);
	ctx->pending_irq = true;
	spin_unlock(&ctx->slock);

	wake_up_all(&ctx->wq);
out:
	वापस IRQ_HANDLED;
पूर्ण

/**
 * ocxlflash_start_work() - start a user context
 * @ctx_cookie:	Context to be started.
 * @num_irqs:	Number of पूर्णांकerrupts requested.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक ocxlflash_start_work(व्योम *ctx_cookie, u64 num_irqs)
अणु
	काष्ठा ocxlflash_context *ctx = ctx_cookie;
	काष्ठा ocxl_hw_afu *afu = ctx->hw_afu;
	काष्ठा device *dev = afu->dev;
	अक्षर *name;
	पूर्णांक rc = 0;
	पूर्णांक i;

	rc = alloc_afu_irqs(ctx, num_irqs);
	अगर (unlikely(rc < 0)) अणु
		dev_err(dev, "%s: alloc_afu_irqs failed rc=%d\n", __func__, rc);
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < num_irqs; i++) अणु
		name = kaप्र_लिखो(GFP_KERNEL, "ocxlflash-%s-pe%i-%i",
				 dev_name(dev), ctx->pe, i);
		rc = afu_map_irq(0, ctx, i, ocxlflash_afu_irq, ctx, name);
		kमुक्त(name);
		अगर (unlikely(rc < 0)) अणु
			dev_err(dev, "%s: afu_map_irq failed rc=%d\n",
				__func__, rc);
			जाओ err;
		पूर्ण
	पूर्ण

	rc = start_context(ctx);
	अगर (unlikely(rc)) अणु
		dev_err(dev, "%s: start_context failed rc=%d\n", __func__, rc);
		जाओ err;
	पूर्ण
out:
	वापस rc;
err:
	क्रम (i = i-1; i >= 0; i--)
		afu_unmap_irq(0, ctx, i, ctx);
	मुक्त_afu_irqs(ctx);
	जाओ out;
पूर्ण;

/**
 * ocxlflash_fd_mmap() - mmap handler क्रम adapter file descriptor
 * @file:	File installed with adapter file descriptor.
 * @vma:	VM area associated with mapping.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक ocxlflash_fd_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस afu_mmap(file, vma);
पूर्ण

/**
 * ocxlflash_fd_release() - release the context associated with the file
 * @inode:	File inode poपूर्णांकer.
 * @file:	File associated with the adapter context.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक ocxlflash_fd_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस afu_release(inode, file);
पूर्ण

/* Backend ops to ocxlflash services */
स्थिर काष्ठा cxlflash_backend_ops cxlflash_ocxl_ops = अणु
	.module			= THIS_MODULE,
	.psa_map		= ocxlflash_psa_map,
	.psa_unmap		= ocxlflash_psa_unmap,
	.process_element	= ocxlflash_process_element,
	.map_afu_irq		= ocxlflash_map_afu_irq,
	.unmap_afu_irq		= ocxlflash_unmap_afu_irq,
	.get_irq_objhndl	= ocxlflash_get_irq_objhndl,
	.start_context		= ocxlflash_start_context,
	.stop_context		= ocxlflash_stop_context,
	.afu_reset		= ocxlflash_afu_reset,
	.set_master		= ocxlflash_set_master,
	.get_context		= ocxlflash_get_context,
	.dev_context_init	= ocxlflash_dev_context_init,
	.release_context	= ocxlflash_release_context,
	.perst_reloads_same_image = ocxlflash_perst_reloads_same_image,
	.पढ़ो_adapter_vpd	= ocxlflash_पढ़ो_adapter_vpd,
	.allocate_afu_irqs	= ocxlflash_allocate_afu_irqs,
	.मुक्त_afu_irqs		= ocxlflash_मुक्त_afu_irqs,
	.create_afu		= ocxlflash_create_afu,
	.destroy_afu		= ocxlflash_destroy_afu,
	.get_fd			= ocxlflash_get_fd,
	.fops_get_context	= ocxlflash_fops_get_context,
	.start_work		= ocxlflash_start_work,
	.fd_mmap		= ocxlflash_fd_mmap,
	.fd_release		= ocxlflash_fd_release,
पूर्ण;
