<शैली गुरु>
/*
 * Copyright 2018 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Lyude Paul
 */

#अगर_अघोषित __GK104_THERM_H__
#घोषणा __GK104_THERM_H__
#घोषणा gk104_therm(p) (container_of((p), काष्ठा gk104_therm, base))

#समावेश <subdev/therm.h>
#समावेश "priv.h"
#समावेश "gf100.h"

काष्ठा gk104_clkgate_engine_info अणु
	क्रमागत nvkm_subdev_type type;
	पूर्णांक inst;
	u8 offset;
पूर्ण;

काष्ठा gk104_therm अणु
	काष्ठा nvkm_therm base;

	स्थिर काष्ठा gk104_clkgate_engine_info *clkgate_order;
	स्थिर काष्ठा gf100_idle_filter *idle_filter;
पूर्ण;

बाह्य स्थिर काष्ठा gk104_clkgate_engine_info gk104_clkgate_engine_info[];
बाह्य स्थिर काष्ठा gf100_idle_filter gk104_idle_filter;

#पूर्ण_अगर
