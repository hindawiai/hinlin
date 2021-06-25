<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2019 Samsung Electronics Co., Ltd.
 *	      http://www.samsung.com/
 * Author: Sylwester Nawrocki <s.nawrocki@samsung.com>
 *
 * Samsung Exynos SoC Adaptive Supply Voltage support
 */
#अगर_अघोषित __LINUX_SOC_EXYNOS_ASV_H
#घोषणा __LINUX_SOC_EXYNOS_ASV_H

काष्ठा regmap;

/* HPM, IDS values to select target group */
काष्ठा asv_limit_entry अणु
	अचिन्हित पूर्णांक hpm;
	अचिन्हित पूर्णांक ids;
पूर्ण;

काष्ठा exynos_asv_table अणु
	अचिन्हित पूर्णांक num_rows;
	अचिन्हित पूर्णांक num_cols;
	u32 *buf;
पूर्ण;

काष्ठा exynos_asv_subsys अणु
	काष्ठा exynos_asv *asv;
	स्थिर अक्षर *cpu_dt_compat;
	पूर्णांक id;
	काष्ठा exynos_asv_table table;

	अचिन्हित पूर्णांक base_volt;
	अचिन्हित पूर्णांक offset_volt_h;
	अचिन्हित पूर्णांक offset_volt_l;
पूर्ण;

काष्ठा exynos_asv अणु
	काष्ठा device *dev;
	काष्ठा regmap *chipid_regmap;
	काष्ठा exynos_asv_subsys subsys[2];

	पूर्णांक (*opp_get_voltage)(स्थिर काष्ठा exynos_asv_subsys *subs,
			       पूर्णांक level, अचिन्हित पूर्णांक voltage);
	अचिन्हित पूर्णांक group;
	अचिन्हित पूर्णांक table;

	/* True अगर SG fields from PKG_ID रेजिस्टर should be used */
	bool use_sg;
	/* ASV bin पढ़ो from DT */
	पूर्णांक of_bin;
पूर्ण;

अटल अंतरभूत u32 __asv_get_table_entry(स्थिर काष्ठा exynos_asv_table *table,
					अचिन्हित पूर्णांक row, अचिन्हित पूर्णांक col)
अणु
	वापस table->buf[row * (table->num_cols) + col];
पूर्ण

अटल अंतरभूत u32 exynos_asv_opp_get_voltage(स्थिर काष्ठा exynos_asv_subsys *subsys,
					अचिन्हित पूर्णांक level, अचिन्हित पूर्णांक group)
अणु
	वापस __asv_get_table_entry(&subsys->table, level, group + 1);
पूर्ण

अटल अंतरभूत u32 exynos_asv_opp_get_frequency(स्थिर काष्ठा exynos_asv_subsys *subsys,
					अचिन्हित पूर्णांक level)
अणु
	वापस __asv_get_table_entry(&subsys->table, level, 0);
पूर्ण

पूर्णांक exynos_asv_init(काष्ठा device *dev, काष्ठा regmap *regmap);

#पूर्ण_अगर /* __LINUX_SOC_EXYNOS_ASV_H */
