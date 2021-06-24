<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * comedi_pcmcia.h
 * header file क्रम Comedi PCMCIA drivers
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1997-2000 David A. Schleef <ds@schleef.org>
 */

#अगर_अघोषित _COMEDI_PCMCIA_H
#घोषणा _COMEDI_PCMCIA_H

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ds.h>

#समावेश "comedidev.h"

काष्ठा pcmcia_device *comedi_to_pcmcia_dev(काष्ठा comedi_device *dev);

पूर्णांक comedi_pcmcia_enable(काष्ठा comedi_device *dev,
			 पूर्णांक (*conf_check)(काष्ठा pcmcia_device *p_dev,
					   व्योम *priv_data));
व्योम comedi_pcmcia_disable(काष्ठा comedi_device *dev);

पूर्णांक comedi_pcmcia_स्वतः_config(काष्ठा pcmcia_device *link,
			      काष्ठा comedi_driver *driver);
व्योम comedi_pcmcia_स्वतः_unconfig(काष्ठा pcmcia_device *link);

पूर्णांक comedi_pcmcia_driver_रेजिस्टर(काष्ठा comedi_driver *comedi_driver,
				  काष्ठा pcmcia_driver *pcmcia_driver);
व्योम comedi_pcmcia_driver_unरेजिस्टर(काष्ठा comedi_driver *comedi_driver,
				     काष्ठा pcmcia_driver *pcmcia_driver);

/**
 * module_comedi_pcmcia_driver() - Helper macro क्रम रेजिस्टरing a comedi
 * PCMCIA driver
 * @__comedi_driver: comedi_driver काष्ठा
 * @__pcmcia_driver: pcmcia_driver काष्ठा
 *
 * Helper macro क्रम comedi PCMCIA drivers which करो not करो anything special
 * in module init/निकास. This eliminates a lot of boilerplate. Each
 * module may only use this macro once, and calling it replaces
 * module_init() and module_निकास()
 */
#घोषणा module_comedi_pcmcia_driver(__comedi_driver, __pcmcia_driver) \
	module_driver(__comedi_driver, comedi_pcmcia_driver_रेजिस्टर, \
			comedi_pcmcia_driver_unरेजिस्टर, &(__pcmcia_driver))

#पूर्ण_अगर /* _COMEDI_PCMCIA_H */
