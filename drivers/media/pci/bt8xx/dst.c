<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Frontend/Card driver क्रम TwinHan DST Frontend
	Copyright (C) 2003 Jamie Honan
	Copyright (C) 2004, 2005 Manu Abraham (manu@kromtek.com)

*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/भाग64.h>
#समावेश <media/dvb_frontend.h>
#समावेश "dst_priv.h"
#समावेश "dst_common.h"

अटल अचिन्हित पूर्णांक verbose;
module_param(verbose, पूर्णांक, 0644);
MODULE_PARM_DESC(verbose, "verbosity level (0 to 3)");

अटल अचिन्हित पूर्णांक dst_adकरोns;
module_param(dst_adकरोns, पूर्णांक, 0644);
MODULE_PARM_DESC(dst_adकरोns, "CA daughterboard, default is 0 (No addons)");

अटल अचिन्हित पूर्णांक dst_algo;
module_param(dst_algo, पूर्णांक, 0644);
MODULE_PARM_DESC(dst_algo, "tuning algo: default is 0=(SW), 1=(HW)");

#घोषणा HAS_LOCK		1
#घोषणा ATTEMPT_TUNE		2
#घोषणा HAS_POWER		4

#घोषणा dprपूर्णांकk(level, fmt, arg...) करो अणु				\
	अगर (level >= verbose)						\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: " fmt),			\
		       __func__, ##arg);				\
पूर्ण जबतक(0)

अटल पूर्णांक dst_command(काष्ठा dst_state *state, u8 *data, u8 len);

अटल व्योम dst_packsize(काष्ठा dst_state *state, पूर्णांक psize)
अणु
	जोड़ dst_gpio_packet bits;

	bits.psize = psize;
	bt878_device_control(state->bt, DST_IG_TS, &bits);
पूर्ण

अटल पूर्णांक dst_gpio_outb(काष्ठा dst_state *state, u32 mask, u32 enbb,
			 u32 outhigh, पूर्णांक delay)
अणु
	जोड़ dst_gpio_packet enb;
	जोड़ dst_gpio_packet bits;
	पूर्णांक err;

	enb.enb.mask = mask;
	enb.enb.enable = enbb;

	dprपूर्णांकk(2, "mask=[%04x], enbb=[%04x], outhigh=[%04x]\n",
		mask, enbb, outhigh);
	अगर ((err = bt878_device_control(state->bt, DST_IG_ENABLE, &enb)) < 0) अणु
		dprपूर्णांकk(2, "dst_gpio_enb error (err == %i, mask == %02x, enb == %02x)\n",
			err, mask, enbb);
		वापस -EREMOTEIO;
	पूर्ण
	udelay(1000);
	/* because complete disabling means no output, no need to करो output packet */
	अगर (enbb == 0)
		वापस 0;
	अगर (delay)
		msleep(10);
	bits.outp.mask = enbb;
	bits.outp.highvals = outhigh;
	अगर ((err = bt878_device_control(state->bt, DST_IG_WRITE, &bits)) < 0) अणु
		dprपूर्णांकk(2, "dst_gpio_outb error (err == %i, enbb == %02x, outhigh == %02x)\n",
			err, enbb, outhigh);
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dst_gpio_inb(काष्ठा dst_state *state, u8 *result)
अणु
	जोड़ dst_gpio_packet rd_packet;
	पूर्णांक err;

	*result = 0;
	अगर ((err = bt878_device_control(state->bt, DST_IG_READ, &rd_packet)) < 0) अणु
		pr_err("dst_gpio_inb error (err == %i)\n", err);
		वापस -EREMOTEIO;
	पूर्ण
	*result = (u8) rd_packet.rd.value;

	वापस 0;
पूर्ण

पूर्णांक rdc_reset_state(काष्ठा dst_state *state)
अणु
	dprपूर्णांकk(2, "Resetting state machine\n");
	अगर (dst_gpio_outb(state, RDC_8820_INT, RDC_8820_INT, 0, NO_DELAY) < 0) अणु
		pr_err("dst_gpio_outb ERROR !\n");
		वापस -1;
	पूर्ण
	msleep(10);
	अगर (dst_gpio_outb(state, RDC_8820_INT, RDC_8820_INT, RDC_8820_INT, NO_DELAY) < 0) अणु
		pr_err("dst_gpio_outb ERROR !\n");
		msleep(10);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(rdc_reset_state);

अटल पूर्णांक rdc_8820_reset(काष्ठा dst_state *state)
अणु
	dprपूर्णांकk(3, "Resetting DST\n");
	अगर (dst_gpio_outb(state, RDC_8820_RESET, RDC_8820_RESET, 0, NO_DELAY) < 0) अणु
		pr_err("dst_gpio_outb ERROR !\n");
		वापस -1;
	पूर्ण
	udelay(1000);
	अगर (dst_gpio_outb(state, RDC_8820_RESET, RDC_8820_RESET, RDC_8820_RESET, DELAY) < 0) अणु
		pr_err("dst_gpio_outb ERROR !\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dst_pio_enable(काष्ठा dst_state *state)
अणु
	अगर (dst_gpio_outb(state, ~0, RDC_8820_PIO_0_ENABLE, 0, NO_DELAY) < 0) अणु
		pr_err("dst_gpio_outb ERROR !\n");
		वापस -1;
	पूर्ण
	udelay(1000);

	वापस 0;
पूर्ण

पूर्णांक dst_pio_disable(काष्ठा dst_state *state)
अणु
	अगर (dst_gpio_outb(state, ~0, RDC_8820_PIO_0_DISABLE, RDC_8820_PIO_0_DISABLE, NO_DELAY) < 0) अणु
		pr_err("dst_gpio_outb ERROR !\n");
		वापस -1;
	पूर्ण
	अगर (state->type_flags & DST_TYPE_HAS_FW_1)
		udelay(1000);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(dst_pio_disable);

पूर्णांक dst_रुको_dst_पढ़ोy(काष्ठा dst_state *state, u8 delay_mode)
अणु
	u8 reply;
	पूर्णांक i;

	क्रम (i = 0; i < 200; i++) अणु
		अगर (dst_gpio_inb(state, &reply) < 0) अणु
			pr_err("dst_gpio_inb ERROR !\n");
			वापस -1;
		पूर्ण
		अगर ((reply & RDC_8820_PIO_0_ENABLE) == 0) अणु
			dprपूर्णांकk(2, "dst wait ready after %d\n", i);
			वापस 1;
		पूर्ण
		msleep(10);
	पूर्ण
	dprपूर्णांकk(1, "dst wait NOT ready after %d\n", i);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(dst_रुको_dst_पढ़ोy);

पूर्णांक dst_error_recovery(काष्ठा dst_state *state)
अणु
	dprपूर्णांकk(1, "Trying to return from previous errors.\n");
	dst_pio_disable(state);
	msleep(10);
	dst_pio_enable(state);
	msleep(10);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(dst_error_recovery);

पूर्णांक dst_error_bailout(काष्ठा dst_state *state)
अणु
	dprपूर्णांकk(2, "Trying to bailout from previous error.\n");
	rdc_8820_reset(state);
	dst_pio_disable(state);
	msleep(10);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(dst_error_bailout);

पूर्णांक dst_comm_init(काष्ठा dst_state *state)
अणु
	dprपूर्णांकk(2, "Initializing DST.\n");
	अगर ((dst_pio_enable(state)) < 0) अणु
		pr_err("PIO Enable Failed\n");
		वापस -1;
	पूर्ण
	अगर ((rdc_reset_state(state)) < 0) अणु
		pr_err("RDC 8820 State RESET Failed.\n");
		वापस -1;
	पूर्ण
	अगर (state->type_flags & DST_TYPE_HAS_FW_1)
		msleep(100);
	अन्यथा
		msleep(5);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(dst_comm_init);

पूर्णांक ग_लिखो_dst(काष्ठा dst_state *state, u8 *data, u8 len)
अणु
	काष्ठा i2c_msg msg = अणु
		.addr = state->config->demod_address,
		.flags = 0,
		.buf = data,
		.len = len
	पूर्ण;

	पूर्णांक err;
	u8 cnt;

	dprपूर्णांकk(1, "writing [ %*ph ]\n", len, data);

	क्रम (cnt = 0; cnt < 2; cnt++) अणु
		अगर ((err = i2c_transfer(state->i2c, &msg, 1)) < 0) अणु
			dprपूर्णांकk(2, "_write_dst error (err == %i, len == 0x%02x, b0 == 0x%02x)\n",
				err, len, data[0]);
			dst_error_recovery(state);
			जारी;
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण
	अगर (cnt >= 2) अणु
		dprपूर्णांकk(2, "RDC 8820 RESET\n");
		dst_error_bailout(state);

		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ग_लिखो_dst);

पूर्णांक पढ़ो_dst(काष्ठा dst_state *state, u8 *ret, u8 len)
अणु
	काष्ठा i2c_msg msg = अणु
		.addr = state->config->demod_address,
		.flags = I2C_M_RD,
		.buf = ret,
		.len = len
	पूर्ण;

	पूर्णांक err;
	पूर्णांक cnt;

	क्रम (cnt = 0; cnt < 2; cnt++) अणु
		अगर ((err = i2c_transfer(state->i2c, &msg, 1)) < 0) अणु
			dprपूर्णांकk(2, "read_dst error (err == %i, len == 0x%02x, b0 == 0x%02x)\n",
				err, len, ret[0]);
			dst_error_recovery(state);
			जारी;
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण
	अगर (cnt >= 2) अणु
		dprपूर्णांकk(2, "RDC 8820 RESET\n");
		dst_error_bailout(state);

		वापस -1;
	पूर्ण
	dprपूर्णांकk(3, "reply is %*ph\n", len, ret);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(पढ़ो_dst);

अटल पूर्णांक dst_set_polarization(काष्ठा dst_state *state)
अणु
	चयन (state->voltage) अणु
	हाल SEC_VOLTAGE_13:	/*	Vertical	*/
		dprपूर्णांकk(2, "Polarization=[Vertical]\n");
		state->tx_tuna[8] &= ~0x40;
		अवरोध;
	हाल SEC_VOLTAGE_18:	/*	Horizontal	*/
		dprपूर्णांकk(2, "Polarization=[Horizontal]\n");
		state->tx_tuna[8] |= 0x40;
		अवरोध;
	हाल SEC_VOLTAGE_OFF:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dst_set_freq(काष्ठा dst_state *state, u32 freq)
अणु
	state->frequency = freq;
	dprपूर्णांकk(2, "set Frequency %u\n", freq);

	अगर (state->dst_type == DST_TYPE_IS_SAT) अणु
		freq = freq / 1000;
		अगर (freq < 950 || freq > 2150)
			वापस -EINVAL;
		state->tx_tuna[2] = (freq >> 8);
		state->tx_tuna[3] = (u8) freq;
		state->tx_tuna[4] = 0x01;
		state->tx_tuna[8] &= ~0x04;
		अगर (state->type_flags & DST_TYPE_HAS_OBS_REGS) अणु
			अगर (freq < 1531)
				state->tx_tuna[8] |= 0x04;
		पूर्ण
	पूर्ण अन्यथा अगर (state->dst_type == DST_TYPE_IS_TERR) अणु
		freq = freq / 1000;
		अगर (freq < 137000 || freq > 858000)
			वापस -EINVAL;
		state->tx_tuna[2] = (freq >> 16) & 0xff;
		state->tx_tuna[3] = (freq >> 8) & 0xff;
		state->tx_tuna[4] = (u8) freq;
	पूर्ण अन्यथा अगर (state->dst_type == DST_TYPE_IS_CABLE) अणु
		freq = freq / 1000;
		state->tx_tuna[2] = (freq >> 16) & 0xff;
		state->tx_tuna[3] = (freq >> 8) & 0xff;
		state->tx_tuna[4] = (u8) freq;
	पूर्ण अन्यथा अगर (state->dst_type == DST_TYPE_IS_ATSC) अणु
		freq = freq / 1000;
		अगर (freq < 51000 || freq > 858000)
			वापस -EINVAL;
		state->tx_tuna[2] = (freq >> 16) & 0xff;
		state->tx_tuna[3] = (freq >>  8) & 0xff;
		state->tx_tuna[4] = (u8) freq;
		state->tx_tuna[5] = 0x00;		/*	ATSC	*/
		state->tx_tuna[6] = 0x00;
		अगर (state->dst_hw_cap & DST_TYPE_HAS_ANALOG)
			state->tx_tuna[7] = 0x00;	/*	Digital	*/
	पूर्ण अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक dst_set_bandwidth(काष्ठा dst_state *state, u32 bandwidth)
अणु
	state->bandwidth = bandwidth;

	अगर (state->dst_type != DST_TYPE_IS_TERR)
		वापस -EOPNOTSUPP;

	चयन (bandwidth) अणु
	हाल 6000000:
		अगर (state->dst_hw_cap & DST_TYPE_HAS_CA)
			state->tx_tuna[7] = 0x06;
		अन्यथा अणु
			state->tx_tuna[6] = 0x06;
			state->tx_tuna[7] = 0x00;
		पूर्ण
		अवरोध;
	हाल 7000000:
		अगर (state->dst_hw_cap & DST_TYPE_HAS_CA)
			state->tx_tuna[7] = 0x07;
		अन्यथा अणु
			state->tx_tuna[6] = 0x07;
			state->tx_tuna[7] = 0x00;
		पूर्ण
		अवरोध;
	हाल 8000000:
		अगर (state->dst_hw_cap & DST_TYPE_HAS_CA)
			state->tx_tuna[7] = 0x08;
		अन्यथा अणु
			state->tx_tuna[6] = 0x08;
			state->tx_tuna[7] = 0x00;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dst_set_inversion(काष्ठा dst_state *state,
			     क्रमागत fe_spectral_inversion inversion)
अणु
	state->inversion = inversion;
	चयन (inversion) अणु
	हाल INVERSION_OFF:	/*	Inversion = Normal	*/
		state->tx_tuna[8] &= ~0x80;
		अवरोध;
	हाल INVERSION_ON:
		state->tx_tuna[8] |= 0x80;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dst_set_fec(काष्ठा dst_state *state, क्रमागत fe_code_rate fec)
अणु
	state->fec = fec;
	वापस 0;
पूर्ण

अटल क्रमागत fe_code_rate dst_get_fec(काष्ठा dst_state *state)
अणु
	वापस state->fec;
पूर्ण

अटल पूर्णांक dst_set_symbolrate(काष्ठा dst_state *state, u32 srate)
अणु
	u32 symcalc;
	u64 sval;

	state->symbol_rate = srate;
	अगर (state->dst_type == DST_TYPE_IS_TERR) अणु
		वापस -EOPNOTSUPP;
	पूर्ण
	dprपूर्णांकk(2, "set symrate %u\n", srate);
	srate /= 1000;
	अगर (state->dst_type == DST_TYPE_IS_SAT) अणु
		अगर (state->type_flags & DST_TYPE_HAS_SYMDIV) अणु
			sval = srate;
			sval <<= 20;
			करो_भाग(sval, 88000);
			symcalc = (u32) sval;
			dprपूर्णांकk(2, "set symcalc %u\n", symcalc);
			state->tx_tuna[5] = (u8) (symcalc >> 12);
			state->tx_tuna[6] = (u8) (symcalc >> 4);
			state->tx_tuna[7] = (u8) (symcalc << 4);
		पूर्ण अन्यथा अणु
			state->tx_tuna[5] = (u8) (srate >> 16) & 0x7f;
			state->tx_tuna[6] = (u8) (srate >> 8);
			state->tx_tuna[7] = (u8) srate;
		पूर्ण
		state->tx_tuna[8] &= ~0x20;
		अगर (state->type_flags & DST_TYPE_HAS_OBS_REGS) अणु
			अगर (srate > 8000)
				state->tx_tuna[8] |= 0x20;
		पूर्ण
	पूर्ण अन्यथा अगर (state->dst_type == DST_TYPE_IS_CABLE) अणु
		dprपूर्णांकk(3, "%s\n", state->fw_name);
		अगर (!म_भेदन(state->fw_name, "DCTNEW", 6)) अणु
			state->tx_tuna[5] = (u8) (srate >> 8);
			state->tx_tuna[6] = (u8) srate;
			state->tx_tuna[7] = 0x00;
		पूर्ण अन्यथा अगर (!म_भेदन(state->fw_name, "DCT-CI", 6)) अणु
			state->tx_tuna[5] = 0x00;
			state->tx_tuna[6] = (u8) (srate >> 8);
			state->tx_tuna[7] = (u8) srate;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dst_set_modulation(काष्ठा dst_state *state,
			      क्रमागत fe_modulation modulation)
अणु
	अगर (state->dst_type != DST_TYPE_IS_CABLE)
		वापस -EOPNOTSUPP;

	state->modulation = modulation;
	चयन (modulation) अणु
	हाल QAM_16:
		state->tx_tuna[8] = 0x10;
		अवरोध;
	हाल QAM_32:
		state->tx_tuna[8] = 0x20;
		अवरोध;
	हाल QAM_64:
		state->tx_tuna[8] = 0x40;
		अवरोध;
	हाल QAM_128:
		state->tx_tuna[8] = 0x80;
		अवरोध;
	हाल QAM_256:
		अगर (!म_भेदन(state->fw_name, "DCTNEW", 6))
			state->tx_tuna[8] = 0xff;
		अन्यथा अगर (!म_भेदन(state->fw_name, "DCT-CI", 6))
			state->tx_tuna[8] = 0x00;
		अवरोध;
	हाल QPSK:
	हाल QAM_AUTO:
	हाल VSB_8:
	हाल VSB_16:
	शेष:
		वापस -EINVAL;

	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत fe_modulation dst_get_modulation(काष्ठा dst_state *state)
अणु
	वापस state->modulation;
पूर्ण


u8 dst_check_sum(u8 *buf, u32 len)
अणु
	u32 i;
	u8 val = 0;
	अगर (!len)
		वापस 0;
	क्रम (i = 0; i < len; i++) अणु
		val += buf[i];
	पूर्ण
	वापस ((~val) + 1);
पूर्ण
EXPORT_SYMBOL(dst_check_sum);

अटल व्योम dst_type_flags_prपूर्णांक(काष्ठा dst_state *state)
अणु
	u32 type_flags = state->type_flags;

	pr_err("DST type flags :\n");
	अगर (type_flags & DST_TYPE_HAS_TS188)
		pr_err(" 0x%x newtuner\n", DST_TYPE_HAS_TS188);
	अगर (type_flags & DST_TYPE_HAS_NEWTUNE_2)
		pr_err(" 0x%x newtuner 2\n", DST_TYPE_HAS_NEWTUNE_2);
	अगर (type_flags & DST_TYPE_HAS_TS204)
		pr_err(" 0x%x ts204\n", DST_TYPE_HAS_TS204);
	अगर (type_flags & DST_TYPE_HAS_VLF)
		pr_err(" 0x%x VLF\n", DST_TYPE_HAS_VLF);
	अगर (type_flags & DST_TYPE_HAS_SYMDIV)
		pr_err(" 0x%x symdiv\n", DST_TYPE_HAS_SYMDIV);
	अगर (type_flags & DST_TYPE_HAS_FW_1)
		pr_err(" 0x%x firmware version = 1\n", DST_TYPE_HAS_FW_1);
	अगर (type_flags & DST_TYPE_HAS_FW_2)
		pr_err(" 0x%x firmware version = 2\n", DST_TYPE_HAS_FW_2);
	अगर (type_flags & DST_TYPE_HAS_FW_3)
		pr_err(" 0x%x firmware version = 3\n", DST_TYPE_HAS_FW_3);
	pr_err("\n");
पूर्ण


अटल पूर्णांक dst_type_prपूर्णांक(काष्ठा dst_state *state, u8 type)
अणु
	अक्षर *otype;
	चयन (type) अणु
	हाल DST_TYPE_IS_SAT:
		otype = "satellite";
		अवरोध;

	हाल DST_TYPE_IS_TERR:
		otype = "terrestrial";
		अवरोध;

	हाल DST_TYPE_IS_CABLE:
		otype = "cable";
		अवरोध;

	हाल DST_TYPE_IS_ATSC:
		otype = "atsc";
		अवरोध;

	शेष:
		dprपूर्णांकk(2, "invalid dst type %d\n", type);
		वापस -EINVAL;
	पूर्ण
	dprपूर्णांकk(2, "DST type: %s\n", otype);

	वापस 0;
पूर्ण

अटल काष्ठा tuner_types tuner_list[] = अणु
	अणु
		.tuner_type = TUNER_TYPE_L64724,
		.tuner_name = "L 64724",
		.board_name = "UNKNOWN",
		.fw_name    = "UNKNOWN"
	पूर्ण,

	अणु
		.tuner_type = TUNER_TYPE_STV0299,
		.tuner_name = "STV 0299",
		.board_name = "VP1020",
		.fw_name    = "DST-MOT"
	पूर्ण,

	अणु
		.tuner_type = TUNER_TYPE_STV0299,
		.tuner_name = "STV 0299",
		.board_name = "VP1020",
		.fw_name    = "DST-03T"
	पूर्ण,

	अणु
		.tuner_type = TUNER_TYPE_MB86A15,
		.tuner_name = "MB 86A15",
		.board_name = "VP1022",
		.fw_name    = "DST-03T"
	पूर्ण,

	अणु
		.tuner_type = TUNER_TYPE_MB86A15,
		.tuner_name = "MB 86A15",
		.board_name = "VP1025",
		.fw_name    = "DST-03T"
	पूर्ण,

	अणु
		.tuner_type = TUNER_TYPE_STV0299,
		.tuner_name = "STV 0299",
		.board_name = "VP1030",
		.fw_name    = "DST-CI"
	पूर्ण,

	अणु
		.tuner_type = TUNER_TYPE_STV0299,
		.tuner_name = "STV 0299",
		.board_name = "VP1030",
		.fw_name    = "DSTMCI"
	पूर्ण,

	अणु
		.tuner_type = TUNER_TYPE_UNKNOWN,
		.tuner_name = "UNKNOWN",
		.board_name = "VP2021",
		.fw_name    = "DCTNEW"
	पूर्ण,

	अणु
		.tuner_type = TUNER_TYPE_UNKNOWN,
		.tuner_name = "UNKNOWN",
		.board_name = "VP2030",
		.fw_name    = "DCT-CI"
	पूर्ण,

	अणु
		.tuner_type = TUNER_TYPE_UNKNOWN,
		.tuner_name = "UNKNOWN",
		.board_name = "VP2031",
		.fw_name    = "DCT-CI"
	पूर्ण,

	अणु
		.tuner_type = TUNER_TYPE_UNKNOWN,
		.tuner_name = "UNKNOWN",
		.board_name = "VP2040",
		.fw_name    = "DCT-CI"
	पूर्ण,

	अणु
		.tuner_type = TUNER_TYPE_UNKNOWN,
		.tuner_name = "UNKNOWN",
		.board_name = "VP3020",
		.fw_name    = "DTTFTA"
	पूर्ण,

	अणु
		.tuner_type = TUNER_TYPE_UNKNOWN,
		.tuner_name = "UNKNOWN",
		.board_name = "VP3021",
		.fw_name    = "DTTFTA"
	पूर्ण,

	अणु
		.tuner_type = TUNER_TYPE_TDA10046,
		.tuner_name = "TDA10046",
		.board_name = "VP3040",
		.fw_name    = "DTT-CI"
	पूर्ण,

	अणु
		.tuner_type = TUNER_TYPE_UNKNOWN,
		.tuner_name = "UNKNOWN",
		.board_name = "VP3051",
		.fw_name    = "DTTNXT"
	पूर्ण,

	अणु
		.tuner_type = TUNER_TYPE_NXT200x,
		.tuner_name = "NXT200x",
		.board_name = "VP3220",
		.fw_name    = "ATSCDI"
	पूर्ण,

	अणु
		.tuner_type = TUNER_TYPE_NXT200x,
		.tuner_name = "NXT200x",
		.board_name = "VP3250",
		.fw_name    = "ATSCAD"
	पूर्ण,
पूर्ण;

/*
	Known cards list
	Satellite
	-------------------
		  200103A
	VP-1020   DST-MOT	LG(old), TS=188

	VP-1020   DST-03T	LG(new), TS=204
	VP-1022   DST-03T	LG(new), TS=204
	VP-1025   DST-03T	LG(new), TS=204

	VP-1030   DSTMCI,	LG(new), TS=188
	VP-1032   DSTMCI,	LG(new), TS=188

	Cable
	-------------------
	VP-2030   DCT-CI,	Samsung, TS=204
	VP-2021   DCT-CI,	Unknown, TS=204
	VP-2031   DCT-CI,	Philips, TS=188
	VP-2040   DCT-CI,	Philips, TS=188, with CA daughter board
	VP-2040   DCT-CI,	Philips, TS=204, without CA daughter board

	Terrestrial
	-------------------
	VP-3050  DTTNXT			 TS=188
	VP-3040  DTT-CI,	Philips, TS=188
	VP-3040  DTT-CI,	Philips, TS=204

	ATSC
	-------------------
	VP-3220  ATSCDI,		 TS=188
	VP-3250  ATSCAD,		 TS=188

*/

अटल काष्ठा dst_types dst_tlist[] = अणु
	अणु
		.device_id = "200103A",
		.offset = 0,
		.dst_type =  DST_TYPE_IS_SAT,
		.type_flags = DST_TYPE_HAS_SYMDIV | DST_TYPE_HAS_FW_1 | DST_TYPE_HAS_OBS_REGS,
		.dst_feature = 0,
		.tuner_type = 0
	पूर्ण,	/*	obsolete	*/

	अणु
		.device_id = "DST-020",
		.offset = 0,
		.dst_type =  DST_TYPE_IS_SAT,
		.type_flags = DST_TYPE_HAS_SYMDIV | DST_TYPE_HAS_FW_1,
		.dst_feature = 0,
		.tuner_type = 0
	पूर्ण,	/*	obsolete	*/

	अणु
		.device_id = "DST-030",
		.offset =  0,
		.dst_type = DST_TYPE_IS_SAT,
		.type_flags = DST_TYPE_HAS_TS204 | DST_TYPE_HAS_TS188 | DST_TYPE_HAS_FW_1,
		.dst_feature = 0,
		.tuner_type = 0
	पूर्ण,	/*	obsolete	*/

	अणु
		.device_id = "DST-03T",
		.offset = 0,
		.dst_type = DST_TYPE_IS_SAT,
		.type_flags = DST_TYPE_HAS_SYMDIV | DST_TYPE_HAS_TS204 | DST_TYPE_HAS_FW_2,
		.dst_feature = DST_TYPE_HAS_DISEQC3 | DST_TYPE_HAS_DISEQC4 | DST_TYPE_HAS_DISEQC5
							 | DST_TYPE_HAS_MAC | DST_TYPE_HAS_MOTO,
		.tuner_type = TUNER_TYPE_MULTI
	 पूर्ण,

	अणु
		.device_id = "DST-MOT",
		.offset =  0,
		.dst_type = DST_TYPE_IS_SAT,
		.type_flags = DST_TYPE_HAS_SYMDIV | DST_TYPE_HAS_FW_1,
		.dst_feature = 0,
		.tuner_type = 0
	पूर्ण,	/*	obsolete	*/

	अणु
		.device_id = "DST-CI",
		.offset = 1,
		.dst_type = DST_TYPE_IS_SAT,
		.type_flags = DST_TYPE_HAS_TS204 | DST_TYPE_HAS_FW_1,
		.dst_feature = DST_TYPE_HAS_CA,
		.tuner_type = 0
	पूर्ण,	/*	An OEM board	*/

	अणु
		.device_id = "DSTMCI",
		.offset = 1,
		.dst_type = DST_TYPE_IS_SAT,
		.type_flags = DST_TYPE_HAS_TS188 | DST_TYPE_HAS_FW_2 | DST_TYPE_HAS_FW_BUILD | DST_TYPE_HAS_INC_COUNT | DST_TYPE_HAS_VLF,
		.dst_feature = DST_TYPE_HAS_CA | DST_TYPE_HAS_DISEQC3 | DST_TYPE_HAS_DISEQC4
							| DST_TYPE_HAS_MOTO | DST_TYPE_HAS_MAC,
		.tuner_type = TUNER_TYPE_MULTI
	पूर्ण,

	अणु
		.device_id = "DSTFCI",
		.offset = 1,
		.dst_type = DST_TYPE_IS_SAT,
		.type_flags = DST_TYPE_HAS_TS188 | DST_TYPE_HAS_FW_1,
		.dst_feature = 0,
		.tuner_type = 0
	पूर्ण,	/* unknown to venकरोr	*/

	अणु
		.device_id = "DCT-CI",
		.offset = 1,
		.dst_type = DST_TYPE_IS_CABLE,
		.type_flags = DST_TYPE_HAS_MULTI_FE | DST_TYPE_HAS_FW_1	| DST_TYPE_HAS_FW_2 | DST_TYPE_HAS_VLF,
		.dst_feature = DST_TYPE_HAS_CA,
		.tuner_type = 0
	पूर्ण,

	अणु
		.device_id = "DCTNEW",
		.offset = 1,
		.dst_type = DST_TYPE_IS_CABLE,
		.type_flags = DST_TYPE_HAS_TS188 | DST_TYPE_HAS_FW_3 | DST_TYPE_HAS_FW_BUILD | DST_TYPE_HAS_MULTI_FE,
		.dst_feature = 0,
		.tuner_type = 0
	पूर्ण,

	अणु
		.device_id = "DTT-CI",
		.offset = 1,
		.dst_type = DST_TYPE_IS_TERR,
		.type_flags = DST_TYPE_HAS_FW_2 | DST_TYPE_HAS_MULTI_FE | DST_TYPE_HAS_VLF,
		.dst_feature = DST_TYPE_HAS_CA,
		.tuner_type = 0
	पूर्ण,

	अणु
		.device_id = "DTTDIG",
		.offset = 1,
		.dst_type = DST_TYPE_IS_TERR,
		.type_flags = DST_TYPE_HAS_FW_2,
		.dst_feature = 0,
		.tuner_type = 0
	पूर्ण,

	अणु
		.device_id = "DTTNXT",
		.offset = 1,
		.dst_type = DST_TYPE_IS_TERR,
		.type_flags = DST_TYPE_HAS_FW_2,
		.dst_feature = DST_TYPE_HAS_ANALOG,
		.tuner_type = 0
	पूर्ण,

	अणु
		.device_id = "ATSCDI",
		.offset = 1,
		.dst_type = DST_TYPE_IS_ATSC,
		.type_flags = DST_TYPE_HAS_FW_2,
		.dst_feature = 0,
		.tuner_type = 0
	पूर्ण,

	अणु
		.device_id = "ATSCAD",
		.offset = 1,
		.dst_type = DST_TYPE_IS_ATSC,
		.type_flags = DST_TYPE_HAS_MULTI_FE | DST_TYPE_HAS_FW_2 | DST_TYPE_HAS_FW_BUILD,
		.dst_feature = DST_TYPE_HAS_MAC | DST_TYPE_HAS_ANALOG,
		.tuner_type = 0
	पूर्ण,

	अणु पूर्ण

पूर्ण;

अटल पूर्णांक dst_get_mac(काष्ठा dst_state *state)
अणु
	u8 get_mac[] = अणु 0x00, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण;
	get_mac[7] = dst_check_sum(get_mac, 7);
	अगर (dst_command(state, get_mac, 8) < 0) अणु
		dprपूर्णांकk(2, "Unsupported Command\n");
		वापस -1;
	पूर्ण
	स_रखो(&state->mac_address, '\0', 8);
	स_नकल(&state->mac_address, &state->rxbuffer, 6);
	pr_err("MAC Address=[%pM]\n", state->mac_address);

	वापस 0;
पूर्ण

अटल पूर्णांक dst_fw_ver(काष्ठा dst_state *state)
अणु
	u8 get_ver[] = अणु 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण;
	get_ver[7] = dst_check_sum(get_ver, 7);
	अगर (dst_command(state, get_ver, 8) < 0) अणु
		dprपूर्णांकk(2, "Unsupported Command\n");
		वापस -1;
	पूर्ण
	स_नकल(&state->fw_version, &state->rxbuffer, 8);
	pr_err("Firmware Ver = %x.%x Build = %02x, on %x:%x, %x-%x-20%02x\n",
		state->fw_version[0] >> 4, state->fw_version[0] & 0x0f,
		state->fw_version[1],
		state->fw_version[5], state->fw_version[6],
		state->fw_version[4], state->fw_version[3], state->fw_version[2]);

	वापस 0;
पूर्ण

अटल पूर्णांक dst_card_type(काष्ठा dst_state *state)
अणु
	पूर्णांक j;
	काष्ठा tuner_types *p_tuner_list = शून्य;

	u8 get_type[] = अणु 0x00, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण;
	get_type[7] = dst_check_sum(get_type, 7);
	अगर (dst_command(state, get_type, 8) < 0) अणु
		dprपूर्णांकk(2, "Unsupported Command\n");
		वापस -1;
	पूर्ण
	स_रखो(&state->card_info, '\0', 8);
	स_नकल(&state->card_info, &state->rxbuffer, 7);
	pr_err("Device Model=[%s]\n", &state->card_info[0]);

	क्रम (j = 0, p_tuner_list = tuner_list; j < ARRAY_SIZE(tuner_list); j++, p_tuner_list++) अणु
		अगर (!म_भेद(&state->card_info[0], p_tuner_list->board_name)) अणु
			state->tuner_type = p_tuner_list->tuner_type;
			pr_err("DST has [%s] tuner, tuner type=[%d]\n",
				p_tuner_list->tuner_name, p_tuner_list->tuner_type);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dst_get_venकरोr(काष्ठा dst_state *state)
अणु
	u8 get_venकरोr[] = अणु 0x00, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण;
	get_venकरोr[7] = dst_check_sum(get_venकरोr, 7);
	अगर (dst_command(state, get_venकरोr, 8) < 0) अणु
		dprपूर्णांकk(2, "Unsupported Command\n");
		वापस -1;
	पूर्ण
	स_रखो(&state->venकरोr, '\0', 8);
	स_नकल(&state->venकरोr, &state->rxbuffer, 7);
	pr_err("Vendor=[%s]\n", &state->venकरोr[0]);

	वापस 0;
पूर्ण

अटल व्योम debug_dst_buffer(काष्ठा dst_state *state)
अणु
	dprपूर्णांकk(3, "%s: [ %*ph ]\n", __func__, 8, state->rxbuffer);
पूर्ण

अटल पूर्णांक dst_check_stv0299(काष्ठा dst_state *state)
अणु
	u8 check_stv0299[] = अणु 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण;

	check_stv0299[7] = dst_check_sum(check_stv0299, 7);
	अगर (dst_command(state, check_stv0299, 8) < 0) अणु
		pr_err("Cmd=[0x04] failed\n");
		वापस -1;
	पूर्ण
	debug_dst_buffer(state);

	अगर (स_भेद(&check_stv0299, &state->rxbuffer, 8)) अणु
		pr_err("Found a STV0299 NIM\n");
		state->tuner_type = TUNER_TYPE_STV0299;
		वापस 0;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक dst_check_mb86a15(काष्ठा dst_state *state)
अणु
	u8 check_mb86a15[] = अणु 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण;

	check_mb86a15[7] = dst_check_sum(check_mb86a15, 7);
	अगर (dst_command(state, check_mb86a15, 8) < 0) अणु
		pr_err("Cmd=[0x10], failed\n");
		वापस -1;
	पूर्ण
	debug_dst_buffer(state);

	अगर (स_भेद(&check_mb86a15, &state->rxbuffer, 8) < 0) अणु
		pr_err("Found a MB86A15 NIM\n");
		state->tuner_type = TUNER_TYPE_MB86A15;
		वापस 0;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक dst_get_tuner_info(काष्ठा dst_state *state)
अणु
	u8 get_tuner_1[] = अणु 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण;
	u8 get_tuner_2[] = अणु 0x00, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण;

	get_tuner_1[7] = dst_check_sum(get_tuner_1, 7);
	get_tuner_2[7] = dst_check_sum(get_tuner_2, 7);
	pr_err("DST TYpe = MULTI FE\n");
	अगर (state->type_flags & DST_TYPE_HAS_MULTI_FE) अणु
		अगर (dst_command(state, get_tuner_1, 8) < 0) अणु
			dprपूर्णांकk(2, "Cmd=[0x13], Unsupported\n");
			जाओ क्रमce;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (dst_command(state, get_tuner_2, 8) < 0) अणु
			dprपूर्णांकk(2, "Cmd=[0xb], Unsupported\n");
			जाओ क्रमce;
		पूर्ण
	पूर्ण
	स_नकल(&state->board_info, &state->rxbuffer, 8);
	अगर (state->type_flags & DST_TYPE_HAS_MULTI_FE) अणु
		pr_err("DST type has TS=188\n");
	पूर्ण
	अगर (state->board_info[0] == 0xbc) अणु
		अगर (state->dst_type != DST_TYPE_IS_ATSC)
			state->type_flags |= DST_TYPE_HAS_TS188;
		अन्यथा
			state->type_flags |= DST_TYPE_HAS_NEWTUNE_2;

		अगर (state->board_info[1] == 0x01) अणु
			state->dst_hw_cap |= DST_TYPE_HAS_DBOARD;
			pr_err("DST has Daughterboard\n");
		पूर्ण
	पूर्ण

	वापस 0;
क्रमce:
	अगर (!म_भेदन(state->fw_name, "DCT-CI", 6)) अणु
		state->type_flags |= DST_TYPE_HAS_TS204;
		pr_err("Forcing [%s] to TS188\n", state->fw_name);
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक dst_get_device_id(काष्ठा dst_state *state)
अणु
	u8 reply;

	पूर्णांक i, j;
	काष्ठा dst_types *p_dst_type = शून्य;
	काष्ठा tuner_types *p_tuner_list = शून्य;

	u8 use_dst_type = 0;
	u32 use_type_flags = 0;

	अटल u8 device_type[8] = अणु0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0xffपूर्ण;

	state->tuner_type = 0;
	device_type[7] = dst_check_sum(device_type, 7);

	अगर (ग_लिखो_dst(state, device_type, FIXED_COMM))
		वापस -1;		/*	Write failed		*/
	अगर ((dst_pio_disable(state)) < 0)
		वापस -1;
	अगर (पढ़ो_dst(state, &reply, GET_ACK))
		वापस -1;		/*	Read failure		*/
	अगर (reply != ACK) अणु
		dprपूर्णांकk(2, "Write not Acknowledged! [Reply=0x%02x]\n", reply);
		वापस -1;		/*	Unack'd ग_लिखो		*/
	पूर्ण
	अगर (!dst_रुको_dst_पढ़ोy(state, DEVICE_INIT))
		वापस -1;		/*	DST not पढ़ोy yet	*/
	अगर (पढ़ो_dst(state, state->rxbuffer, FIXED_COMM))
		वापस -1;

	dst_pio_disable(state);
	अगर (state->rxbuffer[7] != dst_check_sum(state->rxbuffer, 7)) अणु
		dprपूर्णांकk(2, "Checksum failure!\n");
		वापस -1;		/*	Checksum failure	*/
	पूर्ण
	state->rxbuffer[7] = '\0';

	क्रम (i = 0, p_dst_type = dst_tlist; i < ARRAY_SIZE(dst_tlist); i++, p_dst_type++) अणु
		अगर (!म_भेदन (&state->rxbuffer[p_dst_type->offset], p_dst_type->device_id, म_माप (p_dst_type->device_id))) अणु
			use_type_flags = p_dst_type->type_flags;
			use_dst_type = p_dst_type->dst_type;

			/*	Card capabilities	*/
			state->dst_hw_cap = p_dst_type->dst_feature;
			pr_err("Recognise [%s]\n", p_dst_type->device_id);
			strscpy(state->fw_name, p_dst_type->device_id,
			        माप(state->fw_name));
			/*	Multiple tuners		*/
			अगर (p_dst_type->tuner_type & TUNER_TYPE_MULTI) अणु
				चयन (use_dst_type) अणु
				हाल DST_TYPE_IS_SAT:
					/*	STV0299 check	*/
					अगर (dst_check_stv0299(state) < 0) अणु
						pr_err("Unsupported\n");
						state->tuner_type = TUNER_TYPE_MB86A15;
					पूर्ण
					अवरोध;
				शेष:
					अवरोध;
				पूर्ण
				अगर (dst_check_mb86a15(state) < 0)
					pr_err("Unsupported\n");
			/*	Single tuner		*/
			पूर्ण अन्यथा अणु
				state->tuner_type = p_dst_type->tuner_type;
			पूर्ण
			क्रम (j = 0, p_tuner_list = tuner_list; j < ARRAY_SIZE(tuner_list); j++, p_tuner_list++) अणु
				अगर (!(म_भेदन(p_dst_type->device_id, p_tuner_list->fw_name, 7)) &&
					p_tuner_list->tuner_type == state->tuner_type) अणु
					pr_err("[%s] has a [%s]\n",
						p_dst_type->device_id, p_tuner_list->tuner_name);
				पूर्ण
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i >= ARRAY_SIZE(dst_tlist)) अणु
		pr_err("Unable to recognize %s or %s\n", &state->rxbuffer[0], &state->rxbuffer[1]);
		pr_err("please email linux-dvb@linuxtv.org with this type in");
		use_dst_type = DST_TYPE_IS_SAT;
		use_type_flags = DST_TYPE_HAS_SYMDIV;
	पूर्ण
	dst_type_prपूर्णांक(state, use_dst_type);
	state->type_flags = use_type_flags;
	state->dst_type = use_dst_type;
	dst_type_flags_prपूर्णांक(state);

	वापस 0;
पूर्ण

अटल पूर्णांक dst_probe(काष्ठा dst_state *state)
अणु
	mutex_init(&state->dst_mutex);
	अगर (dst_adकरोns & DST_TYPE_HAS_CA) अणु
		अगर ((rdc_8820_reset(state)) < 0) अणु
			pr_err("RDC 8820 RESET Failed.\n");
			वापस -1;
		पूर्ण
		msleep(4000);
	पूर्ण अन्यथा अणु
		msleep(100);
	पूर्ण
	अगर ((dst_comm_init(state)) < 0) अणु
		pr_err("DST Initialization Failed.\n");
		वापस -1;
	पूर्ण
	msleep(100);
	अगर (dst_get_device_id(state) < 0) अणु
		pr_err("unknown device.\n");
		वापस -1;
	पूर्ण
	अगर (dst_get_mac(state) < 0) अणु
		dprपूर्णांकk(2, "MAC: Unsupported command\n");
	पूर्ण
	अगर ((state->type_flags & DST_TYPE_HAS_MULTI_FE) || (state->type_flags & DST_TYPE_HAS_FW_BUILD)) अणु
		अगर (dst_get_tuner_info(state) < 0)
			dprपूर्णांकk(2, "Tuner: Unsupported command\n");
	पूर्ण
	अगर (state->type_flags & DST_TYPE_HAS_TS204) अणु
		dst_packsize(state, 204);
	पूर्ण
	अगर (state->type_flags & DST_TYPE_HAS_FW_BUILD) अणु
		अगर (dst_fw_ver(state) < 0) अणु
			dprपूर्णांकk(2, "FW: Unsupported command\n");
			वापस 0;
		पूर्ण
		अगर (dst_card_type(state) < 0) अणु
			dprपूर्णांकk(2, "Card: Unsupported command\n");
			वापस 0;
		पूर्ण
		अगर (dst_get_venकरोr(state) < 0) अणु
			dprपूर्णांकk(2, "Vendor: Unsupported command\n");
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dst_command(काष्ठा dst_state *state, u8 *data, u8 len)
अणु
	u8 reply;

	mutex_lock(&state->dst_mutex);
	अगर ((dst_comm_init(state)) < 0) अणु
		dprपूर्णांकk(1, "DST Communication Initialization Failed.\n");
		जाओ error;
	पूर्ण
	अगर (ग_लिखो_dst(state, data, len)) अणु
		dprपूर्णांकk(2, "Trying to recover..\n");
		अगर ((dst_error_recovery(state)) < 0) अणु
			pr_err("Recovery Failed.\n");
			जाओ error;
		पूर्ण
		जाओ error;
	पूर्ण
	अगर ((dst_pio_disable(state)) < 0) अणु
		pr_err("PIO Disable Failed.\n");
		जाओ error;
	पूर्ण
	अगर (state->type_flags & DST_TYPE_HAS_FW_1)
		mdelay(3);
	अगर (पढ़ो_dst(state, &reply, GET_ACK)) अणु
		dprपूर्णांकk(3, "Trying to recover..\n");
		अगर ((dst_error_recovery(state)) < 0) अणु
			dprपूर्णांकk(2, "Recovery Failed.\n");
			जाओ error;
		पूर्ण
		जाओ error;
	पूर्ण
	अगर (reply != ACK) अणु
		dprपूर्णांकk(2, "write not acknowledged 0x%02x\n", reply);
		जाओ error;
	पूर्ण
	अगर (len >= 2 && data[0] == 0 && (data[1] == 1 || data[1] == 3))
		जाओ error;
	अगर (state->type_flags & DST_TYPE_HAS_FW_1)
		mdelay(3);
	अन्यथा
		udelay(2000);
	अगर (!dst_रुको_dst_पढ़ोy(state, NO_DELAY))
		जाओ error;
	अगर (पढ़ो_dst(state, state->rxbuffer, FIXED_COMM)) अणु
		dprपूर्णांकk(3, "Trying to recover..\n");
		अगर ((dst_error_recovery(state)) < 0) अणु
			dprपूर्णांकk(2, "Recovery failed.\n");
			जाओ error;
		पूर्ण
		जाओ error;
	पूर्ण
	अगर (state->rxbuffer[7] != dst_check_sum(state->rxbuffer, 7)) अणु
		dprपूर्णांकk(2, "checksum failure\n");
		जाओ error;
	पूर्ण
	mutex_unlock(&state->dst_mutex);
	वापस 0;

error:
	mutex_unlock(&state->dst_mutex);
	वापस -EIO;

पूर्ण

अटल पूर्णांक dst_get_संकेत(काष्ठा dst_state *state)
अणु
	पूर्णांक retval;
	u8 get_संकेत[] = अणु 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfb पूर्ण;
	//dprपूर्णांकk("%s: Getting Signal strength and other parameters\n", __func__);
	अगर ((state->diseq_flags & ATTEMPT_TUNE) == 0) अणु
		state->decode_lock = state->decode_strength = state->decode_snr = 0;
		वापस 0;
	पूर्ण
	अगर (0 == (state->diseq_flags & HAS_LOCK)) अणु
		state->decode_lock = state->decode_strength = state->decode_snr = 0;
		वापस 0;
	पूर्ण
	अगर (समय_after_eq(jअगरfies, state->cur_jअगरf + (HZ / 5))) अणु
		retval = dst_command(state, get_संकेत, 8);
		अगर (retval < 0)
			वापस retval;
		अगर (state->dst_type == DST_TYPE_IS_SAT) अणु
			state->decode_lock = ((state->rxbuffer[6] & 0x10) == 0) ? 1 : 0;
			state->decode_strength = state->rxbuffer[5] << 8;
			state->decode_snr = state->rxbuffer[2] << 8 | state->rxbuffer[3];
		पूर्ण अन्यथा अगर ((state->dst_type == DST_TYPE_IS_TERR) || (state->dst_type == DST_TYPE_IS_CABLE)) अणु
			state->decode_lock = (state->rxbuffer[1]) ? 1 : 0;
			state->decode_strength = state->rxbuffer[4] << 8;
			state->decode_snr = state->rxbuffer[3] << 8;
		पूर्ण अन्यथा अगर (state->dst_type == DST_TYPE_IS_ATSC) अणु
			state->decode_lock = (state->rxbuffer[6] == 0x00) ? 1 : 0;
			state->decode_strength = state->rxbuffer[4] << 8;
			state->decode_snr = state->rxbuffer[2] << 8 | state->rxbuffer[3];
		पूर्ण
		state->cur_jअगरf = jअगरfies;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dst_tone_घातer_cmd(काष्ठा dst_state *state)
अणु
	u8 packet[8] = अणु 0x00, 0x09, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00 पूर्ण;

	अगर (state->dst_type != DST_TYPE_IS_SAT)
		वापस -EOPNOTSUPP;
	packet[4] = state->tx_tuna[4];
	packet[2] = state->tx_tuna[2];
	packet[3] = state->tx_tuna[3];
	packet[7] = dst_check_sum (packet, 7);
	वापस dst_command(state, packet, 8);
पूर्ण

अटल पूर्णांक dst_get_tuna(काष्ठा dst_state *state)
अणु
	पूर्णांक retval;

	अगर ((state->diseq_flags & ATTEMPT_TUNE) == 0)
		वापस 0;
	state->diseq_flags &= ~(HAS_LOCK);
	अगर (!dst_रुको_dst_पढ़ोy(state, NO_DELAY))
		वापस -EIO;
	अगर ((state->type_flags & DST_TYPE_HAS_VLF) &&
		!(state->dst_type == DST_TYPE_IS_ATSC))

		retval = पढ़ो_dst(state, state->rx_tuna, 10);
	अन्यथा
		retval = पढ़ो_dst(state, &state->rx_tuna[2], FIXED_COMM);
	अगर (retval < 0) अणु
		dprपूर्णांकk(3, "read not successful\n");
		वापस retval;
	पूर्ण
	अगर ((state->type_flags & DST_TYPE_HAS_VLF) &&
	   !(state->dst_type == DST_TYPE_IS_ATSC)) अणु

		अगर (state->rx_tuna[9] != dst_check_sum(&state->rx_tuna[0], 9)) अणु
			dprपूर्णांकk(2, "checksum failure ?\n");
			वापस -EIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (state->rx_tuna[9] != dst_check_sum(&state->rx_tuna[2], 7)) अणु
			dprपूर्णांकk(2, "checksum failure?\n");
			वापस -EIO;
		पूर्ण
	पूर्ण
	अगर (state->rx_tuna[2] == 0 && state->rx_tuna[3] == 0)
		वापस 0;
	अगर (state->dst_type == DST_TYPE_IS_SAT) अणु
		state->decode_freq = ((state->rx_tuna[2] & 0x7f) << 8) + state->rx_tuna[3];
	पूर्ण अन्यथा अणु
		state->decode_freq = ((state->rx_tuna[2] & 0x7f) << 16) + (state->rx_tuna[3] << 8) + state->rx_tuna[4];
	पूर्ण
	state->decode_freq = state->decode_freq * 1000;
	state->decode_lock = 1;
	state->diseq_flags |= HAS_LOCK;

	वापस 1;
पूर्ण

अटल पूर्णांक dst_set_voltage(काष्ठा dvb_frontend *fe,
			   क्रमागत fe_sec_voltage voltage);

अटल पूर्णांक dst_ग_लिखो_tuna(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dst_state *state = fe->demodulator_priv;
	पूर्णांक retval;
	u8 reply;

	dprपूर्णांकk(2, "type_flags 0x%x\n", state->type_flags);
	state->decode_freq = 0;
	state->decode_lock = state->decode_strength = state->decode_snr = 0;
	अगर (state->dst_type == DST_TYPE_IS_SAT) अणु
		अगर (!(state->diseq_flags & HAS_POWER))
			dst_set_voltage(fe, SEC_VOLTAGE_13);
	पूर्ण
	state->diseq_flags &= ~(HAS_LOCK | ATTEMPT_TUNE);
	mutex_lock(&state->dst_mutex);
	अगर ((dst_comm_init(state)) < 0) अणु
		dprपूर्णांकk(3, "DST Communication initialization failed.\n");
		जाओ error;
	पूर्ण
//	अगर (state->type_flags & DST_TYPE_HAS_NEWTUNE) अणु
	अगर ((state->type_flags & DST_TYPE_HAS_VLF) &&
		(!(state->dst_type == DST_TYPE_IS_ATSC))) अणु

		state->tx_tuna[9] = dst_check_sum(&state->tx_tuna[0], 9);
		retval = ग_लिखो_dst(state, &state->tx_tuna[0], 10);
	पूर्ण अन्यथा अणु
		state->tx_tuna[9] = dst_check_sum(&state->tx_tuna[2], 7);
		retval = ग_लिखो_dst(state, &state->tx_tuna[2], FIXED_COMM);
	पूर्ण
	अगर (retval < 0) अणु
		dst_pio_disable(state);
		dprपूर्णांकk(3, "write not successful\n");
		जाओ werr;
	पूर्ण
	अगर ((dst_pio_disable(state)) < 0) अणु
		dprपूर्णांकk(3, "DST PIO disable failed !\n");
		जाओ error;
	पूर्ण
	अगर ((पढ़ो_dst(state, &reply, GET_ACK) < 0)) अणु
		dprपूर्णांकk(3, "read verify not successful.\n");
		जाओ error;
	पूर्ण
	अगर (reply != ACK) अणु
		dprपूर्णांकk(3, "write not acknowledged 0x%02x\n", reply);
		जाओ error;
	पूर्ण
	state->diseq_flags |= ATTEMPT_TUNE;
	retval = dst_get_tuna(state);
werr:
	mutex_unlock(&state->dst_mutex);
	वापस retval;

error:
	mutex_unlock(&state->dst_mutex);
	वापस -EIO;
पूर्ण

/*
 * line22k0    0x00, 0x09, 0x00, 0xff, 0x01, 0x00, 0x00, 0x00
 * line22k1    0x00, 0x09, 0x01, 0xff, 0x01, 0x00, 0x00, 0x00
 * line22k2    0x00, 0x09, 0x02, 0xff, 0x01, 0x00, 0x00, 0x00
 * tone        0x00, 0x09, 0xff, 0x00, 0x01, 0x00, 0x00, 0x00
 * data        0x00, 0x09, 0xff, 0x01, 0x01, 0x00, 0x00, 0x00
 * घातer_off   0x00, 0x09, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00
 * घातer_on    0x00, 0x09, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00
 * Diseqc 1    0x00, 0x08, 0x04, 0xe0, 0x10, 0x38, 0xf0, 0xec
 * Diseqc 2    0x00, 0x08, 0x04, 0xe0, 0x10, 0x38, 0xf4, 0xe8
 * Diseqc 3    0x00, 0x08, 0x04, 0xe0, 0x10, 0x38, 0xf8, 0xe4
 * Diseqc 4    0x00, 0x08, 0x04, 0xe0, 0x10, 0x38, 0xfc, 0xe0
 */

अटल पूर्णांक dst_set_diseqc(काष्ठा dvb_frontend *fe, काष्ठा dvb_diseqc_master_cmd *cmd)
अणु
	काष्ठा dst_state *state = fe->demodulator_priv;
	u8 packet[8] = अणु 0x00, 0x08, 0x04, 0xe0, 0x10, 0x38, 0xf0, 0xec पूर्ण;

	अगर (state->dst_type != DST_TYPE_IS_SAT)
		वापस -EOPNOTSUPP;
	अगर (cmd->msg_len > 0 && cmd->msg_len < 5)
		स_नकल(&packet[3], cmd->msg, cmd->msg_len);
	अन्यथा अगर (cmd->msg_len == 5 && state->dst_hw_cap & DST_TYPE_HAS_DISEQC5)
		स_नकल(&packet[2], cmd->msg, cmd->msg_len);
	अन्यथा
		वापस -EINVAL;
	packet[7] = dst_check_sum(&packet[0], 7);
	वापस dst_command(state, packet, 8);
पूर्ण

अटल पूर्णांक dst_set_voltage(काष्ठा dvb_frontend *fe, क्रमागत fe_sec_voltage voltage)
अणु
	पूर्णांक need_cmd, retval = 0;
	काष्ठा dst_state *state = fe->demodulator_priv;

	state->voltage = voltage;
	अगर (state->dst_type != DST_TYPE_IS_SAT)
		वापस -EOPNOTSUPP;

	need_cmd = 0;

	चयन (voltage) अणु
	हाल SEC_VOLTAGE_13:
	हाल SEC_VOLTAGE_18:
		अगर ((state->diseq_flags & HAS_POWER) == 0)
			need_cmd = 1;
		state->diseq_flags |= HAS_POWER;
		state->tx_tuna[4] = 0x01;
		अवरोध;
	हाल SEC_VOLTAGE_OFF:
		need_cmd = 1;
		state->diseq_flags &= ~(HAS_POWER | HAS_LOCK | ATTEMPT_TUNE);
		state->tx_tuna[4] = 0x00;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (need_cmd)
		retval = dst_tone_घातer_cmd(state);

	वापस retval;
पूर्ण

अटल पूर्णांक dst_set_tone(काष्ठा dvb_frontend *fe, क्रमागत fe_sec_tone_mode tone)
अणु
	काष्ठा dst_state *state = fe->demodulator_priv;

	state->tone = tone;
	अगर (state->dst_type != DST_TYPE_IS_SAT)
		वापस -EOPNOTSUPP;

	चयन (tone) अणु
	हाल SEC_TONE_OFF:
		अगर (state->type_flags & DST_TYPE_HAS_OBS_REGS)
		    state->tx_tuna[2] = 0x00;
		अन्यथा
		    state->tx_tuna[2] = 0xff;
		अवरोध;

	हाल SEC_TONE_ON:
		state->tx_tuna[2] = 0x02;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस dst_tone_घातer_cmd(state);
पूर्ण

अटल पूर्णांक dst_send_burst(काष्ठा dvb_frontend *fe, क्रमागत fe_sec_mini_cmd minicmd)
अणु
	काष्ठा dst_state *state = fe->demodulator_priv;

	अगर (state->dst_type != DST_TYPE_IS_SAT)
		वापस -EOPNOTSUPP;
	state->minicmd = minicmd;
	चयन (minicmd) अणु
	हाल SEC_MINI_A:
		state->tx_tuna[3] = 0x02;
		अवरोध;
	हाल SEC_MINI_B:
		state->tx_tuna[3] = 0xff;
		अवरोध;
	पूर्ण
	वापस dst_tone_घातer_cmd(state);
पूर्ण


अटल पूर्णांक bt8xx_dst_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dst_state *state = fe->demodulator_priv;

	अटल u8 sat_tuna_188[] = अणु 0x09, 0x00, 0x03, 0xb6, 0x01, 0x00, 0x73, 0x21, 0x00, 0x00 पूर्ण;
	अटल u8 sat_tuna_204[] = अणु 0x00, 0x00, 0x03, 0xb6, 0x01, 0x55, 0xbd, 0x50, 0x00, 0x00 पूर्ण;
	अटल u8 ter_tuna_188[] = अणु 0x09, 0x00, 0x03, 0xb6, 0x01, 0x07, 0x00, 0x00, 0x00, 0x00 पूर्ण;
	अटल u8 ter_tuna_204[] = अणु 0x00, 0x00, 0x03, 0xb6, 0x01, 0x07, 0x00, 0x00, 0x00, 0x00 पूर्ण;
	अटल u8 cab_tuna_188[] = अणु 0x09, 0x00, 0x03, 0xb6, 0x01, 0x07, 0x00, 0x00, 0x00, 0x00 पूर्ण;
	अटल u8 cab_tuna_204[] = अणु 0x00, 0x00, 0x03, 0xb6, 0x01, 0x07, 0x00, 0x00, 0x00, 0x00 पूर्ण;
	अटल u8 atsc_tuner[] = अणु 0x00, 0x00, 0x03, 0xb6, 0x01, 0x07, 0x00, 0x00, 0x00, 0x00 पूर्ण;

	state->inversion = INVERSION_OFF;
	state->voltage = SEC_VOLTAGE_13;
	state->tone = SEC_TONE_OFF;
	state->diseq_flags = 0;
	state->k22 = 0x02;
	state->bandwidth = 7000000;
	state->cur_jअगरf = jअगरfies;
	अगर (state->dst_type == DST_TYPE_IS_SAT)
		स_नकल(state->tx_tuna, ((state->type_flags & DST_TYPE_HAS_VLF) ? sat_tuna_188 : sat_tuna_204), माप (sat_tuna_204));
	अन्यथा अगर (state->dst_type == DST_TYPE_IS_TERR)
		स_नकल(state->tx_tuna, ((state->type_flags & DST_TYPE_HAS_VLF) ? ter_tuna_188 : ter_tuna_204), माप (ter_tuna_204));
	अन्यथा अगर (state->dst_type == DST_TYPE_IS_CABLE)
		स_नकल(state->tx_tuna, ((state->type_flags & DST_TYPE_HAS_VLF) ? cab_tuna_188 : cab_tuna_204), माप (cab_tuna_204));
	अन्यथा अगर (state->dst_type == DST_TYPE_IS_ATSC)
		स_नकल(state->tx_tuna, atsc_tuner, माप (atsc_tuner));

	वापस 0;
पूर्ण

अटल पूर्णांक dst_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा dst_state *state = fe->demodulator_priv;

	*status = 0;
	अगर (state->diseq_flags & HAS_LOCK) अणु
//		dst_get_संकेत(state);	// करोn't require(?) to ask MCU
		अगर (state->decode_lock)
			*status |= FE_HAS_LOCK | FE_HAS_SIGNAL | FE_HAS_CARRIER | FE_HAS_SYNC | FE_HAS_VITERBI;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dst_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	काष्ठा dst_state *state = fe->demodulator_priv;

	पूर्णांक retval = dst_get_संकेत(state);
	*strength = state->decode_strength;

	वापस retval;
पूर्ण

अटल पूर्णांक dst_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा dst_state *state = fe->demodulator_priv;

	पूर्णांक retval = dst_get_संकेत(state);
	*snr = state->decode_snr;

	वापस retval;
पूर्ण

अटल पूर्णांक dst_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	पूर्णांक retval = -EINVAL;
	काष्ठा dst_state *state = fe->demodulator_priv;

	अगर (p != शून्य) अणु
		retval = dst_set_freq(state, p->frequency);
		अगर(retval != 0)
			वापस retval;
		dprपूर्णांकk(3, "Set Frequency=[%d]\n", p->frequency);

		अगर (state->dst_type == DST_TYPE_IS_SAT) अणु
			अगर (state->type_flags & DST_TYPE_HAS_OBS_REGS)
				dst_set_inversion(state, p->inversion);
			dst_set_fec(state, p->fec_inner);
			dst_set_symbolrate(state, p->symbol_rate);
			dst_set_polarization(state);
			dprपूर्णांकk(3, "Set Symbolrate=[%d]\n", p->symbol_rate);

		पूर्ण अन्यथा अगर (state->dst_type == DST_TYPE_IS_TERR)
			dst_set_bandwidth(state, p->bandwidth_hz);
		अन्यथा अगर (state->dst_type == DST_TYPE_IS_CABLE) अणु
			dst_set_fec(state, p->fec_inner);
			dst_set_symbolrate(state, p->symbol_rate);
			dst_set_modulation(state, p->modulation);
		पूर्ण
		retval = dst_ग_लिखो_tuna(fe);
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक dst_tune_frontend(काष्ठा dvb_frontend* fe,
			    bool re_tune,
			    अचिन्हित पूर्णांक mode_flags,
			    अचिन्हित पूर्णांक *delay,
			    क्रमागत fe_status *status)
अणु
	काष्ठा dst_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;

	अगर (re_tune) अणु
		dst_set_freq(state, p->frequency);
		dprपूर्णांकk(3, "Set Frequency=[%d]\n", p->frequency);

		अगर (state->dst_type == DST_TYPE_IS_SAT) अणु
			अगर (state->type_flags & DST_TYPE_HAS_OBS_REGS)
				dst_set_inversion(state, p->inversion);
			dst_set_fec(state, p->fec_inner);
			dst_set_symbolrate(state, p->symbol_rate);
			dst_set_polarization(state);
			dprपूर्णांकk(3, "Set Symbolrate=[%d]\n", p->symbol_rate);

		पूर्ण अन्यथा अगर (state->dst_type == DST_TYPE_IS_TERR)
			dst_set_bandwidth(state, p->bandwidth_hz);
		अन्यथा अगर (state->dst_type == DST_TYPE_IS_CABLE) अणु
			dst_set_fec(state, p->fec_inner);
			dst_set_symbolrate(state, p->symbol_rate);
			dst_set_modulation(state, p->modulation);
		पूर्ण
		dst_ग_लिखो_tuna(fe);
	पूर्ण

	अगर (!(mode_flags & FE_TUNE_MODE_ONESHOT))
		dst_पढ़ो_status(fe, status);

	*delay = HZ/10;
	वापस 0;
पूर्ण

अटल क्रमागत dvbfe_algo dst_get_tuning_algo(काष्ठा dvb_frontend *fe)
अणु
	वापस dst_algo ? DVBFE_ALGO_HW : DVBFE_ALGO_SW;
पूर्ण

अटल पूर्णांक dst_get_frontend(काष्ठा dvb_frontend *fe,
			    काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा dst_state *state = fe->demodulator_priv;

	p->frequency = state->decode_freq;
	अगर (state->dst_type == DST_TYPE_IS_SAT) अणु
		अगर (state->type_flags & DST_TYPE_HAS_OBS_REGS)
			p->inversion = state->inversion;
		p->symbol_rate = state->symbol_rate;
		p->fec_inner = dst_get_fec(state);
	पूर्ण अन्यथा अगर (state->dst_type == DST_TYPE_IS_TERR) अणु
		p->bandwidth_hz = state->bandwidth;
	पूर्ण अन्यथा अगर (state->dst_type == DST_TYPE_IS_CABLE) अणु
		p->symbol_rate = state->symbol_rate;
		p->fec_inner = dst_get_fec(state);
		p->modulation = dst_get_modulation(state);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bt8xx_dst_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dst_state *state = fe->demodulator_priv;
	अगर (state->dst_ca) अणु
		dvb_unरेजिस्टर_device(state->dst_ca);
#अगर_घोषित CONFIG_MEDIA_ATTACH
		symbol_put(dst_ca_attach);
#पूर्ण_अगर
	पूर्ण
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops dst_dvbt_ops;
अटल स्थिर काष्ठा dvb_frontend_ops dst_dvbs_ops;
अटल स्थिर काष्ठा dvb_frontend_ops dst_dvbc_ops;
अटल स्थिर काष्ठा dvb_frontend_ops dst_atsc_ops;

काष्ठा dst_state *dst_attach(काष्ठा dst_state *state, काष्ठा dvb_adapter *dvb_adapter)
अणु
	/* check अगर the ASIC is there */
	अगर (dst_probe(state) < 0) अणु
		kमुक्त(state);
		वापस शून्य;
	पूर्ण
	/* determine settings based on type */
	/* create dvb_frontend */
	चयन (state->dst_type) अणु
	हाल DST_TYPE_IS_TERR:
		स_नकल(&state->frontend.ops, &dst_dvbt_ops, माप(काष्ठा dvb_frontend_ops));
		अवरोध;
	हाल DST_TYPE_IS_CABLE:
		स_नकल(&state->frontend.ops, &dst_dvbc_ops, माप(काष्ठा dvb_frontend_ops));
		अवरोध;
	हाल DST_TYPE_IS_SAT:
		स_नकल(&state->frontend.ops, &dst_dvbs_ops, माप(काष्ठा dvb_frontend_ops));
		अवरोध;
	हाल DST_TYPE_IS_ATSC:
		स_नकल(&state->frontend.ops, &dst_atsc_ops, माप(काष्ठा dvb_frontend_ops));
		अवरोध;
	शेष:
		pr_err("unknown DST type. please report to the LinuxTV.org DVB mailinglist.\n");
		kमुक्त(state);
		वापस शून्य;
	पूर्ण
	state->frontend.demodulator_priv = state;

	वापस state;				/*	Manu (DST is a card not a frontend)	*/
पूर्ण

EXPORT_SYMBOL(dst_attach);

अटल स्थिर काष्ठा dvb_frontend_ops dst_dvbt_ops = अणु
	.delsys = अणु SYS_DVBT पूर्ण,
	.info = अणु
		.name = "DST DVB-T",
		.frequency_min_hz = 137 * MHz,
		.frequency_max_hz = 858 * MHz,
		.frequency_stepsize_hz = 166667,
		.caps = FE_CAN_FEC_AUTO			|
			FE_CAN_QAM_AUTO			|
			FE_CAN_QAM_16			|
			FE_CAN_QAM_32			|
			FE_CAN_QAM_64			|
			FE_CAN_QAM_128			|
			FE_CAN_QAM_256			|
			FE_CAN_TRANSMISSION_MODE_AUTO	|
			FE_CAN_GUARD_INTERVAL_AUTO
	पूर्ण,

	.release = bt8xx_dst_release,
	.init = bt8xx_dst_init,
	.tune = dst_tune_frontend,
	.set_frontend = dst_set_frontend,
	.get_frontend = dst_get_frontend,
	.get_frontend_algo = dst_get_tuning_algo,
	.पढ़ो_status = dst_पढ़ो_status,
	.पढ़ो_संकेत_strength = dst_पढ़ो_संकेत_strength,
	.पढ़ो_snr = dst_पढ़ो_snr,
पूर्ण;

अटल स्थिर काष्ठा dvb_frontend_ops dst_dvbs_ops = अणु
	.delsys = अणु SYS_DVBS पूर्ण,
	.info = अणु
		.name = "DST DVB-S",
		.frequency_min_hz   =  950 * MHz,
		.frequency_max_hz   = 2150 * MHz,
		.frequency_stepsize_hz = 1 * MHz,
		.frequency_tolerance_hz = 29500 * kHz,
		.symbol_rate_min = 1000000,
		.symbol_rate_max = 45000000,
	/*     . symbol_rate_tolerance	=	???,*/
		.caps = FE_CAN_FEC_AUTO | FE_CAN_QPSK
	पूर्ण,

	.release = bt8xx_dst_release,
	.init = bt8xx_dst_init,
	.tune = dst_tune_frontend,
	.set_frontend = dst_set_frontend,
	.get_frontend = dst_get_frontend,
	.get_frontend_algo = dst_get_tuning_algo,
	.पढ़ो_status = dst_पढ़ो_status,
	.पढ़ो_संकेत_strength = dst_पढ़ो_संकेत_strength,
	.पढ़ो_snr = dst_पढ़ो_snr,
	.diseqc_send_burst = dst_send_burst,
	.diseqc_send_master_cmd = dst_set_diseqc,
	.set_voltage = dst_set_voltage,
	.set_tone = dst_set_tone,
पूर्ण;

अटल स्थिर काष्ठा dvb_frontend_ops dst_dvbc_ops = अणु
	.delsys = अणु SYS_DVBC_ANNEX_A पूर्ण,
	.info = अणु
		.name = "DST DVB-C",
		.frequency_min_hz =  51 * MHz,
		.frequency_max_hz = 858 * MHz,
		.frequency_stepsize_hz = 62500,
		.symbol_rate_min = 1000000,
		.symbol_rate_max = 45000000,
		.caps = FE_CAN_FEC_AUTO |
			FE_CAN_QAM_AUTO |
			FE_CAN_QAM_16	|
			FE_CAN_QAM_32	|
			FE_CAN_QAM_64	|
			FE_CAN_QAM_128	|
			FE_CAN_QAM_256
	पूर्ण,

	.release = bt8xx_dst_release,
	.init = bt8xx_dst_init,
	.tune = dst_tune_frontend,
	.set_frontend = dst_set_frontend,
	.get_frontend = dst_get_frontend,
	.get_frontend_algo = dst_get_tuning_algo,
	.पढ़ो_status = dst_पढ़ो_status,
	.पढ़ो_संकेत_strength = dst_पढ़ो_संकेत_strength,
	.पढ़ो_snr = dst_पढ़ो_snr,
पूर्ण;

अटल स्थिर काष्ठा dvb_frontend_ops dst_atsc_ops = अणु
	.delsys = अणु SYS_ATSC पूर्ण,
	.info = अणु
		.name = "DST ATSC",
		.frequency_min_hz = 510 * MHz,
		.frequency_max_hz = 858 * MHz,
		.frequency_stepsize_hz = 62500,
		.symbol_rate_min = 1000000,
		.symbol_rate_max = 45000000,
		.caps = FE_CAN_FEC_AUTO | FE_CAN_QAM_AUTO | FE_CAN_QAM_64 | FE_CAN_QAM_256 | FE_CAN_8VSB
	पूर्ण,

	.release = bt8xx_dst_release,
	.init = bt8xx_dst_init,
	.tune = dst_tune_frontend,
	.set_frontend = dst_set_frontend,
	.get_frontend = dst_get_frontend,
	.get_frontend_algo = dst_get_tuning_algo,
	.पढ़ो_status = dst_पढ़ो_status,
	.पढ़ो_संकेत_strength = dst_पढ़ो_संकेत_strength,
	.पढ़ो_snr = dst_पढ़ो_snr,
पूर्ण;

MODULE_DESCRIPTION("DST DVB-S/T/C/ATSC Combo Frontend driver");
MODULE_AUTHOR("Jamie Honan, Manu Abraham");
MODULE_LICENSE("GPL");
