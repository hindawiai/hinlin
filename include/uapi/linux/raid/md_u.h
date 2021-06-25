<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
   md_u.h : user <=> kernel API between Linux raidtools and RAID drivers
          Copyright (C) 1998 Ingo Molnar
	  
   This program is मुक्त software; you can redistribute it and/or modअगरy
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.
   
   You should have received a copy of the GNU General Public License
   (क्रम example /usr/src/linux/COPYING); अगर not, ग_लिखो to the Free
   Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  
*/

#अगर_अघोषित _UAPI_MD_U_H
#घोषणा _UAPI_MD_U_H

/*
 * Dअगरferent major versions are not compatible.
 * Dअगरferent minor versions are only करोwnward compatible.
 * Dअगरferent patchlevel versions are करोwnward and upward compatible.
 */
#घोषणा MD_MAJOR_VERSION                0
#घोषणा MD_MINOR_VERSION                90
/*
 * MD_PATCHLEVEL_VERSION indicates kernel functionality.
 * >=1 means dअगरferent superblock क्रमmats are selectable using SET_ARRAY_INFO
 *     and major_version/minor_version accordingly
 * >=2 means that Internal biपंचांगaps are supported by setting MD_SB_BITMAP_PRESENT
 *     in the super status byte
 * >=3 means that biपंचांगap superblock version 4 is supported, which uses
 *     little-ending representation rather than host-endian
 */
#घोषणा MD_PATCHLEVEL_VERSION           3

/* ioctls */

/* status */
#घोषणा RAID_VERSION		_IOR (MD_MAJOR, 0x10, mdu_version_t)
#घोषणा GET_ARRAY_INFO		_IOR (MD_MAJOR, 0x11, mdu_array_info_t)
#घोषणा GET_DISK_INFO		_IOR (MD_MAJOR, 0x12, mdu_disk_info_t)
#घोषणा RAID_AUTORUN		_IO (MD_MAJOR, 0x14)
#घोषणा GET_BITMAP_खाता		_IOR (MD_MAJOR, 0x15, mdu_biपंचांगap_file_t)

/* configuration */
#घोषणा CLEAR_ARRAY		_IO (MD_MAJOR, 0x20)
#घोषणा ADD_NEW_DISK		_IOW (MD_MAJOR, 0x21, mdu_disk_info_t)
#घोषणा HOT_REMOVE_DISK		_IO (MD_MAJOR, 0x22)
#घोषणा SET_ARRAY_INFO		_IOW (MD_MAJOR, 0x23, mdu_array_info_t)
#घोषणा SET_DISK_INFO		_IO (MD_MAJOR, 0x24)
#घोषणा WRITE_RAID_INFO		_IO (MD_MAJOR, 0x25)
#घोषणा UNPROTECT_ARRAY		_IO (MD_MAJOR, 0x26)
#घोषणा PROTECT_ARRAY		_IO (MD_MAJOR, 0x27)
#घोषणा HOT_ADD_DISK		_IO (MD_MAJOR, 0x28)
#घोषणा SET_DISK_FAULTY		_IO (MD_MAJOR, 0x29)
#घोषणा HOT_GENERATE_ERROR	_IO (MD_MAJOR, 0x2a)
#घोषणा SET_BITMAP_खाता		_IOW (MD_MAJOR, 0x2b, पूर्णांक)

/* usage */
#घोषणा RUN_ARRAY		_IOW (MD_MAJOR, 0x30, mdu_param_t)
/*  0x31 was START_ARRAY  */
#घोषणा STOP_ARRAY		_IO (MD_MAJOR, 0x32)
#घोषणा STOP_ARRAY_RO		_IO (MD_MAJOR, 0x33)
#घोषणा RESTART_ARRAY_RW	_IO (MD_MAJOR, 0x34)
#घोषणा CLUSTERED_DISK_NACK	_IO (MD_MAJOR, 0x35)

/* 63 partitions with the alternate major number (mdp) */
#घोषणा MdpMinorShअगरt 6

प्रकार काष्ठा mdu_version_s अणु
	पूर्णांक major;
	पूर्णांक minor;
	पूर्णांक patchlevel;
पूर्ण mdu_version_t;

प्रकार काष्ठा mdu_array_info_s अणु
	/*
	 * Generic स्थिरant inक्रमmation
	 */
	पूर्णांक major_version;
	पूर्णांक minor_version;
	पूर्णांक patch_version;
	अचिन्हित पूर्णांक स_समय;
	पूर्णांक level;
	पूर्णांक size;
	पूर्णांक nr_disks;
	पूर्णांक raid_disks;
	पूर्णांक md_minor;
	पूर्णांक not_persistent;

	/*
	 * Generic state inक्रमmation
	 */
	अचिन्हित पूर्णांक uसमय;	/*  0 Superblock update समय		      */
	पूर्णांक state;		/*  1 State bits (clean, ...)		      */
	पूर्णांक active_disks;	/*  2 Number of currently active disks	      */
	पूर्णांक working_disks;	/*  3 Number of working disks		      */
	पूर्णांक failed_disks;	/*  4 Number of failed disks		      */
	पूर्णांक spare_disks;	/*  5 Number of spare disks		      */

	/*
	 * Personality inक्रमmation
	 */
	पूर्णांक layout;		/*  0 the array's physical layout	      */
	पूर्णांक chunk_size;	/*  1 chunk size in bytes		      */

पूर्ण mdu_array_info_t;

/* non-obvious values क्रम 'level' */
#घोषणा	LEVEL_MULTIPATH		(-4)
#घोषणा	LEVEL_LINEAR		(-1)
#घोषणा	LEVEL_FAULTY		(-5)

/* we need a value क्रम 'no level specified' and 0
 * means 'raid0', so we need something अन्यथा.  This is
 * क्रम पूर्णांकernal use only
 */
#घोषणा	LEVEL_NONE		(-1000000)

प्रकार काष्ठा mdu_disk_info_s अणु
	/*
	 * configuration/status of one particular disk
	 */
	पूर्णांक number;
	पूर्णांक major;
	पूर्णांक minor;
	पूर्णांक raid_disk;
	पूर्णांक state;

पूर्ण mdu_disk_info_t;

प्रकार काष्ठा mdu_start_info_s अणु
	/*
	 * configuration/status of one particular disk
	 */
	पूर्णांक major;
	पूर्णांक minor;
	पूर्णांक raid_disk;
	पूर्णांक state;

पूर्ण mdu_start_info_t;

प्रकार काष्ठा mdu_biपंचांगap_file_s
अणु
	अक्षर pathname[4096];
पूर्ण mdu_biपंचांगap_file_t;

प्रकार काष्ठा mdu_param_s
अणु
	पूर्णांक			personality;	/* 1,2,3,4 */
	पूर्णांक			chunk_size;	/* in bytes */
	पूर्णांक			max_fault;	/* unused क्रम now */
पूर्ण mdu_param_t;

#पूर्ण_अगर /* _UAPI_MD_U_H */
