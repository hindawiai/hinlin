<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* cavium_ptp.c - PTP 1588 घड़ी on Cavium hardware
 * Copyright (c) 2003-2015, 2017 Cavium, Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/समयcounter.h>
#समावेश <linux/pci.h>

#समावेश "cavium_ptp.h"

#घोषणा DRV_NAME "cavium_ptp"

#घोषणा PCI_DEVICE_ID_CAVIUM_PTP	0xA00C
#घोषणा PCI_SUBSYS_DEVID_88XX_PTP	0xA10C
#घोषणा PCI_SUBSYS_DEVID_81XX_PTP	0XA20C
#घोषणा PCI_SUBSYS_DEVID_83XX_PTP	0xA30C
#घोषणा PCI_DEVICE_ID_CAVIUM_RST	0xA00E

#घोषणा PCI_PTP_BAR_NO	0
#घोषणा PCI_RST_BAR_NO	0

#घोषणा PTP_CLOCK_CFG		0xF00ULL
#घोषणा  PTP_CLOCK_CFG_PTP_EN	BIT(0)
#घोषणा PTP_CLOCK_LO		0xF08ULL
#घोषणा PTP_CLOCK_HI		0xF10ULL
#घोषणा PTP_CLOCK_COMP		0xF18ULL

#घोषणा RST_BOOT	0x1600ULL
#घोषणा CLOCK_BASE_RATE	50000000ULL

अटल u64 ptp_cavium_घड़ी_get(व्योम)
अणु
	काष्ठा pci_dev *pdev;
	व्योम __iomem *base;
	u64 ret = CLOCK_BASE_RATE * 16;

	pdev = pci_get_device(PCI_VENDOR_ID_CAVIUM,
			      PCI_DEVICE_ID_CAVIUM_RST, शून्य);
	अगर (!pdev)
		जाओ error;

	base = pci_ioremap_bar(pdev, PCI_RST_BAR_NO);
	अगर (!base)
		जाओ error_put_pdev;

	ret = CLOCK_BASE_RATE * ((पढ़ोq(base + RST_BOOT) >> 33) & 0x3f);

	iounmap(base);

error_put_pdev:
	pci_dev_put(pdev);

error:
	वापस ret;
पूर्ण

काष्ठा cavium_ptp *cavium_ptp_get(व्योम)
अणु
	काष्ठा cavium_ptp *ptp;
	काष्ठा pci_dev *pdev;

	pdev = pci_get_device(PCI_VENDOR_ID_CAVIUM,
			      PCI_DEVICE_ID_CAVIUM_PTP, शून्य);
	अगर (!pdev)
		वापस ERR_PTR(-ENODEV);

	ptp = pci_get_drvdata(pdev);
	अगर (!ptp)
		ptp = ERR_PTR(-EPROBE_DEFER);
	अगर (IS_ERR(ptp))
		pci_dev_put(pdev);

	वापस ptp;
पूर्ण
EXPORT_SYMBOL(cavium_ptp_get);

व्योम cavium_ptp_put(काष्ठा cavium_ptp *ptp)
अणु
	अगर (!ptp)
		वापस;
	pci_dev_put(ptp->pdev);
पूर्ण
EXPORT_SYMBOL(cavium_ptp_put);

/**
 * cavium_ptp_adjfine() - Adjust ptp frequency
 * @ptp_info: PTP घड़ी info
 * @scaled_ppm: how much to adjust by, in parts per million, but with a
 *              16 bit binary fractional field
 */
अटल पूर्णांक cavium_ptp_adjfine(काष्ठा ptp_घड़ी_info *ptp_info, दीर्घ scaled_ppm)
अणु
	काष्ठा cavium_ptp *घड़ी =
		container_of(ptp_info, काष्ठा cavium_ptp, ptp_info);
	अचिन्हित दीर्घ flags;
	u64 comp;
	u64 adj;
	bool neg_adj = false;

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
	 * The scaled_ppm represent the ratio in "parts per bilion" by which the
	 * compensation value should be corrected.
	 * To calculate new compenstation value we use 64bit fixed poपूर्णांक
	 * arithmetic on following क्रमmula
	 * comp = tbase + tbase * scaled_ppm / (1M * 2^16)
	 * where tbase is the basic compensation value calculated initialy
	 * in cavium_ptp_init() -> tbase = 1/Hz. Then we use endian
	 * independent काष्ठाure definition to ग_लिखो data to PTP रेजिस्टर.
	 */
	comp = ((u64)1000000000ull << 32) / घड़ी->घड़ी_rate;
	adj = comp * scaled_ppm;
	adj >>= 16;
	adj = भाग_u64(adj, 1000000ull);
	comp = neg_adj ? comp - adj : comp + adj;

	spin_lock_irqsave(&घड़ी->spin_lock, flags);
	ग_लिखोq(comp, घड़ी->reg_base + PTP_CLOCK_COMP);
	spin_unlock_irqrestore(&घड़ी->spin_lock, flags);

	वापस 0;
पूर्ण

/**
 * cavium_ptp_adjसमय() - Adjust ptp समय
 * @ptp_info:   PTP घड़ी info
 * @delta: how much to adjust by, in nanosecs
 */
अटल पूर्णांक cavium_ptp_adjसमय(काष्ठा ptp_घड़ी_info *ptp_info, s64 delta)
अणु
	काष्ठा cavium_ptp *घड़ी =
		container_of(ptp_info, काष्ठा cavium_ptp, ptp_info);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&घड़ी->spin_lock, flags);
	समयcounter_adjसमय(&घड़ी->समय_counter, delta);
	spin_unlock_irqrestore(&घड़ी->spin_lock, flags);

	/* Sync, क्रम network driver to get latest value */
	smp_mb();

	वापस 0;
पूर्ण

/**
 * cavium_ptp_समय_लो() - Get hardware घड़ी समय with adjusपंचांगent
 * @ptp_info: PTP घड़ी info
 * @ts:  बारpec
 */
अटल पूर्णांक cavium_ptp_समय_लो(काष्ठा ptp_घड़ी_info *ptp_info,
			      काष्ठा बारpec64 *ts)
अणु
	काष्ठा cavium_ptp *घड़ी =
		container_of(ptp_info, काष्ठा cavium_ptp, ptp_info);
	अचिन्हित दीर्घ flags;
	u64 nsec;

	spin_lock_irqsave(&घड़ी->spin_lock, flags);
	nsec = समयcounter_पढ़ो(&घड़ी->समय_counter);
	spin_unlock_irqrestore(&घड़ी->spin_lock, flags);

	*ts = ns_to_बारpec64(nsec);

	वापस 0;
पूर्ण

/**
 * cavium_ptp_समय_रखो() - Set hardware घड़ी समय. Reset adjusपंचांगent
 * @ptp_info: PTP घड़ी info
 * @ts:  बारpec
 */
अटल पूर्णांक cavium_ptp_समय_रखो(काष्ठा ptp_घड़ी_info *ptp_info,
			      स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा cavium_ptp *घड़ी =
		container_of(ptp_info, काष्ठा cavium_ptp, ptp_info);
	अचिन्हित दीर्घ flags;
	u64 nsec;

	nsec = बारpec64_to_ns(ts);

	spin_lock_irqsave(&घड़ी->spin_lock, flags);
	समयcounter_init(&घड़ी->समय_counter, &घड़ी->cycle_counter, nsec);
	spin_unlock_irqrestore(&घड़ी->spin_lock, flags);

	वापस 0;
पूर्ण

/**
 * cavium_ptp_enable() - Request to enable or disable an ancillary feature.
 * @ptp_info: PTP घड़ी info
 * @rq:  request
 * @on:  is it on
 */
अटल पूर्णांक cavium_ptp_enable(काष्ठा ptp_घड़ी_info *ptp_info,
			     काष्ठा ptp_घड़ी_request *rq, पूर्णांक on)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल u64 cavium_ptp_cc_पढ़ो(स्थिर काष्ठा cyclecounter *cc)
अणु
	काष्ठा cavium_ptp *घड़ी =
		container_of(cc, काष्ठा cavium_ptp, cycle_counter);

	वापस पढ़ोq(घड़ी->reg_base + PTP_CLOCK_HI);
पूर्ण

अटल पूर्णांक cavium_ptp_probe(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा cavium_ptp *घड़ी;
	काष्ठा cyclecounter *cc;
	u64 घड़ी_cfg;
	u64 घड़ी_comp;
	पूर्णांक err;

	घड़ी = devm_kzalloc(dev, माप(*घड़ी), GFP_KERNEL);
	अगर (!घड़ी) अणु
		err = -ENOMEM;
		जाओ error;
	पूर्ण

	घड़ी->pdev = pdev;

	err = pcim_enable_device(pdev);
	अगर (err)
		जाओ error_मुक्त;

	err = pcim_iomap_regions(pdev, 1 << PCI_PTP_BAR_NO, pci_name(pdev));
	अगर (err)
		जाओ error_मुक्त;

	घड़ी->reg_base = pcim_iomap_table(pdev)[PCI_PTP_BAR_NO];

	spin_lock_init(&घड़ी->spin_lock);

	cc = &घड़ी->cycle_counter;
	cc->पढ़ो = cavium_ptp_cc_पढ़ो;
	cc->mask = CYCLECOUNTER_MASK(64);
	cc->mult = 1;
	cc->shअगरt = 0;

	समयcounter_init(&घड़ी->समय_counter, &घड़ी->cycle_counter,
			 kसमय_प्रकारo_ns(kसमय_get_real()));

	घड़ी->घड़ी_rate = ptp_cavium_घड़ी_get();

	घड़ी->ptp_info = (काष्ठा ptp_घड़ी_info) अणु
		.owner		= THIS_MODULE,
		.name		= "ThunderX PTP",
		.max_adj	= 1000000000ull,
		.n_ext_ts	= 0,
		.n_pins		= 0,
		.pps		= 0,
		.adjfine	= cavium_ptp_adjfine,
		.adjसमय	= cavium_ptp_adjसमय,
		.समय_लो64	= cavium_ptp_समय_लो,
		.समय_रखो64	= cavium_ptp_समय_रखो,
		.enable		= cavium_ptp_enable,
	पूर्ण;

	घड़ी_cfg = पढ़ोq(घड़ी->reg_base + PTP_CLOCK_CFG);
	घड़ी_cfg |= PTP_CLOCK_CFG_PTP_EN;
	ग_लिखोq(घड़ी_cfg, घड़ी->reg_base + PTP_CLOCK_CFG);

	घड़ी_comp = ((u64)1000000000ull << 32) / घड़ी->घड़ी_rate;
	ग_लिखोq(घड़ी_comp, घड़ी->reg_base + PTP_CLOCK_COMP);

	घड़ी->ptp_घड़ी = ptp_घड़ी_रेजिस्टर(&घड़ी->ptp_info, dev);
	अगर (IS_ERR(घड़ी->ptp_घड़ी)) अणु
		err = PTR_ERR(घड़ी->ptp_घड़ी);
		जाओ error_stop;
	पूर्ण

	pci_set_drvdata(pdev, घड़ी);
	वापस 0;

error_stop:
	घड़ी_cfg = पढ़ोq(घड़ी->reg_base + PTP_CLOCK_CFG);
	घड़ी_cfg &= ~PTP_CLOCK_CFG_PTP_EN;
	ग_लिखोq(घड़ी_cfg, घड़ी->reg_base + PTP_CLOCK_CFG);
	pcim_iounmap_regions(pdev, 1 << PCI_PTP_BAR_NO);

error_मुक्त:
	devm_kमुक्त(dev, घड़ी);

error:
	/* For `cavium_ptp_get()` we need to dअगरferentiate between the हाल
	 * when the core has not tried to probe this device and the हाल when
	 * the probe failed.  In the later हाल we pretend that the
	 * initialization was successful and keep the error in
	 * `dev->driver_data`.
	 */
	pci_set_drvdata(pdev, ERR_PTR(err));
	वापस 0;
पूर्ण

अटल व्योम cavium_ptp_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा cavium_ptp *घड़ी = pci_get_drvdata(pdev);
	u64 घड़ी_cfg;

	अगर (IS_ERR_OR_शून्य(घड़ी))
		वापस;

	ptp_घड़ी_unरेजिस्टर(घड़ी->ptp_घड़ी);

	घड़ी_cfg = पढ़ोq(घड़ी->reg_base + PTP_CLOCK_CFG);
	घड़ी_cfg &= ~PTP_CLOCK_CFG_PTP_EN;
	ग_लिखोq(घड़ी_cfg, घड़ी->reg_base + PTP_CLOCK_CFG);
पूर्ण

अटल स्थिर काष्ठा pci_device_id cavium_ptp_id_table[] = अणु
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_CAVIUM, PCI_DEVICE_ID_CAVIUM_PTP,
			PCI_VENDOR_ID_CAVIUM, PCI_SUBSYS_DEVID_88XX_PTP) पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_CAVIUM, PCI_DEVICE_ID_CAVIUM_PTP,
			PCI_VENDOR_ID_CAVIUM, PCI_SUBSYS_DEVID_81XX_PTP) पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_CAVIUM, PCI_DEVICE_ID_CAVIUM_PTP,
			PCI_VENDOR_ID_CAVIUM, PCI_SUBSYS_DEVID_83XX_PTP) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

अटल काष्ठा pci_driver cavium_ptp_driver = अणु
	.name = DRV_NAME,
	.id_table = cavium_ptp_id_table,
	.probe = cavium_ptp_probe,
	.हटाओ = cavium_ptp_हटाओ,
पूर्ण;

module_pci_driver(cavium_ptp_driver);

MODULE_DESCRIPTION(DRV_NAME);
MODULE_AUTHOR("Cavium Networks <support@cavium.com>");
MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(pci, cavium_ptp_id_table);
