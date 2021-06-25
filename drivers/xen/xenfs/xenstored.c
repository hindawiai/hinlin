<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>

#समावेश <xen/page.h>
#समावेश <xen/xenbus.h>

#समावेश "xenfs.h"

अटल sमाप_प्रकार xsd_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			    माप_प्रकार size, loff_t *off)
अणु
	स्थिर अक्षर *str = (स्थिर अक्षर *)file->निजी_data;
	वापस simple_पढ़ो_from_buffer(buf, size, off, str, म_माप(str));
पूर्ण

अटल पूर्णांक xsd_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	kमुक्त(file->निजी_data);
	वापस 0;
पूर्ण

अटल पूर्णांक xsd_kva_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	file->निजी_data = (व्योम *)kaप्र_लिखो(GFP_KERNEL, "0x%p",
					       xen_store_पूर्णांकerface);
	अगर (!file->निजी_data)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल पूर्णांक xsd_kva_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	माप_प्रकार size = vma->vm_end - vma->vm_start;

	अगर ((size > PAGE_SIZE) || (vma->vm_pgoff != 0))
		वापस -EINVAL;

	अगर (remap_pfn_range(vma, vma->vm_start,
			    virt_to_pfn(xen_store_पूर्णांकerface),
			    size, vma->vm_page_prot))
		वापस -EAGAIN;

	वापस 0;
पूर्ण

स्थिर काष्ठा file_operations xsd_kva_file_ops = अणु
	.खोलो = xsd_kva_खोलो,
	.mmap = xsd_kva_mmap,
	.पढ़ो = xsd_पढ़ो,
	.release = xsd_release,
पूर्ण;

अटल पूर्णांक xsd_port_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	file->निजी_data = (व्योम *)kaप्र_लिखो(GFP_KERNEL, "%d",
					       xen_store_evtchn);
	अगर (!file->निजी_data)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

स्थिर काष्ठा file_operations xsd_port_file_ops = अणु
	.खोलो = xsd_port_खोलो,
	.पढ़ो = xsd_पढ़ो,
	.release = xsd_release,
पूर्ण;
