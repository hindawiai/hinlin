<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_IOBITMAP_H
#घोषणा _ASM_X86_IOBITMAP_H

#समावेश <linux/refcount.h>
#समावेश <यंत्र/processor.h>

काष्ठा io_biपंचांगap अणु
	u64		sequence;
	refcount_t	refcnt;
	/* The maximum number of bytes to copy so all zero bits are covered */
	अचिन्हित पूर्णांक	max;
	अचिन्हित दीर्घ	biपंचांगap[IO_BITMAP_LONGS];
पूर्ण;

काष्ठा task_काष्ठा;

#अगर_घोषित CONFIG_X86_IOPL_IOPERM
व्योम io_biपंचांगap_share(काष्ठा task_काष्ठा *tsk);
व्योम io_biपंचांगap_निकास(काष्ठा task_काष्ठा *tsk);

अटल अंतरभूत व्योम native_tss_invalidate_io_biपंचांगap(व्योम)
अणु
	/*
	 * Invalidate the I/O biपंचांगap by moving io_biपंचांगap_base outside the
	 * TSS limit so any subsequent I/O access from user space will
	 * trigger a #GP.
	 *
	 * This is correct even when VMEXIT reग_लिखोs the TSS limit
	 * to 0x67 as the only requirement is that the base poपूर्णांकs
	 * outside the limit.
	 */
	this_cpu_ग_लिखो(cpu_tss_rw.x86_tss.io_biपंचांगap_base,
		       IO_BITMAP_OFFSET_INVALID);
पूर्ण

व्योम native_tss_update_io_biपंचांगap(व्योम);

#अगर_घोषित CONFIG_PARAVIRT_XXL
#समावेश <यंत्र/paravirt.h>
#अन्यथा
#घोषणा tss_update_io_biपंचांगap native_tss_update_io_biपंचांगap
#घोषणा tss_invalidate_io_biपंचांगap native_tss_invalidate_io_biपंचांगap
#पूर्ण_अगर

#अन्यथा
अटल अंतरभूत व्योम io_biपंचांगap_share(काष्ठा task_काष्ठा *tsk) अणु पूर्ण
अटल अंतरभूत व्योम io_biपंचांगap_निकास(काष्ठा task_काष्ठा *tsk) अणु पूर्ण
अटल अंतरभूत व्योम tss_update_io_biपंचांगap(व्योम) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
