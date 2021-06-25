<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * driver क्रम the SAA7146 based AV110 cards (like the Fujitsu-Siemens DVB)
 * av7110.c: initialization and demux stuff
 *
 * Copyright (C) 1999-2002 Ralph  Metzler
 *                       & Marcus Metzler क्रम convergence पूर्णांकegrated media GmbH
 *
 * originally based on code by:
 * Copyright (C) 1998,1999 Christian Theiss <mistert@rz.fh-augsburg.de>
 *
 * the project's page is at https://linuxtv.org
 */


#समावेश <linux/module.h>
#समावेश <linux/kmod.h>
#समावेश <linux/delay.h>
#समावेश <linux/fs.h>
#समावेश <linux/समयr.h>
#समावेश <linux/poll.h>

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/माला.स>
#समावेश <linux/pci.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/firmware.h>
#समावेश <linux/crc32.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <यंत्र/byteorder.h>


#समावेश <linux/dvb/frontend.h>

#समावेश <media/dvb_frontend.h>

#समावेश "ttpci-eeprom.h"
#समावेश "av7110.h"
#समावेश "av7110_hw.h"
#समावेश "av7110_av.h"
#समावेश "av7110_ca.h"
#समावेश "av7110_ipack.h"

#समावेश "bsbe1.h"
#समावेश "lnbp21.h"
#समावेश "bsru6.h"

#घोषणा TS_WIDTH  376
#घोषणा TS_HEIGHT 512
#घोषणा TS_BUFLEN (TS_WIDTH*TS_HEIGHT)
#घोषणा TS_MAX_PACKETS (TS_BUFLEN/TS_SIZE)


पूर्णांक av7110_debug;

अटल पूर्णांक vidmode = CVBS_RGB_OUT;
अटल पूर्णांक pids_off;
अटल पूर्णांक adac = DVB_ADAC_TI;
अटल पूर्णांक hw_sections;
अटल पूर्णांक rgb_on;
अटल पूर्णांक volume = 255;
अटल पूर्णांक budgetpatch;
अटल पूर्णांक wss_cfg_4_3 = 0x4008;
अटल पूर्णांक wss_cfg_16_9 = 0x0007;
अटल पूर्णांक tv_standard;
अटल पूर्णांक full_ts;

module_param_named(debug, av7110_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "debug level (bitmask, default 0)");
module_param(vidmode, पूर्णांक, 0444);
MODULE_PARM_DESC(vidmode,"analog video out: 0 off, 1 CVBS+RGB (default), 2 CVBS+YC, 3 YC");
module_param(pids_off, पूर्णांक, 0444);
MODULE_PARM_DESC(pids_off,"clear video/audio/PCR PID filters when demux is closed");
module_param(adac, पूर्णांक, 0444);
MODULE_PARM_DESC(adac,"audio DAC type: 0 TI, 1 CRYSTAL, 2 MSP (use if autodetection fails)");
module_param(hw_sections, पूर्णांक, 0444);
MODULE_PARM_DESC(hw_sections, "0 use software section filter, 1 use hardware");
module_param(rgb_on, पूर्णांक, 0444);
MODULE_PARM_DESC(rgb_on, "For Siemens DVB-C cards only: Enable RGB control signal on SCART pin 16 to switch SCART video mode from CVBS to RGB");
module_param(volume, पूर्णांक, 0444);
MODULE_PARM_DESC(volume, "initial volume: default 255 (range 0-255)");
module_param(budgetpatch, पूर्णांक, 0444);
MODULE_PARM_DESC(budgetpatch, "use budget-patch hardware modification: default 0 (0 no, 1 autodetect, 2 always)");
module_param(full_ts, पूर्णांक, 0444);
MODULE_PARM_DESC(full_ts, "enable code for full-ts hardware modification: 0 disable (default), 1 enable");
module_param(wss_cfg_4_3, पूर्णांक, 0444);
MODULE_PARM_DESC(wss_cfg_4_3, "WSS 4:3 - default 0x4008 - bit 15: disable, 14: burst mode, 13..0: wss data");
module_param(wss_cfg_16_9, पूर्णांक, 0444);
MODULE_PARM_DESC(wss_cfg_16_9, "WSS 16:9 - default 0x0007 - bit 15: disable, 14: burst mode, 13..0: wss data");
module_param(tv_standard, पूर्णांक, 0444);
MODULE_PARM_DESC(tv_standard, "TV standard: 0 PAL (default), 1 NTSC");

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

अटल व्योम restart_feeds(काष्ठा av7110 *av7110);
अटल पूर्णांक budget_start_feed(काष्ठा dvb_demux_feed *feed);
अटल पूर्णांक budget_stop_feed(काष्ठा dvb_demux_feed *feed);

अटल पूर्णांक av7110_num;

#घोषणा FE_FUNC_OVERRIDE(fe_func, av7110_copy, av7110_func) \
अणु\
	अगर (fe_func != शून्य) अणु \
		av7110_copy = fe_func; \
		fe_func = av7110_func; \
	पूर्ण \
पूर्ण


अटल व्योम init_av7110_av(काष्ठा av7110 *av7110)
अणु
	पूर्णांक ret;
	काष्ठा saa7146_dev *dev = av7110->dev;

	/* set पूर्णांकernal volume control to maximum */
	av7110->adac_type = DVB_ADAC_TI;
	ret = av7110_set_volume(av7110, av7110->mixer.volume_left, av7110->mixer.volume_right);
	अगर (ret < 0)
		prपूर्णांकk("dvb-ttpci:cannot set internal volume to maximum:%d\n",ret);

	ret = av7110_fw_cmd(av7110, COMTYPE_ENCODER, SetMonitorType,
			    1, (u16) av7110->display_ar);
	अगर (ret < 0)
		prपूर्णांकk("dvb-ttpci: unable to set aspect ratio\n");
	ret = av7110_fw_cmd(av7110, COMTYPE_ENCODER, SetPanScanType,
			    1, av7110->display_panscan);
	अगर (ret < 0)
		prपूर्णांकk("dvb-ttpci: unable to set pan scan\n");

	ret = av7110_fw_cmd(av7110, COMTYPE_ENCODER, SetWSSConfig, 2, 2, wss_cfg_4_3);
	अगर (ret < 0)
		prपूर्णांकk("dvb-ttpci: unable to configure 4:3 wss\n");
	ret = av7110_fw_cmd(av7110, COMTYPE_ENCODER, SetWSSConfig, 2, 3, wss_cfg_16_9);
	अगर (ret < 0)
		prपूर्णांकk("dvb-ttpci: unable to configure 16:9 wss\n");

	ret = av7710_set_video_mode(av7110, vidmode);
	अगर (ret < 0)
		prपूर्णांकk("dvb-ttpci:cannot set video mode:%d\n",ret);

	/* handle dअगरferent card types */
	/* reमुख्यing inits according to card and frontend type */
	av7110->analog_tuner_flags = 0;
	av7110->current_input = 0;
	अगर (dev->pci->subप्रणाली_venकरोr == 0x13c2 && dev->pci->subप्रणाली_device == 0x000a)
		av7110_fw_cmd(av7110, COMTYPE_AUDIODAC, ADSwitch, 1, 0); // SPDIF on
	अगर (i2c_ग_लिखोreg(av7110, 0x20, 0x00, 0x00) == 1) अणु
		prपूर्णांकk ("dvb-ttpci: Crystal audio DAC @ card %d detected\n",
			av7110->dvb_adapter.num);
		av7110->adac_type = DVB_ADAC_CRYSTAL;
		i2c_ग_लिखोreg(av7110, 0x20, 0x01, 0xd2);
		i2c_ग_लिखोreg(av7110, 0x20, 0x02, 0x49);
		i2c_ग_लिखोreg(av7110, 0x20, 0x03, 0x00);
		i2c_ग_लिखोreg(av7110, 0x20, 0x04, 0x00);

		/**
		 * some special handling क्रम the Siemens DVB-C cards...
		 */
	पूर्ण अन्यथा अगर (0 == av7110_init_analog_module(av7110)) अणु
		/* करोne. */
	पूर्ण
	अन्यथा अगर (dev->pci->subप्रणाली_venकरोr == 0x110a) अणु
		prपूर्णांकk("dvb-ttpci: DVB-C w/o analog module @ card %d detected\n",
			av7110->dvb_adapter.num);
		av7110->adac_type = DVB_ADAC_NONE;
	पूर्ण
	अन्यथा अणु
		av7110->adac_type = adac;
		prपूर्णांकk("dvb-ttpci: adac type set to %d @ card %d\n",
			av7110->adac_type, av7110->dvb_adapter.num);
	पूर्ण

	अगर (av7110->adac_type == DVB_ADAC_NONE || av7110->adac_type == DVB_ADAC_MSP34x0) अणु
		// चयन DVB SCART on
		ret = av7110_fw_cmd(av7110, COMTYPE_AUDIODAC, MainSwitch, 1, 0);
		अगर (ret < 0)
			prपूर्णांकk("dvb-ttpci:cannot switch on SCART(Main):%d\n",ret);
		ret = av7110_fw_cmd(av7110, COMTYPE_AUDIODAC, ADSwitch, 1, 1);
		अगर (ret < 0)
			prपूर्णांकk("dvb-ttpci:cannot switch on SCART(AD):%d\n",ret);
		अगर (rgb_on &&
		    ((av7110->dev->pci->subप्रणाली_venकरोr == 0x110a) ||
		     (av7110->dev->pci->subप्रणाली_venकरोr == 0x13c2)) &&
		     (av7110->dev->pci->subप्रणाली_device == 0x0000)) अणु
			saa7146_setgpio(dev, 1, SAA7146_GPIO_OUTHI); // RGB on, SCART pin 16
			//saa7146_setgpio(dev, 3, SAA7146_GPIO_OUTLO); // SCARTpin 8
		पूर्ण
	पूर्ण

	अगर (dev->pci->subप्रणाली_venकरोr == 0x13c2 && dev->pci->subप्रणाली_device == 0x000e)
		av7110_fw_cmd(av7110, COMTYPE_AUDIODAC, SpdअगरSwitch, 1, 0); // SPDIF on

	ret = av7110_set_volume(av7110, av7110->mixer.volume_left, av7110->mixer.volume_right);
	अगर (ret < 0)
		prपूर्णांकk("dvb-ttpci:cannot set volume :%d\n",ret);
पूर्ण

अटल व्योम recover_arm(काष्ठा av7110 *av7110)
अणु
	dprपूर्णांकk(4, "%p\n",av7110);

	av7110_bootarm(av7110);
	msleep(100);

	init_av7110_av(av7110);

	/* card-specअगरic recovery */
	अगर (av7110->recover)
		av7110->recover(av7110);

	restart_feeds(av7110);

#अगर IS_ENABLED(CONFIG_DVB_AV7110_IR)
	av7110_set_ir_config(av7110);
#पूर्ण_अगर
पूर्ण

अटल व्योम av7110_arm_sync(काष्ठा av7110 *av7110)
अणु
	अगर (av7110->arm_thपढ़ो)
		kthपढ़ो_stop(av7110->arm_thपढ़ो);

	av7110->arm_thपढ़ो = शून्य;
पूर्ण

अटल पूर्णांक arm_thपढ़ो(व्योम *data)
अणु
	काष्ठा av7110 *av7110 = data;
	u16 newloops = 0;
	पूर्णांक समयout;

	dprपूर्णांकk(4, "%p\n",av7110);

	क्रम (;;) अणु
		समयout = रुको_event_पूर्णांकerruptible_समयout(av7110->arm_रुको,
			kthपढ़ो_should_stop(), 5 * HZ);

		अगर (-ERESTARTSYS == समयout || kthपढ़ो_should_stop()) अणु
			/* got संकेत or told to quit*/
			अवरोध;
		पूर्ण

		अगर (!av7110->arm_पढ़ोy)
			जारी;

		अगर (mutex_lock_पूर्णांकerruptible(&av7110->dcomlock))
			अवरोध;
		newloops = rdebi(av7110, DEBINOSWAP, STATUS_LOOPS, 0, 2);
		mutex_unlock(&av7110->dcomlock);

		अगर (newloops == av7110->arm_loops || av7110->arm_errors > 3) अणु
			prपूर्णांकk(KERN_ERR "dvb-ttpci: ARM crashed @ card %d\n",
			       av7110->dvb_adapter.num);

			recover_arm(av7110);

			अगर (mutex_lock_पूर्णांकerruptible(&av7110->dcomlock))
				अवरोध;
			newloops = rdebi(av7110, DEBINOSWAP, STATUS_LOOPS, 0, 2) - 1;
			mutex_unlock(&av7110->dcomlock);
		पूर्ण
		av7110->arm_loops = newloops;
		av7110->arm_errors = 0;
	पूर्ण

	वापस 0;
पूर्ण


/****************************************************************************
 * IRQ handling
 ****************************************************************************/

अटल पूर्णांक DvbDmxFilterCallback(u8 *buffer1, माप_प्रकार buffer1_len,
				u8 *buffer2, माप_प्रकार buffer2_len,
				काष्ठा dvb_demux_filter *dvbdmxfilter,
				काष्ठा av7110 *av7110)
अणु
	अगर (!dvbdmxfilter->feed->demux->dmx.frontend)
		वापस 0;
	अगर (dvbdmxfilter->feed->demux->dmx.frontend->source == DMX_MEMORY_FE)
		वापस 0;

	चयन (dvbdmxfilter->type) अणु
	हाल DMX_TYPE_SEC:
		अगर ((((buffer1[1] << 8) | buffer1[2]) & 0xfff) + 3 != buffer1_len)
			वापस 0;
		अगर (dvbdmxfilter->करोneq) अणु
			काष्ठा dmx_section_filter *filter = &dvbdmxfilter->filter;
			पूर्णांक i;
			u8 xor, neq = 0;

			क्रम (i = 0; i < DVB_DEMUX_MASK_MAX; i++) अणु
				xor = filter->filter_value[i] ^ buffer1[i];
				neq |= dvbdmxfilter->maskandnoपंचांगode[i] & xor;
			पूर्ण
			अगर (!neq)
				वापस 0;
		पूर्ण
		वापस dvbdmxfilter->feed->cb.sec(buffer1, buffer1_len,
						  buffer2, buffer2_len,
						  &dvbdmxfilter->filter, शून्य);
	हाल DMX_TYPE_TS:
		अगर (!(dvbdmxfilter->feed->ts_type & TS_PACKET))
			वापस 0;
		अगर (dvbdmxfilter->feed->ts_type & TS_PAYLOAD_ONLY)
			वापस dvbdmxfilter->feed->cb.ts(buffer1, buffer1_len,
							 buffer2, buffer2_len,
							 &dvbdmxfilter->feed->feed.ts,
							 शून्य);
		अन्यथा
			av7110_p2t_ग_लिखो(buffer1, buffer1_len,
					 dvbdmxfilter->feed->pid,
					 &av7110->p2t_filter[dvbdmxfilter->index]);
		वापस 0;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण


//#घोषणा DEBUG_TIMING
अटल अंतरभूत व्योम prपूर्णांक_समय(अक्षर *s)
अणु
#अगर_घोषित DEBUG_TIMING
	काष्ठा बारpec64 ts;
	kसमय_get_real_ts64(&ts);
	prपूर्णांकk("%s: %lld.%09ld\n", s, (s64)ts.tv_sec, ts.tv_nsec);
#पूर्ण_अगर
पूर्ण

#घोषणा DEBI_READ 0
#घोषणा DEBI_WRITE 1
अटल अंतरभूत व्योम start_debi_dma(काष्ठा av7110 *av7110, पूर्णांक dir,
				  अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक len)
अणु
	dprपूर्णांकk(8, "%c %08lx %u\n", dir == DEBI_READ ? 'R' : 'W', addr, len);
	अगर (saa7146_रुको_क्रम_debi_करोne(av7110->dev, 0)) अणु
		prपूर्णांकk(KERN_ERR "%s: saa7146_wait_for_debi_done timed out\n", __func__);
		वापस;
	पूर्ण

	SAA7146_ISR_CLEAR(av7110->dev, MASK_19); /* क्रम good measure */
	SAA7146_IER_ENABLE(av7110->dev, MASK_19);
	अगर (len < 5)
		len = 5; /* we want a real DEBI DMA */
	अगर (dir == DEBI_WRITE)
		iwdebi(av7110, DEBISWAB, addr, 0, (len + 3) & ~3);
	अन्यथा
		irdebi(av7110, DEBISWAB, addr, 0, len);
पूर्ण

अटल व्योम debiirq(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा av7110 *av7110 = from_tasklet(av7110, t, debi_tasklet);
	पूर्णांक type = av7110->debitype;
	पूर्णांक handle = (type >> 8) & 0x1f;
	अचिन्हित पूर्णांक xfer = 0;

	prपूर्णांक_समय("debi");
	dprपूर्णांकk(4, "type 0x%04x\n", type);

	अगर (type == -1) अणु
		prपूर्णांकk("DEBI irq oops @ %ld, psr:0x%08x, ssr:0x%08x\n",
		       jअगरfies, saa7146_पढ़ो(av7110->dev, PSR),
		       saa7146_पढ़ो(av7110->dev, SSR));
		जाओ debi_करोne;
	पूर्ण
	av7110->debitype = -1;

	चयन (type & 0xff) अणु

	हाल DATA_TS_RECORD:
		dvb_dmx_swfilter_packets(&av7110->demux,
					 (स्थिर u8 *) av7110->debi_virt,
					 av7110->debilen / 188);
		xfer = RX_BUFF;
		अवरोध;

	हाल DATA_PES_RECORD:
		अगर (av7110->demux.recording)
			av7110_record_cb(&av7110->p2t[handle],
					 (u8 *) av7110->debi_virt,
					 av7110->debilen);
		xfer = RX_BUFF;
		अवरोध;

	हाल DATA_IPMPE:
	हाल DATA_FSECTION:
	हाल DATA_PIPING:
		अगर (av7110->handle2filter[handle])
			DvbDmxFilterCallback((u8 *)av7110->debi_virt,
					     av7110->debilen, शून्य, 0,
					     av7110->handle2filter[handle],
					     av7110);
		xfer = RX_BUFF;
		अवरोध;

	हाल DATA_CI_GET:
	अणु
		u8 *data = av7110->debi_virt;
		u8 data_0 = data[0];

		अगर (data_0 < 2 && data[2] == 0xff) अणु
			पूर्णांक flags = 0;
			अगर (data[5] > 0)
				flags |= CA_CI_MODULE_PRESENT;
			अगर (data[5] > 5)
				flags |= CA_CI_MODULE_READY;
			av7110->ci_slot[data_0].flags = flags;
		पूर्ण अन्यथा
			ci_get_data(&av7110->ci_rbuffer,
				    av7110->debi_virt,
				    av7110->debilen);
		xfer = RX_BUFF;
		अवरोध;
	पूर्ण

	हाल DATA_COMMON_INTERFACE:
		CI_handle(av7110, (u8 *)av7110->debi_virt, av7110->debilen);
		xfer = RX_BUFF;
		अवरोध;

	हाल DATA_DEBUG_MESSAGE:
		((s8*)av7110->debi_virt)[Reserved_SIZE - 1] = 0;
		prपूर्णांकk("%s\n", (s8 *) av7110->debi_virt);
		xfer = RX_BUFF;
		अवरोध;

	हाल DATA_CI_PUT:
		dprपूर्णांकk(4, "debi DATA_CI_PUT\n");
		xfer = TX_BUFF;
		अवरोध;
	हाल DATA_MPEG_PLAY:
		dprपूर्णांकk(4, "debi DATA_MPEG_PLAY\n");
		xfer = TX_BUFF;
		अवरोध;
	हाल DATA_BMP_LOAD:
		dprपूर्णांकk(4, "debi DATA_BMP_LOAD\n");
		xfer = TX_BUFF;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
debi_करोne:
	spin_lock(&av7110->debilock);
	अगर (xfer)
		iwdebi(av7110, DEBINOSWAP, xfer, 0, 2);
	ARM_ClearMailBox(av7110);
	spin_unlock(&av7110->debilock);
पूर्ण

/* irq from av7110 firmware writing the mailbox रेजिस्टर in the DPRAM */
अटल व्योम gpioirq(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा av7110 *av7110 = from_tasklet(av7110, t, gpio_tasklet);
	u32 rxbuf, txbuf;
	पूर्णांक len;

	अगर (av7110->debitype != -1)
		/* we shouldn't get any irq जबतक a debi xfer is running */
		prपूर्णांकk("dvb-ttpci: GPIO0 irq oops @ %ld, psr:0x%08x, ssr:0x%08x\n",
		       jअगरfies, saa7146_पढ़ो(av7110->dev, PSR),
		       saa7146_पढ़ो(av7110->dev, SSR));

	अगर (saa7146_रुको_क्रम_debi_करोne(av7110->dev, 0)) अणु
		prपूर्णांकk(KERN_ERR "%s: saa7146_wait_for_debi_done timed out\n", __func__);
		BUG(); /* maybe we should try resetting the debi? */
	पूर्ण

	spin_lock(&av7110->debilock);
	ARM_ClearIrq(av7110);

	/* see what the av7110 wants */
	av7110->debitype = irdebi(av7110, DEBINOSWAP, IRQ_STATE, 0, 2);
	av7110->debilen  = irdebi(av7110, DEBINOSWAP, IRQ_STATE_EXT, 0, 2);
	rxbuf = irdebi(av7110, DEBINOSWAP, RX_BUFF, 0, 2);
	txbuf = irdebi(av7110, DEBINOSWAP, TX_BUFF, 0, 2);
	len = (av7110->debilen + 3) & ~3;

	prपूर्णांक_समय("gpio");
	dprपूर्णांकk(8, "GPIO0 irq 0x%04x %d\n", av7110->debitype, av7110->debilen);

	चयन (av7110->debitype & 0xff) अणु

	हाल DATA_TS_PLAY:
	हाल DATA_PES_PLAY:
		अवरोध;

	हाल DATA_MPEG_VIDEO_EVENT:
	अणु
		u32 h_ar;
		काष्ठा video_event event;

		av7110->video_size.w = irdebi(av7110, DEBINOSWAP, STATUS_MPEG_WIDTH, 0, 2);
		h_ar = irdebi(av7110, DEBINOSWAP, STATUS_MPEG_HEIGHT_AR, 0, 2);

		iwdebi(av7110, DEBINOSWAP, IRQ_STATE_EXT, 0, 2);
		iwdebi(av7110, DEBINOSWAP, RX_BUFF, 0, 2);

		av7110->video_size.h = h_ar & 0xfff;

		event.type = VIDEO_EVENT_SIZE_CHANGED;
		event.u.size.w = av7110->video_size.w;
		event.u.size.h = av7110->video_size.h;
		चयन ((h_ar >> 12) & 0xf)
		अणु
		हाल 3:
			av7110->video_size.aspect_ratio = VIDEO_FORMAT_16_9;
			event.u.size.aspect_ratio = VIDEO_FORMAT_16_9;
			av7110->videostate.video_क्रमmat = VIDEO_FORMAT_16_9;
			अवरोध;
		हाल 4:
			av7110->video_size.aspect_ratio = VIDEO_FORMAT_221_1;
			event.u.size.aspect_ratio = VIDEO_FORMAT_221_1;
			av7110->videostate.video_क्रमmat = VIDEO_FORMAT_221_1;
			अवरोध;
		शेष:
			av7110->video_size.aspect_ratio = VIDEO_FORMAT_4_3;
			event.u.size.aspect_ratio = VIDEO_FORMAT_4_3;
			av7110->videostate.video_क्रमmat = VIDEO_FORMAT_4_3;
		पूर्ण

		dprपूर्णांकk(8, "GPIO0 irq: DATA_MPEG_VIDEO_EVENT: w/h/ar = %u/%u/%u\n",
			av7110->video_size.w, av7110->video_size.h,
			av7110->video_size.aspect_ratio);

		dvb_video_add_event(av7110, &event);
		अवरोध;
	पूर्ण

	हाल DATA_CI_PUT:
	अणु
		पूर्णांक avail;
		काष्ठा dvb_ringbuffer *cibuf = &av7110->ci_wbuffer;

		avail = dvb_ringbuffer_avail(cibuf);
		अगर (avail <= 2) अणु
			iwdebi(av7110, DEBINOSWAP, IRQ_STATE_EXT, 0, 2);
			iwdebi(av7110, DEBINOSWAP, TX_LEN, 0, 2);
			iwdebi(av7110, DEBINOSWAP, TX_BUFF, 0, 2);
			अवरोध;
		पूर्ण
		len = DVB_RINGBUFFER_PEEK(cibuf, 0) << 8;
		len |= DVB_RINGBUFFER_PEEK(cibuf, 1);
		अगर (avail < len + 2) अणु
			iwdebi(av7110, DEBINOSWAP, IRQ_STATE_EXT, 0, 2);
			iwdebi(av7110, DEBINOSWAP, TX_LEN, 0, 2);
			iwdebi(av7110, DEBINOSWAP, TX_BUFF, 0, 2);
			अवरोध;
		पूर्ण
		DVB_RINGBUFFER_SKIP(cibuf, 2);

		dvb_ringbuffer_पढ़ो(cibuf, av7110->debi_virt, len);

		iwdebi(av7110, DEBINOSWAP, TX_LEN, len, 2);
		iwdebi(av7110, DEBINOSWAP, IRQ_STATE_EXT, len, 2);
		dprपूर्णांकk(8, "DMA: CI\n");
		start_debi_dma(av7110, DEBI_WRITE, DPRAM_BASE + txbuf, len);
		spin_unlock(&av7110->debilock);
		wake_up(&cibuf->queue);
		वापस;
	पूर्ण

	हाल DATA_MPEG_PLAY:
		अगर (!av7110->playing) अणु
			iwdebi(av7110, DEBINOSWAP, IRQ_STATE_EXT, 0, 2);
			iwdebi(av7110, DEBINOSWAP, TX_LEN, 0, 2);
			iwdebi(av7110, DEBINOSWAP, TX_BUFF, 0, 2);
			अवरोध;
		पूर्ण
		len = 0;
		अगर (av7110->debitype & 0x100) अणु
			spin_lock(&av7110->aout.lock);
			len = av7110_pes_play(av7110->debi_virt, &av7110->aout, 2048);
			spin_unlock(&av7110->aout.lock);
		पूर्ण
		अगर (len <= 0 && (av7110->debitype & 0x200)
		    &&av7110->videostate.play_state != VIDEO_FREEZED) अणु
			spin_lock(&av7110->avout.lock);
			len = av7110_pes_play(av7110->debi_virt, &av7110->avout, 2048);
			spin_unlock(&av7110->avout.lock);
		पूर्ण
		अगर (len <= 0) अणु
			iwdebi(av7110, DEBINOSWAP, IRQ_STATE_EXT, 0, 2);
			iwdebi(av7110, DEBINOSWAP, TX_LEN, 0, 2);
			iwdebi(av7110, DEBINOSWAP, TX_BUFF, 0, 2);
			अवरोध;
		पूर्ण
		dprपूर्णांकk(8, "GPIO0 PES_PLAY len=%04x\n", len);
		iwdebi(av7110, DEBINOSWAP, TX_LEN, len, 2);
		iwdebi(av7110, DEBINOSWAP, IRQ_STATE_EXT, len, 2);
		dprपूर्णांकk(8, "DMA: MPEG_PLAY\n");
		start_debi_dma(av7110, DEBI_WRITE, DPRAM_BASE + txbuf, len);
		spin_unlock(&av7110->debilock);
		वापस;

	हाल DATA_BMP_LOAD:
		len = av7110->debilen;
		dprपूर्णांकk(8, "gpio DATA_BMP_LOAD len %d\n", len);
		अगर (!len) अणु
			av7110->bmp_state = BMP_LOADED;
			iwdebi(av7110, DEBINOSWAP, IRQ_STATE_EXT, 0, 2);
			iwdebi(av7110, DEBINOSWAP, TX_LEN, 0, 2);
			iwdebi(av7110, DEBINOSWAP, TX_BUFF, 0, 2);
			wake_up(&av7110->bmpq);
			dprपूर्णांकk(8, "gpio DATA_BMP_LOAD done\n");
			अवरोध;
		पूर्ण
		अगर (len > av7110->bmplen)
			len = av7110->bmplen;
		अगर (len > 2 * 1024)
			len = 2 * 1024;
		iwdebi(av7110, DEBINOSWAP, TX_LEN, len, 2);
		iwdebi(av7110, DEBINOSWAP, IRQ_STATE_EXT, len, 2);
		स_नकल(av7110->debi_virt, av7110->bmpbuf+av7110->bmpp, len);
		av7110->bmpp += len;
		av7110->bmplen -= len;
		dprपूर्णांकk(8, "gpio DATA_BMP_LOAD DMA len %d\n", len);
		start_debi_dma(av7110, DEBI_WRITE, DPRAM_BASE+txbuf, len);
		spin_unlock(&av7110->debilock);
		वापस;

	हाल DATA_CI_GET:
	हाल DATA_COMMON_INTERFACE:
	हाल DATA_FSECTION:
	हाल DATA_IPMPE:
	हाल DATA_PIPING:
		अगर (!len || len > 4 * 1024) अणु
			iwdebi(av7110, DEBINOSWAP, RX_BUFF, 0, 2);
			अवरोध;
		पूर्ण
		fallthrough;

	हाल DATA_TS_RECORD:
	हाल DATA_PES_RECORD:
		dprपूर्णांकk(8, "DMA: TS_REC etc.\n");
		start_debi_dma(av7110, DEBI_READ, DPRAM_BASE+rxbuf, len);
		spin_unlock(&av7110->debilock);
		वापस;

	हाल DATA_DEBUG_MESSAGE:
		अगर (!len || len > 0xff) अणु
			iwdebi(av7110, DEBINOSWAP, RX_BUFF, 0, 2);
			अवरोध;
		पूर्ण
		start_debi_dma(av7110, DEBI_READ, Reserved, len);
		spin_unlock(&av7110->debilock);
		वापस;

	हाल DATA_IRCOMMAND:
#अगर IS_ENABLED(CONFIG_DVB_AV7110_IR)
		av7110_ir_handler(av7110,
				  swahw32(irdebi(av7110, DEBINOSWAP, Reserved,
						 0, 4)));
#पूर्ण_अगर
		iwdebi(av7110, DEBINOSWAP, RX_BUFF, 0, 2);
		अवरोध;

	शेष:
		prपूर्णांकk("dvb-ttpci: gpioirq unknown type=%d len=%d\n",
		       av7110->debitype, av7110->debilen);
		अवरोध;
	पूर्ण
	av7110->debitype = -1;
	ARM_ClearMailBox(av7110);
	spin_unlock(&av7110->debilock);
पूर्ण


#अगर_घोषित CONFIG_DVB_AV7110_OSD
अटल पूर्णांक dvb_osd_ioctl(काष्ठा file *file,
			 अचिन्हित पूर्णांक cmd, व्योम *parg)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा av7110 *av7110 = dvbdev->priv;

	dprपूर्णांकk(4, "%p\n", av7110);

	अगर (cmd == OSD_SEND_CMD)
		वापस av7110_osd_cmd(av7110, (osd_cmd_t *) parg);
	अगर (cmd == OSD_GET_CAPABILITY)
		वापस av7110_osd_capability(av7110, (osd_cap_t *) parg);

	वापस -EINVAL;
पूर्ण


अटल स्थिर काष्ठा file_operations dvb_osd_fops = अणु
	.owner		= THIS_MODULE,
	.unlocked_ioctl	= dvb_generic_ioctl,
	.खोलो		= dvb_generic_खोलो,
	.release	= dvb_generic_release,
	.llseek		= noop_llseek,
पूर्ण;

अटल काष्ठा dvb_device dvbdev_osd = अणु
	.priv		= शून्य,
	.users		= 1,
	.ग_लिखोrs	= 1,
	.fops		= &dvb_osd_fops,
	.kernel_ioctl	= dvb_osd_ioctl,
पूर्ण;
#पूर्ण_अगर /* CONFIG_DVB_AV7110_OSD */


अटल अंतरभूत पूर्णांक SetPIDs(काष्ठा av7110 *av7110, u16 vpid, u16 apid, u16 ttpid,
			  u16 subpid, u16 pcrpid)
अणु
	u16 aflags = 0;

	dprपूर्णांकk(4, "%p\n", av7110);

	अगर (vpid == 0x1fff || apid == 0x1fff ||
	    ttpid == 0x1fff || subpid == 0x1fff || pcrpid == 0x1fff) अणु
		vpid = apid = ttpid = subpid = pcrpid = 0;
		av7110->pids[DMX_PES_VIDEO] = 0;
		av7110->pids[DMX_PES_AUDIO] = 0;
		av7110->pids[DMX_PES_TELETEXT] = 0;
		av7110->pids[DMX_PES_PCR] = 0;
	पूर्ण

	अगर (av7110->audiostate.bypass_mode)
		aflags |= 0x8000;

	वापस av7110_fw_cmd(av7110, COMTYPE_PIDFILTER, MultiPID, 6,
			     pcrpid, vpid, apid, ttpid, subpid, aflags);
पूर्ण

पूर्णांक ChangePIDs(काष्ठा av7110 *av7110, u16 vpid, u16 apid, u16 ttpid,
		u16 subpid, u16 pcrpid)
अणु
	पूर्णांक ret = 0;
	dprपूर्णांकk(4, "%p\n", av7110);

	अगर (mutex_lock_पूर्णांकerruptible(&av7110->pid_mutex))
		वापस -ERESTARTSYS;

	अगर (!(vpid & 0x8000))
		av7110->pids[DMX_PES_VIDEO] = vpid;
	अगर (!(apid & 0x8000))
		av7110->pids[DMX_PES_AUDIO] = apid;
	अगर (!(ttpid & 0x8000))
		av7110->pids[DMX_PES_TELETEXT] = ttpid;
	अगर (!(pcrpid & 0x8000))
		av7110->pids[DMX_PES_PCR] = pcrpid;

	av7110->pids[DMX_PES_SUBTITLE] = 0;

	अगर (av7110->fe_synced) अणु
		pcrpid = av7110->pids[DMX_PES_PCR];
		ret = SetPIDs(av7110, vpid, apid, ttpid, subpid, pcrpid);
	पूर्ण

	mutex_unlock(&av7110->pid_mutex);
	वापस ret;
पूर्ण


/******************************************************************************
 * hardware filter functions
 ******************************************************************************/

अटल पूर्णांक StartHWFilter(काष्ठा dvb_demux_filter *dvbdmxfilter)
अणु
	काष्ठा dvb_demux_feed *dvbdmxfeed = dvbdmxfilter->feed;
	काष्ठा av7110 *av7110 = dvbdmxfeed->demux->priv;
	u16 buf[20];
	पूर्णांक ret, i;
	u16 handle;
//	u16 mode = 0x0320;
	u16 mode = 0xb96a;

	dprपूर्णांकk(4, "%p\n", av7110);

	अगर (av7110->full_ts)
		वापस 0;

	अगर (dvbdmxfilter->type == DMX_TYPE_SEC) अणु
		अगर (hw_sections) अणु
			buf[4] = (dvbdmxfilter->filter.filter_value[0] << 8) |
				dvbdmxfilter->maskandmode[0];
			क्रम (i = 3; i < 18; i++)
				buf[i + 4 - 2] =
					(dvbdmxfilter->filter.filter_value[i] << 8) |
					dvbdmxfilter->maskandmode[i];
			mode = 4;
		पूर्ण
	पूर्ण अन्यथा अगर ((dvbdmxfeed->ts_type & TS_PACKET) &&
		   !(dvbdmxfeed->ts_type & TS_PAYLOAD_ONLY)) अणु
		av7110_p2t_init(&av7110->p2t_filter[dvbdmxfilter->index], dvbdmxfeed);
	पूर्ण

	buf[0] = (COMTYPE_PID_FILTER << 8) + AddPIDFilter;
	buf[1] = 16;
	buf[2] = dvbdmxfeed->pid;
	buf[3] = mode;

	ret = av7110_fw_request(av7110, buf, 20, &handle, 1);
	अगर (ret != 0 || handle >= 32) अणु
		prपूर्णांकk(KERN_ERR "dvb-ttpci: %s error  buf %04x %04x %04x %04x  ret %d  handle %04x\n",
				__func__, buf[0], buf[1], buf[2], buf[3],
				ret, handle);
		dvbdmxfilter->hw_handle = 0xffff;
		अगर (!ret)
			ret = -1;
		वापस ret;
	पूर्ण

	av7110->handle2filter[handle] = dvbdmxfilter;
	dvbdmxfilter->hw_handle = handle;

	वापस ret;
पूर्ण

अटल पूर्णांक StopHWFilter(काष्ठा dvb_demux_filter *dvbdmxfilter)
अणु
	काष्ठा av7110 *av7110 = dvbdmxfilter->feed->demux->priv;
	u16 buf[3];
	u16 answ[2];
	पूर्णांक ret;
	u16 handle;

	dprपूर्णांकk(4, "%p\n", av7110);

	अगर (av7110->full_ts)
		वापस 0;

	handle = dvbdmxfilter->hw_handle;
	अगर (handle >= 32) अणु
		prपूर्णांकk("%s tried to stop invalid filter %04x, filter type = %x\n",
				__func__, handle, dvbdmxfilter->type);
		वापस -EINVAL;
	पूर्ण

	av7110->handle2filter[handle] = शून्य;

	buf[0] = (COMTYPE_PID_FILTER << 8) + DelPIDFilter;
	buf[1] = 1;
	buf[2] = handle;
	ret = av7110_fw_request(av7110, buf, 3, answ, 2);
	अगर (ret != 0 || answ[1] != handle) अणु
		prपूर्णांकk(KERN_ERR "dvb-ttpci: %s error  cmd %04x %04x %04x  ret %x  resp %04x %04x  pid %d\n",
				__func__, buf[0], buf[1], buf[2], ret,
				answ[0], answ[1], dvbdmxfilter->feed->pid);
		अगर (!ret)
			ret = -1;
	पूर्ण
	वापस ret;
पूर्ण


अटल पूर्णांक dvb_feed_start_pid(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	काष्ठा dvb_demux *dvbdmx = dvbdmxfeed->demux;
	काष्ठा av7110 *av7110 = dvbdmx->priv;
	u16 *pid = dvbdmx->pids, npids[5];
	पूर्णांक i;
	पूर्णांक ret = 0;

	dprपूर्णांकk(4, "%p\n", av7110);

	npids[0] = npids[1] = npids[2] = npids[3] = npids[4] = 0xffff;
	i = dvbdmxfeed->pes_type;
	npids[i] = (pid[i]&0x8000) ? 0 : pid[i];
	अगर ((i == 2) && npids[i] && (dvbdmxfeed->ts_type & TS_PACKET)) अणु
		npids[i] = 0;
		ret = ChangePIDs(av7110, npids[1], npids[0], npids[2], npids[3], npids[4]);
		अगर (!ret)
			ret = StartHWFilter(dvbdmxfeed->filter);
		वापस ret;
	पूर्ण
	अगर (dvbdmxfeed->pes_type <= 2 || dvbdmxfeed->pes_type == 4) अणु
		ret = ChangePIDs(av7110, npids[1], npids[0], npids[2], npids[3], npids[4]);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (dvbdmxfeed->pes_type < 2 && npids[0])
		अगर (av7110->fe_synced)
		अणु
			ret = av7110_fw_cmd(av7110, COMTYPE_PIDFILTER, Scan, 0);
			अगर (ret)
				वापस ret;
		पूर्ण

	अगर ((dvbdmxfeed->ts_type & TS_PACKET) && !av7110->full_ts) अणु
		अगर (dvbdmxfeed->pes_type == 0 && !(dvbdmx->pids[0] & 0x8000))
			ret = av7110_av_start_record(av7110, RP_AUDIO, dvbdmxfeed);
		अगर (dvbdmxfeed->pes_type == 1 && !(dvbdmx->pids[1] & 0x8000))
			ret = av7110_av_start_record(av7110, RP_VIDEO, dvbdmxfeed);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक dvb_feed_stop_pid(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	काष्ठा dvb_demux *dvbdmx = dvbdmxfeed->demux;
	काष्ठा av7110 *av7110 = dvbdmx->priv;
	u16 *pid = dvbdmx->pids, npids[5];
	पूर्णांक i;

	पूर्णांक ret = 0;

	dprपूर्णांकk(4, "%p\n", av7110);

	अगर (dvbdmxfeed->pes_type <= 1) अणु
		ret = av7110_av_stop(av7110, dvbdmxfeed->pes_type ?  RP_VIDEO : RP_AUDIO);
		अगर (ret)
			वापस ret;
		अगर (!av7110->rec_mode)
			dvbdmx->recording = 0;
		अगर (!av7110->playing)
			dvbdmx->playing = 0;
	पूर्ण
	npids[0] = npids[1] = npids[2] = npids[3] = npids[4] = 0xffff;
	i = dvbdmxfeed->pes_type;
	चयन (i) अणु
	हाल 2: //teletext
		अगर (dvbdmxfeed->ts_type & TS_PACKET)
			ret = StopHWFilter(dvbdmxfeed->filter);
		npids[2] = 0;
		अवरोध;
	हाल 0:
	हाल 1:
	हाल 4:
		अगर (!pids_off)
			वापस 0;
		npids[i] = (pid[i]&0x8000) ? 0 : pid[i];
		अवरोध;
	पूर्ण
	अगर (!ret)
		ret = ChangePIDs(av7110, npids[1], npids[0], npids[2], npids[3], npids[4]);
	वापस ret;
पूर्ण

अटल पूर्णांक av7110_start_feed(काष्ठा dvb_demux_feed *feed)
अणु
	काष्ठा dvb_demux *demux = feed->demux;
	काष्ठा av7110 *av7110 = demux->priv;
	पूर्णांक ret = 0;

	dprपूर्णांकk(4, "%p\n", av7110);

	अगर (!demux->dmx.frontend)
		वापस -EINVAL;

	अगर (!av7110->full_ts && feed->pid > 0x1fff)
		वापस -EINVAL;

	अगर (feed->type == DMX_TYPE_TS) अणु
		अगर ((feed->ts_type & TS_DECODER) &&
		    (feed->pes_type <= DMX_PES_PCR)) अणु
			चयन (demux->dmx.frontend->source) अणु
			हाल DMX_MEMORY_FE:
				अगर (feed->ts_type & TS_DECODER)
				       अगर (feed->pes_type < 2 &&
					   !(demux->pids[0] & 0x8000) &&
					   !(demux->pids[1] & 0x8000)) अणु
					       dvb_ringbuffer_flush_spinlock_wakeup(&av7110->avout);
					       dvb_ringbuffer_flush_spinlock_wakeup(&av7110->aout);
					       ret = av7110_av_start_play(av7110,RP_AV);
					       अगर (!ret)
						       demux->playing = 1;
					पूर्ण
				अवरोध;
			शेष:
				ret = dvb_feed_start_pid(feed);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर ((feed->ts_type & TS_PACKET) &&
			   (demux->dmx.frontend->source != DMX_MEMORY_FE)) अणु
			ret = StartHWFilter(feed->filter);
		पूर्ण
	पूर्ण

	अगर (av7110->full_ts) अणु
		budget_start_feed(feed);
		वापस ret;
	पूर्ण

	अगर (feed->type == DMX_TYPE_SEC) अणु
		पूर्णांक i;

		क्रम (i = 0; i < demux->filternum; i++) अणु
			अगर (demux->filter[i].state != DMX_STATE_READY)
				जारी;
			अगर (demux->filter[i].type != DMX_TYPE_SEC)
				जारी;
			अगर (demux->filter[i].filter.parent != &feed->feed.sec)
				जारी;
			demux->filter[i].state = DMX_STATE_GO;
			अगर (demux->dmx.frontend->source != DMX_MEMORY_FE) अणु
				ret = StartHWFilter(&demux->filter[i]);
				अगर (ret)
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण


अटल पूर्णांक av7110_stop_feed(काष्ठा dvb_demux_feed *feed)
अणु
	काष्ठा dvb_demux *demux = feed->demux;
	काष्ठा av7110 *av7110 = demux->priv;
	पूर्णांक i, rc, ret = 0;
	dprपूर्णांकk(4, "%p\n", av7110);

	अगर (feed->type == DMX_TYPE_TS) अणु
		अगर (feed->ts_type & TS_DECODER) अणु
			अगर (feed->pes_type >= DMX_PES_OTHER ||
			    !demux->pesfilter[feed->pes_type])
				वापस -EINVAL;
			demux->pids[feed->pes_type] |= 0x8000;
			demux->pesfilter[feed->pes_type] = शून्य;
		पूर्ण
		अगर (feed->ts_type & TS_DECODER &&
		    feed->pes_type < DMX_PES_OTHER) अणु
			ret = dvb_feed_stop_pid(feed);
		पूर्ण अन्यथा
			अगर ((feed->ts_type & TS_PACKET) &&
			    (demux->dmx.frontend->source != DMX_MEMORY_FE))
				ret = StopHWFilter(feed->filter);
	पूर्ण

	अगर (av7110->full_ts) अणु
		budget_stop_feed(feed);
		वापस ret;
	पूर्ण

	अगर (feed->type == DMX_TYPE_SEC) अणु
		क्रम (i = 0; i<demux->filternum; i++) अणु
			अगर (demux->filter[i].state == DMX_STATE_GO &&
			    demux->filter[i].filter.parent == &feed->feed.sec) अणु
				demux->filter[i].state = DMX_STATE_READY;
				अगर (demux->dmx.frontend->source != DMX_MEMORY_FE) अणु
					rc = StopHWFilter(&demux->filter[i]);
					अगर (!ret)
						ret = rc;
					/* keep going, stop as many filters as possible */
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण


अटल व्योम restart_feeds(काष्ठा av7110 *av7110)
अणु
	काष्ठा dvb_demux *dvbdmx = &av7110->demux;
	काष्ठा dvb_demux_feed *feed;
	पूर्णांक mode;
	पूर्णांक feeding;
	पूर्णांक i, j;

	dprपूर्णांकk(4, "%p\n", av7110);

	mode = av7110->playing;
	av7110->playing = 0;
	av7110->rec_mode = 0;

	feeding = av7110->feeding1; /* full_ts mod */

	क्रम (i = 0; i < dvbdmx->feednum; i++) अणु
		feed = &dvbdmx->feed[i];
		अगर (feed->state == DMX_STATE_GO) अणु
			अगर (feed->type == DMX_TYPE_SEC) अणु
				क्रम (j = 0; j < dvbdmx->filternum; j++) अणु
					अगर (dvbdmx->filter[j].type != DMX_TYPE_SEC)
						जारी;
					अगर (dvbdmx->filter[j].filter.parent != &feed->feed.sec)
						जारी;
					अगर (dvbdmx->filter[j].state == DMX_STATE_GO)
						dvbdmx->filter[j].state = DMX_STATE_READY;
				पूर्ण
			पूर्ण
			av7110_start_feed(feed);
		पूर्ण
	पूर्ण

	av7110->feeding1 = feeding; /* full_ts mod */

	अगर (mode)
		av7110_av_start_play(av7110, mode);
पूर्ण

अटल पूर्णांक dvb_get_stc(काष्ठा dmx_demux *demux, अचिन्हित पूर्णांक num,
		       uपूर्णांक64_t *stc, अचिन्हित पूर्णांक *base)
अणु
	पूर्णांक ret;
	u16 fwstc[4];
	u16 tag = ((COMTYPE_REQUEST << 8) + ReqSTC);
	काष्ठा dvb_demux *dvbdemux;
	काष्ठा av7110 *av7110;

	/* poपूर्णांकer casting paranoia... */
	BUG_ON(!demux);
	dvbdemux = demux->priv;
	BUG_ON(!dvbdemux);
	av7110 = dvbdemux->priv;

	dprपूर्णांकk(4, "%p\n", av7110);

	अगर (num != 0)
		वापस -EINVAL;

	ret = av7110_fw_request(av7110, &tag, 0, fwstc, 4);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "%s: av7110_fw_request error\n", __func__);
		वापस ret;
	पूर्ण
	dprपूर्णांकk(2, "fwstc = %04hx %04hx %04hx %04hx\n",
		fwstc[0], fwstc[1], fwstc[2], fwstc[3]);

	*stc =	(((uपूर्णांक64_t) ((fwstc[3] & 0x8000) >> 15)) << 32) |
		(((uपूर्णांक64_t)  fwstc[1]) << 16) | ((uपूर्णांक64_t) fwstc[0]);
	*base = 1;

	dprपूर्णांकk(4, "stc = %lu\n", (अचिन्हित दीर्घ)*stc);

	वापस 0;
पूर्ण


/******************************************************************************
 * SEC device file operations
 ******************************************************************************/


अटल पूर्णांक av7110_set_tone(काष्ठा dvb_frontend *fe, क्रमागत fe_sec_tone_mode tone)
अणु
	काष्ठा av7110* av7110 = fe->dvb->priv;

	चयन (tone) अणु
	हाल SEC_TONE_ON:
		वापस Set22K(av7110, 1);

	हाल SEC_TONE_OFF:
		वापस Set22K(av7110, 0);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक av7110_diseqc_send_master_cmd(काष्ठा dvb_frontend* fe,
					 काष्ठा dvb_diseqc_master_cmd* cmd)
अणु
	काष्ठा av7110* av7110 = fe->dvb->priv;

	वापस av7110_diseqc_send(av7110, cmd->msg_len, cmd->msg, -1);
पूर्ण

अटल पूर्णांक av7110_diseqc_send_burst(काष्ठा dvb_frontend* fe,
				    क्रमागत fe_sec_mini_cmd minicmd)
अणु
	काष्ठा av7110* av7110 = fe->dvb->priv;

	वापस av7110_diseqc_send(av7110, 0, शून्य, minicmd);
पूर्ण

/* simplअगरied code from budget-core.c */
अटल पूर्णांक stop_ts_capture(काष्ठा av7110 *budget)
अणु
	dprपूर्णांकk(2, "budget: %p\n", budget);

	अगर (--budget->feeding1)
		वापस budget->feeding1;
	saa7146_ग_लिखो(budget->dev, MC1, MASK_20);	/* DMA3 off */
	SAA7146_IER_DISABLE(budget->dev, MASK_10);
	SAA7146_ISR_CLEAR(budget->dev, MASK_10);
	वापस 0;
पूर्ण

अटल पूर्णांक start_ts_capture(काष्ठा av7110 *budget)
अणु
	अचिन्हित y;

	dprपूर्णांकk(2, "budget: %p\n", budget);

	अगर (budget->feeding1)
		वापस ++budget->feeding1;
	क्रम (y = 0; y < TS_HEIGHT; y++)
		स_रखो(budget->grabbing + y * TS_WIDTH, 0x00, TS_WIDTH);
	budget->ttbp = 0;
	SAA7146_ISR_CLEAR(budget->dev, MASK_10);  /* VPE */
	SAA7146_IER_ENABLE(budget->dev, MASK_10); /* VPE */
	saa7146_ग_लिखो(budget->dev, MC1, (MASK_04 | MASK_20)); /* DMA3 on */
	वापस ++budget->feeding1;
पूर्ण

अटल पूर्णांक budget_start_feed(काष्ठा dvb_demux_feed *feed)
अणु
	काष्ठा dvb_demux *demux = feed->demux;
	काष्ठा av7110 *budget = demux->priv;
	पूर्णांक status;

	dprपूर्णांकk(2, "av7110: %p\n", budget);

	spin_lock(&budget->feedlock1);
	feed->pusi_seen = false; /* have a clean section start */
	status = start_ts_capture(budget);
	spin_unlock(&budget->feedlock1);
	वापस status;
पूर्ण

अटल पूर्णांक budget_stop_feed(काष्ठा dvb_demux_feed *feed)
अणु
	काष्ठा dvb_demux *demux = feed->demux;
	काष्ठा av7110 *budget = demux->priv;
	पूर्णांक status;

	dprपूर्णांकk(2, "budget: %p\n", budget);

	spin_lock(&budget->feedlock1);
	status = stop_ts_capture(budget);
	spin_unlock(&budget->feedlock1);
	वापस status;
पूर्ण

अटल व्योम vpeirq(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा av7110 *budget = from_tasklet(budget, t, vpe_tasklet);
	u8 *mem = (u8 *) (budget->grabbing);
	u32 olddma = budget->ttbp;
	u32 newdma = saa7146_पढ़ो(budget->dev, PCI_VDP3);
	काष्ठा dvb_demux *demux = budget->full_ts ? &budget->demux : &budget->demux1;

	/* nearest lower position भागisible by 188 */
	newdma -= newdma % 188;

	अगर (newdma >= TS_BUFLEN)
		वापस;

	budget->ttbp = newdma;

	अगर (!budget->feeding1 || (newdma == olddma))
		वापस;

	/* Ensure streamed PCI data is synced to CPU */
	dma_sync_sg_क्रम_cpu(&budget->dev->pci->dev, budget->pt.slist,
			    budget->pt.nents, DMA_FROM_DEVICE);

#अगर 0
	/* track rps1 activity */
	prपूर्णांकk("vpeirq: %02x Event Counter 1 0x%04x\n",
	       mem[olddma],
	       saa7146_पढ़ो(budget->dev, EC1R) & 0x3fff);
#पूर्ण_अगर

	अगर (newdma > olddma)
		/* no wraparound, dump olddma..newdma */
		dvb_dmx_swfilter_packets(demux, mem + olddma, (newdma - olddma) / 188);
	अन्यथा अणु
		/* wraparound, dump olddma..buflen and 0..newdma */
		dvb_dmx_swfilter_packets(demux, mem + olddma, (TS_BUFLEN - olddma) / 188);
		dvb_dmx_swfilter_packets(demux, mem, newdma / 188);
	पूर्ण
पूर्ण

अटल पूर्णांक av7110_रेजिस्टर(काष्ठा av7110 *av7110)
अणु
	पूर्णांक ret, i;
	काष्ठा dvb_demux *dvbdemux = &av7110->demux;
	काष्ठा dvb_demux *dvbdemux1 = &av7110->demux1;

	dprपूर्णांकk(4, "%p\n", av7110);

	अगर (av7110->रेजिस्टरed)
		वापस -1;

	av7110->रेजिस्टरed = 1;

	dvbdemux->priv = (व्योम *) av7110;

	क्रम (i = 0; i < 32; i++)
		av7110->handle2filter[i] = शून्य;

	dvbdemux->filternum = (av7110->full_ts) ? 256 : 32;
	dvbdemux->feednum = (av7110->full_ts) ? 256 : 32;
	dvbdemux->start_feed = av7110_start_feed;
	dvbdemux->stop_feed = av7110_stop_feed;
	dvbdemux->ग_लिखो_to_decoder = av7110_ग_लिखो_to_decoder;
	dvbdemux->dmx.capabilities = (DMX_TS_FILTERING | DMX_SECTION_FILTERING |
				      DMX_MEMORY_BASED_FILTERING);

	dvb_dmx_init(&av7110->demux);
	av7110->demux.dmx.get_stc = dvb_get_stc;

	av7110->dmxdev.filternum = (av7110->full_ts) ? 256 : 32;
	av7110->dmxdev.demux = &dvbdemux->dmx;
	av7110->dmxdev.capabilities = 0;

	dvb_dmxdev_init(&av7110->dmxdev, &av7110->dvb_adapter);

	av7110->hw_frontend.source = DMX_FRONTEND_0;

	ret = dvbdemux->dmx.add_frontend(&dvbdemux->dmx, &av7110->hw_frontend);

	अगर (ret < 0)
		वापस ret;

	av7110->mem_frontend.source = DMX_MEMORY_FE;

	ret = dvbdemux->dmx.add_frontend(&dvbdemux->dmx, &av7110->mem_frontend);

	अगर (ret < 0)
		वापस ret;

	ret = dvbdemux->dmx.connect_frontend(&dvbdemux->dmx,
					     &av7110->hw_frontend);
	अगर (ret < 0)
		वापस ret;

	av7110_av_रेजिस्टर(av7110);
	av7110_ca_रेजिस्टर(av7110);

#अगर_घोषित CONFIG_DVB_AV7110_OSD
	dvb_रेजिस्टर_device(&av7110->dvb_adapter, &av7110->osd_dev,
			    &dvbdev_osd, av7110, DVB_DEVICE_OSD, 0);
#पूर्ण_अगर

	dvb_net_init(&av7110->dvb_adapter, &av7110->dvb_net, &dvbdemux->dmx);

	अगर (budgetpatch) अणु
		/* initialize software demux1 without its own frontend
		 * demux1 hardware is connected to frontend0 of demux0
		 */
		dvbdemux1->priv = (व्योम *) av7110;

		dvbdemux1->filternum = 256;
		dvbdemux1->feednum = 256;
		dvbdemux1->start_feed = budget_start_feed;
		dvbdemux1->stop_feed = budget_stop_feed;
		dvbdemux1->ग_लिखो_to_decoder = शून्य;

		dvbdemux1->dmx.capabilities = (DMX_TS_FILTERING | DMX_SECTION_FILTERING |
					       DMX_MEMORY_BASED_FILTERING);

		dvb_dmx_init(&av7110->demux1);

		av7110->dmxdev1.filternum = 256;
		av7110->dmxdev1.demux = &dvbdemux1->dmx;
		av7110->dmxdev1.capabilities = 0;

		dvb_dmxdev_init(&av7110->dmxdev1, &av7110->dvb_adapter);

		dvb_net_init(&av7110->dvb_adapter, &av7110->dvb_net1, &dvbdemux1->dmx);
		prपूर्णांकk("dvb-ttpci: additional demux1 for budget-patch registered\n");
	पूर्ण
	वापस 0;
पूर्ण


अटल व्योम dvb_unरेजिस्टर(काष्ठा av7110 *av7110)
अणु
	काष्ठा dvb_demux *dvbdemux = &av7110->demux;
	काष्ठा dvb_demux *dvbdemux1 = &av7110->demux1;

	dprपूर्णांकk(4, "%p\n", av7110);

	अगर (!av7110->रेजिस्टरed)
		वापस;

	अगर (budgetpatch) अणु
		dvb_net_release(&av7110->dvb_net1);
		dvbdemux->dmx.बंद(&dvbdemux1->dmx);
		dvb_dmxdev_release(&av7110->dmxdev1);
		dvb_dmx_release(&av7110->demux1);
	पूर्ण

	dvb_net_release(&av7110->dvb_net);

	dvbdemux->dmx.बंद(&dvbdemux->dmx);
	dvbdemux->dmx.हटाओ_frontend(&dvbdemux->dmx, &av7110->hw_frontend);
	dvbdemux->dmx.हटाओ_frontend(&dvbdemux->dmx, &av7110->mem_frontend);

	dvb_dmxdev_release(&av7110->dmxdev);
	dvb_dmx_release(&av7110->demux);

	अगर (av7110->fe != शून्य) अणु
		dvb_unरेजिस्टर_frontend(av7110->fe);
		dvb_frontend_detach(av7110->fe);
	पूर्ण
	dvb_unरेजिस्टर_device(av7110->osd_dev);
	av7110_av_unरेजिस्टर(av7110);
	av7110_ca_unरेजिस्टर(av7110);
पूर्ण


/****************************************************************************
 * I2C client commands
 ****************************************************************************/

पूर्णांक i2c_ग_लिखोreg(काष्ठा av7110 *av7110, u8 id, u8 reg, u8 val)
अणु
	u8 msg[2] = अणु reg, val पूर्ण;
	काष्ठा i2c_msg msgs;

	msgs.flags = 0;
	msgs.addr = id / 2;
	msgs.len = 2;
	msgs.buf = msg;
	वापस i2c_transfer(&av7110->i2c_adap, &msgs, 1);
पूर्ण

u8 i2c_पढ़ोreg(काष्ठा av7110 *av7110, u8 id, u8 reg)
अणु
	u8 mm1[] = अणु0x00पूर्ण;
	u8 mm2[] = अणु0x00पूर्ण;
	काष्ठा i2c_msg msgs[2];

	msgs[0].flags = 0;
	msgs[1].flags = I2C_M_RD;
	msgs[0].addr = msgs[1].addr = id / 2;
	mm1[0] = reg;
	msgs[0].len = 1; msgs[1].len = 1;
	msgs[0].buf = mm1; msgs[1].buf = mm2;
	i2c_transfer(&av7110->i2c_adap, msgs, 2);

	वापस mm2[0];
पूर्ण

/****************************************************************************
 * INITIALIZATION
 ****************************************************************************/


अटल पूर्णांक check_firmware(काष्ठा av7110* av7110)
अणु
	u32 crc = 0, len = 0;
	अचिन्हित अक्षर *ptr;

	/* check क्रम firmware magic */
	ptr = av7110->bin_fw;
	अगर (ptr[0] != 'A' || ptr[1] != 'V' ||
	    ptr[2] != 'F' || ptr[3] != 'W') अणु
		prपूर्णांकk("dvb-ttpci: this is not an av7110 firmware\n");
		वापस -EINVAL;
	पूर्ण
	ptr += 4;

	/* check dpram file */
	crc = get_unaligned_be32(ptr);
	ptr += 4;
	len = get_unaligned_be32(ptr);
	ptr += 4;
	अगर (len >= 512) अणु
		prपूर्णांकk("dvb-ttpci: dpram file is way too big.\n");
		वापस -EINVAL;
	पूर्ण
	अगर (crc != crc32_le(0, ptr, len)) अणु
		prपूर्णांकk("dvb-ttpci: crc32 of dpram file does not match.\n");
		वापस -EINVAL;
	पूर्ण
	av7110->bin_dpram = ptr;
	av7110->size_dpram = len;
	ptr += len;

	/* check root file */
	crc = get_unaligned_be32(ptr);
	ptr += 4;
	len = get_unaligned_be32(ptr);
	ptr += 4;

	अगर (len <= 200000 || len >= 300000 ||
	    len > ((av7110->bin_fw + av7110->size_fw) - ptr)) अणु
		prपूर्णांकk("dvb-ttpci: root file has strange size (%d). aborting.\n", len);
		वापस -EINVAL;
	पूर्ण
	अगर( crc != crc32_le(0, ptr, len)) अणु
		prपूर्णांकk("dvb-ttpci: crc32 of root file does not match.\n");
		वापस -EINVAL;
	पूर्ण
	av7110->bin_root = ptr;
	av7110->size_root = len;
	वापस 0;
पूर्ण

अटल व्योम put_firmware(काष्ठा av7110* av7110)
अणु
	vमुक्त(av7110->bin_fw);
पूर्ण

अटल पूर्णांक get_firmware(काष्ठा av7110* av7110)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा firmware *fw;

	/* request the av7110 firmware, this will block until someone uploads it */
	ret = request_firmware(&fw, "dvb-ttpci-01.fw", &av7110->dev->pci->dev);
	अगर (ret) अणु
		अगर (ret == -ENOENT) अणु
			prपूर्णांकk(KERN_ERR "dvb-ttpci: could not load firmware, file not found: dvb-ttpci-01.fw\n");
			prपूर्णांकk(KERN_ERR "dvb-ttpci: usually this should be in /usr/lib/hotplug/firmware or /lib/firmware\n");
			prपूर्णांकk(KERN_ERR "dvb-ttpci: and can be downloaded from https://linuxtv.org/download/dvb/firmware/\n");
		पूर्ण अन्यथा
			prपूर्णांकk(KERN_ERR "dvb-ttpci: cannot request firmware (error %i)\n",
			       ret);
		वापस -EINVAL;
	पूर्ण

	अगर (fw->size <= 200000) अणु
		prपूर्णांकk("dvb-ttpci: this firmware is way too small.\n");
		release_firmware(fw);
		वापस -EINVAL;
	पूर्ण

	/* check अगर the firmware is available */
	av7110->bin_fw = vदो_स्मृति(fw->size);
	अगर (शून्य == av7110->bin_fw) अणु
		dprपूर्णांकk(1, "out of memory\n");
		release_firmware(fw);
		वापस -ENOMEM;
	पूर्ण

	स_नकल(av7110->bin_fw, fw->data, fw->size);
	av7110->size_fw = fw->size;
	अगर ((ret = check_firmware(av7110)))
		vमुक्त(av7110->bin_fw);

	release_firmware(fw);
	वापस ret;
पूर्ण

अटल पूर्णांक alps_bsrv2_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा av7110* av7110 = fe->dvb->priv;
	u8 pwr = 0;
	u8 buf[4];
	काष्ठा i2c_msg msg = अणु .addr = 0x61, .flags = 0, .buf = buf, .len = माप(buf) पूर्ण;
	u32 भाग = (p->frequency + 479500) / 125;

	अगर (p->frequency > 2000000)
		pwr = 3;
	अन्यथा अगर (p->frequency > 1800000)
		pwr = 2;
	अन्यथा अगर (p->frequency > 1600000)
		pwr = 1;
	अन्यथा अगर (p->frequency > 1200000)
		pwr = 0;
	अन्यथा अगर (p->frequency >= 1100000)
		pwr = 1;
	अन्यथा
		pwr = 2;

	buf[0] = (भाग >> 8) & 0x7f;
	buf[1] = भाग & 0xff;
	buf[2] = ((भाग & 0x18000) >> 10) | 0x95;
	buf[3] = (pwr << 6) | 0x30;

	// NOTE: since we're using a prescaler of 2, we set the
	// भागisor frequency to 62.5kHz and भागide by 125 above

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer (&av7110->i2c_adap, &msg, 1) != 1)
		वापस -EIO;
	वापस 0;
पूर्ण

अटल काष्ठा ves1x93_config alps_bsrv2_config = अणु
	.demod_address = 0x08,
	.xin = 90100000UL,
	.invert_pwm = 0,
पूर्ण;

अटल पूर्णांक alps_tdbe2_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा av7110* av7110 = fe->dvb->priv;
	u32 भाग;
	u8 data[4];
	काष्ठा i2c_msg msg = अणु .addr = 0x62, .flags = 0, .buf = data, .len = माप(data) पूर्ण;

	भाग = (p->frequency + 35937500 + 31250) / 62500;

	data[0] = (भाग >> 8) & 0x7f;
	data[1] = भाग & 0xff;
	data[2] = 0x85 | ((भाग >> 10) & 0x60);
	data[3] = (p->frequency < 174000000 ? 0x88 : p->frequency < 470000000 ? 0x84 : 0x81);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(&av7110->i2c_adap, &msg, 1) != 1)
		वापस -EIO;
	वापस 0;
पूर्ण

अटल काष्ठा ves1820_config alps_tdbe2_config = अणु
	.demod_address = 0x09,
	.xin = 57840000UL,
	.invert = 1,
	.selagc = VES1820_SELAGC_SIGNAMPERR,
पूर्ण;




अटल पूर्णांक grundig_29504_451_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा av7110* av7110 = fe->dvb->priv;
	u32 भाग;
	u8 data[4];
	काष्ठा i2c_msg msg = अणु .addr = 0x61, .flags = 0, .buf = data, .len = माप(data) पूर्ण;

	भाग = p->frequency / 125;
	data[0] = (भाग >> 8) & 0x7f;
	data[1] = भाग & 0xff;
	data[2] = 0x8e;
	data[3] = 0x00;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(&av7110->i2c_adap, &msg, 1) != 1)
		वापस -EIO;
	वापस 0;
पूर्ण

अटल काष्ठा tda8083_config grundig_29504_451_config = अणु
	.demod_address = 0x68,
पूर्ण;



अटल पूर्णांक philips_cd1516_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा av7110* av7110 = fe->dvb->priv;
	u32 भाग;
	u32 f = p->frequency;
	u8 data[4];
	काष्ठा i2c_msg msg = अणु .addr = 0x61, .flags = 0, .buf = data, .len = माप(data) पूर्ण;

	भाग = (f + 36125000 + 31250) / 62500;

	data[0] = (भाग >> 8) & 0x7f;
	data[1] = भाग & 0xff;
	data[2] = 0x8e;
	data[3] = (f < 174000000 ? 0xa1 : f < 470000000 ? 0x92 : 0x34);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(&av7110->i2c_adap, &msg, 1) != 1)
		वापस -EIO;
	वापस 0;
पूर्ण

अटल काष्ठा ves1820_config philips_cd1516_config = अणु
	.demod_address = 0x09,
	.xin = 57840000UL,
	.invert = 1,
	.selagc = VES1820_SELAGC_SIGNAMPERR,
पूर्ण;



अटल पूर्णांक alps_tdlb7_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा av7110* av7110 = fe->dvb->priv;
	u32 भाग, pwr;
	u8 data[4];
	काष्ठा i2c_msg msg = अणु .addr = 0x60, .flags = 0, .buf = data, .len = माप(data) पूर्ण;

	भाग = (p->frequency + 36200000) / 166666;

	अगर (p->frequency <= 782000000)
		pwr = 1;
	अन्यथा
		pwr = 2;

	data[0] = (भाग >> 8) & 0x7f;
	data[1] = भाग & 0xff;
	data[2] = 0x85;
	data[3] = pwr << 6;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(&av7110->i2c_adap, &msg, 1) != 1)
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक alps_tdlb7_request_firmware(काष्ठा dvb_frontend* fe, स्थिर काष्ठा firmware **fw, अक्षर* name)
अणु
#अगर IS_ENABLED(CONFIG_DVB_SP8870)
	काष्ठा av7110* av7110 = fe->dvb->priv;

	वापस request_firmware(fw, name, &av7110->dev->pci->dev);
#अन्यथा
	वापस -EINVAL;
#पूर्ण_अगर
पूर्ण

अटल स्थिर काष्ठा sp8870_config alps_tdlb7_config = अणु

	.demod_address = 0x71,
	.request_firmware = alps_tdlb7_request_firmware,
पूर्ण;


अटल u8 nexusca_stv0297_inittab[] = अणु
	0x80, 0x01,
	0x80, 0x00,
	0x81, 0x01,
	0x81, 0x00,
	0x00, 0x09,
	0x01, 0x69,
	0x03, 0x00,
	0x04, 0x00,
	0x07, 0x00,
	0x08, 0x00,
	0x20, 0x00,
	0x21, 0x40,
	0x22, 0x00,
	0x23, 0x00,
	0x24, 0x40,
	0x25, 0x88,
	0x30, 0xff,
	0x31, 0x00,
	0x32, 0xff,
	0x33, 0x00,
	0x34, 0x50,
	0x35, 0x7f,
	0x36, 0x00,
	0x37, 0x20,
	0x38, 0x00,
	0x40, 0x1c,
	0x41, 0xff,
	0x42, 0x29,
	0x43, 0x00,
	0x44, 0xff,
	0x45, 0x00,
	0x46, 0x00,
	0x49, 0x04,
	0x4a, 0x00,
	0x4b, 0x7b,
	0x52, 0x30,
	0x55, 0xae,
	0x56, 0x47,
	0x57, 0xe1,
	0x58, 0x3a,
	0x5a, 0x1e,
	0x5b, 0x34,
	0x60, 0x00,
	0x63, 0x00,
	0x64, 0x00,
	0x65, 0x00,
	0x66, 0x00,
	0x67, 0x00,
	0x68, 0x00,
	0x69, 0x00,
	0x6a, 0x02,
	0x6b, 0x00,
	0x70, 0xff,
	0x71, 0x00,
	0x72, 0x00,
	0x73, 0x00,
	0x74, 0x0c,
	0x80, 0x00,
	0x81, 0x00,
	0x82, 0x00,
	0x83, 0x00,
	0x84, 0x04,
	0x85, 0x80,
	0x86, 0x24,
	0x87, 0x78,
	0x88, 0x10,
	0x89, 0x00,
	0x90, 0x01,
	0x91, 0x01,
	0xa0, 0x04,
	0xa1, 0x00,
	0xa2, 0x00,
	0xb0, 0x91,
	0xb1, 0x0b,
	0xc0, 0x53,
	0xc1, 0x70,
	0xc2, 0x12,
	0xd0, 0x00,
	0xd1, 0x00,
	0xd2, 0x00,
	0xd3, 0x00,
	0xd4, 0x00,
	0xd5, 0x00,
	0xde, 0x00,
	0xdf, 0x00,
	0x61, 0x49,
	0x62, 0x0b,
	0x53, 0x08,
	0x59, 0x08,
	0xff, 0xff,
पूर्ण;

अटल पूर्णांक nexusca_stv0297_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा av7110* av7110 = fe->dvb->priv;
	u32 भाग;
	u8 data[4];
	काष्ठा i2c_msg msg = अणु .addr = 0x63, .flags = 0, .buf = data, .len = माप(data) पूर्ण;
	काष्ठा i2c_msg पढ़ोmsg = अणु .addr = 0x63, .flags = I2C_M_RD, .buf = data, .len = 1 पूर्ण;
	पूर्णांक i;

	भाग = (p->frequency + 36150000 + 31250) / 62500;

	data[0] = (भाग >> 8) & 0x7f;
	data[1] = भाग & 0xff;
	data[2] = 0xce;

	अगर (p->frequency < 45000000)
		वापस -EINVAL;
	अन्यथा अगर (p->frequency < 137000000)
		data[3] = 0x01;
	अन्यथा अगर (p->frequency < 403000000)
		data[3] = 0x02;
	अन्यथा अगर (p->frequency < 860000000)
		data[3] = 0x04;
	अन्यथा
		वापस -EINVAL;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer(&av7110->i2c_adap, &msg, 1) != 1) अणु
		prपूर्णांकk("nexusca: pll transfer failed!\n");
		वापस -EIO;
	पूर्ण

	// रुको क्रम PLL lock
	क्रम(i = 0; i < 20; i++) अणु
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);
		अगर (i2c_transfer(&av7110->i2c_adap, &पढ़ोmsg, 1) == 1)
			अगर (data[0] & 0x40) अवरोध;
		msleep(10);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा stv0297_config nexusca_stv0297_config = अणु

	.demod_address = 0x1C,
	.inittab = nexusca_stv0297_inittab,
	.invert = 1,
	.stop_during_पढ़ो = 1,
पूर्ण;



अटल पूर्णांक grundig_29504_401_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा av7110* av7110 = fe->dvb->priv;
	u32 भाग;
	u8 cfg, cpump, band_select;
	u8 data[4];
	काष्ठा i2c_msg msg = अणु .addr = 0x61, .flags = 0, .buf = data, .len = माप(data) पूर्ण;

	भाग = (36125000 + p->frequency) / 166666;

	cfg = 0x88;

	अगर (p->frequency < 175000000)
		cpump = 2;
	अन्यथा अगर (p->frequency < 390000000)
		cpump = 1;
	अन्यथा अगर (p->frequency < 470000000)
		cpump = 2;
	अन्यथा अगर (p->frequency < 750000000)
		cpump = 1;
	अन्यथा
		cpump = 3;

	अगर (p->frequency < 175000000)
		band_select = 0x0e;
	अन्यथा अगर (p->frequency < 470000000)
		band_select = 0x05;
	अन्यथा
		band_select = 0x03;

	data[0] = (भाग >> 8) & 0x7f;
	data[1] = भाग & 0xff;
	data[2] = ((भाग >> 10) & 0x60) | cfg;
	data[3] = (cpump << 6) | band_select;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (i2c_transfer (&av7110->i2c_adap, &msg, 1) != 1) वापस -EIO;
	वापस 0;
पूर्ण

अटल काष्ठा l64781_config grundig_29504_401_config = अणु
	.demod_address = 0x55,
पूर्ण;



अटल पूर्णांक av7110_fe_lock_fix(काष्ठा av7110 *av7110, क्रमागत fe_status status)
अणु
	पूर्णांक ret = 0;
	पूर्णांक synced = (status & FE_HAS_LOCK) ? 1 : 0;

	av7110->fe_status = status;

	अगर (av7110->fe_synced == synced)
		वापस 0;

	अगर (av7110->playing) अणु
		av7110->fe_synced = synced;
		वापस 0;
	पूर्ण

	अगर (mutex_lock_पूर्णांकerruptible(&av7110->pid_mutex))
		वापस -ERESTARTSYS;

	अगर (synced) अणु
		ret = SetPIDs(av7110, av7110->pids[DMX_PES_VIDEO],
			av7110->pids[DMX_PES_AUDIO],
			av7110->pids[DMX_PES_TELETEXT], 0,
			av7110->pids[DMX_PES_PCR]);
		अगर (!ret)
			ret = av7110_fw_cmd(av7110, COMTYPE_PIDFILTER, Scan, 0);
	पूर्ण अन्यथा अणु
		ret = SetPIDs(av7110, 0, 0, 0, 0, 0);
		अगर (!ret) अणु
			ret = av7110_fw_cmd(av7110, COMTYPE_PID_FILTER, FlushTSQueue, 0);
			अगर (!ret)
				ret = av7110_रुको_msgstate(av7110, GPMQBusy);
		पूर्ण
	पूर्ण

	अगर (!ret)
		av7110->fe_synced = synced;

	mutex_unlock(&av7110->pid_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक av7110_fe_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा av7110* av7110 = fe->dvb->priv;

	पूर्णांक ret = av7110_fe_lock_fix(av7110, 0);
	अगर (!ret)
		ret = av7110->fe_set_frontend(fe);

	वापस ret;
पूर्ण

अटल पूर्णांक av7110_fe_init(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा av7110* av7110 = fe->dvb->priv;

	पूर्णांक ret = av7110_fe_lock_fix(av7110, 0);
	अगर (!ret)
		ret = av7110->fe_init(fe);
	वापस ret;
पूर्ण

अटल पूर्णांक av7110_fe_पढ़ो_status(काष्ठा dvb_frontend *fe,
				 क्रमागत fe_status *status)
अणु
	काष्ठा av7110* av7110 = fe->dvb->priv;

	/* call the real implementation */
	पूर्णांक ret = av7110->fe_पढ़ो_status(fe, status);
	अगर (!ret)
		अगर (((*status ^ av7110->fe_status) & FE_HAS_LOCK) && (*status & FE_HAS_LOCK))
			ret = av7110_fe_lock_fix(av7110, *status);
	वापस ret;
पूर्ण

अटल पूर्णांक av7110_fe_diseqc_reset_overload(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा av7110* av7110 = fe->dvb->priv;

	पूर्णांक ret = av7110_fe_lock_fix(av7110, 0);
	अगर (!ret)
		ret = av7110->fe_diseqc_reset_overload(fe);
	वापस ret;
पूर्ण

अटल पूर्णांक av7110_fe_diseqc_send_master_cmd(काष्ठा dvb_frontend* fe,
					    काष्ठा dvb_diseqc_master_cmd* cmd)
अणु
	काष्ठा av7110* av7110 = fe->dvb->priv;

	पूर्णांक ret = av7110_fe_lock_fix(av7110, 0);
	अगर (!ret) अणु
		av7110->saved_master_cmd = *cmd;
		ret = av7110->fe_diseqc_send_master_cmd(fe, cmd);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक av7110_fe_diseqc_send_burst(काष्ठा dvb_frontend *fe,
				       क्रमागत fe_sec_mini_cmd minicmd)
अणु
	काष्ठा av7110* av7110 = fe->dvb->priv;

	पूर्णांक ret = av7110_fe_lock_fix(av7110, 0);
	अगर (!ret) अणु
		av7110->saved_minicmd = minicmd;
		ret = av7110->fe_diseqc_send_burst(fe, minicmd);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक av7110_fe_set_tone(काष्ठा dvb_frontend *fe,
			      क्रमागत fe_sec_tone_mode tone)
अणु
	काष्ठा av7110* av7110 = fe->dvb->priv;

	पूर्णांक ret = av7110_fe_lock_fix(av7110, 0);
	अगर (!ret) अणु
		av7110->saved_tone = tone;
		ret = av7110->fe_set_tone(fe, tone);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक av7110_fe_set_voltage(काष्ठा dvb_frontend *fe,
				 क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा av7110* av7110 = fe->dvb->priv;

	पूर्णांक ret = av7110_fe_lock_fix(av7110, 0);
	अगर (!ret) अणु
		av7110->saved_voltage = voltage;
		ret = av7110->fe_set_voltage(fe, voltage);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक av7110_fe_dishnetwork_send_legacy_command(काष्ठा dvb_frontend* fe, अचिन्हित दीर्घ cmd)
अणु
	काष्ठा av7110* av7110 = fe->dvb->priv;

	पूर्णांक ret = av7110_fe_lock_fix(av7110, 0);
	अगर (!ret)
		ret = av7110->fe_dishnetwork_send_legacy_command(fe, cmd);
	वापस ret;
पूर्ण

अटल व्योम dvb_s_recover(काष्ठा av7110* av7110)
अणु
	av7110_fe_init(av7110->fe);

	av7110_fe_set_voltage(av7110->fe, av7110->saved_voltage);
	अगर (av7110->saved_master_cmd.msg_len) अणु
		msleep(20);
		av7110_fe_diseqc_send_master_cmd(av7110->fe, &av7110->saved_master_cmd);
	पूर्ण
	msleep(20);
	av7110_fe_diseqc_send_burst(av7110->fe, av7110->saved_minicmd);
	msleep(20);
	av7110_fe_set_tone(av7110->fe, av7110->saved_tone);

	av7110_fe_set_frontend(av7110->fe);
पूर्ण

अटल u8 पढ़ो_pwm(काष्ठा av7110* av7110)
अणु
	u8 b = 0xff;
	u8 pwm;
	काष्ठा i2c_msg msg[] = अणु अणु .addr = 0x50,.flags = 0,.buf = &b,.len = 1 पूर्ण,
				 अणु .addr = 0x50,.flags = I2C_M_RD,.buf = &pwm,.len = 1पूर्ण पूर्ण;

	अगर ((i2c_transfer(&av7110->i2c_adap, msg, 2) != 2) || (pwm == 0xff))
		pwm = 0x48;

	वापस pwm;
पूर्ण

अटल पूर्णांक frontend_init(काष्ठा av7110 *av7110)
अणु
	पूर्णांक ret;

	अगर (av7110->dev->pci->subप्रणाली_venकरोr == 0x110a) अणु
		चयन(av7110->dev->pci->subप्रणाली_device) अणु
		हाल 0x0000: // Fujitsu/Siemens DVB-Cable (ves1820/Philips CD1516(??))
			av7110->fe = dvb_attach(ves1820_attach, &philips_cd1516_config,
						    &av7110->i2c_adap, पढ़ो_pwm(av7110));
			अगर (av7110->fe) अणु
				av7110->fe->ops.tuner_ops.set_params = philips_cd1516_tuner_set_params;
			पूर्ण
			अवरोध;
		पूर्ण

	पूर्ण अन्यथा अगर (av7110->dev->pci->subप्रणाली_venकरोr == 0x13c2) अणु
		चयन(av7110->dev->pci->subप्रणाली_device) अणु
		हाल 0x0000: // Hauppauge/TT WinTV DVB-S rev1.X
		हाल 0x0003: // Hauppauge/TT WinTV Nexus-S Rev 2.X
		हाल 0x1002: // Hauppauge/TT WinTV DVB-S rev1.3SE

			// try the ALPS BSRV2 first of all
			av7110->fe = dvb_attach(ves1x93_attach, &alps_bsrv2_config, &av7110->i2c_adap);
			अगर (av7110->fe) अणु
				av7110->fe->ops.tuner_ops.set_params = alps_bsrv2_tuner_set_params;
				av7110->fe->ops.diseqc_send_master_cmd = av7110_diseqc_send_master_cmd;
				av7110->fe->ops.diseqc_send_burst = av7110_diseqc_send_burst;
				av7110->fe->ops.set_tone = av7110_set_tone;
				av7110->recover = dvb_s_recover;
				अवरोध;
			पूर्ण

			// try the ALPS BSRU6 now
			av7110->fe = dvb_attach(stv0299_attach, &alps_bsru6_config, &av7110->i2c_adap);
			अगर (av7110->fe) अणु
				av7110->fe->ops.tuner_ops.set_params = alps_bsru6_tuner_set_params;
				av7110->fe->tuner_priv = &av7110->i2c_adap;

				av7110->fe->ops.diseqc_send_master_cmd = av7110_diseqc_send_master_cmd;
				av7110->fe->ops.diseqc_send_burst = av7110_diseqc_send_burst;
				av7110->fe->ops.set_tone = av7110_set_tone;
				av7110->recover = dvb_s_recover;
				अवरोध;
			पूर्ण

			// Try the grundig 29504-451
			av7110->fe = dvb_attach(tda8083_attach, &grundig_29504_451_config, &av7110->i2c_adap);
			अगर (av7110->fe) अणु
				av7110->fe->ops.tuner_ops.set_params = grundig_29504_451_tuner_set_params;
				av7110->fe->ops.diseqc_send_master_cmd = av7110_diseqc_send_master_cmd;
				av7110->fe->ops.diseqc_send_burst = av7110_diseqc_send_burst;
				av7110->fe->ops.set_tone = av7110_set_tone;
				av7110->recover = dvb_s_recover;
				अवरोध;
			पूर्ण

			/* Try DVB-C cards */
			चयन(av7110->dev->pci->subप्रणाली_device) अणु
			हाल 0x0000:
				/* Siemens DVB-C (full-length card) VES1820/Philips CD1516 */
				av7110->fe = dvb_attach(ves1820_attach, &philips_cd1516_config, &av7110->i2c_adap,
							पढ़ो_pwm(av7110));
				अगर (av7110->fe) अणु
					av7110->fe->ops.tuner_ops.set_params = philips_cd1516_tuner_set_params;
				पूर्ण
				अवरोध;
			हाल 0x0003:
				/* Hauppauge DVB-C 2.1 VES1820/ALPS TDBE2 */
				av7110->fe = dvb_attach(ves1820_attach, &alps_tdbe2_config, &av7110->i2c_adap,
							पढ़ो_pwm(av7110));
				अगर (av7110->fe) अणु
					av7110->fe->ops.tuner_ops.set_params = alps_tdbe2_tuner_set_params;
				पूर्ण
				अवरोध;
			पूर्ण
			अवरोध;

		हाल 0x0001: // Hauppauge/TT Nexus-T premium rev1.X
		अणु
			काष्ठा dvb_frontend *fe;

			// try ALPS TDLB7 first, then Grundig 29504-401
			fe = dvb_attach(sp8870_attach, &alps_tdlb7_config, &av7110->i2c_adap);
			अगर (fe) अणु
				fe->ops.tuner_ops.set_params = alps_tdlb7_tuner_set_params;
				av7110->fe = fe;
				अवरोध;
			पूर्ण
		पूर्ण
			fallthrough;

		हाल 0x0008: // Hauppauge/TT DVB-T
			// Grundig 29504-401
			av7110->fe = dvb_attach(l64781_attach, &grundig_29504_401_config, &av7110->i2c_adap);
			अगर (av7110->fe)
				av7110->fe->ops.tuner_ops.set_params = grundig_29504_401_tuner_set_params;
			अवरोध;

		हाल 0x0002: // Hauppauge/TT DVB-C premium rev2.X

			av7110->fe = dvb_attach(ves1820_attach, &alps_tdbe2_config, &av7110->i2c_adap, पढ़ो_pwm(av7110));
			अगर (av7110->fe) अणु
				av7110->fe->ops.tuner_ops.set_params = alps_tdbe2_tuner_set_params;
			पूर्ण
			अवरोध;

		हाल 0x0004: // Galaxis DVB-S rev1.3
			/* ALPS BSRV2 */
			av7110->fe = dvb_attach(ves1x93_attach, &alps_bsrv2_config, &av7110->i2c_adap);
			अगर (av7110->fe) अणु
				av7110->fe->ops.tuner_ops.set_params = alps_bsrv2_tuner_set_params;
				av7110->fe->ops.diseqc_send_master_cmd = av7110_diseqc_send_master_cmd;
				av7110->fe->ops.diseqc_send_burst = av7110_diseqc_send_burst;
				av7110->fe->ops.set_tone = av7110_set_tone;
				av7110->recover = dvb_s_recover;
			पूर्ण
			अवरोध;

		हाल 0x0006: /* Fujitsu-Siemens DVB-S rev 1.6 */
			/* Grundig 29504-451 */
			av7110->fe = dvb_attach(tda8083_attach, &grundig_29504_451_config, &av7110->i2c_adap);
			अगर (av7110->fe) अणु
				av7110->fe->ops.tuner_ops.set_params = grundig_29504_451_tuner_set_params;
				av7110->fe->ops.diseqc_send_master_cmd = av7110_diseqc_send_master_cmd;
				av7110->fe->ops.diseqc_send_burst = av7110_diseqc_send_burst;
				av7110->fe->ops.set_tone = av7110_set_tone;
				av7110->recover = dvb_s_recover;
			पूर्ण
			अवरोध;

		हाल 0x000A: // Hauppauge/TT Nexus-CA rev1.X

			av7110->fe = dvb_attach(stv0297_attach, &nexusca_stv0297_config, &av7110->i2c_adap);
			अगर (av7110->fe) अणु
				av7110->fe->ops.tuner_ops.set_params = nexusca_stv0297_tuner_set_params;

				/* set TDA9819 पूर्णांकo DVB mode */
				saa7146_setgpio(av7110->dev, 1, SAA7146_GPIO_OUTLO); // TDA9819 pin9(STD)
				saa7146_setgpio(av7110->dev, 3, SAA7146_GPIO_OUTLO); // TDA9819 pin30(VIF)

				/* tuner on this needs a slower i2c bus speed */
				av7110->dev->i2c_bitrate = SAA7146_I2C_BUS_BIT_RATE_240;
				अवरोध;
			पूर्ण
			अवरोध;

		हाल 0x000E: /* Hauppauge/TT Nexus-S rev 2.3 */
			/* ALPS BSBE1 */
			av7110->fe = dvb_attach(stv0299_attach, &alps_bsbe1_config, &av7110->i2c_adap);
			अगर (av7110->fe) अणु
				av7110->fe->ops.tuner_ops.set_params = alps_bsbe1_tuner_set_params;
				av7110->fe->tuner_priv = &av7110->i2c_adap;

				अगर (dvb_attach(lnbp21_attach, av7110->fe, &av7110->i2c_adap, 0, 0) == शून्य) अणु
					prपूर्णांकk("dvb-ttpci: LNBP21 not found!\n");
					अगर (av7110->fe->ops.release)
						av7110->fe->ops.release(av7110->fe);
					av7110->fe = शून्य;
				पूर्ण अन्यथा अणु
					av7110->fe->ops.dishnetwork_send_legacy_command = शून्य;
					av7110->recover = dvb_s_recover;
				पूर्ण
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!av7110->fe) अणु
		/* FIXME: propagate the failure code from the lower layers */
		ret = -ENOMEM;
		prपूर्णांकk("dvb-ttpci: A frontend driver was not found for device [%04x:%04x] subsystem [%04x:%04x]\n",
		       av7110->dev->pci->venकरोr,
		       av7110->dev->pci->device,
		       av7110->dev->pci->subप्रणाली_venकरोr,
		       av7110->dev->pci->subप्रणाली_device);
	पूर्ण अन्यथा अणु
		FE_FUNC_OVERRIDE(av7110->fe->ops.init, av7110->fe_init, av7110_fe_init);
		FE_FUNC_OVERRIDE(av7110->fe->ops.पढ़ो_status, av7110->fe_पढ़ो_status, av7110_fe_पढ़ो_status);
		FE_FUNC_OVERRIDE(av7110->fe->ops.diseqc_reset_overload, av7110->fe_diseqc_reset_overload, av7110_fe_diseqc_reset_overload);
		FE_FUNC_OVERRIDE(av7110->fe->ops.diseqc_send_master_cmd, av7110->fe_diseqc_send_master_cmd, av7110_fe_diseqc_send_master_cmd);
		FE_FUNC_OVERRIDE(av7110->fe->ops.diseqc_send_burst, av7110->fe_diseqc_send_burst, av7110_fe_diseqc_send_burst);
		FE_FUNC_OVERRIDE(av7110->fe->ops.set_tone, av7110->fe_set_tone, av7110_fe_set_tone);
		FE_FUNC_OVERRIDE(av7110->fe->ops.set_voltage, av7110->fe_set_voltage, av7110_fe_set_voltage);
		FE_FUNC_OVERRIDE(av7110->fe->ops.dishnetwork_send_legacy_command, av7110->fe_dishnetwork_send_legacy_command, av7110_fe_dishnetwork_send_legacy_command);
		FE_FUNC_OVERRIDE(av7110->fe->ops.set_frontend, av7110->fe_set_frontend, av7110_fe_set_frontend);

		ret = dvb_रेजिस्टर_frontend(&av7110->dvb_adapter, av7110->fe);
		अगर (ret < 0) अणु
			prपूर्णांकk("av7110: Frontend registration failed!\n");
			dvb_frontend_detach(av7110->fe);
			av7110->fe = शून्य;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/* Budgetpatch note:
 * Original hardware design by Roberto Deza:
 * There is a DVB_Wiki at
 * https://linuxtv.org
 *
 * New software triggering design by Emard that works on
 * original Roberto Deza's hardware:
 *
 * rps1 code क्रम budgetpatch will copy पूर्णांकernal HS event to GPIO3 pin.
 * GPIO3 is in budget-patch hardware connectd to port B VSYNC
 * HS is an पूर्णांकernal event of 7146, accessible with RPS
 * and temporarily उठाओd high every n lines
 * (n in defined in the RPS_THRESH1 counter threshold)
 * I think HS is उठाओd high on the beginning of the n-th line
 * and reमुख्यs high until this n-th line that triggered
 * it is completely received. When the reception of n-th line
 * ends, HS is lowered.
 *
 * To transmit data over DMA, 7146 needs changing state at
 * port B VSYNC pin. Any changing of port B VSYNC will
 * cause some DMA data transfer, with more or less packets loss.
 * It depends on the phase and frequency of VSYNC and
 * the way of 7146 is inकाष्ठाed to trigger on port B (defined
 * in DD1_INIT रेजिस्टर, 3rd nibble from the right valid
 * numbers are 0-7, see datasheet)
 *
 * The correct triggering can minimize packet loss,
 * dvbtraffic should give this stable bandwidths:
 *   22k transponder = 33814 kbit/s
 * 27.5k transponder = 38045 kbit/s
 * by experiment it is found that the best results
 * (stable bandwidths and almost no packet loss)
 * are obtained using DD1_INIT triggering number 2
 * (Va at rising edge of VS Fa = HS x VS-failing क्रमced toggle)
 * and a VSYNC phase that occurs in the middle of DMA transfer
 * (about byte 188*512=96256 in the DMA winकरोw).
 *
 * Phase of HS is still not clear to me how to control,
 * It just happens to be so. It can be seen अगर one enables
 * RPS_IRQ and prपूर्णांक Event Counter 1 in vpeirq(). Every
 * समय RPS_INTERRUPT is called, the Event Counter 1 will
 * increment. That's how the 7146 is programmed to करो event
 * counting in this budget-patch.c
 * I *think* HPS setting has something to करो with the phase
 * of HS but I can't be 100% sure in that.
 *
 * hardware debug note: a working budget card (including budget patch)
 * with vpeirq() पूर्णांकerrupt setup in mode "0x90" (every 64K) will
 * generate 3 पूर्णांकerrupts per 25-Hz DMA frame of 2*188*512 bytes
 * and that means 3*25=75 Hz of पूर्णांकerrupt frequency, as seen by
 * watch cat /proc/पूर्णांकerrupts
 *
 * If this frequency is 3x lower (and data received in the DMA
 * buffer करोn't start with 0x47, but in the middle of packets,
 * whose lengths appear to be like 188 292 188 104 etc.
 * this means VSYNC line is not connected in the hardware.
 * (check soldering pcb and pins)
 * The same behaviour of missing VSYNC can be duplicated on budget
 * cards, by setting DD1_INIT trigger mode 7 in 3rd nibble.
 */
अटल पूर्णांक av7110_attach(काष्ठा saa7146_dev* dev,
			 काष्ठा saa7146_pci_extension_data *pci_ext)
अणु
	स्थिर पूर्णांक length = TS_WIDTH * TS_HEIGHT;
	काष्ठा pci_dev *pdev = dev->pci;
	काष्ठा av7110 *av7110;
	काष्ठा task_काष्ठा *thपढ़ो;
	पूर्णांक ret, count = 0;

	dprपूर्णांकk(4, "dev: %p\n", dev);

	/* Set RPS_IRQ to 1 to track rps1 activity.
	 * Enabling this won't send any पूर्णांकerrupt to PC CPU.
	 */
#घोषणा RPS_IRQ 0

	अगर (budgetpatch == 1) अणु
		budgetpatch = 0;
		/* स्वतःdetect the presence of budget patch
		 * this only works अगर saa7146 has been recently
		 * reset with with MASK_31 to MC1
		 *
		 * will रुको क्रम VBI_B event (vertical blank at port B)
		 * and will reset GPIO3 after VBI_B is detected.
		 * (GPIO3 should be उठाओd high by CPU to
		 * test अगर GPIO3 will generate vertical blank संकेत
		 * in budget patch GPIO3 is connected to VSYNC_B
		 */

		/* RESET SAA7146 */
		saa7146_ग_लिखो(dev, MC1, MASK_31);
		/* स्वतःdetection success seems to be समय-dependend after reset */

		/* Fix VSYNC level */
		saa7146_setgpio(dev, 3, SAA7146_GPIO_OUTLO);
		/* set vsync_b triggering */
		saa7146_ग_लिखो(dev, DD1_STREAM_B, 0);
		/* port B VSYNC at rising edge */
		saa7146_ग_लिखो(dev, DD1_INIT, 0x00000200);
		saa7146_ग_लिखो(dev, BRS_CTRL, 0x00000000);  // VBI
		saa7146_ग_लिखो(dev, MC2,
			      1 * (MASK_08 | MASK_24)  |   // BRS control
			      0 * (MASK_09 | MASK_25)  |   // a
			      1 * (MASK_10 | MASK_26)  |   // b
			      0 * (MASK_06 | MASK_22)  |   // HPS_CTRL1
			      0 * (MASK_05 | MASK_21)  |   // HPS_CTRL2
			      0 * (MASK_01 | MASK_15)      // DEBI
		);

		/* start writing RPS1 code from beginning */
		count = 0;
		/* Disable RPS1 */
		saa7146_ग_लिखो(dev, MC1, MASK_29);
		/* RPS1 समयout disable */
		saa7146_ग_लिखो(dev, RPS_TOV1, 0);
		WRITE_RPS1(CMD_PAUSE | EVT_VBI_B);
		WRITE_RPS1(CMD_WR_REG_MASK | (GPIO_CTRL>>2));
		WRITE_RPS1(GPIO3_MSK);
		WRITE_RPS1(SAA7146_GPIO_OUTLO<<24);
#अगर RPS_IRQ
		/* issue RPS1 पूर्णांकerrupt to increment counter */
		WRITE_RPS1(CMD_INTERRUPT);
#पूर्ण_अगर
		WRITE_RPS1(CMD_STOP);
		/* Jump to begin of RPS program as safety measure               (p37) */
		WRITE_RPS1(CMD_JUMP);
		WRITE_RPS1(dev->d_rps1.dma_handle);

#अगर RPS_IRQ
		/* set event counter 1 source as RPS1 पूर्णांकerrupt (0x03)          (rE4 p53)
		 * use 0x03 to track RPS1 पूर्णांकerrupts - increase by 1 every gpio3 is toggled
		 * use 0x15 to track VPE  पूर्णांकerrupts - increase by 1 every vpeirq() is called
		 */
		saa7146_ग_लिखो(dev, EC1SSR, (0x03<<2) | 3 );
		/* set event counter 1 threshold to maximum allowed value        (rEC p55) */
		saa7146_ग_लिखो(dev, ECT1R,  0x3fff );
#पूर्ण_अगर
		/* Set RPS1 Address रेजिस्टर to poपूर्णांक to RPS code               (r108 p42) */
		saa7146_ग_लिखो(dev, RPS_ADDR1, dev->d_rps1.dma_handle);
		/* Enable RPS1,                                                 (rFC p33) */
		saa7146_ग_लिखो(dev, MC1, (MASK_13 | MASK_29 ));

		mdelay(10);
		/* now send VSYNC_B to rps1 by rising GPIO3 */
		saa7146_setgpio(dev, 3, SAA7146_GPIO_OUTHI);
		mdelay(10);
		/* अगर rps1 responded by lowering the GPIO3,
		 * then we have budgetpatch hardware
		 */
		अगर ((saa7146_पढ़ो(dev, GPIO_CTRL) & 0x10000000) == 0) अणु
			budgetpatch = 1;
			prपूर्णांकk("dvb-ttpci: BUDGET-PATCH DETECTED.\n");
		पूर्ण
		/* Disable RPS1 */
		saa7146_ग_लिखो(dev, MC1, ( MASK_29 ));
#अगर RPS_IRQ
		prपूर्णांकk("dvb-ttpci: Event Counter 1 0x%04x\n", saa7146_पढ़ो(dev, EC1R) & 0x3fff );
#पूर्ण_अगर
	पूर्ण

	/* prepare the av7110 device काष्ठा */
	av7110 = kzalloc(माप(काष्ठा av7110), GFP_KERNEL);
	अगर (!av7110) अणु
		dprपूर्णांकk(1, "out of memory\n");
		वापस -ENOMEM;
	पूर्ण

	av7110->card_name = (अक्षर*) pci_ext->ext_priv;
	av7110->dev = dev;
	dev->ext_priv = av7110;

	ret = get_firmware(av7110);
	अगर (ret < 0)
		जाओ err_kमुक्त_0;

	ret = dvb_रेजिस्टर_adapter(&av7110->dvb_adapter, av7110->card_name,
				   THIS_MODULE, &dev->pci->dev, adapter_nr);
	अगर (ret < 0)
		जाओ err_put_firmware_1;

	/* the Siemens DVB needs this अगर you want to have the i2c chips
	   get recognized beक्रमe the मुख्य driver is fully loaded */
	saa7146_ग_लिखो(dev, GPIO_CTRL, 0x500000);

	strscpy(av7110->i2c_adap.name, pci_ext->ext_priv,
		माप(av7110->i2c_adap.name));

	saa7146_i2c_adapter_prepare(dev, &av7110->i2c_adap, SAA7146_I2C_BUS_BIT_RATE_120); /* 275 kHz */

	ret = i2c_add_adapter(&av7110->i2c_adap);
	अगर (ret < 0)
		जाओ err_dvb_unरेजिस्टर_adapter_2;

	ttpci_eeprom_parse_mac(&av7110->i2c_adap,
			       av7110->dvb_adapter.proposed_mac);
	ret = -ENOMEM;

	/* full-ts mod? */
	अगर (full_ts)
		av7110->full_ts = true;

	/* check क्रम full-ts flag in eeprom */
	अगर (i2c_पढ़ोreg(av7110, 0xaa, 0) == 0x4f && i2c_पढ़ोreg(av7110, 0xaa, 1) == 0x45) अणु
		u8 flags = i2c_पढ़ोreg(av7110, 0xaa, 2);
		अगर (flags != 0xff && (flags & 0x01))
			av7110->full_ts = true;
	पूर्ण

	अगर (av7110->full_ts) अणु
		prपूर्णांकk(KERN_INFO "dvb-ttpci: full-ts mode enabled for saa7146 port B\n");
		spin_lock_init(&av7110->feedlock1);
		av7110->grabbing = saa7146_vदो_स्मृति_build_pgtable(pdev, length,
								 &av7110->pt);
		अगर (!av7110->grabbing)
			जाओ err_i2c_del_3;

		saa7146_ग_लिखो(dev, DD1_STREAM_B, 0x00000000);
		saa7146_ग_लिखो(dev, MC2, (MASK_10 | MASK_26));

		saa7146_ग_लिखो(dev, DD1_INIT, 0x00000600);
		saa7146_ग_लिखो(dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));

		saa7146_ग_लिखो(dev, BRS_CTRL, 0x60000000);
		saa7146_ग_लिखो(dev, MC2, MASK_08 | MASK_24);

		/* dma3 */
		saa7146_ग_लिखो(dev, PCI_BT_V1, 0x001c0000 | (saa7146_पढ़ो(dev, PCI_BT_V1) & ~0x001f0000));
		saa7146_ग_लिखो(dev, BASE_ODD3, 0);
		saa7146_ग_लिखो(dev, BASE_EVEN3, 0);
		saa7146_ग_लिखो(dev, PROT_ADDR3, TS_WIDTH * TS_HEIGHT);
		saa7146_ग_लिखो(dev, PITCH3, TS_WIDTH);
		saa7146_ग_लिखो(dev, BASE_PAGE3, av7110->pt.dma | ME1 | 0x90);
		saa7146_ग_लिखो(dev, NUM_LINE_BYTE3, (TS_HEIGHT << 16) | TS_WIDTH);
		saa7146_ग_लिखो(dev, MC2, MASK_04 | MASK_20);

		tasklet_setup(&av7110->vpe_tasklet, vpeirq);

	पूर्ण अन्यथा अगर (budgetpatch) अणु
		spin_lock_init(&av7110->feedlock1);
		av7110->grabbing = saa7146_vदो_स्मृति_build_pgtable(pdev, length,
								 &av7110->pt);
		अगर (!av7110->grabbing)
			जाओ err_i2c_del_3;

		saa7146_ग_लिखो(dev, PCI_BT_V1, 0x1c1f101f);
		saa7146_ग_लिखो(dev, BCS_CTRL, 0x80400040);
		/* set dd1 stream a & b */
		saa7146_ग_लिखो(dev, DD1_STREAM_B, 0x00000000);
		saa7146_ग_लिखो(dev, DD1_INIT, 0x03000200);
		saa7146_ग_लिखो(dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));
		saa7146_ग_लिखो(dev, BRS_CTRL, 0x60000000);
		saa7146_ग_लिखो(dev, BASE_ODD3, 0);
		saa7146_ग_लिखो(dev, BASE_EVEN3, 0);
		saa7146_ग_लिखो(dev, PROT_ADDR3, TS_WIDTH * TS_HEIGHT);
		saa7146_ग_लिखो(dev, BASE_PAGE3, av7110->pt.dma | ME1 | 0x90);

		saa7146_ग_लिखो(dev, PITCH3, TS_WIDTH);
		saa7146_ग_लिखो(dev, NUM_LINE_BYTE3, (TS_HEIGHT << 16) | TS_WIDTH);

		/* upload all */
		saa7146_ग_लिखो(dev, MC2, 0x077c077c);
		saa7146_ग_लिखो(dev, GPIO_CTRL, 0x000000);
#अगर RPS_IRQ
		/* set event counter 1 source as RPS1 पूर्णांकerrupt (0x03)          (rE4 p53)
		 * use 0x03 to track RPS1 पूर्णांकerrupts - increase by 1 every gpio3 is toggled
		 * use 0x15 to track VPE  पूर्णांकerrupts - increase by 1 every vpeirq() is called
		 */
		saa7146_ग_लिखो(dev, EC1SSR, (0x03<<2) | 3 );
		/* set event counter 1 threshold to maximum allowed value        (rEC p55) */
		saa7146_ग_लिखो(dev, ECT1R,  0x3fff );
#पूर्ण_अगर
		/* Setup BUDGETPATCH MAIN RPS1 "program" (p35) */
		count = 0;

		/* Wait Source Line Counter Threshold                           (p36) */
		WRITE_RPS1(CMD_PAUSE | EVT_HS);
		/* Set GPIO3=1                                                  (p42) */
		WRITE_RPS1(CMD_WR_REG_MASK | (GPIO_CTRL>>2));
		WRITE_RPS1(GPIO3_MSK);
		WRITE_RPS1(SAA7146_GPIO_OUTHI<<24);
#अगर RPS_IRQ
		/* issue RPS1 पूर्णांकerrupt */
		WRITE_RPS1(CMD_INTERRUPT);
#पूर्ण_अगर
		/* Wait reset Source Line Counter Threshold                     (p36) */
		WRITE_RPS1(CMD_PAUSE | RPS_INV | EVT_HS);
		/* Set GPIO3=0                                                  (p42) */
		WRITE_RPS1(CMD_WR_REG_MASK | (GPIO_CTRL>>2));
		WRITE_RPS1(GPIO3_MSK);
		WRITE_RPS1(SAA7146_GPIO_OUTLO<<24);
#अगर RPS_IRQ
		/* issue RPS1 पूर्णांकerrupt */
		WRITE_RPS1(CMD_INTERRUPT);
#पूर्ण_अगर
		/* Jump to begin of RPS program                                 (p37) */
		WRITE_RPS1(CMD_JUMP);
		WRITE_RPS1(dev->d_rps1.dma_handle);

		/* Fix VSYNC level */
		saa7146_setgpio(dev, 3, SAA7146_GPIO_OUTLO);
		/* Set RPS1 Address रेजिस्टर to poपूर्णांक to RPS code               (r108 p42) */
		saa7146_ग_लिखो(dev, RPS_ADDR1, dev->d_rps1.dma_handle);
		/* Set Source Line Counter Threshold, using BRS                 (rCC p43)
		 * It generates HS event every TS_HEIGHT lines
		 * this is related to TS_WIDTH set in रेजिस्टर
		 * NUM_LINE_BYTE3. If NUM_LINE_BYTE low 16 bits
		 * are set to TS_WIDTH bytes (TS_WIDTH=2*188),
		 * then RPS_THRESH1 should be set to trigger
		 * every TS_HEIGHT (512) lines.
		 */
		saa7146_ग_लिखो(dev, RPS_THRESH1, (TS_HEIGHT*1) | MASK_12 );

		/* Enable RPS1                                                  (rFC p33) */
		saa7146_ग_लिखो(dev, MC1, (MASK_13 | MASK_29));

		/* end of budgetpatch रेजिस्टर initialization */
		tasklet_setup(&av7110->vpe_tasklet,  vpeirq);
	पूर्ण अन्यथा अणु
		saa7146_ग_लिखो(dev, PCI_BT_V1, 0x1c00101f);
		saa7146_ग_लिखो(dev, BCS_CTRL, 0x80400040);

		/* set dd1 stream a & b */
		saa7146_ग_लिखो(dev, DD1_STREAM_B, 0x00000000);
		saa7146_ग_लिखो(dev, DD1_INIT, 0x03000000);
		saa7146_ग_लिखो(dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));

		/* upload all */
		saa7146_ग_लिखो(dev, MC2, 0x077c077c);
		saa7146_ग_लिखो(dev, GPIO_CTRL, 0x000000);
	पूर्ण

	tasklet_setup(&av7110->debi_tasklet, debiirq);
	tasklet_setup(&av7110->gpio_tasklet, gpioirq);

	mutex_init(&av7110->pid_mutex);

	/* locks क्रम data transfers from/to AV7110 */
	spin_lock_init(&av7110->debilock);
	mutex_init(&av7110->dcomlock);
	av7110->debitype = -1;

	/* शेष OSD winकरोw */
	av7110->osdwin = 1;
	mutex_init(&av7110->osd_mutex);

	/* TV standard */
	av7110->vidmode = tv_standard == 1 ? AV7110_VIDEO_MODE_NTSC
					   : AV7110_VIDEO_MODE_PAL;

	/* ARM "watchdog" */
	init_रुकोqueue_head(&av7110->arm_रुको);
	av7110->arm_thपढ़ो = शून्य;

	/* allocate and init buffers */
	av7110->debi_virt = dma_alloc_coherent(&pdev->dev, 8192,
					       &av7110->debi_bus, GFP_KERNEL);
	अगर (!av7110->debi_virt)
		जाओ err_saa71466_vमुक्त_4;


	av7110->iobuf = vदो_स्मृति(AVOUTLEN+AOUTLEN+BMPLEN+4*IPACKS);
	अगर (!av7110->iobuf)
		जाओ err_pci_मुक्त_5;

	ret = av7110_av_init(av7110);
	अगर (ret < 0)
		जाओ err_iobuf_vमुक्त_6;

	/* init BMP buffer */
	av7110->bmpbuf = av7110->iobuf+AVOUTLEN+AOUTLEN;
	init_रुकोqueue_head(&av7110->bmpq);

	ret = av7110_ca_init(av7110);
	अगर (ret < 0)
		जाओ err_av7110_av_निकास_7;

	/* load firmware पूर्णांकo AV7110 cards */
	ret = av7110_bootarm(av7110);
	अगर (ret < 0)
		जाओ err_av7110_ca_निकास_8;

	ret = av7110_firmversion(av7110);
	अगर (ret < 0)
		जाओ err_stop_arm_9;

	अगर (FW_VERSION(av7110->arm_app)<0x2501)
		prपूर्णांकk(KERN_WARNING
		       "dvb-ttpci: Warning, firmware version 0x%04x is too old. System might be unstable!\n",
		       FW_VERSION(av7110->arm_app));

	thपढ़ो = kthपढ़ो_run(arm_thपढ़ो, (व्योम *) av7110, "arm_mon");
	अगर (IS_ERR(thपढ़ो)) अणु
		ret = PTR_ERR(thपढ़ो);
		जाओ err_stop_arm_9;
	पूर्ण
	av7110->arm_thपढ़ो = thपढ़ो;

	/* set initial volume in mixer काष्ठा */
	av7110->mixer.volume_left  = volume;
	av7110->mixer.volume_right = volume;

	ret = av7110_रेजिस्टर(av7110);
	अगर (ret < 0)
		जाओ err_arm_thपढ़ो_stop_10;

	init_av7110_av(av7110);

	/* special हाल DVB-C: these cards have an analog tuner
	   plus need some special handling, so we have separate
	   saa7146_ext_vv data क्रम these... */
	ret = av7110_init_v4l(av7110);
	अगर (ret < 0)
		जाओ err_av7110_unरेजिस्टर_11;

	av7110->dvb_adapter.priv = av7110;
	ret = frontend_init(av7110);
	अगर (ret < 0)
		जाओ err_av7110_निकास_v4l_12;

	mutex_init(&av7110->ioctl_mutex);

#अगर IS_ENABLED(CONFIG_DVB_AV7110_IR)
	av7110_ir_init(av7110);
#पूर्ण_अगर
	prपूर्णांकk(KERN_INFO "dvb-ttpci: found av7110-%d.\n", av7110_num);
	av7110_num++;
out:
	वापस ret;

err_av7110_निकास_v4l_12:
	av7110_निकास_v4l(av7110);
err_av7110_unरेजिस्टर_11:
	dvb_unरेजिस्टर(av7110);
err_arm_thपढ़ो_stop_10:
	av7110_arm_sync(av7110);
err_stop_arm_9:
	/* Nothing to करो. Rejoice. */
err_av7110_ca_निकास_8:
	av7110_ca_निकास(av7110);
err_av7110_av_निकास_7:
	av7110_av_निकास(av7110);
err_iobuf_vमुक्त_6:
	vमुक्त(av7110->iobuf);
err_pci_मुक्त_5:
	dma_मुक्त_coherent(&pdev->dev, 8192, av7110->debi_virt,
			  av7110->debi_bus);
err_saa71466_vमुक्त_4:
	अगर (av7110->grabbing)
		saa7146_vमुक्त_destroy_pgtable(pdev, av7110->grabbing, &av7110->pt);
err_i2c_del_3:
	i2c_del_adapter(&av7110->i2c_adap);
err_dvb_unरेजिस्टर_adapter_2:
	dvb_unरेजिस्टर_adapter(&av7110->dvb_adapter);
err_put_firmware_1:
	put_firmware(av7110);
err_kमुक्त_0:
	kमुक्त(av7110);
	जाओ out;
पूर्ण

अटल पूर्णांक av7110_detach(काष्ठा saa7146_dev* saa)
अणु
	काष्ठा av7110 *av7110 = saa->ext_priv;
	dprपूर्णांकk(4, "%p\n", av7110);

#अगर IS_ENABLED(CONFIG_DVB_AV7110_IR)
	av7110_ir_निकास(av7110);
#पूर्ण_अगर
	अगर (budgetpatch || av7110->full_ts) अणु
		अगर (budgetpatch) अणु
			/* Disable RPS1 */
			saa7146_ग_लिखो(saa, MC1, MASK_29);
			/* VSYNC LOW (inactive) */
			saa7146_setgpio(saa, 3, SAA7146_GPIO_OUTLO);
		पूर्ण
		saa7146_ग_लिखो(saa, MC1, MASK_20);	/* DMA3 off */
		SAA7146_IER_DISABLE(saa, MASK_10);
		SAA7146_ISR_CLEAR(saa, MASK_10);
		msleep(50);
		tasklet_समाप्त(&av7110->vpe_tasklet);
		saa7146_vमुक्त_destroy_pgtable(saa->pci, av7110->grabbing, &av7110->pt);
	पूर्ण
	av7110_निकास_v4l(av7110);

	av7110_arm_sync(av7110);

	tasklet_समाप्त(&av7110->debi_tasklet);
	tasklet_समाप्त(&av7110->gpio_tasklet);

	dvb_unरेजिस्टर(av7110);

	SAA7146_IER_DISABLE(saa, MASK_19 | MASK_03);
	SAA7146_ISR_CLEAR(saa, MASK_19 | MASK_03);

	av7110_ca_निकास(av7110);
	av7110_av_निकास(av7110);

	vमुक्त(av7110->iobuf);
	dma_मुक्त_coherent(&saa->pci->dev, 8192, av7110->debi_virt,
			  av7110->debi_bus);

	i2c_del_adapter(&av7110->i2c_adap);

	dvb_unरेजिस्टर_adapter (&av7110->dvb_adapter);

	av7110_num--;

	put_firmware(av7110);

	kमुक्त(av7110);

	saa->ext_priv = शून्य;

	वापस 0;
पूर्ण


अटल व्योम av7110_irq(काष्ठा saa7146_dev* dev, u32 *isr)
अणु
	काष्ठा av7110 *av7110 = dev->ext_priv;

	//prपूर्णांक_समय("av7110_irq");

	/* Note: Don't try to handle the DEBI error irq (MASK_18), in
	 * पूर्णांकel mode the समयout is निश्चितed all the समय...
	 */

	अगर (*isr & MASK_19) अणु
		//prपूर्णांकk("av7110_irq: DEBI\n");
		/* Note 1: The DEBI irq is level triggered: We must enable it
		 * only after we started a DMA xfer, and disable it here
		 * immediately, or it will be संकेतled all the समय जबतक
		 * DEBI is idle.
		 * Note 2: You would think that an irq which is masked is
		 * not संकेतled by the hardware. Not so क्रम the SAA7146:
		 * An irq is संकेतled as दीर्घ as the corresponding bit
		 * in the ISR is set, and disabling irqs just prevents the
		 * hardware from setting the ISR bit. This means a) that we
		 * must clear the ISR *after* disabling the irq (which is why
		 * we must करो it here even though saa7146_core did it alपढ़ोy),
		 * and b) that अगर we were to disable an edge triggered irq
		 * (like the gpio irqs sadly are) temporarily we would likely
		 * loose some. This sucks :-(
		 */
		SAA7146_IER_DISABLE(av7110->dev, MASK_19);
		SAA7146_ISR_CLEAR(av7110->dev, MASK_19);
		tasklet_schedule(&av7110->debi_tasklet);
	पूर्ण

	अगर (*isr & MASK_03) अणु
		//prपूर्णांकk("av7110_irq: GPIO\n");
		tasklet_schedule(&av7110->gpio_tasklet);
	पूर्ण

	अगर (*isr & MASK_10)
		tasklet_schedule(&av7110->vpe_tasklet);
पूर्ण


अटल काष्ठा saa7146_extension av7110_extension_driver;

#घोषणा MAKE_AV7110_INFO(x_var,x_name) \
अटल काष्ठा saa7146_pci_extension_data x_var = अणु \
	.ext_priv = x_name, \
	.ext = &av7110_extension_driver पूर्ण

MAKE_AV7110_INFO(tts_1_X_fsc,"Technotrend/Hauppauge WinTV DVB-S rev1.X or Fujitsu Siemens DVB-C");
MAKE_AV7110_INFO(ttt_1_X,    "Technotrend/Hauppauge WinTV DVB-T rev1.X");
MAKE_AV7110_INFO(ttc_1_X,    "Technotrend/Hauppauge WinTV Nexus-CA rev1.X");
MAKE_AV7110_INFO(ttc_2_X,    "Technotrend/Hauppauge WinTV DVB-C rev2.X");
MAKE_AV7110_INFO(tts_2_X,    "Technotrend/Hauppauge WinTV Nexus-S rev2.X");
MAKE_AV7110_INFO(tts_2_3,    "Technotrend/Hauppauge WinTV Nexus-S rev2.3");
MAKE_AV7110_INFO(tts_1_3se,  "Technotrend/Hauppauge WinTV DVB-S rev1.3 SE");
MAKE_AV7110_INFO(ttt,        "Technotrend/Hauppauge DVB-T");
MAKE_AV7110_INFO(fsc,        "Fujitsu Siemens DVB-C");
MAKE_AV7110_INFO(fss,        "Fujitsu Siemens DVB-S rev1.6");
MAKE_AV7110_INFO(gxs_1_3,    "Galaxis DVB-S rev1.3");

अटल स्थिर काष्ठा pci_device_id pci_tbl[] = अणु
	MAKE_EXTENSION_PCI(fsc,         0x110a, 0x0000),
	MAKE_EXTENSION_PCI(tts_1_X_fsc, 0x13c2, 0x0000),
	MAKE_EXTENSION_PCI(ttt_1_X,     0x13c2, 0x0001),
	MAKE_EXTENSION_PCI(ttc_2_X,     0x13c2, 0x0002),
	MAKE_EXTENSION_PCI(tts_2_X,     0x13c2, 0x0003),
	MAKE_EXTENSION_PCI(gxs_1_3,     0x13c2, 0x0004),
	MAKE_EXTENSION_PCI(fss,         0x13c2, 0x0006),
	MAKE_EXTENSION_PCI(ttt,         0x13c2, 0x0008),
	MAKE_EXTENSION_PCI(ttc_1_X,     0x13c2, 0x000a),
	MAKE_EXTENSION_PCI(tts_2_3,     0x13c2, 0x000e),
	MAKE_EXTENSION_PCI(tts_1_3se,   0x13c2, 0x1002),

/*	MAKE_EXTENSION_PCI(???, 0x13c2, 0x0005), UNDEFINED CARD */ // Technisat SkyStar1
/*	MAKE_EXTENSION_PCI(???, 0x13c2, 0x0009), UNDEFINED CARD */ // TT/Hauppauge WinTV Nexus-CA v????

	अणु
		.venकरोr    = 0,
	पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, pci_tbl);


अटल काष्ठा saa7146_extension av7110_extension_driver = अणु
	.name		= "av7110",
	.flags		= SAA7146_USE_I2C_IRQ,

	.module		= THIS_MODULE,
	.pci_tbl	= &pci_tbl[0],
	.attach		= av7110_attach,
	.detach		= av7110_detach,

	.irq_mask	= MASK_19 | MASK_03 | MASK_10,
	.irq_func	= av7110_irq,
पूर्ण;


अटल पूर्णांक __init av7110_init(व्योम)
अणु
	वापस saa7146_रेजिस्टर_extension(&av7110_extension_driver);
पूर्ण


अटल व्योम __निकास av7110_निकास(व्योम)
अणु
	saa7146_unरेजिस्टर_extension(&av7110_extension_driver);
पूर्ण

module_init(av7110_init);
module_निकास(av7110_निकास);

MODULE_DESCRIPTION("driver for the SAA7146 based AV110 PCI DVB cards by Siemens, Technotrend, Hauppauge");
MODULE_AUTHOR("Ralph Metzler, Marcus Metzler, others");
MODULE_LICENSE("GPL");
