<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI Virtual Channel support
 *
 * Copyright (C) 2013 Red Hat, Inc.  All rights reserved.
 *     Author: Alex Williamson <alex.williamson@redhat.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_regs.h>
#समावेश <linux/types.h>

#समावेश "pci.h"

/**
 * pci_vc_save_restore_dwords - Save or restore a series of dwords
 * @dev: device
 * @pos: starting config space position
 * @buf: buffer to save to or restore from
 * @dwords: number of dwords to save/restore
 * @save: whether to save or restore
 */
अटल व्योम pci_vc_save_restore_dwords(काष्ठा pci_dev *dev, पूर्णांक pos,
				       u32 *buf, पूर्णांक dwords, bool save)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dwords; i++, buf++) अणु
		अगर (save)
			pci_पढ़ो_config_dword(dev, pos + (i * 4), buf);
		अन्यथा
			pci_ग_लिखो_config_dword(dev, pos + (i * 4), *buf);
	पूर्ण
पूर्ण

/**
 * pci_vc_load_arb_table - load and रुको क्रम VC arbitration table
 * @dev: device
 * @pos: starting position of VC capability (VC/VC9/MFVC)
 *
 * Set Load VC Arbitration Table bit requesting hardware to apply the VC
 * Arbitration Table (previously loaded).  When the VC Arbitration Table
 * Status clears, hardware has latched the table पूर्णांकo VC arbitration logic.
 */
अटल व्योम pci_vc_load_arb_table(काष्ठा pci_dev *dev, पूर्णांक pos)
अणु
	u16 ctrl;

	pci_पढ़ो_config_word(dev, pos + PCI_VC_PORT_CTRL, &ctrl);
	pci_ग_लिखो_config_word(dev, pos + PCI_VC_PORT_CTRL,
			      ctrl | PCI_VC_PORT_CTRL_LOAD_TABLE);
	अगर (pci_रुको_क्रम_pending(dev, pos + PCI_VC_PORT_STATUS,
				 PCI_VC_PORT_STATUS_TABLE))
		वापस;

	pci_err(dev, "VC arbitration table failed to load\n");
पूर्ण

/**
 * pci_vc_load_port_arb_table - Load and रुको क्रम VC port arbitration table
 * @dev: device
 * @pos: starting position of VC capability (VC/VC9/MFVC)
 * @res: VC resource number, ie. VCn (0-7)
 *
 * Set Load Port Arbitration Table bit requesting hardware to apply the Port
 * Arbitration Table (previously loaded).  When the Port Arbitration Table
 * Status clears, hardware has latched the table पूर्णांकo port arbitration logic.
 */
अटल व्योम pci_vc_load_port_arb_table(काष्ठा pci_dev *dev, पूर्णांक pos, पूर्णांक res)
अणु
	पूर्णांक ctrl_pos, status_pos;
	u32 ctrl;

	ctrl_pos = pos + PCI_VC_RES_CTRL + (res * PCI_CAP_VC_PER_VC_SIZखातापूर्ण);
	status_pos = pos + PCI_VC_RES_STATUS + (res * PCI_CAP_VC_PER_VC_SIZखातापूर्ण);

	pci_पढ़ो_config_dword(dev, ctrl_pos, &ctrl);
	pci_ग_लिखो_config_dword(dev, ctrl_pos,
			       ctrl | PCI_VC_RES_CTRL_LOAD_TABLE);

	अगर (pci_रुको_क्रम_pending(dev, status_pos, PCI_VC_RES_STATUS_TABLE))
		वापस;

	pci_err(dev, "VC%d port arbitration table failed to load\n", res);
पूर्ण

/**
 * pci_vc_enable - Enable भव channel
 * @dev: device
 * @pos: starting position of VC capability (VC/VC9/MFVC)
 * @res: VC res number, ie. VCn (0-7)
 *
 * A VC is enabled by setting the enable bit in matching resource control
 * रेजिस्टरs on both sides of a link.  We thereक्रमe need to find the opposite
 * end of the link.  To keep this simple we enable from the करोwnstream device.
 * RC devices करो not have an upstream device, nor करोes it seem that VC9 करो
 * (spec is unclear).  Once we find the upstream device, match the VC ID to
 * get the correct resource, disable and enable on both ends.
 */
अटल व्योम pci_vc_enable(काष्ठा pci_dev *dev, पूर्णांक pos, पूर्णांक res)
अणु
	पूर्णांक ctrl_pos, status_pos, id, pos2, evcc, i, ctrl_pos2, status_pos2;
	u32 ctrl, header, cap1, ctrl2;
	काष्ठा pci_dev *link = शून्य;

	/* Enable VCs from the करोwnstream device */
	अगर (!pci_is_pcie(dev) || !pcie_करोwnstream_port(dev))
		वापस;

	ctrl_pos = pos + PCI_VC_RES_CTRL + (res * PCI_CAP_VC_PER_VC_SIZखातापूर्ण);
	status_pos = pos + PCI_VC_RES_STATUS + (res * PCI_CAP_VC_PER_VC_SIZखातापूर्ण);

	pci_पढ़ो_config_dword(dev, ctrl_pos, &ctrl);
	id = ctrl & PCI_VC_RES_CTRL_ID;

	pci_पढ़ो_config_dword(dev, pos, &header);

	/* If there is no opposite end of the link, skip to enable */
	अगर (PCI_EXT_CAP_ID(header) == PCI_EXT_CAP_ID_VC9 ||
	    pci_is_root_bus(dev->bus))
		जाओ enable;

	pos2 = pci_find_ext_capability(dev->bus->self, PCI_EXT_CAP_ID_VC);
	अगर (!pos2)
		जाओ enable;

	pci_पढ़ो_config_dword(dev->bus->self, pos2 + PCI_VC_PORT_CAP1, &cap1);
	evcc = cap1 & PCI_VC_CAP1_EVCC;

	/* VC0 is hardwired enabled, so we can start with 1 */
	क्रम (i = 1; i < evcc + 1; i++) अणु
		ctrl_pos2 = pos2 + PCI_VC_RES_CTRL +
				(i * PCI_CAP_VC_PER_VC_SIZखातापूर्ण);
		status_pos2 = pos2 + PCI_VC_RES_STATUS +
				(i * PCI_CAP_VC_PER_VC_SIZखातापूर्ण);
		pci_पढ़ो_config_dword(dev->bus->self, ctrl_pos2, &ctrl2);
		अगर ((ctrl2 & PCI_VC_RES_CTRL_ID) == id) अणु
			link = dev->bus->self;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!link)
		जाओ enable;

	/* Disable अगर enabled */
	अगर (ctrl2 & PCI_VC_RES_CTRL_ENABLE) अणु
		ctrl2 &= ~PCI_VC_RES_CTRL_ENABLE;
		pci_ग_लिखो_config_dword(link, ctrl_pos2, ctrl2);
	पूर्ण

	/* Enable on both ends */
	ctrl2 |= PCI_VC_RES_CTRL_ENABLE;
	pci_ग_लिखो_config_dword(link, ctrl_pos2, ctrl2);
enable:
	ctrl |= PCI_VC_RES_CTRL_ENABLE;
	pci_ग_लिखो_config_dword(dev, ctrl_pos, ctrl);

	अगर (!pci_रुको_क्रम_pending(dev, status_pos, PCI_VC_RES_STATUS_NEGO))
		pci_err(dev, "VC%d negotiation stuck pending\n", id);

	अगर (link && !pci_रुको_क्रम_pending(link, status_pos2,
					  PCI_VC_RES_STATUS_NEGO))
		pci_err(link, "VC%d negotiation stuck pending\n", id);
पूर्ण

/**
 * pci_vc_करो_save_buffer - Size, save, or restore VC state
 * @dev: device
 * @pos: starting position of VC capability (VC/VC9/MFVC)
 * @save_state: buffer क्रम save/restore
 * @save: अगर provided a buffer, this indicates what to करो with it
 *
 * Walking Virtual Channel config space to size, save, or restore it
 * is complicated, so we करो it all from one function to reduce code and
 * guarantee ordering matches in the buffer.  When called with शून्य
 * @save_state, वापस the size of the necessary save buffer.  When called
 * with a non-शून्य @save_state, @save determines whether we save to the
 * buffer or restore from it.
 */
अटल पूर्णांक pci_vc_करो_save_buffer(काष्ठा pci_dev *dev, पूर्णांक pos,
				 काष्ठा pci_cap_saved_state *save_state,
				 bool save)
अणु
	u32 cap1;
	अक्षर evcc, lpevcc, parb_size;
	पूर्णांक i, len = 0;
	u8 *buf = save_state ? (u8 *)save_state->cap.data : शून्य;

	/* Sanity check buffer size क्रम save/restore */
	अगर (buf && save_state->cap.size !=
	    pci_vc_करो_save_buffer(dev, pos, शून्य, save)) अणु
		pci_err(dev, "VC save buffer size does not match @0x%x\n", pos);
		वापस -ENOMEM;
	पूर्ण

	pci_पढ़ो_config_dword(dev, pos + PCI_VC_PORT_CAP1, &cap1);
	/* Extended VC Count (not counting VC0) */
	evcc = cap1 & PCI_VC_CAP1_EVCC;
	/* Low Priority Extended VC Count (not counting VC0) */
	lpevcc = (cap1 & PCI_VC_CAP1_LPEVCC) >> 4;
	/* Port Arbitration Table Entry Size (bits) */
	parb_size = 1 << ((cap1 & PCI_VC_CAP1_ARB_SIZE) >> 10);

	/*
	 * Port VC Control Register contains VC Arbitration Select, which
	 * cannot be modअगरied when more than one LPVC is in operation.  We
	 * thereक्रमe save/restore it first, as only VC0 should be enabled
	 * after device reset.
	 */
	अगर (buf) अणु
		अगर (save)
			pci_पढ़ो_config_word(dev, pos + PCI_VC_PORT_CTRL,
					     (u16 *)buf);
		अन्यथा
			pci_ग_लिखो_config_word(dev, pos + PCI_VC_PORT_CTRL,
					      *(u16 *)buf);
		buf += 4;
	पूर्ण
	len += 4;

	/*
	 * If we have any Low Priority VCs and a VC Arbitration Table Offset
	 * in Port VC Capability Register 2 then save/restore it next.
	 */
	अगर (lpevcc) अणु
		u32 cap2;
		पूर्णांक vcarb_offset;

		pci_पढ़ो_config_dword(dev, pos + PCI_VC_PORT_CAP2, &cap2);
		vcarb_offset = ((cap2 & PCI_VC_CAP2_ARB_OFF) >> 24) * 16;

		अगर (vcarb_offset) अणु
			पूर्णांक size, vcarb_phases = 0;

			अगर (cap2 & PCI_VC_CAP2_128_PHASE)
				vcarb_phases = 128;
			अन्यथा अगर (cap2 & PCI_VC_CAP2_64_PHASE)
				vcarb_phases = 64;
			अन्यथा अगर (cap2 & PCI_VC_CAP2_32_PHASE)
				vcarb_phases = 32;

			/* Fixed 4 bits per phase per lpevcc (plus VC0) */
			size = ((lpevcc + 1) * vcarb_phases * 4) / 8;

			अगर (size && buf) अणु
				pci_vc_save_restore_dwords(dev,
							   pos + vcarb_offset,
							   (u32 *)buf,
							   size / 4, save);
				/*
				 * On restore, we need to संकेत hardware to
				 * re-load the VC Arbitration Table.
				 */
				अगर (!save)
					pci_vc_load_arb_table(dev, pos);

				buf += size;
			पूर्ण
			len += size;
		पूर्ण
	पूर्ण

	/*
	 * In addition to each VC Resource Control Register, we may have a
	 * Port Arbitration Table attached to each VC.  The Port Arbitration
	 * Table Offset in each VC Resource Capability Register tells us अगर
	 * it exists.  The entry size is global from the Port VC Capability
	 * Register1 above.  The number of phases is determined per VC.
	 */
	क्रम (i = 0; i < evcc + 1; i++) अणु
		u32 cap;
		पूर्णांक parb_offset;

		pci_पढ़ो_config_dword(dev, pos + PCI_VC_RES_CAP +
				      (i * PCI_CAP_VC_PER_VC_SIZखातापूर्ण), &cap);
		parb_offset = ((cap & PCI_VC_RES_CAP_ARB_OFF) >> 24) * 16;
		अगर (parb_offset) अणु
			पूर्णांक size, parb_phases = 0;

			अगर (cap & PCI_VC_RES_CAP_256_PHASE)
				parb_phases = 256;
			अन्यथा अगर (cap & (PCI_VC_RES_CAP_128_PHASE |
					PCI_VC_RES_CAP_128_PHASE_TB))
				parb_phases = 128;
			अन्यथा अगर (cap & PCI_VC_RES_CAP_64_PHASE)
				parb_phases = 64;
			अन्यथा अगर (cap & PCI_VC_RES_CAP_32_PHASE)
				parb_phases = 32;

			size = (parb_size * parb_phases) / 8;

			अगर (size && buf) अणु
				pci_vc_save_restore_dwords(dev,
							   pos + parb_offset,
							   (u32 *)buf,
							   size / 4, save);
				buf += size;
			पूर्ण
			len += size;
		पूर्ण

		/* VC Resource Control Register */
		अगर (buf) अणु
			पूर्णांक ctrl_pos = pos + PCI_VC_RES_CTRL +
						(i * PCI_CAP_VC_PER_VC_SIZखातापूर्ण);
			अगर (save)
				pci_पढ़ो_config_dword(dev, ctrl_pos,
						      (u32 *)buf);
			अन्यथा अणु
				u32 पंचांगp, ctrl = *(u32 *)buf;
				/*
				 * For an FLR हाल, the VC config may reमुख्य.
				 * Preserve enable bit, restore the rest.
				 */
				pci_पढ़ो_config_dword(dev, ctrl_pos, &पंचांगp);
				पंचांगp &= PCI_VC_RES_CTRL_ENABLE;
				पंचांगp |= ctrl & ~PCI_VC_RES_CTRL_ENABLE;
				pci_ग_लिखो_config_dword(dev, ctrl_pos, पंचांगp);
				/* Load port arbitration table अगर used */
				अगर (ctrl & PCI_VC_RES_CTRL_ARB_SELECT)
					pci_vc_load_port_arb_table(dev, pos, i);
				/* Re-enable अगर needed */
				अगर ((ctrl ^ पंचांगp) & PCI_VC_RES_CTRL_ENABLE)
					pci_vc_enable(dev, pos, i);
			पूर्ण
			buf += 4;
		पूर्ण
		len += 4;
	पूर्ण

	वापस buf ? 0 : len;
पूर्ण

अटल काष्ठा अणु
	u16 id;
	स्थिर अक्षर *name;
पूर्ण vc_caps[] = अणु अणु PCI_EXT_CAP_ID_MFVC, "MFVC" पूर्ण,
		अणु PCI_EXT_CAP_ID_VC, "VC" पूर्ण,
		अणु PCI_EXT_CAP_ID_VC9, "VC9" पूर्ण पूर्ण;

/**
 * pci_save_vc_state - Save VC state to pre-allocate save buffer
 * @dev: device
 *
 * For each type of VC capability, VC/VC9/MFVC, find the capability and
 * save it to the pre-allocated save buffer.
 */
पूर्णांक pci_save_vc_state(काष्ठा pci_dev *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(vc_caps); i++) अणु
		पूर्णांक pos, ret;
		काष्ठा pci_cap_saved_state *save_state;

		pos = pci_find_ext_capability(dev, vc_caps[i].id);
		अगर (!pos)
			जारी;

		save_state = pci_find_saved_ext_cap(dev, vc_caps[i].id);
		अगर (!save_state) अणु
			pci_err(dev, "%s buffer not found in %s\n",
				vc_caps[i].name, __func__);
			वापस -ENOMEM;
		पूर्ण

		ret = pci_vc_करो_save_buffer(dev, pos, save_state, true);
		अगर (ret) अणु
			pci_err(dev, "%s save unsuccessful %s\n",
				vc_caps[i].name, __func__);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * pci_restore_vc_state - Restore VC state from save buffer
 * @dev: device
 *
 * For each type of VC capability, VC/VC9/MFVC, find the capability and
 * restore it from the previously saved buffer.
 */
व्योम pci_restore_vc_state(काष्ठा pci_dev *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(vc_caps); i++) अणु
		पूर्णांक pos;
		काष्ठा pci_cap_saved_state *save_state;

		pos = pci_find_ext_capability(dev, vc_caps[i].id);
		save_state = pci_find_saved_ext_cap(dev, vc_caps[i].id);
		अगर (!save_state || !pos)
			जारी;

		pci_vc_करो_save_buffer(dev, pos, save_state, false);
	पूर्ण
पूर्ण

/**
 * pci_allocate_vc_save_buffers - Allocate save buffers क्रम VC caps
 * @dev: device
 *
 * For each type of VC capability, VC/VC9/MFVC, find the capability, size
 * it, and allocate a buffer क्रम save/restore.
 */
व्योम pci_allocate_vc_save_buffers(काष्ठा pci_dev *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(vc_caps); i++) अणु
		पूर्णांक len, pos = pci_find_ext_capability(dev, vc_caps[i].id);

		अगर (!pos)
			जारी;

		len = pci_vc_करो_save_buffer(dev, pos, शून्य, false);
		अगर (pci_add_ext_cap_save_buffer(dev, vc_caps[i].id, len))
			pci_err(dev, "unable to preallocate %s save buffer\n",
				vc_caps[i].name);
	पूर्ण
पूर्ण
