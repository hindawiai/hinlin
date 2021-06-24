<शैली गुरु>
/*
 * Created by: Jason Wessel <jason.wessel@windriver.com>
 *
 * Copyright (c) 2010 Wind River Systems, Inc.  All Rights Reserved.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/module.h>
#समावेश <linux/kdb.h>

/*
 * All kdb shell command call backs receive argc and argv, where
 * argv[0] is the command the end user typed
 */
अटल पूर्णांक kdb_hello_cmd(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	अगर (argc > 1)
		वापस KDB_ARGCOUNT;

	अगर (argc)
		kdb_म_लिखो("Hello %s.\n", argv[1]);
	अन्यथा
		kdb_म_लिखो("Hello world!\n");

	वापस 0;
पूर्ण


अटल पूर्णांक __init kdb_hello_cmd_init(व्योम)
अणु
	/*
	 * Registration of a dynamically added kdb command is करोne with
	 * kdb_रेजिस्टर() with the arguments being:
	 *   1: The name of the shell command
	 *   2: The function that processes the command
	 *   3: Description of the usage of any arguments
	 *   4: Descriptive text when you run help
	 *   5: Number of अक्षरacters to complete the command
	 *      0 == type the whole command
	 *      1 == match both "g" and "go" क्रम example
	 */
	kdb_रेजिस्टर("hello", kdb_hello_cmd, "[string]",
		     "Say Hello World or Hello [string]", 0);
	वापस 0;
पूर्ण

अटल व्योम __निकास kdb_hello_cmd_निकास(व्योम)
अणु
	kdb_unरेजिस्टर("hello");
पूर्ण

module_init(kdb_hello_cmd_init);
module_निकास(kdb_hello_cmd_निकास);

MODULE_AUTHOR("WindRiver");
MODULE_DESCRIPTION("KDB example to add a hello command");
MODULE_LICENSE("GPL");
