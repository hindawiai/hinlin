<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Hypervisor Maपूर्णांकenance Interrupt header file.
 *
 * Copyright 2015 IBM Corporation
 * Author: Mahesh Salgaonkar <mahesh@linux.vnet.ibm.com>
 */

#अगर_अघोषित __ASM_PPC64_HMI_H__
#घोषणा __ASM_PPC64_HMI_H__

#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE

#घोषणा	CORE_TB_RESYNC_REQ_BIT		63
#घोषणा MAX_SUBCORE_PER_CORE		4

/*
 * sibling_subcore_state काष्ठाure is used to co-ordinate all thपढ़ोs
 * during HMI to aव्योम TB corruption. This काष्ठाure is allocated once
 * per each core and shared by all thपढ़ोs on that core.
 */
काष्ठा sibling_subcore_state अणु
	अचिन्हित दीर्घ	flags;
	u8		in_guest[MAX_SUBCORE_PER_CORE];
पूर्ण;

बाह्य व्योम रुको_क्रम_subcore_guest_निकास(व्योम);
बाह्य व्योम रुको_क्रम_tb_resync(व्योम);
#अन्यथा
अटल अंतरभूत व्योम रुको_क्रम_subcore_guest_निकास(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम रुको_क्रम_tb_resync(व्योम) अणु पूर्ण
#पूर्ण_अगर

काष्ठा pt_regs;
बाह्य दीर्घ hmi_handle_debugtrig(काष्ठा pt_regs *regs);

#पूर्ण_अगर /* __ASM_PPC64_HMI_H__ */
