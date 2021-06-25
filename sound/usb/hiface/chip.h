<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Linux driver क्रम M2Tech hiFace compatible devices
 *
 * Copyright 2012-2013 (C) M2TECH S.r.l and Amarula Solutions B.V.
 *
 * Authors:  Michael Trimarchi <michael@amarulasolutions.com>
 *           Antonio Ospite <ao2@amarulasolutions.com>
 *
 * The driver is based on the work करोne in TerraTec DMX 6Fire USB
 */

#अगर_अघोषित HIFACE_CHIP_H
#घोषणा HIFACE_CHIP_H

#समावेश <linux/usb.h>
#समावेश <sound/core.h>

काष्ठा pcm_runसमय;

काष्ठा hअगरace_chip अणु
	काष्ठा usb_device *dev;
	काष्ठा snd_card *card;
	काष्ठा pcm_runसमय *pcm;
पूर्ण;
#पूर्ण_अगर /* HIFACE_CHIP_H */
