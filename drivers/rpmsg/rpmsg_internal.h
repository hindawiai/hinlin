<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * remote processor messaging bus पूर्णांकernals
 *
 * Copyright (C) 2011 Texas Instruments, Inc.
 * Copyright (C) 2011 Google, Inc.
 *
 * Ohad Ben-Cohen <ohad@wizery.com>
 * Brian Swetland <swetland@google.com>
 */

#अगर_अघोषित __RPMSG_INTERNAL_H__
#घोषणा __RPMSG_INTERNAL_H__

#समावेश <linux/rpmsg.h>
#समावेश <linux/poll.h>

#घोषणा to_rpmsg_device(d) container_of(d, काष्ठा rpmsg_device, dev)
#घोषणा to_rpmsg_driver(d) container_of(d, काष्ठा rpmsg_driver, drv)

/**
 * काष्ठा rpmsg_device_ops - indirection table क्रम the rpmsg_device operations
 * @create_channel:	create backend-specअगरic channel, optional
 * @release_channel:	release backend-specअगरic channel, optional
 * @create_ept:		create backend-specअगरic endpoपूर्णांक, required
 * @announce_create:	announce presence of new channel, optional
 * @announce_destroy:	announce deकाष्ठाion of channel, optional
 *
 * Indirection table क्रम the operations that a rpmsg backend should implement.
 * @announce_create and @announce_destroy are optional as the backend might
 * advertise new channels implicitly by creating the endpoपूर्णांकs.
 */
काष्ठा rpmsg_device_ops अणु
	काष्ठा rpmsg_device *(*create_channel)(काष्ठा rpmsg_device *rpdev,
					       काष्ठा rpmsg_channel_info *chinfo);
	पूर्णांक (*release_channel)(काष्ठा rpmsg_device *rpdev,
			       काष्ठा rpmsg_channel_info *chinfo);
	काष्ठा rpmsg_endpoपूर्णांक *(*create_ept)(काष्ठा rpmsg_device *rpdev,
					    rpmsg_rx_cb_t cb, व्योम *priv,
					    काष्ठा rpmsg_channel_info chinfo);

	पूर्णांक (*announce_create)(काष्ठा rpmsg_device *ept);
	पूर्णांक (*announce_destroy)(काष्ठा rpmsg_device *ept);
पूर्ण;

/**
 * काष्ठा rpmsg_endpoपूर्णांक_ops - indirection table क्रम rpmsg_endpoपूर्णांक operations
 * @destroy_ept:	see @rpmsg_destroy_ept(), required
 * @send:		see @rpmsg_send(), required
 * @sendto:		see @rpmsg_sendto(), optional
 * @send_offchannel:	see @rpmsg_send_offchannel(), optional
 * @trysend:		see @rpmsg_trysend(), required
 * @trysendto:		see @rpmsg_trysendto(), optional
 * @trysend_offchannel:	see @rpmsg_trysend_offchannel(), optional
 * @poll:		see @rpmsg_poll(), optional
 *
 * Indirection table क्रम the operations that a rpmsg backend should implement.
 * In addition to @destroy_ept, the backend must at least implement @send and
 * @trysend, जबतक the variants sending data off-channel are optional.
 */
काष्ठा rpmsg_endpoपूर्णांक_ops अणु
	व्योम (*destroy_ept)(काष्ठा rpmsg_endpoपूर्णांक *ept);

	पूर्णांक (*send)(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data, पूर्णांक len);
	पूर्णांक (*sendto)(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data, पूर्णांक len, u32 dst);
	पूर्णांक (*send_offchannel)(काष्ठा rpmsg_endpoपूर्णांक *ept, u32 src, u32 dst,
				  व्योम *data, पूर्णांक len);

	पूर्णांक (*trysend)(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data, पूर्णांक len);
	पूर्णांक (*trysendto)(काष्ठा rpmsg_endpoपूर्णांक *ept, व्योम *data, पूर्णांक len, u32 dst);
	पूर्णांक (*trysend_offchannel)(काष्ठा rpmsg_endpoपूर्णांक *ept, u32 src, u32 dst,
			     व्योम *data, पूर्णांक len);
	__poll_t (*poll)(काष्ठा rpmsg_endpoपूर्णांक *ept, काष्ठा file *filp,
			     poll_table *रुको);
पूर्ण;

काष्ठा device *rpmsg_find_device(काष्ठा device *parent,
				 काष्ठा rpmsg_channel_info *chinfo);

काष्ठा rpmsg_device *rpmsg_create_channel(काष्ठा rpmsg_device *rpdev,
					  काष्ठा rpmsg_channel_info *chinfo);
पूर्णांक rpmsg_release_channel(काष्ठा rpmsg_device *rpdev,
			  काष्ठा rpmsg_channel_info *chinfo);
/**
 * rpmsg_chrdev_रेजिस्टर_device() - रेजिस्टर chrdev device based on rpdev
 * @rpdev:	prepared rpdev to be used क्रम creating endpoपूर्णांकs
 *
 * This function wraps rpmsg_रेजिस्टर_device() preparing the rpdev क्रम use as
 * basis क्रम the rpmsg chrdev.
 */
अटल अंतरभूत पूर्णांक rpmsg_chrdev_रेजिस्टर_device(काष्ठा rpmsg_device *rpdev)
अणु
	म_नकल(rpdev->id.name, "rpmsg_chrdev");
	rpdev->driver_override = "rpmsg_chrdev";

	वापस rpmsg_रेजिस्टर_device(rpdev);
पूर्ण

#पूर्ण_अगर
