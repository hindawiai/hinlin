<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Written by Pat Gaughen (gone@us.ibm.com) Mar 2002
 *
 */

#अगर_अघोषित _ASM_X86_MMZONE_32_H
#घोषणा _ASM_X86_MMZONE_32_H

#समावेश <यंत्र/smp.h>

#अगर_घोषित CONFIG_NUMA
बाह्य काष्ठा pglist_data *node_data[];
#घोषणा NODE_DATA(nid)	(node_data[nid])
#पूर्ण_अगर /* CONFIG_NUMA */

#पूर्ण_अगर /* _ASM_X86_MMZONE_32_H */
