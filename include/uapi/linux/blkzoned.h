<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Zoned block devices handling.
 *
 * Copyright (C) 2015 Seagate Technology PLC
 *
 * Written by: Shaun Tancheff <shaun.tancheff@seagate.com>
 *
 * Modअगरied by: Damien Le Moal <damien.lemoal@hgst.com>
 * Copyright (C) 2016 Western Digital
 *
 * This file is licensed under  the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */
#अगर_अघोषित _UAPI_BLKZONED_H
#घोषणा _UAPI_BLKZONED_H

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

/**
 * क्रमागत blk_zone_type - Types of zones allowed in a zoned device.
 *
 * @BLK_ZONE_TYPE_CONVENTIONAL: The zone has no ग_लिखो poपूर्णांकer and can be ग_लिखोn
 *                              अक्रमomly. Zone reset has no effect on the zone.
 * @BLK_ZONE_TYPE_SEQWRITE_REQ: The zone must be written sequentially
 * @BLK_ZONE_TYPE_SEQWRITE_PREF: The zone can be written non-sequentially
 *
 * Any other value not defined is reserved and must be considered as invalid.
 */
क्रमागत blk_zone_type अणु
	BLK_ZONE_TYPE_CONVENTIONAL	= 0x1,
	BLK_ZONE_TYPE_SEQWRITE_REQ	= 0x2,
	BLK_ZONE_TYPE_SEQWRITE_PREF	= 0x3,
पूर्ण;

/**
 * क्रमागत blk_zone_cond - Condition [state] of a zone in a zoned device.
 *
 * @BLK_ZONE_COND_NOT_WP: The zone has no ग_लिखो poपूर्णांकer, it is conventional.
 * @BLK_ZONE_COND_EMPTY: The zone is empty.
 * @BLK_ZONE_COND_IMP_OPEN: The zone is खोलो, but not explicitly खोलोed.
 * @BLK_ZONE_COND_EXP_OPEN: The zones was explicitly खोलोed by an
 *                          OPEN ZONE command.
 * @BLK_ZONE_COND_CLOSED: The zone was [explicitly] बंदd after writing.
 * @BLK_ZONE_COND_FULL: The zone is marked as full, possibly by a zone
 *                      FINISH ZONE command.
 * @BLK_ZONE_COND_READONLY: The zone is पढ़ो-only.
 * @BLK_ZONE_COND_OFFLINE: The zone is offline (sectors cannot be पढ़ो/written).
 *
 * The Zone Condition state machine in the ZBC/ZAC standards maps the above
 * deinitions as:
 *   - ZC1: Empty         | BLK_ZONE_EMPTY
 *   - ZC2: Implicit Open | BLK_ZONE_COND_IMP_OPEN
 *   - ZC3: Explicit Open | BLK_ZONE_COND_EXP_OPEN
 *   - ZC4: Closed        | BLK_ZONE_CLOSED
 *   - ZC5: Full          | BLK_ZONE_FULL
 *   - ZC6: Read Only     | BLK_ZONE_READONLY
 *   - ZC7: Offline       | BLK_ZONE_OFFLINE
 *
 * Conditions 0x5 to 0xC are reserved by the current ZBC/ZAC spec and should
 * be considered invalid.
 */
क्रमागत blk_zone_cond अणु
	BLK_ZONE_COND_NOT_WP	= 0x0,
	BLK_ZONE_COND_EMPTY	= 0x1,
	BLK_ZONE_COND_IMP_OPEN	= 0x2,
	BLK_ZONE_COND_EXP_OPEN	= 0x3,
	BLK_ZONE_COND_CLOSED	= 0x4,
	BLK_ZONE_COND_READONLY	= 0xD,
	BLK_ZONE_COND_FULL	= 0xE,
	BLK_ZONE_COND_OFFLINE	= 0xF,
पूर्ण;

/**
 * क्रमागत blk_zone_report_flags - Feature flags of reported zone descriptors.
 *
 * @BLK_ZONE_REP_CAPACITY: Zone descriptor has capacity field.
 */
क्रमागत blk_zone_report_flags अणु
	BLK_ZONE_REP_CAPACITY	= (1 << 0),
पूर्ण;

/**
 * काष्ठा blk_zone - Zone descriptor क्रम BLKREPORTZONE ioctl.
 *
 * @start: Zone start in 512 B sector units
 * @len: Zone length in 512 B sector units
 * @wp: Zone ग_लिखो poपूर्णांकer location in 512 B sector units
 * @type: see क्रमागत blk_zone_type क्रम possible values
 * @cond: see क्रमागत blk_zone_cond क्रम possible values
 * @non_seq: Flag indicating that the zone is using non-sequential resources
 *           (क्रम host-aware zoned block devices only).
 * @reset: Flag indicating that a zone reset is recommended.
 * @resv: Padding क्रम 8B alignment.
 * @capacity: Zone usable capacity in 512 B sector units
 * @reserved: Padding to 64 B to match the ZBC, ZAC and ZNS defined zone
 *            descriptor size.
 *
 * start, len, capacity and wp use the regular 512 B sector unit, regardless
 * of the device logical block size. The overall काष्ठाure size is 64 B to
 * match the ZBC, ZAC and ZNS defined zone descriptor and allow support क्रम
 * future additional zone inक्रमmation.
 */
काष्ठा blk_zone अणु
	__u64	start;		/* Zone start sector */
	__u64	len;		/* Zone length in number of sectors */
	__u64	wp;		/* Zone ग_लिखो poपूर्णांकer position */
	__u8	type;		/* Zone type */
	__u8	cond;		/* Zone condition */
	__u8	non_seq;	/* Non-sequential ग_लिखो resources active */
	__u8	reset;		/* Reset ग_लिखो poपूर्णांकer recommended */
	__u8	resv[4];
	__u64	capacity;	/* Zone capacity in number of sectors */
	__u8	reserved[24];
पूर्ण;

/**
 * काष्ठा blk_zone_report - BLKREPORTZONE ioctl request/reply
 *
 * @sector: starting sector of report
 * @nr_zones: IN maximum / OUT actual
 * @flags: one or more flags as defined by क्रमागत blk_zone_report_flags.
 * @zones: Space to hold @nr_zones @zones entries on reply.
 *
 * The array of at most @nr_zones must follow this काष्ठाure in memory.
 */
काष्ठा blk_zone_report अणु
	__u64		sector;
	__u32		nr_zones;
	__u32		flags;
	काष्ठा blk_zone zones[0];
पूर्ण;

/**
 * काष्ठा blk_zone_range - BLKRESETZONE/BLKOPENZONE/
 *                         BLKCLOSEZONE/BLKFINISHZONE ioctl
 *                         requests
 * @sector: Starting sector of the first zone to operate on.
 * @nr_sectors: Total number of sectors of all zones to operate on.
 */
काष्ठा blk_zone_range अणु
	__u64		sector;
	__u64		nr_sectors;
पूर्ण;

/**
 * Zoned block device ioctl's:
 *
 * @BLKREPORTZONE: Get zone inक्रमmation. Takes a zone report as argument.
 *                 The zone report will start from the zone containing the
 *                 sector specअगरied in the report request काष्ठाure.
 * @BLKRESETZONE: Reset the ग_लिखो poपूर्णांकer of the zones in the specअगरied
 *                sector range. The sector range must be zone aligned.
 * @BLKGETZONESZ: Get the device zone size in number of 512 B sectors.
 * @BLKGETNRZONES: Get the total number of zones of the device.
 * @BLKOPENZONE: Open the zones in the specअगरied sector range.
 *               The 512 B sector range must be zone aligned.
 * @BLKCLOSEZONE: Close the zones in the specअगरied sector range.
 *                The 512 B sector range must be zone aligned.
 * @BLKFINISHZONE: Mark the zones as full in the specअगरied sector range.
 *                 The 512 B sector range must be zone aligned.
 */
#घोषणा BLKREPORTZONE	_IOWR(0x12, 130, काष्ठा blk_zone_report)
#घोषणा BLKRESETZONE	_IOW(0x12, 131, काष्ठा blk_zone_range)
#घोषणा BLKGETZONESZ	_IOR(0x12, 132, __u32)
#घोषणा BLKGETNRZONES	_IOR(0x12, 133, __u32)
#घोषणा BLKOPENZONE	_IOW(0x12, 134, काष्ठा blk_zone_range)
#घोषणा BLKCLOSEZONE	_IOW(0x12, 135, काष्ठा blk_zone_range)
#घोषणा BLKFINISHZONE	_IOW(0x12, 136, काष्ठा blk_zone_range)

#पूर्ण_अगर /* _UAPI_BLKZONED_H */
