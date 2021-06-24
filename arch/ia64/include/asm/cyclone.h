<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ASM_IA64_CYCLONE_H
#घोषणा ASM_IA64_CYCLONE_H

#अगर_घोषित	CONFIG_IA64_CYCLONE
बाह्य पूर्णांक use_cyclone;
बाह्य व्योम __init cyclone_setup(व्योम);
#अन्यथा	/* CONFIG_IA64_CYCLONE */
#घोषणा use_cyclone 0
अटल अंतरभूत व्योम cyclone_setup(व्योम)
अणु
	prपूर्णांकk(KERN_ERR "Cyclone Counter: System not configured"
					" w/ CONFIG_IA64_CYCLONE.\n");
पूर्ण
#पूर्ण_अगर	/* CONFIG_IA64_CYCLONE */
#पूर्ण_अगर	/* !ASM_IA64_CYCLONE_H */
