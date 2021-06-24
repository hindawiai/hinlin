<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम mt2063 Micronas tuner
 *
 * Copyright (c) 2011 Mauro Carvalho Chehab
 *
 * This driver came from a driver originally written by:
 *		Henry Wang <Henry.wang@AzureWave.com>
 * Made खुलाly available by Terratec, at:
 *	http://linux.terratec.de/files/TERRATEC_H7/20110323_TERRATEC_H7_Linux.tar.gz
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/videodev2.h>
#समावेश <linux/gcd.h>

#समावेश "mt2063.h"

अटल अचिन्हित पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Set Verbosity level");

#घोषणा dprपूर्णांकk(level, fmt, arg...) करो अणु				\
अगर (debug >= level)							\
	prपूर्णांकk(KERN_DEBUG "mt2063 %s: " fmt, __func__, ## arg);	\
पूर्ण जबतक (0)


/* positive error codes used पूर्णांकernally */

/*  Info: Unaव्योमable LO-related spur may be present in the output  */
#घोषणा MT2063_SPUR_PRESENT_ERR             (0x00800000)

/*  Info: Mask of bits used क्रम # of LO-related spurs that were aव्योमed during tuning  */
#घोषणा MT2063_SPUR_CNT_MASK                (0x001f0000)
#घोषणा MT2063_SPUR_SHIFT                   (16)

/*  Info: Upconverter frequency is out of range (may be reason क्रम MT_UPC_UNLOCK) */
#घोषणा MT2063_UPC_RANGE                    (0x04000000)

/*  Info: Downconverter frequency is out of range (may be reason क्रम MT_DPC_UNLOCK) */
#घोषणा MT2063_DNC_RANGE                    (0x08000000)

/*
 *  Constant defining the version of the following काष्ठाure
 *  and thereक्रमe the API क्रम this code.
 *
 *  When compiling the tuner driver, the preprocessor will
 *  check against this version number to make sure that
 *  it matches the version that the tuner driver knows about.
 */

/* DECT Frequency Aव्योमance */
#घोषणा MT2063_DECT_AVOID_US_FREQS      0x00000001

#घोषणा MT2063_DECT_AVOID_EURO_FREQS    0x00000002

#घोषणा MT2063_EXCLUDE_US_DECT_FREQUENCIES(s) (((s) & MT2063_DECT_AVOID_US_FREQS) != 0)

#घोषणा MT2063_EXCLUDE_EURO_DECT_FREQUENCIES(s) (((s) & MT2063_DECT_AVOID_EURO_FREQS) != 0)

क्रमागत MT2063_DECT_Aव्योम_Type अणु
	MT2063_NO_DECT_AVOIDANCE = 0,				/* Do not create DECT exclusion zones.     */
	MT2063_AVOID_US_DECT = MT2063_DECT_AVOID_US_FREQS,	/* Aव्योम US DECT frequencies.              */
	MT2063_AVOID_EURO_DECT = MT2063_DECT_AVOID_EURO_FREQS,	/* Aव्योम European DECT frequencies.        */
	MT2063_AVOID_BOTH					/* Aव्योम both regions. Not typically used. */
पूर्ण;

#घोषणा MT2063_MAX_ZONES 48

काष्ठा MT2063_ExclZone_t अणु
	u32 min_;
	u32 max_;
	काष्ठा MT2063_ExclZone_t *next_;
पूर्ण;

/*
 *  Structure of data needed क्रम Spur Aव्योमance
 */
काष्ठा MT2063_Aव्योमSpursData_t अणु
	u32 f_ref;
	u32 f_in;
	u32 f_LO1;
	u32 f_अगर1_Center;
	u32 f_अगर1_Request;
	u32 f_अगर1_bw;
	u32 f_LO2;
	u32 f_out;
	u32 f_out_bw;
	u32 f_LO1_Step;
	u32 f_LO2_Step;
	u32 f_LO1_FracN_Aव्योम;
	u32 f_LO2_FracN_Aव्योम;
	u32 f_zअगर_bw;
	u32 f_min_LO_Separation;
	u32 maxH1;
	u32 maxH2;
	क्रमागत MT2063_DECT_Aव्योम_Type aव्योमDECT;
	u32 bSpurPresent;
	u32 bSpurAव्योमed;
	u32 nSpursFound;
	u32 nZones;
	काष्ठा MT2063_ExclZone_t *मुक्तZones;
	काष्ठा MT2063_ExclZone_t *usedZones;
	काष्ठा MT2063_ExclZone_t MT2063_ExclZones[MT2063_MAX_ZONES];
पूर्ण;

/*
 * Parameter क्रम function MT2063_SetPowerMask that specअगरies the घातer करोwn
 * of various sections of the MT2063.
 */
क्रमागत MT2063_Mask_Bits अणु
	MT2063_REG_SD = 0x0040,		/* Shutकरोwn regulator                 */
	MT2063_SRO_SD = 0x0020,		/* Shutकरोwn SRO                       */
	MT2063_AFC_SD = 0x0010,		/* Shutकरोwn AFC A/D                   */
	MT2063_PD_SD = 0x0002,		/* Enable घातer detector shutकरोwn     */
	MT2063_PDADC_SD = 0x0001,	/* Enable घातer detector A/D shutकरोwn */
	MT2063_VCO_SD = 0x8000,		/* Enable VCO shutकरोwn                */
	MT2063_LTX_SD = 0x4000,		/* Enable LTX shutकरोwn                */
	MT2063_LT1_SD = 0x2000,		/* Enable LT1 shutकरोwn                */
	MT2063_LNA_SD = 0x1000,		/* Enable LNA shutकरोwn                */
	MT2063_UPC_SD = 0x0800,		/* Enable upconverter shutकरोwn        */
	MT2063_DNC_SD = 0x0400,		/* Enable करोwnconverter shutकरोwn      */
	MT2063_VGA_SD = 0x0200,		/* Enable VGA shutकरोwn                */
	MT2063_AMP_SD = 0x0100,		/* Enable AMP shutकरोwn                */
	MT2063_ALL_SD = 0xFF73,		/* All shutकरोwn bits क्रम this tuner   */
	MT2063_NONE_SD = 0x0000		/* No shutकरोwn bits                   */
पूर्ण;

/*
 *  Possible values क्रम MT2063_DNC_OUTPUT
 */
क्रमागत MT2063_DNC_Output_Enable अणु
	MT2063_DNC_NONE = 0,
	MT2063_DNC_1,
	MT2063_DNC_2,
	MT2063_DNC_BOTH
पूर्ण;

/*
 *  Two-wire serial bus subaddresses of the tuner रेजिस्टरs.
 *  Also known as the tuner's रेजिस्टर addresses.
 */
क्रमागत MT2063_Register_Offsets अणु
	MT2063_REG_PART_REV = 0,	/*  0x00: Part/Rev Code         */
	MT2063_REG_LO1CQ_1,		/*  0x01: LO1C Queued Byte 1    */
	MT2063_REG_LO1CQ_2,		/*  0x02: LO1C Queued Byte 2    */
	MT2063_REG_LO2CQ_1,		/*  0x03: LO2C Queued Byte 1    */
	MT2063_REG_LO2CQ_2,		/*  0x04: LO2C Queued Byte 2    */
	MT2063_REG_LO2CQ_3,		/*  0x05: LO2C Queued Byte 3    */
	MT2063_REG_RSVD_06,		/*  0x06: Reserved              */
	MT2063_REG_LO_STATUS,		/*  0x07: LO Status             */
	MT2063_REG_FIFFC,		/*  0x08: FIFF Center           */
	MT2063_REG_CLEARTUNE,		/*  0x09: ClearTune Filter      */
	MT2063_REG_ADC_OUT,		/*  0x0A: ADC_OUT               */
	MT2063_REG_LO1C_1,		/*  0x0B: LO1C Byte 1           */
	MT2063_REG_LO1C_2,		/*  0x0C: LO1C Byte 2           */
	MT2063_REG_LO2C_1,		/*  0x0D: LO2C Byte 1           */
	MT2063_REG_LO2C_2,		/*  0x0E: LO2C Byte 2           */
	MT2063_REG_LO2C_3,		/*  0x0F: LO2C Byte 3           */
	MT2063_REG_RSVD_10,		/*  0x10: Reserved              */
	MT2063_REG_PWR_1,		/*  0x11: PWR Byte 1            */
	MT2063_REG_PWR_2,		/*  0x12: PWR Byte 2            */
	MT2063_REG_TEMP_STATUS,		/*  0x13: Temp Status           */
	MT2063_REG_XO_STATUS,		/*  0x14: Crystal Status        */
	MT2063_REG_RF_STATUS,		/*  0x15: RF Attn Status        */
	MT2063_REG_FIF_STATUS,		/*  0x16: FIF Attn Status       */
	MT2063_REG_LNA_OV,		/*  0x17: LNA Attn Override     */
	MT2063_REG_RF_OV,		/*  0x18: RF Attn Override      */
	MT2063_REG_FIF_OV,		/*  0x19: FIF Attn Override     */
	MT2063_REG_LNA_TGT,		/*  0x1A: Reserved              */
	MT2063_REG_PD1_TGT,		/*  0x1B: Pwr Det 1 Target      */
	MT2063_REG_PD2_TGT,		/*  0x1C: Pwr Det 2 Target      */
	MT2063_REG_RSVD_1D,		/*  0x1D: Reserved              */
	MT2063_REG_RSVD_1E,		/*  0x1E: Reserved              */
	MT2063_REG_RSVD_1F,		/*  0x1F: Reserved              */
	MT2063_REG_RSVD_20,		/*  0x20: Reserved              */
	MT2063_REG_BYP_CTRL,		/*  0x21: Bypass Control        */
	MT2063_REG_RSVD_22,		/*  0x22: Reserved              */
	MT2063_REG_RSVD_23,		/*  0x23: Reserved              */
	MT2063_REG_RSVD_24,		/*  0x24: Reserved              */
	MT2063_REG_RSVD_25,		/*  0x25: Reserved              */
	MT2063_REG_RSVD_26,		/*  0x26: Reserved              */
	MT2063_REG_RSVD_27,		/*  0x27: Reserved              */
	MT2063_REG_FIFF_CTRL,		/*  0x28: FIFF Control          */
	MT2063_REG_FIFF_OFFSET,		/*  0x29: FIFF Offset           */
	MT2063_REG_CTUNE_CTRL,		/*  0x2A: Reserved              */
	MT2063_REG_CTUNE_OV,		/*  0x2B: Reserved              */
	MT2063_REG_CTRL_2C,		/*  0x2C: Reserved              */
	MT2063_REG_FIFF_CTRL2,		/*  0x2D: Fअगरf Control          */
	MT2063_REG_RSVD_2E,		/*  0x2E: Reserved              */
	MT2063_REG_DNC_GAIN,		/*  0x2F: DNC Control           */
	MT2063_REG_VGA_GAIN,		/*  0x30: VGA Gain Ctrl         */
	MT2063_REG_RSVD_31,		/*  0x31: Reserved              */
	MT2063_REG_TEMP_SEL,		/*  0x32: Temperature Selection */
	MT2063_REG_RSVD_33,		/*  0x33: Reserved              */
	MT2063_REG_RSVD_34,		/*  0x34: Reserved              */
	MT2063_REG_RSVD_35,		/*  0x35: Reserved              */
	MT2063_REG_RSVD_36,		/*  0x36: Reserved              */
	MT2063_REG_RSVD_37,		/*  0x37: Reserved              */
	MT2063_REG_RSVD_38,		/*  0x38: Reserved              */
	MT2063_REG_RSVD_39,		/*  0x39: Reserved              */
	MT2063_REG_RSVD_3A,		/*  0x3A: Reserved              */
	MT2063_REG_RSVD_3B,		/*  0x3B: Reserved              */
	MT2063_REG_RSVD_3C,		/*  0x3C: Reserved              */
	MT2063_REG_END_REGS
पूर्ण;

काष्ठा mt2063_state अणु
	काष्ठा i2c_adapter *i2c;

	bool init;

	स्थिर काष्ठा mt2063_config *config;
	काष्ठा dvb_tuner_ops ops;
	काष्ठा dvb_frontend *frontend;

	u32 frequency;
	u32 srate;
	u32 bandwidth;
	u32 reference;

	u32 tuner_id;
	काष्ठा MT2063_Aव्योमSpursData_t AS_Data;
	u32 f_IF1_actual;
	u32 rcvr_mode;
	u32 ctfilt_sw;
	u32 CTFiltMax[31];
	u32 num_regs;
	u8 reg[MT2063_REG_END_REGS];
पूर्ण;

/*
 * mt2063_ग_लिखो - Write data पूर्णांकo the I2C bus
 */
अटल पूर्णांक mt2063_ग_लिखो(काष्ठा mt2063_state *state, u8 reg, u8 *data, u32 len)
अणु
	काष्ठा dvb_frontend *fe = state->frontend;
	पूर्णांक ret;
	u8 buf[60];
	काष्ठा i2c_msg msg = अणु
		.addr = state->config->tuner_address,
		.flags = 0,
		.buf = buf,
		.len = len + 1
	पूर्ण;

	dprपूर्णांकk(2, "\n");

	msg.buf[0] = reg;
	स_नकल(msg.buf + 1, data, len);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	ret = i2c_transfer(state->i2c, &msg, 1);
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	अगर (ret < 0)
		prपूर्णांकk(KERN_ERR "%s error ret=%d\n", __func__, ret);

	वापस ret;
पूर्ण

/*
 * mt2063_ग_लिखो - Write रेजिस्टर data पूर्णांकo the I2C bus, caching the value
 */
अटल पूर्णांक mt2063_setreg(काष्ठा mt2063_state *state, u8 reg, u8 val)
अणु
	पूर्णांक status;

	dprपूर्णांकk(2, "\n");

	अगर (reg >= MT2063_REG_END_REGS)
		वापस -दुस्फल;

	status = mt2063_ग_लिखो(state, reg, &val, 1);
	अगर (status < 0)
		वापस status;

	state->reg[reg] = val;

	वापस 0;
पूर्ण

/*
 * mt2063_पढ़ो - Read data from the I2C bus
 */
अटल पूर्णांक mt2063_पढ़ो(काष्ठा mt2063_state *state,
			   u8 subAddress, u8 *pData, u32 cnt)
अणु
	पूर्णांक status = 0;	/* Status to be वापसed        */
	काष्ठा dvb_frontend *fe = state->frontend;
	u32 i = 0;

	dprपूर्णांकk(2, "addr 0x%02x, cnt %d\n", subAddress, cnt);

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	क्रम (i = 0; i < cnt; i++) अणु
		u8 b0[] = अणु subAddress + i पूर्ण;
		काष्ठा i2c_msg msg[] = अणु
			अणु
				.addr = state->config->tuner_address,
				.flags = 0,
				.buf = b0,
				.len = 1
			पूर्ण, अणु
				.addr = state->config->tuner_address,
				.flags = I2C_M_RD,
				.buf = pData + i,
				.len = 1
			पूर्ण
		पूर्ण;

		status = i2c_transfer(state->i2c, msg, 2);
		dprपूर्णांकk(2, "addr 0x%02x, ret = %d, val = 0x%02x\n",
			   subAddress + i, status, *(pData + i));
		अगर (status < 0)
			अवरोध;
	पूर्ण
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	अगर (status < 0)
		prपूर्णांकk(KERN_ERR "Can't read from address 0x%02x,\n",
		       subAddress + i);

	वापस status;
पूर्ण

/*
 * FIXME: Is this really needed?
 */
अटल पूर्णांक MT2063_Sleep(काष्ठा dvb_frontend *fe)
अणु
	/*
	 *  ToDo:  Add code here to implement a OS blocking
	 */
	msleep(100);

	वापस 0;
पूर्ण

/*
 * Microtune spur aव्योमance
 */

/*  Implement उच्चमानing, न्यूनमान functions.  */
#घोषणा उच्चमान(n, d) (((n) < 0) ? (-((-(n))/(d))) : (n)/(d) + ((n)%(d) != 0))
#घोषणा न्यूनमान(n, d) (((n) < 0) ? (-((-(n))/(d))) - ((n)%(d) != 0) : (n)/(d))

काष्ठा MT2063_FIFZone_t अणु
	s32 min_;
	s32 max_;
पूर्ण;

अटल काष्ठा MT2063_ExclZone_t *InsertNode(काष्ठा MT2063_Aव्योमSpursData_t
					    *pAS_Info,
					    काष्ठा MT2063_ExclZone_t *pPrevNode)
अणु
	काष्ठा MT2063_ExclZone_t *pNode;

	dprपूर्णांकk(2, "\n");

	/*  Check क्रम a node in the मुक्त list  */
	अगर (pAS_Info->मुक्तZones != शून्य) अणु
		/*  Use one from the मुक्त list  */
		pNode = pAS_Info->मुक्तZones;
		pAS_Info->मुक्तZones = pNode->next_;
	पूर्ण अन्यथा अणु
		/*  Grab a node from the array  */
		pNode = &pAS_Info->MT2063_ExclZones[pAS_Info->nZones];
	पूर्ण

	अगर (pPrevNode != शून्य) अणु
		pNode->next_ = pPrevNode->next_;
		pPrevNode->next_ = pNode;
	पूर्ण अन्यथा अणु		/*  insert at the beginning of the list  */

		pNode->next_ = pAS_Info->usedZones;
		pAS_Info->usedZones = pNode;
	पूर्ण

	pAS_Info->nZones++;
	वापस pNode;
पूर्ण

अटल काष्ठा MT2063_ExclZone_t *RemoveNode(काष्ठा MT2063_Aव्योमSpursData_t
					    *pAS_Info,
					    काष्ठा MT2063_ExclZone_t *pPrevNode,
					    काष्ठा MT2063_ExclZone_t
					    *pNodeToRemove)
अणु
	काष्ठा MT2063_ExclZone_t *pNext = pNodeToRemove->next_;

	dprपूर्णांकk(2, "\n");

	/*  Make previous node poपूर्णांक to the subsequent node  */
	अगर (pPrevNode != शून्य)
		pPrevNode->next_ = pNext;

	/*  Add pNodeToRemove to the beginning of the मुक्तZones  */
	pNodeToRemove->next_ = pAS_Info->मुक्तZones;
	pAS_Info->मुक्तZones = pNodeToRemove;

	/*  Decrement node count  */
	pAS_Info->nZones--;

	वापस pNext;
पूर्ण

/*
 * MT_AddExclZone()
 *
 * Add (and merge) an exclusion zone पूर्णांकo the list.
 * If the range (f_min, f_max) is totally outside the
 * 1st IF BW, ignore the entry.
 * If the range (f_min, f_max) is negative, ignore the entry.
 */
अटल व्योम MT2063_AddExclZone(काष्ठा MT2063_Aव्योमSpursData_t *pAS_Info,
			       u32 f_min, u32 f_max)
अणु
	काष्ठा MT2063_ExclZone_t *pNode = pAS_Info->usedZones;
	काष्ठा MT2063_ExclZone_t *pPrev = शून्य;
	काष्ठा MT2063_ExclZone_t *pNext = शून्य;

	dprपूर्णांकk(2, "\n");

	/*  Check to see अगर this overlaps the 1st IF filter  */
	अगर ((f_max > (pAS_Info->f_अगर1_Center - (pAS_Info->f_अगर1_bw / 2)))
	    && (f_min < (pAS_Info->f_अगर1_Center + (pAS_Info->f_अगर1_bw / 2)))
	    && (f_min < f_max)) अणु
		/*
		 *                1        2         3      4       5        6
		 *
		 *   New entry:  |---|    |--|      |--|    |-|    |---|    |--|
		 *                or       or        or     or      or
		 *   Existing:  |--|      |--|      |--|    |---|  |-|      |--|
		 */

		/*  Check क्रम our place in the list  */
		जबतक ((pNode != शून्य) && (pNode->max_ < f_min)) अणु
			pPrev = pNode;
			pNode = pNode->next_;
		पूर्ण

		अगर ((pNode != शून्य) && (pNode->min_ < f_max)) अणु
			/*  Combine me with pNode  */
			अगर (f_min < pNode->min_)
				pNode->min_ = f_min;
			अगर (f_max > pNode->max_)
				pNode->max_ = f_max;
		पूर्ण अन्यथा अणु
			pNode = InsertNode(pAS_Info, pPrev);
			pNode->min_ = f_min;
			pNode->max_ = f_max;
		पूर्ण

		/*  Look क्रम merging possibilities  */
		pNext = pNode->next_;
		जबतक ((pNext != शून्य) && (pNext->min_ < pNode->max_)) अणु
			अगर (pNext->max_ > pNode->max_)
				pNode->max_ = pNext->max_;
			/*  Remove pNext, वापस ptr to pNext->next  */
			pNext = RemoveNode(pAS_Info, pNode, pNext);
		पूर्ण
	पूर्ण
पूर्ण

/*
 *  Reset all exclusion zones.
 *  Add zones to protect the PLL FracN regions near zero
 */
अटल व्योम MT2063_ResetExclZones(काष्ठा MT2063_Aव्योमSpursData_t *pAS_Info)
अणु
	u32 center;

	dprपूर्णांकk(2, "\n");

	pAS_Info->nZones = 0;	/*  this clears the used list  */
	pAS_Info->usedZones = शून्य;	/*  reset ptr                  */
	pAS_Info->मुक्तZones = शून्य;	/*  reset ptr                  */

	center =
	    pAS_Info->f_ref *
	    ((pAS_Info->f_अगर1_Center - pAS_Info->f_अगर1_bw / 2 +
	      pAS_Info->f_in) / pAS_Info->f_ref) - pAS_Info->f_in;
	जबतक (center <
	       pAS_Info->f_अगर1_Center + pAS_Info->f_अगर1_bw / 2 +
	       pAS_Info->f_LO1_FracN_Aव्योम) अणु
		/*  Exclude LO1 FracN  */
		MT2063_AddExclZone(pAS_Info,
				   center - pAS_Info->f_LO1_FracN_Aव्योम,
				   center - 1);
		MT2063_AddExclZone(pAS_Info, center + 1,
				   center + pAS_Info->f_LO1_FracN_Aव्योम);
		center += pAS_Info->f_ref;
	पूर्ण

	center =
	    pAS_Info->f_ref *
	    ((pAS_Info->f_अगर1_Center - pAS_Info->f_अगर1_bw / 2 -
	      pAS_Info->f_out) / pAS_Info->f_ref) + pAS_Info->f_out;
	जबतक (center <
	       pAS_Info->f_अगर1_Center + pAS_Info->f_अगर1_bw / 2 +
	       pAS_Info->f_LO2_FracN_Aव्योम) अणु
		/*  Exclude LO2 FracN  */
		MT2063_AddExclZone(pAS_Info,
				   center - pAS_Info->f_LO2_FracN_Aव्योम,
				   center - 1);
		MT2063_AddExclZone(pAS_Info, center + 1,
				   center + pAS_Info->f_LO2_FracN_Aव्योम);
		center += pAS_Info->f_ref;
	पूर्ण

	अगर (MT2063_EXCLUDE_US_DECT_FREQUENCIES(pAS_Info->aव्योमDECT)) अणु
		/*  Exclude LO1 values that conflict with DECT channels */
		MT2063_AddExclZone(pAS_Info, 1920836000 - pAS_Info->f_in, 1922236000 - pAS_Info->f_in);	/* Ctr = 1921.536 */
		MT2063_AddExclZone(pAS_Info, 1922564000 - pAS_Info->f_in, 1923964000 - pAS_Info->f_in);	/* Ctr = 1923.264 */
		MT2063_AddExclZone(pAS_Info, 1924292000 - pAS_Info->f_in, 1925692000 - pAS_Info->f_in);	/* Ctr = 1924.992 */
		MT2063_AddExclZone(pAS_Info, 1926020000 - pAS_Info->f_in, 1927420000 - pAS_Info->f_in);	/* Ctr = 1926.720 */
		MT2063_AddExclZone(pAS_Info, 1927748000 - pAS_Info->f_in, 1929148000 - pAS_Info->f_in);	/* Ctr = 1928.448 */
	पूर्ण

	अगर (MT2063_EXCLUDE_EURO_DECT_FREQUENCIES(pAS_Info->aव्योमDECT)) अणु
		MT2063_AddExclZone(pAS_Info, 1896644000 - pAS_Info->f_in, 1898044000 - pAS_Info->f_in);	/* Ctr = 1897.344 */
		MT2063_AddExclZone(pAS_Info, 1894916000 - pAS_Info->f_in, 1896316000 - pAS_Info->f_in);	/* Ctr = 1895.616 */
		MT2063_AddExclZone(pAS_Info, 1893188000 - pAS_Info->f_in, 1894588000 - pAS_Info->f_in);	/* Ctr = 1893.888 */
		MT2063_AddExclZone(pAS_Info, 1891460000 - pAS_Info->f_in, 1892860000 - pAS_Info->f_in);	/* Ctr = 1892.16  */
		MT2063_AddExclZone(pAS_Info, 1889732000 - pAS_Info->f_in, 1891132000 - pAS_Info->f_in);	/* Ctr = 1890.432 */
		MT2063_AddExclZone(pAS_Info, 1888004000 - pAS_Info->f_in, 1889404000 - pAS_Info->f_in);	/* Ctr = 1888.704 */
		MT2063_AddExclZone(pAS_Info, 1886276000 - pAS_Info->f_in, 1887676000 - pAS_Info->f_in);	/* Ctr = 1886.976 */
		MT2063_AddExclZone(pAS_Info, 1884548000 - pAS_Info->f_in, 1885948000 - pAS_Info->f_in);	/* Ctr = 1885.248 */
		MT2063_AddExclZone(pAS_Info, 1882820000 - pAS_Info->f_in, 1884220000 - pAS_Info->f_in);	/* Ctr = 1883.52  */
		MT2063_AddExclZone(pAS_Info, 1881092000 - pAS_Info->f_in, 1882492000 - pAS_Info->f_in);	/* Ctr = 1881.792 */
	पूर्ण
पूर्ण

/*
 * MT_ChooseFirstIF - Choose the best available 1st IF
 *                    If f_Desired is not excluded, choose that first.
 *                    Otherwise, वापस the value बंदst to f_Center that is
 *                    not excluded
 */
अटल u32 MT2063_ChooseFirstIF(काष्ठा MT2063_Aव्योमSpursData_t *pAS_Info)
अणु
	/*
	 * Update "f_Desired" to be the nearest "combinational-multiple" of
	 * "f_LO1_Step".
	 * The resulting number, F_LO1 must be a multiple of f_LO1_Step.
	 * And F_LO1 is the arithmetic sum of f_in + f_Center.
	 * Neither f_in, nor f_Center must be a multiple of f_LO1_Step.
	 * However, the sum must be.
	 */
	स्थिर u32 f_Desired =
	    pAS_Info->f_LO1_Step *
	    ((pAS_Info->f_अगर1_Request + pAS_Info->f_in +
	      pAS_Info->f_LO1_Step / 2) / pAS_Info->f_LO1_Step) -
	    pAS_Info->f_in;
	स्थिर u32 f_Step =
	    (pAS_Info->f_LO1_Step >
	     pAS_Info->f_LO2_Step) ? pAS_Info->f_LO1_Step : pAS_Info->
	    f_LO2_Step;
	u32 f_Center;
	s32 i;
	s32 j = 0;
	u32 bDesiredExcluded = 0;
	u32 bZeroExcluded = 0;
	s32 पंचांगpMin, पंचांगpMax;
	s32 bestDअगरf;
	काष्ठा MT2063_ExclZone_t *pNode = pAS_Info->usedZones;
	काष्ठा MT2063_FIFZone_t zones[MT2063_MAX_ZONES];

	dprपूर्णांकk(2, "\n");

	अगर (pAS_Info->nZones == 0)
		वापस f_Desired;

	/*
	 *  f_Center needs to be an पूर्णांकeger multiple of f_Step away
	 *  from f_Desired
	 */
	अगर (pAS_Info->f_अगर1_Center > f_Desired)
		f_Center =
		    f_Desired +
		    f_Step *
		    ((pAS_Info->f_अगर1_Center - f_Desired +
		      f_Step / 2) / f_Step);
	अन्यथा
		f_Center =
		    f_Desired -
		    f_Step *
		    ((f_Desired - pAS_Info->f_अगर1_Center +
		      f_Step / 2) / f_Step);

	/*
	 * Take MT_ExclZones, center around f_Center and change the
	 * resolution to f_Step
	 */
	जबतक (pNode != शून्य) अणु
		/*  न्यूनमान function  */
		पंचांगpMin =
		    न्यूनमान((s32) (pNode->min_ - f_Center), (s32) f_Step);

		/*  उच्चमान function  */
		पंचांगpMax =
		    उच्चमान((s32) (pNode->max_ - f_Center), (s32) f_Step);

		अगर ((pNode->min_ < f_Desired) && (pNode->max_ > f_Desired))
			bDesiredExcluded = 1;

		अगर ((पंचांगpMin < 0) && (पंचांगpMax > 0))
			bZeroExcluded = 1;

		/*  See अगर this zone overlaps the previous  */
		अगर ((j > 0) && (पंचांगpMin < zones[j - 1].max_))
			zones[j - 1].max_ = पंचांगpMax;
		अन्यथा अणु
			/*  Add new zone  */
			zones[j].min_ = पंचांगpMin;
			zones[j].max_ = पंचांगpMax;
			j++;
		पूर्ण
		pNode = pNode->next_;
	पूर्ण

	/*
	 *  If the desired is okay, वापस with it
	 */
	अगर (bDesiredExcluded == 0)
		वापस f_Desired;

	/*
	 *  If the desired is excluded and the center is okay, वापस with it
	 */
	अगर (bZeroExcluded == 0)
		वापस f_Center;

	/*  Find the value बंदst to 0 (f_Center)  */
	bestDअगरf = zones[0].min_;
	क्रम (i = 0; i < j; i++) अणु
		अगर (असल(zones[i].min_) < असल(bestDअगरf))
			bestDअगरf = zones[i].min_;
		अगर (असल(zones[i].max_) < असल(bestDअगरf))
			bestDअगरf = zones[i].max_;
	पूर्ण

	अगर (bestDअगरf < 0)
		वापस f_Center - ((u32) (-bestDअगरf) * f_Step);

	वापस f_Center + (bestDअगरf * f_Step);
पूर्ण

/**
 * IsSpurInBand() - Checks to see अगर a spur will be present within the IF's
 *                  bandwidth. (fIFOut +/- fIFBW, -fIFOut +/- fIFBW)
 *
 *                    ma   mb                                     mc   md
 *                  <--+-+-+-------------------+-------------------+-+-+-->
 *                     |   ^                   0                   ^   |
 *                     ^   b=-fIFOut+fIFBW/2      -b=+fIFOut-fIFBW/2   ^
 *                     a=-fIFOut-fIFBW/2              -a=+fIFOut+fIFBW/2
 *
 *                  Note that some equations are द्विगुनd to prevent round-off
 *                  problems when calculating fIFBW/2
 *
 * @pAS_Info:	Aव्योम Spurs inक्रमmation block
 * @fm:		If spur, amount f_IF1 has to move negative
 * @fp:		If spur, amount f_IF1 has to move positive
 *
 *  Returns 1 अगर an LO spur would be present, otherwise 0.
 */
अटल u32 IsSpurInBand(काष्ठा MT2063_Aव्योमSpursData_t *pAS_Info,
			u32 *fm, u32 * fp)
अणु
	/*
	 **  Calculate LO frequency settings.
	 */
	u32 n, n0;
	स्थिर u32 f_LO1 = pAS_Info->f_LO1;
	स्थिर u32 f_LO2 = pAS_Info->f_LO2;
	स्थिर u32 d = pAS_Info->f_out + pAS_Info->f_out_bw / 2;
	स्थिर u32 c = d - pAS_Info->f_out_bw;
	स्थिर u32 f = pAS_Info->f_zअगर_bw / 2;
	स्थिर u32 f_Scale = (f_LO1 / (अच_पूर्णांक_उच्च / 2 / pAS_Info->maxH1)) + 1;
	s32 f_nsLO1, f_nsLO2;
	s32 f_Spur;
	u32 ma, mb, mc, md, me, mf;
	u32 lo_gcd, gd_Scale, gc_Scale, gf_Scale, hgds, hgfs, hgcs;

	dprपूर्णांकk(2, "\n");

	*fm = 0;

	/*
	 ** For each edge (d, c & f), calculate a scale, based on the gcd
	 ** of f_LO1, f_LO2 and the edge value.  Use the larger of this
	 ** gcd-based scale factor or f_Scale.
	 */
	lo_gcd = gcd(f_LO1, f_LO2);
	gd_Scale = max((u32) gcd(lo_gcd, d), f_Scale);
	hgds = gd_Scale / 2;
	gc_Scale = max((u32) gcd(lo_gcd, c), f_Scale);
	hgcs = gc_Scale / 2;
	gf_Scale = max((u32) gcd(lo_gcd, f), f_Scale);
	hgfs = gf_Scale / 2;

	n0 = DIV_ROUND_UP(f_LO2 - d, f_LO1 - f_LO2);

	/*  Check out all multiples of LO1 from n0 to m_maxLOSpurHarmonic  */
	क्रम (n = n0; n <= pAS_Info->maxH1; ++n) अणु
		md = (n * ((f_LO1 + hgds) / gd_Scale) -
		      ((d + hgds) / gd_Scale)) / ((f_LO2 + hgds) / gd_Scale);

		/*  If # fLO2 harmonics > m_maxLOSpurHarmonic, then no spurs present  */
		अगर (md >= pAS_Info->maxH1)
			अवरोध;

		ma = (n * ((f_LO1 + hgds) / gd_Scale) +
		      ((d + hgds) / gd_Scale)) / ((f_LO2 + hgds) / gd_Scale);

		/*  If no spurs between +/- (f_out + f_IFBW/2), then try next harmonic  */
		अगर (md == ma)
			जारी;

		mc = (n * ((f_LO1 + hgcs) / gc_Scale) -
		      ((c + hgcs) / gc_Scale)) / ((f_LO2 + hgcs) / gc_Scale);
		अगर (mc != md) अणु
			f_nsLO1 = (s32) (n * (f_LO1 / gc_Scale));
			f_nsLO2 = (s32) (mc * (f_LO2 / gc_Scale));
			f_Spur =
			    (gc_Scale * (f_nsLO1 - f_nsLO2)) +
			    n * (f_LO1 % gc_Scale) - mc * (f_LO2 % gc_Scale);

			*fp = ((f_Spur - (s32) c) / (mc - n)) + 1;
			*fm = (((s32) d - f_Spur) / (mc - n)) + 1;
			वापस 1;
		पूर्ण

		/*  Location of Zero-IF-spur to be checked  */
		me = (n * ((f_LO1 + hgfs) / gf_Scale) +
		      ((f + hgfs) / gf_Scale)) / ((f_LO2 + hgfs) / gf_Scale);
		mf = (n * ((f_LO1 + hgfs) / gf_Scale) -
		      ((f + hgfs) / gf_Scale)) / ((f_LO2 + hgfs) / gf_Scale);
		अगर (me != mf) अणु
			f_nsLO1 = n * (f_LO1 / gf_Scale);
			f_nsLO2 = me * (f_LO2 / gf_Scale);
			f_Spur =
			    (gf_Scale * (f_nsLO1 - f_nsLO2)) +
			    n * (f_LO1 % gf_Scale) - me * (f_LO2 % gf_Scale);

			*fp = ((f_Spur + (s32) f) / (me - n)) + 1;
			*fm = (((s32) f - f_Spur) / (me - n)) + 1;
			वापस 1;
		पूर्ण

		mb = (n * ((f_LO1 + hgcs) / gc_Scale) +
		      ((c + hgcs) / gc_Scale)) / ((f_LO2 + hgcs) / gc_Scale);
		अगर (ma != mb) अणु
			f_nsLO1 = n * (f_LO1 / gc_Scale);
			f_nsLO2 = ma * (f_LO2 / gc_Scale);
			f_Spur =
			    (gc_Scale * (f_nsLO1 - f_nsLO2)) +
			    n * (f_LO1 % gc_Scale) - ma * (f_LO2 % gc_Scale);

			*fp = (((s32) d + f_Spur) / (ma - n)) + 1;
			*fm = (-(f_Spur + (s32) c) / (ma - n)) + 1;
			वापस 1;
		पूर्ण
	पूर्ण

	/*  No spurs found  */
	वापस 0;
पूर्ण

/*
 * MT_Aव्योमSpurs() - Main entry poपूर्णांक to aव्योम spurs.
 *                   Checks क्रम existing spurs in present LO1, LO2 freqs
 *                   and अगर present, chooses spur-मुक्त LO1, LO2 combination
 *                   that tunes the same input/output frequencies.
 */
अटल u32 MT2063_Aव्योमSpurs(काष्ठा MT2063_Aव्योमSpursData_t *pAS_Info)
अणु
	पूर्णांक status = 0;
	u32 fm, fp;		/*  restricted range on LO's        */
	pAS_Info->bSpurAव्योमed = 0;
	pAS_Info->nSpursFound = 0;

	dprपूर्णांकk(2, "\n");

	अगर (pAS_Info->maxH1 == 0)
		वापस 0;

	/*
	 * Aव्योम LO Generated Spurs
	 *
	 * Make sure that have no LO-related spurs within the IF output
	 * bandwidth.
	 *
	 * If there is an LO spur in this band, start at the current IF1 frequency
	 * and work out until we find a spur-मुक्त frequency or run up against the
	 * 1st IF SAW band edge.  Use temporary copies of fLO1 and fLO2 so that they
	 * will be unchanged अगर a spur-मुक्त setting is not found.
	 */
	pAS_Info->bSpurPresent = IsSpurInBand(pAS_Info, &fm, &fp);
	अगर (pAS_Info->bSpurPresent) अणु
		u32 zfIF1 = pAS_Info->f_LO1 - pAS_Info->f_in;	/*  current attempt at a 1st IF  */
		u32 zfLO1 = pAS_Info->f_LO1;	/*  current attempt at an LO1 freq  */
		u32 zfLO2 = pAS_Info->f_LO2;	/*  current attempt at an LO2 freq  */
		u32 delta_IF1;
		u32 new_IF1;

		/*
		 **  Spur was found, attempt to find a spur-मुक्त 1st IF
		 */
		करो अणु
			pAS_Info->nSpursFound++;

			/*  Raise f_IF1_upper, अगर needed  */
			MT2063_AddExclZone(pAS_Info, zfIF1 - fm, zfIF1 + fp);

			/*  Choose next IF1 that is बंदst to f_IF1_CENTER              */
			new_IF1 = MT2063_ChooseFirstIF(pAS_Info);

			अगर (new_IF1 > zfIF1) अणु
				pAS_Info->f_LO1 += (new_IF1 - zfIF1);
				pAS_Info->f_LO2 += (new_IF1 - zfIF1);
			पूर्ण अन्यथा अणु
				pAS_Info->f_LO1 -= (zfIF1 - new_IF1);
				pAS_Info->f_LO2 -= (zfIF1 - new_IF1);
			पूर्ण
			zfIF1 = new_IF1;

			अगर (zfIF1 > pAS_Info->f_अगर1_Center)
				delta_IF1 = zfIF1 - pAS_Info->f_अगर1_Center;
			अन्यथा
				delta_IF1 = pAS_Info->f_अगर1_Center - zfIF1;

			pAS_Info->bSpurPresent = IsSpurInBand(pAS_Info, &fm, &fp);
		/*
		 *  Continue जबतक the new 1st IF is still within the 1st IF bandwidth
		 *  and there is a spur in the band (again)
		 */
		पूर्ण जबतक ((2 * delta_IF1 + pAS_Info->f_out_bw <= pAS_Info->f_अगर1_bw) && pAS_Info->bSpurPresent);

		/*
		 * Use the LO-spur मुक्त values found.  If the search went all
		 * the way to the 1st IF band edge and always found spurs, just
		 * leave the original choice.  It's as "good" as any other.
		 */
		अगर (pAS_Info->bSpurPresent == 1) अणु
			status |= MT2063_SPUR_PRESENT_ERR;
			pAS_Info->f_LO1 = zfLO1;
			pAS_Info->f_LO2 = zfLO2;
		पूर्ण अन्यथा
			pAS_Info->bSpurAव्योमed = 1;
	पूर्ण

	status |=
	    ((pAS_Info->
	      nSpursFound << MT2063_SPUR_SHIFT) & MT2063_SPUR_CNT_MASK);

	वापस status;
पूर्ण

/*
 * Constants used by the tuning algorithm
 */
#घोषणा MT2063_REF_FREQ          (16000000UL)	/* Reference oscillator Frequency (in Hz) */
#घोषणा MT2063_IF1_BW            (22000000UL)	/* The IF1 filter bandwidth (in Hz) */
#घोषणा MT2063_TUNE_STEP_SIZE       (50000UL)	/* Tune in steps of 50 kHz */
#घोषणा MT2063_SPUR_STEP_HZ        (250000UL)	/* Step size (in Hz) to move IF1 when aव्योमing spurs */
#घोषणा MT2063_ZIF_BW             (2000000UL)	/* Zero-IF spur-मुक्त bandwidth (in Hz) */
#घोषणा MT2063_MAX_HARMONICS_1         (15UL)	/* Highest पूर्णांकra-tuner LO Spur Harmonic to be aव्योमed */
#घोषणा MT2063_MAX_HARMONICS_2          (5UL)	/* Highest पूर्णांकer-tuner LO Spur Harmonic to be aव्योमed */
#घोषणा MT2063_MIN_LO_SEP         (1000000UL)	/* Minimum पूर्णांकer-tuner LO frequency separation */
#घोषणा MT2063_LO1_FRACN_AVOID          (0UL)	/* LO1 FracN numerator aव्योम region (in Hz) */
#घोषणा MT2063_LO2_FRACN_AVOID     (199999UL)	/* LO2 FracN numerator aव्योम region (in Hz) */
#घोषणा MT2063_MIN_FIN_FREQ      (44000000UL)	/* Minimum input frequency (in Hz) */
#घोषणा MT2063_MAX_FIN_FREQ    (1100000000UL)	/* Maximum input frequency (in Hz) */
#घोषणा MT2063_MIN_FOUT_FREQ     (36000000UL)	/* Minimum output frequency (in Hz) */
#घोषणा MT2063_MAX_FOUT_FREQ     (57000000UL)	/* Maximum output frequency (in Hz) */
#घोषणा MT2063_MIN_DNC_FREQ    (1293000000UL)	/* Minimum LO2 frequency (in Hz) */
#घोषणा MT2063_MAX_DNC_FREQ    (1614000000UL)	/* Maximum LO2 frequency (in Hz) */
#घोषणा MT2063_MIN_UPC_FREQ    (1396000000UL)	/* Minimum LO1 frequency (in Hz) */
#घोषणा MT2063_MAX_UPC_FREQ    (2750000000UL)	/* Maximum LO1 frequency (in Hz) */

/*
 *  Define the supported Part/Rev codes क्रम the MT2063
 */
#घोषणा MT2063_B0       (0x9B)
#घोषणा MT2063_B1       (0x9C)
#घोषणा MT2063_B2       (0x9D)
#घोषणा MT2063_B3       (0x9E)

/**
 * mt2063_lockStatus - Checks to see अगर LO1 and LO2 are locked
 *
 * @state:	काष्ठा mt2063_state poपूर्णांकer
 *
 * This function वापसs 0, अगर no lock, 1 अगर locked and a value < 1 अगर error
 */
अटल पूर्णांक mt2063_lockStatus(काष्ठा mt2063_state *state)
अणु
	स्थिर u32 nMaxWait = 100;	/*  रुको a maximum of 100 msec   */
	स्थिर u32 nPollRate = 2;	/*  poll status bits every 2 ms */
	स्थिर u32 nMaxLoops = nMaxWait / nPollRate;
	स्थिर u8 LO1LK = 0x80;
	u8 LO2LK = 0x08;
	पूर्णांक status;
	u32 nDelays = 0;

	dprपूर्णांकk(2, "\n");

	/*  LO2 Lock bit was in a dअगरferent place क्रम B0 version  */
	अगर (state->tuner_id == MT2063_B0)
		LO2LK = 0x40;

	करो अणु
		status = mt2063_पढ़ो(state, MT2063_REG_LO_STATUS,
				     &state->reg[MT2063_REG_LO_STATUS], 1);

		अगर (status < 0)
			वापस status;

		अगर ((state->reg[MT2063_REG_LO_STATUS] & (LO1LK | LO2LK)) ==
		    (LO1LK | LO2LK)) अणु
			वापस TUNER_STATUS_LOCKED | TUNER_STATUS_STEREO;
		पूर्ण
		msleep(nPollRate);	/*  Wait between retries  */
	पूर्ण जबतक (++nDelays < nMaxLoops);

	/*
	 * Got no lock or partial lock
	 */
	वापस 0;
पूर्ण

/*
 *  Constants क्रम setting receiver modes.
 *  (6 modes defined at this समय, क्रमागतerated by mt2063_delivery_sys)
 *  (DNC1GC & DNC2GC are the values, which are used, when the specअगरic
 *   DNC Output is selected, the other is always off)
 *
 *                क्रमागत mt2063_delivery_sys
 * -------------+----------------------------------------------
 * Mode 0 :     | MT2063_CABLE_QAM
 * Mode 1 :     | MT2063_CABLE_ANALOG
 * Mode 2 :     | MT2063_OFFAIR_COFDM
 * Mode 3 :     | MT2063_OFFAIR_COFDM_SAWLESS
 * Mode 4 :     | MT2063_OFFAIR_ANALOG
 * Mode 5 :     | MT2063_OFFAIR_8VSB
 * --------------+----------------------------------------------
 *
 *                |<----------   Mode  -------------->|
 *    Reg Field   |  0  |  1  |  2  |  3  |  4  |  5  |
 *    ------------+-----+-----+-----+-----+-----+-----+
 *    RFAGCen     | OFF | OFF | OFF | OFF | OFF | OFF
 *    LNARin      |   0 |   0 |   3 |   3 |  3  |  3
 *    FIFFQen     |   1 |   1 |   1 |   1 |  1  |  1
 *    FIFFq       |   0 |   0 |   0 |   0 |  0  |  0
 *    DNC1gc      |   0 |   0 |   0 |   0 |  0  |  0
 *    DNC2gc      |   0 |   0 |   0 |   0 |  0  |  0
 *    GCU Auto    |   1 |   1 |   1 |   1 |  1  |  1
 *    LNA max Atn |  31 |  31 |  31 |  31 | 31  | 31
 *    LNA Target  |  44 |  43 |  43 |  43 | 43  | 43
 *    ign  RF Ovl |   0 |   0 |   0 |   0 |  0  |  0
 *    RF  max Atn |  31 |  31 |  31 |  31 | 31  | 31
 *    PD1 Target  |  36 |  36 |  38 |  38 | 36  | 38
 *    ign FIF Ovl |   0 |   0 |   0 |   0 |  0  |  0
 *    FIF max Atn |   5 |   5 |   5 |   5 |  5  |  5
 *    PD2 Target  |  40 |  33 |  42 |  42 | 33  | 42
 */

क्रमागत mt2063_delivery_sys अणु
	MT2063_CABLE_QAM = 0,
	MT2063_CABLE_ANALOG,
	MT2063_OFFAIR_COFDM,
	MT2063_OFFAIR_COFDM_SAWLESS,
	MT2063_OFFAIR_ANALOG,
	MT2063_OFFAIR_8VSB,
	MT2063_NUM_RCVR_MODES
पूर्ण;

अटल स्थिर अक्षर *mt2063_mode_name[] = अणु
	[MT2063_CABLE_QAM]		= "digital cable",
	[MT2063_CABLE_ANALOG]		= "analog cable",
	[MT2063_OFFAIR_COFDM]		= "digital offair",
	[MT2063_OFFAIR_COFDM_SAWLESS]	= "digital offair without SAW",
	[MT2063_OFFAIR_ANALOG]		= "analog offair",
	[MT2063_OFFAIR_8VSB]		= "analog offair 8vsb",
पूर्ण;

अटल स्थिर u8 RFAGCEN[]	= अणु  0,  0,  0,  0,  0,  0 पूर्ण;
अटल स्थिर u8 LNARIN[]	= अणु  0,  0,  3,  3,  3,  3 पूर्ण;
अटल स्थिर u8 FIFFQEN[]	= अणु  1,  1,  1,  1,  1,  1 पूर्ण;
अटल स्थिर u8 FIFFQ[]		= अणु  0,  0,  0,  0,  0,  0 पूर्ण;
अटल स्थिर u8 DNC1GC[]	= अणु  0,  0,  0,  0,  0,  0 पूर्ण;
अटल स्थिर u8 DNC2GC[]	= अणु  0,  0,  0,  0,  0,  0 पूर्ण;
अटल स्थिर u8 ACLNAMAX[]	= अणु 31, 31, 31, 31, 31, 31 पूर्ण;
अटल स्थिर u8 LNATGT[]	= अणु 44, 43, 43, 43, 43, 43 पूर्ण;
अटल स्थिर u8 RFOVDIS[]	= अणु  0,  0,  0,  0,  0,  0 पूर्ण;
अटल स्थिर u8 ACRFMAX[]	= अणु 31, 31, 31, 31, 31, 31 पूर्ण;
अटल स्थिर u8 PD1TGT[]	= अणु 36, 36, 38, 38, 36, 38 पूर्ण;
अटल स्थिर u8 FIFOVDIS[]	= अणु  0,  0,  0,  0,  0,  0 पूर्ण;
अटल स्थिर u8 ACFIFMAX[]	= अणु 29, 29, 29, 29, 29, 29 पूर्ण;
अटल स्थिर u8 PD2TGT[]	= अणु 40, 33, 38, 42, 30, 38 पूर्ण;

/*
 * mt2063_set_dnc_output_enable()
 */
अटल u32 mt2063_get_dnc_output_enable(काष्ठा mt2063_state *state,
					क्रमागत MT2063_DNC_Output_Enable *pValue)
अणु
	dprपूर्णांकk(2, "\n");

	अगर ((state->reg[MT2063_REG_DNC_GAIN] & 0x03) == 0x03) अणु	/* अगर DNC1 is off */
		अगर ((state->reg[MT2063_REG_VGA_GAIN] & 0x03) == 0x03)	/* अगर DNC2 is off */
			*pValue = MT2063_DNC_NONE;
		अन्यथा
			*pValue = MT2063_DNC_2;
	पूर्ण अन्यथा अणु	/* DNC1 is on */
		अगर ((state->reg[MT2063_REG_VGA_GAIN] & 0x03) == 0x03)	/* अगर DNC2 is off */
			*pValue = MT2063_DNC_1;
		अन्यथा
			*pValue = MT2063_DNC_BOTH;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * mt2063_set_dnc_output_enable()
 */
अटल u32 mt2063_set_dnc_output_enable(काष्ठा mt2063_state *state,
					क्रमागत MT2063_DNC_Output_Enable nValue)
अणु
	पूर्णांक status = 0;	/* Status to be वापसed        */
	u8 val = 0;

	dprपूर्णांकk(2, "\n");

	/* selects, which DNC output is used */
	चयन (nValue) अणु
	हाल MT2063_DNC_NONE:
		val = (state->reg[MT2063_REG_DNC_GAIN] & 0xFC) | 0x03;	/* Set DNC1GC=3 */
		अगर (state->reg[MT2063_REG_DNC_GAIN] !=
		    val)
			status |=
			    mt2063_setreg(state,
					  MT2063_REG_DNC_GAIN,
					  val);

		val = (state->reg[MT2063_REG_VGA_GAIN] & 0xFC) | 0x03;	/* Set DNC2GC=3 */
		अगर (state->reg[MT2063_REG_VGA_GAIN] !=
		    val)
			status |=
			    mt2063_setreg(state,
					  MT2063_REG_VGA_GAIN,
					  val);

		val = (state->reg[MT2063_REG_RSVD_20] & ~0x40);	/* Set PD2MUX=0 */
		अगर (state->reg[MT2063_REG_RSVD_20] !=
		    val)
			status |=
			    mt2063_setreg(state,
					  MT2063_REG_RSVD_20,
					  val);

		अवरोध;
	हाल MT2063_DNC_1:
		val = (state->reg[MT2063_REG_DNC_GAIN] & 0xFC) | (DNC1GC[state->rcvr_mode] & 0x03);	/* Set DNC1GC=x */
		अगर (state->reg[MT2063_REG_DNC_GAIN] !=
		    val)
			status |=
			    mt2063_setreg(state,
					  MT2063_REG_DNC_GAIN,
					  val);

		val = (state->reg[MT2063_REG_VGA_GAIN] & 0xFC) | 0x03;	/* Set DNC2GC=3 */
		अगर (state->reg[MT2063_REG_VGA_GAIN] !=
		    val)
			status |=
			    mt2063_setreg(state,
					  MT2063_REG_VGA_GAIN,
					  val);

		val = (state->reg[MT2063_REG_RSVD_20] & ~0x40);	/* Set PD2MUX=0 */
		अगर (state->reg[MT2063_REG_RSVD_20] !=
		    val)
			status |=
			    mt2063_setreg(state,
					  MT2063_REG_RSVD_20,
					  val);

		अवरोध;
	हाल MT2063_DNC_2:
		val = (state->reg[MT2063_REG_DNC_GAIN] & 0xFC) | 0x03;	/* Set DNC1GC=3 */
		अगर (state->reg[MT2063_REG_DNC_GAIN] !=
		    val)
			status |=
			    mt2063_setreg(state,
					  MT2063_REG_DNC_GAIN,
					  val);

		val = (state->reg[MT2063_REG_VGA_GAIN] & 0xFC) | (DNC2GC[state->rcvr_mode] & 0x03);	/* Set DNC2GC=x */
		अगर (state->reg[MT2063_REG_VGA_GAIN] !=
		    val)
			status |=
			    mt2063_setreg(state,
					  MT2063_REG_VGA_GAIN,
					  val);

		val = (state->reg[MT2063_REG_RSVD_20] | 0x40);	/* Set PD2MUX=1 */
		अगर (state->reg[MT2063_REG_RSVD_20] !=
		    val)
			status |=
			    mt2063_setreg(state,
					  MT2063_REG_RSVD_20,
					  val);

		अवरोध;
	हाल MT2063_DNC_BOTH:
		val = (state->reg[MT2063_REG_DNC_GAIN] & 0xFC) | (DNC1GC[state->rcvr_mode] & 0x03);	/* Set DNC1GC=x */
		अगर (state->reg[MT2063_REG_DNC_GAIN] !=
		    val)
			status |=
			    mt2063_setreg(state,
					  MT2063_REG_DNC_GAIN,
					  val);

		val = (state->reg[MT2063_REG_VGA_GAIN] & 0xFC) | (DNC2GC[state->rcvr_mode] & 0x03);	/* Set DNC2GC=x */
		अगर (state->reg[MT2063_REG_VGA_GAIN] !=
		    val)
			status |=
			    mt2063_setreg(state,
					  MT2063_REG_VGA_GAIN,
					  val);

		val = (state->reg[MT2063_REG_RSVD_20] | 0x40);	/* Set PD2MUX=1 */
		अगर (state->reg[MT2063_REG_RSVD_20] !=
		    val)
			status |=
			    mt2063_setreg(state,
					  MT2063_REG_RSVD_20,
					  val);

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस status;
पूर्ण

/*
 * MT2063_SetReceiverMode() - Set the MT2063 receiver mode, according with
 *			      the selected क्रमागत mt2063_delivery_sys type.
 *
 *  (DNC1GC & DNC2GC are the values, which are used, when the specअगरic
 *   DNC Output is selected, the other is always off)
 *
 * @state:	ptr to mt2063_state काष्ठाure
 * @Mode:	desired receiver delivery प्रणाली
 *
 * Note: Register cache must be valid क्रम it to work
 */

अटल u32 MT2063_SetReceiverMode(काष्ठा mt2063_state *state,
				  क्रमागत mt2063_delivery_sys Mode)
अणु
	पूर्णांक status = 0;	/* Status to be वापसed        */
	u8 val;
	u32 दीर्घval;

	dprपूर्णांकk(2, "\n");

	अगर (Mode >= MT2063_NUM_RCVR_MODES)
		status = -दुस्फल;

	/* RFAGCen */
	अगर (status >= 0) अणु
		val =
		    (state->
		     reg[MT2063_REG_PD1_TGT] & ~0x40) | (RFAGCEN[Mode]
								   ? 0x40 :
								   0x00);
		अगर (state->reg[MT2063_REG_PD1_TGT] != val)
			status |= mt2063_setreg(state, MT2063_REG_PD1_TGT, val);
	पूर्ण

	/* LNARin */
	अगर (status >= 0) अणु
		u8 val = (state->reg[MT2063_REG_CTRL_2C] & ~0x03) |
			 (LNARIN[Mode] & 0x03);
		अगर (state->reg[MT2063_REG_CTRL_2C] != val)
			status |= mt2063_setreg(state, MT2063_REG_CTRL_2C, val);
	पूर्ण

	/* FIFFQEN and FIFFQ */
	अगर (status >= 0) अणु
		val =
		    (state->
		     reg[MT2063_REG_FIFF_CTRL2] & ~0xF0) |
		    (FIFFQEN[Mode] << 7) | (FIFFQ[Mode] << 4);
		अगर (state->reg[MT2063_REG_FIFF_CTRL2] != val) अणु
			status |=
			    mt2063_setreg(state, MT2063_REG_FIFF_CTRL2, val);
			/* trigger FIFF calibration, needed after changing FIFFQ */
			val =
			    (state->reg[MT2063_REG_FIFF_CTRL] | 0x01);
			status |=
			    mt2063_setreg(state, MT2063_REG_FIFF_CTRL, val);
			val =
			    (state->
			     reg[MT2063_REG_FIFF_CTRL] & ~0x01);
			status |=
			    mt2063_setreg(state, MT2063_REG_FIFF_CTRL, val);
		पूर्ण
	पूर्ण

	/* DNC1GC & DNC2GC */
	status |= mt2063_get_dnc_output_enable(state, &दीर्घval);
	status |= mt2063_set_dnc_output_enable(state, दीर्घval);

	/* acLNAmax */
	अगर (status >= 0) अणु
		u8 val = (state->reg[MT2063_REG_LNA_OV] & ~0x1F) |
			 (ACLNAMAX[Mode] & 0x1F);
		अगर (state->reg[MT2063_REG_LNA_OV] != val)
			status |= mt2063_setreg(state, MT2063_REG_LNA_OV, val);
	पूर्ण

	/* LNATGT */
	अगर (status >= 0) अणु
		u8 val = (state->reg[MT2063_REG_LNA_TGT] & ~0x3F) |
			 (LNATGT[Mode] & 0x3F);
		अगर (state->reg[MT2063_REG_LNA_TGT] != val)
			status |= mt2063_setreg(state, MT2063_REG_LNA_TGT, val);
	पूर्ण

	/* ACRF */
	अगर (status >= 0) अणु
		u8 val = (state->reg[MT2063_REG_RF_OV] & ~0x1F) |
			 (ACRFMAX[Mode] & 0x1F);
		अगर (state->reg[MT2063_REG_RF_OV] != val)
			status |= mt2063_setreg(state, MT2063_REG_RF_OV, val);
	पूर्ण

	/* PD1TGT */
	अगर (status >= 0) अणु
		u8 val = (state->reg[MT2063_REG_PD1_TGT] & ~0x3F) |
			 (PD1TGT[Mode] & 0x3F);
		अगर (state->reg[MT2063_REG_PD1_TGT] != val)
			status |= mt2063_setreg(state, MT2063_REG_PD1_TGT, val);
	पूर्ण

	/* FIFATN */
	अगर (status >= 0) अणु
		u8 val = ACFIFMAX[Mode];
		अगर (state->reg[MT2063_REG_PART_REV] != MT2063_B3 && val > 5)
			val = 5;
		val = (state->reg[MT2063_REG_FIF_OV] & ~0x1F) |
		      (val & 0x1F);
		अगर (state->reg[MT2063_REG_FIF_OV] != val)
			status |= mt2063_setreg(state, MT2063_REG_FIF_OV, val);
	पूर्ण

	/* PD2TGT */
	अगर (status >= 0) अणु
		u8 val = (state->reg[MT2063_REG_PD2_TGT] & ~0x3F) |
		    (PD2TGT[Mode] & 0x3F);
		अगर (state->reg[MT2063_REG_PD2_TGT] != val)
			status |= mt2063_setreg(state, MT2063_REG_PD2_TGT, val);
	पूर्ण

	/* Ignore ATN Overload */
	अगर (status >= 0) अणु
		val = (state->reg[MT2063_REG_LNA_TGT] & ~0x80) |
		      (RFOVDIS[Mode] ? 0x80 : 0x00);
		अगर (state->reg[MT2063_REG_LNA_TGT] != val)
			status |= mt2063_setreg(state, MT2063_REG_LNA_TGT, val);
	पूर्ण

	/* Ignore FIF Overload */
	अगर (status >= 0) अणु
		val = (state->reg[MT2063_REG_PD1_TGT] & ~0x80) |
		      (FIFOVDIS[Mode] ? 0x80 : 0x00);
		अगर (state->reg[MT2063_REG_PD1_TGT] != val)
			status |= mt2063_setreg(state, MT2063_REG_PD1_TGT, val);
	पूर्ण

	अगर (status >= 0) अणु
		state->rcvr_mode = Mode;
		dprपूर्णांकk(1, "mt2063 mode changed to %s\n",
			mt2063_mode_name[state->rcvr_mode]);
	पूर्ण

	वापस status;
पूर्ण

/*
 * MT2063_ClearPowerMaskBits () - Clears the घातer-करोwn mask bits क्रम various
 *				  sections of the MT2063
 *
 * @Bits:		Mask bits to be cleared.
 *
 * See definition of MT2063_Mask_Bits type क्रम description
 * of each of the घातer bits.
 */
अटल u32 MT2063_ClearPowerMaskBits(काष्ठा mt2063_state *state,
				     क्रमागत MT2063_Mask_Bits Bits)
अणु
	पूर्णांक status = 0;

	dprपूर्णांकk(2, "\n");
	Bits = (क्रमागत MT2063_Mask_Bits)(Bits & MT2063_ALL_SD);	/* Only valid bits क्रम this tuner */
	अगर ((Bits & 0xFF00) != 0) अणु
		state->reg[MT2063_REG_PWR_2] &= ~(u8) (Bits >> 8);
		status |=
		    mt2063_ग_लिखो(state,
				    MT2063_REG_PWR_2,
				    &state->reg[MT2063_REG_PWR_2], 1);
	पूर्ण
	अगर ((Bits & 0xFF) != 0) अणु
		state->reg[MT2063_REG_PWR_1] &= ~(u8) (Bits & 0xFF);
		status |=
		    mt2063_ग_लिखो(state,
				    MT2063_REG_PWR_1,
				    &state->reg[MT2063_REG_PWR_1], 1);
	पूर्ण

	वापस status;
पूर्ण

/*
 * MT2063_SoftwareShutकरोwn() - Enables or disables software shutकरोwn function.
 *			       When Shutकरोwn is 1, any section whose घातer
 *			       mask is set will be shutकरोwn.
 */
अटल u32 MT2063_SoftwareShutकरोwn(काष्ठा mt2063_state *state, u8 Shutकरोwn)
अणु
	पूर्णांक status;

	dprपूर्णांकk(2, "\n");
	अगर (Shutकरोwn == 1)
		state->reg[MT2063_REG_PWR_1] |= 0x04;
	अन्यथा
		state->reg[MT2063_REG_PWR_1] &= ~0x04;

	status = mt2063_ग_लिखो(state,
			    MT2063_REG_PWR_1,
			    &state->reg[MT2063_REG_PWR_1], 1);

	अगर (Shutकरोwn != 1) अणु
		state->reg[MT2063_REG_BYP_CTRL] =
		    (state->reg[MT2063_REG_BYP_CTRL] & 0x9F) | 0x40;
		status |=
		    mt2063_ग_लिखो(state,
				    MT2063_REG_BYP_CTRL,
				    &state->reg[MT2063_REG_BYP_CTRL],
				    1);
		state->reg[MT2063_REG_BYP_CTRL] =
		    (state->reg[MT2063_REG_BYP_CTRL] & 0x9F);
		status |=
		    mt2063_ग_लिखो(state,
				    MT2063_REG_BYP_CTRL,
				    &state->reg[MT2063_REG_BYP_CTRL],
				    1);
	पूर्ण

	वापस status;
पूर्ण

अटल u32 MT2063_Round_fLO(u32 f_LO, u32 f_LO_Step, u32 f_ref)
अणु
	वापस f_ref * (f_LO / f_ref)
	    + f_LO_Step * (((f_LO % f_ref) + (f_LO_Step / 2)) / f_LO_Step);
पूर्ण

/**
 * MT2063_fLO_FractionalTerm - Calculates the portion contributed by FracN / denom.
 *                        This function preserves maximum precision without
 *                        risk of overflow.  It accurately calculates
 *                        f_ref * num / denom to within 1 HZ with fixed math.
 *
 * @f_ref:	SRO frequency.
 * @num:	Fractional portion of the multiplier
 * @denom:	denominator portion of the ratio
 *
 * This calculation handles f_ref as two separate 14-bit fields.
 * Thereक्रमe, a maximum value of 2^28-1 may safely be used क्रम f_ref.
 * This is the genesis of the magic number "14" and the magic mask value of
 * 0x03FFF.
 *
 * This routine successfully handles denom values up to and including 2^18.
 *  Returns:        f_ref * num / denom
 */
अटल u32 MT2063_fLO_FractionalTerm(u32 f_ref, u32 num, u32 denom)
अणु
	u32 t1 = (f_ref >> 14) * num;
	u32 term1 = t1 / denom;
	u32 loss = t1 % denom;
	u32 term2 =
	    (((f_ref & 0x00003FFF) * num + (loss << 14)) + (denom / 2)) / denom;
	वापस (term1 << 14) + term2;
पूर्ण

/*
 * MT2063_CalcLO1Mult - Calculates Integer भागider value and the numerator
 *                value क्रम a FracN PLL.
 *
 *                This function assumes that the f_LO and f_Ref are
 *                evenly भागisible by f_LO_Step.
 *
 * @Div:	OUTPUT: Whole number portion of the multiplier
 * @FracN:	OUTPUT: Fractional portion of the multiplier
 * @f_LO:	desired LO frequency.
 * @f_LO_Step:	Minimum step size क्रम the LO (in Hz).
 * @f_Ref:	SRO frequency.
 * @f_Aव्योम:	Range of PLL frequencies to aव्योम near पूर्णांकeger multiples
 *		of f_Ref (in Hz).
 *
 * Returns:        Recalculated LO frequency.
 */
अटल u32 MT2063_CalcLO1Mult(u32 *Div,
			      u32 *FracN,
			      u32 f_LO,
			      u32 f_LO_Step, u32 f_Ref)
अणु
	/*  Calculate the whole number portion of the भागider */
	*Div = f_LO / f_Ref;

	/*  Calculate the numerator value (round to nearest f_LO_Step) */
	*FracN =
	    (64 * (((f_LO % f_Ref) + (f_LO_Step / 2)) / f_LO_Step) +
	     (f_Ref / f_LO_Step / 2)) / (f_Ref / f_LO_Step);

	वापस (f_Ref * (*Div)) + MT2063_fLO_FractionalTerm(f_Ref, *FracN, 64);
पूर्ण

/**
 * MT2063_CalcLO2Mult - Calculates Integer भागider value and the numerator
 *                 value क्रम a FracN PLL.
 *
 *                  This function assumes that the f_LO and f_Ref are
 *                  evenly भागisible by f_LO_Step.
 *
 * @Div:	OUTPUT: Whole number portion of the multiplier
 * @FracN:	OUTPUT: Fractional portion of the multiplier
 * @f_LO:	desired LO frequency.
 * @f_LO_Step:	Minimum step size क्रम the LO (in Hz).
 * @f_Ref:	SRO frequency.
 *
 * Returns: Recalculated LO frequency.
 */
अटल u32 MT2063_CalcLO2Mult(u32 *Div,
			      u32 *FracN,
			      u32 f_LO,
			      u32 f_LO_Step, u32 f_Ref)
अणु
	/*  Calculate the whole number portion of the भागider */
	*Div = f_LO / f_Ref;

	/*  Calculate the numerator value (round to nearest f_LO_Step) */
	*FracN =
	    (8191 * (((f_LO % f_Ref) + (f_LO_Step / 2)) / f_LO_Step) +
	     (f_Ref / f_LO_Step / 2)) / (f_Ref / f_LO_Step);

	वापस (f_Ref * (*Div)) + MT2063_fLO_FractionalTerm(f_Ref, *FracN,
							    8191);
पूर्ण

/*
 * FindClearTuneFilter() - Calculate the corrrect ClearTune filter to be
 *			   used क्रम a given input frequency.
 *
 * @state:	ptr to tuner data काष्ठाure
 * @f_in:	RF input center frequency (in Hz).
 *
 * Returns: ClearTune filter number (0-31)
 */
अटल u32 FindClearTuneFilter(काष्ठा mt2063_state *state, u32 f_in)
अणु
	u32 RFBand;
	u32 idx;		/*  index loop                      */

	/*
	 **  Find RF Band setting
	 */
	RFBand = 31;		/*  def when f_in > all    */
	क्रम (idx = 0; idx < 31; ++idx) अणु
		अगर (state->CTFiltMax[idx] >= f_in) अणु
			RFBand = idx;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस RFBand;
पूर्ण

/*
 * MT2063_Tune() - Change the tuner's tuned frequency to RFin.
 */
अटल u32 MT2063_Tune(काष्ठा mt2063_state *state, u32 f_in)
अणु				/* RF input center frequency   */

	पूर्णांक status = 0;
	u32 LO1;		/*  1st LO रेजिस्टर value           */
	u32 Num1;		/*  Numerator क्रम LO1 reg. value    */
	u32 f_IF1;		/*  1st IF requested                */
	u32 LO2;		/*  2nd LO रेजिस्टर value           */
	u32 Num2;		/*  Numerator क्रम LO2 reg. value    */
	u32 ofLO1, ofLO2;	/*  last समय's LO frequencies      */
	u8 fअगरfc = 0x80;	/*  FIFF center freq from tuner     */
	u32 fअगरfof;		/*  Offset from FIFF center freq    */
	स्थिर u8 LO1LK = 0x80;	/*  Mask क्रम LO1 Lock bit           */
	u8 LO2LK = 0x08;	/*  Mask क्रम LO2 Lock bit           */
	u8 val;
	u32 RFBand;

	dprपूर्णांकk(2, "\n");
	/*  Check the input and output frequency ranges                   */
	अगर ((f_in < MT2063_MIN_FIN_FREQ) || (f_in > MT2063_MAX_FIN_FREQ))
		वापस -EINVAL;

	अगर ((state->AS_Data.f_out < MT2063_MIN_FOUT_FREQ)
	    || (state->AS_Data.f_out > MT2063_MAX_FOUT_FREQ))
		वापस -EINVAL;

	/*
	 * Save original LO1 and LO2 रेजिस्टर values
	 */
	ofLO1 = state->AS_Data.f_LO1;
	ofLO2 = state->AS_Data.f_LO2;

	/*
	 * Find and set RF Band setting
	 */
	अगर (state->ctfilt_sw == 1) अणु
		val = (state->reg[MT2063_REG_CTUNE_CTRL] | 0x08);
		अगर (state->reg[MT2063_REG_CTUNE_CTRL] != val) अणु
			status |=
			    mt2063_setreg(state, MT2063_REG_CTUNE_CTRL, val);
		पूर्ण
		val = state->reg[MT2063_REG_CTUNE_OV];
		RFBand = FindClearTuneFilter(state, f_in);
		state->reg[MT2063_REG_CTUNE_OV] =
		    (u8) ((state->reg[MT2063_REG_CTUNE_OV] & ~0x1F)
			      | RFBand);
		अगर (state->reg[MT2063_REG_CTUNE_OV] != val) अणु
			status |=
			    mt2063_setreg(state, MT2063_REG_CTUNE_OV, val);
		पूर्ण
	पूर्ण

	/*
	 * Read the FIFF Center Frequency from the tuner
	 */
	अगर (status >= 0) अणु
		status |=
		    mt2063_पढ़ो(state,
				   MT2063_REG_FIFFC,
				   &state->reg[MT2063_REG_FIFFC], 1);
		fअगरfc = state->reg[MT2063_REG_FIFFC];
	पूर्ण
	/*
	 * Assign in the requested values
	 */
	state->AS_Data.f_in = f_in;
	/*  Request a 1st IF such that LO1 is on a step size */
	state->AS_Data.f_अगर1_Request =
	    MT2063_Round_fLO(state->AS_Data.f_अगर1_Request + f_in,
			     state->AS_Data.f_LO1_Step,
			     state->AS_Data.f_ref) - f_in;

	/*
	 * Calculate frequency settings.  f_IF1_FREQ + f_in is the
	 * desired LO1 frequency
	 */
	MT2063_ResetExclZones(&state->AS_Data);

	f_IF1 = MT2063_ChooseFirstIF(&state->AS_Data);

	state->AS_Data.f_LO1 =
	    MT2063_Round_fLO(f_IF1 + f_in, state->AS_Data.f_LO1_Step,
			     state->AS_Data.f_ref);

	state->AS_Data.f_LO2 =
	    MT2063_Round_fLO(state->AS_Data.f_LO1 - state->AS_Data.f_out - f_in,
			     state->AS_Data.f_LO2_Step, state->AS_Data.f_ref);

	/*
	 * Check क्रम any LO spurs in the output bandwidth and adjust
	 * the LO settings to aव्योम them अगर needed
	 */
	status |= MT2063_Aव्योमSpurs(&state->AS_Data);
	/*
	 * MT_Aव्योमSpurs spurs may have changed the LO1 & LO2 values.
	 * Recalculate the LO frequencies and the values to be placed
	 * in the tuning रेजिस्टरs.
	 */
	state->AS_Data.f_LO1 =
	    MT2063_CalcLO1Mult(&LO1, &Num1, state->AS_Data.f_LO1,
			       state->AS_Data.f_LO1_Step, state->AS_Data.f_ref);
	state->AS_Data.f_LO2 =
	    MT2063_Round_fLO(state->AS_Data.f_LO1 - state->AS_Data.f_out - f_in,
			     state->AS_Data.f_LO2_Step, state->AS_Data.f_ref);
	state->AS_Data.f_LO2 =
	    MT2063_CalcLO2Mult(&LO2, &Num2, state->AS_Data.f_LO2,
			       state->AS_Data.f_LO2_Step, state->AS_Data.f_ref);

	/*
	 *  Check the upconverter and करोwnconverter frequency ranges
	 */
	अगर ((state->AS_Data.f_LO1 < MT2063_MIN_UPC_FREQ)
	    || (state->AS_Data.f_LO1 > MT2063_MAX_UPC_FREQ))
		status |= MT2063_UPC_RANGE;
	अगर ((state->AS_Data.f_LO2 < MT2063_MIN_DNC_FREQ)
	    || (state->AS_Data.f_LO2 > MT2063_MAX_DNC_FREQ))
		status |= MT2063_DNC_RANGE;
	/*  LO2 Lock bit was in a dअगरferent place क्रम B0 version  */
	अगर (state->tuner_id == MT2063_B0)
		LO2LK = 0x40;

	/*
	 *  If we have the same LO frequencies and we're alपढ़ोy locked,
	 *  then skip re-programming the LO रेजिस्टरs.
	 */
	अगर ((ofLO1 != state->AS_Data.f_LO1)
	    || (ofLO2 != state->AS_Data.f_LO2)
	    || ((state->reg[MT2063_REG_LO_STATUS] & (LO1LK | LO2LK)) !=
		(LO1LK | LO2LK))) अणु
		/*
		 * Calculate the FIFFOF रेजिस्टर value
		 *
		 *           IF1_Actual
		 * FIFFOF = ------------ - 8 * FIFFC - 4992
		 *            f_ref/64
		 */
		fअगरfof =
		    (state->AS_Data.f_LO1 -
		     f_in) / (state->AS_Data.f_ref / 64) - 8 * (u32) fअगरfc -
		    4992;
		अगर (fअगरfof > 0xFF)
			fअगरfof = 0xFF;

		/*
		 * Place all of the calculated values पूर्णांकo the local tuner
		 * रेजिस्टर fields.
		 */
		अगर (status >= 0) अणु
			state->reg[MT2063_REG_LO1CQ_1] = (u8) (LO1 & 0xFF);	/* DIV1q */
			state->reg[MT2063_REG_LO1CQ_2] = (u8) (Num1 & 0x3F);	/* NUM1q */
			state->reg[MT2063_REG_LO2CQ_1] = (u8) (((LO2 & 0x7F) << 1)	/* DIV2q */
								   |(Num2 >> 12));	/* NUM2q (hi) */
			state->reg[MT2063_REG_LO2CQ_2] = (u8) ((Num2 & 0x0FF0) >> 4);	/* NUM2q (mid) */
			state->reg[MT2063_REG_LO2CQ_3] = (u8) (0xE0 | (Num2 & 0x000F));	/* NUM2q (lo) */

			/*
			 * Now ग_लिखो out the computed रेजिस्टर values
			 * IMPORTANT: There is a required order क्रम writing
			 *            (0x05 must follow all the others).
			 */
			status |= mt2063_ग_लिखो(state, MT2063_REG_LO1CQ_1, &state->reg[MT2063_REG_LO1CQ_1], 5);	/* 0x01 - 0x05 */
			अगर (state->tuner_id == MT2063_B0) अणु
				/* Re-ग_लिखो the one-shot bits to trigger the tune operation */
				status |= mt2063_ग_लिखो(state, MT2063_REG_LO2CQ_3, &state->reg[MT2063_REG_LO2CQ_3], 1);	/* 0x05 */
			पूर्ण
			/* Write out the FIFF offset only अगर it's changing */
			अगर (state->reg[MT2063_REG_FIFF_OFFSET] !=
			    (u8) fअगरfof) अणु
				state->reg[MT2063_REG_FIFF_OFFSET] =
				    (u8) fअगरfof;
				status |=
				    mt2063_ग_लिखो(state,
						    MT2063_REG_FIFF_OFFSET,
						    &state->
						    reg[MT2063_REG_FIFF_OFFSET],
						    1);
			पूर्ण
		पूर्ण

		/*
		 * Check क्रम LO's locking
		 */

		अगर (status < 0)
			वापस status;

		status = mt2063_lockStatus(state);
		अगर (status < 0)
			वापस status;
		अगर (!status)
			वापस -EINVAL;		/* Couldn't lock */

		/*
		 * If we locked OK, assign calculated data to mt2063_state काष्ठाure
		 */
		state->f_IF1_actual = state->AS_Data.f_LO1 - f_in;
	पूर्ण

	वापस status;
पूर्ण

अटल स्थिर u8 MT2063B0_शेषs[] = अणु
	/* Reg,  Value */
	0x19, 0x05,
	0x1B, 0x1D,
	0x1C, 0x1F,
	0x1D, 0x0F,
	0x1E, 0x3F,
	0x1F, 0x0F,
	0x20, 0x3F,
	0x22, 0x21,
	0x23, 0x3F,
	0x24, 0x20,
	0x25, 0x3F,
	0x27, 0xEE,
	0x2C, 0x27,	/*  bit at 0x20 is cleared below  */
	0x30, 0x03,
	0x2C, 0x07,	/*  bit at 0x20 is cleared here   */
	0x2D, 0x87,
	0x2E, 0xAA,
	0x28, 0xE1,	/*  Set the FIFCrst bit here      */
	0x28, 0xE0,	/*  Clear the FIFCrst bit here    */
	0x00
पूर्ण;

/* writing 0x05 0xf0 sw-resets all रेजिस्टरs, so we ग_लिखो only needed changes */
अटल स्थिर u8 MT2063B1_शेषs[] = अणु
	/* Reg,  Value */
	0x05, 0xF0,
	0x11, 0x10,	/* New Enable AFCsd */
	0x19, 0x05,
	0x1A, 0x6C,
	0x1B, 0x24,
	0x1C, 0x28,
	0x1D, 0x8F,
	0x1E, 0x14,
	0x1F, 0x8F,
	0x20, 0x57,
	0x22, 0x21,	/* New - ver 1.03 */
	0x23, 0x3C,	/* New - ver 1.10 */
	0x24, 0x20,	/* New - ver 1.03 */
	0x2C, 0x24,	/*  bit at 0x20 is cleared below  */
	0x2D, 0x87,	/*  FIFFQ=0  */
	0x2F, 0xF3,
	0x30, 0x0C,	/* New - ver 1.11 */
	0x31, 0x1B,	/* New - ver 1.11 */
	0x2C, 0x04,	/*  bit at 0x20 is cleared here  */
	0x28, 0xE1,	/*  Set the FIFCrst bit here      */
	0x28, 0xE0,	/*  Clear the FIFCrst bit here    */
	0x00
पूर्ण;

/* writing 0x05 0xf0 sw-resets all रेजिस्टरs, so we ग_लिखो only needed changes */
अटल स्थिर u8 MT2063B3_शेषs[] = अणु
	/* Reg,  Value */
	0x05, 0xF0,
	0x19, 0x3D,
	0x2C, 0x24,	/*  bit at 0x20 is cleared below  */
	0x2C, 0x04,	/*  bit at 0x20 is cleared here  */
	0x28, 0xE1,	/*  Set the FIFCrst bit here      */
	0x28, 0xE0,	/*  Clear the FIFCrst bit here    */
	0x00
पूर्ण;

अटल पूर्णांक mt2063_init(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक status;
	काष्ठा mt2063_state *state = fe->tuner_priv;
	u8 all_resets = 0xF0;	/* reset/load bits */
	स्थिर u8 *def = शून्य;
	अक्षर *step;
	u32 FCRUN;
	s32 maxReads;
	u32 fcu_osc;
	u32 i;

	dprपूर्णांकk(2, "\n");

	state->rcvr_mode = MT2063_CABLE_QAM;

	/*  Read the Part/Rev code from the tuner */
	status = mt2063_पढ़ो(state, MT2063_REG_PART_REV,
			     &state->reg[MT2063_REG_PART_REV], 1);
	अगर (status < 0) अणु
		prपूर्णांकk(KERN_ERR "Can't read mt2063 part ID\n");
		वापस status;
	पूर्ण

	/* Check the part/rev code */
	चयन (state->reg[MT2063_REG_PART_REV]) अणु
	हाल MT2063_B0:
		step = "B0";
		अवरोध;
	हाल MT2063_B1:
		step = "B1";
		अवरोध;
	हाल MT2063_B2:
		step = "B2";
		अवरोध;
	हाल MT2063_B3:
		step = "B3";
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "mt2063: Unknown mt2063 device ID (0x%02x)\n",
		       state->reg[MT2063_REG_PART_REV]);
		वापस -ENODEV;	/*  Wrong tuner Part/Rev code */
	पूर्ण

	/*  Check the 2nd byte of the Part/Rev code from the tuner */
	status = mt2063_पढ़ो(state, MT2063_REG_RSVD_3B,
			     &state->reg[MT2063_REG_RSVD_3B], 1);

	/* b7 != 0 ==> NOT MT2063 */
	अगर (status < 0 || ((state->reg[MT2063_REG_RSVD_3B] & 0x80) != 0x00)) अणु
		prपूर्णांकk(KERN_ERR "mt2063: Unknown part ID (0x%02x%02x)\n",
		       state->reg[MT2063_REG_PART_REV],
		       state->reg[MT2063_REG_RSVD_3B]);
		वापस -ENODEV;	/*  Wrong tuner Part/Rev code */
	पूर्ण

	prपूर्णांकk(KERN_INFO "mt2063: detected a mt2063 %s\n", step);

	/*  Reset the tuner  */
	status = mt2063_ग_लिखो(state, MT2063_REG_LO2CQ_3, &all_resets, 1);
	अगर (status < 0)
		वापस status;

	/* change all of the शेष values that vary from the HW reset values */
	/*  def = (state->reg[PART_REV] == MT2063_B0) ? MT2063B0_शेषs : MT2063B1_शेषs; */
	चयन (state->reg[MT2063_REG_PART_REV]) अणु
	हाल MT2063_B3:
		def = MT2063B3_शेषs;
		अवरोध;

	हाल MT2063_B1:
		def = MT2063B1_शेषs;
		अवरोध;

	हाल MT2063_B0:
		def = MT2063B0_शेषs;
		अवरोध;

	शेष:
		वापस -ENODEV;
	पूर्ण

	जबतक (status >= 0 && *def) अणु
		u8 reg = *def++;
		u8 val = *def++;
		status = mt2063_ग_लिखो(state, reg, &val, 1);
	पूर्ण
	अगर (status < 0)
		वापस status;

	/*  Wait क्रम FIFF location to complete.  */
	FCRUN = 1;
	maxReads = 10;
	जबतक (status >= 0 && (FCRUN != 0) && (maxReads-- > 0)) अणु
		msleep(2);
		status = mt2063_पढ़ो(state,
					 MT2063_REG_XO_STATUS,
					 &state->
					 reg[MT2063_REG_XO_STATUS], 1);
		FCRUN = (state->reg[MT2063_REG_XO_STATUS] & 0x40) >> 6;
	पूर्ण

	अगर (FCRUN != 0 || status < 0)
		वापस -ENODEV;

	status = mt2063_पढ़ो(state,
			   MT2063_REG_FIFFC,
			   &state->reg[MT2063_REG_FIFFC], 1);
	अगर (status < 0)
		वापस status;

	/* Read back all the रेजिस्टरs from the tuner */
	status = mt2063_पढ़ो(state,
				MT2063_REG_PART_REV,
				state->reg, MT2063_REG_END_REGS);
	अगर (status < 0)
		वापस status;

	/*  Initialize the tuner state.  */
	state->tuner_id = state->reg[MT2063_REG_PART_REV];
	state->AS_Data.f_ref = MT2063_REF_FREQ;
	state->AS_Data.f_अगर1_Center = (state->AS_Data.f_ref / 8) *
				      ((u32) state->reg[MT2063_REG_FIFFC] + 640);
	state->AS_Data.f_अगर1_bw = MT2063_IF1_BW;
	state->AS_Data.f_out = 43750000UL;
	state->AS_Data.f_out_bw = 6750000UL;
	state->AS_Data.f_zअगर_bw = MT2063_ZIF_BW;
	state->AS_Data.f_LO1_Step = state->AS_Data.f_ref / 64;
	state->AS_Data.f_LO2_Step = MT2063_TUNE_STEP_SIZE;
	state->AS_Data.maxH1 = MT2063_MAX_HARMONICS_1;
	state->AS_Data.maxH2 = MT2063_MAX_HARMONICS_2;
	state->AS_Data.f_min_LO_Separation = MT2063_MIN_LO_SEP;
	state->AS_Data.f_अगर1_Request = state->AS_Data.f_अगर1_Center;
	state->AS_Data.f_LO1 = 2181000000UL;
	state->AS_Data.f_LO2 = 1486249786UL;
	state->f_IF1_actual = state->AS_Data.f_अगर1_Center;
	state->AS_Data.f_in = state->AS_Data.f_LO1 - state->f_IF1_actual;
	state->AS_Data.f_LO1_FracN_Aव्योम = MT2063_LO1_FRACN_AVOID;
	state->AS_Data.f_LO2_FracN_Aव्योम = MT2063_LO2_FRACN_AVOID;
	state->num_regs = MT2063_REG_END_REGS;
	state->AS_Data.aव्योमDECT = MT2063_AVOID_BOTH;
	state->ctfilt_sw = 0;

	state->CTFiltMax[0] = 69230000;
	state->CTFiltMax[1] = 105770000;
	state->CTFiltMax[2] = 140350000;
	state->CTFiltMax[3] = 177110000;
	state->CTFiltMax[4] = 212860000;
	state->CTFiltMax[5] = 241130000;
	state->CTFiltMax[6] = 274370000;
	state->CTFiltMax[7] = 309820000;
	state->CTFiltMax[8] = 342450000;
	state->CTFiltMax[9] = 378870000;
	state->CTFiltMax[10] = 416210000;
	state->CTFiltMax[11] = 456500000;
	state->CTFiltMax[12] = 495790000;
	state->CTFiltMax[13] = 534530000;
	state->CTFiltMax[14] = 572610000;
	state->CTFiltMax[15] = 598970000;
	state->CTFiltMax[16] = 635910000;
	state->CTFiltMax[17] = 672130000;
	state->CTFiltMax[18] = 714840000;
	state->CTFiltMax[19] = 739660000;
	state->CTFiltMax[20] = 770410000;
	state->CTFiltMax[21] = 814660000;
	state->CTFiltMax[22] = 846950000;
	state->CTFiltMax[23] = 867820000;
	state->CTFiltMax[24] = 915980000;
	state->CTFiltMax[25] = 947450000;
	state->CTFiltMax[26] = 983110000;
	state->CTFiltMax[27] = 1021630000;
	state->CTFiltMax[28] = 1061870000;
	state->CTFiltMax[29] = 1098330000;
	state->CTFiltMax[30] = 1138990000;

	/*
	 **   Fetch the FCU osc value and use it and the fRef value to
	 **   scale all of the Band Max values
	 */

	state->reg[MT2063_REG_CTUNE_CTRL] = 0x0A;
	status = mt2063_ग_लिखो(state, MT2063_REG_CTUNE_CTRL,
			      &state->reg[MT2063_REG_CTUNE_CTRL], 1);
	अगर (status < 0)
		वापस status;

	/*  Read the ClearTune filter calibration value  */
	status = mt2063_पढ़ो(state, MT2063_REG_FIFFC,
			     &state->reg[MT2063_REG_FIFFC], 1);
	अगर (status < 0)
		वापस status;

	fcu_osc = state->reg[MT2063_REG_FIFFC];

	state->reg[MT2063_REG_CTUNE_CTRL] = 0x00;
	status = mt2063_ग_लिखो(state, MT2063_REG_CTUNE_CTRL,
			      &state->reg[MT2063_REG_CTUNE_CTRL], 1);
	अगर (status < 0)
		वापस status;

	/*  Adjust each of the values in the ClearTune filter cross-over table  */
	क्रम (i = 0; i < 31; i++)
		state->CTFiltMax[i] = (state->CTFiltMax[i] / 768) * (fcu_osc + 640);

	status = MT2063_SoftwareShutकरोwn(state, 1);
	अगर (status < 0)
		वापस status;
	status = MT2063_ClearPowerMaskBits(state, MT2063_ALL_SD);
	अगर (status < 0)
		वापस status;

	state->init = true;

	वापस 0;
पूर्ण

अटल पूर्णांक mt2063_get_status(काष्ठा dvb_frontend *fe, u32 *tuner_status)
अणु
	काष्ठा mt2063_state *state = fe->tuner_priv;
	पूर्णांक status;

	dprपूर्णांकk(2, "\n");

	अगर (!state->init)
		वापस -ENODEV;

	*tuner_status = 0;
	status = mt2063_lockStatus(state);
	अगर (status < 0)
		वापस status;
	अगर (status)
		*tuner_status = TUNER_STATUS_LOCKED;

	dprपूर्णांकk(1, "Tuner status: %d", *tuner_status);

	वापस 0;
पूर्ण

अटल व्योम mt2063_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mt2063_state *state = fe->tuner_priv;

	dprपूर्णांकk(2, "\n");

	fe->tuner_priv = शून्य;
	kमुक्त(state);
पूर्ण

अटल पूर्णांक mt2063_set_analog_params(काष्ठा dvb_frontend *fe,
				    काष्ठा analog_parameters *params)
अणु
	काष्ठा mt2063_state *state = fe->tuner_priv;
	s32 pict_car;
	s32 pict2chanb_vsb;
	s32 ch_bw;
	s32 अगर_mid;
	s32 rcvr_mode;
	पूर्णांक status;

	dprपूर्णांकk(2, "\n");

	अगर (!state->init) अणु
		status = mt2063_init(fe);
		अगर (status < 0)
			वापस status;
	पूर्ण

	चयन (params->mode) अणु
	हाल V4L2_TUNER_RADIO:
		pict_car = 38900000;
		ch_bw = 8000000;
		pict2chanb_vsb = -(ch_bw / 2);
		rcvr_mode = MT2063_OFFAIR_ANALOG;
		अवरोध;
	हाल V4L2_TUNER_ANALOG_TV:
		rcvr_mode = MT2063_CABLE_ANALOG;
		अगर (params->std & ~V4L2_STD_MN) अणु
			pict_car = 38900000;
			ch_bw = 6000000;
			pict2chanb_vsb = -1250000;
		पूर्ण अन्यथा अगर (params->std & V4L2_STD_PAL_G) अणु
			pict_car = 38900000;
			ch_bw = 7000000;
			pict2chanb_vsb = -1250000;
		पूर्ण अन्यथा अणु		/* PAL/SECAM standards */
			pict_car = 38900000;
			ch_bw = 8000000;
			pict2chanb_vsb = -1250000;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर_mid = pict_car - (pict2chanb_vsb + (ch_bw / 2));

	state->AS_Data.f_LO2_Step = 125000;	/* FIXME: probably 5000 क्रम FM */
	state->AS_Data.f_out = अगर_mid;
	state->AS_Data.f_out_bw = ch_bw + 750000;
	status = MT2063_SetReceiverMode(state, rcvr_mode);
	अगर (status < 0)
		वापस status;

	dprपूर्णांकk(1, "Tuning to frequency: %d, bandwidth %d, foffset %d\n",
		params->frequency, ch_bw, pict2chanb_vsb);

	status = MT2063_Tune(state, (params->frequency + (pict2chanb_vsb + (ch_bw / 2))));
	अगर (status < 0)
		वापस status;

	state->frequency = params->frequency;
	वापस 0;
पूर्ण

/*
 * As defined on EN 300 429, the DVB-C roll-off factor is 0.15.
 * So, the amount of the needed bandwidth is given by:
 *	Bw = Symbol_rate * (1 + 0.15)
 * As such, the maximum symbol rate supported by 6 MHz is given by:
 *	max_symbol_rate = 6 MHz / 1.15 = 5217391 Bauds
 */
#घोषणा MAX_SYMBOL_RATE_6MHz	5217391

अटल पूर्णांक mt2063_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा mt2063_state *state = fe->tuner_priv;
	पूर्णांक status;
	s32 pict_car;
	s32 pict2chanb_vsb;
	s32 ch_bw;
	s32 अगर_mid;
	s32 rcvr_mode;

	अगर (!state->init) अणु
		status = mt2063_init(fe);
		अगर (status < 0)
			वापस status;
	पूर्ण

	dprपूर्णांकk(2, "\n");

	अगर (c->bandwidth_hz == 0)
		वापस -EINVAL;
	अगर (c->bandwidth_hz <= 6000000)
		ch_bw = 6000000;
	अन्यथा अगर (c->bandwidth_hz <= 7000000)
		ch_bw = 7000000;
	अन्यथा
		ch_bw = 8000000;

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBT:
		rcvr_mode = MT2063_OFFAIR_COFDM;
		pict_car = 36125000;
		pict2chanb_vsb = -(ch_bw / 2);
		अवरोध;
	हाल SYS_DVBC_ANNEX_A:
	हाल SYS_DVBC_ANNEX_C:
		rcvr_mode = MT2063_CABLE_QAM;
		pict_car = 36125000;
		pict2chanb_vsb = -(ch_bw / 2);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर_mid = pict_car - (pict2chanb_vsb + (ch_bw / 2));

	state->AS_Data.f_LO2_Step = 125000;	/* FIXME: probably 5000 क्रम FM */
	state->AS_Data.f_out = अगर_mid;
	state->AS_Data.f_out_bw = ch_bw + 750000;
	status = MT2063_SetReceiverMode(state, rcvr_mode);
	अगर (status < 0)
		वापस status;

	dprपूर्णांकk(1, "Tuning to frequency: %d, bandwidth %d, foffset %d\n",
		c->frequency, ch_bw, pict2chanb_vsb);

	status = MT2063_Tune(state, (c->frequency + (pict2chanb_vsb + (ch_bw / 2))));

	अगर (status < 0)
		वापस status;

	state->frequency = c->frequency;
	वापस 0;
पूर्ण

अटल पूर्णांक mt2063_get_अगर_frequency(काष्ठा dvb_frontend *fe, u32 *freq)
अणु
	काष्ठा mt2063_state *state = fe->tuner_priv;

	dprपूर्णांकk(2, "\n");

	अगर (!state->init)
		वापस -ENODEV;

	*freq = state->AS_Data.f_out;

	dprपूर्णांकk(1, "IF frequency: %d\n", *freq);

	वापस 0;
पूर्ण

अटल पूर्णांक mt2063_get_bandwidth(काष्ठा dvb_frontend *fe, u32 *bw)
अणु
	काष्ठा mt2063_state *state = fe->tuner_priv;

	dprपूर्णांकk(2, "\n");

	अगर (!state->init)
		वापस -ENODEV;

	*bw = state->AS_Data.f_out_bw - 750000;

	dprपूर्णांकk(1, "bandwidth: %d\n", *bw);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops mt2063_ops = अणु
	.info = अणु
		 .name = "MT2063 Silicon Tuner",
		 .frequency_min_hz  =  45 * MHz,
		 .frequency_max_hz  = 865 * MHz,
	 पूर्ण,

	.init = mt2063_init,
	.sleep = MT2063_Sleep,
	.get_status = mt2063_get_status,
	.set_analog_params = mt2063_set_analog_params,
	.set_params    = mt2063_set_params,
	.get_अगर_frequency = mt2063_get_अगर_frequency,
	.get_bandwidth = mt2063_get_bandwidth,
	.release = mt2063_release,
पूर्ण;

काष्ठा dvb_frontend *mt2063_attach(काष्ठा dvb_frontend *fe,
				   काष्ठा mt2063_config *config,
				   काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा mt2063_state *state = शून्य;

	dprपूर्णांकk(2, "\n");

	state = kzalloc(माप(काष्ठा mt2063_state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	state->config = config;
	state->i2c = i2c;
	state->frontend = fe;
	state->reference = config->refघड़ी / 1000;	/* kHz */
	fe->tuner_priv = state;
	fe->ops.tuner_ops = mt2063_ops;

	prपूर्णांकk(KERN_INFO "%s: Attaching MT2063\n", __func__);
	वापस fe;
पूर्ण
EXPORT_SYMBOL_GPL(mt2063_attach);

#अगर 0
/*
 * Ancillary routines visible outside mt2063
 * FIXME: Remove them in favor of using standard tuner callbacks
 */
अटल पूर्णांक tuner_MT2063_SoftwareShutकरोwn(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mt2063_state *state = fe->tuner_priv;
	पूर्णांक err = 0;

	dprपूर्णांकk(2, "\n");

	err = MT2063_SoftwareShutकरोwn(state, 1);
	अगर (err < 0)
		prपूर्णांकk(KERN_ERR "%s: Couldn't shutdown\n", __func__);

	वापस err;
पूर्ण

अटल पूर्णांक tuner_MT2063_ClearPowerMaskBits(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा mt2063_state *state = fe->tuner_priv;
	पूर्णांक err = 0;

	dprपूर्णांकk(2, "\n");

	err = MT2063_ClearPowerMaskBits(state, MT2063_ALL_SD);
	अगर (err < 0)
		prपूर्णांकk(KERN_ERR "%s: Invalid parameter\n", __func__);

	वापस err;
पूर्ण
#पूर्ण_अगर

MODULE_AUTHOR("Mauro Carvalho Chehab");
MODULE_DESCRIPTION("MT2063 Silicon tuner");
MODULE_LICENSE("GPL");
