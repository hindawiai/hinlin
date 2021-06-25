<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Written by Kanoj Sarcar (kanoj@sgi.com) Aug 99
 * Rewritten क्रम Linux 2.6 by Christoph Hellwig (hch@lst.de) Jan 2004
 */
#अगर_अघोषित _ASM_MMZONE_H_
#घोषणा _ASM_MMZONE_H_

#समावेश <यंत्र/page.h>

#अगर_घोषित CONFIG_NEED_MULTIPLE_NODES
# include <mmzone.h>
#पूर्ण_अगर

#अगर_अघोषित pa_to_nid
#घोषणा pa_to_nid(addr) 0
#पूर्ण_अगर

#अगर_अघोषित nid_to_addrbase
#घोषणा nid_to_addrbase(nid) 0
#पूर्ण_अगर

#अगर_घोषित CONFIG_DISCONTIGMEM

#घोषणा pfn_to_nid(pfn)		pa_to_nid((pfn) << PAGE_SHIFT)

#पूर्ण_अगर /* CONFIG_DISCONTIGMEM */

#पूर्ण_अगर /* _ASM_MMZONE_H_ */
