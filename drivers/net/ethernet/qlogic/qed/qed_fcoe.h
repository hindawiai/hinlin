<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित _QED_FCOE_H
#घोषणा _QED_FCOE_H
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/qed/qed_fcoe_अगर.h>
#समावेश <linux/qed/qed_chain.h>
#समावेश "qed.h"
#समावेश "qed_hsi.h"
#समावेश "qed_mcp.h"
#समावेश "qed_sp.h"

काष्ठा qed_fcoe_info अणु
	spinlock_t lock; /* Connection resources. */
	काष्ठा list_head मुक्त_list;
पूर्ण;

#अगर IS_ENABLED(CONFIG_QED_FCOE)
पूर्णांक qed_fcoe_alloc(काष्ठा qed_hwfn *p_hwfn);

व्योम qed_fcoe_setup(काष्ठा qed_hwfn *p_hwfn);

व्योम qed_fcoe_मुक्त(काष्ठा qed_hwfn *p_hwfn);
व्योम qed_get_protocol_stats_fcoe(काष्ठा qed_dev *cdev,
				 काष्ठा qed_mcp_fcoe_stats *stats);
#अन्यथा /* CONFIG_QED_FCOE */
अटल अंतरभूत पूर्णांक qed_fcoe_alloc(काष्ठा qed_hwfn *p_hwfn)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम qed_fcoe_setup(काष्ठा qed_hwfn *p_hwfn) अणुपूर्ण
अटल अंतरभूत व्योम qed_fcoe_मुक्त(काष्ठा qed_hwfn *p_hwfn) अणुपूर्ण

अटल अंतरभूत व्योम qed_get_protocol_stats_fcoe(काष्ठा qed_dev *cdev,
					       काष्ठा qed_mcp_fcoe_stats *stats)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_QED_FCOE */

#पूर्ण_अगर /* _QED_FCOE_H */
