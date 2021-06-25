<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _LINUX_UPROBES_H
#घोषणा _LINUX_UPROBES_H
/*
 * User-space Probes (UProbes)
 *
 * Copyright (C) IBM Corporation, 2008-2012
 * Authors:
 *	Srikar Dronamraju
 *	Jim Keniston
 * Copyright (C) 2011-2012 Red Hat, Inc., Peter Zijlstra
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/rbtree.h>
#समावेश <linux/types.h>
#समावेश <linux/रुको.h>

काष्ठा vm_area_काष्ठा;
काष्ठा mm_काष्ठा;
काष्ठा inode;
काष्ठा notअगरier_block;
काष्ठा page;

#घोषणा UPROBE_HANDLER_REMOVE		1
#घोषणा UPROBE_HANDLER_MASK		1

#घोषणा MAX_URETPROBE_DEPTH		64

क्रमागत uprobe_filter_ctx अणु
	UPROBE_FILTER_REGISTER,
	UPROBE_FILTER_UNREGISTER,
	UPROBE_FILTER_MMAP,
पूर्ण;

काष्ठा uprobe_consumer अणु
	पूर्णांक (*handler)(काष्ठा uprobe_consumer *self, काष्ठा pt_regs *regs);
	पूर्णांक (*ret_handler)(काष्ठा uprobe_consumer *self,
				अचिन्हित दीर्घ func,
				काष्ठा pt_regs *regs);
	bool (*filter)(काष्ठा uprobe_consumer *self,
				क्रमागत uprobe_filter_ctx ctx,
				काष्ठा mm_काष्ठा *mm);

	काष्ठा uprobe_consumer *next;
पूर्ण;

#अगर_घोषित CONFIG_UPROBES
#समावेश <यंत्र/uprobes.h>

क्रमागत uprobe_task_state अणु
	UTASK_RUNNING,
	UTASK_SSTEP,
	UTASK_SSTEP_ACK,
	UTASK_SSTEP_TRAPPED,
पूर्ण;

/*
 * uprobe_task: Metadata of a task जबतक it singlesteps.
 */
काष्ठा uprobe_task अणु
	क्रमागत uprobe_task_state		state;

	जोड़ अणु
		काष्ठा अणु
			काष्ठा arch_uprobe_task	autask;
			अचिन्हित दीर्घ		vaddr;
		पूर्ण;

		काष्ठा अणु
			काष्ठा callback_head	dup_xol_work;
			अचिन्हित दीर्घ		dup_xol_addr;
		पूर्ण;
	पूर्ण;

	काष्ठा uprobe			*active_uprobe;
	अचिन्हित दीर्घ			xol_vaddr;

	काष्ठा वापस_instance		*वापस_instances;
	अचिन्हित पूर्णांक			depth;
पूर्ण;

काष्ठा वापस_instance अणु
	काष्ठा uprobe		*uprobe;
	अचिन्हित दीर्घ		func;
	अचिन्हित दीर्घ		stack;		/* stack poपूर्णांकer */
	अचिन्हित दीर्घ		orig_ret_vaddr; /* original वापस address */
	bool			chained;	/* true, अगर instance is nested */

	काष्ठा वापस_instance	*next;		/* keep as stack */
पूर्ण;

क्रमागत rp_check अणु
	RP_CHECK_CALL,
	RP_CHECK_CHAIN_CALL,
	RP_CHECK_RET,
पूर्ण;

काष्ठा xol_area;

काष्ठा uprobes_state अणु
	काष्ठा xol_area		*xol_area;
पूर्ण;

बाह्य व्योम __init uprobes_init(व्योम);
बाह्य पूर्णांक set_swbp(काष्ठा arch_uprobe *aup, काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vaddr);
बाह्य पूर्णांक set_orig_insn(काष्ठा arch_uprobe *aup, काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vaddr);
बाह्य bool is_swbp_insn(uprobe_opcode_t *insn);
बाह्य bool is_trap_insn(uprobe_opcode_t *insn);
बाह्य अचिन्हित दीर्घ uprobe_get_swbp_addr(काष्ठा pt_regs *regs);
बाह्य अचिन्हित दीर्घ uprobe_get_trap_addr(काष्ठा pt_regs *regs);
बाह्य पूर्णांक uprobe_ग_लिखो_opcode(काष्ठा arch_uprobe *auprobe, काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vaddr, uprobe_opcode_t);
बाह्य पूर्णांक uprobe_रेजिस्टर(काष्ठा inode *inode, loff_t offset, काष्ठा uprobe_consumer *uc);
बाह्य पूर्णांक uprobe_रेजिस्टर_refctr(काष्ठा inode *inode, loff_t offset, loff_t ref_ctr_offset, काष्ठा uprobe_consumer *uc);
बाह्य पूर्णांक uprobe_apply(काष्ठा inode *inode, loff_t offset, काष्ठा uprobe_consumer *uc, bool);
बाह्य व्योम uprobe_unरेजिस्टर(काष्ठा inode *inode, loff_t offset, काष्ठा uprobe_consumer *uc);
बाह्य पूर्णांक uprobe_mmap(काष्ठा vm_area_काष्ठा *vma);
बाह्य व्योम uprobe_munmap(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम uprobe_start_dup_mmap(व्योम);
बाह्य व्योम uprobe_end_dup_mmap(व्योम);
बाह्य व्योम uprobe_dup_mmap(काष्ठा mm_काष्ठा *oldmm, काष्ठा mm_काष्ठा *newmm);
बाह्य व्योम uprobe_मुक्त_utask(काष्ठा task_काष्ठा *t);
बाह्य व्योम uprobe_copy_process(काष्ठा task_काष्ठा *t, अचिन्हित दीर्घ flags);
बाह्य पूर्णांक uprobe_post_sstep_notअगरier(काष्ठा pt_regs *regs);
बाह्य पूर्णांक uprobe_pre_sstep_notअगरier(काष्ठा pt_regs *regs);
बाह्य व्योम uprobe_notअगरy_resume(काष्ठा pt_regs *regs);
बाह्य bool uprobe_deny_संकेत(व्योम);
बाह्य bool arch_uprobe_skip_sstep(काष्ठा arch_uprobe *aup, काष्ठा pt_regs *regs);
बाह्य व्योम uprobe_clear_state(काष्ठा mm_काष्ठा *mm);
बाह्य पूर्णांक  arch_uprobe_analyze_insn(काष्ठा arch_uprobe *aup, काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr);
बाह्य पूर्णांक  arch_uprobe_pre_xol(काष्ठा arch_uprobe *aup, काष्ठा pt_regs *regs);
बाह्य पूर्णांक  arch_uprobe_post_xol(काष्ठा arch_uprobe *aup, काष्ठा pt_regs *regs);
बाह्य bool arch_uprobe_xol_was_trapped(काष्ठा task_काष्ठा *tsk);
बाह्य पूर्णांक  arch_uprobe_exception_notअगरy(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ val, व्योम *data);
बाह्य व्योम arch_uprobe_पात_xol(काष्ठा arch_uprobe *aup, काष्ठा pt_regs *regs);
बाह्य अचिन्हित दीर्घ arch_uretprobe_hijack_वापस_addr(अचिन्हित दीर्घ trampoline_vaddr, काष्ठा pt_regs *regs);
बाह्य bool arch_uretprobe_is_alive(काष्ठा वापस_instance *ret, क्रमागत rp_check ctx, काष्ठा pt_regs *regs);
बाह्य bool arch_uprobe_ignore(काष्ठा arch_uprobe *aup, काष्ठा pt_regs *regs);
बाह्य व्योम arch_uprobe_copy_ixol(काष्ठा page *page, अचिन्हित दीर्घ vaddr,
					 व्योम *src, अचिन्हित दीर्घ len);
#अन्यथा /* !CONFIG_UPROBES */
काष्ठा uprobes_state अणु
पूर्ण;

अटल अंतरभूत व्योम uprobes_init(व्योम)
अणु
पूर्ण

#घोषणा uprobe_get_trap_addr(regs)	inकाष्ठाion_poपूर्णांकer(regs)

अटल अंतरभूत पूर्णांक
uprobe_रेजिस्टर(काष्ठा inode *inode, loff_t offset, काष्ठा uprobe_consumer *uc)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक uprobe_रेजिस्टर_refctr(काष्ठा inode *inode, loff_t offset, loff_t ref_ctr_offset, काष्ठा uprobe_consumer *uc)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक
uprobe_apply(काष्ठा inode *inode, loff_t offset, काष्ठा uprobe_consumer *uc, bool add)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत व्योम
uprobe_unरेजिस्टर(काष्ठा inode *inode, loff_t offset, काष्ठा uprobe_consumer *uc)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक uprobe_mmap(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम
uprobe_munmap(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
पूर्ण
अटल अंतरभूत व्योम uprobe_start_dup_mmap(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम uprobe_end_dup_mmap(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम
uprobe_dup_mmap(काष्ठा mm_काष्ठा *oldmm, काष्ठा mm_काष्ठा *newmm)
अणु
पूर्ण
अटल अंतरभूत व्योम uprobe_notअगरy_resume(काष्ठा pt_regs *regs)
अणु
पूर्ण
अटल अंतरभूत bool uprobe_deny_संकेत(व्योम)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत व्योम uprobe_मुक्त_utask(काष्ठा task_काष्ठा *t)
अणु
पूर्ण
अटल अंतरभूत व्योम uprobe_copy_process(काष्ठा task_काष्ठा *t, अचिन्हित दीर्घ flags)
अणु
पूर्ण
अटल अंतरभूत व्योम uprobe_clear_state(काष्ठा mm_काष्ठा *mm)
अणु
पूर्ण
#पूर्ण_अगर /* !CONFIG_UPROBES */
#पूर्ण_अगर	/* _LINUX_UPROBES_H */
