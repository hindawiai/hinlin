<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * dice-extension.c - a part of driver क्रम DICE based devices
 *
 * Copyright (c) 2018 Takashi Sakamoto
 */

#समावेश "dice.h"

/* For TCD2210/2220, TCAT defines extension of application protocol. */

#घोषणा DICE_EXT_APP_SPACE		0xffffe0200000uLL

#घोषणा DICE_EXT_APP_CAPS_OFFSET	0x00
#घोषणा DICE_EXT_APP_CAPS_SIZE		0x04
#घोषणा DICE_EXT_APP_CMD_OFFSET		0x08
#घोषणा DICE_EXT_APP_CMD_SIZE		0x0c
#घोषणा DICE_EXT_APP_MIXER_OFFSET	0x10
#घोषणा DICE_EXT_APP_MIXER_SIZE		0x14
#घोषणा DICE_EXT_APP_PEAK_OFFSET	0x18
#घोषणा DICE_EXT_APP_PEAK_SIZE		0x1c
#घोषणा DICE_EXT_APP_ROUTER_OFFSET	0x20
#घोषणा DICE_EXT_APP_ROUTER_SIZE	0x24
#घोषणा DICE_EXT_APP_STREAM_OFFSET	0x28
#घोषणा DICE_EXT_APP_STREAM_SIZE	0x2c
#घोषणा DICE_EXT_APP_CURRENT_OFFSET	0x30
#घोषणा DICE_EXT_APP_CURRENT_SIZE	0x34
#घोषणा DICE_EXT_APP_STANDALONE_OFFSET	0x38
#घोषणा DICE_EXT_APP_STANDALONE_SIZE	0x3c
#घोषणा DICE_EXT_APP_APPLICATION_OFFSET	0x40
#घोषणा DICE_EXT_APP_APPLICATION_SIZE	0x44

#घोषणा EXT_APP_STREAM_TX_NUMBER	0x0000
#घोषणा EXT_APP_STREAM_RX_NUMBER	0x0004
#घोषणा EXT_APP_STREAM_ENTRIES		0x0008
#घोषणा EXT_APP_STREAM_ENTRY_SIZE	0x010c
#घोषणा  EXT_APP_NUMBER_AUDIO		0x0000
#घोषणा  EXT_APP_NUMBER_MIDI		0x0004
#घोषणा  EXT_APP_NAMES			0x0008
#घोषणा   EXT_APP_NAMES_SIZE		256
#घोषणा  EXT_APP_AC3			0x0108

#घोषणा EXT_APP_CONFIG_LOW_ROUTER	0x0000
#घोषणा EXT_APP_CONFIG_LOW_STREAM	0x1000
#घोषणा EXT_APP_CONFIG_MIDDLE_ROUTER	0x2000
#घोषणा EXT_APP_CONFIG_MIDDLE_STREAM	0x3000
#घोषणा EXT_APP_CONFIG_HIGH_ROUTER	0x4000
#घोषणा EXT_APP_CONFIG_HIGH_STREAM	0x5000

अटल अंतरभूत पूर्णांक पढ़ो_transaction(काष्ठा snd_dice *dice, u64 section_addr,
				   u32 offset, व्योम *buf, माप_प्रकार len)
अणु
	वापस snd_fw_transaction(dice->unit,
				  len == 4 ? TCODE_READ_QUADLET_REQUEST :
					     TCODE_READ_BLOCK_REQUEST,
				  section_addr + offset, buf, len, 0);
पूर्ण

अटल पूर्णांक पढ़ो_stream_entries(काष्ठा snd_dice *dice, u64 section_addr,
			       u32 base_offset, अचिन्हित पूर्णांक stream_count,
			       अचिन्हित पूर्णांक mode,
			       अचिन्हित पूर्णांक pcm_channels[MAX_STREAMS][3],
			       अचिन्हित पूर्णांक midi_ports[MAX_STREAMS])
अणु
	u32 entry_offset;
	__be32 reg[2];
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 0; i < stream_count; ++i) अणु
		entry_offset = base_offset + i * EXT_APP_STREAM_ENTRY_SIZE;
		err = पढ़ो_transaction(dice, section_addr,
				    entry_offset + EXT_APP_NUMBER_AUDIO,
				    reg, माप(reg));
		अगर (err < 0)
			वापस err;
		pcm_channels[i][mode] = be32_to_cpu(reg[0]);
		midi_ports[i] = max(midi_ports[i], be32_to_cpu(reg[1]));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक detect_stream_क्रमmats(काष्ठा snd_dice *dice, u64 section_addr)
अणु
	u32 base_offset;
	__be32 reg[2];
	अचिन्हित पूर्णांक stream_count;
	पूर्णांक mode;
	पूर्णांक err = 0;

	क्रम (mode = 0; mode < SND_DICE_RATE_MODE_COUNT; ++mode) अणु
		अचिन्हित पूर्णांक cap;

		/*
		 * Some models report stream क्रमmats at highest mode, however
		 * they करोn't support the mode. Check घड़ी capabilities.
		 */
		अगर (mode == 2) अणु
			cap = CLOCK_CAP_RATE_176400 | CLOCK_CAP_RATE_192000;
		पूर्ण अन्यथा अगर (mode == 1) अणु
			cap = CLOCK_CAP_RATE_88200 | CLOCK_CAP_RATE_96000;
		पूर्ण अन्यथा अणु
			cap = CLOCK_CAP_RATE_32000 | CLOCK_CAP_RATE_44100 |
			      CLOCK_CAP_RATE_48000;
		पूर्ण
		अगर (!(cap & dice->घड़ी_caps))
			जारी;

		base_offset = 0x2000 * mode + 0x1000;

		err = पढ़ो_transaction(dice, section_addr,
				       base_offset + EXT_APP_STREAM_TX_NUMBER,
				       &reg, माप(reg));
		अगर (err < 0)
			अवरोध;

		base_offset += EXT_APP_STREAM_ENTRIES;
		stream_count = be32_to_cpu(reg[0]);
		err = पढ़ो_stream_entries(dice, section_addr, base_offset,
					  stream_count, mode,
					  dice->tx_pcm_chs,
					  dice->tx_midi_ports);
		अगर (err < 0)
			अवरोध;

		base_offset += stream_count * EXT_APP_STREAM_ENTRY_SIZE;
		stream_count = be32_to_cpu(reg[1]);
		err = पढ़ो_stream_entries(dice, section_addr, base_offset,
					  stream_count,
					  mode, dice->rx_pcm_chs,
					  dice->rx_midi_ports);
		अगर (err < 0)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक snd_dice_detect_extension_क्रमmats(काष्ठा snd_dice *dice)
अणु
	__be32 *poपूर्णांकers;
	अचिन्हित पूर्णांक i;
	u64 section_addr;
	पूर्णांक err;

	poपूर्णांकers = kदो_स्मृति_array(9, माप(__be32) * 2, GFP_KERNEL);
	अगर (poपूर्णांकers == शून्य)
		वापस -ENOMEM;

	err = snd_fw_transaction(dice->unit, TCODE_READ_BLOCK_REQUEST,
				 DICE_EXT_APP_SPACE, poपूर्णांकers,
				 9 * माप(__be32) * 2, 0);
	अगर (err < 0)
		जाओ end;

	/* Check two of them क्रम offset have the same value or not. */
	क्रम (i = 0; i < 9; ++i) अणु
		पूर्णांक j;

		क्रम (j = i + 1; j < 9; ++j) अणु
			अगर (poपूर्णांकers[i * 2] == poपूर्णांकers[j * 2]) अणु
				// Fallback to limited functionality.
				err = -ENXIO;
				जाओ end;
			पूर्ण
		पूर्ण
	पूर्ण

	section_addr = DICE_EXT_APP_SPACE + be32_to_cpu(poपूर्णांकers[12]) * 4;
	err = detect_stream_क्रमmats(dice, section_addr);
end:
	kमुक्त(poपूर्णांकers);
	वापस err;
पूर्ण
