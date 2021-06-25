<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * VFIO API definition
 *
 * Copyright (C) 2012 Red Hat, Inc.  All rights reserved.
 *     Author: Alex Williamson <alex.williamson@redhat.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#अगर_अघोषित _UAPIVFIO_H
#घोषणा _UAPIVFIO_H

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

#घोषणा VFIO_API_VERSION	0


/* Kernel & User level defines क्रम VFIO IOCTLs. */

/* Extensions */

#घोषणा VFIO_TYPE1_IOMMU		1
#घोषणा VFIO_SPAPR_TCE_IOMMU		2
#घोषणा VFIO_TYPE1v2_IOMMU		3
/*
 * IOMMU enक्रमces DMA cache coherence (ex. PCIe NoSnoop stripping).  This
 * capability is subject to change as groups are added or हटाओd.
 */
#घोषणा VFIO_DMA_CC_IOMMU		4

/* Check अगर EEH is supported */
#घोषणा VFIO_EEH			5

/* Two-stage IOMMU */
#घोषणा VFIO_TYPE1_NESTING_IOMMU	6	/* Implies v2 */

#घोषणा VFIO_SPAPR_TCE_v2_IOMMU		7

/*
 * The No-IOMMU IOMMU offers no translation or isolation क्रम devices and
 * supports no ioctls outside of VFIO_CHECK_EXTENSION.  Use of VFIO's No-IOMMU
 * code will taपूर्णांक the host kernel and should be used with extreme caution.
 */
#घोषणा VFIO_NOIOMMU_IOMMU		8

/* Supports VFIO_DMA_UNMAP_FLAG_ALL */
#घोषणा VFIO_UNMAP_ALL			9

/* Supports the vaddr flag क्रम DMA map and unmap */
#घोषणा VFIO_UPDATE_VADDR		10

/*
 * The IOCTL पूर्णांकerface is deचिन्हित क्रम extensibility by embedding the
 * काष्ठाure length (argsz) and flags पूर्णांकo काष्ठाures passed between
 * kernel and userspace.  We thereक्रमe use the _IO() macro क्रम these
 * defines to aव्योम implicitly embedding a size पूर्णांकo the ioctl request.
 * As काष्ठाure fields are added, argsz will increase to match and flag
 * bits will be defined to indicate additional fields with valid data.
 * It's *always* the caller's responsibility to indicate the size of
 * the काष्ठाure passed by setting argsz appropriately.
 */

#घोषणा VFIO_TYPE	(';')
#घोषणा VFIO_BASE	100

/*
 * For extension of INFO ioctls, VFIO makes use of a capability chain
 * deचिन्हित after PCI/e capabilities.  A flag bit indicates whether
 * this capability chain is supported and a field defined in the fixed
 * काष्ठाure defines the offset of the first capability in the chain.
 * This field is only valid when the corresponding bit in the flags
 * biपंचांगap is set.  This offset field is relative to the start of the
 * INFO buffer, as is the next field within each capability header.
 * The id within the header is a shared address space per INFO ioctl,
 * जबतक the version field is specअगरic to the capability id.  The
 * contents following the header are specअगरic to the capability id.
 */
काष्ठा vfio_info_cap_header अणु
	__u16	id;		/* Identअगरies capability */
	__u16	version;	/* Version specअगरic to the capability ID */
	__u32	next;		/* Offset of next capability */
पूर्ण;

/*
 * Callers of INFO ioctls passing insufficiently sized buffers will see
 * the capability chain flag bit set, a zero value क्रम the first capability
 * offset (अगर available within the provided argsz), and argsz will be
 * updated to report the necessary buffer size.  For compatibility, the
 * INFO ioctl will not report error in this हाल, but the capability chain
 * will not be available.
 */

/* -------- IOCTLs क्रम VFIO file descriptor (/dev/vfio/vfio) -------- */

/**
 * VFIO_GET_API_VERSION - _IO(VFIO_TYPE, VFIO_BASE + 0)
 *
 * Report the version of the VFIO API.  This allows us to bump the entire
 * API version should we later need to add or change features in incompatible
 * ways.
 * Return: VFIO_API_VERSION
 * Availability: Always
 */
#घोषणा VFIO_GET_API_VERSION		_IO(VFIO_TYPE, VFIO_BASE + 0)

/**
 * VFIO_CHECK_EXTENSION - _IOW(VFIO_TYPE, VFIO_BASE + 1, __u32)
 *
 * Check whether an extension is supported.
 * Return: 0 अगर not supported, 1 (or some other positive पूर्णांकeger) अगर supported.
 * Availability: Always
 */
#घोषणा VFIO_CHECK_EXTENSION		_IO(VFIO_TYPE, VFIO_BASE + 1)

/**
 * VFIO_SET_IOMMU - _IOW(VFIO_TYPE, VFIO_BASE + 2, __s32)
 *
 * Set the iommu to the given type.  The type must be supported by an
 * iommu driver as verअगरied by calling CHECK_EXTENSION using the same
 * type.  A group must be set to this file descriptor beक्रमe this
 * ioctl is available.  The IOMMU पूर्णांकerfaces enabled by this call are
 * specअगरic to the value set.
 * Return: 0 on success, -त्रुटि_सं on failure
 * Availability: When VFIO group attached
 */
#घोषणा VFIO_SET_IOMMU			_IO(VFIO_TYPE, VFIO_BASE + 2)

/* -------- IOCTLs क्रम GROUP file descriptors (/dev/vfio/$GROUP) -------- */

/**
 * VFIO_GROUP_GET_STATUS - _IOR(VFIO_TYPE, VFIO_BASE + 3,
 *						काष्ठा vfio_group_status)
 *
 * Retrieve inक्रमmation about the group.  Fills in provided
 * काष्ठा vfio_group_info.  Caller sets argsz.
 * Return: 0 on succes, -त्रुटि_सं on failure.
 * Availability: Always
 */
काष्ठा vfio_group_status अणु
	__u32	argsz;
	__u32	flags;
#घोषणा VFIO_GROUP_FLAGS_VIABLE		(1 << 0)
#घोषणा VFIO_GROUP_FLAGS_CONTAINER_SET	(1 << 1)
पूर्ण;
#घोषणा VFIO_GROUP_GET_STATUS		_IO(VFIO_TYPE, VFIO_BASE + 3)

/**
 * VFIO_GROUP_SET_CONTAINER - _IOW(VFIO_TYPE, VFIO_BASE + 4, __s32)
 *
 * Set the container क्रम the VFIO group to the खोलो VFIO file
 * descriptor provided.  Groups may only beदीर्घ to a single
 * container.  Containers may, at their discretion, support multiple
 * groups.  Only when a container is set are all of the पूर्णांकerfaces
 * of the VFIO file descriptor and the VFIO group file descriptor
 * available to the user.
 * Return: 0 on success, -त्रुटि_सं on failure.
 * Availability: Always
 */
#घोषणा VFIO_GROUP_SET_CONTAINER	_IO(VFIO_TYPE, VFIO_BASE + 4)

/**
 * VFIO_GROUP_UNSET_CONTAINER - _IO(VFIO_TYPE, VFIO_BASE + 5)
 *
 * Remove the group from the attached container.  This is the
 * opposite of the SET_CONTAINER call and वापसs the group to
 * an initial state.  All device file descriptors must be released
 * prior to calling this पूर्णांकerface.  When removing the last group
 * from a container, the IOMMU will be disabled and all state lost,
 * effectively also वापसing the VFIO file descriptor to an initial
 * state.
 * Return: 0 on success, -त्रुटि_सं on failure.
 * Availability: When attached to container
 */
#घोषणा VFIO_GROUP_UNSET_CONTAINER	_IO(VFIO_TYPE, VFIO_BASE + 5)

/**
 * VFIO_GROUP_GET_DEVICE_FD - _IOW(VFIO_TYPE, VFIO_BASE + 6, अक्षर)
 *
 * Return a new file descriptor क्रम the device object described by
 * the provided string.  The string should match a device listed in
 * the devices subdirectory of the IOMMU group sysfs entry.  The
 * group containing the device must alपढ़ोy be added to this context.
 * Return: new file descriptor on success, -त्रुटि_सं on failure.
 * Availability: When attached to container
 */
#घोषणा VFIO_GROUP_GET_DEVICE_FD	_IO(VFIO_TYPE, VFIO_BASE + 6)

/* --------------- IOCTLs क्रम DEVICE file descriptors --------------- */

/**
 * VFIO_DEVICE_GET_INFO - _IOR(VFIO_TYPE, VFIO_BASE + 7,
 *						काष्ठा vfio_device_info)
 *
 * Retrieve inक्रमmation about the device.  Fills in provided
 * काष्ठा vfio_device_info.  Caller sets argsz.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
काष्ठा vfio_device_info अणु
	__u32	argsz;
	__u32	flags;
#घोषणा VFIO_DEVICE_FLAGS_RESET	(1 << 0)	/* Device supports reset */
#घोषणा VFIO_DEVICE_FLAGS_PCI	(1 << 1)	/* vfio-pci device */
#घोषणा VFIO_DEVICE_FLAGS_PLATFORM (1 << 2)	/* vfio-platक्रमm device */
#घोषणा VFIO_DEVICE_FLAGS_AMBA  (1 << 3)	/* vfio-amba device */
#घोषणा VFIO_DEVICE_FLAGS_CCW	(1 << 4)	/* vfio-ccw device */
#घोषणा VFIO_DEVICE_FLAGS_AP	(1 << 5)	/* vfio-ap device */
#घोषणा VFIO_DEVICE_FLAGS_FSL_MC (1 << 6)	/* vfio-fsl-mc device */
#घोषणा VFIO_DEVICE_FLAGS_CAPS	(1 << 7)	/* Info supports caps */
	__u32	num_regions;	/* Max region index + 1 */
	__u32	num_irqs;	/* Max IRQ index + 1 */
	__u32   cap_offset;	/* Offset within info काष्ठा of first cap */
पूर्ण;
#घोषणा VFIO_DEVICE_GET_INFO		_IO(VFIO_TYPE, VFIO_BASE + 7)

/*
 * Venकरोr driver using Mediated device framework should provide device_api
 * attribute in supported type attribute groups. Device API string should be one
 * of the following corresponding to device flags in vfio_device_info काष्ठाure.
 */

#घोषणा VFIO_DEVICE_API_PCI_STRING		"vfio-pci"
#घोषणा VFIO_DEVICE_API_PLATFORM_STRING		"vfio-platform"
#घोषणा VFIO_DEVICE_API_AMBA_STRING		"vfio-amba"
#घोषणा VFIO_DEVICE_API_CCW_STRING		"vfio-ccw"
#घोषणा VFIO_DEVICE_API_AP_STRING		"vfio-ap"

/*
 * The following capabilities are unique to s390 zPCI devices.  Their contents
 * are further-defined in vfio_zdev.h
 */
#घोषणा VFIO_DEVICE_INFO_CAP_ZPCI_BASE		1
#घोषणा VFIO_DEVICE_INFO_CAP_ZPCI_GROUP		2
#घोषणा VFIO_DEVICE_INFO_CAP_ZPCI_UTIL		3
#घोषणा VFIO_DEVICE_INFO_CAP_ZPCI_PFIP		4

/**
 * VFIO_DEVICE_GET_REGION_INFO - _IOWR(VFIO_TYPE, VFIO_BASE + 8,
 *				       काष्ठा vfio_region_info)
 *
 * Retrieve inक्रमmation about a device region.  Caller provides
 * काष्ठा vfio_region_info with index value set.  Caller sets argsz.
 * Implementation of region mapping is bus driver specअगरic.  This is
 * पूर्णांकended to describe MMIO, I/O port, as well as bus specअगरic
 * regions (ex. PCI config space).  Zero sized regions may be used
 * to describe unimplemented regions (ex. unimplemented PCI BARs).
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
काष्ठा vfio_region_info अणु
	__u32	argsz;
	__u32	flags;
#घोषणा VFIO_REGION_INFO_FLAG_READ	(1 << 0) /* Region supports पढ़ो */
#घोषणा VFIO_REGION_INFO_FLAG_WRITE	(1 << 1) /* Region supports ग_लिखो */
#घोषणा VFIO_REGION_INFO_FLAG_MMAP	(1 << 2) /* Region supports mmap */
#घोषणा VFIO_REGION_INFO_FLAG_CAPS	(1 << 3) /* Info supports caps */
	__u32	index;		/* Region index */
	__u32	cap_offset;	/* Offset within info काष्ठा of first cap */
	__u64	size;		/* Region size (bytes) */
	__u64	offset;		/* Region offset from start of device fd */
पूर्ण;
#घोषणा VFIO_DEVICE_GET_REGION_INFO	_IO(VFIO_TYPE, VFIO_BASE + 8)

/*
 * The sparse mmap capability allows finer granularity of specअगरying areas
 * within a region with mmap support.  When specअगरied, the user should only
 * mmap the offset ranges specअगरied by the areas array.  mmaps outside of the
 * areas specअगरied may fail (such as the range covering a PCI MSI-X table) or
 * may result in improper device behavior.
 *
 * The काष्ठाures below define version 1 of this capability.
 */
#घोषणा VFIO_REGION_INFO_CAP_SPARSE_MMAP	1

काष्ठा vfio_region_sparse_mmap_area अणु
	__u64	offset;	/* Offset of mmap'able area within region */
	__u64	size;	/* Size of mmap'able area */
पूर्ण;

काष्ठा vfio_region_info_cap_sparse_mmap अणु
	काष्ठा vfio_info_cap_header header;
	__u32	nr_areas;
	__u32	reserved;
	काष्ठा vfio_region_sparse_mmap_area areas[];
पूर्ण;

/*
 * The device specअगरic type capability allows regions unique to a specअगरic
 * device or class of devices to be exposed.  This helps solve the problem क्रम
 * vfio bus drivers of defining which region indexes correspond to which region
 * on the device, without needing to resort to अटल indexes, as करोne by
 * vfio-pci.  For instance, अगर we were to go back in समय, we might हटाओ
 * VFIO_PCI_VGA_REGION_INDEX and let vfio-pci simply define that all indexes
 * greater than or equal to VFIO_PCI_NUM_REGIONS are device specअगरic and we'd
 * make a "VGA" device specअगरic type to describe the VGA access space.  This
 * means that non-VGA devices wouldn't need to waste this index, and thus the
 * address space associated with it due to implementation of device file
 * descriptor offsets in vfio-pci.
 *
 * The current implementation is now part of the user ABI, so we can't use this
 * क्रम VGA, but there are other upcoming use हालs, such as opregions क्रम Intel
 * IGD devices and framebuffers क्रम vGPU devices.  We missed VGA, but we'll
 * use this क्रम future additions.
 *
 * The काष्ठाure below defines version 1 of this capability.
 */
#घोषणा VFIO_REGION_INFO_CAP_TYPE	2

काष्ठा vfio_region_info_cap_type अणु
	काष्ठा vfio_info_cap_header header;
	__u32 type;	/* global per bus driver */
	__u32 subtype;	/* type specअगरic */
पूर्ण;

/*
 * List of region types, global per bus driver.
 * If you पूर्णांकroduce a new type, please add it here.
 */

/* PCI region type containing a PCI venकरोr part */
#घोषणा VFIO_REGION_TYPE_PCI_VENDOR_TYPE	(1 << 31)
#घोषणा VFIO_REGION_TYPE_PCI_VENDOR_MASK	(0xffff)
#घोषणा VFIO_REGION_TYPE_GFX                    (1)
#घोषणा VFIO_REGION_TYPE_CCW			(2)
#घोषणा VFIO_REGION_TYPE_MIGRATION              (3)

/* sub-types क्रम VFIO_REGION_TYPE_PCI_* */

/* 8086 venकरोr PCI sub-types */
#घोषणा VFIO_REGION_SUBTYPE_INTEL_IGD_OPREGION	(1)
#घोषणा VFIO_REGION_SUBTYPE_INTEL_IGD_HOST_CFG	(2)
#घोषणा VFIO_REGION_SUBTYPE_INTEL_IGD_LPC_CFG	(3)

/* 10de venकरोr PCI sub-types */
/*
 * NVIDIA GPU NVlink2 RAM is coherent RAM mapped onto the host address space.
 *
 * Deprecated, region no दीर्घer provided
 */
#घोषणा VFIO_REGION_SUBTYPE_NVIDIA_NVLINK2_RAM	(1)

/* 1014 venकरोr PCI sub-types */
/*
 * IBM NPU NVlink2 ATSD (Address Translation Shootकरोwn) रेजिस्टर of NPU
 * to करो TLB invalidation on a GPU.
 *
 * Deprecated, region no दीर्घer provided
 */
#घोषणा VFIO_REGION_SUBTYPE_IBM_NVLINK2_ATSD	(1)

/* sub-types क्रम VFIO_REGION_TYPE_GFX */
#घोषणा VFIO_REGION_SUBTYPE_GFX_EDID            (1)

/**
 * काष्ठा vfio_region_gfx_edid - EDID region layout.
 *
 * Set display link state and EDID blob.
 *
 * The EDID blob has monitor inक्रमmation such as bअक्रम, name, serial
 * number, physical size, supported video modes and more.
 *
 * This special region allows userspace (typically qemu) set a भव
 * EDID क्रम the भव monitor, which allows a flexible display
 * configuration.
 *
 * For the edid blob spec look here:
 *    https://en.wikipedia.org/wiki/Extended_Display_Identअगरication_Data
 *
 * On linux प्रणालीs you can find the EDID blob in sysfs:
 *    /sys/class/drm/$अणुcardपूर्ण/$अणुconnectorपूर्ण/edid
 *
 * You can use the edid-decode ulility (comes with xorg-x11-utils) to
 * decode the EDID blob.
 *
 * @edid_offset: location of the edid blob, relative to the
 *               start of the region (पढ़ोonly).
 * @edid_max_size: max size of the edid blob (पढ़ोonly).
 * @edid_size: actual edid size (पढ़ो/ग_लिखो).
 * @link_state: display link state (पढ़ो/ग_लिखो).
 * VFIO_DEVICE_GFX_LINK_STATE_UP: Monitor is turned on.
 * VFIO_DEVICE_GFX_LINK_STATE_DOWN: Monitor is turned off.
 * @max_xres: max display width (0 == no limitation, पढ़ोonly).
 * @max_yres: max display height (0 == no limitation, पढ़ोonly).
 *
 * EDID update protocol:
 *   (1) set link-state to करोwn.
 *   (2) update edid blob and size.
 *   (3) set link-state to up.
 */
काष्ठा vfio_region_gfx_edid अणु
	__u32 edid_offset;
	__u32 edid_max_size;
	__u32 edid_size;
	__u32 max_xres;
	__u32 max_yres;
	__u32 link_state;
#घोषणा VFIO_DEVICE_GFX_LINK_STATE_UP    1
#घोषणा VFIO_DEVICE_GFX_LINK_STATE_DOWN  2
पूर्ण;

/* sub-types क्रम VFIO_REGION_TYPE_CCW */
#घोषणा VFIO_REGION_SUBTYPE_CCW_ASYNC_CMD	(1)
#घोषणा VFIO_REGION_SUBTYPE_CCW_SCHIB		(2)
#घोषणा VFIO_REGION_SUBTYPE_CCW_CRW		(3)

/* sub-types क्रम VFIO_REGION_TYPE_MIGRATION */
#घोषणा VFIO_REGION_SUBTYPE_MIGRATION           (1)

/*
 * The काष्ठाure vfio_device_migration_info is placed at the 0th offset of
 * the VFIO_REGION_SUBTYPE_MIGRATION region to get and set VFIO device related
 * migration inक्रमmation. Field accesses from this काष्ठाure are only supported
 * at their native width and alignment. Otherwise, the result is undefined and
 * venकरोr drivers should वापस an error.
 *
 * device_state: (पढ़ो/ग_लिखो)
 *      - The user application ग_लिखोs to this field to inक्रमm the venकरोr driver
 *        about the device state to be transitioned to.
 *      - The venकरोr driver should take the necessary actions to change the
 *        device state. After successful transition to a given state, the
 *        venकरोr driver should वापस success on ग_लिखो(device_state, state)
 *        प्रणाली call. If the device state transition fails, the venकरोr driver
 *        should वापस an appropriate -त्रुटि_सं क्रम the fault condition.
 *      - On the user application side, अगर the device state transition fails,
 *	  that is, अगर ग_लिखो(device_state, state) वापसs an error, पढ़ो
 *	  device_state again to determine the current state of the device from
 *	  the venकरोr driver.
 *      - The venकरोr driver should वापस previous state of the device unless
 *        the venकरोr driver has encountered an पूर्णांकernal error, in which हाल
 *        the venकरोr driver may report the device_state VFIO_DEVICE_STATE_ERROR.
 *      - The user application must use the device reset ioctl to recover the
 *        device from VFIO_DEVICE_STATE_ERROR state. If the device is
 *        indicated to be in a valid device state by पढ़ोing device_state, the
 *        user application may attempt to transition the device to any valid
 *        state reachable from the current state or terminate itself.
 *
 *      device_state consists of 3 bits:
 *      - If bit 0 is set, it indicates the _RUNNING state. If bit 0 is clear,
 *        it indicates the _STOP state. When the device state is changed to
 *        _STOP, driver should stop the device beक्रमe ग_लिखो() वापसs.
 *      - If bit 1 is set, it indicates the _SAVING state, which means that the
 *        driver should start gathering device state inक्रमmation that will be
 *        provided to the VFIO user application to save the device's state.
 *      - If bit 2 is set, it indicates the _RESUMING state, which means that
 *        the driver should prepare to resume the device. Data provided through
 *        the migration region should be used to resume the device.
 *      Bits 3 - 31 are reserved क्रम future use. To preserve them, the user
 *      application should perक्रमm a पढ़ो-modअगरy-ग_लिखो operation on this
 *      field when modअगरying the specअगरied bits.
 *
 *  +------- _RESUMING
 *  |+------ _SAVING
 *  ||+----- _RUNNING
 *  |||
 *  000b => Device Stopped, not saving or resuming
 *  001b => Device running, which is the शेष state
 *  010b => Stop the device & save the device state, stop-and-copy state
 *  011b => Device running and save the device state, pre-copy state
 *  100b => Device stopped and the device state is resuming
 *  101b => Invalid state
 *  110b => Error state
 *  111b => Invalid state
 *
 * State transitions:
 *
 *              _RESUMING  _RUNNING    Pre-copy    Stop-and-copy   _STOP
 *                (100b)     (001b)     (011b)        (010b)       (000b)
 * 0. Running or शेष state
 *                             |
 *
 * 1. Normal Shutकरोwn (optional)
 *                             |------------------------------------->|
 *
 * 2. Save the state or suspend
 *                             |------------------------->|---------->|
 *
 * 3. Save the state during live migration
 *                             |----------->|------------>|---------->|
 *
 * 4. Resuming
 *                  |<---------|
 *
 * 5. Resumed
 *                  |--------->|
 *
 * 0. Default state of VFIO device is _RUNNING when the user application starts.
 * 1. During normal shutकरोwn of the user application, the user application may
 *    optionally change the VFIO device state from _RUNNING to _STOP. This
 *    transition is optional. The venकरोr driver must support this transition but
 *    must not require it.
 * 2. When the user application saves state or suspends the application, the
 *    device state transitions from _RUNNING to stop-and-copy and then to _STOP.
 *    On state transition from _RUNNING to stop-and-copy, driver must stop the
 *    device, save the device state and send it to the application through the
 *    migration region. The sequence to be followed क्रम such transition is given
 *    below.
 * 3. In live migration of user application, the state transitions from _RUNNING
 *    to pre-copy, to stop-and-copy, and to _STOP.
 *    On state transition from _RUNNING to pre-copy, the driver should start
 *    gathering the device state जबतक the application is still running and send
 *    the device state data to application through the migration region.
 *    On state transition from pre-copy to stop-and-copy, the driver must stop
 *    the device, save the device state and send it to the user application
 *    through the migration region.
 *    Venकरोr drivers must support the pre-copy state even क्रम implementations
 *    where no data is provided to the user beक्रमe the stop-and-copy state. The
 *    user must not be required to consume all migration data beक्रमe the device
 *    transitions to a new state, including the stop-and-copy state.
 *    The sequence to be followed क्रम above two transitions is given below.
 * 4. To start the resuming phase, the device state should be transitioned from
 *    the _RUNNING to the _RESUMING state.
 *    In the _RESUMING state, the driver should use the device state data
 *    received through the migration region to resume the device.
 * 5. After providing saved device data to the driver, the application should
 *    change the state from _RESUMING to _RUNNING.
 *
 * reserved:
 *      Reads on this field वापस zero and ग_लिखोs are ignored.
 *
 * pending_bytes: (पढ़ो only)
 *      The number of pending bytes still to be migrated from the venकरोr driver.
 *
 * data_offset: (पढ़ो only)
 *      The user application should पढ़ो data_offset field from the migration
 *      region. The user application should पढ़ो the device data from this
 *      offset within the migration region during the _SAVING state or ग_लिखो
 *      the device data during the _RESUMING state. See below क्रम details of
 *      sequence to be followed.
 *
 * data_size: (पढ़ो/ग_लिखो)
 *      The user application should पढ़ो data_size to get the size in bytes of
 *      the data copied in the migration region during the _SAVING state and
 *      ग_लिखो the size in bytes of the data copied in the migration region
 *      during the _RESUMING state.
 *
 * The क्रमmat of the migration region is as follows:
 *  ------------------------------------------------------------------
 * |vfio_device_migration_info|    data section                      |
 * |                          |     ///////////////////////////////  |
 * ------------------------------------------------------------------
 *   ^                              ^
 *  offset 0-trapped part        data_offset
 *
 * The काष्ठाure vfio_device_migration_info is always followed by the data
 * section in the region, so data_offset will always be nonzero. The offset
 * from where the data is copied is decided by the kernel driver. The data
 * section can be trapped, mmapped, or partitioned, depending on how the kernel
 * driver defines the data section. The data section partition can be defined
 * as mapped by the sparse mmap capability. If mmapped, data_offset must be
 * page aligned, whereas initial section which contains the
 * vfio_device_migration_info काष्ठाure, might not end at the offset, which is
 * page aligned. The user is not required to access through mmap regardless
 * of the capabilities of the region mmap.
 * The venकरोr driver should determine whether and how to partition the data
 * section. The venकरोr driver should वापस data_offset accordingly.
 *
 * The sequence to be followed जबतक in pre-copy state and stop-and-copy state
 * is as follows:
 * a. Read pending_bytes, indicating the start of a new iteration to get device
 *    data. Repeated पढ़ो on pending_bytes at this stage should have no side
 *    effects.
 *    If pending_bytes == 0, the user application should not iterate to get data
 *    क्रम that device.
 *    If pending_bytes > 0, perक्रमm the following steps.
 * b. Read data_offset, indicating that the venकरोr driver should make data
 *    available through the data section. The venकरोr driver should वापस this
 *    पढ़ो operation only after data is available from (region + data_offset)
 *    to (region + data_offset + data_size).
 * c. Read data_size, which is the amount of data in bytes available through
 *    the migration region.
 *    Read on data_offset and data_size should वापस the offset and size of
 *    the current buffer अगर the user application पढ़ोs data_offset and
 *    data_size more than once here.
 * d. Read data_size bytes of data from (region + data_offset) from the
 *    migration region.
 * e. Process the data.
 * f. Read pending_bytes, which indicates that the data from the previous
 *    iteration has been पढ़ो. If pending_bytes > 0, go to step b.
 *
 * The user application can transition from the _SAVING|_RUNNING
 * (pre-copy state) to the _SAVING (stop-and-copy) state regardless of the
 * number of pending bytes. The user application should iterate in _SAVING
 * (stop-and-copy) until pending_bytes is 0.
 *
 * The sequence to be followed जबतक _RESUMING device state is as follows:
 * While data क्रम this device is available, repeat the following steps:
 * a. Read data_offset from where the user application should ग_लिखो data.
 * b. Write migration data starting at the migration region + data_offset क्रम
 *    the length determined by data_size from the migration source.
 * c. Write data_size, which indicates to the venकरोr driver that data is
 *    written in the migration region. Venकरोr driver must वापस this ग_लिखो
 *    operations on consuming data. Venकरोr driver should apply the
 *    user-provided migration region data to the device resume state.
 *
 * If an error occurs during the above sequences, the venकरोr driver can वापस
 * an error code क्रम next पढ़ो() or ग_लिखो() operation, which will terminate the
 * loop. The user application should then take the next necessary action, क्रम
 * example, failing migration or terminating the user application.
 *
 * For the user application, data is opaque. The user application should ग_लिखो
 * data in the same order as the data is received and the data should be of
 * same transaction size at the source.
 */

काष्ठा vfio_device_migration_info अणु
	__u32 device_state;         /* VFIO device state */
#घोषणा VFIO_DEVICE_STATE_STOP      (0)
#घोषणा VFIO_DEVICE_STATE_RUNNING   (1 << 0)
#घोषणा VFIO_DEVICE_STATE_SAVING    (1 << 1)
#घोषणा VFIO_DEVICE_STATE_RESUMING  (1 << 2)
#घोषणा VFIO_DEVICE_STATE_MASK      (VFIO_DEVICE_STATE_RUNNING | \
				     VFIO_DEVICE_STATE_SAVING |  \
				     VFIO_DEVICE_STATE_RESUMING)

#घोषणा VFIO_DEVICE_STATE_VALID(state) \
	(state & VFIO_DEVICE_STATE_RESUMING ? \
	(state & VFIO_DEVICE_STATE_MASK) == VFIO_DEVICE_STATE_RESUMING : 1)

#घोषणा VFIO_DEVICE_STATE_IS_ERROR(state) \
	((state & VFIO_DEVICE_STATE_MASK) == (VFIO_DEVICE_STATE_SAVING | \
					      VFIO_DEVICE_STATE_RESUMING))

#घोषणा VFIO_DEVICE_STATE_SET_ERROR(state) \
	((state & ~VFIO_DEVICE_STATE_MASK) | VFIO_DEVICE_SATE_SAVING | \
					     VFIO_DEVICE_STATE_RESUMING)

	__u32 reserved;
	__u64 pending_bytes;
	__u64 data_offset;
	__u64 data_size;
पूर्ण;

/*
 * The MSIX mappable capability inक्रमms that MSIX data of a BAR can be mmapped
 * which allows direct access to non-MSIX रेजिस्टरs which happened to be within
 * the same प्रणाली page.
 *
 * Even though the userspace माला_लो direct access to the MSIX data, the existing
 * VFIO_DEVICE_SET_IRQS पूर्णांकerface must still be used क्रम MSIX configuration.
 */
#घोषणा VFIO_REGION_INFO_CAP_MSIX_MAPPABLE	3

/*
 * Capability with compressed real address (aka SSA - small प्रणाली address)
 * where GPU RAM is mapped on a प्रणाली bus. Used by a GPU क्रम DMA routing
 * and by the userspace to associate a NVLink bridge with a GPU.
 *
 * Deprecated, capability no दीर्घer provided
 */
#घोषणा VFIO_REGION_INFO_CAP_NVLINK2_SSATGT	4

काष्ठा vfio_region_info_cap_nvlink2_ssatgt अणु
	काष्ठा vfio_info_cap_header header;
	__u64 tgt;
पूर्ण;

/*
 * Capability with an NVLink link speed. The value is पढ़ो by
 * the NVlink2 bridge driver from the bridge's "ibm,nvlink-speed"
 * property in the device tree. The value is fixed in the hardware
 * and failing to provide the correct value results in the link
 * not working with no indication from the driver why.
 *
 * Deprecated, capability no दीर्घer provided
 */
#घोषणा VFIO_REGION_INFO_CAP_NVLINK2_LNKSPD	5

काष्ठा vfio_region_info_cap_nvlink2_lnkspd अणु
	काष्ठा vfio_info_cap_header header;
	__u32 link_speed;
	__u32 __pad;
पूर्ण;

/**
 * VFIO_DEVICE_GET_IRQ_INFO - _IOWR(VFIO_TYPE, VFIO_BASE + 9,
 *				    काष्ठा vfio_irq_info)
 *
 * Retrieve inक्रमmation about a device IRQ.  Caller provides
 * काष्ठा vfio_irq_info with index value set.  Caller sets argsz.
 * Implementation of IRQ mapping is bus driver specअगरic.  Indexes
 * using multiple IRQs are primarily पूर्णांकended to support MSI-like
 * पूर्णांकerrupt blocks.  Zero count irq blocks may be used to describe
 * unimplemented पूर्णांकerrupt types.
 *
 * The EVENTFD flag indicates the पूर्णांकerrupt index supports eventfd based
 * संकेतing.
 *
 * The MASKABLE flags indicates the index supports MASK and UNMASK
 * actions described below.
 *
 * AUTOMASKED indicates that after संकेतing, the पूर्णांकerrupt line is
 * स्वतःmatically masked by VFIO and the user needs to unmask the line
 * to receive new पूर्णांकerrupts.  This is primarily पूर्णांकended to distinguish
 * level triggered पूर्णांकerrupts.
 *
 * The NORESIZE flag indicates that the पूर्णांकerrupt lines within the index
 * are setup as a set and new subindexes cannot be enabled without first
 * disabling the entire index.  This is used क्रम पूर्णांकerrupts like PCI MSI
 * and MSI-X where the driver may only use a subset of the available
 * indexes, but VFIO needs to enable a specअगरic number of vectors
 * upfront.  In the हाल of MSI-X, where the user can enable MSI-X and
 * then add and unmask vectors, it's up to userspace to make the decision
 * whether to allocate the maximum supported number of vectors or tear
 * करोwn setup and incrementally increase the vectors as each is enabled.
 */
काष्ठा vfio_irq_info अणु
	__u32	argsz;
	__u32	flags;
#घोषणा VFIO_IRQ_INFO_EVENTFD		(1 << 0)
#घोषणा VFIO_IRQ_INFO_MASKABLE		(1 << 1)
#घोषणा VFIO_IRQ_INFO_AUTOMASKED	(1 << 2)
#घोषणा VFIO_IRQ_INFO_NORESIZE		(1 << 3)
	__u32	index;		/* IRQ index */
	__u32	count;		/* Number of IRQs within this index */
पूर्ण;
#घोषणा VFIO_DEVICE_GET_IRQ_INFO	_IO(VFIO_TYPE, VFIO_BASE + 9)

/**
 * VFIO_DEVICE_SET_IRQS - _IOW(VFIO_TYPE, VFIO_BASE + 10, काष्ठा vfio_irq_set)
 *
 * Set संकेतing, masking, and unmasking of पूर्णांकerrupts.  Caller provides
 * काष्ठा vfio_irq_set with all fields set.  'start' and 'count' indicate
 * the range of subindexes being specअगरied.
 *
 * The DATA flags specअगरy the type of data provided.  If DATA_NONE, the
 * operation perक्रमms the specअगरied action immediately on the specअगरied
 * पूर्णांकerrupt(s).  For example, to unmask AUTOMASKED पूर्णांकerrupt [0,0]:
 * flags = (DATA_NONE|ACTION_UNMASK), index = 0, start = 0, count = 1.
 *
 * DATA_BOOL allows sparse support क्रम the same on arrays of पूर्णांकerrupts.
 * For example, to mask पूर्णांकerrupts [0,1] and [0,3] (but not [0,2]):
 * flags = (DATA_BOOL|ACTION_MASK), index = 0, start = 1, count = 3,
 * data = अणु1,0,1पूर्ण
 *
 * DATA_EVENTFD binds the specअगरied ACTION to the provided __s32 eventfd.
 * A value of -1 can be used to either de-assign पूर्णांकerrupts अगर alपढ़ोy
 * asचिन्हित or skip un-asचिन्हित पूर्णांकerrupts.  For example, to set an eventfd
 * to be trigger क्रम पूर्णांकerrupts [0,0] and [0,2]:
 * flags = (DATA_EVENTFD|ACTION_TRIGGER), index = 0, start = 0, count = 3,
 * data = अणुfd1, -1, fd2पूर्ण
 * If index [0,1] is previously set, two count = 1 ioctls calls would be
 * required to set [0,0] and [0,2] without changing [0,1].
 *
 * Once a संकेतing mechanism is set, DATA_BOOL or DATA_NONE can be used
 * with ACTION_TRIGGER to perक्रमm kernel level पूर्णांकerrupt loopback testing
 * from userspace (ie. simulate hardware triggering).
 *
 * Setting of an event triggering mechanism to userspace क्रम ACTION_TRIGGER
 * enables the पूर्णांकerrupt index क्रम the device.  Inभागidual subindex पूर्णांकerrupts
 * can be disabled using the -1 value क्रम DATA_EVENTFD or the index can be
 * disabled as a whole with: flags = (DATA_NONE|ACTION_TRIGGER), count = 0.
 *
 * Note that ACTION_[UN]MASK specअगरy user->kernel संकेतing (irqfds) जबतक
 * ACTION_TRIGGER specअगरies kernel->user संकेतing.
 */
काष्ठा vfio_irq_set अणु
	__u32	argsz;
	__u32	flags;
#घोषणा VFIO_IRQ_SET_DATA_NONE		(1 << 0) /* Data not present */
#घोषणा VFIO_IRQ_SET_DATA_BOOL		(1 << 1) /* Data is bool (u8) */
#घोषणा VFIO_IRQ_SET_DATA_EVENTFD	(1 << 2) /* Data is eventfd (s32) */
#घोषणा VFIO_IRQ_SET_ACTION_MASK	(1 << 3) /* Mask पूर्णांकerrupt */
#घोषणा VFIO_IRQ_SET_ACTION_UNMASK	(1 << 4) /* Unmask पूर्णांकerrupt */
#घोषणा VFIO_IRQ_SET_ACTION_TRIGGER	(1 << 5) /* Trigger पूर्णांकerrupt */
	__u32	index;
	__u32	start;
	__u32	count;
	__u8	data[];
पूर्ण;
#घोषणा VFIO_DEVICE_SET_IRQS		_IO(VFIO_TYPE, VFIO_BASE + 10)

#घोषणा VFIO_IRQ_SET_DATA_TYPE_MASK	(VFIO_IRQ_SET_DATA_NONE | \
					 VFIO_IRQ_SET_DATA_BOOL | \
					 VFIO_IRQ_SET_DATA_EVENTFD)
#घोषणा VFIO_IRQ_SET_ACTION_TYPE_MASK	(VFIO_IRQ_SET_ACTION_MASK | \
					 VFIO_IRQ_SET_ACTION_UNMASK | \
					 VFIO_IRQ_SET_ACTION_TRIGGER)
/**
 * VFIO_DEVICE_RESET - _IO(VFIO_TYPE, VFIO_BASE + 11)
 *
 * Reset a device.
 */
#घोषणा VFIO_DEVICE_RESET		_IO(VFIO_TYPE, VFIO_BASE + 11)

/*
 * The VFIO-PCI bus driver makes use of the following fixed region and
 * IRQ index mapping.  Unimplemented regions वापस a size of zero.
 * Unimplemented IRQ types वापस a count of zero.
 */

क्रमागत अणु
	VFIO_PCI_BAR0_REGION_INDEX,
	VFIO_PCI_BAR1_REGION_INDEX,
	VFIO_PCI_BAR2_REGION_INDEX,
	VFIO_PCI_BAR3_REGION_INDEX,
	VFIO_PCI_BAR4_REGION_INDEX,
	VFIO_PCI_BAR5_REGION_INDEX,
	VFIO_PCI_ROM_REGION_INDEX,
	VFIO_PCI_CONFIG_REGION_INDEX,
	/*
	 * Expose VGA regions defined क्रम PCI base class 03, subclass 00.
	 * This includes I/O port ranges 0x3b0 to 0x3bb and 0x3c0 to 0x3df
	 * as well as the MMIO range 0xa0000 to 0xbffff.  Each implemented
	 * range is found at it's identity mapped offset from the region
	 * offset, क्रम example 0x3b0 is region_info.offset + 0x3b0.  Areas
	 * between described ranges are unimplemented.
	 */
	VFIO_PCI_VGA_REGION_INDEX,
	VFIO_PCI_NUM_REGIONS = 9 /* Fixed user ABI, region indexes >=9 use */
				 /* device specअगरic cap to define content. */
पूर्ण;

क्रमागत अणु
	VFIO_PCI_INTX_IRQ_INDEX,
	VFIO_PCI_MSI_IRQ_INDEX,
	VFIO_PCI_MSIX_IRQ_INDEX,
	VFIO_PCI_ERR_IRQ_INDEX,
	VFIO_PCI_REQ_IRQ_INDEX,
	VFIO_PCI_NUM_IRQS
पूर्ण;

/*
 * The vfio-ccw bus driver makes use of the following fixed region and
 * IRQ index mapping. Unimplemented regions वापस a size of zero.
 * Unimplemented IRQ types वापस a count of zero.
 */

क्रमागत अणु
	VFIO_CCW_CONFIG_REGION_INDEX,
	VFIO_CCW_NUM_REGIONS
पूर्ण;

क्रमागत अणु
	VFIO_CCW_IO_IRQ_INDEX,
	VFIO_CCW_CRW_IRQ_INDEX,
	VFIO_CCW_REQ_IRQ_INDEX,
	VFIO_CCW_NUM_IRQS
पूर्ण;

/**
 * VFIO_DEVICE_GET_PCI_HOT_RESET_INFO - _IORW(VFIO_TYPE, VFIO_BASE + 12,
 *					      काष्ठा vfio_pci_hot_reset_info)
 *
 * Return: 0 on success, -त्रुटि_सं on failure:
 *	-enospc = insufficient buffer, -enodev = unsupported क्रम device.
 */
काष्ठा vfio_pci_dependent_device अणु
	__u32	group_id;
	__u16	segment;
	__u8	bus;
	__u8	devfn; /* Use PCI_SLOT/PCI_FUNC */
पूर्ण;

काष्ठा vfio_pci_hot_reset_info अणु
	__u32	argsz;
	__u32	flags;
	__u32	count;
	काष्ठा vfio_pci_dependent_device	devices[];
पूर्ण;

#घोषणा VFIO_DEVICE_GET_PCI_HOT_RESET_INFO	_IO(VFIO_TYPE, VFIO_BASE + 12)

/**
 * VFIO_DEVICE_PCI_HOT_RESET - _IOW(VFIO_TYPE, VFIO_BASE + 13,
 *				    काष्ठा vfio_pci_hot_reset)
 *
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
काष्ठा vfio_pci_hot_reset अणु
	__u32	argsz;
	__u32	flags;
	__u32	count;
	__s32	group_fds[];
पूर्ण;

#घोषणा VFIO_DEVICE_PCI_HOT_RESET	_IO(VFIO_TYPE, VFIO_BASE + 13)

/**
 * VFIO_DEVICE_QUERY_GFX_PLANE - _IOW(VFIO_TYPE, VFIO_BASE + 14,
 *                                    काष्ठा vfio_device_query_gfx_plane)
 *
 * Set the drm_plane_type and flags, then retrieve the gfx plane info.
 *
 * flags supported:
 * - VFIO_GFX_PLANE_TYPE_PROBE and VFIO_GFX_PLANE_TYPE_DMABUF are set
 *   to ask अगर the mdev supports dma-buf. 0 on support, -EINVAL on no
 *   support क्रम dma-buf.
 * - VFIO_GFX_PLANE_TYPE_PROBE and VFIO_GFX_PLANE_TYPE_REGION are set
 *   to ask अगर the mdev supports region. 0 on support, -EINVAL on no
 *   support क्रम region.
 * - VFIO_GFX_PLANE_TYPE_DMABUF or VFIO_GFX_PLANE_TYPE_REGION is set
 *   with each call to query the plane info.
 * - Others are invalid and वापस -EINVAL.
 *
 * Note:
 * 1. Plane could be disabled by guest. In that हाल, success will be
 *    वापसed with zero-initialized drm_क्रमmat, size, width and height
 *    fields.
 * 2. x_hot/y_hot is set to 0xFFFFFFFF अगर no hotspot inक्रमmation available
 *
 * Return: 0 on success, -त्रुटि_सं on other failure.
 */
काष्ठा vfio_device_gfx_plane_info अणु
	__u32 argsz;
	__u32 flags;
#घोषणा VFIO_GFX_PLANE_TYPE_PROBE (1 << 0)
#घोषणा VFIO_GFX_PLANE_TYPE_DMABUF (1 << 1)
#घोषणा VFIO_GFX_PLANE_TYPE_REGION (1 << 2)
	/* in */
	__u32 drm_plane_type;	/* type of plane: DRM_PLANE_TYPE_* */
	/* out */
	__u32 drm_क्रमmat;	/* drm क्रमmat of plane */
	__u64 drm_क्रमmat_mod;   /* tiled mode */
	__u32 width;	/* width of plane */
	__u32 height;	/* height of plane */
	__u32 stride;	/* stride of plane */
	__u32 size;	/* size of plane in bytes, align on page*/
	__u32 x_pos;	/* horizontal position of cursor plane */
	__u32 y_pos;	/* vertical position of cursor plane*/
	__u32 x_hot;    /* horizontal position of cursor hotspot */
	__u32 y_hot;    /* vertical position of cursor hotspot */
	जोड़ अणु
		__u32 region_index;	/* region index */
		__u32 dmabuf_id;	/* dma-buf id */
	पूर्ण;
पूर्ण;

#घोषणा VFIO_DEVICE_QUERY_GFX_PLANE _IO(VFIO_TYPE, VFIO_BASE + 14)

/**
 * VFIO_DEVICE_GET_GFX_DMABUF - _IOW(VFIO_TYPE, VFIO_BASE + 15, __u32)
 *
 * Return a new dma-buf file descriptor क्रम an exposed guest framebuffer
 * described by the provided dmabuf_id. The dmabuf_id is वापसed from VFIO_
 * DEVICE_QUERY_GFX_PLANE as a token of the exposed guest framebuffer.
 */

#घोषणा VFIO_DEVICE_GET_GFX_DMABUF _IO(VFIO_TYPE, VFIO_BASE + 15)

/**
 * VFIO_DEVICE_IOEVENTFD - _IOW(VFIO_TYPE, VFIO_BASE + 16,
 *                              काष्ठा vfio_device_ioeventfd)
 *
 * Perक्रमm a ग_लिखो to the device at the specअगरied device fd offset, with
 * the specअगरied data and width when the provided eventfd is triggered.
 * vfio bus drivers may not support this क्रम all regions, क्रम all widths,
 * or at all.  vfio-pci currently only enables support क्रम BAR regions,
 * excluding the MSI-X vector table.
 *
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
काष्ठा vfio_device_ioeventfd अणु
	__u32	argsz;
	__u32	flags;
#घोषणा VFIO_DEVICE_IOEVENTFD_8		(1 << 0) /* 1-byte ग_लिखो */
#घोषणा VFIO_DEVICE_IOEVENTFD_16	(1 << 1) /* 2-byte ग_लिखो */
#घोषणा VFIO_DEVICE_IOEVENTFD_32	(1 << 2) /* 4-byte ग_लिखो */
#घोषणा VFIO_DEVICE_IOEVENTFD_64	(1 << 3) /* 8-byte ग_लिखो */
#घोषणा VFIO_DEVICE_IOEVENTFD_SIZE_MASK	(0xf)
	__u64	offset;			/* device fd offset of ग_लिखो */
	__u64	data;			/* data to be written */
	__s32	fd;			/* -1 क्रम de-assignment */
पूर्ण;

#घोषणा VFIO_DEVICE_IOEVENTFD		_IO(VFIO_TYPE, VFIO_BASE + 16)

/**
 * VFIO_DEVICE_FEATURE - _IORW(VFIO_TYPE, VFIO_BASE + 17,
 *			       काष्ठा vfio_device_feature)
 *
 * Get, set, or probe feature data of the device.  The feature is selected
 * using the FEATURE_MASK portion of the flags field.  Support क्रम a feature
 * can be probed by setting both the FEATURE_MASK and PROBE bits.  A probe
 * may optionally include the GET and/or SET bits to determine पढ़ो vs ग_लिखो
 * access of the feature respectively.  Probing a feature will वापस success
 * अगर the feature is supported and all of the optionally indicated GET/SET
 * methods are supported.  The क्रमmat of the data portion of the काष्ठाure is
 * specअगरic to the given feature.  The data portion is not required क्रम
 * probing.  GET and SET are mutually exclusive, except क्रम use with PROBE.
 *
 * Return 0 on success, -त्रुटि_सं on failure.
 */
काष्ठा vfio_device_feature अणु
	__u32	argsz;
	__u32	flags;
#घोषणा VFIO_DEVICE_FEATURE_MASK	(0xffff) /* 16-bit feature index */
#घोषणा VFIO_DEVICE_FEATURE_GET		(1 << 16) /* Get feature पूर्णांकo data[] */
#घोषणा VFIO_DEVICE_FEATURE_SET		(1 << 17) /* Set feature from data[] */
#घोषणा VFIO_DEVICE_FEATURE_PROBE	(1 << 18) /* Probe feature support */
	__u8	data[];
पूर्ण;

#घोषणा VFIO_DEVICE_FEATURE		_IO(VFIO_TYPE, VFIO_BASE + 17)

/*
 * Provide support क्रम setting a PCI VF Token, which is used as a shared
 * secret between PF and VF drivers.  This feature may only be set on a
 * PCI SR-IOV PF when SR-IOV is enabled on the PF and there are no existing
 * खोलो VFs.  Data provided when setting this feature is a 16-byte array
 * (__u8 b[16]), representing a UUID.
 */
#घोषणा VFIO_DEVICE_FEATURE_PCI_VF_TOKEN	(0)

/* -------- API क्रम Type1 VFIO IOMMU -------- */

/**
 * VFIO_IOMMU_GET_INFO - _IOR(VFIO_TYPE, VFIO_BASE + 12, काष्ठा vfio_iommu_info)
 *
 * Retrieve inक्रमmation about the IOMMU object. Fills in provided
 * काष्ठा vfio_iommu_info. Caller sets argsz.
 *
 * XXX Should we करो these by CHECK_EXTENSION too?
 */
काष्ठा vfio_iommu_type1_info अणु
	__u32	argsz;
	__u32	flags;
#घोषणा VFIO_IOMMU_INFO_PGSIZES (1 << 0)	/* supported page sizes info */
#घोषणा VFIO_IOMMU_INFO_CAPS	(1 << 1)	/* Info supports caps */
	__u64	iova_pgsizes;	/* Biपंचांगap of supported page sizes */
	__u32   cap_offset;	/* Offset within info काष्ठा of first cap */
पूर्ण;

/*
 * The IOVA capability allows to report the valid IOVA range(s)
 * excluding any non-relaxable reserved regions exposed by
 * devices attached to the container. Any DMA map attempt
 * outside the valid iova range will वापस error.
 *
 * The काष्ठाures below define version 1 of this capability.
 */
#घोषणा VFIO_IOMMU_TYPE1_INFO_CAP_IOVA_RANGE  1

काष्ठा vfio_iova_range अणु
	__u64	start;
	__u64	end;
पूर्ण;

काष्ठा vfio_iommu_type1_info_cap_iova_range अणु
	काष्ठा	vfio_info_cap_header header;
	__u32	nr_iovas;
	__u32	reserved;
	काष्ठा	vfio_iova_range iova_ranges[];
पूर्ण;

/*
 * The migration capability allows to report supported features क्रम migration.
 *
 * The काष्ठाures below define version 1 of this capability.
 *
 * The existence of this capability indicates that IOMMU kernel driver supports
 * dirty page logging.
 *
 * pgsize_biपंचांगap: Kernel driver वापसs biपंचांगap of supported page sizes क्रम dirty
 * page logging.
 * max_dirty_biपंचांगap_size: Kernel driver वापसs maximum supported dirty biपंचांगap
 * size in bytes that can be used by user applications when getting the dirty
 * biपंचांगap.
 */
#घोषणा VFIO_IOMMU_TYPE1_INFO_CAP_MIGRATION  2

काष्ठा vfio_iommu_type1_info_cap_migration अणु
	काष्ठा	vfio_info_cap_header header;
	__u32	flags;
	__u64	pgsize_biपंचांगap;
	__u64	max_dirty_biपंचांगap_size;		/* in bytes */
पूर्ण;

/*
 * The DMA available capability allows to report the current number of
 * simultaneously outstanding DMA mappings that are allowed.
 *
 * The काष्ठाure below defines version 1 of this capability.
 *
 * avail: specअगरies the current number of outstanding DMA mappings allowed.
 */
#घोषणा VFIO_IOMMU_TYPE1_INFO_DMA_AVAIL 3

काष्ठा vfio_iommu_type1_info_dma_avail अणु
	काष्ठा	vfio_info_cap_header header;
	__u32	avail;
पूर्ण;

#घोषणा VFIO_IOMMU_GET_INFO _IO(VFIO_TYPE, VFIO_BASE + 12)

/**
 * VFIO_IOMMU_MAP_DMA - _IOW(VFIO_TYPE, VFIO_BASE + 13, काष्ठा vfio_dma_map)
 *
 * Map process भव addresses to IO भव addresses using the
 * provided काष्ठा vfio_dma_map. Caller sets argsz. READ &/ WRITE required.
 *
 * If flags & VFIO_DMA_MAP_FLAG_VADDR, update the base vaddr क्रम iova, and
 * unblock translation of host भव addresses in the iova range.  The vaddr
 * must have previously been invalidated with VFIO_DMA_UNMAP_FLAG_VADDR.  To
 * मुख्यtain memory consistency within the user application, the updated vaddr
 * must address the same memory object as originally mapped.  Failure to करो so
 * will result in user memory corruption and/or device misbehavior.  iova and
 * size must match those in the original MAP_DMA call.  Protection is not
 * changed, and the READ & WRITE flags must be 0.
 */
काष्ठा vfio_iommu_type1_dma_map अणु
	__u32	argsz;
	__u32	flags;
#घोषणा VFIO_DMA_MAP_FLAG_READ (1 << 0)		/* पढ़ोable from device */
#घोषणा VFIO_DMA_MAP_FLAG_WRITE (1 << 1)	/* writable from device */
#घोषणा VFIO_DMA_MAP_FLAG_VADDR (1 << 2)
	__u64	vaddr;				/* Process भव address */
	__u64	iova;				/* IO भव address */
	__u64	size;				/* Size of mapping (bytes) */
पूर्ण;

#घोषणा VFIO_IOMMU_MAP_DMA _IO(VFIO_TYPE, VFIO_BASE + 13)

काष्ठा vfio_biपंचांगap अणु
	__u64        pgsize;	/* page size क्रम biपंचांगap in bytes */
	__u64        size;	/* in bytes */
	__u64 __user *data;	/* one bit per page */
पूर्ण;

/**
 * VFIO_IOMMU_UNMAP_DMA - _IOWR(VFIO_TYPE, VFIO_BASE + 14,
 *							काष्ठा vfio_dma_unmap)
 *
 * Unmap IO भव addresses using the provided काष्ठा vfio_dma_unmap.
 * Caller sets argsz.  The actual unmapped size is वापसed in the size
 * field.  No guarantee is made to the user that arbitrary unmaps of iova
 * or size dअगरferent from those used in the original mapping call will
 * succeed.
 *
 * VFIO_DMA_UNMAP_FLAG_GET_सूचीTY_BITMAP should be set to get the dirty biपंचांगap
 * beक्रमe unmapping IO भव addresses. When this flag is set, the user must
 * provide a काष्ठा vfio_biपंचांगap in data[]. User must provide zero-allocated
 * memory via vfio_biपंचांगap.data and its size in the vfio_biपंचांगap.size field.
 * A bit in the biपंचांगap represents one page, of user provided page size in
 * vfio_biपंचांगap.pgsize field, consecutively starting from iova offset. Bit set
 * indicates that the page at that offset from iova is dirty. A Biपंचांगap of the
 * pages in the range of unmapped size is वापसed in the user-provided
 * vfio_biपंचांगap.data.
 *
 * If flags & VFIO_DMA_UNMAP_FLAG_ALL, unmap all addresses.  iova and size
 * must be 0.  This cannot be combined with the get-dirty-biपंचांगap flag.
 *
 * If flags & VFIO_DMA_UNMAP_FLAG_VADDR, करो not unmap, but invalidate host
 * भव addresses in the iova range.  Tasks that attempt to translate an
 * iova's vaddr will block.  DMA to alपढ़ोy-mapped pages जारीs.  This
 * cannot be combined with the get-dirty-biपंचांगap flag.
 */
काष्ठा vfio_iommu_type1_dma_unmap अणु
	__u32	argsz;
	__u32	flags;
#घोषणा VFIO_DMA_UNMAP_FLAG_GET_सूचीTY_BITMAP (1 << 0)
#घोषणा VFIO_DMA_UNMAP_FLAG_ALL		     (1 << 1)
#घोषणा VFIO_DMA_UNMAP_FLAG_VADDR	     (1 << 2)
	__u64	iova;				/* IO भव address */
	__u64	size;				/* Size of mapping (bytes) */
	__u8    data[];
पूर्ण;

#घोषणा VFIO_IOMMU_UNMAP_DMA _IO(VFIO_TYPE, VFIO_BASE + 14)

/*
 * IOCTLs to enable/disable IOMMU container usage.
 * No parameters are supported.
 */
#घोषणा VFIO_IOMMU_ENABLE	_IO(VFIO_TYPE, VFIO_BASE + 15)
#घोषणा VFIO_IOMMU_DISABLE	_IO(VFIO_TYPE, VFIO_BASE + 16)

/**
 * VFIO_IOMMU_सूचीTY_PAGES - _IOWR(VFIO_TYPE, VFIO_BASE + 17,
 *                                     काष्ठा vfio_iommu_type1_dirty_biपंचांगap)
 * IOCTL is used क्रम dirty pages logging.
 * Caller should set flag depending on which operation to perक्रमm, details as
 * below:
 *
 * Calling the IOCTL with VFIO_IOMMU_सूचीTY_PAGES_FLAG_START flag set, inकाष्ठाs
 * the IOMMU driver to log pages that are dirtied or potentially dirtied by
 * the device; deचिन्हित to be used when a migration is in progress. Dirty pages
 * are logged until logging is disabled by user application by calling the IOCTL
 * with VFIO_IOMMU_सूचीTY_PAGES_FLAG_STOP flag.
 *
 * Calling the IOCTL with VFIO_IOMMU_सूचीTY_PAGES_FLAG_STOP flag set, inकाष्ठाs
 * the IOMMU driver to stop logging dirtied pages.
 *
 * Calling the IOCTL with VFIO_IOMMU_सूचीTY_PAGES_FLAG_GET_BITMAP flag set
 * वापसs the dirty pages biपंचांगap क्रम IOMMU container क्रम a given IOVA range.
 * The user must specअगरy the IOVA range and the pgsize through the काष्ठाure
 * vfio_iommu_type1_dirty_biपंचांगap_get in the data[] portion. This पूर्णांकerface
 * supports getting a biपंचांगap of the smallest supported pgsize only and can be
 * modअगरied in future to get a biपंचांगap of any specअगरied supported pgsize. The
 * user must provide a zeroed memory area क्रम the biपंचांगap memory and specअगरy its
 * size in biपंचांगap.size. One bit is used to represent one page consecutively
 * starting from iova offset. The user should provide page size in biपंचांगap.pgsize
 * field. A bit set in the biपंचांगap indicates that the page at that offset from
 * iova is dirty. The caller must set argsz to a value including the size of
 * काष्ठाure vfio_iommu_type1_dirty_biपंचांगap_get, but excluding the size of the
 * actual biपंचांगap. If dirty pages logging is not enabled, an error will be
 * वापसed.
 *
 * Only one of the flags _START, _STOP and _GET may be specअगरied at a समय.
 *
 */
काष्ठा vfio_iommu_type1_dirty_biपंचांगap अणु
	__u32        argsz;
	__u32        flags;
#घोषणा VFIO_IOMMU_सूचीTY_PAGES_FLAG_START	(1 << 0)
#घोषणा VFIO_IOMMU_सूचीTY_PAGES_FLAG_STOP	(1 << 1)
#घोषणा VFIO_IOMMU_सूचीTY_PAGES_FLAG_GET_BITMAP	(1 << 2)
	__u8         data[];
पूर्ण;

काष्ठा vfio_iommu_type1_dirty_biपंचांगap_get अणु
	__u64              iova;	/* IO भव address */
	__u64              size;	/* Size of iova range */
	काष्ठा vfio_biपंचांगap biपंचांगap;
पूर्ण;

#घोषणा VFIO_IOMMU_सूचीTY_PAGES             _IO(VFIO_TYPE, VFIO_BASE + 17)

/* -------- Additional API क्रम SPAPR TCE (Server POWERPC) IOMMU -------- */

/*
 * The SPAPR TCE DDW info काष्ठा provides the inक्रमmation about
 * the details of Dynamic DMA winकरोw capability.
 *
 * @pgsizes contains a page size biपंचांगask, 4K/64K/16M are supported.
 * @max_dynamic_winकरोws_supported tells the maximum number of winकरोws
 * which the platक्रमm can create.
 * @levels tells the maximum number of levels in multi-level IOMMU tables;
 * this allows splitting a table पूर्णांकo smaller chunks which reduces
 * the amount of physically contiguous memory required क्रम the table.
 */
काष्ठा vfio_iommu_spapr_tce_ddw_info अणु
	__u64 pgsizes;			/* Biपंचांगap of supported page sizes */
	__u32 max_dynamic_winकरोws_supported;
	__u32 levels;
पूर्ण;

/*
 * The SPAPR TCE info काष्ठा provides the inक्रमmation about the PCI bus
 * address ranges available क्रम DMA, these values are programmed पूर्णांकo
 * the hardware so the guest has to know that inक्रमmation.
 *
 * The DMA 32 bit winकरोw start is an असलolute PCI bus address.
 * The IOVA address passed via map/unmap ioctls are असलolute PCI bus
 * addresses too so the winकरोw works as a filter rather than an offset
 * क्रम IOVA addresses.
 *
 * Flags supported:
 * - VFIO_IOMMU_SPAPR_INFO_DDW: inक्रमms the userspace that dynamic DMA winकरोws
 *   (DDW) support is present. @ddw is only supported when DDW is present.
 */
काष्ठा vfio_iommu_spapr_tce_info अणु
	__u32 argsz;
	__u32 flags;
#घोषणा VFIO_IOMMU_SPAPR_INFO_DDW	(1 << 0)	/* DDW supported */
	__u32 dma32_winकरोw_start;	/* 32 bit winकरोw start (bytes) */
	__u32 dma32_winकरोw_size;	/* 32 bit winकरोw size (bytes) */
	काष्ठा vfio_iommu_spapr_tce_ddw_info ddw;
पूर्ण;

#घोषणा VFIO_IOMMU_SPAPR_TCE_GET_INFO	_IO(VFIO_TYPE, VFIO_BASE + 12)

/*
 * EEH PE operation काष्ठा provides ways to:
 * - enable/disable EEH functionality;
 * - unमुक्तze IO/DMA क्रम frozen PE;
 * - पढ़ो PE state;
 * - reset PE;
 * - configure PE;
 * - inject EEH error.
 */
काष्ठा vfio_eeh_pe_err अणु
	__u32 type;
	__u32 func;
	__u64 addr;
	__u64 mask;
पूर्ण;

काष्ठा vfio_eeh_pe_op अणु
	__u32 argsz;
	__u32 flags;
	__u32 op;
	जोड़ अणु
		काष्ठा vfio_eeh_pe_err err;
	पूर्ण;
पूर्ण;

#घोषणा VFIO_EEH_PE_DISABLE		0	/* Disable EEH functionality */
#घोषणा VFIO_EEH_PE_ENABLE		1	/* Enable EEH functionality  */
#घोषणा VFIO_EEH_PE_UNFREEZE_IO		2	/* Enable IO क्रम frozen PE   */
#घोषणा VFIO_EEH_PE_UNFREEZE_DMA	3	/* Enable DMA क्रम frozen PE  */
#घोषणा VFIO_EEH_PE_GET_STATE		4	/* PE state retrieval        */
#घोषणा  VFIO_EEH_PE_STATE_NORMAL	0	/* PE in functional state    */
#घोषणा  VFIO_EEH_PE_STATE_RESET	1	/* PE reset in progress      */
#घोषणा  VFIO_EEH_PE_STATE_STOPPED	2	/* Stopped DMA and IO        */
#घोषणा  VFIO_EEH_PE_STATE_STOPPED_DMA	4	/* Stopped DMA only          */
#घोषणा  VFIO_EEH_PE_STATE_UNAVAIL	5	/* State unavailable         */
#घोषणा VFIO_EEH_PE_RESET_DEACTIVATE	5	/* Deनिश्चित PE reset         */
#घोषणा VFIO_EEH_PE_RESET_HOT		6	/* Assert hot reset          */
#घोषणा VFIO_EEH_PE_RESET_FUNDAMENTAL	7	/* Assert fundamental reset  */
#घोषणा VFIO_EEH_PE_CONFIGURE		8	/* PE configuration          */
#घोषणा VFIO_EEH_PE_INJECT_ERR		9	/* Inject EEH error          */

#घोषणा VFIO_EEH_PE_OP			_IO(VFIO_TYPE, VFIO_BASE + 21)

/**
 * VFIO_IOMMU_SPAPR_REGISTER_MEMORY - _IOW(VFIO_TYPE, VFIO_BASE + 17, काष्ठा vfio_iommu_spapr_रेजिस्टर_memory)
 *
 * Registers user space memory where DMA is allowed. It pins
 * user pages and करोes the locked memory accounting so
 * subsequent VFIO_IOMMU_MAP_DMA/VFIO_IOMMU_UNMAP_DMA calls
 * get faster.
 */
काष्ठा vfio_iommu_spapr_रेजिस्टर_memory अणु
	__u32	argsz;
	__u32	flags;
	__u64	vaddr;				/* Process भव address */
	__u64	size;				/* Size of mapping (bytes) */
पूर्ण;
#घोषणा VFIO_IOMMU_SPAPR_REGISTER_MEMORY	_IO(VFIO_TYPE, VFIO_BASE + 17)

/**
 * VFIO_IOMMU_SPAPR_UNREGISTER_MEMORY - _IOW(VFIO_TYPE, VFIO_BASE + 18, काष्ठा vfio_iommu_spapr_रेजिस्टर_memory)
 *
 * Unरेजिस्टरs user space memory रेजिस्टरed with
 * VFIO_IOMMU_SPAPR_REGISTER_MEMORY.
 * Uses vfio_iommu_spapr_रेजिस्टर_memory क्रम parameters.
 */
#घोषणा VFIO_IOMMU_SPAPR_UNREGISTER_MEMORY	_IO(VFIO_TYPE, VFIO_BASE + 18)

/**
 * VFIO_IOMMU_SPAPR_TCE_CREATE - _IOWR(VFIO_TYPE, VFIO_BASE + 19, काष्ठा vfio_iommu_spapr_tce_create)
 *
 * Creates an additional TCE table and programs it (sets a new DMA winकरोw)
 * to every IOMMU group in the container. It receives page shअगरt, winकरोw
 * size and number of levels in the TCE table being created.
 *
 * It allocates and वापसs an offset on a PCI bus of the new DMA winकरोw.
 */
काष्ठा vfio_iommu_spapr_tce_create अणु
	__u32 argsz;
	__u32 flags;
	/* in */
	__u32 page_shअगरt;
	__u32 __resv1;
	__u64 winकरोw_size;
	__u32 levels;
	__u32 __resv2;
	/* out */
	__u64 start_addr;
पूर्ण;
#घोषणा VFIO_IOMMU_SPAPR_TCE_CREATE	_IO(VFIO_TYPE, VFIO_BASE + 19)

/**
 * VFIO_IOMMU_SPAPR_TCE_REMOVE - _IOW(VFIO_TYPE, VFIO_BASE + 20, काष्ठा vfio_iommu_spapr_tce_हटाओ)
 *
 * Unprograms a TCE table from all groups in the container and destroys it.
 * It receives a PCI bus offset as a winकरोw id.
 */
काष्ठा vfio_iommu_spapr_tce_हटाओ अणु
	__u32 argsz;
	__u32 flags;
	/* in */
	__u64 start_addr;
पूर्ण;
#घोषणा VFIO_IOMMU_SPAPR_TCE_REMOVE	_IO(VFIO_TYPE, VFIO_BASE + 20)

/* ***************************************************************** */

#पूर्ण_अगर /* _UAPIVFIO_H */
