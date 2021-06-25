<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/compat.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/smp.h>
#समावेश <linux/sem.h>
#समावेश <linux/msg.h>
#समावेश <linux/shm.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/mman.h>
#समावेश <linux/file.h>
#समावेश <linux/utsname.h>
#समावेश <linux/personality.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/elf.h>

#समावेश <यंत्र/elf.h>
#समावेश <यंत्र/ia32.h>

/*
 * Align a भव address to aव्योम aliasing in the I$ on AMD F15h.
 */
अटल अचिन्हित दीर्घ get_align_mask(व्योम)
अणु
	/* handle 32- and 64-bit हाल with a single conditional */
	अगर (va_align.flags < 0 || !(va_align.flags & (2 - mmap_is_ia32())))
		वापस 0;

	अगर (!(current->flags & PF_RANDOMIZE))
		वापस 0;

	वापस va_align.mask;
पूर्ण

/*
 * To aव्योम aliasing in the I$ on AMD F15h, the bits defined by the
 * va_align.bits, [12:upper_bit), are set to a अक्रमom value instead of
 * zeroing them. This अक्रमom value is computed once per boot. This क्रमm
 * of ASLR is known as "per-boot ASLR".
 *
 * To achieve this, the अक्रमom value is added to the info.align_offset
 * value beक्रमe calling vm_unmapped_area() or ORed directly to the
 * address.
 */
अटल अचिन्हित दीर्घ get_align_bits(व्योम)
अणु
	वापस va_align.bits & get_align_mask();
पूर्ण

अचिन्हित दीर्घ align_vdso_addr(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ align_mask = get_align_mask();
	addr = (addr + align_mask) & ~align_mask;
	वापस addr | get_align_bits();
पूर्ण

अटल पूर्णांक __init control_va_addr_alignment(अक्षर *str)
अणु
	/* guard against enabling this on other CPU families */
	अगर (va_align.flags < 0)
		वापस 1;

	अगर (*str == 0)
		वापस 1;

	अगर (*str == '=')
		str++;

	अगर (!म_भेद(str, "32"))
		va_align.flags = ALIGN_VA_32;
	अन्यथा अगर (!म_भेद(str, "64"))
		va_align.flags = ALIGN_VA_64;
	अन्यथा अगर (!म_भेद(str, "off"))
		va_align.flags = 0;
	अन्यथा अगर (!म_भेद(str, "on"))
		va_align.flags = ALIGN_VA_32 | ALIGN_VA_64;
	अन्यथा
		वापस 0;

	वापस 1;
पूर्ण
__setup("align_va_addr", control_va_addr_alignment);

SYSCALL_DEFINE6(mmap, अचिन्हित दीर्घ, addr, अचिन्हित दीर्घ, len,
		अचिन्हित दीर्घ, prot, अचिन्हित दीर्घ, flags,
		अचिन्हित दीर्घ, fd, अचिन्हित दीर्घ, off)
अणु
	अगर (off & ~PAGE_MASK)
		वापस -EINVAL;

	वापस ksys_mmap_pgoff(addr, len, prot, flags, fd, off >> PAGE_SHIFT);
पूर्ण

अटल व्योम find_start_end(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ flags,
		अचिन्हित दीर्घ *begin, अचिन्हित दीर्घ *end)
अणु
	अगर (!in_32bit_syscall() && (flags & MAP_32BIT)) अणु
		/* This is usually used needed to map code in small
		   model, so it needs to be in the first 31bit. Limit
		   it to that.  This means we need to move the
		   unmapped base करोwn क्रम this हाल. This can give
		   conflicts with the heap, but we assume that glibc
		   दो_स्मृति knows how to fall back to mmap. Give it 1GB
		   of playground क्रम now. -AK */
		*begin = 0x40000000;
		*end = 0x80000000;
		अगर (current->flags & PF_RANDOMIZE) अणु
			*begin = अक्रमomize_page(*begin, 0x02000000);
		पूर्ण
		वापस;
	पूर्ण

	*begin	= get_mmap_base(1);
	अगर (in_32bit_syscall())
		*end = task_size_32bit();
	अन्यथा
		*end = task_size_64bit(addr > DEFAULT_MAP_WINDOW);
पूर्ण

अचिन्हित दीर्घ
arch_get_unmapped_area(काष्ठा file *filp, अचिन्हित दीर्घ addr,
		अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा vm_unmapped_area_info info;
	अचिन्हित दीर्घ begin, end;

	अगर (flags & MAP_FIXED)
		वापस addr;

	find_start_end(addr, flags, &begin, &end);

	अगर (len > end)
		वापस -ENOMEM;

	अगर (addr) अणु
		addr = PAGE_ALIGN(addr);
		vma = find_vma(mm, addr);
		अगर (end - len >= addr &&
		    (!vma || addr + len <= vm_start_gap(vma)))
			वापस addr;
	पूर्ण

	info.flags = 0;
	info.length = len;
	info.low_limit = begin;
	info.high_limit = end;
	info.align_mask = 0;
	info.align_offset = pgoff << PAGE_SHIFT;
	अगर (filp) अणु
		info.align_mask = get_align_mask();
		info.align_offset += get_align_bits();
	पूर्ण
	वापस vm_unmapped_area(&info);
पूर्ण

अचिन्हित दीर्घ
arch_get_unmapped_area_topकरोwn(काष्ठा file *filp, स्थिर अचिन्हित दीर्घ addr0,
			  स्थिर अचिन्हित दीर्घ len, स्थिर अचिन्हित दीर्घ pgoff,
			  स्थिर अचिन्हित दीर्घ flags)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा mm_काष्ठा *mm = current->mm;
	अचिन्हित दीर्घ addr = addr0;
	काष्ठा vm_unmapped_area_info info;

	/* requested length too big क्रम entire address space */
	अगर (len > TASK_SIZE)
		वापस -ENOMEM;

	/* No address checking. See comment at mmap_address_hपूर्णांक_valid() */
	अगर (flags & MAP_FIXED)
		वापस addr;

	/* क्रम MAP_32BIT mappings we क्रमce the legacy mmap base */
	अगर (!in_32bit_syscall() && (flags & MAP_32BIT))
		जाओ bottomup;

	/* requesting a specअगरic address */
	अगर (addr) अणु
		addr &= PAGE_MASK;
		अगर (!mmap_address_hपूर्णांक_valid(addr, len))
			जाओ get_unmapped_area;

		vma = find_vma(mm, addr);
		अगर (!vma || addr + len <= vm_start_gap(vma))
			वापस addr;
	पूर्ण
get_unmapped_area:

	info.flags = VM_UNMAPPED_AREA_TOPDOWN;
	info.length = len;
	info.low_limit = PAGE_SIZE;
	info.high_limit = get_mmap_base(0);

	/*
	 * If hपूर्णांक address is above DEFAULT_MAP_WINDOW, look क्रम unmapped area
	 * in the full address space.
	 *
	 * !in_32bit_syscall() check to aव्योम high addresses क्रम x32
	 * (and make it no op on native i386).
	 */
	अगर (addr > DEFAULT_MAP_WINDOW && !in_32bit_syscall())
		info.high_limit += TASK_SIZE_MAX - DEFAULT_MAP_WINDOW;

	info.align_mask = 0;
	info.align_offset = pgoff << PAGE_SHIFT;
	अगर (filp) अणु
		info.align_mask = get_align_mask();
		info.align_offset += get_align_bits();
	पूर्ण
	addr = vm_unmapped_area(&info);
	अगर (!(addr & ~PAGE_MASK))
		वापस addr;
	VM_BUG_ON(addr != -ENOMEM);

bottomup:
	/*
	 * A failed mmap() very likely causes application failure,
	 * so fall back to the bottom-up function here. This scenario
	 * can happen with large stack limits and large mmap()
	 * allocations.
	 */
	वापस arch_get_unmapped_area(filp, addr0, len, pgoff, flags);
पूर्ण
