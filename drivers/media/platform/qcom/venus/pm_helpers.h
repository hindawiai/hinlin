<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (C) 2019 Linaro Ltd. */
#अगर_अघोषित __VENUS_PM_HELPERS_H__
#घोषणा __VENUS_PM_HELPERS_H__

काष्ठा device;
काष्ठा venus_core;

#घोषणा POWER_ON	1
#घोषणा POWER_OFF	0

काष्ठा venus_pm_ops अणु
	पूर्णांक (*core_get)(काष्ठा venus_core *core);
	व्योम (*core_put)(काष्ठा venus_core *core);
	पूर्णांक (*core_घातer)(काष्ठा venus_core *core, पूर्णांक on);

	पूर्णांक (*vdec_get)(काष्ठा device *dev);
	व्योम (*vdec_put)(काष्ठा device *dev);
	पूर्णांक (*vdec_घातer)(काष्ठा device *dev, पूर्णांक on);

	पूर्णांक (*venc_get)(काष्ठा device *dev);
	व्योम (*venc_put)(काष्ठा device *dev);
	पूर्णांक (*venc_घातer)(काष्ठा device *dev, पूर्णांक on);

	पूर्णांक (*coreid_घातer)(काष्ठा venus_inst *inst, पूर्णांक on);

	पूर्णांक (*load_scale)(काष्ठा venus_inst *inst);
पूर्ण;

स्थिर काष्ठा venus_pm_ops *venus_pm_get(क्रमागत hfi_version version);

अटल अंतरभूत पूर्णांक venus_pm_load_scale(काष्ठा venus_inst *inst)
अणु
	काष्ठा venus_core *core = inst->core;

	अगर (!core->pm_ops || !core->pm_ops->load_scale)
		वापस 0;

	वापस core->pm_ops->load_scale(inst);
पूर्ण

अटल अंतरभूत पूर्णांक venus_pm_acquire_core(काष्ठा venus_inst *inst)
अणु
	काष्ठा venus_core *core = inst->core;
	स्थिर काष्ठा venus_pm_ops *pm_ops = core->pm_ops;
	पूर्णांक ret = 0;

	अगर (pm_ops && pm_ops->coreid_घातer)
		ret = pm_ops->coreid_घातer(inst, POWER_ON);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक venus_pm_release_core(काष्ठा venus_inst *inst)
अणु
	काष्ठा venus_core *core = inst->core;
	स्थिर काष्ठा venus_pm_ops *pm_ops = core->pm_ops;
	पूर्णांक ret = 0;

	अगर (pm_ops && pm_ops->coreid_घातer)
		ret = pm_ops->coreid_घातer(inst, POWER_OFF);

	वापस ret;
पूर्ण

#पूर्ण_अगर
