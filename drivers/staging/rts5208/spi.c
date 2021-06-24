<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम Realtek PCI-Express card पढ़ोer
 *
 * Copyright(c) 2009-2013 Realtek Semiconductor Corp. All rights reserved.
 *
 * Author:
 *   Wei WANG (wei_wang@realsil.com.cn)
 *   Micky Ching (micky_ching@realsil.com.cn)
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched.h>

#समावेश "rtsx.h"
#समावेश "spi.h"

अटल अंतरभूत व्योम spi_set_err_code(काष्ठा rtsx_chip *chip, u8 err_code)
अणु
	काष्ठा spi_info *spi = &chip->spi;

	spi->err_code = err_code;
पूर्ण

अटल पूर्णांक spi_init(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, SPI_CONTROL, 0xFF,
				     CS_POLARITY_LOW | DTO_MSB_FIRST
				     | SPI_MASTER | SPI_MODE0 | SPI_AUTO);
	अगर (retval)
		वापस retval;
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, SPI_TCTL, EDO_TIMING_MASK,
				     SAMPLE_DELAY_HALF);
	अगर (retval)
		वापस retval;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक spi_set_init_para(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा spi_info *spi = &chip->spi;
	पूर्णांक retval;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, SPI_CLK_DIVIDER1, 0xFF,
				     (u8)(spi->clk_भाग >> 8));
	अगर (retval)
		वापस retval;
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, SPI_CLK_DIVIDER0, 0xFF,
				     (u8)(spi->clk_भाग));
	अगर (retval)
		वापस retval;

	retval = चयन_घड़ी(chip, spi->spi_घड़ी);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = select_card(chip, SPI_CARD);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_CLK_EN, SPI_CLK_EN,
				     SPI_CLK_EN);
	अगर (retval)
		वापस retval;
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_OE, SPI_OUTPUT_EN,
				     SPI_OUTPUT_EN);
	अगर (retval)
		वापस retval;

	रुको_समयout(10);

	retval = spi_init(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक sf_polling_status(काष्ठा rtsx_chip *chip, पूर्णांक msec)
अणु
	पूर्णांक retval;

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_COMMAND, 0xFF, SPI_RDSR);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_TRANSFER0, 0xFF,
		     SPI_TRANSFER0_START | SPI_POLLING_MODE0);
	rtsx_add_cmd(chip, CHECK_REG_CMD, SPI_TRANSFER0, SPI_TRANSFER0_END,
		     SPI_TRANSFER0_END);

	retval = rtsx_send_cmd(chip, 0, msec);
	अगर (retval < 0) अणु
		rtsx_clear_spi_error(chip);
		spi_set_err_code(chip, SPI_BUSY_ERR);
		वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक sf_enable_ग_लिखो(काष्ठा rtsx_chip *chip, u8 ins)
अणु
	काष्ठा spi_info *spi = &chip->spi;
	पूर्णांक retval;

	अगर (!spi->ग_लिखो_en)
		वापस STATUS_SUCCESS;

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_COMMAND, 0xFF, ins);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_CA_NUMBER, 0xFF,
		     SPI_COMMAND_BIT_8 | SPI_ADDRESS_BIT_24);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_TRANSFER0, 0xFF,
		     SPI_TRANSFER0_START | SPI_C_MODE0);
	rtsx_add_cmd(chip, CHECK_REG_CMD, SPI_TRANSFER0, SPI_TRANSFER0_END,
		     SPI_TRANSFER0_END);

	retval = rtsx_send_cmd(chip, 0, 100);
	अगर (retval < 0) अणु
		rtsx_clear_spi_error(chip);
		spi_set_err_code(chip, SPI_HW_ERR);
		वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक sf_disable_ग_लिखो(काष्ठा rtsx_chip *chip, u8 ins)
अणु
	काष्ठा spi_info *spi = &chip->spi;
	पूर्णांक retval;

	अगर (!spi->ग_लिखो_en)
		वापस STATUS_SUCCESS;

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_COMMAND, 0xFF, ins);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_CA_NUMBER, 0xFF,
		     SPI_COMMAND_BIT_8 | SPI_ADDRESS_BIT_24);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_TRANSFER0, 0xFF,
		     SPI_TRANSFER0_START | SPI_C_MODE0);
	rtsx_add_cmd(chip, CHECK_REG_CMD, SPI_TRANSFER0, SPI_TRANSFER0_END,
		     SPI_TRANSFER0_END);

	retval = rtsx_send_cmd(chip, 0, 100);
	अगर (retval < 0) अणु
		rtsx_clear_spi_error(chip);
		spi_set_err_code(chip, SPI_HW_ERR);
		वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल व्योम sf_program(काष्ठा rtsx_chip *chip, u8 ins, u8 addr_mode, u32 addr,
		       u16 len)
अणु
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_COMMAND, 0xFF, ins);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_CA_NUMBER, 0xFF,
		     SPI_COMMAND_BIT_8 | SPI_ADDRESS_BIT_24);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_LENGTH0, 0xFF, (u8)len);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_LENGTH1, 0xFF, (u8)(len >> 8));
	अगर (addr_mode) अणु
		rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_ADDR0, 0xFF, (u8)addr);
		rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_ADDR1, 0xFF,
			     (u8)(addr >> 8));
		rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_ADDR2, 0xFF,
			     (u8)(addr >> 16));
		rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_TRANSFER0, 0xFF,
			     SPI_TRANSFER0_START | SPI_CADO_MODE0);
	पूर्ण अन्यथा अणु
		rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_TRANSFER0, 0xFF,
			     SPI_TRANSFER0_START | SPI_CDO_MODE0);
	पूर्ण
	rtsx_add_cmd(chip, CHECK_REG_CMD, SPI_TRANSFER0, SPI_TRANSFER0_END,
		     SPI_TRANSFER0_END);
पूर्ण

अटल पूर्णांक sf_erase(काष्ठा rtsx_chip *chip, u8 ins, u8 addr_mode, u32 addr)
अणु
	पूर्णांक retval;

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_COMMAND, 0xFF, ins);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_CA_NUMBER, 0xFF,
		     SPI_COMMAND_BIT_8 | SPI_ADDRESS_BIT_24);
	अगर (addr_mode) अणु
		rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_ADDR0, 0xFF, (u8)addr);
		rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_ADDR1, 0xFF,
			     (u8)(addr >> 8));
		rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_ADDR2, 0xFF,
			     (u8)(addr >> 16));
		rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_TRANSFER0, 0xFF,
			     SPI_TRANSFER0_START | SPI_CA_MODE0);
	पूर्ण अन्यथा अणु
		rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_TRANSFER0, 0xFF,
			     SPI_TRANSFER0_START | SPI_C_MODE0);
	पूर्ण
	rtsx_add_cmd(chip, CHECK_REG_CMD, SPI_TRANSFER0, SPI_TRANSFER0_END,
		     SPI_TRANSFER0_END);

	retval = rtsx_send_cmd(chip, 0, 100);
	अगर (retval < 0) अणु
		rtsx_clear_spi_error(chip);
		spi_set_err_code(chip, SPI_HW_ERR);
		वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक spi_init_eeprom(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;
	पूर्णांक clk;

	अगर (chip->asic_code)
		clk = 30;
	अन्यथा
		clk = CLK_30;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, SPI_CLK_DIVIDER1, 0xFF, 0x00);
	अगर (retval)
		वापस retval;
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, SPI_CLK_DIVIDER0, 0xFF, 0x27);
	अगर (retval)
		वापस retval;

	retval = चयन_घड़ी(chip, clk);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = select_card(chip, SPI_CARD);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_CLK_EN, SPI_CLK_EN,
				     SPI_CLK_EN);
	अगर (retval)
		वापस retval;
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_OE, SPI_OUTPUT_EN,
				     SPI_OUTPUT_EN);
	अगर (retval)
		वापस retval;

	रुको_समयout(10);

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, SPI_CONTROL, 0xFF,
				     CS_POLARITY_HIGH | SPI_EEPROM_AUTO);
	अगर (retval)
		वापस retval;
	retval = rtsx_ग_लिखो_रेजिस्टर(chip, SPI_TCTL, EDO_TIMING_MASK,
				     SAMPLE_DELAY_HALF);
	अगर (retval)
		वापस retval;

	वापस STATUS_SUCCESS;
पूर्ण

अटल पूर्णांक spi_eeprom_program_enable(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_CA_NUMBER, 0xFF, 0x86);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_COMMAND, 0xFF, 0x13);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_TRANSFER0, 0xFF,
		     SPI_TRANSFER0_START | SPI_CA_MODE0);
	rtsx_add_cmd(chip, CHECK_REG_CMD, SPI_TRANSFER0, SPI_TRANSFER0_END,
		     SPI_TRANSFER0_END);

	retval = rtsx_send_cmd(chip, 0, 100);
	अगर (retval < 0)
		वापस STATUS_FAIL;

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक spi_erase_eeprom_chip(काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;

	retval = spi_init_eeprom(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = spi_eeprom_program_enable(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_GPIO_सूची, 0x01, 0);
	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE, 0x01, RING_BUFFER);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_COMMAND, 0xFF, 0x12);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_CA_NUMBER, 0xFF, 0x84);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_TRANSFER0, 0xFF,
		     SPI_TRANSFER0_START | SPI_CA_MODE0);
	rtsx_add_cmd(chip, CHECK_REG_CMD, SPI_TRANSFER0, SPI_TRANSFER0_END,
		     SPI_TRANSFER0_END);

	retval = rtsx_send_cmd(chip, 0, 100);
	अगर (retval < 0)
		वापस STATUS_FAIL;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_GPIO_सूची, 0x01, 0x01);
	अगर (retval)
		वापस retval;

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक spi_erase_eeprom_byte(काष्ठा rtsx_chip *chip, u16 addr)
अणु
	पूर्णांक retval;

	retval = spi_init_eeprom(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = spi_eeprom_program_enable(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_GPIO_सूची, 0x01, 0);
	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE, 0x01, RING_BUFFER);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_COMMAND, 0xFF, 0x07);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_ADDR0, 0xFF, (u8)addr);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_ADDR1, 0xFF, (u8)(addr >> 8));
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_CA_NUMBER, 0xFF, 0x46);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_TRANSFER0, 0xFF,
		     SPI_TRANSFER0_START | SPI_CA_MODE0);
	rtsx_add_cmd(chip, CHECK_REG_CMD, SPI_TRANSFER0, SPI_TRANSFER0_END,
		     SPI_TRANSFER0_END);

	retval = rtsx_send_cmd(chip, 0, 100);
	अगर (retval < 0)
		वापस STATUS_FAIL;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_GPIO_सूची, 0x01, 0x01);
	अगर (retval)
		वापस retval;

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक spi_पढ़ो_eeprom(काष्ठा rtsx_chip *chip, u16 addr, u8 *val)
अणु
	पूर्णांक retval;
	u8 data;

	retval = spi_init_eeprom(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_GPIO_सूची, 0x01, 0);
	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE, 0x01, RING_BUFFER);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_COMMAND, 0xFF, 0x06);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_ADDR0, 0xFF, (u8)addr);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_ADDR1, 0xFF, (u8)(addr >> 8));
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_CA_NUMBER, 0xFF, 0x46);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_LENGTH0, 0xFF, 1);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_TRANSFER0, 0xFF,
		     SPI_TRANSFER0_START | SPI_CADI_MODE0);
	rtsx_add_cmd(chip, CHECK_REG_CMD, SPI_TRANSFER0, SPI_TRANSFER0_END,
		     SPI_TRANSFER0_END);

	retval = rtsx_send_cmd(chip, 0, 100);
	अगर (retval < 0)
		वापस STATUS_FAIL;

	रुको_समयout(5);
	retval = rtsx_पढ़ो_रेजिस्टर(chip, SPI_DATA, &data);
	अगर (retval)
		वापस retval;

	अगर (val)
		*val = data;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_GPIO_सूची, 0x01, 0x01);
	अगर (retval)
		वापस retval;

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक spi_ग_लिखो_eeprom(काष्ठा rtsx_chip *chip, u16 addr, u8 val)
अणु
	पूर्णांक retval;

	retval = spi_init_eeprom(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	retval = spi_eeprom_program_enable(chip);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_GPIO_सूची, 0x01, 0);
	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE, 0x01, RING_BUFFER);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_COMMAND, 0xFF, 0x05);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_ADDR0, 0xFF, val);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_ADDR1, 0xFF, (u8)addr);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_ADDR2, 0xFF, (u8)(addr >> 8));
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_CA_NUMBER, 0xFF, 0x4E);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_TRANSFER0, 0xFF,
		     SPI_TRANSFER0_START | SPI_CA_MODE0);
	rtsx_add_cmd(chip, CHECK_REG_CMD, SPI_TRANSFER0, SPI_TRANSFER0_END,
		     SPI_TRANSFER0_END);

	retval = rtsx_send_cmd(chip, 0, 100);
	अगर (retval < 0)
		वापस STATUS_FAIL;

	retval = rtsx_ग_लिखो_रेजिस्टर(chip, CARD_GPIO_सूची, 0x01, 0x01);
	अगर (retval)
		वापस retval;

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक spi_get_status(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	काष्ठा spi_info *spi = &chip->spi;

	dev_dbg(rtsx_dev(chip), "%s: err_code = 0x%x\n", __func__,
		spi->err_code);
	rtsx_stor_set_xfer_buf(&spi->err_code,
			       min_t(पूर्णांक, scsi_bufflen(srb), 1), srb);
	scsi_set_resid(srb, scsi_bufflen(srb) - 1);

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक spi_set_parameter(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	काष्ठा spi_info *spi = &chip->spi;

	spi_set_err_code(chip, SPI_NO_ERR);

	अगर (chip->asic_code)
		spi->spi_घड़ी = ((u16)(srb->cmnd[8]) << 8) | srb->cmnd[9];
	अन्यथा
		spi->spi_घड़ी = srb->cmnd[3];

	spi->clk_भाग = ((u16)(srb->cmnd[4]) << 8) | srb->cmnd[5];
	spi->ग_लिखो_en = srb->cmnd[6];

	dev_dbg(rtsx_dev(chip), "%s: ", __func__);
	dev_dbg(rtsx_dev(chip), "spi_clock = %d, ", spi->spi_घड़ी);
	dev_dbg(rtsx_dev(chip), "clk_div = %d, ", spi->clk_भाग);
	dev_dbg(rtsx_dev(chip), "write_en = %d\n", spi->ग_लिखो_en);

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक spi_पढ़ो_flash_id(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;
	u16 len;
	u8 *buf;

	spi_set_err_code(chip, SPI_NO_ERR);

	len = ((u16)(srb->cmnd[7]) << 8) | srb->cmnd[8];
	अगर (len > 512) अणु
		spi_set_err_code(chip, SPI_INVALID_COMMAND);
		वापस STATUS_FAIL;
	पूर्ण

	retval = spi_set_init_para(chip);
	अगर (retval != STATUS_SUCCESS) अणु
		spi_set_err_code(chip, SPI_HW_ERR);
		वापस STATUS_FAIL;
	पूर्ण

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE, 0x01,
		     PINGPONG_BUFFER);

	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_COMMAND, 0xFF, srb->cmnd[3]);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_ADDR2, 0xFF, srb->cmnd[4]);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_ADDR1, 0xFF, srb->cmnd[5]);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_ADDR0, 0xFF, srb->cmnd[6]);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_CA_NUMBER, 0xFF,
		     SPI_COMMAND_BIT_8 | SPI_ADDRESS_BIT_24);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_LENGTH1, 0xFF, srb->cmnd[7]);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_LENGTH0, 0xFF, srb->cmnd[8]);

	अगर (len == 0) अणु
		अगर (srb->cmnd[9]) अणु
			rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_TRANSFER0,
				     0xFF, SPI_TRANSFER0_START | SPI_CA_MODE0);
		पूर्ण अन्यथा अणु
			rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_TRANSFER0,
				     0xFF, SPI_TRANSFER0_START | SPI_C_MODE0);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (srb->cmnd[9]) अणु
			rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_TRANSFER0, 0xFF,
				     SPI_TRANSFER0_START | SPI_CADI_MODE0);
		पूर्ण अन्यथा अणु
			rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_TRANSFER0, 0xFF,
				     SPI_TRANSFER0_START | SPI_CDI_MODE0);
		पूर्ण
	पूर्ण

	rtsx_add_cmd(chip, CHECK_REG_CMD, SPI_TRANSFER0, SPI_TRANSFER0_END,
		     SPI_TRANSFER0_END);

	retval = rtsx_send_cmd(chip, 0, 100);
	अगर (retval < 0) अणु
		rtsx_clear_spi_error(chip);
		spi_set_err_code(chip, SPI_HW_ERR);
		वापस STATUS_FAIL;
	पूर्ण

	अगर (len) अणु
		buf = kदो_स्मृति(len, GFP_KERNEL);
		अगर (!buf)
			वापस STATUS_ERROR;

		retval = rtsx_पढ़ो_ppbuf(chip, buf, len);
		अगर (retval != STATUS_SUCCESS) अणु
			spi_set_err_code(chip, SPI_READ_ERR);
			kमुक्त(buf);
			वापस STATUS_FAIL;
		पूर्ण

		rtsx_stor_set_xfer_buf(buf, scsi_bufflen(srb), srb);
		scsi_set_resid(srb, 0);

		kमुक्त(buf);
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक spi_पढ़ो_flash(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;
	अचिन्हित पूर्णांक index = 0, offset = 0;
	u8 ins, slow_पढ़ो;
	u32 addr;
	u16 len;
	u8 *buf;

	spi_set_err_code(chip, SPI_NO_ERR);

	ins = srb->cmnd[3];
	addr = ((u32)(srb->cmnd[4]) << 16) | ((u32)(srb->cmnd[5])
					<< 8) | srb->cmnd[6];
	len = ((u16)(srb->cmnd[7]) << 8) | srb->cmnd[8];
	slow_पढ़ो = srb->cmnd[9];

	retval = spi_set_init_para(chip);
	अगर (retval != STATUS_SUCCESS) अणु
		spi_set_err_code(chip, SPI_HW_ERR);
		वापस STATUS_FAIL;
	पूर्ण

	buf = kदो_स्मृति(SF_PAGE_LEN, GFP_KERNEL);
	अगर (!buf)
		वापस STATUS_ERROR;

	जबतक (len) अणु
		u16 pagelen = SF_PAGE_LEN - (u8)addr;

		अगर (pagelen > len)
			pagelen = len;

		rtsx_init_cmd(chip);

		trans_dma_enable(DMA_FROM_DEVICE, chip, 256, DMA_256);

		rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_COMMAND, 0xFF, ins);

		अगर (slow_पढ़ो) अणु
			rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_ADDR0, 0xFF,
				     (u8)addr);
			rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_ADDR1, 0xFF,
				     (u8)(addr >> 8));
			rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_ADDR2, 0xFF,
				     (u8)(addr >> 16));
			rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_CA_NUMBER, 0xFF,
				     SPI_COMMAND_BIT_8 | SPI_ADDRESS_BIT_24);
		पूर्ण अन्यथा अणु
			rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_ADDR1, 0xFF,
				     (u8)addr);
			rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_ADDR2, 0xFF,
				     (u8)(addr >> 8));
			rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_ADDR3, 0xFF,
				     (u8)(addr >> 16));
			rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_CA_NUMBER, 0xFF,
				     SPI_COMMAND_BIT_8 | SPI_ADDRESS_BIT_32);
		पूर्ण

		rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_LENGTH1, 0xFF,
			     (u8)(pagelen >> 8));
		rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_LENGTH0, 0xFF,
			     (u8)pagelen);

		rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_TRANSFER0, 0xFF,
			     SPI_TRANSFER0_START | SPI_CADI_MODE0);
		rtsx_add_cmd(chip, CHECK_REG_CMD, SPI_TRANSFER0,
			     SPI_TRANSFER0_END, SPI_TRANSFER0_END);

		rtsx_send_cmd_no_रुको(chip);

		retval = rtsx_transfer_data(chip, 0, buf, pagelen, 0,
					    DMA_FROM_DEVICE, 10000);
		अगर (retval < 0) अणु
			kमुक्त(buf);
			rtsx_clear_spi_error(chip);
			spi_set_err_code(chip, SPI_HW_ERR);
			वापस STATUS_FAIL;
		पूर्ण

		rtsx_stor_access_xfer_buf(buf, pagelen, srb, &index, &offset,
					  TO_XFER_BUF);

		addr += pagelen;
		len -= pagelen;
	पूर्ण

	scsi_set_resid(srb, 0);
	kमुक्त(buf);

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक spi_ग_लिखो_flash(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;
	u8 ins, program_mode;
	u32 addr;
	u16 len;
	u8 *buf;
	अचिन्हित पूर्णांक index = 0, offset = 0;

	spi_set_err_code(chip, SPI_NO_ERR);

	ins = srb->cmnd[3];
	addr = ((u32)(srb->cmnd[4]) << 16) | ((u32)(srb->cmnd[5])
					<< 8) | srb->cmnd[6];
	len = ((u16)(srb->cmnd[7]) << 8) | srb->cmnd[8];
	program_mode = srb->cmnd[9];

	retval = spi_set_init_para(chip);
	अगर (retval != STATUS_SUCCESS) अणु
		spi_set_err_code(chip, SPI_HW_ERR);
		वापस STATUS_FAIL;
	पूर्ण

	अगर (program_mode == BYTE_PROGRAM) अणु
		buf = kदो_स्मृति(4, GFP_KERNEL);
		अगर (!buf)
			वापस STATUS_ERROR;

		जबतक (len) अणु
			retval = sf_enable_ग_लिखो(chip, SPI_WREN);
			अगर (retval != STATUS_SUCCESS) अणु
				kमुक्त(buf);
				वापस STATUS_FAIL;
			पूर्ण

			rtsx_stor_access_xfer_buf(buf, 1, srb, &index, &offset,
						  FROM_XFER_BUF);

			rtsx_init_cmd(chip);

			rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE,
				     0x01, PINGPONG_BUFFER);
			rtsx_add_cmd(chip, WRITE_REG_CMD, PPBUF_BASE2, 0xFF,
				     buf[0]);
			sf_program(chip, ins, 1, addr, 1);

			retval = rtsx_send_cmd(chip, 0, 100);
			अगर (retval < 0) अणु
				kमुक्त(buf);
				rtsx_clear_spi_error(chip);
				spi_set_err_code(chip, SPI_HW_ERR);
				वापस STATUS_FAIL;
			पूर्ण

			retval = sf_polling_status(chip, 100);
			अगर (retval != STATUS_SUCCESS) अणु
				kमुक्त(buf);
				वापस STATUS_FAIL;
			पूर्ण

			addr++;
			len--;
		पूर्ण

		kमुक्त(buf);

	पूर्ण अन्यथा अगर (program_mode == AAI_PROGRAM) अणु
		पूर्णांक first_byte = 1;

		retval = sf_enable_ग_लिखो(chip, SPI_WREN);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		buf = kदो_स्मृति(4, GFP_KERNEL);
		अगर (!buf)
			वापस STATUS_ERROR;

		जबतक (len) अणु
			rtsx_stor_access_xfer_buf(buf, 1, srb, &index, &offset,
						  FROM_XFER_BUF);

			rtsx_init_cmd(chip);

			rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE,
				     0x01, PINGPONG_BUFFER);
			rtsx_add_cmd(chip, WRITE_REG_CMD, PPBUF_BASE2, 0xFF,
				     buf[0]);
			अगर (first_byte) अणु
				sf_program(chip, ins, 1, addr, 1);
				first_byte = 0;
			पूर्ण अन्यथा अणु
				sf_program(chip, ins, 0, 0, 1);
			पूर्ण

			retval = rtsx_send_cmd(chip, 0, 100);
			अगर (retval < 0) अणु
				kमुक्त(buf);
				rtsx_clear_spi_error(chip);
				spi_set_err_code(chip, SPI_HW_ERR);
				वापस STATUS_FAIL;
			पूर्ण

			retval = sf_polling_status(chip, 100);
			अगर (retval != STATUS_SUCCESS) अणु
				kमुक्त(buf);
				वापस STATUS_FAIL;
			पूर्ण

			len--;
		पूर्ण

		kमुक्त(buf);

		retval = sf_disable_ग_लिखो(chip, SPI_WRDI);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		retval = sf_polling_status(chip, 100);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण अन्यथा अगर (program_mode == PAGE_PROGRAM) अणु
		buf = kदो_स्मृति(SF_PAGE_LEN, GFP_KERNEL);
		अगर (!buf)
			वापस STATUS_NOMEM;

		जबतक (len) अणु
			u16 pagelen = SF_PAGE_LEN - (u8)addr;

			अगर (pagelen > len)
				pagelen = len;

			retval = sf_enable_ग_लिखो(chip, SPI_WREN);
			अगर (retval != STATUS_SUCCESS) अणु
				kमुक्त(buf);
				वापस STATUS_FAIL;
			पूर्ण

			rtsx_init_cmd(chip);

			trans_dma_enable(DMA_TO_DEVICE, chip, 256, DMA_256);
			sf_program(chip, ins, 1, addr, pagelen);

			rtsx_send_cmd_no_रुको(chip);

			rtsx_stor_access_xfer_buf(buf, pagelen, srb, &index,
						  &offset, FROM_XFER_BUF);

			retval = rtsx_transfer_data(chip, 0, buf, pagelen, 0,
						    DMA_TO_DEVICE, 100);
			अगर (retval < 0) अणु
				kमुक्त(buf);
				rtsx_clear_spi_error(chip);
				spi_set_err_code(chip, SPI_HW_ERR);
				वापस STATUS_FAIL;
			पूर्ण

			retval = sf_polling_status(chip, 100);
			अगर (retval != STATUS_SUCCESS) अणु
				kमुक्त(buf);
				वापस STATUS_FAIL;
			पूर्ण

			addr += pagelen;
			len -= pagelen;
		पूर्ण

		kमुक्त(buf);
	पूर्ण अन्यथा अणु
		spi_set_err_code(chip, SPI_INVALID_COMMAND);
		वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक spi_erase_flash(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;
	u8 ins, erase_mode;
	u32 addr;

	spi_set_err_code(chip, SPI_NO_ERR);

	ins = srb->cmnd[3];
	addr = ((u32)(srb->cmnd[4]) << 16) | ((u32)(srb->cmnd[5])
					<< 8) | srb->cmnd[6];
	erase_mode = srb->cmnd[9];

	retval = spi_set_init_para(chip);
	अगर (retval != STATUS_SUCCESS) अणु
		spi_set_err_code(chip, SPI_HW_ERR);
		वापस STATUS_FAIL;
	पूर्ण

	अगर (erase_mode == PAGE_ERASE) अणु
		retval = sf_enable_ग_लिखो(chip, SPI_WREN);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		retval = sf_erase(chip, ins, 1, addr);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण अन्यथा अगर (erase_mode == CHIP_ERASE) अणु
		retval = sf_enable_ग_लिखो(chip, SPI_WREN);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;

		retval = sf_erase(chip, ins, 0, 0);
		अगर (retval != STATUS_SUCCESS)
			वापस STATUS_FAIL;
	पूर्ण अन्यथा अणु
		spi_set_err_code(chip, SPI_INVALID_COMMAND);
		वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण

पूर्णांक spi_ग_लिखो_flash_status(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;
	u8 ins, status, ewsr;

	ins = srb->cmnd[3];
	status = srb->cmnd[4];
	ewsr = srb->cmnd[5];

	retval = spi_set_init_para(chip);
	अगर (retval != STATUS_SUCCESS) अणु
		spi_set_err_code(chip, SPI_HW_ERR);
		वापस STATUS_FAIL;
	पूर्ण

	retval = sf_enable_ग_लिखो(chip, ewsr);
	अगर (retval != STATUS_SUCCESS)
		वापस STATUS_FAIL;

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE, 0x01,
		     PINGPONG_BUFFER);

	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_COMMAND, 0xFF, ins);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_CA_NUMBER, 0xFF,
		     SPI_COMMAND_BIT_8 | SPI_ADDRESS_BIT_24);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_LENGTH1, 0xFF, 0);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_LENGTH0, 0xFF, 1);
	rtsx_add_cmd(chip, WRITE_REG_CMD, PPBUF_BASE2, 0xFF, status);
	rtsx_add_cmd(chip, WRITE_REG_CMD, SPI_TRANSFER0, 0xFF,
		     SPI_TRANSFER0_START | SPI_CDO_MODE0);
	rtsx_add_cmd(chip, CHECK_REG_CMD, SPI_TRANSFER0, SPI_TRANSFER0_END,
		     SPI_TRANSFER0_END);

	retval = rtsx_send_cmd(chip, 0, 100);
	अगर (retval != STATUS_SUCCESS) अणु
		rtsx_clear_spi_error(chip);
		spi_set_err_code(chip, SPI_HW_ERR);
		वापस STATUS_FAIL;
	पूर्ण

	वापस STATUS_SUCCESS;
पूर्ण
