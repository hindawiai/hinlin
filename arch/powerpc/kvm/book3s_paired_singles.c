<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright Novell Inc 2010
 *
 * Authors: Alexander Graf <agraf@suse.de>
 */

#समावेश <यंत्र/kvm.h>
#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/disassemble.h>
#समावेश <यंत्र/kvm_book3s.h>
#समावेश <यंत्र/kvm_fpu.h>
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <linux/vदो_स्मृति.h>

/* #घोषणा DEBUG */

#अगर_घोषित DEBUG
#घोषणा dprपूर्णांकk prपूर्णांकk
#अन्यथा
#घोषणा dprपूर्णांकk(...) करो अणु पूर्ण जबतक(0);
#पूर्ण_अगर

#घोषणा OP_LFS			48
#घोषणा OP_LFSU			49
#घोषणा OP_LFD			50
#घोषणा OP_LFDU			51
#घोषणा OP_STFS			52
#घोषणा OP_STFSU		53
#घोषणा OP_STFD			54
#घोषणा OP_STFDU		55
#घोषणा OP_PSQ_L		56
#घोषणा OP_PSQ_LU		57
#घोषणा OP_PSQ_ST		60
#घोषणा OP_PSQ_STU		61

#घोषणा OP_31_LFSX		535
#घोषणा OP_31_LFSUX		567
#घोषणा OP_31_LFDX		599
#घोषणा OP_31_LFDUX		631
#घोषणा OP_31_STFSX		663
#घोषणा OP_31_STFSUX		695
#घोषणा OP_31_STFX		727
#घोषणा OP_31_STFUX		759
#घोषणा OP_31_LWIZX		887
#घोषणा OP_31_STFIWX		983

#घोषणा OP_59_FADDS		21
#घोषणा OP_59_FSUBS		20
#घोषणा OP_59_FSQRTS		22
#घोषणा OP_59_FDIVS		18
#घोषणा OP_59_FRES		24
#घोषणा OP_59_FMULS		25
#घोषणा OP_59_FRSQRTES		26
#घोषणा OP_59_FMSUBS		28
#घोषणा OP_59_FMADDS		29
#घोषणा OP_59_FNMSUBS		30
#घोषणा OP_59_FNMADDS		31

#घोषणा OP_63_FCMPU		0
#घोषणा OP_63_FCPSGN		8
#घोषणा OP_63_FRSP		12
#घोषणा OP_63_FCTIW		14
#घोषणा OP_63_FCTIWZ		15
#घोषणा OP_63_FDIV		18
#घोषणा OP_63_FADD		21
#घोषणा OP_63_FSQRT		22
#घोषणा OP_63_FSEL		23
#घोषणा OP_63_FRE		24
#घोषणा OP_63_FMUL		25
#घोषणा OP_63_FRSQRTE		26
#घोषणा OP_63_FMSUB		28
#घोषणा OP_63_FMADD		29
#घोषणा OP_63_FNMSUB		30
#घोषणा OP_63_FNMADD		31
#घोषणा OP_63_FCMPO		32
#घोषणा OP_63_MTFSB1		38 // XXX
#घोषणा OP_63_FSUB		20
#घोषणा OP_63_FNEG		40
#घोषणा OP_63_MCRFS		64
#घोषणा OP_63_MTFSB0		70
#घोषणा OP_63_FMR		72
#घोषणा OP_63_MTFSFI		134
#घोषणा OP_63_FABS		264
#घोषणा OP_63_MFFS		583
#घोषणा OP_63_MTFSF		711

#घोषणा OP_4X_PS_CMPU0		0
#घोषणा OP_4X_PSQ_LX		6
#घोषणा OP_4XW_PSQ_STX		7
#घोषणा OP_4A_PS_SUM0		10
#घोषणा OP_4A_PS_SUM1		11
#घोषणा OP_4A_PS_MULS0		12
#घोषणा OP_4A_PS_MULS1		13
#घोषणा OP_4A_PS_MADDS0		14
#घोषणा OP_4A_PS_MADDS1		15
#घोषणा OP_4A_PS_DIV		18
#घोषणा OP_4A_PS_SUB		20
#घोषणा OP_4A_PS_ADD		21
#घोषणा OP_4A_PS_SEL		23
#घोषणा OP_4A_PS_RES		24
#घोषणा OP_4A_PS_MUL		25
#घोषणा OP_4A_PS_RSQRTE		26
#घोषणा OP_4A_PS_MSUB		28
#घोषणा OP_4A_PS_MADD		29
#घोषणा OP_4A_PS_NMSUB		30
#घोषणा OP_4A_PS_NMADD		31
#घोषणा OP_4X_PS_CMPO0		32
#घोषणा OP_4X_PSQ_LUX		38
#घोषणा OP_4XW_PSQ_STUX		39
#घोषणा OP_4X_PS_NEG		40
#घोषणा OP_4X_PS_CMPU1		64
#घोषणा OP_4X_PS_MR		72
#घोषणा OP_4X_PS_CMPO1		96
#घोषणा OP_4X_PS_NABS		136
#घोषणा OP_4X_PS_ABS		264
#घोषणा OP_4X_PS_MERGE00	528
#घोषणा OP_4X_PS_MERGE01	560
#घोषणा OP_4X_PS_MERGE10	592
#घोषणा OP_4X_PS_MERGE11	624

#घोषणा SCALAR_NONE		0
#घोषणा SCALAR_HIGH		(1 << 0)
#घोषणा SCALAR_LOW		(1 << 1)
#घोषणा SCALAR_NO_PS0		(1 << 2)
#घोषणा SCALAR_NO_PS1		(1 << 3)

#घोषणा GQR_ST_TYPE_MASK	0x00000007
#घोषणा GQR_ST_TYPE_SHIFT	0
#घोषणा GQR_ST_SCALE_MASK	0x00003f00
#घोषणा GQR_ST_SCALE_SHIFT	8
#घोषणा GQR_LD_TYPE_MASK	0x00070000
#घोषणा GQR_LD_TYPE_SHIFT	16
#घोषणा GQR_LD_SCALE_MASK	0x3f000000
#घोषणा GQR_LD_SCALE_SHIFT	24

#घोषणा GQR_QUANTIZE_FLOAT	0
#घोषणा GQR_QUANTIZE_U8		4
#घोषणा GQR_QUANTIZE_U16	5
#घोषणा GQR_QUANTIZE_S8		6
#घोषणा GQR_QUANTIZE_S16	7

#घोषणा FPU_LS_SINGLE		0
#घोषणा FPU_LS_DOUBLE		1
#घोषणा FPU_LS_SINGLE_LOW	2

अटल अंतरभूत व्योम kvmppc_sync_qpr(काष्ठा kvm_vcpu *vcpu, पूर्णांक rt)
अणु
	kvm_cvt_df(&VCPU_FPR(vcpu, rt), &vcpu->arch.qpr[rt]);
पूर्ण

अटल व्योम kvmppc_inject_pf(काष्ठा kvm_vcpu *vcpu, uदीर्घ eaddr, bool is_store)
अणु
	u32 dsisr;
	u64 msr = kvmppc_get_msr(vcpu);

	msr = kvmppc_set_field(msr, 33, 36, 0);
	msr = kvmppc_set_field(msr, 42, 47, 0);
	kvmppc_set_msr(vcpu, msr);
	kvmppc_set_dar(vcpu, eaddr);
	/* Page Fault */
	dsisr = kvmppc_set_field(0, 33, 33, 1);
	अगर (is_store)
		dsisr = kvmppc_set_field(dsisr, 38, 38, 1);
	kvmppc_set_dsisr(vcpu, dsisr);
	kvmppc_book3s_queue_irqprio(vcpu, BOOK3S_INTERRUPT_DATA_STORAGE);
पूर्ण

अटल पूर्णांक kvmppc_emulate_fpr_load(काष्ठा kvm_vcpu *vcpu,
				   पूर्णांक rs, uदीर्घ addr, पूर्णांक ls_type)
अणु
	पूर्णांक emulated = EMULATE_FAIL;
	पूर्णांक r;
	अक्षर पंचांगp[8];
	पूर्णांक len = माप(u32);

	अगर (ls_type == FPU_LS_DOUBLE)
		len = माप(u64);

	/* पढ़ो from memory */
	r = kvmppc_ld(vcpu, &addr, len, पंचांगp, true);
	vcpu->arch.paddr_accessed = addr;

	अगर (r < 0) अणु
		kvmppc_inject_pf(vcpu, addr, false);
		जाओ करोne_load;
	पूर्ण अन्यथा अगर (r == EMULATE_DO_MMIO) अणु
		emulated = kvmppc_handle_load(vcpu, KVM_MMIO_REG_FPR | rs,
					      len, 1);
		जाओ करोne_load;
	पूर्ण

	emulated = EMULATE_DONE;

	/* put in रेजिस्टरs */
	चयन (ls_type) अणु
	हाल FPU_LS_SINGLE:
		kvm_cvt_fd((u32*)पंचांगp, &VCPU_FPR(vcpu, rs));
		vcpu->arch.qpr[rs] = *((u32*)पंचांगp);
		अवरोध;
	हाल FPU_LS_DOUBLE:
		VCPU_FPR(vcpu, rs) = *((u64*)पंचांगp);
		अवरोध;
	पूर्ण

	dprपूर्णांकk(KERN_INFO "KVM: FPR_LD [0x%llx] at 0x%lx (%d)\n", *(u64*)पंचांगp,
			  addr, len);

करोne_load:
	वापस emulated;
पूर्ण

अटल पूर्णांक kvmppc_emulate_fpr_store(काष्ठा kvm_vcpu *vcpu,
				    पूर्णांक rs, uदीर्घ addr, पूर्णांक ls_type)
अणु
	पूर्णांक emulated = EMULATE_FAIL;
	पूर्णांक r;
	अक्षर पंचांगp[8];
	u64 val;
	पूर्णांक len;

	चयन (ls_type) अणु
	हाल FPU_LS_SINGLE:
		kvm_cvt_df(&VCPU_FPR(vcpu, rs), (u32*)पंचांगp);
		val = *((u32*)पंचांगp);
		len = माप(u32);
		अवरोध;
	हाल FPU_LS_SINGLE_LOW:
		*((u32*)पंचांगp) = VCPU_FPR(vcpu, rs);
		val = VCPU_FPR(vcpu, rs) & 0xffffffff;
		len = माप(u32);
		अवरोध;
	हाल FPU_LS_DOUBLE:
		*((u64*)पंचांगp) = VCPU_FPR(vcpu, rs);
		val = VCPU_FPR(vcpu, rs);
		len = माप(u64);
		अवरोध;
	शेष:
		val = 0;
		len = 0;
	पूर्ण

	r = kvmppc_st(vcpu, &addr, len, पंचांगp, true);
	vcpu->arch.paddr_accessed = addr;
	अगर (r < 0) अणु
		kvmppc_inject_pf(vcpu, addr, true);
	पूर्ण अन्यथा अगर (r == EMULATE_DO_MMIO) अणु
		emulated = kvmppc_handle_store(vcpu, val, len, 1);
	पूर्ण अन्यथा अणु
		emulated = EMULATE_DONE;
	पूर्ण

	dprपूर्णांकk(KERN_INFO "KVM: FPR_ST [0x%llx] at 0x%lx (%d)\n",
			  val, addr, len);

	वापस emulated;
पूर्ण

अटल पूर्णांक kvmppc_emulate_psq_load(काष्ठा kvm_vcpu *vcpu,
				   पूर्णांक rs, uदीर्घ addr, bool w, पूर्णांक i)
अणु
	पूर्णांक emulated = EMULATE_FAIL;
	पूर्णांक r;
	भग्न one = 1.0;
	u32 पंचांगp[2];

	/* पढ़ो from memory */
	अगर (w) अणु
		r = kvmppc_ld(vcpu, &addr, माप(u32), पंचांगp, true);
		स_नकल(&पंचांगp[1], &one, माप(u32));
	पूर्ण अन्यथा अणु
		r = kvmppc_ld(vcpu, &addr, माप(u32) * 2, पंचांगp, true);
	पूर्ण
	vcpu->arch.paddr_accessed = addr;
	अगर (r < 0) अणु
		kvmppc_inject_pf(vcpu, addr, false);
		जाओ करोne_load;
	पूर्ण अन्यथा अगर ((r == EMULATE_DO_MMIO) && w) अणु
		emulated = kvmppc_handle_load(vcpu, KVM_MMIO_REG_FPR | rs,
					      4, 1);
		vcpu->arch.qpr[rs] = पंचांगp[1];
		जाओ करोne_load;
	पूर्ण अन्यथा अगर (r == EMULATE_DO_MMIO) अणु
		emulated = kvmppc_handle_load(vcpu, KVM_MMIO_REG_FQPR | rs,
					      8, 1);
		जाओ करोne_load;
	पूर्ण

	emulated = EMULATE_DONE;

	/* put in रेजिस्टरs */
	kvm_cvt_fd(&पंचांगp[0], &VCPU_FPR(vcpu, rs));
	vcpu->arch.qpr[rs] = पंचांगp[1];

	dprपूर्णांकk(KERN_INFO "KVM: PSQ_LD [0x%x, 0x%x] at 0x%lx (%d)\n", पंचांगp[0],
			  पंचांगp[1], addr, w ? 4 : 8);

करोne_load:
	वापस emulated;
पूर्ण

अटल पूर्णांक kvmppc_emulate_psq_store(काष्ठा kvm_vcpu *vcpu,
				    पूर्णांक rs, uदीर्घ addr, bool w, पूर्णांक i)
अणु
	पूर्णांक emulated = EMULATE_FAIL;
	पूर्णांक r;
	u32 पंचांगp[2];
	पूर्णांक len = w ? माप(u32) : माप(u64);

	kvm_cvt_df(&VCPU_FPR(vcpu, rs), &पंचांगp[0]);
	पंचांगp[1] = vcpu->arch.qpr[rs];

	r = kvmppc_st(vcpu, &addr, len, पंचांगp, true);
	vcpu->arch.paddr_accessed = addr;
	अगर (r < 0) अणु
		kvmppc_inject_pf(vcpu, addr, true);
	पूर्ण अन्यथा अगर ((r == EMULATE_DO_MMIO) && w) अणु
		emulated = kvmppc_handle_store(vcpu, पंचांगp[0], 4, 1);
	पूर्ण अन्यथा अगर (r == EMULATE_DO_MMIO) अणु
		u64 val = ((u64)पंचांगp[0] << 32) | पंचांगp[1];
		emulated = kvmppc_handle_store(vcpu, val, 8, 1);
	पूर्ण अन्यथा अणु
		emulated = EMULATE_DONE;
	पूर्ण

	dprपूर्णांकk(KERN_INFO "KVM: PSQ_ST [0x%x, 0x%x] at 0x%lx (%d)\n",
			  पंचांगp[0], पंचांगp[1], addr, len);

	वापस emulated;
पूर्ण

/*
 * Cuts out inst bits with ordering according to spec.
 * That means the lefपंचांगost bit is zero. All given bits are included.
 */
अटल अंतरभूत u32 inst_get_field(u32 inst, पूर्णांक msb, पूर्णांक lsb)
अणु
	वापस kvmppc_get_field(inst, msb + 32, lsb + 32);
पूर्ण

अटल bool kvmppc_inst_is_paired_single(काष्ठा kvm_vcpu *vcpu, u32 inst)
अणु
	अगर (!(vcpu->arch.hflags & BOOK3S_HFLAG_PAIRED_SINGLE))
		वापस false;

	चयन (get_op(inst)) अणु
	हाल OP_PSQ_L:
	हाल OP_PSQ_LU:
	हाल OP_PSQ_ST:
	हाल OP_PSQ_STU:
	हाल OP_LFS:
	हाल OP_LFSU:
	हाल OP_LFD:
	हाल OP_LFDU:
	हाल OP_STFS:
	हाल OP_STFSU:
	हाल OP_STFD:
	हाल OP_STFDU:
		वापस true;
	हाल 4:
		/* X क्रमm */
		चयन (inst_get_field(inst, 21, 30)) अणु
		हाल OP_4X_PS_CMPU0:
		हाल OP_4X_PSQ_LX:
		हाल OP_4X_PS_CMPO0:
		हाल OP_4X_PSQ_LUX:
		हाल OP_4X_PS_NEG:
		हाल OP_4X_PS_CMPU1:
		हाल OP_4X_PS_MR:
		हाल OP_4X_PS_CMPO1:
		हाल OP_4X_PS_NABS:
		हाल OP_4X_PS_ABS:
		हाल OP_4X_PS_MERGE00:
		हाल OP_4X_PS_MERGE01:
		हाल OP_4X_PS_MERGE10:
		हाल OP_4X_PS_MERGE11:
			वापस true;
		पूर्ण
		/* XW क्रमm */
		चयन (inst_get_field(inst, 25, 30)) अणु
		हाल OP_4XW_PSQ_STX:
		हाल OP_4XW_PSQ_STUX:
			वापस true;
		पूर्ण
		/* A क्रमm */
		चयन (inst_get_field(inst, 26, 30)) अणु
		हाल OP_4A_PS_SUM1:
		हाल OP_4A_PS_SUM0:
		हाल OP_4A_PS_MULS0:
		हाल OP_4A_PS_MULS1:
		हाल OP_4A_PS_MADDS0:
		हाल OP_4A_PS_MADDS1:
		हाल OP_4A_PS_DIV:
		हाल OP_4A_PS_SUB:
		हाल OP_4A_PS_ADD:
		हाल OP_4A_PS_SEL:
		हाल OP_4A_PS_RES:
		हाल OP_4A_PS_MUL:
		हाल OP_4A_PS_RSQRTE:
		हाल OP_4A_PS_MSUB:
		हाल OP_4A_PS_MADD:
		हाल OP_4A_PS_NMSUB:
		हाल OP_4A_PS_NMADD:
			वापस true;
		पूर्ण
		अवरोध;
	हाल 59:
		चयन (inst_get_field(inst, 21, 30)) अणु
		हाल OP_59_FADDS:
		हाल OP_59_FSUBS:
		हाल OP_59_FDIVS:
		हाल OP_59_FRES:
		हाल OP_59_FRSQRTES:
			वापस true;
		पूर्ण
		चयन (inst_get_field(inst, 26, 30)) अणु
		हाल OP_59_FMULS:
		हाल OP_59_FMSUBS:
		हाल OP_59_FMADDS:
		हाल OP_59_FNMSUBS:
		हाल OP_59_FNMADDS:
			वापस true;
		पूर्ण
		अवरोध;
	हाल 63:
		चयन (inst_get_field(inst, 21, 30)) अणु
		हाल OP_63_MTFSB0:
		हाल OP_63_MTFSB1:
		हाल OP_63_MTFSF:
		हाल OP_63_MTFSFI:
		हाल OP_63_MCRFS:
		हाल OP_63_MFFS:
		हाल OP_63_FCMPU:
		हाल OP_63_FCMPO:
		हाल OP_63_FNEG:
		हाल OP_63_FMR:
		हाल OP_63_FABS:
		हाल OP_63_FRSP:
		हाल OP_63_FDIV:
		हाल OP_63_FADD:
		हाल OP_63_FSUB:
		हाल OP_63_FCTIW:
		हाल OP_63_FCTIWZ:
		हाल OP_63_FRSQRTE:
		हाल OP_63_FCPSGN:
			वापस true;
		पूर्ण
		चयन (inst_get_field(inst, 26, 30)) अणु
		हाल OP_63_FMUL:
		हाल OP_63_FSEL:
		हाल OP_63_FMSUB:
		हाल OP_63_FMADD:
		हाल OP_63_FNMSUB:
		हाल OP_63_FNMADD:
			वापस true;
		पूर्ण
		अवरोध;
	हाल 31:
		चयन (inst_get_field(inst, 21, 30)) अणु
		हाल OP_31_LFSX:
		हाल OP_31_LFSUX:
		हाल OP_31_LFDX:
		हाल OP_31_LFDUX:
		हाल OP_31_STFSX:
		हाल OP_31_STFSUX:
		हाल OP_31_STFX:
		हाल OP_31_STFUX:
		हाल OP_31_STFIWX:
			वापस true;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक get_d_signext(u32 inst)
अणु
	पूर्णांक d = inst & 0x8ff;

	अगर (d & 0x800)
		वापस -(d & 0x7ff);

	वापस (d & 0x7ff);
पूर्ण

अटल पूर्णांक kvmppc_ps_three_in(काष्ठा kvm_vcpu *vcpu, bool rc,
				      पूर्णांक reg_out, पूर्णांक reg_in1, पूर्णांक reg_in2,
				      पूर्णांक reg_in3, पूर्णांक scalar,
				      व्योम (*func)(u64 *fpscr,
						 u32 *dst, u32 *src1,
						 u32 *src2, u32 *src3))
अणु
	u32 *qpr = vcpu->arch.qpr;
	u32 ps0_out;
	u32 ps0_in1, ps0_in2, ps0_in3;
	u32 ps1_in1, ps1_in2, ps1_in3;

	/* RC */
	WARN_ON(rc);

	/* PS0 */
	kvm_cvt_df(&VCPU_FPR(vcpu, reg_in1), &ps0_in1);
	kvm_cvt_df(&VCPU_FPR(vcpu, reg_in2), &ps0_in2);
	kvm_cvt_df(&VCPU_FPR(vcpu, reg_in3), &ps0_in3);

	अगर (scalar & SCALAR_LOW)
		ps0_in2 = qpr[reg_in2];

	func(&vcpu->arch.fp.fpscr, &ps0_out, &ps0_in1, &ps0_in2, &ps0_in3);

	dprपूर्णांकk(KERN_INFO "PS3 ps0 -> f(0x%x, 0x%x, 0x%x) = 0x%x\n",
			  ps0_in1, ps0_in2, ps0_in3, ps0_out);

	अगर (!(scalar & SCALAR_NO_PS0))
		kvm_cvt_fd(&ps0_out, &VCPU_FPR(vcpu, reg_out));

	/* PS1 */
	ps1_in1 = qpr[reg_in1];
	ps1_in2 = qpr[reg_in2];
	ps1_in3 = qpr[reg_in3];

	अगर (scalar & SCALAR_HIGH)
		ps1_in2 = ps0_in2;

	अगर (!(scalar & SCALAR_NO_PS1))
		func(&vcpu->arch.fp.fpscr, &qpr[reg_out], &ps1_in1, &ps1_in2, &ps1_in3);

	dprपूर्णांकk(KERN_INFO "PS3 ps1 -> f(0x%x, 0x%x, 0x%x) = 0x%x\n",
			  ps1_in1, ps1_in2, ps1_in3, qpr[reg_out]);

	वापस EMULATE_DONE;
पूर्ण

अटल पूर्णांक kvmppc_ps_two_in(काष्ठा kvm_vcpu *vcpu, bool rc,
				    पूर्णांक reg_out, पूर्णांक reg_in1, पूर्णांक reg_in2,
				    पूर्णांक scalar,
				    व्योम (*func)(u64 *fpscr,
						 u32 *dst, u32 *src1,
						 u32 *src2))
अणु
	u32 *qpr = vcpu->arch.qpr;
	u32 ps0_out;
	u32 ps0_in1, ps0_in2;
	u32 ps1_out;
	u32 ps1_in1, ps1_in2;

	/* RC */
	WARN_ON(rc);

	/* PS0 */
	kvm_cvt_df(&VCPU_FPR(vcpu, reg_in1), &ps0_in1);

	अगर (scalar & SCALAR_LOW)
		ps0_in2 = qpr[reg_in2];
	अन्यथा
		kvm_cvt_df(&VCPU_FPR(vcpu, reg_in2), &ps0_in2);

	func(&vcpu->arch.fp.fpscr, &ps0_out, &ps0_in1, &ps0_in2);

	अगर (!(scalar & SCALAR_NO_PS0)) अणु
		dprपूर्णांकk(KERN_INFO "PS2 ps0 -> f(0x%x, 0x%x) = 0x%x\n",
				  ps0_in1, ps0_in2, ps0_out);

		kvm_cvt_fd(&ps0_out, &VCPU_FPR(vcpu, reg_out));
	पूर्ण

	/* PS1 */
	ps1_in1 = qpr[reg_in1];
	ps1_in2 = qpr[reg_in2];

	अगर (scalar & SCALAR_HIGH)
		ps1_in2 = ps0_in2;

	func(&vcpu->arch.fp.fpscr, &ps1_out, &ps1_in1, &ps1_in2);

	अगर (!(scalar & SCALAR_NO_PS1)) अणु
		qpr[reg_out] = ps1_out;

		dprपूर्णांकk(KERN_INFO "PS2 ps1 -> f(0x%x, 0x%x) = 0x%x\n",
				  ps1_in1, ps1_in2, qpr[reg_out]);
	पूर्ण

	वापस EMULATE_DONE;
पूर्ण

अटल पूर्णांक kvmppc_ps_one_in(काष्ठा kvm_vcpu *vcpu, bool rc,
				    पूर्णांक reg_out, पूर्णांक reg_in,
				    व्योम (*func)(u64 *t,
						 u32 *dst, u32 *src1))
अणु
	u32 *qpr = vcpu->arch.qpr;
	u32 ps0_out, ps0_in;
	u32 ps1_in;

	/* RC */
	WARN_ON(rc);

	/* PS0 */
	kvm_cvt_df(&VCPU_FPR(vcpu, reg_in), &ps0_in);
	func(&vcpu->arch.fp.fpscr, &ps0_out, &ps0_in);

	dprपूर्णांकk(KERN_INFO "PS1 ps0 -> f(0x%x) = 0x%x\n",
			  ps0_in, ps0_out);

	kvm_cvt_fd(&ps0_out, &VCPU_FPR(vcpu, reg_out));

	/* PS1 */
	ps1_in = qpr[reg_in];
	func(&vcpu->arch.fp.fpscr, &qpr[reg_out], &ps1_in);

	dprपूर्णांकk(KERN_INFO "PS1 ps1 -> f(0x%x) = 0x%x\n",
			  ps1_in, qpr[reg_out]);

	वापस EMULATE_DONE;
पूर्ण

पूर्णांक kvmppc_emulate_paired_single(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 inst;
	क्रमागत emulation_result emulated = EMULATE_DONE;
	पूर्णांक ax_rd, ax_ra, ax_rb, ax_rc;
	लघु full_d;
	u64 *fpr_d, *fpr_a, *fpr_b, *fpr_c;

	bool rcomp;
	u32 cr;
#अगर_घोषित DEBUG
	पूर्णांक i;
#पूर्ण_अगर

	emulated = kvmppc_get_last_inst(vcpu, INST_GENERIC, &inst);
	अगर (emulated != EMULATE_DONE)
		वापस emulated;

	ax_rd = inst_get_field(inst, 6, 10);
	ax_ra = inst_get_field(inst, 11, 15);
	ax_rb = inst_get_field(inst, 16, 20);
	ax_rc = inst_get_field(inst, 21, 25);
	full_d = inst_get_field(inst, 16, 31);

	fpr_d = &VCPU_FPR(vcpu, ax_rd);
	fpr_a = &VCPU_FPR(vcpu, ax_ra);
	fpr_b = &VCPU_FPR(vcpu, ax_rb);
	fpr_c = &VCPU_FPR(vcpu, ax_rc);

	rcomp = (inst & 1) ? true : false;
	cr = kvmppc_get_cr(vcpu);

	अगर (!kvmppc_inst_is_paired_single(vcpu, inst))
		वापस EMULATE_FAIL;

	अगर (!(kvmppc_get_msr(vcpu) & MSR_FP)) अणु
		kvmppc_book3s_queue_irqprio(vcpu, BOOK3S_INTERRUPT_FP_UNAVAIL);
		वापस EMULATE_AGAIN;
	पूर्ण

	kvmppc_giveup_ext(vcpu, MSR_FP);
	preempt_disable();
	enable_kernel_fp();
	/* Do we need to clear FE0 / FE1 here? Don't think so. */

#अगर_घोषित DEBUG
	क्रम (i = 0; i < ARRAY_SIZE(vcpu->arch.fp.fpr); i++) अणु
		u32 f;
		kvm_cvt_df(&VCPU_FPR(vcpu, i), &f);
		dprपूर्णांकk(KERN_INFO "FPR[%d] = 0x%x / 0x%llx    QPR[%d] = 0x%x\n",
			i, f, VCPU_FPR(vcpu, i), i, vcpu->arch.qpr[i]);
	पूर्ण
#पूर्ण_अगर

	चयन (get_op(inst)) अणु
	हाल OP_PSQ_L:
	अणु
		uदीर्घ addr = ax_ra ? kvmppc_get_gpr(vcpu, ax_ra) : 0;
		bool w = inst_get_field(inst, 16, 16) ? true : false;
		पूर्णांक i = inst_get_field(inst, 17, 19);

		addr += get_d_signext(inst);
		emulated = kvmppc_emulate_psq_load(vcpu, ax_rd, addr, w, i);
		अवरोध;
	पूर्ण
	हाल OP_PSQ_LU:
	अणु
		uदीर्घ addr = kvmppc_get_gpr(vcpu, ax_ra);
		bool w = inst_get_field(inst, 16, 16) ? true : false;
		पूर्णांक i = inst_get_field(inst, 17, 19);

		addr += get_d_signext(inst);
		emulated = kvmppc_emulate_psq_load(vcpu, ax_rd, addr, w, i);

		अगर (emulated == EMULATE_DONE)
			kvmppc_set_gpr(vcpu, ax_ra, addr);
		अवरोध;
	पूर्ण
	हाल OP_PSQ_ST:
	अणु
		uदीर्घ addr = ax_ra ? kvmppc_get_gpr(vcpu, ax_ra) : 0;
		bool w = inst_get_field(inst, 16, 16) ? true : false;
		पूर्णांक i = inst_get_field(inst, 17, 19);

		addr += get_d_signext(inst);
		emulated = kvmppc_emulate_psq_store(vcpu, ax_rd, addr, w, i);
		अवरोध;
	पूर्ण
	हाल OP_PSQ_STU:
	अणु
		uदीर्घ addr = kvmppc_get_gpr(vcpu, ax_ra);
		bool w = inst_get_field(inst, 16, 16) ? true : false;
		पूर्णांक i = inst_get_field(inst, 17, 19);

		addr += get_d_signext(inst);
		emulated = kvmppc_emulate_psq_store(vcpu, ax_rd, addr, w, i);

		अगर (emulated == EMULATE_DONE)
			kvmppc_set_gpr(vcpu, ax_ra, addr);
		अवरोध;
	पूर्ण
	हाल 4:
		/* X क्रमm */
		चयन (inst_get_field(inst, 21, 30)) अणु
		हाल OP_4X_PS_CMPU0:
			/* XXX */
			emulated = EMULATE_FAIL;
			अवरोध;
		हाल OP_4X_PSQ_LX:
		अणु
			uदीर्घ addr = ax_ra ? kvmppc_get_gpr(vcpu, ax_ra) : 0;
			bool w = inst_get_field(inst, 21, 21) ? true : false;
			पूर्णांक i = inst_get_field(inst, 22, 24);

			addr += kvmppc_get_gpr(vcpu, ax_rb);
			emulated = kvmppc_emulate_psq_load(vcpu, ax_rd, addr, w, i);
			अवरोध;
		पूर्ण
		हाल OP_4X_PS_CMPO0:
			/* XXX */
			emulated = EMULATE_FAIL;
			अवरोध;
		हाल OP_4X_PSQ_LUX:
		अणु
			uदीर्घ addr = kvmppc_get_gpr(vcpu, ax_ra);
			bool w = inst_get_field(inst, 21, 21) ? true : false;
			पूर्णांक i = inst_get_field(inst, 22, 24);

			addr += kvmppc_get_gpr(vcpu, ax_rb);
			emulated = kvmppc_emulate_psq_load(vcpu, ax_rd, addr, w, i);

			अगर (emulated == EMULATE_DONE)
				kvmppc_set_gpr(vcpu, ax_ra, addr);
			अवरोध;
		पूर्ण
		हाल OP_4X_PS_NEG:
			VCPU_FPR(vcpu, ax_rd) = VCPU_FPR(vcpu, ax_rb);
			VCPU_FPR(vcpu, ax_rd) ^= 0x8000000000000000ULL;
			vcpu->arch.qpr[ax_rd] = vcpu->arch.qpr[ax_rb];
			vcpu->arch.qpr[ax_rd] ^= 0x80000000;
			अवरोध;
		हाल OP_4X_PS_CMPU1:
			/* XXX */
			emulated = EMULATE_FAIL;
			अवरोध;
		हाल OP_4X_PS_MR:
			WARN_ON(rcomp);
			VCPU_FPR(vcpu, ax_rd) = VCPU_FPR(vcpu, ax_rb);
			vcpu->arch.qpr[ax_rd] = vcpu->arch.qpr[ax_rb];
			अवरोध;
		हाल OP_4X_PS_CMPO1:
			/* XXX */
			emulated = EMULATE_FAIL;
			अवरोध;
		हाल OP_4X_PS_NABS:
			WARN_ON(rcomp);
			VCPU_FPR(vcpu, ax_rd) = VCPU_FPR(vcpu, ax_rb);
			VCPU_FPR(vcpu, ax_rd) |= 0x8000000000000000ULL;
			vcpu->arch.qpr[ax_rd] = vcpu->arch.qpr[ax_rb];
			vcpu->arch.qpr[ax_rd] |= 0x80000000;
			अवरोध;
		हाल OP_4X_PS_ABS:
			WARN_ON(rcomp);
			VCPU_FPR(vcpu, ax_rd) = VCPU_FPR(vcpu, ax_rb);
			VCPU_FPR(vcpu, ax_rd) &= ~0x8000000000000000ULL;
			vcpu->arch.qpr[ax_rd] = vcpu->arch.qpr[ax_rb];
			vcpu->arch.qpr[ax_rd] &= ~0x80000000;
			अवरोध;
		हाल OP_4X_PS_MERGE00:
			WARN_ON(rcomp);
			VCPU_FPR(vcpu, ax_rd) = VCPU_FPR(vcpu, ax_ra);
			/* vcpu->arch.qpr[ax_rd] = VCPU_FPR(vcpu, ax_rb); */
			kvm_cvt_df(&VCPU_FPR(vcpu, ax_rb),
				   &vcpu->arch.qpr[ax_rd]);
			अवरोध;
		हाल OP_4X_PS_MERGE01:
			WARN_ON(rcomp);
			VCPU_FPR(vcpu, ax_rd) = VCPU_FPR(vcpu, ax_ra);
			vcpu->arch.qpr[ax_rd] = vcpu->arch.qpr[ax_rb];
			अवरोध;
		हाल OP_4X_PS_MERGE10:
			WARN_ON(rcomp);
			/* VCPU_FPR(vcpu, ax_rd) = vcpu->arch.qpr[ax_ra]; */
			kvm_cvt_fd(&vcpu->arch.qpr[ax_ra],
				   &VCPU_FPR(vcpu, ax_rd));
			/* vcpu->arch.qpr[ax_rd] = VCPU_FPR(vcpu, ax_rb); */
			kvm_cvt_df(&VCPU_FPR(vcpu, ax_rb),
				   &vcpu->arch.qpr[ax_rd]);
			अवरोध;
		हाल OP_4X_PS_MERGE11:
			WARN_ON(rcomp);
			/* VCPU_FPR(vcpu, ax_rd) = vcpu->arch.qpr[ax_ra]; */
			kvm_cvt_fd(&vcpu->arch.qpr[ax_ra],
				   &VCPU_FPR(vcpu, ax_rd));
			vcpu->arch.qpr[ax_rd] = vcpu->arch.qpr[ax_rb];
			अवरोध;
		पूर्ण
		/* XW क्रमm */
		चयन (inst_get_field(inst, 25, 30)) अणु
		हाल OP_4XW_PSQ_STX:
		अणु
			uदीर्घ addr = ax_ra ? kvmppc_get_gpr(vcpu, ax_ra) : 0;
			bool w = inst_get_field(inst, 21, 21) ? true : false;
			पूर्णांक i = inst_get_field(inst, 22, 24);

			addr += kvmppc_get_gpr(vcpu, ax_rb);
			emulated = kvmppc_emulate_psq_store(vcpu, ax_rd, addr, w, i);
			अवरोध;
		पूर्ण
		हाल OP_4XW_PSQ_STUX:
		अणु
			uदीर्घ addr = kvmppc_get_gpr(vcpu, ax_ra);
			bool w = inst_get_field(inst, 21, 21) ? true : false;
			पूर्णांक i = inst_get_field(inst, 22, 24);

			addr += kvmppc_get_gpr(vcpu, ax_rb);
			emulated = kvmppc_emulate_psq_store(vcpu, ax_rd, addr, w, i);

			अगर (emulated == EMULATE_DONE)
				kvmppc_set_gpr(vcpu, ax_ra, addr);
			अवरोध;
		पूर्ण
		पूर्ण
		/* A क्रमm */
		चयन (inst_get_field(inst, 26, 30)) अणु
		हाल OP_4A_PS_SUM1:
			emulated = kvmppc_ps_two_in(vcpu, rcomp, ax_rd,
					ax_rb, ax_ra, SCALAR_NO_PS0 | SCALAR_HIGH, fps_fadds);
			VCPU_FPR(vcpu, ax_rd) = VCPU_FPR(vcpu, ax_rc);
			अवरोध;
		हाल OP_4A_PS_SUM0:
			emulated = kvmppc_ps_two_in(vcpu, rcomp, ax_rd,
					ax_ra, ax_rb, SCALAR_NO_PS1 | SCALAR_LOW, fps_fadds);
			vcpu->arch.qpr[ax_rd] = vcpu->arch.qpr[ax_rc];
			अवरोध;
		हाल OP_4A_PS_MULS0:
			emulated = kvmppc_ps_two_in(vcpu, rcomp, ax_rd,
					ax_ra, ax_rc, SCALAR_HIGH, fps_fmuls);
			अवरोध;
		हाल OP_4A_PS_MULS1:
			emulated = kvmppc_ps_two_in(vcpu, rcomp, ax_rd,
					ax_ra, ax_rc, SCALAR_LOW, fps_fmuls);
			अवरोध;
		हाल OP_4A_PS_MADDS0:
			emulated = kvmppc_ps_three_in(vcpu, rcomp, ax_rd,
					ax_ra, ax_rc, ax_rb, SCALAR_HIGH, fps_fmadds);
			अवरोध;
		हाल OP_4A_PS_MADDS1:
			emulated = kvmppc_ps_three_in(vcpu, rcomp, ax_rd,
					ax_ra, ax_rc, ax_rb, SCALAR_LOW, fps_fmadds);
			अवरोध;
		हाल OP_4A_PS_DIV:
			emulated = kvmppc_ps_two_in(vcpu, rcomp, ax_rd,
					ax_ra, ax_rb, SCALAR_NONE, fps_fभागs);
			अवरोध;
		हाल OP_4A_PS_SUB:
			emulated = kvmppc_ps_two_in(vcpu, rcomp, ax_rd,
					ax_ra, ax_rb, SCALAR_NONE, fps_fsubs);
			अवरोध;
		हाल OP_4A_PS_ADD:
			emulated = kvmppc_ps_two_in(vcpu, rcomp, ax_rd,
					ax_ra, ax_rb, SCALAR_NONE, fps_fadds);
			अवरोध;
		हाल OP_4A_PS_SEL:
			emulated = kvmppc_ps_three_in(vcpu, rcomp, ax_rd,
					ax_ra, ax_rc, ax_rb, SCALAR_NONE, fps_fsel);
			अवरोध;
		हाल OP_4A_PS_RES:
			emulated = kvmppc_ps_one_in(vcpu, rcomp, ax_rd,
					ax_rb, fps_fres);
			अवरोध;
		हाल OP_4A_PS_MUL:
			emulated = kvmppc_ps_two_in(vcpu, rcomp, ax_rd,
					ax_ra, ax_rc, SCALAR_NONE, fps_fmuls);
			अवरोध;
		हाल OP_4A_PS_RSQRTE:
			emulated = kvmppc_ps_one_in(vcpu, rcomp, ax_rd,
					ax_rb, fps_frवर्ग_मूलe);
			अवरोध;
		हाल OP_4A_PS_MSUB:
			emulated = kvmppc_ps_three_in(vcpu, rcomp, ax_rd,
					ax_ra, ax_rc, ax_rb, SCALAR_NONE, fps_fmsubs);
			अवरोध;
		हाल OP_4A_PS_MADD:
			emulated = kvmppc_ps_three_in(vcpu, rcomp, ax_rd,
					ax_ra, ax_rc, ax_rb, SCALAR_NONE, fps_fmadds);
			अवरोध;
		हाल OP_4A_PS_NMSUB:
			emulated = kvmppc_ps_three_in(vcpu, rcomp, ax_rd,
					ax_ra, ax_rc, ax_rb, SCALAR_NONE, fps_fnmsubs);
			अवरोध;
		हाल OP_4A_PS_NMADD:
			emulated = kvmppc_ps_three_in(vcpu, rcomp, ax_rd,
					ax_ra, ax_rc, ax_rb, SCALAR_NONE, fps_fnmadds);
			अवरोध;
		पूर्ण
		अवरोध;

	/* Real FPU operations */

	हाल OP_LFS:
	अणु
		uदीर्घ addr = (ax_ra ? kvmppc_get_gpr(vcpu, ax_ra) : 0) + full_d;

		emulated = kvmppc_emulate_fpr_load(vcpu, ax_rd, addr,
						   FPU_LS_SINGLE);
		अवरोध;
	पूर्ण
	हाल OP_LFSU:
	अणु
		uदीर्घ addr = kvmppc_get_gpr(vcpu, ax_ra) + full_d;

		emulated = kvmppc_emulate_fpr_load(vcpu, ax_rd, addr,
						   FPU_LS_SINGLE);

		अगर (emulated == EMULATE_DONE)
			kvmppc_set_gpr(vcpu, ax_ra, addr);
		अवरोध;
	पूर्ण
	हाल OP_LFD:
	अणु
		uदीर्घ addr = (ax_ra ? kvmppc_get_gpr(vcpu, ax_ra) : 0) + full_d;

		emulated = kvmppc_emulate_fpr_load(vcpu, ax_rd, addr,
						   FPU_LS_DOUBLE);
		अवरोध;
	पूर्ण
	हाल OP_LFDU:
	अणु
		uदीर्घ addr = kvmppc_get_gpr(vcpu, ax_ra) + full_d;

		emulated = kvmppc_emulate_fpr_load(vcpu, ax_rd, addr,
						   FPU_LS_DOUBLE);

		अगर (emulated == EMULATE_DONE)
			kvmppc_set_gpr(vcpu, ax_ra, addr);
		अवरोध;
	पूर्ण
	हाल OP_STFS:
	अणु
		uदीर्घ addr = (ax_ra ? kvmppc_get_gpr(vcpu, ax_ra) : 0) + full_d;

		emulated = kvmppc_emulate_fpr_store(vcpu, ax_rd, addr,
						    FPU_LS_SINGLE);
		अवरोध;
	पूर्ण
	हाल OP_STFSU:
	अणु
		uदीर्घ addr = kvmppc_get_gpr(vcpu, ax_ra) + full_d;

		emulated = kvmppc_emulate_fpr_store(vcpu, ax_rd, addr,
						    FPU_LS_SINGLE);

		अगर (emulated == EMULATE_DONE)
			kvmppc_set_gpr(vcpu, ax_ra, addr);
		अवरोध;
	पूर्ण
	हाल OP_STFD:
	अणु
		uदीर्घ addr = (ax_ra ? kvmppc_get_gpr(vcpu, ax_ra) : 0) + full_d;

		emulated = kvmppc_emulate_fpr_store(vcpu, ax_rd, addr,
						    FPU_LS_DOUBLE);
		अवरोध;
	पूर्ण
	हाल OP_STFDU:
	अणु
		uदीर्घ addr = kvmppc_get_gpr(vcpu, ax_ra) + full_d;

		emulated = kvmppc_emulate_fpr_store(vcpu, ax_rd, addr,
						    FPU_LS_DOUBLE);

		अगर (emulated == EMULATE_DONE)
			kvmppc_set_gpr(vcpu, ax_ra, addr);
		अवरोध;
	पूर्ण
	हाल 31:
		चयन (inst_get_field(inst, 21, 30)) अणु
		हाल OP_31_LFSX:
		अणु
			uदीर्घ addr = ax_ra ? kvmppc_get_gpr(vcpu, ax_ra) : 0;

			addr += kvmppc_get_gpr(vcpu, ax_rb);
			emulated = kvmppc_emulate_fpr_load(vcpu, ax_rd,
							   addr, FPU_LS_SINGLE);
			अवरोध;
		पूर्ण
		हाल OP_31_LFSUX:
		अणु
			uदीर्घ addr = kvmppc_get_gpr(vcpu, ax_ra) +
				     kvmppc_get_gpr(vcpu, ax_rb);

			emulated = kvmppc_emulate_fpr_load(vcpu, ax_rd,
							   addr, FPU_LS_SINGLE);

			अगर (emulated == EMULATE_DONE)
				kvmppc_set_gpr(vcpu, ax_ra, addr);
			अवरोध;
		पूर्ण
		हाल OP_31_LFDX:
		अणु
			uदीर्घ addr = (ax_ra ? kvmppc_get_gpr(vcpu, ax_ra) : 0) +
				     kvmppc_get_gpr(vcpu, ax_rb);

			emulated = kvmppc_emulate_fpr_load(vcpu, ax_rd,
							   addr, FPU_LS_DOUBLE);
			अवरोध;
		पूर्ण
		हाल OP_31_LFDUX:
		अणु
			uदीर्घ addr = kvmppc_get_gpr(vcpu, ax_ra) +
				     kvmppc_get_gpr(vcpu, ax_rb);

			emulated = kvmppc_emulate_fpr_load(vcpu, ax_rd,
							   addr, FPU_LS_DOUBLE);

			अगर (emulated == EMULATE_DONE)
				kvmppc_set_gpr(vcpu, ax_ra, addr);
			अवरोध;
		पूर्ण
		हाल OP_31_STFSX:
		अणु
			uदीर्घ addr = (ax_ra ? kvmppc_get_gpr(vcpu, ax_ra) : 0) +
				     kvmppc_get_gpr(vcpu, ax_rb);

			emulated = kvmppc_emulate_fpr_store(vcpu, ax_rd,
							    addr, FPU_LS_SINGLE);
			अवरोध;
		पूर्ण
		हाल OP_31_STFSUX:
		अणु
			uदीर्घ addr = kvmppc_get_gpr(vcpu, ax_ra) +
				     kvmppc_get_gpr(vcpu, ax_rb);

			emulated = kvmppc_emulate_fpr_store(vcpu, ax_rd,
							    addr, FPU_LS_SINGLE);

			अगर (emulated == EMULATE_DONE)
				kvmppc_set_gpr(vcpu, ax_ra, addr);
			अवरोध;
		पूर्ण
		हाल OP_31_STFX:
		अणु
			uदीर्घ addr = (ax_ra ? kvmppc_get_gpr(vcpu, ax_ra) : 0) +
				     kvmppc_get_gpr(vcpu, ax_rb);

			emulated = kvmppc_emulate_fpr_store(vcpu, ax_rd,
							    addr, FPU_LS_DOUBLE);
			अवरोध;
		पूर्ण
		हाल OP_31_STFUX:
		अणु
			uदीर्घ addr = kvmppc_get_gpr(vcpu, ax_ra) +
				     kvmppc_get_gpr(vcpu, ax_rb);

			emulated = kvmppc_emulate_fpr_store(vcpu, ax_rd,
							    addr, FPU_LS_DOUBLE);

			अगर (emulated == EMULATE_DONE)
				kvmppc_set_gpr(vcpu, ax_ra, addr);
			अवरोध;
		पूर्ण
		हाल OP_31_STFIWX:
		अणु
			uदीर्घ addr = (ax_ra ? kvmppc_get_gpr(vcpu, ax_ra) : 0) +
				     kvmppc_get_gpr(vcpu, ax_rb);

			emulated = kvmppc_emulate_fpr_store(vcpu, ax_rd,
							    addr,
							    FPU_LS_SINGLE_LOW);
			अवरोध;
		पूर्ण
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 59:
		चयन (inst_get_field(inst, 21, 30)) अणु
		हाल OP_59_FADDS:
			fpd_fadds(&vcpu->arch.fp.fpscr, &cr, fpr_d, fpr_a, fpr_b);
			kvmppc_sync_qpr(vcpu, ax_rd);
			अवरोध;
		हाल OP_59_FSUBS:
			fpd_fsubs(&vcpu->arch.fp.fpscr, &cr, fpr_d, fpr_a, fpr_b);
			kvmppc_sync_qpr(vcpu, ax_rd);
			अवरोध;
		हाल OP_59_FDIVS:
			fpd_fभागs(&vcpu->arch.fp.fpscr, &cr, fpr_d, fpr_a, fpr_b);
			kvmppc_sync_qpr(vcpu, ax_rd);
			अवरोध;
		हाल OP_59_FRES:
			fpd_fres(&vcpu->arch.fp.fpscr, &cr, fpr_d, fpr_b);
			kvmppc_sync_qpr(vcpu, ax_rd);
			अवरोध;
		हाल OP_59_FRSQRTES:
			fpd_frवर्ग_मूलes(&vcpu->arch.fp.fpscr, &cr, fpr_d, fpr_b);
			kvmppc_sync_qpr(vcpu, ax_rd);
			अवरोध;
		पूर्ण
		चयन (inst_get_field(inst, 26, 30)) अणु
		हाल OP_59_FMULS:
			fpd_fmuls(&vcpu->arch.fp.fpscr, &cr, fpr_d, fpr_a, fpr_c);
			kvmppc_sync_qpr(vcpu, ax_rd);
			अवरोध;
		हाल OP_59_FMSUBS:
			fpd_fmsubs(&vcpu->arch.fp.fpscr, &cr, fpr_d, fpr_a, fpr_c, fpr_b);
			kvmppc_sync_qpr(vcpu, ax_rd);
			अवरोध;
		हाल OP_59_FMADDS:
			fpd_fmadds(&vcpu->arch.fp.fpscr, &cr, fpr_d, fpr_a, fpr_c, fpr_b);
			kvmppc_sync_qpr(vcpu, ax_rd);
			अवरोध;
		हाल OP_59_FNMSUBS:
			fpd_fnmsubs(&vcpu->arch.fp.fpscr, &cr, fpr_d, fpr_a, fpr_c, fpr_b);
			kvmppc_sync_qpr(vcpu, ax_rd);
			अवरोध;
		हाल OP_59_FNMADDS:
			fpd_fnmadds(&vcpu->arch.fp.fpscr, &cr, fpr_d, fpr_a, fpr_c, fpr_b);
			kvmppc_sync_qpr(vcpu, ax_rd);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 63:
		चयन (inst_get_field(inst, 21, 30)) अणु
		हाल OP_63_MTFSB0:
		हाल OP_63_MTFSB1:
		हाल OP_63_MCRFS:
		हाल OP_63_MTFSFI:
			/* XXX need to implement */
			अवरोध;
		हाल OP_63_MFFS:
			/* XXX missing CR */
			*fpr_d = vcpu->arch.fp.fpscr;
			अवरोध;
		हाल OP_63_MTFSF:
			/* XXX missing fm bits */
			/* XXX missing CR */
			vcpu->arch.fp.fpscr = *fpr_b;
			अवरोध;
		हाल OP_63_FCMPU:
		अणु
			u32 पंचांगp_cr;
			u32 cr0_mask = 0xf0000000;
			u32 cr_shअगरt = inst_get_field(inst, 6, 8) * 4;

			fpd_fcmpu(&vcpu->arch.fp.fpscr, &पंचांगp_cr, fpr_a, fpr_b);
			cr &= ~(cr0_mask >> cr_shअगरt);
			cr |= (cr & cr0_mask) >> cr_shअगरt;
			अवरोध;
		पूर्ण
		हाल OP_63_FCMPO:
		अणु
			u32 पंचांगp_cr;
			u32 cr0_mask = 0xf0000000;
			u32 cr_shअगरt = inst_get_field(inst, 6, 8) * 4;

			fpd_fcmpo(&vcpu->arch.fp.fpscr, &पंचांगp_cr, fpr_a, fpr_b);
			cr &= ~(cr0_mask >> cr_shअगरt);
			cr |= (cr & cr0_mask) >> cr_shअगरt;
			अवरोध;
		पूर्ण
		हाल OP_63_FNEG:
			fpd_fneg(&vcpu->arch.fp.fpscr, &cr, fpr_d, fpr_b);
			अवरोध;
		हाल OP_63_FMR:
			*fpr_d = *fpr_b;
			अवरोध;
		हाल OP_63_FABS:
			fpd_भ_असल(&vcpu->arch.fp.fpscr, &cr, fpr_d, fpr_b);
			अवरोध;
		हाल OP_63_FCPSGN:
			fpd_fcpsgn(&vcpu->arch.fp.fpscr, &cr, fpr_d, fpr_a, fpr_b);
			अवरोध;
		हाल OP_63_FDIV:
			fpd_fभाग(&vcpu->arch.fp.fpscr, &cr, fpr_d, fpr_a, fpr_b);
			अवरोध;
		हाल OP_63_FADD:
			fpd_fadd(&vcpu->arch.fp.fpscr, &cr, fpr_d, fpr_a, fpr_b);
			अवरोध;
		हाल OP_63_FSUB:
			fpd_fsub(&vcpu->arch.fp.fpscr, &cr, fpr_d, fpr_a, fpr_b);
			अवरोध;
		हाल OP_63_FCTIW:
			fpd_fctiw(&vcpu->arch.fp.fpscr, &cr, fpr_d, fpr_b);
			अवरोध;
		हाल OP_63_FCTIWZ:
			fpd_fctiwz(&vcpu->arch.fp.fpscr, &cr, fpr_d, fpr_b);
			अवरोध;
		हाल OP_63_FRSP:
			fpd_frsp(&vcpu->arch.fp.fpscr, &cr, fpr_d, fpr_b);
			kvmppc_sync_qpr(vcpu, ax_rd);
			अवरोध;
		हाल OP_63_FRSQRTE:
		अणु
			द्विगुन one = 1.0f;

			/* fD = वर्ग_मूल(fB) */
			fpd_fवर्ग_मूल(&vcpu->arch.fp.fpscr, &cr, fpr_d, fpr_b);
			/* fD = 1.0f / fD */
			fpd_fभाग(&vcpu->arch.fp.fpscr, &cr, fpr_d, (u64*)&one, fpr_d);
			अवरोध;
		पूर्ण
		पूर्ण
		चयन (inst_get_field(inst, 26, 30)) अणु
		हाल OP_63_FMUL:
			fpd_fmul(&vcpu->arch.fp.fpscr, &cr, fpr_d, fpr_a, fpr_c);
			अवरोध;
		हाल OP_63_FSEL:
			fpd_fsel(&vcpu->arch.fp.fpscr, &cr, fpr_d, fpr_a, fpr_c, fpr_b);
			अवरोध;
		हाल OP_63_FMSUB:
			fpd_fmsub(&vcpu->arch.fp.fpscr, &cr, fpr_d, fpr_a, fpr_c, fpr_b);
			अवरोध;
		हाल OP_63_FMADD:
			fpd_fmadd(&vcpu->arch.fp.fpscr, &cr, fpr_d, fpr_a, fpr_c, fpr_b);
			अवरोध;
		हाल OP_63_FNMSUB:
			fpd_fnmsub(&vcpu->arch.fp.fpscr, &cr, fpr_d, fpr_a, fpr_c, fpr_b);
			अवरोध;
		हाल OP_63_FNMADD:
			fpd_fnmadd(&vcpu->arch.fp.fpscr, &cr, fpr_d, fpr_a, fpr_c, fpr_b);
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

#अगर_घोषित DEBUG
	क्रम (i = 0; i < ARRAY_SIZE(vcpu->arch.fp.fpr); i++) अणु
		u32 f;
		kvm_cvt_df(&VCPU_FPR(vcpu, i), &f);
		dprपूर्णांकk(KERN_INFO "FPR[%d] = 0x%x\n", i, f);
	पूर्ण
#पूर्ण_अगर

	अगर (rcomp)
		kvmppc_set_cr(vcpu, cr);

	disable_kernel_fp();
	preempt_enable();

	वापस emulated;
पूर्ण
