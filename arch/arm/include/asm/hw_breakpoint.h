<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ARM_HW_BREAKPOINT_H
#घोषणा _ARM_HW_BREAKPOINT_H

#अगर_घोषित __KERNEL__

काष्ठा task_काष्ठा;

#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT

काष्ठा arch_hw_अवरोधpoपूर्णांक_ctrl अणु
		u32 __reserved	: 9,
		mismatch	: 1,
				: 9,
		len		: 8,
		type		: 2,
		privilege	: 2,
		enabled		: 1;
पूर्ण;

काष्ठा arch_hw_अवरोधpoपूर्णांक अणु
	u32	address;
	u32	trigger;
	काष्ठा	arch_hw_अवरोधpoपूर्णांक_ctrl step_ctrl;
	काष्ठा	arch_hw_अवरोधpoपूर्णांक_ctrl ctrl;
पूर्ण;

अटल अंतरभूत u32 encode_ctrl_reg(काष्ठा arch_hw_अवरोधpoपूर्णांक_ctrl ctrl)
अणु
	वापस (ctrl.mismatch << 22) | (ctrl.len << 5) | (ctrl.type << 3) |
		(ctrl.privilege << 1) | ctrl.enabled;
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
	reg >>= 17;
	ctrl->mismatch	= reg & 0x1;
पूर्ण

/* Debug architecture numbers. */
#घोषणा ARM_DEBUG_ARCH_RESERVED	0	/* In हाल of ptrace ABI updates. */
#घोषणा ARM_DEBUG_ARCH_V6	1
#घोषणा ARM_DEBUG_ARCH_V6_1	2
#घोषणा ARM_DEBUG_ARCH_V7_ECP14	3
#घोषणा ARM_DEBUG_ARCH_V7_MM	4
#घोषणा ARM_DEBUG_ARCH_V7_1	5
#घोषणा ARM_DEBUG_ARCH_V8	6
#घोषणा ARM_DEBUG_ARCH_V8_1	7
#घोषणा ARM_DEBUG_ARCH_V8_2	8
#घोषणा ARM_DEBUG_ARCH_V8_4	9

/* Breakpoपूर्णांक */
#घोषणा ARM_BREAKPOINT_EXECUTE	0

/* Watchpoपूर्णांकs */
#घोषणा ARM_BREAKPOINT_LOAD	1
#घोषणा ARM_BREAKPOINT_STORE	2
#घोषणा ARM_FSR_ACCESS_MASK	(1 << 11)

/* Privilege Levels */
#घोषणा ARM_BREAKPOINT_PRIV	1
#घोषणा ARM_BREAKPOINT_USER	2

/* Lengths */
#घोषणा ARM_BREAKPOINT_LEN_1	0x1
#घोषणा ARM_BREAKPOINT_LEN_2	0x3
#घोषणा ARM_BREAKPOINT_LEN_4	0xf
#घोषणा ARM_BREAKPOINT_LEN_8	0xff

/* Limits */
#घोषणा ARM_MAX_BRP		16
#घोषणा ARM_MAX_WRP		16
#घोषणा ARM_MAX_HBP_SLOTS	(ARM_MAX_BRP + ARM_MAX_WRP)

/* DSCR method of entry bits. */
#घोषणा ARM_DSCR_MOE(x)			((x >> 2) & 0xf)
#घोषणा ARM_ENTRY_BREAKPOINT		0x1
#घोषणा ARM_ENTRY_ASYNC_WATCHPOINT	0x2
#घोषणा ARM_ENTRY_SYNC_WATCHPOINT	0xa

/* DSCR monitor/halting bits. */
#घोषणा ARM_DSCR_HDBGEN		(1 << 14)
#घोषणा ARM_DSCR_MDBGEN		(1 << 15)

/* OSLSR os lock model bits */
#घोषणा ARM_OSLSR_OSLM0		(1 << 0)

/* opcode2 numbers क्रम the co-processor inकाष्ठाions. */
#घोषणा ARM_OP2_BVR		4
#घोषणा ARM_OP2_BCR		5
#घोषणा ARM_OP2_WVR		6
#घोषणा ARM_OP2_WCR		7

/* Base रेजिस्टर numbers क्रम the debug रेजिस्टरs. */
#घोषणा ARM_BASE_BVR		64
#घोषणा ARM_BASE_BCR		80
#घोषणा ARM_BASE_WVR		96
#घोषणा ARM_BASE_WCR		112

/* Accessor macros क्रम the debug रेजिस्टरs. */
#घोषणा ARM_DBG_READ(N, M, OP2, VAL) करो अणु\
	यंत्र अस्थिर("mrc p14, 0, %0, " #N "," #M ", " #OP2 : "=r" (VAL));\
पूर्ण जबतक (0)

#घोषणा ARM_DBG_WRITE(N, M, OP2, VAL) करो अणु\
	यंत्र अस्थिर("mcr p14, 0, %0, " #N "," #M ", " #OP2 : : "r" (VAL));\
पूर्ण जबतक (0)

काष्ठा perf_event_attr;
काष्ठा notअगरier_block;
काष्ठा perf_event;
काष्ठा pmu;

बाह्य पूर्णांक arch_bp_generic_fields(काष्ठा arch_hw_अवरोधpoपूर्णांक_ctrl ctrl,
				  पूर्णांक *gen_len, पूर्णांक *gen_type);
बाह्य पूर्णांक arch_check_bp_in_kernelspace(काष्ठा arch_hw_अवरोधpoपूर्णांक *hw);
बाह्य पूर्णांक hw_अवरोधpoपूर्णांक_arch_parse(काष्ठा perf_event *bp,
				    स्थिर काष्ठा perf_event_attr *attr,
				    काष्ठा arch_hw_अवरोधpoपूर्णांक *hw);
बाह्य पूर्णांक hw_अवरोधpoपूर्णांक_exceptions_notअगरy(काष्ठा notअगरier_block *unused,
					   अचिन्हित दीर्घ val, व्योम *data);

बाह्य u8 arch_get_debug_arch(व्योम);
बाह्य u8 arch_get_max_wp_len(व्योम);
बाह्य व्योम clear_ptrace_hw_अवरोधpoपूर्णांक(काष्ठा task_काष्ठा *tsk);

पूर्णांक arch_install_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp);
व्योम arch_uninstall_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp);
व्योम hw_अवरोधpoपूर्णांक_pmu_पढ़ो(काष्ठा perf_event *bp);
पूर्णांक hw_अवरोधpoपूर्णांक_slots(पूर्णांक type);

#अन्यथा
अटल अंतरभूत व्योम clear_ptrace_hw_अवरोधpoपूर्णांक(काष्ठा task_काष्ठा *tsk) अणुपूर्ण

#पूर्ण_अगर	/* CONFIG_HAVE_HW_BREAKPOINT */
#पूर्ण_अगर	/* __KERNEL__ */
#पूर्ण_अगर	/* _ARM_HW_BREAKPOINT_H */
