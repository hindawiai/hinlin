<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
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

#अगर_अघोषित DM_CP_PSP_IF__H
#घोषणा DM_CP_PSP_IF__H

काष्ठा dc_link;

काष्ठा cp_psp_stream_config अणु
	uपूर्णांक8_t otg_inst;
	uपूर्णांक8_t dig_be;
	uपूर्णांक8_t dig_fe;
	uपूर्णांक8_t assr_enabled;
	uपूर्णांक8_t mst_enabled;
	व्योम *dm_stream_ctx;
	bool dpms_off;
पूर्ण;

काष्ठा cp_psp_funcs अणु
	bool (*enable_assr)(व्योम *handle, काष्ठा dc_link *link);
	व्योम (*update_stream_config)(व्योम *handle, काष्ठा cp_psp_stream_config *config);
पूर्ण;

काष्ठा cp_psp अणु
	व्योम *handle;
	काष्ठा cp_psp_funcs funcs;
पूर्ण;


#पूर्ण_अगर /* DM_CP_PSP_IF__H */
