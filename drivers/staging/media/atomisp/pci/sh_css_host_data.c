<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#समावेश <linux/slab.h>
#समावेश <ia_css_host_data.h>
#समावेश <sh_css_पूर्णांकernal.h>

काष्ठा ia_css_host_data *ia_css_host_data_allocate(माप_प्रकार size)
अणु
	काष्ठा ia_css_host_data *me;

	me =  kदो_स्मृति(माप(काष्ठा ia_css_host_data), GFP_KERNEL);
	अगर (!me)
		वापस शून्य;
	me->size = (uपूर्णांक32_t)size;
	me->address = kvदो_स्मृति(size, GFP_KERNEL);
	अगर (!me->address) अणु
		kमुक्त(me);
		वापस शून्य;
	पूर्ण
	वापस me;
पूर्ण

व्योम ia_css_host_data_मुक्त(काष्ठा ia_css_host_data *me)
अणु
	अगर (me) अणु
		kvमुक्त(me->address);
		me->address = शून्य;
		kमुक्त(me);
	पूर्ण
पूर्ण
