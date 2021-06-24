<शैली गुरु>
/*
 * Copyright (c) 2006-2008 Chelsio, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#अगर_अघोषित _CXGB3_OFFLOAD_H
#घोषणा _CXGB3_OFFLOAD_H

#समावेश <linux/list.h>
#समावेश <linux/skbuff.h>

#समावेश "l2t.h"

#समावेश "t3cdev.h"
#समावेश "t3_cpl.h"

काष्ठा adapter;

व्योम cxgb3_offload_init(व्योम);

व्योम cxgb3_adapter_ofld(काष्ठा adapter *adapter);
व्योम cxgb3_adapter_unofld(काष्ठा adapter *adapter);
पूर्णांक cxgb3_offload_activate(काष्ठा adapter *adapter);
व्योम cxgb3_offload_deactivate(काष्ठा adapter *adapter);

व्योम cxgb3_set_dummy_ops(काष्ठा t3cdev *dev);

काष्ठा t3cdev *dev2t3cdev(काष्ठा net_device *dev);

/*
 * Client registration.  Users of T3 driver must रेजिस्टर themselves.
 * The T3 driver will call the add function of every client क्रम each T3
 * adapter activated, passing up the t3cdev ptr.  Each client fills out an
 * array of callback functions to process CPL messages.
 */

व्योम cxgb3_रेजिस्टर_client(काष्ठा cxgb3_client *client);
व्योम cxgb3_unरेजिस्टर_client(काष्ठा cxgb3_client *client);
व्योम cxgb3_add_clients(काष्ठा t3cdev *tdev);
व्योम cxgb3_हटाओ_clients(काष्ठा t3cdev *tdev);
व्योम cxgb3_event_notअगरy(काष्ठा t3cdev *tdev, u32 event, u32 port);

प्रकार पूर्णांक (*cxgb3_cpl_handler_func)(काष्ठा t3cdev *dev,
				      काष्ठा sk_buff *skb, व्योम *ctx);

क्रमागत अणु
	OFFLOAD_STATUS_UP,
	OFFLOAD_STATUS_DOWN,
	OFFLOAD_PORT_DOWN,
	OFFLOAD_PORT_UP,
	OFFLOAD_DB_FULL,
	OFFLOAD_DB_EMPTY,
	OFFLOAD_DB_DROP
पूर्ण;

काष्ठा cxgb3_client अणु
	अक्षर *name;
	व्योम (*add) (काष्ठा t3cdev *);
	व्योम (*हटाओ) (काष्ठा t3cdev *);
	cxgb3_cpl_handler_func *handlers;
	पूर्णांक (*redirect)(व्योम *ctx, काष्ठा dst_entry *old,
			काष्ठा dst_entry *new, काष्ठा l2t_entry *l2t);
	काष्ठा list_head client_list;
	व्योम (*event_handler)(काष्ठा t3cdev *tdev, u32 event, u32 port);
पूर्ण;

/*
 * TID allocation services.
 */
पूर्णांक cxgb3_alloc_atid(काष्ठा t3cdev *dev, काष्ठा cxgb3_client *client,
		     व्योम *ctx);
पूर्णांक cxgb3_alloc_stid(काष्ठा t3cdev *dev, काष्ठा cxgb3_client *client,
		     व्योम *ctx);
व्योम *cxgb3_मुक्त_atid(काष्ठा t3cdev *dev, पूर्णांक atid);
व्योम cxgb3_मुक्त_stid(काष्ठा t3cdev *dev, पूर्णांक stid);
व्योम cxgb3_insert_tid(काष्ठा t3cdev *dev, काष्ठा cxgb3_client *client,
		      व्योम *ctx, अचिन्हित पूर्णांक tid);
व्योम cxgb3_queue_tid_release(काष्ठा t3cdev *dev, अचिन्हित पूर्णांक tid);
व्योम cxgb3_हटाओ_tid(काष्ठा t3cdev *dev, व्योम *ctx, अचिन्हित पूर्णांक tid);

काष्ठा t3c_tid_entry अणु
	काष्ठा cxgb3_client *client;
	व्योम *ctx;
पूर्ण;

/* CPL message priority levels */
क्रमागत अणु
	CPL_PRIORITY_DATA = 0,	/* data messages */
	CPL_PRIORITY_SETUP = 1,	/* connection setup messages */
	CPL_PRIORITY_TEARDOWN = 0,	/* connection tearकरोwn messages */
	CPL_PRIORITY_LISTEN = 1,	/* listen start/stop messages */
	CPL_PRIORITY_ACK = 1,	/* RX ACK messages */
	CPL_PRIORITY_CONTROL = 1	/* offload control messages */
पूर्ण;

/* Flags क्रम वापस value of CPL message handlers */
क्रमागत अणु
	CPL_RET_BUF_DONE = 1, /* buffer processing करोne, buffer may be मुक्तd */
	CPL_RET_BAD_MSG = 2,  /* bad CPL message (e.g., unknown opcode) */
	CPL_RET_UNKNOWN_TID = 4	/* unexpected unknown TID */
पूर्ण;

प्रकार पूर्णांक (*cpl_handler_func)(काष्ठा t3cdev *dev, काष्ठा sk_buff *skb);

/*
 * Returns a poपूर्णांकer to the first byte of the CPL header in an sk_buff that
 * contains a CPL message.
 */
अटल अंतरभूत व्योम *cplhdr(काष्ठा sk_buff *skb)
अणु
	वापस skb->data;
पूर्ण

व्योम t3_रेजिस्टर_cpl_handler(अचिन्हित पूर्णांक opcode, cpl_handler_func h);

जोड़ listen_entry अणु
	काष्ठा t3c_tid_entry t3c_tid;
	जोड़ listen_entry *next;
पूर्ण;

जोड़ active_खोलो_entry अणु
	काष्ठा t3c_tid_entry t3c_tid;
	जोड़ active_खोलो_entry *next;
पूर्ण;

/*
 * Holds the size, base address, मुक्त list start, etc of the TID, server TID,
 * and active-खोलो TID tables क्रम a offload device.
 * The tables themselves are allocated dynamically.
 */
काष्ठा tid_info अणु
	काष्ठा t3c_tid_entry *tid_tab;
	अचिन्हित पूर्णांक ntids;
	atomic_t tids_in_use;

	जोड़ listen_entry *stid_tab;
	अचिन्हित पूर्णांक nstids;
	अचिन्हित पूर्णांक stid_base;

	जोड़ active_खोलो_entry *atid_tab;
	अचिन्हित पूर्णांक natids;
	अचिन्हित पूर्णांक atid_base;

	/*
	 * The following members are accessed R/W so we put them in their own
	 * cache lines.
	 *
	 * XXX We could combine the atid fields above with the lock here since
	 * atids are use once (unlike other tids).  OTOH the above fields are
	 * usually in cache due to tid_tab.
	 */
	spinlock_t atid_lock ____cacheline_aligned_in_smp;
	जोड़ active_खोलो_entry *aमुक्त;
	अचिन्हित पूर्णांक atids_in_use;

	spinlock_t stid_lock ____cacheline_aligned;
	जोड़ listen_entry *sमुक्त;
	अचिन्हित पूर्णांक stids_in_use;
पूर्ण;

काष्ठा t3c_data अणु
	काष्ठा list_head list_node;
	काष्ठा t3cdev *dev;
	अचिन्हित पूर्णांक tx_max_chunk;	/* max payload क्रम TX_DATA */
	अचिन्हित पूर्णांक max_wrs;	/* max in-flight WRs per connection */
	अचिन्हित पूर्णांक nmtus;
	स्थिर अचिन्हित लघु *mtus;
	काष्ठा tid_info tid_maps;

	काष्ठा t3c_tid_entry *tid_release_list;
	spinlock_t tid_release_lock;
	काष्ठा work_काष्ठा tid_release_task;

	काष्ठा sk_buff *nofail_skb;
	अचिन्हित पूर्णांक release_list_incomplete;
पूर्ण;

/*
 * t3cdev -> t3c_data accessor
 */
#घोषणा T3C_DATA(dev) (*(काष्ठा t3c_data **)&(dev)->l4opt)

#पूर्ण_अगर
