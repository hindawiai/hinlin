<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <मानकघोष.स>
#समावेश <संकेत.स>
#समावेश <poll.h>
#समावेश <sys/mman.h>
#समावेश <sys/user.h>
#घोषणा __FRAME_OFFSETS
#समावेश <linux/ptrace.h>
#समावेश <यंत्र/types.h>

#घोषणा DEFINE(sym, val) \
	यंत्र अस्थिर("\n->" #sym " %0 " #val : : "i" (val))

#घोषणा DEFINE_LONGS(sym, val) \
	यंत्र अस्थिर("\n->" #sym " %0 " #val : : "i" (val/माप(अचिन्हित दीर्घ)))

व्योम foo(व्योम)
अणु
#अगर_घोषित __i386__
	DEFINE_LONGS(HOST_FP_SIZE, माप(काष्ठा user_fpregs_काष्ठा));
	DEFINE_LONGS(HOST_FPX_SIZE, माप(काष्ठा user_fpxregs_काष्ठा));

	DEFINE(HOST_IP, EIP);
	DEFINE(HOST_SP, UESP);
	DEFINE(HOST_EFLAGS, EFL);
	DEFINE(HOST_AX, EAX);
	DEFINE(HOST_BX, EBX);
	DEFINE(HOST_CX, ECX);
	DEFINE(HOST_DX, EDX);
	DEFINE(HOST_SI, ESI);
	DEFINE(HOST_DI, EDI);
	DEFINE(HOST_BP, EBP);
	DEFINE(HOST_CS, CS);
	DEFINE(HOST_SS, SS);
	DEFINE(HOST_DS, DS);
	DEFINE(HOST_FS, FS);
	DEFINE(HOST_ES, ES);
	DEFINE(HOST_GS, GS);
	DEFINE(HOST_ORIG_AX, ORIG_EAX);
#अन्यथा
#अगर_घोषित FP_XSTATE_MAGIC1
	DEFINE_LONGS(HOST_FP_SIZE, 2696);
#अन्यथा
	DEFINE(HOST_FP_SIZE, माप(काष्ठा _fpstate) / माप(अचिन्हित दीर्घ));
#पूर्ण_अगर
	DEFINE_LONGS(HOST_BX, RBX);
	DEFINE_LONGS(HOST_CX, RCX);
	DEFINE_LONGS(HOST_DI, RDI);
	DEFINE_LONGS(HOST_SI, RSI);
	DEFINE_LONGS(HOST_DX, RDX);
	DEFINE_LONGS(HOST_BP, RBP);
	DEFINE_LONGS(HOST_AX, RAX);
	DEFINE_LONGS(HOST_R8, R8);
	DEFINE_LONGS(HOST_R9, R9);
	DEFINE_LONGS(HOST_R10, R10);
	DEFINE_LONGS(HOST_R11, R11);
	DEFINE_LONGS(HOST_R12, R12);
	DEFINE_LONGS(HOST_R13, R13);
	DEFINE_LONGS(HOST_R14, R14);
	DEFINE_LONGS(HOST_R15, R15);
	DEFINE_LONGS(HOST_ORIG_AX, ORIG_RAX);
	DEFINE_LONGS(HOST_CS, CS);
	DEFINE_LONGS(HOST_SS, SS);
	DEFINE_LONGS(HOST_EFLAGS, EFLAGS);
#अगर 0
	DEFINE_LONGS(HOST_FS, FS);
	DEFINE_LONGS(HOST_GS, GS);
	DEFINE_LONGS(HOST_DS, DS);
	DEFINE_LONGS(HOST_ES, ES);
#पूर्ण_अगर

	DEFINE_LONGS(HOST_IP, RIP);
	DEFINE_LONGS(HOST_SP, RSP);
#पूर्ण_अगर

	DEFINE(UM_FRAME_SIZE, माप(काष्ठा user_regs_काष्ठा));
	DEFINE(UM_POLLIN, POLLIN);
	DEFINE(UM_POLLPRI, POLLPRI);
	DEFINE(UM_POLLOUT, POLLOUT);

	DEFINE(UM_PROT_READ, PROT_READ);
	DEFINE(UM_PROT_WRITE, PROT_WRITE);
	DEFINE(UM_PROT_EXEC, PROT_EXEC);
पूर्ण
