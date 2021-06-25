<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * File: pep_gprs.h
 *
 * GPRS over Phonet pipe end poपूर्णांक socket
 *
 * Copyright (C) 2008 Nokia Corporation.
 *
 * Author: Rथऊmi Denis-Courmont
 */

#अगर_अघोषित NET_PHONET_GPRS_H
#घोषणा NET_PHONET_GPRS_H

काष्ठा sock;
काष्ठा sk_buff;

पूर्णांक pep_ग_लिखोable(काष्ठा sock *sk);
पूर्णांक pep_ग_लिखो(काष्ठा sock *sk, काष्ठा sk_buff *skb);
काष्ठा sk_buff *pep_पढ़ो(काष्ठा sock *sk);

पूर्णांक gprs_attach(काष्ठा sock *sk);
व्योम gprs_detach(काष्ठा sock *sk);

#पूर्ण_अगर
