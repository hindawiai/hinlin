<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Author: Vincent Abriou <vincent.abriou@st.com> क्रम STMicroelectronics.
 */

#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "sti_awg_utils.h"

#घोषणा AWG_DELAY (-5)

#घोषणा AWG_OPCODE_OFFSET 10
#घोषणा AWG_MAX_ARG       0x3ff

क्रमागत opcode अणु
	SET,
	RPTSET,
	RPLSET,
	SKIP,
	STOP,
	REPEAT,
	REPLAY,
	JUMP,
	HOLD,
पूर्ण;

अटल पूर्णांक awg_generate_instr(क्रमागत opcode opcode,
			      दीर्घ पूर्णांक arg,
			      दीर्घ पूर्णांक mux_sel,
			      दीर्घ पूर्णांक data_en,
			      काष्ठा awg_code_generation_params *fwparams)
अणु
	u32 inकाष्ठाion = 0;
	u32 mux = (mux_sel << 8) & 0x1ff;
	u32 data_enable = (data_en << 9) & 0x2ff;
	दीर्घ पूर्णांक arg_पंचांगp = arg;

	/* skip, repeat and replay arg should not exceed 1023.
	 * If user wants to exceed this value, the inकाष्ठाion should be
	 * duplicate and arg should be adjust क्रम each duplicated inकाष्ठाion.
	 *
	 * mux_sel is used in हाल of SAV/EAV synchronization.
	 */

	जबतक (arg_पंचांगp > 0) अणु
		arg = arg_पंचांगp;
		अगर (fwparams->inकाष्ठाion_offset >= AWG_MAX_INST) अणु
			DRM_ERROR("too many number of instructions\n");
			वापस -EINVAL;
		पूर्ण

		चयन (opcode) अणु
		हाल SKIP:
			/* leave 'arg' + 1 pixel elapsing without changing
			 * output bus */
			arg--; /* pixel adjusपंचांगent */
			arg_पंचांगp--;

			अगर (arg < 0) अणु
				/* SKIP inकाष्ठाion not needed */
				वापस 0;
			पूर्ण

			अगर (arg == 0) अणु
				/* SKIP 0 not permitted but we want to skip 1
				 * pixel. So we transक्रमm SKIP पूर्णांकo SET
				 * inकाष्ठाion */
				opcode = SET;
				अवरोध;
			पूर्ण

			mux = 0;
			data_enable = 0;
			arg &= AWG_MAX_ARG;
			अवरोध;
		हाल REPEAT:
		हाल REPLAY:
			अगर (arg == 0) अणु
				/* REPEAT or REPLAY inकाष्ठाion not needed */
				वापस 0;
			पूर्ण

			mux = 0;
			data_enable = 0;
			arg &= AWG_MAX_ARG;
			अवरोध;
		हाल JUMP:
			mux = 0;
			data_enable = 0;
			arg |= 0x40; /* क्रम jump inकाष्ठाion 7th bit is 1 */
			arg &= AWG_MAX_ARG;
			अवरोध;
		हाल STOP:
			arg = 0;
			अवरोध;
		हाल SET:
		हाल RPTSET:
		हाल RPLSET:
		हाल HOLD:
			arg &= (0x0ff);
			अवरोध;
		शेष:
			DRM_ERROR("instruction %d does not exist\n", opcode);
			वापस -EINVAL;
		पूर्ण

		arg_पंचांगp = arg_पंचांगp - arg;

		arg = ((arg + mux) + data_enable);

		inकाष्ठाion = ((opcode) << AWG_OPCODE_OFFSET) | arg;
		fwparams->ram_code[fwparams->inकाष्ठाion_offset] =
			inकाष्ठाion & (0x3fff);
		fwparams->inकाष्ठाion_offset++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक awg_generate_line_संकेत(
		काष्ठा awg_code_generation_params *fwparams,
		काष्ठा awg_timing *timing)
अणु
	दीर्घ पूर्णांक val;
	पूर्णांक ret = 0;

	अगर (timing->trailing_pixels > 0) अणु
		/* skip trailing pixel */
		val = timing->blanking_level;
		ret |= awg_generate_instr(RPLSET, val, 0, 0, fwparams);

		val = timing->trailing_pixels - 1 + AWG_DELAY;
		ret |= awg_generate_instr(SKIP, val, 0, 0, fwparams);
	पूर्ण

	/* set DE संकेत high */
	val = timing->blanking_level;
	ret |= awg_generate_instr((timing->trailing_pixels > 0) ? SET : RPLSET,
			val, 0, 1, fwparams);

	अगर (timing->blanking_pixels > 0) अणु
		/* skip the number of active pixel */
		val = timing->active_pixels - 1;
		ret |= awg_generate_instr(SKIP, val, 0, 1, fwparams);

		/* set DE संकेत low */
		val = timing->blanking_level;
		ret |= awg_generate_instr(SET, val, 0, 0, fwparams);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक sti_awg_generate_code_data_enable_mode(
		काष्ठा awg_code_generation_params *fwparams,
		काष्ठा awg_timing *timing)
अणु
	दीर्घ पूर्णांक val, पंचांगp_val;
	पूर्णांक ret = 0;

	अगर (timing->trailing_lines > 0) अणु
		/* skip trailing lines */
		val = timing->blanking_level;
		ret |= awg_generate_instr(RPLSET, val, 0, 0, fwparams);

		val = timing->trailing_lines - 1;
		ret |= awg_generate_instr(REPLAY, val, 0, 0, fwparams);
	पूर्ण

	पंचांगp_val = timing->active_lines - 1;

	जबतक (पंचांगp_val > 0) अणु
		/* generate DE संकेत क्रम each line */
		ret |= awg_generate_line_संकेत(fwparams, timing);
		/* replay the sequence as many active lines defined */
		ret |= awg_generate_instr(REPLAY,
					  min_t(पूर्णांक, AWG_MAX_ARG, पंचांगp_val),
					  0, 0, fwparams);
		पंचांगp_val -= AWG_MAX_ARG;
	पूर्ण

	अगर (timing->blanking_lines > 0) अणु
		/* skip blanking lines */
		val = timing->blanking_level;
		ret |= awg_generate_instr(RPLSET, val, 0, 0, fwparams);

		val = timing->blanking_lines - 1;
		ret |= awg_generate_instr(REPLAY, val, 0, 0, fwparams);
	पूर्ण

	वापस ret;
पूर्ण
