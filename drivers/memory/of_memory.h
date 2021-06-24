<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OpenFirmware helpers क्रम memory drivers
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 * Copyright (C) 2020 Krzysztof Kozlowski <krzk@kernel.org>
 */

#अगर_अघोषित __LINUX_MEMORY_OF_REG_H
#घोषणा __LINUX_MEMORY_OF_REG_H

#अगर defined(CONFIG_OF) && defined(CONFIG_DDR)
स्थिर काष्ठा lpddr2_min_tck *of_get_min_tck(काष्ठा device_node *np,
					    काष्ठा device *dev);
स्थिर काष्ठा lpddr2_timings *of_get_ddr_timings(काष्ठा device_node *np_ddr,
						काष्ठा device *dev,
						u32 device_type, u32 *nr_frequencies);
स्थिर काष्ठा lpddr3_min_tck *of_lpddr3_get_min_tck(काष्ठा device_node *np,
						   काष्ठा device *dev);
स्थिर काष्ठा lpddr3_timings *
of_lpddr3_get_ddr_timings(काष्ठा device_node *np_ddr,
			  काष्ठा device *dev, u32 device_type, u32 *nr_frequencies);
#अन्यथा
अटल अंतरभूत स्थिर काष्ठा lpddr2_min_tck
	*of_get_min_tck(काष्ठा device_node *np, काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा lpddr2_timings
	*of_get_ddr_timings(काष्ठा device_node *np_ddr, काष्ठा device *dev,
	u32 device_type, u32 *nr_frequencies)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा lpddr3_min_tck
	*of_lpddr3_get_min_tck(काष्ठा device_node *np, काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा lpddr3_timings
	*of_lpddr3_get_ddr_timings(काष्ठा device_node *np_ddr,
	काष्ठा device *dev, u32 device_type, u32 *nr_frequencies)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF && CONFIG_DDR */

#पूर्ण_अगर /* __LINUX_MEMORY_OF_REG_ */
