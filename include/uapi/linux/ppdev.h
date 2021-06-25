<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * linux/include/linux/ppdev.h
 *
 * User-space parallel port device driver (header file).
 *
 * Copyright (C) 1998-9 Tim Waugh <tim@cyberelk.demon.co.uk>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 *
 * Added PPGETTIME/PPSETTIME, Fred Barnes, 1999
 * Added PPGETMODES/PPGETMODE/PPGETPHASE, Fred Barnes <frmb2@ukc.ac.uk>, 03/01/2001
 */

#अगर_अघोषित _UAPI_LINUX_PPDEV_H
#घोषणा _UAPI_LINUX_PPDEV_H

#घोषणा PP_IOCTL	'p'

/* Set mode क्रम पढ़ो/ग_लिखो (e.g. IEEE1284_MODE_EPP) */
#घोषणा PPSETMODE	_IOW(PP_IOCTL, 0x80, पूर्णांक)

/* Read status */
#घोषणा PPRSTATUS	_IOR(PP_IOCTL, 0x81, अचिन्हित अक्षर)
#घोषणा PPWSTATUS	OBSOLETE__IOW(PP_IOCTL, 0x82, अचिन्हित अक्षर)

/* Read/ग_लिखो control */
#घोषणा PPRCONTROL	_IOR(PP_IOCTL, 0x83, अचिन्हित अक्षर)
#घोषणा PPWCONTROL	_IOW(PP_IOCTL, 0x84, अचिन्हित अक्षर)

काष्ठा ppdev_frob_काष्ठा अणु
	अचिन्हित अक्षर mask;
	अचिन्हित अक्षर val;
पूर्ण;
#घोषणा PPFCONTROL      _IOW(PP_IOCTL, 0x8e, काष्ठा ppdev_frob_काष्ठा)

/* Read/ग_लिखो data */
#घोषणा PPRDATA		_IOR(PP_IOCTL, 0x85, अचिन्हित अक्षर)
#घोषणा PPWDATA		_IOW(PP_IOCTL, 0x86, अचिन्हित अक्षर)

/* Read/ग_लिखो econtrol (not used) */
#घोषणा PPRECONTROL	OBSOLETE__IOR(PP_IOCTL, 0x87, अचिन्हित अक्षर)
#घोषणा PPWECONTROL	OBSOLETE__IOW(PP_IOCTL, 0x88, अचिन्हित अक्षर)

/* Read/ग_लिखो FIFO (not used) */
#घोषणा PPRFIFO		OBSOLETE__IOR(PP_IOCTL, 0x89, अचिन्हित अक्षर)
#घोषणा PPWFIFO		OBSOLETE__IOW(PP_IOCTL, 0x8a, अचिन्हित अक्षर)

/* Claim the port to start using it */
#घोषणा PPCLAIM		_IO(PP_IOCTL, 0x8b)

/* Release the port when you aren't using it */
#घोषणा PPRELEASE	_IO(PP_IOCTL, 0x8c)

/* Yield the port (release it अगर another driver is रुकोing,
 * then reclaim) */
#घोषणा PPYIELD		_IO(PP_IOCTL, 0x8d)

/* Register device exclusively (must be beक्रमe PPCLAIM). */
#घोषणा PPEXCL		_IO(PP_IOCTL, 0x8f)

/* Data line direction: non-zero क्रम input mode. */
#घोषणा PPDATAसूची	_IOW(PP_IOCTL, 0x90, पूर्णांक)

/* Negotiate a particular IEEE 1284 mode. */
#घोषणा PPNEGOT		_IOW(PP_IOCTL, 0x91, पूर्णांक)

/* Set control lines when an पूर्णांकerrupt occurs. */
#घोषणा PPWCTLONIRQ	_IOW(PP_IOCTL, 0x92, अचिन्हित अक्षर)

/* Clear (and वापस) पूर्णांकerrupt count. */
#घोषणा PPCLRIRQ	_IOR(PP_IOCTL, 0x93, पूर्णांक)

/* Set the IEEE 1284 phase that we're in (e.g. IEEE1284_PH_FWD_IDLE) */
#घोषणा PPSETPHASE	_IOW(PP_IOCTL, 0x94, पूर्णांक)

/* Set and get port समयout (काष्ठा समयval's) */
#घोषणा PPGETTIME	_IOR(PP_IOCTL, 0x95, काष्ठा समयval)
#घोषणा PPSETTIME	_IOW(PP_IOCTL, 0x96, काष्ठा समयval)

/* Get available modes (what the hardware can करो) */
#घोषणा PPGETMODES	_IOR(PP_IOCTL, 0x97, अचिन्हित पूर्णांक)

/* Get the current mode and phaze */
#घोषणा PPGETMODE	_IOR(PP_IOCTL, 0x98, पूर्णांक)
#घोषणा PPGETPHASE	_IOR(PP_IOCTL, 0x99, पूर्णांक)

/* get/set flags */
#घोषणा PPGETFLAGS	_IOR(PP_IOCTL, 0x9a, पूर्णांक)
#घोषणा PPSETFLAGS	_IOW(PP_IOCTL, 0x9b, पूर्णांक)

/* flags visible to the world */
#घोषणा PP_FASTWRITE	(1<<2)
#घोषणा PP_FASTREAD	(1<<3)
#घोषणा PP_W91284PIC	(1<<4)

/* only masks user-visible flags */
#घोषणा PP_FLAGMASK	(PP_FASTWRITE | PP_FASTREAD | PP_W91284PIC)

#पूर्ण_अगर /* _UAPI_LINUX_PPDEV_H */
