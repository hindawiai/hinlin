<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __S390_ASM_SIGP_H
#घोषणा __S390_ASM_SIGP_H

/* SIGP order codes */
#घोषणा SIGP_SENSE		      1
#घोषणा SIGP_EXTERNAL_CALL	      2
#घोषणा SIGP_EMERGENCY_SIGNAL	      3
#घोषणा SIGP_START		      4
#घोषणा SIGP_STOP		      5
#घोषणा SIGP_RESTART		      6
#घोषणा SIGP_STOP_AND_STORE_STATUS    9
#घोषणा SIGP_INITIAL_CPU_RESET	     11
#घोषणा SIGP_CPU_RESET		     12
#घोषणा SIGP_SET_PREFIX		     13
#घोषणा SIGP_STORE_STATUS_AT_ADDRESS 14
#घोषणा SIGP_SET_ARCHITECTURE	     18
#घोषणा SIGP_COND_EMERGENCY_SIGNAL   19
#घोषणा SIGP_SENSE_RUNNING	     21
#घोषणा SIGP_SET_MULTI_THREADING     22
#घोषणा SIGP_STORE_ADDITIONAL_STATUS 23

/* SIGP condition codes */
#घोषणा SIGP_CC_ORDER_CODE_ACCEPTED 0
#घोषणा SIGP_CC_STATUS_STORED	    1
#घोषणा SIGP_CC_BUSY		    2
#घोषणा SIGP_CC_NOT_OPERATIONAL	    3

/* SIGP cpu status bits */

#घोषणा SIGP_STATUS_INVALID_ORDER	0x00000002UL
#घोषणा SIGP_STATUS_CHECK_STOP		0x00000010UL
#घोषणा SIGP_STATUS_STOPPED		0x00000040UL
#घोषणा SIGP_STATUS_EXT_CALL_PENDING	0x00000080UL
#घोषणा SIGP_STATUS_INVALID_PARAMETER	0x00000100UL
#घोषणा SIGP_STATUS_INCORRECT_STATE	0x00000200UL
#घोषणा SIGP_STATUS_NOT_RUNNING		0x00000400UL

#अगर_अघोषित __ASSEMBLY__

अटल अंतरभूत पूर्णांक ____pcpu_sigp(u16 addr, u8 order, अचिन्हित दीर्घ parm,
				u32 *status)
अणु
	रेजिस्टर अचिन्हित दीर्घ reg1 यंत्र ("1") = parm;
	पूर्णांक cc;

	यंत्र अस्थिर(
		"	sigp	%1,%2,0(%3)\n"
		"	ipm	%0\n"
		"	srl	%0,28\n"
		: "=d" (cc), "+d" (reg1) : "d" (addr), "a" (order) : "cc");
	*status = reg1;
	वापस cc;
पूर्ण

अटल अंतरभूत पूर्णांक __pcpu_sigp(u16 addr, u8 order, अचिन्हित दीर्घ parm,
			      u32 *status)
अणु
	u32 _status;
	पूर्णांक cc;

	cc = ____pcpu_sigp(addr, order, parm, &_status);
	अगर (status && cc == SIGP_CC_STATUS_STORED)
		*status = _status;
	वापस cc;
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* __S390_ASM_SIGP_H */
