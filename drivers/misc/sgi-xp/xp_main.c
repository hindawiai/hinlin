<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * (C) Copyright 2020 Hewlett Packard Enterprise Development LP
 * Copyright (c) 2004-2008 Silicon Graphics, Inc.  All Rights Reserved.
 */

/*
 * Cross Partition (XP) base.
 *
 *	XP provides a base from which its users can पूर्णांकeract
 *	with XPC, yet not be dependent on XPC.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश "xp.h"

/* define the XP debug device काष्ठाures to be used with dev_dbg() et al */

अटल काष्ठा device_driver xp_dbg_name = अणु
	.name = "xp"
पूर्ण;

अटल काष्ठा device xp_dbg_subname = अणु
	.init_name = "",		/* set to "" */
	.driver = &xp_dbg_name
पूर्ण;

काष्ठा device *xp = &xp_dbg_subname;

/* max #of partitions possible */
लघु xp_max_npartitions;
EXPORT_SYMBOL_GPL(xp_max_npartitions);

लघु xp_partition_id;
EXPORT_SYMBOL_GPL(xp_partition_id);

u8 xp_region_size;
EXPORT_SYMBOL_GPL(xp_region_size);

अचिन्हित दीर्घ (*xp_pa) (व्योम *addr);
EXPORT_SYMBOL_GPL(xp_pa);

अचिन्हित दीर्घ (*xp_socket_pa) (अचिन्हित दीर्घ gpa);
EXPORT_SYMBOL_GPL(xp_socket_pa);

क्रमागत xp_retval (*xp_remote_स_नकल) (अचिन्हित दीर्घ dst_gpa,
				    स्थिर अचिन्हित दीर्घ src_gpa, माप_प्रकार len);
EXPORT_SYMBOL_GPL(xp_remote_स_नकल);

पूर्णांक (*xp_cpu_to_nasid) (पूर्णांक cpuid);
EXPORT_SYMBOL_GPL(xp_cpu_to_nasid);

क्रमागत xp_retval (*xp_expand_memprotect) (अचिन्हित दीर्घ phys_addr,
					अचिन्हित दीर्घ size);
EXPORT_SYMBOL_GPL(xp_expand_memprotect);
क्रमागत xp_retval (*xp_restrict_memprotect) (अचिन्हित दीर्घ phys_addr,
					  अचिन्हित दीर्घ size);
EXPORT_SYMBOL_GPL(xp_restrict_memprotect);

/*
 * xpc_registrations[] keeps track of xpc_connect()'s करोne by the kernel-level
 * users of XPC.
 */
काष्ठा xpc_registration xpc_registrations[XPC_MAX_NCHANNELS];
EXPORT_SYMBOL_GPL(xpc_registrations);

/*
 * Initialize the XPC पूर्णांकerface to शून्य to indicate that XPC isn't loaded.
 */
काष्ठा xpc_पूर्णांकerface xpc_पूर्णांकerface = अणु पूर्ण;
EXPORT_SYMBOL_GPL(xpc_पूर्णांकerface);

/*
 * XPC calls this when it (the XPC module) has been loaded.
 */
व्योम
xpc_set_पूर्णांकerface(व्योम (*connect) (पूर्णांक),
		  व्योम (*disconnect) (पूर्णांक),
		  क्रमागत xp_retval (*send) (लघु, पूर्णांक, u32, व्योम *, u16),
		  क्रमागत xp_retval (*send_notअगरy) (लघु, पूर्णांक, u32, व्योम *, u16,
						  xpc_notअगरy_func, व्योम *),
		  व्योम (*received) (लघु, पूर्णांक, व्योम *),
		  क्रमागत xp_retval (*partid_to_nasids) (लघु, व्योम *))
अणु
	xpc_पूर्णांकerface.connect = connect;
	xpc_पूर्णांकerface.disconnect = disconnect;
	xpc_पूर्णांकerface.send = send;
	xpc_पूर्णांकerface.send_notअगरy = send_notअगरy;
	xpc_पूर्णांकerface.received = received;
	xpc_पूर्णांकerface.partid_to_nasids = partid_to_nasids;
पूर्ण
EXPORT_SYMBOL_GPL(xpc_set_पूर्णांकerface);

/*
 * XPC calls this when it (the XPC module) is being unloaded.
 */
व्योम
xpc_clear_पूर्णांकerface(व्योम)
अणु
	स_रखो(&xpc_पूर्णांकerface, 0, माप(xpc_पूर्णांकerface));
पूर्ण
EXPORT_SYMBOL_GPL(xpc_clear_पूर्णांकerface);

/*
 * Register क्रम स्वतःmatic establishment of a channel connection whenever
 * a partition comes up.
 *
 * Arguments:
 *
 *	ch_number - channel # to रेजिस्टर क्रम connection.
 *	func - function to call क्रम asynchronous notअगरication of channel
 *	       state changes (i.e., connection, disconnection, error) and
 *	       the arrival of incoming messages.
 *      key - poपूर्णांकer to optional user-defined value that माला_लो passed back
 *	      to the user on any callouts made to func.
 *	payload_size - size in bytes of the XPC message's payload area which
 *		       contains a user-defined message. The user should make
 *		       this large enough to hold their largest message.
 *	nentries - max #of XPC message entries a message queue can contain.
 *		   The actual number, which is determined when a connection
 * 		   is established and may be less then requested, will be
 *		   passed to the user via the xpConnected callout.
 *	asचिन्हित_limit - max number of kthपढ़ोs allowed to be processing
 * 			 messages (per connection) at any given instant.
 *	idle_limit - max number of kthपढ़ोs allowed to be idle at any given
 * 		     instant.
 */
क्रमागत xp_retval
xpc_connect(पूर्णांक ch_number, xpc_channel_func func, व्योम *key, u16 payload_size,
	    u16 nentries, u32 asचिन्हित_limit, u32 idle_limit)
अणु
	काष्ठा xpc_registration *registration;

	DBUG_ON(ch_number < 0 || ch_number >= XPC_MAX_NCHANNELS);
	DBUG_ON(payload_size == 0 || nentries == 0);
	DBUG_ON(func == शून्य);
	DBUG_ON(asचिन्हित_limit == 0 || idle_limit > asचिन्हित_limit);

	अगर (XPC_MSG_SIZE(payload_size) > XPC_MSG_MAX_SIZE)
		वापस xpPayloadTooBig;

	registration = &xpc_registrations[ch_number];

	अगर (mutex_lock_पूर्णांकerruptible(&registration->mutex) != 0)
		वापस xpInterrupted;

	/* अगर XPC_CHANNEL_REGISTERED(ch_number) */
	अगर (registration->func != शून्य) अणु
		mutex_unlock(&registration->mutex);
		वापस xpAlपढ़ोyRegistered;
	पूर्ण

	/* रेजिस्टर the channel क्रम connection */
	registration->entry_size = XPC_MSG_SIZE(payload_size);
	registration->nentries = nentries;
	registration->asचिन्हित_limit = asचिन्हित_limit;
	registration->idle_limit = idle_limit;
	registration->key = key;
	registration->func = func;

	mutex_unlock(&registration->mutex);

	अगर (xpc_पूर्णांकerface.connect)
		xpc_पूर्णांकerface.connect(ch_number);

	वापस xpSuccess;
पूर्ण
EXPORT_SYMBOL_GPL(xpc_connect);

/*
 * Remove the registration क्रम स्वतःmatic connection of the specअगरied channel
 * when a partition comes up.
 *
 * Beक्रमe वापसing this xpc_disconnect() will रुको क्रम all connections on the
 * specअगरied channel have been बंदd/tornकरोwn. So the caller can be assured
 * that they will not be receiving any more callouts from XPC to their
 * function रेजिस्टरed via xpc_connect().
 *
 * Arguments:
 *
 *	ch_number - channel # to unरेजिस्टर.
 */
व्योम
xpc_disconnect(पूर्णांक ch_number)
अणु
	काष्ठा xpc_registration *registration;

	DBUG_ON(ch_number < 0 || ch_number >= XPC_MAX_NCHANNELS);

	registration = &xpc_registrations[ch_number];

	/*
	 * We've decided not to make this a करोwn_पूर्णांकerruptible(), since we
	 * figured XPC's users will just turn around and call xpc_disconnect()
	 * again anyways, so we might as well रुको, अगर need be.
	 */
	mutex_lock(&registration->mutex);

	/* अगर !XPC_CHANNEL_REGISTERED(ch_number) */
	अगर (registration->func == शून्य) अणु
		mutex_unlock(&registration->mutex);
		वापस;
	पूर्ण

	/* हटाओ the connection registration क्रम the specअगरied channel */
	registration->func = शून्य;
	registration->key = शून्य;
	registration->nentries = 0;
	registration->entry_size = 0;
	registration->asचिन्हित_limit = 0;
	registration->idle_limit = 0;

	अगर (xpc_पूर्णांकerface.disconnect)
		xpc_पूर्णांकerface.disconnect(ch_number);

	mutex_unlock(&registration->mutex);

	वापस;
पूर्ण
EXPORT_SYMBOL_GPL(xpc_disconnect);

अटल पूर्णांक __init
xp_init(व्योम)
अणु
	क्रमागत xp_retval ret;
	पूर्णांक ch_number;

	/* initialize the connection registration mutex */
	क्रम (ch_number = 0; ch_number < XPC_MAX_NCHANNELS; ch_number++)
		mutex_init(&xpc_registrations[ch_number].mutex);

	अगर (is_uv_प्रणाली())
		ret = xp_init_uv();
	अन्यथा
		ret = 0;

	अगर (ret != xpSuccess)
		वापस ret;

	वापस 0;
पूर्ण

module_init(xp_init);

अटल व्योम __निकास
xp_निकास(व्योम)
अणु
	अगर (is_uv_प्रणाली())
		xp_निकास_uv();
पूर्ण

module_निकास(xp_निकास);

MODULE_AUTHOR("Silicon Graphics, Inc.");
MODULE_DESCRIPTION("Cross Partition (XP) base");
MODULE_LICENSE("GPL");
