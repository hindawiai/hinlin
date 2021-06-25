<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  Universal पूर्णांकerface क्रम Audio Codec '97
 *
 *  For more details look to AC '97 component specअगरication revision 2.2
 *  by Intel Corporation (http://developer.पूर्णांकel.com).
 */

#समावेश <linux/mutex.h>

#समावेश <sound/core.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/asoundef.h>
#समावेश "ac97_local.h"
#समावेश "ac97_id.h"

/*
 * proc पूर्णांकerface
 */

अटल व्योम snd_ac97_proc_पढ़ो_functions(काष्ठा snd_ac97 *ac97, काष्ठा snd_info_buffer *buffer)
अणु
	पूर्णांक header = 0, function;
	अचिन्हित लघु info, sense_info;
	अटल स्थिर अक्षर *function_names[12] = अणु
		"Master Out", "AUX Out", "Center/LFE Out", "SPDIF Out",
		"Phone In", "Mic 1", "Mic 2", "Line In", "CD In", "Video In",
		"Aux In", "Mono Out"
	पूर्ण;
	अटल स्थिर अक्षर *locations[8] = अणु
		"Rear I/O Panel", "Front Panel", "Motherboard", "Dock/External",
		"reserved", "reserved", "reserved", "NC/unused"
	पूर्ण;

	क्रम (function = 0; function < 12; ++function) अणु
		snd_ac97_ग_लिखो(ac97, AC97_FUNC_SELECT, function << 1);
		info = snd_ac97_पढ़ो(ac97, AC97_FUNC_INFO);
		अगर (!(info & 0x0001))
			जारी;
		अगर (!header) अणु
			snd_iम_लिखो(buffer, "\n                    Gain     Inverted  Buffer delay  Location\n");
			header = 1;
		पूर्ण
		sense_info = snd_ac97_पढ़ो(ac97, AC97_SENSE_INFO);
		snd_iम_लिखो(buffer, "%-17s: %3d.%d dBV    %c      %2d/fs         %s\n",
			    function_names[function],
			    (info & 0x8000 ? -1 : 1) * ((info & 0x7000) >> 12) * 3 / 2,
			    ((info & 0x0800) >> 11) * 5,
			    info & 0x0400 ? 'X' : '-',
			    (info & 0x03e0) >> 5,
			    locations[sense_info >> 13]);
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *snd_ac97_stereo_enhancements[] =
अणु
  /*   0 */ "No 3D Stereo Enhancement",
  /*   1 */ "Analog Devices Phat Stereo",
  /*   2 */ "Creative Stereo Enhancement",
  /*   3 */ "National Semi 3D Stereo Enhancement",
  /*   4 */ "YAMAHA Ymersion",
  /*   5 */ "BBE 3D Stereo Enhancement",
  /*   6 */ "Crystal Semi 3D Stereo Enhancement",
  /*   7 */ "Qsound QXpander",
  /*   8 */ "Spatializer 3D Stereo Enhancement",
  /*   9 */ "SRS 3D Stereo Enhancement",
  /*  10 */ "Platform Tech 3D Stereo Enhancement",
  /*  11 */ "AKM 3D Audio",
  /*  12 */ "Aureal Stereo Enhancement",
  /*  13 */ "Aztech 3D Enhancement",
  /*  14 */ "Binaura 3D Audio Enhancement",
  /*  15 */ "ESS Technology Stereo Enhancement",
  /*  16 */ "Harman International VMAx",
  /*  17 */ "Nvidea/IC Ensemble/KS Waves 3D Stereo Enhancement",
  /*  18 */ "Philips Incredible Sound",
  /*  19 */ "Texas Instruments 3D Stereo Enhancement",
  /*  20 */ "VLSI Technology 3D Stereo Enhancement",
  /*  21 */ "TriTech 3D Stereo Enhancement",
  /*  22 */ "Realtek 3D Stereo Enhancement",
  /*  23 */ "Samsung 3D Stereo Enhancement",
  /*  24 */ "Wolfson Microelectronics 3D Enhancement",
  /*  25 */ "Delta Integration 3D Enhancement",
  /*  26 */ "SigmaTel 3D Enhancement",
  /*  27 */ "IC Ensemble/KS Waves",
  /*  28 */ "Rockwell 3D Stereo Enhancement",
  /*  29 */ "Reserved 29",
  /*  30 */ "Reserved 30",
  /*  31 */ "Reserved 31"
पूर्ण;

अटल व्योम snd_ac97_proc_पढ़ो_मुख्य(काष्ठा snd_ac97 *ac97, काष्ठा snd_info_buffer *buffer, पूर्णांक subidx)
अणु
	अक्षर name[64];
	अचिन्हित लघु val, पंचांगp, ext, mext;
	अटल स्थिर अक्षर *spdअगर_slots[4] = अणु " SPDIF=3/4", " SPDIF=7/8", " SPDIF=6/9", " SPDIF=10/11" पूर्ण;
	अटल स्थिर अक्षर *spdअगर_rates[4] = अणु " Rate=44.1kHz", " Rate=res", " Rate=48kHz", " Rate=32kHz" पूर्ण;
	अटल स्थिर अक्षर *spdअगर_rates_cs4205[4] = अणु " Rate=48kHz", " Rate=44.1kHz", " Rate=res", " Rate=res" पूर्ण;
	अटल स्थिर अक्षर *द्विगुन_rate_slots[4] = अणु "10/11", "7/8", "reserved", "reserved" पूर्ण;

	snd_ac97_get_name(शून्य, ac97->id, name, 0);
	snd_iम_लिखो(buffer, "%d-%d/%d: %s\n\n", ac97->addr, ac97->num, subidx, name);

	अगर ((ac97->scaps & AC97_SCAP_AUDIO) == 0)
		जाओ __modem;

        snd_iम_लिखो(buffer, "PCI Subsys Vendor: 0x%04x\n",
	            ac97->subप्रणाली_venकरोr);
        snd_iम_लिखो(buffer, "PCI Subsys Device: 0x%04x\n\n",
                    ac97->subप्रणाली_device);

	snd_iम_लिखो(buffer, "Flags: %x\n", ac97->flags);

	अगर ((ac97->ext_id & AC97_EI_REV_MASK) >= AC97_EI_REV_23) अणु
		val = snd_ac97_पढ़ो(ac97, AC97_INT_PAGING);
		snd_ac97_update_bits(ac97, AC97_INT_PAGING,
				     AC97_PAGE_MASK, AC97_PAGE_1);
		पंचांगp = snd_ac97_पढ़ो(ac97, AC97_CODEC_CLASS_REV);
		snd_iम_लिखो(buffer, "Revision         : 0x%02x\n", पंचांगp & 0xff);
		snd_iम_लिखो(buffer, "Compat. Class    : 0x%02x\n", (पंचांगp >> 8) & 0x1f);
		snd_iम_लिखो(buffer, "Subsys. Vendor ID: 0x%04x\n",
			    snd_ac97_पढ़ो(ac97, AC97_PCI_SVID));
		snd_iम_लिखो(buffer, "Subsys. ID       : 0x%04x\n\n",
			    snd_ac97_पढ़ो(ac97, AC97_PCI_SID));
		snd_ac97_update_bits(ac97, AC97_INT_PAGING,
				     AC97_PAGE_MASK, val & AC97_PAGE_MASK);
	पूर्ण

	// val = snd_ac97_पढ़ो(ac97, AC97_RESET);
	val = ac97->caps;
	snd_iम_लिखो(buffer, "Capabilities     :%s%s%s%s%s%s\n",
	    	    val & AC97_BC_DEDICATED_MIC ? " -dedicated MIC PCM IN channel-" : "",
		    val & AC97_BC_RESERVED1 ? " -reserved1-" : "",
		    val & AC97_BC_BASS_TREBLE ? " -bass & treble-" : "",
		    val & AC97_BC_SIM_STEREO ? " -simulated stereo-" : "",
		    val & AC97_BC_HEADPHONE ? " -headphone out-" : "",
		    val & AC97_BC_LOUDNESS ? " -loudness-" : "");
	पंचांगp = ac97->caps & AC97_BC_DAC_MASK;
	snd_iम_लिखो(buffer, "DAC resolution   : %s%s%s%s\n",
		    पंचांगp == AC97_BC_16BIT_DAC ? "16-bit" : "",
		    पंचांगp == AC97_BC_18BIT_DAC ? "18-bit" : "",
		    पंचांगp == AC97_BC_20BIT_DAC ? "20-bit" : "",
		    पंचांगp == AC97_BC_DAC_MASK ? "???" : "");
	पंचांगp = ac97->caps & AC97_BC_ADC_MASK;
	snd_iम_लिखो(buffer, "ADC resolution   : %s%s%s%s\n",
		    पंचांगp == AC97_BC_16BIT_ADC ? "16-bit" : "",
		    पंचांगp == AC97_BC_18BIT_ADC ? "18-bit" : "",
		    पंचांगp == AC97_BC_20BIT_ADC ? "20-bit" : "",
		    पंचांगp == AC97_BC_ADC_MASK ? "???" : "");
	snd_iम_लिखो(buffer, "3D enhancement   : %s\n",
		snd_ac97_stereo_enhancements[(val >> 10) & 0x1f]);
	snd_iम_लिखो(buffer, "\nCurrent setup\n");
	val = snd_ac97_पढ़ो(ac97, AC97_MIC);
	snd_iम_लिखो(buffer, "Mic gain         : %s [%s]\n", val & 0x0040 ? "+20dB" : "+0dB", ac97->regs[AC97_MIC] & 0x0040 ? "+20dB" : "+0dB");
	val = snd_ac97_पढ़ो(ac97, AC97_GENERAL_PURPOSE);
	snd_iम_लिखो(buffer, "POP path         : %s 3D\n"
		    "Sim. stereo      : %s\n"
		    "3D enhancement   : %s\n"
		    "Loudness         : %s\n"
		    "Mono output      : %s\n"
		    "Mic select       : %s\n"
		    "ADC/DAC loopback : %s\n",
		    val & 0x8000 ? "post" : "pre",
		    val & 0x4000 ? "on" : "off",
		    val & 0x2000 ? "on" : "off",
		    val & 0x1000 ? "on" : "off",
		    val & 0x0200 ? "Mic" : "MIX",
		    val & 0x0100 ? "Mic2" : "Mic1",
		    val & 0x0080 ? "on" : "off");
	अगर (ac97->ext_id & AC97_EI_DRA)
		snd_iम_लिखो(buffer, "Double rate slots: %s\n",
			    द्विगुन_rate_slots[(val >> 10) & 3]);

	ext = snd_ac97_पढ़ो(ac97, AC97_EXTENDED_ID);
	अगर (ext == 0)
		जाओ __modem;
		
	snd_iम_लिखो(buffer, "Extended ID      : codec=%i rev=%i%s%s%s%s DSA=%i%s%s%s%s\n",
			(ext & AC97_EI_ADDR_MASK) >> AC97_EI_ADDR_SHIFT,
			(ext & AC97_EI_REV_MASK) >> AC97_EI_REV_SHIFT,
			ext & AC97_EI_AMAP ? " AMAP" : "",
			ext & AC97_EI_LDAC ? " LDAC" : "",
			ext & AC97_EI_SDAC ? " SDAC" : "",
			ext & AC97_EI_CDAC ? " CDAC" : "",
			(ext & AC97_EI_DACS_SLOT_MASK) >> AC97_EI_DACS_SLOT_SHIFT,
			ext & AC97_EI_VRM ? " VRM" : "",
			ext & AC97_EI_SPDIF ? " SPDIF" : "",
			ext & AC97_EI_DRA ? " DRA" : "",
			ext & AC97_EI_VRA ? " VRA" : "");
	val = snd_ac97_पढ़ो(ac97, AC97_EXTENDED_STATUS);
	snd_iम_लिखो(buffer, "Extended status  :%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
			val & AC97_EA_PRL ? " PRL" : "",
			val & AC97_EA_PRK ? " PRK" : "",
			val & AC97_EA_PRJ ? " PRJ" : "",
			val & AC97_EA_PRI ? " PRI" : "",
			val & AC97_EA_SPCV ? " SPCV" : "",
			val & AC97_EA_MDAC ? " MADC" : "",
			val & AC97_EA_LDAC ? " LDAC" : "",
			val & AC97_EA_SDAC ? " SDAC" : "",
			val & AC97_EA_CDAC ? " CDAC" : "",
			ext & AC97_EI_SPDIF ? spdअगर_slots[(val & AC97_EA_SPSA_SLOT_MASK) >> AC97_EA_SPSA_SLOT_SHIFT] : "",
			val & AC97_EA_VRM ? " VRM" : "",
			val & AC97_EA_SPDIF ? " SPDIF" : "",
			val & AC97_EA_DRA ? " DRA" : "",
			val & AC97_EA_VRA ? " VRA" : "");
	अगर (ext & AC97_EI_VRA) अणु	/* VRA */
		val = snd_ac97_पढ़ो(ac97, AC97_PCM_FRONT_DAC_RATE);
		snd_iम_लिखो(buffer, "PCM front DAC    : %iHz\n", val);
		अगर (ext & AC97_EI_SDAC) अणु
			val = snd_ac97_पढ़ो(ac97, AC97_PCM_SURR_DAC_RATE);
			snd_iम_लिखो(buffer, "PCM Surr DAC     : %iHz\n", val);
		पूर्ण
		अगर (ext & AC97_EI_LDAC) अणु
			val = snd_ac97_पढ़ो(ac97, AC97_PCM_LFE_DAC_RATE);
			snd_iम_लिखो(buffer, "PCM LFE DAC      : %iHz\n", val);
		पूर्ण
		val = snd_ac97_पढ़ो(ac97, AC97_PCM_LR_ADC_RATE);
		snd_iम_लिखो(buffer, "PCM ADC          : %iHz\n", val);
	पूर्ण
	अगर (ext & AC97_EI_VRM) अणु
		val = snd_ac97_पढ़ो(ac97, AC97_PCM_MIC_ADC_RATE);
		snd_iम_लिखो(buffer, "PCM MIC ADC      : %iHz\n", val);
	पूर्ण
	अगर ((ext & AC97_EI_SPDIF) || (ac97->flags & AC97_CS_SPDIF) ||
	    (ac97->id == AC97_ID_YMF743)) अणु
	        अगर (ac97->flags & AC97_CS_SPDIF)
			val = snd_ac97_पढ़ो(ac97, AC97_CSR_SPDIF);
		अन्यथा अगर (ac97->id == AC97_ID_YMF743) अणु
			val = snd_ac97_पढ़ो(ac97, AC97_YMF7X3_DIT_CTRL);
			val = 0x2000 | (val & 0xff00) >> 4 | (val & 0x38) >> 2;
		पूर्ण अन्यथा
			val = snd_ac97_पढ़ो(ac97, AC97_SPDIF);

		snd_iम_लिखो(buffer, "SPDIF Control    :%s%s%s%s Category=0x%x Generation=%i%s%s%s\n",
			val & AC97_SC_PRO ? " PRO" : " Consumer",
			val & AC97_SC_NAUDIO ? " Non-audio" : " PCM",
			val & AC97_SC_COPY ? "" : " Copyright",
			val & AC97_SC_PRE ? " Preemph50/15" : "",
			(val & AC97_SC_CC_MASK) >> AC97_SC_CC_SHIFT,
			(val & AC97_SC_L) >> 11,
			(ac97->flags & AC97_CS_SPDIF) ?
			    spdअगर_rates_cs4205[(val & AC97_SC_SPSR_MASK) >> AC97_SC_SPSR_SHIFT] :
			    spdअगर_rates[(val & AC97_SC_SPSR_MASK) >> AC97_SC_SPSR_SHIFT],
			(ac97->flags & AC97_CS_SPDIF) ?
			    (val & AC97_SC_DRS ? " Validity" : "") :
			    (val & AC97_SC_DRS ? " DRS" : ""),
			(ac97->flags & AC97_CS_SPDIF) ?
			    (val & AC97_SC_V ? " Enabled" : "") :
			    (val & AC97_SC_V ? " Validity" : ""));
		/* ALC650 specअगरic*/
		अगर ((ac97->id & 0xfffffff0) == 0x414c4720 &&
		    (snd_ac97_पढ़ो(ac97, AC97_ALC650_CLOCK) & 0x01)) अणु
			val = snd_ac97_पढ़ो(ac97, AC97_ALC650_SPDIF_INPUT_STATUS2);
			अगर (val & AC97_ALC650_CLOCK_LOCK) अणु
				val = snd_ac97_पढ़ो(ac97, AC97_ALC650_SPDIF_INPUT_STATUS1);
				snd_iम_लिखो(buffer, "SPDIF In Status  :%s%s%s%s Category=0x%x Generation=%i",
					    val & AC97_ALC650_PRO ? " PRO" : " Consumer",
					    val & AC97_ALC650_NAUDIO ? " Non-audio" : " PCM",
					    val & AC97_ALC650_COPY ? "" : " Copyright",
					    val & AC97_ALC650_PRE ? " Preemph50/15" : "",
					    (val & AC97_ALC650_CC_MASK) >> AC97_ALC650_CC_SHIFT,
					    (val & AC97_ALC650_L) >> 15);
				val = snd_ac97_पढ़ो(ac97, AC97_ALC650_SPDIF_INPUT_STATUS2);
				snd_iम_लिखो(buffer, "%s Accuracy=%i%s%s\n",
					    spdअगर_rates[(val & AC97_ALC650_SPSR_MASK) >> AC97_ALC650_SPSR_SHIFT],
					    (val & AC97_ALC650_CLOCK_ACCURACY) >> AC97_ALC650_CLOCK_SHIFT,
					    (val & AC97_ALC650_CLOCK_LOCK ? " Locked" : " Unlocked"),
					    (val & AC97_ALC650_V ? " Validity?" : ""));
			पूर्ण अन्यथा अणु
				snd_iम_लिखो(buffer, "SPDIF In Status  : Not Locked\n");
			पूर्ण
		पूर्ण
	पूर्ण
	अगर ((ac97->ext_id & AC97_EI_REV_MASK) >= AC97_EI_REV_23) अणु
		val = snd_ac97_पढ़ो(ac97, AC97_INT_PAGING);
		snd_ac97_update_bits(ac97, AC97_INT_PAGING,
				     AC97_PAGE_MASK, AC97_PAGE_1);
		snd_ac97_proc_पढ़ो_functions(ac97, buffer);
		snd_ac97_update_bits(ac97, AC97_INT_PAGING,
				     AC97_PAGE_MASK, val & AC97_PAGE_MASK);
	पूर्ण


      __modem:
	mext = snd_ac97_पढ़ो(ac97, AC97_EXTENDED_MID);
	अगर (mext == 0)
		वापस;
	
	snd_iम_लिखो(buffer, "Extended modem ID: codec=%i%s%s%s%s%s\n",
			(mext & AC97_MEI_ADDR_MASK) >> AC97_MEI_ADDR_SHIFT,
			mext & AC97_MEI_CID2 ? " CID2" : "",
			mext & AC97_MEI_CID1 ? " CID1" : "",
			mext & AC97_MEI_HANDSET ? " HSET" : "",
			mext & AC97_MEI_LINE2 ? " LIN2" : "",
			mext & AC97_MEI_LINE1 ? " LIN1" : "");
	val = snd_ac97_पढ़ो(ac97, AC97_EXTENDED_MSTATUS);
	snd_iम_लिखो(buffer, "Modem status     :%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
			val & AC97_MEA_GPIO ? " GPIO" : "",
			val & AC97_MEA_MREF ? " MREF" : "",
			val & AC97_MEA_ADC1 ? " ADC1" : "",
			val & AC97_MEA_DAC1 ? " DAC1" : "",
			val & AC97_MEA_ADC2 ? " ADC2" : "",
			val & AC97_MEA_DAC2 ? " DAC2" : "",
			val & AC97_MEA_HADC ? " HADC" : "",
			val & AC97_MEA_HDAC ? " HDAC" : "",
			val & AC97_MEA_PRA ? " PRA(GPIO)" : "",
			val & AC97_MEA_PRB ? " PRB(res)" : "",
			val & AC97_MEA_PRC ? " PRC(ADC1)" : "",
			val & AC97_MEA_PRD ? " PRD(DAC1)" : "",
			val & AC97_MEA_PRE ? " PRE(ADC2)" : "",
			val & AC97_MEA_PRF ? " PRF(DAC2)" : "",
			val & AC97_MEA_PRG ? " PRG(HADC)" : "",
			val & AC97_MEA_PRH ? " PRH(HDAC)" : "");
	अगर (mext & AC97_MEI_LINE1) अणु
		val = snd_ac97_पढ़ो(ac97, AC97_LINE1_RATE);
		snd_iम_लिखो(buffer, "Line1 rate       : %iHz\n", val);
	पूर्ण
	अगर (mext & AC97_MEI_LINE2) अणु
		val = snd_ac97_पढ़ो(ac97, AC97_LINE2_RATE);
		snd_iम_लिखो(buffer, "Line2 rate       : %iHz\n", val);
	पूर्ण
	अगर (mext & AC97_MEI_HANDSET) अणु
		val = snd_ac97_पढ़ो(ac97, AC97_HANDSET_RATE);
		snd_iम_लिखो(buffer, "Headset rate     : %iHz\n", val);
	पूर्ण
पूर्ण

अटल व्योम snd_ac97_proc_पढ़ो(काष्ठा snd_info_entry *entry, काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_ac97 *ac97 = entry->निजी_data;
	
	mutex_lock(&ac97->page_mutex);
	अगर ((ac97->id & 0xffffff40) == AC97_ID_AD1881) अणु	// Analog Devices AD1881/85/86
		पूर्णांक idx;
		क्रम (idx = 0; idx < 3; idx++)
			अगर (ac97->spec.ad18xx.id[idx]) अणु
				/* select single codec */
				snd_ac97_update_bits(ac97, AC97_AD_SERIAL_CFG, 0x7000,
						     ac97->spec.ad18xx.unchained[idx] | ac97->spec.ad18xx.chained[idx]);
				snd_ac97_proc_पढ़ो_मुख्य(ac97, buffer, idx);
				snd_iम_लिखो(buffer, "\n\n");
			पूर्ण
		/* select all codecs */
		snd_ac97_update_bits(ac97, AC97_AD_SERIAL_CFG, 0x7000, 0x7000);
		
		snd_iम_लिखो(buffer, "\nAD18XX configuration\n");
		snd_iम_लिखो(buffer, "Unchained        : 0x%04x,0x%04x,0x%04x\n",
			ac97->spec.ad18xx.unchained[0],
			ac97->spec.ad18xx.unchained[1],
			ac97->spec.ad18xx.unchained[2]);
		snd_iम_लिखो(buffer, "Chained          : 0x%04x,0x%04x,0x%04x\n",
			ac97->spec.ad18xx.chained[0],
			ac97->spec.ad18xx.chained[1],
			ac97->spec.ad18xx.chained[2]);
	पूर्ण अन्यथा अणु
		snd_ac97_proc_पढ़ो_मुख्य(ac97, buffer, 0);
	पूर्ण
	mutex_unlock(&ac97->page_mutex);
पूर्ण

#अगर_घोषित CONFIG_SND_DEBUG
/* direct रेजिस्टर ग_लिखो क्रम debugging */
अटल व्योम snd_ac97_proc_regs_ग_लिखो(काष्ठा snd_info_entry *entry, काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_ac97 *ac97 = entry->निजी_data;
	अक्षर line[64];
	अचिन्हित पूर्णांक reg, val;
	mutex_lock(&ac97->page_mutex);
	जबतक (!snd_info_get_line(buffer, line, माप(line))) अणु
		अगर (माला_पूछो(line, "%x %x", &reg, &val) != 2)
			जारी;
		/* रेजिस्टर must be even */
		अगर (reg < 0x80 && (reg & 1) == 0 && val <= 0xffff)
			snd_ac97_ग_लिखो_cache(ac97, reg, val);
	पूर्ण
	mutex_unlock(&ac97->page_mutex);
पूर्ण
#पूर्ण_अगर

अटल व्योम snd_ac97_proc_regs_पढ़ो_मुख्य(काष्ठा snd_ac97 *ac97, काष्ठा snd_info_buffer *buffer, पूर्णांक subidx)
अणु
	पूर्णांक reg, val;

	क्रम (reg = 0; reg < 0x80; reg += 2) अणु
		val = snd_ac97_पढ़ो(ac97, reg);
		snd_iम_लिखो(buffer, "%i:%02x = %04x\n", subidx, reg, val);
	पूर्ण
पूर्ण

अटल व्योम snd_ac97_proc_regs_पढ़ो(काष्ठा snd_info_entry *entry, 
				    काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_ac97 *ac97 = entry->निजी_data;

	mutex_lock(&ac97->page_mutex);
	अगर ((ac97->id & 0xffffff40) == AC97_ID_AD1881) अणु	// Analog Devices AD1881/85/86

		पूर्णांक idx;
		क्रम (idx = 0; idx < 3; idx++)
			अगर (ac97->spec.ad18xx.id[idx]) अणु
				/* select single codec */
				snd_ac97_update_bits(ac97, AC97_AD_SERIAL_CFG, 0x7000,
						     ac97->spec.ad18xx.unchained[idx] | ac97->spec.ad18xx.chained[idx]);
				snd_ac97_proc_regs_पढ़ो_मुख्य(ac97, buffer, idx);
			पूर्ण
		/* select all codecs */
		snd_ac97_update_bits(ac97, AC97_AD_SERIAL_CFG, 0x7000, 0x7000);
	पूर्ण अन्यथा अणु
		snd_ac97_proc_regs_पढ़ो_मुख्य(ac97, buffer, 0);
	पूर्ण	
	mutex_unlock(&ac97->page_mutex);
पूर्ण

व्योम snd_ac97_proc_init(काष्ठा snd_ac97 * ac97)
अणु
	काष्ठा snd_info_entry *entry;
	अक्षर name[32];
	स्थिर अक्षर *prefix;

	अगर (ac97->bus->proc == शून्य)
		वापस;
	prefix = ac97_is_audio(ac97) ? "ac97" : "mc97";
	प्र_लिखो(name, "%s#%d-%d", prefix, ac97->addr, ac97->num);
	entry = snd_info_create_card_entry(ac97->bus->card, name,
					   ac97->bus->proc);
	अगर (entry)
		snd_info_set_text_ops(entry, ac97, snd_ac97_proc_पढ़ो);
	ac97->proc = entry;
	प्र_लिखो(name, "%s#%d-%d+regs", prefix, ac97->addr, ac97->num);
	entry = snd_info_create_card_entry(ac97->bus->card, name,
					   ac97->bus->proc);
	अगर (entry) अणु
		snd_info_set_text_ops(entry, ac97, snd_ac97_proc_regs_पढ़ो);
#अगर_घोषित CONFIG_SND_DEBUG
		entry->mode |= 0200;
		entry->c.text.ग_लिखो = snd_ac97_proc_regs_ग_लिखो;
#पूर्ण_अगर
	पूर्ण
	ac97->proc_regs = entry;
पूर्ण

व्योम snd_ac97_proc_करोne(काष्ठा snd_ac97 * ac97)
अणु
	snd_info_मुक्त_entry(ac97->proc_regs);
	ac97->proc_regs = शून्य;
	snd_info_मुक्त_entry(ac97->proc);
	ac97->proc = शून्य;
पूर्ण

व्योम snd_ac97_bus_proc_init(काष्ठा snd_ac97_bus * bus)
अणु
	काष्ठा snd_info_entry *entry;
	अक्षर name[32];

	प्र_लिखो(name, "codec97#%d", bus->num);
	entry = snd_info_create_card_entry(bus->card, name,
					   bus->card->proc_root);
	अगर (entry)
		entry->mode = S_IFसूची | 0555;
	bus->proc = entry;
पूर्ण

व्योम snd_ac97_bus_proc_करोne(काष्ठा snd_ac97_bus * bus)
अणु
	snd_info_मुक्त_entry(bus->proc);
	bus->proc = शून्य;
पूर्ण
