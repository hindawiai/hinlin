<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2019, Mellanox Technologies. All rights reserved.
 */

#अगर_अघोषित __MLXBF_BOOTCTL_H__
#घोषणा __MLXBF_BOOTCTL_H__

/*
 * Request that the on-chip watchकरोg be enabled, or disabled, after
 * the next chip soft reset. This call करोes not affect the current
 * status of the on-chip watchकरोg. If non-zero, the argument
 * specअगरies the watchकरोg पूर्णांकerval in seconds. If zero, the watchकरोg
 * will not be enabled after the next soft reset. Non-zero errors are
 * वापसed as करोcumented below.
 */
#घोषणा MLXBF_BOOTCTL_SET_POST_RESET_WDOG	0x82000000

/*
 * Query the status which has been requested क्रम the on-chip watchकरोg
 * after the next chip soft reset. Returns the पूर्णांकerval as set by
 * MLXBF_BOOTCTL_SET_POST_RESET_WDOG.
 */
#घोषणा MLXBF_BOOTCTL_GET_POST_RESET_WDOG	0x82000001

/*
 * Request that a specअगरic boot action be taken at the next soft
 * reset. By शेष, the boot action is set by बाह्यal chip pins,
 * which are sampled on hard reset. Note that the boot action
 * requested by this call will persist on subsequent resets unless
 * this service, or the MLNX_SET_SECOND_RESET_ACTION service, is
 * invoked. See below क्रम the available MLNX_BOOT_xxx parameter
 * values. Non-zero errors are वापसed as करोcumented below.
 */
#घोषणा MLXBF_BOOTCTL_SET_RESET_ACTION		0x82000002

/*
 * Return the specअगरic boot action which will be taken at the next
 * soft reset. Returns the reset action (see below क्रम the parameter
 * values क्रम MLXBF_BOOTCTL_SET_RESET_ACTION).
 */
#घोषणा MLXBF_BOOTCTL_GET_RESET_ACTION		0x82000003

/*
 * Request that a specअगरic boot action be taken at the soft reset
 * after the next soft reset. For a specअगरied valid boot mode, the
 * effect of this call is identical to that of invoking
 * MLXBF_BOOTCTL_SET_RESET_ACTION after the next chip soft reset; in
 * particular, after that reset, the action क्रम the now next reset can
 * be queried with MLXBF_BOOTCTL_GET_RESET_ACTION and modअगरied with
 * MLXBF_BOOTCTL_SET_RESET_ACTION. You may also specअगरy the parameter as
 * MLNX_BOOT_NONE, which is equivalent to specअगरying that no call to
 * MLXBF_BOOTCTL_SET_RESET_ACTION be taken after the next chip soft reset.
 * This call करोes not affect the action to be taken at the next soft
 * reset. Non-zero errors are वापसed as करोcumented below.
 */
#घोषणा MLXBF_BOOTCTL_SET_SECOND_RESET_ACTION	0x82000004

/*
 * Return the specअगरic boot action which will be taken at the soft
 * reset after the next soft reset; this will be one of the valid
 * actions क्रम MLXBF_BOOTCTL_SET_SECOND_RESET_ACTION.
 */
#घोषणा MLXBF_BOOTCTL_GET_SECOND_RESET_ACTION	0x82000005

/*
 * Return the fuse status of the current chip. The caller should specअगरy
 * with the second argument अगर the state of the lअगरecycle fuses or the
 * version of secure boot fuse keys left should be वापसed.
 */
#घोषणा MLXBF_BOOTCTL_GET_TBB_FUSE_STATUS	0x82000006

/* Reset eMMC by programming the RST_N रेजिस्टर. */
#घोषणा MLXBF_BOOTCTL_SET_EMMC_RST_N		0x82000007

#घोषणा MLXBF_BOOTCTL_GET_DIMM_INFO		0x82000008

/* SMC function IDs क्रम SiP Service queries */
#घोषणा MLXBF_BOOTCTL_SIP_SVC_CALL_COUNT	0x8200ff00
#घोषणा MLXBF_BOOTCTL_SIP_SVC_UID		0x8200ff01
#घोषणा MLXBF_BOOTCTL_SIP_SVC_VERSION		0x8200ff03

/* ARM Standard Service Calls version numbers */
#घोषणा MLXBF_BOOTCTL_SVC_VERSION_MAJOR		0x0
#घोषणा MLXBF_BOOTCTL_SVC_VERSION_MINOR		0x2

/* Number of svc calls defined. */
#घोषणा MLXBF_BOOTCTL_NUM_SVC_CALLS 12

/* Valid reset actions क्रम MLXBF_BOOTCTL_SET_RESET_ACTION. */
#घोषणा MLXBF_BOOTCTL_EXTERNAL	0 /* Not boot from eMMC */
#घोषणा MLXBF_BOOTCTL_EMMC	1 /* From primary eMMC boot partition */
#घोषणा MLNX_BOOTCTL_SWAP_EMMC	2 /* Swap eMMC boot partitions and reboot */
#घोषणा MLXBF_BOOTCTL_EMMC_LEGACY	3 /* From primary eMMC in legacy mode */

/* Valid arguments क्रम requesting the fuse status. */
#घोषणा MLXBF_BOOTCTL_FUSE_STATUS_LIFECYCLE	0 /* Return lअगरecycle status. */
#घोषणा MLXBF_BOOTCTL_FUSE_STATUS_KEYS	1 /* Return secure boot key status */

/* Additional value to disable the MLXBF_BOOTCTL_SET_SECOND_RESET_ACTION. */
#घोषणा MLXBF_BOOTCTL_NONE	0x7fffffff /* Don't change next boot action */

#पूर्ण_अगर /* __MLXBF_BOOTCTL_H__ */
