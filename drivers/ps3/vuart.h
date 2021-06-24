<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  PS3 भव uart
 *
 *  Copyright (C) 2006 Sony Computer Entertainment Inc.
 *  Copyright 2006 Sony Corp.
 */

#अगर !defined(_PS3_VUART_H)
#घोषणा _PS3_VUART_H

#समावेश <यंत्र/ps3.h>

काष्ठा ps3_vuart_stats अणु
	अचिन्हित दीर्घ bytes_written;
	अचिन्हित दीर्घ bytes_पढ़ो;
	अचिन्हित दीर्घ tx_पूर्णांकerrupts;
	अचिन्हित दीर्घ rx_पूर्णांकerrupts;
	अचिन्हित दीर्घ disconnect_पूर्णांकerrupts;
पूर्ण;

काष्ठा ps3_vuart_work अणु
	काष्ठा work_काष्ठा work;
	अचिन्हित दीर्घ trigger;
	काष्ठा ps3_प्रणाली_bus_device *dev; /* to convert work to device */
पूर्ण;

/**
 * काष्ठा ps3_vuart_port_driver - a driver क्रम a device on a vuart port
 */

काष्ठा ps3_vuart_port_driver अणु
	काष्ठा ps3_प्रणाली_bus_driver core;
	पूर्णांक (*probe)(काष्ठा ps3_प्रणाली_bus_device *);
	पूर्णांक (*हटाओ)(काष्ठा ps3_प्रणाली_bus_device *);
	व्योम (*shutकरोwn)(काष्ठा ps3_प्रणाली_bus_device *);
	व्योम (*work)(काष्ठा ps3_प्रणाली_bus_device *);
	/* पूर्णांक (*tx_event)(काष्ठा ps3_प्रणाली_bus_device *dev); */
	/* पूर्णांक (*rx_event)(काष्ठा ps3_प्रणाली_bus_device *dev); */
	/* पूर्णांक (*disconnect_event)(काष्ठा ps3_प्रणाली_bus_device *dev); */
	/* पूर्णांक (*suspend)(काष्ठा ps3_प्रणाली_bus_device *, pm_message_t); */
	/* पूर्णांक (*resume)(काष्ठा ps3_प्रणाली_bus_device *); */
पूर्ण;

पूर्णांक ps3_vuart_port_driver_रेजिस्टर(काष्ठा ps3_vuart_port_driver *drv);
व्योम ps3_vuart_port_driver_unरेजिस्टर(काष्ठा ps3_vuart_port_driver *drv);

अटल अंतरभूत काष्ठा ps3_vuart_port_driver *
	ps3_प्रणाली_bus_dev_to_vuart_drv(काष्ठा ps3_प्रणाली_bus_device *_dev)
अणु
	काष्ठा ps3_प्रणाली_bus_driver *sbd =
		ps3_प्रणाली_bus_dev_to_प्रणाली_bus_drv(_dev);
	BUG_ON(!sbd);
	वापस container_of(sbd, काष्ठा ps3_vuart_port_driver, core);
पूर्ण
अटल अंतरभूत काष्ठा ps3_प्रणाली_bus_device *ps3_vuart_work_to_प्रणाली_bus_dev(
	काष्ठा work_काष्ठा *_work)
अणु
	काष्ठा ps3_vuart_work *vw = container_of(_work, काष्ठा ps3_vuart_work,
		work);
	वापस vw->dev;
पूर्ण

पूर्णांक ps3_vuart_ग_लिखो(काष्ठा ps3_प्रणाली_bus_device *dev, स्थिर व्योम *buf,
	अचिन्हित पूर्णांक bytes);
पूर्णांक ps3_vuart_पढ़ो(काष्ठा ps3_प्रणाली_bus_device *dev, व्योम *buf,
	अचिन्हित पूर्णांक bytes);
पूर्णांक ps3_vuart_पढ़ो_async(काष्ठा ps3_प्रणाली_bus_device *dev, अचिन्हित पूर्णांक bytes);
व्योम ps3_vuart_cancel_async(काष्ठा ps3_प्रणाली_bus_device *dev);
व्योम ps3_vuart_clear_rx_bytes(काष्ठा ps3_प्रणाली_bus_device *dev,
	अचिन्हित पूर्णांक bytes);

काष्ठा vuart_triggers अणु
	अचिन्हित दीर्घ rx;
	अचिन्हित दीर्घ tx;
पूर्ण;

पूर्णांक ps3_vuart_get_triggers(काष्ठा ps3_प्रणाली_bus_device *dev,
	काष्ठा vuart_triggers *trig);
पूर्णांक ps3_vuart_set_triggers(काष्ठा ps3_प्रणाली_bus_device *dev, अचिन्हित पूर्णांक tx,
	अचिन्हित पूर्णांक rx);
पूर्णांक ps3_vuart_enable_पूर्णांकerrupt_tx(काष्ठा ps3_प्रणाली_bus_device *dev);
पूर्णांक ps3_vuart_disable_पूर्णांकerrupt_tx(काष्ठा ps3_प्रणाली_bus_device *dev);
पूर्णांक ps3_vuart_enable_पूर्णांकerrupt_rx(काष्ठा ps3_प्रणाली_bus_device *dev);
पूर्णांक ps3_vuart_disable_पूर्णांकerrupt_rx(काष्ठा ps3_प्रणाली_bus_device *dev);
पूर्णांक ps3_vuart_enable_पूर्णांकerrupt_disconnect(काष्ठा ps3_प्रणाली_bus_device *dev);
पूर्णांक ps3_vuart_disable_पूर्णांकerrupt_disconnect(काष्ठा ps3_प्रणाली_bus_device *dev);

#पूर्ण_अगर
