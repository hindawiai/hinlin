<शैली गुरु>
/*
 * Freescale Memory Controller kernel module
 *
 * Author: York Sun <york.sun@nxp.com>
 *
 * Copyright 2016 NXP Semiconductor
 *
 * Derived from mpc85xx_edac.c
 * Author: Dave Jiang <djiang@mvista.com>
 *
 * 2006-2007 (c) MontaVista Software, Inc. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "edac_module.h"
#समावेश "fsl_ddr_edac.h"

अटल स्थिर काष्ठा of_device_id fsl_ddr_mc_err_of_match[] = अणु
	अणु .compatible = "fsl,qoriq-memory-controller", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, fsl_ddr_mc_err_of_match);

अटल काष्ठा platक्रमm_driver fsl_ddr_mc_err_driver = अणु
	.probe = fsl_mc_err_probe,
	.हटाओ = fsl_mc_err_हटाओ,
	.driver = अणु
		.name = "fsl_ddr_mc_err",
		.of_match_table = fsl_ddr_mc_err_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init fsl_ddr_mc_init(व्योम)
अणु
	पूर्णांक res;

	/* make sure error reporting method is sane */
	चयन (edac_op_state) अणु
	हाल EDAC_OPSTATE_POLL:
	हाल EDAC_OPSTATE_INT:
		अवरोध;
	शेष:
		edac_op_state = EDAC_OPSTATE_INT;
		अवरोध;
	पूर्ण

	res = platक्रमm_driver_रेजिस्टर(&fsl_ddr_mc_err_driver);
	अगर (res) अणु
		pr_err("MC fails to register\n");
		वापस res;
	पूर्ण

	वापस 0;
पूर्ण

module_init(fsl_ddr_mc_init);

अटल व्योम __निकास fsl_ddr_mc_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&fsl_ddr_mc_err_driver);
पूर्ण

module_निकास(fsl_ddr_mc_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("NXP Semiconductor");
module_param(edac_op_state, पूर्णांक, 0444);
MODULE_PARM_DESC(edac_op_state,
		 "EDAC Error Reporting state: 0=Poll, 2=Interrupt");
