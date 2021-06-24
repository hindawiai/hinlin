<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित DRBD_GENL_STRUCT_H
#घोषणा DRBD_GENL_STRUCT_H

/**
 * काष्ठा drbd_genlmsghdr - DRBD specअगरic header used in NETLINK_GENERIC requests
 * @minor:
 *     For admin requests (user -> kernel): which minor device to operate on.
 *     For (unicast) replies or inक्रमmational (broadcast) messages
 *     (kernel -> user): which minor device the inक्रमmation is about.
 *     If we करो not operate on minors, but on connections or resources,
 *     the minor value shall be (~0), and the attribute DRBD_NLA_CFG_CONTEXT
 *     is used instead.
 * @flags: possible operation modअगरiers (relevant only क्रम user->kernel):
 *     DRBD_GENL_F_SET_DEFAULTS
 * @volume:
 *     When creating a new minor (adding it to a resource), the resource needs
 *     to know which volume number within the resource this is supposed to be.
 *     The volume number corresponds to the same volume number on the remote side,
 *     whereas the minor number on the remote side may be dअगरferent
 *     (जोड़ with flags).
 * @ret_code: kernel->userland unicast cfg reply वापस code (जोड़ with flags);
 */
काष्ठा drbd_genlmsghdr अणु
	__u32 minor;
	जोड़ अणु
	__u32 flags;
	__s32 ret_code;
	पूर्ण;
पूर्ण;

/* To be used in drbd_genlmsghdr.flags */
क्रमागत अणु
	DRBD_GENL_F_SET_DEFAULTS = 1,
पूर्ण;

क्रमागत drbd_state_info_bcast_reason अणु
	SIB_GET_STATUS_REPLY = 1,
	SIB_STATE_CHANGE = 2,
	SIB_HELPER_PRE = 3,
	SIB_HELPER_POST = 4,
	SIB_SYNC_PROGRESS = 5,
पूर्ण;

/* hack around predefined gcc/cpp "linux=1",
 * we cannot possibly include <1/drbd_genl.h> */
#अघोषित linux

#समावेश <linux/drbd.h>
#घोषणा GENL_MAGIC_VERSION	API_VERSION
#घोषणा GENL_MAGIC_FAMILY	drbd
#घोषणा GENL_MAGIC_FAMILY_HDRSZ	माप(काष्ठा drbd_genlmsghdr)
#घोषणा GENL_MAGIC_INCLUDE_खाता <linux/drbd_genl.h>
#समावेश <linux/genl_magic_काष्ठा.h>

#पूर्ण_अगर
