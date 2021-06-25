<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.0+ WITH Linux-syscall-note */
/*
 * userio: भव serio device support
 * Copyright (C) 2015 Red Hat
 * Copyright (C) 2015 Lyude (Stephen Chandler Paul) <cpaul@redhat.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License क्रम more
 * details.
 *
 * This is the खुला header used क्रम user-space communication with the userio
 * driver. __attribute__((__packed__)) is used क्रम all काष्ठाs to keep ABI
 * compatibility between all architectures.
 */

#अगर_अघोषित _USERIO_H
#घोषणा _USERIO_H

#समावेश <linux/types.h>

क्रमागत userio_cmd_type अणु
	USERIO_CMD_REGISTER = 0,
	USERIO_CMD_SET_PORT_TYPE = 1,
	USERIO_CMD_SEND_INTERRUPT = 2
पूर्ण;

/*
 * userio Commands
 * All commands sent to /dev/userio are encoded using this काष्ठाure. The type
 * field should contain a USERIO_CMD* value that indicates what kind of command
 * is being sent to userio. The data field should contain the accompanying
 * argument क्रम the command, अगर there is one.
 */
काष्ठा userio_cmd अणु
	__u8 type;
	__u8 data;
पूर्ण __attribute__((__packed__));

#पूर्ण_अगर /* !_USERIO_H */
