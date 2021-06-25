<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Author: Vincent Abriou <vincent.abriou@st.com> क्रम STMicroelectronics.
 */

#अगर_अघोषित _STI_AWG_UTILS_H_
#घोषणा _STI_AWG_UTILS_H_

#समावेश <linux/types.h>

#घोषणा AWG_MAX_INST 64

काष्ठा awg_code_generation_params अणु
	u32 *ram_code;
	u8 inकाष्ठाion_offset;
पूर्ण;

काष्ठा awg_timing अणु
	u32 total_lines;
	u32 active_lines;
	u32 blanking_lines;
	u32 trailing_lines;
	u32 total_pixels;
	u32 active_pixels;
	u32 blanking_pixels;
	u32 trailing_pixels;
	u32 blanking_level;
पूर्ण;

पूर्णांक sti_awg_generate_code_data_enable_mode(
		काष्ठा awg_code_generation_params *fw_gen_params,
		काष्ठा awg_timing *timing);
#पूर्ण_अगर
