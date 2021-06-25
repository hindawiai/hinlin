<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
#समावेश <linux/kernel.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/hw_अवरोधpoपूर्णांक.h>
#समावेश <यंत्र/sstep.h>
#समावेश <यंत्र/cache.h>

अटल bool dar_in_user_range(अचिन्हित दीर्घ dar, काष्ठा arch_hw_अवरोधpoपूर्णांक *info)
अणु
	वापस ((info->address <= dar) && (dar - info->address < info->len));
पूर्ण

अटल bool ea_user_range_overlaps(अचिन्हित दीर्घ ea, पूर्णांक size,
				   काष्ठा arch_hw_अवरोधpoपूर्णांक *info)
अणु
	वापस ((ea < info->address + info->len) &&
		(ea + size > info->address));
पूर्ण

अटल bool dar_in_hw_range(अचिन्हित दीर्घ dar, काष्ठा arch_hw_अवरोधpoपूर्णांक *info)
अणु
	अचिन्हित दीर्घ hw_start_addr, hw_end_addr;

	hw_start_addr = ALIGN_DOWN(info->address, HW_BREAKPOINT_SIZE);
	hw_end_addr = ALIGN(info->address + info->len, HW_BREAKPOINT_SIZE);

	वापस ((hw_start_addr <= dar) && (hw_end_addr > dar));
पूर्ण

अटल bool ea_hw_range_overlaps(अचिन्हित दीर्घ ea, पूर्णांक size,
				 काष्ठा arch_hw_अवरोधpoपूर्णांक *info)
अणु
	अचिन्हित दीर्घ hw_start_addr, hw_end_addr;
	अचिन्हित दीर्घ align_size = HW_BREAKPOINT_SIZE;

	/*
	 * On p10 predecessors, quadword is handle dअगरferently then
	 * other inकाष्ठाions.
	 */
	अगर (!cpu_has_feature(CPU_FTR_ARCH_31) && size == 16)
		align_size = HW_BREAKPOINT_SIZE_QUADWORD;

	hw_start_addr = ALIGN_DOWN(info->address, align_size);
	hw_end_addr = ALIGN(info->address + info->len, align_size);

	वापस ((ea < hw_end_addr) && (ea + size > hw_start_addr));
पूर्ण

/*
 * If hw has multiple DAWR रेजिस्टरs, we also need to check all
 * dawrx स्थिरraपूर्णांक bits to confirm this is _really_ a valid event.
 * If type is UNKNOWN, but privilege level matches, consider it as
 * a positive match.
 */
अटल bool check_dawrx_स्थिरraपूर्णांकs(काष्ठा pt_regs *regs, पूर्णांक type,
				    काष्ठा arch_hw_अवरोधpoपूर्णांक *info)
अणु
	अगर (OP_IS_LOAD(type) && !(info->type & HW_BRK_TYPE_READ))
		वापस false;

	/*
	 * The Cache Management inकाष्ठाions other than dcbz never
	 * cause a match. i.e. अगर type is CACHEOP, the inकाष्ठाion
	 * is dcbz, and dcbz is treated as Store.
	 */
	अगर ((OP_IS_STORE(type) || type == CACHEOP) && !(info->type & HW_BRK_TYPE_WRITE))
		वापस false;

	अगर (is_kernel_addr(regs->nip) && !(info->type & HW_BRK_TYPE_KERNEL))
		वापस false;

	अगर (user_mode(regs) && !(info->type & HW_BRK_TYPE_USER))
		वापस false;

	वापस true;
पूर्ण

/*
 * Return true अगर the event is valid wrt dawr configuration,
 * including extraneous exception. Otherwise वापस false.
 */
bool wp_check_स्थिरraपूर्णांकs(काष्ठा pt_regs *regs, काष्ठा ppc_inst instr,
			  अचिन्हित दीर्घ ea, पूर्णांक type, पूर्णांक size,
			  काष्ठा arch_hw_अवरोधpoपूर्णांक *info)
अणु
	bool in_user_range = dar_in_user_range(regs->dar, info);
	bool dawrx_स्थिरraपूर्णांकs;

	/*
	 * 8xx supports only one अवरोधpoपूर्णांक and thus we can
	 * unconditionally वापस true.
	 */
	अगर (IS_ENABLED(CONFIG_PPC_8xx)) अणु
		अगर (!in_user_range)
			info->type |= HW_BRK_TYPE_EXTRANEOUS_IRQ;
		वापस true;
	पूर्ण

	अगर (unlikely(ppc_inst_equal(instr, ppc_inst(0)))) अणु
		अगर (cpu_has_feature(CPU_FTR_ARCH_31) &&
		    !dar_in_hw_range(regs->dar, info))
			वापस false;

		वापस true;
	पूर्ण

	dawrx_स्थिरraपूर्णांकs = check_dawrx_स्थिरraपूर्णांकs(regs, type, info);

	अगर (type == UNKNOWN) अणु
		अगर (cpu_has_feature(CPU_FTR_ARCH_31) &&
		    !dar_in_hw_range(regs->dar, info))
			वापस false;

		वापस dawrx_स्थिरraपूर्णांकs;
	पूर्ण

	अगर (ea_user_range_overlaps(ea, size, info))
		वापस dawrx_स्थिरraपूर्णांकs;

	अगर (ea_hw_range_overlaps(ea, size, info)) अणु
		अगर (dawrx_स्थिरraपूर्णांकs) अणु
			info->type |= HW_BRK_TYPE_EXTRANEOUS_IRQ;
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक cache_op_size(व्योम)
अणु
#अगर_घोषित __घातerpc64__
	वापस ppc64_caches.l1d.block_size;
#अन्यथा
	वापस L1_CACHE_BYTES;
#पूर्ण_अगर
पूर्ण

व्योम wp_get_instr_detail(काष्ठा pt_regs *regs, काष्ठा ppc_inst *instr,
			 पूर्णांक *type, पूर्णांक *size, अचिन्हित दीर्घ *ea)
अणु
	काष्ठा inकाष्ठाion_op op;

	अगर (__get_user_instr(*instr, (व्योम __user *)regs->nip))
		वापस;

	analyse_instr(&op, regs, *instr);
	*type = GETTYPE(op.type);
	*ea = op.ea;
#अगर_घोषित __घातerpc64__
	अगर (!(regs->msr & MSR_64BIT))
		*ea &= 0xffffffffUL;
#पूर्ण_अगर

	*size = GETSIZE(op.type);
	अगर (*type == CACHEOP) अणु
		*size = cache_op_size();
		*ea &= ~(*size - 1);
	पूर्ण अन्यथा अगर (*type == LOAD_VMX || *type == STORE_VMX) अणु
		*ea &= ~(*size - 1);
	पूर्ण
पूर्ण
