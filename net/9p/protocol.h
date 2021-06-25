<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * net/9p/protocol.h
 *
 * 9P Protocol Support Code
 *
 *  Copyright (C) 2008 by Eric Van Hensbergen <ericvh@gmail.com>
 *
 *  Base on code from Anthony Liguori <aliguori@us.ibm.com>
 *  Copyright (C) 2008 by IBM, Corp.
 */

पूर्णांक p9pdu_vग_लिखोf(काष्ठा p9_fcall *pdu, पूर्णांक proto_version, स्थिर अक्षर *fmt,
								बहु_सूची ap);
पूर्णांक p9pdu_पढ़ोf(काष्ठा p9_fcall *pdu, पूर्णांक proto_version, स्थिर अक्षर *fmt, ...);
पूर्णांक p9pdu_prepare(काष्ठा p9_fcall *pdu, पूर्णांक16_t tag, पूर्णांक8_t type);
पूर्णांक p9pdu_finalize(काष्ठा p9_client *clnt, काष्ठा p9_fcall *pdu);
व्योम p9pdu_reset(काष्ठा p9_fcall *pdu);
माप_प्रकार pdu_पढ़ो(काष्ठा p9_fcall *pdu, व्योम *data, माप_प्रकार size);
