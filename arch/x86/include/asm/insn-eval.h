<शैली गुरु>
#अगर_अघोषित _ASM_X86_INSN_EVAL_H
#घोषणा _ASM_X86_INSN_EVAL_H
/*
 * A collection of utility functions क्रम x86 inकाष्ठाion analysis to be
 * used in a kernel context. Useful when, क्रम instance, making sense
 * of the रेजिस्टरs indicated by opeअक्रमs.
 */

#समावेश <linux/compiler.h>
#समावेश <linux/bug.h>
#समावेश <linux/err.h>
#समावेश <यंत्र/ptrace.h>

#घोषणा INSN_CODE_SEG_ADDR_SZ(params) ((params >> 4) & 0xf)
#घोषणा INSN_CODE_SEG_OPND_SZ(params) (params & 0xf)
#घोषणा INSN_CODE_SEG_PARAMS(oper_sz, addr_sz) (oper_sz | (addr_sz << 4))

bool insn_has_rep_prefix(काष्ठा insn *insn);
व्योम __user *insn_get_addr_ref(काष्ठा insn *insn, काष्ठा pt_regs *regs);
पूर्णांक insn_get_modrm_rm_off(काष्ठा insn *insn, काष्ठा pt_regs *regs);
पूर्णांक insn_get_modrm_reg_off(काष्ठा insn *insn, काष्ठा pt_regs *regs);
अचिन्हित दीर्घ insn_get_seg_base(काष्ठा pt_regs *regs, पूर्णांक seg_reg_idx);
पूर्णांक insn_get_code_seg_params(काष्ठा pt_regs *regs);
पूर्णांक insn_fetch_from_user(काष्ठा pt_regs *regs,
			 अचिन्हित अक्षर buf[MAX_INSN_SIZE]);
पूर्णांक insn_fetch_from_user_inatomic(काष्ठा pt_regs *regs,
				  अचिन्हित अक्षर buf[MAX_INSN_SIZE]);
bool insn_decode_from_regs(काष्ठा insn *insn, काष्ठा pt_regs *regs,
			   अचिन्हित अक्षर buf[MAX_INSN_SIZE], पूर्णांक buf_size);

#पूर्ण_अगर /* _ASM_X86_INSN_EVAL_H */
