<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SH Pin Function Control Initialization
 *
 * Copyright (C) 2012  Renesas Solutions Corp.
 */

#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <cpu/pfc.h>

अटल काष्ठा platक्रमm_device sh_pfc_device = अणु
	.id		= -1,
पूर्ण;

पूर्णांक __init sh_pfc_रेजिस्टर(स्थिर अक्षर *name,
			   काष्ठा resource *resource, u32 num_resources)
अणु
	sh_pfc_device.name = name;
	sh_pfc_device.num_resources = num_resources;
	sh_pfc_device.resource = resource;

	वापस platक्रमm_device_रेजिस्टर(&sh_pfc_device);
पूर्ण
