<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 Linaro Ltd.
 *
 * Author: Stanimir Varbanov <stanimir.varbanov@linaro.org>
 */
#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerconnect.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>
#समावेश <linux/types.h>
#समावेश <media/v4l2-mem2स्मृति.स>

#समावेश "core.h"
#समावेश "hfi_parser.h"
#समावेश "hfi_venus_io.h"
#समावेश "pm_helpers.h"
#समावेश "hfi_platform.h"

अटल bool legacy_binding;

अटल पूर्णांक core_clks_get(काष्ठा venus_core *core)
अणु
	स्थिर काष्ठा venus_resources *res = core->res;
	काष्ठा device *dev = core->dev;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < res->clks_num; i++) अणु
		core->clks[i] = devm_clk_get(dev, res->clks[i]);
		अगर (IS_ERR(core->clks[i]))
			वापस PTR_ERR(core->clks[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक core_clks_enable(काष्ठा venus_core *core)
अणु
	स्थिर काष्ठा venus_resources *res = core->res;
	स्थिर काष्ठा freq_tbl *freq_tbl = core->res->freq_tbl;
	अचिन्हित पूर्णांक freq_tbl_size = core->res->freq_tbl_size;
	अचिन्हित दीर्घ freq;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (!freq_tbl)
		वापस -EINVAL;

	freq = freq_tbl[freq_tbl_size - 1].freq;

	क्रम (i = 0; i < res->clks_num; i++) अणु
		अगर (IS_V6(core)) अणु
			ret = clk_set_rate(core->clks[i], freq);
			अगर (ret)
				जाओ err;
		पूर्ण

		ret = clk_prepare_enable(core->clks[i]);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;
err:
	जबतक (i--)
		clk_disable_unprepare(core->clks[i]);

	वापस ret;
पूर्ण

अटल व्योम core_clks_disable(काष्ठा venus_core *core)
अणु
	स्थिर काष्ठा venus_resources *res = core->res;
	अचिन्हित पूर्णांक i = res->clks_num;

	जबतक (i--)
		clk_disable_unprepare(core->clks[i]);
पूर्ण

अटल पूर्णांक core_clks_set_rate(काष्ठा venus_core *core, अचिन्हित दीर्घ freq)
अणु
	पूर्णांक ret;

	ret = dev_pm_opp_set_rate(core->dev, freq);
	अगर (ret)
		वापस ret;

	ret = clk_set_rate(core->vcodec0_clks[0], freq);
	अगर (ret)
		वापस ret;

	ret = clk_set_rate(core->vcodec1_clks[0], freq);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक vcodec_clks_get(काष्ठा venus_core *core, काष्ठा device *dev,
			   काष्ठा clk **clks, स्थिर अक्षर * स्थिर *id)
अणु
	स्थिर काष्ठा venus_resources *res = core->res;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < res->vcodec_clks_num; i++) अणु
		अगर (!id[i])
			जारी;
		clks[i] = devm_clk_get(dev, id[i]);
		अगर (IS_ERR(clks[i]))
			वापस PTR_ERR(clks[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vcodec_clks_enable(काष्ठा venus_core *core, काष्ठा clk **clks)
अणु
	स्थिर काष्ठा venus_resources *res = core->res;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < res->vcodec_clks_num; i++) अणु
		ret = clk_prepare_enable(clks[i]);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;
err:
	जबतक (i--)
		clk_disable_unprepare(clks[i]);

	वापस ret;
पूर्ण

अटल व्योम vcodec_clks_disable(काष्ठा venus_core *core, काष्ठा clk **clks)
अणु
	स्थिर काष्ठा venus_resources *res = core->res;
	अचिन्हित पूर्णांक i = res->vcodec_clks_num;

	जबतक (i--)
		clk_disable_unprepare(clks[i]);
पूर्ण

अटल u32 load_per_instance(काष्ठा venus_inst *inst)
अणु
	u32 mbs;

	अगर (!inst || !(inst->state >= INST_INIT && inst->state < INST_STOP))
		वापस 0;

	mbs = (ALIGN(inst->width, 16) / 16) * (ALIGN(inst->height, 16) / 16);

	वापस mbs * inst->fps;
पूर्ण

अटल u32 load_per_type(काष्ठा venus_core *core, u32 session_type)
अणु
	काष्ठा venus_inst *inst = शून्य;
	u32 mbs_per_sec = 0;

	mutex_lock(&core->lock);
	list_क्रम_each_entry(inst, &core->instances, list) अणु
		अगर (inst->session_type != session_type)
			जारी;

		mbs_per_sec += load_per_instance(inst);
	पूर्ण
	mutex_unlock(&core->lock);

	वापस mbs_per_sec;
पूर्ण

अटल व्योम mbs_to_bw(काष्ठा venus_inst *inst, u32 mbs, u32 *avg, u32 *peak)
अणु
	स्थिर काष्ठा venus_resources *res = inst->core->res;
	स्थिर काष्ठा bw_tbl *bw_tbl;
	अचिन्हित पूर्णांक num_rows, i;

	*avg = 0;
	*peak = 0;

	अगर (mbs == 0)
		वापस;

	अगर (inst->session_type == VIDC_SESSION_TYPE_ENC) अणु
		num_rows = res->bw_tbl_enc_size;
		bw_tbl = res->bw_tbl_enc;
	पूर्ण अन्यथा अगर (inst->session_type == VIDC_SESSION_TYPE_DEC) अणु
		num_rows = res->bw_tbl_dec_size;
		bw_tbl = res->bw_tbl_dec;
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण

	अगर (!bw_tbl || num_rows == 0)
		वापस;

	क्रम (i = 0; i < num_rows; i++) अणु
		अगर (i != 0 && mbs > bw_tbl[i].mbs_per_sec)
			अवरोध;

		अगर (inst->dpb_fmt & HFI_COLOR_FORMAT_10_BIT_BASE) अणु
			*avg = bw_tbl[i].avg_10bit;
			*peak = bw_tbl[i].peak_10bit;
		पूर्ण अन्यथा अणु
			*avg = bw_tbl[i].avg;
			*peak = bw_tbl[i].peak;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक load_scale_bw(काष्ठा venus_core *core)
अणु
	काष्ठा venus_inst *inst = शून्य;
	u32 mbs_per_sec, avg, peak, total_avg = 0, total_peak = 0;

	mutex_lock(&core->lock);
	list_क्रम_each_entry(inst, &core->instances, list) अणु
		mbs_per_sec = load_per_instance(inst);
		mbs_to_bw(inst, mbs_per_sec, &avg, &peak);
		total_avg += avg;
		total_peak += peak;
	पूर्ण
	mutex_unlock(&core->lock);

	/*
	 * keep minimum bandwidth vote क्रम "video-mem" path,
	 * so that clks can be disabled during vdec_session_release().
	 * Actual bandwidth drop will be करोne during device supend
	 * so that device can घातer करोwn without any warnings.
	 */

	अगर (!total_avg && !total_peak)
		total_avg = kbps_to_icc(1000);

	dev_dbg(core->dev, VDBGL "total: avg_bw: %u, peak_bw: %u\n",
		total_avg, total_peak);

	वापस icc_set_bw(core->video_path, total_avg, total_peak);
पूर्ण

अटल पूर्णांक load_scale_v1(काष्ठा venus_inst *inst)
अणु
	काष्ठा venus_core *core = inst->core;
	स्थिर काष्ठा freq_tbl *table = core->res->freq_tbl;
	अचिन्हित पूर्णांक num_rows = core->res->freq_tbl_size;
	अचिन्हित दीर्घ freq = table[0].freq;
	काष्ठा device *dev = core->dev;
	u32 mbs_per_sec;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	mbs_per_sec = load_per_type(core, VIDC_SESSION_TYPE_ENC) +
		      load_per_type(core, VIDC_SESSION_TYPE_DEC);

	अगर (mbs_per_sec > core->res->max_load)
		dev_warn(dev, "HW is overloaded, needed: %d max: %d\n",
			 mbs_per_sec, core->res->max_load);

	अगर (!mbs_per_sec && num_rows > 1) अणु
		freq = table[num_rows - 1].freq;
		जाओ set_freq;
	पूर्ण

	क्रम (i = 0; i < num_rows; i++) अणु
		अगर (mbs_per_sec > table[i].load)
			अवरोध;
		freq = table[i].freq;
	पूर्ण

set_freq:

	ret = core_clks_set_rate(core, freq);
	अगर (ret) अणु
		dev_err(dev, "failed to set clock rate %lu (%d)\n",
			freq, ret);
		वापस ret;
	पूर्ण

	ret = load_scale_bw(core);
	अगर (ret) अणु
		dev_err(dev, "failed to set bandwidth (%d)\n",
			ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक core_get_v1(काष्ठा venus_core *core)
अणु
	पूर्णांक ret;

	ret = core_clks_get(core);
	अगर (ret)
		वापस ret;

	core->opp_table = dev_pm_opp_set_clkname(core->dev, "core");
	अगर (IS_ERR(core->opp_table))
		वापस PTR_ERR(core->opp_table);

	वापस 0;
पूर्ण

अटल व्योम core_put_v1(काष्ठा venus_core *core)
अणु
	dev_pm_opp_put_clkname(core->opp_table);
पूर्ण

अटल पूर्णांक core_घातer_v1(काष्ठा venus_core *core, पूर्णांक on)
अणु
	पूर्णांक ret = 0;

	अगर (on == POWER_ON)
		ret = core_clks_enable(core);
	अन्यथा
		core_clks_disable(core);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा venus_pm_ops pm_ops_v1 = अणु
	.core_get = core_get_v1,
	.core_put = core_put_v1,
	.core_घातer = core_घातer_v1,
	.load_scale = load_scale_v1,
पूर्ण;

अटल व्योम
vcodec_control_v3(काष्ठा venus_core *core, u32 session_type, bool enable)
अणु
	व्योम __iomem *ctrl;

	अगर (session_type == VIDC_SESSION_TYPE_DEC)
		ctrl = core->wrapper_base + WRAPPER_VDEC_VCODEC_POWER_CONTROL;
	अन्यथा
		ctrl = core->wrapper_base + WRAPPER_VENC_VCODEC_POWER_CONTROL;

	अगर (enable)
		ग_लिखोl(0, ctrl);
	अन्यथा
		ग_लिखोl(1, ctrl);
पूर्ण

अटल पूर्णांक vdec_get_v3(काष्ठा device *dev)
अणु
	काष्ठा venus_core *core = dev_get_drvdata(dev);

	वापस vcodec_clks_get(core, dev, core->vcodec0_clks,
			       core->res->vcodec0_clks);
पूर्ण

अटल पूर्णांक vdec_घातer_v3(काष्ठा device *dev, पूर्णांक on)
अणु
	काष्ठा venus_core *core = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	vcodec_control_v3(core, VIDC_SESSION_TYPE_DEC, true);

	अगर (on == POWER_ON)
		ret = vcodec_clks_enable(core, core->vcodec0_clks);
	अन्यथा
		vcodec_clks_disable(core, core->vcodec0_clks);

	vcodec_control_v3(core, VIDC_SESSION_TYPE_DEC, false);

	वापस ret;
पूर्ण

अटल पूर्णांक venc_get_v3(काष्ठा device *dev)
अणु
	काष्ठा venus_core *core = dev_get_drvdata(dev);

	वापस vcodec_clks_get(core, dev, core->vcodec1_clks,
			       core->res->vcodec1_clks);
पूर्ण

अटल पूर्णांक venc_घातer_v3(काष्ठा device *dev, पूर्णांक on)
अणु
	काष्ठा venus_core *core = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	vcodec_control_v3(core, VIDC_SESSION_TYPE_ENC, true);

	अगर (on == POWER_ON)
		ret = vcodec_clks_enable(core, core->vcodec1_clks);
	अन्यथा
		vcodec_clks_disable(core, core->vcodec1_clks);

	vcodec_control_v3(core, VIDC_SESSION_TYPE_ENC, false);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा venus_pm_ops pm_ops_v3 = अणु
	.core_get = core_get_v1,
	.core_put = core_put_v1,
	.core_घातer = core_घातer_v1,
	.vdec_get = vdec_get_v3,
	.vdec_घातer = vdec_घातer_v3,
	.venc_get = venc_get_v3,
	.venc_घातer = venc_घातer_v3,
	.load_scale = load_scale_v1,
पूर्ण;

अटल पूर्णांक vcodec_control_v4(काष्ठा venus_core *core, u32 coreid, bool enable)
अणु
	व्योम __iomem *ctrl, *stat;
	u32 val;
	पूर्णांक ret;

	अगर (IS_V6(core)) अणु
		ctrl = core->wrapper_base + WRAPPER_CORE_POWER_CONTROL_V6;
		stat = core->wrapper_base + WRAPPER_CORE_POWER_STATUS_V6;
	पूर्ण अन्यथा अगर (coreid == VIDC_CORE_ID_1) अणु
		ctrl = core->wrapper_base + WRAPPER_VCODEC0_MMCC_POWER_CONTROL;
		stat = core->wrapper_base + WRAPPER_VCODEC0_MMCC_POWER_STATUS;
	पूर्ण अन्यथा अणु
		ctrl = core->wrapper_base + WRAPPER_VCODEC1_MMCC_POWER_CONTROL;
		stat = core->wrapper_base + WRAPPER_VCODEC1_MMCC_POWER_STATUS;
	पूर्ण

	अगर (enable) अणु
		ग_लिखोl(0, ctrl);

		ret = पढ़ोl_poll_समयout(stat, val, val & BIT(1), 1, 100);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		ग_लिखोl(1, ctrl);

		ret = पढ़ोl_poll_समयout(stat, val, !(val & BIT(1)), 1, 100);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक घातeroff_coreid(काष्ठा venus_core *core, अचिन्हित पूर्णांक coreid_mask)
अणु
	पूर्णांक ret;

	अगर (coreid_mask & VIDC_CORE_ID_1) अणु
		ret = vcodec_control_v4(core, VIDC_CORE_ID_1, true);
		अगर (ret)
			वापस ret;

		vcodec_clks_disable(core, core->vcodec0_clks);

		ret = vcodec_control_v4(core, VIDC_CORE_ID_1, false);
		अगर (ret)
			वापस ret;

		ret = pm_runसमय_put_sync(core->pmकरोमुख्यs[1]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (coreid_mask & VIDC_CORE_ID_2) अणु
		ret = vcodec_control_v4(core, VIDC_CORE_ID_2, true);
		अगर (ret)
			वापस ret;

		vcodec_clks_disable(core, core->vcodec1_clks);

		ret = vcodec_control_v4(core, VIDC_CORE_ID_2, false);
		अगर (ret)
			वापस ret;

		ret = pm_runसमय_put_sync(core->pmकरोमुख्यs[2]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक घातeron_coreid(काष्ठा venus_core *core, अचिन्हित पूर्णांक coreid_mask)
अणु
	पूर्णांक ret;

	अगर (coreid_mask & VIDC_CORE_ID_1) अणु
		ret = pm_runसमय_get_sync(core->pmकरोमुख्यs[1]);
		अगर (ret < 0)
			वापस ret;

		ret = vcodec_control_v4(core, VIDC_CORE_ID_1, true);
		अगर (ret)
			वापस ret;

		ret = vcodec_clks_enable(core, core->vcodec0_clks);
		अगर (ret)
			वापस ret;

		ret = vcodec_control_v4(core, VIDC_CORE_ID_1, false);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (coreid_mask & VIDC_CORE_ID_2) अणु
		ret = pm_runसमय_get_sync(core->pmकरोमुख्यs[2]);
		अगर (ret < 0)
			वापस ret;

		ret = vcodec_control_v4(core, VIDC_CORE_ID_2, true);
		अगर (ret)
			वापस ret;

		ret = vcodec_clks_enable(core, core->vcodec1_clks);
		अगर (ret)
			वापस ret;

		ret = vcodec_control_v4(core, VIDC_CORE_ID_2, false);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
min_loaded_core(काष्ठा venus_inst *inst, u32 *min_coreid, u32 *min_load)
अणु
	u32 mbs_per_sec, load, core1_load = 0, core2_load = 0;
	u32 cores_max = core_num_max(inst);
	काष्ठा venus_core *core = inst->core;
	काष्ठा venus_inst *inst_pos;
	अचिन्हित दीर्घ vpp_freq;
	u32 coreid;

	mutex_lock(&core->lock);

	list_क्रम_each_entry(inst_pos, &core->instances, list) अणु
		अगर (inst_pos == inst)
			जारी;

		अगर (inst_pos->state != INST_START)
			जारी;

		vpp_freq = inst_pos->clk_data.vpp_freq;
		coreid = inst_pos->clk_data.core_id;

		mbs_per_sec = load_per_instance(inst_pos);
		load = mbs_per_sec * vpp_freq;

		अगर ((coreid & VIDC_CORE_ID_3) == VIDC_CORE_ID_3) अणु
			core1_load += load / 2;
			core2_load += load / 2;
		पूर्ण अन्यथा अगर (coreid & VIDC_CORE_ID_1) अणु
			core1_load += load;
		पूर्ण अन्यथा अगर (coreid & VIDC_CORE_ID_2) अणु
			core2_load += load;
		पूर्ण
	पूर्ण

	*min_coreid = core1_load <= core2_load ?
			VIDC_CORE_ID_1 : VIDC_CORE_ID_2;
	*min_load = min(core1_load, core2_load);

	अगर (cores_max < VIDC_CORE_ID_2 || core->res->vcodec_num < 2) अणु
		*min_coreid = VIDC_CORE_ID_1;
		*min_load = core1_load;
	पूर्ण

	mutex_unlock(&core->lock);
पूर्ण

अटल पूर्णांक decide_core(काष्ठा venus_inst *inst)
अणु
	स्थिर u32 ptype = HFI_PROPERTY_CONFIG_VIDEOCORES_USAGE;
	काष्ठा venus_core *core = inst->core;
	u32 min_coreid, min_load, inst_load;
	काष्ठा hfi_videocores_usage_type cu;
	अचिन्हित दीर्घ max_freq;

	अगर (legacy_binding) अणु
		अगर (inst->session_type == VIDC_SESSION_TYPE_DEC)
			cu.video_core_enable_mask = VIDC_CORE_ID_1;
		अन्यथा
			cu.video_core_enable_mask = VIDC_CORE_ID_2;

		जाओ करोne;
	पूर्ण

	अगर (inst->clk_data.core_id != VIDC_CORE_ID_DEFAULT)
		वापस 0;

	inst_load = load_per_instance(inst);
	inst_load *= inst->clk_data.vpp_freq;
	max_freq = core->res->freq_tbl[0].freq;

	min_loaded_core(inst, &min_coreid, &min_load);

	अगर ((inst_load + min_load) > max_freq) अणु
		dev_warn(core->dev, "HW is overloaded, needed: %u max: %lu\n",
			 inst_load, max_freq);
		वापस -EINVAL;
	पूर्ण

	inst->clk_data.core_id = min_coreid;
	cu.video_core_enable_mask = min_coreid;

करोne:
	वापस hfi_session_set_property(inst, ptype, &cu);
पूर्ण

अटल पूर्णांक acquire_core(काष्ठा venus_inst *inst)
अणु
	काष्ठा venus_core *core = inst->core;
	अचिन्हित पूर्णांक coreid_mask = 0;

	अगर (inst->core_acquired)
		वापस 0;

	inst->core_acquired = true;

	अगर (inst->clk_data.core_id & VIDC_CORE_ID_1) अणु
		अगर (core->core0_usage_count++)
			वापस 0;

		coreid_mask = VIDC_CORE_ID_1;
	पूर्ण

	अगर (inst->clk_data.core_id & VIDC_CORE_ID_2) अणु
		अगर (core->core1_usage_count++)
			वापस 0;

		coreid_mask |= VIDC_CORE_ID_2;
	पूर्ण

	वापस घातeron_coreid(core, coreid_mask);
पूर्ण

अटल पूर्णांक release_core(काष्ठा venus_inst *inst)
अणु
	काष्ठा venus_core *core = inst->core;
	अचिन्हित पूर्णांक coreid_mask = 0;
	पूर्णांक ret;

	अगर (!inst->core_acquired)
		वापस 0;

	अगर (inst->clk_data.core_id & VIDC_CORE_ID_1) अणु
		अगर (--core->core0_usage_count)
			जाओ करोne;

		coreid_mask = VIDC_CORE_ID_1;
	पूर्ण

	अगर (inst->clk_data.core_id & VIDC_CORE_ID_2) अणु
		अगर (--core->core1_usage_count)
			जाओ करोne;

		coreid_mask |= VIDC_CORE_ID_2;
	पूर्ण

	ret = घातeroff_coreid(core, coreid_mask);
	अगर (ret)
		वापस ret;

करोne:
	inst->clk_data.core_id = VIDC_CORE_ID_DEFAULT;
	inst->core_acquired = false;
	वापस 0;
पूर्ण

अटल पूर्णांक coreid_घातer_v4(काष्ठा venus_inst *inst, पूर्णांक on)
अणु
	काष्ठा venus_core *core = inst->core;
	पूर्णांक ret;

	अगर (legacy_binding)
		वापस 0;

	अगर (on == POWER_ON) अणु
		ret = decide_core(inst);
		अगर (ret)
			वापस ret;

		mutex_lock(&core->lock);
		ret = acquire_core(inst);
		mutex_unlock(&core->lock);
	पूर्ण अन्यथा अणु
		mutex_lock(&core->lock);
		ret = release_core(inst);
		mutex_unlock(&core->lock);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vdec_get_v4(काष्ठा device *dev)
अणु
	काष्ठा venus_core *core = dev_get_drvdata(dev);

	अगर (!legacy_binding)
		वापस 0;

	वापस vcodec_clks_get(core, dev, core->vcodec0_clks,
			       core->res->vcodec0_clks);
पूर्ण

अटल व्योम vdec_put_v4(काष्ठा device *dev)
अणु
	काष्ठा venus_core *core = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक i;

	अगर (!legacy_binding)
		वापस;

	क्रम (i = 0; i < core->res->vcodec_clks_num; i++)
		core->vcodec0_clks[i] = शून्य;
पूर्ण

अटल पूर्णांक vdec_घातer_v4(काष्ठा device *dev, पूर्णांक on)
अणु
	काष्ठा venus_core *core = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (!legacy_binding)
		वापस 0;

	ret = vcodec_control_v4(core, VIDC_CORE_ID_1, true);
	अगर (ret)
		वापस ret;

	अगर (on == POWER_ON)
		ret = vcodec_clks_enable(core, core->vcodec0_clks);
	अन्यथा
		vcodec_clks_disable(core, core->vcodec0_clks);

	vcodec_control_v4(core, VIDC_CORE_ID_1, false);

	वापस ret;
पूर्ण

अटल पूर्णांक venc_get_v4(काष्ठा device *dev)
अणु
	काष्ठा venus_core *core = dev_get_drvdata(dev);

	अगर (!legacy_binding)
		वापस 0;

	वापस vcodec_clks_get(core, dev, core->vcodec1_clks,
			       core->res->vcodec1_clks);
पूर्ण

अटल व्योम venc_put_v4(काष्ठा device *dev)
अणु
	काष्ठा venus_core *core = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक i;

	अगर (!legacy_binding)
		वापस;

	क्रम (i = 0; i < core->res->vcodec_clks_num; i++)
		core->vcodec1_clks[i] = शून्य;
पूर्ण

अटल पूर्णांक venc_घातer_v4(काष्ठा device *dev, पूर्णांक on)
अणु
	काष्ठा venus_core *core = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (!legacy_binding)
		वापस 0;

	ret = vcodec_control_v4(core, VIDC_CORE_ID_2, true);
	अगर (ret)
		वापस ret;

	अगर (on == POWER_ON)
		ret = vcodec_clks_enable(core, core->vcodec1_clks);
	अन्यथा
		vcodec_clks_disable(core, core->vcodec1_clks);

	vcodec_control_v4(core, VIDC_CORE_ID_2, false);

	वापस ret;
पूर्ण

अटल पूर्णांक vcodec_करोमुख्यs_get(काष्ठा venus_core *core)
अणु
	पूर्णांक ret;
	काष्ठा opp_table *opp_table;
	काष्ठा device **opp_virt_dev;
	काष्ठा device *dev = core->dev;
	स्थिर काष्ठा venus_resources *res = core->res;
	काष्ठा device *pd;
	अचिन्हित पूर्णांक i;

	अगर (!res->vcodec_pmकरोमुख्यs_num)
		जाओ skip_pmकरोमुख्यs;

	क्रम (i = 0; i < res->vcodec_pmकरोमुख्यs_num; i++) अणु
		pd = dev_pm_करोमुख्य_attach_by_name(dev,
						  res->vcodec_pmकरोमुख्यs[i]);
		अगर (IS_ERR(pd))
			वापस PTR_ERR(pd);
		core->pmकरोमुख्यs[i] = pd;
	पूर्ण

skip_pmकरोमुख्यs:
	अगर (!core->has_opp_table)
		वापस 0;

	/* Attach the घातer करोमुख्य क्रम setting perक्रमmance state */
	opp_table = dev_pm_opp_attach_genpd(dev, res->opp_pmकरोमुख्य, &opp_virt_dev);
	अगर (IS_ERR(opp_table)) अणु
		ret = PTR_ERR(opp_table);
		जाओ opp_attach_err;
	पूर्ण

	core->opp_pmकरोमुख्य = *opp_virt_dev;
	core->opp_dl_venus = device_link_add(dev, core->opp_pmकरोमुख्य,
					     DL_FLAG_RPM_ACTIVE |
					     DL_FLAG_PM_RUNTIME |
					     DL_FLAG_STATELESS);
	अगर (!core->opp_dl_venus) अणु
		ret = -ENODEV;
		जाओ opp_dl_add_err;
	पूर्ण

	वापस 0;

opp_dl_add_err:
	dev_pm_opp_detach_genpd(core->opp_table);
opp_attach_err:
	क्रम (i = 0; i < res->vcodec_pmकरोमुख्यs_num; i++) अणु
		अगर (IS_ERR_OR_शून्य(core->pmकरोमुख्यs[i]))
			जारी;
		dev_pm_करोमुख्य_detach(core->pmकरोमुख्यs[i], true);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम vcodec_करोमुख्यs_put(काष्ठा venus_core *core)
अणु
	स्थिर काष्ठा venus_resources *res = core->res;
	अचिन्हित पूर्णांक i;

	अगर (!res->vcodec_pmकरोमुख्यs_num)
		जाओ skip_pmकरोमुख्यs;

	क्रम (i = 0; i < res->vcodec_pmकरोमुख्यs_num; i++) अणु
		अगर (IS_ERR_OR_शून्य(core->pmकरोमुख्यs[i]))
			जारी;
		dev_pm_करोमुख्य_detach(core->pmकरोमुख्यs[i], true);
	पूर्ण

skip_pmकरोमुख्यs:
	अगर (!core->has_opp_table)
		वापस;

	अगर (core->opp_dl_venus)
		device_link_del(core->opp_dl_venus);

	dev_pm_opp_detach_genpd(core->opp_table);
पूर्ण

अटल पूर्णांक core_resets_reset(काष्ठा venus_core *core)
अणु
	स्थिर काष्ठा venus_resources *res = core->res;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (!res->resets_num)
		वापस 0;

	क्रम (i = 0; i < res->resets_num; i++) अणु
		ret = reset_control_निश्चित(core->resets[i]);
		अगर (ret)
			जाओ err;

		usleep_range(150, 250);
		ret = reset_control_deनिश्चित(core->resets[i]);
		अगर (ret)
			जाओ err;
	पूर्ण

err:
	वापस ret;
पूर्ण

अटल पूर्णांक core_resets_get(काष्ठा venus_core *core)
अणु
	काष्ठा device *dev = core->dev;
	स्थिर काष्ठा venus_resources *res = core->res;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (!res->resets_num)
		वापस 0;

	क्रम (i = 0; i < res->resets_num; i++) अणु
		core->resets[i] =
			devm_reset_control_get_exclusive(dev, res->resets[i]);
		अगर (IS_ERR(core->resets[i])) अणु
			ret = PTR_ERR(core->resets[i]);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक core_get_v4(काष्ठा venus_core *core)
अणु
	काष्ठा device *dev = core->dev;
	स्थिर काष्ठा venus_resources *res = core->res;
	पूर्णांक ret;

	ret = core_clks_get(core);
	अगर (ret)
		वापस ret;

	अगर (!res->vcodec_pmकरोमुख्यs_num)
		legacy_binding = true;

	dev_info(dev, "%s legacy binding\n", legacy_binding ? "" : "non");

	ret = vcodec_clks_get(core, dev, core->vcodec0_clks, res->vcodec0_clks);
	अगर (ret)
		वापस ret;

	ret = vcodec_clks_get(core, dev, core->vcodec1_clks, res->vcodec1_clks);
	अगर (ret)
		वापस ret;

	ret = core_resets_get(core);
	अगर (ret)
		वापस ret;

	अगर (legacy_binding)
		वापस 0;

	core->opp_table = dev_pm_opp_set_clkname(dev, "core");
	अगर (IS_ERR(core->opp_table))
		वापस PTR_ERR(core->opp_table);

	अगर (core->res->opp_pmकरोमुख्य) अणु
		ret = dev_pm_opp_of_add_table(dev);
		अगर (!ret) अणु
			core->has_opp_table = true;
		पूर्ण अन्यथा अगर (ret != -ENODEV) अणु
			dev_err(dev, "invalid OPP table in device tree\n");
			dev_pm_opp_put_clkname(core->opp_table);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = vcodec_करोमुख्यs_get(core);
	अगर (ret) अणु
		अगर (core->has_opp_table)
			dev_pm_opp_of_हटाओ_table(dev);
		dev_pm_opp_put_clkname(core->opp_table);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम core_put_v4(काष्ठा venus_core *core)
अणु
	काष्ठा device *dev = core->dev;

	अगर (legacy_binding)
		वापस;

	vcodec_करोमुख्यs_put(core);

	अगर (core->has_opp_table)
		dev_pm_opp_of_हटाओ_table(dev);
	dev_pm_opp_put_clkname(core->opp_table);

पूर्ण

अटल पूर्णांक core_घातer_v4(काष्ठा venus_core *core, पूर्णांक on)
अणु
	काष्ठा device *dev = core->dev;
	काष्ठा device *pmctrl = core->pmकरोमुख्यs[0];
	पूर्णांक ret = 0;

	अगर (on == POWER_ON) अणु
		अगर (pmctrl) अणु
			ret = pm_runसमय_get_sync(pmctrl);
			अगर (ret < 0) अणु
				pm_runसमय_put_noidle(pmctrl);
				वापस ret;
			पूर्ण
		पूर्ण

		ret = core_resets_reset(core);
		अगर (ret) अणु
			अगर (pmctrl)
				pm_runसमय_put_sync(pmctrl);
			वापस ret;
		पूर्ण

		ret = core_clks_enable(core);
		अगर (ret < 0 && pmctrl)
			pm_runसमय_put_sync(pmctrl);
	पूर्ण अन्यथा अणु
		/* Drop the perक्रमmance state vote */
		अगर (core->opp_pmकरोमुख्य)
			dev_pm_opp_set_rate(dev, 0);

		core_clks_disable(core);

		ret = core_resets_reset(core);

		अगर (pmctrl)
			pm_runसमय_put_sync(pmctrl);
	पूर्ण

	वापस ret;
पूर्ण

अटल अचिन्हित दीर्घ calculate_inst_freq(काष्ठा venus_inst *inst,
					 अचिन्हित दीर्घ filled_len)
अणु
	अचिन्हित दीर्घ vpp_freq = 0, vsp_freq = 0;
	u32 fps = (u32)inst->fps;
	u32 mbs_per_sec;

	mbs_per_sec = load_per_instance(inst);

	अगर (inst->state != INST_START)
		वापस 0;

	vpp_freq = mbs_per_sec * inst->clk_data.vpp_freq;
	/* 21 / 20 is overhead factor */
	vpp_freq += vpp_freq / 20;
	vsp_freq = mbs_per_sec * inst->clk_data.vsp_freq;

	/* 10 / 7 is overhead factor */
	अगर (inst->session_type == VIDC_SESSION_TYPE_ENC)
		vsp_freq += (inst->controls.enc.bitrate * 10) / 7;
	अन्यथा
		vsp_freq += ((fps * filled_len * 8) * 10) / 7;

	वापस max(vpp_freq, vsp_freq);
पूर्ण

अटल पूर्णांक load_scale_v4(काष्ठा venus_inst *inst)
अणु
	काष्ठा venus_core *core = inst->core;
	स्थिर काष्ठा freq_tbl *table = core->res->freq_tbl;
	अचिन्हित पूर्णांक num_rows = core->res->freq_tbl_size;
	काष्ठा device *dev = core->dev;
	अचिन्हित दीर्घ freq = 0, freq_core1 = 0, freq_core2 = 0;
	अचिन्हित दीर्घ filled_len = 0;
	पूर्णांक i, ret;

	क्रम (i = 0; i < inst->num_input_bufs; i++)
		filled_len = max(filled_len, inst->payloads[i]);

	अगर (inst->session_type == VIDC_SESSION_TYPE_DEC && !filled_len)
		वापस 0;

	freq = calculate_inst_freq(inst, filled_len);
	inst->clk_data.freq = freq;

	mutex_lock(&core->lock);
	list_क्रम_each_entry(inst, &core->instances, list) अणु
		अगर (inst->clk_data.core_id == VIDC_CORE_ID_1) अणु
			freq_core1 += inst->clk_data.freq;
		पूर्ण अन्यथा अगर (inst->clk_data.core_id == VIDC_CORE_ID_2) अणु
			freq_core2 += inst->clk_data.freq;
		पूर्ण अन्यथा अगर (inst->clk_data.core_id == VIDC_CORE_ID_3) अणु
			freq_core1 += inst->clk_data.freq;
			freq_core2 += inst->clk_data.freq;
		पूर्ण
	पूर्ण
	mutex_unlock(&core->lock);

	freq = max(freq_core1, freq_core2);

	अगर (freq > table[0].freq) अणु
		freq = table[0].freq;
		dev_warn(dev, "HW is overloaded, needed: %lu max: %lu\n",
			 freq, table[0].freq);
		जाओ set_freq;
	पूर्ण

	क्रम (i = num_rows - 1 ; i >= 0; i--) अणु
		अगर (freq <= table[i].freq) अणु
			freq = table[i].freq;
			अवरोध;
		पूर्ण
	पूर्ण

set_freq:

	ret = core_clks_set_rate(core, freq);
	अगर (ret) अणु
		dev_err(dev, "failed to set clock rate %lu (%d)\n",
			freq, ret);
		वापस ret;
	पूर्ण

	ret = load_scale_bw(core);
	अगर (ret) अणु
		dev_err(dev, "failed to set bandwidth (%d)\n",
			ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा venus_pm_ops pm_ops_v4 = अणु
	.core_get = core_get_v4,
	.core_put = core_put_v4,
	.core_घातer = core_घातer_v4,
	.vdec_get = vdec_get_v4,
	.vdec_put = vdec_put_v4,
	.vdec_घातer = vdec_घातer_v4,
	.venc_get = venc_get_v4,
	.venc_put = venc_put_v4,
	.venc_घातer = venc_घातer_v4,
	.coreid_घातer = coreid_घातer_v4,
	.load_scale = load_scale_v4,
पूर्ण;

स्थिर काष्ठा venus_pm_ops *venus_pm_get(क्रमागत hfi_version version)
अणु
	चयन (version) अणु
	हाल HFI_VERSION_1XX:
	शेष:
		वापस &pm_ops_v1;
	हाल HFI_VERSION_3XX:
		वापस &pm_ops_v3;
	हाल HFI_VERSION_4XX:
	हाल HFI_VERSION_6XX:
		वापस &pm_ops_v4;
	पूर्ण

	वापस शून्य;
पूर्ण
