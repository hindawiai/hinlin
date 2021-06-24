<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI__LINUX_GENERIC_NETLINK_H
#घोषणा _UAPI__LINUX_GENERIC_NETLINK_H

#समावेश <linux/types.h>
#समावेश <linux/netlink.h>

#घोषणा GENL_NAMSIZ	16	/* length of family name */

#घोषणा GENL_MIN_ID	NLMSG_MIN_TYPE
#घोषणा GENL_MAX_ID	1023

काष्ठा genlmsghdr अणु
	__u8	cmd;
	__u8	version;
	__u16	reserved;
पूर्ण;

#घोषणा GENL_HDRLEN	NLMSG_ALIGN(माप(काष्ठा genlmsghdr))

#घोषणा GENL_ADMIN_PERM		0x01
#घोषणा GENL_CMD_CAP_DO		0x02
#घोषणा GENL_CMD_CAP_DUMP	0x04
#घोषणा GENL_CMD_CAP_HASPOL	0x08
#घोषणा GENL_UNS_ADMIN_PERM	0x10

/*
 * List of reserved अटल generic netlink identअगरiers:
 */
#घोषणा GENL_ID_CTRL		NLMSG_MIN_TYPE
#घोषणा GENL_ID_VFS_DQUOT	(NLMSG_MIN_TYPE + 1)
#घोषणा GENL_ID_PMCRAID		(NLMSG_MIN_TYPE + 2)
/* must be last reserved + 1 */
#घोषणा GENL_START_ALLOC	(NLMSG_MIN_TYPE + 3)

/**************************************************************************
 * Controller
 **************************************************************************/

क्रमागत अणु
	CTRL_CMD_UNSPEC,
	CTRL_CMD_NEWFAMILY,
	CTRL_CMD_DELFAMILY,
	CTRL_CMD_GETFAMILY,
	CTRL_CMD_NEWOPS,
	CTRL_CMD_DELOPS,
	CTRL_CMD_GETOPS,
	CTRL_CMD_NEWMCAST_GRP,
	CTRL_CMD_DELMCAST_GRP,
	CTRL_CMD_GETMCAST_GRP, /* unused */
	CTRL_CMD_GETPOLICY,
	__CTRL_CMD_MAX,
पूर्ण;

#घोषणा CTRL_CMD_MAX (__CTRL_CMD_MAX - 1)

क्रमागत अणु
	CTRL_ATTR_UNSPEC,
	CTRL_ATTR_FAMILY_ID,
	CTRL_ATTR_FAMILY_NAME,
	CTRL_ATTR_VERSION,
	CTRL_ATTR_HDRSIZE,
	CTRL_ATTR_MAXATTR,
	CTRL_ATTR_OPS,
	CTRL_ATTR_MCAST_GROUPS,
	CTRL_ATTR_POLICY,
	CTRL_ATTR_OP_POLICY,
	CTRL_ATTR_OP,
	__CTRL_ATTR_MAX,
पूर्ण;

#घोषणा CTRL_ATTR_MAX (__CTRL_ATTR_MAX - 1)

क्रमागत अणु
	CTRL_ATTR_OP_UNSPEC,
	CTRL_ATTR_OP_ID,
	CTRL_ATTR_OP_FLAGS,
	__CTRL_ATTR_OP_MAX,
पूर्ण;

#घोषणा CTRL_ATTR_OP_MAX (__CTRL_ATTR_OP_MAX - 1)

क्रमागत अणु
	CTRL_ATTR_MCAST_GRP_UNSPEC,
	CTRL_ATTR_MCAST_GRP_NAME,
	CTRL_ATTR_MCAST_GRP_ID,
	__CTRL_ATTR_MCAST_GRP_MAX,
पूर्ण;

क्रमागत अणु
	CTRL_ATTR_POLICY_UNSPEC,
	CTRL_ATTR_POLICY_DO,
	CTRL_ATTR_POLICY_DUMP,

	__CTRL_ATTR_POLICY_DUMP_MAX,
	CTRL_ATTR_POLICY_DUMP_MAX = __CTRL_ATTR_POLICY_DUMP_MAX - 1
पूर्ण;

#घोषणा CTRL_ATTR_MCAST_GRP_MAX (__CTRL_ATTR_MCAST_GRP_MAX - 1)


#पूर्ण_अगर /* _UAPI__LINUX_GENERIC_NETLINK_H */
