<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Silicon Lअसल Si2146/2147/2148/2157/2158 silicon tuner driver
 *
 * Copyright (C) 2014 Antti Palosaari <crope@iki.fi>
 */

#अगर_अघोषित SI2157_H
#घोषणा SI2157_H

#समावेश <media/media-device.h>
#समावेश <media/dvb_frontend.h>

/**
 * काष्ठा si2157_config - configuration parameters क्रम si2157
 *
 * @fe:
 *	frontend वापसed by driver
 * @mdev:
 *	media device वापसed by driver
 * @inversion:
 *	spectral inversion
 * @करोnt_load_firmware:
 *	Instead of uploading a new firmware, use the existing one
 * @अगर_port:
 *	Port selection
 *	Select the RF पूर्णांकerface to use (pins 9+11 or 12+13)
 *
 * Note:
 *	The I2C address of this demod is 0x60.
 */
काष्ठा si2157_config अणु
	काष्ठा dvb_frontend *fe;

#अगर defined(CONFIG_MEDIA_CONTROLLER)
	काष्ठा media_device *mdev;
#पूर्ण_अगर

	अचिन्हित पूर्णांक inversion:1;
	अचिन्हित पूर्णांक करोnt_load_firmware:1;

	u8 अगर_port;
पूर्ण;

#पूर्ण_अगर
