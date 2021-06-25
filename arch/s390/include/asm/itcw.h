<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Functions क्रम incremental स्थिरruction of fcx enabled I/O control blocks.
 *
 *    Copyright IBM Corp. 2008
 *    Author(s): Peter Oberparleiter <peter.oberparleiter@de.ibm.com>
 */

#अगर_अघोषित _ASM_S390_ITCW_H
#घोषणा _ASM_S390_ITCW_H

#समावेश <linux/types.h>
#समावेश <यंत्र/fcx.h>

#घोषणा ITCW_OP_READ	0
#घोषणा ITCW_OP_WRITE	1

काष्ठा itcw;

काष्ठा tcw *itcw_get_tcw(काष्ठा itcw *itcw);
माप_प्रकार itcw_calc_size(पूर्णांक पूर्णांकrg, पूर्णांक max_tidaws, पूर्णांक पूर्णांकrg_max_tidaws);
काष्ठा itcw *itcw_init(व्योम *buffer, माप_प्रकार size, पूर्णांक op, पूर्णांक पूर्णांकrg,
		       पूर्णांक max_tidaws, पूर्णांक पूर्णांकrg_max_tidaws);
काष्ठा dcw *itcw_add_dcw(काष्ठा itcw *itcw, u8 cmd, u8 flags, व्योम *cd,
			 u8 cd_count, u32 count);
काष्ठा tidaw *itcw_add_tidaw(काष्ठा itcw *itcw, u8 flags, व्योम *addr,
			     u32 count);
व्योम itcw_set_data(काष्ठा itcw *itcw, व्योम *addr, पूर्णांक use_tidal);
व्योम itcw_finalize(काष्ठा itcw *itcw);

#पूर्ण_अगर /* _ASM_S390_ITCW_H */
