<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * PPS API header
 *
 * Copyright (C) 2005-2009   Roकरोlfo Giometti <giometti@linux.it>
 *
 *   This program is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License क्रम more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */


#अगर_अघोषित _PPS_H_
#घोषणा _PPS_H_

#समावेश <linux/types.h>

#घोषणा PPS_VERSION		"5.3.6"
#घोषणा PPS_MAX_SOURCES		16		/* should be enough... */

/* Implementation note: the logical states ``निश्चित'' and ``clear''
 * are implemented in terms of the chip रेजिस्टर, i.e. ``निश्चित''
 * means the bit is set.  */

/*
 * 3.2 New data काष्ठाures
 */

#घोषणा PPS_API_VERS_1		1
#घोषणा PPS_API_VERS		PPS_API_VERS_1	/* we use API version 1 */
#घोषणा PPS_MAX_NAME_LEN	32

/* 32-bit vs. 64-bit compatibility.
 *
 * 0n i386, the alignment of a uपूर्णांक64_t is only 4 bytes, जबतक on most other
 * architectures it's 8 bytes. On i386, there will be no padding between the
 * two consecutive 'struct pps_ktime' members of काष्ठा pps_kinfo and काष्ठा
 * pps_kparams. But on most platक्रमms there will be padding to ensure correct
 * alignment.
 *
 * The simple fix is probably to add an explicit padding.
 *					 		[David Woodhouse]
 */
काष्ठा pps_kसमय अणु
	__s64 sec;
	__s32 nsec;
	__u32 flags;
पूर्ण;

काष्ठा pps_kसमय_compat अणु
	__s64 sec;
	__s32 nsec;
	__u32 flags;
पूर्ण __attribute__((packed, aligned(4)));
#घोषणा PPS_TIME_INVALID	(1<<0)	/* used to specअगरy समयout==शून्य */

काष्ठा pps_kinfo अणु
	__u32 निश्चित_sequence;		/* seq. num. of निश्चित event */
	__u32 clear_sequence; 		/* seq. num. of clear event */
	काष्ठा pps_kसमय निश्चित_tu;	/* समय of निश्चित event */
	काष्ठा pps_kसमय clear_tu;	/* समय of clear event */
	पूर्णांक current_mode;		/* current mode bits */
पूर्ण;

काष्ठा pps_kinfo_compat अणु
	__u32 निश्चित_sequence;			/* seq. num. of निश्चित event */
	__u32 clear_sequence;			/* seq. num. of clear event */
	काष्ठा pps_kसमय_compat निश्चित_tu;	/* समय of निश्चित event */
	काष्ठा pps_kसमय_compat clear_tu;	/* समय of clear event */
	पूर्णांक current_mode;			/* current mode bits */
पूर्ण;

काष्ठा pps_kparams अणु
	पूर्णांक api_version;		/* API version # */
	पूर्णांक mode;			/* mode bits */
	काष्ठा pps_kसमय निश्चित_off_tu;	/* offset compensation क्रम निश्चित */
	काष्ठा pps_kसमय clear_off_tu;	/* offset compensation क्रम clear */
पूर्ण;

/*
 * 3.3 Mode bit definitions
 */

/* Device/implementation parameters */
#घोषणा PPS_CAPTUREASSERT	0x01	/* capture निश्चित events */
#घोषणा PPS_CAPTURECLEAR	0x02	/* capture clear events */
#घोषणा PPS_CAPTUREBOTH		0x03	/* capture निश्चित and clear events */

#घोषणा PPS_OFFSETASSERT	0x10	/* apply compensation क्रम निश्चित event */
#घोषणा PPS_OFFSETCLEAR		0x20	/* apply compensation क्रम clear event */

#घोषणा PPS_CANWAIT		0x100	/* can we रुको क्रम an event? */
#घोषणा PPS_CANPOLL		0x200	/* bit reserved क्रम future use */

/* Kernel actions */
#घोषणा PPS_ECHOASSERT		0x40	/* feed back निश्चित event to output */
#घोषणा PPS_ECHOCLEAR		0x80	/* feed back clear event to output */

/* Timestamp क्रमmats */
#घोषणा PPS_TSFMT_TSPEC		0x1000	/* select बारpec क्रमmat */
#घोषणा PPS_TSFMT_NTPFP		0x2000	/* select NTP क्रमmat */

/*
 * 3.4.4 New functions: disciplining the kernel समयbase
 */

/* Kernel consumers */
#घोषणा PPS_KC_HARDPPS		0	/* hardpps() (or equivalent) */
#घोषणा PPS_KC_HARDPPS_PLL	1	/* hardpps() स्थिरrained to
					   use a phase-locked loop */
#घोषणा PPS_KC_HARDPPS_FLL	2	/* hardpps() स्थिरrained to
					   use a frequency-locked loop */
/*
 * Here begins the implementation-specअगरic part!
 */

काष्ठा pps_fdata अणु
	काष्ठा pps_kinfo info;
	काष्ठा pps_kसमय समयout;
पूर्ण;

काष्ठा pps_fdata_compat अणु
	काष्ठा pps_kinfo_compat info;
	काष्ठा pps_kसमय_compat समयout;
पूर्ण;

काष्ठा pps_bind_args अणु
	पूर्णांक tsक्रमmat;	/* क्रमmat of समय stamps */
	पूर्णांक edge;	/* selected event type */
	पूर्णांक consumer;	/* selected kernel consumer */
पूर्ण;

#समावेश <linux/ioctl.h>

#घोषणा PPS_GETPARAMS		_IOR('p', 0xa1, काष्ठा pps_kparams *)
#घोषणा PPS_SETPARAMS		_IOW('p', 0xa2, काष्ठा pps_kparams *)
#घोषणा PPS_GETCAP		_IOR('p', 0xa3, पूर्णांक *)
#घोषणा PPS_FETCH		_IOWR('p', 0xa4, काष्ठा pps_fdata *)
#घोषणा PPS_KC_BIND		_IOW('p', 0xa5, काष्ठा pps_bind_args *)

#पूर्ण_अगर /* _PPS_H_ */
