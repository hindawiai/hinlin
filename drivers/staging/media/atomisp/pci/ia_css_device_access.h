<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
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

#अगर_अघोषित _IA_CSS_DEVICE_ACCESS_H
#घोषणा _IA_CSS_DEVICE_ACCESS_H

/* @file
 * File containing पूर्णांकernal functions क्रम the CSS-API to access the CSS device.
 */

#समावेश <type_support.h> /* क्रम uपूर्णांक*, माप_प्रकार */
#समावेश <प्रणाली_local.h> /* क्रम hrt_address */
#समावेश <ia_css_env.h>   /* क्रम ia_css_hw_access_env */

व्योम
ia_css_device_access_init(स्थिर काष्ठा ia_css_hw_access_env *env);

uपूर्णांक8_t
ia_css_device_load_uपूर्णांक8(स्थिर hrt_address addr);

uपूर्णांक16_t
ia_css_device_load_uपूर्णांक16(स्थिर hrt_address addr);

uपूर्णांक32_t
ia_css_device_load_uपूर्णांक32(स्थिर hrt_address addr);

uपूर्णांक64_t
ia_css_device_load_uपूर्णांक64(स्थिर hrt_address addr);

व्योम
ia_css_device_store_uपूर्णांक8(स्थिर hrt_address addr, स्थिर uपूर्णांक8_t data);

व्योम
ia_css_device_store_uपूर्णांक16(स्थिर hrt_address addr, स्थिर uपूर्णांक16_t data);

व्योम
ia_css_device_store_uपूर्णांक32(स्थिर hrt_address addr, स्थिर uपूर्णांक32_t data);

व्योम
ia_css_device_store_uपूर्णांक64(स्थिर hrt_address addr, स्थिर uपूर्णांक64_t data);

व्योम
ia_css_device_load(स्थिर hrt_address addr, व्योम *data, स्थिर माप_प्रकार size);

व्योम
ia_css_device_store(स्थिर hrt_address addr, स्थिर व्योम *data,
		    स्थिर माप_प्रकार size);

#पूर्ण_अगर /* _IA_CSS_DEVICE_ACCESS_H */
