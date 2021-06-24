<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2015-2017 Pengutronix, Uwe Kleine-Kथघnig <kernel@pengutronix.de>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/siox.h>

#घोषणा to_siox_master(_dev)	container_of((_dev), काष्ठा siox_master, dev)
काष्ठा siox_master अणु
	/* these fields should be initialized by the driver */
	पूर्णांक busno;
	पूर्णांक (*pushpull)(काष्ठा siox_master *smaster,
			माप_प्रकार रखो_बफ_len, स्थिर u8 रखो_बफ[],
			माप_प्रकार getbuf_len, u8 getbuf[]);

	/* might be initialized by the driver, अगर 0 it is set to HZ / 40 */
	अचिन्हित दीर्घ poll_पूर्णांकerval; /* in jअगरfies */

	/* framework निजी stuff */
	काष्ठा mutex lock;
	bool active;
	काष्ठा module *owner;
	काष्ठा device dev;
	अचिन्हित पूर्णांक num_devices;
	काष्ठा list_head devices;

	माप_प्रकार रखो_बफ_len, getbuf_len;
	माप_प्रकार buf_len;
	u8 *buf;
	u8 status;

	अचिन्हित दीर्घ last_poll;
	काष्ठा task_काष्ठा *poll_thपढ़ो;
पूर्ण;

अटल अंतरभूत व्योम *siox_master_get_devdata(काष्ठा siox_master *smaster)
अणु
	वापस dev_get_drvdata(&smaster->dev);
पूर्ण

काष्ठा siox_master *siox_master_alloc(काष्ठा device *dev, माप_प्रकार size);
अटल अंतरभूत व्योम siox_master_put(काष्ठा siox_master *smaster)
अणु
	put_device(&smaster->dev);
पूर्ण

पूर्णांक siox_master_रेजिस्टर(काष्ठा siox_master *smaster);
व्योम siox_master_unरेजिस्टर(काष्ठा siox_master *smaster);
