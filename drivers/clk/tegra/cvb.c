<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Utility functions क्रम parsing Tegra CVB voltage tables
 *
 * Copyright (C) 2012-2019 NVIDIA Corporation.  All rights reserved.
 */
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pm_opp.h>

#समावेश "cvb.h"

/* cvb_mv = ((c2 * speeकरो / s_scale + c1) * speeकरो / s_scale + c0) */
अटल अंतरभूत पूर्णांक get_cvb_voltage(पूर्णांक speeकरो, पूर्णांक s_scale,
				  स्थिर काष्ठा cvb_coefficients *cvb)
अणु
	पूर्णांक mv;

	/* apply only speeकरो scale: output mv = cvb_mv * v_scale */
	mv = DIV_ROUND_CLOSEST(cvb->c2 * speeकरो, s_scale);
	mv = DIV_ROUND_CLOSEST((mv + cvb->c1) * speeकरो, s_scale) + cvb->c0;
	वापस mv;
पूर्ण

अटल पूर्णांक round_cvb_voltage(पूर्णांक mv, पूर्णांक v_scale,
			     स्थिर काष्ठा rail_alignment *align)
अणु
	/* combined: apply voltage scale and round to cvb alignment step */
	पूर्णांक uv;
	पूर्णांक step = (align->step_uv ? : 1000) * v_scale;
	पूर्णांक offset = align->offset_uv * v_scale;

	uv = max(mv * 1000, offset) - offset;
	uv = DIV_ROUND_UP(uv, step) * align->step_uv + align->offset_uv;
	वापस uv / 1000;
पूर्ण

क्रमागत अणु
	DOWN,
	UP
पूर्ण;

अटल पूर्णांक round_voltage(पूर्णांक mv, स्थिर काष्ठा rail_alignment *align, पूर्णांक up)
अणु
	अगर (align->step_uv) अणु
		पूर्णांक uv;

		uv = max(mv * 1000, align->offset_uv) - align->offset_uv;
		uv = (uv + (up ? align->step_uv - 1 : 0)) / align->step_uv;
		वापस (uv * align->step_uv + align->offset_uv) / 1000;
	पूर्ण
	वापस mv;
पूर्ण

अटल पूर्णांक build_opp_table(काष्ठा device *dev, स्थिर काष्ठा cvb_table *table,
			   काष्ठा rail_alignment *align,
			   पूर्णांक speeकरो_value, अचिन्हित दीर्घ max_freq)
अणु
	पूर्णांक i, ret, dfll_mv, min_mv, max_mv;

	min_mv = round_voltage(table->min_millivolts, align, UP);
	max_mv = round_voltage(table->max_millivolts, align, DOWN);

	क्रम (i = 0; i < MAX_DVFS_FREQS; i++) अणु
		स्थिर काष्ठा cvb_table_freq_entry *entry = &table->entries[i];

		अगर (!entry->freq || (entry->freq > max_freq))
			अवरोध;

		dfll_mv = get_cvb_voltage(speeकरो_value, table->speeकरो_scale,
					  &entry->coefficients);
		dfll_mv = round_cvb_voltage(dfll_mv, table->voltage_scale,
					    align);
		dfll_mv = clamp(dfll_mv, min_mv, max_mv);

		ret = dev_pm_opp_add(dev, entry->freq, dfll_mv * 1000);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * tegra_cvb_add_opp_table - build OPP table from Tegra CVB tables
 * @dev: the काष्ठा device * क्रम which the OPP table is built
 * @tables: array of CVB tables
 * @count: size of the previously mentioned array
 * @align: parameters of the regulator step and offset
 * @process_id: process id of the HW module
 * @speeकरो_id: speeकरो id of the HW module
 * @speeकरो_value: speeकरो value of the HW module
 * @max_freq: highest safe घड़ी rate
 *
 * On Tegra, a CVB table encodes the relationship between operating voltage
 * and safe maximal frequency क्रम a given module (e.g. GPU or CPU). This
 * function calculates the optimal voltage-frequency operating poपूर्णांकs
 * क्रम the given arguments and exports them via the OPP library क्रम the
 * given @dev. Returns a poपूर्णांकer to the काष्ठा cvb_table that matched
 * or an ERR_PTR on failure.
 */
स्थिर काष्ठा cvb_table *
tegra_cvb_add_opp_table(काष्ठा device *dev, स्थिर काष्ठा cvb_table *tables,
			माप_प्रकार count, काष्ठा rail_alignment *align,
			पूर्णांक process_id, पूर्णांक speeकरो_id, पूर्णांक speeकरो_value,
			अचिन्हित दीर्घ max_freq)
अणु
	माप_प्रकार i;
	पूर्णांक ret;

	क्रम (i = 0; i < count; i++) अणु
		स्थिर काष्ठा cvb_table *table = &tables[i];

		अगर (table->speeकरो_id != -1 && table->speeकरो_id != speeकरो_id)
			जारी;

		अगर (table->process_id != -1 && table->process_id != process_id)
			जारी;

		ret = build_opp_table(dev, table, align, speeकरो_value,
				      max_freq);
		वापस ret ? ERR_PTR(ret) : table;
	पूर्ण

	वापस ERR_PTR(-EINVAL);
पूर्ण

व्योम tegra_cvb_हटाओ_opp_table(काष्ठा device *dev,
				स्थिर काष्ठा cvb_table *table,
				अचिन्हित दीर्घ max_freq)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < MAX_DVFS_FREQS; i++) अणु
		स्थिर काष्ठा cvb_table_freq_entry *entry = &table->entries[i];

		अगर (!entry->freq || (entry->freq > max_freq))
			अवरोध;

		dev_pm_opp_हटाओ(dev, entry->freq);
	पूर्ण
पूर्ण
