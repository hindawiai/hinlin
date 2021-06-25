<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 1999 by Uros Bizjak <uros@kss-loka.si>
 *                        Takashi Iwai <tiwai@suse.de>
 *
 *  SB16ASP/AWE32 CSP control
 *
 *  CSP microcode loader:
 *   alsa-tools/sb16_csp/ 
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/info.h>
#समावेश <sound/sb16_csp.h>
#समावेश <sound/initval.h>

MODULE_AUTHOR("Uros Bizjak <uros@kss-loka.si>");
MODULE_DESCRIPTION("ALSA driver for SB16 Creative Signal Processor");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE("sb16/mulaw_main.csp");
MODULE_FIRMWARE("sb16/alaw_main.csp");
MODULE_FIRMWARE("sb16/ima_adpcm_init.csp");
MODULE_FIRMWARE("sb16/ima_adpcm_playback.csp");
MODULE_FIRMWARE("sb16/ima_adpcm_capture.csp");

#अगर_घोषित SNDRV_LITTLE_ENDIAN
#घोषणा CSP_HDR_VALUE(a,b,c,d)	((a) | ((b)<<8) | ((c)<<16) | ((d)<<24))
#अन्यथा
#घोषणा CSP_HDR_VALUE(a,b,c,d)	((d) | ((c)<<8) | ((b)<<16) | ((a)<<24))
#पूर्ण_अगर

#घोषणा RIFF_HEADER	CSP_HDR_VALUE('R', 'I', 'F', 'F')
#घोषणा CSP__HEADER	CSP_HDR_VALUE('C', 'S', 'P', ' ')
#घोषणा LIST_HEADER	CSP_HDR_VALUE('L', 'I', 'S', 'T')
#घोषणा FUNC_HEADER	CSP_HDR_VALUE('f', 'u', 'n', 'c')
#घोषणा CODE_HEADER	CSP_HDR_VALUE('c', 'o', 'd', 'e')
#घोषणा INIT_HEADER	CSP_HDR_VALUE('i', 'n', 'i', 't')
#घोषणा MAIN_HEADER	CSP_HDR_VALUE('m', 'a', 'i', 'n')

/*
 * RIFF data क्रमmat
 */
काष्ठा rअगरf_header अणु
	__le32 name;
	__le32 len;
पूर्ण;

काष्ठा desc_header अणु
	काष्ठा rअगरf_header info;
	__le16 func_nr;
	__le16 VOC_type;
	__le16 flags_play_rec;
	__le16 flags_16bit_8bit;
	__le16 flags_stereo_mono;
	__le16 flags_rates;
पूर्ण;

/*
 * prototypes
 */
अटल व्योम snd_sb_csp_मुक्त(काष्ठा snd_hwdep *hw);
अटल पूर्णांक snd_sb_csp_खोलो(काष्ठा snd_hwdep * hw, काष्ठा file *file);
अटल पूर्णांक snd_sb_csp_ioctl(काष्ठा snd_hwdep * hw, काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
अटल पूर्णांक snd_sb_csp_release(काष्ठा snd_hwdep * hw, काष्ठा file *file);

अटल पूर्णांक csp_detect(काष्ठा snd_sb *chip, पूर्णांक *version);
अटल पूर्णांक set_codec_parameter(काष्ठा snd_sb *chip, अचिन्हित अक्षर par, अचिन्हित अक्षर val);
अटल पूर्णांक set_रेजिस्टर(काष्ठा snd_sb *chip, अचिन्हित अक्षर reg, अचिन्हित अक्षर val);
अटल पूर्णांक पढ़ो_रेजिस्टर(काष्ठा snd_sb *chip, अचिन्हित अक्षर reg);
अटल पूर्णांक set_mode_रेजिस्टर(काष्ठा snd_sb *chip, अचिन्हित अक्षर mode);
अटल पूर्णांक get_version(काष्ठा snd_sb *chip);

अटल पूर्णांक snd_sb_csp_rअगरf_load(काष्ठा snd_sb_csp * p,
				काष्ठा snd_sb_csp_microcode __user * code);
अटल पूर्णांक snd_sb_csp_unload(काष्ठा snd_sb_csp * p);
अटल पूर्णांक snd_sb_csp_load_user(काष्ठा snd_sb_csp * p, स्थिर अचिन्हित अक्षर __user *buf, पूर्णांक size, पूर्णांक load_flags);
अटल पूर्णांक snd_sb_csp_स्वतःload(काष्ठा snd_sb_csp * p, snd_pcm_क्रमmat_t pcm_sfmt, पूर्णांक play_rec_mode);
अटल पूर्णांक snd_sb_csp_check_version(काष्ठा snd_sb_csp * p);

अटल पूर्णांक snd_sb_csp_use(काष्ठा snd_sb_csp * p);
अटल पूर्णांक snd_sb_csp_unuse(काष्ठा snd_sb_csp * p);
अटल पूर्णांक snd_sb_csp_start(काष्ठा snd_sb_csp * p, पूर्णांक sample_width, पूर्णांक channels);
अटल पूर्णांक snd_sb_csp_stop(काष्ठा snd_sb_csp * p);
अटल पूर्णांक snd_sb_csp_छोड़ो(काष्ठा snd_sb_csp * p);
अटल पूर्णांक snd_sb_csp_restart(काष्ठा snd_sb_csp * p);

अटल पूर्णांक snd_sb_qsound_build(काष्ठा snd_sb_csp * p);
अटल व्योम snd_sb_qsound_destroy(काष्ठा snd_sb_csp * p);
अटल पूर्णांक snd_sb_csp_qsound_transfer(काष्ठा snd_sb_csp * p);

अटल पूर्णांक init_proc_entry(काष्ठा snd_sb_csp * p, पूर्णांक device);
अटल व्योम info_पढ़ो(काष्ठा snd_info_entry *entry, काष्ठा snd_info_buffer *buffer);

/*
 * Detect CSP chip and create a new instance
 */
पूर्णांक snd_sb_csp_new(काष्ठा snd_sb *chip, पूर्णांक device, काष्ठा snd_hwdep ** rhwdep)
अणु
	काष्ठा snd_sb_csp *p;
	पूर्णांक version;
	पूर्णांक err;
	काष्ठा snd_hwdep *hw;

	अगर (rhwdep)
		*rhwdep = शून्य;

	अगर (csp_detect(chip, &version))
		वापस -ENODEV;

	अगर ((err = snd_hwdep_new(chip->card, "SB16-CSP", device, &hw)) < 0)
		वापस err;

	अगर ((p = kzalloc(माप(*p), GFP_KERNEL)) == शून्य) अणु
		snd_device_मुक्त(chip->card, hw);
		वापस -ENOMEM;
	पूर्ण
	p->chip = chip;
	p->version = version;

	/* CSP चालकs */
	p->ops.csp_use = snd_sb_csp_use;
	p->ops.csp_unuse = snd_sb_csp_unuse;
	p->ops.csp_स्वतःload = snd_sb_csp_स्वतःload;
	p->ops.csp_start = snd_sb_csp_start;
	p->ops.csp_stop = snd_sb_csp_stop;
	p->ops.csp_qsound_transfer = snd_sb_csp_qsound_transfer;

	mutex_init(&p->access_mutex);
	प्र_लिखो(hw->name, "CSP v%d.%d", (version >> 4), (version & 0x0f));
	hw->अगरace = SNDRV_HWDEP_IFACE_SB16CSP;
	hw->निजी_data = p;
	hw->निजी_मुक्त = snd_sb_csp_मुक्त;

	/* चालकs - only ग_लिखो/ioctl */
	hw->ops.खोलो = snd_sb_csp_खोलो;
	hw->ops.ioctl = snd_sb_csp_ioctl;
	hw->ops.release = snd_sb_csp_release;

	/* create a proc entry */
	init_proc_entry(p, device);
	अगर (rhwdep)
		*rhwdep = hw;
	वापस 0;
पूर्ण

/*
 * मुक्त_निजी क्रम hwdep instance
 */
अटल व्योम snd_sb_csp_मुक्त(काष्ठा snd_hwdep *hwdep)
अणु
	पूर्णांक i;
	काष्ठा snd_sb_csp *p = hwdep->निजी_data;
	अगर (p) अणु
		अगर (p->running & SNDRV_SB_CSP_ST_RUNNING)
			snd_sb_csp_stop(p);
		क्रम (i = 0; i < ARRAY_SIZE(p->csp_programs); ++i)
			release_firmware(p->csp_programs[i]);
		kमुक्त(p);
	पूर्ण
पूर्ण

/* ------------------------------ */

/*
 * खोलो the device exclusively
 */
अटल पूर्णांक snd_sb_csp_खोलो(काष्ठा snd_hwdep * hw, काष्ठा file *file)
अणु
	काष्ठा snd_sb_csp *p = hw->निजी_data;
	वापस (snd_sb_csp_use(p));
पूर्ण

/*
 * ioctl क्रम hwdep device:
 */
अटल पूर्णांक snd_sb_csp_ioctl(काष्ठा snd_hwdep * hw, काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_sb_csp *p = hw->निजी_data;
	काष्ठा snd_sb_csp_info info;
	काष्ठा snd_sb_csp_start start_info;
	पूर्णांक err;

	अगर (snd_BUG_ON(!p))
		वापस -EINVAL;

	अगर (snd_sb_csp_check_version(p))
		वापस -ENODEV;

	चयन (cmd) अणु
		/* get inक्रमmation */
	हाल SNDRV_SB_CSP_IOCTL_INFO:
		स_रखो(&info, 0, माप(info));
		*info.codec_name = *p->codec_name;
		info.func_nr = p->func_nr;
		info.acc_क्रमmat = p->acc_क्रमmat;
		info.acc_channels = p->acc_channels;
		info.acc_width = p->acc_width;
		info.acc_rates = p->acc_rates;
		info.csp_mode = p->mode;
		info.run_channels = p->run_channels;
		info.run_width = p->run_width;
		info.version = p->version;
		info.state = p->running;
		अगर (copy_to_user((व्योम __user *)arg, &info, माप(info)))
			err = -EFAULT;
		अन्यथा
			err = 0;
		अवरोध;

		/* load CSP microcode */
	हाल SNDRV_SB_CSP_IOCTL_LOAD_CODE:
		err = (p->running & SNDRV_SB_CSP_ST_RUNNING ?
		       -EBUSY : snd_sb_csp_rअगरf_load(p, (काष्ठा snd_sb_csp_microcode __user *) arg));
		अवरोध;
	हाल SNDRV_SB_CSP_IOCTL_UNLOAD_CODE:
		err = (p->running & SNDRV_SB_CSP_ST_RUNNING ?
		       -EBUSY : snd_sb_csp_unload(p));
		अवरोध;

		/* change CSP running state */
	हाल SNDRV_SB_CSP_IOCTL_START:
		अगर (copy_from_user(&start_info, (व्योम __user *) arg, माप(start_info)))
			err = -EFAULT;
		अन्यथा
			err = snd_sb_csp_start(p, start_info.sample_width, start_info.channels);
		अवरोध;
	हाल SNDRV_SB_CSP_IOCTL_STOP:
		err = snd_sb_csp_stop(p);
		अवरोध;
	हाल SNDRV_SB_CSP_IOCTL_PAUSE:
		err = snd_sb_csp_छोड़ो(p);
		अवरोध;
	हाल SNDRV_SB_CSP_IOCTL_RESTART:
		err = snd_sb_csp_restart(p);
		अवरोध;
	शेष:
		err = -ENOTTY;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

/*
 * बंद the device
 */
अटल पूर्णांक snd_sb_csp_release(काष्ठा snd_hwdep * hw, काष्ठा file *file)
अणु
	काष्ठा snd_sb_csp *p = hw->निजी_data;
	वापस (snd_sb_csp_unuse(p));
पूर्ण

/* ------------------------------ */

/*
 * acquire device
 */
अटल पूर्णांक snd_sb_csp_use(काष्ठा snd_sb_csp * p)
अणु
	mutex_lock(&p->access_mutex);
	अगर (p->used) अणु
		mutex_unlock(&p->access_mutex);
		वापस -EAGAIN;
	पूर्ण
	p->used++;
	mutex_unlock(&p->access_mutex);

	वापस 0;

पूर्ण

/*
 * release device
 */
अटल पूर्णांक snd_sb_csp_unuse(काष्ठा snd_sb_csp * p)
अणु
	mutex_lock(&p->access_mutex);
	p->used--;
	mutex_unlock(&p->access_mutex);

	वापस 0;
पूर्ण

/*
 * load microcode via ioctl: 
 * code is user-space poपूर्णांकer
 */
अटल पूर्णांक snd_sb_csp_rअगरf_load(काष्ठा snd_sb_csp * p,
				काष्ठा snd_sb_csp_microcode __user * mcode)
अणु
	काष्ठा snd_sb_csp_mc_header info;

	अचिन्हित अक्षर __user *data_ptr;
	अचिन्हित अक्षर __user *data_end;
	अचिन्हित लघु func_nr = 0;

	काष्ठा rअगरf_header file_h, item_h, code_h;
	__le32 item_type;
	काष्ठा desc_header funcdesc_h;

	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	अगर (copy_from_user(&info, mcode, माप(info)))
		वापस -EFAULT;
	data_ptr = mcode->data;

	अगर (copy_from_user(&file_h, data_ptr, माप(file_h)))
		वापस -EFAULT;
	अगर ((le32_to_cpu(file_h.name) != RIFF_HEADER) ||
	    (le32_to_cpu(file_h.len) >= SNDRV_SB_CSP_MAX_MICROCODE_खाता_SIZE - माप(file_h))) अणु
		snd_prपूर्णांकd("%s: Invalid RIFF header\n", __func__);
		वापस -EINVAL;
	पूर्ण
	data_ptr += माप(file_h);
	data_end = data_ptr + le32_to_cpu(file_h.len);

	अगर (copy_from_user(&item_type, data_ptr, माप(item_type)))
		वापस -EFAULT;
	अगर (le32_to_cpu(item_type) != CSP__HEADER) अणु
		snd_prपूर्णांकd("%s: Invalid RIFF file type\n", __func__);
		वापस -EINVAL;
	पूर्ण
	data_ptr += माप (item_type);

	क्रम (; data_ptr < data_end; data_ptr += le32_to_cpu(item_h.len)) अणु
		अगर (copy_from_user(&item_h, data_ptr, माप(item_h)))
			वापस -EFAULT;
		data_ptr += माप(item_h);
		अगर (le32_to_cpu(item_h.name) != LIST_HEADER)
			जारी;

		अगर (copy_from_user(&item_type, data_ptr, माप(item_type)))
			 वापस -EFAULT;
		चयन (le32_to_cpu(item_type)) अणु
		हाल FUNC_HEADER:
			अगर (copy_from_user(&funcdesc_h, data_ptr + माप(item_type), माप(funcdesc_h)))
				वापस -EFAULT;
			func_nr = le16_to_cpu(funcdesc_h.func_nr);
			अवरोध;
		हाल CODE_HEADER:
			अगर (func_nr != info.func_req)
				अवरोध;	/* not required function, try next */
			data_ptr += माप(item_type);

			/* destroy QSound mixer element */
			अगर (p->mode == SNDRV_SB_CSP_MODE_QSOUND) अणु
				snd_sb_qsound_destroy(p);
			पूर्ण
			/* Clear all flags */
			p->running = 0;
			p->mode = 0;

			/* load microcode blocks */
			क्रम (;;) अणु
				अगर (data_ptr >= data_end)
					वापस -EINVAL;
				अगर (copy_from_user(&code_h, data_ptr, माप(code_h)))
					वापस -EFAULT;

				/* init microcode blocks */
				अगर (le32_to_cpu(code_h.name) != INIT_HEADER)
					अवरोध;
				data_ptr += माप(code_h);
				err = snd_sb_csp_load_user(p, data_ptr, le32_to_cpu(code_h.len),
						      SNDRV_SB_CSP_LOAD_INITBLOCK);
				अगर (err)
					वापस err;
				data_ptr += le32_to_cpu(code_h.len);
			पूर्ण
			/* मुख्य microcode block */
			अगर (copy_from_user(&code_h, data_ptr, माप(code_h)))
				वापस -EFAULT;

			अगर (le32_to_cpu(code_h.name) != MAIN_HEADER) अणु
				snd_prपूर्णांकd("%s: Missing 'main' microcode\n", __func__);
				वापस -EINVAL;
			पूर्ण
			data_ptr += माप(code_h);
			err = snd_sb_csp_load_user(p, data_ptr,
						   le32_to_cpu(code_h.len), 0);
			अगर (err)
				वापस err;

			/* fill in codec header */
			strscpy(p->codec_name, info.codec_name, माप(p->codec_name));
			p->func_nr = func_nr;
			p->mode = le16_to_cpu(funcdesc_h.flags_play_rec);
			चयन (le16_to_cpu(funcdesc_h.VOC_type)) अणु
			हाल 0x0001:	/* QSound decoder */
				अगर (le16_to_cpu(funcdesc_h.flags_play_rec) == SNDRV_SB_CSP_MODE_DSP_WRITE) अणु
					अगर (snd_sb_qsound_build(p) == 0)
						/* set QSound flag and clear all other mode flags */
						p->mode = SNDRV_SB_CSP_MODE_QSOUND;
				पूर्ण
				p->acc_क्रमmat = 0;
				अवरोध;
			हाल 0x0006:	/* A Law codec */
				p->acc_क्रमmat = SNDRV_PCM_FMTBIT_A_LAW;
				अवरोध;
			हाल 0x0007:	/* Mu Law codec */
				p->acc_क्रमmat = SNDRV_PCM_FMTBIT_MU_LAW;
				अवरोध;
			हाल 0x0011:	/* what Creative thinks is IMA ADPCM codec */
			हाल 0x0200:	/* Creative ADPCM codec */
				p->acc_क्रमmat = SNDRV_PCM_FMTBIT_IMA_ADPCM;
				अवरोध;
			हाल    201:	/* Text 2 Speech decoder */
				/* TODO: Text2Speech handling routines */
				p->acc_क्रमmat = 0;
				अवरोध;
			हाल 0x0202:	/* Fast Speech 8 codec */
			हाल 0x0203:	/* Fast Speech 10 codec */
				p->acc_क्रमmat = SNDRV_PCM_FMTBIT_SPECIAL;
				अवरोध;
			शेष:	/* other codecs are unsupported */
				p->acc_क्रमmat = p->acc_width = p->acc_rates = 0;
				p->mode = 0;
				snd_prपूर्णांकd("%s: Unsupported CSP codec type: 0x%04x\n",
					   __func__,
					   le16_to_cpu(funcdesc_h.VOC_type));
				वापस -EINVAL;
			पूर्ण
			p->acc_channels = le16_to_cpu(funcdesc_h.flags_stereo_mono);
			p->acc_width = le16_to_cpu(funcdesc_h.flags_16bit_8bit);
			p->acc_rates = le16_to_cpu(funcdesc_h.flags_rates);

			/* Decouple CSP from IRQ and DMAREQ lines */
			spin_lock_irqsave(&p->chip->reg_lock, flags);
			set_mode_रेजिस्टर(p->chip, 0xfc);
			set_mode_रेजिस्टर(p->chip, 0x00);
			spin_unlock_irqrestore(&p->chip->reg_lock, flags);

			/* finished loading successfully */
			p->running = SNDRV_SB_CSP_ST_LOADED;	/* set LOADED flag */
			वापस 0;
		पूर्ण
	पूर्ण
	snd_prपूर्णांकd("%s: Function #%d not found\n", __func__, info.func_req);
	वापस -EINVAL;
पूर्ण

/*
 * unload CSP microcode
 */
अटल पूर्णांक snd_sb_csp_unload(काष्ठा snd_sb_csp * p)
अणु
	अगर (p->running & SNDRV_SB_CSP_ST_RUNNING)
		वापस -EBUSY;
	अगर (!(p->running & SNDRV_SB_CSP_ST_LOADED))
		वापस -ENXIO;

	/* clear supported क्रमmats */
	p->acc_क्रमmat = 0;
	p->acc_channels = p->acc_width = p->acc_rates = 0;
	/* destroy QSound mixer element */
	अगर (p->mode == SNDRV_SB_CSP_MODE_QSOUND) अणु
		snd_sb_qsound_destroy(p);
	पूर्ण
	/* clear all flags */
	p->running = 0;
	p->mode = 0;
	वापस 0;
पूर्ण

/*
 * send command sequence to DSP
 */
अटल अंतरभूत पूर्णांक command_seq(काष्ठा snd_sb *chip, स्थिर अचिन्हित अक्षर *seq, पूर्णांक size)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < size; i++) अणु
		अगर (!snd_sbdsp_command(chip, seq[i]))
			वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * set CSP codec parameter
 */
अटल पूर्णांक set_codec_parameter(काष्ठा snd_sb *chip, अचिन्हित अक्षर par, अचिन्हित अक्षर val)
अणु
	अचिन्हित अक्षर dsp_cmd[3];

	dsp_cmd[0] = 0x05;	/* CSP set codec parameter */
	dsp_cmd[1] = val;	/* Parameter value */
	dsp_cmd[2] = par;	/* Parameter */
	command_seq(chip, dsp_cmd, 3);
	snd_sbdsp_command(chip, 0x03);	/* DSP पढ़ो? */
	अगर (snd_sbdsp_get_byte(chip) != par)
		वापस -EIO;
	वापस 0;
पूर्ण

/*
 * set CSP रेजिस्टर
 */
अटल पूर्णांक set_रेजिस्टर(काष्ठा snd_sb *chip, अचिन्हित अक्षर reg, अचिन्हित अक्षर val)
अणु
	अचिन्हित अक्षर dsp_cmd[3];

	dsp_cmd[0] = 0x0e;	/* CSP set रेजिस्टर */
	dsp_cmd[1] = reg;	/* CSP Register */
	dsp_cmd[2] = val;	/* value */
	वापस command_seq(chip, dsp_cmd, 3);
पूर्ण

/*
 * पढ़ो CSP रेजिस्टर
 * वापस < 0 -> error
 */
अटल पूर्णांक पढ़ो_रेजिस्टर(काष्ठा snd_sb *chip, अचिन्हित अक्षर reg)
अणु
	अचिन्हित अक्षर dsp_cmd[2];

	dsp_cmd[0] = 0x0f;	/* CSP पढ़ो रेजिस्टर */
	dsp_cmd[1] = reg;	/* CSP Register */
	command_seq(chip, dsp_cmd, 2);
	वापस snd_sbdsp_get_byte(chip);	/* Read DSP value */
पूर्ण

/*
 * set CSP mode रेजिस्टर
 */
अटल पूर्णांक set_mode_रेजिस्टर(काष्ठा snd_sb *chip, अचिन्हित अक्षर mode)
अणु
	अचिन्हित अक्षर dsp_cmd[2];

	dsp_cmd[0] = 0x04;	/* CSP set mode रेजिस्टर */
	dsp_cmd[1] = mode;	/* mode */
	वापस command_seq(chip, dsp_cmd, 2);
पूर्ण

/*
 * Detect CSP
 * वापस 0 अगर CSP exists.
 */
अटल पूर्णांक csp_detect(काष्ठा snd_sb *chip, पूर्णांक *version)
अणु
	अचिन्हित अक्षर csp_test1, csp_test2;
	अचिन्हित दीर्घ flags;
	पूर्णांक result = -ENODEV;

	spin_lock_irqsave(&chip->reg_lock, flags);

	set_codec_parameter(chip, 0x00, 0x00);
	set_mode_रेजिस्टर(chip, 0xfc);		/* 0xfc = ?? */

	csp_test1 = पढ़ो_रेजिस्टर(chip, 0x83);
	set_रेजिस्टर(chip, 0x83, ~csp_test1);
	csp_test2 = पढ़ो_रेजिस्टर(chip, 0x83);
	अगर (csp_test2 != (csp_test1 ^ 0xff))
		जाओ __fail;

	set_रेजिस्टर(chip, 0x83, csp_test1);
	csp_test2 = पढ़ो_रेजिस्टर(chip, 0x83);
	अगर (csp_test2 != csp_test1)
		जाओ __fail;

	set_mode_रेजिस्टर(chip, 0x00);		/* 0x00 = ? */

	*version = get_version(chip);
	snd_sbdsp_reset(chip);	/* reset DSP after getversion! */
	अगर (*version >= 0x10 && *version <= 0x1f)
		result = 0;		/* valid version id */

      __fail:
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस result;
पूर्ण

/*
 * get CSP version number
 */
अटल पूर्णांक get_version(काष्ठा snd_sb *chip)
अणु
	अचिन्हित अक्षर dsp_cmd[2];

	dsp_cmd[0] = 0x08;	/* SB_DSP_!something! */
	dsp_cmd[1] = 0x03;	/* get chip version id? */
	command_seq(chip, dsp_cmd, 2);

	वापस (snd_sbdsp_get_byte(chip));
पूर्ण

/*
 * check अगर the CSP version is valid
 */
अटल पूर्णांक snd_sb_csp_check_version(काष्ठा snd_sb_csp * p)
अणु
	अगर (p->version < 0x10 || p->version > 0x1f) अणु
		snd_prपूर्णांकd("%s: Invalid CSP version: 0x%x\n", __func__, p->version);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * करोwnload microcode to CSP (microcode should have one "main" block).
 */
अटल पूर्णांक snd_sb_csp_load(काष्ठा snd_sb_csp * p, स्थिर अचिन्हित अक्षर *buf, पूर्णांक size, पूर्णांक load_flags)
अणु
	पूर्णांक status, i;
	पूर्णांक err;
	पूर्णांक result = -EIO;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&p->chip->reg_lock, flags);
	snd_sbdsp_command(p->chip, 0x01);	/* CSP करोwnload command */
	अगर (snd_sbdsp_get_byte(p->chip)) अणु
		snd_prपूर्णांकd("%s: Download command failed\n", __func__);
		जाओ __fail;
	पूर्ण
	/* Send CSP low byte (size - 1) */
	snd_sbdsp_command(p->chip, (अचिन्हित अक्षर)(size - 1));
	/* Send high byte */
	snd_sbdsp_command(p->chip, (अचिन्हित अक्षर)((size - 1) >> 8));
	/* send microcode sequence */
	/* load from kernel space */
	जबतक (size--) अणु
		अगर (!snd_sbdsp_command(p->chip, *buf++))
			जाओ __fail;
	पूर्ण
	अगर (snd_sbdsp_get_byte(p->chip))
		जाओ __fail;

	अगर (load_flags & SNDRV_SB_CSP_LOAD_INITBLOCK) अणु
		i = 0;
		/* some codecs (FastSpeech) take some समय to initialize */
		जबतक (1) अणु
			snd_sbdsp_command(p->chip, 0x03);
			status = snd_sbdsp_get_byte(p->chip);
			अगर (status == 0x55 || ++i >= 10)
				अवरोध;
			udelay (10);
		पूर्ण
		अगर (status != 0x55) अणु
			snd_prपूर्णांकd("%s: Microcode initialization failed\n", __func__);
			जाओ __fail;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Read mixer रेजिस्टर SB_DSP4_DMASETUP after loading 'main' code.
		 * Start CSP chip अगर no 16bit DMA channel is set - some kind
		 * of स्वतःrun or perhaps a bugfix?
		 */
		spin_lock(&p->chip->mixer_lock);
		status = snd_sbmixer_पढ़ो(p->chip, SB_DSP4_DMASETUP);
		spin_unlock(&p->chip->mixer_lock);
		अगर (!(status & (SB_DMASETUP_DMA7 | SB_DMASETUP_DMA6 | SB_DMASETUP_DMA5))) अणु
			err = (set_codec_parameter(p->chip, 0xaa, 0x00) ||
			       set_codec_parameter(p->chip, 0xff, 0x00));
			snd_sbdsp_reset(p->chip);		/* really! */
			अगर (err)
				जाओ __fail;
			set_mode_रेजिस्टर(p->chip, 0xc0);	/* c0 = STOP */
			set_mode_रेजिस्टर(p->chip, 0x70);	/* 70 = RUN */
		पूर्ण
	पूर्ण
	result = 0;

      __fail:
	spin_unlock_irqrestore(&p->chip->reg_lock, flags);
	वापस result;
पूर्ण
 
अटल पूर्णांक snd_sb_csp_load_user(काष्ठा snd_sb_csp * p, स्थिर अचिन्हित अक्षर __user *buf, पूर्णांक size, पूर्णांक load_flags)
अणु
	पूर्णांक err;
	अचिन्हित अक्षर *kbuf;

	kbuf = memdup_user(buf, size);
	अगर (IS_ERR(kbuf))
		वापस PTR_ERR(kbuf);

	err = snd_sb_csp_load(p, kbuf, size, load_flags);

	kमुक्त(kbuf);
	वापस err;
पूर्ण

अटल पूर्णांक snd_sb_csp_firmware_load(काष्ठा snd_sb_csp *p, पूर्णांक index, पूर्णांक flags)
अणु
	अटल स्थिर अक्षर *स्थिर names[] = अणु
		"sb16/mulaw_main.csp",
		"sb16/alaw_main.csp",
		"sb16/ima_adpcm_init.csp",
		"sb16/ima_adpcm_playback.csp",
		"sb16/ima_adpcm_capture.csp",
	पूर्ण;
	स्थिर काष्ठा firmware *program;

	BUILD_BUG_ON(ARRAY_SIZE(names) != CSP_PROGRAM_COUNT);
	program = p->csp_programs[index];
	अगर (!program) अणु
		पूर्णांक err = request_firmware(&program, names[index],
				       p->chip->card->dev);
		अगर (err < 0)
			वापस err;
		p->csp_programs[index] = program;
	पूर्ण
	वापस snd_sb_csp_load(p, program->data, program->size, flags);
पूर्ण

/*
 * स्वतःload hardware codec अगर necessary
 * वापस 0 अगर CSP is loaded and पढ़ोy to run (p->running != 0)
 */
अटल पूर्णांक snd_sb_csp_स्वतःload(काष्ठा snd_sb_csp * p, snd_pcm_क्रमmat_t pcm_sfmt, पूर्णांक play_rec_mode)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	/* अगर CSP is running or manually loaded then निकास */
	अगर (p->running & (SNDRV_SB_CSP_ST_RUNNING | SNDRV_SB_CSP_ST_LOADED)) 
		वापस -EBUSY;

	/* स्वतःload microcode only अगर requested hardware codec is not alपढ़ोy loaded */
	अगर (((1U << (__क्रमce पूर्णांक)pcm_sfmt) & p->acc_क्रमmat) && (play_rec_mode & p->mode)) अणु
		p->running = SNDRV_SB_CSP_ST_AUTO;
	पूर्ण अन्यथा अणु
		चयन (pcm_sfmt) अणु
		हाल SNDRV_PCM_FORMAT_MU_LAW:
			err = snd_sb_csp_firmware_load(p, CSP_PROGRAM_MULAW, 0);
			p->acc_क्रमmat = SNDRV_PCM_FMTBIT_MU_LAW;
			p->mode = SNDRV_SB_CSP_MODE_DSP_READ | SNDRV_SB_CSP_MODE_DSP_WRITE;
			अवरोध;
		हाल SNDRV_PCM_FORMAT_A_LAW:
			err = snd_sb_csp_firmware_load(p, CSP_PROGRAM_ALAW, 0);
			p->acc_क्रमmat = SNDRV_PCM_FMTBIT_A_LAW;
			p->mode = SNDRV_SB_CSP_MODE_DSP_READ | SNDRV_SB_CSP_MODE_DSP_WRITE;
			अवरोध;
		हाल SNDRV_PCM_FORMAT_IMA_ADPCM:
			err = snd_sb_csp_firmware_load(p, CSP_PROGRAM_ADPCM_INIT,
						       SNDRV_SB_CSP_LOAD_INITBLOCK);
			अगर (err)
				अवरोध;
			अगर (play_rec_mode == SNDRV_SB_CSP_MODE_DSP_WRITE) अणु
				err = snd_sb_csp_firmware_load
					(p, CSP_PROGRAM_ADPCM_PLAYBACK, 0);
				p->mode = SNDRV_SB_CSP_MODE_DSP_WRITE;
			पूर्ण अन्यथा अणु
				err = snd_sb_csp_firmware_load
					(p, CSP_PROGRAM_ADPCM_CAPTURE, 0);
				p->mode = SNDRV_SB_CSP_MODE_DSP_READ;
			पूर्ण
			p->acc_क्रमmat = SNDRV_PCM_FMTBIT_IMA_ADPCM;
			अवरोध;				  
		शेष:
			/* Decouple CSP from IRQ and DMAREQ lines */
			अगर (p->running & SNDRV_SB_CSP_ST_AUTO) अणु
				spin_lock_irqsave(&p->chip->reg_lock, flags);
				set_mode_रेजिस्टर(p->chip, 0xfc);
				set_mode_रेजिस्टर(p->chip, 0x00);
				spin_unlock_irqrestore(&p->chip->reg_lock, flags);
				p->running = 0;			/* clear स्वतःloaded flag */
			पूर्ण
			वापस -EINVAL;
		पूर्ण
		अगर (err) अणु
			p->acc_क्रमmat = 0;
			p->acc_channels = p->acc_width = p->acc_rates = 0;

			p->running = 0;				/* clear स्वतःloaded flag */
			p->mode = 0;
			वापस (err);
		पूर्ण अन्यथा अणु
			p->running = SNDRV_SB_CSP_ST_AUTO;	/* set स्वतःloaded flag */
			p->acc_width = SNDRV_SB_CSP_SAMPLE_16BIT;	/* only 16 bit data */
			p->acc_channels = SNDRV_SB_CSP_MONO | SNDRV_SB_CSP_STEREO;
			p->acc_rates = SNDRV_SB_CSP_RATE_ALL;	/* HW codecs accept all rates */
		पूर्ण   

	पूर्ण
	वापस (p->running & SNDRV_SB_CSP_ST_AUTO) ? 0 : -ENXIO;
पूर्ण

/*
 * start CSP
 */
अटल पूर्णांक snd_sb_csp_start(काष्ठा snd_sb_csp * p, पूर्णांक sample_width, पूर्णांक channels)
अणु
	अचिन्हित अक्षर s_type;	/* sample type */
	अचिन्हित अक्षर mixL, mixR;
	पूर्णांक result = -EIO;
	अचिन्हित दीर्घ flags;

	अगर (!(p->running & (SNDRV_SB_CSP_ST_LOADED | SNDRV_SB_CSP_ST_AUTO))) अणु
		snd_prपूर्णांकd("%s: Microcode not loaded\n", __func__);
		वापस -ENXIO;
	पूर्ण
	अगर (p->running & SNDRV_SB_CSP_ST_RUNNING) अणु
		snd_prपूर्णांकd("%s: CSP already running\n", __func__);
		वापस -EBUSY;
	पूर्ण
	अगर (!(sample_width & p->acc_width)) अणु
		snd_prपूर्णांकd("%s: Unsupported PCM sample width\n", __func__);
		वापस -EINVAL;
	पूर्ण
	अगर (!(channels & p->acc_channels)) अणु
		snd_prपूर्णांकd("%s: Invalid number of channels\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* Mute PCM volume */
	spin_lock_irqsave(&p->chip->mixer_lock, flags);
	mixL = snd_sbmixer_पढ़ो(p->chip, SB_DSP4_PCM_DEV);
	mixR = snd_sbmixer_पढ़ो(p->chip, SB_DSP4_PCM_DEV + 1);
	snd_sbmixer_ग_लिखो(p->chip, SB_DSP4_PCM_DEV, mixL & 0x7);
	snd_sbmixer_ग_लिखो(p->chip, SB_DSP4_PCM_DEV + 1, mixR & 0x7);

	spin_lock(&p->chip->reg_lock);
	set_mode_रेजिस्टर(p->chip, 0xc0);	/* c0 = STOP */
	set_mode_रेजिस्टर(p->chip, 0x70);	/* 70 = RUN */

	s_type = 0x00;
	अगर (channels == SNDRV_SB_CSP_MONO)
		s_type = 0x11;	/* 000n 000n    (n = 1 अगर mono) */
	अगर (sample_width == SNDRV_SB_CSP_SAMPLE_8BIT)
		s_type |= 0x22;	/* 00dX 00dX    (d = 1 अगर 8 bit samples) */

	अगर (set_codec_parameter(p->chip, 0x81, s_type)) अणु
		snd_prपूर्णांकd("%s: Set sample type command failed\n", __func__);
		जाओ __fail;
	पूर्ण
	अगर (set_codec_parameter(p->chip, 0x80, 0x00)) अणु
		snd_prपूर्णांकd("%s: Codec start command failed\n", __func__);
		जाओ __fail;
	पूर्ण
	p->run_width = sample_width;
	p->run_channels = channels;

	p->running |= SNDRV_SB_CSP_ST_RUNNING;

	अगर (p->mode & SNDRV_SB_CSP_MODE_QSOUND) अणु
		set_codec_parameter(p->chip, 0xe0, 0x01);
		/* enable QSound decoder */
		set_codec_parameter(p->chip, 0x00, 0xff);
		set_codec_parameter(p->chip, 0x01, 0xff);
		p->running |= SNDRV_SB_CSP_ST_QSOUND;
		/* set QSound startup value */
		snd_sb_csp_qsound_transfer(p);
	पूर्ण
	result = 0;

      __fail:
	spin_unlock(&p->chip->reg_lock);

	/* restore PCM volume */
	snd_sbmixer_ग_लिखो(p->chip, SB_DSP4_PCM_DEV, mixL);
	snd_sbmixer_ग_लिखो(p->chip, SB_DSP4_PCM_DEV + 1, mixR);
	spin_unlock_irqrestore(&p->chip->mixer_lock, flags);

	वापस result;
पूर्ण

/*
 * stop CSP
 */
अटल पूर्णांक snd_sb_csp_stop(काष्ठा snd_sb_csp * p)
अणु
	पूर्णांक result;
	अचिन्हित अक्षर mixL, mixR;
	अचिन्हित दीर्घ flags;

	अगर (!(p->running & SNDRV_SB_CSP_ST_RUNNING))
		वापस 0;

	/* Mute PCM volume */
	spin_lock_irqsave(&p->chip->mixer_lock, flags);
	mixL = snd_sbmixer_पढ़ो(p->chip, SB_DSP4_PCM_DEV);
	mixR = snd_sbmixer_पढ़ो(p->chip, SB_DSP4_PCM_DEV + 1);
	snd_sbmixer_ग_लिखो(p->chip, SB_DSP4_PCM_DEV, mixL & 0x7);
	snd_sbmixer_ग_लिखो(p->chip, SB_DSP4_PCM_DEV + 1, mixR & 0x7);

	spin_lock(&p->chip->reg_lock);
	अगर (p->running & SNDRV_SB_CSP_ST_QSOUND) अणु
		set_codec_parameter(p->chip, 0xe0, 0x01);
		/* disable QSound decoder */
		set_codec_parameter(p->chip, 0x00, 0x00);
		set_codec_parameter(p->chip, 0x01, 0x00);

		p->running &= ~SNDRV_SB_CSP_ST_QSOUND;
	पूर्ण
	result = set_mode_रेजिस्टर(p->chip, 0xc0);	/* c0 = STOP */
	spin_unlock(&p->chip->reg_lock);

	/* restore PCM volume */
	snd_sbmixer_ग_लिखो(p->chip, SB_DSP4_PCM_DEV, mixL);
	snd_sbmixer_ग_लिखो(p->chip, SB_DSP4_PCM_DEV + 1, mixR);
	spin_unlock_irqrestore(&p->chip->mixer_lock, flags);

	अगर (!(result))
		p->running &= ~(SNDRV_SB_CSP_ST_PAUSED | SNDRV_SB_CSP_ST_RUNNING);
	वापस result;
पूर्ण

/*
 * छोड़ो CSP codec and hold DMA transfer
 */
अटल पूर्णांक snd_sb_csp_छोड़ो(काष्ठा snd_sb_csp * p)
अणु
	पूर्णांक result;
	अचिन्हित दीर्घ flags;

	अगर (!(p->running & SNDRV_SB_CSP_ST_RUNNING))
		वापस -EBUSY;

	spin_lock_irqsave(&p->chip->reg_lock, flags);
	result = set_codec_parameter(p->chip, 0x80, 0xff);
	spin_unlock_irqrestore(&p->chip->reg_lock, flags);
	अगर (!(result))
		p->running |= SNDRV_SB_CSP_ST_PAUSED;

	वापस result;
पूर्ण

/*
 * restart CSP codec and resume DMA transfer
 */
अटल पूर्णांक snd_sb_csp_restart(काष्ठा snd_sb_csp * p)
अणु
	पूर्णांक result;
	अचिन्हित दीर्घ flags;

	अगर (!(p->running & SNDRV_SB_CSP_ST_PAUSED))
		वापस -EBUSY;

	spin_lock_irqsave(&p->chip->reg_lock, flags);
	result = set_codec_parameter(p->chip, 0x80, 0x00);
	spin_unlock_irqrestore(&p->chip->reg_lock, flags);
	अगर (!(result))
		p->running &= ~SNDRV_SB_CSP_ST_PAUSED;

	वापस result;
पूर्ण

/* ------------------------------ */

/*
 * QSound mixer control क्रम PCM
 */

#घोषणा snd_sb_qsound_चयन_info	snd_ctl_boolean_mono_info

अटल पूर्णांक snd_sb_qsound_चयन_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_sb_csp *p = snd_kcontrol_chip(kcontrol);
	
	ucontrol->value.पूर्णांकeger.value[0] = p->q_enabled ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sb_qsound_चयन_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_sb_csp *p = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक change;
	अचिन्हित अक्षर nval;
	
	nval = ucontrol->value.पूर्णांकeger.value[0] & 0x01;
	spin_lock_irqsave(&p->q_lock, flags);
	change = p->q_enabled != nval;
	p->q_enabled = nval;
	spin_unlock_irqrestore(&p->q_lock, flags);
	वापस change;
पूर्ण

अटल पूर्णांक snd_sb_qsound_space_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = SNDRV_SB_CSP_QSOUND_MAX_RIGHT;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sb_qsound_space_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_sb_csp *p = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	
	spin_lock_irqsave(&p->q_lock, flags);
	ucontrol->value.पूर्णांकeger.value[0] = p->qpos_left;
	ucontrol->value.पूर्णांकeger.value[1] = p->qpos_right;
	spin_unlock_irqrestore(&p->q_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sb_qsound_space_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_sb_csp *p = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक change;
	अचिन्हित अक्षर nval1, nval2;
	
	nval1 = ucontrol->value.पूर्णांकeger.value[0];
	अगर (nval1 > SNDRV_SB_CSP_QSOUND_MAX_RIGHT)
		nval1 = SNDRV_SB_CSP_QSOUND_MAX_RIGHT;
	nval2 = ucontrol->value.पूर्णांकeger.value[1];
	अगर (nval2 > SNDRV_SB_CSP_QSOUND_MAX_RIGHT)
		nval2 = SNDRV_SB_CSP_QSOUND_MAX_RIGHT;
	spin_lock_irqsave(&p->q_lock, flags);
	change = p->qpos_left != nval1 || p->qpos_right != nval2;
	p->qpos_left = nval1;
	p->qpos_right = nval2;
	p->qpos_changed = change;
	spin_unlock_irqrestore(&p->q_lock, flags);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_sb_qsound_चयन = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "3D Control - Switch",
	.info = snd_sb_qsound_चयन_info,
	.get = snd_sb_qsound_चयन_get,
	.put = snd_sb_qsound_चयन_put
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_sb_qsound_space = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "3D Control - Space",
	.info = snd_sb_qsound_space_info,
	.get = snd_sb_qsound_space_get,
	.put = snd_sb_qsound_space_put
पूर्ण;

अटल पूर्णांक snd_sb_qsound_build(काष्ठा snd_sb_csp * p)
अणु
	काष्ठा snd_card *card;
	पूर्णांक err;

	अगर (snd_BUG_ON(!p))
		वापस -EINVAL;

	card = p->chip->card;
	p->qpos_left = p->qpos_right = SNDRV_SB_CSP_QSOUND_MAX_RIGHT / 2;
	p->qpos_changed = 0;

	spin_lock_init(&p->q_lock);

	अगर ((err = snd_ctl_add(card, p->qsound_चयन = snd_ctl_new1(&snd_sb_qsound_चयन, p))) < 0) अणु
		p->qsound_चयन = शून्य;
		जाओ __error;
	पूर्ण
	अगर ((err = snd_ctl_add(card, p->qsound_space = snd_ctl_new1(&snd_sb_qsound_space, p))) < 0) अणु
		p->qsound_space = शून्य;
		जाओ __error;
	पूर्ण

	वापस 0;

     __error:
	snd_sb_qsound_destroy(p);
	वापस err;
पूर्ण

अटल व्योम snd_sb_qsound_destroy(काष्ठा snd_sb_csp * p)
अणु
	काष्ठा snd_card *card;
	अचिन्हित दीर्घ flags;

	अगर (snd_BUG_ON(!p))
		वापस;

	card = p->chip->card;	
	
	करोwn_ग_लिखो(&card->controls_rwsem);
	अगर (p->qsound_चयन)
		snd_ctl_हटाओ(card, p->qsound_चयन);
	अगर (p->qsound_space)
		snd_ctl_हटाओ(card, p->qsound_space);
	up_ग_लिखो(&card->controls_rwsem);

	/* cancel pending transfer of QSound parameters */
	spin_lock_irqsave (&p->q_lock, flags);
	p->qpos_changed = 0;
	spin_unlock_irqrestore (&p->q_lock, flags);
पूर्ण

/*
 * Transfer qsound parameters to CSP,
 * function should be called from पूर्णांकerrupt routine
 */
अटल पूर्णांक snd_sb_csp_qsound_transfer(काष्ठा snd_sb_csp * p)
अणु
	पूर्णांक err = -ENXIO;

	spin_lock(&p->q_lock);
	अगर (p->running & SNDRV_SB_CSP_ST_QSOUND) अणु
		set_codec_parameter(p->chip, 0xe0, 0x01);
		/* left channel */
		set_codec_parameter(p->chip, 0x00, p->qpos_left);
		set_codec_parameter(p->chip, 0x02, 0x00);
		/* right channel */
		set_codec_parameter(p->chip, 0x00, p->qpos_right);
		set_codec_parameter(p->chip, 0x03, 0x00);
		err = 0;
	पूर्ण
	p->qpos_changed = 0;
	spin_unlock(&p->q_lock);
	वापस err;
पूर्ण

/* ------------------------------ */

/*
 * proc पूर्णांकerface
 */
अटल पूर्णांक init_proc_entry(काष्ठा snd_sb_csp * p, पूर्णांक device)
अणु
	अक्षर name[16];

	प्र_लिखो(name, "cspD%d", device);
	snd_card_ro_proc_new(p->chip->card, name, p, info_पढ़ो);
	वापस 0;
पूर्ण

अटल व्योम info_पढ़ो(काष्ठा snd_info_entry *entry, काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_sb_csp *p = entry->निजी_data;

	snd_iम_लिखो(buffer, "Creative Signal Processor [v%d.%d]\n", (p->version >> 4), (p->version & 0x0f));
	snd_iम_लिखो(buffer, "State: %cx%c%c%c\n", ((p->running & SNDRV_SB_CSP_ST_QSOUND) ? 'Q' : '-'),
		    ((p->running & SNDRV_SB_CSP_ST_PAUSED) ? 'P' : '-'),
		    ((p->running & SNDRV_SB_CSP_ST_RUNNING) ? 'R' : '-'),
		    ((p->running & SNDRV_SB_CSP_ST_LOADED) ? 'L' : '-'));
	अगर (p->running & SNDRV_SB_CSP_ST_LOADED) अणु
		snd_iम_लिखो(buffer, "Codec: %s [func #%d]\n", p->codec_name, p->func_nr);
		snd_iम_लिखो(buffer, "Sample rates: ");
		अगर (p->acc_rates == SNDRV_SB_CSP_RATE_ALL) अणु
			snd_iम_लिखो(buffer, "All\n");
		पूर्ण अन्यथा अणु
			snd_iम_लिखो(buffer, "%s%s%s%s\n",
				    ((p->acc_rates & SNDRV_SB_CSP_RATE_8000) ? "8000Hz " : ""),
				    ((p->acc_rates & SNDRV_SB_CSP_RATE_11025) ? "11025Hz " : ""),
				    ((p->acc_rates & SNDRV_SB_CSP_RATE_22050) ? "22050Hz " : ""),
				    ((p->acc_rates & SNDRV_SB_CSP_RATE_44100) ? "44100Hz" : ""));
		पूर्ण
		अगर (p->mode == SNDRV_SB_CSP_MODE_QSOUND) अणु
			snd_iम_लिखो(buffer, "QSound decoder %sabled\n",
				    p->q_enabled ? "en" : "dis");
		पूर्ण अन्यथा अणु
			snd_iम_लिखो(buffer, "PCM format ID: 0x%x (%s/%s) [%s/%s] [%s/%s]\n",
				    p->acc_क्रमmat,
				    ((p->acc_width & SNDRV_SB_CSP_SAMPLE_16BIT) ? "16bit" : "-"),
				    ((p->acc_width & SNDRV_SB_CSP_SAMPLE_8BIT) ? "8bit" : "-"),
				    ((p->acc_channels & SNDRV_SB_CSP_MONO) ? "mono" : "-"),
				    ((p->acc_channels & SNDRV_SB_CSP_STEREO) ? "stereo" : "-"),
				    ((p->mode & SNDRV_SB_CSP_MODE_DSP_WRITE) ? "playback" : "-"),
				    ((p->mode & SNDRV_SB_CSP_MODE_DSP_READ) ? "capture" : "-"));
		पूर्ण
	पूर्ण
	अगर (p->running & SNDRV_SB_CSP_ST_AUTO) अणु
		snd_iम_लिखो(buffer, "Autoloaded Mu-Law, A-Law or Ima-ADPCM hardware codec\n");
	पूर्ण
	अगर (p->running & SNDRV_SB_CSP_ST_RUNNING) अणु
		snd_iम_लिखो(buffer, "Processing %dbit %s PCM samples\n",
			    ((p->run_width & SNDRV_SB_CSP_SAMPLE_16BIT) ? 16 : 8),
			    ((p->run_channels & SNDRV_SB_CSP_MONO) ? "mono" : "stereo"));
	पूर्ण
	अगर (p->running & SNDRV_SB_CSP_ST_QSOUND) अणु
		snd_iम_लिखो(buffer, "Qsound position: left = 0x%x, right = 0x%x\n",
			    p->qpos_left, p->qpos_right);
	पूर्ण
पूर्ण

/* */

EXPORT_SYMBOL(snd_sb_csp_new);
