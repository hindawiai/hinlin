<शैली गुरु>
/*
 * Copyright 2012-16 Advanced Micro Devices, Inc.
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
 * Authors: AMD
 *
 */

#अगर_अघोषित __DAL_BIOS_PARSER_HELPER_H__
#घोषणा __DAL_BIOS_PARSER_HELPER_H__

काष्ठा bios_parser;

uपूर्णांक8_t *bios_get_image(काष्ठा dc_bios *bp, uपूर्णांक32_t offset,
	uपूर्णांक32_t size);

bool bios_is_accelerated_mode(काष्ठा dc_bios *bios);
व्योम bios_set_scratch_acc_mode_change(काष्ठा dc_bios *bios, uपूर्णांक32_t state);
व्योम bios_set_scratch_critical_state(काष्ठा dc_bios *bios, bool state);
uपूर्णांक32_t bios_get_vga_enabled_displays(काष्ठा dc_bios *bios);

#घोषणा GET_IMAGE(type, offset) ((type *) bios_get_image(&bp->base, offset, माप(type)))

#पूर्ण_अगर
