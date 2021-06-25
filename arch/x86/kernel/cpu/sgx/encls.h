<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _X86_ENCLS_H
#घोषणा _X86_ENCLS_H

#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/rwsem.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/यंत्र.h>
#समावेश <यंत्र/traps.h>
#समावेश "sgx.h"

/**
 * ENCLS_FAULT_FLAG - flag signअगरying an ENCLS वापस code is a trapnr
 *
 * ENCLS has its own (positive value) error codes and also generates
 * ENCLS specअगरic #GP and #PF faults.  And the ENCLS values get munged
 * with प्रणाली error codes as everything percolates back up the stack.
 * Unक्रमtunately (क्रम us), we need to precisely identअगरy each unique
 * error code, e.g. the action taken अगर EWB fails varies based on the
 * type of fault and on the exact SGX error code, i.e. we can't simply
 * convert all faults to -EFAULT.
 *
 * To make all three error types coexist, we set bit 30 to identअगरy an
 * ENCLS fault.  Bit 31 (technically bits N:31) is used to dअगरferentiate
 * between positive (faults and SGX error codes) and negative (प्रणाली
 * error codes) values.
 */
#घोषणा ENCLS_FAULT_FLAG 0x40000000

/* Retrieve the encoded trapnr from the specअगरied वापस code. */
#घोषणा ENCLS_TRAPNR(r) ((r) & ~ENCLS_FAULT_FLAG)

/* Issue a WARN() about an ENCLS function. */
#घोषणा ENCLS_WARN(r, name) अणु						  \
	करो अणु								  \
		पूर्णांक _r = (r);						  \
		WARN_ONCE(_r, "%s returned %d (0x%x)\n", (name), _r, _r); \
	पूर्ण जबतक (0);							  \
पूर्ण

/*
 * encls_faulted() - Check अगर an ENCLS leaf faulted given an error code
 * @ret:	the वापस value of an ENCLS leaf function call
 *
 * Return:
 * - true:	ENCLS leaf faulted.
 * - false:	Otherwise.
 */
अटल अंतरभूत bool encls_faulted(पूर्णांक ret)
अणु
	वापस ret & ENCLS_FAULT_FLAG;
पूर्ण

/**
 * encls_failed() - Check अगर an ENCLS function failed
 * @ret:	the वापस value of an ENCLS function call
 *
 * Check अगर an ENCLS function failed. This happens when the function causes a
 * fault that is not caused by an EPCM conflict or when the function वापसs a
 * non-zero value.
 */
अटल अंतरभूत bool encls_failed(पूर्णांक ret)
अणु
	अगर (encls_faulted(ret))
		वापस ENCLS_TRAPNR(ret) != X86_TRAP_PF;

	वापस !!ret;
पूर्ण

/**
 * __encls_ret_N - encode an ENCLS function that वापसs an error code in EAX
 * @rax:	function number
 * @inमाला_दो:	यंत्र inमाला_दो क्रम the function
 *
 * Emit assembly क्रम an ENCLS function that वापसs an error code, e.g. EREMOVE.
 * And because SGX isn't complex enough as it is, function that वापस an error
 * code also modअगरy flags.
 *
 * Return:
 *	0 on success,
 *	SGX error code on failure
 */
#घोषणा __encls_ret_N(rax, inमाला_दो...)				\
	(अणु							\
	पूर्णांक ret;						\
	यंत्र अस्थिर(						\
	"1: .byte 0x0f, 0x01, 0xcf;\n\t"			\
	"2:\n"							\
	".section .fixup,\"ax\"\n"				\
	"3: orl $"__stringअगरy(ENCLS_FAULT_FLAG)",%%eax\n"	\
	"   jmp 2b\n"						\
	".previous\n"						\
	_ASM_EXTABLE_FAULT(1b, 3b)				\
	: "=a"(ret)						\
	: "a"(rax), inमाला_दो					\
	: "memory", "cc");					\
	ret;							\
	पूर्ण)

#घोषणा __encls_ret_1(rax, rcx)		\
	(अणु				\
	__encls_ret_N(rax, "c"(rcx));	\
	पूर्ण)

#घोषणा __encls_ret_2(rax, rbx, rcx)		\
	(अणु					\
	__encls_ret_N(rax, "b"(rbx), "c"(rcx));	\
	पूर्ण)

#घोषणा __encls_ret_3(rax, rbx, rcx, rdx)			\
	(अणु							\
	__encls_ret_N(rax, "b"(rbx), "c"(rcx), "d"(rdx));	\
	पूर्ण)

/**
 * __encls_N - encode an ENCLS function that करोesn't वापस an error code
 * @rax:	function number
 * @rbx_out:	optional output variable
 * @inमाला_दो:	यंत्र inमाला_दो क्रम the function
 *
 * Emit assembly क्रम an ENCLS function that करोes not वापस an error code, e.g.
 * ECREATE.  Leaves without error codes either succeed or fault.  @rbx_out is an
 * optional parameter क्रम use by EDGBRD, which वापसs the requested value in
 * RBX.
 *
 * Return:
 *   0 on success,
 *   trapnr with ENCLS_FAULT_FLAG set on fault
 */
#घोषणा __encls_N(rax, rbx_out, inमाला_दो...)			\
	(अणु							\
	पूर्णांक ret;						\
	यंत्र अस्थिर(						\
	"1: .byte 0x0f, 0x01, 0xcf;\n\t"			\
	"   xor %%eax,%%eax;\n"					\
	"2:\n"							\
	".section .fixup,\"ax\"\n"				\
	"3: orl $"__stringअगरy(ENCLS_FAULT_FLAG)",%%eax\n"	\
	"   jmp 2b\n"						\
	".previous\n"						\
	_ASM_EXTABLE_FAULT(1b, 3b)				\
	: "=a"(ret), "=b"(rbx_out)				\
	: "a"(rax), inमाला_दो					\
	: "memory");						\
	ret;							\
	पूर्ण)

#घोषणा __encls_2(rax, rbx, rcx)				\
	(अणु							\
	अचिन्हित दीर्घ ign_rbx_out;				\
	__encls_N(rax, ign_rbx_out, "b"(rbx), "c"(rcx));	\
	पूर्ण)

#घोषणा __encls_1_1(rax, data, rcx)			\
	(अणु						\
	अचिन्हित दीर्घ rbx_out;				\
	पूर्णांक ret = __encls_N(rax, rbx_out, "c"(rcx));	\
	अगर (!ret)					\
		data = rbx_out;				\
	ret;						\
	पूर्ण)

अटल अंतरभूत पूर्णांक __ecreate(काष्ठा sgx_pageinfo *pginfo, व्योम *secs)
अणु
	वापस __encls_2(ECREATE, pginfo, secs);
पूर्ण

अटल अंतरभूत पूर्णांक __eextend(व्योम *secs, व्योम *addr)
अणु
	वापस __encls_2(EEXTEND, secs, addr);
पूर्ण

अटल अंतरभूत पूर्णांक __eadd(काष्ठा sgx_pageinfo *pginfo, व्योम *addr)
अणु
	वापस __encls_2(EADD, pginfo, addr);
पूर्ण

अटल अंतरभूत पूर्णांक __einit(व्योम *sigकाष्ठा, व्योम *token, व्योम *secs)
अणु
	वापस __encls_ret_3(EINIT, sigकाष्ठा, secs, token);
पूर्ण

अटल अंतरभूत पूर्णांक __eहटाओ(व्योम *addr)
अणु
	वापस __encls_ret_1(EREMOVE, addr);
पूर्ण

अटल अंतरभूत पूर्णांक __edbgwr(व्योम *addr, अचिन्हित दीर्घ *data)
अणु
	वापस __encls_2(EDGBWR, *data, addr);
पूर्ण

अटल अंतरभूत पूर्णांक __edbgrd(व्योम *addr, अचिन्हित दीर्घ *data)
अणु
	वापस __encls_1_1(EDGBRD, *data, addr);
पूर्ण

अटल अंतरभूत पूर्णांक __etrack(व्योम *addr)
अणु
	वापस __encls_ret_1(ETRACK, addr);
पूर्ण

अटल अंतरभूत पूर्णांक __eldu(काष्ठा sgx_pageinfo *pginfo, व्योम *addr,
			 व्योम *va)
अणु
	वापस __encls_ret_3(ELDU, pginfo, addr, va);
पूर्ण

अटल अंतरभूत पूर्णांक __eblock(व्योम *addr)
अणु
	वापस __encls_ret_1(EBLOCK, addr);
पूर्ण

अटल अंतरभूत पूर्णांक __epa(व्योम *addr)
अणु
	अचिन्हित दीर्घ rbx = SGX_PAGE_TYPE_VA;

	वापस __encls_2(EPA, rbx, addr);
पूर्ण

अटल अंतरभूत पूर्णांक __ewb(काष्ठा sgx_pageinfo *pginfo, व्योम *addr,
			व्योम *va)
अणु
	वापस __encls_ret_3(EWB, pginfo, addr, va);
पूर्ण

#पूर्ण_अगर /* _X86_ENCLS_H */
