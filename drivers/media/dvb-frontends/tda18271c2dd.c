<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tda18271c2dd: Driver क्रम the TDA18271C2 tuner
 *
 * Copyright (C) 2010 Digital Devices GmbH
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/i2c.h>
#समावेश <यंत्र/भाग64.h>

#समावेश <media/dvb_frontend.h>
#समावेश "tda18271c2dd.h"

/* Max transfer size करोne by I2C transfer functions */
#घोषणा MAX_XFER_SIZE  64

काष्ठा SStandardParam अणु
	s32   m_IFFrequency;
	u32   m_BandWidth;
	u8    m_EP3_4_0;
	u8    m_EB22;
पूर्ण;

काष्ठा SMap अणु
	u32   m_Frequency;
	u8    m_Param;
पूर्ण;

काष्ठा SMapI अणु
	u32   m_Frequency;
	s32    m_Param;
पूर्ण;

काष्ठा SMap2 अणु
	u32   m_Frequency;
	u8    m_Param1;
	u8    m_Param2;
पूर्ण;

काष्ठा SRFBandMap अणु
	u32   m_RF_max;
	u32   m_RF1_Default;
	u32   m_RF2_Default;
	u32   m_RF3_Default;
पूर्ण;

क्रमागत ERegister अणु
	ID = 0,
	TM,
	PL,
	EP1, EP2, EP3, EP4, EP5,
	CPD, CD1, CD2, CD3,
	MPD, MD1, MD2, MD3,
	EB1, EB2, EB3, EB4, EB5, EB6, EB7, EB8, EB9, EB10,
	EB11, EB12, EB13, EB14, EB15, EB16, EB17, EB18, EB19, EB20,
	EB21, EB22, EB23,
	NUM_REGS
पूर्ण;

काष्ठा tda_state अणु
	काष्ठा i2c_adapter *i2c;
	u8 adr;

	u32   m_Frequency;
	u32   IF;

	u8    m_IFLevelAnalog;
	u8    m_IFLevelDigital;
	u8    m_IFLevelDVBC;
	u8    m_IFLevelDVBT;

	u8    m_EP4;
	u8    m_EP3_Standby;

	bool  m_bMaster;

	s32   m_SettlingTime;

	u8    m_Regs[NUM_REGS];

	/* Tracking filter settings क्रम band 0..6 */
	u32   m_RF1[7];
	s32   m_RF_A1[7];
	s32   m_RF_B1[7];
	u32   m_RF2[7];
	s32   m_RF_A2[7];
	s32   m_RF_B2[7];
	u32   m_RF3[7];

	u8    m_TMValue_RFCal;    /* Calibration temperature */

	bool  m_bFMInput;         /* true to use Pin 8 क्रम FM Radio */

पूर्ण;

अटल पूर्णांक PowerScan(काष्ठा tda_state *state,
		     u8 RFBand, u32 RF_in,
		     u32 *pRF_Out, bool *pbcal);

अटल पूर्णांक i2c_पढ़ोn(काष्ठा i2c_adapter *adapter, u8 adr, u8 *data, पूर्णांक len)
अणु
	काष्ठा i2c_msg msgs[1] = अणुअणु.addr = adr,  .flags = I2C_M_RD,
				   .buf  = data, .len   = lenपूर्ण पूर्ण;
	वापस (i2c_transfer(adapter, msgs, 1) == 1) ? 0 : -1;
पूर्ण

अटल पूर्णांक i2c_ग_लिखो(काष्ठा i2c_adapter *adap, u8 adr, u8 *data, पूर्णांक len)
अणु
	काष्ठा i2c_msg msg = अणु.addr = adr, .flags = 0,
			      .buf = data, .len = lenपूर्ण;

	अगर (i2c_transfer(adap, &msg, 1) != 1) अणु
		prपूर्णांकk(KERN_ERR "tda18271c2dd: i2c write error at addr %i\n", adr);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक WriteRegs(काष्ठा tda_state *state,
		     u8 SubAddr, u8 *Regs, u16 nRegs)
अणु
	u8 data[MAX_XFER_SIZE];

	अगर (1 + nRegs > माप(data)) अणु
		prपूर्णांकk(KERN_WARNING
		       "%s: i2c wr: len=%d is too big!\n",
		       KBUILD_MODNAME, nRegs);
		वापस -EINVAL;
	पूर्ण

	data[0] = SubAddr;
	स_नकल(data + 1, Regs, nRegs);
	वापस i2c_ग_लिखो(state->i2c, state->adr, data, nRegs + 1);
पूर्ण

अटल पूर्णांक WriteReg(काष्ठा tda_state *state, u8 SubAddr, u8 Reg)
अणु
	u8 msg[2] = अणुSubAddr, Regपूर्ण;

	वापस i2c_ग_लिखो(state->i2c, state->adr, msg, 2);
पूर्ण

अटल पूर्णांक Read(काष्ठा tda_state *state, u8 * Regs)
अणु
	वापस i2c_पढ़ोn(state->i2c, state->adr, Regs, 16);
पूर्ण

अटल पूर्णांक ReadExtented(काष्ठा tda_state *state, u8 * Regs)
अणु
	वापस i2c_पढ़ोn(state->i2c, state->adr, Regs, NUM_REGS);
पूर्ण

अटल पूर्णांक UpdateRegs(काष्ठा tda_state *state, u8 RegFrom, u8 RegTo)
अणु
	वापस WriteRegs(state, RegFrom,
			 &state->m_Regs[RegFrom], RegTo-RegFrom+1);
पूर्ण
अटल पूर्णांक UpdateReg(काष्ठा tda_state *state, u8 Reg)
अणु
	वापस WriteReg(state, Reg, state->m_Regs[Reg]);
पूर्ण

#समावेश "tda18271c2dd_maps.h"

अटल व्योम reset(काष्ठा tda_state *state)
अणु
	u32   ulIFLevelAnalog = 0;
	u32   ulIFLevelDigital = 2;
	u32   ulIFLevelDVBC = 7;
	u32   ulIFLevelDVBT = 6;
	u32   ulXTOut = 0;
	u32   ulStandbyMode = 0x06;    /* Send in stdb, but leave osc on */
	u32   ulSlave = 0;
	u32   ulFMInput = 0;
	u32   ulSettlingTime = 100;

	state->m_Frequency         = 0;
	state->m_SettlingTime = 100;
	state->m_IFLevelAnalog = (ulIFLevelAnalog & 0x07) << 2;
	state->m_IFLevelDigital = (ulIFLevelDigital & 0x07) << 2;
	state->m_IFLevelDVBC = (ulIFLevelDVBC & 0x07) << 2;
	state->m_IFLevelDVBT = (ulIFLevelDVBT & 0x07) << 2;

	state->m_EP4 = 0x20;
	अगर (ulXTOut != 0)
		state->m_EP4 |= 0x40;

	state->m_EP3_Standby = ((ulStandbyMode & 0x07) << 5) | 0x0F;
	state->m_bMaster = (ulSlave == 0);

	state->m_SettlingTime = ulSettlingTime;

	state->m_bFMInput = (ulFMInput == 2);
पूर्ण

अटल bool SearchMap1(स्थिर काष्ठा SMap map[], u32 frequency, u8 *param)
अणु
	पूर्णांक i = 0;

	जबतक ((map[i].m_Frequency != 0) && (frequency > map[i].m_Frequency))
		i += 1;
	अगर (map[i].m_Frequency == 0)
		वापस false;
	*param = map[i].m_Param;
	वापस true;
पूर्ण

अटल bool SearchMap2(स्थिर काष्ठा SMapI map[], u32 frequency, s32 *param)
अणु
	पूर्णांक i = 0;

	जबतक ((map[i].m_Frequency != 0) &&
	       (frequency > map[i].m_Frequency))
		i += 1;
	अगर (map[i].m_Frequency == 0)
		वापस false;
	*param = map[i].m_Param;
	वापस true;
पूर्ण

अटल bool SearchMap3(स्थिर काष्ठा SMap2 map[], u32 frequency, u8 *param1,
		       u8 *param2)
अणु
	पूर्णांक i = 0;

	जबतक ((map[i].m_Frequency != 0) &&
	       (frequency > map[i].m_Frequency))
		i += 1;
	अगर (map[i].m_Frequency == 0)
		वापस false;
	*param1 = map[i].m_Param1;
	*param2 = map[i].m_Param2;
	वापस true;
पूर्ण

अटल bool SearchMap4(स्थिर काष्ठा SRFBandMap map[], u32 frequency, u8 *rfband)
अणु
	पूर्णांक i = 0;

	जबतक (i < 7 && (frequency > map[i].m_RF_max))
		i += 1;
	अगर (i == 7)
		वापस false;
	*rfband = i;
	वापस true;
पूर्ण

अटल पूर्णांक ThermometerRead(काष्ठा tda_state *state, u8 *pTM_Value)
अणु
	पूर्णांक status = 0;

	करो अणु
		u8 Regs[16];
		state->m_Regs[TM] |= 0x10;
		status = UpdateReg(state, TM);
		अगर (status < 0)
			अवरोध;
		status = Read(state, Regs);
		अगर (status < 0)
			अवरोध;
		अगर (((Regs[TM] & 0x0F) == 0 && (Regs[TM] & 0x20) == 0x20) ||
		    ((Regs[TM] & 0x0F) == 8 && (Regs[TM] & 0x20) == 0x00)) अणु
			state->m_Regs[TM] ^= 0x20;
			status = UpdateReg(state, TM);
			अगर (status < 0)
				अवरोध;
			msleep(10);
			status = Read(state, Regs);
			अगर (status < 0)
				अवरोध;
		पूर्ण
		*pTM_Value = (Regs[TM] & 0x20)
				? m_Thermometer_Map_2[Regs[TM] & 0x0F]
				: m_Thermometer_Map_1[Regs[TM] & 0x0F] ;
		state->m_Regs[TM] &= ~0x10;        /* Thermometer off */
		status = UpdateReg(state, TM);
		अगर (status < 0)
			अवरोध;
		state->m_Regs[EP4] &= ~0x03;       /* CAL_mode = 0 ????????? */
		status = UpdateReg(state, EP4);
		अगर (status < 0)
			अवरोध;
	पूर्ण जबतक (0);

	वापस status;
पूर्ण

अटल पूर्णांक StandBy(काष्ठा tda_state *state)
अणु
	पूर्णांक status = 0;
	करो अणु
		state->m_Regs[EB12] &= ~0x20;  /* PD_AGC1_Det = 0 */
		status = UpdateReg(state, EB12);
		अगर (status < 0)
			अवरोध;
		state->m_Regs[EB18] &= ~0x83;  /* AGC1_loop_off = 0, AGC1_Gain = 6 dB */
		status = UpdateReg(state, EB18);
		अगर (status < 0)
			अवरोध;
		state->m_Regs[EB21] |= 0x03; /* AGC2_Gain = -6 dB */
		state->m_Regs[EP3] = state->m_EP3_Standby;
		status = UpdateReg(state, EP3);
		अगर (status < 0)
			अवरोध;
		state->m_Regs[EB23] &= ~0x06; /* ForceLP_Fc2_En = 0, LP_Fc[2] = 0 */
		status = UpdateRegs(state, EB21, EB23);
		अगर (status < 0)
			अवरोध;
	पूर्ण जबतक (0);
	वापस status;
पूर्ण

अटल पूर्णांक CalcMainPLL(काष्ठा tda_state *state, u32 freq)
अणु

	u8  PostDiv;
	u8  Div;
	u64 OscFreq;
	u32 MainDiv;

	अगर (!SearchMap3(m_Main_PLL_Map, freq, &PostDiv, &Div))
		वापस -EINVAL;

	OscFreq = (u64) freq * (u64) Div;
	OscFreq *= (u64) 16384;
	करो_भाग(OscFreq, (u64)16000000);
	MainDiv = OscFreq;

	state->m_Regs[MPD] = PostDiv & 0x77;
	state->m_Regs[MD1] = ((MainDiv >> 16) & 0x7F);
	state->m_Regs[MD2] = ((MainDiv >>  8) & 0xFF);
	state->m_Regs[MD3] = (MainDiv & 0xFF);

	वापस UpdateRegs(state, MPD, MD3);
पूर्ण

अटल पूर्णांक CalcCalPLL(काष्ठा tda_state *state, u32 freq)
अणु
	u8 PostDiv;
	u8 Div;
	u64 OscFreq;
	u32 CalDiv;

	अगर (!SearchMap3(m_Cal_PLL_Map, freq, &PostDiv, &Div))
		वापस -EINVAL;

	OscFreq = (u64)freq * (u64)Div;
	/* CalDiv = u32( OscFreq * 16384 / 16000000 ); */
	OscFreq *= (u64)16384;
	करो_भाग(OscFreq, (u64)16000000);
	CalDiv = OscFreq;

	state->m_Regs[CPD] = PostDiv;
	state->m_Regs[CD1] = ((CalDiv >> 16) & 0xFF);
	state->m_Regs[CD2] = ((CalDiv >>  8) & 0xFF);
	state->m_Regs[CD3] = (CalDiv & 0xFF);

	वापस UpdateRegs(state, CPD, CD3);
पूर्ण

अटल पूर्णांक CalibrateRF(काष्ठा tda_state *state,
		       u8 RFBand, u32 freq, s32 *pCprog)
अणु
	पूर्णांक status = 0;
	u8 Regs[NUM_REGS];
	करो अणु
		u8 BP_Filter = 0;
		u8 GainTaper = 0;
		u8 RFC_K = 0;
		u8 RFC_M = 0;

		state->m_Regs[EP4] &= ~0x03; /* CAL_mode = 0 */
		status = UpdateReg(state, EP4);
		अगर (status < 0)
			अवरोध;
		state->m_Regs[EB18] |= 0x03;  /* AGC1_Gain = 3 */
		status = UpdateReg(state, EB18);
		अगर (status < 0)
			अवरोध;

		/* Switching off LT (as datasheet says) causes calibration on C1 to fail */
		/* (Reaकरोut of Cprog is always 255) */
		अगर (state->m_Regs[ID] != 0x83)    /* C1: ID == 83, C2: ID == 84 */
			state->m_Regs[EP3] |= 0x40; /* SM_LT = 1 */

		अगर (!(SearchMap1(m_BP_Filter_Map, freq, &BP_Filter) &&
			SearchMap1(m_GainTaper_Map, freq, &GainTaper) &&
			SearchMap3(m_KM_Map, freq, &RFC_K, &RFC_M)))
			वापस -EINVAL;

		state->m_Regs[EP1] = (state->m_Regs[EP1] & ~0x07) | BP_Filter;
		state->m_Regs[EP2] = (RFBand << 5) | GainTaper;

		state->m_Regs[EB13] = (state->m_Regs[EB13] & ~0x7C) | (RFC_K << 4) | (RFC_M << 2);

		status = UpdateRegs(state, EP1, EP3);
		अगर (status < 0)
			अवरोध;
		status = UpdateReg(state, EB13);
		अगर (status < 0)
			अवरोध;

		state->m_Regs[EB4] |= 0x20;    /* LO_ForceSrce = 1 */
		status = UpdateReg(state, EB4);
		अगर (status < 0)
			अवरोध;

		state->m_Regs[EB7] |= 0x20;    /* CAL_ForceSrce = 1 */
		status = UpdateReg(state, EB7);
		अगर (status < 0)
			अवरोध;

		state->m_Regs[EB14] = 0; /* RFC_Cprog = 0 */
		status = UpdateReg(state, EB14);
		अगर (status < 0)
			अवरोध;

		state->m_Regs[EB20] &= ~0x20;  /* ForceLock = 0; */
		status = UpdateReg(state, EB20);
		अगर (status < 0)
			अवरोध;

		state->m_Regs[EP4] |= 0x03;  /* CAL_Mode = 3 */
		status = UpdateRegs(state, EP4, EP5);
		अगर (status < 0)
			अवरोध;

		status = CalcCalPLL(state, freq);
		अगर (status < 0)
			अवरोध;
		status = CalcMainPLL(state, freq + 1000000);
		अगर (status < 0)
			अवरोध;

		msleep(5);
		status = UpdateReg(state, EP2);
		अगर (status < 0)
			अवरोध;
		status = UpdateReg(state, EP1);
		अगर (status < 0)
			अवरोध;
		status = UpdateReg(state, EP2);
		अगर (status < 0)
			अवरोध;
		status = UpdateReg(state, EP1);
		अगर (status < 0)
			अवरोध;

		state->m_Regs[EB4] &= ~0x20;    /* LO_ForceSrce = 0 */
		status = UpdateReg(state, EB4);
		अगर (status < 0)
			अवरोध;

		state->m_Regs[EB7] &= ~0x20;    /* CAL_ForceSrce = 0 */
		status = UpdateReg(state, EB7);
		अगर (status < 0)
			अवरोध;
		msleep(10);

		state->m_Regs[EB20] |= 0x20;  /* ForceLock = 1; */
		status = UpdateReg(state, EB20);
		अगर (status < 0)
			अवरोध;
		msleep(60);

		state->m_Regs[EP4] &= ~0x03;  /* CAL_Mode = 0 */
		state->m_Regs[EP3] &= ~0x40; /* SM_LT = 0 */
		state->m_Regs[EB18] &= ~0x03;  /* AGC1_Gain = 0 */
		status = UpdateReg(state, EB18);
		अगर (status < 0)
			अवरोध;
		status = UpdateRegs(state, EP3, EP4);
		अगर (status < 0)
			अवरोध;
		status = UpdateReg(state, EP1);
		अगर (status < 0)
			अवरोध;

		status = ReadExtented(state, Regs);
		अगर (status < 0)
			अवरोध;

		*pCprog = Regs[EB14];

	पूर्ण जबतक (0);
	वापस status;
पूर्ण

अटल पूर्णांक RFTrackingFiltersInit(काष्ठा tda_state *state,
				 u8 RFBand)
अणु
	पूर्णांक status = 0;

	u32   RF1 = m_RF_Band_Map[RFBand].m_RF1_Default;
	u32   RF2 = m_RF_Band_Map[RFBand].m_RF2_Default;
	u32   RF3 = m_RF_Band_Map[RFBand].m_RF3_Default;
	bool    bcal = false;

	s32    Cprog_cal1 = 0;
	s32    Cprog_table1 = 0;
	s32    Cprog_cal2 = 0;
	s32    Cprog_table2 = 0;
	s32    Cprog_cal3 = 0;
	s32    Cprog_table3 = 0;

	state->m_RF_A1[RFBand] = 0;
	state->m_RF_B1[RFBand] = 0;
	state->m_RF_A2[RFBand] = 0;
	state->m_RF_B2[RFBand] = 0;

	करो अणु
		status = PowerScan(state, RFBand, RF1, &RF1, &bcal);
		अगर (status < 0)
			अवरोध;
		अगर (bcal) अणु
			status = CalibrateRF(state, RFBand, RF1, &Cprog_cal1);
			अगर (status < 0)
				अवरोध;
		पूर्ण
		SearchMap2(m_RF_Cal_Map, RF1, &Cprog_table1);
		अगर (!bcal)
			Cprog_cal1 = Cprog_table1;
		state->m_RF_B1[RFBand] = Cprog_cal1 - Cprog_table1;
		/* state->m_RF_A1[RF_Band] = ???? */

		अगर (RF2 == 0)
			अवरोध;

		status = PowerScan(state, RFBand, RF2, &RF2, &bcal);
		अगर (status < 0)
			अवरोध;
		अगर (bcal) अणु
			status = CalibrateRF(state, RFBand, RF2, &Cprog_cal2);
			अगर (status < 0)
				अवरोध;
		पूर्ण
		SearchMap2(m_RF_Cal_Map, RF2, &Cprog_table2);
		अगर (!bcal)
			Cprog_cal2 = Cprog_table2;

		state->m_RF_A1[RFBand] =
			(Cprog_cal2 - Cprog_table2 - Cprog_cal1 + Cprog_table1) /
			((s32)(RF2) - (s32)(RF1));

		अगर (RF3 == 0)
			अवरोध;

		status = PowerScan(state, RFBand, RF3, &RF3, &bcal);
		अगर (status < 0)
			अवरोध;
		अगर (bcal) अणु
			status = CalibrateRF(state, RFBand, RF3, &Cprog_cal3);
			अगर (status < 0)
				अवरोध;
		पूर्ण
		SearchMap2(m_RF_Cal_Map, RF3, &Cprog_table3);
		अगर (!bcal)
			Cprog_cal3 = Cprog_table3;
		state->m_RF_A2[RFBand] = (Cprog_cal3 - Cprog_table3 - Cprog_cal2 + Cprog_table2) / ((s32)(RF3) - (s32)(RF2));
		state->m_RF_B2[RFBand] = Cprog_cal2 - Cprog_table2;

	पूर्ण जबतक (0);

	state->m_RF1[RFBand] = RF1;
	state->m_RF2[RFBand] = RF2;
	state->m_RF3[RFBand] = RF3;

#अगर 0
	prपूर्णांकk(KERN_ERR "tda18271c2dd: %s %d RF1 = %d A1 = %d B1 = %d RF2 = %d A2 = %d B2 = %d RF3 = %d\n", __func__,
	       RFBand, RF1, state->m_RF_A1[RFBand], state->m_RF_B1[RFBand], RF2,
	       state->m_RF_A2[RFBand], state->m_RF_B2[RFBand], RF3);
#पूर्ण_अगर

	वापस status;
पूर्ण

अटल पूर्णांक PowerScan(काष्ठा tda_state *state,
		     u8 RFBand, u32 RF_in, u32 *pRF_Out, bool *pbcal)
अणु
	पूर्णांक status = 0;
	करो अणु
		u8   Gain_Taper = 0;
		s32  RFC_Cprog = 0;
		u8   CID_Target = 0;
		u8   CountLimit = 0;
		u32  freq_MainPLL;
		u8   Regs[NUM_REGS];
		u8   CID_Gain;
		s32  Count = 0;
		पूर्णांक  sign  = 1;
		bool रुको = false;

		अगर (!(SearchMap2(m_RF_Cal_Map, RF_in, &RFC_Cprog) &&
		      SearchMap1(m_GainTaper_Map, RF_in, &Gain_Taper) &&
		      SearchMap3(m_CID_Target_Map, RF_in, &CID_Target, &CountLimit))) अणु

			prपूर्णांकk(KERN_ERR "tda18271c2dd: %s Search map failed\n", __func__);
			वापस -EINVAL;
		पूर्ण

		state->m_Regs[EP2] = (RFBand << 5) | Gain_Taper;
		state->m_Regs[EB14] = (RFC_Cprog);
		status = UpdateReg(state, EP2);
		अगर (status < 0)
			अवरोध;
		status = UpdateReg(state, EB14);
		अगर (status < 0)
			अवरोध;

		freq_MainPLL = RF_in + 1000000;
		status = CalcMainPLL(state, freq_MainPLL);
		अगर (status < 0)
			अवरोध;
		msleep(5);
		state->m_Regs[EP4] = (state->m_Regs[EP4] & ~0x03) | 1;    /* CAL_mode = 1 */
		status = UpdateReg(state, EP4);
		अगर (status < 0)
			अवरोध;
		status = UpdateReg(state, EP2);  /* Launch घातer measurement */
		अगर (status < 0)
			अवरोध;
		status = ReadExtented(state, Regs);
		अगर (status < 0)
			अवरोध;
		CID_Gain = Regs[EB10] & 0x3F;
		state->m_Regs[ID] = Regs[ID];  /* Chip version, (needed क्रम C1 workaround in CalibrateRF) */

		*pRF_Out = RF_in;

		जबतक (CID_Gain < CID_Target) अणु
			freq_MainPLL = RF_in + sign * Count + 1000000;
			status = CalcMainPLL(state, freq_MainPLL);
			अगर (status < 0)
				अवरोध;
			msleep(रुको ? 5 : 1);
			रुको = false;
			status = UpdateReg(state, EP2);  /* Launch घातer measurement */
			अगर (status < 0)
				अवरोध;
			status = ReadExtented(state, Regs);
			अगर (status < 0)
				अवरोध;
			CID_Gain = Regs[EB10] & 0x3F;
			Count += 200000;

			अगर (Count < CountLimit * 100000)
				जारी;
			अगर (sign < 0)
				अवरोध;

			sign = -sign;
			Count = 200000;
			रुको = true;
		पूर्ण
		अगर (status < 0)
			अवरोध;
		अगर (CID_Gain >= CID_Target) अणु
			*pbcal = true;
			*pRF_Out = freq_MainPLL - 1000000;
		पूर्ण अन्यथा
			*pbcal = false;
	पूर्ण जबतक (0);

	वापस status;
पूर्ण

अटल पूर्णांक PowerScanInit(काष्ठा tda_state *state)
अणु
	पूर्णांक status = 0;
	करो अणु
		state->m_Regs[EP3] = (state->m_Regs[EP3] & ~0x1F) | 0x12;
		state->m_Regs[EP4] = (state->m_Regs[EP4] & ~0x1F); /* If level = 0, Cal mode = 0 */
		status = UpdateRegs(state, EP3, EP4);
		अगर (status < 0)
			अवरोध;
		state->m_Regs[EB18] = (state->m_Regs[EB18] & ~0x03); /* AGC 1 Gain = 0 */
		status = UpdateReg(state, EB18);
		अगर (status < 0)
			अवरोध;
		state->m_Regs[EB21] = (state->m_Regs[EB21] & ~0x03); /* AGC 2 Gain = 0 (Datasheet = 3) */
		state->m_Regs[EB23] = (state->m_Regs[EB23] | 0x06); /* ForceLP_Fc2_En = 1, LPFc[2] = 1 */
		status = UpdateRegs(state, EB21, EB23);
		अगर (status < 0)
			अवरोध;
	पूर्ण जबतक (0);
	वापस status;
पूर्ण

अटल पूर्णांक CalcRFFilterCurve(काष्ठा tda_state *state)
अणु
	पूर्णांक status = 0;
	करो अणु
		msleep(200);      /* Temperature stabilisation */
		status = PowerScanInit(state);
		अगर (status < 0)
			अवरोध;
		status = RFTrackingFiltersInit(state, 0);
		अगर (status < 0)
			अवरोध;
		status = RFTrackingFiltersInit(state, 1);
		अगर (status < 0)
			अवरोध;
		status = RFTrackingFiltersInit(state, 2);
		अगर (status < 0)
			अवरोध;
		status = RFTrackingFiltersInit(state, 3);
		अगर (status < 0)
			अवरोध;
		status = RFTrackingFiltersInit(state, 4);
		अगर (status < 0)
			अवरोध;
		status = RFTrackingFiltersInit(state, 5);
		अगर (status < 0)
			अवरोध;
		status = RFTrackingFiltersInit(state, 6);
		अगर (status < 0)
			अवरोध;
		status = ThermometerRead(state, &state->m_TMValue_RFCal); /* also चयनes off Cal mode !!! */
		अगर (status < 0)
			अवरोध;
	पूर्ण जबतक (0);

	वापस status;
पूर्ण

अटल पूर्णांक FixedContentsI2CUpdate(काष्ठा tda_state *state)
अणु
	अटल u8 InitRegs[] = अणु
		0x08, 0x80, 0xC6,
		0xDF, 0x16, 0x60, 0x80,
		0x80, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0xFC, 0x01, 0x84, 0x41,
		0x01, 0x84, 0x40, 0x07,
		0x00, 0x00, 0x96, 0x3F,
		0xC1, 0x00, 0x8F, 0x00,
		0x00, 0x8C, 0x00, 0x20,
		0xB3, 0x48, 0xB0,
	पूर्ण;
	पूर्णांक status = 0;
	स_नकल(&state->m_Regs[TM], InitRegs, EB23 - TM + 1);
	करो अणु
		status = UpdateRegs(state, TM, EB23);
		अगर (status < 0)
			अवरोध;

		/* AGC1 gain setup */
		state->m_Regs[EB17] = 0x00;
		status = UpdateReg(state, EB17);
		अगर (status < 0)
			अवरोध;
		state->m_Regs[EB17] = 0x03;
		status = UpdateReg(state, EB17);
		अगर (status < 0)
			अवरोध;
		state->m_Regs[EB17] = 0x43;
		status = UpdateReg(state, EB17);
		अगर (status < 0)
			अवरोध;
		state->m_Regs[EB17] = 0x4C;
		status = UpdateReg(state, EB17);
		अगर (status < 0)
			अवरोध;

		/* IRC Cal Low band */
		state->m_Regs[EP3] = 0x1F;
		state->m_Regs[EP4] = 0x66;
		state->m_Regs[EP5] = 0x81;
		state->m_Regs[CPD] = 0xCC;
		state->m_Regs[CD1] = 0x6C;
		state->m_Regs[CD2] = 0x00;
		state->m_Regs[CD3] = 0x00;
		state->m_Regs[MPD] = 0xC5;
		state->m_Regs[MD1] = 0x77;
		state->m_Regs[MD2] = 0x08;
		state->m_Regs[MD3] = 0x00;
		status = UpdateRegs(state, EP2, MD3); /* dअगरf between sw and datasheet (ep3-md3) */
		अगर (status < 0)
			अवरोध;

#अगर 0
		state->m_Regs[EB4] = 0x61;          /* missing in sw */
		status = UpdateReg(state, EB4);
		अगर (status < 0)
			अवरोध;
		msleep(1);
		state->m_Regs[EB4] = 0x41;
		status = UpdateReg(state, EB4);
		अगर (status < 0)
			अवरोध;
#पूर्ण_अगर

		msleep(5);
		status = UpdateReg(state, EP1);
		अगर (status < 0)
			अवरोध;
		msleep(5);

		state->m_Regs[EP5] = 0x85;
		state->m_Regs[CPD] = 0xCB;
		state->m_Regs[CD1] = 0x66;
		state->m_Regs[CD2] = 0x70;
		status = UpdateRegs(state, EP3, CD3);
		अगर (status < 0)
			अवरोध;
		msleep(5);
		status = UpdateReg(state, EP2);
		अगर (status < 0)
			अवरोध;
		msleep(30);

		/* IRC Cal mid band */
		state->m_Regs[EP5] = 0x82;
		state->m_Regs[CPD] = 0xA8;
		state->m_Regs[CD2] = 0x00;
		state->m_Regs[MPD] = 0xA1; /* Datasheet = 0xA9 */
		state->m_Regs[MD1] = 0x73;
		state->m_Regs[MD2] = 0x1A;
		status = UpdateRegs(state, EP3, MD3);
		अगर (status < 0)
			अवरोध;

		msleep(5);
		status = UpdateReg(state, EP1);
		अगर (status < 0)
			अवरोध;
		msleep(5);

		state->m_Regs[EP5] = 0x86;
		state->m_Regs[CPD] = 0xA8;
		state->m_Regs[CD1] = 0x66;
		state->m_Regs[CD2] = 0xA0;
		status = UpdateRegs(state, EP3, CD3);
		अगर (status < 0)
			अवरोध;
		msleep(5);
		status = UpdateReg(state, EP2);
		अगर (status < 0)
			अवरोध;
		msleep(30);

		/* IRC Cal high band */
		state->m_Regs[EP5] = 0x83;
		state->m_Regs[CPD] = 0x98;
		state->m_Regs[CD1] = 0x65;
		state->m_Regs[CD2] = 0x00;
		state->m_Regs[MPD] = 0x91;  /* Datasheet = 0x91 */
		state->m_Regs[MD1] = 0x71;
		state->m_Regs[MD2] = 0xCD;
		status = UpdateRegs(state, EP3, MD3);
		अगर (status < 0)
			अवरोध;
		msleep(5);
		status = UpdateReg(state, EP1);
		अगर (status < 0)
			अवरोध;
		msleep(5);
		state->m_Regs[EP5] = 0x87;
		state->m_Regs[CD1] = 0x65;
		state->m_Regs[CD2] = 0x50;
		status = UpdateRegs(state, EP3, CD3);
		अगर (status < 0)
			अवरोध;
		msleep(5);
		status = UpdateReg(state, EP2);
		अगर (status < 0)
			अवरोध;
		msleep(30);

		/* Back to normal */
		state->m_Regs[EP4] = 0x64;
		status = UpdateReg(state, EP4);
		अगर (status < 0)
			अवरोध;
		status = UpdateReg(state, EP1);
		अगर (status < 0)
			अवरोध;

	पूर्ण जबतक (0);
	वापस status;
पूर्ण

अटल पूर्णांक InitCal(काष्ठा tda_state *state)
अणु
	पूर्णांक status = 0;

	करो अणु
		status = FixedContentsI2CUpdate(state);
		अगर (status < 0)
			अवरोध;
		status = CalcRFFilterCurve(state);
		अगर (status < 0)
			अवरोध;
		status = StandBy(state);
		अगर (status < 0)
			अवरोध;
		/* m_bInitDone = true; */
	पूर्ण जबतक (0);
	वापस status;
पूर्ण;

अटल पूर्णांक RFTrackingFiltersCorrection(काष्ठा tda_state *state,
				       u32 Frequency)
अणु
	पूर्णांक status = 0;
	s32 Cprog_table;
	u8 RFBand;
	u8 dCoverdT;

	अगर (!SearchMap2(m_RF_Cal_Map, Frequency, &Cprog_table) ||
	    !SearchMap4(m_RF_Band_Map, Frequency, &RFBand) ||
	    !SearchMap1(m_RF_Cal_DC_Over_DT_Map, Frequency, &dCoverdT))

		वापस -EINVAL;

	करो अणु
		u8 TMValue_Current;
		u32   RF1 = state->m_RF1[RFBand];
		u32   RF2 = state->m_RF1[RFBand];
		u32   RF3 = state->m_RF1[RFBand];
		s32    RF_A1 = state->m_RF_A1[RFBand];
		s32    RF_B1 = state->m_RF_B1[RFBand];
		s32    RF_A2 = state->m_RF_A2[RFBand];
		s32    RF_B2 = state->m_RF_B2[RFBand];
		s32 Capprox = 0;
		पूर्णांक TComp;

		state->m_Regs[EP3] &= ~0xE0;  /* Power up */
		status = UpdateReg(state, EP3);
		अगर (status < 0)
			अवरोध;

		status = ThermometerRead(state, &TMValue_Current);
		अगर (status < 0)
			अवरोध;

		अगर (RF3 == 0 || Frequency < RF2)
			Capprox = RF_A1 * ((s32)(Frequency) - (s32)(RF1)) + RF_B1 + Cprog_table;
		अन्यथा
			Capprox = RF_A2 * ((s32)(Frequency) - (s32)(RF2)) + RF_B2 + Cprog_table;

		TComp = (पूर्णांक)(dCoverdT) * ((पूर्णांक)(TMValue_Current) - (पूर्णांक)(state->m_TMValue_RFCal))/1000;

		Capprox += TComp;

		अगर (Capprox < 0)
			Capprox = 0;
		अन्यथा अगर (Capprox > 255)
			Capprox = 255;


		/* TODO Temperature compensation. There is defenitely a scale factor */
		/*      missing in the datasheet, so leave it out क्रम now.           */
		state->m_Regs[EB14] = Capprox;

		status = UpdateReg(state, EB14);
		अगर (status < 0)
			अवरोध;

	पूर्ण जबतक (0);
	वापस status;
पूर्ण

अटल पूर्णांक ChannelConfiguration(काष्ठा tda_state *state,
				u32 Frequency, पूर्णांक Standard)
अणु

	s32 IntermediateFrequency = m_StandardTable[Standard].m_IFFrequency;
	पूर्णांक status = 0;

	u8 BP_Filter = 0;
	u8 RF_Band = 0;
	u8 GainTaper = 0;
	u8 IR_Meas = 0;

	state->IF = IntermediateFrequency;
	/* prपूर्णांकk("tda18271c2dd: %s Freq = %d Standard = %d IF = %d\n", __func__, Frequency, Standard, IntermediateFrequency); */
	/* get values from tables */

	अगर (!(SearchMap1(m_BP_Filter_Map, Frequency, &BP_Filter) &&
	       SearchMap1(m_GainTaper_Map, Frequency, &GainTaper) &&
	       SearchMap1(m_IR_Meas_Map, Frequency, &IR_Meas) &&
	       SearchMap4(m_RF_Band_Map, Frequency, &RF_Band))) अणु

		prपूर्णांकk(KERN_ERR "tda18271c2dd: %s SearchMap failed\n", __func__);
		वापस -EINVAL;
	पूर्ण

	करो अणु
		state->m_Regs[EP3] = (state->m_Regs[EP3] & ~0x1F) | m_StandardTable[Standard].m_EP3_4_0;
		state->m_Regs[EP3] &= ~0x04;   /* चयन RFAGC to high speed mode */

		/* m_EP4 शेष क्रम XToutOn, CAL_Mode (0) */
		state->m_Regs[EP4] = state->m_EP4 | ((Standard > HF_AnalogMax) ? state->m_IFLevelDigital : state->m_IFLevelAnalog);
		/* state->m_Regs[EP4] = state->m_EP4 | state->m_IFLevelDigital; */
		अगर (Standard <= HF_AnalogMax)
			state->m_Regs[EP4] = state->m_EP4 | state->m_IFLevelAnalog;
		अन्यथा अगर (Standard <= HF_ATSC)
			state->m_Regs[EP4] = state->m_EP4 | state->m_IFLevelDVBT;
		अन्यथा अगर (Standard <= HF_DVBC)
			state->m_Regs[EP4] = state->m_EP4 | state->m_IFLevelDVBC;
		अन्यथा
			state->m_Regs[EP4] = state->m_EP4 | state->m_IFLevelDigital;

		अगर ((Standard == HF_FM_Radio) && state->m_bFMInput)
			state->m_Regs[EP4] |= 0x80;

		state->m_Regs[MPD] &= ~0x80;
		अगर (Standard > HF_AnalogMax)
			state->m_Regs[MPD] |= 0x80; /* Add IF_notch क्रम digital */

		state->m_Regs[EB22] = m_StandardTable[Standard].m_EB22;

		/* Note: This is missing from flowअक्षरt in TDA18271 specअगरication ( 1.5 MHz cutoff क्रम FM ) */
		अगर (Standard == HF_FM_Radio)
			state->m_Regs[EB23] |=  0x06; /* ForceLP_Fc2_En = 1, LPFc[2] = 1 */
		अन्यथा
			state->m_Regs[EB23] &= ~0x06; /* ForceLP_Fc2_En = 0, LPFc[2] = 0 */

		status = UpdateRegs(state, EB22, EB23);
		अगर (status < 0)
			अवरोध;

		state->m_Regs[EP1] = (state->m_Regs[EP1] & ~0x07) | 0x40 | BP_Filter;   /* Dis_Power_level = 1, Filter */
		state->m_Regs[EP5] = (state->m_Regs[EP5] & ~0x07) | IR_Meas;
		state->m_Regs[EP2] = (RF_Band << 5) | GainTaper;

		state->m_Regs[EB1] = (state->m_Regs[EB1] & ~0x07) |
			(state->m_bMaster ? 0x04 : 0x00); /* CALVCO_FortLOn = MS */
		/* AGC1_always_master = 0 */
		/* AGC_firstn = 0 */
		status = UpdateReg(state, EB1);
		अगर (status < 0)
			अवरोध;

		अगर (state->m_bMaster) अणु
			status = CalcMainPLL(state, Frequency + IntermediateFrequency);
			अगर (status < 0)
				अवरोध;
			status = UpdateRegs(state, TM, EP5);
			अगर (status < 0)
				अवरोध;
			state->m_Regs[EB4] |= 0x20;    /* LO_क्रमceSrce = 1 */
			status = UpdateReg(state, EB4);
			अगर (status < 0)
				अवरोध;
			msleep(1);
			state->m_Regs[EB4] &= ~0x20;   /* LO_क्रमceSrce = 0 */
			status = UpdateReg(state, EB4);
			अगर (status < 0)
				अवरोध;
		पूर्ण अन्यथा अणु
			u8 PostDiv = 0;
			u8 Div;
			status = CalcCalPLL(state, Frequency + IntermediateFrequency);
			अगर (status < 0)
				अवरोध;

			SearchMap3(m_Cal_PLL_Map, Frequency + IntermediateFrequency, &PostDiv, &Div);
			state->m_Regs[MPD] = (state->m_Regs[MPD] & ~0x7F) | (PostDiv & 0x77);
			status = UpdateReg(state, MPD);
			अगर (status < 0)
				अवरोध;
			status = UpdateRegs(state, TM, EP5);
			अगर (status < 0)
				अवरोध;

			state->m_Regs[EB7] |= 0x20;    /* CAL_क्रमceSrce = 1 */
			status = UpdateReg(state, EB7);
			अगर (status < 0)
				अवरोध;
			msleep(1);
			state->m_Regs[EB7] &= ~0x20;   /* CAL_क्रमceSrce = 0 */
			status = UpdateReg(state, EB7);
			अगर (status < 0)
				अवरोध;
		पूर्ण
		msleep(20);
		अगर (Standard != HF_FM_Radio)
			state->m_Regs[EP3] |= 0x04;    /* RFAGC to normal mode */
		status = UpdateReg(state, EP3);
		अगर (status < 0)
			अवरोध;

	पूर्ण जबतक (0);
	वापस status;
पूर्ण

अटल पूर्णांक sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda_state *state = fe->tuner_priv;

	StandBy(state);
	वापस 0;
पूर्ण

अटल पूर्णांक init(काष्ठा dvb_frontend *fe)
अणु
	वापस 0;
पूर्ण

अटल व्योम release(काष्ठा dvb_frontend *fe)
अणु
	kमुक्त(fe->tuner_priv);
	fe->tuner_priv = शून्य;
पूर्ण


अटल पूर्णांक set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda_state *state = fe->tuner_priv;
	पूर्णांक status = 0;
	पूर्णांक Standard;
	u32 bw = fe->dtv_property_cache.bandwidth_hz;
	u32 delsys  = fe->dtv_property_cache.delivery_प्रणाली;

	state->m_Frequency = fe->dtv_property_cache.frequency;

	चयन (delsys) अणु
	हाल  SYS_DVBT:
	हाल  SYS_DVBT2:
		चयन (bw) अणु
		हाल 6000000:
			Standard = HF_DVBT_6MHZ;
			अवरोध;
		हाल 7000000:
			Standard = HF_DVBT_7MHZ;
			अवरोध;
		हाल 8000000:
			Standard = HF_DVBT_8MHZ;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल SYS_DVBC_ANNEX_A:
	हाल SYS_DVBC_ANNEX_C:
		अगर (bw <= 6000000)
			Standard = HF_DVBC_6MHZ;
		अन्यथा अगर (bw <= 7000000)
			Standard = HF_DVBC_7MHZ;
		अन्यथा
			Standard = HF_DVBC_8MHZ;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	करो अणु
		status = RFTrackingFiltersCorrection(state, state->m_Frequency);
		अगर (status < 0)
			अवरोध;
		status = ChannelConfiguration(state, state->m_Frequency,
					      Standard);
		अगर (status < 0)
			अवरोध;

		msleep(state->m_SettlingTime);  /* Allow AGC's to settle करोwn */
	पूर्ण जबतक (0);
	वापस status;
पूर्ण

#अगर 0
अटल पूर्णांक GetSignalStrength(s32 *pSignalStrength, u32 RFAgc, u32 IFAgc)
अणु
	अगर (IFAgc < 500) अणु
		/* Scale this from 0 to 50000 */
		*pSignalStrength = IFAgc * 100;
	पूर्ण अन्यथा अणु
		/* Scale range 500-1500 to 50000-80000 */
		*pSignalStrength = 50000 + (IFAgc - 500) * 30;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक get_अगर_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा tda_state *state = fe->tuner_priv;

	*frequency = state->IF;
	वापस 0;
पूर्ण

अटल पूर्णांक get_bandwidth(काष्ठा dvb_frontend *fe, u32 *bandwidth)
अणु
	/* काष्ठा tda_state *state = fe->tuner_priv; */
	/* *bandwidth = priv->bandwidth; */
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा dvb_tuner_ops tuner_ops = अणु
	.info = अणु
		.name = "NXP TDA18271C2D",
		.frequency_min_hz  =  47125 * kHz,
		.frequency_max_hz  =    865 * MHz,
		.frequency_step_hz =  62500
	पूर्ण,
	.init              = init,
	.sleep             = sleep,
	.set_params        = set_params,
	.release           = release,
	.get_अगर_frequency  = get_अगर_frequency,
	.get_bandwidth     = get_bandwidth,
पूर्ण;

काष्ठा dvb_frontend *tda18271c2dd_attach(काष्ठा dvb_frontend *fe,
					 काष्ठा i2c_adapter *i2c, u8 adr)
अणु
	काष्ठा tda_state *state;

	state = kzalloc(माप(काष्ठा tda_state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	fe->tuner_priv = state;
	state->adr = adr;
	state->i2c = i2c;
	स_नकल(&fe->ops.tuner_ops, &tuner_ops, माप(काष्ठा dvb_tuner_ops));
	reset(state);
	InitCal(state);

	वापस fe;
पूर्ण
EXPORT_SYMBOL_GPL(tda18271c2dd_attach);

MODULE_DESCRIPTION("TDA18271C2 driver");
MODULE_AUTHOR("DD");
MODULE_LICENSE("GPL");
