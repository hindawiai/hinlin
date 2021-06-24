<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * ERSPAN Tunnel Metadata
 *
 * Copyright (c) 2018 VMware
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * Userspace API क्रम metadata mode ERSPAN tunnel
 */
#अगर_अघोषित _UAPI_ERSPAN_H
#घोषणा _UAPI_ERSPAN_H

#समावेश <linux/types.h>	/* For __beXX in userspace */
#समावेश <यंत्र/byteorder.h>

/* ERSPAN version 2 metadata header */
काष्ठा erspan_md2 अणु
	__be32 बारtamp;
	__be16 sgt;	/* security group tag */
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8	hwid_upper:2,
		ft:5,
		p:1;
	__u8	o:1,
		gra:2,
		dir:1,
		hwid:4;
#या_अगर defined(__BIG_ENDIAN_BITFIELD)
	__u8	p:1,
		ft:5,
		hwid_upper:2;
	__u8	hwid:4,
		dir:1,
		gra:2,
		o:1;
#अन्यथा
#त्रुटि "Please fix <asm/byteorder.h>"
#पूर्ण_अगर
पूर्ण;

काष्ठा erspan_metadata अणु
	पूर्णांक version;
	जोड़ अणु
		__be32 index;		/* Version 1 (type II)*/
		काष्ठा erspan_md2 md2;	/* Version 2 (type III) */
	पूर्ण u;
पूर्ण;

#पूर्ण_अगर /* _UAPI_ERSPAN_H */
