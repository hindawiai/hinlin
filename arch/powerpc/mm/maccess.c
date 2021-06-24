<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/uaccess.h>
#समावेश <linux/kernel.h>

#समावेश <यंत्र/disassemble.h>
#समावेश <यंत्र/inst.h>
#समावेश <यंत्र/ppc-opcode.h>

bool copy_from_kernel_nofault_allowed(स्थिर व्योम *unsafe_src, माप_प्रकार size)
अणु
	वापस is_kernel_addr((अचिन्हित दीर्घ)unsafe_src);
पूर्ण

पूर्णांक copy_inst_from_kernel_nofault(काष्ठा ppc_inst *inst, काष्ठा ppc_inst *src)
अणु
	अचिन्हित पूर्णांक val, suffix;
	पूर्णांक err;

	err = copy_from_kernel_nofault(&val, src, माप(val));
	अगर (err)
		वापस err;
	अगर (IS_ENABLED(CONFIG_PPC64) && get_op(val) == OP_PREFIX) अणु
		err = copy_from_kernel_nofault(&suffix, (व्योम *)src + 4, 4);
		*inst = ppc_inst_prefix(val, suffix);
	पूर्ण अन्यथा अणु
		*inst = ppc_inst(val);
	पूर्ण
	वापस err;
पूर्ण
