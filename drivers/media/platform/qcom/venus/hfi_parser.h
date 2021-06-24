<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2018 Linaro Ltd. */
#अगर_अघोषित __VENUS_HFI_PARSER_H__
#घोषणा __VENUS_HFI_PARSER_H__

#समावेश "core.h"

u32 hfi_parser(काष्ठा venus_core *core, काष्ठा venus_inst *inst,
	       व्योम *buf, u32 size);

#घोषणा WHICH_CAP_MIN	0
#घोषणा WHICH_CAP_MAX	1
#घोषणा WHICH_CAP_STEP	2

अटल अंतरभूत u32 get_cap(काष्ठा venus_inst *inst, u32 type, u32 which)
अणु
	काष्ठा venus_core *core = inst->core;
	काष्ठा hfi_capability *cap = शून्य;
	काष्ठा hfi_plat_caps *caps;
	अचिन्हित पूर्णांक i;

	caps = venus_caps_by_codec(core, inst->hfi_codec, inst->session_type);
	अगर (!caps)
		वापस 0;

	क्रम (i = 0; i < caps->num_caps; i++) अणु
		अगर (caps->caps[i].capability_type == type) अणु
			cap = &caps->caps[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!cap)
		वापस 0;

	चयन (which) अणु
	हाल WHICH_CAP_MIN:
		वापस cap->min;
	हाल WHICH_CAP_MAX:
		वापस cap->max;
	हाल WHICH_CAP_STEP:
		वापस cap->step_size;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत u32 cap_min(काष्ठा venus_inst *inst, u32 type)
अणु
	वापस get_cap(inst, type, WHICH_CAP_MIN);
पूर्ण

अटल अंतरभूत u32 cap_max(काष्ठा venus_inst *inst, u32 type)
अणु
	वापस get_cap(inst, type, WHICH_CAP_MAX);
पूर्ण

अटल अंतरभूत u32 cap_step(काष्ठा venus_inst *inst, u32 type)
अणु
	वापस get_cap(inst, type, WHICH_CAP_STEP);
पूर्ण

अटल अंतरभूत u32 frame_width_min(काष्ठा venus_inst *inst)
अणु
	वापस cap_min(inst, HFI_CAPABILITY_FRAME_WIDTH);
पूर्ण

अटल अंतरभूत u32 frame_width_max(काष्ठा venus_inst *inst)
अणु
	वापस cap_max(inst, HFI_CAPABILITY_FRAME_WIDTH);
पूर्ण

अटल अंतरभूत u32 frame_width_step(काष्ठा venus_inst *inst)
अणु
	वापस cap_step(inst, HFI_CAPABILITY_FRAME_WIDTH);
पूर्ण

अटल अंतरभूत u32 frame_height_min(काष्ठा venus_inst *inst)
अणु
	वापस cap_min(inst, HFI_CAPABILITY_FRAME_HEIGHT);
पूर्ण

अटल अंतरभूत u32 frame_height_max(काष्ठा venus_inst *inst)
अणु
	वापस cap_max(inst, HFI_CAPABILITY_FRAME_HEIGHT);
पूर्ण

अटल अंतरभूत u32 frame_height_step(काष्ठा venus_inst *inst)
अणु
	वापस cap_step(inst, HFI_CAPABILITY_FRAME_HEIGHT);
पूर्ण

अटल अंतरभूत u32 frate_min(काष्ठा venus_inst *inst)
अणु
	वापस cap_min(inst, HFI_CAPABILITY_FRAMERATE);
पूर्ण

अटल अंतरभूत u32 frate_max(काष्ठा venus_inst *inst)
अणु
	वापस cap_max(inst, HFI_CAPABILITY_FRAMERATE);
पूर्ण

अटल अंतरभूत u32 frate_step(काष्ठा venus_inst *inst)
अणु
	वापस cap_step(inst, HFI_CAPABILITY_FRAMERATE);
पूर्ण

अटल अंतरभूत u32 core_num_max(काष्ठा venus_inst *inst)
अणु
	वापस cap_max(inst, HFI_CAPABILITY_MAX_VIDEOCORES);
पूर्ण

अटल अंतरभूत u32 mbs_per_frame_max(काष्ठा venus_inst *inst)
अणु
	वापस cap_max(inst, HFI_CAPABILITY_MBS_PER_FRAME);
पूर्ण

#पूर्ण_अगर
