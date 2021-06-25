<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015-2018 Etnaviv Project
 */

#समावेश <linux/kernel.h>

#समावेश "etnaviv_gem.h"
#समावेश "etnaviv_gpu.h"

#समावेश "cmdstream.xml.h"

#घोषणा EXTRACT(val, field) (((val) & field##__MASK) >> field##__SHIFT)

काष्ठा etna_validation_state अणु
	काष्ठा etnaviv_gpu *gpu;
	स्थिर काष्ठा drm_etnaviv_gem_submit_reloc *relocs;
	अचिन्हित पूर्णांक num_relocs;
	u32 *start;
पूर्ण;

अटल स्थिर काष्ठा अणु
	u16 offset;
	u16 size;
पूर्ण etnaviv_sensitive_states[] __initस्थिर = अणु
#घोषणा ST(start, num) अणु (start) >> 2, (num) पूर्ण
	/* 2D */
	ST(0x1200, 1),
	ST(0x1228, 1),
	ST(0x1238, 1),
	ST(0x1284, 1),
	ST(0x128c, 1),
	ST(0x1304, 1),
	ST(0x1310, 1),
	ST(0x1318, 1),
	ST(0x12800, 4),
	ST(0x128a0, 4),
	ST(0x128c0, 4),
	ST(0x12970, 4),
	ST(0x12a00, 8),
	ST(0x12b40, 8),
	ST(0x12b80, 8),
	ST(0x12ce0, 8),
	/* 3D */
	ST(0x0644, 1),
	ST(0x064c, 1),
	ST(0x0680, 8),
	ST(0x086c, 1),
	ST(0x1028, 1),
	ST(0x1410, 1),
	ST(0x1430, 1),
	ST(0x1458, 1),
	ST(0x1460, 8),
	ST(0x1480, 8),
	ST(0x1500, 8),
	ST(0x1520, 8),
	ST(0x1608, 1),
	ST(0x1610, 1),
	ST(0x1658, 1),
	ST(0x165c, 1),
	ST(0x1664, 1),
	ST(0x1668, 1),
	ST(0x16a4, 1),
	ST(0x16c0, 8),
	ST(0x16e0, 8),
	ST(0x1740, 8),
	ST(0x17c0, 8),
	ST(0x17e0, 8),
	ST(0x2400, 14 * 16),
	ST(0x3824, 1),
	ST(0x10800, 32 * 16),
	ST(0x14600, 16),
	ST(0x14800, 8 * 8),
#अघोषित ST
पूर्ण;

#घोषणा ETNAVIV_STATES_SIZE (VIV_FE_LOAD_STATE_HEADER_OFFSET__MASK + 1u)
अटल DECLARE_BITMAP(etnaviv_states, ETNAVIV_STATES_SIZE);

व्योम __init etnaviv_validate_init(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(etnaviv_sensitive_states); i++)
		biपंचांगap_set(etnaviv_states, etnaviv_sensitive_states[i].offset,
			   etnaviv_sensitive_states[i].size);
पूर्ण

अटल व्योम etnaviv_warn_अगर_non_sensitive(काष्ठा etna_validation_state *state,
	अचिन्हित पूर्णांक buf_offset, अचिन्हित पूर्णांक state_addr)
अणु
	अगर (state->num_relocs && state->relocs->submit_offset < buf_offset) अणु
		dev_warn_once(state->gpu->dev,
			      "%s: relocation for non-sensitive state 0x%x at offset %u\n",
			      __func__, state_addr,
			      state->relocs->submit_offset);
		जबतक (state->num_relocs &&
		       state->relocs->submit_offset < buf_offset) अणु
			state->relocs++;
			state->num_relocs--;
		पूर्ण
	पूर्ण
पूर्ण

अटल bool etnaviv_validate_load_state(काष्ठा etna_validation_state *state,
	u32 *ptr, अचिन्हित पूर्णांक state_offset, अचिन्हित पूर्णांक num)
अणु
	अचिन्हित पूर्णांक size = min(ETNAVIV_STATES_SIZE, state_offset + num);
	अचिन्हित पूर्णांक st_offset = state_offset, buf_offset;

	क्रम_each_set_bit_from(st_offset, etnaviv_states, size) अणु
		buf_offset = (ptr - state->start +
			      st_offset - state_offset) * 4;

		etnaviv_warn_अगर_non_sensitive(state, buf_offset, st_offset * 4);
		अगर (state->num_relocs &&
		    state->relocs->submit_offset == buf_offset) अणु
			state->relocs++;
			state->num_relocs--;
			जारी;
		पूर्ण

		dev_warn_ratelimited(state->gpu->dev,
				     "%s: load state touches restricted state 0x%x at offset %u\n",
				     __func__, st_offset * 4, buf_offset);
		वापस false;
	पूर्ण

	अगर (state->num_relocs) अणु
		buf_offset = (ptr - state->start + num) * 4;
		etnaviv_warn_अगर_non_sensitive(state, buf_offset, st_offset * 4 +
					      state->relocs->submit_offset -
					      buf_offset);
	पूर्ण

	वापस true;
पूर्ण

अटल uपूर्णांक8_t cmd_length[32] = अणु
	[FE_OPCODE_DRAW_PRIMITIVES] = 4,
	[FE_OPCODE_DRAW_INDEXED_PRIMITIVES] = 6,
	[FE_OPCODE_DRAW_INSTANCED] = 4,
	[FE_OPCODE_NOP] = 2,
	[FE_OPCODE_STALL] = 2,
पूर्ण;

bool etnaviv_cmd_validate_one(काष्ठा etnaviv_gpu *gpu, u32 *stream,
			      अचिन्हित पूर्णांक size,
			      काष्ठा drm_etnaviv_gem_submit_reloc *relocs,
			      अचिन्हित पूर्णांक reloc_size)
अणु
	काष्ठा etna_validation_state state;
	u32 *buf = stream;
	u32 *end = buf + size;

	state.gpu = gpu;
	state.relocs = relocs;
	state.num_relocs = reloc_size;
	state.start = stream;

	जबतक (buf < end) अणु
		u32 cmd = *buf;
		अचिन्हित पूर्णांक len, n, off;
		अचिन्हित पूर्णांक op = cmd >> 27;

		चयन (op) अणु
		हाल FE_OPCODE_LOAD_STATE:
			n = EXTRACT(cmd, VIV_FE_LOAD_STATE_HEADER_COUNT);
			len = ALIGN(1 + n, 2);
			अगर (buf + len > end)
				अवरोध;

			off = EXTRACT(cmd, VIV_FE_LOAD_STATE_HEADER_OFFSET);
			अगर (!etnaviv_validate_load_state(&state, buf + 1,
							 off, n))
				वापस false;
			अवरोध;

		हाल FE_OPCODE_DRAW_2D:
			n = EXTRACT(cmd, VIV_FE_DRAW_2D_HEADER_COUNT);
			अगर (n == 0)
				n = 256;
			len = 2 + n * 2;
			अवरोध;

		शेष:
			len = cmd_length[op];
			अगर (len == 0) अणु
				dev_err(gpu->dev, "%s: op %u not permitted at offset %tu\n",
					__func__, op, buf - state.start);
				वापस false;
			पूर्ण
			अवरोध;
		पूर्ण

		buf += len;
	पूर्ण

	अगर (buf > end) अणु
		dev_err(gpu->dev, "%s: commands overflow end of buffer: %tu > %u\n",
			__func__, buf - state.start, size);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण
