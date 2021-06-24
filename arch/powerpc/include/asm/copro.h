<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2014 IBM Corp.
 */

#अगर_अघोषित _ASM_POWERPC_COPRO_H
#घोषणा _ASM_POWERPC_COPRO_H

#समावेश <linux/mm_types.h>

काष्ठा copro_slb
अणु
	u64 esid, vsid;
पूर्ण;

पूर्णांक copro_handle_mm_fault(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ ea,
			  अचिन्हित दीर्घ dsisr, vm_fault_t *flt);

पूर्णांक copro_calculate_slb(काष्ठा mm_काष्ठा *mm, u64 ea, काष्ठा copro_slb *slb);


#अगर_घोषित CONFIG_PPC_COPRO_BASE
व्योम copro_flush_all_slbs(काष्ठा mm_काष्ठा *mm);
#अन्यथा
अटल अंतरभूत व्योम copro_flush_all_slbs(काष्ठा mm_काष्ठा *mm) अणुपूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* _ASM_POWERPC_COPRO_H */
