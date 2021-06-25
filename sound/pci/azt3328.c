<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*  azt3328.c - driver क्रम Aztech AZF3328 based soundcards (e.g. PCI168).
 *  Copyright (C) 2002, 2005 - 2011 by Andreas Mohr <andi AT lisas.de>
 *
 *  Framework borrowed from Bart Hartgers's als4000.c.
 *  Driver developed on PCI168 AP(W) version (PCI rev. 10, subप्रणाली ID 1801),
 *  found in a Fujitsu-Siemens PC ("Cordant", aluminum हाल).
 *  Other versions are:
 *  PCI168 A(W), sub ID 1800
 *  PCI168 A/AP, sub ID 8000
 *  Please give me feedback in हाल you try my driver with one of these!!
 *
 *  Keywords: Winकरोws XP Vista 168nt4-125.zip 168win95-125.zip PCI 168 करोwnload
 *  (XP/Vista करो not support this card at all but every Linux distribution
 *   has very good support out of the box;
 *   just to make sure that the right people hit this and get to know that,
 *   despite the high level of Internet ignorance - as usual :-P -
 *   about very good support क्रम this card - on Linux!)
 *
 * NOTES
 *  Since Aztech करोes not provide any chipset करोcumentation,
 *  even on repeated request to various addresses,
 *  and the answer that was finally given was negative
 *  (and I was stupid enough to manage to get hold of a PCI168 soundcard
 *  in the first place >:-Pपूर्ण),
 *  I was क्रमced to base this driver on reverse engineering
 *  (3 weeks' worth of evenings filled with driver work).
 *  (and no, I did NOT go the easy way: to pick up a SB PCI128 क्रम 9 Euros)
 *
 *  It is quite likely that the AZF3328 chip is the PCI cousin of the
 *  AZF3318 ("azt1020 pnp", "MM Pro 16") ISA chip, given very similar specs.
 *
 *  The AZF3328 chip (note: AZF3328, *not* AZT3328, that's just the driver name
 *  क्रम compatibility reasons) from Azfin (joपूर्णांक-venture of Aztech and Fincitec,
 *  Fincitec acquired by National Semiconductor in 2002, together with the
 *  Fincitec-related company ARSmikro) has the following features:
 *
 *  - compatibility & compliance:
 *    - Microsoft PC 97 ("PC 97 Hardware Design Guide",
 *                       http://www.microsoft.com/whdc/archive/pcguides.mspx)
 *    - Microsoft PC 98 Baseline Audio
 *    - MPU401 UART
 *    - Sound Blaster Emulation (DOS Box)
 *  - builtin AC97 conक्रमmant codec (SNR over 80dB)
 *    Note that "conformant" != "compliant"!! this chip's mixer रेजिस्टर layout
 *    *dअगरfers* from the standard AC97 layout:
 *    they chose to not implement the headphone रेजिस्टर (which is not a
 *    problem since it's merely optional), yet when करोing this, they committed
 *    the grave sin of letting other रेजिस्टरs follow immediately instead of
 *    keeping a headphone dummy रेजिस्टर, thereby shअगरting the mixer रेजिस्टर
 *    addresses illegally. So far unक्रमtunately it looks like the very flexible
 *    ALSA AC97 support is still not enough to easily compensate क्रम such a
 *    grave layout violation despite all tweaks and quirks mechanisms it offers.
 *    Well, not quite: now ac97 layer is much improved (bus-specअगरic ops!),
 *    thus I was able to implement support - it's actually working quite well.
 *    An पूर्णांकeresting item might be Aztech AMR 2800-W, since it's an AC97
 *    modem card which might reveal the Aztech-specअगरic codec ID which
 *    we might want to pretend, too. Dito PCI168's brother, PCI368,
 *    where the advertising datasheet says it's AC97-based and has a
 *    Digital Enhanced Game Port.
 *  - builtin genuine OPL3 - verअगरied to work fine, 20080506
 *  - full duplex 16bit playback/record at independent sampling rate
 *  - MPU401 (+ legacy address support, claimed by one official spec sheet)
 *    FIXME: how to enable legacy addr??
 *  - game port (legacy address support)
 *  - builtin DirectInput support, helps reduce CPU overhead (पूर्णांकerrupt-driven
 *    features supported). - See common term "Digital Enhanced Game Port"...
 *    (probably DirectInput 3.0 spec - confirm)
 *  - builtin 3D enhancement (said to be YAMAHA Ymersion)
 *  - built-in General DirectX समयr having a 20 bits counter
 *    with 1us resolution (see below!)
 *  - I2S serial output port क्रम बाह्यal DAC
 *    [FIXME: 3.3V or 5V level? maximum rate is 66.2kHz right?]
 *  - supports 33MHz PCI spec 2.1, PCI घातer management 1.0, compliant with ACPI
 *  - supports hardware volume control
 *  - single chip low cost solution (128 pin QFP)
 *  - supports programmable Sub-venकरोr and Sub-प्रणाली ID [24C02 SEEPROM chip]
 *    required क्रम Microsoft's logo compliance (FIXME: where?)
 *    At least the Trident 4D Wave DX has one bit somewhere
 *    to enable ग_लिखोs to PCI subप्रणाली VID रेजिस्टरs, that should be it.
 *    This might easily be in extended PCI reg space, since PCI168 also has
 *    some custom data starting at 0x80. What kind of config settings
 *    are located in our extended PCI space anyway??
 *  - PCI168 AP(W) card: घातer amplअगरier with 4 Watts/channel at 4 Ohms
 *    [TDA1517P chip]
 *
 *  Note that this driver now is actually *better* than the Winकरोws driver,
 *  since it additionally supports the card's 1MHz DirectX समयr - just try
 *  the following snd-seq module parameters etc.:
 *  - options snd-seq seq_शेष_समयr_class=2 seq_शेष_समयr_sclass=0
 *    seq_शेष_समयr_card=0 seq_client_load=1 seq_शेष_समयr_device=0
 *    seq_शेष_समयr_subdevice=0 seq_शेष_समयr_resolution=1000000
 *  - "timidity -iAv -B2,8 -Os -EFreverb=0"
 *  - "pmidi -p 128:0 jazz.mid"
 *
 *  OPL3 hardware playback testing, try something like:
 *  cat /proc/asound/hwdep
 *  and
 *  aconnect -o
 *  Then use
 *  sbiload -Dhw:x,y --opl3 /usr/share/sounds/opl3/std.o3 ......./drums.o3
 *  where x,y is the xx-yy number as given in hwdep.
 *  Then try
 *  pmidi -p a:b jazz.mid
 *  where a:b is the client number plus 0 usually, as given by aconnect above.
 *  Oh, and make sure to unmute the FM mixer control (करोh!)
 *  NOTE: घातer use during OPL3 playback is _VERY_ high (70W --> 90W!)
 *  despite no CPU activity, possibly due to hindering ACPI idling somehow.
 *  Shouldn't be a problem of the AZF3328 chip itself, I'd hope.
 *  Higher PCM / FM mixer levels seem to conflict (causes crackling),
 *  at least someबार.   Maybe even use with hardware sequencer समयr above :)
 *  adplay/adplug-utils might soon offer hardware-based OPL3 playback, too.
 *
 *  Certain PCI versions of this card are susceptible to DMA traffic underruns
 *  in some प्रणालीs (resulting in sound crackling/clicking/popping),
 *  probably because they करोn't have a DMA FIFO buffer or so.
 *  Overview (PCI ID/PCI subID/PCI rev.):
 *  - no DMA crackling on SiS735: 0x50DC/0x1801/16
 *  - unknown perक्रमmance: 0x50DC/0x1801/10
 *    (well, it's not bad on an Athlon 1800 with now very optimized IRQ handler)
 *
 *  Crackling happens with VIA chipsets or, in my हाल, an SiS735, which is
 *  supposed to be very fast and supposed to get rid of crackling much
 *  better than a VIA, yet ironically I still get crackling, like many other
 *  people with the same chipset.
 *  Possible remedies:
 *  - use speaker (amplअगरier) output instead of headphone output
 *    (in हाल crackling is due to overloaded output clipping)
 *  - plug card पूर्णांकo a dअगरferent PCI slot, preferably one that isn't shared
 *    too much (this helps a lot, but not completely!)
 *  - get rid of PCI VGA card, use AGP instead
 *  - upgrade or करोwngrade BIOS
 *  - fiddle with PCI latency settings (setpci -v -s BUSID latency_समयr=XX)
 *    Not too helpful.
 *  - Disable ACPI/घातer management/"Auto Detect RAM/PCI Clk" in BIOS
 *
 * BUGS
 *  - full-duplex might *still* be problematic, however a recent test was fine
 *  - (non-bug) "Bass/Treble or 3D settings don't work" - they करो get evaluated
 *    अगर you set PCM output चयन to "pre 3D" instead of "post 3D".
 *    If this can't be set, then get a mixer application that Isn't Stupid (पंचांग)
 *    (e.g. kmix, gamix) - unक्रमtunately several are!!
 *  - locking is not entirely clean, especially the audio stream activity
 *    पूर्णांकs --> may be racy
 *  - an _unconnected_ secondary joystick at the gameport will be reported
 *    to be "active" (भग्नing values, not precisely -1) due to the way we need
 *    to पढ़ो the Digital Enhanced Game Port. Not sure whether it is fixable.
 *
 * TODO
 *  - use PCI_VDEVICE
 *  - verअगरy driver status on x86_64
 *  - test multi-card driver operation
 *  - (ab)use 1MHz DirectX समयr as kernel घड़ीsource
 *  - test MPU401 MIDI playback etc.
 *  - add more घातer micro-management (disable various units of the card
 *    as दीर्घ as they're unused, to improve audio quality and save घातer).
 *    However this requires more I/O ports which I haven't figured out yet
 *    and which thus might not even exist...
 *    The standard suspend/resume functionality could probably make use of
 *    some improvement, too...
 *  - figure out what all unknown port bits are responsible क्रम
 *  - figure out some cleverly evil scheme to possibly make ALSA AC97 code
 *    fully accept our quite incompatible ""AC97"" mixer and thus save some
 *    code (but I'm not too optimistic that करोing this is possible at all)
 *  - use MMIO (memory-mapped I/O)? Slightly faster access, e.g. क्रम gameport.
 */

#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/bug.h> /* WARN_ONCE */
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/gameport.h>
#समावेश <linux/module.h>
#समावेश <linux/dma-mapping.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/opl3.h>
#समावेश <sound/initval.h>
/*
 * Config चयन, to use ALSA's AC97 layer instead of old custom mixer crap.
 * If the AC97 compatibility parts we needed to implement locally turn out
 * to work nicely, then हटाओ the old implementation eventually.
 */
#घोषणा AZF_USE_AC97_LAYER 1

#अगर_घोषित AZF_USE_AC97_LAYER
#समावेश <sound/ac97_codec.h>
#पूर्ण_अगर
#समावेश "azt3328.h"

MODULE_AUTHOR("Andreas Mohr <andi AT lisas.de>");
MODULE_DESCRIPTION("Aztech AZF3328 (PCI168)");
MODULE_LICENSE("GPL");

#अगर IS_REACHABLE(CONFIG_GAMEPORT)
#घोषणा SUPPORT_GAMEPORT 1
#पूर्ण_अगर

/* === Debug settings ===
  Further diagnostic functionality than the settings below
  करोes not need to be provided, since one can easily ग_लिखो a POSIX shell script
  to dump the card's I/O ports (those listed in lspci -v -v):
  dump()
  अणु
    local descr=$1; local addr=$2; local count=$3

    echo "${descr}: ${count} @ ${addr}:"
    dd अगर=/dev/port skip=`म_लिखो %d $अणुaddrपूर्ण` count=$अणुcountपूर्ण bs=1 \
      2>/dev/null| hexdump -C
  पूर्ण
  and then use something like
  "dump joy200 0x200 8", "dump mpu388 0x388 4", "dump joy 0xb400 8",
  "dump codec00 0xa800 32", "dump mixer 0xb800 64", "dump synth 0xbc00 8",
  possibly within a "while true; do ... sleep 1; done" loop.
  Tweaking ports could be करोne using
  VALSTRING="`printf "%02x" $value`"
  म_लिखो "\x""$VALSTRING"|dd of=/dev/port seek=`म_लिखो %d $अणुaddrपूर्ण` bs=1 \
    2>/dev/null
*/

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for AZF3328 soundcard.");

अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for AZF3328 soundcard.");

अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;	/* Enable this card */
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable AZF3328 soundcard.");

अटल पूर्णांक seqसमयr_scaling = 128;
module_param(seqसमयr_scaling, पूर्णांक, 0444);
MODULE_PARM_DESC(seqसमयr_scaling, "Set 1024000Hz sequencer timer scale factor (lockup danger!). Default 128.");

क्रमागत snd_azf3328_codec_type अणु
  /* warning: fixed indices (also used क्रम biपंचांगask checks!) */
  AZF_CODEC_PLAYBACK = 0,
  AZF_CODEC_CAPTURE = 1,
  AZF_CODEC_I2S_OUT = 2,
पूर्ण;

काष्ठा snd_azf3328_codec_data अणु
	अचिन्हित दीर्घ io_base; /* keep first! (aव्योम offset calc) */
	अचिन्हित पूर्णांक dma_base; /* helper to aव्योम an indirection in hotpath */
	spinlock_t *lock; /* TODO: convert to our own per-codec lock member */
	काष्ठा snd_pcm_substream *substream;
	bool running;
	क्रमागत snd_azf3328_codec_type type;
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा snd_azf3328 अणु
	/* often-used fields towards beginning, then grouped */

	अचिन्हित दीर्घ ctrl_io; /* usually 0xb000, size 128 */
	अचिन्हित दीर्घ game_io;  /* usually 0xb400, size 8 */
	अचिन्हित दीर्घ mpu_io;   /* usually 0xb800, size 4 */
	अचिन्हित दीर्घ opl3_io; /* usually 0xbc00, size 8 */
	अचिन्हित दीर्घ mixer_io; /* usually 0xc000, size 64 */

	spinlock_t reg_lock;

	काष्ठा snd_समयr *समयr;

	काष्ठा snd_pcm *pcm[3];

	/* playback, recording and I2S out codecs */
	काष्ठा snd_azf3328_codec_data codecs[3];

#अगर_घोषित AZF_USE_AC97_LAYER
	काष्ठा snd_ac97 *ac97;
#पूर्ण_अगर

	काष्ठा snd_card *card;
	काष्ठा snd_rawmidi *rmidi;

#अगर_घोषित SUPPORT_GAMEPORT
	काष्ठा gameport *gameport;
	u16 axes[4];
#पूर्ण_अगर

	काष्ठा pci_dev *pci;
	पूर्णांक irq;

	/* रेजिस्टर 0x6a is ग_लिखो-only, thus need to remember setting.
	 * If we need to add more रेजिस्टरs here, then we might try to fold this
	 * पूर्णांकo some transparent combined shaकरोw रेजिस्टर handling with
	 * CONFIG_PM रेजिस्टर storage below, but that's slightly dअगरficult. */
	u16 shaकरोw_reg_ctrl_6AH;

#अगर_घोषित CONFIG_PM_SLEEP
	/* रेजिस्टर value containers क्रम घातer management
	 * Note: not always full I/O range preserved (similar to Win driver!) */
	u32 saved_regs_ctrl[AZF_ALIGN(AZF_IO_SIZE_CTRL_PM) / 4];
	u32 saved_regs_game[AZF_ALIGN(AZF_IO_SIZE_GAME_PM) / 4];
	u32 saved_regs_mpu[AZF_ALIGN(AZF_IO_SIZE_MPU_PM) / 4];
	u32 saved_regs_opl3[AZF_ALIGN(AZF_IO_SIZE_OPL3_PM) / 4];
	u32 saved_regs_mixer[AZF_ALIGN(AZF_IO_SIZE_MIXER_PM) / 4];
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा pci_device_id snd_azf3328_ids[] = अणु
	अणु 0x122D, 0x50DC, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,   /* PCI168/3328 */
	अणु 0x122D, 0x80DA, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,   /* 3328 */
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_azf3328_ids);


अटल पूर्णांक
snd_azf3328_io_reg_setb(अचिन्हित reg, u8 mask, bool करो_set)
अणु
	/* Well, strictly spoken, the inb/outb sequence isn't atomic
	   and would need locking. However we currently करोn't care
	   since it potentially complicates matters. */
	u8 prev = inb(reg), new;

	new = (करो_set) ? (prev|mask) : (prev & ~mask);
	/* we need to always ग_लिखो the new value no matter whether it dअगरfers
	 * or not, since some रेजिस्टर bits करोn't indicate their setting */
	outb(new, reg);
	अगर (new != prev)
		वापस 1;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
snd_azf3328_codec_outb(स्थिर काष्ठा snd_azf3328_codec_data *codec,
		       अचिन्हित reg,
		       u8 value
)
अणु
	outb(value, codec->io_base + reg);
पूर्ण

अटल अंतरभूत u8
snd_azf3328_codec_inb(स्थिर काष्ठा snd_azf3328_codec_data *codec, अचिन्हित reg)
अणु
	वापस inb(codec->io_base + reg);
पूर्ण

अटल अंतरभूत व्योम
snd_azf3328_codec_outw(स्थिर काष्ठा snd_azf3328_codec_data *codec,
		       अचिन्हित reg,
		       u16 value
)
अणु
	outw(value, codec->io_base + reg);
पूर्ण

अटल अंतरभूत u16
snd_azf3328_codec_inw(स्थिर काष्ठा snd_azf3328_codec_data *codec, अचिन्हित reg)
अणु
	वापस inw(codec->io_base + reg);
पूर्ण

अटल अंतरभूत व्योम
snd_azf3328_codec_outl(स्थिर काष्ठा snd_azf3328_codec_data *codec,
		       अचिन्हित reg,
		       u32 value
)
अणु
	outl(value, codec->io_base + reg);
पूर्ण

अटल अंतरभूत व्योम
snd_azf3328_codec_outl_multi(स्थिर काष्ठा snd_azf3328_codec_data *codec,
			     अचिन्हित reg, स्थिर व्योम *buffer, पूर्णांक count
)
अणु
	अचिन्हित दीर्घ addr = codec->io_base + reg;
	अगर (count) अणु
		स्थिर u32 *buf = buffer;
		करो अणु
			outl(*buf++, addr);
			addr += 4;
		पूर्ण जबतक (--count);
	पूर्ण
पूर्ण

अटल अंतरभूत u32
snd_azf3328_codec_inl(स्थिर काष्ठा snd_azf3328_codec_data *codec, अचिन्हित reg)
अणु
	वापस inl(codec->io_base + reg);
पूर्ण

अटल अंतरभूत व्योम
snd_azf3328_ctrl_outb(स्थिर काष्ठा snd_azf3328 *chip, अचिन्हित reg, u8 value)
अणु
	outb(value, chip->ctrl_io + reg);
पूर्ण

अटल अंतरभूत u8
snd_azf3328_ctrl_inb(स्थिर काष्ठा snd_azf3328 *chip, अचिन्हित reg)
अणु
	वापस inb(chip->ctrl_io + reg);
पूर्ण

अटल अंतरभूत u16
snd_azf3328_ctrl_inw(स्थिर काष्ठा snd_azf3328 *chip, अचिन्हित reg)
अणु
	वापस inw(chip->ctrl_io + reg);
पूर्ण

अटल अंतरभूत व्योम
snd_azf3328_ctrl_outw(स्थिर काष्ठा snd_azf3328 *chip, अचिन्हित reg, u16 value)
अणु
	outw(value, chip->ctrl_io + reg);
पूर्ण

अटल अंतरभूत व्योम
snd_azf3328_ctrl_outl(स्थिर काष्ठा snd_azf3328 *chip, अचिन्हित reg, u32 value)
अणु
	outl(value, chip->ctrl_io + reg);
पूर्ण

अटल अंतरभूत व्योम
snd_azf3328_game_outb(स्थिर काष्ठा snd_azf3328 *chip, अचिन्हित reg, u8 value)
अणु
	outb(value, chip->game_io + reg);
पूर्ण

अटल अंतरभूत व्योम
snd_azf3328_game_outw(स्थिर काष्ठा snd_azf3328 *chip, अचिन्हित reg, u16 value)
अणु
	outw(value, chip->game_io + reg);
पूर्ण

अटल अंतरभूत u8
snd_azf3328_game_inb(स्थिर काष्ठा snd_azf3328 *chip, अचिन्हित reg)
अणु
	वापस inb(chip->game_io + reg);
पूर्ण

अटल अंतरभूत u16
snd_azf3328_game_inw(स्थिर काष्ठा snd_azf3328 *chip, अचिन्हित reg)
अणु
	वापस inw(chip->game_io + reg);
पूर्ण

अटल अंतरभूत व्योम
snd_azf3328_mixer_outw(स्थिर काष्ठा snd_azf3328 *chip, अचिन्हित reg, u16 value)
अणु
	outw(value, chip->mixer_io + reg);
पूर्ण

अटल अंतरभूत u16
snd_azf3328_mixer_inw(स्थिर काष्ठा snd_azf3328 *chip, अचिन्हित reg)
अणु
	वापस inw(chip->mixer_io + reg);
पूर्ण

#घोषणा AZF_MUTE_BIT 0x80

अटल bool
snd_azf3328_mixer_mute_control(स्थिर काष्ठा snd_azf3328 *chip,
			   अचिन्हित reg, bool करो_mute
)
अणु
	अचिन्हित दीर्घ portbase = chip->mixer_io + reg + 1;
	bool updated;

	/* the mute bit is on the *second* (i.e. right) रेजिस्टर of a
	 * left/right channel setting */
	updated = snd_azf3328_io_reg_setb(portbase, AZF_MUTE_BIT, करो_mute);

	/* indicate whether it was muted beक्रमe */
	वापस (करो_mute) ? !updated : updated;
पूर्ण

अटल अंतरभूत bool
snd_azf3328_mixer_mute_control_master(स्थिर काष्ठा snd_azf3328 *chip,
			   bool करो_mute
)
अणु
	वापस snd_azf3328_mixer_mute_control(
		chip,
		IDX_MIXER_PLAY_MASTER,
		करो_mute
	);
पूर्ण

अटल अंतरभूत bool
snd_azf3328_mixer_mute_control_pcm(स्थिर काष्ठा snd_azf3328 *chip,
			   bool करो_mute
)
अणु
	वापस snd_azf3328_mixer_mute_control(
		chip,
		IDX_MIXER_WAVEOUT,
		करो_mute
	);
पूर्ण

अटल अंतरभूत व्योम
snd_azf3328_mixer_reset(स्थिर काष्ठा snd_azf3328 *chip)
अणु
	/* reset (बंद) mixer:
	 * first mute master volume, then reset
	 */
	snd_azf3328_mixer_mute_control_master(chip, 1);
	snd_azf3328_mixer_outw(chip, IDX_MIXER_RESET, 0x0000);
पूर्ण

#अगर_घोषित AZF_USE_AC97_LAYER

अटल अंतरभूत व्योम
snd_azf3328_mixer_ac97_map_unsupported(स्थिर काष्ठा snd_azf3328 *chip,
				       अचिन्हित लघु reg, स्थिर अक्षर *mode)
अणु
	/* need to add some more or less clever emulation? */
	dev_warn(chip->card->dev,
		"missing %s emulation for AC97 register 0x%02x!\n",
		mode, reg);
पूर्ण

/*
 * Need to have _special_ AC97 mixer hardware रेजिस्टर index mapper,
 * to compensate क्रम the issue of a rather AC97-incompatible hardware layout.
 */
#घोषणा AZF_REG_MASK 0x3f
#घोषणा AZF_AC97_REG_UNSUPPORTED 0x8000
#घोषणा AZF_AC97_REG_REAL_IO_READ 0x4000
#घोषणा AZF_AC97_REG_REAL_IO_WRITE 0x2000
#घोषणा AZF_AC97_REG_REAL_IO_RW \
	(AZF_AC97_REG_REAL_IO_READ | AZF_AC97_REG_REAL_IO_WRITE)
#घोषणा AZF_AC97_REG_EMU_IO_READ 0x0400
#घोषणा AZF_AC97_REG_EMU_IO_WRITE 0x0200
#घोषणा AZF_AC97_REG_EMU_IO_RW \
	(AZF_AC97_REG_EMU_IO_READ | AZF_AC97_REG_EMU_IO_WRITE)
अटल अचिन्हित लघु
snd_azf3328_mixer_ac97_map_reg_idx(अचिन्हित लघु reg)
अणु
	अटल स्थिर काष्ठा अणु
		अचिन्हित लघु azf_reg;
	पूर्ण azf_reg_mapper[] = अणु
		/* Especially when taking पूर्णांकo consideration
		 * mono/stereo-based sequence of azf vs. AC97 control series,
		 * it's quite obvious that azf simply got rid
		 * of the AC97_HEADPHONE control at its पूर्णांकended offset,
		 * thus shअगरted _all_ controls by one,
		 * and _then_ simply added it as an FMSYNTH control at the end,
		 * to make up क्रम the offset.
		 * This means we'll have to translate indices here as
		 * needed and then करो some tiny AC97 patch action
		 * (snd_ac97_नाम_vol_ctl() etc.) - that's it.
		 */
		अणु /* AC97_RESET */ IDX_MIXER_RESET
			| AZF_AC97_REG_REAL_IO_WRITE
			| AZF_AC97_REG_EMU_IO_READ पूर्ण,
		अणु /* AC97_MASTER */ IDX_MIXER_PLAY_MASTER पूर्ण,
		 /* note large shअगरt: AC97_HEADPHONE to IDX_MIXER_FMSYNTH! */
		अणु /* AC97_HEADPHONE */ IDX_MIXER_FMSYNTH पूर्ण,
		अणु /* AC97_MASTER_MONO */ IDX_MIXER_MODEMOUT पूर्ण,
		अणु /* AC97_MASTER_TONE */ IDX_MIXER_BASSTREBLE पूर्ण,
		अणु /* AC97_PC_BEEP */ IDX_MIXER_PCBEEP पूर्ण,
		अणु /* AC97_PHONE */ IDX_MIXER_MODEMIN पूर्ण,
		अणु /* AC97_MIC */ IDX_MIXER_MIC पूर्ण,
		अणु /* AC97_LINE */ IDX_MIXER_LINEIN पूर्ण,
		अणु /* AC97_CD */ IDX_MIXER_CDAUDIO पूर्ण,
		अणु /* AC97_VIDEO */ IDX_MIXER_VIDEO पूर्ण,
		अणु /* AC97_AUX */ IDX_MIXER_AUX पूर्ण,
		अणु /* AC97_PCM */ IDX_MIXER_WAVEOUT पूर्ण,
		अणु /* AC97_REC_SEL */ IDX_MIXER_REC_SELECT पूर्ण,
		अणु /* AC97_REC_GAIN */ IDX_MIXER_REC_VOLUME पूर्ण,
		अणु /* AC97_REC_GAIN_MIC */ AZF_AC97_REG_EMU_IO_RW पूर्ण,
		अणु /* AC97_GENERAL_PURPOSE */ IDX_MIXER_ADVCTL2 पूर्ण,
		अणु /* AC97_3D_CONTROL */ IDX_MIXER_ADVCTL1 पूर्ण,
	पूर्ण;

	अचिन्हित लघु reg_azf = AZF_AC97_REG_UNSUPPORTED;

	/* azf3328 supports the low-numbered and low-spec:ed range
	   of AC97 regs only */
	अगर (reg <= AC97_3D_CONTROL) अणु
		अचिन्हित लघु reg_idx = reg / 2;
		reg_azf = azf_reg_mapper[reg_idx].azf_reg;
		/* a translation-only entry means it's real पढ़ो/ग_लिखो: */
		अगर (!(reg_azf & ~AZF_REG_MASK))
			reg_azf |= AZF_AC97_REG_REAL_IO_RW;
	पूर्ण अन्यथा अणु
		चयन (reg) अणु
		हाल AC97_POWERDOWN:
			reg_azf = AZF_AC97_REG_EMU_IO_RW;
			अवरोध;
		हाल AC97_EXTENDED_ID:
			reg_azf = AZF_AC97_REG_EMU_IO_READ;
			अवरोध;
		हाल AC97_EXTENDED_STATUS:
			/* I करोn't know what the h*ll AC97 layer
			 * would consult this _extended_ रेजिस्टर क्रम
			 * given a base-AC97-advertised card,
			 * but let's just emulate it anyway :-P
			 */
			reg_azf = AZF_AC97_REG_EMU_IO_RW;
			अवरोध;
		हाल AC97_VENDOR_ID1:
		हाल AC97_VENDOR_ID2:
			reg_azf = AZF_AC97_REG_EMU_IO_READ;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस reg_azf;
पूर्ण

अटल स्थिर अचिन्हित लघु
azf_emulated_ac97_caps =
	AC97_BC_DEDICATED_MIC |
	AC97_BC_BASS_TREBLE |
	/* Headphone is an FM Synth control here */
	AC97_BC_HEADPHONE |
	/* no AC97_BC_LOUDNESS! */
	/* mask 0x7c00 is
	   venकरोr-specअगरic 3D enhancement
	   venकरोr indicator.
	   Since there actually _is_ an
	   entry क्रम Aztech Lअसल
	   (13), make damn sure
	   to indicate it. */
	(13 << 10);

अटल स्थिर अचिन्हित लघु
azf_emulated_ac97_घातerकरोwn =
	/* pretend everything to be active */
		AC97_PD_ADC_STATUS |
		AC97_PD_DAC_STATUS |
		AC97_PD_MIXER_STATUS |
		AC97_PD_VREF_STATUS;

/*
 * Emulated, _inofficial_ venकरोr ID
 * (there might be some devices such as the MR 2800-W
 * which could reveal the real Aztech AC97 ID).
 * We choose to use "AZT" prefix, and then use 1 to indicate PCI168
 * (better करोn't use 0x68 since there's a PCI368 as well).
 */
अटल स्थिर अचिन्हित पूर्णांक
azf_emulated_ac97_venकरोr_id = 0x415a5401;

अटल अचिन्हित लघु
snd_azf3328_mixer_ac97_पढ़ो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg_ac97)
अणु
	स्थिर काष्ठा snd_azf3328 *chip = ac97->निजी_data;
	अचिन्हित लघु reg_azf = snd_azf3328_mixer_ac97_map_reg_idx(reg_ac97);
	अचिन्हित लघु reg_val = 0;
	bool unsupported = false;

	dev_dbg(chip->card->dev, "snd_azf3328_mixer_ac97_read reg_ac97 %u\n",
		reg_ac97);
	अगर (reg_azf & AZF_AC97_REG_UNSUPPORTED)
		unsupported = true;
	अन्यथा अणु
		अगर (reg_azf & AZF_AC97_REG_REAL_IO_READ)
			reg_val = snd_azf3328_mixer_inw(chip,
						reg_azf & AZF_REG_MASK);
		अन्यथा अणु
			/*
			 * Proceed with dummy I/O पढ़ो,
			 * to ensure compatible timing where this may matter.
			 * (ALSA AC97 layer usually करोesn't call I/O functions
			 * due to पूर्णांकelligent I/O caching anyway)
			 * Choose a mixer रेजिस्टर that's thoroughly unrelated
			 * to common audio (try to minimize distortion).
			 */
			snd_azf3328_mixer_inw(chip, IDX_MIXER_SOMETHING30H);
		पूर्ण

		अगर (reg_azf & AZF_AC97_REG_EMU_IO_READ) अणु
			चयन (reg_ac97) अणु
			हाल AC97_RESET:
				reg_val |= azf_emulated_ac97_caps;
				अवरोध;
			हाल AC97_POWERDOWN:
				reg_val |= azf_emulated_ac97_घातerकरोwn;
				अवरोध;
			हाल AC97_EXTENDED_ID:
			हाल AC97_EXTENDED_STATUS:
				/* AFAICS we simply can't support anything: */
				reg_val |= 0;
				अवरोध;
			हाल AC97_VENDOR_ID1:
				reg_val = azf_emulated_ac97_venकरोr_id >> 16;
				अवरोध;
			हाल AC97_VENDOR_ID2:
				reg_val = azf_emulated_ac97_venकरोr_id & 0xffff;
				अवरोध;
			शेष:
				unsupported = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (unsupported)
		snd_azf3328_mixer_ac97_map_unsupported(chip, reg_ac97, "read");

	वापस reg_val;
पूर्ण

अटल व्योम
snd_azf3328_mixer_ac97_ग_लिखो(काष्ठा snd_ac97 *ac97,
		     अचिन्हित लघु reg_ac97, अचिन्हित लघु val)
अणु
	स्थिर काष्ठा snd_azf3328 *chip = ac97->निजी_data;
	अचिन्हित लघु reg_azf = snd_azf3328_mixer_ac97_map_reg_idx(reg_ac97);
	bool unsupported = false;

	dev_dbg(chip->card->dev,
		"snd_azf3328_mixer_ac97_write reg_ac97 %u val %u\n",
		reg_ac97, val);
	अगर (reg_azf & AZF_AC97_REG_UNSUPPORTED)
		unsupported = true;
	अन्यथा अणु
		अगर (reg_azf & AZF_AC97_REG_REAL_IO_WRITE)
			snd_azf3328_mixer_outw(
				chip,
				reg_azf & AZF_REG_MASK,
				val
			);
		अन्यथा
		अगर (reg_azf & AZF_AC97_REG_EMU_IO_WRITE) अणु
			चयन (reg_ac97) अणु
			हाल AC97_REC_GAIN_MIC:
			हाल AC97_POWERDOWN:
			हाल AC97_EXTENDED_STATUS:
				/*
				 * Silently swallow these ग_लिखोs.
				 * Since क्रम most रेजिस्टरs our card करोesn't
				 * actually support a comparable feature,
				 * this is exactly what we should करो here.
				 * The AC97 layer's I/O caching probably
				 * स्वतःmatically takes care of all the rest...
				 * (remembers written values etc.)
				 */
				अवरोध;
			शेष:
				unsupported = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (unsupported)
		snd_azf3328_mixer_ac97_map_unsupported(chip, reg_ac97, "write");
पूर्ण

अटल पूर्णांक
snd_azf3328_mixer_new(काष्ठा snd_azf3328 *chip)
अणु
	काष्ठा snd_ac97_bus *bus;
	काष्ठा snd_ac97_ढाँचा ac97;
	अटल स्थिर काष्ठा snd_ac97_bus_ops ops = अणु
		.ग_लिखो = snd_azf3328_mixer_ac97_ग_लिखो,
		.पढ़ो = snd_azf3328_mixer_ac97_पढ़ो,
	पूर्ण;
	पूर्णांक rc;

	स_रखो(&ac97, 0, माप(ac97));
	ac97.scaps = AC97_SCAP_SKIP_MODEM
			| AC97_SCAP_AUDIO /* we support audio! */
			| AC97_SCAP_NO_SPDIF;
	ac97.निजी_data = chip;
	ac97.pci = chip->pci;

	/*
	 * ALSA's AC97 layer has terrible init crackling issues,
	 * unक्रमtunately, and since it makes use of AC97_RESET,
	 * there's no use trying to mute Master Playback proactively.
	 */

	rc = snd_ac97_bus(chip->card, 0, &ops, शून्य, &bus);
	अगर (!rc)
		rc = snd_ac97_mixer(bus, &ac97, &chip->ac97);
		/*
		 * Make sure to complain loudly in हाल of AC97 init failure,
		 * since failure may happen quite often,
		 * due to this card being a very quirky AC97 "lookalike".
		 */
	अगर (rc)
		dev_err(chip->card->dev, "AC97 init failed, err %d!\n", rc);

	/* If we वापस an error here, then snd_card_मुक्त() should
	 * मुक्त up any ac97 codecs that got created, as well as the bus.
	 */
	वापस rc;
पूर्ण
#अन्यथा /* AZF_USE_AC97_LAYER */
अटल व्योम
snd_azf3328_mixer_ग_लिखो_volume_gradually(स्थिर काष्ठा snd_azf3328 *chip,
					 अचिन्हित reg,
					 अचिन्हित अक्षर dst_vol_left,
					 अचिन्हित अक्षर dst_vol_right,
					 पूर्णांक chan_sel, पूर्णांक delay
)
अणु
	अचिन्हित दीर्घ portbase = chip->mixer_io + reg;
	अचिन्हित अक्षर curr_vol_left = 0, curr_vol_right = 0;
	पूर्णांक left_change = 0, right_change = 0;

	अगर (chan_sel & SET_CHAN_LEFT) अणु
		curr_vol_left  = inb(portbase + 1);

		/* take care of muting flag contained in left channel */
		अगर (curr_vol_left & AZF_MUTE_BIT)
			dst_vol_left |= AZF_MUTE_BIT;
		अन्यथा
			dst_vol_left &= ~AZF_MUTE_BIT;

		left_change = (curr_vol_left > dst_vol_left) ? -1 : 1;
	पूर्ण

	अगर (chan_sel & SET_CHAN_RIGHT) अणु
		curr_vol_right = inb(portbase + 0);

		right_change = (curr_vol_right > dst_vol_right) ? -1 : 1;
	पूर्ण

	करो अणु
		अगर (left_change) अणु
			अगर (curr_vol_left != dst_vol_left) अणु
				curr_vol_left += left_change;
				outb(curr_vol_left, portbase + 1);
			पूर्ण अन्यथा
			    left_change = 0;
		पूर्ण
		अगर (right_change) अणु
			अगर (curr_vol_right != dst_vol_right) अणु
				curr_vol_right += right_change;

			/* during volume change, the right channel is crackling
			 * somewhat more than the left channel, unक्रमtunately.
			 * This seems to be a hardware issue. */
				outb(curr_vol_right, portbase + 0);
			पूर्ण अन्यथा
			    right_change = 0;
		पूर्ण
		अगर (delay)
			mdelay(delay);
	पूर्ण जबतक ((left_change) || (right_change));
पूर्ण

/*
 * general mixer element
 */
काष्ठा azf3328_mixer_reg अणु
	अचिन्हित reg;
	अचिन्हित पूर्णांक lchan_shअगरt, rchan_shअगरt;
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक invert: 1;
	अचिन्हित पूर्णांक stereo: 1;
	अचिन्हित पूर्णांक क्रमागत_c: 4;
पूर्ण;

#घोषणा COMPOSE_MIXER_REG(reg,lchan_shअगरt,rchan_shअगरt,mask,invert,stereo,क्रमागत_c) \
 ((reg) | (lchan_shअगरt << 8) | (rchan_shअगरt << 12) | \
  (mask << 16) | \
  (invert << 24) | \
  (stereo << 25) | \
  (क्रमागत_c << 26))

अटल व्योम snd_azf3328_mixer_reg_decode(काष्ठा azf3328_mixer_reg *r, अचिन्हित दीर्घ val)
अणु
	r->reg = val & 0xff;
	r->lchan_shअगरt = (val >> 8) & 0x0f;
	r->rchan_shअगरt = (val >> 12) & 0x0f;
	r->mask = (val >> 16) & 0xff;
	r->invert = (val >> 24) & 1;
	r->stereo = (val >> 25) & 1;
	r->क्रमागत_c = (val >> 26) & 0x0f;
पूर्ण

/*
 * mixer चयनes/volumes
 */

#घोषणा AZF3328_MIXER_SWITCH(xname, reg, shअगरt, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
  .info = snd_azf3328_info_mixer, \
  .get = snd_azf3328_get_mixer, .put = snd_azf3328_put_mixer, \
  .निजी_value = COMPOSE_MIXER_REG(reg, shअगरt, 0, 0x1, invert, 0, 0), \
पूर्ण

#घोषणा AZF3328_MIXER_VOL_STEREO(xname, reg, mask, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
  .info = snd_azf3328_info_mixer, \
  .get = snd_azf3328_get_mixer, .put = snd_azf3328_put_mixer, \
  .निजी_value = COMPOSE_MIXER_REG(reg, 8, 0, mask, invert, 1, 0), \
पूर्ण

#घोषणा AZF3328_MIXER_VOL_MONO(xname, reg, mask, is_right_chan) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
  .info = snd_azf3328_info_mixer, \
  .get = snd_azf3328_get_mixer, .put = snd_azf3328_put_mixer, \
  .निजी_value = COMPOSE_MIXER_REG(reg, is_right_chan ? 0 : 8, 0, mask, 1, 0, 0), \
पूर्ण

#घोषणा AZF3328_MIXER_VOL_SPECIAL(xname, reg, mask, shअगरt, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
  .info = snd_azf3328_info_mixer, \
  .get = snd_azf3328_get_mixer, .put = snd_azf3328_put_mixer, \
  .निजी_value = COMPOSE_MIXER_REG(reg, shअगरt, 0, mask, invert, 0, 0), \
पूर्ण

#घोषणा AZF3328_MIXER_ENUM(xname, reg, क्रमागत_c, shअगरt) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
  .info = snd_azf3328_info_mixer_क्रमागत, \
  .get = snd_azf3328_get_mixer_क्रमागत, .put = snd_azf3328_put_mixer_क्रमागत, \
  .निजी_value = COMPOSE_MIXER_REG(reg, shअगरt, 0, 0, 0, 0, क्रमागत_c), \
पूर्ण

अटल पूर्णांक
snd_azf3328_info_mixer(काष्ठा snd_kcontrol *kcontrol,
		       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा azf3328_mixer_reg reg;

	snd_azf3328_mixer_reg_decode(&reg, kcontrol->निजी_value);
	uinfo->type = reg.mask == 1 ?
		SNDRV_CTL_ELEM_TYPE_BOOLEAN : SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = reg.stereo + 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = reg.mask;
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_azf3328_get_mixer(काष्ठा snd_kcontrol *kcontrol,
		      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_azf3328 *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा azf3328_mixer_reg reg;
	u16 oreg, val;

	snd_azf3328_mixer_reg_decode(&reg, kcontrol->निजी_value);

	oreg = snd_azf3328_mixer_inw(chip, reg.reg);
	val = (oreg >> reg.lchan_shअगरt) & reg.mask;
	अगर (reg.invert)
		val = reg.mask - val;
	ucontrol->value.पूर्णांकeger.value[0] = val;
	अगर (reg.stereo) अणु
		val = (oreg >> reg.rchan_shअगरt) & reg.mask;
		अगर (reg.invert)
			val = reg.mask - val;
		ucontrol->value.पूर्णांकeger.value[1] = val;
	पूर्ण
	dev_dbg(chip->card->dev,
		"get: %02x is %04x -> vol %02lx|%02lx (shift %02d|%02d, mask %02x, inv. %d, stereo %d)\n",
		reg.reg, oreg,
		ucontrol->value.पूर्णांकeger.value[0], ucontrol->value.पूर्णांकeger.value[1],
		reg.lchan_shअगरt, reg.rchan_shअगरt, reg.mask, reg.invert, reg.stereo);
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_azf3328_put_mixer(काष्ठा snd_kcontrol *kcontrol,
		      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_azf3328 *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा azf3328_mixer_reg reg;
	u16 oreg, nreg, val;

	snd_azf3328_mixer_reg_decode(&reg, kcontrol->निजी_value);
	oreg = snd_azf3328_mixer_inw(chip, reg.reg);
	val = ucontrol->value.पूर्णांकeger.value[0] & reg.mask;
	अगर (reg.invert)
		val = reg.mask - val;
	nreg = oreg & ~(reg.mask << reg.lchan_shअगरt);
	nreg |= (val << reg.lchan_shअगरt);
	अगर (reg.stereo) अणु
		val = ucontrol->value.पूर्णांकeger.value[1] & reg.mask;
		अगर (reg.invert)
			val = reg.mask - val;
		nreg &= ~(reg.mask << reg.rchan_shअगरt);
		nreg |= (val << reg.rchan_shअगरt);
	पूर्ण
	अगर (reg.mask >= 0x07) /* it's a volume control, so better take care */
		snd_azf3328_mixer_ग_लिखो_volume_gradually(
			chip, reg.reg, nreg >> 8, nreg & 0xff,
			/* just set both channels, करोesn't matter */
			SET_CHAN_LEFT|SET_CHAN_RIGHT,
			0);
	अन्यथा
        	snd_azf3328_mixer_outw(chip, reg.reg, nreg);

	dev_dbg(chip->card->dev,
		"put: %02x to %02lx|%02lx, oreg %04x; shift %02d|%02d -> nreg %04x; after: %04x\n",
		reg.reg, ucontrol->value.पूर्णांकeger.value[0], ucontrol->value.पूर्णांकeger.value[1],
		oreg, reg.lchan_shअगरt, reg.rchan_shअगरt,
		nreg, snd_azf3328_mixer_inw(chip, reg.reg));
	वापस (nreg != oreg);
पूर्ण

अटल पूर्णांक
snd_azf3328_info_mixer_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts1[] = अणु
		"Mic1", "Mic2"
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर texts2[] = अणु
		"Mix", "Mic"
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर texts3[] = अणु
		"Mic", "CD", "Video", "Aux",
		"Line", "Mix", "Mix Mono", "Phone"
        पूर्ण;
	अटल स्थिर अक्षर * स्थिर texts4[] = अणु
		"pre 3D", "post 3D"
        पूर्ण;
	काष्ठा azf3328_mixer_reg reg;
	स्थिर अक्षर * स्थिर *p = शून्य;

	snd_azf3328_mixer_reg_decode(&reg, kcontrol->निजी_value);
	अगर (reg.reg == IDX_MIXER_ADVCTL2) अणु
		चयन(reg.lchan_shअगरt) अणु
		हाल 8: /* modem out sel */
			p = texts1;
			अवरोध;
		हाल 9: /* mono sel source */
			p = texts2;
			अवरोध;
		हाल 15: /* PCM Out Path */
			p = texts4;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (reg.reg == IDX_MIXER_REC_SELECT)
		p = texts3;

	वापस snd_ctl_क्रमागत_info(uinfo,
				 (reg.reg == IDX_MIXER_REC_SELECT) ? 2 : 1,
				 reg.क्रमागत_c, p);
पूर्ण

अटल पूर्णांक
snd_azf3328_get_mixer_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
        काष्ठा snd_azf3328 *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा azf3328_mixer_reg reg;
        अचिन्हित लघु val;

	snd_azf3328_mixer_reg_decode(&reg, kcontrol->निजी_value);
	val = snd_azf3328_mixer_inw(chip, reg.reg);
	अगर (reg.reg == IDX_MIXER_REC_SELECT) अणु
        	ucontrol->value.क्रमागतerated.item[0] = (val >> 8) & (reg.क्रमागत_c - 1);
        	ucontrol->value.क्रमागतerated.item[1] = (val >> 0) & (reg.क्रमागत_c - 1);
	पूर्ण अन्यथा
        	ucontrol->value.क्रमागतerated.item[0] = (val >> reg.lchan_shअगरt) & (reg.क्रमागत_c - 1);

	dev_dbg(chip->card->dev,
		"get_enum: %02x is %04x -> %d|%d (shift %02d, enum_c %d)\n",
		reg.reg, val, ucontrol->value.क्रमागतerated.item[0], ucontrol->value.क्रमागतerated.item[1],
		reg.lchan_shअगरt, reg.क्रमागत_c);
        वापस 0;
पूर्ण

अटल पूर्णांक
snd_azf3328_put_mixer_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
        काष्ठा snd_azf3328 *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा azf3328_mixer_reg reg;
	u16 oreg, nreg, val;

	snd_azf3328_mixer_reg_decode(&reg, kcontrol->निजी_value);
	oreg = snd_azf3328_mixer_inw(chip, reg.reg);
	val = oreg;
	अगर (reg.reg == IDX_MIXER_REC_SELECT) अणु
        	अगर (ucontrol->value.क्रमागतerated.item[0] > reg.क्रमागत_c - 1U ||
            	ucontrol->value.क्रमागतerated.item[1] > reg.क्रमागत_c - 1U)
                	वापस -EINVAL;
        	val = (ucontrol->value.क्रमागतerated.item[0] << 8) |
        	      (ucontrol->value.क्रमागतerated.item[1] << 0);
	पूर्ण अन्यथा अणु
        	अगर (ucontrol->value.क्रमागतerated.item[0] > reg.क्रमागत_c - 1U)
                	वापस -EINVAL;
		val &= ~((reg.क्रमागत_c - 1) << reg.lchan_shअगरt);
        	val |= (ucontrol->value.क्रमागतerated.item[0] << reg.lchan_shअगरt);
	पूर्ण
	snd_azf3328_mixer_outw(chip, reg.reg, val);
	nreg = val;

	dev_dbg(chip->card->dev,
		"put_enum: %02x to %04x, oreg %04x\n", reg.reg, val, oreg);
	वापस (nreg != oreg);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_azf3328_mixer_controls[] = अणु
	AZF3328_MIXER_SWITCH("Master Playback Switch", IDX_MIXER_PLAY_MASTER, 15, 1),
	AZF3328_MIXER_VOL_STEREO("Master Playback Volume", IDX_MIXER_PLAY_MASTER, 0x1f, 1),
	AZF3328_MIXER_SWITCH("PCM Playback Switch", IDX_MIXER_WAVEOUT, 15, 1),
	AZF3328_MIXER_VOL_STEREO("PCM Playback Volume",
					IDX_MIXER_WAVEOUT, 0x1f, 1),
	AZF3328_MIXER_SWITCH("PCM 3D Bypass Playback Switch",
					IDX_MIXER_ADVCTL2, 7, 1),
	AZF3328_MIXER_SWITCH("FM Playback Switch", IDX_MIXER_FMSYNTH, 15, 1),
	AZF3328_MIXER_VOL_STEREO("FM Playback Volume", IDX_MIXER_FMSYNTH, 0x1f, 1),
	AZF3328_MIXER_SWITCH("CD Playback Switch", IDX_MIXER_CDAUDIO, 15, 1),
	AZF3328_MIXER_VOL_STEREO("CD Playback Volume", IDX_MIXER_CDAUDIO, 0x1f, 1),
	AZF3328_MIXER_SWITCH("Capture Switch", IDX_MIXER_REC_VOLUME, 15, 1),
	AZF3328_MIXER_VOL_STEREO("Capture Volume", IDX_MIXER_REC_VOLUME, 0x0f, 0),
	AZF3328_MIXER_ENUM("Capture Source", IDX_MIXER_REC_SELECT, 8, 0),
	AZF3328_MIXER_SWITCH("Mic Playback Switch", IDX_MIXER_MIC, 15, 1),
	AZF3328_MIXER_VOL_MONO("Mic Playback Volume", IDX_MIXER_MIC, 0x1f, 1),
	AZF3328_MIXER_SWITCH("Mic Boost (+20dB)", IDX_MIXER_MIC, 6, 0),
	AZF3328_MIXER_SWITCH("Line Playback Switch", IDX_MIXER_LINEIN, 15, 1),
	AZF3328_MIXER_VOL_STEREO("Line Playback Volume", IDX_MIXER_LINEIN, 0x1f, 1),
	AZF3328_MIXER_SWITCH("Beep Playback Switch", IDX_MIXER_PCBEEP, 15, 1),
	AZF3328_MIXER_VOL_SPECIAL("Beep Playback Volume", IDX_MIXER_PCBEEP, 0x0f, 1, 1),
	AZF3328_MIXER_SWITCH("Video Playback Switch", IDX_MIXER_VIDEO, 15, 1),
	AZF3328_MIXER_VOL_STEREO("Video Playback Volume", IDX_MIXER_VIDEO, 0x1f, 1),
	AZF3328_MIXER_SWITCH("Aux Playback Switch", IDX_MIXER_AUX, 15, 1),
	AZF3328_MIXER_VOL_STEREO("Aux Playback Volume", IDX_MIXER_AUX, 0x1f, 1),
	AZF3328_MIXER_SWITCH("Modem Playback Switch", IDX_MIXER_MODEMOUT, 15, 1),
	AZF3328_MIXER_VOL_MONO("Modem Playback Volume", IDX_MIXER_MODEMOUT, 0x1f, 1),
	AZF3328_MIXER_SWITCH("Modem Capture Switch", IDX_MIXER_MODEMIN, 15, 1),
	AZF3328_MIXER_VOL_MONO("Modem Capture Volume", IDX_MIXER_MODEMIN, 0x1f, 1),
	AZF3328_MIXER_ENUM("Mic Select", IDX_MIXER_ADVCTL2, 2, 8),
	AZF3328_MIXER_ENUM("Mono Output Select", IDX_MIXER_ADVCTL2, 2, 9),
	AZF3328_MIXER_ENUM("PCM Output Route", IDX_MIXER_ADVCTL2, 2, 15), /* PCM Out Path, place in front since it controls *both* 3D and Bass/Treble! */
	AZF3328_MIXER_VOL_SPECIAL("Tone Control - Treble", IDX_MIXER_BASSTREBLE, 0x07, 1, 0),
	AZF3328_MIXER_VOL_SPECIAL("Tone Control - Bass", IDX_MIXER_BASSTREBLE, 0x07, 9, 0),
	AZF3328_MIXER_SWITCH("3D Control - Switch", IDX_MIXER_ADVCTL2, 13, 0),
	AZF3328_MIXER_VOL_SPECIAL("3D Control - Width", IDX_MIXER_ADVCTL1, 0x07, 1, 0), /* "3D Width" */
	AZF3328_MIXER_VOL_SPECIAL("3D Control - Depth", IDX_MIXER_ADVCTL1, 0x03, 8, 0), /* "Hifi 3D" */
#अगर MIXER_TESTING
	AZF3328_MIXER_SWITCH("0", IDX_MIXER_ADVCTL2, 0, 0),
	AZF3328_MIXER_SWITCH("1", IDX_MIXER_ADVCTL2, 1, 0),
	AZF3328_MIXER_SWITCH("2", IDX_MIXER_ADVCTL2, 2, 0),
	AZF3328_MIXER_SWITCH("3", IDX_MIXER_ADVCTL2, 3, 0),
	AZF3328_MIXER_SWITCH("4", IDX_MIXER_ADVCTL2, 4, 0),
	AZF3328_MIXER_SWITCH("5", IDX_MIXER_ADVCTL2, 5, 0),
	AZF3328_MIXER_SWITCH("6", IDX_MIXER_ADVCTL2, 6, 0),
	AZF3328_MIXER_SWITCH("7", IDX_MIXER_ADVCTL2, 7, 0),
	AZF3328_MIXER_SWITCH("8", IDX_MIXER_ADVCTL2, 8, 0),
	AZF3328_MIXER_SWITCH("9", IDX_MIXER_ADVCTL2, 9, 0),
	AZF3328_MIXER_SWITCH("10", IDX_MIXER_ADVCTL2, 10, 0),
	AZF3328_MIXER_SWITCH("11", IDX_MIXER_ADVCTL2, 11, 0),
	AZF3328_MIXER_SWITCH("12", IDX_MIXER_ADVCTL2, 12, 0),
	AZF3328_MIXER_SWITCH("13", IDX_MIXER_ADVCTL2, 13, 0),
	AZF3328_MIXER_SWITCH("14", IDX_MIXER_ADVCTL2, 14, 0),
	AZF3328_MIXER_SWITCH("15", IDX_MIXER_ADVCTL2, 15, 0),
#पूर्ण_अगर
पूर्ण;

अटल स्थिर u16 snd_azf3328_init_values[][2] = अणु
        अणु IDX_MIXER_PLAY_MASTER,	MIXER_MUTE_MASK|0x1f1f पूर्ण,
        अणु IDX_MIXER_MODEMOUT,		MIXER_MUTE_MASK|0x1f1f पूर्ण,
	अणु IDX_MIXER_BASSTREBLE,		0x0000 पूर्ण,
	अणु IDX_MIXER_PCBEEP,		MIXER_MUTE_MASK|0x1f1f पूर्ण,
	अणु IDX_MIXER_MODEMIN,		MIXER_MUTE_MASK|0x1f1f पूर्ण,
	अणु IDX_MIXER_MIC,		MIXER_MUTE_MASK|0x001f पूर्ण,
	अणु IDX_MIXER_LINEIN,		MIXER_MUTE_MASK|0x1f1f पूर्ण,
	अणु IDX_MIXER_CDAUDIO,		MIXER_MUTE_MASK|0x1f1f पूर्ण,
	अणु IDX_MIXER_VIDEO,		MIXER_MUTE_MASK|0x1f1f पूर्ण,
	अणु IDX_MIXER_AUX,		MIXER_MUTE_MASK|0x1f1f पूर्ण,
        अणु IDX_MIXER_WAVEOUT,		MIXER_MUTE_MASK|0x1f1f पूर्ण,
        अणु IDX_MIXER_FMSYNTH,		MIXER_MUTE_MASK|0x1f1f पूर्ण,
        अणु IDX_MIXER_REC_VOLUME,		MIXER_MUTE_MASK|0x0707 पूर्ण,
पूर्ण;

अटल पूर्णांक
snd_azf3328_mixer_new(काष्ठा snd_azf3328 *chip)
अणु
	काष्ठा snd_card *card;
	स्थिर काष्ठा snd_kcontrol_new *sw;
	अचिन्हित पूर्णांक idx;
	पूर्णांक err;

	अगर (snd_BUG_ON(!chip || !chip->card))
		वापस -EINVAL;

	card = chip->card;

	/* mixer reset */
	snd_azf3328_mixer_outw(chip, IDX_MIXER_RESET, 0x0000);

	/* mute and zero volume channels */
	क्रम (idx = 0; idx < ARRAY_SIZE(snd_azf3328_init_values); ++idx) अणु
		snd_azf3328_mixer_outw(chip,
			snd_azf3328_init_values[idx][0],
			snd_azf3328_init_values[idx][1]);
	पूर्ण

	/* add mixer controls */
	sw = snd_azf3328_mixer_controls;
	क्रम (idx = 0; idx < ARRAY_SIZE(snd_azf3328_mixer_controls);
			++idx, ++sw) अणु
		अगर ((err = snd_ctl_add(chip->card, snd_ctl_new1(sw, chip))) < 0)
			वापस err;
	पूर्ण
	snd_component_add(card, "AZF3328 mixer");
	म_नकल(card->mixername, "AZF3328 mixer");

	वापस 0;
पूर्ण
#पूर्ण_अगर /* AZF_USE_AC97_LAYER */

अटल व्योम
snd_azf3328_codec_setfmt(काष्ठा snd_azf3328_codec_data *codec,
			       क्रमागत azf_freq_t bitrate,
			       अचिन्हित पूर्णांक क्रमmat_width,
			       अचिन्हित पूर्णांक channels
)
अणु
	अचिन्हित दीर्घ flags;
	u16 val = 0xff00;
	u8 freq = 0;

	चयन (bitrate) अणु
	हाल AZF_FREQ_4000:  freq = SOUNDFORMAT_FREQ_SUSPECTED_4000; अवरोध;
	हाल AZF_FREQ_4800:  freq = SOUNDFORMAT_FREQ_SUSPECTED_4800; अवरोध;
	हाल AZF_FREQ_5512:
		/* the AZF3328 names it "5510" क्रम some strange reason */
			     freq = SOUNDFORMAT_FREQ_5510; अवरोध;
	हाल AZF_FREQ_6620:  freq = SOUNDFORMAT_FREQ_6620; अवरोध;
	हाल AZF_FREQ_8000:  freq = SOUNDFORMAT_FREQ_8000; अवरोध;
	हाल AZF_FREQ_9600:  freq = SOUNDFORMAT_FREQ_9600; अवरोध;
	हाल AZF_FREQ_11025: freq = SOUNDFORMAT_FREQ_11025; अवरोध;
	हाल AZF_FREQ_13240: freq = SOUNDFORMAT_FREQ_SUSPECTED_13240; अवरोध;
	हाल AZF_FREQ_16000: freq = SOUNDFORMAT_FREQ_16000; अवरोध;
	हाल AZF_FREQ_22050: freq = SOUNDFORMAT_FREQ_22050; अवरोध;
	हाल AZF_FREQ_32000: freq = SOUNDFORMAT_FREQ_32000; अवरोध;
	शेष:
		snd_prपूर्णांकk(KERN_WARNING "unknown bitrate %d, assuming 44.1kHz!\n", bitrate);
		fallthrough;
	हाल AZF_FREQ_44100: freq = SOUNDFORMAT_FREQ_44100; अवरोध;
	हाल AZF_FREQ_48000: freq = SOUNDFORMAT_FREQ_48000; अवरोध;
	हाल AZF_FREQ_66200: freq = SOUNDFORMAT_FREQ_SUSPECTED_66200; अवरोध;
	पूर्ण
	/* val = 0xff07; 3m27.993s (65301Hz; -> 64000Hz???) hmm, 66120, 65967, 66123 */
	/* val = 0xff09; 17m15.098s (13123,478Hz; -> 12000Hz???) hmm, 13237.2Hz? */
	/* val = 0xff0a; 47m30.599s (4764,891Hz; -> 4800Hz???) yup, 4803Hz */
	/* val = 0xff0c; 57m0.510s (4010,263Hz; -> 4000Hz???) yup, 4003Hz */
	/* val = 0xff05; 5m11.556s (... -> 44100Hz) */
	/* val = 0xff03; 10m21.529s (21872,463Hz; -> 22050Hz???) */
	/* val = 0xff0f; 20m41.883s (10937,993Hz; -> 11025Hz???) */
	/* val = 0xff0d; 41m23.135s (5523,600Hz; -> 5512Hz???) */
	/* val = 0xff0e; 28m30.777s (8017Hz; -> 8000Hz???) */

	val |= freq;

	अगर (channels == 2)
		val |= SOUNDFORMAT_FLAG_2CHANNELS;

	अगर (क्रमmat_width == 16)
		val |= SOUNDFORMAT_FLAG_16BIT;

	spin_lock_irqsave(codec->lock, flags);

	/* set bitrate/क्रमmat */
	snd_azf3328_codec_outw(codec, IDX_IO_CODEC_SOUNDFORMAT, val);

	/* changing the bitrate/क्रमmat settings चयनes off the
	 * audio output with an annoying click in हाल of 8/16bit क्रमmat change
	 * (maybe shutting करोwn DAC/ADC?), thus immediately
	 * करो some tweaking to reenable it and get rid of the clicking
	 * (FIXME: yes, it works, but what exactly am I करोing here?? :)
	 * FIXME: करोes this have some side effects क्रम full-duplex
	 * or other dramatic side effects? */
	/* करो it क्रम non-capture codecs only */
	अगर (codec->type != AZF_CODEC_CAPTURE)
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS,
			snd_azf3328_codec_inw(codec, IDX_IO_CODEC_DMA_FLAGS) |
			DMA_RUN_SOMETHING1 |
			DMA_RUN_SOMETHING2 |
			SOMETHING_ALMOST_ALWAYS_SET |
			DMA_EPILOGUE_SOMETHING |
			DMA_SOMETHING_ELSE
		);

	spin_unlock_irqrestore(codec->lock, flags);
पूर्ण

अटल अंतरभूत व्योम
snd_azf3328_codec_setfmt_lowघातer(काष्ठा snd_azf3328_codec_data *codec
)
अणु
	/* choose lowest frequency क्रम low घातer consumption.
	 * While this will cause louder noise due to rather coarse frequency,
	 * it should never matter since output should always
	 * get disabled properly when idle anyway. */
	snd_azf3328_codec_setfmt(codec, AZF_FREQ_4000, 8, 1);
पूर्ण

अटल व्योम
snd_azf3328_ctrl_reg_6AH_update(काष्ठा snd_azf3328 *chip,
					अचिन्हित biपंचांगask,
					bool enable
)
अणु
	bool करो_mask = !enable;
	अगर (करो_mask)
		chip->shaकरोw_reg_ctrl_6AH |= biपंचांगask;
	अन्यथा
		chip->shaकरोw_reg_ctrl_6AH &= ~biपंचांगask;
	dev_dbg(chip->card->dev,
		"6AH_update mask 0x%04x do_mask %d: val 0x%04x\n",
		biपंचांगask, करो_mask, chip->shaकरोw_reg_ctrl_6AH);
	snd_azf3328_ctrl_outw(chip, IDX_IO_6AH, chip->shaकरोw_reg_ctrl_6AH);
पूर्ण

अटल अंतरभूत व्योम
snd_azf3328_ctrl_enable_codecs(काष्ठा snd_azf3328 *chip, bool enable)
अणु
	dev_dbg(chip->card->dev, "codec_enable %d\n", enable);
	/* no idea what exactly is being करोne here, but I strongly assume it's
	 * PM related */
	snd_azf3328_ctrl_reg_6AH_update(
		chip, IO_6A_PAUSE_PLAYBACK_BIT8, enable
	);
पूर्ण

अटल व्योम
snd_azf3328_ctrl_codec_activity(काष्ठा snd_azf3328 *chip,
				क्रमागत snd_azf3328_codec_type codec_type,
				bool enable
)
अणु
	काष्ठा snd_azf3328_codec_data *codec = &chip->codecs[codec_type];
	bool need_change = (codec->running != enable);

	dev_dbg(chip->card->dev,
		"codec_activity: %s codec, enable %d, need_change %d\n",
				codec->name, enable, need_change
	);
	अगर (need_change) अणु
		अटल स्थिर काष्ठा अणु
			क्रमागत snd_azf3328_codec_type other1;
			क्रमागत snd_azf3328_codec_type other2;
		पूर्ण peer_codecs[3] =
			अणु अणु AZF_CODEC_CAPTURE, AZF_CODEC_I2S_OUT पूर्ण,
			  अणु AZF_CODEC_PLAYBACK, AZF_CODEC_I2S_OUT पूर्ण,
			  अणु AZF_CODEC_PLAYBACK, AZF_CODEC_CAPTURE पूर्ण पूर्ण;
		bool call_function;

		अगर (enable)
			/* अगर enable codec, call enable_codecs func
			   to enable codec supply... */
			call_function = 1;
		अन्यथा अणु
			/* ...otherwise call enable_codecs func
			   (which globally shuts करोwn operation of codecs)
			   only in हाल the other codecs are currently
			   not active either! */
			call_function =
				((!chip->codecs[peer_codecs[codec_type].other1]
					.running)
			     &&  (!chip->codecs[peer_codecs[codec_type].other2]
					.running));
		पूर्ण
		अगर (call_function)
			snd_azf3328_ctrl_enable_codecs(chip, enable);

		/* ...and adjust घड़ी, too
		 * (reduce noise and घातer consumption) */
		अगर (!enable)
			snd_azf3328_codec_setfmt_lowघातer(codec);
		codec->running = enable;
	पूर्ण
पूर्ण

अटल व्योम
snd_azf3328_codec_setdmaa(काष्ठा snd_azf3328 *chip,
			  काष्ठा snd_azf3328_codec_data *codec,
			  अचिन्हित दीर्घ addr,
			  अचिन्हित पूर्णांक period_bytes,
			  अचिन्हित पूर्णांक buffer_bytes
)
अणु
	WARN_ONCE(period_bytes & 1, "odd period length!?\n");
	WARN_ONCE(buffer_bytes != 2 * period_bytes,
		 "missed our input expectations! %u vs. %u\n",
		 buffer_bytes, period_bytes);
	अगर (!codec->running) अणु
		/* AZF3328 uses a two buffer poपूर्णांकer DMA transfer approach */

		अचिन्हित दीर्घ flags;

		/* width 32bit (prevent overflow): */
		u32 area_length;
		काष्ठा codec_setup_io अणु
			u32 dma_start_1;
			u32 dma_start_2;
			u32 dma_lengths;
		पूर्ण __attribute__((packed)) setup_io;

		area_length = buffer_bytes/2;

		setup_io.dma_start_1 = addr;
		setup_io.dma_start_2 = addr+area_length;

		dev_dbg(chip->card->dev,
			"setdma: buffers %08x[%u] / %08x[%u], %u, %u\n",
				setup_io.dma_start_1, area_length,
				setup_io.dma_start_2, area_length,
				period_bytes, buffer_bytes);

		/* Hmm, are we really supposed to decrement this by 1??
		   Most definitely certainly not: configuring full length करोes
		   work properly (i.e. likely better), and BTW we
		   violated possibly dअगरfering frame sizes with this...

		area_length--; |* max. index *|
		*/

		/* build combined I/O buffer length word */
		setup_io.dma_lengths = (area_length << 16) | (area_length);

		spin_lock_irqsave(codec->lock, flags);
		snd_azf3328_codec_outl_multi(
			codec, IDX_IO_CODEC_DMA_START_1, &setup_io, 3
		);
		spin_unlock_irqrestore(codec->lock, flags);
	पूर्ण
पूर्ण

अटल पूर्णांक
snd_azf3328_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_azf3328_codec_data *codec = runसमय->निजी_data;
#अगर 0
        अचिन्हित पूर्णांक size = snd_pcm_lib_buffer_bytes(substream);
	अचिन्हित पूर्णांक count = snd_pcm_lib_period_bytes(substream);
#पूर्ण_अगर

	codec->dma_base = runसमय->dma_addr;

#अगर 0
	snd_azf3328_codec_setfmt(codec,
		runसमय->rate,
		snd_pcm_क्रमmat_width(runसमय->क्रमmat),
		runसमय->channels);
	snd_azf3328_codec_setdmaa(chip, codec,
					runसमय->dma_addr, count, size);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_azf3328_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_azf3328 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_azf3328_codec_data *codec = runसमय->निजी_data;
	पूर्णांक result = 0;
	u16 flags1;
	bool previously_muted = false;
	bool is_मुख्य_mixer_playback_codec = (AZF_CODEC_PLAYBACK == codec->type);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		dev_dbg(chip->card->dev, "START PCM %s\n", codec->name);

		अगर (is_मुख्य_mixer_playback_codec) अणु
			/* mute WaveOut (aव्योम clicking during setup) */
			previously_muted =
				snd_azf3328_mixer_mute_control_pcm(
						chip, 1
				);
		पूर्ण

		snd_azf3328_codec_setfmt(codec,
			runसमय->rate,
			snd_pcm_क्रमmat_width(runसमय->क्रमmat),
			runसमय->channels);

		spin_lock(codec->lock);
		/* first, remember current value: */
		flags1 = snd_azf3328_codec_inw(codec, IDX_IO_CODEC_DMA_FLAGS);

		/* stop transfer */
		flags1 &= ~DMA_RESUME;
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS, flags1);

		/* FIXME: clear पूर्णांकerrupts or what??? */
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_IRQTYPE, 0xffff);
		spin_unlock(codec->lock);

		snd_azf3328_codec_setdmaa(chip, codec, runसमय->dma_addr,
			snd_pcm_lib_period_bytes(substream),
			snd_pcm_lib_buffer_bytes(substream)
		);

		spin_lock(codec->lock);
#अगर_घोषित WIN9X
		/* FIXME: enable playback/recording??? */
		flags1 |= DMA_RUN_SOMETHING1 | DMA_RUN_SOMETHING2;
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS, flags1);

		/* start transfer again */
		/* FIXME: what is this value (0x0010)??? */
		flags1 |= DMA_RESUME | DMA_EPILOGUE_SOMETHING;
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS, flags1);
#अन्यथा /* NT4 */
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS,
			0x0000);
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS,
			DMA_RUN_SOMETHING1);
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS,
			DMA_RUN_SOMETHING1 |
			DMA_RUN_SOMETHING2);
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS,
			DMA_RESUME |
			SOMETHING_ALMOST_ALWAYS_SET |
			DMA_EPILOGUE_SOMETHING |
			DMA_SOMETHING_ELSE);
#पूर्ण_अगर
		spin_unlock(codec->lock);
		snd_azf3328_ctrl_codec_activity(chip, codec->type, 1);

		अगर (is_मुख्य_mixer_playback_codec) अणु
			/* now unmute WaveOut */
			अगर (!previously_muted)
				snd_azf3328_mixer_mute_control_pcm(
						chip, 0
				);
		पूर्ण

		dev_dbg(chip->card->dev, "PCM STARTED %s\n", codec->name);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_RESUME:
		dev_dbg(chip->card->dev, "PCM RESUME %s\n", codec->name);
		/* resume codec अगर we were active */
		spin_lock(codec->lock);
		अगर (codec->running)
			snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS,
				snd_azf3328_codec_inw(
					codec, IDX_IO_CODEC_DMA_FLAGS
				) | DMA_RESUME
			);
		spin_unlock(codec->lock);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		dev_dbg(chip->card->dev, "PCM STOP %s\n", codec->name);

		अगर (is_मुख्य_mixer_playback_codec) अणु
			/* mute WaveOut (aव्योम clicking during setup) */
			previously_muted =
				snd_azf3328_mixer_mute_control_pcm(
						chip, 1
				);
		पूर्ण

		spin_lock(codec->lock);
		/* first, remember current value: */
		flags1 = snd_azf3328_codec_inw(codec, IDX_IO_CODEC_DMA_FLAGS);

		/* stop transfer */
		flags1 &= ~DMA_RESUME;
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS, flags1);

		/* hmm, is this really required? we're resetting the same bit
		 * immediately thereafter... */
		flags1 |= DMA_RUN_SOMETHING1;
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS, flags1);

		flags1 &= ~DMA_RUN_SOMETHING1;
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS, flags1);
		spin_unlock(codec->lock);
		snd_azf3328_ctrl_codec_activity(chip, codec->type, 0);

		अगर (is_मुख्य_mixer_playback_codec) अणु
			/* now unmute WaveOut */
			अगर (!previously_muted)
				snd_azf3328_mixer_mute_control_pcm(
						chip, 0
				);
		पूर्ण

		dev_dbg(chip->card->dev, "PCM STOPPED %s\n", codec->name);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		dev_dbg(chip->card->dev, "PCM SUSPEND %s\n", codec->name);
		/* make sure codec is stopped */
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS,
			snd_azf3328_codec_inw(
				codec, IDX_IO_CODEC_DMA_FLAGS
			) & ~DMA_RESUME
		);
		अवरोध;
        हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		WARN(1, "FIXME: SNDRV_PCM_TRIGGER_PAUSE_PUSH NIY!\n");
                अवरोध;
        हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		WARN(1, "FIXME: SNDRV_PCM_TRIGGER_PAUSE_RELEASE NIY!\n");
                अवरोध;
        शेष:
		WARN(1, "FIXME: unknown trigger mode!\n");
                वापस -EINVAL;
	पूर्ण

	वापस result;
पूर्ण

अटल snd_pcm_uframes_t
snd_azf3328_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream
)
अणु
	स्थिर काष्ठा snd_azf3328_codec_data *codec =
		substream->runसमय->निजी_data;
	अचिन्हित दीर्घ result;
	snd_pcm_uframes_t frmres;

	result = snd_azf3328_codec_inl(codec, IDX_IO_CODEC_DMA_CURRPOS);

	/* calculate offset */
#अगर_घोषित QUERY_HARDWARE
	result -= snd_azf3328_codec_inl(codec, IDX_IO_CODEC_DMA_START_1);
#अन्यथा
	result -= codec->dma_base;
#पूर्ण_अगर
	frmres = bytes_to_frames( substream->runसमय, result);
	dev_dbg(substream->pcm->card->dev, "%08li %s @ 0x%8lx, frames %8ld\n",
		jअगरfies, codec->name, result, frmres);
	वापस frmres;
पूर्ण

/******************************************************************/

#अगर_घोषित SUPPORT_GAMEPORT
अटल अंतरभूत व्योम
snd_azf3328_gameport_irq_enable(काष्ठा snd_azf3328 *chip,
				bool enable
)
अणु
	snd_azf3328_io_reg_setb(
		chip->game_io+IDX_GAME_HWCONFIG,
		GAME_HWCFG_IRQ_ENABLE,
		enable
	);
पूर्ण

अटल अंतरभूत व्योम
snd_azf3328_gameport_legacy_address_enable(काष्ठा snd_azf3328 *chip,
					   bool enable
)
अणु
	snd_azf3328_io_reg_setb(
		chip->game_io+IDX_GAME_HWCONFIG,
		GAME_HWCFG_LEGACY_ADDRESS_ENABLE,
		enable
	);
पूर्ण

अटल व्योम
snd_azf3328_gameport_set_counter_frequency(काष्ठा snd_azf3328 *chip,
					   अचिन्हित पूर्णांक freq_cfg
)
अणु
	snd_azf3328_io_reg_setb(
		chip->game_io+IDX_GAME_HWCONFIG,
		0x02,
		(freq_cfg & 1) != 0
	);
	snd_azf3328_io_reg_setb(
		chip->game_io+IDX_GAME_HWCONFIG,
		0x04,
		(freq_cfg & 2) != 0
	);
पूर्ण

अटल अंतरभूत व्योम
snd_azf3328_gameport_axis_circuit_enable(काष्ठा snd_azf3328 *chip, bool enable)
अणु
	snd_azf3328_ctrl_reg_6AH_update(
		chip, IO_6A_SOMETHING2_GAMEPORT, enable
	);
पूर्ण

अटल अंतरभूत व्योम
snd_azf3328_gameport_पूर्णांकerrupt(काष्ठा snd_azf3328 *chip)
अणु
	/*
	 * skeleton handler only
	 * (we करो not want axis पढ़ोing in पूर्णांकerrupt handler - too much load!)
	 */
	dev_dbg(chip->card->dev, "gameport irq\n");

	 /* this should ACK the gameport IRQ properly, hopefully. */
	snd_azf3328_game_inw(chip, IDX_GAME_AXIS_VALUE);
पूर्ण

अटल पूर्णांक
snd_azf3328_gameport_खोलो(काष्ठा gameport *gameport, पूर्णांक mode)
अणु
	काष्ठा snd_azf3328 *chip = gameport_get_port_data(gameport);
	पूर्णांक res;

	dev_dbg(chip->card->dev, "gameport_open, mode %d\n", mode);
	चयन (mode) अणु
	हाल GAMEPORT_MODE_COOKED:
	हाल GAMEPORT_MODE_RAW:
		res = 0;
		अवरोध;
	शेष:
		res = -1;
		अवरोध;
	पूर्ण

	snd_azf3328_gameport_set_counter_frequency(chip,
				GAME_HWCFG_ADC_COUNTER_FREQ_STD);
	snd_azf3328_gameport_axis_circuit_enable(chip, (res == 0));

	वापस res;
पूर्ण

अटल व्योम
snd_azf3328_gameport_बंद(काष्ठा gameport *gameport)
अणु
	काष्ठा snd_azf3328 *chip = gameport_get_port_data(gameport);

	dev_dbg(chip->card->dev, "gameport_close\n");
	snd_azf3328_gameport_set_counter_frequency(chip,
				GAME_HWCFG_ADC_COUNTER_FREQ_1_200);
	snd_azf3328_gameport_axis_circuit_enable(chip, 0);
पूर्ण

अटल पूर्णांक
snd_azf3328_gameport_cooked_पढ़ो(काष्ठा gameport *gameport,
				 पूर्णांक *axes,
				 पूर्णांक *buttons
)
अणु
	काष्ठा snd_azf3328 *chip = gameport_get_port_data(gameport);
	पूर्णांक i;
	u8 val;
	अचिन्हित दीर्घ flags;

	अगर (snd_BUG_ON(!chip))
		वापस 0;

	spin_lock_irqsave(&chip->reg_lock, flags);
	val = snd_azf3328_game_inb(chip, IDX_GAME_LEGACY_COMPATIBLE);
	*buttons = (~(val) >> 4) & 0xf;

	/* ok, this one is a bit dirty: cooked_पढ़ो is being polled by a समयr,
	 * thus we're atomic and cannot actively रुको in here
	 * (which would be useful क्रम us since it probably would be better
	 * to trigger a measurement in here, then रुको a लघु amount of
	 * समय until it's finished, then पढ़ो values of _this_ measurement).
	 *
	 * Thus we simply resort to पढ़ोing values अगर they're available alपढ़ोy
	 * and trigger the next measurement.
	 */

	val = snd_azf3328_game_inb(chip, IDX_GAME_AXES_CONFIG);
	अगर (val & GAME_AXES_SAMPLING_READY) अणु
		क्रम (i = 0; i < ARRAY_SIZE(chip->axes); ++i) अणु
			/* configure the axis to पढ़ो */
			val = (i << 4) | 0x0f;
			snd_azf3328_game_outb(chip, IDX_GAME_AXES_CONFIG, val);

			chip->axes[i] = snd_azf3328_game_inw(
						chip, IDX_GAME_AXIS_VALUE
					);
		पूर्ण
	पूर्ण

	/* trigger next sampling of axes, to be evaluated the next समय we
	 * enter this function */

	/* क्रम some very, very strange reason we cannot enable
	 * Measurement Ready monitoring क्रम all axes here,
	 * at least not when only one joystick connected */
	val = 0x03; /* we're able to monitor axes 1 and 2 only */
	snd_azf3328_game_outb(chip, IDX_GAME_AXES_CONFIG, val);

	snd_azf3328_game_outw(chip, IDX_GAME_AXIS_VALUE, 0xffff);
	spin_unlock_irqrestore(&chip->reg_lock, flags);

	क्रम (i = 0; i < ARRAY_SIZE(chip->axes); i++) अणु
		axes[i] = chip->axes[i];
		अगर (axes[i] == 0xffff)
			axes[i] = -1;
	पूर्ण

	dev_dbg(chip->card->dev, "cooked_read: axes %d %d %d %d buttons %d\n",
		axes[0], axes[1], axes[2], axes[3], *buttons);

	वापस 0;
पूर्ण

अटल पूर्णांक
snd_azf3328_gameport(काष्ठा snd_azf3328 *chip, पूर्णांक dev)
अणु
	काष्ठा gameport *gp;

	chip->gameport = gp = gameport_allocate_port();
	अगर (!gp) अणु
		dev_err(chip->card->dev, "cannot alloc memory for gameport\n");
		वापस -ENOMEM;
	पूर्ण

	gameport_set_name(gp, "AZF3328 Gameport");
	gameport_set_phys(gp, "pci%s/gameport0", pci_name(chip->pci));
	gameport_set_dev_parent(gp, &chip->pci->dev);
	gp->io = chip->game_io;
	gameport_set_port_data(gp, chip);

	gp->खोलो = snd_azf3328_gameport_खोलो;
	gp->बंद = snd_azf3328_gameport_बंद;
	gp->fuzz = 16; /* seems ok */
	gp->cooked_पढ़ो = snd_azf3328_gameport_cooked_पढ़ो;

	/* DISABLE legacy address: we करोn't need it! */
	snd_azf3328_gameport_legacy_address_enable(chip, 0);

	snd_azf3328_gameport_set_counter_frequency(chip,
				GAME_HWCFG_ADC_COUNTER_FREQ_1_200);
	snd_azf3328_gameport_axis_circuit_enable(chip, 0);

	gameport_रेजिस्टर_port(chip->gameport);

	वापस 0;
पूर्ण

अटल व्योम
snd_azf3328_gameport_मुक्त(काष्ठा snd_azf3328 *chip)
अणु
	अगर (chip->gameport) अणु
		gameport_unरेजिस्टर_port(chip->gameport);
		chip->gameport = शून्य;
	पूर्ण
	snd_azf3328_gameport_irq_enable(chip, 0);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक
snd_azf3328_gameport(काष्ठा snd_azf3328 *chip, पूर्णांक dev) अणु वापस -ENOSYS; पूर्ण
अटल अंतरभूत व्योम
snd_azf3328_gameport_मुक्त(काष्ठा snd_azf3328 *chip) अणु पूर्ण
अटल अंतरभूत व्योम
snd_azf3328_gameport_पूर्णांकerrupt(काष्ठा snd_azf3328 *chip)
अणु
	dev_warn(chip->card->dev, "huh, game port IRQ occurred!?\n");
पूर्ण
#पूर्ण_अगर /* SUPPORT_GAMEPORT */

/******************************************************************/

अटल अंतरभूत व्योम
snd_azf3328_irq_log_unknown_type(काष्ठा snd_azf3328 *chip, u8 which)
अणु
	dev_dbg(chip->card->dev,
		"unknown IRQ type (%x) occurred, please report!\n",
		which);
पूर्ण

अटल अंतरभूत व्योम
snd_azf3328_pcm_पूर्णांकerrupt(काष्ठा snd_azf3328 *chip,
			  स्थिर काष्ठा snd_azf3328_codec_data *first_codec,
			  u8 status
)
अणु
	u8 which;
	क्रमागत snd_azf3328_codec_type codec_type;
	स्थिर काष्ठा snd_azf3328_codec_data *codec = first_codec;

	क्रम (codec_type = AZF_CODEC_PLAYBACK;
		 codec_type <= AZF_CODEC_I2S_OUT;
			 ++codec_type, ++codec) अणु

		/* skip codec अगर there's no पूर्णांकerrupt क्रम it */
		अगर (!(status & (1 << codec_type)))
			जारी;

		spin_lock(codec->lock);
		which = snd_azf3328_codec_inb(codec, IDX_IO_CODEC_IRQTYPE);
		/* ack all IRQ types immediately */
		snd_azf3328_codec_outb(codec, IDX_IO_CODEC_IRQTYPE, which);
		spin_unlock(codec->lock);

		अगर (codec->substream) अणु
			snd_pcm_period_elapsed(codec->substream);
			dev_dbg(chip->card->dev, "%s period done (#%x), @ %x\n",
				codec->name,
				which,
				snd_azf3328_codec_inl(
					codec, IDX_IO_CODEC_DMA_CURRPOS));
		पूर्ण अन्यथा
			dev_warn(chip->card->dev, "irq handler problem!\n");
		अगर (which & IRQ_SOMETHING)
			snd_azf3328_irq_log_unknown_type(chip, which);
	पूर्ण
पूर्ण

अटल irqवापस_t
snd_azf3328_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_azf3328 *chip = dev_id;
	u8 status;
	अटल अचिन्हित दीर्घ irq_count;

	status = snd_azf3328_ctrl_inb(chip, IDX_IO_IRQSTATUS);

        /* fast path out, to ease पूर्णांकerrupt sharing */
	अगर (!(status &
		(IRQ_PLAYBACK|IRQ_RECORDING|IRQ_I2S_OUT
		|IRQ_GAMEPORT|IRQ_MPU401|IRQ_TIMER)
	))
		वापस IRQ_NONE; /* must be पूर्णांकerrupt क्रम another device */

	dev_dbg(chip->card->dev,
		"irq_count %ld! IDX_IO_IRQSTATUS %04x\n",
			irq_count++ /* debug-only */,
			status);

	अगर (status & IRQ_TIMER) अणु
		/* dev_dbg(chip->card->dev, "timer %ld\n",
			snd_azf3328_codec_inl(chip, IDX_IO_TIMER_VALUE)
				& TIMER_VALUE_MASK
		); */
		अगर (chip->समयr)
			snd_समयr_पूर्णांकerrupt(chip->समयr, chip->समयr->sticks);
		/* ACK समयr */
                spin_lock(&chip->reg_lock);
		snd_azf3328_ctrl_outb(chip, IDX_IO_TIMER_VALUE + 3, 0x07);
		spin_unlock(&chip->reg_lock);
		dev_dbg(chip->card->dev, "timer IRQ\n");
	पूर्ण

	अगर (status & (IRQ_PLAYBACK|IRQ_RECORDING|IRQ_I2S_OUT))
		snd_azf3328_pcm_पूर्णांकerrupt(chip, chip->codecs, status);

	अगर (status & IRQ_GAMEPORT)
		snd_azf3328_gameport_पूर्णांकerrupt(chip);

	/* MPU401 has less critical IRQ requirements
	 * than समयr and playback/recording, right? */
	अगर (status & IRQ_MPU401) अणु
		snd_mpu401_uart_पूर्णांकerrupt(irq, chip->rmidi->निजी_data);

		/* hmm, करो we have to ack the IRQ here somehow?
		 * If so, then I करोn't know how yet... */
		dev_dbg(chip->card->dev, "MPU401 IRQ\n");
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

/*****************************************************************/

/* as दीर्घ as we think we have identical snd_pcm_hardware parameters
   क्रम playback, capture and i2s out, we can use the same physical काष्ठा
   since the काष्ठा is simply being copied पूर्णांकo a member.
*/
अटल स्थिर काष्ठा snd_pcm_hardware snd_azf3328_hardware =
अणु
	/* FIXME!! Correct? */
	.info =			SNDRV_PCM_INFO_MMAP |
				SNDRV_PCM_INFO_INTERLEAVED |
				SNDRV_PCM_INFO_MMAP_VALID,
	.क्रमmats =		SNDRV_PCM_FMTBIT_S8 |
				SNDRV_PCM_FMTBIT_U8 |
				SNDRV_PCM_FMTBIT_S16_LE |
				SNDRV_PCM_FMTBIT_U16_LE,
	.rates =		SNDRV_PCM_RATE_5512 |
				SNDRV_PCM_RATE_8000_48000 |
				SNDRV_PCM_RATE_KNOT,
	.rate_min =		AZF_FREQ_4000,
	.rate_max =		AZF_FREQ_66200,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(64*1024),
	.period_bytes_min =	1024,
	.period_bytes_max =	(32*1024),
	/* We simply have two DMA areas (instead of a list of descriptors
	   such as other cards); I believe that this is a fixed hardware
	   attribute and there isn't much driver magic to be करोne to expand it.
	   Thus indicate that we have at least and at most 2 periods. */
	.periods_min =		2,
	.periods_max =		2,
	/* FIXME: maybe that card actually has a FIFO?
	 * Hmm, it seems newer revisions करो have one, but we still करोn't know
	 * its size... */
	.fअगरo_size =		0,
पूर्ण;


अटल स्थिर अचिन्हित पूर्णांक snd_azf3328_fixed_rates[] = अणु
	AZF_FREQ_4000,
	AZF_FREQ_4800,
	AZF_FREQ_5512,
	AZF_FREQ_6620,
	AZF_FREQ_8000,
	AZF_FREQ_9600,
	AZF_FREQ_11025,
	AZF_FREQ_13240,
	AZF_FREQ_16000,
	AZF_FREQ_22050,
	AZF_FREQ_32000,
	AZF_FREQ_44100,
	AZF_FREQ_48000,
	AZF_FREQ_66200
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list snd_azf3328_hw_स्थिरraपूर्णांकs_rates = अणु
	.count = ARRAY_SIZE(snd_azf3328_fixed_rates),
	.list = snd_azf3328_fixed_rates,
	.mask = 0,
पूर्ण;

/*****************************************************************/

अटल पूर्णांक
snd_azf3328_pcm_खोलो(काष्ठा snd_pcm_substream *substream,
		     क्रमागत snd_azf3328_codec_type codec_type
)
अणु
	काष्ठा snd_azf3328 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_azf3328_codec_data *codec = &chip->codecs[codec_type];

	codec->substream = substream;

	/* same parameters क्रम all our codecs - at least we think so... */
	runसमय->hw = snd_azf3328_hardware;

	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				   &snd_azf3328_hw_स्थिरraपूर्णांकs_rates);
	runसमय->निजी_data = codec;
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_azf3328_pcm_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_azf3328_pcm_खोलो(substream, AZF_CODEC_PLAYBACK);
पूर्ण

अटल पूर्णांक
snd_azf3328_pcm_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_azf3328_pcm_खोलो(substream, AZF_CODEC_CAPTURE);
पूर्ण

अटल पूर्णांक
snd_azf3328_pcm_i2s_out_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_azf3328_pcm_खोलो(substream, AZF_CODEC_I2S_OUT);
पूर्ण

अटल पूर्णांक
snd_azf3328_pcm_बंद(काष्ठा snd_pcm_substream *substream
)
अणु
	काष्ठा snd_azf3328_codec_data *codec =
		substream->runसमय->निजी_data;

	codec->substream = शून्य;
	वापस 0;
पूर्ण

/******************************************************************/

अटल स्थिर काष्ठा snd_pcm_ops snd_azf3328_playback_ops = अणु
	.खोलो =		snd_azf3328_pcm_playback_खोलो,
	.बंद =	snd_azf3328_pcm_बंद,
	.prepare =	snd_azf3328_pcm_prepare,
	.trigger =	snd_azf3328_pcm_trigger,
	.poपूर्णांकer =	snd_azf3328_pcm_poपूर्णांकer
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_azf3328_capture_ops = अणु
	.खोलो =		snd_azf3328_pcm_capture_खोलो,
	.बंद =	snd_azf3328_pcm_बंद,
	.prepare =	snd_azf3328_pcm_prepare,
	.trigger =	snd_azf3328_pcm_trigger,
	.poपूर्णांकer =	snd_azf3328_pcm_poपूर्णांकer
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_azf3328_i2s_out_ops = अणु
	.खोलो =		snd_azf3328_pcm_i2s_out_खोलो,
	.बंद =	snd_azf3328_pcm_बंद,
	.prepare =	snd_azf3328_pcm_prepare,
	.trigger =	snd_azf3328_pcm_trigger,
	.poपूर्णांकer =	snd_azf3328_pcm_poपूर्णांकer
पूर्ण;

अटल पूर्णांक
snd_azf3328_pcm(काष्ठा snd_azf3328 *chip)
अणु
	/* pcm devices */
	क्रमागत अणु AZF_PCMDEV_STD, AZF_PCMDEV_I2S_OUT, NUM_AZF_PCMDEVS पूर्ण;

	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	err = snd_pcm_new(chip->card, "AZF3328 DSP", AZF_PCMDEV_STD,
								1, 1, &pcm);
	अगर (err < 0)
		वापस err;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
						&snd_azf3328_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
						&snd_azf3328_capture_ops);

	pcm->निजी_data = chip;
	pcm->info_flags = 0;
	म_नकल(pcm->name, chip->card->लघुname);
	/* same pcm object क्रम playback/capture (see snd_pcm_new() above) */
	chip->pcm[AZF_CODEC_PLAYBACK] = pcm;
	chip->pcm[AZF_CODEC_CAPTURE] = pcm;

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV, &chip->pci->dev,
				       64*1024, 64*1024);

	err = snd_pcm_new(chip->card, "AZF3328 I2S OUT", AZF_PCMDEV_I2S_OUT,
								1, 0, &pcm);
	अगर (err < 0)
		वापस err;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
						&snd_azf3328_i2s_out_ops);

	pcm->निजी_data = chip;
	pcm->info_flags = 0;
	म_नकल(pcm->name, chip->card->लघुname);
	chip->pcm[AZF_CODEC_I2S_OUT] = pcm;

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV, &chip->pci->dev,
				       64*1024, 64*1024);

	वापस 0;
पूर्ण

/******************************************************************/

/*** NOTE: the physical समयr resolution actually is 1024000 ticks per second
 *** (probably derived from मुख्य crystal via a भागider of 24),
 *** but announcing those attributes to user-space would make programs
 *** configure the समयr to a 1 tick value, resulting in an असलolutely fatal
 *** समयr IRQ storm.
 *** Thus I chose to announce a करोwn-scaled भव समयr to the outside and
 *** calculate real समयr countकरोwn values पूर्णांकernally.
 *** (the scale factor can be set via module parameter "seqtimer_scaling").
 ***/

अटल पूर्णांक
snd_azf3328_समयr_start(काष्ठा snd_समयr *समयr)
अणु
	काष्ठा snd_azf3328 *chip;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक delay;

	chip = snd_समयr_chip(समयr);
	delay = ((समयr->sticks * seqसमयr_scaling) - 1) & TIMER_VALUE_MASK;
	अगर (delay < 49) अणु
		/* uhoh, that's not good, since user-space won't know about
		 * this timing tweak
		 * (we need to करो it to aव्योम a lockup, though) */

		dev_dbg(chip->card->dev, "delay was too low (%d)!\n", delay);
		delay = 49; /* minimum समय is 49 ticks */
	पूर्ण
	dev_dbg(chip->card->dev, "setting timer countdown value %d\n", delay);
	delay |= TIMER_COUNTDOWN_ENABLE | TIMER_IRQ_ENABLE;
	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_azf3328_ctrl_outl(chip, IDX_IO_TIMER_VALUE, delay);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_azf3328_समयr_stop(काष्ठा snd_समयr *समयr)
अणु
	काष्ठा snd_azf3328 *chip;
	अचिन्हित दीर्घ flags;

	chip = snd_समयr_chip(समयr);
	spin_lock_irqsave(&chip->reg_lock, flags);
	/* disable समयr countकरोwn and पूर्णांकerrupt */
	/* Hmm, should we ग_लिखो TIMER_IRQ_ACK here?
	   YES indeed, otherwise a rogue समयr operation - which prompts
	   ALSA(?) to call repeated stop() in vain, but NOT start() -
	   will never end (value 0x03 is kept shown in control byte).
	   Simply manually poking 0x04 _once_ immediately successfully stops
	   the hardware/ALSA पूर्णांकerrupt activity. */
	snd_azf3328_ctrl_outb(chip, IDX_IO_TIMER_VALUE + 3, 0x04);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस 0;
पूर्ण


अटल पूर्णांक
snd_azf3328_समयr_precise_resolution(काष्ठा snd_समयr *समयr,
					       अचिन्हित दीर्घ *num, अचिन्हित दीर्घ *den)
अणु
	*num = 1;
	*den = 1024000 / seqसमयr_scaling;
	वापस 0;
पूर्ण

अटल काष्ठा snd_समयr_hardware snd_azf3328_समयr_hw = अणु
	.flags = SNDRV_TIMER_HW_AUTO,
	.resolution = 977, /* 1000000/1024000 = 0.9765625us */
	.ticks = 1024000, /* max tick count, defined by the value रेजिस्टर; actually it's not 1024000, but 1048576, but we don't care */
	.start = snd_azf3328_समयr_start,
	.stop = snd_azf3328_समयr_stop,
	.precise_resolution = snd_azf3328_समयr_precise_resolution,
पूर्ण;

अटल पूर्णांक
snd_azf3328_समयr(काष्ठा snd_azf3328 *chip, पूर्णांक device)
अणु
	काष्ठा snd_समयr *समयr = शून्य;
	काष्ठा snd_समयr_id tid;
	पूर्णांक err;

	tid.dev_class = SNDRV_TIMER_CLASS_CARD;
	tid.dev_sclass = SNDRV_TIMER_SCLASS_NONE;
	tid.card = chip->card->number;
	tid.device = device;
	tid.subdevice = 0;

	snd_azf3328_समयr_hw.resolution *= seqसमयr_scaling;
	snd_azf3328_समयr_hw.ticks /= seqसमयr_scaling;

	err = snd_समयr_new(chip->card, "AZF3328", &tid, &समयr);
	अगर (err < 0)
		जाओ out;

	म_नकल(समयr->name, "AZF3328 timer");
	समयr->निजी_data = chip;
	समयr->hw = snd_azf3328_समयr_hw;

	chip->समयr = समयr;

	snd_azf3328_समयr_stop(समयr);

	err = 0;

out:
	वापस err;
पूर्ण

/******************************************************************/

अटल पूर्णांक
snd_azf3328_मुक्त(काष्ठा snd_azf3328 *chip)
अणु
	अगर (chip->irq < 0)
		जाओ __end_hw;

	snd_azf3328_mixer_reset(chip);

	snd_azf3328_समयr_stop(chip->समयr);
	snd_azf3328_gameport_मुक्त(chip);

__end_hw:
	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, chip);
	pci_release_regions(chip->pci);
	pci_disable_device(chip->pci);

	kमुक्त(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_azf3328_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_azf3328 *chip = device->device_data;
	वापस snd_azf3328_मुक्त(chip);
पूर्ण

#अगर 0
/* check whether a bit can be modअगरied */
अटल व्योम
snd_azf3328_test_bit(अचिन्हित अचिन्हित reg, पूर्णांक bit)
अणु
	अचिन्हित अक्षर val, valoff, valon;

	val = inb(reg);

	outb(val & ~(1 << bit), reg);
	valoff = inb(reg);

	outb(val|(1 << bit), reg);
	valon = inb(reg);

	outb(val, reg);

	prपूर्णांकk(KERN_DEBUG "reg %04x bit %d: %02x %02x %02x\n",
				reg, bit, val, valoff, valon
	);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम
snd_azf3328_debug_show_ports(स्थिर काष्ठा snd_azf3328 *chip)
अणु
	u16 पंचांगp;

	dev_dbg(chip->card->dev,
		"ctrl_io 0x%lx, game_io 0x%lx, mpu_io 0x%lx, "
		"opl3_io 0x%lx, mixer_io 0x%lx, irq %d\n",
		chip->ctrl_io, chip->game_io, chip->mpu_io,
		chip->opl3_io, chip->mixer_io, chip->irq);

	dev_dbg(chip->card->dev,
		"game %02x %02x %02x %02x %02x %02x\n",
		snd_azf3328_game_inb(chip, 0),
		snd_azf3328_game_inb(chip, 1),
		snd_azf3328_game_inb(chip, 2),
		snd_azf3328_game_inb(chip, 3),
		snd_azf3328_game_inb(chip, 4),
		snd_azf3328_game_inb(chip, 5));

	क्रम (पंचांगp = 0; पंचांगp < 0x07; पंचांगp += 1)
		dev_dbg(chip->card->dev,
			"mpu_io 0x%04x\n", inb(chip->mpu_io + पंचांगp));

	क्रम (पंचांगp = 0; पंचांगp <= 0x07; पंचांगp += 1)
		dev_dbg(chip->card->dev,
			"0x%02x: game200 0x%04x, game208 0x%04x\n",
			पंचांगp, inb(0x200 + पंचांगp), inb(0x208 + पंचांगp));

	क्रम (पंचांगp = 0; पंचांगp <= 0x01; पंचांगp += 1)
		dev_dbg(chip->card->dev,
			"0x%02x: mpu300 0x%04x, mpu310 0x%04x, mpu320 0x%04x, "
			"mpu330 0x%04x opl388 0x%04x opl38c 0x%04x\n",
				पंचांगp,
				inb(0x300 + पंचांगp),
				inb(0x310 + पंचांगp),
				inb(0x320 + पंचांगp),
				inb(0x330 + पंचांगp),
				inb(0x388 + पंचांगp),
				inb(0x38c + पंचांगp));

	क्रम (पंचांगp = 0; पंचांगp < AZF_IO_SIZE_CTRL; पंचांगp += 2)
		dev_dbg(chip->card->dev,
			"ctrl 0x%02x: 0x%04x\n",
			पंचांगp, snd_azf3328_ctrl_inw(chip, पंचांगp));

	क्रम (पंचांगp = 0; पंचांगp < AZF_IO_SIZE_MIXER; पंचांगp += 2)
		dev_dbg(chip->card->dev,
			"mixer 0x%02x: 0x%04x\n",
			पंचांगp, snd_azf3328_mixer_inw(chip, पंचांगp));
पूर्ण

अटल पूर्णांक
snd_azf3328_create(काष्ठा snd_card *card,
		   काष्ठा pci_dev *pci,
		   अचिन्हित दीर्घ device_type,
		   काष्ठा snd_azf3328 **rchip)
अणु
	काष्ठा snd_azf3328 *chip;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =     snd_azf3328_dev_मुक्त,
	पूर्ण;
	u8 dma_init;
	क्रमागत snd_azf3328_codec_type codec_type;
	काष्ठा snd_azf3328_codec_data *codec_setup;

	*rchip = शून्य;

	err = pci_enable_device(pci);
	अगर (err < 0)
		वापस err;

	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य) अणु
		err = -ENOMEM;
		जाओ out_err;
	पूर्ण
	spin_lock_init(&chip->reg_lock);
	chip->card = card;
	chip->pci = pci;
	chip->irq = -1;

	/* check अगर we can restrict PCI DMA transfers to 24 bits */
	अगर (dma_set_mask_and_coherent(&pci->dev, DMA_BIT_MASK(24))) अणु
		dev_err(card->dev,
			"architecture does not support 24bit PCI busmaster DMA\n"
		);
		err = -ENXIO;
		जाओ out_err;
	पूर्ण

	err = pci_request_regions(pci, "Aztech AZF3328");
	अगर (err < 0)
		जाओ out_err;

	chip->ctrl_io  = pci_resource_start(pci, 0);
	chip->game_io  = pci_resource_start(pci, 1);
	chip->mpu_io   = pci_resource_start(pci, 2);
	chip->opl3_io  = pci_resource_start(pci, 3);
	chip->mixer_io = pci_resource_start(pci, 4);

	codec_setup = &chip->codecs[AZF_CODEC_PLAYBACK];
	codec_setup->io_base = chip->ctrl_io + AZF_IO_OFFS_CODEC_PLAYBACK;
	codec_setup->lock = &chip->reg_lock;
	codec_setup->type = AZF_CODEC_PLAYBACK;
	codec_setup->name = "PLAYBACK";

	codec_setup = &chip->codecs[AZF_CODEC_CAPTURE];
	codec_setup->io_base = chip->ctrl_io + AZF_IO_OFFS_CODEC_CAPTURE;
	codec_setup->lock = &chip->reg_lock;
	codec_setup->type = AZF_CODEC_CAPTURE;
	codec_setup->name = "CAPTURE";

	codec_setup = &chip->codecs[AZF_CODEC_I2S_OUT];
	codec_setup->io_base = chip->ctrl_io + AZF_IO_OFFS_CODEC_I2S_OUT;
	codec_setup->lock = &chip->reg_lock;
	codec_setup->type = AZF_CODEC_I2S_OUT;
	codec_setup->name = "I2S_OUT";

	अगर (request_irq(pci->irq, snd_azf3328_पूर्णांकerrupt,
			IRQF_SHARED, KBUILD_MODNAME, chip)) अणु
		dev_err(card->dev, "unable to grab IRQ %d\n", pci->irq);
		err = -EBUSY;
		जाओ out_err;
	पूर्ण
	chip->irq = pci->irq;
	card->sync_irq = chip->irq;
	pci_set_master(pci);

	snd_azf3328_debug_show_ports(chip);

	err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops);
	अगर (err < 0)
		जाओ out_err;

	/* create mixer पूर्णांकerface & चयनes */
	err = snd_azf3328_mixer_new(chip);
	अगर (err < 0)
		जाओ out_err;

	/* standard codec init stuff */
		/* शेष DMA init value */
	dma_init = DMA_RUN_SOMETHING2|DMA_EPILOGUE_SOMETHING|DMA_SOMETHING_ELSE;

	क्रम (codec_type = AZF_CODEC_PLAYBACK;
		codec_type <= AZF_CODEC_I2S_OUT; ++codec_type) अणु
		काष्ठा snd_azf3328_codec_data *codec =
			 &chip->codecs[codec_type];

		/* shutकरोwn codecs to reduce घातer / noise */
			/* have ...ctrl_codec_activity() act properly */
		codec->running = true;
		snd_azf3328_ctrl_codec_activity(chip, codec_type, 0);

		spin_lock_irq(codec->lock);
		snd_azf3328_codec_outb(codec, IDX_IO_CODEC_DMA_FLAGS,
						 dma_init);
		spin_unlock_irq(codec->lock);
	पूर्ण

	*rchip = chip;

	err = 0;
	जाओ out;

out_err:
	अगर (chip)
		snd_azf3328_मुक्त(chip);
	pci_disable_device(pci);

out:
	वापस err;
पूर्ण

अटल पूर्णांक
snd_azf3328_probe(काष्ठा pci_dev *pci, स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	काष्ठा snd_azf3328 *chip;
	काष्ठा snd_opl3 *opl3;
	पूर्णांक err;

	अगर (dev >= SNDRV_CARDS) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण
	अगर (!enable[dev]) अणु
		dev++;
		err = -ENOENT;
		जाओ out;
	पूर्ण

	err = snd_card_new(&pci->dev, index[dev], id[dev], THIS_MODULE,
			   0, &card);
	अगर (err < 0)
		जाओ out;

	म_नकल(card->driver, "AZF3328");
	म_नकल(card->लघुname, "Aztech AZF3328 (PCI168)");

	err = snd_azf3328_create(card, pci, pci_id->driver_data, &chip);
	अगर (err < 0)
		जाओ out_err;

	card->निजी_data = chip;

	/* chose to use MPU401_HW_AZT2320 ID instead of MPU401_HW_MPU401,
	   since our hardware ought to be similar, thus use same ID. */
	err = snd_mpu401_uart_new(
		card, 0,
		MPU401_HW_AZT2320, chip->mpu_io,
		MPU401_INFO_INTEGRATED | MPU401_INFO_IRQ_HOOK,
		-1, &chip->rmidi
	);
	अगर (err < 0) अणु
		dev_err(card->dev, "no MPU-401 device at 0x%lx?\n",
				chip->mpu_io
		);
		जाओ out_err;
	पूर्ण

	err = snd_azf3328_समयr(chip, 0);
	अगर (err < 0)
		जाओ out_err;

	err = snd_azf3328_pcm(chip);
	अगर (err < 0)
		जाओ out_err;

	अगर (snd_opl3_create(card, chip->opl3_io, chip->opl3_io+2,
			    OPL3_HW_AUTO, 1, &opl3) < 0) अणु
		dev_err(card->dev, "no OPL3 device at 0x%lx-0x%lx?\n",
			   chip->opl3_io, chip->opl3_io+2
		);
	पूर्ण अन्यथा अणु
		/* need to use IDs 1, 2 since ID 0 is snd_azf3328_समयr above */
		err = snd_opl3_समयr_new(opl3, 1, 2);
		अगर (err < 0)
			जाओ out_err;
		err = snd_opl3_hwdep_new(opl3, 0, 1, शून्य);
		अगर (err < 0)
			जाओ out_err;
		opl3->निजी_data = chip;
	पूर्ण

	प्र_लिखो(card->दीर्घname, "%s at 0x%lx, irq %i",
		card->लघुname, chip->ctrl_io, chip->irq);

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ out_err;

#अगर_घोषित MODULE
	dev_info(card->dev,
		 "Sound driver for Aztech AZF3328-based soundcards such as PCI168.\n");
	dev_info(card->dev,
		 "Hardware was completely undocumented, unfortunately.\n");
	dev_info(card->dev,
		 "Feel free to contact andi AT lisas.de for bug reports etc.!\n");
	dev_info(card->dev,
		 "User-scalable sequencer timer set to %dHz (1024000Hz / %d).\n",
		 1024000 / seqसमयr_scaling, seqसमयr_scaling);
#पूर्ण_अगर

	snd_azf3328_gameport(chip, dev);

	pci_set_drvdata(pci, card);
	dev++;

	err = 0;
	जाओ out;

out_err:
	dev_err(card->dev, "something failed, exiting\n");
	snd_card_मुक्त(card);

out:
	वापस err;
पूर्ण

अटल व्योम
snd_azf3328_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल अंतरभूत व्योम
snd_azf3328_suspend_regs(स्थिर काष्ठा snd_azf3328 *chip,
			 अचिन्हित दीर्घ io_addr, अचिन्हित count, u32 *saved_regs)
अणु
	अचिन्हित reg;

	क्रम (reg = 0; reg < count; ++reg) अणु
		*saved_regs = inl(io_addr);
		dev_dbg(chip->card->dev, "suspend: io 0x%04lx: 0x%08x\n",
			io_addr, *saved_regs);
		++saved_regs;
		io_addr += माप(*saved_regs);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
snd_azf3328_resume_regs(स्थिर काष्ठा snd_azf3328 *chip,
			स्थिर u32 *saved_regs,
			अचिन्हित दीर्घ io_addr,
			अचिन्हित count
)
अणु
	अचिन्हित reg;

	क्रम (reg = 0; reg < count; ++reg) अणु
		outl(*saved_regs, io_addr);
		dev_dbg(chip->card->dev,
			"resume: io 0x%04lx: 0x%08x --> 0x%08x\n",
			io_addr, *saved_regs, inl(io_addr));
		++saved_regs;
		io_addr += माप(*saved_regs);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
snd_azf3328_suspend_ac97(काष्ठा snd_azf3328 *chip)
अणु
#अगर_घोषित AZF_USE_AC97_LAYER
	snd_ac97_suspend(chip->ac97);
#अन्यथा
	snd_azf3328_suspend_regs(chip, chip->mixer_io,
		ARRAY_SIZE(chip->saved_regs_mixer), chip->saved_regs_mixer);

	/* make sure to disable master volume etc. to prevent looping sound */
	snd_azf3328_mixer_mute_control_master(chip, 1);
	snd_azf3328_mixer_mute_control_pcm(chip, 1);
#पूर्ण_अगर /* AZF_USE_AC97_LAYER */
पूर्ण

अटल अंतरभूत व्योम
snd_azf3328_resume_ac97(स्थिर काष्ठा snd_azf3328 *chip)
अणु
#अगर_घोषित AZF_USE_AC97_LAYER
	snd_ac97_resume(chip->ac97);
#अन्यथा
	snd_azf3328_resume_regs(chip, chip->saved_regs_mixer, chip->mixer_io,
					ARRAY_SIZE(chip->saved_regs_mixer));

	/* unक्रमtunately with 32bit transfers, IDX_MIXER_PLAY_MASTER (0x02)
	   and IDX_MIXER_RESET (offset 0x00) get touched at the same समय,
	   resulting in a mixer reset condition persisting until _after_
	   master vol was restored. Thus master vol needs an extra restore. */
	outw(((u16 *)chip->saved_regs_mixer)[1], chip->mixer_io + 2);
#पूर्ण_अगर /* AZF_USE_AC97_LAYER */
पूर्ण

अटल पूर्णांक
snd_azf3328_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_azf3328 *chip = card->निजी_data;
	u16 *saved_regs_ctrl_u16;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);

	snd_azf3328_suspend_ac97(chip);

	snd_azf3328_suspend_regs(chip, chip->ctrl_io,
		ARRAY_SIZE(chip->saved_regs_ctrl), chip->saved_regs_ctrl);

	/* manually store the one currently relevant ग_लिखो-only reg, too */
	saved_regs_ctrl_u16 = (u16 *)chip->saved_regs_ctrl;
	saved_regs_ctrl_u16[IDX_IO_6AH / 2] = chip->shaकरोw_reg_ctrl_6AH;

	snd_azf3328_suspend_regs(chip, chip->game_io,
		ARRAY_SIZE(chip->saved_regs_game), chip->saved_regs_game);
	snd_azf3328_suspend_regs(chip, chip->mpu_io,
		ARRAY_SIZE(chip->saved_regs_mpu), chip->saved_regs_mpu);
	snd_azf3328_suspend_regs(chip, chip->opl3_io,
		ARRAY_SIZE(chip->saved_regs_opl3), chip->saved_regs_opl3);
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_azf3328_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	स्थिर काष्ठा snd_azf3328 *chip = card->निजी_data;

	snd_azf3328_resume_regs(chip, chip->saved_regs_game, chip->game_io,
					ARRAY_SIZE(chip->saved_regs_game));
	snd_azf3328_resume_regs(chip, chip->saved_regs_mpu, chip->mpu_io,
					ARRAY_SIZE(chip->saved_regs_mpu));
	snd_azf3328_resume_regs(chip, chip->saved_regs_opl3, chip->opl3_io,
					ARRAY_SIZE(chip->saved_regs_opl3));

	snd_azf3328_resume_ac97(chip);

	snd_azf3328_resume_regs(chip, chip->saved_regs_ctrl, chip->ctrl_io,
					ARRAY_SIZE(chip->saved_regs_ctrl));

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(snd_azf3328_pm, snd_azf3328_suspend, snd_azf3328_resume);
#घोषणा SND_AZF3328_PM_OPS	&snd_azf3328_pm
#अन्यथा
#घोषणा SND_AZF3328_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल काष्ठा pci_driver azf3328_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_azf3328_ids,
	.probe = snd_azf3328_probe,
	.हटाओ = snd_azf3328_हटाओ,
	.driver = अणु
		.pm = SND_AZF3328_PM_OPS,
	पूर्ण,
पूर्ण;

module_pci_driver(azf3328_driver);
