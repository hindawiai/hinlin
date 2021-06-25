<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 2004 James Courtier-Dutton <James@superbug.demon.co.uk>
 *  Driver CA0106 chips. e.g. Sound Blaster Audigy LS and Live 24bit
 *  Version: 0.0.18
 *
 *  FEATURES currently supported:
 *    See ca0106_मुख्य.c क्रम features.
 * 
 *  Changelog:
 *    Support पूर्णांकerrupts per period.
 *    Removed noise from Center/LFE channel when in Analog mode.
 *    Rename and हटाओ mixer controls.
 *  0.0.6
 *    Use separate card based DMA buffer क्रम periods table list.
 *  0.0.7
 *    Change हटाओ and नाम ctrls पूर्णांकo lists.
 *  0.0.8
 *    Try to fix capture sources.
 *  0.0.9
 *    Fix AC3 output.
 *    Enable S32_LE क्रमmat support.
 *  0.0.10
 *    Enable playback 48000 and 96000 rates. (Rates other that these करो not work, even with "plug:front".)
 *  0.0.11
 *    Add Model name recognition.
 *  0.0.12
 *    Correct पूर्णांकerrupt timing. पूर्णांकerrupt at end of period, instead of in the middle of a playback period.
 *    Remove redundent "voice" handling.
 *  0.0.13
 *    Single trigger call क्रम multi channels.
 *  0.0.14
 *    Set limits based on what the sound card hardware can करो.
 *    playback periods_min=2, periods_max=8
 *    capture hw स्थिरraपूर्णांकs require period_size = n * 64 bytes.
 *    playback hw स्थिरraपूर्णांकs require period_size = n * 64 bytes.
 *  0.0.15
 *    Separate ca0106.c पूर्णांकo separate functional .c files.
 *  0.0.16
 *    Modअगरied Copyright message.
 *  0.0.17
 *    Add iec958 file in proc file प्रणाली to show status of SPDIF in.
 *  0.0.18
 *    Implement support क्रम Line-in capture on SB Live 24bit.
 *
 *  This code was initially based on code from ALSA's emu10k1x.c which is:
 *  Copyright (c) by Francisco Moraes <fmoraes@nc.rr.com>
 */
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/पन.स>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/info.h>
#समावेश <sound/asoundef.h>

#समावेश "ca0106.h"


काष्ठा snd_ca0106_category_str अणु
	पूर्णांक val;
	स्थिर अक्षर *name;
पूर्ण;

अटल स्थिर काष्ठा snd_ca0106_category_str snd_ca0106_con_category[] = अणु
	अणु IEC958_AES1_CON_DAT, "DAT" पूर्ण,
	अणु IEC958_AES1_CON_VCR, "VCR" पूर्ण,
	अणु IEC958_AES1_CON_MICROPHONE, "microphone" पूर्ण,
	अणु IEC958_AES1_CON_SYNTHESIZER, "synthesizer" पूर्ण,
	अणु IEC958_AES1_CON_RATE_CONVERTER, "rate converter" पूर्ण,
	अणु IEC958_AES1_CON_MIXER, "mixer" पूर्ण,
	अणु IEC958_AES1_CON_SAMPLER, "sampler" पूर्ण,
	अणु IEC958_AES1_CON_PCM_CODER, "PCM coder" पूर्ण,
	अणु IEC958_AES1_CON_IEC908_CD, "CD" पूर्ण,
	अणु IEC958_AES1_CON_NON_IEC908_CD, "non-IEC908 CD" पूर्ण,
	अणु IEC958_AES1_CON_GENERAL, "general" पूर्ण,
पूर्ण;


अटल व्योम snd_ca0106_proc_dump_iec958( काष्ठा snd_info_buffer *buffer, u32 value)
अणु
	पूर्णांक i;
	u32 status[4];
	status[0] = value & 0xff;
	status[1] = (value >> 8) & 0xff;
	status[2] = (value >> 16)  & 0xff;
	status[3] = (value >> 24)  & 0xff;
	
	अगर (! (status[0] & IEC958_AES0_PROFESSIONAL)) अणु
		/* consumer */
		snd_iम_लिखो(buffer, "Mode: consumer\n");
		snd_iम_लिखो(buffer, "Data: ");
		अगर (!(status[0] & IEC958_AES0_NONAUDIO)) अणु
			snd_iम_लिखो(buffer, "audio\n");
		पूर्ण अन्यथा अणु
			snd_iम_लिखो(buffer, "non-audio\n");
		पूर्ण
		snd_iम_लिखो(buffer, "Rate: ");
		चयन (status[3] & IEC958_AES3_CON_FS) अणु
		हाल IEC958_AES3_CON_FS_44100:
			snd_iम_लिखो(buffer, "44100 Hz\n");
			अवरोध;
		हाल IEC958_AES3_CON_FS_48000:
			snd_iम_लिखो(buffer, "48000 Hz\n");
			अवरोध;
		हाल IEC958_AES3_CON_FS_32000:
			snd_iम_लिखो(buffer, "32000 Hz\n");
			अवरोध;
		शेष:
			snd_iम_लिखो(buffer, "unknown\n");
			अवरोध;
		पूर्ण
		snd_iम_लिखो(buffer, "Copyright: ");
		अगर (status[0] & IEC958_AES0_CON_NOT_COPYRIGHT) अणु
			snd_iम_लिखो(buffer, "permitted\n");
		पूर्ण अन्यथा अणु
			snd_iम_लिखो(buffer, "protected\n");
		पूर्ण
		snd_iम_लिखो(buffer, "Emphasis: ");
		अगर ((status[0] & IEC958_AES0_CON_EMPHASIS) != IEC958_AES0_CON_EMPHASIS_5015) अणु
			snd_iम_लिखो(buffer, "none\n");
		पूर्ण अन्यथा अणु
			snd_iम_लिखो(buffer, "50/15us\n");
		पूर्ण
		snd_iम_लिखो(buffer, "Category: ");
		क्रम (i = 0; i < ARRAY_SIZE(snd_ca0106_con_category); i++) अणु
			अगर ((status[1] & IEC958_AES1_CON_CATEGORY) == snd_ca0106_con_category[i].val) अणु
				snd_iम_लिखो(buffer, "%s\n", snd_ca0106_con_category[i].name);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i >= ARRAY_SIZE(snd_ca0106_con_category)) अणु
			snd_iम_लिखो(buffer, "unknown 0x%x\n", status[1] & IEC958_AES1_CON_CATEGORY);
		पूर्ण
		snd_iम_लिखो(buffer, "Original: ");
		अगर (status[1] & IEC958_AES1_CON_ORIGINAL) अणु
			snd_iम_लिखो(buffer, "original\n");
		पूर्ण अन्यथा अणु
			snd_iम_लिखो(buffer, "1st generation\n");
		पूर्ण
		snd_iम_लिखो(buffer, "Clock: ");
		चयन (status[3] & IEC958_AES3_CON_CLOCK) अणु
		हाल IEC958_AES3_CON_CLOCK_1000PPM:
			snd_iम_लिखो(buffer, "1000 ppm\n");
			अवरोध;
		हाल IEC958_AES3_CON_CLOCK_50PPM:
			snd_iम_लिखो(buffer, "50 ppm\n");
			अवरोध;
		हाल IEC958_AES3_CON_CLOCK_VARIABLE:
			snd_iम_लिखो(buffer, "variable pitch\n");
			अवरोध;
		शेष:
			snd_iम_लिखो(buffer, "unknown\n");
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		snd_iम_लिखो(buffer, "Mode: professional\n");
		snd_iम_लिखो(buffer, "Data: ");
		अगर (!(status[0] & IEC958_AES0_NONAUDIO)) अणु
			snd_iम_लिखो(buffer, "audio\n");
		पूर्ण अन्यथा अणु
			snd_iम_लिखो(buffer, "non-audio\n");
		पूर्ण
		snd_iम_लिखो(buffer, "Rate: ");
		चयन (status[0] & IEC958_AES0_PRO_FS) अणु
		हाल IEC958_AES0_PRO_FS_44100:
			snd_iम_लिखो(buffer, "44100 Hz\n");
			अवरोध;
		हाल IEC958_AES0_PRO_FS_48000:
			snd_iम_लिखो(buffer, "48000 Hz\n");
			अवरोध;
		हाल IEC958_AES0_PRO_FS_32000:
			snd_iम_लिखो(buffer, "32000 Hz\n");
			अवरोध;
		शेष:
			snd_iम_लिखो(buffer, "unknown\n");
			अवरोध;
		पूर्ण
		snd_iम_लिखो(buffer, "Rate Locked: ");
		अगर (status[0] & IEC958_AES0_PRO_FREQ_UNLOCKED)
			snd_iम_लिखो(buffer, "no\n");
		अन्यथा
			snd_iम_लिखो(buffer, "yes\n");
		snd_iम_लिखो(buffer, "Emphasis: ");
		चयन (status[0] & IEC958_AES0_PRO_EMPHASIS) अणु
		हाल IEC958_AES0_PRO_EMPHASIS_CCITT:
			snd_iम_लिखो(buffer, "CCITT J.17\n");
			अवरोध;
		हाल IEC958_AES0_PRO_EMPHASIS_NONE:
			snd_iम_लिखो(buffer, "none\n");
			अवरोध;
		हाल IEC958_AES0_PRO_EMPHASIS_5015:
			snd_iम_लिखो(buffer, "50/15us\n");
			अवरोध;
		हाल IEC958_AES0_PRO_EMPHASIS_NOTID:
		शेष:
			snd_iम_लिखो(buffer, "unknown\n");
			अवरोध;
		पूर्ण
		snd_iम_लिखो(buffer, "Stereophonic: ");
		अगर ((status[1] & IEC958_AES1_PRO_MODE) == IEC958_AES1_PRO_MODE_STEREOPHONIC) अणु
			snd_iम_लिखो(buffer, "stereo\n");
		पूर्ण अन्यथा अणु
			snd_iम_लिखो(buffer, "not indicated\n");
		पूर्ण
		snd_iम_लिखो(buffer, "Userbits: ");
		चयन (status[1] & IEC958_AES1_PRO_USERBITS) अणु
		हाल IEC958_AES1_PRO_USERBITS_192:
			snd_iम_लिखो(buffer, "192bit\n");
			अवरोध;
		हाल IEC958_AES1_PRO_USERBITS_UDEF:
			snd_iम_लिखो(buffer, "user-defined\n");
			अवरोध;
		शेष:
			snd_iम_लिखो(buffer, "unknown\n");
			अवरोध;
		पूर्ण
		snd_iम_लिखो(buffer, "Sample Bits: ");
		चयन (status[2] & IEC958_AES2_PRO_SBITS) अणु
		हाल IEC958_AES2_PRO_SBITS_20:
			snd_iम_लिखो(buffer, "20 bit\n");
			अवरोध;
		हाल IEC958_AES2_PRO_SBITS_24:
			snd_iम_लिखो(buffer, "24 bit\n");
			अवरोध;
		हाल IEC958_AES2_PRO_SBITS_UDEF:
			snd_iम_लिखो(buffer, "user defined\n");
			अवरोध;
		शेष:
			snd_iम_लिखो(buffer, "unknown\n");
			अवरोध;
		पूर्ण
		snd_iम_लिखो(buffer, "Word Length: ");
		चयन (status[2] & IEC958_AES2_PRO_WORDLEN) अणु
		हाल IEC958_AES2_PRO_WORDLEN_22_18:
			snd_iम_लिखो(buffer, "22 bit or 18 bit\n");
			अवरोध;
		हाल IEC958_AES2_PRO_WORDLEN_23_19:
			snd_iम_लिखो(buffer, "23 bit or 19 bit\n");
			अवरोध;
		हाल IEC958_AES2_PRO_WORDLEN_24_20:
			snd_iम_लिखो(buffer, "24 bit or 20 bit\n");
			अवरोध;
		हाल IEC958_AES2_PRO_WORDLEN_20_16:
			snd_iम_लिखो(buffer, "20 bit or 16 bit\n");
			अवरोध;
		शेष:
			snd_iम_लिखो(buffer, "unknown\n");
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम snd_ca0106_proc_iec958(काष्ठा snd_info_entry *entry, 
				       काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_ca0106 *emu = entry->निजी_data;
	u32 value;

        value = snd_ca0106_ptr_पढ़ो(emu, SAMPLE_RATE_TRACKER_STATUS, 0);
	snd_iम_लिखो(buffer, "Status: %s, %s, %s\n",
		  (value & 0x100000) ? "Rate Locked" : "Not Rate Locked",
		  (value & 0x200000) ? "SPDIF Locked" : "No SPDIF Lock",
		  (value & 0x400000) ? "Audio Valid" : "No valid audio" );
	snd_iम_लिखो(buffer, "Estimated sample rate: %u\n", 
		  ((value & 0xfffff) * 48000) / 0x8000 );
	अगर (value & 0x200000) अणु
		snd_iम_लिखो(buffer, "IEC958/SPDIF input status:\n");
        	value = snd_ca0106_ptr_पढ़ो(emu, SPDIF_INPUT_STATUS, 0);
		snd_ca0106_proc_dump_iec958(buffer, value);
	पूर्ण

	snd_iम_लिखो(buffer, "\n");
पूर्ण

अटल व्योम snd_ca0106_proc_reg_ग_लिखो32(काष्ठा snd_info_entry *entry, 
				       काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_ca0106 *emu = entry->निजी_data;
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

अटल व्योम snd_ca0106_proc_reg_पढ़ो32(काष्ठा snd_info_entry *entry, 
				       काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_ca0106 *emu = entry->निजी_data;
	अचिन्हित दीर्घ value;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	snd_iम_लिखो(buffer, "Registers:\n\n");
	क्रम(i = 0; i < 0x20; i+=4) अणु
		spin_lock_irqsave(&emu->emu_lock, flags);
		value = inl(emu->port + i);
		spin_unlock_irqrestore(&emu->emu_lock, flags);
		snd_iम_लिखो(buffer, "Register %02X: %08lX\n", i, value);
	पूर्ण
पूर्ण

अटल व्योम snd_ca0106_proc_reg_पढ़ो16(काष्ठा snd_info_entry *entry, 
				       काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_ca0106 *emu = entry->निजी_data;
        अचिन्हित पूर्णांक value;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	snd_iम_लिखो(buffer, "Registers:\n\n");
	क्रम(i = 0; i < 0x20; i+=2) अणु
		spin_lock_irqsave(&emu->emu_lock, flags);
		value = inw(emu->port + i);
		spin_unlock_irqrestore(&emu->emu_lock, flags);
		snd_iम_लिखो(buffer, "Register %02X: %04X\n", i, value);
	पूर्ण
पूर्ण

अटल व्योम snd_ca0106_proc_reg_पढ़ो8(काष्ठा snd_info_entry *entry, 
				       काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_ca0106 *emu = entry->निजी_data;
	अचिन्हित पूर्णांक value;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	snd_iम_लिखो(buffer, "Registers:\n\n");
	क्रम(i = 0; i < 0x20; i+=1) अणु
		spin_lock_irqsave(&emu->emu_lock, flags);
		value = inb(emu->port + i);
		spin_unlock_irqrestore(&emu->emu_lock, flags);
		snd_iम_लिखो(buffer, "Register %02X: %02X\n", i, value);
	पूर्ण
पूर्ण

अटल व्योम snd_ca0106_proc_reg_पढ़ो1(काष्ठा snd_info_entry *entry, 
				       काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_ca0106 *emu = entry->निजी_data;
	अचिन्हित दीर्घ value;
	पूर्णांक i,j;

	snd_iम_लिखो(buffer, "Registers\n");
	क्रम(i = 0; i < 0x40; i++) अणु
		snd_iम_लिखो(buffer, "%02X: ",i);
		क्रम (j = 0; j < 4; j++) अणु
                  value = snd_ca0106_ptr_पढ़ो(emu, i, j);
		  snd_iम_लिखो(buffer, "%08lX ", value);
                पूर्ण
	        snd_iम_लिखो(buffer, "\n");
	पूर्ण
पूर्ण

अटल व्योम snd_ca0106_proc_reg_पढ़ो2(काष्ठा snd_info_entry *entry, 
				       काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_ca0106 *emu = entry->निजी_data;
	अचिन्हित दीर्घ value;
	पूर्णांक i,j;

	snd_iम_लिखो(buffer, "Registers\n");
	क्रम(i = 0x40; i < 0x80; i++) अणु
		snd_iम_लिखो(buffer, "%02X: ",i);
		क्रम (j = 0; j < 4; j++) अणु
                  value = snd_ca0106_ptr_पढ़ो(emu, i, j);
		  snd_iम_लिखो(buffer, "%08lX ", value);
                पूर्ण
	        snd_iम_लिखो(buffer, "\n");
	पूर्ण
पूर्ण

अटल व्योम snd_ca0106_proc_reg_ग_लिखो(काष्ठा snd_info_entry *entry, 
				       काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_ca0106 *emu = entry->निजी_data;
        अक्षर line[64];
        अचिन्हित पूर्णांक reg, channel_id , val;
        जबतक (!snd_info_get_line(buffer, line, माप(line))) अणु
                अगर (माला_पूछो(line, "%x %x %x", &reg, &channel_id, &val) != 3)
                        जारी;
		अगर (reg < 0x80 && val <= 0xffffffff && channel_id <= 3)
                        snd_ca0106_ptr_ग_लिखो(emu, reg, channel_id, val);
        पूर्ण
पूर्ण

अटल व्योम snd_ca0106_proc_i2c_ग_लिखो(काष्ठा snd_info_entry *entry, 
				       काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_ca0106 *emu = entry->निजी_data;
        अक्षर line[64];
        अचिन्हित पूर्णांक reg, val;
        जबतक (!snd_info_get_line(buffer, line, माप(line))) अणु
                अगर (माला_पूछो(line, "%x %x", &reg, &val) != 2)
                        जारी;
                अगर ((reg <= 0x7f) || (val <= 0x1ff)) अणु
                        snd_ca0106_i2c_ग_लिखो(emu, reg, val);
		पूर्ण
        पूर्ण
पूर्ण

पूर्णांक snd_ca0106_proc_init(काष्ठा snd_ca0106 *emu)
अणु
	snd_card_ro_proc_new(emu->card, "iec958", emu, snd_ca0106_proc_iec958);
	snd_card_rw_proc_new(emu->card, "ca0106_reg32", emu,
			     snd_ca0106_proc_reg_पढ़ो32,
			     snd_ca0106_proc_reg_ग_लिखो32);
	snd_card_ro_proc_new(emu->card, "ca0106_reg16", emu,
			     snd_ca0106_proc_reg_पढ़ो16);
	snd_card_ro_proc_new(emu->card, "ca0106_reg8", emu,
			     snd_ca0106_proc_reg_पढ़ो8);
	snd_card_rw_proc_new(emu->card, "ca0106_regs1", emu,
			     snd_ca0106_proc_reg_पढ़ो1,
			     snd_ca0106_proc_reg_ग_लिखो);
	snd_card_rw_proc_new(emu->card, "ca0106_i2c", emu, शून्य,
			     snd_ca0106_proc_i2c_ग_लिखो);
	snd_card_ro_proc_new(emu->card, "ca0106_regs2", emu,
			     snd_ca0106_proc_reg_पढ़ो2);
	वापस 0;
पूर्ण
