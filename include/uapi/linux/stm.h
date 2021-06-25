<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * System Trace Module (STM) userspace पूर्णांकerfaces
 * Copyright (c) 2014, Intel Corporation.
 *
 * STM class implements generic infraकाष्ठाure क्रम  System Trace Module devices
 * as defined in MIPI STPv2 specअगरication.
 */

#अगर_अघोषित _UAPI_LINUX_STM_H
#घोषणा _UAPI_LINUX_STM_H

#समावेश <linux/types.h>

/* Maximum allowed master and channel values */
#घोषणा STP_MASTER_MAX	0xffff
#घोषणा STP_CHANNEL_MAX	0xffff

/**
 * काष्ठा stp_policy_id - identअगरication क्रम the STP policy
 * @size:	size of the काष्ठाure including real id[] length
 * @master:	asचिन्हित master
 * @channel:	first asचिन्हित channel
 * @width:	number of requested channels
 * @id:		identअगरication string
 *
 * User must calculate the total size of the काष्ठाure and put it पूर्णांकo
 * @size field, fill out the @id and desired @width. In वापस, kernel
 * fills out @master, @channel and @width.
 */
काष्ठा stp_policy_id अणु
	__u32		size;
	__u16		master;
	__u16		channel;
	__u16		width;
	/* padding */
	__u16		__reserved_0;
	__u32		__reserved_1;
	अक्षर		id[0];
पूर्ण;

#घोषणा STP_POLICY_ID_SET	_IOWR('%', 0, काष्ठा stp_policy_id)
#घोषणा STP_POLICY_ID_GET	_IOR('%', 1, काष्ठा stp_policy_id)
#घोषणा STP_SET_OPTIONS		_IOW('%', 2, __u64)

#पूर्ण_अगर /* _UAPI_LINUX_STM_H */
