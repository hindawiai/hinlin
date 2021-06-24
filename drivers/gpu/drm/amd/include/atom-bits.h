<शैली गुरु>
/*
 * Copyright 2008 Advanced Micro Devices, Inc.
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
 * Author: Stanislaw Skowronek
 */

#अगर_अघोषित ATOM_BITS_H
#घोषणा ATOM_BITS_H

अटल अंतरभूत uपूर्णांक8_t get_u8(व्योम *bios, पूर्णांक ptr)
अणु
    वापस ((अचिन्हित अक्षर *)bios)[ptr];
पूर्ण
#घोषणा U8(ptr) get_u8(ctx->ctx->bios, (ptr))
#घोषणा CU8(ptr) get_u8(ctx->bios, (ptr))
अटल अंतरभूत uपूर्णांक16_t get_u16(व्योम *bios, पूर्णांक ptr)
अणु
    वापस get_u8(bios ,ptr)|(((uपूर्णांक16_t)get_u8(bios, ptr+1))<<8);
पूर्ण
#घोषणा U16(ptr) get_u16(ctx->ctx->bios, (ptr))
#घोषणा CU16(ptr) get_u16(ctx->bios, (ptr))
अटल अंतरभूत uपूर्णांक32_t get_u32(व्योम *bios, पूर्णांक ptr)
अणु
    वापस get_u16(bios, ptr)|(((uपूर्णांक32_t)get_u16(bios, ptr+2))<<16);
पूर्ण
#घोषणा U32(ptr) get_u32(ctx->ctx->bios, (ptr))
#घोषणा CU32(ptr) get_u32(ctx->bios, (ptr))
#घोषणा CSTR(ptr) (((अक्षर *)(ctx->bios))+(ptr))

#पूर्ण_अगर
