<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* OLPC machine specअगरic definitions */

#अगर_अघोषित _ASM_X86_OLPC_H
#घोषणा _ASM_X86_OLPC_H

#समावेश <यंत्र/geode.h>

काष्ठा olpc_platक्रमm_t अणु
	पूर्णांक flags;
	uपूर्णांक32_t boardrev;
पूर्ण;

#घोषणा OLPC_F_PRESENT		0x01
#घोषणा OLPC_F_DCON		0x02

#अगर_घोषित CONFIG_OLPC

बाह्य काष्ठा olpc_platक्रमm_t olpc_platक्रमm_info;

/*
 * OLPC board IDs contain the major build number within the mask 0x0ff0,
 * and the minor build number within 0x000f.  Pre-builds have a minor
 * number less than 8, and normal builds start at 8.  For example, 0x0B10
 * is a PreB1, and 0x0C18 is a C1.
 */

अटल अंतरभूत uपूर्णांक32_t olpc_board(uपूर्णांक8_t id)
अणु
	वापस (id << 4) | 0x8;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t olpc_board_pre(uपूर्णांक8_t id)
अणु
	वापस id << 4;
पूर्ण

अटल अंतरभूत पूर्णांक machine_is_olpc(व्योम)
अणु
	वापस (olpc_platक्रमm_info.flags & OLPC_F_PRESENT) ? 1 : 0;
पूर्ण

/*
 * The DCON is OLPC's Display Controller.  It has a number of unique
 * features that we might want to take advantage of..
 */
अटल अंतरभूत पूर्णांक olpc_has_dcon(व्योम)
अणु
	वापस (olpc_platक्रमm_info.flags & OLPC_F_DCON) ? 1 : 0;
पूर्ण

/*
 * The "Mass Production" version of OLPC's XO is identअगरied as being model
 * C2.  During the prototype phase, the following models (in chronological
 * order) were created: A1, B1, B2, B3, B4, C1.  The A1 through B2 models
 * were based on Geode GX CPUs, and models after that were based upon
 * Geode LX CPUs.  There were also some hand-assembled models भग्नing
 * around, referred to as PreB1, PreB2, etc.
 */
अटल अंतरभूत पूर्णांक olpc_board_at_least(uपूर्णांक32_t rev)
अणु
	वापस olpc_platक्रमm_info.boardrev >= rev;
पूर्ण

#अन्यथा

अटल अंतरभूत पूर्णांक machine_is_olpc(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक olpc_has_dcon(व्योम)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_OLPC_XO1_PM
बाह्य व्योम करो_olpc_suspend_lowlevel(व्योम);
बाह्य व्योम olpc_xo1_pm_wakeup_set(u16 value);
बाह्य व्योम olpc_xo1_pm_wakeup_clear(u16 value);
#पूर्ण_अगर

बाह्य पूर्णांक pci_olpc_init(व्योम);

/* GPIO assignments */

#घोषणा OLPC_GPIO_MIC_AC	1
#घोषणा OLPC_GPIO_DCON_STAT0	5
#घोषणा OLPC_GPIO_DCON_STAT1	6
#घोषणा OLPC_GPIO_DCON_IRQ	7
#घोषणा OLPC_GPIO_THRM_ALRM	geode_gpio(10)
#घोषणा OLPC_GPIO_DCON_LOAD    11
#घोषणा OLPC_GPIO_DCON_BLANK   12
#घोषणा OLPC_GPIO_SMB_CLK      14
#घोषणा OLPC_GPIO_SMB_DATA     15
#घोषणा OLPC_GPIO_WORKAUX	geode_gpio(24)
#घोषणा OLPC_GPIO_LID		26
#घोषणा OLPC_GPIO_ECSCI		27

#पूर्ण_अगर /* _ASM_X86_OLPC_H */
