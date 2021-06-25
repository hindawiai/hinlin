<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित _QED_ISCSI_H
#घोषणा _QED_ISCSI_H
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/qed/tcp_common.h>
#समावेश <linux/qed/qed_iscsi_अगर.h>
#समावेश <linux/qed/qed_chain.h>
#समावेश "qed.h"
#समावेश "qed_hsi.h"
#समावेश "qed_mcp.h"
#समावेश "qed_sp.h"

काष्ठा qed_iscsi_info अणु
	spinlock_t lock; /* Connection resources. */
	काष्ठा list_head मुक्त_list;
	u16 max_num_outstanding_tasks;
	व्योम *event_context;
	iscsi_event_cb_t event_cb;
पूर्ण;

#अगर IS_ENABLED(CONFIG_QED_ISCSI)
पूर्णांक qed_iscsi_alloc(काष्ठा qed_hwfn *p_hwfn);

व्योम qed_iscsi_setup(काष्ठा qed_hwfn *p_hwfn);

व्योम qed_iscsi_मुक्त(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief - Fills provided statistics काष्ठा with statistics.
 *
 * @param cdev
 * @param stats - poपूर्णांकs to काष्ठा that will be filled with statistics.
 */
व्योम qed_get_protocol_stats_iscsi(काष्ठा qed_dev *cdev,
				  काष्ठा qed_mcp_iscsi_stats *stats);
#अन्यथा /* IS_ENABLED(CONFIG_QED_ISCSI) */
अटल अंतरभूत पूर्णांक qed_iscsi_alloc(काष्ठा qed_hwfn *p_hwfn)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम qed_iscsi_setup(काष्ठा qed_hwfn *p_hwfn) अणुपूर्ण

अटल अंतरभूत व्योम qed_iscsi_मुक्त(काष्ठा qed_hwfn *p_hwfn) अणुपूर्ण

अटल अंतरभूत व्योम
qed_get_protocol_stats_iscsi(काष्ठा qed_dev *cdev,
			     काष्ठा qed_mcp_iscsi_stats *stats) अणुपूर्ण
#पूर्ण_अगर /* IS_ENABLED(CONFIG_QED_ISCSI) */

#पूर्ण_अगर
