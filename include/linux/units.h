<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_UNITS_H
#घोषणा _LINUX_UNITS_H

#समावेश <linux/गणित.स>

#घोषणा MILLIWATT_PER_WATT	1000L
#घोषणा MICROWATT_PER_MILLIWATT	1000L
#घोषणा MICROWATT_PER_WATT	1000000L

#घोषणा ABSOLUTE_ZERO_MILLICELSIUS -273150

अटल अंतरभूत दीर्घ milli_kelvin_to_millicelsius(दीर्घ t)
अणु
	वापस t + ABSOLUTE_ZERO_MILLICELSIUS;
पूर्ण

अटल अंतरभूत दीर्घ millicelsius_to_milli_kelvin(दीर्घ t)
अणु
	वापस t - ABSOLUTE_ZERO_MILLICELSIUS;
पूर्ण

#घोषणा MILLIDEGREE_PER_DEGREE 1000
#घोषणा MILLIDEGREE_PER_DECIDEGREE 100

अटल अंतरभूत दीर्घ kelvin_to_millicelsius(दीर्घ t)
अणु
	वापस milli_kelvin_to_millicelsius(t * MILLIDEGREE_PER_DEGREE);
पूर्ण

अटल अंतरभूत दीर्घ millicelsius_to_kelvin(दीर्घ t)
अणु
	t = millicelsius_to_milli_kelvin(t);

	वापस DIV_ROUND_CLOSEST(t, MILLIDEGREE_PER_DEGREE);
पूर्ण

अटल अंतरभूत दीर्घ deci_kelvin_to_celsius(दीर्घ t)
अणु
	t = milli_kelvin_to_millicelsius(t * MILLIDEGREE_PER_DECIDEGREE);

	वापस DIV_ROUND_CLOSEST(t, MILLIDEGREE_PER_DEGREE);
पूर्ण

अटल अंतरभूत दीर्घ celsius_to_deci_kelvin(दीर्घ t)
अणु
	t = millicelsius_to_milli_kelvin(t * MILLIDEGREE_PER_DEGREE);

	वापस DIV_ROUND_CLOSEST(t, MILLIDEGREE_PER_DECIDEGREE);
पूर्ण

/**
 * deci_kelvin_to_millicelsius_with_offset - convert Kelvin to Celsius
 * @t: temperature value in decidegrees Kelvin
 * @offset: dअगरference between Kelvin and Celsius in millidegrees
 *
 * Return: temperature value in millidegrees Celsius
 */
अटल अंतरभूत दीर्घ deci_kelvin_to_millicelsius_with_offset(दीर्घ t, दीर्घ offset)
अणु
	वापस t * MILLIDEGREE_PER_DECIDEGREE - offset;
पूर्ण

अटल अंतरभूत दीर्घ deci_kelvin_to_millicelsius(दीर्घ t)
अणु
	वापस milli_kelvin_to_millicelsius(t * MILLIDEGREE_PER_DECIDEGREE);
पूर्ण

अटल अंतरभूत दीर्घ millicelsius_to_deci_kelvin(दीर्घ t)
अणु
	t = millicelsius_to_milli_kelvin(t);

	वापस DIV_ROUND_CLOSEST(t, MILLIDEGREE_PER_DECIDEGREE);
पूर्ण

अटल अंतरभूत दीर्घ kelvin_to_celsius(दीर्घ t)
अणु
	वापस t + DIV_ROUND_CLOSEST(ABSOLUTE_ZERO_MILLICELSIUS,
				     MILLIDEGREE_PER_DEGREE);
पूर्ण

अटल अंतरभूत दीर्घ celsius_to_kelvin(दीर्घ t)
अणु
	वापस t - DIV_ROUND_CLOSEST(ABSOLUTE_ZERO_MILLICELSIUS,
				     MILLIDEGREE_PER_DEGREE);
पूर्ण

#पूर्ण_अगर /* _LINUX_UNITS_H */
