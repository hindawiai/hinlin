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

#समावेश "ia_css_device_access.h"
#समावेश <type_support.h>   /* क्रम uपूर्णांक*, माप_प्रकार */
#समावेश <प्रणाली_local.h>   /* क्रम hrt_address */
#समावेश <ia_css_env.h>     /* क्रम ia_css_hw_access_env */
#समावेश <निश्चित_support.h> /* क्रम निश्चित */

अटल काष्ठा ia_css_hw_access_env my_env;

व्योम
ia_css_device_access_init(स्थिर काष्ठा ia_css_hw_access_env *env)
अणु
	निश्चित(env);

	my_env = *env;
पूर्ण

uपूर्णांक8_t
ia_css_device_load_uपूर्णांक8(स्थिर hrt_address addr)
अणु
	वापस my_env.load_8(addr);
पूर्ण

uपूर्णांक16_t
ia_css_device_load_uपूर्णांक16(स्थिर hrt_address addr)
अणु
	वापस my_env.load_16(addr);
पूर्ण

uपूर्णांक32_t
ia_css_device_load_uपूर्णांक32(स्थिर hrt_address addr)
अणु
	वापस my_env.load_32(addr);
पूर्ण

uपूर्णांक64_t
ia_css_device_load_uपूर्णांक64(स्थिर hrt_address addr)
अणु
	निश्चित(0);

	(व्योम)addr;
	वापस 0;
पूर्ण

व्योम
ia_css_device_store_uपूर्णांक8(स्थिर hrt_address addr, स्थिर uपूर्णांक8_t data)
अणु
	my_env.store_8(addr, data);
पूर्ण

व्योम
ia_css_device_store_uपूर्णांक16(स्थिर hrt_address addr, स्थिर uपूर्णांक16_t data)
अणु
	my_env.store_16(addr, data);
पूर्ण

व्योम
ia_css_device_store_uपूर्णांक32(स्थिर hrt_address addr, स्थिर uपूर्णांक32_t data)
अणु
	my_env.store_32(addr, data);
पूर्ण

व्योम
ia_css_device_store_uपूर्णांक64(स्थिर hrt_address addr, स्थिर uपूर्णांक64_t data)
अणु
	निश्चित(0);

	(व्योम)addr;
	(व्योम)data;
पूर्ण

व्योम
ia_css_device_load(स्थिर hrt_address addr, व्योम *data, स्थिर माप_प्रकार size)
अणु
	my_env.load(addr, data, (uपूर्णांक32_t)size);
पूर्ण

व्योम
ia_css_device_store(स्थिर hrt_address addr, स्थिर व्योम *data, स्थिर माप_प्रकार size)
अणु
	my_env.store(addr, data, (uपूर्णांक32_t)size);
पूर्ण
