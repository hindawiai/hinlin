<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * PTP 1588 घड़ी support - user space पूर्णांकerface
 *
 * Copyright (C) 2010 OMICRON electronics GmbH
 *
 *  This program is मुक्त software; you can redistribute it and/or modअगरy
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License क्रम more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#अगर_अघोषित _PTP_CLOCK_H_
#घोषणा _PTP_CLOCK_H_

#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

/*
 * Bits of the ptp_extts_request.flags field:
 */
#घोषणा PTP_ENABLE_FEATURE (1<<0)
#घोषणा PTP_RISING_EDGE    (1<<1)
#घोषणा PTP_FALLING_EDGE   (1<<2)
#घोषणा PTP_STRICT_FLAGS   (1<<3)
#घोषणा PTP_EXTTS_EDGES    (PTP_RISING_EDGE | PTP_FALLING_EDGE)

/*
 * flag fields valid क्रम the new PTP_EXTTS_REQUEST2 ioctl.
 */
#घोषणा PTP_EXTTS_VALID_FLAGS	(PTP_ENABLE_FEATURE |	\
				 PTP_RISING_EDGE |	\
				 PTP_FALLING_EDGE |	\
				 PTP_STRICT_FLAGS)

/*
 * flag fields valid क्रम the original PTP_EXTTS_REQUEST ioctl.
 * DO NOT ADD NEW FLAGS HERE.
 */
#घोषणा PTP_EXTTS_V1_VALID_FLAGS	(PTP_ENABLE_FEATURE |	\
					 PTP_RISING_EDGE |	\
					 PTP_FALLING_EDGE)

/*
 * Bits of the ptp_perout_request.flags field:
 */
#घोषणा PTP_PEROUT_ONE_SHOT		(1<<0)
#घोषणा PTP_PEROUT_DUTY_CYCLE		(1<<1)
#घोषणा PTP_PEROUT_PHASE		(1<<2)

/*
 * flag fields valid क्रम the new PTP_PEROUT_REQUEST2 ioctl.
 */
#घोषणा PTP_PEROUT_VALID_FLAGS		(PTP_PEROUT_ONE_SHOT | \
					 PTP_PEROUT_DUTY_CYCLE | \
					 PTP_PEROUT_PHASE)

/*
 * No flags are valid क्रम the original PTP_PEROUT_REQUEST ioctl
 */
#घोषणा PTP_PEROUT_V1_VALID_FLAGS	(0)

/*
 * काष्ठा ptp_घड़ी_प्रकारime - represents a समय value
 *
 * The sign of the seconds field applies to the whole value. The
 * nanoseconds field is always अचिन्हित. The reserved field is
 * included क्रम sub-nanosecond resolution, should the demand क्रम
 * this ever appear.
 *
 */
काष्ठा ptp_घड़ी_प्रकारime अणु
	__s64 sec;  /* seconds */
	__u32 nsec; /* nanoseconds */
	__u32 reserved;
पूर्ण;

काष्ठा ptp_घड़ी_caps अणु
	पूर्णांक max_adj;   /* Maximum frequency adjusपंचांगent in parts per billon. */
	पूर्णांक n_alarm;   /* Number of programmable alarms. */
	पूर्णांक n_ext_ts;  /* Number of बाह्यal समय stamp channels. */
	पूर्णांक n_per_out; /* Number of programmable periodic संकेतs. */
	पूर्णांक pps;       /* Whether the घड़ी supports a PPS callback. */
	पूर्णांक n_pins;    /* Number of input/output pins. */
	/* Whether the घड़ी supports precise प्रणाली-device cross बारtamps */
	पूर्णांक cross_बारtamping;
	/* Whether the घड़ी supports adjust phase */
	पूर्णांक adjust_phase;
	पूर्णांक rsv[12];   /* Reserved क्रम future use. */
पूर्ण;

काष्ठा ptp_extts_request अणु
	अचिन्हित पूर्णांक index;  /* Which channel to configure. */
	अचिन्हित पूर्णांक flags;  /* Bit field क्रम PTP_xxx flags. */
	अचिन्हित पूर्णांक rsv[2]; /* Reserved क्रम future use. */
पूर्ण;

काष्ठा ptp_perout_request अणु
	जोड़ अणु
		/*
		 * Absolute start समय.
		 * Valid only अगर (flags & PTP_PEROUT_PHASE) is unset.
		 */
		काष्ठा ptp_घड़ी_प्रकारime start;
		/*
		 * Phase offset. The संकेत should start toggling at an
		 * unspecअगरied पूर्णांकeger multiple of the period, plus this value.
		 * The start समय should be "as soon as possible".
		 * Valid only अगर (flags & PTP_PEROUT_PHASE) is set.
		 */
		काष्ठा ptp_घड़ी_प्रकारime phase;
	पूर्ण;
	काष्ठा ptp_घड़ी_प्रकारime period; /* Desired period, zero means disable. */
	अचिन्हित पूर्णांक index;           /* Which channel to configure. */
	अचिन्हित पूर्णांक flags;
	जोड़ अणु
		/*
		 * The "on" समय of the संकेत.
		 * Must be lower than the period.
		 * Valid only अगर (flags & PTP_PEROUT_DUTY_CYCLE) is set.
		 */
		काष्ठा ptp_घड़ी_प्रकारime on;
		/* Reserved क्रम future use. */
		अचिन्हित पूर्णांक rsv[4];
	पूर्ण;
पूर्ण;

#घोषणा PTP_MAX_SAMPLES 25 /* Maximum allowed offset measurement samples. */

काष्ठा ptp_sys_offset अणु
	अचिन्हित पूर्णांक n_samples; /* Desired number of measurements. */
	अचिन्हित पूर्णांक rsv[3];    /* Reserved क्रम future use. */
	/*
	 * Array of पूर्णांकerleaved प्रणाली/phc समय stamps. The kernel
	 * will provide 2*n_samples + 1 समय stamps, with the last
	 * one as a प्रणाली समय stamp.
	 */
	काष्ठा ptp_घड़ी_प्रकारime ts[2 * PTP_MAX_SAMPLES + 1];
पूर्ण;

काष्ठा ptp_sys_offset_extended अणु
	अचिन्हित पूर्णांक n_samples; /* Desired number of measurements. */
	अचिन्हित पूर्णांक rsv[3];    /* Reserved क्रम future use. */
	/*
	 * Array of [प्रणाली, phc, प्रणाली] समय stamps. The kernel will provide
	 * 3*n_samples समय stamps.
	 */
	काष्ठा ptp_घड़ी_प्रकारime ts[PTP_MAX_SAMPLES][3];
पूर्ण;

काष्ठा ptp_sys_offset_precise अणु
	काष्ठा ptp_घड़ी_प्रकारime device;
	काष्ठा ptp_घड़ी_प्रकारime sys_realसमय;
	काष्ठा ptp_घड़ी_प्रकारime sys_monoraw;
	अचिन्हित पूर्णांक rsv[4];    /* Reserved क्रम future use. */
पूर्ण;

क्रमागत ptp_pin_function अणु
	PTP_PF_NONE,
	PTP_PF_EXTTS,
	PTP_PF_PEROUT,
	PTP_PF_PHYSYNC,
पूर्ण;

काष्ठा ptp_pin_desc अणु
	/*
	 * Hardware specअगरic human पढ़ोable pin name. This field is
	 * set by the kernel during the PTP_PIN_GETFUNC ioctl and is
	 * ignored क्रम the PTP_PIN_SETFUNC ioctl.
	 */
	अक्षर name[64];
	/*
	 * Pin index in the range of zero to ptp_घड़ी_caps.n_pins - 1.
	 */
	अचिन्हित पूर्णांक index;
	/*
	 * Which of the PTP_PF_xxx functions to use on this pin.
	 */
	अचिन्हित पूर्णांक func;
	/*
	 * The specअगरic channel to use क्रम this function.
	 * This corresponds to the 'index' field of the
	 * PTP_EXTTS_REQUEST and PTP_PEROUT_REQUEST ioctls.
	 */
	अचिन्हित पूर्णांक chan;
	/*
	 * Reserved क्रम future use.
	 */
	अचिन्हित पूर्णांक rsv[5];
पूर्ण;

#घोषणा PTP_CLK_MAGIC '='

#घोषणा PTP_CLOCK_GETCAPS  _IOR(PTP_CLK_MAGIC, 1, काष्ठा ptp_घड़ी_caps)
#घोषणा PTP_EXTTS_REQUEST  _IOW(PTP_CLK_MAGIC, 2, काष्ठा ptp_extts_request)
#घोषणा PTP_PEROUT_REQUEST _IOW(PTP_CLK_MAGIC, 3, काष्ठा ptp_perout_request)
#घोषणा PTP_ENABLE_PPS     _IOW(PTP_CLK_MAGIC, 4, पूर्णांक)
#घोषणा PTP_SYS_OFFSET     _IOW(PTP_CLK_MAGIC, 5, काष्ठा ptp_sys_offset)
#घोषणा PTP_PIN_GETFUNC    _IOWR(PTP_CLK_MAGIC, 6, काष्ठा ptp_pin_desc)
#घोषणा PTP_PIN_SETFUNC    _IOW(PTP_CLK_MAGIC, 7, काष्ठा ptp_pin_desc)
#घोषणा PTP_SYS_OFFSET_PRECISE \
	_IOWR(PTP_CLK_MAGIC, 8, काष्ठा ptp_sys_offset_precise)
#घोषणा PTP_SYS_OFFSET_EXTENDED \
	_IOWR(PTP_CLK_MAGIC, 9, काष्ठा ptp_sys_offset_extended)

#घोषणा PTP_CLOCK_GETCAPS2  _IOR(PTP_CLK_MAGIC, 10, काष्ठा ptp_घड़ी_caps)
#घोषणा PTP_EXTTS_REQUEST2  _IOW(PTP_CLK_MAGIC, 11, काष्ठा ptp_extts_request)
#घोषणा PTP_PEROUT_REQUEST2 _IOW(PTP_CLK_MAGIC, 12, काष्ठा ptp_perout_request)
#घोषणा PTP_ENABLE_PPS2     _IOW(PTP_CLK_MAGIC, 13, पूर्णांक)
#घोषणा PTP_SYS_OFFSET2     _IOW(PTP_CLK_MAGIC, 14, काष्ठा ptp_sys_offset)
#घोषणा PTP_PIN_GETFUNC2    _IOWR(PTP_CLK_MAGIC, 15, काष्ठा ptp_pin_desc)
#घोषणा PTP_PIN_SETFUNC2    _IOW(PTP_CLK_MAGIC, 16, काष्ठा ptp_pin_desc)
#घोषणा PTP_SYS_OFFSET_PRECISE2 \
	_IOWR(PTP_CLK_MAGIC, 17, काष्ठा ptp_sys_offset_precise)
#घोषणा PTP_SYS_OFFSET_EXTENDED2 \
	_IOWR(PTP_CLK_MAGIC, 18, काष्ठा ptp_sys_offset_extended)

काष्ठा ptp_extts_event अणु
	काष्ठा ptp_घड़ी_प्रकारime t; /* Time event occured. */
	अचिन्हित पूर्णांक index;      /* Which channel produced the event. */
	अचिन्हित पूर्णांक flags;      /* Reserved क्रम future use. */
	अचिन्हित पूर्णांक rsv[2];     /* Reserved क्रम future use. */
पूर्ण;

#पूर्ण_अगर
