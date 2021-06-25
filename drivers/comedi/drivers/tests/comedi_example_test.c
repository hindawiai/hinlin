<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* vim: set ts=8 sw=8 noet tw=80 nowrap: */
/*
 *  comedi/drivers/tests/comedi_example_test.c
 *  Example set of unit tests.
 *
 *  COMEDI - Linux Control and Measurement Device Interface
 *  Copyright (C) 2016 Spencer E. Olson <olsonse@umich.edu>
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

#समावेश <linux/module.h>

#समावेश "unittest.h"

/* *** BEGIN fake board data *** */
काष्ठा comedi_device अणु
	स्थिर अक्षर *board_name;
	पूर्णांक item;
पूर्ण;

अटल काष्ठा comedi_device dev = अणु
	.board_name = "fake_device",
पूर्ण;

/* *** END fake board data *** */

/* *** BEGIN fake data init *** */
अटल व्योम init_fake(व्योम)
अणु
	dev.item = 10;
पूर्ण

/* *** END fake data init *** */

अटल व्योम test0(व्योम)
अणु
	init_fake();
	unittest(dev.item != 11, "negative result\n");
	unittest(dev.item == 10, "positive result\n");
पूर्ण

/* **** BEGIN simple module entry/निकास functions **** */
अटल पूर्णांक __init unittest_enter(व्योम)
अणु
	अटल स्थिर unittest_fptr unit_tests[] = अणु
		test0,
		शून्य,
	पूर्ण;

	exec_unittests("example", unit_tests);
	वापस 0;
पूर्ण

अटल व्योम __निकास unittest_निकास(व्योम) अणु पूर्ण

module_init(unittest_enter);
module_निकास(unittest_निकास);

MODULE_AUTHOR("Spencer Olson <olsonse@umich.edu>");
MODULE_DESCRIPTION("Comedi unit-tests example");
MODULE_LICENSE("GPL");
/* **** END simple module entry/निकास functions **** */
