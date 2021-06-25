<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* K8 NUMA support */
/* Copyright 2002,2003 by Andi Kleen, SuSE Lअसल */
/* 2.5 Version loosely based on the NUMAQ Code by Pat Gaughen. */
#अगर_अघोषित _ASM_X86_MMZONE_64_H
#घोषणा _ASM_X86_MMZONE_64_H

#अगर_घोषित CONFIG_NUMA

#समावेश <linux/mmdebug.h>
#समावेश <यंत्र/smp.h>

बाह्य काष्ठा pglist_data *node_data[];

#घोषणा NODE_DATA(nid)		(node_data[nid])

#पूर्ण_अगर
#पूर्ण_अगर /* _ASM_X86_MMZONE_64_H */
