<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * bq2415x अक्षरger driver
 *
 * Copyright (C) 2011-2013  Pali Rohथँr <pali@kernel.org>
 */

#अगर_अघोषित BQ2415X_CHARGER_H
#घोषणा BQ2415X_CHARGER_H

/*
 * This is platक्रमm data क्रम bq2415x chip. It contains शेष board
 * voltages and currents which can be also later configured via sysfs. If
 * value is -1 then शेष chip value (specअगरied in datasheet) will be
 * used.
 *
 * Value resistor_sense is needed क्रम configuring अक्षरge and
 * termination current. If it is less or equal to zero, configuring अक्षरge
 * and termination current will not be possible.
 *
 * For स्वतःmode support is needed to provide name of घातer supply device
 * in value notअगरy_device. Device driver must immediately report property
 * POWER_SUPPLY_PROP_CURRENT_MAX when current changed.
 */

/* Supported modes with maximal current limit */
क्रमागत bq2415x_mode अणु
	BQ2415X_MODE_OFF,		/* offline mode (अक्षरger disabled) */
	BQ2415X_MODE_NONE,		/* unknown अक्षरger (100mA) */
	BQ2415X_MODE_HOST_CHARGER,	/* usb host/hub अक्षरger (500mA) */
	BQ2415X_MODE_DEDICATED_CHARGER, /* dedicated अक्षरger (unlimited) */
	BQ2415X_MODE_BOOST,		/* boost mode (अक्षरging disabled) */
पूर्ण;

काष्ठा bq2415x_platक्रमm_data अणु
	पूर्णांक current_limit;		/* mA */
	पूर्णांक weak_battery_voltage;	/* mV */
	पूर्णांक battery_regulation_voltage;	/* mV */
	पूर्णांक अक्षरge_current;		/* mA */
	पूर्णांक termination_current;	/* mA */
	पूर्णांक resistor_sense;		/* m ohm */
	स्थिर अक्षर *notअगरy_device;	/* name */
पूर्ण;

#पूर्ण_अगर
