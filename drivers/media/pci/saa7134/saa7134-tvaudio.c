<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * device driver क्रम philips saa7134 based TV cards
 * tv audio decoder (fm stereo, nicam, ...)
 *
 * (c) 2001-03 Gerd Knorr <kraxel@bytesex.org> [SuSE Lअसल]
 */

#समावेश "saa7134.h"
#समावेश "saa7134-reg.h"

#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/delay.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <यंत्र/भाग64.h>

/* ------------------------------------------------------------------ */

अटल अचिन्हित पूर्णांक audio_debug;
module_param(audio_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(audio_debug,"enable debug messages [tv audio]");

अटल अचिन्हित पूर्णांक audio_ddep;
module_param(audio_ddep, पूर्णांक, 0644);
MODULE_PARM_DESC(audio_ddep,"audio ddep overwrite");

अटल पूर्णांक audio_घड़ी_override = UNSET;
module_param(audio_घड़ी_override, पूर्णांक, 0644);

अटल पूर्णांक audio_घड़ी_प्रकारweak;
module_param(audio_घड़ी_प्रकारweak, पूर्णांक, 0644);
MODULE_PARM_DESC(audio_घड़ी_प्रकारweak, "Audio clock tick fine tuning for cards with audio crystal that's slightly off (range [-1024 .. 1024])");

#घोषणा audio_dbg(level, fmt, arg...) करो अणु \
	अगर (audio_debug >= level) \
		prपूर्णांकk(KERN_DEBUG pr_fmt("audio: " fmt), ## arg); \
	पूर्ण जबतक (0)

/* msecs */
#घोषणा SCAN_INITIAL_DELAY     1000
#घोषणा SCAN_SAMPLE_DELAY       200
#घोषणा SCAN_SUBCARRIER_DELAY  2000

/* ------------------------------------------------------------------ */
/* saa7134 code                                                       */

अटल काष्ठा मुख्यscan अणु
	अक्षर         *name;
	v4l2_std_id  std;
	पूर्णांक          carr;
पूर्ण मुख्यscan[] = अणु
	अणु
		.name = "MN",
		.std  = V4L2_STD_MN,
		.carr = 4500,
	पूर्ण,अणु
		.name = "BGH",
		.std  = V4L2_STD_B | V4L2_STD_GH,
		.carr = 5500,
	पूर्ण,अणु
		.name = "I",
		.std  = V4L2_STD_PAL_I,
		.carr = 6000,
	पूर्ण,अणु
		.name = "DKL",
		.std  = V4L2_STD_DK | V4L2_STD_SECAM_L | V4L2_STD_SECAM_LC,
		.carr = 6500,
	पूर्ण
पूर्ण;

अटल काष्ठा saa7134_tvaudio tvaudio[] = अणु
	अणु
		.name          = "PAL-B/G FM-stereo",
		.std           = V4L2_STD_PAL_BG,
		.mode          = TVAUDIO_FM_BG_STEREO,
		.carr1         = 5500,
		.carr2         = 5742,
	पूर्ण,अणु
		.name          = "PAL-D/K1 FM-stereo",
		.std           = V4L2_STD_PAL_DK,
		.carr1         = 6500,
		.carr2         = 6258,
		.mode          = TVAUDIO_FM_BG_STEREO,
	पूर्ण,अणु
		.name          = "PAL-D/K2 FM-stereo",
		.std           = V4L2_STD_PAL_DK,
		.carr1         = 6500,
		.carr2         = 6742,
		.mode          = TVAUDIO_FM_BG_STEREO,
	पूर्ण,अणु
		.name          = "PAL-D/K3 FM-stereo",
		.std           = V4L2_STD_PAL_DK,
		.carr1         = 6500,
		.carr2         = 5742,
		.mode          = TVAUDIO_FM_BG_STEREO,
	पूर्ण,अणु
		.name          = "PAL-B/G NICAM",
		.std           = V4L2_STD_PAL_BG,
		.carr1         = 5500,
		.carr2         = 5850,
		.mode          = TVAUDIO_NICAM_FM,
	पूर्ण,अणु
		.name          = "PAL-I NICAM",
		.std           = V4L2_STD_PAL_I,
		.carr1         = 6000,
		.carr2         = 6552,
		.mode          = TVAUDIO_NICAM_FM,
	पूर्ण,अणु
		.name          = "PAL-D/K NICAM",
		.std           = V4L2_STD_PAL_DK,
		.carr1         = 6500,
		.carr2         = 5850,
		.mode          = TVAUDIO_NICAM_FM,
	पूर्ण,अणु
		.name          = "SECAM-L NICAM",
		.std           = V4L2_STD_SECAM_L,
		.carr1         = 6500,
		.carr2         = 5850,
		.mode          = TVAUDIO_NICAM_AM,
	पूर्ण,अणु
		.name          = "SECAM-D/K NICAM",
		.std           = V4L2_STD_SECAM_DK,
		.carr1         = 6500,
		.carr2         = 5850,
		.mode          = TVAUDIO_NICAM_FM,
	पूर्ण,अणु
		.name          = "NTSC-A2 FM-stereo",
		.std           = V4L2_STD_NTSC,
		.carr1         = 4500,
		.carr2         = 4724,
		.mode          = TVAUDIO_FM_K_STEREO,
	पूर्ण,अणु
		.name          = "NTSC-M",
		.std           = V4L2_STD_NTSC,
		.carr1         = 4500,
		.carr2         = -1,
		.mode          = TVAUDIO_FM_MONO,
	पूर्ण
पूर्ण;
#घोषणा TVAUDIO ARRAY_SIZE(tvaudio)

/* ------------------------------------------------------------------ */

अटल u32 tvaudio_carr2reg(u32 carrier)
अणु
	u64 a = carrier;

	a <<= 24;
	करो_भाग(a,12288);
	वापस a;
पूर्ण

अटल व्योम tvaudio_setcarrier(काष्ठा saa7134_dev *dev,
			       पूर्णांक primary, पूर्णांक secondary)
अणु
	अगर (-1 == secondary)
		secondary = primary;
	saa_ग_लिखोl(SAA7134_CARRIER1_FREQ0 >> 2, tvaudio_carr2reg(primary));
	saa_ग_लिखोl(SAA7134_CARRIER2_FREQ0 >> 2, tvaudio_carr2reg(secondary));
पूर्ण

#घोषणा SAA7134_MUTE_MASK 0xbb
#घोषणा SAA7134_MUTE_ANALOG 0x04
#घोषणा SAA7134_MUTE_I2S 0x40

अटल व्योम mute_input_7134(काष्ठा saa7134_dev *dev)
अणु
	अचिन्हित पूर्णांक mute;
	काष्ठा saa7134_input *in;
	पूर्णांक ausel=0, ics=0, ocs=0;
	पूर्णांक mask;

	/* look what is to करो ... */
	in   = dev->input;
	mute = (dev->ctl_mute ||
		(dev->स्वतःmute  &&  (&card(dev).radio) != in));
	अगर (card(dev).mute.type) अणु
		/*
		 * 7130 - we'll mute using some unconnected audio input
		 * 7134 - we'll probably should चयन बाह्यal mux with gpio
		 */
		अगर (mute)
			in = &card(dev).mute;
	पूर्ण

	अगर (dev->hw_mute  == mute &&
		dev->hw_input == in && !dev->insuspend) अणु
		audio_dbg(1, "mute/input: nothing to do [mute=%d,input=%s]\n",
			  mute, saa7134_input_name[in->type]);
		वापस;
	पूर्ण

	audio_dbg(1, "ctl_mute=%d automute=%d input=%s  =>  mute=%d input=%s\n",
		  dev->ctl_mute, dev->स्वतःmute,
		  saa7134_input_name[dev->input->type], mute,
		  saa7134_input_name[in->type]);
	dev->hw_mute  = mute;
	dev->hw_input = in;

	अगर (PCI_DEVICE_ID_PHILIPS_SAA7134 == dev->pci->device)
		/* 7134 mute */
		saa_ग_लिखोb(SAA7134_AUDIO_MUTE_CTRL, mute ?
						    SAA7134_MUTE_MASK |
						    SAA7134_MUTE_ANALOG |
						    SAA7134_MUTE_I2S :
						    SAA7134_MUTE_MASK);

	/* चयन पूर्णांकernal audio mux */
	चयन (in->amux) अणु
	हाल TV:         ausel=0xc0; ics=0x00; ocs=0x02; अवरोध;
	हाल LINE1:      ausel=0x80; ics=0x00; ocs=0x00; अवरोध;
	हाल LINE2:      ausel=0x80; ics=0x08; ocs=0x01; अवरोध;
	हाल LINE2_LEFT: ausel=0x80; ics=0x08; ocs=0x05; अवरोध;
	पूर्ण
	saa_anकरोrb(SAA7134_AUDIO_FORMAT_CTRL, 0xc0, ausel);
	saa_anकरोrb(SAA7134_ANALOG_IO_SELECT, 0x08, ics);
	saa_anकरोrb(SAA7134_ANALOG_IO_SELECT, 0x07, ocs);
	// क्रम oss, we need to change the घड़ी configuration
	अगर (in->amux == TV)
		saa_anकरोrb(SAA7134_SIF_SAMPLE_FREQ,   0x03, 0x00);
	अन्यथा
		saa_anकरोrb(SAA7134_SIF_SAMPLE_FREQ,   0x03, 0x01);

	/* चयन gpio-connected बाह्यal audio mux */
	अगर (0 == card(dev).gpiomask)
		वापस;

	mask = card(dev).gpiomask;
	saa_anकरोrl(SAA7134_GPIO_GPMODE0 >> 2,   mask, mask);
	saa_anकरोrl(SAA7134_GPIO_GPSTATUS0 >> 2, mask, in->gpio);
	saa7134_track_gpio(dev, saa7134_input_name[in->type]);
पूर्ण

अटल व्योम tvaudio_seपंचांगode(काष्ठा saa7134_dev *dev,
			    काष्ठा saa7134_tvaudio *audio,
			    अक्षर *note)
अणु
	पूर्णांक acpf, tweak = 0;

	अगर (dev->tvnorm->id == V4L2_STD_NTSC) अणु
		acpf = 0x19066;
	पूर्ण अन्यथा अणु
		acpf = 0x1e000;
	पूर्ण
	अगर (audio_घड़ी_प्रकारweak > -1024 && audio_घड़ी_प्रकारweak < 1024)
		tweak = audio_घड़ी_प्रकारweak;

	अगर (note)
		audio_dbg(1, "tvaudio_setmode: %s %s [%d.%03d/%d.%03d MHz] acpf=%d%+d\n",
			note, audio->name,
			audio->carr1 / 1000, audio->carr1 % 1000,
			audio->carr2 / 1000, audio->carr2 % 1000,
			acpf, tweak);

	acpf += tweak;
	saa_ग_लिखोb(SAA7134_AUDIO_CLOCKS_PER_FIELD0, (acpf & 0x0000ff) >> 0);
	saa_ग_लिखोb(SAA7134_AUDIO_CLOCKS_PER_FIELD1, (acpf & 0x00ff00) >> 8);
	saa_ग_लिखोb(SAA7134_AUDIO_CLOCKS_PER_FIELD2, (acpf & 0x030000) >> 16);
	tvaudio_setcarrier(dev,audio->carr1,audio->carr2);

	चयन (audio->mode) अणु
	हाल TVAUDIO_FM_MONO:
	हाल TVAUDIO_FM_BG_STEREO:
		saa_ग_लिखोb(SAA7134_DEMODULATOR,               0x00);
		saa_ग_लिखोb(SAA7134_DCXO_IDENT_CTRL,           0x00);
		saa_ग_लिखोb(SAA7134_FM_DEEMPHASIS,             0x22);
		saa_ग_लिखोb(SAA7134_FM_DEMATRIX,               0x80);
		saa_ग_लिखोb(SAA7134_STEREO_DAC_OUTPUT_SELECT,  0xa0);
		अवरोध;
	हाल TVAUDIO_FM_K_STEREO:
		saa_ग_लिखोb(SAA7134_DEMODULATOR,               0x00);
		saa_ग_लिखोb(SAA7134_DCXO_IDENT_CTRL,           0x01);
		saa_ग_लिखोb(SAA7134_FM_DEEMPHASIS,             0x22);
		saa_ग_लिखोb(SAA7134_FM_DEMATRIX,               0x80);
		saa_ग_लिखोb(SAA7134_STEREO_DAC_OUTPUT_SELECT,  0xa0);
		अवरोध;
	हाल TVAUDIO_NICAM_FM:
		saa_ग_लिखोb(SAA7134_DEMODULATOR,               0x10);
		saa_ग_लिखोb(SAA7134_DCXO_IDENT_CTRL,           0x00);
		saa_ग_लिखोb(SAA7134_FM_DEEMPHASIS,             0x44);
		saa_ग_लिखोb(SAA7134_STEREO_DAC_OUTPUT_SELECT,  0xa1);
		saa_ग_लिखोb(SAA7134_NICAM_CONFIG,              0x00);
		अवरोध;
	हाल TVAUDIO_NICAM_AM:
		saa_ग_लिखोb(SAA7134_DEMODULATOR,               0x12);
		saa_ग_लिखोb(SAA7134_DCXO_IDENT_CTRL,           0x00);
		saa_ग_लिखोb(SAA7134_FM_DEEMPHASIS,             0x44);
		saa_ग_लिखोb(SAA7134_STEREO_DAC_OUTPUT_SELECT,  0xa1);
		saa_ग_लिखोb(SAA7134_NICAM_CONFIG,              0x00);
		अवरोध;
	हाल TVAUDIO_FM_SAT_STEREO:
		/* not implemented (yet) */
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक tvaudio_sleep(काष्ठा saa7134_dev *dev, पूर्णांक समयout)
अणु
	अगर (dev->thपढ़ो.scan1 == dev->thपढ़ो.scan2 &&
	    !kthपढ़ो_should_stop()) अणु
		अगर (समयout < 0) अणु
			set_current_state(TASK_INTERRUPTIBLE);
			schedule();
		पूर्ण अन्यथा अणु
			schedule_समयout_पूर्णांकerruptible
						(msecs_to_jअगरfies(समयout));
		पूर्ण
	पूर्ण
	वापस dev->thपढ़ो.scan1 != dev->thपढ़ो.scan2;
पूर्ण

अटल पूर्णांक tvaudio_checkcarrier(काष्ठा saa7134_dev *dev, काष्ठा मुख्यscan *scan)
अणु
	__s32 left,right,value;

	अगर (!(dev->tvnorm->id & scan->std)) अणु
		audio_dbg(1, "skipping %d.%03d MHz [%4s]\n",
			  scan->carr / 1000, scan->carr % 1000, scan->name);
		वापस 0;
	पूर्ण

	अगर (audio_debug > 1) अणु
		पूर्णांक i;
		audio_dbg(1, "debug %d:", scan->carr);
		क्रम (i = -150; i <= 150; i += 30) अणु
			tvaudio_setcarrier(dev,scan->carr+i,scan->carr+i);
			saa_पढ़ोl(SAA7134_LEVEL_READOUT1 >> 2);
			अगर (tvaudio_sleep(dev,SCAN_SAMPLE_DELAY))
				वापस -1;
			value = saa_पढ़ोl(SAA7134_LEVEL_READOUT1 >> 2);
			अगर (0 == i)
				pr_cont("  #  %6d  # ", value >> 16);
			अन्यथा
				pr_cont(" %6d", value >> 16);
		पूर्ण
		pr_cont("\n");
	पूर्ण

	tvaudio_setcarrier(dev,scan->carr-90,scan->carr-90);
	saa_पढ़ोl(SAA7134_LEVEL_READOUT1 >> 2);
	अगर (tvaudio_sleep(dev,SCAN_SAMPLE_DELAY))
		वापस -1;
	left = saa_पढ़ोl(SAA7134_LEVEL_READOUT1 >> 2);

	tvaudio_setcarrier(dev,scan->carr+90,scan->carr+90);
	saa_पढ़ोl(SAA7134_LEVEL_READOUT1 >> 2);
	अगर (tvaudio_sleep(dev,SCAN_SAMPLE_DELAY))
		वापस -1;
	right = saa_पढ़ोl(SAA7134_LEVEL_READOUT1 >> 2);

	left >>= 16;
	right >>= 16;
	value = left > right ? left - right : right - left;
	audio_dbg(1, "scanning %d.%03d MHz [%4s] =>  dc is %5d [%d/%d]\n",
		  scan->carr / 1000, scan->carr % 1000,
		  scan->name, value, left, right);
	वापस value;
पूर्ण


अटल पूर्णांक tvaudio_माला_लोtereo(काष्ठा saa7134_dev *dev, काष्ठा saa7134_tvaudio *audio)
अणु
	__u32 idp, nicam, nicam_status;
	पूर्णांक retval = -1;

	चयन (audio->mode) अणु
	हाल TVAUDIO_FM_MONO:
		वापस V4L2_TUNER_SUB_MONO;
	हाल TVAUDIO_FM_K_STEREO:
	हाल TVAUDIO_FM_BG_STEREO:
		idp = (saa_पढ़ोb(SAA7134_IDENT_SIF) & 0xe0) >> 5;
		audio_dbg(1, "getstereo: fm/stereo: idp=0x%x\n", idp);
		अगर (0x03 == (idp & 0x03))
			retval = V4L2_TUNER_SUB_LANG1 | V4L2_TUNER_SUB_LANG2;
		अन्यथा अगर (0x05 == (idp & 0x05))
			retval = V4L2_TUNER_SUB_MONO | V4L2_TUNER_SUB_STEREO;
		अन्यथा अगर (0x01 == (idp & 0x01))
			retval = V4L2_TUNER_SUB_MONO;
		अवरोध;
	हाल TVAUDIO_FM_SAT_STEREO:
		/* not implemented (yet) */
		अवरोध;
	हाल TVAUDIO_NICAM_FM:
	हाल TVAUDIO_NICAM_AM:
		nicam = saa_पढ़ोb(SAA7134_AUDIO_STATUS);
		audio_dbg(1, "getstereo: nicam=0x%x\n", nicam);
		अगर (nicam & 0x1) अणु
			nicam_status = saa_पढ़ोb(SAA7134_NICAM_STATUS);
			audio_dbg(1, "getstereo: nicam_status=0x%x\n",
				  nicam_status);

			चयन (nicam_status & 0x03) अणु
			    हाल 0x01:
				retval = V4L2_TUNER_SUB_LANG1 | V4L2_TUNER_SUB_LANG2;
				अवरोध;
			    हाल 0x02:
				retval = V4L2_TUNER_SUB_MONO | V4L2_TUNER_SUB_STEREO;
				अवरोध;
			    शेष:
				retval = V4L2_TUNER_SUB_MONO;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* No nicam detected */
		पूर्ण
		अवरोध;
	पूर्ण
	अगर (retval != -1)
		audio_dbg(1, "found audio subchannels:%s%s%s%s\n",
			(retval & V4L2_TUNER_SUB_MONO)   ? " mono"   : "",
			(retval & V4L2_TUNER_SUB_STEREO) ? " stereo" : "",
			(retval & V4L2_TUNER_SUB_LANG1)  ? " lang1"  : "",
			(retval & V4L2_TUNER_SUB_LANG2)  ? " lang2"  : "");
	वापस retval;
पूर्ण

अटल पूर्णांक tvaudio_setstereo(काष्ठा saa7134_dev *dev, काष्ठा saa7134_tvaudio *audio,
			     u32 mode)
अणु
	अटल अक्षर *name[] = अणु
		[ V4L2_TUNER_MODE_MONO   ] = "mono",
		[ V4L2_TUNER_MODE_STEREO ] = "stereo",
		[ V4L2_TUNER_MODE_LANG1  ] = "lang1",
		[ V4L2_TUNER_MODE_LANG2  ] = "lang2",
		[ V4L2_TUNER_MODE_LANG1_LANG2  ] = "lang1+lang2",
	पूर्ण;
	अटल u32 fm[] = अणु
		[ V4L2_TUNER_MODE_MONO   ] = 0x00,  /* ch1  */
		[ V4L2_TUNER_MODE_STEREO ] = 0x80,  /* स्वतः */
		[ V4L2_TUNER_MODE_LANG1  ] = 0x00,  /* ch1  */
		[ V4L2_TUNER_MODE_LANG2  ] = 0x01,  /* ch2  */
		[ V4L2_TUNER_MODE_LANG1_LANG2 ] = 0x80,  /* स्वतः */
	पूर्ण;
	u32 reg;

	चयन (audio->mode) अणु
	हाल TVAUDIO_FM_MONO:
		/* nothing to करो ... */
		अवरोध;
	हाल TVAUDIO_FM_K_STEREO:
	हाल TVAUDIO_FM_BG_STEREO:
	हाल TVAUDIO_NICAM_AM:
	हाल TVAUDIO_NICAM_FM:
		audio_dbg(1, "setstereo [fm] => %s\n",
			  name[mode % ARRAY_SIZE(name)]);
		reg = fm[ mode % ARRAY_SIZE(fm) ];
		saa_ग_लिखोb(SAA7134_FM_DEMATRIX, reg);
		अवरोध;
	हाल TVAUDIO_FM_SAT_STEREO:
		/* Not implemented */
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tvaudio_thपढ़ो(व्योम *data)
अणु
	काष्ठा saa7134_dev *dev = data;
	पूर्णांक carr_vals[ARRAY_SIZE(मुख्यscan)];
	अचिन्हित पूर्णांक i, audio, nscan;
	पूर्णांक max1,max2,carrier,rx,mode,lasपंचांगode,शेष_carrier;

	set_मुक्तzable();

	क्रम (;;) अणु
		tvaudio_sleep(dev,-1);
		अगर (kthपढ़ो_should_stop())
			जाओ करोne;

	restart:
		try_to_मुक्तze();

		dev->thपढ़ो.scan1 = dev->thपढ़ो.scan2;
		audio_dbg(1, "tvaudio thread scan start [%d]\n",
			  dev->thपढ़ो.scan1);
		dev->tvaudio  = शून्य;

		saa_ग_लिखोb(SAA7134_MONITOR_SELECT,   0xa0);
		saa_ग_लिखोb(SAA7134_FM_DEMATRIX,      0x80);

		अगर (dev->ctl_स्वतःmute)
			dev->स्वतःmute = 1;

		mute_input_7134(dev);

		/* give the tuner some समय */
		अगर (tvaudio_sleep(dev,SCAN_INITIAL_DELAY))
			जाओ restart;

		max1 = 0;
		max2 = 0;
		nscan = 0;
		carrier = 0;
		शेष_carrier = 0;
		क्रम (i = 0; i < ARRAY_SIZE(मुख्यscan); i++) अणु
			अगर (!(dev->tvnorm->id & मुख्यscan[i].std))
				जारी;
			अगर (!शेष_carrier)
				शेष_carrier = मुख्यscan[i].carr;
			nscan++;
		पूर्ण

		अगर (1 == nscan) अणु
			/* only one candidate -- skip scan ;) */
			audio_dbg(1, "only one main carrier candidate - skipping scan\n");
			max1 = 12345;
			carrier = शेष_carrier;
		पूर्ण अन्यथा अणु
			/* scan क्रम the मुख्य carrier */
			saa_ग_लिखोb(SAA7134_MONITOR_SELECT,0x00);
			tvaudio_seपंचांगode(dev,&tvaudio[0],शून्य);
			क्रम (i = 0; i < ARRAY_SIZE(मुख्यscan); i++) अणु
				carr_vals[i] = tvaudio_checkcarrier(dev, मुख्यscan+i);
				अगर (dev->thपढ़ो.scan1 != dev->thपढ़ो.scan2)
					जाओ restart;
			पूर्ण
			क्रम (max1 = 0, max2 = 0, i = 0; i < ARRAY_SIZE(मुख्यscan); i++) अणु
				अगर (max1 < carr_vals[i]) अणु
					max2 = max1;
					max1 = carr_vals[i];
					carrier = मुख्यscan[i].carr;
				पूर्ण अन्यथा अगर (max2 < carr_vals[i]) अणु
					max2 = carr_vals[i];
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (0 != carrier && max1 > 2000 && max1 > max2*3) अणु
			/* found good carrier */
			audio_dbg(1, "found %s main sound carrier @ %d.%03d MHz [%d/%d]\n",
				  dev->tvnorm->name, carrier/1000, carrier%1000,
				  max1, max2);
			dev->last_carrier = carrier;
			dev->स्वतःmute = 0;

		पूर्ण अन्यथा अगर (0 != dev->last_carrier) अणु
			/* no carrier -- try last detected one as fallback */
			carrier = dev->last_carrier;
			audio_dbg(1, "audio carrier scan failed, using %d.%03d MHz [last detected]\n",
				  carrier/1000, carrier%1000);
			dev->स्वतःmute = 1;

		पूर्ण अन्यथा अणु
			/* no carrier + no fallback -- use शेष */
			carrier = शेष_carrier;
			audio_dbg(1, "audio carrier scan failed, using %d.%03d MHz [default]\n",
				  carrier/1000, carrier%1000);
			dev->स्वतःmute = 1;
		पूर्ण
		tvaudio_setcarrier(dev,carrier,carrier);
		saa_anकरोrb(SAA7134_STEREO_DAC_OUTPUT_SELECT, 0x30, 0x00);
		saa7134_tvaudio_seपंचांगute(dev);
		/* find the exact tv audio norm */
		क्रम (audio = UNSET, i = 0; i < TVAUDIO; i++) अणु
			अगर (dev->tvnorm->id != UNSET &&
				!(dev->tvnorm->id & tvaudio[i].std))
				जारी;
			अगर (tvaudio[i].carr1 != carrier)
				जारी;
			/* Note: at least the primary carrier is right here */
			अगर (UNSET == audio)
				audio = i;
			tvaudio_seपंचांगode(dev,&tvaudio[i],"trying");
			अगर (tvaudio_sleep(dev,SCAN_SUBCARRIER_DELAY))
				जाओ restart;
			अगर (-1 != tvaudio_माला_लोtereo(dev,&tvaudio[i])) अणु
				audio = i;
				अवरोध;
			पूर्ण
		पूर्ण
		saa_anकरोrb(SAA7134_STEREO_DAC_OUTPUT_SELECT, 0x30, 0x30);
		अगर (UNSET == audio)
			जारी;
		tvaudio_seपंचांगode(dev,&tvaudio[audio],"using");

		tvaudio_setstereo(dev,&tvaudio[audio],V4L2_TUNER_MODE_MONO);
		dev->tvaudio = &tvaudio[audio];

		lasपंचांगode = 42;
		क्रम (;;) अणु

			try_to_मुक्तze();

			अगर (tvaudio_sleep(dev,5000))
				जाओ restart;
			अगर (kthपढ़ो_should_stop())
				अवरोध;
			अगर (UNSET == dev->thपढ़ो.mode) अणु
				rx = tvaudio_माला_लोtereo(dev, &tvaudio[audio]);
				mode = saa7134_tvaudio_rx2mode(rx);
			पूर्ण अन्यथा अणु
				mode = dev->thपढ़ो.mode;
			पूर्ण
			अगर (lasपंचांगode != mode) अणु
				tvaudio_setstereo(dev,&tvaudio[audio],mode);
				lasपंचांगode = mode;
			पूर्ण
		पूर्ण
	पूर्ण

 करोne:
	dev->thपढ़ो.stopped = 1;
	वापस 0;
पूर्ण

/* ------------------------------------------------------------------ */
/* saa7133 / saa7135 code                                             */

अटल अक्षर *stdres[0x20] = अणु
	[0x00] = "no standard detected",
	[0x01] = "B/G (in progress)",
	[0x02] = "D/K (in progress)",
	[0x03] = "M (in progress)",

	[0x04] = "B/G A2",
	[0x05] = "B/G NICAM",
	[0x06] = "D/K A2 (1)",
	[0x07] = "D/K A2 (2)",
	[0x08] = "D/K A2 (3)",
	[0x09] = "D/K NICAM",
	[0x0a] = "L NICAM",
	[0x0b] = "I NICAM",

	[0x0c] = "M Korea",
	[0x0d] = "M BTSC ",
	[0x0e] = "M EIAJ",

	[0x0f] = "FM radio / IF 10.7 / 50 deemp",
	[0x10] = "FM radio / IF 10.7 / 75 deemp",
	[0x11] = "FM radio / IF sel / 50 deemp",
	[0x12] = "FM radio / IF sel / 75 deemp",

	[0x13 ... 0x1e ] = "unknown",
	[0x1f] = "??? [in progress]",
पूर्ण;

#घोषणा DSP_RETRY 32
#घोषणा DSP_DELAY 16
#घोषणा SAA7135_DSP_RWCLEAR_RERR 1

अटल अंतरभूत पूर्णांक saa_dsp_reset_error_bit(काष्ठा saa7134_dev *dev)
अणु
	पूर्णांक state = saa_पढ़ोb(SAA7135_DSP_RWSTATE);
	अगर (unlikely(state & SAA7135_DSP_RWSTATE_ERR)) अणु
		audio_dbg(2, "%s: resetting error bit\n", dev->name);
		saa_ग_लिखोb(SAA7135_DSP_RWCLEAR, SAA7135_DSP_RWCLEAR_RERR);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक saa_dsp_रुको_bit(काष्ठा saa7134_dev *dev, पूर्णांक bit)
अणु
	पूर्णांक state, count = DSP_RETRY;

	state = saa_पढ़ोb(SAA7135_DSP_RWSTATE);
	अगर (unlikely(state & SAA7135_DSP_RWSTATE_ERR)) अणु
		pr_warn("%s: dsp access error\n", dev->name);
		saa_dsp_reset_error_bit(dev);
		वापस -EIO;
	पूर्ण
	जबतक (0 == (state & bit)) अणु
		अगर (unlikely(0 == count)) अणु
			pr_err("dsp access wait timeout [bit=%s]\n",
				 (bit & SAA7135_DSP_RWSTATE_WRR) ? "WRR" :
				 (bit & SAA7135_DSP_RWSTATE_RDB) ? "RDB" :
				 (bit & SAA7135_DSP_RWSTATE_IDA) ? "IDA" :
				 "???");
			वापस -EIO;
		पूर्ण
		saa_रुको(DSP_DELAY);
		state = saa_पढ़ोb(SAA7135_DSP_RWSTATE);
		count--;
	पूर्ण
	वापस 0;
पूर्ण


पूर्णांक saa_dsp_ग_लिखोl(काष्ठा saa7134_dev *dev, पूर्णांक reg, u32 value)
अणु
	पूर्णांक err;

	audio_dbg(2, "dsp write reg 0x%x = 0x%06x\n",
		  (reg << 2) & 0xffffffff, value);
	err = saa_dsp_रुको_bit(dev,SAA7135_DSP_RWSTATE_WRR);
	अगर (err < 0)
		वापस err;
	saa_ग_लिखोl(reg,value);
	err = saa_dsp_रुको_bit(dev,SAA7135_DSP_RWSTATE_WRR);
	अगर (err < 0)
		वापस err;
	वापस 0;
पूर्ण

अटल पूर्णांक माला_लोtereo_7133(काष्ठा saa7134_dev *dev)
अणु
	पूर्णांक retval = V4L2_TUNER_SUB_MONO;
	u32 value;

	value = saa_पढ़ोl(0x528 >> 2);
	अगर (value & 0x20)
		retval = V4L2_TUNER_SUB_MONO | V4L2_TUNER_SUB_STEREO;
	अगर (value & 0x40)
		retval = V4L2_TUNER_SUB_LANG1 | V4L2_TUNER_SUB_LANG2;
	वापस retval;
पूर्ण

अटल पूर्णांक mute_input_7133(काष्ठा saa7134_dev *dev)
अणु
	u32 reg = 0;
	u32 xbarin, xbarout;
	पूर्णांक mask;
	काष्ठा saa7134_input *in;

	xbarin = 0x03;
	चयन (dev->input->amux) अणु
	हाल TV:
		reg = 0x02;
		xbarin = 0;
		अवरोध;
	हाल LINE1:
		reg = 0x00;
		अवरोध;
	हाल LINE2:
	हाल LINE2_LEFT:
		reg = 0x09;
		अवरोध;
	पूर्ण
	saa_dsp_ग_लिखोl(dev, 0x464 >> 2, xbarin);
	अगर (dev->ctl_mute) अणु
		reg = 0x07;
		xbarout = 0xbbbbbb;
	पूर्ण अन्यथा
		xbarout = 0xbbbb10;
	saa_dsp_ग_लिखोl(dev, 0x46c >> 2, xbarout);

	saa_ग_लिखोl(0x594 >> 2, reg);


	/* चयन gpio-connected बाह्यal audio mux */
	अगर (0 != card(dev).gpiomask) अणु
		mask = card(dev).gpiomask;

		अगर (card(dev).mute.type && dev->ctl_mute)
			in = &card(dev).mute;
		अन्यथा
			in = dev->input;

		saa_anकरोrl(SAA7134_GPIO_GPMODE0 >> 2,   mask, mask);
		saa_anकरोrl(SAA7134_GPIO_GPSTATUS0 >> 2, mask, in->gpio);
		saa7134_track_gpio(dev, saa7134_input_name[in->type]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tvaudio_thपढ़ो_ddep(व्योम *data)
अणु
	काष्ठा saa7134_dev *dev = data;
	u32 value, norms;

	set_मुक्तzable();
	क्रम (;;) अणु
		tvaudio_sleep(dev,-1);
		अगर (kthपढ़ो_should_stop())
			जाओ करोne;
	restart:
		try_to_मुक्तze();

		dev->thपढ़ो.scan1 = dev->thपढ़ो.scan2;
		audio_dbg(1, "tvaudio thread scan start [%d]\n",
			  dev->thपढ़ो.scan1);

		अगर (audio_ddep >= 0x04 && audio_ddep <= 0x0e) अणु
			/* insmod option override */
			norms = (audio_ddep << 2) | 0x01;
			audio_dbg(1, "ddep override: %s\n",
				  stdres[audio_ddep]);
		पूर्ण अन्यथा अगर (&card(dev).radio == dev->input) अणु
			audio_dbg(1, "FM Radio\n");
			अगर (dev->tuner_type == TUNER_PHILIPS_TDA8290) अणु
				norms = (0x11 << 2) | 0x01;
				/* set IF frequency to 5.5 MHz */
				saa_dsp_ग_लिखोl(dev, 0x42c >> 2, 0x729555);
			पूर्ण अन्यथा अणु
				norms = (0x0f << 2) | 0x01;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* (let chip) scan क्रम sound carrier */
			norms = 0;
			अगर (dev->tvnorm->id & (V4L2_STD_B | V4L2_STD_GH))
				norms |= 0x04;
			अगर (dev->tvnorm->id & V4L2_STD_PAL_I)
				norms |= 0x20;
			अगर (dev->tvnorm->id & V4L2_STD_DK)
				norms |= 0x08;
			अगर (dev->tvnorm->id & V4L2_STD_MN)
				norms |= 0x40;
			अगर (dev->tvnorm->id & (V4L2_STD_SECAM_L | V4L2_STD_SECAM_LC))
				norms |= 0x10;
			अगर (0 == norms)
				norms = 0x7c; /* all */
			audio_dbg(1, "scanning:%s%s%s%s%s\n",
				  (norms & 0x04) ? " B/G"  : "",
				  (norms & 0x08) ? " D/K"  : "",
				  (norms & 0x10) ? " L/L'" : "",
				  (norms & 0x20) ? " I"    : "",
				  (norms & 0x40) ? " M"    : "");
		पूर्ण

		/* kick स्वतःmatic standard detection */
		saa_dsp_ग_लिखोl(dev, 0x454 >> 2, 0);
		saa_dsp_ग_लिखोl(dev, 0x454 >> 2, norms | 0x80);

		/* setup crossbars */
		saa_dsp_ग_लिखोl(dev, 0x464 >> 2, 0x000000);
		saa_dsp_ग_लिखोl(dev, 0x470 >> 2, 0x101010);

		अगर (tvaudio_sleep(dev,3000))
			जाओ restart;
		value = saa_पढ़ोl(0x528 >> 2) & 0xffffff;

		audio_dbg(1, "tvaudio thread status: 0x%x [%s%s%s]\n",
			  value, stdres[value & 0x1f],
			  (value & 0x000020) ? ",stereo" : "",
			  (value & 0x000040) ? ",dual"   : "");
		audio_dbg(1, "detailed status: %s#%s#%s#%s#%s#%s#%s#%s#%s#%s#%s#%s#%s#%s\n",
			  (value & 0x000080) ? " A2/EIAJ pilot tone "     : "",
			  (value & 0x000100) ? " A2/EIAJ dual "           : "",
			  (value & 0x000200) ? " A2/EIAJ stereo "         : "",
			  (value & 0x000400) ? " A2/EIAJ noise mute "     : "",

			  (value & 0x000800) ? " BTSC/FM radio pilot "    : "",
			  (value & 0x001000) ? " SAP carrier "            : "",
			  (value & 0x002000) ? " BTSC stereo noise mute " : "",
			  (value & 0x004000) ? " SAP noise mute "         : "",
			  (value & 0x008000) ? " VDSP "                   : "",

			  (value & 0x010000) ? " NICST "                  : "",
			  (value & 0x020000) ? " NICDU "                  : "",
			  (value & 0x040000) ? " NICAM muted "            : "",
			  (value & 0x080000) ? " NICAM reserve sound "    : "",

			  (value & 0x100000) ? " init done "              : "");
	पूर्ण

 करोne:
	dev->thपढ़ो.stopped = 1;
	वापस 0;
पूर्ण

/* ------------------------------------------------------------------ */
/* common stuff + बाह्यal entry poपूर्णांकs                               */

व्योम saa7134_enable_i2s(काष्ठा saa7134_dev *dev)
अणु
	पूर्णांक i2s_क्रमmat;

	अगर (!card_is_empress(dev))
		वापस;

	अगर (dev->pci->device == PCI_DEVICE_ID_PHILIPS_SAA7130)
		वापस;

	/* configure GPIO क्रम out */
	saa_anकरोrl(SAA7134_GPIO_GPMODE0 >> 2, 0x0E000000, 0x00000000);

	चयन (dev->pci->device) अणु
	हाल PCI_DEVICE_ID_PHILIPS_SAA7133:
	हाल PCI_DEVICE_ID_PHILIPS_SAA7135:
		/* Set I2S क्रमmat (SONY) त */
		saa_ग_लिखोb(SAA7133_I2S_AUDIO_CONTROL, 0x00);
		/* Start I2S */
		saa_ग_लिखोb(SAA7134_I2S_AUDIO_OUTPUT, 0x11);
		अवरोध;

	हाल PCI_DEVICE_ID_PHILIPS_SAA7134:
		i2s_क्रमmat = (dev->input->amux == TV) ? 0x00 : 0x01;

		/* enable I2S audio output क्रम the mpeg encoder */
		saa_ग_लिखोb(SAA7134_I2S_OUTPUT_SELECT, 0x80);
		saa_ग_लिखोb(SAA7134_I2S_OUTPUT_FORMAT, i2s_क्रमmat);
		saa_ग_लिखोb(SAA7134_I2S_OUTPUT_LEVEL,  0x0F);
		saa_ग_लिखोb(SAA7134_I2S_AUDIO_OUTPUT,  0x01);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक saa7134_tvaudio_rx2mode(u32 rx)
अणु
	u32 mode;

	mode = V4L2_TUNER_MODE_MONO;
	अगर (rx & V4L2_TUNER_SUB_STEREO)
		mode = V4L2_TUNER_MODE_STEREO;
	अन्यथा अगर (rx & V4L2_TUNER_SUB_LANG1)
		mode = V4L2_TUNER_MODE_LANG1;
	अन्यथा अगर (rx & V4L2_TUNER_SUB_LANG2)
		mode = V4L2_TUNER_MODE_LANG2;
	वापस mode;
पूर्ण

व्योम saa7134_tvaudio_seपंचांगute(काष्ठा saa7134_dev *dev)
अणु
	चयन (dev->pci->device) अणु
	हाल PCI_DEVICE_ID_PHILIPS_SAA7130:
	हाल PCI_DEVICE_ID_PHILIPS_SAA7134:
		mute_input_7134(dev);
		अवरोध;
	हाल PCI_DEVICE_ID_PHILIPS_SAA7133:
	हाल PCI_DEVICE_ID_PHILIPS_SAA7135:
		mute_input_7133(dev);
		अवरोध;
	पूर्ण
पूर्ण

व्योम saa7134_tvaudio_setinput(काष्ठा saa7134_dev *dev,
			      काष्ठा saa7134_input *in)
अणु
	dev->input = in;
	चयन (dev->pci->device) अणु
	हाल PCI_DEVICE_ID_PHILIPS_SAA7130:
	हाल PCI_DEVICE_ID_PHILIPS_SAA7134:
		mute_input_7134(dev);
		अवरोध;
	हाल PCI_DEVICE_ID_PHILIPS_SAA7133:
	हाल PCI_DEVICE_ID_PHILIPS_SAA7135:
		mute_input_7133(dev);
		अवरोध;
	पूर्ण
	saa7134_enable_i2s(dev);
पूर्ण

व्योम saa7134_tvaudio_setvolume(काष्ठा saa7134_dev *dev, पूर्णांक level)
अणु
	चयन (dev->pci->device) अणु
	हाल PCI_DEVICE_ID_PHILIPS_SAA7134:
		saa_ग_लिखोb(SAA7134_CHANNEL1_LEVEL,     level & 0x1f);
		saa_ग_लिखोb(SAA7134_CHANNEL2_LEVEL,     level & 0x1f);
		saa_ग_लिखोb(SAA7134_NICAM_LEVEL_ADJUST, level & 0x1f);
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक saa7134_tvaudio_माला_लोtereo(काष्ठा saa7134_dev *dev)
अणु
	पूर्णांक retval = V4L2_TUNER_SUB_MONO;

	चयन (dev->pci->device) अणु
	हाल PCI_DEVICE_ID_PHILIPS_SAA7134:
		अगर (dev->tvaudio)
			retval = tvaudio_माला_लोtereo(dev,dev->tvaudio);
		अवरोध;
	हाल PCI_DEVICE_ID_PHILIPS_SAA7133:
	हाल PCI_DEVICE_ID_PHILIPS_SAA7135:
		retval = माला_लोtereo_7133(dev);
		अवरोध;
	पूर्ण
	वापस retval;
पूर्ण

व्योम saa7134_tvaudio_init(काष्ठा saa7134_dev *dev)
अणु
	पूर्णांक घड़ी = saa7134_boards[dev->board].audio_घड़ी;

	अगर (UNSET != audio_घड़ी_override)
		घड़ी = audio_घड़ी_override;

	चयन (dev->pci->device) अणु
	हाल PCI_DEVICE_ID_PHILIPS_SAA7134:
		/* init all audio रेजिस्टरs */
		saa_ग_लिखोb(SAA7134_AUDIO_PLL_CTRL,   0x00);
		अगर (need_resched())
			schedule();
		अन्यथा
			udelay(10);

		saa_ग_लिखोb(SAA7134_AUDIO_CLOCK0,      घड़ी        & 0xff);
		saa_ग_लिखोb(SAA7134_AUDIO_CLOCK1,     (घड़ी >>  8) & 0xff);
		saa_ग_लिखोb(SAA7134_AUDIO_CLOCK2,     (घड़ी >> 16) & 0xff);
		/* frame locked audio is mandatory क्रम NICAM */
		saa_ग_लिखोb(SAA7134_AUDIO_PLL_CTRL,   0x01);
		saa_ग_लिखोb(SAA7134_NICAM_ERROR_LOW,  0x14);
		saa_ग_लिखोb(SAA7134_NICAM_ERROR_HIGH, 0x50);
		अवरोध;
	हाल PCI_DEVICE_ID_PHILIPS_SAA7133:
	हाल PCI_DEVICE_ID_PHILIPS_SAA7135:
		saa_ग_लिखोl(0x598 >> 2, घड़ी);
		saa_dsp_ग_लिखोl(dev, 0x474 >> 2, 0x00);
		saa_dsp_ग_लिखोl(dev, 0x450 >> 2, 0x00);
	पूर्ण
पूर्ण

पूर्णांक saa7134_tvaudio_init2(काष्ठा saa7134_dev *dev)
अणु
	पूर्णांक (*my_thपढ़ो)(व्योम *data) = शून्य;

	चयन (dev->pci->device) अणु
	हाल PCI_DEVICE_ID_PHILIPS_SAA7134:
		my_thपढ़ो = tvaudio_thपढ़ो;
		अवरोध;
	हाल PCI_DEVICE_ID_PHILIPS_SAA7133:
	हाल PCI_DEVICE_ID_PHILIPS_SAA7135:
		my_thपढ़ो = tvaudio_thपढ़ो_ddep;
		अवरोध;
	पूर्ण

	dev->thपढ़ो.thपढ़ो = शून्य;
	dev->thपढ़ो.scan1 = dev->thपढ़ो.scan2 = 0;
	अगर (my_thपढ़ो) अणु
		saa7134_tvaudio_init(dev);
		/* start tvaudio thपढ़ो */
		dev->thपढ़ो.thपढ़ो = kthपढ़ो_run(my_thपढ़ो, dev, "%s", dev->name);
		अगर (IS_ERR(dev->thपढ़ो.thपढ़ो)) अणु
			pr_warn("%s: kernel_thread() failed\n",
			       dev->name);
			/* XXX: missing error handling here */
		पूर्ण
	पूर्ण

	saa7134_enable_i2s(dev);
	वापस 0;
पूर्ण

पूर्णांक saa7134_tvaudio_बंद(काष्ठा saa7134_dev *dev)
अणु
	dev->स्वतःmute = 1;
	/* anything अन्यथा to unकरो? */
	वापस 0;
पूर्ण

पूर्णांक saa7134_tvaudio_fini(काष्ठा saa7134_dev *dev)
अणु
	/* shutकरोwn tvaudio thपढ़ो */
	अगर (dev->thपढ़ो.thपढ़ो && !dev->thपढ़ो.stopped)
		kthपढ़ो_stop(dev->thपढ़ो.thपढ़ो);

	saa_anकरोrb(SAA7134_ANALOG_IO_SELECT, 0x07, 0x00); /* LINE1 */
	वापस 0;
पूर्ण

पूर्णांक saa7134_tvaudio_करो_scan(काष्ठा saa7134_dev *dev)
अणु
	अगर (dev->input->amux != TV) अणु
		audio_dbg(1, "sound IF not in use, skipping scan\n");
		dev->स्वतःmute = 0;
		saa7134_tvaudio_seपंचांगute(dev);
	पूर्ण अन्यथा अगर (dev->thपढ़ो.thपढ़ो) अणु
		dev->thपढ़ो.mode = UNSET;
		dev->thपढ़ो.scan2++;

		अगर (!dev->insuspend && !dev->thपढ़ो.stopped)
			wake_up_process(dev->thपढ़ो.thपढ़ो);
	पूर्ण अन्यथा अणु
		dev->स्वतःmute = 0;
		saa7134_tvaudio_seपंचांगute(dev);
	पूर्ण
	वापस 0;
पूर्ण

EXPORT_SYMBOL(saa_dsp_ग_लिखोl);
EXPORT_SYMBOL(saa7134_tvaudio_seपंचांगute);
