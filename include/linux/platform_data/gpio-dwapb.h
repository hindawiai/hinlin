<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright(c) 2014 Intel Corporation.
 */

#अगर_अघोषित GPIO_DW_APB_H
#घोषणा GPIO_DW_APB_H

#घोषणा DWAPB_MAX_GPIOS		32

काष्ठा dwapb_port_property अणु
	काष्ठा fwnode_handle *fwnode;
	अचिन्हित पूर्णांक	idx;
	अचिन्हित पूर्णांक	ngpio;
	अचिन्हित पूर्णांक	gpio_base;
	पूर्णांक		irq[DWAPB_MAX_GPIOS];
	bool		irq_shared;
पूर्ण;

काष्ठा dwapb_platक्रमm_data अणु
	काष्ठा dwapb_port_property *properties;
	अचिन्हित पूर्णांक nports;
पूर्ण;

#पूर्ण_अगर
