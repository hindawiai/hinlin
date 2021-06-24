<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित XMON_BPTS_H
#घोषणा XMON_BPTS_H

#घोषणा NBPTS	256
#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/inst.h>
#घोषणा BPT_SIZE	(माप(काष्ठा ppc_inst) * 2)
#घोषणा BPT_WORDS	(BPT_SIZE / माप(काष्ठा ppc_inst))

बाह्य अचिन्हित पूर्णांक bpt_table[NBPTS * BPT_WORDS];
#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* XMON_BPTS_H */
