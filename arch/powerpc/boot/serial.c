<शैली गुरु>
/*
 * Generic serial console support
 *
 * Author: Mark A. Greer <mgreer@mvista.com>
 *
 * Code in serial_edit_cmdline() copied from <file:arch/ppc/boot/simple/misc.c>
 * and was written by Matt Porter <mporter@kernel.crashing.org>.
 *
 * 2001,2006 (c) MontaVista Software, Inc.  This file is licensed under
 * the terms of the GNU General Public License version 2.  This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */
#समावेश <मानकतर्क.स>
#समावेश <मानकघोष.स>
#समावेश "types.h"
#समावेश "string.h"
#समावेश "stdio.h"
#समावेश "io.h"
#समावेश "ops.h"

अटल पूर्णांक serial_खोलो(व्योम)
अणु
	काष्ठा serial_console_data *scdp = console_ops.data;
	वापस scdp->खोलो();
पूर्ण

अटल व्योम serial_ग_लिखो(स्थिर अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा serial_console_data *scdp = console_ops.data;

	जबतक (*buf != '\0')
		scdp->अ_दो(*buf++);
पूर्ण

अटल व्योम serial_edit_cmdline(अक्षर *buf, पूर्णांक len, अचिन्हित पूर्णांक समयout)
अणु
	पूर्णांक समयr = 0, count;
	अक्षर ch, *cp;
	काष्ठा serial_console_data *scdp = console_ops.data;

	cp = buf;
	count = म_माप(buf);
	cp = &buf[count];
	count++;

	करो अणु
		अगर (scdp->tstc()) अणु
			जबतक (((ch = scdp->अ_लो()) != '\n') && (ch != '\r')) अणु
				/* Test क्रम backspace/delete */
				अगर ((ch == '\b') || (ch == '\177')) अणु
					अगर (cp != buf) अणु
						cp--;
						count--;
						म_लिखो("\b \b");
					पूर्ण
				/* Test क्रम ^x/^u (and wipe the line) */
				पूर्ण अन्यथा अगर ((ch == '\030') || (ch == '\025')) अणु
					जबतक (cp != buf) अणु
						cp--;
						count--;
						म_लिखो("\b \b");
					पूर्ण
				पूर्ण अन्यथा अगर (count < len) अणु
						*cp++ = ch;
						count++;
						scdp->अ_दो(ch);
				पूर्ण
			पूर्ण
			अवरोध;  /* Exit 'timer' loop */
		पूर्ण
		udelay(1000);  /* 1 msec */
	पूर्ण जबतक (समयr++ < समयout);
	*cp = 0;
पूर्ण

अटल व्योम serial_बंद(व्योम)
अणु
	काष्ठा serial_console_data *scdp = console_ops.data;

	अगर (scdp->बंद)
		scdp->बंद();
पूर्ण

अटल व्योम *serial_get_मानक_निकास_devp(व्योम)
अणु
	व्योम *devp;
	अक्षर devtype[MAX_PROP_LEN];
	अक्षर path[MAX_PATH_LEN];

	devp = finddevice("/chosen");
	अगर (devp == शून्य)
		जाओ err_out;

	अगर (getprop(devp, "linux,stdout-path", path, MAX_PATH_LEN) > 0 ||
		getprop(devp, "stdout-path", path, MAX_PATH_LEN) > 0) अणु
		devp = finddevice(path);
		अगर (devp == शून्य)
			जाओ err_out;

		अगर ((getprop(devp, "device_type", devtype, माप(devtype)) > 0)
				&& !म_भेद(devtype, "serial"))
			वापस devp;
	पूर्ण
err_out:
	वापस शून्य;
पूर्ण

अटल काष्ठा serial_console_data serial_cd;

/* Node's "compatible" property determines which serial driver to use */
पूर्णांक serial_console_init(व्योम)
अणु
	व्योम *devp;
	पूर्णांक rc = -1;

	devp = serial_get_मानक_निकास_devp();
	अगर (devp == शून्य)
		जाओ err_out;

	अगर (dt_is_compatible(devp, "ns16550") ||
	    dt_is_compatible(devp, "pnpPNP,501"))
		rc = ns16550_console_init(devp, &serial_cd);
#अगर_घोषित CONFIG_CPM
	अन्यथा अगर (dt_is_compatible(devp, "fsl,cpm1-scc-uart") ||
	         dt_is_compatible(devp, "fsl,cpm1-smc-uart") ||
	         dt_is_compatible(devp, "fsl,cpm2-scc-uart") ||
	         dt_is_compatible(devp, "fsl,cpm2-smc-uart"))
		rc = cpm_console_init(devp, &serial_cd);
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_MPC52xx
	अन्यथा अगर (dt_is_compatible(devp, "fsl,mpc5200-psc-uart"))
		rc = mpc5200_psc_console_init(devp, &serial_cd);
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC64_BOOT_WRAPPER
	अन्यथा अगर (dt_is_compatible(devp, "ibm,opal-console-raw"))
		rc = opal_console_init(devp, &serial_cd);
#पूर्ण_अगर

	/* Add other serial console driver calls here */

	अगर (!rc) अणु
		console_ops.खोलो = serial_खोलो;
		console_ops.ग_लिखो = serial_ग_लिखो;
		console_ops.बंद = serial_बंद;
		console_ops.data = &serial_cd;

		अगर (serial_cd.अ_लो)
			console_ops.edit_cmdline = serial_edit_cmdline;

		वापस 0;
	पूर्ण
err_out:
	वापस -1;
पूर्ण
