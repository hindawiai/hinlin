<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Ptrace पूर्णांकerface test helper functions
 *
 * Copyright (C) 2015 Anshuman Khandual, IBM Corporation.
 */
#समावेश <पूर्णांकtypes.h>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <दो_स्मृति.h>
#समावेश <त्रुटिसं.स>
#समावेश <समय.स>
#समावेश <sys/ptrace.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/uपन.स>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <sys/संकेत.स>
#समावेश <sys/ipc.h>
#समावेश <sys/shm.h>
#समावेश <sys/user.h>
#समावेश <linux/elf.h>
#समावेश <linux/types.h>
#समावेश <linux/auxvec.h>
#समावेश "reg.h"
#समावेश "utils.h"

#घोषणा TEST_PASS 0
#घोषणा TEST_FAIL 1

काष्ठा fpr_regs अणु
	अचिन्हित दीर्घ fpr[32];
	अचिन्हित दीर्घ fpscr;
पूर्ण;

काष्ठा पंचांग_spr_regs अणु
	अचिन्हित दीर्घ पंचांग_tfhar;
	अचिन्हित दीर्घ पंचांग_texasr;
	अचिन्हित दीर्घ पंचांग_tfiar;
पूर्ण;

#अगर_अघोषित NT_PPC_TAR
#घोषणा NT_PPC_TAR	0x103
#घोषणा NT_PPC_PPR	0x104
#घोषणा NT_PPC_DSCR	0x105
#घोषणा NT_PPC_EBB	0x106
#घोषणा NT_PPC_PMU	0x107
#घोषणा NT_PPC_TM_CGPR	0x108
#घोषणा NT_PPC_TM_CFPR	0x109
#घोषणा NT_PPC_TM_CVMX	0x10a
#घोषणा NT_PPC_TM_CVSX	0x10b
#घोषणा NT_PPC_TM_SPR	0x10c
#घोषणा NT_PPC_TM_CTAR	0x10d
#घोषणा NT_PPC_TM_CPPR	0x10e
#घोषणा NT_PPC_TM_CDSCR	0x10f
#पूर्ण_अगर

/* Basic ptrace operations */
पूर्णांक start_trace(pid_t child)
अणु
	पूर्णांक ret;

	ret = ptrace(PTRACE_ATTACH, child, शून्य, शून्य);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_ATTACH) failed");
		वापस TEST_FAIL;
	पूर्ण
	ret = रुकोpid(child, शून्य, 0);
	अगर (ret != child) अणु
		लिखो_त्रुटि("waitpid() failed");
		वापस TEST_FAIL;
	पूर्ण
	वापस TEST_PASS;
पूर्ण

पूर्णांक stop_trace(pid_t child)
अणु
	पूर्णांक ret;

	ret = ptrace(PTRACE_DETACH, child, शून्य, शून्य);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_DETACH) failed");
		वापस TEST_FAIL;
	पूर्ण
	वापस TEST_PASS;
पूर्ण

पूर्णांक cont_trace(pid_t child)
अणु
	पूर्णांक ret;

	ret = ptrace(PTRACE_CONT, child, शून्य, शून्य);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_CONT) failed");
		वापस TEST_FAIL;
	पूर्ण
	वापस TEST_PASS;
पूर्ण

पूर्णांक ptrace_पढ़ो_regs(pid_t child, अचिन्हित दीर्घ type, अचिन्हित दीर्घ regs[],
		     पूर्णांक n)
अणु
	काष्ठा iovec iov;
	दीर्घ ret;

	FAIL_IF(start_trace(child));

	iov.iov_base = regs;
	iov.iov_len = n * माप(अचिन्हित दीर्घ);

	ret = ptrace(PTRACE_GETREGSET, child, type, &iov);
	अगर (ret)
		वापस ret;

	FAIL_IF(stop_trace(child));

	वापस TEST_PASS;
पूर्ण

दीर्घ ptrace_ग_लिखो_regs(pid_t child, अचिन्हित दीर्घ type, अचिन्हित दीर्घ regs[],
		       पूर्णांक n)
अणु
	काष्ठा iovec iov;
	दीर्घ ret;

	FAIL_IF(start_trace(child));

	iov.iov_base = regs;
	iov.iov_len = n * माप(अचिन्हित दीर्घ);

	ret = ptrace(PTRACE_SETREGSET, child, type, &iov);

	FAIL_IF(stop_trace(child));

	वापस ret;
पूर्ण

/* TAR, PPR, DSCR */
पूर्णांक show_tar_रेजिस्टरs(pid_t child, अचिन्हित दीर्घ *out)
अणु
	काष्ठा iovec iov;
	अचिन्हित दीर्घ *reg;
	पूर्णांक ret;

	reg = दो_स्मृति(माप(अचिन्हित दीर्घ));
	अगर (!reg) अणु
		लिखो_त्रुटि("malloc() failed");
		वापस TEST_FAIL;
	पूर्ण
	iov.iov_base = (u64 *) reg;
	iov.iov_len = माप(अचिन्हित दीर्घ);

	ret = ptrace(PTRACE_GETREGSET, child, NT_PPC_TAR, &iov);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_GETREGSET) failed");
		जाओ fail;
	पूर्ण
	अगर (out)
		out[0] = *reg;

	ret = ptrace(PTRACE_GETREGSET, child, NT_PPC_PPR, &iov);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_GETREGSET) failed");
		जाओ fail;
	पूर्ण
	अगर (out)
		out[1] = *reg;

	ret = ptrace(PTRACE_GETREGSET, child, NT_PPC_DSCR, &iov);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_GETREGSET) failed");
		जाओ fail;
	पूर्ण
	अगर (out)
		out[2] = *reg;

	मुक्त(reg);
	वापस TEST_PASS;
fail:
	मुक्त(reg);
	वापस TEST_FAIL;
पूर्ण

पूर्णांक ग_लिखो_tar_रेजिस्टरs(pid_t child, अचिन्हित दीर्घ tar,
		अचिन्हित दीर्घ ppr, अचिन्हित दीर्घ dscr)
अणु
	काष्ठा iovec iov;
	अचिन्हित दीर्घ *reg;
	पूर्णांक ret;

	reg = दो_स्मृति(माप(अचिन्हित दीर्घ));
	अगर (!reg) अणु
		लिखो_त्रुटि("malloc() failed");
		वापस TEST_FAIL;
	पूर्ण

	iov.iov_base = (u64 *) reg;
	iov.iov_len = माप(अचिन्हित दीर्घ);

	*reg = tar;
	ret = ptrace(PTRACE_SETREGSET, child, NT_PPC_TAR, &iov);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_SETREGSET) failed");
		जाओ fail;
	पूर्ण

	*reg = ppr;
	ret = ptrace(PTRACE_SETREGSET, child, NT_PPC_PPR, &iov);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_SETREGSET) failed");
		जाओ fail;
	पूर्ण

	*reg = dscr;
	ret = ptrace(PTRACE_SETREGSET, child, NT_PPC_DSCR, &iov);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_SETREGSET) failed");
		जाओ fail;
	पूर्ण

	मुक्त(reg);
	वापस TEST_PASS;
fail:
	मुक्त(reg);
	वापस TEST_FAIL;
पूर्ण

पूर्णांक show_पंचांग_checkpoपूर्णांकed_state(pid_t child, अचिन्हित दीर्घ *out)
अणु
	काष्ठा iovec iov;
	अचिन्हित दीर्घ *reg;
	पूर्णांक ret;

	reg = दो_स्मृति(माप(अचिन्हित दीर्घ));
	अगर (!reg) अणु
		लिखो_त्रुटि("malloc() failed");
		वापस TEST_FAIL;
	पूर्ण

	iov.iov_base = (u64 *) reg;
	iov.iov_len = माप(अचिन्हित दीर्घ);

	ret = ptrace(PTRACE_GETREGSET, child, NT_PPC_TM_CTAR, &iov);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_GETREGSET) failed");
		जाओ fail;
	पूर्ण
	अगर (out)
		out[0] = *reg;

	ret = ptrace(PTRACE_GETREGSET, child, NT_PPC_TM_CPPR, &iov);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_GETREGSET) failed");
		जाओ fail;
	पूर्ण
	अगर (out)
		out[1] = *reg;

	ret = ptrace(PTRACE_GETREGSET, child, NT_PPC_TM_CDSCR, &iov);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_GETREGSET) failed");
		जाओ fail;
	पूर्ण
	अगर (out)
		out[2] = *reg;

	मुक्त(reg);
	वापस TEST_PASS;

fail:
	मुक्त(reg);
	वापस TEST_FAIL;
पूर्ण

पूर्णांक ग_लिखो_ckpt_tar_रेजिस्टरs(pid_t child, अचिन्हित दीर्घ tar,
		अचिन्हित दीर्घ ppr, अचिन्हित दीर्घ dscr)
अणु
	काष्ठा iovec iov;
	अचिन्हित दीर्घ *reg;
	पूर्णांक ret;

	reg = दो_स्मृति(माप(अचिन्हित दीर्घ));
	अगर (!reg) अणु
		लिखो_त्रुटि("malloc() failed");
		वापस TEST_FAIL;
	पूर्ण

	iov.iov_base = (u64 *) reg;
	iov.iov_len = माप(अचिन्हित दीर्घ);

	*reg = tar;
	ret = ptrace(PTRACE_SETREGSET, child, NT_PPC_TM_CTAR, &iov);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_GETREGSET) failed");
		जाओ fail;
	पूर्ण

	*reg = ppr;
	ret = ptrace(PTRACE_SETREGSET, child, NT_PPC_TM_CPPR, &iov);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_GETREGSET) failed");
		जाओ fail;
	पूर्ण

	*reg = dscr;
	ret = ptrace(PTRACE_SETREGSET, child, NT_PPC_TM_CDSCR, &iov);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_GETREGSET) failed");
		जाओ fail;
	पूर्ण

	मुक्त(reg);
	वापस TEST_PASS;
fail:
	मुक्त(reg);
	वापस TEST_FAIL;
पूर्ण

/* FPR */
पूर्णांक show_fpr(pid_t child, अचिन्हित दीर्घ *fpr)
अणु
	काष्ठा fpr_regs *regs;
	पूर्णांक ret, i;

	regs = (काष्ठा fpr_regs *) दो_स्मृति(माप(काष्ठा fpr_regs));
	ret = ptrace(PTRACE_GETFPREGS, child, शून्य, regs);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_GETREGSET) failed");
		वापस TEST_FAIL;
	पूर्ण

	अगर (fpr) अणु
		क्रम (i = 0; i < 32; i++)
			fpr[i] = regs->fpr[i];
	पूर्ण
	वापस TEST_PASS;
पूर्ण

पूर्णांक ग_लिखो_fpr(pid_t child, अचिन्हित दीर्घ val)
अणु
	काष्ठा fpr_regs *regs;
	पूर्णांक ret, i;

	regs = (काष्ठा fpr_regs *) दो_स्मृति(माप(काष्ठा fpr_regs));
	ret = ptrace(PTRACE_GETFPREGS, child, शून्य, regs);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_GETREGSET) failed");
		वापस TEST_FAIL;
	पूर्ण

	क्रम (i = 0; i < 32; i++)
		regs->fpr[i] = val;

	ret = ptrace(PTRACE_SETFPREGS, child, शून्य, regs);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_GETREGSET) failed");
		वापस TEST_FAIL;
	पूर्ण
	वापस TEST_PASS;
पूर्ण

पूर्णांक show_ckpt_fpr(pid_t child, अचिन्हित दीर्घ *fpr)
अणु
	काष्ठा fpr_regs *regs;
	काष्ठा iovec iov;
	पूर्णांक ret, i;

	regs = (काष्ठा fpr_regs *) दो_स्मृति(माप(काष्ठा fpr_regs));
	iov.iov_base = regs;
	iov.iov_len = माप(काष्ठा fpr_regs);

	ret = ptrace(PTRACE_GETREGSET, child, NT_PPC_TM_CFPR, &iov);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_GETREGSET) failed");
		वापस TEST_FAIL;
	पूर्ण

	अगर (fpr) अणु
		क्रम (i = 0; i < 32; i++)
			fpr[i] = regs->fpr[i];
	पूर्ण

	वापस TEST_PASS;
पूर्ण

पूर्णांक ग_लिखो_ckpt_fpr(pid_t child, अचिन्हित दीर्घ val)
अणु
	काष्ठा fpr_regs *regs;
	काष्ठा iovec iov;
	पूर्णांक ret, i;

	regs = (काष्ठा fpr_regs *) दो_स्मृति(माप(काष्ठा fpr_regs));
	iov.iov_base = regs;
	iov.iov_len = माप(काष्ठा fpr_regs);

	ret = ptrace(PTRACE_GETREGSET, child, NT_PPC_TM_CFPR, &iov);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_GETREGSET) failed");
		वापस TEST_FAIL;
	पूर्ण

	क्रम (i = 0; i < 32; i++)
		regs->fpr[i] = val;

	ret = ptrace(PTRACE_SETREGSET, child, NT_PPC_TM_CFPR, &iov);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_GETREGSET) failed");
		वापस TEST_FAIL;
	पूर्ण
	वापस TEST_PASS;
पूर्ण

/* GPR */
पूर्णांक show_gpr(pid_t child, अचिन्हित दीर्घ *gpr)
अणु
	काष्ठा pt_regs *regs;
	पूर्णांक ret, i;

	regs = (काष्ठा pt_regs *) दो_स्मृति(माप(काष्ठा pt_regs));
	अगर (!regs) अणु
		लिखो_त्रुटि("malloc() failed");
		वापस TEST_FAIL;
	पूर्ण

	ret = ptrace(PTRACE_GETREGS, child, शून्य, regs);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_GETREGSET) failed");
		वापस TEST_FAIL;
	पूर्ण

	अगर (gpr) अणु
		क्रम (i = 14; i < 32; i++)
			gpr[i-14] = regs->gpr[i];
	पूर्ण

	वापस TEST_PASS;
पूर्ण

पूर्णांक ग_लिखो_gpr(pid_t child, अचिन्हित दीर्घ val)
अणु
	काष्ठा pt_regs *regs;
	पूर्णांक i, ret;

	regs = (काष्ठा pt_regs *) दो_स्मृति(माप(काष्ठा pt_regs));
	अगर (!regs) अणु
		लिखो_त्रुटि("malloc() failed");
		वापस TEST_FAIL;
	पूर्ण

	ret = ptrace(PTRACE_GETREGS, child, शून्य, regs);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_GETREGSET) failed");
		वापस TEST_FAIL;
	पूर्ण

	क्रम (i = 14; i < 32; i++)
		regs->gpr[i] = val;

	ret = ptrace(PTRACE_SETREGS, child, शून्य, regs);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_GETREGSET) failed");
		वापस TEST_FAIL;
	पूर्ण
	वापस TEST_PASS;
पूर्ण

पूर्णांक show_ckpt_gpr(pid_t child, अचिन्हित दीर्घ *gpr)
अणु
	काष्ठा pt_regs *regs;
	काष्ठा iovec iov;
	पूर्णांक ret, i;

	regs = (काष्ठा pt_regs *) दो_स्मृति(माप(काष्ठा pt_regs));
	अगर (!regs) अणु
		लिखो_त्रुटि("malloc() failed");
		वापस TEST_FAIL;
	पूर्ण

	iov.iov_base = (u64 *) regs;
	iov.iov_len = माप(काष्ठा pt_regs);

	ret = ptrace(PTRACE_GETREGSET, child, NT_PPC_TM_CGPR, &iov);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_GETREGSET) failed");
		वापस TEST_FAIL;
	पूर्ण

	अगर (gpr) अणु
		क्रम (i = 14; i < 32; i++)
			gpr[i-14] = regs->gpr[i];
	पूर्ण

	वापस TEST_PASS;
पूर्ण

पूर्णांक ग_लिखो_ckpt_gpr(pid_t child, अचिन्हित दीर्घ val)
अणु
	काष्ठा pt_regs *regs;
	काष्ठा iovec iov;
	पूर्णांक ret, i;

	regs = (काष्ठा pt_regs *) दो_स्मृति(माप(काष्ठा pt_regs));
	अगर (!regs) अणु
		लिखो_त्रुटि("malloc() failed\n");
		वापस TEST_FAIL;
	पूर्ण
	iov.iov_base = (u64 *) regs;
	iov.iov_len = माप(काष्ठा pt_regs);

	ret = ptrace(PTRACE_GETREGSET, child, NT_PPC_TM_CGPR, &iov);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_GETREGSET) failed");
		वापस TEST_FAIL;
	पूर्ण

	क्रम (i = 14; i < 32; i++)
		regs->gpr[i] = val;

	ret = ptrace(PTRACE_SETREGSET, child, NT_PPC_TM_CGPR, &iov);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_GETREGSET) failed");
		वापस TEST_FAIL;
	पूर्ण
	वापस TEST_PASS;
पूर्ण

/* VMX */
पूर्णांक show_vmx(pid_t child, अचिन्हित दीर्घ vmx[][2])
अणु
	पूर्णांक ret;

	ret = ptrace(PTRACE_GETVRREGS, child, 0, vmx);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_GETVRREGS) failed");
		वापस TEST_FAIL;
	पूर्ण
	वापस TEST_PASS;
पूर्ण

पूर्णांक show_vmx_ckpt(pid_t child, अचिन्हित दीर्घ vmx[][2])
अणु
	अचिन्हित दीर्घ regs[34][2];
	काष्ठा iovec iov;
	पूर्णांक ret;

	iov.iov_base = (u64 *) regs;
	iov.iov_len = माप(regs);
	ret = ptrace(PTRACE_GETREGSET, child, NT_PPC_TM_CVMX, &iov);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_GETREGSET, NT_PPC_TM_CVMX) failed");
		वापस TEST_FAIL;
	पूर्ण
	स_नकल(vmx, regs, माप(regs));
	वापस TEST_PASS;
पूर्ण


पूर्णांक ग_लिखो_vmx(pid_t child, अचिन्हित दीर्घ vmx[][2])
अणु
	पूर्णांक ret;

	ret = ptrace(PTRACE_SETVRREGS, child, 0, vmx);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_SETVRREGS) failed");
		वापस TEST_FAIL;
	पूर्ण
	वापस TEST_PASS;
पूर्ण

पूर्णांक ग_लिखो_vmx_ckpt(pid_t child, अचिन्हित दीर्घ vmx[][2])
अणु
	अचिन्हित दीर्घ regs[34][2];
	काष्ठा iovec iov;
	पूर्णांक ret;

	स_नकल(regs, vmx, माप(regs));
	iov.iov_base = (u64 *) regs;
	iov.iov_len = माप(regs);
	ret = ptrace(PTRACE_SETREGSET, child, NT_PPC_TM_CVMX, &iov);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_SETREGSET, NT_PPC_TM_CVMX) failed");
		वापस TEST_FAIL;
	पूर्ण
	वापस TEST_PASS;
पूर्ण

/* VSX */
पूर्णांक show_vsx(pid_t child, अचिन्हित दीर्घ *vsx)
अणु
	पूर्णांक ret;

	ret = ptrace(PTRACE_GETVSRREGS, child, 0, vsx);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_GETVSRREGS) failed");
		वापस TEST_FAIL;
	पूर्ण
	वापस TEST_PASS;
पूर्ण

पूर्णांक show_vsx_ckpt(pid_t child, अचिन्हित दीर्घ *vsx)
अणु
	अचिन्हित दीर्घ regs[32];
	काष्ठा iovec iov;
	पूर्णांक ret;

	iov.iov_base = (u64 *) regs;
	iov.iov_len = माप(regs);
	ret = ptrace(PTRACE_GETREGSET, child, NT_PPC_TM_CVSX, &iov);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_GETREGSET, NT_PPC_TM_CVSX) failed");
		वापस TEST_FAIL;
	पूर्ण
	स_नकल(vsx, regs, माप(regs));
	वापस TEST_PASS;
पूर्ण

पूर्णांक ग_लिखो_vsx(pid_t child, अचिन्हित दीर्घ *vsx)
अणु
	पूर्णांक ret;

	ret = ptrace(PTRACE_SETVSRREGS, child, 0, vsx);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_SETVSRREGS) failed");
		वापस TEST_FAIL;
	पूर्ण
	वापस TEST_PASS;
पूर्ण

पूर्णांक ग_लिखो_vsx_ckpt(pid_t child, अचिन्हित दीर्घ *vsx)
अणु
	अचिन्हित दीर्घ regs[32];
	काष्ठा iovec iov;
	पूर्णांक ret;

	स_नकल(regs, vsx, माप(regs));
	iov.iov_base = (u64 *) regs;
	iov.iov_len = माप(regs);
	ret = ptrace(PTRACE_SETREGSET, child, NT_PPC_TM_CVSX, &iov);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_SETREGSET, NT_PPC_TM_CVSX) failed");
		वापस TEST_FAIL;
	पूर्ण
	वापस TEST_PASS;
पूर्ण

/* TM SPR */
पूर्णांक show_पंचांग_spr(pid_t child, काष्ठा पंचांग_spr_regs *out)
अणु
	काष्ठा पंचांग_spr_regs *regs;
	काष्ठा iovec iov;
	पूर्णांक ret;

	regs = (काष्ठा पंचांग_spr_regs *) दो_स्मृति(माप(काष्ठा पंचांग_spr_regs));
	अगर (!regs) अणु
		लिखो_त्रुटि("malloc() failed");
		वापस TEST_FAIL;
	पूर्ण

	iov.iov_base = (u64 *) regs;
	iov.iov_len = माप(काष्ठा पंचांग_spr_regs);

	ret = ptrace(PTRACE_GETREGSET, child, NT_PPC_TM_SPR, &iov);
	अगर (ret) अणु
		लिखो_त्रुटि("ptrace(PTRACE_GETREGSET) failed");
		वापस TEST_FAIL;
	पूर्ण

	अगर (out)
		स_नकल(out, regs, माप(काष्ठा पंचांग_spr_regs));

	वापस TEST_PASS;
पूर्ण



/* Analyse TEXASR after TM failure */
अंतरभूत अचिन्हित दीर्घ get_tfiar(व्योम)
अणु
	अचिन्हित दीर्घ ret;

	यंत्र अस्थिर("mfspr %0,%1" : "=r" (ret) : "i" (SPRN_TFIAR));
	वापस ret;
पूर्ण

व्योम analyse_texasr(अचिन्हित दीर्घ texasr)
अणु
	म_लिखो("TEXASR: %16lx\t", texasr);

	अगर (texasr & TEXASR_FP)
		म_लिखो("TEXASR_FP  ");

	अगर (texasr & TEXASR_DA)
		म_लिखो("TEXASR_DA  ");

	अगर (texasr & TEXASR_NO)
		म_लिखो("TEXASR_NO  ");

	अगर (texasr & TEXASR_FO)
		म_लिखो("TEXASR_FO  ");

	अगर (texasr & TEXASR_SIC)
		म_लिखो("TEXASR_SIC  ");

	अगर (texasr & TEXASR_NTC)
		म_लिखो("TEXASR_NTC  ");

	अगर (texasr & TEXASR_TC)
		म_लिखो("TEXASR_TC  ");

	अगर (texasr & TEXASR_TIC)
		म_लिखो("TEXASR_TIC  ");

	अगर (texasr & TEXASR_IC)
		म_लिखो("TEXASR_IC  ");

	अगर (texasr & TEXASR_IFC)
		म_लिखो("TEXASR_IFC  ");

	अगर (texasr & TEXASR_ABT)
		म_लिखो("TEXASR_ABT  ");

	अगर (texasr & TEXASR_SPD)
		म_लिखो("TEXASR_SPD  ");

	अगर (texasr & TEXASR_HV)
		म_लिखो("TEXASR_HV  ");

	अगर (texasr & TEXASR_PR)
		म_लिखो("TEXASR_PR  ");

	अगर (texasr & TEXASR_FS)
		म_लिखो("TEXASR_FS  ");

	अगर (texasr & TEXASR_TE)
		म_लिखो("TEXASR_TE  ");

	अगर (texasr & TEXASR_ROT)
		म_लिखो("TEXASR_ROT  ");

	म_लिखो("TFIAR :%lx\n", get_tfiar());
पूर्ण

व्योम store_gpr(अचिन्हित दीर्घ *addr);
व्योम store_fpr(भग्न *addr);
