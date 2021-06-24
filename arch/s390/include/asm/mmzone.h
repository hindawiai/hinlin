<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * NUMA support क्रम s390
 *
 * Copyright IBM Corp. 2015
 */

#अगर_अघोषित _ASM_S390_MMZONE_H
#घोषणा _ASM_S390_MMZONE_H

#अगर_घोषित CONFIG_NUMA

बाह्य काष्ठा pglist_data *node_data[];
#घोषणा NODE_DATA(nid) (node_data[nid])

#पूर्ण_अगर /* CONFIG_NUMA */
#पूर्ण_अगर /* _ASM_S390_MMZONE_H */
