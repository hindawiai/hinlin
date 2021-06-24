<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/dt9812.c
 *   COMEDI driver क्रम DataTranslation DT9812 USB module
 *
 * Copyright (C) 2005 Anders Blomdell <anders.blomdell@control.lth.se>
 *
 * COMEDI - Linux Control and Measurement Device Interface
 */

/*
 * Driver: dt9812
 * Description: Data Translation DT9812 USB module
 * Devices: [Data Translation] DT9812 (dt9812)
 * Author: anders.blomdell@control.lth.se (Anders Blomdell)
 * Status: in development
 * Updated: Sun Nov 20 20:18:34 EST 2005
 *
 * This driver works, but bulk transfers not implemented. Might be a
 * starting poपूर्णांक क्रम someone अन्यथा. I found out too late that USB has
 * too high latencies (>1 ms) क्रम my needs.
 */

/*
 * Nota Bene:
 *   1. All ग_लिखोs to command pipe has to be 32 bytes (ISP1181B SHRTP=0 ?)
 *   2. The DDK source (as of sep 2005) is in error regarding the
 *      input MUX bits (example code says P4, but firmware schematics
 *      says P1).
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/uaccess.h>

#समावेश "../comedi_usb.h"

#घोषणा DT9812_DIAGS_BOARD_INFO_ADDR	0xFBFF
#घोषणा DT9812_MAX_WRITE_CMD_PIPE_SIZE	32
#घोषणा DT9812_MAX_READ_CMD_PIPE_SIZE	32

/* usb_bulk_msg() समयout in milliseconds */
#घोषणा DT9812_USB_TIMEOUT		1000

/*
 * See Silican Laboratories C8051F020/1/2/3 manual
 */
#घोषणा F020_SFR_P4			0x84
#घोषणा F020_SFR_P1			0x90
#घोषणा F020_SFR_P2			0xa0
#घोषणा F020_SFR_P3			0xb0
#घोषणा F020_SFR_AMX0CF			0xba
#घोषणा F020_SFR_AMX0SL			0xbb
#घोषणा F020_SFR_ADC0CF			0xbc
#घोषणा F020_SFR_ADC0L			0xbe
#घोषणा F020_SFR_ADC0H			0xbf
#घोषणा F020_SFR_DAC0L			0xd2
#घोषणा F020_SFR_DAC0H			0xd3
#घोषणा F020_SFR_DAC0CN			0xd4
#घोषणा F020_SFR_DAC1L			0xd5
#घोषणा F020_SFR_DAC1H			0xd6
#घोषणा F020_SFR_DAC1CN			0xd7
#घोषणा F020_SFR_ADC0CN			0xe8

#घोषणा F020_MASK_ADC0CF_AMP0GN0	0x01
#घोषणा F020_MASK_ADC0CF_AMP0GN1	0x02
#घोषणा F020_MASK_ADC0CF_AMP0GN2	0x04

#घोषणा F020_MASK_ADC0CN_AD0EN		0x80
#घोषणा F020_MASK_ADC0CN_AD0INT		0x20
#घोषणा F020_MASK_ADC0CN_AD0BUSY	0x10

#घोषणा F020_MASK_DACXCN_DACXEN		0x80

क्रमागत अणु
					/* A/D  D/A  DI  DO  CT */
	DT9812_DEVID_DT9812_10,		/*  8    2   8   8   1  +/- 10V */
	DT9812_DEVID_DT9812_2PT5,	/*  8    2   8   8   1  0-2.44V */
पूर्ण;

क्रमागत dt9812_gain अणु
	DT9812_GAIN_0PT25 = 1,
	DT9812_GAIN_0PT5 = 2,
	DT9812_GAIN_1 = 4,
	DT9812_GAIN_2 = 8,
	DT9812_GAIN_4 = 16,
	DT9812_GAIN_8 = 32,
	DT9812_GAIN_16 = 64,
पूर्ण;

क्रमागत अणु
	DT9812_LEAST_USB_FIRMWARE_CMD_CODE = 0,
	/* Write Flash memory */
	DT9812_W_FLASH_DATA = 0,
	/* Read Flash memory misc config info */
	DT9812_R_FLASH_DATA = 1,

	/*
	 * Register पढ़ो/ग_लिखो commands क्रम processor
	 */

	/* Read a single byte of USB memory */
	DT9812_R_SINGLE_BYTE_REG = 2,
	/* Write a single byte of USB memory */
	DT9812_W_SINGLE_BYTE_REG = 3,
	/* Multiple Reads of USB memory */
	DT9812_R_MULTI_BYTE_REG = 4,
	/* Multiple Writes of USB memory */
	DT9812_W_MULTI_BYTE_REG = 5,
	/* Read, (AND) with mask, OR value, then ग_लिखो (single) */
	DT9812_RMW_SINGLE_BYTE_REG = 6,
	/* Read, (AND) with mask, OR value, then ग_लिखो (multiple) */
	DT9812_RMW_MULTI_BYTE_REG = 7,

	/*
	 * Register पढ़ो/ग_लिखो commands क्रम SMBus
	 */

	/* Read a single byte of SMBus */
	DT9812_R_SINGLE_BYTE_SMBUS = 8,
	/* Write a single byte of SMBus */
	DT9812_W_SINGLE_BYTE_SMBUS = 9,
	/* Multiple Reads of SMBus */
	DT9812_R_MULTI_BYTE_SMBUS = 10,
	/* Multiple Writes of SMBus */
	DT9812_W_MULTI_BYTE_SMBUS = 11,

	/*
	 * Register पढ़ो/ग_लिखो commands क्रम a device
	 */

	/* Read a single byte of a device */
	DT9812_R_SINGLE_BYTE_DEV = 12,
	/* Write a single byte of a device */
	DT9812_W_SINGLE_BYTE_DEV = 13,
	/* Multiple Reads of a device */
	DT9812_R_MULTI_BYTE_DEV = 14,
	/* Multiple Writes of a device */
	DT9812_W_MULTI_BYTE_DEV = 15,

	/* Not sure अगर we'll need this */
	DT9812_W_DAC_THRESHOLD = 16,

	/* Set पूर्णांकerrupt on change mask */
	DT9812_W_INT_ON_CHANGE_MASK = 17,

	/* Write (or Clear) the CGL क्रम the ADC */
	DT9812_W_CGL = 18,
	/* Multiple Reads of USB memory */
	DT9812_R_MULTI_BYTE_USBMEM = 19,
	/* Multiple Writes to USB memory */
	DT9812_W_MULTI_BYTE_USBMEM = 20,

	/* Issue a start command to a given subप्रणाली */
	DT9812_START_SUBSYSTEM = 21,
	/* Issue a stop command to a given subप्रणाली */
	DT9812_STOP_SUBSYSTEM = 22,

	/* calibrate the board using CAL_POT_CMD */
	DT9812_CALIBRATE_POT = 23,
	/* set the DAC FIFO size */
	DT9812_W_DAC_FIFO_SIZE = 24,
	/* Write or Clear the CGL क्रम the DAC */
	DT9812_W_CGL_DAC = 25,
	/* Read a single value from a subप्रणाली */
	DT9812_R_SINGLE_VALUE_CMD = 26,
	/* Write a single value to a subप्रणाली */
	DT9812_W_SINGLE_VALUE_CMD = 27,
	/* Valid DT9812_USB_FIRMWARE_CMD_CODE's will be less than this number */
	DT9812_MAX_USB_FIRMWARE_CMD_CODE,
पूर्ण;

काष्ठा dt9812_flash_data अणु
	__le16 numbytes;
	__le16 address;
पूर्ण;

#घोषणा DT9812_MAX_NUM_MULTI_BYTE_RDS  \
	((DT9812_MAX_WRITE_CMD_PIPE_SIZE - 4 - 1) / माप(u8))

काष्ठा dt9812_पढ़ो_multi अणु
	u8 count;
	u8 address[DT9812_MAX_NUM_MULTI_BYTE_RDS];
पूर्ण;

काष्ठा dt9812_ग_लिखो_byte अणु
	u8 address;
	u8 value;
पूर्ण;

#घोषणा DT9812_MAX_NUM_MULTI_BYTE_WRTS  \
	((DT9812_MAX_WRITE_CMD_PIPE_SIZE - 4 - 1) / \
	 माप(काष्ठा dt9812_ग_लिखो_byte))

काष्ठा dt9812_ग_लिखो_multi अणु
	u8 count;
	काष्ठा dt9812_ग_लिखो_byte ग_लिखो[DT9812_MAX_NUM_MULTI_BYTE_WRTS];
पूर्ण;

काष्ठा dt9812_rmw_byte अणु
	u8 address;
	u8 and_mask;
	u8 or_value;
पूर्ण;

#घोषणा DT9812_MAX_NUM_MULTI_BYTE_RMWS  \
	((DT9812_MAX_WRITE_CMD_PIPE_SIZE - 4 - 1) / \
	 माप(काष्ठा dt9812_rmw_byte))

काष्ठा dt9812_rmw_multi अणु
	u8 count;
	काष्ठा dt9812_rmw_byte rmw[DT9812_MAX_NUM_MULTI_BYTE_RMWS];
पूर्ण;

काष्ठा dt9812_usb_cmd अणु
	__le32 cmd;
	जोड़ अणु
		काष्ठा dt9812_flash_data flash_data_info;
		काष्ठा dt9812_पढ़ो_multi पढ़ो_multi_info;
		काष्ठा dt9812_ग_लिखो_multi ग_लिखो_multi_info;
		काष्ठा dt9812_rmw_multi rmw_multi_info;
	पूर्ण u;
पूर्ण;

काष्ठा dt9812_निजी अणु
	काष्ठा mutex mut;
	काष्ठा अणु
		__u8 addr;
		माप_प्रकार size;
	पूर्ण cmd_wr, cmd_rd;
	u16 device;
पूर्ण;

अटल पूर्णांक dt9812_पढ़ो_info(काष्ठा comedi_device *dev,
			    पूर्णांक offset, व्योम *buf, माप_प्रकार buf_size)
अणु
	काष्ठा usb_device *usb = comedi_to_usb_dev(dev);
	काष्ठा dt9812_निजी *devpriv = dev->निजी;
	काष्ठा dt9812_usb_cmd cmd;
	पूर्णांक count, ret;

	cmd.cmd = cpu_to_le32(DT9812_R_FLASH_DATA);
	cmd.u.flash_data_info.address =
	    cpu_to_le16(DT9812_DIAGS_BOARD_INFO_ADDR + offset);
	cmd.u.flash_data_info.numbytes = cpu_to_le16(buf_size);

	/* DT9812 only responds to 32 byte ग_लिखोs!! */
	ret = usb_bulk_msg(usb, usb_sndbulkpipe(usb, devpriv->cmd_wr.addr),
			   &cmd, 32, &count, DT9812_USB_TIMEOUT);
	अगर (ret)
		वापस ret;

	वापस usb_bulk_msg(usb, usb_rcvbulkpipe(usb, devpriv->cmd_rd.addr),
			    buf, buf_size, &count, DT9812_USB_TIMEOUT);
पूर्ण

अटल पूर्णांक dt9812_पढ़ो_multiple_रेजिस्टरs(काष्ठा comedi_device *dev,
					  पूर्णांक reg_count, u8 *address,
					  u8 *value)
अणु
	काष्ठा usb_device *usb = comedi_to_usb_dev(dev);
	काष्ठा dt9812_निजी *devpriv = dev->निजी;
	काष्ठा dt9812_usb_cmd cmd;
	पूर्णांक i, count, ret;

	cmd.cmd = cpu_to_le32(DT9812_R_MULTI_BYTE_REG);
	cmd.u.पढ़ो_multi_info.count = reg_count;
	क्रम (i = 0; i < reg_count; i++)
		cmd.u.पढ़ो_multi_info.address[i] = address[i];

	/* DT9812 only responds to 32 byte ग_लिखोs!! */
	ret = usb_bulk_msg(usb, usb_sndbulkpipe(usb, devpriv->cmd_wr.addr),
			   &cmd, 32, &count, DT9812_USB_TIMEOUT);
	अगर (ret)
		वापस ret;

	वापस usb_bulk_msg(usb, usb_rcvbulkpipe(usb, devpriv->cmd_rd.addr),
			    value, reg_count, &count, DT9812_USB_TIMEOUT);
पूर्ण

अटल पूर्णांक dt9812_ग_लिखो_multiple_रेजिस्टरs(काष्ठा comedi_device *dev,
					   पूर्णांक reg_count, u8 *address,
					   u8 *value)
अणु
	काष्ठा usb_device *usb = comedi_to_usb_dev(dev);
	काष्ठा dt9812_निजी *devpriv = dev->निजी;
	काष्ठा dt9812_usb_cmd cmd;
	पूर्णांक i, count;

	cmd.cmd = cpu_to_le32(DT9812_W_MULTI_BYTE_REG);
	cmd.u.पढ़ो_multi_info.count = reg_count;
	क्रम (i = 0; i < reg_count; i++) अणु
		cmd.u.ग_लिखो_multi_info.ग_लिखो[i].address = address[i];
		cmd.u.ग_लिखो_multi_info.ग_लिखो[i].value = value[i];
	पूर्ण

	/* DT9812 only responds to 32 byte ग_लिखोs!! */
	वापस usb_bulk_msg(usb, usb_sndbulkpipe(usb, devpriv->cmd_wr.addr),
			    &cmd, 32, &count, DT9812_USB_TIMEOUT);
पूर्ण

अटल पूर्णांक dt9812_rmw_multiple_रेजिस्टरs(काष्ठा comedi_device *dev,
					 पूर्णांक reg_count,
					 काष्ठा dt9812_rmw_byte *rmw)
अणु
	काष्ठा usb_device *usb = comedi_to_usb_dev(dev);
	काष्ठा dt9812_निजी *devpriv = dev->निजी;
	काष्ठा dt9812_usb_cmd cmd;
	पूर्णांक i, count;

	cmd.cmd = cpu_to_le32(DT9812_RMW_MULTI_BYTE_REG);
	cmd.u.rmw_multi_info.count = reg_count;
	क्रम (i = 0; i < reg_count; i++)
		cmd.u.rmw_multi_info.rmw[i] = rmw[i];

	/* DT9812 only responds to 32 byte ग_लिखोs!! */
	वापस usb_bulk_msg(usb, usb_sndbulkpipe(usb, devpriv->cmd_wr.addr),
			    &cmd, 32, &count, DT9812_USB_TIMEOUT);
पूर्ण

अटल पूर्णांक dt9812_digital_in(काष्ठा comedi_device *dev, u8 *bits)
अणु
	काष्ठा dt9812_निजी *devpriv = dev->निजी;
	u8 reg[2] = अणु F020_SFR_P3, F020_SFR_P1 पूर्ण;
	u8 value[2];
	पूर्णांक ret;

	mutex_lock(&devpriv->mut);
	ret = dt9812_पढ़ो_multiple_रेजिस्टरs(dev, 2, reg, value);
	अगर (ret == 0) अणु
		/*
		 * bits 0-6 in F020_SFR_P3 are bits 0-6 in the digital
		 * input port bit 3 in F020_SFR_P1 is bit 7 in the
		 * digital input port
		 */
		*bits = (value[0] & 0x7f) | ((value[1] & 0x08) << 4);
	पूर्ण
	mutex_unlock(&devpriv->mut);

	वापस ret;
पूर्ण

अटल पूर्णांक dt9812_digital_out(काष्ठा comedi_device *dev, u8 bits)
अणु
	काष्ठा dt9812_निजी *devpriv = dev->निजी;
	u8 reg[1] = अणु F020_SFR_P2 पूर्ण;
	u8 value[1] = अणु bits पूर्ण;
	पूर्णांक ret;

	mutex_lock(&devpriv->mut);
	ret = dt9812_ग_लिखो_multiple_रेजिस्टरs(dev, 1, reg, value);
	mutex_unlock(&devpriv->mut);

	वापस ret;
पूर्ण

अटल व्योम dt9812_configure_mux(काष्ठा comedi_device *dev,
				 काष्ठा dt9812_rmw_byte *rmw, पूर्णांक channel)
अणु
	काष्ठा dt9812_निजी *devpriv = dev->निजी;

	अगर (devpriv->device == DT9812_DEVID_DT9812_10) अणु
		/* In the DT9812/10V MUX is selected by P1.5-7 */
		rmw->address = F020_SFR_P1;
		rmw->and_mask = 0xe0;
		rmw->or_value = channel << 5;
	पूर्ण अन्यथा अणु
		/* In the DT9812/2.5V, पूर्णांकernal mux is selected by bits 0:2 */
		rmw->address = F020_SFR_AMX0SL;
		rmw->and_mask = 0xff;
		rmw->or_value = channel & 0x07;
	पूर्ण
पूर्ण

अटल व्योम dt9812_configure_gain(काष्ठा comedi_device *dev,
				  काष्ठा dt9812_rmw_byte *rmw,
				  क्रमागत dt9812_gain gain)
अणु
	काष्ठा dt9812_निजी *devpriv = dev->निजी;

	/* In the DT9812/10V, there is an बाह्यal gain of 0.5 */
	अगर (devpriv->device == DT9812_DEVID_DT9812_10)
		gain <<= 1;

	rmw->address = F020_SFR_ADC0CF;
	rmw->and_mask = F020_MASK_ADC0CF_AMP0GN2 |
			F020_MASK_ADC0CF_AMP0GN1 |
			F020_MASK_ADC0CF_AMP0GN0;

	चयन (gain) अणु
		/*
		 * 000 -> Gain =  1
		 * 001 -> Gain =  2
		 * 010 -> Gain =  4
		 * 011 -> Gain =  8
		 * 10x -> Gain = 16
		 * 11x -> Gain =  0.5
		 */
	हाल DT9812_GAIN_0PT5:
		rmw->or_value = F020_MASK_ADC0CF_AMP0GN2 |
				F020_MASK_ADC0CF_AMP0GN1;
		अवरोध;
	शेष:
		/* this should never happen, just use a gain of 1 */
	हाल DT9812_GAIN_1:
		rmw->or_value = 0x00;
		अवरोध;
	हाल DT9812_GAIN_2:
		rmw->or_value = F020_MASK_ADC0CF_AMP0GN0;
		अवरोध;
	हाल DT9812_GAIN_4:
		rmw->or_value = F020_MASK_ADC0CF_AMP0GN1;
		अवरोध;
	हाल DT9812_GAIN_8:
		rmw->or_value = F020_MASK_ADC0CF_AMP0GN1 |
				F020_MASK_ADC0CF_AMP0GN0;
		अवरोध;
	हाल DT9812_GAIN_16:
		rmw->or_value = F020_MASK_ADC0CF_AMP0GN2;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक dt9812_analog_in(काष्ठा comedi_device *dev,
			    पूर्णांक channel, u16 *value, क्रमागत dt9812_gain gain)
अणु
	काष्ठा dt9812_निजी *devpriv = dev->निजी;
	काष्ठा dt9812_rmw_byte rmw[3];
	u8 reg[3] = अणु
		F020_SFR_ADC0CN,
		F020_SFR_ADC0H,
		F020_SFR_ADC0L
	पूर्ण;
	u8 val[3];
	पूर्णांक ret;

	mutex_lock(&devpriv->mut);

	/* 1 select the gain */
	dt9812_configure_gain(dev, &rmw[0], gain);

	/* 2 set the MUX to select the channel */
	dt9812_configure_mux(dev, &rmw[1], channel);

	/* 3 start conversion */
	rmw[2].address = F020_SFR_ADC0CN;
	rmw[2].and_mask = 0xff;
	rmw[2].or_value = F020_MASK_ADC0CN_AD0EN | F020_MASK_ADC0CN_AD0BUSY;

	ret = dt9812_rmw_multiple_रेजिस्टरs(dev, 3, rmw);
	अगर (ret)
		जाओ निकास;

	/* पढ़ो the status and ADC */
	ret = dt9812_पढ़ो_multiple_रेजिस्टरs(dev, 3, reg, val);
	अगर (ret)
		जाओ निकास;

	/*
	 * An ADC conversion takes 16 SAR घड़ीs cycles, i.e. about 9us.
	 * Thereक्रमe, between the instant that AD0BUSY was set via
	 * dt9812_rmw_multiple_रेजिस्टरs and the पढ़ो of AD0BUSY via
	 * dt9812_पढ़ो_multiple_रेजिस्टरs, the conversion should be complete
	 * since these two operations require two USB transactions each taking
	 * at least a millisecond to complete.  However, lets make sure that
	 * conversion is finished.
	 */
	अगर ((val[0] & (F020_MASK_ADC0CN_AD0INT | F020_MASK_ADC0CN_AD0BUSY)) ==
	    F020_MASK_ADC0CN_AD0INT) अणु
		चयन (devpriv->device) अणु
		हाल DT9812_DEVID_DT9812_10:
			/*
			 * For DT9812-10V the personality module set the
			 * encoding to 2's complement. Hence, convert it beक्रमe
			 * वापसing it
			 */
			*value = ((val[1] << 8) | val[2]) + 0x800;
			अवरोध;
		हाल DT9812_DEVID_DT9812_2PT5:
			*value = (val[1] << 8) | val[2];
			अवरोध;
		पूर्ण
	पूर्ण

निकास:
	mutex_unlock(&devpriv->mut);

	वापस ret;
पूर्ण

अटल पूर्णांक dt9812_analog_out(काष्ठा comedi_device *dev, पूर्णांक channel, u16 value)
अणु
	काष्ठा dt9812_निजी *devpriv = dev->निजी;
	काष्ठा dt9812_rmw_byte rmw[3];
	पूर्णांक ret;

	mutex_lock(&devpriv->mut);

	चयन (channel) अणु
	हाल 0:
		/* 1. Set DAC mode */
		rmw[0].address = F020_SFR_DAC0CN;
		rmw[0].and_mask = 0xff;
		rmw[0].or_value = F020_MASK_DACXCN_DACXEN;

		/* 2. load lsb of DAC value first */
		rmw[1].address = F020_SFR_DAC0L;
		rmw[1].and_mask = 0xff;
		rmw[1].or_value = value & 0xff;

		/* 3. load msb of DAC value next to latch the 12-bit value */
		rmw[2].address = F020_SFR_DAC0H;
		rmw[2].and_mask = 0xff;
		rmw[2].or_value = (value >> 8) & 0xf;
		अवरोध;

	हाल 1:
		/* 1. Set DAC mode */
		rmw[0].address = F020_SFR_DAC1CN;
		rmw[0].and_mask = 0xff;
		rmw[0].or_value = F020_MASK_DACXCN_DACXEN;

		/* 2. load lsb of DAC value first */
		rmw[1].address = F020_SFR_DAC1L;
		rmw[1].and_mask = 0xff;
		rmw[1].or_value = value & 0xff;

		/* 3. load msb of DAC value next to latch the 12-bit value */
		rmw[2].address = F020_SFR_DAC1H;
		rmw[2].and_mask = 0xff;
		rmw[2].or_value = (value >> 8) & 0xf;
		अवरोध;
	पूर्ण
	ret = dt9812_rmw_multiple_रेजिस्टरs(dev, 3, rmw);

	mutex_unlock(&devpriv->mut);

	वापस ret;
पूर्ण

अटल पूर्णांक dt9812_di_insn_bits(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	u8 bits = 0;
	पूर्णांक ret;

	ret = dt9812_digital_in(dev, &bits);
	अगर (ret)
		वापस ret;

	data[1] = bits;

	वापस insn->n;
पूर्ण

अटल पूर्णांक dt9812_करो_insn_bits(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	अगर (comedi_dio_update_state(s, data))
		dt9812_digital_out(dev, s->state);

	data[1] = s->state;

	वापस insn->n;
पूर्ण

अटल पूर्णांक dt9812_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	u16 val = 0;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		ret = dt9812_analog_in(dev, chan, &val, DT9812_GAIN_1);
		अगर (ret)
			वापस ret;
		data[i] = val;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक dt9812_ao_insn_पढ़ो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn,
			       अचिन्हित पूर्णांक *data)
अणु
	काष्ठा dt9812_निजी *devpriv = dev->निजी;
	पूर्णांक ret;

	mutex_lock(&devpriv->mut);
	ret = comedi_पढ़ोback_insn_पढ़ो(dev, s, insn, data);
	mutex_unlock(&devpriv->mut);

	वापस ret;
पूर्ण

अटल पूर्णांक dt9812_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		अचिन्हित पूर्णांक val = data[i];
		पूर्णांक ret;

		ret = dt9812_analog_out(dev, chan, val);
		अगर (ret)
			वापस ret;

		s->पढ़ोback[chan] = val;
	पूर्ण

	वापस insn->n;
पूर्ण

अटल पूर्णांक dt9812_find_endpoपूर्णांकs(काष्ठा comedi_device *dev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = comedi_to_usb_पूर्णांकerface(dev);
	काष्ठा usb_host_पूर्णांकerface *host = पूर्णांकf->cur_altsetting;
	काष्ठा dt9812_निजी *devpriv = dev->निजी;
	काष्ठा usb_endpoपूर्णांक_descriptor *ep;
	पूर्णांक i;

	अगर (host->desc.bNumEndpoपूर्णांकs != 5) अणु
		dev_err(dev->class_dev, "Wrong number of endpoints\n");
		वापस -ENODEV;
	पूर्ण

	क्रम (i = 0; i < host->desc.bNumEndpoपूर्णांकs; ++i) अणु
		पूर्णांक dir = -1;

		ep = &host->endpoपूर्णांक[i].desc;
		चयन (i) अणु
		हाल 0:
			/* unused message pipe */
			dir = USB_सूची_IN;
			अवरोध;
		हाल 1:
			dir = USB_सूची_OUT;
			devpriv->cmd_wr.addr = ep->bEndpoपूर्णांकAddress;
			devpriv->cmd_wr.size = usb_endpoपूर्णांक_maxp(ep);
			अवरोध;
		हाल 2:
			dir = USB_सूची_IN;
			devpriv->cmd_rd.addr = ep->bEndpoपूर्णांकAddress;
			devpriv->cmd_rd.size = usb_endpoपूर्णांक_maxp(ep);
			अवरोध;
		हाल 3:
			/* unused ग_लिखो stream */
			dir = USB_सूची_OUT;
			अवरोध;
		हाल 4:
			/* unused पढ़ो stream */
			dir = USB_सूची_IN;
			अवरोध;
		पूर्ण
		अगर ((ep->bEndpoपूर्णांकAddress & USB_सूची_IN) != dir) अणु
			dev_err(dev->class_dev,
				"Endpoint has wrong direction\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dt9812_reset_device(काष्ठा comedi_device *dev)
अणु
	काष्ठा usb_device *usb = comedi_to_usb_dev(dev);
	काष्ठा dt9812_निजी *devpriv = dev->निजी;
	u32 serial;
	u16 venकरोr;
	u16 product;
	u8 पंचांगp8;
	__le16 पंचांगp16;
	__le32 पंचांगp32;
	पूर्णांक ret;
	पूर्णांक i;

	ret = dt9812_पढ़ो_info(dev, 0, &पंचांगp8, माप(पंचांगp8));
	अगर (ret) अणु
		/*
		 * Seems like a configuration reset is necessary अगर driver is
		 * reloaded जबतक device is attached
		 */
		usb_reset_configuration(usb);
		क्रम (i = 0; i < 10; i++) अणु
			ret = dt9812_पढ़ो_info(dev, 1, &पंचांगp8, माप(पंचांगp8));
			अगर (ret == 0)
				अवरोध;
		पूर्ण
		अगर (ret) अणु
			dev_err(dev->class_dev,
				"unable to reset configuration\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = dt9812_पढ़ो_info(dev, 1, &पंचांगp16, माप(पंचांगp16));
	अगर (ret) अणु
		dev_err(dev->class_dev, "failed to read vendor id\n");
		वापस ret;
	पूर्ण
	venकरोr = le16_to_cpu(पंचांगp16);

	ret = dt9812_पढ़ो_info(dev, 3, &पंचांगp16, माप(पंचांगp16));
	अगर (ret) अणु
		dev_err(dev->class_dev, "failed to read product id\n");
		वापस ret;
	पूर्ण
	product = le16_to_cpu(पंचांगp16);

	ret = dt9812_पढ़ो_info(dev, 5, &पंचांगp16, माप(पंचांगp16));
	अगर (ret) अणु
		dev_err(dev->class_dev, "failed to read device id\n");
		वापस ret;
	पूर्ण
	devpriv->device = le16_to_cpu(पंचांगp16);

	ret = dt9812_पढ़ो_info(dev, 7, &पंचांगp32, माप(पंचांगp32));
	अगर (ret) अणु
		dev_err(dev->class_dev, "failed to read serial number\n");
		वापस ret;
	पूर्ण
	serial = le32_to_cpu(पंचांगp32);

	/* let the user know what node this device is now attached to */
	dev_info(dev->class_dev, "USB DT9812 (%4.4x.%4.4x.%4.4x) #0x%8.8x\n",
		 venकरोr, product, devpriv->device, serial);

	अगर (devpriv->device != DT9812_DEVID_DT9812_10 &&
	    devpriv->device != DT9812_DEVID_DT9812_2PT5) अणु
		dev_err(dev->class_dev, "Unsupported device!\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dt9812_स्वतः_attach(काष्ठा comedi_device *dev,
			      अचिन्हित दीर्घ context)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = comedi_to_usb_पूर्णांकerface(dev);
	काष्ठा dt9812_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	bool is_unipolar;
	पूर्णांक ret;
	पूर्णांक i;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	mutex_init(&devpriv->mut);
	usb_set_पूर्णांकfdata(पूर्णांकf, devpriv);

	ret = dt9812_find_endpoपूर्णांकs(dev);
	अगर (ret)
		वापस ret;

	ret = dt9812_reset_device(dev);
	अगर (ret)
		वापस ret;

	is_unipolar = (devpriv->device == DT9812_DEVID_DT9812_2PT5);

	ret = comedi_alloc_subdevices(dev, 4);
	अगर (ret)
		वापस ret;

	/* Digital Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_flags	= SDF_READABLE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= dt9812_di_insn_bits;

	/* Digital Output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->range_table	= &range_digital;
	s->insn_bits	= dt9812_करो_insn_bits;

	/* Analog Input subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_flags	= SDF_READABLE | SDF_GROUND;
	s->n_chan	= 8;
	s->maxdata	= 0x0fff;
	s->range_table	= is_unipolar ? &range_unipolar2_5 : &range_bipolar10;
	s->insn_पढ़ो	= dt9812_ai_insn_पढ़ो;

	/* Analog Output subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 2;
	s->maxdata	= 0x0fff;
	s->range_table	= is_unipolar ? &range_unipolar2_5 : &range_bipolar10;
	s->insn_ग_लिखो	= dt9812_ao_insn_ग_लिखो;
	s->insn_पढ़ो	= dt9812_ao_insn_पढ़ो;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < s->n_chan; i++)
		s->पढ़ोback[i] = is_unipolar ? 0x0000 : 0x0800;

	वापस 0;
पूर्ण

अटल व्योम dt9812_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = comedi_to_usb_पूर्णांकerface(dev);
	काष्ठा dt9812_निजी *devpriv = dev->निजी;

	अगर (!devpriv)
		वापस;

	mutex_destroy(&devpriv->mut);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
पूर्ण

अटल काष्ठा comedi_driver dt9812_driver = अणु
	.driver_name	= "dt9812",
	.module		= THIS_MODULE,
	.स्वतः_attach	= dt9812_स्वतः_attach,
	.detach		= dt9812_detach,
पूर्ण;

अटल पूर्णांक dt9812_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			    स्थिर काष्ठा usb_device_id *id)
अणु
	वापस comedi_usb_स्वतः_config(पूर्णांकf, &dt9812_driver, id->driver_info);
पूर्ण

अटल स्थिर काष्ठा usb_device_id dt9812_usb_table[] = अणु
	अणु USB_DEVICE(0x0867, 0x9812) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, dt9812_usb_table);

अटल काष्ठा usb_driver dt9812_usb_driver = अणु
	.name		= "dt9812",
	.id_table	= dt9812_usb_table,
	.probe		= dt9812_usb_probe,
	.disconnect	= comedi_usb_स्वतः_unconfig,
पूर्ण;
module_comedi_usb_driver(dt9812_driver, dt9812_usb_driver);

MODULE_AUTHOR("Anders Blomdell <anders.blomdell@control.lth.se>");
MODULE_DESCRIPTION("Comedi DT9812 driver");
MODULE_LICENSE("GPL");
