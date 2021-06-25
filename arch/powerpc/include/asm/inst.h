<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_POWERPC_INST_H
#घोषणा _ASM_POWERPC_INST_H

#समावेश <यंत्र/ppc-opcode.h>

#अगर_घोषित CONFIG_PPC64

#घोषणा ___get_user_instr(gu_op, dest, ptr)				\
(अणु									\
	दीर्घ __gui_ret = 0;						\
	अचिन्हित दीर्घ __gui_ptr = (अचिन्हित दीर्घ)ptr;			\
	काष्ठा ppc_inst __gui_inst;					\
	अचिन्हित पूर्णांक __prefix, __suffix;				\
	__gui_ret = gu_op(__prefix, (अचिन्हित पूर्णांक __user *)__gui_ptr);	\
	अगर (__gui_ret == 0) अणु						\
		अगर ((__prefix >> 26) == OP_PREFIX) अणु			\
			__gui_ret = gu_op(__suffix,			\
				(अचिन्हित पूर्णांक __user *)__gui_ptr + 1);	\
			__gui_inst = ppc_inst_prefix(__prefix,		\
						     __suffix);		\
		पूर्ण अन्यथा अणु						\
			__gui_inst = ppc_inst(__prefix);		\
		पूर्ण							\
		अगर (__gui_ret == 0)					\
			(dest) = __gui_inst;				\
	पूर्ण								\
	__gui_ret;							\
पूर्ण)
#अन्यथा /* !CONFIG_PPC64 */
#घोषणा ___get_user_instr(gu_op, dest, ptr)				\
	gu_op((dest).val, (u32 __user *)(ptr))
#पूर्ण_अगर /* CONFIG_PPC64 */

#घोषणा get_user_instr(x, ptr) \
	___get_user_instr(get_user, x, ptr)

#घोषणा __get_user_instr(x, ptr) \
	___get_user_instr(__get_user, x, ptr)

/*
 * Inकाष्ठाion data type क्रम POWER
 */

काष्ठा ppc_inst अणु
	u32 val;
#अगर_घोषित CONFIG_PPC64
	u32 suffix;
#पूर्ण_अगर
पूर्ण __packed;

अटल अंतरभूत u32 ppc_inst_val(काष्ठा ppc_inst x)
अणु
	वापस x.val;
पूर्ण

अटल अंतरभूत पूर्णांक ppc_inst_primary_opcode(काष्ठा ppc_inst x)
अणु
	वापस ppc_inst_val(x) >> 26;
पूर्ण

#अगर_घोषित CONFIG_PPC64
#घोषणा ppc_inst(x) ((काष्ठा ppc_inst)अणु .val = (x), .suffix = 0xff पूर्ण)

#घोषणा ppc_inst_prefix(x, y) ((काष्ठा ppc_inst)अणु .val = (x), .suffix = (y) पूर्ण)

अटल अंतरभूत u32 ppc_inst_suffix(काष्ठा ppc_inst x)
अणु
	वापस x.suffix;
पूर्ण

अटल अंतरभूत bool ppc_inst_prefixed(काष्ठा ppc_inst x)
अणु
	वापस (ppc_inst_primary_opcode(x) == 1) && ppc_inst_suffix(x) != 0xff;
पूर्ण

अटल अंतरभूत काष्ठा ppc_inst ppc_inst_swab(काष्ठा ppc_inst x)
अणु
	वापस ppc_inst_prefix(swab32(ppc_inst_val(x)),
			       swab32(ppc_inst_suffix(x)));
पूर्ण

अटल अंतरभूत काष्ठा ppc_inst ppc_inst_पढ़ो(स्थिर काष्ठा ppc_inst *ptr)
अणु
	u32 val, suffix;

	val = *(u32 *)ptr;
	अगर ((val >> 26) == OP_PREFIX) अणु
		suffix = *((u32 *)ptr + 1);
		वापस ppc_inst_prefix(val, suffix);
	पूर्ण अन्यथा अणु
		वापस ppc_inst(val);
	पूर्ण
पूर्ण

अटल अंतरभूत bool ppc_inst_equal(काष्ठा ppc_inst x, काष्ठा ppc_inst y)
अणु
	वापस *(u64 *)&x == *(u64 *)&y;
पूर्ण

#अन्यथा

#घोषणा ppc_inst(x) ((काष्ठा ppc_inst)अणु .val = x पूर्ण)

#घोषणा ppc_inst_prefix(x, y) ppc_inst(x)

अटल अंतरभूत bool ppc_inst_prefixed(काष्ठा ppc_inst x)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत u32 ppc_inst_suffix(काष्ठा ppc_inst x)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा ppc_inst ppc_inst_swab(काष्ठा ppc_inst x)
अणु
	वापस ppc_inst(swab32(ppc_inst_val(x)));
पूर्ण

अटल अंतरभूत काष्ठा ppc_inst ppc_inst_पढ़ो(स्थिर काष्ठा ppc_inst *ptr)
अणु
	वापस *ptr;
पूर्ण

अटल अंतरभूत bool ppc_inst_equal(काष्ठा ppc_inst x, काष्ठा ppc_inst y)
अणु
	वापस ppc_inst_val(x) == ppc_inst_val(y);
पूर्ण

#पूर्ण_अगर /* CONFIG_PPC64 */

अटल अंतरभूत पूर्णांक ppc_inst_len(काष्ठा ppc_inst x)
अणु
	वापस ppc_inst_prefixed(x) ? 8 : 4;
पूर्ण

/*
 * Return the address of the next inकाष्ठाion, अगर the inकाष्ठाion @value was
 * located at @location.
 */
अटल अंतरभूत काष्ठा ppc_inst *ppc_inst_next(व्योम *location, काष्ठा ppc_inst *value)
अणु
	काष्ठा ppc_inst पंचांगp;

	पंचांगp = ppc_inst_पढ़ो(value);

	वापस location + ppc_inst_len(पंचांगp);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ ppc_inst_as_uदीर्घ(काष्ठा ppc_inst x)
अणु
	अगर (IS_ENABLED(CONFIG_PPC32))
		वापस ppc_inst_val(x);
	अन्यथा अगर (IS_ENABLED(CONFIG_CPU_LITTLE_ENDIAN))
		वापस (u64)ppc_inst_suffix(x) << 32 | ppc_inst_val(x);
	अन्यथा
		वापस (u64)ppc_inst_val(x) << 32 | ppc_inst_suffix(x);
पूर्ण

#घोषणा PPC_INST_STR_LEN माप("00000000 00000000")

अटल अंतरभूत अक्षर *__ppc_inst_as_str(अक्षर str[PPC_INST_STR_LEN], काष्ठा ppc_inst x)
अणु
	अगर (ppc_inst_prefixed(x))
		प्र_लिखो(str, "%08x %08x", ppc_inst_val(x), ppc_inst_suffix(x));
	अन्यथा
		प्र_लिखो(str, "%08x", ppc_inst_val(x));

	वापस str;
पूर्ण

#घोषणा ppc_inst_as_str(x)		\
(अणु					\
	अक्षर __str[PPC_INST_STR_LEN];	\
	__ppc_inst_as_str(__str, x);	\
	__str;				\
पूर्ण)

पूर्णांक copy_inst_from_kernel_nofault(काष्ठा ppc_inst *inst, काष्ठा ppc_inst *src);

#पूर्ण_अगर /* _ASM_POWERPC_INST_H */
