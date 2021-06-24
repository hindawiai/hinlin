<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  drivers/s390/net/iucv.h
 *    IUCV base support.
 *
 *  S390 version
 *    Copyright 2000, 2006 IBM Corporation
 *    Author(s):Alan Alपंचांगark (Alan_Alपंचांगark@us.ibm.com)
 *		Xenia Tkatschow (xenia@us.ibm.com)
 *    Rewritten क्रम af_iucv:
 *	Martin Schwidefsky <schwidefsky@de.ibm.com>
 *
 *
 * Functionality:
 * To explore any of the IUCV functions, one must first रेजिस्टर their
 * program using iucv_रेजिस्टर(). Once your program has successfully
 * completed a रेजिस्टर, it can exploit the other functions.
 * For furthur reference on all IUCV functionality, refer to the
 * CP Programming Services book, also available on the web thru
 * www.vm.ibm.com/pubs, manual # SC24-6084
 *
 * Definition of Return Codes
 * - All positive वापस codes including zero are reflected back
 *   from CP. The definition of each वापस code can be found in
 *   CP Programming Services book.
 * - Return Code of:
 *   -EINVAL: Invalid value
 *   -ENOMEM: storage allocation failed
 */

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/debug.h>

/*
 * IUCV option flags usable by device drivers:
 *
 * IUCV_IPRMDATA  Indicates that your program can handle a message in the
 *		  parameter list / a message is sent in the parameter list.
 *		  Used क्रम iucv_path_accept, iucv_path_connect,
 *		  iucv_message_reply, iucv_message_send, iucv_message_send2way.
 * IUCV_IPQUSCE	  Indicates that you करो not want to receive messages on this
 *		  path until an iucv_path_resume is issued.
 *		  Used क्रम iucv_path_accept, iucv_path_connect.
 * IUCV_IPBUFLST  Indicates that an address list is used क्रम the message data.
 *		  Used क्रम iucv_message_receive, iucv_message_send,
 *		  iucv_message_send2way.
 * IUCV_IPPRTY	  Specअगरies that you want to send priority messages.
 *		  Used क्रम iucv_path_accept, iucv_path_connect,
 *		  iucv_message_reply, iucv_message_send, iucv_message_send2way.
 * IUCV_IPSYNC	  Indicates a synchronous send request.
 *		  Used क्रम iucv_message_send, iucv_message_send2way.
 * IUCV_IPANSLST  Indicates that an address list is used क्रम the reply data.
 *		  Used क्रम iucv_message_reply, iucv_message_send2way.
 * IUCV_IPLOCAL	  Specअगरies that the communication partner has to be on the
 *		  local प्रणाली. If local is specअगरied no target class can be
 *		  specअगरied.
 *		  Used क्रम iucv_path_connect.
 *
 * All flags are defined in the input field IPFLAGS1 of each function
 * and can be found in CP Programming Services.
 */
#घोषणा IUCV_IPRMDATA	0x80
#घोषणा IUCV_IPQUSCE	0x40
#घोषणा IUCV_IPBUFLST	0x40
#घोषणा IUCV_IPPRTY	0x20
#घोषणा IUCV_IPANSLST	0x08
#घोषणा IUCV_IPSYNC	0x04
#घोषणा IUCV_IPLOCAL	0x01

/*
 * iucv_array : Defines buffer array.
 * Inside the array may be 31- bit addresses and 31-bit lengths.
 * Use a poपूर्णांकer to an iucv_array as the buffer, reply or answer
 * parameter on iucv_message_send, iucv_message_send2way, iucv_message_receive
 * and iucv_message_reply अगर IUCV_IPBUFLST or IUCV_IPANSLST are used.
 */
काष्ठा iucv_array अणु
	u32 address;
	u32 length;
पूर्ण __attribute__ ((aligned (8)));

बाह्य काष्ठा bus_type iucv_bus;
बाह्य काष्ठा device *iucv_root;

/*
 * काष्ठा iucv_path
 * pathid: 16 bit path identअगरication
 * msglim: 16 bit message limit
 * flags: properties of the path: IPRMDATA, IPQUSCE, IPPRTY
 * handler:  address of iucv handler काष्ठाure
 * निजी: निजी inक्रमmation of the handler associated with the path
 * list: list_head क्रम the iucv_handler path list.
 */
काष्ठा iucv_path अणु
	u16 pathid;
	u16 msglim;
	u8  flags;
	व्योम *निजी;
	काष्ठा iucv_handler *handler;
	काष्ठा list_head list;
पूर्ण;

/*
 * काष्ठा iucv_message
 * id: 32 bit message id
 * audit: 32 bit error inक्रमmation of purged or replied messages
 * class: 32 bit target class of a message (source class क्रम replies)
 * tag: 32 bit tag to be associated with the message
 * length: 32 bit length of the message / reply
 * reply_size: 32 bit maximum allowed length of the reply
 * rmmsg: 8 byte अंतरभूत message
 * flags: message properties (IUCV_IPPRTY)
 */
काष्ठा iucv_message अणु
	u32 id;
	u32 audit;
	u32 class;
	u32 tag;
	u32 length;
	u32 reply_size;
	u8  rmmsg[8];
	u8  flags;
पूर्ण __packed;

/*
 * काष्ठा iucv_handler
 *
 * A vector of functions that handle IUCV पूर्णांकerrupts. Each functions माला_लो
 * a parameter area as defined by the CP Programming Services and निजी
 * poपूर्णांकer that is provided by the user of the पूर्णांकerface.
 */
काष्ठा iucv_handler अणु
	 /*
	  * The path_pending function is called after an iucv पूर्णांकerrupt
	  * type 0x01 has been received. The base code allocates a path
	  * काष्ठाure and "asks" the handler अगर this path beदीर्घs to the
	  * handler. To accept the path the path_pending function needs
	  * to call iucv_path_accept and वापस 0. If the callback वापसs
	  * a value != 0 the iucv base code will जारी with the next
	  * handler. The order in which the path_pending functions are
	  * called is the order of the registration of the iucv handlers
	  * to the base code.
	  */
	पूर्णांक  (*path_pending)(काष्ठा iucv_path *, u8 *ipvmid, u8 *ipuser);
	/*
	 * The path_complete function is called after an iucv पूर्णांकerrupt
	 * type 0x02 has been received क्रम a path that has been established
	 * क्रम this handler with iucv_path_connect and got accepted by the
	 * peer with iucv_path_accept.
	 */
	व्योम (*path_complete)(काष्ठा iucv_path *, u8 *ipuser);
	 /*
	  * The path_severed function is called after an iucv पूर्णांकerrupt
	  * type 0x03 has been received. The communication peer shutकरोwn
	  * his end of the communication path. The path still exists and
	  * reमुख्यing messages can be received until a iucv_path_sever
	  * shuts करोwn the other end of the path as well.
	  */
	व्योम (*path_severed)(काष्ठा iucv_path *, u8 *ipuser);
	/*
	 * The path_quiesced function is called after an icuv पूर्णांकerrupt
	 * type 0x04 has been received. The communication peer has quiesced
	 * the path. Delivery of messages is stopped until iucv_path_resume
	 * has been called.
	 */
	व्योम (*path_quiesced)(काष्ठा iucv_path *, u8 *ipuser);
	/*
	 * The path_resumed function is called after an icuv पूर्णांकerrupt
	 * type 0x05 has been received. The communication peer has resumed
	 * the path.
	 */
	व्योम (*path_resumed)(काष्ठा iucv_path *, u8 *ipuser);
	/*
	 * The message_pending function is called after an icuv पूर्णांकerrupt
	 * type 0x06 or type 0x07 has been received. A new message is
	 * available and can be received with iucv_message_receive.
	 */
	व्योम (*message_pending)(काष्ठा iucv_path *, काष्ठा iucv_message *);
	/*
	 * The message_complete function is called after an icuv पूर्णांकerrupt
	 * type 0x08 or type 0x09 has been received. A message send with
	 * iucv_message_send2way has been replied to. The reply can be
	 * received with iucv_message_receive.
	 */
	व्योम (*message_complete)(काष्ठा iucv_path *, काष्ठा iucv_message *);

	काष्ठा list_head list;
	काष्ठा list_head paths;
पूर्ण;

/**
 * iucv_रेजिस्टर:
 * @handler: address of iucv handler काष्ठाure
 * @smp: != 0 indicates that the handler can deal with out of order messages
 *
 * Registers a driver with IUCV.
 *
 * Returns 0 on success, -ENOMEM अगर the memory allocation क्रम the pathid
 * table failed, or -EIO अगर IUCV_DECLARE_BUFFER failed on all cpus.
 */
पूर्णांक iucv_रेजिस्टर(काष्ठा iucv_handler *handler, पूर्णांक smp);

/**
 * iucv_unरेजिस्टर
 * @handler:  address of iucv handler काष्ठाure
 * @smp: != 0 indicates that the handler can deal with out of order messages
 *
 * Unरेजिस्टर driver from IUCV.
 */
व्योम iucv_unरेजिस्टर(काष्ठा iucv_handler *handle, पूर्णांक smp);

/**
 * iucv_path_alloc
 * @msglim: initial message limit
 * @flags: initial flags
 * @gfp: kदो_स्मृति allocation flag
 *
 * Allocate a new path काष्ठाure क्रम use with iucv_connect.
 *
 * Returns शून्य अगर the memory allocation failed or a poपूर्णांकer to the
 * path काष्ठाure.
 */
अटल अंतरभूत काष्ठा iucv_path *iucv_path_alloc(u16 msglim, u8 flags, gfp_t gfp)
अणु
	काष्ठा iucv_path *path;

	path = kzalloc(माप(काष्ठा iucv_path), gfp);
	अगर (path) अणु
		path->msglim = msglim;
		path->flags = flags;
	पूर्ण
	वापस path;
पूर्ण

/**
 * iucv_path_मुक्त
 * @path: address of iucv path काष्ठाure
 *
 * Frees a path काष्ठाure.
 */
अटल अंतरभूत व्योम iucv_path_मुक्त(काष्ठा iucv_path *path)
अणु
	kमुक्त(path);
पूर्ण

/**
 * iucv_path_accept
 * @path: address of iucv path काष्ठाure
 * @handler: address of iucv handler काष्ठाure
 * @userdata: 16 bytes of data reflected to the communication partner
 * @निजी: निजी data passed to पूर्णांकerrupt handlers क्रम this path
 *
 * This function is issued after the user received a connection pending
 * बाह्यal पूर्णांकerrupt and now wishes to complete the IUCV communication path.
 *
 * Returns the result of the CP IUCV call.
 */
पूर्णांक iucv_path_accept(काष्ठा iucv_path *path, काष्ठा iucv_handler *handler,
		     u8 *userdata, व्योम *निजी);

/**
 * iucv_path_connect
 * @path: address of iucv path काष्ठाure
 * @handler: address of iucv handler काष्ठाure
 * @userid: 8-byte user identअगरication
 * @प्रणाली: 8-byte target प्रणाली identअगरication
 * @userdata: 16 bytes of data reflected to the communication partner
 * @निजी: निजी data passed to पूर्णांकerrupt handlers क्रम this path
 *
 * This function establishes an IUCV path. Although the connect may complete
 * successfully, you are not able to use the path until you receive an IUCV
 * Connection Complete बाह्यal पूर्णांकerrupt.
 *
 * Returns the result of the CP IUCV call.
 */
पूर्णांक iucv_path_connect(काष्ठा iucv_path *path, काष्ठा iucv_handler *handler,
		      u8 *userid, u8 *प्रणाली, u8 *userdata,
		      व्योम *निजी);

/**
 * iucv_path_quiesce:
 * @path: address of iucv path काष्ठाure
 * @userdata: 16 bytes of data reflected to the communication partner
 *
 * This function temporarily suspends incoming messages on an IUCV path.
 * You can later reactivate the path by invoking the iucv_resume function.
 *
 * Returns the result from the CP IUCV call.
 */
पूर्णांक iucv_path_quiesce(काष्ठा iucv_path *path, u8 *userdata);

/**
 * iucv_path_resume:
 * @path: address of iucv path काष्ठाure
 * @userdata: 16 bytes of data reflected to the communication partner
 *
 * This function resumes incoming messages on an IUCV path that has
 * been stopped with iucv_path_quiesce.
 *
 * Returns the result from the CP IUCV call.
 */
पूर्णांक iucv_path_resume(काष्ठा iucv_path *path, u8 *userdata);

/**
 * iucv_path_sever
 * @path: address of iucv path काष्ठाure
 * @userdata: 16 bytes of data reflected to the communication partner
 *
 * This function terminates an IUCV path.
 *
 * Returns the result from the CP IUCV call.
 */
पूर्णांक iucv_path_sever(काष्ठा iucv_path *path, u8 *userdata);

/**
 * iucv_message_purge
 * @path: address of iucv path काष्ठाure
 * @msg: address of iucv msg काष्ठाure
 * @srccls: source class of message
 *
 * Cancels a message you have sent.
 *
 * Returns the result from the CP IUCV call.
 */
पूर्णांक iucv_message_purge(काष्ठा iucv_path *path, काष्ठा iucv_message *msg,
		       u32 srccls);

/**
 * iucv_message_receive
 * @path: address of iucv path काष्ठाure
 * @msg: address of iucv msg काष्ठाure
 * @flags: flags that affect how the message is received (IUCV_IPBUFLST)
 * @buffer: address of data buffer or address of काष्ठा iucv_array
 * @size: length of data buffer
 * @residual:
 *
 * This function receives messages that are being sent to you over
 * established paths. This function will deal with RMDATA messages
 * embedded in काष्ठा iucv_message as well.
 *
 * Locking:	local_bh_enable/local_bh_disable
 *
 * Returns the result from the CP IUCV call.
 */
पूर्णांक iucv_message_receive(काष्ठा iucv_path *path, काष्ठा iucv_message *msg,
			 u8 flags, व्योम *buffer, माप_प्रकार size, माप_प्रकार *residual);

/**
 * __iucv_message_receive
 * @path: address of iucv path काष्ठाure
 * @msg: address of iucv msg काष्ठाure
 * @flags: flags that affect how the message is received (IUCV_IPBUFLST)
 * @buffer: address of data buffer or address of काष्ठा iucv_array
 * @size: length of data buffer
 * @residual:
 *
 * This function receives messages that are being sent to you over
 * established paths. This function will deal with RMDATA messages
 * embedded in काष्ठा iucv_message as well.
 *
 * Locking:	no locking.
 *
 * Returns the result from the CP IUCV call.
 */
पूर्णांक __iucv_message_receive(काष्ठा iucv_path *path, काष्ठा iucv_message *msg,
			   u8 flags, व्योम *buffer, माप_प्रकार size,
			   माप_प्रकार *residual);

/**
 * iucv_message_reject
 * @path: address of iucv path काष्ठाure
 * @msg: address of iucv msg काष्ठाure
 *
 * The reject function refuses a specअगरied message. Between the समय you
 * are notअगरied of a message and the समय that you complete the message,
 * the message may be rejected.
 *
 * Returns the result from the CP IUCV call.
 */
पूर्णांक iucv_message_reject(काष्ठा iucv_path *path, काष्ठा iucv_message *msg);

/**
 * iucv_message_reply
 * @path: address of iucv path काष्ठाure
 * @msg: address of iucv msg काष्ठाure
 * @flags: how the reply is sent (IUCV_IPRMDATA, IUCV_IPPRTY, IUCV_IPBUFLST)
 * @reply: address of data buffer or address of काष्ठा iucv_array
 * @size: length of reply data buffer
 *
 * This function responds to the two-way messages that you receive. You
 * must identअगरy completely the message to which you wish to reply. ie,
 * pathid, msgid, and trgcls. Prmmsg signअगरies the data is moved पूर्णांकo
 * the parameter list.
 *
 * Returns the result from the CP IUCV call.
 */
पूर्णांक iucv_message_reply(काष्ठा iucv_path *path, काष्ठा iucv_message *msg,
		       u8 flags, व्योम *reply, माप_प्रकार size);

/**
 * iucv_message_send
 * @path: address of iucv path काष्ठाure
 * @msg: address of iucv msg काष्ठाure
 * @flags: how the message is sent (IUCV_IPRMDATA, IUCV_IPPRTY, IUCV_IPBUFLST)
 * @srccls: source class of message
 * @buffer: address of data buffer or address of काष्ठा iucv_array
 * @size: length of send buffer
 *
 * This function transmits data to another application. Data to be
 * transmitted is in a buffer and this is a one-way message and the
 * receiver will not reply to the message.
 *
 * Locking:	local_bh_enable/local_bh_disable
 *
 * Returns the result from the CP IUCV call.
 */
पूर्णांक iucv_message_send(काष्ठा iucv_path *path, काष्ठा iucv_message *msg,
		      u8 flags, u32 srccls, व्योम *buffer, माप_प्रकार size);

/**
 * __iucv_message_send
 * @path: address of iucv path काष्ठाure
 * @msg: address of iucv msg काष्ठाure
 * @flags: how the message is sent (IUCV_IPRMDATA, IUCV_IPPRTY, IUCV_IPBUFLST)
 * @srccls: source class of message
 * @buffer: address of data buffer or address of काष्ठा iucv_array
 * @size: length of send buffer
 *
 * This function transmits data to another application. Data to be
 * transmitted is in a buffer and this is a one-way message and the
 * receiver will not reply to the message.
 *
 * Locking:	no locking.
 *
 * Returns the result from the CP IUCV call.
 */
पूर्णांक __iucv_message_send(काष्ठा iucv_path *path, काष्ठा iucv_message *msg,
			u8 flags, u32 srccls, व्योम *buffer, माप_प्रकार size);

/**
 * iucv_message_send2way
 * @path: address of iucv path काष्ठाure
 * @msg: address of iucv msg काष्ठाure
 * @flags: how the message is sent and the reply is received
 *	   (IUCV_IPRMDATA, IUCV_IPBUFLST, IUCV_IPPRTY, IUCV_ANSLST)
 * @srccls: source class of message
 * @buffer: address of data buffer or address of काष्ठा iucv_array
 * @size: length of send buffer
 * @ansbuf: address of answer buffer or address of काष्ठा iucv_array
 * @asize: size of reply buffer
 *
 * This function transmits data to another application. Data to be
 * transmitted is in a buffer. The receiver of the send is expected to
 * reply to the message and a buffer is provided पूर्णांकo which IUCV moves
 * the reply to this message.
 *
 * Returns the result from the CP IUCV call.
 */
पूर्णांक iucv_message_send2way(काष्ठा iucv_path *path, काष्ठा iucv_message *msg,
			  u8 flags, u32 srccls, व्योम *buffer, माप_प्रकार size,
			  व्योम *answer, माप_प्रकार asize, माप_प्रकार *residual);

काष्ठा iucv_पूर्णांकerface अणु
	पूर्णांक (*message_receive)(काष्ठा iucv_path *path, काष्ठा iucv_message *msg,
		u8 flags, व्योम *buffer, माप_प्रकार size, माप_प्रकार *residual);
	पूर्णांक (*__message_receive)(काष्ठा iucv_path *path,
		काष्ठा iucv_message *msg, u8 flags, व्योम *buffer, माप_प्रकार size,
		माप_प्रकार *residual);
	पूर्णांक (*message_reply)(काष्ठा iucv_path *path, काष्ठा iucv_message *msg,
		u8 flags, व्योम *reply, माप_प्रकार size);
	पूर्णांक (*message_reject)(काष्ठा iucv_path *path, काष्ठा iucv_message *msg);
	पूर्णांक (*message_send)(काष्ठा iucv_path *path, काष्ठा iucv_message *msg,
		u8 flags, u32 srccls, व्योम *buffer, माप_प्रकार size);
	पूर्णांक (*__message_send)(काष्ठा iucv_path *path, काष्ठा iucv_message *msg,
		u8 flags, u32 srccls, व्योम *buffer, माप_प्रकार size);
	पूर्णांक (*message_send2way)(काष्ठा iucv_path *path,
		काष्ठा iucv_message *msg, u8 flags, u32 srccls, व्योम *buffer,
		माप_प्रकार size, व्योम *answer, माप_प्रकार asize, माप_प्रकार *residual);
	पूर्णांक (*message_purge)(काष्ठा iucv_path *path, काष्ठा iucv_message *msg,
		u32 srccls);
	पूर्णांक (*path_accept)(काष्ठा iucv_path *path, काष्ठा iucv_handler *handler,
		u8 userdata[16], व्योम *निजी);
	पूर्णांक (*path_connect)(काष्ठा iucv_path *path,
		काष्ठा iucv_handler *handler,
		u8 userid[8], u8 प्रणाली[8], u8 userdata[16], व्योम *निजी);
	पूर्णांक (*path_quiesce)(काष्ठा iucv_path *path, u8 userdata[16]);
	पूर्णांक (*path_resume)(काष्ठा iucv_path *path, u8 userdata[16]);
	पूर्णांक (*path_sever)(काष्ठा iucv_path *path, u8 userdata[16]);
	पूर्णांक (*iucv_रेजिस्टर)(काष्ठा iucv_handler *handler, पूर्णांक smp);
	व्योम (*iucv_unरेजिस्टर)(काष्ठा iucv_handler *handler, पूर्णांक smp);
	काष्ठा bus_type *bus;
	काष्ठा device *root;
पूर्ण;

बाह्य काष्ठा iucv_पूर्णांकerface iucv_अगर;
