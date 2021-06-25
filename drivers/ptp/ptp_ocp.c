<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2020 Facebook */

#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/ptp_घड़ी_kernel.h>

अटल स्थिर काष्ठा pci_device_id ptp_ocp_pcidev_id[] = अणु
	अणु PCI_DEVICE(0x1d9b, 0x0400) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, ptp_ocp_pcidev_id);

#घोषणा OCP_REGISTER_OFFSET	0x01000000

काष्ठा ocp_reg अणु
	u32	ctrl;
	u32	status;
	u32	select;
	u32	version;
	u32	समय_ns;
	u32	समय_sec;
	u32	__pad0[2];
	u32	adjust_ns;
	u32	adjust_sec;
	u32	__pad1[2];
	u32	offset_ns;
	u32	offset_winकरोw_ns;
पूर्ण;

#घोषणा OCP_CTRL_ENABLE		BIT(0)
#घोषणा OCP_CTRL_ADJUST_TIME	BIT(1)
#घोषणा OCP_CTRL_ADJUST_OFFSET	BIT(2)
#घोषणा OCP_CTRL_READ_TIME_REQ	BIT(30)
#घोषणा OCP_CTRL_READ_TIME_DONE	BIT(31)

#घोषणा OCP_STATUS_IN_SYNC	BIT(0)

#घोषणा OCP_SELECT_CLK_NONE	0
#घोषणा OCP_SELECT_CLK_REG	6

काष्ठा tod_reg अणु
	u32	ctrl;
	u32	status;
	u32	uart_polarity;
	u32	version;
	u32	correction_sec;
	u32	__pad0[3];
	u32	uart_baud;
	u32	__pad1[3];
	u32	utc_status;
	u32	leap;
पूर्ण;

#घोषणा TOD_REGISTER_OFFSET	0x01050000

#घोषणा TOD_CTRL_PROTOCOL	BIT(28)
#घोषणा TOD_CTRL_DISABLE_FMT_A	BIT(17)
#घोषणा TOD_CTRL_DISABLE_FMT_B	BIT(16)
#घोषणा TOD_CTRL_ENABLE		BIT(0)
#घोषणा TOD_CTRL_GNSS_MASK	((1U << 4) - 1)
#घोषणा TOD_CTRL_GNSS_SHIFT	24

#घोषणा TOD_STATUS_UTC_MASK	0xff
#घोषणा TOD_STATUS_UTC_VALID	BIT(8)
#घोषणा TOD_STATUS_LEAP_VALID	BIT(16)

काष्ठा ptp_ocp अणु
	काष्ठा pci_dev		*pdev;
	spinlock_t		lock;
	व्योम __iomem		*base;
	काष्ठा ocp_reg __iomem	*reg;
	काष्ठा tod_reg __iomem	*tod;
	काष्ठा ptp_घड़ी	*ptp;
	काष्ठा ptp_घड़ी_info	ptp_info;
पूर्ण;

अटल पूर्णांक
__ptp_ocp_समय_लो_locked(काष्ठा ptp_ocp *bp, काष्ठा बारpec64 *ts,
			 काष्ठा ptp_प्रणाली_बारtamp *sts)
अणु
	u32 ctrl, समय_sec, समय_ns;
	पूर्णांक i;

	ctrl = ioपढ़ो32(&bp->reg->ctrl);
	ctrl |= OCP_CTRL_READ_TIME_REQ;

	ptp_पढ़ो_प्रणाली_prets(sts);
	ioग_लिखो32(ctrl, &bp->reg->ctrl);

	क्रम (i = 0; i < 100; i++) अणु
		ctrl = ioपढ़ो32(&bp->reg->ctrl);
		अगर (ctrl & OCP_CTRL_READ_TIME_DONE)
			अवरोध;
	पूर्ण
	ptp_पढ़ो_प्रणाली_postts(sts);

	समय_ns = ioपढ़ो32(&bp->reg->समय_ns);
	समय_sec = ioपढ़ो32(&bp->reg->समय_sec);

	ts->tv_sec = समय_sec;
	ts->tv_nsec = समय_ns;

	वापस ctrl & OCP_CTRL_READ_TIME_DONE ? 0 : -ETIMEDOUT;
पूर्ण

अटल पूर्णांक
ptp_ocp_समय_लोx(काष्ठा ptp_घड़ी_info *ptp_info, काष्ठा बारpec64 *ts,
		 काष्ठा ptp_प्रणाली_बारtamp *sts)
अणु
	काष्ठा ptp_ocp *bp = container_of(ptp_info, काष्ठा ptp_ocp, ptp_info);
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	spin_lock_irqsave(&bp->lock, flags);
	err = __ptp_ocp_समय_लो_locked(bp, ts, sts);
	spin_unlock_irqrestore(&bp->lock, flags);

	वापस err;
पूर्ण

अटल व्योम
__ptp_ocp_समय_रखो_locked(काष्ठा ptp_ocp *bp, स्थिर काष्ठा बारpec64 *ts)
अणु
	u32 ctrl, समय_sec, समय_ns;
	u32 select;

	समय_ns = ts->tv_nsec;
	समय_sec = ts->tv_sec;

	select = ioपढ़ो32(&bp->reg->select);
	ioग_लिखो32(OCP_SELECT_CLK_REG, &bp->reg->select);

	ioग_लिखो32(समय_ns, &bp->reg->adjust_ns);
	ioग_लिखो32(समय_sec, &bp->reg->adjust_sec);

	ctrl = ioपढ़ो32(&bp->reg->ctrl);
	ctrl |= OCP_CTRL_ADJUST_TIME;
	ioग_लिखो32(ctrl, &bp->reg->ctrl);

	/* restore घड़ी selection */
	ioग_लिखो32(select >> 16, &bp->reg->select);
पूर्ण

अटल पूर्णांक
ptp_ocp_समय_रखो(काष्ठा ptp_घड़ी_info *ptp_info, स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा ptp_ocp *bp = container_of(ptp_info, काष्ठा ptp_ocp, ptp_info);
	अचिन्हित दीर्घ flags;

	अगर (ioपढ़ो32(&bp->reg->status) & OCP_STATUS_IN_SYNC)
		वापस 0;

	spin_lock_irqsave(&bp->lock, flags);
	__ptp_ocp_समय_रखो_locked(bp, ts);
	spin_unlock_irqrestore(&bp->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
ptp_ocp_adjसमय(काष्ठा ptp_घड़ी_info *ptp_info, s64 delta_ns)
अणु
	काष्ठा ptp_ocp *bp = container_of(ptp_info, काष्ठा ptp_ocp, ptp_info);
	काष्ठा बारpec64 ts;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	अगर (ioपढ़ो32(&bp->reg->status) & OCP_STATUS_IN_SYNC)
		वापस 0;

	spin_lock_irqsave(&bp->lock, flags);
	err = __ptp_ocp_समय_लो_locked(bp, &ts, शून्य);
	अगर (likely(!err)) अणु
		बारpec64_add_ns(&ts, delta_ns);
		__ptp_ocp_समय_रखो_locked(bp, &ts);
	पूर्ण
	spin_unlock_irqrestore(&bp->lock, flags);

	वापस err;
पूर्ण

अटल पूर्णांक
ptp_ocp_null_adjfine(काष्ठा ptp_घड़ी_info *ptp_info, दीर्घ scaled_ppm)
अणु
	अगर (scaled_ppm == 0)
		वापस 0;

	वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर काष्ठा ptp_घड़ी_info ptp_ocp_घड़ी_info = अणु
	.owner		= THIS_MODULE,
	.name		= KBUILD_MODNAME,
	.max_adj	= 100000000,
	.समय_लोx64	= ptp_ocp_समय_लोx,
	.समय_रखो64	= ptp_ocp_समय_रखो,
	.adjसमय	= ptp_ocp_adjसमय,
	.adjfine	= ptp_ocp_null_adjfine,
पूर्ण;

अटल पूर्णांक
ptp_ocp_check_घड़ी(काष्ठा ptp_ocp *bp)
अणु
	काष्ठा बारpec64 ts;
	bool sync;
	u32 ctrl;

	/* make sure घड़ी is enabled */
	ctrl = ioपढ़ो32(&bp->reg->ctrl);
	ctrl |= OCP_CTRL_ENABLE;
	ioग_लिखो32(ctrl, &bp->reg->ctrl);

	अगर ((ioपढ़ो32(&bp->reg->ctrl) & OCP_CTRL_ENABLE) == 0) अणु
		dev_err(&bp->pdev->dev, "clock not enabled\n");
		वापस -ENODEV;
	पूर्ण

	sync = ioपढ़ो32(&bp->reg->status) & OCP_STATUS_IN_SYNC;
	अगर (!sync) अणु
		kसमय_get_real_ts64(&ts);
		ptp_ocp_समय_रखो(&bp->ptp_info, &ts);
	पूर्ण
	अगर (!ptp_ocp_समय_लोx(&bp->ptp_info, &ts, शून्य))
		dev_info(&bp->pdev->dev, "Time: %lld.%ld, %s\n",
			 ts.tv_sec, ts.tv_nsec,
			 sync ? "in-sync" : "UNSYNCED");

	वापस 0;
पूर्ण

अटल व्योम
ptp_ocp_tod_info(काष्ठा ptp_ocp *bp)
अणु
	अटल स्थिर अक्षर * स्थिर proto_name[] = अणु
		"NMEA", "NMEA_ZDA", "NMEA_RMC", "NMEA_none",
		"UBX", "UBX_UTC", "UBX_LS", "UBX_none"
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर gnss_name[] = अणु
		"ALL", "COMBINED", "GPS", "GLONASS", "GALILEO", "BEIDOU",
	पूर्ण;
	u32 version, ctrl, reg;
	पूर्णांक idx;

	version = ioपढ़ो32(&bp->tod->version);
	dev_info(&bp->pdev->dev, "TOD Version %d.%d.%d\n",
		 version >> 24, (version >> 16) & 0xff, version & 0xffff);

	ctrl = ioपढ़ो32(&bp->tod->ctrl);
	ctrl |= TOD_CTRL_PROTOCOL | TOD_CTRL_ENABLE;
	ctrl &= ~(TOD_CTRL_DISABLE_FMT_A | TOD_CTRL_DISABLE_FMT_B);
	ioग_लिखो32(ctrl, &bp->tod->ctrl);

	ctrl = ioपढ़ो32(&bp->tod->ctrl);
	idx = ctrl & TOD_CTRL_PROTOCOL ? 4 : 0;
	idx += (ctrl >> 16) & 3;
	dev_info(&bp->pdev->dev, "control: %x\n", ctrl);
	dev_info(&bp->pdev->dev, "TOD Protocol %s %s\n", proto_name[idx],
		 ctrl & TOD_CTRL_ENABLE ? "enabled" : "");

	idx = (ctrl >> TOD_CTRL_GNSS_SHIFT) & TOD_CTRL_GNSS_MASK;
	अगर (idx < ARRAY_SIZE(gnss_name))
		dev_info(&bp->pdev->dev, "GNSS %s\n", gnss_name[idx]);

	reg = ioपढ़ो32(&bp->tod->status);
	dev_info(&bp->pdev->dev, "status: %x\n", reg);

	reg = ioपढ़ो32(&bp->tod->correction_sec);
	dev_info(&bp->pdev->dev, "correction: %d\n", reg);

	reg = ioपढ़ो32(&bp->tod->utc_status);
	dev_info(&bp->pdev->dev, "utc_status: %x\n", reg);
	dev_info(&bp->pdev->dev, "utc_offset: %d  valid:%d  leap_valid:%d\n",
		 reg & TOD_STATUS_UTC_MASK, reg & TOD_STATUS_UTC_VALID ? 1 : 0,
		 reg & TOD_STATUS_LEAP_VALID ? 1 : 0);
पूर्ण

अटल व्योम
ptp_ocp_info(काष्ठा ptp_ocp *bp)
अणु
	अटल स्थिर अक्षर * स्थिर घड़ी_name[] = अणु
		"NO", "TOD", "IRIG", "PPS", "PTP", "RTC", "REGS", "EXT"
	पूर्ण;
	u32 version, select;

	version = ioपढ़ो32(&bp->reg->version);
	select = ioपढ़ो32(&bp->reg->select);
	dev_info(&bp->pdev->dev, "Version %d.%d.%d, clock %s, device ptp%d\n",
		 version >> 24, (version >> 16) & 0xff, version & 0xffff,
		 घड़ी_name[select & 7],
		 ptp_घड़ी_index(bp->ptp));

	ptp_ocp_tod_info(bp);
पूर्ण

अटल पूर्णांक
ptp_ocp_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा ptp_ocp *bp;
	पूर्णांक err;

	bp = kzalloc(माप(*bp), GFP_KERNEL);
	अगर (!bp)
		वापस -ENOMEM;
	bp->pdev = pdev;
	pci_set_drvdata(pdev, bp);

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "pci_enable_device\n");
		जाओ out_मुक्त;
	पूर्ण

	err = pci_request_regions(pdev, KBUILD_MODNAME);
	अगर (err) अणु
		dev_err(&pdev->dev, "pci_request_region\n");
		जाओ out_disable;
	पूर्ण

	bp->base = pci_ioremap_bar(pdev, 0);
	अगर (!bp->base) अणु
		dev_err(&pdev->dev, "io_remap bar0\n");
		err = -ENOMEM;
		जाओ out_release_regions;
	पूर्ण
	bp->reg = bp->base + OCP_REGISTER_OFFSET;
	bp->tod = bp->base + TOD_REGISTER_OFFSET;
	bp->ptp_info = ptp_ocp_घड़ी_info;
	spin_lock_init(&bp->lock);

	err = ptp_ocp_check_घड़ी(bp);
	अगर (err)
		जाओ out;

	bp->ptp = ptp_घड़ी_रेजिस्टर(&bp->ptp_info, &pdev->dev);
	अगर (IS_ERR(bp->ptp)) अणु
		dev_err(&pdev->dev, "ptp_clock_register\n");
		err = PTR_ERR(bp->ptp);
		जाओ out;
	पूर्ण

	ptp_ocp_info(bp);

	वापस 0;

out:
	pci_iounmap(pdev, bp->base);
out_release_regions:
	pci_release_regions(pdev);
out_disable:
	pci_disable_device(pdev);
out_मुक्त:
	kमुक्त(bp);

	वापस err;
पूर्ण

अटल व्योम
ptp_ocp_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ptp_ocp *bp = pci_get_drvdata(pdev);

	ptp_घड़ी_unरेजिस्टर(bp->ptp);
	pci_iounmap(pdev, bp->base);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, शून्य);
	kमुक्त(bp);
पूर्ण

अटल काष्ठा pci_driver ptp_ocp_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= ptp_ocp_pcidev_id,
	.probe		= ptp_ocp_probe,
	.हटाओ		= ptp_ocp_हटाओ,
पूर्ण;

अटल पूर्णांक __init
ptp_ocp_init(व्योम)
अणु
	पूर्णांक err;

	err = pci_रेजिस्टर_driver(&ptp_ocp_driver);
	वापस err;
पूर्ण

अटल व्योम __निकास
ptp_ocp_fini(व्योम)
अणु
	pci_unरेजिस्टर_driver(&ptp_ocp_driver);
पूर्ण

module_init(ptp_ocp_init);
module_निकास(ptp_ocp_fini);

MODULE_DESCRIPTION("OpenCompute TimeCard driver");
MODULE_LICENSE("GPL v2");
