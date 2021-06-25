<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Implementation of primary ALSA driver code base क्रम NVIDIA Tegra HDA.
 */

#समावेश <linux/clk.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/माला.स>
#समावेश <linux/pm_runसमय.स>

#समावेश <sound/core.h>
#समावेश <sound/initval.h>

#समावेश <sound/hda_codec.h>
#समावेश "hda_controller.h"

/* Defines क्रम Nvidia Tegra HDA support */
#घोषणा HDA_BAR0           0x8000

#घोषणा HDA_CFG_CMD        0x1004
#घोषणा HDA_CFG_BAR0       0x1010

#घोषणा HDA_ENABLE_IO_SPACE       (1 << 0)
#घोषणा HDA_ENABLE_MEM_SPACE      (1 << 1)
#घोषणा HDA_ENABLE_BUS_MASTER     (1 << 2)
#घोषणा HDA_ENABLE_SERR           (1 << 8)
#घोषणा HDA_DISABLE_INTR          (1 << 10)
#घोषणा HDA_BAR0_INIT_PROGRAM     0xFFFFFFFF
#घोषणा HDA_BAR0_FINAL_PROGRAM    (1 << 14)

/* IPFS */
#घोषणा HDA_IPFS_CONFIG           0x180
#घोषणा HDA_IPFS_EN_FPCI          0x1

#घोषणा HDA_IPFS_FPCI_BAR0        0x80
#घोषणा HDA_FPCI_BAR0_START       0x40

#घोषणा HDA_IPFS_INTR_MASK        0x188
#घोषणा HDA_IPFS_EN_INTR          (1 << 16)

/* FPCI */
#घोषणा FPCI_DBG_CFG_2		  0x10F4
#घोषणा FPCI_GCAP_NSDO_SHIFT	  18
#घोषणा FPCI_GCAP_NSDO_MASK	  (0x3 << FPCI_GCAP_NSDO_SHIFT)

/* max number of SDs */
#घोषणा NUM_CAPTURE_SD 1
#घोषणा NUM_PLAYBACK_SD 1

/*
 * Tegra194 करोes not reflect correct number of SDO lines. Below macro
 * is used to update the GCAP रेजिस्टर to workaround the issue.
 */
#घोषणा TEGRA194_NUM_SDO_LINES	  4

काष्ठा hda_tegra अणु
	काष्ठा azx chip;
	काष्ठा device *dev;
	काष्ठा reset_control *reset;
	काष्ठा clk_bulk_data घड़ीs[3];
	अचिन्हित पूर्णांक nघड़ीs;
	व्योम __iomem *regs;
	काष्ठा work_काष्ठा probe_work;
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल पूर्णांक घातer_save = CONFIG_SND_HDA_POWER_SAVE_DEFAULT;
module_param(घातer_save, bपूर्णांक, 0644);
MODULE_PARM_DESC(घातer_save,
		 "Automatic power-saving timeout (in seconds, 0 = disable).");
#अन्यथा
#घोषणा घातer_save	0
#पूर्ण_अगर

अटल स्थिर काष्ठा hda_controller_ops hda_tegra_ops; /* nothing special */

अटल व्योम hda_tegra_init(काष्ठा hda_tegra *hda)
अणु
	u32 v;

	/* Enable PCI access */
	v = पढ़ोl(hda->regs + HDA_IPFS_CONFIG);
	v |= HDA_IPFS_EN_FPCI;
	ग_लिखोl(v, hda->regs + HDA_IPFS_CONFIG);

	/* Enable MEM/IO space and bus master */
	v = पढ़ोl(hda->regs + HDA_CFG_CMD);
	v &= ~HDA_DISABLE_INTR;
	v |= HDA_ENABLE_MEM_SPACE | HDA_ENABLE_IO_SPACE |
		HDA_ENABLE_BUS_MASTER | HDA_ENABLE_SERR;
	ग_लिखोl(v, hda->regs + HDA_CFG_CMD);

	ग_लिखोl(HDA_BAR0_INIT_PROGRAM, hda->regs + HDA_CFG_BAR0);
	ग_लिखोl(HDA_BAR0_FINAL_PROGRAM, hda->regs + HDA_CFG_BAR0);
	ग_लिखोl(HDA_FPCI_BAR0_START, hda->regs + HDA_IPFS_FPCI_BAR0);

	v = पढ़ोl(hda->regs + HDA_IPFS_INTR_MASK);
	v |= HDA_IPFS_EN_INTR;
	ग_लिखोl(v, hda->regs + HDA_IPFS_INTR_MASK);
पूर्ण

/*
 * घातer management
 */
अटल पूर्णांक __maybe_unused hda_tegra_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	पूर्णांक rc;

	rc = pm_runसमय_क्रमce_suspend(dev);
	अगर (rc < 0)
		वापस rc;
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused hda_tegra_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	पूर्णांक rc;

	rc = pm_runसमय_क्रमce_resume(dev);
	अगर (rc < 0)
		वापस rc;
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused hda_tegra_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा azx *chip = card->निजी_data;
	काष्ठा hda_tegra *hda = container_of(chip, काष्ठा hda_tegra, chip);

	अगर (chip && chip->running) अणु
		/* enable controller wake up event */
		azx_ग_लिखोw(chip, WAKEEN, azx_पढ़ोw(chip, WAKEEN) |
			   STATESTS_INT_MASK);

		azx_stop_chip(chip);
		azx_enter_link_reset(chip);
	पूर्ण
	clk_bulk_disable_unprepare(hda->nघड़ीs, hda->घड़ीs);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused hda_tegra_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा azx *chip = card->निजी_data;
	काष्ठा hda_tegra *hda = container_of(chip, काष्ठा hda_tegra, chip);
	पूर्णांक rc;

	अगर (!chip->running) अणु
		rc = reset_control_निश्चित(hda->reset);
		अगर (rc)
			वापस rc;
	पूर्ण

	rc = clk_bulk_prepare_enable(hda->nघड़ीs, hda->घड़ीs);
	अगर (rc != 0)
		वापस rc;
	अगर (chip->running) अणु
		hda_tegra_init(hda);
		azx_init_chip(chip, 1);
		/* disable controller wake up event*/
		azx_ग_लिखोw(chip, WAKEEN, azx_पढ़ोw(chip, WAKEEN) &
			   ~STATESTS_INT_MASK);
	पूर्ण अन्यथा अणु
		usleep_range(10, 100);

		rc = reset_control_deनिश्चित(hda->reset);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops hda_tegra_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(hda_tegra_suspend, hda_tegra_resume)
	SET_RUNTIME_PM_OPS(hda_tegra_runसमय_suspend,
			   hda_tegra_runसमय_resume,
			   शून्य)
पूर्ण;

अटल पूर्णांक hda_tegra_dev_disconnect(काष्ठा snd_device *device)
अणु
	काष्ठा azx *chip = device->device_data;

	chip->bus.shutकरोwn = 1;
	वापस 0;
पूर्ण

/*
 * deकाष्ठाor
 */
अटल पूर्णांक hda_tegra_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा azx *chip = device->device_data;
	काष्ठा hda_tegra *hda = container_of(chip, काष्ठा hda_tegra, chip);

	cancel_work_sync(&hda->probe_work);
	अगर (azx_bus(chip)->chip_init) अणु
		azx_stop_all_streams(chip);
		azx_stop_chip(chip);
	पूर्ण

	azx_मुक्त_stream_pages(chip);
	azx_मुक्त_streams(chip);
	snd_hdac_bus_निकास(azx_bus(chip));

	वापस 0;
पूर्ण

अटल पूर्णांक hda_tegra_init_chip(काष्ठा azx *chip, काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hda_tegra *hda = container_of(chip, काष्ठा hda_tegra, chip);
	काष्ठा hdac_bus *bus = azx_bus(chip);
	काष्ठा device *dev = hda->dev;
	काष्ठा resource *res;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	hda->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(hda->regs))
		वापस PTR_ERR(hda->regs);

	bus->remap_addr = hda->regs + HDA_BAR0;
	bus->addr = res->start + HDA_BAR0;

	hda_tegra_init(hda);

	वापस 0;
पूर्ण

अटल पूर्णांक hda_tegra_first_init(काष्ठा azx *chip, काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hda_tegra *hda = container_of(chip, काष्ठा hda_tegra, chip);
	काष्ठा hdac_bus *bus = azx_bus(chip);
	काष्ठा snd_card *card = chip->card;
	पूर्णांक err;
	अचिन्हित लघु gcap;
	पूर्णांक irq_id = platक्रमm_get_irq(pdev, 0);
	स्थिर अक्षर *sname, *drv_name = "tegra-hda";
	काष्ठा device_node *np = pdev->dev.of_node;

	err = hda_tegra_init_chip(chip, pdev);
	अगर (err)
		वापस err;

	err = devm_request_irq(chip->card->dev, irq_id, azx_पूर्णांकerrupt,
			     IRQF_SHARED, KBUILD_MODNAME, chip);
	अगर (err) अणु
		dev_err(chip->card->dev,
			"unable to request IRQ %d, disabling device\n",
			irq_id);
		वापस err;
	पूर्ण
	bus->irq = irq_id;
	bus->dma_stop_delay = 100;
	card->sync_irq = bus->irq;

	/*
	 * Tegra194 has 4 SDO lines and the STRIPE can be used to
	 * indicate how many of the SDO lines the stream should be
	 * striped. But GCAP रेजिस्टर करोes not reflect the true
	 * capability of HW. Below workaround helps to fix this.
	 *
	 * GCAP_NSDO is bits 19:18 in T_AZA_DBG_CFG_2,
	 * 0 क्रम 1 SDO, 1 क्रम 2 SDO, 2 क्रम 4 SDO lines.
	 */
	अगर (of_device_is_compatible(np, "nvidia,tegra194-hda")) अणु
		u32 val;

		dev_info(card->dev, "Override SDO lines to %u\n",
			 TEGRA194_NUM_SDO_LINES);

		val = पढ़ोl(hda->regs + FPCI_DBG_CFG_2) & ~FPCI_GCAP_NSDO_MASK;
		val |= (TEGRA194_NUM_SDO_LINES >> 1) << FPCI_GCAP_NSDO_SHIFT;
		ग_लिखोl(val, hda->regs + FPCI_DBG_CFG_2);
	पूर्ण

	gcap = azx_पढ़ोw(chip, GCAP);
	dev_dbg(card->dev, "chipset global capabilities = 0x%x\n", gcap);

	chip->align_buffer_size = 1;

	/* पढ़ो number of streams from GCAP रेजिस्टर instead of using
	 * hardcoded value
	 */
	chip->capture_streams = (gcap >> 8) & 0x0f;
	chip->playback_streams = (gcap >> 12) & 0x0f;
	अगर (!chip->playback_streams && !chip->capture_streams) अणु
		/* gcap didn't give any info, चयनing to old method */
		chip->playback_streams = NUM_PLAYBACK_SD;
		chip->capture_streams = NUM_CAPTURE_SD;
	पूर्ण
	chip->capture_index_offset = 0;
	chip->playback_index_offset = chip->capture_streams;
	chip->num_streams = chip->playback_streams + chip->capture_streams;

	/* initialize streams */
	err = azx_init_streams(chip);
	अगर (err < 0) अणु
		dev_err(card->dev, "failed to initialize streams: %d\n", err);
		वापस err;
	पूर्ण

	err = azx_alloc_stream_pages(chip);
	अगर (err < 0) अणु
		dev_err(card->dev, "failed to allocate stream pages: %d\n",
			err);
		वापस err;
	पूर्ण

	/* initialize chip */
	azx_init_chip(chip, 1);

	/*
	 * Playback (क्रम 44.1K/48K, 2-channel, 16-bps) fails with
	 * 4 SDO lines due to legacy design limitation. Following
	 * is, from HD Audio Specअगरication (Revision 1.0a), used to
	 * control striping of the stream across multiple SDO lines
	 * क्रम sample rates <= 48K.
	 *
	 * अणु ((num_channels * bits_per_sample) / number of SDOs) >= 8 पूर्ण
	 *
	 * Due to legacy design issue it is recommended that above
	 * ratio must be greater than 8. Since number of SDO lines is
	 * in घातers of 2, next available ratio is 16 which can be
	 * used as a limiting factor here.
	 */
	अगर (of_device_is_compatible(np, "nvidia,tegra30-hda"))
		chip->bus.core.sकरो_limit = 16;

	/* codec detection */
	अगर (!bus->codec_mask) अणु
		dev_err(card->dev, "no codecs found!\n");
		वापस -ENODEV;
	पूर्ण

	/* driver name */
	म_नकलन(card->driver, drv_name, माप(card->driver));
	/* लघुname क्रम card */
	sname = of_get_property(np, "nvidia,model", शून्य);
	अगर (!sname)
		sname = drv_name;
	अगर (म_माप(sname) > माप(card->लघुname))
		dev_info(card->dev, "truncating shortname for card\n");
	म_नकलन(card->लघुname, sname, माप(card->लघुname));

	/* दीर्घname क्रम card */
	snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
		 "%s at 0x%lx irq %i",
		 card->लघुname, bus->addr, bus->irq);

	वापस 0;
पूर्ण

/*
 * स्थिरructor
 */

अटल व्योम hda_tegra_probe_work(काष्ठा work_काष्ठा *work);

अटल पूर्णांक hda_tegra_create(काष्ठा snd_card *card,
			    अचिन्हित पूर्णांक driver_caps,
			    काष्ठा hda_tegra *hda)
अणु
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_disconnect = hda_tegra_dev_disconnect,
		.dev_मुक्त = hda_tegra_dev_मुक्त,
	पूर्ण;
	काष्ठा azx *chip;
	पूर्णांक err;

	chip = &hda->chip;

	mutex_init(&chip->खोलो_mutex);
	chip->card = card;
	chip->ops = &hda_tegra_ops;
	chip->driver_caps = driver_caps;
	chip->driver_type = driver_caps & 0xff;
	chip->dev_index = 0;
	INIT_LIST_HEAD(&chip->pcm_list);

	chip->codec_probe_mask = -1;

	chip->single_cmd = false;
	chip->snoop = true;

	INIT_WORK(&hda->probe_work, hda_tegra_probe_work);

	err = azx_bus_init(chip, शून्य);
	अगर (err < 0)
		वापस err;

	chip->bus.core.sync_ग_लिखो = 0;
	chip->bus.core.needs_damn_दीर्घ_delay = 1;
	chip->bus.core.aligned_mmio = 1;

	err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops);
	अगर (err < 0) अणु
		dev_err(card->dev, "Error creating device\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id hda_tegra_match[] = अणु
	अणु .compatible = "nvidia,tegra30-hda" पूर्ण,
	अणु .compatible = "nvidia,tegra194-hda" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, hda_tegra_match);

अटल पूर्णांक hda_tegra_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर अचिन्हित पूर्णांक driver_flags = AZX_DCAPS_CORBRP_SELF_CLEAR |
					  AZX_DCAPS_PM_RUNTIME;
	काष्ठा snd_card *card;
	काष्ठा azx *chip;
	काष्ठा hda_tegra *hda;
	पूर्णांक err;

	hda = devm_kzalloc(&pdev->dev, माप(*hda), GFP_KERNEL);
	अगर (!hda)
		वापस -ENOMEM;
	hda->dev = &pdev->dev;
	chip = &hda->chip;

	err = snd_card_new(&pdev->dev, SNDRV_DEFAULT_IDX1, SNDRV_DEFAULT_STR1,
			   THIS_MODULE, 0, &card);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "Error creating card!\n");
		वापस err;
	पूर्ण

	hda->reset = devm_reset_control_array_get_exclusive(&pdev->dev);
	अगर (IS_ERR(hda->reset)) अणु
		err = PTR_ERR(hda->reset);
		जाओ out_मुक्त;
	पूर्ण

	hda->घड़ीs[hda->nघड़ीs++].id = "hda";
	hda->घड़ीs[hda->nघड़ीs++].id = "hda2hdmi";
	hda->घड़ीs[hda->nघड़ीs++].id = "hda2codec_2x";

	err = devm_clk_bulk_get(&pdev->dev, hda->nघड़ीs, hda->घड़ीs);
	अगर (err < 0)
		जाओ out_मुक्त;

	err = hda_tegra_create(card, driver_flags, hda);
	अगर (err < 0)
		जाओ out_मुक्त;
	card->निजी_data = chip;

	dev_set_drvdata(&pdev->dev, card);

	pm_runसमय_enable(hda->dev);
	अगर (!azx_has_pm_runसमय(chip))
		pm_runसमय_क्रमbid(hda->dev);

	schedule_work(&hda->probe_work);

	वापस 0;

out_मुक्त:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल व्योम hda_tegra_probe_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hda_tegra *hda = container_of(work, काष्ठा hda_tegra, probe_work);
	काष्ठा azx *chip = &hda->chip;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(hda->dev);
	पूर्णांक err;

	pm_runसमय_get_sync(hda->dev);
	err = hda_tegra_first_init(chip, pdev);
	अगर (err < 0)
		जाओ out_मुक्त;

	/* create codec instances */
	err = azx_probe_codecs(chip, 8);
	अगर (err < 0)
		जाओ out_मुक्त;

	err = azx_codec_configure(chip);
	अगर (err < 0)
		जाओ out_मुक्त;

	err = snd_card_रेजिस्टर(chip->card);
	अगर (err < 0)
		जाओ out_मुक्त;

	chip->running = 1;
	snd_hda_set_घातer_save(&chip->bus, घातer_save * 1000);

 out_मुक्त:
	pm_runसमय_put(hda->dev);
	वापस; /* no error वापस from async probe */
पूर्ण

अटल पूर्णांक hda_tegra_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	ret = snd_card_मुक्त(dev_get_drvdata(&pdev->dev));
	pm_runसमय_disable(&pdev->dev);

	वापस ret;
पूर्ण

अटल व्योम hda_tegra_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(&pdev->dev);
	काष्ठा azx *chip;

	अगर (!card)
		वापस;
	chip = card->निजी_data;
	अगर (chip && chip->running)
		azx_stop_chip(chip);
पूर्ण

अटल काष्ठा platक्रमm_driver tegra_platक्रमm_hda = अणु
	.driver = अणु
		.name = "tegra-hda",
		.pm = &hda_tegra_pm,
		.of_match_table = hda_tegra_match,
	पूर्ण,
	.probe = hda_tegra_probe,
	.हटाओ = hda_tegra_हटाओ,
	.shutकरोwn = hda_tegra_shutकरोwn,
पूर्ण;
module_platक्रमm_driver(tegra_platक्रमm_hda);

MODULE_DESCRIPTION("Tegra HDA bus driver");
MODULE_LICENSE("GPL v2");
