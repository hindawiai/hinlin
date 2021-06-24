<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2009, 2010 ARM Limited
 *
 * Author: Will Deacon <will.deacon@arm.com>
 */

/*
 * HW_अवरोधpoपूर्णांक: a unअगरied kernel/user-space hardware अवरोधpoपूर्णांक facility,
 * using the CPU's debug रेजिस्टरs.
 */
#घोषणा pr_fmt(fmt) "hw-breakpoint: " fmt

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/hardirq.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>
#समावेश <linux/smp.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/coresight.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/hw_अवरोधpoपूर्णांक.h>
#समावेश <यंत्र/traps.h>

/* Breakpoपूर्णांक currently in use क्रम each BRP. */
अटल DEFINE_PER_CPU(काष्ठा perf_event *, bp_on_reg[ARM_MAX_BRP]);

/* Watchpoपूर्णांक currently in use क्रम each WRP. */
अटल DEFINE_PER_CPU(काष्ठा perf_event *, wp_on_reg[ARM_MAX_WRP]);

/* Number of BRP/WRP रेजिस्टरs on this CPU. */
अटल पूर्णांक core_num_brps __ro_after_init;
अटल पूर्णांक core_num_wrps __ro_after_init;

/* Debug architecture version. */
अटल u8 debug_arch __ro_after_init;

/* Does debug architecture support OS Save and Restore? */
अटल bool has_ossr __ro_after_init;

/* Maximum supported watchpoपूर्णांक length. */
अटल u8 max_watchpoपूर्णांक_len __ro_after_init;

#घोषणा READ_WB_REG_CASE(OP2, M, VAL)			\
	हाल ((OP2 << 4) + M):				\
		ARM_DBG_READ(c0, c ## M, OP2, VAL);	\
		अवरोध

#घोषणा WRITE_WB_REG_CASE(OP2, M, VAL)			\
	हाल ((OP2 << 4) + M):				\
		ARM_DBG_WRITE(c0, c ## M, OP2, VAL);	\
		अवरोध

#घोषणा GEN_READ_WB_REG_CASES(OP2, VAL)		\
	READ_WB_REG_CASE(OP2, 0, VAL);		\
	READ_WB_REG_CASE(OP2, 1, VAL);		\
	READ_WB_REG_CASE(OP2, 2, VAL);		\
	READ_WB_REG_CASE(OP2, 3, VAL);		\
	READ_WB_REG_CASE(OP2, 4, VAL);		\
	READ_WB_REG_CASE(OP2, 5, VAL);		\
	READ_WB_REG_CASE(OP2, 6, VAL);		\
	READ_WB_REG_CASE(OP2, 7, VAL);		\
	READ_WB_REG_CASE(OP2, 8, VAL);		\
	READ_WB_REG_CASE(OP2, 9, VAL);		\
	READ_WB_REG_CASE(OP2, 10, VAL);		\
	READ_WB_REG_CASE(OP2, 11, VAL);		\
	READ_WB_REG_CASE(OP2, 12, VAL);		\
	READ_WB_REG_CASE(OP2, 13, VAL);		\
	READ_WB_REG_CASE(OP2, 14, VAL);		\
	READ_WB_REG_CASE(OP2, 15, VAL)

#घोषणा GEN_WRITE_WB_REG_CASES(OP2, VAL)	\
	WRITE_WB_REG_CASE(OP2, 0, VAL);		\
	WRITE_WB_REG_CASE(OP2, 1, VAL);		\
	WRITE_WB_REG_CASE(OP2, 2, VAL);		\
	WRITE_WB_REG_CASE(OP2, 3, VAL);		\
	WRITE_WB_REG_CASE(OP2, 4, VAL);		\
	WRITE_WB_REG_CASE(OP2, 5, VAL);		\
	WRITE_WB_REG_CASE(OP2, 6, VAL);		\
	WRITE_WB_REG_CASE(OP2, 7, VAL);		\
	WRITE_WB_REG_CASE(OP2, 8, VAL);		\
	WRITE_WB_REG_CASE(OP2, 9, VAL);		\
	WRITE_WB_REG_CASE(OP2, 10, VAL);	\
	WRITE_WB_REG_CASE(OP2, 11, VAL);	\
	WRITE_WB_REG_CASE(OP2, 12, VAL);	\
	WRITE_WB_REG_CASE(OP2, 13, VAL);	\
	WRITE_WB_REG_CASE(OP2, 14, VAL);	\
	WRITE_WB_REG_CASE(OP2, 15, VAL)

अटल u32 पढ़ो_wb_reg(पूर्णांक n)
अणु
	u32 val = 0;

	चयन (n) अणु
	GEN_READ_WB_REG_CASES(ARM_OP2_BVR, val);
	GEN_READ_WB_REG_CASES(ARM_OP2_BCR, val);
	GEN_READ_WB_REG_CASES(ARM_OP2_WVR, val);
	GEN_READ_WB_REG_CASES(ARM_OP2_WCR, val);
	शेष:
		pr_warn("attempt to read from unknown breakpoint register %d\n",
			n);
	पूर्ण

	वापस val;
पूर्ण

अटल व्योम ग_लिखो_wb_reg(पूर्णांक n, u32 val)
अणु
	चयन (n) अणु
	GEN_WRITE_WB_REG_CASES(ARM_OP2_BVR, val);
	GEN_WRITE_WB_REG_CASES(ARM_OP2_BCR, val);
	GEN_WRITE_WB_REG_CASES(ARM_OP2_WVR, val);
	GEN_WRITE_WB_REG_CASES(ARM_OP2_WCR, val);
	शेष:
		pr_warn("attempt to write to unknown breakpoint register %d\n",
			n);
	पूर्ण
	isb();
पूर्ण

/* Determine debug architecture. */
अटल u8 get_debug_arch(व्योम)
अणु
	u32 didr;

	/* Do we implement the extended CPUID पूर्णांकerface? */
	अगर (((पढ़ो_cpuid_id() >> 16) & 0xf) != 0xf) अणु
		pr_warn_once("CPUID feature registers not supported. "
			     "Assuming v6 debug is present.\n");
		वापस ARM_DEBUG_ARCH_V6;
	पूर्ण

	ARM_DBG_READ(c0, c0, 0, didr);
	वापस (didr >> 16) & 0xf;
पूर्ण

u8 arch_get_debug_arch(व्योम)
अणु
	वापस debug_arch;
पूर्ण

अटल पूर्णांक debug_arch_supported(व्योम)
अणु
	u8 arch = get_debug_arch();

	/* We करोn't support the memory-mapped पूर्णांकerface. */
	वापस (arch >= ARM_DEBUG_ARCH_V6 && arch <= ARM_DEBUG_ARCH_V7_ECP14) ||
		arch >= ARM_DEBUG_ARCH_V7_1;
पूर्ण

/* Can we determine the watchpoपूर्णांक access type from the fsr? */
अटल पूर्णांक debug_exception_updates_fsr(व्योम)
अणु
	वापस get_debug_arch() >= ARM_DEBUG_ARCH_V8;
पूर्ण

/* Determine number of WRP रेजिस्टरs available. */
अटल पूर्णांक get_num_wrp_resources(व्योम)
अणु
	u32 didr;
	ARM_DBG_READ(c0, c0, 0, didr);
	वापस ((didr >> 28) & 0xf) + 1;
पूर्ण

/* Determine number of BRP रेजिस्टरs available. */
अटल पूर्णांक get_num_brp_resources(व्योम)
अणु
	u32 didr;
	ARM_DBG_READ(c0, c0, 0, didr);
	वापस ((didr >> 24) & 0xf) + 1;
पूर्ण

/* Does this core support mismatch अवरोधpoपूर्णांकs? */
अटल पूर्णांक core_has_mismatch_brps(व्योम)
अणु
	वापस (get_debug_arch() >= ARM_DEBUG_ARCH_V7_ECP14 &&
		get_num_brp_resources() > 1);
पूर्ण

/* Determine number of usable WRPs available. */
अटल पूर्णांक get_num_wrps(व्योम)
अणु
	/*
	 * On debug architectures prior to 7.1, when a watchpoपूर्णांक fires, the
	 * only way to work out which watchpoपूर्णांक it was is by disassembling
	 * the faulting inकाष्ठाion and working out the address of the memory
	 * access.
	 *
	 * Furthermore, we can only करो this अगर the watchpoपूर्णांक was precise
	 * since imprecise watchpoपूर्णांकs prevent us from calculating रेजिस्टर
	 * based addresses.
	 *
	 * Providing we have more than 1 अवरोधpoपूर्णांक रेजिस्टर, we only report
	 * a single watchpoपूर्णांक रेजिस्टर क्रम the समय being. This way, we always
	 * know which watchpoपूर्णांक fired. In the future we can either add a
	 * disassembler and address generation emulator, or we can insert a
	 * check to see अगर the DFAR is set on watchpoपूर्णांक exception entry
	 * [the ARM ARM states that the DFAR is UNKNOWN, but experience shows
	 * that it is set on some implementations].
	 */
	अगर (get_debug_arch() < ARM_DEBUG_ARCH_V7_1)
		वापस 1;

	वापस get_num_wrp_resources();
पूर्ण

/* Determine number of usable BRPs available. */
अटल पूर्णांक get_num_brps(व्योम)
अणु
	पूर्णांक brps = get_num_brp_resources();
	वापस core_has_mismatch_brps() ? brps - 1 : brps;
पूर्ण

/*
 * In order to access the अवरोधpoपूर्णांक/watchpoपूर्णांक control रेजिस्टरs,
 * we must be running in debug monitor mode. Unक्रमtunately, we can
 * be put पूर्णांकo halting debug mode at any समय by an बाह्यal debugger
 * but there is nothing we can करो to prevent that.
 */
अटल पूर्णांक monitor_mode_enabled(व्योम)
अणु
	u32 dscr;
	ARM_DBG_READ(c0, c1, 0, dscr);
	वापस !!(dscr & ARM_DSCR_MDBGEN);
पूर्ण

अटल पूर्णांक enable_monitor_mode(व्योम)
अणु
	u32 dscr;
	ARM_DBG_READ(c0, c1, 0, dscr);

	/* If monitor mode is alपढ़ोy enabled, just वापस. */
	अगर (dscr & ARM_DSCR_MDBGEN)
		जाओ out;

	/* Write to the corresponding DSCR. */
	चयन (get_debug_arch()) अणु
	हाल ARM_DEBUG_ARCH_V6:
	हाल ARM_DEBUG_ARCH_V6_1:
		ARM_DBG_WRITE(c0, c1, 0, (dscr | ARM_DSCR_MDBGEN));
		अवरोध;
	हाल ARM_DEBUG_ARCH_V7_ECP14:
	हाल ARM_DEBUG_ARCH_V7_1:
	हाल ARM_DEBUG_ARCH_V8:
	हाल ARM_DEBUG_ARCH_V8_1:
	हाल ARM_DEBUG_ARCH_V8_2:
	हाल ARM_DEBUG_ARCH_V8_4:
		ARM_DBG_WRITE(c0, c2, 2, (dscr | ARM_DSCR_MDBGEN));
		isb();
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	/* Check that the ग_लिखो made it through. */
	ARM_DBG_READ(c0, c1, 0, dscr);
	अगर (!(dscr & ARM_DSCR_MDBGEN)) अणु
		pr_warn_once("Failed to enable monitor mode on CPU %d.\n",
				smp_processor_id());
		वापस -EPERM;
	पूर्ण

out:
	वापस 0;
पूर्ण

पूर्णांक hw_अवरोधpoपूर्णांक_slots(पूर्णांक type)
अणु
	अगर (!debug_arch_supported())
		वापस 0;

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

/*
 * Check अगर 8-bit byte-address select is available.
 * This clobbers WRP 0.
 */
अटल u8 get_max_wp_len(व्योम)
अणु
	u32 ctrl_reg;
	काष्ठा arch_hw_अवरोधpoपूर्णांक_ctrl ctrl;
	u8 size = 4;

	अगर (debug_arch < ARM_DEBUG_ARCH_V7_ECP14)
		जाओ out;

	स_रखो(&ctrl, 0, माप(ctrl));
	ctrl.len = ARM_BREAKPOINT_LEN_8;
	ctrl_reg = encode_ctrl_reg(ctrl);

	ग_लिखो_wb_reg(ARM_BASE_WVR, 0);
	ग_लिखो_wb_reg(ARM_BASE_WCR, ctrl_reg);
	अगर ((पढ़ो_wb_reg(ARM_BASE_WCR) & ctrl_reg) == ctrl_reg)
		size = 8;

out:
	वापस size;
पूर्ण

u8 arch_get_max_wp_len(व्योम)
अणु
	वापस max_watchpoपूर्णांक_len;
पूर्ण

/*
 * Install a perf counter अवरोधpoपूर्णांक.
 */
पूर्णांक arch_install_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp)
अणु
	काष्ठा arch_hw_अवरोधpoपूर्णांक *info = counter_arch_bp(bp);
	काष्ठा perf_event **slot, **slots;
	पूर्णांक i, max_slots, ctrl_base, val_base;
	u32 addr, ctrl;

	addr = info->address;
	ctrl = encode_ctrl_reg(info->ctrl) | 0x1;

	अगर (info->ctrl.type == ARM_BREAKPOINT_EXECUTE) अणु
		/* Breakpoपूर्णांक */
		ctrl_base = ARM_BASE_BCR;
		val_base = ARM_BASE_BVR;
		slots = this_cpu_ptr(bp_on_reg);
		max_slots = core_num_brps;
	पूर्ण अन्यथा अणु
		/* Watchpoपूर्णांक */
		ctrl_base = ARM_BASE_WCR;
		val_base = ARM_BASE_WVR;
		slots = this_cpu_ptr(wp_on_reg);
		max_slots = core_num_wrps;
	पूर्ण

	क्रम (i = 0; i < max_slots; ++i) अणु
		slot = &slots[i];

		अगर (!*slot) अणु
			*slot = bp;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == max_slots) अणु
		pr_warn("Can't find any breakpoint slot\n");
		वापस -EBUSY;
	पूर्ण

	/* Override the अवरोधpoपूर्णांक data with the step data. */
	अगर (info->step_ctrl.enabled) अणु
		addr = info->trigger & ~0x3;
		ctrl = encode_ctrl_reg(info->step_ctrl);
		अगर (info->ctrl.type != ARM_BREAKPOINT_EXECUTE) अणु
			i = 0;
			ctrl_base = ARM_BASE_BCR + core_num_brps;
			val_base = ARM_BASE_BVR + core_num_brps;
		पूर्ण
	पूर्ण

	/* Setup the address रेजिस्टर. */
	ग_लिखो_wb_reg(val_base + i, addr);

	/* Setup the control रेजिस्टर. */
	ग_लिखो_wb_reg(ctrl_base + i, ctrl);
	वापस 0;
पूर्ण

व्योम arch_uninstall_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp)
अणु
	काष्ठा arch_hw_अवरोधpoपूर्णांक *info = counter_arch_bp(bp);
	काष्ठा perf_event **slot, **slots;
	पूर्णांक i, max_slots, base;

	अगर (info->ctrl.type == ARM_BREAKPOINT_EXECUTE) अणु
		/* Breakpoपूर्णांक */
		base = ARM_BASE_BCR;
		slots = this_cpu_ptr(bp_on_reg);
		max_slots = core_num_brps;
	पूर्ण अन्यथा अणु
		/* Watchpoपूर्णांक */
		base = ARM_BASE_WCR;
		slots = this_cpu_ptr(wp_on_reg);
		max_slots = core_num_wrps;
	पूर्ण

	/* Remove the अवरोधpoपूर्णांक. */
	क्रम (i = 0; i < max_slots; ++i) अणु
		slot = &slots[i];

		अगर (*slot == bp) अणु
			*slot = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == max_slots) अणु
		pr_warn("Can't find any breakpoint slot\n");
		वापस;
	पूर्ण

	/* Ensure that we disable the mismatch अवरोधpoपूर्णांक. */
	अगर (info->ctrl.type != ARM_BREAKPOINT_EXECUTE &&
	    info->step_ctrl.enabled) अणु
		i = 0;
		base = ARM_BASE_BCR + core_num_brps;
	पूर्ण

	/* Reset the control रेजिस्टर. */
	ग_लिखो_wb_reg(base + i, 0);
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
	हाल ARM_BREAKPOINT_LEN_4:
		len_in_bytes = 4;
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
			   पूर्णांक *gen_len, पूर्णांक *gen_type)
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

	/* Len */
	चयन (ctrl.len) अणु
	हाल ARM_BREAKPOINT_LEN_1:
		*gen_len = HW_BREAKPOINT_LEN_1;
		अवरोध;
	हाल ARM_BREAKPOINT_LEN_2:
		*gen_len = HW_BREAKPOINT_LEN_2;
		अवरोध;
	हाल ARM_BREAKPOINT_LEN_4:
		*gen_len = HW_BREAKPOINT_LEN_4;
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
	हाल HW_BREAKPOINT_LEN_4:
		hw->ctrl.len = ARM_BREAKPOINT_LEN_4;
		अवरोध;
	हाल HW_BREAKPOINT_LEN_8:
		hw->ctrl.len = ARM_BREAKPOINT_LEN_8;
		अगर ((hw->ctrl.type != ARM_BREAKPOINT_EXECUTE)
			&& max_watchpoपूर्णांक_len >= 8)
			अवरोध;
		fallthrough;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * Breakpoपूर्णांकs must be of length 2 (thumb) or 4 (ARM) bytes.
	 * Watchpoपूर्णांकs can be of length 1, 2, 4 or 8 bytes अगर supported
	 * by the hardware and must be aligned to the appropriate number of
	 * bytes.
	 */
	अगर (hw->ctrl.type == ARM_BREAKPOINT_EXECUTE &&
	    hw->ctrl.len != ARM_BREAKPOINT_LEN_2 &&
	    hw->ctrl.len != ARM_BREAKPOINT_LEN_4)
		वापस -EINVAL;

	/* Address */
	hw->address = attr->bp_addr;

	/* Privilege */
	hw->ctrl.privilege = ARM_BREAKPOINT_USER;
	अगर (arch_check_bp_in_kernelspace(hw))
		hw->ctrl.privilege |= ARM_BREAKPOINT_PRIV;

	/* Enabled? */
	hw->ctrl.enabled = !attr->disabled;

	/* Mismatch */
	hw->ctrl.mismatch = 0;

	वापस 0;
पूर्ण

/*
 * Validate the arch-specअगरic HW Breakpoपूर्णांक रेजिस्टर settings.
 */
पूर्णांक hw_अवरोधpoपूर्णांक_arch_parse(काष्ठा perf_event *bp,
			     स्थिर काष्ठा perf_event_attr *attr,
			     काष्ठा arch_hw_अवरोधpoपूर्णांक *hw)
अणु
	पूर्णांक ret = 0;
	u32 offset, alignment_mask = 0x3;

	/* Ensure that we are in monitor debug mode. */
	अगर (!monitor_mode_enabled())
		वापस -ENODEV;

	/* Build the arch_hw_अवरोधpoपूर्णांक. */
	ret = arch_build_bp_info(bp, attr, hw);
	अगर (ret)
		जाओ out;

	/* Check address alignment. */
	अगर (hw->ctrl.len == ARM_BREAKPOINT_LEN_8)
		alignment_mask = 0x7;
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
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	hw->address &= ~alignment_mask;
	hw->ctrl.len <<= offset;

	अगर (is_शेष_overflow_handler(bp)) अणु
		/*
		 * Mismatch अवरोधpoपूर्णांकs are required क्रम single-stepping
		 * अवरोधpoपूर्णांकs.
		 */
		अगर (!core_has_mismatch_brps())
			वापस -EINVAL;

		/* We करोn't allow mismatch अवरोधpoपूर्णांकs in kernel space. */
		अगर (arch_check_bp_in_kernelspace(hw))
			वापस -EPERM;

		/*
		 * Per-cpu अवरोधpoपूर्णांकs are not supported by our stepping
		 * mechanism.
		 */
		अगर (!bp->hw.target)
			वापस -EINVAL;

		/*
		 * We only support specअगरic access types अगर the fsr
		 * reports them.
		 */
		अगर (!debug_exception_updates_fsr() &&
		    (hw->ctrl.type == ARM_BREAKPOINT_LOAD ||
		     hw->ctrl.type == ARM_BREAKPOINT_STORE))
			वापस -EINVAL;
	पूर्ण

out:
	वापस ret;
पूर्ण

/*
 * Enable/disable single-stepping over the अवरोधpoपूर्णांक bp at address addr.
 */
अटल व्योम enable_single_step(काष्ठा perf_event *bp, u32 addr)
अणु
	काष्ठा arch_hw_अवरोधpoपूर्णांक *info = counter_arch_bp(bp);

	arch_uninstall_hw_अवरोधpoपूर्णांक(bp);
	info->step_ctrl.mismatch  = 1;
	info->step_ctrl.len	  = ARM_BREAKPOINT_LEN_4;
	info->step_ctrl.type	  = ARM_BREAKPOINT_EXECUTE;
	info->step_ctrl.privilege = info->ctrl.privilege;
	info->step_ctrl.enabled	  = 1;
	info->trigger		  = addr;
	arch_install_hw_अवरोधpoपूर्णांक(bp);
पूर्ण

अटल व्योम disable_single_step(काष्ठा perf_event *bp)
अणु
	arch_uninstall_hw_अवरोधpoपूर्णांक(bp);
	counter_arch_bp(bp)->step_ctrl.enabled = 0;
	arch_install_hw_अवरोधpoपूर्णांक(bp);
पूर्ण

/*
 * Arm32 hardware करोes not always report a watchpoपूर्णांक hit address that matches
 * one of the watchpoपूर्णांकs set. It can also report an address "near" the
 * watchpoपूर्णांक अगर a single inकाष्ठाion access both watched and unwatched
 * addresses. There is no straight-क्रमward way, लघु of disassembling the
 * offending inकाष्ठाion, to map that address back to the watchpoपूर्णांक. This
 * function computes the distance of the memory access from the watchpoपूर्णांक as a
 * heuristic क्रम the likelyhood that a given access triggered the watchpoपूर्णांक.
 *
 * See this same function in the arm64 platक्रमm code, which has the same
 * problem.
 *
 * The function वापसs the distance of the address from the bytes watched by
 * the watchpoपूर्णांक. In हाल of an exact match, it वापसs 0.
 */
अटल u32 get_distance_from_watchpoपूर्णांक(अचिन्हित दीर्घ addr, u32 val,
					काष्ठा arch_hw_अवरोधpoपूर्णांक_ctrl *ctrl)
अणु
	u32 wp_low, wp_high;
	u32 lens, lene;

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

अटल पूर्णांक watchpoपूर्णांक_fault_on_uaccess(काष्ठा pt_regs *regs,
				       काष्ठा arch_hw_अवरोधpoपूर्णांक *info)
अणु
	वापस !user_mode(regs) && info->ctrl.privilege == ARM_BREAKPOINT_USER;
पूर्ण

अटल व्योम watchpoपूर्णांक_handler(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक fsr,
			       काष्ठा pt_regs *regs)
अणु
	पूर्णांक i, access, बंदst_match = 0;
	u32 min_dist = -1, dist;
	u32 val, ctrl_reg;
	काष्ठा perf_event *wp, **slots;
	काष्ठा arch_hw_अवरोधpoपूर्णांक *info;
	काष्ठा arch_hw_अवरोधpoपूर्णांक_ctrl ctrl;

	slots = this_cpu_ptr(wp_on_reg);

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
		 * The DFAR is an unknown value on debug architectures prior
		 * to 7.1. Since we only allow a single watchpoपूर्णांक on these
		 * older CPUs, we can set the trigger to the lowest possible
		 * faulting address.
		 */
		अगर (debug_arch < ARM_DEBUG_ARCH_V7_1) अणु
			BUG_ON(i > 0);
			info = counter_arch_bp(wp);
			info->trigger = wp->attr.bp_addr;
		पूर्ण अन्यथा अणु
			/* Check that the access type matches. */
			अगर (debug_exception_updates_fsr()) अणु
				access = (fsr & ARM_FSR_ACCESS_MASK) ?
					  HW_BREAKPOINT_W : HW_BREAKPOINT_R;
				अगर (!(access & hw_अवरोधpoपूर्णांक_type(wp)))
					जारी;
			पूर्ण

			val = पढ़ो_wb_reg(ARM_BASE_WVR + i);
			ctrl_reg = पढ़ो_wb_reg(ARM_BASE_WCR + i);
			decode_ctrl_reg(ctrl_reg, &ctrl);
			dist = get_distance_from_watchpoपूर्णांक(addr, val, &ctrl);
			अगर (dist < min_dist) अणु
				min_dist = dist;
				बंदst_match = i;
			पूर्ण
			/* Is this an exact match? */
			अगर (dist != 0)
				जारी;

			/* We have a winner. */
			info = counter_arch_bp(wp);
			info->trigger = addr;
		पूर्ण

		pr_debug("watchpoint fired: address = 0x%x\n", info->trigger);

		/*
		 * If we triggered a user watchpoपूर्णांक from a uaccess routine,
		 * then handle the stepping ourselves since userspace really
		 * can't help us with this.
		 */
		अगर (watchpoपूर्णांक_fault_on_uaccess(regs, info))
			जाओ step;

		perf_bp_event(wp, regs);

		/*
		 * Defer stepping to the overflow handler अगर one is installed.
		 * Otherwise, insert a temporary mismatch अवरोधpoपूर्णांक so that
		 * we can single-step over the watchpoपूर्णांक trigger.
		 */
		अगर (!is_शेष_overflow_handler(wp))
			जारी;
step:
		enable_single_step(wp, inकाष्ठाion_poपूर्णांकer(regs));
	पूर्ण

	अगर (min_dist > 0 && min_dist != -1) अणु
		/* No exact match found. */
		wp = slots[बंदst_match];
		info = counter_arch_bp(wp);
		info->trigger = addr;
		pr_debug("watchpoint fired: address = 0x%x\n", info->trigger);
		perf_bp_event(wp, regs);
		अगर (is_शेष_overflow_handler(wp))
			enable_single_step(wp, inकाष्ठाion_poपूर्णांकer(regs));
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम watchpoपूर्णांक_single_step_handler(अचिन्हित दीर्घ pc)
अणु
	पूर्णांक i;
	काष्ठा perf_event *wp, **slots;
	काष्ठा arch_hw_अवरोधpoपूर्णांक *info;

	slots = this_cpu_ptr(wp_on_reg);

	क्रम (i = 0; i < core_num_wrps; ++i) अणु
		rcu_पढ़ो_lock();

		wp = slots[i];

		अगर (wp == शून्य)
			जाओ unlock;

		info = counter_arch_bp(wp);
		अगर (!info->step_ctrl.enabled)
			जाओ unlock;

		/*
		 * Restore the original watchpoपूर्णांक अगर we've completed the
		 * single-step.
		 */
		अगर (info->trigger != pc)
			disable_single_step(wp);

unlock:
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण

अटल व्योम अवरोधpoपूर्णांक_handler(अचिन्हित दीर्घ unknown, काष्ठा pt_regs *regs)
अणु
	पूर्णांक i;
	u32 ctrl_reg, val, addr;
	काष्ठा perf_event *bp, **slots;
	काष्ठा arch_hw_अवरोधpoपूर्णांक *info;
	काष्ठा arch_hw_अवरोधpoपूर्णांक_ctrl ctrl;

	slots = this_cpu_ptr(bp_on_reg);

	/* The exception entry code places the amended lr in the PC. */
	addr = regs->ARM_pc;

	/* Check the currently installed अवरोधpoपूर्णांकs first. */
	क्रम (i = 0; i < core_num_brps; ++i) अणु
		rcu_पढ़ो_lock();

		bp = slots[i];

		अगर (bp == शून्य)
			जाओ unlock;

		info = counter_arch_bp(bp);

		/* Check अगर the अवरोधpoपूर्णांक value matches. */
		val = पढ़ो_wb_reg(ARM_BASE_BVR + i);
		अगर (val != (addr & ~0x3))
			जाओ mismatch;

		/* Possible match, check the byte address select to confirm. */
		ctrl_reg = पढ़ो_wb_reg(ARM_BASE_BCR + i);
		decode_ctrl_reg(ctrl_reg, &ctrl);
		अगर ((1 << (addr & 0x3)) & ctrl.len) अणु
			info->trigger = addr;
			pr_debug("breakpoint fired: address = 0x%x\n", addr);
			perf_bp_event(bp, regs);
			अगर (is_शेष_overflow_handler(bp))
				enable_single_step(bp, addr);
			जाओ unlock;
		पूर्ण

mismatch:
		/* If we're stepping a अवरोधpoपूर्णांक, it can now be restored. */
		अगर (info->step_ctrl.enabled)
			disable_single_step(bp);
unlock:
		rcu_पढ़ो_unlock();
	पूर्ण

	/* Handle any pending watchpoपूर्णांक single-step अवरोधpoपूर्णांकs. */
	watchpoपूर्णांक_single_step_handler(addr);
पूर्ण

/*
 * Called from either the Data Abort Handler [watchpoपूर्णांक] or the
 * Prefetch Abort Handler [अवरोधpoपूर्णांक] with पूर्णांकerrupts disabled.
 */
अटल पूर्णांक hw_अवरोधpoपूर्णांक_pending(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक fsr,
				 काष्ठा pt_regs *regs)
अणु
	पूर्णांक ret = 0;
	u32 dscr;

	preempt_disable();

	अगर (पूर्णांकerrupts_enabled(regs))
		local_irq_enable();

	/* We only handle watchpoपूर्णांकs and hardware अवरोधpoपूर्णांकs. */
	ARM_DBG_READ(c0, c1, 0, dscr);

	/* Perक्रमm perf callbacks. */
	चयन (ARM_DSCR_MOE(dscr)) अणु
	हाल ARM_ENTRY_BREAKPOINT:
		अवरोधpoपूर्णांक_handler(addr, regs);
		अवरोध;
	हाल ARM_ENTRY_ASYNC_WATCHPOINT:
		WARN(1, "Asynchronous watchpoint exception taken. Debugging results may be unreliable\n");
		fallthrough;
	हाल ARM_ENTRY_SYNC_WATCHPOINT:
		watchpoपूर्णांक_handler(addr, fsr, regs);
		अवरोध;
	शेष:
		ret = 1; /* Unhandled fault. */
	पूर्ण

	preempt_enable();

	वापस ret;
पूर्ण

/*
 * One-समय initialisation.
 */
अटल cpumask_t debug_err_mask;

अटल पूर्णांक debug_reg_trap(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक instr)
अणु
	पूर्णांक cpu = smp_processor_id();

	pr_warn("Debug register access (0x%x) caused undefined instruction on CPU %d\n",
		instr, cpu);

	/* Set the error flag क्रम this CPU and skip the faulting inकाष्ठाion. */
	cpumask_set_cpu(cpu, &debug_err_mask);
	inकाष्ठाion_poपूर्णांकer(regs) += 4;
	वापस 0;
पूर्ण

अटल काष्ठा undef_hook debug_reg_hook = अणु
	.instr_mask	= 0x0fe80f10,
	.instr_val	= 0x0e000e10,
	.fn		= debug_reg_trap,
पूर्ण;

/* Does this core support OS Save and Restore? */
अटल bool core_has_os_save_restore(व्योम)
अणु
	u32 oslsr;

	चयन (get_debug_arch()) अणु
	हाल ARM_DEBUG_ARCH_V7_1:
		वापस true;
	हाल ARM_DEBUG_ARCH_V7_ECP14:
		ARM_DBG_READ(c1, c1, 4, oslsr);
		अगर (oslsr & ARM_OSLSR_OSLM0)
			वापस true;
		fallthrough;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम reset_ctrl_regs(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक i, raw_num_brps, err = 0;
	u32 val;

	/*
	 * v7 debug contains save and restore रेजिस्टरs so that debug state
	 * can be मुख्यtained across low-घातer modes without leaving the debug
	 * logic घातered up. It is IMPLEMENTATION DEFINED whether we can access
	 * the debug रेजिस्टरs out of reset, so we must unlock the OS Lock
	 * Access Register to aव्योम taking undefined inकाष्ठाion exceptions
	 * later on.
	 */
	चयन (debug_arch) अणु
	हाल ARM_DEBUG_ARCH_V6:
	हाल ARM_DEBUG_ARCH_V6_1:
		/* ARMv6 cores clear the रेजिस्टरs out of reset. */
		जाओ out_mdbgen;
	हाल ARM_DEBUG_ARCH_V7_ECP14:
		/*
		 * Ensure sticky घातer-करोwn is clear (i.e. debug logic is
		 * घातered up).
		 */
		ARM_DBG_READ(c1, c5, 4, val);
		अगर ((val & 0x1) == 0)
			err = -EPERM;

		अगर (!has_ossr)
			जाओ clear_vcr;
		अवरोध;
	हाल ARM_DEBUG_ARCH_V7_1:
		/*
		 * Ensure the OS द्विगुन lock is clear.
		 */
		ARM_DBG_READ(c1, c3, 4, val);
		अगर ((val & 0x1) == 1)
			err = -EPERM;
		अवरोध;
	पूर्ण

	अगर (err) अणु
		pr_warn_once("CPU %d debug is powered down!\n", cpu);
		cpumask_or(&debug_err_mask, &debug_err_mask, cpumask_of(cpu));
		वापस;
	पूर्ण

	/*
	 * Unconditionally clear the OS lock by writing a value
	 * other than CS_LAR_KEY to the access रेजिस्टर.
	 */
	ARM_DBG_WRITE(c1, c0, 4, ~CORESIGHT_UNLOCK);
	isb();

	/*
	 * Clear any configured vector-catch events beक्रमe
	 * enabling monitor mode.
	 */
clear_vcr:
	ARM_DBG_WRITE(c0, c7, 0, 0);
	isb();

	अगर (cpumask_पूर्णांकersects(&debug_err_mask, cpumask_of(cpu))) अणु
		pr_warn_once("CPU %d failed to disable vector catch\n", cpu);
		वापस;
	पूर्ण

	/*
	 * The control/value रेजिस्टर pairs are UNKNOWN out of reset so
	 * clear them to aव्योम spurious debug events.
	 */
	raw_num_brps = get_num_brp_resources();
	क्रम (i = 0; i < raw_num_brps; ++i) अणु
		ग_लिखो_wb_reg(ARM_BASE_BCR + i, 0UL);
		ग_लिखो_wb_reg(ARM_BASE_BVR + i, 0UL);
	पूर्ण

	क्रम (i = 0; i < core_num_wrps; ++i) अणु
		ग_लिखो_wb_reg(ARM_BASE_WCR + i, 0UL);
		ग_लिखो_wb_reg(ARM_BASE_WVR + i, 0UL);
	पूर्ण

	अगर (cpumask_पूर्णांकersects(&debug_err_mask, cpumask_of(cpu))) अणु
		pr_warn_once("CPU %d failed to clear debug register pairs\n", cpu);
		वापस;
	पूर्ण

	/*
	 * Have a crack at enabling monitor mode. We करोn't actually need
	 * it yet, but reporting an error early is useful अगर it fails.
	 */
out_mdbgen:
	अगर (enable_monitor_mode())
		cpumask_or(&debug_err_mask, &debug_err_mask, cpumask_of(cpu));
पूर्ण

अटल पूर्णांक dbg_reset_online(अचिन्हित पूर्णांक cpu)
अणु
	local_irq_disable();
	reset_ctrl_regs(cpu);
	local_irq_enable();
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_CPU_PM
अटल पूर्णांक dbg_cpu_pm_notअगरy(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ action,
			     व्योम *v)
अणु
	अगर (action == CPU_PM_EXIT)
		reset_ctrl_regs(smp_processor_id());

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block dbg_cpu_pm_nb = अणु
	.notअगरier_call = dbg_cpu_pm_notअगरy,
पूर्ण;

अटल व्योम __init pm_init(व्योम)
अणु
	cpu_pm_रेजिस्टर_notअगरier(&dbg_cpu_pm_nb);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम pm_init(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init arch_hw_अवरोधpoपूर्णांक_init(व्योम)
अणु
	पूर्णांक ret;

	debug_arch = get_debug_arch();

	अगर (!debug_arch_supported()) अणु
		pr_info("debug architecture 0x%x unsupported.\n", debug_arch);
		वापस 0;
	पूर्ण

	/*
	 * Scorpion CPUs (at least those in APQ8060) seem to set DBGPRSR.SPD
	 * whenever a WFI is issued, even अगर the core is not घातered करोwn, in
	 * violation of the architecture.  When DBGPRSR.SPD is set, accesses to
	 * अवरोधpoपूर्णांक and watchpoपूर्णांक रेजिस्टरs are treated as undefined, so
	 * this results in boot समय and runसमय failures when these are
	 * accessed and we unexpectedly take a trap.
	 *
	 * It's not clear अगर/how this can be worked around, so we blacklist
	 * Scorpion CPUs to aव्योम these issues.
	*/
	अगर (पढ़ो_cpuid_part() == ARM_CPU_PART_SCORPION) अणु
		pr_info("Scorpion CPU detected. Hardware breakpoints and watchpoints disabled\n");
		वापस 0;
	पूर्ण

	has_ossr = core_has_os_save_restore();

	/* Determine how many BRPs/WRPs are available. */
	core_num_brps = get_num_brps();
	core_num_wrps = get_num_wrps();

	/*
	 * We need to tपढ़ो carefully here because DBGSWENABLE may be
	 * driven low on this core and there isn't an architected way to
	 * determine that.
	 */
	cpus_पढ़ो_lock();
	रेजिस्टर_undef_hook(&debug_reg_hook);

	/*
	 * Register CPU notअगरier which resets the अवरोधpoपूर्णांक resources. We
	 * assume that a halting debugger will leave the world in a nice state
	 * क्रम us.
	 */
	ret = cpuhp_setup_state_cpuslocked(CPUHP_AP_ONLINE_DYN,
					   "arm/hw_breakpoint:online",
					   dbg_reset_online, शून्य);
	unरेजिस्टर_undef_hook(&debug_reg_hook);
	अगर (WARN_ON(ret < 0) || !cpumask_empty(&debug_err_mask)) अणु
		core_num_brps = 0;
		core_num_wrps = 0;
		अगर (ret > 0)
			cpuhp_हटाओ_state_nocalls_cpuslocked(ret);
		cpus_पढ़ो_unlock();
		वापस 0;
	पूर्ण

	pr_info("found %d " "%s" "breakpoint and %d watchpoint registers.\n",
		core_num_brps, core_has_mismatch_brps() ? "(+1 reserved) " :
		"", core_num_wrps);

	/* Work out the maximum supported watchpoपूर्णांक length. */
	max_watchpoपूर्णांक_len = get_max_wp_len();
	pr_info("maximum watchpoint size is %u bytes.\n",
			max_watchpoपूर्णांक_len);

	/* Register debug fault handler. */
	hook_fault_code(FAULT_CODE_DEBUG, hw_अवरोधpoपूर्णांक_pending, SIGTRAP,
			TRAP_HWBKPT, "watchpoint debug exception");
	hook_अगरault_code(FAULT_CODE_DEBUG, hw_अवरोधpoपूर्णांक_pending, SIGTRAP,
			TRAP_HWBKPT, "breakpoint debug exception");
	cpus_पढ़ो_unlock();

	/* Register PM notअगरiers. */
	pm_init();
	वापस 0;
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
