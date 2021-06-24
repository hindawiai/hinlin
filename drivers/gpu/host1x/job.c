<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Tegra host1x Job
 *
 * Copyright (c) 2010-2015, NVIDIA Corporation.
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/host1x.h>
#समावेश <linux/iommu.h>
#समावेश <linux/kref.h>
#समावेश <linux/module.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <trace/events/host1x.h>

#समावेश "channel.h"
#समावेश "dev.h"
#समावेश "job.h"
#समावेश "syncpt.h"

#घोषणा HOST1X_WAIT_SYNCPT_OFFSET 0x8

काष्ठा host1x_job *host1x_job_alloc(काष्ठा host1x_channel *ch,
				    u32 num_cmdbufs, u32 num_relocs)
अणु
	काष्ठा host1x_job *job = शून्य;
	अचिन्हित पूर्णांक num_unpins = num_relocs;
	u64 total;
	व्योम *mem;

	अगर (!IS_ENABLED(CONFIG_TEGRA_HOST1X_FIREWALL))
		num_unpins += num_cmdbufs;

	/* Check that we're not going to overflow */
	total = माप(काष्ठा host1x_job) +
		(u64)num_relocs * माप(काष्ठा host1x_reloc) +
		(u64)num_unpins * माप(काष्ठा host1x_job_unpin_data) +
		(u64)num_cmdbufs * माप(काष्ठा host1x_job_gather) +
		(u64)num_unpins * माप(dma_addr_t) +
		(u64)num_unpins * माप(u32 *);
	अगर (total > अच_दीर्घ_उच्च)
		वापस शून्य;

	mem = job = kzalloc(total, GFP_KERNEL);
	अगर (!job)
		वापस शून्य;

	kref_init(&job->ref);
	job->channel = ch;

	/* Redistribute memory to the काष्ठाs  */
	mem += माप(काष्ठा host1x_job);
	job->relocs = num_relocs ? mem : शून्य;
	mem += num_relocs * माप(काष्ठा host1x_reloc);
	job->unpins = num_unpins ? mem : शून्य;
	mem += num_unpins * माप(काष्ठा host1x_job_unpin_data);
	job->gathers = num_cmdbufs ? mem : शून्य;
	mem += num_cmdbufs * माप(काष्ठा host1x_job_gather);
	job->addr_phys = num_unpins ? mem : शून्य;

	job->reloc_addr_phys = job->addr_phys;
	job->gather_addr_phys = &job->addr_phys[num_relocs];

	वापस job;
पूर्ण
EXPORT_SYMBOL(host1x_job_alloc);

काष्ठा host1x_job *host1x_job_get(काष्ठा host1x_job *job)
अणु
	kref_get(&job->ref);
	वापस job;
पूर्ण
EXPORT_SYMBOL(host1x_job_get);

अटल व्योम job_मुक्त(काष्ठा kref *ref)
अणु
	काष्ठा host1x_job *job = container_of(ref, काष्ठा host1x_job, ref);

	अगर (job->syncpt)
		host1x_syncpt_put(job->syncpt);

	kमुक्त(job);
पूर्ण

व्योम host1x_job_put(काष्ठा host1x_job *job)
अणु
	kref_put(&job->ref, job_मुक्त);
पूर्ण
EXPORT_SYMBOL(host1x_job_put);

व्योम host1x_job_add_gather(काष्ठा host1x_job *job, काष्ठा host1x_bo *bo,
			   अचिन्हित पूर्णांक words, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा host1x_job_gather *gather = &job->gathers[job->num_gathers];

	gather->words = words;
	gather->bo = bo;
	gather->offset = offset;

	job->num_gathers++;
पूर्ण
EXPORT_SYMBOL(host1x_job_add_gather);

अटल अचिन्हित पूर्णांक pin_job(काष्ठा host1x *host, काष्ठा host1x_job *job)
अणु
	काष्ठा host1x_client *client = job->client;
	काष्ठा device *dev = client->dev;
	काष्ठा host1x_job_gather *g;
	काष्ठा iommu_करोमुख्य *करोमुख्य;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	करोमुख्य = iommu_get_करोमुख्य_क्रम_dev(dev);
	job->num_unpins = 0;

	क्रम (i = 0; i < job->num_relocs; i++) अणु
		काष्ठा host1x_reloc *reloc = &job->relocs[i];
		dma_addr_t phys_addr, *phys;
		काष्ठा sg_table *sgt;

		reloc->target.bo = host1x_bo_get(reloc->target.bo);
		अगर (!reloc->target.bo) अणु
			err = -EINVAL;
			जाओ unpin;
		पूर्ण

		/*
		 * If the client device is not attached to an IOMMU, the
		 * physical address of the buffer object can be used.
		 *
		 * Similarly, when an IOMMU करोमुख्य is shared between all
		 * host1x clients, the IOVA is alपढ़ोy available, so no
		 * need to map the buffer object again.
		 *
		 * XXX Note that this isn't always safe to करो because it
		 * relies on an assumption that no cache मुख्यtenance is
		 * needed on the buffer objects.
		 */
		अगर (!करोमुख्य || client->group)
			phys = &phys_addr;
		अन्यथा
			phys = शून्य;

		sgt = host1x_bo_pin(dev, reloc->target.bo, phys);
		अगर (IS_ERR(sgt)) अणु
			err = PTR_ERR(sgt);
			जाओ unpin;
		पूर्ण

		अगर (sgt) अणु
			अचिन्हित दीर्घ mask = HOST1X_RELOC_READ |
					     HOST1X_RELOC_WRITE;
			क्रमागत dma_data_direction dir;

			चयन (reloc->flags & mask) अणु
			हाल HOST1X_RELOC_READ:
				dir = DMA_TO_DEVICE;
				अवरोध;

			हाल HOST1X_RELOC_WRITE:
				dir = DMA_FROM_DEVICE;
				अवरोध;

			हाल HOST1X_RELOC_READ | HOST1X_RELOC_WRITE:
				dir = DMA_BIसूचीECTIONAL;
				अवरोध;

			शेष:
				err = -EINVAL;
				जाओ unpin;
			पूर्ण

			err = dma_map_sgtable(dev, sgt, dir, 0);
			अगर (err)
				जाओ unpin;

			job->unpins[job->num_unpins].dev = dev;
			job->unpins[job->num_unpins].dir = dir;
			phys_addr = sg_dma_address(sgt->sgl);
		पूर्ण

		job->addr_phys[job->num_unpins] = phys_addr;
		job->unpins[job->num_unpins].bo = reloc->target.bo;
		job->unpins[job->num_unpins].sgt = sgt;
		job->num_unpins++;
	पूर्ण

	/*
	 * We will copy gathers BO content later, so there is no need to
	 * hold and pin them.
	 */
	अगर (IS_ENABLED(CONFIG_TEGRA_HOST1X_FIREWALL))
		वापस 0;

	क्रम (i = 0; i < job->num_gathers; i++) अणु
		माप_प्रकार gather_size = 0;
		काष्ठा scatterlist *sg;
		काष्ठा sg_table *sgt;
		dma_addr_t phys_addr;
		अचिन्हित दीर्घ shअगरt;
		काष्ठा iova *alloc;
		dma_addr_t *phys;
		अचिन्हित पूर्णांक j;

		g = &job->gathers[i];
		g->bo = host1x_bo_get(g->bo);
		अगर (!g->bo) अणु
			err = -EINVAL;
			जाओ unpin;
		पूर्ण

		/**
		 * If the host1x is not attached to an IOMMU, there is no need
		 * to map the buffer object क्रम the host1x, since the physical
		 * address can simply be used.
		 */
		अगर (!iommu_get_करोमुख्य_क्रम_dev(host->dev))
			phys = &phys_addr;
		अन्यथा
			phys = शून्य;

		sgt = host1x_bo_pin(host->dev, g->bo, phys);
		अगर (IS_ERR(sgt)) अणु
			err = PTR_ERR(sgt);
			जाओ put;
		पूर्ण

		अगर (host->करोमुख्य) अणु
			क्रम_each_sgtable_sg(sgt, sg, j)
				gather_size += sg->length;
			gather_size = iova_align(&host->iova, gather_size);

			shअगरt = iova_shअगरt(&host->iova);
			alloc = alloc_iova(&host->iova, gather_size >> shअगरt,
					   host->ioबहु_पूर्ण >> shअगरt, true);
			अगर (!alloc) अणु
				err = -ENOMEM;
				जाओ put;
			पूर्ण

			err = iommu_map_sgtable(host->करोमुख्य,
					iova_dma_addr(&host->iova, alloc),
					sgt, IOMMU_READ);
			अगर (err == 0) अणु
				__मुक्त_iova(&host->iova, alloc);
				err = -EINVAL;
				जाओ put;
			पूर्ण

			job->unpins[job->num_unpins].size = gather_size;
			phys_addr = iova_dma_addr(&host->iova, alloc);
		पूर्ण अन्यथा अगर (sgt) अणु
			err = dma_map_sgtable(host->dev, sgt, DMA_TO_DEVICE, 0);
			अगर (err)
				जाओ put;

			job->unpins[job->num_unpins].dir = DMA_TO_DEVICE;
			job->unpins[job->num_unpins].dev = host->dev;
			phys_addr = sg_dma_address(sgt->sgl);
		पूर्ण

		job->addr_phys[job->num_unpins] = phys_addr;
		job->gather_addr_phys[i] = phys_addr;

		job->unpins[job->num_unpins].bo = g->bo;
		job->unpins[job->num_unpins].sgt = sgt;
		job->num_unpins++;
	पूर्ण

	वापस 0;

put:
	host1x_bo_put(g->bo);
unpin:
	host1x_job_unpin(job);
	वापस err;
पूर्ण

अटल पूर्णांक करो_relocs(काष्ठा host1x_job *job, काष्ठा host1x_job_gather *g)
अणु
	व्योम *cmdbuf_addr = शून्य;
	काष्ठा host1x_bo *cmdbuf = g->bo;
	अचिन्हित पूर्णांक i;

	/* pin & patch the relocs क्रम one gather */
	क्रम (i = 0; i < job->num_relocs; i++) अणु
		काष्ठा host1x_reloc *reloc = &job->relocs[i];
		u32 reloc_addr = (job->reloc_addr_phys[i] +
				  reloc->target.offset) >> reloc->shअगरt;
		u32 *target;

		/* skip all other gathers */
		अगर (cmdbuf != reloc->cmdbuf.bo)
			जारी;

		अगर (IS_ENABLED(CONFIG_TEGRA_HOST1X_FIREWALL)) अणु
			target = (u32 *)job->gather_copy_mapped +
					reloc->cmdbuf.offset / माप(u32) +
						g->offset / माप(u32);
			जाओ patch_reloc;
		पूर्ण

		अगर (!cmdbuf_addr) अणु
			cmdbuf_addr = host1x_bo_mmap(cmdbuf);

			अगर (unlikely(!cmdbuf_addr)) अणु
				pr_err("Could not map cmdbuf for relocation\n");
				वापस -ENOMEM;
			पूर्ण
		पूर्ण

		target = cmdbuf_addr + reloc->cmdbuf.offset;
patch_reloc:
		*target = reloc_addr;
	पूर्ण

	अगर (cmdbuf_addr)
		host1x_bo_munmap(cmdbuf, cmdbuf_addr);

	वापस 0;
पूर्ण

अटल bool check_reloc(काष्ठा host1x_reloc *reloc, काष्ठा host1x_bo *cmdbuf,
			अचिन्हित पूर्णांक offset)
अणु
	offset *= माप(u32);

	अगर (reloc->cmdbuf.bo != cmdbuf || reloc->cmdbuf.offset != offset)
		वापस false;

	/* relocation shअगरt value validation isn't implemented yet */
	अगर (reloc->shअगरt)
		वापस false;

	वापस true;
पूर्ण

काष्ठा host1x_firewall अणु
	काष्ठा host1x_job *job;
	काष्ठा device *dev;

	अचिन्हित पूर्णांक num_relocs;
	काष्ठा host1x_reloc *reloc;

	काष्ठा host1x_bo *cmdbuf;
	अचिन्हित पूर्णांक offset;

	u32 words;
	u32 class;
	u32 reg;
	u32 mask;
	u32 count;
पूर्ण;

अटल पूर्णांक check_रेजिस्टर(काष्ठा host1x_firewall *fw, अचिन्हित दीर्घ offset)
अणु
	अगर (!fw->job->is_addr_reg)
		वापस 0;

	अगर (fw->job->is_addr_reg(fw->dev, fw->class, offset)) अणु
		अगर (!fw->num_relocs)
			वापस -EINVAL;

		अगर (!check_reloc(fw->reloc, fw->cmdbuf, fw->offset))
			वापस -EINVAL;

		fw->num_relocs--;
		fw->reloc++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक check_class(काष्ठा host1x_firewall *fw, u32 class)
अणु
	अगर (!fw->job->is_valid_class) अणु
		अगर (fw->class != class)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (!fw->job->is_valid_class(fw->class))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक check_mask(काष्ठा host1x_firewall *fw)
अणु
	u32 mask = fw->mask;
	u32 reg = fw->reg;
	पूर्णांक ret;

	जबतक (mask) अणु
		अगर (fw->words == 0)
			वापस -EINVAL;

		अगर (mask & 1) अणु
			ret = check_रेजिस्टर(fw, reg);
			अगर (ret < 0)
				वापस ret;

			fw->words--;
			fw->offset++;
		पूर्ण
		mask >>= 1;
		reg++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक check_incr(काष्ठा host1x_firewall *fw)
अणु
	u32 count = fw->count;
	u32 reg = fw->reg;
	पूर्णांक ret;

	जबतक (count) अणु
		अगर (fw->words == 0)
			वापस -EINVAL;

		ret = check_रेजिस्टर(fw, reg);
		अगर (ret < 0)
			वापस ret;

		reg++;
		fw->words--;
		fw->offset++;
		count--;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक check_nonincr(काष्ठा host1x_firewall *fw)
अणु
	u32 count = fw->count;
	पूर्णांक ret;

	जबतक (count) अणु
		अगर (fw->words == 0)
			वापस -EINVAL;

		ret = check_रेजिस्टर(fw, fw->reg);
		अगर (ret < 0)
			वापस ret;

		fw->words--;
		fw->offset++;
		count--;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक validate(काष्ठा host1x_firewall *fw, काष्ठा host1x_job_gather *g)
अणु
	u32 *cmdbuf_base = (u32 *)fw->job->gather_copy_mapped +
		(g->offset / माप(u32));
	u32 job_class = fw->class;
	पूर्णांक err = 0;

	fw->words = g->words;
	fw->cmdbuf = g->bo;
	fw->offset = 0;

	जबतक (fw->words && !err) अणु
		u32 word = cmdbuf_base[fw->offset];
		u32 opcode = (word & 0xf0000000) >> 28;

		fw->mask = 0;
		fw->reg = 0;
		fw->count = 0;
		fw->words--;
		fw->offset++;

		चयन (opcode) अणु
		हाल 0:
			fw->class = word >> 6 & 0x3ff;
			fw->mask = word & 0x3f;
			fw->reg = word >> 16 & 0xfff;
			err = check_class(fw, job_class);
			अगर (!err)
				err = check_mask(fw);
			अगर (err)
				जाओ out;
			अवरोध;
		हाल 1:
			fw->reg = word >> 16 & 0xfff;
			fw->count = word & 0xffff;
			err = check_incr(fw);
			अगर (err)
				जाओ out;
			अवरोध;

		हाल 2:
			fw->reg = word >> 16 & 0xfff;
			fw->count = word & 0xffff;
			err = check_nonincr(fw);
			अगर (err)
				जाओ out;
			अवरोध;

		हाल 3:
			fw->mask = word & 0xffff;
			fw->reg = word >> 16 & 0xfff;
			err = check_mask(fw);
			अगर (err)
				जाओ out;
			अवरोध;
		हाल 4:
		हाल 14:
			अवरोध;
		शेष:
			err = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

out:
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक copy_gathers(काष्ठा device *host, काष्ठा host1x_job *job,
			       काष्ठा device *dev)
अणु
	काष्ठा host1x_firewall fw;
	माप_प्रकार size = 0;
	माप_प्रकार offset = 0;
	अचिन्हित पूर्णांक i;

	fw.job = job;
	fw.dev = dev;
	fw.reloc = job->relocs;
	fw.num_relocs = job->num_relocs;
	fw.class = job->class;

	क्रम (i = 0; i < job->num_gathers; i++) अणु
		काष्ठा host1x_job_gather *g = &job->gathers[i];

		size += g->words * माप(u32);
	पूर्ण

	/*
	 * Try a non-blocking allocation from a higher priority pools first,
	 * as aरुकोing क्रम the allocation here is a major perक्रमmance hit.
	 */
	job->gather_copy_mapped = dma_alloc_wc(host, size, &job->gather_copy,
					       GFP_NOWAIT);

	/* the higher priority allocation failed, try the generic-blocking */
	अगर (!job->gather_copy_mapped)
		job->gather_copy_mapped = dma_alloc_wc(host, size,
						       &job->gather_copy,
						       GFP_KERNEL);
	अगर (!job->gather_copy_mapped)
		वापस -ENOMEM;

	job->gather_copy_size = size;

	क्रम (i = 0; i < job->num_gathers; i++) अणु
		काष्ठा host1x_job_gather *g = &job->gathers[i];
		व्योम *gather;

		/* Copy the gather */
		gather = host1x_bo_mmap(g->bo);
		स_नकल(job->gather_copy_mapped + offset, gather + g->offset,
		       g->words * माप(u32));
		host1x_bo_munmap(g->bo, gather);

		/* Store the location in the buffer */
		g->base = job->gather_copy;
		g->offset = offset;

		/* Validate the job */
		अगर (validate(&fw, g))
			वापस -EINVAL;

		offset += g->words * माप(u32);
	पूर्ण

	/* No relocs should reमुख्य at this poपूर्णांक */
	अगर (fw.num_relocs)
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक host1x_job_pin(काष्ठा host1x_job *job, काष्ठा device *dev)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक i, j;
	काष्ठा host1x *host = dev_get_drvdata(dev->parent);

	/* pin memory */
	err = pin_job(host, job);
	अगर (err)
		जाओ out;

	अगर (IS_ENABLED(CONFIG_TEGRA_HOST1X_FIREWALL)) अणु
		err = copy_gathers(host->dev, job, dev);
		अगर (err)
			जाओ out;
	पूर्ण

	/* patch gathers */
	क्रम (i = 0; i < job->num_gathers; i++) अणु
		काष्ठा host1x_job_gather *g = &job->gathers[i];

		/* process each gather mem only once */
		अगर (g->handled)
			जारी;

		/* copy_gathers() sets gathers base अगर firewall is enabled */
		अगर (!IS_ENABLED(CONFIG_TEGRA_HOST1X_FIREWALL))
			g->base = job->gather_addr_phys[i];

		क्रम (j = i + 1; j < job->num_gathers; j++) अणु
			अगर (job->gathers[j].bo == g->bo) अणु
				job->gathers[j].handled = true;
				job->gathers[j].base = g->base;
			पूर्ण
		पूर्ण

		err = करो_relocs(job, g);
		अगर (err)
			अवरोध;
	पूर्ण

out:
	अगर (err)
		host1x_job_unpin(job);
	wmb();

	वापस err;
पूर्ण
EXPORT_SYMBOL(host1x_job_pin);

व्योम host1x_job_unpin(काष्ठा host1x_job *job)
अणु
	काष्ठा host1x *host = dev_get_drvdata(job->channel->dev->parent);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < job->num_unpins; i++) अणु
		काष्ठा host1x_job_unpin_data *unpin = &job->unpins[i];
		काष्ठा device *dev = unpin->dev ?: host->dev;
		काष्ठा sg_table *sgt = unpin->sgt;

		अगर (!IS_ENABLED(CONFIG_TEGRA_HOST1X_FIREWALL) &&
		    unpin->size && host->करोमुख्य) अणु
			iommu_unmap(host->करोमुख्य, job->addr_phys[i],
				    unpin->size);
			मुक्त_iova(&host->iova,
				iova_pfn(&host->iova, job->addr_phys[i]));
		पूर्ण

		अगर (unpin->dev && sgt)
			dma_unmap_sgtable(unpin->dev, sgt, unpin->dir, 0);

		host1x_bo_unpin(dev, unpin->bo, sgt);
		host1x_bo_put(unpin->bo);
	पूर्ण

	job->num_unpins = 0;

	अगर (job->gather_copy_size)
		dma_मुक्त_wc(host->dev, job->gather_copy_size,
			    job->gather_copy_mapped, job->gather_copy);
पूर्ण
EXPORT_SYMBOL(host1x_job_unpin);

/*
 * Debug routine used to dump job entries
 */
व्योम host1x_job_dump(काष्ठा device *dev, काष्ठा host1x_job *job)
अणु
	dev_dbg(dev, "    SYNCPT_ID   %d\n", job->syncpt->id);
	dev_dbg(dev, "    SYNCPT_VAL  %d\n", job->syncpt_end);
	dev_dbg(dev, "    FIRST_GET   0x%x\n", job->first_get);
	dev_dbg(dev, "    TIMEOUT     %d\n", job->समयout);
	dev_dbg(dev, "    NUM_SLOTS   %d\n", job->num_slots);
	dev_dbg(dev, "    NUM_HANDLES %d\n", job->num_unpins);
पूर्ण
