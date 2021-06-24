<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * USB Driver क्रम ALi m5602 based webcams
 *
 * Copyright (C) 2008 Erik Andrथऊn
 * Copyright (C) 2007 Ilyes Gouta. Based on the m5603x Linux Driver Project.
 * Copyright (C) 2005 m5603x Linux Driver Project <m5602@x3ng.com.br>
 *
 * Portions of code to USB पूर्णांकerface and ALi driver software,
 * Copyright (c) 2006 Willem Duinker
 * v4l2 पूर्णांकerface modeled after the V4L2 driver
 * क्रम SN9C10x PC Camera Controllers
 */

#अगर_अघोषित M5602_SENSOR_H_
#घोषणा M5602_SENSOR_H_

#समावेश "m5602_bridge.h"

#घोषणा M5602_V4L2_CID_GREEN_BALANCE	(V4L2_CID_PRIVATE_BASE + 0)
#घोषणा M5602_V4L2_CID_NOISE_SUPPRESION	(V4L2_CID_PRIVATE_BASE + 1)

/* Enumerates all supported sensors */
क्रमागत sensors अणु
	OV9650_SENSOR	= 1,
	S5K83A_SENSOR	= 2,
	S5K4AA_SENSOR	= 3,
	MT9M111_SENSOR	= 4,
	PO1030_SENSOR	= 5,
	OV7660_SENSOR   = 6,
पूर्ण;

/* Enumerates all possible inकाष्ठाion types */
क्रमागत inकाष्ठाion अणु
	BRIDGE,
	SENSOR,
	SENSOR_LONG
पूर्ण;

काष्ठा m5602_sensor अणु
	/* Defines the name of a sensor */
	अक्षर name[32];

	/* What i2c address the sensor is connected to */
	u8 i2c_slave_id;

	/* Width of each i2c रेजिस्टर (in bytes) */
	u8 i2c_regW;

	/* Probes अगर the sensor is connected */
	पूर्णांक (*probe)(काष्ठा sd *sd);

	/* Perक्रमms a initialization sequence */
	पूर्णांक (*init)(काष्ठा sd *sd);

	/* Controls initialization, maybe शून्य */
	पूर्णांक (*init_controls)(काष्ठा sd *sd);

	/* Executed when the camera starts to send data */
	पूर्णांक (*start)(काष्ठा sd *sd);

	/* Executed when the camera ends to send data */
	पूर्णांक (*stop)(काष्ठा sd *sd);

	/* Executed when the device is disconnected */
	व्योम (*disconnect)(काष्ठा sd *sd);
पूर्ण;

#पूर्ण_अगर
