<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2020 Jonathan Neuschथअfer
 *
 * Register access and version inक्रमmation क्रम the Netronix embedded
 * controller.
 */

#अगर_अघोषित NTXEC_H
#घोषणा NTXEC_H

#समावेश <linux/types.h>

काष्ठा device;
काष्ठा regmap;

काष्ठा ntxec अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
पूर्ण;

/*
 * Some रेजिस्टरs, such as the battery status रेजिस्टर (0x41), are in
 * big-endian, but others only have eight signअगरicant bits, which are in the
 * first byte transmitted over I2C (the MSB of the big-endian value).
 * This convenience function converts an 8-bit value to 16-bit क्रम use in the
 * second kind of रेजिस्टर.
 */
अटल अंतरभूत __be16 ntxec_reg8(u8 value)
अणु
	वापस value << 8;
पूर्ण

/* Known firmware versions */
#घोषणा NTXEC_VERSION_KOBO_AURA	0xd726	/* found in Kobo Aura */
#घोषणा NTXEC_VERSION_TOLINO_SHINE2 0xf110 /* found in Tolino Shine 2 HD */

#पूर्ण_अगर
