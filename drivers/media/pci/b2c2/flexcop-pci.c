<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Linux driver the digital TV devices equipped with B2C2 FlexcopII(b)/III
 * flexcop-pci.c - covers the PCI part including DMA transfers
 * see flexcop.c क्रम copyright inक्रमmation
 */

#घोषणा FC_LOG_PREFIX "flexcop-pci"
#समावेश "flexcop-common.h"

अटल पूर्णांक enable_pid_filtering = 1;
module_param(enable_pid_filtering, पूर्णांक, 0444);
MODULE_PARM_DESC(enable_pid_filtering,
	"enable hardware pid filtering: supported values: 0 (fullts), 1");

अटल पूर्णांक irq_chk_पूर्णांकv = 100;
module_param(irq_chk_पूर्णांकv, पूर्णांक, 0644);
MODULE_PARM_DESC(irq_chk_पूर्णांकv, "set the interval for IRQ streaming watchdog.");

#अगर_घोषित CONFIG_DVB_B2C2_FLEXCOP_DEBUG
#घोषणा dprपूर्णांकk(level, args...) \
	करो अणु अगर ((debug & (level))) prपूर्णांकk(args); पूर्ण जबतक (0)
#घोषणा DEBSTATUS ""
#अन्यथा
#घोषणा dprपूर्णांकk(level, args...) no_prपूर्णांकk(args)
#घोषणा DEBSTATUS " (debugging is not enabled)"
#पूर्ण_अगर

#घोषणा deb_info(args...) dprपूर्णांकk(0x01, args)
#घोषणा deb_reg(args...) dprपूर्णांकk(0x02, args)
#घोषणा deb_ts(args...) dprपूर्णांकk(0x04, args)
#घोषणा deb_irq(args...) dprपूर्णांकk(0x08, args)
#घोषणा deb_chk(args...) dprपूर्णांकk(0x10, args)

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug,
	"set debug level (1=info,2=regs,4=TS,8=irqdma,16=check (|-able))."
	DEBSTATUS);

#घोषणा DRIVER_VERSION "0.1"
#घोषणा DRIVER_NAME "flexcop-pci"
#घोषणा DRIVER_AUTHOR "Patrick Boettcher <patrick.boettcher@posteo.de>"

काष्ठा flexcop_pci अणु
	काष्ठा pci_dev *pdev;

#घोषणा FC_PCI_INIT     0x01
#घोषणा FC_PCI_DMA_INIT 0x02
	पूर्णांक init_state;

	व्योम __iomem *io_mem;
	u32 irq;
	/* buffersize (at least क्रम DMA1, need to be % 188 == 0,
	 * this logic is required */
#घोषणा FC_DEFAULT_DMA1_बफ_मानE (1280 * 188)
#घोषणा FC_DEFAULT_DMA2_बफ_मानE (10 * 188)
	काष्ठा flexcop_dma dma[2];

	पूर्णांक active_dma1_addr; /* 0 = addr0 of dma1; 1 = addr1 of dma1 */
	u32 last_dma1_cur_pos;
	/* position of the poपूर्णांकer last समय the समयr/packet irq occurred */
	पूर्णांक count;
	पूर्णांक count_prev;
	पूर्णांक stream_problem;

	spinlock_t irq_lock;
	अचिन्हित दीर्घ last_irq;

	काष्ठा delayed_work irq_check_work;
	काष्ठा flexcop_device *fc_dev;
पूर्ण;

अटल पूर्णांक lastwreg, lastwval, lastrreg, lastrval;

अटल flexcop_ibi_value flexcop_pci_पढ़ो_ibi_reg(काष्ठा flexcop_device *fc,
		flexcop_ibi_रेजिस्टर r)
अणु
	काष्ठा flexcop_pci *fc_pci = fc->bus_specअगरic;
	flexcop_ibi_value v;
	v.raw = पढ़ोl(fc_pci->io_mem + r);

	अगर (lastrreg != r || lastrval != v.raw) अणु
		lastrreg = r; lastrval = v.raw;
		deb_reg("new rd: %3x: %08x\n", r, v.raw);
	पूर्ण

	वापस v;
पूर्ण

अटल पूर्णांक flexcop_pci_ग_लिखो_ibi_reg(काष्ठा flexcop_device *fc,
		flexcop_ibi_रेजिस्टर r, flexcop_ibi_value v)
अणु
	काष्ठा flexcop_pci *fc_pci = fc->bus_specअगरic;

	अगर (lastwreg != r || lastwval != v.raw) अणु
		lastwreg = r; lastwval = v.raw;
		deb_reg("new wr: %3x: %08x\n", r, v.raw);
	पूर्ण

	ग_लिखोl(v.raw, fc_pci->io_mem + r);
	वापस 0;
पूर्ण

अटल व्योम flexcop_pci_irq_check_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा flexcop_pci *fc_pci =
		container_of(work, काष्ठा flexcop_pci, irq_check_work.work);
	काष्ठा flexcop_device *fc = fc_pci->fc_dev;

	अगर (fc->feedcount) अणु

		अगर (fc_pci->count == fc_pci->count_prev) अणु
			deb_chk("no IRQ since the last check\n");
			अगर (fc_pci->stream_problem++ == 3) अणु
				काष्ठा dvb_demux_feed *feed;
				deb_info("flexcop-pci: stream problem, resetting pid filter\n");

				spin_lock_irq(&fc->demux.lock);
				list_क्रम_each_entry(feed, &fc->demux.feed_list,
						list_head) अणु
					flexcop_pid_feed_control(fc, feed, 0);
				पूर्ण

				list_क्रम_each_entry(feed, &fc->demux.feed_list,
						list_head) अणु
					flexcop_pid_feed_control(fc, feed, 1);
				पूर्ण
				spin_unlock_irq(&fc->demux.lock);

				fc_pci->stream_problem = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			fc_pci->stream_problem = 0;
			fc_pci->count_prev = fc_pci->count;
		पूर्ण
	पूर्ण

	schedule_delayed_work(&fc_pci->irq_check_work,
			msecs_to_jअगरfies(irq_chk_पूर्णांकv < 100 ? 100 : irq_chk_पूर्णांकv));
पूर्ण

/* When PID filtering is turned on, we use the समयr IRQ, because small amounts
 * of data need to be passed to the user space instantly as well. When PID
 * filtering is turned off, we use the page-change-IRQ */
अटल irqवापस_t flexcop_pci_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा flexcop_pci *fc_pci = dev_id;
	काष्ठा flexcop_device *fc = fc_pci->fc_dev;
	अचिन्हित दीर्घ flags;
	flexcop_ibi_value v;
	irqवापस_t ret = IRQ_HANDLED;

	spin_lock_irqsave(&fc_pci->irq_lock, flags);
	v = fc->पढ़ो_ibi_reg(fc, irq_20c);

	/* errors */
	अगर (v.irq_20c.Data_receiver_error)
		deb_chk("data receiver error\n");
	अगर (v.irq_20c.Continuity_error_flag)
		deb_chk("Continuity error flag is set\n");
	अगर (v.irq_20c.LLC_SNAP_FLAG_set)
		deb_chk("LLC_SNAP_FLAG_set is set\n");
	अगर (v.irq_20c.Transport_Error)
		deb_chk("Transport error\n");

	अगर ((fc_pci->count % 1000) == 0)
		deb_chk("%d valid irq took place so far\n", fc_pci->count);

	अगर (v.irq_20c.DMA1_IRQ_Status == 1) अणु
		अगर (fc_pci->active_dma1_addr == 0)
			flexcop_pass_dmx_packets(fc_pci->fc_dev,
					fc_pci->dma[0].cpu_addr0,
					fc_pci->dma[0].size / 188);
		अन्यथा
			flexcop_pass_dmx_packets(fc_pci->fc_dev,
					fc_pci->dma[0].cpu_addr1,
					fc_pci->dma[0].size / 188);

		deb_irq("page change to page: %d\n",!fc_pci->active_dma1_addr);
		fc_pci->active_dma1_addr = !fc_pci->active_dma1_addr;
		/* क्रम the समयr IRQ we only can use buffer dmx feeding, because we करोn't have
		 * complete TS packets when पढ़ोing from the DMA memory */
	पूर्ण अन्यथा अगर (v.irq_20c.DMA1_Timer_Status == 1) अणु
		dma_addr_t cur_addr =
			fc->पढ़ो_ibi_reg(fc,dma1_008).dma_0x8.dma_cur_addr << 2;
		u32 cur_pos = cur_addr - fc_pci->dma[0].dma_addr0;

		deb_irq("%u irq: %08x cur_addr: %llx: cur_pos: %08x, last_cur_pos: %08x ",
				jअगरfies_to_usecs(jअगरfies - fc_pci->last_irq),
				v.raw, (अचिन्हित दीर्घ दीर्घ)cur_addr, cur_pos,
				fc_pci->last_dma1_cur_pos);
		fc_pci->last_irq = jअगरfies;

		/* buffer end was reached, restarted from the beginning
		 * pass the data from last_cur_pos to the buffer end to the demux
		 */
		अगर (cur_pos < fc_pci->last_dma1_cur_pos) अणु
			deb_irq(" end was reached: passing %d bytes ",
				(fc_pci->dma[0].size*2 - 1) -
				fc_pci->last_dma1_cur_pos);
			flexcop_pass_dmx_data(fc_pci->fc_dev,
				fc_pci->dma[0].cpu_addr0 +
					fc_pci->last_dma1_cur_pos,
				(fc_pci->dma[0].size*2) -
					fc_pci->last_dma1_cur_pos);
			fc_pci->last_dma1_cur_pos = 0;
		पूर्ण

		अगर (cur_pos > fc_pci->last_dma1_cur_pos) अणु
			deb_irq(" passing %d bytes ",
				cur_pos - fc_pci->last_dma1_cur_pos);
			flexcop_pass_dmx_data(fc_pci->fc_dev,
				fc_pci->dma[0].cpu_addr0 +
					fc_pci->last_dma1_cur_pos,
				cur_pos - fc_pci->last_dma1_cur_pos);
		पूर्ण
		deb_irq("\n");

		fc_pci->last_dma1_cur_pos = cur_pos;
		fc_pci->count++;
	पूर्ण अन्यथा अणु
		deb_irq("isr for flexcop called, apparently without reason (%08x)\n",
			v.raw);
		ret = IRQ_NONE;
	पूर्ण

	spin_unlock_irqrestore(&fc_pci->irq_lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक flexcop_pci_stream_control(काष्ठा flexcop_device *fc, पूर्णांक onoff)
अणु
	काष्ठा flexcop_pci *fc_pci = fc->bus_specअगरic;
	अगर (onoff) अणु
		flexcop_dma_config(fc, &fc_pci->dma[0], FC_DMA_1);
		flexcop_dma_config(fc, &fc_pci->dma[1], FC_DMA_2);
		flexcop_dma_config_समयr(fc, FC_DMA_1, 0);
		flexcop_dma_xfer_control(fc, FC_DMA_1,
				FC_DMA_SUBADDR_0 | FC_DMA_SUBADDR_1, 1);
		deb_irq("DMA xfer enabled\n");

		fc_pci->last_dma1_cur_pos = 0;
		flexcop_dma_control_समयr_irq(fc, FC_DMA_1, 1);
		deb_irq("IRQ enabled\n");
		fc_pci->count_prev = fc_pci->count;
	पूर्ण अन्यथा अणु
		flexcop_dma_control_समयr_irq(fc, FC_DMA_1, 0);
		deb_irq("IRQ disabled\n");

		flexcop_dma_xfer_control(fc, FC_DMA_1,
			 FC_DMA_SUBADDR_0 | FC_DMA_SUBADDR_1, 0);
		deb_irq("DMA xfer disabled\n");
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक flexcop_pci_dma_init(काष्ठा flexcop_pci *fc_pci)
अणु
	पूर्णांक ret;
	ret = flexcop_dma_allocate(fc_pci->pdev, &fc_pci->dma[0],
			FC_DEFAULT_DMA1_बफ_मानE);
	अगर (ret != 0)
		वापस ret;

	ret = flexcop_dma_allocate(fc_pci->pdev, &fc_pci->dma[1],
			FC_DEFAULT_DMA2_बफ_मानE);
	अगर (ret != 0) अणु
		flexcop_dma_मुक्त(&fc_pci->dma[0]);
		वापस ret;
	पूर्ण

	flexcop_sram_set_dest(fc_pci->fc_dev, FC_SRAM_DEST_MEDIA |
			FC_SRAM_DEST_NET, FC_SRAM_DEST_TARGET_DMA1);
	flexcop_sram_set_dest(fc_pci->fc_dev, FC_SRAM_DEST_CAO |
			FC_SRAM_DEST_CAI, FC_SRAM_DEST_TARGET_DMA2);
	fc_pci->init_state |= FC_PCI_DMA_INIT;
	वापस ret;
पूर्ण

अटल व्योम flexcop_pci_dma_निकास(काष्ठा flexcop_pci *fc_pci)
अणु
	अगर (fc_pci->init_state & FC_PCI_DMA_INIT) अणु
		flexcop_dma_मुक्त(&fc_pci->dma[0]);
		flexcop_dma_मुक्त(&fc_pci->dma[1]);
	पूर्ण
	fc_pci->init_state &= ~FC_PCI_DMA_INIT;
पूर्ण

अटल पूर्णांक flexcop_pci_init(काष्ठा flexcop_pci *fc_pci)
अणु
	पूर्णांक ret;

	info("card revision %x", fc_pci->pdev->revision);

	अगर ((ret = pci_enable_device(fc_pci->pdev)) != 0)
		वापस ret;
	pci_set_master(fc_pci->pdev);

	अगर ((ret = pci_request_regions(fc_pci->pdev, DRIVER_NAME)) != 0)
		जाओ err_pci_disable_device;

	fc_pci->io_mem = pci_iomap(fc_pci->pdev, 0, 0x800);

	अगर (!fc_pci->io_mem) अणु
		err("cannot map io memory\n");
		ret = -EIO;
		जाओ err_pci_release_regions;
	पूर्ण

	pci_set_drvdata(fc_pci->pdev, fc_pci);
	spin_lock_init(&fc_pci->irq_lock);
	अगर ((ret = request_irq(fc_pci->pdev->irq, flexcop_pci_isr,
					IRQF_SHARED, DRIVER_NAME, fc_pci)) != 0)
		जाओ err_pci_iounmap;

	fc_pci->init_state |= FC_PCI_INIT;
	वापस ret;

err_pci_iounmap:
	pci_iounmap(fc_pci->pdev, fc_pci->io_mem);
err_pci_release_regions:
	pci_release_regions(fc_pci->pdev);
err_pci_disable_device:
	pci_disable_device(fc_pci->pdev);
	वापस ret;
पूर्ण

अटल व्योम flexcop_pci_निकास(काष्ठा flexcop_pci *fc_pci)
अणु
	अगर (fc_pci->init_state & FC_PCI_INIT) अणु
		मुक्त_irq(fc_pci->pdev->irq, fc_pci);
		pci_iounmap(fc_pci->pdev, fc_pci->io_mem);
		pci_release_regions(fc_pci->pdev);
		pci_disable_device(fc_pci->pdev);
	पूर्ण
	fc_pci->init_state &= ~FC_PCI_INIT;
पूर्ण

अटल पूर्णांक flexcop_pci_probe(काष्ठा pci_dev *pdev,
		स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा flexcop_device *fc;
	काष्ठा flexcop_pci *fc_pci;
	पूर्णांक ret = -ENOMEM;

	अगर ((fc = flexcop_device_kदो_स्मृति(माप(काष्ठा flexcop_pci))) == शून्य) अणु
		err("out of memory\n");
		वापस -ENOMEM;
	पूर्ण

	/* general flexcop init */
	fc_pci = fc->bus_specअगरic;
	fc_pci->fc_dev = fc;

	fc->पढ़ो_ibi_reg = flexcop_pci_पढ़ो_ibi_reg;
	fc->ग_लिखो_ibi_reg = flexcop_pci_ग_लिखो_ibi_reg;
	fc->i2c_request = flexcop_i2c_request;
	fc->get_mac_addr = flexcop_eeprom_check_mac_addr;
	fc->stream_control = flexcop_pci_stream_control;

	अगर (enable_pid_filtering)
		info("will use the HW PID filter.");
	अन्यथा
		info("will pass the complete TS to the demuxer.");

	fc->pid_filtering = enable_pid_filtering;
	fc->bus_type = FC_PCI;
	fc->dev = &pdev->dev;
	fc->owner = THIS_MODULE;

	/* bus specअगरic part */
	fc_pci->pdev = pdev;
	अगर ((ret = flexcop_pci_init(fc_pci)) != 0)
		जाओ err_kमुक्त;

	/* init flexcop */
	अगर ((ret = flexcop_device_initialize(fc)) != 0)
		जाओ err_pci_निकास;

	/* init dma */
	अगर ((ret = flexcop_pci_dma_init(fc_pci)) != 0)
		जाओ err_fc_निकास;

	INIT_DELAYED_WORK(&fc_pci->irq_check_work, flexcop_pci_irq_check_work);

	अगर (irq_chk_पूर्णांकv > 0)
		schedule_delayed_work(&fc_pci->irq_check_work,
				msecs_to_jअगरfies(irq_chk_पूर्णांकv < 100 ?
					100 :
					irq_chk_पूर्णांकv));
	वापस ret;

err_fc_निकास:
	flexcop_device_निकास(fc);
err_pci_निकास:
	flexcop_pci_निकास(fc_pci);
err_kमुक्त:
	flexcop_device_kमुक्त(fc);
	वापस ret;
पूर्ण

/* in theory every _निकास function should be called exactly two बार,
 * here and in the bail-out-part of the _init-function
 */
अटल व्योम flexcop_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा flexcop_pci *fc_pci = pci_get_drvdata(pdev);

	अगर (irq_chk_पूर्णांकv > 0)
		cancel_delayed_work(&fc_pci->irq_check_work);

	flexcop_pci_dma_निकास(fc_pci);
	flexcop_device_निकास(fc_pci->fc_dev);
	flexcop_pci_निकास(fc_pci);
	flexcop_device_kमुक्त(fc_pci->fc_dev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id flexcop_pci_tbl[] = अणु
	अणु PCI_DEVICE(0x13d0, 0x2103) पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, flexcop_pci_tbl);

अटल काष्ठा pci_driver flexcop_pci_driver = अणु
	.name     = "b2c2_flexcop_pci",
	.id_table = flexcop_pci_tbl,
	.probe    = flexcop_pci_probe,
	.हटाओ   = flexcop_pci_हटाओ,
पूर्ण;

module_pci_driver(flexcop_pci_driver);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_NAME);
MODULE_LICENSE("GPL");
