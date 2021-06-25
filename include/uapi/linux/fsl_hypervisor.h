<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0+ WITH Linux-syscall-note) OR BSD-3-Clause) */
/*
 * Freescale hypervisor ioctl and kernel पूर्णांकerface
 *
 * Copyright (C) 2008-2011 Freescale Semiconductor, Inc.
 * Author: Timur Tabi <timur@मुक्तscale.com>
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *       names of its contributors may be used to enकरोrse or promote products
 *       derived from this software without specअगरic prior written permission.
 *
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * This software is provided by Freescale Semiconductor "as is" and any
 * express or implied warranties, including, but not limited to, the implied
 * warranties of merchantability and fitness क्रम a particular purpose are
 * disclaimed. In no event shall Freescale Semiconductor be liable क्रम any
 * direct, indirect, incidental, special, exemplary, or consequential damages
 * (including, but not limited to, procurement of substitute goods or services;
 * loss of use, data, or profits; or business पूर्णांकerruption) however caused and
 * on any theory of liability, whether in contract, strict liability, or tort
 * (including negligence or otherwise) arising in any way out of the use of this
 * software, even अगर advised of the possibility of such damage.
 *
 * This file is used by the Freescale hypervisor management driver.  It can
 * also be included by applications that need to communicate with the driver
 * via the ioctl पूर्णांकerface.
 */

#अगर_अघोषित _UAPIFSL_HYPERVISOR_H
#घोषणा _UAPIFSL_HYPERVISOR_H

#समावेश <linux/types.h>

/**
 * काष्ठा fsl_hv_ioctl_restart - restart a partition
 * @ret: वापस error code from the hypervisor
 * @partition: the ID of the partition to restart, or -1 क्रम the
 *             calling partition
 *
 * Used by FSL_HV_IOCTL_PARTITION_RESTART
 */
काष्ठा fsl_hv_ioctl_restart अणु
	__u32 ret;
	__u32 partition;
पूर्ण;

/**
 * काष्ठा fsl_hv_ioctl_status - get a partition's status
 * @ret: वापस error code from the hypervisor
 * @partition: the ID of the partition to query, or -1 क्रम the
 *             calling partition
 * @status: The वापसed status of the partition
 *
 * Used by FSL_HV_IOCTL_PARTITION_GET_STATUS
 *
 * Values of 'status':
 *    0 = Stopped
 *    1 = Running
 *    2 = Starting
 *    3 = Stopping
 */
काष्ठा fsl_hv_ioctl_status अणु
	__u32 ret;
	__u32 partition;
	__u32 status;
पूर्ण;

/**
 * काष्ठा fsl_hv_ioctl_start - start a partition
 * @ret: वापस error code from the hypervisor
 * @partition: the ID of the partition to control
 * @entry_poपूर्णांक: The offset within the guest IMA to start execution
 * @load: If non-zero, reload the partition's images beक्रमe starting
 *
 * Used by FSL_HV_IOCTL_PARTITION_START
 */
काष्ठा fsl_hv_ioctl_start अणु
	__u32 ret;
	__u32 partition;
	__u32 entry_poपूर्णांक;
	__u32 load;
पूर्ण;

/**
 * काष्ठा fsl_hv_ioctl_stop - stop a partition
 * @ret: वापस error code from the hypervisor
 * @partition: the ID of the partition to stop, or -1 क्रम the calling
 *             partition
 *
 * Used by FSL_HV_IOCTL_PARTITION_STOP
 */
काष्ठा fsl_hv_ioctl_stop अणु
	__u32 ret;
	__u32 partition;
पूर्ण;

/**
 * काष्ठा fsl_hv_ioctl_स_नकल - copy memory between partitions
 * @ret: वापस error code from the hypervisor
 * @source: the partition ID of the source partition, or -1 क्रम this
 *          partition
 * @target: the partition ID of the target partition, or -1 क्रम this
 *          partition
 * @reserved: reserved, must be set to 0
 * @local_addr: user-space भव address of a buffer in the local
 *              partition
 * @remote_addr: guest physical address of a buffer in the
 *           remote partition
 * @count: the number of bytes to copy.  Both the local and remote
 *         buffers must be at least 'count' bytes दीर्घ
 *
 * Used by FSL_HV_IOCTL_MEMCPY
 *
 * The 'local' partition is the partition that calls this ioctl.  The
 * 'remote' partition is a dअगरferent partition.  The data is copied from
 * the 'source' paritition' to the 'target' partition.
 *
 * The buffer in the remote partition must be guest physically
 * contiguous.
 *
 * This ioctl करोes not support copying memory between two remote
 * partitions or within the same partition, so either 'source' or
 * 'target' (but not both) must be -1.  In other words, either
 *
 *      source == local and target == remote
 * or
 *      source == remote and target == local
 */
काष्ठा fsl_hv_ioctl_स_नकल अणु
	__u32 ret;
	__u32 source;
	__u32 target;
	__u32 reserved;	/* padding to ensure local_vaddr is aligned */
	__u64 local_vaddr;
	__u64 remote_paddr;
	__u64 count;
पूर्ण;

/**
 * काष्ठा fsl_hv_ioctl_करोorbell - ring a करोorbell
 * @ret: वापस error code from the hypervisor
 * @करोorbell: the handle of the करोorbell to ring करोorbell
 *
 * Used by FSL_HV_IOCTL_DOORBELL
 */
काष्ठा fsl_hv_ioctl_करोorbell अणु
	__u32 ret;
	__u32 करोorbell;
पूर्ण;

/**
 * काष्ठा fsl_hv_ioctl_prop - get/set a device tree property
 * @ret: वापस error code from the hypervisor
 * @handle: handle of partition whose tree to access
 * @path: भव address of path name of node to access
 * @propname: भव address of name of property to access
 * @propval: भव address of property data buffer
 * @proplen: Size of property data buffer
 * @reserved: reserved, must be set to 0
 *
 * Used by FSL_HV_IOCTL_DOORBELL
 */
काष्ठा fsl_hv_ioctl_prop अणु
	__u32 ret;
	__u32 handle;
	__u64 path;
	__u64 propname;
	__u64 propval;
	__u32 proplen;
	__u32 reserved;	/* padding to ensure काष्ठाure is aligned */
पूर्ण;

/* The ioctl type, करोcumented in ioctl-number.txt */
#घोषणा FSL_HV_IOCTL_TYPE	0xAF

/* Restart another partition */
#घोषणा FSL_HV_IOCTL_PARTITION_RESTART \
	_IOWR(FSL_HV_IOCTL_TYPE, 1, काष्ठा fsl_hv_ioctl_restart)

/* Get a partition's status */
#घोषणा FSL_HV_IOCTL_PARTITION_GET_STATUS \
	_IOWR(FSL_HV_IOCTL_TYPE, 2, काष्ठा fsl_hv_ioctl_status)

/* Boot another partition */
#घोषणा FSL_HV_IOCTL_PARTITION_START \
	_IOWR(FSL_HV_IOCTL_TYPE, 3, काष्ठा fsl_hv_ioctl_start)

/* Stop this or another partition */
#घोषणा FSL_HV_IOCTL_PARTITION_STOP \
	_IOWR(FSL_HV_IOCTL_TYPE, 4, काष्ठा fsl_hv_ioctl_stop)

/* Copy data from one partition to another */
#घोषणा FSL_HV_IOCTL_MEMCPY \
	_IOWR(FSL_HV_IOCTL_TYPE, 5, काष्ठा fsl_hv_ioctl_स_नकल)

/* Ring a करोorbell */
#घोषणा FSL_HV_IOCTL_DOORBELL \
	_IOWR(FSL_HV_IOCTL_TYPE, 6, काष्ठा fsl_hv_ioctl_करोorbell)

/* Get a property from another guest's device tree */
#घोषणा FSL_HV_IOCTL_GETPROP \
	_IOWR(FSL_HV_IOCTL_TYPE, 7, काष्ठा fsl_hv_ioctl_prop)

/* Set a property in another guest's device tree */
#घोषणा FSL_HV_IOCTL_SETPROP \
	_IOWR(FSL_HV_IOCTL_TYPE, 8, काष्ठा fsl_hv_ioctl_prop)


#पूर्ण_अगर /* _UAPIFSL_HYPERVISOR_H */
