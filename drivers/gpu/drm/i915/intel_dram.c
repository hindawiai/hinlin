<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#समावेश "i915_drv.h"
#समावेश "intel_dram.h"
#समावेश "intel_sideband.h"

काष्ठा dram_dimm_info अणु
	u16 size;
	u8 width, ranks;
पूर्ण;

काष्ठा dram_channel_info अणु
	काष्ठा dram_dimm_info dimm_l, dimm_s;
	u8 ranks;
	bool is_16gb_dimm;
पूर्ण;

#घोषणा DRAM_TYPE_STR(type) [INTEL_DRAM_ ## type] = #type

अटल स्थिर अक्षर *पूर्णांकel_dram_type_str(क्रमागत पूर्णांकel_dram_type type)
अणु
	अटल स्थिर अक्षर * स्थिर str[] = अणु
		DRAM_TYPE_STR(UNKNOWN),
		DRAM_TYPE_STR(DDR3),
		DRAM_TYPE_STR(DDR4),
		DRAM_TYPE_STR(LPDDR3),
		DRAM_TYPE_STR(LPDDR4),
	पूर्ण;

	अगर (type >= ARRAY_SIZE(str))
		type = INTEL_DRAM_UNKNOWN;

	वापस str[type];
पूर्ण

#अघोषित DRAM_TYPE_STR

अटल पूर्णांक पूर्णांकel_dimm_num_devices(स्थिर काष्ठा dram_dimm_info *dimm)
अणु
	वापस dimm->ranks * 64 / (dimm->width ?: 1);
पूर्ण

/* Returns total Gb क्रम the whole DIMM */
अटल पूर्णांक skl_get_dimm_size(u16 val)
अणु
	वापस (val & SKL_DRAM_SIZE_MASK) * 8;
पूर्ण

अटल पूर्णांक skl_get_dimm_width(u16 val)
अणु
	अगर (skl_get_dimm_size(val) == 0)
		वापस 0;

	चयन (val & SKL_DRAM_WIDTH_MASK) अणु
	हाल SKL_DRAM_WIDTH_X8:
	हाल SKL_DRAM_WIDTH_X16:
	हाल SKL_DRAM_WIDTH_X32:
		val = (val & SKL_DRAM_WIDTH_MASK) >> SKL_DRAM_WIDTH_SHIFT;
		वापस 8 << val;
	शेष:
		MISSING_CASE(val);
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक skl_get_dimm_ranks(u16 val)
अणु
	अगर (skl_get_dimm_size(val) == 0)
		वापस 0;

	val = (val & SKL_DRAM_RANK_MASK) >> SKL_DRAM_RANK_SHIFT;

	वापस val + 1;
पूर्ण

/* Returns total Gb क्रम the whole DIMM */
अटल पूर्णांक cnl_get_dimm_size(u16 val)
अणु
	वापस (val & CNL_DRAM_SIZE_MASK) * 8 / 2;
पूर्ण

अटल पूर्णांक cnl_get_dimm_width(u16 val)
अणु
	अगर (cnl_get_dimm_size(val) == 0)
		वापस 0;

	चयन (val & CNL_DRAM_WIDTH_MASK) अणु
	हाल CNL_DRAM_WIDTH_X8:
	हाल CNL_DRAM_WIDTH_X16:
	हाल CNL_DRAM_WIDTH_X32:
		val = (val & CNL_DRAM_WIDTH_MASK) >> CNL_DRAM_WIDTH_SHIFT;
		वापस 8 << val;
	शेष:
		MISSING_CASE(val);
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक cnl_get_dimm_ranks(u16 val)
अणु
	अगर (cnl_get_dimm_size(val) == 0)
		वापस 0;

	val = (val & CNL_DRAM_RANK_MASK) >> CNL_DRAM_RANK_SHIFT;

	वापस val + 1;
पूर्ण

अटल bool
skl_is_16gb_dimm(स्थिर काष्ठा dram_dimm_info *dimm)
अणु
	/* Convert total Gb to Gb per DRAM device */
	वापस dimm->size / (पूर्णांकel_dimm_num_devices(dimm) ?: 1) == 16;
पूर्ण

अटल व्योम
skl_dram_get_dimm_info(काष्ठा drm_i915_निजी *i915,
		       काष्ठा dram_dimm_info *dimm,
		       पूर्णांक channel, अक्षर dimm_name, u16 val)
अणु
	अगर (INTEL_GEN(i915) >= 10) अणु
		dimm->size = cnl_get_dimm_size(val);
		dimm->width = cnl_get_dimm_width(val);
		dimm->ranks = cnl_get_dimm_ranks(val);
	पूर्ण अन्यथा अणु
		dimm->size = skl_get_dimm_size(val);
		dimm->width = skl_get_dimm_width(val);
		dimm->ranks = skl_get_dimm_ranks(val);
	पूर्ण

	drm_dbg_kms(&i915->drm,
		    "CH%u DIMM %c size: %u Gb, width: X%u, ranks: %u, 16Gb DIMMs: %s\n",
		    channel, dimm_name, dimm->size, dimm->width, dimm->ranks,
		    yesno(skl_is_16gb_dimm(dimm)));
पूर्ण

अटल पूर्णांक
skl_dram_get_channel_info(काष्ठा drm_i915_निजी *i915,
			  काष्ठा dram_channel_info *ch,
			  पूर्णांक channel, u32 val)
अणु
	skl_dram_get_dimm_info(i915, &ch->dimm_l,
			       channel, 'L', val & 0xffff);
	skl_dram_get_dimm_info(i915, &ch->dimm_s,
			       channel, 'S', val >> 16);

	अगर (ch->dimm_l.size == 0 && ch->dimm_s.size == 0) अणु
		drm_dbg_kms(&i915->drm, "CH%u not populated\n", channel);
		वापस -EINVAL;
	पूर्ण

	अगर (ch->dimm_l.ranks == 2 || ch->dimm_s.ranks == 2)
		ch->ranks = 2;
	अन्यथा अगर (ch->dimm_l.ranks == 1 && ch->dimm_s.ranks == 1)
		ch->ranks = 2;
	अन्यथा
		ch->ranks = 1;

	ch->is_16gb_dimm = skl_is_16gb_dimm(&ch->dimm_l) ||
		skl_is_16gb_dimm(&ch->dimm_s);

	drm_dbg_kms(&i915->drm, "CH%u ranks: %u, 16Gb DIMMs: %s\n",
		    channel, ch->ranks, yesno(ch->is_16gb_dimm));

	वापस 0;
पूर्ण

अटल bool
पूर्णांकel_is_dram_symmetric(स्थिर काष्ठा dram_channel_info *ch0,
			स्थिर काष्ठा dram_channel_info *ch1)
अणु
	वापस !स_भेद(ch0, ch1, माप(*ch0)) &&
		(ch0->dimm_s.size == 0 ||
		 !स_भेद(&ch0->dimm_l, &ch0->dimm_s, माप(ch0->dimm_l)));
पूर्ण

अटल पूर्णांक
skl_dram_get_channels_info(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा dram_info *dram_info = &i915->dram_info;
	काष्ठा dram_channel_info ch0 = अणुपूर्ण, ch1 = अणुपूर्ण;
	u32 val;
	पूर्णांक ret;

	val = पूर्णांकel_uncore_पढ़ो(&i915->uncore,
				SKL_MAD_DIMM_CH0_0_0_0_MCHBAR_MCMAIN);
	ret = skl_dram_get_channel_info(i915, &ch0, 0, val);
	अगर (ret == 0)
		dram_info->num_channels++;

	val = पूर्णांकel_uncore_पढ़ो(&i915->uncore,
				SKL_MAD_DIMM_CH1_0_0_0_MCHBAR_MCMAIN);
	ret = skl_dram_get_channel_info(i915, &ch1, 1, val);
	अगर (ret == 0)
		dram_info->num_channels++;

	अगर (dram_info->num_channels == 0) अणु
		drm_info(&i915->drm, "Number of memory channels is zero\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ch0.ranks == 0 && ch1.ranks == 0) अणु
		drm_info(&i915->drm, "couldn't get memory rank information\n");
		वापस -EINVAL;
	पूर्ण

	dram_info->wm_lv_0_adjust_needed = ch0.is_16gb_dimm || ch1.is_16gb_dimm;

	dram_info->symmetric_memory = पूर्णांकel_is_dram_symmetric(&ch0, &ch1);

	drm_dbg_kms(&i915->drm, "Memory configuration is symmetric? %s\n",
		    yesno(dram_info->symmetric_memory));

	वापस 0;
पूर्ण

अटल क्रमागत पूर्णांकel_dram_type
skl_get_dram_type(काष्ठा drm_i915_निजी *i915)
अणु
	u32 val;

	val = पूर्णांकel_uncore_पढ़ो(&i915->uncore,
				SKL_MAD_INTER_CHANNEL_0_0_0_MCHBAR_MCMAIN);

	चयन (val & SKL_DRAM_DDR_TYPE_MASK) अणु
	हाल SKL_DRAM_DDR_TYPE_DDR3:
		वापस INTEL_DRAM_DDR3;
	हाल SKL_DRAM_DDR_TYPE_DDR4:
		वापस INTEL_DRAM_DDR4;
	हाल SKL_DRAM_DDR_TYPE_LPDDR3:
		वापस INTEL_DRAM_LPDDR3;
	हाल SKL_DRAM_DDR_TYPE_LPDDR4:
		वापस INTEL_DRAM_LPDDR4;
	शेष:
		MISSING_CASE(val);
		वापस INTEL_DRAM_UNKNOWN;
	पूर्ण
पूर्ण

अटल पूर्णांक
skl_get_dram_info(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा dram_info *dram_info = &i915->dram_info;
	u32 mem_freq_khz, val;
	पूर्णांक ret;

	dram_info->type = skl_get_dram_type(i915);
	drm_dbg_kms(&i915->drm, "DRAM type: %s\n",
		    पूर्णांकel_dram_type_str(dram_info->type));

	ret = skl_dram_get_channels_info(i915);
	अगर (ret)
		वापस ret;

	val = पूर्णांकel_uncore_पढ़ो(&i915->uncore,
				SKL_MC_BIOS_DATA_0_0_0_MCHBAR_PCU);
	mem_freq_khz = DIV_ROUND_UP((val & SKL_REQ_DATA_MASK) *
				    SKL_MEMORY_FREQ_MULTIPLIER_HZ, 1000);

	अगर (dram_info->num_channels * mem_freq_khz == 0) अणु
		drm_info(&i915->drm,
			 "Couldn't get system memory bandwidth\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* Returns Gb per DRAM device */
अटल पूर्णांक bxt_get_dimm_size(u32 val)
अणु
	चयन (val & BXT_DRAM_SIZE_MASK) अणु
	हाल BXT_DRAM_SIZE_4GBIT:
		वापस 4;
	हाल BXT_DRAM_SIZE_6GBIT:
		वापस 6;
	हाल BXT_DRAM_SIZE_8GBIT:
		वापस 8;
	हाल BXT_DRAM_SIZE_12GBIT:
		वापस 12;
	हाल BXT_DRAM_SIZE_16GBIT:
		वापस 16;
	शेष:
		MISSING_CASE(val);
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक bxt_get_dimm_width(u32 val)
अणु
	अगर (!bxt_get_dimm_size(val))
		वापस 0;

	val = (val & BXT_DRAM_WIDTH_MASK) >> BXT_DRAM_WIDTH_SHIFT;

	वापस 8 << val;
पूर्ण

अटल पूर्णांक bxt_get_dimm_ranks(u32 val)
अणु
	अगर (!bxt_get_dimm_size(val))
		वापस 0;

	चयन (val & BXT_DRAM_RANK_MASK) अणु
	हाल BXT_DRAM_RANK_SINGLE:
		वापस 1;
	हाल BXT_DRAM_RANK_DUAL:
		वापस 2;
	शेष:
		MISSING_CASE(val);
		वापस 0;
	पूर्ण
पूर्ण

अटल क्रमागत पूर्णांकel_dram_type bxt_get_dimm_type(u32 val)
अणु
	अगर (!bxt_get_dimm_size(val))
		वापस INTEL_DRAM_UNKNOWN;

	चयन (val & BXT_DRAM_TYPE_MASK) अणु
	हाल BXT_DRAM_TYPE_DDR3:
		वापस INTEL_DRAM_DDR3;
	हाल BXT_DRAM_TYPE_LPDDR3:
		वापस INTEL_DRAM_LPDDR3;
	हाल BXT_DRAM_TYPE_DDR4:
		वापस INTEL_DRAM_DDR4;
	हाल BXT_DRAM_TYPE_LPDDR4:
		वापस INTEL_DRAM_LPDDR4;
	शेष:
		MISSING_CASE(val);
		वापस INTEL_DRAM_UNKNOWN;
	पूर्ण
पूर्ण

अटल व्योम bxt_get_dimm_info(काष्ठा dram_dimm_info *dimm, u32 val)
अणु
	dimm->width = bxt_get_dimm_width(val);
	dimm->ranks = bxt_get_dimm_ranks(val);

	/*
	 * Size in रेजिस्टर is Gb per DRAM device. Convert to total
	 * Gb to match the way we report this क्रम non-LP platक्रमms.
	 */
	dimm->size = bxt_get_dimm_size(val) * पूर्णांकel_dimm_num_devices(dimm);
पूर्ण

अटल पूर्णांक bxt_get_dram_info(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा dram_info *dram_info = &i915->dram_info;
	u32 dram_channels;
	u32 mem_freq_khz, val;
	u8 num_active_channels, valid_ranks = 0;
	पूर्णांक i;

	val = पूर्णांकel_uncore_पढ़ो(&i915->uncore, BXT_P_CR_MC_BIOS_REQ_0_0_0);
	mem_freq_khz = DIV_ROUND_UP((val & BXT_REQ_DATA_MASK) *
				    BXT_MEMORY_FREQ_MULTIPLIER_HZ, 1000);

	dram_channels = val & BXT_DRAM_CHANNEL_ACTIVE_MASK;
	num_active_channels = hweight32(dram_channels);

	अगर (mem_freq_khz * num_active_channels == 0) अणु
		drm_info(&i915->drm,
			 "Couldn't get system memory bandwidth\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Now पढ़ो each DUNIT8/9/10/11 to check the rank of each dimms.
	 */
	क्रम (i = BXT_D_CR_DRP0_DUNIT_START; i <= BXT_D_CR_DRP0_DUNIT_END; i++) अणु
		काष्ठा dram_dimm_info dimm;
		क्रमागत पूर्णांकel_dram_type type;

		val = पूर्णांकel_uncore_पढ़ो(&i915->uncore, BXT_D_CR_DRP0_DUNIT(i));
		अगर (val == 0xFFFFFFFF)
			जारी;

		dram_info->num_channels++;

		bxt_get_dimm_info(&dimm, val);
		type = bxt_get_dimm_type(val);

		drm_WARN_ON(&i915->drm, type != INTEL_DRAM_UNKNOWN &&
			    dram_info->type != INTEL_DRAM_UNKNOWN &&
			    dram_info->type != type);

		drm_dbg_kms(&i915->drm,
			    "CH%u DIMM size: %u Gb, width: X%u, ranks: %u, type: %s\n",
			    i - BXT_D_CR_DRP0_DUNIT_START,
			    dimm.size, dimm.width, dimm.ranks,
			    पूर्णांकel_dram_type_str(type));

		अगर (valid_ranks == 0)
			valid_ranks = dimm.ranks;

		अगर (type != INTEL_DRAM_UNKNOWN)
			dram_info->type = type;
	पूर्ण

	अगर (dram_info->type == INTEL_DRAM_UNKNOWN || valid_ranks == 0) अणु
		drm_info(&i915->drm, "couldn't get memory information\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक icl_pcode_पढ़ो_mem_global_info(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा dram_info *dram_info = &dev_priv->dram_info;
	u32 val = 0;
	पूर्णांक ret;

	ret = sandybridge_pcode_पढ़ो(dev_priv,
				     ICL_PCODE_MEM_SUBSYSYSTEM_INFO |
				     ICL_PCODE_MEM_SS_READ_GLOBAL_INFO,
				     &val, शून्य);
	अगर (ret)
		वापस ret;

	अगर (IS_GEN(dev_priv, 12)) अणु
		चयन (val & 0xf) अणु
		हाल 0:
			dram_info->type = INTEL_DRAM_DDR4;
			अवरोध;
		हाल 1:
			dram_info->type = INTEL_DRAM_DDR5;
			अवरोध;
		हाल 2:
			dram_info->type = INTEL_DRAM_LPDDR5;
			अवरोध;
		हाल 3:
			dram_info->type = INTEL_DRAM_LPDDR4;
			अवरोध;
		हाल 4:
			dram_info->type = INTEL_DRAM_DDR3;
			अवरोध;
		हाल 5:
			dram_info->type = INTEL_DRAM_LPDDR3;
			अवरोध;
		शेष:
			MISSING_CASE(val & 0xf);
			वापस -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (val & 0xf) अणु
		हाल 0:
			dram_info->type = INTEL_DRAM_DDR4;
			अवरोध;
		हाल 1:
			dram_info->type = INTEL_DRAM_DDR3;
			अवरोध;
		हाल 2:
			dram_info->type = INTEL_DRAM_LPDDR3;
			अवरोध;
		हाल 3:
			dram_info->type = INTEL_DRAM_LPDDR4;
			अवरोध;
		शेष:
			MISSING_CASE(val & 0xf);
			वापस -1;
		पूर्ण
	पूर्ण

	dram_info->num_channels = (val & 0xf0) >> 4;
	dram_info->num_qgv_poपूर्णांकs = (val & 0xf00) >> 8;

	वापस 0;
पूर्ण

अटल पूर्णांक gen11_get_dram_info(काष्ठा drm_i915_निजी *i915)
अणु
	पूर्णांक ret = skl_get_dram_info(i915);

	अगर (ret)
		वापस ret;

	वापस icl_pcode_पढ़ो_mem_global_info(i915);
पूर्ण

अटल पूर्णांक gen12_get_dram_info(काष्ठा drm_i915_निजी *i915)
अणु
	/* Always needed क्रम GEN12+ */
	i915->dram_info.wm_lv_0_adjust_needed = true;

	वापस icl_pcode_पढ़ो_mem_global_info(i915);
पूर्ण

व्योम पूर्णांकel_dram_detect(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा dram_info *dram_info = &i915->dram_info;
	पूर्णांक ret;

	/*
	 * Assume level 0 watermark latency adjusपंचांगent is needed until proven
	 * otherwise, this w/a is not needed by bxt/glk.
	 */
	dram_info->wm_lv_0_adjust_needed = !IS_GEN9_LP(i915);

	अगर (INTEL_GEN(i915) < 9 || !HAS_DISPLAY(i915))
		वापस;

	अगर (INTEL_GEN(i915) >= 12)
		ret = gen12_get_dram_info(i915);
	अन्यथा अगर (INTEL_GEN(i915) >= 11)
		ret = gen11_get_dram_info(i915);
	अन्यथा अगर (IS_GEN9_LP(i915))
		ret = bxt_get_dram_info(i915);
	अन्यथा
		ret = skl_get_dram_info(i915);
	अगर (ret)
		वापस;

	drm_dbg_kms(&i915->drm, "DRAM channels: %u\n", dram_info->num_channels);

	drm_dbg_kms(&i915->drm, "Watermark level 0 adjustment needed: %s\n",
		    yesno(dram_info->wm_lv_0_adjust_needed));
पूर्ण

अटल u32 gen9_edram_size_mb(काष्ठा drm_i915_निजी *i915, u32 cap)
अणु
	अटल स्थिर u8 ways[8] = अणु 4, 8, 12, 16, 16, 16, 16, 16 पूर्ण;
	अटल स्थिर u8 sets[4] = अणु 1, 1, 2, 2 पूर्ण;

	वापस EDRAM_NUM_BANKS(cap) *
		ways[EDRAM_WAYS_IDX(cap)] *
		sets[EDRAM_SETS_IDX(cap)];
पूर्ण

व्योम पूर्णांकel_dram_edram_detect(काष्ठा drm_i915_निजी *i915)
अणु
	u32 edram_cap = 0;

	अगर (!(IS_HASWELL(i915) || IS_BROADWELL(i915) || INTEL_GEN(i915) >= 9))
		वापस;

	edram_cap = __raw_uncore_पढ़ो32(&i915->uncore, HSW_EDRAM_CAP);

	/* NB: We can't write IDICR yet because we don't have gt funcs set up */

	अगर (!(edram_cap & EDRAM_ENABLED))
		वापस;

	/*
	 * The needed capability bits क्रम size calculation are not there with
	 * pre gen9 so वापस 128MB always.
	 */
	अगर (INTEL_GEN(i915) < 9)
		i915->edram_size_mb = 128;
	अन्यथा
		i915->edram_size_mb = gen9_edram_size_mb(i915, edram_cap);

	drm_info(&i915->drm, "Found %uMB of eDRAM\n", i915->edram_size_mb);
पूर्ण
