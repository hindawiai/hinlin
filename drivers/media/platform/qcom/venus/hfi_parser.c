<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Linaro Ltd.
 *
 * Author: Stanimir Varbanov <stanimir.varbanov@linaro.org>
 */
#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>

#समावेश "core.h"
#समावेश "hfi_helper.h"
#समावेश "hfi_parser.h"

प्रकार व्योम (*func)(काष्ठा hfi_plat_caps *cap, स्थिर व्योम *data,
		     अचिन्हित पूर्णांक size);

अटल व्योम init_codecs(काष्ठा venus_core *core)
अणु
	काष्ठा hfi_plat_caps *caps = core->caps, *cap;
	अचिन्हित दीर्घ bit;

	क्रम_each_set_bit(bit, &core->dec_codecs, MAX_CODEC_NUM) अणु
		cap = &caps[core->codecs_count++];
		cap->codec = BIT(bit);
		cap->करोमुख्य = VIDC_SESSION_TYPE_DEC;
		cap->valid = false;
	पूर्ण

	क्रम_each_set_bit(bit, &core->enc_codecs, MAX_CODEC_NUM) अणु
		cap = &caps[core->codecs_count++];
		cap->codec = BIT(bit);
		cap->करोमुख्य = VIDC_SESSION_TYPE_ENC;
		cap->valid = false;
	पूर्ण
पूर्ण

अटल व्योम क्रम_each_codec(काष्ठा hfi_plat_caps *caps, अचिन्हित पूर्णांक caps_num,
			   u32 codecs, u32 करोमुख्य, func cb, व्योम *data,
			   अचिन्हित पूर्णांक size)
अणु
	काष्ठा hfi_plat_caps *cap;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < caps_num; i++) अणु
		cap = &caps[i];
		अगर (cap->valid && cap->करोमुख्य == करोमुख्य)
			जारी;
		अगर (cap->codec & codecs && cap->करोमुख्य == करोमुख्य)
			cb(cap, data, size);
	पूर्ण
पूर्ण

अटल व्योम
fill_buf_mode(काष्ठा hfi_plat_caps *cap, स्थिर व्योम *data, अचिन्हित पूर्णांक num)
अणु
	स्थिर u32 *type = data;

	अगर (*type == HFI_BUFFER_MODE_DYNAMIC)
		cap->cap_bufs_mode_dynamic = true;
पूर्ण

अटल व्योम
parse_alloc_mode(काष्ठा venus_core *core, u32 codecs, u32 करोमुख्य, व्योम *data)
अणु
	काष्ठा hfi_buffer_alloc_mode_supported *mode = data;
	u32 num_entries = mode->num_entries;
	u32 *type;

	अगर (num_entries > MAX_ALLOC_MODE_ENTRIES)
		वापस;

	type = mode->data;

	जबतक (num_entries--) अणु
		अगर (mode->buffer_type == HFI_BUFFER_OUTPUT ||
		    mode->buffer_type == HFI_BUFFER_OUTPUT2)
			क्रम_each_codec(core->caps, ARRAY_SIZE(core->caps),
				       codecs, करोमुख्य, fill_buf_mode, type, 1);

		type++;
	पूर्ण
पूर्ण

अटल व्योम fill_profile_level(काष्ठा hfi_plat_caps *cap, स्थिर व्योम *data,
			       अचिन्हित पूर्णांक num)
अणु
	स्थिर काष्ठा hfi_profile_level *pl = data;

	स_नकल(&cap->pl[cap->num_pl], pl, num * माप(*pl));
	cap->num_pl += num;
पूर्ण

अटल व्योम
parse_profile_level(काष्ठा venus_core *core, u32 codecs, u32 करोमुख्य, व्योम *data)
अणु
	काष्ठा hfi_profile_level_supported *pl = data;
	काष्ठा hfi_profile_level *proflevel = pl->profile_level;
	काष्ठा hfi_profile_level pl_arr[HFI_MAX_PROखाता_COUNT] = अणुपूर्ण;

	अगर (pl->profile_count > HFI_MAX_PROखाता_COUNT)
		वापस;

	स_नकल(pl_arr, proflevel, pl->profile_count * माप(*proflevel));

	क्रम_each_codec(core->caps, ARRAY_SIZE(core->caps), codecs, करोमुख्य,
		       fill_profile_level, pl_arr, pl->profile_count);
पूर्ण

अटल व्योम
fill_caps(काष्ठा hfi_plat_caps *cap, स्थिर व्योम *data, अचिन्हित पूर्णांक num)
अणु
	स्थिर काष्ठा hfi_capability *caps = data;

	स_नकल(&cap->caps[cap->num_caps], caps, num * माप(*caps));
	cap->num_caps += num;
पूर्ण

अटल व्योम
parse_caps(काष्ठा venus_core *core, u32 codecs, u32 करोमुख्य, व्योम *data)
अणु
	काष्ठा hfi_capabilities *caps = data;
	काष्ठा hfi_capability *cap = caps->data;
	u32 num_caps = caps->num_capabilities;
	काष्ठा hfi_capability caps_arr[MAX_CAP_ENTRIES] = अणुपूर्ण;

	अगर (num_caps > MAX_CAP_ENTRIES)
		वापस;

	स_नकल(caps_arr, cap, num_caps * माप(*cap));

	क्रम_each_codec(core->caps, ARRAY_SIZE(core->caps), codecs, करोमुख्य,
		       fill_caps, caps_arr, num_caps);
पूर्ण

अटल व्योम fill_raw_fmts(काष्ठा hfi_plat_caps *cap, स्थिर व्योम *fmts,
			  अचिन्हित पूर्णांक num_fmts)
अणु
	स्थिर काष्ठा raw_क्रमmats *क्रमmats = fmts;

	स_नकल(&cap->fmts[cap->num_fmts], क्रमmats, num_fmts * माप(*क्रमmats));
	cap->num_fmts += num_fmts;
पूर्ण

अटल व्योम
parse_raw_क्रमmats(काष्ठा venus_core *core, u32 codecs, u32 करोमुख्य, व्योम *data)
अणु
	काष्ठा hfi_uncompressed_क्रमmat_supported *fmt = data;
	काष्ठा hfi_uncompressed_plane_info *pinfo = fmt->plane_info;
	काष्ठा hfi_uncompressed_plane_स्थिरraपूर्णांकs *स्थिरr;
	काष्ठा raw_क्रमmats rawfmts[MAX_FMT_ENTRIES] = अणुपूर्ण;
	u32 entries = fmt->क्रमmat_entries;
	अचिन्हित पूर्णांक i = 0;
	u32 num_planes;

	जबतक (entries) अणु
		num_planes = pinfo->num_planes;

		rawfmts[i].fmt = pinfo->क्रमmat;
		rawfmts[i].buftype = fmt->buffer_type;
		i++;

		अगर (pinfo->num_planes > MAX_PLANES)
			अवरोध;

		pinfo = (व्योम *)pinfo + माप(*स्थिरr) * num_planes +
			2 * माप(u32);
		entries--;
	पूर्ण

	क्रम_each_codec(core->caps, ARRAY_SIZE(core->caps), codecs, करोमुख्य,
		       fill_raw_fmts, rawfmts, i);
पूर्ण

अटल व्योम parse_codecs(काष्ठा venus_core *core, व्योम *data)
अणु
	काष्ठा hfi_codec_supported *codecs = data;

	core->dec_codecs = codecs->dec_codecs;
	core->enc_codecs = codecs->enc_codecs;

	अगर (IS_V1(core)) अणु
		core->dec_codecs &= ~HFI_VIDEO_CODEC_HEVC;
		core->dec_codecs &= ~HFI_VIDEO_CODEC_SPARK;
		core->enc_codecs &= ~HFI_VIDEO_CODEC_HEVC;
	पूर्ण
पूर्ण

अटल व्योम parse_max_sessions(काष्ठा venus_core *core, स्थिर व्योम *data)
अणु
	स्थिर काष्ठा hfi_max_sessions_supported *sessions = data;

	core->max_sessions_supported = sessions->max_sessions;
पूर्ण

अटल व्योम parse_codecs_mask(u32 *codecs, u32 *करोमुख्य, व्योम *data)
अणु
	काष्ठा hfi_codec_mask_supported *mask = data;

	*codecs = mask->codecs;
	*करोमुख्य = mask->video_करोमुख्यs;
पूर्ण

अटल व्योम parser_init(काष्ठा venus_inst *inst, u32 *codecs, u32 *करोमुख्य)
अणु
	अगर (!inst || !IS_V1(inst->core))
		वापस;

	*codecs = inst->hfi_codec;
	*करोमुख्य = inst->session_type;
पूर्ण

अटल व्योम parser_fini(काष्ठा venus_inst *inst, u32 codecs, u32 करोमुख्य)
अणु
	काष्ठा hfi_plat_caps *caps, *cap;
	अचिन्हित पूर्णांक i;
	u32 करोm;

	अगर (!inst || !IS_V1(inst->core))
		वापस;

	caps = inst->core->caps;
	करोm = inst->session_type;

	क्रम (i = 0; i < MAX_CODEC_NUM; i++) अणु
		cap = &caps[i];
		अगर (cap->codec & codecs && cap->करोमुख्य == करोm)
			cap->valid = true;
	पूर्ण
पूर्ण

अटल पूर्णांक hfi_platक्रमm_parser(काष्ठा venus_core *core, काष्ठा venus_inst *inst)
अणु
	स्थिर काष्ठा hfi_platक्रमm *plat;
	स्थिर काष्ठा hfi_plat_caps *caps = शून्य;
	u32 enc_codecs, dec_codecs, count = 0;
	अचिन्हित पूर्णांक entries;

	plat = hfi_platक्रमm_get(core->res->hfi_version);
	अगर (!plat)
		वापस -EINVAL;

	अगर (inst)
		वापस 0;

	अगर (plat->codecs)
		plat->codecs(&enc_codecs, &dec_codecs, &count);

	अगर (plat->capabilities)
		caps = plat->capabilities(&entries);

	अगर (!caps || !entries || !count)
		वापस -EINVAL;

	core->enc_codecs = enc_codecs;
	core->dec_codecs = dec_codecs;
	core->codecs_count = count;
	core->max_sessions_supported = MAX_SESSIONS;
	स_रखो(core->caps, 0, माप(*caps) * MAX_CODEC_NUM);
	स_नकल(core->caps, caps, माप(*caps) * entries);

	वापस 0;
पूर्ण

u32 hfi_parser(काष्ठा venus_core *core, काष्ठा venus_inst *inst, व्योम *buf,
	       u32 size)
अणु
	अचिन्हित पूर्णांक words_count = size >> 2;
	u32 *word = buf, *data, codecs = 0, करोमुख्य = 0;
	पूर्णांक ret;

	ret = hfi_platक्रमm_parser(core, inst);
	अगर (!ret)
		वापस HFI_ERR_NONE;

	अगर (size % 4)
		वापस HFI_ERR_SYS_INSUFFICIENT_RESOURCES;

	parser_init(inst, &codecs, &करोमुख्य);

	अगर (core->res->hfi_version > HFI_VERSION_1XX) अणु
		core->codecs_count = 0;
		स_रखो(core->caps, 0, माप(core->caps));
	पूर्ण

	जबतक (words_count) अणु
		data = word + 1;

		चयन (*word) अणु
		हाल HFI_PROPERTY_PARAM_CODEC_SUPPORTED:
			parse_codecs(core, data);
			init_codecs(core);
			अवरोध;
		हाल HFI_PROPERTY_PARAM_MAX_SESSIONS_SUPPORTED:
			parse_max_sessions(core, data);
			अवरोध;
		हाल HFI_PROPERTY_PARAM_CODEC_MASK_SUPPORTED:
			parse_codecs_mask(&codecs, &करोमुख्य, data);
			अवरोध;
		हाल HFI_PROPERTY_PARAM_UNCOMPRESSED_FORMAT_SUPPORTED:
			parse_raw_क्रमmats(core, codecs, करोमुख्य, data);
			अवरोध;
		हाल HFI_PROPERTY_PARAM_CAPABILITY_SUPPORTED:
			parse_caps(core, codecs, करोमुख्य, data);
			अवरोध;
		हाल HFI_PROPERTY_PARAM_PROखाता_LEVEL_SUPPORTED:
			parse_profile_level(core, codecs, करोमुख्य, data);
			अवरोध;
		हाल HFI_PROPERTY_PARAM_BUFFER_ALLOC_MODE_SUPPORTED:
			parse_alloc_mode(core, codecs, करोमुख्य, data);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		word++;
		words_count--;
	पूर्ण

	अगर (!core->max_sessions_supported)
		core->max_sessions_supported = MAX_SESSIONS;

	parser_fini(inst, codecs, करोमुख्य);

	वापस HFI_ERR_NONE;
पूर्ण
