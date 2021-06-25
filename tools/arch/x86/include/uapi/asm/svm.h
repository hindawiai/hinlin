<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI__SVM_H
#घोषणा _UAPI__SVM_H

#घोषणा SVM_EXIT_READ_CR0      0x000
#घोषणा SVM_EXIT_READ_CR2      0x002
#घोषणा SVM_EXIT_READ_CR3      0x003
#घोषणा SVM_EXIT_READ_CR4      0x004
#घोषणा SVM_EXIT_READ_CR8      0x008
#घोषणा SVM_EXIT_WRITE_CR0     0x010
#घोषणा SVM_EXIT_WRITE_CR2     0x012
#घोषणा SVM_EXIT_WRITE_CR3     0x013
#घोषणा SVM_EXIT_WRITE_CR4     0x014
#घोषणा SVM_EXIT_WRITE_CR8     0x018
#घोषणा SVM_EXIT_READ_DR0      0x020
#घोषणा SVM_EXIT_READ_DR1      0x021
#घोषणा SVM_EXIT_READ_DR2      0x022
#घोषणा SVM_EXIT_READ_DR3      0x023
#घोषणा SVM_EXIT_READ_DR4      0x024
#घोषणा SVM_EXIT_READ_DR5      0x025
#घोषणा SVM_EXIT_READ_DR6      0x026
#घोषणा SVM_EXIT_READ_DR7      0x027
#घोषणा SVM_EXIT_WRITE_DR0     0x030
#घोषणा SVM_EXIT_WRITE_DR1     0x031
#घोषणा SVM_EXIT_WRITE_DR2     0x032
#घोषणा SVM_EXIT_WRITE_DR3     0x033
#घोषणा SVM_EXIT_WRITE_DR4     0x034
#घोषणा SVM_EXIT_WRITE_DR5     0x035
#घोषणा SVM_EXIT_WRITE_DR6     0x036
#घोषणा SVM_EXIT_WRITE_DR7     0x037
#घोषणा SVM_EXIT_EXCP_BASE     0x040
#घोषणा SVM_EXIT_LAST_EXCP     0x05f
#घोषणा SVM_EXIT_INTR          0x060
#घोषणा SVM_EXIT_NMI           0x061
#घोषणा SVM_EXIT_SMI           0x062
#घोषणा SVM_EXIT_INIT          0x063
#घोषणा SVM_EXIT_VINTR         0x064
#घोषणा SVM_EXIT_CR0_SEL_WRITE 0x065
#घोषणा SVM_EXIT_IDTR_READ     0x066
#घोषणा SVM_EXIT_GDTR_READ     0x067
#घोषणा SVM_EXIT_LDTR_READ     0x068
#घोषणा SVM_EXIT_TR_READ       0x069
#घोषणा SVM_EXIT_IDTR_WRITE    0x06a
#घोषणा SVM_EXIT_GDTR_WRITE    0x06b
#घोषणा SVM_EXIT_LDTR_WRITE    0x06c
#घोषणा SVM_EXIT_TR_WRITE      0x06d
#घोषणा SVM_EXIT_RDTSC         0x06e
#घोषणा SVM_EXIT_RDPMC         0x06f
#घोषणा SVM_EXIT_PUSHF         0x070
#घोषणा SVM_EXIT_POPF          0x071
#घोषणा SVM_EXIT_CPUID         0x072
#घोषणा SVM_EXIT_RSM           0x073
#घोषणा SVM_EXIT_IRET          0x074
#घोषणा SVM_EXIT_SWINT         0x075
#घोषणा SVM_EXIT_INVD          0x076
#घोषणा SVM_EXIT_PAUSE         0x077
#घोषणा SVM_EXIT_HLT           0x078
#घोषणा SVM_EXIT_INVLPG        0x079
#घोषणा SVM_EXIT_INVLPGA       0x07a
#घोषणा SVM_EXIT_IOIO          0x07b
#घोषणा SVM_EXIT_MSR           0x07c
#घोषणा SVM_EXIT_TASK_SWITCH   0x07d
#घोषणा SVM_EXIT_FERR_FREEZE   0x07e
#घोषणा SVM_EXIT_SHUTDOWN      0x07f
#घोषणा SVM_EXIT_VMRUN         0x080
#घोषणा SVM_EXIT_VMMCALL       0x081
#घोषणा SVM_EXIT_VMLOAD        0x082
#घोषणा SVM_EXIT_VMSAVE        0x083
#घोषणा SVM_EXIT_STGI          0x084
#घोषणा SVM_EXIT_CLGI          0x085
#घोषणा SVM_EXIT_SKINIT        0x086
#घोषणा SVM_EXIT_RDTSCP        0x087
#घोषणा SVM_EXIT_ICEBP         0x088
#घोषणा SVM_EXIT_WBINVD        0x089
#घोषणा SVM_EXIT_MONITOR       0x08a
#घोषणा SVM_EXIT_MWAIT         0x08b
#घोषणा SVM_EXIT_MWAIT_COND    0x08c
#घोषणा SVM_EXIT_XSETBV        0x08d
#घोषणा SVM_EXIT_RDPRU         0x08e
#घोषणा SVM_EXIT_EFER_WRITE_TRAP		0x08f
#घोषणा SVM_EXIT_CR0_WRITE_TRAP			0x090
#घोषणा SVM_EXIT_CR1_WRITE_TRAP			0x091
#घोषणा SVM_EXIT_CR2_WRITE_TRAP			0x092
#घोषणा SVM_EXIT_CR3_WRITE_TRAP			0x093
#घोषणा SVM_EXIT_CR4_WRITE_TRAP			0x094
#घोषणा SVM_EXIT_CR5_WRITE_TRAP			0x095
#घोषणा SVM_EXIT_CR6_WRITE_TRAP			0x096
#घोषणा SVM_EXIT_CR7_WRITE_TRAP			0x097
#घोषणा SVM_EXIT_CR8_WRITE_TRAP			0x098
#घोषणा SVM_EXIT_CR9_WRITE_TRAP			0x099
#घोषणा SVM_EXIT_CR10_WRITE_TRAP		0x09a
#घोषणा SVM_EXIT_CR11_WRITE_TRAP		0x09b
#घोषणा SVM_EXIT_CR12_WRITE_TRAP		0x09c
#घोषणा SVM_EXIT_CR13_WRITE_TRAP		0x09d
#घोषणा SVM_EXIT_CR14_WRITE_TRAP		0x09e
#घोषणा SVM_EXIT_CR15_WRITE_TRAP		0x09f
#घोषणा SVM_EXIT_INVPCID       0x0a2
#घोषणा SVM_EXIT_NPF           0x400
#घोषणा SVM_EXIT_AVIC_INCOMPLETE_IPI		0x401
#घोषणा SVM_EXIT_AVIC_UNACCELERATED_ACCESS	0x402
#घोषणा SVM_EXIT_VMGEXIT       0x403

/* SEV-ES software-defined VMGEXIT events */
#घोषणा SVM_VMGEXIT_MMIO_READ			0x80000001
#घोषणा SVM_VMGEXIT_MMIO_WRITE			0x80000002
#घोषणा SVM_VMGEXIT_NMI_COMPLETE		0x80000003
#घोषणा SVM_VMGEXIT_AP_HLT_LOOP			0x80000004
#घोषणा SVM_VMGEXIT_AP_JUMP_TABLE		0x80000005
#घोषणा SVM_VMGEXIT_SET_AP_JUMP_TABLE		0
#घोषणा SVM_VMGEXIT_GET_AP_JUMP_TABLE		1
#घोषणा SVM_VMGEXIT_UNSUPPORTED_EVENT		0x8000ffff

#घोषणा SVM_EXIT_ERR           -1

#घोषणा SVM_EXIT_REASONS \
	अणु SVM_EXIT_READ_CR0,    "read_cr0" पूर्ण, \
	अणु SVM_EXIT_READ_CR2,    "read_cr2" पूर्ण, \
	अणु SVM_EXIT_READ_CR3,    "read_cr3" पूर्ण, \
	अणु SVM_EXIT_READ_CR4,    "read_cr4" पूर्ण, \
	अणु SVM_EXIT_READ_CR8,    "read_cr8" पूर्ण, \
	अणु SVM_EXIT_WRITE_CR0,   "write_cr0" पूर्ण, \
	अणु SVM_EXIT_WRITE_CR2,   "write_cr2" पूर्ण, \
	अणु SVM_EXIT_WRITE_CR3,   "write_cr3" पूर्ण, \
	अणु SVM_EXIT_WRITE_CR4,   "write_cr4" पूर्ण, \
	अणु SVM_EXIT_WRITE_CR8,   "write_cr8" पूर्ण, \
	अणु SVM_EXIT_READ_DR0,    "read_dr0" पूर्ण, \
	अणु SVM_EXIT_READ_DR1,    "read_dr1" पूर्ण, \
	अणु SVM_EXIT_READ_DR2,    "read_dr2" पूर्ण, \
	अणु SVM_EXIT_READ_DR3,    "read_dr3" पूर्ण, \
	अणु SVM_EXIT_READ_DR4,    "read_dr4" पूर्ण, \
	अणु SVM_EXIT_READ_DR5,    "read_dr5" पूर्ण, \
	अणु SVM_EXIT_READ_DR6,    "read_dr6" पूर्ण, \
	अणु SVM_EXIT_READ_DR7,    "read_dr7" पूर्ण, \
	अणु SVM_EXIT_WRITE_DR0,   "write_dr0" पूर्ण, \
	अणु SVM_EXIT_WRITE_DR1,   "write_dr1" पूर्ण, \
	अणु SVM_EXIT_WRITE_DR2,   "write_dr2" पूर्ण, \
	अणु SVM_EXIT_WRITE_DR3,   "write_dr3" पूर्ण, \
	अणु SVM_EXIT_WRITE_DR4,   "write_dr4" पूर्ण, \
	अणु SVM_EXIT_WRITE_DR5,   "write_dr5" पूर्ण, \
	अणु SVM_EXIT_WRITE_DR6,   "write_dr6" पूर्ण, \
	अणु SVM_EXIT_WRITE_DR7,   "write_dr7" पूर्ण, \
	अणु SVM_EXIT_EXCP_BASE + DE_VECTOR,       "DE excp" पूर्ण, \
	अणु SVM_EXIT_EXCP_BASE + DB_VECTOR,       "DB excp" पूर्ण, \
	अणु SVM_EXIT_EXCP_BASE + BP_VECTOR,       "BP excp" पूर्ण, \
	अणु SVM_EXIT_EXCP_BASE + OF_VECTOR,       "OF excp" पूर्ण, \
	अणु SVM_EXIT_EXCP_BASE + BR_VECTOR,       "BR excp" पूर्ण, \
	अणु SVM_EXIT_EXCP_BASE + UD_VECTOR,       "UD excp" पूर्ण, \
	अणु SVM_EXIT_EXCP_BASE + NM_VECTOR,       "NM excp" पूर्ण, \
	अणु SVM_EXIT_EXCP_BASE + DF_VECTOR,       "DF excp" पूर्ण, \
	अणु SVM_EXIT_EXCP_BASE + TS_VECTOR,       "TS excp" पूर्ण, \
	अणु SVM_EXIT_EXCP_BASE + NP_VECTOR,       "NP excp" पूर्ण, \
	अणु SVM_EXIT_EXCP_BASE + SS_VECTOR,       "SS excp" पूर्ण, \
	अणु SVM_EXIT_EXCP_BASE + GP_VECTOR,       "GP excp" पूर्ण, \
	अणु SVM_EXIT_EXCP_BASE + PF_VECTOR,       "PF excp" पूर्ण, \
	अणु SVM_EXIT_EXCP_BASE + MF_VECTOR,       "MF excp" पूर्ण, \
	अणु SVM_EXIT_EXCP_BASE + AC_VECTOR,       "AC excp" पूर्ण, \
	अणु SVM_EXIT_EXCP_BASE + MC_VECTOR,       "MC excp" पूर्ण, \
	अणु SVM_EXIT_EXCP_BASE + XM_VECTOR,       "XF excp" पूर्ण, \
	अणु SVM_EXIT_INTR,        "interrupt" पूर्ण, \
	अणु SVM_EXIT_NMI,         "nmi" पूर्ण, \
	अणु SVM_EXIT_SMI,         "smi" पूर्ण, \
	अणु SVM_EXIT_INIT,        "init" पूर्ण, \
	अणु SVM_EXIT_VINTR,       "vintr" पूर्ण, \
	अणु SVM_EXIT_CR0_SEL_WRITE, "cr0_sel_write" पूर्ण, \
	अणु SVM_EXIT_IDTR_READ,   "read_idtr" पूर्ण, \
	अणु SVM_EXIT_GDTR_READ,   "read_gdtr" पूर्ण, \
	अणु SVM_EXIT_LDTR_READ,   "read_ldtr" पूर्ण, \
	अणु SVM_EXIT_TR_READ,     "read_rt" पूर्ण, \
	अणु SVM_EXIT_IDTR_WRITE,  "write_idtr" पूर्ण, \
	अणु SVM_EXIT_GDTR_WRITE,  "write_gdtr" पूर्ण, \
	अणु SVM_EXIT_LDTR_WRITE,  "write_ldtr" पूर्ण, \
	अणु SVM_EXIT_TR_WRITE,    "write_rt" पूर्ण, \
	अणु SVM_EXIT_RDTSC,       "rdtsc" पूर्ण, \
	अणु SVM_EXIT_RDPMC,       "rdpmc" पूर्ण, \
	अणु SVM_EXIT_PUSHF,       "pushf" पूर्ण, \
	अणु SVM_EXIT_POPF,        "popf" पूर्ण, \
	अणु SVM_EXIT_CPUID,       "cpuid" पूर्ण, \
	अणु SVM_EXIT_RSM,         "rsm" पूर्ण, \
	अणु SVM_EXIT_IRET,        "iret" पूर्ण, \
	अणु SVM_EXIT_SWINT,       "swint" पूर्ण, \
	अणु SVM_EXIT_INVD,        "invd" पूर्ण, \
	अणु SVM_EXIT_PAUSE,       "pause" पूर्ण, \
	अणु SVM_EXIT_HLT,         "hlt" पूर्ण, \
	अणु SVM_EXIT_INVLPG,      "invlpg" पूर्ण, \
	अणु SVM_EXIT_INVLPGA,     "invlpga" पूर्ण, \
	अणु SVM_EXIT_IOIO,        "io" पूर्ण, \
	अणु SVM_EXIT_MSR,         "msr" पूर्ण, \
	अणु SVM_EXIT_TASK_SWITCH, "task_switch" पूर्ण, \
	अणु SVM_EXIT_FERR_FREEZE, "ferr_freeze" पूर्ण, \
	अणु SVM_EXIT_SHUTDOWN,    "shutdown" पूर्ण, \
	अणु SVM_EXIT_VMRUN,       "vmrun" पूर्ण, \
	अणु SVM_EXIT_VMMCALL,     "hypercall" पूर्ण, \
	अणु SVM_EXIT_VMLOAD,      "vmload" पूर्ण, \
	अणु SVM_EXIT_VMSAVE,      "vmsave" पूर्ण, \
	अणु SVM_EXIT_STGI,        "stgi" पूर्ण, \
	अणु SVM_EXIT_CLGI,        "clgi" पूर्ण, \
	अणु SVM_EXIT_SKINIT,      "skinit" पूर्ण, \
	अणु SVM_EXIT_RDTSCP,      "rdtscp" पूर्ण, \
	अणु SVM_EXIT_ICEBP,       "icebp" पूर्ण, \
	अणु SVM_EXIT_WBINVD,      "wbinvd" पूर्ण, \
	अणु SVM_EXIT_MONITOR,     "monitor" पूर्ण, \
	अणु SVM_EXIT_MWAIT,       "mwait" पूर्ण, \
	अणु SVM_EXIT_XSETBV,      "xsetbv" पूर्ण, \
	अणु SVM_EXIT_EFER_WRITE_TRAP,	"write_efer_trap" पूर्ण, \
	अणु SVM_EXIT_CR0_WRITE_TRAP,	"write_cr0_trap" पूर्ण, \
	अणु SVM_EXIT_CR4_WRITE_TRAP,	"write_cr4_trap" पूर्ण, \
	अणु SVM_EXIT_CR8_WRITE_TRAP,	"write_cr8_trap" पूर्ण, \
	अणु SVM_EXIT_INVPCID,     "invpcid" पूर्ण, \
	अणु SVM_EXIT_NPF,         "npf" पूर्ण, \
	अणु SVM_EXIT_AVIC_INCOMPLETE_IPI,		"avic_incomplete_ipi" पूर्ण, \
	अणु SVM_EXIT_AVIC_UNACCELERATED_ACCESS,   "avic_unaccelerated_access" पूर्ण, \
	अणु SVM_EXIT_VMGEXIT,		"vmgexit" पूर्ण, \
	अणु SVM_VMGEXIT_MMIO_READ,	"vmgexit_mmio_read" पूर्ण, \
	अणु SVM_VMGEXIT_MMIO_WRITE,	"vmgexit_mmio_write" पूर्ण, \
	अणु SVM_VMGEXIT_NMI_COMPLETE,	"vmgexit_nmi_complete" पूर्ण, \
	अणु SVM_VMGEXIT_AP_HLT_LOOP,	"vmgexit_ap_hlt_loop" पूर्ण, \
	अणु SVM_VMGEXIT_AP_JUMP_TABLE,	"vmgexit_ap_jump_table" पूर्ण, \
	अणु SVM_EXIT_ERR,         "invalid_guest_state" पूर्ण


#पूर्ण_अगर /* _UAPI__SVM_H */
