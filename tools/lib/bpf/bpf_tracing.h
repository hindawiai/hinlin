<शैली गुरु>
/* SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause) */
#अगर_अघोषित __BPF_TRACING_H__
#घोषणा __BPF_TRACING_H__

/* Scan the ARCH passed in from ARCH env variable (see Makefile) */
#अगर defined(__TARGET_ARCH_x86)
	#घोषणा bpf_target_x86
	#घोषणा bpf_target_defined
#या_अगर defined(__TARGET_ARCH_s390)
	#घोषणा bpf_target_s390
	#घोषणा bpf_target_defined
#या_अगर defined(__TARGET_ARCH_arm)
	#घोषणा bpf_target_arm
	#घोषणा bpf_target_defined
#या_अगर defined(__TARGET_ARCH_arm64)
	#घोषणा bpf_target_arm64
	#घोषणा bpf_target_defined
#या_अगर defined(__TARGET_ARCH_mips)
	#घोषणा bpf_target_mips
	#घोषणा bpf_target_defined
#या_अगर defined(__TARGET_ARCH_घातerpc)
	#घोषणा bpf_target_घातerpc
	#घोषणा bpf_target_defined
#या_अगर defined(__TARGET_ARCH_sparc)
	#घोषणा bpf_target_sparc
	#घोषणा bpf_target_defined
#अन्यथा
	#अघोषित bpf_target_defined
#पूर्ण_अगर

/* Fall back to what the compiler says */
#अगर_अघोषित bpf_target_defined
#अगर defined(__x86_64__)
	#घोषणा bpf_target_x86
#या_अगर defined(__s390__)
	#घोषणा bpf_target_s390
#या_अगर defined(__arm__)
	#घोषणा bpf_target_arm
#या_अगर defined(__aarch64__)
	#घोषणा bpf_target_arm64
#या_अगर defined(__mips__)
	#घोषणा bpf_target_mips
#या_अगर defined(__घातerpc__)
	#घोषणा bpf_target_घातerpc
#या_अगर defined(__sparc__)
	#घोषणा bpf_target_sparc
#पूर्ण_अगर
#पूर्ण_अगर

#अगर defined(bpf_target_x86)

#अगर defined(__KERNEL__) || defined(__VMLINUX_H__)

#घोषणा PT_REGS_PARM1(x) ((x)->di)
#घोषणा PT_REGS_PARM2(x) ((x)->si)
#घोषणा PT_REGS_PARM3(x) ((x)->dx)
#घोषणा PT_REGS_PARM4(x) ((x)->cx)
#घोषणा PT_REGS_PARM5(x) ((x)->r8)
#घोषणा PT_REGS_RET(x) ((x)->sp)
#घोषणा PT_REGS_FP(x) ((x)->bp)
#घोषणा PT_REGS_RC(x) ((x)->ax)
#घोषणा PT_REGS_SP(x) ((x)->sp)
#घोषणा PT_REGS_IP(x) ((x)->ip)

#घोषणा PT_REGS_PARM1_CORE(x) BPF_CORE_READ((x), di)
#घोषणा PT_REGS_PARM2_CORE(x) BPF_CORE_READ((x), si)
#घोषणा PT_REGS_PARM3_CORE(x) BPF_CORE_READ((x), dx)
#घोषणा PT_REGS_PARM4_CORE(x) BPF_CORE_READ((x), cx)
#घोषणा PT_REGS_PARM5_CORE(x) BPF_CORE_READ((x), r8)
#घोषणा PT_REGS_RET_CORE(x) BPF_CORE_READ((x), sp)
#घोषणा PT_REGS_FP_CORE(x) BPF_CORE_READ((x), bp)
#घोषणा PT_REGS_RC_CORE(x) BPF_CORE_READ((x), ax)
#घोषणा PT_REGS_SP_CORE(x) BPF_CORE_READ((x), sp)
#घोषणा PT_REGS_IP_CORE(x) BPF_CORE_READ((x), ip)

#अन्यथा

#अगर_घोषित __i386__
/* i386 kernel is built with -mregparm=3 */
#घोषणा PT_REGS_PARM1(x) ((x)->eax)
#घोषणा PT_REGS_PARM2(x) ((x)->edx)
#घोषणा PT_REGS_PARM3(x) ((x)->ecx)
#घोषणा PT_REGS_PARM4(x) 0
#घोषणा PT_REGS_PARM5(x) 0
#घोषणा PT_REGS_RET(x) ((x)->esp)
#घोषणा PT_REGS_FP(x) ((x)->ebp)
#घोषणा PT_REGS_RC(x) ((x)->eax)
#घोषणा PT_REGS_SP(x) ((x)->esp)
#घोषणा PT_REGS_IP(x) ((x)->eip)

#घोषणा PT_REGS_PARM1_CORE(x) BPF_CORE_READ((x), eax)
#घोषणा PT_REGS_PARM2_CORE(x) BPF_CORE_READ((x), edx)
#घोषणा PT_REGS_PARM3_CORE(x) BPF_CORE_READ((x), ecx)
#घोषणा PT_REGS_PARM4_CORE(x) 0
#घोषणा PT_REGS_PARM5_CORE(x) 0
#घोषणा PT_REGS_RET_CORE(x) BPF_CORE_READ((x), esp)
#घोषणा PT_REGS_FP_CORE(x) BPF_CORE_READ((x), ebp)
#घोषणा PT_REGS_RC_CORE(x) BPF_CORE_READ((x), eax)
#घोषणा PT_REGS_SP_CORE(x) BPF_CORE_READ((x), esp)
#घोषणा PT_REGS_IP_CORE(x) BPF_CORE_READ((x), eip)

#अन्यथा

#घोषणा PT_REGS_PARM1(x) ((x)->rdi)
#घोषणा PT_REGS_PARM2(x) ((x)->rsi)
#घोषणा PT_REGS_PARM3(x) ((x)->rdx)
#घोषणा PT_REGS_PARM4(x) ((x)->rcx)
#घोषणा PT_REGS_PARM5(x) ((x)->r8)
#घोषणा PT_REGS_RET(x) ((x)->rsp)
#घोषणा PT_REGS_FP(x) ((x)->rbp)
#घोषणा PT_REGS_RC(x) ((x)->rax)
#घोषणा PT_REGS_SP(x) ((x)->rsp)
#घोषणा PT_REGS_IP(x) ((x)->rip)

#घोषणा PT_REGS_PARM1_CORE(x) BPF_CORE_READ((x), rdi)
#घोषणा PT_REGS_PARM2_CORE(x) BPF_CORE_READ((x), rsi)
#घोषणा PT_REGS_PARM3_CORE(x) BPF_CORE_READ((x), rdx)
#घोषणा PT_REGS_PARM4_CORE(x) BPF_CORE_READ((x), rcx)
#घोषणा PT_REGS_PARM5_CORE(x) BPF_CORE_READ((x), r8)
#घोषणा PT_REGS_RET_CORE(x) BPF_CORE_READ((x), rsp)
#घोषणा PT_REGS_FP_CORE(x) BPF_CORE_READ((x), rbp)
#घोषणा PT_REGS_RC_CORE(x) BPF_CORE_READ((x), rax)
#घोषणा PT_REGS_SP_CORE(x) BPF_CORE_READ((x), rsp)
#घोषणा PT_REGS_IP_CORE(x) BPF_CORE_READ((x), rip)

#पूर्ण_अगर
#पूर्ण_अगर

#या_अगर defined(bpf_target_s390)

/* s390 provides user_pt_regs instead of काष्ठा pt_regs to userspace */
काष्ठा pt_regs;
#घोषणा PT_REGS_S390 स्थिर अस्थिर user_pt_regs
#घोषणा PT_REGS_PARM1(x) (((PT_REGS_S390 *)(x))->gprs[2])
#घोषणा PT_REGS_PARM2(x) (((PT_REGS_S390 *)(x))->gprs[3])
#घोषणा PT_REGS_PARM3(x) (((PT_REGS_S390 *)(x))->gprs[4])
#घोषणा PT_REGS_PARM4(x) (((PT_REGS_S390 *)(x))->gprs[5])
#घोषणा PT_REGS_PARM5(x) (((PT_REGS_S390 *)(x))->gprs[6])
#घोषणा PT_REGS_RET(x) (((PT_REGS_S390 *)(x))->gprs[14])
/* Works only with CONFIG_FRAME_POINTER */
#घोषणा PT_REGS_FP(x) (((PT_REGS_S390 *)(x))->gprs[11])
#घोषणा PT_REGS_RC(x) (((PT_REGS_S390 *)(x))->gprs[2])
#घोषणा PT_REGS_SP(x) (((PT_REGS_S390 *)(x))->gprs[15])
#घोषणा PT_REGS_IP(x) (((PT_REGS_S390 *)(x))->psw.addr)

#घोषणा PT_REGS_PARM1_CORE(x) BPF_CORE_READ((PT_REGS_S390 *)(x), gprs[2])
#घोषणा PT_REGS_PARM2_CORE(x) BPF_CORE_READ((PT_REGS_S390 *)(x), gprs[3])
#घोषणा PT_REGS_PARM3_CORE(x) BPF_CORE_READ((PT_REGS_S390 *)(x), gprs[4])
#घोषणा PT_REGS_PARM4_CORE(x) BPF_CORE_READ((PT_REGS_S390 *)(x), gprs[5])
#घोषणा PT_REGS_PARM5_CORE(x) BPF_CORE_READ((PT_REGS_S390 *)(x), gprs[6])
#घोषणा PT_REGS_RET_CORE(x) BPF_CORE_READ((PT_REGS_S390 *)(x), gprs[14])
#घोषणा PT_REGS_FP_CORE(x) BPF_CORE_READ((PT_REGS_S390 *)(x), gprs[11])
#घोषणा PT_REGS_RC_CORE(x) BPF_CORE_READ((PT_REGS_S390 *)(x), gprs[2])
#घोषणा PT_REGS_SP_CORE(x) BPF_CORE_READ((PT_REGS_S390 *)(x), gprs[15])
#घोषणा PT_REGS_IP_CORE(x) BPF_CORE_READ((PT_REGS_S390 *)(x), psw.addr)

#या_अगर defined(bpf_target_arm)

#घोषणा PT_REGS_PARM1(x) ((x)->uregs[0])
#घोषणा PT_REGS_PARM2(x) ((x)->uregs[1])
#घोषणा PT_REGS_PARM3(x) ((x)->uregs[2])
#घोषणा PT_REGS_PARM4(x) ((x)->uregs[3])
#घोषणा PT_REGS_PARM5(x) ((x)->uregs[4])
#घोषणा PT_REGS_RET(x) ((x)->uregs[14])
#घोषणा PT_REGS_FP(x) ((x)->uregs[11]) /* Works only with CONFIG_FRAME_POINTER */
#घोषणा PT_REGS_RC(x) ((x)->uregs[0])
#घोषणा PT_REGS_SP(x) ((x)->uregs[13])
#घोषणा PT_REGS_IP(x) ((x)->uregs[12])

#घोषणा PT_REGS_PARM1_CORE(x) BPF_CORE_READ((x), uregs[0])
#घोषणा PT_REGS_PARM2_CORE(x) BPF_CORE_READ((x), uregs[1])
#घोषणा PT_REGS_PARM3_CORE(x) BPF_CORE_READ((x), uregs[2])
#घोषणा PT_REGS_PARM4_CORE(x) BPF_CORE_READ((x), uregs[3])
#घोषणा PT_REGS_PARM5_CORE(x) BPF_CORE_READ((x), uregs[4])
#घोषणा PT_REGS_RET_CORE(x) BPF_CORE_READ((x), uregs[14])
#घोषणा PT_REGS_FP_CORE(x) BPF_CORE_READ((x), uregs[11])
#घोषणा PT_REGS_RC_CORE(x) BPF_CORE_READ((x), uregs[0])
#घोषणा PT_REGS_SP_CORE(x) BPF_CORE_READ((x), uregs[13])
#घोषणा PT_REGS_IP_CORE(x) BPF_CORE_READ((x), uregs[12])

#या_अगर defined(bpf_target_arm64)

/* arm64 provides काष्ठा user_pt_regs instead of काष्ठा pt_regs to userspace */
काष्ठा pt_regs;
#घोषणा PT_REGS_ARM64 स्थिर अस्थिर काष्ठा user_pt_regs
#घोषणा PT_REGS_PARM1(x) (((PT_REGS_ARM64 *)(x))->regs[0])
#घोषणा PT_REGS_PARM2(x) (((PT_REGS_ARM64 *)(x))->regs[1])
#घोषणा PT_REGS_PARM3(x) (((PT_REGS_ARM64 *)(x))->regs[2])
#घोषणा PT_REGS_PARM4(x) (((PT_REGS_ARM64 *)(x))->regs[3])
#घोषणा PT_REGS_PARM5(x) (((PT_REGS_ARM64 *)(x))->regs[4])
#घोषणा PT_REGS_RET(x) (((PT_REGS_ARM64 *)(x))->regs[30])
/* Works only with CONFIG_FRAME_POINTER */
#घोषणा PT_REGS_FP(x) (((PT_REGS_ARM64 *)(x))->regs[29])
#घोषणा PT_REGS_RC(x) (((PT_REGS_ARM64 *)(x))->regs[0])
#घोषणा PT_REGS_SP(x) (((PT_REGS_ARM64 *)(x))->sp)
#घोषणा PT_REGS_IP(x) (((PT_REGS_ARM64 *)(x))->pc)

#घोषणा PT_REGS_PARM1_CORE(x) BPF_CORE_READ((PT_REGS_ARM64 *)(x), regs[0])
#घोषणा PT_REGS_PARM2_CORE(x) BPF_CORE_READ((PT_REGS_ARM64 *)(x), regs[1])
#घोषणा PT_REGS_PARM3_CORE(x) BPF_CORE_READ((PT_REGS_ARM64 *)(x), regs[2])
#घोषणा PT_REGS_PARM4_CORE(x) BPF_CORE_READ((PT_REGS_ARM64 *)(x), regs[3])
#घोषणा PT_REGS_PARM5_CORE(x) BPF_CORE_READ((PT_REGS_ARM64 *)(x), regs[4])
#घोषणा PT_REGS_RET_CORE(x) BPF_CORE_READ((PT_REGS_ARM64 *)(x), regs[30])
#घोषणा PT_REGS_FP_CORE(x) BPF_CORE_READ((PT_REGS_ARM64 *)(x), regs[29])
#घोषणा PT_REGS_RC_CORE(x) BPF_CORE_READ((PT_REGS_ARM64 *)(x), regs[0])
#घोषणा PT_REGS_SP_CORE(x) BPF_CORE_READ((PT_REGS_ARM64 *)(x), sp)
#घोषणा PT_REGS_IP_CORE(x) BPF_CORE_READ((PT_REGS_ARM64 *)(x), pc)

#या_अगर defined(bpf_target_mips)

#घोषणा PT_REGS_PARM1(x) ((x)->regs[4])
#घोषणा PT_REGS_PARM2(x) ((x)->regs[5])
#घोषणा PT_REGS_PARM3(x) ((x)->regs[6])
#घोषणा PT_REGS_PARM4(x) ((x)->regs[7])
#घोषणा PT_REGS_PARM5(x) ((x)->regs[8])
#घोषणा PT_REGS_RET(x) ((x)->regs[31])
#घोषणा PT_REGS_FP(x) ((x)->regs[30]) /* Works only with CONFIG_FRAME_POINTER */
#घोषणा PT_REGS_RC(x) ((x)->regs[2])
#घोषणा PT_REGS_SP(x) ((x)->regs[29])
#घोषणा PT_REGS_IP(x) ((x)->cp0_epc)

#घोषणा PT_REGS_PARM1_CORE(x) BPF_CORE_READ((x), regs[4])
#घोषणा PT_REGS_PARM2_CORE(x) BPF_CORE_READ((x), regs[5])
#घोषणा PT_REGS_PARM3_CORE(x) BPF_CORE_READ((x), regs[6])
#घोषणा PT_REGS_PARM4_CORE(x) BPF_CORE_READ((x), regs[7])
#घोषणा PT_REGS_PARM5_CORE(x) BPF_CORE_READ((x), regs[8])
#घोषणा PT_REGS_RET_CORE(x) BPF_CORE_READ((x), regs[31])
#घोषणा PT_REGS_FP_CORE(x) BPF_CORE_READ((x), regs[30])
#घोषणा PT_REGS_RC_CORE(x) BPF_CORE_READ((x), regs[2])
#घोषणा PT_REGS_SP_CORE(x) BPF_CORE_READ((x), regs[29])
#घोषणा PT_REGS_IP_CORE(x) BPF_CORE_READ((x), cp0_epc)

#या_अगर defined(bpf_target_घातerpc)

#घोषणा PT_REGS_PARM1(x) ((x)->gpr[3])
#घोषणा PT_REGS_PARM2(x) ((x)->gpr[4])
#घोषणा PT_REGS_PARM3(x) ((x)->gpr[5])
#घोषणा PT_REGS_PARM4(x) ((x)->gpr[6])
#घोषणा PT_REGS_PARM5(x) ((x)->gpr[7])
#घोषणा PT_REGS_RC(x) ((x)->gpr[3])
#घोषणा PT_REGS_SP(x) ((x)->sp)
#घोषणा PT_REGS_IP(x) ((x)->nip)

#घोषणा PT_REGS_PARM1_CORE(x) BPF_CORE_READ((x), gpr[3])
#घोषणा PT_REGS_PARM2_CORE(x) BPF_CORE_READ((x), gpr[4])
#घोषणा PT_REGS_PARM3_CORE(x) BPF_CORE_READ((x), gpr[5])
#घोषणा PT_REGS_PARM4_CORE(x) BPF_CORE_READ((x), gpr[6])
#घोषणा PT_REGS_PARM5_CORE(x) BPF_CORE_READ((x), gpr[7])
#घोषणा PT_REGS_RC_CORE(x) BPF_CORE_READ((x), gpr[3])
#घोषणा PT_REGS_SP_CORE(x) BPF_CORE_READ((x), sp)
#घोषणा PT_REGS_IP_CORE(x) BPF_CORE_READ((x), nip)

#या_अगर defined(bpf_target_sparc)

#घोषणा PT_REGS_PARM1(x) ((x)->u_regs[UREG_I0])
#घोषणा PT_REGS_PARM2(x) ((x)->u_regs[UREG_I1])
#घोषणा PT_REGS_PARM3(x) ((x)->u_regs[UREG_I2])
#घोषणा PT_REGS_PARM4(x) ((x)->u_regs[UREG_I3])
#घोषणा PT_REGS_PARM5(x) ((x)->u_regs[UREG_I4])
#घोषणा PT_REGS_RET(x) ((x)->u_regs[UREG_I7])
#घोषणा PT_REGS_RC(x) ((x)->u_regs[UREG_I0])
#घोषणा PT_REGS_SP(x) ((x)->u_regs[UREG_FP])

#घोषणा PT_REGS_PARM1_CORE(x) BPF_CORE_READ((x), u_regs[UREG_I0])
#घोषणा PT_REGS_PARM2_CORE(x) BPF_CORE_READ((x), u_regs[UREG_I1])
#घोषणा PT_REGS_PARM3_CORE(x) BPF_CORE_READ((x), u_regs[UREG_I2])
#घोषणा PT_REGS_PARM4_CORE(x) BPF_CORE_READ((x), u_regs[UREG_I3])
#घोषणा PT_REGS_PARM5_CORE(x) BPF_CORE_READ((x), u_regs[UREG_I4])
#घोषणा PT_REGS_RET_CORE(x) BPF_CORE_READ((x), u_regs[UREG_I7])
#घोषणा PT_REGS_RC_CORE(x) BPF_CORE_READ((x), u_regs[UREG_I0])
#घोषणा PT_REGS_SP_CORE(x) BPF_CORE_READ((x), u_regs[UREG_FP])

/* Should this also be a bpf_target check क्रम the sparc हाल? */
#अगर defined(__arch64__)
#घोषणा PT_REGS_IP(x) ((x)->tpc)
#घोषणा PT_REGS_IP_CORE(x) BPF_CORE_READ((x), tpc)
#अन्यथा
#घोषणा PT_REGS_IP(x) ((x)->pc)
#घोषणा PT_REGS_IP_CORE(x) BPF_CORE_READ((x), pc)
#पूर्ण_अगर

#पूर्ण_अगर

#अगर defined(bpf_target_घातerpc)
#घोषणा BPF_KPROBE_READ_RET_IP(ip, ctx)		(अणु (ip) = (ctx)->link; पूर्ण)
#घोषणा BPF_KRETPROBE_READ_RET_IP		BPF_KPROBE_READ_RET_IP
#या_अगर defined(bpf_target_sparc)
#घोषणा BPF_KPROBE_READ_RET_IP(ip, ctx)		(अणु (ip) = PT_REGS_RET(ctx); पूर्ण)
#घोषणा BPF_KRETPROBE_READ_RET_IP		BPF_KPROBE_READ_RET_IP
#अन्यथा
#घोषणा BPF_KPROBE_READ_RET_IP(ip, ctx)					    \
	(अणु bpf_probe_पढ़ो_kernel(&(ip), माप(ip), (व्योम *)PT_REGS_RET(ctx)); पूर्ण)
#घोषणा BPF_KRETPROBE_READ_RET_IP(ip, ctx)				    \
	(अणु bpf_probe_पढ़ो_kernel(&(ip), माप(ip),			    \
			  (व्योम *)(PT_REGS_FP(ctx) + माप(ip))); पूर्ण)
#पूर्ण_अगर

#घोषणा ___bpf_concat(a, b) a ## b
#घोषणा ___bpf_apply(fn, n) ___bpf_concat(fn, n)
#घोषणा ___bpf_nth(_, _1, _2, _3, _4, _5, _6, _7, _8, _9, _a, _b, _c, N, ...) N
#घोषणा ___bpf_narg(...) \
	___bpf_nth(_, ##__VA_ARGS__, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#घोषणा ___bpf_empty(...) \
	___bpf_nth(_, ##__VA_ARGS__, N, N, N, N, N, N, N, N, N, N, 0)

#घोषणा ___bpf_ctx_cast0() ctx
#घोषणा ___bpf_ctx_cast1(x) ___bpf_ctx_cast0(), (व्योम *)ctx[0]
#घोषणा ___bpf_ctx_cast2(x, args...) ___bpf_ctx_cast1(args), (व्योम *)ctx[1]
#घोषणा ___bpf_ctx_cast3(x, args...) ___bpf_ctx_cast2(args), (व्योम *)ctx[2]
#घोषणा ___bpf_ctx_cast4(x, args...) ___bpf_ctx_cast3(args), (व्योम *)ctx[3]
#घोषणा ___bpf_ctx_cast5(x, args...) ___bpf_ctx_cast4(args), (व्योम *)ctx[4]
#घोषणा ___bpf_ctx_cast6(x, args...) ___bpf_ctx_cast5(args), (व्योम *)ctx[5]
#घोषणा ___bpf_ctx_cast7(x, args...) ___bpf_ctx_cast6(args), (व्योम *)ctx[6]
#घोषणा ___bpf_ctx_cast8(x, args...) ___bpf_ctx_cast7(args), (व्योम *)ctx[7]
#घोषणा ___bpf_ctx_cast9(x, args...) ___bpf_ctx_cast8(args), (व्योम *)ctx[8]
#घोषणा ___bpf_ctx_cast10(x, args...) ___bpf_ctx_cast9(args), (व्योम *)ctx[9]
#घोषणा ___bpf_ctx_cast11(x, args...) ___bpf_ctx_cast10(args), (व्योम *)ctx[10]
#घोषणा ___bpf_ctx_cast12(x, args...) ___bpf_ctx_cast11(args), (व्योम *)ctx[11]
#घोषणा ___bpf_ctx_cast(args...) \
	___bpf_apply(___bpf_ctx_cast, ___bpf_narg(args))(args)

/*
 * BPF_PROG is a convenience wrapper क्रम generic tp_btf/fentry/fनिकास and
 * similar kinds of BPF programs, that accept input arguments as a single
 * poपूर्णांकer to untyped u64 array, where each u64 can actually be a typed
 * poपूर्णांकer or पूर्णांकeger of dअगरferent size. Instead of requring user to ग_लिखो
 * manual casts and work with array elements by index, BPF_PROG macro
 * allows user to declare a list of named and typed input arguments in the
 * same syntax as क्रम normal C function. All the casting is hidden and
 * perक्रमmed transparently, जबतक user code can just assume working with
 * function arguments of specअगरied type and name.
 *
 * Original raw context argument is preserved as well as 'ctx' argument.
 * This is useful when using BPF helpers that expect original context
 * as one of the parameters (e.g., क्रम bpf_perf_event_output()).
 */
#घोषणा BPF_PROG(name, args...)						    \
name(अचिन्हित दीर्घ दीर्घ *ctx);						    \
अटल __attribute__((always_अंतरभूत)) typeof(name(0))			    \
____##name(अचिन्हित दीर्घ दीर्घ *ctx, ##args);				    \
typeof(name(0)) name(अचिन्हित दीर्घ दीर्घ *ctx)				    \
अणु									    \
	_Pragma("GCC diagnostic push")					    \
	_Pragma("GCC diagnostic ignored \"-Wint-conversion\"")		    \
	वापस ____##name(___bpf_ctx_cast(args));			    \
	_Pragma("GCC diagnostic pop")					    \
पूर्ण									    \
अटल __attribute__((always_अंतरभूत)) typeof(name(0))			    \
____##name(अचिन्हित दीर्घ दीर्घ *ctx, ##args)

काष्ठा pt_regs;

#घोषणा ___bpf_kprobe_args0() ctx
#घोषणा ___bpf_kprobe_args1(x) \
	___bpf_kprobe_args0(), (व्योम *)PT_REGS_PARM1(ctx)
#घोषणा ___bpf_kprobe_args2(x, args...) \
	___bpf_kprobe_args1(args), (व्योम *)PT_REGS_PARM2(ctx)
#घोषणा ___bpf_kprobe_args3(x, args...) \
	___bpf_kprobe_args2(args), (व्योम *)PT_REGS_PARM3(ctx)
#घोषणा ___bpf_kprobe_args4(x, args...) \
	___bpf_kprobe_args3(args), (व्योम *)PT_REGS_PARM4(ctx)
#घोषणा ___bpf_kprobe_args5(x, args...) \
	___bpf_kprobe_args4(args), (व्योम *)PT_REGS_PARM5(ctx)
#घोषणा ___bpf_kprobe_args(args...) \
	___bpf_apply(___bpf_kprobe_args, ___bpf_narg(args))(args)

/*
 * BPF_KPROBE serves the same purpose क्रम kprobes as BPF_PROG क्रम
 * tp_btf/fentry/fनिकास BPF programs. It hides the underlying platक्रमm-specअगरic
 * low-level way of getting kprobe input arguments from काष्ठा pt_regs, and
 * provides a familiar typed and named function arguments syntax and
 * semantics of accessing kprobe input paremeters.
 *
 * Original काष्ठा pt_regs* context is preserved as 'ctx' argument. This might
 * be necessary when using BPF helpers like bpf_perf_event_output().
 */
#घोषणा BPF_KPROBE(name, args...)					    \
name(काष्ठा pt_regs *ctx);						    \
अटल __attribute__((always_अंतरभूत)) typeof(name(0))			    \
____##name(काष्ठा pt_regs *ctx, ##args);				    \
typeof(name(0)) name(काष्ठा pt_regs *ctx)				    \
अणु									    \
	_Pragma("GCC diagnostic push")					    \
	_Pragma("GCC diagnostic ignored \"-Wint-conversion\"")		    \
	वापस ____##name(___bpf_kprobe_args(args));			    \
	_Pragma("GCC diagnostic pop")					    \
पूर्ण									    \
अटल __attribute__((always_अंतरभूत)) typeof(name(0))			    \
____##name(काष्ठा pt_regs *ctx, ##args)

#घोषणा ___bpf_kretprobe_args0() ctx
#घोषणा ___bpf_kretprobe_args1(x) \
	___bpf_kretprobe_args0(), (व्योम *)PT_REGS_RC(ctx)
#घोषणा ___bpf_kretprobe_args(args...) \
	___bpf_apply(___bpf_kretprobe_args, ___bpf_narg(args))(args)

/*
 * BPF_KRETPROBE is similar to BPF_KPROBE, except, it only provides optional
 * वापस value (in addition to `काष्ठा pt_regs *ctx`), but no input
 * arguments, because they will be clobbered by the समय probed function
 * वापसs.
 */
#घोषणा BPF_KRETPROBE(name, args...)					    \
name(काष्ठा pt_regs *ctx);						    \
अटल __attribute__((always_अंतरभूत)) typeof(name(0))			    \
____##name(काष्ठा pt_regs *ctx, ##args);				    \
typeof(name(0)) name(काष्ठा pt_regs *ctx)				    \
अणु									    \
	_Pragma("GCC diagnostic push")					    \
	_Pragma("GCC diagnostic ignored \"-Wint-conversion\"")		    \
	वापस ____##name(___bpf_kretprobe_args(args));			    \
	_Pragma("GCC diagnostic pop")					    \
पूर्ण									    \
अटल __always_अंतरभूत typeof(name(0)) ____##name(काष्ठा pt_regs *ctx, ##args)

#घोषणा ___bpf_fill0(arr, p, x) करो अणुपूर्ण जबतक (0)
#घोषणा ___bpf_fill1(arr, p, x) arr[p] = x
#घोषणा ___bpf_fill2(arr, p, x, args...) arr[p] = x; ___bpf_fill1(arr, p + 1, args)
#घोषणा ___bpf_fill3(arr, p, x, args...) arr[p] = x; ___bpf_fill2(arr, p + 1, args)
#घोषणा ___bpf_fill4(arr, p, x, args...) arr[p] = x; ___bpf_fill3(arr, p + 1, args)
#घोषणा ___bpf_fill5(arr, p, x, args...) arr[p] = x; ___bpf_fill4(arr, p + 1, args)
#घोषणा ___bpf_fill6(arr, p, x, args...) arr[p] = x; ___bpf_fill5(arr, p + 1, args)
#घोषणा ___bpf_fill7(arr, p, x, args...) arr[p] = x; ___bpf_fill6(arr, p + 1, args)
#घोषणा ___bpf_fill8(arr, p, x, args...) arr[p] = x; ___bpf_fill7(arr, p + 1, args)
#घोषणा ___bpf_fill9(arr, p, x, args...) arr[p] = x; ___bpf_fill8(arr, p + 1, args)
#घोषणा ___bpf_fill10(arr, p, x, args...) arr[p] = x; ___bpf_fill9(arr, p + 1, args)
#घोषणा ___bpf_fill11(arr, p, x, args...) arr[p] = x; ___bpf_fill10(arr, p + 1, args)
#घोषणा ___bpf_fill12(arr, p, x, args...) arr[p] = x; ___bpf_fill11(arr, p + 1, args)
#घोषणा ___bpf_fill(arr, args...) \
	___bpf_apply(___bpf_fill, ___bpf_narg(args))(arr, 0, args)

/*
 * BPF_SEQ_PRINTF to wrap bpf_seq_म_लिखो to-be-prपूर्णांकed values
 * in a काष्ठाure.
 */
#घोषणा BPF_SEQ_PRINTF(seq, fmt, args...)			\
(अणु								\
	अटल स्थिर अक्षर ___fmt[] = fmt;			\
	अचिन्हित दीर्घ दीर्घ ___param[___bpf_narg(args)];		\
								\
	_Pragma("GCC diagnostic push")				\
	_Pragma("GCC diagnostic ignored \"-Wint-conversion\"")	\
	___bpf_fill(___param, args);				\
	_Pragma("GCC diagnostic pop")				\
								\
	bpf_seq_म_लिखो(seq, ___fmt, माप(___fmt),		\
		       ___param, माप(___param));		\
पूर्ण)

/*
 * BPF_SNPRINTF wraps the bpf_snम_लिखो helper with variadic arguments instead of
 * an array of u64.
 */
#घोषणा BPF_SNPRINTF(out, out_size, fmt, args...)		\
(अणु								\
	अटल स्थिर अक्षर ___fmt[] = fmt;			\
	अचिन्हित दीर्घ दीर्घ ___param[___bpf_narg(args)];		\
								\
	_Pragma("GCC diagnostic push")				\
	_Pragma("GCC diagnostic ignored \"-Wint-conversion\"")	\
	___bpf_fill(___param, args);				\
	_Pragma("GCC diagnostic pop")				\
								\
	bpf_snम_लिखो(out, out_size, ___fmt,			\
		     ___param, माप(___param));		\
पूर्ण)

#पूर्ण_अगर
