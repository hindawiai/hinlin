<शैली गुरु>
/*
 * Copyright 2018 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
#समावेश "nouveau_svm.h"
#समावेश "nouveau_drv.h"
#समावेश "nouveau_chan.h"
#समावेश "nouveau_dmem.h"

#समावेश <nvअगर/notअगरy.h>
#समावेश <nvअगर/object.h>
#समावेश <nvअगर/vmm.h>

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/clb069.h>
#समावेश <nvअगर/अगरc00d.h>

#समावेश <linux/sched/mm.h>
#समावेश <linux/sort.h>
#समावेश <linux/hmm.h>

काष्ठा nouveau_svm अणु
	काष्ठा nouveau_drm *drm;
	काष्ठा mutex mutex;
	काष्ठा list_head inst;

	काष्ठा nouveau_svm_fault_buffer अणु
		पूर्णांक id;
		काष्ठा nvअगर_object object;
		u32 entries;
		u32 getaddr;
		u32 putaddr;
		u32 get;
		u32 put;
		काष्ठा nvअगर_notअगरy notअगरy;

		काष्ठा nouveau_svm_fault अणु
			u64 inst;
			u64 addr;
			u64 समय;
			u32 engine;
			u8  gpc;
			u8  hub;
			u8  access;
			u8  client;
			u8  fault;
			काष्ठा nouveau_svmm *svmm;
		पूर्ण **fault;
		पूर्णांक fault_nr;
	पूर्ण buffer[1];
पूर्ण;

#घोषणा SVM_DBG(s,f,a...) NV_DEBUG((s)->drm, "svm: "f"\n", ##a)
#घोषणा SVM_ERR(s,f,a...) NV_WARN((s)->drm, "svm: "f"\n", ##a)

काष्ठा nouveau_pfnmap_args अणु
	काष्ठा nvअगर_ioctl_v0 i;
	काष्ठा nvअगर_ioctl_mthd_v0 m;
	काष्ठा nvअगर_vmm_pfnmap_v0 p;
पूर्ण;

काष्ठा nouveau_ivmm अणु
	काष्ठा nouveau_svmm *svmm;
	u64 inst;
	काष्ठा list_head head;
पूर्ण;

अटल काष्ठा nouveau_ivmm *
nouveau_ivmm_find(काष्ठा nouveau_svm *svm, u64 inst)
अणु
	काष्ठा nouveau_ivmm *ivmm;
	list_क्रम_each_entry(ivmm, &svm->inst, head) अणु
		अगर (ivmm->inst == inst)
			वापस ivmm;
	पूर्ण
	वापस शून्य;
पूर्ण

#घोषणा SVMM_DBG(s,f,a...)                                                     \
	NV_DEBUG((s)->vmm->cli->drm, "svm-%p: "f"\n", (s), ##a)
#घोषणा SVMM_ERR(s,f,a...)                                                     \
	NV_WARN((s)->vmm->cli->drm, "svm-%p: "f"\n", (s), ##a)

पूर्णांक
nouveau_svmm_bind(काष्ठा drm_device *dev, व्योम *data,
		  काष्ठा drm_file *file_priv)
अणु
	काष्ठा nouveau_cli *cli = nouveau_cli(file_priv);
	काष्ठा drm_nouveau_svm_bind *args = data;
	अचिन्हित target, cmd, priority;
	अचिन्हित दीर्घ addr, end;
	काष्ठा mm_काष्ठा *mm;

	args->बहु_शुरू &= PAGE_MASK;
	args->बहु_पूर्ण = ALIGN(args->बहु_पूर्ण, PAGE_SIZE);

	/* Sanity check arguments */
	अगर (args->reserved0 || args->reserved1)
		वापस -EINVAL;
	अगर (args->header & (~NOUVEAU_SVM_BIND_VALID_MASK))
		वापस -EINVAL;
	अगर (args->बहु_शुरू >= args->बहु_पूर्ण)
		वापस -EINVAL;

	cmd = args->header >> NOUVEAU_SVM_BIND_COMMAND_SHIFT;
	cmd &= NOUVEAU_SVM_BIND_COMMAND_MASK;
	चयन (cmd) अणु
	हाल NOUVEAU_SVM_BIND_COMMAND__MIGRATE:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	priority = args->header >> NOUVEAU_SVM_BIND_PRIORITY_SHIFT;
	priority &= NOUVEAU_SVM_BIND_PRIORITY_MASK;

	/* FIXME support CPU target ie all target value < GPU_VRAM */
	target = args->header >> NOUVEAU_SVM_BIND_TARGET_SHIFT;
	target &= NOUVEAU_SVM_BIND_TARGET_MASK;
	चयन (target) अणु
	हाल NOUVEAU_SVM_BIND_TARGET__GPU_VRAM:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * FIXME: For now refuse non 0 stride, we need to change the migrate
	 * kernel function to handle stride to aव्योम to create a mess within
	 * each device driver.
	 */
	अगर (args->stride)
		वापस -EINVAL;

	/*
	 * Ok we are ask to करो something sane, क्रम now we only support migrate
	 * commands but we will add things like memory policy (what to करो on
	 * page fault) and maybe some other commands.
	 */

	mm = get_task_mm(current);
	mmap_पढ़ो_lock(mm);

	अगर (!cli->svm.svmm) अणु
		mmap_पढ़ो_unlock(mm);
		वापस -EINVAL;
	पूर्ण

	क्रम (addr = args->बहु_शुरू, end = args->बहु_पूर्ण; addr < end;) अणु
		काष्ठा vm_area_काष्ठा *vma;
		अचिन्हित दीर्घ next;

		vma = find_vma_पूर्णांकersection(mm, addr, end);
		अगर (!vma)
			अवरोध;

		addr = max(addr, vma->vm_start);
		next = min(vma->vm_end, end);
		/* This is a best efक्रमt so we ignore errors */
		nouveau_dmem_migrate_vma(cli->drm, cli->svm.svmm, vma, addr,
					 next);
		addr = next;
	पूर्ण

	/*
	 * FIXME Return the number of page we have migrated, again we need to
	 * update the migrate API to वापस that inक्रमmation so that we can
	 * report it to user space.
	 */
	args->result = 0;

	mmap_पढ़ो_unlock(mm);
	mmput(mm);

	वापस 0;
पूर्ण

/* Unlink channel instance from SVMM. */
व्योम
nouveau_svmm_part(काष्ठा nouveau_svmm *svmm, u64 inst)
अणु
	काष्ठा nouveau_ivmm *ivmm;
	अगर (svmm) अणु
		mutex_lock(&svmm->vmm->cli->drm->svm->mutex);
		ivmm = nouveau_ivmm_find(svmm->vmm->cli->drm->svm, inst);
		अगर (ivmm) अणु
			list_del(&ivmm->head);
			kमुक्त(ivmm);
		पूर्ण
		mutex_unlock(&svmm->vmm->cli->drm->svm->mutex);
	पूर्ण
पूर्ण

/* Link channel instance to SVMM. */
पूर्णांक
nouveau_svmm_join(काष्ठा nouveau_svmm *svmm, u64 inst)
अणु
	काष्ठा nouveau_ivmm *ivmm;
	अगर (svmm) अणु
		अगर (!(ivmm = kदो_स्मृति(माप(*ivmm), GFP_KERNEL)))
			वापस -ENOMEM;
		ivmm->svmm = svmm;
		ivmm->inst = inst;

		mutex_lock(&svmm->vmm->cli->drm->svm->mutex);
		list_add(&ivmm->head, &svmm->vmm->cli->drm->svm->inst);
		mutex_unlock(&svmm->vmm->cli->drm->svm->mutex);
	पूर्ण
	वापस 0;
पूर्ण

/* Invalidate SVMM address-range on GPU. */
व्योम
nouveau_svmm_invalidate(काष्ठा nouveau_svmm *svmm, u64 start, u64 limit)
अणु
	अगर (limit > start) अणु
		bool super = svmm->vmm->vmm.object.client->super;
		svmm->vmm->vmm.object.client->super = true;
		nvअगर_object_mthd(&svmm->vmm->vmm.object, NVIF_VMM_V0_PFNCLR,
				 &(काष्ठा nvअगर_vmm_pfnclr_v0) अणु
					.addr = start,
					.size = limit - start,
				 पूर्ण, माप(काष्ठा nvअगर_vmm_pfnclr_v0));
		svmm->vmm->vmm.object.client->super = super;
	पूर्ण
पूर्ण

अटल पूर्णांक
nouveau_svmm_invalidate_range_start(काष्ठा mmu_notअगरier *mn,
				    स्थिर काष्ठा mmu_notअगरier_range *update)
अणु
	काष्ठा nouveau_svmm *svmm =
		container_of(mn, काष्ठा nouveau_svmm, notअगरier);
	अचिन्हित दीर्घ start = update->start;
	अचिन्हित दीर्घ limit = update->end;

	अगर (!mmu_notअगरier_range_blockable(update))
		वापस -EAGAIN;

	SVMM_DBG(svmm, "invalidate %016lx-%016lx", start, limit);

	mutex_lock(&svmm->mutex);
	अगर (unlikely(!svmm->vmm))
		जाओ out;

	/*
	 * Ignore invalidation callbacks क्रम device निजी pages since
	 * the invalidation is handled as part of the migration process.
	 */
	अगर (update->event == MMU_NOTIFY_MIGRATE &&
	    update->migrate_pgmap_owner == svmm->vmm->cli->drm->dev)
		जाओ out;

	अगर (limit > svmm->unmanaged.start && start < svmm->unmanaged.limit) अणु
		अगर (start < svmm->unmanaged.start) अणु
			nouveau_svmm_invalidate(svmm, start,
						svmm->unmanaged.limit);
		पूर्ण
		start = svmm->unmanaged.limit;
	पूर्ण

	nouveau_svmm_invalidate(svmm, start, limit);

out:
	mutex_unlock(&svmm->mutex);
	वापस 0;
पूर्ण

अटल व्योम nouveau_svmm_मुक्त_notअगरier(काष्ठा mmu_notअगरier *mn)
अणु
	kमुक्त(container_of(mn, काष्ठा nouveau_svmm, notअगरier));
पूर्ण

अटल स्थिर काष्ठा mmu_notअगरier_ops nouveau_mn_ops = अणु
	.invalidate_range_start = nouveau_svmm_invalidate_range_start,
	.मुक्त_notअगरier = nouveau_svmm_मुक्त_notअगरier,
पूर्ण;

व्योम
nouveau_svmm_fini(काष्ठा nouveau_svmm **psvmm)
अणु
	काष्ठा nouveau_svmm *svmm = *psvmm;
	अगर (svmm) अणु
		mutex_lock(&svmm->mutex);
		svmm->vmm = शून्य;
		mutex_unlock(&svmm->mutex);
		mmu_notअगरier_put(&svmm->notअगरier);
		*psvmm = शून्य;
	पूर्ण
पूर्ण

पूर्णांक
nouveau_svmm_init(काष्ठा drm_device *dev, व्योम *data,
		  काष्ठा drm_file *file_priv)
अणु
	काष्ठा nouveau_cli *cli = nouveau_cli(file_priv);
	काष्ठा nouveau_svmm *svmm;
	काष्ठा drm_nouveau_svm_init *args = data;
	पूर्णांक ret;

	/* We need to fail अगर svm is disabled */
	अगर (!cli->drm->svm)
		वापस -ENOSYS;

	/* Allocate tracking क्रम SVM-enabled VMM. */
	अगर (!(svmm = kzalloc(माप(*svmm), GFP_KERNEL)))
		वापस -ENOMEM;
	svmm->vmm = &cli->svm;
	svmm->unmanaged.start = args->unmanaged_addr;
	svmm->unmanaged.limit = args->unmanaged_addr + args->unmanaged_size;
	mutex_init(&svmm->mutex);

	/* Check that SVM isn't alपढ़ोy enabled क्रम the client. */
	mutex_lock(&cli->mutex);
	अगर (cli->svm.cli) अणु
		ret = -EBUSY;
		जाओ out_मुक्त;
	पूर्ण

	/* Allocate a new GPU VMM that can support SVM (managed by the
	 * client, with replayable faults enabled).
	 *
	 * All future channel/memory allocations will make use of this
	 * VMM instead of the standard one.
	 */
	ret = nvअगर_vmm_ctor(&cli->mmu, "svmVmm",
			    cli->vmm.vmm.object.oclass, true,
			    args->unmanaged_addr, args->unmanaged_size,
			    &(काष्ठा gp100_vmm_v0) अणु
				.fault_replay = true,
			    पूर्ण, माप(काष्ठा gp100_vmm_v0), &cli->svm.vmm);
	अगर (ret)
		जाओ out_मुक्त;

	mmap_ग_लिखो_lock(current->mm);
	svmm->notअगरier.ops = &nouveau_mn_ops;
	ret = __mmu_notअगरier_रेजिस्टर(&svmm->notअगरier, current->mm);
	अगर (ret)
		जाओ out_mm_unlock;
	/* Note, ownership of svmm transfers to mmu_notअगरier */

	cli->svm.svmm = svmm;
	cli->svm.cli = cli;
	mmap_ग_लिखो_unlock(current->mm);
	mutex_unlock(&cli->mutex);
	वापस 0;

out_mm_unlock:
	mmap_ग_लिखो_unlock(current->mm);
out_मुक्त:
	mutex_unlock(&cli->mutex);
	kमुक्त(svmm);
	वापस ret;
पूर्ण

/* Issue fault replay क्रम GPU to retry accesses that faulted previously. */
अटल व्योम
nouveau_svm_fault_replay(काष्ठा nouveau_svm *svm)
अणु
	SVM_DBG(svm, "replay");
	WARN_ON(nvअगर_object_mthd(&svm->drm->client.vmm.vmm.object,
				 GP100_VMM_VN_FAULT_REPLAY,
				 &(काष्ठा gp100_vmm_fault_replay_vn) अणुपूर्ण,
				 माप(काष्ठा gp100_vmm_fault_replay_vn)));
पूर्ण

/* Cancel a replayable fault that could not be handled.
 *
 * Cancelling the fault will trigger recovery to reset the engine
 * and समाप्त the offending channel (ie. GPU संक_अंश).
 */
अटल व्योम
nouveau_svm_fault_cancel(काष्ठा nouveau_svm *svm,
			 u64 inst, u8 hub, u8 gpc, u8 client)
अणु
	SVM_DBG(svm, "cancel %016llx %d %02x %02x", inst, hub, gpc, client);
	WARN_ON(nvअगर_object_mthd(&svm->drm->client.vmm.vmm.object,
				 GP100_VMM_VN_FAULT_CANCEL,
				 &(काष्ठा gp100_vmm_fault_cancel_v0) अणु
					.hub = hub,
					.gpc = gpc,
					.client = client,
					.inst = inst,
				 पूर्ण, माप(काष्ठा gp100_vmm_fault_cancel_v0)));
पूर्ण

अटल व्योम
nouveau_svm_fault_cancel_fault(काष्ठा nouveau_svm *svm,
			       काष्ठा nouveau_svm_fault *fault)
अणु
	nouveau_svm_fault_cancel(svm, fault->inst,
				      fault->hub,
				      fault->gpc,
				      fault->client);
पूर्ण

अटल पूर्णांक
nouveau_svm_fault_cmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा nouveau_svm_fault *fa = *(काष्ठा nouveau_svm_fault **)a;
	स्थिर काष्ठा nouveau_svm_fault *fb = *(काष्ठा nouveau_svm_fault **)b;
	पूर्णांक ret;
	अगर ((ret = (s64)fa->inst - fb->inst))
		वापस ret;
	अगर ((ret = (s64)fa->addr - fb->addr))
		वापस ret;
	/*XXX: atomic? */
	वापस (fa->access == 0 || fa->access == 3) -
	       (fb->access == 0 || fb->access == 3);
पूर्ण

अटल व्योम
nouveau_svm_fault_cache(काष्ठा nouveau_svm *svm,
			काष्ठा nouveau_svm_fault_buffer *buffer, u32 offset)
अणु
	काष्ठा nvअगर_object *memory = &buffer->object;
	स्थिर u32 instlo = nvअगर_rd32(memory, offset + 0x00);
	स्थिर u32 insthi = nvअगर_rd32(memory, offset + 0x04);
	स्थिर u32 addrlo = nvअगर_rd32(memory, offset + 0x08);
	स्थिर u32 addrhi = nvअगर_rd32(memory, offset + 0x0c);
	स्थिर u32 समयlo = nvअगर_rd32(memory, offset + 0x10);
	स्थिर u32 समयhi = nvअगर_rd32(memory, offset + 0x14);
	स्थिर u32 engine = nvअगर_rd32(memory, offset + 0x18);
	स्थिर u32   info = nvअगर_rd32(memory, offset + 0x1c);
	स्थिर u64   inst = (u64)insthi << 32 | instlo;
	स्थिर u8     gpc = (info & 0x1f000000) >> 24;
	स्थिर u8     hub = (info & 0x00100000) >> 20;
	स्थिर u8  client = (info & 0x00007f00) >> 8;
	काष्ठा nouveau_svm_fault *fault;

	//XXX: i think we're supposed to spin रुकोing */
	अगर (WARN_ON(!(info & 0x80000000)))
		वापस;

	nvअगर_mask(memory, offset + 0x1c, 0x80000000, 0x00000000);

	अगर (!buffer->fault[buffer->fault_nr]) अणु
		fault = kदो_स्मृति(माप(*fault), GFP_KERNEL);
		अगर (WARN_ON(!fault)) अणु
			nouveau_svm_fault_cancel(svm, inst, hub, gpc, client);
			वापस;
		पूर्ण
		buffer->fault[buffer->fault_nr] = fault;
	पूर्ण

	fault = buffer->fault[buffer->fault_nr++];
	fault->inst   = inst;
	fault->addr   = (u64)addrhi << 32 | addrlo;
	fault->समय   = (u64)समयhi << 32 | समयlo;
	fault->engine = engine;
	fault->gpc    = gpc;
	fault->hub    = hub;
	fault->access = (info & 0x000f0000) >> 16;
	fault->client = client;
	fault->fault  = (info & 0x0000001f);

	SVM_DBG(svm, "fault %016llx %016llx %02x",
		fault->inst, fault->addr, fault->access);
पूर्ण

काष्ठा svm_notअगरier अणु
	काष्ठा mmu_पूर्णांकerval_notअगरier notअगरier;
	काष्ठा nouveau_svmm *svmm;
पूर्ण;

अटल bool nouveau_svm_range_invalidate(काष्ठा mmu_पूर्णांकerval_notअगरier *mni,
					 स्थिर काष्ठा mmu_notअगरier_range *range,
					 अचिन्हित दीर्घ cur_seq)
अणु
	काष्ठा svm_notअगरier *sn =
		container_of(mni, काष्ठा svm_notअगरier, notअगरier);

	/*
	 * serializes the update to mni->invalidate_seq करोne by caller and
	 * prevents invalidation of the PTE from progressing जबतक HW is being
	 * programmed. This is very hacky and only works because the normal
	 * notअगरier that करोes invalidation is always called after the range
	 * notअगरier.
	 */
	अगर (mmu_notअगरier_range_blockable(range))
		mutex_lock(&sn->svmm->mutex);
	अन्यथा अगर (!mutex_trylock(&sn->svmm->mutex))
		वापस false;
	mmu_पूर्णांकerval_set_seq(mni, cur_seq);
	mutex_unlock(&sn->svmm->mutex);
	वापस true;
पूर्ण

अटल स्थिर काष्ठा mmu_पूर्णांकerval_notअगरier_ops nouveau_svm_mni_ops = अणु
	.invalidate = nouveau_svm_range_invalidate,
पूर्ण;

अटल व्योम nouveau_hmm_convert_pfn(काष्ठा nouveau_drm *drm,
				    काष्ठा hmm_range *range,
				    काष्ठा nouveau_pfnmap_args *args)
अणु
	काष्ठा page *page;

	/*
	 * The address prepared here is passed through nvअगर_object_ioctl()
	 * to an eventual DMA map in something like gp100_vmm_pgt_pfn()
	 *
	 * This is all just encoding the पूर्णांकernal hmm representation पूर्णांकo a
	 * dअगरferent nouveau पूर्णांकernal representation.
	 */
	अगर (!(range->hmm_pfns[0] & HMM_PFN_VALID)) अणु
		args->p.phys[0] = 0;
		वापस;
	पूर्ण

	page = hmm_pfn_to_page(range->hmm_pfns[0]);
	/*
	 * Only map compound pages to the GPU अगर the CPU is also mapping the
	 * page as a compound page. Otherwise, the PTE protections might not be
	 * consistent (e.g., CPU only maps part of a compound page).
	 * Note that the underlying page might still be larger than the
	 * CPU mapping (e.g., a PUD sized compound page partially mapped with
	 * a PMD sized page table entry).
	 */
	अगर (hmm_pfn_to_map_order(range->hmm_pfns[0])) अणु
		अचिन्हित दीर्घ addr = args->p.addr;

		args->p.page = hmm_pfn_to_map_order(range->hmm_pfns[0]) +
				PAGE_SHIFT;
		args->p.size = 1UL << args->p.page;
		args->p.addr &= ~(args->p.size - 1);
		page -= (addr - args->p.addr) >> PAGE_SHIFT;
	पूर्ण
	अगर (is_device_निजी_page(page))
		args->p.phys[0] = nouveau_dmem_page_addr(page) |
				NVIF_VMM_PFNMAP_V0_V |
				NVIF_VMM_PFNMAP_V0_VRAM;
	अन्यथा
		args->p.phys[0] = page_to_phys(page) |
				NVIF_VMM_PFNMAP_V0_V |
				NVIF_VMM_PFNMAP_V0_HOST;
	अगर (range->hmm_pfns[0] & HMM_PFN_WRITE)
		args->p.phys[0] |= NVIF_VMM_PFNMAP_V0_W;
पूर्ण

अटल पूर्णांक nouveau_range_fault(काष्ठा nouveau_svmm *svmm,
			       काष्ठा nouveau_drm *drm,
			       काष्ठा nouveau_pfnmap_args *args, u32 size,
			       अचिन्हित दीर्घ hmm_flags,
			       काष्ठा svm_notअगरier *notअगरier)
अणु
	अचिन्हित दीर्घ समयout =
		jअगरfies + msecs_to_jअगरfies(HMM_RANGE_DEFAULT_TIMEOUT);
	/* Have HMM fault pages within the fault winकरोw to the GPU. */
	अचिन्हित दीर्घ hmm_pfns[1];
	काष्ठा hmm_range range = अणु
		.notअगरier = &notअगरier->notअगरier,
		.start = notअगरier->notअगरier.पूर्णांकerval_tree.start,
		.end = notअगरier->notअगरier.पूर्णांकerval_tree.last + 1,
		.शेष_flags = hmm_flags,
		.hmm_pfns = hmm_pfns,
		.dev_निजी_owner = drm->dev,
	पूर्ण;
	काष्ठा mm_काष्ठा *mm = notअगरier->notअगरier.mm;
	पूर्णांक ret;

	जबतक (true) अणु
		अगर (समय_after(jअगरfies, समयout))
			वापस -EBUSY;

		range.notअगरier_seq = mmu_पूर्णांकerval_पढ़ो_begin(range.notअगरier);
		mmap_पढ़ो_lock(mm);
		ret = hmm_range_fault(&range);
		mmap_पढ़ो_unlock(mm);
		अगर (ret) अणु
			अगर (ret == -EBUSY)
				जारी;
			वापस ret;
		पूर्ण

		mutex_lock(&svmm->mutex);
		अगर (mmu_पूर्णांकerval_पढ़ो_retry(range.notअगरier,
					    range.notअगरier_seq)) अणु
			mutex_unlock(&svmm->mutex);
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण

	nouveau_hmm_convert_pfn(drm, &range, args);

	svmm->vmm->vmm.object.client->super = true;
	ret = nvअगर_object_ioctl(&svmm->vmm->vmm.object, args, size, शून्य);
	svmm->vmm->vmm.object.client->super = false;
	mutex_unlock(&svmm->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक
nouveau_svm_fault(काष्ठा nvअगर_notअगरy *notअगरy)
अणु
	काष्ठा nouveau_svm_fault_buffer *buffer =
		container_of(notअगरy, typeof(*buffer), notअगरy);
	काष्ठा nouveau_svm *svm =
		container_of(buffer, typeof(*svm), buffer[buffer->id]);
	काष्ठा nvअगर_object *device = &svm->drm->client.device.object;
	काष्ठा nouveau_svmm *svmm;
	काष्ठा अणु
		काष्ठा nouveau_pfnmap_args i;
		u64 phys[1];
	पूर्ण args;
	अचिन्हित दीर्घ hmm_flags;
	u64 inst, start, limit;
	पूर्णांक fi, fn;
	पूर्णांक replay = 0, ret;

	/* Parse available fault buffer entries पूर्णांकo a cache, and update
	 * the GET poपूर्णांकer so HW can reuse the entries.
	 */
	SVM_DBG(svm, "fault handler");
	अगर (buffer->get == buffer->put) अणु
		buffer->put = nvअगर_rd32(device, buffer->putaddr);
		buffer->get = nvअगर_rd32(device, buffer->getaddr);
		अगर (buffer->get == buffer->put)
			वापस NVIF_NOTIFY_KEEP;
	पूर्ण
	buffer->fault_nr = 0;

	SVM_DBG(svm, "get %08x put %08x", buffer->get, buffer->put);
	जबतक (buffer->get != buffer->put) अणु
		nouveau_svm_fault_cache(svm, buffer, buffer->get * 0x20);
		अगर (++buffer->get == buffer->entries)
			buffer->get = 0;
	पूर्ण
	nvअगर_wr32(device, buffer->getaddr, buffer->get);
	SVM_DBG(svm, "%d fault(s) pending", buffer->fault_nr);

	/* Sort parsed faults by instance poपूर्णांकer to prevent unnecessary
	 * instance to SVMM translations, followed by address and access
	 * type to reduce the amount of work when handling the faults.
	 */
	sort(buffer->fault, buffer->fault_nr, माप(*buffer->fault),
	     nouveau_svm_fault_cmp, शून्य);

	/* Lookup SVMM काष्ठाure क्रम each unique instance poपूर्णांकer. */
	mutex_lock(&svm->mutex);
	क्रम (fi = 0, svmm = शून्य; fi < buffer->fault_nr; fi++) अणु
		अगर (!svmm || buffer->fault[fi]->inst != inst) अणु
			काष्ठा nouveau_ivmm *ivmm =
				nouveau_ivmm_find(svm, buffer->fault[fi]->inst);
			svmm = ivmm ? ivmm->svmm : शून्य;
			inst = buffer->fault[fi]->inst;
			SVM_DBG(svm, "inst %016llx -> svm-%p", inst, svmm);
		पूर्ण
		buffer->fault[fi]->svmm = svmm;
	पूर्ण
	mutex_unlock(&svm->mutex);

	/* Process list of faults. */
	args.i.i.version = 0;
	args.i.i.type = NVIF_IOCTL_V0_MTHD;
	args.i.m.version = 0;
	args.i.m.method = NVIF_VMM_V0_PFNMAP;
	args.i.p.version = 0;

	क्रम (fi = 0; fn = fi + 1, fi < buffer->fault_nr; fi = fn) अणु
		काष्ठा svm_notअगरier notअगरier;
		काष्ठा mm_काष्ठा *mm;

		/* Cancel any faults from non-SVM channels. */
		अगर (!(svmm = buffer->fault[fi]->svmm)) अणु
			nouveau_svm_fault_cancel_fault(svm, buffer->fault[fi]);
			जारी;
		पूर्ण
		SVMM_DBG(svmm, "addr %016llx", buffer->fault[fi]->addr);

		/* We try and group handling of faults within a small
		 * winकरोw पूर्णांकo a single update.
		 */
		start = buffer->fault[fi]->addr;
		limit = start + PAGE_SIZE;
		अगर (start < svmm->unmanaged.limit)
			limit = min_t(u64, limit, svmm->unmanaged.start);

		/*
		 * Prepare the GPU-side update of all pages within the
		 * fault winकरोw, determining required pages and access
		 * permissions based on pending faults.
		 */
		args.i.p.addr = start;
		args.i.p.page = PAGE_SHIFT;
		args.i.p.size = PAGE_SIZE;
		/*
		 * Determine required permissions based on GPU fault
		 * access flags.
		 * XXX: atomic?
		 */
		चयन (buffer->fault[fi]->access) अणु
		हाल 0: /* READ. */
			hmm_flags = HMM_PFN_REQ_FAULT;
			अवरोध;
		हाल 3: /* PREFETCH. */
			hmm_flags = 0;
			अवरोध;
		शेष:
			hmm_flags = HMM_PFN_REQ_FAULT | HMM_PFN_REQ_WRITE;
			अवरोध;
		पूर्ण

		mm = svmm->notअगरier.mm;
		अगर (!mmget_not_zero(mm)) अणु
			nouveau_svm_fault_cancel_fault(svm, buffer->fault[fi]);
			जारी;
		पूर्ण

		notअगरier.svmm = svmm;
		ret = mmu_पूर्णांकerval_notअगरier_insert(&notअगरier.notअगरier, mm,
						   args.i.p.addr, args.i.p.size,
						   &nouveau_svm_mni_ops);
		अगर (!ret) अणु
			ret = nouveau_range_fault(svmm, svm->drm, &args.i,
				माप(args), hmm_flags, &notअगरier);
			mmu_पूर्णांकerval_notअगरier_हटाओ(&notअगरier.notअगरier);
		पूर्ण
		mmput(mm);

		limit = args.i.p.addr + args.i.p.size;
		क्रम (fn = fi; ++fn < buffer->fault_nr; ) अणु
			/* It's okay to skip over duplicate addresses from the
			 * same SVMM as faults are ordered by access type such
			 * that only the first one needs to be handled.
			 *
			 * ie. WRITE faults appear first, thus any handling of
			 * pending READ faults will alपढ़ोy be satisfied.
			 * But अगर a large page is mapped, make sure subsequent
			 * fault addresses have sufficient access permission.
			 */
			अगर (buffer->fault[fn]->svmm != svmm ||
			    buffer->fault[fn]->addr >= limit ||
			    (buffer->fault[fi]->access == 0 /* READ. */ &&
			     !(args.phys[0] & NVIF_VMM_PFNMAP_V0_V)) ||
			    (buffer->fault[fi]->access != 0 /* READ. */ &&
			     buffer->fault[fi]->access != 3 /* PREFETCH. */ &&
			     !(args.phys[0] & NVIF_VMM_PFNMAP_V0_W)))
				अवरोध;
		पूर्ण

		/* If handling failed completely, cancel all faults. */
		अगर (ret) अणु
			जबतक (fi < fn) अणु
				काष्ठा nouveau_svm_fault *fault =
					buffer->fault[fi++];

				nouveau_svm_fault_cancel_fault(svm, fault);
			पूर्ण
		पूर्ण अन्यथा
			replay++;
	पूर्ण

	/* Issue fault replay to the GPU. */
	अगर (replay)
		nouveau_svm_fault_replay(svm);
	वापस NVIF_NOTIFY_KEEP;
पूर्ण

अटल काष्ठा nouveau_pfnmap_args *
nouveau_pfns_to_args(व्योम *pfns)
अणु
	वापस container_of(pfns, काष्ठा nouveau_pfnmap_args, p.phys);
पूर्ण

u64 *
nouveau_pfns_alloc(अचिन्हित दीर्घ npages)
अणु
	काष्ठा nouveau_pfnmap_args *args;

	args = kzalloc(काष्ठा_size(args, p.phys, npages), GFP_KERNEL);
	अगर (!args)
		वापस शून्य;

	args->i.type = NVIF_IOCTL_V0_MTHD;
	args->m.method = NVIF_VMM_V0_PFNMAP;
	args->p.page = PAGE_SHIFT;

	वापस args->p.phys;
पूर्ण

व्योम
nouveau_pfns_मुक्त(u64 *pfns)
अणु
	काष्ठा nouveau_pfnmap_args *args = nouveau_pfns_to_args(pfns);

	kमुक्त(args);
पूर्ण

व्योम
nouveau_pfns_map(काष्ठा nouveau_svmm *svmm, काष्ठा mm_काष्ठा *mm,
		 अचिन्हित दीर्घ addr, u64 *pfns, अचिन्हित दीर्घ npages)
अणु
	काष्ठा nouveau_pfnmap_args *args = nouveau_pfns_to_args(pfns);
	पूर्णांक ret;

	args->p.addr = addr;
	args->p.size = npages << PAGE_SHIFT;

	mutex_lock(&svmm->mutex);

	svmm->vmm->vmm.object.client->super = true;
	ret = nvअगर_object_ioctl(&svmm->vmm->vmm.object, args, माप(*args) +
				npages * माप(args->p.phys[0]), शून्य);
	svmm->vmm->vmm.object.client->super = false;

	mutex_unlock(&svmm->mutex);
पूर्ण

अटल व्योम
nouveau_svm_fault_buffer_fini(काष्ठा nouveau_svm *svm, पूर्णांक id)
अणु
	काष्ठा nouveau_svm_fault_buffer *buffer = &svm->buffer[id];
	nvअगर_notअगरy_put(&buffer->notअगरy);
पूर्ण

अटल पूर्णांक
nouveau_svm_fault_buffer_init(काष्ठा nouveau_svm *svm, पूर्णांक id)
अणु
	काष्ठा nouveau_svm_fault_buffer *buffer = &svm->buffer[id];
	काष्ठा nvअगर_object *device = &svm->drm->client.device.object;
	buffer->get = nvअगर_rd32(device, buffer->getaddr);
	buffer->put = nvअगर_rd32(device, buffer->putaddr);
	SVM_DBG(svm, "get %08x put %08x (init)", buffer->get, buffer->put);
	वापस nvअगर_notअगरy_get(&buffer->notअगरy);
पूर्ण

अटल व्योम
nouveau_svm_fault_buffer_dtor(काष्ठा nouveau_svm *svm, पूर्णांक id)
अणु
	काष्ठा nouveau_svm_fault_buffer *buffer = &svm->buffer[id];
	पूर्णांक i;

	अगर (buffer->fault) अणु
		क्रम (i = 0; buffer->fault[i] && i < buffer->entries; i++)
			kमुक्त(buffer->fault[i]);
		kvमुक्त(buffer->fault);
	पूर्ण

	nouveau_svm_fault_buffer_fini(svm, id);

	nvअगर_notअगरy_dtor(&buffer->notअगरy);
	nvअगर_object_dtor(&buffer->object);
पूर्ण

अटल पूर्णांक
nouveau_svm_fault_buffer_ctor(काष्ठा nouveau_svm *svm, s32 oclass, पूर्णांक id)
अणु
	काष्ठा nouveau_svm_fault_buffer *buffer = &svm->buffer[id];
	काष्ठा nouveau_drm *drm = svm->drm;
	काष्ठा nvअगर_object *device = &drm->client.device.object;
	काष्ठा nvअगर_clb069_v0 args = अणुपूर्ण;
	पूर्णांक ret;

	buffer->id = id;

	ret = nvअगर_object_ctor(device, "svmFaultBuffer", 0, oclass, &args,
			       माप(args), &buffer->object);
	अगर (ret < 0) अणु
		SVM_ERR(svm, "Fault buffer allocation failed: %d", ret);
		वापस ret;
	पूर्ण

	nvअगर_object_map(&buffer->object, शून्य, 0);
	buffer->entries = args.entries;
	buffer->getaddr = args.get;
	buffer->putaddr = args.put;

	ret = nvअगर_notअगरy_ctor(&buffer->object, "svmFault", nouveau_svm_fault,
			       true, NVB069_V0_NTFY_FAULT, शून्य, 0, 0,
			       &buffer->notअगरy);
	अगर (ret)
		वापस ret;

	buffer->fault = kvzalloc(माप(*buffer->fault) * buffer->entries, GFP_KERNEL);
	अगर (!buffer->fault)
		वापस -ENOMEM;

	वापस nouveau_svm_fault_buffer_init(svm, id);
पूर्ण

व्योम
nouveau_svm_resume(काष्ठा nouveau_drm *drm)
अणु
	काष्ठा nouveau_svm *svm = drm->svm;
	अगर (svm)
		nouveau_svm_fault_buffer_init(svm, 0);
पूर्ण

व्योम
nouveau_svm_suspend(काष्ठा nouveau_drm *drm)
अणु
	काष्ठा nouveau_svm *svm = drm->svm;
	अगर (svm)
		nouveau_svm_fault_buffer_fini(svm, 0);
पूर्ण

व्योम
nouveau_svm_fini(काष्ठा nouveau_drm *drm)
अणु
	काष्ठा nouveau_svm *svm = drm->svm;
	अगर (svm) अणु
		nouveau_svm_fault_buffer_dtor(svm, 0);
		kमुक्त(drm->svm);
		drm->svm = शून्य;
	पूर्ण
पूर्ण

व्योम
nouveau_svm_init(काष्ठा nouveau_drm *drm)
अणु
	अटल स्थिर काष्ठा nvअगर_mclass buffers[] = अणु
		अणु   VOLTA_FAULT_BUFFER_A, 0 पूर्ण,
		अणु MAXWELL_FAULT_BUFFER_A, 0 पूर्ण,
		अणुपूर्ण
	पूर्ण;
	काष्ठा nouveau_svm *svm;
	पूर्णांक ret;

	/* Disable on Volta and newer until channel recovery is fixed,
	 * otherwise clients will have a trivial way to trash the GPU
	 * क्रम everyone.
	 */
	अगर (drm->client.device.info.family > NV_DEVICE_INFO_V0_PASCAL)
		वापस;

	अगर (!(drm->svm = svm = kzalloc(माप(*drm->svm), GFP_KERNEL)))
		वापस;

	drm->svm->drm = drm;
	mutex_init(&drm->svm->mutex);
	INIT_LIST_HEAD(&drm->svm->inst);

	ret = nvअगर_mclass(&drm->client.device.object, buffers);
	अगर (ret < 0) अणु
		SVM_DBG(svm, "No supported fault buffer class");
		nouveau_svm_fini(drm);
		वापस;
	पूर्ण

	ret = nouveau_svm_fault_buffer_ctor(svm, buffers[ret].oclass, 0);
	अगर (ret) अणु
		nouveau_svm_fini(drm);
		वापस;
	पूर्ण

	SVM_DBG(svm, "Initialised");
पूर्ण
