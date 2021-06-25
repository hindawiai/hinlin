<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drxk_hard: DRX-K DVB-C/T demodulator driver
 *
 * Copyright (C) 2010-2011 Digital Devices GmbH
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hardirq.h>
#समावेश <यंत्र/भाग64.h>

#समावेश <media/dvb_frontend.h>
#समावेश "drxk.h"
#समावेश "drxk_hard.h"
#समावेश <media/dvb_गणित.स>

अटल पूर्णांक घातer_करोwn_dvbt(काष्ठा drxk_state *state, bool set_घातer_mode);
अटल पूर्णांक घातer_करोwn_qam(काष्ठा drxk_state *state);
अटल पूर्णांक set_dvbt_standard(काष्ठा drxk_state *state,
			   क्रमागत operation_mode o_mode);
अटल पूर्णांक set_qam_standard(काष्ठा drxk_state *state,
			  क्रमागत operation_mode o_mode);
अटल पूर्णांक set_qam(काष्ठा drxk_state *state, u16 पूर्णांकermediate_freqk_hz,
		  s32 tuner_freq_offset);
अटल पूर्णांक set_dvbt_standard(काष्ठा drxk_state *state,
			   क्रमागत operation_mode o_mode);
अटल पूर्णांक dvbt_start(काष्ठा drxk_state *state);
अटल पूर्णांक set_dvbt(काष्ठा drxk_state *state, u16 पूर्णांकermediate_freqk_hz,
		   s32 tuner_freq_offset);
अटल पूर्णांक get_qam_lock_status(काष्ठा drxk_state *state, u32 *p_lock_status);
अटल पूर्णांक get_dvbt_lock_status(काष्ठा drxk_state *state, u32 *p_lock_status);
अटल पूर्णांक चयन_antenna_to_qam(काष्ठा drxk_state *state);
अटल पूर्णांक चयन_antenna_to_dvbt(काष्ठा drxk_state *state);

अटल bool is_dvbt(काष्ठा drxk_state *state)
अणु
	वापस state->m_operation_mode == OM_DVBT;
पूर्ण

अटल bool is_qam(काष्ठा drxk_state *state)
अणु
	वापस state->m_operation_mode == OM_QAM_ITU_A ||
	    state->m_operation_mode == OM_QAM_ITU_B ||
	    state->m_operation_mode == OM_QAM_ITU_C;
पूर्ण

#घोषणा NOA1ROM 0

#घोषणा DRXDAP_FASI_SHORT_FORMAT(addr) (((addr) & 0xFC30FF80) == 0)
#घोषणा DRXDAP_FASI_LONG_FORMAT(addr)  (((addr) & 0xFC30FF80) != 0)

#घोषणा DEFAULT_MER_83  165
#घोषणा DEFAULT_MER_93  250

#अगर_अघोषित DRXK_MPEG_SERIAL_OUTPUT_PIN_DRIVE_STRENGTH
#घोषणा DRXK_MPEG_SERIAL_OUTPUT_PIN_DRIVE_STRENGTH (0x02)
#पूर्ण_अगर

#अगर_अघोषित DRXK_MPEG_PARALLEL_OUTPUT_PIN_DRIVE_STRENGTH
#घोषणा DRXK_MPEG_PARALLEL_OUTPUT_PIN_DRIVE_STRENGTH (0x03)
#पूर्ण_अगर

#घोषणा DEFAULT_DRXK_MPEG_LOCK_TIMEOUT 700
#घोषणा DEFAULT_DRXK_DEMOD_LOCK_TIMEOUT 500

#अगर_अघोषित DRXK_KI_RAGC_ATV
#घोषणा DRXK_KI_RAGC_ATV   4
#पूर्ण_अगर
#अगर_अघोषित DRXK_KI_IAGC_ATV
#घोषणा DRXK_KI_IAGC_ATV   6
#पूर्ण_अगर
#अगर_अघोषित DRXK_KI_DAGC_ATV
#घोषणा DRXK_KI_DAGC_ATV   7
#पूर्ण_अगर

#अगर_अघोषित DRXK_KI_RAGC_QAM
#घोषणा DRXK_KI_RAGC_QAM   3
#पूर्ण_अगर
#अगर_अघोषित DRXK_KI_IAGC_QAM
#घोषणा DRXK_KI_IAGC_QAM   4
#पूर्ण_अगर
#अगर_अघोषित DRXK_KI_DAGC_QAM
#घोषणा DRXK_KI_DAGC_QAM   7
#पूर्ण_अगर
#अगर_अघोषित DRXK_KI_RAGC_DVBT
#घोषणा DRXK_KI_RAGC_DVBT  (IsA1WithPatchCode(state) ? 3 : 2)
#पूर्ण_अगर
#अगर_अघोषित DRXK_KI_IAGC_DVBT
#घोषणा DRXK_KI_IAGC_DVBT  (IsA1WithPatchCode(state) ? 4 : 2)
#पूर्ण_अगर
#अगर_अघोषित DRXK_KI_DAGC_DVBT
#घोषणा DRXK_KI_DAGC_DVBT  (IsA1WithPatchCode(state) ? 10 : 7)
#पूर्ण_अगर

#अगर_अघोषित DRXK_AGC_DAC_OFFSET
#घोषणा DRXK_AGC_DAC_OFFSET (0x800)
#पूर्ण_अगर

#अगर_अघोषित DRXK_BANDWIDTH_8MHZ_IN_HZ
#घोषणा DRXK_BANDWIDTH_8MHZ_IN_HZ  (0x8B8249L)
#पूर्ण_अगर

#अगर_अघोषित DRXK_BANDWIDTH_7MHZ_IN_HZ
#घोषणा DRXK_BANDWIDTH_7MHZ_IN_HZ  (0x7A1200L)
#पूर्ण_अगर

#अगर_अघोषित DRXK_BANDWIDTH_6MHZ_IN_HZ
#घोषणा DRXK_BANDWIDTH_6MHZ_IN_HZ  (0x68A1B6L)
#पूर्ण_अगर

#अगर_अघोषित DRXK_QAM_SYMBOLRATE_MAX
#घोषणा DRXK_QAM_SYMBOLRATE_MAX         (7233000)
#पूर्ण_अगर

#घोषणा DRXK_BL_ROM_OFFSET_TAPS_DVBT    56
#घोषणा DRXK_BL_ROM_OFFSET_TAPS_ITU_A   64
#घोषणा DRXK_BL_ROM_OFFSET_TAPS_ITU_C   0x5FE0
#घोषणा DRXK_BL_ROM_OFFSET_TAPS_BG      24
#घोषणा DRXK_BL_ROM_OFFSET_TAPS_DKILLP  32
#घोषणा DRXK_BL_ROM_OFFSET_TAPS_NTSC    40
#घोषणा DRXK_BL_ROM_OFFSET_TAPS_FM      48
#घोषणा DRXK_BL_ROM_OFFSET_UCODE        0

#घोषणा DRXK_BLC_TIMEOUT                100

#घोषणा DRXK_BLCC_NR_ELEMENTS_TAPS      2
#घोषणा DRXK_BLCC_NR_ELEMENTS_UCODE     6

#घोषणा DRXK_BLDC_NR_ELEMENTS_TAPS      28

#अगर_अघोषित DRXK_OFDM_NE_NOTCH_WIDTH
#घोषणा DRXK_OFDM_NE_NOTCH_WIDTH             (4)
#पूर्ण_अगर

#घोषणा DRXK_QAM_SL_SIG_POWER_QAM16       (40960)
#घोषणा DRXK_QAM_SL_SIG_POWER_QAM32       (20480)
#घोषणा DRXK_QAM_SL_SIG_POWER_QAM64       (43008)
#घोषणा DRXK_QAM_SL_SIG_POWER_QAM128      (20992)
#घोषणा DRXK_QAM_SL_SIG_POWER_QAM256      (43520)

अटल अचिन्हित पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "enable debug messages");

#घोषणा dprपूर्णांकk(level, fmt, arg...) करो अणु				\
अगर (debug >= level)							\
	prपूर्णांकk(KERN_DEBUG KBUILD_MODNAME ": %s " fmt, __func__, ##arg);	\
पूर्ण जबतक (0)

अटल अंतरभूत u32 Frac28a(u32 a, u32 c)
अणु
	पूर्णांक i = 0;
	u32 Q1 = 0;
	u32 R0 = 0;

	R0 = (a % c) << 4;	/* 32-28 == 4 shअगरts possible at max */
	Q1 = a / c;		/*
				 * पूर्णांकeger part, only the 4 least signअगरicant
				 * bits will be visible in the result
				 */

	/* भागision using radix 16, 7 nibbles in the result */
	क्रम (i = 0; i < 7; i++) अणु
		Q1 = (Q1 << 4) | (R0 / c);
		R0 = (R0 % c) << 4;
	पूर्ण
	/* rounding */
	अगर ((R0 >> 3) >= c)
		Q1++;

	वापस Q1;
पूर्ण

अटल अंतरभूत u32 log10बार100(u32 value)
अणु
	वापस (100L * पूर्णांकlog10(value)) >> 24;
पूर्ण

/***************************************************************************/
/* I2C **********************************************************************/
/***************************************************************************/

अटल पूर्णांक drxk_i2c_lock(काष्ठा drxk_state *state)
अणु
	i2c_lock_bus(state->i2c, I2C_LOCK_SEGMENT);
	state->drxk_i2c_exclusive_lock = true;

	वापस 0;
पूर्ण

अटल व्योम drxk_i2c_unlock(काष्ठा drxk_state *state)
अणु
	अगर (!state->drxk_i2c_exclusive_lock)
		वापस;

	i2c_unlock_bus(state->i2c, I2C_LOCK_SEGMENT);
	state->drxk_i2c_exclusive_lock = false;
पूर्ण

अटल पूर्णांक drxk_i2c_transfer(काष्ठा drxk_state *state, काष्ठा i2c_msg *msgs,
			     अचिन्हित len)
अणु
	अगर (state->drxk_i2c_exclusive_lock)
		वापस __i2c_transfer(state->i2c, msgs, len);
	अन्यथा
		वापस i2c_transfer(state->i2c, msgs, len);
पूर्ण

अटल पूर्णांक i2c_पढ़ो1(काष्ठा drxk_state *state, u8 adr, u8 *val)
अणु
	काष्ठा i2c_msg msgs[1] = अणु अणु.addr = adr, .flags = I2C_M_RD,
				    .buf = val, .len = 1पूर्ण
	पूर्ण;

	वापस drxk_i2c_transfer(state, msgs, 1);
पूर्ण

अटल पूर्णांक i2c_ग_लिखो(काष्ठा drxk_state *state, u8 adr, u8 *data, पूर्णांक len)
अणु
	पूर्णांक status;
	काष्ठा i2c_msg msg = अणु
	    .addr = adr, .flags = 0, .buf = data, .len = len पूर्ण;

	dprपूर्णांकk(3, ":");
	अगर (debug > 2) अणु
		पूर्णांक i;
		क्रम (i = 0; i < len; i++)
			pr_cont(" %02x", data[i]);
		pr_cont("\n");
	पूर्ण
	status = drxk_i2c_transfer(state, &msg, 1);
	अगर (status >= 0 && status != 1)
		status = -EIO;

	अगर (status < 0)
		pr_err("i2c write error at addr 0x%02x\n", adr);

	वापस status;
पूर्ण

अटल पूर्णांक i2c_पढ़ो(काष्ठा drxk_state *state,
		    u8 adr, u8 *msg, पूर्णांक len, u8 *answ, पूर्णांक alen)
अणु
	पूर्णांक status;
	काष्ठा i2c_msg msgs[2] = अणु
		अणु.addr = adr, .flags = 0,
				    .buf = msg, .len = lenपूर्ण,
		अणु.addr = adr, .flags = I2C_M_RD,
		 .buf = answ, .len = alenपूर्ण
	पूर्ण;

	status = drxk_i2c_transfer(state, msgs, 2);
	अगर (status != 2) अणु
		अगर (debug > 2)
			pr_cont(": ERROR!\n");
		अगर (status >= 0)
			status = -EIO;

		pr_err("i2c read error at addr 0x%02x\n", adr);
		वापस status;
	पूर्ण
	अगर (debug > 2) अणु
		पूर्णांक i;
		dprपूर्णांकk(2, ": read from");
		क्रम (i = 0; i < len; i++)
			pr_cont(" %02x", msg[i]);
		pr_cont(", value = ");
		क्रम (i = 0; i < alen; i++)
			pr_cont(" %02x", answ[i]);
		pr_cont("\n");
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो16_flags(काष्ठा drxk_state *state, u32 reg, u16 *data, u8 flags)
अणु
	पूर्णांक status;
	u8 adr = state->demod_address, mm1[4], mm2[2], len;

	अगर (state->single_master)
		flags |= 0xC0;

	अगर (DRXDAP_FASI_LONG_FORMAT(reg) || (flags != 0)) अणु
		mm1[0] = (((reg << 1) & 0xFF) | 0x01);
		mm1[1] = ((reg >> 16) & 0xFF);
		mm1[2] = ((reg >> 24) & 0xFF) | flags;
		mm1[3] = ((reg >> 7) & 0xFF);
		len = 4;
	पूर्ण अन्यथा अणु
		mm1[0] = ((reg << 1) & 0xFF);
		mm1[1] = (((reg >> 16) & 0x0F) | ((reg >> 18) & 0xF0));
		len = 2;
	पूर्ण
	dprपूर्णांकk(2, "(0x%08x, 0x%02x)\n", reg, flags);
	status = i2c_पढ़ो(state, adr, mm1, len, mm2, 2);
	अगर (status < 0)
		वापस status;
	अगर (data)
		*data = mm2[0] | (mm2[1] << 8);

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो16(काष्ठा drxk_state *state, u32 reg, u16 *data)
अणु
	वापस पढ़ो16_flags(state, reg, data, 0);
पूर्ण

अटल पूर्णांक पढ़ो32_flags(काष्ठा drxk_state *state, u32 reg, u32 *data, u8 flags)
अणु
	पूर्णांक status;
	u8 adr = state->demod_address, mm1[4], mm2[4], len;

	अगर (state->single_master)
		flags |= 0xC0;

	अगर (DRXDAP_FASI_LONG_FORMAT(reg) || (flags != 0)) अणु
		mm1[0] = (((reg << 1) & 0xFF) | 0x01);
		mm1[1] = ((reg >> 16) & 0xFF);
		mm1[2] = ((reg >> 24) & 0xFF) | flags;
		mm1[3] = ((reg >> 7) & 0xFF);
		len = 4;
	पूर्ण अन्यथा अणु
		mm1[0] = ((reg << 1) & 0xFF);
		mm1[1] = (((reg >> 16) & 0x0F) | ((reg >> 18) & 0xF0));
		len = 2;
	पूर्ण
	dprपूर्णांकk(2, "(0x%08x, 0x%02x)\n", reg, flags);
	status = i2c_पढ़ो(state, adr, mm1, len, mm2, 4);
	अगर (status < 0)
		वापस status;
	अगर (data)
		*data = mm2[0] | (mm2[1] << 8) |
		    (mm2[2] << 16) | (mm2[3] << 24);

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो32(काष्ठा drxk_state *state, u32 reg, u32 *data)
अणु
	वापस पढ़ो32_flags(state, reg, data, 0);
पूर्ण

अटल पूर्णांक ग_लिखो16_flags(काष्ठा drxk_state *state, u32 reg, u16 data, u8 flags)
अणु
	u8 adr = state->demod_address, mm[6], len;

	अगर (state->single_master)
		flags |= 0xC0;
	अगर (DRXDAP_FASI_LONG_FORMAT(reg) || (flags != 0)) अणु
		mm[0] = (((reg << 1) & 0xFF) | 0x01);
		mm[1] = ((reg >> 16) & 0xFF);
		mm[2] = ((reg >> 24) & 0xFF) | flags;
		mm[3] = ((reg >> 7) & 0xFF);
		len = 4;
	पूर्ण अन्यथा अणु
		mm[0] = ((reg << 1) & 0xFF);
		mm[1] = (((reg >> 16) & 0x0F) | ((reg >> 18) & 0xF0));
		len = 2;
	पूर्ण
	mm[len] = data & 0xff;
	mm[len + 1] = (data >> 8) & 0xff;

	dprपूर्णांकk(2, "(0x%08x, 0x%04x, 0x%02x)\n", reg, data, flags);
	वापस i2c_ग_लिखो(state, adr, mm, len + 2);
पूर्ण

अटल पूर्णांक ग_लिखो16(काष्ठा drxk_state *state, u32 reg, u16 data)
अणु
	वापस ग_लिखो16_flags(state, reg, data, 0);
पूर्ण

अटल पूर्णांक ग_लिखो32_flags(काष्ठा drxk_state *state, u32 reg, u32 data, u8 flags)
अणु
	u8 adr = state->demod_address, mm[8], len;

	अगर (state->single_master)
		flags |= 0xC0;
	अगर (DRXDAP_FASI_LONG_FORMAT(reg) || (flags != 0)) अणु
		mm[0] = (((reg << 1) & 0xFF) | 0x01);
		mm[1] = ((reg >> 16) & 0xFF);
		mm[2] = ((reg >> 24) & 0xFF) | flags;
		mm[3] = ((reg >> 7) & 0xFF);
		len = 4;
	पूर्ण अन्यथा अणु
		mm[0] = ((reg << 1) & 0xFF);
		mm[1] = (((reg >> 16) & 0x0F) | ((reg >> 18) & 0xF0));
		len = 2;
	पूर्ण
	mm[len] = data & 0xff;
	mm[len + 1] = (data >> 8) & 0xff;
	mm[len + 2] = (data >> 16) & 0xff;
	mm[len + 3] = (data >> 24) & 0xff;
	dprपूर्णांकk(2, "(0x%08x, 0x%08x, 0x%02x)\n", reg, data, flags);

	वापस i2c_ग_लिखो(state, adr, mm, len + 4);
पूर्ण

अटल पूर्णांक ग_लिखो32(काष्ठा drxk_state *state, u32 reg, u32 data)
अणु
	वापस ग_लिखो32_flags(state, reg, data, 0);
पूर्ण

अटल पूर्णांक ग_लिखो_block(काष्ठा drxk_state *state, u32 address,
		      स्थिर पूर्णांक block_size, स्थिर u8 p_block[])
अणु
	पूर्णांक status = 0, blk_size = block_size;
	u8 flags = 0;

	अगर (state->single_master)
		flags |= 0xC0;

	जबतक (blk_size > 0) अणु
		पूर्णांक chunk = blk_size > state->m_chunk_size ?
		    state->m_chunk_size : blk_size;
		u8 *adr_buf = &state->chunk[0];
		u32 adr_length = 0;

		अगर (DRXDAP_FASI_LONG_FORMAT(address) || (flags != 0)) अणु
			adr_buf[0] = (((address << 1) & 0xFF) | 0x01);
			adr_buf[1] = ((address >> 16) & 0xFF);
			adr_buf[2] = ((address >> 24) & 0xFF);
			adr_buf[3] = ((address >> 7) & 0xFF);
			adr_buf[2] |= flags;
			adr_length = 4;
			अगर (chunk == state->m_chunk_size)
				chunk -= 2;
		पूर्ण अन्यथा अणु
			adr_buf[0] = ((address << 1) & 0xFF);
			adr_buf[1] = (((address >> 16) & 0x0F) |
				     ((address >> 18) & 0xF0));
			adr_length = 2;
		पूर्ण
		स_नकल(&state->chunk[adr_length], p_block, chunk);
		dprपूर्णांकk(2, "(0x%08x, 0x%02x)\n", address, flags);
		अगर (debug > 1) अणु
			पूर्णांक i;
			अगर (p_block)
				क्रम (i = 0; i < chunk; i++)
					pr_cont(" %02x", p_block[i]);
			pr_cont("\n");
		पूर्ण
		status = i2c_ग_लिखो(state, state->demod_address,
				   &state->chunk[0], chunk + adr_length);
		अगर (status < 0) अणु
			pr_err("%s: i2c write error at addr 0x%02x\n",
			       __func__, address);
			अवरोध;
		पूर्ण
		p_block += chunk;
		address += (chunk >> 1);
		blk_size -= chunk;
	पूर्ण
	वापस status;
पूर्ण

#अगर_अघोषित DRXK_MAX_RETRIES_POWERUP
#घोषणा DRXK_MAX_RETRIES_POWERUP 20
#पूर्ण_अगर

अटल पूर्णांक घातer_up_device(काष्ठा drxk_state *state)
अणु
	पूर्णांक status;
	u8 data = 0;
	u16 retry_count = 0;

	dprपूर्णांकk(1, "\n");

	status = i2c_पढ़ो1(state, state->demod_address, &data);
	अगर (status < 0) अणु
		करो अणु
			data = 0;
			status = i2c_ग_लिखो(state, state->demod_address,
					   &data, 1);
			usleep_range(10000, 11000);
			retry_count++;
			अगर (status < 0)
				जारी;
			status = i2c_पढ़ो1(state, state->demod_address,
					   &data);
		पूर्ण जबतक (status < 0 &&
			 (retry_count < DRXK_MAX_RETRIES_POWERUP));
		अगर (status < 0 && retry_count >= DRXK_MAX_RETRIES_POWERUP)
			जाओ error;
	पूर्ण

	/* Make sure all clk करोमुख्यs are active */
	status = ग_लिखो16(state, SIO_CC_PWD_MODE__A, SIO_CC_PWD_MODE_LEVEL_NONE);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SIO_CC_UPDATE__A, SIO_CC_UPDATE_KEY);
	अगर (status < 0)
		जाओ error;
	/* Enable pll lock tests */
	status = ग_लिखो16(state, SIO_CC_PLL_LOCK__A, 1);
	अगर (status < 0)
		जाओ error;

	state->m_current_घातer_mode = DRX_POWER_UP;

error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);

	वापस status;
पूर्ण


अटल पूर्णांक init_state(काष्ठा drxk_state *state)
अणु
	/*
	 * FIXME: most (all?) of the values below should be moved पूर्णांकo
	 * काष्ठा drxk_config, as they are probably board-specअगरic
	 */
	u32 ul_vsb_अगर_agc_mode = DRXK_AGC_CTRL_AUTO;
	u32 ul_vsb_अगर_agc_output_level = 0;
	u32 ul_vsb_अगर_agc_min_level = 0;
	u32 ul_vsb_अगर_agc_max_level = 0x7FFF;
	u32 ul_vsb_अगर_agc_speed = 3;

	u32 ul_vsb_rf_agc_mode = DRXK_AGC_CTRL_AUTO;
	u32 ul_vsb_rf_agc_output_level = 0;
	u32 ul_vsb_rf_agc_min_level = 0;
	u32 ul_vsb_rf_agc_max_level = 0x7FFF;
	u32 ul_vsb_rf_agc_speed = 3;
	u32 ul_vsb_rf_agc_top = 9500;
	u32 ul_vsb_rf_agc_cut_off_current = 4000;

	u32 ul_atv_अगर_agc_mode = DRXK_AGC_CTRL_AUTO;
	u32 ul_atv_अगर_agc_output_level = 0;
	u32 ul_atv_अगर_agc_min_level = 0;
	u32 ul_atv_अगर_agc_max_level = 0;
	u32 ul_atv_अगर_agc_speed = 3;

	u32 ul_atv_rf_agc_mode = DRXK_AGC_CTRL_OFF;
	u32 ul_atv_rf_agc_output_level = 0;
	u32 ul_atv_rf_agc_min_level = 0;
	u32 ul_atv_rf_agc_max_level = 0;
	u32 ul_atv_rf_agc_top = 9500;
	u32 ul_atv_rf_agc_cut_off_current = 4000;
	u32 ul_atv_rf_agc_speed = 3;

	u32 ulQual83 = DEFAULT_MER_83;
	u32 ulQual93 = DEFAULT_MER_93;

	u32 ul_mpeg_lock_समय_out = DEFAULT_DRXK_MPEG_LOCK_TIMEOUT;
	u32 ul_demod_lock_समय_out = DEFAULT_DRXK_DEMOD_LOCK_TIMEOUT;

	/* io_pad_cfg रेजिस्टर (8 bit reg.) MSB bit is 1 (शेष value) */
	/* io_pad_cfg_mode output mode is drive always */
	/* io_pad_cfg_drive is set to घातer 2 (23 mA) */
	u32 ul_gpio_cfg = 0x0113;
	u32 ul_invert_ts_घड़ी = 0;
	u32 ul_ts_data_strength = DRXK_MPEG_SERIAL_OUTPUT_PIN_DRIVE_STRENGTH;
	u32 ul_dvbt_bitrate = 50000000;
	u32 ul_dvbc_bitrate = DRXK_QAM_SYMBOLRATE_MAX * 8;

	u32 ul_insert_rs_byte = 0;

	u32 ul_rf_mirror = 1;
	u32 ul_घातer_करोwn = 0;

	dprपूर्णांकk(1, "\n");

	state->m_has_lna = false;
	state->m_has_dvbt = false;
	state->m_has_dvbc = false;
	state->m_has_atv = false;
	state->m_has_oob = false;
	state->m_has_audio = false;

	अगर (!state->m_chunk_size)
		state->m_chunk_size = 124;

	state->m_osc_घड़ी_freq = 0;
	state->m_smart_ant_inverted = false;
	state->m_b_p_करोwn_खोलो_bridge = false;

	/* real प्रणाली घड़ी frequency in kHz */
	state->m_sys_घड़ी_freq = 151875;
	/* Timing भाग, 250ns/Psys */
	/* Timing भाग, = (delay (nano seconds) * sysclk (kHz))/ 1000 */
	state->m_hi_cfg_timing_भाग = ((state->m_sys_घड़ी_freq / 1000) *
				   HI_I2C_DELAY) / 1000;
	/* Clipping */
	अगर (state->m_hi_cfg_timing_भाग > SIO_HI_RA_RAM_PAR_2_CFG_DIV__M)
		state->m_hi_cfg_timing_भाग = SIO_HI_RA_RAM_PAR_2_CFG_DIV__M;
	state->m_hi_cfg_wake_up_key = (state->demod_address << 1);
	/* port/bridge/घातer करोwn ctrl */
	state->m_hi_cfg_ctrl = SIO_HI_RA_RAM_PAR_5_CFG_SLV0_SLAVE;

	state->m_b_घातer_करोwn = (ul_घातer_करोwn != 0);

	state->m_drxk_a3_patch_code = false;

	/* Init AGC and PGA parameters */
	/* VSB IF */
	state->m_vsb_अगर_agc_cfg.ctrl_mode = ul_vsb_अगर_agc_mode;
	state->m_vsb_अगर_agc_cfg.output_level = ul_vsb_अगर_agc_output_level;
	state->m_vsb_अगर_agc_cfg.min_output_level = ul_vsb_अगर_agc_min_level;
	state->m_vsb_अगर_agc_cfg.max_output_level = ul_vsb_अगर_agc_max_level;
	state->m_vsb_अगर_agc_cfg.speed = ul_vsb_अगर_agc_speed;
	state->m_vsb_pga_cfg = 140;

	/* VSB RF */
	state->m_vsb_rf_agc_cfg.ctrl_mode = ul_vsb_rf_agc_mode;
	state->m_vsb_rf_agc_cfg.output_level = ul_vsb_rf_agc_output_level;
	state->m_vsb_rf_agc_cfg.min_output_level = ul_vsb_rf_agc_min_level;
	state->m_vsb_rf_agc_cfg.max_output_level = ul_vsb_rf_agc_max_level;
	state->m_vsb_rf_agc_cfg.speed = ul_vsb_rf_agc_speed;
	state->m_vsb_rf_agc_cfg.top = ul_vsb_rf_agc_top;
	state->m_vsb_rf_agc_cfg.cut_off_current = ul_vsb_rf_agc_cut_off_current;
	state->m_vsb_pre_saw_cfg.reference = 0x07;
	state->m_vsb_pre_saw_cfg.use_pre_saw = true;

	state->m_Quality83percent = DEFAULT_MER_83;
	state->m_Quality93percent = DEFAULT_MER_93;
	अगर (ulQual93 <= 500 && ulQual83 < ulQual93) अणु
		state->m_Quality83percent = ulQual83;
		state->m_Quality93percent = ulQual93;
	पूर्ण

	/* ATV IF */
	state->m_atv_अगर_agc_cfg.ctrl_mode = ul_atv_अगर_agc_mode;
	state->m_atv_अगर_agc_cfg.output_level = ul_atv_अगर_agc_output_level;
	state->m_atv_अगर_agc_cfg.min_output_level = ul_atv_अगर_agc_min_level;
	state->m_atv_अगर_agc_cfg.max_output_level = ul_atv_अगर_agc_max_level;
	state->m_atv_अगर_agc_cfg.speed = ul_atv_अगर_agc_speed;

	/* ATV RF */
	state->m_atv_rf_agc_cfg.ctrl_mode = ul_atv_rf_agc_mode;
	state->m_atv_rf_agc_cfg.output_level = ul_atv_rf_agc_output_level;
	state->m_atv_rf_agc_cfg.min_output_level = ul_atv_rf_agc_min_level;
	state->m_atv_rf_agc_cfg.max_output_level = ul_atv_rf_agc_max_level;
	state->m_atv_rf_agc_cfg.speed = ul_atv_rf_agc_speed;
	state->m_atv_rf_agc_cfg.top = ul_atv_rf_agc_top;
	state->m_atv_rf_agc_cfg.cut_off_current = ul_atv_rf_agc_cut_off_current;
	state->m_atv_pre_saw_cfg.reference = 0x04;
	state->m_atv_pre_saw_cfg.use_pre_saw = true;


	/* DVBT RF */
	state->m_dvbt_rf_agc_cfg.ctrl_mode = DRXK_AGC_CTRL_OFF;
	state->m_dvbt_rf_agc_cfg.output_level = 0;
	state->m_dvbt_rf_agc_cfg.min_output_level = 0;
	state->m_dvbt_rf_agc_cfg.max_output_level = 0xFFFF;
	state->m_dvbt_rf_agc_cfg.top = 0x2100;
	state->m_dvbt_rf_agc_cfg.cut_off_current = 4000;
	state->m_dvbt_rf_agc_cfg.speed = 1;


	/* DVBT IF */
	state->m_dvbt_अगर_agc_cfg.ctrl_mode = DRXK_AGC_CTRL_AUTO;
	state->m_dvbt_अगर_agc_cfg.output_level = 0;
	state->m_dvbt_अगर_agc_cfg.min_output_level = 0;
	state->m_dvbt_अगर_agc_cfg.max_output_level = 9000;
	state->m_dvbt_अगर_agc_cfg.top = 13424;
	state->m_dvbt_अगर_agc_cfg.cut_off_current = 0;
	state->m_dvbt_अगर_agc_cfg.speed = 3;
	state->m_dvbt_अगर_agc_cfg.fast_clip_ctrl_delay = 30;
	state->m_dvbt_अगर_agc_cfg.ingain_tgt_max = 30000;
	/* state->m_dvbtPgaCfg = 140; */

	state->m_dvbt_pre_saw_cfg.reference = 4;
	state->m_dvbt_pre_saw_cfg.use_pre_saw = false;

	/* QAM RF */
	state->m_qam_rf_agc_cfg.ctrl_mode = DRXK_AGC_CTRL_OFF;
	state->m_qam_rf_agc_cfg.output_level = 0;
	state->m_qam_rf_agc_cfg.min_output_level = 6023;
	state->m_qam_rf_agc_cfg.max_output_level = 27000;
	state->m_qam_rf_agc_cfg.top = 0x2380;
	state->m_qam_rf_agc_cfg.cut_off_current = 4000;
	state->m_qam_rf_agc_cfg.speed = 3;

	/* QAM IF */
	state->m_qam_अगर_agc_cfg.ctrl_mode = DRXK_AGC_CTRL_AUTO;
	state->m_qam_अगर_agc_cfg.output_level = 0;
	state->m_qam_अगर_agc_cfg.min_output_level = 0;
	state->m_qam_अगर_agc_cfg.max_output_level = 9000;
	state->m_qam_अगर_agc_cfg.top = 0x0511;
	state->m_qam_अगर_agc_cfg.cut_off_current = 0;
	state->m_qam_अगर_agc_cfg.speed = 3;
	state->m_qam_अगर_agc_cfg.ingain_tgt_max = 5119;
	state->m_qam_अगर_agc_cfg.fast_clip_ctrl_delay = 50;

	state->m_qam_pga_cfg = 140;
	state->m_qam_pre_saw_cfg.reference = 4;
	state->m_qam_pre_saw_cfg.use_pre_saw = false;

	state->m_operation_mode = OM_NONE;
	state->m_drxk_state = DRXK_UNINITIALIZED;

	/* MPEG output configuration */
	state->m_enable_mpeg_output = true;	/* If TRUE; enable MPEG output */
	state->m_insert_rs_byte = false;	/* If TRUE; insert RS byte */
	state->m_invert_data = false;	/* If TRUE; invert DATA संकेतs */
	state->m_invert_err = false;	/* If TRUE; invert ERR संकेत */
	state->m_invert_str = false;	/* If TRUE; invert STR संकेतs */
	state->m_invert_val = false;	/* If TRUE; invert VAL संकेतs */
	state->m_invert_clk = (ul_invert_ts_घड़ी != 0);	/* If TRUE; invert CLK संकेतs */

	/* If TRUE; अटल MPEG घड़ीrate will be used;
	   otherwise घड़ीrate will adapt to the bitrate of the TS */

	state->m_dvbt_bitrate = ul_dvbt_bitrate;
	state->m_dvbc_bitrate = ul_dvbc_bitrate;

	state->m_ts_data_strength = (ul_ts_data_strength & 0x07);

	/* Maximum bitrate in b/s in हाल अटल घड़ीrate is selected */
	state->m_mpeg_ts_अटल_bitrate = 19392658;
	state->m_disable_te_ihandling = false;

	अगर (ul_insert_rs_byte)
		state->m_insert_rs_byte = true;

	state->m_mpeg_lock_समय_out = DEFAULT_DRXK_MPEG_LOCK_TIMEOUT;
	अगर (ul_mpeg_lock_समय_out < 10000)
		state->m_mpeg_lock_समय_out = ul_mpeg_lock_समय_out;
	state->m_demod_lock_समय_out = DEFAULT_DRXK_DEMOD_LOCK_TIMEOUT;
	अगर (ul_demod_lock_समय_out < 10000)
		state->m_demod_lock_समय_out = ul_demod_lock_समय_out;

	/* QAM शेषs */
	state->m_स्थिरellation = DRX_CONSTELLATION_AUTO;
	state->m_qam_पूर्णांकerleave_mode = DRXK_QAM_I12_J17;
	state->m_fec_rs_plen = 204 * 8;	/* fecRsPlen  annex A */
	state->m_fec_rs_prescale = 1;

	state->m_sqi_speed = DRXK_DVBT_SQI_SPEED_MEDIUM;
	state->m_agcfast_clip_ctrl_delay = 0;

	state->m_gpio_cfg = ul_gpio_cfg;

	state->m_b_घातer_करोwn = false;
	state->m_current_घातer_mode = DRX_POWER_DOWN;

	state->m_rfmirror = (ul_rf_mirror == 0);
	state->m_अगर_agc_pol = false;
	वापस 0;
पूर्ण

अटल पूर्णांक drxx_खोलो(काष्ठा drxk_state *state)
अणु
	पूर्णांक status = 0;
	u32 jtag = 0;
	u16 bid = 0;
	u16 key = 0;

	dprपूर्णांकk(1, "\n");
	/* stop lock indicator process */
	status = ग_लिखो16(state, SCU_RAM_GPIO__A,
			 SCU_RAM_GPIO_HW_LOCK_IND_DISABLE);
	अगर (status < 0)
		जाओ error;
	/* Check device id */
	status = पढ़ो16(state, SIO_TOP_COMM_KEY__A, &key);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SIO_TOP_COMM_KEY__A, SIO_TOP_COMM_KEY_KEY);
	अगर (status < 0)
		जाओ error;
	status = पढ़ो32(state, SIO_TOP_JTAGID_LO__A, &jtag);
	अगर (status < 0)
		जाओ error;
	status = पढ़ो16(state, SIO_PDR_UIO_IN_HI__A, &bid);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SIO_TOP_COMM_KEY__A, key);
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

अटल पूर्णांक get_device_capabilities(काष्ठा drxk_state *state)
अणु
	u16 sio_pdr_ohw_cfg = 0;
	u32 sio_top_jtagid_lo = 0;
	पूर्णांक status;
	स्थिर अक्षर *spin = "";

	dprपूर्णांकk(1, "\n");

	/* driver 0.9.0 */
	/* stop lock indicator process */
	status = ग_लिखो16(state, SCU_RAM_GPIO__A,
			 SCU_RAM_GPIO_HW_LOCK_IND_DISABLE);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SIO_TOP_COMM_KEY__A, SIO_TOP_COMM_KEY_KEY);
	अगर (status < 0)
		जाओ error;
	status = पढ़ो16(state, SIO_PDR_OHW_CFG__A, &sio_pdr_ohw_cfg);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SIO_TOP_COMM_KEY__A, 0x0000);
	अगर (status < 0)
		जाओ error;

	चयन ((sio_pdr_ohw_cfg & SIO_PDR_OHW_CFG_FREF_SEL__M)) अणु
	हाल 0:
		/* ignore (bypass ?) */
		अवरोध;
	हाल 1:
		/* 27 MHz */
		state->m_osc_घड़ी_freq = 27000;
		अवरोध;
	हाल 2:
		/* 20.25 MHz */
		state->m_osc_घड़ी_freq = 20250;
		अवरोध;
	हाल 3:
		/* 4 MHz */
		state->m_osc_घड़ी_freq = 20250;
		अवरोध;
	शेष:
		pr_err("Clock Frequency is unknown\n");
		वापस -EINVAL;
	पूर्ण
	/*
		Determine device capabilities
		Based on pinning v14
		*/
	status = पढ़ो32(state, SIO_TOP_JTAGID_LO__A, &sio_top_jtagid_lo);
	अगर (status < 0)
		जाओ error;

	pr_info("status = 0x%08x\n", sio_top_jtagid_lo);

	/* driver 0.9.0 */
	चयन ((sio_top_jtagid_lo >> 29) & 0xF) अणु
	हाल 0:
		state->m_device_spin = DRXK_SPIN_A1;
		spin = "A1";
		अवरोध;
	हाल 2:
		state->m_device_spin = DRXK_SPIN_A2;
		spin = "A2";
		अवरोध;
	हाल 3:
		state->m_device_spin = DRXK_SPIN_A3;
		spin = "A3";
		अवरोध;
	शेष:
		state->m_device_spin = DRXK_SPIN_UNKNOWN;
		status = -EINVAL;
		pr_err("Spin %d unknown\n", (sio_top_jtagid_lo >> 29) & 0xF);
		जाओ error2;
	पूर्ण
	चयन ((sio_top_jtagid_lo >> 12) & 0xFF) अणु
	हाल 0x13:
		/* typeId = DRX3913K_TYPE_ID */
		state->m_has_lna = false;
		state->m_has_oob = false;
		state->m_has_atv = false;
		state->m_has_audio = false;
		state->m_has_dvbt = true;
		state->m_has_dvbc = true;
		state->m_has_sawsw = true;
		state->m_has_gpio2 = false;
		state->m_has_gpio1 = false;
		state->m_has_irqn = false;
		अवरोध;
	हाल 0x15:
		/* typeId = DRX3915K_TYPE_ID */
		state->m_has_lna = false;
		state->m_has_oob = false;
		state->m_has_atv = true;
		state->m_has_audio = false;
		state->m_has_dvbt = true;
		state->m_has_dvbc = false;
		state->m_has_sawsw = true;
		state->m_has_gpio2 = true;
		state->m_has_gpio1 = true;
		state->m_has_irqn = false;
		अवरोध;
	हाल 0x16:
		/* typeId = DRX3916K_TYPE_ID */
		state->m_has_lna = false;
		state->m_has_oob = false;
		state->m_has_atv = true;
		state->m_has_audio = false;
		state->m_has_dvbt = true;
		state->m_has_dvbc = false;
		state->m_has_sawsw = true;
		state->m_has_gpio2 = true;
		state->m_has_gpio1 = true;
		state->m_has_irqn = false;
		अवरोध;
	हाल 0x18:
		/* typeId = DRX3918K_TYPE_ID */
		state->m_has_lna = false;
		state->m_has_oob = false;
		state->m_has_atv = true;
		state->m_has_audio = true;
		state->m_has_dvbt = true;
		state->m_has_dvbc = false;
		state->m_has_sawsw = true;
		state->m_has_gpio2 = true;
		state->m_has_gpio1 = true;
		state->m_has_irqn = false;
		अवरोध;
	हाल 0x21:
		/* typeId = DRX3921K_TYPE_ID */
		state->m_has_lna = false;
		state->m_has_oob = false;
		state->m_has_atv = true;
		state->m_has_audio = true;
		state->m_has_dvbt = true;
		state->m_has_dvbc = true;
		state->m_has_sawsw = true;
		state->m_has_gpio2 = true;
		state->m_has_gpio1 = true;
		state->m_has_irqn = false;
		अवरोध;
	हाल 0x23:
		/* typeId = DRX3923K_TYPE_ID */
		state->m_has_lna = false;
		state->m_has_oob = false;
		state->m_has_atv = true;
		state->m_has_audio = true;
		state->m_has_dvbt = true;
		state->m_has_dvbc = true;
		state->m_has_sawsw = true;
		state->m_has_gpio2 = true;
		state->m_has_gpio1 = true;
		state->m_has_irqn = false;
		अवरोध;
	हाल 0x25:
		/* typeId = DRX3925K_TYPE_ID */
		state->m_has_lna = false;
		state->m_has_oob = false;
		state->m_has_atv = true;
		state->m_has_audio = true;
		state->m_has_dvbt = true;
		state->m_has_dvbc = true;
		state->m_has_sawsw = true;
		state->m_has_gpio2 = true;
		state->m_has_gpio1 = true;
		state->m_has_irqn = false;
		अवरोध;
	हाल 0x26:
		/* typeId = DRX3926K_TYPE_ID */
		state->m_has_lna = false;
		state->m_has_oob = false;
		state->m_has_atv = true;
		state->m_has_audio = false;
		state->m_has_dvbt = true;
		state->m_has_dvbc = true;
		state->m_has_sawsw = true;
		state->m_has_gpio2 = true;
		state->m_has_gpio1 = true;
		state->m_has_irqn = false;
		अवरोध;
	शेष:
		pr_err("DeviceID 0x%02x not supported\n",
			((sio_top_jtagid_lo >> 12) & 0xFF));
		status = -EINVAL;
		जाओ error2;
	पूर्ण

	pr_info("detected a drx-39%02xk, spin %s, xtal %d.%03d MHz\n",
	       ((sio_top_jtagid_lo >> 12) & 0xFF), spin,
	       state->m_osc_घड़ी_freq / 1000,
	       state->m_osc_घड़ी_freq % 1000);

error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);

error2:
	वापस status;
पूर्ण

अटल पूर्णांक hi_command(काष्ठा drxk_state *state, u16 cmd, u16 *p_result)
अणु
	पूर्णांक status;
	bool घातerकरोwn_cmd;

	dprपूर्णांकk(1, "\n");

	/* Write command */
	status = ग_लिखो16(state, SIO_HI_RA_RAM_CMD__A, cmd);
	अगर (status < 0)
		जाओ error;
	अगर (cmd == SIO_HI_RA_RAM_CMD_RESET)
		usleep_range(1000, 2000);

	घातerकरोwn_cmd =
	    (bool) ((cmd == SIO_HI_RA_RAM_CMD_CONFIG) &&
		    ((state->m_hi_cfg_ctrl) &
		     SIO_HI_RA_RAM_PAR_5_CFG_SLEEP__M) ==
		    SIO_HI_RA_RAM_PAR_5_CFG_SLEEP_ZZZ);
	अगर (!घातerकरोwn_cmd) अणु
		/* Wait until command rdy */
		u32 retry_count = 0;
		u16 रुको_cmd;

		करो अणु
			usleep_range(1000, 2000);
			retry_count += 1;
			status = पढ़ो16(state, SIO_HI_RA_RAM_CMD__A,
					  &रुको_cmd);
		पूर्ण जबतक ((status < 0 || रुको_cmd) && (retry_count < DRXK_MAX_RETRIES));
		अगर (status < 0)
			जाओ error;
		status = पढ़ो16(state, SIO_HI_RA_RAM_RES__A, p_result);
	पूर्ण
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);

	वापस status;
पूर्ण

अटल पूर्णांक hi_cfg_command(काष्ठा drxk_state *state)
अणु
	पूर्णांक status;

	dprपूर्णांकk(1, "\n");

	mutex_lock(&state->mutex);

	status = ग_लिखो16(state, SIO_HI_RA_RAM_PAR_6__A,
			 state->m_hi_cfg_समयout);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SIO_HI_RA_RAM_PAR_5__A,
			 state->m_hi_cfg_ctrl);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SIO_HI_RA_RAM_PAR_4__A,
			 state->m_hi_cfg_wake_up_key);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SIO_HI_RA_RAM_PAR_3__A,
			 state->m_hi_cfg_bridge_delay);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SIO_HI_RA_RAM_PAR_2__A,
			 state->m_hi_cfg_timing_भाग);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SIO_HI_RA_RAM_PAR_1__A,
			 SIO_HI_RA_RAM_PAR_1_PAR1_SEC_KEY);
	अगर (status < 0)
		जाओ error;
	status = hi_command(state, SIO_HI_RA_RAM_CMD_CONFIG, शून्य);
	अगर (status < 0)
		जाओ error;

	state->m_hi_cfg_ctrl &= ~SIO_HI_RA_RAM_PAR_5_CFG_SLEEP_ZZZ;
error:
	mutex_unlock(&state->mutex);
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

अटल पूर्णांक init_hi(काष्ठा drxk_state *state)
अणु
	dprपूर्णांकk(1, "\n");

	state->m_hi_cfg_wake_up_key = (state->demod_address << 1);
	state->m_hi_cfg_समयout = 0x96FF;
	/* port/bridge/घातer करोwn ctrl */
	state->m_hi_cfg_ctrl = SIO_HI_RA_RAM_PAR_5_CFG_SLV0_SLAVE;

	वापस hi_cfg_command(state);
पूर्ण

अटल पूर्णांक mpegts_configure_pins(काष्ठा drxk_state *state, bool mpeg_enable)
अणु
	पूर्णांक status;
	u16 sio_pdr_mclk_cfg = 0;
	u16 sio_pdr_mdx_cfg = 0;
	u16 err_cfg = 0;

	dprपूर्णांकk(1, ": mpeg %s, %s mode\n",
		mpeg_enable ? "enable" : "disable",
		state->m_enable_parallel ? "parallel" : "serial");

	/* stop lock indicator process */
	status = ग_लिखो16(state, SCU_RAM_GPIO__A,
			 SCU_RAM_GPIO_HW_LOCK_IND_DISABLE);
	अगर (status < 0)
		जाओ error;

	/*  MPEG TS pad configuration */
	status = ग_लिखो16(state, SIO_TOP_COMM_KEY__A, SIO_TOP_COMM_KEY_KEY);
	अगर (status < 0)
		जाओ error;

	अगर (!mpeg_enable) अणु
		/*  Set MPEG TS pads to inpuपंचांगode */
		status = ग_लिखो16(state, SIO_PDR_MSTRT_CFG__A, 0x0000);
		अगर (status < 0)
			जाओ error;
		status = ग_लिखो16(state, SIO_PDR_MERR_CFG__A, 0x0000);
		अगर (status < 0)
			जाओ error;
		status = ग_लिखो16(state, SIO_PDR_MCLK_CFG__A, 0x0000);
		अगर (status < 0)
			जाओ error;
		status = ग_लिखो16(state, SIO_PDR_MVAL_CFG__A, 0x0000);
		अगर (status < 0)
			जाओ error;
		status = ग_लिखो16(state, SIO_PDR_MD0_CFG__A, 0x0000);
		अगर (status < 0)
			जाओ error;
		status = ग_लिखो16(state, SIO_PDR_MD1_CFG__A, 0x0000);
		अगर (status < 0)
			जाओ error;
		status = ग_लिखो16(state, SIO_PDR_MD2_CFG__A, 0x0000);
		अगर (status < 0)
			जाओ error;
		status = ग_लिखो16(state, SIO_PDR_MD3_CFG__A, 0x0000);
		अगर (status < 0)
			जाओ error;
		status = ग_लिखो16(state, SIO_PDR_MD4_CFG__A, 0x0000);
		अगर (status < 0)
			जाओ error;
		status = ग_लिखो16(state, SIO_PDR_MD5_CFG__A, 0x0000);
		अगर (status < 0)
			जाओ error;
		status = ग_लिखो16(state, SIO_PDR_MD6_CFG__A, 0x0000);
		अगर (status < 0)
			जाओ error;
		status = ग_लिखो16(state, SIO_PDR_MD7_CFG__A, 0x0000);
		अगर (status < 0)
			जाओ error;
	पूर्ण अन्यथा अणु
		/* Enable MPEG output */
		sio_pdr_mdx_cfg =
			((state->m_ts_data_strength <<
			SIO_PDR_MD0_CFG_DRIVE__B) | 0x0003);
		sio_pdr_mclk_cfg = ((state->m_ts_घड़ीk_strength <<
					SIO_PDR_MCLK_CFG_DRIVE__B) |
					0x0003);

		status = ग_लिखो16(state, SIO_PDR_MSTRT_CFG__A, sio_pdr_mdx_cfg);
		अगर (status < 0)
			जाओ error;

		अगर (state->enable_merr_cfg)
			err_cfg = sio_pdr_mdx_cfg;

		status = ग_लिखो16(state, SIO_PDR_MERR_CFG__A, err_cfg);
		अगर (status < 0)
			जाओ error;
		status = ग_लिखो16(state, SIO_PDR_MVAL_CFG__A, err_cfg);
		अगर (status < 0)
			जाओ error;

		अगर (state->m_enable_parallel) अणु
			/* parallel -> enable MD1 to MD7 */
			status = ग_लिखो16(state, SIO_PDR_MD1_CFG__A,
					 sio_pdr_mdx_cfg);
			अगर (status < 0)
				जाओ error;
			status = ग_लिखो16(state, SIO_PDR_MD2_CFG__A,
					 sio_pdr_mdx_cfg);
			अगर (status < 0)
				जाओ error;
			status = ग_लिखो16(state, SIO_PDR_MD3_CFG__A,
					 sio_pdr_mdx_cfg);
			अगर (status < 0)
				जाओ error;
			status = ग_लिखो16(state, SIO_PDR_MD4_CFG__A,
					 sio_pdr_mdx_cfg);
			अगर (status < 0)
				जाओ error;
			status = ग_लिखो16(state, SIO_PDR_MD5_CFG__A,
					 sio_pdr_mdx_cfg);
			अगर (status < 0)
				जाओ error;
			status = ग_लिखो16(state, SIO_PDR_MD6_CFG__A,
					 sio_pdr_mdx_cfg);
			अगर (status < 0)
				जाओ error;
			status = ग_लिखो16(state, SIO_PDR_MD7_CFG__A,
					 sio_pdr_mdx_cfg);
			अगर (status < 0)
				जाओ error;
		पूर्ण अन्यथा अणु
			sio_pdr_mdx_cfg = ((state->m_ts_data_strength <<
						SIO_PDR_MD0_CFG_DRIVE__B)
					| 0x0003);
			/* serial -> disable MD1 to MD7 */
			status = ग_लिखो16(state, SIO_PDR_MD1_CFG__A, 0x0000);
			अगर (status < 0)
				जाओ error;
			status = ग_लिखो16(state, SIO_PDR_MD2_CFG__A, 0x0000);
			अगर (status < 0)
				जाओ error;
			status = ग_लिखो16(state, SIO_PDR_MD3_CFG__A, 0x0000);
			अगर (status < 0)
				जाओ error;
			status = ग_लिखो16(state, SIO_PDR_MD4_CFG__A, 0x0000);
			अगर (status < 0)
				जाओ error;
			status = ग_लिखो16(state, SIO_PDR_MD5_CFG__A, 0x0000);
			अगर (status < 0)
				जाओ error;
			status = ग_लिखो16(state, SIO_PDR_MD6_CFG__A, 0x0000);
			अगर (status < 0)
				जाओ error;
			status = ग_लिखो16(state, SIO_PDR_MD7_CFG__A, 0x0000);
			अगर (status < 0)
				जाओ error;
		पूर्ण
		status = ग_लिखो16(state, SIO_PDR_MCLK_CFG__A, sio_pdr_mclk_cfg);
		अगर (status < 0)
			जाओ error;
		status = ग_लिखो16(state, SIO_PDR_MD0_CFG__A, sio_pdr_mdx_cfg);
		अगर (status < 0)
			जाओ error;
	पूर्ण
	/*  Enable MB output over MPEG pads and ctl input */
	status = ग_लिखो16(state, SIO_PDR_MON_CFG__A, 0x0000);
	अगर (status < 0)
		जाओ error;
	/*  Write nomagic word to enable pdr reg ग_लिखो */
	status = ग_लिखो16(state, SIO_TOP_COMM_KEY__A, 0x0000);
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

अटल पूर्णांक mpegts_disable(काष्ठा drxk_state *state)
अणु
	dprपूर्णांकk(1, "\n");

	वापस mpegts_configure_pins(state, false);
पूर्ण

अटल पूर्णांक bl_chain_cmd(काष्ठा drxk_state *state,
		      u16 rom_offset, u16 nr_of_elements, u32 समय_out)
अणु
	u16 bl_status = 0;
	पूर्णांक status;
	अचिन्हित दीर्घ end;

	dprपूर्णांकk(1, "\n");
	mutex_lock(&state->mutex);
	status = ग_लिखो16(state, SIO_BL_MODE__A, SIO_BL_MODE_CHAIN);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SIO_BL_CHAIN_ADDR__A, rom_offset);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SIO_BL_CHAIN_LEN__A, nr_of_elements);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SIO_BL_ENABLE__A, SIO_BL_ENABLE_ON);
	अगर (status < 0)
		जाओ error;

	end = jअगरfies + msecs_to_jअगरfies(समय_out);
	करो अणु
		usleep_range(1000, 2000);
		status = पढ़ो16(state, SIO_BL_STATUS__A, &bl_status);
		अगर (status < 0)
			जाओ error;
	पूर्ण जबतक ((bl_status == 0x1) &&
			((समय_is_after_jअगरfies(end))));

	अगर (bl_status == 0x1) अणु
		pr_err("SIO not ready\n");
		status = -EINVAL;
		जाओ error2;
	पूर्ण
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
error2:
	mutex_unlock(&state->mutex);
	वापस status;
पूर्ण


अटल पूर्णांक करोwnload_microcode(काष्ठा drxk_state *state,
			     स्थिर u8 p_mc_image[], u32 length)
अणु
	स्थिर u8 *p_src = p_mc_image;
	u32 address;
	u16 n_blocks;
	u16 block_size;
	u32 offset = 0;
	u32 i;
	पूर्णांक status = 0;

	dprपूर्णांकk(1, "\n");

	/* करोwn the drain (we करोn't care about MAGIC_WORD) */
#अगर 0
	/* For future reference */
	drain = (p_src[0] << 8) | p_src[1];
#पूर्ण_अगर
	p_src += माप(u16);
	offset += माप(u16);
	n_blocks = (p_src[0] << 8) | p_src[1];
	p_src += माप(u16);
	offset += माप(u16);

	क्रम (i = 0; i < n_blocks; i += 1) अणु
		address = (p_src[0] << 24) | (p_src[1] << 16) |
		    (p_src[2] << 8) | p_src[3];
		p_src += माप(u32);
		offset += माप(u32);

		block_size = ((p_src[0] << 8) | p_src[1]) * माप(u16);
		p_src += माप(u16);
		offset += माप(u16);

#अगर 0
		/* For future reference */
		flags = (p_src[0] << 8) | p_src[1];
#पूर्ण_अगर
		p_src += माप(u16);
		offset += माप(u16);

#अगर 0
		/* For future reference */
		block_crc = (p_src[0] << 8) | p_src[1];
#पूर्ण_अगर
		p_src += माप(u16);
		offset += माप(u16);

		अगर (offset + block_size > length) अणु
			pr_err("Firmware is corrupted.\n");
			वापस -EINVAL;
		पूर्ण

		status = ग_लिखो_block(state, address, block_size, p_src);
		अगर (status < 0) अणु
			pr_err("Error %d while loading firmware\n", status);
			अवरोध;
		पूर्ण
		p_src += block_size;
		offset += block_size;
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक dvbt_enable_ofdm_token_ring(काष्ठा drxk_state *state, bool enable)
अणु
	पूर्णांक status;
	u16 data = 0;
	u16 desired_ctrl = SIO_OFDM_SH_OFDM_RING_ENABLE_ON;
	u16 desired_status = SIO_OFDM_SH_OFDM_RING_STATUS_ENABLED;
	अचिन्हित दीर्घ end;

	dprपूर्णांकk(1, "\n");

	अगर (!enable) अणु
		desired_ctrl = SIO_OFDM_SH_OFDM_RING_ENABLE_OFF;
		desired_status = SIO_OFDM_SH_OFDM_RING_STATUS_DOWN;
	पूर्ण

	status = पढ़ो16(state, SIO_OFDM_SH_OFDM_RING_STATUS__A, &data);
	अगर (status >= 0 && data == desired_status) अणु
		/* tokenring alपढ़ोy has correct status */
		वापस status;
	पूर्ण
	/* Disable/enable dvbt tokenring bridge   */
	status = ग_लिखो16(state, SIO_OFDM_SH_OFDM_RING_ENABLE__A, desired_ctrl);

	end = jअगरfies + msecs_to_jअगरfies(DRXK_OFDM_TR_SHUTDOWN_TIMEOUT);
	करो अणु
		status = पढ़ो16(state, SIO_OFDM_SH_OFDM_RING_STATUS__A, &data);
		अगर ((status >= 0 && data == desired_status)
		    || समय_is_after_jअगरfies(end))
			अवरोध;
		usleep_range(1000, 2000);
	पूर्ण जबतक (1);
	अगर (data != desired_status) अणु
		pr_err("SIO not ready\n");
		वापस -EINVAL;
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक mpegts_stop(काष्ठा drxk_state *state)
अणु
	पूर्णांक status = 0;
	u16 fec_oc_snc_mode = 0;
	u16 fec_oc_ipr_mode = 0;

	dprपूर्णांकk(1, "\n");

	/* Graceful shutकरोwn (byte boundaries) */
	status = पढ़ो16(state, FEC_OC_SNC_MODE__A, &fec_oc_snc_mode);
	अगर (status < 0)
		जाओ error;
	fec_oc_snc_mode |= FEC_OC_SNC_MODE_SHUTDOWN__M;
	status = ग_लिखो16(state, FEC_OC_SNC_MODE__A, fec_oc_snc_mode);
	अगर (status < 0)
		जाओ error;

	/* Suppress MCLK during असलence of data */
	status = पढ़ो16(state, FEC_OC_IPR_MODE__A, &fec_oc_ipr_mode);
	अगर (status < 0)
		जाओ error;
	fec_oc_ipr_mode |= FEC_OC_IPR_MODE_MCLK_DIS_DAT_ABS__M;
	status = ग_लिखो16(state, FEC_OC_IPR_MODE__A, fec_oc_ipr_mode);

error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);

	वापस status;
पूर्ण

अटल पूर्णांक scu_command(काष्ठा drxk_state *state,
		       u16 cmd, u8 parameter_len,
		       u16 *parameter, u8 result_len, u16 *result)
अणु
#अगर (SCU_RAM_PARAM_0__A - SCU_RAM_PARAM_15__A) != 15
#त्रुटि DRXK रेजिस्टर mapping no दीर्घer compatible with this routine!
#पूर्ण_अगर
	u16 cur_cmd = 0;
	पूर्णांक status = -EINVAL;
	अचिन्हित दीर्घ end;
	u8 buffer[34];
	पूर्णांक cnt = 0, ii;
	स्थिर अक्षर *p;
	अक्षर errname[30];

	dprपूर्णांकk(1, "\n");

	अगर ((cmd == 0) || ((parameter_len > 0) && (parameter == शून्य)) ||
	    ((result_len > 0) && (result == शून्य))) अणु
		pr_err("Error %d on %s\n", status, __func__);
		वापस status;
	पूर्ण

	mutex_lock(&state->mutex);

	/* assume that the command रेजिस्टर is पढ़ोy
		since it is checked afterwards */
	अगर (parameter) अणु
		क्रम (ii = parameter_len - 1; ii >= 0; ii -= 1) अणु
			buffer[cnt++] = (parameter[ii] & 0xFF);
			buffer[cnt++] = ((parameter[ii] >> 8) & 0xFF);
		पूर्ण
	पूर्ण
	buffer[cnt++] = (cmd & 0xFF);
	buffer[cnt++] = ((cmd >> 8) & 0xFF);

	ग_लिखो_block(state, SCU_RAM_PARAM_0__A -
			(parameter_len - 1), cnt, buffer);
	/* Wait until SCU has processed command */
	end = jअगरfies + msecs_to_jअगरfies(DRXK_MAX_WAITTIME);
	करो अणु
		usleep_range(1000, 2000);
		status = पढ़ो16(state, SCU_RAM_COMMAND__A, &cur_cmd);
		अगर (status < 0)
			जाओ error;
	पूर्ण जबतक (!(cur_cmd == DRX_SCU_READY) && (समय_is_after_jअगरfies(end)));
	अगर (cur_cmd != DRX_SCU_READY) अणु
		pr_err("SCU not ready\n");
		status = -EIO;
		जाओ error2;
	पूर्ण
	/* पढ़ो results */
	अगर ((result_len > 0) && (result != शून्य)) अणु
		s16 err;
		पूर्णांक ii;

		क्रम (ii = result_len - 1; ii >= 0; ii -= 1) अणु
			status = पढ़ो16(state, SCU_RAM_PARAM_0__A - ii,
					&result[ii]);
			अगर (status < 0)
				जाओ error;
		पूर्ण

		/* Check अगर an error was reported by SCU */
		err = (s16)result[0];
		अगर (err >= 0)
			जाओ error;

		/* check क्रम the known error codes */
		चयन (err) अणु
		हाल SCU_RESULT_UNKCMD:
			p = "SCU_RESULT_UNKCMD";
			अवरोध;
		हाल SCU_RESULT_UNKSTD:
			p = "SCU_RESULT_UNKSTD";
			अवरोध;
		हाल SCU_RESULT_SIZE:
			p = "SCU_RESULT_SIZE";
			अवरोध;
		हाल SCU_RESULT_INVPAR:
			p = "SCU_RESULT_INVPAR";
			अवरोध;
		शेष: /* Other negative values are errors */
			प्र_लिखो(errname, "ERROR: %d\n", err);
			p = errname;
		पूर्ण
		pr_err("%s while sending cmd 0x%04x with params:", p, cmd);
		prपूर्णांक_hex_dump_bytes("drxk: ", DUMP_PREFIX_NONE, buffer, cnt);
		status = -EINVAL;
		जाओ error2;
	पूर्ण

error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
error2:
	mutex_unlock(&state->mutex);
	वापस status;
पूर्ण

अटल पूर्णांक set_iqm_af(काष्ठा drxk_state *state, bool active)
अणु
	u16 data = 0;
	पूर्णांक status;

	dprपूर्णांकk(1, "\n");

	/* Configure IQM */
	status = पढ़ो16(state, IQM_AF_STDBY__A, &data);
	अगर (status < 0)
		जाओ error;

	अगर (!active) अणु
		data |= (IQM_AF_STDBY_STDBY_ADC_STANDBY
				| IQM_AF_STDBY_STDBY_AMP_STANDBY
				| IQM_AF_STDBY_STDBY_PD_STANDBY
				| IQM_AF_STDBY_STDBY_TAGC_IF_STANDBY
				| IQM_AF_STDBY_STDBY_TAGC_RF_STANDBY);
	पूर्ण अन्यथा अणु
		data &= ((~IQM_AF_STDBY_STDBY_ADC_STANDBY)
				& (~IQM_AF_STDBY_STDBY_AMP_STANDBY)
				& (~IQM_AF_STDBY_STDBY_PD_STANDBY)
				& (~IQM_AF_STDBY_STDBY_TAGC_IF_STANDBY)
				& (~IQM_AF_STDBY_STDBY_TAGC_RF_STANDBY)
			);
	पूर्ण
	status = ग_लिखो16(state, IQM_AF_STDBY__A, data);

error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

अटल पूर्णांक ctrl_घातer_mode(काष्ठा drxk_state *state, क्रमागत drx_घातer_mode *mode)
अणु
	पूर्णांक status = 0;
	u16 sio_cc_pwd_mode = 0;

	dprपूर्णांकk(1, "\n");

	/* Check arguments */
	अगर (mode == शून्य)
		वापस -EINVAL;

	चयन (*mode) अणु
	हाल DRX_POWER_UP:
		sio_cc_pwd_mode = SIO_CC_PWD_MODE_LEVEL_NONE;
		अवरोध;
	हाल DRXK_POWER_DOWN_OFDM:
		sio_cc_pwd_mode = SIO_CC_PWD_MODE_LEVEL_OFDM;
		अवरोध;
	हाल DRXK_POWER_DOWN_CORE:
		sio_cc_pwd_mode = SIO_CC_PWD_MODE_LEVEL_CLOCK;
		अवरोध;
	हाल DRXK_POWER_DOWN_PLL:
		sio_cc_pwd_mode = SIO_CC_PWD_MODE_LEVEL_PLL;
		अवरोध;
	हाल DRX_POWER_DOWN:
		sio_cc_pwd_mode = SIO_CC_PWD_MODE_LEVEL_OSC;
		अवरोध;
	शेष:
		/* Unknow sleep mode */
		वापस -EINVAL;
	पूर्ण

	/* If alपढ़ोy in requested घातer mode, करो nothing */
	अगर (state->m_current_घातer_mode == *mode)
		वापस 0;

	/* For next steps make sure to start from DRX_POWER_UP mode */
	अगर (state->m_current_घातer_mode != DRX_POWER_UP) अणु
		status = घातer_up_device(state);
		अगर (status < 0)
			जाओ error;
		status = dvbt_enable_ofdm_token_ring(state, true);
		अगर (status < 0)
			जाओ error;
	पूर्ण

	अगर (*mode == DRX_POWER_UP) अणु
		/* Restore analog & pin configuration */
	पूर्ण अन्यथा अणु
		/* Power करोwn to requested mode */
		/* Backup some रेजिस्टर settings */
		/* Set pins with possible pull-ups connected
		   to them in input mode */
		/* Analog घातer करोwn */
		/* ADC घातer करोwn */
		/* Power करोwn device */
		/* stop all comm_exec */
		/* Stop and घातer करोwn previous standard */
		चयन (state->m_operation_mode) अणु
		हाल OM_DVBT:
			status = mpegts_stop(state);
			अगर (status < 0)
				जाओ error;
			status = घातer_करोwn_dvbt(state, false);
			अगर (status < 0)
				जाओ error;
			अवरोध;
		हाल OM_QAM_ITU_A:
		हाल OM_QAM_ITU_C:
			status = mpegts_stop(state);
			अगर (status < 0)
				जाओ error;
			status = घातer_करोwn_qam(state);
			अगर (status < 0)
				जाओ error;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		status = dvbt_enable_ofdm_token_ring(state, false);
		अगर (status < 0)
			जाओ error;
		status = ग_लिखो16(state, SIO_CC_PWD_MODE__A, sio_cc_pwd_mode);
		अगर (status < 0)
			जाओ error;
		status = ग_लिखो16(state, SIO_CC_UPDATE__A, SIO_CC_UPDATE_KEY);
		अगर (status < 0)
			जाओ error;

		अगर (*mode != DRXK_POWER_DOWN_OFDM) अणु
			state->m_hi_cfg_ctrl |=
				SIO_HI_RA_RAM_PAR_5_CFG_SLEEP_ZZZ;
			status = hi_cfg_command(state);
			अगर (status < 0)
				जाओ error;
		पूर्ण
	पूर्ण
	state->m_current_घातer_mode = *mode;

error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);

	वापस status;
पूर्ण

अटल पूर्णांक घातer_करोwn_dvbt(काष्ठा drxk_state *state, bool set_घातer_mode)
अणु
	क्रमागत drx_घातer_mode घातer_mode = DRXK_POWER_DOWN_OFDM;
	u16 cmd_result = 0;
	u16 data = 0;
	पूर्णांक status;

	dprपूर्णांकk(1, "\n");

	status = पढ़ो16(state, SCU_COMM_EXEC__A, &data);
	अगर (status < 0)
		जाओ error;
	अगर (data == SCU_COMM_EXEC_ACTIVE) अणु
		/* Send OFDM stop command */
		status = scu_command(state,
				     SCU_RAM_COMMAND_STANDARD_OFDM
				     | SCU_RAM_COMMAND_CMD_DEMOD_STOP,
				     0, शून्य, 1, &cmd_result);
		अगर (status < 0)
			जाओ error;
		/* Send OFDM reset command */
		status = scu_command(state,
				     SCU_RAM_COMMAND_STANDARD_OFDM
				     | SCU_RAM_COMMAND_CMD_DEMOD_RESET,
				     0, शून्य, 1, &cmd_result);
		अगर (status < 0)
			जाओ error;
	पूर्ण

	/* Reset datapath क्रम OFDM, processors first */
	status = ग_लिखो16(state, OFDM_SC_COMM_EXEC__A, OFDM_SC_COMM_EXEC_STOP);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, OFDM_LC_COMM_EXEC__A, OFDM_LC_COMM_EXEC_STOP);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, IQM_COMM_EXEC__A, IQM_COMM_EXEC_B_STOP);
	अगर (status < 0)
		जाओ error;

	/* घातerकरोwn AFE                   */
	status = set_iqm_af(state, false);
	अगर (status < 0)
		जाओ error;

	/* घातerकरोwn to OFDM mode          */
	अगर (set_घातer_mode) अणु
		status = ctrl_घातer_mode(state, &घातer_mode);
		अगर (status < 0)
			जाओ error;
	पूर्ण
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

अटल पूर्णांक setoperation_mode(काष्ठा drxk_state *state,
			    क्रमागत operation_mode o_mode)
अणु
	पूर्णांक status = 0;

	dprपूर्णांकk(1, "\n");
	/*
	   Stop and घातer करोwn previous standard
	   TODO investigate total घातer करोwn instead of partial
	   घातer करोwn depending on "previous" standard.
	 */

	/* disable HW lock indicator */
	status = ग_लिखो16(state, SCU_RAM_GPIO__A,
			 SCU_RAM_GPIO_HW_LOCK_IND_DISABLE);
	अगर (status < 0)
		जाओ error;

	/* Device is alपढ़ोy at the required mode */
	अगर (state->m_operation_mode == o_mode)
		वापस 0;

	चयन (state->m_operation_mode) अणु
		/* OM_NONE was added क्रम start up */
	हाल OM_NONE:
		अवरोध;
	हाल OM_DVBT:
		status = mpegts_stop(state);
		अगर (status < 0)
			जाओ error;
		status = घातer_करोwn_dvbt(state, true);
		अगर (status < 0)
			जाओ error;
		state->m_operation_mode = OM_NONE;
		अवरोध;
	हाल OM_QAM_ITU_A:
	हाल OM_QAM_ITU_C:
		status = mpegts_stop(state);
		अगर (status < 0)
			जाओ error;
		status = घातer_करोwn_qam(state);
		अगर (status < 0)
			जाओ error;
		state->m_operation_mode = OM_NONE;
		अवरोध;
	हाल OM_QAM_ITU_B:
	शेष:
		status = -EINVAL;
		जाओ error;
	पूर्ण

	/*
		Power up new standard
		*/
	चयन (o_mode) अणु
	हाल OM_DVBT:
		dprपूर्णांकk(1, ": DVB-T\n");
		state->m_operation_mode = o_mode;
		status = set_dvbt_standard(state, o_mode);
		अगर (status < 0)
			जाओ error;
		अवरोध;
	हाल OM_QAM_ITU_A:
	हाल OM_QAM_ITU_C:
		dprपूर्णांकk(1, ": DVB-C Annex %c\n",
			(state->m_operation_mode == OM_QAM_ITU_A) ? 'A' : 'C');
		state->m_operation_mode = o_mode;
		status = set_qam_standard(state, o_mode);
		अगर (status < 0)
			जाओ error;
		अवरोध;
	हाल OM_QAM_ITU_B:
	शेष:
		status = -EINVAL;
	पूर्ण
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

अटल पूर्णांक start(काष्ठा drxk_state *state, s32 offset_freq,
		 s32 पूर्णांकermediate_frequency)
अणु
	पूर्णांक status = -EINVAL;

	u16 i_freqk_hz;
	s32 offsetk_hz = offset_freq / 1000;

	dprपूर्णांकk(1, "\n");
	अगर (state->m_drxk_state != DRXK_STOPPED &&
		state->m_drxk_state != DRXK_DTV_STARTED)
		जाओ error;

	state->m_b_mirror_freq_spect = (state->props.inversion == INVERSION_ON);

	अगर (पूर्णांकermediate_frequency < 0) अणु
		state->m_b_mirror_freq_spect = !state->m_b_mirror_freq_spect;
		पूर्णांकermediate_frequency = -पूर्णांकermediate_frequency;
	पूर्ण

	चयन (state->m_operation_mode) अणु
	हाल OM_QAM_ITU_A:
	हाल OM_QAM_ITU_C:
		i_freqk_hz = (पूर्णांकermediate_frequency / 1000);
		status = set_qam(state, i_freqk_hz, offsetk_hz);
		अगर (status < 0)
			जाओ error;
		state->m_drxk_state = DRXK_DTV_STARTED;
		अवरोध;
	हाल OM_DVBT:
		i_freqk_hz = (पूर्णांकermediate_frequency / 1000);
		status = mpegts_stop(state);
		अगर (status < 0)
			जाओ error;
		status = set_dvbt(state, i_freqk_hz, offsetk_hz);
		अगर (status < 0)
			जाओ error;
		status = dvbt_start(state);
		अगर (status < 0)
			जाओ error;
		state->m_drxk_state = DRXK_DTV_STARTED;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

अटल पूर्णांक shut_करोwn(काष्ठा drxk_state *state)
अणु
	dprपूर्णांकk(1, "\n");

	mpegts_stop(state);
	वापस 0;
पूर्ण

अटल पूर्णांक get_lock_status(काष्ठा drxk_state *state, u32 *p_lock_status)
अणु
	पूर्णांक status = -EINVAL;

	dprपूर्णांकk(1, "\n");

	अगर (p_lock_status == शून्य)
		जाओ error;

	*p_lock_status = NOT_LOCKED;

	/* define the SCU command code */
	चयन (state->m_operation_mode) अणु
	हाल OM_QAM_ITU_A:
	हाल OM_QAM_ITU_B:
	हाल OM_QAM_ITU_C:
		status = get_qam_lock_status(state, p_lock_status);
		अवरोध;
	हाल OM_DVBT:
		status = get_dvbt_lock_status(state, p_lock_status);
		अवरोध;
	शेष:
		pr_debug("Unsupported operation mode %d in %s\n",
			state->m_operation_mode, __func__);
		वापस 0;
	पूर्ण
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

अटल पूर्णांक mpegts_start(काष्ठा drxk_state *state)
अणु
	पूर्णांक status;

	u16 fec_oc_snc_mode = 0;

	/* Allow OC to sync again */
	status = पढ़ो16(state, FEC_OC_SNC_MODE__A, &fec_oc_snc_mode);
	अगर (status < 0)
		जाओ error;
	fec_oc_snc_mode &= ~FEC_OC_SNC_MODE_SHUTDOWN__M;
	status = ग_लिखो16(state, FEC_OC_SNC_MODE__A, fec_oc_snc_mode);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, FEC_OC_SNC_UNLOCK__A, 1);
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

अटल पूर्णांक mpegts_dto_init(काष्ठा drxk_state *state)
अणु
	पूर्णांक status;

	dprपूर्णांकk(1, "\n");

	/* Rate पूर्णांकegration settings */
	status = ग_लिखो16(state, FEC_OC_RCN_CTL_STEP_LO__A, 0x0000);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, FEC_OC_RCN_CTL_STEP_HI__A, 0x000C);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, FEC_OC_RCN_GAIN__A, 0x000A);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, FEC_OC_AVR_PARM_A__A, 0x0008);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, FEC_OC_AVR_PARM_B__A, 0x0006);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, FEC_OC_TMD_HI_MARGIN__A, 0x0680);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, FEC_OC_TMD_LO_MARGIN__A, 0x0080);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, FEC_OC_TMD_COUNT__A, 0x03F4);
	अगर (status < 0)
		जाओ error;

	/* Additional configuration */
	status = ग_लिखो16(state, FEC_OC_OCR_INVERT__A, 0);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, FEC_OC_SNC_LWM__A, 2);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, FEC_OC_SNC_HWM__A, 12);
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);

	वापस status;
पूर्ण

अटल पूर्णांक mpegts_dto_setup(काष्ठा drxk_state *state,
			  क्रमागत operation_mode o_mode)
अणु
	पूर्णांक status;

	u16 fec_oc_reg_mode = 0;	/* FEC_OC_MODE       रेजिस्टर value */
	u16 fec_oc_reg_ipr_mode = 0;	/* FEC_OC_IPR_MODE   रेजिस्टर value */
	u16 fec_oc_dto_mode = 0;	/* FEC_OC_IPR_INVERT रेजिस्टर value */
	u16 fec_oc_fct_mode = 0;	/* FEC_OC_IPR_INVERT रेजिस्टर value */
	u16 fec_oc_dto_period = 2;	/* FEC_OC_IPR_INVERT रेजिस्टर value */
	u16 fec_oc_dto_burst_len = 188;	/* FEC_OC_IPR_INVERT रेजिस्टर value */
	u32 fec_oc_rcn_ctl_rate = 0;	/* FEC_OC_IPR_INVERT रेजिस्टर value */
	u16 fec_oc_पंचांगd_mode = 0;
	u16 fec_oc_पंचांगd_पूर्णांक_upd_rate = 0;
	u32 max_bit_rate = 0;
	bool अटल_clk = false;

	dprपूर्णांकk(1, "\n");

	/* Check insertion of the Reed-Solomon parity bytes */
	status = पढ़ो16(state, FEC_OC_MODE__A, &fec_oc_reg_mode);
	अगर (status < 0)
		जाओ error;
	status = पढ़ो16(state, FEC_OC_IPR_MODE__A, &fec_oc_reg_ipr_mode);
	अगर (status < 0)
		जाओ error;
	fec_oc_reg_mode &= (~FEC_OC_MODE_PARITY__M);
	fec_oc_reg_ipr_mode &= (~FEC_OC_IPR_MODE_MVAL_DIS_PAR__M);
	अगर (state->m_insert_rs_byte) अणु
		/* enable parity symbol क्रमward */
		fec_oc_reg_mode |= FEC_OC_MODE_PARITY__M;
		/* MVAL disable during parity bytes */
		fec_oc_reg_ipr_mode |= FEC_OC_IPR_MODE_MVAL_DIS_PAR__M;
		/* TS burst length to 204 */
		fec_oc_dto_burst_len = 204;
	पूर्ण

	/* Check serial or parallel output */
	fec_oc_reg_ipr_mode &= (~(FEC_OC_IPR_MODE_SERIAL__M));
	अगर (!state->m_enable_parallel) अणु
		/* MPEG data output is serial -> set ipr_mode[0] */
		fec_oc_reg_ipr_mode |= FEC_OC_IPR_MODE_SERIAL__M;
	पूर्ण

	चयन (o_mode) अणु
	हाल OM_DVBT:
		max_bit_rate = state->m_dvbt_bitrate;
		fec_oc_पंचांगd_mode = 3;
		fec_oc_rcn_ctl_rate = 0xC00000;
		अटल_clk = state->m_dvbt_अटल_clk;
		अवरोध;
	हाल OM_QAM_ITU_A:
	हाल OM_QAM_ITU_C:
		fec_oc_पंचांगd_mode = 0x0004;
		fec_oc_rcn_ctl_rate = 0xD2B4EE;	/* good क्रम >63 Mb/s */
		max_bit_rate = state->m_dvbc_bitrate;
		अटल_clk = state->m_dvbc_अटल_clk;
		अवरोध;
	शेष:
		status = -EINVAL;
	पूर्ण		/* चयन (standard) */
	अगर (status < 0)
		जाओ error;

	/* Configure DTO's */
	अगर (अटल_clk) अणु
		u32 bit_rate = 0;

		/* Rational DTO क्रम MCLK source (अटल MCLK rate),
			Dynamic DTO क्रम optimal grouping
			(aव्योम पूर्णांकra-packet gaps),
			DTO offset enable to sync TS burst with MSTRT */
		fec_oc_dto_mode = (FEC_OC_DTO_MODE_DYNAMIC__M |
				FEC_OC_DTO_MODE_OFFSET_ENABLE__M);
		fec_oc_fct_mode = (FEC_OC_FCT_MODE_RAT_ENA__M |
				FEC_OC_FCT_MODE_VIRT_ENA__M);

		/* Check user defined bitrate */
		bit_rate = max_bit_rate;
		अगर (bit_rate > 75900000UL) अणु	/* max is 75.9 Mb/s */
			bit_rate = 75900000UL;
		पूर्ण
		/* Rational DTO period:
			dto_period = (Fsys / bitrate) - 2

			result should be न्यूनमानed,
			to make sure >= requested bitrate
			*/
		fec_oc_dto_period = (u16) (((state->m_sys_घड़ी_freq)
						* 1000) / bit_rate);
		अगर (fec_oc_dto_period <= 2)
			fec_oc_dto_period = 0;
		अन्यथा
			fec_oc_dto_period -= 2;
		fec_oc_पंचांगd_पूर्णांक_upd_rate = 8;
	पूर्ण अन्यथा अणु
		/* (commonAttr->अटल_clk == false) => dynamic mode */
		fec_oc_dto_mode = FEC_OC_DTO_MODE_DYNAMIC__M;
		fec_oc_fct_mode = FEC_OC_FCT_MODE__PRE;
		fec_oc_पंचांगd_पूर्णांक_upd_rate = 5;
	पूर्ण

	/* Write appropriate रेजिस्टरs with requested configuration */
	status = ग_लिखो16(state, FEC_OC_DTO_BURST_LEN__A, fec_oc_dto_burst_len);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, FEC_OC_DTO_PERIOD__A, fec_oc_dto_period);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, FEC_OC_DTO_MODE__A, fec_oc_dto_mode);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, FEC_OC_FCT_MODE__A, fec_oc_fct_mode);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, FEC_OC_MODE__A, fec_oc_reg_mode);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, FEC_OC_IPR_MODE__A, fec_oc_reg_ipr_mode);
	अगर (status < 0)
		जाओ error;

	/* Rate पूर्णांकegration settings */
	status = ग_लिखो32(state, FEC_OC_RCN_CTL_RATE_LO__A, fec_oc_rcn_ctl_rate);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, FEC_OC_TMD_INT_UPD_RATE__A,
			 fec_oc_पंचांगd_पूर्णांक_upd_rate);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, FEC_OC_TMD_MODE__A, fec_oc_पंचांगd_mode);
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

अटल पूर्णांक mpegts_configure_polarity(काष्ठा drxk_state *state)
अणु
	u16 fec_oc_reg_ipr_invert = 0;

	/* Data mask क्रम the output data byte */
	u16 invert_data_mask =
	    FEC_OC_IPR_INVERT_MD7__M | FEC_OC_IPR_INVERT_MD6__M |
	    FEC_OC_IPR_INVERT_MD5__M | FEC_OC_IPR_INVERT_MD4__M |
	    FEC_OC_IPR_INVERT_MD3__M | FEC_OC_IPR_INVERT_MD2__M |
	    FEC_OC_IPR_INVERT_MD1__M | FEC_OC_IPR_INVERT_MD0__M;

	dprपूर्णांकk(1, "\n");

	/* Control selective inversion of output bits */
	fec_oc_reg_ipr_invert &= (~(invert_data_mask));
	अगर (state->m_invert_data)
		fec_oc_reg_ipr_invert |= invert_data_mask;
	fec_oc_reg_ipr_invert &= (~(FEC_OC_IPR_INVERT_MERR__M));
	अगर (state->m_invert_err)
		fec_oc_reg_ipr_invert |= FEC_OC_IPR_INVERT_MERR__M;
	fec_oc_reg_ipr_invert &= (~(FEC_OC_IPR_INVERT_MSTRT__M));
	अगर (state->m_invert_str)
		fec_oc_reg_ipr_invert |= FEC_OC_IPR_INVERT_MSTRT__M;
	fec_oc_reg_ipr_invert &= (~(FEC_OC_IPR_INVERT_MVAL__M));
	अगर (state->m_invert_val)
		fec_oc_reg_ipr_invert |= FEC_OC_IPR_INVERT_MVAL__M;
	fec_oc_reg_ipr_invert &= (~(FEC_OC_IPR_INVERT_MCLK__M));
	अगर (state->m_invert_clk)
		fec_oc_reg_ipr_invert |= FEC_OC_IPR_INVERT_MCLK__M;

	वापस ग_लिखो16(state, FEC_OC_IPR_INVERT__A, fec_oc_reg_ipr_invert);
पूर्ण

#घोषणा   SCU_RAM_AGC_KI_INV_RF_POL__M 0x4000

अटल पूर्णांक set_agc_rf(काष्ठा drxk_state *state,
		    काष्ठा s_cfg_agc *p_agc_cfg, bool is_dtv)
अणु
	पूर्णांक status = -EINVAL;
	u16 data = 0;
	काष्ठा s_cfg_agc *p_अगर_agc_settings;

	dprपूर्णांकk(1, "\n");

	अगर (p_agc_cfg == शून्य)
		जाओ error;

	चयन (p_agc_cfg->ctrl_mode) अणु
	हाल DRXK_AGC_CTRL_AUTO:
		/* Enable RF AGC DAC */
		status = पढ़ो16(state, IQM_AF_STDBY__A, &data);
		अगर (status < 0)
			जाओ error;
		data &= ~IQM_AF_STDBY_STDBY_TAGC_RF_STANDBY;
		status = ग_लिखो16(state, IQM_AF_STDBY__A, data);
		अगर (status < 0)
			जाओ error;
		status = पढ़ो16(state, SCU_RAM_AGC_CONFIG__A, &data);
		अगर (status < 0)
			जाओ error;

		/* Enable SCU RF AGC loop */
		data &= ~SCU_RAM_AGC_CONFIG_DISABLE_RF_AGC__M;

		/* Polarity */
		अगर (state->m_rf_agc_pol)
			data |= SCU_RAM_AGC_CONFIG_INV_RF_POL__M;
		अन्यथा
			data &= ~SCU_RAM_AGC_CONFIG_INV_RF_POL__M;
		status = ग_लिखो16(state, SCU_RAM_AGC_CONFIG__A, data);
		अगर (status < 0)
			जाओ error;

		/* Set speed (using complementary reduction value) */
		status = पढ़ो16(state, SCU_RAM_AGC_KI_RED__A, &data);
		अगर (status < 0)
			जाओ error;

		data &= ~SCU_RAM_AGC_KI_RED_RAGC_RED__M;
		data |= (~(p_agc_cfg->speed <<
				SCU_RAM_AGC_KI_RED_RAGC_RED__B)
				& SCU_RAM_AGC_KI_RED_RAGC_RED__M);

		status = ग_लिखो16(state, SCU_RAM_AGC_KI_RED__A, data);
		अगर (status < 0)
			जाओ error;

		अगर (is_dvbt(state))
			p_अगर_agc_settings = &state->m_dvbt_अगर_agc_cfg;
		अन्यथा अगर (is_qam(state))
			p_अगर_agc_settings = &state->m_qam_अगर_agc_cfg;
		अन्यथा
			p_अगर_agc_settings = &state->m_atv_अगर_agc_cfg;
		अगर (p_अगर_agc_settings == शून्य) अणु
			status = -EINVAL;
			जाओ error;
		पूर्ण

		/* Set TOP, only अगर IF-AGC is in AUTO mode */
		अगर (p_अगर_agc_settings->ctrl_mode == DRXK_AGC_CTRL_AUTO) अणु
			status = ग_लिखो16(state,
					 SCU_RAM_AGC_IF_IACCU_HI_TGT_MAX__A,
					 p_agc_cfg->top);
			अगर (status < 0)
				जाओ error;
		पूर्ण

		/* Cut-Off current */
		status = ग_लिखो16(state, SCU_RAM_AGC_RF_IACCU_HI_CO__A,
				 p_agc_cfg->cut_off_current);
		अगर (status < 0)
			जाओ error;

		/* Max. output level */
		status = ग_लिखो16(state, SCU_RAM_AGC_RF_MAX__A,
				 p_agc_cfg->max_output_level);
		अगर (status < 0)
			जाओ error;

		अवरोध;

	हाल DRXK_AGC_CTRL_USER:
		/* Enable RF AGC DAC */
		status = पढ़ो16(state, IQM_AF_STDBY__A, &data);
		अगर (status < 0)
			जाओ error;
		data &= ~IQM_AF_STDBY_STDBY_TAGC_RF_STANDBY;
		status = ग_लिखो16(state, IQM_AF_STDBY__A, data);
		अगर (status < 0)
			जाओ error;

		/* Disable SCU RF AGC loop */
		status = पढ़ो16(state, SCU_RAM_AGC_CONFIG__A, &data);
		अगर (status < 0)
			जाओ error;
		data |= SCU_RAM_AGC_CONFIG_DISABLE_RF_AGC__M;
		अगर (state->m_rf_agc_pol)
			data |= SCU_RAM_AGC_CONFIG_INV_RF_POL__M;
		अन्यथा
			data &= ~SCU_RAM_AGC_CONFIG_INV_RF_POL__M;
		status = ग_लिखो16(state, SCU_RAM_AGC_CONFIG__A, data);
		अगर (status < 0)
			जाओ error;

		/* SCU c.o.c. to 0, enabling full control range */
		status = ग_लिखो16(state, SCU_RAM_AGC_RF_IACCU_HI_CO__A, 0);
		अगर (status < 0)
			जाओ error;

		/* Write value to output pin */
		status = ग_लिखो16(state, SCU_RAM_AGC_RF_IACCU_HI__A,
				 p_agc_cfg->output_level);
		अगर (status < 0)
			जाओ error;
		अवरोध;

	हाल DRXK_AGC_CTRL_OFF:
		/* Disable RF AGC DAC */
		status = पढ़ो16(state, IQM_AF_STDBY__A, &data);
		अगर (status < 0)
			जाओ error;
		data |= IQM_AF_STDBY_STDBY_TAGC_RF_STANDBY;
		status = ग_लिखो16(state, IQM_AF_STDBY__A, data);
		अगर (status < 0)
			जाओ error;

		/* Disable SCU RF AGC loop */
		status = पढ़ो16(state, SCU_RAM_AGC_CONFIG__A, &data);
		अगर (status < 0)
			जाओ error;
		data |= SCU_RAM_AGC_CONFIG_DISABLE_RF_AGC__M;
		status = ग_लिखो16(state, SCU_RAM_AGC_CONFIG__A, data);
		अगर (status < 0)
			जाओ error;
		अवरोध;

	शेष:
		status = -EINVAL;

	पूर्ण
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

#घोषणा SCU_RAM_AGC_KI_INV_IF_POL__M 0x2000

अटल पूर्णांक set_agc_अगर(काष्ठा drxk_state *state,
		    काष्ठा s_cfg_agc *p_agc_cfg, bool is_dtv)
अणु
	u16 data = 0;
	पूर्णांक status = 0;
	काष्ठा s_cfg_agc *p_rf_agc_settings;

	dprपूर्णांकk(1, "\n");

	चयन (p_agc_cfg->ctrl_mode) अणु
	हाल DRXK_AGC_CTRL_AUTO:

		/* Enable IF AGC DAC */
		status = पढ़ो16(state, IQM_AF_STDBY__A, &data);
		अगर (status < 0)
			जाओ error;
		data &= ~IQM_AF_STDBY_STDBY_TAGC_IF_STANDBY;
		status = ग_लिखो16(state, IQM_AF_STDBY__A, data);
		अगर (status < 0)
			जाओ error;

		status = पढ़ो16(state, SCU_RAM_AGC_CONFIG__A, &data);
		अगर (status < 0)
			जाओ error;

		/* Enable SCU IF AGC loop */
		data &= ~SCU_RAM_AGC_CONFIG_DISABLE_IF_AGC__M;

		/* Polarity */
		अगर (state->m_अगर_agc_pol)
			data |= SCU_RAM_AGC_CONFIG_INV_IF_POL__M;
		अन्यथा
			data &= ~SCU_RAM_AGC_CONFIG_INV_IF_POL__M;
		status = ग_लिखो16(state, SCU_RAM_AGC_CONFIG__A, data);
		अगर (status < 0)
			जाओ error;

		/* Set speed (using complementary reduction value) */
		status = पढ़ो16(state, SCU_RAM_AGC_KI_RED__A, &data);
		अगर (status < 0)
			जाओ error;
		data &= ~SCU_RAM_AGC_KI_RED_IAGC_RED__M;
		data |= (~(p_agc_cfg->speed <<
				SCU_RAM_AGC_KI_RED_IAGC_RED__B)
				& SCU_RAM_AGC_KI_RED_IAGC_RED__M);

		status = ग_लिखो16(state, SCU_RAM_AGC_KI_RED__A, data);
		अगर (status < 0)
			जाओ error;

		अगर (is_qam(state))
			p_rf_agc_settings = &state->m_qam_rf_agc_cfg;
		अन्यथा
			p_rf_agc_settings = &state->m_atv_rf_agc_cfg;
		अगर (p_rf_agc_settings == शून्य)
			वापस -1;
		/* Restore TOP */
		status = ग_लिखो16(state, SCU_RAM_AGC_IF_IACCU_HI_TGT_MAX__A,
				 p_rf_agc_settings->top);
		अगर (status < 0)
			जाओ error;
		अवरोध;

	हाल DRXK_AGC_CTRL_USER:

		/* Enable IF AGC DAC */
		status = पढ़ो16(state, IQM_AF_STDBY__A, &data);
		अगर (status < 0)
			जाओ error;
		data &= ~IQM_AF_STDBY_STDBY_TAGC_IF_STANDBY;
		status = ग_लिखो16(state, IQM_AF_STDBY__A, data);
		अगर (status < 0)
			जाओ error;

		status = पढ़ो16(state, SCU_RAM_AGC_CONFIG__A, &data);
		अगर (status < 0)
			जाओ error;

		/* Disable SCU IF AGC loop */
		data |= SCU_RAM_AGC_CONFIG_DISABLE_IF_AGC__M;

		/* Polarity */
		अगर (state->m_अगर_agc_pol)
			data |= SCU_RAM_AGC_CONFIG_INV_IF_POL__M;
		अन्यथा
			data &= ~SCU_RAM_AGC_CONFIG_INV_IF_POL__M;
		status = ग_लिखो16(state, SCU_RAM_AGC_CONFIG__A, data);
		अगर (status < 0)
			जाओ error;

		/* Write value to output pin */
		status = ग_लिखो16(state, SCU_RAM_AGC_IF_IACCU_HI_TGT_MAX__A,
				 p_agc_cfg->output_level);
		अगर (status < 0)
			जाओ error;
		अवरोध;

	हाल DRXK_AGC_CTRL_OFF:

		/* Disable If AGC DAC */
		status = पढ़ो16(state, IQM_AF_STDBY__A, &data);
		अगर (status < 0)
			जाओ error;
		data |= IQM_AF_STDBY_STDBY_TAGC_IF_STANDBY;
		status = ग_लिखो16(state, IQM_AF_STDBY__A, data);
		अगर (status < 0)
			जाओ error;

		/* Disable SCU IF AGC loop */
		status = पढ़ो16(state, SCU_RAM_AGC_CONFIG__A, &data);
		अगर (status < 0)
			जाओ error;
		data |= SCU_RAM_AGC_CONFIG_DISABLE_IF_AGC__M;
		status = ग_लिखो16(state, SCU_RAM_AGC_CONFIG__A, data);
		अगर (status < 0)
			जाओ error;
		अवरोध;
	पूर्ण		/* चयन (agcSettingsIf->ctrl_mode) */

	/* always set the top to support
		configurations without अगर-loop */
	status = ग_लिखो16(state, SCU_RAM_AGC_INGAIN_TGT_MIN__A, p_agc_cfg->top);
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

अटल पूर्णांक get_qam_संकेत_to_noise(काष्ठा drxk_state *state,
			       s32 *p_संकेत_to_noise)
अणु
	पूर्णांक status = 0;
	u16 qam_sl_err_घातer = 0;	/* accum. error between
					raw and sliced symbols */
	u32 qam_sl_sig_घातer = 0;	/* used क्रम MER, depends of
					QAM modulation */
	u32 qam_sl_mer = 0;	/* QAM MER */

	dprपूर्णांकk(1, "\n");

	/* MER calculation */

	/* get the रेजिस्टर value needed क्रम MER */
	status = पढ़ो16(state, QAM_SL_ERR_POWER__A, &qam_sl_err_घातer);
	अगर (status < 0) अणु
		pr_err("Error %d on %s\n", status, __func__);
		वापस -EINVAL;
	पूर्ण

	चयन (state->props.modulation) अणु
	हाल QAM_16:
		qam_sl_sig_घातer = DRXK_QAM_SL_SIG_POWER_QAM16 << 2;
		अवरोध;
	हाल QAM_32:
		qam_sl_sig_घातer = DRXK_QAM_SL_SIG_POWER_QAM32 << 2;
		अवरोध;
	हाल QAM_64:
		qam_sl_sig_घातer = DRXK_QAM_SL_SIG_POWER_QAM64 << 2;
		अवरोध;
	हाल QAM_128:
		qam_sl_sig_घातer = DRXK_QAM_SL_SIG_POWER_QAM128 << 2;
		अवरोध;
	शेष:
	हाल QAM_256:
		qam_sl_sig_घातer = DRXK_QAM_SL_SIG_POWER_QAM256 << 2;
		अवरोध;
	पूर्ण

	अगर (qam_sl_err_घातer > 0) अणु
		qam_sl_mer = log10बार100(qam_sl_sig_घातer) -
			log10बार100((u32) qam_sl_err_घातer);
	पूर्ण
	*p_संकेत_to_noise = qam_sl_mer;

	वापस status;
पूर्ण

अटल पूर्णांक get_dvbt_संकेत_to_noise(काष्ठा drxk_state *state,
				s32 *p_संकेत_to_noise)
अणु
	पूर्णांक status;
	u16 reg_data = 0;
	u32 eq_reg_td_sqr_err_i = 0;
	u32 eq_reg_td_sqr_err_q = 0;
	u16 eq_reg_td_sqr_err_exp = 0;
	u16 eq_reg_td_tps_pwr_ofs = 0;
	u16 eq_reg_td_req_smb_cnt = 0;
	u32 tps_cnt = 0;
	u32 sqr_err_iq = 0;
	u32 a = 0;
	u32 b = 0;
	u32 c = 0;
	u32 i_mer = 0;
	u16 transmission_params = 0;

	dprपूर्णांकk(1, "\n");

	status = पढ़ो16(state, OFDM_EQ_TOP_TD_TPS_PWR_OFS__A,
			&eq_reg_td_tps_pwr_ofs);
	अगर (status < 0)
		जाओ error;
	status = पढ़ो16(state, OFDM_EQ_TOP_TD_REQ_SMB_CNT__A,
			&eq_reg_td_req_smb_cnt);
	अगर (status < 0)
		जाओ error;
	status = पढ़ो16(state, OFDM_EQ_TOP_TD_SQR_ERR_EXP__A,
			&eq_reg_td_sqr_err_exp);
	अगर (status < 0)
		जाओ error;
	status = पढ़ो16(state, OFDM_EQ_TOP_TD_SQR_ERR_I__A,
			&reg_data);
	अगर (status < 0)
		जाओ error;
	/* Extend SQR_ERR_I operational range */
	eq_reg_td_sqr_err_i = (u32) reg_data;
	अगर ((eq_reg_td_sqr_err_exp > 11) &&
		(eq_reg_td_sqr_err_i < 0x00000FFFUL)) अणु
		eq_reg_td_sqr_err_i += 0x00010000UL;
	पूर्ण
	status = पढ़ो16(state, OFDM_EQ_TOP_TD_SQR_ERR_Q__A, &reg_data);
	अगर (status < 0)
		जाओ error;
	/* Extend SQR_ERR_Q operational range */
	eq_reg_td_sqr_err_q = (u32) reg_data;
	अगर ((eq_reg_td_sqr_err_exp > 11) &&
		(eq_reg_td_sqr_err_q < 0x00000FFFUL))
		eq_reg_td_sqr_err_q += 0x00010000UL;

	status = पढ़ो16(state, OFDM_SC_RA_RAM_OP_PARAM__A,
			&transmission_params);
	अगर (status < 0)
		जाओ error;

	/* Check input data क्रम MER */

	/* MER calculation (in 0.1 dB) without गणित.स */
	अगर ((eq_reg_td_tps_pwr_ofs == 0) || (eq_reg_td_req_smb_cnt == 0))
		i_mer = 0;
	अन्यथा अगर ((eq_reg_td_sqr_err_i + eq_reg_td_sqr_err_q) == 0) अणु
		/* No error at all, this must be the HW reset value
			* Apparently no first measurement yet
			* Set MER to 0.0 */
		i_mer = 0;
	पूर्ण अन्यथा अणु
		sqr_err_iq = (eq_reg_td_sqr_err_i + eq_reg_td_sqr_err_q) <<
			eq_reg_td_sqr_err_exp;
		अगर ((transmission_params &
			OFDM_SC_RA_RAM_OP_PARAM_MODE__M)
			== OFDM_SC_RA_RAM_OP_PARAM_MODE_2K)
			tps_cnt = 17;
		अन्यथा
			tps_cnt = 68;

		/* IMER = 100 * log10 (x)
			where x = (eq_reg_td_tps_pwr_ofs^2 *
			eq_reg_td_req_smb_cnt * tps_cnt)/sqr_err_iq

			=> IMER = a + b -c
			where a = 100 * log10 (eq_reg_td_tps_pwr_ofs^2)
			b = 100 * log10 (eq_reg_td_req_smb_cnt * tps_cnt)
			c = 100 * log10 (sqr_err_iq)
			*/

		/* log(x) x = 9bits * 9bits->18 bits  */
		a = log10बार100(eq_reg_td_tps_pwr_ofs *
					eq_reg_td_tps_pwr_ofs);
		/* log(x) x = 16bits * 7bits->23 bits  */
		b = log10बार100(eq_reg_td_req_smb_cnt * tps_cnt);
		/* log(x) x = (16bits + 16bits) << 15 ->32 bits  */
		c = log10बार100(sqr_err_iq);

		i_mer = a + b - c;
	पूर्ण
	*p_संकेत_to_noise = i_mer;

error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

अटल पूर्णांक get_संकेत_to_noise(काष्ठा drxk_state *state, s32 *p_संकेत_to_noise)
अणु
	dprपूर्णांकk(1, "\n");

	*p_संकेत_to_noise = 0;
	चयन (state->m_operation_mode) अणु
	हाल OM_DVBT:
		वापस get_dvbt_संकेत_to_noise(state, p_संकेत_to_noise);
	हाल OM_QAM_ITU_A:
	हाल OM_QAM_ITU_C:
		वापस get_qam_संकेत_to_noise(state, p_संकेत_to_noise);
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

#अगर 0
अटल पूर्णांक get_dvbt_quality(काष्ठा drxk_state *state, s32 *p_quality)
अणु
	/* SNR Values क्रम quasi errorमुक्त reception rom Nordig 2.2 */
	पूर्णांक status = 0;

	dprपूर्णांकk(1, "\n");

	अटल s32 QE_SN[] = अणु
		51,		/* QPSK 1/2 */
		69,		/* QPSK 2/3 */
		79,		/* QPSK 3/4 */
		89,		/* QPSK 5/6 */
		97,		/* QPSK 7/8 */
		108,		/* 16-QAM 1/2 */
		131,		/* 16-QAM 2/3 */
		146,		/* 16-QAM 3/4 */
		156,		/* 16-QAM 5/6 */
		160,		/* 16-QAM 7/8 */
		165,		/* 64-QAM 1/2 */
		187,		/* 64-QAM 2/3 */
		202,		/* 64-QAM 3/4 */
		216,		/* 64-QAM 5/6 */
		225,		/* 64-QAM 7/8 */
	पूर्ण;

	*p_quality = 0;

	करो अणु
		s32 संकेत_to_noise = 0;
		u16 स्थिरellation = 0;
		u16 code_rate = 0;
		u32 संकेत_to_noise_rel;
		u32 ber_quality;

		status = get_dvbt_संकेत_to_noise(state, &संकेत_to_noise);
		अगर (status < 0)
			अवरोध;
		status = पढ़ो16(state, OFDM_EQ_TOP_TD_TPS_CONST__A,
				&स्थिरellation);
		अगर (status < 0)
			अवरोध;
		स्थिरellation &= OFDM_EQ_TOP_TD_TPS_CONST__M;

		status = पढ़ो16(state, OFDM_EQ_TOP_TD_TPS_CODE_HP__A,
				&code_rate);
		अगर (status < 0)
			अवरोध;
		code_rate &= OFDM_EQ_TOP_TD_TPS_CODE_HP__M;

		अगर (स्थिरellation > OFDM_EQ_TOP_TD_TPS_CONST_64QAM ||
		    code_rate > OFDM_EQ_TOP_TD_TPS_CODE_LP_7_8)
			अवरोध;
		संकेत_to_noise_rel = संकेत_to_noise -
		    QE_SN[स्थिरellation * 5 + code_rate];
		ber_quality = 100;

		अगर (संकेत_to_noise_rel < -70)
			*p_quality = 0;
		अन्यथा अगर (संकेत_to_noise_rel < 30)
			*p_quality = ((संकेत_to_noise_rel + 70) *
				     ber_quality) / 100;
		अन्यथा
			*p_quality = ber_quality;
	पूर्ण जबतक (0);
	वापस 0;
पूर्ण;

अटल पूर्णांक get_dvbc_quality(काष्ठा drxk_state *state, s32 *p_quality)
अणु
	पूर्णांक status = 0;
	*p_quality = 0;

	dprपूर्णांकk(1, "\n");

	करो अणु
		u32 संकेत_to_noise = 0;
		u32 ber_quality = 100;
		u32 संकेत_to_noise_rel = 0;

		status = get_qam_संकेत_to_noise(state, &संकेत_to_noise);
		अगर (status < 0)
			अवरोध;

		चयन (state->props.modulation) अणु
		हाल QAM_16:
			संकेत_to_noise_rel = संकेत_to_noise - 200;
			अवरोध;
		हाल QAM_32:
			संकेत_to_noise_rel = संकेत_to_noise - 230;
			अवरोध;	/* Not in NorDig */
		हाल QAM_64:
			संकेत_to_noise_rel = संकेत_to_noise - 260;
			अवरोध;
		हाल QAM_128:
			संकेत_to_noise_rel = संकेत_to_noise - 290;
			अवरोध;
		शेष:
		हाल QAM_256:
			संकेत_to_noise_rel = संकेत_to_noise - 320;
			अवरोध;
		पूर्ण

		अगर (संकेत_to_noise_rel < -70)
			*p_quality = 0;
		अन्यथा अगर (संकेत_to_noise_rel < 30)
			*p_quality = ((संकेत_to_noise_rel + 70) *
				     ber_quality) / 100;
		अन्यथा
			*p_quality = ber_quality;
	पूर्ण जबतक (0);

	वापस status;
पूर्ण

अटल पूर्णांक get_quality(काष्ठा drxk_state *state, s32 *p_quality)
अणु
	dprपूर्णांकk(1, "\n");

	चयन (state->m_operation_mode) अणु
	हाल OM_DVBT:
		वापस get_dvbt_quality(state, p_quality);
	हाल OM_QAM_ITU_A:
		वापस get_dvbc_quality(state, p_quality);
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

/* Free data ram in SIO HI */
#घोषणा SIO_HI_RA_RAM_USR_BEGIN__A 0x420040
#घोषणा SIO_HI_RA_RAM_USR_END__A   0x420060

#घोषणा DRXK_HI_ATOMIC_BUF_START (SIO_HI_RA_RAM_USR_BEGIN__A)
#घोषणा DRXK_HI_ATOMIC_BUF_END   (SIO_HI_RA_RAM_USR_BEGIN__A + 7)
#घोषणा DRXK_HI_ATOMIC_READ      SIO_HI_RA_RAM_PAR_3_ACP_RW_READ
#घोषणा DRXK_HI_ATOMIC_WRITE     SIO_HI_RA_RAM_PAR_3_ACP_RW_WRITE

#घोषणा DRXDAP_FASI_ADDR2BLOCK(addr)  (((addr) >> 22) & 0x3F)
#घोषणा DRXDAP_FASI_ADDR2BANK(addr)   (((addr) >> 16) & 0x3F)
#घोषणा DRXDAP_FASI_ADDR2OFFSET(addr) ((addr) & 0x7FFF)

अटल पूर्णांक ConfigureI2CBridge(काष्ठा drxk_state *state, bool b_enable_bridge)
अणु
	पूर्णांक status = -EINVAL;

	dprपूर्णांकk(1, "\n");

	अगर (state->m_drxk_state == DRXK_UNINITIALIZED)
		वापस 0;
	अगर (state->m_drxk_state == DRXK_POWERED_DOWN)
		जाओ error;

	अगर (state->no_i2c_bridge)
		वापस 0;

	status = ग_लिखो16(state, SIO_HI_RA_RAM_PAR_1__A,
			 SIO_HI_RA_RAM_PAR_1_PAR1_SEC_KEY);
	अगर (status < 0)
		जाओ error;
	अगर (b_enable_bridge) अणु
		status = ग_लिखो16(state, SIO_HI_RA_RAM_PAR_2__A,
				 SIO_HI_RA_RAM_PAR_2_BRD_CFG_CLOSED);
		अगर (status < 0)
			जाओ error;
	पूर्ण अन्यथा अणु
		status = ग_लिखो16(state, SIO_HI_RA_RAM_PAR_2__A,
				 SIO_HI_RA_RAM_PAR_2_BRD_CFG_OPEN);
		अगर (status < 0)
			जाओ error;
	पूर्ण

	status = hi_command(state, SIO_HI_RA_RAM_CMD_BRDCTRL, शून्य);

error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

अटल पूर्णांक set_pre_saw(काष्ठा drxk_state *state,
		     काष्ठा s_cfg_pre_saw *p_pre_saw_cfg)
अणु
	पूर्णांक status = -EINVAL;

	dprपूर्णांकk(1, "\n");

	अगर ((p_pre_saw_cfg == शून्य)
	    || (p_pre_saw_cfg->reference > IQM_AF_PDREF__M))
		जाओ error;

	status = ग_लिखो16(state, IQM_AF_PDREF__A, p_pre_saw_cfg->reference);
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

अटल पूर्णांक bl_direct_cmd(काष्ठा drxk_state *state, u32 target_addr,
		       u16 rom_offset, u16 nr_of_elements, u32 समय_out)
अणु
	u16 bl_status = 0;
	u16 offset = (u16) ((target_addr >> 0) & 0x00FFFF);
	u16 blockbank = (u16) ((target_addr >> 16) & 0x000FFF);
	पूर्णांक status;
	अचिन्हित दीर्घ end;

	dprपूर्णांकk(1, "\n");

	mutex_lock(&state->mutex);
	status = ग_लिखो16(state, SIO_BL_MODE__A, SIO_BL_MODE_सूचीECT);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SIO_BL_TGT_HDR__A, blockbank);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SIO_BL_TGT_ADDR__A, offset);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SIO_BL_SRC_ADDR__A, rom_offset);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SIO_BL_SRC_LEN__A, nr_of_elements);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SIO_BL_ENABLE__A, SIO_BL_ENABLE_ON);
	अगर (status < 0)
		जाओ error;

	end = jअगरfies + msecs_to_jअगरfies(समय_out);
	करो अणु
		status = पढ़ो16(state, SIO_BL_STATUS__A, &bl_status);
		अगर (status < 0)
			जाओ error;
	पूर्ण जबतक ((bl_status == 0x1) && समय_is_after_jअगरfies(end));
	अगर (bl_status == 0x1) अणु
		pr_err("SIO not ready\n");
		status = -EINVAL;
		जाओ error2;
	पूर्ण
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
error2:
	mutex_unlock(&state->mutex);
	वापस status;

पूर्ण

अटल पूर्णांक adc_sync_measurement(काष्ठा drxk_state *state, u16 *count)
अणु
	u16 data = 0;
	पूर्णांक status;

	dprपूर्णांकk(1, "\n");

	/* start measurement */
	status = ग_लिखो16(state, IQM_AF_COMM_EXEC__A, IQM_AF_COMM_EXEC_ACTIVE);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, IQM_AF_START_LOCK__A, 1);
	अगर (status < 0)
		जाओ error;

	*count = 0;
	status = पढ़ो16(state, IQM_AF_PHASE0__A, &data);
	अगर (status < 0)
		जाओ error;
	अगर (data == 127)
		*count = *count + 1;
	status = पढ़ो16(state, IQM_AF_PHASE1__A, &data);
	अगर (status < 0)
		जाओ error;
	अगर (data == 127)
		*count = *count + 1;
	status = पढ़ो16(state, IQM_AF_PHASE2__A, &data);
	अगर (status < 0)
		जाओ error;
	अगर (data == 127)
		*count = *count + 1;

error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

अटल पूर्णांक adc_synchronization(काष्ठा drxk_state *state)
अणु
	u16 count = 0;
	पूर्णांक status;

	dprपूर्णांकk(1, "\n");

	status = adc_sync_measurement(state, &count);
	अगर (status < 0)
		जाओ error;

	अगर (count == 1) अणु
		/* Try sampling on a dअगरferent edge */
		u16 clk_neg = 0;

		status = पढ़ो16(state, IQM_AF_CLKNEG__A, &clk_neg);
		अगर (status < 0)
			जाओ error;
		अगर ((clk_neg & IQM_AF_CLKNEG_CLKNEGDATA__M) ==
			IQM_AF_CLKNEG_CLKNEGDATA_CLK_ADC_DATA_POS) अणु
			clk_neg &= (~(IQM_AF_CLKNEG_CLKNEGDATA__M));
			clk_neg |=
				IQM_AF_CLKNEG_CLKNEGDATA_CLK_ADC_DATA_NEG;
		पूर्ण अन्यथा अणु
			clk_neg &= (~(IQM_AF_CLKNEG_CLKNEGDATA__M));
			clk_neg |=
				IQM_AF_CLKNEG_CLKNEGDATA_CLK_ADC_DATA_POS;
		पूर्ण
		status = ग_लिखो16(state, IQM_AF_CLKNEG__A, clk_neg);
		अगर (status < 0)
			जाओ error;
		status = adc_sync_measurement(state, &count);
		अगर (status < 0)
			जाओ error;
	पूर्ण

	अगर (count < 2)
		status = -EINVAL;
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

अटल पूर्णांक set_frequency_shअगरter(काष्ठा drxk_state *state,
			       u16 पूर्णांकermediate_freqk_hz,
			       s32 tuner_freq_offset, bool is_dtv)
अणु
	bool select_pos_image = false;
	u32 rf_freq_residual = tuner_freq_offset;
	u32 fm_frequency_shअगरt = 0;
	bool tuner_mirror = !state->m_b_mirror_freq_spect;
	u32 adc_freq;
	bool adc_flip;
	पूर्णांक status;
	u32 अगर_freq_actual;
	u32 sampling_frequency = (u32) (state->m_sys_घड़ी_freq / 3);
	u32 frequency_shअगरt;
	bool image_to_select;

	dprपूर्णांकk(1, "\n");

	/*
	   Program frequency shअगरter
	   No need to account क्रम mirroring on RF
	 */
	अगर (is_dtv) अणु
		अगर ((state->m_operation_mode == OM_QAM_ITU_A) ||
		    (state->m_operation_mode == OM_QAM_ITU_C) ||
		    (state->m_operation_mode == OM_DVBT))
			select_pos_image = true;
		अन्यथा
			select_pos_image = false;
	पूर्ण
	अगर (tuner_mirror)
		/* tuner करोesn't mirror */
		अगर_freq_actual = पूर्णांकermediate_freqk_hz +
		    rf_freq_residual + fm_frequency_shअगरt;
	अन्यथा
		/* tuner mirrors */
		अगर_freq_actual = पूर्णांकermediate_freqk_hz -
		    rf_freq_residual - fm_frequency_shअगरt;
	अगर (अगर_freq_actual > sampling_frequency / 2) अणु
		/* adc mirrors */
		adc_freq = sampling_frequency - अगर_freq_actual;
		adc_flip = true;
	पूर्ण अन्यथा अणु
		/* adc करोesn't mirror */
		adc_freq = अगर_freq_actual;
		adc_flip = false;
	पूर्ण

	frequency_shअगरt = adc_freq;
	image_to_select = state->m_rfmirror ^ tuner_mirror ^
	    adc_flip ^ select_pos_image;
	state->m_iqm_fs_rate_ofs =
	    Frac28a((frequency_shअगरt), sampling_frequency);

	अगर (image_to_select)
		state->m_iqm_fs_rate_ofs = ~state->m_iqm_fs_rate_ofs + 1;

	/* Program frequency shअगरter with tuner offset compensation */
	/* frequency_shअगरt += tuner_freq_offset; TODO */
	status = ग_लिखो32(state, IQM_FS_RATE_OFS_LO__A,
			 state->m_iqm_fs_rate_ofs);
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

अटल पूर्णांक init_agc(काष्ठा drxk_state *state, bool is_dtv)
अणु
	u16 ingain_tgt = 0;
	u16 ingain_tgt_min = 0;
	u16 ingain_tgt_max = 0;
	u16 clp_cyclen = 0;
	u16 clp_sum_min = 0;
	u16 clp_dir_to = 0;
	u16 sns_sum_min = 0;
	u16 sns_sum_max = 0;
	u16 clp_sum_max = 0;
	u16 sns_dir_to = 0;
	u16 ki_innergain_min = 0;
	u16 अगर_iaccu_hi_tgt = 0;
	u16 अगर_iaccu_hi_tgt_min = 0;
	u16 अगर_iaccu_hi_tgt_max = 0;
	u16 data = 0;
	u16 fast_clp_ctrl_delay = 0;
	u16 clp_ctrl_mode = 0;
	पूर्णांक status = 0;

	dprपूर्णांकk(1, "\n");

	/* Common settings */
	sns_sum_max = 1023;
	अगर_iaccu_hi_tgt_min = 2047;
	clp_cyclen = 500;
	clp_sum_max = 1023;

	/* AGCInit() not available क्रम DVBT; init करोne in microcode */
	अगर (!is_qam(state)) अणु
		pr_err("%s: mode %d is not DVB-C\n",
		       __func__, state->m_operation_mode);
		वापस -EINVAL;
	पूर्ण

	/* FIXME: Analog TV AGC require dअगरferent settings */

	/* Standard specअगरic settings */
	clp_sum_min = 8;
	clp_dir_to = (u16) -9;
	clp_ctrl_mode = 0;
	sns_sum_min = 8;
	sns_dir_to = (u16) -9;
	ki_innergain_min = (u16) -1030;
	अगर_iaccu_hi_tgt_max = 0x2380;
	अगर_iaccu_hi_tgt = 0x2380;
	ingain_tgt_min = 0x0511;
	ingain_tgt = 0x0511;
	ingain_tgt_max = 5119;
	fast_clp_ctrl_delay = state->m_qam_अगर_agc_cfg.fast_clip_ctrl_delay;

	status = ग_लिखो16(state, SCU_RAM_AGC_FAST_CLP_CTRL_DELAY__A,
			 fast_clp_ctrl_delay);
	अगर (status < 0)
		जाओ error;

	status = ग_लिखो16(state, SCU_RAM_AGC_CLP_CTRL_MODE__A, clp_ctrl_mode);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_INGAIN_TGT__A, ingain_tgt);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_INGAIN_TGT_MIN__A, ingain_tgt_min);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_INGAIN_TGT_MAX__A, ingain_tgt_max);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_IF_IACCU_HI_TGT_MIN__A,
			 अगर_iaccu_hi_tgt_min);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_IF_IACCU_HI_TGT_MAX__A,
			 अगर_iaccu_hi_tgt_max);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_IF_IACCU_HI__A, 0);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_IF_IACCU_LO__A, 0);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_RF_IACCU_HI__A, 0);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_RF_IACCU_LO__A, 0);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_CLP_SUM_MAX__A, clp_sum_max);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_SNS_SUM_MAX__A, sns_sum_max);
	अगर (status < 0)
		जाओ error;

	status = ग_लिखो16(state, SCU_RAM_AGC_KI_INNERGAIN_MIN__A,
			 ki_innergain_min);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_IF_IACCU_HI_TGT__A,
			 अगर_iaccu_hi_tgt);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_CLP_CYCLEN__A, clp_cyclen);
	अगर (status < 0)
		जाओ error;

	status = ग_लिखो16(state, SCU_RAM_AGC_RF_SNS_DEV_MAX__A, 1023);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_RF_SNS_DEV_MIN__A, (u16) -1023);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_FAST_SNS_CTRL_DELAY__A, 50);
	अगर (status < 0)
		जाओ error;

	status = ग_लिखो16(state, SCU_RAM_AGC_KI_MAXMINGAIN_TH__A, 20);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_CLP_SUM_MIN__A, clp_sum_min);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_SNS_SUM_MIN__A, sns_sum_min);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_CLP_सूची_TO__A, clp_dir_to);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_SNS_सूची_TO__A, sns_dir_to);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_KI_MINGAIN__A, 0x7fff);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_KI_MAXGAIN__A, 0x0);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_KI_MIN__A, 0x0117);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_KI_MAX__A, 0x0657);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_CLP_SUM__A, 0);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_CLP_CYCCNT__A, 0);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_CLP_सूची_WD__A, 0);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_CLP_सूची_STP__A, 1);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_SNS_SUM__A, 0);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_SNS_CYCCNT__A, 0);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_SNS_सूची_WD__A, 0);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_SNS_सूची_STP__A, 1);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_SNS_CYCLEN__A, 500);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_KI_CYCLEN__A, 500);
	अगर (status < 0)
		जाओ error;

	/* Initialize inner-loop KI gain factors */
	status = पढ़ो16(state, SCU_RAM_AGC_KI__A, &data);
	अगर (status < 0)
		जाओ error;

	data = 0x0657;
	data &= ~SCU_RAM_AGC_KI_RF__M;
	data |= (DRXK_KI_RAGC_QAM << SCU_RAM_AGC_KI_RF__B);
	data &= ~SCU_RAM_AGC_KI_IF__M;
	data |= (DRXK_KI_IAGC_QAM << SCU_RAM_AGC_KI_IF__B);

	status = ग_लिखो16(state, SCU_RAM_AGC_KI__A, data);
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

अटल पूर्णांक dvbtqam_get_acc_pkt_err(काष्ठा drxk_state *state, u16 *packet_err)
अणु
	पूर्णांक status;

	dprपूर्णांकk(1, "\n");
	अगर (packet_err == शून्य)
		status = ग_लिखो16(state, SCU_RAM_FEC_ACCUM_PKT_FAILURES__A, 0);
	अन्यथा
		status = पढ़ो16(state, SCU_RAM_FEC_ACCUM_PKT_FAILURES__A,
				packet_err);
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

अटल पूर्णांक dvbt_sc_command(काष्ठा drxk_state *state,
			 u16 cmd, u16 subcmd,
			 u16 param0, u16 param1, u16 param2,
			 u16 param3, u16 param4)
अणु
	u16 cur_cmd = 0;
	u16 err_code = 0;
	u16 retry_cnt = 0;
	u16 sc_exec = 0;
	पूर्णांक status;

	dprपूर्णांकk(1, "\n");
	status = पढ़ो16(state, OFDM_SC_COMM_EXEC__A, &sc_exec);
	अगर (sc_exec != 1) अणु
		/* SC is not running */
		status = -EINVAL;
	पूर्ण
	अगर (status < 0)
		जाओ error;

	/* Wait until sc is पढ़ोy to receive command */
	retry_cnt = 0;
	करो अणु
		usleep_range(1000, 2000);
		status = पढ़ो16(state, OFDM_SC_RA_RAM_CMD__A, &cur_cmd);
		retry_cnt++;
	पूर्ण जबतक ((cur_cmd != 0) && (retry_cnt < DRXK_MAX_RETRIES));
	अगर (retry_cnt >= DRXK_MAX_RETRIES && (status < 0))
		जाओ error;

	/* Write sub-command */
	चयन (cmd) अणु
		/* All commands using sub-cmd */
	हाल OFDM_SC_RA_RAM_CMD_PROC_START:
	हाल OFDM_SC_RA_RAM_CMD_SET_PREF_PARAM:
	हाल OFDM_SC_RA_RAM_CMD_PROGRAM_PARAM:
		status = ग_लिखो16(state, OFDM_SC_RA_RAM_CMD_ADDR__A, subcmd);
		अगर (status < 0)
			जाओ error;
		अवरोध;
	शेष:
		/* Do nothing */
		अवरोध;
	पूर्ण

	/* Write needed parameters and the command */
	status = 0;
	चयन (cmd) अणु
		/* All commands using 5 parameters */
		/* All commands using 4 parameters */
		/* All commands using 3 parameters */
		/* All commands using 2 parameters */
	हाल OFDM_SC_RA_RAM_CMD_PROC_START:
	हाल OFDM_SC_RA_RAM_CMD_SET_PREF_PARAM:
	हाल OFDM_SC_RA_RAM_CMD_PROGRAM_PARAM:
		status |= ग_लिखो16(state, OFDM_SC_RA_RAM_PARAM1__A, param1);
		fallthrough;	/* All commands using 1 parameters */
	हाल OFDM_SC_RA_RAM_CMD_SET_ECHO_TIMING:
	हाल OFDM_SC_RA_RAM_CMD_USER_IO:
		status |= ग_लिखो16(state, OFDM_SC_RA_RAM_PARAM0__A, param0);
		fallthrough;	/* All commands using 0 parameters */
	हाल OFDM_SC_RA_RAM_CMD_GET_OP_PARAM:
	हाल OFDM_SC_RA_RAM_CMD_शून्य:
		/* Write command */
		status |= ग_लिखो16(state, OFDM_SC_RA_RAM_CMD__A, cmd);
		अवरोध;
	शेष:
		/* Unknown command */
		status = -EINVAL;
	पूर्ण
	अगर (status < 0)
		जाओ error;

	/* Wait until sc is पढ़ोy processing command */
	retry_cnt = 0;
	करो अणु
		usleep_range(1000, 2000);
		status = पढ़ो16(state, OFDM_SC_RA_RAM_CMD__A, &cur_cmd);
		retry_cnt++;
	पूर्ण जबतक ((cur_cmd != 0) && (retry_cnt < DRXK_MAX_RETRIES));
	अगर (retry_cnt >= DRXK_MAX_RETRIES && (status < 0))
		जाओ error;

	/* Check क्रम illegal cmd */
	status = पढ़ो16(state, OFDM_SC_RA_RAM_CMD_ADDR__A, &err_code);
	अगर (err_code == 0xFFFF) अणु
		/* illegal command */
		status = -EINVAL;
	पूर्ण
	अगर (status < 0)
		जाओ error;

	/* Retrieve results parameters from SC */
	चयन (cmd) अणु
		/* All commands yielding 5 results */
		/* All commands yielding 4 results */
		/* All commands yielding 3 results */
		/* All commands yielding 2 results */
		/* All commands yielding 1 result */
	हाल OFDM_SC_RA_RAM_CMD_USER_IO:
	हाल OFDM_SC_RA_RAM_CMD_GET_OP_PARAM:
		status = पढ़ो16(state, OFDM_SC_RA_RAM_PARAM0__A, &(param0));
		अवरोध;
		/* All commands yielding 0 results */
	हाल OFDM_SC_RA_RAM_CMD_SET_ECHO_TIMING:
	हाल OFDM_SC_RA_RAM_CMD_SET_TIMER:
	हाल OFDM_SC_RA_RAM_CMD_PROC_START:
	हाल OFDM_SC_RA_RAM_CMD_SET_PREF_PARAM:
	हाल OFDM_SC_RA_RAM_CMD_PROGRAM_PARAM:
	हाल OFDM_SC_RA_RAM_CMD_शून्य:
		अवरोध;
	शेष:
		/* Unknown command */
		status = -EINVAL;
		अवरोध;
	पूर्ण			/* चयन (cmd->cmd) */
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

अटल पूर्णांक घातer_up_dvbt(काष्ठा drxk_state *state)
अणु
	क्रमागत drx_घातer_mode घातer_mode = DRX_POWER_UP;
	पूर्णांक status;

	dprपूर्णांकk(1, "\n");
	status = ctrl_घातer_mode(state, &घातer_mode);
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

अटल पूर्णांक dvbt_ctrl_set_inc_enable(काष्ठा drxk_state *state, bool *enabled)
अणु
	पूर्णांक status;

	dprपूर्णांकk(1, "\n");
	अगर (*enabled)
		status = ग_लिखो16(state, IQM_CF_BYPASSDET__A, 0);
	अन्यथा
		status = ग_लिखो16(state, IQM_CF_BYPASSDET__A, 1);
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

#घोषणा DEFAULT_FR_THRES_8K     4000
अटल पूर्णांक dvbt_ctrl_set_fr_enable(काष्ठा drxk_state *state, bool *enabled)
अणु

	पूर्णांक status;

	dprपूर्णांकk(1, "\n");
	अगर (*enabled) अणु
		/* ग_लिखो mask to 1 */
		status = ग_लिखो16(state, OFDM_SC_RA_RAM_FR_THRES_8K__A,
				   DEFAULT_FR_THRES_8K);
	पूर्ण अन्यथा अणु
		/* ग_लिखो mask to 0 */
		status = ग_लिखो16(state, OFDM_SC_RA_RAM_FR_THRES_8K__A, 0);
	पूर्ण
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);

	वापस status;
पूर्ण

अटल पूर्णांक dvbt_ctrl_set_echo_threshold(काष्ठा drxk_state *state,
				काष्ठा drxk_cfg_dvbt_echo_thres_t *echo_thres)
अणु
	u16 data = 0;
	पूर्णांक status;

	dprपूर्णांकk(1, "\n");
	status = पढ़ो16(state, OFDM_SC_RA_RAM_ECHO_THRES__A, &data);
	अगर (status < 0)
		जाओ error;

	चयन (echo_thres->fft_mode) अणु
	हाल DRX_FFTMODE_2K:
		data &= ~OFDM_SC_RA_RAM_ECHO_THRES_2K__M;
		data |= ((echo_thres->threshold <<
			OFDM_SC_RA_RAM_ECHO_THRES_2K__B)
			& (OFDM_SC_RA_RAM_ECHO_THRES_2K__M));
		अवरोध;
	हाल DRX_FFTMODE_8K:
		data &= ~OFDM_SC_RA_RAM_ECHO_THRES_8K__M;
		data |= ((echo_thres->threshold <<
			OFDM_SC_RA_RAM_ECHO_THRES_8K__B)
			& (OFDM_SC_RA_RAM_ECHO_THRES_8K__M));
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	status = ग_लिखो16(state, OFDM_SC_RA_RAM_ECHO_THRES__A, data);
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

अटल पूर्णांक dvbt_ctrl_set_sqi_speed(काष्ठा drxk_state *state,
			       क्रमागत drxk_cfg_dvbt_sqi_speed *speed)
अणु
	पूर्णांक status = -EINVAL;

	dprपूर्णांकk(1, "\n");

	चयन (*speed) अणु
	हाल DRXK_DVBT_SQI_SPEED_FAST:
	हाल DRXK_DVBT_SQI_SPEED_MEDIUM:
	हाल DRXK_DVBT_SQI_SPEED_SLOW:
		अवरोध;
	शेष:
		जाओ error;
	पूर्ण
	status = ग_लिखो16(state, SCU_RAM_FEC_PRE_RS_BER_FILTER_SH__A,
			   (u16) *speed);
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

/*============================================================================*/

/*
* \मrief Activate DVBT specअगरic presets
* \param demod instance of demodulator.
* \लeturn DRXStatus_t.
*
* Called in DVBTSetStandard
*
*/
अटल पूर्णांक dvbt_activate_presets(काष्ठा drxk_state *state)
अणु
	पूर्णांक status;
	bool setincenable = false;
	bool setfrenable = true;

	काष्ठा drxk_cfg_dvbt_echo_thres_t echo_thres2k = अणु 0, DRX_FFTMODE_2K पूर्ण;
	काष्ठा drxk_cfg_dvbt_echo_thres_t echo_thres8k = अणु 0, DRX_FFTMODE_8K पूर्ण;

	dprपूर्णांकk(1, "\n");
	status = dvbt_ctrl_set_inc_enable(state, &setincenable);
	अगर (status < 0)
		जाओ error;
	status = dvbt_ctrl_set_fr_enable(state, &setfrenable);
	अगर (status < 0)
		जाओ error;
	status = dvbt_ctrl_set_echo_threshold(state, &echo_thres2k);
	अगर (status < 0)
		जाओ error;
	status = dvbt_ctrl_set_echo_threshold(state, &echo_thres8k);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_AGC_INGAIN_TGT_MAX__A,
			 state->m_dvbt_अगर_agc_cfg.ingain_tgt_max);
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

/*============================================================================*/

/*
* \मrief Initialize channelचयन-independent settings क्रम DVBT.
* \param demod instance of demodulator.
* \लeturn DRXStatus_t.
*
* For ROM code channel filter taps are loaded from the bootloader. For microcode
* the DVB-T taps from the drxk_filters.h are used.
*/
अटल पूर्णांक set_dvbt_standard(काष्ठा drxk_state *state,
			   क्रमागत operation_mode o_mode)
अणु
	u16 cmd_result = 0;
	u16 data = 0;
	पूर्णांक status;

	dprपूर्णांकk(1, "\n");

	घातer_up_dvbt(state);
	/* added antenna चयन */
	चयन_antenna_to_dvbt(state);
	/* send OFDM reset command */
	status = scu_command(state,
			     SCU_RAM_COMMAND_STANDARD_OFDM
			     | SCU_RAM_COMMAND_CMD_DEMOD_RESET,
			     0, शून्य, 1, &cmd_result);
	अगर (status < 0)
		जाओ error;

	/* send OFDM setenv command */
	status = scu_command(state, SCU_RAM_COMMAND_STANDARD_OFDM
			     | SCU_RAM_COMMAND_CMD_DEMOD_SET_ENV,
			     0, शून्य, 1, &cmd_result);
	अगर (status < 0)
		जाओ error;

	/* reset datapath क्रम OFDM, processors first */
	status = ग_लिखो16(state, OFDM_SC_COMM_EXEC__A, OFDM_SC_COMM_EXEC_STOP);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, OFDM_LC_COMM_EXEC__A, OFDM_LC_COMM_EXEC_STOP);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, IQM_COMM_EXEC__A, IQM_COMM_EXEC_B_STOP);
	अगर (status < 0)
		जाओ error;

	/* IQM setup */
	/* synchronize on ofdstate->m_festart */
	status = ग_लिखो16(state, IQM_AF_UPD_SEL__A, 1);
	अगर (status < 0)
		जाओ error;
	/* winकरोw size क्रम clipping ADC detection */
	status = ग_लिखो16(state, IQM_AF_CLP_LEN__A, 0);
	अगर (status < 0)
		जाओ error;
	/* winकरोw size क्रम क्रम sense pre-SAW detection */
	status = ग_लिखो16(state, IQM_AF_SNS_LEN__A, 0);
	अगर (status < 0)
		जाओ error;
	/* sense threshold क्रम sense pre-SAW detection */
	status = ग_लिखो16(state, IQM_AF_AMUX__A, IQM_AF_AMUX_SIGNAL2ADC);
	अगर (status < 0)
		जाओ error;
	status = set_iqm_af(state, true);
	अगर (status < 0)
		जाओ error;

	status = ग_लिखो16(state, IQM_AF_AGC_RF__A, 0);
	अगर (status < 0)
		जाओ error;

	/* Impulse noise cruncher setup */
	status = ग_लिखो16(state, IQM_AF_INC_LCT__A, 0);	/* crunch in IQM_CF */
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, IQM_CF_DET_LCT__A, 0);	/* detect in IQM_CF */
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, IQM_CF_WND_LEN__A, 3);	/* peak detector winकरोw length */
	अगर (status < 0)
		जाओ error;

	status = ग_लिखो16(state, IQM_RC_STRETCH__A, 16);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, IQM_CF_OUT_ENA__A, 0x4); /* enable output 2 */
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, IQM_CF_DS_ENA__A, 0x4);	/* decimate output 2 */
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, IQM_CF_SCALE__A, 1600);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, IQM_CF_SCALE_SH__A, 0);
	अगर (status < 0)
		जाओ error;

	/* भव clipping threshold क्रम clipping ADC detection */
	status = ग_लिखो16(state, IQM_AF_CLP_TH__A, 448);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, IQM_CF_DATATH__A, 495);	/* crunching threshold */
	अगर (status < 0)
		जाओ error;

	status = bl_chain_cmd(state, DRXK_BL_ROM_OFFSET_TAPS_DVBT,
			      DRXK_BLCC_NR_ELEMENTS_TAPS, DRXK_BLC_TIMEOUT);
	अगर (status < 0)
		जाओ error;

	status = ग_लिखो16(state, IQM_CF_PKDTH__A, 2);	/* peak detector threshold */
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, IQM_CF_POW_MEAS_LEN__A, 2);
	अगर (status < 0)
		जाओ error;
	/* enable घातer measurement पूर्णांकerrupt */
	status = ग_लिखो16(state, IQM_CF_COMM_INT_MSK__A, 1);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, IQM_COMM_EXEC__A, IQM_COMM_EXEC_B_ACTIVE);
	अगर (status < 0)
		जाओ error;

	/* IQM will not be reset from here, sync ADC and update/init AGC */
	status = adc_synchronization(state);
	अगर (status < 0)
		जाओ error;
	status = set_pre_saw(state, &state->m_dvbt_pre_saw_cfg);
	अगर (status < 0)
		जाओ error;

	/* Halt SCU to enable safe non-atomic accesses */
	status = ग_लिखो16(state, SCU_COMM_EXEC__A, SCU_COMM_EXEC_HOLD);
	अगर (status < 0)
		जाओ error;

	status = set_agc_rf(state, &state->m_dvbt_rf_agc_cfg, true);
	अगर (status < 0)
		जाओ error;
	status = set_agc_अगर(state, &state->m_dvbt_अगर_agc_cfg, true);
	अगर (status < 0)
		जाओ error;

	/* Set Noise Estimation notch width and enable DC fix */
	status = पढ़ो16(state, OFDM_SC_RA_RAM_CONFIG__A, &data);
	अगर (status < 0)
		जाओ error;
	data |= OFDM_SC_RA_RAM_CONFIG_NE_FIX_ENABLE__M;
	status = ग_लिखो16(state, OFDM_SC_RA_RAM_CONFIG__A, data);
	अगर (status < 0)
		जाओ error;

	/* Activate SCU to enable SCU commands */
	status = ग_लिखो16(state, SCU_COMM_EXEC__A, SCU_COMM_EXEC_ACTIVE);
	अगर (status < 0)
		जाओ error;

	अगर (!state->m_drxk_a3_rom_code) अणु
		/* AGCInit() is not करोne क्रम DVBT, so set agcfast_clip_ctrl_delay  */
		status = ग_लिखो16(state, SCU_RAM_AGC_FAST_CLP_CTRL_DELAY__A,
				 state->m_dvbt_अगर_agc_cfg.fast_clip_ctrl_delay);
		अगर (status < 0)
			जाओ error;
	पूर्ण

	/* OFDM_SC setup */
#अगर_घोषित COMPILE_FOR_NONRT
	status = ग_लिखो16(state, OFDM_SC_RA_RAM_BE_OPT_DELAY__A, 1);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, OFDM_SC_RA_RAM_BE_OPT_INIT_DELAY__A, 2);
	अगर (status < 0)
		जाओ error;
#पूर्ण_अगर

	/* FEC setup */
	status = ग_लिखो16(state, FEC_DI_INPUT_CTL__A, 1);	/* OFDM input */
	अगर (status < 0)
		जाओ error;


#अगर_घोषित COMPILE_FOR_NONRT
	status = ग_लिखो16(state, FEC_RS_MEASUREMENT_PERIOD__A, 0x400);
	अगर (status < 0)
		जाओ error;
#अन्यथा
	status = ग_लिखो16(state, FEC_RS_MEASUREMENT_PERIOD__A, 0x1000);
	अगर (status < 0)
		जाओ error;
#पूर्ण_अगर
	status = ग_लिखो16(state, FEC_RS_MEASUREMENT_PRESCALE__A, 0x0001);
	अगर (status < 0)
		जाओ error;

	/* Setup MPEG bus */
	status = mpegts_dto_setup(state, OM_DVBT);
	अगर (status < 0)
		जाओ error;
	/* Set DVBT Presets */
	status = dvbt_activate_presets(state);
	अगर (status < 0)
		जाओ error;

error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

/*============================================================================*/
/*
* \मrief start dvbt demodulating क्रम channel.
* \param demod instance of demodulator.
* \लeturn DRXStatus_t.
*/
अटल पूर्णांक dvbt_start(काष्ठा drxk_state *state)
अणु
	u16 param1;
	पूर्णांक status;
	/* drxk_ofdm_sc_cmd_t scCmd; */

	dprपूर्णांकk(1, "\n");
	/* start correct processes to get in lock */
	/* DRXK: OFDM_SC_RA_RAM_PROC_LOCKTRACK is no दीर्घer in mapfile! */
	param1 = OFDM_SC_RA_RAM_LOCKTRACK_MIN;
	status = dvbt_sc_command(state, OFDM_SC_RA_RAM_CMD_PROC_START, 0,
				 OFDM_SC_RA_RAM_SW_EVENT_RUN_NMASK__M, param1,
				 0, 0, 0);
	अगर (status < 0)
		जाओ error;
	/* start FEC OC */
	status = mpegts_start(state);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, FEC_COMM_EXEC__A, FEC_COMM_EXEC_ACTIVE);
	अगर (status < 0)
		जाओ error;
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण


/*============================================================================*/

/*
* \मrief Set up dvbt demodulator क्रम channel.
* \param demod instance of demodulator.
* \लeturn DRXStatus_t.
* // original DVBTSetChannel()
*/
अटल पूर्णांक set_dvbt(काष्ठा drxk_state *state, u16 पूर्णांकermediate_freqk_hz,
		   s32 tuner_freq_offset)
अणु
	u16 cmd_result = 0;
	u16 transmission_params = 0;
	u16 operation_mode = 0;
	u32 iqm_rc_rate_ofs = 0;
	u32 bandwidth = 0;
	u16 param1;
	पूर्णांक status;

	dprपूर्णांकk(1, "IF =%d, TFO = %d\n",
		पूर्णांकermediate_freqk_hz, tuner_freq_offset);

	status = scu_command(state, SCU_RAM_COMMAND_STANDARD_OFDM
			    | SCU_RAM_COMMAND_CMD_DEMOD_STOP,
			    0, शून्य, 1, &cmd_result);
	अगर (status < 0)
		जाओ error;

	/* Halt SCU to enable safe non-atomic accesses */
	status = ग_लिखो16(state, SCU_COMM_EXEC__A, SCU_COMM_EXEC_HOLD);
	अगर (status < 0)
		जाओ error;

	/* Stop processors */
	status = ग_लिखो16(state, OFDM_SC_COMM_EXEC__A, OFDM_SC_COMM_EXEC_STOP);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, OFDM_LC_COMM_EXEC__A, OFDM_LC_COMM_EXEC_STOP);
	अगर (status < 0)
		जाओ error;

	/* Mandatory fix, always stop CP, required to set spl offset back to
		hardware शेष (is set to 0 by ucode during pilot detection */
	status = ग_लिखो16(state, OFDM_CP_COMM_EXEC__A, OFDM_CP_COMM_EXEC_STOP);
	अगर (status < 0)
		जाओ error;

	/*== Write channel settings to device ================================*/

	/* mode */
	चयन (state->props.transmission_mode) अणु
	हाल TRANSMISSION_MODE_AUTO:
	शेष:
		operation_mode |= OFDM_SC_RA_RAM_OP_AUTO_MODE__M;
		fallthrough;	/* try first guess DRX_FFTMODE_8K */
	हाल TRANSMISSION_MODE_8K:
		transmission_params |= OFDM_SC_RA_RAM_OP_PARAM_MODE_8K;
		अवरोध;
	हाल TRANSMISSION_MODE_2K:
		transmission_params |= OFDM_SC_RA_RAM_OP_PARAM_MODE_2K;
		अवरोध;
	पूर्ण

	/* guard */
	चयन (state->props.guard_पूर्णांकerval) अणु
	शेष:
	हाल GUARD_INTERVAL_AUTO:
		operation_mode |= OFDM_SC_RA_RAM_OP_AUTO_GUARD__M;
		fallthrough;	/* try first guess DRX_GUARD_1DIV4 */
	हाल GUARD_INTERVAL_1_4:
		transmission_params |= OFDM_SC_RA_RAM_OP_PARAM_GUARD_4;
		अवरोध;
	हाल GUARD_INTERVAL_1_32:
		transmission_params |= OFDM_SC_RA_RAM_OP_PARAM_GUARD_32;
		अवरोध;
	हाल GUARD_INTERVAL_1_16:
		transmission_params |= OFDM_SC_RA_RAM_OP_PARAM_GUARD_16;
		अवरोध;
	हाल GUARD_INTERVAL_1_8:
		transmission_params |= OFDM_SC_RA_RAM_OP_PARAM_GUARD_8;
		अवरोध;
	पूर्ण

	/* hierarchy */
	चयन (state->props.hierarchy) अणु
	हाल HIERARCHY_AUTO:
	हाल HIERARCHY_NONE:
	शेष:
		operation_mode |= OFDM_SC_RA_RAM_OP_AUTO_HIER__M;
		/* try first guess SC_RA_RAM_OP_PARAM_HIER_NO */
		/* transmission_params |= OFDM_SC_RA_RAM_OP_PARAM_HIER_NO; */
		fallthrough;
	हाल HIERARCHY_1:
		transmission_params |= OFDM_SC_RA_RAM_OP_PARAM_HIER_A1;
		अवरोध;
	हाल HIERARCHY_2:
		transmission_params |= OFDM_SC_RA_RAM_OP_PARAM_HIER_A2;
		अवरोध;
	हाल HIERARCHY_4:
		transmission_params |= OFDM_SC_RA_RAM_OP_PARAM_HIER_A4;
		अवरोध;
	पूर्ण


	/* modulation */
	चयन (state->props.modulation) अणु
	हाल QAM_AUTO:
	शेष:
		operation_mode |= OFDM_SC_RA_RAM_OP_AUTO_CONST__M;
		fallthrough;	/* try first guess DRX_CONSTELLATION_QAM64 */
	हाल QAM_64:
		transmission_params |= OFDM_SC_RA_RAM_OP_PARAM_CONST_QAM64;
		अवरोध;
	हाल QPSK:
		transmission_params |= OFDM_SC_RA_RAM_OP_PARAM_CONST_QPSK;
		अवरोध;
	हाल QAM_16:
		transmission_params |= OFDM_SC_RA_RAM_OP_PARAM_CONST_QAM16;
		अवरोध;
	पूर्ण
#अगर 0
	/* No hierarchical channels support in BDA */
	/* Priority (only क्रम hierarchical channels) */
	चयन (channel->priority) अणु
	हाल DRX_PRIORITY_LOW:
		transmission_params |= OFDM_SC_RA_RAM_OP_PARAM_PRIO_LO;
		WR16(dev_addr, OFDM_EC_SB_PRIOR__A,
			OFDM_EC_SB_PRIOR_LO);
		अवरोध;
	हाल DRX_PRIORITY_HIGH:
		transmission_params |= OFDM_SC_RA_RAM_OP_PARAM_PRIO_HI;
		WR16(dev_addr, OFDM_EC_SB_PRIOR__A,
			OFDM_EC_SB_PRIOR_HI));
		अवरोध;
	हाल DRX_PRIORITY_UNKNOWN:
	शेष:
		status = -EINVAL;
		जाओ error;
	पूर्ण
#अन्यथा
	/* Set Priority high */
	transmission_params |= OFDM_SC_RA_RAM_OP_PARAM_PRIO_HI;
	status = ग_लिखो16(state, OFDM_EC_SB_PRIOR__A, OFDM_EC_SB_PRIOR_HI);
	अगर (status < 0)
		जाओ error;
#पूर्ण_अगर

	/* coderate */
	चयन (state->props.code_rate_HP) अणु
	हाल FEC_AUTO:
	शेष:
		operation_mode |= OFDM_SC_RA_RAM_OP_AUTO_RATE__M;
		fallthrough;	/* try first guess DRX_CODERATE_2DIV3 */
	हाल FEC_2_3:
		transmission_params |= OFDM_SC_RA_RAM_OP_PARAM_RATE_2_3;
		अवरोध;
	हाल FEC_1_2:
		transmission_params |= OFDM_SC_RA_RAM_OP_PARAM_RATE_1_2;
		अवरोध;
	हाल FEC_3_4:
		transmission_params |= OFDM_SC_RA_RAM_OP_PARAM_RATE_3_4;
		अवरोध;
	हाल FEC_5_6:
		transmission_params |= OFDM_SC_RA_RAM_OP_PARAM_RATE_5_6;
		अवरोध;
	हाल FEC_7_8:
		transmission_params |= OFDM_SC_RA_RAM_OP_PARAM_RATE_7_8;
		अवरोध;
	पूर्ण

	/*
	 * SAW filter selection: normally not necessary, but अगर wanted
	 * the application can select a SAW filter via the driver by
	 * using UIOs
	 */

	/* First determine real bandwidth (Hz) */
	/* Also set delay क्रम impulse noise cruncher */
	/*
	 * Also set parameters क्रम EC_OC fix, note EC_OC_REG_TMD_HIL_MAR is
	 * changed by SC क्रम fix क्रम some 8K,1/8 guard but is restored by
	 * InitEC and ResetEC functions
	 */
	चयन (state->props.bandwidth_hz) अणु
	हाल 0:
		state->props.bandwidth_hz = 8000000;
		fallthrough;
	हाल 8000000:
		bandwidth = DRXK_BANDWIDTH_8MHZ_IN_HZ;
		status = ग_लिखो16(state, OFDM_SC_RA_RAM_SRMM_FIX_FACT_8K__A,
				 3052);
		अगर (status < 0)
			जाओ error;
		/* cochannel protection क्रम PAL 8 MHz */
		status = ग_लिखो16(state, OFDM_SC_RA_RAM_NI_INIT_8K_PER_LEFT__A,
				 7);
		अगर (status < 0)
			जाओ error;
		status = ग_लिखो16(state, OFDM_SC_RA_RAM_NI_INIT_8K_PER_RIGHT__A,
				 7);
		अगर (status < 0)
			जाओ error;
		status = ग_लिखो16(state, OFDM_SC_RA_RAM_NI_INIT_2K_PER_LEFT__A,
				 7);
		अगर (status < 0)
			जाओ error;
		status = ग_लिखो16(state, OFDM_SC_RA_RAM_NI_INIT_2K_PER_RIGHT__A,
				 1);
		अगर (status < 0)
			जाओ error;
		अवरोध;
	हाल 7000000:
		bandwidth = DRXK_BANDWIDTH_7MHZ_IN_HZ;
		status = ग_लिखो16(state, OFDM_SC_RA_RAM_SRMM_FIX_FACT_8K__A,
				 3491);
		अगर (status < 0)
			जाओ error;
		/* cochannel protection क्रम PAL 7 MHz */
		status = ग_लिखो16(state, OFDM_SC_RA_RAM_NI_INIT_8K_PER_LEFT__A,
				 8);
		अगर (status < 0)
			जाओ error;
		status = ग_लिखो16(state, OFDM_SC_RA_RAM_NI_INIT_8K_PER_RIGHT__A,
				 8);
		अगर (status < 0)
			जाओ error;
		status = ग_लिखो16(state, OFDM_SC_RA_RAM_NI_INIT_2K_PER_LEFT__A,
				 4);
		अगर (status < 0)
			जाओ error;
		status = ग_लिखो16(state, OFDM_SC_RA_RAM_NI_INIT_2K_PER_RIGHT__A,
				 1);
		अगर (status < 0)
			जाओ error;
		अवरोध;
	हाल 6000000:
		bandwidth = DRXK_BANDWIDTH_6MHZ_IN_HZ;
		status = ग_लिखो16(state, OFDM_SC_RA_RAM_SRMM_FIX_FACT_8K__A,
				 4073);
		अगर (status < 0)
			जाओ error;
		/* cochannel protection क्रम NTSC 6 MHz */
		status = ग_लिखो16(state, OFDM_SC_RA_RAM_NI_INIT_8K_PER_LEFT__A,
				 19);
		अगर (status < 0)
			जाओ error;
		status = ग_लिखो16(state, OFDM_SC_RA_RAM_NI_INIT_8K_PER_RIGHT__A,
				 19);
		अगर (status < 0)
			जाओ error;
		status = ग_लिखो16(state, OFDM_SC_RA_RAM_NI_INIT_2K_PER_LEFT__A,
				 14);
		अगर (status < 0)
			जाओ error;
		status = ग_लिखो16(state, OFDM_SC_RA_RAM_NI_INIT_2K_PER_RIGHT__A,
				 1);
		अगर (status < 0)
			जाओ error;
		अवरोध;
	शेष:
		status = -EINVAL;
		जाओ error;
	पूर्ण

	अगर (iqm_rc_rate_ofs == 0) अणु
		/* Now compute IQM_RC_RATE_OFS
			(((SysFreq/BandWidth)/2)/2) -1) * 2^23)
			=>
			((SysFreq / BandWidth) * (2^21)) - (2^23)
			*/
		/* (SysFreq / BandWidth) * (2^28)  */
		/*
		 * निश्चित (MAX(sysClk)/MIN(bandwidth) < 16)
		 *	=> निश्चित(MAX(sysClk) < 16*MIN(bandwidth))
		 *	=> निश्चित(109714272 > 48000000) = true
		 * so Frac 28 can be used
		 */
		iqm_rc_rate_ofs = Frac28a((u32)
					((state->m_sys_घड़ी_freq *
						1000) / 3), bandwidth);
		/* (SysFreq / BandWidth) * (2^21), rounding beक्रमe truncating */
		अगर ((iqm_rc_rate_ofs & 0x7fL) >= 0x40)
			iqm_rc_rate_ofs += 0x80L;
		iqm_rc_rate_ofs = iqm_rc_rate_ofs >> 7;
		/* ((SysFreq / BandWidth) * (2^21)) - (2^23)  */
		iqm_rc_rate_ofs = iqm_rc_rate_ofs - (1 << 23);
	पूर्ण

	iqm_rc_rate_ofs &=
		((((u32) IQM_RC_RATE_OFS_HI__M) <<
		IQM_RC_RATE_OFS_LO__W) | IQM_RC_RATE_OFS_LO__M);
	status = ग_लिखो32(state, IQM_RC_RATE_OFS_LO__A, iqm_rc_rate_ofs);
	अगर (status < 0)
		जाओ error;

	/* Bandwidth setting करोne */

#अगर 0
	status = dvbt_set_frequency_shअगरt(demod, channel, tuner_offset);
	अगर (status < 0)
		जाओ error;
#पूर्ण_अगर
	status = set_frequency_shअगरter(state, पूर्णांकermediate_freqk_hz,
				       tuner_freq_offset, true);
	अगर (status < 0)
		जाओ error;

	/*== start SC, ग_लिखो channel settings to SC ==========================*/

	/* Activate SCU to enable SCU commands */
	status = ग_लिखो16(state, SCU_COMM_EXEC__A, SCU_COMM_EXEC_ACTIVE);
	अगर (status < 0)
		जाओ error;

	/* Enable SC after setting all other parameters */
	status = ग_लिखो16(state, OFDM_SC_COMM_STATE__A, 0);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, OFDM_SC_COMM_EXEC__A, 1);
	अगर (status < 0)
		जाओ error;


	status = scu_command(state, SCU_RAM_COMMAND_STANDARD_OFDM
			     | SCU_RAM_COMMAND_CMD_DEMOD_START,
			     0, शून्य, 1, &cmd_result);
	अगर (status < 0)
		जाओ error;

	/* Write SC parameter रेजिस्टरs, set all AUTO flags in operation mode */
	param1 = (OFDM_SC_RA_RAM_OP_AUTO_MODE__M |
			OFDM_SC_RA_RAM_OP_AUTO_GUARD__M |
			OFDM_SC_RA_RAM_OP_AUTO_CONST__M |
			OFDM_SC_RA_RAM_OP_AUTO_HIER__M |
			OFDM_SC_RA_RAM_OP_AUTO_RATE__M);
	status = dvbt_sc_command(state, OFDM_SC_RA_RAM_CMD_SET_PREF_PARAM,
				0, transmission_params, param1, 0, 0, 0);
	अगर (status < 0)
		जाओ error;

	अगर (!state->m_drxk_a3_rom_code)
		status = dvbt_ctrl_set_sqi_speed(state, &state->m_sqi_speed);
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);

	वापस status;
पूर्ण


/*============================================================================*/

/*
* \मrief Retrieve lock status .
* \param demod    Poपूर्णांकer to demodulator instance.
* \param lockStat Poपूर्णांकer to lock status काष्ठाure.
* \लeturn DRXStatus_t.
*
*/
अटल पूर्णांक get_dvbt_lock_status(काष्ठा drxk_state *state, u32 *p_lock_status)
अणु
	पूर्णांक status;
	स्थिर u16 mpeg_lock_mask = (OFDM_SC_RA_RAM_LOCK_MPEG__M |
				    OFDM_SC_RA_RAM_LOCK_FEC__M);
	स्थिर u16 fec_lock_mask = (OFDM_SC_RA_RAM_LOCK_FEC__M);
	स्थिर u16 demod_lock_mask = OFDM_SC_RA_RAM_LOCK_DEMOD__M;

	u16 sc_ra_ram_lock = 0;
	u16 sc_comm_exec = 0;

	dprपूर्णांकk(1, "\n");

	*p_lock_status = NOT_LOCKED;
	/* driver 0.9.0 */
	/* Check अगर SC is running */
	status = पढ़ो16(state, OFDM_SC_COMM_EXEC__A, &sc_comm_exec);
	अगर (status < 0)
		जाओ end;
	अगर (sc_comm_exec == OFDM_SC_COMM_EXEC_STOP)
		जाओ end;

	status = पढ़ो16(state, OFDM_SC_RA_RAM_LOCK__A, &sc_ra_ram_lock);
	अगर (status < 0)
		जाओ end;

	अगर ((sc_ra_ram_lock & mpeg_lock_mask) == mpeg_lock_mask)
		*p_lock_status = MPEG_LOCK;
	अन्यथा अगर ((sc_ra_ram_lock & fec_lock_mask) == fec_lock_mask)
		*p_lock_status = FEC_LOCK;
	अन्यथा अगर ((sc_ra_ram_lock & demod_lock_mask) == demod_lock_mask)
		*p_lock_status = DEMOD_LOCK;
	अन्यथा अगर (sc_ra_ram_lock & OFDM_SC_RA_RAM_LOCK_NODVBT__M)
		*p_lock_status = NEVER_LOCK;
end:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);

	वापस status;
पूर्ण

अटल पूर्णांक घातer_up_qam(काष्ठा drxk_state *state)
अणु
	क्रमागत drx_घातer_mode घातer_mode = DRXK_POWER_DOWN_OFDM;
	पूर्णांक status;

	dprपूर्णांकk(1, "\n");
	status = ctrl_घातer_mode(state, &घातer_mode);
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);

	वापस status;
पूर्ण


/* Power Down QAM */
अटल पूर्णांक घातer_करोwn_qam(काष्ठा drxk_state *state)
अणु
	u16 data = 0;
	u16 cmd_result;
	पूर्णांक status = 0;

	dprपूर्णांकk(1, "\n");
	status = पढ़ो16(state, SCU_COMM_EXEC__A, &data);
	अगर (status < 0)
		जाओ error;
	अगर (data == SCU_COMM_EXEC_ACTIVE) अणु
		/*
			STOP demodulator
			QAM and HW blocks
			*/
		/* stop all comstate->m_exec */
		status = ग_लिखो16(state, QAM_COMM_EXEC__A, QAM_COMM_EXEC_STOP);
		अगर (status < 0)
			जाओ error;
		status = scu_command(state, SCU_RAM_COMMAND_STANDARD_QAM
				     | SCU_RAM_COMMAND_CMD_DEMOD_STOP,
				     0, शून्य, 1, &cmd_result);
		अगर (status < 0)
			जाओ error;
	पूर्ण
	/* घातerकरोwn AFE                   */
	status = set_iqm_af(state, false);

error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);

	वापस status;
पूर्ण

/*============================================================================*/

/*
* \मrief Setup of the QAM Measurement पूर्णांकervals क्रम संकेत quality
* \param demod instance of demod.
* \param modulation current modulation.
* \लeturn DRXStatus_t.
*
*  NOTE:
*  Take पूर्णांकo account that क्रम certain settings the errorcounters can overflow.
*  The implementation करोes not check this.
*
*/
अटल पूर्णांक set_qam_measurement(काष्ठा drxk_state *state,
			     क्रमागत e_drxk_स्थिरellation modulation,
			     u32 symbol_rate)
अणु
	u32 fec_bits_desired = 0;	/* BER accounting period */
	u32 fec_rs_period_total = 0;	/* Total period */
	u16 fec_rs_prescale = 0;	/* ReedSolomon Measurement Prescale */
	u16 fec_rs_period = 0;	/* Value क्रम corresponding I2C रेजिस्टर */
	पूर्णांक status = 0;

	dprपूर्णांकk(1, "\n");

	fec_rs_prescale = 1;
	/* fec_bits_desired = symbol_rate [kHz] *
		FrameLenght [ms] *
		(modulation + 1) *
		SyncLoss (== 1) *
		ViterbiLoss (==1)
		*/
	चयन (modulation) अणु
	हाल DRX_CONSTELLATION_QAM16:
		fec_bits_desired = 4 * symbol_rate;
		अवरोध;
	हाल DRX_CONSTELLATION_QAM32:
		fec_bits_desired = 5 * symbol_rate;
		अवरोध;
	हाल DRX_CONSTELLATION_QAM64:
		fec_bits_desired = 6 * symbol_rate;
		अवरोध;
	हाल DRX_CONSTELLATION_QAM128:
		fec_bits_desired = 7 * symbol_rate;
		अवरोध;
	हाल DRX_CONSTELLATION_QAM256:
		fec_bits_desired = 8 * symbol_rate;
		अवरोध;
	शेष:
		status = -EINVAL;
	पूर्ण
	अगर (status < 0)
		जाओ error;

	fec_bits_desired /= 1000;	/* symbol_rate [Hz] -> symbol_rate [kHz] */
	fec_bits_desired *= 500;	/* meas. period [ms] */

	/* Annex A/C: bits/RsPeriod = 204 * 8 = 1632 */
	/* fec_rs_period_total = fec_bits_desired / 1632 */
	fec_rs_period_total = (fec_bits_desired / 1632UL) + 1;	/* roughly उच्चमान */

	/* fec_rs_period_total =  fec_rs_prescale * fec_rs_period  */
	fec_rs_prescale = 1 + (u16) (fec_rs_period_total >> 16);
	अगर (fec_rs_prescale == 0) अणु
		/* Divide by zero (though impossible) */
		status = -EINVAL;
		अगर (status < 0)
			जाओ error;
	पूर्ण
	fec_rs_period =
		((u16) fec_rs_period_total +
		(fec_rs_prescale >> 1)) / fec_rs_prescale;

	/* ग_लिखो corresponding रेजिस्टरs */
	status = ग_लिखो16(state, FEC_RS_MEASUREMENT_PERIOD__A, fec_rs_period);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, FEC_RS_MEASUREMENT_PRESCALE__A,
			 fec_rs_prescale);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, FEC_OC_SNC_FAIL_PERIOD__A, fec_rs_period);
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

अटल पूर्णांक set_qam16(काष्ठा drxk_state *state)
अणु
	पूर्णांक status = 0;

	dprपूर्णांकk(1, "\n");
	/* QAM Equalizer Setup */
	/* Equalizer */
	status = ग_लिखो16(state, SCU_RAM_QAM_EQ_CMA_RAD0__A, 13517);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_EQ_CMA_RAD1__A, 13517);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_EQ_CMA_RAD2__A, 13517);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_EQ_CMA_RAD3__A, 13517);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_EQ_CMA_RAD4__A, 13517);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_EQ_CMA_RAD5__A, 13517);
	अगर (status < 0)
		जाओ error;
	/* Decision Feedback Equalizer */
	status = ग_लिखो16(state, QAM_DQ_QUAL_FUN0__A, 2);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_DQ_QUAL_FUN1__A, 2);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_DQ_QUAL_FUN2__A, 2);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_DQ_QUAL_FUN3__A, 2);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_DQ_QUAL_FUN4__A, 2);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_DQ_QUAL_FUN5__A, 0);
	अगर (status < 0)
		जाओ error;

	status = ग_लिखो16(state, QAM_SY_SYNC_HWM__A, 5);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_SY_SYNC_AWM__A, 4);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_SY_SYNC_LWM__A, 3);
	अगर (status < 0)
		जाओ error;

	/* QAM Slicer Settings */
	status = ग_लिखो16(state, SCU_RAM_QAM_SL_SIG_POWER__A,
			 DRXK_QAM_SL_SIG_POWER_QAM16);
	अगर (status < 0)
		जाओ error;

	/* QAM Loop Controller Coeficients */
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CA_FINE__A, 15);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CA_COARSE__A, 40);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_EP_FINE__A, 12);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_EP_MEDIUM__A, 24);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_EP_COARSE__A, 24);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_EI_FINE__A, 12);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_EI_MEDIUM__A, 16);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_EI_COARSE__A, 16);
	अगर (status < 0)
		जाओ error;

	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CP_FINE__A, 5);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CP_MEDIUM__A, 20);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CP_COARSE__A, 80);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CI_FINE__A, 5);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CI_MEDIUM__A, 20);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CI_COARSE__A, 50);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CF_FINE__A, 16);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CF_MEDIUM__A, 16);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CF_COARSE__A, 32);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CF1_FINE__A, 5);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CF1_MEDIUM__A, 10);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CF1_COARSE__A, 10);
	अगर (status < 0)
		जाओ error;


	/* QAM State Machine (FSM) Thresholds */

	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_RTH__A, 140);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_FTH__A, 50);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_CTH__A, 95);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_PTH__A, 120);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_QTH__A, 230);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_MTH__A, 105);
	अगर (status < 0)
		जाओ error;

	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_RATE_LIM__A, 40);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_COUNT_LIM__A, 4);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_FREQ_LIM__A, 24);
	अगर (status < 0)
		जाओ error;


	/* QAM FSM Tracking Parameters */

	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_MEDIAN_AV_MULT__A, (u16) 16);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_RADIUS_AV_LIMIT__A, (u16) 220);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_LCAVG_OFFSET1__A, (u16) 25);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_LCAVG_OFFSET2__A, (u16) 6);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_LCAVG_OFFSET3__A, (u16) -24);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_LCAVG_OFFSET4__A, (u16) -65);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_LCAVG_OFFSET5__A, (u16) -127);
	अगर (status < 0)
		जाओ error;

error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

/*============================================================================*/

/*
* \मrief QAM32 specअगरic setup
* \param demod instance of demod.
* \लeturn DRXStatus_t.
*/
अटल पूर्णांक set_qam32(काष्ठा drxk_state *state)
अणु
	पूर्णांक status = 0;

	dprपूर्णांकk(1, "\n");

	/* QAM Equalizer Setup */
	/* Equalizer */
	status = ग_लिखो16(state, SCU_RAM_QAM_EQ_CMA_RAD0__A, 6707);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_EQ_CMA_RAD1__A, 6707);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_EQ_CMA_RAD2__A, 6707);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_EQ_CMA_RAD3__A, 6707);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_EQ_CMA_RAD4__A, 6707);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_EQ_CMA_RAD5__A, 6707);
	अगर (status < 0)
		जाओ error;

	/* Decision Feedback Equalizer */
	status = ग_लिखो16(state, QAM_DQ_QUAL_FUN0__A, 3);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_DQ_QUAL_FUN1__A, 3);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_DQ_QUAL_FUN2__A, 3);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_DQ_QUAL_FUN3__A, 3);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_DQ_QUAL_FUN4__A, 3);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_DQ_QUAL_FUN5__A, 0);
	अगर (status < 0)
		जाओ error;

	status = ग_लिखो16(state, QAM_SY_SYNC_HWM__A, 6);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_SY_SYNC_AWM__A, 5);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_SY_SYNC_LWM__A, 3);
	अगर (status < 0)
		जाओ error;

	/* QAM Slicer Settings */

	status = ग_लिखो16(state, SCU_RAM_QAM_SL_SIG_POWER__A,
			 DRXK_QAM_SL_SIG_POWER_QAM32);
	अगर (status < 0)
		जाओ error;


	/* QAM Loop Controller Coeficients */

	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CA_FINE__A, 15);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CA_COARSE__A, 40);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_EP_FINE__A, 12);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_EP_MEDIUM__A, 24);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_EP_COARSE__A, 24);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_EI_FINE__A, 12);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_EI_MEDIUM__A, 16);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_EI_COARSE__A, 16);
	अगर (status < 0)
		जाओ error;

	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CP_FINE__A, 5);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CP_MEDIUM__A, 20);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CP_COARSE__A, 80);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CI_FINE__A, 5);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CI_MEDIUM__A, 20);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CI_COARSE__A, 50);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CF_FINE__A, 16);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CF_MEDIUM__A, 16);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CF_COARSE__A, 16);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CF1_FINE__A, 5);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CF1_MEDIUM__A, 10);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CF1_COARSE__A, 0);
	अगर (status < 0)
		जाओ error;


	/* QAM State Machine (FSM) Thresholds */

	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_RTH__A, 90);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_FTH__A, 50);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_CTH__A, 80);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_PTH__A, 100);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_QTH__A, 170);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_MTH__A, 100);
	अगर (status < 0)
		जाओ error;

	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_RATE_LIM__A, 40);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_COUNT_LIM__A, 4);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_FREQ_LIM__A, 10);
	अगर (status < 0)
		जाओ error;


	/* QAM FSM Tracking Parameters */

	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_MEDIAN_AV_MULT__A, (u16) 12);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_RADIUS_AV_LIMIT__A, (u16) 140);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_LCAVG_OFFSET1__A, (u16) -8);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_LCAVG_OFFSET2__A, (u16) -16);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_LCAVG_OFFSET3__A, (u16) -26);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_LCAVG_OFFSET4__A, (u16) -56);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_LCAVG_OFFSET5__A, (u16) -86);
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

/*============================================================================*/

/*
* \मrief QAM64 specअगरic setup
* \param demod instance of demod.
* \लeturn DRXStatus_t.
*/
अटल पूर्णांक set_qam64(काष्ठा drxk_state *state)
अणु
	पूर्णांक status = 0;

	dprपूर्णांकk(1, "\n");
	/* QAM Equalizer Setup */
	/* Equalizer */
	status = ग_लिखो16(state, SCU_RAM_QAM_EQ_CMA_RAD0__A, 13336);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_EQ_CMA_RAD1__A, 12618);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_EQ_CMA_RAD2__A, 11988);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_EQ_CMA_RAD3__A, 13809);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_EQ_CMA_RAD4__A, 13809);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_EQ_CMA_RAD5__A, 15609);
	अगर (status < 0)
		जाओ error;

	/* Decision Feedback Equalizer */
	status = ग_लिखो16(state, QAM_DQ_QUAL_FUN0__A, 4);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_DQ_QUAL_FUN1__A, 4);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_DQ_QUAL_FUN2__A, 4);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_DQ_QUAL_FUN3__A, 4);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_DQ_QUAL_FUN4__A, 3);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_DQ_QUAL_FUN5__A, 0);
	अगर (status < 0)
		जाओ error;

	status = ग_लिखो16(state, QAM_SY_SYNC_HWM__A, 5);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_SY_SYNC_AWM__A, 4);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_SY_SYNC_LWM__A, 3);
	अगर (status < 0)
		जाओ error;

	/* QAM Slicer Settings */
	status = ग_लिखो16(state, SCU_RAM_QAM_SL_SIG_POWER__A,
			 DRXK_QAM_SL_SIG_POWER_QAM64);
	अगर (status < 0)
		जाओ error;


	/* QAM Loop Controller Coeficients */

	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CA_FINE__A, 15);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CA_COARSE__A, 40);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_EP_FINE__A, 12);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_EP_MEDIUM__A, 24);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_EP_COARSE__A, 24);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_EI_FINE__A, 12);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_EI_MEDIUM__A, 16);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_EI_COARSE__A, 16);
	अगर (status < 0)
		जाओ error;

	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CP_FINE__A, 5);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CP_MEDIUM__A, 30);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CP_COARSE__A, 100);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CI_FINE__A, 5);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CI_MEDIUM__A, 30);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CI_COARSE__A, 50);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CF_FINE__A, 16);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CF_MEDIUM__A, 25);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CF_COARSE__A, 48);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CF1_FINE__A, 5);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CF1_MEDIUM__A, 10);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CF1_COARSE__A, 10);
	अगर (status < 0)
		जाओ error;


	/* QAM State Machine (FSM) Thresholds */

	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_RTH__A, 100);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_FTH__A, 60);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_CTH__A, 80);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_PTH__A, 110);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_QTH__A, 200);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_MTH__A, 95);
	अगर (status < 0)
		जाओ error;

	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_RATE_LIM__A, 40);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_COUNT_LIM__A, 4);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_FREQ_LIM__A, 15);
	अगर (status < 0)
		जाओ error;


	/* QAM FSM Tracking Parameters */

	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_MEDIAN_AV_MULT__A, (u16) 12);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_RADIUS_AV_LIMIT__A, (u16) 141);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_LCAVG_OFFSET1__A, (u16) 7);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_LCAVG_OFFSET2__A, (u16) 0);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_LCAVG_OFFSET3__A, (u16) -15);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_LCAVG_OFFSET4__A, (u16) -45);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_LCAVG_OFFSET5__A, (u16) -80);
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);

	वापस status;
पूर्ण

/*============================================================================*/

/*
* \मrief QAM128 specअगरic setup
* \param demod: instance of demod.
* \लeturn DRXStatus_t.
*/
अटल पूर्णांक set_qam128(काष्ठा drxk_state *state)
अणु
	पूर्णांक status = 0;

	dprपूर्णांकk(1, "\n");
	/* QAM Equalizer Setup */
	/* Equalizer */
	status = ग_लिखो16(state, SCU_RAM_QAM_EQ_CMA_RAD0__A, 6564);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_EQ_CMA_RAD1__A, 6598);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_EQ_CMA_RAD2__A, 6394);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_EQ_CMA_RAD3__A, 6409);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_EQ_CMA_RAD4__A, 6656);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_EQ_CMA_RAD5__A, 7238);
	अगर (status < 0)
		जाओ error;

	/* Decision Feedback Equalizer */
	status = ग_लिखो16(state, QAM_DQ_QUAL_FUN0__A, 6);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_DQ_QUAL_FUN1__A, 6);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_DQ_QUAL_FUN2__A, 6);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_DQ_QUAL_FUN3__A, 6);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_DQ_QUAL_FUN4__A, 5);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_DQ_QUAL_FUN5__A, 0);
	अगर (status < 0)
		जाओ error;

	status = ग_लिखो16(state, QAM_SY_SYNC_HWM__A, 6);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_SY_SYNC_AWM__A, 5);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_SY_SYNC_LWM__A, 3);
	अगर (status < 0)
		जाओ error;


	/* QAM Slicer Settings */

	status = ग_लिखो16(state, SCU_RAM_QAM_SL_SIG_POWER__A,
			 DRXK_QAM_SL_SIG_POWER_QAM128);
	अगर (status < 0)
		जाओ error;


	/* QAM Loop Controller Coeficients */

	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CA_FINE__A, 15);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CA_COARSE__A, 40);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_EP_FINE__A, 12);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_EP_MEDIUM__A, 24);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_EP_COARSE__A, 24);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_EI_FINE__A, 12);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_EI_MEDIUM__A, 16);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_EI_COARSE__A, 16);
	अगर (status < 0)
		जाओ error;

	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CP_FINE__A, 5);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CP_MEDIUM__A, 40);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CP_COARSE__A, 120);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CI_FINE__A, 5);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CI_MEDIUM__A, 40);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CI_COARSE__A, 60);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CF_FINE__A, 16);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CF_MEDIUM__A, 25);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CF_COARSE__A, 64);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CF1_FINE__A, 5);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CF1_MEDIUM__A, 10);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CF1_COARSE__A, 0);
	अगर (status < 0)
		जाओ error;


	/* QAM State Machine (FSM) Thresholds */

	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_RTH__A, 50);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_FTH__A, 60);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_CTH__A, 80);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_PTH__A, 100);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_QTH__A, 140);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_MTH__A, 100);
	अगर (status < 0)
		जाओ error;

	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_RATE_LIM__A, 40);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_COUNT_LIM__A, 5);
	अगर (status < 0)
		जाओ error;

	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_FREQ_LIM__A, 12);
	अगर (status < 0)
		जाओ error;

	/* QAM FSM Tracking Parameters */

	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_MEDIAN_AV_MULT__A, (u16) 8);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_RADIUS_AV_LIMIT__A, (u16) 65);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_LCAVG_OFFSET1__A, (u16) 5);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_LCAVG_OFFSET2__A, (u16) 3);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_LCAVG_OFFSET3__A, (u16) -1);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_LCAVG_OFFSET4__A, (u16) -12);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_LCAVG_OFFSET5__A, (u16) -23);
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);

	वापस status;
पूर्ण

/*============================================================================*/

/*
* \मrief QAM256 specअगरic setup
* \param demod: instance of demod.
* \लeturn DRXStatus_t.
*/
अटल पूर्णांक set_qam256(काष्ठा drxk_state *state)
अणु
	पूर्णांक status = 0;

	dprपूर्णांकk(1, "\n");
	/* QAM Equalizer Setup */
	/* Equalizer */
	status = ग_लिखो16(state, SCU_RAM_QAM_EQ_CMA_RAD0__A, 11502);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_EQ_CMA_RAD1__A, 12084);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_EQ_CMA_RAD2__A, 12543);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_EQ_CMA_RAD3__A, 12931);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_EQ_CMA_RAD4__A, 13629);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_EQ_CMA_RAD5__A, 15385);
	अगर (status < 0)
		जाओ error;

	/* Decision Feedback Equalizer */
	status = ग_लिखो16(state, QAM_DQ_QUAL_FUN0__A, 8);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_DQ_QUAL_FUN1__A, 8);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_DQ_QUAL_FUN2__A, 8);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_DQ_QUAL_FUN3__A, 8);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_DQ_QUAL_FUN4__A, 6);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_DQ_QUAL_FUN5__A, 0);
	अगर (status < 0)
		जाओ error;

	status = ग_लिखो16(state, QAM_SY_SYNC_HWM__A, 5);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_SY_SYNC_AWM__A, 4);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_SY_SYNC_LWM__A, 3);
	अगर (status < 0)
		जाओ error;

	/* QAM Slicer Settings */

	status = ग_लिखो16(state, SCU_RAM_QAM_SL_SIG_POWER__A,
			 DRXK_QAM_SL_SIG_POWER_QAM256);
	अगर (status < 0)
		जाओ error;


	/* QAM Loop Controller Coeficients */

	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CA_FINE__A, 15);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CA_COARSE__A, 40);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_EP_FINE__A, 12);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_EP_MEDIUM__A, 24);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_EP_COARSE__A, 24);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_EI_FINE__A, 12);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_EI_MEDIUM__A, 16);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_EI_COARSE__A, 16);
	अगर (status < 0)
		जाओ error;

	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CP_FINE__A, 5);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CP_MEDIUM__A, 50);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CP_COARSE__A, 250);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CI_FINE__A, 5);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CI_MEDIUM__A, 50);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CI_COARSE__A, 125);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CF_FINE__A, 16);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CF_MEDIUM__A, 25);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CF_COARSE__A, 48);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CF1_FINE__A, 5);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CF1_MEDIUM__A, 10);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_LC_CF1_COARSE__A, 10);
	अगर (status < 0)
		जाओ error;


	/* QAM State Machine (FSM) Thresholds */

	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_RTH__A, 50);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_FTH__A, 60);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_CTH__A, 80);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_PTH__A, 100);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_QTH__A, 150);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_MTH__A, 110);
	अगर (status < 0)
		जाओ error;

	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_RATE_LIM__A, 40);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_COUNT_LIM__A, 4);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_FREQ_LIM__A, 12);
	अगर (status < 0)
		जाओ error;


	/* QAM FSM Tracking Parameters */

	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_MEDIAN_AV_MULT__A, (u16) 8);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_RADIUS_AV_LIMIT__A, (u16) 74);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_LCAVG_OFFSET1__A, (u16) 18);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_LCAVG_OFFSET2__A, (u16) 13);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_LCAVG_OFFSET3__A, (u16) 7);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_LCAVG_OFFSET4__A, (u16) 0);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_LCAVG_OFFSET5__A, (u16) -8);
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण


/*============================================================================*/
/*
* \मrief Reset QAM block.
* \param demod:   instance of demod.
* \param channel: poपूर्णांकer to channel data.
* \लeturn DRXStatus_t.
*/
अटल पूर्णांक qam_reset_qam(काष्ठा drxk_state *state)
अणु
	पूर्णांक status;
	u16 cmd_result;

	dprपूर्णांकk(1, "\n");
	/* Stop QAM comstate->m_exec */
	status = ग_लिखो16(state, QAM_COMM_EXEC__A, QAM_COMM_EXEC_STOP);
	अगर (status < 0)
		जाओ error;

	status = scu_command(state, SCU_RAM_COMMAND_STANDARD_QAM
			     | SCU_RAM_COMMAND_CMD_DEMOD_RESET,
			     0, शून्य, 1, &cmd_result);
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

/*============================================================================*/

/*
* \मrief Set QAM symbolrate.
* \param demod:   instance of demod.
* \param channel: poपूर्णांकer to channel data.
* \लeturn DRXStatus_t.
*/
अटल पूर्णांक qam_set_symbolrate(काष्ठा drxk_state *state)
अणु
	u32 adc_frequency = 0;
	u32 symb_freq = 0;
	u32 iqm_rc_rate = 0;
	u16 ratesel = 0;
	u32 lc_symb_rate = 0;
	पूर्णांक status;

	dprपूर्णांकk(1, "\n");
	/* Select & calculate correct IQM rate */
	adc_frequency = (state->m_sys_घड़ी_freq * 1000) / 3;
	ratesel = 0;
	अगर (state->props.symbol_rate <= 1188750)
		ratesel = 3;
	अन्यथा अगर (state->props.symbol_rate <= 2377500)
		ratesel = 2;
	अन्यथा अगर (state->props.symbol_rate <= 4755000)
		ratesel = 1;
	status = ग_लिखो16(state, IQM_FD_RATESEL__A, ratesel);
	अगर (status < 0)
		जाओ error;

	/*
		IqmRcRate = ((Fadc / (symbolrate * (4<<ratesel))) - 1) * (1<<23)
		*/
	symb_freq = state->props.symbol_rate * (1 << ratesel);
	अगर (symb_freq == 0) अणु
		/* Divide by zero */
		status = -EINVAL;
		जाओ error;
	पूर्ण
	iqm_rc_rate = (adc_frequency / symb_freq) * (1 << 21) +
		(Frac28a((adc_frequency % symb_freq), symb_freq) >> 7) -
		(1 << 23);
	status = ग_लिखो32(state, IQM_RC_RATE_OFS_LO__A, iqm_rc_rate);
	अगर (status < 0)
		जाओ error;
	state->m_iqm_rc_rate = iqm_rc_rate;
	/*
		LcSymbFreq = round (.125 *  symbolrate / adc_freq * (1<<15))
		*/
	symb_freq = state->props.symbol_rate;
	अगर (adc_frequency == 0) अणु
		/* Divide by zero */
		status = -EINVAL;
		जाओ error;
	पूर्ण
	lc_symb_rate = (symb_freq / adc_frequency) * (1 << 12) +
		(Frac28a((symb_freq % adc_frequency), adc_frequency) >>
		16);
	अगर (lc_symb_rate > 511)
		lc_symb_rate = 511;
	status = ग_लिखो16(state, QAM_LC_SYMBOL_FREQ__A, (u16) lc_symb_rate);

error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

/*============================================================================*/

/*
* \मrief Get QAM lock status.
* \param demod:   instance of demod.
* \param channel: poपूर्णांकer to channel data.
* \लeturn DRXStatus_t.
*/

अटल पूर्णांक get_qam_lock_status(काष्ठा drxk_state *state, u32 *p_lock_status)
अणु
	पूर्णांक status;
	u16 result[2] = अणु 0, 0 पूर्ण;

	dprपूर्णांकk(1, "\n");
	*p_lock_status = NOT_LOCKED;
	status = scu_command(state,
			SCU_RAM_COMMAND_STANDARD_QAM |
			SCU_RAM_COMMAND_CMD_DEMOD_GET_LOCK, 0, शून्य, 2,
			result);
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);

	अगर (result[1] < SCU_RAM_QAM_LOCKED_LOCKED_DEMOD_LOCKED) अणु
		/* 0x0000 NOT LOCKED */
	पूर्ण अन्यथा अगर (result[1] < SCU_RAM_QAM_LOCKED_LOCKED_LOCKED) अणु
		/* 0x4000 DEMOD LOCKED */
		*p_lock_status = DEMOD_LOCK;
	पूर्ण अन्यथा अगर (result[1] < SCU_RAM_QAM_LOCKED_LOCKED_NEVER_LOCK) अणु
		/* 0x8000 DEMOD + FEC LOCKED (प्रणाली lock) */
		*p_lock_status = MPEG_LOCK;
	पूर्ण अन्यथा अणु
		/* 0xC000 NEVER LOCKED */
		/* (प्रणाली will never be able to lock to the संकेत) */
		/*
		 * TODO: check this, पूर्णांकermediate & standard specअगरic lock
		 * states are not taken पूर्णांकo account here
		 */
		*p_lock_status = NEVER_LOCK;
	पूर्ण
	वापस status;
पूर्ण

#घोषणा QAM_MIRROR__M         0x03
#घोषणा QAM_MIRROR_NORMAL     0x00
#घोषणा QAM_MIRRORED          0x01
#घोषणा QAM_MIRROR_AUTO_ON    0x02
#घोषणा QAM_LOCKRANGE__M      0x10
#घोषणा QAM_LOCKRANGE_NORMAL  0x10

अटल पूर्णांक qam_demodulator_command(काष्ठा drxk_state *state,
				 पूर्णांक number_of_parameters)
अणु
	पूर्णांक status;
	u16 cmd_result;
	u16 set_param_parameters[4] = अणु 0, 0, 0, 0 पूर्ण;

	set_param_parameters[0] = state->m_स्थिरellation;	/* modulation     */
	set_param_parameters[1] = DRXK_QAM_I12_J17;	/* पूर्णांकerleave mode   */

	अगर (number_of_parameters == 2) अणु
		u16 set_env_parameters[1] = अणु 0 पूर्ण;

		अगर (state->m_operation_mode == OM_QAM_ITU_C)
			set_env_parameters[0] = QAM_TOP_ANNEX_C;
		अन्यथा
			set_env_parameters[0] = QAM_TOP_ANNEX_A;

		status = scu_command(state,
				     SCU_RAM_COMMAND_STANDARD_QAM
				     | SCU_RAM_COMMAND_CMD_DEMOD_SET_ENV,
				     1, set_env_parameters, 1, &cmd_result);
		अगर (status < 0)
			जाओ error;

		status = scu_command(state,
				     SCU_RAM_COMMAND_STANDARD_QAM
				     | SCU_RAM_COMMAND_CMD_DEMOD_SET_PARAM,
				     number_of_parameters, set_param_parameters,
				     1, &cmd_result);
	पूर्ण अन्यथा अगर (number_of_parameters == 4) अणु
		अगर (state->m_operation_mode == OM_QAM_ITU_C)
			set_param_parameters[2] = QAM_TOP_ANNEX_C;
		अन्यथा
			set_param_parameters[2] = QAM_TOP_ANNEX_A;

		set_param_parameters[3] |= (QAM_MIRROR_AUTO_ON);
		/* Env parameters */
		/* check क्रम LOCKRANGE Extended */
		/* set_param_parameters[3] |= QAM_LOCKRANGE_NORMAL; */

		status = scu_command(state,
				     SCU_RAM_COMMAND_STANDARD_QAM
				     | SCU_RAM_COMMAND_CMD_DEMOD_SET_PARAM,
				     number_of_parameters, set_param_parameters,
				     1, &cmd_result);
	पूर्ण अन्यथा अणु
		pr_warn("Unknown QAM demodulator parameter count %d\n",
			number_of_parameters);
		status = -EINVAL;
	पूर्ण

error:
	अगर (status < 0)
		pr_warn("Warning %d on %s\n", status, __func__);
	वापस status;
पूर्ण

अटल पूर्णांक set_qam(काष्ठा drxk_state *state, u16 पूर्णांकermediate_freqk_hz,
		  s32 tuner_freq_offset)
अणु
	पूर्णांक status;
	u16 cmd_result;
	पूर्णांक qam_demod_param_count = state->qam_demod_parameter_count;

	dprपूर्णांकk(1, "\n");
	/*
	 * STEP 1: reset demodulator
	 *	resets FEC DI and FEC RS
	 *	resets QAM block
	 *	resets SCU variables
	 */
	status = ग_लिखो16(state, FEC_DI_COMM_EXEC__A, FEC_DI_COMM_EXEC_STOP);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, FEC_RS_COMM_EXEC__A, FEC_RS_COMM_EXEC_STOP);
	अगर (status < 0)
		जाओ error;
	status = qam_reset_qam(state);
	अगर (status < 0)
		जाओ error;

	/*
	 * STEP 2: configure demodulator
	 *	-set params; resets IQM,QAM,FEC HW; initializes some
	 *       SCU variables
	 */
	status = qam_set_symbolrate(state);
	अगर (status < 0)
		जाओ error;

	/* Set params */
	चयन (state->props.modulation) अणु
	हाल QAM_256:
		state->m_स्थिरellation = DRX_CONSTELLATION_QAM256;
		अवरोध;
	हाल QAM_AUTO:
	हाल QAM_64:
		state->m_स्थिरellation = DRX_CONSTELLATION_QAM64;
		अवरोध;
	हाल QAM_16:
		state->m_स्थिरellation = DRX_CONSTELLATION_QAM16;
		अवरोध;
	हाल QAM_32:
		state->m_स्थिरellation = DRX_CONSTELLATION_QAM32;
		अवरोध;
	हाल QAM_128:
		state->m_स्थिरellation = DRX_CONSTELLATION_QAM128;
		अवरोध;
	शेष:
		status = -EINVAL;
		अवरोध;
	पूर्ण
	अगर (status < 0)
		जाओ error;

	/* Use the 4-parameter अगर it's requested or we're probing क्रम
	 * the correct command. */
	अगर (state->qam_demod_parameter_count == 4
		|| !state->qam_demod_parameter_count) अणु
		qam_demod_param_count = 4;
		status = qam_demodulator_command(state, qam_demod_param_count);
	पूर्ण

	/* Use the 2-parameter command अगर it was requested or अगर we're
	 * probing क्रम the correct command and the 4-parameter command
	 * failed. */
	अगर (state->qam_demod_parameter_count == 2
		|| (!state->qam_demod_parameter_count && status < 0)) अणु
		qam_demod_param_count = 2;
		status = qam_demodulator_command(state, qam_demod_param_count);
	पूर्ण

	अगर (status < 0) अणु
		dprपूर्णांकk(1, "Could not set demodulator parameters.\n");
		dprपूर्णांकk(1,
			"Make sure qam_demod_parameter_count (%d) is correct for your firmware (%s).\n",
			state->qam_demod_parameter_count,
			state->microcode_name);
		जाओ error;
	पूर्ण अन्यथा अगर (!state->qam_demod_parameter_count) अणु
		dprपूर्णांकk(1,
			"Auto-probing the QAM command parameters was successful - using %d parameters.\n",
			qam_demod_param_count);

		/*
		 * One of our commands was successful. We करोn't need to
		 * स्वतः-probe anymore, now that we got the correct command.
		 */
		state->qam_demod_parameter_count = qam_demod_param_count;
	पूर्ण

	/*
	 * STEP 3: enable the प्रणाली in a mode where the ADC provides valid
	 * संकेत setup modulation independent रेजिस्टरs
	 */
#अगर 0
	status = set_frequency(channel, tuner_freq_offset));
	अगर (status < 0)
		जाओ error;
#पूर्ण_अगर
	status = set_frequency_shअगरter(state, पूर्णांकermediate_freqk_hz,
				       tuner_freq_offset, true);
	अगर (status < 0)
		जाओ error;

	/* Setup BER measurement */
	status = set_qam_measurement(state, state->m_स्थिरellation,
				     state->props.symbol_rate);
	अगर (status < 0)
		जाओ error;

	/* Reset शेष values */
	status = ग_लिखो16(state, IQM_CF_SCALE_SH__A, IQM_CF_SCALE_SH__PRE);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_SY_TIMEOUT__A, QAM_SY_TIMEOUT__PRE);
	अगर (status < 0)
		जाओ error;

	/* Reset शेष LC values */
	status = ग_लिखो16(state, QAM_LC_RATE_LIMIT__A, 3);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_LC_LPF_FACTORP__A, 4);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_LC_LPF_FACTORI__A, 4);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_LC_MODE__A, 7);
	अगर (status < 0)
		जाओ error;

	status = ग_लिखो16(state, QAM_LC_QUAL_TAB0__A, 1);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_LC_QUAL_TAB1__A, 1);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_LC_QUAL_TAB2__A, 1);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_LC_QUAL_TAB3__A, 1);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_LC_QUAL_TAB4__A, 2);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_LC_QUAL_TAB5__A, 2);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_LC_QUAL_TAB6__A, 2);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_LC_QUAL_TAB8__A, 2);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_LC_QUAL_TAB9__A, 2);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_LC_QUAL_TAB10__A, 2);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_LC_QUAL_TAB12__A, 2);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_LC_QUAL_TAB15__A, 3);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_LC_QUAL_TAB16__A, 3);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_LC_QUAL_TAB20__A, 4);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_LC_QUAL_TAB25__A, 4);
	अगर (status < 0)
		जाओ error;

	/* Mirroring, QAM-block starting poपूर्णांक not inverted */
	status = ग_लिखो16(state, QAM_SY_SP_INV__A,
			 QAM_SY_SP_INV_SPECTRUM_INV_DIS);
	अगर (status < 0)
		जाओ error;

	/* Halt SCU to enable safe non-atomic accesses */
	status = ग_लिखो16(state, SCU_COMM_EXEC__A, SCU_COMM_EXEC_HOLD);
	अगर (status < 0)
		जाओ error;

	/* STEP 4: modulation specअगरic setup */
	चयन (state->props.modulation) अणु
	हाल QAM_16:
		status = set_qam16(state);
		अवरोध;
	हाल QAM_32:
		status = set_qam32(state);
		अवरोध;
	हाल QAM_AUTO:
	हाल QAM_64:
		status = set_qam64(state);
		अवरोध;
	हाल QAM_128:
		status = set_qam128(state);
		अवरोध;
	हाल QAM_256:
		status = set_qam256(state);
		अवरोध;
	शेष:
		status = -EINVAL;
		अवरोध;
	पूर्ण
	अगर (status < 0)
		जाओ error;

	/* Activate SCU to enable SCU commands */
	status = ग_लिखो16(state, SCU_COMM_EXEC__A, SCU_COMM_EXEC_ACTIVE);
	अगर (status < 0)
		जाओ error;

	/* Re-configure MPEG output, requires knowledge of channel bitrate */
	/* extAttr->currentChannel.modulation = channel->modulation; */
	/* extAttr->currentChannel.symbolrate    = channel->symbolrate; */
	status = mpegts_dto_setup(state, state->m_operation_mode);
	अगर (status < 0)
		जाओ error;

	/* start processes */
	status = mpegts_start(state);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, FEC_COMM_EXEC__A, FEC_COMM_EXEC_ACTIVE);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, QAM_COMM_EXEC__A, QAM_COMM_EXEC_ACTIVE);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, IQM_COMM_EXEC__A, IQM_COMM_EXEC_B_ACTIVE);
	अगर (status < 0)
		जाओ error;

	/* STEP 5: start QAM demodulator (starts FEC, QAM and IQM HW) */
	status = scu_command(state, SCU_RAM_COMMAND_STANDARD_QAM
			     | SCU_RAM_COMMAND_CMD_DEMOD_START,
			     0, शून्य, 1, &cmd_result);
	अगर (status < 0)
		जाओ error;

	/* update global DRXK data container */
/*?     extAttr->qamInterleaveMode = DRXK_QAM_I12_J17; */

error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

अटल पूर्णांक set_qam_standard(काष्ठा drxk_state *state,
			  क्रमागत operation_mode o_mode)
अणु
	पूर्णांक status;
#अगर_घोषित DRXK_QAM_TAPS
#घोषणा DRXK_QAMA_TAPS_SELECT
#समावेश "drxk_filters.h"
#अघोषित DRXK_QAMA_TAPS_SELECT
#पूर्ण_अगर

	dprपूर्णांकk(1, "\n");

	/* added antenna चयन */
	चयन_antenna_to_qam(state);

	/* Ensure correct घातer-up mode */
	status = घातer_up_qam(state);
	अगर (status < 0)
		जाओ error;
	/* Reset QAM block */
	status = qam_reset_qam(state);
	अगर (status < 0)
		जाओ error;

	/* Setup IQM */

	status = ग_लिखो16(state, IQM_COMM_EXEC__A, IQM_COMM_EXEC_B_STOP);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, IQM_AF_AMUX__A, IQM_AF_AMUX_SIGNAL2ADC);
	अगर (status < 0)
		जाओ error;

	/* Upload IQM Channel Filter settings by
		boot loader from ROM table */
	चयन (o_mode) अणु
	हाल OM_QAM_ITU_A:
		status = bl_chain_cmd(state, DRXK_BL_ROM_OFFSET_TAPS_ITU_A,
				      DRXK_BLCC_NR_ELEMENTS_TAPS,
			DRXK_BLC_TIMEOUT);
		अवरोध;
	हाल OM_QAM_ITU_C:
		status = bl_direct_cmd(state, IQM_CF_TAP_RE0__A,
				       DRXK_BL_ROM_OFFSET_TAPS_ITU_C,
				       DRXK_BLDC_NR_ELEMENTS_TAPS,
				       DRXK_BLC_TIMEOUT);
		अगर (status < 0)
			जाओ error;
		status = bl_direct_cmd(state,
				       IQM_CF_TAP_IM0__A,
				       DRXK_BL_ROM_OFFSET_TAPS_ITU_C,
				       DRXK_BLDC_NR_ELEMENTS_TAPS,
				       DRXK_BLC_TIMEOUT);
		अवरोध;
	शेष:
		status = -EINVAL;
	पूर्ण
	अगर (status < 0)
		जाओ error;

	status = ग_लिखो16(state, IQM_CF_OUT_ENA__A, 1 << IQM_CF_OUT_ENA_QAM__B);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, IQM_CF_SYMMETRIC__A, 0);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, IQM_CF_MIDTAP__A,
		     ((1 << IQM_CF_MIDTAP_RE__B) | (1 << IQM_CF_MIDTAP_IM__B)));
	अगर (status < 0)
		जाओ error;

	status = ग_लिखो16(state, IQM_RC_STRETCH__A, 21);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, IQM_AF_CLP_LEN__A, 0);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, IQM_AF_CLP_TH__A, 448);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, IQM_AF_SNS_LEN__A, 0);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, IQM_CF_POW_MEAS_LEN__A, 0);
	अगर (status < 0)
		जाओ error;

	status = ग_लिखो16(state, IQM_FS_ADJ_SEL__A, 1);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, IQM_RC_ADJ_SEL__A, 1);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, IQM_CF_ADJ_SEL__A, 1);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, IQM_AF_UPD_SEL__A, 0);
	अगर (status < 0)
		जाओ error;

	/* IQM Impulse Noise Processing Unit */
	status = ग_लिखो16(state, IQM_CF_CLP_VAL__A, 500);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, IQM_CF_DATATH__A, 1000);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, IQM_CF_BYPASSDET__A, 1);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, IQM_CF_DET_LCT__A, 0);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, IQM_CF_WND_LEN__A, 1);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, IQM_CF_PKDTH__A, 1);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, IQM_AF_INC_BYPASS__A, 1);
	अगर (status < 0)
		जाओ error;

	/* turn on IQMAF. Must be करोne beक्रमe setAgc**() */
	status = set_iqm_af(state, true);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, IQM_AF_START_LOCK__A, 0x01);
	अगर (status < 0)
		जाओ error;

	/* IQM will not be reset from here, sync ADC and update/init AGC */
	status = adc_synchronization(state);
	अगर (status < 0)
		जाओ error;

	/* Set the FSM step period */
	status = ग_लिखो16(state, SCU_RAM_QAM_FSM_STEP_PERIOD__A, 2000);
	अगर (status < 0)
		जाओ error;

	/* Halt SCU to enable safe non-atomic accesses */
	status = ग_लिखो16(state, SCU_COMM_EXEC__A, SCU_COMM_EXEC_HOLD);
	अगर (status < 0)
		जाओ error;

	/* No more resets of the IQM, current standard correctly set =>
		now AGCs can be configured. */

	status = init_agc(state, true);
	अगर (status < 0)
		जाओ error;
	status = set_pre_saw(state, &(state->m_qam_pre_saw_cfg));
	अगर (status < 0)
		जाओ error;

	/* Configure AGC's */
	status = set_agc_rf(state, &(state->m_qam_rf_agc_cfg), true);
	अगर (status < 0)
		जाओ error;
	status = set_agc_अगर(state, &(state->m_qam_अगर_agc_cfg), true);
	अगर (status < 0)
		जाओ error;

	/* Activate SCU to enable SCU commands */
	status = ग_लिखो16(state, SCU_COMM_EXEC__A, SCU_COMM_EXEC_ACTIVE);
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

अटल पूर्णांक ग_लिखो_gpio(काष्ठा drxk_state *state)
अणु
	पूर्णांक status;
	u16 value = 0;

	dprपूर्णांकk(1, "\n");
	/* stop lock indicator process */
	status = ग_लिखो16(state, SCU_RAM_GPIO__A,
			 SCU_RAM_GPIO_HW_LOCK_IND_DISABLE);
	अगर (status < 0)
		जाओ error;

	/*  Write magic word to enable pdr reg ग_लिखो               */
	status = ग_लिखो16(state, SIO_TOP_COMM_KEY__A, SIO_TOP_COMM_KEY_KEY);
	अगर (status < 0)
		जाओ error;

	अगर (state->m_has_sawsw) अणु
		अगर (state->uio_mask & 0x0001) अणु /* UIO-1 */
			/* ग_लिखो to io pad configuration रेजिस्टर - output mode */
			status = ग_लिखो16(state, SIO_PDR_SMA_TX_CFG__A,
					 state->m_gpio_cfg);
			अगर (status < 0)
				जाओ error;

			/* use corresponding bit in io data output registar */
			status = पढ़ो16(state, SIO_PDR_UIO_OUT_LO__A, &value);
			अगर (status < 0)
				जाओ error;
			अगर ((state->m_gpio & 0x0001) == 0)
				value &= 0x7FFF;	/* ग_लिखो zero to 15th bit - 1st UIO */
			अन्यथा
				value |= 0x8000;	/* ग_लिखो one to 15th bit - 1st UIO */
			/* ग_लिखो back to io data output रेजिस्टर */
			status = ग_लिखो16(state, SIO_PDR_UIO_OUT_LO__A, value);
			अगर (status < 0)
				जाओ error;
		पूर्ण
		अगर (state->uio_mask & 0x0002) अणु /* UIO-2 */
			/* ग_लिखो to io pad configuration रेजिस्टर - output mode */
			status = ग_लिखो16(state, SIO_PDR_SMA_RX_CFG__A,
					 state->m_gpio_cfg);
			अगर (status < 0)
				जाओ error;

			/* use corresponding bit in io data output registar */
			status = पढ़ो16(state, SIO_PDR_UIO_OUT_LO__A, &value);
			अगर (status < 0)
				जाओ error;
			अगर ((state->m_gpio & 0x0002) == 0)
				value &= 0xBFFF;	/* ग_लिखो zero to 14th bit - 2st UIO */
			अन्यथा
				value |= 0x4000;	/* ग_लिखो one to 14th bit - 2st UIO */
			/* ग_लिखो back to io data output रेजिस्टर */
			status = ग_लिखो16(state, SIO_PDR_UIO_OUT_LO__A, value);
			अगर (status < 0)
				जाओ error;
		पूर्ण
		अगर (state->uio_mask & 0x0004) अणु /* UIO-3 */
			/* ग_लिखो to io pad configuration रेजिस्टर - output mode */
			status = ग_लिखो16(state, SIO_PDR_GPIO_CFG__A,
					 state->m_gpio_cfg);
			अगर (status < 0)
				जाओ error;

			/* use corresponding bit in io data output registar */
			status = पढ़ो16(state, SIO_PDR_UIO_OUT_LO__A, &value);
			अगर (status < 0)
				जाओ error;
			अगर ((state->m_gpio & 0x0004) == 0)
				value &= 0xFFFB;            /* ग_लिखो zero to 2nd bit - 3rd UIO */
			अन्यथा
				value |= 0x0004;            /* ग_लिखो one to 2nd bit - 3rd UIO */
			/* ग_लिखो back to io data output रेजिस्टर */
			status = ग_लिखो16(state, SIO_PDR_UIO_OUT_LO__A, value);
			अगर (status < 0)
				जाओ error;
		पूर्ण
	पूर्ण
	/*  Write magic word to disable pdr reg ग_लिखो               */
	status = ग_लिखो16(state, SIO_TOP_COMM_KEY__A, 0x0000);
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

अटल पूर्णांक चयन_antenna_to_qam(काष्ठा drxk_state *state)
अणु
	पूर्णांक status = 0;
	bool gpio_state;

	dprपूर्णांकk(1, "\n");

	अगर (!state->antenna_gpio)
		वापस 0;

	gpio_state = state->m_gpio & state->antenna_gpio;

	अगर (state->antenna_dvbt ^ gpio_state) अणु
		/* Antenna is on DVB-T mode. Switch */
		अगर (state->antenna_dvbt)
			state->m_gpio &= ~state->antenna_gpio;
		अन्यथा
			state->m_gpio |= state->antenna_gpio;
		status = ग_लिखो_gpio(state);
	पूर्ण
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण

अटल पूर्णांक चयन_antenna_to_dvbt(काष्ठा drxk_state *state)
अणु
	पूर्णांक status = 0;
	bool gpio_state;

	dprपूर्णांकk(1, "\n");

	अगर (!state->antenna_gpio)
		वापस 0;

	gpio_state = state->m_gpio & state->antenna_gpio;

	अगर (!(state->antenna_dvbt ^ gpio_state)) अणु
		/* Antenna is on DVB-C mode. Switch */
		अगर (state->antenna_dvbt)
			state->m_gpio |= state->antenna_gpio;
		अन्यथा
			state->m_gpio &= ~state->antenna_gpio;
		status = ग_लिखो_gpio(state);
	पूर्ण
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	वापस status;
पूर्ण


अटल पूर्णांक घातer_करोwn_device(काष्ठा drxk_state *state)
अणु
	/* Power करोwn to requested mode */
	/* Backup some रेजिस्टर settings */
	/* Set pins with possible pull-ups connected to them in input mode */
	/* Analog घातer करोwn */
	/* ADC घातer करोwn */
	/* Power करोwn device */
	पूर्णांक status;

	dprपूर्णांकk(1, "\n");
	अगर (state->m_b_p_करोwn_खोलो_bridge) अणु
		/* Open I2C bridge beक्रमe घातer करोwn of DRXK */
		status = ConfigureI2CBridge(state, true);
		अगर (status < 0)
			जाओ error;
	पूर्ण
	/* driver 0.9.0 */
	status = dvbt_enable_ofdm_token_ring(state, false);
	अगर (status < 0)
		जाओ error;

	status = ग_लिखो16(state, SIO_CC_PWD_MODE__A,
			 SIO_CC_PWD_MODE_LEVEL_CLOCK);
	अगर (status < 0)
		जाओ error;
	status = ग_लिखो16(state, SIO_CC_UPDATE__A, SIO_CC_UPDATE_KEY);
	अगर (status < 0)
		जाओ error;
	state->m_hi_cfg_ctrl |= SIO_HI_RA_RAM_PAR_5_CFG_SLEEP_ZZZ;
	status = hi_cfg_command(state);
error:
	अगर (status < 0)
		pr_err("Error %d on %s\n", status, __func__);

	वापस status;
पूर्ण

अटल पूर्णांक init_drxk(काष्ठा drxk_state *state)
अणु
	पूर्णांक status = 0, n = 0;
	क्रमागत drx_घातer_mode घातer_mode = DRXK_POWER_DOWN_OFDM;
	u16 driver_version;

	dprपूर्णांकk(1, "\n");
	अगर (state->m_drxk_state == DRXK_UNINITIALIZED) अणु
		drxk_i2c_lock(state);
		status = घातer_up_device(state);
		अगर (status < 0)
			जाओ error;
		status = drxx_खोलो(state);
		अगर (status < 0)
			जाओ error;
		/* Soft reset of OFDM-, sys- and osc-घड़ीकरोमुख्य */
		status = ग_लिखो16(state, SIO_CC_SOFT_RST__A,
				 SIO_CC_SOFT_RST_OFDM__M
				 | SIO_CC_SOFT_RST_SYS__M
				 | SIO_CC_SOFT_RST_OSC__M);
		अगर (status < 0)
			जाओ error;
		status = ग_लिखो16(state, SIO_CC_UPDATE__A, SIO_CC_UPDATE_KEY);
		अगर (status < 0)
			जाओ error;
		/*
		 * TODO is this needed? If yes, how much delay in
		 * worst हाल scenario
		 */
		usleep_range(1000, 2000);
		state->m_drxk_a3_patch_code = true;
		status = get_device_capabilities(state);
		अगर (status < 0)
			जाओ error;

		/* Bridge delay, uses oscilator घड़ी */
		/* Delay = (delay (nano seconds) * oscclk (kHz))/ 1000 */
		/* SDA brdige delay */
		state->m_hi_cfg_bridge_delay =
			(u16) ((state->m_osc_घड़ी_freq / 1000) *
				HI_I2C_BRIDGE_DELAY) / 1000;
		/* Clipping */
		अगर (state->m_hi_cfg_bridge_delay >
			SIO_HI_RA_RAM_PAR_3_CFG_DBL_SDA__M) अणु
			state->m_hi_cfg_bridge_delay =
				SIO_HI_RA_RAM_PAR_3_CFG_DBL_SDA__M;
		पूर्ण
		/* SCL bridge delay, same as SDA क्रम now */
		state->m_hi_cfg_bridge_delay +=
			state->m_hi_cfg_bridge_delay <<
			SIO_HI_RA_RAM_PAR_3_CFG_DBL_SCL__B;

		status = init_hi(state);
		अगर (status < 0)
			जाओ error;
		/* disable various processes */
#अगर NOA1ROM
		अगर (!(state->m_DRXK_A1_ROM_CODE)
			&& !(state->m_DRXK_A2_ROM_CODE))
#पूर्ण_अगर
		अणु
			status = ग_लिखो16(state, SCU_RAM_GPIO__A,
					 SCU_RAM_GPIO_HW_LOCK_IND_DISABLE);
			अगर (status < 0)
				जाओ error;
		पूर्ण

		/* disable MPEG port */
		status = mpegts_disable(state);
		अगर (status < 0)
			जाओ error;

		/* Stop AUD and SCU */
		status = ग_लिखो16(state, AUD_COMM_EXEC__A, AUD_COMM_EXEC_STOP);
		अगर (status < 0)
			जाओ error;
		status = ग_लिखो16(state, SCU_COMM_EXEC__A, SCU_COMM_EXEC_STOP);
		अगर (status < 0)
			जाओ error;

		/* enable token-ring bus through OFDM block क्रम possible ucode upload */
		status = ग_लिखो16(state, SIO_OFDM_SH_OFDM_RING_ENABLE__A,
				 SIO_OFDM_SH_OFDM_RING_ENABLE_ON);
		अगर (status < 0)
			जाओ error;

		/* include boot loader section */
		status = ग_लिखो16(state, SIO_BL_COMM_EXEC__A,
				 SIO_BL_COMM_EXEC_ACTIVE);
		अगर (status < 0)
			जाओ error;
		status = bl_chain_cmd(state, 0, 6, 100);
		अगर (status < 0)
			जाओ error;

		अगर (state->fw) अणु
			status = करोwnload_microcode(state, state->fw->data,
						   state->fw->size);
			अगर (status < 0)
				जाओ error;
		पूर्ण

		/* disable token-ring bus through OFDM block क्रम possible ucode upload */
		status = ग_लिखो16(state, SIO_OFDM_SH_OFDM_RING_ENABLE__A,
				 SIO_OFDM_SH_OFDM_RING_ENABLE_OFF);
		अगर (status < 0)
			जाओ error;

		/* Run SCU क्रम a little जबतक to initialize microcode version numbers */
		status = ग_लिखो16(state, SCU_COMM_EXEC__A, SCU_COMM_EXEC_ACTIVE);
		अगर (status < 0)
			जाओ error;
		status = drxx_खोलो(state);
		अगर (status < 0)
			जाओ error;
		/* added क्रम test */
		msleep(30);

		घातer_mode = DRXK_POWER_DOWN_OFDM;
		status = ctrl_घातer_mode(state, &घातer_mode);
		अगर (status < 0)
			जाओ error;

		/* Stamp driver version number in SCU data RAM in BCD code
			Done to enable field application engineers to retrieve drxdriver version
			via I2C from SCU RAM.
			Not using SCU command पूर्णांकerface क्रम SCU रेजिस्टर access since no
			microcode may be present.
			*/
		driver_version =
			(((DRXK_VERSION_MAJOR / 100) % 10) << 12) +
			(((DRXK_VERSION_MAJOR / 10) % 10) << 8) +
			((DRXK_VERSION_MAJOR % 10) << 4) +
			(DRXK_VERSION_MINOR % 10);
		status = ग_लिखो16(state, SCU_RAM_DRIVER_VER_HI__A,
				 driver_version);
		अगर (status < 0)
			जाओ error;
		driver_version =
			(((DRXK_VERSION_PATCH / 1000) % 10) << 12) +
			(((DRXK_VERSION_PATCH / 100) % 10) << 8) +
			(((DRXK_VERSION_PATCH / 10) % 10) << 4) +
			(DRXK_VERSION_PATCH % 10);
		status = ग_लिखो16(state, SCU_RAM_DRIVER_VER_LO__A,
				 driver_version);
		अगर (status < 0)
			जाओ error;

		pr_info("DRXK driver version %d.%d.%d\n",
			DRXK_VERSION_MAJOR, DRXK_VERSION_MINOR,
			DRXK_VERSION_PATCH);

		/*
		 * Dirty fix of शेष values क्रम ROM/PATCH microcode
		 * Dirty because this fix makes it impossible to setup
		 * suitable values beक्रमe calling DRX_Open. This solution
		 * requires changes to RF AGC speed to be करोne via the CTRL
		 * function after calling DRX_Open
		 */

		/* m_dvbt_rf_agc_cfg.speed = 3; */

		/* Reset driver debug flags to 0 */
		status = ग_लिखो16(state, SCU_RAM_DRIVER_DEBUG__A, 0);
		अगर (status < 0)
			जाओ error;
		/* driver 0.9.0 */
		/* Setup FEC OC:
			NOTE: No more full FEC resets allowed afterwards!! */
		status = ग_लिखो16(state, FEC_COMM_EXEC__A, FEC_COMM_EXEC_STOP);
		अगर (status < 0)
			जाओ error;
		/* MPEGTS functions are still the same */
		status = mpegts_dto_init(state);
		अगर (status < 0)
			जाओ error;
		status = mpegts_stop(state);
		अगर (status < 0)
			जाओ error;
		status = mpegts_configure_polarity(state);
		अगर (status < 0)
			जाओ error;
		status = mpegts_configure_pins(state, state->m_enable_mpeg_output);
		अगर (status < 0)
			जाओ error;
		/* added: configure GPIO */
		status = ग_लिखो_gpio(state);
		अगर (status < 0)
			जाओ error;

		state->m_drxk_state = DRXK_STOPPED;

		अगर (state->m_b_घातer_करोwn) अणु
			status = घातer_करोwn_device(state);
			अगर (status < 0)
				जाओ error;
			state->m_drxk_state = DRXK_POWERED_DOWN;
		पूर्ण अन्यथा
			state->m_drxk_state = DRXK_STOPPED;

		/* Initialize the supported delivery प्रणालीs */
		n = 0;
		अगर (state->m_has_dvbc) अणु
			state->frontend.ops.delsys[n++] = SYS_DVBC_ANNEX_A;
			state->frontend.ops.delsys[n++] = SYS_DVBC_ANNEX_C;
			strlcat(state->frontend.ops.info.name, " DVB-C",
				माप(state->frontend.ops.info.name));
		पूर्ण
		अगर (state->m_has_dvbt) अणु
			state->frontend.ops.delsys[n++] = SYS_DVBT;
			strlcat(state->frontend.ops.info.name, " DVB-T",
				माप(state->frontend.ops.info.name));
		पूर्ण
		drxk_i2c_unlock(state);
	पूर्ण
error:
	अगर (status < 0) अणु
		state->m_drxk_state = DRXK_NO_DEV;
		drxk_i2c_unlock(state);
		pr_err("Error %d on %s\n", status, __func__);
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम load_firmware_cb(स्थिर काष्ठा firmware *fw,
			     व्योम *context)
अणु
	काष्ठा drxk_state *state = context;

	dprपूर्णांकk(1, ": %s\n", fw ? "firmware loaded" : "firmware not loaded");
	अगर (!fw) अणु
		pr_err("Could not load firmware file %s.\n",
			state->microcode_name);
		pr_info("Copy %s to your hotplug directory!\n",
			state->microcode_name);
		state->microcode_name = शून्य;

		/*
		 * As firmware is now load asynchronous, it is not possible
		 * anymore to fail at frontend attach. We might silently
		 * वापस here, and hope that the driver won't crash.
		 * We might also change all DVB callbacks to वापस -ENODEV
		 * अगर the device is not initialized.
		 * As the DRX-K devices have their own पूर्णांकernal firmware,
		 * let's just hope that it will match a firmware revision
		 * compatible with this driver and proceed.
		 */
	पूर्ण
	state->fw = fw;

	init_drxk(state);
पूर्ण

अटल व्योम drxk_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा drxk_state *state = fe->demodulator_priv;

	dprपूर्णांकk(1, "\n");
	release_firmware(state->fw);

	kमुक्त(state);
पूर्ण

अटल पूर्णांक drxk_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा drxk_state *state = fe->demodulator_priv;

	dprपूर्णांकk(1, "\n");

	अगर (state->m_drxk_state == DRXK_NO_DEV)
		वापस -ENODEV;
	अगर (state->m_drxk_state == DRXK_UNINITIALIZED)
		वापस 0;

	shut_करोwn(state);
	वापस 0;
पूर्ण

अटल पूर्णांक drxk_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा drxk_state *state = fe->demodulator_priv;

	dprपूर्णांकk(1, ": %s\n", enable ? "enable" : "disable");

	अगर (state->m_drxk_state == DRXK_NO_DEV)
		वापस -ENODEV;

	वापस ConfigureI2CBridge(state, enable ? true : false);
पूर्ण

अटल पूर्णांक drxk_set_parameters(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	u32 delsys  = p->delivery_प्रणाली, old_delsys;
	काष्ठा drxk_state *state = fe->demodulator_priv;
	u32 IF;

	dprपूर्णांकk(1, "\n");

	अगर (state->m_drxk_state == DRXK_NO_DEV)
		वापस -ENODEV;

	अगर (state->m_drxk_state == DRXK_UNINITIALIZED)
		वापस -EAGAIN;

	अगर (!fe->ops.tuner_ops.get_अगर_frequency) अणु
		pr_err("Error: get_if_frequency() not defined at tuner. Can't work without it!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	अगर (fe->ops.tuner_ops.set_params)
		fe->ops.tuner_ops.set_params(fe);
	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	old_delsys = state->props.delivery_प्रणाली;
	state->props = *p;

	अगर (old_delsys != delsys) अणु
		shut_करोwn(state);
		चयन (delsys) अणु
		हाल SYS_DVBC_ANNEX_A:
		हाल SYS_DVBC_ANNEX_C:
			अगर (!state->m_has_dvbc)
				वापस -EINVAL;
			state->m_itut_annex_c = (delsys == SYS_DVBC_ANNEX_C) ?
						true : false;
			अगर (state->m_itut_annex_c)
				setoperation_mode(state, OM_QAM_ITU_C);
			अन्यथा
				setoperation_mode(state, OM_QAM_ITU_A);
			अवरोध;
		हाल SYS_DVBT:
			अगर (!state->m_has_dvbt)
				वापस -EINVAL;
			setoperation_mode(state, OM_DVBT);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	fe->ops.tuner_ops.get_अगर_frequency(fe, &IF);
	start(state, 0, IF);

	/* After set_frontend, stats aren't available */
	p->strength.stat[0].scale = FE_SCALE_RELATIVE;
	p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->pre_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->pre_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	/* prपूर्णांकk(KERN_DEBUG "drxk: %s IF=%d done\n", __func__, IF); */

	वापस 0;
पूर्ण

अटल पूर्णांक get_strength(काष्ठा drxk_state *state, u64 *strength)
अणु
	पूर्णांक status;
	काष्ठा s_cfg_agc   rf_agc, अगर_agc;
	u32          total_gain  = 0;
	u32          atten      = 0;
	u32          agc_range   = 0;
	u16            scu_lvl  = 0;
	u16            scu_coc  = 0;
	/* FIXME: those are part of the tuner presets */
	u16 tuner_rf_gain         = 50; /* Default value on az6007 driver */
	u16 tuner_अगर_gain         = 40; /* Default value on az6007 driver */

	*strength = 0;

	अगर (is_dvbt(state)) अणु
		rf_agc = state->m_dvbt_rf_agc_cfg;
		अगर_agc = state->m_dvbt_अगर_agc_cfg;
	पूर्ण अन्यथा अगर (is_qam(state)) अणु
		rf_agc = state->m_qam_rf_agc_cfg;
		अगर_agc = state->m_qam_अगर_agc_cfg;
	पूर्ण अन्यथा अणु
		rf_agc = state->m_atv_rf_agc_cfg;
		अगर_agc = state->m_atv_अगर_agc_cfg;
	पूर्ण

	अगर (rf_agc.ctrl_mode == DRXK_AGC_CTRL_AUTO) अणु
		/* SCU output_level */
		status = पढ़ो16(state, SCU_RAM_AGC_RF_IACCU_HI__A, &scu_lvl);
		अगर (status < 0)
			वापस status;

		/* SCU c.o.c. */
		status = पढ़ो16(state, SCU_RAM_AGC_RF_IACCU_HI_CO__A, &scu_coc);
		अगर (status < 0)
			वापस status;

		अगर (((u32) scu_lvl + (u32) scu_coc) < 0xffff)
			rf_agc.output_level = scu_lvl + scu_coc;
		अन्यथा
			rf_agc.output_level = 0xffff;

		/* Take RF gain पूर्णांकo account */
		total_gain += tuner_rf_gain;

		/* clip output value */
		अगर (rf_agc.output_level < rf_agc.min_output_level)
			rf_agc.output_level = rf_agc.min_output_level;
		अगर (rf_agc.output_level > rf_agc.max_output_level)
			rf_agc.output_level = rf_agc.max_output_level;

		agc_range = (u32) (rf_agc.max_output_level - rf_agc.min_output_level);
		अगर (agc_range > 0) अणु
			atten += 100UL *
				((u32)(tuner_rf_gain)) *
				((u32)(rf_agc.output_level - rf_agc.min_output_level))
				/ agc_range;
		पूर्ण
	पूर्ण

	अगर (अगर_agc.ctrl_mode == DRXK_AGC_CTRL_AUTO) अणु
		status = पढ़ो16(state, SCU_RAM_AGC_IF_IACCU_HI__A,
				&अगर_agc.output_level);
		अगर (status < 0)
			वापस status;

		status = पढ़ो16(state, SCU_RAM_AGC_INGAIN_TGT_MIN__A,
				&अगर_agc.top);
		अगर (status < 0)
			वापस status;

		/* Take IF gain पूर्णांकo account */
		total_gain += (u32) tuner_अगर_gain;

		/* clip output value */
		अगर (अगर_agc.output_level < अगर_agc.min_output_level)
			अगर_agc.output_level = अगर_agc.min_output_level;
		अगर (अगर_agc.output_level > अगर_agc.max_output_level)
			अगर_agc.output_level = अगर_agc.max_output_level;

		agc_range  = (u32)(अगर_agc.max_output_level - अगर_agc.min_output_level);
		अगर (agc_range > 0) अणु
			atten += 100UL *
				((u32)(tuner_अगर_gain)) *
				((u32)(अगर_agc.output_level - अगर_agc.min_output_level))
				/ agc_range;
		पूर्ण
	पूर्ण

	/*
	 * Convert to 0..65535 scale.
	 * If it can't be measured (AGC is disabled), just show 100%.
	 */
	अगर (total_gain > 0)
		*strength = (65535UL * atten / total_gain / 100);
	अन्यथा
		*strength = 65535;

	वापस 0;
पूर्ण

अटल पूर्णांक drxk_get_stats(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा drxk_state *state = fe->demodulator_priv;
	पूर्णांक status;
	u32 stat;
	u16 reg16;
	u32 post_bit_count;
	u32 post_bit_err_count;
	u32 post_bit_error_scale;
	u32 pre_bit_err_count;
	u32 pre_bit_count;
	u32 pkt_count;
	u32 pkt_error_count;
	s32 cnr;

	अगर (state->m_drxk_state == DRXK_NO_DEV)
		वापस -ENODEV;
	अगर (state->m_drxk_state == DRXK_UNINITIALIZED)
		वापस -EAGAIN;

	/* get status */
	state->fe_status = 0;
	get_lock_status(state, &stat);
	अगर (stat == MPEG_LOCK)
		state->fe_status |= 0x1f;
	अगर (stat == FEC_LOCK)
		state->fe_status |= 0x0f;
	अगर (stat == DEMOD_LOCK)
		state->fe_status |= 0x07;

	/*
	 * Estimate संकेत strength from AGC
	 */
	get_strength(state, &c->strength.stat[0].uvalue);
	c->strength.stat[0].scale = FE_SCALE_RELATIVE;


	अगर (stat >= DEMOD_LOCK) अणु
		get_संकेत_to_noise(state, &cnr);
		c->cnr.stat[0].svalue = cnr * 100;
		c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
	पूर्ण अन्यथा अणु
		c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	अगर (stat < FEC_LOCK) अणु
		c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->pre_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->pre_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		वापस 0;
	पूर्ण

	/* Get post BER */

	/* BER measurement is valid अगर at least FEC lock is achieved */

	/*
	 * OFDM_EC_VD_REQ_SMB_CNT__A and/or OFDM_EC_VD_REQ_BIT_CNT can be
	 * written to set nr of symbols or bits over which to measure
	 * EC_VD_REG_ERR_BIT_CNT__A . See CtrlSetCfg().
	 */

	/* Read रेजिस्टरs क्रम post/preViterbi BER calculation */
	status = पढ़ो16(state, OFDM_EC_VD_ERR_BIT_CNT__A, &reg16);
	अगर (status < 0)
		जाओ error;
	pre_bit_err_count = reg16;

	status = पढ़ो16(state, OFDM_EC_VD_IN_BIT_CNT__A , &reg16);
	अगर (status < 0)
		जाओ error;
	pre_bit_count = reg16;

	/* Number of bit-errors */
	status = पढ़ो16(state, FEC_RS_NR_BIT_ERRORS__A, &reg16);
	अगर (status < 0)
		जाओ error;
	post_bit_err_count = reg16;

	status = पढ़ो16(state, FEC_RS_MEASUREMENT_PRESCALE__A, &reg16);
	अगर (status < 0)
		जाओ error;
	post_bit_error_scale = reg16;

	status = पढ़ो16(state, FEC_RS_MEASUREMENT_PERIOD__A, &reg16);
	अगर (status < 0)
		जाओ error;
	pkt_count = reg16;

	status = पढ़ो16(state, SCU_RAM_FEC_ACCUM_PKT_FAILURES__A, &reg16);
	अगर (status < 0)
		जाओ error;
	pkt_error_count = reg16;
	ग_लिखो16(state, SCU_RAM_FEC_ACCUM_PKT_FAILURES__A, 0);

	post_bit_err_count *= post_bit_error_scale;

	post_bit_count = pkt_count * 204 * 8;

	/* Store the results */
	c->block_error.stat[0].scale = FE_SCALE_COUNTER;
	c->block_error.stat[0].uvalue += pkt_error_count;
	c->block_count.stat[0].scale = FE_SCALE_COUNTER;
	c->block_count.stat[0].uvalue += pkt_count;

	c->pre_bit_error.stat[0].scale = FE_SCALE_COUNTER;
	c->pre_bit_error.stat[0].uvalue += pre_bit_err_count;
	c->pre_bit_count.stat[0].scale = FE_SCALE_COUNTER;
	c->pre_bit_count.stat[0].uvalue += pre_bit_count;

	c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
	c->post_bit_error.stat[0].uvalue += post_bit_err_count;
	c->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
	c->post_bit_count.stat[0].uvalue += post_bit_count;

error:
	वापस status;
पूर्ण


अटल पूर्णांक drxk_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा drxk_state *state = fe->demodulator_priv;
	पूर्णांक rc;

	dprपूर्णांकk(1, "\n");

	rc = drxk_get_stats(fe);
	अगर (rc < 0)
		वापस rc;

	*status = state->fe_status;

	वापस 0;
पूर्ण

अटल पूर्णांक drxk_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe,
				     u16 *strength)
अणु
	काष्ठा drxk_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	dprपूर्णांकk(1, "\n");

	अगर (state->m_drxk_state == DRXK_NO_DEV)
		वापस -ENODEV;
	अगर (state->m_drxk_state == DRXK_UNINITIALIZED)
		वापस -EAGAIN;

	*strength = c->strength.stat[0].uvalue;
	वापस 0;
पूर्ण

अटल पूर्णांक drxk_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा drxk_state *state = fe->demodulator_priv;
	s32 snr2;

	dprपूर्णांकk(1, "\n");

	अगर (state->m_drxk_state == DRXK_NO_DEV)
		वापस -ENODEV;
	अगर (state->m_drxk_state == DRXK_UNINITIALIZED)
		वापस -EAGAIN;

	get_संकेत_to_noise(state, &snr2);

	/* No negative SNR, clip to zero */
	अगर (snr2 < 0)
		snr2 = 0;
	*snr = snr2 & 0xffff;
	वापस 0;
पूर्ण

अटल पूर्णांक drxk_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	काष्ठा drxk_state *state = fe->demodulator_priv;
	u16 err;

	dprपूर्णांकk(1, "\n");

	अगर (state->m_drxk_state == DRXK_NO_DEV)
		वापस -ENODEV;
	अगर (state->m_drxk_state == DRXK_UNINITIALIZED)
		वापस -EAGAIN;

	dvbtqam_get_acc_pkt_err(state, &err);
	*ucblocks = (u32) err;
	वापस 0;
पूर्ण

अटल पूर्णांक drxk_get_tune_settings(काष्ठा dvb_frontend *fe,
				  काष्ठा dvb_frontend_tune_settings *sets)
अणु
	काष्ठा drxk_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;

	dprपूर्णांकk(1, "\n");

	अगर (state->m_drxk_state == DRXK_NO_DEV)
		वापस -ENODEV;
	अगर (state->m_drxk_state == DRXK_UNINITIALIZED)
		वापस -EAGAIN;

	चयन (p->delivery_प्रणाली) अणु
	हाल SYS_DVBC_ANNEX_A:
	हाल SYS_DVBC_ANNEX_C:
	हाल SYS_DVBT:
		sets->min_delay_ms = 3000;
		sets->max_drअगरt = 0;
		sets->step_size = 0;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops drxk_ops = अणु
	/* .delsys will be filled dynamically */
	.info = अणु
		.name = "DRXK",
		.frequency_min_hz =  47 * MHz,
		.frequency_max_hz = 865 * MHz,
		 /* For DVB-C */
		.symbol_rate_min =   870000,
		.symbol_rate_max = 11700000,
		/* For DVB-T */
		.frequency_stepsize_hz = 166667,

		.caps = FE_CAN_QAM_16 | FE_CAN_QAM_32 | FE_CAN_QAM_64 |
			FE_CAN_QAM_128 | FE_CAN_QAM_256 | FE_CAN_FEC_AUTO |
			FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_MUTE_TS |
			FE_CAN_TRANSMISSION_MODE_AUTO | FE_CAN_RECOVER |
			FE_CAN_GUARD_INTERVAL_AUTO | FE_CAN_HIERARCHY_AUTO
	पूर्ण,

	.release = drxk_release,
	.sleep = drxk_sleep,
	.i2c_gate_ctrl = drxk_gate_ctrl,

	.set_frontend = drxk_set_parameters,
	.get_tune_settings = drxk_get_tune_settings,

	.पढ़ो_status = drxk_पढ़ो_status,
	.पढ़ो_संकेत_strength = drxk_पढ़ो_संकेत_strength,
	.पढ़ो_snr = drxk_पढ़ो_snr,
	.पढ़ो_ucblocks = drxk_पढ़ो_ucblocks,
पूर्ण;

काष्ठा dvb_frontend *drxk_attach(स्थिर काष्ठा drxk_config *config,
				 काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा dtv_frontend_properties *p;
	काष्ठा drxk_state *state = शून्य;
	u8 adr = config->adr;
	पूर्णांक status;

	dprपूर्णांकk(1, "\n");
	state = kzalloc(माप(काष्ठा drxk_state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	state->i2c = i2c;
	state->demod_address = adr;
	state->single_master = config->single_master;
	state->microcode_name = config->microcode_name;
	state->qam_demod_parameter_count = config->qam_demod_parameter_count;
	state->no_i2c_bridge = config->no_i2c_bridge;
	state->antenna_gpio = config->antenna_gpio;
	state->antenna_dvbt = config->antenna_dvbt;
	state->m_chunk_size = config->chunk_size;
	state->enable_merr_cfg = config->enable_merr_cfg;

	अगर (config->dynamic_clk) अणु
		state->m_dvbt_अटल_clk = false;
		state->m_dvbc_अटल_clk = false;
	पूर्ण अन्यथा अणु
		state->m_dvbt_अटल_clk = true;
		state->m_dvbc_अटल_clk = true;
	पूर्ण


	अगर (config->mpeg_out_clk_strength)
		state->m_ts_घड़ीk_strength = config->mpeg_out_clk_strength & 0x07;
	अन्यथा
		state->m_ts_घड़ीk_strength = 0x06;

	अगर (config->parallel_ts)
		state->m_enable_parallel = true;
	अन्यथा
		state->m_enable_parallel = false;

	/* NOTE: as more UIO bits will be used, add them to the mask */
	state->uio_mask = config->antenna_gpio;

	/* Default gpio to DVB-C */
	अगर (!state->antenna_dvbt && state->antenna_gpio)
		state->m_gpio |= state->antenna_gpio;
	अन्यथा
		state->m_gpio &= ~state->antenna_gpio;

	mutex_init(&state->mutex);

	स_नकल(&state->frontend.ops, &drxk_ops, माप(drxk_ops));
	state->frontend.demodulator_priv = state;

	init_state(state);

	/* Load firmware and initialize DRX-K */
	अगर (state->microcode_name) अणु
		स्थिर काष्ठा firmware *fw = शून्य;

		status = request_firmware(&fw, state->microcode_name,
					  state->i2c->dev.parent);
		अगर (status < 0)
			fw = शून्य;
		load_firmware_cb(fw, state);
	पूर्ण अन्यथा अगर (init_drxk(state) < 0)
		जाओ error;


	/* Initialize stats */
	p = &state->frontend.dtv_property_cache;
	p->strength.len = 1;
	p->cnr.len = 1;
	p->block_error.len = 1;
	p->block_count.len = 1;
	p->pre_bit_error.len = 1;
	p->pre_bit_count.len = 1;
	p->post_bit_error.len = 1;
	p->post_bit_count.len = 1;

	p->strength.stat[0].scale = FE_SCALE_RELATIVE;
	p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->pre_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->pre_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	pr_info("frontend initialized.\n");
	वापस &state->frontend;

error:
	pr_err("not found\n");
	kमुक्त(state);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(drxk_attach);

MODULE_DESCRIPTION("DRX-K driver");
MODULE_AUTHOR("Ralph Metzler");
MODULE_LICENSE("GPL");
