<शैली गुरु>
/*
 * net/tipc/server.h: Include file क्रम TIPC server code
 *
 * Copyright (c) 2012-2013, Wind River Systems
 * Copyright (c) 2017, Ericsson AB
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright holders nor the names of its
 *    contributors may be used to enकरोrse or promote products derived from
 *    this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित _TIPC_SERVER_H
#घोषणा _TIPC_SERVER_H

#समावेश "core.h"

#घोषणा TIPC_SERVER_NAME_LEN	32
#घोषणा TIPC_SUB_CLUSTER_SCOPE  0x20
#घोषणा TIPC_SUB_NODE_SCOPE     0x40
#घोषणा TIPC_SUB_NO_STATUS      0x80

व्योम tipc_topsrv_queue_evt(काष्ठा net *net, पूर्णांक conid,
			   u32 event, काष्ठा tipc_event *evt);

bool tipc_topsrv_kern_subscr(काष्ठा net *net, u32 port, u32 type, u32 lower,
			     u32 upper, u32 filter, पूर्णांक *conid);
व्योम tipc_topsrv_kern_unsubscr(काष्ठा net *net, पूर्णांक conid);

#पूर्ण_अगर
