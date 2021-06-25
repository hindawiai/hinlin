<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * Copyright तऊ 1999-2010 David Woodhouse <dwmw2@infradead.org>
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

#अगर_अघोषित __MTD_NFTL_USER_H__
#घोषणा __MTD_NFTL_USER_H__

#समावेश <linux/types.h>

/* Block Control Inक्रमmation */

काष्ठा nftl_bci अणु
	अचिन्हित अक्षर ECCSig[6];
	__u8 Status;
	__u8 Status1;
पूर्ण__attribute__((packed));

/* Unit Control Inक्रमmation */

काष्ठा nftl_uci0 अणु
	__u16 VirtUnitNum;
	__u16 ReplUnitNum;
	__u16 SpareVirtUnitNum;
	__u16 SpareReplUnitNum;
पूर्ण __attribute__((packed));

काष्ठा nftl_uci1 अणु
	__u32 WearInfo;
	__u16 EraseMark;
	__u16 EraseMark1;
पूर्ण __attribute__((packed));

काष्ठा nftl_uci2 अणु
        __u16 FoldMark;
        __u16 FoldMark1;
	__u32 unused;
पूर्ण __attribute__((packed));

जोड़ nftl_uci अणु
	काष्ठा nftl_uci0 a;
	काष्ठा nftl_uci1 b;
	काष्ठा nftl_uci2 c;
पूर्ण;

काष्ठा nftl_oob अणु
	काष्ठा nftl_bci b;
	जोड़ nftl_uci u;
पूर्ण;

/* NFTL Media Header */

काष्ठा NFTLMediaHeader अणु
	अक्षर DataOrgID[6];
	__u16 NumEraseUnits;
	__u16 FirstPhysicalEUN;
	__u32 FormattedSize;
	अचिन्हित अक्षर UnitSizeFactor;
पूर्ण __attribute__((packed));

#घोषणा MAX_ERASE_ZONES (8192 - 512)

#घोषणा ERASE_MARK 0x3c69
#घोषणा SECTOR_FREE 0xff
#घोषणा SECTOR_USED 0x55
#घोषणा SECTOR_IGNORE 0x11
#घोषणा SECTOR_DELETED 0x00

#घोषणा FOLD_MARK_IN_PROGRESS 0x5555

#घोषणा ZONE_GOOD 0xff
#घोषणा ZONE_BAD_ORIGINAL 0
#घोषणा ZONE_BAD_MARKED 7


#पूर्ण_अगर /* __MTD_NFTL_USER_H__ */
