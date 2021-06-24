<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2014 IBM Corp.
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/mm.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/idr.h>
#समावेश <linux/pci.h>
#समावेश <linux/sched/task.h>

#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/mmu.h>
#समावेश <misc/cxl-base.h>

#समावेश "cxl.h"
#समावेश "trace.h"

अटल DEFINE_SPINLOCK(adapter_idr_lock);
अटल DEFINE_IDR(cxl_adapter_idr);

uपूर्णांक cxl_verbose;
module_param_named(verbose, cxl_verbose, uपूर्णांक, 0600);
MODULE_PARM_DESC(verbose, "Enable verbose dmesg output");

स्थिर काष्ठा cxl_backend_ops *cxl_ops;

पूर्णांक cxl_afu_slbia(काष्ठा cxl_afu *afu)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + (HZ * CXL_TIMEOUT);

	pr_devel("cxl_afu_slbia issuing SLBIA command\n");
	cxl_p2n_ग_लिखो(afu, CXL_SLBIA_An, CXL_TLB_SLB_IQ_ALL);
	जबतक (cxl_p2n_पढ़ो(afu, CXL_SLBIA_An) & CXL_TLB_SLB_P) अणु
		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			dev_warn(&afu->dev, "WARNING: CXL AFU SLBIA timed out!\n");
			वापस -EBUSY;
		पूर्ण
		/* If the adapter has gone करोwn, we can assume that we
		 * will PERST it and that will invalidate everything.
		 */
		अगर (!cxl_ops->link_ok(afu->adapter, afu))
			वापस -EIO;
		cpu_relax();
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम _cxl_slbia(काष्ठा cxl_context *ctx, काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ flags;

	अगर (ctx->mm != mm)
		वापस;

	pr_devel("%s matched mm - card: %i afu: %i pe: %i\n", __func__,
		 ctx->afu->adapter->adapter_num, ctx->afu->slice, ctx->pe);

	spin_lock_irqsave(&ctx->sste_lock, flags);
	trace_cxl_slbia(ctx);
	स_रखो(ctx->sstp, 0, ctx->sst_size);
	spin_unlock_irqrestore(&ctx->sste_lock, flags);
	mb();
	cxl_afu_slbia(ctx->afu);
पूर्ण

अटल अंतरभूत व्योम cxl_slbia_core(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा cxl *adapter;
	काष्ठा cxl_afu *afu;
	काष्ठा cxl_context *ctx;
	पूर्णांक card, slice, id;

	pr_devel("%s called\n", __func__);

	spin_lock(&adapter_idr_lock);
	idr_क्रम_each_entry(&cxl_adapter_idr, adapter, card) अणु
		/* XXX: Make this lookup faster with link from mm to ctx */
		spin_lock(&adapter->afu_list_lock);
		क्रम (slice = 0; slice < adapter->slices; slice++) अणु
			afu = adapter->afu[slice];
			अगर (!afu || !afu->enabled)
				जारी;
			rcu_पढ़ो_lock();
			idr_क्रम_each_entry(&afu->contexts_idr, ctx, id)
				_cxl_slbia(ctx, mm);
			rcu_पढ़ो_unlock();
		पूर्ण
		spin_unlock(&adapter->afu_list_lock);
	पूर्ण
	spin_unlock(&adapter_idr_lock);
पूर्ण

अटल काष्ठा cxl_calls cxl_calls = अणु
	.cxl_slbia = cxl_slbia_core,
	.owner = THIS_MODULE,
पूर्ण;

पूर्णांक cxl_alloc_sst(काष्ठा cxl_context *ctx)
अणु
	अचिन्हित दीर्घ vsid;
	u64 ea_mask, size, sstp0, sstp1;

	sstp0 = 0;
	sstp1 = 0;

	ctx->sst_size = PAGE_SIZE;
	ctx->sst_lru = 0;
	ctx->sstp = (काष्ठा cxl_sste *)get_zeroed_page(GFP_KERNEL);
	अगर (!ctx->sstp) अणु
		pr_err("cxl_alloc_sst: Unable to allocate segment table\n");
		वापस -ENOMEM;
	पूर्ण
	pr_devel("SSTP allocated at 0x%p\n", ctx->sstp);

	vsid  = get_kernel_vsid((u64)ctx->sstp, mmu_kernel_ssize) << 12;

	sstp0 |= (u64)mmu_kernel_ssize << CXL_SSTP0_An_B_SHIFT;
	sstp0 |= (SLB_VSID_KERNEL | mmu_psize_defs[mmu_linear_psize].sllp) << 50;

	size = (((u64)ctx->sst_size >> 8) - 1) << CXL_SSTP0_An_SegTableSize_SHIFT;
	अगर (unlikely(size & ~CXL_SSTP0_An_SegTableSize_MASK)) अणु
		WARN(1, "Impossible segment table size\n");
		वापस -EINVAL;
	पूर्ण
	sstp0 |= size;

	अगर (mmu_kernel_ssize == MMU_SEGSIZE_256M)
		ea_mask = 0xfffff00ULL;
	अन्यथा
		ea_mask = 0xffffffff00ULL;

	sstp0 |=  vsid >>     (50-14);  /*   Top 14 bits of VSID */
	sstp1 |= (vsid << (64-(50-14))) & ~ea_mask;
	sstp1 |= (u64)ctx->sstp & ea_mask;
	sstp1 |= CXL_SSTP1_An_V;

	pr_devel("Looked up %#llx: slbfee. %#llx (ssize: %x, vsid: %#lx), copied to SSTP0: %#llx, SSTP1: %#llx\n",
			(u64)ctx->sstp, (u64)ctx->sstp & ESID_MASK, mmu_kernel_ssize, vsid, sstp0, sstp1);

	/* Store calculated sstp hardware poपूर्णांकs क्रम use later */
	ctx->sstp0 = sstp0;
	ctx->sstp1 = sstp1;

	वापस 0;
पूर्ण

/* prपूर्णांक buffer content as पूर्णांकegers when debugging */
व्योम cxl_dump_debug_buffer(व्योम *buf, माप_प्रकार buf_len)
अणु
#अगर_घोषित DEBUG
	पूर्णांक i, *ptr;

	/*
	 * We want to regroup up to 4 पूर्णांकegers per line, which means they
	 * need to be in the same pr_devel() statement
	 */
	ptr = (पूर्णांक *) buf;
	क्रम (i = 0; i * 4 < buf_len; i += 4) अणु
		अगर ((i + 3) * 4 < buf_len)
			pr_devel("%.8x %.8x %.8x %.8x\n", ptr[i], ptr[i + 1],
				ptr[i + 2], ptr[i + 3]);
		अन्यथा अगर ((i + 2) * 4 < buf_len)
			pr_devel("%.8x %.8x %.8x\n", ptr[i], ptr[i + 1],
				ptr[i + 2]);
		अन्यथा अगर ((i + 1) * 4 < buf_len)
			pr_devel("%.8x %.8x\n", ptr[i], ptr[i + 1]);
		अन्यथा
			pr_devel("%.8x\n", ptr[i]);
	पूर्ण
#पूर्ण_अगर /* DEBUG */
पूर्ण

/* Find a CXL adapter by it's number and increase it's refcount */
काष्ठा cxl *get_cxl_adapter(पूर्णांक num)
अणु
	काष्ठा cxl *adapter;

	spin_lock(&adapter_idr_lock);
	अगर ((adapter = idr_find(&cxl_adapter_idr, num)))
		get_device(&adapter->dev);
	spin_unlock(&adapter_idr_lock);

	वापस adapter;
पूर्ण

अटल पूर्णांक cxl_alloc_adapter_nr(काष्ठा cxl *adapter)
अणु
	पूर्णांक i;

	idr_preload(GFP_KERNEL);
	spin_lock(&adapter_idr_lock);
	i = idr_alloc(&cxl_adapter_idr, adapter, 0, 0, GFP_NOWAIT);
	spin_unlock(&adapter_idr_lock);
	idr_preload_end();
	अगर (i < 0)
		वापस i;

	adapter->adapter_num = i;

	वापस 0;
पूर्ण

व्योम cxl_हटाओ_adapter_nr(काष्ठा cxl *adapter)
अणु
	idr_हटाओ(&cxl_adapter_idr, adapter->adapter_num);
पूर्ण

काष्ठा cxl *cxl_alloc_adapter(व्योम)
अणु
	काष्ठा cxl *adapter;

	अगर (!(adapter = kzalloc(माप(काष्ठा cxl), GFP_KERNEL)))
		वापस शून्य;

	spin_lock_init(&adapter->afu_list_lock);

	अगर (cxl_alloc_adapter_nr(adapter))
		जाओ err1;

	अगर (dev_set_name(&adapter->dev, "card%i", adapter->adapter_num))
		जाओ err2;

	/* start with context lock taken */
	atomic_set(&adapter->contexts_num, -1);

	वापस adapter;
err2:
	cxl_हटाओ_adapter_nr(adapter);
err1:
	kमुक्त(adapter);
	वापस शून्य;
पूर्ण

काष्ठा cxl_afu *cxl_alloc_afu(काष्ठा cxl *adapter, पूर्णांक slice)
अणु
	काष्ठा cxl_afu *afu;

	अगर (!(afu = kzalloc(माप(काष्ठा cxl_afu), GFP_KERNEL)))
		वापस शून्य;

	afu->adapter = adapter;
	afu->dev.parent = &adapter->dev;
	afu->dev.release = cxl_ops->release_afu;
	afu->slice = slice;
	idr_init(&afu->contexts_idr);
	mutex_init(&afu->contexts_lock);
	spin_lock_init(&afu->afu_cntl_lock);
	atomic_set(&afu->configured_state, -1);
	afu->prefault_mode = CXL_PREFAULT_NONE;
	afu->irqs_max = afu->adapter->user_irqs;

	वापस afu;
पूर्ण

पूर्णांक cxl_afu_select_best_mode(काष्ठा cxl_afu *afu)
अणु
	अगर (afu->modes_supported & CXL_MODE_सूचीECTED)
		वापस cxl_ops->afu_activate_mode(afu, CXL_MODE_सूचीECTED);

	अगर (afu->modes_supported & CXL_MODE_DEDICATED)
		वापस cxl_ops->afu_activate_mode(afu, CXL_MODE_DEDICATED);

	dev_warn(&afu->dev, "No supported programming modes available\n");
	/* We करोn't fail this so the user can inspect sysfs */
	वापस 0;
पूर्ण

पूर्णांक cxl_adapter_context_get(काष्ठा cxl *adapter)
अणु
	पूर्णांक rc;

	rc = atomic_inc_unless_negative(&adapter->contexts_num);
	वापस rc ? 0 : -EBUSY;
पूर्ण

व्योम cxl_adapter_context_put(काष्ठा cxl *adapter)
अणु
	atomic_dec_अगर_positive(&adapter->contexts_num);
पूर्ण

पूर्णांक cxl_adapter_context_lock(काष्ठा cxl *adapter)
अणु
	पूर्णांक rc;
	/* no active contexts -> contexts_num == 0 */
	rc = atomic_cmpxchg(&adapter->contexts_num, 0, -1);
	वापस rc ? -EBUSY : 0;
पूर्ण

व्योम cxl_adapter_context_unlock(काष्ठा cxl *adapter)
अणु
	पूर्णांक val = atomic_cmpxchg(&adapter->contexts_num, -1, 0);

	/*
	 * contexts lock taken -> contexts_num == -1
	 * If not true then show a warning and क्रमce reset the lock.
	 * This will happen when context_unlock was requested without
	 * करोing a context_lock.
	 */
	अगर (val != -1) अणु
		atomic_set(&adapter->contexts_num, 0);
		WARN(1, "Adapter context unlocked with %d active contexts",
		     val);
	पूर्ण
पूर्ण

अटल पूर्णांक __init init_cxl(व्योम)
अणु
	पूर्णांक rc = 0;

	अगर (!tlbie_capable)
		वापस -EINVAL;

	अगर ((rc = cxl_file_init()))
		वापस rc;

	cxl_debugfs_init();

	/*
	 * we करोn't रेजिस्टर the callback on P9. slb callack is only
	 * used क्रम the PSL8 MMU and CX4.
	 */
	अगर (cxl_is_घातer8()) अणु
		rc = रेजिस्टर_cxl_calls(&cxl_calls);
		अगर (rc)
			जाओ err;
	पूर्ण

	अगर (cpu_has_feature(CPU_FTR_HVMODE)) अणु
		cxl_ops = &cxl_native_ops;
		rc = pci_रेजिस्टर_driver(&cxl_pci_driver);
	पूर्ण
#अगर_घोषित CONFIG_PPC_PSERIES
	अन्यथा अणु
		cxl_ops = &cxl_guest_ops;
		rc = platक्रमm_driver_रेजिस्टर(&cxl_of_driver);
	पूर्ण
#पूर्ण_अगर
	अगर (rc)
		जाओ err1;

	वापस 0;
err1:
	अगर (cxl_is_घातer8())
		unरेजिस्टर_cxl_calls(&cxl_calls);
err:
	cxl_debugfs_निकास();
	cxl_file_निकास();

	वापस rc;
पूर्ण

अटल व्योम निकास_cxl(व्योम)
अणु
	अगर (cpu_has_feature(CPU_FTR_HVMODE))
		pci_unरेजिस्टर_driver(&cxl_pci_driver);
#अगर_घोषित CONFIG_PPC_PSERIES
	अन्यथा
		platक्रमm_driver_unरेजिस्टर(&cxl_of_driver);
#पूर्ण_अगर

	cxl_debugfs_निकास();
	cxl_file_निकास();
	अगर (cxl_is_घातer8())
		unरेजिस्टर_cxl_calls(&cxl_calls);
	idr_destroy(&cxl_adapter_idr);
पूर्ण

module_init(init_cxl);
module_निकास(निकास_cxl);

MODULE_DESCRIPTION("IBM Coherent Accelerator");
MODULE_AUTHOR("Ian Munsie <imunsie@au1.ibm.com>");
MODULE_LICENSE("GPL");
