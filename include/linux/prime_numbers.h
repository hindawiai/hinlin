<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_PRIME_NUMBERS_H
#घोषणा __LINUX_PRIME_NUMBERS_H

#समावेश <linux/types.h>

bool is_prime_number(अचिन्हित दीर्घ x);
अचिन्हित दीर्घ next_prime_number(अचिन्हित दीर्घ x);

/**
 * क्रम_each_prime_number - iterate over each prime upto a value
 * @prime: the current prime number in this iteration
 * @max: the upper limit
 *
 * Starting from the first prime number 2 iterate over each prime number up to
 * the @max value. On each iteration, @prime is set to the current prime number.
 * @max should be less than अच_दीर्घ_उच्च to ensure termination. To begin with
 * @prime set to 1 on the first iteration use क्रम_each_prime_number_from()
 * instead.
 */
#घोषणा क्रम_each_prime_number(prime, max) \
	क्रम_each_prime_number_from((prime), 2, (max))

/**
 * क्रम_each_prime_number_from - iterate over each prime upto a value
 * @prime: the current prime number in this iteration
 * @from: the initial value
 * @max: the upper limit
 *
 * Starting from @from iterate over each successive prime number up to the
 * @max value. On each iteration, @prime is set to the current prime number.
 * @max should be less than अच_दीर्घ_उच्च, and @from less than @max, to ensure
 * termination.
 */
#घोषणा क्रम_each_prime_number_from(prime, from, max) \
	क्रम (prime = (from); prime <= (max); prime = next_prime_number(prime))

#पूर्ण_अगर /* !__LINUX_PRIME_NUMBERS_H */
