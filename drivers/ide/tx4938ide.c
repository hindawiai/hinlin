<शैली गुरु>
/*
 * TX4938 पूर्णांकernal IDE driver
 * Based on tx4939ide.c.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * (C) Copyright TOSHIBA CORPORATION 2005-2007
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/ide.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/ide.h>
#समावेश <यंत्र/txx9/tx4938.h>

अटल व्योम tx4938ide_tune_ebusc(अचिन्हित पूर्णांक ebus_ch,
				 अचिन्हित पूर्णांक gbus_घड़ी,
				 u8 pio)
अणु
	काष्ठा ide_timing *t = ide_timing_find_mode(XFER_PIO_0 + pio);
	u64 cr = __raw_पढ़ोq(&tx4938_ebuscptr->cr[ebus_ch]);
	अचिन्हित पूर्णांक sp = (cr >> 4) & 3;
	अचिन्हित पूर्णांक घड़ी = gbus_घड़ी / (4 - sp);
	अचिन्हित पूर्णांक cycle = 1000000000 / घड़ी;
	अचिन्हित पूर्णांक shwt;
	पूर्णांक wt;

	/* Minimum DIOx- active समय */
	wt = DIV_ROUND_UP(t->act8b, cycle) - 2;
	/* IORDY setup समय: 35ns */
	wt = max_t(पूर्णांक, wt, DIV_ROUND_UP(35, cycle));
	/* actual रुको-cycle is max(wt & ~1, 1) */
	अगर (wt > 2 && (wt & 1))
		wt++;
	wt &= ~1;
	/* Address-valid to DIOR/DIOW setup */
	shwt = DIV_ROUND_UP(t->setup, cycle);

	/* -DIOx recovery समय (SHWT * 4) and cycle समय requirement */
	जबतक ((shwt * 4 + wt + (wt ? 2 : 3)) * cycle < t->cycle)
		shwt++;
	अगर (shwt > 7) अणु
		pr_warn("tx4938ide: SHWT violation (%d)\n", shwt);
		shwt = 7;
	पूर्ण
	pr_debug("tx4938ide: ebus %d, bus cycle %dns, WT %d, SHWT %d\n",
		 ebus_ch, cycle, wt, shwt);

	__raw_ग_लिखोq((cr & ~0x3f007ull) | (wt << 12) | shwt,
		     &tx4938_ebuscptr->cr[ebus_ch]);
पूर्ण

अटल व्योम tx4938ide_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	काष्ठा tx4938ide_platक्रमm_info *pdata = dev_get_platdata(hwअगर->dev);
	u8 safe = drive->pio_mode - XFER_PIO_0;
	ide_drive_t *pair;

	pair = ide_get_pair_dev(drive);
	अगर (pair)
		safe = min_t(u8, safe, pair->pio_mode - XFER_PIO_0);
	tx4938ide_tune_ebusc(pdata->ebus_ch, pdata->gbus_घड़ी, safe);
पूर्ण

#अगर_घोषित __BIG_ENDIAN

/* custom iops (independent from SWAP_IO_SPACE) */
अटल व्योम tx4938ide_input_data_swap(ide_drive_t *drive, काष्ठा ide_cmd *cmd,
				व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित दीर्घ port = drive->hwअगर->io_ports.data_addr;
	अचिन्हित लघु *ptr = buf;
	अचिन्हित पूर्णांक count = (len + 1) / 2;

	जबतक (count--)
		*ptr++ = cpu_to_le16(__raw_पढ़ोw((व्योम __iomem *)port));
	__ide_flush_dcache_range((अचिन्हित दीर्घ)buf, roundup(len, 2));
पूर्ण

अटल व्योम tx4938ide_output_data_swap(ide_drive_t *drive, काष्ठा ide_cmd *cmd,
				व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित दीर्घ port = drive->hwअगर->io_ports.data_addr;
	अचिन्हित लघु *ptr = buf;
	अचिन्हित पूर्णांक count = (len + 1) / 2;

	जबतक (count--) अणु
		__raw_ग_लिखोw(le16_to_cpu(*ptr), (व्योम __iomem *)port);
		ptr++;
	पूर्ण
	__ide_flush_dcache_range((अचिन्हित दीर्घ)buf, roundup(len, 2));
पूर्ण

अटल स्थिर काष्ठा ide_tp_ops tx4938ide_tp_ops = अणु
	.exec_command		= ide_exec_command,
	.पढ़ो_status		= ide_पढ़ो_status,
	.पढ़ो_altstatus		= ide_पढ़ो_altstatus,
	.ग_लिखो_devctl		= ide_ग_लिखो_devctl,

	.dev_select		= ide_dev_select,
	.tf_load		= ide_tf_load,
	.tf_पढ़ो		= ide_tf_पढ़ो,

	.input_data		= tx4938ide_input_data_swap,
	.output_data		= tx4938ide_output_data_swap,
पूर्ण;

#पूर्ण_अगर	/* __BIG_ENDIAN */

अटल स्थिर काष्ठा ide_port_ops tx4938ide_port_ops = अणु
	.set_pio_mode		= tx4938ide_set_pio_mode,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info tx4938ide_port_info __initस्थिर = अणु
	.port_ops		= &tx4938ide_port_ops,
#अगर_घोषित __BIG_ENDIAN
	.tp_ops			= &tx4938ide_tp_ops,
#पूर्ण_अगर
	.host_flags		= IDE_HFLAG_MMIO | IDE_HFLAG_NO_DMA,
	.pio_mask		= ATA_PIO5,
	.chipset		= ide_generic,
पूर्ण;

अटल पूर्णांक __init tx4938ide_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ide_hw hw, *hws[] = अणु &hw पूर्ण;
	काष्ठा ide_host *host;
	काष्ठा resource *res;
	काष्ठा tx4938ide_platक्रमm_info *pdata = dev_get_platdata(&pdev->dev);
	पूर्णांक irq, ret, i;
	अचिन्हित दीर्घ mapbase, mapctl;
	काष्ठा ide_port_info d = tx4938ide_port_info;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -ENODEV;
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	अगर (!devm_request_mem_region(&pdev->dev, res->start,
				     resource_size(res), "tx4938ide"))
		वापस -EBUSY;
	mapbase = (अचिन्हित दीर्घ)devm_ioremap(&pdev->dev, res->start,
					      8 << pdata->ioport_shअगरt);
	mapctl = (अचिन्हित दीर्घ)devm_ioremap(&pdev->dev,
					     res->start + 0x10000 +
					     (6 << pdata->ioport_shअगरt),
					     1 << pdata->ioport_shअगरt);
	अगर (!mapbase || !mapctl)
		वापस -EBUSY;

	स_रखो(&hw, 0, माप(hw));
	अगर (pdata->ioport_shअगरt) अणु
		अचिन्हित दीर्घ port = mapbase;
		अचिन्हित दीर्घ ctl = mapctl;

		hw.io_ports_array[0] = port;
#अगर_घोषित __BIG_ENDIAN
		port++;
		ctl++;
#पूर्ण_अगर
		क्रम (i = 1; i <= 7; i++)
			hw.io_ports_array[i] =
				port + (i << pdata->ioport_shअगरt);
		hw.io_ports.ctl_addr = ctl;
	पूर्ण अन्यथा
		ide_std_init_ports(&hw, mapbase, mapctl);
	hw.irq = irq;
	hw.dev = &pdev->dev;

	pr_info("TX4938 IDE interface (base %#lx, ctl %#lx, irq %d)\n",
		mapbase, mapctl, hw.irq);
	अगर (pdata->gbus_घड़ी)
		tx4938ide_tune_ebusc(pdata->ebus_ch, pdata->gbus_घड़ी, 0);
	अन्यथा
		d.port_ops = शून्य;
	ret = ide_host_add(&d, hws, 1, &host);
	अगर (!ret)
		platक्रमm_set_drvdata(pdev, host);
	वापस ret;
पूर्ण

अटल पूर्णांक __निकास tx4938ide_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ide_host *host = platक्रमm_get_drvdata(pdev);

	ide_host_हटाओ(host);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver tx4938ide_driver = अणु
	.driver		= अणु
		.name	= "tx4938ide",
	पूर्ण,
	.हटाओ = __निकास_p(tx4938ide_हटाओ),
पूर्ण;

module_platक्रमm_driver_probe(tx4938ide_driver, tx4938ide_probe);

MODULE_DESCRIPTION("TX4938 internal IDE driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:tx4938ide");
