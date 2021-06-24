<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Utility functions क्रम parsing Tegra CVB voltage tables
 */

#अगर_अघोषित __DRIVERS_CLK_TEGRA_CVB_H
#घोषणा __DRIVERS_CLK_TEGRA_CVB_H

#समावेश <linux/types.h>

काष्ठा device;

#घोषणा MAX_DVFS_FREQS	40

काष्ठा rail_alignment अणु
	पूर्णांक offset_uv;
	पूर्णांक step_uv;
पूर्ण;

काष्ठा cvb_coefficients अणु
	पूर्णांक c0;
	पूर्णांक c1;
	पूर्णांक c2;
पूर्ण;

काष्ठा cvb_table_freq_entry अणु
	अचिन्हित दीर्घ freq;
	काष्ठा cvb_coefficients coefficients;
पूर्ण;

काष्ठा cvb_cpu_dfll_data अणु
	u32 tune0_low;
	u32 tune0_high;
	u32 tune1;
	अचिन्हित पूर्णांक tune_high_min_millivolts;
पूर्ण;

काष्ठा cvb_table अणु
	पूर्णांक speeकरो_id;
	पूर्णांक process_id;

	पूर्णांक min_millivolts;
	पूर्णांक max_millivolts;

	पूर्णांक speeकरो_scale;
	पूर्णांक voltage_scale;
	काष्ठा cvb_table_freq_entry entries[MAX_DVFS_FREQS];
	काष्ठा cvb_cpu_dfll_data cpu_dfll_data;
पूर्ण;

स्थिर काष्ठा cvb_table *
tegra_cvb_add_opp_table(काष्ठा device *dev, स्थिर काष्ठा cvb_table *cvb_tables,
			माप_प्रकार count, काष्ठा rail_alignment *align,
			पूर्णांक process_id, पूर्णांक speeकरो_id, पूर्णांक speeकरो_value,
			अचिन्हित दीर्घ max_freq);
व्योम tegra_cvb_हटाओ_opp_table(काष्ठा device *dev,
				स्थिर काष्ठा cvb_table *table,
				अचिन्हित दीर्घ max_freq);

#पूर्ण_अगर
