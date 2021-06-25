<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * vmx.h: VMX Architecture related definitions
 * Copyright (c) 2004, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 *
 * You should have received a copy of the GNU General Public License aदीर्घ with
 * this program; अगर not, ग_लिखो to the Free Software Foundation, Inc., 59 Temple
 * Place - Suite 330, Boston, MA 02111-1307 USA.
 *
 * A few अक्रमom additions are:
 * Copyright (C) 2006 Qumranet
 *    Avi Kivity <avi@qumranet.com>
 *    Yaniv Kamay <yaniv@qumranet.com>
 *
 */
#अगर_अघोषित _UAPIVMX_H
#घोषणा _UAPIVMX_H


#घोषणा VMX_EXIT_REASONS_FAILED_VMENTRY         0x80000000
#घोषणा VMX_EXIT_REASONS_SGX_ENCLAVE_MODE	0x08000000

#घोषणा EXIT_REASON_EXCEPTION_NMI       0
#घोषणा EXIT_REASON_EXTERNAL_INTERRUPT  1
#घोषणा EXIT_REASON_TRIPLE_FAULT        2
#घोषणा EXIT_REASON_INIT_SIGNAL			3
#घोषणा EXIT_REASON_SIPI_SIGNAL         4

#घोषणा EXIT_REASON_INTERRUPT_WINDOW    7
#घोषणा EXIT_REASON_NMI_WINDOW          8
#घोषणा EXIT_REASON_TASK_SWITCH         9
#घोषणा EXIT_REASON_CPUID               10
#घोषणा EXIT_REASON_HLT                 12
#घोषणा EXIT_REASON_INVD                13
#घोषणा EXIT_REASON_INVLPG              14
#घोषणा EXIT_REASON_RDPMC               15
#घोषणा EXIT_REASON_RDTSC               16
#घोषणा EXIT_REASON_VMCALL              18
#घोषणा EXIT_REASON_VMCLEAR             19
#घोषणा EXIT_REASON_VMLAUNCH            20
#घोषणा EXIT_REASON_VMPTRLD             21
#घोषणा EXIT_REASON_VMPTRST             22
#घोषणा EXIT_REASON_VMREAD              23
#घोषणा EXIT_REASON_VMRESUME            24
#घोषणा EXIT_REASON_VMWRITE             25
#घोषणा EXIT_REASON_VMOFF               26
#घोषणा EXIT_REASON_VMON                27
#घोषणा EXIT_REASON_CR_ACCESS           28
#घोषणा EXIT_REASON_DR_ACCESS           29
#घोषणा EXIT_REASON_IO_INSTRUCTION      30
#घोषणा EXIT_REASON_MSR_READ            31
#घोषणा EXIT_REASON_MSR_WRITE           32
#घोषणा EXIT_REASON_INVALID_STATE       33
#घोषणा EXIT_REASON_MSR_LOAD_FAIL       34
#घोषणा EXIT_REASON_MWAIT_INSTRUCTION   36
#घोषणा EXIT_REASON_MONITOR_TRAP_FLAG   37
#घोषणा EXIT_REASON_MONITOR_INSTRUCTION 39
#घोषणा EXIT_REASON_PAUSE_INSTRUCTION   40
#घोषणा EXIT_REASON_MCE_DURING_VMENTRY  41
#घोषणा EXIT_REASON_TPR_BELOW_THRESHOLD 43
#घोषणा EXIT_REASON_APIC_ACCESS         44
#घोषणा EXIT_REASON_EOI_INDUCED         45
#घोषणा EXIT_REASON_GDTR_IDTR           46
#घोषणा EXIT_REASON_LDTR_TR             47
#घोषणा EXIT_REASON_EPT_VIOLATION       48
#घोषणा EXIT_REASON_EPT_MISCONFIG       49
#घोषणा EXIT_REASON_INVEPT              50
#घोषणा EXIT_REASON_RDTSCP              51
#घोषणा EXIT_REASON_PREEMPTION_TIMER    52
#घोषणा EXIT_REASON_INVVPID             53
#घोषणा EXIT_REASON_WBINVD              54
#घोषणा EXIT_REASON_XSETBV              55
#घोषणा EXIT_REASON_APIC_WRITE          56
#घोषणा EXIT_REASON_RDRAND              57
#घोषणा EXIT_REASON_INVPCID             58
#घोषणा EXIT_REASON_VMFUNC              59
#घोषणा EXIT_REASON_ENCLS               60
#घोषणा EXIT_REASON_RDSEED              61
#घोषणा EXIT_REASON_PML_FULL            62
#घोषणा EXIT_REASON_XSAVES              63
#घोषणा EXIT_REASON_XRSTORS             64
#घोषणा EXIT_REASON_UMWAIT              67
#घोषणा EXIT_REASON_TPAUSE              68
#घोषणा EXIT_REASON_BUS_LOCK            74

#घोषणा VMX_EXIT_REASONS \
	अणु EXIT_REASON_EXCEPTION_NMI,         "EXCEPTION_NMI" पूर्ण, \
	अणु EXIT_REASON_EXTERNAL_INTERRUPT,    "EXTERNAL_INTERRUPT" पूर्ण, \
	अणु EXIT_REASON_TRIPLE_FAULT,          "TRIPLE_FAULT" पूर्ण, \
	अणु EXIT_REASON_INIT_SIGNAL,           "INIT_SIGNAL" पूर्ण, \
	अणु EXIT_REASON_SIPI_SIGNAL,           "SIPI_SIGNAL" पूर्ण, \
	अणु EXIT_REASON_INTERRUPT_WINDOW,      "INTERRUPT_WINDOW" पूर्ण, \
	अणु EXIT_REASON_NMI_WINDOW,            "NMI_WINDOW" पूर्ण, \
	अणु EXIT_REASON_TASK_SWITCH,           "TASK_SWITCH" पूर्ण, \
	अणु EXIT_REASON_CPUID,                 "CPUID" पूर्ण, \
	अणु EXIT_REASON_HLT,                   "HLT" पूर्ण, \
	अणु EXIT_REASON_INVD,                  "INVD" पूर्ण, \
	अणु EXIT_REASON_INVLPG,                "INVLPG" पूर्ण, \
	अणु EXIT_REASON_RDPMC,                 "RDPMC" पूर्ण, \
	अणु EXIT_REASON_RDTSC,                 "RDTSC" पूर्ण, \
	अणु EXIT_REASON_VMCALL,                "VMCALL" पूर्ण, \
	अणु EXIT_REASON_VMCLEAR,               "VMCLEAR" पूर्ण, \
	अणु EXIT_REASON_VMLAUNCH,              "VMLAUNCH" पूर्ण, \
	अणु EXIT_REASON_VMPTRLD,               "VMPTRLD" पूर्ण, \
	अणु EXIT_REASON_VMPTRST,               "VMPTRST" पूर्ण, \
	अणु EXIT_REASON_VMREAD,                "VMREAD" पूर्ण, \
	अणु EXIT_REASON_VMRESUME,              "VMRESUME" पूर्ण, \
	अणु EXIT_REASON_VMWRITE,               "VMWRITE" पूर्ण, \
	अणु EXIT_REASON_VMOFF,                 "VMOFF" पूर्ण, \
	अणु EXIT_REASON_VMON,                  "VMON" पूर्ण, \
	अणु EXIT_REASON_CR_ACCESS,             "CR_ACCESS" पूर्ण, \
	अणु EXIT_REASON_DR_ACCESS,             "DR_ACCESS" पूर्ण, \
	अणु EXIT_REASON_IO_INSTRUCTION,        "IO_INSTRUCTION" पूर्ण, \
	अणु EXIT_REASON_MSR_READ,              "MSR_READ" पूर्ण, \
	अणु EXIT_REASON_MSR_WRITE,             "MSR_WRITE" पूर्ण, \
	अणु EXIT_REASON_INVALID_STATE,         "INVALID_STATE" पूर्ण, \
	अणु EXIT_REASON_MSR_LOAD_FAIL,         "MSR_LOAD_FAIL" पूर्ण, \
	अणु EXIT_REASON_MWAIT_INSTRUCTION,     "MWAIT_INSTRUCTION" पूर्ण, \
	अणु EXIT_REASON_MONITOR_TRAP_FLAG,     "MONITOR_TRAP_FLAG" पूर्ण, \
	अणु EXIT_REASON_MONITOR_INSTRUCTION,   "MONITOR_INSTRUCTION" पूर्ण, \
	अणु EXIT_REASON_PAUSE_INSTRUCTION,     "PAUSE_INSTRUCTION" पूर्ण, \
	अणु EXIT_REASON_MCE_DURING_VMENTRY,    "MCE_DURING_VMENTRY" पूर्ण, \
	अणु EXIT_REASON_TPR_BELOW_THRESHOLD,   "TPR_BELOW_THRESHOLD" पूर्ण, \
	अणु EXIT_REASON_APIC_ACCESS,           "APIC_ACCESS" पूर्ण, \
	अणु EXIT_REASON_EOI_INDUCED,           "EOI_INDUCED" पूर्ण, \
	अणु EXIT_REASON_GDTR_IDTR,             "GDTR_IDTR" पूर्ण, \
	अणु EXIT_REASON_LDTR_TR,               "LDTR_TR" पूर्ण, \
	अणु EXIT_REASON_EPT_VIOLATION,         "EPT_VIOLATION" पूर्ण, \
	अणु EXIT_REASON_EPT_MISCONFIG,         "EPT_MISCONFIG" पूर्ण, \
	अणु EXIT_REASON_INVEPT,                "INVEPT" पूर्ण, \
	अणु EXIT_REASON_RDTSCP,                "RDTSCP" पूर्ण, \
	अणु EXIT_REASON_PREEMPTION_TIMER,      "PREEMPTION_TIMER" पूर्ण, \
	अणु EXIT_REASON_INVVPID,               "INVVPID" पूर्ण, \
	अणु EXIT_REASON_WBINVD,                "WBINVD" पूर्ण, \
	अणु EXIT_REASON_XSETBV,                "XSETBV" पूर्ण, \
	अणु EXIT_REASON_APIC_WRITE,            "APIC_WRITE" पूर्ण, \
	अणु EXIT_REASON_RDRAND,                "RDRAND" पूर्ण, \
	अणु EXIT_REASON_INVPCID,               "INVPCID" पूर्ण, \
	अणु EXIT_REASON_VMFUNC,                "VMFUNC" पूर्ण, \
	अणु EXIT_REASON_ENCLS,                 "ENCLS" पूर्ण, \
	अणु EXIT_REASON_RDSEED,                "RDSEED" पूर्ण, \
	अणु EXIT_REASON_PML_FULL,              "PML_FULL" पूर्ण, \
	अणु EXIT_REASON_XSAVES,                "XSAVES" पूर्ण, \
	अणु EXIT_REASON_XRSTORS,               "XRSTORS" पूर्ण, \
	अणु EXIT_REASON_UMWAIT,                "UMWAIT" पूर्ण, \
	अणु EXIT_REASON_TPAUSE,                "TPAUSE" पूर्ण, \
	अणु EXIT_REASON_BUS_LOCK,              "BUS_LOCK" पूर्ण

#घोषणा VMX_EXIT_REASON_FLAGS \
	अणु VMX_EXIT_REASONS_FAILED_VMENTRY,	"FAILED_VMENTRY" पूर्ण

#घोषणा VMX_ABORT_SAVE_GUEST_MSR_FAIL        1
#घोषणा VMX_ABORT_LOAD_HOST_PDPTE_FAIL       2
#घोषणा VMX_ABORT_LOAD_HOST_MSR_FAIL         4

#पूर्ण_अगर /* _UAPIVMX_H */
