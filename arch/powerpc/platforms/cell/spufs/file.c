<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SPU file प्रणाली -- file contents
 *
 * (C) Copyright IBM Deutschland Entwicklung GmbH 2005
 *
 * Author: Arnd Bergmann <arndb@de.ibm.com>
 */

#अघोषित DEBUG

#समावेश <linux/coredump.h>
#समावेश <linux/fs.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/export.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/poll.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/spu.h>
#समावेश <यंत्र/spu_info.h>
#समावेश <linux/uaccess.h>

#समावेश "spufs.h"
#समावेश "sputrace.h"

#घोषणा SPUFS_MMAP_4K (PAGE_SIZE == 0x1000)

/* Simple attribute files */
काष्ठा spufs_attr अणु
	पूर्णांक (*get)(व्योम *, u64 *);
	पूर्णांक (*set)(व्योम *, u64);
	अक्षर get_buf[24];       /* enough to store a u64 and "\n\0" */
	अक्षर set_buf[24];
	व्योम *data;
	स्थिर अक्षर *fmt;        /* क्रमmat क्रम पढ़ो operation */
	काष्ठा mutex mutex;     /* protects access to these buffers */
पूर्ण;

अटल पूर्णांक spufs_attr_खोलो(काष्ठा inode *inode, काष्ठा file *file,
		पूर्णांक (*get)(व्योम *, u64 *), पूर्णांक (*set)(व्योम *, u64),
		स्थिर अक्षर *fmt)
अणु
	काष्ठा spufs_attr *attr;

	attr = kदो_स्मृति(माप(*attr), GFP_KERNEL);
	अगर (!attr)
		वापस -ENOMEM;

	attr->get = get;
	attr->set = set;
	attr->data = inode->i_निजी;
	attr->fmt = fmt;
	mutex_init(&attr->mutex);
	file->निजी_data = attr;

	वापस nonseekable_खोलो(inode, file);
पूर्ण

अटल पूर्णांक spufs_attr_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
       kमुक्त(file->निजी_data);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार spufs_attr_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
		माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा spufs_attr *attr;
	माप_प्रकार size;
	sमाप_प्रकार ret;

	attr = file->निजी_data;
	अगर (!attr->get)
		वापस -EACCES;

	ret = mutex_lock_पूर्णांकerruptible(&attr->mutex);
	अगर (ret)
		वापस ret;

	अगर (*ppos) अणु		/* जारीd पढ़ो */
		size = म_माप(attr->get_buf);
	पूर्ण अन्यथा अणु		/* first पढ़ो */
		u64 val;
		ret = attr->get(attr->data, &val);
		अगर (ret)
			जाओ out;

		size = scnम_लिखो(attr->get_buf, माप(attr->get_buf),
				 attr->fmt, (अचिन्हित दीर्घ दीर्घ)val);
	पूर्ण

	ret = simple_पढ़ो_from_buffer(buf, len, ppos, attr->get_buf, size);
out:
	mutex_unlock(&attr->mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार spufs_attr_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
		माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा spufs_attr *attr;
	u64 val;
	माप_प्रकार size;
	sमाप_प्रकार ret;

	attr = file->निजी_data;
	अगर (!attr->set)
		वापस -EACCES;

	ret = mutex_lock_पूर्णांकerruptible(&attr->mutex);
	अगर (ret)
		वापस ret;

	ret = -EFAULT;
	size = min(माप(attr->set_buf) - 1, len);
	अगर (copy_from_user(attr->set_buf, buf, size))
		जाओ out;

	ret = len; /* claim we got the whole input */
	attr->set_buf[size] = '\0';
	val = simple_म_से_दीर्घ(attr->set_buf, शून्य, 0);
	attr->set(attr->data, val);
out:
	mutex_unlock(&attr->mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार spufs_dump_emit(काष्ठा coredump_params *cprm, व्योम *buf,
		माप_प्रकार size)
अणु
	अगर (!dump_emit(cprm, buf, size))
		वापस -EIO;
	वापस size;
पूर्ण

#घोषणा DEFINE_SPUFS_SIMPLE_ATTRIBUTE(__fops, __get, __set, __fmt)	\
अटल पूर्णांक __fops ## _खोलो(काष्ठा inode *inode, काष्ठा file *file)	\
अणु									\
	__simple_attr_check_क्रमmat(__fmt, 0ull);			\
	वापस spufs_attr_खोलो(inode, file, __get, __set, __fmt);	\
पूर्ण									\
अटल स्थिर काष्ठा file_operations __fops = अणु				\
	.खोलो	 = __fops ## _खोलो,					\
	.release = spufs_attr_release,					\
	.पढ़ो	 = spufs_attr_पढ़ो,					\
	.ग_लिखो	 = spufs_attr_ग_लिखो,					\
	.llseek  = generic_file_llseek,					\
पूर्ण;


अटल पूर्णांक
spufs_mem_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा spufs_inode_info *i = SPUFS_I(inode);
	काष्ठा spu_context *ctx = i->i_ctx;

	mutex_lock(&ctx->mapping_lock);
	file->निजी_data = ctx;
	अगर (!i->i_खोलोers++)
		ctx->local_store = inode->i_mapping;
	mutex_unlock(&ctx->mapping_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक
spufs_mem_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा spufs_inode_info *i = SPUFS_I(inode);
	काष्ठा spu_context *ctx = i->i_ctx;

	mutex_lock(&ctx->mapping_lock);
	अगर (!--i->i_खोलोers)
		ctx->local_store = शून्य;
	mutex_unlock(&ctx->mapping_lock);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार
spufs_mem_dump(काष्ठा spu_context *ctx, काष्ठा coredump_params *cprm)
अणु
	वापस spufs_dump_emit(cprm, ctx->ops->get_ls(ctx), LS_SIZE);
पूर्ण

अटल sमाप_प्रकार
spufs_mem_पढ़ो(काष्ठा file *file, अक्षर __user *buffer,
				माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा spu_context *ctx = file->निजी_data;
	sमाप_प्रकार ret;

	ret = spu_acquire(ctx);
	अगर (ret)
		वापस ret;
	ret = simple_पढ़ो_from_buffer(buffer, size, pos, ctx->ops->get_ls(ctx),
				      LS_SIZE);
	spu_release(ctx);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार
spufs_mem_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
					माप_प्रकार size, loff_t *ppos)
अणु
	काष्ठा spu_context *ctx = file->निजी_data;
	अक्षर *local_store;
	loff_t pos = *ppos;
	पूर्णांक ret;

	अगर (pos > LS_SIZE)
		वापस -EFBIG;

	ret = spu_acquire(ctx);
	अगर (ret)
		वापस ret;

	local_store = ctx->ops->get_ls(ctx);
	size = simple_ग_लिखो_to_buffer(local_store, LS_SIZE, ppos, buffer, size);
	spu_release(ctx);

	वापस size;
पूर्ण

अटल vm_fault_t
spufs_mem_mmap_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा spu_context *ctx	= vma->vm_file->निजी_data;
	अचिन्हित दीर्घ pfn, offset;
	vm_fault_t ret;

	offset = vmf->pgoff << PAGE_SHIFT;
	अगर (offset >= LS_SIZE)
		वापस VM_FAULT_SIGBUS;

	pr_debug("spufs_mem_mmap_fault address=0x%lx, offset=0x%lx\n",
			vmf->address, offset);

	अगर (spu_acquire(ctx))
		वापस VM_FAULT_NOPAGE;

	अगर (ctx->state == SPU_STATE_SAVED) अणु
		vma->vm_page_prot = pgprot_cached(vma->vm_page_prot);
		pfn = vदो_स्मृति_to_pfn(ctx->csa.lscsa->ls + offset);
	पूर्ण अन्यथा अणु
		vma->vm_page_prot = pgprot_noncached_wc(vma->vm_page_prot);
		pfn = (ctx->spu->local_store_phys + offset) >> PAGE_SHIFT;
	पूर्ण
	ret = vmf_insert_pfn(vma, vmf->address, pfn);

	spu_release(ctx);

	वापस ret;
पूर्ण

अटल पूर्णांक spufs_mem_mmap_access(काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ address,
				व्योम *buf, पूर्णांक len, पूर्णांक ग_लिखो)
अणु
	काष्ठा spu_context *ctx = vma->vm_file->निजी_data;
	अचिन्हित दीर्घ offset = address - vma->vm_start;
	अक्षर *local_store;

	अगर (ग_लिखो && !(vma->vm_flags & VM_WRITE))
		वापस -EACCES;
	अगर (spu_acquire(ctx))
		वापस -EINTR;
	अगर ((offset + len) > vma->vm_end)
		len = vma->vm_end - offset;
	local_store = ctx->ops->get_ls(ctx);
	अगर (ग_लिखो)
		स_नकल_toio(local_store + offset, buf, len);
	अन्यथा
		स_नकल_fromio(buf, local_store + offset, len);
	spu_release(ctx);
	वापस len;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा spufs_mem_mmap_vmops = अणु
	.fault = spufs_mem_mmap_fault,
	.access = spufs_mem_mmap_access,
पूर्ण;

अटल पूर्णांक spufs_mem_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (!(vma->vm_flags & VM_SHARED))
		वापस -EINVAL;

	vma->vm_flags |= VM_IO | VM_PFNMAP;
	vma->vm_page_prot = pgprot_noncached_wc(vma->vm_page_prot);

	vma->vm_ops = &spufs_mem_mmap_vmops;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations spufs_mem_fops = अणु
	.खोलो			= spufs_mem_खोलो,
	.release		= spufs_mem_release,
	.पढ़ो			= spufs_mem_पढ़ो,
	.ग_लिखो			= spufs_mem_ग_लिखो,
	.llseek			= generic_file_llseek,
	.mmap			= spufs_mem_mmap,
पूर्ण;

अटल vm_fault_t spufs_ps_fault(काष्ठा vm_fault *vmf,
				    अचिन्हित दीर्घ ps_offs,
				    अचिन्हित दीर्घ ps_size)
अणु
	काष्ठा spu_context *ctx = vmf->vma->vm_file->निजी_data;
	अचिन्हित दीर्घ area, offset = vmf->pgoff << PAGE_SHIFT;
	पूर्णांक err = 0;
	vm_fault_t ret = VM_FAULT_NOPAGE;

	spu_context_nospu_trace(spufs_ps_fault__enter, ctx);

	अगर (offset >= ps_size)
		वापस VM_FAULT_SIGBUS;

	अगर (fatal_संकेत_pending(current))
		वापस VM_FAULT_SIGBUS;

	/*
	 * Because we release the mmap_lock, the context may be destroyed जबतक
	 * we're in spu_wait. Grab an extra reference so it isn't destroyed
	 * in the meanसमय.
	 */
	get_spu_context(ctx);

	/*
	 * We have to रुको क्रम context to be loaded beक्रमe we have
	 * pages to hand out to the user, but we करोn't want to रुको
	 * with the mmap_lock held.
	 * It is possible to drop the mmap_lock here, but then we need
	 * to वापस VM_FAULT_NOPAGE because the mappings may have
	 * hanged.
	 */
	अगर (spu_acquire(ctx))
		जाओ refault;

	अगर (ctx->state == SPU_STATE_SAVED) अणु
		mmap_पढ़ो_unlock(current->mm);
		spu_context_nospu_trace(spufs_ps_fault__sleep, ctx);
		err = spufs_रुको(ctx->run_wq, ctx->state == SPU_STATE_RUNNABLE);
		spu_context_trace(spufs_ps_fault__wake, ctx, ctx->spu);
		mmap_पढ़ो_lock(current->mm);
	पूर्ण अन्यथा अणु
		area = ctx->spu->problem_phys + ps_offs;
		ret = vmf_insert_pfn(vmf->vma, vmf->address,
				(area + offset) >> PAGE_SHIFT);
		spu_context_trace(spufs_ps_fault__insert, ctx, ctx->spu);
	पूर्ण

	अगर (!err)
		spu_release(ctx);

refault:
	put_spu_context(ctx);
	वापस ret;
पूर्ण

#अगर SPUFS_MMAP_4K
अटल vm_fault_t spufs_cntl_mmap_fault(काष्ठा vm_fault *vmf)
अणु
	वापस spufs_ps_fault(vmf, 0x4000, SPUFS_CNTL_MAP_SIZE);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा spufs_cntl_mmap_vmops = अणु
	.fault = spufs_cntl_mmap_fault,
पूर्ण;

/*
 * mmap support क्रम problem state control area [0x4000 - 0x4fff].
 */
अटल पूर्णांक spufs_cntl_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (!(vma->vm_flags & VM_SHARED))
		वापस -EINVAL;

	vma->vm_flags |= VM_IO | VM_PFNMAP;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	vma->vm_ops = &spufs_cntl_mmap_vmops;
	वापस 0;
पूर्ण
#अन्यथा /* SPUFS_MMAP_4K */
#घोषणा spufs_cntl_mmap शून्य
#पूर्ण_अगर /* !SPUFS_MMAP_4K */

अटल पूर्णांक spufs_cntl_get(व्योम *data, u64 *val)
अणु
	काष्ठा spu_context *ctx = data;
	पूर्णांक ret;

	ret = spu_acquire(ctx);
	अगर (ret)
		वापस ret;
	*val = ctx->ops->status_पढ़ो(ctx);
	spu_release(ctx);

	वापस 0;
पूर्ण

अटल पूर्णांक spufs_cntl_set(व्योम *data, u64 val)
अणु
	काष्ठा spu_context *ctx = data;
	पूर्णांक ret;

	ret = spu_acquire(ctx);
	अगर (ret)
		वापस ret;
	ctx->ops->runcntl_ग_लिखो(ctx, val);
	spu_release(ctx);

	वापस 0;
पूर्ण

अटल पूर्णांक spufs_cntl_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा spufs_inode_info *i = SPUFS_I(inode);
	काष्ठा spu_context *ctx = i->i_ctx;

	mutex_lock(&ctx->mapping_lock);
	file->निजी_data = ctx;
	अगर (!i->i_खोलोers++)
		ctx->cntl = inode->i_mapping;
	mutex_unlock(&ctx->mapping_lock);
	वापस simple_attr_खोलो(inode, file, spufs_cntl_get,
					spufs_cntl_set, "0x%08lx");
पूर्ण

अटल पूर्णांक
spufs_cntl_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा spufs_inode_info *i = SPUFS_I(inode);
	काष्ठा spu_context *ctx = i->i_ctx;

	simple_attr_release(inode, file);

	mutex_lock(&ctx->mapping_lock);
	अगर (!--i->i_खोलोers)
		ctx->cntl = शून्य;
	mutex_unlock(&ctx->mapping_lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations spufs_cntl_fops = अणु
	.खोलो = spufs_cntl_खोलो,
	.release = spufs_cntl_release,
	.पढ़ो = simple_attr_पढ़ो,
	.ग_लिखो = simple_attr_ग_लिखो,
	.llseek	= no_llseek,
	.mmap = spufs_cntl_mmap,
पूर्ण;

अटल पूर्णांक
spufs_regs_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा spufs_inode_info *i = SPUFS_I(inode);
	file->निजी_data = i->i_ctx;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार
spufs_regs_dump(काष्ठा spu_context *ctx, काष्ठा coredump_params *cprm)
अणु
	वापस spufs_dump_emit(cprm, ctx->csa.lscsa->gprs,
			       माप(ctx->csa.lscsa->gprs));
पूर्ण

अटल sमाप_प्रकार
spufs_regs_पढ़ो(काष्ठा file *file, अक्षर __user *buffer,
		माप_प्रकार size, loff_t *pos)
अणु
	पूर्णांक ret;
	काष्ठा spu_context *ctx = file->निजी_data;

	/* pre-check क्रम file position: अगर we'd return EOF, there's no poपूर्णांक
	 * causing a deschedule */
	अगर (*pos >= माप(ctx->csa.lscsa->gprs))
		वापस 0;

	ret = spu_acquire_saved(ctx);
	अगर (ret)
		वापस ret;
	ret = simple_पढ़ो_from_buffer(buffer, size, pos, ctx->csa.lscsa->gprs,
				      माप(ctx->csa.lscsa->gprs));
	spu_release_saved(ctx);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
spufs_regs_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
		 माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा spu_context *ctx = file->निजी_data;
	काष्ठा spu_lscsa *lscsa = ctx->csa.lscsa;
	पूर्णांक ret;

	अगर (*pos >= माप(lscsa->gprs))
		वापस -EFBIG;

	ret = spu_acquire_saved(ctx);
	अगर (ret)
		वापस ret;

	size = simple_ग_लिखो_to_buffer(lscsa->gprs, माप(lscsa->gprs), pos,
					buffer, size);

	spu_release_saved(ctx);
	वापस size;
पूर्ण

अटल स्थिर काष्ठा file_operations spufs_regs_fops = अणु
	.खोलो	 = spufs_regs_खोलो,
	.पढ़ो    = spufs_regs_पढ़ो,
	.ग_लिखो   = spufs_regs_ग_लिखो,
	.llseek  = generic_file_llseek,
पूर्ण;

अटल sमाप_प्रकार
spufs_fpcr_dump(काष्ठा spu_context *ctx, काष्ठा coredump_params *cprm)
अणु
	वापस spufs_dump_emit(cprm, &ctx->csa.lscsa->fpcr,
			       माप(ctx->csa.lscsa->fpcr));
पूर्ण

अटल sमाप_प्रकार
spufs_fpcr_पढ़ो(काष्ठा file *file, अक्षर __user * buffer,
		माप_प्रकार size, loff_t * pos)
अणु
	पूर्णांक ret;
	काष्ठा spu_context *ctx = file->निजी_data;

	ret = spu_acquire_saved(ctx);
	अगर (ret)
		वापस ret;
	ret = simple_पढ़ो_from_buffer(buffer, size, pos, &ctx->csa.lscsa->fpcr,
				      माप(ctx->csa.lscsa->fpcr));
	spu_release_saved(ctx);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
spufs_fpcr_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user * buffer,
		 माप_प्रकार size, loff_t * pos)
अणु
	काष्ठा spu_context *ctx = file->निजी_data;
	काष्ठा spu_lscsa *lscsa = ctx->csa.lscsa;
	पूर्णांक ret;

	अगर (*pos >= माप(lscsa->fpcr))
		वापस -EFBIG;

	ret = spu_acquire_saved(ctx);
	अगर (ret)
		वापस ret;

	size = simple_ग_लिखो_to_buffer(&lscsa->fpcr, माप(lscsa->fpcr), pos,
					buffer, size);

	spu_release_saved(ctx);
	वापस size;
पूर्ण

अटल स्थिर काष्ठा file_operations spufs_fpcr_fops = अणु
	.खोलो = spufs_regs_खोलो,
	.पढ़ो = spufs_fpcr_पढ़ो,
	.ग_लिखो = spufs_fpcr_ग_लिखो,
	.llseek = generic_file_llseek,
पूर्ण;

/* generic खोलो function क्रम all pipe-like files */
अटल पूर्णांक spufs_pipe_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा spufs_inode_info *i = SPUFS_I(inode);
	file->निजी_data = i->i_ctx;

	वापस stream_खोलो(inode, file);
पूर्ण

/*
 * Read as many bytes from the mailbox as possible, until
 * one of the conditions becomes true:
 *
 * - no more data available in the mailbox
 * - end of the user provided buffer
 * - end of the mapped area
 */
अटल sमाप_प्रकार spufs_mbox_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			माप_प्रकार len, loff_t *pos)
अणु
	काष्ठा spu_context *ctx = file->निजी_data;
	u32 mbox_data, __user *udata = (व्योम __user *)buf;
	sमाप_प्रकार count;

	अगर (len < 4)
		वापस -EINVAL;

	count = spu_acquire(ctx);
	अगर (count)
		वापस count;

	क्रम (count = 0; (count + 4) <= len; count += 4, udata++) अणु
		पूर्णांक ret;
		ret = ctx->ops->mbox_पढ़ो(ctx, &mbox_data);
		अगर (ret == 0)
			अवरोध;

		/*
		 * at the end of the mapped area, we can fault
		 * but still need to वापस the data we have
		 * पढ़ो successfully so far.
		 */
		ret = put_user(mbox_data, udata);
		अगर (ret) अणु
			अगर (!count)
				count = -EFAULT;
			अवरोध;
		पूर्ण
	पूर्ण
	spu_release(ctx);

	अगर (!count)
		count = -EAGAIN;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations spufs_mbox_fops = अणु
	.खोलो	= spufs_pipe_खोलो,
	.पढ़ो	= spufs_mbox_पढ़ो,
	.llseek	= no_llseek,
पूर्ण;

अटल sमाप_प्रकार spufs_mbox_stat_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			माप_प्रकार len, loff_t *pos)
अणु
	काष्ठा spu_context *ctx = file->निजी_data;
	sमाप_प्रकार ret;
	u32 mbox_stat;

	अगर (len < 4)
		वापस -EINVAL;

	ret = spu_acquire(ctx);
	अगर (ret)
		वापस ret;

	mbox_stat = ctx->ops->mbox_stat_पढ़ो(ctx) & 0xff;

	spu_release(ctx);

	अगर (copy_to_user(buf, &mbox_stat, माप mbox_stat))
		वापस -EFAULT;

	वापस 4;
पूर्ण

अटल स्थिर काष्ठा file_operations spufs_mbox_stat_fops = अणु
	.खोलो	= spufs_pipe_खोलो,
	.पढ़ो	= spufs_mbox_stat_पढ़ो,
	.llseek = no_llseek,
पूर्ण;

/* low-level ibox access function */
माप_प्रकार spu_ibox_पढ़ो(काष्ठा spu_context *ctx, u32 *data)
अणु
	वापस ctx->ops->ibox_पढ़ो(ctx, data);
पूर्ण

/* पूर्णांकerrupt-level ibox callback function. */
व्योम spufs_ibox_callback(काष्ठा spu *spu)
अणु
	काष्ठा spu_context *ctx = spu->ctx;

	अगर (ctx)
		wake_up_all(&ctx->ibox_wq);
पूर्ण

/*
 * Read as many bytes from the पूर्णांकerrupt mailbox as possible, until
 * one of the conditions becomes true:
 *
 * - no more data available in the mailbox
 * - end of the user provided buffer
 * - end of the mapped area
 *
 * If the file is खोलोed without O_NONBLOCK, we रुको here until
 * any data is available, but वापस when we have been able to
 * पढ़ो something.
 */
अटल sमाप_प्रकार spufs_ibox_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			माप_प्रकार len, loff_t *pos)
अणु
	काष्ठा spu_context *ctx = file->निजी_data;
	u32 ibox_data, __user *udata = (व्योम __user *)buf;
	sमाप_प्रकार count;

	अगर (len < 4)
		वापस -EINVAL;

	count = spu_acquire(ctx);
	अगर (count)
		जाओ out;

	/* रुको only क्रम the first element */
	count = 0;
	अगर (file->f_flags & O_NONBLOCK) अणु
		अगर (!spu_ibox_पढ़ो(ctx, &ibox_data)) अणु
			count = -EAGAIN;
			जाओ out_unlock;
		पूर्ण
	पूर्ण अन्यथा अणु
		count = spufs_रुको(ctx->ibox_wq, spu_ibox_पढ़ो(ctx, &ibox_data));
		अगर (count)
			जाओ out;
	पूर्ण

	/* अगर we can't ग_लिखो at all, वापस -EFAULT */
	count = put_user(ibox_data, udata);
	अगर (count)
		जाओ out_unlock;

	क्रम (count = 4, udata++; (count + 4) <= len; count += 4, udata++) अणु
		पूर्णांक ret;
		ret = ctx->ops->ibox_पढ़ो(ctx, &ibox_data);
		अगर (ret == 0)
			अवरोध;
		/*
		 * at the end of the mapped area, we can fault
		 * but still need to वापस the data we have
		 * पढ़ो successfully so far.
		 */
		ret = put_user(ibox_data, udata);
		अगर (ret)
			अवरोध;
	पूर्ण

out_unlock:
	spu_release(ctx);
out:
	वापस count;
पूर्ण

अटल __poll_t spufs_ibox_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा spu_context *ctx = file->निजी_data;
	__poll_t mask;

	poll_रुको(file, &ctx->ibox_wq, रुको);

	/*
	 * For now keep this unपूर्णांकerruptible and also ignore the rule
	 * that poll should not sleep.  Will be fixed later.
	 */
	mutex_lock(&ctx->state_mutex);
	mask = ctx->ops->mbox_stat_poll(ctx, EPOLLIN | EPOLLRDNORM);
	spu_release(ctx);

	वापस mask;
पूर्ण

अटल स्थिर काष्ठा file_operations spufs_ibox_fops = अणु
	.खोलो	= spufs_pipe_खोलो,
	.पढ़ो	= spufs_ibox_पढ़ो,
	.poll	= spufs_ibox_poll,
	.llseek = no_llseek,
पूर्ण;

अटल sमाप_प्रकार spufs_ibox_stat_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			माप_प्रकार len, loff_t *pos)
अणु
	काष्ठा spu_context *ctx = file->निजी_data;
	sमाप_प्रकार ret;
	u32 ibox_stat;

	अगर (len < 4)
		वापस -EINVAL;

	ret = spu_acquire(ctx);
	अगर (ret)
		वापस ret;
	ibox_stat = (ctx->ops->mbox_stat_पढ़ो(ctx) >> 16) & 0xff;
	spu_release(ctx);

	अगर (copy_to_user(buf, &ibox_stat, माप ibox_stat))
		वापस -EFAULT;

	वापस 4;
पूर्ण

अटल स्थिर काष्ठा file_operations spufs_ibox_stat_fops = अणु
	.खोलो	= spufs_pipe_खोलो,
	.पढ़ो	= spufs_ibox_stat_पढ़ो,
	.llseek = no_llseek,
पूर्ण;

/* low-level mailbox ग_लिखो */
माप_प्रकार spu_wbox_ग_लिखो(काष्ठा spu_context *ctx, u32 data)
अणु
	वापस ctx->ops->wbox_ग_लिखो(ctx, data);
पूर्ण

/* पूर्णांकerrupt-level wbox callback function. */
व्योम spufs_wbox_callback(काष्ठा spu *spu)
अणु
	काष्ठा spu_context *ctx = spu->ctx;

	अगर (ctx)
		wake_up_all(&ctx->wbox_wq);
पूर्ण

/*
 * Write as many bytes to the पूर्णांकerrupt mailbox as possible, until
 * one of the conditions becomes true:
 *
 * - the mailbox is full
 * - end of the user provided buffer
 * - end of the mapped area
 *
 * If the file is खोलोed without O_NONBLOCK, we रुको here until
 * space is available, but वापस when we have been able to
 * ग_लिखो something.
 */
अटल sमाप_प्रकार spufs_wbox_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			माप_प्रकार len, loff_t *pos)
अणु
	काष्ठा spu_context *ctx = file->निजी_data;
	u32 wbox_data, __user *udata = (व्योम __user *)buf;
	sमाप_प्रकार count;

	अगर (len < 4)
		वापस -EINVAL;

	अगर (get_user(wbox_data, udata))
		वापस -EFAULT;

	count = spu_acquire(ctx);
	अगर (count)
		जाओ out;

	/*
	 * make sure we can at least ग_लिखो one element, by रुकोing
	 * in हाल of !O_NONBLOCK
	 */
	count = 0;
	अगर (file->f_flags & O_NONBLOCK) अणु
		अगर (!spu_wbox_ग_लिखो(ctx, wbox_data)) अणु
			count = -EAGAIN;
			जाओ out_unlock;
		पूर्ण
	पूर्ण अन्यथा अणु
		count = spufs_रुको(ctx->wbox_wq, spu_wbox_ग_लिखो(ctx, wbox_data));
		अगर (count)
			जाओ out;
	पूर्ण


	/* ग_लिखो as much as possible */
	क्रम (count = 4, udata++; (count + 4) <= len; count += 4, udata++) अणु
		पूर्णांक ret;
		ret = get_user(wbox_data, udata);
		अगर (ret)
			अवरोध;

		ret = spu_wbox_ग_लिखो(ctx, wbox_data);
		अगर (ret == 0)
			अवरोध;
	पूर्ण

out_unlock:
	spu_release(ctx);
out:
	वापस count;
पूर्ण

अटल __poll_t spufs_wbox_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा spu_context *ctx = file->निजी_data;
	__poll_t mask;

	poll_रुको(file, &ctx->wbox_wq, रुको);

	/*
	 * For now keep this unपूर्णांकerruptible and also ignore the rule
	 * that poll should not sleep.  Will be fixed later.
	 */
	mutex_lock(&ctx->state_mutex);
	mask = ctx->ops->mbox_stat_poll(ctx, EPOLLOUT | EPOLLWRNORM);
	spu_release(ctx);

	वापस mask;
पूर्ण

अटल स्थिर काष्ठा file_operations spufs_wbox_fops = अणु
	.खोलो	= spufs_pipe_खोलो,
	.ग_लिखो	= spufs_wbox_ग_लिखो,
	.poll	= spufs_wbox_poll,
	.llseek = no_llseek,
पूर्ण;

अटल sमाप_प्रकार spufs_wbox_stat_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			माप_प्रकार len, loff_t *pos)
अणु
	काष्ठा spu_context *ctx = file->निजी_data;
	sमाप_प्रकार ret;
	u32 wbox_stat;

	अगर (len < 4)
		वापस -EINVAL;

	ret = spu_acquire(ctx);
	अगर (ret)
		वापस ret;
	wbox_stat = (ctx->ops->mbox_stat_पढ़ो(ctx) >> 8) & 0xff;
	spu_release(ctx);

	अगर (copy_to_user(buf, &wbox_stat, माप wbox_stat))
		वापस -EFAULT;

	वापस 4;
पूर्ण

अटल स्थिर काष्ठा file_operations spufs_wbox_stat_fops = अणु
	.खोलो	= spufs_pipe_खोलो,
	.पढ़ो	= spufs_wbox_stat_पढ़ो,
	.llseek = no_llseek,
पूर्ण;

अटल पूर्णांक spufs_संकेत1_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा spufs_inode_info *i = SPUFS_I(inode);
	काष्ठा spu_context *ctx = i->i_ctx;

	mutex_lock(&ctx->mapping_lock);
	file->निजी_data = ctx;
	अगर (!i->i_खोलोers++)
		ctx->संकेत1 = inode->i_mapping;
	mutex_unlock(&ctx->mapping_lock);
	वापस nonseekable_खोलो(inode, file);
पूर्ण

अटल पूर्णांक
spufs_संकेत1_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा spufs_inode_info *i = SPUFS_I(inode);
	काष्ठा spu_context *ctx = i->i_ctx;

	mutex_lock(&ctx->mapping_lock);
	अगर (!--i->i_खोलोers)
		ctx->संकेत1 = शून्य;
	mutex_unlock(&ctx->mapping_lock);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार spufs_संकेत1_dump(काष्ठा spu_context *ctx,
		काष्ठा coredump_params *cprm)
अणु
	अगर (!ctx->csa.spu_chnlcnt_RW[3])
		वापस 0;
	वापस spufs_dump_emit(cprm, &ctx->csa.spu_chnldata_RW[3],
			       माप(ctx->csa.spu_chnldata_RW[3]));
पूर्ण

अटल sमाप_प्रकार __spufs_संकेत1_पढ़ो(काष्ठा spu_context *ctx, अक्षर __user *buf,
			माप_प्रकार len)
अणु
	अगर (len < माप(ctx->csa.spu_chnldata_RW[3]))
		वापस -EINVAL;
	अगर (!ctx->csa.spu_chnlcnt_RW[3])
		वापस 0;
	अगर (copy_to_user(buf, &ctx->csa.spu_chnldata_RW[3],
			 माप(ctx->csa.spu_chnldata_RW[3])))
		वापस -EFAULT;
	वापस माप(ctx->csa.spu_chnldata_RW[3]);
पूर्ण

अटल sमाप_प्रकार spufs_संकेत1_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			माप_प्रकार len, loff_t *pos)
अणु
	पूर्णांक ret;
	काष्ठा spu_context *ctx = file->निजी_data;

	ret = spu_acquire_saved(ctx);
	अगर (ret)
		वापस ret;
	ret = __spufs_संकेत1_पढ़ो(ctx, buf, len);
	spu_release_saved(ctx);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार spufs_संकेत1_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			माप_प्रकार len, loff_t *pos)
अणु
	काष्ठा spu_context *ctx;
	sमाप_प्रकार ret;
	u32 data;

	ctx = file->निजी_data;

	अगर (len < 4)
		वापस -EINVAL;

	अगर (copy_from_user(&data, buf, 4))
		वापस -EFAULT;

	ret = spu_acquire(ctx);
	अगर (ret)
		वापस ret;
	ctx->ops->संकेत1_ग_लिखो(ctx, data);
	spu_release(ctx);

	वापस 4;
पूर्ण

अटल vm_fault_t
spufs_संकेत1_mmap_fault(काष्ठा vm_fault *vmf)
अणु
#अगर SPUFS_SIGNAL_MAP_SIZE == 0x1000
	वापस spufs_ps_fault(vmf, 0x14000, SPUFS_SIGNAL_MAP_SIZE);
#या_अगर SPUFS_SIGNAL_MAP_SIZE == 0x10000
	/* For 64k pages, both संकेत1 and संकेत2 can be used to mmap the whole
	 * संकेत 1 and 2 area
	 */
	वापस spufs_ps_fault(vmf, 0x10000, SPUFS_SIGNAL_MAP_SIZE);
#अन्यथा
#त्रुटि unsupported page size
#पूर्ण_अगर
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा spufs_संकेत1_mmap_vmops = अणु
	.fault = spufs_संकेत1_mmap_fault,
पूर्ण;

अटल पूर्णांक spufs_संकेत1_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (!(vma->vm_flags & VM_SHARED))
		वापस -EINVAL;

	vma->vm_flags |= VM_IO | VM_PFNMAP;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	vma->vm_ops = &spufs_संकेत1_mmap_vmops;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations spufs_संकेत1_fops = अणु
	.खोलो = spufs_संकेत1_खोलो,
	.release = spufs_संकेत1_release,
	.पढ़ो = spufs_संकेत1_पढ़ो,
	.ग_लिखो = spufs_संकेत1_ग_लिखो,
	.mmap = spufs_संकेत1_mmap,
	.llseek = no_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations spufs_संकेत1_nosched_fops = अणु
	.खोलो = spufs_संकेत1_खोलो,
	.release = spufs_संकेत1_release,
	.ग_लिखो = spufs_संकेत1_ग_लिखो,
	.mmap = spufs_संकेत1_mmap,
	.llseek = no_llseek,
पूर्ण;

अटल पूर्णांक spufs_संकेत2_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा spufs_inode_info *i = SPUFS_I(inode);
	काष्ठा spu_context *ctx = i->i_ctx;

	mutex_lock(&ctx->mapping_lock);
	file->निजी_data = ctx;
	अगर (!i->i_खोलोers++)
		ctx->संकेत2 = inode->i_mapping;
	mutex_unlock(&ctx->mapping_lock);
	वापस nonseekable_खोलो(inode, file);
पूर्ण

अटल पूर्णांक
spufs_संकेत2_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा spufs_inode_info *i = SPUFS_I(inode);
	काष्ठा spu_context *ctx = i->i_ctx;

	mutex_lock(&ctx->mapping_lock);
	अगर (!--i->i_खोलोers)
		ctx->संकेत2 = शून्य;
	mutex_unlock(&ctx->mapping_lock);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार spufs_संकेत2_dump(काष्ठा spu_context *ctx,
		काष्ठा coredump_params *cprm)
अणु
	अगर (!ctx->csa.spu_chnlcnt_RW[4])
		वापस 0;
	वापस spufs_dump_emit(cprm, &ctx->csa.spu_chnldata_RW[4],
			       माप(ctx->csa.spu_chnldata_RW[4]));
पूर्ण

अटल sमाप_प्रकार __spufs_संकेत2_पढ़ो(काष्ठा spu_context *ctx, अक्षर __user *buf,
			माप_प्रकार len)
अणु
	अगर (len < माप(ctx->csa.spu_chnldata_RW[4]))
		वापस -EINVAL;
	अगर (!ctx->csa.spu_chnlcnt_RW[4])
		वापस 0;
	अगर (copy_to_user(buf, &ctx->csa.spu_chnldata_RW[4],
			 माप(ctx->csa.spu_chnldata_RW[4])))
		वापस -EFAULT;
	वापस माप(ctx->csa.spu_chnldata_RW[4]);
पूर्ण

अटल sमाप_प्रकार spufs_संकेत2_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			माप_प्रकार len, loff_t *pos)
अणु
	काष्ठा spu_context *ctx = file->निजी_data;
	पूर्णांक ret;

	ret = spu_acquire_saved(ctx);
	अगर (ret)
		वापस ret;
	ret = __spufs_संकेत2_पढ़ो(ctx, buf, len);
	spu_release_saved(ctx);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार spufs_संकेत2_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			माप_प्रकार len, loff_t *pos)
अणु
	काष्ठा spu_context *ctx;
	sमाप_प्रकार ret;
	u32 data;

	ctx = file->निजी_data;

	अगर (len < 4)
		वापस -EINVAL;

	अगर (copy_from_user(&data, buf, 4))
		वापस -EFAULT;

	ret = spu_acquire(ctx);
	अगर (ret)
		वापस ret;
	ctx->ops->संकेत2_ग_लिखो(ctx, data);
	spu_release(ctx);

	वापस 4;
पूर्ण

#अगर SPUFS_MMAP_4K
अटल vm_fault_t
spufs_संकेत2_mmap_fault(काष्ठा vm_fault *vmf)
अणु
#अगर SPUFS_SIGNAL_MAP_SIZE == 0x1000
	वापस spufs_ps_fault(vmf, 0x1c000, SPUFS_SIGNAL_MAP_SIZE);
#या_अगर SPUFS_SIGNAL_MAP_SIZE == 0x10000
	/* For 64k pages, both संकेत1 and संकेत2 can be used to mmap the whole
	 * संकेत 1 and 2 area
	 */
	वापस spufs_ps_fault(vmf, 0x10000, SPUFS_SIGNAL_MAP_SIZE);
#अन्यथा
#त्रुटि unsupported page size
#पूर्ण_अगर
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा spufs_संकेत2_mmap_vmops = अणु
	.fault = spufs_संकेत2_mmap_fault,
पूर्ण;

अटल पूर्णांक spufs_संकेत2_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (!(vma->vm_flags & VM_SHARED))
		वापस -EINVAL;

	vma->vm_flags |= VM_IO | VM_PFNMAP;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	vma->vm_ops = &spufs_संकेत2_mmap_vmops;
	वापस 0;
पूर्ण
#अन्यथा /* SPUFS_MMAP_4K */
#घोषणा spufs_संकेत2_mmap शून्य
#पूर्ण_अगर /* !SPUFS_MMAP_4K */

अटल स्थिर काष्ठा file_operations spufs_संकेत2_fops = अणु
	.खोलो = spufs_संकेत2_खोलो,
	.release = spufs_संकेत2_release,
	.पढ़ो = spufs_संकेत2_पढ़ो,
	.ग_लिखो = spufs_संकेत2_ग_लिखो,
	.mmap = spufs_संकेत2_mmap,
	.llseek = no_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations spufs_संकेत2_nosched_fops = अणु
	.खोलो = spufs_संकेत2_खोलो,
	.release = spufs_संकेत2_release,
	.ग_लिखो = spufs_संकेत2_ग_लिखो,
	.mmap = spufs_संकेत2_mmap,
	.llseek = no_llseek,
पूर्ण;

/*
 * This is a wrapper around DEFINE_SIMPLE_ATTRIBUTE which करोes the
 * work of acquiring (or not) the SPU context beक्रमe calling through
 * to the actual get routine. The set routine is called directly.
 */
#घोषणा SPU_ATTR_NOACQUIRE	0
#घोषणा SPU_ATTR_ACQUIRE	1
#घोषणा SPU_ATTR_ACQUIRE_SAVED	2

#घोषणा DEFINE_SPUFS_ATTRIBUTE(__name, __get, __set, __fmt, __acquire)	\
अटल पूर्णांक __##__get(व्योम *data, u64 *val)				\
अणु									\
	काष्ठा spu_context *ctx = data;					\
	पूर्णांक ret = 0;							\
									\
	अगर (__acquire == SPU_ATTR_ACQUIRE) अणु				\
		ret = spu_acquire(ctx);					\
		अगर (ret)						\
			वापस ret;					\
		*val = __get(ctx);					\
		spu_release(ctx);					\
	पूर्ण अन्यथा अगर (__acquire == SPU_ATTR_ACQUIRE_SAVED)	अणु		\
		ret = spu_acquire_saved(ctx);				\
		अगर (ret)						\
			वापस ret;					\
		*val = __get(ctx);					\
		spu_release_saved(ctx);					\
	पूर्ण अन्यथा								\
		*val = __get(ctx);					\
									\
	वापस 0;							\
पूर्ण									\
DEFINE_SPUFS_SIMPLE_ATTRIBUTE(__name, __##__get, __set, __fmt);

अटल पूर्णांक spufs_संकेत1_type_set(व्योम *data, u64 val)
अणु
	काष्ठा spu_context *ctx = data;
	पूर्णांक ret;

	ret = spu_acquire(ctx);
	अगर (ret)
		वापस ret;
	ctx->ops->संकेत1_type_set(ctx, val);
	spu_release(ctx);

	वापस 0;
पूर्ण

अटल u64 spufs_संकेत1_type_get(काष्ठा spu_context *ctx)
अणु
	वापस ctx->ops->संकेत1_type_get(ctx);
पूर्ण
DEFINE_SPUFS_ATTRIBUTE(spufs_संकेत1_type, spufs_संकेत1_type_get,
		       spufs_संकेत1_type_set, "%llu\n", SPU_ATTR_ACQUIRE);


अटल पूर्णांक spufs_संकेत2_type_set(व्योम *data, u64 val)
अणु
	काष्ठा spu_context *ctx = data;
	पूर्णांक ret;

	ret = spu_acquire(ctx);
	अगर (ret)
		वापस ret;
	ctx->ops->संकेत2_type_set(ctx, val);
	spu_release(ctx);

	वापस 0;
पूर्ण

अटल u64 spufs_संकेत2_type_get(काष्ठा spu_context *ctx)
अणु
	वापस ctx->ops->संकेत2_type_get(ctx);
पूर्ण
DEFINE_SPUFS_ATTRIBUTE(spufs_संकेत2_type, spufs_संकेत2_type_get,
		       spufs_संकेत2_type_set, "%llu\n", SPU_ATTR_ACQUIRE);

#अगर SPUFS_MMAP_4K
अटल vm_fault_t
spufs_mss_mmap_fault(काष्ठा vm_fault *vmf)
अणु
	वापस spufs_ps_fault(vmf, 0x0000, SPUFS_MSS_MAP_SIZE);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा spufs_mss_mmap_vmops = अणु
	.fault = spufs_mss_mmap_fault,
पूर्ण;

/*
 * mmap support क्रम problem state MFC DMA area [0x0000 - 0x0fff].
 */
अटल पूर्णांक spufs_mss_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (!(vma->vm_flags & VM_SHARED))
		वापस -EINVAL;

	vma->vm_flags |= VM_IO | VM_PFNMAP;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	vma->vm_ops = &spufs_mss_mmap_vmops;
	वापस 0;
पूर्ण
#अन्यथा /* SPUFS_MMAP_4K */
#घोषणा spufs_mss_mmap शून्य
#पूर्ण_अगर /* !SPUFS_MMAP_4K */

अटल पूर्णांक spufs_mss_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा spufs_inode_info *i = SPUFS_I(inode);
	काष्ठा spu_context *ctx = i->i_ctx;

	file->निजी_data = i->i_ctx;

	mutex_lock(&ctx->mapping_lock);
	अगर (!i->i_खोलोers++)
		ctx->mss = inode->i_mapping;
	mutex_unlock(&ctx->mapping_lock);
	वापस nonseekable_खोलो(inode, file);
पूर्ण

अटल पूर्णांक
spufs_mss_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा spufs_inode_info *i = SPUFS_I(inode);
	काष्ठा spu_context *ctx = i->i_ctx;

	mutex_lock(&ctx->mapping_lock);
	अगर (!--i->i_खोलोers)
		ctx->mss = शून्य;
	mutex_unlock(&ctx->mapping_lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations spufs_mss_fops = अणु
	.खोलो	 = spufs_mss_खोलो,
	.release = spufs_mss_release,
	.mmap	 = spufs_mss_mmap,
	.llseek  = no_llseek,
पूर्ण;

अटल vm_fault_t
spufs_psmap_mmap_fault(काष्ठा vm_fault *vmf)
अणु
	वापस spufs_ps_fault(vmf, 0x0000, SPUFS_PS_MAP_SIZE);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा spufs_psmap_mmap_vmops = अणु
	.fault = spufs_psmap_mmap_fault,
पूर्ण;

/*
 * mmap support क्रम full problem state area [0x00000 - 0x1ffff].
 */
अटल पूर्णांक spufs_psmap_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (!(vma->vm_flags & VM_SHARED))
		वापस -EINVAL;

	vma->vm_flags |= VM_IO | VM_PFNMAP;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	vma->vm_ops = &spufs_psmap_mmap_vmops;
	वापस 0;
पूर्ण

अटल पूर्णांक spufs_psmap_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा spufs_inode_info *i = SPUFS_I(inode);
	काष्ठा spu_context *ctx = i->i_ctx;

	mutex_lock(&ctx->mapping_lock);
	file->निजी_data = i->i_ctx;
	अगर (!i->i_खोलोers++)
		ctx->psmap = inode->i_mapping;
	mutex_unlock(&ctx->mapping_lock);
	वापस nonseekable_खोलो(inode, file);
पूर्ण

अटल पूर्णांक
spufs_psmap_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा spufs_inode_info *i = SPUFS_I(inode);
	काष्ठा spu_context *ctx = i->i_ctx;

	mutex_lock(&ctx->mapping_lock);
	अगर (!--i->i_खोलोers)
		ctx->psmap = शून्य;
	mutex_unlock(&ctx->mapping_lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations spufs_psmap_fops = अणु
	.खोलो	 = spufs_psmap_खोलो,
	.release = spufs_psmap_release,
	.mmap	 = spufs_psmap_mmap,
	.llseek  = no_llseek,
पूर्ण;


#अगर SPUFS_MMAP_4K
अटल vm_fault_t
spufs_mfc_mmap_fault(काष्ठा vm_fault *vmf)
अणु
	वापस spufs_ps_fault(vmf, 0x3000, SPUFS_MFC_MAP_SIZE);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा spufs_mfc_mmap_vmops = अणु
	.fault = spufs_mfc_mmap_fault,
पूर्ण;

/*
 * mmap support क्रम problem state MFC DMA area [0x0000 - 0x0fff].
 */
अटल पूर्णांक spufs_mfc_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (!(vma->vm_flags & VM_SHARED))
		वापस -EINVAL;

	vma->vm_flags |= VM_IO | VM_PFNMAP;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	vma->vm_ops = &spufs_mfc_mmap_vmops;
	वापस 0;
पूर्ण
#अन्यथा /* SPUFS_MMAP_4K */
#घोषणा spufs_mfc_mmap शून्य
#पूर्ण_अगर /* !SPUFS_MMAP_4K */

अटल पूर्णांक spufs_mfc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा spufs_inode_info *i = SPUFS_I(inode);
	काष्ठा spu_context *ctx = i->i_ctx;

	/* we करोn't want to deal with DMA पूर्णांकo other processes */
	अगर (ctx->owner != current->mm)
		वापस -EINVAL;

	अगर (atomic_पढ़ो(&inode->i_count) != 1)
		वापस -EBUSY;

	mutex_lock(&ctx->mapping_lock);
	file->निजी_data = ctx;
	अगर (!i->i_खोलोers++)
		ctx->mfc = inode->i_mapping;
	mutex_unlock(&ctx->mapping_lock);
	वापस nonseekable_खोलो(inode, file);
पूर्ण

अटल पूर्णांक
spufs_mfc_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा spufs_inode_info *i = SPUFS_I(inode);
	काष्ठा spu_context *ctx = i->i_ctx;

	mutex_lock(&ctx->mapping_lock);
	अगर (!--i->i_खोलोers)
		ctx->mfc = शून्य;
	mutex_unlock(&ctx->mapping_lock);
	वापस 0;
पूर्ण

/* पूर्णांकerrupt-level mfc callback function. */
व्योम spufs_mfc_callback(काष्ठा spu *spu)
अणु
	काष्ठा spu_context *ctx = spu->ctx;

	अगर (ctx)
		wake_up_all(&ctx->mfc_wq);
पूर्ण

अटल पूर्णांक spufs_पढ़ो_mfc_tagstatus(काष्ठा spu_context *ctx, u32 *status)
अणु
	/* See अगर there is one tag group is complete */
	/* FIXME we need locking around tagरुको */
	*status = ctx->ops->पढ़ो_mfc_tagstatus(ctx) & ctx->tagरुको;
	ctx->tagरुको &= ~*status;
	अगर (*status)
		वापस 1;

	/* enable पूर्णांकerrupt रुकोing क्रम any tag group,
	   may silently fail अगर पूर्णांकerrupts are alपढ़ोy enabled */
	ctx->ops->set_mfc_query(ctx, ctx->tagरुको, 1);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार spufs_mfc_पढ़ो(काष्ठा file *file, अक्षर __user *buffer,
			माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा spu_context *ctx = file->निजी_data;
	पूर्णांक ret = -EINVAL;
	u32 status;

	अगर (size != 4)
		जाओ out;

	ret = spu_acquire(ctx);
	अगर (ret)
		वापस ret;

	ret = -EINVAL;
	अगर (file->f_flags & O_NONBLOCK) अणु
		status = ctx->ops->पढ़ो_mfc_tagstatus(ctx);
		अगर (!(status & ctx->tagरुको))
			ret = -EAGAIN;
		अन्यथा
			/* XXX(hch): shouldn't we clear ret here? */
			ctx->tagरुको &= ~status;
	पूर्ण अन्यथा अणु
		ret = spufs_रुको(ctx->mfc_wq,
			   spufs_पढ़ो_mfc_tagstatus(ctx, &status));
		अगर (ret)
			जाओ out;
	पूर्ण
	spu_release(ctx);

	ret = 4;
	अगर (copy_to_user(buffer, &status, 4))
		ret = -EFAULT;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक spufs_check_valid_dma(काष्ठा mfc_dma_command *cmd)
अणु
	pr_debug("queueing DMA %x %llx %x %x %x\n", cmd->lsa,
		 cmd->ea, cmd->size, cmd->tag, cmd->cmd);

	चयन (cmd->cmd) अणु
	हाल MFC_PUT_CMD:
	हाल MFC_PUTF_CMD:
	हाल MFC_PUTB_CMD:
	हाल MFC_GET_CMD:
	हाल MFC_GETF_CMD:
	हाल MFC_GETB_CMD:
		अवरोध;
	शेष:
		pr_debug("invalid DMA opcode %x\n", cmd->cmd);
		वापस -EIO;
	पूर्ण

	अगर ((cmd->lsa & 0xf) != (cmd->ea &0xf)) अणु
		pr_debug("invalid DMA alignment, ea %llx lsa %x\n",
				cmd->ea, cmd->lsa);
		वापस -EIO;
	पूर्ण

	चयन (cmd->size & 0xf) अणु
	हाल 1:
		अवरोध;
	हाल 2:
		अगर (cmd->lsa & 1)
			जाओ error;
		अवरोध;
	हाल 4:
		अगर (cmd->lsa & 3)
			जाओ error;
		अवरोध;
	हाल 8:
		अगर (cmd->lsa & 7)
			जाओ error;
		अवरोध;
	हाल 0:
		अगर (cmd->lsa & 15)
			जाओ error;
		अवरोध;
	error:
	शेष:
		pr_debug("invalid DMA alignment %x for size %x\n",
			cmd->lsa & 0xf, cmd->size);
		वापस -EIO;
	पूर्ण

	अगर (cmd->size > 16 * 1024) अणु
		pr_debug("invalid DMA size %x\n", cmd->size);
		वापस -EIO;
	पूर्ण

	अगर (cmd->tag & 0xfff0) अणु
		/* we reserve the higher tag numbers क्रम kernel use */
		pr_debug("invalid DMA tag\n");
		वापस -EIO;
	पूर्ण

	अगर (cmd->class) अणु
		/* not supported in this version */
		pr_debug("invalid DMA class\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक spu_send_mfc_command(काष्ठा spu_context *ctx,
				काष्ठा mfc_dma_command cmd,
				पूर्णांक *error)
अणु
	*error = ctx->ops->send_mfc_command(ctx, &cmd);
	अगर (*error == -EAGAIN) अणु
		/* रुको क्रम any tag group to complete
		   so we have space क्रम the new command */
		ctx->ops->set_mfc_query(ctx, ctx->tagरुको, 1);
		/* try again, because the queue might be
		   empty again */
		*error = ctx->ops->send_mfc_command(ctx, &cmd);
		अगर (*error == -EAGAIN)
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल sमाप_प्रकार spufs_mfc_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
			माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा spu_context *ctx = file->निजी_data;
	काष्ठा mfc_dma_command cmd;
	पूर्णांक ret = -EINVAL;

	अगर (size != माप cmd)
		जाओ out;

	ret = -EFAULT;
	अगर (copy_from_user(&cmd, buffer, माप cmd))
		जाओ out;

	ret = spufs_check_valid_dma(&cmd);
	अगर (ret)
		जाओ out;

	ret = spu_acquire(ctx);
	अगर (ret)
		जाओ out;

	ret = spufs_रुको(ctx->run_wq, ctx->state == SPU_STATE_RUNNABLE);
	अगर (ret)
		जाओ out;

	अगर (file->f_flags & O_NONBLOCK) अणु
		ret = ctx->ops->send_mfc_command(ctx, &cmd);
	पूर्ण अन्यथा अणु
		पूर्णांक status;
		ret = spufs_रुको(ctx->mfc_wq,
				 spu_send_mfc_command(ctx, cmd, &status));
		अगर (ret)
			जाओ out;
		अगर (status)
			ret = status;
	पूर्ण

	अगर (ret)
		जाओ out_unlock;

	ctx->tagरुको |= 1 << cmd.tag;
	ret = size;

out_unlock:
	spu_release(ctx);
out:
	वापस ret;
पूर्ण

अटल __poll_t spufs_mfc_poll(काष्ठा file *file,poll_table *रुको)
अणु
	काष्ठा spu_context *ctx = file->निजी_data;
	u32 मुक्त_elements, tagstatus;
	__poll_t mask;

	poll_रुको(file, &ctx->mfc_wq, रुको);

	/*
	 * For now keep this unपूर्णांकerruptible and also ignore the rule
	 * that poll should not sleep.  Will be fixed later.
	 */
	mutex_lock(&ctx->state_mutex);
	ctx->ops->set_mfc_query(ctx, ctx->tagरुको, 2);
	मुक्त_elements = ctx->ops->get_mfc_मुक्त_elements(ctx);
	tagstatus = ctx->ops->पढ़ो_mfc_tagstatus(ctx);
	spu_release(ctx);

	mask = 0;
	अगर (मुक्त_elements & 0xffff)
		mask |= EPOLLOUT | EPOLLWRNORM;
	अगर (tagstatus & ctx->tagरुको)
		mask |= EPOLLIN | EPOLLRDNORM;

	pr_debug("%s: free %d tagstatus %d tagwait %d\n", __func__,
		मुक्त_elements, tagstatus, ctx->tagरुको);

	वापस mask;
पूर्ण

अटल पूर्णांक spufs_mfc_flush(काष्ठा file *file, fl_owner_t id)
अणु
	काष्ठा spu_context *ctx = file->निजी_data;
	पूर्णांक ret;

	ret = spu_acquire(ctx);
	अगर (ret)
		जाओ out;
#अगर 0
/* this currently hangs */
	ret = spufs_रुको(ctx->mfc_wq,
			 ctx->ops->set_mfc_query(ctx, ctx->tagरुको, 2));
	अगर (ret)
		जाओ out;
	ret = spufs_रुको(ctx->mfc_wq,
			 ctx->ops->पढ़ो_mfc_tagstatus(ctx) == ctx->tagरुको);
	अगर (ret)
		जाओ out;
#अन्यथा
	ret = 0;
#पूर्ण_अगर
	spu_release(ctx);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक spufs_mfc_fsync(काष्ठा file *file, loff_t start, loff_t end, पूर्णांक datasync)
अणु
	काष्ठा inode *inode = file_inode(file);
	पूर्णांक err = file_ग_लिखो_and_रुको_range(file, start, end);
	अगर (!err) अणु
		inode_lock(inode);
		err = spufs_mfc_flush(file, शून्य);
		inode_unlock(inode);
	पूर्ण
	वापस err;
पूर्ण

अटल स्थिर काष्ठा file_operations spufs_mfc_fops = अणु
	.खोलो	 = spufs_mfc_खोलो,
	.release = spufs_mfc_release,
	.पढ़ो	 = spufs_mfc_पढ़ो,
	.ग_लिखो	 = spufs_mfc_ग_लिखो,
	.poll	 = spufs_mfc_poll,
	.flush	 = spufs_mfc_flush,
	.fsync	 = spufs_mfc_fsync,
	.mmap	 = spufs_mfc_mmap,
	.llseek  = no_llseek,
पूर्ण;

अटल पूर्णांक spufs_npc_set(व्योम *data, u64 val)
अणु
	काष्ठा spu_context *ctx = data;
	पूर्णांक ret;

	ret = spu_acquire(ctx);
	अगर (ret)
		वापस ret;
	ctx->ops->npc_ग_लिखो(ctx, val);
	spu_release(ctx);

	वापस 0;
पूर्ण

अटल u64 spufs_npc_get(काष्ठा spu_context *ctx)
अणु
	वापस ctx->ops->npc_पढ़ो(ctx);
पूर्ण
DEFINE_SPUFS_ATTRIBUTE(spufs_npc_ops, spufs_npc_get, spufs_npc_set,
		       "0x%llx\n", SPU_ATTR_ACQUIRE);

अटल पूर्णांक spufs_decr_set(व्योम *data, u64 val)
अणु
	काष्ठा spu_context *ctx = data;
	काष्ठा spu_lscsa *lscsa = ctx->csa.lscsa;
	पूर्णांक ret;

	ret = spu_acquire_saved(ctx);
	अगर (ret)
		वापस ret;
	lscsa->decr.slot[0] = (u32) val;
	spu_release_saved(ctx);

	वापस 0;
पूर्ण

अटल u64 spufs_decr_get(काष्ठा spu_context *ctx)
अणु
	काष्ठा spu_lscsa *lscsa = ctx->csa.lscsa;
	वापस lscsa->decr.slot[0];
पूर्ण
DEFINE_SPUFS_ATTRIBUTE(spufs_decr_ops, spufs_decr_get, spufs_decr_set,
		       "0x%llx\n", SPU_ATTR_ACQUIRE_SAVED);

अटल पूर्णांक spufs_decr_status_set(व्योम *data, u64 val)
अणु
	काष्ठा spu_context *ctx = data;
	पूर्णांक ret;

	ret = spu_acquire_saved(ctx);
	अगर (ret)
		वापस ret;
	अगर (val)
		ctx->csa.priv2.mfc_control_RW |= MFC_CNTL_DECREMENTER_RUNNING;
	अन्यथा
		ctx->csa.priv2.mfc_control_RW &= ~MFC_CNTL_DECREMENTER_RUNNING;
	spu_release_saved(ctx);

	वापस 0;
पूर्ण

अटल u64 spufs_decr_status_get(काष्ठा spu_context *ctx)
अणु
	अगर (ctx->csa.priv2.mfc_control_RW & MFC_CNTL_DECREMENTER_RUNNING)
		वापस SPU_DECR_STATUS_RUNNING;
	अन्यथा
		वापस 0;
पूर्ण
DEFINE_SPUFS_ATTRIBUTE(spufs_decr_status_ops, spufs_decr_status_get,
		       spufs_decr_status_set, "0x%llx\n",
		       SPU_ATTR_ACQUIRE_SAVED);

अटल पूर्णांक spufs_event_mask_set(व्योम *data, u64 val)
अणु
	काष्ठा spu_context *ctx = data;
	काष्ठा spu_lscsa *lscsa = ctx->csa.lscsa;
	पूर्णांक ret;

	ret = spu_acquire_saved(ctx);
	अगर (ret)
		वापस ret;
	lscsa->event_mask.slot[0] = (u32) val;
	spu_release_saved(ctx);

	वापस 0;
पूर्ण

अटल u64 spufs_event_mask_get(काष्ठा spu_context *ctx)
अणु
	काष्ठा spu_lscsa *lscsa = ctx->csa.lscsa;
	वापस lscsa->event_mask.slot[0];
पूर्ण

DEFINE_SPUFS_ATTRIBUTE(spufs_event_mask_ops, spufs_event_mask_get,
		       spufs_event_mask_set, "0x%llx\n",
		       SPU_ATTR_ACQUIRE_SAVED);

अटल u64 spufs_event_status_get(काष्ठा spu_context *ctx)
अणु
	काष्ठा spu_state *state = &ctx->csa;
	u64 stat;
	stat = state->spu_chnlcnt_RW[0];
	अगर (stat)
		वापस state->spu_chnldata_RW[0];
	वापस 0;
पूर्ण
DEFINE_SPUFS_ATTRIBUTE(spufs_event_status_ops, spufs_event_status_get,
		       शून्य, "0x%llx\n", SPU_ATTR_ACQUIRE_SAVED)

अटल पूर्णांक spufs_srr0_set(व्योम *data, u64 val)
अणु
	काष्ठा spu_context *ctx = data;
	काष्ठा spu_lscsa *lscsa = ctx->csa.lscsa;
	पूर्णांक ret;

	ret = spu_acquire_saved(ctx);
	अगर (ret)
		वापस ret;
	lscsa->srr0.slot[0] = (u32) val;
	spu_release_saved(ctx);

	वापस 0;
पूर्ण

अटल u64 spufs_srr0_get(काष्ठा spu_context *ctx)
अणु
	काष्ठा spu_lscsa *lscsa = ctx->csa.lscsa;
	वापस lscsa->srr0.slot[0];
पूर्ण
DEFINE_SPUFS_ATTRIBUTE(spufs_srr0_ops, spufs_srr0_get, spufs_srr0_set,
		       "0x%llx\n", SPU_ATTR_ACQUIRE_SAVED)

अटल u64 spufs_id_get(काष्ठा spu_context *ctx)
अणु
	u64 num;

	अगर (ctx->state == SPU_STATE_RUNNABLE)
		num = ctx->spu->number;
	अन्यथा
		num = (अचिन्हित पूर्णांक)-1;

	वापस num;
पूर्ण
DEFINE_SPUFS_ATTRIBUTE(spufs_id_ops, spufs_id_get, शून्य, "0x%llx\n",
		       SPU_ATTR_ACQUIRE)

अटल u64 spufs_object_id_get(काष्ठा spu_context *ctx)
अणु
	/* FIXME: Should there really be no locking here? */
	वापस ctx->object_id;
पूर्ण

अटल पूर्णांक spufs_object_id_set(व्योम *data, u64 id)
अणु
	काष्ठा spu_context *ctx = data;
	ctx->object_id = id;

	वापस 0;
पूर्ण

DEFINE_SPUFS_ATTRIBUTE(spufs_object_id_ops, spufs_object_id_get,
		       spufs_object_id_set, "0x%llx\n", SPU_ATTR_NOACQUIRE);

अटल u64 spufs_lslr_get(काष्ठा spu_context *ctx)
अणु
	वापस ctx->csa.priv2.spu_lslr_RW;
पूर्ण
DEFINE_SPUFS_ATTRIBUTE(spufs_lslr_ops, spufs_lslr_get, शून्य, "0x%llx\n",
		       SPU_ATTR_ACQUIRE_SAVED);

अटल पूर्णांक spufs_info_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा spufs_inode_info *i = SPUFS_I(inode);
	काष्ठा spu_context *ctx = i->i_ctx;
	file->निजी_data = ctx;
	वापस 0;
पूर्ण

अटल पूर्णांक spufs_caps_show(काष्ठा seq_file *s, व्योम *निजी)
अणु
	काष्ठा spu_context *ctx = s->निजी;

	अगर (!(ctx->flags & SPU_CREATE_NOSCHED))
		seq_माला_दो(s, "sched\n");
	अगर (!(ctx->flags & SPU_CREATE_ISOLATE))
		seq_माला_दो(s, "step\n");
	वापस 0;
पूर्ण

अटल पूर्णांक spufs_caps_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, spufs_caps_show, SPUFS_I(inode)->i_ctx);
पूर्ण

अटल स्थिर काष्ठा file_operations spufs_caps_fops = अणु
	.खोलो		= spufs_caps_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

अटल sमाप_प्रकार spufs_mbox_info_dump(काष्ठा spu_context *ctx,
		काष्ठा coredump_params *cprm)
अणु
	अगर (!(ctx->csa.prob.mb_stat_R & 0x0000ff))
		वापस 0;
	वापस spufs_dump_emit(cprm, &ctx->csa.prob.pu_mb_R,
			       माप(ctx->csa.prob.pu_mb_R));
पूर्ण

अटल sमाप_प्रकार spufs_mbox_info_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				   माप_प्रकार len, loff_t *pos)
अणु
	काष्ठा spu_context *ctx = file->निजी_data;
	u32 stat, data;
	पूर्णांक ret;

	ret = spu_acquire_saved(ctx);
	अगर (ret)
		वापस ret;
	spin_lock(&ctx->csa.रेजिस्टर_lock);
	stat = ctx->csa.prob.mb_stat_R;
	data = ctx->csa.prob.pu_mb_R;
	spin_unlock(&ctx->csa.रेजिस्टर_lock);
	spu_release_saved(ctx);

	/* खातापूर्ण अगर there's no entry in the mbox */
	अगर (!(stat & 0x0000ff))
		वापस 0;

	वापस simple_पढ़ो_from_buffer(buf, len, pos, &data, माप(data));
पूर्ण

अटल स्थिर काष्ठा file_operations spufs_mbox_info_fops = अणु
	.खोलो = spufs_info_खोलो,
	.पढ़ो = spufs_mbox_info_पढ़ो,
	.llseek  = generic_file_llseek,
पूर्ण;

अटल sमाप_प्रकार spufs_ibox_info_dump(काष्ठा spu_context *ctx,
		काष्ठा coredump_params *cprm)
अणु
	अगर (!(ctx->csa.prob.mb_stat_R & 0xff0000))
		वापस 0;
	वापस spufs_dump_emit(cprm, &ctx->csa.priv2.puपूर्णांक_mb_R,
			       माप(ctx->csa.priv2.puपूर्णांक_mb_R));
पूर्ण

अटल sमाप_प्रकार spufs_ibox_info_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				   माप_प्रकार len, loff_t *pos)
अणु
	काष्ठा spu_context *ctx = file->निजी_data;
	u32 stat, data;
	पूर्णांक ret;

	ret = spu_acquire_saved(ctx);
	अगर (ret)
		वापस ret;
	spin_lock(&ctx->csa.रेजिस्टर_lock);
	stat = ctx->csa.prob.mb_stat_R;
	data = ctx->csa.priv2.puपूर्णांक_mb_R;
	spin_unlock(&ctx->csa.रेजिस्टर_lock);
	spu_release_saved(ctx);

	/* खातापूर्ण अगर there's no entry in the ibox */
	अगर (!(stat & 0xff0000))
		वापस 0;

	वापस simple_पढ़ो_from_buffer(buf, len, pos, &data, माप(data));
पूर्ण

अटल स्थिर काष्ठा file_operations spufs_ibox_info_fops = अणु
	.खोलो = spufs_info_खोलो,
	.पढ़ो = spufs_ibox_info_पढ़ो,
	.llseek  = generic_file_llseek,
पूर्ण;

अटल माप_प्रकार spufs_wbox_info_cnt(काष्ठा spu_context *ctx)
अणु
	वापस (4 - ((ctx->csa.prob.mb_stat_R & 0x00ff00) >> 8)) * माप(u32);
पूर्ण

अटल sमाप_प्रकार spufs_wbox_info_dump(काष्ठा spu_context *ctx,
		काष्ठा coredump_params *cprm)
अणु
	वापस spufs_dump_emit(cprm, &ctx->csa.spu_mailbox_data,
			spufs_wbox_info_cnt(ctx));
पूर्ण

अटल sमाप_प्रकार spufs_wbox_info_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				   माप_प्रकार len, loff_t *pos)
अणु
	काष्ठा spu_context *ctx = file->निजी_data;
	u32 data[ARRAY_SIZE(ctx->csa.spu_mailbox_data)];
	पूर्णांक ret, count;

	ret = spu_acquire_saved(ctx);
	अगर (ret)
		वापस ret;
	spin_lock(&ctx->csa.रेजिस्टर_lock);
	count = spufs_wbox_info_cnt(ctx);
	स_नकल(&data, &ctx->csa.spu_mailbox_data, माप(data));
	spin_unlock(&ctx->csa.रेजिस्टर_lock);
	spu_release_saved(ctx);

	वापस simple_पढ़ो_from_buffer(buf, len, pos, &data,
				count * माप(u32));
पूर्ण

अटल स्थिर काष्ठा file_operations spufs_wbox_info_fops = अणु
	.खोलो = spufs_info_खोलो,
	.पढ़ो = spufs_wbox_info_पढ़ो,
	.llseek  = generic_file_llseek,
पूर्ण;

अटल व्योम spufs_get_dma_info(काष्ठा spu_context *ctx,
		काष्ठा spu_dma_info *info)
अणु
	पूर्णांक i;

	info->dma_info_type = ctx->csa.priv2.spu_tag_status_query_RW;
	info->dma_info_mask = ctx->csa.lscsa->tag_mask.slot[0];
	info->dma_info_status = ctx->csa.spu_chnldata_RW[24];
	info->dma_info_stall_and_notअगरy = ctx->csa.spu_chnldata_RW[25];
	info->dma_info_atomic_command_status = ctx->csa.spu_chnldata_RW[27];
	क्रम (i = 0; i < 16; i++) अणु
		काष्ठा mfc_cq_sr *qp = &info->dma_info_command_data[i];
		काष्ठा mfc_cq_sr *spuqp = &ctx->csa.priv2.spuq[i];

		qp->mfc_cq_data0_RW = spuqp->mfc_cq_data0_RW;
		qp->mfc_cq_data1_RW = spuqp->mfc_cq_data1_RW;
		qp->mfc_cq_data2_RW = spuqp->mfc_cq_data2_RW;
		qp->mfc_cq_data3_RW = spuqp->mfc_cq_data3_RW;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार spufs_dma_info_dump(काष्ठा spu_context *ctx,
		काष्ठा coredump_params *cprm)
अणु
	काष्ठा spu_dma_info info;

	spufs_get_dma_info(ctx, &info);
	वापस spufs_dump_emit(cprm, &info, माप(info));
पूर्ण

अटल sमाप_प्रकार spufs_dma_info_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			      माप_प्रकार len, loff_t *pos)
अणु
	काष्ठा spu_context *ctx = file->निजी_data;
	काष्ठा spu_dma_info info;
	पूर्णांक ret;

	ret = spu_acquire_saved(ctx);
	अगर (ret)
		वापस ret;
	spin_lock(&ctx->csa.रेजिस्टर_lock);
	spufs_get_dma_info(ctx, &info);
	spin_unlock(&ctx->csa.रेजिस्टर_lock);
	spu_release_saved(ctx);

	वापस simple_पढ़ो_from_buffer(buf, len, pos, &info,
				माप(info));
पूर्ण

अटल स्थिर काष्ठा file_operations spufs_dma_info_fops = अणु
	.खोलो = spufs_info_खोलो,
	.पढ़ो = spufs_dma_info_पढ़ो,
	.llseek = no_llseek,
पूर्ण;

अटल व्योम spufs_get_proxydma_info(काष्ठा spu_context *ctx,
		काष्ठा spu_proxydma_info *info)
अणु
	पूर्णांक i;

	info->proxydma_info_type = ctx->csa.prob.dma_querytype_RW;
	info->proxydma_info_mask = ctx->csa.prob.dma_querymask_RW;
	info->proxydma_info_status = ctx->csa.prob.dma_tagstatus_R;

	क्रम (i = 0; i < 8; i++) अणु
		काष्ठा mfc_cq_sr *qp = &info->proxydma_info_command_data[i];
		काष्ठा mfc_cq_sr *puqp = &ctx->csa.priv2.puq[i];

		qp->mfc_cq_data0_RW = puqp->mfc_cq_data0_RW;
		qp->mfc_cq_data1_RW = puqp->mfc_cq_data1_RW;
		qp->mfc_cq_data2_RW = puqp->mfc_cq_data2_RW;
		qp->mfc_cq_data3_RW = puqp->mfc_cq_data3_RW;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार spufs_proxydma_info_dump(काष्ठा spu_context *ctx,
		काष्ठा coredump_params *cprm)
अणु
	काष्ठा spu_proxydma_info info;

	spufs_get_proxydma_info(ctx, &info);
	वापस spufs_dump_emit(cprm, &info, माप(info));
पूर्ण

अटल sमाप_प्रकार spufs_proxydma_info_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				   माप_प्रकार len, loff_t *pos)
अणु
	काष्ठा spu_context *ctx = file->निजी_data;
	काष्ठा spu_proxydma_info info;
	पूर्णांक ret;

	अगर (len < माप(info))
		वापस -EINVAL;

	ret = spu_acquire_saved(ctx);
	अगर (ret)
		वापस ret;
	spin_lock(&ctx->csa.रेजिस्टर_lock);
	spufs_get_proxydma_info(ctx, &info);
	spin_unlock(&ctx->csa.रेजिस्टर_lock);
	spu_release_saved(ctx);

	वापस simple_पढ़ो_from_buffer(buf, len, pos, &info,
				माप(info));
पूर्ण

अटल स्थिर काष्ठा file_operations spufs_proxydma_info_fops = अणु
	.खोलो = spufs_info_खोलो,
	.पढ़ो = spufs_proxydma_info_पढ़ो,
	.llseek = no_llseek,
पूर्ण;

अटल पूर्णांक spufs_show_tid(काष्ठा seq_file *s, व्योम *निजी)
अणु
	काष्ठा spu_context *ctx = s->निजी;

	seq_म_लिखो(s, "%d\n", ctx->tid);
	वापस 0;
पूर्ण

अटल पूर्णांक spufs_tid_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, spufs_show_tid, SPUFS_I(inode)->i_ctx);
पूर्ण

अटल स्थिर काष्ठा file_operations spufs_tid_fops = अणु
	.खोलो		= spufs_tid_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

अटल स्थिर अक्षर *ctx_state_names[] = अणु
	"user", "system", "iowait", "loaded"
पूर्ण;

अटल अचिन्हित दीर्घ दीर्घ spufs_acct_समय(काष्ठा spu_context *ctx,
		क्रमागत spu_utilization_state state)
अणु
	अचिन्हित दीर्घ दीर्घ समय = ctx->stats.बार[state];

	/*
	 * In general, utilization statistics are updated by the controlling
	 * thपढ़ो as the spu context moves through various well defined
	 * state transitions, but अगर the context is lazily loaded its
	 * utilization statistics are not updated as the controlling thपढ़ो
	 * is not tightly coupled with the execution of the spu context.  We
	 * calculate and apply the समय delta from the last recorded state
	 * of the spu context.
	 */
	अगर (ctx->spu && ctx->stats.util_state == state) अणु
		समय += kसमय_get_ns() - ctx->stats.tstamp;
	पूर्ण

	वापस समय / NSEC_PER_MSEC;
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ spufs_slb_flts(काष्ठा spu_context *ctx)
अणु
	अचिन्हित दीर्घ दीर्घ slb_flts = ctx->stats.slb_flt;

	अगर (ctx->state == SPU_STATE_RUNNABLE) अणु
		slb_flts += (ctx->spu->stats.slb_flt -
			     ctx->stats.slb_flt_base);
	पूर्ण

	वापस slb_flts;
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ spufs_class2_पूर्णांकrs(काष्ठा spu_context *ctx)
अणु
	अचिन्हित दीर्घ दीर्घ class2_पूर्णांकrs = ctx->stats.class2_पूर्णांकr;

	अगर (ctx->state == SPU_STATE_RUNNABLE) अणु
		class2_पूर्णांकrs += (ctx->spu->stats.class2_पूर्णांकr -
				 ctx->stats.class2_पूर्णांकr_base);
	पूर्ण

	वापस class2_पूर्णांकrs;
पूर्ण


अटल पूर्णांक spufs_show_stat(काष्ठा seq_file *s, व्योम *निजी)
अणु
	काष्ठा spu_context *ctx = s->निजी;
	पूर्णांक ret;

	ret = spu_acquire(ctx);
	अगर (ret)
		वापस ret;

	seq_म_लिखो(s, "%s %llu %llu %llu %llu "
		      "%llu %llu %llu %llu %llu %llu %llu %llu\n",
		ctx_state_names[ctx->stats.util_state],
		spufs_acct_समय(ctx, SPU_UTIL_USER),
		spufs_acct_समय(ctx, SPU_UTIL_SYSTEM),
		spufs_acct_समय(ctx, SPU_UTIL_IOWAIT),
		spufs_acct_समय(ctx, SPU_UTIL_IDLE_LOADED),
		ctx->stats.vol_ctx_चयन,
		ctx->stats.invol_ctx_चयन,
		spufs_slb_flts(ctx),
		ctx->stats.hash_flt,
		ctx->stats.min_flt,
		ctx->stats.maj_flt,
		spufs_class2_पूर्णांकrs(ctx),
		ctx->stats.libassist);
	spu_release(ctx);
	वापस 0;
पूर्ण

अटल पूर्णांक spufs_stat_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, spufs_show_stat, SPUFS_I(inode)->i_ctx);
पूर्ण

अटल स्थिर काष्ठा file_operations spufs_stat_fops = अणु
	.खोलो		= spufs_stat_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

अटल अंतरभूत पूर्णांक spufs_चयन_log_used(काष्ठा spu_context *ctx)
अणु
	वापस (ctx->चयन_log->head - ctx->चयन_log->tail) %
		SWITCH_LOG_बफ_मानE;
पूर्ण

अटल अंतरभूत पूर्णांक spufs_चयन_log_avail(काष्ठा spu_context *ctx)
अणु
	वापस SWITCH_LOG_बफ_मानE - spufs_चयन_log_used(ctx);
पूर्ण

अटल पूर्णांक spufs_चयन_log_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा spu_context *ctx = SPUFS_I(inode)->i_ctx;
	पूर्णांक rc;

	rc = spu_acquire(ctx);
	अगर (rc)
		वापस rc;

	अगर (ctx->चयन_log) अणु
		rc = -EBUSY;
		जाओ out;
	पूर्ण

	ctx->चयन_log = kदो_स्मृति(काष्ठा_size(ctx->चयन_log, log,
				  SWITCH_LOG_बफ_मानE), GFP_KERNEL);

	अगर (!ctx->चयन_log) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	ctx->चयन_log->head = ctx->चयन_log->tail = 0;
	init_रुकोqueue_head(&ctx->चयन_log->रुको);
	rc = 0;

out:
	spu_release(ctx);
	वापस rc;
पूर्ण

अटल पूर्णांक spufs_चयन_log_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा spu_context *ctx = SPUFS_I(inode)->i_ctx;
	पूर्णांक rc;

	rc = spu_acquire(ctx);
	अगर (rc)
		वापस rc;

	kमुक्त(ctx->चयन_log);
	ctx->चयन_log = शून्य;
	spu_release(ctx);

	वापस 0;
पूर्ण

अटल पूर्णांक चयन_log_sprपूर्णांक(काष्ठा spu_context *ctx, अक्षर *tbuf, पूर्णांक n)
अणु
	काष्ठा चयन_log_entry *p;

	p = ctx->चयन_log->log + ctx->चयन_log->tail % SWITCH_LOG_बफ_मानE;

	वापस snम_लिखो(tbuf, n, "%llu.%09u %d %u %u %llu\n",
			(अचिन्हित दीर्घ दीर्घ) p->tstamp.tv_sec,
			(अचिन्हित पूर्णांक) p->tstamp.tv_nsec,
			p->spu_id,
			(अचिन्हित पूर्णांक) p->type,
			(अचिन्हित पूर्णांक) p->val,
			(अचिन्हित दीर्घ दीर्घ) p->समयbase);
पूर्ण

अटल sमाप_प्रकार spufs_चयन_log_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			     माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा spu_context *ctx = SPUFS_I(inode)->i_ctx;
	पूर्णांक error = 0, cnt = 0;

	अगर (!buf)
		वापस -EINVAL;

	error = spu_acquire(ctx);
	अगर (error)
		वापस error;

	जबतक (cnt < len) अणु
		अक्षर tbuf[128];
		पूर्णांक width;

		अगर (spufs_चयन_log_used(ctx) == 0) अणु
			अगर (cnt > 0) अणु
				/* If there's data पढ़ोy to go, we can
				 * just वापस straight away */
				अवरोध;

			पूर्ण अन्यथा अगर (file->f_flags & O_NONBLOCK) अणु
				error = -EAGAIN;
				अवरोध;

			पूर्ण अन्यथा अणु
				/* spufs_रुको will drop the mutex and
				 * re-acquire, but since we're in पढ़ो(), the
				 * file cannot be _released (and so
				 * ctx->चयन_log is stable).
				 */
				error = spufs_रुको(ctx->चयन_log->रुको,
						spufs_चयन_log_used(ctx) > 0);

				/* On error, spufs_रुको वापसs without the
				 * state mutex held */
				अगर (error)
					वापस error;

				/* We may have had entries पढ़ो from underneath
				 * us जबतक we dropped the mutex in spufs_रुको,
				 * so re-check */
				अगर (spufs_चयन_log_used(ctx) == 0)
					जारी;
			पूर्ण
		पूर्ण

		width = चयन_log_sprपूर्णांक(ctx, tbuf, माप(tbuf));
		अगर (width < len)
			ctx->चयन_log->tail =
				(ctx->चयन_log->tail + 1) %
				 SWITCH_LOG_बफ_मानE;
		अन्यथा
			/* If the record is greater than space available वापस
			 * partial buffer (so far) */
			अवरोध;

		error = copy_to_user(buf + cnt, tbuf, width);
		अगर (error)
			अवरोध;
		cnt += width;
	पूर्ण

	spu_release(ctx);

	वापस cnt == 0 ? error : cnt;
पूर्ण

अटल __poll_t spufs_चयन_log_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा spu_context *ctx = SPUFS_I(inode)->i_ctx;
	__poll_t mask = 0;
	पूर्णांक rc;

	poll_रुको(file, &ctx->चयन_log->रुको, रुको);

	rc = spu_acquire(ctx);
	अगर (rc)
		वापस rc;

	अगर (spufs_चयन_log_used(ctx) > 0)
		mask |= EPOLLIN;

	spu_release(ctx);

	वापस mask;
पूर्ण

अटल स्थिर काष्ठा file_operations spufs_चयन_log_fops = अणु
	.खोलो		= spufs_चयन_log_खोलो,
	.पढ़ो		= spufs_चयन_log_पढ़ो,
	.poll		= spufs_चयन_log_poll,
	.release	= spufs_चयन_log_release,
	.llseek		= no_llseek,
पूर्ण;

/**
 * Log a context चयन event to a चयन log पढ़ोer.
 *
 * Must be called with ctx->state_mutex held.
 */
व्योम spu_चयन_log_notअगरy(काष्ठा spu *spu, काष्ठा spu_context *ctx,
		u32 type, u32 val)
अणु
	अगर (!ctx->चयन_log)
		वापस;

	अगर (spufs_चयन_log_avail(ctx) > 1) अणु
		काष्ठा चयन_log_entry *p;

		p = ctx->चयन_log->log + ctx->चयन_log->head;
		kसमय_get_ts64(&p->tstamp);
		p->समयbase = get_tb();
		p->spu_id = spu ? spu->number : -1;
		p->type = type;
		p->val = val;

		ctx->चयन_log->head =
			(ctx->चयन_log->head + 1) % SWITCH_LOG_बफ_मानE;
	पूर्ण

	wake_up(&ctx->चयन_log->रुको);
पूर्ण

अटल पूर्णांक spufs_show_ctx(काष्ठा seq_file *s, व्योम *निजी)
अणु
	काष्ठा spu_context *ctx = s->निजी;
	u64 mfc_control_RW;

	mutex_lock(&ctx->state_mutex);
	अगर (ctx->spu) अणु
		काष्ठा spu *spu = ctx->spu;
		काष्ठा spu_priv2 __iomem *priv2 = spu->priv2;

		spin_lock_irq(&spu->रेजिस्टर_lock);
		mfc_control_RW = in_be64(&priv2->mfc_control_RW);
		spin_unlock_irq(&spu->रेजिस्टर_lock);
	पूर्ण अन्यथा अणु
		काष्ठा spu_state *csa = &ctx->csa;

		mfc_control_RW = csa->priv2.mfc_control_RW;
	पूर्ण

	seq_म_लिखो(s, "%c flgs(%lx) sflgs(%lx) pri(%d) ts(%d) spu(%02d)"
		" %c %llx %llx %llx %llx %x %x\n",
		ctx->state == SPU_STATE_SAVED ? 'S' : 'R',
		ctx->flags,
		ctx->sched_flags,
		ctx->prio,
		ctx->समय_slice,
		ctx->spu ? ctx->spu->number : -1,
		!list_empty(&ctx->rq) ? 'q' : ' ',
		ctx->csa.class_0_pending,
		ctx->csa.class_0_dar,
		ctx->csa.class_1_dsisr,
		mfc_control_RW,
		ctx->ops->runcntl_पढ़ो(ctx),
		ctx->ops->status_पढ़ो(ctx));

	mutex_unlock(&ctx->state_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक spufs_ctx_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, spufs_show_ctx, SPUFS_I(inode)->i_ctx);
पूर्ण

अटल स्थिर काष्ठा file_operations spufs_ctx_fops = अणु
	.खोलो           = spufs_ctx_खोलो,
	.पढ़ो           = seq_पढ़ो,
	.llseek         = seq_lseek,
	.release        = single_release,
पूर्ण;

स्थिर काष्ठा spufs_tree_descr spufs_dir_contents[] = अणु
	अणु "capabilities", &spufs_caps_fops, 0444, पूर्ण,
	अणु "mem",  &spufs_mem_fops,  0666, LS_SIZE, पूर्ण,
	अणु "regs", &spufs_regs_fops,  0666, माप(काष्ठा spu_reg128[128]), पूर्ण,
	अणु "mbox", &spufs_mbox_fops, 0444, पूर्ण,
	अणु "ibox", &spufs_ibox_fops, 0444, पूर्ण,
	अणु "wbox", &spufs_wbox_fops, 0222, पूर्ण,
	अणु "mbox_stat", &spufs_mbox_stat_fops, 0444, माप(u32), पूर्ण,
	अणु "ibox_stat", &spufs_ibox_stat_fops, 0444, माप(u32), पूर्ण,
	अणु "wbox_stat", &spufs_wbox_stat_fops, 0444, माप(u32), पूर्ण,
	अणु "signal1", &spufs_संकेत1_fops, 0666, पूर्ण,
	अणु "signal2", &spufs_संकेत2_fops, 0666, पूर्ण,
	अणु "signal1_type", &spufs_संकेत1_type, 0666, पूर्ण,
	अणु "signal2_type", &spufs_संकेत2_type, 0666, पूर्ण,
	अणु "cntl", &spufs_cntl_fops,  0666, पूर्ण,
	अणु "fpcr", &spufs_fpcr_fops, 0666, माप(काष्ठा spu_reg128), पूर्ण,
	अणु "lslr", &spufs_lslr_ops, 0444, पूर्ण,
	अणु "mfc", &spufs_mfc_fops, 0666, पूर्ण,
	अणु "mss", &spufs_mss_fops, 0666, पूर्ण,
	अणु "npc", &spufs_npc_ops, 0666, पूर्ण,
	अणु "srr0", &spufs_srr0_ops, 0666, पूर्ण,
	अणु "decr", &spufs_decr_ops, 0666, पूर्ण,
	अणु "decr_status", &spufs_decr_status_ops, 0666, पूर्ण,
	अणु "event_mask", &spufs_event_mask_ops, 0666, पूर्ण,
	अणु "event_status", &spufs_event_status_ops, 0444, पूर्ण,
	अणु "psmap", &spufs_psmap_fops, 0666, SPUFS_PS_MAP_SIZE, पूर्ण,
	अणु "phys-id", &spufs_id_ops, 0666, पूर्ण,
	अणु "object-id", &spufs_object_id_ops, 0666, पूर्ण,
	अणु "mbox_info", &spufs_mbox_info_fops, 0444, माप(u32), पूर्ण,
	अणु "ibox_info", &spufs_ibox_info_fops, 0444, माप(u32), पूर्ण,
	अणु "wbox_info", &spufs_wbox_info_fops, 0444, माप(u32), पूर्ण,
	अणु "dma_info", &spufs_dma_info_fops, 0444,
		माप(काष्ठा spu_dma_info), पूर्ण,
	अणु "proxydma_info", &spufs_proxydma_info_fops, 0444,
		माप(काष्ठा spu_proxydma_info)पूर्ण,
	अणु "tid", &spufs_tid_fops, 0444, पूर्ण,
	अणु "stat", &spufs_stat_fops, 0444, पूर्ण,
	अणु "switch_log", &spufs_चयन_log_fops, 0444 पूर्ण,
	अणुपूर्ण,
पूर्ण;

स्थिर काष्ठा spufs_tree_descr spufs_dir_nosched_contents[] = अणु
	अणु "capabilities", &spufs_caps_fops, 0444, पूर्ण,
	अणु "mem",  &spufs_mem_fops,  0666, LS_SIZE, पूर्ण,
	अणु "mbox", &spufs_mbox_fops, 0444, पूर्ण,
	अणु "ibox", &spufs_ibox_fops, 0444, पूर्ण,
	अणु "wbox", &spufs_wbox_fops, 0222, पूर्ण,
	अणु "mbox_stat", &spufs_mbox_stat_fops, 0444, माप(u32), पूर्ण,
	अणु "ibox_stat", &spufs_ibox_stat_fops, 0444, माप(u32), पूर्ण,
	अणु "wbox_stat", &spufs_wbox_stat_fops, 0444, माप(u32), पूर्ण,
	अणु "signal1", &spufs_संकेत1_nosched_fops, 0222, पूर्ण,
	अणु "signal2", &spufs_संकेत2_nosched_fops, 0222, पूर्ण,
	अणु "signal1_type", &spufs_संकेत1_type, 0666, पूर्ण,
	अणु "signal2_type", &spufs_संकेत2_type, 0666, पूर्ण,
	अणु "mss", &spufs_mss_fops, 0666, पूर्ण,
	अणु "mfc", &spufs_mfc_fops, 0666, पूर्ण,
	अणु "cntl", &spufs_cntl_fops,  0666, पूर्ण,
	अणु "npc", &spufs_npc_ops, 0666, पूर्ण,
	अणु "psmap", &spufs_psmap_fops, 0666, SPUFS_PS_MAP_SIZE, पूर्ण,
	अणु "phys-id", &spufs_id_ops, 0666, पूर्ण,
	अणु "object-id", &spufs_object_id_ops, 0666, पूर्ण,
	अणु "tid", &spufs_tid_fops, 0444, पूर्ण,
	अणु "stat", &spufs_stat_fops, 0444, पूर्ण,
	अणुपूर्ण,
पूर्ण;

स्थिर काष्ठा spufs_tree_descr spufs_dir_debug_contents[] = अणु
	अणु ".ctx", &spufs_ctx_fops, 0444, पूर्ण,
	अणुपूर्ण,
पूर्ण;

स्थिर काष्ठा spufs_coredump_पढ़ोer spufs_coredump_पढ़ो[] = अणु
	अणु "regs", spufs_regs_dump, शून्य, माप(काष्ठा spu_reg128[128])पूर्ण,
	अणु "fpcr", spufs_fpcr_dump, शून्य, माप(काष्ठा spu_reg128) पूर्ण,
	अणु "lslr", शून्य, spufs_lslr_get, 19 पूर्ण,
	अणु "decr", शून्य, spufs_decr_get, 19 पूर्ण,
	अणु "decr_status", शून्य, spufs_decr_status_get, 19 पूर्ण,
	अणु "mem", spufs_mem_dump, शून्य, LS_SIZE, पूर्ण,
	अणु "signal1", spufs_संकेत1_dump, शून्य, माप(u32) पूर्ण,
	अणु "signal1_type", शून्य, spufs_संकेत1_type_get, 19 पूर्ण,
	अणु "signal2", spufs_संकेत2_dump, शून्य, माप(u32) पूर्ण,
	अणु "signal2_type", शून्य, spufs_संकेत2_type_get, 19 पूर्ण,
	अणु "event_mask", शून्य, spufs_event_mask_get, 19 पूर्ण,
	अणु "event_status", शून्य, spufs_event_status_get, 19 पूर्ण,
	अणु "mbox_info", spufs_mbox_info_dump, शून्य, माप(u32) पूर्ण,
	अणु "ibox_info", spufs_ibox_info_dump, शून्य, माप(u32) पूर्ण,
	अणु "wbox_info", spufs_wbox_info_dump, शून्य, 4 * माप(u32)पूर्ण,
	अणु "dma_info", spufs_dma_info_dump, शून्य, माप(काष्ठा spu_dma_info)पूर्ण,
	अणु "proxydma_info", spufs_proxydma_info_dump,
			   शून्य, माप(काष्ठा spu_proxydma_info)पूर्ण,
	अणु "object-id", शून्य, spufs_object_id_get, 19 पूर्ण,
	अणु "npc", शून्य, spufs_npc_get, 19 पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;
