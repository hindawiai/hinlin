<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * cs5536 mfgpt header file
 */

#अगर_अघोषित _CS5536_MFGPT_H
#घोषणा _CS5536_MFGPT_H

#समावेश <cs5536/cs5536.h>
#समावेश <cs5536/cs5536_pci.h>

#अगर_घोषित CONFIG_CS5536_MFGPT
बाह्य व्योम setup_mfgpt0_समयr(व्योम);
बाह्य व्योम disable_mfgpt0_counter(व्योम);
बाह्य व्योम enable_mfgpt0_counter(व्योम);
#अन्यथा
अटल अंतरभूत व्योम __maybe_unused setup_mfgpt0_समयr(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम __maybe_unused disable_mfgpt0_counter(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम __maybe_unused enable_mfgpt0_counter(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#घोषणा MFGPT_TICK_RATE 14318000
#घोषणा COMPARE	 ((MFGPT_TICK_RATE + HZ/2) / HZ)

#घोषणा MFGPT_BASE	mfgpt_base
#घोषणा MFGPT0_CMP2	(MFGPT_BASE + 2)
#घोषणा MFGPT0_CNT	(MFGPT_BASE + 4)
#घोषणा MFGPT0_SETUP	(MFGPT_BASE + 6)

#पूर्ण_अगर /*!_CS5536_MFGPT_H */
