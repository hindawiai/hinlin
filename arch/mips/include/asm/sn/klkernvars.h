<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * File ported from IRIX to Linux by Kanoj Sarcar, 06/08/00.
 * Copyright 2000 Silicon Graphics, Inc.
 */
#अगर_अघोषित __ASM_SN_KLKERNVARS_H
#घोषणा __ASM_SN_KLKERNVARS_H

#घोषणा KV_MAGIC_OFFSET		0x0
#घोषणा KV_RO_NASID_OFFSET	0x4
#घोषणा KV_RW_NASID_OFFSET	0x6

#घोषणा KV_MAGIC		0x5f4b565f

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/sn/types.h>

प्रकार काष्ठा kern_vars_s अणु
	पूर्णांक		kv_magic;
	nasid_t		kv_ro_nasid;
	nasid_t		kv_rw_nasid;
	अचिन्हित दीर्घ	kv_ro_baseaddr;
	अचिन्हित दीर्घ	kv_rw_baseaddr;
पूर्ण kern_vars_t;

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_SN_KLKERNVARS_H */
