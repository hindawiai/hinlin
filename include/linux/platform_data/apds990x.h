<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of the APDS990x sensor driver.
 * Chip is combined proximity and ambient light sensor.
 *
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * Contact: Samu Onkalo <samu.p.onkalo@nokia.com>
 */

#अगर_अघोषित __APDS990X_H__
#घोषणा __APDS990X_H__


#घोषणा APDS_IRLED_CURR_12mA	0x3
#घोषणा APDS_IRLED_CURR_25mA	0x2
#घोषणा APDS_IRLED_CURR_50mA	0x1
#घोषणा APDS_IRLED_CURR_100mA	0x0

/**
 * काष्ठा apds990x_chip_factors - defines effect of the cover winकरोw
 * @ga: Total glass attenuation
 * @cf1: clear channel factor 1 क्रम raw to lux conversion
 * @irf1: IR channel factor 1 क्रम raw to lux conversion
 * @cf2: clear channel factor 2 क्रम raw to lux conversion
 * @irf2: IR channel factor 2 क्रम raw to lux conversion
 * @df: device factor क्रम conversion क्रमmulas
 *
 * Structure क्रम tuning ALS calculation to match with environment.
 * Values depend on the material above the sensor and the sensor
 * itself. If the GA is zero, driver will use uncovered sensor शेष values
 * क्रमmat: decimal value * APDS_PARAM_SCALE except df which is plain पूर्णांकeger.
 */
#घोषणा APDS_PARAM_SCALE 4096
काष्ठा apds990x_chip_factors अणु
	पूर्णांक ga;
	पूर्णांक cf1;
	पूर्णांक irf1;
	पूर्णांक cf2;
	पूर्णांक irf2;
	पूर्णांक df;
पूर्ण;

/**
 * काष्ठा apds990x_platक्रमm_data - platक्रमm data क्रम apsd990x.c driver
 * @cf: chip factor data
 * @pddrive: IR-led driving current
 * @ppcount: number of IR pulses used क्रम proximity estimation
 * @setup_resources: पूर्णांकerrupt line setup call back function
 * @release_resources: पूर्णांकerrupt line release call back function
 *
 * Proximity detection result depends heavily on correct ppcount, pdrive
 * and cover winकरोw.
 *
 */

काष्ठा apds990x_platक्रमm_data अणु
	काष्ठा apds990x_chip_factors cf;
	u8     pdrive;
	u8     ppcount;
	पूर्णांक    (*setup_resources)(व्योम);
	पूर्णांक    (*release_resources)(व्योम);
पूर्ण;

#पूर्ण_अगर
