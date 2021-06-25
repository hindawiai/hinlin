<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Anybus-S client adapter definitions
 *
 * Copyright 2018 Arcx Inc
 */

#अगर_अघोषित __LINUX_ANYBUSS_CLIENT_H__
#घोषणा __LINUX_ANYBUSS_CLIENT_H__

#समावेश <linux/device.h>
#समावेश <linux/types.h>
#समावेश <linux/poll.h>

/* move to <linux/fieldbus_dev.h> when taking this out of staging */
#समावेश "../fieldbus_dev.h"

काष्ठा anybuss_host;

काष्ठा anybuss_client अणु
	काष्ठा device dev;
	काष्ठा anybuss_host *host;
	__be16 anybus_id;
	/*
	 * these can be optionally set by the client to receive event
	 * notअगरications from the host.
	 */
	व्योम (*on_area_updated)(काष्ठा anybuss_client *client);
	व्योम (*on_online_changed)(काष्ठा anybuss_client *client, bool online);
पूर्ण;

काष्ठा anybuss_client_driver अणु
	काष्ठा device_driver driver;
	पूर्णांक (*probe)(काष्ठा anybuss_client *adev);
	पूर्णांक (*हटाओ)(काष्ठा anybuss_client *adev);
	u16 anybus_id;
पूर्ण;

पूर्णांक anybuss_client_driver_रेजिस्टर(काष्ठा anybuss_client_driver *drv);
व्योम anybuss_client_driver_unरेजिस्टर(काष्ठा anybuss_client_driver *drv);

अटल अंतरभूत काष्ठा anybuss_client *to_anybuss_client(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा anybuss_client, dev);
पूर्ण

अटल अंतरभूत काष्ठा anybuss_client_driver *
to_anybuss_client_driver(काष्ठा device_driver *drv)
अणु
	वापस container_of(drv, काष्ठा anybuss_client_driver, driver);
पूर्ण

अटल अंतरभूत व्योम *
anybuss_get_drvdata(स्थिर काष्ठा anybuss_client *client)
अणु
	वापस dev_get_drvdata(&client->dev);
पूर्ण

अटल अंतरभूत व्योम
anybuss_set_drvdata(काष्ठा anybuss_client *client, व्योम *data)
अणु
	dev_set_drvdata(&client->dev, data);
पूर्ण

पूर्णांक anybuss_set_घातer(काष्ठा anybuss_client *client, bool घातer_on);

काष्ठा anybuss_memcfg अणु
	u16 input_io;
	u16 input_dpram;
	u16 input_total;

	u16 output_io;
	u16 output_dpram;
	u16 output_total;

	क्रमागत fieldbus_dev_offl_mode offl_mode;
पूर्ण;

पूर्णांक anybuss_start_init(काष्ठा anybuss_client *client,
		       स्थिर काष्ठा anybuss_memcfg *cfg);
पूर्णांक anybuss_finish_init(काष्ठा anybuss_client *client);
पूर्णांक anybuss_पढ़ो_fbctrl(काष्ठा anybuss_client *client, u16 addr,
			व्योम *buf, माप_प्रकार count);
पूर्णांक anybuss_send_msg(काष्ठा anybuss_client *client, u16 cmd_num,
		     स्थिर व्योम *buf, माप_प्रकार count);
पूर्णांक anybuss_send_ext(काष्ठा anybuss_client *client, u16 cmd_num,
		     स्थिर व्योम *buf, माप_प्रकार count);
पूर्णांक anybuss_recv_msg(काष्ठा anybuss_client *client, u16 cmd_num,
		     व्योम *buf, माप_प्रकार count);

/* these help clients make a काष्ठा file_operations */
पूर्णांक anybuss_ग_लिखो_input(काष्ठा anybuss_client *client,
			स्थिर अक्षर __user *buf, माप_प्रकार size,
				loff_t *offset);
पूर्णांक anybuss_पढ़ो_output(काष्ठा anybuss_client *client,
			अक्षर __user *buf, माप_प्रकार size,
				loff_t *offset);

#पूर्ण_अगर /* __LINUX_ANYBUSS_CLIENT_H__ */
