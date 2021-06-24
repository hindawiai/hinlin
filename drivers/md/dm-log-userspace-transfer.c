<शैली गुरु>
/*
 * Copyright (C) 2006-2009 Red Hat, Inc.
 *
 * This file is released under the LGPL.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/connector.h>
#समावेश <linux/device-mapper.h>
#समावेश <linux/dm-log-userspace.h>

#समावेश "dm-log-userspace-transfer.h"

अटल uपूर्णांक32_t dm_ulog_seq;

/*
 * Netlink/Connector is an unreliable protocol.  How दीर्घ should
 * we रुको क्रम a response beक्रमe assuming it was lost and retrying?
 * (If we करो receive a response after this समय, it will be discarded
 * and the response to the resent request will be रुकोed क्रम.
 */
#घोषणा DM_ULOG_RETRY_TIMEOUT (15 * HZ)

/*
 * Pre-allocated space क्रम speed
 */
#घोषणा DM_ULOG_PREALLOCED_SIZE 512
अटल काष्ठा cn_msg *pपुनः_स्मृतिed_cn_msg;
अटल काष्ठा dm_ulog_request *pपुनः_स्मृतिed_ulog_tfr;

अटल काष्ठा cb_id ulog_cn_id = अणु
	.idx = CN_IDX_DM,
	.val = CN_VAL_DM_USERSPACE_LOG
पूर्ण;

अटल DEFINE_MUTEX(dm_ulog_lock);

काष्ठा receiving_pkg अणु
	काष्ठा list_head list;
	काष्ठा completion complete;

	uपूर्णांक32_t seq;

	पूर्णांक error;
	माप_प्रकार *data_size;
	अक्षर *data;
पूर्ण;

अटल DEFINE_SPINLOCK(receiving_list_lock);
अटल काष्ठा list_head receiving_list;

अटल पूर्णांक dm_ulog_sendto_server(काष्ठा dm_ulog_request *tfr)
अणु
	पूर्णांक r;
	काष्ठा cn_msg *msg = pपुनः_स्मृतिed_cn_msg;

	स_रखो(msg, 0, माप(काष्ठा cn_msg));

	msg->id.idx = ulog_cn_id.idx;
	msg->id.val = ulog_cn_id.val;
	msg->ack = 0;
	msg->seq = tfr->seq;
	msg->len = माप(काष्ठा dm_ulog_request) + tfr->data_size;

	r = cn_netlink_send(msg, 0, 0, gfp_any());

	वापस r;
पूर्ण

/*
 * Parameters क्रम this function can be either msg or tfr, but not
 * both.  This function fills in the reply क्रम a रुकोing request.
 * If just msg is given, then the reply is simply an ACK from userspace
 * that the request was received.
 *
 * Returns: 0 on success, -ENOENT on failure
 */
अटल पूर्णांक fill_pkg(काष्ठा cn_msg *msg, काष्ठा dm_ulog_request *tfr)
अणु
	uपूर्णांक32_t rtn_seq = (msg) ? msg->seq : (tfr) ? tfr->seq : 0;
	काष्ठा receiving_pkg *pkg;

	/*
	 * The 'receiving_pkg' entries in this list are अटलally
	 * allocated on the stack in 'dm_consult_userspace'.
	 * Each process that is रुकोing क्रम a reply from the user
	 * space server will have an entry in this list.
	 *
	 * We are safe to करो it this way because the stack space
	 * is unique to each process, but still addressable by
	 * other processes.
	 */
	list_क्रम_each_entry(pkg, &receiving_list, list) अणु
		अगर (rtn_seq != pkg->seq)
			जारी;

		अगर (msg) अणु
			pkg->error = -msg->ack;
			/*
			 * If we are trying again, we will need to know our
			 * storage capacity.  Otherwise, aदीर्घ with the
			 * error code, we make explicit that we have no data.
			 */
			अगर (pkg->error != -EAGAIN)
				*(pkg->data_size) = 0;
		पूर्ण अन्यथा अगर (tfr->data_size > *(pkg->data_size)) अणु
			DMERR("Insufficient space to receive package [%u] "
			      "(%u vs %zu)", tfr->request_type,
			      tfr->data_size, *(pkg->data_size));

			*(pkg->data_size) = 0;
			pkg->error = -ENOSPC;
		पूर्ण अन्यथा अणु
			pkg->error = tfr->error;
			स_नकल(pkg->data, tfr->data, tfr->data_size);
			*(pkg->data_size) = tfr->data_size;
		पूर्ण
		complete(&pkg->complete);
		वापस 0;
	पूर्ण

	वापस -ENOENT;
पूर्ण

/*
 * This is the connector callback that delivers data
 * that was sent from userspace.
 */
अटल व्योम cn_ulog_callback(काष्ठा cn_msg *msg, काष्ठा netlink_skb_parms *nsp)
अणु
	काष्ठा dm_ulog_request *tfr = (काष्ठा dm_ulog_request *)(msg + 1);

	अगर (!capable(CAP_SYS_ADMIN))
		वापस;

	spin_lock(&receiving_list_lock);
	अगर (msg->len == 0)
		fill_pkg(msg, शून्य);
	अन्यथा अगर (msg->len < माप(*tfr))
		DMERR("Incomplete message received (expected %u, got %u): [%u]",
		      (अचिन्हित)माप(*tfr), msg->len, msg->seq);
	अन्यथा
		fill_pkg(शून्य, tfr);
	spin_unlock(&receiving_list_lock);
पूर्ण

/**
 * dm_consult_userspace
 * @uuid: log's universal unique identअगरier (must be DM_UUID_LEN in size)
 * @luid: log's local unique identअगरier
 * @request_type:  found in include/linux/dm-log-userspace.h
 * @data: data to tx to the server
 * @data_size: size of data in bytes
 * @rdata: place to put वापस data from server
 * @rdata_size: value-result (amount of space given/amount of space used)
 *
 * rdata_size is undefined on failure.
 *
 * Memory used to communicate with userspace is zero'ed
 * beक्रमe populating to ensure that no unwanted bits leak
 * from kernel space to user-space.  All userspace log communications
 * between kernel and user space go through this function.
 *
 * Returns: 0 on success, -EXXX on failure
 **/
पूर्णांक dm_consult_userspace(स्थिर अक्षर *uuid, uपूर्णांक64_t luid, पूर्णांक request_type,
			 अक्षर *data, माप_प्रकार data_size,
			 अक्षर *rdata, माप_प्रकार *rdata_size)
अणु
	पूर्णांक r = 0;
	अचिन्हित दीर्घ पंचांगo;
	माप_प्रकार dummy = 0;
	पूर्णांक overhead_size = माप(काष्ठा dm_ulog_request) + माप(काष्ठा cn_msg);
	काष्ठा dm_ulog_request *tfr = pपुनः_स्मृतिed_ulog_tfr;
	काष्ठा receiving_pkg pkg;

	/*
	 * Given the space needed to hold the 'struct cn_msg' and
	 * 'struct dm_ulog_request' - करो we have enough payload
	 * space reमुख्यing?
	 */
	अगर (data_size > (DM_ULOG_PREALLOCED_SIZE - overhead_size)) अणु
		DMINFO("Size of tfr exceeds preallocated size");
		वापस -EINVAL;
	पूर्ण

	अगर (!rdata_size)
		rdata_size = &dummy;
resend:
	/*
	 * We serialize the sending of requests so we can
	 * use the pपुनः_स्मृतिated space.
	 */
	mutex_lock(&dm_ulog_lock);

	स_रखो(tfr, 0, DM_ULOG_PREALLOCED_SIZE - माप(काष्ठा cn_msg));
	स_नकल(tfr->uuid, uuid, DM_UUID_LEN);
	tfr->version = DM_ULOG_REQUEST_VERSION;
	tfr->luid = luid;
	tfr->seq = dm_ulog_seq++;

	/*
	 * Must be valid request type (all other bits set to
	 * zero).  This reserves other bits क्रम possible future
	 * use.
	 */
	tfr->request_type = request_type & DM_ULOG_REQUEST_MASK;

	tfr->data_size = data_size;
	अगर (data && data_size)
		स_नकल(tfr->data, data, data_size);

	स_रखो(&pkg, 0, माप(pkg));
	init_completion(&pkg.complete);
	pkg.seq = tfr->seq;
	pkg.data_size = rdata_size;
	pkg.data = rdata;
	spin_lock(&receiving_list_lock);
	list_add(&(pkg.list), &receiving_list);
	spin_unlock(&receiving_list_lock);

	r = dm_ulog_sendto_server(tfr);

	mutex_unlock(&dm_ulog_lock);

	अगर (r) अणु
		DMERR("Unable to send log request [%u] to userspace: %d",
		      request_type, r);
		spin_lock(&receiving_list_lock);
		list_del_init(&(pkg.list));
		spin_unlock(&receiving_list_lock);

		जाओ out;
	पूर्ण

	पंचांगo = रुको_क्रम_completion_समयout(&(pkg.complete), DM_ULOG_RETRY_TIMEOUT);
	spin_lock(&receiving_list_lock);
	list_del_init(&(pkg.list));
	spin_unlock(&receiving_list_lock);
	अगर (!पंचांगo) अणु
		DMWARN("[%s] Request timed out: [%u/%u] - retrying",
		       (म_माप(uuid) > 8) ?
		       (uuid + (म_माप(uuid) - 8)) : (uuid),
		       request_type, pkg.seq);
		जाओ resend;
	पूर्ण

	r = pkg.error;
	अगर (r == -EAGAIN)
		जाओ resend;

out:
	वापस r;
पूर्ण

पूर्णांक dm_ulog_tfr_init(व्योम)
अणु
	पूर्णांक r;
	व्योम *pपुनः_स्मृतिed;

	INIT_LIST_HEAD(&receiving_list);

	pपुनः_स्मृतिed = kदो_स्मृति(DM_ULOG_PREALLOCED_SIZE, GFP_KERNEL);
	अगर (!pपुनः_स्मृतिed)
		वापस -ENOMEM;

	pपुनः_स्मृतिed_cn_msg = pपुनः_स्मृतिed;
	pपुनः_स्मृतिed_ulog_tfr = pपुनः_स्मृतिed + माप(काष्ठा cn_msg);

	r = cn_add_callback(&ulog_cn_id, "dmlogusr", cn_ulog_callback);
	अगर (r) अणु
		kमुक्त(pपुनः_स्मृतिed_cn_msg);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

व्योम dm_ulog_tfr_निकास(व्योम)
अणु
	cn_del_callback(&ulog_cn_id);
	kमुक्त(pपुनः_स्मृतिed_cn_msg);
पूर्ण
