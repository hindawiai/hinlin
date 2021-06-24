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

#समावेश "tag.h"
#समावेश <platक्रमm_support.h>	/* शून्य */
#समावेश <निश्चित_support.h>
#समावेश "tag_local.h"

/*
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
			काष्ठा sh_css_tag_descr *tag_descr)
अणु
	निश्चित(tag_descr);

	tag_descr->num_captures = num_captures;
	tag_descr->skip		= skip;
	tag_descr->offset	= offset;
	tag_descr->exp_id	= exp_id;
पूर्ण

/*
 * @brief	Encodes the members of tag description पूर्णांकo a 32-bit value.
 * @param[in]	tag		Poपूर्णांकer to the tag description
 * @वापस	(अचिन्हित पूर्णांक)	Encoded 32-bit tag-info
 */
अचिन्हित पूर्णांक
sh_css_encode_tag_descr(काष्ठा sh_css_tag_descr *tag)
अणु
	पूर्णांक num_captures;
	अचिन्हित पूर्णांक num_captures_sign;
	अचिन्हित पूर्णांक skip;
	पूर्णांक offset;
	अचिन्हित पूर्णांक offset_sign;
	अचिन्हित पूर्णांक exp_id;
	अचिन्हित पूर्णांक encoded_tag;

	निश्चित(tag);

	अगर (tag->num_captures < 0) अणु
		num_captures = -tag->num_captures;
		num_captures_sign = 1;
	पूर्ण अन्यथा अणु
		num_captures = tag->num_captures;
		num_captures_sign = 0;
	पूर्ण
	skip = tag->skip;
	अगर (tag->offset < 0) अणु
		offset = -tag->offset;
		offset_sign = 1;
	पूर्ण अन्यथा अणु
		offset = tag->offset;
		offset_sign = 0;
	पूर्ण
	exp_id = tag->exp_id;

	अगर (exp_id != 0) अणु
		/* we encode either an exp_id or capture data */
		निश्चित((num_captures == 0) && (skip == 0) && (offset == 0));

		encoded_tag = TAG_EXP | (exp_id & 0xFF) << TAG_EXP_ID_SHIFT;
	पूर्ण अन्यथा अणु
		encoded_tag = TAG_CAP
			      | ((num_captures_sign & 0x00000001) << TAG_NUM_CAPTURES_SIGN_SHIFT)
			      | ((offset_sign       & 0x00000001) << TAG_OFFSET_SIGN_SHIFT)
			      | ((num_captures      & 0x000000FF) << TAG_NUM_CAPTURES_SHIFT)
			      | ((skip              & 0x000000FF) << TAG_OFFSET_SHIFT)
			      | ((offset            & 0x000000FF) << TAG_SKIP_SHIFT);
	पूर्ण
	वापस encoded_tag;
पूर्ण
