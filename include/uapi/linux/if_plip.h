<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 *	NET3	PLIP tuning facilities क्रम the new Niibe PLIP.
 *
 *	This program is मुक्त software; you can redistribute it and/or
 *	modअगरy it under the terms of the GNU General Public License
 *	as published by the Free Software Foundation; either version
 *	2 of the License, or (at your option) any later version.
 *
 */
 
#अगर_अघोषित _LINUX_IF_PLIP_H
#घोषणा _LINUX_IF_PLIP_H

#समावेश <linux/sockios.h>

#घोषणा	SIOCDEVPLIP	SIOCDEVPRIVATE

काष्ठा plipconf अणु
	अचिन्हित लघु pcmd;
	अचिन्हित दीर्घ  nibble;
	अचिन्हित दीर्घ  trigger;
पूर्ण;

#घोषणा PLIP_GET_TIMEOUT	0x1
#घोषणा PLIP_SET_TIMEOUT	0x2

#पूर्ण_अगर
