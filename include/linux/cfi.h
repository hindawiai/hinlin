<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Clang Control Flow Integrity (CFI) support.
 *
 * Copyright (C) 2021 Google LLC
 */
#अगर_अघोषित _LINUX_CFI_H
#घोषणा _LINUX_CFI_H

#अगर_घोषित CONFIG_CFI_CLANG
प्रकार व्योम (*cfi_check_fn)(uपूर्णांक64_t id, व्योम *ptr, व्योम *diag);

/* Compiler-generated function in each module, and the kernel */
बाह्य व्योम __cfi_check(uपूर्णांक64_t id, व्योम *ptr, व्योम *diag);

/*
 * Force the compiler to generate a CFI jump table entry क्रम a function
 * and store the jump table address to __cfi_jt_<function>.
 */
#घोषणा __CFI_ADDRESSABLE(fn, __attr) \
	स्थिर व्योम *__cfi_jt_ ## fn __visible __attr = (व्योम *)&fn

#अगर_घोषित CONFIG_CFI_CLANG_SHADOW

बाह्य व्योम cfi_module_add(काष्ठा module *mod, अचिन्हित दीर्घ base_addr);
बाह्य व्योम cfi_module_हटाओ(काष्ठा module *mod, अचिन्हित दीर्घ base_addr);

#अन्यथा

अटल अंतरभूत व्योम cfi_module_add(काष्ठा module *mod, अचिन्हित दीर्घ base_addr) अणुपूर्ण
अटल अंतरभूत व्योम cfi_module_हटाओ(काष्ठा module *mod, अचिन्हित दीर्घ base_addr) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_CFI_CLANG_SHADOW */

#अन्यथा /* !CONFIG_CFI_CLANG */

#घोषणा __CFI_ADDRESSABLE(fn, __attr)

#पूर्ण_अगर /* CONFIG_CFI_CLANG */

#पूर्ण_अगर /* _LINUX_CFI_H */
