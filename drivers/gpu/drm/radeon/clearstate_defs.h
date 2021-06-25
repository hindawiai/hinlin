<शैली गुरु>
/*
 * Copyright 2012 Advanced Micro Devices, Inc.
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
 */
#अगर_अघोषित CLEARSTATE_DEFS_H
#घोषणा CLEARSTATE_DEFS_H

क्रमागत section_id अणु
    SECT_NONE,
    SECT_CONTEXT,
    SECT_CLEAR,
    SECT_CTRLCONST
पूर्ण;

काष्ठा cs_extent_def अणु
    स्थिर अचिन्हित पूर्णांक *extent;
    स्थिर अचिन्हित पूर्णांक reg_index;
    स्थिर अचिन्हित पूर्णांक reg_count;
पूर्ण;

काष्ठा cs_section_def अणु
    स्थिर काष्ठा cs_extent_def *section;
    स्थिर क्रमागत section_id id;
पूर्ण;

#पूर्ण_अगर
