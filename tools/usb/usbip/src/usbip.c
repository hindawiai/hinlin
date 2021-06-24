<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * command काष्ठाure borrowed from udev
 * (git://git.kernel.org/pub/scm/linux/hotplug/udev.git)
 *
 * Copyright (C) 2011 matt mooney <mfm@muteddisk.com>
 *               2005-2007 Takahiro Hirofuchi
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>

#समावेश <getopt.h>
#समावेश <syslog.h>

#समावेश "usbip_common.h"
#समावेश "usbip_network.h"
#समावेश "usbip.h"

अटल पूर्णांक usbip_help(पूर्णांक argc, अक्षर *argv[]);
अटल पूर्णांक usbip_version(पूर्णांक argc, अक्षर *argv[]);

अटल स्थिर अक्षर usbip_version_string[] = PACKAGE_STRING;

अटल स्थिर अक्षर usbip_usage_string[] =
	"usbip [--debug] [--log] [--tcp-port PORT] [version]\n"
	"             [help] <command> <args>\n";

अटल व्योम usbip_usage(व्योम)
अणु
	म_लिखो("usage: %s", usbip_usage_string);
पूर्ण

काष्ठा command अणु
	स्थिर अक्षर *name;
	पूर्णांक (*fn)(पूर्णांक argc, अक्षर *argv[]);
	स्थिर अक्षर *help;
	व्योम (*usage)(व्योम);
पूर्ण;

अटल स्थिर काष्ठा command cmds[] = अणु
	अणु
		.name  = "help",
		.fn    = usbip_help,
		.help  = शून्य,
		.usage = शून्य
	पूर्ण,
	अणु
		.name  = "version",
		.fn    = usbip_version,
		.help  = शून्य,
		.usage = शून्य
	पूर्ण,
	अणु
		.name  = "attach",
		.fn    = usbip_attach,
		.help  = "Attach a remote USB device",
		.usage = usbip_attach_usage
	पूर्ण,
	अणु
		.name  = "detach",
		.fn    = usbip_detach,
		.help  = "Detach a remote USB device",
		.usage = usbip_detach_usage
	पूर्ण,
	अणु
		.name  = "list",
		.fn    = usbip_list,
		.help  = "List exportable or local USB devices",
		.usage = usbip_list_usage
	पूर्ण,
	अणु
		.name  = "bind",
		.fn    = usbip_bind,
		.help  = "Bind device to " USBIP_HOST_DRV_NAME ".ko",
		.usage = usbip_bind_usage
	पूर्ण,
	अणु
		.name  = "unbind",
		.fn    = usbip_unbind,
		.help  = "Unbind device from " USBIP_HOST_DRV_NAME ".ko",
		.usage = usbip_unbind_usage
	पूर्ण,
	अणु
		.name  = "port",
		.fn    = usbip_port_show,
		.help  = "Show imported USB devices",
		.usage = शून्य
	पूर्ण,
	अणु शून्य, शून्य, शून्य, शून्य पूर्ण
पूर्ण;

अटल पूर्णांक usbip_help(पूर्णांक argc, अक्षर *argv[])
अणु
	स्थिर काष्ठा command *cmd;
	पूर्णांक i;
	पूर्णांक ret = 0;

	अगर (argc > 1 && argv++) अणु
		क्रम (i = 0; cmds[i].name != शून्य; i++)
			अगर (!म_भेद(cmds[i].name, argv[0]) && cmds[i].usage) अणु
				cmds[i].usage();
				जाओ करोne;
			पूर्ण
		ret = -1;
	पूर्ण

	usbip_usage();
	म_लिखो("\n");
	क्रम (cmd = cmds; cmd->name != शून्य; cmd++)
		अगर (cmd->help != शून्य)
			म_लिखो("  %-10s %s\n", cmd->name, cmd->help);
	म_लिखो("\n");
करोne:
	वापस ret;
पूर्ण

अटल पूर्णांक usbip_version(पूर्णांक argc, अक्षर *argv[])
अणु
	(व्योम) argc;
	(व्योम) argv;

	म_लिखो(PROGNAME " (%s)\n", usbip_version_string);
	वापस 0;
पूर्ण

अटल पूर्णांक run_command(स्थिर काष्ठा command *cmd, पूर्णांक argc, अक्षर *argv[])
अणु
	dbg("running command: `%s'", cmd->name);
	वापस cmd->fn(argc, argv);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	अटल स्थिर काष्ठा option opts[] = अणु
		अणु "debug",    no_argument,       शून्य, 'd' पूर्ण,
		अणु "log",      no_argument,       शून्य, 'l' पूर्ण,
		अणु "tcp-port", required_argument, शून्य, 't' पूर्ण,
		अणु शून्य,       0,                 शून्य,  0  पूर्ण
	पूर्ण;

	अक्षर *cmd;
	पूर्णांक opt;
	पूर्णांक i, rc = -1;

	usbip_use_मानक_त्रुटि = 1;
	opterr = 0;
	क्रम (;;) अणु
		opt = getopt_दीर्घ(argc, argv, "+dlt:", opts, शून्य);

		अगर (opt == -1)
			अवरोध;

		चयन (opt) अणु
		हाल 'd':
			usbip_use_debug = 1;
			अवरोध;
		हाल 'l':
			usbip_use_syslog = 1;
			खोलोlog("", LOG_PID, LOG_USER);
			अवरोध;
		हाल 't':
			usbip_setup_port_number(optarg);
			अवरोध;
		हाल '?':
			म_लिखो("usbip: invalid option\n");
			/* Terminate after prपूर्णांकing error */
			/* FALLTHRU */
		शेष:
			usbip_usage();
			जाओ out;
		पूर्ण
	पूर्ण

	cmd = argv[optind];
	अगर (cmd) अणु
		क्रम (i = 0; cmds[i].name != शून्य; i++)
			अगर (!म_भेद(cmds[i].name, cmd)) अणु
				argc -= optind;
				argv += optind;
				optind = 0;
				rc = run_command(&cmds[i], argc, argv);
				जाओ out;
			पूर्ण
	पूर्ण

	/* invalid command */
	usbip_help(0, शून्य);
out:
	वापस (rc > -1 ? निकास_सफल : निकास_त्रुटि);
पूर्ण
