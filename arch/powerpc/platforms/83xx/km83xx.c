<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2008-2011 DENX Software Engineering GmbH
 * Author: Heiko Schocher <hs@denx.de>
 *
 * Description:
 * Keymile 83xx platक्रमm specअगरic routines.
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/reboot.h>
#समावेश <linux/pci.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/major.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/root_dev.h>
#समावेश <linux/initrd.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_device.h>

#समावेश <linux/atomic.h>
#समावेश <linux/समय.स>
#समावेश <linux/पन.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/ipic.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/udbg.h>
#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/fsl_pci.h>
#समावेश <soc/fsl/qe/qe.h>

#समावेश "mpc83xx.h"

#घोषणा SVR_REV(svr)    (((svr) >>  0) & 0xFFFF) /* Revision field */

अटल व्योम quirk_mpc8360e_qe_enet10(व्योम)
अणु
	/*
	 * handle mpc8360E Erratum QE_ENET10:
	 * RGMII AC values करो not meet the specअगरication
	 */
	uपूर्णांक svid = mfspr(SPRN_SVR);
	काष्ठा	device_node *np_par;
	काष्ठा	resource res;
	व्योम	__iomem *base;
	पूर्णांक	ret;

	np_par = of_find_node_by_name(शून्य, "par_io");
	अगर (np_par == शून्य) अणु
		pr_warn("%s couldn't find par_io node\n", __func__);
		वापस;
	पूर्ण
	/* Map Parallel I/O ports रेजिस्टरs */
	ret = of_address_to_resource(np_par, 0, &res);
	अगर (ret) अणु
		pr_warn("%s couldn't map par_io registers\n", __func__);
		जाओ out;
	पूर्ण

	base = ioremap(res.start, resource_size(&res));
	अगर (!base)
		जाओ out;

	/*
	 * set output delay adjusपंचांगents to शेष values according
	 * table 5 in Errata Rev. 5, 9/2011:
	 *
	 * ग_लिखो 0b01 to UCC1 bits 18:19
	 * ग_लिखो 0b01 to UCC2 option 1 bits 4:5
	 * ग_लिखो 0b01 to UCC2 option 2 bits 16:17
	 */
	clrsetbits_be32((base + 0xa8), 0x0c00f000, 0x04005000);

	/*
	 * set output delay adjusपंचांगents to शेष values according
	 * table 3-13 in Reference Manual Rev.3 05/2010:
	 *
	 * ग_लिखो 0b01 to UCC2 option 2 bits 16:17
	 * ग_लिखो 0b0101 to UCC1 bits 20:23
	 * ग_लिखो 0b0101 to UCC2 option 1 bits 24:27
	 */
	clrsetbits_be32((base + 0xac), 0x0000cff0, 0x00004550);

	अगर (SVR_REV(svid) == 0x0021) अणु
		/*
		 * UCC2 option 1: ग_लिखो 0b1010 to bits 24:27
		 * at address IMMRBAR+0x14AC
		 */
		clrsetbits_be32((base + 0xac), 0x000000f0, 0x000000a0);
	पूर्ण अन्यथा अगर (SVR_REV(svid) == 0x0020) अणु
		/*
		 * UCC1: ग_लिखो 0b11 to bits 18:19
		 * at address IMMRBAR+0x14A8
		 */
		setbits32((base + 0xa8), 0x00003000);

		/*
		 * UCC2 option 1: ग_लिखो 0b11 to bits 4:5
		 * at address IMMRBAR+0x14A8
		 */
		setbits32((base + 0xa8), 0x0c000000);

		/*
		 * UCC2 option 2: ग_लिखो 0b11 to bits 16:17
		 * at address IMMRBAR+0x14AC
		 */
		setbits32((base + 0xac), 0x0000c000);
	पूर्ण
	iounmap(base);
out:
	of_node_put(np_par);
पूर्ण

/* ************************************************************************
 *
 * Setup the architecture
 *
 */
अटल व्योम __init mpc83xx_km_setup_arch(व्योम)
अणु
#अगर_घोषित CONFIG_QUICC_ENGINE
	काष्ठा device_node *np;
#पूर्ण_अगर

	mpc83xx_setup_arch();

#अगर_घोषित CONFIG_QUICC_ENGINE
	np = of_find_node_by_name(शून्य, "par_io");
	अगर (np != शून्य) अणु
		par_io_init(np);
		of_node_put(np);

		क्रम_each_node_by_name(np, "spi")
			par_io_of_config(np);

		क्रम_each_node_by_name(np, "ucc")
			par_io_of_config(np);

		/* Only apply this quirk when par_io is available */
		np = of_find_compatible_node(शून्य, "network", "ucc_geth");
		अगर (np != शून्य) अणु
			quirk_mpc8360e_qe_enet10();
			of_node_put(np);
		पूर्ण
	पूर्ण
#पूर्ण_अगर	/* CONFIG_QUICC_ENGINE */
पूर्ण

machine_device_initcall(mpc83xx_km, mpc83xx_declare_of_platक्रमm_devices);

/* list of the supported boards */
अटल अक्षर *board[] __initdata = अणु
	"Keymile,KMETER1",
	"Keymile,kmpbec8321",
	शून्य
पूर्ण;

/*
 * Called very early, MMU is off, device-tree isn't unflattened
 */
अटल पूर्णांक __init mpc83xx_km_probe(व्योम)
अणु
	पूर्णांक i = 0;

	जबतक (board[i]) अणु
		अगर (of_machine_is_compatible(board[i]))
			अवरोध;
		i++;
	पूर्ण
	वापस (board[i] != शून्य);
पूर्ण

define_machine(mpc83xx_km) अणु
	.name		= "mpc83xx-km-platform",
	.probe		= mpc83xx_km_probe,
	.setup_arch	= mpc83xx_km_setup_arch,
	.discover_phbs	= mpc83xx_setup_pci,
	.init_IRQ	= mpc83xx_ipic_init_IRQ,
	.get_irq	= ipic_get_irq,
	.restart	= mpc83xx_restart,
	.समय_init	= mpc83xx_समय_init,
	.calibrate_decr	= generic_calibrate_decr,
	.progress	= udbg_progress,
पूर्ण;
