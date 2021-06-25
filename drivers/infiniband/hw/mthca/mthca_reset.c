<शैली गुरु>
/*
 * Copyright (c) 2004 Topspin Communications.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>

#समावेश "mthca_dev.h"
#समावेश "mthca_cmd.h"

पूर्णांक mthca_reset(काष्ठा mthca_dev *mdev)
अणु
	पूर्णांक i;
	पूर्णांक err = 0;
	u32 *hca_header    = शून्य;
	u32 *bridge_header = शून्य;
	काष्ठा pci_dev *bridge = शून्य;
	पूर्णांक bridge_pcix_cap = 0;
	पूर्णांक hca_pcie_cap = 0;
	पूर्णांक hca_pcix_cap = 0;

	u16 devctl;
	u16 linkctl;

#घोषणा MTHCA_RESET_OFFSET 0xf0010
#घोषणा MTHCA_RESET_VALUE  swab32(1)

	/*
	 * Reset the chip.  This is somewhat ugly because we have to
	 * save off the PCI header beक्रमe reset and then restore it
	 * after the chip reboots.  We skip config space offsets 22
	 * and 23 since those have a special meaning.
	 *
	 * To make matters worse, क्रम Tavor (PCI-X HCA) we have to
	 * find the associated bridge device and save off its PCI
	 * header as well.
	 */

	अगर (!(mdev->mthca_flags & MTHCA_FLAG_PCIE)) अणु
		/* Look क्रम the bridge -- its device ID will be 2 more
		   than HCA's device ID. */
		जबतक ((bridge = pci_get_device(mdev->pdev->venकरोr,
						mdev->pdev->device + 2,
						bridge)) != शून्य) अणु
			अगर (bridge->hdr_type    == PCI_HEADER_TYPE_BRIDGE &&
			    bridge->subordinate == mdev->pdev->bus) अणु
				mthca_dbg(mdev, "Found bridge: %s\n",
					  pci_name(bridge));
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!bridge) अणु
			/*
			 * Didn't find a bridge क्रम a Tavor device --
			 * assume we're in no-bridge mode and hope क्रम
			 * the best.
			 */
			mthca_warn(mdev, "No bridge found for %s\n",
				  pci_name(mdev->pdev));
		पूर्ण

	पूर्ण

	/* For Arbel करो we need to save off the full 4K PCI Express header?? */
	hca_header = kदो_स्मृति(256, GFP_KERNEL);
	अगर (!hca_header) अणु
		err = -ENOMEM;
		जाओ put_dev;
	पूर्ण

	क्रम (i = 0; i < 64; ++i) अणु
		अगर (i == 22 || i == 23)
			जारी;
		अगर (pci_पढ़ो_config_dword(mdev->pdev, i * 4, hca_header + i)) अणु
			err = -ENODEV;
			mthca_err(mdev, "Couldn't save HCA "
				  "PCI header, aborting.\n");
			जाओ मुक्त_hca;
		पूर्ण
	पूर्ण

	hca_pcix_cap = pci_find_capability(mdev->pdev, PCI_CAP_ID_PCIX);
	hca_pcie_cap = pci_pcie_cap(mdev->pdev);

	अगर (bridge) अणु
		bridge_header = kदो_स्मृति(256, GFP_KERNEL);
		अगर (!bridge_header) अणु
			err = -ENOMEM;
			जाओ मुक्त_hca;
		पूर्ण

		क्रम (i = 0; i < 64; ++i) अणु
			अगर (i == 22 || i == 23)
				जारी;
			अगर (pci_पढ़ो_config_dword(bridge, i * 4, bridge_header + i)) अणु
				err = -ENODEV;
				mthca_err(mdev, "Couldn't save HCA bridge "
					  "PCI header, aborting.\n");
				जाओ मुक्त_bh;
			पूर्ण
		पूर्ण
		bridge_pcix_cap = pci_find_capability(bridge, PCI_CAP_ID_PCIX);
		अगर (!bridge_pcix_cap) अणु
				err = -ENODEV;
				mthca_err(mdev, "Couldn't locate HCA bridge "
					  "PCI-X capability, aborting.\n");
				जाओ मुक्त_bh;
		पूर्ण
	पूर्ण

	/* actually hit reset */
	अणु
		व्योम __iomem *reset = ioremap(pci_resource_start(mdev->pdev, 0) +
					      MTHCA_RESET_OFFSET, 4);

		अगर (!reset) अणु
			err = -ENOMEM;
			mthca_err(mdev, "Couldn't map HCA reset register, "
				  "aborting.\n");
			जाओ मुक्त_bh;
		पूर्ण

		ग_लिखोl(MTHCA_RESET_VALUE, reset);
		iounmap(reset);
	पूर्ण

	/* Docs say to रुको one second beक्रमe accessing device */
	msleep(1000);

	/* Now रुको क्रम PCI device to start responding again */
	अणु
		u32 v;
		पूर्णांक c = 0;

		क्रम (c = 0; c < 100; ++c) अणु
			अगर (pci_पढ़ो_config_dword(bridge ? bridge : mdev->pdev, 0, &v)) अणु
				err = -ENODEV;
				mthca_err(mdev, "Couldn't access HCA after reset, "
					  "aborting.\n");
				जाओ मुक्त_bh;
			पूर्ण

			अगर (v != 0xffffffff)
				जाओ good;

			msleep(100);
		पूर्ण

		err = -ENODEV;
		mthca_err(mdev, "PCI device did not come back after reset, "
			  "aborting.\n");
		जाओ मुक्त_bh;
	पूर्ण

good:
	/* Now restore the PCI headers */
	अगर (bridge) अणु
		अगर (pci_ग_लिखो_config_dword(bridge, bridge_pcix_cap + 0x8,
				 bridge_header[(bridge_pcix_cap + 0x8) / 4])) अणु
			err = -ENODEV;
			mthca_err(mdev, "Couldn't restore HCA bridge Upstream "
				  "split transaction control, aborting.\n");
			जाओ मुक्त_bh;
		पूर्ण
		अगर (pci_ग_लिखो_config_dword(bridge, bridge_pcix_cap + 0xc,
				 bridge_header[(bridge_pcix_cap + 0xc) / 4])) अणु
			err = -ENODEV;
			mthca_err(mdev, "Couldn't restore HCA bridge Downstream "
				  "split transaction control, aborting.\n");
			जाओ मुक्त_bh;
		पूर्ण
		/*
		 * Bridge control रेजिस्टर is at 0x3e, so we'll
		 * naturally restore it last in this loop.
		 */
		क्रम (i = 0; i < 16; ++i) अणु
			अगर (i * 4 == PCI_COMMAND)
				जारी;

			अगर (pci_ग_लिखो_config_dword(bridge, i * 4, bridge_header[i])) अणु
				err = -ENODEV;
				mthca_err(mdev, "Couldn't restore HCA bridge reg %x, "
					  "aborting.\n", i);
				जाओ मुक्त_bh;
			पूर्ण
		पूर्ण

		अगर (pci_ग_लिखो_config_dword(bridge, PCI_COMMAND,
					   bridge_header[PCI_COMMAND / 4])) अणु
			err = -ENODEV;
			mthca_err(mdev, "Couldn't restore HCA bridge COMMAND, "
				  "aborting.\n");
			जाओ मुक्त_bh;
		पूर्ण
	पूर्ण

	अगर (hca_pcix_cap) अणु
		अगर (pci_ग_लिखो_config_dword(mdev->pdev, hca_pcix_cap,
				 hca_header[hca_pcix_cap / 4])) अणु
			err = -ENODEV;
			mthca_err(mdev, "Couldn't restore HCA PCI-X "
				  "command register, aborting.\n");
			जाओ मुक्त_bh;
		पूर्ण
	पूर्ण

	अगर (hca_pcie_cap) अणु
		devctl = hca_header[(hca_pcie_cap + PCI_EXP_DEVCTL) / 4];
		अगर (pcie_capability_ग_लिखो_word(mdev->pdev, PCI_EXP_DEVCTL,
					       devctl)) अणु
			err = -ENODEV;
			mthca_err(mdev, "Couldn't restore HCA PCI Express "
				  "Device Control register, aborting.\n");
			जाओ मुक्त_bh;
		पूर्ण
		linkctl = hca_header[(hca_pcie_cap + PCI_EXP_LNKCTL) / 4];
		अगर (pcie_capability_ग_लिखो_word(mdev->pdev, PCI_EXP_LNKCTL,
					       linkctl)) अणु
			err = -ENODEV;
			mthca_err(mdev, "Couldn't restore HCA PCI Express "
				  "Link control register, aborting.\n");
			जाओ मुक्त_bh;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 16; ++i) अणु
		अगर (i * 4 == PCI_COMMAND)
			जारी;

		अगर (pci_ग_लिखो_config_dword(mdev->pdev, i * 4, hca_header[i])) अणु
			err = -ENODEV;
			mthca_err(mdev, "Couldn't restore HCA reg %x, "
				  "aborting.\n", i);
			जाओ मुक्त_bh;
		पूर्ण
	पूर्ण

	अगर (pci_ग_लिखो_config_dword(mdev->pdev, PCI_COMMAND,
				   hca_header[PCI_COMMAND / 4])) अणु
		err = -ENODEV;
		mthca_err(mdev, "Couldn't restore HCA COMMAND, "
			  "aborting.\n");
	पूर्ण
मुक्त_bh:
	kमुक्त(bridge_header);
मुक्त_hca:
	kमुक्त(hca_header);
put_dev:
	pci_dev_put(bridge);
	वापस err;
पूर्ण
