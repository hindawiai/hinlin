<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_ERROR_INJECTION_H
#घोषणा _ASM_GENERIC_ERROR_INJECTION_H

#अगर defined(__KERNEL__) && !defined(__ASSEMBLY__)
क्रमागत अणु
	EI_ETYPE_NONE,		/* Dummy value क्रम undefined हाल */
	EI_ETYPE_शून्य,		/* Return शून्य अगर failure */
	EI_ETYPE_ERRNO,		/* Return -ERRNO अगर failure */
	EI_ETYPE_ERRNO_शून्य,	/* Return -ERRNO or शून्य अगर failure */
	EI_ETYPE_TRUE,		/* Return true अगर failure */
पूर्ण;

काष्ठा error_injection_entry अणु
	अचिन्हित दीर्घ	addr;
	पूर्णांक		etype;
पूर्ण;

काष्ठा pt_regs;

#अगर_घोषित CONFIG_FUNCTION_ERROR_INJECTION
/*
 * Whitelist ganerating macro. Specअगरy functions which can be
 * error-injectable using this macro.
 */
#घोषणा ALLOW_ERROR_INJECTION(fname, _etype)				\
अटल काष्ठा error_injection_entry __used				\
	__section("_error_injection_whitelist")				\
	_eil_addr_##fname = अणु						\
		.addr = (अचिन्हित दीर्घ)fname,				\
		.etype = EI_ETYPE_##_etype,				\
	पूर्ण;

व्योम override_function_with_वापस(काष्ठा pt_regs *regs);
#अन्यथा
#घोषणा ALLOW_ERROR_INJECTION(fname, _etype)

अटल अंतरभूत व्योम override_function_with_वापस(काष्ठा pt_regs *regs) अणु पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_GENERIC_ERROR_INJECTION_H */
