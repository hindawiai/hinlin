<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __NETLINK_DIAG_H__
#घोषणा __NETLINK_DIAG_H__

#समावेश <linux/types.h>

काष्ठा netlink_diag_req अणु
	__u8	sdiag_family;
	__u8	sdiag_protocol;
	__u16	pad;
	__u32	ndiag_ino;
	__u32	ndiag_show;
	__u32	ndiag_cookie[2];
पूर्ण;

काष्ठा netlink_diag_msg अणु
	__u8	ndiag_family;
	__u8	ndiag_type;
	__u8	ndiag_protocol;
	__u8	ndiag_state;

	__u32	ndiag_portid;
	__u32	ndiag_dst_portid;
	__u32	ndiag_dst_group;
	__u32	ndiag_ino;
	__u32	ndiag_cookie[2];
पूर्ण;

काष्ठा netlink_diag_ring अणु
	__u32	ndr_block_size;
	__u32	ndr_block_nr;
	__u32	ndr_frame_size;
	__u32	ndr_frame_nr;
पूर्ण;

क्रमागत अणु
	/* NETLINK_DIAG_NONE, standard nl API requires this attribute!  */
	NETLINK_DIAG_MEMINFO,
	NETLINK_DIAG_GROUPS,
	NETLINK_DIAG_RX_RING,
	NETLINK_DIAG_TX_RING,
	NETLINK_DIAG_FLAGS,

	__NETLINK_DIAG_MAX,
पूर्ण;

#घोषणा NETLINK_DIAG_MAX (__NETLINK_DIAG_MAX - 1)

#घोषणा NDIAG_PROTO_ALL		((__u8) ~0)

#घोषणा NDIAG_SHOW_MEMINFO	0x00000001 /* show memory info of a socket */
#घोषणा NDIAG_SHOW_GROUPS	0x00000002 /* show groups of a netlink socket */
#अगर_अघोषित __KERNEL__
/* deprecated since 4.6 */
#घोषणा NDIAG_SHOW_RING_CFG	0x00000004 /* show ring configuration */
#पूर्ण_अगर
#घोषणा NDIAG_SHOW_FLAGS	0x00000008 /* show flags of a netlink socket */

/* flags */
#घोषणा NDIAG_FLAG_CB_RUNNING		0x00000001
#घोषणा NDIAG_FLAG_PKTINFO		0x00000002
#घोषणा NDIAG_FLAG_BROADCAST_ERROR	0x00000004
#घोषणा NDIAG_FLAG_NO_ENOBUFS		0x00000008
#घोषणा NDIAG_FLAG_LISTEN_ALL_NSID	0x00000010
#घोषणा NDIAG_FLAG_CAP_ACK		0x00000020

#पूर्ण_अगर
