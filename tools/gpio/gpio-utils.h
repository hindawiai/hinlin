<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * GPIO tools - utility helpers library क्रम the GPIO tools
 *
 * Copyright (C) 2015 Linus Walleij
 *
 * Portions copied from iio_utils and lssio:
 * Copyright (c) 2010 Manuel Stahl <manuel.stahl@iis.fraunhofer.de>
 * Copyright (c) 2008 Jonathan Cameron
 * *
 */
#अगर_अघोषित _GPIO_UTILS_H_
#घोषणा _GPIO_UTILS_H_

#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <linux/types.h>

#घोषणा ARRAY_SIZE(arr) (माप(arr) / माप((arr)[0]))

अटल अंतरभूत पूर्णांक check_prefix(स्थिर अक्षर *str, स्थिर अक्षर *prefix)
अणु
	वापस म_माप(str) > म_माप(prefix) &&
		म_भेदन(str, prefix, म_माप(prefix)) == 0;
पूर्ण

पूर्णांक gpiotools_request_line(स्थिर अक्षर *device_name,
			   अचिन्हित पूर्णांक *lines,
			   अचिन्हित पूर्णांक num_lines,
			   काष्ठा gpio_v2_line_config *config,
			   स्थिर अक्षर *consumer);
पूर्णांक gpiotools_set_values(स्थिर पूर्णांक fd, काष्ठा gpio_v2_line_values *values);
पूर्णांक gpiotools_get_values(स्थिर पूर्णांक fd, काष्ठा gpio_v2_line_values *values);
पूर्णांक gpiotools_release_line(स्थिर पूर्णांक fd);

पूर्णांक gpiotools_get(स्थिर अक्षर *device_name, अचिन्हित पूर्णांक line);
पूर्णांक gpiotools_माला_लो(स्थिर अक्षर *device_name, अचिन्हित पूर्णांक *lines,
		   अचिन्हित पूर्णांक num_lines, अचिन्हित पूर्णांक *values);
पूर्णांक gpiotools_set(स्थिर अक्षर *device_name, अचिन्हित पूर्णांक line,
		  अचिन्हित पूर्णांक value);
पूर्णांक gpiotools_sets(स्थिर अक्षर *device_name, अचिन्हित पूर्णांक *lines,
		   अचिन्हित पूर्णांक num_lines, अचिन्हित पूर्णांक *values);

/* helper functions क्रम gpio_v2_line_values bits */
अटल अंतरभूत व्योम gpiotools_set_bit(__u64 *b, पूर्णांक n)
अणु
	*b |= _BITULL(n);
पूर्ण

अटल अंतरभूत व्योम gpiotools_change_bit(__u64 *b, पूर्णांक n)
अणु
	*b ^= _BITULL(n);
पूर्ण

अटल अंतरभूत व्योम gpiotools_clear_bit(__u64 *b, पूर्णांक n)
अणु
	*b &= ~_BITULL(n);
पूर्ण

अटल अंतरभूत पूर्णांक gpiotools_test_bit(__u64 b, पूर्णांक n)
अणु
	वापस !!(b & _BITULL(n));
पूर्ण

अटल अंतरभूत व्योम gpiotools_assign_bit(__u64 *b, पूर्णांक n, bool value)
अणु
	अगर (value)
		gpiotools_set_bit(b, n);
	अन्यथा
		gpiotools_clear_bit(b, n);
पूर्ण

#पूर्ण_अगर /* _GPIO_UTILS_H_ */
