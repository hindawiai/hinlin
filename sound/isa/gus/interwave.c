<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम AMD InterWave soundcard
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *
 *   1999/07/22		Erik Inge Bolso <knan@mo.himolde.no>
 *			* mixer group handlers
 */

#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/isa.h>
#समावेश <linux/delay.h>
#समावेश <linux/pnp.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/dma.h>
#समावेश <sound/core.h>
#समावेश <sound/gus.h>
#समावेश <sound/wss.h>
#अगर_घोषित SNDRV_STB
#समावेश <sound/tea6330t.h>
#पूर्ण_अगर
#घोषणा SNDRV_LEGACY_FIND_FREE_IRQ
#घोषणा SNDRV_LEGACY_FIND_FREE_DMA
#समावेश <sound/initval.h>

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_LICENSE("GPL");
#अगर_अघोषित SNDRV_STB
MODULE_DESCRIPTION("AMD InterWave");
#अन्यथा
MODULE_DESCRIPTION("AMD InterWave STB with TEA6330T");
#पूर्ण_अगर

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_ISAPNP; /* Enable this card */
#अगर_घोषित CONFIG_PNP
अटल bool isapnp[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 1पूर्ण;
#पूर्ण_अगर
अटल दीर्घ port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* 0x210,0x220,0x230,0x240,0x250,0x260 */
#अगर_घोषित SNDRV_STB
अटल दीर्घ port_tc[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* 0x350,0x360,0x370,0x380 */
#पूर्ण_अगर
अटल पूर्णांक irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;	/* 2,3,5,9,11,12,15 */
अटल पूर्णांक dma1[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;	/* 0,1,3,5,6,7 */
अटल पूर्णांक dma2[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;	/* 0,1,3,5,6,7 */
अटल पूर्णांक joystick_dac[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 29पूर्ण;
				/* 0 to 31, (0.59V-4.52V or 0.389V-2.98V) */
अटल पूर्णांक midi[SNDRV_CARDS];
अटल पूर्णांक pcm_channels[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 2पूर्ण;
अटल पूर्णांक effect[SNDRV_CARDS];

#अगर_घोषित SNDRV_STB
#घोषणा PFX "interwave-stb: "
#घोषणा INTERWAVE_DRIVER	"snd_interwave_stb"
#घोषणा INTERWAVE_PNP_DRIVER	"interwave-stb"
#अन्यथा
#घोषणा PFX "interwave: "
#घोषणा INTERWAVE_DRIVER	"snd_interwave"
#घोषणा INTERWAVE_PNP_DRIVER	"interwave"
#पूर्ण_अगर

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for InterWave soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for InterWave soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable InterWave soundcard.");
#अगर_घोषित CONFIG_PNP
module_param_array(isapnp, bool, शून्य, 0444);
MODULE_PARM_DESC(isapnp, "ISA PnP detection for specified soundcard.");
#पूर्ण_अगर
module_param_hw_array(port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(port, "Port # for InterWave driver.");
#अगर_घोषित SNDRV_STB
module_param_hw_array(port_tc, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(port_tc, "Tone control (TEA6330T - i2c bus) port # for InterWave driver.");
#पूर्ण_अगर
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(irq, "IRQ # for InterWave driver.");
module_param_hw_array(dma1, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(dma1, "DMA1 # for InterWave driver.");
module_param_hw_array(dma2, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(dma2, "DMA2 # for InterWave driver.");
module_param_array(joystick_dac, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(joystick_dac, "Joystick DAC level 0.59V-4.52V or 0.389V-2.98V for InterWave driver.");
module_param_array(midi, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(midi, "MIDI UART enable for InterWave driver.");
module_param_array(pcm_channels, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(pcm_channels, "Reserved PCM channels for InterWave driver.");
module_param_array(effect, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(effect, "Effects enable for InterWave driver.");

काष्ठा snd_पूर्णांकerwave अणु
	पूर्णांक irq;
	काष्ठा snd_card *card;
	काष्ठा snd_gus_card *gus;
	काष्ठा snd_wss *wss;
#अगर_घोषित SNDRV_STB
	काष्ठा resource *i2c_res;
#पूर्ण_अगर
	अचिन्हित लघु gus_status_reg;
	अचिन्हित लघु pcm_status_reg;
#अगर_घोषित CONFIG_PNP
	काष्ठा pnp_dev *dev;
#अगर_घोषित SNDRV_STB
	काष्ठा pnp_dev *devtc;
#पूर्ण_अगर
#पूर्ण_अगर
पूर्ण;


#अगर_घोषित CONFIG_PNP
अटल पूर्णांक isa_रेजिस्टरed;
अटल पूर्णांक pnp_रेजिस्टरed;

अटल स्थिर काष्ठा pnp_card_device_id snd_पूर्णांकerwave_pnpids[] = अणु
#अगर_अघोषित SNDRV_STB
	/* Gravis UltraSound Plug & Play */
	अणु .id = "GRV0001", .devs = अणु अणु .id = "GRV0000" पूर्ण पूर्ण पूर्ण,
	/* STB SoundRage32 */
	अणु .id = "STB011a", .devs = अणु अणु .id = "STB0010" पूर्ण पूर्ण पूर्ण,
	/* MED3210 */
	अणु .id = "DXP3201", .devs = अणु अणु .id = "DXP0010" पूर्ण पूर्ण पूर्ण,
	/* Dynasonic Pro */
	/* This device also have CDC1117:DynaSonix Pro Audio Effects Processor */
	अणु .id = "CDC1111", .devs = अणु अणु .id = "CDC1112" पूर्ण पूर्ण पूर्ण,
	/* Panasonic PCA761AW Audio Card */
	अणु .id = "ADV55ff", .devs = अणु अणु .id = "ADV0010" पूर्ण पूर्ण पूर्ण,
	/* InterWave STB without TEA6330T */
	अणु .id = "ADV550a", .devs = अणु अणु .id = "ADV0010" पूर्ण पूर्ण पूर्ण,
#अन्यथा
	/* InterWave STB with TEA6330T */
	अणु .id = "ADV550a", .devs = अणु अणु .id = "ADV0010" पूर्ण, अणु .id = "ADV0015" पूर्ण पूर्ण पूर्ण,
#पूर्ण_अगर
	अणु .id = "" पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pnp_card, snd_पूर्णांकerwave_pnpids);

#पूर्ण_अगर /* CONFIG_PNP */


#अगर_घोषित SNDRV_STB
अटल व्योम snd_पूर्णांकerwave_i2c_setlines(काष्ठा snd_i2c_bus *bus, पूर्णांक ctrl, पूर्णांक data)
अणु
	अचिन्हित दीर्घ port = bus->निजी_value;

#अगर 0
	prपूर्णांकk(KERN_DEBUG "i2c_setlines - 0x%lx <- %i,%i\n", port, ctrl, data);
#पूर्ण_अगर
	outb((data << 1) | ctrl, port);
	udelay(10);
पूर्ण

अटल पूर्णांक snd_पूर्णांकerwave_i2c_अ_लोlockline(काष्ठा snd_i2c_bus *bus)
अणु
	अचिन्हित दीर्घ port = bus->निजी_value;
	अचिन्हित अक्षर res;

	res = inb(port) & 1;
#अगर 0
	prपूर्णांकk(KERN_DEBUG "i2c_getclockline - 0x%lx -> %i\n", port, res);
#पूर्ण_अगर
	वापस res;
पूर्ण

अटल पूर्णांक snd_पूर्णांकerwave_i2c_getdataline(काष्ठा snd_i2c_bus *bus, पूर्णांक ack)
अणु
	अचिन्हित दीर्घ port = bus->निजी_value;
	अचिन्हित अक्षर res;

	अगर (ack)
		udelay(10);
	res = (inb(port) & 2) >> 1;
#अगर 0
	prपूर्णांकk(KERN_DEBUG "i2c_getdataline - 0x%lx -> %i\n", port, res);
#पूर्ण_अगर
	वापस res;
पूर्ण

अटल काष्ठा snd_i2c_bit_ops snd_पूर्णांकerwave_i2c_bit_ops = अणु
	.setlines = snd_पूर्णांकerwave_i2c_setlines,
	.अ_लोlock = snd_पूर्णांकerwave_i2c_अ_लोlockline,
	.getdata  = snd_पूर्णांकerwave_i2c_getdataline,
पूर्ण;

अटल पूर्णांक snd_पूर्णांकerwave_detect_stb(काष्ठा snd_पूर्णांकerwave *iwcard,
				    काष्ठा snd_gus_card *gus, पूर्णांक dev,
				    काष्ठा snd_i2c_bus **rbus)
अणु
	अचिन्हित दीर्घ port;
	काष्ठा snd_i2c_bus *bus;
	काष्ठा snd_card *card = iwcard->card;
	अक्षर name[32];
	पूर्णांक err;

	*rbus = शून्य;
	port = port_tc[dev];
	अगर (port == SNDRV_AUTO_PORT) अणु
		port = 0x350;
		अगर (gus->gf1.port == 0x250) अणु
			port = 0x360;
		पूर्ण
		जबतक (port <= 0x380) अणु
			अगर ((iwcard->i2c_res = request_region(port, 1, "InterWave (I2C bus)")) != शून्य)
				अवरोध;
			port += 0x10;
		पूर्ण
	पूर्ण अन्यथा अणु
		iwcard->i2c_res = request_region(port, 1, "InterWave (I2C bus)");
	पूर्ण
	अगर (iwcard->i2c_res == शून्य) अणु
		snd_prपूर्णांकk(KERN_ERR "interwave: can't grab i2c bus port\n");
		वापस -ENODEV;
	पूर्ण

	प्र_लिखो(name, "InterWave-%i", card->number);
	अगर ((err = snd_i2c_bus_create(card, name, शून्य, &bus)) < 0)
		वापस err;
	bus->निजी_value = port;
	bus->hw_ops.bit = &snd_पूर्णांकerwave_i2c_bit_ops;
	अगर ((err = snd_tea6330t_detect(bus, 0)) < 0)
		वापस err;
	*rbus = bus;
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक snd_पूर्णांकerwave_detect(काष्ठा snd_पूर्णांकerwave *iwcard,
				काष्ठा snd_gus_card *gus,
				पूर्णांक dev
#अगर_घोषित SNDRV_STB
				, काष्ठा snd_i2c_bus **rbus
#पूर्ण_अगर
				          )
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर rev1, rev2;
	पूर्णांक d;

	snd_gf1_i_ग_लिखो8(gus, SNDRV_GF1_GB_RESET, 0);	/* reset GF1 */
	अगर (((d = snd_gf1_i_look8(gus, SNDRV_GF1_GB_RESET)) & 0x07) != 0) अणु
		snd_prपूर्णांकdd("[0x%lx] check 1 failed - 0x%x\n", gus->gf1.port, d);
		वापस -ENODEV;
	पूर्ण
	udelay(160);
	snd_gf1_i_ग_लिखो8(gus, SNDRV_GF1_GB_RESET, 1);	/* release reset */
	udelay(160);
	अगर (((d = snd_gf1_i_look8(gus, SNDRV_GF1_GB_RESET)) & 0x07) != 1) अणु
		snd_prपूर्णांकdd("[0x%lx] check 2 failed - 0x%x\n", gus->gf1.port, d);
		वापस -ENODEV;
	पूर्ण
	spin_lock_irqsave(&gus->reg_lock, flags);
	rev1 = snd_gf1_look8(gus, SNDRV_GF1_GB_VERSION_NUMBER);
	snd_gf1_ग_लिखो8(gus, SNDRV_GF1_GB_VERSION_NUMBER, ~rev1);
	rev2 = snd_gf1_look8(gus, SNDRV_GF1_GB_VERSION_NUMBER);
	snd_gf1_ग_लिखो8(gus, SNDRV_GF1_GB_VERSION_NUMBER, rev1);
	spin_unlock_irqrestore(&gus->reg_lock, flags);
	snd_prपूर्णांकdd("[0x%lx] InterWave check - rev1=0x%x, rev2=0x%x\n", gus->gf1.port, rev1, rev2);
	अगर ((rev1 & 0xf0) == (rev2 & 0xf0) &&
	    (rev1 & 0x0f) != (rev2 & 0x0f)) अणु
		snd_prपूर्णांकdd("[0x%lx] InterWave check - passed\n", gus->gf1.port);
		gus->पूर्णांकerwave = 1;
		म_नकल(gus->card->लघुname, "AMD InterWave");
		gus->revision = rev1 >> 4;
#अगर_अघोषित SNDRV_STB
		वापस 0;	/* ok.. We have an InterWave board */
#अन्यथा
		वापस snd_पूर्णांकerwave_detect_stb(iwcard, gus, dev, rbus);
#पूर्ण_अगर
	पूर्ण
	snd_prपूर्णांकdd("[0x%lx] InterWave check - failed\n", gus->gf1.port);
	वापस -ENODEV;
पूर्ण

अटल irqवापस_t snd_पूर्णांकerwave_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_पूर्णांकerwave *iwcard = dev_id;
	पूर्णांक loop, max = 5;
	पूर्णांक handled = 0;

	करो अणु
		loop = 0;
		अगर (inb(iwcard->gus_status_reg)) अणु
			handled = 1;
			snd_gus_पूर्णांकerrupt(irq, iwcard->gus);
			loop++;
		पूर्ण
		अगर (inb(iwcard->pcm_status_reg) & 0x01) अणु	/* IRQ bit is set? */
			handled = 1;
			snd_wss_पूर्णांकerrupt(irq, iwcard->wss);
			loop++;
		पूर्ण
	पूर्ण जबतक (loop && --max > 0);
	वापस IRQ_RETVAL(handled);
पूर्ण

अटल व्योम snd_पूर्णांकerwave_reset(काष्ठा snd_gus_card *gus)
अणु
	snd_gf1_ग_लिखो8(gus, SNDRV_GF1_GB_RESET, 0x00);
	udelay(160);
	snd_gf1_ग_लिखो8(gus, SNDRV_GF1_GB_RESET, 0x01);
	udelay(160);
पूर्ण

अटल व्योम snd_पूर्णांकerwave_bank_sizes(काष्ठा snd_gus_card *gus, पूर्णांक *sizes)
अणु
	अचिन्हित पूर्णांक idx;
	अचिन्हित पूर्णांक local;
	अचिन्हित अक्षर d;

	क्रम (idx = 0; idx < 4; idx++) अणु
		sizes[idx] = 0;
		d = 0x55;
		क्रम (local = idx << 22;
		     local < (idx << 22) + 0x400000;
		     local += 0x40000, d++) अणु
			snd_gf1_poke(gus, local, d);
			snd_gf1_poke(gus, local + 1, d + 1);
#अगर 0
			prपूर्णांकk(KERN_DEBUG "d = 0x%x, local = 0x%x, "
			       "local + 1 = 0x%x, idx << 22 = 0x%x\n",
			       d,
			       snd_gf1_peek(gus, local),
			       snd_gf1_peek(gus, local + 1),
			       snd_gf1_peek(gus, idx << 22));
#पूर्ण_अगर
			अगर (snd_gf1_peek(gus, local) != d ||
			    snd_gf1_peek(gus, local + 1) != d + 1 ||
			    snd_gf1_peek(gus, idx << 22) != 0x55)
				अवरोध;
			sizes[idx]++;
		पूर्ण
	पूर्ण
#अगर 0
	prपूर्णांकk(KERN_DEBUG "sizes: %i %i %i %i\n",
	       sizes[0], sizes[1], sizes[2], sizes[3]);
#पूर्ण_अगर
पूर्ण

काष्ठा rom_hdr अणु
	/* 000 */ अचिन्हित अक्षर iwave[8];
	/* 008 */ अचिन्हित अक्षर rom_hdr_revision;
	/* 009 */ अचिन्हित अक्षर series_number;
	/* 010 */ अचिन्हित अक्षर series_name[16];
	/* 026 */ अचिन्हित अक्षर date[10];
	/* 036 */ अचिन्हित लघु venकरोr_revision_major;
	/* 038 */ अचिन्हित लघु venकरोr_revision_minor;
	/* 040 */ अचिन्हित पूर्णांक rom_size;
	/* 044 */ अचिन्हित अक्षर copyright[128];
	/* 172 */ अचिन्हित अक्षर venकरोr_name[64];
	/* 236 */ अचिन्हित अक्षर rom_description[128];
	/* 364 */ अचिन्हित अक्षर pad[147];
	/* 511 */ अचिन्हित अक्षर csum;
पूर्ण;

अटल व्योम snd_पूर्णांकerwave_detect_memory(काष्ठा snd_gus_card *gus)
अणु
	अटल स्थिर अचिन्हित पूर्णांक lmc[13] =
	अणु
		0x00000001, 0x00000101, 0x01010101, 0x00000401,
		0x04040401, 0x00040101, 0x04040101, 0x00000004,
		0x00000404, 0x04040404, 0x00000010, 0x00001010,
		0x10101010
	पूर्ण;

	पूर्णांक bank_pos, pages;
	अचिन्हित पूर्णांक i, lmct;
	पूर्णांक psizes[4];
	अचिन्हित अक्षर iwave[8];
	अचिन्हित अक्षर csum;

	snd_पूर्णांकerwave_reset(gus);
	snd_gf1_ग_लिखो8(gus, SNDRV_GF1_GB_GLOBAL_MODE, snd_gf1_पढ़ो8(gus, SNDRV_GF1_GB_GLOBAL_MODE) | 0x01);		/* enhanced mode */
	snd_gf1_ग_लिखो8(gus, SNDRV_GF1_GB_MEMORY_CONTROL, 0x01);	/* DRAM I/O cycles selected */
	snd_gf1_ग_लिखो16(gus, SNDRV_GF1_GW_MEMORY_CONFIG, (snd_gf1_look16(gus, SNDRV_GF1_GW_MEMORY_CONFIG) & 0xff10) | 0x004c);
	/* ok.. simple test of memory size */
	pages = 0;
	snd_gf1_poke(gus, 0, 0x55);
	snd_gf1_poke(gus, 1, 0xaa);
#अगर 1
	अगर (snd_gf1_peek(gus, 0) == 0x55 && snd_gf1_peek(gus, 1) == 0xaa)
#अन्यथा
	अगर (0)			/* ok.. क्रम testing of 0k RAM */
#पूर्ण_अगर
	अणु
		snd_पूर्णांकerwave_bank_sizes(gus, psizes);
		lmct = (psizes[3] << 24) | (psizes[2] << 16) |
		    (psizes[1] << 8) | psizes[0];
#अगर 0
		prपूर्णांकk(KERN_DEBUG "lmct = 0x%08x\n", lmct);
#पूर्ण_अगर
		क्रम (i = 0; i < ARRAY_SIZE(lmc); i++)
			अगर (lmct == lmc[i]) अणु
#अगर 0
				prपूर्णांकk(KERN_DEBUG "found !!! %i\n", i);
#पूर्ण_अगर
				snd_gf1_ग_लिखो16(gus, SNDRV_GF1_GW_MEMORY_CONFIG, (snd_gf1_look16(gus, SNDRV_GF1_GW_MEMORY_CONFIG) & 0xfff0) | i);
				snd_पूर्णांकerwave_bank_sizes(gus, psizes);
				अवरोध;
			पूर्ण
		अगर (i >= ARRAY_SIZE(lmc) && !gus->gf1.enh_mode)
			 snd_gf1_ग_लिखो16(gus, SNDRV_GF1_GW_MEMORY_CONFIG, (snd_gf1_look16(gus, SNDRV_GF1_GW_MEMORY_CONFIG) & 0xfff0) | 2);
		क्रम (i = 0; i < 4; i++) अणु
			gus->gf1.mem_alloc.banks_8[i].address =
			    gus->gf1.mem_alloc.banks_16[i].address = i << 22;
			gus->gf1.mem_alloc.banks_8[i].size =
			    gus->gf1.mem_alloc.banks_16[i].size = psizes[i] << 18;
			pages += psizes[i];
		पूर्ण
	पूर्ण
	pages <<= 18;
	gus->gf1.memory = pages;

	snd_gf1_ग_लिखो8(gus, SNDRV_GF1_GB_MEMORY_CONTROL, 0x03);	/* select ROM */
	snd_gf1_ग_लिखो16(gus, SNDRV_GF1_GW_MEMORY_CONFIG, (snd_gf1_look16(gus, SNDRV_GF1_GW_MEMORY_CONFIG) & 0xff1f) | (4 << 5));
	gus->gf1.rom_banks = 0;
	gus->gf1.rom_memory = 0;
	क्रम (bank_pos = 0; bank_pos < 16L * 1024L * 1024L; bank_pos += 4L * 1024L * 1024L) अणु
		क्रम (i = 0; i < 8; ++i)
			iwave[i] = snd_gf1_peek(gus, bank_pos + i);
		अगर (म_भेदन(iwave, "INTRWAVE", 8))
			जारी;	/* first check */
		csum = 0;
		क्रम (i = 0; i < माप(काष्ठा rom_hdr); i++)
			csum += snd_gf1_peek(gus, bank_pos + i);
		अगर (csum != 0)
			जारी;	/* not valid rom */
		gus->gf1.rom_banks++;
		gus->gf1.rom_present |= 1 << (bank_pos >> 22);
		gus->gf1.rom_memory = snd_gf1_peek(gus, bank_pos + 40) |
				     (snd_gf1_peek(gus, bank_pos + 41) << 8) |
				     (snd_gf1_peek(gus, bank_pos + 42) << 16) |
				     (snd_gf1_peek(gus, bank_pos + 43) << 24);
	पूर्ण
#अगर 0
	अगर (gus->gf1.rom_memory > 0) अणु
		अगर (gus->gf1.rom_banks == 1 && gus->gf1.rom_present == 8)
			gus->card->type = SNDRV_CARD_TYPE_IW_DYNASONIC;
	पूर्ण
#पूर्ण_अगर
	snd_gf1_ग_लिखो8(gus, SNDRV_GF1_GB_MEMORY_CONTROL, 0x00);	/* select RAM */

	अगर (!gus->gf1.enh_mode)
		snd_पूर्णांकerwave_reset(gus);
पूर्ण

अटल व्योम snd_पूर्णांकerwave_init(पूर्णांक dev, काष्ठा snd_gus_card *gus)
अणु
	अचिन्हित दीर्घ flags;

	/* ok.. some InterWave specअगरic initialization */
	spin_lock_irqsave(&gus->reg_lock, flags);
	snd_gf1_ग_लिखो8(gus, SNDRV_GF1_GB_SOUND_BLASTER_CONTROL, 0x00);
	snd_gf1_ग_लिखो8(gus, SNDRV_GF1_GB_COMPATIBILITY, 0x1f);
	snd_gf1_ग_लिखो8(gus, SNDRV_GF1_GB_DECODE_CONTROL, 0x49);
	snd_gf1_ग_लिखो8(gus, SNDRV_GF1_GB_VERSION_NUMBER, 0x11);
	snd_gf1_ग_लिखो8(gus, SNDRV_GF1_GB_MPU401_CONTROL_A, 0x00);
	snd_gf1_ग_लिखो8(gus, SNDRV_GF1_GB_MPU401_CONTROL_B, 0x30);
	snd_gf1_ग_लिखो8(gus, SNDRV_GF1_GB_EMULATION_IRQ, 0x00);
	spin_unlock_irqrestore(&gus->reg_lock, flags);
	gus->equal_irq = 1;
	gus->codec_flag = 1;
	gus->पूर्णांकerwave = 1;
	gus->max_flag = 1;
	gus->joystick_dac = joystick_dac[dev];

पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_पूर्णांकerwave_controls[] = अणु
WSS_DOUBLE("Master Playback Switch", 0,
		CS4231_LINE_LEFT_OUTPUT, CS4231_LINE_RIGHT_OUTPUT, 7, 7, 1, 1),
WSS_DOUBLE("Master Playback Volume", 0,
		CS4231_LINE_LEFT_OUTPUT, CS4231_LINE_RIGHT_OUTPUT, 0, 0, 31, 1),
WSS_DOUBLE("Mic Playback Switch", 0,
		CS4231_LEFT_MIC_INPUT, CS4231_RIGHT_MIC_INPUT, 7, 7, 1, 1),
WSS_DOUBLE("Mic Playback Volume", 0,
		CS4231_LEFT_MIC_INPUT, CS4231_RIGHT_MIC_INPUT, 0, 0, 31, 1)
पूर्ण;

अटल पूर्णांक snd_पूर्णांकerwave_mixer(काष्ठा snd_wss *chip)
अणु
	काष्ठा snd_card *card = chip->card;
	काष्ठा snd_ctl_elem_id id1, id2;
	अचिन्हित पूर्णांक idx;
	पूर्णांक err;

	स_रखो(&id1, 0, माप(id1));
	स_रखो(&id2, 0, माप(id2));
	id1.अगरace = id2.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
#अगर 0
	/* हटाओ mono microphone controls */
	म_नकल(id1.name, "Mic Playback Switch");
	अगर ((err = snd_ctl_हटाओ_id(card, &id1)) < 0)
		वापस err;
	म_नकल(id1.name, "Mic Playback Volume");
	अगर ((err = snd_ctl_हटाओ_id(card, &id1)) < 0)
		वापस err;
#पूर्ण_अगर
	/* add new master and mic controls */
	क्रम (idx = 0; idx < ARRAY_SIZE(snd_पूर्णांकerwave_controls); idx++)
		अगर ((err = snd_ctl_add(card, snd_ctl_new1(&snd_पूर्णांकerwave_controls[idx], chip))) < 0)
			वापस err;
	snd_wss_out(chip, CS4231_LINE_LEFT_OUTPUT, 0x9f);
	snd_wss_out(chip, CS4231_LINE_RIGHT_OUTPUT, 0x9f);
	snd_wss_out(chip, CS4231_LEFT_MIC_INPUT, 0x9f);
	snd_wss_out(chip, CS4231_RIGHT_MIC_INPUT, 0x9f);
	/* reassign AUXA to SYNTHESIZER */
	म_नकल(id1.name, "Aux Playback Switch");
	म_नकल(id2.name, "Synth Playback Switch");
	अगर ((err = snd_ctl_नाम_id(card, &id1, &id2)) < 0)
		वापस err;
	म_नकल(id1.name, "Aux Playback Volume");
	म_नकल(id2.name, "Synth Playback Volume");
	अगर ((err = snd_ctl_नाम_id(card, &id1, &id2)) < 0)
		वापस err;
	/* reassign AUXB to CD */
	म_नकल(id1.name, "Aux Playback Switch"); id1.index = 1;
	म_नकल(id2.name, "CD Playback Switch");
	अगर ((err = snd_ctl_नाम_id(card, &id1, &id2)) < 0)
		वापस err;
	म_नकल(id1.name, "Aux Playback Volume");
	म_नकल(id2.name, "CD Playback Volume");
	अगर ((err = snd_ctl_नाम_id(card, &id1, &id2)) < 0)
		वापस err;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PNP

अटल पूर्णांक snd_पूर्णांकerwave_pnp(पूर्णांक dev, काष्ठा snd_पूर्णांकerwave *iwcard,
			     काष्ठा pnp_card_link *card,
			     स्थिर काष्ठा pnp_card_device_id *id)
अणु
	काष्ठा pnp_dev *pdev;
	पूर्णांक err;

	iwcard->dev = pnp_request_card_device(card, id->devs[0].id, शून्य);
	अगर (iwcard->dev == शून्य)
		वापस -EBUSY;

#अगर_घोषित SNDRV_STB
	iwcard->devtc = pnp_request_card_device(card, id->devs[1].id, शून्य);
	अगर (iwcard->devtc == शून्य)
		वापस -EBUSY;
#पूर्ण_अगर
	/* Synth & Codec initialization */
	pdev = iwcard->dev;

	err = pnp_activate_dev(pdev);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "InterWave PnP configure failure (out of resources?)\n");
		वापस err;
	पूर्ण
	अगर (pnp_port_start(pdev, 0) + 0x100 != pnp_port_start(pdev, 1) ||
	    pnp_port_start(pdev, 0) + 0x10c != pnp_port_start(pdev, 2)) अणु
		snd_prपूर्णांकk(KERN_ERR "PnP configure failure (wrong ports)\n");
		वापस -ENOENT;
	पूर्ण
	port[dev] = pnp_port_start(pdev, 0);
	dma1[dev] = pnp_dma(pdev, 0);
	अगर (dma2[dev] >= 0)
		dma2[dev] = pnp_dma(pdev, 1);
	irq[dev] = pnp_irq(pdev, 0);
	snd_prपूर्णांकdd("isapnp IW: sb port=0x%llx, gf1 port=0x%llx, codec port=0x%llx\n",
			(अचिन्हित दीर्घ दीर्घ)pnp_port_start(pdev, 0),
			(अचिन्हित दीर्घ दीर्घ)pnp_port_start(pdev, 1),
			(अचिन्हित दीर्घ दीर्घ)pnp_port_start(pdev, 2));
	snd_prपूर्णांकdd("isapnp IW: dma1=%i, dma2=%i, irq=%i\n", dma1[dev], dma2[dev], irq[dev]);
#अगर_घोषित SNDRV_STB
	/* Tone Control initialization */
	pdev = iwcard->devtc;

	err = pnp_activate_dev(pdev);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "InterWave ToneControl PnP configure failure (out of resources?)\n");
		वापस err;
	पूर्ण
	port_tc[dev] = pnp_port_start(pdev, 0);
	snd_prपूर्णांकdd("isapnp IW: tone control port=0x%lx\n", port_tc[dev]);
#पूर्ण_अगर
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PNP */

अटल व्योम snd_पूर्णांकerwave_मुक्त(काष्ठा snd_card *card)
अणु
	काष्ठा snd_पूर्णांकerwave *iwcard = card->निजी_data;

	अगर (iwcard == शून्य)
		वापस;
#अगर_घोषित SNDRV_STB
	release_and_मुक्त_resource(iwcard->i2c_res);
#पूर्ण_अगर
	अगर (iwcard->irq >= 0)
		मुक्त_irq(iwcard->irq, (व्योम *)iwcard);
पूर्ण

अटल पूर्णांक snd_पूर्णांकerwave_card_new(काष्ठा device *pdev, पूर्णांक dev,
				  काष्ठा snd_card **cardp)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_पूर्णांकerwave *iwcard;
	पूर्णांक err;

	err = snd_card_new(pdev, index[dev], id[dev], THIS_MODULE,
			   माप(काष्ठा snd_पूर्णांकerwave), &card);
	अगर (err < 0)
		वापस err;
	iwcard = card->निजी_data;
	iwcard->card = card;
	iwcard->irq = -1;
	card->निजी_मुक्त = snd_पूर्णांकerwave_मुक्त;
	*cardp = card;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_पूर्णांकerwave_probe(काष्ठा snd_card *card, पूर्णांक dev)
अणु
	पूर्णांक xirq, xdma1, xdma2;
	काष्ठा snd_पूर्णांकerwave *iwcard = card->निजी_data;
	काष्ठा snd_wss *wss;
	काष्ठा snd_gus_card *gus;
#अगर_घोषित SNDRV_STB
	काष्ठा snd_i2c_bus *i2c_bus;
#पूर्ण_अगर
	अक्षर *str;
	पूर्णांक err;

	xirq = irq[dev];
	xdma1 = dma1[dev];
	xdma2 = dma2[dev];

	अगर ((err = snd_gus_create(card,
				  port[dev],
				  -xirq, xdma1, xdma2,
				  0, 32,
				  pcm_channels[dev], effect[dev], &gus)) < 0)
		वापस err;

	अगर ((err = snd_पूर्णांकerwave_detect(iwcard, gus, dev
#अगर_घोषित SNDRV_STB
            , &i2c_bus
#पूर्ण_अगर
	    )) < 0)
		वापस err;

	iwcard->gus_status_reg = gus->gf1.reg_irqstat;
	iwcard->pcm_status_reg = gus->gf1.port + 0x10c + 2;

	snd_पूर्णांकerwave_init(dev, gus);
	snd_पूर्णांकerwave_detect_memory(gus);
	अगर ((err = snd_gus_initialize(gus)) < 0)
		वापस err;

	अगर (request_irq(xirq, snd_पूर्णांकerwave_पूर्णांकerrupt, 0,
			"InterWave", iwcard)) अणु
		snd_prपूर्णांकk(KERN_ERR PFX "unable to grab IRQ %d\n", xirq);
		वापस -EBUSY;
	पूर्ण
	iwcard->irq = xirq;
	card->sync_irq = iwcard->irq;

	err = snd_wss_create(card,
			     gus->gf1.port + 0x10c, -1, xirq,
			     xdma2 < 0 ? xdma1 : xdma2, xdma1,
			     WSS_HW_INTERWAVE,
			     WSS_HWSHARE_IRQ |
			     WSS_HWSHARE_DMA1 |
			     WSS_HWSHARE_DMA2,
			     &wss);
	अगर (err < 0)
		वापस err;

	err = snd_wss_pcm(wss, 0);
	अगर (err < 0)
		वापस err;

	प्र_लिखो(wss->pcm->name + म_माप(wss->pcm->name), " rev %c",
		gus->revision + 'A');
	म_जोड़ो(wss->pcm->name, " (codec)");

	err = snd_wss_समयr(wss, 2);
	अगर (err < 0)
		वापस err;

	err = snd_wss_mixer(wss);
	अगर (err < 0)
		वापस err;

	अगर (pcm_channels[dev] > 0) अणु
		err = snd_gf1_pcm_new(gus, 1, 1);
		अगर (err < 0)
			वापस err;
	पूर्ण
	err = snd_पूर्णांकerwave_mixer(wss);
	अगर (err < 0)
		वापस err;

#अगर_घोषित SNDRV_STB
	अणु
		काष्ठा snd_ctl_elem_id id1, id2;
		स_रखो(&id1, 0, माप(id1));
		स_रखो(&id2, 0, माप(id2));
		id1.अगरace = id2.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
		म_नकल(id1.name, "Master Playback Switch");
		म_नकल(id2.name, id1.name);
		id2.index = 1;
		अगर ((err = snd_ctl_नाम_id(card, &id1, &id2)) < 0)
			वापस err;
		म_नकल(id1.name, "Master Playback Volume");
		म_नकल(id2.name, id1.name);
		अगर ((err = snd_ctl_नाम_id(card, &id1, &id2)) < 0)
			वापस err;
		अगर ((err = snd_tea6330t_update_mixer(card, i2c_bus, 0, 1)) < 0)
			वापस err;
	पूर्ण
#पूर्ण_अगर

	gus->uart_enable = midi[dev];
	अगर ((err = snd_gf1_rawmidi_new(gus, 0)) < 0)
		वापस err;

#अगर_अघोषित SNDRV_STB
	str = "AMD InterWave";
	अगर (gus->gf1.rom_banks == 1 && gus->gf1.rom_present == 8)
		str = "Dynasonic 3-D";
#अन्यथा
	str = "InterWave STB";
#पूर्ण_अगर
	म_नकल(card->driver, str);
	म_नकल(card->लघुname, str);
	प्र_लिखो(card->दीर्घname, "%s at 0x%lx, irq %i, dma %d",
		str,
		gus->gf1.port,
		xirq,
		xdma1);
	अगर (xdma2 >= 0)
		प्र_लिखो(card->दीर्घname + म_माप(card->दीर्घname), "&%d", xdma2);

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		वापस err;
	
	iwcard->wss = wss;
	iwcard->gus = gus;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_पूर्णांकerwave_isa_probe1(पूर्णांक dev, काष्ठा device *devptr)
अणु
	काष्ठा snd_card *card;
	पूर्णांक err;

	err = snd_पूर्णांकerwave_card_new(devptr, dev, &card);
	अगर (err < 0)
		वापस err;

	अगर ((err = snd_पूर्णांकerwave_probe(card, dev)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	dev_set_drvdata(devptr, card);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_पूर्णांकerwave_isa_match(काष्ठा device *pdev,
				   अचिन्हित पूर्णांक dev)
अणु
	अगर (!enable[dev])
		वापस 0;
#अगर_घोषित CONFIG_PNP
	अगर (isapnp[dev])
		वापस 0;
#पूर्ण_अगर
	वापस 1;
पूर्ण

अटल पूर्णांक snd_पूर्णांकerwave_isa_probe(काष्ठा device *pdev,
				   अचिन्हित पूर्णांक dev)
अणु
	पूर्णांक err;
	अटल स्थिर पूर्णांक possible_irqs[] = अणु5, 11, 12, 9, 7, 15, 3, -1पूर्ण;
	अटल स्थिर पूर्णांक possible_dmas[] = अणु0, 1, 3, 5, 6, 7, -1पूर्ण;

	अगर (irq[dev] == SNDRV_AUTO_IRQ) अणु
		अगर ((irq[dev] = snd_legacy_find_मुक्त_irq(possible_irqs)) < 0) अणु
			snd_prपूर्णांकk(KERN_ERR PFX "unable to find a free IRQ\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	अगर (dma1[dev] == SNDRV_AUTO_DMA) अणु
		अगर ((dma1[dev] = snd_legacy_find_मुक्त_dma(possible_dmas)) < 0) अणु
			snd_prपूर्णांकk(KERN_ERR PFX "unable to find a free DMA1\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	अगर (dma2[dev] == SNDRV_AUTO_DMA) अणु
		अगर ((dma2[dev] = snd_legacy_find_मुक्त_dma(possible_dmas)) < 0) अणु
			snd_prपूर्णांकk(KERN_ERR PFX "unable to find a free DMA2\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	अगर (port[dev] != SNDRV_AUTO_PORT)
		वापस snd_पूर्णांकerwave_isa_probe1(dev, pdev);
	अन्यथा अणु
		अटल स्थिर दीर्घ possible_ports[] = अणु0x210, 0x220, 0x230, 0x240, 0x250, 0x260पूर्ण;
		पूर्णांक i;
		क्रम (i = 0; i < ARRAY_SIZE(possible_ports); i++) अणु
			port[dev] = possible_ports[i];
			err = snd_पूर्णांकerwave_isa_probe1(dev, pdev);
			अगर (! err)
				वापस 0;
		पूर्ण
		वापस err;
	पूर्ण
पूर्ण

अटल व्योम snd_पूर्णांकerwave_isa_हटाओ(काष्ठा device *devptr, अचिन्हित पूर्णांक dev)
अणु
	snd_card_मुक्त(dev_get_drvdata(devptr));
पूर्ण

अटल काष्ठा isa_driver snd_पूर्णांकerwave_driver = अणु
	.match		= snd_पूर्णांकerwave_isa_match,
	.probe		= snd_पूर्णांकerwave_isa_probe,
	.हटाओ		= snd_पूर्णांकerwave_isa_हटाओ,
	/* FIXME: suspend,resume */
	.driver		= अणु
		.name	= INTERWAVE_DRIVER
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_PNP
अटल पूर्णांक snd_पूर्णांकerwave_pnp_detect(काष्ठा pnp_card_link *pcard,
				    स्थिर काष्ठा pnp_card_device_id *pid)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	पूर्णांक res;

	क्रम ( ; dev < SNDRV_CARDS; dev++) अणु
		अगर (enable[dev] && isapnp[dev])
			अवरोध;
	पूर्ण
	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;
				
	res = snd_पूर्णांकerwave_card_new(&pcard->card->dev, dev, &card);
	अगर (res < 0)
		वापस res;

	अगर ((res = snd_पूर्णांकerwave_pnp(dev, card->निजी_data, pcard, pid)) < 0) अणु
		snd_card_मुक्त(card);
		वापस res;
	पूर्ण
	अगर ((res = snd_पूर्णांकerwave_probe(card, dev)) < 0) अणु
		snd_card_मुक्त(card);
		वापस res;
	पूर्ण
	pnp_set_card_drvdata(pcard, card);
	dev++;
	वापस 0;
पूर्ण

अटल व्योम snd_पूर्णांकerwave_pnp_हटाओ(काष्ठा pnp_card_link *pcard)
अणु
	snd_card_मुक्त(pnp_get_card_drvdata(pcard));
	pnp_set_card_drvdata(pcard, शून्य);
पूर्ण

अटल काष्ठा pnp_card_driver पूर्णांकerwave_pnpc_driver = अणु
	.flags = PNP_DRIVER_RES_DISABLE,
	.name = INTERWAVE_PNP_DRIVER,
	.id_table = snd_पूर्णांकerwave_pnpids,
	.probe = snd_पूर्णांकerwave_pnp_detect,
	.हटाओ = snd_पूर्णांकerwave_pnp_हटाओ,
	/* FIXME: suspend,resume */
पूर्ण;

#पूर्ण_अगर /* CONFIG_PNP */

अटल पूर्णांक __init alsa_card_पूर्णांकerwave_init(व्योम)
अणु
	पूर्णांक err;

	err = isa_रेजिस्टर_driver(&snd_पूर्णांकerwave_driver, SNDRV_CARDS);
#अगर_घोषित CONFIG_PNP
	अगर (!err)
		isa_रेजिस्टरed = 1;

	err = pnp_रेजिस्टर_card_driver(&पूर्णांकerwave_pnpc_driver);
	अगर (!err)
		pnp_रेजिस्टरed = 1;

	अगर (isa_रेजिस्टरed)
		err = 0;
#पूर्ण_अगर
	वापस err;
पूर्ण

अटल व्योम __निकास alsa_card_पूर्णांकerwave_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_PNP
	अगर (pnp_रेजिस्टरed)
		pnp_unरेजिस्टर_card_driver(&पूर्णांकerwave_pnpc_driver);
	अगर (isa_रेजिस्टरed)
#पूर्ण_अगर
		isa_unरेजिस्टर_driver(&snd_पूर्णांकerwave_driver);
पूर्ण

module_init(alsa_card_पूर्णांकerwave_init)
module_निकास(alsa_card_पूर्णांकerwave_निकास)
