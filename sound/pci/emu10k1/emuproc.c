<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *                   Creative Lअसल, Inc.
 *  Routines क्रम control of EMU10K1 chips / proc पूर्णांकerface routines
 *
 *  Copyright (c) by James Courtier-Dutton <James@superbug.co.uk>
 *  	Added EMU 1010 support.
 *
 *  BUGS:
 *    --
 *
 *  TODO:
 *    --
 */

#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <sound/core.h>
#समावेश <sound/emu10k1.h>
#समावेश "p16v.h"

अटल व्योम snd_emu10k1_proc_spdअगर_status(काष्ठा snd_emu10k1 * emu,
					  काष्ठा snd_info_buffer *buffer,
					  अक्षर *title,
					  पूर्णांक status_reg,
					  पूर्णांक rate_reg)
अणु
	अटल स्थिर अक्षर * स्थिर clkaccy[4] = अणु "1000ppm", "50ppm", "variable", "unknown" पूर्ण;
	अटल स्थिर पूर्णांक samplerate[16] = अणु 44100, 1, 48000, 32000, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 पूर्ण;
	अटल स्थिर अक्षर * स्थिर channel[16] = अणु "unspec", "left", "right", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15" पूर्ण;
	अटल स्थिर अक्षर * स्थिर emphasis[8] = अणु "none", "50/15 usec 2 channel", "2", "3", "4", "5", "6", "7" पूर्ण;
	अचिन्हित पूर्णांक status, rate = 0;
	
	status = snd_emu10k1_ptr_पढ़ो(emu, status_reg, 0);

	snd_iम_लिखो(buffer, "\n%s\n", title);

	अगर (status != 0xffffffff) अणु
		snd_iम_लिखो(buffer, "Professional Mode     : %s\n", (status & SPCS_PROFESSIONAL) ? "yes" : "no");
		snd_iम_लिखो(buffer, "Not Audio Data        : %s\n", (status & SPCS_NOTAUDIODATA) ? "yes" : "no");
		snd_iम_लिखो(buffer, "Copyright             : %s\n", (status & SPCS_COPYRIGHT) ? "yes" : "no");
		snd_iम_लिखो(buffer, "Emphasis              : %s\n", emphasis[(status & SPCS_EMPHASISMASK) >> 3]);
		snd_iम_लिखो(buffer, "Mode                  : %i\n", (status & SPCS_MODEMASK) >> 6);
		snd_iम_लिखो(buffer, "Category Code         : 0x%x\n", (status & SPCS_CATEGORYCODEMASK) >> 8);
		snd_iम_लिखो(buffer, "Generation Status     : %s\n", status & SPCS_GENERATIONSTATUS ? "original" : "copy");
		snd_iम_लिखो(buffer, "Source Mask           : %i\n", (status & SPCS_SOURCENUMMASK) >> 16);
		snd_iम_लिखो(buffer, "Channel Number        : %s\n", channel[(status & SPCS_CHANNELNUMMASK) >> 20]);
		snd_iम_लिखो(buffer, "Sample Rate           : %iHz\n", samplerate[(status & SPCS_SAMPLERATEMASK) >> 24]);
		snd_iम_लिखो(buffer, "Clock Accuracy        : %s\n", clkaccy[(status & SPCS_CLKACCYMASK) >> 28]);

		अगर (rate_reg > 0) अणु
			rate = snd_emu10k1_ptr_पढ़ो(emu, rate_reg, 0);
			snd_iम_लिखो(buffer, "S/PDIF Valid          : %s\n", rate & SRCS_SPDIFVALID ? "on" : "off");
			snd_iम_लिखो(buffer, "S/PDIF Locked         : %s\n", rate & SRCS_SPDIFLOCKED ? "on" : "off");
			snd_iम_लिखो(buffer, "Rate Locked           : %s\n", rate & SRCS_RATELOCKED ? "on" : "off");
			/* From ((Rate * 48000 ) / 262144); */
			snd_iम_लिखो(buffer, "Estimated Sample Rate : %d\n", ((rate & 0xFFFFF ) * 375) >> 11); 
		पूर्ण
	पूर्ण अन्यथा अणु
		snd_iम_लिखो(buffer, "No signal detected.\n");
	पूर्ण

पूर्ण

अटल व्योम snd_emu10k1_proc_पढ़ो(काष्ठा snd_info_entry *entry, 
				  काष्ठा snd_info_buffer *buffer)
अणु
	/* FIXME - output names are in emufx.c too */
	अटल स्थिर अक्षर * स्थिर creative_outs[32] = अणु
		/* 00 */ "AC97 Left",
		/* 01 */ "AC97 Right",
		/* 02 */ "Optical IEC958 Left",
		/* 03 */ "Optical IEC958 Right",
		/* 04 */ "Center",
		/* 05 */ "LFE",
		/* 06 */ "Headphone Left",
		/* 07 */ "Headphone Right",
		/* 08 */ "Surround Left",
		/* 09 */ "Surround Right",
		/* 10 */ "PCM Capture Left",
		/* 11 */ "PCM Capture Right",
		/* 12 */ "MIC Capture",
		/* 13 */ "AC97 Surround Left",
		/* 14 */ "AC97 Surround Right",
		/* 15 */ "???",
		/* 16 */ "???",
		/* 17 */ "Analog Center",
		/* 18 */ "Analog LFE",
		/* 19 */ "???",
		/* 20 */ "???",
		/* 21 */ "???",
		/* 22 */ "???",
		/* 23 */ "???",
		/* 24 */ "???",
		/* 25 */ "???",
		/* 26 */ "???",
		/* 27 */ "???",
		/* 28 */ "???",
		/* 29 */ "???",
		/* 30 */ "???",
		/* 31 */ "???"
	पूर्ण;

	अटल स्थिर अक्षर * स्थिर audigy_outs[64] = अणु
		/* 00 */ "Digital Front Left",
		/* 01 */ "Digital Front Right",
		/* 02 */ "Digital Center",
		/* 03 */ "Digital LEF",
		/* 04 */ "Headphone Left",
		/* 05 */ "Headphone Right",
		/* 06 */ "Digital Rear Left",
		/* 07 */ "Digital Rear Right",
		/* 08 */ "Front Left",
		/* 09 */ "Front Right",
		/* 10 */ "Center",
		/* 11 */ "LFE",
		/* 12 */ "???",
		/* 13 */ "???",
		/* 14 */ "Rear Left",
		/* 15 */ "Rear Right",
		/* 16 */ "AC97 Front Left",
		/* 17 */ "AC97 Front Right",
		/* 18 */ "ADC Capture Left",
		/* 19 */ "ADC Capture Right",
		/* 20 */ "???",
		/* 21 */ "???",
		/* 22 */ "???",
		/* 23 */ "???",
		/* 24 */ "???",
		/* 25 */ "???",
		/* 26 */ "???",
		/* 27 */ "???",
		/* 28 */ "???",
		/* 29 */ "???",
		/* 30 */ "???",
		/* 31 */ "???",
		/* 32 */ "FXBUS2_0",
		/* 33 */ "FXBUS2_1",
		/* 34 */ "FXBUS2_2",
		/* 35 */ "FXBUS2_3",
		/* 36 */ "FXBUS2_4",
		/* 37 */ "FXBUS2_5",
		/* 38 */ "FXBUS2_6",
		/* 39 */ "FXBUS2_7",
		/* 40 */ "FXBUS2_8",
		/* 41 */ "FXBUS2_9",
		/* 42 */ "FXBUS2_10",
		/* 43 */ "FXBUS2_11",
		/* 44 */ "FXBUS2_12",
		/* 45 */ "FXBUS2_13",
		/* 46 */ "FXBUS2_14",
		/* 47 */ "FXBUS2_15",
		/* 48 */ "FXBUS2_16",
		/* 49 */ "FXBUS2_17",
		/* 50 */ "FXBUS2_18",
		/* 51 */ "FXBUS2_19",
		/* 52 */ "FXBUS2_20",
		/* 53 */ "FXBUS2_21",
		/* 54 */ "FXBUS2_22",
		/* 55 */ "FXBUS2_23",
		/* 56 */ "FXBUS2_24",
		/* 57 */ "FXBUS2_25",
		/* 58 */ "FXBUS2_26",
		/* 59 */ "FXBUS2_27",
		/* 60 */ "FXBUS2_28",
		/* 61 */ "FXBUS2_29",
		/* 62 */ "FXBUS2_30",
		/* 63 */ "FXBUS2_31"
	पूर्ण;

	काष्ठा snd_emu10k1 *emu = entry->निजी_data;
	अचिन्हित पूर्णांक val, val1;
	पूर्णांक nefx = emu->audigy ? 64 : 32;
	स्थिर अक्षर * स्थिर *outमाला_दो = emu->audigy ? audigy_outs : creative_outs;
	पूर्णांक idx;
	
	snd_iम_लिखो(buffer, "EMU10K1\n\n");
	snd_iम_लिखो(buffer, "Card                  : %s\n",
		    emu->audigy ? "Audigy" : (emu->card_capabilities->ecard ? "EMU APS" : "Creative"));
	snd_iम_लिखो(buffer, "Internal TRAM (words) : 0x%x\n", emu->fx8010.itram_size);
	snd_iम_लिखो(buffer, "External TRAM (words) : 0x%x\n", (पूर्णांक)emu->fx8010.etram_pages.bytes / 2);
	snd_iम_लिखो(buffer, "\n");
	snd_iम_लिखो(buffer, "Effect Send Routing   :\n");
	क्रम (idx = 0; idx < NUM_G; idx++) अणु
		val = emu->audigy ?
			snd_emu10k1_ptr_पढ़ो(emu, A_FXRT1, idx) :
			snd_emu10k1_ptr_पढ़ो(emu, FXRT, idx);
		val1 = emu->audigy ?
			snd_emu10k1_ptr_पढ़ो(emu, A_FXRT2, idx) :
			0;
		अगर (emu->audigy) अणु
			snd_iम_लिखो(buffer, "Ch%i: A=%i, B=%i, C=%i, D=%i, ",
				idx,
				val & 0x3f,
				(val >> 8) & 0x3f,
				(val >> 16) & 0x3f,
				(val >> 24) & 0x3f);
			snd_iम_लिखो(buffer, "E=%i, F=%i, G=%i, H=%i\n",
				val1 & 0x3f,
				(val1 >> 8) & 0x3f,
				(val1 >> 16) & 0x3f,
				(val1 >> 24) & 0x3f);
		पूर्ण अन्यथा अणु
			snd_iम_लिखो(buffer, "Ch%i: A=%i, B=%i, C=%i, D=%i\n",
				idx,
				(val >> 16) & 0x0f,
				(val >> 20) & 0x0f,
				(val >> 24) & 0x0f,
				(val >> 28) & 0x0f);
		पूर्ण
	पूर्ण
	snd_iम_लिखो(buffer, "\nCaptured FX Outputs   :\n");
	क्रम (idx = 0; idx < nefx; idx++) अणु
		अगर (emu->efx_voices_mask[idx/32] & (1 << (idx%32)))
			snd_iम_लिखो(buffer, "  Output %02i [%s]\n", idx, outमाला_दो[idx]);
	पूर्ण
	snd_iम_लिखो(buffer, "\nAll FX Outputs        :\n");
	क्रम (idx = 0; idx < (emu->audigy ? 64 : 32); idx++)
		snd_iम_लिखो(buffer, "  Output %02i [%s]\n", idx, outमाला_दो[idx]);
पूर्ण

अटल व्योम snd_emu10k1_proc_spdअगर_पढ़ो(काष्ठा snd_info_entry *entry, 
				  काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_emu10k1 *emu = entry->निजी_data;
	u32 value;
	u32 value2;
	u32 rate;

	अगर (emu->card_capabilities->emu_model) अणु
		snd_emu1010_fpga_पढ़ो(emu, 0x38, &value);
		अगर ((value & 0x1) == 0) अणु
			snd_emu1010_fpga_पढ़ो(emu, 0x2a, &value);
			snd_emu1010_fpga_पढ़ो(emu, 0x2b, &value2);
			rate = 0x1770000 / (((value << 5) | value2)+1);	
			snd_iम_लिखो(buffer, "ADAT Locked : %u\n", rate);
		पूर्ण अन्यथा अणु
			snd_iम_लिखो(buffer, "ADAT Unlocked\n");
		पूर्ण
		snd_emu1010_fpga_पढ़ो(emu, 0x20, &value);
		अगर ((value & 0x4) == 0) अणु
			snd_emu1010_fpga_पढ़ो(emu, 0x28, &value);
			snd_emu1010_fpga_पढ़ो(emu, 0x29, &value2);
			rate = 0x1770000 / (((value << 5) | value2)+1);	
			snd_iम_लिखो(buffer, "SPDIF Locked : %d\n", rate);
		पूर्ण अन्यथा अणु
			snd_iम_लिखो(buffer, "SPDIF Unlocked\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		snd_emu10k1_proc_spdअगर_status(emu, buffer, "CD-ROM S/PDIF In", CDCS, CDSRCS);
		snd_emu10k1_proc_spdअगर_status(emu, buffer, "Optical or Coax S/PDIF In", GPSCS, GPSRCS);
	पूर्ण
#अगर 0
	val = snd_emu10k1_ptr_पढ़ो(emu, ZVSRCS, 0);
	snd_iम_लिखो(buffer, "\nZoomed Video\n");
	snd_iम_लिखो(buffer, "Rate Locked           : %s\n", val & SRCS_RATELOCKED ? "on" : "off");
	snd_iम_लिखो(buffer, "Estimated Sample Rate : 0x%x\n", val & SRCS_ESTSAMPLERATE);
#पूर्ण_अगर
पूर्ण

अटल व्योम snd_emu10k1_proc_rates_पढ़ो(काष्ठा snd_info_entry *entry, 
				  काष्ठा snd_info_buffer *buffer)
अणु
	अटल स्थिर पूर्णांक samplerate[8] = अणु 44100, 48000, 96000, 192000, 4, 5, 6, 7 पूर्ण;
	काष्ठा snd_emu10k1 *emu = entry->निजी_data;
	अचिन्हित पूर्णांक val, पंचांगp, n;
	val = snd_emu10k1_ptr20_पढ़ो(emu, CAPTURE_RATE_STATUS, 0);
	क्रम (n = 0; n < 4; n++) अणु
		पंचांगp = val >> (16 + (n*4));
		अगर (पंचांगp & 0x8) snd_iम_लिखो(buffer, "Channel %d: Rate=%d\n", n, samplerate[पंचांगp & 0x7]);
		अन्यथा snd_iम_लिखो(buffer, "Channel %d: No input\n", n);
	पूर्ण
पूर्ण

अटल व्योम snd_emu10k1_proc_acode_पढ़ो(काष्ठा snd_info_entry *entry, 
				        काष्ठा snd_info_buffer *buffer)
अणु
	u32 pc;
	काष्ठा snd_emu10k1 *emu = entry->निजी_data;

	snd_iम_लिखो(buffer, "FX8010 Instruction List '%s'\n", emu->fx8010.name);
	snd_iम_लिखो(buffer, "  Code dump      :\n");
	क्रम (pc = 0; pc < (emu->audigy ? 1024 : 512); pc++) अणु
		u32 low, high;
			
		low = snd_emu10k1_efx_पढ़ो(emu, pc * 2);
		high = snd_emu10k1_efx_पढ़ो(emu, pc * 2 + 1);
		अगर (emu->audigy)
			snd_iम_लिखो(buffer, "    OP(0x%02x, 0x%03x, 0x%03x, 0x%03x, 0x%03x) /* 0x%04x: 0x%08x%08x */\n",
				    (high >> 24) & 0x0f,
				    (high >> 12) & 0x7ff,
				    (high >> 0) & 0x7ff,
				    (low >> 12) & 0x7ff,
				    (low >> 0) & 0x7ff,
				    pc,
				    high, low);
		अन्यथा
			snd_iम_लिखो(buffer, "    OP(0x%02x, 0x%03x, 0x%03x, 0x%03x, 0x%03x) /* 0x%04x: 0x%08x%08x */\n",
				    (high >> 20) & 0x0f,
				    (high >> 10) & 0x3ff,
				    (high >> 0) & 0x3ff,
				    (low >> 10) & 0x3ff,
				    (low >> 0) & 0x3ff,
				    pc,
				    high, low);
	पूर्ण
पूर्ण

#घोषणा TOTAL_SIZE_GPR		(0x100*4)
#घोषणा A_TOTAL_SIZE_GPR	(0x200*4)
#घोषणा TOTAL_SIZE_TANKMEM_DATA	(0xa0*4)
#घोषणा TOTAL_SIZE_TANKMEM_ADDR (0xa0*4)
#घोषणा A_TOTAL_SIZE_TANKMEM_DATA (0x100*4)
#घोषणा A_TOTAL_SIZE_TANKMEM_ADDR (0x100*4)
#घोषणा TOTAL_SIZE_CODE		(0x200*8)
#घोषणा A_TOTAL_SIZE_CODE	(0x400*8)

अटल sमाप_प्रकार snd_emu10k1_fx8010_पढ़ो(काष्ठा snd_info_entry *entry,
				       व्योम *file_निजी_data,
				       काष्ठा file *file, अक्षर __user *buf,
				       माप_प्रकार count, loff_t pos)
अणु
	काष्ठा snd_emu10k1 *emu = entry->निजी_data;
	अचिन्हित पूर्णांक offset;
	पूर्णांक tram_addr = 0;
	अचिन्हित पूर्णांक *पंचांगp;
	दीर्घ res;
	अचिन्हित पूर्णांक idx;
	
	अगर (!म_भेद(entry->name, "fx8010_tram_addr")) अणु
		offset = TANKMEMADDRREGBASE;
		tram_addr = 1;
	पूर्ण अन्यथा अगर (!म_भेद(entry->name, "fx8010_tram_data")) अणु
		offset = TANKMEMDATAREGBASE;
	पूर्ण अन्यथा अगर (!म_भेद(entry->name, "fx8010_code")) अणु
		offset = emu->audigy ? A_MICROCODEBASE : MICROCODEBASE;
	पूर्ण अन्यथा अणु
		offset = emu->audigy ? A_FXGPREGBASE : FXGPREGBASE;
	पूर्ण

	पंचांगp = kदो_स्मृति(count + 8, GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;
	क्रम (idx = 0; idx < ((pos & 3) + count + 3) >> 2; idx++) अणु
		अचिन्हित पूर्णांक val;
		val = snd_emu10k1_ptr_पढ़ो(emu, offset + idx + (pos >> 2), 0);
		अगर (tram_addr && emu->audigy) अणु
			val >>= 11;
			val |= snd_emu10k1_ptr_पढ़ो(emu, 0x100 + idx + (pos >> 2), 0) << 20;
		पूर्ण
		पंचांगp[idx] = val;
	पूर्ण
	अगर (copy_to_user(buf, ((अक्षर *)पंचांगp) + (pos & 3), count))
		res = -EFAULT;
	अन्यथा
		res = count;
	kमुक्त(पंचांगp);
	वापस res;
पूर्ण

अटल व्योम snd_emu10k1_proc_voices_पढ़ो(काष्ठा snd_info_entry *entry, 
				  काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_emu10k1 *emu = entry->निजी_data;
	काष्ठा snd_emu10k1_voice *voice;
	पूर्णांक idx;
	
	snd_iम_लिखो(buffer, "ch\tuse\tpcm\tefx\tsynth\tmidi\n");
	क्रम (idx = 0; idx < NUM_G; idx++) अणु
		voice = &emu->voices[idx];
		snd_iम_लिखो(buffer, "%i\t%i\t%i\t%i\t%i\t%i\n",
			idx,
			voice->use,
			voice->pcm,
			voice->efx,
			voice->synth,
			voice->midi);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SND_DEBUG
अटल व्योम snd_emu_proc_emu1010_reg_पढ़ो(काष्ठा snd_info_entry *entry,
				     काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_emu10k1 *emu = entry->निजी_data;
	u32 value;
	पूर्णांक i;
	snd_iम_लिखो(buffer, "EMU1010 Registers:\n\n");

	क्रम(i = 0; i < 0x40; i+=1) अणु
		snd_emu1010_fpga_पढ़ो(emu, i, &value);
		snd_iम_लिखो(buffer, "%02X: %08X, %02X\n", i, value, (value >> 8) & 0x7f);
	पूर्ण
पूर्ण

अटल व्योम snd_emu_proc_io_reg_पढ़ो(काष्ठा snd_info_entry *entry,
				     काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_emu10k1 *emu = entry->निजी_data;
	अचिन्हित दीर्घ value;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	snd_iम_लिखो(buffer, "IO Registers:\n\n");
	क्रम(i = 0; i < 0x40; i+=4) अणु
		spin_lock_irqsave(&emu->emu_lock, flags);
		value = inl(emu->port + i);
		spin_unlock_irqrestore(&emu->emu_lock, flags);
		snd_iम_लिखो(buffer, "%02X: %08lX\n", i, value);
	पूर्ण
पूर्ण

अटल व्योम snd_emu_proc_io_reg_ग_लिखो(काष्ठा snd_info_entry *entry,
                                      काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_emu10k1 *emu = entry->निजी_data;
	अचिन्हित दीर्घ flags;
	अक्षर line[64];
	u32 reg, val;
	जबतक (!snd_info_get_line(buffer, line, माप(line))) अणु
		अगर (माला_पूछो(line, "%x %x", &reg, &val) != 2)
			जारी;
		अगर (reg < 0x40 && val <= 0xffffffff) अणु
			spin_lock_irqsave(&emu->emu_lock, flags);
			outl(val, emu->port + (reg & 0xfffffffc));
			spin_unlock_irqrestore(&emu->emu_lock, flags);
		पूर्ण
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक snd_ptr_पढ़ो(काष्ठा snd_emu10k1 * emu,
				 अचिन्हित पूर्णांक iobase,
				 अचिन्हित पूर्णांक reg,
				 अचिन्हित पूर्णांक chn)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक regptr, val;

	regptr = (reg << 16) | chn;

	spin_lock_irqsave(&emu->emu_lock, flags);
	outl(regptr, emu->port + iobase + PTR);
	val = inl(emu->port + iobase + DATA);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
	वापस val;
पूर्ण

अटल व्योम snd_ptr_ग_लिखो(काष्ठा snd_emu10k1 *emu,
			  अचिन्हित पूर्णांक iobase,
			  अचिन्हित पूर्णांक reg,
			  अचिन्हित पूर्णांक chn,
			  अचिन्हित पूर्णांक data)
अणु
	अचिन्हित पूर्णांक regptr;
	अचिन्हित दीर्घ flags;

	regptr = (reg << 16) | chn;

	spin_lock_irqsave(&emu->emu_lock, flags);
	outl(regptr, emu->port + iobase + PTR);
	outl(data, emu->port + iobase + DATA);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
पूर्ण


अटल व्योम snd_emu_proc_ptr_reg_पढ़ो(काष्ठा snd_info_entry *entry,
				      काष्ठा snd_info_buffer *buffer, पूर्णांक iobase, पूर्णांक offset, पूर्णांक length, पूर्णांक voices)
अणु
	काष्ठा snd_emu10k1 *emu = entry->निजी_data;
	अचिन्हित दीर्घ value;
	पूर्णांक i,j;
	अगर (offset+length > 0xa0) अणु
		snd_iम_लिखो(buffer, "Input values out of range\n");
		वापस;
	पूर्ण
	snd_iम_लिखो(buffer, "Registers 0x%x\n", iobase);
	क्रम(i = offset; i < offset+length; i++) अणु
		snd_iम_लिखो(buffer, "%02X: ",i);
		क्रम (j = 0; j < voices; j++) अणु
			अगर(iobase == 0)
                		value = snd_ptr_पढ़ो(emu, 0, i, j);
			अन्यथा
                		value = snd_ptr_पढ़ो(emu, 0x20, i, j);
			snd_iम_लिखो(buffer, "%08lX ", value);
		पूर्ण
		snd_iम_लिखो(buffer, "\n");
	पूर्ण
पूर्ण

अटल व्योम snd_emu_proc_ptr_reg_ग_लिखो(काष्ठा snd_info_entry *entry,
				       काष्ठा snd_info_buffer *buffer, पूर्णांक iobase)
अणु
	काष्ठा snd_emu10k1 *emu = entry->निजी_data;
	अक्षर line[64];
	अचिन्हित पूर्णांक reg, channel_id , val;
	जबतक (!snd_info_get_line(buffer, line, माप(line))) अणु
		अगर (माला_पूछो(line, "%x %x %x", &reg, &channel_id, &val) != 3)
			जारी;
		अगर (reg < 0xa0 && val <= 0xffffffff && channel_id <= 3)
			snd_ptr_ग_लिखो(emu, iobase, reg, channel_id, val);
	पूर्ण
पूर्ण

अटल व्योम snd_emu_proc_ptr_reg_ग_लिखो00(काष्ठा snd_info_entry *entry,
					 काष्ठा snd_info_buffer *buffer)
अणु
	snd_emu_proc_ptr_reg_ग_लिखो(entry, buffer, 0);
पूर्ण

अटल व्योम snd_emu_proc_ptr_reg_ग_लिखो20(काष्ठा snd_info_entry *entry,
					 काष्ठा snd_info_buffer *buffer)
अणु
	snd_emu_proc_ptr_reg_ग_लिखो(entry, buffer, 0x20);
पूर्ण
	

अटल व्योम snd_emu_proc_ptr_reg_पढ़ो00a(काष्ठा snd_info_entry *entry,
					 काष्ठा snd_info_buffer *buffer)
अणु
	snd_emu_proc_ptr_reg_पढ़ो(entry, buffer, 0, 0, 0x40, 64);
पूर्ण

अटल व्योम snd_emu_proc_ptr_reg_पढ़ो00b(काष्ठा snd_info_entry *entry,
					 काष्ठा snd_info_buffer *buffer)
अणु
	snd_emu_proc_ptr_reg_पढ़ो(entry, buffer, 0, 0x40, 0x40, 64);
पूर्ण

अटल व्योम snd_emu_proc_ptr_reg_पढ़ो20a(काष्ठा snd_info_entry *entry,
					 काष्ठा snd_info_buffer *buffer)
अणु
	snd_emu_proc_ptr_reg_पढ़ो(entry, buffer, 0x20, 0, 0x40, 4);
पूर्ण

अटल व्योम snd_emu_proc_ptr_reg_पढ़ो20b(काष्ठा snd_info_entry *entry,
					 काष्ठा snd_info_buffer *buffer)
अणु
	snd_emu_proc_ptr_reg_पढ़ो(entry, buffer, 0x20, 0x40, 0x40, 4);
पूर्ण

अटल व्योम snd_emu_proc_ptr_reg_पढ़ो20c(काष्ठा snd_info_entry *entry,
					 काष्ठा snd_info_buffer * buffer)
अणु
	snd_emu_proc_ptr_reg_पढ़ो(entry, buffer, 0x20, 0x80, 0x20, 4);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा snd_info_entry_ops snd_emu10k1_proc_ops_fx8010 = अणु
	.पढ़ो = snd_emu10k1_fx8010_पढ़ो,
पूर्ण;

पूर्णांक snd_emu10k1_proc_init(काष्ठा snd_emu10k1 *emu)
अणु
	काष्ठा snd_info_entry *entry;
#अगर_घोषित CONFIG_SND_DEBUG
	अगर (emu->card_capabilities->emu_model) अणु
		snd_card_ro_proc_new(emu->card, "emu1010_regs",
				     emu, snd_emu_proc_emu1010_reg_पढ़ो);
	पूर्ण
	snd_card_rw_proc_new(emu->card, "io_regs", emu,
			     snd_emu_proc_io_reg_पढ़ो,
			     snd_emu_proc_io_reg_ग_लिखो);
	snd_card_rw_proc_new(emu->card, "ptr_regs00a", emu,
			     snd_emu_proc_ptr_reg_पढ़ो00a,
			     snd_emu_proc_ptr_reg_ग_लिखो00);
	snd_card_rw_proc_new(emu->card, "ptr_regs00b", emu,
			     snd_emu_proc_ptr_reg_पढ़ो00b,
			     snd_emu_proc_ptr_reg_ग_लिखो00);
	snd_card_rw_proc_new(emu->card, "ptr_regs20a", emu,
			     snd_emu_proc_ptr_reg_पढ़ो20a,
			     snd_emu_proc_ptr_reg_ग_लिखो20);
	snd_card_rw_proc_new(emu->card, "ptr_regs20b", emu,
			     snd_emu_proc_ptr_reg_पढ़ो20b,
			     snd_emu_proc_ptr_reg_ग_लिखो20);
	snd_card_rw_proc_new(emu->card, "ptr_regs20c", emu,
			     snd_emu_proc_ptr_reg_पढ़ो20c,
			     snd_emu_proc_ptr_reg_ग_लिखो20);
#पूर्ण_अगर
	
	snd_card_ro_proc_new(emu->card, "emu10k1", emu, snd_emu10k1_proc_पढ़ो);

	अगर (emu->card_capabilities->emu10k2_chip)
		snd_card_ro_proc_new(emu->card, "spdif-in", emu,
				     snd_emu10k1_proc_spdअगर_पढ़ो);
	अगर (emu->card_capabilities->ca0151_chip)
		snd_card_ro_proc_new(emu->card, "capture-rates", emu,
				     snd_emu10k1_proc_rates_पढ़ो);

	snd_card_ro_proc_new(emu->card, "voices", emu,
			     snd_emu10k1_proc_voices_पढ़ो);

	अगर (! snd_card_proc_new(emu->card, "fx8010_gpr", &entry)) अणु
		entry->content = SNDRV_INFO_CONTENT_DATA;
		entry->निजी_data = emu;
		entry->mode = S_IFREG | 0444 /*| S_IWUSR*/;
		entry->size = emu->audigy ? A_TOTAL_SIZE_GPR : TOTAL_SIZE_GPR;
		entry->c.ops = &snd_emu10k1_proc_ops_fx8010;
	पूर्ण
	अगर (! snd_card_proc_new(emu->card, "fx8010_tram_data", &entry)) अणु
		entry->content = SNDRV_INFO_CONTENT_DATA;
		entry->निजी_data = emu;
		entry->mode = S_IFREG | 0444 /*| S_IWUSR*/;
		entry->size = emu->audigy ? A_TOTAL_SIZE_TANKMEM_DATA : TOTAL_SIZE_TANKMEM_DATA ;
		entry->c.ops = &snd_emu10k1_proc_ops_fx8010;
	पूर्ण
	अगर (! snd_card_proc_new(emu->card, "fx8010_tram_addr", &entry)) अणु
		entry->content = SNDRV_INFO_CONTENT_DATA;
		entry->निजी_data = emu;
		entry->mode = S_IFREG | 0444 /*| S_IWUSR*/;
		entry->size = emu->audigy ? A_TOTAL_SIZE_TANKMEM_ADDR : TOTAL_SIZE_TANKMEM_ADDR ;
		entry->c.ops = &snd_emu10k1_proc_ops_fx8010;
	पूर्ण
	अगर (! snd_card_proc_new(emu->card, "fx8010_code", &entry)) अणु
		entry->content = SNDRV_INFO_CONTENT_DATA;
		entry->निजी_data = emu;
		entry->mode = S_IFREG | 0444 /*| S_IWUSR*/;
		entry->size = emu->audigy ? A_TOTAL_SIZE_CODE : TOTAL_SIZE_CODE;
		entry->c.ops = &snd_emu10k1_proc_ops_fx8010;
	पूर्ण
	snd_card_ro_proc_new(emu->card, "fx8010_acode", emu,
			     snd_emu10k1_proc_acode_पढ़ो);
	वापस 0;
पूर्ण
