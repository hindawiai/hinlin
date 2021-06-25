<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Marvell PTP driver
 *
 * Copyright (C) 2020 Marvell International Ltd.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश "ptp.h"
#समावेश "mbox.h"
#समावेश "rvu.h"

#घोषणा DRV_NAME				"Marvell PTP Driver"

#घोषणा PCI_DEVID_OCTEONTX2_PTP			0xA00C
#घोषणा PCI_SUBSYS_DEVID_OCTX2_98xx_PTP		0xB100
#घोषणा PCI_SUBSYS_DEVID_OCTX2_96XX_PTP		0xB200
#घोषणा PCI_SUBSYS_DEVID_OCTX2_95XX_PTP		0xB300
#घोषणा PCI_SUBSYS_DEVID_OCTX2_LOKI_PTP		0xB400
#घोषणा PCI_SUBSYS_DEVID_OCTX2_95MM_PTP		0xB500
#घोषणा PCI_SUBSYS_DEVID_CN10K_A_PTP		0xB900
#घोषणा PCI_SUBSYS_DEVID_CNF10K_A_PTP		0xBA00
#घोषणा PCI_SUBSYS_DEVID_CNF10K_B_PTP		0xBC00
#घोषणा PCI_DEVID_OCTEONTX2_RST			0xA085

#घोषणा PCI_PTP_BAR_NO				0
#घोषणा PCI_RST_BAR_NO				0

#घोषणा PTP_CLOCK_CFG				0xF00ULL
#घोषणा PTP_CLOCK_CFG_PTP_EN			BIT_ULL(0)
#घोषणा PTP_CLOCK_LO				0xF08ULL
#घोषणा PTP_CLOCK_HI				0xF10ULL
#घोषणा PTP_CLOCK_COMP				0xF18ULL

#घोषणा RST_BOOT				0x1600ULL
#घोषणा RST_MUL_BITS				GENMASK_ULL(38, 33)
#घोषणा CLOCK_BASE_RATE				50000000ULL

अटल u64 get_घड़ी_rate(व्योम)
अणु
	u64 cfg, ret = CLOCK_BASE_RATE * 16;
	काष्ठा pci_dev *pdev;
	व्योम __iomem *base;

	/* To get the input घड़ी frequency with which PTP co-processor
	 * block is running the base frequency(50 MHz) needs to be multiplied
	 * with multiplier bits present in RST_BOOT रेजिस्टर of RESET block.
	 * Hence below code माला_लो the multiplier bits from the RESET PCI
	 * device present in the प्रणाली.
	 */
	pdev = pci_get_device(PCI_VENDOR_ID_CAVIUM,
			      PCI_DEVID_OCTEONTX2_RST, शून्य);
	अगर (!pdev)
		जाओ error;

	base = pci_ioremap_bar(pdev, PCI_RST_BAR_NO);
	अगर (!base)
		जाओ error_put_pdev;

	cfg = पढ़ोq(base + RST_BOOT);
	ret = CLOCK_BASE_RATE * FIELD_GET(RST_MUL_BITS, cfg);

	iounmap(base);

error_put_pdev:
	pci_dev_put(pdev);

error:
	वापस ret;
पूर्ण

काष्ठा ptp *ptp_get(व्योम)
अणु
	काष्ठा pci_dev *pdev;
	काष्ठा ptp *ptp;

	/* If the PTP pci device is found on the प्रणाली and ptp
	 * driver is bound to it then the PTP pci device is वापसed
	 * to the caller(rvu driver).
	 */
	pdev = pci_get_device(PCI_VENDOR_ID_CAVIUM,
			      PCI_DEVID_OCTEONTX2_PTP, शून्य);
	अगर (!pdev)
		वापस ERR_PTR(-ENODEV);

	ptp = pci_get_drvdata(pdev);
	अगर (!ptp)
		ptp = ERR_PTR(-EPROBE_DEFER);
	अगर (IS_ERR(ptp))
		pci_dev_put(pdev);

	वापस ptp;
पूर्ण

व्योम ptp_put(काष्ठा ptp *ptp)
अणु
	अगर (!ptp)
		वापस;

	pci_dev_put(ptp->pdev);
पूर्ण

अटल पूर्णांक ptp_adjfine(काष्ठा ptp *ptp, दीर्घ scaled_ppm)
अणु
	bool neg_adj = false;
	u64 comp;
	u64 adj;
	s64 ppb;

	अगर (scaled_ppm < 0) अणु
		neg_adj = true;
		scaled_ppm = -scaled_ppm;
	पूर्ण

	/* The hardware adds the घड़ी compensation value to the PTP घड़ी
	 * on every coprocessor घड़ी cycle. Typical convention is that it
	 * represent number of nanosecond betwen each cycle. In this
	 * convention compensation value is in 64 bit fixed-poपूर्णांक
	 * representation where upper 32 bits are number of nanoseconds
	 * and lower is fractions of nanosecond.
	 * The scaled_ppm represent the ratio in "parts per million" by which
	 * the compensation value should be corrected.
	 * To calculate new compenstation value we use 64bit fixed poपूर्णांक
	 * arithmetic on following क्रमmula
	 * comp = tbase + tbase * scaled_ppm / (1M * 2^16)
	 * where tbase is the basic compensation value calculated
	 * initialy in the probe function.
	 */
	comp = ((u64)1000000000ull << 32) / ptp->घड़ी_rate;
	/* convert scaled_ppm to ppb */
	ppb = 1 + scaled_ppm;
	ppb *= 125;
	ppb >>= 13;
	adj = comp * ppb;
	adj = भाग_u64(adj, 1000000000ull);
	comp = neg_adj ? comp - adj : comp + adj;

	ग_लिखोq(comp, ptp->reg_base + PTP_CLOCK_COMP);

	वापस 0;
पूर्ण

अटल पूर्णांक ptp_get_घड़ी(काष्ठा ptp *ptp, u64 *clk)
अणु
	/* Return the current PTP घड़ी */
	*clk = पढ़ोq(ptp->reg_base + PTP_CLOCK_HI);

	वापस 0;
पूर्ण

अटल पूर्णांक ptp_probe(काष्ठा pci_dev *pdev,
		     स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ptp *ptp;
	u64 घड़ी_comp;
	u64 घड़ी_cfg;
	पूर्णांक err;

	ptp = devm_kzalloc(dev, माप(*ptp), GFP_KERNEL);
	अगर (!ptp) अणु
		err = -ENOMEM;
		जाओ error;
	पूर्ण

	ptp->pdev = pdev;

	err = pcim_enable_device(pdev);
	अगर (err)
		जाओ error_मुक्त;

	err = pcim_iomap_regions(pdev, 1 << PCI_PTP_BAR_NO, pci_name(pdev));
	अगर (err)
		जाओ error_मुक्त;

	ptp->reg_base = pcim_iomap_table(pdev)[PCI_PTP_BAR_NO];

	ptp->घड़ी_rate = get_घड़ी_rate();

	/* Enable PTP घड़ी */
	घड़ी_cfg = पढ़ोq(ptp->reg_base + PTP_CLOCK_CFG);
	घड़ी_cfg |= PTP_CLOCK_CFG_PTP_EN;
	ग_लिखोq(घड़ी_cfg, ptp->reg_base + PTP_CLOCK_CFG);

	घड़ी_comp = ((u64)1000000000ull << 32) / ptp->घड़ी_rate;
	/* Initial compensation value to start the nanosecs counter */
	ग_लिखोq(घड़ी_comp, ptp->reg_base + PTP_CLOCK_COMP);

	pci_set_drvdata(pdev, ptp);

	वापस 0;

error_मुक्त:
	devm_kमुक्त(dev, ptp);

error:
	/* For `ptp_get()` we need to dअगरferentiate between the हाल
	 * when the core has not tried to probe this device and the हाल when
	 * the probe failed.  In the later हाल we pretend that the
	 * initialization was successful and keep the error in
	 * `dev->driver_data`.
	 */
	pci_set_drvdata(pdev, ERR_PTR(err));
	वापस 0;
पूर्ण

अटल व्योम ptp_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ptp *ptp = pci_get_drvdata(pdev);
	u64 घड़ी_cfg;

	अगर (IS_ERR_OR_शून्य(ptp))
		वापस;

	/* Disable PTP घड़ी */
	घड़ी_cfg = पढ़ोq(ptp->reg_base + PTP_CLOCK_CFG);
	घड़ी_cfg &= ~PTP_CLOCK_CFG_PTP_EN;
	ग_लिखोq(घड़ी_cfg, ptp->reg_base + PTP_CLOCK_CFG);
पूर्ण

अटल स्थिर काष्ठा pci_device_id ptp_id_table[] = अणु
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_CAVIUM, PCI_DEVID_OCTEONTX2_PTP,
			 PCI_VENDOR_ID_CAVIUM,
			 PCI_SUBSYS_DEVID_OCTX2_98xx_PTP) पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_CAVIUM, PCI_DEVID_OCTEONTX2_PTP,
			 PCI_VENDOR_ID_CAVIUM,
			 PCI_SUBSYS_DEVID_OCTX2_96XX_PTP) पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_CAVIUM, PCI_DEVID_OCTEONTX2_PTP,
			 PCI_VENDOR_ID_CAVIUM,
			 PCI_SUBSYS_DEVID_OCTX2_95XX_PTP) पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_CAVIUM, PCI_DEVID_OCTEONTX2_PTP,
			 PCI_VENDOR_ID_CAVIUM,
			 PCI_SUBSYS_DEVID_OCTX2_LOKI_PTP) पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_CAVIUM, PCI_DEVID_OCTEONTX2_PTP,
			 PCI_VENDOR_ID_CAVIUM,
			 PCI_SUBSYS_DEVID_OCTX2_95MM_PTP) पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_CAVIUM, PCI_DEVID_OCTEONTX2_PTP,
			 PCI_VENDOR_ID_CAVIUM,
			 PCI_SUBSYS_DEVID_CN10K_A_PTP) पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_CAVIUM, PCI_DEVID_OCTEONTX2_PTP,
			 PCI_VENDOR_ID_CAVIUM,
			 PCI_SUBSYS_DEVID_CNF10K_A_PTP) पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_CAVIUM, PCI_DEVID_OCTEONTX2_PTP,
			 PCI_VENDOR_ID_CAVIUM,
			 PCI_SUBSYS_DEVID_CNF10K_B_PTP) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

काष्ठा pci_driver ptp_driver = अणु
	.name = DRV_NAME,
	.id_table = ptp_id_table,
	.probe = ptp_probe,
	.हटाओ = ptp_हटाओ,
पूर्ण;

पूर्णांक rvu_mbox_handler_ptp_op(काष्ठा rvu *rvu, काष्ठा ptp_req *req,
			    काष्ठा ptp_rsp *rsp)
अणु
	पूर्णांक err = 0;

	/* This function is the PTP mailbox handler invoked when
	 * called by AF consumers/netdev drivers via mailbox mechanism.
	 * It is used by netdev driver to get the PTP घड़ी and to set
	 * frequency adjusपंचांगents. Since mailbox can be called without
	 * notion of whether the driver is bound to ptp device below
	 * validation is needed as first step.
	 */
	अगर (!rvu->ptp)
		वापस -ENODEV;

	चयन (req->op) अणु
	हाल PTP_OP_ADJFINE:
		err = ptp_adjfine(rvu->ptp, req->scaled_ppm);
		अवरोध;
	हाल PTP_OP_GET_CLOCK:
		err = ptp_get_घड़ी(rvu->ptp, &rsp->clk);
		अवरोध;
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण
