<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drxd_hard.c: DVB-T Demodulator Micronas DRX3975D-A2,DRX397xD-B1
 *
 * Copyright (C) 2003-2007 Micronas
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/i2c.h>
#समावेश <यंत्र/भाग64.h>

#समावेश <media/dvb_frontend.h>
#समावेश "drxd.h"
#समावेश "drxd_firm.h"

#घोषणा DRX_FW_खाताNAME_A2 "drxd-a2-1.1.fw"
#घोषणा DRX_FW_खाताNAME_B1 "drxd-b1-1.1.fw"

#घोषणा CHUNK_SIZE 48

#घोषणा DRX_I2C_RMW           0x10
#घोषणा DRX_I2C_BROADCAST     0x20
#घोषणा DRX_I2C_CLEARCRC      0x80
#घोषणा DRX_I2C_SINGLE_MASTER 0xC0
#घोषणा DRX_I2C_MODEFLAGS     0xC0
#घोषणा DRX_I2C_FLAGS         0xF0

#घोषणा DEFAULT_LOCK_TIMEOUT    1100

#घोषणा DRX_CHANNEL_AUTO 0
#घोषणा DRX_CHANNEL_HIGH 1
#घोषणा DRX_CHANNEL_LOW  2

#घोषणा DRX_LOCK_MPEG  1
#घोषणा DRX_LOCK_FEC   2
#घोषणा DRX_LOCK_DEMOD 4

/****************************************************************************/

क्रमागत CSCDState अणु
	CSCD_INIT = 0,
	CSCD_SET,
	CSCD_SAVED
पूर्ण;

क्रमागत CDrxdState अणु
	DRXD_UNINITIALIZED = 0,
	DRXD_STOPPED,
	DRXD_STARTED
पूर्ण;

क्रमागत AGC_CTRL_MODE अणु
	AGC_CTRL_AUTO = 0,
	AGC_CTRL_USER,
	AGC_CTRL_OFF
पूर्ण;

क्रमागत OperationMode अणु
	OM_Default,
	OM_DVBT_Diversity_Front,
	OM_DVBT_Diversity_End
पूर्ण;

काष्ठा SCfgAgc अणु
	क्रमागत AGC_CTRL_MODE ctrlMode;
	u16 outputLevel;	/* range [0, ... , 1023], 1/n of fullscale range */
	u16 settleLevel;	/* range [0, ... , 1023], 1/n of fullscale range */
	u16 minOutputLevel;	/* range [0, ... , 1023], 1/n of fullscale range */
	u16 maxOutputLevel;	/* range [0, ... , 1023], 1/n of fullscale range */
	u16 speed;		/* range [0, ... , 1023], 1/n of fullscale range */

	u16 R1;
	u16 R2;
	u16 R3;
पूर्ण;

काष्ठा SNoiseCal अणु
	पूर्णांक cpOpt;
	लघु cpNexpOfs;
	लघु tdCal2k;
	लघु tdCal8k;
पूर्ण;

क्रमागत app_env अणु
	APPENV_STATIC = 0,
	APPENV_PORTABLE = 1,
	APPENV_MOBILE = 2
पूर्ण;

क्रमागत EIFFilter अणु
	IFFILTER_SAW = 0,
	IFFILTER_DISCRETE = 1
पूर्ण;

काष्ठा drxd_state अणु
	काष्ठा dvb_frontend frontend;
	काष्ठा dvb_frontend_ops ops;
	काष्ठा dtv_frontend_properties props;

	स्थिर काष्ठा firmware *fw;
	काष्ठा device *dev;

	काष्ठा i2c_adapter *i2c;
	व्योम *priv;
	काष्ठा drxd_config config;

	पूर्णांक i2c_access;
	पूर्णांक init_करोne;
	काष्ठा mutex mutex;

	u8 chip_adr;
	u16 hi_cfg_timing_भाग;
	u16 hi_cfg_bridge_delay;
	u16 hi_cfg_wakeup_key;
	u16 hi_cfg_ctrl;

	u16 पूर्णांकermediate_freq;
	u16 osc_घड़ी_freq;

	क्रमागत CSCDState cscd_state;
	क्रमागत CDrxdState drxd_state;

	u16 sys_घड़ी_freq;
	s16 osc_घड़ी_deviation;
	u16 expected_sys_घड़ी_freq;

	u16 insert_rs_byte;
	u16 enable_parallel;

	पूर्णांक operation_mode;

	काष्ठा SCfgAgc अगर_agc_cfg;
	काष्ठा SCfgAgc rf_agc_cfg;

	काष्ठा SNoiseCal noise_cal;

	u32 fe_fs_add_incr;
	u32 org_fe_fs_add_incr;
	u16 current_fe_अगर_incr;

	u16 m_FeAgRegAgPwd;
	u16 m_FeAgRegAgAgcSio;

	u16 m_EcOcRegOcModeLop;
	u16 m_EcOcRegSncSncLvl;
	u8 *m_InitAtomicRead;
	u8 *m_HiI2cPatch;

	u8 *m_ResetCEFR;
	u8 *m_InitFE_1;
	u8 *m_InitFE_2;
	u8 *m_InitCP;
	u8 *m_InitCE;
	u8 *m_InitEQ;
	u8 *m_InitSC;
	u8 *m_InitEC;
	u8 *m_ResetECRAM;
	u8 *m_InitDiversityFront;
	u8 *m_InitDiversityEnd;
	u8 *m_DisableDiversity;
	u8 *m_StartDiversityFront;
	u8 *m_StartDiversityEnd;

	u8 *m_DiversityDelay8MHZ;
	u8 *m_DiversityDelay6MHZ;

	u8 *microcode;
	u32 microcode_length;

	पूर्णांक type_A;
	पूर्णांक PGA;
	पूर्णांक भागersity;
	पूर्णांक tuner_mirrors;

	क्रमागत app_env app_env_शेष;
	क्रमागत app_env app_env_भागersity;

पूर्ण;

/****************************************************************************/
/* I2C **********************************************************************/
/****************************************************************************/

अटल पूर्णांक i2c_ग_लिखो(काष्ठा i2c_adapter *adap, u8 adr, u8 * data, पूर्णांक len)
अणु
	काष्ठा i2c_msg msg = अणु.addr = adr, .flags = 0, .buf = data, .len = len पूर्ण;

	अगर (i2c_transfer(adap, &msg, 1) != 1)
		वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक i2c_पढ़ो(काष्ठा i2c_adapter *adap,
		    u8 adr, u8 *msg, पूर्णांक len, u8 *answ, पूर्णांक alen)
अणु
	काष्ठा i2c_msg msgs[2] = अणु
		अणु
			.addr = adr, .flags = 0,
			.buf = msg, .len = len
		पूर्ण, अणु
			.addr = adr, .flags = I2C_M_RD,
			.buf = answ, .len = alen
		पूर्ण
	पूर्ण;
	अगर (i2c_transfer(adap, msgs, 2) != 2)
		वापस -1;
	वापस 0;
पूर्ण

अटल अंतरभूत u32 MulDiv32(u32 a, u32 b, u32 c)
अणु
	u64 पंचांगp64;

	पंचांगp64 = (u64)a * (u64)b;
	करो_भाग(पंचांगp64, c);

	वापस (u32) पंचांगp64;
पूर्ण

अटल पूर्णांक Read16(काष्ठा drxd_state *state, u32 reg, u16 *data, u8 flags)
अणु
	u8 adr = state->config.demod_address;
	u8 mm1[4] = अणु reg & 0xff, (reg >> 16) & 0xff,
		flags | ((reg >> 24) & 0xff), (reg >> 8) & 0xff
	पूर्ण;
	u8 mm2[2];
	अगर (i2c_पढ़ो(state->i2c, adr, mm1, 4, mm2, 2) < 0)
		वापस -1;
	अगर (data)
		*data = mm2[0] | (mm2[1] << 8);
	वापस mm2[0] | (mm2[1] << 8);
पूर्ण

अटल पूर्णांक Read32(काष्ठा drxd_state *state, u32 reg, u32 *data, u8 flags)
अणु
	u8 adr = state->config.demod_address;
	u8 mm1[4] = अणु reg & 0xff, (reg >> 16) & 0xff,
		flags | ((reg >> 24) & 0xff), (reg >> 8) & 0xff
	पूर्ण;
	u8 mm2[4];

	अगर (i2c_पढ़ो(state->i2c, adr, mm1, 4, mm2, 4) < 0)
		वापस -1;
	अगर (data)
		*data =
		    mm2[0] | (mm2[1] << 8) | (mm2[2] << 16) | (mm2[3] << 24);
	वापस 0;
पूर्ण

अटल पूर्णांक Write16(काष्ठा drxd_state *state, u32 reg, u16 data, u8 flags)
अणु
	u8 adr = state->config.demod_address;
	u8 mm[6] = अणु reg & 0xff, (reg >> 16) & 0xff,
		flags | ((reg >> 24) & 0xff), (reg >> 8) & 0xff,
		data & 0xff, (data >> 8) & 0xff
	पूर्ण;

	अगर (i2c_ग_लिखो(state->i2c, adr, mm, 6) < 0)
		वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक Write32(काष्ठा drxd_state *state, u32 reg, u32 data, u8 flags)
अणु
	u8 adr = state->config.demod_address;
	u8 mm[8] = अणु reg & 0xff, (reg >> 16) & 0xff,
		flags | ((reg >> 24) & 0xff), (reg >> 8) & 0xff,
		data & 0xff, (data >> 8) & 0xff,
		(data >> 16) & 0xff, (data >> 24) & 0xff
	पूर्ण;

	अगर (i2c_ग_लिखो(state->i2c, adr, mm, 8) < 0)
		वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_chunk(काष्ठा drxd_state *state,
		       u32 reg, u8 *data, u32 len, u8 flags)
अणु
	u8 adr = state->config.demod_address;
	u8 mm[CHUNK_SIZE + 4] = अणु reg & 0xff, (reg >> 16) & 0xff,
		flags | ((reg >> 24) & 0xff), (reg >> 8) & 0xff
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		mm[4 + i] = data[i];
	अगर (i2c_ग_लिखो(state->i2c, adr, mm, 4 + len) < 0) अणु
		prपूर्णांकk(KERN_ERR "error in write_chunk\n");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक WriteBlock(काष्ठा drxd_state *state,
		      u32 Address, u16 BlockSize, u8 *pBlock, u8 Flags)
अणु
	जबतक (BlockSize > 0) अणु
		u16 Chunk = BlockSize > CHUNK_SIZE ? CHUNK_SIZE : BlockSize;

		अगर (ग_लिखो_chunk(state, Address, pBlock, Chunk, Flags) < 0)
			वापस -1;
		pBlock += Chunk;
		Address += (Chunk >> 1);
		BlockSize -= Chunk;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक WriteTable(काष्ठा drxd_state *state, u8 * pTable)
अणु
	पूर्णांक status = 0;

	अगर (!pTable)
		वापस 0;

	जबतक (!status) अणु
		u16 Length;
		u32 Address = pTable[0] | (pTable[1] << 8) |
		    (pTable[2] << 16) | (pTable[3] << 24);

		अगर (Address == 0xFFFFFFFF)
			अवरोध;
		pTable += माप(u32);

		Length = pTable[0] | (pTable[1] << 8);
		pTable += माप(u16);
		अगर (!Length)
			अवरोध;
		status = WriteBlock(state, Address, Length * 2, pTable, 0);
		pTable += (Length * 2);
	पूर्ण
	वापस status;
पूर्ण

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

अटल पूर्णांक ResetCEFR(काष्ठा drxd_state *state)
अणु
	वापस WriteTable(state, state->m_ResetCEFR);
पूर्ण

अटल पूर्णांक InitCP(काष्ठा drxd_state *state)
अणु
	वापस WriteTable(state, state->m_InitCP);
पूर्ण

अटल पूर्णांक InitCE(काष्ठा drxd_state *state)
अणु
	पूर्णांक status;
	क्रमागत app_env AppEnv = state->app_env_शेष;

	करो अणु
		status = WriteTable(state, state->m_InitCE);
		अगर (status < 0)
			अवरोध;

		अगर (state->operation_mode == OM_DVBT_Diversity_Front ||
		    state->operation_mode == OM_DVBT_Diversity_End) अणु
			AppEnv = state->app_env_भागersity;
		पूर्ण
		अगर (AppEnv == APPENV_STATIC) अणु
			status = Write16(state, CE_REG_TAPSET__A, 0x0000, 0);
			अगर (status < 0)
				अवरोध;
		पूर्ण अन्यथा अगर (AppEnv == APPENV_PORTABLE) अणु
			status = Write16(state, CE_REG_TAPSET__A, 0x0001, 0);
			अगर (status < 0)
				अवरोध;
		पूर्ण अन्यथा अगर (AppEnv == APPENV_MOBILE && state->type_A) अणु
			status = Write16(state, CE_REG_TAPSET__A, 0x0002, 0);
			अगर (status < 0)
				अवरोध;
		पूर्ण अन्यथा अगर (AppEnv == APPENV_MOBILE && !state->type_A) अणु
			status = Write16(state, CE_REG_TAPSET__A, 0x0006, 0);
			अगर (status < 0)
				अवरोध;
		पूर्ण

		/* start ce */
		status = Write16(state, B_CE_REG_COMM_EXEC__A, 0x0001, 0);
		अगर (status < 0)
			अवरोध;
	पूर्ण जबतक (0);
	वापस status;
पूर्ण

अटल पूर्णांक StopOC(काष्ठा drxd_state *state)
अणु
	पूर्णांक status = 0;
	u16 ocSyncLvl = 0;
	u16 ocModeLop = state->m_EcOcRegOcModeLop;
	u16 dtoIncLop = 0;
	u16 dtoIncHip = 0;

	करो अणु
		/* Store output configuration */
		status = Read16(state, EC_OC_REG_SNC_ISC_LVL__A, &ocSyncLvl, 0);
		अगर (status < 0)
			अवरोध;
		/* CHK_ERROR(Read16(EC_OC_REG_OC_MODE_LOP__A, &ocModeLop)); */
		state->m_EcOcRegSncSncLvl = ocSyncLvl;
		/* m_EcOcRegOcModeLop = ocModeLop; */

		/* Flush FIFO (byte-boundary) at fixed rate */
		status = Read16(state, EC_OC_REG_RCN_MAP_LOP__A, &dtoIncLop, 0);
		अगर (status < 0)
			अवरोध;
		status = Read16(state, EC_OC_REG_RCN_MAP_HIP__A, &dtoIncHip, 0);
		अगर (status < 0)
			अवरोध;
		status = Write16(state, EC_OC_REG_DTO_INC_LOP__A, dtoIncLop, 0);
		अगर (status < 0)
			अवरोध;
		status = Write16(state, EC_OC_REG_DTO_INC_HIP__A, dtoIncHip, 0);
		अगर (status < 0)
			अवरोध;
		ocModeLop &= ~(EC_OC_REG_OC_MODE_LOP_DTO_CTR_SRC__M);
		ocModeLop |= EC_OC_REG_OC_MODE_LOP_DTO_CTR_SRC_STATIC;
		status = Write16(state, EC_OC_REG_OC_MODE_LOP__A, ocModeLop, 0);
		अगर (status < 0)
			अवरोध;
		status = Write16(state, EC_OC_REG_COMM_EXEC__A, EC_OC_REG_COMM_EXEC_CTL_HOLD, 0);
		अगर (status < 0)
			अवरोध;

		msleep(1);
		/* Output pins to '0' */
		status = Write16(state, EC_OC_REG_OCR_MPG_UOS__A, EC_OC_REG_OCR_MPG_UOS__M, 0);
		अगर (status < 0)
			अवरोध;

		/* Force the OC out of sync */
		ocSyncLvl &= ~(EC_OC_REG_SNC_ISC_LVL_OSC__M);
		status = Write16(state, EC_OC_REG_SNC_ISC_LVL__A, ocSyncLvl, 0);
		अगर (status < 0)
			अवरोध;
		ocModeLop &= ~(EC_OC_REG_OC_MODE_LOP_PAR_ENA__M);
		ocModeLop |= EC_OC_REG_OC_MODE_LOP_PAR_ENA_ENABLE;
		ocModeLop |= 0x2;	/* Magically-out-of-sync */
		status = Write16(state, EC_OC_REG_OC_MODE_LOP__A, ocModeLop, 0);
		अगर (status < 0)
			अवरोध;
		status = Write16(state, EC_OC_REG_COMM_INT_STA__A, 0x0, 0);
		अगर (status < 0)
			अवरोध;
		status = Write16(state, EC_OC_REG_COMM_EXEC__A, EC_OC_REG_COMM_EXEC_CTL_ACTIVE, 0);
		अगर (status < 0)
			अवरोध;
	पूर्ण जबतक (0);

	वापस status;
पूर्ण

अटल पूर्णांक StartOC(काष्ठा drxd_state *state)
अणु
	पूर्णांक status = 0;

	करो अणु
		/* Stop OC */
		status = Write16(state, EC_OC_REG_COMM_EXEC__A, EC_OC_REG_COMM_EXEC_CTL_HOLD, 0);
		अगर (status < 0)
			अवरोध;

		/* Restore output configuration */
		status = Write16(state, EC_OC_REG_SNC_ISC_LVL__A, state->m_EcOcRegSncSncLvl, 0);
		अगर (status < 0)
			अवरोध;
		status = Write16(state, EC_OC_REG_OC_MODE_LOP__A, state->m_EcOcRegOcModeLop, 0);
		अगर (status < 0)
			अवरोध;

		/* Output pins active again */
		status = Write16(state, EC_OC_REG_OCR_MPG_UOS__A, EC_OC_REG_OCR_MPG_UOS_INIT, 0);
		अगर (status < 0)
			अवरोध;

		/* Start OC */
		status = Write16(state, EC_OC_REG_COMM_EXEC__A, EC_OC_REG_COMM_EXEC_CTL_ACTIVE, 0);
		अगर (status < 0)
			अवरोध;
	पूर्ण जबतक (0);
	वापस status;
पूर्ण

अटल पूर्णांक InitEQ(काष्ठा drxd_state *state)
अणु
	वापस WriteTable(state, state->m_InitEQ);
पूर्ण

अटल पूर्णांक InitEC(काष्ठा drxd_state *state)
अणु
	वापस WriteTable(state, state->m_InitEC);
पूर्ण

अटल पूर्णांक InitSC(काष्ठा drxd_state *state)
अणु
	वापस WriteTable(state, state->m_InitSC);
पूर्ण

अटल पूर्णांक InitAtomicRead(काष्ठा drxd_state *state)
अणु
	वापस WriteTable(state, state->m_InitAtomicRead);
पूर्ण

अटल पूर्णांक CorrectSysClockDeviation(काष्ठा drxd_state *state);

अटल पूर्णांक DRX_GetLockStatus(काष्ठा drxd_state *state, u32 * pLockStatus)
अणु
	u16 ScRaRamLock = 0;
	स्थिर u16 mpeg_lock_mask = (SC_RA_RAM_LOCK_MPEG__M |
				    SC_RA_RAM_LOCK_FEC__M |
				    SC_RA_RAM_LOCK_DEMOD__M);
	स्थिर u16 fec_lock_mask = (SC_RA_RAM_LOCK_FEC__M |
				   SC_RA_RAM_LOCK_DEMOD__M);
	स्थिर u16 demod_lock_mask = SC_RA_RAM_LOCK_DEMOD__M;

	पूर्णांक status;

	*pLockStatus = 0;

	status = Read16(state, SC_RA_RAM_LOCK__A, &ScRaRamLock, 0x0000);
	अगर (status < 0) अणु
		prपूर्णांकk(KERN_ERR "Can't read SC_RA_RAM_LOCK__A status = %08x\n", status);
		वापस status;
	पूर्ण

	अगर (state->drxd_state != DRXD_STARTED)
		वापस 0;

	अगर ((ScRaRamLock & mpeg_lock_mask) == mpeg_lock_mask) अणु
		*pLockStatus |= DRX_LOCK_MPEG;
		CorrectSysClockDeviation(state);
	पूर्ण

	अगर ((ScRaRamLock & fec_lock_mask) == fec_lock_mask)
		*pLockStatus |= DRX_LOCK_FEC;

	अगर ((ScRaRamLock & demod_lock_mask) == demod_lock_mask)
		*pLockStatus |= DRX_LOCK_DEMOD;
	वापस 0;
पूर्ण

/****************************************************************************/

अटल पूर्णांक SetCfgIfAgc(काष्ठा drxd_state *state, काष्ठा SCfgAgc *cfg)
अणु
	पूर्णांक status;

	अगर (cfg->outputLevel > DRXD_FE_CTRL_MAX)
		वापस -1;

	अगर (cfg->ctrlMode == AGC_CTRL_USER) अणु
		करो अणु
			u16 FeAgRegPm1AgcWri;
			u16 FeAgRegAgModeLop;

			status = Read16(state, FE_AG_REG_AG_MODE_LOP__A, &FeAgRegAgModeLop, 0);
			अगर (status < 0)
				अवरोध;
			FeAgRegAgModeLop &= (~FE_AG_REG_AG_MODE_LOP_MODE_4__M);
			FeAgRegAgModeLop |= FE_AG_REG_AG_MODE_LOP_MODE_4_STATIC;
			status = Write16(state, FE_AG_REG_AG_MODE_LOP__A, FeAgRegAgModeLop, 0);
			अगर (status < 0)
				अवरोध;

			FeAgRegPm1AgcWri = (u16) (cfg->outputLevel &
						  FE_AG_REG_PM1_AGC_WRI__M);
			status = Write16(state, FE_AG_REG_PM1_AGC_WRI__A, FeAgRegPm1AgcWri, 0);
			अगर (status < 0)
				अवरोध;
		पूर्ण जबतक (0);
	पूर्ण अन्यथा अगर (cfg->ctrlMode == AGC_CTRL_AUTO) अणु
		अगर (((cfg->maxOutputLevel) < (cfg->minOutputLevel)) ||
		    ((cfg->maxOutputLevel) > DRXD_FE_CTRL_MAX) ||
		    ((cfg->speed) > DRXD_FE_CTRL_MAX) ||
		    ((cfg->settleLevel) > DRXD_FE_CTRL_MAX)
		    )
			वापस -1;
		करो अणु
			u16 FeAgRegAgModeLop;
			u16 FeAgRegEgcSetLvl;
			u16 slope, offset;

			/* == Mode == */

			status = Read16(state, FE_AG_REG_AG_MODE_LOP__A, &FeAgRegAgModeLop, 0);
			अगर (status < 0)
				अवरोध;
			FeAgRegAgModeLop &= (~FE_AG_REG_AG_MODE_LOP_MODE_4__M);
			FeAgRegAgModeLop |=
			    FE_AG_REG_AG_MODE_LOP_MODE_4_DYNAMIC;
			status = Write16(state, FE_AG_REG_AG_MODE_LOP__A, FeAgRegAgModeLop, 0);
			अगर (status < 0)
				अवरोध;

			/* == Settle level == */

			FeAgRegEgcSetLvl = (u16) ((cfg->settleLevel >> 1) &
						  FE_AG_REG_EGC_SET_LVL__M);
			status = Write16(state, FE_AG_REG_EGC_SET_LVL__A, FeAgRegEgcSetLvl, 0);
			अगर (status < 0)
				अवरोध;

			/* == Min/Max == */

			slope = (u16) ((cfg->maxOutputLevel -
					cfg->minOutputLevel) / 2);
			offset = (u16) ((cfg->maxOutputLevel +
					 cfg->minOutputLevel) / 2 - 511);

			status = Write16(state, FE_AG_REG_GC1_AGC_RIC__A, slope, 0);
			अगर (status < 0)
				अवरोध;
			status = Write16(state, FE_AG_REG_GC1_AGC_OFF__A, offset, 0);
			अगर (status < 0)
				अवरोध;

			/* == Speed == */
			अणु
				स्थिर u16 maxRur = 8;
				अटल स्थिर u16 slowIncrDecLUT[] = अणु
					3, 4, 4, 5, 6 पूर्ण;
				अटल स्थिर u16 fastIncrDecLUT[] = अणु
					14, 15, 15, 16,
					17, 18, 18, 19,
					20, 21, 22, 23,
					24, 26, 27, 28,
					29, 31
				पूर्ण;

				u16 fineSteps = (DRXD_FE_CTRL_MAX + 1) /
				    (maxRur + 1);
				u16 fineSpeed = (u16) (cfg->speed -
						       ((cfg->speed /
							 fineSteps) *
							fineSteps));
				u16 invRurCount = (u16) (cfg->speed /
							 fineSteps);
				u16 rurCount;
				अगर (invRurCount > maxRur) अणु
					rurCount = 0;
					fineSpeed += fineSteps;
				पूर्ण अन्यथा अणु
					rurCount = maxRur - invRurCount;
				पूर्ण

				/*
				   fastInc = शेष *
				   (2^(fineSpeed/fineSteps))
				   => range[शेष...2*शेष>
				   slowInc = शेष *
				   (2^(fineSpeed/fineSteps))
				 */
				अणु
					u16 fastIncrDec =
					    fastIncrDecLUT[fineSpeed /
							   ((fineSteps /
							     (14 + 1)) + 1)];
					u16 slowIncrDec =
					    slowIncrDecLUT[fineSpeed /
							   (fineSteps /
							    (3 + 1))];

					status = Write16(state, FE_AG_REG_EGC_RUR_CNT__A, rurCount, 0);
					अगर (status < 0)
						अवरोध;
					status = Write16(state, FE_AG_REG_EGC_FAS_INC__A, fastIncrDec, 0);
					अगर (status < 0)
						अवरोध;
					status = Write16(state, FE_AG_REG_EGC_FAS_DEC__A, fastIncrDec, 0);
					अगर (status < 0)
						अवरोध;
					status = Write16(state, FE_AG_REG_EGC_SLO_INC__A, slowIncrDec, 0);
					अगर (status < 0)
						अवरोध;
					status = Write16(state, FE_AG_REG_EGC_SLO_DEC__A, slowIncrDec, 0);
					अगर (status < 0)
						अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण जबतक (0);

	पूर्ण अन्यथा अणु
		/* No OFF mode क्रम IF control */
		वापस -1;
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक SetCfgRfAgc(काष्ठा drxd_state *state, काष्ठा SCfgAgc *cfg)
अणु
	पूर्णांक status = 0;

	अगर (cfg->outputLevel > DRXD_FE_CTRL_MAX)
		वापस -1;

	अगर (cfg->ctrlMode == AGC_CTRL_USER) अणु
		करो अणु
			u16 AgModeLop = 0;
			u16 level = (cfg->outputLevel);

			अगर (level == DRXD_FE_CTRL_MAX)
				level++;

			status = Write16(state, FE_AG_REG_PM2_AGC_WRI__A, level, 0x0000);
			अगर (status < 0)
				अवरोध;

			/*==== Mode ====*/

			/* Powerकरोwn PD2, WRI source */
			state->m_FeAgRegAgPwd &= ~(FE_AG_REG_AG_PWD_PWD_PD2__M);
			state->m_FeAgRegAgPwd |=
			    FE_AG_REG_AG_PWD_PWD_PD2_DISABLE;
			status = Write16(state, FE_AG_REG_AG_PWD__A, state->m_FeAgRegAgPwd, 0x0000);
			अगर (status < 0)
				अवरोध;

			status = Read16(state, FE_AG_REG_AG_MODE_LOP__A, &AgModeLop, 0x0000);
			अगर (status < 0)
				अवरोध;
			AgModeLop &= (~(FE_AG_REG_AG_MODE_LOP_MODE_5__M |
					FE_AG_REG_AG_MODE_LOP_MODE_E__M));
			AgModeLop |= (FE_AG_REG_AG_MODE_LOP_MODE_5_STATIC |
				      FE_AG_REG_AG_MODE_LOP_MODE_E_STATIC);
			status = Write16(state, FE_AG_REG_AG_MODE_LOP__A, AgModeLop, 0x0000);
			अगर (status < 0)
				अवरोध;

			/* enable AGC2 pin */
			अणु
				u16 FeAgRegAgAgcSio = 0;
				status = Read16(state, FE_AG_REG_AG_AGC_SIO__A, &FeAgRegAgAgcSio, 0x0000);
				अगर (status < 0)
					अवरोध;
				FeAgRegAgAgcSio &=
				    ~(FE_AG_REG_AG_AGC_SIO_AGC_SIO_2__M);
				FeAgRegAgAgcSio |=
				    FE_AG_REG_AG_AGC_SIO_AGC_SIO_2_OUTPUT;
				status = Write16(state, FE_AG_REG_AG_AGC_SIO__A, FeAgRegAgAgcSio, 0x0000);
				अगर (status < 0)
					अवरोध;
			पूर्ण

		पूर्ण जबतक (0);
	पूर्ण अन्यथा अगर (cfg->ctrlMode == AGC_CTRL_AUTO) अणु
		u16 AgModeLop = 0;

		करो अणु
			u16 level;
			/* Automatic control */
			/* Powerup PD2, AGC2 as output, TGC source */
			(state->m_FeAgRegAgPwd) &=
			    ~(FE_AG_REG_AG_PWD_PWD_PD2__M);
			(state->m_FeAgRegAgPwd) |=
			    FE_AG_REG_AG_PWD_PWD_PD2_DISABLE;
			status = Write16(state, FE_AG_REG_AG_PWD__A, (state->m_FeAgRegAgPwd), 0x0000);
			अगर (status < 0)
				अवरोध;

			status = Read16(state, FE_AG_REG_AG_MODE_LOP__A, &AgModeLop, 0x0000);
			अगर (status < 0)
				अवरोध;
			AgModeLop &= (~(FE_AG_REG_AG_MODE_LOP_MODE_5__M |
					FE_AG_REG_AG_MODE_LOP_MODE_E__M));
			AgModeLop |= (FE_AG_REG_AG_MODE_LOP_MODE_5_STATIC |
				      FE_AG_REG_AG_MODE_LOP_MODE_E_DYNAMIC);
			status = Write16(state, FE_AG_REG_AG_MODE_LOP__A, AgModeLop, 0x0000);
			अगर (status < 0)
				अवरोध;
			/* Settle level */
			level = (((cfg->settleLevel) >> 4) &
				 FE_AG_REG_TGC_SET_LVL__M);
			status = Write16(state, FE_AG_REG_TGC_SET_LVL__A, level, 0x0000);
			अगर (status < 0)
				अवरोध;

			/* Min/max: करोn't care */

			/* Speed: TODO */

			/* enable AGC2 pin */
			अणु
				u16 FeAgRegAgAgcSio = 0;
				status = Read16(state, FE_AG_REG_AG_AGC_SIO__A, &FeAgRegAgAgcSio, 0x0000);
				अगर (status < 0)
					अवरोध;
				FeAgRegAgAgcSio &=
				    ~(FE_AG_REG_AG_AGC_SIO_AGC_SIO_2__M);
				FeAgRegAgAgcSio |=
				    FE_AG_REG_AG_AGC_SIO_AGC_SIO_2_OUTPUT;
				status = Write16(state, FE_AG_REG_AG_AGC_SIO__A, FeAgRegAgAgcSio, 0x0000);
				अगर (status < 0)
					अवरोध;
			पूर्ण

		पूर्ण जबतक (0);
	पूर्ण अन्यथा अणु
		u16 AgModeLop = 0;

		करो अणु
			/* No RF AGC control */
			/* Powerकरोwn PD2, AGC2 as output, WRI source */
			(state->m_FeAgRegAgPwd) &=
			    ~(FE_AG_REG_AG_PWD_PWD_PD2__M);
			(state->m_FeAgRegAgPwd) |=
			    FE_AG_REG_AG_PWD_PWD_PD2_ENABLE;
			status = Write16(state, FE_AG_REG_AG_PWD__A, (state->m_FeAgRegAgPwd), 0x0000);
			अगर (status < 0)
				अवरोध;

			status = Read16(state, FE_AG_REG_AG_MODE_LOP__A, &AgModeLop, 0x0000);
			अगर (status < 0)
				अवरोध;
			AgModeLop &= (~(FE_AG_REG_AG_MODE_LOP_MODE_5__M |
					FE_AG_REG_AG_MODE_LOP_MODE_E__M));
			AgModeLop |= (FE_AG_REG_AG_MODE_LOP_MODE_5_STATIC |
				      FE_AG_REG_AG_MODE_LOP_MODE_E_STATIC);
			status = Write16(state, FE_AG_REG_AG_MODE_LOP__A, AgModeLop, 0x0000);
			अगर (status < 0)
				अवरोध;

			/* set FeAgRegAgAgcSio AGC2 (RF) as input */
			अणु
				u16 FeAgRegAgAgcSio = 0;
				status = Read16(state, FE_AG_REG_AG_AGC_SIO__A, &FeAgRegAgAgcSio, 0x0000);
				अगर (status < 0)
					अवरोध;
				FeAgRegAgAgcSio &=
				    ~(FE_AG_REG_AG_AGC_SIO_AGC_SIO_2__M);
				FeAgRegAgAgcSio |=
				    FE_AG_REG_AG_AGC_SIO_AGC_SIO_2_INPUT;
				status = Write16(state, FE_AG_REG_AG_AGC_SIO__A, FeAgRegAgAgcSio, 0x0000);
				अगर (status < 0)
					अवरोध;
			पूर्ण
		पूर्ण जबतक (0);
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक ReadIFAgc(काष्ठा drxd_state *state, u32 * pValue)
अणु
	पूर्णांक status = 0;

	*pValue = 0;
	अगर (state->अगर_agc_cfg.ctrlMode != AGC_CTRL_OFF) अणु
		u16 Value;
		status = Read16(state, FE_AG_REG_GC1_AGC_DAT__A, &Value, 0);
		Value &= FE_AG_REG_GC1_AGC_DAT__M;
		अगर (status >= 0) अणु
			/*           3.3V
			   |
			   R1
			   |
			   Vin - R3 - * -- Vout
			   |
			   R2
			   |
			   GND
			 */
			u32 R1 = state->अगर_agc_cfg.R1;
			u32 R2 = state->अगर_agc_cfg.R2;
			u32 R3 = state->अगर_agc_cfg.R3;

			u32 Vmax, Rpar, Vmin, Vout;

			अगर (R2 == 0 && (R1 == 0 || R3 == 0))
				वापस 0;

			Vmax = (3300 * R2) / (R1 + R2);
			Rpar = (R2 * R3) / (R3 + R2);
			Vmin = (3300 * Rpar) / (R1 + Rpar);
			Vout = Vmin + ((Vmax - Vmin) * Value) / 1024;

			*pValue = Vout;
		पूर्ण
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक load_firmware(काष्ठा drxd_state *state, स्थिर अक्षर *fw_name)
अणु
	स्थिर काष्ठा firmware *fw;

	अगर (request_firmware(&fw, fw_name, state->dev) < 0) अणु
		prपूर्णांकk(KERN_ERR "drxd: firmware load failure [%s]\n", fw_name);
		वापस -EIO;
	पूर्ण

	state->microcode = kmemdup(fw->data, fw->size, GFP_KERNEL);
	अगर (!state->microcode) अणु
		release_firmware(fw);
		वापस -ENOMEM;
	पूर्ण

	state->microcode_length = fw->size;
	release_firmware(fw);
	वापस 0;
पूर्ण

अटल पूर्णांक DownloadMicrocode(काष्ठा drxd_state *state,
			     स्थिर u8 *pMCImage, u32 Length)
अणु
	u8 *pSrc;
	u32 Address;
	u16 nBlocks;
	u16 BlockSize;
	u32 offset = 0;
	पूर्णांक i, status = 0;

	pSrc = (u8 *) pMCImage;
	/* We're not using Flags */
	/* Flags = (pSrc[0] << 8) | pSrc[1]; */
	pSrc += माप(u16);
	offset += माप(u16);
	nBlocks = (pSrc[0] << 8) | pSrc[1];
	pSrc += माप(u16);
	offset += माप(u16);

	क्रम (i = 0; i < nBlocks; i++) अणु
		Address = (pSrc[0] << 24) | (pSrc[1] << 16) |
		    (pSrc[2] << 8) | pSrc[3];
		pSrc += माप(u32);
		offset += माप(u32);

		BlockSize = ((pSrc[0] << 8) | pSrc[1]) * माप(u16);
		pSrc += माप(u16);
		offset += माप(u16);

		/* We're not using Flags */
		/* u16 Flags = (pSrc[0] << 8) | pSrc[1]; */
		pSrc += माप(u16);
		offset += माप(u16);

		/* We're not using BlockCRC */
		/* u16 BlockCRC = (pSrc[0] << 8) | pSrc[1]; */
		pSrc += माप(u16);
		offset += माप(u16);

		status = WriteBlock(state, Address, BlockSize,
				    pSrc, DRX_I2C_CLEARCRC);
		अगर (status < 0)
			अवरोध;
		pSrc += BlockSize;
		offset += BlockSize;
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक HI_Command(काष्ठा drxd_state *state, u16 cmd, u16 * pResult)
अणु
	u32 nrRetries = 0;
	पूर्णांक status;

	status = Write16(state, HI_RA_RAM_SRV_CMD__A, cmd, 0);
	अगर (status < 0)
		वापस status;

	करो अणु
		nrRetries += 1;
		अगर (nrRetries > DRXD_MAX_RETRIES) अणु
			status = -1;
			अवरोध;
		पूर्ण
		status = Read16(state, HI_RA_RAM_SRV_CMD__A, शून्य, 0);
	पूर्ण जबतक (status != 0);

	अगर (status >= 0)
		status = Read16(state, HI_RA_RAM_SRV_RES__A, pResult, 0);
	वापस status;
पूर्ण

अटल पूर्णांक HI_CfgCommand(काष्ठा drxd_state *state)
अणु
	पूर्णांक status = 0;

	mutex_lock(&state->mutex);
	Write16(state, HI_RA_RAM_SRV_CFG_KEY__A, HI_RA_RAM_SRV_RST_KEY_ACT, 0);
	Write16(state, HI_RA_RAM_SRV_CFG_DIV__A, state->hi_cfg_timing_भाग, 0);
	Write16(state, HI_RA_RAM_SRV_CFG_BDL__A, state->hi_cfg_bridge_delay, 0);
	Write16(state, HI_RA_RAM_SRV_CFG_WUP__A, state->hi_cfg_wakeup_key, 0);
	Write16(state, HI_RA_RAM_SRV_CFG_ACT__A, state->hi_cfg_ctrl, 0);

	Write16(state, HI_RA_RAM_SRV_CFG_KEY__A, HI_RA_RAM_SRV_RST_KEY_ACT, 0);

	अगर ((state->hi_cfg_ctrl & HI_RA_RAM_SRV_CFG_ACT_PWD_EXE) ==
	    HI_RA_RAM_SRV_CFG_ACT_PWD_EXE)
		status = Write16(state, HI_RA_RAM_SRV_CMD__A,
				 HI_RA_RAM_SRV_CMD_CONFIG, 0);
	अन्यथा
		status = HI_Command(state, HI_RA_RAM_SRV_CMD_CONFIG, शून्य);
	mutex_unlock(&state->mutex);
	वापस status;
पूर्ण

अटल पूर्णांक InitHI(काष्ठा drxd_state *state)
अणु
	state->hi_cfg_wakeup_key = (state->chip_adr);
	/* port/bridge/घातer करोwn ctrl */
	state->hi_cfg_ctrl = HI_RA_RAM_SRV_CFG_ACT_SLV0_ON;
	वापस HI_CfgCommand(state);
पूर्ण

अटल पूर्णांक HI_ResetCommand(काष्ठा drxd_state *state)
अणु
	पूर्णांक status;

	mutex_lock(&state->mutex);
	status = Write16(state, HI_RA_RAM_SRV_RST_KEY__A,
			 HI_RA_RAM_SRV_RST_KEY_ACT, 0);
	अगर (status == 0)
		status = HI_Command(state, HI_RA_RAM_SRV_CMD_RESET, शून्य);
	mutex_unlock(&state->mutex);
	msleep(1);
	वापस status;
पूर्ण

अटल पूर्णांक DRX_ConfigureI2CBridge(काष्ठा drxd_state *state, पूर्णांक bEnableBridge)
अणु
	state->hi_cfg_ctrl &= (~HI_RA_RAM_SRV_CFG_ACT_BRD__M);
	अगर (bEnableBridge)
		state->hi_cfg_ctrl |= HI_RA_RAM_SRV_CFG_ACT_BRD_ON;
	अन्यथा
		state->hi_cfg_ctrl |= HI_RA_RAM_SRV_CFG_ACT_BRD_OFF;

	वापस HI_CfgCommand(state);
पूर्ण

#घोषणा HI_TR_WRITE      0x9
#घोषणा HI_TR_READ       0xA
#घोषणा HI_TR_READ_WRITE 0xB
#घोषणा HI_TR_BROADCAST  0x4

#अगर 0
अटल पूर्णांक AtomicReadBlock(काष्ठा drxd_state *state,
			   u32 Addr, u16 DataSize, u8 *pData, u8 Flags)
अणु
	पूर्णांक status;
	पूर्णांक i = 0;

	/* Parameter check */
	अगर ((!pData) || ((DataSize & 1) != 0))
		वापस -1;

	mutex_lock(&state->mutex);

	करो अणु
		/* Inकाष्ठा HI to पढ़ो n bytes */
		/* TODO use proper names क्रमthese egisters */
		status = Write16(state, HI_RA_RAM_SRV_CFG_KEY__A, (HI_TR_FUNC_ADDR & 0xFFFF), 0);
		अगर (status < 0)
			अवरोध;
		status = Write16(state, HI_RA_RAM_SRV_CFG_DIV__A, (u16) (Addr >> 16), 0);
		अगर (status < 0)
			अवरोध;
		status = Write16(state, HI_RA_RAM_SRV_CFG_BDL__A, (u16) (Addr & 0xFFFF), 0);
		अगर (status < 0)
			अवरोध;
		status = Write16(state, HI_RA_RAM_SRV_CFG_WUP__A, (u16) ((DataSize / 2) - 1), 0);
		अगर (status < 0)
			अवरोध;
		status = Write16(state, HI_RA_RAM_SRV_CFG_ACT__A, HI_TR_READ, 0);
		अगर (status < 0)
			अवरोध;

		status = HI_Command(state, HI_RA_RAM_SRV_CMD_EXECUTE, 0);
		अगर (status < 0)
			अवरोध;

	पूर्ण जबतक (0);

	अगर (status >= 0) अणु
		क्रम (i = 0; i < (DataSize / 2); i += 1) अणु
			u16 word;

			status = Read16(state, (HI_RA_RAM_USR_BEGIN__A + i),
					&word, 0);
			अगर (status < 0)
				अवरोध;
			pData[2 * i] = (u8) (word & 0xFF);
			pData[(2 * i) + 1] = (u8) (word >> 8);
		पूर्ण
	पूर्ण
	mutex_unlock(&state->mutex);
	वापस status;
पूर्ण

अटल पूर्णांक AtomicReadReg32(काष्ठा drxd_state *state,
			   u32 Addr, u32 *pData, u8 Flags)
अणु
	u8 buf[माप(u32)];
	पूर्णांक status;

	अगर (!pData)
		वापस -1;
	status = AtomicReadBlock(state, Addr, माप(u32), buf, Flags);
	*pData = (((u32) buf[0]) << 0) +
	    (((u32) buf[1]) << 8) +
	    (((u32) buf[2]) << 16) + (((u32) buf[3]) << 24);
	वापस status;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक StopAllProcessors(काष्ठा drxd_state *state)
अणु
	वापस Write16(state, HI_COMM_EXEC__A,
		       SC_COMM_EXEC_CTL_STOP, DRX_I2C_BROADCAST);
पूर्ण

अटल पूर्णांक EnableAndResetMB(काष्ठा drxd_state *state)
अणु
	अगर (state->type_A) अणु
		/* disable? monitor bus observe @ EC_OC */
		Write16(state, EC_OC_REG_OC_MON_SIO__A, 0x0000, 0x0000);
	पूर्ण

	/* करो inverse broadcast, followed by explicit ग_लिखो to HI */
	Write16(state, HI_COMM_MB__A, 0x0000, DRX_I2C_BROADCAST);
	Write16(state, HI_COMM_MB__A, 0x0000, 0x0000);
	वापस 0;
पूर्ण

अटल पूर्णांक InitCC(काष्ठा drxd_state *state)
अणु
	पूर्णांक status = 0;

	अगर (state->osc_घड़ी_freq == 0 ||
	    state->osc_घड़ी_freq > 20000 ||
	    (state->osc_घड़ी_freq % 4000) != 0) अणु
		prपूर्णांकk(KERN_ERR "invalid osc frequency %d\n", state->osc_घड़ी_freq);
		वापस -1;
	पूर्ण

	status |= Write16(state, CC_REG_OSC_MODE__A, CC_REG_OSC_MODE_M20, 0);
	status |= Write16(state, CC_REG_PLL_MODE__A,
				CC_REG_PLL_MODE_BYPASS_PLL |
				CC_REG_PLL_MODE_PUMP_CUR_12, 0);
	status |= Write16(state, CC_REG_REF_DIVIDE__A,
				state->osc_घड़ी_freq / 4000, 0);
	status |= Write16(state, CC_REG_PWD_MODE__A, CC_REG_PWD_MODE_DOWN_PLL,
				0);
	status |= Write16(state, CC_REG_UPDATE__A, CC_REG_UPDATE_KEY, 0);

	वापस status;
पूर्ण

अटल पूर्णांक ResetECOD(काष्ठा drxd_state *state)
अणु
	पूर्णांक status = 0;

	अगर (state->type_A)
		status = Write16(state, EC_OD_REG_SYNC__A, 0x0664, 0);
	अन्यथा
		status = Write16(state, B_EC_OD_REG_SYNC__A, 0x0664, 0);

	अगर (!(status < 0))
		status = WriteTable(state, state->m_ResetECRAM);
	अगर (!(status < 0))
		status = Write16(state, EC_OD_REG_COMM_EXEC__A, 0x0001, 0);
	वापस status;
पूर्ण

/* Configure PGA चयन */

अटल पूर्णांक SetCfgPga(काष्ठा drxd_state *state, पूर्णांक pgaSwitch)
अणु
	पूर्णांक status;
	u16 AgModeLop = 0;
	u16 AgModeHip = 0;
	करो अणु
		अगर (pgaSwitch) अणु
			/* PGA on */
			/* fine gain */
			status = Read16(state, B_FE_AG_REG_AG_MODE_LOP__A, &AgModeLop, 0x0000);
			अगर (status < 0)
				अवरोध;
			AgModeLop &= (~(B_FE_AG_REG_AG_MODE_LOP_MODE_C__M));
			AgModeLop |= B_FE_AG_REG_AG_MODE_LOP_MODE_C_DYNAMIC;
			status = Write16(state, B_FE_AG_REG_AG_MODE_LOP__A, AgModeLop, 0x0000);
			अगर (status < 0)
				अवरोध;

			/* coarse gain */
			status = Read16(state, B_FE_AG_REG_AG_MODE_HIP__A, &AgModeHip, 0x0000);
			अगर (status < 0)
				अवरोध;
			AgModeHip &= (~(B_FE_AG_REG_AG_MODE_HIP_MODE_J__M));
			AgModeHip |= B_FE_AG_REG_AG_MODE_HIP_MODE_J_DYNAMIC;
			status = Write16(state, B_FE_AG_REG_AG_MODE_HIP__A, AgModeHip, 0x0000);
			अगर (status < 0)
				अवरोध;

			/* enable fine and coarse gain, enable AAF,
			   no ext resistor */
			status = Write16(state, B_FE_AG_REG_AG_PGA_MODE__A, B_FE_AG_REG_AG_PGA_MODE_PFY_PCY_AFY_REN, 0x0000);
			अगर (status < 0)
				अवरोध;
		पूर्ण अन्यथा अणु
			/* PGA off, bypass */

			/* fine gain */
			status = Read16(state, B_FE_AG_REG_AG_MODE_LOP__A, &AgModeLop, 0x0000);
			अगर (status < 0)
				अवरोध;
			AgModeLop &= (~(B_FE_AG_REG_AG_MODE_LOP_MODE_C__M));
			AgModeLop |= B_FE_AG_REG_AG_MODE_LOP_MODE_C_STATIC;
			status = Write16(state, B_FE_AG_REG_AG_MODE_LOP__A, AgModeLop, 0x0000);
			अगर (status < 0)
				अवरोध;

			/* coarse gain */
			status = Read16(state, B_FE_AG_REG_AG_MODE_HIP__A, &AgModeHip, 0x0000);
			अगर (status < 0)
				अवरोध;
			AgModeHip &= (~(B_FE_AG_REG_AG_MODE_HIP_MODE_J__M));
			AgModeHip |= B_FE_AG_REG_AG_MODE_HIP_MODE_J_STATIC;
			status = Write16(state, B_FE_AG_REG_AG_MODE_HIP__A, AgModeHip, 0x0000);
			अगर (status < 0)
				अवरोध;

			/* disable fine and coarse gain, enable AAF,
			   no ext resistor */
			status = Write16(state, B_FE_AG_REG_AG_PGA_MODE__A, B_FE_AG_REG_AG_PGA_MODE_PFN_PCN_AFY_REN, 0x0000);
			अगर (status < 0)
				अवरोध;
		पूर्ण
	पूर्ण जबतक (0);
	वापस status;
पूर्ण

अटल पूर्णांक InitFE(काष्ठा drxd_state *state)
अणु
	पूर्णांक status;

	करो अणु
		status = WriteTable(state, state->m_InitFE_1);
		अगर (status < 0)
			अवरोध;

		अगर (state->type_A) अणु
			status = Write16(state, FE_AG_REG_AG_PGA_MODE__A,
					 FE_AG_REG_AG_PGA_MODE_PFN_PCN_AFY_REN,
					 0);
		पूर्ण अन्यथा अणु
			अगर (state->PGA)
				status = SetCfgPga(state, 0);
			अन्यथा
				status =
				    Write16(state, B_FE_AG_REG_AG_PGA_MODE__A,
					    B_FE_AG_REG_AG_PGA_MODE_PFN_PCN_AFY_REN,
					    0);
		पूर्ण

		अगर (status < 0)
			अवरोध;
		status = Write16(state, FE_AG_REG_AG_AGC_SIO__A, state->m_FeAgRegAgAgcSio, 0x0000);
		अगर (status < 0)
			अवरोध;
		status = Write16(state, FE_AG_REG_AG_PWD__A, state->m_FeAgRegAgPwd, 0x0000);
		अगर (status < 0)
			अवरोध;

		status = WriteTable(state, state->m_InitFE_2);
		अगर (status < 0)
			अवरोध;

	पूर्ण जबतक (0);

	वापस status;
पूर्ण

अटल पूर्णांक InitFT(काष्ठा drxd_state *state)
अणु
	/*
	   norm OFFSET,  MB says =2 voor 8K en =3 voor 2K waarschijnlijk
	   SC stuff
	 */
	वापस Write16(state, FT_REG_COMM_EXEC__A, 0x0001, 0x0000);
पूर्ण

अटल पूर्णांक SC_WaitForReady(काष्ठा drxd_state *state)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < DRXD_MAX_RETRIES; i += 1) अणु
		पूर्णांक status = Read16(state, SC_RA_RAM_CMD__A, शून्य, 0);
		अगर (status == 0)
			वापस status;
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक SC_SendCommand(काष्ठा drxd_state *state, u16 cmd)
अणु
	पूर्णांक status = 0, ret;
	u16 errCode;

	status = Write16(state, SC_RA_RAM_CMD__A, cmd, 0);
	अगर (status < 0)
		वापस status;

	SC_WaitForReady(state);

	ret = Read16(state, SC_RA_RAM_CMD_ADDR__A, &errCode, 0);

	अगर (ret < 0 || errCode == 0xFFFF) अणु
		prपूर्णांकk(KERN_ERR "Command Error\n");
		status = -1;
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक SC_ProcStartCommand(काष्ठा drxd_state *state,
			       u16 subCmd, u16 param0, u16 param1)
अणु
	पूर्णांक ret, status = 0;
	u16 scExec;

	mutex_lock(&state->mutex);
	करो अणु
		ret = Read16(state, SC_COMM_EXEC__A, &scExec, 0);
		अगर (ret < 0 || scExec != 1) अणु
			status = -1;
			अवरोध;
		पूर्ण
		SC_WaitForReady(state);
		status |= Write16(state, SC_RA_RAM_CMD_ADDR__A, subCmd, 0);
		status |= Write16(state, SC_RA_RAM_PARAM1__A, param1, 0);
		status |= Write16(state, SC_RA_RAM_PARAM0__A, param0, 0);

		SC_SendCommand(state, SC_RA_RAM_CMD_PROC_START);
	पूर्ण जबतक (0);
	mutex_unlock(&state->mutex);
	वापस status;
पूर्ण

अटल पूर्णांक SC_SetPrefParamCommand(काष्ठा drxd_state *state,
				  u16 subCmd, u16 param0, u16 param1)
अणु
	पूर्णांक status;

	mutex_lock(&state->mutex);
	करो अणु
		status = SC_WaitForReady(state);
		अगर (status < 0)
			अवरोध;
		status = Write16(state, SC_RA_RAM_CMD_ADDR__A, subCmd, 0);
		अगर (status < 0)
			अवरोध;
		status = Write16(state, SC_RA_RAM_PARAM1__A, param1, 0);
		अगर (status < 0)
			अवरोध;
		status = Write16(state, SC_RA_RAM_PARAM0__A, param0, 0);
		अगर (status < 0)
			अवरोध;

		status = SC_SendCommand(state, SC_RA_RAM_CMD_SET_PREF_PARAM);
		अगर (status < 0)
			अवरोध;
	पूर्ण जबतक (0);
	mutex_unlock(&state->mutex);
	वापस status;
पूर्ण

#अगर 0
अटल पूर्णांक SC_GetOpParamCommand(काष्ठा drxd_state *state, u16 * result)
अणु
	पूर्णांक status = 0;

	mutex_lock(&state->mutex);
	करो अणु
		status = SC_WaitForReady(state);
		अगर (status < 0)
			अवरोध;
		status = SC_SendCommand(state, SC_RA_RAM_CMD_GET_OP_PARAM);
		अगर (status < 0)
			अवरोध;
		status = Read16(state, SC_RA_RAM_PARAM0__A, result, 0);
		अगर (status < 0)
			अवरोध;
	पूर्ण जबतक (0);
	mutex_unlock(&state->mutex);
	वापस status;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ConfigureMPEGOutput(काष्ठा drxd_state *state, पूर्णांक bEnableOutput)
अणु
	पूर्णांक status;

	करो अणु
		u16 EcOcRegIprInvMpg = 0;
		u16 EcOcRegOcModeLop = 0;
		u16 EcOcRegOcModeHip = 0;
		u16 EcOcRegOcMpgSio = 0;

		/*CHK_ERROR(Read16(state, EC_OC_REG_OC_MODE_LOP__A, &EcOcRegOcModeLop, 0)); */

		अगर (state->operation_mode == OM_DVBT_Diversity_Front) अणु
			अगर (bEnableOutput) अणु
				EcOcRegOcModeHip |=
				    B_EC_OC_REG_OC_MODE_HIP_MPG_BUS_SRC_MONITOR;
			पूर्ण अन्यथा
				EcOcRegOcMpgSio |= EC_OC_REG_OC_MPG_SIO__M;
			EcOcRegOcModeLop |=
			    EC_OC_REG_OC_MODE_LOP_PAR_ENA_DISABLE;
		पूर्ण अन्यथा अणु
			EcOcRegOcModeLop = state->m_EcOcRegOcModeLop;

			अगर (bEnableOutput)
				EcOcRegOcMpgSio &= (~(EC_OC_REG_OC_MPG_SIO__M));
			अन्यथा
				EcOcRegOcMpgSio |= EC_OC_REG_OC_MPG_SIO__M;

			/* Don't Insert RS Byte */
			अगर (state->insert_rs_byte) अणु
				EcOcRegOcModeLop &=
				    (~(EC_OC_REG_OC_MODE_LOP_PAR_ENA__M));
				EcOcRegOcModeHip &=
				    (~EC_OC_REG_OC_MODE_HIP_MPG_PAR_VAL__M);
				EcOcRegOcModeHip |=
				    EC_OC_REG_OC_MODE_HIP_MPG_PAR_VAL_ENABLE;
			पूर्ण अन्यथा अणु
				EcOcRegOcModeLop |=
				    EC_OC_REG_OC_MODE_LOP_PAR_ENA_DISABLE;
				EcOcRegOcModeHip &=
				    (~EC_OC_REG_OC_MODE_HIP_MPG_PAR_VAL__M);
				EcOcRegOcModeHip |=
				    EC_OC_REG_OC_MODE_HIP_MPG_PAR_VAL_DISABLE;
			पूर्ण

			/* Mode = Parallel */
			अगर (state->enable_parallel)
				EcOcRegOcModeLop &=
				    (~(EC_OC_REG_OC_MODE_LOP_MPG_TRM_MDE__M));
			अन्यथा
				EcOcRegOcModeLop |=
				    EC_OC_REG_OC_MODE_LOP_MPG_TRM_MDE_SERIAL;
		पूर्ण
		/* Invert Data */
		/* EcOcRegIprInvMpg |= 0x00FF; */
		EcOcRegIprInvMpg &= (~(0x00FF));

		/* Invert Error ( we करोn't use the pin ) */
		/*  EcOcRegIprInvMpg |= 0x0100; */
		EcOcRegIprInvMpg &= (~(0x0100));

		/* Invert Start ( we करोn't use the pin ) */
		/* EcOcRegIprInvMpg |= 0x0200; */
		EcOcRegIprInvMpg &= (~(0x0200));

		/* Invert Valid ( we करोn't use the pin ) */
		/* EcOcRegIprInvMpg |= 0x0400; */
		EcOcRegIprInvMpg &= (~(0x0400));

		/* Invert Clock */
		/* EcOcRegIprInvMpg |= 0x0800; */
		EcOcRegIprInvMpg &= (~(0x0800));

		/* EcOcRegOcModeLop =0x05; */
		status = Write16(state, EC_OC_REG_IPR_INV_MPG__A, EcOcRegIprInvMpg, 0);
		अगर (status < 0)
			अवरोध;
		status = Write16(state, EC_OC_REG_OC_MODE_LOP__A, EcOcRegOcModeLop, 0);
		अगर (status < 0)
			अवरोध;
		status = Write16(state, EC_OC_REG_OC_MODE_HIP__A, EcOcRegOcModeHip, 0x0000);
		अगर (status < 0)
			अवरोध;
		status = Write16(state, EC_OC_REG_OC_MPG_SIO__A, EcOcRegOcMpgSio, 0);
		अगर (status < 0)
			अवरोध;
	पूर्ण जबतक (0);
	वापस status;
पूर्ण

अटल पूर्णांक SetDeviceTypeId(काष्ठा drxd_state *state)
अणु
	पूर्णांक status = 0;
	u16 deviceId = 0;

	करो अणु
		status = Read16(state, CC_REG_JTAGID_L__A, &deviceId, 0);
		अगर (status < 0)
			अवरोध;
		/* TODO: why twice? */
		status = Read16(state, CC_REG_JTAGID_L__A, &deviceId, 0);
		अगर (status < 0)
			अवरोध;
		prपूर्णांकk(KERN_INFO "drxd: deviceId = %04x\n", deviceId);

		state->type_A = 0;
		state->PGA = 0;
		state->भागersity = 0;
		अगर (deviceId == 0) अणु	/* on A2 only 3975 available */
			state->type_A = 1;
			prपूर्णांकk(KERN_INFO "DRX3975D-A2\n");
		पूर्ण अन्यथा अणु
			deviceId >>= 12;
			prपूर्णांकk(KERN_INFO "DRX397%dD-B1\n", deviceId);
			चयन (deviceId) अणु
			हाल 4:
				state->भागersity = 1;
				fallthrough;
			हाल 3:
			हाल 7:
				state->PGA = 1;
				अवरोध;
			हाल 6:
				state->भागersity = 1;
				fallthrough;
			हाल 5:
			हाल 8:
				अवरोध;
			शेष:
				status = -1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (0);

	अगर (status < 0)
		वापस status;

	/* Init Table selection */
	state->m_InitAtomicRead = DRXD_InitAtomicRead;
	state->m_InitSC = DRXD_InitSC;
	state->m_ResetECRAM = DRXD_ResetECRAM;
	अगर (state->type_A) अणु
		state->m_ResetCEFR = DRXD_ResetCEFR;
		state->m_InitFE_1 = DRXD_InitFEA2_1;
		state->m_InitFE_2 = DRXD_InitFEA2_2;
		state->m_InitCP = DRXD_InitCPA2;
		state->m_InitCE = DRXD_InitCEA2;
		state->m_InitEQ = DRXD_InitEQA2;
		state->m_InitEC = DRXD_InitECA2;
		अगर (load_firmware(state, DRX_FW_खाताNAME_A2))
			वापस -EIO;
	पूर्ण अन्यथा अणु
		state->m_ResetCEFR = शून्य;
		state->m_InitFE_1 = DRXD_InitFEB1_1;
		state->m_InitFE_2 = DRXD_InitFEB1_2;
		state->m_InitCP = DRXD_InitCPB1;
		state->m_InitCE = DRXD_InitCEB1;
		state->m_InitEQ = DRXD_InitEQB1;
		state->m_InitEC = DRXD_InitECB1;
		अगर (load_firmware(state, DRX_FW_खाताNAME_B1))
			वापस -EIO;
	पूर्ण
	अगर (state->भागersity) अणु
		state->m_InitDiversityFront = DRXD_InitDiversityFront;
		state->m_InitDiversityEnd = DRXD_InitDiversityEnd;
		state->m_DisableDiversity = DRXD_DisableDiversity;
		state->m_StartDiversityFront = DRXD_StartDiversityFront;
		state->m_StartDiversityEnd = DRXD_StartDiversityEnd;
		state->m_DiversityDelay8MHZ = DRXD_DiversityDelay8MHZ;
		state->m_DiversityDelay6MHZ = DRXD_DiversityDelay6MHZ;
	पूर्ण अन्यथा अणु
		state->m_InitDiversityFront = शून्य;
		state->m_InitDiversityEnd = शून्य;
		state->m_DisableDiversity = शून्य;
		state->m_StartDiversityFront = शून्य;
		state->m_StartDiversityEnd = शून्य;
		state->m_DiversityDelay8MHZ = शून्य;
		state->m_DiversityDelay6MHZ = शून्य;
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक CorrectSysClockDeviation(काष्ठा drxd_state *state)
अणु
	पूर्णांक status;
	s32 incr = 0;
	s32 nomincr = 0;
	u32 bandwidth = 0;
	u32 sysClockInHz = 0;
	u32 sysClockFreq = 0;	/* in kHz */
	s16 oscClockDeviation;
	s16 Dअगरf;

	करो अणु
		/* Retrieve bandwidth and incr, sanity check */

		/* These accesses should be AtomicReadReg32, but that
		   causes trouble (at least क्रम भागersity */
		status = Read32(state, LC_RA_RAM_IFINCR_NOM_L__A, ((u32 *) &nomincr), 0);
		अगर (status < 0)
			अवरोध;
		status = Read32(state, FE_IF_REG_INCR0__A, (u32 *) &incr, 0);
		अगर (status < 0)
			अवरोध;

		अगर (state->type_A) अणु
			अगर ((nomincr - incr < -500) || (nomincr - incr > 500))
				अवरोध;
		पूर्ण अन्यथा अणु
			अगर ((nomincr - incr < -2000) || (nomincr - incr > 2000))
				अवरोध;
		पूर्ण

		चयन (state->props.bandwidth_hz) अणु
		हाल 8000000:
			bandwidth = DRXD_BANDWIDTH_8MHZ_IN_HZ;
			अवरोध;
		हाल 7000000:
			bandwidth = DRXD_BANDWIDTH_7MHZ_IN_HZ;
			अवरोध;
		हाल 6000000:
			bandwidth = DRXD_BANDWIDTH_6MHZ_IN_HZ;
			अवरोध;
		शेष:
			वापस -1;
		पूर्ण

		/* Compute new sysघड़ी value
		   sysClockFreq = (((incr + 2^23)*bandwidth)/2^21)/1000 */
		incr += (1 << 23);
		sysClockInHz = MulDiv32(incr, bandwidth, 1 << 21);
		sysClockFreq = (u32) (sysClockInHz / 1000);
		/* rounding */
		अगर ((sysClockInHz % 1000) > 500)
			sysClockFreq++;

		/* Compute घड़ी deviation in ppm */
		oscClockDeviation = (u16) ((((s32) (sysClockFreq) -
					     (s32)
					     (state->expected_sys_घड़ी_freq)) *
					    1000000L) /
					   (s32)
					   (state->expected_sys_घड़ी_freq));

		Dअगरf = oscClockDeviation - state->osc_घड़ी_deviation;
		/*prपूर्णांकk(KERN_INFO "sysclockdiff=%d\n", Dअगरf); */
		अगर (Dअगरf >= -200 && Dअगरf <= 200) अणु
			state->sys_घड़ी_freq = (u16) sysClockFreq;
			अगर (oscClockDeviation != state->osc_घड़ी_deviation) अणु
				अगर (state->config.osc_deviation) अणु
					state->config.osc_deviation(state->priv,
								    oscClockDeviation,
								    1);
					state->osc_घड़ी_deviation =
					    oscClockDeviation;
				पूर्ण
			पूर्ण
			/* चयन OFF SRMM scan in SC */
			status = Write16(state, SC_RA_RAM_SAMPLE_RATE_COUNT__A, DRXD_OSCDEV_DONT_SCAN, 0);
			अगर (status < 0)
				अवरोध;
			/* overrule FE_IF पूर्णांकernal value क्रम
			   proper re-locking */
			status = Write16(state, SC_RA_RAM_IF_SAVE__AX, state->current_fe_अगर_incr, 0);
			अगर (status < 0)
				अवरोध;
			state->cscd_state = CSCD_SAVED;
		पूर्ण
	पूर्ण जबतक (0);

	वापस status;
पूर्ण

अटल पूर्णांक DRX_Stop(काष्ठा drxd_state *state)
अणु
	पूर्णांक status;

	अगर (state->drxd_state != DRXD_STARTED)
		वापस 0;

	करो अणु
		अगर (state->cscd_state != CSCD_SAVED) अणु
			u32 lock;
			status = DRX_GetLockStatus(state, &lock);
			अगर (status < 0)
				अवरोध;
		पूर्ण

		status = StopOC(state);
		अगर (status < 0)
			अवरोध;

		state->drxd_state = DRXD_STOPPED;

		status = ConfigureMPEGOutput(state, 0);
		अगर (status < 0)
			अवरोध;

		अगर (state->type_A) अणु
			/* Stop relevant processors off the device */
			status = Write16(state, EC_OD_REG_COMM_EXEC__A, 0x0000, 0x0000);
			अगर (status < 0)
				अवरोध;

			status = Write16(state, SC_COMM_EXEC__A, SC_COMM_EXEC_CTL_STOP, 0);
			अगर (status < 0)
				अवरोध;
			status = Write16(state, LC_COMM_EXEC__A, SC_COMM_EXEC_CTL_STOP, 0);
			अगर (status < 0)
				अवरोध;
		पूर्ण अन्यथा अणु
			/* Stop all processors except HI & CC & FE */
			status = Write16(state, B_SC_COMM_EXEC__A, SC_COMM_EXEC_CTL_STOP, 0);
			अगर (status < 0)
				अवरोध;
			status = Write16(state, B_LC_COMM_EXEC__A, SC_COMM_EXEC_CTL_STOP, 0);
			अगर (status < 0)
				अवरोध;
			status = Write16(state, B_FT_COMM_EXEC__A, SC_COMM_EXEC_CTL_STOP, 0);
			अगर (status < 0)
				अवरोध;
			status = Write16(state, B_CP_COMM_EXEC__A, SC_COMM_EXEC_CTL_STOP, 0);
			अगर (status < 0)
				अवरोध;
			status = Write16(state, B_CE_COMM_EXEC__A, SC_COMM_EXEC_CTL_STOP, 0);
			अगर (status < 0)
				अवरोध;
			status = Write16(state, B_EQ_COMM_EXEC__A, SC_COMM_EXEC_CTL_STOP, 0);
			अगर (status < 0)
				अवरोध;
			status = Write16(state, EC_OD_REG_COMM_EXEC__A, 0x0000, 0);
			अगर (status < 0)
				अवरोध;
		पूर्ण

	पूर्ण जबतक (0);
	वापस status;
पूर्ण

#अगर 0	/* Currently unused */
अटल पूर्णांक SetOperationMode(काष्ठा drxd_state *state, पूर्णांक oMode)
अणु
	पूर्णांक status;

	करो अणु
		अगर (state->drxd_state != DRXD_STOPPED) अणु
			status = -1;
			अवरोध;
		पूर्ण

		अगर (oMode == state->operation_mode) अणु
			status = 0;
			अवरोध;
		पूर्ण

		अगर (oMode != OM_Default && !state->भागersity) अणु
			status = -1;
			अवरोध;
		पूर्ण

		चयन (oMode) अणु
		हाल OM_DVBT_Diversity_Front:
			status = WriteTable(state, state->m_InitDiversityFront);
			अवरोध;
		हाल OM_DVBT_Diversity_End:
			status = WriteTable(state, state->m_InitDiversityEnd);
			अवरोध;
		हाल OM_Default:
			/* We need to check how to
			   get DRXD out of भागersity */
		शेष:
			status = WriteTable(state, state->m_DisableDiversity);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (0);

	अगर (!status)
		state->operation_mode = oMode;
	वापस status;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक StartDiversity(काष्ठा drxd_state *state)
अणु
	पूर्णांक status = 0;
	u16 rcControl;

	करो अणु
		अगर (state->operation_mode == OM_DVBT_Diversity_Front) अणु
			status = WriteTable(state, state->m_StartDiversityFront);
			अगर (status < 0)
				अवरोध;
		पूर्ण अन्यथा अगर (state->operation_mode == OM_DVBT_Diversity_End) अणु
			status = WriteTable(state, state->m_StartDiversityEnd);
			अगर (status < 0)
				अवरोध;
			अगर (state->props.bandwidth_hz == 8000000) अणु
				status = WriteTable(state, state->m_DiversityDelay8MHZ);
				अगर (status < 0)
					अवरोध;
			पूर्ण अन्यथा अणु
				status = WriteTable(state, state->m_DiversityDelay6MHZ);
				अगर (status < 0)
					अवरोध;
			पूर्ण

			status = Read16(state, B_EQ_REG_RC_SEL_CAR__A, &rcControl, 0);
			अगर (status < 0)
				अवरोध;
			rcControl &= ~(B_EQ_REG_RC_SEL_CAR_FFTMODE__M);
			rcControl |= B_EQ_REG_RC_SEL_CAR_DIV_ON |
			    /*  combining enabled */
			    B_EQ_REG_RC_SEL_CAR_MEAS_A_CC |
			    B_EQ_REG_RC_SEL_CAR_PASS_A_CC |
			    B_EQ_REG_RC_SEL_CAR_LOCAL_A_CC;
			status = Write16(state, B_EQ_REG_RC_SEL_CAR__A, rcControl, 0);
			अगर (status < 0)
				अवरोध;
		पूर्ण
	पूर्ण जबतक (0);
	वापस status;
पूर्ण

अटल पूर्णांक SetFrequencyShअगरt(काष्ठा drxd_state *state,
			     u32 offsetFreq, पूर्णांक channelMirrored)
अणु
	पूर्णांक negativeShअगरt = (state->tuner_mirrors == channelMirrored);

	/* Handle all mirroring
	 *
	 * Note: ADC mirroring (aliasing) is implictly handled by limiting
	 * feFsRegAddInc to 28 bits below
	 * (अगर the result beक्रमe masking is more than 28 bits, this means
	 *  that the ADC is mirroring.
	 * The masking is in fact the aliasing of the ADC)
	 *
	 */

	/* Compute रेजिस्टर value, अचिन्हित computation */
	state->fe_fs_add_incr = MulDiv32(state->पूर्णांकermediate_freq +
					 offsetFreq,
					 1 << 28, state->sys_घड़ी_freq);
	/* Remove पूर्णांकeger part */
	state->fe_fs_add_incr &= 0x0FFFFFFFL;
	अगर (negativeShअगरt)
		state->fe_fs_add_incr = ((1 << 28) - state->fe_fs_add_incr);

	/* Save the frequency shअगरt without tunerOffset compensation
	   क्रम CtrlGetChannel. */
	state->org_fe_fs_add_incr = MulDiv32(state->पूर्णांकermediate_freq,
					     1 << 28, state->sys_घड़ी_freq);
	/* Remove पूर्णांकeger part */
	state->org_fe_fs_add_incr &= 0x0FFFFFFFL;
	अगर (negativeShअगरt)
		state->org_fe_fs_add_incr = ((1L << 28) -
					     state->org_fe_fs_add_incr);

	वापस Write32(state, FE_FS_REG_ADD_INC_LOP__A,
		       state->fe_fs_add_incr, 0);
पूर्ण

अटल पूर्णांक SetCfgNoiseCalibration(काष्ठा drxd_state *state,
				  काष्ठा SNoiseCal *noiseCal)
अणु
	u16 beOptEna;
	पूर्णांक status = 0;

	करो अणु
		status = Read16(state, SC_RA_RAM_BE_OPT_ENA__A, &beOptEna, 0);
		अगर (status < 0)
			अवरोध;
		अगर (noiseCal->cpOpt) अणु
			beOptEna |= (1 << SC_RA_RAM_BE_OPT_ENA_CP_OPT);
		पूर्ण अन्यथा अणु
			beOptEna &= ~(1 << SC_RA_RAM_BE_OPT_ENA_CP_OPT);
			status = Write16(state, CP_REG_AC_NEXP_OFFS__A, noiseCal->cpNexpOfs, 0);
			अगर (status < 0)
				अवरोध;
		पूर्ण
		status = Write16(state, SC_RA_RAM_BE_OPT_ENA__A, beOptEna, 0);
		अगर (status < 0)
			अवरोध;

		अगर (!state->type_A) अणु
			status = Write16(state, B_SC_RA_RAM_CO_TD_CAL_2K__A, noiseCal->tdCal2k, 0);
			अगर (status < 0)
				अवरोध;
			status = Write16(state, B_SC_RA_RAM_CO_TD_CAL_8K__A, noiseCal->tdCal8k, 0);
			अगर (status < 0)
				अवरोध;
		पूर्ण
	पूर्ण जबतक (0);

	वापस status;
पूर्ण

अटल पूर्णांक DRX_Start(काष्ठा drxd_state *state, s32 off)
अणु
	काष्ठा dtv_frontend_properties *p = &state->props;
	पूर्णांक status;

	u16 transmissionParams = 0;
	u16 operationMode = 0;
	u16 qpskTdTpsPwr = 0;
	u16 qam16TdTpsPwr = 0;
	u16 qam64TdTpsPwr = 0;
	u32 feIfIncr = 0;
	u32 bandwidth = 0;
	पूर्णांक mirrorFreqSpect;

	u16 qpskSnCeGain = 0;
	u16 qam16SnCeGain = 0;
	u16 qam64SnCeGain = 0;
	u16 qpskIsGainMan = 0;
	u16 qam16IsGainMan = 0;
	u16 qam64IsGainMan = 0;
	u16 qpskIsGainExp = 0;
	u16 qam16IsGainExp = 0;
	u16 qam64IsGainExp = 0;
	u16 bandwidthParam = 0;

	अगर (off < 0)
		off = (off - 500) / 1000;
	अन्यथा
		off = (off + 500) / 1000;

	करो अणु
		अगर (state->drxd_state != DRXD_STOPPED)
			वापस -1;
		status = ResetECOD(state);
		अगर (status < 0)
			अवरोध;
		अगर (state->type_A) अणु
			status = InitSC(state);
			अगर (status < 0)
				अवरोध;
		पूर्ण अन्यथा अणु
			status = InitFT(state);
			अगर (status < 0)
				अवरोध;
			status = InitCP(state);
			अगर (status < 0)
				अवरोध;
			status = InitCE(state);
			अगर (status < 0)
				अवरोध;
			status = InitEQ(state);
			अगर (status < 0)
				अवरोध;
			status = InitSC(state);
			अगर (status < 0)
				अवरोध;
		पूर्ण

		/* Restore current IF & RF AGC settings */

		status = SetCfgIfAgc(state, &state->अगर_agc_cfg);
		अगर (status < 0)
			अवरोध;
		status = SetCfgRfAgc(state, &state->rf_agc_cfg);
		अगर (status < 0)
			अवरोध;

		mirrorFreqSpect = (state->props.inversion == INVERSION_ON);

		चयन (p->transmission_mode) अणु
		शेष:	/* Not set, detect it स्वतःmatically */
			operationMode |= SC_RA_RAM_OP_AUTO_MODE__M;
			fallthrough;	/* try first guess DRX_FFTMODE_8K */
		हाल TRANSMISSION_MODE_8K:
			transmissionParams |= SC_RA_RAM_OP_PARAM_MODE_8K;
			अगर (state->type_A) अणु
				status = Write16(state, EC_SB_REG_TR_MODE__A, EC_SB_REG_TR_MODE_8K, 0x0000);
				अगर (status < 0)
					अवरोध;
				qpskSnCeGain = 99;
				qam16SnCeGain = 83;
				qam64SnCeGain = 67;
			पूर्ण
			अवरोध;
		हाल TRANSMISSION_MODE_2K:
			transmissionParams |= SC_RA_RAM_OP_PARAM_MODE_2K;
			अगर (state->type_A) अणु
				status = Write16(state, EC_SB_REG_TR_MODE__A, EC_SB_REG_TR_MODE_2K, 0x0000);
				अगर (status < 0)
					अवरोध;
				qpskSnCeGain = 97;
				qam16SnCeGain = 71;
				qam64SnCeGain = 65;
			पूर्ण
			अवरोध;
		पूर्ण

		चयन (p->guard_पूर्णांकerval) अणु
		हाल GUARD_INTERVAL_1_4:
			transmissionParams |= SC_RA_RAM_OP_PARAM_GUARD_4;
			अवरोध;
		हाल GUARD_INTERVAL_1_8:
			transmissionParams |= SC_RA_RAM_OP_PARAM_GUARD_8;
			अवरोध;
		हाल GUARD_INTERVAL_1_16:
			transmissionParams |= SC_RA_RAM_OP_PARAM_GUARD_16;
			अवरोध;
		हाल GUARD_INTERVAL_1_32:
			transmissionParams |= SC_RA_RAM_OP_PARAM_GUARD_32;
			अवरोध;
		शेष:	/* Not set, detect it स्वतःmatically */
			operationMode |= SC_RA_RAM_OP_AUTO_GUARD__M;
			/* try first guess 1/4 */
			transmissionParams |= SC_RA_RAM_OP_PARAM_GUARD_4;
			अवरोध;
		पूर्ण

		चयन (p->hierarchy) अणु
		हाल HIERARCHY_1:
			transmissionParams |= SC_RA_RAM_OP_PARAM_HIER_A1;
			अगर (state->type_A) अणु
				status = Write16(state, EQ_REG_OT_ALPHA__A, 0x0001, 0x0000);
				अगर (status < 0)
					अवरोध;
				status = Write16(state, EC_SB_REG_ALPHA__A, 0x0001, 0x0000);
				अगर (status < 0)
					अवरोध;

				qpskTdTpsPwr = EQ_TD_TPS_PWR_UNKNOWN;
				qam16TdTpsPwr = EQ_TD_TPS_PWR_QAM16_ALPHA1;
				qam64TdTpsPwr = EQ_TD_TPS_PWR_QAM64_ALPHA1;

				qpskIsGainMan =
				    SC_RA_RAM_EQ_IS_GAIN_UNKNOWN_MAN__PRE;
				qam16IsGainMan =
				    SC_RA_RAM_EQ_IS_GAIN_16QAM_MAN__PRE;
				qam64IsGainMan =
				    SC_RA_RAM_EQ_IS_GAIN_64QAM_MAN__PRE;

				qpskIsGainExp =
				    SC_RA_RAM_EQ_IS_GAIN_UNKNOWN_EXP__PRE;
				qam16IsGainExp =
				    SC_RA_RAM_EQ_IS_GAIN_16QAM_EXP__PRE;
				qam64IsGainExp =
				    SC_RA_RAM_EQ_IS_GAIN_64QAM_EXP__PRE;
			पूर्ण
			अवरोध;

		हाल HIERARCHY_2:
			transmissionParams |= SC_RA_RAM_OP_PARAM_HIER_A2;
			अगर (state->type_A) अणु
				status = Write16(state, EQ_REG_OT_ALPHA__A, 0x0002, 0x0000);
				अगर (status < 0)
					अवरोध;
				status = Write16(state, EC_SB_REG_ALPHA__A, 0x0002, 0x0000);
				अगर (status < 0)
					अवरोध;

				qpskTdTpsPwr = EQ_TD_TPS_PWR_UNKNOWN;
				qam16TdTpsPwr = EQ_TD_TPS_PWR_QAM16_ALPHA2;
				qam64TdTpsPwr = EQ_TD_TPS_PWR_QAM64_ALPHA2;

				qpskIsGainMan =
				    SC_RA_RAM_EQ_IS_GAIN_UNKNOWN_MAN__PRE;
				qam16IsGainMan =
				    SC_RA_RAM_EQ_IS_GAIN_16QAM_A2_MAN__PRE;
				qam64IsGainMan =
				    SC_RA_RAM_EQ_IS_GAIN_64QAM_A2_MAN__PRE;

				qpskIsGainExp =
				    SC_RA_RAM_EQ_IS_GAIN_UNKNOWN_EXP__PRE;
				qam16IsGainExp =
				    SC_RA_RAM_EQ_IS_GAIN_16QAM_A2_EXP__PRE;
				qam64IsGainExp =
				    SC_RA_RAM_EQ_IS_GAIN_64QAM_A2_EXP__PRE;
			पूर्ण
			अवरोध;
		हाल HIERARCHY_4:
			transmissionParams |= SC_RA_RAM_OP_PARAM_HIER_A4;
			अगर (state->type_A) अणु
				status = Write16(state, EQ_REG_OT_ALPHA__A, 0x0003, 0x0000);
				अगर (status < 0)
					अवरोध;
				status = Write16(state, EC_SB_REG_ALPHA__A, 0x0003, 0x0000);
				अगर (status < 0)
					अवरोध;

				qpskTdTpsPwr = EQ_TD_TPS_PWR_UNKNOWN;
				qam16TdTpsPwr = EQ_TD_TPS_PWR_QAM16_ALPHA4;
				qam64TdTpsPwr = EQ_TD_TPS_PWR_QAM64_ALPHA4;

				qpskIsGainMan =
				    SC_RA_RAM_EQ_IS_GAIN_UNKNOWN_MAN__PRE;
				qam16IsGainMan =
				    SC_RA_RAM_EQ_IS_GAIN_16QAM_A4_MAN__PRE;
				qam64IsGainMan =
				    SC_RA_RAM_EQ_IS_GAIN_64QAM_A4_MAN__PRE;

				qpskIsGainExp =
				    SC_RA_RAM_EQ_IS_GAIN_UNKNOWN_EXP__PRE;
				qam16IsGainExp =
				    SC_RA_RAM_EQ_IS_GAIN_16QAM_A4_EXP__PRE;
				qam64IsGainExp =
				    SC_RA_RAM_EQ_IS_GAIN_64QAM_A4_EXP__PRE;
			पूर्ण
			अवरोध;
		हाल HIERARCHY_AUTO:
		शेष:
			/* Not set, detect it स्वतःmatically, start with none */
			operationMode |= SC_RA_RAM_OP_AUTO_HIER__M;
			transmissionParams |= SC_RA_RAM_OP_PARAM_HIER_NO;
			अगर (state->type_A) अणु
				status = Write16(state, EQ_REG_OT_ALPHA__A, 0x0000, 0x0000);
				अगर (status < 0)
					अवरोध;
				status = Write16(state, EC_SB_REG_ALPHA__A, 0x0000, 0x0000);
				अगर (status < 0)
					अवरोध;

				qpskTdTpsPwr = EQ_TD_TPS_PWR_QPSK;
				qam16TdTpsPwr = EQ_TD_TPS_PWR_QAM16_ALPHAN;
				qam64TdTpsPwr = EQ_TD_TPS_PWR_QAM64_ALPHAN;

				qpskIsGainMan =
				    SC_RA_RAM_EQ_IS_GAIN_QPSK_MAN__PRE;
				qam16IsGainMan =
				    SC_RA_RAM_EQ_IS_GAIN_16QAM_MAN__PRE;
				qam64IsGainMan =
				    SC_RA_RAM_EQ_IS_GAIN_64QAM_MAN__PRE;

				qpskIsGainExp =
				    SC_RA_RAM_EQ_IS_GAIN_QPSK_EXP__PRE;
				qam16IsGainExp =
				    SC_RA_RAM_EQ_IS_GAIN_16QAM_EXP__PRE;
				qam64IsGainExp =
				    SC_RA_RAM_EQ_IS_GAIN_64QAM_EXP__PRE;
			पूर्ण
			अवरोध;
		पूर्ण
		अगर (status < 0)
			अवरोध;

		चयन (p->modulation) अणु
		शेष:
			operationMode |= SC_RA_RAM_OP_AUTO_CONST__M;
			fallthrough;	/* try first guess DRX_CONSTELLATION_QAM64 */
		हाल QAM_64:
			transmissionParams |= SC_RA_RAM_OP_PARAM_CONST_QAM64;
			अगर (state->type_A) अणु
				status = Write16(state, EQ_REG_OT_CONST__A, 0x0002, 0x0000);
				अगर (status < 0)
					अवरोध;
				status = Write16(state, EC_SB_REG_CONST__A, EC_SB_REG_CONST_64QAM, 0x0000);
				अगर (status < 0)
					अवरोध;
				status = Write16(state, EC_SB_REG_SCALE_MSB__A, 0x0020, 0x0000);
				अगर (status < 0)
					अवरोध;
				status = Write16(state, EC_SB_REG_SCALE_BIT2__A, 0x0008, 0x0000);
				अगर (status < 0)
					अवरोध;
				status = Write16(state, EC_SB_REG_SCALE_LSB__A, 0x0002, 0x0000);
				अगर (status < 0)
					अवरोध;

				status = Write16(state, EQ_REG_TD_TPS_PWR_OFS__A, qam64TdTpsPwr, 0x0000);
				अगर (status < 0)
					अवरोध;
				status = Write16(state, EQ_REG_SN_CEGAIN__A, qam64SnCeGain, 0x0000);
				अगर (status < 0)
					अवरोध;
				status = Write16(state, EQ_REG_IS_GAIN_MAN__A, qam64IsGainMan, 0x0000);
				अगर (status < 0)
					अवरोध;
				status = Write16(state, EQ_REG_IS_GAIN_EXP__A, qam64IsGainExp, 0x0000);
				अगर (status < 0)
					अवरोध;
			पूर्ण
			अवरोध;
		हाल QPSK:
			transmissionParams |= SC_RA_RAM_OP_PARAM_CONST_QPSK;
			अगर (state->type_A) अणु
				status = Write16(state, EQ_REG_OT_CONST__A, 0x0000, 0x0000);
				अगर (status < 0)
					अवरोध;
				status = Write16(state, EC_SB_REG_CONST__A, EC_SB_REG_CONST_QPSK, 0x0000);
				अगर (status < 0)
					अवरोध;
				status = Write16(state, EC_SB_REG_SCALE_MSB__A, 0x0010, 0x0000);
				अगर (status < 0)
					अवरोध;
				status = Write16(state, EC_SB_REG_SCALE_BIT2__A, 0x0000, 0x0000);
				अगर (status < 0)
					अवरोध;
				status = Write16(state, EC_SB_REG_SCALE_LSB__A, 0x0000, 0x0000);
				अगर (status < 0)
					अवरोध;

				status = Write16(state, EQ_REG_TD_TPS_PWR_OFS__A, qpskTdTpsPwr, 0x0000);
				अगर (status < 0)
					अवरोध;
				status = Write16(state, EQ_REG_SN_CEGAIN__A, qpskSnCeGain, 0x0000);
				अगर (status < 0)
					अवरोध;
				status = Write16(state, EQ_REG_IS_GAIN_MAN__A, qpskIsGainMan, 0x0000);
				अगर (status < 0)
					अवरोध;
				status = Write16(state, EQ_REG_IS_GAIN_EXP__A, qpskIsGainExp, 0x0000);
				अगर (status < 0)
					अवरोध;
			पूर्ण
			अवरोध;

		हाल QAM_16:
			transmissionParams |= SC_RA_RAM_OP_PARAM_CONST_QAM16;
			अगर (state->type_A) अणु
				status = Write16(state, EQ_REG_OT_CONST__A, 0x0001, 0x0000);
				अगर (status < 0)
					अवरोध;
				status = Write16(state, EC_SB_REG_CONST__A, EC_SB_REG_CONST_16QAM, 0x0000);
				अगर (status < 0)
					अवरोध;
				status = Write16(state, EC_SB_REG_SCALE_MSB__A, 0x0010, 0x0000);
				अगर (status < 0)
					अवरोध;
				status = Write16(state, EC_SB_REG_SCALE_BIT2__A, 0x0004, 0x0000);
				अगर (status < 0)
					अवरोध;
				status = Write16(state, EC_SB_REG_SCALE_LSB__A, 0x0000, 0x0000);
				अगर (status < 0)
					अवरोध;

				status = Write16(state, EQ_REG_TD_TPS_PWR_OFS__A, qam16TdTpsPwr, 0x0000);
				अगर (status < 0)
					अवरोध;
				status = Write16(state, EQ_REG_SN_CEGAIN__A, qam16SnCeGain, 0x0000);
				अगर (status < 0)
					अवरोध;
				status = Write16(state, EQ_REG_IS_GAIN_MAN__A, qam16IsGainMan, 0x0000);
				अगर (status < 0)
					अवरोध;
				status = Write16(state, EQ_REG_IS_GAIN_EXP__A, qam16IsGainExp, 0x0000);
				अगर (status < 0)
					अवरोध;
			पूर्ण
			अवरोध;

		पूर्ण
		अगर (status < 0)
			अवरोध;

		चयन (DRX_CHANNEL_HIGH) अणु
		शेष:
		हाल DRX_CHANNEL_AUTO:
		हाल DRX_CHANNEL_LOW:
			transmissionParams |= SC_RA_RAM_OP_PARAM_PRIO_LO;
			status = Write16(state, EC_SB_REG_PRIOR__A, EC_SB_REG_PRIOR_LO, 0x0000);
			अवरोध;
		हाल DRX_CHANNEL_HIGH:
			transmissionParams |= SC_RA_RAM_OP_PARAM_PRIO_HI;
			status = Write16(state, EC_SB_REG_PRIOR__A, EC_SB_REG_PRIOR_HI, 0x0000);
			अवरोध;
		पूर्ण

		चयन (p->code_rate_HP) अणु
		हाल FEC_1_2:
			transmissionParams |= SC_RA_RAM_OP_PARAM_RATE_1_2;
			अगर (state->type_A)
				status = Write16(state, EC_VD_REG_SET_CODERATE__A, EC_VD_REG_SET_CODERATE_C1_2, 0x0000);
			अवरोध;
		शेष:
			operationMode |= SC_RA_RAM_OP_AUTO_RATE__M;
			fallthrough;
		हाल FEC_2_3:
			transmissionParams |= SC_RA_RAM_OP_PARAM_RATE_2_3;
			अगर (state->type_A)
				status = Write16(state, EC_VD_REG_SET_CODERATE__A, EC_VD_REG_SET_CODERATE_C2_3, 0x0000);
			अवरोध;
		हाल FEC_3_4:
			transmissionParams |= SC_RA_RAM_OP_PARAM_RATE_3_4;
			अगर (state->type_A)
				status = Write16(state, EC_VD_REG_SET_CODERATE__A, EC_VD_REG_SET_CODERATE_C3_4, 0x0000);
			अवरोध;
		हाल FEC_5_6:
			transmissionParams |= SC_RA_RAM_OP_PARAM_RATE_5_6;
			अगर (state->type_A)
				status = Write16(state, EC_VD_REG_SET_CODERATE__A, EC_VD_REG_SET_CODERATE_C5_6, 0x0000);
			अवरोध;
		हाल FEC_7_8:
			transmissionParams |= SC_RA_RAM_OP_PARAM_RATE_7_8;
			अगर (state->type_A)
				status = Write16(state, EC_VD_REG_SET_CODERATE__A, EC_VD_REG_SET_CODERATE_C7_8, 0x0000);
			अवरोध;
		पूर्ण
		अगर (status < 0)
			अवरोध;

		/* First determine real bandwidth (Hz) */
		/* Also set delay क्रम impulse noise cruncher (only A2) */
		/* Also set parameters क्रम EC_OC fix, note
		   EC_OC_REG_TMD_HIL_MAR is changed
		   by SC क्रम fix क्रम some 8K,1/8 guard but is restored by
		   InitEC and ResetEC
		   functions */
		चयन (p->bandwidth_hz) अणु
		हाल 0:
			p->bandwidth_hz = 8000000;
			fallthrough;
		हाल 8000000:
			/* (64/7)*(8/8)*1000000 */
			bandwidth = DRXD_BANDWIDTH_8MHZ_IN_HZ;

			bandwidthParam = 0;
			status = Write16(state,
					 FE_AG_REG_IND_DEL__A, 50, 0x0000);
			अवरोध;
		हाल 7000000:
			/* (64/7)*(7/8)*1000000 */
			bandwidth = DRXD_BANDWIDTH_7MHZ_IN_HZ;
			bandwidthParam = 0x4807;	/*binary:0100 1000 0000 0111 */
			status = Write16(state,
					 FE_AG_REG_IND_DEL__A, 59, 0x0000);
			अवरोध;
		हाल 6000000:
			/* (64/7)*(6/8)*1000000 */
			bandwidth = DRXD_BANDWIDTH_6MHZ_IN_HZ;
			bandwidthParam = 0x0F07;	/*binary: 0000 1111 0000 0111 */
			status = Write16(state,
					 FE_AG_REG_IND_DEL__A, 71, 0x0000);
			अवरोध;
		शेष:
			status = -EINVAL;
		पूर्ण
		अगर (status < 0)
			अवरोध;

		status = Write16(state, SC_RA_RAM_BAND__A, bandwidthParam, 0x0000);
		अगर (status < 0)
			अवरोध;

		अणु
			u16 sc_config;
			status = Read16(state, SC_RA_RAM_CONFIG__A, &sc_config, 0);
			अगर (status < 0)
				अवरोध;

			/* enable SLAVE mode in 2k 1/32 to
			   prevent timing change glitches */
			अगर ((p->transmission_mode == TRANSMISSION_MODE_2K) &&
			    (p->guard_पूर्णांकerval == GUARD_INTERVAL_1_32)) अणु
				/* enable slave */
				sc_config |= SC_RA_RAM_CONFIG_SLAVE__M;
			पूर्ण अन्यथा अणु
				/* disable slave */
				sc_config &= ~SC_RA_RAM_CONFIG_SLAVE__M;
			पूर्ण
			status = Write16(state, SC_RA_RAM_CONFIG__A, sc_config, 0);
			अगर (status < 0)
				अवरोध;
		पूर्ण

		status = SetCfgNoiseCalibration(state, &state->noise_cal);
		अगर (status < 0)
			अवरोध;

		अगर (state->cscd_state == CSCD_INIT) अणु
			/* चयन on SRMM scan in SC */
			status = Write16(state, SC_RA_RAM_SAMPLE_RATE_COUNT__A, DRXD_OSCDEV_DO_SCAN, 0x0000);
			अगर (status < 0)
				अवरोध;
/*            CHK_ERROR(Write16(SC_RA_RAM_SAMPLE_RATE_STEP__A, DRXD_OSCDEV_STEP, 0x0000));*/
			state->cscd_state = CSCD_SET;
		पूर्ण

		/* Now compute FE_IF_REG_INCR */
		/*((( SysFreq/BandWidth)/2)/2) -1) * 2^23) =>
		   ((SysFreq / BandWidth) * (2^21) ) - (2^23) */
		feIfIncr = MulDiv32(state->sys_घड़ी_freq * 1000,
				    (1ULL << 21), bandwidth) - (1 << 23);
		status = Write16(state, FE_IF_REG_INCR0__A, (u16) (feIfIncr & FE_IF_REG_INCR0__M), 0x0000);
		अगर (status < 0)
			अवरोध;
		status = Write16(state, FE_IF_REG_INCR1__A, (u16) ((feIfIncr >> FE_IF_REG_INCR0__W) & FE_IF_REG_INCR1__M), 0x0000);
		अगर (status < 0)
			अवरोध;
		/* Bandwidth setting करोne */

		/* Mirror & frequency offset */
		SetFrequencyShअगरt(state, off, mirrorFreqSpect);

		/* Start SC, ग_लिखो channel settings to SC */

		/* Enable SC after setting all other parameters */
		status = Write16(state, SC_COMM_STATE__A, 0, 0x0000);
		अगर (status < 0)
			अवरोध;
		status = Write16(state, SC_COMM_EXEC__A, 1, 0x0000);
		अगर (status < 0)
			अवरोध;

		/* Write SC parameter रेजिस्टरs, operation mode */
#अगर 1
		operationMode = (SC_RA_RAM_OP_AUTO_MODE__M |
				 SC_RA_RAM_OP_AUTO_GUARD__M |
				 SC_RA_RAM_OP_AUTO_CONST__M |
				 SC_RA_RAM_OP_AUTO_HIER__M |
				 SC_RA_RAM_OP_AUTO_RATE__M);
#पूर्ण_अगर
		status = SC_SetPrefParamCommand(state, 0x0000, transmissionParams, operationMode);
		अगर (status < 0)
			अवरोध;

		/* Start correct processes to get in lock */
		status = SC_ProcStartCommand(state, SC_RA_RAM_PROC_LOCKTRACK, SC_RA_RAM_SW_EVENT_RUN_NMASK__M, SC_RA_RAM_LOCKTRACK_MIN);
		अगर (status < 0)
			अवरोध;

		status = StartOC(state);
		अगर (status < 0)
			अवरोध;

		अगर (state->operation_mode != OM_Default) अणु
			status = StartDiversity(state);
			अगर (status < 0)
				अवरोध;
		पूर्ण

		state->drxd_state = DRXD_STARTED;
	पूर्ण जबतक (0);

	वापस status;
पूर्ण

अटल पूर्णांक CDRXD(काष्ठा drxd_state *state, u32 IntermediateFrequency)
अणु
	u32 ulRfAgcOutputLevel = 0xffffffff;
	u32 ulRfAgcSettleLevel = 528;	/* Optimum value क्रम MT2060 */
	u32 ulRfAgcMinLevel = 0;	/* Currently unused */
	u32 ulRfAgcMaxLevel = DRXD_FE_CTRL_MAX;	/* Currently unused */
	u32 ulRfAgcSpeed = 0;	/* Currently unused */
	u32 ulRfAgcMode = 0;	/*2;   Off */
	u32 ulRfAgcR1 = 820;
	u32 ulRfAgcR2 = 2200;
	u32 ulRfAgcR3 = 150;
	u32 ulIfAgcMode = 0;	/* Auto */
	u32 ulIfAgcOutputLevel = 0xffffffff;
	u32 ulIfAgcSettleLevel = 0xffffffff;
	u32 ulIfAgcMinLevel = 0xffffffff;
	u32 ulIfAgcMaxLevel = 0xffffffff;
	u32 ulIfAgcSpeed = 0xffffffff;
	u32 ulIfAgcR1 = 820;
	u32 ulIfAgcR2 = 2200;
	u32 ulIfAgcR3 = 150;
	u32 ulClock = state->config.घड़ी;
	u32 ulSerialMode = 0;
	u32 ulEcOcRegOcModeLop = 4;	/* Dynamic DTO source */
	u32 ulHiI2cDelay = HI_I2C_DELAY;
	u32 ulHiI2cBridgeDelay = HI_I2C_BRIDGE_DELAY;
	u32 ulHiI2cPatch = 0;
	u32 ulEnvironment = APPENV_PORTABLE;
	u32 ulEnvironmentDiversity = APPENV_MOBILE;
	u32 ulIFFilter = IFFILTER_SAW;

	state->अगर_agc_cfg.ctrlMode = AGC_CTRL_AUTO;
	state->अगर_agc_cfg.outputLevel = 0;
	state->अगर_agc_cfg.settleLevel = 140;
	state->अगर_agc_cfg.minOutputLevel = 0;
	state->अगर_agc_cfg.maxOutputLevel = 1023;
	state->अगर_agc_cfg.speed = 904;

	अगर (ulIfAgcMode == 1 && ulIfAgcOutputLevel <= DRXD_FE_CTRL_MAX) अणु
		state->अगर_agc_cfg.ctrlMode = AGC_CTRL_USER;
		state->अगर_agc_cfg.outputLevel = (u16) (ulIfAgcOutputLevel);
	पूर्ण

	अगर (ulIfAgcMode == 0 &&
	    ulIfAgcSettleLevel <= DRXD_FE_CTRL_MAX &&
	    ulIfAgcMinLevel <= DRXD_FE_CTRL_MAX &&
	    ulIfAgcMaxLevel <= DRXD_FE_CTRL_MAX &&
	    ulIfAgcSpeed <= DRXD_FE_CTRL_MAX) अणु
		state->अगर_agc_cfg.ctrlMode = AGC_CTRL_AUTO;
		state->अगर_agc_cfg.settleLevel = (u16) (ulIfAgcSettleLevel);
		state->अगर_agc_cfg.minOutputLevel = (u16) (ulIfAgcMinLevel);
		state->अगर_agc_cfg.maxOutputLevel = (u16) (ulIfAgcMaxLevel);
		state->अगर_agc_cfg.speed = (u16) (ulIfAgcSpeed);
	पूर्ण

	state->अगर_agc_cfg.R1 = (u16) (ulIfAgcR1);
	state->अगर_agc_cfg.R2 = (u16) (ulIfAgcR2);
	state->अगर_agc_cfg.R3 = (u16) (ulIfAgcR3);

	state->rf_agc_cfg.R1 = (u16) (ulRfAgcR1);
	state->rf_agc_cfg.R2 = (u16) (ulRfAgcR2);
	state->rf_agc_cfg.R3 = (u16) (ulRfAgcR3);

	state->rf_agc_cfg.ctrlMode = AGC_CTRL_AUTO;
	/* rest of the RFAgcCfg काष्ठाure currently unused */
	अगर (ulRfAgcMode == 1 && ulRfAgcOutputLevel <= DRXD_FE_CTRL_MAX) अणु
		state->rf_agc_cfg.ctrlMode = AGC_CTRL_USER;
		state->rf_agc_cfg.outputLevel = (u16) (ulRfAgcOutputLevel);
	पूर्ण

	अगर (ulRfAgcMode == 0 &&
	    ulRfAgcSettleLevel <= DRXD_FE_CTRL_MAX &&
	    ulRfAgcMinLevel <= DRXD_FE_CTRL_MAX &&
	    ulRfAgcMaxLevel <= DRXD_FE_CTRL_MAX &&
	    ulRfAgcSpeed <= DRXD_FE_CTRL_MAX) अणु
		state->rf_agc_cfg.ctrlMode = AGC_CTRL_AUTO;
		state->rf_agc_cfg.settleLevel = (u16) (ulRfAgcSettleLevel);
		state->rf_agc_cfg.minOutputLevel = (u16) (ulRfAgcMinLevel);
		state->rf_agc_cfg.maxOutputLevel = (u16) (ulRfAgcMaxLevel);
		state->rf_agc_cfg.speed = (u16) (ulRfAgcSpeed);
	पूर्ण

	अगर (ulRfAgcMode == 2)
		state->rf_agc_cfg.ctrlMode = AGC_CTRL_OFF;

	अगर (ulEnvironment <= 2)
		state->app_env_शेष = (क्रमागत app_env)
		    (ulEnvironment);
	अगर (ulEnvironmentDiversity <= 2)
		state->app_env_भागersity = (क्रमागत app_env)
		    (ulEnvironmentDiversity);

	अगर (ulIFFilter == IFFILTER_DISCRETE) अणु
		/* discrete filter */
		state->noise_cal.cpOpt = 0;
		state->noise_cal.cpNexpOfs = 40;
		state->noise_cal.tdCal2k = -40;
		state->noise_cal.tdCal8k = -24;
	पूर्ण अन्यथा अणु
		/* SAW filter */
		state->noise_cal.cpOpt = 1;
		state->noise_cal.cpNexpOfs = 0;
		state->noise_cal.tdCal2k = -21;
		state->noise_cal.tdCal8k = -24;
	पूर्ण
	state->m_EcOcRegOcModeLop = (u16) (ulEcOcRegOcModeLop);

	state->chip_adr = (state->config.demod_address << 1) | 1;
	चयन (ulHiI2cPatch) अणु
	हाल 1:
		state->m_HiI2cPatch = DRXD_HiI2cPatch_1;
		अवरोध;
	हाल 3:
		state->m_HiI2cPatch = DRXD_HiI2cPatch_3;
		अवरोध;
	शेष:
		state->m_HiI2cPatch = शून्य;
	पूर्ण

	/* modअगरy tuner and घड़ी attributes */
	state->पूर्णांकermediate_freq = (u16) (IntermediateFrequency / 1000);
	/* expected प्रणाली घड़ी frequency in kHz */
	state->expected_sys_घड़ी_freq = 48000;
	/* real प्रणाली घड़ी frequency in kHz */
	state->sys_घड़ी_freq = 48000;
	state->osc_घड़ी_freq = (u16) ulClock;
	state->osc_घड़ी_deviation = 0;
	state->cscd_state = CSCD_INIT;
	state->drxd_state = DRXD_UNINITIALIZED;

	state->PGA = 0;
	state->type_A = 0;
	state->tuner_mirrors = 0;

	/* modअगरy MPEG output attributes */
	state->insert_rs_byte = state->config.insert_rs_byte;
	state->enable_parallel = (ulSerialMode != 1);

	/* Timing भाग, 250ns/Psys */
	/* Timing भाग, = ( delay (nano seconds) * sysclk (kHz) )/ 1000 */

	state->hi_cfg_timing_भाग = (u16) ((state->sys_घड़ी_freq / 1000) *
					  ulHiI2cDelay) / 1000;
	/* Bridge delay, uses oscilator घड़ी */
	/* Delay = ( delay (nano seconds) * oscclk (kHz) )/ 1000 */
	state->hi_cfg_bridge_delay = (u16) ((state->osc_घड़ी_freq / 1000) *
					    ulHiI2cBridgeDelay) / 1000;

	state->m_FeAgRegAgPwd = DRXD_DEF_AG_PWD_CONSUMER;
	/* state->m_FeAgRegAgPwd = DRXD_DEF_AG_PWD_PRO; */
	state->m_FeAgRegAgAgcSio = DRXD_DEF_AG_AGC_SIO;
	वापस 0;
पूर्ण

अटल पूर्णांक DRXD_init(काष्ठा drxd_state *state, स्थिर u8 *fw, u32 fw_size)
अणु
	पूर्णांक status = 0;
	u32 driverVersion;

	अगर (state->init_करोne)
		वापस 0;

	CDRXD(state, state->config.IF ? state->config.IF : 36000000);

	करो अणु
		state->operation_mode = OM_Default;

		status = SetDeviceTypeId(state);
		अगर (status < 0)
			अवरोध;

		/* Apply I2c address patch to B1 */
		अगर (!state->type_A && state->m_HiI2cPatch) अणु
			status = WriteTable(state, state->m_HiI2cPatch);
			अगर (status < 0)
				अवरोध;
		पूर्ण

		अगर (state->type_A) अणु
			/* HI firmware patch क्रम UIO पढ़ोout,
			   aव्योम clearing of result रेजिस्टर */
			status = Write16(state, 0x43012D, 0x047f, 0);
			अगर (status < 0)
				अवरोध;
		पूर्ण

		status = HI_ResetCommand(state);
		अगर (status < 0)
			अवरोध;

		status = StopAllProcessors(state);
		अगर (status < 0)
			अवरोध;
		status = InitCC(state);
		अगर (status < 0)
			अवरोध;

		state->osc_घड़ी_deviation = 0;

		अगर (state->config.osc_deviation)
			state->osc_घड़ी_deviation =
			    state->config.osc_deviation(state->priv, 0, 0);
		अणु
			/* Handle घड़ी deviation */
			s32 devB;
			s32 devA = (s32) (state->osc_घड़ी_deviation) *
			    (s32) (state->expected_sys_घड़ी_freq);
			/* deviation in kHz */
			s32 deviation = (devA / (1000000L));
			/* rounding, चिन्हित */
			अगर (devA > 0)
				devB = (2);
			अन्यथा
				devB = (-2);
			अगर ((devB * (devA % 1000000L) > 1000000L)) अणु
				/* add +1 or -1 */
				deviation += (devB / 2);
			पूर्ण

			state->sys_घड़ी_freq =
			    (u16) ((state->expected_sys_घड़ी_freq) +
				   deviation);
		पूर्ण
		status = InitHI(state);
		अगर (status < 0)
			अवरोध;
		status = InitAtomicRead(state);
		अगर (status < 0)
			अवरोध;

		status = EnableAndResetMB(state);
		अगर (status < 0)
			अवरोध;
		अगर (state->type_A) अणु
			status = ResetCEFR(state);
			अगर (status < 0)
				अवरोध;
		पूर्ण
		अगर (fw) अणु
			status = DownloadMicrocode(state, fw, fw_size);
			अगर (status < 0)
				अवरोध;
		पूर्ण अन्यथा अणु
			status = DownloadMicrocode(state, state->microcode, state->microcode_length);
			अगर (status < 0)
				अवरोध;
		पूर्ण

		अगर (state->PGA) अणु
			state->m_FeAgRegAgPwd = DRXD_DEF_AG_PWD_PRO;
			SetCfgPga(state, 0);	/* PGA = 0 dB */
		पूर्ण अन्यथा अणु
			state->m_FeAgRegAgPwd = DRXD_DEF_AG_PWD_CONSUMER;
		पूर्ण

		state->m_FeAgRegAgAgcSio = DRXD_DEF_AG_AGC_SIO;

		status = InitFE(state);
		अगर (status < 0)
			अवरोध;
		status = InitFT(state);
		अगर (status < 0)
			अवरोध;
		status = InitCP(state);
		अगर (status < 0)
			अवरोध;
		status = InitCE(state);
		अगर (status < 0)
			अवरोध;
		status = InitEQ(state);
		अगर (status < 0)
			अवरोध;
		status = InitEC(state);
		अगर (status < 0)
			अवरोध;
		status = InitSC(state);
		अगर (status < 0)
			अवरोध;

		status = SetCfgIfAgc(state, &state->अगर_agc_cfg);
		अगर (status < 0)
			अवरोध;
		status = SetCfgRfAgc(state, &state->rf_agc_cfg);
		अगर (status < 0)
			अवरोध;

		state->cscd_state = CSCD_INIT;
		status = Write16(state, SC_COMM_EXEC__A, SC_COMM_EXEC_CTL_STOP, 0);
		अगर (status < 0)
			अवरोध;
		status = Write16(state, LC_COMM_EXEC__A, SC_COMM_EXEC_CTL_STOP, 0);
		अगर (status < 0)
			अवरोध;

		driverVersion = (((VERSION_MAJOR / 10) << 4) +
				 (VERSION_MAJOR % 10)) << 24;
		driverVersion += (((VERSION_MINOR / 10) << 4) +
				  (VERSION_MINOR % 10)) << 16;
		driverVersion += ((VERSION_PATCH / 1000) << 12) +
		    ((VERSION_PATCH / 100) << 8) +
		    ((VERSION_PATCH / 10) << 4) + (VERSION_PATCH % 10);

		status = Write32(state, SC_RA_RAM_DRIVER_VERSION__AX, driverVersion, 0);
		अगर (status < 0)
			अवरोध;

		status = StopOC(state);
		अगर (status < 0)
			अवरोध;

		state->drxd_state = DRXD_STOPPED;
		state->init_करोne = 1;
		status = 0;
	पूर्ण जबतक (0);
	वापस status;
पूर्ण

अटल पूर्णांक DRXD_status(काष्ठा drxd_state *state, u32 *pLockStatus)
अणु
	DRX_GetLockStatus(state, pLockStatus);

	/*अगर (*pLockStatus&DRX_LOCK_MPEG) */
	अगर (*pLockStatus & DRX_LOCK_FEC) अणु
		ConfigureMPEGOutput(state, 1);
		/* Get status again, in हाल we have MPEG lock now */
		/*DRX_GetLockStatus(state, pLockStatus); */
	पूर्ण

	वापस 0;
पूर्ण

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

अटल पूर्णांक drxd_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe, u16 * strength)
अणु
	काष्ठा drxd_state *state = fe->demodulator_priv;
	u32 value;
	पूर्णांक res;

	res = ReadIFAgc(state, &value);
	अगर (res < 0)
		*strength = 0;
	अन्यथा
		*strength = 0xffff - (value << 4);
	वापस 0;
पूर्ण

अटल पूर्णांक drxd_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा drxd_state *state = fe->demodulator_priv;
	u32 lock;

	DRXD_status(state, &lock);
	*status = 0;
	/* No MPEG lock in V255 firmware, bug ? */
#अगर 1
	अगर (lock & DRX_LOCK_MPEG)
		*status |= FE_HAS_LOCK;
#अन्यथा
	अगर (lock & DRX_LOCK_FEC)
		*status |= FE_HAS_LOCK;
#पूर्ण_अगर
	अगर (lock & DRX_LOCK_FEC)
		*status |= FE_HAS_VITERBI | FE_HAS_SYNC;
	अगर (lock & DRX_LOCK_DEMOD)
		*status |= FE_HAS_CARRIER | FE_HAS_SIGNAL;

	वापस 0;
पूर्ण

अटल पूर्णांक drxd_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा drxd_state *state = fe->demodulator_priv;

	वापस DRXD_init(state, शून्य, 0);
पूर्ण

अटल पूर्णांक drxd_config_i2c(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा drxd_state *state = fe->demodulator_priv;

	अगर (state->config.disable_i2c_gate_ctrl == 1)
		वापस 0;

	वापस DRX_ConfigureI2CBridge(state, onoff);
पूर्ण

अटल पूर्णांक drxd_get_tune_settings(काष्ठा dvb_frontend *fe,
				  काष्ठा dvb_frontend_tune_settings *sets)
अणु
	sets->min_delay_ms = 10000;
	sets->max_drअगरt = 0;
	sets->step_size = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक drxd_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 * ber)
अणु
	*ber = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक drxd_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 * snr)
अणु
	*snr = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक drxd_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 * ucblocks)
अणु
	*ucblocks = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक drxd_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा drxd_state *state = fe->demodulator_priv;

	ConfigureMPEGOutput(state, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक drxd_i2c_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	वापस drxd_config_i2c(fe, enable);
पूर्ण

अटल पूर्णांक drxd_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा drxd_state *state = fe->demodulator_priv;
	s32 off = 0;

	state->props = *p;
	DRX_Stop(state);

	अगर (fe->ops.tuner_ops.set_params) अणु
		fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	msleep(200);

	वापस DRX_Start(state, off);
पूर्ण

अटल व्योम drxd_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा drxd_state *state = fe->demodulator_priv;

	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops drxd_ops = अणु
	.delsys = अणु SYS_DVBTपूर्ण,
	.info = अणु
		 .name = "Micronas DRXD DVB-T",
		 .frequency_min_hz =  47125 * kHz,
		 .frequency_max_hz = 855250 * kHz,
		 .frequency_stepsize_hz = 166667,
		 .caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 |
		 FE_CAN_FEC_3_4 | FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 |
		 FE_CAN_FEC_AUTO |
		 FE_CAN_QAM_16 | FE_CAN_QAM_64 |
		 FE_CAN_QAM_AUTO |
		 FE_CAN_TRANSMISSION_MODE_AUTO |
		 FE_CAN_GUARD_INTERVAL_AUTO |
		 FE_CAN_HIERARCHY_AUTO | FE_CAN_RECOVER | FE_CAN_MUTE_TSपूर्ण,

	.release = drxd_release,
	.init = drxd_init,
	.sleep = drxd_sleep,
	.i2c_gate_ctrl = drxd_i2c_gate_ctrl,

	.set_frontend = drxd_set_frontend,
	.get_tune_settings = drxd_get_tune_settings,

	.पढ़ो_status = drxd_पढ़ो_status,
	.पढ़ो_ber = drxd_पढ़ो_ber,
	.पढ़ो_संकेत_strength = drxd_पढ़ो_संकेत_strength,
	.पढ़ो_snr = drxd_पढ़ो_snr,
	.पढ़ो_ucblocks = drxd_पढ़ो_ucblocks,
पूर्ण;

काष्ठा dvb_frontend *drxd_attach(स्थिर काष्ठा drxd_config *config,
				 व्योम *priv, काष्ठा i2c_adapter *i2c,
				 काष्ठा device *dev)
अणु
	काष्ठा drxd_state *state = शून्य;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	state->ops = drxd_ops;
	state->dev = dev;
	state->config = *config;
	state->i2c = i2c;
	state->priv = priv;

	mutex_init(&state->mutex);

	अगर (Read16(state, 0, शून्य, 0) < 0)
		जाओ error;

	state->frontend.ops = drxd_ops;
	state->frontend.demodulator_priv = state;
	ConfigureMPEGOutput(state, 0);
	/* add few initialization to allow gate control */
	CDRXD(state, state->config.IF ? state->config.IF : 36000000);
	InitHI(state);

	वापस &state->frontend;

error:
	prपूर्णांकk(KERN_ERR "drxd: not found\n");
	kमुक्त(state);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(drxd_attach);

MODULE_DESCRIPTION("DRXD driver");
MODULE_AUTHOR("Micronas");
MODULE_LICENSE("GPL");
