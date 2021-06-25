<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * VMware VMCI Driver
 *
 * Copyright (C) 2012 VMware, Inc. All rights reserved.
 */

#अगर_अघोषित __VMW_VMCI_API_H__
#घोषणा __VMW_VMCI_API_H__

#समावेश <linux/uidgid.h>
#समावेश <linux/vmw_vmci_defs.h>

#अघोषित  VMCI_KERNEL_API_VERSION
#घोषणा VMCI_KERNEL_API_VERSION_1 1
#घोषणा VMCI_KERNEL_API_VERSION_2 2
#घोषणा VMCI_KERNEL_API_VERSION   VMCI_KERNEL_API_VERSION_2

काष्ठा msghdr;
प्रकार व्योम (vmci_device_shutकरोwn_fn) (व्योम *device_registration,
					व्योम *user_data);
प्रकार व्योम (*vmci_vsock_cb) (bool is_host);

पूर्णांक vmci_datagram_create_handle(u32 resource_id, u32 flags,
				vmci_datagram_recv_cb recv_cb,
				व्योम *client_data,
				काष्ठा vmci_handle *out_handle);
पूर्णांक vmci_datagram_create_handle_priv(u32 resource_id, u32 flags, u32 priv_flags,
				     vmci_datagram_recv_cb recv_cb,
				     व्योम *client_data,
				     काष्ठा vmci_handle *out_handle);
पूर्णांक vmci_datagram_destroy_handle(काष्ठा vmci_handle handle);
पूर्णांक vmci_datagram_send(काष्ठा vmci_datagram *msg);
पूर्णांक vmci_करोorbell_create(काष्ठा vmci_handle *handle, u32 flags,
			 u32 priv_flags,
			 vmci_callback notअगरy_cb, व्योम *client_data);
पूर्णांक vmci_करोorbell_destroy(काष्ठा vmci_handle handle);
पूर्णांक vmci_करोorbell_notअगरy(काष्ठा vmci_handle handle, u32 priv_flags);
u32 vmci_get_context_id(व्योम);
bool vmci_is_context_owner(u32 context_id, kuid_t uid);
पूर्णांक vmci_रेजिस्टर_vsock_callback(vmci_vsock_cb callback);

पूर्णांक vmci_event_subscribe(u32 event,
			 vmci_event_cb callback, व्योम *callback_data,
			 u32 *subid);
पूर्णांक vmci_event_unsubscribe(u32 subid);
u32 vmci_context_get_priv_flags(u32 context_id);
पूर्णांक vmci_qpair_alloc(काष्ठा vmci_qp **qpair,
		     काष्ठा vmci_handle *handle,
		     u64 produce_qsize,
		     u64 consume_qsize,
		     u32 peer, u32 flags, u32 priv_flags);
पूर्णांक vmci_qpair_detach(काष्ठा vmci_qp **qpair);
पूर्णांक vmci_qpair_get_produce_indexes(स्थिर काष्ठा vmci_qp *qpair,
				   u64 *producer_tail,
				   u64 *consumer_head);
पूर्णांक vmci_qpair_get_consume_indexes(स्थिर काष्ठा vmci_qp *qpair,
				   u64 *consumer_tail,
				   u64 *producer_head);
s64 vmci_qpair_produce_मुक्त_space(स्थिर काष्ठा vmci_qp *qpair);
s64 vmci_qpair_produce_buf_पढ़ोy(स्थिर काष्ठा vmci_qp *qpair);
s64 vmci_qpair_consume_मुक्त_space(स्थिर काष्ठा vmci_qp *qpair);
s64 vmci_qpair_consume_buf_पढ़ोy(स्थिर काष्ठा vmci_qp *qpair);
sमाप_प्रकार vmci_qpair_enqueue(काष्ठा vmci_qp *qpair,
			   स्थिर व्योम *buf, माप_प्रकार buf_size, पूर्णांक mode);
sमाप_प्रकार vmci_qpair_dequeue(काष्ठा vmci_qp *qpair,
			   व्योम *buf, माप_प्रकार buf_size, पूर्णांक mode);
sमाप_प्रकार vmci_qpair_peek(काष्ठा vmci_qp *qpair, व्योम *buf, माप_प्रकार buf_size,
			पूर्णांक mode);
sमाप_प्रकार vmci_qpair_enquev(काष्ठा vmci_qp *qpair,
			  काष्ठा msghdr *msg, माप_प्रकार iov_size, पूर्णांक mode);
sमाप_प्रकार vmci_qpair_dequev(काष्ठा vmci_qp *qpair,
			  काष्ठा msghdr *msg, माप_प्रकार iov_size, पूर्णांक mode);
sमाप_प्रकार vmci_qpair_peekv(काष्ठा vmci_qp *qpair, काष्ठा msghdr *msg, माप_प्रकार iov_size,
			 पूर्णांक mode);

#पूर्ण_अगर /* !__VMW_VMCI_API_H__ */
