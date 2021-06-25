<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * comedi/drivers/amplc_dपन.स
 *
 * Header क्रम amplc_dio200.c, amplc_dio200_common.c and
 * amplc_dio200_pci.c.
 *
 * Copyright (C) 2005-2013 MEV Ltd. <https://www.mev.co.uk/>
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1998,2000 David A. Schleef <ds@schleef.org>
 */

#अगर_अघोषित AMPLC_DIO200_H_INCLUDED
#घोषणा AMPLC_DIO200_H_INCLUDED

#समावेश <linux/types.h>

काष्ठा comedi_device;

/*
 * Subdevice types.
 */
क्रमागत dio200_sdtype अणु sd_none, sd_पूर्णांकr, sd_8255, sd_8254, sd_समयr पूर्ण;

#घोषणा DIO200_MAX_SUBDEVS	8
#घोषणा DIO200_MAX_ISNS		6

काष्ठा dio200_board अणु
	स्थिर अक्षर *name;
	अचिन्हित अक्षर मुख्यbar;
	अचिन्हित लघु n_subdevs;	/* number of subdevices */
	अचिन्हित अक्षर sdtype[DIO200_MAX_SUBDEVS];	/* क्रमागत dio200_sdtype */
	अचिन्हित अक्षर sdinfo[DIO200_MAX_SUBDEVS];	/* depends on sdtype */
	अचिन्हित पूर्णांक has_पूर्णांक_sce:1;	/* has पूर्णांकerrupt enable/status reg */
	अचिन्हित पूर्णांक has_clk_gat_sce:1;	/* has घड़ी/gate selection रेजिस्टरs */
	अचिन्हित पूर्णांक is_pcie:1;			/* has enhanced features */
पूर्ण;

पूर्णांक amplc_dio200_common_attach(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक irq,
			       अचिन्हित दीर्घ req_irq_flags);

/* Used by initialization of PCIe boards. */
व्योम amplc_dio200_set_enhance(काष्ठा comedi_device *dev, अचिन्हित अक्षर val);

#पूर्ण_अगर
