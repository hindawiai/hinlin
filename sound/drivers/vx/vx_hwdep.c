<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Digigram VX soundcards
 *
 * DSP firmware management
 *
 * Copyright (c) 2002 by Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/hwdep.h>
#समावेश <sound/vx_core.h>

MODULE_FIRMWARE("vx/bx_1_vxp.b56");
MODULE_FIRMWARE("vx/bx_1_vp4.b56");
MODULE_FIRMWARE("vx/x1_1_vx2.xlx");
MODULE_FIRMWARE("vx/x1_2_v22.xlx");
MODULE_FIRMWARE("vx/x1_1_vxp.xlx");
MODULE_FIRMWARE("vx/x1_1_vp4.xlx");
MODULE_FIRMWARE("vx/bd56002.boot");
MODULE_FIRMWARE("vx/bd563v2.boot");
MODULE_FIRMWARE("vx/bd563s3.boot");
MODULE_FIRMWARE("vx/l_1_vx2.d56");
MODULE_FIRMWARE("vx/l_1_v22.d56");
MODULE_FIRMWARE("vx/l_1_vxp.d56");
MODULE_FIRMWARE("vx/l_1_vp4.d56");

पूर्णांक snd_vx_setup_firmware(काष्ठा vx_core *chip)
अणु
	अटल स्थिर अक्षर * स्थिर fw_files[VX_TYPE_NUMS][4] = अणु
		[VX_TYPE_BOARD] = अणु
			शून्य, "x1_1_vx2.xlx", "bd56002.boot", "l_1_vx2.d56",
		पूर्ण,
		[VX_TYPE_V2] = अणु
			शून्य, "x1_2_v22.xlx", "bd563v2.boot", "l_1_v22.d56",
		पूर्ण,
		[VX_TYPE_MIC] = अणु
			शून्य, "x1_2_v22.xlx", "bd563v2.boot", "l_1_v22.d56",
		पूर्ण,
		[VX_TYPE_VXPOCKET] = अणु
			"bx_1_vxp.b56", "x1_1_vxp.xlx", "bd563s3.boot", "l_1_vxp.d56"
		पूर्ण,
		[VX_TYPE_VXP440] = अणु
			"bx_1_vp4.b56", "x1_1_vp4.xlx", "bd563s3.boot", "l_1_vp4.d56"
		पूर्ण,
	पूर्ण;

	पूर्णांक i, err;

	क्रम (i = 0; i < 4; i++) अणु
		अक्षर path[32];
		स्थिर काष्ठा firmware *fw;
		अगर (! fw_files[chip->type][i])
			जारी;
		प्र_लिखो(path, "vx/%s", fw_files[chip->type][i]);
		अगर (request_firmware(&fw, path, chip->dev)) अणु
			snd_prपूर्णांकk(KERN_ERR "vx: can't load firmware %s\n", path);
			वापस -ENOENT;
		पूर्ण
		err = chip->ops->load_dsp(chip, i, fw);
		अगर (err < 0) अणु
			release_firmware(fw);
			वापस err;
		पूर्ण
		अगर (i == 1)
			chip->chip_status |= VX_STAT_XILINX_LOADED;
#अगर_घोषित CONFIG_PM
		chip->firmware[i] = fw;
#अन्यथा
		release_firmware(fw);
#पूर्ण_अगर
	पूर्ण

	/* ok, we reached to the last one */
	/* create the devices अगर not built yet */
	अगर ((err = snd_vx_pcm_new(chip)) < 0)
		वापस err;

	अगर ((err = snd_vx_mixer_new(chip)) < 0)
		वापस err;

	अगर (chip->ops->add_controls)
		अगर ((err = chip->ops->add_controls(chip)) < 0)
			वापस err;

	chip->chip_status |= VX_STAT_DEVICE_INIT;
	chip->chip_status |= VX_STAT_CHIP_INIT;

	वापस snd_card_रेजिस्टर(chip->card);
पूर्ण

/* exported */
व्योम snd_vx_मुक्त_firmware(काष्ठा vx_core *chip)
अणु
#अगर_घोषित CONFIG_PM
	पूर्णांक i;
	क्रम (i = 0; i < 4; i++)
		release_firmware(chip->firmware[i]);
#पूर्ण_अगर
पूर्ण

EXPORT_SYMBOL(snd_vx_setup_firmware);
EXPORT_SYMBOL(snd_vx_मुक्त_firmware);
