<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HW_अवरोधpoपूर्णांक: a unअगरied kernel/user-space hardware अवरोधpoपूर्णांक facility,
 * using the CPU's debug रेजिस्टरs.
 *
 * Copyright (C) 2012 ARM Limited
 * Author: Will Deacon <will.deacon@arm.com>
 */

#घोषणा pr_fmt(fmt) "hw-breakpoint: " fmt

#समावेश <linux/compat.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/smp.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/current.h>
#समावेश <यंत्र/debug-monitors.h>
#समावेश <यंत्र/hw_अवरोधpoपूर्णांक.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/प्रणाली_misc.h>

/* Breakpoपूर्णांक currently in use क्रम each BRP. */
अटल DEFINE_PER_CPU(काष्ठा perf_event *, bp_on_reg[ARM_MAX_BRP]);

/* Watchpoपूर्णांक currently in use क्रम each WRP. */
अटल DEFINE_PER_CPU(काष्ठा perf_event *, wp_on_reg[ARM_MAX_WRP]);

/* Currently stepping a per-CPU kernel अवरोधpoपूर्णांक. */
अटल DEFINE_PER_CPU(पूर्णांक, stepping_kernel_bp);

/* Number of BRP/WRP रेजिस्टरs on this CPU. */
अटल पूर्णांक core_num_brps;
अटल पूर्णांक core_num_wrps;

पूर्णांक hw_अवरोधpoपूर्णांक_slots(पूर्णांक type)
अणु
	/*
	 * We can be called early, so करोn't rely on
	 * our अटल variables being initialised.
	 */
	चयन (type) अणु
	हाल TYPE_INST:
		वापस get_num_brps();
	हाल TYPE_DATA:
		वापस get_num_wrps();
	शेष:
		pr_warn("unknown slot type: %d\n", type);
		वापस 0;
	पूर्ण
पूर्ण

#घोषणा READ_WB_REG_CASE(OFF, N, REG, VAL)	\
	हाल (OFF + N):				\
		AARCH64_DBG_READ(N, REG, VAL);	\
		अवरोध

#घोषणा WRITE_WB_REG_CASE(OFF, N, REG, VAL)	\
	हाल (OFF + N):				\
		AARCH64_DBG_WRITE(N, REG, VAL);	\
		अवरोध

#घोषणा GEN_READ_WB_REG_CASES(OFF, REG, VAL)	\
	READ_WB_REG_CASE(OFF,  0, REG, VAL);	\
	READ_WB_REG_CASE(OFF,  1, REG, VAL);	\
	READ_WB_REG_CASE(OFF,  2, REG, VAL);	\
	READ_WB_REG_CASE(OFF,  3, REG, VAL);	\
	READ_WB_REG_CASE(OFF,  4, REG, VAL);	\
	READ_WB_REG_CASE(OFF,  5, REG, VAL);	\
	READ_WB_REG_CASE(OFF,  6, REG, VAL);	\
	READ_WB_REG_CASE(OFF,  7, REG, VAL);	\
	READ_WB_REG_CASE(OFF,  8, REG, VAL);	\
	READ_WB_REG_CASE(OFF,  9, REG, VAL);	\
	READ_WB_REG_CASE(OFF, 10, REG, VAL);	\
	READ_WB_REG_CASE(OFF, 11, REG, VAL);	\
	READ_WB_REG_CASE(OFF, 12, REG, VAL);	\
	READ_WB_REG_CASE(OFF, 13, REG, VAL);	\
	READ_WB_REG_CASE(OFF, 14, REG, VAL);	\
	READ_WB_REG_CASE(OFF, 15, REG, VAL)

#घोषणा GEN_WRITE_WB_REG_CASES(OFF, REG, VAL)	\
	WRITE_WB_REG_CASE(OFF,  0, REG, VAL);	\
	WRITE_WB_REG_CASE(OFF,  1, REG, VAL);	\
	WRITE_WB_REG_CASE(OFF,  2, REG, VAL);	\
	WRITE_WB_REG_CASE(OFF,  3, REG, VAL);	\
	WRITE_WB_REG_CASE(OFF,  4, REG, VAL);	\
	WRITE_WB_REG_CASE(OFF,  5, REG, VAL);	\
	WRITE_WB_REG_CASE(OFF,  6, REG, VAL);	\
	WRITE_WB_REG_CASE(OFF,  7, REG, VAL);	\
	WRITE_WB_REG_CASE(OFF,  8, REG, VAL);	\
	WRITE_WB_REG_CASE(OFF,  9, REG, VAL);	\
	WRITE_WB_REG_CASE(OFF, 10, REG, VAL);	\
	WRITE_WB_REG_CASE(OFF, 11, REG, VAL);	\
	WRITE_WB_REG_CASE(OFF, 12, REG, VAL);	\
	WRITE_WB_REG_CASE(OFF, 13, REG, VAL);	\
	WRITE_WB_REG_CASE(OFF, 14, REG, VAL);	\
	WRITE_WB_REG_CASE(OFF, 15, REG, VAL)

अटल u64 पढ़ो_wb_reg(पूर्णांक reg, पूर्णांक n)
अणु
	u64 val = 0;

	चयन (reg + n) अणु
	GEN_READ_WB_REG_CASES(AARCH64_DBG_REG_BVR, AARCH64_DBG_REG_NAME_BVR, val);
	GEN_READ_WB_REG_CASES(AARCH64_DBG_REG_BCR, AARCH64_DBG_REG_NAME_BCR, val);
	GEN_READ_WB_REG_CASES(AARCH64_DBG_REG_WVR, AARCH64_DBG_REG_NAME_WVR, val);
	GEN_READ_WB_REG_CASES(AARCH64_DBG_REG_WCR, AARCH64_DBG_REG_NAME_WCR, val);
	शेष:
		pr_warn("attempt to read from unknown breakpoint register %d\n", n);
	पूर्ण

	वापस val;
पूर्ण
NOKPROBE_SYMBOL(पढ़ो_wb_reg);

अटल व्योम ग_लिखो_wb_reg(पूर्णांक reg, पूर्णांक n, u64 val)
अणु
	चयन (reg + n) अणु
	GEN_WRITE_WB_REG_CASES(AARCH64_DBG_REG_BVR, AARCH64_DBG_REG_NAME_BVR, val);
	GEN_WRITE_WB_REG_CASES(AARCH64_DBG_REG_BCR, AARCH64_DBG_REG_NAME_BCR, val);
	GEN_WRITE_WB_REG_CASES(AARCH64_DBG_REG_WVR, AARCH64_DBG_REG_NAME_WVR, val);
	GEN_WRITE_WB_REG_CASES(AARCH64_DBG_REG_WCR, AARCH64_DBG_REG_NAME_WCR, val);
	शेष:
		pr_warn("attempt to write to unknown breakpoint register %d\n", n);
	पूर्ण
	isb();
पूर्ण
NOKPROBE_SYMBOL(ग_लिखो_wb_reg);

/*
 * Convert a अवरोधpoपूर्णांक privilege level to the corresponding exception
 * level.
 */
अटल क्रमागत dbg_active_el debug_exception_level(पूर्णांक privilege)
अणु
	चयन (privilege) अणु
	हाल AARCH64_BREAKPOINT_EL0:
		वापस DBG_ACTIVE_EL0;
	हाल AARCH64_BREAKPOINT_EL1:
		वापस DBG_ACTIVE_EL1;
	शेष:
		pr_warn("invalid breakpoint privilege level %d\n", privilege);
		वापस -EINVAL;
	पूर्ण
पूर्ण
NOKPROBE_SYMBOL(debug_exception_level);

क्रमागत hw_अवरोधpoपूर्णांक_ops अणु
	HW_BREAKPOINT_INSTALL,
	HW_BREAKPOINT_UNINSTALL,
	HW_BREAKPOINT_RESTORE
पूर्ण;

अटल पूर्णांक is_compat_bp(काष्ठा perf_event *bp)
अणु
	काष्ठा task_काष्ठा *tsk = bp->hw.target;

	/*
	 * tsk can be शून्य क्रम per-cpu (non-ptrace) अवरोधpoपूर्णांकs.
	 * In this हाल, use the native पूर्णांकerface, since we करोn't have
	 * the notion of a "compat CPU" and could end up relying on
	 * deprecated behaviour अगर we use unaligned watchpoपूर्णांकs in
	 * AArch64 state.
	 */
	वापस tsk && is_compat_thपढ़ो(task_thपढ़ो_info(tsk));
पूर्ण

/**
 * hw_अवरोधpoपूर्णांक_slot_setup - Find and setup a perf slot according to
 *			      operations
 *
 * @slots: poपूर्णांकer to array of slots
 * @max_slots: max number of slots
 * @bp: perf_event to setup
 * @ops: operation to be carried out on the slot
 *
 * Return:
 *	slot index on success
 *	-ENOSPC अगर no slot is available/matches
 *	-EINVAL on wrong operations parameter
 */
अटल पूर्णांक hw_अवरोधpoपूर्णांक_slot_setup(काष्ठा perf_event **slots, पूर्णांक max_slots,
				    काष्ठा perf_event *bp,
				    क्रमागत hw_अवरोधpoपूर्णांक_ops ops)
अणु
	पूर्णांक i;
	काष्ठा perf_event **slot;

	क्रम (i = 0; i < max_slots; ++i) अणु
		slot = &slots[i];
		चयन (ops) अणु
		हाल HW_BREAKPOINT_INSTALL:
			अगर (!*slot) अणु
				*slot = bp;
				वापस i;
			पूर्ण
			अवरोध;
		हाल HW_BREAKPOINT_UNINSTALL:
			अगर (*slot == bp) अणु
				*slot = शून्य;
				वापस i;
			पूर्ण
			अवरोध;
		हाल HW_BREAKPOINT_RESTORE:
			अगर (*slot == bp)
				वापस i;
			अवरोध;
		शेष:
			pr_warn_once("Unhandled hw breakpoint ops %d\n", ops);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस -ENOSPC;
पूर्ण

अटल पूर्णांक hw_अवरोधpoपूर्णांक_control(काष्ठा perf_event *bp,
				 क्रमागत hw_अवरोधpoपूर्णांक_ops ops)
अणु
	काष्ठा arch_hw_अवरोधpoपूर्णांक *info = counter_arch_bp(bp);
	काष्ठा perf_event **slots;
	काष्ठा debug_info *debug_info = &current->thपढ़ो.debug;
	पूर्णांक i, max_slots, ctrl_reg, val_reg, reg_enable;
	क्रमागत dbg_active_el dbg_el = debug_exception_level(info->ctrl.privilege);
	u32 ctrl;

	अगर (info->ctrl.type == ARM_BREAKPOINT_EXECUTE) अणु
		/* Breakpoपूर्णांक */
		ctrl_reg = AARCH64_DBG_REG_BCR;
		val_reg = AARCH64_DBG_REG_BVR;
		slots = this_cpu_ptr(bp_on_reg);
		max_slots = core_num_brps;
		reg_enable = !debug_info->bps_disabled;
	पूर्ण अन्यथा अणु
		/* Watchpoपूर्णांक */
		ctrl_reg = AARCH64_DBG_REG_WCR;
		val_reg = AARCH64_DBG_REG_WVR;
		slots = this_cpu_ptr(wp_on_reg);
		max_slots = core_num_wrps;
		reg_enable = !debug_info->wps_disabled;
	पूर्ण

	i = hw_अवरोधpoपूर्णांक_slot_setup(slots, max_slots, bp, ops);

	अगर (WARN_ONCE(i < 0, "Can't find any breakpoint slot"))
		वापस i;

	चयन (ops) अणु
	हाल HW_BREAKPOINT_INSTALL:
		/*
		 * Ensure debug monitors are enabled at the correct exception
		 * level.
		 */
		enable_debug_monitors(dbg_el);
		fallthrough;
	हाल HW_BREAKPOINT_RESTORE:
		/* Setup the address रेजिस्टर. */
		ग_लिखो_wb_reg(val_reg, i, info->address);

		/* Setup the control रेजिस्टर. */
		ctrl = encode_ctrl_reg(info->ctrl);
		ग_लिखो_wb_reg(ctrl_reg, i,
			     reg_enable ? ctrl | 0x1 : ctrl & ~0x1);
		अवरोध;
	हाल HW_BREAKPOINT_UNINSTALL:
		/* Reset the control रेजिस्टर. */
		ग_लिखो_wb_reg(ctrl_reg, i, 0);

		/*
		 * Release the debug monitors क्रम the correct exception
		 * level.
		 */
		disable_debug_monitors(dbg_el);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Install a perf counter अवरोधpoपूर्णांक.
 */
पूर्णांक arch_install_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp)
अणु
	वापस hw_अवरोधpoपूर्णांक_control(bp, HW_BREAKPOINT_INSTALL);
पूर्ण

व्योम arch_uninstall_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp)
अणु
	hw_अवरोधpoपूर्णांक_control(bp, HW_BREAKPOINT_UNINSTALL);
पूर्ण

अटल पूर्णांक get_hbp_len(u8 hbp_len)
अणु
	अचिन्हित पूर्णांक len_in_bytes = 0;

	चयन (hbp_len) अणु
	हाल ARM_BREAKPOINT_LEN_1:
		len_in_bytes = 1;
		अवरोध;
	हाल ARM_BREAKPOINT_LEN_2:
		len_in_bytes = 2;
		अवरोध;
	हाल ARM_BREAKPOINT_LEN_3:
		len_in_bytes = 3;
		अवरोध;
	हाल ARM_BREAKPOINT_LEN_4:
		len_in_bytes = 4;
		अवरोध;
	हाल ARM_BREAKPOINT_LEN_5:
		len_in_bytes = 5;
		अवरोध;
	हाल ARM_BREAKPOINT_LEN_6:
		len_in_bytes = 6;
		अवरोध;
	हाल ARM_BREAKPOINT_LEN_7:
		len_in_bytes = 7;
		अवरोध;
	हाल ARM_BREAKPOINT_LEN_8:
		len_in_bytes = 8;
		अवरोध;
	पूर्ण

	वापस len_in_bytes;
पूर्ण

/*
 * Check whether bp भव address is in kernel space.
 */
पूर्णांक arch_check_bp_in_kernelspace(काष्ठा arch_hw_अवरोधpoपूर्णांक *hw)
अणु
	अचिन्हित पूर्णांक len;
	अचिन्हित दीर्घ va;

	va = hw->address;
	len = get_hbp_len(hw->ctrl.len);

	वापस (va >= TASK_SIZE) && ((va + len - 1) >= TASK_SIZE);
पूर्ण

/*
 * Extract generic type and length encodings from an arch_hw_अवरोधpoपूर्णांक_ctrl.
 * Hopefully this will disappear when ptrace can bypass the conversion
 * to generic अवरोधpoपूर्णांक descriptions.
 */
पूर्णांक arch_bp_generic_fields(काष्ठा arch_hw_अवरोधpoपूर्णांक_ctrl ctrl,
			   पूर्णांक *gen_len, पूर्णांक *gen_type, पूर्णांक *offset)
अणु
	/* Type */
	चयन (ctrl.type) अणु
	हाल ARM_BREAKPOINT_EXECUTE:
		*gen_type = HW_BREAKPOINT_X;
		अवरोध;
	हाल ARM_BREAKPOINT_LOAD:
		*gen_type = HW_BREAKPOINT_R;
		अवरोध;
	हाल ARM_BREAKPOINT_STORE:
		*gen_type = HW_BREAKPOINT_W;
		अवरोध;
	हाल ARM_BREAKPOINT_LOAD | ARM_BREAKPOINT_STORE:
		*gen_type = HW_BREAKPOINT_RW;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!ctrl.len)
		वापस -EINVAL;
	*offset = __ffs(ctrl.len);

	/* Len */
	चयन (ctrl.len >> *offset) अणु
	हाल ARM_BREAKPOINT_LEN_1:
		*gen_len = HW_BREAKPOINT_LEN_1;
		अवरोध;
	हाल ARM_BREAKPOINT_LEN_2:
		*gen_len = HW_BREAKPOINT_LEN_2;
		अवरोध;
	हाल ARM_BREAKPOINT_LEN_3:
		*gen_len = HW_BREAKPOINT_LEN_3;
		अवरोध;
	हाल ARM_BREAKPOINT_LEN_4:
		*gen_len = HW_BREAKPOINT_LEN_4;
		अवरोध;
	हाल ARM_BREAKPOINT_LEN_5:
		*gen_len = HW_BREAKPOINT_LEN_5;
		अवरोध;
	हाल ARM_BREAKPOINT_LEN_6:
		*gen_len = HW_BREAKPOINT_LEN_6;
		अवरोध;
	हाल ARM_BREAKPOINT_LEN_7:
		*gen_len = HW_BREAKPOINT_LEN_7;
		अवरोध;
	हाल ARM_BREAKPOINT_LEN_8:
		*gen_len = HW_BREAKPOINT_LEN_8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Conकाष्ठा an arch_hw_अवरोधpoपूर्णांक from a perf_event.
 */
अटल पूर्णांक arch_build_bp_info(काष्ठा perf_event *bp,
			      स्थिर काष्ठा perf_event_attr *attr,
			      काष्ठा arch_hw_अवरोधpoपूर्णांक *hw)
अणु
	/* Type */
	चयन (attr->bp_type) अणु
	हाल HW_BREAKPOINT_X:
		hw->ctrl.type = ARM_BREAKPOINT_EXECUTE;
		अवरोध;
	हाल HW_BREAKPOINT_R:
		hw->ctrl.type = ARM_BREAKPOINT_LOAD;
		अवरोध;
	हाल HW_BREAKPOINT_W:
		hw->ctrl.type = ARM_BREAKPOINT_STORE;
		अवरोध;
	हाल HW_BREAKPOINT_RW:
		hw->ctrl.type = ARM_BREAKPOINT_LOAD | ARM_BREAKPOINT_STORE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Len */
	चयन (attr->bp_len) अणु
	हाल HW_BREAKPOINT_LEN_1:
		hw->ctrl.len = ARM_BREAKPOINT_LEN_1;
		अवरोध;
	हाल HW_BREAKPOINT_LEN_2:
		hw->ctrl.len = ARM_BREAKPOINT_LEN_2;
		अवरोध;
	हाल HW_BREAKPOINT_LEN_3:
		hw->ctrl.len = ARM_BREAKPOINT_LEN_3;
		अवरोध;
	हाल HW_BREAKPOINT_LEN_4:
		hw->ctrl.len = ARM_BREAKPOINT_LEN_4;
		अवरोध;
	हाल HW_BREAKPOINT_LEN_5:
		hw->ctrl.len = ARM_BREAKPOINT_LEN_5;
		अवरोध;
	हाल HW_BREAKPOINT_LEN_6:
		hw->ctrl.len = ARM_BREAKPOINT_LEN_6;
		अवरोध;
	हाल HW_BREAKPOINT_LEN_7:
		hw->ctrl.len = ARM_BREAKPOINT_LEN_7;
		अवरोध;
	हाल HW_BREAKPOINT_LEN_8:
		hw->ctrl.len = ARM_BREAKPOINT_LEN_8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * On AArch64, we only permit अवरोधpoपूर्णांकs of length 4, whereas
	 * AArch32 also requires अवरोधpoपूर्णांकs of length 2 क्रम Thumb.
	 * Watchpoपूर्णांकs can be of length 1, 2, 4 or 8 bytes.
	 */
	अगर (hw->ctrl.type == ARM_BREAKPOINT_EXECUTE) अणु
		अगर (is_compat_bp(bp)) अणु
			अगर (hw->ctrl.len != ARM_BREAKPOINT_LEN_2 &&
			    hw->ctrl.len != ARM_BREAKPOINT_LEN_4)
				वापस -EINVAL;
		पूर्ण अन्यथा अगर (hw->ctrl.len != ARM_BREAKPOINT_LEN_4) अणु
			/*
			 * FIXME: Some tools (I'm looking at you perf) assume
			 *	  that अवरोधpoपूर्णांकs should be माप(दीर्घ). This
			 *	  is nonsense. For now, we fix up the parameter
			 *	  but we should probably वापस -EINVAL instead.
			 */
			hw->ctrl.len = ARM_BREAKPOINT_LEN_4;
		पूर्ण
	पूर्ण

	/* Address */
	hw->address = attr->bp_addr;

	/*
	 * Privilege
	 * Note that we disallow combined EL0/EL1 अवरोधpoपूर्णांकs because
	 * that would complicate the stepping code.
	 */
	अगर (arch_check_bp_in_kernelspace(hw))
		hw->ctrl.privilege = AARCH64_BREAKPOINT_EL1;
	अन्यथा
		hw->ctrl.privilege = AARCH64_BREAKPOINT_EL0;

	/* Enabled? */
	hw->ctrl.enabled = !attr->disabled;

	वापस 0;
पूर्ण

/*
 * Validate the arch-specअगरic HW Breakpoपूर्णांक रेजिस्टर settings.
 */
पूर्णांक hw_अवरोधpoपूर्णांक_arch_parse(काष्ठा perf_event *bp,
			     स्थिर काष्ठा perf_event_attr *attr,
			     काष्ठा arch_hw_अवरोधpoपूर्णांक *hw)
अणु
	पूर्णांक ret;
	u64 alignment_mask, offset;

	/* Build the arch_hw_अवरोधpoपूर्णांक. */
	ret = arch_build_bp_info(bp, attr, hw);
	अगर (ret)
		वापस ret;

	/*
	 * Check address alignment.
	 * We करोn't करो any clever alignment correction क्रम watchpoपूर्णांकs
	 * because using 64-bit unaligned addresses is deprecated क्रम
	 * AArch64.
	 *
	 * AArch32 tasks expect some simple alignment fixups, so emulate
	 * that here.
	 */
	अगर (is_compat_bp(bp)) अणु
		अगर (hw->ctrl.len == ARM_BREAKPOINT_LEN_8)
			alignment_mask = 0x7;
		अन्यथा
			alignment_mask = 0x3;
		offset = hw->address & alignment_mask;
		चयन (offset) अणु
		हाल 0:
			/* Aligned */
			अवरोध;
		हाल 1:
		हाल 2:
			/* Allow halfword watchpoपूर्णांकs and अवरोधpoपूर्णांकs. */
			अगर (hw->ctrl.len == ARM_BREAKPOINT_LEN_2)
				अवरोध;

			fallthrough;
		हाल 3:
			/* Allow single byte watchpoपूर्णांक. */
			अगर (hw->ctrl.len == ARM_BREAKPOINT_LEN_1)
				अवरोध;

			fallthrough;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (hw->ctrl.type == ARM_BREAKPOINT_EXECUTE)
			alignment_mask = 0x3;
		अन्यथा
			alignment_mask = 0x7;
		offset = hw->address & alignment_mask;
	पूर्ण

	hw->address &= ~alignment_mask;
	hw->ctrl.len <<= offset;

	/*
	 * Disallow per-task kernel अवरोधpoपूर्णांकs since these would
	 * complicate the stepping code.
	 */
	अगर (hw->ctrl.privilege == AARCH64_BREAKPOINT_EL1 && bp->hw.target)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/*
 * Enable/disable all of the अवरोधpoपूर्णांकs active at the specअगरied
 * exception level at the रेजिस्टर level.
 * This is used when single-stepping after a अवरोधpoपूर्णांक exception.
 */
अटल व्योम toggle_bp_रेजिस्टरs(पूर्णांक reg, क्रमागत dbg_active_el el, पूर्णांक enable)
अणु
	पूर्णांक i, max_slots, privilege;
	u32 ctrl;
	काष्ठा perf_event **slots;

	चयन (reg) अणु
	हाल AARCH64_DBG_REG_BCR:
		slots = this_cpu_ptr(bp_on_reg);
		max_slots = core_num_brps;
		अवरोध;
	हाल AARCH64_DBG_REG_WCR:
		slots = this_cpu_ptr(wp_on_reg);
		max_slots = core_num_wrps;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	क्रम (i = 0; i < max_slots; ++i) अणु
		अगर (!slots[i])
			जारी;

		privilege = counter_arch_bp(slots[i])->ctrl.privilege;
		अगर (debug_exception_level(privilege) != el)
			जारी;

		ctrl = पढ़ो_wb_reg(reg, i);
		अगर (enable)
			ctrl |= 0x1;
		अन्यथा
			ctrl &= ~0x1;
		ग_लिखो_wb_reg(reg, i, ctrl);
	पूर्ण
पूर्ण
NOKPROBE_SYMBOL(toggle_bp_रेजिस्टरs);

/*
 * Debug exception handlers.
 */
अटल पूर्णांक अवरोधpoपूर्णांक_handler(अचिन्हित दीर्घ unused, अचिन्हित पूर्णांक esr,
			      काष्ठा pt_regs *regs)
अणु
	पूर्णांक i, step = 0, *kernel_step;
	u32 ctrl_reg;
	u64 addr, val;
	काष्ठा perf_event *bp, **slots;
	काष्ठा debug_info *debug_info;
	काष्ठा arch_hw_अवरोधpoपूर्णांक_ctrl ctrl;

	slots = this_cpu_ptr(bp_on_reg);
	addr = inकाष्ठाion_poपूर्णांकer(regs);
	debug_info = &current->thपढ़ो.debug;

	क्रम (i = 0; i < core_num_brps; ++i) अणु
		rcu_पढ़ो_lock();

		bp = slots[i];

		अगर (bp == शून्य)
			जाओ unlock;

		/* Check अगर the अवरोधpoपूर्णांक value matches. */
		val = पढ़ो_wb_reg(AARCH64_DBG_REG_BVR, i);
		अगर (val != (addr & ~0x3))
			जाओ unlock;

		/* Possible match, check the byte address select to confirm. */
		ctrl_reg = पढ़ो_wb_reg(AARCH64_DBG_REG_BCR, i);
		decode_ctrl_reg(ctrl_reg, &ctrl);
		अगर (!((1 << (addr & 0x3)) & ctrl.len))
			जाओ unlock;

		counter_arch_bp(bp)->trigger = addr;
		perf_bp_event(bp, regs);

		/* Do we need to handle the stepping? */
		अगर (is_शेष_overflow_handler(bp))
			step = 1;
unlock:
		rcu_पढ़ो_unlock();
	पूर्ण

	अगर (!step)
		वापस 0;

	अगर (user_mode(regs)) अणु
		debug_info->bps_disabled = 1;
		toggle_bp_रेजिस्टरs(AARCH64_DBG_REG_BCR, DBG_ACTIVE_EL0, 0);

		/* If we're alपढ़ोy stepping a watchpoपूर्णांक, just वापस. */
		अगर (debug_info->wps_disabled)
			वापस 0;

		अगर (test_thपढ़ो_flag(TIF_SINGLESTEP))
			debug_info->suspended_step = 1;
		अन्यथा
			user_enable_single_step(current);
	पूर्ण अन्यथा अणु
		toggle_bp_रेजिस्टरs(AARCH64_DBG_REG_BCR, DBG_ACTIVE_EL1, 0);
		kernel_step = this_cpu_ptr(&stepping_kernel_bp);

		अगर (*kernel_step != ARM_KERNEL_STEP_NONE)
			वापस 0;

		अगर (kernel_active_single_step()) अणु
			*kernel_step = ARM_KERNEL_STEP_SUSPEND;
		पूर्ण अन्यथा अणु
			*kernel_step = ARM_KERNEL_STEP_ACTIVE;
			kernel_enable_single_step(regs);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
NOKPROBE_SYMBOL(अवरोधpoपूर्णांक_handler);

/*
 * Arm64 hardware करोes not always report a watchpoपूर्णांक hit address that matches
 * one of the watchpoपूर्णांकs set. It can also report an address "near" the
 * watchpoपूर्णांक अगर a single inकाष्ठाion access both watched and unwatched
 * addresses. There is no straight-क्रमward way, लघु of disassembling the
 * offending inकाष्ठाion, to map that address back to the watchpoपूर्णांक. This
 * function computes the distance of the memory access from the watchpoपूर्णांक as a
 * heuristic क्रम the likelyhood that a given access triggered the watchpoपूर्णांक.
 *
 * See Section D2.10.5 "Determining the memory location that caused a Watchpoपूर्णांक
 * exception" of ARMv8 Architecture Reference Manual क्रम details.
 *
 * The function वापसs the distance of the address from the bytes watched by
 * the watchpoपूर्णांक. In हाल of an exact match, it वापसs 0.
 */
अटल u64 get_distance_from_watchpoपूर्णांक(अचिन्हित दीर्घ addr, u64 val,
					काष्ठा arch_hw_अवरोधpoपूर्णांक_ctrl *ctrl)
अणु
	u64 wp_low, wp_high;
	u32 lens, lene;

	addr = untagged_addr(addr);

	lens = __ffs(ctrl->len);
	lene = __fls(ctrl->len);

	wp_low = val + lens;
	wp_high = val + lene;
	अगर (addr < wp_low)
		वापस wp_low - addr;
	अन्यथा अगर (addr > wp_high)
		वापस addr - wp_high;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक watchpoपूर्णांक_report(काष्ठा perf_event *wp, अचिन्हित दीर्घ addr,
			     काष्ठा pt_regs *regs)
अणु
	पूर्णांक step = is_शेष_overflow_handler(wp);
	काष्ठा arch_hw_अवरोधpoपूर्णांक *info = counter_arch_bp(wp);

	info->trigger = addr;

	/*
	 * If we triggered a user watchpoपूर्णांक from a uaccess routine, then
	 * handle the stepping ourselves since userspace really can't help
	 * us with this.
	 */
	अगर (!user_mode(regs) && info->ctrl.privilege == AARCH64_BREAKPOINT_EL0)
		step = 1;
	अन्यथा
		perf_bp_event(wp, regs);

	वापस step;
पूर्ण

अटल पूर्णांक watchpoपूर्णांक_handler(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक esr,
			      काष्ठा pt_regs *regs)
अणु
	पूर्णांक i, step = 0, *kernel_step, access, बंदst_match = 0;
	u64 min_dist = -1, dist;
	u32 ctrl_reg;
	u64 val;
	काष्ठा perf_event *wp, **slots;
	काष्ठा debug_info *debug_info;
	काष्ठा arch_hw_अवरोधpoपूर्णांक_ctrl ctrl;

	slots = this_cpu_ptr(wp_on_reg);
	debug_info = &current->thपढ़ो.debug;

	/*
	 * Find all watchpoपूर्णांकs that match the reported address. If no exact
	 * match is found. Attribute the hit to the बंदst watchpoपूर्णांक.
	 */
	rcu_पढ़ो_lock();
	क्रम (i = 0; i < core_num_wrps; ++i) अणु
		wp = slots[i];
		अगर (wp == शून्य)
			जारी;

		/*
		 * Check that the access type matches.
		 * 0 => load, otherwise => store
		 */
		access = (esr & AARCH64_ESR_ACCESS_MASK) ? HW_BREAKPOINT_W :
			 HW_BREAKPOINT_R;
		अगर (!(access & hw_अवरोधpoपूर्णांक_type(wp)))
			जारी;

		/* Check अगर the watchpoपूर्णांक value and byte select match. */
		val = पढ़ो_wb_reg(AARCH64_DBG_REG_WVR, i);
		ctrl_reg = पढ़ो_wb_reg(AARCH64_DBG_REG_WCR, i);
		decode_ctrl_reg(ctrl_reg, &ctrl);
		dist = get_distance_from_watchpoपूर्णांक(addr, val, &ctrl);
		अगर (dist < min_dist) अणु
			min_dist = dist;
			बंदst_match = i;
		पूर्ण
		/* Is this an exact match? */
		अगर (dist != 0)
			जारी;

		step = watchpoपूर्णांक_report(wp, addr, regs);
	पूर्ण

	/* No exact match found? */
	अगर (min_dist > 0 && min_dist != -1)
		step = watchpoपूर्णांक_report(slots[बंदst_match], addr, regs);

	rcu_पढ़ो_unlock();

	अगर (!step)
		वापस 0;

	/*
	 * We always disable EL0 watchpoपूर्णांकs because the kernel can
	 * cause these to fire via an unprivileged access.
	 */
	toggle_bp_रेजिस्टरs(AARCH64_DBG_REG_WCR, DBG_ACTIVE_EL0, 0);

	अगर (user_mode(regs)) अणु
		debug_info->wps_disabled = 1;

		/* If we're alपढ़ोy stepping a अवरोधpoपूर्णांक, just वापस. */
		अगर (debug_info->bps_disabled)
			वापस 0;

		अगर (test_thपढ़ो_flag(TIF_SINGLESTEP))
			debug_info->suspended_step = 1;
		अन्यथा
			user_enable_single_step(current);
	पूर्ण अन्यथा अणु
		toggle_bp_रेजिस्टरs(AARCH64_DBG_REG_WCR, DBG_ACTIVE_EL1, 0);
		kernel_step = this_cpu_ptr(&stepping_kernel_bp);

		अगर (*kernel_step != ARM_KERNEL_STEP_NONE)
			वापस 0;

		अगर (kernel_active_single_step()) अणु
			*kernel_step = ARM_KERNEL_STEP_SUSPEND;
		पूर्ण अन्यथा अणु
			*kernel_step = ARM_KERNEL_STEP_ACTIVE;
			kernel_enable_single_step(regs);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
NOKPROBE_SYMBOL(watchpoपूर्णांक_handler);

/*
 * Handle single-step exception.
 */
पूर्णांक reinstall_suspended_bps(काष्ठा pt_regs *regs)
अणु
	काष्ठा debug_info *debug_info = &current->thपढ़ो.debug;
	पूर्णांक handled_exception = 0, *kernel_step;

	kernel_step = this_cpu_ptr(&stepping_kernel_bp);

	/*
	 * Called from single-step exception handler.
	 * Return 0 अगर execution can resume, 1 अगर a SIGTRAP should be
	 * reported.
	 */
	अगर (user_mode(regs)) अणु
		अगर (debug_info->bps_disabled) अणु
			debug_info->bps_disabled = 0;
			toggle_bp_रेजिस्टरs(AARCH64_DBG_REG_BCR, DBG_ACTIVE_EL0, 1);
			handled_exception = 1;
		पूर्ण

		अगर (debug_info->wps_disabled) अणु
			debug_info->wps_disabled = 0;
			toggle_bp_रेजिस्टरs(AARCH64_DBG_REG_WCR, DBG_ACTIVE_EL0, 1);
			handled_exception = 1;
		पूर्ण

		अगर (handled_exception) अणु
			अगर (debug_info->suspended_step) अणु
				debug_info->suspended_step = 0;
				/* Allow exception handling to fall-through. */
				handled_exception = 0;
			पूर्ण अन्यथा अणु
				user_disable_single_step(current);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (*kernel_step != ARM_KERNEL_STEP_NONE) अणु
		toggle_bp_रेजिस्टरs(AARCH64_DBG_REG_BCR, DBG_ACTIVE_EL1, 1);
		toggle_bp_रेजिस्टरs(AARCH64_DBG_REG_WCR, DBG_ACTIVE_EL1, 1);

		अगर (!debug_info->wps_disabled)
			toggle_bp_रेजिस्टरs(AARCH64_DBG_REG_WCR, DBG_ACTIVE_EL0, 1);

		अगर (*kernel_step != ARM_KERNEL_STEP_SUSPEND) अणु
			kernel_disable_single_step();
			handled_exception = 1;
		पूर्ण अन्यथा अणु
			handled_exception = 0;
		पूर्ण

		*kernel_step = ARM_KERNEL_STEP_NONE;
	पूर्ण

	वापस !handled_exception;
पूर्ण
NOKPROBE_SYMBOL(reinstall_suspended_bps);

/*
 * Context-चयनer क्रम restoring suspended अवरोधpoपूर्णांकs.
 */
व्योम hw_अवरोधpoपूर्णांक_thपढ़ो_चयन(काष्ठा task_काष्ठा *next)
अणु
	/*
	 *           current        next
	 * disabled: 0              0     => The usual हाल, NOTIFY_DONE
	 *           0              1     => Disable the रेजिस्टरs
	 *           1              0     => Enable the रेजिस्टरs
	 *           1              1     => NOTIFY_DONE. per-task bps will
	 *                                   get taken care of by perf.
	 */

	काष्ठा debug_info *current_debug_info, *next_debug_info;

	current_debug_info = &current->thपढ़ो.debug;
	next_debug_info = &next->thपढ़ो.debug;

	/* Update अवरोधpoपूर्णांकs. */
	अगर (current_debug_info->bps_disabled != next_debug_info->bps_disabled)
		toggle_bp_रेजिस्टरs(AARCH64_DBG_REG_BCR,
				    DBG_ACTIVE_EL0,
				    !next_debug_info->bps_disabled);

	/* Update watchpoपूर्णांकs. */
	अगर (current_debug_info->wps_disabled != next_debug_info->wps_disabled)
		toggle_bp_रेजिस्टरs(AARCH64_DBG_REG_WCR,
				    DBG_ACTIVE_EL0,
				    !next_debug_info->wps_disabled);
पूर्ण

/*
 * CPU initialisation.
 */
अटल पूर्णांक hw_अवरोधpoपूर्णांक_reset(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक i;
	काष्ठा perf_event **slots;
	/*
	 * When a CPU goes through cold-boot, it करोes not have any installed
	 * slot, so it is safe to share the same function क्रम restoring and
	 * resetting अवरोधpoपूर्णांकs; when a CPU is hotplugged in, it goes
	 * through the slots, which are all empty, hence it just resets control
	 * and value क्रम debug रेजिस्टरs.
	 * When this function is triggered on warm-boot through a CPU PM
	 * notअगरier some slots might be initialized; अगर so they are
	 * reprogrammed according to the debug slots content.
	 */
	क्रम (slots = this_cpu_ptr(bp_on_reg), i = 0; i < core_num_brps; ++i) अणु
		अगर (slots[i]) अणु
			hw_अवरोधpoपूर्णांक_control(slots[i], HW_BREAKPOINT_RESTORE);
		पूर्ण अन्यथा अणु
			ग_लिखो_wb_reg(AARCH64_DBG_REG_BCR, i, 0UL);
			ग_लिखो_wb_reg(AARCH64_DBG_REG_BVR, i, 0UL);
		पूर्ण
	पूर्ण

	क्रम (slots = this_cpu_ptr(wp_on_reg), i = 0; i < core_num_wrps; ++i) अणु
		अगर (slots[i]) अणु
			hw_अवरोधpoपूर्णांक_control(slots[i], HW_BREAKPOINT_RESTORE);
		पूर्ण अन्यथा अणु
			ग_लिखो_wb_reg(AARCH64_DBG_REG_WCR, i, 0UL);
			ग_लिखो_wb_reg(AARCH64_DBG_REG_WVR, i, 0UL);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_CPU_PM
बाह्य व्योम cpu_suspend_set_dbg_restorer(पूर्णांक (*hw_bp_restore)(अचिन्हित पूर्णांक));
#अन्यथा
अटल अंतरभूत व्योम cpu_suspend_set_dbg_restorer(पूर्णांक (*hw_bp_restore)(अचिन्हित पूर्णांक))
अणु
पूर्ण
#पूर्ण_अगर

/*
 * One-समय initialisation.
 */
अटल पूर्णांक __init arch_hw_अवरोधpoपूर्णांक_init(व्योम)
अणु
	पूर्णांक ret;

	core_num_brps = get_num_brps();
	core_num_wrps = get_num_wrps();

	pr_info("found %d breakpoint and %d watchpoint registers.\n",
		core_num_brps, core_num_wrps);

	/* Register debug fault handlers. */
	hook_debug_fault_code(DBG_ESR_EVT_HWBP, अवरोधpoपूर्णांक_handler, SIGTRAP,
			      TRAP_HWBKPT, "hw-breakpoint handler");
	hook_debug_fault_code(DBG_ESR_EVT_HWWP, watchpoपूर्णांक_handler, SIGTRAP,
			      TRAP_HWBKPT, "hw-watchpoint handler");

	/*
	 * Reset the अवरोधpoपूर्णांक resources. We assume that a halting
	 * debugger will leave the world in a nice state क्रम us.
	 */
	ret = cpuhp_setup_state(CPUHP_AP_PERF_ARM_HW_BREAKPOINT_STARTING,
			  "perf/arm64/hw_breakpoint:starting",
			  hw_अवरोधpoपूर्णांक_reset, शून्य);
	अगर (ret)
		pr_err("failed to register CPU hotplug notifier: %d\n", ret);

	/* Register cpu_suspend hw अवरोधpoपूर्णांक restore hook */
	cpu_suspend_set_dbg_restorer(hw_अवरोधpoपूर्णांक_reset);

	वापस ret;
पूर्ण
arch_initcall(arch_hw_अवरोधpoपूर्णांक_init);

व्योम hw_अवरोधpoपूर्णांक_pmu_पढ़ो(काष्ठा perf_event *bp)
अणु
पूर्ण

/*
 * Dummy function to रेजिस्टर with die_notअगरier.
 */
पूर्णांक hw_अवरोधpoपूर्णांक_exceptions_notअगरy(काष्ठा notअगरier_block *unused,
				    अचिन्हित दीर्घ val, व्योम *data)
अणु
	वापस NOTIFY_DONE;
पूर्ण
