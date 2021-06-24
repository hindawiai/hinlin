<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2012 Cavium, Inc.
 * Copyright (C) 2009 Wind River Systems,
 *   written by Ralf Baechle <ralf@linux-mips.org>
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/edac.h>

#समावेश <यंत्र/octeon/cvmx.h>
#समावेश <यंत्र/octeon/cvmx-npi-defs.h>
#समावेश <यंत्र/octeon/cvmx-pci-defs.h>
#समावेश <यंत्र/octeon/octeon.h>

#समावेश "edac_module.h"

अटल व्योम octeon_pci_poll(काष्ठा edac_pci_ctl_info *pci)
अणु
	जोड़ cvmx_pci_cfg01 cfg01;

	cfg01.u32 = octeon_npi_पढ़ो32(CVMX_NPI_PCI_CFG01);
	अगर (cfg01.s.dpe) अणु		/* Detected parity error */
		edac_pci_handle_pe(pci, pci->ctl_name);
		cfg01.s.dpe = 1;		/* Reset  */
		octeon_npi_ग_लिखो32(CVMX_NPI_PCI_CFG01, cfg01.u32);
	पूर्ण
	अगर (cfg01.s.sse) अणु
		edac_pci_handle_npe(pci, "Signaled System Error");
		cfg01.s.sse = 1;		/* Reset */
		octeon_npi_ग_लिखो32(CVMX_NPI_PCI_CFG01, cfg01.u32);
	पूर्ण
	अगर (cfg01.s.rma) अणु
		edac_pci_handle_npe(pci, "Received Master Abort");
		cfg01.s.rma = 1;		/* Reset */
		octeon_npi_ग_लिखो32(CVMX_NPI_PCI_CFG01, cfg01.u32);
	पूर्ण
	अगर (cfg01.s.rta) अणु
		edac_pci_handle_npe(pci, "Received Target Abort");
		cfg01.s.rta = 1;		/* Reset */
		octeon_npi_ग_लिखो32(CVMX_NPI_PCI_CFG01, cfg01.u32);
	पूर्ण
	अगर (cfg01.s.sta) अणु
		edac_pci_handle_npe(pci, "Signaled Target Abort");
		cfg01.s.sta = 1;		/* Reset */
		octeon_npi_ग_लिखो32(CVMX_NPI_PCI_CFG01, cfg01.u32);
	पूर्ण
	अगर (cfg01.s.mdpe) अणु
		edac_pci_handle_npe(pci, "Master Data Parity Error");
		cfg01.s.mdpe = 1;		/* Reset */
		octeon_npi_ग_लिखो32(CVMX_NPI_PCI_CFG01, cfg01.u32);
	पूर्ण
पूर्ण

अटल पूर्णांक octeon_pci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा edac_pci_ctl_info *pci;
	पूर्णांक res = 0;

	pci = edac_pci_alloc_ctl_info(0, "octeon_pci_err");
	अगर (!pci)
		वापस -ENOMEM;

	pci->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, pci);
	pci->dev_name = dev_name(&pdev->dev);

	pci->mod_name = "octeon-pci";
	pci->ctl_name = "octeon_pci_err";
	pci->edac_check = octeon_pci_poll;

	अगर (edac_pci_add_device(pci, 0) > 0) अणु
		pr_err("%s: edac_pci_add_device() failed\n", __func__);
		जाओ err;
	पूर्ण

	वापस 0;

err:
	edac_pci_मुक्त_ctl_info(pci);

	वापस res;
पूर्ण

अटल पूर्णांक octeon_pci_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा edac_pci_ctl_info *pci = platक्रमm_get_drvdata(pdev);

	edac_pci_del_device(&pdev->dev);
	edac_pci_मुक्त_ctl_info(pci);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver octeon_pci_driver = अणु
	.probe = octeon_pci_probe,
	.हटाओ = octeon_pci_हटाओ,
	.driver = अणु
		   .name = "octeon_pci_edac",
	पूर्ण
पूर्ण;
module_platक्रमm_driver(octeon_pci_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ralf Baechle <ralf@linux-mips.org>");
