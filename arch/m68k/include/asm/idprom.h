<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _M68K_IDPROM_H
#घोषणा _M68K_IDPROM_H
/*
 * idprom.h: Macros and defines क्रम idprom routines
 *
 * Copyright (C) 1995,1996 David S. Miller (davem@caip.rutgers.edu)
 */

#समावेश <linux/types.h>

काष्ठा idprom अणु
	u8		id_क्रमmat;	/* Format identअगरier (always 0x01) */
	u8		id_machtype;	/* Machine type */
	u8		id_ethaddr[6];	/* Hardware ethernet address */
	s32		id_date;	/* Date of manufacture */
	u32		id_sernum:24;	/* Unique serial number */
	u8		id_cksum;	/* Checksum - xor of the data bytes */
	u8		reserved[16];
पूर्ण;

बाह्य काष्ठा idprom *idprom;
बाह्य व्योम idprom_init(व्योम);

/* Sun3: in control space */
#घोषणा SUN3_IDPROM_BASE	0x00000000

#पूर्ण_अगर /* !(_M68K_IDPROM_H) */
