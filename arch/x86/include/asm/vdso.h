<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_VDSO_H
#घोषणा _ASM_X86_VDSO_H

#समावेश <यंत्र/page_types.h>
#समावेश <linux/linkage.h>
#समावेश <linux/init.h>

#अगर_अघोषित __ASSEMBLER__

#समावेश <linux/mm_types.h>

काष्ठा vdso_image अणु
	व्योम *data;
	अचिन्हित दीर्घ size;   /* Always a multiple of PAGE_SIZE */

	अचिन्हित दीर्घ alt, alt_len;
	अचिन्हित दीर्घ extable_base, extable_len;
	स्थिर व्योम *extable;

	दीर्घ sym_vvar_start;  /* Negative offset to the vvar area */

	दीर्घ sym_vvar_page;
	दीर्घ sym_pvघड़ी_page;
	दीर्घ sym_hvघड़ी_page;
	दीर्घ sym_समयns_page;
	दीर्घ sym_VDSO32_NOTE_MASK;
	दीर्घ sym___kernel_sigवापस;
	दीर्घ sym___kernel_rt_sigवापस;
	दीर्घ sym___kernel_vsyscall;
	दीर्घ sym_पूर्णांक80_landing_pad;
	दीर्घ sym_vdso32_sigवापस_landing_pad;
	दीर्घ sym_vdso32_rt_sigवापस_landing_pad;
पूर्ण;

#अगर_घोषित CONFIG_X86_64
बाह्य स्थिर काष्ठा vdso_image vdso_image_64;
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_X32
बाह्य स्थिर काष्ठा vdso_image vdso_image_x32;
#पूर्ण_अगर

#अगर defined CONFIG_X86_32 || defined CONFIG_COMPAT
बाह्य स्थिर काष्ठा vdso_image vdso_image_32;
#पूर्ण_अगर

बाह्य व्योम __init init_vdso_image(स्थिर काष्ठा vdso_image *image);

बाह्य पूर्णांक map_vdso_once(स्थिर काष्ठा vdso_image *image, अचिन्हित दीर्घ addr);

बाह्य bool fixup_vdso_exception(काष्ठा pt_regs *regs, पूर्णांक trapnr,
				 अचिन्हित दीर्घ error_code,
				 अचिन्हित दीर्घ fault_addr);
#पूर्ण_अगर /* __ASSEMBLER__ */

#पूर्ण_अगर /* _ASM_X86_VDSO_H */
