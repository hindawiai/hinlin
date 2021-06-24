<शैली गुरु>
/****************************************************************************

   Copyright Echo Digital Audio Corporation (c) 1998 - 2004
   All rights reserved
   www.echoaudio.com

   This file is part of Echo Digital Audio's generic driver library.

   Echo Digital Audio's generic driver library is मुक्त software;
   you can redistribute it and/or modअगरy it under the terms of
   the GNU General Public License as published by the Free Software
   Foundation.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License क्रम more details.

   You should have received a copy of the GNU General Public License
   aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston,
   MA  02111-1307, USA.

   *************************************************************************

 Translation from C++ and adaptation क्रम use in ALSA-Driver
 were made by Giuliano Pochini <pochini@shiny.it>

****************************************************************************/

#अगर PAGE_SIZE < 4096
#त्रुटि PAGE_SIZE is < 4k
#पूर्ण_अगर

अटल पूर्णांक restore_dsp_rettings(काष्ठा echoaudio *chip);


/* Some vector commands involve the DSP पढ़ोing or writing data to and from the
comm page; अगर you send one of these commands to the DSP, it will complete the
command and then ग_लिखो a non-zero value to the Handshake field in the
comm page.  This function रुकोs क्रम the handshake to show up. */
अटल पूर्णांक रुको_handshake(काष्ठा echoaudio *chip)
अणु
	पूर्णांक i;

	/* Wait up to 20ms क्रम the handshake from the DSP */
	क्रम (i = 0; i < HANDSHAKE_TIMEOUT; i++) अणु
		/* Look क्रम the handshake value */
		barrier();
		अगर (chip->comm_page->handshake) अणु
			वापस 0;
		पूर्ण
		udelay(1);
	पूर्ण

	dev_err(chip->card->dev, "wait_handshake(): Timeout waiting for DSP\n");
	वापस -EBUSY;
पूर्ण



/* Much of the पूर्णांकeraction between the DSP and the driver is करोne via vector
commands; send_vector ग_लिखोs a vector command to the DSP.  Typically, this
causes the DSP to पढ़ो or ग_लिखो fields in the comm page.
PCI posting is not required thanks to the handshake logic. */
अटल पूर्णांक send_vector(काष्ठा echoaudio *chip, u32 command)
अणु
	पूर्णांक i;

	wmb();	/* Flush all pending ग_लिखोs beक्रमe sending the command */

	/* Wait up to 100ms क्रम the "vector busy" bit to be off */
	क्रम (i = 0; i < VECTOR_BUSY_TIMEOUT; i++) अणु
		अगर (!(get_dsp_रेजिस्टर(chip, CHI32_VECTOR_REG) &
		      CHI32_VECTOR_BUSY)) अणु
			set_dsp_रेजिस्टर(chip, CHI32_VECTOR_REG, command);
			/*अगर (i)  DE_ACT(("send_vector time: %d\n", i));*/
			वापस 0;
		पूर्ण
		udelay(1);
	पूर्ण

	dev_err(chip->card->dev, "timeout on send_vector\n");
	वापस -EBUSY;
पूर्ण



/* ग_लिखो_dsp ग_लिखोs a 32-bit value to the DSP; this is used almost
exclusively क्रम loading the DSP. */
अटल पूर्णांक ग_लिखो_dsp(काष्ठा echoaudio *chip, u32 data)
अणु
	u32 status, i;

	क्रम (i = 0; i < 10000000; i++) अणु	/* समयout = 10s */
		status = get_dsp_रेजिस्टर(chip, CHI32_STATUS_REG);
		अगर ((status & CHI32_STATUS_HOST_WRITE_EMPTY) != 0) अणु
			set_dsp_रेजिस्टर(chip, CHI32_DATA_REG, data);
			wmb();			/* ग_लिखो it immediately */
			वापस 0;
		पूर्ण
		udelay(1);
		cond_resched();
	पूर्ण

	chip->bad_board = true;		/* Set true until DSP re-loaded */
	dev_dbg(chip->card->dev, "write_dsp: Set bad_board to true\n");
	वापस -EIO;
पूर्ण



/* पढ़ो_dsp पढ़ोs a 32-bit value from the DSP; this is used almost
exclusively क्रम loading the DSP and checking the status of the ASIC. */
अटल पूर्णांक पढ़ो_dsp(काष्ठा echoaudio *chip, u32 *data)
अणु
	u32 status, i;

	क्रम (i = 0; i < READ_DSP_TIMEOUT; i++) अणु
		status = get_dsp_रेजिस्टर(chip, CHI32_STATUS_REG);
		अगर ((status & CHI32_STATUS_HOST_READ_FULL) != 0) अणु
			*data = get_dsp_रेजिस्टर(chip, CHI32_DATA_REG);
			वापस 0;
		पूर्ण
		udelay(1);
		cond_resched();
	पूर्ण

	chip->bad_board = true;		/* Set true until DSP re-loaded */
	dev_err(chip->card->dev, "read_dsp: Set bad_board to true\n");
	वापस -EIO;
पूर्ण



/****************************************************************************
	Firmware loading functions
 ****************************************************************************/

/* This function is used to पढ़ो back the serial number from the DSP;
this is triggered by the SET_COMMPAGE_ADDR command.
Only some early Echogals products have serial numbers in the ROM;
the serial number is not used, but you still need to करो this as
part of the DSP load process. */
अटल पूर्णांक पढ़ो_sn(काष्ठा echoaudio *chip)
अणु
	पूर्णांक i;
	u32 sn[6];

	क्रम (i = 0; i < 5; i++) अणु
		अगर (पढ़ो_dsp(chip, &sn[i])) अणु
			dev_err(chip->card->dev,
				"Failed to read serial number\n");
			वापस -EIO;
		पूर्ण
	पूर्ण
	dev_dbg(chip->card->dev,
		"Read serial number %08x %08x %08x %08x %08x\n",
		 sn[0], sn[1], sn[2], sn[3], sn[4]);
	वापस 0;
पूर्ण



#अगर_अघोषित ECHOCARD_HAS_ASIC
/* This card has no ASIC, just वापस ok */
अटल अंतरभूत पूर्णांक check_asic_status(काष्ठा echoaudio *chip)
अणु
	chip->asic_loaded = true;
	वापस 0;
पूर्ण

#पूर्ण_अगर /* !ECHOCARD_HAS_ASIC */



#अगर_घोषित ECHOCARD_HAS_ASIC

/* Load ASIC code - करोne after the DSP is loaded */
अटल पूर्णांक load_asic_generic(काष्ठा echoaudio *chip, u32 cmd, लघु asic)
अणु
	स्थिर काष्ठा firmware *fw;
	पूर्णांक err;
	u32 i, size;
	u8 *code;

	err = get_firmware(&fw, chip, asic);
	अगर (err < 0) अणु
		dev_warn(chip->card->dev, "Firmware not found !\n");
		वापस err;
	पूर्ण

	code = (u8 *)fw->data;
	size = fw->size;

	/* Send the "Here comes the ASIC" command */
	अगर (ग_लिखो_dsp(chip, cmd) < 0)
		जाओ la_error;

	/* Write length of ASIC file in bytes */
	अगर (ग_लिखो_dsp(chip, size) < 0)
		जाओ la_error;

	क्रम (i = 0; i < size; i++) अणु
		अगर (ग_लिखो_dsp(chip, code[i]) < 0)
			जाओ la_error;
	पूर्ण

	मुक्त_firmware(fw, chip);
	वापस 0;

la_error:
	dev_err(chip->card->dev, "failed on write_dsp\n");
	मुक्त_firmware(fw, chip);
	वापस -EIO;
पूर्ण

#पूर्ण_अगर /* ECHOCARD_HAS_ASIC */



#अगर_घोषित DSP_56361

/* Install the resident loader क्रम 56361 DSPs;  The resident loader is on
the EPROM on the board क्रम 56301 DSP. The resident loader is a tiny little
program that is used to load the real DSP code. */
अटल पूर्णांक install_resident_loader(काष्ठा echoaudio *chip)
अणु
	u32 address;
	पूर्णांक index, words, i;
	u16 *code;
	u32 status;
	स्थिर काष्ठा firmware *fw;

	/* 56361 cards only!  This check is required by the old 56301-based
	Mona and Gina24 */
	अगर (chip->device_id != DEVICE_ID_56361)
		वापस 0;

	/* Look to see अगर the resident loader is present.  If the resident
	loader is alपढ़ोy installed, host flag 5 will be on. */
	status = get_dsp_रेजिस्टर(chip, CHI32_STATUS_REG);
	अगर (status & CHI32_STATUS_REG_HF5) अणु
		dev_dbg(chip->card->dev,
			"Resident loader already installed; status is 0x%x\n",
			 status);
		वापस 0;
	पूर्ण

	i = get_firmware(&fw, chip, FW_361_LOADER);
	अगर (i < 0) अणु
		dev_warn(chip->card->dev, "Firmware not found !\n");
		वापस i;
	पूर्ण

	/* The DSP code is an array of 16 bit words.  The array is भागided up
	पूर्णांकo sections.  The first word of each section is the size in words,
	followed by the section type.
	Since DSP addresses and data are 24 bits wide, they each take up two
	16 bit words in the array.
	This is a lot like the other loader loop, but it's not a loop, you
	करोn't write the memory type, and you don't ग_लिखो a zero at the end. */

	/* Set DSP क्रमmat bits क्रम 24 bit mode */
	set_dsp_रेजिस्टर(chip, CHI32_CONTROL_REG,
			 get_dsp_रेजिस्टर(chip, CHI32_CONTROL_REG) | 0x900);

	code = (u16 *)fw->data;

	/* Skip the header section; the first word in the array is the size
	of the first section, so the first real section of code is poपूर्णांकed
	to by Code[0]. */
	index = code[0];

	/* Skip the section size, LRS block type, and DSP memory type */
	index += 3;

	/* Get the number of DSP words to ग_लिखो */
	words = code[index++];

	/* Get the DSP address क्रम this block; 24 bits, so build from two words */
	address = ((u32)code[index] << 16) + code[index + 1];
	index += 2;

	/* Write the count to the DSP */
	अगर (ग_लिखो_dsp(chip, words)) अणु
		dev_err(chip->card->dev,
			"install_resident_loader: Failed to write word count!\n");
		जाओ irl_error;
	पूर्ण
	/* Write the DSP address */
	अगर (ग_लिखो_dsp(chip, address)) अणु
		dev_err(chip->card->dev,
			"install_resident_loader: Failed to write DSP address!\n");
		जाओ irl_error;
	पूर्ण
	/* Write out this block of code to the DSP */
	क्रम (i = 0; i < words; i++) अणु
		u32 data;

		data = ((u32)code[index] << 16) + code[index + 1];
		अगर (ग_लिखो_dsp(chip, data)) अणु
			dev_err(chip->card->dev,
				"install_resident_loader: Failed to write DSP code\n");
			जाओ irl_error;
		पूर्ण
		index += 2;
	पूर्ण

	/* Wait क्रम flag 5 to come up */
	क्रम (i = 0; i < 200; i++) अणु	/* Timeout is 50us * 200 = 10ms */
		udelay(50);
		status = get_dsp_रेजिस्टर(chip, CHI32_STATUS_REG);
		अगर (status & CHI32_STATUS_REG_HF5)
			अवरोध;
	पूर्ण

	अगर (i == 200) अणु
		dev_err(chip->card->dev, "Resident loader failed to set HF5\n");
		जाओ irl_error;
	पूर्ण

	dev_dbg(chip->card->dev, "Resident loader successfully installed\n");
	मुक्त_firmware(fw, chip);
	वापस 0;

irl_error:
	मुक्त_firmware(fw, chip);
	वापस -EIO;
पूर्ण

#पूर्ण_अगर /* DSP_56361 */


अटल पूर्णांक load_dsp(काष्ठा echoaudio *chip, u16 *code)
अणु
	u32 address, data;
	पूर्णांक index, words, i;

	अगर (chip->dsp_code == code) अणु
		dev_warn(chip->card->dev, "DSP is already loaded!\n");
		वापस 0;
	पूर्ण
	chip->bad_board = true;		/* Set true until DSP loaded */
	chip->dsp_code = शून्य;		/* Current DSP code not loaded */
	chip->asic_loaded = false;	/* Loading the DSP code will reset the ASIC */

	dev_dbg(chip->card->dev, "load_dsp: Set bad_board to true\n");

	/* If this board requires a resident loader, install it. */
#अगर_घोषित DSP_56361
	अगर ((i = install_resident_loader(chip)) < 0)
		वापस i;
#पूर्ण_अगर

	/* Send software reset command */
	अगर (send_vector(chip, DSP_VC_RESET) < 0) अणु
		dev_err(chip->card->dev,
			"LoadDsp: send_vector DSP_VC_RESET failed, Critical Failure\n");
		वापस -EIO;
	पूर्ण
	/* Delay 10us */
	udelay(10);

	/* Wait 10ms क्रम HF3 to indicate that software reset is complete */
	क्रम (i = 0; i < 1000; i++) अणु	/* Timeout is 10us * 1000 = 10ms */
		अगर (get_dsp_रेजिस्टर(chip, CHI32_STATUS_REG) &
		    CHI32_STATUS_REG_HF3)
			अवरोध;
		udelay(10);
	पूर्ण

	अगर (i == 1000) अणु
		dev_err(chip->card->dev,
			"load_dsp: Timeout waiting for CHI32_STATUS_REG_HF3\n");
		वापस -EIO;
	पूर्ण

	/* Set DSP क्रमmat bits क्रम 24 bit mode now that soft reset is करोne */
	set_dsp_रेजिस्टर(chip, CHI32_CONTROL_REG,
			 get_dsp_रेजिस्टर(chip, CHI32_CONTROL_REG) | 0x900);

	/* Main loader loop */

	index = code[0];
	क्रम (;;) अणु
		पूर्णांक block_type, mem_type;

		/* Total Block Size */
		index++;

		/* Block Type */
		block_type = code[index];
		अगर (block_type == 4)	/* We're finished */
			अवरोध;

		index++;

		/* Memory Type  P=0,X=1,Y=2 */
		mem_type = code[index++];

		/* Block Code Size */
		words = code[index++];
		अगर (words == 0)		/* We're finished */
			अवरोध;

		/* Start Address */
		address = ((u32)code[index] << 16) + code[index + 1];
		index += 2;

		अगर (ग_लिखो_dsp(chip, words) < 0) अणु
			dev_err(chip->card->dev,
				"load_dsp: failed to write number of DSP words\n");
			वापस -EIO;
		पूर्ण
		अगर (ग_लिखो_dsp(chip, address) < 0) अणु
			dev_err(chip->card->dev,
				"load_dsp: failed to write DSP address\n");
			वापस -EIO;
		पूर्ण
		अगर (ग_लिखो_dsp(chip, mem_type) < 0) अणु
			dev_err(chip->card->dev,
				"load_dsp: failed to write DSP memory type\n");
			वापस -EIO;
		पूर्ण
		/* Code */
		क्रम (i = 0; i < words; i++, index+=2) अणु
			data = ((u32)code[index] << 16) + code[index + 1];
			अगर (ग_लिखो_dsp(chip, data) < 0) अणु
				dev_err(chip->card->dev,
					"load_dsp: failed to write DSP data\n");
				वापस -EIO;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (ग_लिखो_dsp(chip, 0) < 0) अणु	/* We're करोne!!! */
		dev_err(chip->card->dev,
			"load_dsp: Failed to write final zero\n");
		वापस -EIO;
	पूर्ण
	udelay(10);

	क्रम (i = 0; i < 5000; i++) अणु	/* Timeout is 100us * 5000 = 500ms */
		/* Wait क्रम flag 4 - indicates that the DSP loaded OK */
		अगर (get_dsp_रेजिस्टर(chip, CHI32_STATUS_REG) &
		    CHI32_STATUS_REG_HF4) अणु
			set_dsp_रेजिस्टर(chip, CHI32_CONTROL_REG,
					 get_dsp_रेजिस्टर(chip, CHI32_CONTROL_REG) & ~0x1b00);

			अगर (ग_लिखो_dsp(chip, DSP_FNC_SET_COMMPAGE_ADDR) < 0) अणु
				dev_err(chip->card->dev,
					"load_dsp: Failed to write DSP_FNC_SET_COMMPAGE_ADDR\n");
				वापस -EIO;
			पूर्ण

			अगर (ग_लिखो_dsp(chip, chip->comm_page_phys) < 0) अणु
				dev_err(chip->card->dev,
					"load_dsp: Failed to write comm page address\n");
				वापस -EIO;
			पूर्ण

			/* Get the serial number via slave mode.
			This is triggered by the SET_COMMPAGE_ADDR command.
			We करोn't actually use the serial number but we have to
			get it as part of the DSP init vooकरोo. */
			अगर (पढ़ो_sn(chip) < 0) अणु
				dev_err(chip->card->dev,
					"load_dsp: Failed to read serial number\n");
				वापस -EIO;
			पूर्ण

			chip->dsp_code = code;		/* Show which DSP code loaded */
			chip->bad_board = false;	/* DSP OK */
			वापस 0;
		पूर्ण
		udelay(100);
	पूर्ण

	dev_err(chip->card->dev,
		"load_dsp: DSP load timed out waiting for HF4\n");
	वापस -EIO;
पूर्ण



/* load_firmware takes care of loading the DSP and any ASIC code. */
अटल पूर्णांक load_firmware(काष्ठा echoaudio *chip)
अणु
	स्थिर काष्ठा firmware *fw;
	पूर्णांक box_type, err;

	अगर (snd_BUG_ON(!chip->comm_page))
		वापस -EPERM;

	/* See अगर the ASIC is present and working - only अगर the DSP is alपढ़ोy loaded */
	अगर (chip->dsp_code) अणु
		अगर ((box_type = check_asic_status(chip)) >= 0)
			वापस box_type;
		/* ASIC check failed; क्रमce the DSP to reload */
		chip->dsp_code = शून्य;
	पूर्ण

	err = get_firmware(&fw, chip, chip->dsp_code_to_load);
	अगर (err < 0)
		वापस err;
	err = load_dsp(chip, (u16 *)fw->data);
	मुक्त_firmware(fw, chip);
	अगर (err < 0)
		वापस err;

	अगर ((box_type = load_asic(chip)) < 0)
		वापस box_type;	/* error */

	वापस box_type;
पूर्ण



/****************************************************************************
	Mixer functions
 ****************************************************************************/

#अगर defined(ECHOCARD_HAS_INPUT_NOMINAL_LEVEL) || \
	defined(ECHOCARD_HAS_OUTPUT_NOMINAL_LEVEL)

/* Set the nominal level क्रम an input or output bus (true = -10dBV, false = +4dBu) */
अटल पूर्णांक set_nominal_level(काष्ठा echoaudio *chip, u16 index, अक्षर consumer)
अणु
	अगर (snd_BUG_ON(index >= num_busses_out(chip) + num_busses_in(chip)))
		वापस -EINVAL;

	/* Wait क्रम the handshake (OK even अगर ASIC is not loaded) */
	अगर (रुको_handshake(chip))
		वापस -EIO;

	chip->nominal_level[index] = consumer;

	अगर (consumer)
		chip->comm_page->nominal_level_mask |= cpu_to_le32(1 << index);
	अन्यथा
		chip->comm_page->nominal_level_mask &= ~cpu_to_le32(1 << index);

	वापस 0;
पूर्ण

#पूर्ण_अगर /* ECHOCARD_HAS_*_NOMINAL_LEVEL */



/* Set the gain क्रम a single physical output channel (dB). */
अटल पूर्णांक set_output_gain(काष्ठा echoaudio *chip, u16 channel, s8 gain)
अणु
	अगर (snd_BUG_ON(channel >= num_busses_out(chip)))
		वापस -EINVAL;

	अगर (रुको_handshake(chip))
		वापस -EIO;

	/* Save the new value */
	chip->output_gain[channel] = gain;
	chip->comm_page->line_out_level[channel] = gain;
	वापस 0;
पूर्ण



#अगर_घोषित ECHOCARD_HAS_MONITOR
/* Set the monitor level from an input bus to an output bus. */
अटल पूर्णांक set_monitor_gain(काष्ठा echoaudio *chip, u16 output, u16 input,
			    s8 gain)
अणु
	अगर (snd_BUG_ON(output >= num_busses_out(chip) ||
		    input >= num_busses_in(chip)))
		वापस -EINVAL;

	अगर (रुको_handshake(chip))
		वापस -EIO;

	chip->monitor_gain[output][input] = gain;
	chip->comm_page->monitors[monitor_index(chip, output, input)] = gain;
	वापस 0;
पूर्ण
#पूर्ण_अगर /* ECHOCARD_HAS_MONITOR */


/* Tell the DSP to पढ़ो and update output, nominal & monitor levels in comm page. */
अटल पूर्णांक update_output_line_level(काष्ठा echoaudio *chip)
अणु
	अगर (रुको_handshake(chip))
		वापस -EIO;
	clear_handshake(chip);
	वापस send_vector(chip, DSP_VC_UPDATE_OUTVOL);
पूर्ण



/* Tell the DSP to पढ़ो and update input levels in comm page */
अटल पूर्णांक update_input_line_level(काष्ठा echoaudio *chip)
अणु
	अगर (रुको_handshake(chip))
		वापस -EIO;
	clear_handshake(chip);
	वापस send_vector(chip, DSP_VC_UPDATE_INGAIN);
पूर्ण



/* set_meters_on turns the meters on or off.  If meters are turned on, the DSP
will ग_लिखो the meter and घड़ी detect values to the comm page at about 30Hz */
अटल व्योम set_meters_on(काष्ठा echoaudio *chip, अक्षर on)
अणु
	अगर (on && !chip->meters_enabled) अणु
		send_vector(chip, DSP_VC_METERS_ON);
		chip->meters_enabled = 1;
	पूर्ण अन्यथा अगर (!on && chip->meters_enabled) अणु
		send_vector(chip, DSP_VC_METERS_OFF);
		chip->meters_enabled = 0;
		स_रखो((s8 *)chip->comm_page->vu_meter, ECHOGAIN_MUTED,
		       DSP_MAXPIPES);
		स_रखो((s8 *)chip->comm_page->peak_meter, ECHOGAIN_MUTED,
		       DSP_MAXPIPES);
	पूर्ण
पूर्ण



/* Fill out an the given array using the current values in the comm page.
Meters are written in the comm page by the DSP in this order:
 Output busses
 Input busses
 Output pipes (vmixer cards only)

This function assumes there are no more than 16 in/out busses or pipes
Meters is an array [3][16][2] of दीर्घ. */
अटल व्योम get_audio_meters(काष्ठा echoaudio *chip, दीर्घ *meters)
अणु
	अचिन्हित पूर्णांक i, m, n;

	क्रम (i = 0 ; i < 96; i++)
		meters[i] = 0;

	क्रम (m = 0, n = 0, i = 0; i < num_busses_out(chip); i++, m++) अणु
		meters[n++] = chip->comm_page->vu_meter[m];
		meters[n++] = chip->comm_page->peak_meter[m];
	पूर्ण

#अगर_घोषित ECHOCARD_ECHO3G
	m = E3G_MAX_OUTPUTS;	/* Skip unused meters */
#पूर्ण_अगर

	क्रम (n = 32, i = 0; i < num_busses_in(chip); i++, m++) अणु
		meters[n++] = chip->comm_page->vu_meter[m];
		meters[n++] = chip->comm_page->peak_meter[m];
	पूर्ण
#अगर_घोषित ECHOCARD_HAS_VMIXER
	क्रम (n = 64, i = 0; i < num_pipes_out(chip); i++, m++) अणु
		meters[n++] = chip->comm_page->vu_meter[m];
		meters[n++] = chip->comm_page->peak_meter[m];
	पूर्ण
#पूर्ण_अगर
पूर्ण



अटल पूर्णांक restore_dsp_rettings(काष्ठा echoaudio *chip)
अणु
	पूर्णांक i, o, err;

	अगर ((err = check_asic_status(chip)) < 0)
		वापस err;

	/* Gina20/Darla20 only. Should be harmless क्रम other cards. */
	chip->comm_page->gd_घड़ी_state = GD_CLOCK_UNDEF;
	chip->comm_page->gd_spdअगर_status = GD_SPDIF_STATUS_UNDEF;
	chip->comm_page->handshake = cpu_to_le32(0xffffffff);

	/* Restore output busses */
	क्रम (i = 0; i < num_busses_out(chip); i++) अणु
		err = set_output_gain(chip, i, chip->output_gain[i]);
		अगर (err < 0)
			वापस err;
	पूर्ण

#अगर_घोषित ECHOCARD_HAS_VMIXER
	क्रम (i = 0; i < num_pipes_out(chip); i++)
		क्रम (o = 0; o < num_busses_out(chip); o++) अणु
			err = set_vmixer_gain(chip, o, i,
						chip->vmixer_gain[o][i]);
			अगर (err < 0)
				वापस err;
		पूर्ण
	अगर (update_vmixer_level(chip) < 0)
		वापस -EIO;
#पूर्ण_अगर /* ECHOCARD_HAS_VMIXER */

#अगर_घोषित ECHOCARD_HAS_MONITOR
	क्रम (o = 0; o < num_busses_out(chip); o++)
		क्रम (i = 0; i < num_busses_in(chip); i++) अणु
			err = set_monitor_gain(chip, o, i,
						chip->monitor_gain[o][i]);
			अगर (err < 0)
				वापस err;
		पूर्ण
#पूर्ण_अगर /* ECHOCARD_HAS_MONITOR */

#अगर_घोषित ECHOCARD_HAS_INPUT_GAIN
	क्रम (i = 0; i < num_busses_in(chip); i++) अणु
		err = set_input_gain(chip, i, chip->input_gain[i]);
		अगर (err < 0)
			वापस err;
	पूर्ण
#पूर्ण_अगर /* ECHOCARD_HAS_INPUT_GAIN */

	err = update_output_line_level(chip);
	अगर (err < 0)
		वापस err;

	err = update_input_line_level(chip);
	अगर (err < 0)
		वापस err;

	err = set_sample_rate(chip, chip->sample_rate);
	अगर (err < 0)
		वापस err;

	अगर (chip->meters_enabled) अणु
		err = send_vector(chip, DSP_VC_METERS_ON);
		अगर (err < 0)
			वापस err;
	पूर्ण

#अगर_घोषित ECHOCARD_HAS_DIGITAL_MODE_SWITCH
	अगर (set_digital_mode(chip, chip->digital_mode) < 0)
		वापस -EIO;
#पूर्ण_अगर

#अगर_घोषित ECHOCARD_HAS_DIGITAL_IO
	अगर (set_professional_spdअगर(chip, chip->professional_spdअगर) < 0)
		वापस -EIO;
#पूर्ण_अगर

#अगर_घोषित ECHOCARD_HAS_PHANTOM_POWER
	अगर (set_phantom_घातer(chip, chip->phantom_घातer) < 0)
		वापस -EIO;
#पूर्ण_अगर

#अगर_घोषित ECHOCARD_HAS_EXTERNAL_CLOCK
	/* set_input_घड़ी() also restores स्वतःmute setting */
	अगर (set_input_घड़ी(chip, chip->input_घड़ी) < 0)
		वापस -EIO;
#पूर्ण_अगर

#अगर_घोषित ECHOCARD_HAS_OUTPUT_CLOCK_SWITCH
	अगर (set_output_घड़ी(chip, chip->output_घड़ी) < 0)
		वापस -EIO;
#पूर्ण_अगर

	अगर (रुको_handshake(chip) < 0)
		वापस -EIO;
	clear_handshake(chip);
	अगर (send_vector(chip, DSP_VC_UPDATE_FLAGS) < 0)
		वापस -EIO;

	वापस 0;
पूर्ण



/****************************************************************************
	Transport functions
 ****************************************************************************/

/* set_audio_क्रमmat() sets the क्रमmat of the audio data in host memory क्रम
this pipe.  Note that _MS_ (mono-to-stereo) playback modes are not used by ALSA
but they are here because they are just mono जबतक capturing */
अटल व्योम set_audio_क्रमmat(काष्ठा echoaudio *chip, u16 pipe_index,
			     स्थिर काष्ठा audioक्रमmat *क्रमmat)
अणु
	u16 dsp_क्रमmat;

	dsp_क्रमmat = DSP_AUDIOFORM_SS_16LE;

	/* Look क्रम super-पूर्णांकerleave (no big-endian and 8 bits) */
	अगर (क्रमmat->पूर्णांकerleave > 2) अणु
		चयन (क्रमmat->bits_per_sample) अणु
		हाल 16:
			dsp_क्रमmat = DSP_AUDIOFORM_SUPER_INTERLEAVE_16LE;
			अवरोध;
		हाल 24:
			dsp_क्रमmat = DSP_AUDIOFORM_SUPER_INTERLEAVE_24LE;
			अवरोध;
		हाल 32:
			dsp_क्रमmat = DSP_AUDIOFORM_SUPER_INTERLEAVE_32LE;
			अवरोध;
		पूर्ण
		dsp_क्रमmat |= क्रमmat->पूर्णांकerleave;
	पूर्ण अन्यथा अगर (क्रमmat->data_are_bigendian) अणु
		/* For big-endian data, only 32 bit samples are supported */
		चयन (क्रमmat->पूर्णांकerleave) अणु
		हाल 1:
			dsp_क्रमmat = DSP_AUDIOFORM_MM_32BE;
			अवरोध;
#अगर_घोषित ECHOCARD_HAS_STEREO_BIG_ENDIAN32
		हाल 2:
			dsp_क्रमmat = DSP_AUDIOFORM_SS_32BE;
			अवरोध;
#पूर्ण_अगर
		पूर्ण
	पूर्ण अन्यथा अगर (क्रमmat->पूर्णांकerleave == 1 &&
		   क्रमmat->bits_per_sample == 32 && !क्रमmat->mono_to_stereo) अणु
		/* 32 bit little-endian mono->mono हाल */
		dsp_क्रमmat = DSP_AUDIOFORM_MM_32LE;
	पूर्ण अन्यथा अणु
		/* Handle the other little-endian क्रमmats */
		चयन (क्रमmat->bits_per_sample) अणु
		हाल 8:
			अगर (क्रमmat->पूर्णांकerleave == 2)
				dsp_क्रमmat = DSP_AUDIOFORM_SS_8;
			अन्यथा
				dsp_क्रमmat = DSP_AUDIOFORM_MS_8;
			अवरोध;
		शेष:
		हाल 16:
			अगर (क्रमmat->पूर्णांकerleave == 2)
				dsp_क्रमmat = DSP_AUDIOFORM_SS_16LE;
			अन्यथा
				dsp_क्रमmat = DSP_AUDIOFORM_MS_16LE;
			अवरोध;
		हाल 24:
			अगर (क्रमmat->पूर्णांकerleave == 2)
				dsp_क्रमmat = DSP_AUDIOFORM_SS_24LE;
			अन्यथा
				dsp_क्रमmat = DSP_AUDIOFORM_MS_24LE;
			अवरोध;
		हाल 32:
			अगर (क्रमmat->पूर्णांकerleave == 2)
				dsp_क्रमmat = DSP_AUDIOFORM_SS_32LE;
			अन्यथा
				dsp_क्रमmat = DSP_AUDIOFORM_MS_32LE;
			अवरोध;
		पूर्ण
	पूर्ण
	dev_dbg(chip->card->dev,
		 "set_audio_format[%d] = %x\n", pipe_index, dsp_क्रमmat);
	chip->comm_page->audio_क्रमmat[pipe_index] = cpu_to_le16(dsp_क्रमmat);
पूर्ण



/* start_transport starts transport क्रम a set of pipes.
The bits 1 in channel_mask specअगरy what pipes to start. Only the bit of the
first channel must be set, regardless its पूर्णांकerleave.
Same thing क्रम छोड़ो_ and stop_ -trasport below. */
अटल पूर्णांक start_transport(काष्ठा echoaudio *chip, u32 channel_mask,
			   u32 cyclic_mask)
अणु

	अगर (रुको_handshake(chip))
		वापस -EIO;

	chip->comm_page->cmd_start |= cpu_to_le32(channel_mask);

	अगर (chip->comm_page->cmd_start) अणु
		clear_handshake(chip);
		send_vector(chip, DSP_VC_START_TRANSFER);
		अगर (रुको_handshake(chip))
			वापस -EIO;
		/* Keep track of which pipes are transporting */
		chip->active_mask |= channel_mask;
		chip->comm_page->cmd_start = 0;
		वापस 0;
	पूर्ण

	dev_err(chip->card->dev, "start_transport: No pipes to start!\n");
	वापस -EINVAL;
पूर्ण



अटल पूर्णांक छोड़ो_transport(काष्ठा echoaudio *chip, u32 channel_mask)
अणु

	अगर (रुको_handshake(chip))
		वापस -EIO;

	chip->comm_page->cmd_stop |= cpu_to_le32(channel_mask);
	chip->comm_page->cmd_reset = 0;
	अगर (chip->comm_page->cmd_stop) अणु
		clear_handshake(chip);
		send_vector(chip, DSP_VC_STOP_TRANSFER);
		अगर (रुको_handshake(chip))
			वापस -EIO;
		/* Keep track of which pipes are transporting */
		chip->active_mask &= ~channel_mask;
		chip->comm_page->cmd_stop = 0;
		chip->comm_page->cmd_reset = 0;
		वापस 0;
	पूर्ण

	dev_dbg(chip->card->dev, "pause_transport: No pipes to stop!\n");
	वापस 0;
पूर्ण



अटल पूर्णांक stop_transport(काष्ठा echoaudio *chip, u32 channel_mask)
अणु

	अगर (रुको_handshake(chip))
		वापस -EIO;

	chip->comm_page->cmd_stop |= cpu_to_le32(channel_mask);
	chip->comm_page->cmd_reset |= cpu_to_le32(channel_mask);
	अगर (chip->comm_page->cmd_reset) अणु
		clear_handshake(chip);
		send_vector(chip, DSP_VC_STOP_TRANSFER);
		अगर (रुको_handshake(chip))
			वापस -EIO;
		/* Keep track of which pipes are transporting */
		chip->active_mask &= ~channel_mask;
		chip->comm_page->cmd_stop = 0;
		chip->comm_page->cmd_reset = 0;
		वापस 0;
	पूर्ण

	dev_dbg(chip->card->dev, "stop_transport: No pipes to stop!\n");
	वापस 0;
पूर्ण



अटल अंतरभूत पूर्णांक is_pipe_allocated(काष्ठा echoaudio *chip, u16 pipe_index)
अणु
	वापस (chip->pipe_alloc_mask & (1 << pipe_index));
पूर्ण



/* Stops everything and turns off the DSP. All pipes should be alपढ़ोy
stopped and unallocated. */
अटल पूर्णांक rest_in_peace(काष्ठा echoaudio *chip)
अणु

	/* Stops all active pipes (just to be sure) */
	stop_transport(chip, chip->active_mask);

	set_meters_on(chip, false);

#अगर_घोषित ECHOCARD_HAS_MIDI
	enable_midi_input(chip, false);
#पूर्ण_अगर

	/* Go to sleep */
	अगर (chip->dsp_code) अणु
		/* Make load_firmware करो a complete reload */
		chip->dsp_code = शून्य;
		/* Put the DSP to sleep */
		वापस send_vector(chip, DSP_VC_GO_COMATOSE);
	पूर्ण
	वापस 0;
पूर्ण



/* Fills the comm page with शेष values */
अटल पूर्णांक init_dsp_comm_page(काष्ठा echoaudio *chip)
अणु
	/* Check अगर the compiler added extra padding inside the काष्ठाure */
	अगर (दुरत्व(काष्ठा comm_page, midi_output) != 0xbe0) अणु
		dev_err(chip->card->dev,
			"init_dsp_comm_page() - Invalid struct comm_page structure\n");
		वापस -EPERM;
	पूर्ण

	/* Init all the basic stuff */
	chip->card_name = ECHOCARD_NAME;
	chip->bad_board = true;	/* Set true until DSP loaded */
	chip->dsp_code = शून्य;	/* Current DSP code not loaded */
	chip->asic_loaded = false;
	स_रखो(chip->comm_page, 0, माप(काष्ठा comm_page));

	/* Init the comm page */
	chip->comm_page->comm_size =
		cpu_to_le32(माप(काष्ठा comm_page));
	chip->comm_page->handshake = cpu_to_le32(0xffffffff);
	chip->comm_page->midi_out_मुक्त_count =
		cpu_to_le32(DSP_MIDI_OUT_FIFO_SIZE);
	chip->comm_page->sample_rate = cpu_to_le32(44100);

	/* Set line levels so we करोn't blast any inमाला_दो on startup */
	स_रखो(chip->comm_page->monitors, ECHOGAIN_MUTED, MONITOR_ARRAY_SIZE);
	स_रखो(chip->comm_page->vmixer, ECHOGAIN_MUTED, VMIXER_ARRAY_SIZE);

	वापस 0;
पूर्ण



/* This function initializes the chip काष्ठाure with शेष values, ie. all
 * muted and पूर्णांकernal घड़ी source. Then it copies the settings to the DSP.
 * This MUST be called after the DSP is up and running !
 */
अटल पूर्णांक init_line_levels(काष्ठा echoaudio *chip)
अणु
	स_रखो(chip->output_gain, ECHOGAIN_MUTED, माप(chip->output_gain));
	स_रखो(chip->input_gain, ECHOGAIN_MUTED, माप(chip->input_gain));
	स_रखो(chip->monitor_gain, ECHOGAIN_MUTED, माप(chip->monitor_gain));
	स_रखो(chip->vmixer_gain, ECHOGAIN_MUTED, माप(chip->vmixer_gain));
	chip->input_घड़ी = ECHO_CLOCK_INTERNAL;
	chip->output_घड़ी = ECHO_CLOCK_WORD;
	chip->sample_rate = 44100;
	वापस restore_dsp_rettings(chip);
पूर्ण



/* This is low level part of the पूर्णांकerrupt handler.
It वापसs -1 अगर the IRQ is not ours, or N>=0 अगर it is, where N is the number
of midi data in the input queue. */
अटल पूर्णांक service_irq(काष्ठा echoaudio *chip)
अणु
	पूर्णांक st;

	/* Read the DSP status रेजिस्टर and see अगर this DSP generated this पूर्णांकerrupt */
	अगर (get_dsp_रेजिस्टर(chip, CHI32_STATUS_REG) & CHI32_STATUS_IRQ) अणु
		st = 0;
#अगर_घोषित ECHOCARD_HAS_MIDI
		/* Get and parse midi data अगर present */
		अगर (chip->comm_page->midi_input[0])	/* The count is at index 0 */
			st = midi_service_irq(chip);	/* Returns how many midi bytes we received */
#पूर्ण_अगर
		/* Clear the hardware पूर्णांकerrupt */
		chip->comm_page->midi_input[0] = 0;
		send_vector(chip, DSP_VC_ACK_INT);
		वापस st;
	पूर्ण
	वापस -1;
पूर्ण




/******************************************************************************
	Functions क्रम खोलोing and closing pipes
 ******************************************************************************/

/* allocate_pipes is used to reserve audio pipes क्रम your exclusive use.
The call will fail अगर some pipes are alपढ़ोy allocated. */
अटल पूर्णांक allocate_pipes(काष्ठा echoaudio *chip, काष्ठा audiopipe *pipe,
			  पूर्णांक pipe_index, पूर्णांक पूर्णांकerleave)
अणु
	पूर्णांक i;
	u32 channel_mask;

	dev_dbg(chip->card->dev,
		"allocate_pipes: ch=%d int=%d\n", pipe_index, पूर्णांकerleave);

	अगर (chip->bad_board)
		वापस -EIO;

	क्रम (channel_mask = i = 0; i < पूर्णांकerleave; i++)
		channel_mask |= 1 << (pipe_index + i);
	अगर (chip->pipe_alloc_mask & channel_mask) अणु
		dev_err(chip->card->dev,
			"allocate_pipes: channel already open\n");
		वापस -EAGAIN;
	पूर्ण

	chip->comm_page->position[pipe_index] = 0;
	chip->pipe_alloc_mask |= channel_mask;
	/* This driver uses cyclic buffers only */
	chip->pipe_cyclic_mask |= channel_mask;
	pipe->index = pipe_index;
	pipe->पूर्णांकerleave = पूर्णांकerleave;
	pipe->state = PIPE_STATE_STOPPED;

	/* The counter रेजिस्टर is where the DSP ग_लिखोs the 32 bit DMA
	position क्रम a pipe.  The DSP is स्थिरantly updating this value as
	it moves data. The DMA counter is in units of bytes, not samples. */
	pipe->dma_counter = (__le32 *)&chip->comm_page->position[pipe_index];
	*pipe->dma_counter = 0;
	वापस pipe_index;
पूर्ण



अटल पूर्णांक मुक्त_pipes(काष्ठा echoaudio *chip, काष्ठा audiopipe *pipe)
अणु
	u32 channel_mask;
	पूर्णांक i;

	अगर (snd_BUG_ON(!is_pipe_allocated(chip, pipe->index)))
		वापस -EINVAL;
	अगर (snd_BUG_ON(pipe->state != PIPE_STATE_STOPPED))
		वापस -EINVAL;

	क्रम (channel_mask = i = 0; i < pipe->पूर्णांकerleave; i++)
		channel_mask |= 1 << (pipe->index + i);

	chip->pipe_alloc_mask &= ~channel_mask;
	chip->pipe_cyclic_mask &= ~channel_mask;
	वापस 0;
पूर्ण



/******************************************************************************
	Functions क्रम managing the scatter-gather list
******************************************************************************/

अटल पूर्णांक sglist_init(काष्ठा echoaudio *chip, काष्ठा audiopipe *pipe)
अणु
	pipe->sglist_head = 0;
	स_रखो(pipe->sgpage.area, 0, PAGE_SIZE);
	chip->comm_page->sglist_addr[pipe->index].addr =
		cpu_to_le32(pipe->sgpage.addr);
	वापस 0;
पूर्ण



अटल पूर्णांक sglist_add_mapping(काष्ठा echoaudio *chip, काष्ठा audiopipe *pipe,
				dma_addr_t address, माप_प्रकार length)
अणु
	पूर्णांक head = pipe->sglist_head;
	काष्ठा sg_entry *list = (काष्ठा sg_entry *)pipe->sgpage.area;

	अगर (head < MAX_SGLIST_ENTRIES - 1) अणु
		list[head].addr = cpu_to_le32(address);
		list[head].size = cpu_to_le32(length);
		pipe->sglist_head++;
	पूर्ण अन्यथा अणु
		dev_err(chip->card->dev, "SGlist: too many fragments\n");
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण



अटल अंतरभूत पूर्णांक sglist_add_irq(काष्ठा echoaudio *chip, काष्ठा audiopipe *pipe)
अणु
	वापस sglist_add_mapping(chip, pipe, 0, 0);
पूर्ण



अटल अंतरभूत पूर्णांक sglist_wrap(काष्ठा echoaudio *chip, काष्ठा audiopipe *pipe)
अणु
	वापस sglist_add_mapping(chip, pipe, pipe->sgpage.addr, 0);
पूर्ण
