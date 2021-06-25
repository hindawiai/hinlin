<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*---------------------------------------------------------------------------+
 |  fpu_प्रणाली.h                                                             |
 |                                                                           |
 | Copyright (C) 1992,1994,1997                                              |
 |                       W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |
 |                       Australia.  E-mail   billm@suburbia.net             |
 |                                                                           |
 +---------------------------------------------------------------------------*/

#अगर_अघोषित _FPU_SYSTEM_H
#घोषणा _FPU_SYSTEM_H

/* प्रणाली dependent definitions */

#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/mmu_context.h>

अटल अंतरभूत काष्ठा desc_काष्ठा FPU_get_ldt_descriptor(अचिन्हित seg)
अणु
	अटल काष्ठा desc_काष्ठा zero_desc;
	काष्ठा desc_काष्ठा ret = zero_desc;

#अगर_घोषित CONFIG_MODIFY_LDT_SYSCALL
	seg >>= 3;
	mutex_lock(&current->mm->context.lock);
	अगर (current->mm->context.ldt && seg < current->mm->context.ldt->nr_entries)
		ret = current->mm->context.ldt->entries[seg];
	mutex_unlock(&current->mm->context.lock);
#पूर्ण_अगर
	वापस ret;
पूर्ण

#घोषणा SEG_TYPE_WRITABLE	(1U << 1)
#घोषणा SEG_TYPE_EXPANDS_DOWN	(1U << 2)
#घोषणा SEG_TYPE_EXECUTE	(1U << 3)
#घोषणा SEG_TYPE_EXPAND_MASK	(SEG_TYPE_EXPANDS_DOWN | SEG_TYPE_EXECUTE)
#घोषणा SEG_TYPE_EXECUTE_MASK	(SEG_TYPE_WRITABLE | SEG_TYPE_EXECUTE)

अटल अंतरभूत अचिन्हित दीर्घ seg_get_base(काष्ठा desc_काष्ठा *d)
अणु
	अचिन्हित दीर्घ base = (अचिन्हित दीर्घ)d->base2 << 24;

	वापस base | ((अचिन्हित दीर्घ)d->base1 << 16) | d->base0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ seg_get_limit(काष्ठा desc_काष्ठा *d)
अणु
	वापस ((अचिन्हित दीर्घ)d->limit1 << 16) | d->limit0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ seg_get_granularity(काष्ठा desc_काष्ठा *d)
अणु
	वापस d->g ? 4096 : 1;
पूर्ण

अटल अंतरभूत bool seg_expands_करोwn(काष्ठा desc_काष्ठा *d)
अणु
	वापस (d->type & SEG_TYPE_EXPAND_MASK) == SEG_TYPE_EXPANDS_DOWN;
पूर्ण

अटल अंतरभूत bool seg_execute_only(काष्ठा desc_काष्ठा *d)
अणु
	वापस (d->type & SEG_TYPE_EXECUTE_MASK) == SEG_TYPE_EXECUTE;
पूर्ण

अटल अंतरभूत bool seg_writable(काष्ठा desc_काष्ठा *d)
अणु
	वापस (d->type & SEG_TYPE_EXECUTE_MASK) == SEG_TYPE_WRITABLE;
पूर्ण

#घोषणा I387			(&current->thपढ़ो.fpu.state)
#घोषणा FPU_info		(I387->soft.info)

#घोषणा FPU_CS			(*(अचिन्हित लघु *) &(FPU_info->regs->cs))
#घोषणा FPU_SS			(*(अचिन्हित लघु *) &(FPU_info->regs->ss))
#घोषणा FPU_DS			(*(अचिन्हित लघु *) &(FPU_info->regs->ds))
#घोषणा FPU_EAX			(FPU_info->regs->ax)
#घोषणा FPU_EFLAGS		(FPU_info->regs->flags)
#घोषणा FPU_EIP			(FPU_info->regs->ip)
#घोषणा FPU_ORIG_EIP		(FPU_info->___orig_eip)

#घोषणा FPU_lookahead           (I387->soft.lookahead)

/* nz अगर ip_offset and cs_selector are not to be set क्रम the current
   inकाष्ठाion. */
#घोषणा no_ip_update		(*(u_अक्षर *)&(I387->soft.no_update))
#घोषणा FPU_rm			(*(u_अक्षर *)&(I387->soft.rm))

/* Number of bytes of data which can be legally accessed by the current
   inकाष्ठाion. This only needs to hold a number <= 108, so a byte will करो. */
#घोषणा access_limit		(*(u_अक्षर *)&(I387->soft.alimit))

#घोषणा partial_status		(I387->soft.swd)
#घोषणा control_word		(I387->soft.cwd)
#घोषणा fpu_tag_word		(I387->soft.twd)
#घोषणा रेजिस्टरs		(I387->soft.st_space)
#घोषणा top			(I387->soft.ftop)

#घोषणा inकाष्ठाion_address	(*(काष्ठा address *)&I387->soft.fip)
#घोषणा opeअक्रम_address		(*(काष्ठा address *)&I387->soft.foo)

#घोषणा FPU_access_ok(y,z)	अगर ( !access_ok(y,z) ) \
				math_पात(FPU_info,संक_अंश)
#घोषणा FPU_पात		math_पात(FPU_info, संक_अंश)
#घोषणा FPU_copy_from_user(to, from, n)	\
		करो अणु अगर (copy_from_user(to, from, n)) FPU_पात; पूर्ण जबतक (0)

#अघोषित FPU_IGNORE_CODE_SEGV
#अगर_घोषित FPU_IGNORE_CODE_SEGV
/* access_ok() is very expensive, and causes the emulator to run
   about 20% slower अगर applied to the code. Anyway, errors due to bad
   code addresses should be much rarer than errors due to bad data
   addresses. */
#घोषणा	FPU_code_access_ok(z)
#अन्यथा
/* A simpler test than access_ok() can probably be करोne क्रम
   FPU_code_access_ok() because the only possible error is to step
   past the upper boundary of a legal code area. */
#घोषणा	FPU_code_access_ok(z) FPU_access_ok((व्योम __user *)FPU_EIP,z)
#पूर्ण_अगर

#घोषणा FPU_get_user(x,y) करो अणु अगर (get_user((x),(y))) FPU_पात; पूर्ण जबतक (0)
#घोषणा FPU_put_user(x,y) करो अणु अगर (put_user((x),(y))) FPU_पात; पूर्ण जबतक (0)

#पूर्ण_अगर
