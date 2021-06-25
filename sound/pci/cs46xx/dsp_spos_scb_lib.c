<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 */

/*
 * 2002-07 Benny Sjostअक्रम benny@hosपंचांगobility.com
 */


#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>

#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/info.h>
#समावेश "cs46xx.h"

#समावेश "cs46xx_lib.h"
#समावेश "dsp_spos.h"

काष्ठा proc_scb_info अणु
	काष्ठा dsp_scb_descriptor * scb_desc;
	काष्ठा snd_cs46xx *chip;
पूर्ण;

अटल व्योम हटाओ_symbol (काष्ठा snd_cs46xx * chip, काष्ठा dsp_symbol_entry * symbol)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	पूर्णांक symbol_index = (पूर्णांक)(symbol - ins->symbol_table.symbols);

	अगर (snd_BUG_ON(ins->symbol_table.nsymbols <= 0))
		वापस;
	अगर (snd_BUG_ON(symbol_index < 0 ||
		       symbol_index >= ins->symbol_table.nsymbols))
		वापस;

	ins->symbol_table.symbols[symbol_index].deleted = 1;

	अगर (symbol_index < ins->symbol_table.highest_frag_index) अणु
		ins->symbol_table.highest_frag_index = symbol_index;
	पूर्ण
  
	अगर (symbol_index == ins->symbol_table.nsymbols - 1)
		ins->symbol_table.nsymbols --;

	अगर (ins->symbol_table.highest_frag_index > ins->symbol_table.nsymbols) अणु
		ins->symbol_table.highest_frag_index = ins->symbol_table.nsymbols;
	पूर्ण

पूर्ण

#अगर_घोषित CONFIG_SND_PROC_FS
अटल व्योम cs46xx_dsp_proc_scb_info_पढ़ो (काष्ठा snd_info_entry *entry,
					   काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा proc_scb_info * scb_info  = entry->निजी_data;
	काष्ठा dsp_scb_descriptor * scb = scb_info->scb_desc;
	काष्ठा snd_cs46xx *chip = scb_info->chip;
	पूर्णांक j,col;
	व्योम __iomem *dst = chip->region.idx[1].remap_addr + DSP_PARAMETER_BYTE_OFFSET;

	mutex_lock(&chip->spos_mutex);
	snd_iम_लिखो(buffer,"%04x %s:\n",scb->address,scb->scb_name);

	क्रम (col = 0,j = 0;j < 0x10; j++,col++) अणु
		अगर (col == 4) अणु
			snd_iम_लिखो(buffer,"\n");
			col = 0;
		पूर्ण
		snd_iम_लिखो(buffer,"%08x ",पढ़ोl(dst + (scb->address + j) * माप(u32)));
	पूर्ण
  
	snd_iम_लिखो(buffer,"\n");

	अगर (scb->parent_scb_ptr != शून्य) अणु
		snd_iम_लिखो(buffer,"parent [%s:%04x] ", 
			    scb->parent_scb_ptr->scb_name,
			    scb->parent_scb_ptr->address);
	पूर्ण अन्यथा snd_iम_लिखो(buffer,"parent [none] ");
  
	snd_iम_लिखो(buffer,"sub_list_ptr [%s:%04x]\nnext_scb_ptr [%s:%04x]  task_entry [%s:%04x]\n",
		    scb->sub_list_ptr->scb_name,
		    scb->sub_list_ptr->address,
		    scb->next_scb_ptr->scb_name,
		    scb->next_scb_ptr->address,
		    scb->task_entry->symbol_name,
		    scb->task_entry->address);

	snd_iम_लिखो(buffer,"index [%d] ref_count [%d]\n",scb->index,scb->ref_count);  
	mutex_unlock(&chip->spos_mutex);
पूर्ण
#पूर्ण_अगर

अटल व्योम _dsp_unlink_scb (काष्ठा snd_cs46xx *chip, काष्ठा dsp_scb_descriptor * scb)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;

	अगर ( scb->parent_scb_ptr ) अणु
		/* unlink parent SCB */
		अगर (snd_BUG_ON(scb->parent_scb_ptr->sub_list_ptr != scb &&
			       scb->parent_scb_ptr->next_scb_ptr != scb))
			वापस;
  
		अगर (scb->parent_scb_ptr->sub_list_ptr == scb) अणु

			अगर (scb->next_scb_ptr == ins->the_null_scb) अणु
				/* last and only node in parent sublist */
				scb->parent_scb_ptr->sub_list_ptr = scb->sub_list_ptr;

				अगर (scb->sub_list_ptr != ins->the_null_scb) अणु
					scb->sub_list_ptr->parent_scb_ptr = scb->parent_scb_ptr;
				पूर्ण
				scb->sub_list_ptr = ins->the_null_scb;
			पूर्ण अन्यथा अणु
				/* first node in parent sublist */
				scb->parent_scb_ptr->sub_list_ptr = scb->next_scb_ptr;

				अगर (scb->next_scb_ptr != ins->the_null_scb) अणु
					/* update next node parent ptr. */
					scb->next_scb_ptr->parent_scb_ptr = scb->parent_scb_ptr;
				पूर्ण
				scb->next_scb_ptr = ins->the_null_scb;
			पूर्ण
		पूर्ण अन्यथा अणु
			scb->parent_scb_ptr->next_scb_ptr = scb->next_scb_ptr;

			अगर (scb->next_scb_ptr != ins->the_null_scb) अणु
				/* update next node parent ptr. */
				scb->next_scb_ptr->parent_scb_ptr = scb->parent_scb_ptr;
			पूर्ण
			scb->next_scb_ptr = ins->the_null_scb;
		पूर्ण

		/* update parent first entry in DSP RAM */
		cs46xx_dsp_spos_update_scb(chip,scb->parent_scb_ptr);

		/* then update entry in DSP RAM */
		cs46xx_dsp_spos_update_scb(chip,scb);

		scb->parent_scb_ptr = शून्य;
	पूर्ण
पूर्ण

अटल व्योम _dsp_clear_sample_buffer (काष्ठा snd_cs46xx *chip, u32 sample_buffer_addr,
				      पूर्णांक dword_count) 
अणु
	व्योम __iomem *dst = chip->region.idx[2].remap_addr + sample_buffer_addr;
	पूर्णांक i;
  
	क्रम (i = 0; i < dword_count ; ++i ) अणु
		ग_लिखोl(0, dst);
		dst += 4;
	पूर्ण  
पूर्ण

व्योम cs46xx_dsp_हटाओ_scb (काष्ठा snd_cs46xx *chip, काष्ठा dsp_scb_descriptor * scb)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	अचिन्हित दीर्घ flags;

	/* check पूर्णांकegrety */
	अगर (snd_BUG_ON(scb->index < 0 ||
		       scb->index >= ins->nscb ||
		       (ins->scbs + scb->index) != scb))
		वापस;

#अगर 0
	/* can't हटाओ a SCB with childs beक्रमe 
	   removing childs first  */
	अगर (snd_BUG_ON(scb->sub_list_ptr != ins->the_null_scb ||
		       scb->next_scb_ptr != ins->the_null_scb))
		जाओ _end;
#पूर्ण_अगर

	spin_lock_irqsave(&chip->reg_lock, flags);    
	_dsp_unlink_scb (chip,scb);
	spin_unlock_irqrestore(&chip->reg_lock, flags);

	cs46xx_dsp_proc_मुक्त_scb_desc(scb);
	अगर (snd_BUG_ON(!scb->scb_symbol))
		वापस;
	हटाओ_symbol (chip,scb->scb_symbol);

	ins->scbs[scb->index].deleted = 1;
#अगर_घोषित CONFIG_PM_SLEEP
	kमुक्त(ins->scbs[scb->index].data);
	ins->scbs[scb->index].data = शून्य;
#पूर्ण_अगर

	अगर (scb->index < ins->scb_highest_frag_index)
		ins->scb_highest_frag_index = scb->index;

	अगर (scb->index == ins->nscb - 1) अणु
		ins->nscb --;
	पूर्ण

	अगर (ins->scb_highest_frag_index > ins->nscb) अणु
		ins->scb_highest_frag_index = ins->nscb;
	पूर्ण

#अगर 0
	/* !!!! THIS IS A PIECE OF SHIT MADE BY ME !!! */
	क्रम(i = scb->index + 1;i < ins->nscb; ++i) अणु
		ins->scbs[i - 1].index = i - 1;
	पूर्ण
#पूर्ण_अगर
पूर्ण


#अगर_घोषित CONFIG_SND_PROC_FS
व्योम cs46xx_dsp_proc_मुक्त_scb_desc (काष्ठा dsp_scb_descriptor * scb)
अणु
	अगर (scb->proc_info) अणु
		काष्ठा proc_scb_info * scb_info = scb->proc_info->निजी_data;
		काष्ठा snd_cs46xx *chip = scb_info->chip;

		dev_dbg(chip->card->dev,
			"cs46xx_dsp_proc_free_scb_desc: freeing %s\n",
			scb->scb_name);

		snd_info_मुक्त_entry(scb->proc_info);
		scb->proc_info = शून्य;

		kमुक्त (scb_info);
	पूर्ण
पूर्ण

व्योम cs46xx_dsp_proc_रेजिस्टर_scb_desc (काष्ठा snd_cs46xx *chip,
					काष्ठा dsp_scb_descriptor * scb)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	काष्ठा snd_info_entry * entry;
	काष्ठा proc_scb_info * scb_info;

	/* रेजिस्टर to proc */
	अगर (ins->snd_card != शून्य && ins->proc_dsp_dir != शून्य &&
	    scb->proc_info == शून्य) अणु
  
		entry = snd_info_create_card_entry(ins->snd_card, scb->scb_name,
						   ins->proc_dsp_dir);
		अगर (entry) अणु
			scb_info = kदो_स्मृति(माप(काष्ठा proc_scb_info), GFP_KERNEL);
			अगर (!scb_info) अणु
				snd_info_मुक्त_entry(entry);
				entry = शून्य;
				जाओ out;
			पूर्ण

			scb_info->chip = chip;
			scb_info->scb_desc = scb;
			snd_info_set_text_ops(entry, scb_info,
					      cs46xx_dsp_proc_scb_info_पढ़ो);
		पूर्ण
out:
		scb->proc_info = entry;
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_SND_PROC_FS */

अटल काष्ठा dsp_scb_descriptor * 
_dsp_create_generic_scb (काष्ठा snd_cs46xx *chip, अक्षर * name, u32 * scb_data, u32 dest,
                         काष्ठा dsp_symbol_entry * task_entry,
                         काष्ठा dsp_scb_descriptor * parent_scb,
                         पूर्णांक scb_child_type)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	काष्ठा dsp_scb_descriptor * scb;
  
	अचिन्हित दीर्घ flags;

	अगर (snd_BUG_ON(!ins->the_null_scb))
		वापस शून्य;

	/* fill the data that will be wroten to DSP */
	scb_data[SCBsubListPtr] = 
		(ins->the_null_scb->address << 0x10) | ins->the_null_scb->address;

	scb_data[SCBfuncEntryPtr] &= 0xFFFF0000;
	scb_data[SCBfuncEntryPtr] |= task_entry->address;

	dev_dbg(chip->card->dev, "dsp_spos: creating SCB <%s>\n", name);

	scb = cs46xx_dsp_create_scb(chip,name,scb_data,dest);


	scb->sub_list_ptr = ins->the_null_scb;
	scb->next_scb_ptr = ins->the_null_scb;

	scb->parent_scb_ptr = parent_scb;
	scb->task_entry = task_entry;

  
	/* update parent SCB */
	अगर (scb->parent_scb_ptr) अणु
#अगर 0
		dev_dbg(chip->card->dev,
			"scb->parent_scb_ptr = %s\n",
			scb->parent_scb_ptr->scb_name);
		dev_dbg(chip->card->dev,
			"scb->parent_scb_ptr->next_scb_ptr = %s\n",
			scb->parent_scb_ptr->next_scb_ptr->scb_name);
		dev_dbg(chip->card->dev,
			"scb->parent_scb_ptr->sub_list_ptr = %s\n",
			scb->parent_scb_ptr->sub_list_ptr->scb_name);
#पूर्ण_अगर
		/* link to  parent SCB */
		अगर (scb_child_type == SCB_ON_PARENT_NEXT_SCB) अणु
			अगर (snd_BUG_ON(scb->parent_scb_ptr->next_scb_ptr !=
				       ins->the_null_scb))
				वापस शून्य;

			scb->parent_scb_ptr->next_scb_ptr = scb;

		पूर्ण अन्यथा अगर (scb_child_type == SCB_ON_PARENT_SUBLIST_SCB) अणु
			अगर (snd_BUG_ON(scb->parent_scb_ptr->sub_list_ptr !=
				       ins->the_null_scb))
				वापस शून्य;

			scb->parent_scb_ptr->sub_list_ptr = scb;
		पूर्ण अन्यथा अणु
			snd_BUG();
		पूर्ण

		spin_lock_irqsave(&chip->reg_lock, flags);

		/* update entry in DSP RAM */
		cs46xx_dsp_spos_update_scb(chip,scb->parent_scb_ptr);

		spin_unlock_irqrestore(&chip->reg_lock, flags);
	पूर्ण


	cs46xx_dsp_proc_रेजिस्टर_scb_desc (chip,scb);

	वापस scb;
पूर्ण

अटल काष्ठा dsp_scb_descriptor * 
cs46xx_dsp_create_generic_scb (काष्ठा snd_cs46xx *chip, अक्षर * name, u32 * scb_data,
			       u32 dest, अक्षर * task_entry_name,
                               काष्ठा dsp_scb_descriptor * parent_scb,
                               पूर्णांक scb_child_type)
अणु
	काष्ठा dsp_symbol_entry * task_entry;

	task_entry = cs46xx_dsp_lookup_symbol (chip,task_entry_name,
					       SYMBOL_CODE);
  
	अगर (task_entry == शून्य) अणु
		dev_err(chip->card->dev,
			"dsp_spos: symbol %s not found\n", task_entry_name);
		वापस शून्य;
	पूर्ण
  
	वापस _dsp_create_generic_scb (chip,name,scb_data,dest,task_entry,
					parent_scb,scb_child_type);
पूर्ण

काष्ठा dsp_scb_descriptor * 
cs46xx_dsp_create_timing_master_scb (काष्ठा snd_cs46xx *chip)
अणु
	काष्ठा dsp_scb_descriptor * scb;
  
	काष्ठा dsp_timing_master_scb timing_master_scb = अणु
		अणु 0,
		  0,
		  0,
		  0
		पूर्ण,
		अणु 0,
		  0,
		  0,
		  0,
		  0
		पूर्ण,
		0,0,
		0,शून्य_SCB_ADDR,
		0,0,             /* extraSampleAccum:TMreserved */
		0,0,             /* codecFIFOptr:codecFIFOsyncd */
		0x0001,0x8000,   /* fracSampAccumQm1:TMfrmsLeftInGroup */
		0x0001,0x0000,   /* fracSampCorrectionQm1:TMfrmGroupLength */
		0x00060000       /* nSampPerFrmQ15 */
	पूर्ण;    
  
	scb = cs46xx_dsp_create_generic_scb(chip,"TimingMasterSCBInst",(u32 *)&timing_master_scb,
					    TIMINGMASTER_SCB_ADDR,
					    "TIMINGMASTER",शून्य,SCB_NO_PARENT);

	वापस scb;
पूर्ण


काष्ठा dsp_scb_descriptor * 
cs46xx_dsp_create_codec_out_scb(काष्ठा snd_cs46xx * chip, अक्षर * codec_name,
                                u16 channel_disp, u16 fअगरo_addr, u16 child_scb_addr,
                                u32 dest, काष्ठा dsp_scb_descriptor * parent_scb,
                                पूर्णांक scb_child_type)
अणु
	काष्ठा dsp_scb_descriptor * scb;
  
	काष्ठा dsp_codec_output_scb codec_out_scb = अणु
		अणु 0,
		  0,
		  0,
		  0
		पूर्ण,
		अणु
			0,
			0,
			0,
			0,
			0
		पूर्ण,
		0,0,
		0,शून्य_SCB_ADDR,
		0,                      /* COstrmRsConfig */
		0,                      /* COstrmBufPtr */
		channel_disp,fअगरo_addr, /* leftChanBaseIOaddr:rightChanIOdisp */
		0x0000,0x0080,          /* (!AC97!) COexpVolChangeRate:COscaleShअगरtCount */
		0,child_scb_addr        /* COreserved - need child scb to work with rom code */
	पूर्ण;
  
  
	scb = cs46xx_dsp_create_generic_scb(chip,codec_name,(u32 *)&codec_out_scb,
					    dest,"S16_CODECOUTPUTTASK",parent_scb,
					    scb_child_type);
  
	वापस scb;
पूर्ण

काष्ठा dsp_scb_descriptor * 
cs46xx_dsp_create_codec_in_scb(काष्ठा snd_cs46xx * chip, अक्षर * codec_name,
			       u16 channel_disp, u16 fअगरo_addr, u16 sample_buffer_addr,
			       u32 dest, काष्ठा dsp_scb_descriptor * parent_scb,
			       पूर्णांक scb_child_type)
अणु

	काष्ठा dsp_scb_descriptor * scb;
	काष्ठा dsp_codec_input_scb codec_input_scb = अणु
		अणु 0,
		  0,
		  0,
		  0
		पूर्ण,
		अणु
			0,
			0,
			0,
			0,
			0
		पूर्ण,
    
#अगर 0  /* cs4620 */
		SyncIOSCB,शून्य_SCB_ADDR
#अन्यथा
		0 , 0,
#पूर्ण_अगर
		0,0,

		RSCONFIG_SAMPLE_16STEREO + RSCONFIG_MODULO_64,  /* strmRsConfig */
		sample_buffer_addr << 0x10,       /* strmBufPtr; defined as a dword ptr, used as a byte ptr */
		channel_disp,fअगरo_addr,           /* (!AC97!) leftChanBaseINaddr=AC97primary 
						     link input slot 3 :rightChanINdisp=""slot 4 */
		0x0000,0x0000,                    /* (!AC97!) ????:scaleShअगरtCount; no shअगरt needed 
						     because AC97 is alपढ़ोy 20 bits */
		0x80008000                        /* ??clw cwcgame.scb has 0 */
	पूर्ण;
  
	scb = cs46xx_dsp_create_generic_scb(chip,codec_name,(u32 *)&codec_input_scb,
					    dest,"S16_CODECINPUTTASK",parent_scb,
					    scb_child_type);
	वापस scb;
पूर्ण


अटल काष्ठा dsp_scb_descriptor * 
cs46xx_dsp_create_pcm_पढ़ोer_scb(काष्ठा snd_cs46xx * chip, अक्षर * scb_name,
                                 u16 sample_buffer_addr, u32 dest,
                                 पूर्णांक भव_channel, u32 playback_hw_addr,
                                 काष्ठा dsp_scb_descriptor * parent_scb,
                                 पूर्णांक scb_child_type)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	काष्ठा dsp_scb_descriptor * scb;
  
	काष्ठा dsp_generic_scb pcm_पढ़ोer_scb = अणु
    
		/*
		  Play DMA Task xfers data from host buffer to SP buffer
		  init/runसमय variables:
		  PlayAC: Play Audio Data Conversion - SCB loc: 2nd dword, mask: 0x0000F000L
		  DATA_FMT_16BIT_ST_LTLEND(0x00000000L)   from 16-bit stereo, little-endian
		  DATA_FMT_8_BIT_ST_SIGNED(0x00001000L)   from 8-bit stereo, चिन्हित
		  DATA_FMT_16BIT_MN_LTLEND(0x00002000L)   from 16-bit mono, little-endian
		  DATA_FMT_8_BIT_MN_SIGNED(0x00003000L)   from 8-bit mono, चिन्हित
		  DATA_FMT_16BIT_ST_BIGEND(0x00004000L)   from 16-bit stereo, big-endian
		  DATA_FMT_16BIT_MN_BIGEND(0x00006000L)   from 16-bit mono, big-endian
		  DATA_FMT_8_BIT_ST_UNSIGNED(0x00009000L) from 8-bit stereo, अचिन्हित
		  DATA_FMT_8_BIT_MN_UNSIGNED(0x0000b000L) from 8-bit mono, अचिन्हित
		  ? Other combinations possible from:
		  DMA_RQ_C2_AUDIO_CONVERT_MASK    0x0000F000L
		  DMA_RQ_C2_AC_NONE               0x00000000L
		  DMA_RQ_C2_AC_8_TO_16_BIT        0x00001000L
		  DMA_RQ_C2_AC_MONO_TO_STEREO     0x00002000L
		  DMA_RQ_C2_AC_ENDIAN_CONVERT     0x00004000L
		  DMA_RQ_C2_AC_SIGNED_CONVERT     0x00008000L
        
		  HostBuffAddr: Host Buffer Physical Byte Address - SCB loc:3rd dword, Mask: 0xFFFFFFFFL
		  aligned to dword boundary
		*/
		/* Basic (non scatter/gather) DMA requestor (4 पूर्णांकs) */
		अणु DMA_RQ_C1_SOURCE_ON_HOST +        /* source buffer is on the host */
		  DMA_RQ_C1_SOURCE_MOD1024 +        /* source buffer is 1024 dwords (4096 bytes) */
		  DMA_RQ_C1_DEST_MOD32 +            /* dest buffer(PCMपढ़ोerBuf) is 32 dwords*/
		  DMA_RQ_C1_WRITEBACK_SRC_FLAG +    /* ?? */
		  DMA_RQ_C1_WRITEBACK_DEST_FLAG +   /* ?? */
		  15,                             /* DwordCount-1: picked 16 क्रम DwordCount because Jim */
		  /*        Barnette said that is what we should use since */
		  /*        we are not running in optimized mode? */
		  DMA_RQ_C2_AC_NONE +
		  DMA_RQ_C2_SIGNAL_SOURCE_PINGPONG + /* set play पूर्णांकerrupt (bit0) in HISR when source */
		  /*   buffer (on host) crosses half-way poपूर्णांक */
		  भव_channel,                   /* Play DMA channel arbitrarily set to 0 */
		  playback_hw_addr,                  /* HostBuffAddr (source) */
		  DMA_RQ_SD_SP_SAMPLE_ADDR +         /* destination buffer is in SP Sample Memory */
		  sample_buffer_addr                 /* SP Buffer Address (destination) */
		पूर्ण,
		/* Scatter/gather DMA requestor extension   (5 पूर्णांकs) */
		अणु
			0,
			0,
			0,
			0,
			0 
		पूर्ण,
		/* Sublist poपूर्णांकer & next stream control block (SCB) link. */
		शून्य_SCB_ADDR,शून्य_SCB_ADDR,
		/* Poपूर्णांकer to this tasks parameter block & stream function poपूर्णांकer */
		0,शून्य_SCB_ADDR,
		/* rsConfig रेजिस्टर क्रम stream buffer (rsDMA reg. is loaded from basicReq.daw */
		/*   क्रम incoming streams, or basicReq.saw, क्रम outgoing streams) */
		RSCONFIG_DMA_ENABLE +                 /* enable DMA */
		(19 << RSCONFIG_MAX_DMA_SIZE_SHIFT) + /* MAX_DMA_SIZE picked to be 19 since SPUD  */
		/*  uses it क्रम some reason */
		((dest >> 4) << RSCONFIG_STREAM_NUM_SHIFT) + /* stream number = SCBaddr/16 */
		RSCONFIG_SAMPLE_16STEREO +
		RSCONFIG_MODULO_32,             /* dest buffer(PCMपढ़ोerBuf) is 32 dwords (256 bytes) */
		/* Stream sample poपूर्णांकer & MAC-unit mode क्रम this stream */
		(sample_buffer_addr << 0x10),
		/* Fractional increment per output sample in the input sample buffer */
		0, 
		अणु
			/* Standard stereo volume control
			   शेष muted */
			0xffff,0xffff,
			0xffff,0xffff
		पूर्ण
	पूर्ण;

	अगर (ins->null_algorithm == शून्य) अणु
		ins->null_algorithm =  cs46xx_dsp_lookup_symbol (chip,"NULLALGORITHM",
								 SYMBOL_CODE);
    
		अगर (ins->null_algorithm == शून्य) अणु
			dev_err(chip->card->dev,
				"dsp_spos: symbol NULLALGORITHM not found\n");
			वापस शून्य;
		पूर्ण    
	पूर्ण

	scb = _dsp_create_generic_scb(chip,scb_name,(u32 *)&pcm_पढ़ोer_scb,
				      dest,ins->null_algorithm,parent_scb,
				      scb_child_type);
  
	वापस scb;
पूर्ण

#घोषणा GOF_PER_SEC 200

काष्ठा dsp_scb_descriptor * 
cs46xx_dsp_create_src_task_scb(काष्ठा snd_cs46xx * chip, अक्षर * scb_name,
			       पूर्णांक rate,
                               u16 src_buffer_addr,
                               u16 src_delay_buffer_addr, u32 dest,
                               काष्ठा dsp_scb_descriptor * parent_scb,
                               पूर्णांक scb_child_type,
	                       पूर्णांक pass_through)
अणु

	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	काष्ठा dsp_scb_descriptor * scb;
	अचिन्हित पूर्णांक पंचांगp1, पंचांगp2;
	अचिन्हित पूर्णांक phiIncr;
	अचिन्हित पूर्णांक correctionPerGOF, correctionPerSec;

	dev_dbg(chip->card->dev, "dsp_spos: setting %s rate to %u\n",
		scb_name, rate);

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

	अणु
		काष्ठा dsp_src_task_scb src_task_scb = अणु
			0x0028,0x00c8,
			0x5555,0x0000,
			0x0000,0x0000,
			src_buffer_addr,1,
			correctionPerGOF,correctionPerSec,
			RSCONFIG_SAMPLE_16STEREO + RSCONFIG_MODULO_32,  
			0x0000,src_delay_buffer_addr,                  
			0x0,                                            
			0x080,(src_delay_buffer_addr + (24 * 4)),
			0,0, /* next_scb, sub_list_ptr */
			0,0, /* entry, this_spb */
			RSCONFIG_SAMPLE_16STEREO + RSCONFIG_MODULO_8,
			src_buffer_addr << 0x10,
			phiIncr,
			अणु 
				0xffff - ins->dac_volume_right,0xffff - ins->dac_volume_left,
				0xffff - ins->dac_volume_right,0xffff - ins->dac_volume_left
			पूर्ण
		पूर्ण;
		
		अगर (ins->s16_up == शून्य) अणु
			ins->s16_up =  cs46xx_dsp_lookup_symbol (chip,"S16_UPSRC",
								 SYMBOL_CODE);
			
			अगर (ins->s16_up == शून्य) अणु
				dev_err(chip->card->dev,
					"dsp_spos: symbol S16_UPSRC not found\n");
				वापस शून्य;
			पूर्ण    
		पूर्ण
		
		/* clear buffers */
		_dsp_clear_sample_buffer (chip,src_buffer_addr,8);
		_dsp_clear_sample_buffer (chip,src_delay_buffer_addr,32);
				
		अगर (pass_through) अणु
			/* wont work with any other rate than
			   the native DSP rate */
			snd_BUG_ON(rate != 48000);

			scb = cs46xx_dsp_create_generic_scb(chip,scb_name,(u32 *)&src_task_scb,
							    dest,"DMAREADER",parent_scb,
							    scb_child_type);
		पूर्ण अन्यथा अणु
			scb = _dsp_create_generic_scb(chip,scb_name,(u32 *)&src_task_scb,
						      dest,ins->s16_up,parent_scb,
						      scb_child_type);
		पूर्ण


	पूर्ण

	वापस scb;
पूर्ण

#अगर 0 /* not used */
काष्ठा dsp_scb_descriptor * 
cs46xx_dsp_create_filter_scb(काष्ठा snd_cs46xx * chip, अक्षर * scb_name,
			     u16 buffer_addr, u32 dest,
			     काष्ठा dsp_scb_descriptor * parent_scb,
			     पूर्णांक scb_child_type) अणु
	काष्ठा dsp_scb_descriptor * scb;
	
	काष्ठा dsp_filter_scb filter_scb = अणु
		.a0_right            = 0x41a9,
		.a0_left             = 0x41a9,
		.a1_right            = 0xb8e4,
		.a1_left             = 0xb8e4,
		.a2_right            = 0x3e55,
		.a2_left             = 0x3e55,
		
		.filter_unused3      = 0x0000,
		.filter_unused2      = 0x0000,

		.output_buf_ptr      = buffer_addr,
		.init                = 0x000,

		.prev_sample_output1 = 0x00000000,
		.prev_sample_output2 = 0x00000000,

		.prev_sample_input1  = 0x00000000,
		.prev_sample_input2  = 0x00000000,

		.next_scb_ptr        = 0x0000,
		.sub_list_ptr        = 0x0000,

		.entry_poपूर्णांक         = 0x0000,
		.spb_ptr             = 0x0000,

		.b0_right            = 0x0e38,
		.b0_left             = 0x0e38,
		.b1_right            = 0x1c71,
		.b1_left             = 0x1c71,
		.b2_right            = 0x0e38,
		.b2_left             = 0x0e38,
	पूर्ण;


	scb = cs46xx_dsp_create_generic_scb(chip,scb_name,(u32 *)&filter_scb,
					    dest,"FILTERTASK",parent_scb,
					    scb_child_type);

 	वापस scb;
पूर्ण
#पूर्ण_अगर /* not used */

काष्ठा dsp_scb_descriptor * 
cs46xx_dsp_create_mix_only_scb(काष्ठा snd_cs46xx * chip, अक्षर * scb_name,
                               u16 mix_buffer_addr, u32 dest,
                               काष्ठा dsp_scb_descriptor * parent_scb,
                               पूर्णांक scb_child_type)
अणु
	काष्ठा dsp_scb_descriptor * scb;
  
	काष्ठा dsp_mix_only_scb master_mix_scb = अणु
		/* 0 */ अणु 0,
			  /* 1 */   0,
			  /* 2 */  mix_buffer_addr,
			  /* 3 */  0
			  /*   */ पूर्ण,
		अणु
			/* 4 */  0,
			/* 5 */  0,
			/* 6 */  0,
			/* 7 */  0,
			/* 8 */  0x00000080
		पूर्ण,
		/* 9 */ 0,0,
		/* A */ 0,0,
		/* B */ RSCONFIG_SAMPLE_16STEREO + RSCONFIG_MODULO_32,
		/* C */ (mix_buffer_addr  + (16 * 4)) << 0x10, 
		/* D */ 0,
		अणु
			/* E */ 0x8000,0x8000,
			/* F */ 0x8000,0x8000
		पूर्ण
	पूर्ण;


	scb = cs46xx_dsp_create_generic_scb(chip,scb_name,(u32 *)&master_mix_scb,
					    dest,"S16_MIX",parent_scb,
					    scb_child_type);
	वापस scb;
पूर्ण


काष्ठा dsp_scb_descriptor * 
cs46xx_dsp_create_mix_to_ostream_scb(काष्ठा snd_cs46xx * chip, अक्षर * scb_name,
                                     u16 mix_buffer_addr, u16 ग_लिखोback_spb, u32 dest,
                                     काष्ठा dsp_scb_descriptor * parent_scb,
                                     पूर्णांक scb_child_type)
अणु
	काष्ठा dsp_scb_descriptor * scb;

	काष्ठा dsp_mix2_ostream_scb mix2_ostream_scb = अणु
		/* Basic (non scatter/gather) DMA requestor (4 पूर्णांकs) */
		अणु 
			DMA_RQ_C1_SOURCE_MOD64 +
			DMA_RQ_C1_DEST_ON_HOST +
			DMA_RQ_C1_DEST_MOD1024 +
			DMA_RQ_C1_WRITEBACK_SRC_FLAG + 
			DMA_RQ_C1_WRITEBACK_DEST_FLAG +
			15,                            
      
			DMA_RQ_C2_AC_NONE +
			DMA_RQ_C2_SIGNAL_DEST_PINGPONG + 
      
			CS46XX_DSP_CAPTURE_CHANNEL,                                 
			DMA_RQ_SD_SP_SAMPLE_ADDR + 
			mix_buffer_addr, 
			0x0                   
		पूर्ण,
    
		अणु 0, 0, 0, 0, 0, पूर्ण,
		0,0,
		0,ग_लिखोback_spb,
    
		RSCONFIG_DMA_ENABLE + 
		(19 << RSCONFIG_MAX_DMA_SIZE_SHIFT) + 
    
		((dest >> 4) << RSCONFIG_STREAM_NUM_SHIFT) +
		RSCONFIG_DMA_TO_HOST + 
		RSCONFIG_SAMPLE_16STEREO +
		RSCONFIG_MODULO_64,    
		(mix_buffer_addr + (32 * 4)) << 0x10,
		1,0,            
		0x0001,0x0080,
		0xFFFF,0
	पूर्ण;


	scb = cs46xx_dsp_create_generic_scb(chip,scb_name,(u32 *)&mix2_ostream_scb,
				
	    dest,"S16_MIX_TO_OSTREAM",parent_scb,
					    scb_child_type);
  
	वापस scb;
पूर्ण


काष्ठा dsp_scb_descriptor * 
cs46xx_dsp_create_vari_decimate_scb(काष्ठा snd_cs46xx * chip,अक्षर * scb_name,
                                    u16 vari_buffer_addr0,
                                    u16 vari_buffer_addr1,
                                    u32 dest,
                                    काष्ठा dsp_scb_descriptor * parent_scb,
                                    पूर्णांक scb_child_type)
अणु

	काष्ठा dsp_scb_descriptor * scb;
  
	काष्ठा dsp_vari_decimate_scb vari_decimate_scb = अणु
		0x0028,0x00c8,
		0x5555,0x0000,
		0x0000,0x0000,
		vari_buffer_addr0,vari_buffer_addr1,
    
		0x0028,0x00c8,
		RSCONFIG_SAMPLE_16STEREO + RSCONFIG_MODULO_256, 
    
		0xFF800000,   
		0,
		0x0080,vari_buffer_addr1 + (25 * 4), 
    
		0,0, 
		0,0,

		RSCONFIG_SAMPLE_16STEREO + RSCONFIG_MODULO_8,
		vari_buffer_addr0 << 0x10,   
		0x04000000,                   
		अणु
			0x8000,0x8000, 
			0xFFFF,0xFFFF
		पूर्ण
	पूर्ण;

	scb = cs46xx_dsp_create_generic_scb(chip,scb_name,(u32 *)&vari_decimate_scb,
					    dest,"VARIDECIMATE",parent_scb,
					    scb_child_type);
  
	वापस scb;
पूर्ण


अटल काष्ठा dsp_scb_descriptor * 
cs46xx_dsp_create_pcm_serial_input_scb(काष्ठा snd_cs46xx * chip, अक्षर * scb_name, u32 dest,
                                       काष्ठा dsp_scb_descriptor * input_scb,
                                       काष्ठा dsp_scb_descriptor * parent_scb,
                                       पूर्णांक scb_child_type)
अणु

	काष्ठा dsp_scb_descriptor * scb;


	काष्ठा dsp_pcm_serial_input_scb pcm_serial_input_scb = अणु
		अणु 0,
		  0,
		  0,
		  0
		पूर्ण,
		अणु
			0,
			0,
			0,
			0,
			0
		पूर्ण,

		0,0,
		0,0,

		RSCONFIG_SAMPLE_16STEREO + RSCONFIG_MODULO_16,
		0,
      /* 0xD */ 0,input_scb->address,
		अणु
      /* 0xE */   0x8000,0x8000,
      /* 0xF */	  0x8000,0x8000
		पूर्ण
	पूर्ण;

	scb = cs46xx_dsp_create_generic_scb(chip,scb_name,(u32 *)&pcm_serial_input_scb,
					    dest,"PCMSERIALINPUTTASK",parent_scb,
					    scb_child_type);
	वापस scb;
पूर्ण


अटल काष्ठा dsp_scb_descriptor * 
cs46xx_dsp_create_asynch_fg_tx_scb(काष्ठा snd_cs46xx * chip, अक्षर * scb_name, u32 dest,
                                   u16 hfg_scb_address,
                                   u16 asynch_buffer_address,
                                   काष्ठा dsp_scb_descriptor * parent_scb,
                                   पूर्णांक scb_child_type)
अणु

	काष्ठा dsp_scb_descriptor * scb;

	काष्ठा dsp_asynch_fg_tx_scb asynch_fg_tx_scb = अणु
		0xfc00,0x03ff,      /*  Prototype sample buffer size of 256 dwords */
		0x0058,0x0028,      /* Min Delta 7 dwords == 28 bytes */
		/* : Max delta 25 dwords == 100 bytes */
		0,hfg_scb_address,  /* Poपूर्णांक to HFG task SCB */
		0,0,		    /* Initialize current Delta and Consumer ptr adjusपंचांगent count */
		0,                  /* Initialize accumulated Phi to 0 */
		0,0x2aab,           /* Const 1/3 */
    
		अणु
			0,         /* Define the unused elements */
			0,
			0
		पूर्ण,
    
		0,0,
		0,dest + AFGTxAccumPhi,
    
		RSCONFIG_SAMPLE_16STEREO + RSCONFIG_MODULO_256, /* Stereo, 256 dword */
		(asynch_buffer_address) << 0x10,  /* This should be स्वतःmagically synchronized
                                                     to the producer poपूर्णांकer */
    
		/* There is no correct initial value, it will depend upon the detected
		   rate etc  */
		0x18000000,                     /* Phi increment क्रम approx 32k operation */
		0x8000,0x8000,                  /* Volume controls are unused at this समय */
		0x8000,0x8000
	पूर्ण;
  
	scb = cs46xx_dsp_create_generic_scb(chip,scb_name,(u32 *)&asynch_fg_tx_scb,
					    dest,"ASYNCHFGTXCODE",parent_scb,
					    scb_child_type);

	वापस scb;
पूर्ण


काष्ठा dsp_scb_descriptor * 
cs46xx_dsp_create_asynch_fg_rx_scb(काष्ठा snd_cs46xx * chip, अक्षर * scb_name, u32 dest,
                                   u16 hfg_scb_address,
                                   u16 asynch_buffer_address,
                                   काष्ठा dsp_scb_descriptor * parent_scb,
                                   पूर्णांक scb_child_type)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	काष्ठा dsp_scb_descriptor * scb;

	काष्ठा dsp_asynch_fg_rx_scb asynch_fg_rx_scb = अणु
		0xfe00,0x01ff,      /*  Prototype sample buffer size of 128 dwords */
		0x0064,0x001c,      /* Min Delta 7 dwords == 28 bytes */
		                    /* : Max delta 25 dwords == 100 bytes */
		0,hfg_scb_address,  /* Poपूर्णांक to HFG task SCB */
		0,0,				/* Initialize current Delta and Consumer ptr adjusपंचांगent count */
		अणु
			0,                /* Define the unused elements */
			0,
			0,
			0,
			0
		पूर्ण,
      
		0,0,
		0,dest,
    
		RSCONFIG_MODULO_128 |
        RSCONFIG_SAMPLE_16STEREO,                         /* Stereo, 128 dword */
		( (asynch_buffer_address + (16 * 4))  << 0x10),   /* This should be स्वतःmagically 
							                                  synchrinized to the producer poपूर्णांकer */
    
		/* There is no correct initial value, it will depend upon the detected
		   rate etc  */
		0x18000000,         

		/* Set IEC958 input volume */
		0xffff - ins->spdअगर_input_volume_right,0xffff - ins->spdअगर_input_volume_left,
		0xffff - ins->spdअगर_input_volume_right,0xffff - ins->spdअगर_input_volume_left,
	पूर्ण;

	scb = cs46xx_dsp_create_generic_scb(chip,scb_name,(u32 *)&asynch_fg_rx_scb,
					    dest,"ASYNCHFGRXCODE",parent_scb,
					    scb_child_type);

	वापस scb;
पूर्ण


#अगर 0 /* not used */
काष्ठा dsp_scb_descriptor * 
cs46xx_dsp_create_output_snoop_scb(काष्ठा snd_cs46xx * chip, अक्षर * scb_name, u32 dest,
                                   u16 snoop_buffer_address,
                                   काष्ठा dsp_scb_descriptor * snoop_scb,
                                   काष्ठा dsp_scb_descriptor * parent_scb,
                                   पूर्णांक scb_child_type)
अणु

	काष्ठा dsp_scb_descriptor * scb;
  
	काष्ठा dsp_output_snoop_scb output_snoop_scb = अणु
		अणु 0,	/*  not used.  Zero */
		  0,
		  0,
		  0,
		पूर्ण,
		अणु
			0, /* not used.  Zero */
			0,
			0,
			0,
			0
		पूर्ण,
    
		0,0,
		0,0,
    
		RSCONFIG_SAMPLE_16STEREO + RSCONFIG_MODULO_64,
		snoop_buffer_address << 0x10,  
		0,0,
		0,
		0,snoop_scb->address
	पूर्ण;
  
	scb = cs46xx_dsp_create_generic_scb(chip,scb_name,(u32 *)&output_snoop_scb,
					    dest,"OUTPUTSNOOP",parent_scb,
					    scb_child_type);
	वापस scb;
पूर्ण
#पूर्ण_अगर /* not used */


काष्ठा dsp_scb_descriptor * 
cs46xx_dsp_create_spio_ग_लिखो_scb(काष्ठा snd_cs46xx * chip, अक्षर * scb_name, u32 dest,
                                 काष्ठा dsp_scb_descriptor * parent_scb,
                                 पूर्णांक scb_child_type)
अणु
	काष्ठा dsp_scb_descriptor * scb;
  
	काष्ठा dsp_spio_ग_लिखो_scb spio_ग_लिखो_scb = अणु
		0,0,         /*   SPIOWAddress2:SPIOWAddress1; */
		0,           /*   SPIOWData1; */
		0,           /*   SPIOWData2; */
		0,0,         /*   SPIOWAddress4:SPIOWAddress3; */
		0,           /*   SPIOWData3; */
		0,           /*   SPIOWData4; */
		0,0,         /*   SPIOWDataPtr:Unused1; */
		अणु 0,0 पूर्ण,     /*   Unused2[2]; */
    
		0,0,	     /*   SPIOWChildPtr:SPIOWSiblingPtr; */
		0,0,         /*   SPIOWThisPtr:SPIOWEntryPoपूर्णांक; */
    
		अणु 
			0,
			0,
			0,
			0,
			0          /*   Unused3[5];  */
		पूर्ण
	पूर्ण;

	scb = cs46xx_dsp_create_generic_scb(chip,scb_name,(u32 *)&spio_ग_लिखो_scb,
					    dest,"SPIOWRITE",parent_scb,
					    scb_child_type);

	वापस scb;
पूर्ण

काष्ठा dsp_scb_descriptor *
cs46xx_dsp_create_magic_snoop_scb(काष्ठा snd_cs46xx * chip, अक्षर * scb_name, u32 dest,
				  u16 snoop_buffer_address,
				  काष्ठा dsp_scb_descriptor * snoop_scb,
				  काष्ठा dsp_scb_descriptor * parent_scb,
				  पूर्णांक scb_child_type)
अणु
	काष्ठा dsp_scb_descriptor * scb;
  
	काष्ठा dsp_magic_snoop_task magic_snoop_scb = अणु
		/* 0 */ 0, /* i0 */
		/* 1 */ 0, /* i1 */
		/* 2 */ snoop_buffer_address << 0x10,
		/* 3 */ 0,snoop_scb->address,
		/* 4 */ 0, /* i3 */
		/* 5 */ 0, /* i4 */
		/* 6 */ 0, /* i5 */
		/* 7 */ 0, /* i6 */
		/* 8 */ 0, /* i7 */
		/* 9 */ 0,0, /* next_scb, sub_list_ptr */
		/* A */ 0,0, /* entry_poपूर्णांक, this_ptr */
		/* B */ RSCONFIG_SAMPLE_16STEREO + RSCONFIG_MODULO_64,
		/* C */ snoop_buffer_address  << 0x10,
		/* D */ 0,
		/* E */ अणु 0x8000,0x8000,
	        /* F */   0xffff,0xffff
		पूर्ण
	पूर्ण;

	scb = cs46xx_dsp_create_generic_scb(chip,scb_name,(u32 *)&magic_snoop_scb,
					    dest,"MAGICSNOOPTASK",parent_scb,
					    scb_child_type);

	वापस scb;
पूर्ण

अटल काष्ठा dsp_scb_descriptor *
find_next_मुक्त_scb (काष्ठा snd_cs46xx * chip, काष्ठा dsp_scb_descriptor * from)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	काष्ठा dsp_scb_descriptor * scb = from;

	जबतक (scb->next_scb_ptr != ins->the_null_scb) अणु
		अगर (snd_BUG_ON(!scb->next_scb_ptr))
			वापस शून्य;

		scb = scb->next_scb_ptr;
	पूर्ण

	वापस scb;
पूर्ण

अटल स्थिर u32 pcm_पढ़ोer_buffer_addr[DSP_MAX_PCM_CHANNELS] = अणु
	0x0600, /* 1 */
	0x1500, /* 2 */
	0x1580, /* 3 */
	0x1600, /* 4 */
	0x1680, /* 5 */
	0x1700, /* 6 */
	0x1780, /* 7 */
	0x1800, /* 8 */
	0x1880, /* 9 */
	0x1900, /* 10 */
	0x1980, /* 11 */
	0x1A00, /* 12 */
	0x1A80, /* 13 */
	0x1B00, /* 14 */
	0x1B80, /* 15 */
	0x1C00, /* 16 */
	0x1C80, /* 17 */
	0x1D00, /* 18 */
	0x1D80, /* 19 */
	0x1E00, /* 20 */
	0x1E80, /* 21 */
	0x1F00, /* 22 */
	0x1F80, /* 23 */
	0x2000, /* 24 */
	0x2080, /* 25 */
	0x2100, /* 26 */
	0x2180, /* 27 */
	0x2200, /* 28 */
	0x2280, /* 29 */
	0x2300, /* 30 */
	0x2380, /* 31 */
	0x2400, /* 32 */
पूर्ण;

अटल स्थिर u32 src_output_buffer_addr[DSP_MAX_SRC_NR] = अणु
	0x2B80,
	0x2BA0,
	0x2BC0,
	0x2BE0,
	0x2D00,  
	0x2D20,  
	0x2D40,  
	0x2D60,
	0x2D80,
	0x2DA0,
	0x2DC0,
	0x2DE0,
	0x2E00,
	0x2E20
पूर्ण;

अटल स्थिर u32 src_delay_buffer_addr[DSP_MAX_SRC_NR] = अणु
	0x2480,
	0x2500,
	0x2580,
	0x2600,
	0x2680,
	0x2700,
	0x2780,
	0x2800,
	0x2880,
	0x2900,
	0x2980,
	0x2A00,
	0x2A80,
	0x2B00
पूर्ण;

काष्ठा dsp_pcm_channel_descriptor *
cs46xx_dsp_create_pcm_channel (काष्ठा snd_cs46xx * chip,
			       u32 sample_rate, व्योम * निजी_data, 
			       u32 hw_dma_addr,
			       पूर्णांक pcm_channel_id)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	काष्ठा dsp_scb_descriptor * src_scb = शून्य, * pcm_scb, * mixer_scb = शून्य;
	काष्ठा dsp_scb_descriptor * src_parent_scb = शून्य;

	/* काष्ठा dsp_scb_descriptor * pcm_parent_scb; */
	अक्षर scb_name[DSP_MAX_SCB_NAME];
	पूर्णांक i, pcm_index = -1, insert_poपूर्णांक, src_index = -1, pass_through = 0;
	अचिन्हित दीर्घ flags;

	चयन (pcm_channel_id) अणु
	हाल DSP_PCM_MAIN_CHANNEL:
		mixer_scb = ins->master_mix_scb;
		अवरोध;
	हाल DSP_PCM_REAR_CHANNEL:
		mixer_scb = ins->rear_mix_scb;
		अवरोध;
	हाल DSP_PCM_CENTER_LFE_CHANNEL:
		mixer_scb = ins->center_lfe_mix_scb;
		अवरोध;
	हाल DSP_PCM_S71_CHANNEL:
		/* TODO */
		snd_BUG();
		अवरोध;
	हाल DSP_IEC958_CHANNEL:
		अगर (snd_BUG_ON(!ins->asynch_tx_scb))
			वापस शून्य;
		mixer_scb = ins->asynch_tx_scb;

		/* अगर sample rate is set to 48khz we pass
		   the Sample Rate Converted (which could
		   alter the raw data stream ...) */
		अगर (sample_rate == 48000) अणु
			dev_dbg(chip->card->dev, "IEC958 pass through\n");
			/* Hack to bypass creating a new SRC */
			pass_through = 1;
		पूर्ण
		अवरोध;
	शेष:
		snd_BUG();
		वापस शून्य;
	पूर्ण
	/* शेष sample rate is 44100 */
	अगर (!sample_rate) sample_rate = 44100;

	/* search क्रम a alपढ़ोy created SRC SCB with the same sample rate */
	क्रम (i = 0; i < DSP_MAX_PCM_CHANNELS && 
		     (pcm_index == -1 || src_scb == शून्य); ++i) अणु

		/* भव channel reserved 
		   क्रम capture */
		अगर (i == CS46XX_DSP_CAPTURE_CHANNEL) जारी;

		अगर (ins->pcm_channels[i].active) अणु
			अगर (!src_scb && 
			    ins->pcm_channels[i].sample_rate == sample_rate &&
			    ins->pcm_channels[i].mixer_scb == mixer_scb) अणु
				src_scb = ins->pcm_channels[i].src_scb;
				ins->pcm_channels[i].src_scb->ref_count ++;
				src_index = ins->pcm_channels[i].src_slot;
			पूर्ण
		पूर्ण अन्यथा अगर (pcm_index == -1) अणु
			pcm_index = i;
		पूर्ण
	पूर्ण

	अगर (pcm_index == -1) अणु
		dev_err(chip->card->dev, "dsp_spos: no free PCM channel\n");
		वापस शून्य;
	पूर्ण

	अगर (src_scb == शून्य) अणु
		अगर (ins->nsrc_scb >= DSP_MAX_SRC_NR) अणु
			dev_err(chip->card->dev,
				"dsp_spos: too many SRC instances\n!");
			वापस शून्य;
		पूर्ण

		/* find a मुक्त slot */
		क्रम (i = 0; i < DSP_MAX_SRC_NR; ++i) अणु
			अगर (ins->src_scb_slots[i] == 0) अणु
				src_index = i;
				ins->src_scb_slots[i] = 1;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (snd_BUG_ON(src_index == -1))
			वापस शून्य;

		/* we need to create a new SRC SCB */
		अगर (mixer_scb->sub_list_ptr == ins->the_null_scb) अणु
			src_parent_scb = mixer_scb;
			insert_poपूर्णांक = SCB_ON_PARENT_SUBLIST_SCB;
		पूर्ण अन्यथा अणु
			src_parent_scb = find_next_मुक्त_scb(chip,mixer_scb->sub_list_ptr);
			insert_poपूर्णांक = SCB_ON_PARENT_NEXT_SCB;
		पूर्ण

		snम_लिखो (scb_name,DSP_MAX_SCB_NAME,"SrcTask_SCB%d",src_index);
		
		dev_dbg(chip->card->dev,
			"dsp_spos: creating SRC \"%s\"\n", scb_name);
		src_scb = cs46xx_dsp_create_src_task_scb(chip,scb_name,
							 sample_rate,
							 src_output_buffer_addr[src_index],
							 src_delay_buffer_addr[src_index],
							 /* 0x400 - 0x600 source SCBs */
							 0x400 + (src_index * 0x10) ,
							 src_parent_scb,
							 insert_poपूर्णांक,
							 pass_through);

		अगर (!src_scb) अणु
			dev_err(chip->card->dev,
				"dsp_spos: failed to create SRCtaskSCB\n");
			वापस शून्य;
		पूर्ण

		/* cs46xx_dsp_set_src_sample_rate(chip,src_scb,sample_rate); */

		ins->nsrc_scb ++;
	पूर्ण 
  
  
	snम_लिखो (scb_name,DSP_MAX_SCB_NAME,"PCMReader_SCB%d",pcm_index);

	dev_dbg(chip->card->dev, "dsp_spos: creating PCM \"%s\" (%d)\n",
		scb_name, pcm_channel_id);

	pcm_scb = cs46xx_dsp_create_pcm_पढ़ोer_scb(chip,scb_name,
						   pcm_पढ़ोer_buffer_addr[pcm_index],
						   /* 0x200 - 400 PCMपढ़ोer SCBs */
						   (pcm_index * 0x10) + 0x200,
						   pcm_index,    /* भव channel 0-31 */
						   hw_dma_addr,  /* pcm hw addr */
                           शून्य,         /* parent SCB ptr */
                           0             /* insert poपूर्णांक */ 
                           );

	अगर (!pcm_scb) अणु
		dev_err(chip->card->dev,
			"dsp_spos: failed to create PCMreaderSCB\n");
		वापस शून्य;
	पूर्ण
	
	spin_lock_irqsave(&chip->reg_lock, flags);
	ins->pcm_channels[pcm_index].sample_rate = sample_rate;
	ins->pcm_channels[pcm_index].pcm_पढ़ोer_scb = pcm_scb;
	ins->pcm_channels[pcm_index].src_scb = src_scb;
	ins->pcm_channels[pcm_index].unlinked = 1;
	ins->pcm_channels[pcm_index].निजी_data = निजी_data;
	ins->pcm_channels[pcm_index].src_slot = src_index;
	ins->pcm_channels[pcm_index].active = 1;
	ins->pcm_channels[pcm_index].pcm_slot = pcm_index;
	ins->pcm_channels[pcm_index].mixer_scb = mixer_scb;
	ins->npcm_channels ++;
	spin_unlock_irqrestore(&chip->reg_lock, flags);

	वापस (ins->pcm_channels + pcm_index);
पूर्ण

पूर्णांक cs46xx_dsp_pcm_channel_set_period (काष्ठा snd_cs46xx * chip,
				       काष्ठा dsp_pcm_channel_descriptor * pcm_channel,
				       पूर्णांक period_size)
अणु
	u32 temp = snd_cs46xx_peek (chip,pcm_channel->pcm_पढ़ोer_scb->address << 2);
	temp &= ~DMA_RQ_C1_SOURCE_SIZE_MASK;

	चयन (period_size) अणु
	हाल 2048:
		temp |= DMA_RQ_C1_SOURCE_MOD1024;
		अवरोध;
	हाल 1024:
		temp |= DMA_RQ_C1_SOURCE_MOD512;
		अवरोध;
	हाल 512:
		temp |= DMA_RQ_C1_SOURCE_MOD256;
		अवरोध;
	हाल 256:
		temp |= DMA_RQ_C1_SOURCE_MOD128;
		अवरोध;
	हाल 128:
		temp |= DMA_RQ_C1_SOURCE_MOD64;
		अवरोध;
	हाल 64:
		temp |= DMA_RQ_C1_SOURCE_MOD32;
		अवरोध;		      
	हाल 32:
		temp |= DMA_RQ_C1_SOURCE_MOD16;
		अवरोध; 
	शेष:
		dev_dbg(chip->card->dev,
			"period size (%d) not supported by HW\n", period_size);
		वापस -EINVAL;
	पूर्ण

	snd_cs46xx_poke (chip,pcm_channel->pcm_पढ़ोer_scb->address << 2,temp);

	वापस 0;
पूर्ण

पूर्णांक cs46xx_dsp_pcm_ostream_set_period (काष्ठा snd_cs46xx * chip,
				       पूर्णांक period_size)
अणु
	u32 temp = snd_cs46xx_peek (chip,WRITEBACK_SCB_ADDR << 2);
	temp &= ~DMA_RQ_C1_DEST_SIZE_MASK;

	चयन (period_size) अणु
	हाल 2048:
		temp |= DMA_RQ_C1_DEST_MOD1024;
		अवरोध;
	हाल 1024:
		temp |= DMA_RQ_C1_DEST_MOD512;
		अवरोध;
	हाल 512:
		temp |= DMA_RQ_C1_DEST_MOD256;
		अवरोध;
	हाल 256:
		temp |= DMA_RQ_C1_DEST_MOD128;
		अवरोध;
	हाल 128:
		temp |= DMA_RQ_C1_DEST_MOD64;
		अवरोध;
	हाल 64:
		temp |= DMA_RQ_C1_DEST_MOD32;
		अवरोध;		      
	हाल 32:
		temp |= DMA_RQ_C1_DEST_MOD16;
		अवरोध; 
	शेष:
		dev_dbg(chip->card->dev,
			"period size (%d) not supported by HW\n", period_size);
		वापस -EINVAL;
	पूर्ण

	snd_cs46xx_poke (chip,WRITEBACK_SCB_ADDR << 2,temp);

	वापस 0;
पूर्ण

व्योम cs46xx_dsp_destroy_pcm_channel (काष्ठा snd_cs46xx * chip,
				     काष्ठा dsp_pcm_channel_descriptor * pcm_channel)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	अचिन्हित दीर्घ flags;

	अगर (snd_BUG_ON(!pcm_channel->active ||
		       ins->npcm_channels <= 0 ||
		       pcm_channel->src_scb->ref_count <= 0))
		वापस;

	spin_lock_irqsave(&chip->reg_lock, flags);
	pcm_channel->unlinked = 1;
	pcm_channel->active = 0;
	pcm_channel->निजी_data = शून्य;
	pcm_channel->src_scb->ref_count --;
	ins->npcm_channels --;
	spin_unlock_irqrestore(&chip->reg_lock, flags);

	cs46xx_dsp_हटाओ_scb(chip,pcm_channel->pcm_पढ़ोer_scb);

	अगर (!pcm_channel->src_scb->ref_count) अणु
		cs46xx_dsp_हटाओ_scb(chip,pcm_channel->src_scb);

		अगर (snd_BUG_ON(pcm_channel->src_slot < 0 ||
			       pcm_channel->src_slot >= DSP_MAX_SRC_NR))
			वापस;

		ins->src_scb_slots[pcm_channel->src_slot] = 0;
		ins->nsrc_scb --;
	पूर्ण
पूर्ण

पूर्णांक cs46xx_dsp_pcm_unlink (काष्ठा snd_cs46xx * chip,
			   काष्ठा dsp_pcm_channel_descriptor * pcm_channel)
अणु
	अचिन्हित दीर्घ flags;

	अगर (snd_BUG_ON(!pcm_channel->active ||
		       chip->dsp_spos_instance->npcm_channels <= 0))
		वापस -EIO;

	spin_lock_irqsave(&chip->reg_lock, flags);
	अगर (pcm_channel->unlinked) अणु
		spin_unlock_irqrestore(&chip->reg_lock, flags);
		वापस -EIO;
	पूर्ण

	pcm_channel->unlinked = 1;

	_dsp_unlink_scb (chip,pcm_channel->pcm_पढ़ोer_scb);
	spin_unlock_irqrestore(&chip->reg_lock, flags);

	वापस 0;
पूर्ण

पूर्णांक cs46xx_dsp_pcm_link (काष्ठा snd_cs46xx * chip,
			 काष्ठा dsp_pcm_channel_descriptor * pcm_channel)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	काष्ठा dsp_scb_descriptor * parent_scb;
	काष्ठा dsp_scb_descriptor * src_scb = pcm_channel->src_scb;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->reg_lock, flags);

	अगर (pcm_channel->unlinked == 0) अणु
		spin_unlock_irqrestore(&chip->reg_lock, flags);
		वापस -EIO;
	पूर्ण

	parent_scb = src_scb;

	अगर (src_scb->sub_list_ptr != ins->the_null_scb) अणु
		src_scb->sub_list_ptr->parent_scb_ptr = pcm_channel->pcm_पढ़ोer_scb;
		pcm_channel->pcm_पढ़ोer_scb->next_scb_ptr = src_scb->sub_list_ptr;
	पूर्ण

	src_scb->sub_list_ptr = pcm_channel->pcm_पढ़ोer_scb;

	snd_BUG_ON(pcm_channel->pcm_पढ़ोer_scb->parent_scb_ptr);
	pcm_channel->pcm_पढ़ोer_scb->parent_scb_ptr = parent_scb;

	/* update SCB entry in DSP RAM */
	cs46xx_dsp_spos_update_scb(chip,pcm_channel->pcm_पढ़ोer_scb);

	/* update parent SCB entry */
	cs46xx_dsp_spos_update_scb(chip,parent_scb);

	pcm_channel->unlinked = 0;
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस 0;
पूर्ण

काष्ठा dsp_scb_descriptor *
cs46xx_add_record_source (काष्ठा snd_cs46xx *chip, काष्ठा dsp_scb_descriptor * source,
			  u16 addr, अक्षर * scb_name)
अणु
  	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	काष्ठा dsp_scb_descriptor * parent;
	काष्ठा dsp_scb_descriptor * pcm_input;
	पूर्णांक insert_poपूर्णांक;

	अगर (snd_BUG_ON(!ins->record_mixer_scb))
		वापस शून्य;

	अगर (ins->record_mixer_scb->sub_list_ptr != ins->the_null_scb) अणु
		parent = find_next_मुक्त_scb (chip,ins->record_mixer_scb->sub_list_ptr);
		insert_poपूर्णांक = SCB_ON_PARENT_NEXT_SCB;
	पूर्ण अन्यथा अणु
		parent = ins->record_mixer_scb;
		insert_poपूर्णांक = SCB_ON_PARENT_SUBLIST_SCB;
	पूर्ण

	pcm_input = cs46xx_dsp_create_pcm_serial_input_scb(chip,scb_name,addr,
							   source, parent,
							   insert_poपूर्णांक);

	वापस pcm_input;
पूर्ण

पूर्णांक cs46xx_src_unlink(काष्ठा snd_cs46xx *chip, काष्ठा dsp_scb_descriptor * src)
अणु
	अचिन्हित दीर्घ flags;

	अगर (snd_BUG_ON(!src->parent_scb_ptr))
		वापस -EINVAL;

	/* mute SCB */
	cs46xx_dsp_scb_set_volume (chip,src,0,0);

	spin_lock_irqsave(&chip->reg_lock, flags);
	_dsp_unlink_scb (chip,src);
	spin_unlock_irqrestore(&chip->reg_lock, flags);

	वापस 0;
पूर्ण

पूर्णांक cs46xx_src_link(काष्ठा snd_cs46xx *chip, काष्ठा dsp_scb_descriptor * src)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;
	काष्ठा dsp_scb_descriptor * parent_scb;

	अगर (snd_BUG_ON(src->parent_scb_ptr))
		वापस -EINVAL;
	अगर (snd_BUG_ON(!ins->master_mix_scb))
		वापस -EINVAL;

	अगर (ins->master_mix_scb->sub_list_ptr != ins->the_null_scb) अणु
		parent_scb = find_next_मुक्त_scb (chip,ins->master_mix_scb->sub_list_ptr);
		parent_scb->next_scb_ptr = src;
	पूर्ण अन्यथा अणु
		parent_scb = ins->master_mix_scb;
		parent_scb->sub_list_ptr = src;
	पूर्ण

	src->parent_scb_ptr = parent_scb;

	/* update entry in DSP RAM */
	cs46xx_dsp_spos_update_scb(chip,parent_scb);
  
	वापस 0;
पूर्ण

पूर्णांक cs46xx_dsp_enable_spdअगर_out (काष्ठा snd_cs46xx *chip)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;

	अगर ( ! (ins->spdअगर_status_out & DSP_SPDIF_STATUS_HW_ENABLED) ) अणु
		cs46xx_dsp_enable_spdअगर_hw (chip);
	पूर्ण

	/* करोnt touch anything अगर SPDIF is खोलो */
	अगर ( ins->spdअगर_status_out & DSP_SPDIF_STATUS_PLAYBACK_OPEN) अणु
		/* when cs46xx_iec958_post_बंद(...) is called it
		   will call this function अगर necessary depending on
		   this bit */
		ins->spdअगर_status_out |= DSP_SPDIF_STATUS_OUTPUT_ENABLED;

		वापस -EBUSY;
	पूर्ण

	अगर (snd_BUG_ON(ins->asynch_tx_scb))
		वापस -EINVAL;
	अगर (snd_BUG_ON(ins->master_mix_scb->next_scb_ptr !=
		       ins->the_null_scb))
		वापस -EINVAL;

	/* reset output snooper sample buffer poपूर्णांकer */
	snd_cs46xx_poke (chip, (ins->ref_snoop_scb->address + 2) << 2,
			 (OUTPUT_SNOOP_BUFFER + 0x10) << 0x10 );
	
	/* The asynch. transfer task */
	ins->asynch_tx_scb = cs46xx_dsp_create_asynch_fg_tx_scb(chip,"AsynchFGTxSCB",ASYNCTX_SCB_ADDR,
								SPDIFO_SCB_INST,
								SPDIFO_IP_OUTPUT_BUFFER1,
								ins->master_mix_scb,
								SCB_ON_PARENT_NEXT_SCB);
	अगर (!ins->asynch_tx_scb) वापस -ENOMEM;

	ins->spdअगर_pcm_input_scb = cs46xx_dsp_create_pcm_serial_input_scb(chip,"PCMSerialInput_II",
									  PCMSERIALINII_SCB_ADDR,
									  ins->ref_snoop_scb,
									  ins->asynch_tx_scb,
									  SCB_ON_PARENT_SUBLIST_SCB);
  
	
	अगर (!ins->spdअगर_pcm_input_scb) वापस -ENOMEM;

	/* monitor state */
	ins->spdअगर_status_out |= DSP_SPDIF_STATUS_OUTPUT_ENABLED;

	वापस 0;
पूर्ण

पूर्णांक  cs46xx_dsp_disable_spdअगर_out (काष्ठा snd_cs46xx *chip)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;

	/* करोnt touch anything अगर SPDIF is खोलो */
	अगर ( ins->spdअगर_status_out & DSP_SPDIF_STATUS_PLAYBACK_OPEN) अणु
		ins->spdअगर_status_out &= ~DSP_SPDIF_STATUS_OUTPUT_ENABLED;
		वापस -EBUSY;
	पूर्ण

	/* check पूर्णांकegrety */
	अगर (snd_BUG_ON(!ins->asynch_tx_scb))
		वापस -EINVAL;
	अगर (snd_BUG_ON(!ins->spdअगर_pcm_input_scb))
		वापस -EINVAL;
	अगर (snd_BUG_ON(ins->master_mix_scb->next_scb_ptr != ins->asynch_tx_scb))
		वापस -EINVAL;
	अगर (snd_BUG_ON(ins->asynch_tx_scb->parent_scb_ptr !=
		       ins->master_mix_scb))
		वापस -EINVAL;

	cs46xx_dsp_हटाओ_scb (chip,ins->spdअगर_pcm_input_scb);
	cs46xx_dsp_हटाओ_scb (chip,ins->asynch_tx_scb);

	ins->spdअगर_pcm_input_scb = शून्य;
	ins->asynch_tx_scb = शून्य;

	/* clear buffer to prevent any undesired noise */
	_dsp_clear_sample_buffer(chip,SPDIFO_IP_OUTPUT_BUFFER1,256);

	/* monitor state */
	ins->spdअगर_status_out  &= ~DSP_SPDIF_STATUS_OUTPUT_ENABLED;


	वापस 0;
पूर्ण

पूर्णांक cs46xx_iec958_pre_खोलो (काष्ठा snd_cs46xx *chip)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;

	अगर ( ins->spdअगर_status_out & DSP_SPDIF_STATUS_OUTPUT_ENABLED ) अणु
		/* हटाओ AsynchFGTxSCB and PCMSerialInput_II */
		cs46xx_dsp_disable_spdअगर_out (chip);

		/* save state */
		ins->spdअगर_status_out |= DSP_SPDIF_STATUS_OUTPUT_ENABLED;
	पूर्ण
	
	/* अगर not enabled alपढ़ोy */
	अगर ( !(ins->spdअगर_status_out & DSP_SPDIF_STATUS_HW_ENABLED) ) अणु
		cs46xx_dsp_enable_spdअगर_hw (chip);
	पूर्ण

	/* Create the asynch. transfer task  क्रम playback */
	ins->asynch_tx_scb = cs46xx_dsp_create_asynch_fg_tx_scb(chip,"AsynchFGTxSCB",ASYNCTX_SCB_ADDR,
								SPDIFO_SCB_INST,
								SPDIFO_IP_OUTPUT_BUFFER1,
								ins->master_mix_scb,
								SCB_ON_PARENT_NEXT_SCB);


	/* set spdअगर channel status value क्रम streaming */
	cs46xx_poke_via_dsp (chip,SP_SPDOUT_CSUV, ins->spdअगर_csuv_stream);

	ins->spdअगर_status_out  |= DSP_SPDIF_STATUS_PLAYBACK_OPEN;

	वापस 0;
पूर्ण

पूर्णांक cs46xx_iec958_post_बंद (काष्ठा snd_cs46xx *chip)
अणु
	काष्ठा dsp_spos_instance * ins = chip->dsp_spos_instance;

	अगर (snd_BUG_ON(!ins->asynch_tx_scb))
		वापस -EINVAL;

	ins->spdअगर_status_out  &= ~DSP_SPDIF_STATUS_PLAYBACK_OPEN;

	/* restore settings */
	cs46xx_poke_via_dsp (chip,SP_SPDOUT_CSUV, ins->spdअगर_csuv_शेष);
	
	/* deallocate stuff */
	अगर (ins->spdअगर_pcm_input_scb != शून्य) अणु
		cs46xx_dsp_हटाओ_scb (chip,ins->spdअगर_pcm_input_scb);
		ins->spdअगर_pcm_input_scb = शून्य;
	पूर्ण

	cs46xx_dsp_हटाओ_scb (chip,ins->asynch_tx_scb);
	ins->asynch_tx_scb = शून्य;

	/* clear buffer to prevent any undesired noise */
	_dsp_clear_sample_buffer(chip,SPDIFO_IP_OUTPUT_BUFFER1,256);

	/* restore state */
	अगर ( ins->spdअगर_status_out & DSP_SPDIF_STATUS_OUTPUT_ENABLED ) अणु
		cs46xx_dsp_enable_spdअगर_out (chip);
	पूर्ण
	
	वापस 0;
पूर्ण
