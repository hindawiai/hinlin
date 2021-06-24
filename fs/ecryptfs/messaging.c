<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * eCryptfs: Linux fileप्रणाली encryption layer
 *
 * Copyright (C) 2004-2008 International Business Machines Corp.
 *   Author(s): Michael A. Halcrow <mhalcrow@us.ibm.com>
 *		Tyler Hicks <code@tyhicks.com>
 */
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/nsproxy.h>
#समावेश "ecryptfs_kernel.h"

अटल LIST_HEAD(ecryptfs_msg_ctx_मुक्त_list);
अटल LIST_HEAD(ecryptfs_msg_ctx_alloc_list);
अटल DEFINE_MUTEX(ecryptfs_msg_ctx_lists_mux);

अटल काष्ठा hlist_head *ecryptfs_daemon_hash;
DEFINE_MUTEX(ecryptfs_daemon_hash_mux);
अटल पूर्णांक ecryptfs_hash_bits;
#घोषणा ecryptfs_current_euid_hash(uid) \
	hash_दीर्घ((अचिन्हित दीर्घ)from_kuid(&init_user_ns, current_euid()), ecryptfs_hash_bits)

अटल u32 ecryptfs_msg_counter;
अटल काष्ठा ecryptfs_msg_ctx *ecryptfs_msg_ctx_arr;

/**
 * ecryptfs_acquire_मुक्त_msg_ctx
 * @msg_ctx: The context that was acquired from the मुक्त list
 *
 * Acquires a context element from the मुक्त list and locks the mutex
 * on the context.  Sets the msg_ctx task to current.  Returns zero on
 * success; non-zero on error or upon failure to acquire a मुक्त
 * context element.  Must be called with ecryptfs_msg_ctx_lists_mux
 * held.
 */
अटल पूर्णांक ecryptfs_acquire_मुक्त_msg_ctx(काष्ठा ecryptfs_msg_ctx **msg_ctx)
अणु
	काष्ठा list_head *p;
	पूर्णांक rc;

	अगर (list_empty(&ecryptfs_msg_ctx_मुक्त_list)) अणु
		prपूर्णांकk(KERN_WARNING "%s: The eCryptfs free "
		       "context list is empty.  It may be helpful to "
		       "specify the ecryptfs_message_buf_len "
		       "parameter to be greater than the current "
		       "value of [%d]\n", __func__, ecryptfs_message_buf_len);
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	list_क्रम_each(p, &ecryptfs_msg_ctx_मुक्त_list) अणु
		*msg_ctx = list_entry(p, काष्ठा ecryptfs_msg_ctx, node);
		अगर (mutex_trylock(&(*msg_ctx)->mux)) अणु
			(*msg_ctx)->task = current;
			rc = 0;
			जाओ out;
		पूर्ण
	पूर्ण
	rc = -ENOMEM;
out:
	वापस rc;
पूर्ण

/**
 * ecryptfs_msg_ctx_मुक्त_to_alloc
 * @msg_ctx: The context to move from the मुक्त list to the alloc list
 *
 * Must be called with ecryptfs_msg_ctx_lists_mux held.
 */
अटल व्योम ecryptfs_msg_ctx_मुक्त_to_alloc(काष्ठा ecryptfs_msg_ctx *msg_ctx)
अणु
	list_move(&msg_ctx->node, &ecryptfs_msg_ctx_alloc_list);
	msg_ctx->state = ECRYPTFS_MSG_CTX_STATE_PENDING;
	msg_ctx->counter = ++ecryptfs_msg_counter;
पूर्ण

/**
 * ecryptfs_msg_ctx_alloc_to_मुक्त
 * @msg_ctx: The context to move from the alloc list to the मुक्त list
 *
 * Must be called with ecryptfs_msg_ctx_lists_mux held.
 */
व्योम ecryptfs_msg_ctx_alloc_to_मुक्त(काष्ठा ecryptfs_msg_ctx *msg_ctx)
अणु
	list_move(&(msg_ctx->node), &ecryptfs_msg_ctx_मुक्त_list);
	kमुक्त(msg_ctx->msg);
	msg_ctx->msg = शून्य;
	msg_ctx->state = ECRYPTFS_MSG_CTX_STATE_FREE;
पूर्ण

/**
 * ecryptfs_find_daemon_by_euid
 * @daemon: If वापस value is zero, poपूर्णांकs to the desired daemon poपूर्णांकer
 *
 * Must be called with ecryptfs_daemon_hash_mux held.
 *
 * Search the hash list क्रम the current effective user id.
 *
 * Returns zero अगर the user id exists in the list; non-zero otherwise.
 */
पूर्णांक ecryptfs_find_daemon_by_euid(काष्ठा ecryptfs_daemon **daemon)
अणु
	पूर्णांक rc;

	hlist_क्रम_each_entry(*daemon,
			    &ecryptfs_daemon_hash[ecryptfs_current_euid_hash()],
			    euid_chain) अणु
		अगर (uid_eq((*daemon)->file->f_cred->euid, current_euid())) अणु
			rc = 0;
			जाओ out;
		पूर्ण
	पूर्ण
	rc = -EINVAL;
out:
	वापस rc;
पूर्ण

/**
 * ecryptfs_spawn_daemon - Create and initialize a new daemon काष्ठा
 * @daemon: Poपूर्णांकer to set to newly allocated daemon काष्ठा
 * @file: File used when खोलोing /dev/ecryptfs
 *
 * Must be called ceremoniously जबतक in possession of
 * ecryptfs_sacred_daemon_hash_mux
 *
 * Returns zero on success; non-zero otherwise
 */
पूर्णांक
ecryptfs_spawn_daemon(काष्ठा ecryptfs_daemon **daemon, काष्ठा file *file)
अणु
	पूर्णांक rc = 0;

	(*daemon) = kzalloc(माप(**daemon), GFP_KERNEL);
	अगर (!(*daemon)) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	(*daemon)->file = file;
	mutex_init(&(*daemon)->mux);
	INIT_LIST_HEAD(&(*daemon)->msg_ctx_out_queue);
	init_रुकोqueue_head(&(*daemon)->रुको);
	(*daemon)->num_queued_msg_ctx = 0;
	hlist_add_head(&(*daemon)->euid_chain,
		       &ecryptfs_daemon_hash[ecryptfs_current_euid_hash()]);
out:
	वापस rc;
पूर्ण

/*
 * ecryptfs_exorcise_daemon - Destroy the daemon काष्ठा
 *
 * Must be called ceremoniously जबतक in possession of
 * ecryptfs_daemon_hash_mux and the daemon's own mux.
 */
पूर्णांक ecryptfs_exorcise_daemon(काष्ठा ecryptfs_daemon *daemon)
अणु
	काष्ठा ecryptfs_msg_ctx *msg_ctx, *msg_ctx_पंचांगp;
	पूर्णांक rc = 0;

	mutex_lock(&daemon->mux);
	अगर ((daemon->flags & ECRYPTFS_DAEMON_IN_READ)
	    || (daemon->flags & ECRYPTFS_DAEMON_IN_POLL)) अणु
		rc = -EBUSY;
		mutex_unlock(&daemon->mux);
		जाओ out;
	पूर्ण
	list_क्रम_each_entry_safe(msg_ctx, msg_ctx_पंचांगp,
				 &daemon->msg_ctx_out_queue, daemon_out_list) अणु
		list_del(&msg_ctx->daemon_out_list);
		daemon->num_queued_msg_ctx--;
		prपूर्णांकk(KERN_WARNING "%s: Warning: dropping message that is in "
		       "the out queue of a dying daemon\n", __func__);
		ecryptfs_msg_ctx_alloc_to_मुक्त(msg_ctx);
	पूर्ण
	hlist_del(&daemon->euid_chain);
	mutex_unlock(&daemon->mux);
	kमुक्त_sensitive(daemon);
out:
	वापस rc;
पूर्ण

/**
 * ecryptfs_process_response
 * @daemon: eCryptfs daemon object
 * @msg: The ecryptfs message received; the caller should sanity check
 *       msg->data_len and मुक्त the memory
 * @seq: The sequence number of the message; must match the sequence
 *       number क्रम the existing message context रुकोing क्रम this
 *       response
 *
 * Processes a response message after sending an operation request to
 * userspace. Some other process is aरुकोing this response. Beक्रमe
 * sending out its first communications, the other process allocated a
 * msg_ctx from the ecryptfs_msg_ctx_arr at a particular index. The
 * response message contains this index so that we can copy over the
 * response message पूर्णांकo the msg_ctx that the process holds a
 * reference to. The other process is going to wake up, check to see
 * that msg_ctx->state == ECRYPTFS_MSG_CTX_STATE_DONE, and then
 * proceed to पढ़ो off and process the response message. Returns zero
 * upon delivery to desired context element; non-zero upon delivery
 * failure or error.
 *
 * Returns zero on success; non-zero otherwise
 */
पूर्णांक ecryptfs_process_response(काष्ठा ecryptfs_daemon *daemon,
			      काष्ठा ecryptfs_message *msg, u32 seq)
अणु
	काष्ठा ecryptfs_msg_ctx *msg_ctx;
	माप_प्रकार msg_size;
	पूर्णांक rc;

	अगर (msg->index >= ecryptfs_message_buf_len) अणु
		rc = -EINVAL;
		prपूर्णांकk(KERN_ERR "%s: Attempt to reference "
		       "context buffer at index [%d]; maximum "
		       "allowable is [%d]\n", __func__, msg->index,
		       (ecryptfs_message_buf_len - 1));
		जाओ out;
	पूर्ण
	msg_ctx = &ecryptfs_msg_ctx_arr[msg->index];
	mutex_lock(&msg_ctx->mux);
	अगर (msg_ctx->state != ECRYPTFS_MSG_CTX_STATE_PENDING) अणु
		rc = -EINVAL;
		prपूर्णांकk(KERN_WARNING "%s: Desired context element is not "
		       "pending a response\n", __func__);
		जाओ unlock;
	पूर्ण अन्यथा अगर (msg_ctx->counter != seq) अणु
		rc = -EINVAL;
		prपूर्णांकk(KERN_WARNING "%s: Invalid message sequence; "
		       "expected [%d]; received [%d]\n", __func__,
		       msg_ctx->counter, seq);
		जाओ unlock;
	पूर्ण
	msg_size = (माप(*msg) + msg->data_len);
	msg_ctx->msg = kmemdup(msg, msg_size, GFP_KERNEL);
	अगर (!msg_ctx->msg) अणु
		rc = -ENOMEM;
		जाओ unlock;
	पूर्ण
	msg_ctx->state = ECRYPTFS_MSG_CTX_STATE_DONE;
	wake_up_process(msg_ctx->task);
	rc = 0;
unlock:
	mutex_unlock(&msg_ctx->mux);
out:
	वापस rc;
पूर्ण

/**
 * ecryptfs_send_message_locked
 * @data: The data to send
 * @data_len: The length of data
 * @msg_type: Type of message
 * @msg_ctx: The message context allocated क्रम the send
 *
 * Must be called with ecryptfs_daemon_hash_mux held.
 *
 * Returns zero on success; non-zero otherwise
 */
अटल पूर्णांक
ecryptfs_send_message_locked(अक्षर *data, पूर्णांक data_len, u8 msg_type,
			     काष्ठा ecryptfs_msg_ctx **msg_ctx)
अणु
	काष्ठा ecryptfs_daemon *daemon;
	पूर्णांक rc;

	rc = ecryptfs_find_daemon_by_euid(&daemon);
	अगर (rc) अणु
		rc = -ENOTCONN;
		जाओ out;
	पूर्ण
	mutex_lock(&ecryptfs_msg_ctx_lists_mux);
	rc = ecryptfs_acquire_मुक्त_msg_ctx(msg_ctx);
	अगर (rc) अणु
		mutex_unlock(&ecryptfs_msg_ctx_lists_mux);
		prपूर्णांकk(KERN_WARNING "%s: Could not claim a free "
		       "context element\n", __func__);
		जाओ out;
	पूर्ण
	ecryptfs_msg_ctx_मुक्त_to_alloc(*msg_ctx);
	mutex_unlock(&(*msg_ctx)->mux);
	mutex_unlock(&ecryptfs_msg_ctx_lists_mux);
	rc = ecryptfs_send_miscdev(data, data_len, *msg_ctx, msg_type, 0,
				   daemon);
	अगर (rc)
		prपूर्णांकk(KERN_ERR "%s: Error attempting to send message to "
		       "userspace daemon; rc = [%d]\n", __func__, rc);
out:
	वापस rc;
पूर्ण

/**
 * ecryptfs_send_message
 * @data: The data to send
 * @data_len: The length of data
 * @msg_ctx: The message context allocated क्रम the send
 *
 * Grअसल ecryptfs_daemon_hash_mux.
 *
 * Returns zero on success; non-zero otherwise
 */
पूर्णांक ecryptfs_send_message(अक्षर *data, पूर्णांक data_len,
			  काष्ठा ecryptfs_msg_ctx **msg_ctx)
अणु
	पूर्णांक rc;

	mutex_lock(&ecryptfs_daemon_hash_mux);
	rc = ecryptfs_send_message_locked(data, data_len, ECRYPTFS_MSG_REQUEST,
					  msg_ctx);
	mutex_unlock(&ecryptfs_daemon_hash_mux);
	वापस rc;
पूर्ण

/**
 * ecryptfs_रुको_क्रम_response
 * @msg_ctx: The context that was asचिन्हित when sending a message
 * @msg: The incoming message from userspace; not set अगर rc != 0
 *
 * Sleeps until awaken by ecryptfs_receive_message or until the amount
 * of समय exceeds ecryptfs_message_रुको_समयout.  If zero is
 * वापसed, msg will poपूर्णांक to a valid message from userspace; a
 * non-zero value is वापसed upon failure to receive a message or an
 * error occurs. Callee must मुक्त @msg on success.
 */
पूर्णांक ecryptfs_रुको_क्रम_response(काष्ठा ecryptfs_msg_ctx *msg_ctx,
			       काष्ठा ecryptfs_message **msg)
अणु
	चिन्हित दीर्घ समयout = ecryptfs_message_रुको_समयout * HZ;
	पूर्णांक rc = 0;

sleep:
	समयout = schedule_समयout_पूर्णांकerruptible(समयout);
	mutex_lock(&ecryptfs_msg_ctx_lists_mux);
	mutex_lock(&msg_ctx->mux);
	अगर (msg_ctx->state != ECRYPTFS_MSG_CTX_STATE_DONE) अणु
		अगर (समयout) अणु
			mutex_unlock(&msg_ctx->mux);
			mutex_unlock(&ecryptfs_msg_ctx_lists_mux);
			जाओ sleep;
		पूर्ण
		rc = -ENOMSG;
	पूर्ण अन्यथा अणु
		*msg = msg_ctx->msg;
		msg_ctx->msg = शून्य;
	पूर्ण
	ecryptfs_msg_ctx_alloc_to_मुक्त(msg_ctx);
	mutex_unlock(&msg_ctx->mux);
	mutex_unlock(&ecryptfs_msg_ctx_lists_mux);
	वापस rc;
पूर्ण

पूर्णांक __init ecryptfs_init_messaging(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक rc = 0;

	अगर (ecryptfs_number_of_users > ECRYPTFS_MAX_NUM_USERS) अणु
		ecryptfs_number_of_users = ECRYPTFS_MAX_NUM_USERS;
		prपूर्णांकk(KERN_WARNING "%s: Specified number of users is "
		       "too large, defaulting to [%d] users\n", __func__,
		       ecryptfs_number_of_users);
	पूर्ण
	mutex_lock(&ecryptfs_daemon_hash_mux);
	ecryptfs_hash_bits = 1;
	जबतक (ecryptfs_number_of_users >> ecryptfs_hash_bits)
		ecryptfs_hash_bits++;
	ecryptfs_daemon_hash = kदो_स्मृति((माप(काष्ठा hlist_head)
					* (1 << ecryptfs_hash_bits)),
				       GFP_KERNEL);
	अगर (!ecryptfs_daemon_hash) अणु
		rc = -ENOMEM;
		mutex_unlock(&ecryptfs_daemon_hash_mux);
		जाओ out;
	पूर्ण
	क्रम (i = 0; i < (1 << ecryptfs_hash_bits); i++)
		INIT_HLIST_HEAD(&ecryptfs_daemon_hash[i]);
	mutex_unlock(&ecryptfs_daemon_hash_mux);
	ecryptfs_msg_ctx_arr = kदो_स्मृति((माप(काष्ठा ecryptfs_msg_ctx)
					* ecryptfs_message_buf_len),
				       GFP_KERNEL);
	अगर (!ecryptfs_msg_ctx_arr) अणु
		kमुक्त(ecryptfs_daemon_hash);
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	mutex_lock(&ecryptfs_msg_ctx_lists_mux);
	ecryptfs_msg_counter = 0;
	क्रम (i = 0; i < ecryptfs_message_buf_len; i++) अणु
		INIT_LIST_HEAD(&ecryptfs_msg_ctx_arr[i].node);
		INIT_LIST_HEAD(&ecryptfs_msg_ctx_arr[i].daemon_out_list);
		mutex_init(&ecryptfs_msg_ctx_arr[i].mux);
		mutex_lock(&ecryptfs_msg_ctx_arr[i].mux);
		ecryptfs_msg_ctx_arr[i].index = i;
		ecryptfs_msg_ctx_arr[i].state = ECRYPTFS_MSG_CTX_STATE_FREE;
		ecryptfs_msg_ctx_arr[i].counter = 0;
		ecryptfs_msg_ctx_arr[i].task = शून्य;
		ecryptfs_msg_ctx_arr[i].msg = शून्य;
		list_add_tail(&ecryptfs_msg_ctx_arr[i].node,
			      &ecryptfs_msg_ctx_मुक्त_list);
		mutex_unlock(&ecryptfs_msg_ctx_arr[i].mux);
	पूर्ण
	mutex_unlock(&ecryptfs_msg_ctx_lists_mux);
	rc = ecryptfs_init_ecryptfs_miscdev();
	अगर (rc)
		ecryptfs_release_messaging();
out:
	वापस rc;
पूर्ण

व्योम ecryptfs_release_messaging(व्योम)
अणु
	अगर (ecryptfs_msg_ctx_arr) अणु
		पूर्णांक i;

		mutex_lock(&ecryptfs_msg_ctx_lists_mux);
		क्रम (i = 0; i < ecryptfs_message_buf_len; i++) अणु
			mutex_lock(&ecryptfs_msg_ctx_arr[i].mux);
			kमुक्त(ecryptfs_msg_ctx_arr[i].msg);
			mutex_unlock(&ecryptfs_msg_ctx_arr[i].mux);
		पूर्ण
		kमुक्त(ecryptfs_msg_ctx_arr);
		mutex_unlock(&ecryptfs_msg_ctx_lists_mux);
	पूर्ण
	अगर (ecryptfs_daemon_hash) अणु
		काष्ठा ecryptfs_daemon *daemon;
		काष्ठा hlist_node *n;
		पूर्णांक i;

		mutex_lock(&ecryptfs_daemon_hash_mux);
		क्रम (i = 0; i < (1 << ecryptfs_hash_bits); i++) अणु
			पूर्णांक rc;

			hlist_क्रम_each_entry_safe(daemon, n,
						  &ecryptfs_daemon_hash[i],
						  euid_chain) अणु
				rc = ecryptfs_exorcise_daemon(daemon);
				अगर (rc)
					prपूर्णांकk(KERN_ERR "%s: Error whilst "
					       "attempting to destroy daemon; "
					       "rc = [%d]. Dazed and confused, "
					       "but trying to continue.\n",
					       __func__, rc);
			पूर्ण
		पूर्ण
		kमुक्त(ecryptfs_daemon_hash);
		mutex_unlock(&ecryptfs_daemon_hash_mux);
	पूर्ण
	ecryptfs_destroy_ecryptfs_miscdev();
	वापस;
पूर्ण
