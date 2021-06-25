<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Zoran ZR36016 basic configuration functions - header file
 *
 * Copyright (C) 2001 Wolfgang Scherr <scherr@net4you.at>
 */

#अगर_अघोषित ZR36016_H
#घोषणा ZR36016_H

/* data stored क्रम each zoran jpeg codec chip */
काष्ठा zr36016 अणु
	अक्षर name[32];
	पूर्णांक num;
	/* io dataकाष्ठाure */
	काष्ठा videocodec *codec;
	// coder status
	__u8 version;
	// actual coder setup
	पूर्णांक mode;

	__u16 xoff;
	__u16 yoff;
	__u16 width;
	__u16 height;
	__u16 xdec;
	__u16 ydec;
पूर्ण;

/* direct  रेजिस्टर addresses */
#घोषणा ZR016_GOSTOP      0x00
#घोषणा ZR016_MODE        0x01
#घोषणा ZR016_IADDR       0x02
#घोषणा ZR016_IDATA       0x03

/* indirect  रेजिस्टर addresses */
#घोषणा ZR016I_SETUP1     0x00
#घोषणा ZR016I_SETUP2     0x01
#घोषणा ZR016I_NAX_LO     0x02
#घोषणा ZR016I_NAX_HI     0x03
#घोषणा ZR016I_PAX_LO     0x04
#घोषणा ZR016I_PAX_HI     0x05
#घोषणा ZR016I_NAY_LO     0x06
#घोषणा ZR016I_NAY_HI     0x07
#घोषणा ZR016I_PAY_LO     0x08
#घोषणा ZR016I_PAY_HI     0x09
#घोषणा ZR016I_NOL_LO     0x0a
#घोषणा ZR016I_NOL_HI     0x0b

/* possible values क्रम mode रेजिस्टर */
#घोषणा ZR016_RGB444_YUV444  0x00
#घोषणा ZR016_RGB444_YUV422  0x01
#घोषणा ZR016_RGB444_YUV411  0x02
#घोषणा ZR016_RGB444_Y400    0x03
#घोषणा ZR016_RGB444_RGB444  0x04
#घोषणा ZR016_YUV444_YUV444  0x08
#घोषणा ZR016_YUV444_YUV422  0x09
#घोषणा ZR016_YUV444_YUV411  0x0a
#घोषणा ZR016_YUV444_Y400    0x0b
#घोषणा ZR016_YUV444_RGB444  0x0c
#घोषणा ZR016_YUV422_YUV422  0x11
#घोषणा ZR016_YUV422_YUV411  0x12
#घोषणा ZR016_YUV422_Y400    0x13
#घोषणा ZR016_YUV411_YUV411  0x16
#घोषणा ZR016_YUV411_Y400    0x17
#घोषणा ZR016_4444_4444      0x19
#घोषणा ZR016_100_100        0x1b

#घोषणा ZR016_RGB444         0x00
#घोषणा ZR016_YUV444         0x20
#घोषणा ZR016_YUV422         0x40

#घोषणा ZR016_COMPRESSION    0x80
#घोषणा ZR016_EXPANSION      0x80

/* possible values क्रम setup 1 रेजिस्टर */
#घोषणा ZR016_CKRT           0x80
#घोषणा ZR016_VERT           0x40
#घोषणा ZR016_HORZ           0x20
#घोषणा ZR016_HRFL           0x10
#घोषणा ZR016_DSFL           0x08
#घोषणा ZR016_SBFL           0x04
#घोषणा ZR016_RSTR           0x02
#घोषणा ZR016_CNTI           0x01

/* possible values क्रम setup 2 रेजिस्टर */
#घोषणा ZR016_SYEN           0x40
#घोषणा ZR016_CCIR           0x04
#घोषणा ZR016_SIGN           0x02
#घोषणा ZR016_YMCS           0x01

#पूर्ण_अगर				/*fndef ZR36016_H */
