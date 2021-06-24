<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * drस्मृति.स: Power specअगरic logical memory block representation
 *
 * Copyright 2017 IBM Corporation
 */

#अगर_अघोषित _ASM_POWERPC_LMB_H
#घोषणा _ASM_POWERPC_LMB_H

#समावेश <linux/sched.h>

काष्ठा drmem_lmb अणु
	u64     base_addr;
	u32     drc_index;
	u32     aa_index;
	u32     flags;
पूर्ण;

काष्ठा drmem_lmb_info अणु
	काष्ठा drmem_lmb        *lmbs;
	पूर्णांक                     n_lmbs;
	u64                     lmb_size;
पूर्ण;

बाह्य काष्ठा drmem_lmb_info *drmem_info;

अटल अंतरभूत काष्ठा drmem_lmb *drmem_lmb_next(काष्ठा drmem_lmb *lmb,
					       स्थिर काष्ठा drmem_lmb *start)
अणु
	/*
	 * DLPAR code paths can take several milliseconds per element
	 * when पूर्णांकeracting with firmware. Ensure that we करोn't
	 * unfairly monopolize the CPU.
	 */
	अगर (((++lmb - start) % 16) == 0)
		cond_resched();

	वापस lmb;
पूर्ण

#घोषणा क्रम_each_drmem_lmb_in_range(lmb, start, end)		\
	क्रम ((lmb) = (start); (lmb) < (end); lmb = drmem_lmb_next(lmb, start))

#घोषणा क्रम_each_drmem_lmb(lmb)					\
	क्रम_each_drmem_lmb_in_range((lmb),			\
		&drmem_info->lmbs[0],				\
		&drmem_info->lmbs[drmem_info->n_lmbs])

/*
 * The of_drconf_cell_v1 काष्ठा defines the layout of the LMB data
 * specअगरied in the ibm,dynamic-memory device tree property.
 * The property itself is a 32-bit value specअगरying the number of
 * LMBs followed by an array of of_drconf_cell_v1 entries, one
 * per LMB.
 */
काष्ठा of_drconf_cell_v1 अणु
	__be64	base_addr;
	__be32	drc_index;
	__be32	reserved;
	__be32	aa_index;
	__be32	flags;
पूर्ण;

/*
 * Version 2 of the ibm,dynamic-memory property is defined as a
 * 32-bit value specअगरying the number of LMB sets followed by an
 * array of of_drconf_cell_v2 entries, one per LMB set.
 */
काष्ठा of_drconf_cell_v2 अणु
	u32	seq_lmbs;
	u64	base_addr;
	u32	drc_index;
	u32	aa_index;
	u32	flags;
पूर्ण __packed;

#घोषणा DRCONF_MEM_ASSIGNED	0x00000008
#घोषणा DRCONF_MEM_AI_INVALID	0x00000040
#घोषणा DRCONF_MEM_RESERVED	0x00000080
#घोषणा DRCONF_MEM_HOTREMOVABLE	0x00000100

अटल अंतरभूत u64 drmem_lmb_size(व्योम)
अणु
	वापस drmem_info->lmb_size;
पूर्ण

#घोषणा DRMEM_LMB_RESERVED	0x80000000

अटल अंतरभूत व्योम drmem_mark_lmb_reserved(काष्ठा drmem_lmb *lmb)
अणु
	lmb->flags |= DRMEM_LMB_RESERVED;
पूर्ण

अटल अंतरभूत व्योम drmem_हटाओ_lmb_reservation(काष्ठा drmem_lmb *lmb)
अणु
	lmb->flags &= ~DRMEM_LMB_RESERVED;
पूर्ण

अटल अंतरभूत bool drmem_lmb_reserved(काष्ठा drmem_lmb *lmb)
अणु
	वापस lmb->flags & DRMEM_LMB_RESERVED;
पूर्ण

u64 drmem_lmb_memory_max(व्योम);
पूर्णांक walk_drmem_lmbs(काष्ठा device_node *dn, व्योम *data,
		    पूर्णांक (*func)(काष्ठा drmem_lmb *, स्थिर __be32 **, व्योम *));
पूर्णांक drmem_update_dt(व्योम);

#अगर_घोषित CONFIG_PPC_PSERIES
पूर्णांक __init
walk_drmem_lmbs_early(अचिन्हित दीर्घ node, व्योम *data,
		      पूर्णांक (*func)(काष्ठा drmem_lmb *, स्थिर __be32 **, व्योम *));
#पूर्ण_अगर

अटल अंतरभूत व्योम invalidate_lmb_associativity_index(काष्ठा drmem_lmb *lmb)
अणु
	lmb->aa_index = 0xffffffff;
पूर्ण

#पूर्ण_अगर /* _ASM_POWERPC_LMB_H */
