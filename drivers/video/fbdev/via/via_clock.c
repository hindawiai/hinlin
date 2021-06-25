<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 1998-2008 VIA Technologies, Inc. All Rights Reserved.
 * Copyright 2001-2008 S3 Graphics, Inc. All Rights Reserved.
 * Copyright 2011 Florian Tobias Schandinat <FlorianSchandinat@gmx.de>
 */
/*
 * घड़ी and PLL management functions
 */

#समावेश <linux/kernel.h>
#समावेश <linux/via-core.h>

#समावेश "via_clock.h"
#समावेश "global.h"
#समावेश "debug.h"

अटल स्थिर अक्षर *via_slap = "Please slap VIA Technologies to motivate them "
	"releasing full documentation for your platform!\n";

अटल अंतरभूत u32 cle266_encode_pll(काष्ठा via_pll_config pll)
अणु
	वापस (pll.multiplier << 8)
		| (pll.rshअगरt << 6)
		| pll.भागisor;
पूर्ण

अटल अंतरभूत u32 k800_encode_pll(काष्ठा via_pll_config pll)
अणु
	वापस ((pll.भागisor - 2) << 16)
		| (pll.rshअगरt << 10)
		| (pll.multiplier - 2);
पूर्ण

अटल अंतरभूत u32 vx855_encode_pll(काष्ठा via_pll_config pll)
अणु
	वापस (pll.भागisor << 16)
		| (pll.rshअगरt << 10)
		| pll.multiplier;
पूर्ण

अटल अंतरभूत व्योम cle266_set_primary_pll_encoded(u32 data)
अणु
	via_ग_लिखो_reg_mask(VIASR, 0x40, 0x02, 0x02); /* enable reset */
	via_ग_लिखो_reg(VIASR, 0x46, data & 0xFF);
	via_ग_लिखो_reg(VIASR, 0x47, (data >> 8) & 0xFF);
	via_ग_लिखो_reg_mask(VIASR, 0x40, 0x00, 0x02); /* disable reset */
पूर्ण

अटल अंतरभूत व्योम k800_set_primary_pll_encoded(u32 data)
अणु
	via_ग_लिखो_reg_mask(VIASR, 0x40, 0x02, 0x02); /* enable reset */
	via_ग_लिखो_reg(VIASR, 0x44, data & 0xFF);
	via_ग_लिखो_reg(VIASR, 0x45, (data >> 8) & 0xFF);
	via_ग_लिखो_reg(VIASR, 0x46, (data >> 16) & 0xFF);
	via_ग_लिखो_reg_mask(VIASR, 0x40, 0x00, 0x02); /* disable reset */
पूर्ण

अटल अंतरभूत व्योम cle266_set_secondary_pll_encoded(u32 data)
अणु
	via_ग_लिखो_reg_mask(VIASR, 0x40, 0x04, 0x04); /* enable reset */
	via_ग_लिखो_reg(VIASR, 0x44, data & 0xFF);
	via_ग_लिखो_reg(VIASR, 0x45, (data >> 8) & 0xFF);
	via_ग_लिखो_reg_mask(VIASR, 0x40, 0x00, 0x04); /* disable reset */
पूर्ण

अटल अंतरभूत व्योम k800_set_secondary_pll_encoded(u32 data)
अणु
	via_ग_लिखो_reg_mask(VIASR, 0x40, 0x04, 0x04); /* enable reset */
	via_ग_लिखो_reg(VIASR, 0x4A, data & 0xFF);
	via_ग_लिखो_reg(VIASR, 0x4B, (data >> 8) & 0xFF);
	via_ग_लिखो_reg(VIASR, 0x4C, (data >> 16) & 0xFF);
	via_ग_लिखो_reg_mask(VIASR, 0x40, 0x00, 0x04); /* disable reset */
पूर्ण

अटल अंतरभूत व्योम set_engine_pll_encoded(u32 data)
अणु
	via_ग_लिखो_reg_mask(VIASR, 0x40, 0x01, 0x01); /* enable reset */
	via_ग_लिखो_reg(VIASR, 0x47, data & 0xFF);
	via_ग_लिखो_reg(VIASR, 0x48, (data >> 8) & 0xFF);
	via_ग_लिखो_reg(VIASR, 0x49, (data >> 16) & 0xFF);
	via_ग_लिखो_reg_mask(VIASR, 0x40, 0x00, 0x01); /* disable reset */
पूर्ण

अटल व्योम cle266_set_primary_pll(काष्ठा via_pll_config config)
अणु
	cle266_set_primary_pll_encoded(cle266_encode_pll(config));
पूर्ण

अटल व्योम k800_set_primary_pll(काष्ठा via_pll_config config)
अणु
	k800_set_primary_pll_encoded(k800_encode_pll(config));
पूर्ण

अटल व्योम vx855_set_primary_pll(काष्ठा via_pll_config config)
अणु
	k800_set_primary_pll_encoded(vx855_encode_pll(config));
पूर्ण

अटल व्योम cle266_set_secondary_pll(काष्ठा via_pll_config config)
अणु
	cle266_set_secondary_pll_encoded(cle266_encode_pll(config));
पूर्ण

अटल व्योम k800_set_secondary_pll(काष्ठा via_pll_config config)
अणु
	k800_set_secondary_pll_encoded(k800_encode_pll(config));
पूर्ण

अटल व्योम vx855_set_secondary_pll(काष्ठा via_pll_config config)
अणु
	k800_set_secondary_pll_encoded(vx855_encode_pll(config));
पूर्ण

अटल व्योम k800_set_engine_pll(काष्ठा via_pll_config config)
अणु
	set_engine_pll_encoded(k800_encode_pll(config));
पूर्ण

अटल व्योम vx855_set_engine_pll(काष्ठा via_pll_config config)
अणु
	set_engine_pll_encoded(vx855_encode_pll(config));
पूर्ण

अटल व्योम set_primary_pll_state(u8 state)
अणु
	u8 value;

	चयन (state) अणु
	हाल VIA_STATE_ON:
		value = 0x20;
		अवरोध;
	हाल VIA_STATE_OFF:
		value = 0x00;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	via_ग_लिखो_reg_mask(VIASR, 0x2D, value, 0x30);
पूर्ण

अटल व्योम set_secondary_pll_state(u8 state)
अणु
	u8 value;

	चयन (state) अणु
	हाल VIA_STATE_ON:
		value = 0x08;
		अवरोध;
	हाल VIA_STATE_OFF:
		value = 0x00;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	via_ग_लिखो_reg_mask(VIASR, 0x2D, value, 0x0C);
पूर्ण

अटल व्योम set_engine_pll_state(u8 state)
अणु
	u8 value;

	चयन (state) अणु
	हाल VIA_STATE_ON:
		value = 0x02;
		अवरोध;
	हाल VIA_STATE_OFF:
		value = 0x00;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	via_ग_लिखो_reg_mask(VIASR, 0x2D, value, 0x03);
पूर्ण

अटल व्योम set_primary_घड़ी_state(u8 state)
अणु
	u8 value;

	चयन (state) अणु
	हाल VIA_STATE_ON:
		value = 0x20;
		अवरोध;
	हाल VIA_STATE_OFF:
		value = 0x00;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	via_ग_लिखो_reg_mask(VIASR, 0x1B, value, 0x30);
पूर्ण

अटल व्योम set_secondary_घड़ी_state(u8 state)
अणु
	u8 value;

	चयन (state) अणु
	हाल VIA_STATE_ON:
		value = 0x80;
		अवरोध;
	हाल VIA_STATE_OFF:
		value = 0x00;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	via_ग_लिखो_reg_mask(VIASR, 0x1B, value, 0xC0);
पूर्ण

अटल अंतरभूत u8 set_घड़ी_source_common(क्रमागत via_clksrc source, bool use_pll)
अणु
	u8 data = 0;

	चयन (source) अणु
	हाल VIA_CLKSRC_X1:
		data = 0x00;
		अवरोध;
	हाल VIA_CLKSRC_TVX1:
		data = 0x02;
		अवरोध;
	हाल VIA_CLKSRC_TVPLL:
		data = 0x04; /* 0x06 should be the same */
		अवरोध;
	हाल VIA_CLKSRC_DVP1TVCLKR:
		data = 0x0A;
		अवरोध;
	हाल VIA_CLKSRC_CAP0:
		data = 0xC;
		अवरोध;
	हाल VIA_CLKSRC_CAP1:
		data = 0x0E;
		अवरोध;
	पूर्ण

	अगर (!use_pll)
		data |= 1;

	वापस data;
पूर्ण

अटल व्योम set_primary_घड़ी_source(क्रमागत via_clksrc source, bool use_pll)
अणु
	u8 data = set_घड़ी_source_common(source, use_pll) << 4;
	via_ग_लिखो_reg_mask(VIACR, 0x6C, data, 0xF0);
पूर्ण

अटल व्योम set_secondary_घड़ी_source(क्रमागत via_clksrc source, bool use_pll)
अणु
	u8 data = set_घड़ी_source_common(source, use_pll);
	via_ग_लिखो_reg_mask(VIACR, 0x6C, data, 0x0F);
पूर्ण

अटल व्योम dummy_set_घड़ी_state(u8 state)
अणु
	prपूर्णांकk(KERN_INFO "Using undocumented set clock state.\n%s", via_slap);
पूर्ण

अटल व्योम dummy_set_घड़ी_source(क्रमागत via_clksrc source, bool use_pll)
अणु
	prपूर्णांकk(KERN_INFO "Using undocumented set clock source.\n%s", via_slap);
पूर्ण

अटल व्योम dummy_set_pll_state(u8 state)
अणु
	prपूर्णांकk(KERN_INFO "Using undocumented set PLL state.\n%s", via_slap);
पूर्ण

अटल व्योम dummy_set_pll(काष्ठा via_pll_config config)
अणु
	prपूर्णांकk(KERN_INFO "Using undocumented set PLL.\n%s", via_slap);
पूर्ण

अटल व्योम noop_set_घड़ी_state(u8 state)
अणु
पूर्ण

व्योम via_घड़ी_init(काष्ठा via_घड़ी *घड़ी, पूर्णांक gfx_chip)
अणु
	चयन (gfx_chip) अणु
	हाल UNICHROME_CLE266:
	हाल UNICHROME_K400:
		घड़ी->set_primary_घड़ी_state = dummy_set_घड़ी_state;
		घड़ी->set_primary_घड़ी_source = dummy_set_घड़ी_source;
		घड़ी->set_primary_pll_state = dummy_set_pll_state;
		घड़ी->set_primary_pll = cle266_set_primary_pll;

		घड़ी->set_secondary_घड़ी_state = dummy_set_घड़ी_state;
		घड़ी->set_secondary_घड़ी_source = dummy_set_घड़ी_source;
		घड़ी->set_secondary_pll_state = dummy_set_pll_state;
		घड़ी->set_secondary_pll = cle266_set_secondary_pll;

		घड़ी->set_engine_pll_state = dummy_set_pll_state;
		घड़ी->set_engine_pll = dummy_set_pll;
		अवरोध;
	हाल UNICHROME_K800:
	हाल UNICHROME_PM800:
	हाल UNICHROME_CN700:
	हाल UNICHROME_CX700:
	हाल UNICHROME_CN750:
	हाल UNICHROME_K8M890:
	हाल UNICHROME_P4M890:
	हाल UNICHROME_P4M900:
	हाल UNICHROME_VX800:
		घड़ी->set_primary_घड़ी_state = set_primary_घड़ी_state;
		घड़ी->set_primary_घड़ी_source = set_primary_घड़ी_source;
		घड़ी->set_primary_pll_state = set_primary_pll_state;
		घड़ी->set_primary_pll = k800_set_primary_pll;

		घड़ी->set_secondary_घड़ी_state = set_secondary_घड़ी_state;
		घड़ी->set_secondary_घड़ी_source = set_secondary_घड़ी_source;
		घड़ी->set_secondary_pll_state = set_secondary_pll_state;
		घड़ी->set_secondary_pll = k800_set_secondary_pll;

		घड़ी->set_engine_pll_state = set_engine_pll_state;
		घड़ी->set_engine_pll = k800_set_engine_pll;
		अवरोध;
	हाल UNICHROME_VX855:
	हाल UNICHROME_VX900:
		घड़ी->set_primary_घड़ी_state = set_primary_घड़ी_state;
		घड़ी->set_primary_घड़ी_source = set_primary_घड़ी_source;
		घड़ी->set_primary_pll_state = set_primary_pll_state;
		घड़ी->set_primary_pll = vx855_set_primary_pll;

		घड़ी->set_secondary_घड़ी_state = set_secondary_घड़ी_state;
		घड़ी->set_secondary_घड़ी_source = set_secondary_घड़ी_source;
		घड़ी->set_secondary_pll_state = set_secondary_pll_state;
		घड़ी->set_secondary_pll = vx855_set_secondary_pll;

		घड़ी->set_engine_pll_state = set_engine_pll_state;
		घड़ी->set_engine_pll = vx855_set_engine_pll;
		अवरोध;

	पूर्ण

	अगर (machine_is_olpc()) अणु
		/* The OLPC XO-1.5 cannot suspend/resume reliably अगर the
		 * IGA1/IGA2 घड़ीs are set as on or off (memory rot
		 * occasionally happens during suspend under such
		 * configurations).
		 *
		 * The only known stable scenario is to leave this bits as-is,
		 * which in their शेष states are करोcumented to enable the
		 * घड़ी only when it is needed.
		 */
		घड़ी->set_primary_घड़ी_state = noop_set_घड़ी_state;
		घड़ी->set_secondary_घड़ी_state = noop_set_घड़ी_state;
	पूर्ण
पूर्ण
