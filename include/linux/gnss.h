<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * GNSS receiver support
 *
 * Copyright (C) 2018 Johan Hovold <johan@kernel.org>
 */

#अगर_अघोषित _LINUX_GNSS_H
#घोषणा _LINUX_GNSS_H

#समावेश <linux/cdev.h>
#समावेश <linux/device.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/types.h>
#समावेश <linux/रुको.h>

काष्ठा gnss_device;

क्रमागत gnss_type अणु
	GNSS_TYPE_NMEA = 0,
	GNSS_TYPE_SIRF,
	GNSS_TYPE_UBX,
	GNSS_TYPE_MTK,

	GNSS_TYPE_COUNT
पूर्ण;

काष्ठा gnss_operations अणु
	पूर्णांक (*खोलो)(काष्ठा gnss_device *gdev);
	व्योम (*बंद)(काष्ठा gnss_device *gdev);
	पूर्णांक (*ग_लिखो_raw)(काष्ठा gnss_device *gdev, स्थिर अचिन्हित अक्षर *buf,
				माप_प्रकार count);
पूर्ण;

काष्ठा gnss_device अणु
	काष्ठा device dev;
	काष्ठा cdev cdev;
	पूर्णांक id;

	क्रमागत gnss_type type;
	अचिन्हित दीर्घ flags;

	काष्ठा rw_semaphore rwsem;
	स्थिर काष्ठा gnss_operations *ops;
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक disconnected:1;

	काष्ठा mutex पढ़ो_mutex;
	काष्ठा kfअगरo पढ़ो_fअगरo;
	रुको_queue_head_t पढ़ो_queue;

	काष्ठा mutex ग_लिखो_mutex;
	अक्षर *ग_लिखो_buf;
पूर्ण;

काष्ठा gnss_device *gnss_allocate_device(काष्ठा device *parent);
व्योम gnss_put_device(काष्ठा gnss_device *gdev);
पूर्णांक gnss_रेजिस्टर_device(काष्ठा gnss_device *gdev);
व्योम gnss_deरेजिस्टर_device(काष्ठा gnss_device *gdev);

पूर्णांक gnss_insert_raw(काष्ठा gnss_device *gdev, स्थिर अचिन्हित अक्षर *buf,
			माप_प्रकार count);

अटल अंतरभूत व्योम gnss_set_drvdata(काष्ठा gnss_device *gdev, व्योम *data)
अणु
	dev_set_drvdata(&gdev->dev, data);
पूर्ण

अटल अंतरभूत व्योम *gnss_get_drvdata(काष्ठा gnss_device *gdev)
अणु
	वापस dev_get_drvdata(&gdev->dev);
पूर्ण

#पूर्ण_अगर /* _LINUX_GNSS_H */
