<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Linux-DVB Driver क्रम DiBcom's DiB9000 and demodulator-family.
 *
 * Copyright (C) 2005-10 DiBcom (http://www.dibcom.fr/)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>

#समावेश <media/dvb_गणित.स>
#समावेश <media/dvb_frontend.h>

#समावेश "dib9000.h"
#समावेश "dibx000_common.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "turn on debugging (default: 0)");

#घोषणा dprपूर्णांकk(fmt, arg...) करो अणु					\
	अगर (debug)							\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: " fmt),			\
		       __func__, ##arg);				\
पूर्ण जबतक (0)

#घोषणा MAX_NUMBER_OF_FRONTENDS 6

काष्ठा i2c_device अणु
	काष्ठा i2c_adapter *i2c_adap;
	u8 i2c_addr;
	u8 *i2c_पढ़ो_buffer;
	u8 *i2c_ग_लिखो_buffer;
पूर्ण;

काष्ठा dib9000_pid_ctrl अणु
#घोषणा DIB9000_PID_FILTER_CTRL 0
#घोषणा DIB9000_PID_FILTER      1
	u8 cmd;
	u8 id;
	u16 pid;
	u8 onoff;
पूर्ण;

काष्ठा dib9000_state अणु
	काष्ठा i2c_device i2c;

	काष्ठा dibx000_i2c_master i2c_master;
	काष्ठा i2c_adapter tuner_adap;
	काष्ठा i2c_adapter component_bus;

	u16 revision;
	u8 reg_offs;

	क्रमागत frontend_tune_state tune_state;
	u32 status;
	काष्ठा dvb_frontend_parametersContext channel_status;

	u8 fe_id;

#घोषणा DIB9000_GPIO_DEFAULT_सूचीECTIONS 0xffff
	u16 gpio_dir;
#घोषणा DIB9000_GPIO_DEFAULT_VALUES     0x0000
	u16 gpio_val;
#घोषणा DIB9000_GPIO_DEFAULT_PWM_POS    0xffff
	u16 gpio_pwm_pos;

	जोड़ अणु			/* common क्रम all chips */
		काष्ठा अणु
			u8 mobile_mode:1;
		पूर्ण host;

		काष्ठा अणु
			काष्ठा dib9000_fe_memory_map अणु
				u16 addr;
				u16 size;
			पूर्ण fe_mm[18];
			u8 memcmd;

			काष्ठा mutex mbx_अगर_lock;	/* to protect पढ़ो/ग_लिखो operations */
			काष्ठा mutex mbx_lock;	/* to protect the whole mailbox handling */

			काष्ठा mutex mem_lock;	/* to protect the memory accesses */
			काष्ठा mutex mem_mbx_lock;	/* to protect the memory-based mailbox */

#घोषणा MBX_MAX_WORDS (256 - 200 - 2)
#घोषणा DIB9000_MSG_CACHE_SIZE 2
			u16 message_cache[DIB9000_MSG_CACHE_SIZE][MBX_MAX_WORDS];
			u8 fw_is_running;
		पूर्ण risc;
	पूर्ण platक्रमm;

	जोड़ अणु			/* common क्रम all platक्रमms */
		काष्ठा अणु
			काष्ठा dib9000_config cfg;
		पूर्ण d9;
	पूर्ण chip;

	काष्ठा dvb_frontend *fe[MAX_NUMBER_OF_FRONTENDS];
	u16 component_bus_speed;

	/* क्रम the I2C transfer */
	काष्ठा i2c_msg msg[2];
	u8 i2c_ग_लिखो_buffer[255];
	u8 i2c_पढ़ो_buffer[255];
	काष्ठा mutex demod_lock;
	u8 get_frontend_पूर्णांकernal;
	काष्ठा dib9000_pid_ctrl pid_ctrl[10];
	s8 pid_ctrl_index; /* -1: empty list; -2: करो not use the list */
पूर्ण;

अटल स्थिर u32 fe_info[44] = अणु 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
पूर्ण;

क्रमागत dib9000_घातer_mode अणु
	DIB9000_POWER_ALL = 0,

	DIB9000_POWER_NO,
	DIB9000_POWER_INTERF_ANALOG_AGC,
	DIB9000_POWER_COR4_DINTLV_ICIRM_EQUAL_CFROD,
	DIB9000_POWER_COR4_CRY_ESRAM_MOUT_NUD,
	DIB9000_POWER_INTERFACE_ONLY,
पूर्ण;

क्रमागत dib9000_out_messages अणु
	OUT_MSG_HBM_ACK,
	OUT_MSG_HOST_BUF_FAIL,
	OUT_MSG_REQ_VERSION,
	OUT_MSG_BRIDGE_I2C_W,
	OUT_MSG_BRIDGE_I2C_R,
	OUT_MSG_BRIDGE_APB_W,
	OUT_MSG_BRIDGE_APB_R,
	OUT_MSG_SCAN_CHANNEL,
	OUT_MSG_MONIT_DEMOD,
	OUT_MSG_CONF_GPIO,
	OUT_MSG_DEBUG_HELP,
	OUT_MSG_SUBBAND_SEL,
	OUT_MSG_ENABLE_TIME_SLICE,
	OUT_MSG_FE_FW_DL,
	OUT_MSG_FE_CHANNEL_SEARCH,
	OUT_MSG_FE_CHANNEL_TUNE,
	OUT_MSG_FE_SLEEP,
	OUT_MSG_FE_SYNC,
	OUT_MSG_CTL_MONIT,

	OUT_MSG_CONF_SVC,
	OUT_MSG_SET_HBM,
	OUT_MSG_INIT_DEMOD,
	OUT_MSG_ENABLE_DIVERSITY,
	OUT_MSG_SET_OUTPUT_MODE,
	OUT_MSG_SET_PRIORITARY_CHANNEL,
	OUT_MSG_ACK_FRG,
	OUT_MSG_INIT_PMU,
पूर्ण;

क्रमागत dib9000_in_messages अणु
	IN_MSG_DATA,
	IN_MSG_FRAME_INFO,
	IN_MSG_CTL_MONIT,
	IN_MSG_ACK_FREE_ITEM,
	IN_MSG_DEBUG_BUF,
	IN_MSG_MPE_MONITOR,
	IN_MSG_RAWTS_MONITOR,
	IN_MSG_END_BRIDGE_I2C_RW,
	IN_MSG_END_BRIDGE_APB_RW,
	IN_MSG_VERSION,
	IN_MSG_END_OF_SCAN,
	IN_MSG_MONIT_DEMOD,
	IN_MSG_ERROR,
	IN_MSG_FE_FW_DL_DONE,
	IN_MSG_EVENT,
	IN_MSG_ACK_CHANGE_SVC,
	IN_MSG_HBM_PROF,
पूर्ण;

/* memory_access requests */
#घोषणा FE_MM_W_CHANNEL                   0
#घोषणा FE_MM_W_FE_INFO                   1
#घोषणा FE_MM_RW_SYNC                     2

#घोषणा FE_SYNC_CHANNEL          1
#घोषणा FE_SYNC_W_GENERIC_MONIT	 2
#घोषणा FE_SYNC_COMPONENT_ACCESS 3

#घोषणा FE_MM_R_CHANNEL_SEARCH_STATE      3
#घोषणा FE_MM_R_CHANNEL_UNION_CONTEXT     4
#घोषणा FE_MM_R_FE_INFO                   5
#घोषणा FE_MM_R_FE_MONITOR                6

#घोषणा FE_MM_W_CHANNEL_HEAD              7
#घोषणा FE_MM_W_CHANNEL_UNION             8
#घोषणा FE_MM_W_CHANNEL_CONTEXT           9
#घोषणा FE_MM_R_CHANNEL_UNION            10
#घोषणा FE_MM_R_CHANNEL_CONTEXT          11
#घोषणा FE_MM_R_CHANNEL_TUNE_STATE       12

#घोषणा FE_MM_R_GENERIC_MONITORING_SIZE	 13
#घोषणा FE_MM_W_GENERIC_MONITORING	     14
#घोषणा FE_MM_R_GENERIC_MONITORING	     15

#घोषणा FE_MM_W_COMPONENT_ACCESS         16
#घोषणा FE_MM_RW_COMPONENT_ACCESS_BUFFER 17
अटल पूर्णांक dib9000_risc_apb_access_पढ़ो(काष्ठा dib9000_state *state, u32 address, u16 attribute, स्थिर u8 * tx, u32 txlen, u8 * b, u32 len);
अटल पूर्णांक dib9000_risc_apb_access_ग_लिखो(काष्ठा dib9000_state *state, u32 address, u16 attribute, स्थिर u8 * b, u32 len);

अटल u16 to_fw_output_mode(u16 mode)
अणु
	चयन (mode) अणु
	हाल OUTMODE_HIGH_Z:
		वापस 0;
	हाल OUTMODE_MPEG2_PAR_GATED_CLK:
		वापस 4;
	हाल OUTMODE_MPEG2_PAR_CONT_CLK:
		वापस 8;
	हाल OUTMODE_MPEG2_SERIAL:
		वापस 16;
	हाल OUTMODE_DIVERSITY:
		वापस 128;
	हाल OUTMODE_MPEG2_FIFO:
		वापस 2;
	हाल OUTMODE_ANALOG_ADC:
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक dib9000_पढ़ो16_attr(काष्ठा dib9000_state *state, u16 reg, u8 *b, u32 len, u16 attribute)
अणु
	u32 chunk_size = 126;
	u32 l;
	पूर्णांक ret;

	अगर (state->platक्रमm.risc.fw_is_running && (reg < 1024))
		वापस dib9000_risc_apb_access_पढ़ो(state, reg, attribute, शून्य, 0, b, len);

	स_रखो(state->msg, 0, 2 * माप(काष्ठा i2c_msg));
	state->msg[0].addr = state->i2c.i2c_addr >> 1;
	state->msg[0].flags = 0;
	state->msg[0].buf = state->i2c_ग_लिखो_buffer;
	state->msg[0].len = 2;
	state->msg[1].addr = state->i2c.i2c_addr >> 1;
	state->msg[1].flags = I2C_M_RD;
	state->msg[1].buf = b;
	state->msg[1].len = len;

	state->i2c_ग_लिखो_buffer[0] = reg >> 8;
	state->i2c_ग_लिखो_buffer[1] = reg & 0xff;

	अगर (attribute & DATA_BUS_ACCESS_MODE_8BIT)
		state->i2c_ग_लिखो_buffer[0] |= (1 << 5);
	अगर (attribute & DATA_BUS_ACCESS_MODE_NO_ADDRESS_INCREMENT)
		state->i2c_ग_लिखो_buffer[0] |= (1 << 4);

	करो अणु
		l = len < chunk_size ? len : chunk_size;
		state->msg[1].len = l;
		state->msg[1].buf = b;
		ret = i2c_transfer(state->i2c.i2c_adap, state->msg, 2) != 2 ? -EREMOTEIO : 0;
		अगर (ret != 0) अणु
			dprपूर्णांकk("i2c read error on %d\n", reg);
			वापस -EREMOTEIO;
		पूर्ण

		b += l;
		len -= l;

		अगर (!(attribute & DATA_BUS_ACCESS_MODE_NO_ADDRESS_INCREMENT))
			reg += l / 2;
	पूर्ण जबतक ((ret == 0) && len);

	वापस 0;
पूर्ण

अटल u16 dib9000_i2c_पढ़ो16(काष्ठा i2c_device *i2c, u16 reg)
अणु
	काष्ठा i2c_msg msg[2] = अणु
		अणु.addr = i2c->i2c_addr >> 1, .flags = 0,
			.buf = i2c->i2c_ग_लिखो_buffer, .len = 2पूर्ण,
		अणु.addr = i2c->i2c_addr >> 1, .flags = I2C_M_RD,
			.buf = i2c->i2c_पढ़ो_buffer, .len = 2पूर्ण,
	पूर्ण;

	i2c->i2c_ग_लिखो_buffer[0] = reg >> 8;
	i2c->i2c_ग_लिखो_buffer[1] = reg & 0xff;

	अगर (i2c_transfer(i2c->i2c_adap, msg, 2) != 2) अणु
		dprपूर्णांकk("read register %x error\n", reg);
		वापस 0;
	पूर्ण

	वापस (i2c->i2c_पढ़ो_buffer[0] << 8) | i2c->i2c_पढ़ो_buffer[1];
पूर्ण

अटल अंतरभूत u16 dib9000_पढ़ो_word(काष्ठा dib9000_state *state, u16 reg)
अणु
	अगर (dib9000_पढ़ो16_attr(state, reg, state->i2c_पढ़ो_buffer, 2, 0) != 0)
		वापस 0;
	वापस (state->i2c_पढ़ो_buffer[0] << 8) | state->i2c_पढ़ो_buffer[1];
पूर्ण

अटल अंतरभूत u16 dib9000_पढ़ो_word_attr(काष्ठा dib9000_state *state, u16 reg, u16 attribute)
अणु
	अगर (dib9000_पढ़ो16_attr(state, reg, state->i2c_पढ़ो_buffer, 2,
				attribute) != 0)
		वापस 0;
	वापस (state->i2c_पढ़ो_buffer[0] << 8) | state->i2c_पढ़ो_buffer[1];
पूर्ण

#घोषणा dib9000_पढ़ो16_noinc_attr(state, reg, b, len, attribute) dib9000_पढ़ो16_attr(state, reg, b, len, (attribute) | DATA_BUS_ACCESS_MODE_NO_ADDRESS_INCREMENT)

अटल पूर्णांक dib9000_ग_लिखो16_attr(काष्ठा dib9000_state *state, u16 reg, स्थिर u8 *buf, u32 len, u16 attribute)
अणु
	u32 chunk_size = 126;
	u32 l;
	पूर्णांक ret;

	अगर (state->platक्रमm.risc.fw_is_running && (reg < 1024)) अणु
		अगर (dib9000_risc_apb_access_ग_लिखो
		    (state, reg, DATA_BUS_ACCESS_MODE_16BIT | DATA_BUS_ACCESS_MODE_NO_ADDRESS_INCREMENT | attribute, buf, len) != 0)
			वापस -EINVAL;
		वापस 0;
	पूर्ण

	स_रखो(&state->msg[0], 0, माप(काष्ठा i2c_msg));
	state->msg[0].addr = state->i2c.i2c_addr >> 1;
	state->msg[0].flags = 0;
	state->msg[0].buf = state->i2c_ग_लिखो_buffer;
	state->msg[0].len = len + 2;

	state->i2c_ग_लिखो_buffer[0] = (reg >> 8) & 0xff;
	state->i2c_ग_लिखो_buffer[1] = (reg) & 0xff;

	अगर (attribute & DATA_BUS_ACCESS_MODE_8BIT)
		state->i2c_ग_लिखो_buffer[0] |= (1 << 5);
	अगर (attribute & DATA_BUS_ACCESS_MODE_NO_ADDRESS_INCREMENT)
		state->i2c_ग_लिखो_buffer[0] |= (1 << 4);

	करो अणु
		l = len < chunk_size ? len : chunk_size;
		state->msg[0].len = l + 2;
		स_नकल(&state->i2c_ग_लिखो_buffer[2], buf, l);

		ret = i2c_transfer(state->i2c.i2c_adap, state->msg, 1) != 1 ? -EREMOTEIO : 0;

		buf += l;
		len -= l;

		अगर (!(attribute & DATA_BUS_ACCESS_MODE_NO_ADDRESS_INCREMENT))
			reg += l / 2;
	पूर्ण जबतक ((ret == 0) && len);

	वापस ret;
पूर्ण

अटल पूर्णांक dib9000_i2c_ग_लिखो16(काष्ठा i2c_device *i2c, u16 reg, u16 val)
अणु
	काष्ठा i2c_msg msg = अणु
		.addr = i2c->i2c_addr >> 1, .flags = 0,
		.buf = i2c->i2c_ग_लिखो_buffer, .len = 4
	पूर्ण;

	i2c->i2c_ग_लिखो_buffer[0] = (reg >> 8) & 0xff;
	i2c->i2c_ग_लिखो_buffer[1] = reg & 0xff;
	i2c->i2c_ग_लिखो_buffer[2] = (val >> 8) & 0xff;
	i2c->i2c_ग_लिखो_buffer[3] = val & 0xff;

	वापस i2c_transfer(i2c->i2c_adap, &msg, 1) != 1 ? -EREMOTEIO : 0;
पूर्ण

अटल अंतरभूत पूर्णांक dib9000_ग_लिखो_word(काष्ठा dib9000_state *state, u16 reg, u16 val)
अणु
	u8 b[2] = अणु val >> 8, val & 0xff पूर्ण;
	वापस dib9000_ग_लिखो16_attr(state, reg, b, 2, 0);
पूर्ण

अटल अंतरभूत पूर्णांक dib9000_ग_लिखो_word_attr(काष्ठा dib9000_state *state, u16 reg, u16 val, u16 attribute)
अणु
	u8 b[2] = अणु val >> 8, val & 0xff पूर्ण;
	वापस dib9000_ग_लिखो16_attr(state, reg, b, 2, attribute);
पूर्ण

#घोषणा dib9000_ग_लिखो(state, reg, buf, len) dib9000_ग_लिखो16_attr(state, reg, buf, len, 0)
#घोषणा dib9000_ग_लिखो16_noinc(state, reg, buf, len) dib9000_ग_लिखो16_attr(state, reg, buf, len, DATA_BUS_ACCESS_MODE_NO_ADDRESS_INCREMENT)
#घोषणा dib9000_ग_लिखो16_noinc_attr(state, reg, buf, len, attribute) dib9000_ग_लिखो16_attr(state, reg, buf, len, DATA_BUS_ACCESS_MODE_NO_ADDRESS_INCREMENT | (attribute))

#घोषणा dib9000_mbx_send(state, id, data, len) dib9000_mbx_send_attr(state, id, data, len, 0)
#घोषणा dib9000_mbx_get_message(state, id, msg, len) dib9000_mbx_get_message_attr(state, id, msg, len, 0)

#घोषणा MAC_IRQ      (1 << 1)
#घोषणा IRQ_POL_MSK  (1 << 4)

#घोषणा dib9000_risc_mem_पढ़ो_chunks(state, b, len) dib9000_पढ़ो16_attr(state, 1063, b, len, DATA_BUS_ACCESS_MODE_8BIT | DATA_BUS_ACCESS_MODE_NO_ADDRESS_INCREMENT)
#घोषणा dib9000_risc_mem_ग_लिखो_chunks(state, buf, len) dib9000_ग_लिखो16_attr(state, 1063, buf, len, DATA_BUS_ACCESS_MODE_8BIT | DATA_BUS_ACCESS_MODE_NO_ADDRESS_INCREMENT)

अटल व्योम dib9000_risc_mem_setup_cmd(काष्ठा dib9000_state *state, u32 addr, u32 len, u8 पढ़ोing)
अणु
	u8 b[14] = अणु 0 पूर्ण;

/*      dprपूर्णांकk("%d memcmd: %d %d %d\n", state->fe_id, addr, addr+len, len); */
/*      b[0] = 0 << 7; */
	b[1] = 1;

/*      b[2] = 0; */
/*      b[3] = 0; */
	b[4] = (u8) (addr >> 8);
	b[5] = (u8) (addr & 0xff);

/*      b[10] = 0; */
/*      b[11] = 0; */
	b[12] = (u8) (addr >> 8);
	b[13] = (u8) (addr & 0xff);

	addr += len;
/*      b[6] = 0; */
/*      b[7] = 0; */
	b[8] = (u8) (addr >> 8);
	b[9] = (u8) (addr & 0xff);

	dib9000_ग_लिखो(state, 1056, b, 14);
	अगर (पढ़ोing)
		dib9000_ग_लिखो_word(state, 1056, (1 << 15) | 1);
	state->platक्रमm.risc.memcmd = -1;	/* अगर it was called directly reset it - to क्रमce a future setup-call to set it */
पूर्ण

अटल व्योम dib9000_risc_mem_setup(काष्ठा dib9000_state *state, u8 cmd)
अणु
	काष्ठा dib9000_fe_memory_map *m = &state->platक्रमm.risc.fe_mm[cmd & 0x7f];
	/* decide whether we need to "refresh" the memory controller */
	अगर (state->platक्रमm.risc.memcmd == cmd &&	/* same command */
	    !(cmd & 0x80 && m->size < 67))	/* and we करो not want to पढ़ो something with less than 67 bytes looping - working around a bug in the memory controller */
		वापस;
	dib9000_risc_mem_setup_cmd(state, m->addr, m->size, cmd & 0x80);
	state->platक्रमm.risc.memcmd = cmd;
पूर्ण

अटल पूर्णांक dib9000_risc_mem_पढ़ो(काष्ठा dib9000_state *state, u8 cmd, u8 * b, u16 len)
अणु
	अगर (!state->platक्रमm.risc.fw_is_running)
		वापस -EIO;

	अगर (mutex_lock_पूर्णांकerruptible(&state->platक्रमm.risc.mem_lock) < 0) अणु
		dprपूर्णांकk("could not get the lock\n");
		वापस -EINTR;
	पूर्ण
	dib9000_risc_mem_setup(state, cmd | 0x80);
	dib9000_risc_mem_पढ़ो_chunks(state, b, len);
	mutex_unlock(&state->platक्रमm.risc.mem_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक dib9000_risc_mem_ग_लिखो(काष्ठा dib9000_state *state, u8 cmd, स्थिर u8 * b)
अणु
	काष्ठा dib9000_fe_memory_map *m = &state->platक्रमm.risc.fe_mm[cmd];
	अगर (!state->platक्रमm.risc.fw_is_running)
		वापस -EIO;

	अगर (mutex_lock_पूर्णांकerruptible(&state->platक्रमm.risc.mem_lock) < 0) अणु
		dprपूर्णांकk("could not get the lock\n");
		वापस -EINTR;
	पूर्ण
	dib9000_risc_mem_setup(state, cmd);
	dib9000_risc_mem_ग_लिखो_chunks(state, b, m->size);
	mutex_unlock(&state->platक्रमm.risc.mem_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक dib9000_firmware_करोwnload(काष्ठा dib9000_state *state, u8 risc_id, u16 key, स्थिर u8 * code, u32 len)
अणु
	u16 offs;

	अगर (risc_id == 1)
		offs = 16;
	अन्यथा
		offs = 0;

	/* config crtl reg */
	dib9000_ग_लिखो_word(state, 1024 + offs, 0x000f);
	dib9000_ग_लिखो_word(state, 1025 + offs, 0);
	dib9000_ग_लिखो_word(state, 1031 + offs, key);

	dprपूर्णांकk("going to download %dB of microcode\n", len);
	अगर (dib9000_ग_लिखो16_noinc(state, 1026 + offs, (u8 *) code, (u16) len) != 0) अणु
		dprपूर्णांकk("error while downloading microcode for RISC %c\n", 'A' + risc_id);
		वापस -EIO;
	पूर्ण

	dprपूर्णांकk("Microcode for RISC %c loaded\n", 'A' + risc_id);

	वापस 0;
पूर्ण

अटल पूर्णांक dib9000_mbx_host_init(काष्ठा dib9000_state *state, u8 risc_id)
अणु
	u16 mbox_offs;
	u16 reset_reg;
	u16 tries = 1000;

	अगर (risc_id == 1)
		mbox_offs = 16;
	अन्यथा
		mbox_offs = 0;

	/* Reset mailbox  */
	dib9000_ग_लिखो_word(state, 1027 + mbox_offs, 0x8000);

	/* Read reset status */
	करो अणु
		reset_reg = dib9000_पढ़ो_word(state, 1027 + mbox_offs);
		msleep(100);
	पूर्ण जबतक ((reset_reg & 0x8000) && --tries);

	अगर (reset_reg & 0x8000) अणु
		dprपूर्णांकk("MBX: init ERROR, no response from RISC %c\n", 'A' + risc_id);
		वापस -EIO;
	पूर्ण
	dprपूर्णांकk("MBX: initialized\n");
	वापस 0;
पूर्ण

#घोषणा MAX_MAILBOX_TRY 100
अटल पूर्णांक dib9000_mbx_send_attr(काष्ठा dib9000_state *state, u8 id, u16 * data, u8 len, u16 attr)
अणु
	u8 *d, b[2];
	u16 पंचांगp;
	u16 size;
	u32 i;
	पूर्णांक ret = 0;

	अगर (!state->platक्रमm.risc.fw_is_running)
		वापस -EINVAL;

	अगर (mutex_lock_पूर्णांकerruptible(&state->platक्रमm.risc.mbx_अगर_lock) < 0) अणु
		dprपूर्णांकk("could not get the lock\n");
		वापस -EINTR;
	पूर्ण
	पंचांगp = MAX_MAILBOX_TRY;
	करो अणु
		size = dib9000_पढ़ो_word_attr(state, 1043, attr) & 0xff;
		अगर ((size + len + 1) > MBX_MAX_WORDS && --पंचांगp) अणु
			dprपूर्णांकk("MBX: RISC mbx full, retrying\n");
			msleep(100);
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण जबतक (1);

	/*dprपूर्णांकk( "MBX: size: %d\n", size); */

	अगर (पंचांगp == 0) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
#अगर_घोषित DUMP_MSG
	dprपूर्णांकk("--> %02x %d %*ph\n", id, len + 1, len, data);
#पूर्ण_अगर

	/* byte-order conversion - works on big (where it is not necessary) or little endian */
	d = (u8 *) data;
	क्रम (i = 0; i < len; i++) अणु
		पंचांगp = data[i];
		*d++ = पंचांगp >> 8;
		*d++ = पंचांगp & 0xff;
	पूर्ण

	/* ग_लिखो msg */
	b[0] = id;
	b[1] = len + 1;
	अगर (dib9000_ग_लिखो16_noinc_attr(state, 1045, b, 2, attr) != 0 || dib9000_ग_लिखो16_noinc_attr(state, 1045, (u8 *) data, len * 2, attr) != 0) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	/* update रेजिस्टर nb_mes_in_RX */
	ret = (u8) dib9000_ग_लिखो_word_attr(state, 1043, 1 << 14, attr);

out:
	mutex_unlock(&state->platक्रमm.risc.mbx_अगर_lock);

	वापस ret;
पूर्ण

अटल u8 dib9000_mbx_पढ़ो(काष्ठा dib9000_state *state, u16 * data, u8 risc_id, u16 attr)
अणु
#अगर_घोषित DUMP_MSG
	u16 *d = data;
#पूर्ण_अगर

	u16 पंचांगp, i;
	u8 size;
	u8 mc_base;

	अगर (!state->platक्रमm.risc.fw_is_running)
		वापस 0;

	अगर (mutex_lock_पूर्णांकerruptible(&state->platक्रमm.risc.mbx_अगर_lock) < 0) अणु
		dprपूर्णांकk("could not get the lock\n");
		वापस 0;
	पूर्ण
	अगर (risc_id == 1)
		mc_base = 16;
	अन्यथा
		mc_base = 0;

	/* Length and type in the first word */
	*data = dib9000_पढ़ो_word_attr(state, 1029 + mc_base, attr);

	size = *data & 0xff;
	अगर (size <= MBX_MAX_WORDS) अणु
		data++;
		size--;		/* Initial word alपढ़ोy पढ़ो */

		dib9000_पढ़ो16_noinc_attr(state, 1029 + mc_base, (u8 *) data, size * 2, attr);

		/* to word conversion */
		क्रम (i = 0; i < size; i++) अणु
			पंचांगp = *data;
			*data = (पंचांगp >> 8) | (पंचांगp << 8);
			data++;
		पूर्ण

#अगर_घोषित DUMP_MSG
		dprपूर्णांकk("<--\n");
		क्रम (i = 0; i < size + 1; i++)
			dprपूर्णांकk("%04x\n", d[i]);
		dprपूर्णांकk("\n");
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		dprपूर्णांकk("MBX: message is too big for message cache (%d), flushing message\n", size);
		size--;		/* Initial word alपढ़ोy पढ़ो */
		जबतक (size--)
			dib9000_पढ़ो16_noinc_attr(state, 1029 + mc_base, (u8 *) data, 2, attr);
	पूर्ण
	/* Update रेजिस्टर nb_mes_in_TX */
	dib9000_ग_लिखो_word_attr(state, 1028 + mc_base, 1 << 14, attr);

	mutex_unlock(&state->platक्रमm.risc.mbx_अगर_lock);

	वापस size + 1;
पूर्ण

अटल पूर्णांक dib9000_risc_debug_buf(काष्ठा dib9000_state *state, u16 * data, u8 size)
अणु
	u32 ts = data[1] << 16 | data[0];
	अक्षर *b = (अक्षर *)&data[2];

	b[2 * (size - 2) - 1] = '\0';	/* Bullet proof the buffer */
	अगर (*b == '~') अणु
		b++;
		dprपूर्णांकk("%s\n", b);
	पूर्ण अन्यथा
		dprपूर्णांकk("RISC%d: %d.%04d %s\n",
			state->fe_id,
			ts / 10000, ts % 10000, *b ? b : "<empty>");
	वापस 1;
पूर्ण

अटल पूर्णांक dib9000_mbx_fetch_to_cache(काष्ठा dib9000_state *state, u16 attr)
अणु
	पूर्णांक i;
	u8 size;
	u16 *block;
	/* find a मुक्त slot */
	क्रम (i = 0; i < DIB9000_MSG_CACHE_SIZE; i++) अणु
		block = state->platक्रमm.risc.message_cache[i];
		अगर (*block == 0) अणु
			size = dib9000_mbx_पढ़ो(state, block, 1, attr);

/*                      dprपूर्णांकk( "MBX: fetched %04x message to cache\n", *block); */

			चयन (*block >> 8) अणु
			हाल IN_MSG_DEBUG_BUF:
				dib9000_risc_debug_buf(state, block + 1, size);	/* debug-messages are going to be prपूर्णांकed right away */
				*block = 0;	/* मुक्त the block */
				अवरोध;
#अगर 0
			हाल IN_MSG_DATA:	/* FE-TRACE */
				dib9000_risc_data_process(state, block + 1, size);
				*block = 0;
				अवरोध;
#पूर्ण_अगर
			शेष:
				अवरोध;
			पूर्ण

			वापस 1;
		पूर्ण
	पूर्ण
	dprपूर्णांकk("MBX: no free cache-slot found for new message...\n");
	वापस -1;
पूर्ण

अटल u8 dib9000_mbx_count(काष्ठा dib9000_state *state, u8 risc_id, u16 attr)
अणु
	अगर (risc_id == 0)
		वापस (u8) (dib9000_पढ़ो_word_attr(state, 1028, attr) >> 10) & 0x1f;	/* 5 bit field */
	अन्यथा
		वापस (u8) (dib9000_पढ़ो_word_attr(state, 1044, attr) >> 8) & 0x7f;	/* 7 bit field */
पूर्ण

अटल पूर्णांक dib9000_mbx_process(काष्ठा dib9000_state *state, u16 attr)
अणु
	पूर्णांक ret = 0;

	अगर (!state->platक्रमm.risc.fw_is_running)
		वापस -1;

	अगर (mutex_lock_पूर्णांकerruptible(&state->platक्रमm.risc.mbx_lock) < 0) अणु
		dprपूर्णांकk("could not get the lock\n");
		वापस -1;
	पूर्ण

	अगर (dib9000_mbx_count(state, 1, attr))	/* 1=RiscB */
		ret = dib9000_mbx_fetch_to_cache(state, attr);

	dib9000_पढ़ो_word_attr(state, 1229, attr);	/* Clear the IRQ */
/*      अगर (पंचांगp) */
/*              dprपूर्णांकk( "cleared IRQ: %x\n", पंचांगp); */
	mutex_unlock(&state->platक्रमm.risc.mbx_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक dib9000_mbx_get_message_attr(काष्ठा dib9000_state *state, u16 id, u16 * msg, u8 * size, u16 attr)
अणु
	u8 i;
	u16 *block;
	u16 समयout = 30;

	*msg = 0;
	करो अणु
		/* dib9000_mbx_get_from_cache(); */
		क्रम (i = 0; i < DIB9000_MSG_CACHE_SIZE; i++) अणु
			block = state->platक्रमm.risc.message_cache[i];
			अगर ((*block >> 8) == id) अणु
				*size = (*block & 0xff) - 1;
				स_नकल(msg, block + 1, (*size) * 2);
				*block = 0;	/* मुक्त the block */
				i = 0;	/* संकेत that we found a message */
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (i == 0)
			अवरोध;

		अगर (dib9000_mbx_process(state, attr) == -1)	/* try to fetch one message - अगर any */
			वापस -1;

	पूर्ण जबतक (--समयout);

	अगर (समयout == 0) अणु
		dprपूर्णांकk("waiting for message %d timed out\n", id);
		वापस -1;
	पूर्ण

	वापस i == 0;
पूर्ण

अटल पूर्णांक dib9000_risc_check_version(काष्ठा dib9000_state *state)
अणु
	u8 r[4];
	u8 size;
	u16 fw_version = 0;

	अगर (dib9000_mbx_send(state, OUT_MSG_REQ_VERSION, &fw_version, 1) != 0)
		वापस -EIO;

	अगर (dib9000_mbx_get_message(state, IN_MSG_VERSION, (u16 *) r, &size) < 0)
		वापस -EIO;

	fw_version = (r[0] << 8) | r[1];
	dprपूर्णांकk("RISC: ver: %d.%02d (IC: %d)\n", fw_version >> 10, fw_version & 0x3ff, (r[2] << 8) | r[3]);

	अगर ((fw_version >> 10) != 7)
		वापस -EINVAL;

	चयन (fw_version & 0x3ff) अणु
	हाल 11:
	हाल 12:
	हाल 14:
	हाल 15:
	हाल 16:
	हाल 17:
		अवरोध;
	शेष:
		dprपूर्णांकk("RISC: invalid firmware version");
		वापस -EINVAL;
	पूर्ण

	dprपूर्णांकk("RISC: valid firmware version");
	वापस 0;
पूर्ण

अटल पूर्णांक dib9000_fw_boot(काष्ठा dib9000_state *state, स्थिर u8 * codeA, u32 lenA, स्थिर u8 * codeB, u32 lenB)
अणु
	/* Reconfig pool mac ram */
	dib9000_ग_लिखो_word(state, 1225, 0x02);	/* A: 8k C, 4 k D - B: 32k C 6 k D - IRAM 96k */
	dib9000_ग_लिखो_word(state, 1226, 0x05);

	/* Toggles IP crypto to Host APB पूर्णांकerface. */
	dib9000_ग_लिखो_word(state, 1542, 1);

	/* Set jump and no jump in the dma box */
	dib9000_ग_लिखो_word(state, 1074, 0);
	dib9000_ग_लिखो_word(state, 1075, 0);

	/* Set MAC as APB Master. */
	dib9000_ग_लिखो_word(state, 1237, 0);

	/* Reset the RISCs */
	अगर (codeA != शून्य)
		dib9000_ग_लिखो_word(state, 1024, 2);
	अन्यथा
		dib9000_ग_लिखो_word(state, 1024, 15);
	अगर (codeB != शून्य)
		dib9000_ग_लिखो_word(state, 1040, 2);

	अगर (codeA != शून्य)
		dib9000_firmware_करोwnload(state, 0, 0x1234, codeA, lenA);
	अगर (codeB != शून्य)
		dib9000_firmware_करोwnload(state, 1, 0x1234, codeB, lenB);

	/* Run the RISCs */
	अगर (codeA != शून्य)
		dib9000_ग_लिखो_word(state, 1024, 0);
	अगर (codeB != शून्य)
		dib9000_ग_लिखो_word(state, 1040, 0);

	अगर (codeA != शून्य)
		अगर (dib9000_mbx_host_init(state, 0) != 0)
			वापस -EIO;
	अगर (codeB != शून्य)
		अगर (dib9000_mbx_host_init(state, 1) != 0)
			वापस -EIO;

	msleep(100);
	state->platक्रमm.risc.fw_is_running = 1;

	अगर (dib9000_risc_check_version(state) != 0)
		वापस -EINVAL;

	state->platक्रमm.risc.memcmd = 0xff;
	वापस 0;
पूर्ण

अटल u16 dib9000_identअगरy(काष्ठा i2c_device *client)
अणु
	u16 value;

	value = dib9000_i2c_पढ़ो16(client, 896);
	अगर (value != 0x01b3) अणु
		dprपूर्णांकk("wrong Vendor ID (0x%x)\n", value);
		वापस 0;
	पूर्ण

	value = dib9000_i2c_पढ़ो16(client, 897);
	अगर (value != 0x4000 && value != 0x4001 && value != 0x4002 && value != 0x4003 && value != 0x4004 && value != 0x4005) अणु
		dprपूर्णांकk("wrong Device ID (0x%x)\n", value);
		वापस 0;
	पूर्ण

	/* protect this driver to be used with 7000PC */
	अगर (value == 0x4000 && dib9000_i2c_पढ़ो16(client, 769) == 0x4000) अणु
		dprपूर्णांकk("this driver does not work with DiB7000PC\n");
		वापस 0;
	पूर्ण

	चयन (value) अणु
	हाल 0x4000:
		dprपूर्णांकk("found DiB7000MA/PA/MB/PB\n");
		अवरोध;
	हाल 0x4001:
		dprपूर्णांकk("found DiB7000HC\n");
		अवरोध;
	हाल 0x4002:
		dprपूर्णांकk("found DiB7000MC\n");
		अवरोध;
	हाल 0x4003:
		dprपूर्णांकk("found DiB9000A\n");
		अवरोध;
	हाल 0x4004:
		dprपूर्णांकk("found DiB9000H\n");
		अवरोध;
	हाल 0x4005:
		dprपूर्णांकk("found DiB9000M\n");
		अवरोध;
	पूर्ण

	वापस value;
पूर्ण

अटल व्योम dib9000_set_घातer_mode(काष्ठा dib9000_state *state, क्रमागत dib9000_घातer_mode mode)
अणु
	/* by शेष everything is going to be घातered off */
	u16 reg_903 = 0x3fff, reg_904 = 0xffff, reg_905 = 0xffff, reg_906;
	u8 offset;

	अगर (state->revision == 0x4003 || state->revision == 0x4004 || state->revision == 0x4005)
		offset = 1;
	अन्यथा
		offset = 0;

	reg_906 = dib9000_पढ़ो_word(state, 906 + offset) | 0x3;	/* keep settings क्रम RISC */

	/* now, depending on the requested mode, we घातer on */
	चयन (mode) अणु
		/* घातer up everything in the demod */
	हाल DIB9000_POWER_ALL:
		reg_903 = 0x0000;
		reg_904 = 0x0000;
		reg_905 = 0x0000;
		reg_906 = 0x0000;
		अवरोध;

		/* just leave घातer on the control-पूर्णांकerfaces: GPIO and (I2C or SDIO or SRAM) */
	हाल DIB9000_POWER_INTERFACE_ONLY:	/* TODO घातer up either SDIO or I2C or SRAM */
		reg_905 &= ~((1 << 7) | (1 << 6) | (1 << 5) | (1 << 2));
		अवरोध;

	हाल DIB9000_POWER_INTERF_ANALOG_AGC:
		reg_903 &= ~((1 << 15) | (1 << 14) | (1 << 11) | (1 << 10));
		reg_905 &= ~((1 << 7) | (1 << 6) | (1 << 5) | (1 << 4) | (1 << 2));
		reg_906 &= ~((1 << 0));
		अवरोध;

	हाल DIB9000_POWER_COR4_DINTLV_ICIRM_EQUAL_CFROD:
		reg_903 = 0x0000;
		reg_904 = 0x801f;
		reg_905 = 0x0000;
		reg_906 &= ~((1 << 0));
		अवरोध;

	हाल DIB9000_POWER_COR4_CRY_ESRAM_MOUT_NUD:
		reg_903 = 0x0000;
		reg_904 = 0x8000;
		reg_905 = 0x010b;
		reg_906 &= ~((1 << 0));
		अवरोध;
	शेष:
	हाल DIB9000_POWER_NO:
		अवरोध;
	पूर्ण

	/* always घातer करोwn unused parts */
	अगर (!state->platक्रमm.host.mobile_mode)
		reg_904 |= (1 << 7) | (1 << 6) | (1 << 4) | (1 << 2) | (1 << 1);

	/* P_sdio_select_clk = 0 on MC and after */
	अगर (state->revision != 0x4000)
		reg_906 <<= 1;

	dib9000_ग_लिखो_word(state, 903 + offset, reg_903);
	dib9000_ग_लिखो_word(state, 904 + offset, reg_904);
	dib9000_ग_लिखो_word(state, 905 + offset, reg_905);
	dib9000_ग_लिखो_word(state, 906 + offset, reg_906);
पूर्ण

अटल पूर्णांक dib9000_fw_reset(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib9000_state *state = fe->demodulator_priv;

	dib9000_ग_लिखो_word(state, 1817, 0x0003);

	dib9000_ग_लिखो_word(state, 1227, 1);
	dib9000_ग_लिखो_word(state, 1227, 0);

	चयन ((state->revision = dib9000_identअगरy(&state->i2c))) अणु
	हाल 0x4003:
	हाल 0x4004:
	हाल 0x4005:
		state->reg_offs = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* reset the i2c-master to use the host पूर्णांकerface */
	dibx000_reset_i2c_master(&state->i2c_master);

	dib9000_set_घातer_mode(state, DIB9000_POWER_ALL);

	/* unक्रमce भागstr regardless whether i2c क्रमागतeration was करोne or not */
	dib9000_ग_लिखो_word(state, 1794, dib9000_पढ़ो_word(state, 1794) & ~(1 << 1));
	dib9000_ग_लिखो_word(state, 1796, 0);
	dib9000_ग_लिखो_word(state, 1805, 0x805);

	/* restart all parts */
	dib9000_ग_लिखो_word(state, 898, 0xffff);
	dib9000_ग_लिखो_word(state, 899, 0xffff);
	dib9000_ग_लिखो_word(state, 900, 0x0001);
	dib9000_ग_लिखो_word(state, 901, 0xff19);
	dib9000_ग_लिखो_word(state, 902, 0x003c);

	dib9000_ग_लिखो_word(state, 898, 0);
	dib9000_ग_लिखो_word(state, 899, 0);
	dib9000_ग_लिखो_word(state, 900, 0);
	dib9000_ग_लिखो_word(state, 901, 0);
	dib9000_ग_लिखो_word(state, 902, 0);

	dib9000_ग_लिखो_word(state, 911, state->chip.d9.cfg.अगर_drives);

	dib9000_set_घातer_mode(state, DIB9000_POWER_INTERFACE_ONLY);

	वापस 0;
पूर्ण

अटल पूर्णांक dib9000_risc_apb_access_पढ़ो(काष्ठा dib9000_state *state, u32 address, u16 attribute, स्थिर u8 * tx, u32 txlen, u8 * b, u32 len)
अणु
	u16 mb[10];
	u8 i, s;

	अगर (address >= 1024 || !state->platक्रमm.risc.fw_is_running)
		वापस -EINVAL;

	/* dprपूर्णांकk( "APB access through rd fw %d %x\n", address, attribute); */

	mb[0] = (u16) address;
	mb[1] = len / 2;
	dib9000_mbx_send_attr(state, OUT_MSG_BRIDGE_APB_R, mb, 2, attribute);
	चयन (dib9000_mbx_get_message_attr(state, IN_MSG_END_BRIDGE_APB_RW, mb, &s, attribute)) अणु
	हाल 1:
		s--;
		क्रम (i = 0; i < s; i++) अणु
			b[i * 2] = (mb[i + 1] >> 8) & 0xff;
			b[i * 2 + 1] = (mb[i + 1]) & 0xff;
		पूर्ण
		वापस 0;
	शेष:
		वापस -EIO;
	पूर्ण
	वापस -EIO;
पूर्ण

अटल पूर्णांक dib9000_risc_apb_access_ग_लिखो(काष्ठा dib9000_state *state, u32 address, u16 attribute, स्थिर u8 * b, u32 len)
अणु
	u16 mb[10];
	u8 s, i;

	अगर (address >= 1024 || !state->platक्रमm.risc.fw_is_running)
		वापस -EINVAL;

	अगर (len > 18)
		वापस -EINVAL;

	/* dprपूर्णांकk( "APB access through wr fw %d %x\n", address, attribute); */

	mb[0] = (u16)address;
	क्रम (i = 0; i + 1 < len; i += 2)
		mb[1 + i / 2] = b[i] << 8 | b[i + 1];
	अगर (len & 1)
		mb[1 + len / 2] = b[len - 1] << 8;

	dib9000_mbx_send_attr(state, OUT_MSG_BRIDGE_APB_W, mb, (3 + len) / 2, attribute);
	वापस dib9000_mbx_get_message_attr(state, IN_MSG_END_BRIDGE_APB_RW, mb, &s, attribute) == 1 ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक dib9000_fw_memmbx_sync(काष्ठा dib9000_state *state, u8 i)
अणु
	u8 index_loop = 10;

	अगर (!state->platक्रमm.risc.fw_is_running)
		वापस 0;
	dib9000_risc_mem_ग_लिखो(state, FE_MM_RW_SYNC, &i);
	करो अणु
		dib9000_risc_mem_पढ़ो(state, FE_MM_RW_SYNC, state->i2c_पढ़ो_buffer, 1);
	पूर्ण जबतक (state->i2c_पढ़ो_buffer[0] && index_loop--);

	अगर (index_loop > 0)
		वापस 0;
	वापस -EIO;
पूर्ण

अटल पूर्णांक dib9000_fw_init(काष्ठा dib9000_state *state)
अणु
	काष्ठा dibGPIOFunction *f;
	u16 b[40] = अणु 0 पूर्ण;
	u8 i;
	u8 size;

	अगर (dib9000_fw_boot(state, शून्य, 0, state->chip.d9.cfg.microcode_B_fe_buffer, state->chip.d9.cfg.microcode_B_fe_size) != 0)
		वापस -EIO;

	/* initialize the firmware */
	क्रम (i = 0; i < ARRAY_SIZE(state->chip.d9.cfg.gpio_function); i++) अणु
		f = &state->chip.d9.cfg.gpio_function[i];
		अगर (f->mask) अणु
			चयन (f->function) अणु
			हाल BOARD_GPIO_FUNCTION_COMPONENT_ON:
				b[0] = (u16) f->mask;
				b[1] = (u16) f->direction;
				b[2] = (u16) f->value;
				अवरोध;
			हाल BOARD_GPIO_FUNCTION_COMPONENT_OFF:
				b[3] = (u16) f->mask;
				b[4] = (u16) f->direction;
				b[5] = (u16) f->value;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (dib9000_mbx_send(state, OUT_MSG_CONF_GPIO, b, 15) != 0)
		वापस -EIO;

	/* subband */
	b[0] = state->chip.d9.cfg.subband.size;	/* type == 0 -> GPIO - PWM not yet supported */
	क्रम (i = 0; i < state->chip.d9.cfg.subband.size; i++) अणु
		b[1 + i * 4] = state->chip.d9.cfg.subband.subband[i].f_mhz;
		b[2 + i * 4] = (u16) state->chip.d9.cfg.subband.subband[i].gpio.mask;
		b[3 + i * 4] = (u16) state->chip.d9.cfg.subband.subband[i].gpio.direction;
		b[4 + i * 4] = (u16) state->chip.d9.cfg.subband.subband[i].gpio.value;
	पूर्ण
	b[1 + i * 4] = 0;	/* fe_id */
	अगर (dib9000_mbx_send(state, OUT_MSG_SUBBAND_SEL, b, 2 + 4 * i) != 0)
		वापस -EIO;

	/* 0 - id, 1 - no_of_frontends */
	b[0] = (0 << 8) | 1;
	/* 0 = i2c-address demod, 0 = tuner */
	b[1] = (0 << 8) | (0);
	b[2] = (u16) (((state->chip.d9.cfg.xtal_घड़ी_khz * 1000) >> 16) & 0xffff);
	b[3] = (u16) (((state->chip.d9.cfg.xtal_घड़ी_khz * 1000)) & 0xffff);
	b[4] = (u16) ((state->chip.d9.cfg.vcxo_समयr >> 16) & 0xffff);
	b[5] = (u16) ((state->chip.d9.cfg.vcxo_समयr) & 0xffff);
	b[6] = (u16) ((state->chip.d9.cfg.timing_frequency >> 16) & 0xffff);
	b[7] = (u16) ((state->chip.d9.cfg.timing_frequency) & 0xffff);
	b[29] = state->chip.d9.cfg.अगर_drives;
	अगर (dib9000_mbx_send(state, OUT_MSG_INIT_DEMOD, b, ARRAY_SIZE(b)) != 0)
		वापस -EIO;

	अगर (dib9000_mbx_send(state, OUT_MSG_FE_FW_DL, शून्य, 0) != 0)
		वापस -EIO;

	अगर (dib9000_mbx_get_message(state, IN_MSG_FE_FW_DL_DONE, b, &size) < 0)
		वापस -EIO;

	अगर (size > ARRAY_SIZE(b)) अणु
		dprपूर्णांकk("error : firmware returned %dbytes needed but the used buffer has only %dbytes\n Firmware init ABORTED", size,
			(पूर्णांक)ARRAY_SIZE(b));
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < size; i += 2) अणु
		state->platक्रमm.risc.fe_mm[i / 2].addr = b[i + 0];
		state->platक्रमm.risc.fe_mm[i / 2].size = b[i + 1];
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dib9000_fw_set_channel_head(काष्ठा dib9000_state *state)
अणु
	u8 b[9];
	u32 freq = state->fe[0]->dtv_property_cache.frequency / 1000;
	अगर (state->fe_id % 2)
		freq += 101;

	b[0] = (u8) ((freq >> 0) & 0xff);
	b[1] = (u8) ((freq >> 8) & 0xff);
	b[2] = (u8) ((freq >> 16) & 0xff);
	b[3] = (u8) ((freq >> 24) & 0xff);
	b[4] = (u8) ((state->fe[0]->dtv_property_cache.bandwidth_hz / 1000 >> 0) & 0xff);
	b[5] = (u8) ((state->fe[0]->dtv_property_cache.bandwidth_hz / 1000 >> 8) & 0xff);
	b[6] = (u8) ((state->fe[0]->dtv_property_cache.bandwidth_hz / 1000 >> 16) & 0xff);
	b[7] = (u8) ((state->fe[0]->dtv_property_cache.bandwidth_hz / 1000 >> 24) & 0xff);
	b[8] = 0x80;		/* करो not रुको क्रम CELL ID when करोing स्वतःsearch */
	अगर (state->fe[0]->dtv_property_cache.delivery_प्रणाली == SYS_DVBT)
		b[8] |= 1;
	dib9000_risc_mem_ग_लिखो(state, FE_MM_W_CHANNEL_HEAD, b);
पूर्ण

अटल पूर्णांक dib9000_fw_get_channel(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib9000_state *state = fe->demodulator_priv;
	काष्ठा dibDVBTChannel अणु
		s8 spectrum_inversion;

		s8 nfft;
		s8 guard;
		s8 स्थिरellation;

		s8 hrch;
		s8 alpha;
		s8 code_rate_hp;
		s8 code_rate_lp;
		s8 select_hp;

		s8 पूर्णांकlv_native;
	पूर्ण;
	काष्ठा dibDVBTChannel *ch;
	पूर्णांक ret = 0;

	अगर (mutex_lock_पूर्णांकerruptible(&state->platक्रमm.risc.mem_mbx_lock) < 0) अणु
		dprपूर्णांकk("could not get the lock\n");
		वापस -EINTR;
	पूर्ण
	अगर (dib9000_fw_memmbx_sync(state, FE_SYNC_CHANNEL) < 0) अणु
		ret = -EIO;
		जाओ error;
	पूर्ण

	dib9000_risc_mem_पढ़ो(state, FE_MM_R_CHANNEL_UNION,
			state->i2c_पढ़ो_buffer, माप(काष्ठा dibDVBTChannel));
	ch = (काष्ठा dibDVBTChannel *)state->i2c_पढ़ो_buffer;


	चयन (ch->spectrum_inversion & 0x7) अणु
	हाल 1:
		state->fe[0]->dtv_property_cache.inversion = INVERSION_ON;
		अवरोध;
	हाल 0:
		state->fe[0]->dtv_property_cache.inversion = INVERSION_OFF;
		अवरोध;
	शेष:
	हाल -1:
		state->fe[0]->dtv_property_cache.inversion = INVERSION_AUTO;
		अवरोध;
	पूर्ण
	चयन (ch->nfft) अणु
	हाल 0:
		state->fe[0]->dtv_property_cache.transmission_mode = TRANSMISSION_MODE_2K;
		अवरोध;
	हाल 2:
		state->fe[0]->dtv_property_cache.transmission_mode = TRANSMISSION_MODE_4K;
		अवरोध;
	हाल 1:
		state->fe[0]->dtv_property_cache.transmission_mode = TRANSMISSION_MODE_8K;
		अवरोध;
	शेष:
	हाल -1:
		state->fe[0]->dtv_property_cache.transmission_mode = TRANSMISSION_MODE_AUTO;
		अवरोध;
	पूर्ण
	चयन (ch->guard) अणु
	हाल 0:
		state->fe[0]->dtv_property_cache.guard_पूर्णांकerval = GUARD_INTERVAL_1_32;
		अवरोध;
	हाल 1:
		state->fe[0]->dtv_property_cache.guard_पूर्णांकerval = GUARD_INTERVAL_1_16;
		अवरोध;
	हाल 2:
		state->fe[0]->dtv_property_cache.guard_पूर्णांकerval = GUARD_INTERVAL_1_8;
		अवरोध;
	हाल 3:
		state->fe[0]->dtv_property_cache.guard_पूर्णांकerval = GUARD_INTERVAL_1_4;
		अवरोध;
	शेष:
	हाल -1:
		state->fe[0]->dtv_property_cache.guard_पूर्णांकerval = GUARD_INTERVAL_AUTO;
		अवरोध;
	पूर्ण
	चयन (ch->स्थिरellation) अणु
	हाल 2:
		state->fe[0]->dtv_property_cache.modulation = QAM_64;
		अवरोध;
	हाल 1:
		state->fe[0]->dtv_property_cache.modulation = QAM_16;
		अवरोध;
	हाल 0:
		state->fe[0]->dtv_property_cache.modulation = QPSK;
		अवरोध;
	शेष:
	हाल -1:
		state->fe[0]->dtv_property_cache.modulation = QAM_AUTO;
		अवरोध;
	पूर्ण
	चयन (ch->hrch) अणु
	हाल 0:
		state->fe[0]->dtv_property_cache.hierarchy = HIERARCHY_NONE;
		अवरोध;
	हाल 1:
		state->fe[0]->dtv_property_cache.hierarchy = HIERARCHY_1;
		अवरोध;
	शेष:
	हाल -1:
		state->fe[0]->dtv_property_cache.hierarchy = HIERARCHY_AUTO;
		अवरोध;
	पूर्ण
	चयन (ch->code_rate_hp) अणु
	हाल 1:
		state->fe[0]->dtv_property_cache.code_rate_HP = FEC_1_2;
		अवरोध;
	हाल 2:
		state->fe[0]->dtv_property_cache.code_rate_HP = FEC_2_3;
		अवरोध;
	हाल 3:
		state->fe[0]->dtv_property_cache.code_rate_HP = FEC_3_4;
		अवरोध;
	हाल 5:
		state->fe[0]->dtv_property_cache.code_rate_HP = FEC_5_6;
		अवरोध;
	हाल 7:
		state->fe[0]->dtv_property_cache.code_rate_HP = FEC_7_8;
		अवरोध;
	शेष:
	हाल -1:
		state->fe[0]->dtv_property_cache.code_rate_HP = FEC_AUTO;
		अवरोध;
	पूर्ण
	चयन (ch->code_rate_lp) अणु
	हाल 1:
		state->fe[0]->dtv_property_cache.code_rate_LP = FEC_1_2;
		अवरोध;
	हाल 2:
		state->fe[0]->dtv_property_cache.code_rate_LP = FEC_2_3;
		अवरोध;
	हाल 3:
		state->fe[0]->dtv_property_cache.code_rate_LP = FEC_3_4;
		अवरोध;
	हाल 5:
		state->fe[0]->dtv_property_cache.code_rate_LP = FEC_5_6;
		अवरोध;
	हाल 7:
		state->fe[0]->dtv_property_cache.code_rate_LP = FEC_7_8;
		अवरोध;
	शेष:
	हाल -1:
		state->fe[0]->dtv_property_cache.code_rate_LP = FEC_AUTO;
		अवरोध;
	पूर्ण

error:
	mutex_unlock(&state->platक्रमm.risc.mem_mbx_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक dib9000_fw_set_channel_जोड़(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib9000_state *state = fe->demodulator_priv;
	काष्ठा dibDVBTChannel अणु
		s8 spectrum_inversion;

		s8 nfft;
		s8 guard;
		s8 स्थिरellation;

		s8 hrch;
		s8 alpha;
		s8 code_rate_hp;
		s8 code_rate_lp;
		s8 select_hp;

		s8 पूर्णांकlv_native;
	पूर्ण;
	काष्ठा dibDVBTChannel ch;

	चयन (state->fe[0]->dtv_property_cache.inversion) अणु
	हाल INVERSION_ON:
		ch.spectrum_inversion = 1;
		अवरोध;
	हाल INVERSION_OFF:
		ch.spectrum_inversion = 0;
		अवरोध;
	शेष:
	हाल INVERSION_AUTO:
		ch.spectrum_inversion = -1;
		अवरोध;
	पूर्ण
	चयन (state->fe[0]->dtv_property_cache.transmission_mode) अणु
	हाल TRANSMISSION_MODE_2K:
		ch.nfft = 0;
		अवरोध;
	हाल TRANSMISSION_MODE_4K:
		ch.nfft = 2;
		अवरोध;
	हाल TRANSMISSION_MODE_8K:
		ch.nfft = 1;
		अवरोध;
	शेष:
	हाल TRANSMISSION_MODE_AUTO:
		ch.nfft = 1;
		अवरोध;
	पूर्ण
	चयन (state->fe[0]->dtv_property_cache.guard_पूर्णांकerval) अणु
	हाल GUARD_INTERVAL_1_32:
		ch.guard = 0;
		अवरोध;
	हाल GUARD_INTERVAL_1_16:
		ch.guard = 1;
		अवरोध;
	हाल GUARD_INTERVAL_1_8:
		ch.guard = 2;
		अवरोध;
	हाल GUARD_INTERVAL_1_4:
		ch.guard = 3;
		अवरोध;
	शेष:
	हाल GUARD_INTERVAL_AUTO:
		ch.guard = -1;
		अवरोध;
	पूर्ण
	चयन (state->fe[0]->dtv_property_cache.modulation) अणु
	हाल QAM_64:
		ch.स्थिरellation = 2;
		अवरोध;
	हाल QAM_16:
		ch.स्थिरellation = 1;
		अवरोध;
	हाल QPSK:
		ch.स्थिरellation = 0;
		अवरोध;
	शेष:
	हाल QAM_AUTO:
		ch.स्थिरellation = -1;
		अवरोध;
	पूर्ण
	चयन (state->fe[0]->dtv_property_cache.hierarchy) अणु
	हाल HIERARCHY_NONE:
		ch.hrch = 0;
		अवरोध;
	हाल HIERARCHY_1:
	हाल HIERARCHY_2:
	हाल HIERARCHY_4:
		ch.hrch = 1;
		अवरोध;
	शेष:
	हाल HIERARCHY_AUTO:
		ch.hrch = -1;
		अवरोध;
	पूर्ण
	ch.alpha = 1;
	चयन (state->fe[0]->dtv_property_cache.code_rate_HP) अणु
	हाल FEC_1_2:
		ch.code_rate_hp = 1;
		अवरोध;
	हाल FEC_2_3:
		ch.code_rate_hp = 2;
		अवरोध;
	हाल FEC_3_4:
		ch.code_rate_hp = 3;
		अवरोध;
	हाल FEC_5_6:
		ch.code_rate_hp = 5;
		अवरोध;
	हाल FEC_7_8:
		ch.code_rate_hp = 7;
		अवरोध;
	शेष:
	हाल FEC_AUTO:
		ch.code_rate_hp = -1;
		अवरोध;
	पूर्ण
	चयन (state->fe[0]->dtv_property_cache.code_rate_LP) अणु
	हाल FEC_1_2:
		ch.code_rate_lp = 1;
		अवरोध;
	हाल FEC_2_3:
		ch.code_rate_lp = 2;
		अवरोध;
	हाल FEC_3_4:
		ch.code_rate_lp = 3;
		अवरोध;
	हाल FEC_5_6:
		ch.code_rate_lp = 5;
		अवरोध;
	हाल FEC_7_8:
		ch.code_rate_lp = 7;
		अवरोध;
	शेष:
	हाल FEC_AUTO:
		ch.code_rate_lp = -1;
		अवरोध;
	पूर्ण
	ch.select_hp = 1;
	ch.पूर्णांकlv_native = 1;

	dib9000_risc_mem_ग_लिखो(state, FE_MM_W_CHANNEL_UNION, (u8 *) &ch);

	वापस 0;
पूर्ण

अटल पूर्णांक dib9000_fw_tune(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib9000_state *state = fe->demodulator_priv;
	पूर्णांक ret = 10, search = state->channel_status.status == CHANNEL_STATUS_PARAMETERS_UNKNOWN;
	s8 i;

	चयन (state->tune_state) अणु
	हाल CT_DEMOD_START:
		dib9000_fw_set_channel_head(state);

		/* ग_लिखो the channel context - a channel is initialized to 0, so it is OK */
		dib9000_risc_mem_ग_लिखो(state, FE_MM_W_CHANNEL_CONTEXT, (u8 *) fe_info);
		dib9000_risc_mem_ग_लिखो(state, FE_MM_W_FE_INFO, (u8 *) fe_info);

		अगर (search)
			dib9000_mbx_send(state, OUT_MSG_FE_CHANNEL_SEARCH, शून्य, 0);
		अन्यथा अणु
			dib9000_fw_set_channel_जोड़(fe);
			dib9000_mbx_send(state, OUT_MSG_FE_CHANNEL_TUNE, शून्य, 0);
		पूर्ण
		state->tune_state = CT_DEMOD_STEP_1;
		अवरोध;
	हाल CT_DEMOD_STEP_1:
		अगर (search)
			dib9000_risc_mem_पढ़ो(state, FE_MM_R_CHANNEL_SEARCH_STATE, state->i2c_पढ़ो_buffer, 1);
		अन्यथा
			dib9000_risc_mem_पढ़ो(state, FE_MM_R_CHANNEL_TUNE_STATE, state->i2c_पढ़ो_buffer, 1);
		i = (s8)state->i2c_पढ़ो_buffer[0];
		चयन (i) अणु	/* something happened */
		हाल 0:
			अवरोध;
		हाल -2:	/* tps locks are "slower" than MPEG locks -> even in स्वतःsearch data is OK here */
			अगर (search)
				state->status = FE_STATUS_DEMOD_SUCCESS;
			अन्यथा अणु
				state->tune_state = CT_DEMOD_STOP;
				state->status = FE_STATUS_LOCKED;
			पूर्ण
			अवरोध;
		शेष:
			state->status = FE_STATUS_TUNE_FAILED;
			state->tune_state = CT_DEMOD_STOP;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		ret = FE_CALLBACK_TIME_NEVER;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dib9000_fw_set_भागersity_in(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा dib9000_state *state = fe->demodulator_priv;
	u16 mode = (u16) onoff;
	वापस dib9000_mbx_send(state, OUT_MSG_ENABLE_DIVERSITY, &mode, 1);
पूर्ण

अटल पूर्णांक dib9000_fw_set_output_mode(काष्ठा dvb_frontend *fe, पूर्णांक mode)
अणु
	काष्ठा dib9000_state *state = fe->demodulator_priv;
	u16 outreg, smo_mode;

	dprपूर्णांकk("setting output mode for demod %p to %d\n", fe, mode);

	चयन (mode) अणु
	हाल OUTMODE_MPEG2_PAR_GATED_CLK:
		outreg = (1 << 10);	/* 0x0400 */
		अवरोध;
	हाल OUTMODE_MPEG2_PAR_CONT_CLK:
		outreg = (1 << 10) | (1 << 6);	/* 0x0440 */
		अवरोध;
	हाल OUTMODE_MPEG2_SERIAL:
		outreg = (1 << 10) | (2 << 6) | (0 << 1);	/* 0x0482 */
		अवरोध;
	हाल OUTMODE_DIVERSITY:
		outreg = (1 << 10) | (4 << 6);	/* 0x0500 */
		अवरोध;
	हाल OUTMODE_MPEG2_FIFO:
		outreg = (1 << 10) | (5 << 6);
		अवरोध;
	हाल OUTMODE_HIGH_Z:
		outreg = 0;
		अवरोध;
	शेष:
		dprपूर्णांकk("Unhandled output_mode passed to be set for demod %p\n", &state->fe[0]);
		वापस -EINVAL;
	पूर्ण

	dib9000_ग_लिखो_word(state, 1795, outreg);

	चयन (mode) अणु
	हाल OUTMODE_MPEG2_PAR_GATED_CLK:
	हाल OUTMODE_MPEG2_PAR_CONT_CLK:
	हाल OUTMODE_MPEG2_SERIAL:
	हाल OUTMODE_MPEG2_FIFO:
		smo_mode = (dib9000_पढ़ो_word(state, 295) & 0x0010) | (1 << 1);
		अगर (state->chip.d9.cfg.output_mpeg2_in_188_bytes)
			smo_mode |= (1 << 5);
		dib9000_ग_लिखो_word(state, 295, smo_mode);
		अवरोध;
	पूर्ण

	outreg = to_fw_output_mode(mode);
	वापस dib9000_mbx_send(state, OUT_MSG_SET_OUTPUT_MODE, &outreg, 1);
पूर्ण

अटल पूर्णांक dib9000_tuner_xfer(काष्ठा i2c_adapter *i2c_adap, काष्ठा i2c_msg msg[], पूर्णांक num)
अणु
	काष्ठा dib9000_state *state = i2c_get_adapdata(i2c_adap);
	u16 i, len, t, index_msg;

	क्रम (index_msg = 0; index_msg < num; index_msg++) अणु
		अगर (msg[index_msg].flags & I2C_M_RD) अणु	/* पढ़ो */
			len = msg[index_msg].len;
			अगर (len > 16)
				len = 16;

			अगर (dib9000_पढ़ो_word(state, 790) != 0)
				dprपूर्णांकk("TunerITF: read busy\n");

			dib9000_ग_लिखो_word(state, 784, (u16) (msg[index_msg].addr));
			dib9000_ग_लिखो_word(state, 787, (len / 2) - 1);
			dib9000_ग_लिखो_word(state, 786, 1);	/* start पढ़ो */

			i = 1000;
			जबतक (dib9000_पढ़ो_word(state, 790) != (len / 2) && i)
				i--;

			अगर (i == 0)
				dprपूर्णांकk("TunerITF: read failed\n");

			क्रम (i = 0; i < len; i += 2) अणु
				t = dib9000_पढ़ो_word(state, 785);
				msg[index_msg].buf[i] = (t >> 8) & 0xff;
				msg[index_msg].buf[i + 1] = (t) & 0xff;
			पूर्ण
			अगर (dib9000_पढ़ो_word(state, 790) != 0)
				dprपूर्णांकk("TunerITF: read more data than expected\n");
		पूर्ण अन्यथा अणु
			i = 1000;
			जबतक (dib9000_पढ़ो_word(state, 789) && i)
				i--;
			अगर (i == 0)
				dprपूर्णांकk("TunerITF: write busy\n");

			len = msg[index_msg].len;
			अगर (len > 16)
				len = 16;

			क्रम (i = 0; i < len; i += 2)
				dib9000_ग_लिखो_word(state, 785, (msg[index_msg].buf[i] << 8) | msg[index_msg].buf[i + 1]);
			dib9000_ग_लिखो_word(state, 784, (u16) msg[index_msg].addr);
			dib9000_ग_लिखो_word(state, 787, (len / 2) - 1);
			dib9000_ग_लिखो_word(state, 786, 0);	/* start ग_लिखो */

			i = 1000;
			जबतक (dib9000_पढ़ो_word(state, 791) > 0 && i)
				i--;
			अगर (i == 0)
				dprपूर्णांकk("TunerITF: write failed\n");
		पूर्ण
	पूर्ण
	वापस num;
पूर्ण

पूर्णांक dib9000_fw_set_component_bus_speed(काष्ठा dvb_frontend *fe, u16 speed)
अणु
	काष्ठा dib9000_state *state = fe->demodulator_priv;

	state->component_bus_speed = speed;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dib9000_fw_set_component_bus_speed);

अटल पूर्णांक dib9000_fw_component_bus_xfer(काष्ठा i2c_adapter *i2c_adap, काष्ठा i2c_msg msg[], पूर्णांक num)
अणु
	काष्ठा dib9000_state *state = i2c_get_adapdata(i2c_adap);
	u8 type = 0;		/* I2C */
	u8 port = DIBX000_I2C_INTERFACE_GPIO_3_4;
	u16 scl = state->component_bus_speed;	/* SCL frequency */
	काष्ठा dib9000_fe_memory_map *m = &state->platक्रमm.risc.fe_mm[FE_MM_RW_COMPONENT_ACCESS_BUFFER];
	u8 p[13] = अणु 0 पूर्ण;

	p[0] = type;
	p[1] = port;
	p[2] = msg[0].addr << 1;

	p[3] = (u8) scl & 0xff;	/* scl */
	p[4] = (u8) (scl >> 8);

	p[7] = 0;
	p[8] = 0;

	p[9] = (u8) (msg[0].len);
	p[10] = (u8) (msg[0].len >> 8);
	अगर ((num > 1) && (msg[1].flags & I2C_M_RD)) अणु
		p[11] = (u8) (msg[1].len);
		p[12] = (u8) (msg[1].len >> 8);
	पूर्ण अन्यथा अणु
		p[11] = 0;
		p[12] = 0;
	पूर्ण

	अगर (mutex_lock_पूर्णांकerruptible(&state->platक्रमm.risc.mem_mbx_lock) < 0) अणु
		dprपूर्णांकk("could not get the lock\n");
		वापस 0;
	पूर्ण

	dib9000_risc_mem_ग_लिखो(state, FE_MM_W_COMPONENT_ACCESS, p);

	अणु			/* ग_लिखो-part */
		dib9000_risc_mem_setup_cmd(state, m->addr, msg[0].len, 0);
		dib9000_risc_mem_ग_लिखो_chunks(state, msg[0].buf, msg[0].len);
	पूर्ण

	/* करो the transaction */
	अगर (dib9000_fw_memmbx_sync(state, FE_SYNC_COMPONENT_ACCESS) < 0) अणु
		mutex_unlock(&state->platक्रमm.risc.mem_mbx_lock);
		वापस 0;
	पूर्ण

	/* पढ़ो back any possible result */
	अगर ((num > 1) && (msg[1].flags & I2C_M_RD))
		dib9000_risc_mem_पढ़ो(state, FE_MM_RW_COMPONENT_ACCESS_BUFFER, msg[1].buf, msg[1].len);

	mutex_unlock(&state->platक्रमm.risc.mem_mbx_lock);

	वापस num;
पूर्ण

अटल u32 dib9000_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm dib9000_tuner_algo = अणु
	.master_xfer = dib9000_tuner_xfer,
	.functionality = dib9000_i2c_func,
पूर्ण;

अटल स्थिर काष्ठा i2c_algorithm dib9000_component_bus_algo = अणु
	.master_xfer = dib9000_fw_component_bus_xfer,
	.functionality = dib9000_i2c_func,
पूर्ण;

काष्ठा i2c_adapter *dib9000_get_tuner_पूर्णांकerface(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib9000_state *st = fe->demodulator_priv;
	वापस &st->tuner_adap;
पूर्ण
EXPORT_SYMBOL(dib9000_get_tuner_पूर्णांकerface);

काष्ठा i2c_adapter *dib9000_get_component_bus_पूर्णांकerface(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib9000_state *st = fe->demodulator_priv;
	वापस &st->component_bus;
पूर्ण
EXPORT_SYMBOL(dib9000_get_component_bus_पूर्णांकerface);

काष्ठा i2c_adapter *dib9000_get_i2c_master(काष्ठा dvb_frontend *fe, क्रमागत dibx000_i2c_पूर्णांकerface पूर्णांकf, पूर्णांक gating)
अणु
	काष्ठा dib9000_state *st = fe->demodulator_priv;
	वापस dibx000_get_i2c_adapter(&st->i2c_master, पूर्णांकf, gating);
पूर्ण
EXPORT_SYMBOL(dib9000_get_i2c_master);

पूर्णांक dib9000_set_i2c_adapter(काष्ठा dvb_frontend *fe, काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा dib9000_state *st = fe->demodulator_priv;

	st->i2c.i2c_adap = i2c;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dib9000_set_i2c_adapter);

अटल पूर्णांक dib9000_cfg_gpio(काष्ठा dib9000_state *st, u8 num, u8 dir, u8 val)
अणु
	st->gpio_dir = dib9000_पढ़ो_word(st, 773);
	st->gpio_dir &= ~(1 << num);	/* reset the direction bit */
	st->gpio_dir |= (dir & 0x1) << num;	/* set the new direction */
	dib9000_ग_लिखो_word(st, 773, st->gpio_dir);

	st->gpio_val = dib9000_पढ़ो_word(st, 774);
	st->gpio_val &= ~(1 << num);	/* reset the direction bit */
	st->gpio_val |= (val & 0x01) << num;	/* set the new value */
	dib9000_ग_लिखो_word(st, 774, st->gpio_val);

	dprपूर्णांकk("gpio dir: %04x: gpio val: %04x\n", st->gpio_dir, st->gpio_val);

	वापस 0;
पूर्ण

पूर्णांक dib9000_set_gpio(काष्ठा dvb_frontend *fe, u8 num, u8 dir, u8 val)
अणु
	काष्ठा dib9000_state *state = fe->demodulator_priv;
	वापस dib9000_cfg_gpio(state, num, dir, val);
पूर्ण
EXPORT_SYMBOL(dib9000_set_gpio);

पूर्णांक dib9000_fw_pid_filter_ctrl(काष्ठा dvb_frontend *fe, u8 onoff)
अणु
	काष्ठा dib9000_state *state = fe->demodulator_priv;
	u16 val;
	पूर्णांक ret;

	अगर ((state->pid_ctrl_index != -2) && (state->pid_ctrl_index < 9)) अणु
		/* postpone the pid filtering cmd */
		dprपूर्णांकk("pid filter cmd postpone\n");
		state->pid_ctrl_index++;
		state->pid_ctrl[state->pid_ctrl_index].cmd = DIB9000_PID_FILTER_CTRL;
		state->pid_ctrl[state->pid_ctrl_index].onoff = onoff;
		वापस 0;
	पूर्ण

	अगर (mutex_lock_पूर्णांकerruptible(&state->demod_lock) < 0) अणु
		dprपूर्णांकk("could not get the lock\n");
		वापस -EINTR;
	पूर्ण

	val = dib9000_पढ़ो_word(state, 294 + 1) & 0xffef;
	val |= (onoff & 0x1) << 4;

	dprपूर्णांकk("PID filter enabled %d\n", onoff);
	ret = dib9000_ग_लिखो_word(state, 294 + 1, val);
	mutex_unlock(&state->demod_lock);
	वापस ret;

पूर्ण
EXPORT_SYMBOL(dib9000_fw_pid_filter_ctrl);

पूर्णांक dib9000_fw_pid_filter(काष्ठा dvb_frontend *fe, u8 id, u16 pid, u8 onoff)
अणु
	काष्ठा dib9000_state *state = fe->demodulator_priv;
	पूर्णांक ret;

	अगर (state->pid_ctrl_index != -2) अणु
		/* postpone the pid filtering cmd */
		dprपूर्णांकk("pid filter postpone\n");
		अगर (state->pid_ctrl_index < 9) अणु
			state->pid_ctrl_index++;
			state->pid_ctrl[state->pid_ctrl_index].cmd = DIB9000_PID_FILTER;
			state->pid_ctrl[state->pid_ctrl_index].id = id;
			state->pid_ctrl[state->pid_ctrl_index].pid = pid;
			state->pid_ctrl[state->pid_ctrl_index].onoff = onoff;
		पूर्ण अन्यथा
			dprपूर्णांकk("can not add any more pid ctrl cmd\n");
		वापस 0;
	पूर्ण

	अगर (mutex_lock_पूर्णांकerruptible(&state->demod_lock) < 0) अणु
		dprपूर्णांकk("could not get the lock\n");
		वापस -EINTR;
	पूर्ण
	dprपूर्णांकk("Index %x, PID %d, OnOff %d\n", id, pid, onoff);
	ret = dib9000_ग_लिखो_word(state, 300 + 1 + id,
			onoff ? (1 << 13) | pid : 0);
	mutex_unlock(&state->demod_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(dib9000_fw_pid_filter);

पूर्णांक dib9000_firmware_post_pll_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib9000_state *state = fe->demodulator_priv;
	वापस dib9000_fw_init(state);
पूर्ण
EXPORT_SYMBOL(dib9000_firmware_post_pll_init);

अटल व्योम dib9000_release(काष्ठा dvb_frontend *demod)
अणु
	काष्ठा dib9000_state *st = demod->demodulator_priv;
	u8 index_frontend;

	क्रम (index_frontend = 1; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (st->fe[index_frontend] != शून्य); index_frontend++)
		dvb_frontend_detach(st->fe[index_frontend]);

	dibx000_निकास_i2c_master(&st->i2c_master);

	i2c_del_adapter(&st->tuner_adap);
	i2c_del_adapter(&st->component_bus);
	kमुक्त(st->fe[0]);
	kमुक्त(st);
पूर्ण

अटल पूर्णांक dib9000_wakeup(काष्ठा dvb_frontend *fe)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक dib9000_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib9000_state *state = fe->demodulator_priv;
	u8 index_frontend;
	पूर्णांक ret = 0;

	अगर (mutex_lock_पूर्णांकerruptible(&state->demod_lock) < 0) अणु
		dprपूर्णांकk("could not get the lock\n");
		वापस -EINTR;
	पूर्ण
	क्रम (index_frontend = 1; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != शून्य); index_frontend++) अणु
		ret = state->fe[index_frontend]->ops.sleep(state->fe[index_frontend]);
		अगर (ret < 0)
			जाओ error;
	पूर्ण
	ret = dib9000_mbx_send(state, OUT_MSG_FE_SLEEP, शून्य, 0);

error:
	mutex_unlock(&state->demod_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक dib9000_fe_get_tune_settings(काष्ठा dvb_frontend *fe, काष्ठा dvb_frontend_tune_settings *tune)
अणु
	tune->min_delay_ms = 1000;
	वापस 0;
पूर्ण

अटल पूर्णांक dib9000_get_frontend(काष्ठा dvb_frontend *fe,
				काष्ठा dtv_frontend_properties *c)
अणु
	काष्ठा dib9000_state *state = fe->demodulator_priv;
	u8 index_frontend, sub_index_frontend;
	क्रमागत fe_status stat;
	पूर्णांक ret = 0;

	अगर (state->get_frontend_पूर्णांकernal == 0) अणु
		अगर (mutex_lock_पूर्णांकerruptible(&state->demod_lock) < 0) अणु
			dprपूर्णांकk("could not get the lock\n");
			वापस -EINTR;
		पूर्ण
	पूर्ण

	क्रम (index_frontend = 1; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != शून्य); index_frontend++) अणु
		state->fe[index_frontend]->ops.पढ़ो_status(state->fe[index_frontend], &stat);
		अगर (stat & FE_HAS_SYNC) अणु
			dprपूर्णांकk("TPS lock on the slave%i\n", index_frontend);

			/* synchronize the cache with the other frontends */
			state->fe[index_frontend]->ops.get_frontend(state->fe[index_frontend], c);
			क्रम (sub_index_frontend = 0; (sub_index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[sub_index_frontend] != शून्य);
			     sub_index_frontend++) अणु
				अगर (sub_index_frontend != index_frontend) अणु
					state->fe[sub_index_frontend]->dtv_property_cache.modulation =
					    state->fe[index_frontend]->dtv_property_cache.modulation;
					state->fe[sub_index_frontend]->dtv_property_cache.inversion =
					    state->fe[index_frontend]->dtv_property_cache.inversion;
					state->fe[sub_index_frontend]->dtv_property_cache.transmission_mode =
					    state->fe[index_frontend]->dtv_property_cache.transmission_mode;
					state->fe[sub_index_frontend]->dtv_property_cache.guard_पूर्णांकerval =
					    state->fe[index_frontend]->dtv_property_cache.guard_पूर्णांकerval;
					state->fe[sub_index_frontend]->dtv_property_cache.hierarchy =
					    state->fe[index_frontend]->dtv_property_cache.hierarchy;
					state->fe[sub_index_frontend]->dtv_property_cache.code_rate_HP =
					    state->fe[index_frontend]->dtv_property_cache.code_rate_HP;
					state->fe[sub_index_frontend]->dtv_property_cache.code_rate_LP =
					    state->fe[index_frontend]->dtv_property_cache.code_rate_LP;
					state->fe[sub_index_frontend]->dtv_property_cache.rolloff =
					    state->fe[index_frontend]->dtv_property_cache.rolloff;
				पूर्ण
			पूर्ण
			ret = 0;
			जाओ वापस_value;
		पूर्ण
	पूर्ण

	/* get the channel from master chip */
	ret = dib9000_fw_get_channel(fe);
	अगर (ret != 0)
		जाओ वापस_value;

	/* synchronize the cache with the other frontends */
	क्रम (index_frontend = 1; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != शून्य); index_frontend++) अणु
		state->fe[index_frontend]->dtv_property_cache.inversion = c->inversion;
		state->fe[index_frontend]->dtv_property_cache.transmission_mode = c->transmission_mode;
		state->fe[index_frontend]->dtv_property_cache.guard_पूर्णांकerval = c->guard_पूर्णांकerval;
		state->fe[index_frontend]->dtv_property_cache.modulation = c->modulation;
		state->fe[index_frontend]->dtv_property_cache.hierarchy = c->hierarchy;
		state->fe[index_frontend]->dtv_property_cache.code_rate_HP = c->code_rate_HP;
		state->fe[index_frontend]->dtv_property_cache.code_rate_LP = c->code_rate_LP;
		state->fe[index_frontend]->dtv_property_cache.rolloff = c->rolloff;
	पूर्ण
	ret = 0;

वापस_value:
	अगर (state->get_frontend_पूर्णांकernal == 0)
		mutex_unlock(&state->demod_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक dib9000_set_tune_state(काष्ठा dvb_frontend *fe, क्रमागत frontend_tune_state tune_state)
अणु
	काष्ठा dib9000_state *state = fe->demodulator_priv;
	state->tune_state = tune_state;
	अगर (tune_state == CT_DEMOD_START)
		state->status = FE_STATUS_TUNE_PENDING;

	वापस 0;
पूर्ण

अटल u32 dib9000_get_status(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib9000_state *state = fe->demodulator_priv;
	वापस state->status;
पूर्ण

अटल पूर्णांक dib9000_set_channel_status(काष्ठा dvb_frontend *fe, काष्ठा dvb_frontend_parametersContext *channel_status)
अणु
	काष्ठा dib9000_state *state = fe->demodulator_priv;

	स_नकल(&state->channel_status, channel_status, माप(काष्ठा dvb_frontend_parametersContext));
	वापस 0;
पूर्ण

अटल पूर्णांक dib9000_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib9000_state *state = fe->demodulator_priv;
	पूर्णांक sleep_समय, sleep_समय_slave;
	u32 frontend_status;
	u8 nbr_pending, निकास_condition, index_frontend, index_frontend_success;
	काष्ठा dvb_frontend_parametersContext channel_status;

	/* check that the correct parameters are set */
	अगर (state->fe[0]->dtv_property_cache.frequency == 0) अणु
		dprपूर्णांकk("dib9000: must specify frequency\n");
		वापस 0;
	पूर्ण

	अगर (state->fe[0]->dtv_property_cache.bandwidth_hz == 0) अणु
		dprपूर्णांकk("dib9000: must specify bandwidth\n");
		वापस 0;
	पूर्ण

	state->pid_ctrl_index = -1; /* postpone the pid filtering cmd */
	अगर (mutex_lock_पूर्णांकerruptible(&state->demod_lock) < 0) अणु
		dprपूर्णांकk("could not get the lock\n");
		वापस 0;
	पूर्ण

	fe->dtv_property_cache.delivery_प्रणाली = SYS_DVBT;

	/* set the master status */
	अगर (state->fe[0]->dtv_property_cache.transmission_mode == TRANSMISSION_MODE_AUTO ||
	    state->fe[0]->dtv_property_cache.guard_पूर्णांकerval == GUARD_INTERVAL_AUTO ||
	    state->fe[0]->dtv_property_cache.modulation == QAM_AUTO ||
	    state->fe[0]->dtv_property_cache.code_rate_HP == FEC_AUTO) अणु
		/* no channel specअगरied, स्वतःsearch the channel */
		state->channel_status.status = CHANNEL_STATUS_PARAMETERS_UNKNOWN;
	पूर्ण अन्यथा
		state->channel_status.status = CHANNEL_STATUS_PARAMETERS_SET;

	/* set mode and status क्रम the dअगरferent frontends */
	क्रम (index_frontend = 0; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != शून्य); index_frontend++) अणु
		dib9000_fw_set_भागersity_in(state->fe[index_frontend], 1);

		/* synchronization of the cache */
		स_नकल(&state->fe[index_frontend]->dtv_property_cache, &fe->dtv_property_cache, माप(काष्ठा dtv_frontend_properties));

		state->fe[index_frontend]->dtv_property_cache.delivery_प्रणाली = SYS_DVBT;
		dib9000_fw_set_output_mode(state->fe[index_frontend], OUTMODE_HIGH_Z);

		dib9000_set_channel_status(state->fe[index_frontend], &state->channel_status);
		dib9000_set_tune_state(state->fe[index_frontend], CT_DEMOD_START);
	पूर्ण

	/* actual tune */
	निकास_condition = 0;	/* 0: tune pending; 1: tune failed; 2:tune success */
	index_frontend_success = 0;
	करो अणु
		sleep_समय = dib9000_fw_tune(state->fe[0]);
		क्रम (index_frontend = 1; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != शून्य); index_frontend++) अणु
			sleep_समय_slave = dib9000_fw_tune(state->fe[index_frontend]);
			अगर (sleep_समय == FE_CALLBACK_TIME_NEVER)
				sleep_समय = sleep_समय_slave;
			अन्यथा अगर ((sleep_समय_slave != FE_CALLBACK_TIME_NEVER) && (sleep_समय_slave > sleep_समय))
				sleep_समय = sleep_समय_slave;
		पूर्ण
		अगर (sleep_समय != FE_CALLBACK_TIME_NEVER)
			msleep(sleep_समय / 10);
		अन्यथा
			अवरोध;

		nbr_pending = 0;
		निकास_condition = 0;
		index_frontend_success = 0;
		क्रम (index_frontend = 0; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != शून्य); index_frontend++) अणु
			frontend_status = -dib9000_get_status(state->fe[index_frontend]);
			अगर (frontend_status > -FE_STATUS_TUNE_PENDING) अणु
				निकास_condition = 2;	/* tune success */
				index_frontend_success = index_frontend;
				अवरोध;
			पूर्ण
			अगर (frontend_status == -FE_STATUS_TUNE_PENDING)
				nbr_pending++;	/* some frontends are still tuning */
		पूर्ण
		अगर ((निकास_condition != 2) && (nbr_pending == 0))
			निकास_condition = 1;	/* अगर all tune are करोne and no success, निकास: tune failed */

	पूर्ण जबतक (निकास_condition == 0);

	/* check the tune result */
	अगर (निकास_condition == 1) अणु	/* tune failed */
		dprपूर्णांकk("tune failed\n");
		mutex_unlock(&state->demod_lock);
		/* tune failed; put all the pid filtering cmd to junk */
		state->pid_ctrl_index = -1;
		वापस 0;
	पूर्ण

	dprपूर्णांकk("tune success on frontend%i\n", index_frontend_success);

	/* synchronize all the channel cache */
	state->get_frontend_पूर्णांकernal = 1;
	dib9000_get_frontend(state->fe[0], &state->fe[0]->dtv_property_cache);
	state->get_frontend_पूर्णांकernal = 0;

	/* retune the other frontends with the found channel */
	channel_status.status = CHANNEL_STATUS_PARAMETERS_SET;
	क्रम (index_frontend = 0; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != शून्य); index_frontend++) अणु
		/* only retune the frontends which was not tuned success */
		अगर (index_frontend != index_frontend_success) अणु
			dib9000_set_channel_status(state->fe[index_frontend], &channel_status);
			dib9000_set_tune_state(state->fe[index_frontend], CT_DEMOD_START);
		पूर्ण
	पूर्ण
	करो अणु
		sleep_समय = FE_CALLBACK_TIME_NEVER;
		क्रम (index_frontend = 0; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != शून्य); index_frontend++) अणु
			अगर (index_frontend != index_frontend_success) अणु
				sleep_समय_slave = dib9000_fw_tune(state->fe[index_frontend]);
				अगर (sleep_समय == FE_CALLBACK_TIME_NEVER)
					sleep_समय = sleep_समय_slave;
				अन्यथा अगर ((sleep_समय_slave != FE_CALLBACK_TIME_NEVER) && (sleep_समय_slave > sleep_समय))
					sleep_समय = sleep_समय_slave;
			पूर्ण
		पूर्ण
		अगर (sleep_समय != FE_CALLBACK_TIME_NEVER)
			msleep(sleep_समय / 10);
		अन्यथा
			अवरोध;

		nbr_pending = 0;
		क्रम (index_frontend = 0; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != शून्य); index_frontend++) अणु
			अगर (index_frontend != index_frontend_success) अणु
				frontend_status = -dib9000_get_status(state->fe[index_frontend]);
				अगर ((index_frontend != index_frontend_success) && (frontend_status == -FE_STATUS_TUNE_PENDING))
					nbr_pending++;	/* some frontends are still tuning */
			पूर्ण
		पूर्ण
	पूर्ण जबतक (nbr_pending != 0);

	/* set the output mode */
	dib9000_fw_set_output_mode(state->fe[0], state->chip.d9.cfg.output_mode);
	क्रम (index_frontend = 1; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != शून्य); index_frontend++)
		dib9000_fw_set_output_mode(state->fe[index_frontend], OUTMODE_DIVERSITY);

	/* turn off the भागersity क्रम the last frontend */
	dib9000_fw_set_भागersity_in(state->fe[index_frontend - 1], 0);

	mutex_unlock(&state->demod_lock);
	अगर (state->pid_ctrl_index >= 0) अणु
		u8 index_pid_filter_cmd;
		u8 pid_ctrl_index = state->pid_ctrl_index;

		state->pid_ctrl_index = -2;
		क्रम (index_pid_filter_cmd = 0;
				index_pid_filter_cmd <= pid_ctrl_index;
				index_pid_filter_cmd++) अणु
			अगर (state->pid_ctrl[index_pid_filter_cmd].cmd == DIB9000_PID_FILTER_CTRL)
				dib9000_fw_pid_filter_ctrl(state->fe[0],
						state->pid_ctrl[index_pid_filter_cmd].onoff);
			अन्यथा अगर (state->pid_ctrl[index_pid_filter_cmd].cmd == DIB9000_PID_FILTER)
				dib9000_fw_pid_filter(state->fe[0],
						state->pid_ctrl[index_pid_filter_cmd].id,
						state->pid_ctrl[index_pid_filter_cmd].pid,
						state->pid_ctrl[index_pid_filter_cmd].onoff);
		पूर्ण
	पूर्ण
	/* करो not postpone any more the pid filtering */
	state->pid_ctrl_index = -2;

	वापस 0;
पूर्ण

अटल u16 dib9000_पढ़ो_lock(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib9000_state *state = fe->demodulator_priv;

	वापस dib9000_पढ़ो_word(state, 535);
पूर्ण

अटल पूर्णांक dib9000_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *stat)
अणु
	काष्ठा dib9000_state *state = fe->demodulator_priv;
	u8 index_frontend;
	u16 lock = 0, lock_slave = 0;

	अगर (mutex_lock_पूर्णांकerruptible(&state->demod_lock) < 0) अणु
		dprपूर्णांकk("could not get the lock\n");
		वापस -EINTR;
	पूर्ण
	क्रम (index_frontend = 1; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != शून्य); index_frontend++)
		lock_slave |= dib9000_पढ़ो_lock(state->fe[index_frontend]);

	lock = dib9000_पढ़ो_word(state, 535);

	*stat = 0;

	अगर ((lock & 0x8000) || (lock_slave & 0x8000))
		*stat |= FE_HAS_SIGNAL;
	अगर ((lock & 0x3000) || (lock_slave & 0x3000))
		*stat |= FE_HAS_CARRIER;
	अगर ((lock & 0x0100) || (lock_slave & 0x0100))
		*stat |= FE_HAS_VITERBI;
	अगर (((lock & 0x0038) == 0x38) || ((lock_slave & 0x0038) == 0x38))
		*stat |= FE_HAS_SYNC;
	अगर ((lock & 0x0008) || (lock_slave & 0x0008))
		*stat |= FE_HAS_LOCK;

	mutex_unlock(&state->demod_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक dib9000_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 * ber)
अणु
	काष्ठा dib9000_state *state = fe->demodulator_priv;
	u16 *c;
	पूर्णांक ret = 0;

	अगर (mutex_lock_पूर्णांकerruptible(&state->demod_lock) < 0) अणु
		dprपूर्णांकk("could not get the lock\n");
		वापस -EINTR;
	पूर्ण
	अगर (mutex_lock_पूर्णांकerruptible(&state->platक्रमm.risc.mem_mbx_lock) < 0) अणु
		dprपूर्णांकk("could not get the lock\n");
		ret = -EINTR;
		जाओ error;
	पूर्ण
	अगर (dib9000_fw_memmbx_sync(state, FE_SYNC_CHANNEL) < 0) अणु
		mutex_unlock(&state->platक्रमm.risc.mem_mbx_lock);
		ret = -EIO;
		जाओ error;
	पूर्ण
	dib9000_risc_mem_पढ़ो(state, FE_MM_R_FE_MONITOR,
			state->i2c_पढ़ो_buffer, 16 * 2);
	mutex_unlock(&state->platक्रमm.risc.mem_mbx_lock);

	c = (u16 *)state->i2c_पढ़ो_buffer;

	*ber = c[10] << 16 | c[11];

error:
	mutex_unlock(&state->demod_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक dib9000_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe, u16 * strength)
अणु
	काष्ठा dib9000_state *state = fe->demodulator_priv;
	u8 index_frontend;
	u16 *c = (u16 *)state->i2c_पढ़ो_buffer;
	u16 val;
	पूर्णांक ret = 0;

	अगर (mutex_lock_पूर्णांकerruptible(&state->demod_lock) < 0) अणु
		dprपूर्णांकk("could not get the lock\n");
		वापस -EINTR;
	पूर्ण
	*strength = 0;
	क्रम (index_frontend = 1; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != शून्य); index_frontend++) अणु
		state->fe[index_frontend]->ops.पढ़ो_संकेत_strength(state->fe[index_frontend], &val);
		अगर (val > 65535 - *strength)
			*strength = 65535;
		अन्यथा
			*strength += val;
	पूर्ण

	अगर (mutex_lock_पूर्णांकerruptible(&state->platक्रमm.risc.mem_mbx_lock) < 0) अणु
		dprपूर्णांकk("could not get the lock\n");
		ret = -EINTR;
		जाओ error;
	पूर्ण
	अगर (dib9000_fw_memmbx_sync(state, FE_SYNC_CHANNEL) < 0) अणु
		mutex_unlock(&state->platक्रमm.risc.mem_mbx_lock);
		ret = -EIO;
		जाओ error;
	पूर्ण
	dib9000_risc_mem_पढ़ो(state, FE_MM_R_FE_MONITOR, (u8 *) c, 16 * 2);
	mutex_unlock(&state->platक्रमm.risc.mem_mbx_lock);

	val = 65535 - c[4];
	अगर (val > 65535 - *strength)
		*strength = 65535;
	अन्यथा
		*strength += val;

error:
	mutex_unlock(&state->demod_lock);
	वापस ret;
पूर्ण

अटल u32 dib9000_get_snr(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dib9000_state *state = fe->demodulator_priv;
	u16 *c = (u16 *)state->i2c_पढ़ो_buffer;
	u32 n, s, exp;
	u16 val;

	अगर (mutex_lock_पूर्णांकerruptible(&state->platक्रमm.risc.mem_mbx_lock) < 0) अणु
		dprपूर्णांकk("could not get the lock\n");
		वापस 0;
	पूर्ण
	अगर (dib9000_fw_memmbx_sync(state, FE_SYNC_CHANNEL) < 0) अणु
		mutex_unlock(&state->platक्रमm.risc.mem_mbx_lock);
		वापस 0;
	पूर्ण
	dib9000_risc_mem_पढ़ो(state, FE_MM_R_FE_MONITOR, (u8 *) c, 16 * 2);
	mutex_unlock(&state->platक्रमm.risc.mem_mbx_lock);

	val = c[7];
	n = (val >> 4) & 0xff;
	exp = ((val & 0xf) << 2);
	val = c[8];
	exp += ((val >> 14) & 0x3);
	अगर ((exp & 0x20) != 0)
		exp -= 0x40;
	n <<= exp + 16;

	s = (val >> 6) & 0xFF;
	exp = (val & 0x3F);
	अगर ((exp & 0x20) != 0)
		exp -= 0x40;
	s <<= exp + 16;

	अगर (n > 0) अणु
		u32 t = (s / n) << 16;
		वापस t + ((s << 16) - n * t) / n;
	पूर्ण
	वापस 0xffffffff;
पूर्ण

अटल पूर्णांक dib9000_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 * snr)
अणु
	काष्ठा dib9000_state *state = fe->demodulator_priv;
	u8 index_frontend;
	u32 snr_master;

	अगर (mutex_lock_पूर्णांकerruptible(&state->demod_lock) < 0) अणु
		dprपूर्णांकk("could not get the lock\n");
		वापस -EINTR;
	पूर्ण
	snr_master = dib9000_get_snr(fe);
	क्रम (index_frontend = 1; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != शून्य); index_frontend++)
		snr_master += dib9000_get_snr(state->fe[index_frontend]);

	अगर ((snr_master >> 16) != 0) अणु
		snr_master = 10 * पूर्णांकlog10(snr_master >> 16);
		*snr = snr_master / ((1 << 24) / 10);
	पूर्ण अन्यथा
		*snr = 0;

	mutex_unlock(&state->demod_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक dib9000_पढ़ो_unc_blocks(काष्ठा dvb_frontend *fe, u32 * unc)
अणु
	काष्ठा dib9000_state *state = fe->demodulator_priv;
	u16 *c = (u16 *)state->i2c_पढ़ो_buffer;
	पूर्णांक ret = 0;

	अगर (mutex_lock_पूर्णांकerruptible(&state->demod_lock) < 0) अणु
		dprपूर्णांकk("could not get the lock\n");
		वापस -EINTR;
	पूर्ण
	अगर (mutex_lock_पूर्णांकerruptible(&state->platक्रमm.risc.mem_mbx_lock) < 0) अणु
		dprपूर्णांकk("could not get the lock\n");
		ret = -EINTR;
		जाओ error;
	पूर्ण
	अगर (dib9000_fw_memmbx_sync(state, FE_SYNC_CHANNEL) < 0) अणु
		mutex_unlock(&state->platक्रमm.risc.mem_mbx_lock);
		ret = -EIO;
		जाओ error;
	पूर्ण
	dib9000_risc_mem_पढ़ो(state, FE_MM_R_FE_MONITOR, (u8 *) c, 16 * 2);
	mutex_unlock(&state->platक्रमm.risc.mem_mbx_lock);

	*unc = c[12];

error:
	mutex_unlock(&state->demod_lock);
	वापस ret;
पूर्ण

पूर्णांक dib9000_i2c_क्रमागतeration(काष्ठा i2c_adapter *i2c, पूर्णांक no_of_demods, u8 शेष_addr, u8 first_addr)
अणु
	पूर्णांक k = 0, ret = 0;
	u8 new_addr = 0;
	काष्ठा i2c_device client = अणु.i2c_adap = i2c पूर्ण;

	client.i2c_ग_लिखो_buffer = kzalloc(4, GFP_KERNEL);
	अगर (!client.i2c_ग_लिखो_buffer) अणु
		dprपूर्णांकk("%s: not enough memory\n", __func__);
		वापस -ENOMEM;
	पूर्ण
	client.i2c_पढ़ो_buffer = kzalloc(4, GFP_KERNEL);
	अगर (!client.i2c_पढ़ो_buffer) अणु
		dprपूर्णांकk("%s: not enough memory\n", __func__);
		ret = -ENOMEM;
		जाओ error_memory;
	पूर्ण

	client.i2c_addr = शेष_addr + 16;
	dib9000_i2c_ग_लिखो16(&client, 1796, 0x0);

	क्रम (k = no_of_demods - 1; k >= 0; k--) अणु
		/* designated i2c address */
		new_addr = first_addr + (k << 1);
		client.i2c_addr = शेष_addr;

		dib9000_i2c_ग_लिखो16(&client, 1817, 3);
		dib9000_i2c_ग_लिखो16(&client, 1796, 0);
		dib9000_i2c_ग_लिखो16(&client, 1227, 1);
		dib9000_i2c_ग_लिखो16(&client, 1227, 0);

		client.i2c_addr = new_addr;
		dib9000_i2c_ग_लिखो16(&client, 1817, 3);
		dib9000_i2c_ग_लिखो16(&client, 1796, 0);
		dib9000_i2c_ग_लिखो16(&client, 1227, 1);
		dib9000_i2c_ग_लिखो16(&client, 1227, 0);

		अगर (dib9000_identअगरy(&client) == 0) अणु
			client.i2c_addr = शेष_addr;
			अगर (dib9000_identअगरy(&client) == 0) अणु
				dprपूर्णांकk("DiB9000 #%d: not identified\n", k);
				ret = -EIO;
				जाओ error;
			पूर्ण
		पूर्ण

		dib9000_i2c_ग_लिखो16(&client, 1795, (1 << 10) | (4 << 6));
		dib9000_i2c_ग_लिखो16(&client, 1794, (new_addr << 2) | 2);

		dprपूर्णांकk("IC %d initialized (to i2c_address 0x%x)\n", k, new_addr);
	पूर्ण

	क्रम (k = 0; k < no_of_demods; k++) अणु
		new_addr = first_addr | (k << 1);
		client.i2c_addr = new_addr;

		dib9000_i2c_ग_लिखो16(&client, 1794, (new_addr << 2));
		dib9000_i2c_ग_लिखो16(&client, 1795, 0);
	पूर्ण

error:
	kमुक्त(client.i2c_पढ़ो_buffer);
error_memory:
	kमुक्त(client.i2c_ग_लिखो_buffer);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(dib9000_i2c_क्रमागतeration);

पूर्णांक dib9000_set_slave_frontend(काष्ठा dvb_frontend *fe, काष्ठा dvb_frontend *fe_slave)
अणु
	काष्ठा dib9000_state *state = fe->demodulator_priv;
	u8 index_frontend = 1;

	जबतक ((index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != शून्य))
		index_frontend++;
	अगर (index_frontend < MAX_NUMBER_OF_FRONTENDS) अणु
		dprपूर्णांकk("set slave fe %p to index %i\n", fe_slave, index_frontend);
		state->fe[index_frontend] = fe_slave;
		वापस 0;
	पूर्ण

	dprपूर्णांकk("too many slave frontend\n");
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL(dib9000_set_slave_frontend);

काष्ठा dvb_frontend *dib9000_get_slave_frontend(काष्ठा dvb_frontend *fe, पूर्णांक slave_index)
अणु
	काष्ठा dib9000_state *state = fe->demodulator_priv;

	अगर (slave_index >= MAX_NUMBER_OF_FRONTENDS)
		वापस शून्य;
	वापस state->fe[slave_index];
पूर्ण
EXPORT_SYMBOL(dib9000_get_slave_frontend);

अटल स्थिर काष्ठा dvb_frontend_ops dib9000_ops;
काष्ठा dvb_frontend *dib9000_attach(काष्ठा i2c_adapter *i2c_adap, u8 i2c_addr, स्थिर काष्ठा dib9000_config *cfg)
अणु
	काष्ठा dvb_frontend *fe;
	काष्ठा dib9000_state *st;
	st = kzalloc(माप(काष्ठा dib9000_state), GFP_KERNEL);
	अगर (st == शून्य)
		वापस शून्य;
	fe = kzalloc(माप(काष्ठा dvb_frontend), GFP_KERNEL);
	अगर (fe == शून्य) अणु
		kमुक्त(st);
		वापस शून्य;
	पूर्ण

	स_नकल(&st->chip.d9.cfg, cfg, माप(काष्ठा dib9000_config));
	st->i2c.i2c_adap = i2c_adap;
	st->i2c.i2c_addr = i2c_addr;
	st->i2c.i2c_ग_लिखो_buffer = st->i2c_ग_लिखो_buffer;
	st->i2c.i2c_पढ़ो_buffer = st->i2c_पढ़ो_buffer;

	st->gpio_dir = DIB9000_GPIO_DEFAULT_सूचीECTIONS;
	st->gpio_val = DIB9000_GPIO_DEFAULT_VALUES;
	st->gpio_pwm_pos = DIB9000_GPIO_DEFAULT_PWM_POS;

	mutex_init(&st->platक्रमm.risc.mbx_अगर_lock);
	mutex_init(&st->platक्रमm.risc.mbx_lock);
	mutex_init(&st->platक्रमm.risc.mem_lock);
	mutex_init(&st->platक्रमm.risc.mem_mbx_lock);
	mutex_init(&st->demod_lock);
	st->get_frontend_पूर्णांकernal = 0;

	st->pid_ctrl_index = -2;

	st->fe[0] = fe;
	fe->demodulator_priv = st;
	स_नकल(&st->fe[0]->ops, &dib9000_ops, माप(काष्ठा dvb_frontend_ops));

	/* Ensure the output mode reमुख्यs at the previous शेष अगर it's
	 * not specअगरically set by the caller.
	 */
	अगर ((st->chip.d9.cfg.output_mode != OUTMODE_MPEG2_SERIAL) && (st->chip.d9.cfg.output_mode != OUTMODE_MPEG2_PAR_GATED_CLK))
		st->chip.d9.cfg.output_mode = OUTMODE_MPEG2_FIFO;

	अगर (dib9000_identअगरy(&st->i2c) == 0)
		जाओ error;

	dibx000_init_i2c_master(&st->i2c_master, DIB7000MC, st->i2c.i2c_adap, st->i2c.i2c_addr);

	st->tuner_adap.dev.parent = i2c_adap->dev.parent;
	strscpy(st->tuner_adap.name, "DIB9000_FW TUNER ACCESS",
		माप(st->tuner_adap.name));
	st->tuner_adap.algo = &dib9000_tuner_algo;
	st->tuner_adap.algo_data = शून्य;
	i2c_set_adapdata(&st->tuner_adap, st);
	अगर (i2c_add_adapter(&st->tuner_adap) < 0)
		जाओ error;

	st->component_bus.dev.parent = i2c_adap->dev.parent;
	strscpy(st->component_bus.name, "DIB9000_FW COMPONENT BUS ACCESS",
		माप(st->component_bus.name));
	st->component_bus.algo = &dib9000_component_bus_algo;
	st->component_bus.algo_data = शून्य;
	st->component_bus_speed = 340;
	i2c_set_adapdata(&st->component_bus, st);
	अगर (i2c_add_adapter(&st->component_bus) < 0)
		जाओ component_bus_add_error;

	dib9000_fw_reset(fe);

	वापस fe;

component_bus_add_error:
	i2c_del_adapter(&st->tuner_adap);
error:
	kमुक्त(st);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(dib9000_attach);

अटल स्थिर काष्ठा dvb_frontend_ops dib9000_ops = अणु
	.delsys = अणु SYS_DVBT पूर्ण,
	.info = अणु
		 .name = "DiBcom 9000",
		 .frequency_min_hz =  44250 * kHz,
		 .frequency_max_hz = 867250 * kHz,
		 .frequency_stepsize_hz = 62500,
		 .caps = FE_CAN_INVERSION_AUTO |
		 FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
		 FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
		 FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
		 FE_CAN_TRANSMISSION_MODE_AUTO | FE_CAN_GUARD_INTERVAL_AUTO | FE_CAN_RECOVER | FE_CAN_HIERARCHY_AUTO,
		 पूर्ण,

	.release = dib9000_release,

	.init = dib9000_wakeup,
	.sleep = dib9000_sleep,

	.set_frontend = dib9000_set_frontend,
	.get_tune_settings = dib9000_fe_get_tune_settings,
	.get_frontend = dib9000_get_frontend,

	.पढ़ो_status = dib9000_पढ़ो_status,
	.पढ़ो_ber = dib9000_पढ़ो_ber,
	.पढ़ो_संकेत_strength = dib9000_पढ़ो_संकेत_strength,
	.पढ़ो_snr = dib9000_पढ़ो_snr,
	.पढ़ो_ucblocks = dib9000_पढ़ो_unc_blocks,
पूर्ण;

MODULE_AUTHOR("Patrick Boettcher <patrick.boettcher@posteo.de>");
MODULE_AUTHOR("Olivier Grenie <olivier.grenie@parrot.com>");
MODULE_DESCRIPTION("Driver for the DiBcom 9000 COFDM demodulator");
MODULE_LICENSE("GPL");
