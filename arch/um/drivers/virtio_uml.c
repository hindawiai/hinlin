<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Virtio vhost-user driver
 *
 * Copyright(c) 2019 Intel Corporation
 *
 * This driver allows virtio devices to be used over a vhost-user socket.
 *
 * Guest devices can be instantiated by kernel module or command line
 * parameters. One device will be created क्रम each parameter. Syntax:
 *
 *		virtio_uml.device=<socket>:<virtio_id>[:<platक्रमm_id>]
 * where:
 *		<socket>	:= vhost-user socket path to connect
 *		<virtio_id>	:= virtio device id (as in virtio_ids.h)
 *		<platक्रमm_id>	:= (optional) platक्रमm device id
 *
 * example:
 *		virtio_uml.device=/var/uml.socket:1
 *
 * Based on Virtio MMIO driver by Pawel Moll, copyright 2011-2014, ARM Ltd.
 */
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/virtपन.स>
#समावेश <linux/virtio_config.h>
#समावेश <linux/virtio_ring.h>
#समावेश <linux/समय-पूर्णांकernal.h>
#समावेश <shared/as-layout.h>
#समावेश <irq_kern.h>
#समावेश <init.h>
#समावेश <os.h>
#समावेश "vhost_user.h"

#घोषणा MAX_SUPPORTED_QUEUE_SIZE	256

#घोषणा to_virtio_uml_device(_vdev) \
	container_of(_vdev, काष्ठा virtio_uml_device, vdev)

काष्ठा virtio_uml_platक्रमm_data अणु
	u32 virtio_device_id;
	स्थिर अक्षर *socket_path;
	काष्ठा work_काष्ठा conn_broken_wk;
	काष्ठा platक्रमm_device *pdev;
पूर्ण;

काष्ठा virtio_uml_device अणु
	काष्ठा virtio_device vdev;
	काष्ठा platक्रमm_device *pdev;

	spinlock_t sock_lock;
	पूर्णांक sock, req_fd, irq;
	u64 features;
	u64 protocol_features;
	u8 status;
	u8 रेजिस्टरed:1;
	u8 suspended:1;

	u8 config_changed_irq:1;
	uपूर्णांक64_t vq_irq_vq_map;
पूर्ण;

काष्ठा virtio_uml_vq_info अणु
	पूर्णांक kick_fd, call_fd;
	अक्षर name[32];
	bool suspended;
पूर्ण;

बाह्य अचिन्हित दीर्घ दीर्घ physmem_size, highmem;

#घोषणा vu_err(vu_dev, ...)	dev_err(&(vu_dev)->pdev->dev, ##__VA_ARGS__)

/* Vhost-user protocol */

अटल पूर्णांक full_sendmsg_fds(पूर्णांक fd, स्थिर व्योम *buf, अचिन्हित पूर्णांक len,
			    स्थिर पूर्णांक *fds, अचिन्हित पूर्णांक fds_num)
अणु
	पूर्णांक rc;

	करो अणु
		rc = os_sendmsg_fds(fd, buf, len, fds, fds_num);
		अगर (rc > 0) अणु
			buf += rc;
			len -= rc;
			fds = शून्य;
			fds_num = 0;
		पूर्ण
	पूर्ण जबतक (len && (rc >= 0 || rc == -EINTR));

	अगर (rc < 0)
		वापस rc;
	वापस 0;
पूर्ण

अटल पूर्णांक full_पढ़ो(पूर्णांक fd, व्योम *buf, पूर्णांक len, bool पातable)
अणु
	पूर्णांक rc;

	अगर (!len)
		वापस 0;

	करो अणु
		rc = os_पढ़ो_file(fd, buf, len);
		अगर (rc > 0) अणु
			buf += rc;
			len -= rc;
		पूर्ण
	पूर्ण जबतक (len && (rc > 0 || rc == -EINTR || (!पातable && rc == -EAGAIN)));

	अगर (rc < 0)
		वापस rc;
	अगर (rc == 0)
		वापस -ECONNRESET;
	वापस 0;
पूर्ण

अटल पूर्णांक vhost_user_recv_header(पूर्णांक fd, काष्ठा vhost_user_msg *msg)
अणु
	वापस full_पढ़ो(fd, msg, माप(msg->header), true);
पूर्ण

अटल पूर्णांक vhost_user_recv(काष्ठा virtio_uml_device *vu_dev,
			   पूर्णांक fd, काष्ठा vhost_user_msg *msg,
			   माप_प्रकार max_payload_size, bool रुको)
अणु
	माप_प्रकार size;
	पूर्णांक rc;

	/*
	 * In virtio समय-travel mode, we're handling all the vhost-user
	 * FDs by polling them whenever appropriate. However, we may get
	 * पूर्णांकo a situation where we're sending out an पूर्णांकerrupt message
	 * to a device (e.g. a net device) and need to handle a simulation
	 * समय message जबतक करोing so, e.g. one that tells us to update
	 * our idea of how दीर्घ we can run without scheduling.
	 *
	 * Thus, we need to not just पढ़ो() from the given fd, but need
	 * to also handle messages क्रम the simulation समय - this function
	 * करोes that क्रम us जबतक रुकोing क्रम the given fd to be पढ़ोable.
	 */
	अगर (रुको)
		समय_प्रकारravel_रुको_पढ़ोable(fd);

	rc = vhost_user_recv_header(fd, msg);

	अगर (rc == -ECONNRESET && vu_dev->रेजिस्टरed) अणु
		काष्ठा virtio_uml_platक्रमm_data *pdata;

		pdata = vu_dev->pdev->dev.platक्रमm_data;

		virtio_अवरोध_device(&vu_dev->vdev);
		schedule_work(&pdata->conn_broken_wk);
	पूर्ण
	अगर (rc)
		वापस rc;
	size = msg->header.size;
	अगर (size > max_payload_size)
		वापस -EPROTO;
	वापस full_पढ़ो(fd, &msg->payload, size, false);
पूर्ण

अटल पूर्णांक vhost_user_recv_resp(काष्ठा virtio_uml_device *vu_dev,
				काष्ठा vhost_user_msg *msg,
				माप_प्रकार max_payload_size)
अणु
	पूर्णांक rc = vhost_user_recv(vu_dev, vu_dev->sock, msg,
				 max_payload_size, true);

	अगर (rc)
		वापस rc;

	अगर (msg->header.flags != (VHOST_USER_FLAG_REPLY | VHOST_USER_VERSION))
		वापस -EPROTO;

	वापस 0;
पूर्ण

अटल पूर्णांक vhost_user_recv_u64(काष्ठा virtio_uml_device *vu_dev,
			       u64 *value)
अणु
	काष्ठा vhost_user_msg msg;
	पूर्णांक rc = vhost_user_recv_resp(vu_dev, &msg,
				      माप(msg.payload.पूर्णांकeger));

	अगर (rc)
		वापस rc;
	अगर (msg.header.size != माप(msg.payload.पूर्णांकeger))
		वापस -EPROTO;
	*value = msg.payload.पूर्णांकeger;
	वापस 0;
पूर्ण

अटल पूर्णांक vhost_user_recv_req(काष्ठा virtio_uml_device *vu_dev,
			       काष्ठा vhost_user_msg *msg,
			       माप_प्रकार max_payload_size)
अणु
	पूर्णांक rc = vhost_user_recv(vu_dev, vu_dev->req_fd, msg,
				 max_payload_size, false);

	अगर (rc)
		वापस rc;

	अगर ((msg->header.flags & ~VHOST_USER_FLAG_NEED_REPLY) !=
			VHOST_USER_VERSION)
		वापस -EPROTO;

	वापस 0;
पूर्ण

अटल पूर्णांक vhost_user_send(काष्ठा virtio_uml_device *vu_dev,
			   bool need_response, काष्ठा vhost_user_msg *msg,
			   पूर्णांक *fds, माप_प्रकार num_fds)
अणु
	माप_प्रकार size = माप(msg->header) + msg->header.size;
	अचिन्हित दीर्घ flags;
	bool request_ack;
	पूर्णांक rc;

	msg->header.flags |= VHOST_USER_VERSION;

	/*
	 * The need_response flag indicates that we alपढ़ोy need a response,
	 * e.g. to पढ़ो the features. In these हालs, करोn't request an ACK as
	 * it is meaningless. Also request an ACK only अगर supported.
	 */
	request_ack = !need_response;
	अगर (!(vu_dev->protocol_features &
			BIT_ULL(VHOST_USER_PROTOCOL_F_REPLY_ACK)))
		request_ack = false;

	अगर (request_ack)
		msg->header.flags |= VHOST_USER_FLAG_NEED_REPLY;

	spin_lock_irqsave(&vu_dev->sock_lock, flags);
	rc = full_sendmsg_fds(vu_dev->sock, msg, size, fds, num_fds);
	अगर (rc < 0)
		जाओ out;

	अगर (request_ack) अणु
		uपूर्णांक64_t status;

		rc = vhost_user_recv_u64(vu_dev, &status);
		अगर (rc)
			जाओ out;

		अगर (status) अणु
			vu_err(vu_dev, "slave reports error: %llu\n", status);
			rc = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण

out:
	spin_unlock_irqrestore(&vu_dev->sock_lock, flags);
	वापस rc;
पूर्ण

अटल पूर्णांक vhost_user_send_no_payload(काष्ठा virtio_uml_device *vu_dev,
				      bool need_response, u32 request)
अणु
	काष्ठा vhost_user_msg msg = अणु
		.header.request = request,
	पूर्ण;

	वापस vhost_user_send(vu_dev, need_response, &msg, शून्य, 0);
पूर्ण

अटल पूर्णांक vhost_user_send_no_payload_fd(काष्ठा virtio_uml_device *vu_dev,
					 u32 request, पूर्णांक fd)
अणु
	काष्ठा vhost_user_msg msg = अणु
		.header.request = request,
	पूर्ण;

	वापस vhost_user_send(vu_dev, false, &msg, &fd, 1);
पूर्ण

अटल पूर्णांक vhost_user_send_u64(काष्ठा virtio_uml_device *vu_dev,
			       u32 request, u64 value)
अणु
	काष्ठा vhost_user_msg msg = अणु
		.header.request = request,
		.header.size = माप(msg.payload.पूर्णांकeger),
		.payload.पूर्णांकeger = value,
	पूर्ण;

	वापस vhost_user_send(vu_dev, false, &msg, शून्य, 0);
पूर्ण

अटल पूर्णांक vhost_user_set_owner(काष्ठा virtio_uml_device *vu_dev)
अणु
	वापस vhost_user_send_no_payload(vu_dev, false, VHOST_USER_SET_OWNER);
पूर्ण

अटल पूर्णांक vhost_user_get_features(काष्ठा virtio_uml_device *vu_dev,
				   u64 *features)
अणु
	पूर्णांक rc = vhost_user_send_no_payload(vu_dev, true,
					    VHOST_USER_GET_FEATURES);

	अगर (rc)
		वापस rc;
	वापस vhost_user_recv_u64(vu_dev, features);
पूर्ण

अटल पूर्णांक vhost_user_set_features(काष्ठा virtio_uml_device *vu_dev,
				   u64 features)
अणु
	वापस vhost_user_send_u64(vu_dev, VHOST_USER_SET_FEATURES, features);
पूर्ण

अटल पूर्णांक vhost_user_get_protocol_features(काष्ठा virtio_uml_device *vu_dev,
					    u64 *protocol_features)
अणु
	पूर्णांक rc = vhost_user_send_no_payload(vu_dev, true,
			VHOST_USER_GET_PROTOCOL_FEATURES);

	अगर (rc)
		वापस rc;
	वापस vhost_user_recv_u64(vu_dev, protocol_features);
पूर्ण

अटल पूर्णांक vhost_user_set_protocol_features(काष्ठा virtio_uml_device *vu_dev,
					    u64 protocol_features)
अणु
	वापस vhost_user_send_u64(vu_dev, VHOST_USER_SET_PROTOCOL_FEATURES,
				   protocol_features);
पूर्ण

अटल व्योम vhost_user_reply(काष्ठा virtio_uml_device *vu_dev,
			     काष्ठा vhost_user_msg *msg, पूर्णांक response)
अणु
	काष्ठा vhost_user_msg reply = अणु
		.payload.पूर्णांकeger = response,
	पूर्ण;
	माप_प्रकार size = माप(reply.header) + माप(reply.payload.पूर्णांकeger);
	पूर्णांक rc;

	reply.header = msg->header;
	reply.header.flags &= ~VHOST_USER_FLAG_NEED_REPLY;
	reply.header.flags |= VHOST_USER_FLAG_REPLY;
	reply.header.size = माप(reply.payload.पूर्णांकeger);

	rc = full_sendmsg_fds(vu_dev->req_fd, &reply, size, शून्य, 0);

	अगर (rc)
		vu_err(vu_dev,
		       "sending reply to slave request failed: %d (size %zu)\n",
		       rc, size);
पूर्ण

अटल irqवापस_t vu_req_पढ़ो_message(काष्ठा virtio_uml_device *vu_dev,
				       काष्ठा समय_प्रकारravel_event *ev)
अणु
	काष्ठा virtqueue *vq;
	पूर्णांक response = 1;
	काष्ठा अणु
		काष्ठा vhost_user_msg msg;
		u8 extra_payload[512];
	पूर्ण msg;
	पूर्णांक rc;

	rc = vhost_user_recv_req(vu_dev, &msg.msg,
				 माप(msg.msg.payload) +
				 माप(msg.extra_payload));

	अगर (rc)
		वापस IRQ_NONE;

	चयन (msg.msg.header.request) अणु
	हाल VHOST_USER_SLAVE_CONFIG_CHANGE_MSG:
		vu_dev->config_changed_irq = true;
		response = 0;
		अवरोध;
	हाल VHOST_USER_SLAVE_VRING_CALL:
		virtio_device_क्रम_each_vq((&vu_dev->vdev), vq) अणु
			अगर (vq->index == msg.msg.payload.vring_state.index) अणु
				response = 0;
				vu_dev->vq_irq_vq_map |= BIT_ULL(vq->index);
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल VHOST_USER_SLAVE_IOTLB_MSG:
		/* not supported - VIRTIO_F_ACCESS_PLATFORM */
	हाल VHOST_USER_SLAVE_VRING_HOST_NOTIFIER_MSG:
		/* not supported - VHOST_USER_PROTOCOL_F_HOST_NOTIFIER */
	शेष:
		vu_err(vu_dev, "unexpected slave request %d\n",
		       msg.msg.header.request);
	पूर्ण

	अगर (ev && !vu_dev->suspended)
		समय_प्रकारravel_add_irq_event(ev);

	अगर (msg.msg.header.flags & VHOST_USER_FLAG_NEED_REPLY)
		vhost_user_reply(vu_dev, &msg.msg, response);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t vu_req_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा virtio_uml_device *vu_dev = data;
	irqवापस_t ret = IRQ_HANDLED;

	अगर (!um_irq_समयtravel_handler_used())
		ret = vu_req_पढ़ो_message(vu_dev, शून्य);

	अगर (vu_dev->vq_irq_vq_map) अणु
		काष्ठा virtqueue *vq;

		virtio_device_क्रम_each_vq((&vu_dev->vdev), vq) अणु
			अगर (vu_dev->vq_irq_vq_map & BIT_ULL(vq->index))
				vring_पूर्णांकerrupt(0 /* ignored */, vq);
		पूर्ण
		vu_dev->vq_irq_vq_map = 0;
	पूर्ण अन्यथा अगर (vu_dev->config_changed_irq) अणु
		virtio_config_changed(&vu_dev->vdev);
		vu_dev->config_changed_irq = false;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम vu_req_पूर्णांकerrupt_comm_handler(पूर्णांक irq, पूर्णांक fd, व्योम *data,
					  काष्ठा समय_प्रकारravel_event *ev)
अणु
	vu_req_पढ़ो_message(data, ev);
पूर्ण

अटल पूर्णांक vhost_user_init_slave_req(काष्ठा virtio_uml_device *vu_dev)
अणु
	पूर्णांक rc, req_fds[2];

	/* Use a pipe क्रम slave req fd, SIGIO is not supported क्रम eventfd */
	rc = os_pipe(req_fds, true, true);
	अगर (rc < 0)
		वापस rc;
	vu_dev->req_fd = req_fds[0];

	rc = um_request_irq_tt(UM_IRQ_ALLOC, vu_dev->req_fd, IRQ_READ,
			       vu_req_पूर्णांकerrupt, IRQF_SHARED,
			       vu_dev->pdev->name, vu_dev,
			       vu_req_पूर्णांकerrupt_comm_handler);
	अगर (rc < 0)
		जाओ err_बंद;

	vu_dev->irq = rc;

	rc = vhost_user_send_no_payload_fd(vu_dev, VHOST_USER_SET_SLAVE_REQ_FD,
					   req_fds[1]);
	अगर (rc)
		जाओ err_मुक्त_irq;

	जाओ out;

err_मुक्त_irq:
	um_मुक्त_irq(vu_dev->irq, vu_dev);
err_बंद:
	os_बंद_file(req_fds[0]);
out:
	/* Close unused ग_लिखो end of request fds */
	os_बंद_file(req_fds[1]);
	वापस rc;
पूर्ण

अटल पूर्णांक vhost_user_init(काष्ठा virtio_uml_device *vu_dev)
अणु
	पूर्णांक rc = vhost_user_set_owner(vu_dev);

	अगर (rc)
		वापस rc;
	rc = vhost_user_get_features(vu_dev, &vu_dev->features);
	अगर (rc)
		वापस rc;

	अगर (vu_dev->features & BIT_ULL(VHOST_USER_F_PROTOCOL_FEATURES)) अणु
		rc = vhost_user_get_protocol_features(vu_dev,
				&vu_dev->protocol_features);
		अगर (rc)
			वापस rc;
		vu_dev->protocol_features &= VHOST_USER_SUPPORTED_PROTOCOL_F;
		rc = vhost_user_set_protocol_features(vu_dev,
				vu_dev->protocol_features);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (vu_dev->protocol_features &
			BIT_ULL(VHOST_USER_PROTOCOL_F_SLAVE_REQ)) अणु
		rc = vhost_user_init_slave_req(vu_dev);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vhost_user_get_config(काष्ठा virtio_uml_device *vu_dev,
				  u32 offset, व्योम *buf, u32 len)
अणु
	u32 cfg_size = offset + len;
	काष्ठा vhost_user_msg *msg;
	माप_प्रकार payload_size = माप(msg->payload.config) + cfg_size;
	माप_प्रकार msg_size = माप(msg->header) + payload_size;
	पूर्णांक rc;

	अगर (!(vu_dev->protocol_features &
	      BIT_ULL(VHOST_USER_PROTOCOL_F_CONFIG)))
		वापस;

	msg = kzalloc(msg_size, GFP_KERNEL);
	अगर (!msg)
		वापस;
	msg->header.request = VHOST_USER_GET_CONFIG;
	msg->header.size = payload_size;
	msg->payload.config.offset = 0;
	msg->payload.config.size = cfg_size;

	rc = vhost_user_send(vu_dev, true, msg, शून्य, 0);
	अगर (rc) अणु
		vu_err(vu_dev, "sending VHOST_USER_GET_CONFIG failed: %d\n",
		       rc);
		जाओ मुक्त;
	पूर्ण

	rc = vhost_user_recv_resp(vu_dev, msg, msg_size);
	अगर (rc) अणु
		vu_err(vu_dev,
		       "receiving VHOST_USER_GET_CONFIG response failed: %d\n",
		       rc);
		जाओ मुक्त;
	पूर्ण

	अगर (msg->header.size != payload_size ||
	    msg->payload.config.size != cfg_size) अणु
		rc = -EPROTO;
		vu_err(vu_dev,
		       "Invalid VHOST_USER_GET_CONFIG sizes (payload %d expected %zu, config %u expected %u)\n",
		       msg->header.size, payload_size,
		       msg->payload.config.size, cfg_size);
		जाओ मुक्त;
	पूर्ण
	स_नकल(buf, msg->payload.config.payload + offset, len);

मुक्त:
	kमुक्त(msg);
पूर्ण

अटल व्योम vhost_user_set_config(काष्ठा virtio_uml_device *vu_dev,
				  u32 offset, स्थिर व्योम *buf, u32 len)
अणु
	काष्ठा vhost_user_msg *msg;
	माप_प्रकार payload_size = माप(msg->payload.config) + len;
	माप_प्रकार msg_size = माप(msg->header) + payload_size;
	पूर्णांक rc;

	अगर (!(vu_dev->protocol_features &
	      BIT_ULL(VHOST_USER_PROTOCOL_F_CONFIG)))
		वापस;

	msg = kzalloc(msg_size, GFP_KERNEL);
	अगर (!msg)
		वापस;
	msg->header.request = VHOST_USER_SET_CONFIG;
	msg->header.size = payload_size;
	msg->payload.config.offset = offset;
	msg->payload.config.size = len;
	स_नकल(msg->payload.config.payload, buf, len);

	rc = vhost_user_send(vu_dev, false, msg, शून्य, 0);
	अगर (rc)
		vu_err(vu_dev, "sending VHOST_USER_SET_CONFIG failed: %d\n",
		       rc);

	kमुक्त(msg);
पूर्ण

अटल पूर्णांक vhost_user_init_mem_region(u64 addr, u64 size, पूर्णांक *fd_out,
				      काष्ठा vhost_user_mem_region *region_out)
अणु
	अचिन्हित दीर्घ दीर्घ mem_offset;
	पूर्णांक rc = phys_mapping(addr, &mem_offset);

	अगर (WARN(rc < 0, "phys_mapping of 0x%llx returned %d\n", addr, rc))
		वापस -EFAULT;
	*fd_out = rc;
	region_out->guest_addr = addr;
	region_out->user_addr = addr;
	region_out->size = size;
	region_out->mmap_offset = mem_offset;

	/* Ensure mapping is valid क्रम the entire region */
	rc = phys_mapping(addr + size - 1, &mem_offset);
	अगर (WARN(rc != *fd_out, "phys_mapping of 0x%llx failed: %d != %d\n",
		 addr + size - 1, rc, *fd_out))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक vhost_user_set_mem_table(काष्ठा virtio_uml_device *vu_dev)
अणु
	काष्ठा vhost_user_msg msg = अणु
		.header.request = VHOST_USER_SET_MEM_TABLE,
		.header.size = माप(msg.payload.mem_regions),
		.payload.mem_regions.num = 1,
	पूर्ण;
	अचिन्हित दीर्घ reserved = uml_reserved - uml_physmem;
	पूर्णांक fds[2];
	पूर्णांक rc;

	/*
	 * This is a bit tricky, see also the comment with setup_physmem().
	 *
	 * Essentially, setup_physmem() uses a file to mmap() our physmem,
	 * but the code and data we *alपढ़ोy* have is omitted. To us, this
	 * is no dअगरference, since they both become part of our address
	 * space and memory consumption. To somebody looking in from the
	 * outside, however, it is dअगरferent because the part of our memory
	 * consumption that's alपढ़ोy part of the binary (code/data) is not
	 * mapped from the file, so it's not visible to another mmap from
	 * the file descriptor.
	 *
	 * Thus, करोn't advertise this space to the vhost-user slave. This
	 * means that the slave will likely पात or similar when we give
	 * it an address from the hidden range, since it's not marked as
	 * a valid address, but at least that way we detect the issue and
	 * करोn't just have the slave पढ़ो an all-zeroes buffer from the
	 * shared memory file, or ग_लिखो something there that we can never
	 * see (depending on the direction of the virtqueue traffic.)
	 *
	 * Since we usually करोn't want to use .text क्रम virtio buffers,
	 * this effectively means that you cannot use
	 *  1) global variables, which are in the .bss and not in the shm
	 *     file-backed memory
	 *  2) the stack in some processes, depending on where they have
	 *     their stack (or maybe only no पूर्णांकerrupt stack?)
	 *
	 * The stack is alपढ़ोy not typically valid क्रम DMA, so this isn't
	 * much of a restriction, but global variables might be encountered.
	 *
	 * It might be possible to fix it by copying around the data that's
	 * between bss_start and where we map the file now, but it's not
	 * something that you typically encounter with virtio drivers, so
	 * it didn't seem worthजबतक.
	 */
	rc = vhost_user_init_mem_region(reserved, physmem_size - reserved,
					&fds[0],
					&msg.payload.mem_regions.regions[0]);

	अगर (rc < 0)
		वापस rc;
	अगर (highmem) अणु
		msg.payload.mem_regions.num++;
		rc = vhost_user_init_mem_region(__pa(end_iomem), highmem,
				&fds[1], &msg.payload.mem_regions.regions[1]);
		अगर (rc < 0)
			वापस rc;
	पूर्ण

	वापस vhost_user_send(vu_dev, false, &msg, fds,
			       msg.payload.mem_regions.num);
पूर्ण

अटल पूर्णांक vhost_user_set_vring_state(काष्ठा virtio_uml_device *vu_dev,
				      u32 request, u32 index, u32 num)
अणु
	काष्ठा vhost_user_msg msg = अणु
		.header.request = request,
		.header.size = माप(msg.payload.vring_state),
		.payload.vring_state.index = index,
		.payload.vring_state.num = num,
	पूर्ण;

	वापस vhost_user_send(vu_dev, false, &msg, शून्य, 0);
पूर्ण

अटल पूर्णांक vhost_user_set_vring_num(काष्ठा virtio_uml_device *vu_dev,
				    u32 index, u32 num)
अणु
	वापस vhost_user_set_vring_state(vu_dev, VHOST_USER_SET_VRING_NUM,
					  index, num);
पूर्ण

अटल पूर्णांक vhost_user_set_vring_base(काष्ठा virtio_uml_device *vu_dev,
				     u32 index, u32 offset)
अणु
	वापस vhost_user_set_vring_state(vu_dev, VHOST_USER_SET_VRING_BASE,
					  index, offset);
पूर्ण

अटल पूर्णांक vhost_user_set_vring_addr(काष्ठा virtio_uml_device *vu_dev,
				     u32 index, u64 desc, u64 used, u64 avail,
				     u64 log)
अणु
	काष्ठा vhost_user_msg msg = अणु
		.header.request = VHOST_USER_SET_VRING_ADDR,
		.header.size = माप(msg.payload.vring_addr),
		.payload.vring_addr.index = index,
		.payload.vring_addr.desc = desc,
		.payload.vring_addr.used = used,
		.payload.vring_addr.avail = avail,
		.payload.vring_addr.log = log,
	पूर्ण;

	वापस vhost_user_send(vu_dev, false, &msg, शून्य, 0);
पूर्ण

अटल पूर्णांक vhost_user_set_vring_fd(काष्ठा virtio_uml_device *vu_dev,
				   u32 request, पूर्णांक index, पूर्णांक fd)
अणु
	काष्ठा vhost_user_msg msg = अणु
		.header.request = request,
		.header.size = माप(msg.payload.पूर्णांकeger),
		.payload.पूर्णांकeger = index,
	पूर्ण;

	अगर (index & ~VHOST_USER_VRING_INDEX_MASK)
		वापस -EINVAL;
	अगर (fd < 0) अणु
		msg.payload.पूर्णांकeger |= VHOST_USER_VRING_POLL_MASK;
		वापस vhost_user_send(vu_dev, false, &msg, शून्य, 0);
	पूर्ण
	वापस vhost_user_send(vu_dev, false, &msg, &fd, 1);
पूर्ण

अटल पूर्णांक vhost_user_set_vring_call(काष्ठा virtio_uml_device *vu_dev,
				     पूर्णांक index, पूर्णांक fd)
अणु
	वापस vhost_user_set_vring_fd(vu_dev, VHOST_USER_SET_VRING_CALL,
				       index, fd);
पूर्ण

अटल पूर्णांक vhost_user_set_vring_kick(काष्ठा virtio_uml_device *vu_dev,
				     पूर्णांक index, पूर्णांक fd)
अणु
	वापस vhost_user_set_vring_fd(vu_dev, VHOST_USER_SET_VRING_KICK,
				       index, fd);
पूर्ण

अटल पूर्णांक vhost_user_set_vring_enable(काष्ठा virtio_uml_device *vu_dev,
				       u32 index, bool enable)
अणु
	अगर (!(vu_dev->features & BIT_ULL(VHOST_USER_F_PROTOCOL_FEATURES)))
		वापस 0;

	वापस vhost_user_set_vring_state(vu_dev, VHOST_USER_SET_VRING_ENABLE,
					  index, enable);
पूर्ण


/* Virtio पूर्णांकerface */

अटल bool vu_notअगरy(काष्ठा virtqueue *vq)
अणु
	काष्ठा virtio_uml_vq_info *info = vq->priv;
	स्थिर uपूर्णांक64_t n = 1;
	पूर्णांक rc;

	अगर (info->suspended)
		वापस true;

	समय_प्रकारravel_propagate_समय();

	अगर (info->kick_fd < 0) अणु
		काष्ठा virtio_uml_device *vu_dev;

		vu_dev = to_virtio_uml_device(vq->vdev);

		वापस vhost_user_set_vring_state(vu_dev, VHOST_USER_VRING_KICK,
						  vq->index, 0) == 0;
	पूर्ण

	करो अणु
		rc = os_ग_लिखो_file(info->kick_fd, &n, माप(n));
	पूर्ण जबतक (rc == -EINTR);
	वापस !WARN(rc != माप(n), "write returned %d\n", rc);
पूर्ण

अटल irqवापस_t vu_पूर्णांकerrupt(पूर्णांक irq, व्योम *opaque)
अणु
	काष्ठा virtqueue *vq = opaque;
	काष्ठा virtio_uml_vq_info *info = vq->priv;
	uपूर्णांक64_t n;
	पूर्णांक rc;
	irqवापस_t ret = IRQ_NONE;

	करो अणु
		rc = os_पढ़ो_file(info->call_fd, &n, माप(n));
		अगर (rc == माप(n))
			ret |= vring_पूर्णांकerrupt(irq, vq);
	पूर्ण जबतक (rc == माप(n) || rc == -EINTR);
	WARN(rc != -EAGAIN, "read returned %d\n", rc);
	वापस ret;
पूर्ण


अटल व्योम vu_get(काष्ठा virtio_device *vdev, अचिन्हित offset,
		   व्योम *buf, अचिन्हित len)
अणु
	काष्ठा virtio_uml_device *vu_dev = to_virtio_uml_device(vdev);

	vhost_user_get_config(vu_dev, offset, buf, len);
पूर्ण

अटल व्योम vu_set(काष्ठा virtio_device *vdev, अचिन्हित offset,
		   स्थिर व्योम *buf, अचिन्हित len)
अणु
	काष्ठा virtio_uml_device *vu_dev = to_virtio_uml_device(vdev);

	vhost_user_set_config(vu_dev, offset, buf, len);
पूर्ण

अटल u8 vu_get_status(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_uml_device *vu_dev = to_virtio_uml_device(vdev);

	वापस vu_dev->status;
पूर्ण

अटल व्योम vu_set_status(काष्ठा virtio_device *vdev, u8 status)
अणु
	काष्ठा virtio_uml_device *vu_dev = to_virtio_uml_device(vdev);

	vu_dev->status = status;
पूर्ण

अटल व्योम vu_reset(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_uml_device *vu_dev = to_virtio_uml_device(vdev);

	vu_dev->status = 0;
पूर्ण

अटल व्योम vu_del_vq(काष्ठा virtqueue *vq)
अणु
	काष्ठा virtio_uml_vq_info *info = vq->priv;

	अगर (info->call_fd >= 0) अणु
		काष्ठा virtio_uml_device *vu_dev;

		vu_dev = to_virtio_uml_device(vq->vdev);

		um_मुक्त_irq(vu_dev->irq, vq);
		os_बंद_file(info->call_fd);
	पूर्ण

	अगर (info->kick_fd >= 0)
		os_बंद_file(info->kick_fd);

	vring_del_virtqueue(vq);
	kमुक्त(info);
पूर्ण

अटल व्योम vu_del_vqs(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_uml_device *vu_dev = to_virtio_uml_device(vdev);
	काष्ठा virtqueue *vq, *n;
	u64 features;

	/* Note: reverse order as a workaround to a decoding bug in snabb */
	list_क्रम_each_entry_reverse(vq, &vdev->vqs, list)
		WARN_ON(vhost_user_set_vring_enable(vu_dev, vq->index, false));

	/* Ensure previous messages have been processed */
	WARN_ON(vhost_user_get_features(vu_dev, &features));

	list_क्रम_each_entry_safe(vq, n, &vdev->vqs, list)
		vu_del_vq(vq);
पूर्ण

अटल पूर्णांक vu_setup_vq_call_fd(काष्ठा virtio_uml_device *vu_dev,
			       काष्ठा virtqueue *vq)
अणु
	काष्ठा virtio_uml_vq_info *info = vq->priv;
	पूर्णांक call_fds[2];
	पूर्णांक rc;

	/* no call FD needed/desired in this हाल */
	अगर (vu_dev->protocol_features &
			BIT_ULL(VHOST_USER_PROTOCOL_F_INBAND_NOTIFICATIONS) &&
	    vu_dev->protocol_features &
			BIT_ULL(VHOST_USER_PROTOCOL_F_SLAVE_REQ)) अणु
		info->call_fd = -1;
		वापस 0;
	पूर्ण

	/* Use a pipe क्रम call fd, since SIGIO is not supported क्रम eventfd */
	rc = os_pipe(call_fds, true, true);
	अगर (rc < 0)
		वापस rc;

	info->call_fd = call_fds[0];
	rc = um_request_irq(vu_dev->irq, info->call_fd, IRQ_READ,
			    vu_पूर्णांकerrupt, IRQF_SHARED, info->name, vq);
	अगर (rc < 0)
		जाओ बंद_both;

	rc = vhost_user_set_vring_call(vu_dev, vq->index, call_fds[1]);
	अगर (rc)
		जाओ release_irq;

	जाओ out;

release_irq:
	um_मुक्त_irq(vu_dev->irq, vq);
बंद_both:
	os_बंद_file(call_fds[0]);
out:
	/* Close (unused) ग_लिखो end of call fds */
	os_बंद_file(call_fds[1]);

	वापस rc;
पूर्ण

अटल काष्ठा virtqueue *vu_setup_vq(काष्ठा virtio_device *vdev,
				     अचिन्हित index, vq_callback_t *callback,
				     स्थिर अक्षर *name, bool ctx)
अणु
	काष्ठा virtio_uml_device *vu_dev = to_virtio_uml_device(vdev);
	काष्ठा platक्रमm_device *pdev = vu_dev->pdev;
	काष्ठा virtio_uml_vq_info *info;
	काष्ठा virtqueue *vq;
	पूर्णांक num = MAX_SUPPORTED_QUEUE_SIZE;
	पूर्णांक rc;

	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (!info) अणु
		rc = -ENOMEM;
		जाओ error_kzalloc;
	पूर्ण
	snम_लिखो(info->name, माप(info->name), "%s.%d-%s", pdev->name,
		 pdev->id, name);

	vq = vring_create_virtqueue(index, num, PAGE_SIZE, vdev, true, true,
				    ctx, vu_notअगरy, callback, info->name);
	अगर (!vq) अणु
		rc = -ENOMEM;
		जाओ error_create;
	पूर्ण
	vq->priv = info;
	num = virtqueue_get_vring_size(vq);

	अगर (vu_dev->protocol_features &
			BIT_ULL(VHOST_USER_PROTOCOL_F_INBAND_NOTIFICATIONS)) अणु
		info->kick_fd = -1;
	पूर्ण अन्यथा अणु
		rc = os_eventfd(0, 0);
		अगर (rc < 0)
			जाओ error_kick;
		info->kick_fd = rc;
	पूर्ण

	rc = vu_setup_vq_call_fd(vu_dev, vq);
	अगर (rc)
		जाओ error_call;

	rc = vhost_user_set_vring_num(vu_dev, index, num);
	अगर (rc)
		जाओ error_setup;

	rc = vhost_user_set_vring_base(vu_dev, index, 0);
	अगर (rc)
		जाओ error_setup;

	rc = vhost_user_set_vring_addr(vu_dev, index,
				       virtqueue_get_desc_addr(vq),
				       virtqueue_get_used_addr(vq),
				       virtqueue_get_avail_addr(vq),
				       (u64) -1);
	अगर (rc)
		जाओ error_setup;

	वापस vq;

error_setup:
	अगर (info->call_fd >= 0) अणु
		um_मुक्त_irq(vu_dev->irq, vq);
		os_बंद_file(info->call_fd);
	पूर्ण
error_call:
	अगर (info->kick_fd >= 0)
		os_बंद_file(info->kick_fd);
error_kick:
	vring_del_virtqueue(vq);
error_create:
	kमुक्त(info);
error_kzalloc:
	वापस ERR_PTR(rc);
पूर्ण

अटल पूर्णांक vu_find_vqs(काष्ठा virtio_device *vdev, अचिन्हित nvqs,
		       काष्ठा virtqueue *vqs[], vq_callback_t *callbacks[],
		       स्थिर अक्षर * स्थिर names[], स्थिर bool *ctx,
		       काष्ठा irq_affinity *desc)
अणु
	काष्ठा virtio_uml_device *vu_dev = to_virtio_uml_device(vdev);
	पूर्णांक i, queue_idx = 0, rc;
	काष्ठा virtqueue *vq;

	/* not supported क्रम now */
	अगर (WARN_ON(nvqs > 64))
		वापस -EINVAL;

	rc = vhost_user_set_mem_table(vu_dev);
	अगर (rc)
		वापस rc;

	क्रम (i = 0; i < nvqs; ++i) अणु
		अगर (!names[i]) अणु
			vqs[i] = शून्य;
			जारी;
		पूर्ण

		vqs[i] = vu_setup_vq(vdev, queue_idx++, callbacks[i], names[i],
				     ctx ? ctx[i] : false);
		अगर (IS_ERR(vqs[i])) अणु
			rc = PTR_ERR(vqs[i]);
			जाओ error_setup;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(vq, &vdev->vqs, list) अणु
		काष्ठा virtio_uml_vq_info *info = vq->priv;

		अगर (info->kick_fd >= 0) अणु
			rc = vhost_user_set_vring_kick(vu_dev, vq->index,
						       info->kick_fd);
			अगर (rc)
				जाओ error_setup;
		पूर्ण

		rc = vhost_user_set_vring_enable(vu_dev, vq->index, true);
		अगर (rc)
			जाओ error_setup;
	पूर्ण

	वापस 0;

error_setup:
	vu_del_vqs(vdev);
	वापस rc;
पूर्ण

अटल u64 vu_get_features(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_uml_device *vu_dev = to_virtio_uml_device(vdev);

	वापस vu_dev->features;
पूर्ण

अटल पूर्णांक vu_finalize_features(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_uml_device *vu_dev = to_virtio_uml_device(vdev);
	u64 supported = vdev->features & VHOST_USER_SUPPORTED_F;

	vring_transport_features(vdev);
	vu_dev->features = vdev->features | supported;

	वापस vhost_user_set_features(vu_dev, vu_dev->features);
पूर्ण

अटल स्थिर अक्षर *vu_bus_name(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_uml_device *vu_dev = to_virtio_uml_device(vdev);

	वापस vu_dev->pdev->name;
पूर्ण

अटल स्थिर काष्ठा virtio_config_ops virtio_uml_config_ops = अणु
	.get = vu_get,
	.set = vu_set,
	.get_status = vu_get_status,
	.set_status = vu_set_status,
	.reset = vu_reset,
	.find_vqs = vu_find_vqs,
	.del_vqs = vu_del_vqs,
	.get_features = vu_get_features,
	.finalize_features = vu_finalize_features,
	.bus_name = vu_bus_name,
पूर्ण;

अटल व्योम virtio_uml_release_dev(काष्ठा device *d)
अणु
	काष्ठा virtio_device *vdev =
			container_of(d, काष्ठा virtio_device, dev);
	काष्ठा virtio_uml_device *vu_dev = to_virtio_uml_device(vdev);

	/* might not have been खोलोed due to not negotiating the feature */
	अगर (vu_dev->req_fd >= 0) अणु
		um_मुक्त_irq(vu_dev->irq, vu_dev);
		os_बंद_file(vu_dev->req_fd);
	पूर्ण

	os_बंद_file(vu_dev->sock);
	kमुक्त(vu_dev);
पूर्ण

/* Platक्रमm device */

अटल पूर्णांक virtio_uml_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा virtio_uml_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;
	काष्ठा virtio_uml_device *vu_dev;
	पूर्णांक rc;

	अगर (!pdata)
		वापस -EINVAL;

	vu_dev = kzalloc(माप(*vu_dev), GFP_KERNEL);
	अगर (!vu_dev)
		वापस -ENOMEM;

	vu_dev->vdev.dev.parent = &pdev->dev;
	vu_dev->vdev.dev.release = virtio_uml_release_dev;
	vu_dev->vdev.config = &virtio_uml_config_ops;
	vu_dev->vdev.id.device = pdata->virtio_device_id;
	vu_dev->vdev.id.venकरोr = VIRTIO_DEV_ANY_ID;
	vu_dev->pdev = pdev;
	vu_dev->req_fd = -1;

	करो अणु
		rc = os_connect_socket(pdata->socket_path);
	पूर्ण जबतक (rc == -EINTR);
	अगर (rc < 0)
		वापस rc;
	vu_dev->sock = rc;

	spin_lock_init(&vu_dev->sock_lock);

	rc = vhost_user_init(vu_dev);
	अगर (rc)
		जाओ error_init;

	platक्रमm_set_drvdata(pdev, vu_dev);

	device_set_wakeup_capable(&vu_dev->vdev.dev, true);

	rc = रेजिस्टर_virtio_device(&vu_dev->vdev);
	अगर (rc)
		put_device(&vu_dev->vdev.dev);
	vu_dev->रेजिस्टरed = 1;
	वापस rc;

error_init:
	os_बंद_file(vu_dev->sock);
	वापस rc;
पूर्ण

अटल पूर्णांक virtio_uml_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा virtio_uml_device *vu_dev = platक्रमm_get_drvdata(pdev);

	unरेजिस्टर_virtio_device(&vu_dev->vdev);
	वापस 0;
पूर्ण

/* Command line device list */

अटल व्योम vu_cmdline_release_dev(काष्ठा device *d)
अणु
पूर्ण

अटल काष्ठा device vu_cmdline_parent = अणु
	.init_name = "virtio-uml-cmdline",
	.release = vu_cmdline_release_dev,
पूर्ण;

अटल bool vu_cmdline_parent_रेजिस्टरed;
अटल पूर्णांक vu_cmdline_id;

अटल पूर्णांक vu_unरेजिस्टर_cmdline_device(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा virtio_uml_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;

	kमुक्त(pdata->socket_path);
	platक्रमm_device_unरेजिस्टर(pdev);
	वापस 0;
पूर्ण

अटल व्योम vu_conn_broken(काष्ठा work_काष्ठा *wk)
अणु
	काष्ठा virtio_uml_platक्रमm_data *pdata;

	pdata = container_of(wk, काष्ठा virtio_uml_platक्रमm_data, conn_broken_wk);
	vu_unरेजिस्टर_cmdline_device(&pdata->pdev->dev, शून्य);
पूर्ण

अटल पूर्णांक vu_cmdline_set(स्थिर अक्षर *device, स्थिर काष्ठा kernel_param *kp)
अणु
	स्थिर अक्षर *ids = म_अक्षर(device, ':');
	अचिन्हित पूर्णांक virtio_device_id;
	पूर्णांक processed, consumed, err;
	अक्षर *socket_path;
	काष्ठा virtio_uml_platक्रमm_data pdata, *ppdata;
	काष्ठा platक्रमm_device *pdev;

	अगर (!ids || ids == device)
		वापस -EINVAL;

	processed = माला_पूछो(ids, ":%u%n:%d%n",
			   &virtio_device_id, &consumed,
			   &vu_cmdline_id, &consumed);

	अगर (processed < 1 || ids[consumed])
		वापस -EINVAL;

	अगर (!vu_cmdline_parent_रेजिस्टरed) अणु
		err = device_रेजिस्टर(&vu_cmdline_parent);
		अगर (err) अणु
			pr_err("Failed to register parent device!\n");
			put_device(&vu_cmdline_parent);
			वापस err;
		पूर्ण
		vu_cmdline_parent_रेजिस्टरed = true;
	पूर्ण

	socket_path = kmemdup_nul(device, ids - device, GFP_KERNEL);
	अगर (!socket_path)
		वापस -ENOMEM;

	pdata.virtio_device_id = (u32) virtio_device_id;
	pdata.socket_path = socket_path;

	pr_info("Registering device virtio-uml.%d id=%d at %s\n",
		vu_cmdline_id, virtio_device_id, socket_path);

	pdev = platक्रमm_device_रेजिस्टर_data(&vu_cmdline_parent, "virtio-uml",
					     vu_cmdline_id++, &pdata,
					     माप(pdata));
	err = PTR_ERR_OR_ZERO(pdev);
	अगर (err)
		जाओ मुक्त;

	ppdata = pdev->dev.platक्रमm_data;
	ppdata->pdev = pdev;
	INIT_WORK(&ppdata->conn_broken_wk, vu_conn_broken);

	वापस 0;

मुक्त:
	kमुक्त(socket_path);
	वापस err;
पूर्ण

अटल पूर्णांक vu_cmdline_get_device(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा virtio_uml_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;
	अक्षर *buffer = data;
	अचिन्हित पूर्णांक len = म_माप(buffer);

	snम_लिखो(buffer + len, PAGE_SIZE - len, "%s:%d:%d\n",
		 pdata->socket_path, pdata->virtio_device_id, pdev->id);
	वापस 0;
पूर्ण

अटल पूर्णांक vu_cmdline_get(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	buffer[0] = '\0';
	अगर (vu_cmdline_parent_रेजिस्टरed)
		device_क्रम_each_child(&vu_cmdline_parent, buffer,
				      vu_cmdline_get_device);
	वापस म_माप(buffer) + 1;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops vu_cmdline_param_ops = अणु
	.set = vu_cmdline_set,
	.get = vu_cmdline_get,
पूर्ण;

device_param_cb(device, &vu_cmdline_param_ops, शून्य, S_IRUSR);
__uml_help(vu_cmdline_param_ops,
"virtio_uml.device=<socket>:<virtio_id>[:<platform_id>]\n"
"    Configure a virtio device over a vhost-user socket.\n"
"    See virtio_ids.h for a list of possible virtio device id values.\n"
"    Optionally use a specific platform_device id.\n\n"
);


अटल व्योम vu_unरेजिस्टर_cmdline_devices(व्योम)
अणु
	अगर (vu_cmdline_parent_रेजिस्टरed) अणु
		device_क्रम_each_child(&vu_cmdline_parent, शून्य,
				      vu_unरेजिस्टर_cmdline_device);
		device_unरेजिस्टर(&vu_cmdline_parent);
		vu_cmdline_parent_रेजिस्टरed = false;
	पूर्ण
पूर्ण

/* Platक्रमm driver */

अटल स्थिर काष्ठा of_device_id virtio_uml_match[] = अणु
	अणु .compatible = "virtio,uml", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, virtio_uml_match);

अटल पूर्णांक virtio_uml_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	काष्ठा virtio_uml_device *vu_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा virtqueue *vq;

	virtio_device_क्रम_each_vq((&vu_dev->vdev), vq) अणु
		काष्ठा virtio_uml_vq_info *info = vq->priv;

		info->suspended = true;
		vhost_user_set_vring_enable(vu_dev, vq->index, false);
	पूर्ण

	अगर (!device_may_wakeup(&vu_dev->vdev.dev)) अणु
		vu_dev->suspended = true;
		वापस 0;
	पूर्ण

	वापस irq_set_irq_wake(vu_dev->irq, 1);
पूर्ण

अटल पूर्णांक virtio_uml_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा virtio_uml_device *vu_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा virtqueue *vq;

	virtio_device_क्रम_each_vq((&vu_dev->vdev), vq) अणु
		काष्ठा virtio_uml_vq_info *info = vq->priv;

		info->suspended = false;
		vhost_user_set_vring_enable(vu_dev, vq->index, true);
	पूर्ण

	vu_dev->suspended = false;

	अगर (!device_may_wakeup(&vu_dev->vdev.dev))
		वापस 0;

	वापस irq_set_irq_wake(vu_dev->irq, 0);
पूर्ण

अटल काष्ठा platक्रमm_driver virtio_uml_driver = अणु
	.probe = virtio_uml_probe,
	.हटाओ = virtio_uml_हटाओ,
	.driver = अणु
		.name = "virtio-uml",
		.of_match_table = virtio_uml_match,
	पूर्ण,
	.suspend = virtio_uml_suspend,
	.resume = virtio_uml_resume,
पूर्ण;

अटल पूर्णांक __init virtio_uml_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&virtio_uml_driver);
पूर्ण

अटल व्योम __निकास virtio_uml_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&virtio_uml_driver);
	vu_unरेजिस्टर_cmdline_devices();
पूर्ण

module_init(virtio_uml_init);
module_निकास(virtio_uml_निकास);
__uml_निकासcall(virtio_uml_निकास);

MODULE_DESCRIPTION("UML driver for vhost-user virtio devices");
MODULE_LICENSE("GPL");
