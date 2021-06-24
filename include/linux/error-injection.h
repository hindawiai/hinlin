<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_ERROR_INJECTION_H
#घोषणा _LINUX_ERROR_INJECTION_H

#समावेश <linux/compiler.h>
#समावेश <यंत्र-generic/error-injection.h>

#अगर_घोषित CONFIG_FUNCTION_ERROR_INJECTION

बाह्य bool within_error_injection_list(अचिन्हित दीर्घ addr);
बाह्य पूर्णांक get_injectable_error_type(अचिन्हित दीर्घ addr);

#अन्यथा /* !CONFIG_FUNCTION_ERROR_INJECTION */

अटल अंतरभूत bool within_error_injection_list(अचिन्हित दीर्घ addr)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक get_injectable_error_type(अचिन्हित दीर्घ addr)
अणु
	वापस EI_ETYPE_NONE;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_ERROR_INJECTION_H */
