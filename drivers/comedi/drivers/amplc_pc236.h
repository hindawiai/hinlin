<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * comedi/drivers/amplc_pc236.h
 * Header क्रम "amplc_pc236", "amplc_pci236" and "amplc_pc236_common".
 *
 * Copyright (C) 2002-2014 MEV Ltd. <https://www.mev.co.uk/>
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */

#अगर_अघोषित AMPLC_PC236_H_INCLUDED
#घोषणा AMPLC_PC236_H_INCLUDED

#समावेश <linux/types.h>

काष्ठा comedi_device;

काष्ठा pc236_board अणु
	स्थिर अक्षर *name;
	व्योम (*पूर्णांकr_update_cb)(काष्ठा comedi_device *dev, bool enable);
	bool (*पूर्णांकr_chk_clr_cb)(काष्ठा comedi_device *dev);
पूर्ण;

काष्ठा pc236_निजी अणु
	अचिन्हित दीर्घ lcr_iobase; /* PLX PCI9052 config रेजिस्टरs in PCIBAR1 */
	bool enable_irq;
पूर्ण;

पूर्णांक amplc_pc236_common_attach(काष्ठा comedi_device *dev, अचिन्हित दीर्घ iobase,
			      अचिन्हित पूर्णांक irq, अचिन्हित दीर्घ req_irq_flags);

#पूर्ण_अगर
