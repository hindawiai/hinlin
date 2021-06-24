<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  Universal पूर्णांकerface क्रम Audio Codec '97
 *
 *  For more details look to AC '97 component specअगरication revision 2.2
 *  by Intel Corporation (http://developer.पूर्णांकel.com).
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/tlv.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/asoundef.h>
#समावेश <sound/initval.h>
#समावेश "ac97_id.h"

#समावेश "ac97_patch.c"

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("Universal interface for Audio Codec '97");
MODULE_LICENSE("GPL");

अटल bool enable_loopback;

module_param(enable_loopback, bool, 0444);
MODULE_PARM_DESC(enable_loopback, "Enable AC97 ADC/DAC Loopback Control");

#अगर_घोषित CONFIG_SND_AC97_POWER_SAVE
अटल पूर्णांक घातer_save = CONFIG_SND_AC97_POWER_SAVE_DEFAULT;
module_param(घातer_save, पूर्णांक, 0644);
MODULE_PARM_DESC(घातer_save, "Automatic power-saving timeout "
		 "(in second, 0 = disable).");
#पूर्ण_अगर
/*

 */

काष्ठा ac97_codec_id अणु
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक mask;
	स्थिर अक्षर *name;
	पूर्णांक (*patch)(काष्ठा snd_ac97 *ac97);
	पूर्णांक (*mpatch)(काष्ठा snd_ac97 *ac97);
	अचिन्हित पूर्णांक flags;
पूर्ण;

अटल स्थिर काष्ठा ac97_codec_id snd_ac97_codec_id_venकरोrs[] = अणु
अणु 0x41445300, 0xffffff00, "Analog Devices",	शून्य,	शून्य पूर्ण,
अणु 0x414b4d00, 0xffffff00, "Asahi Kasei",	शून्य,	शून्य पूर्ण,
अणु 0x414c4300, 0xffffff00, "Realtek",		शून्य,	शून्य पूर्ण,
अणु 0x414c4700, 0xffffff00, "Realtek",		शून्य,	शून्य पूर्ण,
/*
 * This is an _inofficial_ Aztech Lअसल entry
 * (value might dअगरfer from unknown official Aztech ID),
 * currently used by the AC97 emulation of the almost-AC97 PCI168 card.
 */
अणु 0x415a5400, 0xffffff00, "Aztech Labs (emulated)",	शून्य,	शून्य पूर्ण,
अणु 0x434d4900, 0xffffff00, "C-Media Electronics", शून्य,	शून्य पूर्ण,
अणु 0x43525900, 0xffffff00, "Cirrus Logic",	शून्य,	शून्य पूर्ण,
अणु 0x43585400, 0xffffff00, "Conexant",           शून्य,	शून्य पूर्ण,
अणु 0x44543000, 0xffffff00, "Diamond Technology", शून्य,	शून्य पूर्ण,
अणु 0x454d4300, 0xffffff00, "eMicro",		शून्य,	शून्य पूर्ण,
अणु 0x45838300, 0xffffff00, "ESS Technology",	शून्य,	शून्य पूर्ण,
अणु 0x48525300, 0xffffff00, "Intersil",		शून्य,	शून्य पूर्ण,
अणु 0x49434500, 0xffffff00, "ICEnsemble",		शून्य,	शून्य पूर्ण,
अणु 0x49544500, 0xffffff00, "ITE Tech.Inc",	शून्य,	शून्य पूर्ण,
अणु 0x4e534300, 0xffffff00, "National Semiconductor", शून्य, शून्य पूर्ण,
अणु 0x50534300, 0xffffff00, "Philips",		शून्य,	शून्य पूर्ण,
अणु 0x53494c00, 0xffffff00, "Silicon Laboratory",	शून्य,	शून्य पूर्ण,
अणु 0x53544d00, 0xffffff00, "STMicroelectronics",	शून्य,	शून्य पूर्ण,
अणु 0x54524100, 0xffffff00, "TriTech",		शून्य,	शून्य पूर्ण,
अणु 0x54584e00, 0xffffff00, "Texas Instruments",	शून्य,	शून्य पूर्ण,
अणु 0x56494100, 0xffffff00, "VIA Technologies",   शून्य,	शून्य पूर्ण,
अणु 0x57454300, 0xffffff00, "Winbond",		शून्य,	शून्य पूर्ण,
अणु 0x574d4c00, 0xffffff00, "Wolfson",		शून्य,	शून्य पूर्ण,
अणु 0x594d4800, 0xffffff00, "Yamaha",		शून्य,	शून्य पूर्ण,
अणु 0x83847600, 0xffffff00, "SigmaTel",		शून्य,	शून्य पूर्ण,
अणु 0,	      0, 	  शून्य,			शून्य,	शून्य पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ac97_codec_id snd_ac97_codec_ids[] = अणु
अणु 0x41445303, 0xffffffff, "AD1819",		patch_ad1819,	शून्य पूर्ण,
अणु 0x41445340, 0xffffffff, "AD1881",		patch_ad1881,	शून्य पूर्ण,
अणु 0x41445348, 0xffffffff, "AD1881A",		patch_ad1881,	शून्य पूर्ण,
अणु 0x41445360, 0xffffffff, "AD1885",		patch_ad1885,	शून्य पूर्ण,
अणु 0x41445361, 0xffffffff, "AD1886",		patch_ad1886,	शून्य पूर्ण,
अणु 0x41445362, 0xffffffff, "AD1887",		patch_ad1881,	शून्य पूर्ण,
अणु 0x41445363, 0xffffffff, "AD1886A",		patch_ad1881,	शून्य पूर्ण,
अणु 0x41445368, 0xffffffff, "AD1888",		patch_ad1888,	शून्य पूर्ण,
अणु 0x41445370, 0xffffffff, "AD1980",		patch_ad1980,	शून्य पूर्ण,
अणु 0x41445372, 0xffffffff, "AD1981A",		patch_ad1981a,	शून्य पूर्ण,
अणु 0x41445374, 0xffffffff, "AD1981B",		patch_ad1981b,	शून्य पूर्ण,
अणु 0x41445375, 0xffffffff, "AD1985",		patch_ad1985,	शून्य पूर्ण,
अणु 0x41445378, 0xffffffff, "AD1986",		patch_ad1986,	शून्य पूर्ण,
अणु 0x414b4d00, 0xffffffff, "AK4540",		शून्य,		शून्य पूर्ण,
अणु 0x414b4d01, 0xffffffff, "AK4542",		शून्य,		शून्य पूर्ण,
अणु 0x414b4d02, 0xffffffff, "AK4543",		शून्य,		शून्य पूर्ण,
अणु 0x414b4d06, 0xffffffff, "AK4544A",		शून्य,		शून्य पूर्ण,
अणु 0x414b4d07, 0xffffffff, "AK4545",		शून्य,		शून्य पूर्ण,
अणु 0x414c4300, 0xffffff00, "ALC100,100P", 	शून्य,		शून्य पूर्ण,
अणु 0x414c4710, 0xfffffff0, "ALC200,200P",	शून्य,		शून्य पूर्ण,
अणु 0x414c4721, 0xffffffff, "ALC650D",		शून्य,	शून्य पूर्ण, /* alपढ़ोy patched */
अणु 0x414c4722, 0xffffffff, "ALC650E",		शून्य,	शून्य पूर्ण, /* alपढ़ोy patched */
अणु 0x414c4723, 0xffffffff, "ALC650F",		शून्य,	शून्य पूर्ण, /* alपढ़ोy patched */
अणु 0x414c4720, 0xfffffff0, "ALC650",		patch_alc650,	शून्य पूर्ण,
अणु 0x414c4730, 0xffffffff, "ALC101",		शून्य,		शून्य पूर्ण,
अणु 0x414c4740, 0xfffffff0, "ALC202",		शून्य,		शून्य पूर्ण,
अणु 0x414c4750, 0xfffffff0, "ALC250",		शून्य,		शून्य पूर्ण,
अणु 0x414c4760, 0xfffffff0, "ALC655",		patch_alc655,	शून्य पूर्ण,
अणु 0x414c4770, 0xfffffff0, "ALC203",		patch_alc203,	शून्य पूर्ण,
अणु 0x414c4781, 0xffffffff, "ALC658D",		शून्य,	शून्य पूर्ण, /* alपढ़ोy patched */
अणु 0x414c4780, 0xfffffff0, "ALC658",		patch_alc655,	शून्य पूर्ण,
अणु 0x414c4790, 0xfffffff0, "ALC850",		patch_alc850,	शून्य पूर्ण,
अणु 0x415a5401, 0xffffffff, "AZF3328",		patch_aztech_azf3328,	शून्य पूर्ण,
अणु 0x434d4941, 0xffffffff, "CMI9738",		patch_cm9738,	शून्य पूर्ण,
अणु 0x434d4961, 0xffffffff, "CMI9739",		patch_cm9739,	शून्य पूर्ण,
अणु 0x434d4969, 0xffffffff, "CMI9780",		patch_cm9780,	शून्य पूर्ण,
अणु 0x434d4978, 0xffffffff, "CMI9761A",		patch_cm9761,	शून्य पूर्ण,
अणु 0x434d4982, 0xffffffff, "CMI9761B",		patch_cm9761,	शून्य पूर्ण,
अणु 0x434d4983, 0xffffffff, "CMI9761A+",		patch_cm9761,	शून्य पूर्ण,
अणु 0x43525900, 0xfffffff8, "CS4297",		शून्य,		शून्य पूर्ण,
अणु 0x43525910, 0xfffffff8, "CS4297A",		patch_cirrus_spdअगर,	शून्य पूर्ण,
अणु 0x43525920, 0xfffffff8, "CS4298",		patch_cirrus_spdअगर,		शून्य पूर्ण,
अणु 0x43525928, 0xfffffff8, "CS4294",		शून्य,		शून्य पूर्ण,
अणु 0x43525930, 0xfffffff8, "CS4299",		patch_cirrus_cs4299,	शून्य पूर्ण,
अणु 0x43525948, 0xfffffff8, "CS4201",		शून्य,		शून्य पूर्ण,
अणु 0x43525958, 0xfffffff8, "CS4205",		patch_cirrus_spdअगर,	शून्य पूर्ण,
अणु 0x43525960, 0xfffffff8, "CS4291",		शून्य,		शून्य पूर्ण,
अणु 0x43525970, 0xfffffff8, "CS4202",		शून्य,		शून्य पूर्ण,
अणु 0x43585421, 0xffffffff, "HSD11246",		शून्य,		शून्य पूर्ण,	// SmartMC II
अणु 0x43585428, 0xfffffff8, "Cx20468",		patch_conexant,	शून्य पूर्ण, // SmartAMC fixme: the mask might be dअगरferent
अणु 0x43585430, 0xffffffff, "Cx20468-31",		patch_conexant, शून्य पूर्ण,
अणु 0x43585431, 0xffffffff, "Cx20551",           patch_cx20551,  शून्य पूर्ण,
अणु 0x44543031, 0xfffffff0, "DT0398",		शून्य,		शून्य पूर्ण,
अणु 0x454d4328, 0xffffffff, "EM28028",		शून्य,		शून्य पूर्ण,  // same as TR28028?
अणु 0x45838308, 0xffffffff, "ESS1988",		शून्य,		शून्य पूर्ण,
अणु 0x48525300, 0xffffff00, "HMP9701",		शून्य,		शून्य पूर्ण,
अणु 0x49434501, 0xffffffff, "ICE1230",		शून्य,		शून्य पूर्ण,
अणु 0x49434511, 0xffffffff, "ICE1232",		शून्य,		शून्य पूर्ण, // alias VIA VT1611A?
अणु 0x49434514, 0xffffffff, "ICE1232A",		शून्य,		शून्य पूर्ण,
अणु 0x49434551, 0xffffffff, "VT1616", 		patch_vt1616,	शून्य पूर्ण, 
अणु 0x49434552, 0xffffffff, "VT1616i",		patch_vt1616,	शून्य पूर्ण, // VT1616 compatible (chipset पूर्णांकegrated)
अणु 0x49544520, 0xffffffff, "IT2226E",		शून्य,		शून्य पूर्ण,
अणु 0x49544561, 0xffffffff, "IT2646E",		patch_it2646,	शून्य पूर्ण,
अणु 0x4e534300, 0xffffffff, "LM4540,43,45,46,48",	शून्य,		शून्य पूर्ण, // only guess --jk
अणु 0x4e534331, 0xffffffff, "LM4549",		शून्य,		शून्य पूर्ण,
अणु 0x4e534350, 0xffffffff, "LM4550",		patch_lm4550,  	शून्य पूर्ण, // volume wrap fix 
अणु 0x50534304, 0xffffffff, "UCB1400",		patch_ucb1400,	शून्य पूर्ण,
अणु 0x53494c20, 0xffffffe0, "Si3036,8",		mpatch_si3036,	mpatch_si3036, AC97_MODEM_PATCH पूर्ण,
अणु 0x53544d02, 0xffffffff, "ST7597",		शून्य,		शून्य पूर्ण,
अणु 0x54524102, 0xffffffff, "TR28022",		शून्य,		शून्य पूर्ण,
अणु 0x54524103, 0xffffffff, "TR28023",		शून्य,		शून्य पूर्ण,
अणु 0x54524106, 0xffffffff, "TR28026",		शून्य,		शून्य पूर्ण,
अणु 0x54524108, 0xffffffff, "TR28028",		patch_tritech_tr28028,	शून्य पूर्ण, // added by xin jin [07/09/99]
अणु 0x54524123, 0xffffffff, "TR28602",		शून्य,		शून्य पूर्ण, // only guess --jk [TR28023 = eMicro EM28023 (new CT1297)]
अणु 0x54584e03, 0xffffffff, "TLV320AIC27",	शून्य,		शून्य पूर्ण,
अणु 0x54584e20, 0xffffffff, "TLC320AD9xC",	शून्य,		शून्य पूर्ण,
अणु 0x56494120, 0xfffffff0, "VIA1613",		patch_vt1613,	शून्य पूर्ण,
अणु 0x56494161, 0xffffffff, "VIA1612A",		शून्य,		शून्य पूर्ण, // modअगरied ICE1232 with S/PDIF
अणु 0x56494170, 0xffffffff, "VIA1617A",		patch_vt1617a,	शून्य पूर्ण, // modअगरied VT1616 with S/PDIF
अणु 0x56494182, 0xffffffff, "VIA1618",		patch_vt1618,   शून्य पूर्ण,
अणु 0x57454301, 0xffffffff, "W83971D",		शून्य,		शून्य पूर्ण,
अणु 0x574d4c00, 0xffffffff, "WM9701,WM9701A",	शून्य,		शून्य पूर्ण,
अणु 0x574d4C03, 0xffffffff, "WM9703,WM9707,WM9708,WM9717", patch_wolfson03, शून्यपूर्ण,
अणु 0x574d4C04, 0xffffffff, "WM9704M,WM9704Q",	patch_wolfson04, शून्यपूर्ण,
अणु 0x574d4C05, 0xffffffff, "WM9705,WM9710",	patch_wolfson05, शून्यपूर्ण,
अणु 0x574d4C09, 0xffffffff, "WM9709",		शून्य,		शून्यपूर्ण,
अणु 0x574d4C12, 0xffffffff, "WM9711,WM9712,WM9715",	patch_wolfson11, शून्यपूर्ण,
अणु 0x574d4c13, 0xffffffff, "WM9713,WM9714",	patch_wolfson13, शून्य, AC97_DEFAULT_POWER_OFFपूर्ण,
अणु 0x594d4800, 0xffffffff, "YMF743",		patch_yamaha_ymf743,	शून्य पूर्ण,
अणु 0x594d4802, 0xffffffff, "YMF752",		शून्य,		शून्य पूर्ण,
अणु 0x594d4803, 0xffffffff, "YMF753",		patch_yamaha_ymf753,	शून्य पूर्ण,
अणु 0x83847600, 0xffffffff, "STAC9700,83,84",	patch_sigmatel_stac9700,	शून्य पूर्ण,
अणु 0x83847604, 0xffffffff, "STAC9701,3,4,5",	शून्य,		शून्य पूर्ण,
अणु 0x83847605, 0xffffffff, "STAC9704",		शून्य,		शून्य पूर्ण,
अणु 0x83847608, 0xffffffff, "STAC9708,11",	patch_sigmatel_stac9708,	शून्य पूर्ण,
अणु 0x83847609, 0xffffffff, "STAC9721,23",	patch_sigmatel_stac9721,	शून्य पूर्ण,
अणु 0x83847644, 0xffffffff, "STAC9744",		patch_sigmatel_stac9744,	शून्य पूर्ण,
अणु 0x83847650, 0xffffffff, "STAC9750,51",	शून्य,		शून्य पूर्ण,	// patch?
अणु 0x83847652, 0xffffffff, "STAC9752,53",	शून्य,		शून्य पूर्ण, // patch?
अणु 0x83847656, 0xffffffff, "STAC9756,57",	patch_sigmatel_stac9756,	शून्य पूर्ण,
अणु 0x83847658, 0xffffffff, "STAC9758,59",	patch_sigmatel_stac9758,	शून्य पूर्ण,
अणु 0x83847666, 0xffffffff, "STAC9766,67",	शून्य,		शून्य पूर्ण, // patch?
अणु 0, 	      0,	  शून्य,			शून्य,		शून्य पूर्ण
पूर्ण;


अटल व्योम update_घातer_regs(काष्ठा snd_ac97 *ac97);
#अगर_घोषित CONFIG_SND_AC97_POWER_SAVE
#घोषणा ac97_is_घातer_save_mode(ac97) \
	((ac97->scaps & AC97_SCAP_POWER_SAVE) && घातer_save)
#अन्यथा
#घोषणा ac97_is_घातer_save_mode(ac97) 0
#पूर्ण_अगर

#घोषणा ac97_err(ac97, fmt, args...)	\
	dev_err((ac97)->bus->card->dev, fmt, ##args)
#घोषणा ac97_warn(ac97, fmt, args...)	\
	dev_warn((ac97)->bus->card->dev, fmt, ##args)
#घोषणा ac97_dbg(ac97, fmt, args...)	\
	dev_dbg((ac97)->bus->card->dev, fmt, ##args)

/*
 *  I/O routines
 */

अटल पूर्णांक snd_ac97_valid_reg(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg)
अणु
	/* filter some रेजिस्टरs क्रम buggy codecs */
	चयन (ac97->id) अणु
	हाल AC97_ID_ST_AC97_ID4:
		अगर (reg == 0x08)
			वापस 0;
		fallthrough;
	हाल AC97_ID_ST7597:
		अगर (reg == 0x22 || reg == 0x7a)
			वापस 1;
		fallthrough;
	हाल AC97_ID_AK4540:
	हाल AC97_ID_AK4542:
		अगर (reg <= 0x1c || reg == 0x20 || reg == 0x26 || reg >= 0x7c)
			वापस 1;
		वापस 0;
	हाल AC97_ID_AD1819:	/* AD1819 */
	हाल AC97_ID_AD1881:	/* AD1881 */
	हाल AC97_ID_AD1881A:	/* AD1881A */
		अगर (reg >= 0x3a && reg <= 0x6e)	/* 0x59 */
			वापस 0;
		वापस 1;
	हाल AC97_ID_AD1885:	/* AD1885 */
	हाल AC97_ID_AD1886:	/* AD1886 */
	हाल AC97_ID_AD1886A:	/* AD1886A - !!verअगरy!! --jk */
	हाल AC97_ID_AD1887:	/* AD1887 - !!verअगरy!! --jk */
		अगर (reg == 0x5a)
			वापस 1;
		अगर (reg >= 0x3c && reg <= 0x6e)	/* 0x59 */
			वापस 0;
		वापस 1;
	हाल AC97_ID_STAC9700:
	हाल AC97_ID_STAC9704:
	हाल AC97_ID_STAC9705:
	हाल AC97_ID_STAC9708:
	हाल AC97_ID_STAC9721:
	हाल AC97_ID_STAC9744:
	हाल AC97_ID_STAC9756:
		अगर (reg <= 0x3a || reg >= 0x5a)
			वापस 1;
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/**
 * snd_ac97_ग_लिखो - ग_लिखो a value on the given रेजिस्टर
 * @ac97: the ac97 instance
 * @reg: the रेजिस्टर to change
 * @value: the value to set
 *
 * Writes a value on the given रेजिस्टर.  This will invoke the ग_लिखो
 * callback directly after the रेजिस्टर check.
 * This function करोesn't change the रेजिस्टर cache unlike
 * #snd_ca97_ग_लिखो_cache(), so use this only when you करोn't want to
 * reflect the change to the suspend/resume state.
 */
व्योम snd_ac97_ग_लिखो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg, अचिन्हित लघु value)
अणु
	अगर (!snd_ac97_valid_reg(ac97, reg))
		वापस;
	अगर ((ac97->id & 0xffffff00) == AC97_ID_ALC100) अणु
		/* Fix H/W bug of ALC100/100P */
		अगर (reg == AC97_MASTER || reg == AC97_HEADPHONE)
			ac97->bus->ops->ग_लिखो(ac97, AC97_RESET, 0);	/* reset audio codec */
	पूर्ण
	ac97->bus->ops->ग_लिखो(ac97, reg, value);
पूर्ण

EXPORT_SYMBOL(snd_ac97_ग_लिखो);

/**
 * snd_ac97_पढ़ो - पढ़ो a value from the given रेजिस्टर
 * 
 * @ac97: the ac97 instance
 * @reg: the रेजिस्टर to पढ़ो
 *
 * Reads a value from the given रेजिस्टर.  This will invoke the पढ़ो
 * callback directly after the रेजिस्टर check.
 *
 * Return: The पढ़ो value.
 */
अचिन्हित लघु snd_ac97_पढ़ो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg)
अणु
	अगर (!snd_ac97_valid_reg(ac97, reg))
		वापस 0;
	वापस ac97->bus->ops->पढ़ो(ac97, reg);
पूर्ण

/* पढ़ो a रेजिस्टर - वापस the cached value अगर alपढ़ोy पढ़ो */
अटल अंतरभूत अचिन्हित लघु snd_ac97_पढ़ो_cache(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg)
अणु
	अगर (! test_bit(reg, ac97->reg_accessed)) अणु
		ac97->regs[reg] = ac97->bus->ops->पढ़ो(ac97, reg);
		// set_bit(reg, ac97->reg_accessed);
	पूर्ण
	वापस ac97->regs[reg];
पूर्ण

EXPORT_SYMBOL(snd_ac97_पढ़ो);

/**
 * snd_ac97_ग_लिखो_cache - ग_लिखो a value on the given रेजिस्टर and update the cache
 * @ac97: the ac97 instance
 * @reg: the रेजिस्टर to change
 * @value: the value to set
 *
 * Writes a value on the given रेजिस्टर and updates the रेजिस्टर
 * cache.  The cached values are used क्रम the cached-पढ़ो and the
 * suspend/resume.
 */
व्योम snd_ac97_ग_लिखो_cache(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg, अचिन्हित लघु value)
अणु
	अगर (!snd_ac97_valid_reg(ac97, reg))
		वापस;
	mutex_lock(&ac97->reg_mutex);
	ac97->regs[reg] = value;
	ac97->bus->ops->ग_लिखो(ac97, reg, value);
	set_bit(reg, ac97->reg_accessed);
	mutex_unlock(&ac97->reg_mutex);
पूर्ण

EXPORT_SYMBOL(snd_ac97_ग_लिखो_cache);

/**
 * snd_ac97_update - update the value on the given रेजिस्टर
 * @ac97: the ac97 instance
 * @reg: the रेजिस्टर to change
 * @value: the value to set
 *
 * Compares the value with the रेजिस्टर cache and updates the value
 * only when the value is changed.
 *
 * Return: 1 अगर the value is changed, 0 अगर no change, or a negative
 * code on failure.
 */
पूर्णांक snd_ac97_update(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg, अचिन्हित लघु value)
अणु
	पूर्णांक change;

	अगर (!snd_ac97_valid_reg(ac97, reg))
		वापस -EINVAL;
	mutex_lock(&ac97->reg_mutex);
	change = ac97->regs[reg] != value;
	अगर (change) अणु
		ac97->regs[reg] = value;
		ac97->bus->ops->ग_लिखो(ac97, reg, value);
	पूर्ण
	set_bit(reg, ac97->reg_accessed);
	mutex_unlock(&ac97->reg_mutex);
	वापस change;
पूर्ण

EXPORT_SYMBOL(snd_ac97_update);

/**
 * snd_ac97_update_bits - update the bits on the given रेजिस्टर
 * @ac97: the ac97 instance
 * @reg: the रेजिस्टर to change
 * @mask: the bit-mask to change
 * @value: the value to set
 *
 * Updates the masked-bits on the given रेजिस्टर only when the value
 * is changed.
 *
 * Return: 1 अगर the bits are changed, 0 अगर no change, or a negative
 * code on failure.
 */
पूर्णांक snd_ac97_update_bits(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg, अचिन्हित लघु mask, अचिन्हित लघु value)
अणु
	पूर्णांक change;

	अगर (!snd_ac97_valid_reg(ac97, reg))
		वापस -EINVAL;
	mutex_lock(&ac97->reg_mutex);
	change = snd_ac97_update_bits_nolock(ac97, reg, mask, value);
	mutex_unlock(&ac97->reg_mutex);
	वापस change;
पूर्ण

EXPORT_SYMBOL(snd_ac97_update_bits);

/* no lock version - see snd_ac97_update_bits() */
पूर्णांक snd_ac97_update_bits_nolock(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg,
				अचिन्हित लघु mask, अचिन्हित लघु value)
अणु
	पूर्णांक change;
	अचिन्हित लघु old, new;

	old = snd_ac97_पढ़ो_cache(ac97, reg);
	new = (old & ~mask) | (value & mask);
	change = old != new;
	अगर (change) अणु
		ac97->regs[reg] = new;
		ac97->bus->ops->ग_लिखो(ac97, reg, new);
	पूर्ण
	set_bit(reg, ac97->reg_accessed);
	वापस change;
पूर्ण

अटल पूर्णांक snd_ac97_ad18xx_update_pcm_bits(काष्ठा snd_ac97 *ac97, पूर्णांक codec, अचिन्हित लघु mask, अचिन्हित लघु value)
अणु
	पूर्णांक change;
	अचिन्हित लघु old, new, cfg;

	mutex_lock(&ac97->page_mutex);
	old = ac97->spec.ad18xx.pcmreg[codec];
	new = (old & ~mask) | (value & mask);
	change = old != new;
	अगर (change) अणु
		mutex_lock(&ac97->reg_mutex);
		cfg = snd_ac97_पढ़ो_cache(ac97, AC97_AD_SERIAL_CFG);
		ac97->spec.ad18xx.pcmreg[codec] = new;
		/* select single codec */
		ac97->bus->ops->ग_लिखो(ac97, AC97_AD_SERIAL_CFG,
				 (cfg & ~0x7000) |
				 ac97->spec.ad18xx.unchained[codec] | ac97->spec.ad18xx.chained[codec]);
		/* update PCM bits */
		ac97->bus->ops->ग_लिखो(ac97, AC97_PCM, new);
		/* select all codecs */
		ac97->bus->ops->ग_लिखो(ac97, AC97_AD_SERIAL_CFG,
				 cfg | 0x7000);
		mutex_unlock(&ac97->reg_mutex);
	पूर्ण
	mutex_unlock(&ac97->page_mutex);
	वापस change;
पूर्ण

/*
 * Controls
 */

अटल पूर्णांक snd_ac97_info_क्रमागत_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा ac97_क्रमागत *e = (काष्ठा ac97_क्रमागत *)kcontrol->निजी_value;
	
	वापस snd_ctl_क्रमागत_info(uinfo, e->shअगरt_l == e->shअगरt_r ? 1 : 2,
				 e->mask, e->texts);
पूर्ण

अटल पूर्णांक snd_ac97_get_क्रमागत_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	काष्ठा ac97_क्रमागत *e = (काष्ठा ac97_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित लघु val, biपंचांगask;
	
	क्रम (biपंचांगask = 1; biपंचांगask < e->mask; biपंचांगask <<= 1)
		;
	val = snd_ac97_पढ़ो_cache(ac97, e->reg);
	ucontrol->value.क्रमागतerated.item[0] = (val >> e->shअगरt_l) & (biपंचांगask - 1);
	अगर (e->shअगरt_l != e->shअगरt_r)
		ucontrol->value.क्रमागतerated.item[1] = (val >> e->shअगरt_r) & (biपंचांगask - 1);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_put_क्रमागत_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	काष्ठा ac97_क्रमागत *e = (काष्ठा ac97_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित लघु val;
	अचिन्हित लघु mask, biपंचांगask;
	
	क्रम (biपंचांगask = 1; biपंचांगask < e->mask; biपंचांगask <<= 1)
		;
	अगर (ucontrol->value.क्रमागतerated.item[0] > e->mask - 1)
		वापस -EINVAL;
	val = ucontrol->value.क्रमागतerated.item[0] << e->shअगरt_l;
	mask = (biपंचांगask - 1) << e->shअगरt_l;
	अगर (e->shअगरt_l != e->shअगरt_r) अणु
		अगर (ucontrol->value.क्रमागतerated.item[1] > e->mask - 1)
			वापस -EINVAL;
		val |= ucontrol->value.क्रमागतerated.item[1] << e->shअगरt_r;
		mask |= (biपंचांगask - 1) << e->shअगरt_r;
	पूर्ण
	वापस snd_ac97_update_bits(ac97, e->reg, mask, val);
पूर्ण

/* save/restore ac97 v2.3 paging */
अटल पूर्णांक snd_ac97_page_save(काष्ठा snd_ac97 *ac97, पूर्णांक reg, काष्ठा snd_kcontrol *kcontrol)
अणु
	पूर्णांक page_save = -1;
	अगर ((kcontrol->निजी_value & (1<<25)) &&
	    (ac97->ext_id & AC97_EI_REV_MASK) >= AC97_EI_REV_23 &&
	    (reg >= 0x60 && reg < 0x70)) अणु
		अचिन्हित लघु page = (kcontrol->निजी_value >> 26) & 0x0f;
		mutex_lock(&ac97->page_mutex); /* lock paging */
		page_save = snd_ac97_पढ़ो(ac97, AC97_INT_PAGING) & AC97_PAGE_MASK;
		snd_ac97_update_bits(ac97, AC97_INT_PAGING, AC97_PAGE_MASK, page);
	पूर्ण
	वापस page_save;
पूर्ण

अटल व्योम snd_ac97_page_restore(काष्ठा snd_ac97 *ac97, पूर्णांक page_save)
अणु
	अगर (page_save >= 0) अणु
		snd_ac97_update_bits(ac97, AC97_INT_PAGING, AC97_PAGE_MASK, page_save);
		mutex_unlock(&ac97->page_mutex); /* unlock paging */
	पूर्ण
पूर्ण

/* volume and चयन controls */
अटल पूर्णांक snd_ac97_info_volsw(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0x0f;
	पूर्णांक rshअगरt = (kcontrol->निजी_value >> 12) & 0x0f;

	uinfo->type = mask == 1 ? SNDRV_CTL_ELEM_TYPE_BOOLEAN : SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = shअगरt == rshअगरt ? 1 : 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = mask;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_get_volsw(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0x0f;
	पूर्णांक rshअगरt = (kcontrol->निजी_value >> 12) & 0x0f;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & 0x01;
	पूर्णांक page_save;

	page_save = snd_ac97_page_save(ac97, reg, kcontrol);
	ucontrol->value.पूर्णांकeger.value[0] = (snd_ac97_पढ़ो_cache(ac97, reg) >> shअगरt) & mask;
	अगर (shअगरt != rshअगरt)
		ucontrol->value.पूर्णांकeger.value[1] = (snd_ac97_पढ़ो_cache(ac97, reg) >> rshअगरt) & mask;
	अगर (invert) अणु
		ucontrol->value.पूर्णांकeger.value[0] = mask - ucontrol->value.पूर्णांकeger.value[0];
		अगर (shअगरt != rshअगरt)
			ucontrol->value.पूर्णांकeger.value[1] = mask - ucontrol->value.पूर्णांकeger.value[1];
	पूर्ण
	snd_ac97_page_restore(ac97, page_save);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_put_volsw(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0x0f;
	पूर्णांक rshअगरt = (kcontrol->निजी_value >> 12) & 0x0f;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & 0x01;
	पूर्णांक err, page_save;
	अचिन्हित लघु val, val2, val_mask;
	
	page_save = snd_ac97_page_save(ac97, reg, kcontrol);
	val = (ucontrol->value.पूर्णांकeger.value[0] & mask);
	अगर (invert)
		val = mask - val;
	val_mask = mask << shअगरt;
	val = val << shअगरt;
	अगर (shअगरt != rshअगरt) अणु
		val2 = (ucontrol->value.पूर्णांकeger.value[1] & mask);
		अगर (invert)
			val2 = mask - val2;
		val_mask |= mask << rshअगरt;
		val |= val2 << rshअगरt;
	पूर्ण
	err = snd_ac97_update_bits(ac97, reg, val_mask, val);
	snd_ac97_page_restore(ac97, page_save);
#अगर_घोषित CONFIG_SND_AC97_POWER_SAVE
	/* check analog mixer घातer-करोwn */
	अगर ((val_mask & AC97_PD_EAPD) &&
	    (kcontrol->निजी_value & (1<<30))) अणु
		अगर (val & AC97_PD_EAPD)
			ac97->घातer_up &= ~(1 << (reg>>1));
		अन्यथा
			ac97->घातer_up |= 1 << (reg>>1);
		update_घातer_regs(ac97);
	पूर्ण
#पूर्ण_अगर
	वापस err;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_controls_tone[2] = अणु
AC97_SINGLE("Tone Control - Bass", AC97_MASTER_TONE, 8, 15, 1),
AC97_SINGLE("Tone Control - Treble", AC97_MASTER_TONE, 0, 15, 1)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_controls_pc_beep[2] = अणु
AC97_SINGLE("Beep Playback Switch", AC97_PC_BEEP, 15, 1, 1),
AC97_SINGLE("Beep Playback Volume", AC97_PC_BEEP, 1, 15, 1)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_controls_mic_boost =
	AC97_SINGLE("Mic Boost (+20dB)", AC97_MIC, 6, 1, 0);


अटल स्थिर अक्षर* std_rec_sel[] = अणु"Mic", "CD", "Video", "Aux", "Line", "Mix", "Mix Mono", "Phone"पूर्ण;
अटल स्थिर अक्षर* std_3d_path[] = अणु"pre 3D", "post 3D"पूर्ण;
अटल स्थिर अक्षर* std_mix[] = अणु"Mix", "Mic"पूर्ण;
अटल स्थिर अक्षर* std_mic[] = अणु"Mic1", "Mic2"पूर्ण;

अटल स्थिर काष्ठा ac97_क्रमागत std_क्रमागत[] = अणु
AC97_ENUM_DOUBLE(AC97_REC_SEL, 8, 0, 8, std_rec_sel),
AC97_ENUM_SINGLE(AC97_GENERAL_PURPOSE, 15, 2, std_3d_path),
AC97_ENUM_SINGLE(AC97_GENERAL_PURPOSE, 9, 2, std_mix),
AC97_ENUM_SINGLE(AC97_GENERAL_PURPOSE, 8, 2, std_mic),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_control_capture_src = 
AC97_ENUM("Capture Source", std_क्रमागत[0]); 

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_control_capture_vol =
AC97_DOUBLE("Capture Volume", AC97_REC_GAIN, 8, 0, 15, 0);

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_controls_mic_capture[2] = अणु
AC97_SINGLE("Mic Capture Switch", AC97_REC_GAIN_MIC, 15, 1, 1),
AC97_SINGLE("Mic Capture Volume", AC97_REC_GAIN_MIC, 0, 15, 0)
पूर्ण;

क्रमागत अणु
	AC97_GENERAL_PCM_OUT = 0,
	AC97_GENERAL_STEREO_ENHANCEMENT,
	AC97_GENERAL_3D,
	AC97_GENERAL_LOUDNESS,
	AC97_GENERAL_MONO,
	AC97_GENERAL_MIC,
	AC97_GENERAL_LOOPBACK
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_controls_general[7] = अणु
AC97_ENUM("PCM Out Path & Mute", std_क्रमागत[1]),
AC97_SINGLE("Simulated Stereo Enhancement", AC97_GENERAL_PURPOSE, 14, 1, 0),
AC97_SINGLE("3D Control - Switch", AC97_GENERAL_PURPOSE, 13, 1, 0),
AC97_SINGLE("Loudness (bass boost)", AC97_GENERAL_PURPOSE, 12, 1, 0),
AC97_ENUM("Mono Output Select", std_क्रमागत[2]),
AC97_ENUM("Mic Select", std_क्रमागत[3]),
AC97_SINGLE("ADC/DAC Loopback", AC97_GENERAL_PURPOSE, 7, 1, 0)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_controls_3d[2] = अणु
AC97_SINGLE("3D Control - Center", AC97_3D_CONTROL, 8, 15, 0),
AC97_SINGLE("3D Control - Depth", AC97_3D_CONTROL, 0, 15, 0)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_controls_center[2] = अणु
AC97_SINGLE("Center Playback Switch", AC97_CENTER_LFE_MASTER, 7, 1, 1),
AC97_SINGLE("Center Playback Volume", AC97_CENTER_LFE_MASTER, 0, 31, 1)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_controls_lfe[2] = अणु
AC97_SINGLE("LFE Playback Switch", AC97_CENTER_LFE_MASTER, 15, 1, 1),
AC97_SINGLE("LFE Playback Volume", AC97_CENTER_LFE_MASTER, 8, 31, 1)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_control_eapd =
AC97_SINGLE("External Amplifier", AC97_POWERDOWN, 15, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_controls_modem_चयनes[2] = अणु
AC97_SINGLE("Off-hook Switch", AC97_GPIO_STATUS, 0, 1, 0),
AC97_SINGLE("Caller ID Switch", AC97_GPIO_STATUS, 2, 1, 0)
पूर्ण;

/* change the existing EAPD control as inverted */
अटल व्योम set_inv_eapd(काष्ठा snd_ac97 *ac97, काष्ठा snd_kcontrol *kctl)
अणु
	kctl->निजी_value = AC97_SINGLE_VALUE(AC97_POWERDOWN, 15, 1, 0);
	snd_ac97_update_bits(ac97, AC97_POWERDOWN, (1<<15), (1<<15)); /* EAPD up */
	ac97->scaps |= AC97_SCAP_INV_EAPD;
पूर्ण

अटल पूर्णांक snd_ac97_spdअगर_mask_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण
                        
अटल पूर्णांक snd_ac97_spdअगर_cmask_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.iec958.status[0] = IEC958_AES0_PROFESSIONAL |
					   IEC958_AES0_NONAUDIO |
					   IEC958_AES0_CON_EMPHASIS_5015 |
					   IEC958_AES0_CON_NOT_COPYRIGHT;
	ucontrol->value.iec958.status[1] = IEC958_AES1_CON_CATEGORY |
					   IEC958_AES1_CON_ORIGINAL;
	ucontrol->value.iec958.status[3] = IEC958_AES3_CON_FS;
	वापस 0;
पूर्ण
                        
अटल पूर्णांक snd_ac97_spdअगर_pmask_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	/* FIXME: AC'97 spec doesn't say which bits are used क्रम what */
	ucontrol->value.iec958.status[0] = IEC958_AES0_PROFESSIONAL |
					   IEC958_AES0_NONAUDIO |
					   IEC958_AES0_PRO_FS |
					   IEC958_AES0_PRO_EMPHASIS_5015;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_spdअगर_शेष_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);

	mutex_lock(&ac97->reg_mutex);
	ucontrol->value.iec958.status[0] = ac97->spdअगर_status & 0xff;
	ucontrol->value.iec958.status[1] = (ac97->spdअगर_status >> 8) & 0xff;
	ucontrol->value.iec958.status[2] = (ac97->spdअगर_status >> 16) & 0xff;
	ucontrol->value.iec958.status[3] = (ac97->spdअगर_status >> 24) & 0xff;
	mutex_unlock(&ac97->reg_mutex);
	वापस 0;
पूर्ण
                        
अटल पूर्णांक snd_ac97_spdअगर_शेष_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक new = 0;
	अचिन्हित लघु val = 0;
	पूर्णांक change;

	new = val = ucontrol->value.iec958.status[0] & (IEC958_AES0_PROFESSIONAL|IEC958_AES0_NONAUDIO);
	अगर (ucontrol->value.iec958.status[0] & IEC958_AES0_PROFESSIONAL) अणु
		new |= ucontrol->value.iec958.status[0] & (IEC958_AES0_PRO_FS|IEC958_AES0_PRO_EMPHASIS_5015);
		चयन (new & IEC958_AES0_PRO_FS) अणु
		हाल IEC958_AES0_PRO_FS_44100: val |= 0<<12; अवरोध;
		हाल IEC958_AES0_PRO_FS_48000: val |= 2<<12; अवरोध;
		हाल IEC958_AES0_PRO_FS_32000: val |= 3<<12; अवरोध;
		शेष:		       val |= 1<<12; अवरोध;
		पूर्ण
		अगर ((new & IEC958_AES0_PRO_EMPHASIS) == IEC958_AES0_PRO_EMPHASIS_5015)
			val |= 1<<3;
	पूर्ण अन्यथा अणु
		new |= ucontrol->value.iec958.status[0] & (IEC958_AES0_CON_EMPHASIS_5015|IEC958_AES0_CON_NOT_COPYRIGHT);
		new |= ((ucontrol->value.iec958.status[1] & (IEC958_AES1_CON_CATEGORY|IEC958_AES1_CON_ORIGINAL)) << 8);
		new |= ((ucontrol->value.iec958.status[3] & IEC958_AES3_CON_FS) << 24);
		अगर ((new & IEC958_AES0_CON_EMPHASIS) == IEC958_AES0_CON_EMPHASIS_5015)
			val |= 1<<3;
		अगर (!(new & IEC958_AES0_CON_NOT_COPYRIGHT))
			val |= 1<<2;
		val |= ((new >> 8) & 0xff) << 4;	// category + original
		चयन ((new >> 24) & 0xff) अणु
		हाल IEC958_AES3_CON_FS_44100: val |= 0<<12; अवरोध;
		हाल IEC958_AES3_CON_FS_48000: val |= 2<<12; अवरोध;
		हाल IEC958_AES3_CON_FS_32000: val |= 3<<12; अवरोध;
		शेष:		       val |= 1<<12; अवरोध;
		पूर्ण
	पूर्ण

	mutex_lock(&ac97->reg_mutex);
	change = ac97->spdअगर_status != new;
	ac97->spdअगर_status = new;

	अगर (ac97->flags & AC97_CS_SPDIF) अणु
		पूर्णांक x = (val >> 12) & 0x03;
		चयन (x) अणु
		हाल 0: x = 1; अवरोध;  // 44.1
		हाल 2: x = 0; अवरोध;  // 48.0
		शेष: x = 0; अवरोध; // illegal.
		पूर्ण
		change |= snd_ac97_update_bits_nolock(ac97, AC97_CSR_SPDIF, 0x3fff, ((val & 0xcfff) | (x << 12)));
	पूर्ण अन्यथा अगर (ac97->flags & AC97_CX_SPDIF) अणु
		पूर्णांक v;
		v = new & (IEC958_AES0_CON_EMPHASIS_5015|IEC958_AES0_CON_NOT_COPYRIGHT) ? 0 : AC97_CXR_COPYRGT;
		v |= new & IEC958_AES0_NONAUDIO ? AC97_CXR_SPDIF_AC3 : AC97_CXR_SPDIF_PCM;
		change |= snd_ac97_update_bits_nolock(ac97, AC97_CXR_AUDIO_MISC, 
						      AC97_CXR_SPDIF_MASK | AC97_CXR_COPYRGT,
						      v);
	पूर्ण अन्यथा अगर (ac97->id == AC97_ID_YMF743) अणु
		change |= snd_ac97_update_bits_nolock(ac97,
						      AC97_YMF7X3_DIT_CTRL,
						      0xff38,
						      ((val << 4) & 0xff00) |
						      ((val << 2) & 0x0038));
	पूर्ण अन्यथा अणु
		अचिन्हित लघु extst = snd_ac97_पढ़ो_cache(ac97, AC97_EXTENDED_STATUS);
		snd_ac97_update_bits_nolock(ac97, AC97_EXTENDED_STATUS, AC97_EA_SPDIF, 0); /* turn off */

		change |= snd_ac97_update_bits_nolock(ac97, AC97_SPDIF, 0x3fff, val);
		अगर (extst & AC97_EA_SPDIF) अणु
			snd_ac97_update_bits_nolock(ac97, AC97_EXTENDED_STATUS, AC97_EA_SPDIF, AC97_EA_SPDIF); /* turn on again */
                पूर्ण
	पूर्ण
	mutex_unlock(&ac97->reg_mutex);

	वापस change;
पूर्ण

अटल पूर्णांक snd_ac97_put_spsa(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0x0f;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	// पूर्णांक invert = (kcontrol->निजी_value >> 24) & 0xff;
	अचिन्हित लघु value, old, new;
	पूर्णांक change;

	value = (ucontrol->value.पूर्णांकeger.value[0] & mask);

	mutex_lock(&ac97->reg_mutex);
	mask <<= shअगरt;
	value <<= shअगरt;
	old = snd_ac97_पढ़ो_cache(ac97, reg);
	new = (old & ~mask) | value;
	change = old != new;

	अगर (change) अणु
		अचिन्हित लघु extst = snd_ac97_पढ़ो_cache(ac97, AC97_EXTENDED_STATUS);
		snd_ac97_update_bits_nolock(ac97, AC97_EXTENDED_STATUS, AC97_EA_SPDIF, 0); /* turn off */
		change = snd_ac97_update_bits_nolock(ac97, reg, mask, value);
		अगर (extst & AC97_EA_SPDIF)
			snd_ac97_update_bits_nolock(ac97, AC97_EXTENDED_STATUS, AC97_EA_SPDIF, AC97_EA_SPDIF); /* turn on again */
	पूर्ण
	mutex_unlock(&ac97->reg_mutex);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_controls_spdअगर[5] = अणु
	अणु
		.access = SNDRV_CTL_ELEM_ACCESS_READ,
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = SNDRV_CTL_NAME_IEC958("",PLAYBACK,CON_MASK),
		.info = snd_ac97_spdअगर_mask_info,
		.get = snd_ac97_spdअगर_cmask_get,
	पूर्ण,
	अणु
		.access = SNDRV_CTL_ELEM_ACCESS_READ,
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = SNDRV_CTL_NAME_IEC958("",PLAYBACK,PRO_MASK),
		.info = snd_ac97_spdअगर_mask_info,
		.get = snd_ac97_spdअगर_pmask_get,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = SNDRV_CTL_NAME_IEC958("",PLAYBACK,DEFAULT),
		.info = snd_ac97_spdअगर_mask_info,
		.get = snd_ac97_spdअगर_शेष_get,
		.put = snd_ac97_spdअगर_शेष_put,
	पूर्ण,

	AC97_SINGLE(SNDRV_CTL_NAME_IEC958("",PLAYBACK,SWITCH),AC97_EXTENDED_STATUS, 2, 1, 0),
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = SNDRV_CTL_NAME_IEC958("",PLAYBACK,NONE) "AC97-SPSA",
		.info = snd_ac97_info_volsw,
		.get = snd_ac97_get_volsw,
		.put = snd_ac97_put_spsa,
		.निजी_value = AC97_SINGLE_VALUE(AC97_EXTENDED_STATUS, 4, 3, 0)
	पूर्ण,
पूर्ण;

#घोषणा AD18XX_PCM_BITS(xname, codec, lshअगरt, rshअगरt, mask) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .info = snd_ac97_ad18xx_pcm_info_bits, \
  .get = snd_ac97_ad18xx_pcm_get_bits, .put = snd_ac97_ad18xx_pcm_put_bits, \
  .निजी_value = (codec) | ((lshअगरt) << 8) | ((rshअगरt) << 12) | ((mask) << 16) पूर्ण

अटल पूर्णांक snd_ac97_ad18xx_pcm_info_bits(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0x0f;
	पूर्णांक lshअगरt = (kcontrol->निजी_value >> 8) & 0x0f;
	पूर्णांक rshअगरt = (kcontrol->निजी_value >> 12) & 0x0f;

	uinfo->type = mask == 1 ? SNDRV_CTL_ELEM_TYPE_BOOLEAN : SNDRV_CTL_ELEM_TYPE_INTEGER;
	अगर (lshअगरt != rshअगरt && (ac97->flags & AC97_STEREO_MUTES))
		uinfo->count = 2;
	अन्यथा
		uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = mask;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_ad18xx_pcm_get_bits(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	पूर्णांक codec = kcontrol->निजी_value & 3;
	पूर्णांक lshअगरt = (kcontrol->निजी_value >> 8) & 0x0f;
	पूर्णांक rshअगरt = (kcontrol->निजी_value >> 12) & 0x0f;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	
	ucontrol->value.पूर्णांकeger.value[0] = mask - ((ac97->spec.ad18xx.pcmreg[codec] >> lshअगरt) & mask);
	अगर (lshअगरt != rshअगरt && (ac97->flags & AC97_STEREO_MUTES))
		ucontrol->value.पूर्णांकeger.value[1] = mask - ((ac97->spec.ad18xx.pcmreg[codec] >> rshअगरt) & mask);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_ad18xx_pcm_put_bits(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	पूर्णांक codec = kcontrol->निजी_value & 3;
	पूर्णांक lshअगरt = (kcontrol->निजी_value >> 8) & 0x0f;
	पूर्णांक rshअगरt = (kcontrol->निजी_value >> 12) & 0x0f;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	अचिन्हित लघु val, valmask;
	
	val = (mask - (ucontrol->value.पूर्णांकeger.value[0] & mask)) << lshअगरt;
	valmask = mask << lshअगरt;
	अगर (lshअगरt != rshअगरt && (ac97->flags & AC97_STEREO_MUTES)) अणु
		val |= (mask - (ucontrol->value.पूर्णांकeger.value[1] & mask)) << rshअगरt;
		valmask |= mask << rshअगरt;
	पूर्ण
	वापस snd_ac97_ad18xx_update_pcm_bits(ac97, codec, valmask, val);
पूर्ण

#घोषणा AD18XX_PCM_VOLUME(xname, codec) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .info = snd_ac97_ad18xx_pcm_info_volume, \
  .get = snd_ac97_ad18xx_pcm_get_volume, .put = snd_ac97_ad18xx_pcm_put_volume, \
  .निजी_value = codec पूर्ण

अटल पूर्णांक snd_ac97_ad18xx_pcm_info_volume(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 31;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_ad18xx_pcm_get_volume(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	पूर्णांक codec = kcontrol->निजी_value & 3;
	
	mutex_lock(&ac97->page_mutex);
	ucontrol->value.पूर्णांकeger.value[0] = 31 - ((ac97->spec.ad18xx.pcmreg[codec] >> 0) & 31);
	ucontrol->value.पूर्णांकeger.value[1] = 31 - ((ac97->spec.ad18xx.pcmreg[codec] >> 8) & 31);
	mutex_unlock(&ac97->page_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_ad18xx_pcm_put_volume(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	पूर्णांक codec = kcontrol->निजी_value & 3;
	अचिन्हित लघु val1, val2;
	
	val1 = 31 - (ucontrol->value.पूर्णांकeger.value[0] & 31);
	val2 = 31 - (ucontrol->value.पूर्णांकeger.value[1] & 31);
	वापस snd_ac97_ad18xx_update_pcm_bits(ac97, codec, 0x1f1f, (val1 << 8) | val2);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_controls_ad18xx_pcm[2] = अणु
AD18XX_PCM_BITS("PCM Playback Switch", 0, 15, 7, 1),
AD18XX_PCM_VOLUME("PCM Playback Volume", 0)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_controls_ad18xx_surround[2] = अणु
AD18XX_PCM_BITS("Surround Playback Switch", 1, 15, 7, 1),
AD18XX_PCM_VOLUME("Surround Playback Volume", 1)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_controls_ad18xx_center[2] = अणु
AD18XX_PCM_BITS("Center Playback Switch", 2, 15, 15, 1),
AD18XX_PCM_BITS("Center Playback Volume", 2, 8, 8, 31)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_controls_ad18xx_lfe[2] = अणु
AD18XX_PCM_BITS("LFE Playback Switch", 2, 7, 7, 1),
AD18XX_PCM_BITS("LFE Playback Volume", 2, 0, 0, 31)
पूर्ण;

/*
 *
 */

अटल व्योम snd_ac97_घातerकरोwn(काष्ठा snd_ac97 *ac97);

अटल पूर्णांक snd_ac97_bus_मुक्त(काष्ठा snd_ac97_bus *bus)
अणु
	अगर (bus) अणु
		snd_ac97_bus_proc_करोne(bus);
		kमुक्त(bus->pcms);
		अगर (bus->निजी_मुक्त)
			bus->निजी_मुक्त(bus);
		kमुक्त(bus);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_bus_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_ac97_bus *bus = device->device_data;
	वापस snd_ac97_bus_मुक्त(bus);
पूर्ण

अटल पूर्णांक snd_ac97_मुक्त(काष्ठा snd_ac97 *ac97)
अणु
	अगर (ac97) अणु
#अगर_घोषित CONFIG_SND_AC97_POWER_SAVE
		cancel_delayed_work_sync(&ac97->घातer_work);
#पूर्ण_अगर
		snd_ac97_proc_करोne(ac97);
		अगर (ac97->bus)
			ac97->bus->codec[ac97->num] = शून्य;
		अगर (ac97->निजी_मुक्त)
			ac97->निजी_मुक्त(ac97);
		kमुक्त(ac97);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_ac97 *ac97 = device->device_data;
	snd_ac97_घातerकरोwn(ac97); /* क्रम aव्योमing click noises during shut करोwn */
	वापस snd_ac97_मुक्त(ac97);
पूर्ण

अटल पूर्णांक snd_ac97_try_volume_mix(काष्ठा snd_ac97 * ac97, पूर्णांक reg)
अणु
	अचिन्हित लघु val, mask = AC97_MUTE_MASK_MONO;

	अगर (! snd_ac97_valid_reg(ac97, reg))
		वापस 0;

	चयन (reg) अणु
	हाल AC97_MASTER_TONE:
		वापस ac97->caps & AC97_BC_BASS_TREBLE ? 1 : 0;
	हाल AC97_HEADPHONE:
		वापस ac97->caps & AC97_BC_HEADPHONE ? 1 : 0;
	हाल AC97_REC_GAIN_MIC:
		वापस ac97->caps & AC97_BC_DEDICATED_MIC ? 1 : 0;
	हाल AC97_3D_CONTROL:
		अगर (ac97->caps & AC97_BC_3D_TECH_ID_MASK) अणु
			val = snd_ac97_पढ़ो(ac97, reg);
			/* अगर nonzero - fixed and we can't set it */
			वापस val == 0;
		पूर्ण
		वापस 0;
	हाल AC97_CENTER_LFE_MASTER:	/* center */
		अगर ((ac97->ext_id & AC97_EI_CDAC) == 0)
			वापस 0;
		अवरोध;
	हाल AC97_CENTER_LFE_MASTER+1:	/* lfe */
		अगर ((ac97->ext_id & AC97_EI_LDAC) == 0)
			वापस 0;
		reg = AC97_CENTER_LFE_MASTER;
		mask = 0x0080;
		अवरोध;
	हाल AC97_SURROUND_MASTER:
		अगर ((ac97->ext_id & AC97_EI_SDAC) == 0)
			वापस 0;
		अवरोध;
	पूर्ण

	val = snd_ac97_पढ़ो(ac97, reg);
	अगर (!(val & mask)) अणु
		/* nothing seems to be here - mute flag is not set */
		/* try another test */
		snd_ac97_ग_लिखो_cache(ac97, reg, val | mask);
		val = snd_ac97_पढ़ो(ac97, reg);
		val = snd_ac97_पढ़ो(ac97, reg);
		अगर (!(val & mask))
			वापस 0;	/* nothing here */
	पूर्ण
	वापस 1;		/* success, useable */
पूर्ण

अटल व्योम check_volume_resolution(काष्ठा snd_ac97 *ac97, पूर्णांक reg, अचिन्हित अक्षर *lo_max, अचिन्हित अक्षर *hi_max)
अणु
	अचिन्हित लघु cbit[3] = अणु 0x20, 0x10, 0x01 पूर्ण;
	अचिन्हित अक्षर max[3] = अणु 63, 31, 15 पूर्ण;
	पूर्णांक i;

	/* first look up the अटल resolution table */
	अगर (ac97->res_table) अणु
		स्थिर काष्ठा snd_ac97_res_table *tbl;
		क्रम (tbl = ac97->res_table; tbl->reg; tbl++) अणु
			अगर (tbl->reg == reg) अणु
				*lo_max = tbl->bits & 0xff;
				*hi_max = (tbl->bits >> 8) & 0xff;
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	*lo_max = *hi_max = 0;
	क्रम (i = 0 ; i < ARRAY_SIZE(cbit); i++) अणु
		अचिन्हित लघु val;
		snd_ac97_ग_लिखो(
			ac97, reg,
			AC97_MUTE_MASK_STEREO | cbit[i] | (cbit[i] << 8)
		);
		/* Do the पढ़ो twice due to buffers on some ac97 codecs.
		 * e.g. The STAC9704 वापसs exactly what you wrote to the रेजिस्टर
		 * अगर you पढ़ो it immediately. This causes the detect routine to fail.
		 */
		val = snd_ac97_पढ़ो(ac97, reg);
		val = snd_ac97_पढ़ो(ac97, reg);
		अगर (! *lo_max && (val & 0x7f) == cbit[i])
			*lo_max = max[i];
		अगर (! *hi_max && ((val >> 8) & 0x7f) == cbit[i])
			*hi_max = max[i];
		अगर (*lo_max && *hi_max)
			अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक snd_ac97_try_bit(काष्ठा snd_ac97 * ac97, पूर्णांक reg, पूर्णांक bit)
अणु
	अचिन्हित लघु mask, val, orig, res;

	mask = 1 << bit;
	orig = snd_ac97_पढ़ो(ac97, reg);
	val = orig ^ mask;
	snd_ac97_ग_लिखो(ac97, reg, val);
	res = snd_ac97_पढ़ो(ac97, reg);
	snd_ac97_ग_लिखो_cache(ac97, reg, orig);
	वापस res == val;
पूर्ण

/* check the volume resolution of center/lfe */
अटल व्योम snd_ac97_change_volume_params2(काष्ठा snd_ac97 * ac97, पूर्णांक reg, पूर्णांक shअगरt, अचिन्हित अक्षर *max)
अणु
	अचिन्हित लघु val, val1;

	*max = 63;
	val = AC97_MUTE_MASK_STEREO | (0x20 << shअगरt);
	snd_ac97_ग_लिखो(ac97, reg, val);
	val1 = snd_ac97_पढ़ो(ac97, reg);
	अगर (val != val1) अणु
		*max = 31;
	पूर्ण
	/* reset volume to zero */
	snd_ac97_ग_लिखो_cache(ac97, reg, AC97_MUTE_MASK_STEREO);
पूर्ण

अटल अंतरभूत पूर्णांक prपूर्णांकable(अचिन्हित पूर्णांक x)
अणु
	x &= 0xff;
	अगर (x < ' ' || x >= 0x71) अणु
		अगर (x <= 0x89)
			वापस x - 0x71 + 'A';
		वापस '?';
	पूर्ण
	वापस x;
पूर्ण

अटल काष्ठा snd_kcontrol *snd_ac97_cnew(स्थिर काष्ठा snd_kcontrol_new *_ढाँचा,
					  काष्ठा snd_ac97 * ac97)
अणु
	काष्ठा snd_kcontrol_new ढाँचा;
	स_नकल(&ढाँचा, _ढाँचा, माप(ढाँचा));
	ढाँचा.index = ac97->num;
	वापस snd_ctl_new1(&ढाँचा, ac97);
पूर्ण

/*
 * create mute चयन(es) क्रम normal stereo controls
 */
अटल पूर्णांक snd_ac97_cmute_new_stereo(काष्ठा snd_card *card, अक्षर *name, पूर्णांक reg,
				     पूर्णांक check_stereo, पूर्णांक check_amix,
				     काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा snd_kcontrol *kctl;
	पूर्णांक err;
	अचिन्हित लघु val, val1, mute_mask;

	अगर (! snd_ac97_valid_reg(ac97, reg))
		वापस 0;

	mute_mask = AC97_MUTE_MASK_MONO;
	val = snd_ac97_पढ़ो(ac97, reg);
	अगर (check_stereo || (ac97->flags & AC97_STEREO_MUTES)) अणु
		/* check whether both mute bits work */
		val1 = val | AC97_MUTE_MASK_STEREO;
		snd_ac97_ग_लिखो(ac97, reg, val1);
		अगर (val1 == snd_ac97_पढ़ो(ac97, reg))
			mute_mask = AC97_MUTE_MASK_STEREO;
	पूर्ण
	अगर (mute_mask == AC97_MUTE_MASK_STEREO) अणु
		काष्ठा snd_kcontrol_new पंचांगp = AC97_DOUBLE(name, reg, 15, 7, 1, 1);
		अगर (check_amix)
			पंचांगp.निजी_value |= (1 << 30);
		पंचांगp.index = ac97->num;
		kctl = snd_ctl_new1(&पंचांगp, ac97);
	पूर्ण अन्यथा अणु
		काष्ठा snd_kcontrol_new पंचांगp = AC97_SINGLE(name, reg, 15, 1, 1);
		अगर (check_amix)
			पंचांगp.निजी_value |= (1 << 30);
		पंचांगp.index = ac97->num;
		kctl = snd_ctl_new1(&पंचांगp, ac97);
	पूर्ण
	err = snd_ctl_add(card, kctl);
	अगर (err < 0)
		वापस err;
	/* mute as शेष */
	snd_ac97_ग_लिखो_cache(ac97, reg, val | mute_mask);
	वापस 0;
पूर्ण

/*
 * set dB inक्रमmation
 */
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_4bit, -4500, 300, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_5bit, -4650, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_6bit, -9450, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_5bit_12db_max, -3450, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_rec_gain, 0, 150, 0);

अटल स्थिर अचिन्हित पूर्णांक *find_db_scale(अचिन्हित पूर्णांक maxval)
अणु
	चयन (maxval) अणु
	हाल 0x0f: वापस db_scale_4bit;
	हाल 0x1f: वापस db_scale_5bit;
	हाल 0x3f: वापस db_scale_6bit;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम set_tlv_db_scale(काष्ठा snd_kcontrol *kctl, स्थिर अचिन्हित पूर्णांक *tlv)
अणु
	kctl->tlv.p = tlv;
	अगर (tlv)
		kctl->vd[0].access |= SNDRV_CTL_ELEM_ACCESS_TLV_READ;
पूर्ण

/*
 * create a volume क्रम normal stereo/mono controls
 */
अटल पूर्णांक snd_ac97_cvol_new(काष्ठा snd_card *card, अक्षर *name, पूर्णांक reg, अचिन्हित पूर्णांक lo_max,
			     अचिन्हित पूर्णांक hi_max, काष्ठा snd_ac97 *ac97)
अणु
	पूर्णांक err;
	काष्ठा snd_kcontrol *kctl;

	अगर (! snd_ac97_valid_reg(ac97, reg))
		वापस 0;
	अगर (hi_max) अणु
		/* invert */
		काष्ठा snd_kcontrol_new पंचांगp = AC97_DOUBLE(name, reg, 8, 0, lo_max, 1);
		पंचांगp.index = ac97->num;
		kctl = snd_ctl_new1(&पंचांगp, ac97);
	पूर्ण अन्यथा अणु
		/* invert */
		काष्ठा snd_kcontrol_new पंचांगp = AC97_SINGLE(name, reg, 0, lo_max, 1);
		पंचांगp.index = ac97->num;
		kctl = snd_ctl_new1(&पंचांगp, ac97);
	पूर्ण
	अगर (!kctl)
		वापस -ENOMEM;
	अगर (reg >= AC97_PHONE && reg <= AC97_PCM)
		set_tlv_db_scale(kctl, db_scale_5bit_12db_max);
	अन्यथा
		set_tlv_db_scale(kctl, find_db_scale(lo_max));
	err = snd_ctl_add(card, kctl);
	अगर (err < 0)
		वापस err;
	snd_ac97_ग_लिखो_cache(
		ac97, reg,
		(snd_ac97_पढ़ो(ac97, reg) & AC97_MUTE_MASK_STEREO)
		| lo_max | (hi_max << 8)
	);
	वापस 0;
पूर्ण

/*
 * create a mute-चयन and a volume क्रम normal stereo/mono controls
 */
अटल पूर्णांक snd_ac97_cmix_new_stereo(काष्ठा snd_card *card, स्थिर अक्षर *pfx,
				    पूर्णांक reg, पूर्णांक check_stereo, पूर्णांक check_amix,
				    काष्ठा snd_ac97 *ac97)
अणु
	पूर्णांक err;
	अक्षर name[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
	अचिन्हित अक्षर lo_max, hi_max;

	अगर (! snd_ac97_valid_reg(ac97, reg))
		वापस 0;

	अगर (snd_ac97_try_bit(ac97, reg, 15)) अणु
		प्र_लिखो(name, "%s Switch", pfx);
		अगर ((err = snd_ac97_cmute_new_stereo(card, name, reg,
						     check_stereo, check_amix,
						     ac97)) < 0)
			वापस err;
	पूर्ण
	check_volume_resolution(ac97, reg, &lo_max, &hi_max);
	अगर (lo_max) अणु
		प्र_लिखो(name, "%s Volume", pfx);
		अगर ((err = snd_ac97_cvol_new(card, name, reg, lo_max, hi_max, ac97)) < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा snd_ac97_cmix_new(card, pfx, reg, acheck, ac97) \
	snd_ac97_cmix_new_stereo(card, pfx, reg, 0, acheck, ac97)
#घोषणा snd_ac97_cmute_new(card, name, reg, acheck, ac97) \
	snd_ac97_cmute_new_stereo(card, name, reg, 0, acheck, ac97)

अटल अचिन्हित पूर्णांक snd_ac97_determine_spdअगर_rates(काष्ठा snd_ac97 *ac97);

अटल पूर्णांक snd_ac97_mixer_build(काष्ठा snd_ac97 * ac97)
अणु
	काष्ठा snd_card *card = ac97->bus->card;
	काष्ठा snd_kcontrol *kctl;
	पूर्णांक err;
	अचिन्हित पूर्णांक idx;
	अचिन्हित अक्षर max;

	/* build master controls */
	/* AD claims to हटाओ this control from AD1887, although spec v2.2 करोes not allow this */
	अगर (snd_ac97_try_volume_mix(ac97, AC97_MASTER)) अणु
		अगर (ac97->flags & AC97_HAS_NO_MASTER_VOL)
			err = snd_ac97_cmute_new(card, "Master Playback Switch",
						 AC97_MASTER, 0, ac97);
		अन्यथा
			err = snd_ac97_cmix_new(card, "Master Playback",
						AC97_MASTER, 0, ac97);
		अगर (err < 0)
			वापस err;
	पूर्ण

	ac97->regs[AC97_CENTER_LFE_MASTER] = AC97_MUTE_MASK_STEREO;

	/* build center controls */
	अगर ((snd_ac97_try_volume_mix(ac97, AC97_CENTER_LFE_MASTER)) 
		&& !(ac97->flags & AC97_AD_MULTI)) अणु
		अगर ((err = snd_ctl_add(card, snd_ac97_cnew(&snd_ac97_controls_center[0], ac97))) < 0)
			वापस err;
		अगर ((err = snd_ctl_add(card, kctl = snd_ac97_cnew(&snd_ac97_controls_center[1], ac97))) < 0)
			वापस err;
		snd_ac97_change_volume_params2(ac97, AC97_CENTER_LFE_MASTER, 0, &max);
		kctl->निजी_value &= ~(0xff << 16);
		kctl->निजी_value |= (पूर्णांक)max << 16;
		set_tlv_db_scale(kctl, find_db_scale(max));
		snd_ac97_ग_लिखो_cache(ac97, AC97_CENTER_LFE_MASTER, ac97->regs[AC97_CENTER_LFE_MASTER] | max);
	पूर्ण

	/* build LFE controls */
	अगर ((snd_ac97_try_volume_mix(ac97, AC97_CENTER_LFE_MASTER+1))
		&& !(ac97->flags & AC97_AD_MULTI)) अणु
		अगर ((err = snd_ctl_add(card, snd_ac97_cnew(&snd_ac97_controls_lfe[0], ac97))) < 0)
			वापस err;
		अगर ((err = snd_ctl_add(card, kctl = snd_ac97_cnew(&snd_ac97_controls_lfe[1], ac97))) < 0)
			वापस err;
		snd_ac97_change_volume_params2(ac97, AC97_CENTER_LFE_MASTER, 8, &max);
		kctl->निजी_value &= ~(0xff << 16);
		kctl->निजी_value |= (पूर्णांक)max << 16;
		set_tlv_db_scale(kctl, find_db_scale(max));
		snd_ac97_ग_लिखो_cache(ac97, AC97_CENTER_LFE_MASTER, ac97->regs[AC97_CENTER_LFE_MASTER] | max << 8);
	पूर्ण

	/* build surround controls */
	अगर ((snd_ac97_try_volume_mix(ac97, AC97_SURROUND_MASTER)) 
		&& !(ac97->flags & AC97_AD_MULTI)) अणु
		/* Surround Master (0x38) is with stereo mutes */
		अगर ((err = snd_ac97_cmix_new_stereo(card, "Surround Playback",
						    AC97_SURROUND_MASTER, 1, 0,
						    ac97)) < 0)
			वापस err;
	पूर्ण

	/* build headphone controls */
	अगर (snd_ac97_try_volume_mix(ac97, AC97_HEADPHONE)) अणु
		अगर ((err = snd_ac97_cmix_new(card, "Headphone Playback",
					     AC97_HEADPHONE, 0, ac97)) < 0)
			वापस err;
	पूर्ण
	
	/* build master mono controls */
	अगर (snd_ac97_try_volume_mix(ac97, AC97_MASTER_MONO)) अणु
		अगर ((err = snd_ac97_cmix_new(card, "Master Mono Playback",
					     AC97_MASTER_MONO, 0, ac97)) < 0)
			वापस err;
	पूर्ण
	
	/* build master tone controls */
	अगर (!(ac97->flags & AC97_HAS_NO_TONE)) अणु
		अगर (snd_ac97_try_volume_mix(ac97, AC97_MASTER_TONE)) अणु
			क्रम (idx = 0; idx < 2; idx++) अणु
				अगर ((err = snd_ctl_add(card, kctl = snd_ac97_cnew(&snd_ac97_controls_tone[idx], ac97))) < 0)
					वापस err;
				अगर (ac97->id == AC97_ID_YMF743 ||
				    ac97->id == AC97_ID_YMF753) अणु
					kctl->निजी_value &= ~(0xff << 16);
					kctl->निजी_value |= 7 << 16;
				पूर्ण
			पूर्ण
			snd_ac97_ग_लिखो_cache(ac97, AC97_MASTER_TONE, 0x0f0f);
		पूर्ण
	पूर्ण
	
	/* build Beep controls */
	अगर (!(ac97->flags & AC97_HAS_NO_PC_BEEP) && 
		((ac97->flags & AC97_HAS_PC_BEEP) ||
	    snd_ac97_try_volume_mix(ac97, AC97_PC_BEEP))) अणु
		क्रम (idx = 0; idx < 2; idx++)
			अगर ((err = snd_ctl_add(card, kctl = snd_ac97_cnew(&snd_ac97_controls_pc_beep[idx], ac97))) < 0)
				वापस err;
		set_tlv_db_scale(kctl, db_scale_4bit);
		snd_ac97_ग_लिखो_cache(
			ac97,
			AC97_PC_BEEP,
			(snd_ac97_पढ़ो(ac97, AC97_PC_BEEP)
				| AC97_MUTE_MASK_MONO | 0x001e)
		);
	पूर्ण
	
	/* build Phone controls */
	अगर (!(ac97->flags & AC97_HAS_NO_PHONE)) अणु
		अगर (snd_ac97_try_volume_mix(ac97, AC97_PHONE)) अणु
			अगर ((err = snd_ac97_cmix_new(card, "Phone Playback",
						     AC97_PHONE, 1, ac97)) < 0)
				वापस err;
		पूर्ण
	पूर्ण
	
	/* build MIC controls */
	अगर (!(ac97->flags & AC97_HAS_NO_MIC)) अणु
		अगर (snd_ac97_try_volume_mix(ac97, AC97_MIC)) अणु
			अगर ((err = snd_ac97_cmix_new(card, "Mic Playback",
						     AC97_MIC, 1, ac97)) < 0)
				वापस err;
			अगर ((err = snd_ctl_add(card, snd_ac97_cnew(&snd_ac97_controls_mic_boost, ac97))) < 0)
				वापस err;
		पूर्ण
	पूर्ण

	/* build Line controls */
	अगर (snd_ac97_try_volume_mix(ac97, AC97_LINE)) अणु
		अगर ((err = snd_ac97_cmix_new(card, "Line Playback",
					     AC97_LINE, 1, ac97)) < 0)
			वापस err;
	पूर्ण
	
	/* build CD controls */
	अगर (!(ac97->flags & AC97_HAS_NO_CD)) अणु
		अगर (snd_ac97_try_volume_mix(ac97, AC97_CD)) अणु
			अगर ((err = snd_ac97_cmix_new(card, "CD Playback",
						     AC97_CD, 1, ac97)) < 0)
				वापस err;
		पूर्ण
	पूर्ण
	
	/* build Video controls */
	अगर (!(ac97->flags & AC97_HAS_NO_VIDEO)) अणु
		अगर (snd_ac97_try_volume_mix(ac97, AC97_VIDEO)) अणु
			अगर ((err = snd_ac97_cmix_new(card, "Video Playback",
						     AC97_VIDEO, 1, ac97)) < 0)
				वापस err;
		पूर्ण
	पूर्ण

	/* build Aux controls */
	अगर (!(ac97->flags & AC97_HAS_NO_AUX)) अणु
		अगर (snd_ac97_try_volume_mix(ac97, AC97_AUX)) अणु
			अगर ((err = snd_ac97_cmix_new(card, "Aux Playback",
						     AC97_AUX, 1, ac97)) < 0)
				वापस err;
		पूर्ण
	पूर्ण

	/* build PCM controls */
	अगर (ac97->flags & AC97_AD_MULTI) अणु
		अचिन्हित लघु init_val;
		अगर (ac97->flags & AC97_STEREO_MUTES)
			init_val = 0x9f9f;
		अन्यथा
			init_val = 0x9f1f;
		क्रम (idx = 0; idx < 2; idx++)
			अगर ((err = snd_ctl_add(card, kctl = snd_ac97_cnew(&snd_ac97_controls_ad18xx_pcm[idx], ac97))) < 0)
				वापस err;
		set_tlv_db_scale(kctl, db_scale_5bit);
		ac97->spec.ad18xx.pcmreg[0] = init_val;
		अगर (ac97->scaps & AC97_SCAP_SURROUND_DAC) अणु
			क्रम (idx = 0; idx < 2; idx++)
				अगर ((err = snd_ctl_add(card, kctl = snd_ac97_cnew(&snd_ac97_controls_ad18xx_surround[idx], ac97))) < 0)
					वापस err;
			set_tlv_db_scale(kctl, db_scale_5bit);
			ac97->spec.ad18xx.pcmreg[1] = init_val;
		पूर्ण
		अगर (ac97->scaps & AC97_SCAP_CENTER_LFE_DAC) अणु
			क्रम (idx = 0; idx < 2; idx++)
				अगर ((err = snd_ctl_add(card, kctl = snd_ac97_cnew(&snd_ac97_controls_ad18xx_center[idx], ac97))) < 0)
					वापस err;
			set_tlv_db_scale(kctl, db_scale_5bit);
			क्रम (idx = 0; idx < 2; idx++)
				अगर ((err = snd_ctl_add(card, kctl = snd_ac97_cnew(&snd_ac97_controls_ad18xx_lfe[idx], ac97))) < 0)
					वापस err;
			set_tlv_db_scale(kctl, db_scale_5bit);
			ac97->spec.ad18xx.pcmreg[2] = init_val;
		पूर्ण
		snd_ac97_ग_लिखो_cache(ac97, AC97_PCM, init_val);
	पूर्ण अन्यथा अणु
		अगर (!(ac97->flags & AC97_HAS_NO_STD_PCM)) अणु
			अगर (ac97->flags & AC97_HAS_NO_PCM_VOL)
				err = snd_ac97_cmute_new(card,
							 "PCM Playback Switch",
							 AC97_PCM, 0, ac97);
			अन्यथा
				err = snd_ac97_cmix_new(card, "PCM Playback",
							AC97_PCM, 0, ac97);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण

	/* build Capture controls */
	अगर (!(ac97->flags & AC97_HAS_NO_REC_GAIN)) अणु
		अगर ((err = snd_ctl_add(card, snd_ac97_cnew(&snd_ac97_control_capture_src, ac97))) < 0)
			वापस err;
		अगर (snd_ac97_try_bit(ac97, AC97_REC_GAIN, 15)) अणु
			err = snd_ac97_cmute_new(card, "Capture Switch",
						 AC97_REC_GAIN, 0, ac97);
			अगर (err < 0)
				वापस err;
		पूर्ण
		अगर ((err = snd_ctl_add(card, kctl = snd_ac97_cnew(&snd_ac97_control_capture_vol, ac97))) < 0)
			वापस err;
		set_tlv_db_scale(kctl, db_scale_rec_gain);
		snd_ac97_ग_लिखो_cache(ac97, AC97_REC_SEL, 0x0000);
		snd_ac97_ग_लिखो_cache(ac97, AC97_REC_GAIN, 0x0000);
	पूर्ण
	/* build MIC Capture controls */
	अगर (snd_ac97_try_volume_mix(ac97, AC97_REC_GAIN_MIC)) अणु
		क्रम (idx = 0; idx < 2; idx++)
			अगर ((err = snd_ctl_add(card, kctl = snd_ac97_cnew(&snd_ac97_controls_mic_capture[idx], ac97))) < 0)
				वापस err;
		set_tlv_db_scale(kctl, db_scale_rec_gain);
		snd_ac97_ग_लिखो_cache(ac97, AC97_REC_GAIN_MIC, 0x0000);
	पूर्ण

	/* build PCM out path & mute control */
	अगर (snd_ac97_try_bit(ac97, AC97_GENERAL_PURPOSE, 15)) अणु
		अगर ((err = snd_ctl_add(card, snd_ac97_cnew(&snd_ac97_controls_general[AC97_GENERAL_PCM_OUT], ac97))) < 0)
			वापस err;
	पूर्ण

	/* build Simulated Stereo Enhancement control */
	अगर (ac97->caps & AC97_BC_SIM_STEREO) अणु
		अगर ((err = snd_ctl_add(card, snd_ac97_cnew(&snd_ac97_controls_general[AC97_GENERAL_STEREO_ENHANCEMENT], ac97))) < 0)
			वापस err;
	पूर्ण

	/* build 3D Stereo Enhancement control */
	अगर (snd_ac97_try_bit(ac97, AC97_GENERAL_PURPOSE, 13)) अणु
		अगर ((err = snd_ctl_add(card, snd_ac97_cnew(&snd_ac97_controls_general[AC97_GENERAL_3D], ac97))) < 0)
			वापस err;
	पूर्ण

	/* build Loudness control */
	अगर (ac97->caps & AC97_BC_LOUDNESS) अणु
		अगर ((err = snd_ctl_add(card, snd_ac97_cnew(&snd_ac97_controls_general[AC97_GENERAL_LOUDNESS], ac97))) < 0)
			वापस err;
	पूर्ण

	/* build Mono output select control */
	अगर (snd_ac97_try_bit(ac97, AC97_GENERAL_PURPOSE, 9)) अणु
		अगर ((err = snd_ctl_add(card, snd_ac97_cnew(&snd_ac97_controls_general[AC97_GENERAL_MONO], ac97))) < 0)
			वापस err;
	पूर्ण

	/* build Mic select control */
	अगर (snd_ac97_try_bit(ac97, AC97_GENERAL_PURPOSE, 8)) अणु
		अगर ((err = snd_ctl_add(card, snd_ac97_cnew(&snd_ac97_controls_general[AC97_GENERAL_MIC], ac97))) < 0)
			वापस err;
	पूर्ण

	/* build ADC/DAC loopback control */
	अगर (enable_loopback && snd_ac97_try_bit(ac97, AC97_GENERAL_PURPOSE, 7)) अणु
		अगर ((err = snd_ctl_add(card, snd_ac97_cnew(&snd_ac97_controls_general[AC97_GENERAL_LOOPBACK], ac97))) < 0)
			वापस err;
	पूर्ण

	snd_ac97_update_bits(ac97, AC97_GENERAL_PURPOSE, ~AC97_GP_DRSS_MASK, 0x0000);

	/* build 3D controls */
	अगर (ac97->build_ops->build_3d) अणु
		ac97->build_ops->build_3d(ac97);
	पूर्ण अन्यथा अणु
		अगर (snd_ac97_try_volume_mix(ac97, AC97_3D_CONTROL)) अणु
			अचिन्हित लघु val;
			val = 0x0707;
			snd_ac97_ग_लिखो(ac97, AC97_3D_CONTROL, val);
			val = snd_ac97_पढ़ो(ac97, AC97_3D_CONTROL);
			val = val == 0x0606;
			अगर ((err = snd_ctl_add(card, kctl = snd_ac97_cnew(&snd_ac97_controls_3d[0], ac97))) < 0)
				वापस err;
			अगर (val)
				kctl->निजी_value = AC97_3D_CONTROL | (9 << 8) | (7 << 16);
			अगर ((err = snd_ctl_add(card, kctl = snd_ac97_cnew(&snd_ac97_controls_3d[1], ac97))) < 0)
				वापस err;
			अगर (val)
				kctl->निजी_value = AC97_3D_CONTROL | (1 << 8) | (7 << 16);
			snd_ac97_ग_लिखो_cache(ac97, AC97_3D_CONTROL, 0x0000);
		पूर्ण
	पूर्ण

	/* build S/PDIF controls */

	/* Hack क्रम ASUS P5P800-VM, which करोes not indicate S/PDIF capability */
	अगर (ac97->subप्रणाली_venकरोr == 0x1043 &&
	    ac97->subप्रणाली_device == 0x810f)
		ac97->ext_id |= AC97_EI_SPDIF;

	अगर ((ac97->ext_id & AC97_EI_SPDIF) && !(ac97->scaps & AC97_SCAP_NO_SPDIF)) अणु
		अगर (ac97->build_ops->build_spdअगर) अणु
			अगर ((err = ac97->build_ops->build_spdअगर(ac97)) < 0)
				वापस err;
		पूर्ण अन्यथा अणु
			क्रम (idx = 0; idx < 5; idx++)
				अगर ((err = snd_ctl_add(card, snd_ac97_cnew(&snd_ac97_controls_spdअगर[idx], ac97))) < 0)
					वापस err;
			अगर (ac97->build_ops->build_post_spdअगर) अणु
				अगर ((err = ac97->build_ops->build_post_spdअगर(ac97)) < 0)
					वापस err;
			पूर्ण
			/* set शेष PCM S/PDIF params */
			/* consumer,PCM audio,no copyright,no preemphasis,PCM coder,original,48000Hz */
			snd_ac97_ग_लिखो_cache(ac97, AC97_SPDIF, 0x2a20);
			ac97->rates[AC97_RATES_SPDIF] = snd_ac97_determine_spdअगर_rates(ac97);
		पूर्ण
		ac97->spdअगर_status = SNDRV_PCM_DEFAULT_CON_SPDIF;
	पूर्ण
	
	/* build chip specअगरic controls */
	अगर (ac97->build_ops->build_specअगरic)
		अगर ((err = ac97->build_ops->build_specअगरic(ac97)) < 0)
			वापस err;

	अगर (snd_ac97_try_bit(ac97, AC97_POWERDOWN, 15)) अणु
		kctl = snd_ac97_cnew(&snd_ac97_control_eapd, ac97);
		अगर (! kctl)
			वापस -ENOMEM;
		अगर (ac97->scaps & AC97_SCAP_INV_EAPD)
			set_inv_eapd(ac97, kctl);
		अगर ((err = snd_ctl_add(card, kctl)) < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_modem_build(काष्ठा snd_card *card, काष्ठा snd_ac97 * ac97)
अणु
	पूर्णांक err, idx;

	/*
	ac97_dbg(ac97, "AC97_GPIO_CFG = %x\n",
	       snd_ac97_पढ़ो(ac97,AC97_GPIO_CFG));
	*/
	snd_ac97_ग_लिखो(ac97, AC97_GPIO_CFG, 0xffff & ~(AC97_GPIO_LINE1_OH));
	snd_ac97_ग_लिखो(ac97, AC97_GPIO_POLARITY, 0xffff & ~(AC97_GPIO_LINE1_OH));
	snd_ac97_ग_लिखो(ac97, AC97_GPIO_STICKY, 0xffff);
	snd_ac97_ग_लिखो(ac97, AC97_GPIO_WAKEUP, 0x0);
	snd_ac97_ग_लिखो(ac97, AC97_MISC_AFE, 0x0);

	/* build modem चयनes */
	क्रम (idx = 0; idx < ARRAY_SIZE(snd_ac97_controls_modem_चयनes); idx++)
		अगर ((err = snd_ctl_add(card, snd_ctl_new1(&snd_ac97_controls_modem_चयनes[idx], ac97))) < 0)
			वापस err;

	/* build chip specअगरic controls */
	अगर (ac97->build_ops->build_specअगरic)
		अगर ((err = ac97->build_ops->build_specअगरic(ac97)) < 0)
			वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_ac97_test_rate(काष्ठा snd_ac97 *ac97, पूर्णांक reg, पूर्णांक shaकरोw_reg, पूर्णांक rate)
अणु
	अचिन्हित लघु val;
	अचिन्हित पूर्णांक पंचांगp;

	पंचांगp = ((अचिन्हित पूर्णांक)rate * ac97->bus->घड़ी) / 48000;
	snd_ac97_ग_लिखो_cache(ac97, reg, पंचांगp & 0xffff);
	अगर (shaकरोw_reg)
		snd_ac97_ग_लिखो_cache(ac97, shaकरोw_reg, पंचांगp & 0xffff);
	val = snd_ac97_पढ़ो(ac97, reg);
	वापस val == (पंचांगp & 0xffff);
पूर्ण

अटल व्योम snd_ac97_determine_rates(काष्ठा snd_ac97 *ac97, पूर्णांक reg, पूर्णांक shaकरोw_reg, अचिन्हित पूर्णांक *r_result)
अणु
	अचिन्हित पूर्णांक result = 0;
	अचिन्हित लघु saved;

	अगर (ac97->bus->no_vra) अणु
		*r_result = SNDRV_PCM_RATE_48000;
		अगर ((ac97->flags & AC97_DOUBLE_RATE) &&
		    reg == AC97_PCM_FRONT_DAC_RATE)
			*r_result |= SNDRV_PCM_RATE_96000;
		वापस;
	पूर्ण

	saved = snd_ac97_पढ़ो(ac97, reg);
	अगर ((ac97->ext_id & AC97_EI_DRA) && reg == AC97_PCM_FRONT_DAC_RATE)
		snd_ac97_update_bits(ac97, AC97_EXTENDED_STATUS,
				     AC97_EA_DRA, 0);
	/* test a non-standard rate */
	अगर (snd_ac97_test_rate(ac97, reg, shaकरोw_reg, 11000))
		result |= SNDRV_PCM_RATE_CONTINUOUS;
	/* let's try to obtain standard rates */
	अगर (snd_ac97_test_rate(ac97, reg, shaकरोw_reg, 8000))
		result |= SNDRV_PCM_RATE_8000;
	अगर (snd_ac97_test_rate(ac97, reg, shaकरोw_reg, 11025))
		result |= SNDRV_PCM_RATE_11025;
	अगर (snd_ac97_test_rate(ac97, reg, shaकरोw_reg, 16000))
		result |= SNDRV_PCM_RATE_16000;
	अगर (snd_ac97_test_rate(ac97, reg, shaकरोw_reg, 22050))
		result |= SNDRV_PCM_RATE_22050;
	अगर (snd_ac97_test_rate(ac97, reg, shaकरोw_reg, 32000))
		result |= SNDRV_PCM_RATE_32000;
	अगर (snd_ac97_test_rate(ac97, reg, shaकरोw_reg, 44100))
		result |= SNDRV_PCM_RATE_44100;
	अगर (snd_ac97_test_rate(ac97, reg, shaकरोw_reg, 48000))
		result |= SNDRV_PCM_RATE_48000;
	अगर ((ac97->flags & AC97_DOUBLE_RATE) &&
	    reg == AC97_PCM_FRONT_DAC_RATE) अणु
		/* test standard द्विगुन rates */
		snd_ac97_update_bits(ac97, AC97_EXTENDED_STATUS,
				     AC97_EA_DRA, AC97_EA_DRA);
		अगर (snd_ac97_test_rate(ac97, reg, shaकरोw_reg, 64000 / 2))
			result |= SNDRV_PCM_RATE_64000;
		अगर (snd_ac97_test_rate(ac97, reg, shaकरोw_reg, 88200 / 2))
			result |= SNDRV_PCM_RATE_88200;
		अगर (snd_ac97_test_rate(ac97, reg, shaकरोw_reg, 96000 / 2))
			result |= SNDRV_PCM_RATE_96000;
		/* some codecs करोn't support variable द्विगुन rates */
		अगर (!snd_ac97_test_rate(ac97, reg, shaकरोw_reg, 76100 / 2))
			result &= ~SNDRV_PCM_RATE_CONTINUOUS;
		snd_ac97_update_bits(ac97, AC97_EXTENDED_STATUS,
				     AC97_EA_DRA, 0);
	पूर्ण
	/* restore the शेष value */
	snd_ac97_ग_लिखो_cache(ac97, reg, saved);
	अगर (shaकरोw_reg)
		snd_ac97_ग_लिखो_cache(ac97, shaकरोw_reg, saved);
	*r_result = result;
पूर्ण

/* check AC97_SPDIF रेजिस्टर to accept which sample rates */
अटल अचिन्हित पूर्णांक snd_ac97_determine_spdअगर_rates(काष्ठा snd_ac97 *ac97)
अणु
	अचिन्हित पूर्णांक result = 0;
	पूर्णांक i;
	अटल स्थिर अचिन्हित लघु ctl_bits[] = अणु
		AC97_SC_SPSR_44K, AC97_SC_SPSR_32K, AC97_SC_SPSR_48K
	पूर्ण;
	अटल स्थिर अचिन्हित पूर्णांक rate_bits[] = अणु
		SNDRV_PCM_RATE_44100, SNDRV_PCM_RATE_32000, SNDRV_PCM_RATE_48000
	पूर्ण;

	क्रम (i = 0; i < (पूर्णांक)ARRAY_SIZE(ctl_bits); i++) अणु
		snd_ac97_update_bits(ac97, AC97_SPDIF, AC97_SC_SPSR_MASK, ctl_bits[i]);
		अगर ((snd_ac97_पढ़ो(ac97, AC97_SPDIF) & AC97_SC_SPSR_MASK) == ctl_bits[i])
			result |= rate_bits[i];
	पूर्ण
	वापस result;
पूर्ण

/* look क्रम the codec id table matching with the given id */
अटल स्थिर काष्ठा ac97_codec_id *look_क्रम_codec_id(स्थिर काष्ठा ac97_codec_id *table,
						     अचिन्हित पूर्णांक id)
अणु
	स्थिर काष्ठा ac97_codec_id *pid;

	क्रम (pid = table; pid->id; pid++)
		अगर (pid->id == (id & pid->mask))
			वापस pid;
	वापस शून्य;
पूर्ण

व्योम snd_ac97_get_name(काष्ठा snd_ac97 *ac97, अचिन्हित पूर्णांक id, अक्षर *name, पूर्णांक modem)
अणु
	स्थिर काष्ठा ac97_codec_id *pid;

	प्र_लिखो(name, "0x%x %c%c%c", id,
		prपूर्णांकable(id >> 24),
		prपूर्णांकable(id >> 16),
		prपूर्णांकable(id >> 8));
	pid = look_क्रम_codec_id(snd_ac97_codec_id_venकरोrs, id);
	अगर (! pid)
		वापस;

	म_नकल(name, pid->name);
	अगर (ac97 && pid->patch) अणु
		अगर ((modem && (pid->flags & AC97_MODEM_PATCH)) ||
		    (! modem && ! (pid->flags & AC97_MODEM_PATCH)))
			pid->patch(ac97);
	पूर्ण 

	pid = look_क्रम_codec_id(snd_ac97_codec_ids, id);
	अगर (pid) अणु
		म_जोड़ो(name, " ");
		म_जोड़ो(name, pid->name);
		अगर (pid->mask != 0xffffffff)
			प्र_लिखो(name + म_माप(name), " rev %d", id & ~pid->mask);
		अगर (ac97 && pid->patch) अणु
			अगर ((modem && (pid->flags & AC97_MODEM_PATCH)) ||
			    (! modem && ! (pid->flags & AC97_MODEM_PATCH)))
				pid->patch(ac97);
		पूर्ण
	पूर्ण अन्यथा
		प्र_लिखो(name + म_माप(name), " id %x", id & 0xff);
पूर्ण

/**
 * snd_ac97_get_लघु_name - retrieve codec name
 * @ac97: the codec instance
 *
 * Return: The लघु identअगरying name of the codec.
 */
स्थिर अक्षर *snd_ac97_get_लघु_name(काष्ठा snd_ac97 *ac97)
अणु
	स्थिर काष्ठा ac97_codec_id *pid;

	क्रम (pid = snd_ac97_codec_ids; pid->id; pid++)
		अगर (pid->id == (ac97->id & pid->mask))
			वापस pid->name;
	वापस "unknown codec";
पूर्ण

EXPORT_SYMBOL(snd_ac97_get_लघु_name);

/* रुको क्रम a जबतक until रेजिस्टरs are accessible after RESET
 * वापस 0 अगर ok, negative not पढ़ोy
 */
अटल पूर्णांक ac97_reset_रुको(काष्ठा snd_ac97 *ac97, पूर्णांक समयout, पूर्णांक with_modem)
अणु
	अचिन्हित दीर्घ end_समय;
	अचिन्हित लघु val;

	end_समय = jअगरfies + समयout;
	करो अणु
		
		/* use preliminary पढ़ोs to settle the communication */
		snd_ac97_पढ़ो(ac97, AC97_RESET);
		snd_ac97_पढ़ो(ac97, AC97_VENDOR_ID1);
		snd_ac97_पढ़ो(ac97, AC97_VENDOR_ID2);
		/* modem? */
		अगर (with_modem) अणु
			val = snd_ac97_पढ़ो(ac97, AC97_EXTENDED_MID);
			अगर (val != 0xffff && (val & 1) != 0)
				वापस 0;
		पूर्ण
		अगर (ac97->scaps & AC97_SCAP_DETECT_BY_VENDOR) अणु
			/* probably only Xbox issue - all रेजिस्टरs are पढ़ो as zero */
			val = snd_ac97_पढ़ो(ac97, AC97_VENDOR_ID1);
			अगर (val != 0 && val != 0xffff)
				वापस 0;
		पूर्ण अन्यथा अणु
			/* because the PCM or MASTER volume रेजिस्टरs can be modअगरied,
			 * the REC_GAIN रेजिस्टर is used क्रम tests
			 */
			/* test अगर we can ग_लिखो to the record gain volume रेजिस्टर */
			snd_ac97_ग_लिखो_cache(ac97, AC97_REC_GAIN, 0x8a05);
			अगर ((snd_ac97_पढ़ो(ac97, AC97_REC_GAIN) & 0x7fff) == 0x0a05)
				वापस 0;
		पूर्ण
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण जबतक (समय_after_eq(end_समय, jअगरfies));
	वापस -ENODEV;
पूर्ण

/**
 * snd_ac97_bus - create an AC97 bus component
 * @card: the card instance
 * @num: the bus number
 * @ops: the bus callbacks table
 * @निजी_data: निजी data poपूर्णांकer क्रम the new instance
 * @rbus: the poपूर्णांकer to store the new AC97 bus instance.
 *
 * Creates an AC97 bus component.  An काष्ठा snd_ac97_bus instance is newly
 * allocated and initialized.
 *
 * The ops table must include valid callbacks (at least पढ़ो and
 * ग_लिखो).  The other callbacks, रुको and reset, are not mandatory.
 * 
 * The घड़ी is set to 48000.  If another घड़ी is needed, set
 * ``(*rbus)->घड़ी`` manually.
 *
 * The AC97 bus instance is रेजिस्टरed as a low-level device, so you करोn't
 * have to release it manually.
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_ac97_bus(काष्ठा snd_card *card, पूर्णांक num,
		 स्थिर काष्ठा snd_ac97_bus_ops *ops,
		 व्योम *निजी_data, काष्ठा snd_ac97_bus **rbus)
अणु
	पूर्णांक err;
	काष्ठा snd_ac97_bus *bus;
	अटल स्थिर काष्ठा snd_device_ops dev_ops = अणु
		.dev_मुक्त =	snd_ac97_bus_dev_मुक्त,
	पूर्ण;

	अगर (snd_BUG_ON(!card))
		वापस -EINVAL;
	bus = kzalloc(माप(*bus), GFP_KERNEL);
	अगर (bus == शून्य)
		वापस -ENOMEM;
	bus->card = card;
	bus->num = num;
	bus->ops = ops;
	bus->निजी_data = निजी_data;
	bus->घड़ी = 48000;
	spin_lock_init(&bus->bus_lock);
	snd_ac97_bus_proc_init(bus);
	अगर ((err = snd_device_new(card, SNDRV_DEV_BUS, bus, &dev_ops)) < 0) अणु
		snd_ac97_bus_मुक्त(bus);
		वापस err;
	पूर्ण
	अगर (rbus)
		*rbus = bus;
	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_ac97_bus);

/* stop no dev release warning */
अटल व्योम ac97_device_release(काष्ठा device * dev)
अणु
पूर्ण

/* रेजिस्टर ac97 codec to bus */
अटल पूर्णांक snd_ac97_dev_रेजिस्टर(काष्ठा snd_device *device)
अणु
	काष्ठा snd_ac97 *ac97 = device->device_data;
	पूर्णांक err;

	ac97->dev.bus = &ac97_bus_type;
	ac97->dev.parent = ac97->bus->card->dev;
	ac97->dev.release = ac97_device_release;
	dev_set_name(&ac97->dev, "%d-%d:%s",
		     ac97->bus->card->number, ac97->num,
		     snd_ac97_get_लघु_name(ac97));
	अगर ((err = device_रेजिस्टर(&ac97->dev)) < 0) अणु
		ac97_err(ac97, "Can't register ac97 bus\n");
		ac97->dev.bus = शून्य;
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

/* disconnect ac97 codec */
अटल पूर्णांक snd_ac97_dev_disconnect(काष्ठा snd_device *device)
अणु
	काष्ठा snd_ac97 *ac97 = device->device_data;
	अगर (ac97->dev.bus)
		device_unरेजिस्टर(&ac97->dev);
	वापस 0;
पूर्ण

/* build_ops to करो nothing */
अटल स्थिर काष्ठा snd_ac97_build_ops null_build_ops;

#अगर_घोषित CONFIG_SND_AC97_POWER_SAVE
अटल व्योम करो_update_घातer(काष्ठा work_काष्ठा *work)
अणु
	update_घातer_regs(
		container_of(work, काष्ठा snd_ac97, घातer_work.work));
पूर्ण
#पूर्ण_अगर

/**
 * snd_ac97_mixer - create an Codec97 component
 * @bus: the AC97 bus which codec is attached to
 * @ढाँचा: the ढाँचा of ac97, including index, callbacks and
 *         the निजी data.
 * @rac97: the poपूर्णांकer to store the new ac97 instance.
 *
 * Creates an Codec97 component.  An काष्ठा snd_ac97 instance is newly
 * allocated and initialized from the ढाँचा.  The codec
 * is then initialized by the standard procedure.
 *
 * The ढाँचा must include the codec number (num) and address (addr),
 * and the निजी data (निजी_data).
 * 
 * The ac97 instance is रेजिस्टरed as a low-level device, so you करोn't
 * have to release it manually.
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */
पूर्णांक snd_ac97_mixer(काष्ठा snd_ac97_bus *bus, काष्ठा snd_ac97_ढाँचा *ढाँचा, काष्ठा snd_ac97 **rac97)
अणु
	पूर्णांक err;
	काष्ठा snd_ac97 *ac97;
	काष्ठा snd_card *card;
	अक्षर name[64];
	अचिन्हित दीर्घ end_समय;
	अचिन्हित पूर्णांक reg;
	स्थिर काष्ठा ac97_codec_id *pid;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_ac97_dev_मुक्त,
		.dev_रेजिस्टर =	snd_ac97_dev_रेजिस्टर,
		.dev_disconnect =	snd_ac97_dev_disconnect,
	पूर्ण;

	अगर (rac97)
		*rac97 = शून्य;
	अगर (snd_BUG_ON(!bus || !ढाँचा))
		वापस -EINVAL;
	अगर (snd_BUG_ON(ढाँचा->num >= 4))
		वापस -EINVAL;
	अगर (bus->codec[ढाँचा->num])
		वापस -EBUSY;

	card = bus->card;
	ac97 = kzalloc(माप(*ac97), GFP_KERNEL);
	अगर (ac97 == शून्य)
		वापस -ENOMEM;
	ac97->निजी_data = ढाँचा->निजी_data;
	ac97->निजी_मुक्त = ढाँचा->निजी_मुक्त;
	ac97->bus = bus;
	ac97->pci = ढाँचा->pci;
	ac97->num = ढाँचा->num;
	ac97->addr = ढाँचा->addr;
	ac97->scaps = ढाँचा->scaps;
	ac97->res_table = ढाँचा->res_table;
	bus->codec[ac97->num] = ac97;
	mutex_init(&ac97->reg_mutex);
	mutex_init(&ac97->page_mutex);
#अगर_घोषित CONFIG_SND_AC97_POWER_SAVE
	INIT_DELAYED_WORK(&ac97->घातer_work, करो_update_घातer);
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI
	अगर (ac97->pci) अणु
		pci_पढ़ो_config_word(ac97->pci, PCI_SUBSYSTEM_VENDOR_ID, &ac97->subप्रणाली_venकरोr);
		pci_पढ़ो_config_word(ac97->pci, PCI_SUBSYSTEM_ID, &ac97->subप्रणाली_device);
	पूर्ण
#पूर्ण_अगर
	अगर (bus->ops->reset) अणु
		bus->ops->reset(ac97);
		जाओ __access_ok;
	पूर्ण

	ac97->id = snd_ac97_पढ़ो(ac97, AC97_VENDOR_ID1) << 16;
	ac97->id |= snd_ac97_पढ़ो(ac97, AC97_VENDOR_ID2);
	अगर (ac97->id && ac97->id != (अचिन्हित पूर्णांक)-1) अणु
		pid = look_क्रम_codec_id(snd_ac97_codec_ids, ac97->id);
		अगर (pid && (pid->flags & AC97_DEFAULT_POWER_OFF))
			जाओ __access_ok;
	पूर्ण

	/* reset to शेषs */
	अगर (!(ac97->scaps & AC97_SCAP_SKIP_AUDIO))
		snd_ac97_ग_लिखो(ac97, AC97_RESET, 0);
	अगर (!(ac97->scaps & AC97_SCAP_SKIP_MODEM))
		snd_ac97_ग_लिखो(ac97, AC97_EXTENDED_MID, 0);
	अगर (bus->ops->रुको)
		bus->ops->रुको(ac97);
	अन्यथा अणु
		udelay(50);
		अगर (ac97->scaps & AC97_SCAP_SKIP_AUDIO)
			err = ac97_reset_रुको(ac97, msecs_to_jअगरfies(500), 1);
		अन्यथा अणु
			err = ac97_reset_रुको(ac97, msecs_to_jअगरfies(500), 0);
			अगर (err < 0)
				err = ac97_reset_रुको(ac97,
						      msecs_to_jअगरfies(500), 1);
		पूर्ण
		अगर (err < 0) अणु
			ac97_warn(ac97, "AC'97 %d does not respond - RESET\n",
				 ac97->num);
			/* proceed anyway - it's often non-critical */
		पूर्ण
	पूर्ण
      __access_ok:
	ac97->id = snd_ac97_पढ़ो(ac97, AC97_VENDOR_ID1) << 16;
	ac97->id |= snd_ac97_पढ़ो(ac97, AC97_VENDOR_ID2);
	अगर (! (ac97->scaps & AC97_SCAP_DETECT_BY_VENDOR) &&
	    (ac97->id == 0x00000000 || ac97->id == 0xffffffff)) अणु
		ac97_err(ac97,
			 "AC'97 %d access is not valid [0x%x], removing mixer.\n",
			 ac97->num, ac97->id);
		snd_ac97_मुक्त(ac97);
		वापस -EIO;
	पूर्ण
	pid = look_क्रम_codec_id(snd_ac97_codec_ids, ac97->id);
	अगर (pid)
		ac97->flags |= pid->flags;
	
	/* test क्रम AC'97 */
	अगर (!(ac97->scaps & AC97_SCAP_SKIP_AUDIO) && !(ac97->scaps & AC97_SCAP_AUDIO)) अणु
		/* test अगर we can ग_लिखो to the record gain volume रेजिस्टर */
		snd_ac97_ग_लिखो_cache(ac97, AC97_REC_GAIN, 0x8a06);
		अगर (((err = snd_ac97_पढ़ो(ac97, AC97_REC_GAIN)) & 0x7fff) == 0x0a06)
			ac97->scaps |= AC97_SCAP_AUDIO;
	पूर्ण
	अगर (ac97->scaps & AC97_SCAP_AUDIO) अणु
		ac97->caps = snd_ac97_पढ़ो(ac97, AC97_RESET);
		ac97->ext_id = snd_ac97_पढ़ो(ac97, AC97_EXTENDED_ID);
		अगर (ac97->ext_id == 0xffff)	/* invalid combination */
			ac97->ext_id = 0;
	पूर्ण

	/* test क्रम MC'97 */
	अगर (!(ac97->scaps & AC97_SCAP_SKIP_MODEM) && !(ac97->scaps & AC97_SCAP_MODEM)) अणु
		ac97->ext_mid = snd_ac97_पढ़ो(ac97, AC97_EXTENDED_MID);
		अगर (ac97->ext_mid == 0xffff)	/* invalid combination */
			ac97->ext_mid = 0;
		अगर (ac97->ext_mid & 1)
			ac97->scaps |= AC97_SCAP_MODEM;
	पूर्ण

	अगर (!ac97_is_audio(ac97) && !ac97_is_modem(ac97)) अणु
		अगर (!(ac97->scaps & (AC97_SCAP_SKIP_AUDIO|AC97_SCAP_SKIP_MODEM)))
			ac97_err(ac97,
				 "AC'97 %d access error (not audio or modem codec)\n",
				 ac97->num);
		snd_ac97_मुक्त(ac97);
		वापस -EACCES;
	पूर्ण

	अगर (bus->ops->reset) // FIXME: always skipping?
		जाओ __पढ़ोy_ok;

	/* FIXME: add घातerकरोwn control */
	अगर (ac97_is_audio(ac97)) अणु
		/* nothing should be in घातerकरोwn mode */
		snd_ac97_ग_लिखो_cache(ac97, AC97_POWERDOWN, 0);
		अगर (! (ac97->flags & AC97_DEFAULT_POWER_OFF)) अणु
			snd_ac97_ग_लिखो_cache(ac97, AC97_RESET, 0); /* reset to शेषs */
			udelay(100);
			snd_ac97_ग_लिखो_cache(ac97, AC97_POWERDOWN, 0);
		पूर्ण
		/* nothing should be in घातerकरोwn mode */
		snd_ac97_ग_लिखो_cache(ac97, AC97_GENERAL_PURPOSE, 0);
		end_समय = jअगरfies + msecs_to_jअगरfies(5000);
		करो अणु
			अगर ((snd_ac97_पढ़ो(ac97, AC97_POWERDOWN) & 0x0f) == 0x0f)
				जाओ __पढ़ोy_ok;
			schedule_समयout_unपूर्णांकerruptible(1);
		पूर्ण जबतक (समय_after_eq(end_समय, jअगरfies));
		ac97_warn(ac97,
			  "AC'97 %d analog subsections not ready\n", ac97->num);
	पूर्ण

	/* FIXME: add घातerकरोwn control */
	अगर (ac97_is_modem(ac97)) अणु
		अचिन्हित अक्षर पंचांगp;

		/* nothing should be in घातerकरोwn mode */
		/* note: it's important to set the rate at first */
		पंचांगp = AC97_MEA_GPIO;
		अगर (ac97->ext_mid & AC97_MEI_LINE1) अणु
			snd_ac97_ग_लिखो_cache(ac97, AC97_LINE1_RATE, 8000);
			पंचांगp |= AC97_MEA_ADC1 | AC97_MEA_DAC1;
		पूर्ण
		अगर (ac97->ext_mid & AC97_MEI_LINE2) अणु
			snd_ac97_ग_लिखो_cache(ac97, AC97_LINE2_RATE, 8000);
			पंचांगp |= AC97_MEA_ADC2 | AC97_MEA_DAC2;
		पूर्ण
		अगर (ac97->ext_mid & AC97_MEI_HANDSET) अणु
			snd_ac97_ग_लिखो_cache(ac97, AC97_HANDSET_RATE, 8000);
			पंचांगp |= AC97_MEA_HADC | AC97_MEA_HDAC;
		पूर्ण
		snd_ac97_ग_लिखो_cache(ac97, AC97_EXTENDED_MSTATUS, 0);
		udelay(100);
		/* nothing should be in घातerकरोwn mode */
		snd_ac97_ग_लिखो_cache(ac97, AC97_EXTENDED_MSTATUS, 0);
		end_समय = jअगरfies + msecs_to_jअगरfies(100);
		करो अणु
			अगर ((snd_ac97_पढ़ो(ac97, AC97_EXTENDED_MSTATUS) & पंचांगp) == पंचांगp)
				जाओ __पढ़ोy_ok;
			schedule_समयout_unपूर्णांकerruptible(1);
		पूर्ण जबतक (समय_after_eq(end_समय, jअगरfies));
		ac97_warn(ac97,
			  "MC'97 %d converters and GPIO not ready (0x%x)\n",
			  ac97->num,
			  snd_ac97_पढ़ो(ac97, AC97_EXTENDED_MSTATUS));
	पूर्ण
	
      __पढ़ोy_ok:
	अगर (ac97_is_audio(ac97))
		ac97->addr = (ac97->ext_id & AC97_EI_ADDR_MASK) >> AC97_EI_ADDR_SHIFT;
	अन्यथा
		ac97->addr = (ac97->ext_mid & AC97_MEI_ADDR_MASK) >> AC97_MEI_ADDR_SHIFT;
	अगर (ac97->ext_id & 0x01c9) अणु	/* L/R, MIC, SDAC, LDAC VRA support */
		reg = snd_ac97_पढ़ो(ac97, AC97_EXTENDED_STATUS);
		reg |= ac97->ext_id & 0x01c0; /* LDAC/SDAC/CDAC */
		अगर (! bus->no_vra)
			reg |= ac97->ext_id & 0x0009; /* VRA/VRM */
		snd_ac97_ग_लिखो_cache(ac97, AC97_EXTENDED_STATUS, reg);
	पूर्ण
	अगर ((ac97->ext_id & AC97_EI_DRA) && bus->dra) अणु
		/* Intel controllers require द्विगुन rate data to be put in
		 * slots 7+8, so let's hope the codec supports it. */
		snd_ac97_update_bits(ac97, AC97_GENERAL_PURPOSE, AC97_GP_DRSS_MASK, AC97_GP_DRSS_78);
		अगर ((snd_ac97_पढ़ो(ac97, AC97_GENERAL_PURPOSE) & AC97_GP_DRSS_MASK) == AC97_GP_DRSS_78)
			ac97->flags |= AC97_DOUBLE_RATE;
		/* restore to slots 10/11 to aव्योम the confliction with surrounds */
		snd_ac97_update_bits(ac97, AC97_GENERAL_PURPOSE, AC97_GP_DRSS_MASK, 0);
	पूर्ण
	अगर (ac97->ext_id & AC97_EI_VRA) अणु	/* VRA support */
		snd_ac97_determine_rates(ac97, AC97_PCM_FRONT_DAC_RATE, 0, &ac97->rates[AC97_RATES_FRONT_DAC]);
		snd_ac97_determine_rates(ac97, AC97_PCM_LR_ADC_RATE, 0, &ac97->rates[AC97_RATES_ADC]);
	पूर्ण अन्यथा अणु
		ac97->rates[AC97_RATES_FRONT_DAC] = SNDRV_PCM_RATE_48000;
		अगर (ac97->flags & AC97_DOUBLE_RATE)
			ac97->rates[AC97_RATES_FRONT_DAC] |= SNDRV_PCM_RATE_96000;
		ac97->rates[AC97_RATES_ADC] = SNDRV_PCM_RATE_48000;
	पूर्ण
	अगर (ac97->ext_id & AC97_EI_SPDIF) अणु
		/* codec specअगरic code (patch) should override these values */
		ac97->rates[AC97_RATES_SPDIF] = SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_32000;
	पूर्ण
	अगर (ac97->ext_id & AC97_EI_VRM) अणु	/* MIC VRA support */
		snd_ac97_determine_rates(ac97, AC97_PCM_MIC_ADC_RATE, 0, &ac97->rates[AC97_RATES_MIC_ADC]);
	पूर्ण अन्यथा अणु
		ac97->rates[AC97_RATES_MIC_ADC] = SNDRV_PCM_RATE_48000;
	पूर्ण
	अगर (ac97->ext_id & AC97_EI_SDAC) अणु	/* SDAC support */
		snd_ac97_determine_rates(ac97, AC97_PCM_SURR_DAC_RATE, AC97_PCM_FRONT_DAC_RATE, &ac97->rates[AC97_RATES_SURR_DAC]);
		ac97->scaps |= AC97_SCAP_SURROUND_DAC;
	पूर्ण
	अगर (ac97->ext_id & AC97_EI_LDAC) अणु	/* LDAC support */
		snd_ac97_determine_rates(ac97, AC97_PCM_LFE_DAC_RATE, AC97_PCM_FRONT_DAC_RATE, &ac97->rates[AC97_RATES_LFE_DAC]);
		ac97->scaps |= AC97_SCAP_CENTER_LFE_DAC;
	पूर्ण
	/* additional initializations */
	अगर (bus->ops->init)
		bus->ops->init(ac97);
	snd_ac97_get_name(ac97, ac97->id, name, !ac97_is_audio(ac97));
	snd_ac97_get_name(शून्य, ac97->id, name, !ac97_is_audio(ac97));  // ac97->id might be changed in the special setup code
	अगर (! ac97->build_ops)
		ac97->build_ops = &null_build_ops;

	अगर (ac97_is_audio(ac97)) अणु
		अक्षर comp[16];
		अगर (card->mixername[0] == '\0') अणु
			म_नकल(card->mixername, name);
		पूर्ण अन्यथा अणु
			अगर (म_माप(card->mixername) + 1 + म_माप(name) + 1 <= माप(card->mixername)) अणु
				म_जोड़ो(card->mixername, ",");
				म_जोड़ो(card->mixername, name);
			पूर्ण
		पूर्ण
		प्र_लिखो(comp, "AC97a:%08x", ac97->id);
		अगर ((err = snd_component_add(card, comp)) < 0) अणु
			snd_ac97_मुक्त(ac97);
			वापस err;
		पूर्ण
		अगर (snd_ac97_mixer_build(ac97) < 0) अणु
			snd_ac97_मुक्त(ac97);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	अगर (ac97_is_modem(ac97)) अणु
		अक्षर comp[16];
		अगर (card->mixername[0] == '\0') अणु
			म_नकल(card->mixername, name);
		पूर्ण अन्यथा अणु
			अगर (म_माप(card->mixername) + 1 + म_माप(name) + 1 <= माप(card->mixername)) अणु
				म_जोड़ो(card->mixername, ",");
				म_जोड़ो(card->mixername, name);
			पूर्ण
		पूर्ण
		प्र_लिखो(comp, "AC97m:%08x", ac97->id);
		अगर ((err = snd_component_add(card, comp)) < 0) अणु
			snd_ac97_मुक्त(ac97);
			वापस err;
		पूर्ण
		अगर (snd_ac97_modem_build(card, ac97) < 0) अणु
			snd_ac97_मुक्त(ac97);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	अगर (ac97_is_audio(ac97))
		update_घातer_regs(ac97);
	snd_ac97_proc_init(ac97);
	अगर ((err = snd_device_new(card, SNDRV_DEV_CODEC, ac97, &ops)) < 0) अणु
		snd_ac97_मुक्त(ac97);
		वापस err;
	पूर्ण
	*rac97 = ac97;
	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_ac97_mixer);

/*
 * Power करोwn the chip.
 *
 * MASTER and HEADPHONE रेजिस्टरs are muted but the रेजिस्टर cache values
 * are not changed, so that the values can be restored in snd_ac97_resume().
 */
अटल व्योम snd_ac97_घातerकरोwn(काष्ठा snd_ac97 *ac97)
अणु
	अचिन्हित लघु घातer;

	अगर (ac97_is_audio(ac97)) अणु
		/* some codecs have stereo mute bits */
		snd_ac97_ग_लिखो(ac97, AC97_MASTER, 0x9f9f);
		snd_ac97_ग_लिखो(ac97, AC97_HEADPHONE, 0x9f9f);
	पूर्ण

	/* surround, CLFE, mic घातerकरोwn */
	घातer = ac97->regs[AC97_EXTENDED_STATUS];
	अगर (ac97->scaps & AC97_SCAP_SURROUND_DAC)
		घातer |= AC97_EA_PRJ;
	अगर (ac97->scaps & AC97_SCAP_CENTER_LFE_DAC)
		घातer |= AC97_EA_PRI | AC97_EA_PRK;
	घातer |= AC97_EA_PRL;
	snd_ac97_ग_लिखो(ac97, AC97_EXTENDED_STATUS, घातer);

	/* घातerकरोwn बाह्यal amplअगरier */
	अगर (ac97->scaps & AC97_SCAP_INV_EAPD)
		घातer = ac97->regs[AC97_POWERDOWN] & ~AC97_PD_EAPD;
	अन्यथा अगर (! (ac97->scaps & AC97_SCAP_EAPD_LED))
		घातer = ac97->regs[AC97_POWERDOWN] | AC97_PD_EAPD;
	घातer |= AC97_PD_PR6;	/* Headphone amplअगरier घातerकरोwn */
	घातer |= AC97_PD_PR0 | AC97_PD_PR1;	/* ADC & DAC घातerकरोwn */
	snd_ac97_ग_लिखो(ac97, AC97_POWERDOWN, घातer);
	udelay(100);
	घातer |= AC97_PD_PR2;	/* Analog Mixer घातerकरोwn (Vref on) */
	snd_ac97_ग_लिखो(ac97, AC97_POWERDOWN, घातer);
	अगर (ac97_is_घातer_save_mode(ac97)) अणु
		घातer |= AC97_PD_PR3;	/* Analog Mixer घातerकरोwn */
		snd_ac97_ग_लिखो(ac97, AC97_POWERDOWN, घातer);
		udelay(100);
		/* AC-link घातerकरोwn, पूर्णांकernal Clk disable */
		/* FIXME: this may cause click noises on some boards */
		घातer |= AC97_PD_PR4 | AC97_PD_PR5;
		snd_ac97_ग_लिखो(ac97, AC97_POWERDOWN, घातer);
	पूर्ण
पूर्ण


काष्ठा ac97_घातer_reg अणु
	अचिन्हित लघु reg;
	अचिन्हित लघु घातer_reg;
	अचिन्हित लघु mask;
पूर्ण;

क्रमागत अणु PWIDX_ADC, PWIDX_FRONT, PWIDX_CLFE, PWIDX_SURR, PWIDX_MIC, PWIDX_SIZE पूर्ण;

अटल स्थिर काष्ठा ac97_घातer_reg घातer_regs[PWIDX_SIZE] = अणु
	[PWIDX_ADC] = अणु AC97_PCM_LR_ADC_RATE, AC97_POWERDOWN, AC97_PD_PR0पूर्ण,
	[PWIDX_FRONT] = अणु AC97_PCM_FRONT_DAC_RATE, AC97_POWERDOWN, AC97_PD_PR1पूर्ण,
	[PWIDX_CLFE] = अणु AC97_PCM_LFE_DAC_RATE, AC97_EXTENDED_STATUS,
			 AC97_EA_PRI | AC97_EA_PRKपूर्ण,
	[PWIDX_SURR] = अणु AC97_PCM_SURR_DAC_RATE, AC97_EXTENDED_STATUS,
			 AC97_EA_PRJपूर्ण,
	[PWIDX_MIC] = अणु AC97_PCM_MIC_ADC_RATE, AC97_EXTENDED_STATUS,
			AC97_EA_PRLपूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_SND_AC97_POWER_SAVE
/**
 * snd_ac97_update_घातer - update the घातerकरोwn रेजिस्टर
 * @ac97: the codec instance
 * @reg: the rate रेजिस्टर, e.g. AC97_PCM_FRONT_DAC_RATE
 * @घातerup: non-zero when घातer up the part
 *
 * Update the AC97 घातerकरोwn रेजिस्टर bits of the given part.
 *
 * Return: Zero.
 */
पूर्णांक snd_ac97_update_घातer(काष्ठा snd_ac97 *ac97, पूर्णांक reg, पूर्णांक घातerup)
अणु
	पूर्णांक i;

	अगर (! ac97)
		वापस 0;

	अगर (reg) अणु
		/* SPDIF requires DAC घातer, too */
		अगर (reg == AC97_SPDIF)
			reg = AC97_PCM_FRONT_DAC_RATE;
		क्रम (i = 0; i < PWIDX_SIZE; i++) अणु
			अगर (घातer_regs[i].reg == reg) अणु
				अगर (घातerup)
					ac97->घातer_up |= (1 << i);
				अन्यथा
					ac97->घातer_up &= ~(1 << i);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (ac97_is_घातer_save_mode(ac97) && !घातerup)
		/* adjust घातer-करोwn bits after two seconds delay
		 * (क्रम aव्योमing loud click noises क्रम many (OSS) apps
		 *  that खोलो/बंद frequently)
		 */
		schedule_delayed_work(&ac97->घातer_work,
				      msecs_to_jअगरfies(घातer_save * 1000));
	अन्यथा अणु
		cancel_delayed_work(&ac97->घातer_work);
		update_घातer_regs(ac97);
	पूर्ण

	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_ac97_update_घातer);
#पूर्ण_अगर /* CONFIG_SND_AC97_POWER_SAVE */

अटल व्योम update_घातer_regs(काष्ठा snd_ac97 *ac97)
अणु
	अचिन्हित पूर्णांक घातer_up, bits;
	पूर्णांक i;

	घातer_up = (1 << PWIDX_FRONT) | (1 << PWIDX_ADC);
	घातer_up |= (1 << PWIDX_MIC);
	अगर (ac97->scaps & AC97_SCAP_SURROUND_DAC)
		घातer_up |= (1 << PWIDX_SURR);
	अगर (ac97->scaps & AC97_SCAP_CENTER_LFE_DAC)
		घातer_up |= (1 << PWIDX_CLFE);
#अगर_घोषित CONFIG_SND_AC97_POWER_SAVE
	अगर (ac97_is_घातer_save_mode(ac97))
		घातer_up = ac97->घातer_up;
#पूर्ण_अगर
	अगर (घातer_up) अणु
		अगर (ac97->regs[AC97_POWERDOWN] & AC97_PD_PR2) अणु
			/* needs घातer-up analog mix and vref */
			snd_ac97_update_bits(ac97, AC97_POWERDOWN,
					     AC97_PD_PR3, 0);
			msleep(1);
			snd_ac97_update_bits(ac97, AC97_POWERDOWN,
					     AC97_PD_PR2, 0);
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < PWIDX_SIZE; i++) अणु
		अगर (घातer_up & (1 << i))
			bits = 0;
		अन्यथा
			bits = घातer_regs[i].mask;
		snd_ac97_update_bits(ac97, घातer_regs[i].घातer_reg,
				     घातer_regs[i].mask, bits);
	पूर्ण
	अगर (! घातer_up) अणु
		अगर (! (ac97->regs[AC97_POWERDOWN] & AC97_PD_PR2)) अणु
			/* घातer करोwn analog mix and vref */
			snd_ac97_update_bits(ac97, AC97_POWERDOWN,
					     AC97_PD_PR2, AC97_PD_PR2);
			snd_ac97_update_bits(ac97, AC97_POWERDOWN,
					     AC97_PD_PR3, AC97_PD_PR3);
		पूर्ण
	पूर्ण
पूर्ण


#अगर_घोषित CONFIG_PM
/**
 * snd_ac97_suspend - General suspend function क्रम AC97 codec
 * @ac97: the ac97 instance
 *
 * Suspends the codec, घातer करोwn the chip.
 */
व्योम snd_ac97_suspend(काष्ठा snd_ac97 *ac97)
अणु
	अगर (! ac97)
		वापस;
	अगर (ac97->build_ops->suspend)
		ac97->build_ops->suspend(ac97);
#अगर_घोषित CONFIG_SND_AC97_POWER_SAVE
	cancel_delayed_work_sync(&ac97->घातer_work);
#पूर्ण_अगर
	snd_ac97_घातerकरोwn(ac97);
पूर्ण

EXPORT_SYMBOL(snd_ac97_suspend);

/*
 * restore ac97 status
 */
अटल व्योम snd_ac97_restore_status(काष्ठा snd_ac97 *ac97)
अणु
	पूर्णांक i;

	क्रम (i = 2; i < 0x7c ; i += 2) अणु
		अगर (i == AC97_POWERDOWN || i == AC97_EXTENDED_ID)
			जारी;
		/* restore only accessible रेजिस्टरs
		 * some chip (e.g. nm256) may hang up when unsupported रेजिस्टरs
		 * are accessed..!
		 */
		अगर (test_bit(i, ac97->reg_accessed)) अणु
			snd_ac97_ग_लिखो(ac97, i, ac97->regs[i]);
			snd_ac97_पढ़ो(ac97, i);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * restore IEC958 status
 */
अटल व्योम snd_ac97_restore_iec958(काष्ठा snd_ac97 *ac97)
अणु
	अगर (ac97->ext_id & AC97_EI_SPDIF) अणु
		अगर (ac97->regs[AC97_EXTENDED_STATUS] & AC97_EA_SPDIF) अणु
			/* reset spdअगर status */
			snd_ac97_update_bits(ac97, AC97_EXTENDED_STATUS, AC97_EA_SPDIF, 0);
			snd_ac97_ग_लिखो(ac97, AC97_EXTENDED_STATUS, ac97->regs[AC97_EXTENDED_STATUS]);
			अगर (ac97->flags & AC97_CS_SPDIF)
				snd_ac97_ग_लिखो(ac97, AC97_CSR_SPDIF, ac97->regs[AC97_CSR_SPDIF]);
			अन्यथा
				snd_ac97_ग_लिखो(ac97, AC97_SPDIF, ac97->regs[AC97_SPDIF]);
			snd_ac97_update_bits(ac97, AC97_EXTENDED_STATUS, AC97_EA_SPDIF, AC97_EA_SPDIF); /* turn on again */
		पूर्ण
	पूर्ण
पूर्ण

/**
 * snd_ac97_resume - General resume function क्रम AC97 codec
 * @ac97: the ac97 instance
 *
 * Do the standard resume procedure, घातer up and restoring the
 * old रेजिस्टर values.
 */
व्योम snd_ac97_resume(काष्ठा snd_ac97 *ac97)
अणु
	अचिन्हित दीर्घ end_समय;

	अगर (! ac97)
		वापस;

	अगर (ac97->bus->ops->reset) अणु
		ac97->bus->ops->reset(ac97);
		जाओ  __reset_पढ़ोy;
	पूर्ण

	snd_ac97_ग_लिखो(ac97, AC97_POWERDOWN, 0);
	अगर (! (ac97->flags & AC97_DEFAULT_POWER_OFF)) अणु
		अगर (!(ac97->scaps & AC97_SCAP_SKIP_AUDIO))
			snd_ac97_ग_लिखो(ac97, AC97_RESET, 0);
		अन्यथा अगर (!(ac97->scaps & AC97_SCAP_SKIP_MODEM))
			snd_ac97_ग_लिखो(ac97, AC97_EXTENDED_MID, 0);
		udelay(100);
		snd_ac97_ग_लिखो(ac97, AC97_POWERDOWN, 0);
	पूर्ण
	snd_ac97_ग_लिखो(ac97, AC97_GENERAL_PURPOSE, 0);

	snd_ac97_ग_लिखो(ac97, AC97_POWERDOWN, ac97->regs[AC97_POWERDOWN]);
	अगर (ac97_is_audio(ac97)) अणु
		ac97->bus->ops->ग_लिखो(ac97, AC97_MASTER, 0x8101);
		end_समय = jअगरfies + msecs_to_jअगरfies(100);
		करो अणु
			अगर (snd_ac97_पढ़ो(ac97, AC97_MASTER) == 0x8101)
				अवरोध;
			schedule_समयout_unपूर्णांकerruptible(1);
		पूर्ण जबतक (समय_after_eq(end_समय, jअगरfies));
		/* FIXME: extra delay */
		ac97->bus->ops->ग_लिखो(ac97, AC97_MASTER, AC97_MUTE_MASK_MONO);
		अगर (snd_ac97_पढ़ो(ac97, AC97_MASTER) != AC97_MUTE_MASK_MONO)
			msleep(250);
	पूर्ण अन्यथा अणु
		end_समय = jअगरfies + msecs_to_jअगरfies(100);
		करो अणु
			अचिन्हित लघु val = snd_ac97_पढ़ो(ac97, AC97_EXTENDED_MID);
			अगर (val != 0xffff && (val & 1) != 0)
				अवरोध;
			schedule_समयout_unपूर्णांकerruptible(1);
		पूर्ण जबतक (समय_after_eq(end_समय, jअगरfies));
	पूर्ण
__reset_पढ़ोy:

	अगर (ac97->bus->ops->init)
		ac97->bus->ops->init(ac97);

	अगर (ac97->build_ops->resume)
		ac97->build_ops->resume(ac97);
	अन्यथा अणु
		snd_ac97_restore_status(ac97);
		snd_ac97_restore_iec958(ac97);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(snd_ac97_resume);
#पूर्ण_अगर


/*
 * Hardware tuning
 */
अटल व्योम set_ctl_name(अक्षर *dst, स्थिर अक्षर *src, स्थिर अक्षर *suffix)
अणु
	अगर (suffix)
		प्र_लिखो(dst, "%s %s", src, suffix);
	अन्यथा
		म_नकल(dst, src);
पूर्ण	

/* हटाओ the control with the given name and optional suffix */
अटल पूर्णांक snd_ac97_हटाओ_ctl(काष्ठा snd_ac97 *ac97, स्थिर अक्षर *name,
			       स्थिर अक्षर *suffix)
अणु
	काष्ठा snd_ctl_elem_id id;
	स_रखो(&id, 0, माप(id));
	set_ctl_name(id.name, name, suffix);
	id.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	वापस snd_ctl_हटाओ_id(ac97->bus->card, &id);
पूर्ण

अटल काष्ठा snd_kcontrol *ctl_find(काष्ठा snd_ac97 *ac97, स्थिर अक्षर *name, स्थिर अक्षर *suffix)
अणु
	काष्ठा snd_ctl_elem_id sid;
	स_रखो(&sid, 0, माप(sid));
	set_ctl_name(sid.name, name, suffix);
	sid.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	वापस snd_ctl_find_id(ac97->bus->card, &sid);
पूर्ण

/* नाम the control with the given name and optional suffix */
अटल पूर्णांक snd_ac97_नाम_ctl(काष्ठा snd_ac97 *ac97, स्थिर अक्षर *src,
			       स्थिर अक्षर *dst, स्थिर अक्षर *suffix)
अणु
	काष्ठा snd_kcontrol *kctl = ctl_find(ac97, src, suffix);
	अगर (kctl) अणु
		set_ctl_name(kctl->id.name, dst, suffix);
		वापस 0;
	पूर्ण
	वापस -ENOENT;
पूर्ण

/* नाम both Volume and Switch controls - करोn't check the वापस value */
अटल व्योम snd_ac97_नाम_vol_ctl(काष्ठा snd_ac97 *ac97, स्थिर अक्षर *src,
				    स्थिर अक्षर *dst)
अणु
	snd_ac97_नाम_ctl(ac97, src, dst, "Switch");
	snd_ac97_नाम_ctl(ac97, src, dst, "Volume");
पूर्ण

/* swap controls */
अटल पूर्णांक snd_ac97_swap_ctl(काष्ठा snd_ac97 *ac97, स्थिर अक्षर *s1,
			     स्थिर अक्षर *s2, स्थिर अक्षर *suffix)
अणु
	काष्ठा snd_kcontrol *kctl1, *kctl2;
	kctl1 = ctl_find(ac97, s1, suffix);
	kctl2 = ctl_find(ac97, s2, suffix);
	अगर (kctl1 && kctl2) अणु
		set_ctl_name(kctl1->id.name, s2, suffix);
		set_ctl_name(kctl2->id.name, s1, suffix);
		वापस 0;
	पूर्ण
	वापस -ENOENT;
पूर्ण

#अगर 1
/* bind hp and master controls instead of using only hp control */
अटल पूर्णांक bind_hp_volsw_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक err = snd_ac97_put_volsw(kcontrol, ucontrol);
	अगर (err > 0) अणु
		अचिन्हित दीर्घ priv_saved = kcontrol->निजी_value;
		kcontrol->निजी_value = (kcontrol->निजी_value & ~0xff) | AC97_HEADPHONE;
		snd_ac97_put_volsw(kcontrol, ucontrol);
		kcontrol->निजी_value = priv_saved;
	पूर्ण
	वापस err;
पूर्ण

/* ac97 tune: bind Master and Headphone controls */
अटल पूर्णांक tune_hp_only(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा snd_kcontrol *msw = ctl_find(ac97, "Master Playback Switch", शून्य);
	काष्ठा snd_kcontrol *mvol = ctl_find(ac97, "Master Playback Volume", शून्य);
	अगर (! msw || ! mvol)
		वापस -ENOENT;
	msw->put = bind_hp_volsw_put;
	mvol->put = bind_hp_volsw_put;
	snd_ac97_हटाओ_ctl(ac97, "Headphone Playback", "Switch");
	snd_ac97_हटाओ_ctl(ac97, "Headphone Playback", "Volume");
	वापस 0;
पूर्ण

#अन्यथा
/* ac97 tune: use Headphone control as master */
अटल पूर्णांक tune_hp_only(काष्ठा snd_ac97 *ac97)
अणु
	अगर (ctl_find(ac97, "Headphone Playback Switch", शून्य) == शून्य)
		वापस -ENOENT;
	snd_ac97_हटाओ_ctl(ac97, "Master Playback", "Switch");
	snd_ac97_हटाओ_ctl(ac97, "Master Playback", "Volume");
	snd_ac97_नाम_vol_ctl(ac97, "Headphone Playback", "Master Playback");
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* ac97 tune: swap Headphone and Master controls */
अटल पूर्णांक tune_swap_hp(काष्ठा snd_ac97 *ac97)
अणु
	अगर (ctl_find(ac97, "Headphone Playback Switch", शून्य) == शून्य)
		वापस -ENOENT;
	snd_ac97_नाम_vol_ctl(ac97, "Master Playback", "Line-Out Playback");
	snd_ac97_नाम_vol_ctl(ac97, "Headphone Playback", "Master Playback");
	वापस 0;
पूर्ण

/* ac97 tune: swap Surround and Master controls */
अटल पूर्णांक tune_swap_surround(काष्ठा snd_ac97 *ac97)
अणु
	अगर (snd_ac97_swap_ctl(ac97, "Master Playback", "Surround Playback", "Switch") ||
	    snd_ac97_swap_ctl(ac97, "Master Playback", "Surround Playback", "Volume"))
		वापस -ENOENT;
	वापस 0;
पूर्ण

/* ac97 tune: set up mic sharing क्रम AD codecs */
अटल पूर्णांक tune_ad_sharing(काष्ठा snd_ac97 *ac97)
अणु
	अचिन्हित लघु scfg;
	अगर ((ac97->id & 0xffffff00) != 0x41445300) अणु
		ac97_err(ac97, "ac97_quirk AD_SHARING is only for AD codecs\n");
		वापस -EINVAL;
	पूर्ण
	/* Turn on OMS bit to route microphone to back panel */
	scfg = snd_ac97_पढ़ो(ac97, AC97_AD_SERIAL_CFG);
	snd_ac97_ग_लिखो_cache(ac97, AC97_AD_SERIAL_CFG, scfg | 0x0200);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ac97_alc_jack_detect = 
AC97_SINGLE("Jack Detect", AC97_ALC650_CLOCK, 5, 1, 0);

/* ac97 tune: set up ALC jack-select */
अटल पूर्णांक tune_alc_jack(काष्ठा snd_ac97 *ac97)
अणु
	अगर ((ac97->id & 0xffffff00) != 0x414c4700) अणु
		ac97_err(ac97,
			 "ac97_quirk ALC_JACK is only for Realtek codecs\n");
		वापस -EINVAL;
	पूर्ण
	snd_ac97_update_bits(ac97, 0x7a, 0x20, 0x20); /* select jack detect function */
	snd_ac97_update_bits(ac97, 0x7a, 0x01, 0x01); /* Line-out स्वतः mute */
	अगर (ac97->id == AC97_ID_ALC658D)
		snd_ac97_update_bits(ac97, 0x74, 0x0800, 0x0800);
	वापस snd_ctl_add(ac97->bus->card, snd_ac97_cnew(&snd_ac97_alc_jack_detect, ac97));
पूर्ण

/* ac97 tune: inversed EAPD bit */
अटल पूर्णांक tune_inv_eapd(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा snd_kcontrol *kctl = ctl_find(ac97, "External Amplifier", शून्य);
	अगर (! kctl)
		वापस -ENOENT;
	set_inv_eapd(ac97, kctl);
	वापस 0;
पूर्ण

अटल पूर्णांक master_mute_sw_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक err = snd_ac97_put_volsw(kcontrol, ucontrol);
	अगर (err > 0) अणु
		काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
		पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0x0f;
		पूर्णांक rshअगरt = (kcontrol->निजी_value >> 12) & 0x0f;
		अचिन्हित लघु mask;
		अगर (shअगरt != rshअगरt)
			mask = AC97_MUTE_MASK_STEREO;
		अन्यथा
			mask = AC97_MUTE_MASK_MONO;
		snd_ac97_update_bits(ac97, AC97_POWERDOWN, AC97_PD_EAPD,
				     (ac97->regs[AC97_MASTER] & mask) == mask ?
				     AC97_PD_EAPD : 0);
	पूर्ण
	वापस err;
पूर्ण

/* ac97 tune: EAPD controls mute LED bound with the master mute */
अटल पूर्णांक tune_mute_led(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा snd_kcontrol *msw = ctl_find(ac97, "Master Playback Switch", शून्य);
	अगर (! msw)
		वापस -ENOENT;
	msw->put = master_mute_sw_put;
	snd_ac97_हटाओ_ctl(ac97, "External Amplifier", शून्य);
	snd_ac97_update_bits(
		ac97, AC97_POWERDOWN,
		AC97_PD_EAPD, AC97_PD_EAPD /* mute LED on */
	);
	ac97->scaps |= AC97_SCAP_EAPD_LED;
	वापस 0;
पूर्ण

अटल पूर्णांक hp_master_mute_sw_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक err = bind_hp_volsw_put(kcontrol, ucontrol);
	अगर (err > 0) अणु
		काष्ठा snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
		पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0x0f;
		पूर्णांक rshअगरt = (kcontrol->निजी_value >> 12) & 0x0f;
		अचिन्हित लघु mask;
		अगर (shअगरt != rshअगरt)
			mask = AC97_MUTE_MASK_STEREO;
		अन्यथा
			mask = AC97_MUTE_MASK_MONO;
		snd_ac97_update_bits(ac97, AC97_POWERDOWN, AC97_PD_EAPD,
				     (ac97->regs[AC97_MASTER] & mask) == mask ?
				     AC97_PD_EAPD : 0);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक tune_hp_mute_led(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा snd_kcontrol *msw = ctl_find(ac97, "Master Playback Switch", शून्य);
	काष्ठा snd_kcontrol *mvol = ctl_find(ac97, "Master Playback Volume", शून्य);
	अगर (! msw || ! mvol)
		वापस -ENOENT;
	msw->put = hp_master_mute_sw_put;
	mvol->put = bind_hp_volsw_put;
	snd_ac97_हटाओ_ctl(ac97, "External Amplifier", शून्य);
	snd_ac97_हटाओ_ctl(ac97, "Headphone Playback", "Switch");
	snd_ac97_हटाओ_ctl(ac97, "Headphone Playback", "Volume");
	snd_ac97_update_bits(
		ac97, AC97_POWERDOWN,
		AC97_PD_EAPD, AC97_PD_EAPD /* mute LED on */
	);
	वापस 0;
पूर्ण

काष्ठा quirk_table अणु
	स्थिर अक्षर *name;
	पूर्णांक (*func)(काष्ठा snd_ac97 *);
पूर्ण;

अटल स्थिर काष्ठा quirk_table applicable_quirks[] = अणु
	अणु "none", शून्य पूर्ण,
	अणु "hp_only", tune_hp_only पूर्ण,
	अणु "swap_hp", tune_swap_hp पूर्ण,
	अणु "swap_surround", tune_swap_surround पूर्ण,
	अणु "ad_sharing", tune_ad_sharing पूर्ण,
	अणु "alc_jack", tune_alc_jack पूर्ण,
	अणु "inv_eapd", tune_inv_eapd पूर्ण,
	अणु "mute_led", tune_mute_led पूर्ण,
	अणु "hp_mute_led", tune_hp_mute_led पूर्ण,
पूर्ण;

/* apply the quirk with the given type */
अटल पूर्णांक apply_quirk(काष्ठा snd_ac97 *ac97, पूर्णांक type)
अणु
	अगर (type <= 0)
		वापस 0;
	अन्यथा अगर (type >= ARRAY_SIZE(applicable_quirks))
		वापस -EINVAL;
	अगर (applicable_quirks[type].func)
		वापस applicable_quirks[type].func(ac97);
	वापस 0;
पूर्ण

/* apply the quirk with the given name */
अटल पूर्णांक apply_quirk_str(काष्ठा snd_ac97 *ac97, स्थिर अक्षर *typestr)
अणु
	पूर्णांक i;
	स्थिर काष्ठा quirk_table *q;

	क्रम (i = 0; i < ARRAY_SIZE(applicable_quirks); i++) अणु
		q = &applicable_quirks[i];
		अगर (q->name && ! म_भेद(typestr, q->name))
			वापस apply_quirk(ac97, i);
	पूर्ण
	/* क्रम compatibility, accept the numbers, too */
	अगर (*typestr >= '0' && *typestr <= '9')
		वापस apply_quirk(ac97, (पूर्णांक)simple_म_से_अदीर्घ(typestr, शून्य, 10));
	वापस -EINVAL;
पूर्ण

/**
 * snd_ac97_tune_hardware - tune up the hardware
 * @ac97: the ac97 instance
 * @quirk: quirk list
 * @override: explicit quirk value (overrides the list अगर non-शून्य)
 *
 * Do some workaround क्रम each pci device, such as renaming of the
 * headphone (true line-out) control as "Master".
 * The quirk-list must be terminated with a zero-filled entry.
 *
 * Return: Zero अगर successful, or a negative error code on failure.
 */

पूर्णांक snd_ac97_tune_hardware(काष्ठा snd_ac97 *ac97,
			   स्थिर काष्ठा ac97_quirk *quirk, स्थिर अक्षर *override)
अणु
	पूर्णांक result;

	/* quirk overriden? */
	अगर (override && म_भेद(override, "-1") && म_भेद(override, "default")) अणु
		result = apply_quirk_str(ac97, override);
		अगर (result < 0)
			ac97_err(ac97, "applying quirk type %s failed (%d)\n",
				 override, result);
		वापस result;
	पूर्ण

	अगर (! quirk)
		वापस -EINVAL;

	क्रम (; quirk->subvenकरोr; quirk++) अणु
		अगर (quirk->subvenकरोr != ac97->subप्रणाली_venकरोr)
			जारी;
		अगर ((! quirk->mask && quirk->subdevice == ac97->subप्रणाली_device) ||
		    quirk->subdevice == (quirk->mask & ac97->subप्रणाली_device)) अणु
			अगर (quirk->codec_id && quirk->codec_id != ac97->id)
				जारी;
			ac97_dbg(ac97, "ac97 quirk for %s (%04x:%04x)\n",
				 quirk->name, ac97->subप्रणाली_venकरोr,
				 ac97->subप्रणाली_device);
			result = apply_quirk(ac97, quirk->type);
			अगर (result < 0)
				ac97_err(ac97,
					 "applying quirk type %d for %s failed (%d)\n",
					 quirk->type, quirk->name, result);
			वापस result;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_ac97_tune_hardware);
