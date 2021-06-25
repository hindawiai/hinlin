<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Zoran zr36057/zr36067 PCI controller driver, क्रम the
 * Pinnacle/Miro DC10/DC10+/DC30/DC30+, Iomega Buz, Linux
 * Media Lअसल LML33/LML33R10.
 *
 * This part handles card-specअगरic data and detection
 *
 * Copyright (C) 2000 Serguei Miriकरोnov <mirsev@cicese.mx>
 */

#अगर_अघोषित __ZORAN_CARD_H__
#घोषणा __ZORAN_CARD_H__

बाह्य पूर्णांक zr36067_debug;

/* Anybody who uses more than four? */
#घोषणा BUZ_MAX 4

बाह्य स्थिर काष्ठा video_device zoran_ढाँचा;

बाह्य पूर्णांक zoran_check_jpg_settings(काष्ठा zoran *zr,
				    काष्ठा zoran_jpg_settings *settings,
				    पूर्णांक try);
बाह्य व्योम zoran_खोलो_init_params(काष्ठा zoran *zr);
बाह्य व्योम zoran_vdev_release(काष्ठा video_device *vdev);

व्योम zr36016_ग_लिखो(काष्ठा videocodec *codec, u16 reg, u32 val);

#पूर्ण_अगर				/* __ZORAN_CARD_H__ */
