<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * dlmकरोमुख्य.h
 *
 * Copyright (C) 2004 Oracle.  All rights reserved.
 */

#अगर_अघोषित DLMDOMAIN_H
#घोषणा DLMDOMAIN_H

बाह्य spinlock_t dlm_करोमुख्य_lock;
बाह्य काष्ठा list_head dlm_करोमुख्यs;

अटल अंतरभूत पूर्णांक dlm_joined(काष्ठा dlm_ctxt *dlm)
अणु
	पूर्णांक ret = 0;

	spin_lock(&dlm_करोमुख्य_lock);
	अगर (dlm->dlm_state == DLM_CTXT_JOINED)
		ret = 1;
	spin_unlock(&dlm_करोमुख्य_lock);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक dlm_shutting_करोwn(काष्ठा dlm_ctxt *dlm)
अणु
	पूर्णांक ret = 0;

	spin_lock(&dlm_करोमुख्य_lock);
	अगर (dlm->dlm_state == DLM_CTXT_IN_SHUTDOWN)
		ret = 1;
	spin_unlock(&dlm_करोमुख्य_lock);

	वापस ret;
पूर्ण

व्योम dlm_fire_करोमुख्य_eviction_callbacks(काष्ठा dlm_ctxt *dlm,
					पूर्णांक node_num);

#पूर्ण_अगर
