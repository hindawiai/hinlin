<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause */
/*
 * Copyright (c) 2020, MIPI Alliance, Inc.
 *
 * Author: Nicolas Pitre <npitre@baylibre.com>
 *
 * Common IBI related stuff
 */

#अगर_अघोषित IBI_H
#घोषणा IBI_H

/*
 * IBI Status Descriptor bits
 */
#घोषणा IBI_STS				BIT(31)
#घोषणा IBI_ERROR			BIT(30)
#घोषणा IBI_STATUS_TYPE			BIT(29)
#घोषणा IBI_HW_CONTEXT			GENMASK(28, 26)
#घोषणा IBI_TS				BIT(25)
#घोषणा IBI_LAST_STATUS			BIT(24)
#घोषणा IBI_CHUNKS			GENMASK(23, 16)
#घोषणा IBI_ID				GENMASK(15, 8)
#घोषणा IBI_TARGET_ADDR			GENMASK(15, 9)
#घोषणा IBI_TARGET_RNW			BIT(8)
#घोषणा IBI_DATA_LENGTH			GENMASK(7, 0)

/*  handy helpers */
अटल अंतरभूत काष्ठा i3c_dev_desc *
i3c_hci_addr_to_dev(काष्ठा i3c_hci *hci, अचिन्हित पूर्णांक addr)
अणु
	काष्ठा i3c_bus *bus = i3c_master_get_bus(&hci->master);
	काष्ठा i3c_dev_desc *dev;

	i3c_bus_क्रम_each_i3cdev(bus, dev) अणु
		अगर (dev->info.dyn_addr == addr)
			वापस dev;
	पूर्ण
	वापस शून्य;
पूर्ण

#पूर्ण_अगर
