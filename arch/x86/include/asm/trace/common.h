<शैली गुरु>
#अगर_अघोषित _ASM_TRACE_COMMON_H
#घोषणा _ASM_TRACE_COMMON_H

#अगर_घोषित CONFIG_TRACING
DECLARE_STATIC_KEY_FALSE(trace_pagefault_key);
#घोषणा trace_pagefault_enabled()			\
	अटल_branch_unlikely(&trace_pagefault_key)
#अन्यथा
अटल अंतरभूत bool trace_pagefault_enabled(व्योम) अणु वापस false; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
