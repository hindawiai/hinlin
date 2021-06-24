<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2017-2018, Intel Corporation
 */

#अगर_अघोषित __STRATIX10_SVC_CLIENT_H
#घोषणा __STRATIX10_SVC_CLIENT_H

/*
 * Service layer driver supports client names
 *
 * fpga: क्रम FPGA configuration
 * rsu: क्रम remote status update
 */
#घोषणा SVC_CLIENT_FPGA			"fpga"
#घोषणा SVC_CLIENT_RSU			"rsu"

/*
 * Status of the sent command, in bit number
 *
 * SVC_STATUS_OK:
 * Secure firmware accepts the request issued by one of service clients.
 *
 * SVC_STATUS_BUFFER_SUBMITTED:
 * Service client successfully submits data buffer to secure firmware.
 *
 * SVC_STATUS_BUFFER_DONE:
 * Secure firmware completes data process, पढ़ोy to accept the
 * next WRITE transaction.
 *
 * SVC_STATUS_COMPLETED:
 * Secure firmware completes service request successfully. In हाल of
 * FPGA configuration, FPGA should be in user mode.
 *
 * SVC_COMMAND_STATUS_BUSY:
 * Service request is still in process.
 *
 * SVC_COMMAND_STATUS_ERROR:
 * Error encountered during the process of the service request.
 *
 * SVC_STATUS_NO_SUPPORT:
 * Secure firmware करोesn't support requested features such as RSU retry
 * or RSU notअगरy.
 */
#घोषणा SVC_STATUS_OK			0
#घोषणा SVC_STATUS_BUFFER_SUBMITTED	1
#घोषणा SVC_STATUS_BUFFER_DONE		2
#घोषणा SVC_STATUS_COMPLETED		3
#घोषणा SVC_STATUS_BUSY			4
#घोषणा SVC_STATUS_ERROR		5
#घोषणा SVC_STATUS_NO_SUPPORT		6

/*
 * Flag bit क्रम COMMAND_RECONFIG
 *
 * COMMAND_RECONFIG_FLAG_PARTIAL:
 * Set to FPGA configuration type (full or partial).
 */
#घोषणा COMMAND_RECONFIG_FLAG_PARTIAL	0

/*
 * Timeout settings क्रम service clients:
 * समयout value used in Stratix10 FPGA manager driver.
 * समयout value used in RSU driver
 */
#घोषणा SVC_RECONFIG_REQUEST_TIMEOUT_MS         300
#घोषणा SVC_RECONFIG_BUFFER_TIMEOUT_MS          720
#घोषणा SVC_RSU_REQUEST_TIMEOUT_MS              300

काष्ठा stratix10_svc_chan;

/**
 * क्रमागत stratix10_svc_command_code - supported service commands
 *
 * @COMMAND_NOOP: करो 'dummy' request क्रम पूर्णांकegration/debug/trouble-shooting
 *
 * @COMMAND_RECONFIG: ask क्रम FPGA configuration preparation, वापस status
 * is SVC_STATUS_OK
 *
 * @COMMAND_RECONFIG_DATA_SUBMIT: submit buffer(s) of bit-stream data क्रम the
 * FPGA configuration, वापस status is SVC_STATUS_SUBMITTED or SVC_STATUS_ERROR
 *
 * @COMMAND_RECONFIG_DATA_CLAIM: check the status of the configuration, वापस
 * status is SVC_STATUS_COMPLETED, or SVC_STATUS_BUSY, or SVC_STATUS_ERROR
 *
 * @COMMAND_RECONFIG_STATUS: check the status of the configuration, वापस
 * status is SVC_STATUS_COMPLETED, or SVC_STATUS_BUSY, or SVC_STATUS_ERROR
 *
 * @COMMAND_RSU_STATUS: request remote प्रणाली update boot log, वापस status
 * is log data or SVC_STATUS_RSU_ERROR
 *
 * @COMMAND_RSU_UPDATE: set the offset of the bitstream to boot after reboot,
 * वापस status is SVC_STATUS_OK or SVC_STATUS_ERROR
 *
 * @COMMAND_RSU_NOTIFY: report the status of hard processor प्रणाली
 * software to firmware, वापस status is SVC_STATUS_OK or
 * SVC_STATUS_ERROR
 *
 * @COMMAND_RSU_RETRY: query firmware क्रम the current image's retry counter,
 * वापस status is SVC_STATUS_OK or SVC_STATUS_ERROR
 *
 * @COMMAND_RSU_MAX_RETRY: query firmware क्रम the max retry value,
 * वापस status is SVC_STATUS_OK or SVC_STATUS_ERROR
 *
 * @COMMAND_RSU_DCMF_VERSION: query firmware क्रम the DCMF version, वापस status
 * is SVC_STATUS_OK or SVC_STATUS_ERROR
 */
क्रमागत stratix10_svc_command_code अणु
	COMMAND_NOOP = 0,
	COMMAND_RECONFIG,
	COMMAND_RECONFIG_DATA_SUBMIT,
	COMMAND_RECONFIG_DATA_CLAIM,
	COMMAND_RECONFIG_STATUS,
	COMMAND_RSU_STATUS,
	COMMAND_RSU_UPDATE,
	COMMAND_RSU_NOTIFY,
	COMMAND_RSU_RETRY,
	COMMAND_RSU_MAX_RETRY,
	COMMAND_RSU_DCMF_VERSION,
पूर्ण;

/**
 * काष्ठा stratix10_svc_client_msg - message sent by client to service
 * @payload: starting address of data need be processed
 * @payload_length: data size in bytes
 * @command: service command
 * @arg: args to be passed via रेजिस्टरs and not physically mapped buffers
 */
काष्ठा stratix10_svc_client_msg अणु
	व्योम *payload;
	माप_प्रकार payload_length;
	क्रमागत stratix10_svc_command_code command;
	u64 arg[3];
पूर्ण;

/**
 * काष्ठा stratix10_svc_command_config_type - config type
 * @flags: flag bit क्रम the type of FPGA configuration
 */
काष्ठा stratix10_svc_command_config_type अणु
	u32 flags;
पूर्ण;

/**
 * काष्ठा stratix10_svc_cb_data - callback data काष्ठाure from service layer
 * @status: the status of sent command
 * @kaddr1: address of 1st completed data block
 * @kaddr2: address of 2nd completed data block
 * @kaddr3: address of 3rd completed data block
 */
काष्ठा stratix10_svc_cb_data अणु
	u32 status;
	व्योम *kaddr1;
	व्योम *kaddr2;
	व्योम *kaddr3;
पूर्ण;

/**
 * काष्ठा stratix10_svc_client - service client काष्ठाure
 * @dev: the client device
 * @receive_cb: callback to provide service client the received data
 * @priv: client निजी data
 */
काष्ठा stratix10_svc_client अणु
	काष्ठा device *dev;
	व्योम (*receive_cb)(काष्ठा stratix10_svc_client *client,
			   काष्ठा stratix10_svc_cb_data *cb_data);
	व्योम *priv;
पूर्ण;

/**
 * stratix10_svc_request_channel_byname() - request service channel
 * @client: identity of the client requesting the channel
 * @name: supporting client name defined above
 *
 * Return: a poपूर्णांकer to channel asचिन्हित to the client on success,
 * or ERR_PTR() on error.
 */
काष्ठा stratix10_svc_chan
*stratix10_svc_request_channel_byname(काष्ठा stratix10_svc_client *client,
	स्थिर अक्षर *name);

/**
 * stratix10_svc_मुक्त_channel() - मुक्त service channel.
 * @chan: service channel to be मुक्तd
 */
व्योम stratix10_svc_मुक्त_channel(काष्ठा stratix10_svc_chan *chan);

/**
 * stratix10_svc_allocate_memory() - allocate the momory
 * @chan: service channel asचिन्हित to the client
 * @size: number of bytes client requests
 *
 * Service layer allocates the requested number of bytes from the memory
 * pool क्रम the client.
 *
 * Return: the starting address of allocated memory on success, or
 * ERR_PTR() on error.
 */
व्योम *stratix10_svc_allocate_memory(काष्ठा stratix10_svc_chan *chan,
				    माप_प्रकार size);

/**
 * stratix10_svc_मुक्त_memory() - मुक्त allocated memory
 * @chan: service channel asचिन्हित to the client
 * @kaddr: starting address of memory to be मुक्त back to pool
 */
व्योम stratix10_svc_मुक्त_memory(काष्ठा stratix10_svc_chan *chan, व्योम *kaddr);

/**
 * stratix10_svc_send() - send a message to the remote
 * @chan: service channel asचिन्हित to the client
 * @msg: message data to be sent, in the क्रमmat of
 * काष्ठा stratix10_svc_client_msg
 *
 * Return: 0 क्रम success, -ENOMEM or -ENOBUFS on error.
 */
पूर्णांक stratix10_svc_send(काष्ठा stratix10_svc_chan *chan, व्योम *msg);

/**
 * stratix10_svc_करोne() - complete service request
 * @chan: service channel asचिन्हित to the client
 *
 * This function is used by service client to inक्रमm service layer that
 * client's service requests are completed, or there is an error in the
 * request process.
 */
व्योम stratix10_svc_करोne(काष्ठा stratix10_svc_chan *chan);
#पूर्ण_अगर

