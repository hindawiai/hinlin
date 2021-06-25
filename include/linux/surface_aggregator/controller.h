<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Surface System Aggregator Module (SSAM) controller पूर्णांकerface.
 *
 * Main communication पूर्णांकerface क्रम the SSAM EC. Provides a controller
 * managing access and communication to and from the SSAM EC, as well as मुख्य
 * communication काष्ठाures and definitions.
 *
 * Copyright (C) 2019-2020 Maximilian Luz <luzmaximilian@gmail.com>
 */

#अगर_अघोषित _LINUX_SURFACE_AGGREGATOR_CONTROLLER_H
#घोषणा _LINUX_SURFACE_AGGREGATOR_CONTROLLER_H

#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/types.h>

#समावेश <linux/surface_aggregator/serial_hub.h>


/* -- Main data types and definitions --------------------------------------- */

/**
 * क्रमागत ssam_event_flags - Flags क्रम enabling/disabling SAM events
 * @SSAM_EVENT_SEQUENCED: The event will be sent via a sequenced data frame.
 */
क्रमागत ssam_event_flags अणु
	SSAM_EVENT_SEQUENCED = BIT(0),
पूर्ण;

/**
 * काष्ठा ssam_event - SAM event sent from the EC to the host.
 * @target_category: Target category of the event source. See &क्रमागत ssam_ssh_tc.
 * @target_id:       Target ID of the event source.
 * @command_id:      Command ID of the event.
 * @instance_id:     Instance ID of the event source.
 * @length:          Length of the event payload in bytes.
 * @data:            Event payload data.
 */
काष्ठा ssam_event अणु
	u8 target_category;
	u8 target_id;
	u8 command_id;
	u8 instance_id;
	u16 length;
	u8 data[];
पूर्ण;

/**
 * क्रमागत ssam_request_flags - Flags क्रम SAM requests.
 *
 * @SSAM_REQUEST_HAS_RESPONSE:
 *	Specअगरies that the request expects a response. If not set, the request
 *	will be directly completed after its underlying packet has been
 *	transmitted. If set, the request transport प्रणाली रुकोs क्रम a response
 *	of the request.
 *
 * @SSAM_REQUEST_UNSEQUENCED:
 *	Specअगरies that the request should be transmitted via an unsequenced
 *	packet. If set, the request must not have a response, meaning that this
 *	flag and the %SSAM_REQUEST_HAS_RESPONSE flag are mutually exclusive.
 */
क्रमागत ssam_request_flags अणु
	SSAM_REQUEST_HAS_RESPONSE = BIT(0),
	SSAM_REQUEST_UNSEQUENCED  = BIT(1),
पूर्ण;

/**
 * काष्ठा ssam_request - SAM request description.
 * @target_category: Category of the request's target. See &क्रमागत ssam_ssh_tc.
 * @target_id:       ID of the request's target.
 * @command_id:      Command ID of the request.
 * @instance_id:     Instance ID of the request's target.
 * @flags:           Flags क्रम the request. See &क्रमागत ssam_request_flags.
 * @length:          Length of the request payload in bytes.
 * @payload:         Request payload data.
 *
 * This काष्ठा fully describes a SAM request with payload. It is पूर्णांकended to
 * help set up the actual transport काष्ठा, e.g. &काष्ठा ssam_request_sync,
 * and specअगरically its raw message data via ssam_request_ग_लिखो_data().
 */
काष्ठा ssam_request अणु
	u8 target_category;
	u8 target_id;
	u8 command_id;
	u8 instance_id;
	u16 flags;
	u16 length;
	स्थिर u8 *payload;
पूर्ण;

/**
 * काष्ठा ssam_response - Response buffer क्रम SAM request.
 * @capacity: Capacity of the buffer, in bytes.
 * @length:   Length of the actual data stored in the memory poपूर्णांकed to by
 *            @poपूर्णांकer, in bytes. Set by the transport प्रणाली.
 * @poपूर्णांकer:  Poपूर्णांकer to the buffer's memory, storing the response payload data.
 */
काष्ठा ssam_response अणु
	माप_प्रकार capacity;
	माप_प्रकार length;
	u8 *poपूर्णांकer;
पूर्ण;

काष्ठा ssam_controller;

काष्ठा ssam_controller *ssam_get_controller(व्योम);
काष्ठा ssam_controller *ssam_client_bind(काष्ठा device *client);
पूर्णांक ssam_client_link(काष्ठा ssam_controller *ctrl, काष्ठा device *client);

काष्ठा device *ssam_controller_device(काष्ठा ssam_controller *c);

काष्ठा ssam_controller *ssam_controller_get(काष्ठा ssam_controller *c);
व्योम ssam_controller_put(काष्ठा ssam_controller *c);

व्योम ssam_controller_statelock(काष्ठा ssam_controller *c);
व्योम ssam_controller_stateunlock(काष्ठा ssam_controller *c);

sमाप_प्रकार ssam_request_ग_लिखो_data(काष्ठा ssam_span *buf,
				काष्ठा ssam_controller *ctrl,
				स्थिर काष्ठा ssam_request *spec);


/* -- Synchronous request पूर्णांकerface. ---------------------------------------- */

/**
 * काष्ठा ssam_request_sync - Synchronous SAM request काष्ठा.
 * @base:   Underlying SSH request.
 * @comp:   Completion used to संकेत full completion of the request. After the
 *          request has been submitted, this काष्ठा may only be modअगरied or
 *          deallocated after the completion has been संकेतed.
 *          request has been submitted,
 * @resp:   Buffer to store the response.
 * @status: Status of the request, set after the base request has been
 *          completed or has failed.
 */
काष्ठा ssam_request_sync अणु
	काष्ठा ssh_request base;
	काष्ठा completion comp;
	काष्ठा ssam_response *resp;
	पूर्णांक status;
पूर्ण;

पूर्णांक ssam_request_sync_alloc(माप_प्रकार payload_len, gfp_t flags,
			    काष्ठा ssam_request_sync **rqst,
			    काष्ठा ssam_span *buffer);

व्योम ssam_request_sync_मुक्त(काष्ठा ssam_request_sync *rqst);

पूर्णांक ssam_request_sync_init(काष्ठा ssam_request_sync *rqst,
			   क्रमागत ssam_request_flags flags);

/**
 * ssam_request_sync_set_data - Set message data of a synchronous request.
 * @rqst: The request.
 * @ptr:  Poपूर्णांकer to the request message data.
 * @len:  Length of the request message data.
 *
 * Set the request message data of a synchronous request. The provided buffer
 * needs to live until the request has been completed.
 */
अटल अंतरभूत व्योम ssam_request_sync_set_data(काष्ठा ssam_request_sync *rqst,
					      u8 *ptr, माप_प्रकार len)
अणु
	ssh_request_set_data(&rqst->base, ptr, len);
पूर्ण

/**
 * ssam_request_sync_set_resp - Set response buffer of a synchronous request.
 * @rqst: The request.
 * @resp: The response buffer.
 *
 * Sets the response buffer of a synchronous request. This buffer will store
 * the response of the request after it has been completed. May be %शून्य अगर no
 * response is expected.
 */
अटल अंतरभूत व्योम ssam_request_sync_set_resp(काष्ठा ssam_request_sync *rqst,
					      काष्ठा ssam_response *resp)
अणु
	rqst->resp = resp;
पूर्ण

पूर्णांक ssam_request_sync_submit(काष्ठा ssam_controller *ctrl,
			     काष्ठा ssam_request_sync *rqst);

/**
 * ssam_request_sync_रुको - Wait क्रम completion of a synchronous request.
 * @rqst: The request to रुको क्रम.
 *
 * Wait क्रम completion and release of a synchronous request. After this
 * function terminates, the request is guaranteed to have left the transport
 * प्रणाली. After successful submission of a request, this function must be
 * called beक्रमe accessing the response of the request, मुक्तing the request,
 * or मुक्तing any of the buffers associated with the request.
 *
 * This function must not be called अगर the request has not been submitted yet
 * and may lead to a deadlock/infinite रुको अगर a subsequent request submission
 * fails in that हाल, due to the completion never triggering.
 *
 * Return: Returns the status of the given request, which is set on completion
 * of the packet. This value is zero on success and negative on failure.
 */
अटल अंतरभूत पूर्णांक ssam_request_sync_रुको(काष्ठा ssam_request_sync *rqst)
अणु
	रुको_क्रम_completion(&rqst->comp);
	वापस rqst->status;
पूर्ण

पूर्णांक ssam_request_sync(काष्ठा ssam_controller *ctrl,
		      स्थिर काष्ठा ssam_request *spec,
		      काष्ठा ssam_response *rsp);

पूर्णांक ssam_request_sync_with_buffer(काष्ठा ssam_controller *ctrl,
				  स्थिर काष्ठा ssam_request *spec,
				  काष्ठा ssam_response *rsp,
				  काष्ठा ssam_span *buf);

/**
 * ssam_request_sync_onstack - Execute a synchronous request on the stack.
 * @ctrl: The controller via which the request is submitted.
 * @rqst: The request specअगरication.
 * @rsp:  The response buffer.
 * @payload_len: The (maximum) request payload length.
 *
 * Allocates a synchronous request with specअगरied payload length on the stack,
 * fully initializes it via the provided request specअगरication, submits it,
 * and finally रुकोs क्रम its completion beक्रमe वापसing its status. This
 * helper macro essentially allocates the request message buffer on the stack
 * and then calls ssam_request_sync_with_buffer().
 *
 * Note: The @payload_len parameter specअगरies the maximum payload length, used
 * क्रम buffer allocation. The actual payload length may be smaller.
 *
 * Return: Returns the status of the request or any failure during setup, i.e.
 * zero on success and a negative value on failure.
 */
#घोषणा ssam_request_sync_onstack(ctrl, rqst, rsp, payload_len)			\
	(अणु									\
		u8 __data[SSH_COMMAND_MESSAGE_LENGTH(payload_len)];		\
		काष्ठा ssam_span __buf = अणु &__data[0], ARRAY_SIZE(__data) पूर्ण;	\
										\
		ssam_request_sync_with_buffer(ctrl, rqst, rsp, &__buf);		\
	पूर्ण)

/**
 * __ssam_retry - Retry request in हाल of I/O errors or समयouts.
 * @request: The request function to execute. Must वापस an पूर्णांकeger.
 * @n:       Number of tries.
 * @args:    Arguments क्रम the request function.
 *
 * Executes the given request function, i.e. calls @request. In हाल the
 * request वापसs %-EREMOTEIO (indicates I/O error) or %-ETIMEDOUT (request
 * or underlying packet समयd out), @request will be re-executed again, up to
 * @n बार in total.
 *
 * Return: Returns the वापस value of the last execution of @request.
 */
#घोषणा __ssam_retry(request, n, args...)				\
	(अणु								\
		पूर्णांक __i, __s = 0;					\
									\
		क्रम (__i = (n); __i > 0; __i--) अणु			\
			__s = request(args);				\
			अगर (__s != -ETIMEDOUT && __s != -EREMOTEIO)	\
				अवरोध;					\
		पूर्ण							\
		__s;							\
	पूर्ण)

/**
 * ssam_retry - Retry request in हाल of I/O errors or समयouts up to three
 * बार in total.
 * @request: The request function to execute. Must वापस an पूर्णांकeger.
 * @args:    Arguments क्रम the request function.
 *
 * Executes the given request function, i.e. calls @request. In हाल the
 * request वापसs %-EREMOTEIO (indicates I/O error) or -%ETIMEDOUT (request
 * or underlying packet समयd out), @request will be re-executed again, up to
 * three बार in total.
 *
 * See __ssam_retry() क्रम a more generic macro क्रम this purpose.
 *
 * Return: Returns the वापस value of the last execution of @request.
 */
#घोषणा ssam_retry(request, args...) \
	__ssam_retry(request, 3, args)

/**
 * काष्ठा ssam_request_spec - Blue-prपूर्णांक specअगरication of SAM request.
 * @target_category: Category of the request's target. See &क्रमागत ssam_ssh_tc.
 * @target_id:       ID of the request's target.
 * @command_id:      Command ID of the request.
 * @instance_id:     Instance ID of the request's target.
 * @flags:           Flags क्रम the request. See &क्रमागत ssam_request_flags.
 *
 * Blue-prपूर्णांक specअगरication क्रम a SAM request. This काष्ठा describes the
 * unique अटल parameters of a request (i.e. type) without specअगरying any of
 * its instance-specअगरic data (e.g. payload). It is पूर्णांकended to be used as base
 * क्रम defining simple request functions via the
 * ``SSAM_DEFINE_SYNC_REQUEST_x()`` family of macros.
 */
काष्ठा ssam_request_spec अणु
	u8 target_category;
	u8 target_id;
	u8 command_id;
	u8 instance_id;
	u8 flags;
पूर्ण;

/**
 * काष्ठा ssam_request_spec_md - Blue-prपूर्णांक specअगरication क्रम multi-device SAM
 * request.
 * @target_category: Category of the request's target. See &क्रमागत ssam_ssh_tc.
 * @command_id:      Command ID of the request.
 * @flags:           Flags क्रम the request. See &क्रमागत ssam_request_flags.
 *
 * Blue-prपूर्णांक specअगरication क्रम a multi-device SAM request, i.e. a request
 * that is applicable to multiple device instances, described by their
 * inभागidual target and instance IDs. This काष्ठा describes the unique अटल
 * parameters of a request (i.e. type) without specअगरying any of its
 * instance-specअगरic data (e.g. payload) and without specअगरying any of its
 * device specअगरic IDs (i.e. target and instance ID). It is पूर्णांकended to be
 * used as base क्रम defining simple multi-device request functions via the
 * ``SSAM_DEFINE_SYNC_REQUEST_MD_x()`` and ``SSAM_DEFINE_SYNC_REQUEST_CL_x()``
 * families of macros.
 */
काष्ठा ssam_request_spec_md अणु
	u8 target_category;
	u8 command_id;
	u8 flags;
पूर्ण;

/**
 * SSAM_DEFINE_SYNC_REQUEST_N() - Define synchronous SAM request function
 * with neither argument nor वापस value.
 * @name: Name of the generated function.
 * @spec: Specअगरication (&काष्ठा ssam_request_spec) defining the request.
 *
 * Defines a function executing the synchronous SAM request specअगरied by
 * @spec, with the request having neither argument nor वापस value. The
 * generated function takes care of setting up the request काष्ठा and buffer
 * allocation, as well as execution of the request itself, वापसing once the
 * request has been fully completed. The required transport buffer will be
 * allocated on the stack.
 *
 * The generated function is defined as ``अटल पूर्णांक name(काष्ठा
 * ssam_controller *ctrl)``, वापसing the status of the request, which is
 * zero on success and negative on failure. The ``ctrl`` parameter is the
 * controller via which the request is being sent.
 *
 * Refer to ssam_request_sync_onstack() क्रम more details on the behavior of
 * the generated function.
 */
#घोषणा SSAM_DEFINE_SYNC_REQUEST_N(name, spec...)				\
	अटल पूर्णांक name(काष्ठा ssam_controller *ctrl)				\
	अणु									\
		काष्ठा ssam_request_spec s = (काष्ठा ssam_request_spec)spec;	\
		काष्ठा ssam_request rqst;					\
										\
		rqst.target_category = s.target_category;			\
		rqst.target_id = s.target_id;					\
		rqst.command_id = s.command_id;					\
		rqst.instance_id = s.instance_id;				\
		rqst.flags = s.flags;						\
		rqst.length = 0;						\
		rqst.payload = शून्य;						\
										\
		वापस ssam_request_sync_onstack(ctrl, &rqst, शून्य, 0);		\
	पूर्ण

/**
 * SSAM_DEFINE_SYNC_REQUEST_W() - Define synchronous SAM request function with
 * argument.
 * @name:  Name of the generated function.
 * @atype: Type of the request's argument.
 * @spec:  Specअगरication (&काष्ठा ssam_request_spec) defining the request.
 *
 * Defines a function executing the synchronous SAM request specअगरied by
 * @spec, with the request taking an argument of type @atype and having no
 * वापस value. The generated function takes care of setting up the request
 * काष्ठा, buffer allocation, as well as execution of the request itself,
 * वापसing once the request has been fully completed. The required transport
 * buffer will be allocated on the stack.
 *
 * The generated function is defined as ``अटल पूर्णांक name(काष्ठा
 * ssam_controller *ctrl, स्थिर atype *arg)``, वापसing the status of the
 * request, which is zero on success and negative on failure. The ``ctrl``
 * parameter is the controller via which the request is sent. The request
 * argument is specअगरied via the ``arg`` poपूर्णांकer.
 *
 * Refer to ssam_request_sync_onstack() क्रम more details on the behavior of
 * the generated function.
 */
#घोषणा SSAM_DEFINE_SYNC_REQUEST_W(name, atype, spec...)			\
	अटल पूर्णांक name(काष्ठा ssam_controller *ctrl, स्थिर atype *arg)		\
	अणु									\
		काष्ठा ssam_request_spec s = (काष्ठा ssam_request_spec)spec;	\
		काष्ठा ssam_request rqst;					\
										\
		rqst.target_category = s.target_category;			\
		rqst.target_id = s.target_id;					\
		rqst.command_id = s.command_id;					\
		rqst.instance_id = s.instance_id;				\
		rqst.flags = s.flags;						\
		rqst.length = माप(atype);					\
		rqst.payload = (u8 *)arg;					\
										\
		वापस ssam_request_sync_onstack(ctrl, &rqst, शून्य,		\
						 माप(atype));		\
	पूर्ण

/**
 * SSAM_DEFINE_SYNC_REQUEST_R() - Define synchronous SAM request function with
 * वापस value.
 * @name:  Name of the generated function.
 * @rtype: Type of the request's वापस value.
 * @spec:  Specअगरication (&काष्ठा ssam_request_spec) defining the request.
 *
 * Defines a function executing the synchronous SAM request specअगरied by
 * @spec, with the request taking no argument but having a वापस value of
 * type @rtype. The generated function takes care of setting up the request
 * and response काष्ठाs, buffer allocation, as well as execution of the
 * request itself, वापसing once the request has been fully completed. The
 * required transport buffer will be allocated on the stack.
 *
 * The generated function is defined as ``अटल पूर्णांक name(काष्ठा
 * ssam_controller *ctrl, rtype *ret)``, वापसing the status of the request,
 * which is zero on success and negative on failure. The ``ctrl`` parameter is
 * the controller via which the request is sent. The request's वापस value is
 * written to the memory poपूर्णांकed to by the ``ret`` parameter.
 *
 * Refer to ssam_request_sync_onstack() क्रम more details on the behavior of
 * the generated function.
 */
#घोषणा SSAM_DEFINE_SYNC_REQUEST_R(name, rtype, spec...)			\
	अटल पूर्णांक name(काष्ठा ssam_controller *ctrl, rtype *ret)		\
	अणु									\
		काष्ठा ssam_request_spec s = (काष्ठा ssam_request_spec)spec;	\
		काष्ठा ssam_request rqst;					\
		काष्ठा ssam_response rsp;					\
		पूर्णांक status;							\
										\
		rqst.target_category = s.target_category;			\
		rqst.target_id = s.target_id;					\
		rqst.command_id = s.command_id;					\
		rqst.instance_id = s.instance_id;				\
		rqst.flags = s.flags | SSAM_REQUEST_HAS_RESPONSE;		\
		rqst.length = 0;						\
		rqst.payload = शून्य;						\
										\
		rsp.capacity = माप(rtype);					\
		rsp.length = 0;							\
		rsp.poपूर्णांकer = (u8 *)ret;					\
										\
		status = ssam_request_sync_onstack(ctrl, &rqst, &rsp, 0);	\
		अगर (status)							\
			वापस status;						\
										\
		अगर (rsp.length != माप(rtype)) अणु				\
			काष्ठा device *dev = ssam_controller_device(ctrl);	\
			dev_err(dev,						\
				"rqst: invalid response length, expected %zu, got %zu (tc: %#04x, cid: %#04x)", \
				माप(rtype), rsp.length, rqst.target_category,\
				rqst.command_id);				\
			वापस -EIO;						\
		पूर्ण								\
										\
		वापस 0;							\
	पूर्ण

/**
 * SSAM_DEFINE_SYNC_REQUEST_MD_N() - Define synchronous multi-device SAM
 * request function with neither argument nor वापस value.
 * @name: Name of the generated function.
 * @spec: Specअगरication (&काष्ठा ssam_request_spec_md) defining the request.
 *
 * Defines a function executing the synchronous SAM request specअगरied by
 * @spec, with the request having neither argument nor वापस value. Device
 * specअगरying parameters are not hard-coded, but instead must be provided to
 * the function. The generated function takes care of setting up the request
 * काष्ठा, buffer allocation, as well as execution of the request itself,
 * वापसing once the request has been fully completed. The required transport
 * buffer will be allocated on the stack.
 *
 * The generated function is defined as ``अटल पूर्णांक name(काष्ठा
 * ssam_controller *ctrl, u8 tid, u8 iid)``, वापसing the status of the
 * request, which is zero on success and negative on failure. The ``ctrl``
 * parameter is the controller via which the request is sent, ``tid`` the
 * target ID क्रम the request, and ``iid`` the instance ID.
 *
 * Refer to ssam_request_sync_onstack() क्रम more details on the behavior of
 * the generated function.
 */
#घोषणा SSAM_DEFINE_SYNC_REQUEST_MD_N(name, spec...)				\
	अटल पूर्णांक name(काष्ठा ssam_controller *ctrl, u8 tid, u8 iid)		\
	अणु									\
		काष्ठा ssam_request_spec_md s = (काष्ठा ssam_request_spec_md)spec; \
		काष्ठा ssam_request rqst;					\
										\
		rqst.target_category = s.target_category;			\
		rqst.target_id = tid;						\
		rqst.command_id = s.command_id;					\
		rqst.instance_id = iid;						\
		rqst.flags = s.flags;						\
		rqst.length = 0;						\
		rqst.payload = शून्य;						\
										\
		वापस ssam_request_sync_onstack(ctrl, &rqst, शून्य, 0);		\
	पूर्ण

/**
 * SSAM_DEFINE_SYNC_REQUEST_MD_W() - Define synchronous multi-device SAM
 * request function with argument.
 * @name:  Name of the generated function.
 * @atype: Type of the request's argument.
 * @spec:  Specअगरication (&काष्ठा ssam_request_spec_md) defining the request.
 *
 * Defines a function executing the synchronous SAM request specअगरied by
 * @spec, with the request taking an argument of type @atype and having no
 * वापस value. Device specअगरying parameters are not hard-coded, but instead
 * must be provided to the function. The generated function takes care of
 * setting up the request काष्ठा, buffer allocation, as well as execution of
 * the request itself, वापसing once the request has been fully completed.
 * The required transport buffer will be allocated on the stack.
 *
 * The generated function is defined as ``अटल पूर्णांक name(काष्ठा
 * ssam_controller *ctrl, u8 tid, u8 iid, स्थिर atype *arg)``, वापसing the
 * status of the request, which is zero on success and negative on failure.
 * The ``ctrl`` parameter is the controller via which the request is sent,
 * ``tid`` the target ID क्रम the request, and ``iid`` the instance ID. The
 * request argument is specअगरied via the ``arg`` poपूर्णांकer.
 *
 * Refer to ssam_request_sync_onstack() क्रम more details on the behavior of
 * the generated function.
 */
#घोषणा SSAM_DEFINE_SYNC_REQUEST_MD_W(name, atype, spec...)			\
	अटल पूर्णांक name(काष्ठा ssam_controller *ctrl, u8 tid, u8 iid, स्थिर atype *arg) \
	अणु									\
		काष्ठा ssam_request_spec_md s = (काष्ठा ssam_request_spec_md)spec; \
		काष्ठा ssam_request rqst;					\
										\
		rqst.target_category = s.target_category;			\
		rqst.target_id = tid;						\
		rqst.command_id = s.command_id;					\
		rqst.instance_id = iid;						\
		rqst.flags = s.flags;						\
		rqst.length = माप(atype);					\
		rqst.payload = (u8 *)arg;					\
										\
		वापस ssam_request_sync_onstack(ctrl, &rqst, शून्य,		\
						 माप(atype));		\
	पूर्ण

/**
 * SSAM_DEFINE_SYNC_REQUEST_MD_R() - Define synchronous multi-device SAM
 * request function with वापस value.
 * @name:  Name of the generated function.
 * @rtype: Type of the request's वापस value.
 * @spec:  Specअगरication (&काष्ठा ssam_request_spec_md) defining the request.
 *
 * Defines a function executing the synchronous SAM request specअगरied by
 * @spec, with the request taking no argument but having a वापस value of
 * type @rtype. Device specअगरying parameters are not hard-coded, but instead
 * must be provided to the function. The generated function takes care of
 * setting up the request and response काष्ठाs, buffer allocation, as well as
 * execution of the request itself, वापसing once the request has been fully
 * completed. The required transport buffer will be allocated on the stack.
 *
 * The generated function is defined as ``अटल पूर्णांक name(काष्ठा
 * ssam_controller *ctrl, u8 tid, u8 iid, rtype *ret)``, वापसing the status
 * of the request, which is zero on success and negative on failure. The
 * ``ctrl`` parameter is the controller via which the request is sent, ``tid``
 * the target ID क्रम the request, and ``iid`` the instance ID. The request's
 * वापस value is written to the memory poपूर्णांकed to by the ``ret`` parameter.
 *
 * Refer to ssam_request_sync_onstack() क्रम more details on the behavior of
 * the generated function.
 */
#घोषणा SSAM_DEFINE_SYNC_REQUEST_MD_R(name, rtype, spec...)			\
	अटल पूर्णांक name(काष्ठा ssam_controller *ctrl, u8 tid, u8 iid, rtype *ret) \
	अणु									\
		काष्ठा ssam_request_spec_md s = (काष्ठा ssam_request_spec_md)spec; \
		काष्ठा ssam_request rqst;					\
		काष्ठा ssam_response rsp;					\
		पूर्णांक status;							\
										\
		rqst.target_category = s.target_category;			\
		rqst.target_id = tid;						\
		rqst.command_id = s.command_id;					\
		rqst.instance_id = iid;						\
		rqst.flags = s.flags | SSAM_REQUEST_HAS_RESPONSE;		\
		rqst.length = 0;						\
		rqst.payload = शून्य;						\
										\
		rsp.capacity = माप(rtype);					\
		rsp.length = 0;							\
		rsp.poपूर्णांकer = (u8 *)ret;					\
										\
		status = ssam_request_sync_onstack(ctrl, &rqst, &rsp, 0);	\
		अगर (status)							\
			वापस status;						\
										\
		अगर (rsp.length != माप(rtype)) अणु				\
			काष्ठा device *dev = ssam_controller_device(ctrl);	\
			dev_err(dev,						\
				"rqst: invalid response length, expected %zu, got %zu (tc: %#04x, cid: %#04x)", \
				माप(rtype), rsp.length, rqst.target_category,\
				rqst.command_id);				\
			वापस -EIO;						\
		पूर्ण								\
										\
		वापस 0;							\
	पूर्ण


/* -- Event notअगरier/callbacks. --------------------------------------------- */

#घोषणा SSAM_NOTIF_STATE_SHIFT		2
#घोषणा SSAM_NOTIF_STATE_MASK		((1 << SSAM_NOTIF_STATE_SHIFT) - 1)

/**
 * क्रमागत ssam_notअगर_flags - Flags used in वापस values from SSAM notअगरier
 * callback functions.
 *
 * @SSAM_NOTIF_HANDLED:
 *	Indicates that the notअगरication has been handled. This flag should be
 *	set by the handler अगर the handler can act/has acted upon the event
 *	provided to it. This flag should not be set अगर the handler is not a
 *	primary handler पूर्णांकended क्रम the provided event.
 *
 *	If this flag has not been set by any handler after the notअगरier chain
 *	has been traversed, a warning will be emitted, stating that the event
 *	has not been handled.
 *
 * @SSAM_NOTIF_STOP:
 *	Indicates that the notअगरier traversal should stop. If this flag is
 *	वापसed from a notअगरier callback, notअगरier chain traversal will
 *	immediately stop and any reमुख्यing notअगरiers will not be called. This
 *	flag is स्वतःmatically set when ssam_notअगरier_from_त्रुटि_सं() is called
 *	with a negative error value.
 */
क्रमागत ssam_notअगर_flags अणु
	SSAM_NOTIF_HANDLED = BIT(0),
	SSAM_NOTIF_STOP    = BIT(1),
पूर्ण;

काष्ठा ssam_event_notअगरier;

प्रकार u32 (*ssam_notअगरier_fn_t)(काष्ठा ssam_event_notअगरier *nf,
				  स्थिर काष्ठा ssam_event *event);

/**
 * काष्ठा ssam_notअगरier_block - Base notअगरier block क्रम SSAM event
 * notअगरications.
 * @node:     The node क्रम the list of notअगरiers.
 * @fn:       The callback function of this notअगरier. This function takes the
 *            respective notअगरier block and event as input and should वापस
 *            a notअगरier value, which can either be obtained from the flags
 *            provided in &क्रमागत ssam_notअगर_flags, converted from a standard
 *            error value via ssam_notअगरier_from_त्रुटि_सं(), or a combination of
 *            both (e.g. ``ssam_notअगरier_from_त्रुटि_सं(e) | SSAM_NOTIF_HANDLED``).
 * @priority: Priority value determining the order in which notअगरier callbacks
 *            will be called. A higher value means higher priority, i.e. the
 *            associated callback will be executed earlier than other (lower
 *            priority) callbacks.
 */
काष्ठा ssam_notअगरier_block अणु
	काष्ठा list_head node;
	ssam_notअगरier_fn_t fn;
	पूर्णांक priority;
पूर्ण;

/**
 * ssam_notअगरier_from_त्रुटि_सं() - Convert standard error value to notअगरier
 * वापस code.
 * @err: The error code to convert, must be negative (in हाल of failure) or
 *       zero (in हाल of success).
 *
 * Return: Returns the notअगरier वापस value obtained by converting the
 * specअगरied @err value. In हाल @err is negative, the %SSAM_NOTIF_STOP flag
 * will be set, causing notअगरier call chain traversal to पात.
 */
अटल अंतरभूत u32 ssam_notअगरier_from_त्रुटि_सं(पूर्णांक err)
अणु
	अगर (WARN_ON(err > 0) || err == 0)
		वापस 0;
	अन्यथा
		वापस ((-err) << SSAM_NOTIF_STATE_SHIFT) | SSAM_NOTIF_STOP;
पूर्ण

/**
 * ssam_notअगरier_to_त्रुटि_सं() - Convert notअगरier वापस code to standard error
 * value.
 * @ret: The notअगरier वापस value to convert.
 *
 * Return: Returns the negative error value encoded in @ret or zero अगर @ret
 * indicates success.
 */
अटल अंतरभूत पूर्णांक ssam_notअगरier_to_त्रुटि_सं(u32 ret)
अणु
	वापस -(ret >> SSAM_NOTIF_STATE_SHIFT);
पूर्ण


/* -- Event/notअगरication registry. ------------------------------------------ */

/**
 * काष्ठा ssam_event_registry - Registry specअगरication used क्रम enabling events.
 * @target_category: Target category क्रम the event registry requests.
 * @target_id:       Target ID क्रम the event registry requests.
 * @cid_enable:      Command ID क्रम the event-enable request.
 * @cid_disable:     Command ID क्रम the event-disable request.
 *
 * This काष्ठा describes a SAM event registry via the minimal collection of
 * SAM IDs specअगरying the requests to use क्रम enabling and disabling an event.
 * The inभागidual event to be enabled/disabled itself is specअगरied via &काष्ठा
 * ssam_event_id.
 */
काष्ठा ssam_event_registry अणु
	u8 target_category;
	u8 target_id;
	u8 cid_enable;
	u8 cid_disable;
पूर्ण;

/**
 * काष्ठा ssam_event_id - Unique event ID used क्रम enabling events.
 * @target_category: Target category of the event source.
 * @instance:        Instance ID of the event source.
 *
 * This काष्ठा specअगरies the event to be enabled/disabled via an बाह्यally
 * provided registry. It करोes not specअगरy the registry to be used itself, this
 * is करोne via &काष्ठा ssam_event_registry.
 */
काष्ठा ssam_event_id अणु
	u8 target_category;
	u8 instance;
पूर्ण;

/**
 * क्रमागत ssam_event_mask - Flags specअगरying how events are matched to notअगरiers.
 *
 * @SSAM_EVENT_MASK_NONE:
 *	Run the callback क्रम any event with matching target category. Do not
 *	करो any additional filtering.
 *
 * @SSAM_EVENT_MASK_TARGET:
 *	In addition to filtering by target category, only execute the notअगरier
 *	callback क्रम events with a target ID matching to the one of the
 *	registry used क्रम enabling/disabling the event.
 *
 * @SSAM_EVENT_MASK_INSTANCE:
 *	In addition to filtering by target category, only execute the notअगरier
 *	callback क्रम events with an instance ID matching to the instance ID
 *	used when enabling the event.
 *
 * @SSAM_EVENT_MASK_STRICT:
 *	Do all the filtering above.
 */
क्रमागत ssam_event_mask अणु
	SSAM_EVENT_MASK_TARGET   = BIT(0),
	SSAM_EVENT_MASK_INSTANCE = BIT(1),

	SSAM_EVENT_MASK_NONE = 0,
	SSAM_EVENT_MASK_STRICT =
		  SSAM_EVENT_MASK_TARGET
		| SSAM_EVENT_MASK_INSTANCE,
पूर्ण;

/**
 * SSAM_EVENT_REGISTRY() - Define a new event registry.
 * @tc:      Target category क्रम the event registry requests.
 * @tid:     Target ID क्रम the event registry requests.
 * @cid_en:  Command ID क्रम the event-enable request.
 * @cid_dis: Command ID क्रम the event-disable request.
 *
 * Return: Returns the &काष्ठा ssam_event_registry specअगरied by the given
 * parameters.
 */
#घोषणा SSAM_EVENT_REGISTRY(tc, tid, cid_en, cid_dis)	\
	((काष्ठा ssam_event_registry) अणु			\
		.target_category = (tc),		\
		.target_id = (tid),			\
		.cid_enable = (cid_en),			\
		.cid_disable = (cid_dis),		\
	पूर्ण)

#घोषणा SSAM_EVENT_REGISTRY_SAM	\
	SSAM_EVENT_REGISTRY(SSAM_SSH_TC_SAM, 0x01, 0x0b, 0x0c)

#घोषणा SSAM_EVENT_REGISTRY_KIP	\
	SSAM_EVENT_REGISTRY(SSAM_SSH_TC_KIP, 0x02, 0x27, 0x28)

#घोषणा SSAM_EVENT_REGISTRY_REG \
	SSAM_EVENT_REGISTRY(SSAM_SSH_TC_REG, 0x02, 0x01, 0x02)

/**
 * काष्ठा ssam_event_notअगरier - Notअगरier block क्रम SSAM events.
 * @base:        The base notअगरier block with callback function and priority.
 * @event:       The event क्रम which this block will receive notअगरications.
 * @event.reg:   Registry via which the event will be enabled/disabled.
 * @event.id:    ID specअगरying the event.
 * @event.mask:  Flags determining how events are matched to the notअगरier.
 * @event.flags: Flags used क्रम enabling the event.
 */
काष्ठा ssam_event_notअगरier अणु
	काष्ठा ssam_notअगरier_block base;

	काष्ठा अणु
		काष्ठा ssam_event_registry reg;
		काष्ठा ssam_event_id id;
		क्रमागत ssam_event_mask mask;
		u8 flags;
	पूर्ण event;
पूर्ण;

पूर्णांक ssam_notअगरier_रेजिस्टर(काष्ठा ssam_controller *ctrl,
			   काष्ठा ssam_event_notअगरier *n);

पूर्णांक ssam_notअगरier_unरेजिस्टर(काष्ठा ssam_controller *ctrl,
			     काष्ठा ssam_event_notअगरier *n);

#पूर्ण_अगर /* _LINUX_SURFACE_AGGREGATOR_CONTROLLER_H */
