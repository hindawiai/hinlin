<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 LAPIS Semiconductor Co., Ltd.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/fs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/माला.स>
#समावेश <linux/pci.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/dmi.h>
#समावेश <linux/of.h>

#घोषणा PHUB_STATUS 0x00		/* Status Register offset */
#घोषणा PHUB_CONTROL 0x04		/* Control Register offset */
#घोषणा PHUB_TIMEOUT 0x05		/* Time out value क्रम Status Register */
#घोषणा PCH_PHUB_ROM_WRITE_ENABLE 0x01	/* Enabling क्रम writing ROM */
#घोषणा PCH_PHUB_ROM_WRITE_DISABLE 0x00	/* Disabling क्रम writing ROM */
#घोषणा PCH_PHUB_MAC_START_ADDR_EG20T 0x14  /* MAC data area start address
					       offset */
#घोषणा PCH_PHUB_MAC_START_ADDR_ML7223 0x20C  /* MAC data area start address
						 offset */
#घोषणा PCH_PHUB_ROM_START_ADDR_EG20T 0x80 /* ROM data area start address offset
					      (Intel EG20T PCH)*/
#घोषणा PCH_PHUB_ROM_START_ADDR_ML7213 0x400 /* ROM data area start address
						offset(LAPIS Semicon ML7213)
					      */
#घोषणा PCH_PHUB_ROM_START_ADDR_ML7223 0x400 /* ROM data area start address
						offset(LAPIS Semicon ML7223)
					      */

/* MAX number of INT_REDUCE_CONTROL रेजिस्टरs */
#घोषणा MAX_NUM_INT_REDUCE_CONTROL_REG 128
#घोषणा PCI_DEVICE_ID_PCH1_PHUB 0x8801
#घोषणा PCH_MINOR_NOS 1
#घोषणा CLKCFG_CAN_50MHZ 0x12000000
#घोषणा CLKCFG_CANCLK_MASK 0xFF000000
#घोषणा CLKCFG_UART_MASK			0xFFFFFF

/* CM-iTC */
#घोषणा CLKCFG_UART_48MHZ			(1 << 16)
#घोषणा CLKCFG_UART_25MHZ			(2 << 16)
#घोषणा CLKCFG_BAUDDIV				(2 << 20)
#घोषणा CLKCFG_PLL2VCO				(8 << 9)
#घोषणा CLKCFG_UARTCLKSEL			(1 << 18)

/* Macros क्रम ML7213 */
#घोषणा PCI_DEVICE_ID_ROHM_ML7213_PHUB		0x801A

/* Macros क्रम ML7223 */
#घोषणा PCI_DEVICE_ID_ROHM_ML7223_mPHUB	0x8012 /* क्रम Bus-m */
#घोषणा PCI_DEVICE_ID_ROHM_ML7223_nPHUB	0x8002 /* क्रम Bus-n */

/* Macros क्रम ML7831 */
#घोषणा PCI_DEVICE_ID_ROHM_ML7831_PHUB 0x8801

/* SROM ACCESS Macro */
#घोषणा PCH_WORD_ADDR_MASK (~((1 << 2) - 1))

/* Registers address offset */
#घोषणा PCH_PHUB_ID_REG				0x0000
#घोषणा PCH_PHUB_QUEUE_PRI_VAL_REG		0x0004
#घोषणा PCH_PHUB_RC_QUEUE_MAXSIZE_REG		0x0008
#घोषणा PCH_PHUB_BRI_QUEUE_MAXSIZE_REG		0x000C
#घोषणा PCH_PHUB_COMP_RESP_TIMEOUT_REG		0x0010
#घोषणा PCH_PHUB_BUS_SLAVE_CONTROL_REG		0x0014
#घोषणा PCH_PHUB_DEADLOCK_AVOID_TYPE_REG	0x0018
#घोषणा PCH_PHUB_INTPIN_REG_WPERMIT_REG0	0x0020
#घोषणा PCH_PHUB_INTPIN_REG_WPERMIT_REG1	0x0024
#घोषणा PCH_PHUB_INTPIN_REG_WPERMIT_REG2	0x0028
#घोषणा PCH_PHUB_INTPIN_REG_WPERMIT_REG3	0x002C
#घोषणा PCH_PHUB_INT_REDUCE_CONTROL_REG_BASE	0x0040
#घोषणा CLKCFG_REG_OFFSET			0x500
#घोषणा FUNCSEL_REG_OFFSET			0x508

#घोषणा PCH_PHUB_OROM_SIZE 15360

/**
 * काष्ठा pch_phub_reg - PHUB रेजिस्टर काष्ठाure
 * @phub_id_reg:			PHUB_ID रेजिस्टर val
 * @q_pri_val_reg:			QUEUE_PRI_VAL रेजिस्टर val
 * @rc_q_maxsize_reg:			RC_QUEUE_MAXSIZE रेजिस्टर val
 * @bri_q_maxsize_reg:			BRI_QUEUE_MAXSIZE रेजिस्टर val
 * @comp_resp_समयout_reg:		COMP_RESP_TIMEOUT रेजिस्टर val
 * @bus_slave_control_reg:		BUS_SLAVE_CONTROL_REG रेजिस्टर val
 * @deadlock_aव्योम_type_reg:		DEADLOCK_AVOID_TYPE रेजिस्टर val
 * @पूर्णांकpin_reg_wpermit_reg0:		INTPIN_REG_WPERMIT रेजिस्टर 0 val
 * @पूर्णांकpin_reg_wpermit_reg1:		INTPIN_REG_WPERMIT रेजिस्टर 1 val
 * @पूर्णांकpin_reg_wpermit_reg2:		INTPIN_REG_WPERMIT रेजिस्टर 2 val
 * @पूर्णांकpin_reg_wpermit_reg3:		INTPIN_REG_WPERMIT रेजिस्टर 3 val
 * @पूर्णांक_reduce_control_reg:		INT_REDUCE_CONTROL रेजिस्टरs val
 * @clkcfg_reg:				CLK CFG रेजिस्टर val
 * @funcsel_reg:			Function select रेजिस्टर value
 * @pch_phub_base_address:		Register base address
 * @pch_phub_extrom_base_address:	बाह्यal rom base address
 * @pch_mac_start_address:		MAC address area start address
 * @pch_opt_rom_start_address:		Option ROM start address
 * @ioh_type:				Save IOH type
 * @pdev:				poपूर्णांकer to pci device काष्ठा
 */
काष्ठा pch_phub_reg अणु
	u32 phub_id_reg;
	u32 q_pri_val_reg;
	u32 rc_q_maxsize_reg;
	u32 bri_q_maxsize_reg;
	u32 comp_resp_समयout_reg;
	u32 bus_slave_control_reg;
	u32 deadlock_aव्योम_type_reg;
	u32 पूर्णांकpin_reg_wpermit_reg0;
	u32 पूर्णांकpin_reg_wpermit_reg1;
	u32 पूर्णांकpin_reg_wpermit_reg2;
	u32 पूर्णांकpin_reg_wpermit_reg3;
	u32 पूर्णांक_reduce_control_reg[MAX_NUM_INT_REDUCE_CONTROL_REG];
	u32 clkcfg_reg;
	u32 funcsel_reg;
	व्योम __iomem *pch_phub_base_address;
	व्योम __iomem *pch_phub_extrom_base_address;
	u32 pch_mac_start_address;
	u32 pch_opt_rom_start_address;
	पूर्णांक ioh_type;
	काष्ठा pci_dev *pdev;
पूर्ण;

/* SROM SPEC क्रम MAC address assignment offset */
अटल स्थिर पूर्णांक pch_phub_mac_offset[ETH_ALEN] = अणु0x3, 0x2, 0x1, 0x0, 0xb, 0xaपूर्ण;

अटल DEFINE_MUTEX(pch_phub_mutex);

/**
 * pch_phub_पढ़ो_modअगरy_ग_लिखो_reg() - Reading modअगरying and writing रेजिस्टर
 * @chip:		Poपूर्णांकer to the PHUB रेजिस्टर काष्ठाure
 * @reg_addr_offset:	Register offset address value.
 * @data:		Writing value.
 * @mask:		Mask value.
 */
अटल व्योम pch_phub_पढ़ो_modअगरy_ग_लिखो_reg(काष्ठा pch_phub_reg *chip,
					   अचिन्हित पूर्णांक reg_addr_offset,
					   अचिन्हित पूर्णांक data, अचिन्हित पूर्णांक mask)
अणु
	व्योम __iomem *reg_addr = chip->pch_phub_base_address + reg_addr_offset;
	ioग_लिखो32(((ioपढ़ो32(reg_addr) & ~mask)) | data, reg_addr);
पूर्ण

/* pch_phub_save_reg_conf - saves रेजिस्टर configuration */
अटल व्योम __maybe_unused pch_phub_save_reg_conf(काष्ठा pci_dev *pdev)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा pch_phub_reg *chip = pci_get_drvdata(pdev);

	व्योम __iomem *p = chip->pch_phub_base_address;

	chip->phub_id_reg = ioपढ़ो32(p + PCH_PHUB_ID_REG);
	chip->q_pri_val_reg = ioपढ़ो32(p + PCH_PHUB_QUEUE_PRI_VAL_REG);
	chip->rc_q_maxsize_reg = ioपढ़ो32(p + PCH_PHUB_RC_QUEUE_MAXSIZE_REG);
	chip->bri_q_maxsize_reg = ioपढ़ो32(p + PCH_PHUB_BRI_QUEUE_MAXSIZE_REG);
	chip->comp_resp_समयout_reg =
				ioपढ़ो32(p + PCH_PHUB_COMP_RESP_TIMEOUT_REG);
	chip->bus_slave_control_reg =
				ioपढ़ो32(p + PCH_PHUB_BUS_SLAVE_CONTROL_REG);
	chip->deadlock_aव्योम_type_reg =
				ioपढ़ो32(p + PCH_PHUB_DEADLOCK_AVOID_TYPE_REG);
	chip->पूर्णांकpin_reg_wpermit_reg0 =
				ioपढ़ो32(p + PCH_PHUB_INTPIN_REG_WPERMIT_REG0);
	chip->पूर्णांकpin_reg_wpermit_reg1 =
				ioपढ़ो32(p + PCH_PHUB_INTPIN_REG_WPERMIT_REG1);
	chip->पूर्णांकpin_reg_wpermit_reg2 =
				ioपढ़ो32(p + PCH_PHUB_INTPIN_REG_WPERMIT_REG2);
	chip->पूर्णांकpin_reg_wpermit_reg3 =
				ioपढ़ो32(p + PCH_PHUB_INTPIN_REG_WPERMIT_REG3);
	dev_dbg(&pdev->dev, "%s : "
		"chip->phub_id_reg=%x, "
		"chip->q_pri_val_reg=%x, "
		"chip->rc_q_maxsize_reg=%x, "
		"chip->bri_q_maxsize_reg=%x, "
		"chip->comp_resp_timeout_reg=%x, "
		"chip->bus_slave_control_reg=%x, "
		"chip->deadlock_avoid_type_reg=%x, "
		"chip->intpin_reg_wpermit_reg0=%x, "
		"chip->intpin_reg_wpermit_reg1=%x, "
		"chip->intpin_reg_wpermit_reg2=%x, "
		"chip->intpin_reg_wpermit_reg3=%x\n", __func__,
		chip->phub_id_reg,
		chip->q_pri_val_reg,
		chip->rc_q_maxsize_reg,
		chip->bri_q_maxsize_reg,
		chip->comp_resp_समयout_reg,
		chip->bus_slave_control_reg,
		chip->deadlock_aव्योम_type_reg,
		chip->पूर्णांकpin_reg_wpermit_reg0,
		chip->पूर्णांकpin_reg_wpermit_reg1,
		chip->पूर्णांकpin_reg_wpermit_reg2,
		chip->पूर्णांकpin_reg_wpermit_reg3);
	क्रम (i = 0; i < MAX_NUM_INT_REDUCE_CONTROL_REG; i++) अणु
		chip->पूर्णांक_reduce_control_reg[i] =
		    ioपढ़ो32(p + PCH_PHUB_INT_REDUCE_CONTROL_REG_BASE + 4 * i);
		dev_dbg(&pdev->dev, "%s : "
			"chip->int_reduce_control_reg[%d]=%x\n",
			__func__, i, chip->पूर्णांक_reduce_control_reg[i]);
	पूर्ण
	chip->clkcfg_reg = ioपढ़ो32(p + CLKCFG_REG_OFFSET);
	अगर ((chip->ioh_type == 2) || (chip->ioh_type == 4))
		chip->funcsel_reg = ioपढ़ो32(p + FUNCSEL_REG_OFFSET);
पूर्ण

/* pch_phub_restore_reg_conf - restore रेजिस्टर configuration */
अटल व्योम __maybe_unused pch_phub_restore_reg_conf(काष्ठा pci_dev *pdev)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा pch_phub_reg *chip = pci_get_drvdata(pdev);
	व्योम __iomem *p;
	p = chip->pch_phub_base_address;

	ioग_लिखो32(chip->phub_id_reg, p + PCH_PHUB_ID_REG);
	ioग_लिखो32(chip->q_pri_val_reg, p + PCH_PHUB_QUEUE_PRI_VAL_REG);
	ioग_लिखो32(chip->rc_q_maxsize_reg, p + PCH_PHUB_RC_QUEUE_MAXSIZE_REG);
	ioग_लिखो32(chip->bri_q_maxsize_reg, p + PCH_PHUB_BRI_QUEUE_MAXSIZE_REG);
	ioग_लिखो32(chip->comp_resp_समयout_reg,
					p + PCH_PHUB_COMP_RESP_TIMEOUT_REG);
	ioग_लिखो32(chip->bus_slave_control_reg,
					p + PCH_PHUB_BUS_SLAVE_CONTROL_REG);
	ioग_लिखो32(chip->deadlock_aव्योम_type_reg,
					p + PCH_PHUB_DEADLOCK_AVOID_TYPE_REG);
	ioग_लिखो32(chip->पूर्णांकpin_reg_wpermit_reg0,
					p + PCH_PHUB_INTPIN_REG_WPERMIT_REG0);
	ioग_लिखो32(chip->पूर्णांकpin_reg_wpermit_reg1,
					p + PCH_PHUB_INTPIN_REG_WPERMIT_REG1);
	ioग_लिखो32(chip->पूर्णांकpin_reg_wpermit_reg2,
					p + PCH_PHUB_INTPIN_REG_WPERMIT_REG2);
	ioग_लिखो32(chip->पूर्णांकpin_reg_wpermit_reg3,
					p + PCH_PHUB_INTPIN_REG_WPERMIT_REG3);
	dev_dbg(&pdev->dev, "%s : "
		"chip->phub_id_reg=%x, "
		"chip->q_pri_val_reg=%x, "
		"chip->rc_q_maxsize_reg=%x, "
		"chip->bri_q_maxsize_reg=%x, "
		"chip->comp_resp_timeout_reg=%x, "
		"chip->bus_slave_control_reg=%x, "
		"chip->deadlock_avoid_type_reg=%x, "
		"chip->intpin_reg_wpermit_reg0=%x, "
		"chip->intpin_reg_wpermit_reg1=%x, "
		"chip->intpin_reg_wpermit_reg2=%x, "
		"chip->intpin_reg_wpermit_reg3=%x\n", __func__,
		chip->phub_id_reg,
		chip->q_pri_val_reg,
		chip->rc_q_maxsize_reg,
		chip->bri_q_maxsize_reg,
		chip->comp_resp_समयout_reg,
		chip->bus_slave_control_reg,
		chip->deadlock_aव्योम_type_reg,
		chip->पूर्णांकpin_reg_wpermit_reg0,
		chip->पूर्णांकpin_reg_wpermit_reg1,
		chip->पूर्णांकpin_reg_wpermit_reg2,
		chip->पूर्णांकpin_reg_wpermit_reg3);
	क्रम (i = 0; i < MAX_NUM_INT_REDUCE_CONTROL_REG; i++) अणु
		ioग_लिखो32(chip->पूर्णांक_reduce_control_reg[i],
			p + PCH_PHUB_INT_REDUCE_CONTROL_REG_BASE + 4 * i);
		dev_dbg(&pdev->dev, "%s : "
			"chip->int_reduce_control_reg[%d]=%x\n",
			__func__, i, chip->पूर्णांक_reduce_control_reg[i]);
	पूर्ण

	ioग_लिखो32(chip->clkcfg_reg, p + CLKCFG_REG_OFFSET);
	अगर ((chip->ioh_type == 2) || (chip->ioh_type == 4))
		ioग_लिखो32(chip->funcsel_reg, p + FUNCSEL_REG_OFFSET);
पूर्ण

/**
 * pch_phub_पढ़ो_serial_rom() - Reading Serial ROM
 * @chip:		Poपूर्णांकer to the PHUB रेजिस्टर काष्ठाure
 * @offset_address:	Serial ROM offset address to पढ़ो.
 * @data:		Read buffer क्रम specअगरied Serial ROM value.
 */
अटल व्योम pch_phub_पढ़ो_serial_rom(काष्ठा pch_phub_reg *chip,
				     अचिन्हित पूर्णांक offset_address, u8 *data)
अणु
	व्योम __iomem *mem_addr = chip->pch_phub_extrom_base_address +
								offset_address;

	*data = ioपढ़ो8(mem_addr);
पूर्ण

/**
 * pch_phub_ग_लिखो_serial_rom() - Writing Serial ROM
 * @chip:		Poपूर्णांकer to the PHUB रेजिस्टर काष्ठाure
 * @offset_address:	Serial ROM offset address.
 * @data:		Serial ROM value to ग_लिखो.
 */
अटल पूर्णांक pch_phub_ग_लिखो_serial_rom(काष्ठा pch_phub_reg *chip,
				     अचिन्हित पूर्णांक offset_address, u8 data)
अणु
	व्योम __iomem *mem_addr = chip->pch_phub_extrom_base_address +
					(offset_address & PCH_WORD_ADDR_MASK);
	पूर्णांक i;
	अचिन्हित पूर्णांक word_data;
	अचिन्हित पूर्णांक pos;
	अचिन्हित पूर्णांक mask;
	pos = (offset_address % 4) * 8;
	mask = ~(0xFF << pos);

	ioग_लिखो32(PCH_PHUB_ROM_WRITE_ENABLE,
			chip->pch_phub_extrom_base_address + PHUB_CONTROL);

	word_data = ioपढ़ो32(mem_addr);
	ioग_लिखो32((word_data & mask) | (u32)data << pos, mem_addr);

	i = 0;
	जबतक (ioपढ़ो8(chip->pch_phub_extrom_base_address +
						PHUB_STATUS) != 0x00) अणु
		msleep(1);
		अगर (i == PHUB_TIMEOUT)
			वापस -ETIMEDOUT;
		i++;
	पूर्ण

	ioग_लिखो32(PCH_PHUB_ROM_WRITE_DISABLE,
			chip->pch_phub_extrom_base_address + PHUB_CONTROL);

	वापस 0;
पूर्ण

/**
 * pch_phub_पढ़ो_serial_rom_val() - Read Serial ROM value
 * @chip:		Poपूर्णांकer to the PHUB रेजिस्टर काष्ठाure
 * @offset_address:	Serial ROM address offset value.
 * @data:		Serial ROM value to पढ़ो.
 */
अटल व्योम pch_phub_पढ़ो_serial_rom_val(काष्ठा pch_phub_reg *chip,
					 अचिन्हित पूर्णांक offset_address, u8 *data)
अणु
	अचिन्हित पूर्णांक mem_addr;

	mem_addr = chip->pch_mac_start_address +
			pch_phub_mac_offset[offset_address];

	pch_phub_पढ़ो_serial_rom(chip, mem_addr, data);
पूर्ण

/**
 * pch_phub_ग_लिखो_serial_rom_val() - writing Serial ROM value
 * @chip:		Poपूर्णांकer to the PHUB रेजिस्टर काष्ठाure
 * @offset_address:	Serial ROM address offset value.
 * @data:		Serial ROM value.
 */
अटल पूर्णांक pch_phub_ग_लिखो_serial_rom_val(काष्ठा pch_phub_reg *chip,
					 अचिन्हित पूर्णांक offset_address, u8 data)
अणु
	पूर्णांक retval;
	अचिन्हित पूर्णांक mem_addr;

	mem_addr = chip->pch_mac_start_address +
			pch_phub_mac_offset[offset_address];

	retval = pch_phub_ग_लिखो_serial_rom(chip, mem_addr, data);

	वापस retval;
पूर्ण

/* pch_phub_gbe_serial_rom_conf - makes Serial ROM header क्रमmat configuration
 * क्रम Gigabit Ethernet MAC address
 */
अटल पूर्णांक pch_phub_gbe_serial_rom_conf(काष्ठा pch_phub_reg *chip)
अणु
	पूर्णांक retval;

	retval = pch_phub_ग_लिखो_serial_rom(chip, 0x0b, 0xbc);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x0a, 0x10);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x09, 0x01);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x08, 0x02);

	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x0f, 0x00);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x0e, 0x00);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x0d, 0x00);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x0c, 0x80);

	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x13, 0xbc);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x12, 0x10);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x11, 0x01);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x10, 0x18);

	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x1b, 0xbc);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x1a, 0x10);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x19, 0x01);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x18, 0x19);

	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x23, 0xbc);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x22, 0x10);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x21, 0x01);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x20, 0x3a);

	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x27, 0x01);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x26, 0x00);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x25, 0x00);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x24, 0x00);

	वापस retval;
पूर्ण

/* pch_phub_gbe_serial_rom_conf_mp - makes SerialROM header क्रमmat configuration
 * क्रम Gigabit Ethernet MAC address
 */
अटल पूर्णांक pch_phub_gbe_serial_rom_conf_mp(काष्ठा pch_phub_reg *chip)
अणु
	पूर्णांक retval;
	u32 offset_addr;

	offset_addr = 0x200;
	retval = pch_phub_ग_लिखो_serial_rom(chip, 0x03 + offset_addr, 0xbc);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x02 + offset_addr, 0x00);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x01 + offset_addr, 0x40);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x00 + offset_addr, 0x02);

	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x07 + offset_addr, 0x00);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x06 + offset_addr, 0x00);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x05 + offset_addr, 0x00);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x04 + offset_addr, 0x80);

	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x0b + offset_addr, 0xbc);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x0a + offset_addr, 0x00);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x09 + offset_addr, 0x40);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x08 + offset_addr, 0x18);

	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x13 + offset_addr, 0xbc);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x12 + offset_addr, 0x00);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x11 + offset_addr, 0x40);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x10 + offset_addr, 0x19);

	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x1b + offset_addr, 0xbc);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x1a + offset_addr, 0x00);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x19 + offset_addr, 0x40);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x18 + offset_addr, 0x3a);

	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x1f + offset_addr, 0x01);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x1e + offset_addr, 0x00);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x1d + offset_addr, 0x00);
	retval |= pch_phub_ग_लिखो_serial_rom(chip, 0x1c + offset_addr, 0x00);

	वापस retval;
पूर्ण

/**
 * pch_phub_पढ़ो_gbe_mac_addr() - Read Gigabit Ethernet MAC address
 * @chip:		Poपूर्णांकer to the PHUB रेजिस्टर काष्ठाure
 * @data:		Buffer of the Gigabit Ethernet MAC address value.
 */
अटल व्योम pch_phub_पढ़ो_gbe_mac_addr(काष्ठा pch_phub_reg *chip, u8 *data)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < ETH_ALEN; i++)
		pch_phub_पढ़ो_serial_rom_val(chip, i, &data[i]);
पूर्ण

/**
 * pch_phub_ग_लिखो_gbe_mac_addr() - Write MAC address
 * @chip:		Poपूर्णांकer to the PHUB रेजिस्टर काष्ठाure
 * @data:		Gigabit Ethernet MAC address value.
 */
अटल पूर्णांक pch_phub_ग_लिखो_gbe_mac_addr(काष्ठा pch_phub_reg *chip, u8 *data)
अणु
	पूर्णांक retval;
	पूर्णांक i;

	अगर ((chip->ioh_type == 1) || (chip->ioh_type == 5)) /* EG20T or ML7831*/
		retval = pch_phub_gbe_serial_rom_conf(chip);
	अन्यथा	/* ML7223 */
		retval = pch_phub_gbe_serial_rom_conf_mp(chip);
	अगर (retval)
		वापस retval;

	क्रम (i = 0; i < ETH_ALEN; i++) अणु
		retval = pch_phub_ग_लिखो_serial_rom_val(chip, i, data[i]);
		अगर (retval)
			वापस retval;
	पूर्ण

	वापस retval;
पूर्ण

अटल sमाप_प्रकार pch_phub_bin_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
				 काष्ठा bin_attribute *attr, अक्षर *buf,
				 loff_t off, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक rom_signature;
	अचिन्हित अक्षर rom_length;
	अचिन्हित पूर्णांक पंचांगp;
	अचिन्हित पूर्णांक addr_offset;
	अचिन्हित पूर्णांक orom_size;
	पूर्णांक ret;
	पूर्णांक err;
	sमाप_प्रकार rom_size;

	काष्ठा pch_phub_reg *chip = dev_get_drvdata(kobj_to_dev(kobj));

	ret = mutex_lock_पूर्णांकerruptible(&pch_phub_mutex);
	अगर (ret) अणु
		err = -ERESTARTSYS;
		जाओ वापस_err_nomutex;
	पूर्ण

	/* Get Rom signature */
	chip->pch_phub_extrom_base_address = pci_map_rom(chip->pdev, &rom_size);
	अगर (!chip->pch_phub_extrom_base_address) अणु
		err = -ENODATA;
		जाओ exrom_map_err;
	पूर्ण

	pch_phub_पढ़ो_serial_rom(chip, chip->pch_opt_rom_start_address,
				(अचिन्हित अक्षर *)&rom_signature);
	rom_signature &= 0xff;
	pch_phub_पढ़ो_serial_rom(chip, chip->pch_opt_rom_start_address + 1,
				(अचिन्हित अक्षर *)&पंचांगp);
	rom_signature |= (पंचांगp & 0xff) << 8;
	अगर (rom_signature == 0xAA55) अणु
		pch_phub_पढ़ो_serial_rom(chip,
					 chip->pch_opt_rom_start_address + 2,
					 &rom_length);
		orom_size = rom_length * 512;
		अगर (orom_size < off) अणु
			addr_offset = 0;
			जाओ वापस_ok;
		पूर्ण
		अगर (orom_size < count) अणु
			addr_offset = 0;
			जाओ वापस_ok;
		पूर्ण

		क्रम (addr_offset = 0; addr_offset < count; addr_offset++) अणु
			pch_phub_पढ़ो_serial_rom(chip,
			    chip->pch_opt_rom_start_address + addr_offset + off,
			    &buf[addr_offset]);
		पूर्ण
	पूर्ण अन्यथा अणु
		err = -ENODATA;
		जाओ वापस_err;
	पूर्ण
वापस_ok:
	pci_unmap_rom(chip->pdev, chip->pch_phub_extrom_base_address);
	mutex_unlock(&pch_phub_mutex);
	वापस addr_offset;

वापस_err:
	pci_unmap_rom(chip->pdev, chip->pch_phub_extrom_base_address);
exrom_map_err:
	mutex_unlock(&pch_phub_mutex);
वापस_err_nomutex:
	वापस err;
पूर्ण

अटल sमाप_प्रकार pch_phub_bin_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
				  काष्ठा bin_attribute *attr,
				  अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक addr_offset;
	पूर्णांक ret;
	sमाप_प्रकार rom_size;
	काष्ठा pch_phub_reg *chip = dev_get_drvdata(kobj_to_dev(kobj));

	ret = mutex_lock_पूर्णांकerruptible(&pch_phub_mutex);
	अगर (ret)
		वापस -ERESTARTSYS;

	अगर (off > PCH_PHUB_OROM_SIZE) अणु
		addr_offset = 0;
		जाओ वापस_ok;
	पूर्ण
	अगर (count > PCH_PHUB_OROM_SIZE) अणु
		addr_offset = 0;
		जाओ वापस_ok;
	पूर्ण

	chip->pch_phub_extrom_base_address = pci_map_rom(chip->pdev, &rom_size);
	अगर (!chip->pch_phub_extrom_base_address) अणु
		err = -ENOMEM;
		जाओ exrom_map_err;
	पूर्ण

	क्रम (addr_offset = 0; addr_offset < count; addr_offset++) अणु
		अगर (PCH_PHUB_OROM_SIZE < off + addr_offset)
			जाओ वापस_ok;

		ret = pch_phub_ग_लिखो_serial_rom(chip,
			    chip->pch_opt_rom_start_address + addr_offset + off,
			    buf[addr_offset]);
		अगर (ret) अणु
			err = ret;
			जाओ वापस_err;
		पूर्ण
	पूर्ण

वापस_ok:
	pci_unmap_rom(chip->pdev, chip->pch_phub_extrom_base_address);
	mutex_unlock(&pch_phub_mutex);
	वापस addr_offset;

वापस_err:
	pci_unmap_rom(chip->pdev, chip->pch_phub_extrom_base_address);

exrom_map_err:
	mutex_unlock(&pch_phub_mutex);
	वापस err;
पूर्ण

अटल sमाप_प्रकार show_pch_mac(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	u8 mac[8];
	काष्ठा pch_phub_reg *chip = dev_get_drvdata(dev);
	sमाप_प्रकार rom_size;

	chip->pch_phub_extrom_base_address = pci_map_rom(chip->pdev, &rom_size);
	अगर (!chip->pch_phub_extrom_base_address)
		वापस -ENOMEM;

	pch_phub_पढ़ो_gbe_mac_addr(chip, mac);
	pci_unmap_rom(chip->pdev, chip->pch_phub_extrom_base_address);

	वापस प्र_लिखो(buf, "%pM\n", mac);
पूर्ण

अटल sमाप_प्रकार store_pch_mac(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u8 mac[ETH_ALEN];
	sमाप_प्रकार rom_size;
	काष्ठा pch_phub_reg *chip = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (!mac_pton(buf, mac))
		वापस -EINVAL;

	chip->pch_phub_extrom_base_address = pci_map_rom(chip->pdev, &rom_size);
	अगर (!chip->pch_phub_extrom_base_address)
		वापस -ENOMEM;

	ret = pch_phub_ग_लिखो_gbe_mac_addr(chip, mac);
	pci_unmap_rom(chip->pdev, chip->pch_phub_extrom_base_address);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल DEVICE_ATTR(pch_mac, S_IRUGO | S_IWUSR, show_pch_mac, store_pch_mac);

अटल स्थिर काष्ठा bin_attribute pch_bin_attr = अणु
	.attr = अणु
		.name = "pch_firmware",
		.mode = S_IRUGO | S_IWUSR,
	पूर्ण,
	.size = PCH_PHUB_OROM_SIZE + 1,
	.पढ़ो = pch_phub_bin_पढ़ो,
	.ग_लिखो = pch_phub_bin_ग_लिखो,
पूर्ण;

अटल पूर्णांक pch_phub_probe(काष्ठा pci_dev *pdev,
				    स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा pch_phub_reg *chip;

	chip = kzalloc(माप(काष्ठा pch_phub_reg), GFP_KERNEL);
	अगर (chip == शून्य)
		वापस -ENOMEM;

	ret = pci_enable_device(pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev,
		"%s : pci_enable_device FAILED(ret=%d)", __func__, ret);
		जाओ err_pci_enable_dev;
	पूर्ण
	dev_dbg(&pdev->dev, "%s : pci_enable_device returns %d\n", __func__,
		ret);

	ret = pci_request_regions(pdev, KBUILD_MODNAME);
	अगर (ret) अणु
		dev_err(&pdev->dev,
		"%s : pci_request_regions FAILED(ret=%d)", __func__, ret);
		जाओ err_req_regions;
	पूर्ण
	dev_dbg(&pdev->dev, "%s : "
		"pci_request_regions returns %d\n", __func__, ret);

	chip->pch_phub_base_address = pci_iomap(pdev, 1, 0);


	अगर (chip->pch_phub_base_address == शून्य) अणु
		dev_err(&pdev->dev, "%s : pci_iomap FAILED", __func__);
		ret = -ENOMEM;
		जाओ err_pci_iomap;
	पूर्ण
	dev_dbg(&pdev->dev, "%s : pci_iomap SUCCESS and value "
		"in pch_phub_base_address variable is %p\n", __func__,
		chip->pch_phub_base_address);

	chip->pdev = pdev; /* Save pci device काष्ठा */

	अगर (id->driver_data == 1) अणु /* EG20T PCH */
		स्थिर अक्षर *board_name;
		अचिन्हित पूर्णांक prefetch = 0x000affaa;

		अगर (pdev->dev.of_node)
			of_property_पढ़ो_u32(pdev->dev.of_node,
						  "intel,eg20t-prefetch",
						  &prefetch);

		ret = sysfs_create_file(&pdev->dev.kobj,
					&dev_attr_pch_mac.attr);
		अगर (ret)
			जाओ err_sysfs_create;

		ret = sysfs_create_bin_file(&pdev->dev.kobj, &pch_bin_attr);
		अगर (ret)
			जाओ निकास_bin_attr;

		pch_phub_पढ़ो_modअगरy_ग_लिखो_reg(chip,
					       (अचिन्हित पूर्णांक)CLKCFG_REG_OFFSET,
					       CLKCFG_CAN_50MHZ,
					       CLKCFG_CANCLK_MASK);

		/* quirk क्रम CM-iTC board */
		board_name = dmi_get_प्रणाली_info(DMI_BOARD_NAME);
		अगर (board_name && म_माला(board_name, "CM-iTC"))
			pch_phub_पढ़ो_modअगरy_ग_लिखो_reg(chip,
						(अचिन्हित पूर्णांक)CLKCFG_REG_OFFSET,
						CLKCFG_UART_48MHZ | CLKCFG_BAUDDIV |
						CLKCFG_PLL2VCO | CLKCFG_UARTCLKSEL,
						CLKCFG_UART_MASK);

		/* set the prefech value */
		ioग_लिखो32(prefetch, chip->pch_phub_base_address + 0x14);
		/* set the पूर्णांकerrupt delay value */
		ioग_लिखो32(0x25, chip->pch_phub_base_address + 0x44);
		chip->pch_opt_rom_start_address = PCH_PHUB_ROM_START_ADDR_EG20T;
		chip->pch_mac_start_address = PCH_PHUB_MAC_START_ADDR_EG20T;

		/* quirk क्रम MIPS Boston platक्रमm */
		अगर (pdev->dev.of_node) अणु
			अगर (of_machine_is_compatible("img,boston")) अणु
				pch_phub_पढ़ो_modअगरy_ग_लिखो_reg(chip,
					(अचिन्हित पूर्णांक)CLKCFG_REG_OFFSET,
					CLKCFG_UART_25MHZ,
					CLKCFG_UART_MASK);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (id->driver_data == 2) अणु /* ML7213 IOH */
		ret = sysfs_create_bin_file(&pdev->dev.kobj, &pch_bin_attr);
		अगर (ret)
			जाओ err_sysfs_create;
		/* set the prefech value
		 * Device2(USB OHCI #1/ USB EHCI #1/ USB Device):a
		 * Device4(SDIO #0,1,2):f
		 * Device6(SATA 2):f
		 * Device8(USB OHCI #0/ USB EHCI #0):a
		 */
		ioग_लिखो32(0x000affa0, chip->pch_phub_base_address + 0x14);
		chip->pch_opt_rom_start_address =\
						 PCH_PHUB_ROM_START_ADDR_ML7213;
	पूर्ण अन्यथा अगर (id->driver_data == 3) अणु /* ML7223 IOH Bus-m*/
		/* set the prefech value
		 * Device8(GbE)
		 */
		ioग_लिखो32(0x000a0000, chip->pch_phub_base_address + 0x14);
		/* set the पूर्णांकerrupt delay value */
		ioग_लिखो32(0x25, chip->pch_phub_base_address + 0x140);
		chip->pch_opt_rom_start_address =\
						 PCH_PHUB_ROM_START_ADDR_ML7223;
		chip->pch_mac_start_address = PCH_PHUB_MAC_START_ADDR_ML7223;
	पूर्ण अन्यथा अगर (id->driver_data == 4) अणु /* ML7223 IOH Bus-n*/
		ret = sysfs_create_file(&pdev->dev.kobj,
					&dev_attr_pch_mac.attr);
		अगर (ret)
			जाओ err_sysfs_create;
		ret = sysfs_create_bin_file(&pdev->dev.kobj, &pch_bin_attr);
		अगर (ret)
			जाओ निकास_bin_attr;
		/* set the prefech value
		 * Device2(USB OHCI #0,1,2,3/ USB EHCI #0):a
		 * Device4(SDIO #0,1):f
		 * Device6(SATA 2):f
		 */
		ioग_लिखो32(0x0000ffa0, chip->pch_phub_base_address + 0x14);
		chip->pch_opt_rom_start_address =\
						 PCH_PHUB_ROM_START_ADDR_ML7223;
		chip->pch_mac_start_address = PCH_PHUB_MAC_START_ADDR_ML7223;
	पूर्ण अन्यथा अगर (id->driver_data == 5) अणु /* ML7831 */
		ret = sysfs_create_file(&pdev->dev.kobj,
					&dev_attr_pch_mac.attr);
		अगर (ret)
			जाओ err_sysfs_create;

		ret = sysfs_create_bin_file(&pdev->dev.kobj, &pch_bin_attr);
		अगर (ret)
			जाओ निकास_bin_attr;

		/* set the prefech value */
		ioग_लिखो32(0x000affaa, chip->pch_phub_base_address + 0x14);
		/* set the पूर्णांकerrupt delay value */
		ioग_लिखो32(0x25, chip->pch_phub_base_address + 0x44);
		chip->pch_opt_rom_start_address = PCH_PHUB_ROM_START_ADDR_EG20T;
		chip->pch_mac_start_address = PCH_PHUB_MAC_START_ADDR_EG20T;
	पूर्ण

	chip->ioh_type = id->driver_data;
	pci_set_drvdata(pdev, chip);

	वापस 0;
निकास_bin_attr:
	sysfs_हटाओ_file(&pdev->dev.kobj, &dev_attr_pch_mac.attr);

err_sysfs_create:
	pci_iounmap(pdev, chip->pch_phub_base_address);
err_pci_iomap:
	pci_release_regions(pdev);
err_req_regions:
	pci_disable_device(pdev);
err_pci_enable_dev:
	kमुक्त(chip);
	dev_err(&pdev->dev, "%s returns %d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल व्योम pch_phub_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pch_phub_reg *chip = pci_get_drvdata(pdev);

	sysfs_हटाओ_file(&pdev->dev.kobj, &dev_attr_pch_mac.attr);
	sysfs_हटाओ_bin_file(&pdev->dev.kobj, &pch_bin_attr);
	pci_iounmap(pdev, chip->pch_phub_base_address);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	kमुक्त(chip);
पूर्ण

अटल पूर्णांक __maybe_unused pch_phub_suspend(काष्ठा device *dev_d)
अणु
	device_wakeup_disable(dev_d);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused pch_phub_resume(काष्ठा device *dev_d)
अणु
	device_wakeup_disable(dev_d);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_device_id pch_phub_pcidev_id[] = अणु
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_PCH1_PHUB),       1,  पूर्ण,
	अणु PCI_VDEVICE(ROHM, PCI_DEVICE_ID_ROHM_ML7213_PHUB), 2,  पूर्ण,
	अणु PCI_VDEVICE(ROHM, PCI_DEVICE_ID_ROHM_ML7223_mPHUB), 3,  पूर्ण,
	अणु PCI_VDEVICE(ROHM, PCI_DEVICE_ID_ROHM_ML7223_nPHUB), 4,  पूर्ण,
	अणु PCI_VDEVICE(ROHM, PCI_DEVICE_ID_ROHM_ML7831_PHUB), 5,  पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, pch_phub_pcidev_id);

अटल SIMPLE_DEV_PM_OPS(pch_phub_pm_ops, pch_phub_suspend, pch_phub_resume);

अटल काष्ठा pci_driver pch_phub_driver = अणु
	.name = "pch_phub",
	.id_table = pch_phub_pcidev_id,
	.probe = pch_phub_probe,
	.हटाओ = pch_phub_हटाओ,
	.driver.pm = &pch_phub_pm_ops,
पूर्ण;

module_pci_driver(pch_phub_driver);

MODULE_DESCRIPTION("Intel EG20T PCH/LAPIS Semiconductor IOH(ML7213/ML7223) PHUB");
MODULE_LICENSE("GPL");
