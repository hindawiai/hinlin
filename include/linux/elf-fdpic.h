<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* FDPIC ELF load map
 *
 * Copyright (C) 2003 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित _LINUX_ELF_FDPIC_H
#घोषणा _LINUX_ELF_FDPIC_H

#समावेश <uapi/linux/elf-fdpic.h>

/*
 * binfmt binary parameters काष्ठाure
 */
काष्ठा elf_fdpic_params अणु
	काष्ठा elfhdr			hdr;		/* ref copy of ELF header */
	काष्ठा elf_phdr			*phdrs;		/* ref copy of PT_PHDR table */
	काष्ठा elf32_fdpic_loadmap	*loadmap;	/* loadmap to be passed to userspace */
	अचिन्हित दीर्घ			elfhdr_addr;	/* mapped ELF header user address */
	अचिन्हित दीर्घ			ph_addr;	/* mapped PT_PHDR user address */
	अचिन्हित दीर्घ			map_addr;	/* mapped loadmap user address */
	अचिन्हित दीर्घ			entry_addr;	/* mapped entry user address */
	अचिन्हित दीर्घ			stack_size;	/* stack size requested (PT_GNU_STACK) */
	अचिन्हित दीर्घ			dynamic_addr;	/* mapped PT_DYNAMIC user address */
	अचिन्हित दीर्घ			load_addr;	/* user address at which to map binary */
	अचिन्हित दीर्घ			flags;
#घोषणा ELF_FDPIC_FLAG_ARRANGEMENT	0x0000000f	/* PT_LOAD arrangement flags */
#घोषणा ELF_FDPIC_FLAG_INDEPENDENT	0x00000000	/* PT_LOADs can be put anywhere */
#घोषणा ELF_FDPIC_FLAG_HONOURVADDR	0x00000001	/* PT_LOAD.vaddr must be honoured */
#घोषणा ELF_FDPIC_FLAG_CONSTDISP	0x00000002	/* PT_LOADs require स्थिरant
							 * displacement */
#घोषणा ELF_FDPIC_FLAG_CONTIGUOUS	0x00000003	/* PT_LOADs should be contiguous */
#घोषणा ELF_FDPIC_FLAG_EXEC_STACK	0x00000010	/* T अगर stack to be executable */
#घोषणा ELF_FDPIC_FLAG_NOEXEC_STACK	0x00000020	/* T अगर stack not to be executable */
#घोषणा ELF_FDPIC_FLAG_EXECUTABLE	0x00000040	/* T अगर this object is the executable */
#घोषणा ELF_FDPIC_FLAG_PRESENT		0x80000000	/* T अगर this object is present */
पूर्ण;

#अगर_घोषित CONFIG_MMU
बाह्य व्योम elf_fdpic_arch_lay_out_mm(काष्ठा elf_fdpic_params *exec_params,
				      काष्ठा elf_fdpic_params *पूर्णांकerp_params,
				      अचिन्हित दीर्घ *start_stack,
				      अचिन्हित दीर्घ *start_brk);
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_ELF_FDPIC_H */
