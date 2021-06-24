<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/***********************************************************************

    AudioScience HPI driver
    Functions क्रम पढ़ोing DSP code using hotplug firmware loader

    Copyright (C) 1997-2014  AudioScience Inc. <support@audioscience.com>


***********************************************************************/
#घोषणा SOURCEखाता_NAME "hpidspcd.c"
#समावेश "hpidspcd.h"
#समावेश "hpidebug.h"
#समावेश "hpi_version.h"

काष्ठा dsp_code_निजी अणु
	/**  Firmware descriptor */
	स्थिर काष्ठा firmware *firmware;
	काष्ठा pci_dev *dev;
पूर्ण;

/*-------------------------------------------------------------------*/
लघु hpi_dsp_code_खोलो(u32 adapter, व्योम *os_data, काष्ठा dsp_code *dsp_code,
	u32 *os_error_code)
अणु
	स्थिर काष्ठा firmware *firmware;
	काष्ठा pci_dev *dev = os_data;
	काष्ठा code_header header;
	अक्षर fw_name[20];
	लघु err_ret = HPI_ERROR_DSP_खाता_NOT_FOUND;
	पूर्णांक err;

	प्र_लिखो(fw_name, "asihpi/dsp%04x.bin", adapter);

	err = request_firmware(&firmware, fw_name, &dev->dev);

	अगर (err || !firmware) अणु
		dev_err(&dev->dev, "%d, request_firmware failed for %s\n",
			err, fw_name);
		जाओ error1;
	पूर्ण
	अगर (firmware->size < माप(header)) अणु
		dev_err(&dev->dev, "Header size too small %s\n", fw_name);
		जाओ error2;
	पूर्ण
	स_नकल(&header, firmware->data, माप(header));

	अगर ((header.type != 0x45444F43) ||	/* "CODE" */
		(header.adapter != adapter)
		|| (header.size != firmware->size)) अणु
		dev_err(&dev->dev,
			"Invalid firmware header size %d != file %zd\n",
			header.size, firmware->size);
		जाओ error2;
	पूर्ण

	अगर (HPI_VER_MAJOR(header.version) != HPI_VER_MAJOR(HPI_VER)) अणु
		/* Major version change probably means Host-DSP protocol change */
		dev_err(&dev->dev,
			"Incompatible firmware version DSP image %X != Driver %X\n",
			header.version, HPI_VER);
		जाओ error2;
	पूर्ण

	अगर (header.version != HPI_VER) अणु
		dev_warn(&dev->dev,
			"Firmware version mismatch: DSP image %X != Driver %X\n",
			header.version, HPI_VER);
	पूर्ण

	HPI_DEBUG_LOG(DEBUG, "dsp code %s opened\n", fw_name);
	dsp_code->pvt = kदो_स्मृति(माप(*dsp_code->pvt), GFP_KERNEL);
	अगर (!dsp_code->pvt) अणु
		err_ret = HPI_ERROR_MEMORY_ALLOC;
		जाओ error2;
	पूर्ण

	dsp_code->pvt->dev = dev;
	dsp_code->pvt->firmware = firmware;
	dsp_code->header = header;
	dsp_code->block_length = header.size / माप(u32);
	dsp_code->word_count = माप(header) / माप(u32);
	वापस 0;

error2:
	release_firmware(firmware);
error1:
	dsp_code->block_length = 0;
	वापस err_ret;
पूर्ण

/*-------------------------------------------------------------------*/
व्योम hpi_dsp_code_बंद(काष्ठा dsp_code *dsp_code)
अणु
	HPI_DEBUG_LOG(DEBUG, "dsp code closed\n");
	release_firmware(dsp_code->pvt->firmware);
	kमुक्त(dsp_code->pvt);
पूर्ण

/*-------------------------------------------------------------------*/
व्योम hpi_dsp_code_शुरुआत(काष्ठा dsp_code *dsp_code)
अणु
	/* Go back to start of  data, after header */
	dsp_code->word_count = माप(काष्ठा code_header) / माप(u32);
पूर्ण

/*-------------------------------------------------------------------*/
लघु hpi_dsp_code_पढ़ो_word(काष्ठा dsp_code *dsp_code, u32 *pword)
अणु
	अगर (dsp_code->word_count + 1 > dsp_code->block_length)
		वापस HPI_ERROR_DSP_खाता_FORMAT;

	*pword = ((u32 *)(dsp_code->pvt->firmware->data))[dsp_code->
		word_count];
	dsp_code->word_count++;
	वापस 0;
पूर्ण

/*-------------------------------------------------------------------*/
लघु hpi_dsp_code_पढ़ो_block(माप_प्रकार words_requested,
	काष्ठा dsp_code *dsp_code, u32 **ppblock)
अणु
	अगर (dsp_code->word_count + words_requested > dsp_code->block_length)
		वापस HPI_ERROR_DSP_खाता_FORMAT;

	*ppblock =
		((u32 *)(dsp_code->pvt->firmware->data)) +
		dsp_code->word_count;
	dsp_code->word_count += words_requested;
	वापस 0;
पूर्ण
