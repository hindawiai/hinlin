<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * kexec क्रम arm64
 *
 * Copyright (C) Linaro.
 * Copyright (C) Huawei Futurewei Technologies.
 */

#अगर_अघोषित _ARM64_KEXEC_H
#घोषणा _ARM64_KEXEC_H

/* Maximum physical address we can use pages from */

#घोषणा KEXEC_SOURCE_MEMORY_LIMIT (-1UL)

/* Maximum address we can reach in physical address mode */

#घोषणा KEXEC_DESTINATION_MEMORY_LIMIT (-1UL)

/* Maximum address we can use क्रम the control code buffer */

#घोषणा KEXEC_CONTROL_MEMORY_LIMIT (-1UL)

#घोषणा KEXEC_CONTROL_PAGE_SIZE 4096

#घोषणा KEXEC_ARCH KEXEC_ARCH_AARCH64

#अगर_अघोषित __ASSEMBLY__

/**
 * crash_setup_regs() - save रेजिस्टरs क्रम the panic kernel
 *
 * @newregs: रेजिस्टरs are saved here
 * @oldregs: रेजिस्टरs to be saved (may be %शून्य)
 */

अटल अंतरभूत व्योम crash_setup_regs(काष्ठा pt_regs *newregs,
				    काष्ठा pt_regs *oldregs)
अणु
	अगर (oldregs) अणु
		स_नकल(newregs, oldregs, माप(*newregs));
	पूर्ण अन्यथा अणु
		u64 पंचांगp1, पंचांगp2;

		__यंत्र__ __अस्थिर__ (
			"stp	 x0,   x1, [%2, #16 *  0]\n"
			"stp	 x2,   x3, [%2, #16 *  1]\n"
			"stp	 x4,   x5, [%2, #16 *  2]\n"
			"stp	 x6,   x7, [%2, #16 *  3]\n"
			"stp	 x8,   x9, [%2, #16 *  4]\n"
			"stp	x10,  x11, [%2, #16 *  5]\n"
			"stp	x12,  x13, [%2, #16 *  6]\n"
			"stp	x14,  x15, [%2, #16 *  7]\n"
			"stp	x16,  x17, [%2, #16 *  8]\n"
			"stp	x18,  x19, [%2, #16 *  9]\n"
			"stp	x20,  x21, [%2, #16 * 10]\n"
			"stp	x22,  x23, [%2, #16 * 11]\n"
			"stp	x24,  x25, [%2, #16 * 12]\n"
			"stp	x26,  x27, [%2, #16 * 13]\n"
			"stp	x28,  x29, [%2, #16 * 14]\n"
			"mov	 %0,  sp\n"
			"stp	x30,  %0,  [%2, #16 * 15]\n"

			"/* faked current PSTATE */\n"
			"mrs	 %0, CurrentEL\n"
			"mrs	 %1, SPSEL\n"
			"orr	 %0, %0, %1\n"
			"mrs	 %1, DAIF\n"
			"orr	 %0, %0, %1\n"
			"mrs	 %1, NZCV\n"
			"orr	 %0, %0, %1\n"
			/* pc */
			"adr	 %1, 1f\n"
		"1:\n"
			"stp	 %1, %0,   [%2, #16 * 16]\n"
			: "=&r" (पंचांगp1), "=&r" (पंचांगp2)
			: "r" (newregs)
			: "memory"
		);
	पूर्ण
पूर्ण

#अगर defined(CONFIG_KEXEC_CORE) && defined(CONFIG_HIBERNATION)
बाह्य bool crash_is_nosave(अचिन्हित दीर्घ pfn);
बाह्य व्योम crash_prepare_suspend(व्योम);
बाह्य व्योम crash_post_resume(व्योम);
#अन्यथा
अटल अंतरभूत bool crash_is_nosave(अचिन्हित दीर्घ pfn) अणुवापस false; पूर्ण
अटल अंतरभूत व्योम crash_prepare_suspend(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम crash_post_resume(व्योम) अणुपूर्ण
#पूर्ण_अगर

#घोषणा ARCH_HAS_KIMAGE_ARCH

काष्ठा kimage_arch अणु
	व्योम *dtb;
	phys_addr_t dtb_mem;
	phys_addr_t kern_reloc;
पूर्ण;

#अगर_घोषित CONFIG_KEXEC_खाता
बाह्य स्थिर काष्ठा kexec_file_ops kexec_image_ops;

काष्ठा kimage;

बाह्य पूर्णांक arch_kimage_file_post_load_cleanup(काष्ठा kimage *image);
बाह्य पूर्णांक load_other_segments(काष्ठा kimage *image,
		अचिन्हित दीर्घ kernel_load_addr, अचिन्हित दीर्घ kernel_size,
		अक्षर *initrd, अचिन्हित दीर्घ initrd_len,
		अक्षर *cmdline);
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर
