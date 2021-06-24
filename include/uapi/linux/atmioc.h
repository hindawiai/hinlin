<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* aपंचांगioc.h - ranges क्रम ATM-related ioctl numbers */
 
/* Written 1995-1999 by Werner Almesberger, EPFL LRC/ICA */


/*
 * See https://icawww1.epfl.ch/linux-aपंचांग/magic.hपंचांगl क्रम the complete list of
 * "magic" ioctl numbers.
 */


#अगर_अघोषित _LINUX_ATMIOC_H
#घोषणा _LINUX_ATMIOC_H

#समावेश <यंत्र/ioctl.h>
		/* everybody including aपंचांगioc.h will also need _IOअणु,R,W,WRपूर्ण */

#घोषणा ATMIOC_PHYCOM	  0x00 /* PHY device common ioctls, globally unique */
#घोषणा ATMIOC_PHYCOM_END 0x0f
#घोषणा ATMIOC_PHYTYP	  0x10 /* PHY dev type ioctls, unique per PHY type */
#घोषणा ATMIOC_PHYTYP_END 0x2f
#घोषणा ATMIOC_PHYPRV	  0x30 /* PHY dev निजी ioctls, unique per driver */
#घोषणा ATMIOC_PHYPRV_END 0x4f
#घोषणा ATMIOC_SARCOM	  0x50 /* SAR device common ioctls, globally unique */
#घोषणा ATMIOC_SARCOM_END 0x50
#घोषणा ATMIOC_SARPRV	  0x60 /* SAR dev निजी ioctls, unique per driver */
#घोषणा ATMIOC_SARPRV_END 0x7f
#घोषणा ATMIOC_ITF	  0x80 /* Interface ioctls, globally unique */
#घोषणा ATMIOC_ITF_END	  0x8f
#घोषणा ATMIOC_BACKEND	  0x90 /* ATM generic backend ioctls, u. per backend */
#घोषणा ATMIOC_BACKEND_END 0xaf
/* 0xb0-0xbf: Reserved क्रम future use */
#घोषणा ATMIOC_AREQUIPA	  0xc0 /* Application requested IP over ATM, glob. u. */
#घोषणा ATMIOC_LANE	  0xd0 /* LAN Emulation, globally unique */
#घोषणा ATMIOC_MPOA       0xd8 /* MPOA, globally unique */
#घोषणा	ATMIOC_CLIP	  0xe0 /* Classical IP over ATM control, globally u. */
#घोषणा	ATMIOC_CLIP_END	  0xef
#घोषणा	ATMIOC_SPECIAL	  0xf0 /* Special-purpose controls, globally unique */
#घोषणा	ATMIOC_SPECIAL_END 0xff

#पूर्ण_अगर
