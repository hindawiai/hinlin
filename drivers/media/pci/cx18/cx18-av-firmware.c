<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  cx18 ADEC firmware functions
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 *  Copyright (C) 2008  Andy Walls <awalls@md.metrocast.net>
 */

#समावेश "cx18-driver.h"
#समावेश "cx18-io.h"
#समावेश <linux/firmware.h>

#घोषणा CX18_AUDIO_ENABLE    0xc72014
#घोषणा CX18_AI1_MUX_MASK    0x30
#घोषणा CX18_AI1_MUX_I2S1    0x00
#घोषणा CX18_AI1_MUX_I2S2    0x10
#घोषणा CX18_AI1_MUX_843_I2S 0x20
#घोषणा CX18_AI1_MUX_INVALID 0x30

#घोषणा FWखाता "v4l-cx23418-dig.fw"

अटल पूर्णांक cx18_av_verअगरyfw(काष्ठा cx18 *cx, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा v4l2_subdev *sd = &cx->av_state.sd;
	पूर्णांक ret = 0;
	स्थिर u8 *data;
	u32 size;
	पूर्णांक addr;
	u32 expected, dl_control;

	/* Ensure we put the 8051 in reset and enable firmware upload mode */
	dl_control = cx18_av_पढ़ो4(cx, CXADEC_DL_CTL);
	करो अणु
		dl_control &= 0x00ffffff;
		dl_control |= 0x0f000000;
		cx18_av_ग_लिखो4_noretry(cx, CXADEC_DL_CTL, dl_control);
		dl_control = cx18_av_पढ़ो4(cx, CXADEC_DL_CTL);
	पूर्ण जबतक ((dl_control & 0xff000000) != 0x0f000000);

	/* Read and स्वतः increment until at address 0x0000 */
	जबतक (dl_control & 0x3fff)
		dl_control = cx18_av_पढ़ो4(cx, CXADEC_DL_CTL);

	data = fw->data;
	size = fw->size;
	क्रम (addr = 0; addr < size; addr++) अणु
		dl_control &= 0xffff3fff; /* ignore top 2 bits of address */
		expected = 0x0f000000 | ((u32)data[addr] << 16) | addr;
		अगर (expected != dl_control) अणु
			CX18_ERR_DEV(sd, "verification of %s firmware load failed: expected %#010x got %#010x\n",
				     FWखाता, expected, dl_control);
			ret = -EIO;
			अवरोध;
		पूर्ण
		dl_control = cx18_av_पढ़ो4(cx, CXADEC_DL_CTL);
	पूर्ण
	अगर (ret == 0)
		CX18_INFO_DEV(sd, "verified load of %s firmware (%d bytes)\n",
			      FWखाता, size);
	वापस ret;
पूर्ण

पूर्णांक cx18_av_loadfw(काष्ठा cx18 *cx)
अणु
	काष्ठा v4l2_subdev *sd = &cx->av_state.sd;
	स्थिर काष्ठा firmware *fw = शून्य;
	u32 size;
	u32 u, v;
	स्थिर u8 *ptr;
	पूर्णांक i;
	पूर्णांक retries1 = 0;

	अगर (request_firmware(&fw, FWखाता, &cx->pci_dev->dev) != 0) अणु
		CX18_ERR_DEV(sd, "unable to open firmware %s\n", FWखाता);
		वापस -EINVAL;
	पूर्ण

	/* The firmware load often has byte errors, so allow क्रम several
	   retries, both at byte level and at the firmware load level. */
	जबतक (retries1 < 5) अणु
		cx18_av_ग_लिखो4_expect(cx, CXADEC_CHIP_CTRL, 0x00010000,
					  0x00008430, 0xffffffff); /* cx25843 */
		cx18_av_ग_लिखो_expect(cx, CXADEC_STD_DET_CTL, 0xf6, 0xf6, 0xff);

		/* Reset the Mako core, Register is alias of CXADEC_CHIP_CTRL */
		cx18_av_ग_लिखो4_expect(cx, 0x8100, 0x00010000,
					  0x00008430, 0xffffffff); /* cx25843 */

		/* Put the 8051 in reset and enable firmware upload */
		cx18_av_ग_लिखो4_noretry(cx, CXADEC_DL_CTL, 0x0F000000);

		ptr = fw->data;
		size = fw->size;

		क्रम (i = 0; i < size; i++) अणु
			u32 dl_control = 0x0F000000 | i | ((u32)ptr[i] << 16);
			u32 value = 0;
			पूर्णांक retries2;
			पूर्णांक unrec_err = 0;

			क्रम (retries2 = 0; retries2 < CX18_MAX_MMIO_WR_RETRIES;
			     retries2++) अणु
				cx18_av_ग_लिखो4_noretry(cx, CXADEC_DL_CTL,
						       dl_control);
				udelay(10);
				value = cx18_av_पढ़ो4(cx, CXADEC_DL_CTL);
				अगर (value == dl_control)
					अवरोध;
				/* Check अगर we can correct the byte by changing
				   the address.  We can only ग_लिखो the lower
				   address byte of the address. */
				अगर ((value & 0x3F00) != (dl_control & 0x3F00)) अणु
					unrec_err = 1;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (unrec_err || retries2 >= CX18_MAX_MMIO_WR_RETRIES)
				अवरोध;
		पूर्ण
		अगर (i == size)
			अवरोध;
		retries1++;
	पूर्ण
	अगर (retries1 >= 5) अणु
		CX18_ERR_DEV(sd, "unable to load firmware %s\n", FWखाता);
		release_firmware(fw);
		वापस -EIO;
	पूर्ण

	cx18_av_ग_लिखो4_expect(cx, CXADEC_DL_CTL,
				0x03000000 | fw->size, 0x03000000, 0x13000000);

	CX18_INFO_DEV(sd, "loaded %s firmware (%d bytes)\n", FWखाता, size);

	अगर (cx18_av_verअगरyfw(cx, fw) == 0)
		cx18_av_ग_लिखो4_expect(cx, CXADEC_DL_CTL,
				0x13000000 | fw->size, 0x13000000, 0x13000000);

	/* Output to the 416 */
	cx18_av_and_or4(cx, CXADEC_PIN_CTRL1, ~0, 0x78000);

	/* Audio input control 1 set to Sony mode */
	/* Audio output input 2 is 0 क्रम slave operation input */
	/* 0xC4000914[5]: 0 = left sample on WS=0, 1 = left sample on WS=1 */
	/* 0xC4000914[7]: 0 = Philips mode, 1 = Sony mode (1st SCK rising edge
	   after WS transition क्रम first bit of audio word. */
	cx18_av_ग_लिखो4(cx, CXADEC_I2S_IN_CTL, 0x000000A0);

	/* Audio output control 1 is set to Sony mode */
	/* Audio output control 2 is set to 1 क्रम master mode */
	/* 0xC4000918[5]: 0 = left sample on WS=0, 1 = left sample on WS=1 */
	/* 0xC4000918[7]: 0 = Philips mode, 1 = Sony mode (1st SCK rising edge
	   after WS transition क्रम first bit of audio word. */
	/* 0xC4000918[8]: 0 = slave operation, 1 = master (SCK_OUT and WS_OUT
	   are generated) */
	cx18_av_ग_लिखो4(cx, CXADEC_I2S_OUT_CTL, 0x000001A0);

	/* set alt I2s master घड़ी to /0x16 and enable alt भागider i2s
	   passthrough */
	cx18_av_ग_लिखो4(cx, CXADEC_PIN_CFG3, 0x5600B687);

	cx18_av_ग_लिखो4_expect(cx, CXADEC_STD_DET_CTL, 0x000000F6, 0x000000F6,
								  0x3F00FFFF);
	/* CxDevWrReg(CXADEC_STD_DET_CTL, 0x000000FF); */

	/* Set bit 0 in रेजिस्टर 0x9CC to signअगरy that this is MiniMe. */
	/* Register 0x09CC is defined by the Merlin firmware, and करोesn't
	   have a name in the spec. */
	cx18_av_ग_लिखो4(cx, 0x09CC, 1);

	v = cx18_पढ़ो_reg(cx, CX18_AUDIO_ENABLE);
	/* If bit 11 is 1, clear bit 10 */
	अगर (v & 0x800)
		cx18_ग_लिखो_reg_expect(cx, v & 0xFFFFFBFF, CX18_AUDIO_ENABLE,
				      0, 0x400);

	/* Toggle the AI1 MUX */
	v = cx18_पढ़ो_reg(cx, CX18_AUDIO_ENABLE);
	u = v & CX18_AI1_MUX_MASK;
	v &= ~CX18_AI1_MUX_MASK;
	अगर (u == CX18_AI1_MUX_843_I2S || u == CX18_AI1_MUX_INVALID) अणु
		/* Switch to I2S1 */
		v |= CX18_AI1_MUX_I2S1;
		cx18_ग_लिखो_reg_expect(cx, v | 0xb00, CX18_AUDIO_ENABLE,
				      v, CX18_AI1_MUX_MASK);
		/* Switch back to the A/V decoder core I2S output */
		v = (v & ~CX18_AI1_MUX_MASK) | CX18_AI1_MUX_843_I2S;
	पूर्ण अन्यथा अणु
		/* Switch to the A/V decoder core I2S output */
		v |= CX18_AI1_MUX_843_I2S;
		cx18_ग_लिखो_reg_expect(cx, v | 0xb00, CX18_AUDIO_ENABLE,
				      v, CX18_AI1_MUX_MASK);
		/* Switch back to I2S1 or I2S2 */
		v = (v & ~CX18_AI1_MUX_MASK) | u;
	पूर्ण
	cx18_ग_लिखो_reg_expect(cx, v | 0xb00, CX18_AUDIO_ENABLE,
			      v, CX18_AI1_MUX_MASK);

	/* Enable WW स्वतः audio standard detection */
	v = cx18_av_पढ़ो4(cx, CXADEC_STD_DET_CTL);
	v |= 0xFF;   /* Auto by शेष */
	v |= 0x400;  /* Stereo by शेष */
	v |= 0x14000000;
	cx18_av_ग_लिखो4_expect(cx, CXADEC_STD_DET_CTL, v, v, 0x3F00FFFF);

	release_firmware(fw);
	वापस 0;
पूर्ण

MODULE_FIRMWARE(FWखाता);
