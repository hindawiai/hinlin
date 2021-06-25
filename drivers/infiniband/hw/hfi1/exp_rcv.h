<शैली गुरु>
#अगर_अघोषित _HFI1_EXP_RCV_H
#घोषणा _HFI1_EXP_RCV_H
/*
 * Copyright(c) 2017 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#समावेश "hfi.h"

#घोषणा EXP_TID_SET_EMPTY(set) (set.count == 0 && list_empty(&set.list))

#घोषणा EXP_TID_TIDLEN_MASK   0x7FFULL
#घोषणा EXP_TID_TIDLEN_SHIFT  0
#घोषणा EXP_TID_TIDCTRL_MASK  0x3ULL
#घोषणा EXP_TID_TIDCTRL_SHIFT 20
#घोषणा EXP_TID_TIDIDX_MASK   0x3FFULL
#घोषणा EXP_TID_TIDIDX_SHIFT  22
#घोषणा EXP_TID_GET(tid, field)	\
	(((tid) >> EXP_TID_TID##field##_SHIFT) & EXP_TID_TID##field##_MASK)

#घोषणा EXP_TID_SET(field, value)			\
	(((value) & EXP_TID_TID##field##_MASK) <<	\
	 EXP_TID_TID##field##_SHIFT)
#घोषणा EXP_TID_CLEAR(tid, field) (अणु					\
		(tid) &= ~(EXP_TID_TID##field##_MASK <<			\
			   EXP_TID_TID##field##_SHIFT);			\
		पूर्ण)
#घोषणा EXP_TID_RESET(tid, field, value) करो अणु				\
		EXP_TID_CLEAR(tid, field);				\
		(tid) |= EXP_TID_SET(field, (value));			\
	पूर्ण जबतक (0)

/*
 * Define fields in the KDETH header so we can update the header
 * ढाँचा.
 */
#घोषणा KDETH_OFFSET_SHIFT        0
#घोषणा KDETH_OFFSET_MASK         0x7fff
#घोषणा KDETH_OM_SHIFT            15
#घोषणा KDETH_OM_MASK             0x1
#घोषणा KDETH_TID_SHIFT           16
#घोषणा KDETH_TID_MASK            0x3ff
#घोषणा KDETH_TIDCTRL_SHIFT       26
#घोषणा KDETH_TIDCTRL_MASK        0x3
#घोषणा KDETH_INTR_SHIFT          28
#घोषणा KDETH_INTR_MASK           0x1
#घोषणा KDETH_SH_SHIFT            29
#घोषणा KDETH_SH_MASK             0x1
#घोषणा KDETH_KVER_SHIFT          30
#घोषणा KDETH_KVER_MASK           0x3
#घोषणा KDETH_JKEY_SHIFT          0x0
#घोषणा KDETH_JKEY_MASK           0xff
#घोषणा KDETH_HCRC_UPPER_SHIFT    16
#घोषणा KDETH_HCRC_UPPER_MASK     0xff
#घोषणा KDETH_HCRC_LOWER_SHIFT    24
#घोषणा KDETH_HCRC_LOWER_MASK     0xff

#घोषणा KDETH_GET(val, field)						\
	(((le32_to_cpu((val))) >> KDETH_##field##_SHIFT) & KDETH_##field##_MASK)
#घोषणा KDETH_SET(dw, field, val) करो अणु					\
		u32 dwval = le32_to_cpu(dw);				\
		dwval &= ~(KDETH_##field##_MASK << KDETH_##field##_SHIFT); \
		dwval |= (((val) & KDETH_##field##_MASK) << \
			  KDETH_##field##_SHIFT);			\
		dw = cpu_to_le32(dwval);				\
	पूर्ण जबतक (0)

#घोषणा KDETH_RESET(dw, field, val) (अणु dw = 0; KDETH_SET(dw, field, val); पूर्ण)

/* KDETH OM multipliers and चयन over poपूर्णांक */
#घोषणा KDETH_OM_SMALL     4
#घोषणा KDETH_OM_SMALL_SHIFT     2
#घोषणा KDETH_OM_LARGE     64
#घोषणा KDETH_OM_LARGE_SHIFT     6
#घोषणा KDETH_OM_MAX_SIZE  (1 << ((KDETH_OM_LARGE / KDETH_OM_SMALL) + 1))

काष्ठा tid_group अणु
	काष्ठा list_head list;
	u32 base;
	u8 size;
	u8 used;
	u8 map;
पूर्ण;

/*
 * Write an "empty" RcvArray entry.
 * This function exists so the TID registaration code can use it
 * to ग_लिखो to unused/unneeded entries and still take advantage
 * of the WC perक्रमmance improvements. The HFI will ignore this
 * ग_लिखो to the RcvArray entry.
 */
अटल अंतरभूत व्योम rcv_array_wc_fill(काष्ठा hfi1_devdata *dd, u32 index)
अणु
	/*
	 * Doing the WC fill ग_लिखोs only makes sense अगर the device is
	 * present and the RcvArray has been mapped as WC memory.
	 */
	अगर ((dd->flags & HFI1_PRESENT) && dd->rcvarray_wc) अणु
		ग_लिखोq(0, dd->rcvarray_wc + (index * 8));
		अगर ((index & 3) == 3)
			flush_wc();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम tid_group_add_tail(काष्ठा tid_group *grp,
				      काष्ठा exp_tid_set *set)
अणु
	list_add_tail(&grp->list, &set->list);
	set->count++;
पूर्ण

अटल अंतरभूत व्योम tid_group_हटाओ(काष्ठा tid_group *grp,
				    काष्ठा exp_tid_set *set)
अणु
	list_del_init(&grp->list);
	set->count--;
पूर्ण

अटल अंतरभूत व्योम tid_group_move(काष्ठा tid_group *group,
				  काष्ठा exp_tid_set *s1,
				  काष्ठा exp_tid_set *s2)
अणु
	tid_group_हटाओ(group, s1);
	tid_group_add_tail(group, s2);
पूर्ण

अटल अंतरभूत काष्ठा tid_group *tid_group_pop(काष्ठा exp_tid_set *set)
अणु
	काष्ठा tid_group *grp =
		list_first_entry(&set->list, काष्ठा tid_group, list);
	list_del_init(&grp->list);
	set->count--;
	वापस grp;
पूर्ण

अटल अंतरभूत u32 rcventry2tidinfo(u32 rcventry)
अणु
	u32 pair = rcventry & ~0x1;

	वापस EXP_TID_SET(IDX, pair >> 1) |
		EXP_TID_SET(CTRL, 1 << (rcventry - pair));
पूर्ण

/**
 * hfi1_tid_group_to_idx - convert an index to a group
 * @rcd - the receive context
 * @grp - the group poपूर्णांकer
 */
अटल अंतरभूत u16
hfi1_tid_group_to_idx(काष्ठा hfi1_ctxtdata *rcd, काष्ठा tid_group *grp)
अणु
	वापस grp - &rcd->groups[0];
पूर्ण

/**
 * hfi1_idx_to_tid_group - convert a group to an index
 * @rcd - the receive context
 * @idx - the index
 */
अटल अंतरभूत काष्ठा tid_group *
hfi1_idx_to_tid_group(काष्ठा hfi1_ctxtdata *rcd, u16 idx)
अणु
	वापस &rcd->groups[idx];
पूर्ण

पूर्णांक hfi1_alloc_ctxt_rcv_groups(काष्ठा hfi1_ctxtdata *rcd);
व्योम hfi1_मुक्त_ctxt_rcv_groups(काष्ठा hfi1_ctxtdata *rcd);
व्योम hfi1_exp_tid_group_init(काष्ठा hfi1_ctxtdata *rcd);

#पूर्ण_अगर /* _HFI1_EXP_RCV_H */
