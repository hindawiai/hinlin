<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tools/testing/selftests/kvm/lib/elf.c
 *
 * Copyright (C) 2018, Google LLC.
 */

#समावेश "test_util.h"

#समावेश <bits/endian.h>
#समावेश <linux/elf.h>

#समावेश "kvm_util.h"
#समावेश "kvm_util_internal.h"

अटल व्योम elfhdr_get(स्थिर अक्षर *filename, Elf64_Ehdr *hdrp)
अणु
	off_t offset_rv;

	/* Open the ELF file. */
	पूर्णांक fd;
	fd = खोलो(filename, O_RDONLY);
	TEST_ASSERT(fd >= 0, "Failed to open ELF file,\n"
		"  filename: %s\n"
		"  rv: %i errno: %i", filename, fd, त्रुटि_सं);

	/* Read in and validate ELF Identअगरication Record.
	 * The ELF Identअगरication record is the first 16 (EI_NIDENT) bytes
	 * of the ELF header, which is at the beginning of the ELF file.
	 * For now it is only safe to पढ़ो the first EI_NIDENT bytes.  Once
	 * पढ़ो and validated, the value of e_ehsize can be used to determine
	 * the real size of the ELF header.
	 */
	अचिन्हित अक्षर ident[EI_NIDENT];
	test_पढ़ो(fd, ident, माप(ident));
	TEST_ASSERT((ident[EI_MAG0] == ELFMAG0) && (ident[EI_MAG1] == ELFMAG1)
		&& (ident[EI_MAG2] == ELFMAG2) && (ident[EI_MAG3] == ELFMAG3),
		"ELF MAGIC Mismatch,\n"
		"  filename: %s\n"
		"  ident[EI_MAG0 - EI_MAG3]: %02x %02x %02x %02x\n"
		"  Expected: %02x %02x %02x %02x",
		filename,
		ident[EI_MAG0], ident[EI_MAG1], ident[EI_MAG2], ident[EI_MAG3],
		ELFMAG0, ELFMAG1, ELFMAG2, ELFMAG3);
	TEST_ASSERT(ident[EI_CLASS] == ELFCLASS64,
		"Current implementation only able to handle ELFCLASS64,\n"
		"  filename: %s\n"
		"  ident[EI_CLASS]: %02x\n"
		"  expected: %02x",
		filename,
		ident[EI_CLASS], ELFCLASS64);
	TEST_ASSERT(((BYTE_ORDER == LITTLE_ENDIAN)
			&& (ident[EI_DATA] == ELFDATA2LSB))
		|| ((BYTE_ORDER == BIG_ENDIAN)
			&& (ident[EI_DATA] == ELFDATA2MSB)), "Current "
		"implementation only able to handle\n"
		"cases where the host and ELF file endianness\n"
		"is the same:\n"
		"  host BYTE_ORDER: %u\n"
		"  host LITTLE_ENDIAN: %u\n"
		"  host BIG_ENDIAN: %u\n"
		"  ident[EI_DATA]: %u\n"
		"  ELFDATA2LSB: %u\n"
		"  ELFDATA2MSB: %u",
		BYTE_ORDER, LITTLE_ENDIAN, BIG_ENDIAN,
		ident[EI_DATA], ELFDATA2LSB, ELFDATA2MSB);
	TEST_ASSERT(ident[EI_VERSION] == EV_CURRENT,
		"Current implementation only able to handle current "
		"ELF version,\n"
		"  filename: %s\n"
		"  ident[EI_VERSION]: %02x\n"
		"  expected: %02x",
		filename, ident[EI_VERSION], EV_CURRENT);

	/* Read in the ELF header.
	 * With the ELF Identअगरication portion of the ELF header
	 * validated, especially that the value at EI_VERSION is
	 * as expected, it is now safe to पढ़ो the entire ELF header.
	 */
	offset_rv = lseek(fd, 0, शुरू_से);
	TEST_ASSERT(offset_rv == 0, "Seek to ELF header failed,\n"
		"  rv: %zi expected: %i", offset_rv, 0);
	test_पढ़ो(fd, hdrp, माप(*hdrp));
	TEST_ASSERT(hdrp->e_phentsize == माप(Elf64_Phdr),
		"Unexpected physical header size,\n"
		"  hdrp->e_phentsize: %x\n"
		"  expected: %zx",
		hdrp->e_phentsize, माप(Elf64_Phdr));
	TEST_ASSERT(hdrp->e_shentsize == माप(Elf64_Shdr),
		"Unexpected section header size,\n"
		"  hdrp->e_shentsize: %x\n"
		"  expected: %zx",
		hdrp->e_shentsize, माप(Elf64_Shdr));
पूर्ण

/* VM ELF Load
 *
 * Input Args:
 *   filename - Path to ELF file
 *
 * Output Args: None
 *
 * Input/Output Args:
 *   vm - Poपूर्णांकer to opaque type that describes the VM.
 *
 * Return: None, TEST_ASSERT failures क्रम all error conditions
 *
 * Loads the program image of the ELF file specअगरied by filename,
 * पूर्णांकo the भव address space of the VM poपूर्णांकed to by vm.  On entry
 * the VM needs to not be using any of the भव address space used
 * by the image and it needs to have sufficient available physical pages, to
 * back the भव pages used to load the image.
 */
व्योम kvm_vm_elf_load(काष्ठा kvm_vm *vm, स्थिर अक्षर *filename,
	uपूर्णांक32_t data_memslot, uपूर्णांक32_t pgd_memslot)
अणु
	off_t offset, offset_rv;
	Elf64_Ehdr hdr;

	/* Open the ELF file. */
	पूर्णांक fd;
	fd = खोलो(filename, O_RDONLY);
	TEST_ASSERT(fd >= 0, "Failed to open ELF file,\n"
		"  filename: %s\n"
		"  rv: %i errno: %i", filename, fd, त्रुटि_सं);

	/* Read in the ELF header. */
	elfhdr_get(filename, &hdr);

	/* For each program header.
	 * The following ELF header members specअगरy the location
	 * and size of the program headers:
	 *
	 *   e_phoff - File offset to start of program headers
	 *   e_phentsize - Size of each program header
	 *   e_phnum - Number of program header entries
	 */
	क्रम (अचिन्हित पूर्णांक n1 = 0; n1 < hdr.e_phnum; n1++) अणु
		/* Seek to the beginning of the program header. */
		offset = hdr.e_phoff + (n1 * hdr.e_phentsize);
		offset_rv = lseek(fd, offset, शुरू_से);
		TEST_ASSERT(offset_rv == offset,
			"Failed to seek to begining of program header %u,\n"
			"  filename: %s\n"
			"  rv: %jd errno: %i",
			n1, filename, (पूर्णांकmax_t) offset_rv, त्रुटि_सं);

		/* Read in the program header. */
		Elf64_Phdr phdr;
		test_पढ़ो(fd, &phdr, माप(phdr));

		/* Skip अगर this header करोesn't describe a loadable segment. */
		अगर (phdr.p_type != PT_LOAD)
			जारी;

		/* Allocate memory क्रम this segment within the VM. */
		TEST_ASSERT(phdr.p_memsz > 0, "Unexpected loadable segment "
			"memsize of 0,\n"
			"  phdr index: %u p_memsz: 0x%" PRIx64,
			n1, (uपूर्णांक64_t) phdr.p_memsz);
		vm_vaddr_t seg_vstart = phdr.p_vaddr;
		seg_vstart &= ~(vm_vaddr_t)(vm->page_size - 1);
		vm_vaddr_t seg_vend = phdr.p_vaddr + phdr.p_memsz - 1;
		seg_vend |= vm->page_size - 1;
		माप_प्रकार seg_size = seg_vend - seg_vstart + 1;

		vm_vaddr_t vaddr = vm_vaddr_alloc(vm, seg_size, seg_vstart,
			data_memslot, pgd_memslot);
		TEST_ASSERT(vaddr == seg_vstart, "Unable to allocate "
			"virtual memory for segment at requested min addr,\n"
			"  segment idx: %u\n"
			"  seg_vstart: 0x%lx\n"
			"  vaddr: 0x%lx",
			n1, seg_vstart, vaddr);
		स_रखो(addr_gva2hva(vm, vaddr), 0, seg_size);
		/* TODO(lhuemill): Set permissions of each memory segment
		 * based on the least-signअगरicant 3 bits of phdr.p_flags.
		 */

		/* Load portion of initial state that is contained within
		 * the ELF file.
		 */
		अगर (phdr.p_filesz) अणु
			offset_rv = lseek(fd, phdr.p_offset, शुरू_से);
			TEST_ASSERT(offset_rv == phdr.p_offset,
				"Seek to program segment offset failed,\n"
				"  program header idx: %u errno: %i\n"
				"  offset_rv: 0x%jx\n"
				"  expected: 0x%jx\n",
				n1, त्रुटि_सं, (पूर्णांकmax_t) offset_rv,
				(पूर्णांकmax_t) phdr.p_offset);
			test_पढ़ो(fd, addr_gva2hva(vm, phdr.p_vaddr),
				phdr.p_filesz);
		पूर्ण
	पूर्ण
पूर्ण
