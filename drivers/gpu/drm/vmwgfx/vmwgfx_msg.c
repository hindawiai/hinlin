<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/*
 * Copyright 2016 VMware, Inc., Palo Alto, CA., USA
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#समावेश <linux/objtool.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/mem_encrypt.h>

#समावेश <यंत्र/hypervisor.h>

#समावेश "vmwgfx_drv.h"
#समावेश "vmwgfx_msg.h"

#घोषणा MESSAGE_STATUS_SUCCESS  0x0001
#घोषणा MESSAGE_STATUS_DORECV   0x0002
#घोषणा MESSAGE_STATUS_CPT      0x0010
#घोषणा MESSAGE_STATUS_HB       0x0080

#घोषणा RPCI_PROTOCOL_NUM       0x49435052
#घोषणा GUESTMSG_FLAG_COOKIE    0x80000000

#घोषणा RETRIES                 3

#घोषणा VMW_HYPERVISOR_MAGIC    0x564D5868

#घोषणा VMW_PORT_CMD_MSG        30
#घोषणा VMW_PORT_CMD_HB_MSG     0
#घोषणा VMW_PORT_CMD_OPEN_CHANNEL  (MSG_TYPE_OPEN << 16 | VMW_PORT_CMD_MSG)
#घोषणा VMW_PORT_CMD_CLOSE_CHANNEL (MSG_TYPE_CLOSE << 16 | VMW_PORT_CMD_MSG)
#घोषणा VMW_PORT_CMD_SENDSIZE   (MSG_TYPE_SENDSIZE << 16 | VMW_PORT_CMD_MSG)
#घोषणा VMW_PORT_CMD_RECVSIZE   (MSG_TYPE_RECVSIZE << 16 | VMW_PORT_CMD_MSG)
#घोषणा VMW_PORT_CMD_RECVSTATUS (MSG_TYPE_RECVSTATUS << 16 | VMW_PORT_CMD_MSG)

#घोषणा HIGH_WORD(X) ((X & 0xFFFF0000) >> 16)

#घोषणा MAX_USER_MSG_LENGTH	PAGE_SIZE

अटल u32 vmw_msg_enabled = 1;

क्रमागत rpc_msg_type अणु
	MSG_TYPE_OPEN,
	MSG_TYPE_SENDSIZE,
	MSG_TYPE_SENDPAYLOAD,
	MSG_TYPE_RECVSIZE,
	MSG_TYPE_RECVPAYLOAD,
	MSG_TYPE_RECVSTATUS,
	MSG_TYPE_CLOSE,
पूर्ण;

काष्ठा rpc_channel अणु
	u16 channel_id;
	u32 cookie_high;
	u32 cookie_low;
पूर्ण;



/**
 * vmw_खोलो_channel
 *
 * @channel: RPC channel
 * @protocol:
 *
 * Returns: 0 on success
 */
अटल पूर्णांक vmw_खोलो_channel(काष्ठा rpc_channel *channel, अचिन्हित पूर्णांक protocol)
अणु
	अचिन्हित दीर्घ eax, ebx, ecx, edx, si = 0, di = 0;

	VMW_PORT(VMW_PORT_CMD_OPEN_CHANNEL,
		(protocol | GUESTMSG_FLAG_COOKIE), si, di,
		0,
		VMW_HYPERVISOR_MAGIC,
		eax, ebx, ecx, edx, si, di);

	अगर ((HIGH_WORD(ecx) & MESSAGE_STATUS_SUCCESS) == 0)
		वापस -EINVAL;

	channel->channel_id  = HIGH_WORD(edx);
	channel->cookie_high = si;
	channel->cookie_low  = di;

	वापस 0;
पूर्ण



/**
 * vmw_बंद_channel
 *
 * @channel: RPC channel
 *
 * Returns: 0 on success
 */
अटल पूर्णांक vmw_बंद_channel(काष्ठा rpc_channel *channel)
अणु
	अचिन्हित दीर्घ eax, ebx, ecx, edx, si, di;

	/* Set up additional parameters */
	si  = channel->cookie_high;
	di  = channel->cookie_low;

	VMW_PORT(VMW_PORT_CMD_CLOSE_CHANNEL,
		0, si, di,
		channel->channel_id << 16,
		VMW_HYPERVISOR_MAGIC,
		eax, ebx, ecx, edx, si, di);

	अगर ((HIGH_WORD(ecx) & MESSAGE_STATUS_SUCCESS) == 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * vmw_port_hb_out - Send the message payload either through the
 * high-bandwidth port अगर available, or through the backकरोor otherwise.
 * @channel: The rpc channel.
 * @msg: शून्य-terminated message.
 * @hb: Whether the high-bandwidth port is available.
 *
 * Return: The port status.
 */
अटल अचिन्हित दीर्घ vmw_port_hb_out(काष्ठा rpc_channel *channel,
				     स्थिर अक्षर *msg, bool hb)
अणु
	अचिन्हित दीर्घ si, di, eax, ebx, ecx, edx;
	अचिन्हित दीर्घ msg_len = म_माप(msg);

	/* HB port can't access encrypted memory. */
	अगर (hb && !mem_encrypt_active()) अणु
		अचिन्हित दीर्घ bp = channel->cookie_high;

		si = (uपूर्णांकptr_t) msg;
		di = channel->cookie_low;

		VMW_PORT_HB_OUT(
			(MESSAGE_STATUS_SUCCESS << 16) | VMW_PORT_CMD_HB_MSG,
			msg_len, si, di,
			VMWARE_HYPERVISOR_HB | (channel->channel_id << 16) |
			VMWARE_HYPERVISOR_OUT,
			VMW_HYPERVISOR_MAGIC, bp,
			eax, ebx, ecx, edx, si, di);

		वापस ebx;
	पूर्ण

	/* HB port not available. Send the message 4 bytes at a समय. */
	ecx = MESSAGE_STATUS_SUCCESS << 16;
	जबतक (msg_len && (HIGH_WORD(ecx) & MESSAGE_STATUS_SUCCESS)) अणु
		अचिन्हित पूर्णांक bytes = min_t(माप_प्रकार, msg_len, 4);
		अचिन्हित दीर्घ word = 0;

		स_नकल(&word, msg, bytes);
		msg_len -= bytes;
		msg += bytes;
		si = channel->cookie_high;
		di = channel->cookie_low;

		VMW_PORT(VMW_PORT_CMD_MSG | (MSG_TYPE_SENDPAYLOAD << 16),
			 word, si, di,
			 channel->channel_id << 16,
			 VMW_HYPERVISOR_MAGIC,
			 eax, ebx, ecx, edx, si, di);
	पूर्ण

	वापस ecx;
पूर्ण

/**
 * vmw_port_hb_in - Receive the message payload either through the
 * high-bandwidth port अगर available, or through the backकरोor otherwise.
 * @channel: The rpc channel.
 * @reply: Poपूर्णांकer to buffer holding reply.
 * @reply_len: Length of the reply.
 * @hb: Whether the high-bandwidth port is available.
 *
 * Return: The port status.
 */
अटल अचिन्हित दीर्घ vmw_port_hb_in(काष्ठा rpc_channel *channel, अक्षर *reply,
				    अचिन्हित दीर्घ reply_len, bool hb)
अणु
	अचिन्हित दीर्घ si, di, eax, ebx, ecx, edx;

	/* HB port can't access encrypted memory */
	अगर (hb && !mem_encrypt_active()) अणु
		अचिन्हित दीर्घ bp = channel->cookie_low;

		si = channel->cookie_high;
		di = (uपूर्णांकptr_t) reply;

		VMW_PORT_HB_IN(
			(MESSAGE_STATUS_SUCCESS << 16) | VMW_PORT_CMD_HB_MSG,
			reply_len, si, di,
			VMWARE_HYPERVISOR_HB | (channel->channel_id << 16),
			VMW_HYPERVISOR_MAGIC, bp,
			eax, ebx, ecx, edx, si, di);

		वापस ebx;
	पूर्ण

	/* HB port not available. Retrieve the message 4 bytes at a समय. */
	ecx = MESSAGE_STATUS_SUCCESS << 16;
	जबतक (reply_len) अणु
		अचिन्हित पूर्णांक bytes = min_t(अचिन्हित दीर्घ, reply_len, 4);

		si = channel->cookie_high;
		di = channel->cookie_low;

		VMW_PORT(VMW_PORT_CMD_MSG | (MSG_TYPE_RECVPAYLOAD << 16),
			 MESSAGE_STATUS_SUCCESS, si, di,
			 channel->channel_id << 16,
			 VMW_HYPERVISOR_MAGIC,
			 eax, ebx, ecx, edx, si, di);

		अगर ((HIGH_WORD(ecx) & MESSAGE_STATUS_SUCCESS) == 0)
			अवरोध;

		स_नकल(reply, &ebx, bytes);
		reply_len -= bytes;
		reply += bytes;
	पूर्ण

	वापस ecx;
पूर्ण


/**
 * vmw_send_msg: Sends a message to the host
 *
 * @channel: RPC channel
 * @msg: शून्य terminated string
 *
 * Returns: 0 on success
 */
अटल पूर्णांक vmw_send_msg(काष्ठा rpc_channel *channel, स्थिर अक्षर *msg)
अणु
	अचिन्हित दीर्घ eax, ebx, ecx, edx, si, di;
	माप_प्रकार msg_len = म_माप(msg);
	पूर्णांक retries = 0;

	जबतक (retries < RETRIES) अणु
		retries++;

		/* Set up additional parameters */
		si  = channel->cookie_high;
		di  = channel->cookie_low;

		VMW_PORT(VMW_PORT_CMD_SENDSIZE,
			msg_len, si, di,
			channel->channel_id << 16,
			VMW_HYPERVISOR_MAGIC,
			eax, ebx, ecx, edx, si, di);

		अगर ((HIGH_WORD(ecx) & MESSAGE_STATUS_SUCCESS) == 0) अणु
			/* Expected success. Give up. */
			वापस -EINVAL;
		पूर्ण

		/* Send msg */
		ebx = vmw_port_hb_out(channel, msg,
				      !!(HIGH_WORD(ecx) & MESSAGE_STATUS_HB));

		अगर ((HIGH_WORD(ebx) & MESSAGE_STATUS_SUCCESS) != 0) अणु
			वापस 0;
		पूर्ण अन्यथा अगर ((HIGH_WORD(ebx) & MESSAGE_STATUS_CPT) != 0) अणु
			/* A checkpoपूर्णांक occurred. Retry. */
			जारी;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण
STACK_FRAME_NON_STANDARD(vmw_send_msg);


/**
 * vmw_recv_msg: Receives a message from the host
 *
 * Note:  It is the caller's responsibility to call kमुक्त() on msg.
 *
 * @channel:  channel खोलोed by vmw_खोलो_channel
 * @msg:  [OUT] message received from the host
 * @msg_len: message length
 */
अटल पूर्णांक vmw_recv_msg(काष्ठा rpc_channel *channel, व्योम **msg,
			माप_प्रकार *msg_len)
अणु
	अचिन्हित दीर्घ eax, ebx, ecx, edx, si, di;
	अक्षर *reply;
	माप_प्रकार reply_len;
	पूर्णांक retries = 0;


	*msg_len = 0;
	*msg = शून्य;

	जबतक (retries < RETRIES) अणु
		retries++;

		/* Set up additional parameters */
		si  = channel->cookie_high;
		di  = channel->cookie_low;

		VMW_PORT(VMW_PORT_CMD_RECVSIZE,
			0, si, di,
			channel->channel_id << 16,
			VMW_HYPERVISOR_MAGIC,
			eax, ebx, ecx, edx, si, di);

		अगर ((HIGH_WORD(ecx) & MESSAGE_STATUS_SUCCESS) == 0) अणु
			DRM_ERROR("Failed to get reply size for host message.\n");
			वापस -EINVAL;
		पूर्ण

		/* No reply available.  This is okay. */
		अगर ((HIGH_WORD(ecx) & MESSAGE_STATUS_DORECV) == 0)
			वापस 0;

		reply_len = ebx;
		reply     = kzalloc(reply_len + 1, GFP_KERNEL);
		अगर (!reply) अणु
			DRM_ERROR("Cannot allocate memory for host message reply.\n");
			वापस -ENOMEM;
		पूर्ण


		/* Receive buffer */
		ebx = vmw_port_hb_in(channel, reply, reply_len,
				     !!(HIGH_WORD(ecx) & MESSAGE_STATUS_HB));
		अगर ((HIGH_WORD(ebx) & MESSAGE_STATUS_SUCCESS) == 0) अणु
			kमुक्त(reply);
			reply = शून्य;
			अगर ((HIGH_WORD(ebx) & MESSAGE_STATUS_CPT) != 0) अणु
				/* A checkpoपूर्णांक occurred. Retry. */
				जारी;
			पूर्ण

			वापस -EINVAL;
		पूर्ण

		reply[reply_len] = '\0';


		/* Ack buffer */
		si  = channel->cookie_high;
		di  = channel->cookie_low;

		VMW_PORT(VMW_PORT_CMD_RECVSTATUS,
			MESSAGE_STATUS_SUCCESS, si, di,
			channel->channel_id << 16,
			VMW_HYPERVISOR_MAGIC,
			eax, ebx, ecx, edx, si, di);

		अगर ((HIGH_WORD(ecx) & MESSAGE_STATUS_SUCCESS) == 0) अणु
			kमुक्त(reply);
			reply = शून्य;
			अगर ((HIGH_WORD(ecx) & MESSAGE_STATUS_CPT) != 0) अणु
				/* A checkpoपूर्णांक occurred. Retry. */
				जारी;
			पूर्ण

			वापस -EINVAL;
		पूर्ण

		अवरोध;
	पूर्ण

	अगर (!reply)
		वापस -EINVAL;

	*msg_len = reply_len;
	*msg     = reply;

	वापस 0;
पूर्ण
STACK_FRAME_NON_STANDARD(vmw_recv_msg);


/**
 * vmw_host_get_guestinfo: Gets a GuestInfo parameter
 *
 * Gets the value of a  GuestInfo.* parameter.  The value वापसed will be in
 * a string, and it is up to the caller to post-process.
 *
 * @guest_info_param:  Parameter to get, e.g. GuestInfo.svga.gl3
 * @buffer: अगर शून्य, *reply_len will contain reply size.
 * @length: size of the reply_buf.  Set to size of reply upon वापस
 *
 * Returns: 0 on success
 */
पूर्णांक vmw_host_get_guestinfo(स्थिर अक्षर *guest_info_param,
			   अक्षर *buffer, माप_प्रकार *length)
अणु
	काष्ठा rpc_channel channel;
	अक्षर *msg, *reply = शून्य;
	माप_प्रकार reply_len = 0;

	अगर (!vmw_msg_enabled)
		वापस -ENODEV;

	अगर (!guest_info_param || !length)
		वापस -EINVAL;

	msg = kaप्र_लिखो(GFP_KERNEL, "info-get %s", guest_info_param);
	अगर (!msg) अणु
		DRM_ERROR("Cannot allocate memory to get guest info \"%s\".",
			  guest_info_param);
		वापस -ENOMEM;
	पूर्ण

	अगर (vmw_खोलो_channel(&channel, RPCI_PROTOCOL_NUM))
		जाओ out_खोलो;

	अगर (vmw_send_msg(&channel, msg) ||
	    vmw_recv_msg(&channel, (व्योम *) &reply, &reply_len))
		जाओ out_msg;

	vmw_बंद_channel(&channel);
	अगर (buffer && reply && reply_len > 0) अणु
		/* Remove reply code, which are the first 2 अक्षरacters of
		 * the reply
		 */
		reply_len = max(reply_len - 2, (माप_प्रकार) 0);
		reply_len = min(reply_len, *length);

		अगर (reply_len > 0)
			स_नकल(buffer, reply + 2, reply_len);
	पूर्ण

	*length = reply_len;

	kमुक्त(reply);
	kमुक्त(msg);

	वापस 0;

out_msg:
	vmw_बंद_channel(&channel);
	kमुक्त(reply);
out_खोलो:
	*length = 0;
	kमुक्त(msg);
	DRM_ERROR("Failed to get guest info \"%s\".", guest_info_param);

	वापस -EINVAL;
पूर्ण



/**
 * vmw_host_log: Sends a log message to the host
 *
 * @log: शून्य terminated string
 *
 * Returns: 0 on success
 */
पूर्णांक vmw_host_log(स्थिर अक्षर *log)
अणु
	काष्ठा rpc_channel channel;
	अक्षर *msg;
	पूर्णांक ret = 0;


	अगर (!vmw_msg_enabled)
		वापस -ENODEV;

	अगर (!log)
		वापस ret;

	msg = kaप्र_लिखो(GFP_KERNEL, "log %s", log);
	अगर (!msg) अणु
		DRM_ERROR("Cannot allocate memory for host log message.\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (vmw_खोलो_channel(&channel, RPCI_PROTOCOL_NUM))
		जाओ out_खोलो;

	अगर (vmw_send_msg(&channel, msg))
		जाओ out_msg;

	vmw_बंद_channel(&channel);
	kमुक्त(msg);

	वापस 0;

out_msg:
	vmw_बंद_channel(&channel);
out_खोलो:
	kमुक्त(msg);
	DRM_ERROR("Failed to send host log message.\n");

	वापस -EINVAL;
पूर्ण


/**
 * vmw_msg_ioctl: Sends and receveives a message to/from host from/to user-space
 *
 * Sends a message from user-space to host.
 * Can also receive a result from host and वापस that to user-space.
 *
 * @dev: Identअगरies the drm device.
 * @data: Poपूर्णांकer to the ioctl argument.
 * @file_priv: Identअगरies the caller.
 * Return: Zero on success, negative error code on error.
 */

पूर्णांक vmw_msg_ioctl(काष्ठा drm_device *dev, व्योम *data,
		  काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_vmw_msg_arg *arg =
		(काष्ठा drm_vmw_msg_arg *) data;
	काष्ठा rpc_channel channel;
	अक्षर *msg;
	पूर्णांक length;

	msg = kदो_स्मृति(MAX_USER_MSG_LENGTH, GFP_KERNEL);
	अगर (!msg) अणु
		DRM_ERROR("Cannot allocate memory for log message.\n");
		वापस -ENOMEM;
	पूर्ण

	length = म_नकलन_from_user(msg, (व्योम __user *)((अचिन्हित दीर्घ)arg->send),
				   MAX_USER_MSG_LENGTH);
	अगर (length < 0 || length >= MAX_USER_MSG_LENGTH) अणु
		DRM_ERROR("Userspace message access failure.\n");
		kमुक्त(msg);
		वापस -EINVAL;
	पूर्ण


	अगर (vmw_खोलो_channel(&channel, RPCI_PROTOCOL_NUM)) अणु
		DRM_ERROR("Failed to open channel.\n");
		जाओ out_खोलो;
	पूर्ण

	अगर (vmw_send_msg(&channel, msg)) अणु
		DRM_ERROR("Failed to send message to host.\n");
		जाओ out_msg;
	पूर्ण

	अगर (!arg->send_only) अणु
		अक्षर *reply = शून्य;
		माप_प्रकार reply_len = 0;

		अगर (vmw_recv_msg(&channel, (व्योम *) &reply, &reply_len)) अणु
			DRM_ERROR("Failed to receive message from host.\n");
			जाओ out_msg;
		पूर्ण
		अगर (reply && reply_len > 0) अणु
			अगर (copy_to_user((व्योम __user *)((अचिन्हित दीर्घ)arg->receive),
							 reply, reply_len)) अणु
				DRM_ERROR("Failed to copy message to userspace.\n");
				kमुक्त(reply);
				जाओ out_msg;
			पूर्ण
			arg->receive_len = (__u32)reply_len;
		पूर्ण
		kमुक्त(reply);
	पूर्ण

	vmw_बंद_channel(&channel);
	kमुक्त(msg);

	वापस 0;

out_msg:
	vmw_बंद_channel(&channel);
out_खोलो:
	kमुक्त(msg);

	वापस -EINVAL;
पूर्ण
