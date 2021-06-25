<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Generic serial GNSS receiver driver
 *
 * Copyright (C) 2018 Johan Hovold <johan@kernel.org>
 */

#अगर_अघोषित _LINUX_GNSS_SERIAL_H
#घोषणा _LINUX_GNSS_SERIAL_H

#समावेश <यंत्र/termbits.h>
#समावेश <linux/pm.h>

काष्ठा gnss_serial अणु
	काष्ठा serdev_device *serdev;
	काष्ठा gnss_device *gdev;
	speed_t	speed;
	स्थिर काष्ठा gnss_serial_ops *ops;
	अचिन्हित दीर्घ drvdata[];
पूर्ण;

क्रमागत gnss_serial_pm_state अणु
	GNSS_SERIAL_OFF,
	GNSS_SERIAL_ACTIVE,
	GNSS_SERIAL_STANDBY,
पूर्ण;

काष्ठा gnss_serial_ops अणु
	पूर्णांक (*set_घातer)(काष्ठा gnss_serial *gserial,
				क्रमागत gnss_serial_pm_state state);
पूर्ण;

बाह्य स्थिर काष्ठा dev_pm_ops gnss_serial_pm_ops;

काष्ठा gnss_serial *gnss_serial_allocate(काष्ठा serdev_device *gserial,
						माप_प्रकार data_size);
व्योम gnss_serial_मुक्त(काष्ठा gnss_serial *gserial);

पूर्णांक gnss_serial_रेजिस्टर(काष्ठा gnss_serial *gserial);
व्योम gnss_serial_deरेजिस्टर(काष्ठा gnss_serial *gserial);

अटल अंतरभूत व्योम *gnss_serial_get_drvdata(काष्ठा gnss_serial *gserial)
अणु
	वापस gserial->drvdata;
पूर्ण

#पूर्ण_अगर /* _LINUX_GNSS_SERIAL_H */
