<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * HID Sensors Driver
 * Copyright (c) 2012, Intel Corporation.
 */
#अगर_अघोषित _HID_SENSOR_TRIGGER_H
#घोषणा _HID_SENSOR_TRIGGER_H

#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>

बाह्य स्थिर काष्ठा dev_pm_ops hid_sensor_pm_ops;

पूर्णांक hid_sensor_setup_trigger(काष्ठा iio_dev *indio_dev, स्थिर अक्षर *name,
				काष्ठा hid_sensor_common *attrb);
व्योम hid_sensor_हटाओ_trigger(काष्ठा iio_dev *indio_dev,
			       काष्ठा hid_sensor_common *attrb);
पूर्णांक hid_sensor_घातer_state(काष्ठा hid_sensor_common *st, bool state);

#पूर्ण_अगर
