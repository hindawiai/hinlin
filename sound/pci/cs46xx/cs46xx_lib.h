<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  The driver क्रम the Cirrus Logic's Sound Fusion CS46XX based soundcards
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#अगर_अघोषित __CS46XX_LIB_H__
#घोषणा __CS46XX_LIB_H__

/*
 *  स्थिरants
 */

#घोषणा CS46XX_BA0_SIZE		  0x1000
#घोषणा CS46XX_BA1_DATA0_SIZE 0x3000
#घोषणा CS46XX_BA1_DATA1_SIZE 0x3800
#घोषणा CS46XX_BA1_PRG_SIZE	  0x7000
#घोषणा CS46XX_BA1_REG_SIZE	  0x0100



#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
#घोषणा CS46XX_MIN_PERIOD_SIZE 64
#घोषणा CS46XX_MAX_PERIOD_SIZE 1024*1024
#अन्यथा
#घोषणा CS46XX_MIN_PERIOD_SIZE 2048
#घोषणा CS46XX_MAX_PERIOD_SIZE 2048
#पूर्ण_अगर

#घोषणा CS46XX_FRAGS 2
/* #घोषणा CS46XX_BUFFER_SIZE CS46XX_MAX_PERIOD_SIZE * CS46XX_FRAGS */

#घोषणा SCB_NO_PARENT             0
#घोषणा SCB_ON_PARENT_NEXT_SCB    1
#घोषणा SCB_ON_PARENT_SUBLIST_SCB 2

/* 3*1024 parameter, 3.5*1024 sample, 2*3.5*1024 code */
#घोषणा BA1_DWORD_SIZE		(13 * 1024 + 512)
#घोषणा BA1_MEMORY_COUNT	3

/*
 *  common I/O routines
 */

अटल अंतरभूत व्योम snd_cs46xx_poke(काष्ठा snd_cs46xx *chip, अचिन्हित दीर्घ reg, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक bank = reg >> 16;
	अचिन्हित पूर्णांक offset = reg & 0xffff;

	/*
	अगर (bank == 0)
		prपूर्णांकk(KERN_DEBUG "snd_cs46xx_poke: %04X - %08X\n",
		       reg >> 2,val);
	*/
	ग_लिखोl(val, chip->region.idx[bank+1].remap_addr + offset);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक snd_cs46xx_peek(काष्ठा snd_cs46xx *chip, अचिन्हित दीर्घ reg)
अणु
	अचिन्हित पूर्णांक bank = reg >> 16;
	अचिन्हित पूर्णांक offset = reg & 0xffff;
	वापस पढ़ोl(chip->region.idx[bank+1].remap_addr + offset);
पूर्ण

अटल अंतरभूत व्योम snd_cs46xx_pokeBA0(काष्ठा snd_cs46xx *chip, अचिन्हित दीर्घ offset, अचिन्हित पूर्णांक val)
अणु
	ग_लिखोl(val, chip->region.name.ba0.remap_addr + offset);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक snd_cs46xx_peekBA0(काष्ठा snd_cs46xx *chip, अचिन्हित दीर्घ offset)
अणु
	वापस पढ़ोl(chip->region.name.ba0.remap_addr + offset);
पूर्ण

काष्ठा dsp_spos_instance *cs46xx_dsp_spos_create (काष्ठा snd_cs46xx * chip);
व्योम cs46xx_dsp_spos_destroy (काष्ठा snd_cs46xx * chip);
पूर्णांक cs46xx_dsp_load_module (काष्ठा snd_cs46xx * chip, काष्ठा dsp_module_desc * module);
#अगर_घोषित CONFIG_PM_SLEEP
पूर्णांक cs46xx_dsp_resume(काष्ठा snd_cs46xx * chip);
#पूर्ण_अगर
काष्ठा dsp_symbol_entry *cs46xx_dsp_lookup_symbol (काष्ठा snd_cs46xx * chip, अक्षर * symbol_name,
						   पूर्णांक symbol_type);
#अगर_घोषित CONFIG_SND_PROC_FS
पूर्णांक cs46xx_dsp_proc_init (काष्ठा snd_card *card, काष्ठा snd_cs46xx *chip);
पूर्णांक cs46xx_dsp_proc_करोne (काष्ठा snd_cs46xx *chip);
#अन्यथा
#घोषणा cs46xx_dsp_proc_init(card, chip)
#घोषणा cs46xx_dsp_proc_करोne(chip)
#पूर्ण_अगर
पूर्णांक cs46xx_dsp_scb_and_task_init (काष्ठा snd_cs46xx *chip);
पूर्णांक snd_cs46xx_करोwnload (काष्ठा snd_cs46xx *chip, u32 *src, अचिन्हित दीर्घ offset,
			 अचिन्हित दीर्घ len);
पूर्णांक snd_cs46xx_clear_BA1(काष्ठा snd_cs46xx *chip, अचिन्हित दीर्घ offset, अचिन्हित दीर्घ len);
पूर्णांक cs46xx_dsp_enable_spdअगर_out (काष्ठा snd_cs46xx *chip);
पूर्णांक cs46xx_dsp_enable_spdअगर_hw (काष्ठा snd_cs46xx *chip);
पूर्णांक cs46xx_dsp_disable_spdअगर_out (काष्ठा snd_cs46xx *chip);
पूर्णांक cs46xx_dsp_enable_spdअगर_in (काष्ठा snd_cs46xx *chip);
पूर्णांक cs46xx_dsp_disable_spdअगर_in (काष्ठा snd_cs46xx *chip);
पूर्णांक cs46xx_dsp_enable_pcm_capture (काष्ठा snd_cs46xx *chip);
पूर्णांक cs46xx_dsp_disable_pcm_capture (काष्ठा snd_cs46xx *chip);
पूर्णांक cs46xx_dsp_enable_adc_capture (काष्ठा snd_cs46xx *chip);
पूर्णांक cs46xx_dsp_disable_adc_capture (काष्ठा snd_cs46xx *chip);
पूर्णांक cs46xx_poke_via_dsp (काष्ठा snd_cs46xx *chip, u32 address, u32 data);
काष्ठा dsp_scb_descriptor * cs46xx_dsp_create_scb (काष्ठा snd_cs46xx *chip, अक्षर * name,
						   u32 * scb_data, u32 dest);
#अगर_घोषित CONFIG_SND_PROC_FS
व्योम cs46xx_dsp_proc_मुक्त_scb_desc (काष्ठा dsp_scb_descriptor * scb);
व्योम cs46xx_dsp_proc_रेजिस्टर_scb_desc (काष्ठा snd_cs46xx *chip,
					काष्ठा dsp_scb_descriptor * scb);
#अन्यथा
#घोषणा cs46xx_dsp_proc_मुक्त_scb_desc(scb)
#घोषणा cs46xx_dsp_proc_रेजिस्टर_scb_desc(chip, scb)
#पूर्ण_अगर
काष्ठा dsp_scb_descriptor * cs46xx_dsp_create_timing_master_scb (काष्ठा snd_cs46xx *chip);
काष्ठा dsp_scb_descriptor *
cs46xx_dsp_create_codec_out_scb(काष्ठा snd_cs46xx * chip,
				अक्षर * codec_name, u16 channel_disp, u16 fअगरo_addr,
				u16 child_scb_addr, u32 dest,
				काष्ठा dsp_scb_descriptor * parent_scb,
				पूर्णांक scb_child_type);
काष्ठा dsp_scb_descriptor *
cs46xx_dsp_create_codec_in_scb(काष्ठा snd_cs46xx * chip, अक्षर * codec_name,
			       u16 channel_disp, u16 fअगरo_addr,
			       u16 sample_buffer_addr, u32 dest,
			       काष्ठा dsp_scb_descriptor * parent_scb,
			       पूर्णांक scb_child_type);
व्योम cs46xx_dsp_हटाओ_scb (काष्ठा snd_cs46xx *chip,
			    काष्ठा dsp_scb_descriptor * scb);
काष्ठा dsp_scb_descriptor *
cs46xx_dsp_create_codec_in_scb(काष्ठा snd_cs46xx * chip, अक्षर * codec_name,
			       u16 channel_disp, u16 fअगरo_addr,
			       u16 sample_buffer_addr, u32 dest,
			       काष्ठा dsp_scb_descriptor * parent_scb,
			       पूर्णांक scb_child_type);
काष्ठा dsp_scb_descriptor *
cs46xx_dsp_create_src_task_scb(काष्ठा snd_cs46xx * chip, अक्षर * scb_name,
			       पूर्णांक sample_rate, u16 src_buffer_addr,
			       u16 src_delay_buffer_addr, u32 dest,
			       काष्ठा dsp_scb_descriptor * parent_scb,
			       पूर्णांक scb_child_type, पूर्णांक pass_through);
काष्ठा dsp_scb_descriptor *
cs46xx_dsp_create_mix_only_scb(काष्ठा snd_cs46xx * chip, अक्षर * scb_name,
			       u16 mix_buffer_addr, u32 dest,
			       काष्ठा dsp_scb_descriptor * parent_scb,
			       पूर्णांक scb_child_type);

काष्ठा dsp_scb_descriptor *
cs46xx_dsp_create_vari_decimate_scb(काष्ठा snd_cs46xx * chip, अक्षर * scb_name,
				    u16 vari_buffer_addr0, u16 vari_buffer_addr1, u32 dest,
				    काष्ठा dsp_scb_descriptor * parent_scb,
				    पूर्णांक scb_child_type);
काष्ठा dsp_scb_descriptor *
cs46xx_dsp_create_asynch_fg_rx_scb(काष्ठा snd_cs46xx * chip, अक्षर * scb_name,
				   u32 dest, u16 hfg_scb_address, u16 asynch_buffer_address,
				   काष्ठा dsp_scb_descriptor * parent_scb,
				   पूर्णांक scb_child_type);
काष्ठा dsp_scb_descriptor *
cs46xx_dsp_create_spio_ग_लिखो_scb(काष्ठा snd_cs46xx * chip, अक्षर * scb_name, u32 dest,
				 काष्ठा dsp_scb_descriptor * parent_scb,
				 पूर्णांक scb_child_type);
काष्ठा dsp_scb_descriptor *
cs46xx_dsp_create_mix_to_ostream_scb(काष्ठा snd_cs46xx * chip, अक्षर * scb_name,
				     u16 mix_buffer_addr, u16 ग_लिखोback_spb, u32 dest,
				     काष्ठा dsp_scb_descriptor * parent_scb,
				     पूर्णांक scb_child_type);
काष्ठा dsp_scb_descriptor *
cs46xx_dsp_create_magic_snoop_scb(काष्ठा snd_cs46xx * chip, अक्षर * scb_name,
				  u32 dest, u16 snoop_buffer_address,
				  काष्ठा dsp_scb_descriptor * snoop_scb,
				  काष्ठा dsp_scb_descriptor * parent_scb,
				  पूर्णांक scb_child_type);
काष्ठा dsp_pcm_channel_descriptor *
cs46xx_dsp_create_pcm_channel (काष्ठा snd_cs46xx * chip, u32 sample_rate,
			       व्योम * निजी_data, u32 hw_dma_addr,
			       पूर्णांक pcm_channel_id);
व्योम cs46xx_dsp_destroy_pcm_channel (काष्ठा snd_cs46xx * chip,
				     काष्ठा dsp_pcm_channel_descriptor * pcm_channel);
पूर्णांक cs46xx_dsp_pcm_unlink (काष्ठा snd_cs46xx * chip,
			   काष्ठा dsp_pcm_channel_descriptor * pcm_channel);
पूर्णांक cs46xx_dsp_pcm_link (काष्ठा snd_cs46xx * chip,
			 काष्ठा dsp_pcm_channel_descriptor * pcm_channel);
काष्ठा dsp_scb_descriptor *
cs46xx_add_record_source (काष्ठा snd_cs46xx *chip, काष्ठा dsp_scb_descriptor * source,
			  u16 addr, अक्षर * scb_name);
पूर्णांक cs46xx_src_unlink(काष्ठा snd_cs46xx *chip, काष्ठा dsp_scb_descriptor * src);
पूर्णांक cs46xx_src_link(काष्ठा snd_cs46xx *chip, काष्ठा dsp_scb_descriptor * src);
पूर्णांक cs46xx_iec958_pre_खोलो (काष्ठा snd_cs46xx *chip);
पूर्णांक cs46xx_iec958_post_बंद (काष्ठा snd_cs46xx *chip);
पूर्णांक cs46xx_dsp_pcm_channel_set_period (काष्ठा snd_cs46xx * chip,
				       काष्ठा dsp_pcm_channel_descriptor * pcm_channel,
				       पूर्णांक period_size);
पूर्णांक cs46xx_dsp_pcm_ostream_set_period (काष्ठा snd_cs46xx * chip, पूर्णांक period_size);
पूर्णांक cs46xx_dsp_set_dac_volume (काष्ठा snd_cs46xx * chip, u16 left, u16 right);
पूर्णांक cs46xx_dsp_set_iec958_volume (काष्ठा snd_cs46xx * chip, u16 left, u16 right);
#पूर्ण_अगर /* __CS46XX_LIB_H__ */
