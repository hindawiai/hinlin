<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * budget-core.c: driver क्रम the SAA7146 based Budget DVB cards
 *
 * Compiled from various sources by Michael Hunold <michael@mihu.de>
 *
 * Copyright (C) 2002 Ralph Metzler <rjkm@metzlerbros.de>
 *
 * Copyright (C) 1999-2002 Ralph  Metzler
 *			 & Marcus Metzler क्रम convergence पूर्णांकegrated media GmbH
 *
 * 26feb2004 Support क्रम FS Activy Card (Grundig tuner) by
 *	     Michael Dreher <michael@5करोt1.de>,
 *	     Oliver Endriss <o.endriss@gmx.de>,
 *	     Andreas 'randy' Weinberger
 *
 * the project's page is at https://linuxtv.org
 */


#समावेश "budget.h"
#समावेश "ttpci-eeprom.h"

#घोषणा TS_WIDTH		(2 * TS_SIZE)
#घोषणा TS_WIDTH_ACTIVY		TS_SIZE
#घोषणा TS_WIDTH_DVBC		TS_SIZE
#घोषणा TS_HEIGHT_MASK		0xf00
#घोषणा TS_HEIGHT_MASK_ACTIVY	0xc00
#घोषणा TS_HEIGHT_MASK_DVBC	0xe00
#घोषणा TS_MIN_बफ_मानE_K	188
#घोषणा TS_MAX_बफ_मानE_K	1410
#घोषणा TS_MAX_बफ_मानE_K_ACTIVY	564
#घोषणा TS_MAX_बफ_मानE_K_DVBC	1316
#घोषणा BUFFER_WARNING_WAIT	(30*HZ)

पूर्णांक budget_debug;
अटल पूर्णांक dma_buffer_size = TS_MIN_बफ_मानE_K;
module_param_named(debug, budget_debug, पूर्णांक, 0644);
module_param_named(bufsize, dma_buffer_size, पूर्णांक, 0444);
MODULE_PARM_DESC(debug, "Turn on/off budget debugging (default:off).");
MODULE_PARM_DESC(bufsize, "DMA buffer size in KB, default: 188, min: 188, max: 1410 (Activy: 564)");

/****************************************************************************
 * TT budget / WinTV Nova
 ****************************************************************************/

अटल पूर्णांक stop_ts_capture(काष्ठा budget *budget)
अणु
	dprपूर्णांकk(2, "budget: %p\n", budget);

	saa7146_ग_लिखो(budget->dev, MC1, MASK_20);	// DMA3 off
	SAA7146_IER_DISABLE(budget->dev, MASK_10);
	वापस 0;
पूर्ण

अटल पूर्णांक start_ts_capture(काष्ठा budget *budget)
अणु
	काष्ठा saa7146_dev *dev = budget->dev;

	dprपूर्णांकk(2, "budget: %p\n", budget);

	अगर (!budget->feeding || !budget->fe_synced)
		वापस 0;

	saa7146_ग_लिखो(dev, MC1, MASK_20);	// DMA3 off

	स_रखो(budget->grabbing, 0x00, budget->buffer_size);

	saa7146_ग_लिखो(dev, PCI_BT_V1, 0x001c0000 | (saa7146_पढ़ो(dev, PCI_BT_V1) & ~0x001f0000));

	budget->ttbp = 0;

	/*
	 *  Signal path on the Activy:
	 *
	 *  tuner -> SAA7146 port A -> SAA7146 BRS -> SAA7146 DMA3 -> memory
	 *
	 *  Since the tuner feeds 204 bytes packets पूर्णांकo the SAA7146,
	 *  DMA3 is configured to strip the trailing 16 FEC bytes:
	 *      Pitch: 188, NumBytes3: 188, NumLines3: 1024
	 */

	चयन(budget->card->type) अणु
	हाल BUDGET_FS_ACTIVY:
		saa7146_ग_लिखो(dev, DD1_INIT, 0x04000000);
		saa7146_ग_लिखो(dev, MC2, (MASK_09 | MASK_25));
		saa7146_ग_लिखो(dev, BRS_CTRL, 0x00000000);
		अवरोध;
	हाल BUDGET_PATCH:
		saa7146_ग_लिखो(dev, DD1_INIT, 0x00000200);
		saa7146_ग_लिखो(dev, MC2, (MASK_10 | MASK_26));
		saa7146_ग_लिखो(dev, BRS_CTRL, 0x60000000);
		अवरोध;
	हाल BUDGET_CIN1200C_MK3:
	हाल BUDGET_KNC1C_MK3:
	हाल BUDGET_KNC1C_TDA10024:
	हाल BUDGET_KNC1CP_MK3:
		अगर (budget->video_port == BUDGET_VIDEO_PORTA) अणु
			saa7146_ग_लिखो(dev, DD1_INIT, 0x06000200);
			saa7146_ग_लिखो(dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));
			saa7146_ग_लिखो(dev, BRS_CTRL, 0x00000000);
		पूर्ण अन्यथा अणु
			saa7146_ग_लिखो(dev, DD1_INIT, 0x00000600);
			saa7146_ग_लिखो(dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));
			saa7146_ग_लिखो(dev, BRS_CTRL, 0x60000000);
		पूर्ण
		अवरोध;
	शेष:
		अगर (budget->video_port == BUDGET_VIDEO_PORTA) अणु
			saa7146_ग_लिखो(dev, DD1_INIT, 0x06000200);
			saa7146_ग_लिखो(dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));
			saa7146_ग_लिखो(dev, BRS_CTRL, 0x00000000);
		पूर्ण अन्यथा अणु
			saa7146_ग_लिखो(dev, DD1_INIT, 0x02000600);
			saa7146_ग_लिखो(dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));
			saa7146_ग_लिखो(dev, BRS_CTRL, 0x60000000);
		पूर्ण
	पूर्ण

	saa7146_ग_लिखो(dev, MC2, (MASK_08 | MASK_24));
	mdelay(10);

	saa7146_ग_लिखो(dev, BASE_ODD3, 0);
	अगर (budget->buffer_size > budget->buffer_height * budget->buffer_width) अणु
		// using odd/even buffers
		saa7146_ग_लिखो(dev, BASE_EVEN3, budget->buffer_height * budget->buffer_width);
	पूर्ण अन्यथा अणु
		// using a single buffer
		saa7146_ग_लिखो(dev, BASE_EVEN3, 0);
	पूर्ण
	saa7146_ग_लिखो(dev, PROT_ADDR3, budget->buffer_size);
	saa7146_ग_लिखो(dev, BASE_PAGE3, budget->pt.dma | ME1 | 0x90);

	saa7146_ग_लिखो(dev, PITCH3, budget->buffer_width);
	saa7146_ग_लिखो(dev, NUM_LINE_BYTE3,
			(budget->buffer_height << 16) | budget->buffer_width);

	saa7146_ग_लिखो(dev, MC2, (MASK_04 | MASK_20));

	SAA7146_ISR_CLEAR(budget->dev, MASK_10);	/* VPE */
	SAA7146_IER_ENABLE(budget->dev, MASK_10);	/* VPE */
	saa7146_ग_लिखो(dev, MC1, (MASK_04 | MASK_20));	/* DMA3 on */

	वापस 0;
पूर्ण

अटल पूर्णांक budget_पढ़ो_fe_status(काष्ठा dvb_frontend *fe,
				 क्रमागत fe_status *status)
अणु
	काष्ठा budget *budget = (काष्ठा budget *) fe->dvb->priv;
	पूर्णांक synced;
	पूर्णांक ret;

	अगर (budget->पढ़ो_fe_status)
		ret = budget->पढ़ो_fe_status(fe, status);
	अन्यथा
		ret = -EINVAL;

	अगर (!ret) अणु
		synced = (*status & FE_HAS_LOCK);
		अगर (synced != budget->fe_synced) अणु
			budget->fe_synced = synced;
			spin_lock(&budget->feedlock);
			अगर (synced)
				start_ts_capture(budget);
			अन्यथा
				stop_ts_capture(budget);
			spin_unlock(&budget->feedlock);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम vpeirq(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा budget *budget = from_tasklet(budget, t, vpe_tasklet);
	u8 *mem = (u8 *) (budget->grabbing);
	u32 olddma = budget->ttbp;
	u32 newdma = saa7146_पढ़ो(budget->dev, PCI_VDP3);
	u32 count;

	/* Ensure streamed PCI data is synced to CPU */
	pci_dma_sync_sg_क्रम_cpu(budget->dev->pci, budget->pt.slist, budget->pt.nents, PCI_DMA_FROMDEVICE);

	/* nearest lower position भागisible by 188 */
	newdma -= newdma % 188;

	अगर (newdma >= budget->buffer_size)
		वापस;

	budget->ttbp = newdma;

	अगर (budget->feeding == 0 || newdma == olddma)
		वापस;

	अगर (newdma > olddma) अणु	/* no wraparound, dump olddma..newdma */
		count = newdma - olddma;
		dvb_dmx_swfilter_packets(&budget->demux, mem + olddma, count / 188);
	पूर्ण अन्यथा अणु		/* wraparound, dump olddma..buflen and 0..newdma */
		count = budget->buffer_size - olddma;
		dvb_dmx_swfilter_packets(&budget->demux, mem + olddma, count / 188);
		count += newdma;
		dvb_dmx_swfilter_packets(&budget->demux, mem, newdma / 188);
	पूर्ण

	अगर (count > budget->buffer_warning_threshold)
		budget->buffer_warnings++;

	अगर (budget->buffer_warnings && समय_after(jअगरfies, budget->buffer_warning_समय)) अणु
		prपूर्णांकk("%s %s: used %d times >80%% of buffer (%u bytes now)\n",
			budget->dev->name, __func__, budget->buffer_warnings, count);
		budget->buffer_warning_समय = jअगरfies + BUFFER_WARNING_WAIT;
		budget->buffer_warnings = 0;
	पूर्ण
पूर्ण


अटल पूर्णांक ttpci_budget_debiपढ़ो_nolock(काष्ठा budget *budget, u32 config,
		पूर्णांक addr, पूर्णांक count, पूर्णांक nobusyloop)
अणु
	काष्ठा saa7146_dev *saa = budget->dev;
	पूर्णांक result;

	result = saa7146_रुको_क्रम_debi_करोne(saa, nobusyloop);
	अगर (result < 0)
		वापस result;

	saa7146_ग_लिखो(saa, DEBI_COMMAND, (count << 17) | 0x10000 | (addr & 0xffff));
	saa7146_ग_लिखो(saa, DEBI_CONFIG, config);
	saa7146_ग_लिखो(saa, DEBI_PAGE, 0);
	saa7146_ग_लिखो(saa, MC2, (2 << 16) | 2);

	result = saa7146_रुको_क्रम_debi_करोne(saa, nobusyloop);
	अगर (result < 0)
		वापस result;

	result = saa7146_पढ़ो(saa, DEBI_AD);
	result &= (0xffffffffUL >> ((4 - count) * 8));
	वापस result;
पूर्ण

पूर्णांक ttpci_budget_debiपढ़ो(काष्ठा budget *budget, u32 config, पूर्णांक addr, पूर्णांक count,
			  पूर्णांक uselocks, पूर्णांक nobusyloop)
अणु
	अगर (count > 4 || count <= 0)
		वापस 0;

	अगर (uselocks) अणु
		अचिन्हित दीर्घ flags;
		पूर्णांक result;

		spin_lock_irqsave(&budget->debilock, flags);
		result = ttpci_budget_debiपढ़ो_nolock(budget, config, addr,
						      count, nobusyloop);
		spin_unlock_irqrestore(&budget->debilock, flags);
		वापस result;
	पूर्ण
	वापस ttpci_budget_debiपढ़ो_nolock(budget, config, addr,
					    count, nobusyloop);
पूर्ण

अटल पूर्णांक ttpci_budget_debiग_लिखो_nolock(काष्ठा budget *budget, u32 config,
		पूर्णांक addr, पूर्णांक count, u32 value, पूर्णांक nobusyloop)
अणु
	काष्ठा saa7146_dev *saa = budget->dev;
	पूर्णांक result;

	result = saa7146_रुको_क्रम_debi_करोne(saa, nobusyloop);
	अगर (result < 0)
		वापस result;

	saa7146_ग_लिखो(saa, DEBI_COMMAND, (count << 17) | 0x00000 | (addr & 0xffff));
	saa7146_ग_लिखो(saa, DEBI_CONFIG, config);
	saa7146_ग_लिखो(saa, DEBI_PAGE, 0);
	saa7146_ग_लिखो(saa, DEBI_AD, value);
	saa7146_ग_लिखो(saa, MC2, (2 << 16) | 2);

	result = saa7146_रुको_क्रम_debi_करोne(saa, nobusyloop);
	वापस result < 0 ? result : 0;
पूर्ण

पूर्णांक ttpci_budget_debiग_लिखो(काष्ठा budget *budget, u32 config, पूर्णांक addr,
			   पूर्णांक count, u32 value, पूर्णांक uselocks, पूर्णांक nobusyloop)
अणु
	अगर (count > 4 || count <= 0)
		वापस 0;

	अगर (uselocks) अणु
		अचिन्हित दीर्घ flags;
		पूर्णांक result;

		spin_lock_irqsave(&budget->debilock, flags);
		result = ttpci_budget_debiग_लिखो_nolock(budget, config, addr,
						count, value, nobusyloop);
		spin_unlock_irqrestore(&budget->debilock, flags);
		वापस result;
	पूर्ण
	वापस ttpci_budget_debiग_लिखो_nolock(budget, config, addr,
					     count, value, nobusyloop);
पूर्ण


/****************************************************************************
 * DVB API SECTION
 ****************************************************************************/

अटल पूर्णांक budget_start_feed(काष्ठा dvb_demux_feed *feed)
अणु
	काष्ठा dvb_demux *demux = feed->demux;
	काष्ठा budget *budget = (काष्ठा budget *) demux->priv;
	पूर्णांक status = 0;

	dprपूर्णांकk(2, "budget: %p\n", budget);

	अगर (!demux->dmx.frontend)
		वापस -EINVAL;

	spin_lock(&budget->feedlock);
	feed->pusi_seen = false; /* have a clean section start */
	अगर (budget->feeding++ == 0)
		status = start_ts_capture(budget);
	spin_unlock(&budget->feedlock);
	वापस status;
पूर्ण

अटल पूर्णांक budget_stop_feed(काष्ठा dvb_demux_feed *feed)
अणु
	काष्ठा dvb_demux *demux = feed->demux;
	काष्ठा budget *budget = (काष्ठा budget *) demux->priv;
	पूर्णांक status = 0;

	dprपूर्णांकk(2, "budget: %p\n", budget);

	spin_lock(&budget->feedlock);
	अगर (--budget->feeding == 0)
		status = stop_ts_capture(budget);
	spin_unlock(&budget->feedlock);
	वापस status;
पूर्ण

अटल पूर्णांक budget_रेजिस्टर(काष्ठा budget *budget)
अणु
	काष्ठा dvb_demux *dvbdemux = &budget->demux;
	पूर्णांक ret;

	dprपूर्णांकk(2, "budget: %p\n", budget);

	dvbdemux->priv = (व्योम *) budget;

	dvbdemux->filternum = 256;
	dvbdemux->feednum = 256;
	dvbdemux->start_feed = budget_start_feed;
	dvbdemux->stop_feed = budget_stop_feed;
	dvbdemux->ग_लिखो_to_decoder = शून्य;

	dvbdemux->dmx.capabilities = (DMX_TS_FILTERING | DMX_SECTION_FILTERING |
				      DMX_MEMORY_BASED_FILTERING);

	dvb_dmx_init(&budget->demux);

	budget->dmxdev.filternum = 256;
	budget->dmxdev.demux = &dvbdemux->dmx;
	budget->dmxdev.capabilities = 0;

	dvb_dmxdev_init(&budget->dmxdev, &budget->dvb_adapter);

	budget->hw_frontend.source = DMX_FRONTEND_0;

	ret = dvbdemux->dmx.add_frontend(&dvbdemux->dmx, &budget->hw_frontend);

	अगर (ret < 0)
		जाओ err_release_dmx;

	budget->mem_frontend.source = DMX_MEMORY_FE;
	ret = dvbdemux->dmx.add_frontend(&dvbdemux->dmx, &budget->mem_frontend);
	अगर (ret < 0)
		जाओ err_release_dmx;

	ret = dvbdemux->dmx.connect_frontend(&dvbdemux->dmx, &budget->hw_frontend);
	अगर (ret < 0)
		जाओ err_release_dmx;

	dvb_net_init(&budget->dvb_adapter, &budget->dvb_net, &dvbdemux->dmx);

	वापस 0;

err_release_dmx:
	dvb_dmxdev_release(&budget->dmxdev);
	dvb_dmx_release(&budget->demux);
	वापस ret;
पूर्ण

अटल व्योम budget_unरेजिस्टर(काष्ठा budget *budget)
अणु
	काष्ठा dvb_demux *dvbdemux = &budget->demux;

	dprपूर्णांकk(2, "budget: %p\n", budget);

	dvb_net_release(&budget->dvb_net);

	dvbdemux->dmx.बंद(&dvbdemux->dmx);
	dvbdemux->dmx.हटाओ_frontend(&dvbdemux->dmx, &budget->hw_frontend);
	dvbdemux->dmx.हटाओ_frontend(&dvbdemux->dmx, &budget->mem_frontend);

	dvb_dmxdev_release(&budget->dmxdev);
	dvb_dmx_release(&budget->demux);
पूर्ण

पूर्णांक ttpci_budget_init(काष्ठा budget *budget, काष्ठा saa7146_dev *dev,
		      काष्ठा saa7146_pci_extension_data *info,
		      काष्ठा module *owner, लघु *adapter_nums)
अणु
	पूर्णांक ret = 0;
	काष्ठा budget_info *bi = info->ext_priv;
	पूर्णांक max_bufsize;
	पूर्णांक height_mask;

	स_रखो(budget, 0, माप(काष्ठा budget));

	dprपूर्णांकk(2, "dev: %p, budget: %p\n", dev, budget);

	budget->card = bi;
	budget->dev = (काष्ठा saa7146_dev *) dev;

	चयन(budget->card->type) अणु
	हाल BUDGET_FS_ACTIVY:
		budget->buffer_width = TS_WIDTH_ACTIVY;
		max_bufsize = TS_MAX_बफ_मानE_K_ACTIVY;
		height_mask = TS_HEIGHT_MASK_ACTIVY;
		अवरोध;

	हाल BUDGET_KNC1C:
	हाल BUDGET_KNC1CP:
	हाल BUDGET_CIN1200C:
	हाल BUDGET_KNC1C_MK3:
	हाल BUDGET_KNC1C_TDA10024:
	हाल BUDGET_KNC1CP_MK3:
	हाल BUDGET_CIN1200C_MK3:
		budget->buffer_width = TS_WIDTH_DVBC;
		max_bufsize = TS_MAX_बफ_मानE_K_DVBC;
		height_mask = TS_HEIGHT_MASK_DVBC;
		अवरोध;

	शेष:
		budget->buffer_width = TS_WIDTH;
		max_bufsize = TS_MAX_बफ_मानE_K;
		height_mask = TS_HEIGHT_MASK;
	पूर्ण

	अगर (dma_buffer_size < TS_MIN_बफ_मानE_K)
		dma_buffer_size = TS_MIN_बफ_मानE_K;
	अन्यथा अगर (dma_buffer_size > max_bufsize)
		dma_buffer_size = max_bufsize;

	budget->buffer_height = dma_buffer_size * 1024 / budget->buffer_width;
	अगर (budget->buffer_height > 0xfff) अणु
		budget->buffer_height /= 2;
		budget->buffer_height &= height_mask;
		budget->buffer_size = 2 * budget->buffer_height * budget->buffer_width;
	पूर्ण अन्यथा अणु
		budget->buffer_height &= height_mask;
		budget->buffer_size = budget->buffer_height * budget->buffer_width;
	पूर्ण
	budget->buffer_warning_threshold = budget->buffer_size * 80/100;
	budget->buffer_warnings = 0;
	budget->buffer_warning_समय = jअगरfies;

	dprपूर्णांकk(2, "%s: buffer type = %s, width = %d, height = %d\n",
		budget->dev->name,
		budget->buffer_size > budget->buffer_width * budget->buffer_height ? "odd/even" : "single",
		budget->buffer_width, budget->buffer_height);
	prपूर्णांकk("%s: dma buffer size %u\n", budget->dev->name, budget->buffer_size);

	ret = dvb_रेजिस्टर_adapter(&budget->dvb_adapter, budget->card->name,
				   owner, &budget->dev->pci->dev, adapter_nums);
	अगर (ret < 0)
		वापस ret;

	/* set dd1 stream a & b */
	saa7146_ग_लिखो(dev, DD1_STREAM_B, 0x00000000);
	saa7146_ग_लिखो(dev, MC2, (MASK_09 | MASK_25));
	saa7146_ग_लिखो(dev, MC2, (MASK_10 | MASK_26));
	saa7146_ग_लिखो(dev, DD1_INIT, 0x02000000);
	saa7146_ग_लिखो(dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));

	अगर (bi->type != BUDGET_FS_ACTIVY)
		budget->video_port = BUDGET_VIDEO_PORTB;
	अन्यथा
		budget->video_port = BUDGET_VIDEO_PORTA;
	spin_lock_init(&budget->feedlock);
	spin_lock_init(&budget->debilock);

	/* the Siemens DVB needs this अगर you want to have the i2c chips
	   get recognized beक्रमe the मुख्य driver is loaded */
	अगर (bi->type != BUDGET_FS_ACTIVY)
		saa7146_ग_लिखो(dev, GPIO_CTRL, 0x500000);	/* GPIO 3 = 1 */

	strscpy(budget->i2c_adap.name, budget->card->name,
		माप(budget->i2c_adap.name));

	saa7146_i2c_adapter_prepare(dev, &budget->i2c_adap, SAA7146_I2C_BUS_BIT_RATE_120);
	strscpy(budget->i2c_adap.name, budget->card->name,
		माप(budget->i2c_adap.name));

	अगर (i2c_add_adapter(&budget->i2c_adap) < 0) अणु
		ret = -ENOMEM;
		जाओ err_dvb_unरेजिस्टर;
	पूर्ण

	ttpci_eeprom_parse_mac(&budget->i2c_adap, budget->dvb_adapter.proposed_mac);

	budget->grabbing = saa7146_vदो_स्मृति_build_pgtable(dev->pci, budget->buffer_size, &budget->pt);
	अगर (शून्य == budget->grabbing) अणु
		ret = -ENOMEM;
		जाओ err_del_i2c;
	पूर्ण

	saa7146_ग_लिखो(dev, PCI_BT_V1, 0x001c0000);
	/* upload all */
	saa7146_ग_लिखो(dev, GPIO_CTRL, 0x000000);

	tasklet_setup(&budget->vpe_tasklet, vpeirq);

	/* frontend घातer on */
	अगर (bi->type != BUDGET_FS_ACTIVY)
		saa7146_setgpio(dev, 2, SAA7146_GPIO_OUTHI);

	अगर ((ret = budget_रेजिस्टर(budget)) == 0)
		वापस 0; /* Everything OK */

	/* An error occurred, cleanup resources */
	saa7146_vमुक्त_destroy_pgtable(dev->pci, budget->grabbing, &budget->pt);

err_del_i2c:
	i2c_del_adapter(&budget->i2c_adap);

err_dvb_unरेजिस्टर:
	dvb_unरेजिस्टर_adapter(&budget->dvb_adapter);

	वापस ret;
पूर्ण

व्योम ttpci_budget_init_hooks(काष्ठा budget *budget)
अणु
	अगर (budget->dvb_frontend && !budget->पढ़ो_fe_status) अणु
		budget->पढ़ो_fe_status = budget->dvb_frontend->ops.पढ़ो_status;
		budget->dvb_frontend->ops.पढ़ो_status = budget_पढ़ो_fe_status;
	पूर्ण
पूर्ण

पूर्णांक ttpci_budget_deinit(काष्ठा budget *budget)
अणु
	काष्ठा saa7146_dev *dev = budget->dev;

	dprपूर्णांकk(2, "budget: %p\n", budget);

	budget_unरेजिस्टर(budget);

	tasklet_समाप्त(&budget->vpe_tasklet);

	saa7146_vमुक्त_destroy_pgtable(dev->pci, budget->grabbing, &budget->pt);

	i2c_del_adapter(&budget->i2c_adap);

	dvb_unरेजिस्टर_adapter(&budget->dvb_adapter);

	वापस 0;
पूर्ण

व्योम ttpci_budget_irq10_handler(काष्ठा saa7146_dev *dev, u32 * isr)
अणु
	काष्ठा budget *budget = (काष्ठा budget *) dev->ext_priv;

	dprपूर्णांकk(8, "dev: %p, budget: %p\n", dev, budget);

	अगर (*isr & MASK_10)
		tasklet_schedule(&budget->vpe_tasklet);
पूर्ण

व्योम ttpci_budget_set_video_port(काष्ठा saa7146_dev *dev, पूर्णांक video_port)
अणु
	काष्ठा budget *budget = (काष्ठा budget *) dev->ext_priv;

	spin_lock(&budget->feedlock);
	budget->video_port = video_port;
	अगर (budget->feeding) अणु
		stop_ts_capture(budget);
		start_ts_capture(budget);
	पूर्ण
	spin_unlock(&budget->feedlock);
पूर्ण

EXPORT_SYMBOL_GPL(ttpci_budget_debiपढ़ो);
EXPORT_SYMBOL_GPL(ttpci_budget_debiग_लिखो);
EXPORT_SYMBOL_GPL(ttpci_budget_init);
EXPORT_SYMBOL_GPL(ttpci_budget_init_hooks);
EXPORT_SYMBOL_GPL(ttpci_budget_deinit);
EXPORT_SYMBOL_GPL(ttpci_budget_irq10_handler);
EXPORT_SYMBOL_GPL(ttpci_budget_set_video_port);
EXPORT_SYMBOL_GPL(budget_debug);

MODULE_LICENSE("GPL");
