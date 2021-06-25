<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2020 ROHM Semiconductors */

#अगर_अघोषित LINEAR_RANGE_H
#घोषणा LINEAR_RANGE_H

#समावेश <linux/types.h>

/**
 * काष्ठा linear_range - table of selector - value pairs
 *
 * Define a lookup-table क्रम range of values. Intended to help when looking
 * क्रम a रेजिस्टर value matching certaing physical measure (like voltage).
 * Usable when increment of one in रेजिस्टर always results a स्थिरant increment
 * of the physical measure (like voltage).
 *
 * @min:  Lowest value in range
 * @min_sel: Lowest selector क्रम range
 * @max_sel: Highest selector क्रम range
 * @step: Value step size
 */
काष्ठा linear_range अणु
	अचिन्हित पूर्णांक min;
	अचिन्हित पूर्णांक min_sel;
	अचिन्हित पूर्णांक max_sel;
	अचिन्हित पूर्णांक step;
पूर्ण;

अचिन्हित पूर्णांक linear_range_values_in_range(स्थिर काष्ठा linear_range *r);
अचिन्हित पूर्णांक linear_range_values_in_range_array(स्थिर काष्ठा linear_range *r,
						पूर्णांक ranges);
अचिन्हित पूर्णांक linear_range_get_max_value(स्थिर काष्ठा linear_range *r);

पूर्णांक linear_range_get_value(स्थिर काष्ठा linear_range *r, अचिन्हित पूर्णांक selector,
			   अचिन्हित पूर्णांक *val);
पूर्णांक linear_range_get_value_array(स्थिर काष्ठा linear_range *r, पूर्णांक ranges,
				 अचिन्हित पूर्णांक selector, अचिन्हित पूर्णांक *val);
पूर्णांक linear_range_get_selector_low(स्थिर काष्ठा linear_range *r,
				  अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक *selector,
				  bool *found);
पूर्णांक linear_range_get_selector_high(स्थिर काष्ठा linear_range *r,
				   अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक *selector,
				   bool *found);
पूर्णांक linear_range_get_selector_low_array(स्थिर काष्ठा linear_range *r,
					पूर्णांक ranges, अचिन्हित पूर्णांक val,
					अचिन्हित पूर्णांक *selector, bool *found);

#पूर्ण_अगर
