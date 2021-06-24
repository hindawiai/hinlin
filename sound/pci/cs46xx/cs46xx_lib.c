<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *                   Abramo Bagnara <abramo@alsa-project.org>
 *                   Cirrus Logic, Inc.
 *  Routines क्रम control of Cirrus Logic CS461x chips
 *
 *  KNOWN BUGS:
 *    - Someबार the SPDIF input DSP tasks get's unsynchronized
 *      and the SPDIF get somewhat "distorcionated", or/and left right channel
 *      are swapped. To get around this problem when it happens, mute and unmute 
 *      the SPDIF input mixer control.
 *    - On the Hercules Game Theater XP the amplअगरier are someबार turned
 *      off on inadecuate moments which causes distorcions on sound.
 *
 *  TODO:
 *    - Secondary CODEC on some soundcards
 *    - SPDIF input support क्रम other sample rates then 48khz
 *    - Posibility to mix the SPDIF output with analog sources.
 *    - PCM channels क्रम Center and LFE on secondary codec
 *
 *  NOTE: with CONFIG_SND_CS46XX_NEW_DSP unset uses old DSP image (which
 *        is शेष configuration), no SPDIF, no secondary codec, no
 *        multi channel PCM.  But known to work.
 *
 *  FINALLY: A credit to the developers Tom and Jordan 
 *           at Cirrus क्रम have helping me out with the DSP, however we
 *           still करोn't have sufficient करोcumentation and technical
 *           references to be able to implement all fancy feutures
 *           supported by the cs46xx DSP's. 
 *           Benny <benny@hosपंचांगobility.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/gameport.h>
#समावेश <linux/mutex.h>
#समावेश <linux/export.h>
#समावेश <linux/module.h>
#समावेश <linux/firmware.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/पन.स>

#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/info.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश "cs46xx.h"

#समावेश "cs46xx_lib.h"
#समावेश "dsp_spos.h"

अटल व्योम amp_voyetra(काष्ठा snd_cs46xx *chip, पूर्णांक change);

#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
अटल स्थिर काष्ठा snd_pcm_ops snd_cs46xx_playback_rear_ops;
अटल स्थिर काष्ठा snd_pcm_ops snd_cs46xx_playback_indirect_rear_ops;
अटल स्थिर काष्ठा snd_pcm_ops snd_cs46xx_playback_clfe_ops;
अटल स्थिर काष्ठा snd_pcm_ops snd_cs46xx_playback_indirect_clfe_ops;
अटल स्थिर काष्ठा snd_pcm_ops snd_cs46xx_playback_iec958_ops;
अटल स्थिर काष्ठा snd_pcm_ops snd_cs46xx_playback_indirect_iec958_ops;
#पूर्ण_अगर

अटल स्थिर काष्ठा snd_pcm_ops snd_cs46xx_playback_ops;
अटल स्थिर काष्ठा snd_pcm_ops snd_cs46xx_playback_indirect_ops;
अटल स्थिर काष्ठा snd_pcm_ops snd_cs46xx_capture_ops;
अटल स्थिर काष्ठा snd_pcm_ops snd_cs46xx_capture_indirect_ops;

अटल अचिन्हित लघु snd_cs46xx_codec_पढ़ो(काष्ठा snd_cs46xx *chip,
					    अचिन्हित लघु reg,
					    पूर्णांक codec_index)
अणु
	पूर्णांक count;
	अचिन्हित लघु result,पंचांगp;
	u32 offset = 0;

	अगर (snd_BUG_ON(codec_index != CS46XX_PRIMARY_CODEC_INDEX &&
		       codec_index != CS46XX_SECONDARY_CODEC_INDEX))
		वापस 0xffff;

	chip->active_ctrl(chip, 1);

	अगर (codec_index == CS46XX_SECONDARY_CODEC_INDEX)
		offset = CS46XX_SECONDARY_CODEC_OFFSET;

	/*
	 *  1. Write ACCAD = Command Address Register = 46Ch क्रम AC97 रेजिस्टर address
	 *  2. Write ACCDA = Command Data Register = 470h    क्रम data to ग_लिखो to AC97 
	 *  3. Write ACCTL = Control Register = 460h क्रम initiating the ग_लिखो7---55
	 *  4. Read ACCTL = 460h, DCV should be reset by now and 460h = 17h
	 *  5. अगर DCV not cleared, अवरोध and वापस error
	 *  6. Read ACSTS = Status Register = 464h, check VSTS bit
	 */

	snd_cs46xx_peekBA0(chip, BA0_ACSDA + offset);

	पंचांगp = snd_cs46xx_peekBA0(chip, BA0_ACCTL);
	अगर ((पंचांगp & ACCTL_VFRM) == 0) अणु
		dev_warn(chip->card->dev, "ACCTL_VFRM not set 0x%x\n", पंचांगp);
		snd_cs46xx_pokeBA0(chip, BA0_ACCTL, (पंचांगp & (~ACCTL_ESYN)) | ACCTL_VFRM );
		msleep(50);
		पंचांगp = snd_cs46xx_peekBA0(chip, BA0_ACCTL + offset);
		snd_cs46xx_pokeBA0(chip, BA0_ACCTL, पंचांगp | ACCTL_ESYN | ACCTL_VFRM );

	पूर्ण

	/*
	 *  Setup the AC97 control रेजिस्टरs on the CS461x to send the
	 *  appropriate command to the AC97 to perक्रमm the पढ़ो.
	 *  ACCAD = Command Address Register = 46Ch
	 *  ACCDA = Command Data Register = 470h
	 *  ACCTL = Control Register = 460h
	 *  set DCV - will clear when process completed
	 *  set CRW - Read command
	 *  set VFRM - valid frame enabled
	 *  set ESYN - ASYNC generation enabled
	 *  set RSTN - ARST# inactive, AC97 codec not reset
	 */

	snd_cs46xx_pokeBA0(chip, BA0_ACCAD, reg);
	snd_cs46xx_pokeBA0(chip, BA0_ACCDA, 0);
	अगर (codec_index == CS46XX_PRIMARY_CODEC_INDEX) अणु
		snd_cs46xx_pokeBA0(chip, BA0_ACCTL,/* clear ACCTL_DCV */ ACCTL_CRW | 
				   ACCTL_VFRM | ACCTL_ESYN |
				   ACCTL_RSTN);
		snd_cs46xx_pokeBA0(chip, BA0_ACCTL, ACCTL_DCV | ACCTL_CRW |
				   ACCTL_VFRM | ACCTL_ESYN |
				   ACCTL_RSTN);
	पूर्ण अन्यथा अणु
		snd_cs46xx_pokeBA0(chip, BA0_ACCTL, ACCTL_DCV | ACCTL_TC |
				   ACCTL_CRW | ACCTL_VFRM | ACCTL_ESYN |
				   ACCTL_RSTN);
	पूर्ण

	/*
	 *  Wait क्रम the पढ़ो to occur.
	 */
	क्रम (count = 0; count < 1000; count++) अणु
		/*
		 *  First, we want to रुको क्रम a लघु समय.
	 	 */
		udelay(10);
		/*
		 *  Now, check to see अगर the पढ़ो has completed.
		 *  ACCTL = 460h, DCV should be reset by now and 460h = 17h
		 */
		अगर (!(snd_cs46xx_peekBA0(chip, BA0_ACCTL) & ACCTL_DCV))
			जाओ ok1;
	पूर्ण

	dev_err(chip->card->dev,
		"AC'97 read problem (ACCTL_DCV), reg = 0x%x\n", reg);
	result = 0xffff;
	जाओ end;
	
 ok1:
	/*
	 *  Wait क्रम the valid status bit to go active.
	 */
	क्रम (count = 0; count < 100; count++) अणु
		/*
		 *  Read the AC97 status रेजिस्टर.
		 *  ACSTS = Status Register = 464h
		 *  VSTS - Valid Status
		 */
		अगर (snd_cs46xx_peekBA0(chip, BA0_ACSTS + offset) & ACSTS_VSTS)
			जाओ ok2;
		udelay(10);
	पूर्ण
	
	dev_err(chip->card->dev,
		"AC'97 read problem (ACSTS_VSTS), codec_index %d, reg = 0x%x\n",
		codec_index, reg);
	result = 0xffff;
	जाओ end;

 ok2:
	/*
	 *  Read the data वापसed from the AC97 रेजिस्टर.
	 *  ACSDA = Status Data Register = 474h
	 */
#अगर 0
	dev_dbg(chip->card->dev,
		"e) reg = 0x%x, val = 0x%x, BA0_ACCAD = 0x%x\n", reg,
			snd_cs46xx_peekBA0(chip, BA0_ACSDA),
			snd_cs46xx_peekBA0(chip, BA0_ACCAD));
#पूर्ण_अगर

	//snd_cs46xx_peekBA0(chip, BA0_ACCAD);
	result = snd_cs46xx_peekBA0(chip, BA0_ACSDA + offset);
 end:
	chip->active_ctrl(chip, -1);
	वापस result;
पूर्ण

अटल अचिन्हित लघु snd_cs46xx_ac97_पढ़ो(काष्ठा snd_ac97 * ac97,
					    अचिन्हित लघु reg)
अणु
	काष्ठा snd_cs46xx *chip = ac97->निजी_data;
	अचिन्हित लघु val;
	पूर्णांक codec_index = ac97->num;

	अगर (snd_BUG_ON(codec_index != CS46XX_PRIMARY_CODEC_INDEX &&
		       codec_index != CS46XX_SECONDARY_CODEC_INDEX))
		वापस 0xffff;

	val = snd_cs46xx_codec_पढ़ो(chip, reg, codec_index);

	वापस val;
पूर्ण


अटल व्योम snd_cs46xx_codec_ग_लिखो(काष्ठा snd_cs46xx *chip,
				   अचिन्हित लघु reg,
				   अचिन्हित लघु val,
				   पूर्णांक codec_index)
अणु
	पूर्णांक count;

	अगर (snd_BUG_ON(codec_index != CS46XX_PRIMARY_CODEC_INDEX &&
		       codec_index != CS46XX_SECONDARY_CODEC_INDEX))
		वापस;

	chip->active_ctrl(chip, 1);

	/*
	 *  1. Write ACCAD = Command Address Register = 46Ch क्रम AC97 रेजिस्टर address
	 *  2. Write ACCDA = Command Data Register = 470h    क्रम data to ग_लिखो to AC97
	 *  3. Write ACCTL = Control Register = 460h क्रम initiating the ग_लिखो
	 *  4. Read ACCTL = 460h, DCV should be reset by now and 460h = 07h
	 *  5. अगर DCV not cleared, अवरोध and वापस error
	 */

	/*
	 *  Setup the AC97 control रेजिस्टरs on the CS461x to send the
	 *  appropriate command to the AC97 to perक्रमm the पढ़ो.
	 *  ACCAD = Command Address Register = 46Ch
	 *  ACCDA = Command Data Register = 470h
	 *  ACCTL = Control Register = 460h
	 *  set DCV - will clear when process completed
	 *  reset CRW - Write command
	 *  set VFRM - valid frame enabled
	 *  set ESYN - ASYNC generation enabled
	 *  set RSTN - ARST# inactive, AC97 codec not reset
         */
	snd_cs46xx_pokeBA0(chip, BA0_ACCAD , reg);
	snd_cs46xx_pokeBA0(chip, BA0_ACCDA , val);
	snd_cs46xx_peekBA0(chip, BA0_ACCTL);

	अगर (codec_index == CS46XX_PRIMARY_CODEC_INDEX) अणु
		snd_cs46xx_pokeBA0(chip, BA0_ACCTL, /* clear ACCTL_DCV */ ACCTL_VFRM |
				   ACCTL_ESYN | ACCTL_RSTN);
		snd_cs46xx_pokeBA0(chip, BA0_ACCTL, ACCTL_DCV | ACCTL_VFRM |
				   ACCTL_ESYN | ACCTL_RSTN);
	पूर्ण अन्यथा अणु
		snd_cs46xx_pokeBA0(chip, BA0_ACCTL, ACCTL_DCV | ACCTL_TC |
				   ACCTL_VFRM | ACCTL_ESYN | ACCTL_RSTN);
	पूर्ण

	क्रम (count = 0; count < 4000; count++) अणु
		/*
		 *  First, we want to रुको क्रम a लघु समय.
		 */
		udelay(10);
		/*
		 *  Now, check to see अगर the ग_लिखो has completed.
		 *  ACCTL = 460h, DCV should be reset by now and 460h = 07h
		 */
		अगर (!(snd_cs46xx_peekBA0(chip, BA0_ACCTL) & ACCTL_DCV)) अणु
			जाओ end;
		पूर्ण
	पूर्ण
	dev_err(chip->card->dev,
		"AC'97 write problem, codec_index = %d, reg = 0x%x, val = 0x%x\n",
		codec_index, reg, val);
 end:
	chip->active_ctrl(chip, -1);
पूर्ण

अटल व्योम snd_cs46xx_ac97_ग_लिखो(काष्ठा snd_ac97 *ac97,
				   अचिन्हित लघु reg,
				   अचिन्हित लघु val)
अणु
	काष्ठा snd_cs46xx *chip = ac97->निजी_data;
	पूर्णांक codec_index = ac97->num;

	अगर (snd_BUG_ON(codec_index != CS46XX_PRIMARY_CODEC_INDEX &&
		       codec_index != CS46XX_SECONDARY_CODEC_INDEX))
		वापस;

	snd_cs46xx_codec_ग_लिखो(chip, reg, val, codec_index);
पूर्ण


/*
 *  Chip initialization
 */

पूर्णांक snd_cs46xx_करोwnload(काष्ठा snd_cs46xx *chip,
			u32 *src,
                        अचिन्हित दीर्घ offset,
                        अचिन्हित दीर्घ len)
अणु
	व्योम __iomem *dst;
	अचिन्हित पूर्णांक bank = offset >> 16;
	offset = offset & 0xffff;

	अगर (snd_BUG_ON((offset & 3) || (len & 3)))
		वापस -EINVAL;
	dst = chip->region.idx[bank+1].remap_addr + offset;
	len /= माप(u32);

	/* ग_लिखोl alपढ़ोy converts 32-bit value to right endianess */
	जबतक (len-- > 0) अणु
		ग_लिखोl(*src++, dst);
		dst += माप(u32);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम स_नकल_le32(व्योम *dst, स्थिर व्योम *src, अचिन्हित पूर्णांक len)
अणु
#अगर_घोषित __LITTLE_ENDIAN
	स_नकल(dst, src, len);
#अन्यथा
	u32 *_dst = dst;
	स्थिर __le32 *_src = src;
	len /= 4;
	जबतक (len-- > 0)
		*_dst++ = le32_to_cpu(*_src++);
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP

अटल स्थिर अक्षर *module_names[CS46XX_DSP_MODULES] = अणु
	"cwc4630", "cwcasync", "cwcsnoop", "cwcbinhack", "cwcdma"
पूर्ण;

MODULE_FIRMWARE("cs46xx/cwc4630");
MODULE_FIRMWARE("cs46xx/cwcasync");
MODULE_FIRMWARE("cs46xx/cwcsnoop");
MODULE_FIRMWARE("cs46xx/cwcbinhack");
MODULE_FIRMWARE("cs46xx/cwcdma");

अटल व्योम मुक्त_module_desc(काष्ठा dsp_module_desc *module)
अणु
	अगर (!module)
		वापस;
	kमुक्त(module->module_name);
	kमुक्त(module->symbol_table.symbols);
	अगर (module->segments) अणु
		पूर्णांक i;
		क्रम (i = 0; i < module->nsegments; i++)
			kमुक्त(module->segments[i].data);
		kमुक्त(module->segments);
	पूर्ण
	kमुक्त(module);
पूर्ण

/* firmware binary क्रमmat:
 * le32 nsymbols;
 * काष्ठा अणु
 *	le32 address;
 *	अक्षर symbol_name[DSP_MAX_SYMBOL_NAME];
 *	le32 symbol_type;
 * पूर्ण symbols[nsymbols];
 * le32 nsegments;
 * काष्ठा अणु
 *	le32 segment_type;
 *	le32 offset;
 *	le32 size;
 *	le32 data[size];
 * पूर्ण segments[nsegments];
 */

अटल पूर्णांक load_firmware(काष्ठा snd_cs46xx *chip,
			 काष्ठा dsp_module_desc **module_ret,
			 स्थिर अक्षर *fw_name)
अणु
	पूर्णांक i, err;
	अचिन्हित पूर्णांक nums, fwlen, fwsize;
	स्थिर __le32 *fwdat;
	काष्ठा dsp_module_desc *module = शून्य;
	स्थिर काष्ठा firmware *fw;
	अक्षर fw_path[32];

	प्र_लिखो(fw_path, "cs46xx/%s", fw_name);
	err = request_firmware(&fw, fw_path, &chip->pci->dev);
	अगर (err < 0)
		वापस err;
	fwsize = fw->size / 4;
	अगर (fwsize < 2) अणु
		err = -EINVAL;
		जाओ error;
	पूर्ण

	err = -ENOMEM;
	module = kzalloc(माप(*module), GFP_KERNEL);
	अगर (!module)
		जाओ error;
	module->module_name = kstrdup(fw_name, GFP_KERNEL);
	अगर (!module->module_name)
		जाओ error;

	fwlen = 0;
	fwdat = (स्थिर __le32 *)fw->data;
	nums = module->symbol_table.nsymbols = le32_to_cpu(fwdat[fwlen++]);
	अगर (nums >= 40)
		जाओ error_inval;
	module->symbol_table.symbols =
		kसुस्मृति(nums, माप(काष्ठा dsp_symbol_entry), GFP_KERNEL);
	अगर (!module->symbol_table.symbols)
		जाओ error;
	क्रम (i = 0; i < nums; i++) अणु
		काष्ठा dsp_symbol_entry *entry =
			&module->symbol_table.symbols[i];
		अगर (fwlen + 2 + DSP_MAX_SYMBOL_NAME / 4 > fwsize)
			जाओ error_inval;
		entry->address = le32_to_cpu(fwdat[fwlen++]);
		स_नकल(entry->symbol_name, &fwdat[fwlen], DSP_MAX_SYMBOL_NAME - 1);
		fwlen += DSP_MAX_SYMBOL_NAME / 4;
		entry->symbol_type = le32_to_cpu(fwdat[fwlen++]);
	पूर्ण

	अगर (fwlen >= fwsize)
		जाओ error_inval;
	nums = module->nsegments = le32_to_cpu(fwdat[fwlen++]);
	अगर (nums > 10)
		जाओ error_inval;
	module->segments =
		kसुस्मृति(nums, माप(काष्ठा dsp_segment_desc), GFP_KERNEL);
	अगर (!module->segments)
		जाओ error;
	क्रम (i = 0; i < nums; i++) अणु
		काष्ठा dsp_segment_desc *entry = &module->segments[i];
		अगर (fwlen + 3 > fwsize)
			जाओ error_inval;
		entry->segment_type = le32_to_cpu(fwdat[fwlen++]);
		entry->offset = le32_to_cpu(fwdat[fwlen++]);
		entry->size = le32_to_cpu(fwdat[fwlen++]);
		अगर (fwlen + entry->size > fwsize)
			जाओ error_inval;
		entry->data = kदो_स्मृति_array(entry->size, 4, GFP_KERNEL);
		अगर (!entry->data)
			जाओ error;
		स_नकल_le32(entry->data, &fwdat[fwlen], entry->size * 4);
		fwlen += entry->size;
	पूर्ण

	*module_ret = module;
	release_firmware(fw);
	वापस 0;

 error_inval:
	err = -EINVAL;
 error:
	मुक्त_module_desc(module);
	release_firmware(fw);
	वापस err;
पूर्ण

पूर्णांक snd_cs46xx_clear_BA1(काष्ठा snd_cs46xx *chip,
                         अचिन्हित दीर्घ offset,
                         अचिन्हित दीर्घ len) 
अणु
	व्योम __iomem *dst;
	अचिन्हित पूर्णांक bank = offset >> 16;
	offset = offset & 0xffff;

	अगर (snd_BUG_ON((offset & 3) || (len & 3)))
		वापस -EINVAL;
	dst = chip->region.idx[bank+1].remap_addr + offset;
	len /= माप(u32);

	/* ग_लिखोl alपढ़ोy converts 32-bit value to right endianess */
	जबतक (len-- > 0) अणु
		ग_लिखोl(0, dst);
		dst += माप(u32);
	पूर्ण
	वापस 0;
पूर्ण

#अन्यथा /* old DSP image */

काष्ठा ba1_काष्ठा अणु
	काष्ठा अणु
		u32 offset;
		u32 size;
	पूर्ण memory[BA1_MEMORY_COUNT];
	u32 map[BA1_DWORD_SIZE];
पूर्ण;

MODULE_FIRMWARE("cs46xx/ba1");

अटल पूर्णांक load_firmware(काष्ठा snd_cs46xx *chip)
अणु
	स्थिर काष्ठा firmware *fw;
	पूर्णांक i, size, err;

	err = request_firmware(&fw, "cs46xx/ba1", &chip->pci->dev);
	अगर (err < 0)
		वापस err;
	अगर (fw->size != माप(*chip->ba1)) अणु
		err = -EINVAL;
		जाओ error;
	पूर्ण

	chip->ba1 = vदो_स्मृति(माप(*chip->ba1));
	अगर (!chip->ba1) अणु
		err = -ENOMEM;
		जाओ error;
	पूर्ण

	स_नकल_le32(chip->ba1, fw->data, माप(*chip->ba1));

	/* sanity check */
	size = 0;
	क्रम (i = 0; i < BA1_MEMORY_COUNT; i++)
		size += chip->ba1->memory[i].size;
	अगर (size > BA1_DWORD_SIZE * 4)
		err = -EINVAL;

 error:
	release_firmware(fw);
	वापस err;
पूर्ण

पूर्णांक snd_cs46xx_करोwnload_image(काष्ठा snd_cs46xx *chip)
अणु
	पूर्णांक idx, err;
	अचिन्हित पूर्णांक offset = 0;
	काष्ठा ba1_काष्ठा *ba1 = chip->ba1;

	क्रम (idx = 0; idx < BA1_MEMORY_COUNT; idx++) अणु
		err = snd_cs46xx_करोwnload(chip,
					  &ba1->map[offset],
					  ba1->memory[idx].offset,
					  ba1->memory[idx].size);
		अगर (err < 0)
			वापस err;
		offset += ba1->memory[idx].size >> 2;
	पूर्ण	
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SND_CS46XX_NEW_DSP */

/*
 *  Chip reset
 */

अटल व्योम snd_cs46xx_reset(काष्ठा snd_cs46xx *chip)
अणु
	पूर्णांक idx;

	/*
	 *  Write the reset bit of the SP control रेजिस्टर.
	 */
	snd_cs46xx_poke(chip, BA1_SPCR, SPCR_RSTSP);

	/*
	 *  Write the control रेजिस्टर.
	 */
	snd_cs46xx_poke(chip, BA1_SPCR, SPCR_DRQEN);

	/*
	 *  Clear the trap रेजिस्टरs.
	 */
	क्रम (idx = 0; idx < 8; idx++) अणु
		snd_cs46xx_poke(chip, BA1_DREG, DREG_REGID_TRAP_SELECT + idx);
		snd_cs46xx_poke(chip, BA1_TWPR, 0xFFFF);
	पूर्ण
	snd_cs46xx_poke(chip, BA1_DREG, 0);

	/*
	 *  Set the frame समयr to reflect the number of cycles per frame.
	 */
	snd_cs46xx_poke(chip, BA1_FRMT, 0xadf);
पूर्ण

अटल पूर्णांक cs46xx_रुको_क्रम_fअगरo(काष्ठा snd_cs46xx * chip,पूर्णांक retry_समयout) 
अणु
	u32 i, status = 0;
	/*
	 * Make sure the previous FIFO ग_लिखो operation has completed.
	 */
	क्रम(i = 0; i < 50; i++)अणु
		status = snd_cs46xx_peekBA0(chip, BA0_SERBST);
    
		अगर( !(status & SERBST_WBSY) )
			अवरोध;

		mdelay(retry_समयout);
	पूर्ण
  
	अगर(status & SERBST_WBSY) अणु
		dev_err(chip->card->dev,
			"failure waiting for FIFO command to complete\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम snd_cs46xx_clear_serial_FIFOs(काष्ठा snd_cs46xx *chip)
अणु
	पूर्णांक idx, घातerकरोwn = 0;
	अचिन्हित पूर्णांक पंचांगp;

	/*
	 *  See अगर the devices are घातered करोwn.  If so, we must घातer them up first
	 *  or they will not respond.
	 */
	पंचांगp = snd_cs46xx_peekBA0(chip, BA0_CLKCR1);
	अगर (!(पंचांगp & CLKCR1_SWCE)) अणु
		snd_cs46xx_pokeBA0(chip, BA0_CLKCR1, पंचांगp | CLKCR1_SWCE);
		घातerकरोwn = 1;
	पूर्ण

	/*
	 *  We want to clear out the serial port FIFOs so we करोn't end up playing
	 *  whatever अक्रमom garbage happens to be in them.  We fill the sample FIFOS
	 *  with zero (silence).
	 */
	snd_cs46xx_pokeBA0(chip, BA0_SERBWP, 0);

	/*
	 *  Fill all 256 sample FIFO locations.
	 */
	क्रम (idx = 0; idx < 0xFF; idx++) अणु
		/*
		 *  Make sure the previous FIFO ग_लिखो operation has completed.
		 */
		अगर (cs46xx_रुको_क्रम_fअगरo(chip,1)) अणु
			dev_dbg(chip->card->dev,
				"failed waiting for FIFO at addr (%02X)\n",
				idx);

			अगर (घातerकरोwn)
				snd_cs46xx_pokeBA0(chip, BA0_CLKCR1, पंचांगp);
          
			अवरोध;
		पूर्ण
		/*
		 *  Write the serial port FIFO index.
		 */
		snd_cs46xx_pokeBA0(chip, BA0_SERBAD, idx);
		/*
		 *  Tell the serial port to load the new value पूर्णांकo the FIFO location.
		 */
		snd_cs46xx_pokeBA0(chip, BA0_SERBCM, SERBCM_WRC);
	पूर्ण
	/*
	 *  Now, अगर we घातered up the devices, then घातer them back करोwn again.
	 *  This is kinda ugly, but should never happen.
	 */
	अगर (घातerकरोwn)
		snd_cs46xx_pokeBA0(chip, BA0_CLKCR1, पंचांगp);
पूर्ण

अटल व्योम snd_cs46xx_proc_start(काष्ठा snd_cs46xx *chip)
अणु
	पूर्णांक cnt;

	/*
	 *  Set the frame समयr to reflect the number of cycles per frame.
	 */
	snd_cs46xx_poke(chip, BA1_FRMT, 0xadf);
	/*
	 *  Turn on the run, run at frame, and DMA enable bits in the local copy of
	 *  the SP control रेजिस्टर.
	 */
	snd_cs46xx_poke(chip, BA1_SPCR, SPCR_RUN | SPCR_RUNFR | SPCR_DRQEN);
	/*
	 *  Wait until the run at frame bit resets itself in the SP control
	 *  रेजिस्टर.
	 */
	क्रम (cnt = 0; cnt < 25; cnt++) अणु
		udelay(50);
		अगर (!(snd_cs46xx_peek(chip, BA1_SPCR) & SPCR_RUNFR))
			अवरोध;
	पूर्ण

	अगर (snd_cs46xx_peek(chip, BA1_SPCR) & SPCR_RUNFR)
		dev_err(chip->card->dev, "SPCR_RUNFR never reset\n");
पूर्ण

अटल व्योम snd_cs46xx_proc_stop(काष्ठा snd_cs46xx *chip)
अणु
	/*
	 *  Turn off the run, run at frame, and DMA enable bits in the local copy of
	 *  the SP control रेजिस्टर.
	 */
	snd_cs46xx_poke(chip, BA1_SPCR, 0);
पूर्ण

/*
 *  Sample rate routines
 */

#घोषणा GOF_PER_SEC 200

अटल व्योम snd_cs46xx_set_play_sample_rate(काष्ठा snd_cs46xx *chip, अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक पंचांगp1, पंचांगp2;
	अचिन्हित पूर्णांक phiIncr;
	अचिन्हित पूर्णांक correctionPerGOF, correctionPerSec;

	/*
	 *  Compute the values used to drive the actual sample rate conversion.
	 *  The following क्रमmulas are being computed, using अंतरभूत assembly
	 *  since we need to use 64 bit arithmetic to compute the values:
	 *
	 *  phiIncr = न्यूनमान((Fs,in * 2^26) / Fs,out)
	 *  correctionPerGOF = न्यूनमान((Fs,in * 2^26 - Fs,out * phiIncr) /
         *                                   GOF_PER_SEC)
         *  ulCorrectionPerSec = Fs,in * 2^26 - Fs,out * phiIncr -M
         *                       GOF_PER_SEC * correctionPerGOF
	 *
	 *  i.e.
	 *
	 *  phiIncr:other = भागidend:reमुख्यder((Fs,in * 2^26) / Fs,out)
	 *  correctionPerGOF:correctionPerSec =
	 *      भागidend:reमुख्यder(ulOther / GOF_PER_SEC)
	 */
	पंचांगp1 = rate << 16;
	phiIncr = पंचांगp1 / 48000;
	पंचांगp1 -= phiIncr * 48000;
	पंचांगp1 <<= 10;
	phiIncr <<= 10;
	पंचांगp2 = पंचांगp1 / 48000;
	phiIncr += पंचांगp2;
	पंचांगp1 -= पंचांगp2 * 48000;
	correctionPerGOF = पंचांगp1 / GOF_PER_SEC;
	पंचांगp1 -= correctionPerGOF * GOF_PER_SEC;
	correctionPerSec = पंचांगp1;

	/*
	 *  Fill in the SampleRateConverter control block.
	 */
	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_cs46xx_poke(chip, BA1_PSRC,
	  ((correctionPerSec << 16) & 0xFFFF0000) | (correctionPerGOF & 0xFFFF));
	snd_cs46xx_poke(chip, BA1_PPI, phiIncr);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
पूर्ण

अटल व्योम snd_cs46xx_set_capture_sample_rate(काष्ठा snd_cs46xx *chip, अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक phiIncr, coeffIncr, पंचांगp1, पंचांगp2;
	अचिन्हित पूर्णांक correctionPerGOF, correctionPerSec, initialDelay;
	अचिन्हित पूर्णांक frameGroupLength, cnt;

	/*
	 *  We can only decimate by up to a factor of 1/9th the hardware rate.
	 *  Correct the value अगर an attempt is made to stray outside that limit.
	 */
	अगर ((rate * 9) < 48000)
		rate = 48000 / 9;

	/*
	 *  We can not capture at a rate greater than the Input Rate (48000).
	 *  Return an error अगर an attempt is made to stray outside that limit.
	 */
	अगर (rate > 48000)
		rate = 48000;

	/*
	 *  Compute the values used to drive the actual sample rate conversion.
	 *  The following क्रमmulas are being computed, using अंतरभूत assembly
	 *  since we need to use 64 bit arithmetic to compute the values:
	 *
	 *     coeffIncr = -न्यूनमान((Fs,out * 2^23) / Fs,in)
	 *     phiIncr = न्यूनमान((Fs,in * 2^26) / Fs,out)
	 *     correctionPerGOF = न्यूनमान((Fs,in * 2^26 - Fs,out * phiIncr) /
	 *                                GOF_PER_SEC)
	 *     correctionPerSec = Fs,in * 2^26 - Fs,out * phiIncr -
	 *                          GOF_PER_SEC * correctionPerGOF
	 *     initialDelay = उच्चमान((24 * Fs,in) / Fs,out)
	 *
	 * i.e.
	 *
	 *     coeffIncr = neg(भागidend((Fs,out * 2^23) / Fs,in))
	 *     phiIncr:ulOther = भागidend:reमुख्यder((Fs,in * 2^26) / Fs,out)
	 *     correctionPerGOF:correctionPerSec =
	 * 	    भागidend:reमुख्यder(ulOther / GOF_PER_SEC)
	 *     initialDelay = भागidend(((24 * Fs,in) + Fs,out - 1) / Fs,out)
	 */

	पंचांगp1 = rate << 16;
	coeffIncr = पंचांगp1 / 48000;
	पंचांगp1 -= coeffIncr * 48000;
	पंचांगp1 <<= 7;
	coeffIncr <<= 7;
	coeffIncr += पंचांगp1 / 48000;
	coeffIncr ^= 0xFFFFFFFF;
	coeffIncr++;
	पंचांगp1 = 48000 << 16;
	phiIncr = पंचांगp1 / rate;
	पंचांगp1 -= phiIncr * rate;
	पंचांगp1 <<= 10;
	phiIncr <<= 10;
	पंचांगp2 = पंचांगp1 / rate;
	phiIncr += पंचांगp2;
	पंचांगp1 -= पंचांगp2 * rate;
	correctionPerGOF = पंचांगp1 / GOF_PER_SEC;
	पंचांगp1 -= correctionPerGOF * GOF_PER_SEC;
	correctionPerSec = पंचांगp1;
	initialDelay = DIV_ROUND_UP(48000 * 24, rate);

	/*
	 *  Fill in the VariDecimate control block.
	 */
	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_cs46xx_poke(chip, BA1_CSRC,
		((correctionPerSec << 16) & 0xFFFF0000) | (correctionPerGOF & 0xFFFF));
	snd_cs46xx_poke(chip, BA1_CCI, coeffIncr);
	snd_cs46xx_poke(chip, BA1_CD,
		(((BA1_VARIDEC_BUF_1 + (initialDelay << 2)) << 16) & 0xFFFF0000) | 0x80);
	snd_cs46xx_poke(chip, BA1_CPI, phiIncr);
	spin_unlock_irqrestore(&chip->reg_lock, flags);

	/*
	 *  Figure out the frame group length क्रम the ग_लिखो back task.  Basically,
	 *  this is just the factors of 24000 (2^6*3*5^3) that are not present in
	 *  the output sample rate.
	 */
	frameGroupLength = 1;
	क्रम (cnt = 2; cnt <= 64; cnt *= 2) अणु
		अगर (((rate / cnt) * cnt) != rate)
			frameGroupLength *= 2;
	पूर्ण
	अगर (((rate / 3) * 3) != rate) अणु
		frameGroupLength *= 3;
	पूर्ण
	क्रम (cnt = 5; cnt <= 125; cnt *= 5) अणु
		अगर (((rate / cnt) * cnt) != rate) 
			frameGroupLength *= 5;
        पूर्ण

	/*
	 * Fill in the WriteBack control block.
	 */
	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_cs46xx_poke(chip, BA1_CFG1, frameGroupLength);
	snd_cs46xx_poke(chip, BA1_CFG2, (0x00800000 | frameGroupLength));
	snd_cs46xx_poke(chip, BA1_CCST, 0x0000FFFF);
	snd_cs46xx_poke(chip, BA1_CSPB, ((65536 * rate) / 24000));
	snd_cs46xx_poke(chip, (BA1_CSPB + 4), 0x0000FFFF);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
पूर्ण

/*
 *  PCM part
 */

अटल व्योम snd_cs46xx_pb_trans_copy(काष्ठा snd_pcm_substream *substream,
				     काष्ठा snd_pcm_indirect *rec, माप_प्रकार bytes)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_cs46xx_pcm * cpcm = runसमय->निजी_data;
	स_नकल(cpcm->hw_buf.area + rec->hw_data, runसमय->dma_area + rec->sw_data, bytes);
पूर्ण

अटल पूर्णांक snd_cs46xx_playback_transfer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_cs46xx_pcm * cpcm = runसमय->निजी_data;
	वापस snd_pcm_indirect_playback_transfer(substream, &cpcm->pcm_rec,
						  snd_cs46xx_pb_trans_copy);
पूर्ण

अटल व्योम snd_cs46xx_cp_trans_copy(काष्ठा snd_pcm_substream *substream,
				     काष्ठा snd_pcm_indirect *rec, माप_प्रकार bytes)
अणु
	काष्ठा snd_cs46xx *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	स_नकल(runसमय->dma_area + rec->sw_data,
	       chip->capt.hw_buf.area + rec->hw_data, bytes);
पूर्ण

अटल पूर्णांक snd_cs46xx_capture_transfer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_cs46xx *chip = snd_pcm_substream_chip(substream);
	वापस snd_pcm_indirect_capture_transfer(substream, &chip->capt.pcm_rec,
						 snd_cs46xx_cp_trans_copy);
पूर्ण

अटल snd_pcm_uframes_t snd_cs46xx_playback_direct_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_cs46xx *chip = snd_pcm_substream_chip(substream);
	माप_प्रकार ptr;
	काष्ठा snd_cs46xx_pcm *cpcm = substream->runसमय->निजी_data;

	अगर (snd_BUG_ON(!cpcm->pcm_channel))
		वापस -ENXIO;

#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	ptr = snd_cs46xx_peek(chip, (cpcm->pcm_channel->pcm_पढ़ोer_scb->address + 2) << 2);
#अन्यथा
	ptr = snd_cs46xx_peek(chip, BA1_PBA);
#पूर्ण_अगर
	ptr -= cpcm->hw_buf.addr;
	वापस ptr >> cpcm->shअगरt;
पूर्ण

अटल snd_pcm_uframes_t snd_cs46xx_playback_indirect_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_cs46xx *chip = snd_pcm_substream_chip(substream);
	माप_प्रकार ptr;
	काष्ठा snd_cs46xx_pcm *cpcm = substream->runसमय->निजी_data;

#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	अगर (snd_BUG_ON(!cpcm->pcm_channel))
		वापस -ENXIO;
	ptr = snd_cs46xx_peek(chip, (cpcm->pcm_channel->pcm_पढ़ोer_scb->address + 2) << 2);
#अन्यथा
	ptr = snd_cs46xx_peek(chip, BA1_PBA);
#पूर्ण_अगर
	ptr -= cpcm->hw_buf.addr;
	वापस snd_pcm_indirect_playback_poपूर्णांकer(substream, &cpcm->pcm_rec, ptr);
पूर्ण

अटल snd_pcm_uframes_t snd_cs46xx_capture_direct_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_cs46xx *chip = snd_pcm_substream_chip(substream);
	माप_प्रकार ptr = snd_cs46xx_peek(chip, BA1_CBA) - chip->capt.hw_buf.addr;
	वापस ptr >> chip->capt.shअगरt;
पूर्ण

अटल snd_pcm_uframes_t snd_cs46xx_capture_indirect_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_cs46xx *chip = snd_pcm_substream_chip(substream);
	माप_प्रकार ptr = snd_cs46xx_peek(chip, BA1_CBA) - chip->capt.hw_buf.addr;
	वापस snd_pcm_indirect_capture_poपूर्णांकer(substream, &chip->capt.pcm_rec, ptr);
पूर्ण

अटल पूर्णांक snd_cs46xx_playback_trigger(काष्ठा snd_pcm_substream *substream,
				       पूर्णांक cmd)
अणु
	काष्ठा snd_cs46xx *chip = snd_pcm_substream_chip(substream);
	/*काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;*/
	पूर्णांक result = 0;

#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	काष्ठा snd_cs46xx_pcm *cpcm = substream->runसमय->निजी_data;
	अगर (! cpcm->pcm_channel) अणु
		वापस -ENXIO;
	पूर्ण
#पूर्ण_अगर
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
		/* magic value to unmute PCM stream  playback volume */
		snd_cs46xx_poke(chip, (cpcm->pcm_channel->pcm_पढ़ोer_scb->address + 
				       SCBVolumeCtrl) << 2, 0x80008000);

		अगर (cpcm->pcm_channel->unlinked)
			cs46xx_dsp_pcm_link(chip,cpcm->pcm_channel);

		अगर (substream->runसमय->periods != CS46XX_FRAGS)
			snd_cs46xx_playback_transfer(substream);
#अन्यथा
		spin_lock(&chip->reg_lock);
		अगर (substream->runसमय->periods != CS46XX_FRAGS)
			snd_cs46xx_playback_transfer(substream);
		अणु अचिन्हित पूर्णांक पंचांगp;
		पंचांगp = snd_cs46xx_peek(chip, BA1_PCTL);
		पंचांगp &= 0x0000ffff;
		snd_cs46xx_poke(chip, BA1_PCTL, chip->play_ctl | पंचांगp);
		पूर्ण
		spin_unlock(&chip->reg_lock);
#पूर्ण_अगर
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
		/* magic mute channel */
		snd_cs46xx_poke(chip, (cpcm->pcm_channel->pcm_पढ़ोer_scb->address + 
				       SCBVolumeCtrl) << 2, 0xffffffff);

		अगर (!cpcm->pcm_channel->unlinked)
			cs46xx_dsp_pcm_unlink(chip,cpcm->pcm_channel);
#अन्यथा
		spin_lock(&chip->reg_lock);
		अणु अचिन्हित पूर्णांक पंचांगp;
		पंचांगp = snd_cs46xx_peek(chip, BA1_PCTL);
		पंचांगp &= 0x0000ffff;
		snd_cs46xx_poke(chip, BA1_PCTL, पंचांगp);
		पूर्ण
		spin_unlock(&chip->reg_lock);
#पूर्ण_अगर
		अवरोध;
	शेष:
		result = -EINVAL;
		अवरोध;
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक snd_cs46xx_capture_trigger(काष्ठा snd_pcm_substream *substream,
				      पूर्णांक cmd)
अणु
	काष्ठा snd_cs46xx *chip = snd_pcm_substream_chip(substream);
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक result = 0;

	spin_lock(&chip->reg_lock);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		पंचांगp = snd_cs46xx_peek(chip, BA1_CCTL);
		पंचांगp &= 0xffff0000;
		snd_cs46xx_poke(chip, BA1_CCTL, chip->capt.ctl | पंचांगp);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		पंचांगp = snd_cs46xx_peek(chip, BA1_CCTL);
		पंचांगp &= 0xffff0000;
		snd_cs46xx_poke(chip, BA1_CCTL, पंचांगp);
		अवरोध;
	शेष:
		result = -EINVAL;
		अवरोध;
	पूर्ण
	spin_unlock(&chip->reg_lock);

	वापस result;
पूर्ण

#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
अटल पूर्णांक _cs46xx_adjust_sample_rate (काष्ठा snd_cs46xx *chip, काष्ठा snd_cs46xx_pcm *cpcm,
				       पूर्णांक sample_rate) 
अणु

	/* If PCMReaderSCB and SrcTaskSCB not created yet ... */
	अगर ( cpcm->pcm_channel == शून्य) अणु
		cpcm->pcm_channel = cs46xx_dsp_create_pcm_channel (chip, sample_rate, 
								   cpcm, cpcm->hw_buf.addr,cpcm->pcm_channel_id);
		अगर (cpcm->pcm_channel == शून्य) अणु
			dev_err(chip->card->dev,
				"failed to create virtual PCM channel\n");
			वापस -ENOMEM;
		पूर्ण
		cpcm->pcm_channel->sample_rate = sample_rate;
	पूर्ण अन्यथा
	/* अगर sample rate is changed */
	अगर ((पूर्णांक)cpcm->pcm_channel->sample_rate != sample_rate) अणु
		पूर्णांक unlinked = cpcm->pcm_channel->unlinked;
		cs46xx_dsp_destroy_pcm_channel (chip,cpcm->pcm_channel);

		अगर ( (cpcm->pcm_channel = cs46xx_dsp_create_pcm_channel (chip, sample_rate, cpcm, 
									 cpcm->hw_buf.addr,
									 cpcm->pcm_channel_id)) == शून्य) अणु
			dev_err(chip->card->dev,
				"failed to re-create virtual PCM channel\n");
			वापस -ENOMEM;
		पूर्ण

		अगर (!unlinked) cs46xx_dsp_pcm_link (chip,cpcm->pcm_channel);
		cpcm->pcm_channel->sample_rate = sample_rate;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर


अटल पूर्णांक snd_cs46xx_playback_hw_params(काष्ठा snd_pcm_substream *substream,
					 काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_cs46xx_pcm *cpcm;
	पूर्णांक err;
#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	काष्ठा snd_cs46xx *chip = snd_pcm_substream_chip(substream);
	पूर्णांक sample_rate = params_rate(hw_params);
	पूर्णांक period_size = params_period_bytes(hw_params);
#पूर्ण_अगर
	cpcm = runसमय->निजी_data;

#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	अगर (snd_BUG_ON(!sample_rate))
		वापस -ENXIO;

	mutex_lock(&chip->spos_mutex);

	अगर (_cs46xx_adjust_sample_rate (chip,cpcm,sample_rate)) अणु
		mutex_unlock(&chip->spos_mutex);
		वापस -ENXIO;
	पूर्ण

	snd_BUG_ON(!cpcm->pcm_channel);
	अगर (!cpcm->pcm_channel) अणु
		mutex_unlock(&chip->spos_mutex);
		वापस -ENXIO;
	पूर्ण


	अगर (cs46xx_dsp_pcm_channel_set_period (chip,cpcm->pcm_channel,period_size)) अणु
		 mutex_unlock(&chip->spos_mutex);
		 वापस -EINVAL;
	 पूर्ण

	dev_dbg(chip->card->dev,
		"period_size (%d), periods (%d) buffer_size(%d)\n",
		     period_size, params_periods(hw_params),
		     params_buffer_bytes(hw_params));
#पूर्ण_अगर

	अगर (params_periods(hw_params) == CS46XX_FRAGS) अणु
		अगर (runसमय->dma_area != cpcm->hw_buf.area)
			snd_pcm_lib_मुक्त_pages(substream);
		runसमय->dma_area = cpcm->hw_buf.area;
		runसमय->dma_addr = cpcm->hw_buf.addr;
		runसमय->dma_bytes = cpcm->hw_buf.bytes;


#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
		अगर (cpcm->pcm_channel_id == DSP_PCM_MAIN_CHANNEL) अणु
			substream->ops = &snd_cs46xx_playback_ops;
		पूर्ण अन्यथा अगर (cpcm->pcm_channel_id == DSP_PCM_REAR_CHANNEL) अणु
			substream->ops = &snd_cs46xx_playback_rear_ops;
		पूर्ण अन्यथा अगर (cpcm->pcm_channel_id == DSP_PCM_CENTER_LFE_CHANNEL) अणु
			substream->ops = &snd_cs46xx_playback_clfe_ops;
		पूर्ण अन्यथा अगर (cpcm->pcm_channel_id == DSP_IEC958_CHANNEL) अणु
			substream->ops = &snd_cs46xx_playback_iec958_ops;
		पूर्ण अन्यथा अणु
			snd_BUG();
		पूर्ण
#अन्यथा
		substream->ops = &snd_cs46xx_playback_ops;
#पूर्ण_अगर

	पूर्ण अन्यथा अणु
		अगर (runसमय->dma_area == cpcm->hw_buf.area) अणु
			runसमय->dma_area = शून्य;
			runसमय->dma_addr = 0;
			runसमय->dma_bytes = 0;
		पूर्ण
		अगर ((err = snd_pcm_lib_दो_स्मृति_pages(substream, params_buffer_bytes(hw_params))) < 0) अणु
#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
			mutex_unlock(&chip->spos_mutex);
#पूर्ण_अगर
			वापस err;
		पूर्ण

#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
		अगर (cpcm->pcm_channel_id == DSP_PCM_MAIN_CHANNEL) अणु
			substream->ops = &snd_cs46xx_playback_indirect_ops;
		पूर्ण अन्यथा अगर (cpcm->pcm_channel_id == DSP_PCM_REAR_CHANNEL) अणु
			substream->ops = &snd_cs46xx_playback_indirect_rear_ops;
		पूर्ण अन्यथा अगर (cpcm->pcm_channel_id == DSP_PCM_CENTER_LFE_CHANNEL) अणु
			substream->ops = &snd_cs46xx_playback_indirect_clfe_ops;
		पूर्ण अन्यथा अगर (cpcm->pcm_channel_id == DSP_IEC958_CHANNEL) अणु
			substream->ops = &snd_cs46xx_playback_indirect_iec958_ops;
		पूर्ण अन्यथा अणु
			snd_BUG();
		पूर्ण
#अन्यथा
		substream->ops = &snd_cs46xx_playback_indirect_ops;
#पूर्ण_अगर

	पूर्ण

#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	mutex_unlock(&chip->spos_mutex);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs46xx_playback_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	/*काष्ठा snd_cs46xx *chip = snd_pcm_substream_chip(substream);*/
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_cs46xx_pcm *cpcm;

	cpcm = runसमय->निजी_data;

	/* अगर play_back खोलो fails, then this function
	   is called and cpcm can actually be शून्य here */
	अगर (!cpcm) वापस -ENXIO;

	अगर (runसमय->dma_area != cpcm->hw_buf.area)
		snd_pcm_lib_मुक्त_pages(substream);
    
	runसमय->dma_area = शून्य;
	runसमय->dma_addr = 0;
	runसमय->dma_bytes = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs46xx_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	अचिन्हित पूर्णांक pfie;
	काष्ठा snd_cs46xx *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_cs46xx_pcm *cpcm;

	cpcm = runसमय->निजी_data;

#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	अगर (snd_BUG_ON(!cpcm->pcm_channel))
		वापस -ENXIO;

	pfie = snd_cs46xx_peek(chip, (cpcm->pcm_channel->pcm_पढ़ोer_scb->address + 1) << 2 );
	pfie &= ~0x0000f03f;
#अन्यथा
	/* old dsp */
	pfie = snd_cs46xx_peek(chip, BA1_PFIE);
 	pfie &= ~0x0000f03f;
#पूर्ण_अगर

	cpcm->shअगरt = 2;
	/* अगर to convert from stereo to mono */
	अगर (runसमय->channels == 1) अणु
		cpcm->shअगरt--;
		pfie |= 0x00002000;
	पूर्ण
	/* अगर to convert from 8 bit to 16 bit */
	अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 8) अणु
		cpcm->shअगरt--;
		pfie |= 0x00001000;
	पूर्ण
	/* अगर to convert to अचिन्हित */
	अगर (snd_pcm_क्रमmat_अचिन्हित(runसमय->क्रमmat))
		pfie |= 0x00008000;

	/* Never convert byte order when sample stream is 8 bit */
	अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) != 8) अणु
		/* convert from big endian to little endian */
		अगर (snd_pcm_क्रमmat_big_endian(runसमय->क्रमmat))
			pfie |= 0x00004000;
	पूर्ण
	
	स_रखो(&cpcm->pcm_rec, 0, माप(cpcm->pcm_rec));
	cpcm->pcm_rec.sw_buffer_size = snd_pcm_lib_buffer_bytes(substream);
	cpcm->pcm_rec.hw_buffer_size = runसमय->period_size * CS46XX_FRAGS << cpcm->shअगरt;

#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP

	पंचांगp = snd_cs46xx_peek(chip, (cpcm->pcm_channel->pcm_पढ़ोer_scb->address) << 2);
	पंचांगp &= ~0x000003ff;
	पंचांगp |= (4 << cpcm->shअगरt) - 1;
	/* playback transaction count रेजिस्टर */
	snd_cs46xx_poke(chip, (cpcm->pcm_channel->pcm_पढ़ोer_scb->address) << 2, पंचांगp);

	/* playback क्रमmat && पूर्णांकerrupt enable */
	snd_cs46xx_poke(chip, (cpcm->pcm_channel->pcm_पढ़ोer_scb->address + 1) << 2, pfie | cpcm->pcm_channel->pcm_slot);
#अन्यथा
	snd_cs46xx_poke(chip, BA1_PBA, cpcm->hw_buf.addr);
	पंचांगp = snd_cs46xx_peek(chip, BA1_PDTC);
	पंचांगp &= ~0x000003ff;
	पंचांगp |= (4 << cpcm->shअगरt) - 1;
	snd_cs46xx_poke(chip, BA1_PDTC, पंचांगp);
	snd_cs46xx_poke(chip, BA1_PFIE, pfie);
	snd_cs46xx_set_play_sample_rate(chip, runसमय->rate);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs46xx_capture_hw_params(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_cs46xx *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	cs46xx_dsp_pcm_ostream_set_period (chip, params_period_bytes(hw_params));
#पूर्ण_अगर
	अगर (runसमय->periods == CS46XX_FRAGS) अणु
		अगर (runसमय->dma_area != chip->capt.hw_buf.area)
			snd_pcm_lib_मुक्त_pages(substream);
		runसमय->dma_area = chip->capt.hw_buf.area;
		runसमय->dma_addr = chip->capt.hw_buf.addr;
		runसमय->dma_bytes = chip->capt.hw_buf.bytes;
		substream->ops = &snd_cs46xx_capture_ops;
	पूर्ण अन्यथा अणु
		अगर (runसमय->dma_area == chip->capt.hw_buf.area) अणु
			runसमय->dma_area = शून्य;
			runसमय->dma_addr = 0;
			runसमय->dma_bytes = 0;
		पूर्ण
		अगर ((err = snd_pcm_lib_दो_स्मृति_pages(substream, params_buffer_bytes(hw_params))) < 0)
			वापस err;
		substream->ops = &snd_cs46xx_capture_indirect_ops;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs46xx_capture_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_cs46xx *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	अगर (runसमय->dma_area != chip->capt.hw_buf.area)
		snd_pcm_lib_मुक्त_pages(substream);
	runसमय->dma_area = शून्य;
	runसमय->dma_addr = 0;
	runसमय->dma_bytes = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs46xx_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_cs46xx *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	snd_cs46xx_poke(chip, BA1_CBA, chip->capt.hw_buf.addr);
	chip->capt.shअगरt = 2;
	स_रखो(&chip->capt.pcm_rec, 0, माप(chip->capt.pcm_rec));
	chip->capt.pcm_rec.sw_buffer_size = snd_pcm_lib_buffer_bytes(substream);
	chip->capt.pcm_rec.hw_buffer_size = runसमय->period_size * CS46XX_FRAGS << 2;
	snd_cs46xx_set_capture_sample_rate(chip, runसमय->rate);

	वापस 0;
पूर्ण

अटल irqवापस_t snd_cs46xx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_cs46xx *chip = dev_id;
	u32 status1;
#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	u32 status2;
	पूर्णांक i;
	काष्ठा snd_cs46xx_pcm *cpcm = शून्य;
#पूर्ण_अगर

	/*
	 *  Read the Interrupt Status Register to clear the पूर्णांकerrupt
	 */
	status1 = snd_cs46xx_peekBA0(chip, BA0_HISR);
	अगर ((status1 & 0x7fffffff) == 0) अणु
		snd_cs46xx_pokeBA0(chip, BA0_HICR, HICR_CHGM | HICR_IEV);
		वापस IRQ_NONE;
	पूर्ण

#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	status2 = snd_cs46xx_peekBA0(chip, BA0_HSR0);

	क्रम (i = 0; i < DSP_MAX_PCM_CHANNELS; ++i) अणु
		अगर (i <= 15) अणु
			अगर ( status1 & (1 << i) ) अणु
				अगर (i == CS46XX_DSP_CAPTURE_CHANNEL) अणु
					अगर (chip->capt.substream)
						snd_pcm_period_elapsed(chip->capt.substream);
				पूर्ण अन्यथा अणु
					अगर (ins->pcm_channels[i].active &&
					    ins->pcm_channels[i].निजी_data &&
					    !ins->pcm_channels[i].unlinked) अणु
						cpcm = ins->pcm_channels[i].निजी_data;
						snd_pcm_period_elapsed(cpcm->substream);
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर ( status2 & (1 << (i - 16))) अणु
				अगर (ins->pcm_channels[i].active && 
				    ins->pcm_channels[i].निजी_data &&
				    !ins->pcm_channels[i].unlinked) अणु
					cpcm = ins->pcm_channels[i].निजी_data;
					snd_pcm_period_elapsed(cpcm->substream);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

#अन्यथा
	/* old dsp */
	अगर ((status1 & HISR_VC0) && chip->playback_pcm) अणु
		अगर (chip->playback_pcm->substream)
			snd_pcm_period_elapsed(chip->playback_pcm->substream);
	पूर्ण
	अगर ((status1 & HISR_VC1) && chip->pcm) अणु
		अगर (chip->capt.substream)
			snd_pcm_period_elapsed(chip->capt.substream);
	पूर्ण
#पूर्ण_अगर

	अगर ((status1 & HISR_MIDI) && chip->rmidi) अणु
		अचिन्हित अक्षर c;
		
		spin_lock(&chip->reg_lock);
		जबतक ((snd_cs46xx_peekBA0(chip, BA0_MIDSR) & MIDSR_RBE) == 0) अणु
			c = snd_cs46xx_peekBA0(chip, BA0_MIDRP);
			अगर ((chip->midcr & MIDCR_RIE) == 0)
				जारी;
			snd_rawmidi_receive(chip->midi_input, &c, 1);
		पूर्ण
		जबतक ((snd_cs46xx_peekBA0(chip, BA0_MIDSR) & MIDSR_TBF) == 0) अणु
			अगर ((chip->midcr & MIDCR_TIE) == 0)
				अवरोध;
			अगर (snd_rawmidi_transmit(chip->midi_output, &c, 1) != 1) अणु
				chip->midcr &= ~MIDCR_TIE;
				snd_cs46xx_pokeBA0(chip, BA0_MIDCR, chip->midcr);
				अवरोध;
			पूर्ण
			snd_cs46xx_pokeBA0(chip, BA0_MIDWP, c);
		पूर्ण
		spin_unlock(&chip->reg_lock);
	पूर्ण
	/*
	 *  EOI to the PCI part....reenables पूर्णांकerrupts
	 */
	snd_cs46xx_pokeBA0(chip, BA0_HICR, HICR_CHGM | HICR_IEV);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_cs46xx_playback =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP |
				 SNDRV_PCM_INFO_INTERLEAVED | 
				 SNDRV_PCM_INFO_BLOCK_TRANSFER /*|*/
				 /*SNDRV_PCM_INFO_RESUME*/ |
				 SNDRV_PCM_INFO_SYNC_APPLPTR),
	.क्रमmats =		(SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_U8 |
				 SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S16_BE |
				 SNDRV_PCM_FMTBIT_U16_LE | SNDRV_PCM_FMTBIT_U16_BE),
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		5500,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(256 * 1024),
	.period_bytes_min =	CS46XX_MIN_PERIOD_SIZE,
	.period_bytes_max =	CS46XX_MAX_PERIOD_SIZE,
	.periods_min =		CS46XX_FRAGS,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_cs46xx_capture =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP |
				 SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER /*|*/
				 /*SNDRV_PCM_INFO_RESUME*/ |
				 SNDRV_PCM_INFO_SYNC_APPLPTR),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		5500,
	.rate_max =		48000,
	.channels_min =		2,
	.channels_max =		2,
	.buffer_bytes_max =	(256 * 1024),
	.period_bytes_min =	CS46XX_MIN_PERIOD_SIZE,
	.period_bytes_max =	CS46XX_MAX_PERIOD_SIZE,
	.periods_min =		CS46XX_FRAGS,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP

अटल स्थिर अचिन्हित पूर्णांक period_sizes[] = अणु 32, 64, 128, 256, 512, 1024, 2048 पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_स्थिरraपूर्णांकs_period_sizes = अणु
	.count = ARRAY_SIZE(period_sizes),
	.list = period_sizes,
	.mask = 0
पूर्ण;

#पूर्ण_अगर

अटल व्योम snd_cs46xx_pcm_मुक्त_substream(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	kमुक्त(runसमय->निजी_data);
पूर्ण

अटल पूर्णांक _cs46xx_playback_खोलो_channel (काष्ठा snd_pcm_substream *substream,पूर्णांक pcm_channel_id)
अणु
	काष्ठा snd_cs46xx *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_cs46xx_pcm * cpcm;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	cpcm = kzalloc(माप(*cpcm), GFP_KERNEL);
	अगर (cpcm == शून्य)
		वापस -ENOMEM;
	अगर (snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, &chip->pci->dev,
				PAGE_SIZE, &cpcm->hw_buf) < 0) अणु
		kमुक्त(cpcm);
		वापस -ENOMEM;
	पूर्ण

	runसमय->hw = snd_cs46xx_playback;
	runसमय->निजी_data = cpcm;
	runसमय->निजी_मुक्त = snd_cs46xx_pcm_मुक्त_substream;

	cpcm->substream = substream;
#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	mutex_lock(&chip->spos_mutex);
	cpcm->pcm_channel = शून्य; 
	cpcm->pcm_channel_id = pcm_channel_id;


	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
				   SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 
				   &hw_स्थिरraपूर्णांकs_period_sizes);

	mutex_unlock(&chip->spos_mutex);
#अन्यथा
	chip->playback_pcm = cpcm; /* HACK */
#पूर्ण_अगर

	अगर (chip->accept_valid)
		substream->runसमय->hw.info |= SNDRV_PCM_INFO_MMAP_VALID;
	chip->active_ctrl(chip, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs46xx_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	dev_dbg(substream->pcm->card->dev, "open front channel\n");
	वापस _cs46xx_playback_खोलो_channel(substream,DSP_PCM_MAIN_CHANNEL);
पूर्ण

#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
अटल पूर्णांक snd_cs46xx_playback_खोलो_rear(काष्ठा snd_pcm_substream *substream)
अणु
	dev_dbg(substream->pcm->card->dev, "open rear channel\n");
	वापस _cs46xx_playback_खोलो_channel(substream,DSP_PCM_REAR_CHANNEL);
पूर्ण

अटल पूर्णांक snd_cs46xx_playback_खोलो_clfe(काष्ठा snd_pcm_substream *substream)
अणु
	dev_dbg(substream->pcm->card->dev, "open center - LFE channel\n");
	वापस _cs46xx_playback_खोलो_channel(substream,DSP_PCM_CENTER_LFE_CHANNEL);
पूर्ण

अटल पूर्णांक snd_cs46xx_playback_खोलो_iec958(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_cs46xx *chip = snd_pcm_substream_chip(substream);

	dev_dbg(chip->card->dev, "open raw iec958 channel\n");

	mutex_lock(&chip->spos_mutex);
	cs46xx_iec958_pre_खोलो (chip);
	mutex_unlock(&chip->spos_mutex);

	वापस _cs46xx_playback_खोलो_channel(substream,DSP_IEC958_CHANNEL);
पूर्ण

अटल पूर्णांक snd_cs46xx_playback_बंद(काष्ठा snd_pcm_substream *substream);

अटल पूर्णांक snd_cs46xx_playback_बंद_iec958(काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक err;
	काष्ठा snd_cs46xx *chip = snd_pcm_substream_chip(substream);
  
	dev_dbg(chip->card->dev, "close raw iec958 channel\n");

	err = snd_cs46xx_playback_बंद(substream);

	mutex_lock(&chip->spos_mutex);
	cs46xx_iec958_post_बंद (chip);
	mutex_unlock(&chip->spos_mutex);

	वापस err;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक snd_cs46xx_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_cs46xx *chip = snd_pcm_substream_chip(substream);

	अगर (snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, &chip->pci->dev,
				PAGE_SIZE, &chip->capt.hw_buf) < 0)
		वापस -ENOMEM;
	chip->capt.substream = substream;
	substream->runसमय->hw = snd_cs46xx_capture;

	अगर (chip->accept_valid)
		substream->runसमय->hw.info |= SNDRV_PCM_INFO_MMAP_VALID;

	chip->active_ctrl(chip, 1);

#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
				   SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 
				   &hw_स्थिरraपूर्णांकs_period_sizes);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs46xx_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_cs46xx *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_cs46xx_pcm * cpcm;

	cpcm = runसमय->निजी_data;

	/* when playback_खोलो fails, then cpcm can be शून्य */
	अगर (!cpcm) वापस -ENXIO;

#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	mutex_lock(&chip->spos_mutex);
	अगर (cpcm->pcm_channel) अणु
		cs46xx_dsp_destroy_pcm_channel(chip,cpcm->pcm_channel);
		cpcm->pcm_channel = शून्य;
	पूर्ण
	mutex_unlock(&chip->spos_mutex);
#अन्यथा
	chip->playback_pcm = शून्य;
#पूर्ण_अगर

	cpcm->substream = शून्य;
	snd_dma_मुक्त_pages(&cpcm->hw_buf);
	chip->active_ctrl(chip, -1);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs46xx_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_cs46xx *chip = snd_pcm_substream_chip(substream);

	chip->capt.substream = शून्य;
	snd_dma_मुक्त_pages(&chip->capt.hw_buf);
	chip->active_ctrl(chip, -1);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
अटल स्थिर काष्ठा snd_pcm_ops snd_cs46xx_playback_rear_ops = अणु
	.खोलो =			snd_cs46xx_playback_खोलो_rear,
	.बंद =		snd_cs46xx_playback_बंद,
	.hw_params =		snd_cs46xx_playback_hw_params,
	.hw_मुक्त =		snd_cs46xx_playback_hw_मुक्त,
	.prepare =		snd_cs46xx_playback_prepare,
	.trigger =		snd_cs46xx_playback_trigger,
	.poपूर्णांकer =		snd_cs46xx_playback_direct_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_cs46xx_playback_indirect_rear_ops = अणु
	.खोलो =			snd_cs46xx_playback_खोलो_rear,
	.बंद =		snd_cs46xx_playback_बंद,
	.hw_params =		snd_cs46xx_playback_hw_params,
	.hw_मुक्त =		snd_cs46xx_playback_hw_मुक्त,
	.prepare =		snd_cs46xx_playback_prepare,
	.trigger =		snd_cs46xx_playback_trigger,
	.poपूर्णांकer =		snd_cs46xx_playback_indirect_poपूर्णांकer,
	.ack =			snd_cs46xx_playback_transfer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_cs46xx_playback_clfe_ops = अणु
	.खोलो =			snd_cs46xx_playback_खोलो_clfe,
	.बंद =		snd_cs46xx_playback_बंद,
	.hw_params =		snd_cs46xx_playback_hw_params,
	.hw_मुक्त =		snd_cs46xx_playback_hw_मुक्त,
	.prepare =		snd_cs46xx_playback_prepare,
	.trigger =		snd_cs46xx_playback_trigger,
	.poपूर्णांकer =		snd_cs46xx_playback_direct_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_cs46xx_playback_indirect_clfe_ops = अणु
	.खोलो =			snd_cs46xx_playback_खोलो_clfe,
	.बंद =		snd_cs46xx_playback_बंद,
	.hw_params =		snd_cs46xx_playback_hw_params,
	.hw_मुक्त =		snd_cs46xx_playback_hw_मुक्त,
	.prepare =		snd_cs46xx_playback_prepare,
	.trigger =		snd_cs46xx_playback_trigger,
	.poपूर्णांकer =		snd_cs46xx_playback_indirect_poपूर्णांकer,
	.ack =			snd_cs46xx_playback_transfer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_cs46xx_playback_iec958_ops = अणु
	.खोलो =			snd_cs46xx_playback_खोलो_iec958,
	.बंद =		snd_cs46xx_playback_बंद_iec958,
	.hw_params =		snd_cs46xx_playback_hw_params,
	.hw_मुक्त =		snd_cs46xx_playback_hw_मुक्त,
	.prepare =		snd_cs46xx_playback_prepare,
	.trigger =		snd_cs46xx_playback_trigger,
	.poपूर्णांकer =		snd_cs46xx_playback_direct_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_cs46xx_playback_indirect_iec958_ops = अणु
	.खोलो =			snd_cs46xx_playback_खोलो_iec958,
	.बंद =		snd_cs46xx_playback_बंद_iec958,
	.hw_params =		snd_cs46xx_playback_hw_params,
	.hw_मुक्त =		snd_cs46xx_playback_hw_मुक्त,
	.prepare =		snd_cs46xx_playback_prepare,
	.trigger =		snd_cs46xx_playback_trigger,
	.poपूर्णांकer =		snd_cs46xx_playback_indirect_poपूर्णांकer,
	.ack =			snd_cs46xx_playback_transfer,
पूर्ण;

#पूर्ण_अगर

अटल स्थिर काष्ठा snd_pcm_ops snd_cs46xx_playback_ops = अणु
	.खोलो =			snd_cs46xx_playback_खोलो,
	.बंद =		snd_cs46xx_playback_बंद,
	.hw_params =		snd_cs46xx_playback_hw_params,
	.hw_मुक्त =		snd_cs46xx_playback_hw_मुक्त,
	.prepare =		snd_cs46xx_playback_prepare,
	.trigger =		snd_cs46xx_playback_trigger,
	.poपूर्णांकer =		snd_cs46xx_playback_direct_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_cs46xx_playback_indirect_ops = अणु
	.खोलो =			snd_cs46xx_playback_खोलो,
	.बंद =		snd_cs46xx_playback_बंद,
	.hw_params =		snd_cs46xx_playback_hw_params,
	.hw_मुक्त =		snd_cs46xx_playback_hw_मुक्त,
	.prepare =		snd_cs46xx_playback_prepare,
	.trigger =		snd_cs46xx_playback_trigger,
	.poपूर्णांकer =		snd_cs46xx_playback_indirect_poपूर्णांकer,
	.ack =			snd_cs46xx_playback_transfer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_cs46xx_capture_ops = अणु
	.खोलो =			snd_cs46xx_capture_खोलो,
	.बंद =		snd_cs46xx_capture_बंद,
	.hw_params =		snd_cs46xx_capture_hw_params,
	.hw_मुक्त =		snd_cs46xx_capture_hw_मुक्त,
	.prepare =		snd_cs46xx_capture_prepare,
	.trigger =		snd_cs46xx_capture_trigger,
	.poपूर्णांकer =		snd_cs46xx_capture_direct_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_cs46xx_capture_indirect_ops = अणु
	.खोलो =			snd_cs46xx_capture_खोलो,
	.बंद =		snd_cs46xx_capture_बंद,
	.hw_params =		snd_cs46xx_capture_hw_params,
	.hw_मुक्त =		snd_cs46xx_capture_hw_मुक्त,
	.prepare =		snd_cs46xx_capture_prepare,
	.trigger =		snd_cs46xx_capture_trigger,
	.poपूर्णांकer =		snd_cs46xx_capture_indirect_poपूर्णांकer,
	.ack =			snd_cs46xx_capture_transfer,
पूर्ण;

#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
#घोषणा MAX_PLAYBACK_CHANNELS	(DSP_MAX_PCM_CHANNELS - 1)
#अन्यथा
#घोषणा MAX_PLAYBACK_CHANNELS	1
#पूर्ण_अगर

पूर्णांक snd_cs46xx_pcm(काष्ठा snd_cs46xx *chip, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	अगर ((err = snd_pcm_new(chip->card, "CS46xx", device, MAX_PLAYBACK_CHANNELS, 1, &pcm)) < 0)
		वापस err;

	pcm->निजी_data = chip;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_cs46xx_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_cs46xx_capture_ops);

	/* global setup */
	pcm->info_flags = 0;
	म_नकल(pcm->name, "CS46xx");
	chip->pcm = pcm;

	snd_pcm_lib_pपुनः_स्मृतिate_pages_क्रम_all(pcm, SNDRV_DMA_TYPE_DEV,
					      &chip->pci->dev,
					      64*1024, 256*1024);

	वापस 0;
पूर्ण


#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
पूर्णांक snd_cs46xx_pcm_rear(काष्ठा snd_cs46xx *chip, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	अगर ((err = snd_pcm_new(chip->card, "CS46xx - Rear", device, MAX_PLAYBACK_CHANNELS, 0, &pcm)) < 0)
		वापस err;

	pcm->निजी_data = chip;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_cs46xx_playback_rear_ops);

	/* global setup */
	pcm->info_flags = 0;
	म_नकल(pcm->name, "CS46xx - Rear");
	chip->pcm_rear = pcm;

	snd_pcm_lib_pपुनः_स्मृतिate_pages_क्रम_all(pcm, SNDRV_DMA_TYPE_DEV,
					      &chip->pci->dev,
					      64*1024, 256*1024);

	वापस 0;
पूर्ण

पूर्णांक snd_cs46xx_pcm_center_lfe(काष्ठा snd_cs46xx *chip, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	अगर ((err = snd_pcm_new(chip->card, "CS46xx - Center LFE", device, MAX_PLAYBACK_CHANNELS, 0, &pcm)) < 0)
		वापस err;

	pcm->निजी_data = chip;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_cs46xx_playback_clfe_ops);

	/* global setup */
	pcm->info_flags = 0;
	म_नकल(pcm->name, "CS46xx - Center LFE");
	chip->pcm_center_lfe = pcm;

	snd_pcm_lib_pपुनः_स्मृतिate_pages_क्रम_all(pcm, SNDRV_DMA_TYPE_DEV,
					      &chip->pci->dev,
					      64*1024, 256*1024);

	वापस 0;
पूर्ण

पूर्णांक snd_cs46xx_pcm_iec958(काष्ठा snd_cs46xx *chip, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	अगर ((err = snd_pcm_new(chip->card, "CS46xx - IEC958", device, 1, 0, &pcm)) < 0)
		वापस err;

	pcm->निजी_data = chip;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_cs46xx_playback_iec958_ops);

	/* global setup */
	pcm->info_flags = 0;
	म_नकल(pcm->name, "CS46xx - IEC958");
	chip->pcm_iec958 = pcm;

	snd_pcm_lib_pपुनः_स्मृतिate_pages_क्रम_all(pcm, SNDRV_DMA_TYPE_DEV,
					      &chip->pci->dev,
					      64*1024, 256*1024);

	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 *  Mixer routines
 */
अटल व्योम snd_cs46xx_mixer_मुक्त_ac97_bus(काष्ठा snd_ac97_bus *bus)
अणु
	काष्ठा snd_cs46xx *chip = bus->निजी_data;

	chip->ac97_bus = शून्य;
पूर्ण

अटल व्योम snd_cs46xx_mixer_मुक्त_ac97(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा snd_cs46xx *chip = ac97->निजी_data;

	अगर (snd_BUG_ON(ac97 != chip->ac97[CS46XX_PRIMARY_CODEC_INDEX] &&
		       ac97 != chip->ac97[CS46XX_SECONDARY_CODEC_INDEX]))
		वापस;

	अगर (ac97 == chip->ac97[CS46XX_PRIMARY_CODEC_INDEX]) अणु
		chip->ac97[CS46XX_PRIMARY_CODEC_INDEX] = शून्य;
		chip->eapd_चयन = शून्य;
	पूर्ण
	अन्यथा
		chip->ac97[CS46XX_SECONDARY_CODEC_INDEX] = शून्य;
पूर्ण

अटल पूर्णांक snd_cs46xx_vol_info(काष्ठा snd_kcontrol *kcontrol, 
			       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 0x7fff;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs46xx_vol_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_cs46xx *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक reg = kcontrol->निजी_value;
	अचिन्हित पूर्णांक val = snd_cs46xx_peek(chip, reg);
	ucontrol->value.पूर्णांकeger.value[0] = 0xffff - (val >> 16);
	ucontrol->value.पूर्णांकeger.value[1] = 0xffff - (val & 0xffff);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs46xx_vol_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_cs46xx *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक reg = kcontrol->निजी_value;
	अचिन्हित पूर्णांक val = ((0xffff - ucontrol->value.पूर्णांकeger.value[0]) << 16 | 
			    (0xffff - ucontrol->value.पूर्णांकeger.value[1]));
	अचिन्हित पूर्णांक old = snd_cs46xx_peek(chip, reg);
	पूर्णांक change = (old != val);

	अगर (change) अणु
		snd_cs46xx_poke(chip, reg, val);
	पूर्ण

	वापस change;
पूर्ण

#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP

अटल पूर्णांक snd_cs46xx_vol_dac_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_cs46xx *chip = snd_kcontrol_chip(kcontrol);

	ucontrol->value.पूर्णांकeger.value[0] = chip->dsp_spos_instance->dac_volume_left;
	ucontrol->value.पूर्णांकeger.value[1] = chip->dsp_spos_instance->dac_volume_right;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs46xx_vol_dac_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_cs46xx *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक change = 0;

	अगर (chip->dsp_spos_instance->dac_volume_right != ucontrol->value.पूर्णांकeger.value[0] ||
	    chip->dsp_spos_instance->dac_volume_left != ucontrol->value.पूर्णांकeger.value[1]) अणु
		cs46xx_dsp_set_dac_volume(chip,
					  ucontrol->value.पूर्णांकeger.value[0],
					  ucontrol->value.पूर्णांकeger.value[1]);
		change = 1;
	पूर्ण

	वापस change;
पूर्ण

#अगर 0
अटल पूर्णांक snd_cs46xx_vol_iec958_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_cs46xx *chip = snd_kcontrol_chip(kcontrol);

	ucontrol->value.पूर्णांकeger.value[0] = chip->dsp_spos_instance->spdअगर_input_volume_left;
	ucontrol->value.पूर्णांकeger.value[1] = chip->dsp_spos_instance->spdअगर_input_volume_right;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs46xx_vol_iec958_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_cs46xx *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक change = 0;

	अगर (chip->dsp_spos_instance->spdअगर_input_volume_left  != ucontrol->value.पूर्णांकeger.value[0] ||
	    chip->dsp_spos_instance->spdअगर_input_volume_right!= ucontrol->value.पूर्णांकeger.value[1]) अणु
		cs46xx_dsp_set_iec958_volume (chip,
					      ucontrol->value.पूर्णांकeger.value[0],
					      ucontrol->value.पूर्णांकeger.value[1]);
		change = 1;
	पूर्ण

	वापस change;
पूर्ण
#पूर्ण_अगर

#घोषणा snd_mixer_boolean_info		snd_ctl_boolean_mono_info

अटल पूर्णांक snd_cs46xx_iec958_get(काष्ठा snd_kcontrol *kcontrol, 
                                 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_cs46xx *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक reg = kcontrol->निजी_value;

	अगर (reg == CS46XX_MIXER_SPDIF_OUTPUT_ELEMENT)
		ucontrol->value.पूर्णांकeger.value[0] = (chip->dsp_spos_instance->spdअगर_status_out & DSP_SPDIF_STATUS_OUTPUT_ENABLED);
	अन्यथा
		ucontrol->value.पूर्णांकeger.value[0] = chip->dsp_spos_instance->spdअगर_status_in;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs46xx_iec958_put(काष्ठा snd_kcontrol *kcontrol, 
                                  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_cs46xx *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक change, res;

	चयन (kcontrol->निजी_value) अणु
	हाल CS46XX_MIXER_SPDIF_OUTPUT_ELEMENT:
		mutex_lock(&chip->spos_mutex);
		change = (chip->dsp_spos_instance->spdअगर_status_out & DSP_SPDIF_STATUS_OUTPUT_ENABLED);
		अगर (ucontrol->value.पूर्णांकeger.value[0] && !change) 
			cs46xx_dsp_enable_spdअगर_out(chip);
		अन्यथा अगर (change && !ucontrol->value.पूर्णांकeger.value[0])
			cs46xx_dsp_disable_spdअगर_out(chip);

		res = (change != (chip->dsp_spos_instance->spdअगर_status_out & DSP_SPDIF_STATUS_OUTPUT_ENABLED));
		mutex_unlock(&chip->spos_mutex);
		अवरोध;
	हाल CS46XX_MIXER_SPDIF_INPUT_ELEMENT:
		change = chip->dsp_spos_instance->spdअगर_status_in;
		अगर (ucontrol->value.पूर्णांकeger.value[0] && !change) अणु
			cs46xx_dsp_enable_spdअगर_in(chip);
			/* restore volume */
		पूर्ण
		अन्यथा अगर (change && !ucontrol->value.पूर्णांकeger.value[0])
			cs46xx_dsp_disable_spdअगर_in(chip);
		
		res = (change != chip->dsp_spos_instance->spdअगर_status_in);
		अवरोध;
	शेष:
		res = -EINVAL;
		snd_BUG(); /* should never happen ... */
	पूर्ण

	वापस res;
पूर्ण

अटल पूर्णांक snd_cs46xx_adc_capture_get(काष्ठा snd_kcontrol *kcontrol, 
                                      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_cs46xx *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;

	अगर (ins->adc_input != शून्य) 
		ucontrol->value.पूर्णांकeger.value[0] = 1;
	अन्यथा 
		ucontrol->value.पूर्णांकeger.value[0] = 0;
	
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs46xx_adc_capture_put(काष्ठा snd_kcontrol *kcontrol, 
                                      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_cs46xx *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	पूर्णांक change = 0;

	अगर (ucontrol->value.पूर्णांकeger.value[0] && !ins->adc_input) अणु
		cs46xx_dsp_enable_adc_capture(chip);
		change = 1;
	पूर्ण अन्यथा  अगर (!ucontrol->value.पूर्णांकeger.value[0] && ins->adc_input) अणु
		cs46xx_dsp_disable_adc_capture(chip);
		change = 1;
	पूर्ण
	वापस change;
पूर्ण

अटल पूर्णांक snd_cs46xx_pcm_capture_get(काष्ठा snd_kcontrol *kcontrol, 
                                      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_cs46xx *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;

	अगर (ins->pcm_input != शून्य) 
		ucontrol->value.पूर्णांकeger.value[0] = 1;
	अन्यथा 
		ucontrol->value.पूर्णांकeger.value[0] = 0;

	वापस 0;
पूर्ण


अटल पूर्णांक snd_cs46xx_pcm_capture_put(काष्ठा snd_kcontrol *kcontrol, 
                                      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_cs46xx *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	पूर्णांक change = 0;

	अगर (ucontrol->value.पूर्णांकeger.value[0] && !ins->pcm_input) अणु
		cs46xx_dsp_enable_pcm_capture(chip);
		change = 1;
	पूर्ण अन्यथा  अगर (!ucontrol->value.पूर्णांकeger.value[0] && ins->pcm_input) अणु
		cs46xx_dsp_disable_pcm_capture(chip);
		change = 1;
	पूर्ण

	वापस change;
पूर्ण

अटल पूर्णांक snd_herc_spdअगर_select_get(काष्ठा snd_kcontrol *kcontrol, 
                                     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_cs46xx *chip = snd_kcontrol_chip(kcontrol);

	पूर्णांक val1 = snd_cs46xx_peekBA0(chip, BA0_EGPIODR);

	अगर (val1 & EGPIODR_GPOE0)
		ucontrol->value.पूर्णांकeger.value[0] = 1;
	अन्यथा
		ucontrol->value.पूर्णांकeger.value[0] = 0;

	वापस 0;
पूर्ण

/*
 *	Game Theatre XP card - EGPIO[0] is used to select SPDIF input optical or coaxial.
 */ 
अटल पूर्णांक snd_herc_spdअगर_select_put(काष्ठा snd_kcontrol *kcontrol, 
                                       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_cs46xx *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक val1 = snd_cs46xx_peekBA0(chip, BA0_EGPIODR);
	पूर्णांक val2 = snd_cs46xx_peekBA0(chip, BA0_EGPIOPTR);

	अगर (ucontrol->value.पूर्णांकeger.value[0]) अणु
		/* optical is शेष */
		snd_cs46xx_pokeBA0(chip, BA0_EGPIODR, 
				   EGPIODR_GPOE0 | val1);  /* enable EGPIO0 output */
		snd_cs46xx_pokeBA0(chip, BA0_EGPIOPTR, 
				   EGPIOPTR_GPPT0 | val2); /* खोलो-drain on output */
	पूर्ण अन्यथा अणु
		/* coaxial */
		snd_cs46xx_pokeBA0(chip, BA0_EGPIODR,  val1 & ~EGPIODR_GPOE0); /* disable */
		snd_cs46xx_pokeBA0(chip, BA0_EGPIOPTR, val2 & ~EGPIOPTR_GPPT0); /* disable */
	पूर्ण

	/* checking dअगरf from the EGPIO direction रेजिस्टर 
	   should be enough */
	वापस (val1 != (पूर्णांक)snd_cs46xx_peekBA0(chip, BA0_EGPIODR));
पूर्ण


अटल पूर्णांक snd_cs46xx_spdअगर_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs46xx_spdअगर_शेष_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_cs46xx *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;

	mutex_lock(&chip->spos_mutex);
	ucontrol->value.iec958.status[0] = _wrap_all_bits((ins->spdअगर_csuv_शेष >> 24) & 0xff);
	ucontrol->value.iec958.status[1] = _wrap_all_bits((ins->spdअगर_csuv_शेष >> 16) & 0xff);
	ucontrol->value.iec958.status[2] = 0;
	ucontrol->value.iec958.status[3] = _wrap_all_bits((ins->spdअगर_csuv_शेष) & 0xff);
	mutex_unlock(&chip->spos_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs46xx_spdअगर_शेष_put(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_cs46xx * chip = snd_kcontrol_chip(kcontrol);
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	अचिन्हित पूर्णांक val;
	पूर्णांक change;

	mutex_lock(&chip->spos_mutex);
	val = ((अचिन्हित पूर्णांक)_wrap_all_bits(ucontrol->value.iec958.status[0]) << 24) |
		((अचिन्हित पूर्णांक)_wrap_all_bits(ucontrol->value.iec958.status[2]) << 16) |
		((अचिन्हित पूर्णांक)_wrap_all_bits(ucontrol->value.iec958.status[3]))  |
		/* left and right validity bit */
		(1 << 13) | (1 << 12);


	change = (अचिन्हित पूर्णांक)ins->spdअगर_csuv_शेष != val;
	ins->spdअगर_csuv_शेष = val;

	अगर ( !(ins->spdअगर_status_out & DSP_SPDIF_STATUS_PLAYBACK_OPEN) )
		cs46xx_poke_via_dsp (chip,SP_SPDOUT_CSUV,val);

	mutex_unlock(&chip->spos_mutex);

	वापस change;
पूर्ण

अटल पूर्णांक snd_cs46xx_spdअगर_mask_get(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.iec958.status[0] = 0xff;
	ucontrol->value.iec958.status[1] = 0xff;
	ucontrol->value.iec958.status[2] = 0x00;
	ucontrol->value.iec958.status[3] = 0xff;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs46xx_spdअगर_stream_get(काष्ठा snd_kcontrol *kcontrol,
                                         काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_cs46xx *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;

	mutex_lock(&chip->spos_mutex);
	ucontrol->value.iec958.status[0] = _wrap_all_bits((ins->spdअगर_csuv_stream >> 24) & 0xff);
	ucontrol->value.iec958.status[1] = _wrap_all_bits((ins->spdअगर_csuv_stream >> 16) & 0xff);
	ucontrol->value.iec958.status[2] = 0;
	ucontrol->value.iec958.status[3] = _wrap_all_bits((ins->spdअगर_csuv_stream) & 0xff);
	mutex_unlock(&chip->spos_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs46xx_spdअगर_stream_put(काष्ठा snd_kcontrol *kcontrol,
                                        काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_cs46xx * chip = snd_kcontrol_chip(kcontrol);
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	अचिन्हित पूर्णांक val;
	पूर्णांक change;

	mutex_lock(&chip->spos_mutex);
	val = ((अचिन्हित पूर्णांक)_wrap_all_bits(ucontrol->value.iec958.status[0]) << 24) |
		((अचिन्हित पूर्णांक)_wrap_all_bits(ucontrol->value.iec958.status[1]) << 16) |
		((अचिन्हित पूर्णांक)_wrap_all_bits(ucontrol->value.iec958.status[3])) |
		/* left and right validity bit */
		(1 << 13) | (1 << 12);


	change = ins->spdअगर_csuv_stream != val;
	ins->spdअगर_csuv_stream = val;

	अगर ( ins->spdअगर_status_out & DSP_SPDIF_STATUS_PLAYBACK_OPEN )
		cs46xx_poke_via_dsp (chip,SP_SPDOUT_CSUV,val);

	mutex_unlock(&chip->spos_mutex);

	वापस change;
पूर्ण

#पूर्ण_अगर /* CONFIG_SND_CS46XX_NEW_DSP */


अटल स्थिर काष्ठा snd_kcontrol_new snd_cs46xx_controls[] = अणु
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "DAC Volume",
	.info = snd_cs46xx_vol_info,
#अगर_अघोषित CONFIG_SND_CS46XX_NEW_DSP
	.get = snd_cs46xx_vol_get,
	.put = snd_cs46xx_vol_put,
	.निजी_value = BA1_PVOL,
#अन्यथा
	.get = snd_cs46xx_vol_dac_get,
	.put = snd_cs46xx_vol_dac_put,
#पूर्ण_अगर
पूर्ण,

अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "ADC Volume",
	.info = snd_cs46xx_vol_info,
	.get = snd_cs46xx_vol_get,
	.put = snd_cs46xx_vol_put,
#अगर_अघोषित CONFIG_SND_CS46XX_NEW_DSP
	.निजी_value = BA1_CVOL,
#अन्यथा
	.निजी_value = (VARIDECIMATE_SCB_ADDR + 0xE) << 2,
#पूर्ण_अगर
पूर्ण,
#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "ADC Capture Switch",
	.info = snd_mixer_boolean_info,
	.get = snd_cs46xx_adc_capture_get,
	.put = snd_cs46xx_adc_capture_put
पूर्ण,
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "DAC Capture Switch",
	.info = snd_mixer_boolean_info,
	.get = snd_cs46xx_pcm_capture_get,
	.put = snd_cs46xx_pcm_capture_put
पूर्ण,
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = SNDRV_CTL_NAME_IEC958("Output ",NONE,SWITCH),
	.info = snd_mixer_boolean_info,
	.get = snd_cs46xx_iec958_get,
	.put = snd_cs46xx_iec958_put,
	.निजी_value = CS46XX_MIXER_SPDIF_OUTPUT_ELEMENT,
पूर्ण,
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = SNDRV_CTL_NAME_IEC958("Input ",NONE,SWITCH),
	.info = snd_mixer_boolean_info,
	.get = snd_cs46xx_iec958_get,
	.put = snd_cs46xx_iec958_put,
	.निजी_value = CS46XX_MIXER_SPDIF_INPUT_ELEMENT,
पूर्ण,
#अगर 0
/* Input IEC958 volume करोes not work क्रम the moment. (Benny) */
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = SNDRV_CTL_NAME_IEC958("Input ",NONE,VOLUME),
	.info = snd_cs46xx_vol_info,
	.get = snd_cs46xx_vol_iec958_get,
	.put = snd_cs46xx_vol_iec958_put,
	.निजी_value = (ASYNCRX_SCB_ADDR + 0xE) << 2,
पूर्ण,
#पूर्ण_अगर
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
	.name =  SNDRV_CTL_NAME_IEC958("",PLAYBACK,DEFAULT),
	.info =	 snd_cs46xx_spdअगर_info,
	.get =	 snd_cs46xx_spdअगर_शेष_get,
	.put =   snd_cs46xx_spdअगर_शेष_put,
पूर्ण,
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
	.name =	 SNDRV_CTL_NAME_IEC958("",PLAYBACK,MASK),
	.info =	 snd_cs46xx_spdअगर_info,
        .get =	 snd_cs46xx_spdअगर_mask_get,
	.access = SNDRV_CTL_ELEM_ACCESS_READ
पूर्ण,
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
	.name =	 SNDRV_CTL_NAME_IEC958("",PLAYBACK,PCM_STREAM),
	.info =	 snd_cs46xx_spdअगर_info,
	.get =	 snd_cs46xx_spdअगर_stream_get,
	.put =	 snd_cs46xx_spdअगर_stream_put
पूर्ण,

#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
/* set primary cs4294 codec पूर्णांकo Extended Audio Mode */
अटल पूर्णांक snd_cs46xx_front_dup_get(काष्ठा snd_kcontrol *kcontrol, 
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_cs46xx *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु val;
	val = snd_ac97_पढ़ो(chip->ac97[CS46XX_PRIMARY_CODEC_INDEX], AC97_CSR_ACMODE);
	ucontrol->value.पूर्णांकeger.value[0] = (val & 0x200) ? 0 : 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs46xx_front_dup_put(काष्ठा snd_kcontrol *kcontrol, 
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_cs46xx *chip = snd_kcontrol_chip(kcontrol);
	वापस snd_ac97_update_bits(chip->ac97[CS46XX_PRIMARY_CODEC_INDEX],
				    AC97_CSR_ACMODE, 0x200,
				    ucontrol->value.पूर्णांकeger.value[0] ? 0 : 0x200);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_cs46xx_front_dup_ctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Duplicate Front",
	.info = snd_mixer_boolean_info,
	.get = snd_cs46xx_front_dup_get,
	.put = snd_cs46xx_front_dup_put,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
/* Only available on the Hercules Game Theater XP soundcard */
अटल स्थिर काष्ठा snd_kcontrol_new snd_hercules_controls[] = अणु
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Optical/Coaxial SPDIF Input Switch",
	.info = snd_mixer_boolean_info,
	.get = snd_herc_spdअगर_select_get,
	.put = snd_herc_spdअगर_select_put,
पूर्ण,
पूर्ण;


अटल व्योम snd_cs46xx_codec_reset (काष्ठा snd_ac97 * ac97)
अणु
	अचिन्हित दीर्घ end_समय;
	पूर्णांक err;

	/* reset to शेषs */
	snd_ac97_ग_लिखो(ac97, AC97_RESET, 0);	

	/* set the desired CODEC mode */
	अगर (ac97->num == CS46XX_PRIMARY_CODEC_INDEX) अणु
		dev_dbg(ac97->bus->card->dev, "CODEC1 mode %04x\n", 0x0);
		snd_cs46xx_ac97_ग_लिखो(ac97, AC97_CSR_ACMODE, 0x0);
	पूर्ण अन्यथा अगर (ac97->num == CS46XX_SECONDARY_CODEC_INDEX) अणु
		dev_dbg(ac97->bus->card->dev, "CODEC2 mode %04x\n", 0x3);
		snd_cs46xx_ac97_ग_लिखो(ac97, AC97_CSR_ACMODE, 0x3);
	पूर्ण अन्यथा अणु
		snd_BUG(); /* should never happen ... */
	पूर्ण

	udelay(50);

	/* it's necessary to रुको aजबतक until रेजिस्टरs are accessible after RESET */
	/* because the PCM or MASTER volume रेजिस्टरs can be modअगरied, */
	/* the REC_GAIN रेजिस्टर is used क्रम tests */
	end_समय = jअगरfies + HZ;
	करो अणु
		अचिन्हित लघु ext_mid;
    
		/* use preliminary पढ़ोs to settle the communication */
		snd_ac97_पढ़ो(ac97, AC97_RESET);
		snd_ac97_पढ़ो(ac97, AC97_VENDOR_ID1);
		snd_ac97_पढ़ो(ac97, AC97_VENDOR_ID2);
		/* modem? */
		ext_mid = snd_ac97_पढ़ो(ac97, AC97_EXTENDED_MID);
		अगर (ext_mid != 0xffff && (ext_mid & 1) != 0)
			वापस;

		/* test अगर we can ग_लिखो to the record gain volume रेजिस्टर */
		snd_ac97_ग_लिखो(ac97, AC97_REC_GAIN, 0x8a05);
		अगर ((err = snd_ac97_पढ़ो(ac97, AC97_REC_GAIN)) == 0x8a05)
			वापस;

		msleep(10);
	पूर्ण जबतक (समय_after_eq(end_समय, jअगरfies));

	dev_err(ac97->bus->card->dev,
		"CS46xx secondary codec doesn't respond!\n");
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक cs46xx_detect_codec(काष्ठा snd_cs46xx *chip, पूर्णांक codec)
अणु
	पूर्णांक idx, err;
	काष्ठा snd_ac97_ढाँचा ac97;

	स_रखो(&ac97, 0, माप(ac97));
	ac97.निजी_data = chip;
	ac97.निजी_मुक्त = snd_cs46xx_mixer_मुक्त_ac97;
	ac97.num = codec;
	अगर (chip->amplअगरier_ctrl == amp_voyetra)
		ac97.scaps = AC97_SCAP_INV_EAPD;

	अगर (codec == CS46XX_SECONDARY_CODEC_INDEX) अणु
		snd_cs46xx_codec_ग_लिखो(chip, AC97_RESET, 0, codec);
		udelay(10);
		अगर (snd_cs46xx_codec_पढ़ो(chip, AC97_RESET, codec) & 0x8000) अणु
			dev_dbg(chip->card->dev,
				"secondary codec not present\n");
			वापस -ENXIO;
		पूर्ण
	पूर्ण

	snd_cs46xx_codec_ग_लिखो(chip, AC97_MASTER, 0x8000, codec);
	क्रम (idx = 0; idx < 100; ++idx) अणु
		अगर (snd_cs46xx_codec_पढ़ो(chip, AC97_MASTER, codec) == 0x8000) अणु
			err = snd_ac97_mixer(chip->ac97_bus, &ac97, &chip->ac97[codec]);
			वापस err;
		पूर्ण
		msleep(10);
	पूर्ण
	dev_dbg(chip->card->dev, "codec %d detection timeout\n", codec);
	वापस -ENXIO;
पूर्ण

पूर्णांक snd_cs46xx_mixer(काष्ठा snd_cs46xx *chip, पूर्णांक spdअगर_device)
अणु
	काष्ठा snd_card *card = chip->card;
	काष्ठा snd_ctl_elem_id id;
	पूर्णांक err;
	अचिन्हित पूर्णांक idx;
	अटल स्थिर काष्ठा snd_ac97_bus_ops ops = अणु
#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
		.reset = snd_cs46xx_codec_reset,
#पूर्ण_अगर
		.ग_लिखो = snd_cs46xx_ac97_ग_लिखो,
		.पढ़ो = snd_cs46xx_ac97_पढ़ो,
	पूर्ण;

	/* detect primary codec */
	chip->nr_ac97_codecs = 0;
	dev_dbg(chip->card->dev, "detecting primary codec\n");
	अगर ((err = snd_ac97_bus(card, 0, &ops, chip, &chip->ac97_bus)) < 0)
		वापस err;
	chip->ac97_bus->निजी_मुक्त = snd_cs46xx_mixer_मुक्त_ac97_bus;

	अगर (cs46xx_detect_codec(chip, CS46XX_PRIMARY_CODEC_INDEX) < 0)
		वापस -ENXIO;
	chip->nr_ac97_codecs = 1;

#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	dev_dbg(chip->card->dev, "detecting secondary codec\n");
	/* try detect a secondary codec */
	अगर (! cs46xx_detect_codec(chip, CS46XX_SECONDARY_CODEC_INDEX))
		chip->nr_ac97_codecs = 2;
#पूर्ण_अगर /* CONFIG_SND_CS46XX_NEW_DSP */

	/* add cs4630 mixer controls */
	क्रम (idx = 0; idx < ARRAY_SIZE(snd_cs46xx_controls); idx++) अणु
		काष्ठा snd_kcontrol *kctl;
		kctl = snd_ctl_new1(&snd_cs46xx_controls[idx], chip);
		अगर (kctl && kctl->id.अगरace == SNDRV_CTL_ELEM_IFACE_PCM)
			kctl->id.device = spdअगर_device;
		अगर ((err = snd_ctl_add(card, kctl)) < 0)
			वापस err;
	पूर्ण

	/* get EAPD mixer चयन (क्रम voyetra hack) */
	स_रखो(&id, 0, माप(id));
	id.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	म_नकल(id.name, "External Amplifier");
	chip->eapd_चयन = snd_ctl_find_id(chip->card, &id);
    
#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	अगर (chip->nr_ac97_codecs == 1) अणु
		अचिन्हित पूर्णांक id2 = chip->ac97[CS46XX_PRIMARY_CODEC_INDEX]->id & 0xffff;
		अगर ((id2 & 0xfff0) == 0x5920) अणु	/* CS4294 and CS4298 */
			err = snd_ctl_add(card, snd_ctl_new1(&snd_cs46xx_front_dup_ctl, chip));
			अगर (err < 0)
				वापस err;
			snd_ac97_ग_लिखो_cache(chip->ac97[CS46XX_PRIMARY_CODEC_INDEX],
					     AC97_CSR_ACMODE, 0x200);
		पूर्ण
	पूर्ण
	/* करो soundcard specअगरic mixer setup */
	अगर (chip->mixer_init) अणु
		dev_dbg(chip->card->dev, "calling chip->mixer_init(chip);\n");
		chip->mixer_init(chip);
	पूर्ण
#पूर्ण_अगर

 	/* turn on amplअगरier */
	chip->amplअगरier_ctrl(chip, 1);
    
	वापस 0;
पूर्ण

/*
 *  RawMIDI पूर्णांकerface
 */

अटल व्योम snd_cs46xx_midi_reset(काष्ठा snd_cs46xx *chip)
अणु
	snd_cs46xx_pokeBA0(chip, BA0_MIDCR, MIDCR_MRST);
	udelay(100);
	snd_cs46xx_pokeBA0(chip, BA0_MIDCR, chip->midcr);
पूर्ण

अटल पूर्णांक snd_cs46xx_midi_input_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_cs46xx *chip = substream->rmidi->निजी_data;

	chip->active_ctrl(chip, 1);
	spin_lock_irq(&chip->reg_lock);
	chip->uarपंचांग |= CS46XX_MODE_INPUT;
	chip->midcr |= MIDCR_RXE;
	chip->midi_input = substream;
	अगर (!(chip->uarपंचांग & CS46XX_MODE_OUTPUT)) अणु
		snd_cs46xx_midi_reset(chip);
	पूर्ण अन्यथा अणु
		snd_cs46xx_pokeBA0(chip, BA0_MIDCR, chip->midcr);
	पूर्ण
	spin_unlock_irq(&chip->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs46xx_midi_input_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_cs46xx *chip = substream->rmidi->निजी_data;

	spin_lock_irq(&chip->reg_lock);
	chip->midcr &= ~(MIDCR_RXE | MIDCR_RIE);
	chip->midi_input = शून्य;
	अगर (!(chip->uarपंचांग & CS46XX_MODE_OUTPUT)) अणु
		snd_cs46xx_midi_reset(chip);
	पूर्ण अन्यथा अणु
		snd_cs46xx_pokeBA0(chip, BA0_MIDCR, chip->midcr);
	पूर्ण
	chip->uarपंचांग &= ~CS46XX_MODE_INPUT;
	spin_unlock_irq(&chip->reg_lock);
	chip->active_ctrl(chip, -1);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs46xx_midi_output_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_cs46xx *chip = substream->rmidi->निजी_data;

	chip->active_ctrl(chip, 1);

	spin_lock_irq(&chip->reg_lock);
	chip->uarपंचांग |= CS46XX_MODE_OUTPUT;
	chip->midcr |= MIDCR_TXE;
	chip->midi_output = substream;
	अगर (!(chip->uarपंचांग & CS46XX_MODE_INPUT)) अणु
		snd_cs46xx_midi_reset(chip);
	पूर्ण अन्यथा अणु
		snd_cs46xx_pokeBA0(chip, BA0_MIDCR, chip->midcr);
	पूर्ण
	spin_unlock_irq(&chip->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs46xx_midi_output_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_cs46xx *chip = substream->rmidi->निजी_data;

	spin_lock_irq(&chip->reg_lock);
	chip->midcr &= ~(MIDCR_TXE | MIDCR_TIE);
	chip->midi_output = शून्य;
	अगर (!(chip->uarपंचांग & CS46XX_MODE_INPUT)) अणु
		snd_cs46xx_midi_reset(chip);
	पूर्ण अन्यथा अणु
		snd_cs46xx_pokeBA0(chip, BA0_MIDCR, chip->midcr);
	पूर्ण
	chip->uarपंचांग &= ~CS46XX_MODE_OUTPUT;
	spin_unlock_irq(&chip->reg_lock);
	chip->active_ctrl(chip, -1);
	वापस 0;
पूर्ण

अटल व्योम snd_cs46xx_midi_input_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_cs46xx *chip = substream->rmidi->निजी_data;

	spin_lock_irqsave(&chip->reg_lock, flags);
	अगर (up) अणु
		अगर ((chip->midcr & MIDCR_RIE) == 0) अणु
			chip->midcr |= MIDCR_RIE;
			snd_cs46xx_pokeBA0(chip, BA0_MIDCR, chip->midcr);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (chip->midcr & MIDCR_RIE) अणु
			chip->midcr &= ~MIDCR_RIE;
			snd_cs46xx_pokeBA0(chip, BA0_MIDCR, chip->midcr);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&chip->reg_lock, flags);
पूर्ण

अटल व्योम snd_cs46xx_midi_output_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_cs46xx *chip = substream->rmidi->निजी_data;
	अचिन्हित अक्षर byte;

	spin_lock_irqsave(&chip->reg_lock, flags);
	अगर (up) अणु
		अगर ((chip->midcr & MIDCR_TIE) == 0) अणु
			chip->midcr |= MIDCR_TIE;
			/* fill UART FIFO buffer at first, and turn Tx पूर्णांकerrupts only अगर necessary */
			जबतक ((chip->midcr & MIDCR_TIE) &&
			       (snd_cs46xx_peekBA0(chip, BA0_MIDSR) & MIDSR_TBF) == 0) अणु
				अगर (snd_rawmidi_transmit(substream, &byte, 1) != 1) अणु
					chip->midcr &= ~MIDCR_TIE;
				पूर्ण अन्यथा अणु
					snd_cs46xx_pokeBA0(chip, BA0_MIDWP, byte);
				पूर्ण
			पूर्ण
			snd_cs46xx_pokeBA0(chip, BA0_MIDCR, chip->midcr);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (chip->midcr & MIDCR_TIE) अणु
			chip->midcr &= ~MIDCR_TIE;
			snd_cs46xx_pokeBA0(chip, BA0_MIDCR, chip->midcr);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&chip->reg_lock, flags);
पूर्ण

अटल स्थिर काष्ठा snd_rawmidi_ops snd_cs46xx_midi_output =
अणु
	.खोलो =		snd_cs46xx_midi_output_खोलो,
	.बंद =	snd_cs46xx_midi_output_बंद,
	.trigger =	snd_cs46xx_midi_output_trigger,
पूर्ण;

अटल स्थिर काष्ठा snd_rawmidi_ops snd_cs46xx_midi_input =
अणु
	.खोलो =		snd_cs46xx_midi_input_खोलो,
	.बंद =	snd_cs46xx_midi_input_बंद,
	.trigger =	snd_cs46xx_midi_input_trigger,
पूर्ण;

पूर्णांक snd_cs46xx_midi(काष्ठा snd_cs46xx *chip, पूर्णांक device)
अणु
	काष्ठा snd_rawmidi *rmidi;
	पूर्णांक err;

	अगर ((err = snd_rawmidi_new(chip->card, "CS46XX", device, 1, 1, &rmidi)) < 0)
		वापस err;
	म_नकल(rmidi->name, "CS46XX");
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT, &snd_cs46xx_midi_output);
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT, &snd_cs46xx_midi_input);
	rmidi->info_flags |= SNDRV_RAWMIDI_INFO_OUTPUT | SNDRV_RAWMIDI_INFO_INPUT | SNDRV_RAWMIDI_INFO_DUPLEX;
	rmidi->निजी_data = chip;
	chip->rmidi = rmidi;
	वापस 0;
पूर्ण


/*
 * gameport पूर्णांकerface
 */

#अगर IS_REACHABLE(CONFIG_GAMEPORT)

अटल व्योम snd_cs46xx_gameport_trigger(काष्ठा gameport *gameport)
अणु
	काष्ठा snd_cs46xx *chip = gameport_get_port_data(gameport);

	अगर (snd_BUG_ON(!chip))
		वापस;
	snd_cs46xx_pokeBA0(chip, BA0_JSPT, 0xFF);  //outb(gameport->io, 0xFF);
पूर्ण

अटल अचिन्हित अक्षर snd_cs46xx_gameport_पढ़ो(काष्ठा gameport *gameport)
अणु
	काष्ठा snd_cs46xx *chip = gameport_get_port_data(gameport);

	अगर (snd_BUG_ON(!chip))
		वापस 0;
	वापस snd_cs46xx_peekBA0(chip, BA0_JSPT); //inb(gameport->io);
पूर्ण

अटल पूर्णांक snd_cs46xx_gameport_cooked_पढ़ो(काष्ठा gameport *gameport, पूर्णांक *axes, पूर्णांक *buttons)
अणु
	काष्ठा snd_cs46xx *chip = gameport_get_port_data(gameport);
	अचिन्हित js1, js2, jst;

	अगर (snd_BUG_ON(!chip))
		वापस 0;

	js1 = snd_cs46xx_peekBA0(chip, BA0_JSC1);
	js2 = snd_cs46xx_peekBA0(chip, BA0_JSC2);
	jst = snd_cs46xx_peekBA0(chip, BA0_JSPT);
	
	*buttons = (~jst >> 4) & 0x0F; 
	
	axes[0] = ((js1 & JSC1_Y1V_MASK) >> JSC1_Y1V_SHIFT) & 0xFFFF;
	axes[1] = ((js1 & JSC1_X1V_MASK) >> JSC1_X1V_SHIFT) & 0xFFFF;
	axes[2] = ((js2 & JSC2_Y2V_MASK) >> JSC2_Y2V_SHIFT) & 0xFFFF;
	axes[3] = ((js2 & JSC2_X2V_MASK) >> JSC2_X2V_SHIFT) & 0xFFFF;

	क्रम(jst=0;jst<4;++jst)
		अगर(axes[jst]==0xFFFF) axes[jst] = -1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs46xx_gameport_खोलो(काष्ठा gameport *gameport, पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल GAMEPORT_MODE_COOKED:
		वापस 0;
	हाल GAMEPORT_MODE_RAW:
		वापस 0;
	शेष:
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक snd_cs46xx_gameport(काष्ठा snd_cs46xx *chip)
अणु
	काष्ठा gameport *gp;

	chip->gameport = gp = gameport_allocate_port();
	अगर (!gp) अणु
		dev_err(chip->card->dev,
			"cannot allocate memory for gameport\n");
		वापस -ENOMEM;
	पूर्ण

	gameport_set_name(gp, "CS46xx Gameport");
	gameport_set_phys(gp, "pci%s/gameport0", pci_name(chip->pci));
	gameport_set_dev_parent(gp, &chip->pci->dev);
	gameport_set_port_data(gp, chip);

	gp->खोलो = snd_cs46xx_gameport_खोलो;
	gp->पढ़ो = snd_cs46xx_gameport_पढ़ो;
	gp->trigger = snd_cs46xx_gameport_trigger;
	gp->cooked_पढ़ो = snd_cs46xx_gameport_cooked_पढ़ो;

	snd_cs46xx_pokeBA0(chip, BA0_JSIO, 0xFF); // ?
	snd_cs46xx_pokeBA0(chip, BA0_JSCTL, JSCTL_SP_MEDIUM_SLOW);

	gameport_रेजिस्टर_port(gp);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम snd_cs46xx_हटाओ_gameport(काष्ठा snd_cs46xx *chip)
अणु
	अगर (chip->gameport) अणु
		gameport_unरेजिस्टर_port(chip->gameport);
		chip->gameport = शून्य;
	पूर्ण
पूर्ण
#अन्यथा
पूर्णांक snd_cs46xx_gameport(काष्ठा snd_cs46xx *chip) अणु वापस -ENOSYS; पूर्ण
अटल अंतरभूत व्योम snd_cs46xx_हटाओ_gameport(काष्ठा snd_cs46xx *chip) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_GAMEPORT */

#अगर_घोषित CONFIG_SND_PROC_FS
/*
 *  proc पूर्णांकerface
 */

अटल sमाप_प्रकार snd_cs46xx_io_पढ़ो(काष्ठा snd_info_entry *entry,
				  व्योम *file_निजी_data,
				  काष्ठा file *file, अक्षर __user *buf,
				  माप_प्रकार count, loff_t pos)
अणु
	काष्ठा snd_cs46xx_region *region = entry->निजी_data;
	
	अगर (copy_to_user_fromio(buf, region->remap_addr + pos, count))
		वापस -EFAULT;
	वापस count;
पूर्ण

अटल स्थिर काष्ठा snd_info_entry_ops snd_cs46xx_proc_io_ops = अणु
	.पढ़ो = snd_cs46xx_io_पढ़ो,
पूर्ण;

अटल पूर्णांक snd_cs46xx_proc_init(काष्ठा snd_card *card, काष्ठा snd_cs46xx *chip)
अणु
	काष्ठा snd_info_entry *entry;
	पूर्णांक idx;
	
	क्रम (idx = 0; idx < 5; idx++) अणु
		काष्ठा snd_cs46xx_region *region = &chip->region.idx[idx];
		अगर (! snd_card_proc_new(card, region->name, &entry)) अणु
			entry->content = SNDRV_INFO_CONTENT_DATA;
			entry->निजी_data = chip;
			entry->c.ops = &snd_cs46xx_proc_io_ops;
			entry->size = region->size;
			entry->mode = S_IFREG | 0400;
		पूर्ण
	पूर्ण
#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	cs46xx_dsp_proc_init(card, chip);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs46xx_proc_करोne(काष्ठा snd_cs46xx *chip)
अणु
#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	cs46xx_dsp_proc_करोne(chip);
#पूर्ण_अगर
	वापस 0;
पूर्ण
#अन्यथा /* !CONFIG_SND_PROC_FS */
#घोषणा snd_cs46xx_proc_init(card, chip)
#घोषणा snd_cs46xx_proc_करोne(chip)
#पूर्ण_अगर

/*
 * stop the h/w
 */
अटल व्योम snd_cs46xx_hw_stop(काष्ठा snd_cs46xx *chip)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	पंचांगp = snd_cs46xx_peek(chip, BA1_PFIE);
	पंचांगp &= ~0x0000f03f;
	पंचांगp |=  0x00000010;
	snd_cs46xx_poke(chip, BA1_PFIE, पंचांगp);	/* playback पूर्णांकerrupt disable */

	पंचांगp = snd_cs46xx_peek(chip, BA1_CIE);
	पंचांगp &= ~0x0000003f;
	पंचांगp |=  0x00000011;
	snd_cs46xx_poke(chip, BA1_CIE, पंचांगp);	/* capture पूर्णांकerrupt disable */

	/*
         *  Stop playback DMA.
	 */
	पंचांगp = snd_cs46xx_peek(chip, BA1_PCTL);
	snd_cs46xx_poke(chip, BA1_PCTL, पंचांगp & 0x0000ffff);

	/*
         *  Stop capture DMA.
	 */
	पंचांगp = snd_cs46xx_peek(chip, BA1_CCTL);
	snd_cs46xx_poke(chip, BA1_CCTL, पंचांगp & 0xffff0000);

	/*
         *  Reset the processor.
         */
	snd_cs46xx_reset(chip);

	snd_cs46xx_proc_stop(chip);

	/*
	 *  Power करोwn the PLL.
	 */
	snd_cs46xx_pokeBA0(chip, BA0_CLKCR1, 0);

	/*
	 *  Turn off the Processor by turning off the software घड़ी enable flag in 
	 *  the घड़ी control रेजिस्टर.
	 */
	पंचांगp = snd_cs46xx_peekBA0(chip, BA0_CLKCR1) & ~CLKCR1_SWCE;
	snd_cs46xx_pokeBA0(chip, BA0_CLKCR1, पंचांगp);
पूर्ण


अटल पूर्णांक snd_cs46xx_मुक्त(काष्ठा snd_cs46xx *chip)
अणु
	पूर्णांक idx;

	अगर (snd_BUG_ON(!chip))
		वापस -EINVAL;

	अगर (chip->active_ctrl)
		chip->active_ctrl(chip, 1);

	snd_cs46xx_हटाओ_gameport(chip);

	अगर (chip->amplअगरier_ctrl)
		chip->amplअगरier_ctrl(chip, -chip->amplअगरier); /* क्रमce to off */
	
	snd_cs46xx_proc_करोne(chip);

	अगर (chip->region.idx[0].resource)
		snd_cs46xx_hw_stop(chip);

	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, chip);

	अगर (chip->active_ctrl)
		chip->active_ctrl(chip, -chip->amplअगरier);

	क्रम (idx = 0; idx < 5; idx++) अणु
		काष्ठा snd_cs46xx_region *region = &chip->region.idx[idx];

		iounmap(region->remap_addr);
		release_and_मुक्त_resource(region->resource);
	पूर्ण

#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	अगर (chip->dsp_spos_instance) अणु
		cs46xx_dsp_spos_destroy(chip);
		chip->dsp_spos_instance = शून्य;
	पूर्ण
	क्रम (idx = 0; idx < CS46XX_DSP_MODULES; idx++)
		मुक्त_module_desc(chip->modules[idx]);
#अन्यथा
	vमुक्त(chip->ba1);
#पूर्ण_अगर
	
#अगर_घोषित CONFIG_PM_SLEEP
	kमुक्त(chip->saved_regs);
#पूर्ण_अगर

	pci_disable_device(chip->pci);
	kमुक्त(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs46xx_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_cs46xx *chip = device->device_data;
	वापस snd_cs46xx_मुक्त(chip);
पूर्ण

/*
 *  initialize chip
 */
अटल पूर्णांक snd_cs46xx_chip_init(काष्ठा snd_cs46xx *chip)
अणु
	पूर्णांक समयout;

	/* 
	 *  First, blast the घड़ी control रेजिस्टर to zero so that the PLL starts
         *  out in a known state, and blast the master serial port control रेजिस्टर
         *  to zero so that the serial ports also start out in a known state.
         */
        snd_cs46xx_pokeBA0(chip, BA0_CLKCR1, 0);
        snd_cs46xx_pokeBA0(chip, BA0_SERMC1, 0);

	/*
	 *  If we are in AC97 mode, then we must set the part to a host controlled
         *  AC-link.  Otherwise, we won't be able to bring up the link.
         */        
#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	snd_cs46xx_pokeBA0(chip, BA0_SERACC, SERACC_HSP | SERACC_CHIP_TYPE_2_0 | 
			   SERACC_TWO_CODECS);	/* 2.00 dual codecs */
	/* snd_cs46xx_pokeBA0(chip, BA0_SERACC, SERACC_HSP | SERACC_CHIP_TYPE_2_0); */ /* 2.00 codec */
#अन्यथा
	snd_cs46xx_pokeBA0(chip, BA0_SERACC, SERACC_HSP | SERACC_CHIP_TYPE_1_03); /* 1.03 codec */
#पूर्ण_अगर

        /*
         *  Drive the ARST# pin low क्रम a minimum of 1uS (as defined in the AC97
         *  spec) and then drive it high.  This is करोne क्रम non AC97 modes since
         *  there might be logic बाह्यal to the CS461x that uses the ARST# line
         *  क्रम a reset.
         */
	snd_cs46xx_pokeBA0(chip, BA0_ACCTL, 0);
#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	snd_cs46xx_pokeBA0(chip, BA0_ACCTL2, 0);
#पूर्ण_अगर
	udelay(50);
	snd_cs46xx_pokeBA0(chip, BA0_ACCTL, ACCTL_RSTN);
#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	snd_cs46xx_pokeBA0(chip, BA0_ACCTL2, ACCTL_RSTN);
#पूर्ण_अगर
    
	/*
	 *  The first thing we करो here is to enable sync generation.  As soon
	 *  as we start receiving bit घड़ी, we'll start producing the SYNC
	 *  संकेत.
	 */
	snd_cs46xx_pokeBA0(chip, BA0_ACCTL, ACCTL_ESYN | ACCTL_RSTN);
#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	snd_cs46xx_pokeBA0(chip, BA0_ACCTL2, ACCTL_ESYN | ACCTL_RSTN);
#पूर्ण_अगर

	/*
	 *  Now रुको क्रम a लघु जबतक to allow the AC97 part to start
	 *  generating bit घड़ी (so we करोn't try to start the PLL without an
	 *  input घड़ी).
	 */
	mdelay(10);

	/*
	 *  Set the serial port timing configuration, so that
	 *  the घड़ी control circuit माला_लो its घड़ी from the correct place.
	 */
	snd_cs46xx_pokeBA0(chip, BA0_SERMC1, SERMC1_PTC_AC97);

	/*
	 *  Write the selected घड़ी control setup to the hardware.  Do not turn on
	 *  SWCE yet (अगर requested), so that the devices घड़ीed by the output of
	 *  PLL are not घड़ीed until the PLL is stable.
	 */
	snd_cs46xx_pokeBA0(chip, BA0_PLLCC, PLLCC_LPF_1050_2780_KHZ | PLLCC_CDR_73_104_MHZ);
	snd_cs46xx_pokeBA0(chip, BA0_PLLM, 0x3a);
	snd_cs46xx_pokeBA0(chip, BA0_CLKCR2, CLKCR2_PDIVS_8);

	/*
	 *  Power up the PLL.
	 */
	snd_cs46xx_pokeBA0(chip, BA0_CLKCR1, CLKCR1_PLLP);

	/*
         *  Wait until the PLL has stabilized.
	 */
	msleep(100);

	/*
	 *  Turn on घड़ीing of the core so that we can setup the serial ports.
	 */
	snd_cs46xx_pokeBA0(chip, BA0_CLKCR1, CLKCR1_PLLP | CLKCR1_SWCE);

	/*
	 * Enable FIFO  Host Bypass
	 */
	snd_cs46xx_pokeBA0(chip, BA0_SERBCF, SERBCF_HBP);

	/*
	 *  Fill the serial port FIFOs with silence.
	 */
	snd_cs46xx_clear_serial_FIFOs(chip);

	/*
	 *  Set the serial port FIFO poपूर्णांकer to the first sample in the FIFO.
	 */
	/* snd_cs46xx_pokeBA0(chip, BA0_SERBSP, 0); */

	/*
	 *  Write the serial port configuration to the part.  The master
	 *  enable bit is not set until all other values have been written.
	 */
	snd_cs46xx_pokeBA0(chip, BA0_SERC1, SERC1_SO1F_AC97 | SERC1_SO1EN);
	snd_cs46xx_pokeBA0(chip, BA0_SERC2, SERC2_SI1F_AC97 | SERC1_SO1EN);
	snd_cs46xx_pokeBA0(chip, BA0_SERMC1, SERMC1_PTC_AC97 | SERMC1_MSPE);


#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	snd_cs46xx_pokeBA0(chip, BA0_SERC7, SERC7_ASDI2EN);
	snd_cs46xx_pokeBA0(chip, BA0_SERC3, 0);
	snd_cs46xx_pokeBA0(chip, BA0_SERC4, 0);
	snd_cs46xx_pokeBA0(chip, BA0_SERC5, 0);
	snd_cs46xx_pokeBA0(chip, BA0_SERC6, 1);
#पूर्ण_अगर

	mdelay(5);


	/*
	 * Wait क्रम the codec पढ़ोy संकेत from the AC97 codec.
	 */
	समयout = 150;
	जबतक (समयout-- > 0) अणु
		/*
		 *  Read the AC97 status रेजिस्टर to see अगर we've seen a CODEC READY
		 *  संकेत from the AC97 codec.
		 */
		अगर (snd_cs46xx_peekBA0(chip, BA0_ACSTS) & ACSTS_CRDY)
			जाओ ok1;
		msleep(10);
	पूर्ण


	dev_err(chip->card->dev,
		"create - never read codec ready from AC'97\n");
	dev_err(chip->card->dev,
		"it is not probably bug, try to use CS4236 driver\n");
	वापस -EIO;
 ok1:
#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	अणु
		पूर्णांक count;
		क्रम (count = 0; count < 150; count++) अणु
			/* First, we want to रुको क्रम a लघु समय. */
			udelay(25);
        
			अगर (snd_cs46xx_peekBA0(chip, BA0_ACSTS2) & ACSTS_CRDY)
				अवरोध;
		पूर्ण

		/*
		 *  Make sure CODEC is READY.
		 */
		अगर (!(snd_cs46xx_peekBA0(chip, BA0_ACSTS2) & ACSTS_CRDY))
			dev_dbg(chip->card->dev,
				"never read card ready from secondary AC'97\n");
	पूर्ण
#पूर्ण_अगर

	/*
	 *  Assert the vaid frame संकेत so that we can start sending commands
	 *  to the AC97 codec.
	 */
	snd_cs46xx_pokeBA0(chip, BA0_ACCTL, ACCTL_VFRM | ACCTL_ESYN | ACCTL_RSTN);
#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	snd_cs46xx_pokeBA0(chip, BA0_ACCTL2, ACCTL_VFRM | ACCTL_ESYN | ACCTL_RSTN);
#पूर्ण_अगर


	/*
	 *  Wait until we've sampled input slots 3 and 4 as valid, meaning that
	 *  the codec is pumping ADC data across the AC-link.
	 */
	समयout = 150;
	जबतक (समयout-- > 0) अणु
		/*
		 *  Read the input slot valid रेजिस्टर and see अगर input slots 3 and
		 *  4 are valid yet.
		 */
		अगर ((snd_cs46xx_peekBA0(chip, BA0_ACISV) & (ACISV_ISV3 | ACISV_ISV4)) == (ACISV_ISV3 | ACISV_ISV4))
			जाओ ok2;
		msleep(10);
	पूर्ण

#अगर_अघोषित CONFIG_SND_CS46XX_NEW_DSP
	dev_err(chip->card->dev,
		"create - never read ISV3 & ISV4 from AC'97\n");
	वापस -EIO;
#अन्यथा
	/* This may happen on a cold boot with a Terratec SiXPack 5.1.
	   Reloading the driver may help, अगर there's other soundcards 
	   with the same problem I would like to know. (Benny) */

	dev_err(chip->card->dev, "never read ISV3 & ISV4 from AC'97\n");
	dev_err(chip->card->dev,
		"Try reloading the ALSA driver, if you find something\n");
	dev_err(chip->card->dev,
		"broken or not working on your soundcard upon\n");
	dev_err(chip->card->dev,
		"this message please report to alsa-devel@alsa-project.org\n");

	वापस -EIO;
#पूर्ण_अगर
 ok2:

	/*
	 *  Now, निश्चित valid frame and the slot 3 and 4 valid bits.  This will
	 *  commense the transfer of digital audio data to the AC97 codec.
	 */

	snd_cs46xx_pokeBA0(chip, BA0_ACOSV, ACOSV_SLV3 | ACOSV_SLV4);


	/*
	 *  Power करोwn the DAC and ADC.  We will घातer them up (अगर) when we need
	 *  them.
	 */
	/* snd_cs46xx_pokeBA0(chip, BA0_AC97_POWERDOWN, 0x300); */

	/*
	 *  Turn off the Processor by turning off the software घड़ी enable flag in 
	 *  the घड़ी control रेजिस्टर.
	 */
	/* पंचांगp = snd_cs46xx_peekBA0(chip, BA0_CLKCR1) & ~CLKCR1_SWCE; */
	/* snd_cs46xx_pokeBA0(chip, BA0_CLKCR1, पंचांगp); */

	वापस 0;
पूर्ण

/*
 *  start and load DSP 
 */

अटल व्योम cs46xx_enable_stream_irqs(काष्ठा snd_cs46xx *chip)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	snd_cs46xx_pokeBA0(chip, BA0_HICR, HICR_IEV | HICR_CHGM);
        
	पंचांगp = snd_cs46xx_peek(chip, BA1_PFIE);
	पंचांगp &= ~0x0000f03f;
	snd_cs46xx_poke(chip, BA1_PFIE, पंचांगp);	/* playback पूर्णांकerrupt enable */

	पंचांगp = snd_cs46xx_peek(chip, BA1_CIE);
	पंचांगp &= ~0x0000003f;
	पंचांगp |=  0x00000001;
	snd_cs46xx_poke(chip, BA1_CIE, पंचांगp);	/* capture पूर्णांकerrupt enable */
पूर्ण

पूर्णांक snd_cs46xx_start_dsp(काष्ठा snd_cs46xx *chip)
अणु	
	अचिन्हित पूर्णांक पंचांगp;
#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	पूर्णांक i;
#पूर्ण_अगर
	पूर्णांक err;

	/*
	 *  Reset the processor.
	 */
	snd_cs46xx_reset(chip);
	/*
	 *  Download the image to the processor.
	 */
#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	क्रम (i = 0; i < CS46XX_DSP_MODULES; i++) अणु
		err = load_firmware(chip, &chip->modules[i], module_names[i]);
		अगर (err < 0) अणु
			dev_err(chip->card->dev, "firmware load error [%s]\n",
				   module_names[i]);
			वापस err;
		पूर्ण
		err = cs46xx_dsp_load_module(chip, chip->modules[i]);
		अगर (err < 0) अणु
			dev_err(chip->card->dev, "image download error [%s]\n",
				   module_names[i]);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (cs46xx_dsp_scb_and_task_init(chip) < 0)
		वापस -EIO;
#अन्यथा
	err = load_firmware(chip);
	अगर (err < 0)
		वापस err;

	/* old image */
	err = snd_cs46xx_करोwnload_image(chip);
	अगर (err < 0) अणु
		dev_err(chip->card->dev, "image download error\n");
		वापस err;
	पूर्ण

	/*
         *  Stop playback DMA.
	 */
	पंचांगp = snd_cs46xx_peek(chip, BA1_PCTL);
	chip->play_ctl = पंचांगp & 0xffff0000;
	snd_cs46xx_poke(chip, BA1_PCTL, पंचांगp & 0x0000ffff);
#पूर्ण_अगर

	/*
         *  Stop capture DMA.
	 */
	पंचांगp = snd_cs46xx_peek(chip, BA1_CCTL);
	chip->capt.ctl = पंचांगp & 0x0000ffff;
	snd_cs46xx_poke(chip, BA1_CCTL, पंचांगp & 0xffff0000);

	mdelay(5);

	snd_cs46xx_set_play_sample_rate(chip, 8000);
	snd_cs46xx_set_capture_sample_rate(chip, 8000);

	snd_cs46xx_proc_start(chip);

	cs46xx_enable_stream_irqs(chip);
	
#अगर_अघोषित CONFIG_SND_CS46XX_NEW_DSP
	/* set the attenuation to 0dB */ 
	snd_cs46xx_poke(chip, BA1_PVOL, 0x80008000);
	snd_cs46xx_poke(chip, BA1_CVOL, 0x80008000);
#पूर्ण_अगर

	वापस 0;
पूर्ण


/*
 *	AMP control - null AMP
 */
 
अटल व्योम amp_none(काष्ठा snd_cs46xx *chip, पूर्णांक change)
अणु	
पूर्ण

#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
अटल पूर्णांक voyetra_setup_eapd_slot(काष्ठा snd_cs46xx *chip)
अणु
	
	u32 idx, valid_slots,पंचांगp,घातerकरोwn = 0;
	u16 modem_घातer,pin_config,logic_type;

	dev_dbg(chip->card->dev, "cs46xx_setup_eapd_slot()+\n");

	/*
	 *  See अगर the devices are घातered करोwn.  If so, we must घातer them up first
	 *  or they will not respond.
	 */
	पंचांगp = snd_cs46xx_peekBA0(chip, BA0_CLKCR1);

	अगर (!(पंचांगp & CLKCR1_SWCE)) अणु
		snd_cs46xx_pokeBA0(chip, BA0_CLKCR1, पंचांगp | CLKCR1_SWCE);
		घातerकरोwn = 1;
	पूर्ण

	/*
	 * Clear PRA.  The Bonzo chip will be used क्रम GPIO not क्रम modem
	 * stuff.
	 */
	अगर(chip->nr_ac97_codecs != 2) अणु
		dev_err(chip->card->dev,
			"cs46xx_setup_eapd_slot() - no secondary codec configured\n");
		वापस -EINVAL;
	पूर्ण

	modem_घातer = snd_cs46xx_codec_पढ़ो (chip, 
					     AC97_EXTENDED_MSTATUS,
					     CS46XX_SECONDARY_CODEC_INDEX);
	modem_घातer &=0xFEFF;

	snd_cs46xx_codec_ग_लिखो(chip, 
			       AC97_EXTENDED_MSTATUS, modem_घातer,
			       CS46XX_SECONDARY_CODEC_INDEX);

	/*
	 * Set GPIO pin's 7 and 8 so that they are configured क्रम output.
	 */
	pin_config = snd_cs46xx_codec_पढ़ो (chip, 
					    AC97_GPIO_CFG,
					    CS46XX_SECONDARY_CODEC_INDEX);
	pin_config &=0x27F;

	snd_cs46xx_codec_ग_लिखो(chip, 
			       AC97_GPIO_CFG, pin_config,
			       CS46XX_SECONDARY_CODEC_INDEX);
    
	/*
	 * Set GPIO pin's 7 and 8 so that they are compatible with CMOS logic.
	 */

	logic_type = snd_cs46xx_codec_पढ़ो(chip, AC97_GPIO_POLARITY,
					   CS46XX_SECONDARY_CODEC_INDEX);
	logic_type &=0x27F; 

	snd_cs46xx_codec_ग_लिखो (chip, AC97_GPIO_POLARITY, logic_type,
				CS46XX_SECONDARY_CODEC_INDEX);

	valid_slots = snd_cs46xx_peekBA0(chip, BA0_ACOSV);
	valid_slots |= 0x200;
	snd_cs46xx_pokeBA0(chip, BA0_ACOSV, valid_slots);

	अगर ( cs46xx_रुको_क्रम_fअगरo(chip,1) ) अणु
		dev_dbg(chip->card->dev, "FIFO is busy\n");
	  
	  वापस -EINVAL;
	पूर्ण

	/*
	 * Fill slots 12 with the correct value क्रम the GPIO pins. 
	 */
	क्रम(idx = 0x90; idx <= 0x9F; idx++) अणु
		/*
		 * Initialize the fअगरo so that bits 7 and 8 are on.
		 *
		 * Remember that the GPIO pins in bonzo are shअगरted by 4 bits to
		 * the left.  0x1800 corresponds to bits 7 and 8.
		 */
		snd_cs46xx_pokeBA0(chip, BA0_SERBWP, 0x1800);

		/*
		 * Wait क्रम command to complete
		 */
		अगर ( cs46xx_रुको_क्रम_fअगरo(chip,200) ) अणु
			dev_dbg(chip->card->dev,
				"failed waiting for FIFO at addr (%02X)\n",
				idx);

			वापस -EINVAL;
		पूर्ण
            
		/*
		 * Write the serial port FIFO index.
		 */
		snd_cs46xx_pokeBA0(chip, BA0_SERBAD, idx);
      
		/*
		 * Tell the serial port to load the new value पूर्णांकo the FIFO location.
		 */
		snd_cs46xx_pokeBA0(chip, BA0_SERBCM, SERBCM_WRC);
	पूर्ण

	/* रुको क्रम last command to complete */
	cs46xx_रुको_क्रम_fअगरo(chip,200);

	/*
	 *  Now, अगर we घातered up the devices, then घातer them back करोwn again.
	 *  This is kinda ugly, but should never happen.
	 */
	अगर (घातerकरोwn)
		snd_cs46xx_pokeBA0(chip, BA0_CLKCR1, पंचांगp);

	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 *	Crystal EAPD mode
 */
 
अटल व्योम amp_voyetra(काष्ठा snd_cs46xx *chip, पूर्णांक change)
अणु
	/* Manage the EAPD bit on the Crystal 4297 
	   and the Analog AD1885 */
	   
#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	पूर्णांक old = chip->amplअगरier;
#पूर्ण_अगर
	पूर्णांक oval, val;
	
	chip->amplअगरier += change;
	oval = snd_cs46xx_codec_पढ़ो(chip, AC97_POWERDOWN,
				     CS46XX_PRIMARY_CODEC_INDEX);
	val = oval;
	अगर (chip->amplअगरier) अणु
		/* Turn the EAPD amp on */
		val |= 0x8000;
	पूर्ण अन्यथा अणु
		/* Turn the EAPD amp off */
		val &= ~0x8000;
	पूर्ण
	अगर (val != oval) अणु
		snd_cs46xx_codec_ग_लिखो(chip, AC97_POWERDOWN, val,
				       CS46XX_PRIMARY_CODEC_INDEX);
		अगर (chip->eapd_चयन)
			snd_ctl_notअगरy(chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
				       &chip->eapd_चयन->id);
	पूर्ण

#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	अगर (chip->amplअगरier && !old) अणु
		voyetra_setup_eapd_slot(chip);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम hercules_init(काष्ठा snd_cs46xx *chip) 
अणु
	/* शेष: AMP off, and SPDIF input optical */
	snd_cs46xx_pokeBA0(chip, BA0_EGPIODR, EGPIODR_GPOE0);
	snd_cs46xx_pokeBA0(chip, BA0_EGPIOPTR, EGPIODR_GPOE0);
पूर्ण


/*
 *	Game Theatre XP card - EGPIO[2] is used to enable the बाह्यal amp.
 */ 
अटल व्योम amp_hercules(काष्ठा snd_cs46xx *chip, पूर्णांक change)
अणु
	पूर्णांक old = chip->amplअगरier;
	पूर्णांक val1 = snd_cs46xx_peekBA0(chip, BA0_EGPIODR);
	पूर्णांक val2 = snd_cs46xx_peekBA0(chip, BA0_EGPIOPTR);

	chip->amplअगरier += change;
	अगर (chip->amplअगरier && !old) अणु
		dev_dbg(chip->card->dev, "Hercules amplifier ON\n");

		snd_cs46xx_pokeBA0(chip, BA0_EGPIODR, 
				   EGPIODR_GPOE2 | val1);     /* enable EGPIO2 output */
		snd_cs46xx_pokeBA0(chip, BA0_EGPIOPTR, 
				   EGPIOPTR_GPPT2 | val2);   /* खोलो-drain on output */
	पूर्ण अन्यथा अगर (old && !chip->amplअगरier) अणु
		dev_dbg(chip->card->dev, "Hercules amplifier OFF\n");
		snd_cs46xx_pokeBA0(chip, BA0_EGPIODR,  val1 & ~EGPIODR_GPOE2); /* disable */
		snd_cs46xx_pokeBA0(chip, BA0_EGPIOPTR, val2 & ~EGPIOPTR_GPPT2); /* disable */
	पूर्ण
पूर्ण

अटल व्योम voyetra_mixer_init (काष्ठा snd_cs46xx *chip)
अणु
	dev_dbg(chip->card->dev, "initializing Voyetra mixer\n");

	/* Enable SPDIF out */
	snd_cs46xx_pokeBA0(chip, BA0_EGPIODR, EGPIODR_GPOE0);
	snd_cs46xx_pokeBA0(chip, BA0_EGPIOPTR, EGPIODR_GPOE0);
पूर्ण

अटल व्योम hercules_mixer_init (काष्ठा snd_cs46xx *chip)
अणु
#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	अचिन्हित पूर्णांक idx;
	पूर्णांक err;
	काष्ठा snd_card *card = chip->card;
#पूर्ण_अगर

	/* set EGPIO to शेष */
	hercules_init(chip);

	dev_dbg(chip->card->dev, "initializing Hercules mixer\n");

#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	अगर (chip->in_suspend)
		वापस;

	क्रम (idx = 0 ; idx < ARRAY_SIZE(snd_hercules_controls); idx++) अणु
		काष्ठा snd_kcontrol *kctl;

		kctl = snd_ctl_new1(&snd_hercules_controls[idx], chip);
		अगर ((err = snd_ctl_add(card, kctl)) < 0) अणु
			dev_err(card->dev,
				"failed to initialize Hercules mixer (%d)\n",
				err);
			अवरोध;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण


#अगर 0
/*
 *	Untested
 */
 
अटल व्योम amp_voyetra_4294(काष्ठा snd_cs46xx *chip, पूर्णांक change)
अणु
	chip->amplअगरier += change;

	अगर (chip->amplअगरier) अणु
		/* Switch the GPIO pins 7 and 8 to खोलो drain */
		snd_cs46xx_codec_ग_लिखो(chip, 0x4C,
				       snd_cs46xx_codec_पढ़ो(chip, 0x4C) & 0xFE7F);
		snd_cs46xx_codec_ग_लिखो(chip, 0x4E,
				       snd_cs46xx_codec_पढ़ो(chip, 0x4E) | 0x0180);
		/* Now wake the AMP (this might be backwards) */
		snd_cs46xx_codec_ग_लिखो(chip, 0x54,
				       snd_cs46xx_codec_पढ़ो(chip, 0x54) & ~0x0180);
	पूर्ण अन्यथा अणु
		snd_cs46xx_codec_ग_लिखो(chip, 0x54,
				       snd_cs46xx_codec_पढ़ो(chip, 0x54) | 0x0180);
	पूर्ण
पूर्ण
#पूर्ण_अगर


/*
 *	Handle the CLKRUN on a thinkpad. We must disable CLKRUN support
 *	whenever we need to beat on the chip.
 *
 *	The original idea and code क्रम this hack comes from David Kaiser at
 *	Linuxcare. Perhaps one day Crystal will करोcument their chips well
 *	enough to make them useful.
 */
 
अटल व्योम clkrun_hack(काष्ठा snd_cs46xx *chip, पूर्णांक change)
अणु
	u16 control, nval;
	
	अगर (!chip->acpi_port)
		वापस;

	chip->amplअगरier += change;
	
	/* Read ACPI port */	
	nval = control = inw(chip->acpi_port + 0x10);

	/* Flip CLKRUN off जबतक running */
	अगर (! chip->amplअगरier)
		nval |= 0x2000;
	अन्यथा
		nval &= ~0x2000;
	अगर (nval != control)
		outw(nval, chip->acpi_port + 0x10);
पूर्ण

	
/*
 * detect पूर्णांकel piix4
 */
अटल व्योम clkrun_init(काष्ठा snd_cs46xx *chip)
अणु
	काष्ठा pci_dev *pdev;
	u8 pp;

	chip->acpi_port = 0;
	
	pdev = pci_get_device(PCI_VENDOR_ID_INTEL,
		PCI_DEVICE_ID_INTEL_82371AB_3, शून्य);
	अगर (pdev == शून्य)
		वापस;		/* Not a thinkpad thats क्रम sure */

	/* Find the control port */		
	pci_पढ़ो_config_byte(pdev, 0x41, &pp);
	chip->acpi_port = pp << 8;
	pci_dev_put(pdev);
पूर्ण


/*
 * Card subid table
 */
 
काष्ठा cs_card_type
अणु
	u16 venकरोr;
	u16 id;
	अक्षर *name;
	व्योम (*init)(काष्ठा snd_cs46xx *);
	व्योम (*amp)(काष्ठा snd_cs46xx *, पूर्णांक);
	व्योम (*active)(काष्ठा snd_cs46xx *, पूर्णांक);
	व्योम (*mixer_init)(काष्ठा snd_cs46xx *);
पूर्ण;

अटल काष्ठा cs_card_type cards[] = अणु
	अणु
		.venकरोr = 0x1489,
		.id = 0x7001,
		.name = "Genius Soundmaker 128 value",
		/* nothing special */
	पूर्ण,
	अणु
		.venकरोr = 0x5053,
		.id = 0x3357,
		.name = "Voyetra",
		.amp = amp_voyetra,
		.mixer_init = voyetra_mixer_init,
	पूर्ण,
	अणु
		.venकरोr = 0x1071,
		.id = 0x6003,
		.name = "Mitac MI6020/21",
		.amp = amp_voyetra,
	पूर्ण,
	/* Hercules Game Theatre XP */
	अणु
		.venकरोr = 0x14af, /* Guillemot Corporation */
		.id = 0x0050,
		.name = "Hercules Game Theatre XP",
		.amp = amp_hercules,
		.mixer_init = hercules_mixer_init,
	पूर्ण,
	अणु
		.venकरोr = 0x1681,
		.id = 0x0050,
		.name = "Hercules Game Theatre XP",
		.amp = amp_hercules,
		.mixer_init = hercules_mixer_init,
	पूर्ण,
	अणु
		.venकरोr = 0x1681,
		.id = 0x0051,
		.name = "Hercules Game Theatre XP",
		.amp = amp_hercules,
		.mixer_init = hercules_mixer_init,

	पूर्ण,
	अणु
		.venकरोr = 0x1681,
		.id = 0x0052,
		.name = "Hercules Game Theatre XP",
		.amp = amp_hercules,
		.mixer_init = hercules_mixer_init,
	पूर्ण,
	अणु
		.venकरोr = 0x1681,
		.id = 0x0053,
		.name = "Hercules Game Theatre XP",
		.amp = amp_hercules,
		.mixer_init = hercules_mixer_init,
	पूर्ण,
	अणु
		.venकरोr = 0x1681,
		.id = 0x0054,
		.name = "Hercules Game Theatre XP",
		.amp = amp_hercules,
		.mixer_init = hercules_mixer_init,
	पूर्ण,
	/* Herculess Fortissimo */
	अणु
		.venकरोr = 0x1681,
		.id = 0xa010,
		.name = "Hercules Gamesurround Fortissimo II",
	पूर्ण,
	अणु
		.venकरोr = 0x1681,
		.id = 0xa011,
		.name = "Hercules Gamesurround Fortissimo III 7.1",
	पूर्ण,
	/* Teratec */
	अणु
		.venकरोr = 0x153b,
		.id = 0x112e,
		.name = "Terratec DMX XFire 1024",
	पूर्ण,
	अणु
		.venकरोr = 0x153b,
		.id = 0x1136,
		.name = "Terratec SiXPack 5.1",
	पूर्ण,
	/* Not sure अगर the 570 needs the clkrun hack */
	अणु
		.venकरोr = PCI_VENDOR_ID_IBM,
		.id = 0x0132,
		.name = "Thinkpad 570",
		.init = clkrun_init,
		.active = clkrun_hack,
	पूर्ण,
	अणु
		.venकरोr = PCI_VENDOR_ID_IBM,
		.id = 0x0153,
		.name = "Thinkpad 600X/A20/T20",
		.init = clkrun_init,
		.active = clkrun_hack,
	पूर्ण,
	अणु
		.venकरोr = PCI_VENDOR_ID_IBM,
		.id = 0x1010,
		.name = "Thinkpad 600E (unsupported)",
	पूर्ण,
	अणुपूर्ण /* terminator */
पूर्ण;


/*
 * APM support
 */
#अगर_घोषित CONFIG_PM_SLEEP
अटल स्थिर अचिन्हित पूर्णांक saved_regs[] = अणु
	BA0_ACOSV,
	/*BA0_ASER_FADDR,*/
	BA0_ASER_MASTER,
	BA1_PVOL,
	BA1_CVOL,
पूर्ण;

अटल पूर्णांक snd_cs46xx_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_cs46xx *chip = card->निजी_data;
	पूर्णांक i, amp_saved;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	chip->in_suspend = 1;
	// chip->ac97_घातerकरोwn = snd_cs46xx_codec_पढ़ो(chip, AC97_POWER_CONTROL);
	// chip->ac97_general_purpose = snd_cs46xx_codec_पढ़ो(chip, BA0_AC97_GENERAL_PURPOSE);

	snd_ac97_suspend(chip->ac97[CS46XX_PRIMARY_CODEC_INDEX]);
	snd_ac97_suspend(chip->ac97[CS46XX_SECONDARY_CODEC_INDEX]);

	/* save some रेजिस्टरs */
	क्रम (i = 0; i < ARRAY_SIZE(saved_regs); i++)
		chip->saved_regs[i] = snd_cs46xx_peekBA0(chip, saved_regs[i]);

	amp_saved = chip->amplअगरier;
	/* turn off amp */
	chip->amplअगरier_ctrl(chip, -chip->amplअगरier);
	snd_cs46xx_hw_stop(chip);
	/* disable CLKRUN */
	chip->active_ctrl(chip, -chip->amplअगरier);
	chip->amplअगरier = amp_saved; /* restore the status */
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs46xx_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_cs46xx *chip = card->निजी_data;
	पूर्णांक amp_saved;
#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	पूर्णांक i;
#पूर्ण_अगर
	अचिन्हित पूर्णांक पंचांगp;

	amp_saved = chip->amplअगरier;
	chip->amplअगरier = 0;
	chip->active_ctrl(chip, 1); /* क्रमce to on */

	snd_cs46xx_chip_init(chip);

	snd_cs46xx_reset(chip);
#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	cs46xx_dsp_resume(chip);
	/* restore some रेजिस्टरs */
	क्रम (i = 0; i < ARRAY_SIZE(saved_regs); i++)
		snd_cs46xx_pokeBA0(chip, saved_regs[i], chip->saved_regs[i]);
#अन्यथा
	snd_cs46xx_करोwnload_image(chip);
#पूर्ण_अगर

#अगर 0
	snd_cs46xx_codec_ग_लिखो(chip, BA0_AC97_GENERAL_PURPOSE, 
			       chip->ac97_general_purpose);
	snd_cs46xx_codec_ग_लिखो(chip, AC97_POWER_CONTROL, 
			       chip->ac97_घातerकरोwn);
	mdelay(10);
	snd_cs46xx_codec_ग_लिखो(chip, BA0_AC97_POWERDOWN,
			       chip->ac97_घातerकरोwn);
	mdelay(5);
#पूर्ण_अगर

	snd_ac97_resume(chip->ac97[CS46XX_PRIMARY_CODEC_INDEX]);
	snd_ac97_resume(chip->ac97[CS46XX_SECONDARY_CODEC_INDEX]);

	/*
         *  Stop capture DMA.
	 */
	पंचांगp = snd_cs46xx_peek(chip, BA1_CCTL);
	chip->capt.ctl = पंचांगp & 0x0000ffff;
	snd_cs46xx_poke(chip, BA1_CCTL, पंचांगp & 0xffff0000);

	mdelay(5);

	/* reset playback/capture */
	snd_cs46xx_set_play_sample_rate(chip, 8000);
	snd_cs46xx_set_capture_sample_rate(chip, 8000);
	snd_cs46xx_proc_start(chip);

	cs46xx_enable_stream_irqs(chip);

	अगर (amp_saved)
		chip->amplअगरier_ctrl(chip, 1); /* turn amp on */
	अन्यथा
		chip->active_ctrl(chip, -1); /* disable CLKRUN */
	chip->amplअगरier = amp_saved;
	chip->in_suspend = 0;
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण

SIMPLE_DEV_PM_OPS(snd_cs46xx_pm, snd_cs46xx_suspend, snd_cs46xx_resume);
#पूर्ण_अगर /* CONFIG_PM_SLEEP */


/*
 */

पूर्णांक snd_cs46xx_create(काष्ठा snd_card *card,
		      काष्ठा pci_dev *pci,
		      पूर्णांक बाह्यal_amp, पूर्णांक thinkpad,
		      काष्ठा snd_cs46xx **rchip)
अणु
	काष्ठा snd_cs46xx *chip;
	पूर्णांक err, idx;
	काष्ठा snd_cs46xx_region *region;
	काष्ठा cs_card_type *cp;
	u16 ss_card, ss_venकरोr;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_cs46xx_dev_मुक्त,
	पूर्ण;
	
	*rchip = शून्य;

	/* enable PCI device */
	अगर ((err = pci_enable_device(pci)) < 0)
		वापस err;

	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण
	spin_lock_init(&chip->reg_lock);
#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	mutex_init(&chip->spos_mutex);
#पूर्ण_अगर
	chip->card = card;
	chip->pci = pci;
	chip->irq = -1;
	chip->ba0_addr = pci_resource_start(pci, 0);
	chip->ba1_addr = pci_resource_start(pci, 1);
	अगर (chip->ba0_addr == 0 || chip->ba0_addr == (अचिन्हित दीर्घ)~0 ||
	    chip->ba1_addr == 0 || chip->ba1_addr == (अचिन्हित दीर्घ)~0) अणु
		dev_err(chip->card->dev,
			"wrong address(es) - ba0 = 0x%lx, ba1 = 0x%lx\n",
			   chip->ba0_addr, chip->ba1_addr);
	    	snd_cs46xx_मुक्त(chip);
	    	वापस -ENOMEM;
	पूर्ण

	region = &chip->region.name.ba0;
	म_नकल(region->name, "CS46xx_BA0");
	region->base = chip->ba0_addr;
	region->size = CS46XX_BA0_SIZE;

	region = &chip->region.name.data0;
	म_नकल(region->name, "CS46xx_BA1_data0");
	region->base = chip->ba1_addr + BA1_SP_DMEM0;
	region->size = CS46XX_BA1_DATA0_SIZE;

	region = &chip->region.name.data1;
	म_नकल(region->name, "CS46xx_BA1_data1");
	region->base = chip->ba1_addr + BA1_SP_DMEM1;
	region->size = CS46XX_BA1_DATA1_SIZE;

	region = &chip->region.name.pmem;
	म_नकल(region->name, "CS46xx_BA1_pmem");
	region->base = chip->ba1_addr + BA1_SP_PMEM;
	region->size = CS46XX_BA1_PRG_SIZE;

	region = &chip->region.name.reg;
	म_नकल(region->name, "CS46xx_BA1_reg");
	region->base = chip->ba1_addr + BA1_SP_REG;
	region->size = CS46XX_BA1_REG_SIZE;

	/* set up amp and clkrun hack */
	pci_पढ़ो_config_word(pci, PCI_SUBSYSTEM_VENDOR_ID, &ss_venकरोr);
	pci_पढ़ो_config_word(pci, PCI_SUBSYSTEM_ID, &ss_card);

	क्रम (cp = &cards[0]; cp->name; cp++) अणु
		अगर (cp->venकरोr == ss_venकरोr && cp->id == ss_card) अणु
			dev_dbg(chip->card->dev, "hack for %s enabled\n",
				cp->name);

			chip->amplअगरier_ctrl = cp->amp;
			chip->active_ctrl = cp->active;
			chip->mixer_init = cp->mixer_init;

			अगर (cp->init)
				cp->init(chip);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (बाह्यal_amp) अणु
		dev_info(chip->card->dev,
			 "Crystal EAPD support forced on.\n");
		chip->amplअगरier_ctrl = amp_voyetra;
	पूर्ण

	अगर (thinkpad) अणु
		dev_info(chip->card->dev,
			 "Activating CLKRUN hack for Thinkpad.\n");
		chip->active_ctrl = clkrun_hack;
		clkrun_init(chip);
	पूर्ण
	
	अगर (chip->amplअगरier_ctrl == शून्य)
		chip->amplअगरier_ctrl = amp_none;
	अगर (chip->active_ctrl == शून्य)
		chip->active_ctrl = amp_none;

	chip->active_ctrl(chip, 1); /* enable CLKRUN */

	pci_set_master(pci);

	क्रम (idx = 0; idx < 5; idx++) अणु
		region = &chip->region.idx[idx];
		अगर ((region->resource = request_mem_region(region->base, region->size,
							   region->name)) == शून्य) अणु
			dev_err(chip->card->dev,
				"unable to request memory region 0x%lx-0x%lx\n",
				   region->base, region->base + region->size - 1);
			snd_cs46xx_मुक्त(chip);
			वापस -EBUSY;
		पूर्ण
		region->remap_addr = ioremap(region->base, region->size);
		अगर (region->remap_addr == शून्य) अणु
			dev_err(chip->card->dev,
				"%s ioremap problem\n", region->name);
			snd_cs46xx_मुक्त(chip);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	अगर (request_irq(pci->irq, snd_cs46xx_पूर्णांकerrupt, IRQF_SHARED,
			KBUILD_MODNAME, chip)) अणु
		dev_err(chip->card->dev, "unable to grab IRQ %d\n", pci->irq);
		snd_cs46xx_मुक्त(chip);
		वापस -EBUSY;
	पूर्ण
	chip->irq = pci->irq;
	card->sync_irq = chip->irq;

#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	chip->dsp_spos_instance = cs46xx_dsp_spos_create(chip);
	अगर (chip->dsp_spos_instance == शून्य) अणु
		snd_cs46xx_मुक्त(chip);
		वापस -ENOMEM;
	पूर्ण
#पूर्ण_अगर

	err = snd_cs46xx_chip_init(chip);
	अगर (err < 0) अणु
		snd_cs46xx_मुक्त(chip);
		वापस err;
	पूर्ण

	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops)) < 0) अणु
		snd_cs46xx_मुक्त(chip);
		वापस err;
	पूर्ण
	
	snd_cs46xx_proc_init(card, chip);

#अगर_घोषित CONFIG_PM_SLEEP
	chip->saved_regs = kदो_स्मृति_array(ARRAY_SIZE(saved_regs),
					 माप(*chip->saved_regs),
					 GFP_KERNEL);
	अगर (!chip->saved_regs) अणु
		snd_cs46xx_मुक्त(chip);
		वापस -ENOMEM;
	पूर्ण
#पूर्ण_अगर

	chip->active_ctrl(chip, -1); /* disable CLKRUN */

	*rchip = chip;
	वापस 0;
पूर्ण
