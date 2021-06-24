<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC64_INTR_QUEUE_H
#घोषणा _SPARC64_INTR_QUEUE_H

/* Sun4v पूर्णांकerrupt queue रेजिस्टरs, accessed via ASI_QUEUE.  */

#घोषणा INTRQ_CPU_MONDO_HEAD	  0x3c0 /* CPU monकरो head	          */
#घोषणा INTRQ_CPU_MONDO_TAIL	  0x3c8 /* CPU monकरो tail	          */
#घोषणा INTRQ_DEVICE_MONDO_HEAD	  0x3d0 /* Device monकरो head	          */
#घोषणा INTRQ_DEVICE_MONDO_TAIL	  0x3d8 /* Device monकरो tail	          */
#घोषणा INTRQ_RESUM_MONDO_HEAD	  0x3e0 /* Resumable error monकरो head     */
#घोषणा INTRQ_RESUM_MONDO_TAIL	  0x3e8 /* Resumable error monकरो tail     */
#घोषणा INTRQ_NONRESUM_MONDO_HEAD 0x3f0 /* Non-resumable error monकरो head */
#घोषणा INTRQ_NONRESUM_MONDO_TAIL 0x3f8 /* Non-resumable error monकरो head */

#पूर्ण_अगर /* !(_SPARC64_INTR_QUEUE_H) */
