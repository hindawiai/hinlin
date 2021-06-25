<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2003 Evgeniy Polyakov <zbr@ioremap.net>
 */

#अगर_अघोषित __W1_NETLINK_H
#घोषणा __W1_NETLINK_H

#समावेश <यंत्र/types.h>
#समावेश <linux/connector.h>

#समावेश "w1_internal.h"

/**
 * क्रमागत w1_cn_msg_flags - bitfield flags क्रम काष्ठा cn_msg.flags
 *
 * @W1_CN_BUNDLE: Request bundling replies पूर्णांकo fewer messagse.  Be prepared
 * to handle multiple काष्ठा cn_msg, काष्ठा w1_netlink_msg, and
 * काष्ठा w1_netlink_cmd in one packet.
 */
क्रमागत w1_cn_msg_flags अणु
	W1_CN_BUNDLE = 1,
पूर्ण;

/**
 * क्रमागत w1_netlink_message_types - message type
 *
 * @W1_SLAVE_ADD: notअगरication that a slave device was added
 * @W1_SLAVE_REMOVE: notअगरication that a slave device was हटाओd
 * @W1_MASTER_ADD: notअगरication that a new bus master was added
 * @W1_MASTER_REMOVE: notअगरication that a bus masterwas हटाओd
 * @W1_MASTER_CMD: initiate operations on a specअगरic master
 * @W1_SLAVE_CMD: sends reset, selects the slave, then करोes a पढ़ो/ग_लिखो/touch
 * operation
 * @W1_LIST_MASTERS: used to determine the bus master identअगरiers
 */
क्रमागत w1_netlink_message_types अणु
	W1_SLAVE_ADD = 0,
	W1_SLAVE_REMOVE,
	W1_MASTER_ADD,
	W1_MASTER_REMOVE,
	W1_MASTER_CMD,
	W1_SLAVE_CMD,
	W1_LIST_MASTERS,
पूर्ण;

/**
 * काष्ठा w1_netlink_msg - holds w1 message type, id, and result
 *
 * @type: one of क्रमागत w1_netlink_message_types
 * @status: kernel feedback क्रम success 0 or त्रुटि_सं failure value
 * @len: length of data following w1_netlink_msg
 * @id: जोड़ holding bus master id (msg.id) and slave device id (id[8]).
 * @id.id: Slave ID (8 bytes)
 * @id.mst: bus master identअगरication
 * @id.mst.id: bus master ID
 * @id.mst.res: bus master reserved
 * @data: start address of any following data
 *
 * The base message काष्ठाure क्रम w1 messages over netlink.
 * The netlink connector data sequence is, काष्ठा nlmsghdr, काष्ठा cn_msg,
 * then one or more काष्ठा w1_netlink_msg (each with optional data).
 */
काष्ठा w1_netlink_msg
अणु
	__u8				type;
	__u8				status;
	__u16				len;
	जोड़ अणु
		__u8			id[8];
		काष्ठा w1_mst अणु
			__u32		id;
			__u32		res;
		पूर्ण mst;
	पूर्ण id;
	__u8				data[];
पूर्ण;

/**
 * क्रमागत w1_commands - commands available क्रम master or slave operations
 *
 * @W1_CMD_READ: पढ़ो len bytes
 * @W1_CMD_WRITE: ग_लिखो len bytes
 * @W1_CMD_SEARCH: initiate a standard search, वापसs only the slave
 * devices found during that search
 * @W1_CMD_ALARM_SEARCH: search क्रम devices that are currently alarming
 * @W1_CMD_TOUCH: Touches a series of bytes.
 * @W1_CMD_RESET: sends a bus reset on the given master
 * @W1_CMD_SLAVE_ADD: adds a slave to the given master,
 * 8 byte slave id at data[0]
 * @W1_CMD_SLAVE_REMOVE: हटाओs a slave to the given master,
 * 8 byte slave id at data[0]
 * @W1_CMD_LIST_SLAVES: list of slaves रेजिस्टरed on this master
 * @W1_CMD_MAX: number of available commands
 */
क्रमागत w1_commands अणु
	W1_CMD_READ = 0,
	W1_CMD_WRITE,
	W1_CMD_SEARCH,
	W1_CMD_ALARM_SEARCH,
	W1_CMD_TOUCH,
	W1_CMD_RESET,
	W1_CMD_SLAVE_ADD,
	W1_CMD_SLAVE_REMOVE,
	W1_CMD_LIST_SLAVES,
	W1_CMD_MAX
पूर्ण;

/**
 * काष्ठा w1_netlink_cmd - holds the command and data
 *
 * @cmd: one of क्रमागत w1_commands
 * @res: reserved
 * @len: length of data following w1_netlink_cmd
 * @data: start address of any following data
 *
 * One or more काष्ठा w1_netlink_cmd is placed starting at w1_netlink_msg.data
 * each with optional data.
 */
काष्ठा w1_netlink_cmd
अणु
	__u8				cmd;
	__u8				res;
	__u16				len;
	__u8				data[];
पूर्ण;

#अगर_घोषित __KERNEL__

व्योम w1_netlink_send(काष्ठा w1_master *, काष्ठा w1_netlink_msg *);
पूर्णांक w1_init_netlink(व्योम);
व्योम w1_fini_netlink(व्योम);

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* __W1_NETLINK_H */
