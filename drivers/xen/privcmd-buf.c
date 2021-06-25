<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT

/******************************************************************************
 * privcmd-buf.c
 *
 * Mmap of hypercall buffers.
 *
 * Copyright (c) 2018 Juergen Gross
 */

#घोषणा pr_fmt(fmt) "xen:" KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>

#समावेश "privcmd.h"

MODULE_LICENSE("GPL");

काष्ठा privcmd_buf_निजी अणु
	काष्ठा mutex lock;
	काष्ठा list_head list;
पूर्ण;

काष्ठा privcmd_buf_vma_निजी अणु
	काष्ठा privcmd_buf_निजी *file_priv;
	काष्ठा list_head list;
	अचिन्हित पूर्णांक users;
	अचिन्हित पूर्णांक n_pages;
	काष्ठा page *pages[];
पूर्ण;

अटल पूर्णांक privcmd_buf_खोलो(काष्ठा inode *ino, काष्ठा file *file)
अणु
	काष्ठा privcmd_buf_निजी *file_priv;

	file_priv = kzalloc(माप(*file_priv), GFP_KERNEL);
	अगर (!file_priv)
		वापस -ENOMEM;

	mutex_init(&file_priv->lock);
	INIT_LIST_HEAD(&file_priv->list);

	file->निजी_data = file_priv;

	वापस 0;
पूर्ण

अटल व्योम privcmd_buf_vmapriv_मुक्त(काष्ठा privcmd_buf_vma_निजी *vma_priv)
अणु
	अचिन्हित पूर्णांक i;

	list_del(&vma_priv->list);

	क्रम (i = 0; i < vma_priv->n_pages; i++)
		__मुक्त_page(vma_priv->pages[i]);

	kमुक्त(vma_priv);
पूर्ण

अटल पूर्णांक privcmd_buf_release(काष्ठा inode *ino, काष्ठा file *file)
अणु
	काष्ठा privcmd_buf_निजी *file_priv = file->निजी_data;
	काष्ठा privcmd_buf_vma_निजी *vma_priv;

	mutex_lock(&file_priv->lock);

	जबतक (!list_empty(&file_priv->list)) अणु
		vma_priv = list_first_entry(&file_priv->list,
					    काष्ठा privcmd_buf_vma_निजी,
					    list);
		privcmd_buf_vmapriv_मुक्त(vma_priv);
	पूर्ण

	mutex_unlock(&file_priv->lock);

	kमुक्त(file_priv);

	वापस 0;
पूर्ण

अटल व्योम privcmd_buf_vma_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा privcmd_buf_vma_निजी *vma_priv = vma->vm_निजी_data;

	अगर (!vma_priv)
		वापस;

	mutex_lock(&vma_priv->file_priv->lock);
	vma_priv->users++;
	mutex_unlock(&vma_priv->file_priv->lock);
पूर्ण

अटल व्योम privcmd_buf_vma_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा privcmd_buf_vma_निजी *vma_priv = vma->vm_निजी_data;
	काष्ठा privcmd_buf_निजी *file_priv;

	अगर (!vma_priv)
		वापस;

	file_priv = vma_priv->file_priv;

	mutex_lock(&file_priv->lock);

	vma_priv->users--;
	अगर (!vma_priv->users)
		privcmd_buf_vmapriv_मुक्त(vma_priv);

	mutex_unlock(&file_priv->lock);
पूर्ण

अटल vm_fault_t privcmd_buf_vma_fault(काष्ठा vm_fault *vmf)
अणु
	pr_debug("fault: vma=%p %lx-%lx, pgoff=%lx, uv=%p\n",
		 vmf->vma, vmf->vma->vm_start, vmf->vma->vm_end,
		 vmf->pgoff, (व्योम *)vmf->address);

	वापस VM_FAULT_SIGBUS;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा privcmd_buf_vm_ops = अणु
	.खोलो = privcmd_buf_vma_खोलो,
	.बंद = privcmd_buf_vma_बंद,
	.fault = privcmd_buf_vma_fault,
पूर्ण;

अटल पूर्णांक privcmd_buf_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा privcmd_buf_निजी *file_priv = file->निजी_data;
	काष्ठा privcmd_buf_vma_निजी *vma_priv;
	अचिन्हित दीर्घ count = vma_pages(vma);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	अगर (!(vma->vm_flags & VM_SHARED))
		वापस -EINVAL;

	vma_priv = kzalloc(काष्ठा_size(vma_priv, pages, count), GFP_KERNEL);
	अगर (!vma_priv)
		वापस -ENOMEM;

	क्रम (i = 0; i < count; i++) अणु
		vma_priv->pages[i] = alloc_page(GFP_KERNEL | __GFP_ZERO);
		अगर (!vma_priv->pages[i])
			अवरोध;
		vma_priv->n_pages++;
	पूर्ण

	mutex_lock(&file_priv->lock);

	vma_priv->file_priv = file_priv;
	vma_priv->users = 1;

	vma->vm_flags |= VM_IO | VM_DONTEXPAND;
	vma->vm_ops = &privcmd_buf_vm_ops;
	vma->vm_निजी_data = vma_priv;

	list_add(&vma_priv->list, &file_priv->list);

	अगर (vma_priv->n_pages != count)
		ret = -ENOMEM;
	अन्यथा
		ret = vm_map_pages_zero(vma, vma_priv->pages,
						vma_priv->n_pages);

	अगर (ret)
		privcmd_buf_vmapriv_मुक्त(vma_priv);

	mutex_unlock(&file_priv->lock);

	वापस ret;
पूर्ण

स्थिर काष्ठा file_operations xen_privcmdbuf_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = privcmd_buf_खोलो,
	.release = privcmd_buf_release,
	.mmap = privcmd_buf_mmap,
पूर्ण;
EXPORT_SYMBOL_GPL(xen_privcmdbuf_fops);

काष्ठा miscdevice xen_privcmdbuf_dev = अणु
	.minor = MISC_DYNAMIC_MINOR,
	.name = "xen/hypercall",
	.fops = &xen_privcmdbuf_fops,
पूर्ण;
