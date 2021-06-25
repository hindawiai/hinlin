<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_HW_BREAKPOINT_H
#घोषणा __ASM_HW_BREAKPOINT_H

#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/sysreg.h>
#समावेश <यंत्र/virt.h>

काष्ठा arch_hw_अवरोधpoपूर्णांक_ctrl अणु
	u32 __reserved	: 19,
	len		: 8,
	type		: 2,
	privilege	: 2,
	enabled		: 1;
पूर्ण;

काष्ठा arch_hw_अवरोधpoपूर्णांक अणु
	u64 address;
	u64 trigger;
	काष्ठा arch_hw_अवरोधpoपूर्णांक_ctrl ctrl;
पूर्ण;

/* Privilege Levels */
#घोषणा AARCH64_BREAKPOINT_EL1	1
#घोषणा AARCH64_BREAKPOINT_EL0	2

#घोषणा DBG_HMC_HYP		(1 << 13)

अटल अंतरभूत u32 encode_ctrl_reg(काष्ठा arch_hw_अवरोधpoपूर्णांक_ctrl ctrl)
अणु
	u32 val = (ctrl.len << 5) | (ctrl.type << 3) | (ctrl.privilege << 1) |
		ctrl.enabled;

	अगर (is_kernel_in_hyp_mode() && ctrl.privilege == AARCH64_BREAKPOINT_EL1)
		val |= DBG_HMC_HYP;

	वापस val;
पूर्ण

अटल अंतरभूत व्योम decode_ctrl_reg(u32 reg,
				   काष्ठा arch_hw_अवरोधpoपूर्णांक_ctrl *ctrl)
अणु
	ctrl->enabled	= reg & 0x1;
	reg >>= 1;
	ctrl->privilege	= reg & 0x3;
	reg >>= 2;
	ctrl->type	= reg & 0x3;
	reg >>= 2;
	ctrl->len	= reg & 0xff;
पूर्ण

/* Breakpoपूर्णांक */
#घोषणा ARM_BREAKPOINT_EXECUTE	0

/* Watchpoपूर्णांकs */
#घोषणा ARM_BREAKPOINT_LOAD	1
#घोषणा ARM_BREAKPOINT_STORE	2
#घोषणा AARCH64_ESR_ACCESS_MASK	(1 << 6)

/* Lengths */
#घोषणा ARM_BREAKPOINT_LEN_1	0x1
#घोषणा ARM_BREAKPOINT_LEN_2	0x3
#घोषणा ARM_BREAKPOINT_LEN_3	0x7
#घोषणा ARM_BREAKPOINT_LEN_4	0xf
#घोषणा ARM_BREAKPOINT_LEN_5	0x1f
#घोषणा ARM_BREAKPOINT_LEN_6	0x3f
#घोषणा ARM_BREAKPOINT_LEN_7	0x7f
#घोषणा ARM_BREAKPOINT_LEN_8	0xff

/* Kernel stepping */
#घोषणा ARM_KERNEL_STEP_NONE	0
#घोषणा ARM_KERNEL_STEP_ACTIVE	1
#घोषणा ARM_KERNEL_STEP_SUSPEND	2

/*
 * Limits.
 * Changing these will require modअगरications to the रेजिस्टर accessors.
 */
#घोषणा ARM_MAX_BRP		16
#घोषणा ARM_MAX_WRP		16

/* Virtual debug रेजिस्टर bases. */
#घोषणा AARCH64_DBG_REG_BVR	0
#घोषणा AARCH64_DBG_REG_BCR	(AARCH64_DBG_REG_BVR + ARM_MAX_BRP)
#घोषणा AARCH64_DBG_REG_WVR	(AARCH64_DBG_REG_BCR + ARM_MAX_BRP)
#घोषणा AARCH64_DBG_REG_WCR	(AARCH64_DBG_REG_WVR + ARM_MAX_WRP)

/* Debug रेजिस्टर names. */
#घोषणा AARCH64_DBG_REG_NAME_BVR	bvr
#घोषणा AARCH64_DBG_REG_NAME_BCR	bcr
#घोषणा AARCH64_DBG_REG_NAME_WVR	wvr
#घोषणा AARCH64_DBG_REG_NAME_WCR	wcr

/* Accessor macros क्रम the debug रेजिस्टरs. */
#घोषणा AARCH64_DBG_READ(N, REG, VAL) करो अणु\
	VAL = पढ़ो_sysreg(dbg##REG##N##_el1);\
पूर्ण जबतक (0)

#घोषणा AARCH64_DBG_WRITE(N, REG, VAL) करो अणु\
	ग_लिखो_sysreg(VAL, dbg##REG##N##_el1);\
पूर्ण जबतक (0)

काष्ठा task_काष्ठा;
काष्ठा notअगरier_block;
काष्ठा perf_event_attr;
काष्ठा perf_event;
काष्ठा pmu;

बाह्य पूर्णांक arch_bp_generic_fields(काष्ठा arch_hw_अवरोधpoपूर्णांक_ctrl ctrl,
				  पूर्णांक *gen_len, पूर्णांक *gen_type, पूर्णांक *offset);
बाह्य पूर्णांक arch_check_bp_in_kernelspace(काष्ठा arch_hw_अवरोधpoपूर्णांक *hw);
बाह्य पूर्णांक hw_अवरोधpoपूर्णांक_arch_parse(काष्ठा perf_event *bp,
				    स्थिर काष्ठा perf_event_attr *attr,
				    काष्ठा arch_hw_अवरोधpoपूर्णांक *hw);
बाह्य पूर्णांक hw_अवरोधpoपूर्णांक_exceptions_notअगरy(काष्ठा notअगरier_block *unused,
					   अचिन्हित दीर्घ val, व्योम *data);

बाह्य पूर्णांक arch_install_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp);
बाह्य व्योम arch_uninstall_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp);
बाह्य व्योम hw_अवरोधpoपूर्णांक_pmu_पढ़ो(काष्ठा perf_event *bp);
बाह्य पूर्णांक hw_अवरोधpoपूर्णांक_slots(पूर्णांक type);

#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
बाह्य व्योम hw_अवरोधpoपूर्णांक_thपढ़ो_चयन(काष्ठा task_काष्ठा *next);
बाह्य व्योम ptrace_hw_copy_thपढ़ो(काष्ठा task_काष्ठा *task);
#अन्यथा
अटल अंतरभूत व्योम hw_अवरोधpoपूर्णांक_thपढ़ो_चयन(काष्ठा task_काष्ठा *next)
अणु
पूर्ण
अटल अंतरभूत व्योम ptrace_hw_copy_thपढ़ो(काष्ठा task_काष्ठा *task)
अणु
पूर्ण
#पूर्ण_अगर

/* Determine number of BRP रेजिस्टरs available. */
अटल अंतरभूत पूर्णांक get_num_brps(व्योम)
अणु
	u64 dfr0 = पढ़ो_sanitised_ftr_reg(SYS_ID_AA64DFR0_EL1);
	वापस 1 +
		cpuid_feature_extract_अचिन्हित_field(dfr0,
						ID_AA64DFR0_BRPS_SHIFT);
पूर्ण

/* Determine number of WRP रेजिस्टरs available. */
अटल अंतरभूत पूर्णांक get_num_wrps(व्योम)
अणु
	u64 dfr0 = पढ़ो_sanitised_ftr_reg(SYS_ID_AA64DFR0_EL1);
	वापस 1 +
		cpuid_feature_extract_अचिन्हित_field(dfr0,
						ID_AA64DFR0_WRPS_SHIFT);
पूर्ण

#पूर्ण_अगर	/* __ASM_BREAKPOINT_H */
