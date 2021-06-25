<शैली गुरु>
/*****************************************************************************
 *
 *     Author: Xilinx, Inc.
 *
 *     This program is मुक्त software; you can redistribute it and/or modअगरy it
 *     under the terms of the GNU General Public License as published by the
 *     Free Software Foundation; either version 2 of the License, or (at your
 *     option) any later version.
 *
 *     XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS"
 *     AS A COURTESY TO YOU, SOLELY FOR USE IN DEVELOPING PROGRAMS AND
 *     SOLUTIONS FOR XILINX DEVICES.  BY PROVIDING THIS DESIGN, CODE,
 *     OR INFORMATION AS ONE POSSIBLE IMPLEMENTATION OF THIS FEATURE,
 *     APPLICATION OR STANDARD, XILINX IS MAKING NO REPRESENTATION
 *     THAT THIS IMPLEMENTATION IS FREE FROM ANY CLAIMS OF INFRINGEMENT,
 *     AND YOU ARE RESPONSIBLE FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE
 *     FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY DISCLAIMS ANY
 *     WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE
 *     IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR
 *     REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF
 *     INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *     FOR A PARTICULAR PURPOSE.
 *
 *     (c) Copyright 2007-2008 Xilinx Inc.
 *     All rights reserved.
 *
 *     You should have received a copy of the GNU General Public License aदीर्घ
 *     with this program; अगर not, ग_लिखो to the Free Software Foundation, Inc.,
 *     675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *****************************************************************************/

#समावेश "fifo_icap.h"

/* Register offsets क्रम the XHwIcap device. */
#घोषणा XHI_GIER_OFFSET	0x1C  /* Device Global Interrupt Enable Reg */
#घोषणा XHI_IPISR_OFFSET 0x20  /* Interrupt Status Register */
#घोषणा XHI_IPIER_OFFSET 0x28  /* Interrupt Enable Register */
#घोषणा XHI_WF_OFFSET 0x100 /* Write FIFO */
#घोषणा XHI_RF_OFFSET 0x104 /* Read FIFO */
#घोषणा XHI_SZ_OFFSET 0x108 /* Size Register */
#घोषणा XHI_CR_OFFSET 0x10C /* Control Register */
#घोषणा XHI_SR_OFFSET 0x110 /* Status Register */
#घोषणा XHI_WFV_OFFSET 0x114 /* Write FIFO Vacancy Register */
#घोषणा XHI_RFO_OFFSET 0x118 /* Read FIFO Occupancy Register */

/* Device Global Interrupt Enable Register (GIER) bit definitions */

#घोषणा XHI_GIER_GIE_MASK 0x80000000 /* Global Interrupt enable Mask */

/**
 * HwIcap Device Interrupt Status/Enable Registers
 *
 * Interrupt Status Register (IPISR) : This रेजिस्टर holds the
 * पूर्णांकerrupt status flags क्रम the device. These bits are toggle on
 * ग_लिखो.
 *
 * Interrupt Enable Register (IPIER) : This रेजिस्टर is used to enable
 * पूर्णांकerrupt sources क्रम the device.
 * Writing a '1' to a bit enables the corresponding पूर्णांकerrupt.
 * Writing a '0' to a bit disables the corresponding पूर्णांकerrupt.
 *
 * IPISR/IPIER रेजिस्टरs have the same bit definitions and are only defined
 * once.
 */
#घोषणा XHI_IPIXR_RFULL_MASK 0x00000008 /* Read FIFO Full */
#घोषणा XHI_IPIXR_WEMPTY_MASK 0x00000004 /* Write FIFO Empty */
#घोषणा XHI_IPIXR_RDP_MASK 0x00000002 /* Read FIFO half full */
#घोषणा XHI_IPIXR_WRP_MASK 0x00000001 /* Write FIFO half full */
#घोषणा XHI_IPIXR_ALL_MASK 0x0000000F /* Mask of all पूर्णांकerrupts */

/* Control Register (CR) */
#घोषणा XHI_CR_SW_RESET_MASK 0x00000008 /* SW Reset Mask */
#घोषणा XHI_CR_FIFO_CLR_MASK 0x00000004 /* FIFO Clear Mask */
#घोषणा XHI_CR_READ_MASK 0x00000002 /* Read from ICAP to FIFO */
#घोषणा XHI_CR_WRITE_MASK 0x00000001 /* Write from FIFO to ICAP */


#घोषणा XHI_WFO_MAX_VACANCY 1024 /* Max Write FIFO Vacancy, in words */
#घोषणा XHI_RFO_MAX_OCCUPANCY 256 /* Max Read FIFO Occupancy, in words */
/* The maximum amount we can request from fअगरo_icap_get_configuration
   at once, in bytes. */
#घोषणा XHI_MAX_READ_TRANSACTION_WORDS 0xFFF


/**
 * fअगरo_icap_fअगरo_ग_लिखो - Write data to the ग_लिखो FIFO.
 * @drvdata: a poपूर्णांकer to the drvdata.
 * @data: the 32-bit value to be written to the FIFO.
 *
 * This function will silently fail अगर the fअगरo is full.
 **/
अटल अंतरभूत व्योम fअगरo_icap_fअगरo_ग_लिखो(काष्ठा hwicap_drvdata *drvdata,
		u32 data)
अणु
	dev_dbg(drvdata->dev, "fifo_write: %x\n", data);
	out_be32(drvdata->base_address + XHI_WF_OFFSET, data);
पूर्ण

/**
 * fअगरo_icap_fअगरo_पढ़ो - Read data from the Read FIFO.
 * @drvdata: a poपूर्णांकer to the drvdata.
 *
 * This function will silently fail अगर the fअगरo is empty.
 **/
अटल अंतरभूत u32 fअगरo_icap_fअगरo_पढ़ो(काष्ठा hwicap_drvdata *drvdata)
अणु
	u32 data = in_be32(drvdata->base_address + XHI_RF_OFFSET);
	dev_dbg(drvdata->dev, "fifo_read: %x\n", data);
	वापस data;
पूर्ण

/**
 * fअगरo_icap_set_पढ़ो_size - Set the the size रेजिस्टर.
 * @drvdata: a poपूर्णांकer to the drvdata.
 * @data: the size of the following पढ़ो transaction, in words.
 **/
अटल अंतरभूत व्योम fअगरo_icap_set_पढ़ो_size(काष्ठा hwicap_drvdata *drvdata,
		u32 data)
अणु
	out_be32(drvdata->base_address + XHI_SZ_OFFSET, data);
पूर्ण

/**
 * fअगरo_icap_start_config - Initiate a configuration (ग_लिखो) to the device.
 * @drvdata: a poपूर्णांकer to the drvdata.
 **/
अटल अंतरभूत व्योम fअगरo_icap_start_config(काष्ठा hwicap_drvdata *drvdata)
अणु
	out_be32(drvdata->base_address + XHI_CR_OFFSET, XHI_CR_WRITE_MASK);
	dev_dbg(drvdata->dev, "configuration started\n");
पूर्ण

/**
 * fअगरo_icap_start_पढ़ोback - Initiate a पढ़ोback from the device.
 * @drvdata: a poपूर्णांकer to the drvdata.
 **/
अटल अंतरभूत व्योम fअगरo_icap_start_पढ़ोback(काष्ठा hwicap_drvdata *drvdata)
अणु
	out_be32(drvdata->base_address + XHI_CR_OFFSET, XHI_CR_READ_MASK);
	dev_dbg(drvdata->dev, "readback started\n");
पूर्ण

/**
 * fअगरo_icap_get_status - Get the contents of the status रेजिस्टर.
 * @drvdata: a poपूर्णांकer to the drvdata.
 *
 * The status रेजिस्टर contains the ICAP status and the करोne bit.
 *
 * D8 - cfgerr
 * D7 - dalign
 * D6 - rip
 * D5 - in_पात_l
 * D4 - Always 1
 * D3 - Always 1
 * D2 - Always 1
 * D1 - Always 1
 * D0 - Done bit
 **/
u32 fअगरo_icap_get_status(काष्ठा hwicap_drvdata *drvdata)
अणु
	u32 status = in_be32(drvdata->base_address + XHI_SR_OFFSET);
	dev_dbg(drvdata->dev, "Getting status = %x\n", status);
	वापस status;
पूर्ण

/**
 * fअगरo_icap_busy - Return true अगर the ICAP is still processing a transaction.
 * @drvdata: a poपूर्णांकer to the drvdata.
 **/
अटल अंतरभूत u32 fअगरo_icap_busy(काष्ठा hwicap_drvdata *drvdata)
अणु
	u32 status = in_be32(drvdata->base_address + XHI_SR_OFFSET);
	वापस (status & XHI_SR_DONE_MASK) ? 0 : 1;
पूर्ण

/**
 * fअगरo_icap_ग_लिखो_fअगरo_vacancy - Query the ग_लिखो fअगरo available space.
 * @drvdata: a poपूर्णांकer to the drvdata.
 *
 * Return the number of words that can be safely pushed पूर्णांकo the ग_लिखो fअगरo.
 **/
अटल अंतरभूत u32 fअगरo_icap_ग_लिखो_fअगरo_vacancy(
		काष्ठा hwicap_drvdata *drvdata)
अणु
	वापस in_be32(drvdata->base_address + XHI_WFV_OFFSET);
पूर्ण

/**
 * fअगरo_icap_पढ़ो_fअगरo_occupancy - Query the पढ़ो fअगरo available data.
 * @drvdata: a poपूर्णांकer to the drvdata.
 *
 * Return the number of words that can be safely पढ़ो from the पढ़ो fअगरo.
 **/
अटल अंतरभूत u32 fअगरo_icap_पढ़ो_fअगरo_occupancy(
		काष्ठा hwicap_drvdata *drvdata)
अणु
	वापस in_be32(drvdata->base_address + XHI_RFO_OFFSET);
पूर्ण

/**
 * fअगरo_icap_set_configuration - Send configuration data to the ICAP.
 * @drvdata: a poपूर्णांकer to the drvdata.
 * @frame_buffer: a poपूर्णांकer to the data to be written to the
 *		ICAP device.
 * @num_words: the number of words (32 bit) to ग_लिखो to the ICAP
 *		device.

 * This function ग_लिखोs the given user data to the Write FIFO in
 * polled mode and starts the transfer of the data to
 * the ICAP device.
 **/
पूर्णांक fअगरo_icap_set_configuration(काष्ठा hwicap_drvdata *drvdata,
		u32 *frame_buffer, u32 num_words)
अणु

	u32 ग_लिखो_fअगरo_vacancy = 0;
	u32 retries = 0;
	u32 reमुख्यing_words;

	dev_dbg(drvdata->dev, "fifo_set_configuration\n");

	/*
	 * Check अगर the ICAP device is Busy with the last Read/Write
	 */
	अगर (fअगरo_icap_busy(drvdata))
		वापस -EBUSY;

	/*
	 * Set up the buffer poपूर्णांकer and the words to be transferred.
	 */
	reमुख्यing_words = num_words;

	जबतक (reमुख्यing_words > 0) अणु
		/*
		 * Wait until we have some data in the fअगरo.
		 */
		जबतक (ग_लिखो_fअगरo_vacancy == 0) अणु
			ग_लिखो_fअगरo_vacancy =
				fअगरo_icap_ग_लिखो_fअगरo_vacancy(drvdata);
			retries++;
			अगर (retries > XHI_MAX_RETRIES)
				वापस -EIO;
		पूर्ण

		/*
		 * Write data पूर्णांकo the Write FIFO.
		 */
		जबतक ((ग_लिखो_fअगरo_vacancy != 0) &&
				(reमुख्यing_words > 0)) अणु
			fअगरo_icap_fअगरo_ग_लिखो(drvdata, *frame_buffer);

			reमुख्यing_words--;
			ग_लिखो_fअगरo_vacancy--;
			frame_buffer++;
		पूर्ण
		/* Start pushing whatever is in the FIFO पूर्णांकo the ICAP. */
		fअगरo_icap_start_config(drvdata);
	पूर्ण

	/* Wait until the ग_लिखो has finished. */
	जबतक (fअगरo_icap_busy(drvdata)) अणु
		retries++;
		अगर (retries > XHI_MAX_RETRIES)
			अवरोध;
	पूर्ण

	dev_dbg(drvdata->dev, "done fifo_set_configuration\n");

	/*
	 * If the requested number of words have not been पढ़ो from
	 * the device then indicate failure.
	 */
	अगर (reमुख्यing_words != 0)
		वापस -EIO;

	वापस 0;
पूर्ण

/**
 * fअगरo_icap_get_configuration - Read configuration data from the device.
 * @drvdata: a poपूर्णांकer to the drvdata.
 * @data: Address of the data representing the partial bitstream
 * @size: the size of the partial bitstream in 32 bit words.
 *
 * This function पढ़ोs the specअगरied number of words from the ICAP device in
 * the polled mode.
 */
पूर्णांक fअगरo_icap_get_configuration(काष्ठा hwicap_drvdata *drvdata,
		u32 *frame_buffer, u32 num_words)
अणु

	u32 पढ़ो_fअगरo_occupancy = 0;
	u32 retries = 0;
	u32 *data = frame_buffer;
	u32 reमुख्यing_words;
	u32 words_to_पढ़ो;

	dev_dbg(drvdata->dev, "fifo_get_configuration\n");

	/*
	 * Check अगर the ICAP device is Busy with the last Write/Read
	 */
	अगर (fअगरo_icap_busy(drvdata))
		वापस -EBUSY;

	reमुख्यing_words = num_words;

	जबतक (reमुख्यing_words > 0) अणु
		words_to_पढ़ो = reमुख्यing_words;
		/* The hardware has a limit on the number of words
		   that can be पढ़ो at one समय.  */
		अगर (words_to_पढ़ो > XHI_MAX_READ_TRANSACTION_WORDS)
			words_to_पढ़ो = XHI_MAX_READ_TRANSACTION_WORDS;

		reमुख्यing_words -= words_to_पढ़ो;

		fअगरo_icap_set_पढ़ो_size(drvdata, words_to_पढ़ो);
		fअगरo_icap_start_पढ़ोback(drvdata);

		जबतक (words_to_पढ़ो > 0) अणु
			/* Wait until we have some data in the fअगरo. */
			जबतक (पढ़ो_fअगरo_occupancy == 0) अणु
				पढ़ो_fअगरo_occupancy =
					fअगरo_icap_पढ़ो_fअगरo_occupancy(drvdata);
				retries++;
				अगर (retries > XHI_MAX_RETRIES)
					वापस -EIO;
			पूर्ण

			अगर (पढ़ो_fअगरo_occupancy > words_to_पढ़ो)
				पढ़ो_fअगरo_occupancy = words_to_पढ़ो;

			words_to_पढ़ो -= पढ़ो_fअगरo_occupancy;

			/* Read the data from the Read FIFO. */
			जबतक (पढ़ो_fअगरo_occupancy != 0) अणु
				*data++ = fअगरo_icap_fअगरo_पढ़ो(drvdata);
				पढ़ो_fअगरo_occupancy--;
			पूर्ण
		पूर्ण
	पूर्ण

	dev_dbg(drvdata->dev, "done fifo_get_configuration\n");

	वापस 0;
पूर्ण

/**
 * buffer_icap_reset - Reset the logic of the icap device.
 * @drvdata: a poपूर्णांकer to the drvdata.
 *
 * This function क्रमces the software reset of the complete HWICAP device.
 * All the रेजिस्टरs will वापस to the शेष value and the FIFO is also
 * flushed as a part of this software reset.
 */
व्योम fअगरo_icap_reset(काष्ठा hwicap_drvdata *drvdata)
अणु
	u32 reg_data;
	/*
	 * Reset the device by setting/clearing the RESET bit in the
	 * Control Register.
	 */
	reg_data = in_be32(drvdata->base_address + XHI_CR_OFFSET);

	out_be32(drvdata->base_address + XHI_CR_OFFSET,
				reg_data | XHI_CR_SW_RESET_MASK);

	out_be32(drvdata->base_address + XHI_CR_OFFSET,
				reg_data & (~XHI_CR_SW_RESET_MASK));

पूर्ण

/**
 * fअगरo_icap_flush_fअगरo - This function flushes the FIFOs in the device.
 * @drvdata: a poपूर्णांकer to the drvdata.
 */
व्योम fअगरo_icap_flush_fअगरo(काष्ठा hwicap_drvdata *drvdata)
अणु
	u32 reg_data;
	/*
	 * Flush the FIFO by setting/clearing the FIFO Clear bit in the
	 * Control Register.
	 */
	reg_data = in_be32(drvdata->base_address + XHI_CR_OFFSET);

	out_be32(drvdata->base_address + XHI_CR_OFFSET,
				reg_data | XHI_CR_FIFO_CLR_MASK);

	out_be32(drvdata->base_address + XHI_CR_OFFSET,
				reg_data & (~XHI_CR_FIFO_CLR_MASK));
पूर्ण

