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

#अगर_अघोषित __TAG_PUBLIC_H_INCLUDED__
#घोषणा __TAG_PUBLIC_H_INCLUDED__

/**
 * @brief	Creates the tag description from the given parameters.
 * @param[in]	num_captures
 * @param[in]	skip
 * @param[in]	offset
 * @param[out]	tag_descr
 */
व्योम
sh_css_create_tag_descr(पूर्णांक num_captures,
			अचिन्हित पूर्णांक skip,
			पूर्णांक offset,
			अचिन्हित पूर्णांक exp_id,
			काष्ठा sh_css_tag_descr *tag_descr);

/**
 * @brief	Encodes the members of tag description पूर्णांकo a 32-bit value.
 * @param[in]	tag		Poपूर्णांकer to the tag description
 * @वापस	(अचिन्हित पूर्णांक)	Encoded 32-bit tag-info
 */
अचिन्हित पूर्णांक
sh_css_encode_tag_descr(काष्ठा sh_css_tag_descr *tag);

#पूर्ण_अगर /* __TAG_PUBLIC_H_INCLUDED__ */
