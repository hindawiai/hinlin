<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * definition क्रम kernel भव machines on s390
 *
 * Copyright IBM Corp. 2008, 2018
 *
 *    Author(s): Carsten Otte <cotte@de.ibm.com>
 */


#अगर_अघोषित ASM_KVM_HOST_H
#घोषणा ASM_KVM_HOST_H

#समावेश <linux/types.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kvm_types.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/kvm.h>
#समावेश <linux/seqlock.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/fpu/api.h>
#समावेश <यंत्र/isc.h>
#समावेश <यंत्र/guarded_storage.h>

#घोषणा KVM_S390_BSCA_CPU_SLOTS 64
#घोषणा KVM_S390_ESCA_CPU_SLOTS 248
#घोषणा KVM_MAX_VCPUS 255

/*
 * These seem to be used क्रम allocating ->chip in the routing table, which we
 * करोn't use. 1 is as small as we can get to reduce the needed memory. If we
 * need to look at ->chip later on, we'll need to revisit this.
 */
#घोषणा KVM_NR_IRQCHIPS 1
#घोषणा KVM_IRQCHIP_NUM_PINS 1
#घोषणा KVM_HALT_POLL_NS_DEFAULT 50000

/* s390-specअगरic vcpu->requests bit members */
#घोषणा KVM_REQ_ENABLE_IBS	KVM_ARCH_REQ(0)
#घोषणा KVM_REQ_DISABLE_IBS	KVM_ARCH_REQ(1)
#घोषणा KVM_REQ_ICPT_OPEREXC	KVM_ARCH_REQ(2)
#घोषणा KVM_REQ_START_MIGRATION KVM_ARCH_REQ(3)
#घोषणा KVM_REQ_STOP_MIGRATION  KVM_ARCH_REQ(4)
#घोषणा KVM_REQ_VSIE_RESTART	KVM_ARCH_REQ(5)

#घोषणा SIGP_CTRL_C		0x80
#घोषणा SIGP_CTRL_SCN_MASK	0x3f

जोड़ bsca_sigp_ctrl अणु
	__u8 value;
	काष्ठा अणु
		__u8 c : 1;
		__u8 r : 1;
		__u8 scn : 6;
	पूर्ण;
पूर्ण;

जोड़ esca_sigp_ctrl अणु
	__u16 value;
	काष्ठा अणु
		__u8 c : 1;
		__u8 reserved: 7;
		__u8 scn;
	पूर्ण;
पूर्ण;

काष्ठा esca_entry अणु
	जोड़ esca_sigp_ctrl sigp_ctrl;
	__u16   reserved1[3];
	__u64   sda;
	__u64   reserved2[6];
पूर्ण;

काष्ठा bsca_entry अणु
	__u8	reserved0;
	जोड़ bsca_sigp_ctrl	sigp_ctrl;
	__u16	reserved[3];
	__u64	sda;
	__u64	reserved2[2];
पूर्ण;

जोड़ ipte_control अणु
	अचिन्हित दीर्घ val;
	काष्ठा अणु
		अचिन्हित दीर्घ k  : 1;
		अचिन्हित दीर्घ kh : 31;
		अचिन्हित दीर्घ kg : 32;
	पूर्ण;
पूर्ण;

काष्ठा bsca_block अणु
	जोड़ ipte_control ipte_control;
	__u64	reserved[5];
	__u64	mcn;
	__u64	reserved2;
	काष्ठा bsca_entry cpu[KVM_S390_BSCA_CPU_SLOTS];
पूर्ण;

काष्ठा esca_block अणु
	जोड़ ipte_control ipte_control;
	__u64   reserved1[7];
	__u64   mcn[4];
	__u64   reserved2[20];
	काष्ठा esca_entry cpu[KVM_S390_ESCA_CPU_SLOTS];
पूर्ण;

/*
 * This काष्ठा is used to store some machine check info from lowcore
 * क्रम machine checks that happen जबतक the guest is running.
 * This info in host's lowcore might be overwritten by a second machine
 * check from host when host is in the machine check's high-level handling.
 * The size is 24 bytes.
 */
काष्ठा mcck_अस्थिर_info अणु
	__u64 mcic;
	__u64 failing_storage_address;
	__u32 ext_damage_code;
	__u32 reserved;
पूर्ण;

#घोषणा CR0_INITIAL_MASK (CR0_UNUSED_56 | CR0_INTERRUPT_KEY_SUBMASK | \
			  CR0_MEASUREMENT_ALERT_SUBMASK)
#घोषणा CR14_INITIAL_MASK (CR14_UNUSED_32 | CR14_UNUSED_33 | \
			   CR14_EXTERNAL_DAMAGE_SUBMASK)

#घोषणा SIDAD_SIZE_MASK		0xff
#घोषणा sida_origin(sie_block) \
	((sie_block)->sidad & PAGE_MASK)
#घोषणा sida_size(sie_block) \
	((((sie_block)->sidad & SIDAD_SIZE_MASK) + 1) * PAGE_SIZE)

#घोषणा CPUSTAT_STOPPED    0x80000000
#घोषणा CPUSTAT_WAIT       0x10000000
#घोषणा CPUSTAT_ECALL_PEND 0x08000000
#घोषणा CPUSTAT_STOP_INT   0x04000000
#घोषणा CPUSTAT_IO_INT     0x02000000
#घोषणा CPUSTAT_EXT_INT    0x01000000
#घोषणा CPUSTAT_RUNNING    0x00800000
#घोषणा CPUSTAT_RETAINED   0x00400000
#घोषणा CPUSTAT_TIMING_SUB 0x00020000
#घोषणा CPUSTAT_SIE_SUB    0x00010000
#घोषणा CPUSTAT_RRF        0x00008000
#घोषणा CPUSTAT_SLSV       0x00004000
#घोषणा CPUSTAT_SLSR       0x00002000
#घोषणा CPUSTAT_ZARCH      0x00000800
#घोषणा CPUSTAT_MCDS       0x00000100
#घोषणा CPUSTAT_KSS        0x00000200
#घोषणा CPUSTAT_SM         0x00000080
#घोषणा CPUSTAT_IBS        0x00000040
#घोषणा CPUSTAT_GED2       0x00000010
#घोषणा CPUSTAT_G          0x00000008
#घोषणा CPUSTAT_GED        0x00000004
#घोषणा CPUSTAT_J          0x00000002
#घोषणा CPUSTAT_P          0x00000001

काष्ठा kvm_s390_sie_block अणु
	atomic_t cpuflags;		/* 0x0000 */
	__u32 : 1;			/* 0x0004 */
	__u32 prefix : 18;
	__u32 : 1;
	__u32 ibc : 12;
	__u8	reserved08[4];		/* 0x0008 */
#घोषणा PROG_IN_SIE (1<<0)
	__u32	prog0c;			/* 0x000c */
	जोड़ अणु
		__u8	reserved10[16];		/* 0x0010 */
		काष्ठा अणु
			__u64	pv_handle_cpu;
			__u64	pv_handle_config;
		पूर्ण;
	पूर्ण;
#घोषणा PROG_BLOCK_SIE	(1<<0)
#घोषणा PROG_REQUEST	(1<<1)
	atomic_t prog20;		/* 0x0020 */
	__u8	reserved24[4];		/* 0x0024 */
	__u64	cpuपंचांग;			/* 0x0028 */
	__u64	ckc;			/* 0x0030 */
	__u64	epoch;			/* 0x0038 */
	__u32	svcc;			/* 0x0040 */
#घोषणा LCTL_CR0	0x8000
#घोषणा LCTL_CR6	0x0200
#घोषणा LCTL_CR9	0x0040
#घोषणा LCTL_CR10	0x0020
#घोषणा LCTL_CR11	0x0010
#घोषणा LCTL_CR14	0x0002
	__u16   lctl;			/* 0x0044 */
	__s16	icpua;			/* 0x0046 */
#घोषणा ICTL_OPEREXC	0x80000000
#घोषणा ICTL_PINT	0x20000000
#घोषणा ICTL_LPSW	0x00400000
#घोषणा ICTL_STCTL	0x00040000
#घोषणा ICTL_ISKE	0x00004000
#घोषणा ICTL_SSKE	0x00002000
#घोषणा ICTL_RRBE	0x00001000
#घोषणा ICTL_TPROT	0x00000200
	__u32	ictl;			/* 0x0048 */
#घोषणा ECA_CEI		0x80000000
#घोषणा ECA_IB		0x40000000
#घोषणा ECA_SIGPI	0x10000000
#घोषणा ECA_MVPGI	0x01000000
#घोषणा ECA_AIV		0x00200000
#घोषणा ECA_VX		0x00020000
#घोषणा ECA_PROTEXCI	0x00002000
#घोषणा ECA_APIE	0x00000008
#घोषणा ECA_SII		0x00000001
	__u32	eca;			/* 0x004c */
#घोषणा ICPT_INST	0x04
#घोषणा ICPT_PROGI	0x08
#घोषणा ICPT_INSTPROGI	0x0C
#घोषणा ICPT_EXTREQ	0x10
#घोषणा ICPT_EXTINT	0x14
#घोषणा ICPT_IOREQ	0x18
#घोषणा ICPT_WAIT	0x1c
#घोषणा ICPT_VALIDITY	0x20
#घोषणा ICPT_STOP	0x28
#घोषणा ICPT_OPEREXC	0x2C
#घोषणा ICPT_PARTEXEC	0x38
#घोषणा ICPT_IOINST	0x40
#घोषणा ICPT_KSS	0x5c
#घोषणा ICPT_MCHKREQ	0x60
#घोषणा ICPT_INT_ENABLE	0x64
#घोषणा ICPT_PV_INSTR	0x68
#घोषणा ICPT_PV_NOTIFY	0x6c
#घोषणा ICPT_PV_PREF	0x70
	__u8	icptcode;		/* 0x0050 */
	__u8	icptstatus;		/* 0x0051 */
	__u16	ihcpu;			/* 0x0052 */
	__u8	reserved54;		/* 0x0054 */
#घोषणा IICTL_CODE_NONE		 0x00
#घोषणा IICTL_CODE_MCHK		 0x01
#घोषणा IICTL_CODE_EXT		 0x02
#घोषणा IICTL_CODE_IO		 0x03
#घोषणा IICTL_CODE_RESTART	 0x04
#घोषणा IICTL_CODE_SPECIFICATION 0x10
#घोषणा IICTL_CODE_OPERAND	 0x11
	__u8	iictl;			/* 0x0055 */
	__u16	ipa;			/* 0x0056 */
	__u32	ipb;			/* 0x0058 */
	__u32	scaoh;			/* 0x005c */
#घोषणा FPF_BPBC 	0x20
	__u8	fpf;			/* 0x0060 */
#घोषणा ECB_GS		0x40
#घोषणा ECB_TE		0x10
#घोषणा ECB_SRSI	0x04
#घोषणा ECB_HOSTPROTINT	0x02
	__u8	ecb;			/* 0x0061 */
#घोषणा ECB2_CMMA	0x80
#घोषणा ECB2_IEP	0x20
#घोषणा ECB2_PFMFI	0x08
#घोषणा ECB2_ESCA	0x04
	__u8    ecb2;                   /* 0x0062 */
#घोषणा ECB3_DEA 0x08
#घोषणा ECB3_AES 0x04
#घोषणा ECB3_RI  0x01
	__u8    ecb3;			/* 0x0063 */
	__u32	scaol;			/* 0x0064 */
	__u8	sdf;			/* 0x0068 */
	__u8    epdx;			/* 0x0069 */
	__u8	cpnc;			/* 0x006a */
	__u8	reserved6b;		/* 0x006b */
	__u32	todpr;			/* 0x006c */
#घोषणा GISA_FORMAT1 0x00000001
	__u32	gd;			/* 0x0070 */
	__u8	reserved74[12];		/* 0x0074 */
	__u64	mso;			/* 0x0080 */
	__u64	msl;			/* 0x0088 */
	psw_t	gpsw;			/* 0x0090 */
	__u64	gg14;			/* 0x00a0 */
	__u64	gg15;			/* 0x00a8 */
	__u8	reservedb0[8];		/* 0x00b0 */
#घोषणा HPID_KVM	0x4
#घोषणा HPID_VSIE	0x5
	__u8	hpid;			/* 0x00b8 */
	__u8	reservedb9[7];		/* 0x00b9 */
	जोड़ अणु
		काष्ठा अणु
			__u32	eiparams;	/* 0x00c0 */
			__u16	extcpuaddr;	/* 0x00c4 */
			__u16	eic;		/* 0x00c6 */
		पूर्ण;
		__u64	mcic;			/* 0x00c0 */
	पूर्ण __packed;
	__u32	reservedc8;		/* 0x00c8 */
	जोड़ अणु
		काष्ठा अणु
			__u16	pgmilc;		/* 0x00cc */
			__u16	iprcc;		/* 0x00ce */
		पूर्ण;
		__u32	edc;			/* 0x00cc */
	पूर्ण __packed;
	जोड़ अणु
		काष्ठा अणु
			__u32	dxc;		/* 0x00d0 */
			__u16	mcn;		/* 0x00d4 */
			__u8	perc;		/* 0x00d6 */
			__u8	peraपंचांगid;	/* 0x00d7 */
		पूर्ण;
		__u64	faddr;			/* 0x00d0 */
	पूर्ण __packed;
	__u64	peraddr;		/* 0x00d8 */
	__u8	eai;			/* 0x00e0 */
	__u8	peraid;			/* 0x00e1 */
	__u8	oai;			/* 0x00e2 */
	__u8	armid;			/* 0x00e3 */
	__u8	reservede4[4];		/* 0x00e4 */
	जोड़ अणु
		__u64	tecmc;		/* 0x00e8 */
		काष्ठा अणु
			__u16	subchannel_id;	/* 0x00e8 */
			__u16	subchannel_nr;	/* 0x00ea */
			__u32	io_पूर्णांक_parm;	/* 0x00ec */
			__u32	io_पूर्णांक_word;	/* 0x00f0 */
		पूर्ण;
	पूर्ण __packed;
	__u8	reservedf4[8];		/* 0x00f4 */
#घोषणा CRYCB_FORMAT_MASK 0x00000003
#घोषणा CRYCB_FORMAT0 0x00000000
#घोषणा CRYCB_FORMAT1 0x00000001
#घोषणा CRYCB_FORMAT2 0x00000003
	__u32	crycbd;			/* 0x00fc */
	__u64	gcr[16];		/* 0x0100 */
	जोड़ अणु
		__u64	gbea;		/* 0x0180 */
		__u64	sidad;
	पूर्ण;
	__u8    reserved188[8];		/* 0x0188 */
	__u64   sdnxo;			/* 0x0190 */
	__u8    reserved198[8];		/* 0x0198 */
	__u32	fac;			/* 0x01a0 */
	__u8	reserved1a4[20];	/* 0x01a4 */
	__u64	cbrlo;			/* 0x01b8 */
	__u8	reserved1c0[8];		/* 0x01c0 */
#घोषणा ECD_HOSTREGMGMT	0x20000000
#घोषणा ECD_MEF		0x08000000
#घोषणा ECD_ETOKENF	0x02000000
#घोषणा ECD_ECC		0x00200000
	__u32	ecd;			/* 0x01c8 */
	__u8	reserved1cc[18];	/* 0x01cc */
	__u64	pp;			/* 0x01de */
	__u8	reserved1e6[2];		/* 0x01e6 */
	__u64	itdba;			/* 0x01e8 */
	__u64   riccbd;			/* 0x01f0 */
	__u64	gvrd;			/* 0x01f8 */
पूर्ण __packed __aligned(512);

काष्ठा kvm_s390_itdb अणु
	__u8	data[256];
पूर्ण;

काष्ठा sie_page अणु
	काष्ठा kvm_s390_sie_block sie_block;
	काष्ठा mcck_अस्थिर_info mcck_info;	/* 0x0200 */
	__u8 reserved218[360];		/* 0x0218 */
	__u64 pv_grregs[16];		/* 0x0380 */
	__u8 reserved400[512];		/* 0x0400 */
	काष्ठा kvm_s390_itdb itdb;	/* 0x0600 */
	__u8 reserved700[2304];		/* 0x0700 */
पूर्ण;

काष्ठा kvm_vcpu_stat अणु
	u64 निकास_userspace;
	u64 निकास_null;
	u64 निकास_बाह्यal_request;
	u64 निकास_io_request;
	u64 निकास_बाह्यal_पूर्णांकerrupt;
	u64 निकास_stop_request;
	u64 निकास_validity;
	u64 निकास_inकाष्ठाion;
	u64 निकास_pei;
	u64 halt_successful_poll;
	u64 halt_attempted_poll;
	u64 halt_poll_invalid;
	u64 halt_no_poll_steal;
	u64 halt_wakeup;
	u64 halt_poll_success_ns;
	u64 halt_poll_fail_ns;
	u64 inकाष्ठाion_lctl;
	u64 inकाष्ठाion_lctlg;
	u64 inकाष्ठाion_stctl;
	u64 inकाष्ठाion_stctg;
	u64 निकास_program_पूर्णांकerruption;
	u64 निकास_instr_and_program;
	u64 निकास_operation_exception;
	u64 deliver_ckc;
	u64 deliver_cpuपंचांग;
	u64 deliver_बाह्यal_call;
	u64 deliver_emergency_संकेत;
	u64 deliver_service_संकेत;
	u64 deliver_virtio;
	u64 deliver_stop_संकेत;
	u64 deliver_prefix_संकेत;
	u64 deliver_restart_संकेत;
	u64 deliver_program;
	u64 deliver_io;
	u64 deliver_machine_check;
	u64 निकास_रुको_state;
	u64 inject_ckc;
	u64 inject_cpuपंचांग;
	u64 inject_बाह्यal_call;
	u64 inject_emergency_संकेत;
	u64 inject_mchk;
	u64 inject_pfault_init;
	u64 inject_program;
	u64 inject_restart;
	u64 inject_set_prefix;
	u64 inject_stop_संकेत;
	u64 inकाष्ठाion_epsw;
	u64 inकाष्ठाion_gs;
	u64 inकाष्ठाion_io_other;
	u64 inकाष्ठाion_lpsw;
	u64 inकाष्ठाion_lpswe;
	u64 inकाष्ठाion_pfmf;
	u64 inकाष्ठाion_ptff;
	u64 inकाष्ठाion_sck;
	u64 inकाष्ठाion_sckpf;
	u64 inकाष्ठाion_stidp;
	u64 inकाष्ठाion_spx;
	u64 inकाष्ठाion_stpx;
	u64 inकाष्ठाion_stap;
	u64 inकाष्ठाion_iske;
	u64 inकाष्ठाion_ri;
	u64 inकाष्ठाion_rrbe;
	u64 inकाष्ठाion_sske;
	u64 inकाष्ठाion_ipte_पूर्णांकerlock;
	u64 inकाष्ठाion_stsi;
	u64 inकाष्ठाion_stfl;
	u64 inकाष्ठाion_tb;
	u64 inकाष्ठाion_tpi;
	u64 inकाष्ठाion_tprot;
	u64 inकाष्ठाion_tsch;
	u64 inकाष्ठाion_sie;
	u64 inकाष्ठाion_essa;
	u64 inकाष्ठाion_sthyi;
	u64 inकाष्ठाion_sigp_sense;
	u64 inकाष्ठाion_sigp_sense_running;
	u64 inकाष्ठाion_sigp_बाह्यal_call;
	u64 inकाष्ठाion_sigp_emergency;
	u64 inकाष्ठाion_sigp_cond_emergency;
	u64 inकाष्ठाion_sigp_start;
	u64 inकाष्ठाion_sigp_stop;
	u64 inकाष्ठाion_sigp_stop_store_status;
	u64 inकाष्ठाion_sigp_store_status;
	u64 inकाष्ठाion_sigp_store_adtl_status;
	u64 inकाष्ठाion_sigp_arch;
	u64 inकाष्ठाion_sigp_prefix;
	u64 inकाष्ठाion_sigp_restart;
	u64 inकाष्ठाion_sigp_init_cpu_reset;
	u64 inकाष्ठाion_sigp_cpu_reset;
	u64 inकाष्ठाion_sigp_unknown;
	u64 diagnose_10;
	u64 diagnose_44;
	u64 diagnose_9c;
	u64 diagnose_9c_ignored;
	u64 diagnose_9c_क्रमward;
	u64 diagnose_258;
	u64 diagnose_308;
	u64 diagnose_500;
	u64 diagnose_other;
	u64 pfault_sync;
पूर्ण;

#घोषणा PGM_OPERATION			0x01
#घोषणा PGM_PRIVILEGED_OP		0x02
#घोषणा PGM_EXECUTE			0x03
#घोषणा PGM_PROTECTION			0x04
#घोषणा PGM_ADDRESSING			0x05
#घोषणा PGM_SPECIFICATION		0x06
#घोषणा PGM_DATA			0x07
#घोषणा PGM_FIXED_POINT_OVERFLOW	0x08
#घोषणा PGM_FIXED_POINT_DIVIDE		0x09
#घोषणा PGM_DECIMAL_OVERFLOW		0x0a
#घोषणा PGM_DECIMAL_DIVIDE		0x0b
#घोषणा PGM_HFP_EXPONENT_OVERFLOW	0x0c
#घोषणा PGM_HFP_EXPONENT_UNDERFLOW	0x0d
#घोषणा PGM_HFP_SIGNIFICANCE		0x0e
#घोषणा PGM_HFP_DIVIDE			0x0f
#घोषणा PGM_SEGMENT_TRANSLATION		0x10
#घोषणा PGM_PAGE_TRANSLATION		0x11
#घोषणा PGM_TRANSLATION_SPEC		0x12
#घोषणा PGM_SPECIAL_OPERATION		0x13
#घोषणा PGM_OPERAND			0x15
#घोषणा PGM_TRACE_TABEL			0x16
#घोषणा PGM_VECTOR_PROCESSING		0x1b
#घोषणा PGM_SPACE_SWITCH		0x1c
#घोषणा PGM_HFP_SQUARE_ROOT		0x1d
#घोषणा PGM_PC_TRANSLATION_SPEC		0x1f
#घोषणा PGM_AFX_TRANSLATION		0x20
#घोषणा PGM_ASX_TRANSLATION		0x21
#घोषणा PGM_LX_TRANSLATION		0x22
#घोषणा PGM_EX_TRANSLATION		0x23
#घोषणा PGM_PRIMARY_AUTHORITY		0x24
#घोषणा PGM_SECONDARY_AUTHORITY		0x25
#घोषणा PGM_LFX_TRANSLATION		0x26
#घोषणा PGM_LSX_TRANSLATION		0x27
#घोषणा PGM_ALET_SPECIFICATION		0x28
#घोषणा PGM_ALEN_TRANSLATION		0x29
#घोषणा PGM_ALE_SEQUENCE		0x2a
#घोषणा PGM_ASTE_VALIDITY		0x2b
#घोषणा PGM_ASTE_SEQUENCE		0x2c
#घोषणा PGM_EXTENDED_AUTHORITY		0x2d
#घोषणा PGM_LSTE_SEQUENCE		0x2e
#घोषणा PGM_ASTE_INSTANCE		0x2f
#घोषणा PGM_STACK_FULL			0x30
#घोषणा PGM_STACK_EMPTY			0x31
#घोषणा PGM_STACK_SPECIFICATION		0x32
#घोषणा PGM_STACK_TYPE			0x33
#घोषणा PGM_STACK_OPERATION		0x34
#घोषणा PGM_ASCE_TYPE			0x38
#घोषणा PGM_REGION_FIRST_TRANS		0x39
#घोषणा PGM_REGION_SECOND_TRANS		0x3a
#घोषणा PGM_REGION_THIRD_TRANS		0x3b
#घोषणा PGM_MONITOR			0x40
#घोषणा PGM_PER				0x80
#घोषणा PGM_CRYPTO_OPERATION		0x119

/* irq types in ascend order of priorities */
क्रमागत irq_types अणु
	IRQ_PEND_SET_PREFIX = 0,
	IRQ_PEND_RESTART,
	IRQ_PEND_SIGP_STOP,
	IRQ_PEND_IO_ISC_7,
	IRQ_PEND_IO_ISC_6,
	IRQ_PEND_IO_ISC_5,
	IRQ_PEND_IO_ISC_4,
	IRQ_PEND_IO_ISC_3,
	IRQ_PEND_IO_ISC_2,
	IRQ_PEND_IO_ISC_1,
	IRQ_PEND_IO_ISC_0,
	IRQ_PEND_VIRTIO,
	IRQ_PEND_PFAULT_DONE,
	IRQ_PEND_PFAULT_INIT,
	IRQ_PEND_EXT_HOST,
	IRQ_PEND_EXT_SERVICE,
	IRQ_PEND_EXT_SERVICE_EV,
	IRQ_PEND_EXT_TIMING,
	IRQ_PEND_EXT_CPU_TIMER,
	IRQ_PEND_EXT_CLOCK_COMP,
	IRQ_PEND_EXT_EXTERNAL,
	IRQ_PEND_EXT_EMERGENCY,
	IRQ_PEND_EXT_MALFUNC,
	IRQ_PEND_EXT_IRQ_KEY,
	IRQ_PEND_MCHK_REP,
	IRQ_PEND_PROG,
	IRQ_PEND_SVC,
	IRQ_PEND_MCHK_EX,
	IRQ_PEND_COUNT
पूर्ण;

/* We have 2M क्रम virtio device descriptor pages. Smallest amount of
 * memory per page is 24 bytes (1 queue), so (2048*1024) / 24 = 87381
 */
#घोषणा KVM_S390_MAX_VIRTIO_IRQS 87381

/*
 * Repressible (non-भग्नing) machine check पूर्णांकerrupts
 * subclass bits in MCIC
 */
#घोषणा MCHK_EXTD_BIT 58
#घोषणा MCHK_DEGR_BIT 56
#घोषणा MCHK_WARN_BIT 55
#घोषणा MCHK_REP_MASK ((1UL << MCHK_DEGR_BIT) | \
		       (1UL << MCHK_EXTD_BIT) | \
		       (1UL << MCHK_WARN_BIT))

/* Exigent machine check पूर्णांकerrupts subclass bits in MCIC */
#घोषणा MCHK_SD_BIT 63
#घोषणा MCHK_PD_BIT 62
#घोषणा MCHK_EX_MASK ((1UL << MCHK_SD_BIT) | (1UL << MCHK_PD_BIT))

#घोषणा IRQ_PEND_EXT_MASK ((1UL << IRQ_PEND_EXT_IRQ_KEY)    | \
			   (1UL << IRQ_PEND_EXT_CLOCK_COMP) | \
			   (1UL << IRQ_PEND_EXT_CPU_TIMER)  | \
			   (1UL << IRQ_PEND_EXT_MALFUNC)    | \
			   (1UL << IRQ_PEND_EXT_EMERGENCY)  | \
			   (1UL << IRQ_PEND_EXT_EXTERNAL)   | \
			   (1UL << IRQ_PEND_EXT_TIMING)     | \
			   (1UL << IRQ_PEND_EXT_HOST)       | \
			   (1UL << IRQ_PEND_EXT_SERVICE)    | \
			   (1UL << IRQ_PEND_EXT_SERVICE_EV) | \
			   (1UL << IRQ_PEND_VIRTIO)         | \
			   (1UL << IRQ_PEND_PFAULT_INIT)    | \
			   (1UL << IRQ_PEND_PFAULT_DONE))

#घोषणा IRQ_PEND_IO_MASK ((1UL << IRQ_PEND_IO_ISC_0) | \
			  (1UL << IRQ_PEND_IO_ISC_1) | \
			  (1UL << IRQ_PEND_IO_ISC_2) | \
			  (1UL << IRQ_PEND_IO_ISC_3) | \
			  (1UL << IRQ_PEND_IO_ISC_4) | \
			  (1UL << IRQ_PEND_IO_ISC_5) | \
			  (1UL << IRQ_PEND_IO_ISC_6) | \
			  (1UL << IRQ_PEND_IO_ISC_7))

#घोषणा IRQ_PEND_MCHK_MASK ((1UL << IRQ_PEND_MCHK_REP) | \
			    (1UL << IRQ_PEND_MCHK_EX))

#घोषणा IRQ_PEND_EXT_II_MASK ((1UL << IRQ_PEND_EXT_CPU_TIMER)  | \
			      (1UL << IRQ_PEND_EXT_CLOCK_COMP) | \
			      (1UL << IRQ_PEND_EXT_EMERGENCY)  | \
			      (1UL << IRQ_PEND_EXT_EXTERNAL)   | \
			      (1UL << IRQ_PEND_EXT_SERVICE)    | \
			      (1UL << IRQ_PEND_EXT_SERVICE_EV))

काष्ठा kvm_s390_पूर्णांकerrupt_info अणु
	काष्ठा list_head list;
	u64	type;
	जोड़ अणु
		काष्ठा kvm_s390_io_info io;
		काष्ठा kvm_s390_ext_info ext;
		काष्ठा kvm_s390_pgm_info pgm;
		काष्ठा kvm_s390_emerg_info emerg;
		काष्ठा kvm_s390_extcall_info extcall;
		काष्ठा kvm_s390_prefix_info prefix;
		काष्ठा kvm_s390_stop_info stop;
		काष्ठा kvm_s390_mchk_info mchk;
	पूर्ण;
पूर्ण;

काष्ठा kvm_s390_irq_payload अणु
	काष्ठा kvm_s390_io_info io;
	काष्ठा kvm_s390_ext_info ext;
	काष्ठा kvm_s390_pgm_info pgm;
	काष्ठा kvm_s390_emerg_info emerg;
	काष्ठा kvm_s390_extcall_info extcall;
	काष्ठा kvm_s390_prefix_info prefix;
	काष्ठा kvm_s390_stop_info stop;
	काष्ठा kvm_s390_mchk_info mchk;
पूर्ण;

काष्ठा kvm_s390_local_पूर्णांकerrupt अणु
	spinlock_t lock;
	DECLARE_BITMAP(sigp_emerg_pending, KVM_MAX_VCPUS);
	काष्ठा kvm_s390_irq_payload irq;
	अचिन्हित दीर्घ pending_irqs;
पूर्ण;

#घोषणा FIRQ_LIST_IO_ISC_0 0
#घोषणा FIRQ_LIST_IO_ISC_1 1
#घोषणा FIRQ_LIST_IO_ISC_2 2
#घोषणा FIRQ_LIST_IO_ISC_3 3
#घोषणा FIRQ_LIST_IO_ISC_4 4
#घोषणा FIRQ_LIST_IO_ISC_5 5
#घोषणा FIRQ_LIST_IO_ISC_6 6
#घोषणा FIRQ_LIST_IO_ISC_7 7
#घोषणा FIRQ_LIST_PFAULT   8
#घोषणा FIRQ_LIST_VIRTIO   9
#घोषणा FIRQ_LIST_COUNT   10
#घोषणा FIRQ_CNTR_IO       0
#घोषणा FIRQ_CNTR_SERVICE  1
#घोषणा FIRQ_CNTR_VIRTIO   2
#घोषणा FIRQ_CNTR_PFAULT   3
#घोषणा FIRQ_MAX_COUNT     4

/* mask the AIS mode क्रम a given ISC */
#घोषणा AIS_MODE_MASK(isc) (0x80 >> isc)

#घोषणा KVM_S390_AIS_MODE_ALL    0
#घोषणा KVM_S390_AIS_MODE_SINGLE 1

काष्ठा kvm_s390_भग्न_पूर्णांकerrupt अणु
	अचिन्हित दीर्घ pending_irqs;
	अचिन्हित दीर्घ masked_irqs;
	spinlock_t lock;
	काष्ठा list_head lists[FIRQ_LIST_COUNT];
	पूर्णांक counters[FIRQ_MAX_COUNT];
	काष्ठा kvm_s390_mchk_info mchk;
	काष्ठा kvm_s390_ext_info srv_संकेत;
	पूर्णांक next_rr_cpu;
	काष्ठा mutex ais_lock;
	u8 simm;
	u8 nimm;
पूर्ण;

काष्ठा kvm_hw_wp_info_arch अणु
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ phys_addr;
	पूर्णांक len;
	अक्षर *old_data;
पूर्ण;

काष्ठा kvm_hw_bp_info_arch अणु
	अचिन्हित दीर्घ addr;
	पूर्णांक len;
पूर्ण;

/*
 * Only the upper 16 bits of kvm_guest_debug->control are arch specअगरic.
 * Further KVM_GUESTDBG flags which an be used from userspace can be found in
 * arch/s390/include/uapi/यंत्र/kvm.h
 */
#घोषणा KVM_GUESTDBG_EXIT_PENDING 0x10000000

#घोषणा guestdbg_enabled(vcpu) \
		(vcpu->guest_debug & KVM_GUESTDBG_ENABLE)
#घोषणा guestdbg_sstep_enabled(vcpu) \
		(vcpu->guest_debug & KVM_GUESTDBG_SINGLESTEP)
#घोषणा guestdbg_hw_bp_enabled(vcpu) \
		(vcpu->guest_debug & KVM_GUESTDBG_USE_HW_BP)
#घोषणा guestdbg_निकास_pending(vcpu) (guestdbg_enabled(vcpu) && \
		(vcpu->guest_debug & KVM_GUESTDBG_EXIT_PENDING))

#घोषणा KVM_GUESTDBG_VALID_MASK \
		(KVM_GUESTDBG_ENABLE | KVM_GUESTDBG_SINGLESTEP |\
		KVM_GUESTDBG_USE_HW_BP | KVM_GUESTDBG_EXIT_PENDING)

काष्ठा kvm_guestdbg_info_arch अणु
	अचिन्हित दीर्घ cr0;
	अचिन्हित दीर्घ cr9;
	अचिन्हित दीर्घ cr10;
	अचिन्हित दीर्घ cr11;
	काष्ठा kvm_hw_bp_info_arch *hw_bp_info;
	काष्ठा kvm_hw_wp_info_arch *hw_wp_info;
	पूर्णांक nr_hw_bp;
	पूर्णांक nr_hw_wp;
	अचिन्हित दीर्घ last_bp;
पूर्ण;

काष्ठा kvm_s390_pv_vcpu अणु
	u64 handle;
	अचिन्हित दीर्घ stor_base;
पूर्ण;

काष्ठा kvm_vcpu_arch अणु
	काष्ठा kvm_s390_sie_block *sie_block;
	/* अगर vsie is active, currently executed shaकरोw sie control block */
	काष्ठा kvm_s390_sie_block *vsie_block;
	अचिन्हित पूर्णांक      host_acrs[NUM_ACRS];
	काष्ठा gs_cb      *host_gscb;
	काष्ठा fpu	  host_fpregs;
	काष्ठा kvm_s390_local_पूर्णांकerrupt local_पूर्णांक;
	काष्ठा hrसमयr    ckc_समयr;
	काष्ठा kvm_s390_pgm_info pgm;
	काष्ठा gmap *gmap;
	/* backup location क्रम the currently enabled gmap when scheduled out */
	काष्ठा gmap *enabled_gmap;
	काष्ठा kvm_guestdbg_info_arch guestdbg;
	अचिन्हित दीर्घ pfault_token;
	अचिन्हित दीर्घ pfault_select;
	अचिन्हित दीर्घ pfault_compare;
	bool cpuपंचांग_enabled;
	/*
	 * The seqcount protects updates to cpuपंचांग_start and sie_block.cpuपंचांग,
	 * this way we can have non-blocking पढ़ोs with consistent values.
	 * Only the owning VCPU thपढ़ो (vcpu->cpu) is allowed to change these
	 * values and to start/stop/enable/disable cpu समयr accounting.
	 */
	seqcount_t cpuपंचांग_seqcount;
	__u64 cpuपंचांग_start;
	bool gs_enabled;
	bool skey_enabled;
	काष्ठा kvm_s390_pv_vcpu pv;
	जोड़ diag318_info diag318_info;
पूर्ण;

काष्ठा kvm_vm_stat अणु
	u64 inject_io;
	u64 inject_भग्न_mchk;
	u64 inject_pfault_करोne;
	u64 inject_service_संकेत;
	u64 inject_virtio;
	u64 remote_tlb_flush;
पूर्ण;

काष्ठा kvm_arch_memory_slot अणु
पूर्ण;

काष्ठा s390_map_info अणु
	काष्ठा list_head list;
	__u64 guest_addr;
	__u64 addr;
	काष्ठा page *page;
पूर्ण;

काष्ठा s390_io_adapter अणु
	अचिन्हित पूर्णांक id;
	पूर्णांक isc;
	bool maskable;
	bool masked;
	bool swap;
	bool suppressible;
पूर्ण;

#घोषणा MAX_S390_IO_ADAPTERS ((MAX_ISC + 1) * 8)
#घोषणा MAX_S390_ADAPTER_MAPS 256

/* maximum size of facilities and facility mask is 2k bytes */
#घोषणा S390_ARCH_FAC_LIST_SIZE_BYTE (1<<11)
#घोषणा S390_ARCH_FAC_LIST_SIZE_U64 \
	(S390_ARCH_FAC_LIST_SIZE_BYTE / माप(u64))
#घोषणा S390_ARCH_FAC_MASK_SIZE_BYTE S390_ARCH_FAC_LIST_SIZE_BYTE
#घोषणा S390_ARCH_FAC_MASK_SIZE_U64 \
	(S390_ARCH_FAC_MASK_SIZE_BYTE / माप(u64))

काष्ठा kvm_s390_cpu_model अणु
	/* facility mask supported by kvm & hosting machine */
	__u64 fac_mask[S390_ARCH_FAC_LIST_SIZE_U64];
	काष्ठा kvm_s390_vm_cpu_subfunc subfuncs;
	/* facility list requested by guest (in dma page) */
	__u64 *fac_list;
	u64 cpuid;
	अचिन्हित लघु ibc;
पूर्ण;

काष्ठा kvm_s390_module_hook अणु
	पूर्णांक (*hook)(काष्ठा kvm_vcpu *vcpu);
	काष्ठा module *owner;
पूर्ण;

काष्ठा kvm_s390_crypto अणु
	काष्ठा kvm_s390_crypto_cb *crycb;
	काष्ठा kvm_s390_module_hook *pqap_hook;
	__u32 crycbd;
	__u8 aes_kw;
	__u8 dea_kw;
	__u8 apie;
पूर्ण;

#घोषणा APCB0_MASK_SIZE 1
काष्ठा kvm_s390_apcb0 अणु
	__u64 apm[APCB0_MASK_SIZE];		/* 0x0000 */
	__u64 aqm[APCB0_MASK_SIZE];		/* 0x0008 */
	__u64 adm[APCB0_MASK_SIZE];		/* 0x0010 */
	__u64 reserved18;			/* 0x0018 */
पूर्ण;

#घोषणा APCB1_MASK_SIZE 4
काष्ठा kvm_s390_apcb1 अणु
	__u64 apm[APCB1_MASK_SIZE];		/* 0x0000 */
	__u64 aqm[APCB1_MASK_SIZE];		/* 0x0020 */
	__u64 adm[APCB1_MASK_SIZE];		/* 0x0040 */
	__u64 reserved60[4];			/* 0x0060 */
पूर्ण;

काष्ठा kvm_s390_crypto_cb अणु
	काष्ठा kvm_s390_apcb0 apcb0;		/* 0x0000 */
	__u8   reserved20[0x0048 - 0x0020];	/* 0x0020 */
	__u8   dea_wrapping_key_mask[24];	/* 0x0048 */
	__u8   aes_wrapping_key_mask[32];	/* 0x0060 */
	काष्ठा kvm_s390_apcb1 apcb1;		/* 0x0080 */
पूर्ण;

काष्ठा kvm_s390_gisa अणु
	जोड़ अणु
		काष्ठा अणु /* common to all क्रमmats */
			u32 next_alert;
			u8  ipm;
			u8  reserved01[2];
			u8  iam;
		पूर्ण;
		काष्ठा अणु /* क्रमmat 0 */
			u32 next_alert;
			u8  ipm;
			u8  reserved01;
			u8  : 6;
			u8  g : 1;
			u8  c : 1;
			u8  iam;
			u8  reserved02[4];
			u32 airq_count;
		पूर्ण g0;
		काष्ठा अणु /* क्रमmat 1 */
			u32 next_alert;
			u8  ipm;
			u8  simm;
			u8  nimm;
			u8  iam;
			u8  aism[8];
			u8  : 6;
			u8  g : 1;
			u8  c : 1;
			u8  reserved03[11];
			u32 airq_count;
		पूर्ण g1;
		काष्ठा अणु
			u64 word[4];
		पूर्ण u64;
	पूर्ण;
पूर्ण;

काष्ठा kvm_s390_gib अणु
	u32 alert_list_origin;
	u32 reserved01;
	u8:5;
	u8  nisc:3;
	u8  reserved03[3];
	u32 reserved04[5];
पूर्ण;

/*
 * sie_page2 has to be allocated as DMA because fac_list, crycb and
 * gisa need 31bit addresses in the sie control block.
 */
काष्ठा sie_page2 अणु
	__u64 fac_list[S390_ARCH_FAC_LIST_SIZE_U64];	/* 0x0000 */
	काष्ठा kvm_s390_crypto_cb crycb;		/* 0x0800 */
	काष्ठा kvm_s390_gisa gisa;			/* 0x0900 */
	काष्ठा kvm *kvm;				/* 0x0920 */
	u8 reserved928[0x1000 - 0x928];			/* 0x0928 */
पूर्ण;

काष्ठा kvm_s390_vsie अणु
	काष्ठा mutex mutex;
	काष्ठा radix_tree_root addr_to_page;
	पूर्णांक page_count;
	पूर्णांक next;
	काष्ठा page *pages[KVM_MAX_VCPUS];
पूर्ण;

काष्ठा kvm_s390_gisa_iam अणु
	u8 mask;
	spinlock_t ref_lock;
	u32 ref_count[MAX_ISC + 1];
पूर्ण;

काष्ठा kvm_s390_gisa_पूर्णांकerrupt अणु
	काष्ठा kvm_s390_gisa *origin;
	काष्ठा kvm_s390_gisa_iam alert;
	काष्ठा hrसमयr समयr;
	u64 expires;
	DECLARE_BITMAP(kicked_mask, KVM_MAX_VCPUS);
पूर्ण;

काष्ठा kvm_s390_pv अणु
	u64 handle;
	u64 guest_len;
	अचिन्हित दीर्घ stor_base;
	व्योम *stor_var;
पूर्ण;

काष्ठा kvm_archअणु
	व्योम *sca;
	पूर्णांक use_esca;
	rwlock_t sca_lock;
	debug_info_t *dbf;
	काष्ठा kvm_s390_भग्न_पूर्णांकerrupt भग्न_पूर्णांक;
	काष्ठा kvm_device *flic;
	काष्ठा gmap *gmap;
	अचिन्हित दीर्घ mem_limit;
	पूर्णांक css_support;
	पूर्णांक use_irqchip;
	पूर्णांक use_cmma;
	पूर्णांक use_pfmfi;
	पूर्णांक use_skf;
	पूर्णांक user_cpu_state_ctrl;
	पूर्णांक user_sigp;
	पूर्णांक user_stsi;
	पूर्णांक user_instr0;
	काष्ठा s390_io_adapter *adapters[MAX_S390_IO_ADAPTERS];
	रुको_queue_head_t ipte_wq;
	पूर्णांक ipte_lock_count;
	काष्ठा mutex ipte_mutex;
	spinlock_t start_stop_lock;
	काष्ठा sie_page2 *sie_page2;
	काष्ठा kvm_s390_cpu_model model;
	काष्ठा kvm_s390_crypto crypto;
	काष्ठा kvm_s390_vsie vsie;
	u8 epdx;
	u64 epoch;
	पूर्णांक migration_mode;
	atomic64_t cmma_dirty_pages;
	/* subset of available cpu features enabled by user space */
	DECLARE_BITMAP(cpu_feat, KVM_S390_VM_CPU_FEAT_NR_BITS);
	DECLARE_BITMAP(idle_mask, KVM_MAX_VCPUS);
	काष्ठा kvm_s390_gisa_पूर्णांकerrupt gisa_पूर्णांक;
	काष्ठा kvm_s390_pv pv;
पूर्ण;

#घोषणा KVM_HVA_ERR_BAD		(-1UL)
#घोषणा KVM_HVA_ERR_RO_BAD	(-2UL)

अटल अंतरभूत bool kvm_is_error_hva(अचिन्हित दीर्घ addr)
अणु
	वापस IS_ERR_VALUE(addr);
पूर्ण

#घोषणा ASYNC_PF_PER_VCPU	64
काष्ठा kvm_arch_async_pf अणु
	अचिन्हित दीर्घ pfault_token;
पूर्ण;

bool kvm_arch_can_dequeue_async_page_present(काष्ठा kvm_vcpu *vcpu);

व्योम kvm_arch_async_page_पढ़ोy(काष्ठा kvm_vcpu *vcpu,
			       काष्ठा kvm_async_pf *work);

bool kvm_arch_async_page_not_present(काष्ठा kvm_vcpu *vcpu,
				     काष्ठा kvm_async_pf *work);

व्योम kvm_arch_async_page_present(काष्ठा kvm_vcpu *vcpu,
				 काष्ठा kvm_async_pf *work);

अटल अंतरभूत व्योम kvm_arch_async_page_present_queued(काष्ठा kvm_vcpu *vcpu) अणुपूर्ण

व्योम kvm_arch_crypto_clear_masks(काष्ठा kvm *kvm);
व्योम kvm_arch_crypto_set_masks(काष्ठा kvm *kvm, अचिन्हित दीर्घ *apm,
			       अचिन्हित दीर्घ *aqm, अचिन्हित दीर्घ *adm);

बाह्य पूर्णांक sie64a(काष्ठा kvm_s390_sie_block *, u64 *);
बाह्य अक्षर sie_निकास;

बाह्य पूर्णांक kvm_s390_gisc_रेजिस्टर(काष्ठा kvm *kvm, u32 gisc);
बाह्य पूर्णांक kvm_s390_gisc_unरेजिस्टर(काष्ठा kvm *kvm, u32 gisc);

अटल अंतरभूत व्योम kvm_arch_hardware_disable(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम kvm_arch_sync_events(काष्ठा kvm *kvm) अणुपूर्ण
अटल अंतरभूत व्योम kvm_arch_sched_in(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu) अणुपूर्ण
अटल अंतरभूत व्योम kvm_arch_मुक्त_memslot(काष्ठा kvm *kvm,
					 काष्ठा kvm_memory_slot *slot) अणुपूर्ण
अटल अंतरभूत व्योम kvm_arch_memslots_updated(काष्ठा kvm *kvm, u64 gen) अणुपूर्ण
अटल अंतरभूत व्योम kvm_arch_flush_shaकरोw_all(काष्ठा kvm *kvm) अणुपूर्ण
अटल अंतरभूत व्योम kvm_arch_flush_shaकरोw_memslot(काष्ठा kvm *kvm,
		काष्ठा kvm_memory_slot *slot) अणुपूर्ण
अटल अंतरभूत व्योम kvm_arch_vcpu_blocking(काष्ठा kvm_vcpu *vcpu) अणुपूर्ण
अटल अंतरभूत व्योम kvm_arch_vcpu_unblocking(काष्ठा kvm_vcpu *vcpu) अणुपूर्ण

व्योम kvm_arch_vcpu_block_finish(काष्ठा kvm_vcpu *vcpu);

#पूर्ण_अगर
