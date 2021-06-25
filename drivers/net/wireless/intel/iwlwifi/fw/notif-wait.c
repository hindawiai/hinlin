<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2005-2014, 2021 Intel Corporation
 * Copyright (C) 2015-2017 Intel Deutschland GmbH
 */
#समावेश <linux/sched.h>
#समावेश <linux/export.h>

#समावेश "iwl-drv.h"
#समावेश "notif-wait.h"


व्योम iwl_notअगरication_रुको_init(काष्ठा iwl_notअगर_रुको_data *notअगर_रुको)
अणु
	spin_lock_init(&notअगर_रुको->notअगर_रुको_lock);
	INIT_LIST_HEAD(&notअगर_रुको->notअगर_रुकोs);
	init_रुकोqueue_head(&notअगर_रुको->notअगर_रुकोq);
पूर्ण
IWL_EXPORT_SYMBOL(iwl_notअगरication_रुको_init);

bool iwl_notअगरication_रुको(काष्ठा iwl_notअगर_रुको_data *notअगर_रुको,
			   काष्ठा iwl_rx_packet *pkt)
अणु
	bool triggered = false;

	अगर (!list_empty(&notअगर_रुको->notअगर_रुकोs)) अणु
		काष्ठा iwl_notअगरication_रुको *w;

		spin_lock_bh(&notअगर_रुको->notअगर_रुको_lock);
		list_क्रम_each_entry(w, &notअगर_रुको->notअगर_रुकोs, list) अणु
			पूर्णांक i;
			bool found = false;

			/*
			 * If it alपढ़ोy finished (triggered) or has been
			 * पातed then करोn't evaluate it again to aव्योम races,
			 * Otherwise the function could be called again even
			 * though it वापसed true beक्रमe
			 */
			अगर (w->triggered || w->पातed)
				जारी;

			क्रम (i = 0; i < w->n_cmds; i++) अणु
				u16 rec_id = WIDE_ID(pkt->hdr.group_id,
						     pkt->hdr.cmd);

				अगर (w->cmds[i] == rec_id ||
				    (!iwl_cmd_groupid(w->cmds[i]) &&
				     DEF_ID(w->cmds[i]) == rec_id)) अणु
					found = true;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (!found)
				जारी;

			अगर (!w->fn || w->fn(notअगर_रुको, pkt, w->fn_data)) अणु
				w->triggered = true;
				triggered = true;
			पूर्ण
		पूर्ण
		spin_unlock_bh(&notअगर_रुको->notअगर_रुको_lock);
	पूर्ण

	वापस triggered;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_notअगरication_रुको);

व्योम iwl_पात_notअगरication_रुकोs(काष्ठा iwl_notअगर_रुको_data *notअगर_रुको)
अणु
	काष्ठा iwl_notअगरication_रुको *रुको_entry;

	spin_lock_bh(&notअगर_रुको->notअगर_रुको_lock);
	list_क्रम_each_entry(रुको_entry, &notअगर_रुको->notअगर_रुकोs, list)
		रुको_entry->पातed = true;
	spin_unlock_bh(&notअगर_रुको->notअगर_रुको_lock);

	wake_up_all(&notअगर_रुको->notअगर_रुकोq);
पूर्ण
IWL_EXPORT_SYMBOL(iwl_पात_notअगरication_रुकोs);

व्योम
iwl_init_notअगरication_रुको(काष्ठा iwl_notअगर_रुको_data *notअगर_रुको,
			   काष्ठा iwl_notअगरication_रुको *रुको_entry,
			   स्थिर u16 *cmds, पूर्णांक n_cmds,
			   bool (*fn)(काष्ठा iwl_notअगर_रुको_data *notअगर_रुको,
				      काष्ठा iwl_rx_packet *pkt, व्योम *data),
			   व्योम *fn_data)
अणु
	अगर (WARN_ON(n_cmds > MAX_NOTIF_CMDS))
		n_cmds = MAX_NOTIF_CMDS;

	रुको_entry->fn = fn;
	रुको_entry->fn_data = fn_data;
	रुको_entry->n_cmds = n_cmds;
	स_नकल(रुको_entry->cmds, cmds, n_cmds * माप(u16));
	रुको_entry->triggered = false;
	रुको_entry->पातed = false;

	spin_lock_bh(&notअगर_रुको->notअगर_रुको_lock);
	list_add(&रुको_entry->list, &notअगर_रुको->notअगर_रुकोs);
	spin_unlock_bh(&notअगर_रुको->notअगर_रुको_lock);
पूर्ण
IWL_EXPORT_SYMBOL(iwl_init_notअगरication_रुको);

व्योम iwl_हटाओ_notअगरication(काष्ठा iwl_notअगर_रुको_data *notअगर_रुको,
			     काष्ठा iwl_notअगरication_रुको *रुको_entry)
अणु
	spin_lock_bh(&notअगर_रुको->notअगर_रुको_lock);
	list_del(&रुको_entry->list);
	spin_unlock_bh(&notअगर_रुको->notअगर_रुको_lock);
पूर्ण
IWL_EXPORT_SYMBOL(iwl_हटाओ_notअगरication);

पूर्णांक iwl_रुको_notअगरication(काष्ठा iwl_notअगर_रुको_data *notअगर_रुको,
			  काष्ठा iwl_notअगरication_रुको *रुको_entry,
			  अचिन्हित दीर्घ समयout)
अणु
	पूर्णांक ret;

	ret = रुको_event_समयout(notअगर_रुको->notअगर_रुकोq,
				 रुको_entry->triggered || रुको_entry->पातed,
				 समयout);

	iwl_हटाओ_notअगरication(notअगर_रुको, रुको_entry);

	अगर (रुको_entry->पातed)
		वापस -EIO;

	/* वापस value is always >= 0 */
	अगर (ret <= 0)
		वापस -ETIMEDOUT;
	वापस 0;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_रुको_notअगरication);
