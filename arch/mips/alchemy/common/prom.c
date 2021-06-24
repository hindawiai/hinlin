<शैली गुरु>
/*
 *
 * BRIEF MODULE DESCRIPTION
 *    PROM library initialisation code, supports YAMON and U-Boot.
 *
 * Copyright 2000-2001, 2006, 2008 MontaVista Software Inc.
 * Author: MontaVista Software, Inc. <source@mvista.com>
 *
 * This file was derived from Carsten Langgaard's
 * arch/mips/mips-boards/xx files.
 *
 * Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 1999,2000 MIPS Technologies, Inc.  All rights reserved.
 *
 *  This program is मुक्त software; you can redistribute  it and/or modअगरy it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS'' AND   ANY  EXPRESS OR IMPLIED
 *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   सूचीECT, INसूचीECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
 *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License aदीर्घ
 *  with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/memblock.h>
#समावेश <linux/sizes.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/bootinfo.h>

पूर्णांक prom_argc;
अक्षर **prom_argv;
अक्षर **prom_envp;

व्योम __init prom_init_cmdline(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 1; i < prom_argc; i++) अणु
		strlcat(arcs_cmdline, prom_argv[i], COMMAND_LINE_SIZE);
		अगर (i < (prom_argc - 1))
			strlcat(arcs_cmdline, " ", COMMAND_LINE_SIZE);
	पूर्ण
पूर्ण

अक्षर *prom_दो_पर्या(अक्षर *envname)
अणु
	/*
	 * Return a poपूर्णांकer to the given environment variable.
	 * YAMON uses "name", "value" pairs, जबतक U-Boot uses "name=value".
	 */

	अक्षर **env = prom_envp;
	पूर्णांक i = म_माप(envname);
	पूर्णांक yamon = (*env && म_अक्षर(*env, '=') == शून्य);

	जबतक (*env) अणु
		अगर (yamon) अणु
			अगर (म_भेद(envname, *env++) == 0)
				वापस *env;
		पूर्ण अन्यथा अगर (म_भेदन(envname, *env, i) == 0 && (*env)[i] == '=')
			वापस *env + i + 1;
		env++;
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम __init prom_init(व्योम)
अणु
	अचिन्हित अक्षर *memsize_str;
	अचिन्हित दीर्घ memsize;

	prom_argc = (पूर्णांक)fw_arg0;
	prom_argv = (अक्षर **)fw_arg1;
	prom_envp = (अक्षर **)fw_arg2;

	prom_init_cmdline();

	memsize_str = prom_दो_पर्या("memsize");
	अगर (!memsize_str || kम_से_अदीर्घ(memsize_str, 0, &memsize))
		memsize = SZ_64M; /* minimum memsize is 64MB RAM */

	memblock_add(0, memsize);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर str2hexnum(अचिन्हित अक्षर c)
अणु
	अगर (c >= '0' && c <= '9')
		वापस c - '0';
	अगर (c >= 'a' && c <= 'f')
		वापस c - 'a' + 10;
	अगर (c >= 'A' && c <= 'F')
		वापस c - 'A' + 10;

	वापस 0; /* foo */
पूर्ण

अटल अंतरभूत व्योम str2eaddr(अचिन्हित अक्षर *ea, अचिन्हित अक्षर *str)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 6; i++) अणु
		अचिन्हित अक्षर num;

		अगर ((*str == '.') || (*str == ':'))
			str++;
		num  = str2hexnum(*str++) << 4;
		num |= str2hexnum(*str++);
		ea[i] = num;
	पूर्ण
पूर्ण

पूर्णांक __init prom_get_ethernet_addr(अक्षर *ethernet_addr)
अणु
	अक्षर *ethaddr_str;

	/* Check the environment variables first */
	ethaddr_str = prom_दो_पर्या("ethaddr");
	अगर (!ethaddr_str) अणु
		/* Check command line */
		ethaddr_str = म_माला(arcs_cmdline, "ethaddr=");
		अगर (!ethaddr_str)
			वापस -1;

		ethaddr_str += म_माप("ethaddr=");
	पूर्ण

	str2eaddr(ethernet_addr, ethaddr_str);

	वापस 0;
पूर्ण
