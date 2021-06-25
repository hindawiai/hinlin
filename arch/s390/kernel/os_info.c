<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * OS info memory पूर्णांकerface
 *
 * Copyright IBM Corp. 2012
 * Author(s): Michael Holzheu <holzheu@linux.vnet.ibm.com>
 */

#घोषणा KMSG_COMPONENT "os_info"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/crash_dump.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/checksum.h>
#समावेश <यंत्र/lowcore.h>
#समावेश <यंत्र/os_info.h>

/*
 * OS info काष्ठाure has to be page aligned
 */
अटल काष्ठा os_info os_info __page_aligned_data;

/*
 * Compute checksum over OS info काष्ठाure
 */
u32 os_info_csum(काष्ठा os_info *os_info)
अणु
	पूर्णांक size = माप(*os_info) - दुरत्व(काष्ठा os_info, version_major);
	वापस (__क्रमce u32)csum_partial(&os_info->version_major, size, 0);
पूर्ण

/*
 * Add crashkernel info to OS info and update checksum
 */
व्योम os_info_crashkernel_add(अचिन्हित दीर्घ base, अचिन्हित दीर्घ size)
अणु
	os_info.crashkernel_addr = (u64)(अचिन्हित दीर्घ)base;
	os_info.crashkernel_size = (u64)(अचिन्हित दीर्घ)size;
	os_info.csum = os_info_csum(&os_info);
पूर्ण

/*
 * Add OS info entry and update checksum
 */
व्योम os_info_entry_add(पूर्णांक nr, व्योम *ptr, u64 size)
अणु
	os_info.entry[nr].addr = (u64)(अचिन्हित दीर्घ)ptr;
	os_info.entry[nr].size = size;
	os_info.entry[nr].csum = (__क्रमce u32)csum_partial(ptr, size, 0);
	os_info.csum = os_info_csum(&os_info);
पूर्ण

/*
 * Initialize OS info काष्ठाure and set lowcore poपूर्णांकer
 */
व्योम __init os_info_init(व्योम)
अणु
	व्योम *ptr = &os_info;

	os_info.version_major = OS_INFO_VERSION_MAJOR;
	os_info.version_minor = OS_INFO_VERSION_MINOR;
	os_info.magic = OS_INFO_MAGIC;
	os_info.csum = os_info_csum(&os_info);
	mem_assign_असलolute(S390_lowcore.os_info, (अचिन्हित दीर्घ) ptr);
पूर्ण

#अगर_घोषित CONFIG_CRASH_DUMP

अटल काष्ठा os_info *os_info_old;

/*
 * Allocate and copy OS info entry from oldmem
 */
अटल व्योम os_info_old_alloc(पूर्णांक nr, पूर्णांक align)
अणु
	अचिन्हित दीर्घ addr, size = 0;
	अक्षर *buf, *buf_align, *msg;
	u32 csum;

	addr = os_info_old->entry[nr].addr;
	अगर (!addr) अणु
		msg = "not available";
		जाओ fail;
	पूर्ण
	size = os_info_old->entry[nr].size;
	buf = kदो_स्मृति(size + align - 1, GFP_KERNEL);
	अगर (!buf) अणु
		msg = "alloc failed";
		जाओ fail;
	पूर्ण
	buf_align = PTR_ALIGN(buf, align);
	अगर (copy_oldmem_kernel(buf_align, (व्योम *) addr, size)) अणु
		msg = "copy failed";
		जाओ fail_मुक्त;
	पूर्ण
	csum = (__क्रमce u32)csum_partial(buf_align, size, 0);
	अगर (csum != os_info_old->entry[nr].csum) अणु
		msg = "checksum failed";
		जाओ fail_मुक्त;
	पूर्ण
	os_info_old->entry[nr].addr = (u64)(अचिन्हित दीर्घ)buf_align;
	msg = "copied";
	जाओ out;
fail_मुक्त:
	kमुक्त(buf);
fail:
	os_info_old->entry[nr].addr = 0;
out:
	pr_info("entry %i: %s (addr=0x%lx size=%lu)\n",
		nr, msg, addr, size);
पूर्ण

/*
 * Initialize os info and os info entries from oldmem
 */
अटल व्योम os_info_old_init(व्योम)
अणु
	अटल पूर्णांक os_info_init;
	अचिन्हित दीर्घ addr;

	अगर (os_info_init)
		वापस;
	अगर (!OLDMEM_BASE)
		जाओ fail;
	अगर (copy_oldmem_kernel(&addr, &S390_lowcore.os_info, माप(addr)))
		जाओ fail;
	अगर (addr == 0 || addr % PAGE_SIZE)
		जाओ fail;
	os_info_old = kzalloc(माप(*os_info_old), GFP_KERNEL);
	अगर (!os_info_old)
		जाओ fail;
	अगर (copy_oldmem_kernel(os_info_old, (व्योम *) addr,
			       माप(*os_info_old)))
		जाओ fail_मुक्त;
	अगर (os_info_old->magic != OS_INFO_MAGIC)
		जाओ fail_मुक्त;
	अगर (os_info_old->csum != os_info_csum(os_info_old))
		जाओ fail_मुक्त;
	अगर (os_info_old->version_major > OS_INFO_VERSION_MAJOR)
		जाओ fail_मुक्त;
	os_info_old_alloc(OS_INFO_VMCOREINFO, 1);
	os_info_old_alloc(OS_INFO_REIPL_BLOCK, 1);
	pr_info("crashkernel: addr=0x%lx size=%lu\n",
		(अचिन्हित दीर्घ) os_info_old->crashkernel_addr,
		(अचिन्हित दीर्घ) os_info_old->crashkernel_size);
	os_info_init = 1;
	वापस;
fail_मुक्त:
	kमुक्त(os_info_old);
fail:
	os_info_init = 1;
	os_info_old = शून्य;
पूर्ण

/*
 * Return poपूर्णांकer to os inक्रम entry and its size
 */
व्योम *os_info_old_entry(पूर्णांक nr, अचिन्हित दीर्घ *size)
अणु
	os_info_old_init();

	अगर (!os_info_old)
		वापस शून्य;
	अगर (!os_info_old->entry[nr].addr)
		वापस शून्य;
	*size = (अचिन्हित दीर्घ) os_info_old->entry[nr].size;
	वापस (व्योम *)(अचिन्हित दीर्घ)os_info_old->entry[nr].addr;
पूर्ण
#पूर्ण_अगर
