<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR BSD-3-Clause) */
/*
 * Copyright(c) 2003-2015 Intel Corporation. All rights reserved.
 * Intel Management Engine Interface (Intel MEI) Linux driver
 * Intel MEI Interface Header
 */
#अगर_अघोषित _LINUX_MEI_H
#घोषणा _LINUX_MEI_H

#समावेश <linux/uuid.h>

/*
 * This IOCTL is used to associate the current file descriptor with a
 * FW Client (given by UUID). This खोलोs a communication channel
 * between a host client and a FW client. From this poपूर्णांक every पढ़ो and ग_लिखो
 * will communicate with the associated FW client.
 * Only in बंद() (file_operation release()) the communication between
 * the clients is disconnected
 *
 * The IOCTL argument is a काष्ठा with a जोड़ that contains
 * the input parameter and the output parameter क्रम this IOCTL.
 *
 * The input parameter is UUID of the FW Client.
 * The output parameter is the properties of the FW client
 * (FW protocol version and max message size).
 *
 */
#घोषणा IOCTL_MEI_CONNECT_CLIENT \
	_IOWR('H' , 0x01, काष्ठा mei_connect_client_data)

/*
 * Intel MEI client inक्रमmation काष्ठा
 */
काष्ठा mei_client अणु
	__u32 max_msg_length;
	__u8 protocol_version;
	__u8 reserved[3];
पूर्ण;

/*
 * IOCTL Connect Client Data काष्ठाure
 */
काष्ठा mei_connect_client_data अणु
	जोड़ अणु
		uuid_le in_client_uuid;
		काष्ठा mei_client out_client_properties;
	पूर्ण;
पूर्ण;

/**
 * DOC: set and unset event notअगरication क्रम a connected client
 *
 * The IOCTL argument is 1 क्रम enabling event notअगरication and 0 क्रम
 * disabling the service
 * Return:  -EOPNOTSUPP अगर the devices करोesn't support the feature
 */
#घोषणा IOCTL_MEI_NOTIFY_SET _IOW('H', 0x02, __u32)

/**
 * DOC: retrieve notअगरication
 *
 * The IOCTL output argument is 1 अगर an event was is pending and 0 otherwise
 * the ioctl has to be called in order to acknowledge pending event
 *
 * Return:  -EOPNOTSUPP अगर the devices करोesn't support the feature
 */
#घोषणा IOCTL_MEI_NOTIFY_GET _IOR('H', 0x03, __u32)

/**
 * काष्ठा mei_connect_client_vtag - mei client inक्रमmation काष्ठा with vtag
 *
 * @in_client_uuid: UUID of client to connect
 * @vtag: भव tag
 * @reserved: reserved क्रम future use
 */
काष्ठा mei_connect_client_vtag अणु
	uuid_le in_client_uuid;
	__u8 vtag;
	__u8 reserved[3];
पूर्ण;

/**
 * काष्ठा mei_connect_client_data_vtag - IOCTL connect data जोड़
 *
 * @connect: input connect data
 * @out_client_properties: output client data
 */
काष्ठा mei_connect_client_data_vtag अणु
	जोड़ अणु
		काष्ठा mei_connect_client_vtag connect;
		काष्ठा mei_client out_client_properties;
	पूर्ण;
पूर्ण;

/**
 * DOC:
 * This IOCTL is used to associate the current file descriptor with a
 * FW Client (given by UUID), and भव tag (vtag).
 * The IOCTL खोलोs a communication channel between a host client and
 * a FW client on a tagged channel. From this poपूर्णांक on, every पढ़ो
 * and ग_लिखो will communicate with the associated FW client with
 * on the tagged channel.
 * Upone बंद() the communication is terminated.
 *
 * The IOCTL argument is a काष्ठा with a जोड़ that contains
 * the input parameter and the output parameter क्रम this IOCTL.
 *
 * The input parameter is UUID of the FW Client, a vtag [0,255]
 * The output parameter is the properties of the FW client
 * (FW protocool version and max message size).
 *
 * Clients that करो not support tagged connection
 * will respond with -EOPNOTSUPP.
 */
#घोषणा IOCTL_MEI_CONNECT_CLIENT_VTAG \
	_IOWR('H', 0x04, काष्ठा mei_connect_client_data_vtag)

#पूर्ण_अगर /* _LINUX_MEI_H  */
