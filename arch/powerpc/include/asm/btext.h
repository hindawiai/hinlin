<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Definitions क्रम using the procedures in btext.c.
 *
 * Benjamin Herrenschmidt <benh@kernel.crashing.org>
 */
#अगर_अघोषित __PPC_BTEXT_H
#घोषणा __PPC_BTEXT_H
#अगर_घोषित __KERNEL__

बाह्य पूर्णांक btext_find_display(पूर्णांक allow_nonमानक_निकास);
बाह्य व्योम btext_update_display(अचिन्हित दीर्घ phys, पूर्णांक width, पूर्णांक height,
				 पूर्णांक depth, पूर्णांक pitch);
बाह्य व्योम btext_setup_display(पूर्णांक width, पूर्णांक height, पूर्णांक depth, पूर्णांक pitch,
				अचिन्हित दीर्घ address);
#अगर_घोषित CONFIG_PPC32
बाह्य व्योम btext_prepare_BAT(व्योम);
#अन्यथा
अटल अंतरभूत व्योम btext_prepare_BAT(व्योम) अणु पूर्ण
#पूर्ण_अगर
बाह्य व्योम btext_map(व्योम);
बाह्य व्योम btext_unmap(व्योम);

बाह्य व्योम btext_drawअक्षर(अक्षर c);
बाह्य व्योम btext_drawstring(स्थिर अक्षर *str);
बाह्य व्योम btext_drawhex(अचिन्हित दीर्घ v);
बाह्य व्योम btext_drawtext(स्थिर अक्षर *c, अचिन्हित पूर्णांक len);

बाह्य व्योम btext_clearscreen(व्योम);
बाह्य व्योम btext_flushscreen(व्योम);
बाह्य व्योम btext_flushline(व्योम);

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* __PPC_BTEXT_H */
