<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Support क्रम the OLPC DCON and OLPC EC access
 *
 * Copyright तऊ 2006  Advanced Micro Devices, Inc.
 * Copyright तऊ 2007-2008  Andres Salomon <dilinger@debian.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/माला.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/mutex.h>
#समावेश <linux/olpc-ec.h>

#समावेश <यंत्र/geode.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/olpc.h>
#समावेश <यंत्र/olpc_ofw.h>

काष्ठा olpc_platक्रमm_t olpc_platक्रमm_info;
EXPORT_SYMBOL_GPL(olpc_platक्रमm_info);

/* what the समयout *should* be (in ms) */
#घोषणा EC_BASE_TIMEOUT 20

/* the समयout that bugs in the EC might क्रमce us to actually use */
अटल पूर्णांक ec_समयout = EC_BASE_TIMEOUT;

अटल पूर्णांक __init olpc_ec_समयout_set(अक्षर *str)
अणु
	अगर (get_option(&str, &ec_समयout) != 1) अणु
		ec_समयout = EC_BASE_TIMEOUT;
		prपूर्णांकk(KERN_ERR "olpc-ec:  invalid argument to "
				"'olpc_ec_timeout=', ignoring!\n");
	पूर्ण
	prपूर्णांकk(KERN_DEBUG "olpc-ec:  using %d ms delay for EC commands.\n",
			ec_समयout);
	वापस 1;
पूर्ण
__setup("olpc_ec_timeout=", olpc_ec_समयout_set);

/*
 * These अणुi,oपूर्णbf_status functions वापस whether the buffers are full or not.
 */

अटल अंतरभूत अचिन्हित पूर्णांक ibf_status(अचिन्हित पूर्णांक port)
अणु
	वापस !!(inb(port) & 0x02);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक obf_status(अचिन्हित पूर्णांक port)
अणु
	वापस inb(port) & 0x01;
पूर्ण

#घोषणा रुको_on_ibf(p, d) __रुको_on_ibf(__LINE__, (p), (d))
अटल पूर्णांक __रुको_on_ibf(अचिन्हित पूर्णांक line, अचिन्हित पूर्णांक port, पूर्णांक desired)
अणु
	अचिन्हित पूर्णांक समयo;
	पूर्णांक state = ibf_status(port);

	क्रम (समयo = ec_समयout; state != desired && समयo; समयo--) अणु
		mdelay(1);
		state = ibf_status(port);
	पूर्ण

	अगर ((state == desired) && (ec_समयout > EC_BASE_TIMEOUT) &&
			समयo < (ec_समयout - EC_BASE_TIMEOUT)) अणु
		prपूर्णांकk(KERN_WARNING "olpc-ec:  %d: waited %u ms for IBF!\n",
				line, ec_समयout - समयo);
	पूर्ण

	वापस !(state == desired);
पूर्ण

#घोषणा रुको_on_obf(p, d) __रुको_on_obf(__LINE__, (p), (d))
अटल पूर्णांक __रुको_on_obf(अचिन्हित पूर्णांक line, अचिन्हित पूर्णांक port, पूर्णांक desired)
अणु
	अचिन्हित पूर्णांक समयo;
	पूर्णांक state = obf_status(port);

	क्रम (समयo = ec_समयout; state != desired && समयo; समयo--) अणु
		mdelay(1);
		state = obf_status(port);
	पूर्ण

	अगर ((state == desired) && (ec_समयout > EC_BASE_TIMEOUT) &&
			समयo < (ec_समयout - EC_BASE_TIMEOUT)) अणु
		prपूर्णांकk(KERN_WARNING "olpc-ec:  %d: waited %u ms for OBF!\n",
				line, ec_समयout - समयo);
	पूर्ण

	वापस !(state == desired);
पूर्ण

/*
 * This allows the kernel to run Embedded Controller commands.  The EC is
 * करोcumented at <http://wiki.laptop.org/go/Embedded_controller>, and the
 * available EC commands are here:
 * <http://wiki.laptop.org/go/Ec_specअगरication>.  Unक्रमtunately, जबतक
 * OpenFirmware's source is available, the EC's is not.
 */
अटल पूर्णांक olpc_xo1_ec_cmd(u8 cmd, u8 *inbuf, माप_प्रकार inlen, u8 *outbuf,
		माप_प्रकार outlen, व्योम *arg)
अणु
	पूर्णांक ret = -EIO;
	पूर्णांक i;
	पूर्णांक restarts = 0;

	/* Clear OBF */
	क्रम (i = 0; i < 10 && (obf_status(0x6c) == 1); i++)
		inb(0x68);
	अगर (i == 10) अणु
		prपूर्णांकk(KERN_ERR "olpc-ec:  timeout while attempting to "
				"clear OBF flag!\n");
		जाओ err;
	पूर्ण

	अगर (रुको_on_ibf(0x6c, 0)) अणु
		prपूर्णांकk(KERN_ERR "olpc-ec:  timeout waiting for EC to "
				"quiesce!\n");
		जाओ err;
	पूर्ण

restart:
	/*
	 * Note that अगर we समय out during any IBF checks, that's a failure;
	 * we have to वापस.  There's no way क्रम the kernel to clear that.
	 *
	 * If we समय out during an OBF check, we can restart the command;
	 * reissuing it will clear the OBF flag, and we should be alright.
	 * The OBF flag will someबार misbehave due to what we believe
	 * is a hardware quirk..
	 */
	pr_devel("olpc-ec:  running cmd 0x%x\n", cmd);
	outb(cmd, 0x6c);

	अगर (रुको_on_ibf(0x6c, 0)) अणु
		prपूर्णांकk(KERN_ERR "olpc-ec:  timeout waiting for EC to read "
				"command!\n");
		जाओ err;
	पूर्ण

	अगर (inbuf && inlen) अणु
		/* ग_लिखो data to EC */
		क्रम (i = 0; i < inlen; i++) अणु
			pr_devel("olpc-ec:  sending cmd arg 0x%x\n", inbuf[i]);
			outb(inbuf[i], 0x68);
			अगर (रुको_on_ibf(0x6c, 0)) अणु
				prपूर्णांकk(KERN_ERR "olpc-ec:  timeout waiting for"
						" EC accept data!\n");
				जाओ err;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (outbuf && outlen) अणु
		/* पढ़ो data from EC */
		क्रम (i = 0; i < outlen; i++) अणु
			अगर (रुको_on_obf(0x6c, 1)) अणु
				prपूर्णांकk(KERN_ERR "olpc-ec:  timeout waiting for"
						" EC to provide data!\n");
				अगर (restarts++ < 10)
					जाओ restart;
				जाओ err;
			पूर्ण
			outbuf[i] = inb(0x68);
			pr_devel("olpc-ec:  received 0x%x\n", outbuf[i]);
		पूर्ण
	पूर्ण

	ret = 0;
err:
	वापस ret;
पूर्ण

अटल bool __init check_ofw_architecture(काष्ठा device_node *root)
अणु
	स्थिर अक्षर *olpc_arch;
	पूर्णांक propsize;

	olpc_arch = of_get_property(root, "architecture", &propsize);
	वापस propsize == 5 && म_भेदन("OLPC", olpc_arch, 5) == 0;
पूर्ण

अटल u32 __init get_board_revision(काष्ठा device_node *root)
अणु
	पूर्णांक propsize;
	स्थिर __be32 *rev;

	rev = of_get_property(root, "board-revision-int", &propsize);
	अगर (propsize != 4)
		वापस 0;

	वापस be32_to_cpu(*rev);
पूर्ण

अटल bool __init platक्रमm_detect(व्योम)
अणु
	काष्ठा device_node *root = of_find_node_by_path("/");
	bool success;

	अगर (!root)
		वापस false;

	success = check_ofw_architecture(root);
	अगर (success) अणु
		olpc_platक्रमm_info.boardrev = get_board_revision(root);
		olpc_platक्रमm_info.flags |= OLPC_F_PRESENT;

		pr_info("OLPC board revision %s%X\n",
			((olpc_platक्रमm_info.boardrev & 0xf) < 8) ? "pre" : "",
			olpc_platक्रमm_info.boardrev >> 4);
	पूर्ण

	of_node_put(root);
	वापस success;
पूर्ण

अटल पूर्णांक __init add_xo1_platक्रमm_devices(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;

	pdev = platक्रमm_device_रेजिस्टर_simple("xo1-rfkill", -1, शून्य, 0);
	अगर (IS_ERR(pdev))
		वापस PTR_ERR(pdev);

	pdev = platक्रमm_device_रेजिस्टर_simple("olpc-xo1", -1, शून्य, 0);

	वापस PTR_ERR_OR_ZERO(pdev);
पूर्ण

अटल पूर्णांक olpc_xo1_ec_suspend(काष्ठा platक्रमm_device *pdev)
अणु
	/*
	 * Squelch SCIs जबतक suspended.  This is a fix क्रम
	 * <http://dev.laptop.org/ticket/1835>.
	 */
	वापस olpc_ec_cmd(EC_SET_SCI_INHIBIT, शून्य, 0, शून्य, 0);
पूर्ण

अटल पूर्णांक olpc_xo1_ec_resume(काष्ठा platक्रमm_device *pdev)
अणु
	/* Tell the EC to stop inhibiting SCIs */
	olpc_ec_cmd(EC_SET_SCI_INHIBIT_RELEASE, शून्य, 0, शून्य, 0);

	/*
	 * Tell the wireless module to restart USB communication.
	 * Must be करोne twice.
	 */
	olpc_ec_cmd(EC_WAKE_UP_WLAN, शून्य, 0, शून्य, 0);
	olpc_ec_cmd(EC_WAKE_UP_WLAN, शून्य, 0, शून्य, 0);

	वापस 0;
पूर्ण

अटल काष्ठा olpc_ec_driver ec_xo1_driver = अणु
	.suspend = olpc_xo1_ec_suspend,
	.resume = olpc_xo1_ec_resume,
	.ec_cmd = olpc_xo1_ec_cmd,
#अगर_घोषित CONFIG_OLPC_XO1_SCI
	/*
	 * XO-1 EC wakeups are available when olpc-xo1-sci driver is
	 * compiled in
	 */
	.wakeup_available = true,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा olpc_ec_driver ec_xo1_5_driver = अणु
	.ec_cmd = olpc_xo1_ec_cmd,
#अगर_घोषित CONFIG_OLPC_XO1_5_SCI
	/*
	 * XO-1.5 EC wakeups are available when olpc-xo15-sci driver is
	 * compiled in
	 */
	.wakeup_available = true,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init olpc_init(व्योम)
अणु
	पूर्णांक r = 0;

	अगर (!olpc_ofw_present() || !platक्रमm_detect())
		वापस 0;

	/* रेजिस्टर the XO-1 and 1.5-specअगरic EC handler */
	अगर (olpc_platक्रमm_info.boardrev < olpc_board_pre(0xd0))	/* XO-1 */
		olpc_ec_driver_रेजिस्टर(&ec_xo1_driver, शून्य);
	अन्यथा
		olpc_ec_driver_रेजिस्टर(&ec_xo1_5_driver, शून्य);
	platक्रमm_device_रेजिस्टर_simple("olpc-ec", -1, शून्य, 0);

	/* assume B1 and above models always have a DCON */
	अगर (olpc_board_at_least(olpc_board(0xb1)))
		olpc_platक्रमm_info.flags |= OLPC_F_DCON;

#अगर_घोषित CONFIG_PCI_OLPC
	/* If the VSA exists let it emulate PCI, अगर not emulate in kernel.
	 * XO-1 only. */
	अगर (olpc_platक्रमm_info.boardrev < olpc_board_pre(0xd0) &&
			!cs5535_has_vsa2())
		x86_init.pci.arch_init = pci_olpc_init;
#पूर्ण_अगर

	अगर (olpc_platक्रमm_info.boardrev < olpc_board_pre(0xd0)) अणु /* XO-1 */
		r = add_xo1_platक्रमm_devices();
		अगर (r)
			वापस r;
	पूर्ण

	वापस 0;
पूर्ण

postcore_initcall(olpc_init);
