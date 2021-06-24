<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Access to PCI I/O memory from user space programs.
 *
 * Copyright IBM Corp. 2014
 * Author(s): Alexey Ishchuk <aishchuk@linux.vnet.ibm.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <यंत्र/pci_पन.स>
#समावेश <यंत्र/pci_debug.h>

अटल अंतरभूत व्योम zpci_err_mmio(u8 cc, u8 status, u64 offset)
अणु
	काष्ठा अणु
		u64 offset;
		u8 cc;
		u8 status;
	पूर्ण data = अणुoffset, cc, statusपूर्ण;

	zpci_err_hex(&data, माप(data));
पूर्ण

अटल अंतरभूत पूर्णांक __pcistb_mio_inuser(
		व्योम __iomem *ioaddr, स्थिर व्योम __user *src,
		u64 len, u8 *status)
अणु
	पूर्णांक cc = -ENXIO;

	यंत्र अस्थिर (
		"       sacf 256\n"
		"0:     .insn   rsy,0xeb00000000d4,%[len],%[ioaddr],%[src]\n"
		"1:     ipm     %[cc]\n"
		"       srl     %[cc],28\n"
		"2:     sacf 768\n"
		EX_TABLE(0b, 2b) EX_TABLE(1b, 2b)
		: [cc] "+d" (cc), [len] "+d" (len)
		: [ioaddr] "a" (ioaddr), [src] "Q" (*((u8 __क्रमce *)src))
		: "cc", "memory");
	*status = len >> 24 & 0xff;
	वापस cc;
पूर्ण

अटल अंतरभूत पूर्णांक __pcistg_mio_inuser(
		व्योम __iomem *ioaddr, स्थिर व्योम __user *src,
		u64 ulen, u8 *status)
अणु
	रेजिस्टर u64 addr यंत्र("2") = (u64 __क्रमce) ioaddr;
	रेजिस्टर u64 len यंत्र("3") = ulen;
	पूर्णांक cc = -ENXIO;
	u64 val = 0;
	u64 cnt = ulen;
	u8 पंचांगp;

	/*
	 * copy 0 < @len <= 8 bytes from @src पूर्णांकo the right most bytes of
	 * a रेजिस्टर, then store it to PCI at @ioaddr जबतक in secondary
	 * address space. pcistg then uses the user mappings.
	 */
	यंत्र अस्थिर (
		"       sacf    256\n"
		"0:     llgc    %[tmp],0(%[src])\n"
		"       sllg    %[val],%[val],8\n"
		"       aghi    %[src],1\n"
		"       ogr     %[val],%[tmp]\n"
		"       brctg   %[cnt],0b\n"
		"1:     .insn   rre,0xb9d40000,%[val],%[ioaddr]\n"
		"2:     ipm     %[cc]\n"
		"       srl     %[cc],28\n"
		"3:     sacf    768\n"
		EX_TABLE(0b, 3b) EX_TABLE(1b, 3b) EX_TABLE(2b, 3b)
		:
		[src] "+a" (src), [cnt] "+d" (cnt),
		[val] "+d" (val), [पंचांगp] "=d" (पंचांगp),
		[len] "+d" (len), [cc] "+d" (cc),
		[ioaddr] "+a" (addr)
		:: "cc", "memory");
	*status = len >> 24 & 0xff;

	/* did we पढ़ो everything from user memory? */
	अगर (!cc && cnt != 0)
		cc = -EFAULT;

	वापस cc;
पूर्ण

अटल अंतरभूत पूर्णांक __स_नकल_toio_inuser(व्योम __iomem *dst,
				   स्थिर व्योम __user *src, माप_प्रकार n)
अणु
	पूर्णांक size, rc = 0;
	u8 status = 0;

	अगर (!src)
		वापस -EINVAL;

	जबतक (n > 0) अणु
		size = zpci_get_max_ग_लिखो_size((u64 __क्रमce) dst,
					       (u64 __क्रमce) src, n,
					       ZPCI_MAX_WRITE_SIZE);
		अगर (size > 8) /* मुख्य path */
			rc = __pcistb_mio_inuser(dst, src, size, &status);
		अन्यथा
			rc = __pcistg_mio_inuser(dst, src, size, &status);
		अगर (rc)
			अवरोध;
		src += size;
		dst += size;
		n -= size;
	पूर्ण
	अगर (rc)
		zpci_err_mmio(rc, status, (__क्रमce u64) dst);
	वापस rc;
पूर्ण

SYSCALL_DEFINE3(s390_pci_mmio_ग_लिखो, अचिन्हित दीर्घ, mmio_addr,
		स्थिर व्योम __user *, user_buffer, माप_प्रकार, length)
अणु
	u8 local_buf[64];
	व्योम __iomem *io_addr;
	व्योम *buf;
	काष्ठा vm_area_काष्ठा *vma;
	pte_t *ptep;
	spinlock_t *ptl;
	दीर्घ ret;

	अगर (!zpci_is_enabled())
		वापस -ENODEV;

	अगर (length <= 0 || PAGE_SIZE - (mmio_addr & ~PAGE_MASK) < length)
		वापस -EINVAL;

	/*
	 * We only support ग_लिखो access to MIO capable devices अगर we are on
	 * a MIO enabled प्रणाली. Otherwise we would have to check क्रम every
	 * address अगर it is a special ZPCI_ADDR and would have to करो
	 * a pfn lookup which we करोn't need क्रम MIO capable devices.  Currently
	 * ISM devices are the only devices without MIO support and there is no
	 * known need क्रम accessing these from userspace.
	 */
	अगर (अटल_branch_likely(&have_mio)) अणु
		ret = __स_नकल_toio_inuser((व्योम  __iomem *) mmio_addr,
					user_buffer,
					length);
		वापस ret;
	पूर्ण

	अगर (length > 64) अणु
		buf = kदो_स्मृति(length, GFP_KERNEL);
		अगर (!buf)
			वापस -ENOMEM;
	पूर्ण अन्यथा
		buf = local_buf;

	ret = -EFAULT;
	अगर (copy_from_user(buf, user_buffer, length))
		जाओ out_मुक्त;

	mmap_पढ़ो_lock(current->mm);
	ret = -EINVAL;
	vma = find_vma(current->mm, mmio_addr);
	अगर (!vma)
		जाओ out_unlock_mmap;
	अगर (!(vma->vm_flags & (VM_IO | VM_PFNMAP)))
		जाओ out_unlock_mmap;
	ret = -EACCES;
	अगर (!(vma->vm_flags & VM_WRITE))
		जाओ out_unlock_mmap;

	ret = follow_pte(vma->vm_mm, mmio_addr, &ptep, &ptl);
	अगर (ret)
		जाओ out_unlock_mmap;

	io_addr = (व्योम __iomem *)((pte_pfn(*ptep) << PAGE_SHIFT) |
			(mmio_addr & ~PAGE_MASK));

	अगर ((अचिन्हित दीर्घ) io_addr < ZPCI_IOMAP_ADDR_BASE)
		जाओ out_unlock_pt;

	ret = zpci_स_नकल_toio(io_addr, buf, length);
out_unlock_pt:
	pte_unmap_unlock(ptep, ptl);
out_unlock_mmap:
	mmap_पढ़ो_unlock(current->mm);
out_मुक्त:
	अगर (buf != local_buf)
		kमुक्त(buf);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक __pcilg_mio_inuser(
		व्योम __user *dst, स्थिर व्योम __iomem *ioaddr,
		u64 ulen, u8 *status)
अणु
	रेजिस्टर u64 addr यंत्र("2") = (u64 __क्रमce) ioaddr;
	रेजिस्टर u64 len यंत्र("3") = ulen;
	u64 cnt = ulen;
	पूर्णांक shअगरt = ulen * 8;
	पूर्णांक cc = -ENXIO;
	u64 val, पंचांगp;

	/*
	 * पढ़ो 0 < @len <= 8 bytes from the PCI memory mapped at @ioaddr (in
	 * user space) पूर्णांकo a रेजिस्टर using pcilg then store these bytes at
	 * user address @dst
	 */
	यंत्र अस्थिर (
		"       sacf    256\n"
		"0:     .insn   rre,0xb9d60000,%[val],%[ioaddr]\n"
		"1:     ipm     %[cc]\n"
		"       srl     %[cc],28\n"
		"       ltr     %[cc],%[cc]\n"
		"       jne     4f\n"
		"2:     ahi     %[shift],-8\n"
		"       srlg    %[tmp],%[val],0(%[shift])\n"
		"3:     stc     %[tmp],0(%[dst])\n"
		"       aghi    %[dst],1\n"
		"       brctg   %[cnt],2b\n"
		"4:     sacf    768\n"
		EX_TABLE(0b, 4b) EX_TABLE(1b, 4b) EX_TABLE(3b, 4b)
		:
		[cc] "+d" (cc), [val] "=d" (val), [len] "+d" (len),
		[dst] "+a" (dst), [cnt] "+d" (cnt), [पंचांगp] "=d" (पंचांगp),
		[shअगरt] "+d" (shअगरt)
		:
		[ioaddr] "a" (addr)
		: "cc", "memory");

	/* did we ग_लिखो everything to the user space buffer? */
	अगर (!cc && cnt != 0)
		cc = -EFAULT;

	*status = len >> 24 & 0xff;
	वापस cc;
पूर्ण

अटल अंतरभूत पूर्णांक __स_नकल_fromio_inuser(व्योम __user *dst,
				     स्थिर व्योम __iomem *src,
				     अचिन्हित दीर्घ n)
अणु
	पूर्णांक size, rc = 0;
	u8 status;

	जबतक (n > 0) अणु
		size = zpci_get_max_ग_लिखो_size((u64 __क्रमce) src,
					       (u64 __क्रमce) dst, n,
					       ZPCI_MAX_READ_SIZE);
		rc = __pcilg_mio_inuser(dst, src, size, &status);
		अगर (rc)
			अवरोध;
		src += size;
		dst += size;
		n -= size;
	पूर्ण
	अगर (rc)
		zpci_err_mmio(rc, status, (__क्रमce u64) dst);
	वापस rc;
पूर्ण

SYSCALL_DEFINE3(s390_pci_mmio_पढ़ो, अचिन्हित दीर्घ, mmio_addr,
		व्योम __user *, user_buffer, माप_प्रकार, length)
अणु
	u8 local_buf[64];
	व्योम __iomem *io_addr;
	व्योम *buf;
	काष्ठा vm_area_काष्ठा *vma;
	pte_t *ptep;
	spinlock_t *ptl;
	दीर्घ ret;

	अगर (!zpci_is_enabled())
		वापस -ENODEV;

	अगर (length <= 0 || PAGE_SIZE - (mmio_addr & ~PAGE_MASK) < length)
		वापस -EINVAL;

	/*
	 * We only support पढ़ो access to MIO capable devices अगर we are on
	 * a MIO enabled प्रणाली. Otherwise we would have to check क्रम every
	 * address अगर it is a special ZPCI_ADDR and would have to करो
	 * a pfn lookup which we करोn't need क्रम MIO capable devices.  Currently
	 * ISM devices are the only devices without MIO support and there is no
	 * known need क्रम accessing these from userspace.
	 */
	अगर (अटल_branch_likely(&have_mio)) अणु
		ret = __स_नकल_fromio_inuser(
				user_buffer, (स्थिर व्योम __iomem *)mmio_addr,
				length);
		वापस ret;
	पूर्ण

	अगर (length > 64) अणु
		buf = kदो_स्मृति(length, GFP_KERNEL);
		अगर (!buf)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		buf = local_buf;
	पूर्ण

	mmap_पढ़ो_lock(current->mm);
	ret = -EINVAL;
	vma = find_vma(current->mm, mmio_addr);
	अगर (!vma)
		जाओ out_unlock_mmap;
	अगर (!(vma->vm_flags & (VM_IO | VM_PFNMAP)))
		जाओ out_unlock_mmap;
	ret = -EACCES;
	अगर (!(vma->vm_flags & VM_WRITE))
		जाओ out_unlock_mmap;

	ret = follow_pte(vma->vm_mm, mmio_addr, &ptep, &ptl);
	अगर (ret)
		जाओ out_unlock_mmap;

	io_addr = (व्योम __iomem *)((pte_pfn(*ptep) << PAGE_SHIFT) |
			(mmio_addr & ~PAGE_MASK));

	अगर ((अचिन्हित दीर्घ) io_addr < ZPCI_IOMAP_ADDR_BASE) अणु
		ret = -EFAULT;
		जाओ out_unlock_pt;
	पूर्ण
	ret = zpci_स_नकल_fromio(buf, io_addr, length);

out_unlock_pt:
	pte_unmap_unlock(ptep, ptl);
out_unlock_mmap:
	mmap_पढ़ो_unlock(current->mm);

	अगर (!ret && copy_to_user(user_buffer, buf, length))
		ret = -EFAULT;

	अगर (buf != local_buf)
		kमुक्त(buf);
	वापस ret;
पूर्ण
