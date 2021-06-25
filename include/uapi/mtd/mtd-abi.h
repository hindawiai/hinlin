<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * Copyright तऊ 1999-2010 David Woodhouse <dwmw2@infradead.org> et al.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA  02110-1301  USA
 *
 */

#अगर_अघोषित __MTD_ABI_H__
#घोषणा __MTD_ABI_H__

#समावेश <linux/types.h>

काष्ठा erase_info_user अणु
	__u32 start;
	__u32 length;
पूर्ण;

काष्ठा erase_info_user64 अणु
	__u64 start;
	__u64 length;
पूर्ण;

काष्ठा mtd_oob_buf अणु
	__u32 start;
	__u32 length;
	अचिन्हित अक्षर __user *ptr;
पूर्ण;

काष्ठा mtd_oob_buf64 अणु
	__u64 start;
	__u32 pad;
	__u32 length;
	__u64 usr_ptr;
पूर्ण;

/**
 * MTD operation modes
 *
 * @MTD_OPS_PLACE_OOB:	OOB data are placed at the given offset (शेष)
 * @MTD_OPS_AUTO_OOB:	OOB data are स्वतःmatically placed at the मुक्त areas
 *			which are defined by the पूर्णांकernal ecclayout
 * @MTD_OPS_RAW:	data are transferred as-is, with no error correction;
 *			this mode implies %MTD_OPS_PLACE_OOB
 *
 * These modes can be passed to ioctl(MEMWRITE) and are also used पूर्णांकernally.
 * See notes on "MTD file modes" क्रम discussion on %MTD_OPS_RAW vs.
 * %MTD_खाता_MODE_RAW.
 */
क्रमागत अणु
	MTD_OPS_PLACE_OOB = 0,
	MTD_OPS_AUTO_OOB = 1,
	MTD_OPS_RAW = 2,
पूर्ण;

/**
 * काष्ठा mtd_ग_लिखो_req - data काष्ठाure क्रम requesting a ग_लिखो operation
 *
 * @start:	start address
 * @len:	length of data buffer
 * @ooblen:	length of OOB buffer
 * @usr_data:	user-provided data buffer
 * @usr_oob:	user-provided OOB buffer
 * @mode:	MTD mode (see "MTD operation modes")
 * @padding:	reserved, must be set to 0
 *
 * This काष्ठाure supports ioctl(MEMWRITE) operations, allowing data and/or OOB
 * ग_लिखोs in various modes. To ग_लिखो to OOB-only, set @usr_data == शून्य, and to
 * ग_लिखो data-only, set @usr_oob == शून्य. However, setting both @usr_data and
 * @usr_oob to शून्य is not allowed.
 */
काष्ठा mtd_ग_लिखो_req अणु
	__u64 start;
	__u64 len;
	__u64 ooblen;
	__u64 usr_data;
	__u64 usr_oob;
	__u8 mode;
	__u8 padding[7];
पूर्ण;

#घोषणा MTD_ABSENT		0
#घोषणा MTD_RAM			1
#घोषणा MTD_ROM			2
#घोषणा MTD_NORFLASH		3
#घोषणा MTD_न_अंकDFLASH		4	/* SLC न_अंकD */
#घोषणा MTD_DATAFLASH		6
#घोषणा MTD_UBIVOLUME		7
#घोषणा MTD_MLCन_अंकDFLASH	8	/* MLC न_अंकD (including TLC) */

#घोषणा MTD_WRITEABLE		0x400	/* Device is ग_लिखोable */
#घोषणा MTD_BIT_WRITEABLE	0x800	/* Single bits can be flipped */
#घोषणा MTD_NO_ERASE		0x1000	/* No erase necessary */
#घोषणा MTD_POWERUP_LOCK	0x2000	/* Always locked after reset */
#घोषणा MTD_SLC_ON_MLC_EMULATION 0x4000	/* Emulate SLC behavior on MLC न_अंकDs */

/* Some common devices / combinations of capabilities */
#घोषणा MTD_CAP_ROM		0
#घोषणा MTD_CAP_RAM		(MTD_WRITEABLE | MTD_BIT_WRITEABLE | MTD_NO_ERASE)
#घोषणा MTD_CAP_NORFLASH	(MTD_WRITEABLE | MTD_BIT_WRITEABLE)
#घोषणा MTD_CAP_न_अंकDFLASH	(MTD_WRITEABLE)
#घोषणा MTD_CAP_NVRAM		(MTD_WRITEABLE | MTD_BIT_WRITEABLE | MTD_NO_ERASE)

/* Obsolete ECC byte placement modes (used with obsolete MEMGETOOBSEL) */
#घोषणा MTD_न_अंकDECC_OFF		0	/* Switch off ECC (Not recommended) */
#घोषणा MTD_न_अंकDECC_PLACE	1	/* Use the given placement in the काष्ठाure (YAFFS1 legacy mode) */
#घोषणा MTD_न_अंकDECC_AUTOPLACE	2	/* Use the शेष placement scheme */
#घोषणा MTD_न_अंकDECC_PLACEONLY	3	/* Use the given placement in the काष्ठाure (Do not store ecc result on पढ़ो) */
#घोषणा MTD_न_अंकDECC_AUTOPL_USR 	4	/* Use the given स्वतःplacement scheme rather than using the शेष */

/* OTP mode selection */
#घोषणा MTD_OTP_OFF		0
#घोषणा MTD_OTP_FACTORY		1
#घोषणा MTD_OTP_USER		2

काष्ठा mtd_info_user अणु
	__u8 type;
	__u32 flags;
	__u32 size;	/* Total size of the MTD */
	__u32 erasesize;
	__u32 ग_लिखोsize;
	__u32 oobsize;	/* Amount of OOB data per block (e.g. 16) */
	__u64 padding;	/* Old obsolete field; करो not use */
पूर्ण;

काष्ठा region_info_user अणु
	__u32 offset;		/* At which this region starts,
				 * from the beginning of the MTD */
	__u32 erasesize;	/* For this region */
	__u32 numblocks;	/* Number of blocks in this region */
	__u32 regionindex;
पूर्ण;

काष्ठा otp_info अणु
	__u32 start;
	__u32 length;
	__u32 locked;
पूर्ण;

/*
 * Note, the following ioctl existed in the past and was हटाओd:
 * #घोषणा MEMSETOOBSEL           _IOW('M', 9, काष्ठा nand_oobinfo)
 * Try to aव्योम adding a new ioctl with the same ioctl number.
 */

/* Get basic MTD अक्षरacteristics info (better to use sysfs) */
#घोषणा MEMGETINFO		_IOR('M', 1, काष्ठा mtd_info_user)
/* Erase segment of MTD */
#घोषणा MEMERASE		_IOW('M', 2, काष्ठा erase_info_user)
/* Write out-of-band data from MTD */
#घोषणा MEMWRITEOOB		_IOWR('M', 3, काष्ठा mtd_oob_buf)
/* Read out-of-band data from MTD */
#घोषणा MEMREADOOB		_IOWR('M', 4, काष्ठा mtd_oob_buf)
/* Lock a chip (क्रम MTD that supports it) */
#घोषणा MEMLOCK			_IOW('M', 5, काष्ठा erase_info_user)
/* Unlock a chip (क्रम MTD that supports it) */
#घोषणा MEMUNLOCK		_IOW('M', 6, काष्ठा erase_info_user)
/* Get the number of dअगरferent erase regions */
#घोषणा MEMGETREGIONCOUNT	_IOR('M', 7, पूर्णांक)
/* Get inक्रमmation about the erase region क्रम a specअगरic index */
#घोषणा MEMGETREGIONINFO	_IOWR('M', 8, काष्ठा region_info_user)
/* Get info about OOB modes (e.g., RAW, PLACE, AUTO) - legacy पूर्णांकerface */
#घोषणा MEMGETOOBSEL		_IOR('M', 10, काष्ठा nand_oobinfo)
/* Check अगर an eraseblock is bad */
#घोषणा MEMGETBADBLOCK		_IOW('M', 11, __kernel_loff_t)
/* Mark an eraseblock as bad */
#घोषणा MEMSETBADBLOCK		_IOW('M', 12, __kernel_loff_t)
/* Set OTP (One-Time Programmable) mode (factory vs. user) */
#घोषणा OTPSELECT		_IOR('M', 13, पूर्णांक)
/* Get number of OTP (One-Time Programmable) regions */
#घोषणा OTPGETREGIONCOUNT	_IOW('M', 14, पूर्णांक)
/* Get all OTP (One-Time Programmable) info about MTD */
#घोषणा OTPGETREGIONINFO	_IOW('M', 15, काष्ठा otp_info)
/* Lock a given range of user data (must be in mode %MTD_खाता_MODE_OTP_USER) */
#घोषणा OTPLOCK			_IOR('M', 16, काष्ठा otp_info)
/* Get ECC layout (deprecated) */
#घोषणा ECCGETLAYOUT		_IOR('M', 17, काष्ठा nand_ecclayout_user)
/* Get statistics about corrected/uncorrected errors */
#घोषणा ECCGETSTATS		_IOR('M', 18, काष्ठा mtd_ecc_stats)
/* Set MTD mode on a per-file-descriptor basis (see "MTD file modes") */
#घोषणा MTDखाताMODE		_IO('M', 19)
/* Erase segment of MTD (supports 64-bit address) */
#घोषणा MEMERASE64		_IOW('M', 20, काष्ठा erase_info_user64)
/* Write data to OOB (64-bit version) */
#घोषणा MEMWRITEOOB64		_IOWR('M', 21, काष्ठा mtd_oob_buf64)
/* Read data from OOB (64-bit version) */
#घोषणा MEMREADOOB64		_IOWR('M', 22, काष्ठा mtd_oob_buf64)
/* Check अगर chip is locked (क्रम MTD that supports it) */
#घोषणा MEMISLOCKED		_IOR('M', 23, काष्ठा erase_info_user)
/*
 * Most generic ग_लिखो पूर्णांकerface; can ग_लिखो in-band and/or out-of-band in various
 * modes (see "struct mtd_write_req"). This ioctl is not supported क्रम flashes
 * without OOB, e.g., NOR flash.
 */
#घोषणा MEMWRITE		_IOWR('M', 24, काष्ठा mtd_ग_लिखो_req)
/* Erase a given range of user data (must be in mode %MTD_खाता_MODE_OTP_USER) */
#घोषणा OTPERASE		_IOW('M', 25, काष्ठा otp_info)

/*
 * Obsolete legacy पूर्णांकerface. Keep it in order not to अवरोध userspace
 * पूर्णांकerfaces
 */
काष्ठा nand_oobinfo अणु
	__u32 useecc;
	__u32 eccbytes;
	__u32 oobमुक्त[8][2];
	__u32 eccpos[32];
पूर्ण;

काष्ठा nand_oobमुक्त अणु
	__u32 offset;
	__u32 length;
पूर्ण;

#घोषणा MTD_MAX_OOBFREE_ENTRIES	8
#घोषणा MTD_MAX_ECCPOS_ENTRIES	64
/*
 * OBSOLETE: ECC layout control काष्ठाure. Exported to user-space via ioctl
 * ECCGETLAYOUT क्रम backwards compatbility and should not be mistaken as a
 * complete set of ECC inक्रमmation. The ioctl truncates the larger पूर्णांकernal
 * काष्ठाure to retain binary compatibility with the अटल declaration of the
 * ioctl. Note that the "MTD_MAX_..._ENTRIES" macros represent the max size of
 * the user काष्ठा, not the MAX size of the पूर्णांकernal OOB layout representation.
 */
काष्ठा nand_ecclayout_user अणु
	__u32 eccbytes;
	__u32 eccpos[MTD_MAX_ECCPOS_ENTRIES];
	__u32 oobavail;
	काष्ठा nand_oobमुक्त oobमुक्त[MTD_MAX_OOBFREE_ENTRIES];
पूर्ण;

/**
 * काष्ठा mtd_ecc_stats - error correction stats
 *
 * @corrected:	number of corrected bits
 * @failed:	number of uncorrectable errors
 * @badblocks:	number of bad blocks in this partition
 * @bbtblocks:	number of blocks reserved क्रम bad block tables
 */
काष्ठा mtd_ecc_stats अणु
	__u32 corrected;
	__u32 failed;
	__u32 badblocks;
	__u32 bbtblocks;
पूर्ण;

/*
 * MTD file modes - क्रम पढ़ो/ग_लिखो access to MTD
 *
 * @MTD_खाता_MODE_NORMAL:	OTP disabled, ECC enabled
 * @MTD_खाता_MODE_OTP_FACTORY:	OTP enabled in factory mode
 * @MTD_खाता_MODE_OTP_USER:	OTP enabled in user mode
 * @MTD_खाता_MODE_RAW:		OTP disabled, ECC disabled
 *
 * These modes can be set via ioctl(MTDखाताMODE). The mode will be retained
 * separately क्रम each खोलो file descriptor.
 *
 * Note: %MTD_खाता_MODE_RAW provides the same functionality as %MTD_OPS_RAW -
 * raw access to the flash, without error correction or स्वतःplacement schemes.
 * Wherever possible, the MTD_OPS_* mode will override the MTD_खाता_MODE_* mode
 * (e.g., when using ioctl(MEMWRITE)), but in some हालs, the MTD_खाता_MODE is
 * used out of necessity (e.g., `ग_लिखो()', ioctl(MEMWRITEOOB64)).
 */
क्रमागत mtd_file_modes अणु
	MTD_खाता_MODE_NORMAL = MTD_OTP_OFF,
	MTD_खाता_MODE_OTP_FACTORY = MTD_OTP_FACTORY,
	MTD_खाता_MODE_OTP_USER = MTD_OTP_USER,
	MTD_खाता_MODE_RAW,
पूर्ण;

अटल अंतरभूत पूर्णांक mtd_type_is_nand_user(स्थिर काष्ठा mtd_info_user *mtd)
अणु
	वापस mtd->type == MTD_न_अंकDFLASH || mtd->type == MTD_MLCन_अंकDFLASH;
पूर्ण

#पूर्ण_अगर /* __MTD_ABI_H__ */
