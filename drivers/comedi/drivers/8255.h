<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * module/8255.h
 * Header file क्रम 8255
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1998 David A. Schleef <ds@schleef.org>
 */

#अगर_अघोषित _8255_H
#घोषणा _8255_H

#घोषणा I8255_SIZE		0x04

#घोषणा I8255_DATA_A_REG	0x00
#घोषणा I8255_DATA_B_REG	0x01
#घोषणा I8255_DATA_C_REG	0x02
#घोषणा I8255_CTRL_REG		0x03
#घोषणा I8255_CTRL_C_LO_IO	BIT(0)
#घोषणा I8255_CTRL_B_IO		BIT(1)
#घोषणा I8255_CTRL_B_MODE	BIT(2)
#घोषणा I8255_CTRL_C_HI_IO	BIT(3)
#घोषणा I8255_CTRL_A_IO		BIT(4)
#घोषणा I8255_CTRL_A_MODE(x)	((x) << 5)
#घोषणा I8255_CTRL_CW		BIT(7)

काष्ठा comedi_device;
काष्ठा comedi_subdevice;

पूर्णांक subdev_8255_init(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
		     पूर्णांक (*io)(काष्ठा comedi_device *dev, पूर्णांक dir, पूर्णांक port,
			       पूर्णांक data, अचिन्हित दीर्घ regbase),
		     अचिन्हित दीर्घ regbase);

पूर्णांक subdev_8255_mm_init(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
			पूर्णांक (*io)(काष्ठा comedi_device *dev, पूर्णांक dir, पूर्णांक port,
				  पूर्णांक data, अचिन्हित दीर्घ regbase),
			अचिन्हित दीर्घ regbase);

अचिन्हित दीर्घ subdev_8255_regbase(काष्ठा comedi_subdevice *s);

#पूर्ण_अगर
