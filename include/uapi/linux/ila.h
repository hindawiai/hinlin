<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* ila.h - ILA Interface */

#अगर_अघोषित _UAPI_LINUX_ILA_H
#घोषणा _UAPI_LINUX_ILA_H

/* NETLINK_GENERIC related info */
#घोषणा ILA_GENL_NAME		"ila"
#घोषणा ILA_GENL_VERSION	0x1

क्रमागत अणु
	ILA_ATTR_UNSPEC,
	ILA_ATTR_LOCATOR,			/* u64 */
	ILA_ATTR_IDENTIFIER,			/* u64 */
	ILA_ATTR_LOCATOR_MATCH,			/* u64 */
	ILA_ATTR_IFINDEX,			/* s32 */
	ILA_ATTR_सूची,				/* u32 */
	ILA_ATTR_PAD,
	ILA_ATTR_CSUM_MODE,			/* u8 */
	ILA_ATTR_IDENT_TYPE,			/* u8 */
	ILA_ATTR_HOOK_TYPE,			/* u8 */

	__ILA_ATTR_MAX,
पूर्ण;

#घोषणा ILA_ATTR_MAX		(__ILA_ATTR_MAX - 1)

क्रमागत अणु
	ILA_CMD_UNSPEC,
	ILA_CMD_ADD,
	ILA_CMD_DEL,
	ILA_CMD_GET,
	ILA_CMD_FLUSH,

	__ILA_CMD_MAX,
पूर्ण;

#घोषणा ILA_CMD_MAX	(__ILA_CMD_MAX - 1)

#घोषणा ILA_सूची_IN	(1 << 0)
#घोषणा ILA_सूची_OUT	(1 << 1)

क्रमागत अणु
	ILA_CSUM_ADJUST_TRANSPORT,
	ILA_CSUM_NEUTRAL_MAP,
	ILA_CSUM_NO_ACTION,
	ILA_CSUM_NEUTRAL_MAP_AUTO,
पूर्ण;

क्रमागत अणु
	ILA_ATYPE_IID = 0,
	ILA_ATYPE_LUID,
	ILA_ATYPE_VIRT_V4,
	ILA_ATYPE_VIRT_UNI_V6,
	ILA_ATYPE_VIRT_MULTI_V6,
	ILA_ATYPE_NONLOCAL_ADDR,
	ILA_ATYPE_RSVD_1,
	ILA_ATYPE_RSVD_2,

	ILA_ATYPE_USE_FORMAT = 32, /* Get type from type field in identअगरier */
पूर्ण;

क्रमागत अणु
	ILA_HOOK_ROUTE_OUTPUT,
	ILA_HOOK_ROUTE_INPUT,
पूर्ण;

#पूर्ण_अगर /* _UAPI_LINUX_ILA_H */
