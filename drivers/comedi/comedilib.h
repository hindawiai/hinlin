<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * comedilib.h
 * Header file क्रम kcomedilib
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1998-2001 David A. Schleef <ds@schleef.org>
 */

#अगर_अघोषित _LINUX_COMEDILIB_H
#घोषणा _LINUX_COMEDILIB_H

काष्ठा comedi_device *comedi_खोलो(स्थिर अक्षर *path);
पूर्णांक comedi_बंद(काष्ठा comedi_device *dev);
पूर्णांक comedi_dio_get_config(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक subdev,
			  अचिन्हित पूर्णांक chan, अचिन्हित पूर्णांक *io);
पूर्णांक comedi_dio_config(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक subdev,
		      अचिन्हित पूर्णांक chan, अचिन्हित पूर्णांक io);
पूर्णांक comedi_dio_bitfield2(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक subdev,
			 अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक *bits,
			 अचिन्हित पूर्णांक base_channel);
पूर्णांक comedi_find_subdevice_by_type(काष्ठा comedi_device *dev, पूर्णांक type,
				  अचिन्हित पूर्णांक subd);
पूर्णांक comedi_get_n_channels(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक subdevice);

#पूर्ण_अगर
