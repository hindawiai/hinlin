<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * S390 kdump implementation
 *
 * Copyright IBM Corp. 2011
 * Author(s): Michael Holzheu <holzheu@linux.vnet.ibm.com>
 */

#समावेश <linux/crash_dump.h>
#समावेश <यंत्र/lowcore.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/gfp.h>
#समावेश <linux/slab.h>
#समावेश <linux/memblock.h>
#समावेश <linux/elf.h>
#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/os_info.h>
#समावेश <यंत्र/elf.h>
#समावेश <यंत्र/ipl.h>
#समावेश <यंत्र/sclp.h>

#घोषणा PTR_ADD(x, y) (((अक्षर *) (x)) + ((अचिन्हित दीर्घ) (y)))
#घोषणा PTR_SUB(x, y) (((अक्षर *) (x)) - ((अचिन्हित दीर्घ) (y)))
#घोषणा PTR_DIFF(x, y) ((अचिन्हित दीर्घ)(((अक्षर *) (x)) - ((अचिन्हित दीर्घ) (y))))

अटल काष्ठा memblock_region oldmem_region;

अटल काष्ठा memblock_type oldmem_type = अणु
	.cnt = 1,
	.max = 1,
	.total_size = 0,
	.regions = &oldmem_region,
	.name = "oldmem",
पूर्ण;

काष्ठा save_area अणु
	काष्ठा list_head list;
	u64 psw[2];
	u64 ctrs[16];
	u64 gprs[16];
	u32 acrs[16];
	u64 fprs[16];
	u32 fpc;
	u32 prefix;
	u64 todpreg;
	u64 समयr;
	u64 todcmp;
	u64 vxrs_low[16];
	__vector128 vxrs_high[16];
पूर्ण;

अटल LIST_HEAD(dump_save_areas);

/*
 * Allocate a save area
 */
काष्ठा save_area * __init save_area_alloc(bool is_boot_cpu)
अणु
	काष्ठा save_area *sa;

	sa = (व्योम *) memblock_phys_alloc(माप(*sa), 8);
	अगर (!sa)
		panic("Failed to allocate save area\n");

	अगर (is_boot_cpu)
		list_add(&sa->list, &dump_save_areas);
	अन्यथा
		list_add_tail(&sa->list, &dump_save_areas);
	वापस sa;
पूर्ण

/*
 * Return the address of the save area क्रम the boot CPU
 */
काष्ठा save_area * __init save_area_boot_cpu(व्योम)
अणु
	वापस list_first_entry_or_null(&dump_save_areas, काष्ठा save_area, list);
पूर्ण

/*
 * Copy CPU रेजिस्टरs पूर्णांकo the save area
 */
व्योम __init save_area_add_regs(काष्ठा save_area *sa, व्योम *regs)
अणु
	काष्ठा lowcore *lc;

	lc = (काष्ठा lowcore *)(regs - __LC_FPREGS_SAVE_AREA);
	स_नकल(&sa->psw, &lc->psw_save_area, माप(sa->psw));
	स_नकल(&sa->ctrs, &lc->cregs_save_area, माप(sa->ctrs));
	स_नकल(&sa->gprs, &lc->gpregs_save_area, माप(sa->gprs));
	स_नकल(&sa->acrs, &lc->access_regs_save_area, माप(sa->acrs));
	स_नकल(&sa->fprs, &lc->भग्नing_pt_save_area, माप(sa->fprs));
	स_नकल(&sa->fpc, &lc->fpt_creg_save_area, माप(sa->fpc));
	स_नकल(&sa->prefix, &lc->prefixreg_save_area, माप(sa->prefix));
	स_नकल(&sa->todpreg, &lc->tod_progreg_save_area, माप(sa->todpreg));
	स_नकल(&sa->समयr, &lc->cpu_समयr_save_area, माप(sa->समयr));
	स_नकल(&sa->todcmp, &lc->घड़ी_comp_save_area, माप(sa->todcmp));
पूर्ण

/*
 * Copy vector रेजिस्टरs पूर्णांकo the save area
 */
व्योम __init save_area_add_vxrs(काष्ठा save_area *sa, __vector128 *vxrs)
अणु
	पूर्णांक i;

	/* Copy lower halves of vector रेजिस्टरs 0-15 */
	क्रम (i = 0; i < 16; i++)
		स_नकल(&sa->vxrs_low[i], &vxrs[i].u[2], 8);
	/* Copy vector रेजिस्टरs 16-31 */
	स_नकल(sa->vxrs_high, vxrs + 16, 16 * माप(__vector128));
पूर्ण

/*
 * Return physical address क्रम भव address
 */
अटल अंतरभूत व्योम *load_real_addr(व्योम *addr)
अणु
	अचिन्हित दीर्घ real_addr;

	यंत्र अस्थिर(
		   "	lra     %0,0(%1)\n"
		   "	jz	0f\n"
		   "	la	%0,0\n"
		   "0:"
		   : "=a" (real_addr) : "a" (addr) : "cc");
	वापस (व्योम *)real_addr;
पूर्ण

/*
 * Copy memory of the old, dumped प्रणाली to a kernel space भव address
 */
पूर्णांक copy_oldmem_kernel(व्योम *dst, व्योम *src, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ from, len;
	व्योम *ra;
	पूर्णांक rc;

	जबतक (count) अणु
		from = __pa(src);
		अगर (!OLDMEM_BASE && from < sclp.hsa_size) अणु
			/* Copy from zfcp/nvme dump HSA area */
			len = min(count, sclp.hsa_size - from);
			rc = स_नकल_hsa_kernel(dst, from, len);
			अगर (rc)
				वापस rc;
		पूर्ण अन्यथा अणु
			/* Check क्रम swapped kdump oldmem areas */
			अगर (OLDMEM_BASE && from - OLDMEM_BASE < OLDMEM_SIZE) अणु
				from -= OLDMEM_BASE;
				len = min(count, OLDMEM_SIZE - from);
			पूर्ण अन्यथा अगर (OLDMEM_BASE && from < OLDMEM_SIZE) अणु
				len = min(count, OLDMEM_SIZE - from);
				from += OLDMEM_BASE;
			पूर्ण अन्यथा अणु
				len = count;
			पूर्ण
			अगर (is_vदो_स्मृति_or_module_addr(dst)) अणु
				ra = load_real_addr(dst);
				len = min(PAGE_SIZE - offset_in_page(ra), len);
			पूर्ण अन्यथा अणु
				ra = dst;
			पूर्ण
			अगर (स_नकल_real(ra, (व्योम *) from, len))
				वापस -EFAULT;
		पूर्ण
		dst += len;
		src += len;
		count -= len;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Copy memory of the old, dumped प्रणाली to a user space भव address
 */
अटल पूर्णांक copy_oldmem_user(व्योम __user *dst, व्योम *src, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ from, len;
	पूर्णांक rc;

	जबतक (count) अणु
		from = __pa(src);
		अगर (!OLDMEM_BASE && from < sclp.hsa_size) अणु
			/* Copy from zfcp/nvme dump HSA area */
			len = min(count, sclp.hsa_size - from);
			rc = स_नकल_hsa_user(dst, from, len);
			अगर (rc)
				वापस rc;
		पूर्ण अन्यथा अणु
			/* Check क्रम swapped kdump oldmem areas */
			अगर (OLDMEM_BASE && from - OLDMEM_BASE < OLDMEM_SIZE) अणु
				from -= OLDMEM_BASE;
				len = min(count, OLDMEM_SIZE - from);
			पूर्ण अन्यथा अगर (OLDMEM_BASE && from < OLDMEM_SIZE) अणु
				len = min(count, OLDMEM_SIZE - from);
				from += OLDMEM_BASE;
			पूर्ण अन्यथा अणु
				len = count;
			पूर्ण
			rc = copy_to_user_real(dst, (व्योम *) from, count);
			अगर (rc)
				वापस rc;
		पूर्ण
		dst += len;
		src += len;
		count -= len;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Copy one page from "oldmem"
 */
sमाप_प्रकार copy_oldmem_page(अचिन्हित दीर्घ pfn, अक्षर *buf, माप_प्रकार csize,
			 अचिन्हित दीर्घ offset, पूर्णांक userbuf)
अणु
	व्योम *src;
	पूर्णांक rc;

	अगर (!csize)
		वापस 0;
	src = (व्योम *) (pfn << PAGE_SHIFT) + offset;
	अगर (userbuf)
		rc = copy_oldmem_user((व्योम __क्रमce __user *) buf, src, csize);
	अन्यथा
		rc = copy_oldmem_kernel((व्योम *) buf, src, csize);
	वापस rc;
पूर्ण

/*
 * Remap "oldmem" क्रम kdump
 *
 * For the kdump reserved memory this functions perक्रमms a swap operation:
 * [0 - OLDMEM_SIZE] is mapped to [OLDMEM_BASE - OLDMEM_BASE + OLDMEM_SIZE]
 */
अटल पूर्णांक remap_oldmem_pfn_range_kdump(काष्ठा vm_area_काष्ठा *vma,
					अचिन्हित दीर्घ from, अचिन्हित दीर्घ pfn,
					अचिन्हित दीर्घ size, pgprot_t prot)
अणु
	अचिन्हित दीर्घ size_old;
	पूर्णांक rc;

	अगर (pfn < OLDMEM_SIZE >> PAGE_SHIFT) अणु
		size_old = min(size, OLDMEM_SIZE - (pfn << PAGE_SHIFT));
		rc = remap_pfn_range(vma, from,
				     pfn + (OLDMEM_BASE >> PAGE_SHIFT),
				     size_old, prot);
		अगर (rc || size == size_old)
			वापस rc;
		size -= size_old;
		from += size_old;
		pfn += size_old >> PAGE_SHIFT;
	पूर्ण
	वापस remap_pfn_range(vma, from, pfn, size, prot);
पूर्ण

/*
 * Remap "oldmem" क्रम zfcp/nvme dump
 *
 * We only map available memory above HSA size. Memory below HSA size
 * is पढ़ो on demand using the copy_oldmem_page() function.
 */
अटल पूर्णांक remap_oldmem_pfn_range_zfcpdump(काष्ठा vm_area_काष्ठा *vma,
					   अचिन्हित दीर्घ from,
					   अचिन्हित दीर्घ pfn,
					   अचिन्हित दीर्घ size, pgprot_t prot)
अणु
	अचिन्हित दीर्घ hsa_end = sclp.hsa_size;
	अचिन्हित दीर्घ size_hsa;

	अगर (pfn < hsa_end >> PAGE_SHIFT) अणु
		size_hsa = min(size, hsa_end - (pfn << PAGE_SHIFT));
		अगर (size == size_hsa)
			वापस 0;
		size -= size_hsa;
		from += size_hsa;
		pfn += size_hsa >> PAGE_SHIFT;
	पूर्ण
	वापस remap_pfn_range(vma, from, pfn, size, prot);
पूर्ण

/*
 * Remap "oldmem" क्रम kdump or zfcp/nvme dump
 */
पूर्णांक remap_oldmem_pfn_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ from,
			   अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ size, pgprot_t prot)
अणु
	अगर (OLDMEM_BASE)
		वापस remap_oldmem_pfn_range_kdump(vma, from, pfn, size, prot);
	अन्यथा
		वापस remap_oldmem_pfn_range_zfcpdump(vma, from, pfn, size,
						       prot);
पूर्ण

अटल स्थिर अक्षर *nt_name(Elf64_Word type)
अणु
	स्थिर अक्षर *name = "LINUX";

	अगर (type == NT_PRPSINFO || type == NT_PRSTATUS || type == NT_PRFPREG)
		name = KEXEC_CORE_NOTE_NAME;
	वापस name;
पूर्ण

/*
 * Initialize ELF note
 */
अटल व्योम *nt_init_name(व्योम *buf, Elf64_Word type, व्योम *desc, पूर्णांक d_len,
			  स्थिर अक्षर *name)
अणु
	Elf64_Nhdr *note;
	u64 len;

	note = (Elf64_Nhdr *)buf;
	note->n_namesz = म_माप(name) + 1;
	note->n_descsz = d_len;
	note->n_type = type;
	len = माप(Elf64_Nhdr);

	स_नकल(buf + len, name, note->n_namesz);
	len = roundup(len + note->n_namesz, 4);

	स_नकल(buf + len, desc, note->n_descsz);
	len = roundup(len + note->n_descsz, 4);

	वापस PTR_ADD(buf, len);
पूर्ण

अटल अंतरभूत व्योम *nt_init(व्योम *buf, Elf64_Word type, व्योम *desc, पूर्णांक d_len)
अणु
	वापस nt_init_name(buf, type, desc, d_len, nt_name(type));
पूर्ण

/*
 * Calculate the size of ELF note
 */
अटल माप_प्रकार nt_size_name(पूर्णांक d_len, स्थिर अक्षर *name)
अणु
	माप_प्रकार size;

	size = माप(Elf64_Nhdr);
	size += roundup(म_माप(name) + 1, 4);
	size += roundup(d_len, 4);

	वापस size;
पूर्ण

अटल अंतरभूत माप_प्रकार nt_size(Elf64_Word type, पूर्णांक d_len)
अणु
	वापस nt_size_name(d_len, nt_name(type));
पूर्ण

/*
 * Fill ELF notes क्रम one CPU with save area रेजिस्टरs
 */
अटल व्योम *fill_cpu_elf_notes(व्योम *ptr, पूर्णांक cpu, काष्ठा save_area *sa)
अणु
	काष्ठा elf_prstatus nt_prstatus;
	elf_fpregset_t nt_fpregset;

	/* Prepare prstatus note */
	स_रखो(&nt_prstatus, 0, माप(nt_prstatus));
	स_नकल(&nt_prstatus.pr_reg.gprs, sa->gprs, माप(sa->gprs));
	स_नकल(&nt_prstatus.pr_reg.psw, sa->psw, माप(sa->psw));
	स_नकल(&nt_prstatus.pr_reg.acrs, sa->acrs, माप(sa->acrs));
	nt_prstatus.common.pr_pid = cpu;
	/* Prepare fpregset (भग्नing poपूर्णांक) note */
	स_रखो(&nt_fpregset, 0, माप(nt_fpregset));
	स_नकल(&nt_fpregset.fpc, &sa->fpc, माप(sa->fpc));
	स_नकल(&nt_fpregset.fprs, &sa->fprs, माप(sa->fprs));
	/* Create ELF notes क्रम the CPU */
	ptr = nt_init(ptr, NT_PRSTATUS, &nt_prstatus, माप(nt_prstatus));
	ptr = nt_init(ptr, NT_PRFPREG, &nt_fpregset, माप(nt_fpregset));
	ptr = nt_init(ptr, NT_S390_TIMER, &sa->समयr, माप(sa->समयr));
	ptr = nt_init(ptr, NT_S390_TODCMP, &sa->todcmp, माप(sa->todcmp));
	ptr = nt_init(ptr, NT_S390_TODPREG, &sa->todpreg, माप(sa->todpreg));
	ptr = nt_init(ptr, NT_S390_CTRS, &sa->ctrs, माप(sa->ctrs));
	ptr = nt_init(ptr, NT_S390_PREFIX, &sa->prefix, माप(sa->prefix));
	अगर (MACHINE_HAS_VX) अणु
		ptr = nt_init(ptr, NT_S390_VXRS_HIGH,
			      &sa->vxrs_high, माप(sa->vxrs_high));
		ptr = nt_init(ptr, NT_S390_VXRS_LOW,
			      &sa->vxrs_low, माप(sa->vxrs_low));
	पूर्ण
	वापस ptr;
पूर्ण

/*
 * Calculate size of ELF notes per cpu
 */
अटल माप_प्रकार get_cpu_elf_notes_size(व्योम)
अणु
	काष्ठा save_area *sa = शून्य;
	माप_प्रकार size;

	size =	nt_size(NT_PRSTATUS, माप(काष्ठा elf_prstatus));
	size +=  nt_size(NT_PRFPREG, माप(elf_fpregset_t));
	size +=  nt_size(NT_S390_TIMER, माप(sa->समयr));
	size +=  nt_size(NT_S390_TODCMP, माप(sa->todcmp));
	size +=  nt_size(NT_S390_TODPREG, माप(sa->todpreg));
	size +=  nt_size(NT_S390_CTRS, माप(sa->ctrs));
	size +=  nt_size(NT_S390_PREFIX, माप(sa->prefix));
	अगर (MACHINE_HAS_VX) अणु
		size += nt_size(NT_S390_VXRS_HIGH, माप(sa->vxrs_high));
		size += nt_size(NT_S390_VXRS_LOW, माप(sa->vxrs_low));
	पूर्ण

	वापस size;
पूर्ण

/*
 * Initialize prpsinfo note (new kernel)
 */
अटल व्योम *nt_prpsinfo(व्योम *ptr)
अणु
	काष्ठा elf_prpsinfo prpsinfo;

	स_रखो(&prpsinfo, 0, माप(prpsinfo));
	prpsinfo.pr_sname = 'R';
	म_नकल(prpsinfo.pr_fname, "vmlinux");
	वापस nt_init(ptr, NT_PRPSINFO, &prpsinfo, माप(prpsinfo));
पूर्ण

/*
 * Get vmcoreinfo using lowcore->vmcore_info (new kernel)
 */
अटल व्योम *get_vmcoreinfo_old(अचिन्हित दीर्घ *size)
अणु
	अक्षर nt_name[11], *vmcoreinfo;
	Elf64_Nhdr note;
	व्योम *addr;

	अगर (copy_oldmem_kernel(&addr, &S390_lowcore.vmcore_info, माप(addr)))
		वापस शून्य;
	स_रखो(nt_name, 0, माप(nt_name));
	अगर (copy_oldmem_kernel(&note, addr, माप(note)))
		वापस शून्य;
	अगर (copy_oldmem_kernel(nt_name, addr + माप(note),
			       माप(nt_name) - 1))
		वापस शून्य;
	अगर (म_भेद(nt_name, VMCOREINFO_NOTE_NAME) != 0)
		वापस शून्य;
	vmcoreinfo = kzalloc(note.n_descsz, GFP_KERNEL);
	अगर (!vmcoreinfo)
		वापस शून्य;
	अगर (copy_oldmem_kernel(vmcoreinfo, addr + 24, note.n_descsz)) अणु
		kमुक्त(vmcoreinfo);
		वापस शून्य;
	पूर्ण
	*size = note.n_descsz;
	वापस vmcoreinfo;
पूर्ण

/*
 * Initialize vmcoreinfo note (new kernel)
 */
अटल व्योम *nt_vmcoreinfo(व्योम *ptr)
अणु
	स्थिर अक्षर *name = VMCOREINFO_NOTE_NAME;
	अचिन्हित दीर्घ size;
	व्योम *vmcoreinfo;

	vmcoreinfo = os_info_old_entry(OS_INFO_VMCOREINFO, &size);
	अगर (vmcoreinfo)
		वापस nt_init_name(ptr, 0, vmcoreinfo, size, name);

	vmcoreinfo = get_vmcoreinfo_old(&size);
	अगर (!vmcoreinfo)
		वापस ptr;
	ptr = nt_init_name(ptr, 0, vmcoreinfo, size, name);
	kमुक्त(vmcoreinfo);
	वापस ptr;
पूर्ण

अटल माप_प्रकार nt_vmcoreinfo_size(व्योम)
अणु
	स्थिर अक्षर *name = VMCOREINFO_NOTE_NAME;
	अचिन्हित दीर्घ size;
	व्योम *vmcoreinfo;

	vmcoreinfo = os_info_old_entry(OS_INFO_VMCOREINFO, &size);
	अगर (vmcoreinfo)
		वापस nt_size_name(size, name);

	vmcoreinfo = get_vmcoreinfo_old(&size);
	अगर (!vmcoreinfo)
		वापस 0;

	kमुक्त(vmcoreinfo);
	वापस nt_size_name(size, name);
पूर्ण

/*
 * Initialize final note (needed क्रम /proc/vmcore code)
 */
अटल व्योम *nt_final(व्योम *ptr)
अणु
	Elf64_Nhdr *note;

	note = (Elf64_Nhdr *) ptr;
	note->n_namesz = 0;
	note->n_descsz = 0;
	note->n_type = 0;
	वापस PTR_ADD(ptr, माप(Elf64_Nhdr));
पूर्ण

/*
 * Initialize ELF header (new kernel)
 */
अटल व्योम *ehdr_init(Elf64_Ehdr *ehdr, पूर्णांक mem_chunk_cnt)
अणु
	स_रखो(ehdr, 0, माप(*ehdr));
	स_नकल(ehdr->e_ident, ELFMAG, SELFMAG);
	ehdr->e_ident[EI_CLASS] = ELFCLASS64;
	ehdr->e_ident[EI_DATA] = ELFDATA2MSB;
	ehdr->e_ident[EI_VERSION] = EV_CURRENT;
	स_रखो(ehdr->e_ident + EI_PAD, 0, EI_NIDENT - EI_PAD);
	ehdr->e_type = ET_CORE;
	ehdr->e_machine = EM_S390;
	ehdr->e_version = EV_CURRENT;
	ehdr->e_phoff = माप(Elf64_Ehdr);
	ehdr->e_ehsize = माप(Elf64_Ehdr);
	ehdr->e_phentsize = माप(Elf64_Phdr);
	ehdr->e_phnum = mem_chunk_cnt + 1;
	वापस ehdr + 1;
पूर्ण

/*
 * Return CPU count क्रम ELF header (new kernel)
 */
अटल पूर्णांक get_cpu_cnt(व्योम)
अणु
	काष्ठा save_area *sa;
	पूर्णांक cpus = 0;

	list_क्रम_each_entry(sa, &dump_save_areas, list)
		अगर (sa->prefix != 0)
			cpus++;
	वापस cpus;
पूर्ण

/*
 * Return memory chunk count क्रम ELF header (new kernel)
 */
अटल पूर्णांक get_mem_chunk_cnt(व्योम)
अणु
	पूर्णांक cnt = 0;
	u64 idx;

	क्रम_each_physmem_range(idx, &oldmem_type, शून्य, शून्य)
		cnt++;
	वापस cnt;
पूर्ण

/*
 * Initialize ELF loads (new kernel)
 */
अटल व्योम loads_init(Elf64_Phdr *phdr, u64 loads_offset)
अणु
	phys_addr_t start, end;
	u64 idx;

	क्रम_each_physmem_range(idx, &oldmem_type, &start, &end) अणु
		phdr->p_filesz = end - start;
		phdr->p_type = PT_LOAD;
		phdr->p_offset = start;
		phdr->p_vaddr = start;
		phdr->p_paddr = start;
		phdr->p_memsz = end - start;
		phdr->p_flags = PF_R | PF_W | PF_X;
		phdr->p_align = PAGE_SIZE;
		phdr++;
	पूर्ण
पूर्ण

/*
 * Initialize notes (new kernel)
 */
अटल व्योम *notes_init(Elf64_Phdr *phdr, व्योम *ptr, u64 notes_offset)
अणु
	काष्ठा save_area *sa;
	व्योम *ptr_start = ptr;
	पूर्णांक cpu;

	ptr = nt_prpsinfo(ptr);

	cpu = 1;
	list_क्रम_each_entry(sa, &dump_save_areas, list)
		अगर (sa->prefix != 0)
			ptr = fill_cpu_elf_notes(ptr, cpu++, sa);
	ptr = nt_vmcoreinfo(ptr);
	ptr = nt_final(ptr);
	स_रखो(phdr, 0, माप(*phdr));
	phdr->p_type = PT_NOTE;
	phdr->p_offset = notes_offset;
	phdr->p_filesz = (अचिन्हित दीर्घ) PTR_SUB(ptr, ptr_start);
	phdr->p_memsz = phdr->p_filesz;
	वापस ptr;
पूर्ण

अटल माप_प्रकार get_elfcorehdr_size(पूर्णांक mem_chunk_cnt)
अणु
	माप_प्रकार size;

	size = माप(Elf64_Ehdr);
	/* PT_NOTES */
	size += माप(Elf64_Phdr);
	/* nt_prpsinfo */
	size += nt_size(NT_PRPSINFO, माप(काष्ठा elf_prpsinfo));
	/* regsets */
	size += get_cpu_cnt() * get_cpu_elf_notes_size();
	/* nt_vmcoreinfo */
	size += nt_vmcoreinfo_size();
	/* nt_final */
	size += माप(Elf64_Nhdr);
	/* PT_LOADS */
	size += mem_chunk_cnt * माप(Elf64_Phdr);

	वापस size;
पूर्ण

/*
 * Create ELF core header (new kernel)
 */
पूर्णांक elfcorehdr_alloc(अचिन्हित दीर्घ दीर्घ *addr, अचिन्हित दीर्घ दीर्घ *size)
अणु
	Elf64_Phdr *phdr_notes, *phdr_loads;
	पूर्णांक mem_chunk_cnt;
	व्योम *ptr, *hdr;
	u32 alloc_size;
	u64 hdr_off;

	/* If we are not in kdump or zfcp/nvme dump mode वापस */
	अगर (!OLDMEM_BASE && !is_ipl_type_dump())
		वापस 0;
	/* If we cannot get HSA size क्रम zfcp/nvme dump वापस error */
	अगर (is_ipl_type_dump() && !sclp.hsa_size)
		वापस -ENODEV;

	/* For kdump, exclude previous crashkernel memory */
	अगर (OLDMEM_BASE) अणु
		oldmem_region.base = OLDMEM_BASE;
		oldmem_region.size = OLDMEM_SIZE;
		oldmem_type.total_size = OLDMEM_SIZE;
	पूर्ण

	mem_chunk_cnt = get_mem_chunk_cnt();

	alloc_size = get_elfcorehdr_size(mem_chunk_cnt);

	hdr = kzalloc(alloc_size, GFP_KERNEL);

	/* Without elfcorehdr /proc/vmcore cannot be created. Thus creating
	 * a dump with this crash kernel will fail. Panic now to allow other
	 * dump mechanisms to take over.
	 */
	अगर (!hdr)
		panic("s390 kdump allocating elfcorehdr failed");

	/* Init elf header */
	ptr = ehdr_init(hdr, mem_chunk_cnt);
	/* Init program headers */
	phdr_notes = ptr;
	ptr = PTR_ADD(ptr, माप(Elf64_Phdr));
	phdr_loads = ptr;
	ptr = PTR_ADD(ptr, माप(Elf64_Phdr) * mem_chunk_cnt);
	/* Init notes */
	hdr_off = PTR_DIFF(ptr, hdr);
	ptr = notes_init(phdr_notes, ptr, ((अचिन्हित दीर्घ) hdr) + hdr_off);
	/* Init loads */
	hdr_off = PTR_DIFF(ptr, hdr);
	loads_init(phdr_loads, hdr_off);
	*addr = (अचिन्हित दीर्घ दीर्घ) hdr;
	*size = (अचिन्हित दीर्घ दीर्घ) hdr_off;
	BUG_ON(elfcorehdr_size > alloc_size);
	वापस 0;
पूर्ण

/*
 * Free ELF core header (new kernel)
 */
व्योम elfcorehdr_मुक्त(अचिन्हित दीर्घ दीर्घ addr)
अणु
	kमुक्त((व्योम *)(अचिन्हित दीर्घ)addr);
पूर्ण

/*
 * Read from ELF header
 */
sमाप_प्रकार elfcorehdr_पढ़ो(अक्षर *buf, माप_प्रकार count, u64 *ppos)
अणु
	व्योम *src = (व्योम *)(अचिन्हित दीर्घ)*ppos;

	स_नकल(buf, src, count);
	*ppos += count;
	वापस count;
पूर्ण

/*
 * Read from ELF notes data
 */
sमाप_प्रकार elfcorehdr_पढ़ो_notes(अक्षर *buf, माप_प्रकार count, u64 *ppos)
अणु
	व्योम *src = (व्योम *)(अचिन्हित दीर्घ)*ppos;

	स_नकल(buf, src, count);
	*ppos += count;
	वापस count;
पूर्ण
