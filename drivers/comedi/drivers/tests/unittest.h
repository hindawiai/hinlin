<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* vim: set ts=8 sw=8 noet tw=80 nowrap: */
/*
 *  comedi/drivers/tests/unittest.h
 *  Simple framework क्रम unittests क्रम comedi drivers.
 *
 *  COMEDI - Linux Control and Measurement Device Interface
 *  Copyright (C) 2016 Spencer E. Olson <olsonse@umich.edu>
 *  based of parts of drivers/of/unittest.c
 *
 *  This program is मुक्त software; you can redistribute it and/or modअगरy
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License क्रम more details.
 */

#अगर_अघोषित _COMEDI_DRIVERS_TESTS_UNITTEST_H
#घोषणा _COMEDI_DRIVERS_TESTS_UNITTEST_H

अटल काष्ठा unittest_results अणु
	पूर्णांक passed;
	पूर्णांक failed;
पूर्ण unittest_results;

प्रकार व्योम (*unittest_fptr)(व्योम);

#घोषणा unittest(result, fmt, ...) (अणु \
	bool failed = !(result); \
	अगर (failed) अणु \
		++unittest_results.failed; \
		pr_err("FAIL %s():%i " fmt, __func__, __LINE__, \
		       ##__VA_ARGS__); \
	पूर्ण अन्यथा अणु \
		++unittest_results.passed; \
		pr_debug("pass %s():%i " fmt, __func__, __LINE__, \
			 ##__VA_ARGS__); \
	पूर्ण \
	failed; \
पूर्ण)

/**
 * Execute an array of unit tests.
 * @name:	Name of set of unit tests--will be shown at INFO log level.
 * @unit_tests:	A null-terminated list of unit tests to execute.
 */
अटल अंतरभूत व्योम exec_unittests(स्थिर अक्षर *name,
				  स्थिर unittest_fptr *unit_tests)
अणु
	pr_info("begin comedi:\"%s\" unittests\n", name);

	क्रम (; (*unit_tests) != शून्य; ++unit_tests)
		(*unit_tests)();

	pr_info("end of comedi:\"%s\" unittests - %i passed, %i failed\n", name,
		unittest_results.passed, unittest_results.failed);
पूर्ण

#पूर्ण_अगर /* _COMEDI_DRIVERS_TESTS_UNITTEST_H */
