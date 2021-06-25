<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* fou.h - FOU Interface */

#अगर_अघोषित _UAPI_LINUX_FOU_H
#घोषणा _UAPI_LINUX_FOU_H

/* NETLINK_GENERIC related info
 */
#घोषणा FOU_GENL_NAME		"fou"
#घोषणा FOU_GENL_VERSION	0x1

क्रमागत अणु
	FOU_ATTR_UNSPEC,
	FOU_ATTR_PORT,				/* u16 */
	FOU_ATTR_AF,				/* u8 */
	FOU_ATTR_IPPROTO,			/* u8 */
	FOU_ATTR_TYPE,				/* u8 */
	FOU_ATTR_REMCSUM_NOPARTIAL,		/* flag */
	FOU_ATTR_LOCAL_V4,			/* u32 */
	FOU_ATTR_LOCAL_V6,			/* in6_addr */
	FOU_ATTR_PEER_V4,			/* u32 */
	FOU_ATTR_PEER_V6,			/* in6_addr */
	FOU_ATTR_PEER_PORT,			/* u16 */
	FOU_ATTR_IFINDEX,			/* s32 */

	__FOU_ATTR_MAX,
पूर्ण;

#घोषणा FOU_ATTR_MAX		(__FOU_ATTR_MAX - 1)

क्रमागत अणु
	FOU_CMD_UNSPEC,
	FOU_CMD_ADD,
	FOU_CMD_DEL,
	FOU_CMD_GET,

	__FOU_CMD_MAX,
पूर्ण;

क्रमागत अणु
	FOU_ENCAP_UNSPEC,
	FOU_ENCAP_सूचीECT,
	FOU_ENCAP_GUE,
पूर्ण;

#घोषणा FOU_CMD_MAX	(__FOU_CMD_MAX - 1)

#पूर्ण_अगर /* _UAPI_LINUX_FOU_H */
