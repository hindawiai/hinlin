<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Jump label s390 support
 *
 * Copyright IBM Corp. 2011
 * Author(s): Jan Glauber <jang@linux.vnet.ibm.com>
 */
#समावेश <linux/uaccess.h>
#समावेश <linux/stop_machine.h>
#समावेश <linux/jump_label.h>
#समावेश <यंत्र/ipl.h>

काष्ठा insn अणु
	u16 opcode;
	s32 offset;
पूर्ण __packed;

अटल व्योम jump_label_make_nop(काष्ठा jump_entry *entry, काष्ठा insn *insn)
अणु
	/* brcl 0,offset */
	insn->opcode = 0xc004;
	insn->offset = (jump_entry_target(entry) - jump_entry_code(entry)) >> 1;
पूर्ण

अटल व्योम jump_label_make_branch(काष्ठा jump_entry *entry, काष्ठा insn *insn)
अणु
	/* brcl 15,offset */
	insn->opcode = 0xc0f4;
	insn->offset = (jump_entry_target(entry) - jump_entry_code(entry)) >> 1;
पूर्ण

अटल व्योम jump_label_bug(काष्ठा jump_entry *entry, काष्ठा insn *expected,
			   काष्ठा insn *new)
अणु
	अचिन्हित अक्षर *ipc = (अचिन्हित अक्षर *)jump_entry_code(entry);
	अचिन्हित अक्षर *ipe = (अचिन्हित अक्षर *)expected;
	अचिन्हित अक्षर *ipn = (अचिन्हित अक्षर *)new;

	pr_emerg("Jump label code mismatch at %pS [%p]\n", ipc, ipc);
	pr_emerg("Found:    %6ph\n", ipc);
	pr_emerg("Expected: %6ph\n", ipe);
	pr_emerg("New:      %6ph\n", ipn);
	panic("Corrupted kernel text");
पूर्ण

अटल काष्ठा insn orignop = अणु
	.opcode = 0xc004,
	.offset = JUMP_LABEL_NOP_OFFSET >> 1,
पूर्ण;

अटल व्योम __jump_label_transक्रमm(काष्ठा jump_entry *entry,
				   क्रमागत jump_label_type type,
				   पूर्णांक init)
अणु
	व्योम *code = (व्योम *)jump_entry_code(entry);
	काष्ठा insn old, new;

	अगर (type == JUMP_LABEL_JMP) अणु
		jump_label_make_nop(entry, &old);
		jump_label_make_branch(entry, &new);
	पूर्ण अन्यथा अणु
		jump_label_make_branch(entry, &old);
		jump_label_make_nop(entry, &new);
	पूर्ण
	अगर (init) अणु
		अगर (स_भेद(code, &orignop, माप(orignop)))
			jump_label_bug(entry, &orignop, &new);
	पूर्ण अन्यथा अणु
		अगर (स_भेद(code, &old, माप(old)))
			jump_label_bug(entry, &old, &new);
	पूर्ण
	s390_kernel_ग_लिखो(code, &new, माप(new));
पूर्ण

अटल व्योम __jump_label_sync(व्योम *dummy)
अणु
पूर्ण

व्योम arch_jump_label_transक्रमm(काष्ठा jump_entry *entry,
			       क्रमागत jump_label_type type)
अणु
	__jump_label_transक्रमm(entry, type, 0);
	smp_call_function(__jump_label_sync, शून्य, 1);
पूर्ण

व्योम arch_jump_label_transक्रमm_अटल(काष्ठा jump_entry *entry,
				      क्रमागत jump_label_type type)
अणु
	__jump_label_transक्रमm(entry, type, 1);
पूर्ण
