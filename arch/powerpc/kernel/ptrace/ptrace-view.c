<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

#समावेश <linux/regset.h>
#समावेश <linux/elf.h>
#समावेश <linux/nospec.h>
#समावेश <linux/pkeys.h>

#समावेश "ptrace-decl.h"

काष्ठा pt_regs_offset अणु
	स्थिर अक्षर *name;
	पूर्णांक offset;
पूर्ण;

#घोषणा STR(s)	#s			/* convert to string */
#घोषणा REG_OFFSET_NAME(r) अणु.name = #r, .offset = दुरत्व(काष्ठा pt_regs, r)पूर्ण
#घोषणा GPR_OFFSET_NAME(num)	\
	अणु.name = STR(r##num), .offset = दुरत्व(काष्ठा pt_regs, gpr[num])पूर्ण, \
	अणु.name = STR(gpr##num), .offset = दुरत्व(काष्ठा pt_regs, gpr[num])पूर्ण
#घोषणा REG_OFFSET_END अणु.name = शून्य, .offset = 0पूर्ण

अटल स्थिर काष्ठा pt_regs_offset regoffset_table[] = अणु
	GPR_OFFSET_NAME(0),
	GPR_OFFSET_NAME(1),
	GPR_OFFSET_NAME(2),
	GPR_OFFSET_NAME(3),
	GPR_OFFSET_NAME(4),
	GPR_OFFSET_NAME(5),
	GPR_OFFSET_NAME(6),
	GPR_OFFSET_NAME(7),
	GPR_OFFSET_NAME(8),
	GPR_OFFSET_NAME(9),
	GPR_OFFSET_NAME(10),
	GPR_OFFSET_NAME(11),
	GPR_OFFSET_NAME(12),
	GPR_OFFSET_NAME(13),
	GPR_OFFSET_NAME(14),
	GPR_OFFSET_NAME(15),
	GPR_OFFSET_NAME(16),
	GPR_OFFSET_NAME(17),
	GPR_OFFSET_NAME(18),
	GPR_OFFSET_NAME(19),
	GPR_OFFSET_NAME(20),
	GPR_OFFSET_NAME(21),
	GPR_OFFSET_NAME(22),
	GPR_OFFSET_NAME(23),
	GPR_OFFSET_NAME(24),
	GPR_OFFSET_NAME(25),
	GPR_OFFSET_NAME(26),
	GPR_OFFSET_NAME(27),
	GPR_OFFSET_NAME(28),
	GPR_OFFSET_NAME(29),
	GPR_OFFSET_NAME(30),
	GPR_OFFSET_NAME(31),
	REG_OFFSET_NAME(nip),
	REG_OFFSET_NAME(msr),
	REG_OFFSET_NAME(ctr),
	REG_OFFSET_NAME(link),
	REG_OFFSET_NAME(xer),
	REG_OFFSET_NAME(ccr),
#अगर_घोषित CONFIG_PPC64
	REG_OFFSET_NAME(softe),
#अन्यथा
	REG_OFFSET_NAME(mq),
#पूर्ण_अगर
	REG_OFFSET_NAME(trap),
	REG_OFFSET_NAME(dar),
	REG_OFFSET_NAME(dsisr),
	REG_OFFSET_END,
पूर्ण;

/**
 * regs_query_रेजिस्टर_offset() - query रेजिस्टर offset from its name
 * @name:	the name of a रेजिस्टर
 *
 * regs_query_रेजिस्टर_offset() वापसs the offset of a रेजिस्टर in काष्ठा
 * pt_regs from its name. If the name is invalid, this वापसs -EINVAL;
 */
पूर्णांक regs_query_रेजिस्टर_offset(स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा pt_regs_offset *roff;
	क्रम (roff = regoffset_table; roff->name != शून्य; roff++)
		अगर (!म_भेद(roff->name, name))
			वापस roff->offset;
	वापस -EINVAL;
पूर्ण

/**
 * regs_query_रेजिस्टर_name() - query रेजिस्टर name from its offset
 * @offset:	the offset of a रेजिस्टर in काष्ठा pt_regs.
 *
 * regs_query_रेजिस्टर_name() वापसs the name of a रेजिस्टर from its
 * offset in काष्ठा pt_regs. If the @offset is invalid, this वापसs शून्य;
 */
स्थिर अक्षर *regs_query_रेजिस्टर_name(अचिन्हित पूर्णांक offset)
अणु
	स्थिर काष्ठा pt_regs_offset *roff;
	क्रम (roff = regoffset_table; roff->name != शून्य; roff++)
		अगर (roff->offset == offset)
			वापस roff->name;
	वापस शून्य;
पूर्ण

/*
 * करोes not yet catch संकेतs sent when the child dies.
 * in निकास.c or in संकेत.c.
 */

अटल अचिन्हित दीर्घ get_user_msr(काष्ठा task_काष्ठा *task)
अणु
	वापस task->thपढ़ो.regs->msr | task->thपढ़ो.fpexc_mode;
पूर्ण

अटल __always_अंतरभूत पूर्णांक set_user_msr(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ msr)
अणु
	task->thपढ़ो.regs->msr &= ~MSR_DEBUGCHANGE;
	task->thपढ़ो.regs->msr |= msr & MSR_DEBUGCHANGE;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PPC64
अटल पूर्णांक get_user_dscr(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ *data)
अणु
	*data = task->thपढ़ो.dscr;
	वापस 0;
पूर्ण

अटल पूर्णांक set_user_dscr(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ dscr)
अणु
	task->thपढ़ो.dscr = dscr;
	task->thपढ़ो.dscr_inherit = 1;
	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक get_user_dscr(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ *data)
अणु
	वापस -EIO;
पूर्ण

अटल पूर्णांक set_user_dscr(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ dscr)
अणु
	वापस -EIO;
पूर्ण
#पूर्ण_अगर

/*
 * We prevent mucking around with the reserved area of trap
 * which are used पूर्णांकernally by the kernel.
 */
अटल __always_अंतरभूत पूर्णांक set_user_trap(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ trap)
अणु
	set_trap(task->thपढ़ो.regs, trap);
	वापस 0;
पूर्ण

/*
 * Get contents of रेजिस्टर REGNO in task TASK.
 */
पूर्णांक ptrace_get_reg(काष्ठा task_काष्ठा *task, पूर्णांक regno, अचिन्हित दीर्घ *data)
अणु
	अचिन्हित पूर्णांक regs_max;

	अगर (task->thपढ़ो.regs == शून्य || !data)
		वापस -EIO;

	अगर (regno == PT_MSR) अणु
		*data = get_user_msr(task);
		वापस 0;
	पूर्ण

	अगर (regno == PT_DSCR)
		वापस get_user_dscr(task, data);

	/*
	 * softe copies paca->irq_soft_mask variable state. Since irq_soft_mask is
	 * no more used as a flag, lets क्रमce usr to alway see the softe value as 1
	 * which means पूर्णांकerrupts are not soft disabled.
	 */
	अगर (IS_ENABLED(CONFIG_PPC64) && regno == PT_SOFTE) अणु
		*data = 1;
		वापस  0;
	पूर्ण

	regs_max = माप(काष्ठा user_pt_regs) / माप(अचिन्हित दीर्घ);
	अगर (regno < regs_max) अणु
		regno = array_index_nospec(regno, regs_max);
		*data = ((अचिन्हित दीर्घ *)task->thपढ़ो.regs)[regno];
		वापस 0;
	पूर्ण

	वापस -EIO;
पूर्ण

/*
 * Write contents of रेजिस्टर REGNO in task TASK.
 */
पूर्णांक ptrace_put_reg(काष्ठा task_काष्ठा *task, पूर्णांक regno, अचिन्हित दीर्घ data)
अणु
	अगर (task->thपढ़ो.regs == शून्य)
		वापस -EIO;

	अगर (regno == PT_MSR)
		वापस set_user_msr(task, data);
	अगर (regno == PT_TRAP)
		वापस set_user_trap(task, data);
	अगर (regno == PT_DSCR)
		वापस set_user_dscr(task, data);

	अगर (regno <= PT_MAX_PUT_REG) अणु
		regno = array_index_nospec(regno, PT_MAX_PUT_REG + 1);
		((अचिन्हित दीर्घ *)task->thपढ़ो.regs)[regno] = data;
		वापस 0;
	पूर्ण
	वापस -EIO;
पूर्ण

अटल पूर्णांक gpr_get(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		   काष्ठा membuf to)
अणु
	काष्ठा membuf to_msr = membuf_at(&to, दुरत्व(काष्ठा pt_regs, msr));
#अगर_घोषित CONFIG_PPC64
	काष्ठा membuf to_softe = membuf_at(&to, दुरत्व(काष्ठा pt_regs, softe));
#पूर्ण_अगर
	अगर (target->thपढ़ो.regs == शून्य)
		वापस -EIO;

	membuf_ग_लिखो(&to, target->thपढ़ो.regs, माप(काष्ठा user_pt_regs));

	membuf_store(&to_msr, get_user_msr(target));
#अगर_घोषित CONFIG_PPC64
	membuf_store(&to_softe, 0x1ul);
#पूर्ण_अगर
	वापस membuf_zero(&to, ELF_NGREG * माप(अचिन्हित दीर्घ) -
				 माप(काष्ठा user_pt_regs));
पूर्ण

अटल पूर्णांक gpr_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		   अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count, स्थिर व्योम *kbuf,
		   स्थिर व्योम __user *ubuf)
अणु
	अचिन्हित दीर्घ reg;
	पूर्णांक ret;

	अगर (target->thपढ़ो.regs == शून्य)
		वापस -EIO;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 target->thपढ़ो.regs,
				 0, PT_MSR * माप(reg));

	अगर (!ret && count > 0) अणु
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, &reg,
					 PT_MSR * माप(reg),
					 (PT_MSR + 1) * माप(reg));
		अगर (!ret)
			ret = set_user_msr(target, reg);
	पूर्ण

	BUILD_BUG_ON(दुरत्व(काष्ठा pt_regs, orig_gpr3) !=
		     दुरत्व(काष्ठा pt_regs, msr) + माप(दीर्घ));

	अगर (!ret)
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					 &target->thपढ़ो.regs->orig_gpr3,
					 PT_ORIG_R3 * माप(reg),
					 (PT_MAX_PUT_REG + 1) * माप(reg));

	अगर (PT_MAX_PUT_REG + 1 < PT_TRAP && !ret)
		ret = user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf,
						(PT_MAX_PUT_REG + 1) * माप(reg),
						PT_TRAP * माप(reg));

	अगर (!ret && count > 0) अणु
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, &reg,
					 PT_TRAP * माप(reg),
					 (PT_TRAP + 1) * माप(reg));
		अगर (!ret)
			ret = set_user_trap(target, reg);
	पूर्ण

	अगर (!ret)
		ret = user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf,
						(PT_TRAP + 1) * माप(reg), -1);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PPC64
अटल पूर्णांक ppr_get(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		   काष्ठा membuf to)
अणु
	वापस membuf_ग_लिखो(&to, &target->thपढ़ो.regs->ppr, माप(u64));
पूर्ण

अटल पूर्णांक ppr_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		   अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count, स्थिर व्योम *kbuf,
		   स्थिर व्योम __user *ubuf)
अणु
	वापस user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				  &target->thपढ़ो.regs->ppr, 0, माप(u64));
पूर्ण

अटल पूर्णांक dscr_get(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		    काष्ठा membuf to)
अणु
	वापस membuf_ग_लिखो(&to, &target->thपढ़ो.dscr, माप(u64));
पूर्ण
अटल पूर्णांक dscr_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		    अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count, स्थिर व्योम *kbuf,
		    स्थिर व्योम __user *ubuf)
अणु
	वापस user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				  &target->thपढ़ो.dscr, 0, माप(u64));
पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_BOOK3S_64
अटल पूर्णांक tar_get(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		   काष्ठा membuf to)
अणु
	वापस membuf_ग_लिखो(&to, &target->thपढ़ो.tar, माप(u64));
पूर्ण
अटल पूर्णांक tar_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		   अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count, स्थिर व्योम *kbuf,
		   स्थिर व्योम __user *ubuf)
अणु
	वापस user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				  &target->thपढ़ो.tar, 0, माप(u64));
पूर्ण

अटल पूर्णांक ebb_active(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset)
अणु
	अगर (!cpu_has_feature(CPU_FTR_ARCH_207S))
		वापस -ENODEV;

	अगर (target->thपढ़ो.used_ebb)
		वापस regset->n;

	वापस 0;
पूर्ण

अटल पूर्णांक ebb_get(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		   काष्ठा membuf to)
अणु
	/* Build tests */
	BUILD_BUG_ON(TSO(ebbrr) + माप(अचिन्हित दीर्घ) != TSO(ebbhr));
	BUILD_BUG_ON(TSO(ebbhr) + माप(अचिन्हित दीर्घ) != TSO(bescr));

	अगर (!cpu_has_feature(CPU_FTR_ARCH_207S))
		वापस -ENODEV;

	अगर (!target->thपढ़ो.used_ebb)
		वापस -ENODATA;

	वापस membuf_ग_लिखो(&to, &target->thपढ़ो.ebbrr, 3 * माप(अचिन्हित दीर्घ));
पूर्ण

अटल पूर्णांक ebb_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		   अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count, स्थिर व्योम *kbuf,
		   स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक ret = 0;

	/* Build tests */
	BUILD_BUG_ON(TSO(ebbrr) + माप(अचिन्हित दीर्घ) != TSO(ebbhr));
	BUILD_BUG_ON(TSO(ebbhr) + माप(अचिन्हित दीर्घ) != TSO(bescr));

	अगर (!cpu_has_feature(CPU_FTR_ARCH_207S))
		वापस -ENODEV;

	अगर (target->thपढ़ो.used_ebb)
		वापस -ENODATA;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, &target->thपढ़ो.ebbrr,
				 0, माप(अचिन्हित दीर्घ));

	अगर (!ret)
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					 &target->thपढ़ो.ebbhr, माप(अचिन्हित दीर्घ),
					 2 * माप(अचिन्हित दीर्घ));

	अगर (!ret)
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					 &target->thपढ़ो.bescr, 2 * माप(अचिन्हित दीर्घ),
					 3 * माप(अचिन्हित दीर्घ));

	वापस ret;
पूर्ण
अटल पूर्णांक pmu_active(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset)
अणु
	अगर (!cpu_has_feature(CPU_FTR_ARCH_207S))
		वापस -ENODEV;

	वापस regset->n;
पूर्ण

अटल पूर्णांक pmu_get(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		   काष्ठा membuf to)
अणु
	/* Build tests */
	BUILD_BUG_ON(TSO(siar) + माप(अचिन्हित दीर्घ) != TSO(sdar));
	BUILD_BUG_ON(TSO(sdar) + माप(अचिन्हित दीर्घ) != TSO(sier));
	BUILD_BUG_ON(TSO(sier) + माप(अचिन्हित दीर्घ) != TSO(mmcr2));
	BUILD_BUG_ON(TSO(mmcr2) + माप(अचिन्हित दीर्घ) != TSO(mmcr0));

	अगर (!cpu_has_feature(CPU_FTR_ARCH_207S))
		वापस -ENODEV;

	वापस membuf_ग_लिखो(&to, &target->thपढ़ो.siar, 5 * माप(अचिन्हित दीर्घ));
पूर्ण

अटल पूर्णांक pmu_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		   अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count, स्थिर व्योम *kbuf,
		   स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक ret = 0;

	/* Build tests */
	BUILD_BUG_ON(TSO(siar) + माप(अचिन्हित दीर्घ) != TSO(sdar));
	BUILD_BUG_ON(TSO(sdar) + माप(अचिन्हित दीर्घ) != TSO(sier));
	BUILD_BUG_ON(TSO(sier) + माप(अचिन्हित दीर्घ) != TSO(mmcr2));
	BUILD_BUG_ON(TSO(mmcr2) + माप(अचिन्हित दीर्घ) != TSO(mmcr0));

	अगर (!cpu_has_feature(CPU_FTR_ARCH_207S))
		वापस -ENODEV;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, &target->thपढ़ो.siar,
				 0, माप(अचिन्हित दीर्घ));

	अगर (!ret)
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					 &target->thपढ़ो.sdar, माप(अचिन्हित दीर्घ),
					 2 * माप(अचिन्हित दीर्घ));

	अगर (!ret)
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					 &target->thपढ़ो.sier, 2 * माप(अचिन्हित दीर्घ),
					 3 * माप(अचिन्हित दीर्घ));

	अगर (!ret)
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					 &target->thपढ़ो.mmcr2, 3 * माप(अचिन्हित दीर्घ),
					 4 * माप(अचिन्हित दीर्घ));

	अगर (!ret)
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					 &target->thपढ़ो.mmcr0, 4 * माप(अचिन्हित दीर्घ),
					 5 * माप(अचिन्हित दीर्घ));
	वापस ret;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_MEM_KEYS
अटल पूर्णांक pkey_active(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset)
अणु
	अगर (!arch_pkeys_enabled())
		वापस -ENODEV;

	वापस regset->n;
पूर्ण

अटल पूर्णांक pkey_get(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		    काष्ठा membuf to)
अणु

	अगर (!arch_pkeys_enabled())
		वापस -ENODEV;

	membuf_store(&to, target->thपढ़ो.regs->amr);
	membuf_store(&to, target->thपढ़ो.regs->iamr);
	वापस membuf_store(&to, शेष_uamor);
पूर्ण

अटल पूर्णांक pkey_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		    अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count, स्थिर व्योम *kbuf,
		    स्थिर व्योम __user *ubuf)
अणु
	u64 new_amr;
	पूर्णांक ret;

	अगर (!arch_pkeys_enabled())
		वापस -ENODEV;

	/* Only the AMR can be set from userspace */
	अगर (pos != 0 || count != माप(new_amr))
		वापस -EINVAL;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 &new_amr, 0, माप(new_amr));
	अगर (ret)
		वापस ret;

	/*
	 * UAMOR determines which bits of the AMR can be set from userspace.
	 * UAMOR value 0b11 indicates that the AMR value can be modअगरied
	 * from userspace. If the kernel is using a specअगरic key, we aव्योम
	 * userspace modअगरying the AMR value क्रम that key by masking them
	 * via UAMOR 0b00.
	 *
	 * Pick the AMR values क्रम the keys that kernel is using. This
	 * will be indicated by the ~शेष_uamor bits.
	 */
	target->thपढ़ो.regs->amr = (new_amr & शेष_uamor) |
		(target->thपढ़ो.regs->amr & ~शेष_uamor);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_MEM_KEYS */

अटल स्थिर काष्ठा user_regset native_regsets[] = अणु
	[REGSET_GPR] = अणु
		.core_note_type = NT_PRSTATUS, .n = ELF_NGREG,
		.size = माप(दीर्घ), .align = माप(दीर्घ),
		.regset_get = gpr_get, .set = gpr_set
	पूर्ण,
	[REGSET_FPR] = अणु
		.core_note_type = NT_PRFPREG, .n = ELF_NFPREG,
		.size = माप(द्विगुन), .align = माप(द्विगुन),
		.regset_get = fpr_get, .set = fpr_set
	पूर्ण,
#अगर_घोषित CONFIG_ALTIVEC
	[REGSET_VMX] = अणु
		.core_note_type = NT_PPC_VMX, .n = 34,
		.size = माप(vector128), .align = माप(vector128),
		.active = vr_active, .regset_get = vr_get, .set = vr_set
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_VSX
	[REGSET_VSX] = अणु
		.core_note_type = NT_PPC_VSX, .n = 32,
		.size = माप(द्विगुन), .align = माप(द्विगुन),
		.active = vsr_active, .regset_get = vsr_get, .set = vsr_set
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SPE
	[REGSET_SPE] = अणु
		.core_note_type = NT_PPC_SPE, .n = 35,
		.size = माप(u32), .align = माप(u32),
		.active = evr_active, .regset_get = evr_get, .set = evr_set
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	[REGSET_TM_CGPR] = अणु
		.core_note_type = NT_PPC_TM_CGPR, .n = ELF_NGREG,
		.size = माप(दीर्घ), .align = माप(दीर्घ),
		.active = पंचांग_cgpr_active, .regset_get = पंचांग_cgpr_get, .set = पंचांग_cgpr_set
	पूर्ण,
	[REGSET_TM_CFPR] = अणु
		.core_note_type = NT_PPC_TM_CFPR, .n = ELF_NFPREG,
		.size = माप(द्विगुन), .align = माप(द्विगुन),
		.active = पंचांग_cfpr_active, .regset_get = पंचांग_cfpr_get, .set = पंचांग_cfpr_set
	पूर्ण,
	[REGSET_TM_CVMX] = अणु
		.core_note_type = NT_PPC_TM_CVMX, .n = ELF_NVMX,
		.size = माप(vector128), .align = माप(vector128),
		.active = पंचांग_cvmx_active, .regset_get = पंचांग_cvmx_get, .set = पंचांग_cvmx_set
	पूर्ण,
	[REGSET_TM_CVSX] = अणु
		.core_note_type = NT_PPC_TM_CVSX, .n = ELF_NVSX,
		.size = माप(द्विगुन), .align = माप(द्विगुन),
		.active = पंचांग_cvsx_active, .regset_get = पंचांग_cvsx_get, .set = पंचांग_cvsx_set
	पूर्ण,
	[REGSET_TM_SPR] = अणु
		.core_note_type = NT_PPC_TM_SPR, .n = ELF_NTMSPRREG,
		.size = माप(u64), .align = माप(u64),
		.active = पंचांग_spr_active, .regset_get = पंचांग_spr_get, .set = पंचांग_spr_set
	पूर्ण,
	[REGSET_TM_CTAR] = अणु
		.core_note_type = NT_PPC_TM_CTAR, .n = 1,
		.size = माप(u64), .align = माप(u64),
		.active = पंचांग_tar_active, .regset_get = पंचांग_tar_get, .set = पंचांग_tar_set
	पूर्ण,
	[REGSET_TM_CPPR] = अणु
		.core_note_type = NT_PPC_TM_CPPR, .n = 1,
		.size = माप(u64), .align = माप(u64),
		.active = पंचांग_ppr_active, .regset_get = पंचांग_ppr_get, .set = पंचांग_ppr_set
	पूर्ण,
	[REGSET_TM_CDSCR] = अणु
		.core_note_type = NT_PPC_TM_CDSCR, .n = 1,
		.size = माप(u64), .align = माप(u64),
		.active = पंचांग_dscr_active, .regset_get = पंचांग_dscr_get, .set = पंचांग_dscr_set
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC64
	[REGSET_PPR] = अणु
		.core_note_type = NT_PPC_PPR, .n = 1,
		.size = माप(u64), .align = माप(u64),
		.regset_get = ppr_get, .set = ppr_set
	पूर्ण,
	[REGSET_DSCR] = अणु
		.core_note_type = NT_PPC_DSCR, .n = 1,
		.size = माप(u64), .align = माप(u64),
		.regset_get = dscr_get, .set = dscr_set
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	[REGSET_TAR] = अणु
		.core_note_type = NT_PPC_TAR, .n = 1,
		.size = माप(u64), .align = माप(u64),
		.regset_get = tar_get, .set = tar_set
	पूर्ण,
	[REGSET_EBB] = अणु
		.core_note_type = NT_PPC_EBB, .n = ELF_NEBB,
		.size = माप(u64), .align = माप(u64),
		.active = ebb_active, .regset_get = ebb_get, .set = ebb_set
	पूर्ण,
	[REGSET_PMR] = अणु
		.core_note_type = NT_PPC_PMU, .n = ELF_NPMU,
		.size = माप(u64), .align = माप(u64),
		.active = pmu_active, .regset_get = pmu_get, .set = pmu_set
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_MEM_KEYS
	[REGSET_PKEY] = अणु
		.core_note_type = NT_PPC_PKEY, .n = ELF_NPKEY,
		.size = माप(u64), .align = माप(u64),
		.active = pkey_active, .regset_get = pkey_get, .set = pkey_set
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

स्थिर काष्ठा user_regset_view user_ppc_native_view = अणु
	.name = UTS_MACHINE, .e_machine = ELF_ARCH, .ei_osabi = ELF_OSABI,
	.regsets = native_regsets, .n = ARRAY_SIZE(native_regsets)
पूर्ण;

#समावेश <linux/compat.h>

पूर्णांक gpr32_get_common(काष्ठा task_काष्ठा *target,
		     स्थिर काष्ठा user_regset *regset,
		     काष्ठा membuf to, अचिन्हित दीर्घ *regs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PT_MSR; i++)
		membuf_store(&to, (u32)regs[i]);
	membuf_store(&to, (u32)get_user_msr(target));
	क्रम (i++ ; i < PT_REGS_COUNT; i++)
		membuf_store(&to, (u32)regs[i]);
	वापस membuf_zero(&to, (ELF_NGREG - PT_REGS_COUNT) * माप(u32));
पूर्ण

पूर्णांक gpr32_set_common(काष्ठा task_काष्ठा *target,
		     स्थिर काष्ठा user_regset *regset,
		     अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		     स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf,
		     अचिन्हित दीर्घ *regs)
अणु
	स्थिर compat_uदीर्घ_t *k = kbuf;
	स्थिर compat_uदीर्घ_t __user *u = ubuf;
	compat_uदीर्घ_t reg;

	अगर (!kbuf && !user_पढ़ो_access_begin(u, count))
		वापस -EFAULT;

	pos /= माप(reg);
	count /= माप(reg);

	अगर (kbuf)
		क्रम (; count > 0 && pos < PT_MSR; --count)
			regs[pos++] = *k++;
	अन्यथा
		क्रम (; count > 0 && pos < PT_MSR; --count) अणु
			unsafe_get_user(reg, u++, Efault);
			regs[pos++] = reg;
		पूर्ण


	अगर (count > 0 && pos == PT_MSR) अणु
		अगर (kbuf)
			reg = *k++;
		अन्यथा
			unsafe_get_user(reg, u++, Efault);
		set_user_msr(target, reg);
		++pos;
		--count;
	पूर्ण

	अगर (kbuf) अणु
		क्रम (; count > 0 && pos <= PT_MAX_PUT_REG; --count)
			regs[pos++] = *k++;
		क्रम (; count > 0 && pos < PT_TRAP; --count, ++pos)
			++k;
	पूर्ण अन्यथा अणु
		क्रम (; count > 0 && pos <= PT_MAX_PUT_REG; --count) अणु
			unsafe_get_user(reg, u++, Efault);
			regs[pos++] = reg;
		पूर्ण
		क्रम (; count > 0 && pos < PT_TRAP; --count, ++pos)
			unsafe_get_user(reg, u++, Efault);
	पूर्ण

	अगर (count > 0 && pos == PT_TRAP) अणु
		अगर (kbuf)
			reg = *k++;
		अन्यथा
			unsafe_get_user(reg, u++, Efault);
		set_user_trap(target, reg);
		++pos;
		--count;
	पूर्ण
	अगर (!kbuf)
		user_पढ़ो_access_end();

	kbuf = k;
	ubuf = u;
	pos *= माप(reg);
	count *= माप(reg);
	वापस user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf,
					 (PT_TRAP + 1) * माप(reg), -1);

Efault:
	user_पढ़ो_access_end();
	वापस -EFAULT;
पूर्ण

अटल पूर्णांक gpr32_get(काष्ठा task_काष्ठा *target,
		     स्थिर काष्ठा user_regset *regset,
		     काष्ठा membuf to)
अणु
	अगर (target->thपढ़ो.regs == शून्य)
		वापस -EIO;

	वापस gpr32_get_common(target, regset, to,
			&target->thपढ़ो.regs->gpr[0]);
पूर्ण

अटल पूर्णांक gpr32_set(काष्ठा task_काष्ठा *target,
		     स्थिर काष्ठा user_regset *regset,
		     अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		     स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	अगर (target->thपढ़ो.regs == शून्य)
		वापस -EIO;

	वापस gpr32_set_common(target, regset, pos, count, kbuf, ubuf,
			&target->thपढ़ो.regs->gpr[0]);
पूर्ण

/*
 * These are the regset flavors matching the CONFIG_PPC32 native set.
 */
अटल स्थिर काष्ठा user_regset compat_regsets[] = अणु
	[REGSET_GPR] = अणु
		.core_note_type = NT_PRSTATUS, .n = ELF_NGREG,
		.size = माप(compat_दीर्घ_t), .align = माप(compat_दीर्घ_t),
		.regset_get = gpr32_get, .set = gpr32_set
	पूर्ण,
	[REGSET_FPR] = अणु
		.core_note_type = NT_PRFPREG, .n = ELF_NFPREG,
		.size = माप(द्विगुन), .align = माप(द्विगुन),
		.regset_get = fpr_get, .set = fpr_set
	पूर्ण,
#अगर_घोषित CONFIG_ALTIVEC
	[REGSET_VMX] = अणु
		.core_note_type = NT_PPC_VMX, .n = 34,
		.size = माप(vector128), .align = माप(vector128),
		.active = vr_active, .regset_get = vr_get, .set = vr_set
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SPE
	[REGSET_SPE] = अणु
		.core_note_type = NT_PPC_SPE, .n = 35,
		.size = माप(u32), .align = माप(u32),
		.active = evr_active, .regset_get = evr_get, .set = evr_set
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	[REGSET_TM_CGPR] = अणु
		.core_note_type = NT_PPC_TM_CGPR, .n = ELF_NGREG,
		.size = माप(दीर्घ), .align = माप(दीर्घ),
		.active = पंचांग_cgpr_active,
		.regset_get = पंचांग_cgpr32_get, .set = पंचांग_cgpr32_set
	पूर्ण,
	[REGSET_TM_CFPR] = अणु
		.core_note_type = NT_PPC_TM_CFPR, .n = ELF_NFPREG,
		.size = माप(द्विगुन), .align = माप(द्विगुन),
		.active = पंचांग_cfpr_active, .regset_get = पंचांग_cfpr_get, .set = पंचांग_cfpr_set
	पूर्ण,
	[REGSET_TM_CVMX] = अणु
		.core_note_type = NT_PPC_TM_CVMX, .n = ELF_NVMX,
		.size = माप(vector128), .align = माप(vector128),
		.active = पंचांग_cvmx_active, .regset_get = पंचांग_cvmx_get, .set = पंचांग_cvmx_set
	पूर्ण,
	[REGSET_TM_CVSX] = अणु
		.core_note_type = NT_PPC_TM_CVSX, .n = ELF_NVSX,
		.size = माप(द्विगुन), .align = माप(द्विगुन),
		.active = पंचांग_cvsx_active, .regset_get = पंचांग_cvsx_get, .set = पंचांग_cvsx_set
	पूर्ण,
	[REGSET_TM_SPR] = अणु
		.core_note_type = NT_PPC_TM_SPR, .n = ELF_NTMSPRREG,
		.size = माप(u64), .align = माप(u64),
		.active = पंचांग_spr_active, .regset_get = पंचांग_spr_get, .set = पंचांग_spr_set
	पूर्ण,
	[REGSET_TM_CTAR] = अणु
		.core_note_type = NT_PPC_TM_CTAR, .n = 1,
		.size = माप(u64), .align = माप(u64),
		.active = पंचांग_tar_active, .regset_get = पंचांग_tar_get, .set = पंचांग_tar_set
	पूर्ण,
	[REGSET_TM_CPPR] = अणु
		.core_note_type = NT_PPC_TM_CPPR, .n = 1,
		.size = माप(u64), .align = माप(u64),
		.active = पंचांग_ppr_active, .regset_get = पंचांग_ppr_get, .set = पंचांग_ppr_set
	पूर्ण,
	[REGSET_TM_CDSCR] = अणु
		.core_note_type = NT_PPC_TM_CDSCR, .n = 1,
		.size = माप(u64), .align = माप(u64),
		.active = पंचांग_dscr_active, .regset_get = पंचांग_dscr_get, .set = पंचांग_dscr_set
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC64
	[REGSET_PPR] = अणु
		.core_note_type = NT_PPC_PPR, .n = 1,
		.size = माप(u64), .align = माप(u64),
		.regset_get = ppr_get, .set = ppr_set
	पूर्ण,
	[REGSET_DSCR] = अणु
		.core_note_type = NT_PPC_DSCR, .n = 1,
		.size = माप(u64), .align = माप(u64),
		.regset_get = dscr_get, .set = dscr_set
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	[REGSET_TAR] = अणु
		.core_note_type = NT_PPC_TAR, .n = 1,
		.size = माप(u64), .align = माप(u64),
		.regset_get = tar_get, .set = tar_set
	पूर्ण,
	[REGSET_EBB] = अणु
		.core_note_type = NT_PPC_EBB, .n = ELF_NEBB,
		.size = माप(u64), .align = माप(u64),
		.active = ebb_active, .regset_get = ebb_get, .set = ebb_set
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा user_regset_view user_ppc_compat_view = अणु
	.name = "ppc", .e_machine = EM_PPC, .ei_osabi = ELF_OSABI,
	.regsets = compat_regsets, .n = ARRAY_SIZE(compat_regsets)
पूर्ण;

स्थिर काष्ठा user_regset_view *task_user_regset_view(काष्ठा task_काष्ठा *task)
अणु
	अगर (IS_ENABLED(CONFIG_PPC64) && test_tsk_thपढ़ो_flag(task, TIF_32BIT))
		वापस &user_ppc_compat_view;
	वापस &user_ppc_native_view;
पूर्ण
