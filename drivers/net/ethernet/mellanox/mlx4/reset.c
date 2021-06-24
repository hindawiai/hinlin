<शैली गुरु>
/*
 * Copyright (c) 2006, 2007 Cisco Systems, Inc.  All rights reserved.
 * Copyright (c) 2007, 2008 Mellanox Technologies. All rights reserved.
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
#समावेश <linux/jअगरfies.h>

#समावेश "mlx4.h"

पूर्णांक mlx4_reset(काष्ठा mlx4_dev *dev)
अणु
	व्योम __iomem *reset;
	u32 *hca_header = शून्य;
	पूर्णांक pcie_cap;
	u16 devctl;
	u16 linkctl;
	u16 venकरोr;
	अचिन्हित दीर्घ end;
	u32 sem;
	पूर्णांक i;
	पूर्णांक err = 0;

#घोषणा MLX4_RESET_BASE		0xf0000
#घोषणा MLX4_RESET_SIZE		  0x400
#घोषणा MLX4_SEM_OFFSET		  0x3fc
#घोषणा MLX4_RESET_OFFSET	   0x10
#घोषणा MLX4_RESET_VALUE	swab32(1)

#घोषणा MLX4_SEM_TIMEOUT_JIFFIES	(10 * HZ)
#घोषणा MLX4_RESET_TIMEOUT_JIFFIES	(2 * HZ)

	/*
	 * Reset the chip.  This is somewhat ugly because we have to
	 * save off the PCI header beक्रमe reset and then restore it
	 * after the chip reboots.  We skip config space offsets 22
	 * and 23 since those have a special meaning.
	 */

	/* Do we need to save off the full 4K PCI Express header?? */
	hca_header = kदो_स्मृति(256, GFP_KERNEL);
	अगर (!hca_header) अणु
		err = -ENOMEM;
		mlx4_err(dev, "Couldn't allocate memory to save HCA PCI header, aborting\n");
		जाओ out;
	पूर्ण

	pcie_cap = pci_pcie_cap(dev->persist->pdev);

	क्रम (i = 0; i < 64; ++i) अणु
		अगर (i == 22 || i == 23)
			जारी;
		अगर (pci_पढ़ो_config_dword(dev->persist->pdev, i * 4,
					  hca_header + i)) अणु
			err = -ENODEV;
			mlx4_err(dev, "Couldn't save HCA PCI header, aborting\n");
			जाओ out;
		पूर्ण
	पूर्ण

	reset = ioremap(pci_resource_start(dev->persist->pdev, 0) +
			MLX4_RESET_BASE,
			MLX4_RESET_SIZE);
	अगर (!reset) अणु
		err = -ENOMEM;
		mlx4_err(dev, "Couldn't map HCA reset register, aborting\n");
		जाओ out;
	पूर्ण

	/* grab HW semaphore to lock out flash updates */
	end = jअगरfies + MLX4_SEM_TIMEOUT_JIFFIES;
	करो अणु
		sem = पढ़ोl(reset + MLX4_SEM_OFFSET);
		अगर (!sem)
			अवरोध;

		msleep(1);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, end));

	अगर (sem) अणु
		mlx4_err(dev, "Failed to obtain HW semaphore, aborting\n");
		err = -EAGAIN;
		iounmap(reset);
		जाओ out;
	पूर्ण

	/* actually hit reset */
	ग_लिखोl(MLX4_RESET_VALUE, reset + MLX4_RESET_OFFSET);
	iounmap(reset);

	/* Docs say to रुको one second beक्रमe accessing device */
	msleep(1000);

	end = jअगरfies + MLX4_RESET_TIMEOUT_JIFFIES;
	करो अणु
		अगर (!pci_पढ़ो_config_word(dev->persist->pdev, PCI_VENDOR_ID,
					  &venकरोr) && venकरोr != 0xffff)
			अवरोध;

		msleep(1);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, end));

	अगर (venकरोr == 0xffff) अणु
		err = -ENODEV;
		mlx4_err(dev, "PCI device did not come back after reset, aborting\n");
		जाओ out;
	पूर्ण

	/* Now restore the PCI headers */
	अगर (pcie_cap) अणु
		devctl = hca_header[(pcie_cap + PCI_EXP_DEVCTL) / 4];
		अगर (pcie_capability_ग_लिखो_word(dev->persist->pdev,
					       PCI_EXP_DEVCTL,
					       devctl)) अणु
			err = -ENODEV;
			mlx4_err(dev, "Couldn't restore HCA PCI Express Device Control register, aborting\n");
			जाओ out;
		पूर्ण
		linkctl = hca_header[(pcie_cap + PCI_EXP_LNKCTL) / 4];
		अगर (pcie_capability_ग_लिखो_word(dev->persist->pdev,
					       PCI_EXP_LNKCTL,
					       linkctl)) अणु
			err = -ENODEV;
			mlx4_err(dev, "Couldn't restore HCA PCI Express Link control register, aborting\n");
			जाओ out;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 16; ++i) अणु
		अगर (i * 4 == PCI_COMMAND)
			जारी;

		अगर (pci_ग_लिखो_config_dword(dev->persist->pdev, i * 4,
					   hca_header[i])) अणु
			err = -ENODEV;
			mlx4_err(dev, "Couldn't restore HCA reg %x, aborting\n",
				 i);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (pci_ग_लिखो_config_dword(dev->persist->pdev, PCI_COMMAND,
				   hca_header[PCI_COMMAND / 4])) अणु
		err = -ENODEV;
		mlx4_err(dev, "Couldn't restore HCA COMMAND, aborting\n");
		जाओ out;
	पूर्ण

out:
	kमुक्त(hca_header);

	वापस err;
पूर्ण
