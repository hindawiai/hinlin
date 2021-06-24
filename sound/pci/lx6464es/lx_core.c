<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* -*- linux-c -*- *
 *
 * ALSA driver क्रम the digigram lx6464es पूर्णांकerface
 * low-level पूर्णांकerface
 *
 * Copyright (c) 2009 Tim Blechmann <tim@klingt.org>
 */

/* #घोषणा RMH_DEBUG 1 */

#समावेश <linux/bitops.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>

#समावेश "lx6464es.h"
#समावेश "lx_core.h"

/* low-level रेजिस्टर access */

अटल स्थिर अचिन्हित दीर्घ dsp_port_offsets[] = अणु
	0,
	0x400,
	0x401,
	0x402,
	0x403,
	0x404,
	0x405,
	0x406,
	0x407,
	0x408,
	0x409,
	0x40a,
	0x40b,
	0x40c,

	0x410,
	0x411,
	0x412,
	0x413,
	0x414,
	0x415,
	0x416,

	0x420,
	0x430,
	0x431,
	0x432,
	0x433,
	0x434,
	0x440
पूर्ण;

अटल व्योम __iomem *lx_dsp_रेजिस्टर(काष्ठा lx6464es *chip, पूर्णांक port)
अणु
	व्योम __iomem *base_address = chip->port_dsp_bar;
	वापस base_address + dsp_port_offsets[port]*4;
पूर्ण

अचिन्हित दीर्घ lx_dsp_reg_पढ़ो(काष्ठा lx6464es *chip, पूर्णांक port)
अणु
	व्योम __iomem *address = lx_dsp_रेजिस्टर(chip, port);
	वापस ioपढ़ो32(address);
पूर्ण

अटल व्योम lx_dsp_reg_पढ़ोbuf(काष्ठा lx6464es *chip, पूर्णांक port, u32 *data,
			       u32 len)
अणु
	u32 __iomem *address = lx_dsp_रेजिस्टर(chip, port);
	पूर्णांक i;

	/* we cannot use स_नकल_fromio */
	क्रम (i = 0; i != len; ++i)
		data[i] = ioपढ़ो32(address + i);
पूर्ण


व्योम lx_dsp_reg_ग_लिखो(काष्ठा lx6464es *chip, पूर्णांक port, अचिन्हित data)
अणु
	व्योम __iomem *address = lx_dsp_रेजिस्टर(chip, port);
	ioग_लिखो32(data, address);
पूर्ण

अटल व्योम lx_dsp_reg_ग_लिखोbuf(काष्ठा lx6464es *chip, पूर्णांक port,
				स्थिर u32 *data, u32 len)
अणु
	u32 __iomem *address = lx_dsp_रेजिस्टर(chip, port);
	पूर्णांक i;

	/* we cannot use स_नकल_to */
	क्रम (i = 0; i != len; ++i)
		ioग_लिखो32(data[i], address + i);
पूर्ण


अटल स्थिर अचिन्हित दीर्घ plx_port_offsets[] = अणु
	0x04,
	0x40,
	0x44,
	0x48,
	0x4c,
	0x50,
	0x54,
	0x58,
	0x5c,
	0x64,
	0x68,
	0x6C
पूर्ण;

अटल व्योम __iomem *lx_plx_रेजिस्टर(काष्ठा lx6464es *chip, पूर्णांक port)
अणु
	व्योम __iomem *base_address = chip->port_plx_remapped;
	वापस base_address + plx_port_offsets[port];
पूर्ण

अचिन्हित दीर्घ lx_plx_reg_पढ़ो(काष्ठा lx6464es *chip, पूर्णांक port)
अणु
	व्योम __iomem *address = lx_plx_रेजिस्टर(chip, port);
	वापस ioपढ़ो32(address);
पूर्ण

व्योम lx_plx_reg_ग_लिखो(काष्ठा lx6464es *chip, पूर्णांक port, u32 data)
अणु
	व्योम __iomem *address = lx_plx_रेजिस्टर(chip, port);
	ioग_लिखो32(data, address);
पूर्ण

/* rmh */

#अगर_घोषित CONFIG_SND_DEBUG
#घोषणा CMD_NAME(a) a
#अन्यथा
#घोषणा CMD_NAME(a) शून्य
#पूर्ण_अगर

#घोषणा Reg_CSM_MR			0x00000002
#घोषणा Reg_CSM_MC			0x00000001

काष्ठा dsp_cmd_info अणु
	u32    dcCodeOp;	/* Op Code of the command (usually 1st 24-bits
				 * word).*/
	u16    dcCmdLength;	/* Command length in words of 24 bits.*/
	u16    dcStatusType;	/* Status type: 0 क्रम fixed length, 1 क्रम
				 * अक्रमom. */
	u16    dcStatusLength;	/* Status length (अगर fixed).*/
	अक्षर  *dcOpName;
पूर्ण;

/*
  Initialization and control data क्रम the Microblaze पूर्णांकerface
  - OpCode:
    the opcode field of the command set at the proper offset
  - CmdLength
    the number of command words
  - StatusType
    offset in the status रेजिस्टरs: 0 means that the वापस value may be
    dअगरferent from 0, and must be पढ़ो
  - StatusLength
    the number of status words (in addition to the वापस value)
*/

अटल स्थिर काष्ठा dsp_cmd_info dsp_commands[] =
अणु
	अणु (CMD_00_INFO_DEBUG << OPCODE_OFFSET)			, 1 /*custom*/
	  , 1	, 0 /**/		    , CMD_NAME("INFO_DEBUG") पूर्ण,
	अणु (CMD_01_GET_SYS_CFG << OPCODE_OFFSET) 		, 1 /**/
	  , 1      , 2 /**/		    , CMD_NAME("GET_SYS_CFG") पूर्ण,
	अणु (CMD_02_SET_GRANULARITY << OPCODE_OFFSET)	        , 1 /**/
	  , 1      , 0 /**/		    , CMD_NAME("SET_GRANULARITY") पूर्ण,
	अणु (CMD_03_SET_TIMER_IRQ << OPCODE_OFFSET)		, 1 /**/
	  , 1      , 0 /**/		    , CMD_NAME("SET_TIMER_IRQ") पूर्ण,
	अणु (CMD_04_GET_EVENT << OPCODE_OFFSET)			, 1 /**/
	  , 1      , 0 /*up to 10*/     , CMD_NAME("GET_EVENT") पूर्ण,
	अणु (CMD_05_GET_PIPES << OPCODE_OFFSET)			, 1 /**/
	  , 1      , 2 /*up to 4*/      , CMD_NAME("GET_PIPES") पूर्ण,
	अणु (CMD_06_ALLOCATE_PIPE << OPCODE_OFFSET)		, 1 /**/
	  , 0      , 0 /**/		    , CMD_NAME("ALLOCATE_PIPE") पूर्ण,
	अणु (CMD_07_RELEASE_PIPE << OPCODE_OFFSET)		, 1 /**/
	  , 0      , 0 /**/		    , CMD_NAME("RELEASE_PIPE") पूर्ण,
	अणु (CMD_08_ASK_BUFFERS << OPCODE_OFFSET) 		, 1 /**/
	  , 1      , MAX_STREAM_BUFFER  , CMD_NAME("ASK_BUFFERS") पूर्ण,
	अणु (CMD_09_STOP_PIPE << OPCODE_OFFSET)			, 1 /**/
	  , 0      , 0 /*up to 2*/      , CMD_NAME("STOP_PIPE") पूर्ण,
	अणु (CMD_0A_GET_PIPE_SPL_COUNT << OPCODE_OFFSET)	        , 1 /**/
	  , 1      , 1 /*up to 2*/      , CMD_NAME("GET_PIPE_SPL_COUNT") पूर्ण,
	अणु (CMD_0B_TOGGLE_PIPE_STATE << OPCODE_OFFSET)           , 1 /*up to 5*/
	  , 1      , 0 /**/		    , CMD_NAME("TOGGLE_PIPE_STATE") पूर्ण,
	अणु (CMD_0C_DEF_STREAM << OPCODE_OFFSET)			, 1 /*up to 4*/
	  , 1      , 0 /**/		    , CMD_NAME("DEF_STREAM") पूर्ण,
	अणु (CMD_0D_SET_MUTE  << OPCODE_OFFSET)			, 3 /**/
	  , 1      , 0 /**/		    , CMD_NAME("SET_MUTE") पूर्ण,
	अणु (CMD_0E_GET_STREAM_SPL_COUNT << OPCODE_OFFSET)        , 1/**/
	  , 1      , 2 /**/		    , CMD_NAME("GET_STREAM_SPL_COUNT") पूर्ण,
	अणु (CMD_0F_UPDATE_BUFFER << OPCODE_OFFSET)		, 3 /*up to 4*/
	  , 0      , 1 /**/		    , CMD_NAME("UPDATE_BUFFER") पूर्ण,
	अणु (CMD_10_GET_BUFFER << OPCODE_OFFSET)			, 1 /**/
	  , 1      , 4 /**/		    , CMD_NAME("GET_BUFFER") पूर्ण,
	अणु (CMD_11_CANCEL_BUFFER << OPCODE_OFFSET)		, 1 /**/
	  , 1      , 1 /*up to 4*/      , CMD_NAME("CANCEL_BUFFER") पूर्ण,
	अणु (CMD_12_GET_PEAK << OPCODE_OFFSET)			, 1 /**/
	  , 1      , 1 /**/		    , CMD_NAME("GET_PEAK") पूर्ण,
	अणु (CMD_13_SET_STREAM_STATE << OPCODE_OFFSET)	        , 1 /**/
	  , 1      , 0 /**/		    , CMD_NAME("SET_STREAM_STATE") पूर्ण,
पूर्ण;

अटल व्योम lx_message_init(काष्ठा lx_rmh *rmh, क्रमागत cmd_mb_opcodes cmd)
अणु
	snd_BUG_ON(cmd >= CMD_14_INVALID);

	rmh->cmd[0] = dsp_commands[cmd].dcCodeOp;
	rmh->cmd_len = dsp_commands[cmd].dcCmdLength;
	rmh->stat_len = dsp_commands[cmd].dcStatusLength;
	rmh->dsp_stat = dsp_commands[cmd].dcStatusType;
	rmh->cmd_idx = cmd;
	स_रखो(&rmh->cmd[1], 0, (REG_CRM_NUMBER - 1) * माप(u32));

#अगर_घोषित CONFIG_SND_DEBUG
	स_रखो(rmh->stat, 0, REG_CRM_NUMBER * माप(u32));
#पूर्ण_अगर
#अगर_घोषित RMH_DEBUG
	rmh->cmd_idx = cmd;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित RMH_DEBUG
#घोषणा LXRMH "lx6464es rmh: "
अटल व्योम lx_message_dump(काष्ठा lx_rmh *rmh)
अणु
	u8 idx = rmh->cmd_idx;
	पूर्णांक i;

	snd_prपूर्णांकk(LXRMH "command %s\n", dsp_commands[idx].dcOpName);

	क्रम (i = 0; i != rmh->cmd_len; ++i)
		snd_prपूर्णांकk(LXRMH "\tcmd[%d] %08x\n", i, rmh->cmd[i]);

	क्रम (i = 0; i != rmh->stat_len; ++i)
		snd_prपूर्णांकk(LXRMH "\tstat[%d]: %08x\n", i, rmh->stat[i]);
	snd_prपूर्णांकk("\n");
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम lx_message_dump(काष्ठा lx_rmh *rmh)
अणुपूर्ण
#पूर्ण_अगर



/* sleep 500 - 100 = 400 बार 100us -> the समयout is >= 40 ms */
#घोषणा XILINX_TIMEOUT_MS       40
#घोषणा XILINX_POLL_NO_SLEEP    100
#घोषणा XILINX_POLL_ITERATIONS  150


अटल पूर्णांक lx_message_send_atomic(काष्ठा lx6464es *chip, काष्ठा lx_rmh *rmh)
अणु
	u32 reg = ED_DSP_TIMED_OUT;
	पूर्णांक dwloop;

	अगर (lx_dsp_reg_पढ़ो(chip, eReg_CSM) & (Reg_CSM_MC | Reg_CSM_MR)) अणु
		dev_err(chip->card->dev, "PIOSendMessage eReg_CSM %x\n", reg);
		वापस -EBUSY;
	पूर्ण

	/* ग_लिखो command */
	lx_dsp_reg_ग_लिखोbuf(chip, eReg_CRM1, rmh->cmd, rmh->cmd_len);

	/* MicoBlaze gogogo */
	lx_dsp_reg_ग_लिखो(chip, eReg_CSM, Reg_CSM_MC);

	/* रुको क्रम device to answer */
	क्रम (dwloop = 0; dwloop != XILINX_TIMEOUT_MS * 1000; ++dwloop) अणु
		अगर (lx_dsp_reg_पढ़ो(chip, eReg_CSM) & Reg_CSM_MR) अणु
			अगर (rmh->dsp_stat == 0)
				reg = lx_dsp_reg_पढ़ो(chip, eReg_CRM1);
			अन्यथा
				reg = 0;
			जाओ polling_successful;
		पूर्ण अन्यथा
			udelay(1);
	पूर्ण
	dev_warn(chip->card->dev, "TIMEOUT lx_message_send_atomic! "
		   "polling failed\n");

polling_successful:
	अगर ((reg & ERROR_VALUE) == 0) अणु
		/* पढ़ो response */
		अगर (rmh->stat_len) अणु
			snd_BUG_ON(rmh->stat_len >= (REG_CRM_NUMBER-1));
			lx_dsp_reg_पढ़ोbuf(chip, eReg_CRM2, rmh->stat,
					   rmh->stat_len);
		पूर्ण
	पूर्ण अन्यथा
		dev_err(chip->card->dev, "rmh error: %08x\n", reg);

	/* clear Reg_CSM_MR */
	lx_dsp_reg_ग_लिखो(chip, eReg_CSM, 0);

	चयन (reg) अणु
	हाल ED_DSP_TIMED_OUT:
		dev_warn(chip->card->dev, "lx_message_send: dsp timeout\n");
		वापस -ETIMEDOUT;

	हाल ED_DSP_CRASHED:
		dev_warn(chip->card->dev, "lx_message_send: dsp crashed\n");
		वापस -EAGAIN;
	पूर्ण

	lx_message_dump(rmh);

	वापस reg;
पूर्ण


/* low-level dsp access */
पूर्णांक lx_dsp_get_version(काष्ठा lx6464es *chip, u32 *rdsp_version)
अणु
	u16 ret;

	mutex_lock(&chip->msg_lock);

	lx_message_init(&chip->rmh, CMD_01_GET_SYS_CFG);
	ret = lx_message_send_atomic(chip, &chip->rmh);

	*rdsp_version = chip->rmh.stat[1];
	mutex_unlock(&chip->msg_lock);
	वापस ret;
पूर्ण

पूर्णांक lx_dsp_get_घड़ी_frequency(काष्ठा lx6464es *chip, u32 *rfreq)
अणु
	u16 ret = 0;
	u32 freq_raw = 0;
	u32 freq = 0;
	u32 frequency = 0;

	mutex_lock(&chip->msg_lock);

	lx_message_init(&chip->rmh, CMD_01_GET_SYS_CFG);
	ret = lx_message_send_atomic(chip, &chip->rmh);

	अगर (ret == 0) अणु
		freq_raw = chip->rmh.stat[0] >> FREQ_FIELD_OFFSET;
		freq = freq_raw & XES_FREQ_COUNT8_MASK;

		अगर ((freq < XES_FREQ_COUNT8_48_MAX) ||
		    (freq > XES_FREQ_COUNT8_44_MIN))
			frequency = 0; /* unknown */
		अन्यथा अगर (freq >= XES_FREQ_COUNT8_44_MAX)
			frequency = 44100;
		अन्यथा
			frequency = 48000;
	पूर्ण

	mutex_unlock(&chip->msg_lock);

	*rfreq = frequency * chip->freq_ratio;

	वापस ret;
पूर्ण

पूर्णांक lx_dsp_get_mac(काष्ठा lx6464es *chip)
अणु
	u32 macmsb, maclsb;

	macmsb = lx_dsp_reg_पढ़ो(chip, eReg_ADMACESMSB) & 0x00FFFFFF;
	maclsb = lx_dsp_reg_पढ़ो(chip, eReg_ADMACESLSB) & 0x00FFFFFF;

	/* toकरो: endianess handling */
	chip->mac_address[5] = ((u8 *)(&maclsb))[0];
	chip->mac_address[4] = ((u8 *)(&maclsb))[1];
	chip->mac_address[3] = ((u8 *)(&maclsb))[2];
	chip->mac_address[2] = ((u8 *)(&macmsb))[0];
	chip->mac_address[1] = ((u8 *)(&macmsb))[1];
	chip->mac_address[0] = ((u8 *)(&macmsb))[2];

	वापस 0;
पूर्ण


पूर्णांक lx_dsp_set_granularity(काष्ठा lx6464es *chip, u32 gran)
अणु
	पूर्णांक ret;

	mutex_lock(&chip->msg_lock);

	lx_message_init(&chip->rmh, CMD_02_SET_GRANULARITY);
	chip->rmh.cmd[0] |= gran;

	ret = lx_message_send_atomic(chip, &chip->rmh);
	mutex_unlock(&chip->msg_lock);
	वापस ret;
पूर्ण

पूर्णांक lx_dsp_पढ़ो_async_events(काष्ठा lx6464es *chip, u32 *data)
अणु
	पूर्णांक ret;

	mutex_lock(&chip->msg_lock);

	lx_message_init(&chip->rmh, CMD_04_GET_EVENT);
	chip->rmh.stat_len = 9;	/* we करोn't necessarily need the full length */

	ret = lx_message_send_atomic(chip, &chip->rmh);

	अगर (!ret)
		स_नकल(data, chip->rmh.stat, chip->rmh.stat_len * माप(u32));

	mutex_unlock(&chip->msg_lock);
	वापस ret;
पूर्ण

#घोषणा PIPE_INFO_TO_CMD(capture, pipe)					\
	((u32)((u32)(pipe) | ((capture) ? ID_IS_CAPTURE : 0L)) << ID_OFFSET)



/* low-level pipe handling */
पूर्णांक lx_pipe_allocate(काष्ठा lx6464es *chip, u32 pipe, पूर्णांक is_capture,
		     पूर्णांक channels)
अणु
	पूर्णांक err;
	u32 pipe_cmd = PIPE_INFO_TO_CMD(is_capture, pipe);

	mutex_lock(&chip->msg_lock);
	lx_message_init(&chip->rmh, CMD_06_ALLOCATE_PIPE);

	chip->rmh.cmd[0] |= pipe_cmd;
	chip->rmh.cmd[0] |= channels;

	err = lx_message_send_atomic(chip, &chip->rmh);
	mutex_unlock(&chip->msg_lock);

	अगर (err != 0)
		dev_err(chip->card->dev, "could not allocate pipe\n");

	वापस err;
पूर्ण

पूर्णांक lx_pipe_release(काष्ठा lx6464es *chip, u32 pipe, पूर्णांक is_capture)
अणु
	पूर्णांक err;
	u32 pipe_cmd = PIPE_INFO_TO_CMD(is_capture, pipe);

	mutex_lock(&chip->msg_lock);
	lx_message_init(&chip->rmh, CMD_07_RELEASE_PIPE);

	chip->rmh.cmd[0] |= pipe_cmd;

	err = lx_message_send_atomic(chip, &chip->rmh);
	mutex_unlock(&chip->msg_lock);

	वापस err;
पूर्ण

पूर्णांक lx_buffer_ask(काष्ठा lx6464es *chip, u32 pipe, पूर्णांक is_capture,
		  u32 *r_needed, u32 *r_मुक्तd, u32 *size_array)
अणु
	पूर्णांक err;
	u32 pipe_cmd = PIPE_INFO_TO_CMD(is_capture, pipe);

#अगर_घोषित CONFIG_SND_DEBUG
	अगर (size_array)
		स_रखो(size_array, 0, माप(u32)*MAX_STREAM_BUFFER);
#पूर्ण_अगर

	*r_needed = 0;
	*r_मुक्तd = 0;

	mutex_lock(&chip->msg_lock);
	lx_message_init(&chip->rmh, CMD_08_ASK_BUFFERS);

	chip->rmh.cmd[0] |= pipe_cmd;

	err = lx_message_send_atomic(chip, &chip->rmh);

	अगर (!err) अणु
		पूर्णांक i;
		क्रम (i = 0; i < MAX_STREAM_BUFFER; ++i) अणु
			u32 stat = chip->rmh.stat[i];
			अगर (stat & (BF_EOB << BUFF_FLAGS_OFFSET)) अणु
				/* finished */
				*r_मुक्तd += 1;
				अगर (size_array)
					size_array[i] = stat & MASK_DATA_SIZE;
			पूर्ण अन्यथा अगर ((stat & (BF_VALID << BUFF_FLAGS_OFFSET))
				   == 0)
				/* मुक्त */
				*r_needed += 1;
		पूर्ण

		dev_dbg(chip->card->dev,
			"CMD_08_ASK_BUFFERS: needed %d, freed %d\n",
			    *r_needed, *r_मुक्तd);
		क्रम (i = 0; i < MAX_STREAM_BUFFER; ++i) अणु
			क्रम (i = 0; i != chip->rmh.stat_len; ++i)
				dev_dbg(chip->card->dev,
					"  stat[%d]: %x, %x\n", i,
					    chip->rmh.stat[i],
					    chip->rmh.stat[i] & MASK_DATA_SIZE);
		पूर्ण
	पूर्ण

	mutex_unlock(&chip->msg_lock);
	वापस err;
पूर्ण


पूर्णांक lx_pipe_stop(काष्ठा lx6464es *chip, u32 pipe, पूर्णांक is_capture)
अणु
	पूर्णांक err;
	u32 pipe_cmd = PIPE_INFO_TO_CMD(is_capture, pipe);

	mutex_lock(&chip->msg_lock);
	lx_message_init(&chip->rmh, CMD_09_STOP_PIPE);

	chip->rmh.cmd[0] |= pipe_cmd;

	err = lx_message_send_atomic(chip, &chip->rmh);

	mutex_unlock(&chip->msg_lock);
	वापस err;
पूर्ण

अटल पूर्णांक lx_pipe_toggle_state(काष्ठा lx6464es *chip, u32 pipe, पूर्णांक is_capture)
अणु
	पूर्णांक err;
	u32 pipe_cmd = PIPE_INFO_TO_CMD(is_capture, pipe);

	mutex_lock(&chip->msg_lock);
	lx_message_init(&chip->rmh, CMD_0B_TOGGLE_PIPE_STATE);

	chip->rmh.cmd[0] |= pipe_cmd;

	err = lx_message_send_atomic(chip, &chip->rmh);

	mutex_unlock(&chip->msg_lock);
	वापस err;
पूर्ण


पूर्णांक lx_pipe_start(काष्ठा lx6464es *chip, u32 pipe, पूर्णांक is_capture)
अणु
	पूर्णांक err;

	err = lx_pipe_रुको_क्रम_idle(chip, pipe, is_capture);
	अगर (err < 0)
		वापस err;

	err = lx_pipe_toggle_state(chip, pipe, is_capture);

	वापस err;
पूर्ण

पूर्णांक lx_pipe_छोड़ो(काष्ठा lx6464es *chip, u32 pipe, पूर्णांक is_capture)
अणु
	पूर्णांक err = 0;

	err = lx_pipe_रुको_क्रम_start(chip, pipe, is_capture);
	अगर (err < 0)
		वापस err;

	err = lx_pipe_toggle_state(chip, pipe, is_capture);

	वापस err;
पूर्ण


पूर्णांक lx_pipe_sample_count(काष्ठा lx6464es *chip, u32 pipe, पूर्णांक is_capture,
			 u64 *rsample_count)
अणु
	पूर्णांक err;
	u32 pipe_cmd = PIPE_INFO_TO_CMD(is_capture, pipe);

	mutex_lock(&chip->msg_lock);
	lx_message_init(&chip->rmh, CMD_0A_GET_PIPE_SPL_COUNT);

	chip->rmh.cmd[0] |= pipe_cmd;
	chip->rmh.stat_len = 2;	/* need all words here! */

	err = lx_message_send_atomic(chip, &chip->rmh); /* करोn't sleep! */

	अगर (err != 0)
		dev_err(chip->card->dev,
			"could not query pipe's sample count\n");
	अन्यथा अणु
		*rsample_count = ((u64)(chip->rmh.stat[0] & MASK_SPL_COUNT_HI)
				  << 24)     /* hi part */
			+ chip->rmh.stat[1]; /* lo part */
	पूर्ण

	mutex_unlock(&chip->msg_lock);
	वापस err;
पूर्ण

पूर्णांक lx_pipe_state(काष्ठा lx6464es *chip, u32 pipe, पूर्णांक is_capture, u16 *rstate)
अणु
	पूर्णांक err;
	u32 pipe_cmd = PIPE_INFO_TO_CMD(is_capture, pipe);

	mutex_lock(&chip->msg_lock);
	lx_message_init(&chip->rmh, CMD_0A_GET_PIPE_SPL_COUNT);

	chip->rmh.cmd[0] |= pipe_cmd;

	err = lx_message_send_atomic(chip, &chip->rmh);

	अगर (err != 0)
		dev_err(chip->card->dev, "could not query pipe's state\n");
	अन्यथा
		*rstate = (chip->rmh.stat[0] >> PSTATE_OFFSET) & 0x0F;

	mutex_unlock(&chip->msg_lock);
	वापस err;
पूर्ण

अटल पूर्णांक lx_pipe_रुको_क्रम_state(काष्ठा lx6464es *chip, u32 pipe,
				  पूर्णांक is_capture, u16 state)
अणु
	पूर्णांक i;

	/* max 2*PCMOnlyGranularity = 2*1024 at 44100 = < 50 ms:
	 * समयout 50 ms */
	क्रम (i = 0; i != 50; ++i) अणु
		u16 current_state;
		पूर्णांक err = lx_pipe_state(chip, pipe, is_capture, &current_state);

		अगर (err < 0)
			वापस err;

		अगर (!err && current_state == state)
			वापस 0;

		mdelay(1);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

पूर्णांक lx_pipe_रुको_क्रम_start(काष्ठा lx6464es *chip, u32 pipe, पूर्णांक is_capture)
अणु
	वापस lx_pipe_रुको_क्रम_state(chip, pipe, is_capture, PSTATE_RUN);
पूर्ण

पूर्णांक lx_pipe_रुको_क्रम_idle(काष्ठा lx6464es *chip, u32 pipe, पूर्णांक is_capture)
अणु
	वापस lx_pipe_रुको_क्रम_state(chip, pipe, is_capture, PSTATE_IDLE);
पूर्ण

/* low-level stream handling */
पूर्णांक lx_stream_set_state(काष्ठा lx6464es *chip, u32 pipe,
			       पूर्णांक is_capture, क्रमागत stream_state_t state)
अणु
	पूर्णांक err;
	u32 pipe_cmd = PIPE_INFO_TO_CMD(is_capture, pipe);

	mutex_lock(&chip->msg_lock);
	lx_message_init(&chip->rmh, CMD_13_SET_STREAM_STATE);

	chip->rmh.cmd[0] |= pipe_cmd;
	chip->rmh.cmd[0] |= state;

	err = lx_message_send_atomic(chip, &chip->rmh);
	mutex_unlock(&chip->msg_lock);

	वापस err;
पूर्ण

पूर्णांक lx_stream_set_क्रमmat(काष्ठा lx6464es *chip, काष्ठा snd_pcm_runसमय *runसमय,
			 u32 pipe, पूर्णांक is_capture)
अणु
	पूर्णांक err;
	u32 pipe_cmd = PIPE_INFO_TO_CMD(is_capture, pipe);
	u32 channels = runसमय->channels;

	अगर (runसमय->channels != channels)
		dev_err(chip->card->dev, "channel count mismatch: %d vs %d",
			   runसमय->channels, channels);

	mutex_lock(&chip->msg_lock);
	lx_message_init(&chip->rmh, CMD_0C_DEF_STREAM);

	chip->rmh.cmd[0] |= pipe_cmd;

	अगर (runसमय->sample_bits == 16)
		/* 16 bit क्रमmat */
		chip->rmh.cmd[0] |= (STREAM_FMT_16b << STREAM_FMT_OFFSET);

	अगर (snd_pcm_क्रमmat_little_endian(runसमय->क्रमmat))
		/* little endian/पूर्णांकel क्रमmat */
		chip->rmh.cmd[0] |= (STREAM_FMT_पूर्णांकel << STREAM_FMT_OFFSET);

	chip->rmh.cmd[0] |= channels-1;

	err = lx_message_send_atomic(chip, &chip->rmh);
	mutex_unlock(&chip->msg_lock);

	वापस err;
पूर्ण

पूर्णांक lx_stream_state(काष्ठा lx6464es *chip, u32 pipe, पूर्णांक is_capture,
		    पूर्णांक *rstate)
अणु
	पूर्णांक err;
	u32 pipe_cmd = PIPE_INFO_TO_CMD(is_capture, pipe);

	mutex_lock(&chip->msg_lock);
	lx_message_init(&chip->rmh, CMD_0E_GET_STREAM_SPL_COUNT);

	chip->rmh.cmd[0] |= pipe_cmd;

	err = lx_message_send_atomic(chip, &chip->rmh);

	*rstate = (chip->rmh.stat[0] & SF_START) ? START_STATE : PAUSE_STATE;

	mutex_unlock(&chip->msg_lock);
	वापस err;
पूर्ण

पूर्णांक lx_stream_sample_position(काष्ठा lx6464es *chip, u32 pipe, पूर्णांक is_capture,
			      u64 *r_bytepos)
अणु
	पूर्णांक err;
	u32 pipe_cmd = PIPE_INFO_TO_CMD(is_capture, pipe);

	mutex_lock(&chip->msg_lock);
	lx_message_init(&chip->rmh, CMD_0E_GET_STREAM_SPL_COUNT);

	chip->rmh.cmd[0] |= pipe_cmd;

	err = lx_message_send_atomic(chip, &chip->rmh);

	*r_bytepos = ((u64) (chip->rmh.stat[0] & MASK_SPL_COUNT_HI)
		      << 32)	     /* hi part */
		+ chip->rmh.stat[1]; /* lo part */

	mutex_unlock(&chip->msg_lock);
	वापस err;
पूर्ण

/* low-level buffer handling */
पूर्णांक lx_buffer_give(काष्ठा lx6464es *chip, u32 pipe, पूर्णांक is_capture,
		   u32 buffer_size, u32 buf_address_lo, u32 buf_address_hi,
		   u32 *r_buffer_index)
अणु
	पूर्णांक err;
	u32 pipe_cmd = PIPE_INFO_TO_CMD(is_capture, pipe);

	mutex_lock(&chip->msg_lock);
	lx_message_init(&chip->rmh, CMD_0F_UPDATE_BUFFER);

	chip->rmh.cmd[0] |= pipe_cmd;
	chip->rmh.cmd[0] |= BF_NOTIFY_EOB; /* request पूर्णांकerrupt notअगरication */

	/* toकरो: छोड़ो request, circular buffer */

	chip->rmh.cmd[1] = buffer_size & MASK_DATA_SIZE;
	chip->rmh.cmd[2] = buf_address_lo;

	अगर (buf_address_hi) अणु
		chip->rmh.cmd_len = 4;
		chip->rmh.cmd[3] = buf_address_hi;
		chip->rmh.cmd[0] |= BF_64BITS_ADR;
	पूर्ण

	err = lx_message_send_atomic(chip, &chip->rmh);

	अगर (err == 0) अणु
		*r_buffer_index = chip->rmh.stat[0];
		जाओ करोne;
	पूर्ण

	अगर (err == EB_RBUFFERS_TABLE_OVERFLOW)
		dev_err(chip->card->dev,
			"lx_buffer_give EB_RBUFFERS_TABLE_OVERFLOW\n");

	अगर (err == EB_INVALID_STREAM)
		dev_err(chip->card->dev,
			"lx_buffer_give EB_INVALID_STREAM\n");

	अगर (err == EB_CMD_REFUSED)
		dev_err(chip->card->dev,
			"lx_buffer_give EB_CMD_REFUSED\n");

 करोne:
	mutex_unlock(&chip->msg_lock);
	वापस err;
पूर्ण

पूर्णांक lx_buffer_मुक्त(काष्ठा lx6464es *chip, u32 pipe, पूर्णांक is_capture,
		   u32 *r_buffer_size)
अणु
	पूर्णांक err;
	u32 pipe_cmd = PIPE_INFO_TO_CMD(is_capture, pipe);

	mutex_lock(&chip->msg_lock);
	lx_message_init(&chip->rmh, CMD_11_CANCEL_BUFFER);

	chip->rmh.cmd[0] |= pipe_cmd;
	chip->rmh.cmd[0] |= MASK_BUFFER_ID; /* ask क्रम the current buffer: the
					     * microblaze will seek क्रम it */

	err = lx_message_send_atomic(chip, &chip->rmh);

	अगर (err == 0)
		*r_buffer_size = chip->rmh.stat[0]  & MASK_DATA_SIZE;

	mutex_unlock(&chip->msg_lock);
	वापस err;
पूर्ण

पूर्णांक lx_buffer_cancel(काष्ठा lx6464es *chip, u32 pipe, पूर्णांक is_capture,
		     u32 buffer_index)
अणु
	पूर्णांक err;
	u32 pipe_cmd = PIPE_INFO_TO_CMD(is_capture, pipe);

	mutex_lock(&chip->msg_lock);
	lx_message_init(&chip->rmh, CMD_11_CANCEL_BUFFER);

	chip->rmh.cmd[0] |= pipe_cmd;
	chip->rmh.cmd[0] |= buffer_index;

	err = lx_message_send_atomic(chip, &chip->rmh);

	mutex_unlock(&chip->msg_lock);
	वापस err;
पूर्ण


/* low-level gain/peak handling
 *
 * \टoकरो: can we unmute capture/playback channels independently?
 *
 * */
पूर्णांक lx_level_unmute(काष्ठा lx6464es *chip, पूर्णांक is_capture, पूर्णांक unmute)
अणु
	पूर्णांक err;
	/* bit set to 1: channel muted */
	u64 mute_mask = unmute ? 0 : 0xFFFFFFFFFFFFFFFFLLU;

	mutex_lock(&chip->msg_lock);
	lx_message_init(&chip->rmh, CMD_0D_SET_MUTE);

	chip->rmh.cmd[0] |= PIPE_INFO_TO_CMD(is_capture, 0);

	chip->rmh.cmd[1] = (u32)(mute_mask >> (u64)32);	       /* hi part */
	chip->rmh.cmd[2] = (u32)(mute_mask & (u64)0xFFFFFFFF); /* lo part */

	dev_dbg(chip->card->dev,
		"mute %x %x %x\n", chip->rmh.cmd[0], chip->rmh.cmd[1],
		   chip->rmh.cmd[2]);

	err = lx_message_send_atomic(chip, &chip->rmh);

	mutex_unlock(&chip->msg_lock);
	वापस err;
पूर्ण

अटल स्थिर u32 peak_map[] = अणु
	0x00000109, /* -90.308dB */
	0x0000083B, /* -72.247dB */
	0x000020C4, /* -60.205dB */
	0x00008273, /* -48.030dB */
	0x00020756, /* -36.005dB */
	0x00040C37, /* -30.001dB */
	0x00081385, /* -24.002dB */
	0x00101D3F, /* -18.000dB */
	0x0016C310, /* -15.000dB */
	0x002026F2, /* -12.001dB */
	0x002D6A86, /* -9.000dB */
	0x004026E6, /* -6.004dB */
	0x005A9DF6, /* -3.000dB */
	0x0065AC8B, /* -2.000dB */
	0x00721481, /* -1.000dB */
	0x007FFFFF, /* FS */
पूर्ण;

पूर्णांक lx_level_peaks(काष्ठा lx6464es *chip, पूर्णांक is_capture, पूर्णांक channels,
		   u32 *r_levels)
अणु
	पूर्णांक err = 0;
	पूर्णांक i;

	mutex_lock(&chip->msg_lock);
	क्रम (i = 0; i < channels; i += 4) अणु
		u32 s0, s1, s2, s3;

		lx_message_init(&chip->rmh, CMD_12_GET_PEAK);
		chip->rmh.cmd[0] |= PIPE_INFO_TO_CMD(is_capture, i);

		err = lx_message_send_atomic(chip, &chip->rmh);

		अगर (err == 0) अणु
			s0 = peak_map[chip->rmh.stat[0] & 0x0F];
			s1 = peak_map[(chip->rmh.stat[0] >>  4) & 0xf];
			s2 = peak_map[(chip->rmh.stat[0] >>  8) & 0xf];
			s3 = peak_map[(chip->rmh.stat[0] >>  12) & 0xf];
		पूर्ण अन्यथा
			s0 = s1 = s2 = s3 = 0;

		r_levels[0] = s0;
		r_levels[1] = s1;
		r_levels[2] = s2;
		r_levels[3] = s3;

		r_levels += 4;
	पूर्ण

	mutex_unlock(&chip->msg_lock);
	वापस err;
पूर्ण

/* पूर्णांकerrupt handling */
#घोषणा PCX_IRQ_NONE 0
#घोषणा IRQCS_ACTIVE_PCIDB	BIT(13)
#घोषणा IRQCS_ENABLE_PCIIRQ	BIT(8)
#घोषणा IRQCS_ENABLE_PCIDB	BIT(9)

अटल u32 lx_पूर्णांकerrupt_test_ack(काष्ठा lx6464es *chip)
अणु
	u32 irqcs = lx_plx_reg_पढ़ो(chip, ePLX_IRQCS);

	/* Test अगर PCI Doorbell पूर्णांकerrupt is active */
	अगर (irqcs & IRQCS_ACTIVE_PCIDB)	अणु
		u32 temp;
		irqcs = PCX_IRQ_NONE;

		जबतक ((temp = lx_plx_reg_पढ़ो(chip, ePLX_L2PCIDB))) अणु
			/* RAZ पूर्णांकerrupt */
			irqcs |= temp;
			lx_plx_reg_ग_लिखो(chip, ePLX_L2PCIDB, temp);
		पूर्ण

		वापस irqcs;
	पूर्ण
	वापस PCX_IRQ_NONE;
पूर्ण

अटल पूर्णांक lx_पूर्णांकerrupt_ack(काष्ठा lx6464es *chip, u32 *r_irqsrc,
			    पूर्णांक *r_async_pending, पूर्णांक *r_async_escmd)
अणु
	u32 irq_async;
	u32 irqsrc = lx_पूर्णांकerrupt_test_ack(chip);

	अगर (irqsrc == PCX_IRQ_NONE)
		वापस 0;

	*r_irqsrc = irqsrc;

	irq_async = irqsrc & MASK_SYS_ASYNC_EVENTS; /* + EtherSound response
						     * (set by xilinx) + EOB */

	अगर (irq_async & MASK_SYS_STATUS_ESA) अणु
		irq_async &= ~MASK_SYS_STATUS_ESA;
		*r_async_escmd = 1;
	पूर्ण

	अगर (irq_async) अणु
		/* dev_dbg(chip->card->dev, "interrupt: async event pending\n"); */
		*r_async_pending = 1;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक lx_पूर्णांकerrupt_handle_async_events(काष्ठा lx6464es *chip, u32 irqsrc,
					    पूर्णांक *r_freq_changed,
					    u64 *r_notअगरied_in_pipe_mask,
					    u64 *r_notअगरied_out_pipe_mask)
अणु
	पूर्णांक err;
	u32 stat[9];		/* answer from CMD_04_GET_EVENT */

	/* We can optimize this to not पढ़ो dumb events.
	 * Answer words are in the following order:
	 * Stat[0]	general status
	 * Stat[1]	end of buffer OUT pF
	 * Stat[2]	end of buffer OUT pf
	 * Stat[3]	end of buffer IN pF
	 * Stat[4]	end of buffer IN pf
	 * Stat[5]	MSB underrun
	 * Stat[6]	LSB underrun
	 * Stat[7]	MSB overrun
	 * Stat[8]	LSB overrun
	 * */

	पूर्णांक eb_pending_out = (irqsrc & MASK_SYS_STATUS_EOBO) ? 1 : 0;
	पूर्णांक eb_pending_in  = (irqsrc & MASK_SYS_STATUS_EOBI) ? 1 : 0;

	*r_freq_changed = (irqsrc & MASK_SYS_STATUS_FREQ) ? 1 : 0;

	err = lx_dsp_पढ़ो_async_events(chip, stat);
	अगर (err < 0)
		वापस err;

	अगर (eb_pending_in) अणु
		*r_notअगरied_in_pipe_mask = ((u64)stat[3] << 32)
			+ stat[4];
		dev_dbg(chip->card->dev, "interrupt: EOBI pending %llx\n",
			    *r_notअगरied_in_pipe_mask);
	पूर्ण
	अगर (eb_pending_out) अणु
		*r_notअगरied_out_pipe_mask = ((u64)stat[1] << 32)
			+ stat[2];
		dev_dbg(chip->card->dev, "interrupt: EOBO pending %llx\n",
			    *r_notअगरied_out_pipe_mask);
	पूर्ण

	/* toकरो: handle xrun notअगरication */

	वापस err;
पूर्ण

अटल पूर्णांक lx_पूर्णांकerrupt_request_new_buffer(काष्ठा lx6464es *chip,
					   काष्ठा lx_stream *lx_stream)
अणु
	काष्ठा snd_pcm_substream *substream = lx_stream->stream;
	स्थिर अचिन्हित पूर्णांक is_capture = lx_stream->is_capture;
	पूर्णांक err;

	स्थिर u32 channels = substream->runसमय->channels;
	स्थिर u32 bytes_per_frame = channels * 3;
	स्थिर u32 period_size = substream->runसमय->period_size;
	स्थिर u32 period_bytes = period_size * bytes_per_frame;
	स्थिर u32 pos = lx_stream->frame_pos;
	स्थिर u32 next_pos = ((pos+1) == substream->runसमय->periods) ?
		0 : pos + 1;

	dma_addr_t buf = substream->dma_buffer.addr + pos * period_bytes;
	u32 buf_hi = 0;
	u32 buf_lo = 0;
	u32 buffer_index = 0;

	u32 needed, मुक्तd;
	u32 size_array[MAX_STREAM_BUFFER];

	dev_dbg(chip->card->dev, "->lx_interrupt_request_new_buffer\n");

	mutex_lock(&chip->lock);

	err = lx_buffer_ask(chip, 0, is_capture, &needed, &मुक्तd, size_array);
	dev_dbg(chip->card->dev,
		"interrupt: needed %d, freed %d\n", needed, मुक्तd);

	unpack_poपूर्णांकer(buf, &buf_lo, &buf_hi);
	err = lx_buffer_give(chip, 0, is_capture, period_bytes, buf_lo, buf_hi,
			     &buffer_index);
	dev_dbg(chip->card->dev,
		"interrupt: gave buffer index %x on 0x%lx (%d bytes)\n",
		    buffer_index, (अचिन्हित दीर्घ)buf, period_bytes);

	lx_stream->frame_pos = next_pos;
	mutex_unlock(&chip->lock);

	वापस err;
पूर्ण

irqवापस_t lx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा lx6464es *chip = dev_id;
	पूर्णांक async_pending, async_escmd;
	u32 irqsrc;
	bool wake_thपढ़ो = false;

	dev_dbg(chip->card->dev,
		"**************************************************\n");

	अगर (!lx_पूर्णांकerrupt_ack(chip, &irqsrc, &async_pending, &async_escmd)) अणु
		dev_dbg(chip->card->dev, "IRQ_NONE\n");
		वापस IRQ_NONE; /* this device did not cause the पूर्णांकerrupt */
	पूर्ण

	अगर (irqsrc & MASK_SYS_STATUS_CMD_DONE)
		वापस IRQ_HANDLED;

	अगर (irqsrc & MASK_SYS_STATUS_EOBI)
		dev_dbg(chip->card->dev, "interrupt: EOBI\n");

	अगर (irqsrc & MASK_SYS_STATUS_EOBO)
		dev_dbg(chip->card->dev, "interrupt: EOBO\n");

	अगर (irqsrc & MASK_SYS_STATUS_URUN)
		dev_dbg(chip->card->dev, "interrupt: URUN\n");

	अगर (irqsrc & MASK_SYS_STATUS_ORUN)
		dev_dbg(chip->card->dev, "interrupt: ORUN\n");

	अगर (async_pending) अणु
		wake_thपढ़ो = true;
		chip->irqsrc = irqsrc;
	पूर्ण

	अगर (async_escmd) अणु
		/* backकरोor क्रम ethersound commands
		 *
		 * क्रम now, we करो not need this
		 *
		 * */

		dev_dbg(chip->card->dev, "interrupt requests escmd handling\n");
	पूर्ण

	वापस wake_thपढ़ो ? IRQ_WAKE_THREAD : IRQ_HANDLED;
पूर्ण

irqवापस_t lx_thपढ़ोed_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा lx6464es *chip = dev_id;
	u64 notअगरied_in_pipe_mask = 0;
	u64 notअगरied_out_pipe_mask = 0;
	पूर्णांक freq_changed;
	पूर्णांक err;

	/* handle async events */
	err = lx_पूर्णांकerrupt_handle_async_events(chip, chip->irqsrc,
					       &freq_changed,
					       &notअगरied_in_pipe_mask,
					       &notअगरied_out_pipe_mask);
	अगर (err)
		dev_err(chip->card->dev, "error handling async events\n");

	अगर (notअगरied_in_pipe_mask) अणु
		काष्ठा lx_stream *lx_stream = &chip->capture_stream;

		dev_dbg(chip->card->dev,
			"requesting audio transfer for capture\n");
		err = lx_पूर्णांकerrupt_request_new_buffer(chip, lx_stream);
		अगर (err < 0)
			dev_err(chip->card->dev,
				"cannot request new buffer for capture\n");
		snd_pcm_period_elapsed(lx_stream->stream);
	पूर्ण

	अगर (notअगरied_out_pipe_mask) अणु
		काष्ठा lx_stream *lx_stream = &chip->playback_stream;

		dev_dbg(chip->card->dev,
			"requesting audio transfer for playback\n");
		err = lx_पूर्णांकerrupt_request_new_buffer(chip, lx_stream);
		अगर (err < 0)
			dev_err(chip->card->dev,
				"cannot request new buffer for playback\n");
		snd_pcm_period_elapsed(lx_stream->stream);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण


अटल व्योम lx_irq_set(काष्ठा lx6464es *chip, पूर्णांक enable)
अणु
	u32 reg = lx_plx_reg_पढ़ो(chip, ePLX_IRQCS);

	/* enable/disable पूर्णांकerrupts
	 *
	 * Set the Doorbell and PCI पूर्णांकerrupt enable bits
	 *
	 * */
	अगर (enable)
		reg |=  (IRQCS_ENABLE_PCIIRQ | IRQCS_ENABLE_PCIDB);
	अन्यथा
		reg &= ~(IRQCS_ENABLE_PCIIRQ | IRQCS_ENABLE_PCIDB);
	lx_plx_reg_ग_लिखो(chip, ePLX_IRQCS, reg);
पूर्ण

व्योम lx_irq_enable(काष्ठा lx6464es *chip)
अणु
	dev_dbg(chip->card->dev, "->lx_irq_enable\n");
	lx_irq_set(chip, 1);
पूर्ण

व्योम lx_irq_disable(काष्ठा lx6464es *chip)
अणु
	dev_dbg(chip->card->dev, "->lx_irq_disable\n");
	lx_irq_set(chip, 0);
पूर्ण
