<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Bt8xx based DVB adapter driver
 *
 * Copyright (C) 2002,2003 Florian Schirmer <jolt@tuxbox.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/bitops.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>

#समावेश <media/dmxdev.h>
#समावेश <media/dvbdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>
#समावेश "dvb-bt8xx.h"
#समावेश "bt878.h"

अटल पूर्णांक debug;

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off debugging (default:off).");

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

#घोषणा dprपूर्णांकk(fmt, arg...) करो अणु				\
	अगर (debug)						\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: " fmt),		\
		       __func__, ##arg);			\
पूर्ण जबतक (0)


#घोषणा IF_FREQUENCYx6 217    /* 6 * 36.16666666667MHz */

अटल व्योम dvb_bt8xx_task(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा bt878 *bt = from_tasklet(bt, t, tasklet);
	काष्ठा dvb_bt8xx_card *card = dev_get_drvdata(&bt->adapter->dev);

	dprपूर्णांकk("%d\n", card->bt->finished_block);

	जबतक (card->bt->last_block != card->bt->finished_block) अणु
		(card->bt->TS_Size ? dvb_dmx_swfilter_204 : dvb_dmx_swfilter)
			(&card->demux,
			 &card->bt->buf_cpu[card->bt->last_block *
					    card->bt->block_bytes],
			 card->bt->block_bytes);
		card->bt->last_block = (card->bt->last_block + 1) %
					card->bt->block_count;
	पूर्ण
पूर्ण

अटल पूर्णांक dvb_bt8xx_start_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	काष्ठा dvb_demux*dvbdmx = dvbdmxfeed->demux;
	काष्ठा dvb_bt8xx_card *card = dvbdmx->priv;
	पूर्णांक rc;

	dprपूर्णांकk("dvb_bt8xx: start_feed\n");

	अगर (!dvbdmx->dmx.frontend)
		वापस -EINVAL;

	mutex_lock(&card->lock);
	card->nfeeds++;
	rc = card->nfeeds;
	अगर (card->nfeeds == 1)
		bt878_start(card->bt, card->gpio_mode,
			    card->op_sync_orin, card->irq_err_ignore);
	mutex_unlock(&card->lock);
	वापस rc;
पूर्ण

अटल पूर्णांक dvb_bt8xx_stop_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	काष्ठा dvb_demux *dvbdmx = dvbdmxfeed->demux;
	काष्ठा dvb_bt8xx_card *card = dvbdmx->priv;

	dprपूर्णांकk("dvb_bt8xx: stop_feed\n");

	अगर (!dvbdmx->dmx.frontend)
		वापस -EINVAL;

	mutex_lock(&card->lock);
	card->nfeeds--;
	अगर (card->nfeeds == 0)
		bt878_stop(card->bt);
	mutex_unlock(&card->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक is_pci_slot_eq(काष्ठा pci_dev* adev, काष्ठा pci_dev* bdev)
अणु
	अगर ((adev->subप्रणाली_venकरोr == bdev->subप्रणाली_venकरोr) &&
		(adev->subप्रणाली_device == bdev->subप्रणाली_device) &&
		(adev->bus->number == bdev->bus->number) &&
		(PCI_SLOT(adev->devfn) == PCI_SLOT(bdev->devfn)))
		वापस 1;
	वापस 0;
पूर्ण

अटल काष्ठा bt878 *dvb_bt8xx_878_match(अचिन्हित पूर्णांक bttv_nr,
					 काष्ठा pci_dev* bttv_pci_dev)
अणु
	अचिन्हित पूर्णांक card_nr;

	/* Hmm, n squared. Hope n is small */
	क्रम (card_nr = 0; card_nr < bt878_num; card_nr++)
		अगर (is_pci_slot_eq(bt878[card_nr].dev, bttv_pci_dev))
			वापस &bt878[card_nr];
	वापस शून्य;
पूर्ण

अटल पूर्णांक thomson_dtt7579_demod_init(काष्ठा dvb_frontend* fe)
अणु
	अटल u8 mt352_घड़ी_config [] = अणु 0x89, 0x38, 0x38 पूर्ण;
	अटल u8 mt352_reset [] = अणु 0x50, 0x80 पूर्ण;
	अटल u8 mt352_adc_ctl_1_cfg [] = अणु 0x8E, 0x40 पूर्ण;
	अटल u8 mt352_agc_cfg [] = अणु 0x67, 0x28, 0x20 पूर्ण;
	अटल u8 mt352_gpp_ctl_cfg [] = अणु 0x8C, 0x33 पूर्ण;
	अटल u8 mt352_capt_range_cfg[] = अणु 0x75, 0x32 पूर्ण;

	mt352_ग_लिखो(fe, mt352_घड़ी_config, माप(mt352_घड़ी_config));
	udelay(2000);
	mt352_ग_लिखो(fe, mt352_reset, माप(mt352_reset));
	mt352_ग_लिखो(fe, mt352_adc_ctl_1_cfg, माप(mt352_adc_ctl_1_cfg));

	mt352_ग_लिखो(fe, mt352_agc_cfg, माप(mt352_agc_cfg));
	mt352_ग_लिखो(fe, mt352_gpp_ctl_cfg, माप(mt352_gpp_ctl_cfg));
	mt352_ग_लिखो(fe, mt352_capt_range_cfg, माप(mt352_capt_range_cfg));

	वापस 0;
पूर्ण

अटल पूर्णांक thomson_dtt7579_tuner_calc_regs(काष्ठा dvb_frontend *fe, u8* pllbuf, पूर्णांक buf_len)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 भाग;
	अचिन्हित अक्षर bs = 0;
	अचिन्हित अक्षर cp = 0;

	अगर (buf_len < 5)
		वापस -EINVAL;

	भाग = (((c->frequency + 83333) * 3) / 500000) + IF_FREQUENCYx6;

	अगर (c->frequency < 542000000)
		cp = 0xb4;
	अन्यथा अगर (c->frequency < 771000000)
		cp = 0xbc;
	अन्यथा
		cp = 0xf4;

	अगर (c->frequency == 0)
		bs = 0x03;
	अन्यथा अगर (c->frequency < 443250000)
		bs = 0x02;
	अन्यथा
		bs = 0x08;

	pllbuf[0] = 0x60;
	pllbuf[1] = भाग >> 8;
	pllbuf[2] = भाग & 0xff;
	pllbuf[3] = cp;
	pllbuf[4] = bs;

	वापस 5;
पूर्ण

अटल काष्ठा mt352_config thomson_dtt7579_config = अणु
	.demod_address = 0x0f,
	.demod_init = thomson_dtt7579_demod_init,
पूर्ण;

अटल काष्ठा zl10353_config thomson_dtt7579_zl10353_config = अणु
	.demod_address = 0x0f,
पूर्ण;

अटल पूर्णांक cx24108_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 freq = c->frequency;
	पूर्णांक i, a, n, pump;
	u32 band, pll;
	u32 osci[]=अणु950000,1019000,1075000,1178000,1296000,1432000,
		1576000,1718000,1856000,2036000,2150000पूर्ण;
	u32 bandsel[]=अणु0,0x00020000,0x00040000,0x00100800,0x00101000,
		0x00102000,0x00104000,0x00108000,0x00110000,
		0x00120000,0x00140000पूर्ण;

	#घोषणा XTAL 1011100 /* Hz, really 1.0111 MHz and a /10 prescaler */
	dprपूर्णांकk("cx24108 debug: entering SetTunerFreq, freq=%d\n", freq);

	/* This is really the bit driving the tuner chip cx24108 */

	अगर (freq<950000)
		freq = 950000; /* kHz */
	अन्यथा अगर (freq>2150000)
		freq = 2150000; /* satellite IF is 950..2150MHz */

	/* decide which VCO to use क्रम the input frequency */
	क्रम(i = 1; (i < ARRAY_SIZE(osci) - 1) && (osci[i] < freq); i++);
	dprपूर्णांकk("cx24108 debug: select vco #%d (f=%d)\n", i, freq);
	band=bandsel[i];
	/* the gain values must be set by SetSymbolrate */
	/* compute the pll भागider needed, from Conexant data sheet,
	   resolved क्रम (n*32+a), remember f(vco) is f(receive) *2 or *4,
	   depending on the भागider bit. It is set to /4 on the 2 lowest
	   bands  */
	n=((i<=2?2:1)*freq*10L)/(XTAL/100);
	a=n%32; n/=32; अगर(a==0) n--;
	pump=(freq<(osci[i-1]+osci[i])/2);
	pll=0xf8000000|
	    ((pump?1:2)<<(14+11))|
	    ((n&0x1ff)<<(5+11))|
	    ((a&0x1f)<<11);
	/* everything is shअगरted left 11 bits to left-align the bits in the
	   32bit word. Output to the tuner goes MSB-aligned, after all */
	dprपूर्णांकk("cx24108 debug: pump=%d, n=%d, a=%d\n", pump, n, a);
	cx24110_pll_ग_लिखो(fe,band);
	/* set vga and vca to their widest-band settings, as a precaution.
	   SetSymbolrate might not be called to set this up */
	cx24110_pll_ग_लिखो(fe,0x500c0000);
	cx24110_pll_ग_लिखो(fe,0x83f1f800);
	cx24110_pll_ग_लिखो(fe,pll);
	//ग_लिखोreg(client,0x56,0x7f);

	वापस 0;
पूर्ण

अटल पूर्णांक pinnsat_tuner_init(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा dvb_bt8xx_card *card = fe->dvb->priv;

	bttv_gpio_enable(card->bttv_nr, 1, 1);  /* output */
	bttv_ग_लिखो_gpio(card->bttv_nr, 1, 1);   /* relay on */

	वापस 0;
पूर्ण

अटल पूर्णांक pinnsat_tuner_sleep(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा dvb_bt8xx_card *card = fe->dvb->priv;

	bttv_ग_लिखो_gpio(card->bttv_nr, 1, 0);   /* relay off */

	वापस 0;
पूर्ण

अटल काष्ठा cx24110_config pctvsat_config = अणु
	.demod_address = 0x55,
पूर्ण;

अटल पूर्णांक microtune_mt7202dtf_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा dvb_bt8xx_card *card = (काष्ठा dvb_bt8xx_card *) fe->dvb->priv;
	u8 cfg, cpump, band_select;
	u8 data[4];
	u32 भाग;
	काष्ठा i2c_msg msg = अणु .addr = 0x60, .flags = 0, .buf = data, .len = माप(data) पूर्ण;

	भाग = (36000000 + c->frequency + 83333) / 166666;
	cfg = 0x88;

	अगर (c->frequency < 175000000)
		cpump = 2;
	अन्यथा अगर (c->frequency < 390000000)
		cpump = 1;
	अन्यथा अगर (c->frequency < 470000000)
		cpump = 2;
	अन्यथा अगर (c->frequency < 750000000)
		cpump = 2;
	अन्यथा
		cpump = 3;

	अगर (c->frequency < 175000000)
		band_select = 0x0e;
	अन्यथा अगर (c->frequency < 470000000)
		band_select = 0x05;
	अन्यथा
		band_select = 0x03;

	data[0] = (भाग >> 8) & 0x7f;
	data[1] = भाग & 0xff;
	data[2] = ((भाग >> 10) & 0x60) | cfg;
	data[3] = (cpump << 6) | band_select;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	i2c_transfer(card->i2c_adapter, &msg, 1);
	वापस (भाग * 166666 - 36000000);
पूर्ण

अटल पूर्णांक microtune_mt7202dtf_request_firmware(काष्ठा dvb_frontend* fe, स्थिर काष्ठा firmware **fw, अक्षर* name)
अणु
	काष्ठा dvb_bt8xx_card* bt = (काष्ठा dvb_bt8xx_card*) fe->dvb->priv;

	वापस request_firmware(fw, name, &bt->bt->dev->dev);
पूर्ण

अटल स्थिर काष्ठा sp887x_config microtune_mt7202dtf_config = अणु
	.demod_address = 0x70,
	.request_firmware = microtune_mt7202dtf_request_firmware,
पूर्ण;

अटल पूर्णांक advbt771_samsung_tdtc9251dh0_demod_init(काष्ठा dvb_frontend* fe)
अणु
	अटल u8 mt352_घड़ी_config [] = अणु 0x89, 0x38, 0x2d पूर्ण;
	अटल u8 mt352_reset [] = अणु 0x50, 0x80 पूर्ण;
	अटल u8 mt352_adc_ctl_1_cfg [] = अणु 0x8E, 0x40 पूर्ण;
	अटल u8 mt352_agc_cfg [] = अणु 0x67, 0x10, 0x23, 0x00, 0xFF, 0xFF,
				       0x00, 0xFF, 0x00, 0x40, 0x40 पूर्ण;
	अटल u8 mt352_av771_extra[] = अणु 0xB5, 0x7A पूर्ण;
	अटल u8 mt352_capt_range_cfg[] = अणु 0x75, 0x32 पूर्ण;

	mt352_ग_लिखो(fe, mt352_घड़ी_config, माप(mt352_घड़ी_config));
	udelay(2000);
	mt352_ग_लिखो(fe, mt352_reset, माप(mt352_reset));
	mt352_ग_लिखो(fe, mt352_adc_ctl_1_cfg, माप(mt352_adc_ctl_1_cfg));

	mt352_ग_लिखो(fe, mt352_agc_cfg,माप(mt352_agc_cfg));
	udelay(2000);
	mt352_ग_लिखो(fe, mt352_av771_extra,माप(mt352_av771_extra));
	mt352_ग_लिखो(fe, mt352_capt_range_cfg, माप(mt352_capt_range_cfg));

	वापस 0;
पूर्ण

अटल पूर्णांक advbt771_samsung_tdtc9251dh0_tuner_calc_regs(काष्ठा dvb_frontend *fe, u8 *pllbuf, पूर्णांक buf_len)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 भाग;
	अचिन्हित अक्षर bs = 0;
	अचिन्हित अक्षर cp = 0;

	अगर (buf_len < 5) वापस -EINVAL;

	भाग = (((c->frequency + 83333) * 3) / 500000) + IF_FREQUENCYx6;

	अगर (c->frequency < 150000000)
		cp = 0xB4;
	अन्यथा अगर (c->frequency < 173000000)
		cp = 0xBC;
	अन्यथा अगर (c->frequency < 250000000)
		cp = 0xB4;
	अन्यथा अगर (c->frequency < 400000000)
		cp = 0xBC;
	अन्यथा अगर (c->frequency < 420000000)
		cp = 0xF4;
	अन्यथा अगर (c->frequency < 470000000)
		cp = 0xFC;
	अन्यथा अगर (c->frequency < 600000000)
		cp = 0xBC;
	अन्यथा अगर (c->frequency < 730000000)
		cp = 0xF4;
	अन्यथा
		cp = 0xFC;

	अगर (c->frequency < 150000000)
		bs = 0x01;
	अन्यथा अगर (c->frequency < 173000000)
		bs = 0x01;
	अन्यथा अगर (c->frequency < 250000000)
		bs = 0x02;
	अन्यथा अगर (c->frequency < 400000000)
		bs = 0x02;
	अन्यथा अगर (c->frequency < 420000000)
		bs = 0x02;
	अन्यथा अगर (c->frequency < 470000000)
		bs = 0x02;
	अन्यथा
		bs = 0x08;

	pllbuf[0] = 0x61;
	pllbuf[1] = भाग >> 8;
	pllbuf[2] = भाग & 0xff;
	pllbuf[3] = cp;
	pllbuf[4] = bs;

	वापस 5;
पूर्ण

अटल काष्ठा mt352_config advbt771_samsung_tdtc9251dh0_config = अणु
	.demod_address = 0x0f,
	.demod_init = advbt771_samsung_tdtc9251dh0_demod_init,
पूर्ण;

अटल स्थिर काष्ठा dst_config dst_config = अणु
	.demod_address = 0x55,
पूर्ण;

अटल पूर्णांक or51211_request_firmware(काष्ठा dvb_frontend* fe, स्थिर काष्ठा firmware **fw, अक्षर* name)
अणु
	काष्ठा dvb_bt8xx_card* bt = (काष्ठा dvb_bt8xx_card*) fe->dvb->priv;

	वापस request_firmware(fw, name, &bt->bt->dev->dev);
पूर्ण

अटल व्योम or51211_seपंचांगode(काष्ठा dvb_frontend * fe, पूर्णांक mode)
अणु
	काष्ठा dvb_bt8xx_card *bt = fe->dvb->priv;
	bttv_ग_लिखो_gpio(bt->bttv_nr, 0x0002, mode);   /* Reset */
	msleep(20);
पूर्ण

अटल व्योम or51211_reset(काष्ठा dvb_frontend * fe)
अणु
	काष्ठा dvb_bt8xx_card *bt = fe->dvb->priv;

	/* RESET DEVICE
	 * reset is controlled by GPIO-0
	 * when set to 0 causes reset and when to 1 क्रम normal op
	 * must reमुख्य reset क्रम 128 घड़ी cycles on a 50Mhz घड़ी
	 * also PRM1 PRM2 & PRM4 are controlled by GPIO-1,GPIO-2 & GPIO-4
	 * We assume that the reset has be held low दीर्घ enough or we
	 * have been reset by a घातer on.  When the driver is unloaded
	 * reset set to 0 so अगर reloaded we have been reset.
	 */
	/* reset & PRM1,2&4 are outमाला_दो */
	पूर्णांक ret = bttv_gpio_enable(bt->bttv_nr, 0x001F, 0x001F);
	अगर (ret != 0)
		pr_warn("or51211: Init Error - Can't Reset DVR (%i)\n", ret);
	bttv_ग_लिखो_gpio(bt->bttv_nr, 0x001F, 0x0000);   /* Reset */
	msleep(20);
	/* Now set क्रम normal operation */
	bttv_ग_लिखो_gpio(bt->bttv_nr, 0x0001F, 0x0001);
	/* रुको क्रम operation to begin */
	msleep(500);
पूर्ण

अटल व्योम or51211_sleep(काष्ठा dvb_frontend * fe)
अणु
	काष्ठा dvb_bt8xx_card *bt = fe->dvb->priv;
	bttv_ग_लिखो_gpio(bt->bttv_nr, 0x0001, 0x0000);
पूर्ण

अटल स्थिर काष्ठा or51211_config or51211_config = अणु
	.demod_address = 0x15,
	.request_firmware = or51211_request_firmware,
	.seपंचांगode = or51211_seपंचांगode,
	.reset = or51211_reset,
	.sleep = or51211_sleep,
पूर्ण;

अटल पूर्णांक vp3021_alps_tded4_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा dvb_bt8xx_card *card = (काष्ठा dvb_bt8xx_card *) fe->dvb->priv;
	u8 buf[4];
	u32 भाग;
	काष्ठा i2c_msg msg = अणु .addr = 0x60, .flags = 0, .buf = buf, .len = माप(buf) पूर्ण;

	भाग = (c->frequency + 36166667) / 166667;

	buf[0] = (भाग >> 8) & 0x7F;
	buf[1] = भाग & 0xFF;
	buf[2] = 0x85;
	अगर ((c->frequency >= 47000000) && (c->frequency < 153000000))
		buf[3] = 0x01;
	अन्यथा अगर ((c->frequency >= 153000000) && (c->frequency < 430000000))
		buf[3] = 0x02;
	अन्यथा अगर ((c->frequency >= 430000000) && (c->frequency < 824000000))
		buf[3] = 0x0C;
	अन्यथा अगर ((c->frequency >= 824000000) && (c->frequency < 863000000))
		buf[3] = 0x8C;
	अन्यथा
		वापस -EINVAL;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	i2c_transfer(card->i2c_adapter, &msg, 1);
	वापस 0;
पूर्ण

अटल काष्ठा nxt6000_config vp3021_alps_tded4_config = अणु
	.demod_address = 0x0a,
	.घड़ी_inversion = 1,
पूर्ण;

अटल पूर्णांक digitv_alps_tded4_demod_init(काष्ठा dvb_frontend* fe)
अणु
	अटल u8 mt352_घड़ी_config [] = अणु 0x89, 0x38, 0x2d पूर्ण;
	अटल u8 mt352_reset [] = अणु 0x50, 0x80 पूर्ण;
	अटल u8 mt352_adc_ctl_1_cfg [] = अणु 0x8E, 0x40 पूर्ण;
	अटल u8 mt352_agc_cfg [] = अणु 0x67, 0x20, 0xa0 पूर्ण;
	अटल u8 mt352_capt_range_cfg[] = अणु 0x75, 0x32 पूर्ण;

	mt352_ग_लिखो(fe, mt352_घड़ी_config, माप(mt352_घड़ी_config));
	udelay(2000);
	mt352_ग_लिखो(fe, mt352_reset, माप(mt352_reset));
	mt352_ग_लिखो(fe, mt352_adc_ctl_1_cfg, माप(mt352_adc_ctl_1_cfg));
	mt352_ग_लिखो(fe, mt352_agc_cfg,माप(mt352_agc_cfg));
	mt352_ग_लिखो(fe, mt352_capt_range_cfg, माप(mt352_capt_range_cfg));

	वापस 0;
पूर्ण

अटल पूर्णांक digitv_alps_tded4_tuner_calc_regs(काष्ठा dvb_frontend *fe,  u8 *pllbuf, पूर्णांक buf_len)
अणु
	u32 भाग;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	अगर (buf_len < 5)
		वापस -EINVAL;

	भाग = (((c->frequency + 83333) * 3) / 500000) + IF_FREQUENCYx6;

	pllbuf[0] = 0x61;
	pllbuf[1] = (भाग >> 8) & 0x7F;
	pllbuf[2] = भाग & 0xFF;
	pllbuf[3] = 0x85;

	dprपूर्णांकk("frequency %u, div %u\n", c->frequency, भाग);

	अगर (c->frequency < 470000000)
		pllbuf[4] = 0x02;
	अन्यथा अगर (c->frequency > 823000000)
		pllbuf[4] = 0x88;
	अन्यथा
		pllbuf[4] = 0x08;

	अगर (c->bandwidth_hz == 8000000)
		pllbuf[4] |= 0x04;

	वापस 5;
पूर्ण

अटल व्योम digitv_alps_tded4_reset(काष्ठा dvb_bt8xx_card *bt)
अणु
	/*
	 * Reset the frontend, must be called beक्रमe trying
	 * to initialise the MT352 or mt352_attach
	 * will fail. Same goes क्रम the nxt6000 frontend.
	 *
	 */

	पूर्णांक ret = bttv_gpio_enable(bt->bttv_nr, 0x08, 0x08);
	अगर (ret != 0)
		pr_warn("digitv_alps_tded4: Init Error - Can't Reset DVR (%i)\n",
			ret);

	/* Pulse the reset line */
	bttv_ग_लिखो_gpio(bt->bttv_nr, 0x08, 0x08); /* High */
	bttv_ग_लिखो_gpio(bt->bttv_nr, 0x08, 0x00); /* Low  */
	msleep(100);

	bttv_ग_लिखो_gpio(bt->bttv_nr, 0x08, 0x08); /* High */
पूर्ण

अटल काष्ठा mt352_config digitv_alps_tded4_config = अणु
	.demod_address = 0x0a,
	.demod_init = digitv_alps_tded4_demod_init,
पूर्ण;

अटल काष्ठा lgdt330x_config tdvs_tua6034_config = अणु
	.demod_chip       = LGDT3303,
	.serial_mpeg      = 0x40, /* TPSERIAL क्रम 3303 in TOP_CONTROL */
पूर्ण;

अटल व्योम lgdt330x_reset(काष्ठा dvb_bt8xx_card *bt)
अणु
	/* Set pin 27 of the lgdt3303 chip high to reset the frontend */

	/* Pulse the reset line */
	bttv_ग_लिखो_gpio(bt->bttv_nr, 0x00e00007, 0x00000001); /* High */
	bttv_ग_लिखो_gpio(bt->bttv_nr, 0x00e00007, 0x00000000); /* Low  */
	msleep(100);

	bttv_ग_लिखो_gpio(bt->bttv_nr, 0x00e00007, 0x00000001); /* High */
	msleep(100);
पूर्ण

अटल व्योम frontend_init(काष्ठा dvb_bt8xx_card *card, u32 type)
अणु
	काष्ठा dst_state* state = शून्य;

	चयन(type) अणु
	हाल BTTV_BOARD_DVICO_DVBT_LITE:
		card->fe = dvb_attach(mt352_attach, &thomson_dtt7579_config, card->i2c_adapter);

		अगर (card->fe == शून्य)
			card->fe = dvb_attach(zl10353_attach, &thomson_dtt7579_zl10353_config,
						  card->i2c_adapter);

		अगर (card->fe != शून्य) अणु
			card->fe->ops.tuner_ops.calc_regs = thomson_dtt7579_tuner_calc_regs;
			card->fe->ops.info.frequency_min_hz = 174 * MHz;
			card->fe->ops.info.frequency_max_hz = 862 * MHz;
		पूर्ण
		अवरोध;

	हाल BTTV_BOARD_DVICO_FUSIONHDTV_5_LITE:
		lgdt330x_reset(card);
		card->fe = dvb_attach(lgdt330x_attach, &tdvs_tua6034_config,
				      0x0e, card->i2c_adapter);
		अगर (card->fe != शून्य) अणु
			dvb_attach(simple_tuner_attach, card->fe,
				   card->i2c_adapter, 0x61,
				   TUNER_LG_TDVS_H06XF);
			dprपूर्णांकk("dvb_bt8xx: lgdt330x detected\n");
		पूर्ण
		अवरोध;

	हाल BTTV_BOARD_NEBULA_DIGITV:
		/*
		 * It is possible to determine the correct frontend using the I2C bus (see the Nebula SDK);
		 * this would be a cleaner solution than trying each frontend in turn.
		 */

		/* Old Nebula (marked (c)2003 on high profile pci card) has nxt6000 demod */
		digitv_alps_tded4_reset(card);
		card->fe = dvb_attach(nxt6000_attach, &vp3021_alps_tded4_config, card->i2c_adapter);
		अगर (card->fe != शून्य) अणु
			card->fe->ops.tuner_ops.set_params = vp3021_alps_tded4_tuner_set_params;
			dprपूर्णांकk("dvb_bt8xx: an nxt6000 was detected on your digitv card\n");
			अवरोध;
		पूर्ण

		/* New Nebula (marked (c)2005 on low profile pci card) has mt352 demod */
		digitv_alps_tded4_reset(card);
		card->fe = dvb_attach(mt352_attach, &digitv_alps_tded4_config, card->i2c_adapter);

		अगर (card->fe != शून्य) अणु
			card->fe->ops.tuner_ops.calc_regs = digitv_alps_tded4_tuner_calc_regs;
			dprपूर्णांकk("dvb_bt8xx: an mt352 was detected on your digitv card\n");
		पूर्ण
		अवरोध;

	हाल BTTV_BOARD_AVDVBT_761:
		card->fe = dvb_attach(sp887x_attach, &microtune_mt7202dtf_config, card->i2c_adapter);
		अगर (card->fe) अणु
			card->fe->ops.tuner_ops.set_params = microtune_mt7202dtf_tuner_set_params;
		पूर्ण
		अवरोध;

	हाल BTTV_BOARD_AVDVBT_771:
		card->fe = dvb_attach(mt352_attach, &advbt771_samsung_tdtc9251dh0_config, card->i2c_adapter);
		अगर (card->fe != शून्य) अणु
			card->fe->ops.tuner_ops.calc_regs = advbt771_samsung_tdtc9251dh0_tuner_calc_regs;
			card->fe->ops.info.frequency_min_hz = 174 * MHz;
			card->fe->ops.info.frequency_max_hz = 862 * MHz;
		पूर्ण
		अवरोध;

	हाल BTTV_BOARD_TWINHAN_DST:
		/*	DST is not a frontend driver !!!		*/
		state = kदो_स्मृति(माप (काष्ठा dst_state), GFP_KERNEL);
		अगर (!state) अणु
			pr_err("No memory\n");
			अवरोध;
		पूर्ण
		/*	Setup the Card					*/
		state->config = &dst_config;
		state->i2c = card->i2c_adapter;
		state->bt = card->bt;
		state->dst_ca = शून्य;
		/*	DST is not a frontend, attaching the ASIC	*/
		अगर (dvb_attach(dst_attach, state, &card->dvb_adapter) == शून्य) अणु
			pr_err("%s: Could not find a Twinhan DST\n", __func__);
			kमुक्त(state);
			अवरोध;
		पूर्ण
		/*	Attach other DST peripherals अगर any		*/
		/*	Conditional Access device			*/
		card->fe = &state->frontend;
		अगर (state->dst_hw_cap & DST_TYPE_HAS_CA)
			dvb_attach(dst_ca_attach, state, &card->dvb_adapter);
		अवरोध;

	हाल BTTV_BOARD_PINNACLESAT:
		card->fe = dvb_attach(cx24110_attach, &pctvsat_config, card->i2c_adapter);
		अगर (card->fe) अणु
			card->fe->ops.tuner_ops.init = pinnsat_tuner_init;
			card->fe->ops.tuner_ops.sleep = pinnsat_tuner_sleep;
			card->fe->ops.tuner_ops.set_params = cx24108_tuner_set_params;
		पूर्ण
		अवरोध;

	हाल BTTV_BOARD_PC_HDTV:
		card->fe = dvb_attach(or51211_attach, &or51211_config, card->i2c_adapter);
		अगर (card->fe != शून्य)
			dvb_attach(simple_tuner_attach, card->fe,
				   card->i2c_adapter, 0x61,
				   TUNER_PHILIPS_FCV1236D);
		अवरोध;
	पूर्ण

	अगर (card->fe == शून्य)
		pr_err("A frontend driver was not found for device [%04x:%04x] subsystem [%04x:%04x]\n",
		       card->bt->dev->venकरोr,
		       card->bt->dev->device,
		       card->bt->dev->subप्रणाली_venकरोr,
		       card->bt->dev->subप्रणाली_device);
	अन्यथा
		अगर (dvb_रेजिस्टर_frontend(&card->dvb_adapter, card->fe)) अणु
			pr_err("Frontend registration failed!\n");
			dvb_frontend_detach(card->fe);
			card->fe = शून्य;
		पूर्ण
पूर्ण

अटल पूर्णांक dvb_bt8xx_load_card(काष्ठा dvb_bt8xx_card *card, u32 type)
अणु
	पूर्णांक result;

	result = dvb_रेजिस्टर_adapter(&card->dvb_adapter, card->card_name,
				      THIS_MODULE, &card->bt->dev->dev,
				      adapter_nr);
	अगर (result < 0) अणु
		pr_err("dvb_register_adapter failed (errno = %d)\n", result);
		वापस result;
	पूर्ण
	card->dvb_adapter.priv = card;

	card->bt->adapter = card->i2c_adapter;

	स_रखो(&card->demux, 0, माप(काष्ठा dvb_demux));

	card->demux.dmx.capabilities = DMX_TS_FILTERING | DMX_SECTION_FILTERING | DMX_MEMORY_BASED_FILTERING;

	card->demux.priv = card;
	card->demux.filternum = 256;
	card->demux.feednum = 256;
	card->demux.start_feed = dvb_bt8xx_start_feed;
	card->demux.stop_feed = dvb_bt8xx_stop_feed;
	card->demux.ग_लिखो_to_decoder = शून्य;

	result = dvb_dmx_init(&card->demux);
	अगर (result < 0) अणु
		pr_err("dvb_dmx_init failed (errno = %d)\n", result);
		जाओ err_unरेजिस्टर_adaptor;
	पूर्ण

	card->dmxdev.filternum = 256;
	card->dmxdev.demux = &card->demux.dmx;
	card->dmxdev.capabilities = 0;

	result = dvb_dmxdev_init(&card->dmxdev, &card->dvb_adapter);
	अगर (result < 0) अणु
		pr_err("dvb_dmxdev_init failed (errno = %d)\n", result);
		जाओ err_dmx_release;
	पूर्ण

	card->fe_hw.source = DMX_FRONTEND_0;

	result = card->demux.dmx.add_frontend(&card->demux.dmx, &card->fe_hw);
	अगर (result < 0) अणु
		pr_err("dvb_dmx_init failed (errno = %d)\n", result);
		जाओ err_dmxdev_release;
	पूर्ण

	card->fe_mem.source = DMX_MEMORY_FE;

	result = card->demux.dmx.add_frontend(&card->demux.dmx, &card->fe_mem);
	अगर (result < 0) अणु
		pr_err("dvb_dmx_init failed (errno = %d)\n", result);
		जाओ err_हटाओ_hw_frontend;
	पूर्ण

	result = card->demux.dmx.connect_frontend(&card->demux.dmx, &card->fe_hw);
	अगर (result < 0) अणु
		pr_err("dvb_dmx_init failed (errno = %d)\n", result);
		जाओ err_हटाओ_mem_frontend;
	पूर्ण

	result = dvb_net_init(&card->dvb_adapter, &card->dvbnet, &card->demux.dmx);
	अगर (result < 0) अणु
		pr_err("dvb_net_init failed (errno = %d)\n", result);
		जाओ err_disconnect_frontend;
	पूर्ण

	tasklet_setup(&card->bt->tasklet, dvb_bt8xx_task);

	frontend_init(card, type);

	वापस 0;

err_disconnect_frontend:
	card->demux.dmx.disconnect_frontend(&card->demux.dmx);
err_हटाओ_mem_frontend:
	card->demux.dmx.हटाओ_frontend(&card->demux.dmx, &card->fe_mem);
err_हटाओ_hw_frontend:
	card->demux.dmx.हटाओ_frontend(&card->demux.dmx, &card->fe_hw);
err_dmxdev_release:
	dvb_dmxdev_release(&card->dmxdev);
err_dmx_release:
	dvb_dmx_release(&card->demux);
err_unरेजिस्टर_adaptor:
	dvb_unरेजिस्टर_adapter(&card->dvb_adapter);
	वापस result;
पूर्ण

अटल पूर्णांक dvb_bt8xx_probe(काष्ठा bttv_sub_device *sub)
अणु
	काष्ठा dvb_bt8xx_card *card;
	काष्ठा pci_dev* bttv_pci_dev;
	पूर्णांक ret;

	अगर (!(card = kzalloc(माप(काष्ठा dvb_bt8xx_card), GFP_KERNEL)))
		वापस -ENOMEM;

	mutex_init(&card->lock);
	card->bttv_nr = sub->core->nr;
	strscpy(card->card_name, sub->core->v4l2_dev.name,
		माप(card->card_name));
	card->i2c_adapter = &sub->core->i2c_adap;

	चयन(sub->core->type) अणु
	हाल BTTV_BOARD_PINNACLESAT:
		card->gpio_mode = 0x0400c060;
		/* should be: BT878_A_GAIN=0,BT878_A_PWRDN,BT878_DA_DPM,BT878_DA_SBR,
			      BT878_DA_IOM=1,BT878_DA_APP to enable serial highspeed mode. */
		card->op_sync_orin = BT878_RISC_SYNC_MASK;
		card->irq_err_ignore = BT878_AFBUS | BT878_AFDSR;
		अवरोध;

	हाल BTTV_BOARD_DVICO_DVBT_LITE:
		card->gpio_mode = 0x0400C060;
		card->op_sync_orin = BT878_RISC_SYNC_MASK;
		card->irq_err_ignore = BT878_AFBUS | BT878_AFDSR;
		/* 26, 15, 14, 6, 5
		 * A_PWRDN  DA_DPM DA_SBR DA_IOM_DA
		 * DA_APP(parallel) */
		अवरोध;

	हाल BTTV_BOARD_DVICO_FUSIONHDTV_5_LITE:
		card->gpio_mode = 0x0400c060;
		card->op_sync_orin = BT878_RISC_SYNC_MASK;
		card->irq_err_ignore = BT878_AFBUS | BT878_AFDSR;
		अवरोध;

	हाल BTTV_BOARD_NEBULA_DIGITV:
	हाल BTTV_BOARD_AVDVBT_761:
		card->gpio_mode = (1 << 26) | (1 << 14) | (1 << 5);
		card->op_sync_orin = BT878_RISC_SYNC_MASK;
		card->irq_err_ignore = BT878_AFBUS | BT878_AFDSR;
		/* A_PWRDN DA_SBR DA_APP (high speed serial) */
		अवरोध;

	हाल BTTV_BOARD_AVDVBT_771: //हाल 0x07711461:
		card->gpio_mode = 0x0400402B;
		card->op_sync_orin = BT878_RISC_SYNC_MASK;
		card->irq_err_ignore = BT878_AFBUS | BT878_AFDSR;
		/* A_PWRDN DA_SBR  DA_APP[0] PKTP=10 RISC_ENABLE FIFO_ENABLE*/
		अवरोध;

	हाल BTTV_BOARD_TWINHAN_DST:
		card->gpio_mode = 0x2204f2c;
		card->op_sync_orin = BT878_RISC_SYNC_MASK;
		card->irq_err_ignore = BT878_APABORT | BT878_ARIPERR |
				       BT878_APPERR | BT878_AFBUS;
		/* 25,21,14,11,10,9,8,3,2 then
		 * 0x33 = 5,4,1,0
		 * A_SEL=SML, DA_MLB, DA_SBR,
		 * DA_SDR=f, fअगरo trigger = 32 DWORDS
		 * IOM = 0 == audio A/D
		 * DPM = 0 == digital audio mode
		 * == async data parallel port
		 * then 0x33 (13 is set by start_capture)
		 * DA_APP = async data parallel port,
		 * ACAP_EN = 1,
		 * RISC+FIFO ENABLE */
		अवरोध;

	हाल BTTV_BOARD_PC_HDTV:
		card->gpio_mode = 0x0100EC7B;
		card->op_sync_orin = BT878_RISC_SYNC_MASK;
		card->irq_err_ignore = BT878_AFBUS | BT878_AFDSR;
		अवरोध;

	शेष:
		pr_err("Unknown bttv card type: %d\n", sub->core->type);
		kमुक्त(card);
		वापस -ENODEV;
	पूर्ण

	dprपूर्णांकk("dvb_bt8xx: identified card%d as %s\n", card->bttv_nr, card->card_name);

	अगर (!(bttv_pci_dev = bttv_get_pcidev(card->bttv_nr))) अणु
		pr_err("no pci device for card %d\n", card->bttv_nr);
		kमुक्त(card);
		वापस -ENODEV;
	पूर्ण

	अगर (!(card->bt = dvb_bt8xx_878_match(card->bttv_nr, bttv_pci_dev))) अणु
		pr_err("unable to determine DMA core of card %d,\n", card->bttv_nr);
		pr_err("if you have the ALSA bt87x audio driver installed, try removing it.\n");

		kमुक्त(card);
		वापस -ENODEV;
	पूर्ण

	mutex_init(&card->bt->gpio_lock);
	card->bt->bttv_nr = sub->core->nr;

	अगर ( (ret = dvb_bt8xx_load_card(card, sub->core->type)) ) अणु
		kमुक्त(card);
		वापस ret;
	पूर्ण

	dev_set_drvdata(&sub->dev, card);
	वापस 0;
पूर्ण

अटल व्योम dvb_bt8xx_हटाओ(काष्ठा bttv_sub_device *sub)
अणु
	काष्ठा dvb_bt8xx_card *card = dev_get_drvdata(&sub->dev);

	dprपूर्णांकk("dvb_bt8xx: unloading card%d\n", card->bttv_nr);

	bt878_stop(card->bt);
	tasklet_समाप्त(&card->bt->tasklet);
	dvb_net_release(&card->dvbnet);
	card->demux.dmx.हटाओ_frontend(&card->demux.dmx, &card->fe_mem);
	card->demux.dmx.हटाओ_frontend(&card->demux.dmx, &card->fe_hw);
	dvb_dmxdev_release(&card->dmxdev);
	dvb_dmx_release(&card->demux);
	अगर (card->fe) अणु
		dvb_unरेजिस्टर_frontend(card->fe);
		dvb_frontend_detach(card->fe);
	पूर्ण
	dvb_unरेजिस्टर_adapter(&card->dvb_adapter);

	kमुक्त(card);
पूर्ण

अटल काष्ठा bttv_sub_driver driver = अणु
	.drv = अणु
		.name		= "dvb-bt8xx",
	पूर्ण,
	.probe		= dvb_bt8xx_probe,
	.हटाओ		= dvb_bt8xx_हटाओ,
	/* FIXME:
	 * .shutकरोwn	= dvb_bt8xx_shutकरोwn,
	 * .suspend	= dvb_bt8xx_suspend,
	 * .resume	= dvb_bt8xx_resume,
	 */
पूर्ण;

अटल पूर्णांक __init dvb_bt8xx_init(व्योम)
अणु
	वापस bttv_sub_रेजिस्टर(&driver, "dvb");
पूर्ण

अटल व्योम __निकास dvb_bt8xx_निकास(व्योम)
अणु
	bttv_sub_unरेजिस्टर(&driver);
पूर्ण

module_init(dvb_bt8xx_init);
module_निकास(dvb_bt8xx_निकास);

MODULE_DESCRIPTION("Bt8xx based DVB adapter driver");
MODULE_AUTHOR("Florian Schirmer <jolt@tuxbox.org>");
MODULE_LICENSE("GPL");
