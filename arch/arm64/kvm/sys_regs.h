<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012,2013 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 *
 * Derived from arch/arm/kvm/coproc.h
 * Copyright (C) 2012 - Virtual Open Systems and Columbia University
 * Authors: Christoffer Dall <c.dall@भवखोलोप्रणालीs.com>
 */

#अगर_अघोषित __ARM64_KVM_SYS_REGS_LOCAL_H__
#घोषणा __ARM64_KVM_SYS_REGS_LOCAL_H__

काष्ठा sys_reg_params अणु
	u8	Op0;
	u8	Op1;
	u8	CRn;
	u8	CRm;
	u8	Op2;
	u64	regval;
	bool	is_ग_लिखो;
पूर्ण;

काष्ठा sys_reg_desc अणु
	/* Sysreg string क्रम debug */
	स्थिर अक्षर *name;

	क्रमागत अणु
		AA32_ZEROHIGH,
		AA32_LO,
		AA32_HI,
	पूर्ण aarch32_map;

	/* MRS/MSR inकाष्ठाion which accesses it. */
	u8	Op0;
	u8	Op1;
	u8	CRn;
	u8	CRm;
	u8	Op2;

	/* Trapped access from guest, अगर non-शून्य. */
	bool (*access)(काष्ठा kvm_vcpu *,
		       काष्ठा sys_reg_params *,
		       स्थिर काष्ठा sys_reg_desc *);

	/* Initialization क्रम vcpu. */
	व्योम (*reset)(काष्ठा kvm_vcpu *, स्थिर काष्ठा sys_reg_desc *);

	/* Index पूर्णांकo sys_reg[], or 0 अगर we करोn't need to save it. */
	पूर्णांक reg;

	/* Value (usually reset value) */
	u64 val;

	/* Custom get/set_user functions, fallback to generic अगर शून्य */
	पूर्णांक (*get_user)(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा sys_reg_desc *rd,
			स्थिर काष्ठा kvm_one_reg *reg, व्योम __user *uaddr);
	पूर्णांक (*set_user)(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा sys_reg_desc *rd,
			स्थिर काष्ठा kvm_one_reg *reg, व्योम __user *uaddr);

	/* Return mask of REG_* runसमय visibility overrides */
	अचिन्हित पूर्णांक (*visibility)(स्थिर काष्ठा kvm_vcpu *vcpu,
				   स्थिर काष्ठा sys_reg_desc *rd);
पूर्ण;

#घोषणा REG_HIDDEN		(1 << 0) /* hidden from userspace and guest */
#घोषणा REG_RAZ			(1 << 1) /* RAZ from userspace and guest */

अटल __म_लिखो(2, 3)
अंतरभूत व्योम prपूर्णांक_sys_reg_msg(स्थिर काष्ठा sys_reg_params *p,
				       अक्षर *fmt, ...)
अणु
	बहु_सूची va;

	बहु_शुरू(va, fmt);
	/* Look, we even क्रमmatted it क्रम you to paste पूर्णांकo the table! */
	kvm_pr_unimpl("%pV { Op0(%2u), Op1(%2u), CRn(%2u), CRm(%2u), Op2(%2u), func_%s },\n",
		      &(काष्ठा va_क्रमmat)अणु fmt, &va पूर्ण,
		      p->Op0, p->Op1, p->CRn, p->CRm, p->Op2, p->is_ग_लिखो ? "write" : "read");
	बहु_पूर्ण(va);
पूर्ण

अटल अंतरभूत व्योम prपूर्णांक_sys_reg_instr(स्थिर काष्ठा sys_reg_params *p)
अणु
	/* GCC warns on an empty क्रमmat string */
	prपूर्णांक_sys_reg_msg(p, "%s", "");
पूर्ण

अटल अंतरभूत bool ignore_ग_लिखो(काष्ठा kvm_vcpu *vcpu,
				स्थिर काष्ठा sys_reg_params *p)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत bool पढ़ो_zero(काष्ठा kvm_vcpu *vcpu,
			     काष्ठा sys_reg_params *p)
अणु
	p->regval = 0;
	वापस true;
पूर्ण

/* Reset functions */
अटल अंतरभूत व्योम reset_unknown(काष्ठा kvm_vcpu *vcpu,
				 स्थिर काष्ठा sys_reg_desc *r)
अणु
	BUG_ON(!r->reg);
	BUG_ON(r->reg >= NR_SYS_REGS);
	__vcpu_sys_reg(vcpu, r->reg) = 0x1de7ec7edbadc0deULL;
पूर्ण

अटल अंतरभूत व्योम reset_val(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा sys_reg_desc *r)
अणु
	BUG_ON(!r->reg);
	BUG_ON(r->reg >= NR_SYS_REGS);
	__vcpu_sys_reg(vcpu, r->reg) = r->val;
पूर्ण

अटल अंतरभूत bool sysreg_hidden(स्थिर काष्ठा kvm_vcpu *vcpu,
				 स्थिर काष्ठा sys_reg_desc *r)
अणु
	अगर (likely(!r->visibility))
		वापस false;

	वापस r->visibility(vcpu, r) & REG_HIDDEN;
पूर्ण

अटल अंतरभूत bool sysreg_visible_as_raz(स्थिर काष्ठा kvm_vcpu *vcpu,
					 स्थिर काष्ठा sys_reg_desc *r)
अणु
	अगर (likely(!r->visibility))
		वापस false;

	वापस r->visibility(vcpu, r) & REG_RAZ;
पूर्ण

अटल अंतरभूत पूर्णांक cmp_sys_reg(स्थिर काष्ठा sys_reg_desc *i1,
			      स्थिर काष्ठा sys_reg_desc *i2)
अणु
	BUG_ON(i1 == i2);
	अगर (!i1)
		वापस 1;
	अन्यथा अगर (!i2)
		वापस -1;
	अगर (i1->Op0 != i2->Op0)
		वापस i1->Op0 - i2->Op0;
	अगर (i1->Op1 != i2->Op1)
		वापस i1->Op1 - i2->Op1;
	अगर (i1->CRn != i2->CRn)
		वापस i1->CRn - i2->CRn;
	अगर (i1->CRm != i2->CRm)
		वापस i1->CRm - i2->CRm;
	वापस i1->Op2 - i2->Op2;
पूर्ण

स्थिर काष्ठा sys_reg_desc *find_reg_by_id(u64 id,
					  काष्ठा sys_reg_params *params,
					  स्थिर काष्ठा sys_reg_desc table[],
					  अचिन्हित पूर्णांक num);

#घोषणा AA32(_x)	.aarch32_map = AA32_##_x
#घोषणा Op0(_x) 	.Op0 = _x
#घोषणा Op1(_x) 	.Op1 = _x
#घोषणा CRn(_x)		.CRn = _x
#घोषणा CRm(_x) 	.CRm = _x
#घोषणा Op2(_x) 	.Op2 = _x

#घोषणा SYS_DESC(reg)					\
	.name = #reg,					\
	Op0(sys_reg_Op0(reg)), Op1(sys_reg_Op1(reg)),	\
	CRn(sys_reg_CRn(reg)), CRm(sys_reg_CRm(reg)),	\
	Op2(sys_reg_Op2(reg))

#पूर्ण_अगर /* __ARM64_KVM_SYS_REGS_LOCAL_H__ */
