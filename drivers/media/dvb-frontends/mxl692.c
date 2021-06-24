<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम the MaxLinear MxL69x family of combo tuners/demods
 *
 * Copyright (C) 2020 Brad Love <brad@nextdimension.cc>
 *
 * based on code:
 * Copyright (c) 2016 MaxLinear, Inc. All rights reserved
 * which was released under GPL V2
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/mutex.h>
#समावेश <linux/i2c-mux.h>
#समावेश <linux/माला.स>
#समावेश <linux/firmware.h>

#समावेश "mxl692.h"
#समावेश "mxl692_defs.h"

अटल स्थिर काष्ठा dvb_frontend_ops mxl692_ops;

काष्ठा mxl692_dev अणु
	काष्ठा dvb_frontend fe;
	काष्ठा i2c_client *i2c_client;
	काष्ठा mutex i2c_lock;		/* i2c command mutex */
	क्रमागत MXL_EAGLE_DEMOD_TYPE_E demod_type;
	क्रमागत MXL_EAGLE_POWER_MODE_E घातer_mode;
	u32 current_frequency;
	पूर्णांक device_type;
	पूर्णांक seqnum;
	पूर्णांक init_करोne;
पूर्ण;

अटल पूर्णांक mxl692_i2c_ग_लिखो(काष्ठा mxl692_dev *dev, u8 *buffer, u16 buf_len)
अणु
	पूर्णांक ret = 0;
	काष्ठा i2c_msg msg = अणु
		.addr = dev->i2c_client->addr,
		.flags = 0,
		.buf = buffer,
		.len = buf_len
	पूर्ण;

	ret = i2c_transfer(dev->i2c_client->adapter, &msg, 1);
	अगर (ret != 1)
		dev_dbg(&dev->i2c_client->dev, "i2c write error!\n");

	वापस ret;
पूर्ण

अटल पूर्णांक mxl692_i2c_पढ़ो(काष्ठा mxl692_dev *dev, u8 *buffer, u16 buf_len)
अणु
	पूर्णांक ret = 0;
	काष्ठा i2c_msg msg = अणु
		.addr = dev->i2c_client->addr,
		.flags = I2C_M_RD,
		.buf = buffer,
		.len = buf_len
	पूर्ण;

	ret = i2c_transfer(dev->i2c_client->adapter, &msg, 1);
	अगर (ret != 1)
		dev_dbg(&dev->i2c_client->dev, "i2c read error!\n");

	वापस ret;
पूर्ण

अटल पूर्णांक convert_endian(u32 size, u8 *d)
अणु
	u32 i;

	क्रम (i = 0; i < (size & ~3); i += 4) अणु
		d[i + 0] ^= d[i + 3];
		d[i + 3] ^= d[i + 0];
		d[i + 0] ^= d[i + 3];

		d[i + 1] ^= d[i + 2];
		d[i + 2] ^= d[i + 1];
		d[i + 1] ^= d[i + 2];
	पूर्ण

	चयन (size & 3) अणु
	हाल 0:
	हाल 1:
		/* करो nothing */
		अवरोध;
	हाल 2:
		d[i + 0] ^= d[i + 1];
		d[i + 1] ^= d[i + 0];
		d[i + 0] ^= d[i + 1];
		अवरोध;

	हाल 3:
		d[i + 0] ^= d[i + 2];
		d[i + 2] ^= d[i + 0];
		d[i + 0] ^= d[i + 2];
		अवरोध;
	पूर्ण
	वापस size;
पूर्ण

अटल पूर्णांक convert_endian_n(पूर्णांक n, u32 size, u8 *d)
अणु
	पूर्णांक i, count = 0;

	क्रम (i = 0; i < n; i += size)
		count += convert_endian(size, d + i);
	वापस count;
पूर्ण

अटल व्योम mxl692_tx_swap(क्रमागत MXL_EAGLE_OPCODE_E opcode, u8 *buffer)
अणु
#अगर_घोषित __BIG_ENDIAN
	वापस;
#पूर्ण_अगर
	buffer += MXL_EAGLE_HOST_MSG_HEADER_SIZE; /* skip API header */

	चयन (opcode) अणु
	हाल MXL_EAGLE_OPCODE_DEVICE_INTR_MASK_SET:
	हाल MXL_EAGLE_OPCODE_TUNER_CHANNEL_TUNE_SET:
	हाल MXL_EAGLE_OPCODE_SMA_TRANSMIT_SET:
		buffer += convert_endian(माप(u32), buffer);
		अवरोध;
	हाल MXL_EAGLE_OPCODE_QAM_PARAMS_SET:
		buffer += 5;
		buffer += convert_endian(2 * माप(u32), buffer);
		अवरोध;
	शेष:
		/* no swapping - all get opcodes */
		/* ATSC/OOB no swapping */
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mxl692_rx_swap(क्रमागत MXL_EAGLE_OPCODE_E opcode, u8 *buffer)
अणु
#अगर_घोषित __BIG_ENDIAN
	वापस;
#पूर्ण_अगर
	buffer += MXL_EAGLE_HOST_MSG_HEADER_SIZE; /* skip API header */

	चयन (opcode) अणु
	हाल MXL_EAGLE_OPCODE_TUNER_AGC_STATUS_GET:
		buffer++;
		buffer += convert_endian(2 * माप(u16), buffer);
		अवरोध;
	हाल MXL_EAGLE_OPCODE_ATSC_STATUS_GET:
		buffer += convert_endian_n(2, माप(u16), buffer);
		buffer += convert_endian(माप(u32), buffer);
		अवरोध;
	हाल MXL_EAGLE_OPCODE_ATSC_ERROR_COUNTERS_GET:
		buffer += convert_endian(3 * माप(u32), buffer);
		अवरोध;
	हाल MXL_EAGLE_OPCODE_ATSC_EQUALIZER_FILTER_FFE_TAPS_GET:
		buffer += convert_endian_n(24, माप(u16), buffer);
		अवरोध;
	हाल MXL_EAGLE_OPCODE_QAM_STATUS_GET:
		buffer += 8;
		buffer += convert_endian_n(2, माप(u16), buffer);
		buffer += convert_endian(माप(u32), buffer);
		अवरोध;
	हाल MXL_EAGLE_OPCODE_QAM_ERROR_COUNTERS_GET:
		buffer += convert_endian(7 * माप(u32), buffer);
		अवरोध;
	हाल MXL_EAGLE_OPCODE_QAM_CONSTELLATION_VALUE_GET:
	हाल MXL_EAGLE_OPCODE_QAM_EQUALIZER_FILTER_DFE_START_GET:
	हाल MXL_EAGLE_OPCODE_QAM_EQUALIZER_FILTER_DFE_MIDDLE_GET:
	हाल MXL_EAGLE_OPCODE_QAM_EQUALIZER_FILTER_DFE_END_GET:
	हाल MXL_EAGLE_OPCODE_QAM_EQUALIZER_FILTER_SPUR_START_GET:
		buffer += convert_endian_n(24, माप(u16), buffer);
		अवरोध;
	हाल MXL_EAGLE_OPCODE_QAM_EQUALIZER_FILTER_SPUR_END_GET:
		buffer += convert_endian_n(8, माप(u16), buffer);
		अवरोध;
	हाल MXL_EAGLE_OPCODE_QAM_EQUALIZER_FILTER_FFE_GET:
		buffer += convert_endian_n(17, माप(u16), buffer);
		अवरोध;
	हाल MXL_EAGLE_OPCODE_OOB_ERROR_COUNTERS_GET:
		buffer += convert_endian(3 * माप(u32), buffer);
		अवरोध;
	हाल MXL_EAGLE_OPCODE_OOB_STATUS_GET:
		buffer += convert_endian_n(2, माप(u16), buffer);
		buffer += convert_endian(माप(u32), buffer);
		अवरोध;
	हाल MXL_EAGLE_OPCODE_SMA_RECEIVE_GET:
		buffer += convert_endian(माप(u32), buffer);
		अवरोध;
	शेष:
		/* no swapping - all set opcodes */
		अवरोध;
	पूर्ण
पूर्ण

अटल u32 mxl692_checksum(u8 *buffer, u32 size)
अणु
	u32 ix, भाग_size;
	u32 cur_cksum = 0;
	__be32 *buf;

	भाग_size = DIV_ROUND_UP(size, 4);

	buf = (__be32 *)buffer;
	क्रम (ix = 0; ix < भाग_size; ix++)
		cur_cksum += be32_to_cpu(buf[ix]);

	cur_cksum ^= 0xDEADBEEF;

	वापस cur_cksum;
पूर्ण

अटल पूर्णांक mxl692_validate_fw_header(काष्ठा mxl692_dev *dev,
				     स्थिर u8 *buffer, u32 buf_len)
अणु
	पूर्णांक status = 0;
	u32 ix, temp;
	__be32 *local_buf = शून्य;
	u8 temp_cksum = 0;
	स्थिर u8 fw_hdr[] = अणु 0x4D, 0x31, 0x10, 0x02, 0x40, 0x00, 0x00, 0x80 पूर्ण;

	अगर (स_भेद(buffer, fw_hdr, 8) != 0) अणु
		status = -EINVAL;
		जाओ err_finish;
	पूर्ण

	local_buf = (__be32 *)(buffer + 8);
	temp = be32_to_cpu(*local_buf);

	अगर ((buf_len - 16) != temp >> 8) अणु
		status = -EINVAL;
		जाओ err_finish;
	पूर्ण

	क्रम (ix = 16; ix < buf_len; ix++)
		temp_cksum += buffer[ix];

	अगर (temp_cksum != buffer[11])
		status = -EINVAL;

err_finish:
	अगर (status)
		dev_dbg(&dev->i2c_client->dev, "failed\n");
	वापस status;
पूर्ण

अटल पूर्णांक mxl692_ग_लिखो_fw_block(काष्ठा mxl692_dev *dev, स्थिर u8 *buffer,
				 u32 buf_len, u32 *index)
अणु
	पूर्णांक status = 0;
	u32 ix = 0, total_len = 0, addr = 0, chunk_len = 0, prevchunk_len = 0;
	u8 local_buf[MXL_EAGLE_MAX_I2C_PACKET_SIZE] = अणुपूर्ण, *plocal_buf = शून्य;
	पूर्णांक payload_max = MXL_EAGLE_MAX_I2C_PACKET_SIZE - MXL_EAGLE_I2C_MHEADER_SIZE;

	ix = *index;

	अगर (buffer[ix] == 0x53) अणु
		total_len = buffer[ix + 1] << 16 | buffer[ix + 2] << 8 | buffer[ix + 3];
		total_len = (total_len + 3) & ~3;
		addr      = buffer[ix + 4] << 24 | buffer[ix + 5] << 16 |
			    buffer[ix + 6] << 8 | buffer[ix + 7];
		ix       += MXL_EAGLE_FW_SEGMENT_HEADER_SIZE;

		जबतक ((total_len > 0) && (status == 0)) अणु
			plocal_buf = local_buf;
			chunk_len  = (total_len < payload_max) ? total_len : payload_max;

			*plocal_buf++ = 0xFC;
			*plocal_buf++ = chunk_len + माप(u32);

			*(u32 *)plocal_buf = addr + prevchunk_len;
#अगर_घोषित __BIG_ENDIAN
			convert_endian(माप(u32), plocal_buf);
#पूर्ण_अगर
			plocal_buf += माप(u32);

			स_नकल(plocal_buf, &buffer[ix], chunk_len);
			convert_endian(chunk_len, plocal_buf);
			अगर (mxl692_i2c_ग_लिखो(dev, local_buf,
					     (chunk_len + MXL_EAGLE_I2C_MHEADER_SIZE)) < 0) अणु
				status = -EREMOTEIO;
				अवरोध;
			पूर्ण

			prevchunk_len += chunk_len;
			total_len -= chunk_len;
			ix += chunk_len;
		पूर्ण
		*index = ix;
	पूर्ण अन्यथा अणु
		status = -EINVAL;
	पूर्ण

	अगर (status)
		dev_dbg(&dev->i2c_client->dev, "err %d\n", status);

	वापस status;
पूर्ण

अटल पूर्णांक mxl692_memग_लिखो(काष्ठा mxl692_dev *dev, u32 addr,
			   u8 *buffer, u32 size)
अणु
	पूर्णांक status = 0, total_len = 0;
	u8 local_buf[MXL_EAGLE_MAX_I2C_PACKET_SIZE] = अणुपूर्ण, *plocal_buf = शून्य;

	total_len = size;
	total_len = (total_len + 3) & ~3;  /* 4 byte alignment */

	अगर (total_len > (MXL_EAGLE_MAX_I2C_PACKET_SIZE - MXL_EAGLE_I2C_MHEADER_SIZE))
		dev_dbg(&dev->i2c_client->dev, "hrmph?\n");

	plocal_buf = local_buf;

	*plocal_buf++ = 0xFC;
	*plocal_buf++ = total_len + माप(u32);

	*(u32 *)plocal_buf = addr;
	plocal_buf += माप(u32);

	स_नकल(plocal_buf, buffer, total_len);
#अगर_घोषित __BIG_ENDIAN
	convert_endian(माप(u32) + total_len, local_buf + 2);
#पूर्ण_अगर
	अगर (mxl692_i2c_ग_लिखो(dev, local_buf,
			     (total_len + MXL_EAGLE_I2C_MHEADER_SIZE)) < 0) अणु
		status = -EREMOTEIO;
		जाओ err_finish;
	पूर्ण

	वापस status;
err_finish:
	dev_dbg(&dev->i2c_client->dev, "err %d\n", status);
	वापस status;
पूर्ण

अटल पूर्णांक mxl692_memपढ़ो(काष्ठा mxl692_dev *dev, u32 addr,
			  u8 *buffer, u32 size)
अणु
	पूर्णांक status = 0;
	u8 local_buf[MXL_EAGLE_I2C_MHEADER_SIZE] = अणुपूर्ण, *plocal_buf = शून्य;

	plocal_buf = local_buf;

	*plocal_buf++ = 0xFB;
	*plocal_buf++ = माप(u32);
	*(u32 *)plocal_buf = addr;
#अगर_घोषित __BIG_ENDIAN
	convert_endian(माप(u32), plocal_buf);
#पूर्ण_अगर
	mutex_lock(&dev->i2c_lock);

	अगर (mxl692_i2c_ग_लिखो(dev, local_buf, MXL_EAGLE_I2C_MHEADER_SIZE) > 0) अणु
		size = (size + 3) & ~3;  /* 4 byte alignment */
		status = mxl692_i2c_पढ़ो(dev, buffer, (u16)size) < 0 ? -EREMOTEIO : 0;
#अगर_घोषित __BIG_ENDIAN
		अगर (status == 0)
			convert_endian(size, buffer);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		status = -EREMOTEIO;
	पूर्ण

	mutex_unlock(&dev->i2c_lock);

	अगर (status)
		dev_dbg(&dev->i2c_client->dev, "err %d\n", status);

	वापस status;
पूर्ण

अटल स्थिर अक्षर *mxl692_opcode_string(u8 opcode)
अणु
	अगर (opcode <= MXL_EAGLE_OPCODE_INTERNAL)
		वापस MXL_EAGLE_OPCODE_STRING[opcode];

	वापस "invalid opcode";
पूर्ण

अटल पूर्णांक mxl692_opग_लिखो(काष्ठा mxl692_dev *dev, u8 *buffer,
			  u32 size)
अणु
	पूर्णांक status = 0, total_len = 0;
	u8 local_buf[MXL_EAGLE_MAX_I2C_PACKET_SIZE] = अणुपूर्ण, *plocal_buf = शून्य;
	काष्ठा MXL_EAGLE_HOST_MSG_HEADER_T *tx_hdr = (काष्ठा MXL_EAGLE_HOST_MSG_HEADER_T *)buffer;

	total_len = size;
	total_len = (total_len + 3) & ~3;  /* 4 byte alignment */

	अगर (total_len > (MXL_EAGLE_MAX_I2C_PACKET_SIZE - MXL_EAGLE_I2C_PHEADER_SIZE))
		dev_dbg(&dev->i2c_client->dev, "hrmph?\n");

	plocal_buf = local_buf;

	*plocal_buf++ = 0xFE;
	*plocal_buf++ = (u8)total_len;

	स_नकल(plocal_buf, buffer, total_len);
	convert_endian(total_len, plocal_buf);

	अगर (mxl692_i2c_ग_लिखो(dev, local_buf,
			     (total_len + MXL_EAGLE_I2C_PHEADER_SIZE)) < 0) अणु
		status = -EREMOTEIO;
		जाओ err_finish;
	पूर्ण
err_finish:
	अगर (status)
		dev_dbg(&dev->i2c_client->dev, "opcode %s  err %d\n",
			mxl692_opcode_string(tx_hdr->opcode), status);
	वापस status;
पूर्ण

अटल पूर्णांक mxl692_opपढ़ो(काष्ठा mxl692_dev *dev, u8 *buffer,
			 u32 size)
अणु
	पूर्णांक status = 0;
	u32 ix = 0;
	u8 local_buf[MXL_EAGLE_I2C_PHEADER_SIZE] = अणुपूर्ण;

	local_buf[0] = 0xFD;
	local_buf[1] = 0;

	अगर (mxl692_i2c_ग_लिखो(dev, local_buf, MXL_EAGLE_I2C_PHEADER_SIZE) > 0) अणु
		size = (size + 3) & ~3;  /* 4 byte alignment */

		/* Read in 4 byte chunks */
		क्रम (ix = 0; ix < size; ix += 4) अणु
			अगर (mxl692_i2c_पढ़ो(dev, buffer + ix, 4) < 0) अणु
				dev_dbg(&dev->i2c_client->dev, "ix=%d   size=%d\n", ix, size);
				status = -EREMOTEIO;
				जाओ err_finish;
			पूर्ण
		पूर्ण
		convert_endian(size, buffer);
	पूर्ण अन्यथा अणु
		status = -EREMOTEIO;
	पूर्ण
err_finish:
	अगर (status)
		dev_dbg(&dev->i2c_client->dev, "err %d\n", status);
	वापस status;
पूर्ण

अटल पूर्णांक mxl692_i2c_ग_लिखोपढ़ो(काष्ठा mxl692_dev *dev,
				u8 opcode,
				u8 *tx_payload,
				u8 tx_payload_size,
				u8 *rx_payload,
				u8 rx_payload_expected)
अणु
	पूर्णांक status = 0, समयout = 40;
	u8 tx_buf[MXL_EAGLE_MAX_I2C_PACKET_SIZE] = अणुपूर्ण;
	u8 rx_buf[MXL_EAGLE_MAX_I2C_PACKET_SIZE] = अणुपूर्ण;
	u32 resp_checksum = 0, resp_checksum_पंचांगp = 0;
	काष्ठा MXL_EAGLE_HOST_MSG_HEADER_T *tx_header;
	काष्ठा MXL_EAGLE_HOST_MSG_HEADER_T *rx_header;

	mutex_lock(&dev->i2c_lock);

	अगर ((tx_payload_size + MXL_EAGLE_HOST_MSG_HEADER_SIZE) >
	    (MXL_EAGLE_MAX_I2C_PACKET_SIZE - MXL_EAGLE_I2C_PHEADER_SIZE)) अणु
		status = -EINVAL;
		जाओ err_finish;
	पूर्ण

	tx_header = (काष्ठा MXL_EAGLE_HOST_MSG_HEADER_T *)tx_buf;
	tx_header->opcode = opcode;
	tx_header->seqnum = dev->seqnum++;
	tx_header->payload_size = tx_payload_size;
	tx_header->checksum = 0;

	अगर (dev->seqnum == 0)
		dev->seqnum = 1;

	अगर (tx_payload && tx_payload_size > 0)
		स_नकल(&tx_buf[MXL_EAGLE_HOST_MSG_HEADER_SIZE], tx_payload, tx_payload_size);

	mxl692_tx_swap(opcode, tx_buf);

	tx_header->checksum = 0;
	tx_header->checksum = mxl692_checksum(tx_buf,
					      MXL_EAGLE_HOST_MSG_HEADER_SIZE + tx_payload_size);
#अगर_घोषित __LITTLE_ENDIAN
	convert_endian(4, (u8 *)&tx_header->checksum); /* cksum is big endian */
#पूर्ण_अगर
	/* send Tx message */
	status = mxl692_opग_लिखो(dev, tx_buf,
				tx_payload_size + MXL_EAGLE_HOST_MSG_HEADER_SIZE);
	अगर (status) अणु
		status = -EREMOTEIO;
		जाओ err_finish;
	पूर्ण

	/* receive Rx message (polling) */
	rx_header = (काष्ठा MXL_EAGLE_HOST_MSG_HEADER_T *)rx_buf;

	करो अणु
		status = mxl692_opपढ़ो(dev, rx_buf,
				       rx_payload_expected + MXL_EAGLE_HOST_MSG_HEADER_SIZE);
		usleep_range(1000, 2000);
		समयout--;
	पूर्ण जबतक ((समयout > 0) && (status == 0) &&
		 (rx_header->seqnum == 0) &&
		 (rx_header->checksum == 0));

	अगर (समयout == 0 || status) अणु
		dev_dbg(&dev->i2c_client->dev, "timeout=%d   status=%d\n",
			समयout, status);
		status = -ETIMEDOUT;
		जाओ err_finish;
	पूर्ण

	अगर (rx_header->status) अणु
		dev_dbg(&dev->i2c_client->dev, "rx header status code: %d\n", rx_header->status);
		status = -EREMOTEIO;
		जाओ err_finish;
	पूर्ण

	अगर (rx_header->seqnum != tx_header->seqnum ||
	    rx_header->opcode != tx_header->opcode ||
	    rx_header->payload_size != rx_payload_expected) अणु
		dev_dbg(&dev->i2c_client->dev, "Something failed seq=%s  opcode=%s  pSize=%s\n",
			rx_header->seqnum != tx_header->seqnum ? "X" : "0",
			rx_header->opcode != tx_header->opcode ? "X" : "0",
			rx_header->payload_size != rx_payload_expected ? "X" : "0");
		अगर (rx_header->payload_size != rx_payload_expected)
			dev_dbg(&dev->i2c_client->dev,
				"rx_header->payloadSize=%d   rx_payload_expected=%d\n",
				rx_header->payload_size, rx_payload_expected);
		status = -EREMOTEIO;
		जाओ err_finish;
	पूर्ण

	resp_checksum = rx_header->checksum;
	rx_header->checksum = 0;

	resp_checksum_पंचांगp = mxl692_checksum(rx_buf,
					    MXL_EAGLE_HOST_MSG_HEADER_SIZE + rx_header->payload_size);
#अगर_घोषित __LITTLE_ENDIAN
	convert_endian(4, (u8 *)&resp_checksum_पंचांगp); /* cksum is big endian */
#पूर्ण_अगर
	अगर (resp_checksum != resp_checksum_पंचांगp) अणु
		dev_dbg(&dev->i2c_client->dev, "rx checksum failure\n");
		status = -EREMOTEIO;
		जाओ err_finish;
	पूर्ण

	mxl692_rx_swap(rx_header->opcode, rx_buf);

	अगर (rx_header->payload_size > 0) अणु
		अगर (!rx_payload) अणु
			dev_dbg(&dev->i2c_client->dev, "no rx payload?!?\n");
			status = -EREMOTEIO;
			जाओ err_finish;
		पूर्ण
		स_नकल(rx_payload, rx_buf + MXL_EAGLE_HOST_MSG_HEADER_SIZE,
		       rx_header->payload_size);
	पूर्ण
err_finish:
	अगर (status)
		dev_dbg(&dev->i2c_client->dev, "err %d\n", status);

	mutex_unlock(&dev->i2c_lock);
	वापस status;
पूर्ण

अटल पूर्णांक mxl692_fwकरोwnload(काष्ठा mxl692_dev *dev,
			     स्थिर u8 *firmware_buf, u32 buf_len)
अणु
	पूर्णांक status = 0;
	u32 ix, reg_val = 0x1;
	u8 rx_buf[MXL_EAGLE_MAX_I2C_PACKET_SIZE] = अणुपूर्ण;
	काष्ठा MXL_EAGLE_DEV_STATUS_T *dev_status;

	अगर (buf_len < MXL_EAGLE_FW_HEADER_SIZE ||
	    buf_len > MXL_EAGLE_FW_MAX_SIZE_IN_KB * 1000)
		वापस -EINVAL;

	mutex_lock(&dev->i2c_lock);

	dev_dbg(&dev->i2c_client->dev, "\n");

	status = mxl692_validate_fw_header(dev, firmware_buf, buf_len);
	अगर (status)
		जाओ err_finish;

	ix = 16;
	status = mxl692_ग_लिखो_fw_block(dev, firmware_buf, buf_len, &ix); /* DRAM */
	अगर (status)
		जाओ err_finish;

	status = mxl692_ग_लिखो_fw_block(dev, firmware_buf, buf_len, &ix); /* IRAM */
	अगर (status)
		जाओ err_finish;

	/* release CPU from reset */
	status = mxl692_memग_लिखो(dev, 0x70000018, (u8 *)&reg_val, माप(u32));
	अगर (status)
		जाओ err_finish;

	mutex_unlock(&dev->i2c_lock);

	अगर (status == 0) अणु
		/* verअगरy FW is alive */
		usleep_range(MXL_EAGLE_FW_LOAD_TIME * 1000, (MXL_EAGLE_FW_LOAD_TIME + 5) * 1000);
		dev_status = (काष्ठा MXL_EAGLE_DEV_STATUS_T *)&rx_buf;
		status = mxl692_i2c_ग_लिखोपढ़ो(dev,
					      MXL_EAGLE_OPCODE_DEVICE_STATUS_GET,
					      शून्य,
					      0,
					      (u8 *)dev_status,
					      माप(काष्ठा MXL_EAGLE_DEV_STATUS_T));
	पूर्ण

	वापस status;
err_finish:
	mutex_unlock(&dev->i2c_lock);
	अगर (status)
		dev_dbg(&dev->i2c_client->dev, "err %d\n", status);
	वापस status;
पूर्ण

अटल पूर्णांक mxl692_get_versions(काष्ठा mxl692_dev *dev)
अणु
	पूर्णांक status = 0;
	काष्ठा MXL_EAGLE_DEV_VER_T dev_ver = अणुपूर्ण;
	अटल स्थिर अक्षर * स्थिर chip_id[] = अणु"N/A", "691", "248", "692"पूर्ण;

	status = mxl692_i2c_ग_लिखोपढ़ो(dev, MXL_EAGLE_OPCODE_DEVICE_VERSION_GET,
				      शून्य,
				      0,
				      (u8 *)&dev_ver,
				      माप(काष्ठा MXL_EAGLE_DEV_VER_T));
	अगर (status)
		वापस status;

	dev_info(&dev->i2c_client->dev, "MxL692_DEMOD Chip ID: %s\n",
		 chip_id[dev_ver.chip_id]);

	dev_info(&dev->i2c_client->dev,
		 "MxL692_DEMOD FW Version: %d.%d.%d.%d_RC%d\n",
		 dev_ver.firmware_ver[0],
		 dev_ver.firmware_ver[1],
		 dev_ver.firmware_ver[2],
		 dev_ver.firmware_ver[3],
		 dev_ver.firmware_ver[4]);

	वापस status;
पूर्ण

अटल पूर्णांक mxl692_reset(काष्ठा mxl692_dev *dev)
अणु
	पूर्णांक status = 0;
	u32 dev_type = MXL_EAGLE_DEVICE_MAX, reg_val = 0x2;

	dev_dbg(&dev->i2c_client->dev, "\n");

	/* legacy i2c override */
	status = mxl692_memग_लिखो(dev, 0x80000100, (u8 *)&reg_val, माप(u32));
	अगर (status)
		जाओ err_finish;

	/* verअगरy sku */
	status = mxl692_memपढ़ो(dev, 0x70000188, (u8 *)&dev_type, माप(u32));
	अगर (status)
		जाओ err_finish;

	अगर (dev_type != dev->device_type)
		जाओ err_finish;

err_finish:
	अगर (status)
		dev_dbg(&dev->i2c_client->dev, "err %d\n", status);
	वापस status;
पूर्ण

अटल पूर्णांक mxl692_config_regulators(काष्ठा mxl692_dev *dev,
				    क्रमागत MXL_EAGLE_POWER_SUPPLY_SOURCE_E घातer_supply)
अणु
	पूर्णांक status = 0;
	u32 reg_val;

	dev_dbg(&dev->i2c_client->dev, "\n");

	/* configure मुख्य regulator according to the घातer supply source */
	status = mxl692_memपढ़ो(dev, 0x90000000, (u8 *)&reg_val, माप(u32));
	अगर (status)
		जाओ err_finish;

	reg_val &= 0x00FFFFFF;
	reg_val |= (घातer_supply == MXL_EAGLE_POWER_SUPPLY_SOURCE_SINGLE) ?
					0x14000000 : 0x10000000;

	status = mxl692_memग_लिखो(dev, 0x90000000, (u8 *)&reg_val, माप(u32));
	अगर (status)
		जाओ err_finish;

	/* configure digital regulator to high current mode */
	status = mxl692_memपढ़ो(dev, 0x90000018, (u8 *)&reg_val, माप(u32));
	अगर (status)
		जाओ err_finish;

	reg_val |= 0x800;

	status = mxl692_memग_लिखो(dev, 0x90000018, (u8 *)&reg_val, माप(u32));

err_finish:
	अगर (status)
		dev_dbg(&dev->i2c_client->dev, "err %d\n", status);
	वापस status;
पूर्ण

अटल पूर्णांक mxl692_config_xtal(काष्ठा mxl692_dev *dev,
			      काष्ठा MXL_EAGLE_DEV_XTAL_T *dev_xtal)
अणु
	पूर्णांक status = 0;
	u32 reg_val, reg_val1;

	dev_dbg(&dev->i2c_client->dev, "\n");

	status = mxl692_memपढ़ो(dev, 0x90000000, (u8 *)&reg_val, माप(u32));
	अगर (status)
		जाओ err_finish;

	/* set XTAL capacitance */
	reg_val &= 0xFFFFFFE0;
	reg_val |= dev_xtal->xtal_cap;

	/* set CLK OUT */
	reg_val = dev_xtal->clk_out_enable ? (reg_val | 0x0100) : (reg_val & 0xFFFFFEFF);

	status = mxl692_memग_लिखो(dev, 0x90000000, (u8 *)&reg_val, माप(u32));
	अगर (status)
		जाओ err_finish;

	/* set CLK OUT भागider */
	reg_val = dev_xtal->clk_out_भाग_enable ? (reg_val | 0x0200) : (reg_val & 0xFFFFFDFF);

	status = mxl692_memग_लिखो(dev, 0x90000000, (u8 *)&reg_val, माप(u32));
	अगर (status)
		जाओ err_finish;

	/* set XTAL sharing */
	reg_val = dev_xtal->xtal_sharing_enable ? (reg_val | 0x010400) : (reg_val & 0xFFFEFBFF);

	status = mxl692_memग_लिखो(dev, 0x90000000, (u8 *)&reg_val, माप(u32));
	अगर (status)
		जाओ err_finish;

	/* enable/disable XTAL calibration, based on master/slave device */
	status = mxl692_memपढ़ो(dev, 0x90000030, (u8 *)&reg_val1, माप(u32));
	अगर (status)
		जाओ err_finish;

	अगर (dev_xtal->xtal_calibration_enable) अणु
		/* enable XTAL calibration and set XTAL amplitude to a higher value */
		reg_val1 &= 0xFFFFFFFD;
		reg_val1 |= 0x30;

		status = mxl692_memग_लिखो(dev, 0x90000030, (u8 *)&reg_val1, माप(u32));
		अगर (status)
			जाओ err_finish;
	पूर्ण अन्यथा अणु
		/* disable XTAL calibration */
		reg_val1 |= 0x2;

		status = mxl692_memग_लिखो(dev, 0x90000030, (u8 *)&reg_val1, माप(u32));
		अगर (status)
			जाओ err_finish;

		/* set XTAL bias value */
		status = mxl692_memपढ़ो(dev, 0x9000002c, (u8 *)&reg_val, माप(u32));
		अगर (status)
			जाओ err_finish;

		reg_val &= 0xC0FFFFFF;
		reg_val |= 0xA000000;

		status = mxl692_memग_लिखो(dev, 0x9000002c, (u8 *)&reg_val, माप(u32));
		अगर (status)
			जाओ err_finish;
	पूर्ण

	/* start XTAL calibration */
	status = mxl692_memपढ़ो(dev, 0x70000010, (u8 *)&reg_val, माप(u32));
	अगर (status)
		जाओ err_finish;

	reg_val |= 0x8;

	status = mxl692_memग_लिखो(dev, 0x70000010, (u8 *)&reg_val, माप(u32));
	अगर (status)
		जाओ err_finish;

	status = mxl692_memपढ़ो(dev, 0x70000018, (u8 *)&reg_val, माप(u32));
	अगर (status)
		जाओ err_finish;

	reg_val |= 0x10;

	status = mxl692_memग_लिखो(dev, 0x70000018, (u8 *)&reg_val, माप(u32));
	अगर (status)
		जाओ err_finish;

	status = mxl692_memपढ़ो(dev, 0x9001014c, (u8 *)&reg_val, माप(u32));
	अगर (status)
		जाओ err_finish;

	reg_val &= 0xFFFFEFFF;

	status = mxl692_memग_लिखो(dev, 0x9001014c, (u8 *)&reg_val, माप(u32));
	अगर (status)
		जाओ err_finish;

	reg_val |= 0x1000;

	status = mxl692_memग_लिखो(dev, 0x9001014c, (u8 *)&reg_val, माप(u32));
	अगर (status)
		जाओ err_finish;

	usleep_range(45000, 55000);

err_finish:
	अगर (status)
		dev_dbg(&dev->i2c_client->dev, "err %d\n", status);
	वापस status;
पूर्ण

अटल पूर्णांक mxl692_घातermode(काष्ठा mxl692_dev *dev,
			    क्रमागत MXL_EAGLE_POWER_MODE_E घातer_mode)
अणु
	पूर्णांक status = 0;
	u8 mode = घातer_mode;

	dev_dbg(&dev->i2c_client->dev, "%s\n",
		घातer_mode == MXL_EAGLE_POWER_MODE_SLEEP ? "sleep" : "active");

	status = mxl692_i2c_ग_लिखोपढ़ो(dev,
				      MXL_EAGLE_OPCODE_DEVICE_POWERMODE_SET,
				      &mode,
				      माप(u8),
				      शून्य,
				      0);
	अगर (status) अणु
		dev_dbg(&dev->i2c_client->dev, "err %d\n", status);
		वापस status;
	पूर्ण

	dev->घातer_mode = घातer_mode;

	वापस status;
पूर्ण

अटल पूर्णांक mxl692_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mxl692_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->i2c_client;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक status = 0;
	स्थिर काष्ठा firmware *firmware;
	काष्ठा MXL_EAGLE_DEV_XTAL_T xtal_config = अणुपूर्ण;

	dev_dbg(&dev->i2c_client->dev, "\n");

	अगर (dev->init_करोne)
		जाओ warm;

	dev->seqnum = 1;

	status = mxl692_reset(dev);
	अगर (status)
		जाओ err;

	usleep_range(50 * 1000, 60 * 1000); /* was 1000! */

	status = mxl692_config_regulators(dev, MXL_EAGLE_POWER_SUPPLY_SOURCE_DUAL);
	अगर (status)
		जाओ err;

	xtal_config.xtal_cap = 26;
	xtal_config.clk_out_भाग_enable = 0;
	xtal_config.clk_out_enable = 0;
	xtal_config.xtal_calibration_enable = 0;
	xtal_config.xtal_sharing_enable = 1;
	status = mxl692_config_xtal(dev, &xtal_config);
	अगर (status)
		जाओ err;

	status = request_firmware(&firmware, MXL692_FIRMWARE, &client->dev);
	अगर (status) अणु
		dev_dbg(&dev->i2c_client->dev, "firmware missing? %s\n",
			MXL692_FIRMWARE);
		जाओ err;
	पूर्ण

	status = mxl692_fwकरोwnload(dev, firmware->data, firmware->size);
	अगर (status)
		जाओ err_release_firmware;

	release_firmware(firmware);

	status = mxl692_get_versions(dev);
	अगर (status)
		जाओ err;

	dev->घातer_mode = MXL_EAGLE_POWER_MODE_SLEEP;
warm:
	/* Config Device Power Mode */
	अगर (dev->घातer_mode != MXL_EAGLE_POWER_MODE_ACTIVE) अणु
		status = mxl692_घातermode(dev, MXL_EAGLE_POWER_MODE_ACTIVE);
		अगर (status)
			जाओ err;

		usleep_range(50 * 1000, 60 * 1000); /* was 500! */
	पूर्ण

	/* Init stats here to indicate which stats are supported */
	c->cnr.len = 1;
	c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_error.len = 1;
	c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_count.len = 1;
	c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->block_error.len = 1;
	c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	dev->init_करोne = 1;
	वापस 0;
err_release_firmware:
	release_firmware(firmware);
err:
	dev_dbg(&dev->i2c_client->dev, "err %d\n", status);
	वापस status;
पूर्ण

अटल पूर्णांक mxl692_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mxl692_dev *dev = fe->demodulator_priv;

	अगर (dev->घातer_mode != MXL_EAGLE_POWER_MODE_SLEEP)
		mxl692_घातermode(dev, MXL_EAGLE_POWER_MODE_SLEEP);

	वापस 0;
पूर्ण

अटल पूर्णांक mxl692_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा mxl692_dev *dev = fe->demodulator_priv;

	पूर्णांक status = 0;
	क्रमागत MXL_EAGLE_DEMOD_TYPE_E demod_type;
	काष्ठा MXL_EAGLE_MPEGOUT_PARAMS_T mpeg_params = अणुपूर्ण;
	क्रमागत MXL_EAGLE_QAM_DEMOD_ANNEX_TYPE_E qam_annex = MXL_EAGLE_QAM_DEMOD_ANNEX_B;
	काष्ठा MXL_EAGLE_QAM_DEMOD_PARAMS_T qam_params = अणुपूर्ण;
	काष्ठा MXL_EAGLE_TUNER_CHANNEL_PARAMS_T tuner_params = अणुपूर्ण;
	u8 op_param = 0;

	dev_dbg(&dev->i2c_client->dev, "\n");

	चयन (p->modulation) अणु
	हाल VSB_8:
		demod_type = MXL_EAGLE_DEMOD_TYPE_ATSC;
		अवरोध;
	हाल QAM_AUTO:
	हाल QAM_64:
	हाल QAM_128:
	हाल QAM_256:
		demod_type = MXL_EAGLE_DEMOD_TYPE_QAM;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (dev->current_frequency == p->frequency && dev->demod_type == demod_type) अणु
		dev_dbg(&dev->i2c_client->dev, "already set up\n");
		वापस 0;
	पूर्ण

	dev->current_frequency = -1;
	dev->demod_type = -1;

	op_param = demod_type;
	status = mxl692_i2c_ग_लिखोपढ़ो(dev,
				      MXL_EAGLE_OPCODE_DEVICE_DEMODULATOR_TYPE_SET,
				      &op_param,
				      माप(u8),
				      शून्य,
				      0);
	अगर (status) अणु
		dev_dbg(&dev->i2c_client->dev,
			"DEVICE_DEMODULATOR_TYPE_SET...FAIL  err 0x%x\n", status);
		जाओ err;
	पूर्ण

	usleep_range(20 * 1000, 30 * 1000); /* was 500! */

	mpeg_params.mpeg_parallel = 0;
	mpeg_params.msb_first = MXL_EAGLE_DATA_SERIAL_MSB_1ST;
	mpeg_params.mpeg_sync_pulse_width = MXL_EAGLE_DATA_SYNC_WIDTH_BIT;
	mpeg_params.mpeg_valid_pol = MXL_EAGLE_CLOCK_POSITIVE;
	mpeg_params.mpeg_sync_pol = MXL_EAGLE_CLOCK_POSITIVE;
	mpeg_params.mpeg_clk_pol = MXL_EAGLE_CLOCK_NEGATIVE;
	mpeg_params.mpeg3wire_mode_enable = 0;
	mpeg_params.mpeg_clk_freq = MXL_EAGLE_MPEG_CLOCK_27MHZ;

	चयन (demod_type) अणु
	हाल MXL_EAGLE_DEMOD_TYPE_ATSC:
		status = mxl692_i2c_ग_लिखोपढ़ो(dev,
					      MXL_EAGLE_OPCODE_DEVICE_MPEG_OUT_PARAMS_SET,
					      (u8 *)&mpeg_params,
					      माप(काष्ठा MXL_EAGLE_MPEGOUT_PARAMS_T),
					      शून्य,
					      0);
		अगर (status)
			जाओ err;
		अवरोध;
	हाल MXL_EAGLE_DEMOD_TYPE_QAM:
		अगर (qam_annex == MXL_EAGLE_QAM_DEMOD_ANNEX_A)
			mpeg_params.msb_first = MXL_EAGLE_DATA_SERIAL_LSB_1ST;
		status = mxl692_i2c_ग_लिखोपढ़ो(dev,
					      MXL_EAGLE_OPCODE_DEVICE_MPEG_OUT_PARAMS_SET,
					      (u8 *)&mpeg_params,
					      माप(काष्ठा MXL_EAGLE_MPEGOUT_PARAMS_T),
					      शून्य,
					      0);
		अगर (status)
			जाओ err;

		qam_params.annex_type = qam_annex;
		qam_params.qam_type = MXL_EAGLE_QAM_DEMOD_AUTO;
		qam_params.iq_flip = MXL_EAGLE_DEMOD_IQ_AUTO;
		अगर (p->modulation == QAM_64)
			qam_params.symbol_rate_hz = 5057000;
		अन्यथा
			qam_params.symbol_rate_hz = 5361000;

		qam_params.symbol_rate_256qam_hz = 5361000;

		status = mxl692_i2c_ग_लिखोपढ़ो(dev,
					      MXL_EAGLE_OPCODE_QAM_PARAMS_SET,
					      (u8 *)&qam_params,
					      माप(काष्ठा MXL_EAGLE_QAM_DEMOD_PARAMS_T),
					      शून्य, 0);
		अगर (status)
			जाओ err;

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	usleep_range(20 * 1000, 30 * 1000); /* was 500! */

	tuner_params.freq_hz = p->frequency;
	tuner_params.bandwidth = MXL_EAGLE_TUNER_BW_6MHZ;
	tuner_params.tune_mode = MXL_EAGLE_TUNER_CHANNEL_TUNE_MODE_VIEW;

	dev_dbg(&dev->i2c_client->dev, " Tuning Freq: %d %s\n", tuner_params.freq_hz,
		demod_type == MXL_EAGLE_DEMOD_TYPE_ATSC ? "ATSC" : "QAM");

	status = mxl692_i2c_ग_लिखोपढ़ो(dev,
				      MXL_EAGLE_OPCODE_TUNER_CHANNEL_TUNE_SET,
				      (u8 *)&tuner_params,
				      माप(काष्ठा MXL_EAGLE_TUNER_CHANNEL_PARAMS_T),
				      शून्य,
				      0);
	अगर (status)
		जाओ err;

	usleep_range(20 * 1000, 30 * 1000); /* was 500! */

	चयन (demod_type) अणु
	हाल MXL_EAGLE_DEMOD_TYPE_ATSC:
		status = mxl692_i2c_ग_लिखोपढ़ो(dev,
					      MXL_EAGLE_OPCODE_ATSC_INIT_SET,
					      शून्य, 0, शून्य, 0);
		अगर (status)
			जाओ err;
		अवरोध;
	हाल MXL_EAGLE_DEMOD_TYPE_QAM:
		status = mxl692_i2c_ग_लिखोपढ़ो(dev,
					      MXL_EAGLE_OPCODE_QAM_RESTART_SET,
					      शून्य, 0, शून्य, 0);
		अगर (status)
			जाओ err;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	dev->demod_type = demod_type;
	dev->current_frequency = p->frequency;

	वापस 0;
err:
	dev_dbg(&dev->i2c_client->dev, "err %d\n", status);
	वापस status;
पूर्ण

अटल पूर्णांक mxl692_get_frontend(काष्ठा dvb_frontend *fe,
			       काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	p->modulation = c->modulation;
	p->frequency = c->frequency;

	वापस 0;
पूर्ण

अटल पूर्णांक mxl692_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा mxl692_dev *dev = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u8 rx_buf[MXL_EAGLE_MAX_I2C_PACKET_SIZE] = अणुपूर्ण;
	काष्ठा MXL_EAGLE_ATSC_DEMOD_STATUS_T *atsc_status;
	काष्ठा MXL_EAGLE_QAM_DEMOD_STATUS_T *qam_status;
	क्रमागत MXL_EAGLE_DEMOD_TYPE_E demod_type = dev->demod_type;
	पूर्णांक mxl_status = 0;

	*snr = 0;

	dev_dbg(&dev->i2c_client->dev, "\n");

	atsc_status = (काष्ठा MXL_EAGLE_ATSC_DEMOD_STATUS_T *)&rx_buf;
	qam_status = (काष्ठा MXL_EAGLE_QAM_DEMOD_STATUS_T *)&rx_buf;

	चयन (demod_type) अणु
	हाल MXL_EAGLE_DEMOD_TYPE_ATSC:
		mxl_status = mxl692_i2c_ग_लिखोपढ़ो(dev,
						  MXL_EAGLE_OPCODE_ATSC_STATUS_GET,
						  शून्य,
						  0,
						  rx_buf,
						  माप(काष्ठा MXL_EAGLE_ATSC_DEMOD_STATUS_T));
		अगर (!mxl_status) अणु
			*snr = (u16)(atsc_status->snr_db_tenths / 10);
			c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
			c->cnr.stat[0].svalue = *snr;
		पूर्ण
		अवरोध;
	हाल MXL_EAGLE_DEMOD_TYPE_QAM:
		mxl_status = mxl692_i2c_ग_लिखोपढ़ो(dev,
						  MXL_EAGLE_OPCODE_QAM_STATUS_GET,
						  शून्य,
						  0,
						  rx_buf,
						  माप(काष्ठा MXL_EAGLE_QAM_DEMOD_STATUS_T));
		अगर (!mxl_status)
			*snr = (u16)(qam_status->snr_db_tenths / 10);
		अवरोध;
	हाल MXL_EAGLE_DEMOD_TYPE_OOB:
	शेष:
		अवरोध;
	पूर्ण

	अगर (mxl_status)
		dev_dbg(&dev->i2c_client->dev, "err %d\n", mxl_status);
	वापस mxl_status;
पूर्ण

अटल पूर्णांक mxl692_पढ़ो_ber_ucb(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mxl692_dev *dev = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u8 rx_buf[MXL_EAGLE_MAX_I2C_PACKET_SIZE] = अणुपूर्ण;
	काष्ठा MXL_EAGLE_ATSC_DEMOD_ERROR_COUNTERS_T *atsc_errors;
	क्रमागत MXL_EAGLE_DEMOD_TYPE_E demod_type = dev->demod_type;
	पूर्णांक mxl_status = 0;
	u32 uपंचांगp;

	dev_dbg(&dev->i2c_client->dev, "\n");

	atsc_errors = (काष्ठा MXL_EAGLE_ATSC_DEMOD_ERROR_COUNTERS_T *)&rx_buf;

	चयन (demod_type) अणु
	हाल MXL_EAGLE_DEMOD_TYPE_ATSC:
		mxl_status = mxl692_i2c_ग_लिखोपढ़ो(dev,
						  MXL_EAGLE_OPCODE_ATSC_ERROR_COUNTERS_GET,
						  शून्य,
						  0,
						  rx_buf,
						  माप(काष्ठा MXL_EAGLE_ATSC_DEMOD_ERROR_COUNTERS_T));
		अगर (!mxl_status) अणु
			अगर (atsc_errors->error_packets == 0)
				uपंचांगp = 0;
			अन्यथा
				uपंचांगp = ((atsc_errors->error_bytes / atsc_errors->error_packets) *
					atsc_errors->total_packets);
			/* ber */
			c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
			c->post_bit_error.stat[0].uvalue += atsc_errors->error_bytes;
			c->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
			c->post_bit_count.stat[0].uvalue += uपंचांगp;
			/* ucb */
			c->block_error.stat[0].scale = FE_SCALE_COUNTER;
			c->block_error.stat[0].uvalue += atsc_errors->error_packets;

			dev_dbg(&dev->i2c_client->dev, "%llu   %llu\n",
				c->post_bit_count.stat[0].uvalue, c->block_error.stat[0].uvalue);
		पूर्ण
		अवरोध;
	हाल MXL_EAGLE_DEMOD_TYPE_QAM:
	हाल MXL_EAGLE_DEMOD_TYPE_OOB:
	शेष:
		अवरोध;
	पूर्ण

	अगर (mxl_status)
		dev_dbg(&dev->i2c_client->dev, "err %d\n", mxl_status);

	वापस mxl_status;
पूर्ण

अटल पूर्णांक mxl692_पढ़ो_status(काष्ठा dvb_frontend *fe,
			      क्रमागत fe_status *status)
अणु
	काष्ठा mxl692_dev *dev = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u8 rx_buf[MXL_EAGLE_MAX_I2C_PACKET_SIZE] = अणुपूर्ण;
	काष्ठा MXL_EAGLE_ATSC_DEMOD_STATUS_T *atsc_status;
	काष्ठा MXL_EAGLE_QAM_DEMOD_STATUS_T *qam_status;
	क्रमागत MXL_EAGLE_DEMOD_TYPE_E demod_type = dev->demod_type;
	पूर्णांक mxl_status = 0;
	*status = 0;

	dev_dbg(&dev->i2c_client->dev, "\n");

	atsc_status = (काष्ठा MXL_EAGLE_ATSC_DEMOD_STATUS_T *)&rx_buf;
	qam_status = (काष्ठा MXL_EAGLE_QAM_DEMOD_STATUS_T *)&rx_buf;

	चयन (demod_type) अणु
	हाल MXL_EAGLE_DEMOD_TYPE_ATSC:
		mxl_status = mxl692_i2c_ग_लिखोपढ़ो(dev,
						  MXL_EAGLE_OPCODE_ATSC_STATUS_GET,
						  शून्य,
						  0,
						  rx_buf,
						  माप(काष्ठा MXL_EAGLE_ATSC_DEMOD_STATUS_T));
		अगर (!mxl_status && atsc_status->atsc_lock) अणु
			*status |= FE_HAS_SIGNAL;
			*status |= FE_HAS_CARRIER;
			*status |= FE_HAS_VITERBI;
			*status |= FE_HAS_SYNC;
			*status |= FE_HAS_LOCK;

			c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
			c->cnr.stat[0].svalue = atsc_status->snr_db_tenths / 10;
		पूर्ण
		अवरोध;
	हाल MXL_EAGLE_DEMOD_TYPE_QAM:
		mxl_status = mxl692_i2c_ग_लिखोपढ़ो(dev,
						  MXL_EAGLE_OPCODE_QAM_STATUS_GET,
						  शून्य,
						  0,
						  rx_buf,
						  माप(काष्ठा MXL_EAGLE_QAM_DEMOD_STATUS_T));
		अगर (!mxl_status && qam_status->qam_locked) अणु
			*status |= FE_HAS_SIGNAL;
			*status |= FE_HAS_CARRIER;
			*status |= FE_HAS_VITERBI;
			*status |= FE_HAS_SYNC;
			*status |= FE_HAS_LOCK;

			c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
			c->cnr.stat[0].svalue = qam_status->snr_db_tenths / 10;
		पूर्ण
		अवरोध;
	हाल MXL_EAGLE_DEMOD_TYPE_OOB:
	शेष:
		अवरोध;
	पूर्ण

	अगर ((*status & FE_HAS_LOCK) == 0) अणु
		/* No lock, reset all statistics */
		c->cnr.len = 1;
		c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		वापस 0;
	पूर्ण

	अगर (mxl_status)
		dev_dbg(&dev->i2c_client->dev, "err %d\n", mxl_status);
	अन्यथा
		mxl_status = mxl692_पढ़ो_ber_ucb(fe);

	वापस mxl_status;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops mxl692_ops = अणु
	.delsys = अणु SYS_ATSC पूर्ण,
	.info = अणु
		.name = "MaxLinear MxL692 VSB tuner-demodulator",
		.frequency_min_hz      = 54000000,
		.frequency_max_hz      = 858000000,
		.frequency_stepsize_hz = 62500,
		.caps = FE_CAN_8VSB
	पूर्ण,

	.init         = mxl692_init,
	.sleep        = mxl692_sleep,
	.set_frontend = mxl692_set_frontend,
	.get_frontend = mxl692_get_frontend,

	.पढ़ो_status          = mxl692_पढ़ो_status,
	.पढ़ो_snr             = mxl692_पढ़ो_snr,
पूर्ण;

अटल पूर्णांक mxl692_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा mxl692_config *config = client->dev.platक्रमm_data;
	काष्ठा mxl692_dev *dev;
	पूर्णांक ret = 0;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		ret = -ENOMEM;
		dev_dbg(&client->dev, "kzalloc() failed\n");
		जाओ err;
	पूर्ण

	स_नकल(&dev->fe.ops, &mxl692_ops, माप(काष्ठा dvb_frontend_ops));
	dev->fe.demodulator_priv = dev;
	dev->i2c_client = client;
	*config->fe = &dev->fe;
	mutex_init(&dev->i2c_lock);
	i2c_set_clientdata(client, dev);

	dev_info(&client->dev, "MaxLinear mxl692 successfully attached\n");

	वापस 0;
err:
	dev_dbg(&client->dev, "failed %d\n", ret);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक mxl692_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा mxl692_dev *dev = i2c_get_clientdata(client);

	dev->fe.demodulator_priv = शून्य;
	i2c_set_clientdata(client, शून्य);
	kमुक्त(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id mxl692_id_table[] = अणु
	अणु"mxl692", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mxl692_id_table);

अटल काष्ठा i2c_driver mxl692_driver = अणु
	.driver = अणु
		.name	= "mxl692",
	पूर्ण,
	.probe		= mxl692_probe,
	.हटाओ		= mxl692_हटाओ,
	.id_table	= mxl692_id_table,
पूर्ण;

module_i2c_driver(mxl692_driver);

MODULE_AUTHOR("Brad Love <brad@nextdimension.cc>");
MODULE_DESCRIPTION("MaxLinear MxL692 demodulator/tuner driver");
MODULE_FIRMWARE(MXL692_FIRMWARE);
MODULE_LICENSE("GPL");
