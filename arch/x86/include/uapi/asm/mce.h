<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_ASM_X86_MCE_H
#घोषणा _UAPI_ASM_X86_MCE_H

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

/*
 * Fields are zero when not available. Also, this काष्ठा is shared with
 * userspace mcelog and thus must keep existing fields at current offsets.
 * Only add new fields to the end of the काष्ठाure
 */
काष्ठा mce अणु
	__u64 status;		/* Bank's MCi_STATUS MSR */
	__u64 misc;		/* Bank's MCi_MISC MSR */
	__u64 addr;		/* Bank's MCi_ADDR MSR */
	__u64 mcgstatus;	/* Machine Check Global Status MSR */
	__u64 ip;		/* Inकाष्ठाion Poपूर्णांकer when the error happened */
	__u64 tsc;		/* CPU समय stamp counter */
	__u64 समय;		/* Wall समय_प्रकार when error was detected */
	__u8  cpuvenकरोr;	/* Kernel's X86_VENDOR क्रमागत */
	__u8  inject_flags;	/* Software inject flags */
	__u8  severity;		/* Error severity */
	__u8  pad;
	__u32 cpuid;		/* CPUID 1 EAX */
	__u8  cs;		/* Code segment */
	__u8  bank;		/* Machine check bank reporting the error */
	__u8  cpu;		/* CPU number; obsoleted by extcpu */
	__u8  finished;		/* Entry is valid */
	__u32 extcpu;		/* Linux CPU number that detected the error */
	__u32 socketid;		/* CPU socket ID */
	__u32 apicid;		/* CPU initial APIC ID */
	__u64 mcgcap;		/* MCGCAP MSR: machine check capabilities of CPU */
	__u64 synd;		/* MCA_SYND MSR: only valid on SMCA प्रणालीs */
	__u64 ipid;		/* MCA_IPID MSR: only valid on SMCA प्रणालीs */
	__u64 ppin;		/* Protected Processor Inventory Number */
	__u32 microcode;	/* Microcode revision */
	__u64 kflags;		/* Internal kernel use */
पूर्ण;

#घोषणा MCE_GET_RECORD_LEN   _IOR('M', 1, पूर्णांक)
#घोषणा MCE_GET_LOG_LEN      _IOR('M', 2, पूर्णांक)
#घोषणा MCE_GETCLEAR_FLAGS   _IOR('M', 3, पूर्णांक)

#पूर्ण_अगर /* _UAPI_ASM_X86_MCE_H */
