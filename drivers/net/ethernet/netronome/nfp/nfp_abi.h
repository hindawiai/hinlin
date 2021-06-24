<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright (C) 2018 Netronome Systems, Inc. */

#अगर_अघोषित __NFP_ABI__
#घोषणा __NFP_ABI__ 1

#समावेश <linux/types.h>

#घोषणा NFP_MBOX_SYM_NAME		"_abi_nfd_pf%u_mbox"
#घोषणा NFP_MBOX_SYM_MIN_SIZE		16 /* When no data needed */

#घोषणा NFP_MBOX_CMD		0x00
#घोषणा NFP_MBOX_RET		0x04
#घोषणा NFP_MBOX_DATA_LEN	0x08
#घोषणा NFP_MBOX_RESERVED	0x0c
#घोषणा NFP_MBOX_DATA		0x10

/**
 * क्रमागत nfp_mbox_cmd - PF mailbox commands
 *
 * @NFP_MBOX_NO_CMD:	null command
 * Used to indicate previous command has finished.
 *
 * @NFP_MBOX_POOL_GET:	get shared buffer pool info/config
 * Input  - काष्ठा nfp_shared_buf_pool_id
 * Output - काष्ठा nfp_shared_buf_pool_info_get
 *
 * @NFP_MBOX_POOL_SET:	set shared buffer pool info/config
 * Input  - काष्ठा nfp_shared_buf_pool_info_set
 * Output - None
 *
 * @NFP_MBOX_PCIE_ABM_ENABLE:	enable PCIe-side advanced buffer management
 * Enable advanced buffer management of the PCIe block.  If ABM is disabled
 * PCIe block मुख्यtains a very लघु queue of buffers and करोes tail drop.
 * ABM allows more advanced buffering and priority control.
 * Input  - None
 * Output - None
 *
 * @NFP_MBOX_PCIE_ABM_DISABLE:	disable PCIe-side advanced buffer management
 * Input  - None
 * Output - None
 */
क्रमागत nfp_mbox_cmd अणु
	NFP_MBOX_NO_CMD			= 0x00,

	NFP_MBOX_POOL_GET		= 0x01,
	NFP_MBOX_POOL_SET		= 0x02,

	NFP_MBOX_PCIE_ABM_ENABLE	= 0x03,
	NFP_MBOX_PCIE_ABM_DISABLE	= 0x04,
पूर्ण;

#घोषणा NFP_SHARED_BUF_COUNT_SYM_NAME	"_abi_nfd_pf%u_sb_cnt"
#घोषणा NFP_SHARED_BUF_TABLE_SYM_NAME	"_abi_nfd_pf%u_sb_tbl"

/**
 * काष्ठा nfp_shared_buf - NFP shared buffer description
 * @id:				numerical user-visible id of the shared buffer
 * @size:			size in bytes of the buffer
 * @ingress_pools_count:	number of ingress pools
 * @egress_pools_count:		number of egress pools
 * @ingress_tc_count:		number of ingress trafic classes
 * @egress_tc_count:		number of egress trafic classes
 * @pool_size_unit:		pool size may be in credits, each credit is
 *				@pool_size_unit bytes
 */
काष्ठा nfp_shared_buf अणु
	__le32 id;
	__le32 size;
	__le16 ingress_pools_count;
	__le16 egress_pools_count;
	__le16 ingress_tc_count;
	__le16 egress_tc_count;

	__le32 pool_size_unit;
पूर्ण;

/**
 * काष्ठा nfp_shared_buf_pool_id - shared buffer pool identअगरication
 * @shared_buf:		shared buffer id
 * @pool:		pool index
 */
काष्ठा nfp_shared_buf_pool_id अणु
	__le32 shared_buf;
	__le32 pool;
पूर्ण;

/**
 * काष्ठा nfp_shared_buf_pool_info_get - काष्ठा devlink_sb_pool_info mirror
 * @pool_type:		one of क्रमागत devlink_sb_pool_type
 * @size:		pool size in units of SB's @pool_size_unit
 * @threshold_type:	one of क्रमागत devlink_sb_threshold_type
 */
काष्ठा nfp_shared_buf_pool_info_get अणु
	__le32 pool_type;
	__le32 size;
	__le32 threshold_type;
पूर्ण;

/**
 * काष्ठा nfp_shared_buf_pool_info_set - packed args of sb_pool_set
 * @id:			pool identअगरication info
 * @size:		pool size in units of SB's @pool_size_unit
 * @threshold_type:	one of क्रमागत devlink_sb_threshold_type
 */
काष्ठा nfp_shared_buf_pool_info_set अणु
	काष्ठा nfp_shared_buf_pool_id id;
	__le32 size;
	__le32 threshold_type;
पूर्ण;

#पूर्ण_अगर
