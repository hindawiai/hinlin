<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PTP 1588 घड़ी using the EG20T PCH
 *
 * Copyright (C) 2010 OMICRON electronics GmbH
 * Copyright (C) 2011-2012 LAPIS SEMICONDUCTOR Co., LTD.
 *
 * This code was derived from the IXP46X driver.
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/ptp_pch.h>
#समावेश <linux/slab.h>

#घोषणा STATION_ADDR_LEN	20
#घोषणा PCI_DEVICE_ID_PCH_1588	0x8819
#घोषणा IO_MEM_BAR 1

#घोषणा DEFAULT_ADDEND 0xA0000000
#घोषणा TICKS_NS_SHIFT  5
#घोषणा N_EXT_TS	2

क्रमागत pch_status अणु
	PCH_SUCCESS,
	PCH_INVALIDPARAM,
	PCH_NOTIMESTAMP,
	PCH_INTERRUPTMODEINUSE,
	PCH_FAILED,
	PCH_UNSUPPORTED,
पूर्ण;

/*
 * काष्ठा pch_ts_regs - IEEE 1588 रेजिस्टरs
 */
काष्ठा pch_ts_regs अणु
	u32 control;
	u32 event;
	u32 addend;
	u32 accum;
	u32 test;
	u32 ts_compare;
	u32 rsysसमय_lo;
	u32 rsysसमय_hi;
	u32 sysसमय_lo;
	u32 sysसमय_hi;
	u32 trgt_lo;
	u32 trgt_hi;
	u32 यंत्रs_lo;
	u32 यंत्रs_hi;
	u32 amms_lo;
	u32 amms_hi;
	u32 ch_control;
	u32 ch_event;
	u32 tx_snap_lo;
	u32 tx_snap_hi;
	u32 rx_snap_lo;
	u32 rx_snap_hi;
	u32 src_uuid_lo;
	u32 src_uuid_hi;
	u32 can_status;
	u32 can_snap_lo;
	u32 can_snap_hi;
	u32 ts_sel;
	u32 ts_st[6];
	u32 reserve1[14];
	u32 stl_max_set_en;
	u32 stl_max_set;
	u32 reserve2[13];
	u32 srst;
पूर्ण;

#घोषणा PCH_TSC_RESET		(1 << 0)
#घोषणा PCH_TSC_TTM_MASK	(1 << 1)
#घोषणा PCH_TSC_ASMS_MASK	(1 << 2)
#घोषणा PCH_TSC_AMMS_MASK	(1 << 3)
#घोषणा PCH_TSC_PPSM_MASK	(1 << 4)
#घोषणा PCH_TSE_TTIPEND		(1 << 1)
#घोषणा PCH_TSE_SNS		(1 << 2)
#घोषणा PCH_TSE_SNM		(1 << 3)
#घोषणा PCH_TSE_PPS		(1 << 4)
#घोषणा PCH_CC_MM		(1 << 0)
#घोषणा PCH_CC_TA		(1 << 1)

#घोषणा PCH_CC_MODE_SHIFT	16
#घोषणा PCH_CC_MODE_MASK	0x001F0000
#घोषणा PCH_CC_VERSION		(1 << 31)
#घोषणा PCH_CE_TXS		(1 << 0)
#घोषणा PCH_CE_RXS		(1 << 1)
#घोषणा PCH_CE_OVR		(1 << 0)
#घोषणा PCH_CE_VAL		(1 << 1)
#घोषणा PCH_ECS_ETH		(1 << 0)

#घोषणा PCH_ECS_CAN		(1 << 1)
#घोषणा PCH_STATION_BYTES	6

#घोषणा PCH_IEEE1588_ETH	(1 << 0)
#घोषणा PCH_IEEE1588_CAN	(1 << 1)

/*
 * काष्ठा pch_dev - Driver निजी data
 */
काष्ठा pch_dev अणु
	काष्ठा pch_ts_regs __iomem *regs;
	काष्ठा ptp_घड़ी *ptp_घड़ी;
	काष्ठा ptp_घड़ी_info caps;
	पूर्णांक exts0_enabled;
	पूर्णांक exts1_enabled;

	u32 mem_base;
	u32 mem_size;
	u32 irq;
	काष्ठा pci_dev *pdev;
	spinlock_t रेजिस्टर_lock;
पूर्ण;

/*
 * काष्ठा pch_params - 1588 module parameter
 */
काष्ठा pch_params अणु
	u8 station[STATION_ADDR_LEN];
पूर्ण;

/* काष्ठाure to hold the module parameters */
अटल काष्ठा pch_params pch_param = अणु
	"00:00:00:00:00:00"
पूर्ण;

/*
 * Register access functions
 */
अटल अंतरभूत व्योम pch_eth_enable_set(काष्ठा pch_dev *chip)
अणु
	u32 val;
	/* SET the eth_enable bit */
	val = ioपढ़ो32(&chip->regs->ts_sel) | (PCH_ECS_ETH);
	ioग_लिखो32(val, (&chip->regs->ts_sel));
पूर्ण

अटल u64 pch_sysसमय_पढ़ो(काष्ठा pch_ts_regs __iomem *regs)
अणु
	u64 ns;
	u32 lo, hi;

	lo = ioपढ़ो32(&regs->sysसमय_lo);
	hi = ioपढ़ो32(&regs->sysसमय_hi);

	ns = ((u64) hi) << 32;
	ns |= lo;
	ns <<= TICKS_NS_SHIFT;

	वापस ns;
पूर्ण

अटल व्योम pch_sysसमय_ग_लिखो(काष्ठा pch_ts_regs __iomem *regs, u64 ns)
अणु
	u32 hi, lo;

	ns >>= TICKS_NS_SHIFT;
	hi = ns >> 32;
	lo = ns & 0xffffffff;

	ioग_लिखो32(lo, &regs->sysसमय_lo);
	ioग_लिखो32(hi, &regs->sysसमय_hi);
पूर्ण

अटल अंतरभूत व्योम pch_block_reset(काष्ठा pch_dev *chip)
अणु
	u32 val;
	/* Reset Hardware Assist block */
	val = ioपढ़ो32(&chip->regs->control) | PCH_TSC_RESET;
	ioग_लिखो32(val, (&chip->regs->control));
	val = val & ~PCH_TSC_RESET;
	ioग_लिखो32(val, (&chip->regs->control));
पूर्ण

व्योम pch_ch_control_ग_लिखो(काष्ठा pci_dev *pdev, u32 val)
अणु
	काष्ठा pch_dev *chip = pci_get_drvdata(pdev);

	ioग_लिखो32(val, (&chip->regs->ch_control));
पूर्ण
EXPORT_SYMBOL(pch_ch_control_ग_लिखो);

u32 pch_ch_event_पढ़ो(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pch_dev *chip = pci_get_drvdata(pdev);
	u32 val;

	val = ioपढ़ो32(&chip->regs->ch_event);

	वापस val;
पूर्ण
EXPORT_SYMBOL(pch_ch_event_पढ़ो);

व्योम pch_ch_event_ग_लिखो(काष्ठा pci_dev *pdev, u32 val)
अणु
	काष्ठा pch_dev *chip = pci_get_drvdata(pdev);

	ioग_लिखो32(val, (&chip->regs->ch_event));
पूर्ण
EXPORT_SYMBOL(pch_ch_event_ग_लिखो);

u32 pch_src_uuid_lo_पढ़ो(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pch_dev *chip = pci_get_drvdata(pdev);
	u32 val;

	val = ioपढ़ो32(&chip->regs->src_uuid_lo);

	वापस val;
पूर्ण
EXPORT_SYMBOL(pch_src_uuid_lo_पढ़ो);

u32 pch_src_uuid_hi_पढ़ो(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pch_dev *chip = pci_get_drvdata(pdev);
	u32 val;

	val = ioपढ़ो32(&chip->regs->src_uuid_hi);

	वापस val;
पूर्ण
EXPORT_SYMBOL(pch_src_uuid_hi_पढ़ो);

u64 pch_rx_snap_पढ़ो(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pch_dev *chip = pci_get_drvdata(pdev);
	u64 ns;
	u32 lo, hi;

	lo = ioपढ़ो32(&chip->regs->rx_snap_lo);
	hi = ioपढ़ो32(&chip->regs->rx_snap_hi);

	ns = ((u64) hi) << 32;
	ns |= lo;
	ns <<= TICKS_NS_SHIFT;

	वापस ns;
पूर्ण
EXPORT_SYMBOL(pch_rx_snap_पढ़ो);

u64 pch_tx_snap_पढ़ो(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pch_dev *chip = pci_get_drvdata(pdev);
	u64 ns;
	u32 lo, hi;

	lo = ioपढ़ो32(&chip->regs->tx_snap_lo);
	hi = ioपढ़ो32(&chip->regs->tx_snap_hi);

	ns = ((u64) hi) << 32;
	ns |= lo;
	ns <<= TICKS_NS_SHIFT;

	वापस ns;
पूर्ण
EXPORT_SYMBOL(pch_tx_snap_पढ़ो);

/* This function enables all 64 bits in प्रणाली समय रेजिस्टरs [high & low].
This is a work-around क्रम non continuous value in the SystemTime Register*/
अटल व्योम pch_set_प्रणाली_समय_count(काष्ठा pch_dev *chip)
अणु
	ioग_लिखो32(0x01, &chip->regs->stl_max_set_en);
	ioग_लिखो32(0xFFFFFFFF, &chip->regs->stl_max_set);
	ioग_लिखो32(0x00, &chip->regs->stl_max_set_en);
पूर्ण

अटल व्योम pch_reset(काष्ठा pch_dev *chip)
अणु
	/* Reset Hardware Assist */
	pch_block_reset(chip);

	/* enable all 32 bits in प्रणाली समय रेजिस्टरs */
	pch_set_प्रणाली_समय_count(chip);
पूर्ण

/**
 * pch_set_station_address() - This API sets the station address used by
 *				    IEEE 1588 hardware when looking at PTP
 *				    traffic on the  ethernet पूर्णांकerface
 * @addr:	dress which contain the column separated address to be used.
 * @pdev:	PCI device.
 */
पूर्णांक pch_set_station_address(u8 *addr, काष्ठा pci_dev *pdev)
अणु
	s32 i;
	काष्ठा pch_dev *chip = pci_get_drvdata(pdev);

	/* Verअगरy the parameter */
	अगर ((chip->regs == शून्य) || addr == (u8 *)शून्य) अणु
		dev_err(&pdev->dev,
			"invalid params returning PCH_INVALIDPARAM\n");
		वापस PCH_INVALIDPARAM;
	पूर्ण
	/* For all station address bytes */
	क्रम (i = 0; i < PCH_STATION_BYTES; i++) अणु
		u32 val;
		s32 पंचांगp;

		पंचांगp = hex_to_bin(addr[i * 3]);
		अगर (पंचांगp < 0) अणु
			dev_err(&pdev->dev,
				"invalid params returning PCH_INVALIDPARAM\n");
			वापस PCH_INVALIDPARAM;
		पूर्ण
		val = पंचांगp * 16;
		पंचांगp = hex_to_bin(addr[(i * 3) + 1]);
		अगर (पंचांगp < 0) अणु
			dev_err(&pdev->dev,
				"invalid params returning PCH_INVALIDPARAM\n");
			वापस PCH_INVALIDPARAM;
		पूर्ण
		val += पंचांगp;
		/* Expects ':' separated addresses */
		अगर ((i < 5) && (addr[(i * 3) + 2] != ':')) अणु
			dev_err(&pdev->dev,
				"invalid params returning PCH_INVALIDPARAM\n");
			वापस PCH_INVALIDPARAM;
		पूर्ण

		/* Ideally we should set the address only after validating
							 entire string */
		dev_dbg(&pdev->dev, "invoking pch_station_set\n");
		ioग_लिखो32(val, &chip->regs->ts_st[i]);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(pch_set_station_address);

/*
 * Interrupt service routine
 */
अटल irqवापस_t isr(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा pch_dev *pch_dev = priv;
	काष्ठा pch_ts_regs __iomem *regs = pch_dev->regs;
	काष्ठा ptp_घड़ी_event event;
	u32 ack = 0, lo, hi, val;

	val = ioपढ़ो32(&regs->event);

	अगर (val & PCH_TSE_SNS) अणु
		ack |= PCH_TSE_SNS;
		अगर (pch_dev->exts0_enabled) अणु
			hi = ioपढ़ो32(&regs->यंत्रs_hi);
			lo = ioपढ़ो32(&regs->यंत्रs_lo);
			event.type = PTP_CLOCK_EXTTS;
			event.index = 0;
			event.बारtamp = ((u64) hi) << 32;
			event.बारtamp |= lo;
			event.बारtamp <<= TICKS_NS_SHIFT;
			ptp_घड़ी_event(pch_dev->ptp_घड़ी, &event);
		पूर्ण
	पूर्ण

	अगर (val & PCH_TSE_SNM) अणु
		ack |= PCH_TSE_SNM;
		अगर (pch_dev->exts1_enabled) अणु
			hi = ioपढ़ो32(&regs->amms_hi);
			lo = ioपढ़ो32(&regs->amms_lo);
			event.type = PTP_CLOCK_EXTTS;
			event.index = 1;
			event.बारtamp = ((u64) hi) << 32;
			event.बारtamp |= lo;
			event.बारtamp <<= TICKS_NS_SHIFT;
			ptp_घड़ी_event(pch_dev->ptp_घड़ी, &event);
		पूर्ण
	पूर्ण

	अगर (val & PCH_TSE_TTIPEND)
		ack |= PCH_TSE_TTIPEND; /* this bit seems to be always set */

	अगर (ack) अणु
		ioग_लिखो32(ack, &regs->event);
		वापस IRQ_HANDLED;
	पूर्ण अन्यथा
		वापस IRQ_NONE;
पूर्ण

/*
 * PTP घड़ी operations
 */

अटल पूर्णांक ptp_pch_adjfreq(काष्ठा ptp_घड़ी_info *ptp, s32 ppb)
अणु
	u64 adj;
	u32 dअगरf, addend;
	पूर्णांक neg_adj = 0;
	काष्ठा pch_dev *pch_dev = container_of(ptp, काष्ठा pch_dev, caps);
	काष्ठा pch_ts_regs __iomem *regs = pch_dev->regs;

	अगर (ppb < 0) अणु
		neg_adj = 1;
		ppb = -ppb;
	पूर्ण
	addend = DEFAULT_ADDEND;
	adj = addend;
	adj *= ppb;
	dअगरf = भाग_u64(adj, 1000000000ULL);

	addend = neg_adj ? addend - dअगरf : addend + dअगरf;

	ioग_लिखो32(addend, &regs->addend);

	वापस 0;
पूर्ण

अटल पूर्णांक ptp_pch_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	s64 now;
	अचिन्हित दीर्घ flags;
	काष्ठा pch_dev *pch_dev = container_of(ptp, काष्ठा pch_dev, caps);
	काष्ठा pch_ts_regs __iomem *regs = pch_dev->regs;

	spin_lock_irqsave(&pch_dev->रेजिस्टर_lock, flags);
	now = pch_sysसमय_पढ़ो(regs);
	now += delta;
	pch_sysसमय_ग_लिखो(regs, now);
	spin_unlock_irqrestore(&pch_dev->रेजिस्टर_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ptp_pch_समय_लो(काष्ठा ptp_घड़ी_info *ptp, काष्ठा बारpec64 *ts)
अणु
	u64 ns;
	अचिन्हित दीर्घ flags;
	काष्ठा pch_dev *pch_dev = container_of(ptp, काष्ठा pch_dev, caps);
	काष्ठा pch_ts_regs __iomem *regs = pch_dev->regs;

	spin_lock_irqsave(&pch_dev->रेजिस्टर_lock, flags);
	ns = pch_sysसमय_पढ़ो(regs);
	spin_unlock_irqrestore(&pch_dev->रेजिस्टर_lock, flags);

	*ts = ns_to_बारpec64(ns);
	वापस 0;
पूर्ण

अटल पूर्णांक ptp_pch_समय_रखो(काष्ठा ptp_घड़ी_info *ptp,
			   स्थिर काष्ठा बारpec64 *ts)
अणु
	u64 ns;
	अचिन्हित दीर्घ flags;
	काष्ठा pch_dev *pch_dev = container_of(ptp, काष्ठा pch_dev, caps);
	काष्ठा pch_ts_regs __iomem *regs = pch_dev->regs;

	ns = बारpec64_to_ns(ts);

	spin_lock_irqsave(&pch_dev->रेजिस्टर_lock, flags);
	pch_sysसमय_ग_लिखो(regs, ns);
	spin_unlock_irqrestore(&pch_dev->रेजिस्टर_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ptp_pch_enable(काष्ठा ptp_घड़ी_info *ptp,
			  काष्ठा ptp_घड़ी_request *rq, पूर्णांक on)
अणु
	काष्ठा pch_dev *pch_dev = container_of(ptp, काष्ठा pch_dev, caps);

	चयन (rq->type) अणु
	हाल PTP_CLK_REQ_EXTTS:
		चयन (rq->extts.index) अणु
		हाल 0:
			pch_dev->exts0_enabled = on ? 1 : 0;
			अवरोध;
		हाल 1:
			pch_dev->exts1_enabled = on ? 1 : 0;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर काष्ठा ptp_घड़ी_info ptp_pch_caps = अणु
	.owner		= THIS_MODULE,
	.name		= "PCH timer",
	.max_adj	= 50000000,
	.n_ext_ts	= N_EXT_TS,
	.n_pins		= 0,
	.pps		= 0,
	.adjfreq	= ptp_pch_adjfreq,
	.adjसमय	= ptp_pch_adjसमय,
	.समय_लो64	= ptp_pch_समय_लो,
	.समय_रखो64	= ptp_pch_समय_रखो,
	.enable		= ptp_pch_enable,
पूर्ण;

#घोषणा pch_suspend शून्य
#घोषणा pch_resume शून्य

अटल व्योम pch_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pch_dev *chip = pci_get_drvdata(pdev);

	ptp_घड़ी_unरेजिस्टर(chip->ptp_घड़ी);
	/* मुक्त the पूर्णांकerrupt */
	अगर (pdev->irq != 0)
		मुक्त_irq(pdev->irq, chip);

	/* unmap the भव IO memory space */
	अगर (chip->regs != शून्य) अणु
		iounmap(chip->regs);
		chip->regs = शून्य;
	पूर्ण
	/* release the reserved IO memory space */
	अगर (chip->mem_base != 0) अणु
		release_mem_region(chip->mem_base, chip->mem_size);
		chip->mem_base = 0;
	पूर्ण
	pci_disable_device(pdev);
	kमुक्त(chip);
	dev_info(&pdev->dev, "complete\n");
पूर्ण

अटल s32
pch_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	s32 ret;
	अचिन्हित दीर्घ flags;
	काष्ठा pch_dev *chip;

	chip = kzalloc(माप(काष्ठा pch_dev), GFP_KERNEL);
	अगर (chip == शून्य)
		वापस -ENOMEM;

	/* enable the 1588 pci device */
	ret = pci_enable_device(pdev);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "could not enable the pci device\n");
		जाओ err_pci_en;
	पूर्ण

	chip->mem_base = pci_resource_start(pdev, IO_MEM_BAR);
	अगर (!chip->mem_base) अणु
		dev_err(&pdev->dev, "could not locate IO memory address\n");
		ret = -ENODEV;
		जाओ err_pci_start;
	पूर्ण

	/* retrieve the available length of the IO memory space */
	chip->mem_size = pci_resource_len(pdev, IO_MEM_BAR);

	/* allocate the memory क्रम the device रेजिस्टरs */
	अगर (!request_mem_region(chip->mem_base, chip->mem_size, "1588_regs")) अणु
		dev_err(&pdev->dev,
			"could not allocate register memory space\n");
		ret = -EBUSY;
		जाओ err_req_mem_region;
	पूर्ण

	/* get the भव address to the 1588 रेजिस्टरs */
	chip->regs = ioremap(chip->mem_base, chip->mem_size);

	अगर (!chip->regs) अणु
		dev_err(&pdev->dev, "Could not get virtual address\n");
		ret = -ENOMEM;
		जाओ err_ioremap;
	पूर्ण

	chip->caps = ptp_pch_caps;
	chip->ptp_घड़ी = ptp_घड़ी_रेजिस्टर(&chip->caps, &pdev->dev);
	अगर (IS_ERR(chip->ptp_घड़ी)) अणु
		ret = PTR_ERR(chip->ptp_घड़ी);
		जाओ err_ptp_घड़ी_reg;
	पूर्ण

	spin_lock_init(&chip->रेजिस्टर_lock);

	ret = request_irq(pdev->irq, &isr, IRQF_SHARED, KBUILD_MODNAME, chip);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "failed to get irq %d\n", pdev->irq);
		जाओ err_req_irq;
	पूर्ण

	/* indicate success */
	chip->irq = pdev->irq;
	chip->pdev = pdev;
	pci_set_drvdata(pdev, chip);

	spin_lock_irqsave(&chip->रेजिस्टर_lock, flags);
	/* reset the ieee1588 h/w */
	pch_reset(chip);

	ioग_लिखो32(DEFAULT_ADDEND, &chip->regs->addend);
	ioग_लिखो32(1, &chip->regs->trgt_lo);
	ioग_लिखो32(0, &chip->regs->trgt_hi);
	ioग_लिखो32(PCH_TSE_TTIPEND, &chip->regs->event);

	pch_eth_enable_set(chip);

	अगर (म_भेद(pch_param.station, "00:00:00:00:00:00") != 0) अणु
		अगर (pch_set_station_address(pch_param.station, pdev) != 0) अणु
			dev_err(&pdev->dev,
			"Invalid station address parameter\n"
			"Module loaded but station address not set correctly\n"
			);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&chip->रेजिस्टर_lock, flags);
	वापस 0;

err_req_irq:
	ptp_घड़ी_unरेजिस्टर(chip->ptp_घड़ी);
err_ptp_घड़ी_reg:
	iounmap(chip->regs);
	chip->regs = शून्य;

err_ioremap:
	release_mem_region(chip->mem_base, chip->mem_size);

err_req_mem_region:
	chip->mem_base = 0;

err_pci_start:
	pci_disable_device(pdev);

err_pci_en:
	kमुक्त(chip);
	dev_err(&pdev->dev, "probe failed(ret=0x%x)\n", ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pci_device_id pch_ieee1588_pcidev_id[] = अणु
	अणु
	  .venकरोr = PCI_VENDOR_ID_INTEL,
	  .device = PCI_DEVICE_ID_PCH_1588
	 पूर्ण,
	अणु0पूर्ण
पूर्ण;

अटल SIMPLE_DEV_PM_OPS(pch_pm_ops, pch_suspend, pch_resume);

अटल काष्ठा pci_driver pch_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = pch_ieee1588_pcidev_id,
	.probe = pch_probe,
	.हटाओ = pch_हटाओ,
	.driver.pm = &pch_pm_ops,
पूर्ण;

अटल व्योम __निकास ptp_pch_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&pch_driver);
पूर्ण

अटल s32 __init ptp_pch_init(व्योम)
अणु
	s32 ret;

	/* रेजिस्टर the driver with the pci core */
	ret = pci_रेजिस्टर_driver(&pch_driver);

	वापस ret;
पूर्ण

module_init(ptp_pch_init);
module_निकास(ptp_pch_निकास);

module_param_string(station,
		    pch_param.station, माप(pch_param.station), 0444);
MODULE_PARM_DESC(station,
	 "IEEE 1588 station address to use - colon separated hex values");

MODULE_AUTHOR("LAPIS SEMICONDUCTOR, <tshimizu818@gmail.com>");
MODULE_DESCRIPTION("PTP clock using the EG20T timer");
MODULE_LICENSE("GPL");
