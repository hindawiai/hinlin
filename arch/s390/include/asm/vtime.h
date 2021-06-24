<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _S390_VTIME_H
#घोषणा _S390_VTIME_H

#घोषणा __ARCH_HAS_VTIME_TASK_SWITCH

अटल अंतरभूत व्योम update_समयr_sys(व्योम)
अणु
	S390_lowcore.प्रणाली_समयr += S390_lowcore.last_update_समयr - S390_lowcore.निकास_समयr;
	S390_lowcore.user_समयr += S390_lowcore.निकास_समयr - S390_lowcore.sys_enter_समयr;
	S390_lowcore.last_update_समयr = S390_lowcore.sys_enter_समयr;
पूर्ण

अटल अंतरभूत व्योम update_समयr_mcck(व्योम)
अणु
	S390_lowcore.प्रणाली_समयr += S390_lowcore.last_update_समयr - S390_lowcore.निकास_समयr;
	S390_lowcore.user_समयr += S390_lowcore.निकास_समयr - S390_lowcore.mcck_enter_समयr;
	S390_lowcore.last_update_समयr = S390_lowcore.mcck_enter_समयr;
पूर्ण

#पूर्ण_अगर /* _S390_VTIME_H */
