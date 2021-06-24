<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *   Machine check handler definitions
 *
 *    Copyright IBM Corp. 2000, 2009
 *    Author(s): Ingo Adlung <adlung@de.ibm.com>,
 *		 Martin Schwidefsky <schwidefsky@de.ibm.com>,
 *		 Cornelia Huck <cornelia.huck@de.ibm.com>,
 *		 Heiko Carstens <heiko.carstens@de.ibm.com>,
 */

#अगर_अघोषित _ASM_S390_NMI_H
#घोषणा _ASM_S390_NMI_H

#समावेश <linux/bits.h>
#समावेश <linux/types.h>

#घोषणा MCIC_SUBCLASS_MASK	(1ULL<<63 | 1ULL<<62 | 1ULL<<61 | \
				1ULL<<59 | 1ULL<<58 | 1ULL<<56 | \
				1ULL<<55 | 1ULL<<54 | 1ULL<<53 | \
				1ULL<<52 | 1ULL<<47 | 1ULL<<46 | \
				1ULL<<45 | 1ULL<<44)
#घोषणा MCCK_CODE_SYSTEM_DAMAGE		BIT(63)
#घोषणा MCCK_CODE_EXT_DAMAGE		BIT(63 - 5)
#घोषणा MCCK_CODE_CP			BIT(63 - 9)
#घोषणा MCCK_CODE_CPU_TIMER_VALID	BIT(63 - 46)
#घोषणा MCCK_CODE_PSW_MWP_VALID		BIT(63 - 20)
#घोषणा MCCK_CODE_PSW_IA_VALID		BIT(63 - 23)
#घोषणा MCCK_CODE_CR_VALID		BIT(63 - 29)
#घोषणा MCCK_CODE_GS_VALID		BIT(63 - 36)
#घोषणा MCCK_CODE_FC_VALID		BIT(63 - 43)

#अगर_अघोषित __ASSEMBLY__

जोड़ mci अणु
	अचिन्हित दीर्घ val;
	काष्ठा अणु
		u64 sd :  1; /* 00 प्रणाली damage */
		u64 pd :  1; /* 01 inकाष्ठाion-processing damage */
		u64 sr :  1; /* 02 प्रणाली recovery */
		u64    :  1; /* 03 */
		u64 cd :  1; /* 04 timing-facility damage */
		u64 ed :  1; /* 05 बाह्यal damage */
		u64    :  1; /* 06 */
		u64 dg :  1; /* 07 degradation */
		u64 w  :  1; /* 08 warning pending */
		u64 cp :  1; /* 09 channel-report pending */
		u64 sp :  1; /* 10 service-processor damage */
		u64 ck :  1; /* 11 channel-subप्रणाली damage */
		u64    :  2; /* 12-13 */
		u64 b  :  1; /* 14 backed up */
		u64    :  1; /* 15 */
		u64 se :  1; /* 16 storage error uncorrected */
		u64 sc :  1; /* 17 storage error corrected */
		u64 ke :  1; /* 18 storage-key error uncorrected */
		u64 ds :  1; /* 19 storage degradation */
		u64 wp :  1; /* 20 psw mwp validity */
		u64 ms :  1; /* 21 psw mask and key validity */
		u64 pm :  1; /* 22 psw program mask and cc validity */
		u64 ia :  1; /* 23 psw inकाष्ठाion address validity */
		u64 fa :  1; /* 24 failing storage address validity */
		u64 vr :  1; /* 25 vector रेजिस्टर validity */
		u64 ec :  1; /* 26 बाह्यal damage code validity */
		u64 fp :  1; /* 27 भग्नing poपूर्णांक रेजिस्टर validity */
		u64 gr :  1; /* 28 general रेजिस्टर validity */
		u64 cr :  1; /* 29 control रेजिस्टर validity */
		u64    :  1; /* 30 */
		u64 st :  1; /* 31 storage logical validity */
		u64 ie :  1; /* 32 indirect storage error */
		u64 ar :  1; /* 33 access रेजिस्टर validity */
		u64 da :  1; /* 34 delayed access exception */
		u64    :  1; /* 35 */
		u64 gs :  1; /* 36 guarded storage रेजिस्टरs validity */
		u64    :  5; /* 37-41 */
		u64 pr :  1; /* 42 tod programmable रेजिस्टर validity */
		u64 fc :  1; /* 43 fp control रेजिस्टर validity */
		u64 ap :  1; /* 44 ancillary report */
		u64    :  1; /* 45 */
		u64 ct :  1; /* 46 cpu समयr validity */
		u64 cc :  1; /* 47 घड़ी comparator validity */
		u64    : 16; /* 47-63 */
	पूर्ण;
पूर्ण;

#घोषणा MCESA_ORIGIN_MASK	(~0x3ffUL)
#घोषणा MCESA_LC_MASK		(0xfUL)
#घोषणा MCESA_MIN_SIZE		(1024)
#घोषणा MCESA_MAX_SIZE		(2048)

काष्ठा mcesa अणु
	u8 vector_save_area[1024];
	u8 guarded_storage_save_area[32];
पूर्ण;

काष्ठा pt_regs;

व्योम nmi_alloc_boot_cpu(काष्ठा lowcore *lc);
पूर्णांक nmi_alloc_per_cpu(काष्ठा lowcore *lc);
व्योम nmi_मुक्त_per_cpu(काष्ठा lowcore *lc);

व्योम s390_handle_mcck(व्योम);
व्योम __s390_handle_mcck(व्योम);
पूर्णांक s390_करो_machine_check(काष्ठा pt_regs *regs);

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_S390_NMI_H */
