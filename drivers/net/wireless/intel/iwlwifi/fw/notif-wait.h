<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2005-2014 Intel Corporation
 * Copyright (C) 2015-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_notअगर_रुको_h__
#घोषणा __iwl_notअगर_रुको_h__

#समावेश <linux/रुको.h>

#समावेश "iwl-trans.h"

काष्ठा iwl_notअगर_रुको_data अणु
	काष्ठा list_head notअगर_रुकोs;
	spinlock_t notअगर_रुको_lock;
	रुको_queue_head_t notअगर_रुकोq;
पूर्ण;

#घोषणा MAX_NOTIF_CMDS	5

/**
 * काष्ठा iwl_notअगरication_रुको - notअगरication रुको entry
 * @list: list head क्रम global list
 * @fn: Function called with the notअगरication. If the function
 *	वापसs true, the रुको is over, अगर it वापसs false then
 *	the रुकोer stays blocked. If no function is given, any
 *	of the listed commands will unblock the रुकोer.
 * @cmds: command IDs
 * @n_cmds: number of command IDs
 * @triggered: रुकोer should be woken up
 * @पातed: रुको was पातed
 *
 * This काष्ठाure is not used directly, to रुको क्रम a
 * notअगरication declare it on the stack, and call
 * iwl_init_notअगरication_रुको() with appropriate
 * parameters. Then करो whatever will cause the ucode
 * to notअगरy the driver, and to रुको क्रम that then
 * call iwl_रुको_notअगरication().
 *
 * Each notअगरication is one-shot. If at some poपूर्णांक we
 * need to support multi-shot notअगरications (which
 * can't be allocated on the stack) we need to modअगरy
 * the code क्रम them.
 */
काष्ठा iwl_notअगरication_रुको अणु
	काष्ठा list_head list;

	bool (*fn)(काष्ठा iwl_notअगर_रुको_data *notअगर_data,
		   काष्ठा iwl_rx_packet *pkt, व्योम *data);
	व्योम *fn_data;

	u16 cmds[MAX_NOTIF_CMDS];
	u8 n_cmds;
	bool triggered, पातed;
पूर्ण;


/* caller functions */
व्योम iwl_notअगरication_रुको_init(काष्ठा iwl_notअगर_रुको_data *notअगर_data);
bool iwl_notअगरication_रुको(काष्ठा iwl_notअगर_रुको_data *notअगर_data,
			   काष्ठा iwl_rx_packet *pkt);
व्योम iwl_पात_notअगरication_रुकोs(काष्ठा iwl_notअगर_रुको_data *notअगर_data);

अटल अंतरभूत व्योम
iwl_notअगरication_notअगरy(काष्ठा iwl_notअगर_रुको_data *notअगर_data)
अणु
	wake_up_all(&notअगर_data->notअगर_रुकोq);
पूर्ण

अटल अंतरभूत व्योम
iwl_notअगरication_रुको_notअगरy(काष्ठा iwl_notअगर_रुको_data *notअगर_data,
			     काष्ठा iwl_rx_packet *pkt)
अणु
	अगर (iwl_notअगरication_रुको(notअगर_data, pkt))
		iwl_notअगरication_notअगरy(notअगर_data);
पूर्ण

/* user functions */
व्योम __acquires(रुको_entry)
iwl_init_notअगरication_रुको(काष्ठा iwl_notअगर_रुको_data *notअगर_data,
			   काष्ठा iwl_notअगरication_रुको *रुको_entry,
			   स्थिर u16 *cmds, पूर्णांक n_cmds,
			   bool (*fn)(काष्ठा iwl_notअगर_रुको_data *notअगर_data,
				      काष्ठा iwl_rx_packet *pkt, व्योम *data),
			   व्योम *fn_data);

पूर्णांक __must_check __releases(रुको_entry)
iwl_रुको_notअगरication(काष्ठा iwl_notअगर_रुको_data *notअगर_data,
		      काष्ठा iwl_notअगरication_रुको *रुको_entry,
		      अचिन्हित दीर्घ समयout);

व्योम __releases(रुको_entry)
iwl_हटाओ_notअगरication(काष्ठा iwl_notअगर_रुको_data *notअगर_data,
			काष्ठा iwl_notअगरication_रुको *रुको_entry);

#पूर्ण_अगर /* __iwl_notअगर_रुको_h__ */
