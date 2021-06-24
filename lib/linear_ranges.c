<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * helpers to map values in a linear range to range index
 *
 * Original idea borrowed from regulator framework
 *
 * It might be useful अगर we could support also inversely proportional ranges?
 * Copyright 2020 ROHM Semiconductors
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/linear_range.h>
#समावेश <linux/module.h>

/**
 * linear_range_values_in_range - वापस the amount of values in a range
 * @r:		poपूर्णांकer to linear range where values are counted
 *
 * Compute the amount of values in range poपूर्णांकed by @r. Note, values can
 * be all equal - range with selectors 0,...,2 with step 0 still contains
 * 3 values even though they are all equal.
 *
 * Return: the amount of values in range poपूर्णांकed by @r
 */
अचिन्हित पूर्णांक linear_range_values_in_range(स्थिर काष्ठा linear_range *r)
अणु
	अगर (!r)
		वापस 0;
	वापस r->max_sel - r->min_sel + 1;
पूर्ण
EXPORT_SYMBOL_GPL(linear_range_values_in_range);

/**
 * linear_range_values_in_range_array - वापस the amount of values in ranges
 * @r:		poपूर्णांकer to array of linear ranges where values are counted
 * @ranges:	amount of ranges we include in computation.
 *
 * Compute the amount of values in ranges poपूर्णांकed by @r. Note, values can
 * be all equal - range with selectors 0,...,2 with step 0 still contains
 * 3 values even though they are all equal.
 *
 * Return: the amount of values in first @ranges ranges poपूर्णांकed by @r
 */
अचिन्हित पूर्णांक linear_range_values_in_range_array(स्थिर काष्ठा linear_range *r,
						पूर्णांक ranges)
अणु
	पूर्णांक i, values_in_range = 0;

	क्रम (i = 0; i < ranges; i++) अणु
		पूर्णांक values;

		values = linear_range_values_in_range(&r[i]);
		अगर (!values)
			वापस values;

		values_in_range += values;
	पूर्ण
	वापस values_in_range;
पूर्ण
EXPORT_SYMBOL_GPL(linear_range_values_in_range_array);

/**
 * linear_range_get_max_value - वापस the largest value in a range
 * @r:		poपूर्णांकer to linear range where value is looked from
 *
 * Return: the largest value in the given range
 */
अचिन्हित पूर्णांक linear_range_get_max_value(स्थिर काष्ठा linear_range *r)
अणु
	वापस r->min + (r->max_sel - r->min_sel) * r->step;
पूर्ण
EXPORT_SYMBOL_GPL(linear_range_get_max_value);

/**
 * linear_range_get_value - fetch a value from given range
 * @r:		poपूर्णांकer to linear range where value is looked from
 * @selector:	selector क्रम which the value is searched
 * @val:	address where found value is updated
 *
 * Search given ranges क्रम value which matches given selector.
 *
 * Return: 0 on success, -EINVAL given selector is not found from any of the
 * ranges.
 */
पूर्णांक linear_range_get_value(स्थिर काष्ठा linear_range *r, अचिन्हित पूर्णांक selector,
			   अचिन्हित पूर्णांक *val)
अणु
	अगर (r->min_sel > selector || r->max_sel < selector)
		वापस -EINVAL;

	*val = r->min + (selector - r->min_sel) * r->step;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(linear_range_get_value);

/**
 * linear_range_get_value_array - fetch a value from array of ranges
 * @r:		poपूर्णांकer to array of linear ranges where value is looked from
 * @ranges:	amount of ranges in an array
 * @selector:	selector क्रम which the value is searched
 * @val:	address where found value is updated
 *
 * Search through an array of ranges क्रम value which matches given selector.
 *
 * Return: 0 on success, -EINVAL given selector is not found from any of the
 * ranges.
 */
पूर्णांक linear_range_get_value_array(स्थिर काष्ठा linear_range *r, पूर्णांक ranges,
				 अचिन्हित पूर्णांक selector, अचिन्हित पूर्णांक *val)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ranges; i++)
		अगर (r[i].min_sel <= selector && r[i].max_sel >= selector)
			वापस linear_range_get_value(&r[i], selector, val);

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(linear_range_get_value_array);

/**
 * linear_range_get_selector_low - वापस linear range selector क्रम value
 * @r:		poपूर्णांकer to linear range where selector is looked from
 * @val:	value क्रम which the selector is searched
 * @selector:	address where found selector value is updated
 * @found:	flag to indicate that given value was in the range
 *
 * Return selector क्रम which range value is बंदst match क्रम given
 * input value. Value is matching अगर it is equal or smaller than given
 * value. If given value is in the range, then @found is set true.
 *
 * Return: 0 on success, -EINVAL अगर range is invalid or करोes not contain
 * value smaller or equal to given value
 */
पूर्णांक linear_range_get_selector_low(स्थिर काष्ठा linear_range *r,
				  अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक *selector,
				  bool *found)
अणु
	*found = false;

	अगर (r->min > val)
		वापस -EINVAL;

	अगर (linear_range_get_max_value(r) < val) अणु
		*selector = r->max_sel;
		वापस 0;
	पूर्ण

	*found = true;

	अगर (r->step == 0)
		*selector = r->min_sel;
	अन्यथा
		*selector = (val - r->min) / r->step + r->min_sel;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(linear_range_get_selector_low);

/**
 * linear_range_get_selector_low_array - वापस linear range selector क्रम value
 * @r:		poपूर्णांकer to array of linear ranges where selector is looked from
 * @ranges:	amount of ranges to scan from array
 * @val:	value क्रम which the selector is searched
 * @selector:	address where found selector value is updated
 * @found:	flag to indicate that given value was in the range
 *
 * Scan array of ranges क्रम selector क्रम which range value matches given
 * input value. Value is matching अगर it is equal or smaller than given
 * value. If given value is found to be in a range scanning is stopped and
 * @found is set true. If a range with values smaller than given value is found
 * but the range max is being smaller than given value, then the range's
 * biggest selector is updated to @selector but scanning ranges is जारीd
 * and @found is set to false.
 *
 * Return: 0 on success, -EINVAL अगर range array is invalid or करोes not contain
 * range with a value smaller or equal to given value
 */
पूर्णांक linear_range_get_selector_low_array(स्थिर काष्ठा linear_range *r,
					पूर्णांक ranges, अचिन्हित पूर्णांक val,
					अचिन्हित पूर्णांक *selector, bool *found)
अणु
	पूर्णांक i;
	पूर्णांक ret = -EINVAL;

	क्रम (i = 0; i < ranges; i++) अणु
		पूर्णांक पंचांगpret;

		पंचांगpret = linear_range_get_selector_low(&r[i], val, selector,
						       found);
		अगर (!पंचांगpret)
			ret = 0;

		अगर (*found)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(linear_range_get_selector_low_array);

/**
 * linear_range_get_selector_high - वापस linear range selector क्रम value
 * @r:		poपूर्णांकer to linear range where selector is looked from
 * @val:	value क्रम which the selector is searched
 * @selector:	address where found selector value is updated
 * @found:	flag to indicate that given value was in the range
 *
 * Return selector क्रम which range value is बंदst match क्रम given
 * input value. Value is matching अगर it is equal or higher than given
 * value. If given value is in the range, then @found is set true.
 *
 * Return: 0 on success, -EINVAL अगर range is invalid or करोes not contain
 * value greater or equal to given value
 */
पूर्णांक linear_range_get_selector_high(स्थिर काष्ठा linear_range *r,
				   अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक *selector,
				   bool *found)
अणु
	*found = false;

	अगर (linear_range_get_max_value(r) < val)
		वापस -EINVAL;

	अगर (r->min > val) अणु
		*selector = r->min_sel;
		वापस 0;
	पूर्ण

	*found = true;

	अगर (r->step == 0)
		*selector = r->max_sel;
	अन्यथा
		*selector = DIV_ROUND_UP(val - r->min, r->step) + r->min_sel;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(linear_range_get_selector_high);

MODULE_DESCRIPTION("linear-ranges helper");
MODULE_LICENSE("GPL");
