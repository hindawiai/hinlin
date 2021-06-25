<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
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
 * Interface Functions related to the BIOS PowerPlay Tables.
 *
 */

#अगर_अघोषित PROCESSPPTABLES_H
#घोषणा PROCESSPPTABLES_H

काष्ठा pp_hwmgr;
काष्ठा pp_घातer_state;
काष्ठा pp_hw_घातer_state;

बाह्य स्थिर काष्ठा pp_table_func pptable_funcs;

प्रकार पूर्णांक (*pp_tables_hw_घड़ी_info_callback)(काष्ठा pp_hwmgr *hwmgr,
						काष्ठा pp_hw_घातer_state *hw_ps,
						अचिन्हित पूर्णांक index,
						स्थिर व्योम *घड़ी_info);

पूर्णांक pp_tables_get_num_of_entries(काष्ठा pp_hwmgr *hwmgr,
				 अचिन्हित दीर्घ *num_of_entries);

पूर्णांक pp_tables_get_entry(काष्ठा pp_hwmgr *hwmgr,
			अचिन्हित दीर्घ entry_index,
			काष्ठा pp_घातer_state *ps,
			pp_tables_hw_घड़ी_info_callback func);

पूर्णांक pp_tables_get_response_बार(काष्ठा pp_hwmgr *hwmgr,
				 uपूर्णांक32_t *vol_rep_समय, uपूर्णांक32_t *bb_rep_समय);

#पूर्ण_अगर
