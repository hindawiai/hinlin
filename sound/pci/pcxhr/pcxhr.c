<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Digigram pcxhr compatible soundcards
 *
 * मुख्य file with alsa callbacks
 *
 * Copyright (c) 2004 by Digigram <alsa@digigram.com>
 */


#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>

#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/info.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश "pcxhr.h"
#समावेश "pcxhr_mixer.h"
#समावेश "pcxhr_hwdep.h"
#समावेश "pcxhr_core.h"
#समावेश "pcxhr_mix22.h"

#घोषणा DRIVER_NAME "pcxhr"

MODULE_AUTHOR("Markus Bollinger <bollinger@digigram.com>, "
	      "Marc Titinger <titinger@digigram.com>");
MODULE_DESCRIPTION("Digigram " DRIVER_NAME " " PCXHR_DRIVER_VERSION_STRING);
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;/* Enable this card */
अटल bool mono[SNDRV_CARDS];				/* capture  mono only */

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for Digigram " DRIVER_NAME " soundcard");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for Digigram " DRIVER_NAME " soundcard");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable Digigram " DRIVER_NAME " soundcard");
module_param_array(mono, bool, शून्य, 0444);
MODULE_PARM_DESC(mono, "Mono capture mode (default is stereo)");

क्रमागत अणु
	PCI_ID_VX882HR,
	PCI_ID_PCX882HR,
	PCI_ID_VX881HR,
	PCI_ID_PCX881HR,
	PCI_ID_VX882E,
	PCI_ID_PCX882E,
	PCI_ID_VX881E,
	PCI_ID_PCX881E,
	PCI_ID_VX1222HR,
	PCI_ID_PCX1222HR,
	PCI_ID_VX1221HR,
	PCI_ID_PCX1221HR,
	PCI_ID_VX1222E,
	PCI_ID_PCX1222E,
	PCI_ID_VX1221E,
	PCI_ID_PCX1221E,
	PCI_ID_VX222HR,
	PCI_ID_VX222E,
	PCI_ID_PCX22HR,
	PCI_ID_PCX22E,
	PCI_ID_VX222HRMIC,
	PCI_ID_VX222E_MIC,
	PCI_ID_PCX924HR,
	PCI_ID_PCX924E,
	PCI_ID_PCX924HRMIC,
	PCI_ID_PCX924E_MIC,
	PCI_ID_VX442HR,
	PCI_ID_PCX442HR,
	PCI_ID_VX442E,
	PCI_ID_PCX442E,
	PCI_ID_VX822HR,
	PCI_ID_PCX822HR,
	PCI_ID_VX822E,
	PCI_ID_PCX822E,
	PCI_ID_LAST
पूर्ण;

अटल स्थिर काष्ठा pci_device_id pcxhr_ids[] = अणु
	अणु 0x10b5, 0x9656, 0x1369, 0xb001, 0, 0, PCI_ID_VX882HR, पूर्ण,
	अणु 0x10b5, 0x9656, 0x1369, 0xb101, 0, 0, PCI_ID_PCX882HR, पूर्ण,
	अणु 0x10b5, 0x9656, 0x1369, 0xb201, 0, 0, PCI_ID_VX881HR, पूर्ण,
	अणु 0x10b5, 0x9656, 0x1369, 0xb301, 0, 0, PCI_ID_PCX881HR, पूर्ण,
	अणु 0x10b5, 0x9056, 0x1369, 0xb021, 0, 0, PCI_ID_VX882E, पूर्ण,
	अणु 0x10b5, 0x9056, 0x1369, 0xb121, 0, 0, PCI_ID_PCX882E, पूर्ण,
	अणु 0x10b5, 0x9056, 0x1369, 0xb221, 0, 0, PCI_ID_VX881E, पूर्ण,
	अणु 0x10b5, 0x9056, 0x1369, 0xb321, 0, 0, PCI_ID_PCX881E, पूर्ण,
	अणु 0x10b5, 0x9656, 0x1369, 0xb401, 0, 0, PCI_ID_VX1222HR, पूर्ण,
	अणु 0x10b5, 0x9656, 0x1369, 0xb501, 0, 0, PCI_ID_PCX1222HR, पूर्ण,
	अणु 0x10b5, 0x9656, 0x1369, 0xb601, 0, 0, PCI_ID_VX1221HR, पूर्ण,
	अणु 0x10b5, 0x9656, 0x1369, 0xb701, 0, 0, PCI_ID_PCX1221HR, पूर्ण,
	अणु 0x10b5, 0x9056, 0x1369, 0xb421, 0, 0, PCI_ID_VX1222E, पूर्ण,
	अणु 0x10b5, 0x9056, 0x1369, 0xb521, 0, 0, PCI_ID_PCX1222E, पूर्ण,
	अणु 0x10b5, 0x9056, 0x1369, 0xb621, 0, 0, PCI_ID_VX1221E, पूर्ण,
	अणु 0x10b5, 0x9056, 0x1369, 0xb721, 0, 0, PCI_ID_PCX1221E, पूर्ण,
	अणु 0x10b5, 0x9056, 0x1369, 0xba01, 0, 0, PCI_ID_VX222HR, पूर्ण,
	अणु 0x10b5, 0x9056, 0x1369, 0xba21, 0, 0, PCI_ID_VX222E, पूर्ण,
	अणु 0x10b5, 0x9056, 0x1369, 0xbd01, 0, 0, PCI_ID_PCX22HR, पूर्ण,
	अणु 0x10b5, 0x9056, 0x1369, 0xbd21, 0, 0, PCI_ID_PCX22E, पूर्ण,
	अणु 0x10b5, 0x9056, 0x1369, 0xbc01, 0, 0, PCI_ID_VX222HRMIC, पूर्ण,
	अणु 0x10b5, 0x9056, 0x1369, 0xbc21, 0, 0, PCI_ID_VX222E_MIC, पूर्ण,
	अणु 0x10b5, 0x9056, 0x1369, 0xbb01, 0, 0, PCI_ID_PCX924HR, पूर्ण,
	अणु 0x10b5, 0x9056, 0x1369, 0xbb21, 0, 0, PCI_ID_PCX924E, पूर्ण,
	अणु 0x10b5, 0x9056, 0x1369, 0xbf01, 0, 0, PCI_ID_PCX924HRMIC, पूर्ण,
	अणु 0x10b5, 0x9056, 0x1369, 0xbf21, 0, 0, PCI_ID_PCX924E_MIC, पूर्ण,
	अणु 0x10b5, 0x9656, 0x1369, 0xd001, 0, 0, PCI_ID_VX442HR, पूर्ण,
	अणु 0x10b5, 0x9656, 0x1369, 0xd101, 0, 0, PCI_ID_PCX442HR, पूर्ण,
	अणु 0x10b5, 0x9056, 0x1369, 0xd021, 0, 0, PCI_ID_VX442E, पूर्ण,
	अणु 0x10b5, 0x9056, 0x1369, 0xd121, 0, 0, PCI_ID_PCX442E, पूर्ण,
	अणु 0x10b5, 0x9656, 0x1369, 0xd201, 0, 0, PCI_ID_VX822HR, पूर्ण,
	अणु 0x10b5, 0x9656, 0x1369, 0xd301, 0, 0, PCI_ID_PCX822HR, पूर्ण,
	अणु 0x10b5, 0x9056, 0x1369, 0xd221, 0, 0, PCI_ID_VX822E, पूर्ण,
	अणु 0x10b5, 0x9056, 0x1369, 0xd321, 0, 0, PCI_ID_PCX822E, पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, pcxhr_ids);

काष्ठा board_parameters अणु
	अक्षर* board_name;
	लघु playback_chips;
	लघु capture_chips;
	लघु fw_file_set;
	लघु firmware_num;
पूर्ण;
अटल स्थिर काष्ठा board_parameters pcxhr_board_params[] = अणु
[PCI_ID_VX882HR] =      अणु "VX882HR",      4, 4, 0, 41 पूर्ण,
[PCI_ID_PCX882HR] =     अणु "PCX882HR",     4, 4, 0, 41 पूर्ण,
[PCI_ID_VX881HR] =      अणु "VX881HR",      4, 4, 0, 41 पूर्ण,
[PCI_ID_PCX881HR] =     अणु "PCX881HR",     4, 4, 0, 41 पूर्ण,
[PCI_ID_VX882E] =       अणु "VX882e",       4, 4, 1, 41 पूर्ण,
[PCI_ID_PCX882E] =      अणु "PCX882e",      4, 4, 1, 41 पूर्ण,
[PCI_ID_VX881E] =       अणु "VX881e",       4, 4, 1, 41 पूर्ण,
[PCI_ID_PCX881E] =      अणु "PCX881e",      4, 4, 1, 41 पूर्ण,
[PCI_ID_VX1222HR] =     अणु "VX1222HR",     6, 1, 2, 42 पूर्ण,
[PCI_ID_PCX1222HR] =    अणु "PCX1222HR",    6, 1, 2, 42 पूर्ण,
[PCI_ID_VX1221HR] =     अणु "VX1221HR",     6, 1, 2, 42 पूर्ण,
[PCI_ID_PCX1221HR] =    अणु "PCX1221HR",    6, 1, 2, 42 पूर्ण,
[PCI_ID_VX1222E] =      अणु "VX1222e",      6, 1, 3, 42 पूर्ण,
[PCI_ID_PCX1222E] =     अणु "PCX1222e",     6, 1, 3, 42 पूर्ण,
[PCI_ID_VX1221E] =      अणु "VX1221e",      6, 1, 3, 42 पूर्ण,
[PCI_ID_PCX1221E] =     अणु "PCX1221e",     6, 1, 3, 42 पूर्ण,
[PCI_ID_VX222HR] =      अणु "VX222HR",      1, 1, 4, 44 पूर्ण,
[PCI_ID_VX222E] =       अणु "VX222e",       1, 1, 4, 44 पूर्ण,
[PCI_ID_PCX22HR] =      अणु "PCX22HR",      1, 0, 4, 44 पूर्ण,
[PCI_ID_PCX22E] =       अणु "PCX22e",       1, 0, 4, 44 पूर्ण,
[PCI_ID_VX222HRMIC] =   अणु "VX222HR-Mic",  1, 1, 5, 44 पूर्ण,
[PCI_ID_VX222E_MIC] =   अणु "VX222e-Mic",   1, 1, 5, 44 पूर्ण,
[PCI_ID_PCX924HR] =     अणु "PCX924HR",     1, 1, 5, 44 पूर्ण,
[PCI_ID_PCX924E] =      अणु "PCX924e",      1, 1, 5, 44 पूर्ण,
[PCI_ID_PCX924HRMIC] =  अणु "PCX924HR-Mic", 1, 1, 5, 44 पूर्ण,
[PCI_ID_PCX924E_MIC] =  अणु "PCX924e-Mic",  1, 1, 5, 44 पूर्ण,
[PCI_ID_VX442HR] =      अणु "VX442HR",      2, 2, 0, 41 पूर्ण,
[PCI_ID_PCX442HR] =     अणु "PCX442HR",     2, 2, 0, 41 पूर्ण,
[PCI_ID_VX442E] =       अणु "VX442e",       2, 2, 1, 41 पूर्ण,
[PCI_ID_PCX442E] =      अणु "PCX442e",      2, 2, 1, 41 पूर्ण,
[PCI_ID_VX822HR] =      अणु "VX822HR",      4, 1, 2, 42 पूर्ण,
[PCI_ID_PCX822HR] =     अणु "PCX822HR",     4, 1, 2, 42 पूर्ण,
[PCI_ID_VX822E] =       अणु "VX822e",       4, 1, 3, 42 पूर्ण,
[PCI_ID_PCX822E] =      अणु "PCX822e",      4, 1, 3, 42 पूर्ण,
पूर्ण;

/* boards without hw AES1 and SRC onboard are all using fw_file_set==4 */
/* VX222HR, VX222e, PCX22HR and PCX22e */
#घोषणा PCXHR_BOARD_HAS_AES1(x) (x->fw_file_set != 4)
/* some boards करो not support 192kHz on digital AES input plugs */
#घोषणा PCXHR_BOARD_AESIN_NO_192K(x) ((x->capture_chips == 0) || \
				      (x->fw_file_set == 0)   || \
				      (x->fw_file_set == 2))

अटल पूर्णांक pcxhr_pll_freq_रेजिस्टर(अचिन्हित पूर्णांक freq, अचिन्हित पूर्णांक* pllreg,
				   अचिन्हित पूर्णांक* realfreq)
अणु
	अचिन्हित पूर्णांक reg;

	अगर (freq < 6900 || freq > 110000)
		वापस -EINVAL;
	reg = (28224000 * 2) / freq;
	reg = (reg - 1) / 2;
	अगर (reg < 0x200)
		*pllreg = reg + 0x800;
	अन्यथा अगर (reg < 0x400)
		*pllreg = reg & 0x1ff;
	अन्यथा अगर (reg < 0x800) अणु
		*pllreg = ((reg >> 1) & 0x1ff) + 0x200;
		reg &= ~1;
	पूर्ण अन्यथा अणु
		*pllreg = ((reg >> 2) & 0x1ff) + 0x400;
		reg &= ~3;
	पूर्ण
	अगर (realfreq)
		*realfreq = (28224000 / (reg + 1));
	वापस 0;
पूर्ण


#घोषणा PCXHR_FREQ_REG_MASK		0x1f
#घोषणा PCXHR_FREQ_QUARTZ_48000		0x00
#घोषणा PCXHR_FREQ_QUARTZ_24000		0x01
#घोषणा PCXHR_FREQ_QUARTZ_12000		0x09
#घोषणा PCXHR_FREQ_QUARTZ_32000		0x08
#घोषणा PCXHR_FREQ_QUARTZ_16000		0x04
#घोषणा PCXHR_FREQ_QUARTZ_8000		0x0c
#घोषणा PCXHR_FREQ_QUARTZ_44100		0x02
#घोषणा PCXHR_FREQ_QUARTZ_22050		0x0a
#घोषणा PCXHR_FREQ_QUARTZ_11025		0x06
#घोषणा PCXHR_FREQ_PLL			0x05
#घोषणा PCXHR_FREQ_QUARTZ_192000	0x10
#घोषणा PCXHR_FREQ_QUARTZ_96000		0x18
#घोषणा PCXHR_FREQ_QUARTZ_176400	0x14
#घोषणा PCXHR_FREQ_QUARTZ_88200		0x1c
#घोषणा PCXHR_FREQ_QUARTZ_128000	0x12
#घोषणा PCXHR_FREQ_QUARTZ_64000		0x1a

#घोषणा PCXHR_FREQ_WORD_CLOCK		0x0f
#घोषणा PCXHR_FREQ_SYNC_AES		0x0e
#घोषणा PCXHR_FREQ_AES_1		0x07
#घोषणा PCXHR_FREQ_AES_2		0x0b
#घोषणा PCXHR_FREQ_AES_3		0x03
#घोषणा PCXHR_FREQ_AES_4		0x0d

अटल पूर्णांक pcxhr_get_घड़ी_reg(काष्ठा pcxhr_mgr *mgr, अचिन्हित पूर्णांक rate,
			       अचिन्हित पूर्णांक *reg, अचिन्हित पूर्णांक *freq)
अणु
	अचिन्हित पूर्णांक val, realfreq, pllreg;
	काष्ठा pcxhr_rmh rmh;
	पूर्णांक err;

	realfreq = rate;
	चयन (mgr->use_घड़ी_प्रकारype) अणु
	हाल PCXHR_CLOCK_TYPE_INTERNAL :	/* घड़ी by quartz or pll */
		चयन (rate) अणु
		हाल 48000 :	val = PCXHR_FREQ_QUARTZ_48000;	अवरोध;
		हाल 24000 :	val = PCXHR_FREQ_QUARTZ_24000;	अवरोध;
		हाल 12000 :	val = PCXHR_FREQ_QUARTZ_12000;	अवरोध;
		हाल 32000 :	val = PCXHR_FREQ_QUARTZ_32000;	अवरोध;
		हाल 16000 :	val = PCXHR_FREQ_QUARTZ_16000;	अवरोध;
		हाल 8000 :	val = PCXHR_FREQ_QUARTZ_8000;	अवरोध;
		हाल 44100 :	val = PCXHR_FREQ_QUARTZ_44100;	अवरोध;
		हाल 22050 :	val = PCXHR_FREQ_QUARTZ_22050;	अवरोध;
		हाल 11025 :	val = PCXHR_FREQ_QUARTZ_11025;	अवरोध;
		हाल 192000 :	val = PCXHR_FREQ_QUARTZ_192000;	अवरोध;
		हाल 96000 :	val = PCXHR_FREQ_QUARTZ_96000;	अवरोध;
		हाल 176400 :	val = PCXHR_FREQ_QUARTZ_176400;	अवरोध;
		हाल 88200 :	val = PCXHR_FREQ_QUARTZ_88200;	अवरोध;
		हाल 128000 :	val = PCXHR_FREQ_QUARTZ_128000;	अवरोध;
		हाल 64000 :	val = PCXHR_FREQ_QUARTZ_64000;	अवरोध;
		शेष :
			val = PCXHR_FREQ_PLL;
			/* get the value क्रम the pll रेजिस्टर */
			err = pcxhr_pll_freq_रेजिस्टर(rate, &pllreg, &realfreq);
			अगर (err)
				वापस err;
			pcxhr_init_rmh(&rmh, CMD_ACCESS_IO_WRITE);
			rmh.cmd[0] |= IO_NUM_REG_GENCLK;
			rmh.cmd[1]  = pllreg & MASK_DSP_WORD;
			rmh.cmd[2]  = pllreg >> 24;
			rmh.cmd_len = 3;
			err = pcxhr_send_msg(mgr, &rmh);
			अगर (err < 0) अणु
				dev_err(&mgr->pci->dev,
					   "error CMD_ACCESS_IO_WRITE "
					   "for PLL register : %x!\n", err);
				वापस err;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल PCXHR_CLOCK_TYPE_WORD_CLOCK:
		val = PCXHR_FREQ_WORD_CLOCK;
		अवरोध;
	हाल PCXHR_CLOCK_TYPE_AES_SYNC:
		val = PCXHR_FREQ_SYNC_AES;
		अवरोध;
	हाल PCXHR_CLOCK_TYPE_AES_1:
		val = PCXHR_FREQ_AES_1;
		अवरोध;
	हाल PCXHR_CLOCK_TYPE_AES_2:
		val = PCXHR_FREQ_AES_2;
		अवरोध;
	हाल PCXHR_CLOCK_TYPE_AES_3:
		val = PCXHR_FREQ_AES_3;
		अवरोध;
	हाल PCXHR_CLOCK_TYPE_AES_4:
		val = PCXHR_FREQ_AES_4;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	*reg = val;
	*freq = realfreq;
	वापस 0;
पूर्ण


अटल पूर्णांक pcxhr_sub_set_घड़ी(काष्ठा pcxhr_mgr *mgr,
			       अचिन्हित पूर्णांक rate,
			       पूर्णांक *changed)
अणु
	अचिन्हित पूर्णांक val, realfreq, speed;
	काष्ठा pcxhr_rmh rmh;
	पूर्णांक err;

	err = pcxhr_get_घड़ी_reg(mgr, rate, &val, &realfreq);
	अगर (err)
		वापस err;

	/* codec speed modes */
	अगर (rate < 55000)
		speed = 0;	/* single speed */
	अन्यथा अगर (rate < 100000)
		speed = 1;	/* dual speed */
	अन्यथा
		speed = 2;	/* quad speed */
	अगर (mgr->codec_speed != speed) अणु
		pcxhr_init_rmh(&rmh, CMD_ACCESS_IO_WRITE); /* mute outमाला_दो */
		rmh.cmd[0] |= IO_NUM_REG_MUTE_OUT;
		अगर (DSP_EXT_CMD_SET(mgr)) अणु
			rmh.cmd[1]  = 1;
			rmh.cmd_len = 2;
		पूर्ण
		err = pcxhr_send_msg(mgr, &rmh);
		अगर (err)
			वापस err;

		pcxhr_init_rmh(&rmh, CMD_ACCESS_IO_WRITE); /* set speed ratio */
		rmh.cmd[0] |= IO_NUM_SPEED_RATIO;
		rmh.cmd[1] = speed;
		rmh.cmd_len = 2;
		err = pcxhr_send_msg(mgr, &rmh);
		अगर (err)
			वापस err;
	पूर्ण
	/* set the new frequency */
	dev_dbg(&mgr->pci->dev, "clock register : set %x\n", val);
	err = pcxhr_ग_लिखो_io_num_reg_cont(mgr, PCXHR_FREQ_REG_MASK,
					  val, changed);
	अगर (err)
		वापस err;

	mgr->sample_rate_real = realfreq;
	mgr->cur_घड़ी_प्रकारype = mgr->use_घड़ी_प्रकारype;

	/* unmute after codec speed modes */
	अगर (mgr->codec_speed != speed) अणु
		pcxhr_init_rmh(&rmh, CMD_ACCESS_IO_READ); /* unmute outमाला_दो */
		rmh.cmd[0] |= IO_NUM_REG_MUTE_OUT;
		अगर (DSP_EXT_CMD_SET(mgr)) अणु
			rmh.cmd[1]  = 1;
			rmh.cmd_len = 2;
		पूर्ण
		err = pcxhr_send_msg(mgr, &rmh);
		अगर (err)
			वापस err;
		mgr->codec_speed = speed;	/* save new codec speed */
	पूर्ण

	dev_dbg(&mgr->pci->dev, "pcxhr_sub_set_clock to %dHz (realfreq=%d)\n",
		    rate, realfreq);
	वापस 0;
पूर्ण

#घोषणा PCXHR_MODIFY_CLOCK_S_BIT	0x04

#घोषणा PCXHR_IRQ_TIMER_FREQ		92000
#घोषणा PCXHR_IRQ_TIMER_PERIOD		48

पूर्णांक pcxhr_set_घड़ी(काष्ठा pcxhr_mgr *mgr, अचिन्हित पूर्णांक rate)
अणु
	काष्ठा pcxhr_rmh rmh;
	पूर्णांक err, changed;

	अगर (rate == 0)
		वापस 0; /* nothing to करो */

	अगर (mgr->is_hr_stereo)
		err = hr222_sub_set_घड़ी(mgr, rate, &changed);
	अन्यथा
		err = pcxhr_sub_set_घड़ी(mgr, rate, &changed);

	अगर (err)
		वापस err;

	अगर (changed) अणु
		pcxhr_init_rmh(&rmh, CMD_MODIFY_CLOCK);
		rmh.cmd[0] |= PCXHR_MODIFY_CLOCK_S_BIT; /* resync fअगरos  */
		अगर (rate < PCXHR_IRQ_TIMER_FREQ)
			rmh.cmd[1] = PCXHR_IRQ_TIMER_PERIOD;
		अन्यथा
			rmh.cmd[1] = PCXHR_IRQ_TIMER_PERIOD * 2;
		rmh.cmd[2] = rate;
		rmh.cmd_len = 3;
		err = pcxhr_send_msg(mgr, &rmh);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक pcxhr_sub_get_बाह्यal_घड़ी(काष्ठा pcxhr_mgr *mgr,
					क्रमागत pcxhr_घड़ी_प्रकारype घड़ी_प्रकारype,
					पूर्णांक *sample_rate)
अणु
	काष्ठा pcxhr_rmh rmh;
	अचिन्हित अक्षर reg;
	पूर्णांक err, rate;

	चयन (घड़ी_प्रकारype) अणु
	हाल PCXHR_CLOCK_TYPE_WORD_CLOCK:
		reg = REG_STATUS_WORD_CLOCK;
		अवरोध;
	हाल PCXHR_CLOCK_TYPE_AES_SYNC:
		reg = REG_STATUS_AES_SYNC;
		अवरोध;
	हाल PCXHR_CLOCK_TYPE_AES_1:
		reg = REG_STATUS_AES_1;
		अवरोध;
	हाल PCXHR_CLOCK_TYPE_AES_2:
		reg = REG_STATUS_AES_2;
		अवरोध;
	हाल PCXHR_CLOCK_TYPE_AES_3:
		reg = REG_STATUS_AES_3;
		अवरोध;
	हाल PCXHR_CLOCK_TYPE_AES_4:
		reg = REG_STATUS_AES_4;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	pcxhr_init_rmh(&rmh, CMD_ACCESS_IO_READ);
	rmh.cmd_len = 2;
	rmh.cmd[0] |= IO_NUM_REG_STATUS;
	अगर (mgr->last_reg_stat != reg) अणु
		rmh.cmd[1]  = reg;
		err = pcxhr_send_msg(mgr, &rmh);
		अगर (err)
			वापस err;
		udelay(100);	/* रुको minimum 2 sample_frames at 32kHz ! */
		mgr->last_reg_stat = reg;
	पूर्ण
	rmh.cmd[1]  = REG_STATUS_CURRENT;
	err = pcxhr_send_msg(mgr, &rmh);
	अगर (err)
		वापस err;
	चयन (rmh.stat[1] & 0x0f) अणु
	हाल REG_STATUS_SYNC_32000 :	rate = 32000; अवरोध;
	हाल REG_STATUS_SYNC_44100 :	rate = 44100; अवरोध;
	हाल REG_STATUS_SYNC_48000 :	rate = 48000; अवरोध;
	हाल REG_STATUS_SYNC_64000 :	rate = 64000; अवरोध;
	हाल REG_STATUS_SYNC_88200 :	rate = 88200; अवरोध;
	हाल REG_STATUS_SYNC_96000 :	rate = 96000; अवरोध;
	हाल REG_STATUS_SYNC_128000 :	rate = 128000; अवरोध;
	हाल REG_STATUS_SYNC_176400 :	rate = 176400; अवरोध;
	हाल REG_STATUS_SYNC_192000 :	rate = 192000; अवरोध;
	शेष: rate = 0;
	पूर्ण
	dev_dbg(&mgr->pci->dev, "External clock is at %d Hz\n", rate);
	*sample_rate = rate;
	वापस 0;
पूर्ण


पूर्णांक pcxhr_get_बाह्यal_घड़ी(काष्ठा pcxhr_mgr *mgr,
			     क्रमागत pcxhr_घड़ी_प्रकारype घड़ी_प्रकारype,
			     पूर्णांक *sample_rate)
अणु
	अगर (mgr->is_hr_stereo)
		वापस hr222_get_बाह्यal_घड़ी(mgr, घड़ी_प्रकारype,
						sample_rate);
	अन्यथा
		वापस pcxhr_sub_get_बाह्यal_घड़ी(mgr, घड़ी_प्रकारype,
						    sample_rate);
पूर्ण

/*
 *  start or stop playback/capture substream
 */
अटल पूर्णांक pcxhr_set_stream_state(काष्ठा snd_pcxhr *chip,
				  काष्ठा pcxhr_stream *stream)
अणु
	पूर्णांक err;
	काष्ठा pcxhr_rmh rmh;
	पूर्णांक stream_mask, start;

	अगर (stream->status == PCXHR_STREAM_STATUS_SCHEDULE_RUN)
		start = 1;
	अन्यथा अणु
		अगर (stream->status != PCXHR_STREAM_STATUS_SCHEDULE_STOP) अणु
			dev_err(chip->card->dev,
				"pcxhr_set_stream_state CANNOT be stopped\n");
			वापस -EINVAL;
		पूर्ण
		start = 0;
	पूर्ण
	अगर (!stream->substream)
		वापस -EINVAL;

	stream->समयr_असल_periods = 0;
	stream->समयr_period_frag = 0;	/* reset theoretical stream pos */
	stream->समयr_buf_periods = 0;
	stream->समयr_is_synced = 0;

	stream_mask =
	  stream->pipe->is_capture ? 1 : 1<<stream->substream->number;

	pcxhr_init_rmh(&rmh, start ? CMD_START_STREAM : CMD_STOP_STREAM);
	pcxhr_set_pipe_cmd_params(&rmh, stream->pipe->is_capture,
				  stream->pipe->first_audio, 0, stream_mask);

	chip = snd_pcm_substream_chip(stream->substream);

	err = pcxhr_send_msg(chip->mgr, &rmh);
	अगर (err)
		dev_err(chip->card->dev,
			"ERROR pcxhr_set_stream_state err=%x;\n", err);
	stream->status =
	  start ? PCXHR_STREAM_STATUS_STARTED : PCXHR_STREAM_STATUS_STOPPED;
	वापस err;
पूर्ण

#घोषणा HEADER_FMT_BASE_LIN		0xfed00000
#घोषणा HEADER_FMT_BASE_FLOAT		0xfad00000
#घोषणा HEADER_FMT_INTEL		0x00008000
#घोषणा HEADER_FMT_24BITS		0x00004000
#घोषणा HEADER_FMT_16BITS		0x00002000
#घोषणा HEADER_FMT_UPTO11		0x00000200
#घोषणा HEADER_FMT_UPTO32		0x00000100
#घोषणा HEADER_FMT_MONO			0x00000080

अटल पूर्णांक pcxhr_set_क्रमmat(काष्ठा pcxhr_stream *stream)
अणु
	पूर्णांक err, is_capture, sample_rate, stream_num;
	काष्ठा snd_pcxhr *chip;
	काष्ठा pcxhr_rmh rmh;
	अचिन्हित पूर्णांक header;

	chip = snd_pcm_substream_chip(stream->substream);
	चयन (stream->क्रमmat) अणु
	हाल SNDRV_PCM_FORMAT_U8:
		header = HEADER_FMT_BASE_LIN;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_LE:
		header = HEADER_FMT_BASE_LIN |
			 HEADER_FMT_16BITS | HEADER_FMT_INTEL;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_BE:
		header = HEADER_FMT_BASE_LIN | HEADER_FMT_16BITS;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_3LE:
		header = HEADER_FMT_BASE_LIN |
			 HEADER_FMT_24BITS | HEADER_FMT_INTEL;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_3BE:
		header = HEADER_FMT_BASE_LIN | HEADER_FMT_24BITS;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_FLOAT_LE:
		header = HEADER_FMT_BASE_FLOAT | HEADER_FMT_INTEL;
		अवरोध;
	शेष:
		dev_err(chip->card->dev,
			"error pcxhr_set_format() : unknown format\n");
		वापस -EINVAL;
	पूर्ण

	sample_rate = chip->mgr->sample_rate;
	अगर (sample_rate <= 32000 && sample_rate !=0) अणु
		अगर (sample_rate <= 11025)
			header |= HEADER_FMT_UPTO11;
		अन्यथा
			header |= HEADER_FMT_UPTO32;
	पूर्ण
	अगर (stream->channels == 1)
		header |= HEADER_FMT_MONO;

	is_capture = stream->pipe->is_capture;
	stream_num = is_capture ? 0 : stream->substream->number;

	pcxhr_init_rmh(&rmh, is_capture ?
		       CMD_FORMAT_STREAM_IN : CMD_FORMAT_STREAM_OUT);
	pcxhr_set_pipe_cmd_params(&rmh, is_capture, stream->pipe->first_audio,
				  stream_num, 0);
	अगर (is_capture) अणु
		/* bug with old dsp versions: */
		/* bit 12 also sets the क्रमmat of the playback stream */
		अगर (DSP_EXT_CMD_SET(chip->mgr))
			rmh.cmd[0] |= 1<<10;
		अन्यथा
			rmh.cmd[0] |= 1<<12;
	पूर्ण
	rmh.cmd[1] = 0;
	rmh.cmd_len = 2;
	अगर (DSP_EXT_CMD_SET(chip->mgr)) अणु
		/* add channels and set bit 19 अगर channels>2 */
		rmh.cmd[1] = stream->channels;
		अगर (!is_capture) अणु
			/* playback : add channel mask to command */
			rmh.cmd[2] = (stream->channels == 1) ? 0x01 : 0x03;
			rmh.cmd_len = 3;
		पूर्ण
	पूर्ण
	rmh.cmd[rmh.cmd_len++] = header >> 8;
	rmh.cmd[rmh.cmd_len++] = (header & 0xff) << 16;
	err = pcxhr_send_msg(chip->mgr, &rmh);
	अगर (err)
		dev_err(chip->card->dev,
			"ERROR pcxhr_set_format err=%x;\n", err);
	वापस err;
पूर्ण

अटल पूर्णांक pcxhr_update_r_buffer(काष्ठा pcxhr_stream *stream)
अणु
	पूर्णांक err, is_capture, stream_num;
	काष्ठा pcxhr_rmh rmh;
	काष्ठा snd_pcm_substream *subs = stream->substream;
	काष्ठा snd_pcxhr *chip = snd_pcm_substream_chip(subs);

	is_capture = (subs->stream == SNDRV_PCM_STREAM_CAPTURE);
	stream_num = is_capture ? 0 : subs->number;

	dev_dbg(chip->card->dev,
		"pcxhr_update_r_buffer(pcm%c%d) : addr(%p) bytes(%zx) subs(%d)\n",
		is_capture ? 'c' : 'p',
		chip->chip_idx, (व्योम *)(दीर्घ)subs->runसमय->dma_addr,
		subs->runसमय->dma_bytes, subs->number);

	pcxhr_init_rmh(&rmh, CMD_UPDATE_R_BUFFERS);
	pcxhr_set_pipe_cmd_params(&rmh, is_capture, stream->pipe->first_audio,
				  stream_num, 0);

	/* max buffer size is 2 MByte */
	snd_BUG_ON(subs->runसमय->dma_bytes >= 0x200000);
	/* size in bits */
	rmh.cmd[1] = subs->runसमय->dma_bytes * 8;
	/* most signअगरicant byte */
	rmh.cmd[2] = subs->runसमय->dma_addr >> 24;
	/* this is a circular buffer */
	rmh.cmd[2] |= 1<<19;
	/* least 3 signअगरicant bytes */
	rmh.cmd[3] = subs->runसमय->dma_addr & MASK_DSP_WORD;
	rmh.cmd_len = 4;
	err = pcxhr_send_msg(chip->mgr, &rmh);
	अगर (err)
		dev_err(chip->card->dev,
			   "ERROR CMD_UPDATE_R_BUFFERS err=%x;\n", err);
	वापस err;
पूर्ण


#अगर 0
अटल पूर्णांक pcxhr_pipe_sample_count(काष्ठा pcxhr_stream *stream,
				   snd_pcm_uframes_t *sample_count)
अणु
	काष्ठा pcxhr_rmh rmh;
	पूर्णांक err;
	pcxhr_t *chip = snd_pcm_substream_chip(stream->substream);
	pcxhr_init_rmh(&rmh, CMD_PIPE_SAMPLE_COUNT);
	pcxhr_set_pipe_cmd_params(&rmh, stream->pipe->is_capture, 0, 0,
				  1<<stream->pipe->first_audio);
	err = pcxhr_send_msg(chip->mgr, &rmh);
	अगर (err == 0) अणु
		*sample_count = ((snd_pcm_uframes_t)rmh.stat[0]) << 24;
		*sample_count += (snd_pcm_uframes_t)rmh.stat[1];
	पूर्ण
	dev_dbg(chip->card->dev, "PIPE_SAMPLE_COUNT = %lx\n", *sample_count);
	वापस err;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक pcxhr_stream_scheduled_get_pipe(काष्ठा pcxhr_stream *stream,
						  काष्ठा pcxhr_pipe **pipe)
अणु
	अगर (stream->status == PCXHR_STREAM_STATUS_SCHEDULE_RUN) अणु
		*pipe = stream->pipe;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम pcxhr_start_linked_stream(काष्ठा pcxhr_mgr *mgr)
अणु
	पूर्णांक i, j, err;
	काष्ठा pcxhr_pipe *pipe;
	काष्ठा snd_pcxhr *chip;
	पूर्णांक capture_mask = 0;
	पूर्णांक playback_mask = 0;

#अगर_घोषित CONFIG_SND_DEBUG_VERBOSE
	kसमय_प्रकार start_समय, stop_समय, dअगरf_समय;

	start_समय = kसमय_get();
#पूर्ण_अगर
	mutex_lock(&mgr->setup_mutex);

	/* check the pipes concerned and build pipe_array */
	क्रम (i = 0; i < mgr->num_cards; i++) अणु
		chip = mgr->chip[i];
		क्रम (j = 0; j < chip->nb_streams_capt; j++) अणु
			अगर (pcxhr_stream_scheduled_get_pipe(&chip->capture_stream[j], &pipe))
				capture_mask |= (1 << pipe->first_audio);
		पूर्ण
		क्रम (j = 0; j < chip->nb_streams_play; j++) अणु
			अगर (pcxhr_stream_scheduled_get_pipe(&chip->playback_stream[j], &pipe)) अणु
				playback_mask |= (1 << pipe->first_audio);
				अवरोध;	/* add only once, as all playback
					 * streams of one chip use the same pipe
					 */
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (capture_mask == 0 && playback_mask == 0) अणु
		mutex_unlock(&mgr->setup_mutex);
		dev_err(&mgr->pci->dev, "pcxhr_start_linked_stream : no pipes\n");
		वापस;
	पूर्ण

	dev_dbg(&mgr->pci->dev, "pcxhr_start_linked_stream : "
		    "playback_mask=%x capture_mask=%x\n",
		    playback_mask, capture_mask);

	/* synchronous stop of all the pipes concerned */
	err = pcxhr_set_pipe_state(mgr,  playback_mask, capture_mask, 0);
	अगर (err) अणु
		mutex_unlock(&mgr->setup_mutex);
		dev_err(&mgr->pci->dev, "pcxhr_start_linked_stream : "
			   "error stop pipes (P%x C%x)\n",
			   playback_mask, capture_mask);
		वापस;
	पूर्ण

	/* the dsp lost क्रमmat and buffer info with the stop pipe */
	क्रम (i = 0; i < mgr->num_cards; i++) अणु
		काष्ठा pcxhr_stream *stream;
		chip = mgr->chip[i];
		क्रम (j = 0; j < chip->nb_streams_capt; j++) अणु
			stream = &chip->capture_stream[j];
			अगर (pcxhr_stream_scheduled_get_pipe(stream, &pipe)) अणु
				err = pcxhr_set_क्रमmat(stream);
				err = pcxhr_update_r_buffer(stream);
			पूर्ण
		पूर्ण
		क्रम (j = 0; j < chip->nb_streams_play; j++) अणु
			stream = &chip->playback_stream[j];
			अगर (pcxhr_stream_scheduled_get_pipe(stream, &pipe)) अणु
				err = pcxhr_set_क्रमmat(stream);
				err = pcxhr_update_r_buffer(stream);
			पूर्ण
		पूर्ण
	पूर्ण
	/* start all the streams */
	क्रम (i = 0; i < mgr->num_cards; i++) अणु
		काष्ठा pcxhr_stream *stream;
		chip = mgr->chip[i];
		क्रम (j = 0; j < chip->nb_streams_capt; j++) अणु
			stream = &chip->capture_stream[j];
			अगर (pcxhr_stream_scheduled_get_pipe(stream, &pipe))
				err = pcxhr_set_stream_state(chip, stream);
		पूर्ण
		क्रम (j = 0; j < chip->nb_streams_play; j++) अणु
			stream = &chip->playback_stream[j];
			अगर (pcxhr_stream_scheduled_get_pipe(stream, &pipe))
				err = pcxhr_set_stream_state(chip, stream);
		पूर्ण
	पूर्ण

	/* synchronous start of all the pipes concerned */
	err = pcxhr_set_pipe_state(mgr, playback_mask, capture_mask, 1);
	अगर (err) अणु
		mutex_unlock(&mgr->setup_mutex);
		dev_err(&mgr->pci->dev, "pcxhr_start_linked_stream : "
			   "error start pipes (P%x C%x)\n",
			   playback_mask, capture_mask);
		वापस;
	पूर्ण

	/* put the streams पूर्णांकo the running state now
	 * (increment poपूर्णांकer by पूर्णांकerrupt)
	 */
	mutex_lock(&mgr->lock);
	क्रम ( i =0; i < mgr->num_cards; i++) अणु
		काष्ठा pcxhr_stream *stream;
		chip = mgr->chip[i];
		क्रम(j = 0; j < chip->nb_streams_capt; j++) अणु
			stream = &chip->capture_stream[j];
			अगर(stream->status == PCXHR_STREAM_STATUS_STARTED)
				stream->status = PCXHR_STREAM_STATUS_RUNNING;
		पूर्ण
		क्रम (j = 0; j < chip->nb_streams_play; j++) अणु
			stream = &chip->playback_stream[j];
			अगर (stream->status == PCXHR_STREAM_STATUS_STARTED) अणु
				/* playback will alपढ़ोy have advanced ! */
				stream->समयr_period_frag += mgr->granularity;
				stream->status = PCXHR_STREAM_STATUS_RUNNING;
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&mgr->lock);

	mutex_unlock(&mgr->setup_mutex);

#अगर_घोषित CONFIG_SND_DEBUG_VERBOSE
	stop_समय = kसमय_get();
	dअगरf_समय = kसमय_sub(stop_समय, start_समय);
	dev_dbg(&mgr->pci->dev, "***TRIGGER START*** TIME = %ld (err = %x)\n",
		    (दीर्घ)(kसमय_प्रकारo_ns(dअगरf_समय)), err);
#पूर्ण_अगर
पूर्ण


/*
 *  trigger callback
 */
अटल पूर्णांक pcxhr_trigger(काष्ठा snd_pcm_substream *subs, पूर्णांक cmd)
अणु
	काष्ठा pcxhr_stream *stream;
	काष्ठा snd_pcm_substream *s;
	काष्ठा snd_pcxhr *chip = snd_pcm_substream_chip(subs);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		dev_dbg(chip->card->dev, "SNDRV_PCM_TRIGGER_START\n");
		अगर (snd_pcm_stream_linked(subs)) अणु
			snd_pcm_group_क्रम_each_entry(s, subs) अणु
				अगर (snd_pcm_substream_chip(s) != chip)
					जारी;
				stream = s->runसमय->निजी_data;
				stream->status =
					PCXHR_STREAM_STATUS_SCHEDULE_RUN;
				snd_pcm_trigger_करोne(s, subs);
			पूर्ण
			pcxhr_start_linked_stream(chip->mgr);
		पूर्ण अन्यथा अणु
			stream = subs->runसमय->निजी_data;
			dev_dbg(chip->card->dev, "Only one Substream %c %d\n",
				    stream->pipe->is_capture ? 'C' : 'P',
				    stream->pipe->first_audio);
			अगर (pcxhr_set_क्रमmat(stream))
				वापस -EINVAL;
			अगर (pcxhr_update_r_buffer(stream))
				वापस -EINVAL;

			stream->status = PCXHR_STREAM_STATUS_SCHEDULE_RUN;
			अगर (pcxhr_set_stream_state(chip, stream))
				वापस -EINVAL;
			stream->status = PCXHR_STREAM_STATUS_RUNNING;
		पूर्ण
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		dev_dbg(chip->card->dev, "SNDRV_PCM_TRIGGER_STOP\n");
		snd_pcm_group_क्रम_each_entry(s, subs) अणु
			stream = s->runसमय->निजी_data;
			stream->status = PCXHR_STREAM_STATUS_SCHEDULE_STOP;
			अगर (pcxhr_set_stream_state(chip, stream))
				वापस -EINVAL;
			snd_pcm_trigger_करोne(s, subs);
		पूर्ण
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		/* TODO */
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक pcxhr_hardware_समयr(काष्ठा pcxhr_mgr *mgr, पूर्णांक start)
अणु
	काष्ठा pcxhr_rmh rmh;
	पूर्णांक err;

	pcxhr_init_rmh(&rmh, CMD_SET_TIMER_INTERRUPT);
	अगर (start) अणु
		/* last dsp समय invalid */
		mgr->dsp_समय_last = PCXHR_DSP_TIME_INVALID;
		rmh.cmd[0] |= mgr->granularity;
	पूर्ण
	err = pcxhr_send_msg(mgr, &rmh);
	अगर (err < 0)
		dev_err(&mgr->pci->dev, "error pcxhr_hardware_timer err(%x)\n",
			   err);
	वापस err;
पूर्ण

/*
 *  prepare callback क्रम all pcms
 */
अटल पूर्णांक pcxhr_prepare(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_pcxhr *chip = snd_pcm_substream_chip(subs);
	काष्ठा pcxhr_mgr *mgr = chip->mgr;
	पूर्णांक err = 0;

	dev_dbg(chip->card->dev,
		"pcxhr_prepare : period_size(%lx) periods(%x) buffer_size(%lx)\n",
		    subs->runसमय->period_size, subs->runसमय->periods,
		    subs->runसमय->buffer_size);

	mutex_lock(&mgr->setup_mutex);

	करो अणु
		/* only the first stream can choose the sample rate */
		/* set the घड़ी only once (first stream) */
		अगर (mgr->sample_rate != subs->runसमय->rate) अणु
			err = pcxhr_set_घड़ी(mgr, subs->runसमय->rate);
			अगर (err)
				अवरोध;
			अगर (mgr->sample_rate == 0)
				/* start the DSP-समयr */
				err = pcxhr_hardware_समयr(mgr, 1);
			mgr->sample_rate = subs->runसमय->rate;
		पूर्ण
	पूर्ण जबतक(0);	/* करो only once (so we can use अवरोध instead of जाओ) */

	mutex_unlock(&mgr->setup_mutex);

	वापस err;
पूर्ण


/*
 *  HW_PARAMS callback क्रम all pcms
 */
अटल पूर्णांक pcxhr_hw_params(काष्ठा snd_pcm_substream *subs,
			   काष्ठा snd_pcm_hw_params *hw)
अणु
	काष्ठा snd_pcxhr *chip = snd_pcm_substream_chip(subs);
	काष्ठा pcxhr_mgr *mgr = chip->mgr;
	काष्ठा pcxhr_stream *stream = subs->runसमय->निजी_data;

	mutex_lock(&mgr->setup_mutex);

	/* set up channels */
	stream->channels = params_channels(hw);
	/* set up क्रमmat क्रम the stream */
	stream->क्रमmat = params_क्रमmat(hw);

	mutex_unlock(&mgr->setup_mutex);

	वापस 0;
पूर्ण


/*
 *  CONFIGURATION SPACE क्रम all pcms, mono pcm must update channels_max
 */
अटल स्थिर काष्ठा snd_pcm_hardware pcxhr_caps =
अणु
	.info             = (SNDRV_PCM_INFO_MMAP |
			     SNDRV_PCM_INFO_INTERLEAVED |
			     SNDRV_PCM_INFO_MMAP_VALID |
			     SNDRV_PCM_INFO_SYNC_START),
	.क्रमmats	  = (SNDRV_PCM_FMTBIT_U8 |
			     SNDRV_PCM_FMTBIT_S16_LE |
			     SNDRV_PCM_FMTBIT_S16_BE |
			     SNDRV_PCM_FMTBIT_S24_3LE |
			     SNDRV_PCM_FMTBIT_S24_3BE |
			     SNDRV_PCM_FMTBIT_FLOAT_LE),
	.rates            = (SNDRV_PCM_RATE_CONTINUOUS |
			     SNDRV_PCM_RATE_8000_192000),
	.rate_min         = 8000,
	.rate_max         = 192000,
	.channels_min     = 1,
	.channels_max     = 2,
	.buffer_bytes_max = (32*1024),
	/* 1 byte == 1 frame U8 mono (PCXHR_GRANULARITY is frames!) */
	.period_bytes_min = (2*PCXHR_GRANULARITY),
	.period_bytes_max = (16*1024),
	.periods_min      = 2,
	.periods_max      = (32*1024/PCXHR_GRANULARITY),
पूर्ण;


अटल पूर्णांक pcxhr_खोलो(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_pcxhr       *chip = snd_pcm_substream_chip(subs);
	काष्ठा pcxhr_mgr       *mgr = chip->mgr;
	काष्ठा snd_pcm_runसमय *runसमय = subs->runसमय;
	काष्ठा pcxhr_stream    *stream;
	पूर्णांक err;

	mutex_lock(&mgr->setup_mutex);

	/* copy the काष्ठा snd_pcm_hardware काष्ठा */
	runसमय->hw = pcxhr_caps;

	अगर( subs->stream == SNDRV_PCM_STREAM_PLAYBACK ) अणु
		dev_dbg(chip->card->dev, "pcxhr_open playback chip%d subs%d\n",
			    chip->chip_idx, subs->number);
		stream = &chip->playback_stream[subs->number];
	पूर्ण अन्यथा अणु
		dev_dbg(chip->card->dev, "pcxhr_open capture chip%d subs%d\n",
			    chip->chip_idx, subs->number);
		अगर (mgr->mono_capture)
			runसमय->hw.channels_max = 1;
		अन्यथा
			runसमय->hw.channels_min = 2;
		stream = &chip->capture_stream[subs->number];
	पूर्ण
	अगर (stream->status != PCXHR_STREAM_STATUS_FREE)अणु
		/* streams in use */
		dev_err(chip->card->dev, "pcxhr_open chip%d subs%d in use\n",
			   chip->chip_idx, subs->number);
		mutex_unlock(&mgr->setup_mutex);
		वापस -EBUSY;
	पूर्ण

	/* भग्न क्रमmat support is in some हालs buggy on stereo cards */
	अगर (mgr->is_hr_stereo)
		runसमय->hw.क्रमmats &= ~SNDRV_PCM_FMTBIT_FLOAT_LE;

	/* buffer-size should better be multiple of period-size */
	err = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय,
					    SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (err < 0) अणु
		mutex_unlock(&mgr->setup_mutex);
		वापस err;
	पूर्ण

	/* अगर a sample rate is alपढ़ोy used or fixed by बाह्यal घड़ी,
	 * the stream cannot change
	 */
	अगर (mgr->sample_rate)
		runसमय->hw.rate_min = runसमय->hw.rate_max = mgr->sample_rate;
	अन्यथा अणु
		अगर (mgr->use_घड़ी_प्रकारype != PCXHR_CLOCK_TYPE_INTERNAL) अणु
			पूर्णांक बाह्यal_rate;
			अगर (pcxhr_get_बाह्यal_घड़ी(mgr, mgr->use_घड़ी_प्रकारype,
						     &बाह्यal_rate) ||
			    बाह्यal_rate == 0) अणु
				/* cannot detect the बाह्यal घड़ी rate */
				mutex_unlock(&mgr->setup_mutex);
				वापस -EBUSY;
			पूर्ण
			runसमय->hw.rate_min = बाह्यal_rate;
			runसमय->hw.rate_max = बाह्यal_rate;
		पूर्ण
	पूर्ण

	stream->status      = PCXHR_STREAM_STATUS_OPEN;
	stream->substream   = subs;
	stream->channels    = 0; /* not configured yet */

	runसमय->निजी_data = stream;

	/* better get a भागisor of granularity values (96 or 192) */
	snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0,
				   SNDRV_PCM_HW_PARAM_BUFFER_SIZE, 32);
	snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0,
				   SNDRV_PCM_HW_PARAM_PERIOD_SIZE, 32);
	snd_pcm_set_sync(subs);

	mgr->ref_count_rate++;

	mutex_unlock(&mgr->setup_mutex);
	वापस 0;
पूर्ण


अटल पूर्णांक pcxhr_बंद(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_pcxhr *chip = snd_pcm_substream_chip(subs);
	काष्ठा pcxhr_mgr *mgr = chip->mgr;
	काष्ठा pcxhr_stream *stream = subs->runसमय->निजी_data;

	mutex_lock(&mgr->setup_mutex);

	dev_dbg(chip->card->dev, "pcxhr_close chip%d subs%d\n",
		    chip->chip_idx, subs->number);

	/* sample rate released */
	अगर (--mgr->ref_count_rate == 0) अणु
		mgr->sample_rate = 0;	/* the sample rate is no more locked */
		pcxhr_hardware_समयr(mgr, 0);	/* stop the DSP-समयr */
	पूर्ण

	stream->status    = PCXHR_STREAM_STATUS_FREE;
	stream->substream = शून्य;

	mutex_unlock(&mgr->setup_mutex);

	वापस 0;
पूर्ण


अटल snd_pcm_uframes_t pcxhr_stream_poपूर्णांकer(काष्ठा snd_pcm_substream *subs)
अणु
	u_पूर्णांक32_t समयr_period_frag;
	पूर्णांक समयr_buf_periods;
	काष्ठा snd_pcxhr *chip = snd_pcm_substream_chip(subs);
	काष्ठा snd_pcm_runसमय *runसमय = subs->runसमय;
	काष्ठा pcxhr_stream *stream  = runसमय->निजी_data;

	mutex_lock(&chip->mgr->lock);

	/* get the period fragment and the nb of periods in the buffer */
	समयr_period_frag = stream->समयr_period_frag;
	समयr_buf_periods = stream->समयr_buf_periods;

	mutex_unlock(&chip->mgr->lock);

	वापस (snd_pcm_uframes_t)((समयr_buf_periods * runसमय->period_size) +
				   समयr_period_frag);
पूर्ण


अटल स्थिर काष्ठा snd_pcm_ops pcxhr_ops = अणु
	.खोलो      = pcxhr_खोलो,
	.बंद     = pcxhr_बंद,
	.prepare   = pcxhr_prepare,
	.hw_params = pcxhr_hw_params,
	.trigger   = pcxhr_trigger,
	.poपूर्णांकer   = pcxhr_stream_poपूर्णांकer,
पूर्ण;

/*
 */
पूर्णांक pcxhr_create_pcm(काष्ठा snd_pcxhr *chip)
अणु
	पूर्णांक err;
	काष्ठा snd_pcm *pcm;
	अक्षर name[32];

	snम_लिखो(name, माप(name), "pcxhr %d", chip->chip_idx);
	अगर ((err = snd_pcm_new(chip->card, name, 0,
			       chip->nb_streams_play,
			       chip->nb_streams_capt, &pcm)) < 0) अणु
		dev_err(chip->card->dev, "cannot create pcm %s\n", name);
		वापस err;
	पूर्ण
	pcm->निजी_data = chip;

	अगर (chip->nb_streams_play)
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &pcxhr_ops);
	अगर (chip->nb_streams_capt)
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &pcxhr_ops);

	pcm->info_flags = 0;
	pcm->nonatomic = true;
	म_नकल(pcm->name, name);

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       &chip->mgr->pci->dev,
				       32*1024, 32*1024);
	chip->pcm = pcm;
	वापस 0;
पूर्ण

अटल पूर्णांक pcxhr_chip_मुक्त(काष्ठा snd_pcxhr *chip)
अणु
	kमुक्त(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक pcxhr_chip_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_pcxhr *chip = device->device_data;
	वापस pcxhr_chip_मुक्त(chip);
पूर्ण


/*
 */
अटल पूर्णांक pcxhr_create(काष्ठा pcxhr_mgr *mgr,
			काष्ठा snd_card *card, पूर्णांक idx)
अणु
	पूर्णांक err;
	काष्ठा snd_pcxhr *chip;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त = pcxhr_chip_dev_मुक्त,
	पूर्ण;

	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->card = card;
	chip->chip_idx = idx;
	chip->mgr = mgr;
	card->sync_irq = mgr->irq;

	अगर (idx < mgr->playback_chips)
		/* stereo or mono streams */
		chip->nb_streams_play = PCXHR_PLAYBACK_STREAMS;

	अगर (idx < mgr->capture_chips) अणु
		अगर (mgr->mono_capture)
			chip->nb_streams_capt = 2;	/* 2 mono streams */
		अन्यथा
			chip->nb_streams_capt = 1;	/* or 1 stereo stream */
	पूर्ण

	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops)) < 0) अणु
		pcxhr_chip_मुक्त(chip);
		वापस err;
	पूर्ण

	mgr->chip[idx] = chip;

	वापस 0;
पूर्ण

/* proc पूर्णांकerface */
अटल व्योम pcxhr_proc_info(काष्ठा snd_info_entry *entry,
			    काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_pcxhr *chip = entry->निजी_data;
	काष्ठा pcxhr_mgr *mgr = chip->mgr;

	snd_iम_लिखो(buffer, "\n%s\n", mgr->name);

	/* stats available when embedded DSP is running */
	अगर (mgr->dsp_loaded & (1 << PCXHR_FIRMWARE_DSP_MAIN_INDEX)) अणु
		काष्ठा pcxhr_rmh rmh;
		लघु ver_maj = (mgr->dsp_version >> 16) & 0xff;
		लघु ver_min = (mgr->dsp_version >> 8) & 0xff;
		लघु ver_build = mgr->dsp_version & 0xff;
		snd_iम_लिखो(buffer, "module version %s\n",
			    PCXHR_DRIVER_VERSION_STRING);
		snd_iम_लिखो(buffer, "dsp version %d.%d.%d\n",
			    ver_maj, ver_min, ver_build);
		अगर (mgr->board_has_analog)
			snd_iम_लिखो(buffer, "analog io available\n");
		अन्यथा
			snd_iम_लिखो(buffer, "digital only board\n");

		/* calc cpu load of the dsp */
		pcxhr_init_rmh(&rmh, CMD_GET_DSP_RESOURCES);
		अगर( ! pcxhr_send_msg(mgr, &rmh) ) अणु
			पूर्णांक cur = rmh.stat[0];
			पूर्णांक ref = rmh.stat[1];
			अगर (ref > 0) अणु
				अगर (mgr->sample_rate_real != 0 &&
				    mgr->sample_rate_real != 48000) अणु
					ref = (ref * 48000) /
					  mgr->sample_rate_real;
					अगर (mgr->sample_rate_real >=
					    PCXHR_IRQ_TIMER_FREQ)
						ref *= 2;
				पूर्ण
				cur = 100 - (100 * cur) / ref;
				snd_iम_लिखो(buffer, "cpu load    %d%%\n", cur);
				snd_iम_लिखो(buffer, "buffer pool %d/%d\n",
					    rmh.stat[2], rmh.stat[3]);
			पूर्ण
		पूर्ण
		snd_iम_लिखो(buffer, "dma granularity : %d\n",
			    mgr->granularity);
		snd_iम_लिखो(buffer, "dsp time errors : %d\n",
			    mgr->dsp_समय_err);
		snd_iम_लिखो(buffer, "dsp async pipe xrun errors : %d\n",
			    mgr->async_err_pipe_xrun);
		snd_iम_लिखो(buffer, "dsp async stream xrun errors : %d\n",
			    mgr->async_err_stream_xrun);
		snd_iम_लिखो(buffer, "dsp async last other error : %x\n",
			    mgr->async_err_other_last);
		/* debug zone dsp */
		rmh.cmd[0] = 0x4200 + PCXHR_SIZE_MAX_STATUS;
		rmh.cmd_len = 1;
		rmh.stat_len = PCXHR_SIZE_MAX_STATUS;
		rmh.dsp_stat = 0;
		rmh.cmd_idx = CMD_LAST_INDEX;
		अगर( ! pcxhr_send_msg(mgr, &rmh) ) अणु
			पूर्णांक i;
			अगर (rmh.stat_len > 8)
				rmh.stat_len = 8;
			क्रम (i = 0; i < rmh.stat_len; i++)
				snd_iम_लिखो(buffer, "debug[%02d] = %06x\n",
					    i,  rmh.stat[i]);
		पूर्ण
	पूर्ण अन्यथा
		snd_iम_लिखो(buffer, "no firmware loaded\n");
	snd_iम_लिखो(buffer, "\n");
पूर्ण
अटल व्योम pcxhr_proc_sync(काष्ठा snd_info_entry *entry,
			    काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_pcxhr *chip = entry->निजी_data;
	काष्ठा pcxhr_mgr *mgr = chip->mgr;
	अटल स्थिर अक्षर *textsHR22[3] = अणु
		"Internal", "AES Sync", "AES 1"
	पूर्ण;
	अटल स्थिर अक्षर *textsPCXHR[7] = अणु
		"Internal", "Word", "AES Sync",
		"AES 1", "AES 2", "AES 3", "AES 4"
	पूर्ण;
	स्थिर अक्षर **texts;
	पूर्णांक max_घड़ी;
	अगर (mgr->is_hr_stereo) अणु
		texts = textsHR22;
		max_घड़ी = HR22_CLOCK_TYPE_MAX;
	पूर्ण अन्यथा अणु
		texts = textsPCXHR;
		max_घड़ी = PCXHR_CLOCK_TYPE_MAX;
	पूर्ण

	snd_iम_लिखो(buffer, "\n%s\n", mgr->name);
	snd_iम_लिखो(buffer, "Current Sample Clock\t: %s\n",
		    texts[mgr->cur_घड़ी_प्रकारype]);
	snd_iम_लिखो(buffer, "Current Sample Rate\t= %d\n",
		    mgr->sample_rate_real);
	/* commands available when embedded DSP is running */
	अगर (mgr->dsp_loaded & (1 << PCXHR_FIRMWARE_DSP_MAIN_INDEX)) अणु
		पूर्णांक i, err, sample_rate;
		क्रम (i = 1; i <= max_घड़ी; i++) अणु
			err = pcxhr_get_बाह्यal_घड़ी(mgr, i, &sample_rate);
			अगर (err)
				अवरोध;
			snd_iम_लिखो(buffer, "%s Clock\t\t= %d\n",
				    texts[i], sample_rate);
		पूर्ण
	पूर्ण अन्यथा
		snd_iम_लिखो(buffer, "no firmware loaded\n");
	snd_iम_लिखो(buffer, "\n");
पूर्ण

अटल व्योम pcxhr_proc_gpio_पढ़ो(काष्ठा snd_info_entry *entry,
				 काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_pcxhr *chip = entry->निजी_data;
	काष्ठा pcxhr_mgr *mgr = chip->mgr;
	/* commands available when embedded DSP is running */
	अगर (mgr->dsp_loaded & (1 << PCXHR_FIRMWARE_DSP_MAIN_INDEX)) अणु
		/* gpio ports on stereo boards only available */
		पूर्णांक value = 0;
		hr222_पढ़ो_gpio(mgr, 1, &value);	/* GPI */
		snd_iम_लिखो(buffer, "GPI: 0x%x\n", value);
		hr222_पढ़ो_gpio(mgr, 0, &value);	/* GP0 */
		snd_iम_लिखो(buffer, "GPO: 0x%x\n", value);
	पूर्ण अन्यथा
		snd_iम_लिखो(buffer, "no firmware loaded\n");
	snd_iम_लिखो(buffer, "\n");
पूर्ण
अटल व्योम pcxhr_proc_gpo_ग_लिखो(काष्ठा snd_info_entry *entry,
				 काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_pcxhr *chip = entry->निजी_data;
	काष्ठा pcxhr_mgr *mgr = chip->mgr;
	अक्षर line[64];
	पूर्णांक value;
	/* commands available when embedded DSP is running */
	अगर (!(mgr->dsp_loaded & (1 << PCXHR_FIRMWARE_DSP_MAIN_INDEX)))
		वापस;
	जबतक (!snd_info_get_line(buffer, line, माप(line))) अणु
		अगर (माला_पूछो(line, "GPO: 0x%x", &value) != 1)
			जारी;
		hr222_ग_लिखो_gpo(mgr, value);	/* GP0 */
	पूर्ण
पूर्ण

/* Access to the results of the CMD_GET_TIME_CODE RMH */
#घोषणा TIME_CODE_VALID_MASK	0x00800000
#घोषणा TIME_CODE_NEW_MASK	0x00400000
#घोषणा TIME_CODE_BACK_MASK	0x00200000
#घोषणा TIME_CODE_WAIT_MASK	0x00100000

/* Values क्रम the CMD_MANAGE_SIGNAL RMH */
#घोषणा MANAGE_SIGNAL_TIME_CODE	0x01
#घोषणा MANAGE_SIGNAL_MIDI	0x02

/* linear समय code पढ़ो proc*/
अटल व्योम pcxhr_proc_ltc(काष्ठा snd_info_entry *entry,
			   काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_pcxhr *chip = entry->निजी_data;
	काष्ठा pcxhr_mgr *mgr = chip->mgr;
	काष्ठा pcxhr_rmh rmh;
	अचिन्हित पूर्णांक ltcHrs, ltcMin, ltcSec, ltcFrm;
	पूर्णांक err;
	/* commands available when embedded DSP is running */
	अगर (!(mgr->dsp_loaded & (1 << PCXHR_FIRMWARE_DSP_MAIN_INDEX))) अणु
		snd_iम_लिखो(buffer, "no firmware loaded\n");
		वापस;
	पूर्ण
	अगर (!mgr->capture_ltc) अणु
		pcxhr_init_rmh(&rmh, CMD_MANAGE_SIGNAL);
		rmh.cmd[0] |= MANAGE_SIGNAL_TIME_CODE;
		err = pcxhr_send_msg(mgr, &rmh);
		अगर (err) अणु
			snd_iम_लिखो(buffer, "ltc not activated (%d)\n", err);
			वापस;
		पूर्ण
		अगर (mgr->is_hr_stereo)
			hr222_manage_समयcode(mgr, 1);
		अन्यथा
			pcxhr_ग_लिखो_io_num_reg_cont(mgr, REG_CONT_VALSMPTE,
						    REG_CONT_VALSMPTE, शून्य);
		mgr->capture_ltc = 1;
	पूर्ण
	pcxhr_init_rmh(&rmh, CMD_GET_TIME_CODE);
	err = pcxhr_send_msg(mgr, &rmh);
	अगर (err) अणु
		snd_iम_लिखो(buffer, "ltc read error (err=%d)\n", err);
		वापस ;
	पूर्ण
	ltcHrs = 10*((rmh.stat[0] >> 8) & 0x3) + (rmh.stat[0] & 0xf);
	ltcMin = 10*((rmh.stat[1] >> 16) & 0x7) + ((rmh.stat[1] >> 8) & 0xf);
	ltcSec = 10*(rmh.stat[1] & 0x7) + ((rmh.stat[2] >> 16) & 0xf);
	ltcFrm = 10*((rmh.stat[2] >> 8) & 0x3) + (rmh.stat[2] & 0xf);

	snd_iम_लिखो(buffer, "timecode: %02u:%02u:%02u-%02u\n",
			    ltcHrs, ltcMin, ltcSec, ltcFrm);
	snd_iम_लिखो(buffer, "raw: 0x%04x%06x%06x\n", rmh.stat[0] & 0x00ffff,
			    rmh.stat[1] & 0xffffff, rmh.stat[2] & 0xffffff);
	/*snd_iम_लिखो(buffer, "dsp ref time: 0x%06x%06x\n",
			    rmh.stat[3] & 0xffffff, rmh.stat[4] & 0xffffff);*/
	अगर (!(rmh.stat[0] & TIME_CODE_VALID_MASK)) अणु
		snd_iम_लिखो(buffer, "warning: linear timecode not valid\n");
	पूर्ण
पूर्ण

अटल व्योम pcxhr_proc_init(काष्ठा snd_pcxhr *chip)
अणु
	snd_card_ro_proc_new(chip->card, "info", chip, pcxhr_proc_info);
	snd_card_ro_proc_new(chip->card, "sync", chip, pcxhr_proc_sync);
	/* gpio available on stereo sound cards only */
	अगर (chip->mgr->is_hr_stereo)
		snd_card_rw_proc_new(chip->card, "gpio", chip,
				     pcxhr_proc_gpio_पढ़ो,
				     pcxhr_proc_gpo_ग_लिखो);
	snd_card_ro_proc_new(chip->card, "ltc", chip, pcxhr_proc_ltc);
पूर्ण
/* end of proc पूर्णांकerface */

/*
 * release all the cards asचिन्हित to a manager instance
 */
अटल पूर्णांक pcxhr_मुक्त(काष्ठा pcxhr_mgr *mgr)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < mgr->num_cards; i++) अणु
		अगर (mgr->chip[i])
			snd_card_मुक्त(mgr->chip[i]->card);
	पूर्ण

	/* reset board अगर some firmware was loaded */
	अगर(mgr->dsp_loaded) अणु
		pcxhr_reset_board(mgr);
		dev_dbg(&mgr->pci->dev, "reset pcxhr !\n");
	पूर्ण

	/* release irq  */
	अगर (mgr->irq >= 0)
		मुक्त_irq(mgr->irq, mgr);

	pci_release_regions(mgr->pci);

	/* मुक्त hostport purgebuffer */
	अगर (mgr->hostport.area) अणु
		snd_dma_मुक्त_pages(&mgr->hostport);
		mgr->hostport.area = शून्य;
	पूर्ण

	kमुक्त(mgr->prmh);

	pci_disable_device(mgr->pci);
	kमुक्त(mgr);
	वापस 0;
पूर्ण

/*
 *    probe function - creates the card manager
 */
अटल पूर्णांक pcxhr_probe(काष्ठा pci_dev *pci,
		       स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा pcxhr_mgr *mgr;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;
	माप_प्रकार size;
	अक्षर *card_name;

	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;
	अगर (! enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण

	/* enable PCI device */
	अगर ((err = pci_enable_device(pci)) < 0)
		वापस err;
	pci_set_master(pci);

	/* check अगर we can restrict PCI DMA transfers to 32 bits */
	अगर (dma_set_mask(&pci->dev, DMA_BIT_MASK(32)) < 0) अणु
		dev_err(&pci->dev,
			"architecture does not support 32bit PCI busmaster DMA\n");
		pci_disable_device(pci);
		वापस -ENXIO;
	पूर्ण

	/* alloc card manager */
	mgr = kzalloc(माप(*mgr), GFP_KERNEL);
	अगर (! mgr) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण

	अगर (snd_BUG_ON(pci_id->driver_data >= PCI_ID_LAST)) अणु
		kमुक्त(mgr);
		pci_disable_device(pci);
		वापस -ENODEV;
	पूर्ण
	card_name =
		pcxhr_board_params[pci_id->driver_data].board_name;
	mgr->playback_chips =
		pcxhr_board_params[pci_id->driver_data].playback_chips;
	mgr->capture_chips  =
		pcxhr_board_params[pci_id->driver_data].capture_chips;
	mgr->fw_file_set =
		pcxhr_board_params[pci_id->driver_data].fw_file_set;
	mgr->firmware_num  =
		pcxhr_board_params[pci_id->driver_data].firmware_num;
	mgr->mono_capture = mono[dev];
	mgr->is_hr_stereo = (mgr->playback_chips == 1);
	mgr->board_has_aes1 = PCXHR_BOARD_HAS_AES1(mgr);
	mgr->board_aes_in_192k = !PCXHR_BOARD_AESIN_NO_192K(mgr);

	अगर (mgr->is_hr_stereo)
		mgr->granularity = PCXHR_GRANULARITY_HR22;
	अन्यथा
		mgr->granularity = PCXHR_GRANULARITY;

	/* resource assignment */
	अगर ((err = pci_request_regions(pci, card_name)) < 0) अणु
		kमुक्त(mgr);
		pci_disable_device(pci);
		वापस err;
	पूर्ण
	क्रम (i = 0; i < 3; i++)
		mgr->port[i] = pci_resource_start(pci, i);

	mgr->pci = pci;
	mgr->irq = -1;

	अगर (request_thपढ़ोed_irq(pci->irq, pcxhr_पूर्णांकerrupt,
				 pcxhr_thपढ़ोed_irq, IRQF_SHARED,
				 KBUILD_MODNAME, mgr)) अणु
		dev_err(&pci->dev, "unable to grab IRQ %d\n", pci->irq);
		pcxhr_मुक्त(mgr);
		वापस -EBUSY;
	पूर्ण
	mgr->irq = pci->irq;

	snम_लिखो(mgr->name, माप(mgr->name),
		 "Digigram at 0x%lx & 0x%lx, 0x%lx irq %i",
		 mgr->port[0], mgr->port[1], mgr->port[2], mgr->irq);

	/* ISR lock  */
	mutex_init(&mgr->lock);
	mutex_init(&mgr->msg_lock);

	/* init setup mutex*/
	mutex_init(&mgr->setup_mutex);

	mgr->prmh = kदो_स्मृति(माप(*mgr->prmh) + 
			    माप(u32) * (PCXHR_SIZE_MAX_LONG_STATUS -
					   PCXHR_SIZE_MAX_STATUS),
			    GFP_KERNEL);
	अगर (! mgr->prmh) अणु
		pcxhr_मुक्त(mgr);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i=0; i < PCXHR_MAX_CARDS; i++) अणु
		काष्ठा snd_card *card;
		अक्षर पंचांगpid[16];
		पूर्णांक idx;

		अगर (i >= max(mgr->playback_chips, mgr->capture_chips))
			अवरोध;
		mgr->num_cards++;

		अगर (index[dev] < 0)
			idx = index[dev];
		अन्यथा
			idx = index[dev] + i;

		snम_लिखो(पंचांगpid, माप(पंचांगpid), "%s-%d",
			 id[dev] ? id[dev] : card_name, i);
		err = snd_card_new(&pci->dev, idx, पंचांगpid, THIS_MODULE,
				   0, &card);

		अगर (err < 0) अणु
			dev_err(&pci->dev, "cannot allocate the card %d\n", i);
			pcxhr_मुक्त(mgr);
			वापस err;
		पूर्ण

		म_नकल(card->driver, DRIVER_NAME);
		snम_लिखो(card->लघुname, माप(card->लघुname),
			 "Digigram [PCM #%d]", i);
		snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
			 "%s [PCM #%d]", mgr->name, i);

		अगर ((err = pcxhr_create(mgr, card, i)) < 0) अणु
			snd_card_मुक्त(card);
			pcxhr_मुक्त(mgr);
			वापस err;
		पूर्ण

		अगर (i == 0)
			/* init proc पूर्णांकerface only क्रम chip0 */
			pcxhr_proc_init(mgr->chip[i]);

		अगर ((err = snd_card_रेजिस्टर(card)) < 0) अणु
			pcxhr_मुक्त(mgr);
			वापस err;
		पूर्ण
	पूर्ण

	/* create hostport purgebuffer */
	size = PAGE_ALIGN(माप(काष्ठा pcxhr_hostport));
	अगर (snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, &pci->dev,
				size, &mgr->hostport) < 0) अणु
		pcxhr_मुक्त(mgr);
		वापस -ENOMEM;
	पूर्ण
	/* init purgebuffer */
	स_रखो(mgr->hostport.area, 0, size);

	/* create a DSP loader */
	err = pcxhr_setup_firmware(mgr);
	अगर (err < 0) अणु
		pcxhr_मुक्त(mgr);
		वापस err;
	पूर्ण

	pci_set_drvdata(pci, mgr);
	dev++;
	वापस 0;
पूर्ण

अटल व्योम pcxhr_हटाओ(काष्ठा pci_dev *pci)
अणु
	pcxhr_मुक्त(pci_get_drvdata(pci));
पूर्ण

अटल काष्ठा pci_driver pcxhr_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = pcxhr_ids,
	.probe = pcxhr_probe,
	.हटाओ = pcxhr_हटाओ,
पूर्ण;

module_pci_driver(pcxhr_driver);
