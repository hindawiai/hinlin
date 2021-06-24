<शैली गुरु>
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * Copyright(c) 2012 Intel Corporation. All rights reserved.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 * The full GNU General Public License is included in this distribution
 * in the file called LICENSE.GPL.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary क्रमm must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the करोcumentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to enकरोrse or promote products derived
 *     from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  Supports the SMBus Message Transport (SMT) in the Intel Atom Processor
 *  S12xx Product Family.
 *
 *  Features supported by this driver:
 *  Hardware PEC                     yes
 *  Block buffer                     yes
 *  Block process call transaction   yes
 *  Slave mode                       no
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/completion.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/i2c.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/io-64-nonatomic-lo-hi.h>

/* PCI Address Constants */
#घोषणा SMBBAR		0

/* PCI DIDs क्रम the Intel SMBus Message Transport (SMT) Devices */
#घोषणा PCI_DEVICE_ID_INTEL_S1200_SMT0	0x0c59
#घोषणा PCI_DEVICE_ID_INTEL_S1200_SMT1	0x0c5a
#घोषणा PCI_DEVICE_ID_INTEL_CDF_SMT	0x18ac
#घोषणा PCI_DEVICE_ID_INTEL_DNV_SMT	0x19ac
#घोषणा PCI_DEVICE_ID_INTEL_EBG_SMT	0x1bff
#घोषणा PCI_DEVICE_ID_INTEL_AVOTON_SMT	0x1f15

#घोषणा ISMT_DESC_ENTRIES	2	/* number of descriptor entries */
#घोषणा ISMT_MAX_RETRIES	3	/* number of SMBus retries to attempt */

/* Hardware Descriptor Constants - Control Field */
#घोषणा ISMT_DESC_CWRL	0x01	/* Command/Write Length */
#घोषणा ISMT_DESC_BLK	0X04	/* Perक्रमm Block Transaction */
#घोषणा ISMT_DESC_FAIR	0x08	/* Set fairness flag upon successful arbit. */
#घोषणा ISMT_DESC_PEC	0x10	/* Packet Error Code */
#घोषणा ISMT_DESC_I2C	0x20	/* I2C Enable */
#घोषणा ISMT_DESC_INT	0x40	/* Interrupt */
#घोषणा ISMT_DESC_SOE	0x80	/* Stop On Error */

/* Hardware Descriptor Constants - Status Field */
#घोषणा ISMT_DESC_SCS	0x01	/* Success */
#घोषणा ISMT_DESC_DLTO	0x04	/* Data Low Time Out */
#घोषणा ISMT_DESC_NAK	0x08	/* NAK Received */
#घोषणा ISMT_DESC_CRC	0x10	/* CRC Error */
#घोषणा ISMT_DESC_CLTO	0x20	/* Clock Low Time Out */
#घोषणा ISMT_DESC_COL	0x40	/* Collisions */
#घोषणा ISMT_DESC_LPR	0x80	/* Large Packet Received */

/* Macros */
#घोषणा ISMT_DESC_ADDR_RW(addr, rw) (((addr) << 1) | (rw))

/* iSMT General Register address offsets (SMBBAR + <addr>) */
#घोषणा ISMT_GR_GCTRL		0x000	/* General Control */
#घोषणा ISMT_GR_SMTICL		0x008	/* SMT Interrupt Cause Location */
#घोषणा ISMT_GR_ERRINTMSK	0x010	/* Error Interrupt Mask */
#घोषणा ISMT_GR_ERRAERMSK	0x014	/* Error AER Mask */
#घोषणा ISMT_GR_ERRSTS		0x018	/* Error Status */
#घोषणा ISMT_GR_ERRINFO		0x01c	/* Error Inक्रमmation */

/* iSMT Master Registers */
#घोषणा ISMT_MSTR_MDBA		0x100	/* Master Descriptor Base Address */
#घोषणा ISMT_MSTR_MCTRL		0x108	/* Master Control */
#घोषणा ISMT_MSTR_MSTS		0x10c	/* Master Status */
#घोषणा ISMT_MSTR_MDS		0x110	/* Master Descriptor Size */
#घोषणा ISMT_MSTR_RPOLICY	0x114	/* Retry Policy */

/* iSMT Miscellaneous Registers */
#घोषणा ISMT_SPGT	0x300	/* SMBus PHY Global Timing */

/* General Control Register (GCTRL) bit definitions */
#घोषणा ISMT_GCTRL_TRST	0x04	/* Target Reset */
#घोषणा ISMT_GCTRL_KILL	0x08	/* Kill */
#घोषणा ISMT_GCTRL_SRST	0x40	/* Soft Reset */

/* Master Control Register (MCTRL) bit definitions */
#घोषणा ISMT_MCTRL_SS	0x01		/* Start/Stop */
#घोषणा ISMT_MCTRL_MEIE	0x10		/* Master Error Interrupt Enable */
#घोषणा ISMT_MCTRL_FMHP	0x00ff0000	/* Firmware Master Head Ptr (FMHP) */

/* Master Status Register (MSTS) bit definitions */
#घोषणा ISMT_MSTS_HMTP	0xff0000	/* HW Master Tail Poपूर्णांकer (HMTP) */
#घोषणा ISMT_MSTS_MIS	0x20		/* Master Interrupt Status (MIS) */
#घोषणा ISMT_MSTS_MEIS	0x10		/* Master Error Int Status (MEIS) */
#घोषणा ISMT_MSTS_IP	0x01		/* In Progress */

/* Master Descriptor Size (MDS) bit definitions */
#घोषणा ISMT_MDS_MASK	0xff	/* Master Descriptor Size mask (MDS) */

/* SMBus PHY Global Timing Register (SPGT) bit definitions */
#घोषणा ISMT_SPGT_SPD_MASK	0xc0000000	/* SMBus Speed mask */
#घोषणा ISMT_SPGT_SPD_80K	0x00		/* 80 kHz */
#घोषणा ISMT_SPGT_SPD_100K	(0x1 << 30)	/* 100 kHz */
#घोषणा ISMT_SPGT_SPD_400K	(0x2 << 30)	/* 400 kHz */
#घोषणा ISMT_SPGT_SPD_1M	(0x3 << 30)	/* 1 MHz */


/* MSI Control Register (MSICTL) bit definitions */
#घोषणा ISMT_MSICTL_MSIE	0x01	/* MSI Enable */

/* iSMT Hardware Descriptor */
काष्ठा ismt_desc अणु
	u8 tgtaddr_rw;	/* target address & r/w bit */
	u8 wr_len_cmd;	/* ग_लिखो length in bytes or a command */
	u8 rd_len;	/* पढ़ो length */
	u8 control;	/* control bits */
	u8 status;	/* status bits */
	u8 retry;	/* collision retry and retry count */
	u8 rxbytes;	/* received bytes */
	u8 txbytes;	/* transmitted bytes */
	u32 dptr_low;	/* lower 32 bit of the data poपूर्णांकer */
	u32 dptr_high;	/* upper 32 bit of the data poपूर्णांकer */
पूर्ण __packed;

काष्ठा ismt_priv अणु
	काष्ठा i2c_adapter adapter;
	व्योम __iomem *smba;			/* PCI BAR */
	काष्ठा pci_dev *pci_dev;
	काष्ठा ismt_desc *hw;			/* descriptor virt base addr */
	dma_addr_t io_rng_dma;			/* descriptor HW base addr */
	u8 head;				/* ring buffer head poपूर्णांकer */
	काष्ठा completion cmp;			/* पूर्णांकerrupt completion */
	u8 buffer[I2C_SMBUS_BLOCK_MAX + 16];	/* temp R/W data buffer */
पूर्ण;

अटल स्थिर काष्ठा pci_device_id ismt_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_S1200_SMT0) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_S1200_SMT1) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CDF_SMT) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_DNV_SMT) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_EBG_SMT) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_AVOTON_SMT) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, ismt_ids);

/* Bus speed control bits क्रम slow debuggers - refer to the करोcs क्रम usage */
अटल अचिन्हित पूर्णांक bus_speed;
module_param(bus_speed, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(bus_speed, "Bus Speed in kHz (0 = BIOS default)");

/**
 * __ismt_desc_dump() - dump the contents of a specअगरic descriptor
 * @dev: the iSMT device
 * @desc: the iSMT hardware descriptor
 */
अटल व्योम __ismt_desc_dump(काष्ठा device *dev, स्थिर काष्ठा ismt_desc *desc)
अणु

	dev_dbg(dev, "Descriptor struct:  %p\n", desc);
	dev_dbg(dev, "\ttgtaddr_rw=0x%02X\n", desc->tgtaddr_rw);
	dev_dbg(dev, "\twr_len_cmd=0x%02X\n", desc->wr_len_cmd);
	dev_dbg(dev, "\trd_len=    0x%02X\n", desc->rd_len);
	dev_dbg(dev, "\tcontrol=   0x%02X\n", desc->control);
	dev_dbg(dev, "\tstatus=    0x%02X\n", desc->status);
	dev_dbg(dev, "\tretry=     0x%02X\n", desc->retry);
	dev_dbg(dev, "\trxbytes=   0x%02X\n", desc->rxbytes);
	dev_dbg(dev, "\ttxbytes=   0x%02X\n", desc->txbytes);
	dev_dbg(dev, "\tdptr_low=  0x%08X\n", desc->dptr_low);
	dev_dbg(dev, "\tdptr_high= 0x%08X\n", desc->dptr_high);
पूर्ण
/**
 * ismt_desc_dump() - dump the contents of a descriptor क्रम debug purposes
 * @priv: iSMT निजी data
 */
अटल व्योम ismt_desc_dump(काष्ठा ismt_priv *priv)
अणु
	काष्ठा device *dev = &priv->pci_dev->dev;
	काष्ठा ismt_desc *desc = &priv->hw[priv->head];

	dev_dbg(dev, "Dump of the descriptor struct:  0x%X\n", priv->head);
	__ismt_desc_dump(dev, desc);
पूर्ण

/**
 * ismt_gen_reg_dump() - dump the iSMT General Registers
 * @priv: iSMT निजी data
 */
अटल व्योम ismt_gen_reg_dump(काष्ठा ismt_priv *priv)
अणु
	काष्ठा device *dev = &priv->pci_dev->dev;

	dev_dbg(dev, "Dump of the iSMT General Registers\n");
	dev_dbg(dev, "  GCTRL.... : (0x%p)=0x%X\n",
		priv->smba + ISMT_GR_GCTRL,
		पढ़ोl(priv->smba + ISMT_GR_GCTRL));
	dev_dbg(dev, "  SMTICL... : (0x%p)=0x%016llX\n",
		priv->smba + ISMT_GR_SMTICL,
		(दीर्घ दीर्घ अचिन्हित पूर्णांक)पढ़ोq(priv->smba + ISMT_GR_SMTICL));
	dev_dbg(dev, "  ERRINTMSK : (0x%p)=0x%X\n",
		priv->smba + ISMT_GR_ERRINTMSK,
		पढ़ोl(priv->smba + ISMT_GR_ERRINTMSK));
	dev_dbg(dev, "  ERRAERMSK : (0x%p)=0x%X\n",
		priv->smba + ISMT_GR_ERRAERMSK,
		पढ़ोl(priv->smba + ISMT_GR_ERRAERMSK));
	dev_dbg(dev, "  ERRSTS... : (0x%p)=0x%X\n",
		priv->smba + ISMT_GR_ERRSTS,
		पढ़ोl(priv->smba + ISMT_GR_ERRSTS));
	dev_dbg(dev, "  ERRINFO.. : (0x%p)=0x%X\n",
		priv->smba + ISMT_GR_ERRINFO,
		पढ़ोl(priv->smba + ISMT_GR_ERRINFO));
पूर्ण

/**
 * ismt_mstr_reg_dump() - dump the iSMT Master Registers
 * @priv: iSMT निजी data
 */
अटल व्योम ismt_mstr_reg_dump(काष्ठा ismt_priv *priv)
अणु
	काष्ठा device *dev = &priv->pci_dev->dev;

	dev_dbg(dev, "Dump of the iSMT Master Registers\n");
	dev_dbg(dev, "  MDBA..... : (0x%p)=0x%016llX\n",
		priv->smba + ISMT_MSTR_MDBA,
		(दीर्घ दीर्घ अचिन्हित पूर्णांक)पढ़ोq(priv->smba + ISMT_MSTR_MDBA));
	dev_dbg(dev, "  MCTRL.... : (0x%p)=0x%X\n",
		priv->smba + ISMT_MSTR_MCTRL,
		पढ़ोl(priv->smba + ISMT_MSTR_MCTRL));
	dev_dbg(dev, "  MSTS..... : (0x%p)=0x%X\n",
		priv->smba + ISMT_MSTR_MSTS,
		पढ़ोl(priv->smba + ISMT_MSTR_MSTS));
	dev_dbg(dev, "  MDS...... : (0x%p)=0x%X\n",
		priv->smba + ISMT_MSTR_MDS,
		पढ़ोl(priv->smba + ISMT_MSTR_MDS));
	dev_dbg(dev, "  RPOLICY.. : (0x%p)=0x%X\n",
		priv->smba + ISMT_MSTR_RPOLICY,
		पढ़ोl(priv->smba + ISMT_MSTR_RPOLICY));
	dev_dbg(dev, "  SPGT..... : (0x%p)=0x%X\n",
		priv->smba + ISMT_SPGT,
		पढ़ोl(priv->smba + ISMT_SPGT));
पूर्ण

/**
 * ismt_submit_desc() - add a descriptor to the ring
 * @priv: iSMT निजी data
 */
अटल व्योम ismt_submit_desc(काष्ठा ismt_priv *priv)
अणु
	uपूर्णांक fmhp;
	uपूर्णांक val;

	ismt_desc_dump(priv);
	ismt_gen_reg_dump(priv);
	ismt_mstr_reg_dump(priv);

	/* Set the FMHP (Firmware Master Head Poपूर्णांकer)*/
	fmhp = ((priv->head + 1) % ISMT_DESC_ENTRIES) << 16;
	val = पढ़ोl(priv->smba + ISMT_MSTR_MCTRL);
	ग_लिखोl((val & ~ISMT_MCTRL_FMHP) | fmhp,
	       priv->smba + ISMT_MSTR_MCTRL);

	/* Set the start bit */
	val = पढ़ोl(priv->smba + ISMT_MSTR_MCTRL);
	ग_लिखोl(val | ISMT_MCTRL_SS,
	       priv->smba + ISMT_MSTR_MCTRL);
पूर्ण

/**
 * ismt_process_desc() - handle the completion of the descriptor
 * @desc: the iSMT hardware descriptor
 * @data: data buffer from the upper layer
 * @priv: ismt_priv काष्ठा holding our dma buffer
 * @size: SMBus transaction type
 * @पढ़ो_ग_लिखो: flag to indicate अगर this is a पढ़ो or ग_लिखो
 */
अटल पूर्णांक ismt_process_desc(स्थिर काष्ठा ismt_desc *desc,
			     जोड़ i2c_smbus_data *data,
			     काष्ठा ismt_priv *priv, पूर्णांक size,
			     अक्षर पढ़ो_ग_लिखो)
अणु
	u8 *dma_buffer = PTR_ALIGN(&priv->buffer[0], 16);

	dev_dbg(&priv->pci_dev->dev, "Processing completed descriptor\n");
	__ismt_desc_dump(&priv->pci_dev->dev, desc);
	ismt_gen_reg_dump(priv);
	ismt_mstr_reg_dump(priv);

	अगर (desc->status & ISMT_DESC_SCS) अणु
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE &&
		    size != I2C_SMBUS_PROC_CALL &&
		    size != I2C_SMBUS_BLOCK_PROC_CALL)
			वापस 0;

		चयन (size) अणु
		हाल I2C_SMBUS_BYTE:
		हाल I2C_SMBUS_BYTE_DATA:
			data->byte = dma_buffer[0];
			अवरोध;
		हाल I2C_SMBUS_WORD_DATA:
		हाल I2C_SMBUS_PROC_CALL:
			data->word = dma_buffer[0] | (dma_buffer[1] << 8);
			अवरोध;
		हाल I2C_SMBUS_BLOCK_DATA:
		हाल I2C_SMBUS_BLOCK_PROC_CALL:
			अगर (desc->rxbytes != dma_buffer[0] + 1)
				वापस -EMSGSIZE;

			स_नकल(data->block, dma_buffer, desc->rxbytes);
			अवरोध;
		हाल I2C_SMBUS_I2C_BLOCK_DATA:
			स_नकल(&data->block[1], dma_buffer, desc->rxbytes);
			data->block[0] = desc->rxbytes;
			अवरोध;
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (likely(desc->status & ISMT_DESC_NAK))
		वापस -ENXIO;

	अगर (desc->status & ISMT_DESC_CRC)
		वापस -EBADMSG;

	अगर (desc->status & ISMT_DESC_COL)
		वापस -EAGAIN;

	अगर (desc->status & ISMT_DESC_LPR)
		वापस -EPROTO;

	अगर (desc->status & (ISMT_DESC_DLTO | ISMT_DESC_CLTO))
		वापस -ETIMEDOUT;

	वापस -EIO;
पूर्ण

/**
 * ismt_access() - process an SMBus command
 * @adap: the i2c host adapter
 * @addr: address of the i2c/SMBus target
 * @flags: command options
 * @पढ़ो_ग_लिखो: पढ़ो from or ग_लिखो to device
 * @command: the i2c/SMBus command to issue
 * @size: SMBus transaction type
 * @data: पढ़ो/ग_लिखो data buffer
 */
अटल पूर्णांक ismt_access(काष्ठा i2c_adapter *adap, u16 addr,
		       अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो, u8 command,
		       पूर्णांक size, जोड़ i2c_smbus_data *data)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ समय_left;
	dma_addr_t dma_addr = 0; /* address of the data buffer */
	u8 dma_size = 0;
	क्रमागत dma_data_direction dma_direction = 0;
	काष्ठा ismt_desc *desc;
	काष्ठा ismt_priv *priv = i2c_get_adapdata(adap);
	काष्ठा device *dev = &priv->pci_dev->dev;
	u8 *dma_buffer = PTR_ALIGN(&priv->buffer[0], 16);

	desc = &priv->hw[priv->head];

	/* Initialize the DMA buffer */
	स_रखो(priv->buffer, 0, माप(priv->buffer));

	/* Initialize the descriptor */
	स_रखो(desc, 0, माप(काष्ठा ismt_desc));
	desc->tgtaddr_rw = ISMT_DESC_ADDR_RW(addr, पढ़ो_ग_लिखो);

	/* Initialize common control bits */
	अगर (likely(pci_dev_msi_enabled(priv->pci_dev)))
		desc->control = ISMT_DESC_INT | ISMT_DESC_FAIR;
	अन्यथा
		desc->control = ISMT_DESC_FAIR;

	अगर ((flags & I2C_CLIENT_PEC) && (size != I2C_SMBUS_QUICK)
	    && (size != I2C_SMBUS_I2C_BLOCK_DATA))
		desc->control |= ISMT_DESC_PEC;

	चयन (size) अणु
	हाल I2C_SMBUS_QUICK:
		dev_dbg(dev, "I2C_SMBUS_QUICK\n");
		अवरोध;

	हाल I2C_SMBUS_BYTE:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			/*
			 * Send Byte
			 * The command field contains the ग_लिखो data
			 */
			dev_dbg(dev, "I2C_SMBUS_BYTE:  WRITE\n");
			desc->control |= ISMT_DESC_CWRL;
			desc->wr_len_cmd = command;
		पूर्ण अन्यथा अणु
			/* Receive Byte */
			dev_dbg(dev, "I2C_SMBUS_BYTE:  READ\n");
			dma_size = 1;
			dma_direction = DMA_FROM_DEVICE;
			desc->rd_len = 1;
		पूर्ण
		अवरोध;

	हाल I2C_SMBUS_BYTE_DATA:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			/*
			 * Write Byte
			 * Command plus 1 data byte
			 */
			dev_dbg(dev, "I2C_SMBUS_BYTE_DATA:  WRITE\n");
			desc->wr_len_cmd = 2;
			dma_size = 2;
			dma_direction = DMA_TO_DEVICE;
			dma_buffer[0] = command;
			dma_buffer[1] = data->byte;
		पूर्ण अन्यथा अणु
			/* Read Byte */
			dev_dbg(dev, "I2C_SMBUS_BYTE_DATA:  READ\n");
			desc->control |= ISMT_DESC_CWRL;
			desc->wr_len_cmd = command;
			desc->rd_len = 1;
			dma_size = 1;
			dma_direction = DMA_FROM_DEVICE;
		पूर्ण
		अवरोध;

	हाल I2C_SMBUS_WORD_DATA:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			/* Write Word */
			dev_dbg(dev, "I2C_SMBUS_WORD_DATA:  WRITE\n");
			desc->wr_len_cmd = 3;
			dma_size = 3;
			dma_direction = DMA_TO_DEVICE;
			dma_buffer[0] = command;
			dma_buffer[1] = data->word & 0xff;
			dma_buffer[2] = data->word >> 8;
		पूर्ण अन्यथा अणु
			/* Read Word */
			dev_dbg(dev, "I2C_SMBUS_WORD_DATA:  READ\n");
			desc->wr_len_cmd = command;
			desc->control |= ISMT_DESC_CWRL;
			desc->rd_len = 2;
			dma_size = 2;
			dma_direction = DMA_FROM_DEVICE;
		पूर्ण
		अवरोध;

	हाल I2C_SMBUS_PROC_CALL:
		dev_dbg(dev, "I2C_SMBUS_PROC_CALL\n");
		desc->wr_len_cmd = 3;
		desc->rd_len = 2;
		dma_size = 3;
		dma_direction = DMA_BIसूचीECTIONAL;
		dma_buffer[0] = command;
		dma_buffer[1] = data->word & 0xff;
		dma_buffer[2] = data->word >> 8;
		अवरोध;

	हाल I2C_SMBUS_BLOCK_DATA:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			/* Block Write */
			dev_dbg(dev, "I2C_SMBUS_BLOCK_DATA:  WRITE\n");
			dma_size = data->block[0] + 1;
			dma_direction = DMA_TO_DEVICE;
			desc->wr_len_cmd = dma_size;
			desc->control |= ISMT_DESC_BLK;
			dma_buffer[0] = command;
			स_नकल(&dma_buffer[1], &data->block[1], dma_size - 1);
		पूर्ण अन्यथा अणु
			/* Block Read */
			dev_dbg(dev, "I2C_SMBUS_BLOCK_DATA:  READ\n");
			dma_size = I2C_SMBUS_BLOCK_MAX;
			dma_direction = DMA_FROM_DEVICE;
			desc->rd_len = dma_size;
			desc->wr_len_cmd = command;
			desc->control |= (ISMT_DESC_BLK | ISMT_DESC_CWRL);
		पूर्ण
		अवरोध;

	हाल I2C_SMBUS_BLOCK_PROC_CALL:
		dev_dbg(dev, "I2C_SMBUS_BLOCK_PROC_CALL\n");
		dma_size = I2C_SMBUS_BLOCK_MAX;
		desc->tgtaddr_rw = ISMT_DESC_ADDR_RW(addr, 1);
		desc->wr_len_cmd = data->block[0] + 1;
		desc->rd_len = dma_size;
		desc->control |= ISMT_DESC_BLK;
		dma_direction = DMA_BIसूचीECTIONAL;
		dma_buffer[0] = command;
		स_नकल(&dma_buffer[1], &data->block[1], data->block[0]);
		अवरोध;

	हाल I2C_SMBUS_I2C_BLOCK_DATA:
		/* Make sure the length is valid */
		अगर (data->block[0] < 1)
			data->block[0] = 1;

		अगर (data->block[0] > I2C_SMBUS_BLOCK_MAX)
			data->block[0] = I2C_SMBUS_BLOCK_MAX;

		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			/* i2c Block Write */
			dev_dbg(dev, "I2C_SMBUS_I2C_BLOCK_DATA:  WRITE\n");
			dma_size = data->block[0] + 1;
			dma_direction = DMA_TO_DEVICE;
			desc->wr_len_cmd = dma_size;
			desc->control |= ISMT_DESC_I2C;
			dma_buffer[0] = command;
			स_नकल(&dma_buffer[1], &data->block[1], dma_size - 1);
		पूर्ण अन्यथा अणु
			/* i2c Block Read */
			dev_dbg(dev, "I2C_SMBUS_I2C_BLOCK_DATA:  READ\n");
			dma_size = data->block[0];
			dma_direction = DMA_FROM_DEVICE;
			desc->rd_len = dma_size;
			desc->wr_len_cmd = command;
			desc->control |= (ISMT_DESC_I2C | ISMT_DESC_CWRL);
			/*
			 * Per the "Table 15-15. I2C Commands",
			 * in the External Design Specअगरication (EDS),
			 * (Document Number: 508084, Revision: 2.0),
			 * the _rw bit must be 0
			 */
			desc->tgtaddr_rw = ISMT_DESC_ADDR_RW(addr, 0);
		पूर्ण
		अवरोध;

	शेष:
		dev_err(dev, "Unsupported transaction %d\n",
			size);
		वापस -EOPNOTSUPP;
	पूर्ण

	/* map the data buffer */
	अगर (dma_size != 0) अणु
		dev_dbg(dev, " dev=%p\n", dev);
		dev_dbg(dev, " data=%p\n", data);
		dev_dbg(dev, " dma_buffer=%p\n", dma_buffer);
		dev_dbg(dev, " dma_size=%d\n", dma_size);
		dev_dbg(dev, " dma_direction=%d\n", dma_direction);

		dma_addr = dma_map_single(dev,
				      dma_buffer,
				      dma_size,
				      dma_direction);

		अगर (dma_mapping_error(dev, dma_addr)) अणु
			dev_err(dev, "Error in mapping dma buffer %p\n",
				dma_buffer);
			वापस -EIO;
		पूर्ण

		dev_dbg(dev, " dma_addr = %pad\n", &dma_addr);

		desc->dptr_low = lower_32_bits(dma_addr);
		desc->dptr_high = upper_32_bits(dma_addr);
	पूर्ण

	reinit_completion(&priv->cmp);

	/* Add the descriptor */
	ismt_submit_desc(priv);

	/* Now we रुको क्रम पूर्णांकerrupt completion, 1s */
	समय_left = रुको_क्रम_completion_समयout(&priv->cmp, HZ*1);

	/* unmap the data buffer */
	अगर (dma_size != 0)
		dma_unmap_single(dev, dma_addr, dma_size, dma_direction);

	अगर (unlikely(!समय_left)) अणु
		dev_err(dev, "completion wait timed out\n");
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	/* करो any post processing of the descriptor here */
	ret = ismt_process_desc(desc, data, priv, size, पढ़ो_ग_लिखो);

out:
	/* Update the ring poपूर्णांकer */
	priv->head++;
	priv->head %= ISMT_DESC_ENTRIES;

	वापस ret;
पूर्ण

/**
 * ismt_func() - report which i2c commands are supported by this adapter
 * @adap: the i2c host adapter
 */
अटल u32 ismt_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_SMBUS_QUICK		|
	       I2C_FUNC_SMBUS_BYTE		|
	       I2C_FUNC_SMBUS_BYTE_DATA		|
	       I2C_FUNC_SMBUS_WORD_DATA		|
	       I2C_FUNC_SMBUS_PROC_CALL		|
	       I2C_FUNC_SMBUS_BLOCK_PROC_CALL	|
	       I2C_FUNC_SMBUS_BLOCK_DATA	|
	       I2C_FUNC_SMBUS_I2C_BLOCK		|
	       I2C_FUNC_SMBUS_PEC;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm smbus_algorithm = अणु
	.smbus_xfer	= ismt_access,
	.functionality	= ismt_func,
पूर्ण;

/**
 * ismt_handle_isr() - पूर्णांकerrupt handler bottom half
 * @priv: iSMT निजी data
 */
अटल irqवापस_t ismt_handle_isr(काष्ठा ismt_priv *priv)
अणु
	complete(&priv->cmp);

	वापस IRQ_HANDLED;
पूर्ण


/**
 * ismt_करो_पूर्णांकerrupt() - IRQ पूर्णांकerrupt handler
 * @vec: पूर्णांकerrupt vector
 * @data: iSMT निजी data
 */
अटल irqवापस_t ismt_करो_पूर्णांकerrupt(पूर्णांक vec, व्योम *data)
अणु
	u32 val;
	काष्ठा ismt_priv *priv = data;

	/*
	 * check to see it's our पूर्णांकerrupt, वापस IRQ_NONE अगर not ours
	 * since we are sharing पूर्णांकerrupt
	 */
	val = पढ़ोl(priv->smba + ISMT_MSTR_MSTS);

	अगर (!(val & (ISMT_MSTS_MIS | ISMT_MSTS_MEIS)))
		वापस IRQ_NONE;
	अन्यथा
		ग_लिखोl(val | ISMT_MSTS_MIS | ISMT_MSTS_MEIS,
		       priv->smba + ISMT_MSTR_MSTS);

	वापस ismt_handle_isr(priv);
पूर्ण

/**
 * ismt_करो_msi_पूर्णांकerrupt() - MSI पूर्णांकerrupt handler
 * @vec: पूर्णांकerrupt vector
 * @data: iSMT निजी data
 */
अटल irqवापस_t ismt_करो_msi_पूर्णांकerrupt(पूर्णांक vec, व्योम *data)
अणु
	वापस ismt_handle_isr(data);
पूर्ण

/**
 * ismt_hw_init() - initialize the iSMT hardware
 * @priv: iSMT निजी data
 */
अटल व्योम ismt_hw_init(काष्ठा ismt_priv *priv)
अणु
	u32 val;
	काष्ठा device *dev = &priv->pci_dev->dev;

	/* initialize the Master Descriptor Base Address (MDBA) */
	ग_लिखोq(priv->io_rng_dma, priv->smba + ISMT_MSTR_MDBA);

	/* initialize the Master Control Register (MCTRL) */
	ग_लिखोl(ISMT_MCTRL_MEIE, priv->smba + ISMT_MSTR_MCTRL);

	/* initialize the Master Status Register (MSTS) */
	ग_लिखोl(0, priv->smba + ISMT_MSTR_MSTS);

	/* initialize the Master Descriptor Size (MDS) */
	val = पढ़ोl(priv->smba + ISMT_MSTR_MDS);
	ग_लिखोl((val & ~ISMT_MDS_MASK) | (ISMT_DESC_ENTRIES - 1),
		priv->smba + ISMT_MSTR_MDS);

	/*
	 * Set the SMBus speed (could use this क्रम slow HW debuggers)
	 */

	val = पढ़ोl(priv->smba + ISMT_SPGT);

	चयन (bus_speed) अणु
	हाल 0:
		अवरोध;

	हाल 80:
		dev_dbg(dev, "Setting SMBus clock to 80 kHz\n");
		ग_लिखोl(((val & ~ISMT_SPGT_SPD_MASK) | ISMT_SPGT_SPD_80K),
			priv->smba + ISMT_SPGT);
		अवरोध;

	हाल 100:
		dev_dbg(dev, "Setting SMBus clock to 100 kHz\n");
		ग_लिखोl(((val & ~ISMT_SPGT_SPD_MASK) | ISMT_SPGT_SPD_100K),
			priv->smba + ISMT_SPGT);
		अवरोध;

	हाल 400:
		dev_dbg(dev, "Setting SMBus clock to 400 kHz\n");
		ग_लिखोl(((val & ~ISMT_SPGT_SPD_MASK) | ISMT_SPGT_SPD_400K),
			priv->smba + ISMT_SPGT);
		अवरोध;

	हाल 1000:
		dev_dbg(dev, "Setting SMBus clock to 1000 kHz\n");
		ग_लिखोl(((val & ~ISMT_SPGT_SPD_MASK) | ISMT_SPGT_SPD_1M),
			priv->smba + ISMT_SPGT);
		अवरोध;

	शेष:
		dev_warn(dev, "Invalid SMBus clock speed, only 0, 80, 100, 400, and 1000 are valid\n");
		अवरोध;
	पूर्ण

	val = पढ़ोl(priv->smba + ISMT_SPGT);

	चयन (val & ISMT_SPGT_SPD_MASK) अणु
	हाल ISMT_SPGT_SPD_80K:
		bus_speed = 80;
		अवरोध;
	हाल ISMT_SPGT_SPD_100K:
		bus_speed = 100;
		अवरोध;
	हाल ISMT_SPGT_SPD_400K:
		bus_speed = 400;
		अवरोध;
	हाल ISMT_SPGT_SPD_1M:
		bus_speed = 1000;
		अवरोध;
	पूर्ण
	dev_dbg(dev, "SMBus clock is running at %d kHz\n", bus_speed);
पूर्ण

/**
 * ismt_dev_init() - initialize the iSMT data काष्ठाures
 * @priv: iSMT निजी data
 */
अटल पूर्णांक ismt_dev_init(काष्ठा ismt_priv *priv)
अणु
	/* allocate memory क्रम the descriptor */
	priv->hw = dmam_alloc_coherent(&priv->pci_dev->dev,
				       (ISMT_DESC_ENTRIES
					       * माप(काष्ठा ismt_desc)),
				       &priv->io_rng_dma,
				       GFP_KERNEL);
	अगर (!priv->hw)
		वापस -ENOMEM;

	priv->head = 0;
	init_completion(&priv->cmp);

	वापस 0;
पूर्ण

/**
 * ismt_पूर्णांक_init() - initialize पूर्णांकerrupts
 * @priv: iSMT निजी data
 */
अटल पूर्णांक ismt_पूर्णांक_init(काष्ठा ismt_priv *priv)
अणु
	पूर्णांक err;

	/* Try using MSI पूर्णांकerrupts */
	err = pci_enable_msi(priv->pci_dev);
	अगर (err)
		जाओ पूर्णांकx;

	err = devm_request_irq(&priv->pci_dev->dev,
			       priv->pci_dev->irq,
			       ismt_करो_msi_पूर्णांकerrupt,
			       0,
			       "ismt-msi",
			       priv);
	अगर (err) अणु
		pci_disable_msi(priv->pci_dev);
		जाओ पूर्णांकx;
	पूर्ण

	वापस 0;

	/* Try using legacy पूर्णांकerrupts */
पूर्णांकx:
	dev_warn(&priv->pci_dev->dev,
		 "Unable to use MSI interrupts, falling back to legacy\n");

	err = devm_request_irq(&priv->pci_dev->dev,
			       priv->pci_dev->irq,
			       ismt_करो_पूर्णांकerrupt,
			       IRQF_SHARED,
			       "ismt-intx",
			       priv);
	अगर (err) अणु
		dev_err(&priv->pci_dev->dev, "no usable interrupts\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा pci_driver ismt_driver;

/**
 * ismt_probe() - probe क्रम iSMT devices
 * @pdev: PCI-Express device
 * @id: PCI-Express device ID
 */
अटल पूर्णांक
ismt_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक err;
	काष्ठा ismt_priv *priv;
	अचिन्हित दीर्घ start, len;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	pci_set_drvdata(pdev, priv);

	i2c_set_adapdata(&priv->adapter, priv);
	priv->adapter.owner = THIS_MODULE;
	priv->adapter.class = I2C_CLASS_HWMON;
	priv->adapter.algo = &smbus_algorithm;
	priv->adapter.dev.parent = &pdev->dev;
	ACPI_COMPANION_SET(&priv->adapter.dev, ACPI_COMPANION(&pdev->dev));
	priv->adapter.retries = ISMT_MAX_RETRIES;

	priv->pci_dev = pdev;

	err = pcim_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to enable SMBus PCI device (%d)\n",
			err);
		वापस err;
	पूर्ण

	/* enable bus mastering */
	pci_set_master(pdev);

	/* Determine the address of the SMBus area */
	start = pci_resource_start(pdev, SMBBAR);
	len = pci_resource_len(pdev, SMBBAR);
	अगर (!start || !len) अणु
		dev_err(&pdev->dev,
			"SMBus base address uninitialized, upgrade BIOS\n");
		वापस -ENODEV;
	पूर्ण

	snम_लिखो(priv->adapter.name, माप(priv->adapter.name),
		 "SMBus iSMT adapter at %lx", start);

	dev_dbg(&priv->pci_dev->dev, " start=0x%lX\n", start);
	dev_dbg(&priv->pci_dev->dev, " len=0x%lX\n", len);

	err = acpi_check_resource_conflict(&pdev->resource[SMBBAR]);
	अगर (err) अणु
		dev_err(&pdev->dev, "ACPI resource conflict!\n");
		वापस err;
	पूर्ण

	err = pci_request_region(pdev, SMBBAR, ismt_driver.name);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"Failed to request SMBus region 0x%lx-0x%lx\n",
			start, start + len);
		वापस err;
	पूर्ण

	priv->smba = pcim_iomap(pdev, SMBBAR, len);
	अगर (!priv->smba) अणु
		dev_err(&pdev->dev, "Unable to ioremap SMBus BAR\n");
		वापस -ENODEV;
	पूर्ण

	अगर ((pci_set_dma_mask(pdev, DMA_BIT_MASK(64)) != 0) ||
	    (pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64)) != 0)) अणु
		अगर ((pci_set_dma_mask(pdev, DMA_BIT_MASK(32)) != 0) ||
		    (pci_set_consistent_dma_mask(pdev,
						 DMA_BIT_MASK(32)) != 0)) अणु
			dev_err(&pdev->dev, "pci_set_dma_mask fail %p\n",
				pdev);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	err = ismt_dev_init(priv);
	अगर (err)
		वापस err;

	ismt_hw_init(priv);

	err = ismt_पूर्णांक_init(priv);
	अगर (err)
		वापस err;

	err = i2c_add_adapter(&priv->adapter);
	अगर (err)
		वापस -ENODEV;
	वापस 0;
पूर्ण

/**
 * ismt_हटाओ() - release driver resources
 * @pdev: PCI-Express device
 */
अटल व्योम ismt_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ismt_priv *priv = pci_get_drvdata(pdev);

	i2c_del_adapter(&priv->adapter);
पूर्ण

अटल काष्ठा pci_driver ismt_driver = अणु
	.name = "ismt_smbus",
	.id_table = ismt_ids,
	.probe = ismt_probe,
	.हटाओ = ismt_हटाओ,
पूर्ण;

module_pci_driver(ismt_driver);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Bill E. Brown <bill.e.brown@intel.com>");
MODULE_DESCRIPTION("Intel SMBus Message Transport (iSMT) driver");
