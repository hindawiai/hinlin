<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/***********************************************************************/
/*

    AudioScience HPI driver
    Copyright (C) 1997-2011  AudioScience Inc. <support@audioscience.com>


\पile
Functions क्रम पढ़ोing DSP code to load पूर्णांकo DSP

*/
/***********************************************************************/
#अगर_अघोषित _HPIDSPCD_H_
#घोषणा _HPIDSPCD_H_

#समावेश "hpi_internal.h"

/** Header काष्ठाure क्रम dsp firmware file
 This काष्ठाure must match that used in s2bin.c क्रम generation of asidsp.bin
 */
/*#अगर_अघोषित DISABLE_PRAGMA_PACK1 */
/*#आशय pack(push, 1) */
/*#पूर्ण_अगर */
काष्ठा code_header अणु
	/** Size in bytes including header */
	u32 size;
	/** File type tag "CODE" == 0x45444F43 */
	u32 type;
	/** Adapter model number */
	u32 adapter;
	/** Firmware version*/
	u32 version;
	/** Data checksum */
	u32 checksum;
पूर्ण;
/*#अगर_अघोषित DISABLE_PRAGMA_PACK1 */
/*#आशय pack(pop) */
/*#पूर्ण_अगर */

/*? Don't need the pragmas? */
compile_समय_निश्चित((माप(काष्ठा code_header) == 20), code_header_size);

/** Descriptor क्रम dspcode from firmware loader */
काष्ठा dsp_code अणु
	/** copy of  file header */
	काष्ठा code_header header;
	/** Expected number of words in the whole dsp code,INCL header */
	u32 block_length;
	/** Number of words पढ़ो so far */
	u32 word_count;

	/** पूर्णांकernal state of DSP code पढ़ोer */
	काष्ठा dsp_code_निजी *pvt;
पूर्ण;

/** Prepare *psDspCode to refer to the requested adapter's firmware.
Code file name is obtained from HpiOs_GetDspCodePath

\लeturn 0 क्रम success, or error code अगर requested code is not available
*/
लघु hpi_dsp_code_खोलो(
	/** Code identअगरier, usually adapter family */
	u32 adapter, व्योम *pci_dev,
	/** Poपूर्णांकer to DSP code control काष्ठाure */
	काष्ठा dsp_code *ps_dsp_code,
	/** Poपूर्णांकer to dword to receive OS specअगरic error code */
	u32 *pos_error_code);

/** Close the DSP code file */
व्योम hpi_dsp_code_बंद(काष्ठा dsp_code *ps_dsp_code);

/** Rewind to the beginning of the DSP code file (क्रम verअगरy) */
व्योम hpi_dsp_code_शुरुआत(काष्ठा dsp_code *ps_dsp_code);

/** Read one word from the dsp code file
	\लeturn 0 क्रम success, or error code अगर eof, or block length exceeded
*/
लघु hpi_dsp_code_पढ़ो_word(काष्ठा dsp_code *ps_dsp_code,
				      /**< DSP code descriptor */
	u32 *pword /**< Where to store the पढ़ो word */
	);

/** Get a block of dsp code पूर्णांकo an पूर्णांकernal buffer, and provide a poपूर्णांकer to
that buffer. (If dsp code is alपढ़ोy an array in memory, it is referenced,
not copied.)

\लeturn Error अगर requested number of words are not available
*/
लघु hpi_dsp_code_पढ़ो_block(माप_प्रकार words_requested,
	काष्ठा dsp_code *ps_dsp_code,
	/* Poपूर्णांकer to store (Poपूर्णांकer to code buffer) */
	u32 **ppblock);

#पूर्ण_अगर
