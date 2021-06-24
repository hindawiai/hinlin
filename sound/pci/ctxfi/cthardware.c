<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008, Creative Technology Ltd. All Rights Reserved.
 *
 * @File	cthardware.c
 *
 * @Brief
 * This file contains the implementation of hardware access methord.
 *
 * @Author	Liu Chun
 * @Date 	Jun 26 2008
 */

#समावेश "cthardware.h"
#समावेश "cthw20k1.h"
#समावेश "cthw20k2.h"
#समावेश <linux/bug.h>

पूर्णांक create_hw_obj(काष्ठा pci_dev *pci, क्रमागत CHIPTYP chip_type,
		  क्रमागत CTCARDS model, काष्ठा hw **rhw)
अणु
	पूर्णांक err;

	चयन (chip_type) अणु
	हाल ATC20K1:
		err = create_20k1_hw_obj(rhw);
		अवरोध;
	हाल ATC20K2:
		err = create_20k2_hw_obj(rhw);
		अवरोध;
	शेष:
		err = -ENODEV;
		अवरोध;
	पूर्ण
	अगर (err)
		वापस err;

	(*rhw)->pci = pci;
	(*rhw)->chip_type = chip_type;
	(*rhw)->model = model;

	वापस 0;
पूर्ण

पूर्णांक destroy_hw_obj(काष्ठा hw *hw)
अणु
	पूर्णांक err;

	चयन (hw->pci->device) अणु
	हाल 0x0005:	/* 20k1 device */
		err = destroy_20k1_hw_obj(hw);
		अवरोध;
	हाल 0x000B:	/* 20k2 device */
		err = destroy_20k2_hw_obj(hw);
		अवरोध;
	शेष:
		err = -ENODEV;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अचिन्हित पूर्णांक get_field(अचिन्हित पूर्णांक data, अचिन्हित पूर्णांक field)
अणु
	पूर्णांक i;

	अगर (WARN_ON(!field))
		वापस 0;
	/* @field should always be greater than 0 */
	क्रम (i = 0; !(field & (1 << i)); )
		i++;

	वापस (data & field) >> i;
पूर्ण

व्योम set_field(अचिन्हित पूर्णांक *data, अचिन्हित पूर्णांक field, अचिन्हित पूर्णांक value)
अणु
	पूर्णांक i;

	अगर (WARN_ON(!field))
		वापस;
	/* @field should always be greater than 0 */
	क्रम (i = 0; !(field & (1 << i)); )
		i++;

	*data = (*data & (~field)) | ((value << i) & field);
पूर्ण

