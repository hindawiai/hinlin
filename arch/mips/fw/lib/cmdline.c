<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2012 MIPS Technologies, Inc.  All rights reserved.
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/fw/fw.h>

पूर्णांक fw_argc;
पूर्णांक *_fw_argv;
पूर्णांक *_fw_envp;

#अगर_अघोषित CONFIG_HAVE_PLAT_FW_INIT_CMDLINE
व्योम __init fw_init_cmdline(व्योम)
अणु
	पूर्णांक i;

	/* Validate command line parameters. */
	अगर ((fw_arg0 >= CKSEG0) || (fw_arg1 < CKSEG0)) अणु
		fw_argc = 0;
		_fw_argv = शून्य;
	पूर्ण अन्यथा अणु
		fw_argc = (fw_arg0 & 0x0000ffff);
		_fw_argv = (पूर्णांक *)fw_arg1;
	पूर्ण

	/* Validate environment poपूर्णांकer. */
	अगर (fw_arg2 < CKSEG0)
		_fw_envp = शून्य;
	अन्यथा
		_fw_envp = (पूर्णांक *)fw_arg2;

	क्रम (i = 1; i < fw_argc; i++) अणु
		strlcat(arcs_cmdline, fw_argv(i), COMMAND_LINE_SIZE);
		अगर (i < (fw_argc - 1))
			strlcat(arcs_cmdline, " ", COMMAND_LINE_SIZE);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अक्षर * __init fw_अ_लोmdline(व्योम)
अणु
	वापस &(arcs_cmdline[0]);
पूर्ण

अक्षर *fw_दो_पर्या(अक्षर *envname)
अणु
	अक्षर *result = शून्य;

	अगर (_fw_envp != शून्य) अणु
		/*
		 * Return a poपूर्णांकer to the given environment variable.
		 * YAMON uses "name", "value" pairs, जबतक U-Boot uses
		 * "name=value".
		 */
		पूर्णांक i, yamon, index = 0;

		yamon = (म_अक्षर(fw_envp(index), '=') == शून्य);
		i = म_माप(envname);

		जबतक (fw_envp(index)) अणु
			अगर (म_भेदन(envname, fw_envp(index), i) == 0) अणु
				अगर (yamon) अणु
					result = fw_envp(index + 1);
					अवरोध;
				पूर्ण अन्यथा अगर (fw_envp(index)[i] == '=') अणु
					result = fw_envp(index) + i + 1;
					अवरोध;
				पूर्ण
			पूर्ण

			/* Increment array index. */
			अगर (yamon)
				index += 2;
			अन्यथा
				index += 1;
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण

अचिन्हित दीर्घ fw_दो_पर्याl(अक्षर *envname)
अणु
	अचिन्हित दीर्घ envl = 0UL;
	अक्षर *str;
	पूर्णांक पंचांगp;

	str = fw_दो_पर्या(envname);
	अगर (str) अणु
		पंचांगp = kम_से_अदीर्घ(str, 0, &envl);
		अगर (पंचांगp)
			envl = 0;
	पूर्ण

	वापस envl;
पूर्ण
