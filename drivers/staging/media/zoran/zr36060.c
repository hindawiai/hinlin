<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Zoran ZR36060 basic configuration functions
 *
 * Copyright (C) 2002 Laurent Pinअक्षरt <laurent.pinअक्षरt@skynet.be>
 */

#घोषणा ZR060_VERSION "v0.7"

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>

#समावेश <linux/types.h>
#समावेश <linux/रुको.h>

/* I/O commands, error codes */
#समावेश <linux/पन.स>

/* headerfile of this module */
#समावेश "zr36060.h"

/* codec io API */
#समावेश "videocodec.h"

/* it करोesn't make sense to have more than 20 or so, just to prevent some unwanted loops */
#घोषणा MAX_CODECS 20

/* amount of chips attached via this driver */
अटल पूर्णांक zr36060_codecs;

अटल bool low_bitrate;
module_param(low_bitrate, bool, 0);
MODULE_PARM_DESC(low_bitrate, "Buz compatibility option, halves bitrate");

/* debugging is available via module parameter */
अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug level (0-4)");

#घोषणा dprपूर्णांकk(num, क्रमmat, args...) \
	करो अणु \
		अगर (debug >= num) \
			prपूर्णांकk(क्रमmat, ##args); \
	पूर्ण जबतक (0)

/* =========================================================================
 * Local hardware I/O functions:
 * पढ़ो/ग_लिखो via codec layer (रेजिस्टरs are located in the master device)
 * =========================================================================
 */

अटल u8 zr36060_पढ़ो(काष्ठा zr36060 *ptr, u16 reg)
अणु
	u8 value = 0;

	// just in हाल something is wrong...
	अगर (ptr->codec->master_data->पढ़ोreg)
		value = (ptr->codec->master_data->पढ़ोreg(ptr->codec, reg)) & 0xff;
	अन्यथा
		pr_err("%s: invalid I/O setup, nothing read!\n", ptr->name);

	वापस value;
पूर्ण

अटल व्योम zr36060_ग_लिखो(काष्ठा zr36060 *ptr, u16 reg, u8 value)
अणु
	dprपूर्णांकk(4, "0x%02x @0x%04x\n", value, reg);

	// just in हाल something is wrong...
	अगर (ptr->codec->master_data->ग_लिखोreg)
		ptr->codec->master_data->ग_लिखोreg(ptr->codec, reg, value);
	अन्यथा
		pr_err("%s: invalid I/O setup, nothing written!\n", ptr->name);
पूर्ण

/* =========================================================================
 * Local helper function:
 * status पढ़ो
 * =========================================================================
 */

/* status is kept in dataकाष्ठाure */
अटल u8 zr36060_पढ़ो_status(काष्ठा zr36060 *ptr)
अणु
	ptr->status = zr36060_पढ़ो(ptr, ZR060_CFSR);

	zr36060_पढ़ो(ptr, 0);
	वापस ptr->status;
पूर्ण

/* scale factor is kept in dataकाष्ठाure */
अटल u16 zr36060_पढ़ो_scalefactor(काष्ठा zr36060 *ptr)
अणु
	ptr->scalefact = (zr36060_पढ़ो(ptr, ZR060_SF_HI) << 8) |
			 (zr36060_पढ़ो(ptr, ZR060_SF_LO) & 0xFF);

	/* leave 0 selected क्रम an eventually GO from master */
	zr36060_पढ़ो(ptr, 0);
	वापस ptr->scalefact;
पूर्ण

/* रुको अगर codec is पढ़ोy to proceed (end of processing) or समय is over */
अटल व्योम zr36060_रुको_end(काष्ठा zr36060 *ptr)
अणु
	पूर्णांक i = 0;

	जबतक (zr36060_पढ़ो_status(ptr) & ZR060_CFSR_BUSY) अणु
		udelay(1);
		अगर (i++ > 200000) अणु	// 200ms, there is क्रम sure something wrong!!!
			dprपूर्णांकk(1,
				"%s: timeout at wait_end (last status: 0x%02x)\n",
				ptr->name, ptr->status);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* Basic test of "connectivity", ग_लिखोs/पढ़ोs to/from memory the SOF marker */
अटल पूर्णांक zr36060_basic_test(काष्ठा zr36060 *ptr)
अणु
	अगर ((zr36060_पढ़ो(ptr, ZR060_IDR_DEV) != 0x33) &&
	    (zr36060_पढ़ो(ptr, ZR060_IDR_REV) != 0x01)) अणु
		pr_err("%s: attach failed, can't connect to jpeg processor!\n", ptr->name);
		वापस -ENXIO;
	पूर्ण

	zr36060_रुको_end(ptr);
	अगर (ptr->status & ZR060_CFSR_BUSY) अणु
		pr_err("%s: attach failed, jpeg processor failed (end flag)!\n", ptr->name);
		वापस -EBUSY;
	पूर्ण

	वापस 0;		/* looks good! */
पूर्ण

/* simple loop क्रम pushing the init datasets */
अटल पूर्णांक zr36060_pushit(काष्ठा zr36060 *ptr, u16 startreg, u16 len, स्थिर अक्षर *data)
अणु
	पूर्णांक i = 0;

	dprपूर्णांकk(4, "%s: write data block to 0x%04x (len=%d)\n", ptr->name,
		startreg, len);
	जबतक (i < len)
		zr36060_ग_लिखो(ptr, startreg++, data[i++]);

	वापस i;
पूर्ण

/* =========================================================================
 * Basic datasets:
 * jpeg baseline setup data (you find it on lots places in पूर्णांकernet, or just
 * extract it from any regular .jpg image...)
 *
 * Could be variable, but until it's not needed it they are just fixed to save
 * memory. Otherwise expand zr36060 काष्ठाure with arrays, push the values to
 * it and initialize from there, as e.g. the linux zr36057/60 driver करोes it.
 * =========================================================================
 */
अटल स्थिर अक्षर zr36060_dqt[0x86] = अणु
	0xff, 0xdb,		//Marker: DQT
	0x00, 0x84,		//Length: 2*65+2
	0x00,			//Pq,Tq first table
	0x10, 0x0b, 0x0c, 0x0e, 0x0c, 0x0a, 0x10, 0x0e,
	0x0d, 0x0e, 0x12, 0x11, 0x10, 0x13, 0x18, 0x28,
	0x1a, 0x18, 0x16, 0x16, 0x18, 0x31, 0x23, 0x25,
	0x1d, 0x28, 0x3a, 0x33, 0x3d, 0x3c, 0x39, 0x33,
	0x38, 0x37, 0x40, 0x48, 0x5c, 0x4e, 0x40, 0x44,
	0x57, 0x45, 0x37, 0x38, 0x50, 0x6d, 0x51, 0x57,
	0x5f, 0x62, 0x67, 0x68, 0x67, 0x3e, 0x4d, 0x71,
	0x79, 0x70, 0x64, 0x78, 0x5c, 0x65, 0x67, 0x63,
	0x01,			//Pq,Tq second table
	0x11, 0x12, 0x12, 0x18, 0x15, 0x18, 0x2f, 0x1a,
	0x1a, 0x2f, 0x63, 0x42, 0x38, 0x42, 0x63, 0x63,
	0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
	0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
	0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
	0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
	0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
	0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63
पूर्ण;

अटल स्थिर अक्षर zr36060_dht[0x1a4] = अणु
	0xff, 0xc4,		//Marker: DHT
	0x01, 0xa2,		//Length: 2*AC, 2*DC
	0x00,			//DC first table
	0x00, 0x01, 0x05, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
	0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
	0x01,			//DC second table
	0x00, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
	0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
	0x10,			//AC first table
	0x00, 0x02, 0x01, 0x03, 0x03, 0x02, 0x04, 0x03,
	0x05, 0x05, 0x04, 0x04, 0x00, 0x00,
	0x01, 0x7D, 0x01, 0x02, 0x03, 0x00, 0x04, 0x11,
	0x05, 0x12, 0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61,
	0x07, 0x22, 0x71, 0x14, 0x32, 0x81, 0x91, 0xA1,
	0x08, 0x23, 0x42, 0xB1, 0xC1, 0x15, 0x52, 0xD1, 0xF0, 0x24,
	0x33, 0x62, 0x72, 0x82, 0x09, 0x0A, 0x16, 0x17,
	0x18, 0x19, 0x1A, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x34,
	0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x43, 0x44,
	0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x53, 0x54, 0x55, 0x56,
	0x57, 0x58, 0x59, 0x5A, 0x63, 0x64, 0x65, 0x66,
	0x67, 0x68, 0x69, 0x6A, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
	0x79, 0x7A, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88,
	0x89, 0x8A, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99,
	0x9A, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8,
	0xA9, 0xAA, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9,
	0xBA, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8,
	0xC9, 0xCA, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9,
	0xDA, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7,
	0xE8, 0xE9, 0xEA, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7,
	0xF8, 0xF9, 0xFA,
	0x11,			//AC second table
	0x00, 0x02, 0x01, 0x02, 0x04, 0x04, 0x03, 0x04,
	0x07, 0x05, 0x04, 0x04, 0x00, 0x01,
	0x02, 0x77, 0x00, 0x01, 0x02, 0x03, 0x11, 0x04,
	0x05, 0x21, 0x31, 0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71,
	0x13, 0x22, 0x32, 0x81, 0x08, 0x14, 0x42, 0x91,
	0xA1, 0xB1, 0xC1, 0x09, 0x23, 0x33, 0x52, 0xF0, 0x15, 0x62,
	0x72, 0xD1, 0x0A, 0x16, 0x24, 0x34, 0xE1, 0x25,
	0xF1, 0x17, 0x18, 0x19, 0x1A, 0x26, 0x27, 0x28, 0x29, 0x2A,
	0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x43, 0x44,
	0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x53, 0x54, 0x55, 0x56,
	0x57, 0x58, 0x59, 0x5A, 0x63, 0x64, 0x65, 0x66,
	0x67, 0x68, 0x69, 0x6A, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
	0x79, 0x7A, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
	0x88, 0x89, 0x8A, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98,
	0x99, 0x9A, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7,
	0xA8, 0xA9, 0xAA, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8,
	0xB9, 0xBA, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7,
	0xC8, 0xC9, 0xCA, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8,
	0xD9, 0xDA, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7,
	0xE8, 0xE9, 0xEA, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8,
	0xF9, 0xFA
पूर्ण;

/* jpeg baseline setup, this is just fixed in this driver (YUV pictures) */
#घोषणा NO_OF_COMPONENTS          0x3	//Y,U,V
#घोषणा BASELINE_PRECISION        0x8	//MCU size (?)
अटल स्थिर अक्षर zr36060_tq[8] = अणु 0, 1, 1, 0, 0, 0, 0, 0 पूर्ण;	//table idx's QT
अटल स्थिर अक्षर zr36060_td[8] = अणु 0, 1, 1, 0, 0, 0, 0, 0 पूर्ण;	//table idx's DC
अटल स्थिर अक्षर zr36060_ta[8] = अणु 0, 1, 1, 0, 0, 0, 0, 0 पूर्ण;	//table idx's AC

/* horizontal 422 decimation setup (maybe we support 411 or so later, too) */
अटल स्थिर अक्षर zr36060_decimation_h[8] = अणु 2, 1, 1, 0, 0, 0, 0, 0 पूर्ण;
अटल स्थिर अक्षर zr36060_decimation_v[8] = अणु 1, 1, 1, 0, 0, 0, 0, 0 पूर्ण;

/* SOF (start of frame) segment depends on width, height and sampling ratio of each color component */
अटल पूर्णांक zr36060_set_sof(काष्ठा zr36060 *ptr)
अणु
	अक्षर sof_data[34];	// max. size of रेजिस्टर set
	पूर्णांक i;

	dprपूर्णांकk(3, "%s: write SOF (%dx%d, %d components)\n", ptr->name,
		ptr->width, ptr->height, NO_OF_COMPONENTS);
	sof_data[0] = 0xff;
	sof_data[1] = 0xc0;
	sof_data[2] = 0x00;
	sof_data[3] = (3 * NO_OF_COMPONENTS) + 8;
	sof_data[4] = BASELINE_PRECISION;	// only '8' possible with zr36060
	sof_data[5] = (ptr->height) >> 8;
	sof_data[6] = (ptr->height) & 0xff;
	sof_data[7] = (ptr->width) >> 8;
	sof_data[8] = (ptr->width) & 0xff;
	sof_data[9] = NO_OF_COMPONENTS;
	क्रम (i = 0; i < NO_OF_COMPONENTS; i++) अणु
		sof_data[10 + (i * 3)] = i;	// index identअगरier
		sof_data[11 + (i * 3)] = (ptr->h_samp_ratio[i] << 4) |
					 (ptr->v_samp_ratio[i]); // sampling ratios
		sof_data[12 + (i * 3)] = zr36060_tq[i];	// Q table selection
	पूर्ण
	वापस zr36060_pushit(ptr, ZR060_SOF_IDX,
			      (3 * NO_OF_COMPONENTS) + 10, sof_data);
पूर्ण

/* SOS (start of scan) segment depends on the used scan components of each color component */
अटल पूर्णांक zr36060_set_sos(काष्ठा zr36060 *ptr)
अणु
	अक्षर sos_data[16];	// max. size of रेजिस्टर set
	पूर्णांक i;

	dprपूर्णांकk(3, "%s: write SOS\n", ptr->name);
	sos_data[0] = 0xff;
	sos_data[1] = 0xda;
	sos_data[2] = 0x00;
	sos_data[3] = 2 + 1 + (2 * NO_OF_COMPONENTS) + 3;
	sos_data[4] = NO_OF_COMPONENTS;
	क्रम (i = 0; i < NO_OF_COMPONENTS; i++) अणु
		sos_data[5 + (i * 2)] = i;	// index
		sos_data[6 + (i * 2)] = (zr36060_td[i] << 4) |
					zr36060_ta[i]; // AC/DC tbl.sel.
	पूर्ण
	sos_data[2 + 1 + (2 * NO_OF_COMPONENTS) + 2] = 00;	// scan start
	sos_data[2 + 1 + (2 * NO_OF_COMPONENTS) + 3] = 0x3f;
	sos_data[2 + 1 + (2 * NO_OF_COMPONENTS) + 4] = 00;
	वापस zr36060_pushit(ptr, ZR060_SOS_IDX,
			      4 + 1 + (2 * NO_OF_COMPONENTS) + 3,
			      sos_data);
पूर्ण

/* DRI (define restart पूर्णांकerval) */
अटल पूर्णांक zr36060_set_dri(काष्ठा zr36060 *ptr)
अणु
	अक्षर dri_data[6];	// max. size of रेजिस्टर set

	dprपूर्णांकk(3, "%s: write DRI\n", ptr->name);
	dri_data[0] = 0xff;
	dri_data[1] = 0xdd;
	dri_data[2] = 0x00;
	dri_data[3] = 0x04;
	dri_data[4] = (ptr->dri) >> 8;
	dri_data[5] = (ptr->dri) & 0xff;
	वापस zr36060_pushit(ptr, ZR060_DRI_IDX, 6, dri_data);
पूर्ण

/* Setup compression/decompression of Zoran's JPEG processor ( see also zoran 36060 manual )
 * ... sorry क्रम the spaghetti code ...
 */
अटल व्योम zr36060_init(काष्ठा zr36060 *ptr)
अणु
	पूर्णांक sum = 0;
	दीर्घ bitcnt, पंचांगp;

	अगर (ptr->mode == CODEC_DO_COMPRESSION) अणु
		dprपूर्णांकk(2, "%s: COMPRESSION SETUP\n", ptr->name);

		zr36060_ग_लिखो(ptr, ZR060_LOAD, ZR060_LOAD_SYNC_RST);

		/* 060 communicates with 067 in master mode */
		zr36060_ग_लिखो(ptr, ZR060_CIR, ZR060_CIR_CODE_MSTR);

		/* Compression with or without variable scale factor */
		/*FIXME: What about ptr->bitrate_ctrl? */
		zr36060_ग_लिखो(ptr, ZR060_CMR, ZR060_CMR_COMP | ZR060_CMR_PASS2 | ZR060_CMR_BRB);

		/* Must be zero */
		zr36060_ग_लिखो(ptr, ZR060_MBZ, 0x00);
		zr36060_ग_लिखो(ptr, ZR060_TCR_HI, 0x00);
		zr36060_ग_लिखो(ptr, ZR060_TCR_LO, 0x00);

		/* Disable all IRQs - no DataErr means स्वतःreset */
		zr36060_ग_लिखो(ptr, ZR060_IMR, 0);

		/* volume control settings */
		zr36060_ग_लिखो(ptr, ZR060_SF_HI, ptr->scalefact >> 8);
		zr36060_ग_लिखो(ptr, ZR060_SF_LO, ptr->scalefact & 0xff);

		zr36060_ग_लिखो(ptr, ZR060_AF_HI, 0xff);
		zr36060_ग_लिखो(ptr, ZR060_AF_M, 0xff);
		zr36060_ग_लिखो(ptr, ZR060_AF_LO, 0xff);

		/* setup the variable jpeg tables */
		sum += zr36060_set_sof(ptr);
		sum += zr36060_set_sos(ptr);
		sum += zr36060_set_dri(ptr);

/* setup the fixed jpeg tables - maybe variable, though - (see table init section above) */
		sum += zr36060_pushit(ptr, ZR060_DQT_IDX, माप(zr36060_dqt), zr36060_dqt);
		sum += zr36060_pushit(ptr, ZR060_DHT_IDX, माप(zr36060_dht), zr36060_dht);
		zr36060_ग_लिखो(ptr, ZR060_APP_IDX, 0xff);
		zr36060_ग_लिखो(ptr, ZR060_APP_IDX + 1, 0xe0 + ptr->app.appn);
		zr36060_ग_लिखो(ptr, ZR060_APP_IDX + 2, 0x00);
		zr36060_ग_लिखो(ptr, ZR060_APP_IDX + 3, ptr->app.len + 2);
		sum += zr36060_pushit(ptr, ZR060_APP_IDX + 4, 60, ptr->app.data) + 4;
		zr36060_ग_लिखो(ptr, ZR060_COM_IDX, 0xff);
		zr36060_ग_लिखो(ptr, ZR060_COM_IDX + 1, 0xfe);
		zr36060_ग_लिखो(ptr, ZR060_COM_IDX + 2, 0x00);
		zr36060_ग_लिखो(ptr, ZR060_COM_IDX + 3, ptr->com.len + 2);
		sum += zr36060_pushit(ptr, ZR060_COM_IDX + 4, 60, ptr->com.data) + 4;

		/* setup misc. data क्रम compression (target code sizes) */

		/* size of compressed code to reach without header data */
		sum = ptr->real_code_vol - sum;
		bitcnt = sum << 3;	/* need the size in bits */

		पंचांगp = bitcnt >> 16;
		dprपूर्णांकk(3,
			"%s: code: csize=%d, tot=%d, bit=%ld, highbits=%ld\n",
			ptr->name, sum, ptr->real_code_vol, bitcnt, पंचांगp);
		zr36060_ग_लिखो(ptr, ZR060_TCV_NET_HI, पंचांगp >> 8);
		zr36060_ग_लिखो(ptr, ZR060_TCV_NET_MH, पंचांगp & 0xff);
		पंचांगp = bitcnt & 0xffff;
		zr36060_ग_लिखो(ptr, ZR060_TCV_NET_ML, पंचांगp >> 8);
		zr36060_ग_लिखो(ptr, ZR060_TCV_NET_LO, पंचांगp & 0xff);

		bitcnt -= bitcnt >> 7;	// bits without stuffing
		bitcnt -= ((bitcnt * 5) >> 6);	// bits without eob

		पंचांगp = bitcnt >> 16;
		dprपूर्णांकk(3, "%s: code: nettobit=%ld, highnettobits=%ld\n",
			ptr->name, bitcnt, पंचांगp);
		zr36060_ग_लिखो(ptr, ZR060_TCV_DATA_HI, पंचांगp >> 8);
		zr36060_ग_लिखो(ptr, ZR060_TCV_DATA_MH, पंचांगp & 0xff);
		पंचांगp = bitcnt & 0xffff;
		zr36060_ग_लिखो(ptr, ZR060_TCV_DATA_ML, पंचांगp >> 8);
		zr36060_ग_लिखो(ptr, ZR060_TCV_DATA_LO, पंचांगp & 0xff);

		/* JPEG markers to be included in the compressed stream */
		zr36060_ग_लिखो(ptr, ZR060_MER,
			      ZR060_MER_DQT | ZR060_MER_DHT |
			      ((ptr->com.len > 0) ? ZR060_MER_COM : 0) |
			      ((ptr->app.len > 0) ? ZR060_MER_APP : 0));

		/* Setup the Video Frontend */
		/* Limit pixel range to 16..235 as per CCIR-601 */
		zr36060_ग_लिखो(ptr, ZR060_VCR, ZR060_VCR_RANGE);

	पूर्ण अन्यथा अणु
		dprपूर्णांकk(2, "%s: EXPANSION SETUP\n", ptr->name);

		zr36060_ग_लिखो(ptr, ZR060_LOAD, ZR060_LOAD_SYNC_RST);

		/* 060 communicates with 067 in master mode */
		zr36060_ग_लिखो(ptr, ZR060_CIR, ZR060_CIR_CODE_MSTR);

		/* Decompression */
		zr36060_ग_लिखो(ptr, ZR060_CMR, 0);

		/* Must be zero */
		zr36060_ग_लिखो(ptr, ZR060_MBZ, 0x00);
		zr36060_ग_लिखो(ptr, ZR060_TCR_HI, 0x00);
		zr36060_ग_लिखो(ptr, ZR060_TCR_LO, 0x00);

		/* Disable all IRQs - no DataErr means स्वतःreset */
		zr36060_ग_लिखो(ptr, ZR060_IMR, 0);

		/* setup misc. data क्रम expansion */
		zr36060_ग_लिखो(ptr, ZR060_MER, 0);

/* setup the fixed jpeg tables - maybe variable, though - (see table init section above) */
		zr36060_pushit(ptr, ZR060_DHT_IDX, माप(zr36060_dht), zr36060_dht);

		/* Setup the Video Frontend */
		//zr36060_ग_लिखो(ptr, ZR060_VCR, ZR060_VCR_FI_EXT);
		//this करोesn't seem right and doesn't work...
		zr36060_ग_लिखो(ptr, ZR060_VCR, ZR060_VCR_RANGE);
	पूर्ण

	/* Load the tables */
	zr36060_ग_लिखो(ptr, ZR060_LOAD, ZR060_LOAD_SYNC_RST | ZR060_LOAD_LOAD);
	zr36060_रुको_end(ptr);
	dprपूर्णांकk(2, "%s: Status after table preload: 0x%02x\n", ptr->name, ptr->status);

	अगर (ptr->status & ZR060_CFSR_BUSY) अणु
		pr_err("%s: init aborted!\n", ptr->name);
		वापस;		// something is wrong, its समयd out!!!!
	पूर्ण
पूर्ण

/* =========================================================================
 * CODEC API FUNCTIONS
 * this functions are accessed by the master via the API काष्ठाure
 * =========================================================================
 */

/* set compressiion/expansion mode and launches codec -
 * this should be the last call from the master beक्रमe starting processing
 */
अटल पूर्णांक zr36060_set_mode(काष्ठा videocodec *codec, पूर्णांक mode)
अणु
	काष्ठा zr36060 *ptr = (काष्ठा zr36060 *)codec->data;

	dprपूर्णांकk(2, "%s: set_mode %d call\n", ptr->name, mode);

	अगर (mode != CODEC_DO_EXPANSION && mode != CODEC_DO_COMPRESSION)
		वापस -EINVAL;

	ptr->mode = mode;
	zr36060_init(ptr);

	वापस 0;
पूर्ण

/* set picture size (norm is ignored as the codec करोesn't know about it) */
अटल पूर्णांक zr36060_set_video(काष्ठा videocodec *codec, स्थिर काष्ठा tvnorm *norm,
			     काष्ठा vfe_settings *cap, काष्ठा vfe_polarity *pol)
अणु
	काष्ठा zr36060 *ptr = (काष्ठा zr36060 *)codec->data;
	u32 reg;
	पूर्णांक size;

	dprपूर्णांकk(2, "%s: set_video %d/%d-%dx%d (%%%d) call\n", ptr->name,
		cap->x, cap->y, cap->width, cap->height, cap->decimation);

	/* अगर () वापस -EINVAL;
	 * trust the master driver that it knows what it करोes - so
	 * we allow invalid startx/y and norm क्रम now ...
	 */
	ptr->width = cap->width / (cap->decimation & 0xff);
	ptr->height = cap->height / (cap->decimation >> 8);

	zr36060_ग_लिखो(ptr, ZR060_LOAD, ZR060_LOAD_SYNC_RST);

	/* Note that VSPol/HSPol bits in zr36060 have the opposite
	 * meaning of their zr360x7 counterparts with the same names
	 * N.b. क्रम VSPol this is only true अगर FIVEdge = 0 (शेष,
	 * left unchanged here - in accordance with datasheet).
	 */
	reg = (!pol->vsync_pol ? ZR060_VPR_VS_POL : 0)
	    | (!pol->hsync_pol ? ZR060_VPR_HS_POL : 0)
	    | (pol->field_pol ? ZR060_VPR_FI_POL : 0)
	    | (pol->blank_pol ? ZR060_VPR_BL_POL : 0)
	    | (pol->subimg_pol ? ZR060_VPR_S_IMG_POL : 0)
	    | (pol->poe_pol ? ZR060_VPR_POE_POL : 0)
	    | (pol->pvalid_pol ? ZR060_VPR_P_VAL_POL : 0)
	    | (pol->vclk_pol ? ZR060_VPR_VCLK_POL : 0);
	zr36060_ग_लिखो(ptr, ZR060_VPR, reg);

	reg = 0;
	चयन (cap->decimation & 0xff) अणु
	शेष:
	हाल 1:
		अवरोध;

	हाल 2:
		reg |= ZR060_SR_H_SCALE2;
		अवरोध;

	हाल 4:
		reg |= ZR060_SR_H_SCALE4;
		अवरोध;
	पूर्ण

	चयन (cap->decimation >> 8) अणु
	शेष:
	हाल 1:
		अवरोध;

	हाल 2:
		reg |= ZR060_SR_V_SCALE;
		अवरोध;
	पूर्ण
	zr36060_ग_लिखो(ptr, ZR060_SR, reg);

	zr36060_ग_लिखो(ptr, ZR060_BCR_Y, 0x00);
	zr36060_ग_लिखो(ptr, ZR060_BCR_U, 0x80);
	zr36060_ग_लिखो(ptr, ZR060_BCR_V, 0x80);

	/* sync generator */

	reg = norm->ht - 1;	/* Vtotal */
	zr36060_ग_लिखो(ptr, ZR060_SGR_VTOTAL_HI, (reg >> 8) & 0xff);
	zr36060_ग_लिखो(ptr, ZR060_SGR_VTOTAL_LO, (reg >> 0) & 0xff);

	reg = norm->wt - 1;	/* Htotal */
	zr36060_ग_लिखो(ptr, ZR060_SGR_HTOTAL_HI, (reg >> 8) & 0xff);
	zr36060_ग_लिखो(ptr, ZR060_SGR_HTOTAL_LO, (reg >> 0) & 0xff);

	reg = 6 - 1;		/* VsyncSize */
	zr36060_ग_लिखो(ptr, ZR060_SGR_VSYNC, reg);

	//reg   = 30 - 1;               /* HsyncSize */
///*CP*/        reg = (zr->params.norm == 1 ? 57 : 68);
	reg = 68;
	zr36060_ग_लिखो(ptr, ZR060_SGR_HSYNC, reg);

	reg = norm->v_start - 1;	/* BVstart */
	zr36060_ग_लिखो(ptr, ZR060_SGR_BVSTART, reg);

	reg += norm->ha / 2;	/* BVend */
	zr36060_ग_लिखो(ptr, ZR060_SGR_BVEND_HI, (reg >> 8) & 0xff);
	zr36060_ग_लिखो(ptr, ZR060_SGR_BVEND_LO, (reg >> 0) & 0xff);

	reg = norm->h_start - 1;	/* BHstart */
	zr36060_ग_लिखो(ptr, ZR060_SGR_BHSTART, reg);

	reg += norm->wa;	/* BHend */
	zr36060_ग_लिखो(ptr, ZR060_SGR_BHEND_HI, (reg >> 8) & 0xff);
	zr36060_ग_लिखो(ptr, ZR060_SGR_BHEND_LO, (reg >> 0) & 0xff);

	/* active area */
	reg = cap->y + norm->v_start;	/* Vstart */
	zr36060_ग_लिखो(ptr, ZR060_AAR_VSTART_HI, (reg >> 8) & 0xff);
	zr36060_ग_लिखो(ptr, ZR060_AAR_VSTART_LO, (reg >> 0) & 0xff);

	reg += cap->height;	/* Vend */
	zr36060_ग_लिखो(ptr, ZR060_AAR_VEND_HI, (reg >> 8) & 0xff);
	zr36060_ग_लिखो(ptr, ZR060_AAR_VEND_LO, (reg >> 0) & 0xff);

	reg = cap->x + norm->h_start;	/* Hstart */
	zr36060_ग_लिखो(ptr, ZR060_AAR_HSTART_HI, (reg >> 8) & 0xff);
	zr36060_ग_लिखो(ptr, ZR060_AAR_HSTART_LO, (reg >> 0) & 0xff);

	reg += cap->width;	/* Hend */
	zr36060_ग_लिखो(ptr, ZR060_AAR_HEND_HI, (reg >> 8) & 0xff);
	zr36060_ग_लिखो(ptr, ZR060_AAR_HEND_LO, (reg >> 0) & 0xff);

	/* subimage area */
	reg = norm->v_start - 4;	/* SVstart */
	zr36060_ग_लिखो(ptr, ZR060_SWR_VSTART_HI, (reg >> 8) & 0xff);
	zr36060_ग_लिखो(ptr, ZR060_SWR_VSTART_LO, (reg >> 0) & 0xff);

	reg += norm->ha / 2 + 8;	/* SVend */
	zr36060_ग_लिखो(ptr, ZR060_SWR_VEND_HI, (reg >> 8) & 0xff);
	zr36060_ग_लिखो(ptr, ZR060_SWR_VEND_LO, (reg >> 0) & 0xff);

	reg = norm->h_start /*+ 64 */  - 4;	/* SHstart */
	zr36060_ग_लिखो(ptr, ZR060_SWR_HSTART_HI, (reg >> 8) & 0xff);
	zr36060_ग_लिखो(ptr, ZR060_SWR_HSTART_LO, (reg >> 0) & 0xff);

	reg += norm->wa + 8;	/* SHend */
	zr36060_ग_लिखो(ptr, ZR060_SWR_HEND_HI, (reg >> 8) & 0xff);
	zr36060_ग_लिखो(ptr, ZR060_SWR_HEND_LO, (reg >> 0) & 0xff);

	size = ptr->width * ptr->height;
	/* Target compressed field size in bits: */
	size = size * 16;	/* uncompressed size in bits */
	/* (Ronald) by शेष, quality = 100 is a compression
	 * ratio 1:2. Setting low_bitrate (insmod option) sets
	 * it to 1:4 (instead of 1:2, zr36060 max) as limit because the
	 * buz can't handle more at decimation=1... Use low_bitrate अगर
	 * you have a Buz, unless you know what you're करोing
	 */
	size = size * cap->quality / (low_bitrate ? 400 : 200);
	/* Lower limit (arbitrary, 1 KB) */
	अगर (size < 8192)
		size = 8192;
	/* Upper limit: 7/8 of the code buffers */
	अगर (size > ptr->total_code_vol * 7)
		size = ptr->total_code_vol * 7;

	ptr->real_code_vol = size >> 3;	/* in bytes */

	/* the MBCVR is the *maximum* block volume, according to the
	 * JPEG ISO specs, this shouldn't be used, since that allows
	 * क्रम the best encoding quality. So set it to it's max value
	 */
	reg = ptr->max_block_vol;
	zr36060_ग_लिखो(ptr, ZR060_MBCVR, reg);

	वापस 0;
पूर्ण

/* additional control functions */
अटल पूर्णांक zr36060_control(काष्ठा videocodec *codec, पूर्णांक type, पूर्णांक size, व्योम *data)
अणु
	काष्ठा zr36060 *ptr = (काष्ठा zr36060 *)codec->data;
	पूर्णांक *ival = (पूर्णांक *)data;

	dprपूर्णांकk(2, "%s: control %d call with %d byte\n", ptr->name, type,
		size);

	चयन (type) अणु
	हाल CODEC_G_STATUS:	/* get last status */
		अगर (size != माप(पूर्णांक))
			वापस -EFAULT;
		zr36060_पढ़ो_status(ptr);
		*ival = ptr->status;
		अवरोध;

	हाल CODEC_G_CODEC_MODE:
		अगर (size != माप(पूर्णांक))
			वापस -EFAULT;
		*ival = CODEC_MODE_BJPG;
		अवरोध;

	हाल CODEC_S_CODEC_MODE:
		अगर (size != माप(पूर्णांक))
			वापस -EFAULT;
		अगर (*ival != CODEC_MODE_BJPG)
			वापस -EINVAL;
		/* not needed, करो nothing */
		वापस 0;

	हाल CODEC_G_VFE:
	हाल CODEC_S_VFE:
		/* not needed, करो nothing */
		वापस 0;

	हाल CODEC_S_MMAP:
		/* not available, give an error */
		वापस -ENXIO;

	हाल CODEC_G_JPEG_TDS_BYTE:	/* get target volume in byte */
		अगर (size != माप(पूर्णांक))
			वापस -EFAULT;
		*ival = ptr->total_code_vol;
		अवरोध;

	हाल CODEC_S_JPEG_TDS_BYTE:	/* get target volume in byte */
		अगर (size != माप(पूर्णांक))
			वापस -EFAULT;
		ptr->total_code_vol = *ival;
		ptr->real_code_vol = (ptr->total_code_vol * 6) >> 3;
		अवरोध;

	हाल CODEC_G_JPEG_SCALE:	/* get scaling factor */
		अगर (size != माप(पूर्णांक))
			वापस -EFAULT;
		*ival = zr36060_पढ़ो_scalefactor(ptr);
		अवरोध;

	हाल CODEC_S_JPEG_SCALE:	/* set scaling factor */
		अगर (size != माप(पूर्णांक))
			वापस -EFAULT;
		ptr->scalefact = *ival;
		अवरोध;

	हाल CODEC_G_JPEG_APP_DATA: अणु	/* get appn marker data */
		काष्ठा jpeg_app_marker *app = data;

		अगर (size != माप(काष्ठा jpeg_app_marker))
			वापस -EFAULT;

		*app = ptr->app;
		अवरोध;
	पूर्ण

	हाल CODEC_S_JPEG_APP_DATA: अणु	/* set appn marker data */
		काष्ठा jpeg_app_marker *app = data;

		अगर (size != माप(काष्ठा jpeg_app_marker))
			वापस -EFAULT;

		ptr->app = *app;
		अवरोध;
	पूर्ण

	हाल CODEC_G_JPEG_COM_DATA: अणु	/* get comment marker data */
		काष्ठा jpeg_com_marker *com = data;

		अगर (size != माप(काष्ठा jpeg_com_marker))
			वापस -EFAULT;

		*com = ptr->com;
		अवरोध;
	पूर्ण

	हाल CODEC_S_JPEG_COM_DATA: अणु	/* set comment marker data */
		काष्ठा jpeg_com_marker *com = data;

		अगर (size != माप(काष्ठा jpeg_com_marker))
			वापस -EFAULT;

		ptr->com = *com;
		अवरोध;
	पूर्ण

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस size;
पूर्ण

/* =========================================================================
 * Exit and unरेजिस्टर function:
 * Deinitializes Zoran's JPEG processor
 * =========================================================================
 */
अटल पूर्णांक zr36060_unset(काष्ठा videocodec *codec)
अणु
	काष्ठा zr36060 *ptr = codec->data;

	अगर (ptr) अणु
		/* करो wee need some codec deinit here, too ???? */

		dprपूर्णांकk(1, "%s: finished codec #%d\n", ptr->name, ptr->num);
		kमुक्त(ptr);
		codec->data = शून्य;

		zr36060_codecs--;
		वापस 0;
	पूर्ण

	वापस -EFAULT;
पूर्ण

/* =========================================================================
 * Setup and registry function:
 * Initializes Zoran's JPEG processor
 * Also sets pixel size, average code size, mode (compr./decompr.)
 * (the given size is determined by the processor with the video पूर्णांकerface)
 * =========================================================================
 */
अटल पूर्णांक zr36060_setup(काष्ठा videocodec *codec)
अणु
	काष्ठा zr36060 *ptr;
	पूर्णांक res;

	dprपूर्णांकk(2, "zr36060: initializing MJPEG subsystem #%d.\n", zr36060_codecs);

	अगर (zr36060_codecs == MAX_CODECS) अणु
		pr_err("zr36060: Can't attach more codecs!\n");
		वापस -ENOSPC;
	पूर्ण
	//mem काष्ठाure init
	codec->data = ptr = kzalloc(माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	snम_लिखो(ptr->name, माप(ptr->name), "zr36060[%d]", zr36060_codecs);
	ptr->num = zr36060_codecs++;
	ptr->codec = codec;

	//testing
	res = zr36060_basic_test(ptr);
	अगर (res < 0) अणु
		zr36060_unset(codec);
		वापस res;
	पूर्ण
	//final setup
	स_नकल(ptr->h_samp_ratio, zr36060_decimation_h, 8);
	स_नकल(ptr->v_samp_ratio, zr36060_decimation_v, 8);

	ptr->bitrate_ctrl = 0;	/* 0 or 1 - fixed file size flag (what is the dअगरference?) */
	ptr->mode = CODEC_DO_COMPRESSION;
	ptr->width = 384;
	ptr->height = 288;
	ptr->total_code_vol = 16000;	/* CHECKME */
	ptr->real_code_vol = (ptr->total_code_vol * 6) >> 3;
	ptr->max_block_vol = 240;	/* CHECKME, was 120 is 240 */
	ptr->scalefact = 0x100;
	ptr->dri = 1;		/* CHECKME, was 8 is 1 */

	/* by शेष, no COM or APP markers - app should set those */
	ptr->com.len = 0;
	ptr->app.appn = 0;
	ptr->app.len = 0;

	zr36060_init(ptr);

	dprपूर्णांकk(1, KERN_INFO "%s: codec attached and running\n", ptr->name);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा videocodec zr36060_codec = अणु
	.owner = THIS_MODULE,
	.name = "zr36060",
	.magic = 0L,		// magic not used
	.flags =
	    CODEC_FLAG_JPEG | CODEC_FLAG_HARDWARE | CODEC_FLAG_ENCODER |
	    CODEC_FLAG_DECODER | CODEC_FLAG_VFE,
	.type = CODEC_TYPE_ZR36060,
	.setup = zr36060_setup,	// functionality
	.unset = zr36060_unset,
	.set_mode = zr36060_set_mode,
	.set_video = zr36060_set_video,
	.control = zr36060_control,
	// others are not used
पूर्ण;

अटल पूर्णांक __init zr36060_init_module(व्योम)
अणु
	zr36060_codecs = 0;
	वापस videocodec_रेजिस्टर(&zr36060_codec);
पूर्ण

अटल व्योम __निकास zr36060_cleanup_module(व्योम)
अणु
	अगर (zr36060_codecs) अणु
		dprपूर्णांकk(1,
			"zr36060: something's wrong - %d codecs left somehow.\n",
			zr36060_codecs);
	पूर्ण

	/* however, we can't just stay alive */
	videocodec_unरेजिस्टर(&zr36060_codec);
पूर्ण

module_init(zr36060_init_module);
module_निकास(zr36060_cleanup_module);

MODULE_AUTHOR("Laurent Pinchart <laurent.pinchart@skynet.be>");
MODULE_DESCRIPTION("Driver module for ZR36060 jpeg processors " ZR060_VERSION);
MODULE_LICENSE("GPL");
