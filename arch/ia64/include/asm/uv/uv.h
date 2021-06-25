<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_UV_UV_H
#घोषणा _ASM_IA64_UV_UV_H

#अगर_घोषित CONFIG_IA64_SGI_UV
बाह्य bool ia64_is_uv;

अटल अंतरभूत पूर्णांक is_uv_प्रणाली(व्योम)
अणु
	वापस ia64_is_uv;
पूर्ण

व्योम __init uv_probe_प्रणाली_type(व्योम);
व्योम __init uv_setup(अक्षर **cmdline_p);
#अन्यथा /* CONFIG_IA64_SGI_UV */
अटल अंतरभूत पूर्णांक is_uv_प्रणाली(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम __init uv_probe_प्रणाली_type(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम __init uv_setup(अक्षर **cmdline_p)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_IA64_SGI_UV */

#पूर्ण_अगर	/* _ASM_IA64_UV_UV_H */
