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

#अगर_अघोषित _IA_CSS_CIRCBUF_COMM_H
#घोषणा _IA_CSS_CIRCBUF_COMM_H

#समावेश <type_support.h>  /* uपूर्णांक8_t, uपूर्णांक32_t */

#घोषणा IA_CSS_CIRCBUF_PADDING 1 /* The circular buffer is implemented in lock-less manner, wherein
				   * the head and tail can advance independently without any locks.
				   * But to achieve this, an extra buffer element is required to detect
				   * queue full & empty conditions, wherein the tail trails the head क्रम
				   * full and is equal to head क्रम empty condition. This causes 1 buffer
				   * not being available क्रम use.
				   */

/****************************************************************
 *
 * Portable Data काष्ठाures
 *
 ****************************************************************/
/**
 * @brief Data काष्ठाure क्रम the circular descriptor.
 */
प्रकार काष्ठा ia_css_circbuf_desc_s ia_css_circbuf_desc_t;
काष्ठा ia_css_circbuf_desc_s अणु
	u8 size;	/* the maximum number of elements*/
	u8 step;   /* number of bytes per element */
	u8 start;	/* index of the oldest element */
	u8 end;	/* index at which to ग_लिखो the new element */
पूर्ण;

#घोषणा SIZE_OF_IA_CSS_CIRCBUF_DESC_S_STRUCT				\
	(4 * माप(uपूर्णांक8_t))

/**
 * @brief Data काष्ठाure क्रम the circular buffer element.
 */
प्रकार काष्ठा ia_css_circbuf_elem_s ia_css_circbuf_elem_t;
काष्ठा ia_css_circbuf_elem_s अणु
	u32 val;	/* the value stored in the element */
पूर्ण;

#घोषणा SIZE_OF_IA_CSS_CIRCBUF_ELEM_S_STRUCT				\
	(माप(uपूर्णांक32_t))

#पूर्ण_अगर /*_IA_CSS_CIRCBUF_COMM_H*/
