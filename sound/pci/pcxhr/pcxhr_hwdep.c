<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Digigram pcxhr compatible soundcards
 *
 * hwdep device manager
 *
 * Copyright (c) 2004 by Digigram <alsa@digigram.com>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/firmware.h>
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <sound/core.h>
#समावेश <sound/hwdep.h>
#समावेश "pcxhr.h"
#समावेश "pcxhr_mixer.h"
#समावेश "pcxhr_hwdep.h"
#समावेश "pcxhr_core.h"
#समावेश "pcxhr_mix22.h"


अटल पूर्णांक pcxhr_sub_init(काष्ठा pcxhr_mgr *mgr);
/*
 * get basic inक्रमmation and init pcxhr card
 */
अटल पूर्णांक pcxhr_init_board(काष्ठा pcxhr_mgr *mgr)
अणु
	पूर्णांक err;
	काष्ठा pcxhr_rmh rmh;
	पूर्णांक card_streams;

	/* calc the number of all streams used */
	अगर (mgr->mono_capture)
		card_streams = mgr->capture_chips * 2;
	अन्यथा
		card_streams = mgr->capture_chips;
	card_streams += mgr->playback_chips * PCXHR_PLAYBACK_STREAMS;

	/* enable पूर्णांकerrupts */
	pcxhr_enable_dsp(mgr);

	pcxhr_init_rmh(&rmh, CMD_SUPPORTED);
	err = pcxhr_send_msg(mgr, &rmh);
	अगर (err)
		वापस err;
	/* test 4, 8 or 12 phys out */
	अगर ((rmh.stat[0] & MASK_FIRST_FIELD) < mgr->playback_chips * 2)
		वापस -EINVAL;
	/* test 4, 8 or 2 phys in */
	अगर (((rmh.stat[0] >> (2 * FIELD_SIZE)) & MASK_FIRST_FIELD) <
	    mgr->capture_chips * 2)
		वापस -EINVAL;
	/* test max nb substream per board */
	अगर ((rmh.stat[1] & 0x5F) < card_streams)
		वापस -EINVAL;
	/* test max nb substream per pipe */
	अगर (((rmh.stat[1] >> 7) & 0x5F) < PCXHR_PLAYBACK_STREAMS)
		वापस -EINVAL;
	dev_dbg(&mgr->pci->dev,
		"supported formats : playback=%x capture=%x\n",
		    rmh.stat[2], rmh.stat[3]);

	pcxhr_init_rmh(&rmh, CMD_VERSION);
	/* firmware num क्रम DSP */
	rmh.cmd[0] |= mgr->firmware_num;
	/* transfer granularity in samples (should be multiple of 48) */
	rmh.cmd[1] = (1<<23) + mgr->granularity;
	rmh.cmd_len = 2;
	err = pcxhr_send_msg(mgr, &rmh);
	अगर (err)
		वापस err;
	dev_dbg(&mgr->pci->dev,
		"PCXHR DSP version is %d.%d.%d\n", (rmh.stat[0]>>16)&0xff,
		    (rmh.stat[0]>>8)&0xff, rmh.stat[0]&0xff);
	mgr->dsp_version = rmh.stat[0];

	अगर (mgr->is_hr_stereo)
		err = hr222_sub_init(mgr);
	अन्यथा
		err = pcxhr_sub_init(mgr);
	वापस err;
पूर्ण

अटल पूर्णांक pcxhr_sub_init(काष्ठा pcxhr_mgr *mgr)
अणु
	पूर्णांक err;
	काष्ठा pcxhr_rmh rmh;

	/* get options */
	pcxhr_init_rmh(&rmh, CMD_ACCESS_IO_READ);
	rmh.cmd[0] |= IO_NUM_REG_STATUS;
	rmh.cmd[1]  = REG_STATUS_OPTIONS;
	rmh.cmd_len = 2;
	err = pcxhr_send_msg(mgr, &rmh);
	अगर (err)
		वापस err;

	अगर ((rmh.stat[1] & REG_STATUS_OPT_DAUGHTER_MASK) ==
	    REG_STATUS_OPT_ANALOG_BOARD)
		mgr->board_has_analog = 1;	/* analog adकरोn board found */

	/* unmute inमाला_दो */
	err = pcxhr_ग_लिखो_io_num_reg_cont(mgr, REG_CONT_UNMUTE_INPUTS,
					  REG_CONT_UNMUTE_INPUTS, शून्य);
	अगर (err)
		वापस err;
	/* unmute outमाला_दो (a ग_लिखो to IO_NUM_REG_MUTE_OUT mutes!) */
	pcxhr_init_rmh(&rmh, CMD_ACCESS_IO_READ);
	rmh.cmd[0] |= IO_NUM_REG_MUTE_OUT;
	अगर (DSP_EXT_CMD_SET(mgr)) अणु
		rmh.cmd[1]  = 1;	/* unmute digital plugs */
		rmh.cmd_len = 2;
	पूर्ण
	err = pcxhr_send_msg(mgr, &rmh);
	वापस err;
पूर्ण

व्योम pcxhr_reset_board(काष्ठा pcxhr_mgr *mgr)
अणु
	काष्ठा pcxhr_rmh rmh;

	अगर (mgr->dsp_loaded & (1 << PCXHR_FIRMWARE_DSP_MAIN_INDEX)) अणु
		/* mute outमाला_दो */
	    अगर (!mgr->is_hr_stereo) अणु
		/* a पढ़ो to IO_NUM_REG_MUTE_OUT रेजिस्टर unmutes! */
		pcxhr_init_rmh(&rmh, CMD_ACCESS_IO_WRITE);
		rmh.cmd[0] |= IO_NUM_REG_MUTE_OUT;
		pcxhr_send_msg(mgr, &rmh);
		/* mute inमाला_दो */
		pcxhr_ग_लिखो_io_num_reg_cont(mgr, REG_CONT_UNMUTE_INPUTS,
					    0, शून्य);
	    पूर्ण
		/* stereo cards mute with reset of dsp */
	पूर्ण
	/* reset pcxhr dsp */
	अगर (mgr->dsp_loaded & (1 << PCXHR_FIRMWARE_DSP_EPRM_INDEX))
		pcxhr_reset_dsp(mgr);
	/* reset second xilinx */
	अगर (mgr->dsp_loaded & (1 << PCXHR_FIRMWARE_XLX_COM_INDEX)) अणु
		pcxhr_reset_xilinx_com(mgr);
		mgr->dsp_loaded = 1;
	पूर्ण
	वापस;
पूर्ण


/*
 *  allocate a playback/capture pipe (pcmp0/pcmc0)
 */
अटल पूर्णांक pcxhr_dsp_allocate_pipe(काष्ठा pcxhr_mgr *mgr,
				   काष्ठा pcxhr_pipe *pipe,
				   पूर्णांक is_capture, पूर्णांक pin)
अणु
	पूर्णांक stream_count, audio_count;
	पूर्णांक err;
	काष्ठा pcxhr_rmh rmh;

	अगर (is_capture) अणु
		stream_count = 1;
		अगर (mgr->mono_capture)
			audio_count = 1;
		अन्यथा
			audio_count = 2;
	पूर्ण अन्यथा अणु
		stream_count = PCXHR_PLAYBACK_STREAMS;
		audio_count = 2;	/* always stereo */
	पूर्ण
	dev_dbg(&mgr->pci->dev, "snd_add_ref_pipe pin(%d) pcm%c0\n",
		    pin, is_capture ? 'c' : 'p');
	pipe->is_capture = is_capture;
	pipe->first_audio = pin;
	/* define pipe (P_PCM_ONLY_MASK (0x020000) is not necessary) */
	pcxhr_init_rmh(&rmh, CMD_RES_PIPE);
	pcxhr_set_pipe_cmd_params(&rmh, is_capture, pin,
				  audio_count, stream_count);
	rmh.cmd[1] |= 0x020000; /* add P_PCM_ONLY_MASK */
	अगर (DSP_EXT_CMD_SET(mgr)) अणु
		/* add channel mask to command */
	  rmh.cmd[rmh.cmd_len++] = (audio_count == 1) ? 0x01 : 0x03;
	पूर्ण
	err = pcxhr_send_msg(mgr, &rmh);
	अगर (err < 0) अणु
		dev_err(&mgr->pci->dev, "error pipe allocation "
			   "(CMD_RES_PIPE) err=%x!\n", err);
		वापस err;
	पूर्ण
	pipe->status = PCXHR_PIPE_DEFINED;

	वापस 0;
पूर्ण

/*
 *  मुक्त playback/capture pipe (pcmp0/pcmc0)
 */
#अगर 0
अटल पूर्णांक pcxhr_dsp_मुक्त_pipe( काष्ठा pcxhr_mgr *mgr, काष्ठा pcxhr_pipe *pipe)
अणु
	काष्ठा pcxhr_rmh rmh;
	पूर्णांक capture_mask = 0;
	पूर्णांक playback_mask = 0;
	पूर्णांक err = 0;

	अगर (pipe->is_capture)
		capture_mask  = (1 << pipe->first_audio);
	अन्यथा
		playback_mask = (1 << pipe->first_audio);

	/* stop one pipe */
	err = pcxhr_set_pipe_state(mgr, playback_mask, capture_mask, 0);
	अगर (err < 0)
		dev_err(&mgr->pci->dev, "error stopping pipe!\n");
	/* release the pipe */
	pcxhr_init_rmh(&rmh, CMD_FREE_PIPE);
	pcxhr_set_pipe_cmd_params(&rmh, pipe->is_capture, pipe->first_audio,
				  0, 0);
	err = pcxhr_send_msg(mgr, &rmh);
	अगर (err < 0)
		dev_err(&mgr->pci->dev, "error pipe release "
			   "(CMD_FREE_PIPE) err(%x)\n", err);
	pipe->status = PCXHR_PIPE_UNDEFINED;
	वापस err;
पूर्ण
#पूर्ण_अगर


अटल पूर्णांक pcxhr_config_pipes(काष्ठा pcxhr_mgr *mgr)
अणु
	पूर्णांक err, i, j;
	काष्ठा snd_pcxhr *chip;
	काष्ठा pcxhr_pipe *pipe;

	/* allocate the pipes on the dsp */
	क्रम (i = 0; i < mgr->num_cards; i++) अणु
		chip = mgr->chip[i];
		अगर (chip->nb_streams_play) अणु
			pipe = &chip->playback_pipe;
			err = pcxhr_dsp_allocate_pipe( mgr, pipe, 0, i*2);
			अगर (err)
				वापस err;
			क्रम(j = 0; j < chip->nb_streams_play; j++)
				chip->playback_stream[j].pipe = pipe;
		पूर्ण
		क्रम (j = 0; j < chip->nb_streams_capt; j++) अणु
			pipe = &chip->capture_pipe[j];
			err = pcxhr_dsp_allocate_pipe(mgr, pipe, 1, i*2 + j);
			अगर (err)
				वापस err;
			chip->capture_stream[j].pipe = pipe;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pcxhr_start_pipes(काष्ठा pcxhr_mgr *mgr)
अणु
	पूर्णांक i, j;
	काष्ठा snd_pcxhr *chip;
	पूर्णांक playback_mask = 0;
	पूर्णांक capture_mask = 0;

	/* start all the pipes on the dsp */
	क्रम (i = 0; i < mgr->num_cards; i++) अणु
		chip = mgr->chip[i];
		अगर (chip->nb_streams_play)
			playback_mask |= 1 << chip->playback_pipe.first_audio;
		क्रम (j = 0; j < chip->nb_streams_capt; j++)
			capture_mask |= 1 << chip->capture_pipe[j].first_audio;
	पूर्ण
	वापस pcxhr_set_pipe_state(mgr, playback_mask, capture_mask, 1);
पूर्ण


अटल पूर्णांक pcxhr_dsp_load(काष्ठा pcxhr_mgr *mgr, पूर्णांक index,
			  स्थिर काष्ठा firmware *dsp)
अणु
	पूर्णांक err, card_index;

	dev_dbg(&mgr->pci->dev,
		"loading dsp [%d] size = %zd\n", index, dsp->size);

	चयन (index) अणु
	हाल PCXHR_FIRMWARE_XLX_INT_INDEX:
		pcxhr_reset_xilinx_com(mgr);
		वापस pcxhr_load_xilinx_binary(mgr, dsp, 0);

	हाल PCXHR_FIRMWARE_XLX_COM_INDEX:
		pcxhr_reset_xilinx_com(mgr);
		वापस pcxhr_load_xilinx_binary(mgr, dsp, 1);

	हाल PCXHR_FIRMWARE_DSP_EPRM_INDEX:
		pcxhr_reset_dsp(mgr);
		वापस pcxhr_load_eeprom_binary(mgr, dsp);

	हाल PCXHR_FIRMWARE_DSP_BOOT_INDEX:
		वापस pcxhr_load_boot_binary(mgr, dsp);

	हाल PCXHR_FIRMWARE_DSP_MAIN_INDEX:
		err = pcxhr_load_dsp_binary(mgr, dsp);
		अगर (err)
			वापस err;
		अवरोध;	/* जारी with first init */
	शेष:
		dev_err(&mgr->pci->dev, "wrong file index\n");
		वापस -EFAULT;
	पूर्ण /* end of चयन file index*/

	/* first communication with embedded */
	err = pcxhr_init_board(mgr);
        अगर (err < 0) अणु
		dev_err(&mgr->pci->dev, "pcxhr could not be set up\n");
		वापस err;
	पूर्ण
	err = pcxhr_config_pipes(mgr);
        अगर (err < 0) अणु
		dev_err(&mgr->pci->dev, "pcxhr pipes could not be set up\n");
		वापस err;
	पूर्ण
       	/* create devices and mixer in accordance with HW options*/
        क्रम (card_index = 0; card_index < mgr->num_cards; card_index++) अणु
		काष्ठा snd_pcxhr *chip = mgr->chip[card_index];

		अगर ((err = pcxhr_create_pcm(chip)) < 0)
			वापस err;

		अगर (card_index == 0) अणु
			अगर ((err = pcxhr_create_mixer(chip->mgr)) < 0)
				वापस err;
		पूर्ण
		अगर ((err = snd_card_रेजिस्टर(chip->card)) < 0)
			वापस err;
	पूर्ण
	err = pcxhr_start_pipes(mgr);
        अगर (err < 0) अणु
		dev_err(&mgr->pci->dev, "pcxhr pipes could not be started\n");
		वापस err;
	पूर्ण
	dev_dbg(&mgr->pci->dev,
		"pcxhr firmware downloaded and successfully set up\n");

	वापस 0;
पूर्ण

/*
 * fw loader entry
 */
पूर्णांक pcxhr_setup_firmware(काष्ठा pcxhr_mgr *mgr)
अणु
	अटल स्थिर अक्षर * स्थिर fw_files[][5] = अणु
	[0] = अणु "xlxint.dat", "xlxc882hr.dat",
		"dspe882.e56", "dspb882hr.b56", "dspd882.d56" पूर्ण,
	[1] = अणु "xlxint.dat", "xlxc882e.dat",
		"dspe882.e56", "dspb882e.b56", "dspd882.d56" पूर्ण,
	[2] = अणु "xlxint.dat", "xlxc1222hr.dat",
		"dspe882.e56", "dspb1222hr.b56", "dspd1222.d56" पूर्ण,
	[3] = अणु "xlxint.dat", "xlxc1222e.dat",
		"dspe882.e56", "dspb1222e.b56", "dspd1222.d56" पूर्ण,
	[4] = अणु शून्य, "xlxc222.dat",
		"dspe924.e56", "dspb924.b56", "dspd222.d56" पूर्ण,
	[5] = अणु शून्य, "xlxc924.dat",
		"dspe924.e56", "dspb924.b56", "dspd222.d56" पूर्ण,
	पूर्ण;
	अक्षर path[32];

	स्थिर काष्ठा firmware *fw_entry;
	पूर्णांक i, err;
	पूर्णांक fw_set = mgr->fw_file_set;

	क्रम (i = 0; i < 5; i++) अणु
		अगर (!fw_files[fw_set][i])
			जारी;
		प्र_लिखो(path, "pcxhr/%s", fw_files[fw_set][i]);
		अगर (request_firmware(&fw_entry, path, &mgr->pci->dev)) अणु
			dev_err(&mgr->pci->dev,
				"pcxhr: can't load firmware %s\n",
				   path);
			वापस -ENOENT;
		पूर्ण
		/* fake hwdep dsp record */
		err = pcxhr_dsp_load(mgr, i, fw_entry);
		release_firmware(fw_entry);
		अगर (err < 0)
			वापस err;
		mgr->dsp_loaded |= 1 << i;
	पूर्ण
	वापस 0;
पूर्ण

MODULE_FIRMWARE("pcxhr/xlxint.dat");
MODULE_FIRMWARE("pcxhr/xlxc882hr.dat");
MODULE_FIRMWARE("pcxhr/xlxc882e.dat");
MODULE_FIRMWARE("pcxhr/dspe882.e56");
MODULE_FIRMWARE("pcxhr/dspb882hr.b56");
MODULE_FIRMWARE("pcxhr/dspb882e.b56");
MODULE_FIRMWARE("pcxhr/dspd882.d56");

MODULE_FIRMWARE("pcxhr/xlxc1222hr.dat");
MODULE_FIRMWARE("pcxhr/xlxc1222e.dat");
MODULE_FIRMWARE("pcxhr/dspb1222hr.b56");
MODULE_FIRMWARE("pcxhr/dspb1222e.b56");
MODULE_FIRMWARE("pcxhr/dspd1222.d56");

MODULE_FIRMWARE("pcxhr/xlxc222.dat");
MODULE_FIRMWARE("pcxhr/xlxc924.dat");
MODULE_FIRMWARE("pcxhr/dspe924.e56");
MODULE_FIRMWARE("pcxhr/dspb924.b56");
MODULE_FIRMWARE("pcxhr/dspd222.d56");
