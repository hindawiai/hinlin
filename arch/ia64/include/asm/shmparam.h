<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_SHMPARAM_H
#घोषणा _ASM_IA64_SHMPARAM_H

/*
 * SHMLBA controls minimum alignment at which shared memory segments
 * get attached.  The IA-64 architecture says that there may be a
 * perक्रमmance degradation when there are भव aliases within 1MB.
 * To reduce the chance of this, we set SHMLBA to 1MB. --davidm 00/12/20
 */
#घोषणा	SHMLBA	(1024*1024)

#पूर्ण_अगर /* _ASM_IA64_SHMPARAM_H */
