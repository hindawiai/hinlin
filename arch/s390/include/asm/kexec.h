<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright IBM Corp. 2005
 *
 * Author(s): Rolf Adelsberger <adelsberger@de.ibm.com>
 *
 */

#अगर_अघोषित _S390_KEXEC_H
#घोषणा _S390_KEXEC_H

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/setup.h>
/*
 * KEXEC_SOURCE_MEMORY_LIMIT maximum page get_मुक्त_page can वापस.
 * I.e. Maximum page that is mapped directly पूर्णांकo kernel memory,
 * and kmap is not required.
 */

/* Maximum physical address we can use pages from */
#घोषणा KEXEC_SOURCE_MEMORY_LIMIT (-1UL)

/* Maximum address we can reach in physical address mode */
#घोषणा KEXEC_DESTINATION_MEMORY_LIMIT (-1UL)

/* Maximum address we can use क्रम the control pages */
/* Not more than 2GB */
#घोषणा KEXEC_CONTROL_MEMORY_LIMIT (1UL<<31)

/* Allocate control page with GFP_DMA */
#घोषणा KEXEC_CONTROL_MEMORY_GFP GFP_DMA

/* Maximum address we can use क्रम the crash control pages */
#घोषणा KEXEC_CRASH_CONTROL_MEMORY_LIMIT (-1UL)

/* Allocate one page क्रम the pdp and the second क्रम the code */
#घोषणा KEXEC_CONTROL_PAGE_SIZE 4096

/* Alignment of crashkernel memory */
#घोषणा KEXEC_CRASH_MEM_ALIGN HPAGE_SIZE

/* The native architecture */
#घोषणा KEXEC_ARCH KEXEC_ARCH_S390

/* Allow kexec_file to load a segment to 0 */
#घोषणा KEXEC_BUF_MEM_UNKNOWN -1

/* Provide a dummy definition to aव्योम build failures. */
अटल अंतरभूत व्योम crash_setup_regs(काष्ठा pt_regs *newregs,
					काष्ठा pt_regs *oldregs) अणु पूर्ण

काष्ठा kimage;
काष्ठा s390_load_data अणु
	/* Poपूर्णांकer to the kernel buffer. Used to रेजिस्टर cmdline etc.. */
	व्योम *kernel_buf;

	/* Load address of the kernel_buf. */
	अचिन्हित दीर्घ kernel_mem;

	/* Parmarea in the kernel buffer. */
	काष्ठा parmarea *parm;

	/* Total size of loaded segments in memory. Used as an offset. */
	माप_प्रकार memsz;

	काष्ठा ipl_report *report;
पूर्ण;

पूर्णांक s390_verअगरy_sig(स्थिर अक्षर *kernel, अचिन्हित दीर्घ kernel_len);
व्योम *kexec_file_add_components(काष्ठा kimage *image,
				पूर्णांक (*add_kernel)(काष्ठा kimage *image,
						  काष्ठा s390_load_data *data));
पूर्णांक arch_kexec_करो_relocs(पूर्णांक r_type, व्योम *loc, अचिन्हित दीर्घ val,
			 अचिन्हित दीर्घ addr);

बाह्य स्थिर काष्ठा kexec_file_ops s390_kexec_image_ops;
बाह्य स्थिर काष्ठा kexec_file_ops s390_kexec_elf_ops;

#पूर्ण_अगर /*_S390_KEXEC_H */
