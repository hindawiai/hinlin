<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * PCC (Platक्रमm Communications Channel) methods
 */

#अगर_अघोषित _PCC_H
#घोषणा _PCC_H

#समावेश <linux/mailbox_controller.h>
#समावेश <linux/mailbox_client.h>

#घोषणा MAX_PCC_SUBSPACES	256
#अगर_घोषित CONFIG_PCC
बाह्य काष्ठा mbox_chan *pcc_mbox_request_channel(काष्ठा mbox_client *cl,
						  पूर्णांक subspace_id);
बाह्य व्योम pcc_mbox_मुक्त_channel(काष्ठा mbox_chan *chan);
#अन्यथा
अटल अंतरभूत काष्ठा mbox_chan *pcc_mbox_request_channel(काष्ठा mbox_client *cl,
							 पूर्णांक subspace_id)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण
अटल अंतरभूत व्योम pcc_mbox_मुक्त_channel(काष्ठा mbox_chan *chan) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _PCC_H */
