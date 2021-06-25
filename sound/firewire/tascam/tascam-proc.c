<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tascam-proc.h - a part of driver क्रम TASCAM FireWire series
 *
 * Copyright (c) 2015 Takashi Sakamoto
 */

#समावेश "./tascam.h"

अटल व्योम proc_पढ़ो_firmware(काष्ठा snd_info_entry *entry,
			       काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_tscm *tscm = entry->निजी_data;
	__be32 data;
	अचिन्हित पूर्णांक reg, fpga, arm, hw;
	पूर्णांक err;

	err = snd_fw_transaction(tscm->unit, TCODE_READ_QUADLET_REQUEST,
			TSCM_ADDR_BASE + TSCM_OFFSET_FIRMWARE_REGISTER,
			&data, माप(data), 0);
	अगर (err < 0)
		वापस;
	reg = be32_to_cpu(data);

	err = snd_fw_transaction(tscm->unit, TCODE_READ_QUADLET_REQUEST,
			TSCM_ADDR_BASE + TSCM_OFFSET_FIRMWARE_FPGA,
			&data, माप(data), 0);
	अगर (err < 0)
		वापस;
	fpga = be32_to_cpu(data);

	err = snd_fw_transaction(tscm->unit, TCODE_READ_QUADLET_REQUEST,
			TSCM_ADDR_BASE + TSCM_OFFSET_FIRMWARE_ARM,
			&data, माप(data), 0);
	अगर (err < 0)
		वापस;
	arm = be32_to_cpu(data);

	err = snd_fw_transaction(tscm->unit, TCODE_READ_QUADLET_REQUEST,
			TSCM_ADDR_BASE + TSCM_OFFSET_FIRMWARE_HW,
			&data, माप(data), 0);
	अगर (err < 0)
		वापस;
	hw = be32_to_cpu(data);

	snd_iम_लिखो(buffer, "Register: %d (0x%08x)\n", reg & 0xffff, reg);
	snd_iम_लिखो(buffer, "FPGA:     %d (0x%08x)\n", fpga & 0xffff, fpga);
	snd_iम_लिखो(buffer, "ARM:      %d (0x%08x)\n", arm & 0xffff, arm);
	snd_iम_लिखो(buffer, "Hardware: %d (0x%08x)\n", hw >> 16, hw);
पूर्ण

अटल व्योम add_node(काष्ठा snd_tscm *tscm, काष्ठा snd_info_entry *root,
		     स्थिर अक्षर *name,
		     व्योम (*op)(काष्ठा snd_info_entry *e,
				काष्ठा snd_info_buffer *b))
अणु
	काष्ठा snd_info_entry *entry;

	entry = snd_info_create_card_entry(tscm->card, name, root);
	अगर (entry)
		snd_info_set_text_ops(entry, tscm, op);
पूर्ण

व्योम snd_tscm_proc_init(काष्ठा snd_tscm *tscm)
अणु
	काष्ठा snd_info_entry *root;

	/*
	 * All nodes are स्वतःmatically हटाओd at snd_card_disconnect(),
	 * by following to link list.
	 */
	root = snd_info_create_card_entry(tscm->card, "firewire",
					  tscm->card->proc_root);
	अगर (root == शून्य)
		वापस;
	root->mode = S_IFसूची | 0555;

	add_node(tscm, root, "firmware", proc_पढ़ो_firmware);
पूर्ण
