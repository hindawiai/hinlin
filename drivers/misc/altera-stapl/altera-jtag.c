<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * altera-jtag.c
 *
 * altera FPGA driver
 *
 * Copyright (C) Altera Corporation 1998-2001
 * Copyright (C) 2010 NetUP Inc.
 * Copyright (C) 2010 Igor M. Liplianin <liplianin@netup.ru>
 */

#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/slab.h>
#समावेश <misc/altera.h>
#समावेश "altera-exprt.h"
#समावेश "altera-jtag.h"

#घोषणा	alt_jtag_io(a, b, c)\
		astate->config->jtag_io(astate->config->dev, a, b, c);

#घोषणा	alt_दो_स्मृति(a)	kzalloc(a, GFP_KERNEL);

/*
 * This काष्ठाure shows, क्रम each JTAG state, which state is reached after
 * a single TCK घड़ी cycle with TMS high or TMS low, respectively.  This
 * describes all possible state transitions in the JTAG state machine.
 */
काष्ठा altera_jtag_machine अणु
	क्रमागत altera_jtag_state पंचांगs_high;
	क्रमागत altera_jtag_state पंचांगs_low;
पूर्ण;

अटल स्थिर काष्ठा altera_jtag_machine altera_transitions[] = अणु
	/* RESET     */	अणु RESET,	IDLE पूर्ण,
	/* IDLE      */	अणु DRSELECT,	IDLE पूर्ण,
	/* DRSELECT  */	अणु IRSELECT,	DRCAPTURE पूर्ण,
	/* DRCAPTURE */	अणु DREXIT1,	DRSHIFT पूर्ण,
	/* DRSHIFT   */	अणु DREXIT1,	DRSHIFT पूर्ण,
	/* DREXIT1   */	अणु DRUPDATE,	DRPAUSE पूर्ण,
	/* DRPAUSE   */	अणु DREXIT2,	DRPAUSE पूर्ण,
	/* DREXIT2   */	अणु DRUPDATE,	DRSHIFT पूर्ण,
	/* DRUPDATE  */	अणु DRSELECT,	IDLE पूर्ण,
	/* IRSELECT  */	अणु RESET,	IRCAPTURE पूर्ण,
	/* IRCAPTURE */	अणु IREXIT1,	IRSHIFT पूर्ण,
	/* IRSHIFT   */	अणु IREXIT1,	IRSHIFT पूर्ण,
	/* IREXIT1   */	अणु IRUPDATE,	IRPAUSE पूर्ण,
	/* IRPAUSE   */	अणु IREXIT2,	IRPAUSE पूर्ण,
	/* IREXIT2   */	अणु IRUPDATE,	IRSHIFT पूर्ण,
	/* IRUPDATE  */	अणु DRSELECT,	IDLE पूर्ण
पूर्ण;

/*
 * This table contains the TMS value to be used to take the NEXT STEP on
 * the path to the desired state.  The array index is the current state,
 * and the bit position is the desired endstate.  To find out which state
 * is used as the पूर्णांकermediate state, look up the TMS value in the
 * altera_transitions[] table.
 */
अटल स्थिर u16 altera_jtag_path_map[16] = अणु
	/* RST	RTI	SDRS	CDR	SDR	E1DR	PDR	E2DR */
	0x0001,	0xFFFD,	0xFE01,	0xFFE7,	0xFFEF,	0xFF0F,	0xFFBF,	0xFFFF,
	/* UDR	SIRS	CIR	SIR	E1IR	PIR	E2IR	UIR */
	0xFEFD,	0x0001,	0xF3FF,	0xF7FF,	0x87FF,	0xDFFF,	0xFFFF,	0x7FFD
पूर्ण;

/* Flag bits क्रम alt_jtag_io() function */
#घोषणा TMS_HIGH   1
#घोषणा TMS_LOW    0
#घोषणा TDI_HIGH   1
#घोषणा TDI_LOW    0
#घोषणा READ_TDO   1
#घोषणा IGNORE_TDO 0

पूर्णांक altera_jinit(काष्ठा altera_state *astate)
अणु
	काष्ठा altera_jtag *js = &astate->js;

	/* initial JTAG state is unknown */
	js->jtag_state = ILLEGAL_JTAG_STATE;

	/* initialize to शेष state */
	js->drstop_state = IDLE;
	js->irstop_state = IDLE;
	js->dr_pre  = 0;
	js->dr_post = 0;
	js->ir_pre  = 0;
	js->ir_post = 0;
	js->dr_length    = 0;
	js->ir_length    = 0;

	js->dr_pre_data  = शून्य;
	js->dr_post_data = शून्य;
	js->ir_pre_data  = शून्य;
	js->ir_post_data = शून्य;
	js->dr_buffer	 = शून्य;
	js->ir_buffer	 = शून्य;

	वापस 0;
पूर्ण

पूर्णांक altera_set_drstop(काष्ठा altera_jtag *js, क्रमागत altera_jtag_state state)
अणु
	js->drstop_state = state;

	वापस 0;
पूर्ण

पूर्णांक altera_set_irstop(काष्ठा altera_jtag *js, क्रमागत altera_jtag_state state)
अणु
	js->irstop_state = state;

	वापस 0;
पूर्ण

पूर्णांक altera_set_dr_pre(काष्ठा altera_jtag *js,
				u32 count, u32 start_index,
				u8 *preamble_data)
अणु
	पूर्णांक status = 0;
	u32 i;
	u32 j;

	अगर (count > js->dr_pre) अणु
		kमुक्त(js->dr_pre_data);
		js->dr_pre_data = (u8 *)alt_दो_स्मृति((count + 7) >> 3);
		अगर (js->dr_pre_data == शून्य)
			status = -ENOMEM;
		अन्यथा
			js->dr_pre = count;
	पूर्ण अन्यथा
		js->dr_pre = count;

	अगर (status == 0) अणु
		क्रम (i = 0; i < count; ++i) अणु
			j = i + start_index;

			अगर (preamble_data == शून्य)
				js->dr_pre_data[i >> 3] |= (1 << (i & 7));
			अन्यथा अणु
				अगर (preamble_data[j >> 3] & (1 << (j & 7)))
					js->dr_pre_data[i >> 3] |=
							(1 << (i & 7));
				अन्यथा
					js->dr_pre_data[i >> 3] &=
							~(u32)(1 << (i & 7));

			पूर्ण
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

पूर्णांक altera_set_ir_pre(काष्ठा altera_jtag *js, u32 count, u32 start_index,
							u8 *preamble_data)
अणु
	पूर्णांक status = 0;
	u32 i;
	u32 j;

	अगर (count > js->ir_pre) अणु
		kमुक्त(js->ir_pre_data);
		js->ir_pre_data = (u8 *)alt_दो_स्मृति((count + 7) >> 3);
		अगर (js->ir_pre_data == शून्य)
			status = -ENOMEM;
		अन्यथा
			js->ir_pre = count;

	पूर्ण अन्यथा
		js->ir_pre = count;

	अगर (status == 0) अणु
		क्रम (i = 0; i < count; ++i) अणु
			j = i + start_index;
			अगर (preamble_data == शून्य)
				js->ir_pre_data[i >> 3] |= (1 << (i & 7));
			अन्यथा अणु
				अगर (preamble_data[j >> 3] & (1 << (j & 7)))
					js->ir_pre_data[i >> 3] |=
							(1 << (i & 7));
				अन्यथा
					js->ir_pre_data[i >> 3] &=
							~(u32)(1 << (i & 7));

			पूर्ण
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

पूर्णांक altera_set_dr_post(काष्ठा altera_jtag *js, u32 count, u32 start_index,
						u8 *postamble_data)
अणु
	पूर्णांक status = 0;
	u32 i;
	u32 j;

	अगर (count > js->dr_post) अणु
		kमुक्त(js->dr_post_data);
		js->dr_post_data = (u8 *)alt_दो_स्मृति((count + 7) >> 3);

		अगर (js->dr_post_data == शून्य)
			status = -ENOMEM;
		अन्यथा
			js->dr_post = count;

	पूर्ण अन्यथा
		js->dr_post = count;

	अगर (status == 0) अणु
		क्रम (i = 0; i < count; ++i) अणु
			j = i + start_index;

			अगर (postamble_data == शून्य)
				js->dr_post_data[i >> 3] |= (1 << (i & 7));
			अन्यथा अणु
				अगर (postamble_data[j >> 3] & (1 << (j & 7)))
					js->dr_post_data[i >> 3] |=
								(1 << (i & 7));
				अन्यथा
					js->dr_post_data[i >> 3] &=
					    ~(u32)(1 << (i & 7));

			पूर्ण
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

पूर्णांक altera_set_ir_post(काष्ठा altera_jtag *js, u32 count, u32 start_index,
						u8 *postamble_data)
अणु
	पूर्णांक status = 0;
	u32 i;
	u32 j;

	अगर (count > js->ir_post) अणु
		kमुक्त(js->ir_post_data);
		js->ir_post_data = (u8 *)alt_दो_स्मृति((count + 7) >> 3);
		अगर (js->ir_post_data == शून्य)
			status = -ENOMEM;
		अन्यथा
			js->ir_post = count;

	पूर्ण अन्यथा
		js->ir_post = count;

	अगर (status != 0)
		वापस status;

	क्रम (i = 0; i < count; ++i) अणु
		j = i + start_index;

		अगर (postamble_data == शून्य)
			js->ir_post_data[i >> 3] |= (1 << (i & 7));
		अन्यथा अणु
			अगर (postamble_data[j >> 3] & (1 << (j & 7)))
				js->ir_post_data[i >> 3] |= (1 << (i & 7));
			अन्यथा
				js->ir_post_data[i >> 3] &=
				    ~(u32)(1 << (i & 7));

		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम altera_jreset_idle(काष्ठा altera_state *astate)
अणु
	काष्ठा altera_jtag *js = &astate->js;
	पूर्णांक i;
	/* Go to Test Logic Reset (no matter what the starting state may be) */
	क्रम (i = 0; i < 5; ++i)
		alt_jtag_io(TMS_HIGH, TDI_LOW, IGNORE_TDO);

	/* Now step to Run Test / Idle */
	alt_jtag_io(TMS_LOW, TDI_LOW, IGNORE_TDO);
	js->jtag_state = IDLE;
पूर्ण

पूर्णांक altera_जाओ_jstate(काष्ठा altera_state *astate,
					क्रमागत altera_jtag_state state)
अणु
	काष्ठा altera_jtag *js = &astate->js;
	पूर्णांक पंचांगs;
	पूर्णांक count = 0;
	पूर्णांक status = 0;

	अगर (js->jtag_state == ILLEGAL_JTAG_STATE)
		/* initialize JTAG chain to known state */
		altera_jreset_idle(astate);

	अगर (js->jtag_state == state) अणु
		/*
		 * We are alपढ़ोy in the desired state.
		 * If it is a stable state, loop here.
		 * Otherwise करो nothing (no घड़ी cycles).
		 */
		अगर ((state == IDLE) || (state == DRSHIFT) ||
			(state == DRPAUSE) || (state == IRSHIFT) ||
				(state == IRPAUSE)) अणु
			alt_jtag_io(TMS_LOW, TDI_LOW, IGNORE_TDO);
		पूर्ण अन्यथा अगर (state == RESET)
			alt_jtag_io(TMS_HIGH, TDI_LOW, IGNORE_TDO);

	पूर्ण अन्यथा अणु
		जबतक ((js->jtag_state != state) && (count < 9)) अणु
			/* Get TMS value to take a step toward desired state */
			पंचांगs = (altera_jtag_path_map[js->jtag_state] &
							(1 << state))
							? TMS_HIGH : TMS_LOW;

			/* Take a step */
			alt_jtag_io(पंचांगs, TDI_LOW, IGNORE_TDO);

			अगर (पंचांगs)
				js->jtag_state =
					altera_transitions[js->jtag_state].पंचांगs_high;
			अन्यथा
				js->jtag_state =
					altera_transitions[js->jtag_state].पंचांगs_low;

			++count;
		पूर्ण
	पूर्ण

	अगर (js->jtag_state != state)
		status = -EREMOTEIO;

	वापस status;
पूर्ण

पूर्णांक altera_रुको_cycles(काष्ठा altera_state *astate,
					s32 cycles,
					क्रमागत altera_jtag_state रुको_state)
अणु
	काष्ठा altera_jtag *js = &astate->js;
	पूर्णांक पंचांगs;
	s32 count;
	पूर्णांक status = 0;

	अगर (js->jtag_state != रुको_state)
		status = altera_जाओ_jstate(astate, रुको_state);

	अगर (status == 0) अणु
		/*
		 * Set TMS high to loop in RESET state
		 * Set TMS low to loop in any other stable state
		 */
		पंचांगs = (रुको_state == RESET) ? TMS_HIGH : TMS_LOW;

		क्रम (count = 0L; count < cycles; count++)
			alt_jtag_io(पंचांगs, TDI_LOW, IGNORE_TDO);

	पूर्ण

	वापस status;
पूर्ण

पूर्णांक altera_रुको_msecs(काष्ठा altera_state *astate,
			s32 microseconds, क्रमागत altera_jtag_state रुको_state)
/*
 * Causes JTAG hardware to sit in the specअगरied stable
 * state क्रम the specअगरied duration of real समय.  If
 * no JTAG operations have been perक्रमmed yet, then only
 * a delay is perक्रमmed.  This permits the WAIT USECS
 * statement to be used in VECTOR programs without causing
 * any JTAG operations.
 * Returns 0 क्रम success, अन्यथा appropriate error code.
 */
अणु
	काष्ठा altera_jtag *js = &astate->js;
	पूर्णांक status = 0;

	अगर ((js->jtag_state != ILLEGAL_JTAG_STATE) &&
	    (js->jtag_state != रुको_state))
		status = altera_जाओ_jstate(astate, रुको_state);

	अगर (status == 0)
		/* Wait क्रम specअगरied समय पूर्णांकerval */
		udelay(microseconds);

	वापस status;
पूर्ण

अटल व्योम altera_concatenate_data(u8 *buffer,
				u8 *preamble_data,
				u32 preamble_count,
				u8 *target_data,
				u32 start_index,
				u32 target_count,
				u8 *postamble_data,
				u32 postamble_count)
/*
 * Copies preamble data, target data, and postamble data
 * पूर्णांकo one buffer क्रम IR or DR scans.
 */
अणु
	u32 i, j, k;

	क्रम (i = 0L; i < preamble_count; ++i) अणु
		अगर (preamble_data[i >> 3L] & (1L << (i & 7L)))
			buffer[i >> 3L] |= (1L << (i & 7L));
		अन्यथा
			buffer[i >> 3L] &= ~(u32)(1L << (i & 7L));

	पूर्ण

	j = start_index;
	k = preamble_count + target_count;
	क्रम (; i < k; ++i, ++j) अणु
		अगर (target_data[j >> 3L] & (1L << (j & 7L)))
			buffer[i >> 3L] |= (1L << (i & 7L));
		अन्यथा
			buffer[i >> 3L] &= ~(u32)(1L << (i & 7L));

	पूर्ण

	j = 0L;
	k = preamble_count + target_count + postamble_count;
	क्रम (; i < k; ++i, ++j) अणु
		अगर (postamble_data[j >> 3L] & (1L << (j & 7L)))
			buffer[i >> 3L] |= (1L << (i & 7L));
		अन्यथा
			buffer[i >> 3L] &= ~(u32)(1L << (i & 7L));

	पूर्ण
पूर्ण

अटल पूर्णांक alt_jtag_drscan(काष्ठा altera_state *astate,
			पूर्णांक start_state,
			पूर्णांक count,
			u8 *tdi,
			u8 *tकरो)
अणु
	पूर्णांक i = 0;
	पूर्णांक tकरो_bit = 0;
	पूर्णांक status = 1;

	/* First go to DRSHIFT state */
	चयन (start_state) अणु
	हाल 0:						/* IDLE */
		alt_jtag_io(1, 0, 0);	/* DRSELECT */
		alt_jtag_io(0, 0, 0);	/* DRCAPTURE */
		alt_jtag_io(0, 0, 0);	/* DRSHIFT */
		अवरोध;

	हाल 1:						/* DRPAUSE */
		alt_jtag_io(1, 0, 0);	/* DREXIT2 */
		alt_jtag_io(1, 0, 0);	/* DRUPDATE */
		alt_jtag_io(1, 0, 0);	/* DRSELECT */
		alt_jtag_io(0, 0, 0);	/* DRCAPTURE */
		alt_jtag_io(0, 0, 0);	/* DRSHIFT */
		अवरोध;

	हाल 2:						/* IRPAUSE */
		alt_jtag_io(1, 0, 0);	/* IREXIT2 */
		alt_jtag_io(1, 0, 0);	/* IRUPDATE */
		alt_jtag_io(1, 0, 0);	/* DRSELECT */
		alt_jtag_io(0, 0, 0);	/* DRCAPTURE */
		alt_jtag_io(0, 0, 0);	/* DRSHIFT */
		अवरोध;

	शेष:
		status = 0;
	पूर्ण

	अगर (status) अणु
		/* loop in the SHIFT-DR state */
		क्रम (i = 0; i < count; i++) अणु
			tकरो_bit = alt_jtag_io(
					(i == count - 1),
					tdi[i >> 3] & (1 << (i & 7)),
					(tकरो != शून्य));

			अगर (tकरो != शून्य) अणु
				अगर (tकरो_bit)
					tकरो[i >> 3] |= (1 << (i & 7));
				अन्यथा
					tकरो[i >> 3] &= ~(u32)(1 << (i & 7));

			पूर्ण
		पूर्ण

		alt_jtag_io(0, 0, 0);	/* DRPAUSE */
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक alt_jtag_irscan(काष्ठा altera_state *astate,
		    पूर्णांक start_state,
		    पूर्णांक count,
		    u8 *tdi,
		    u8 *tकरो)
अणु
	पूर्णांक i = 0;
	पूर्णांक tकरो_bit = 0;
	पूर्णांक status = 1;

	/* First go to IRSHIFT state */
	चयन (start_state) अणु
	हाल 0:						/* IDLE */
		alt_jtag_io(1, 0, 0);	/* DRSELECT */
		alt_jtag_io(1, 0, 0);	/* IRSELECT */
		alt_jtag_io(0, 0, 0);	/* IRCAPTURE */
		alt_jtag_io(0, 0, 0);	/* IRSHIFT */
		अवरोध;

	हाल 1:						/* DRPAUSE */
		alt_jtag_io(1, 0, 0);	/* DREXIT2 */
		alt_jtag_io(1, 0, 0);	/* DRUPDATE */
		alt_jtag_io(1, 0, 0);	/* DRSELECT */
		alt_jtag_io(1, 0, 0);	/* IRSELECT */
		alt_jtag_io(0, 0, 0);	/* IRCAPTURE */
		alt_jtag_io(0, 0, 0);	/* IRSHIFT */
		अवरोध;

	हाल 2:						/* IRPAUSE */
		alt_jtag_io(1, 0, 0);	/* IREXIT2 */
		alt_jtag_io(1, 0, 0);	/* IRUPDATE */
		alt_jtag_io(1, 0, 0);	/* DRSELECT */
		alt_jtag_io(1, 0, 0);	/* IRSELECT */
		alt_jtag_io(0, 0, 0);	/* IRCAPTURE */
		alt_jtag_io(0, 0, 0);	/* IRSHIFT */
		अवरोध;

	शेष:
		status = 0;
	पूर्ण

	अगर (status) अणु
		/* loop in the SHIFT-IR state */
		क्रम (i = 0; i < count; i++) अणु
			tकरो_bit = alt_jtag_io(
				      (i == count - 1),
				      tdi[i >> 3] & (1 << (i & 7)),
				      (tकरो != शून्य));
			अगर (tकरो != शून्य) अणु
				अगर (tकरो_bit)
					tकरो[i >> 3] |= (1 << (i & 7));
				अन्यथा
					tकरो[i >> 3] &= ~(u32)(1 << (i & 7));

			पूर्ण
		पूर्ण

		alt_jtag_io(0, 0, 0);	/* IRPAUSE */
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम altera_extract_target_data(u8 *buffer,
				u8 *target_data,
				u32 start_index,
				u32 preamble_count,
				u32 target_count)
/*
 * Copies target data from scan buffer, filtering out
 * preamble and postamble data.
 */
अणु
	u32 i;
	u32 j;
	u32 k;

	j = preamble_count;
	k = start_index + target_count;
	क्रम (i = start_index; i < k; ++i, ++j) अणु
		अगर (buffer[j >> 3] & (1 << (j & 7)))
			target_data[i >> 3] |= (1 << (i & 7));
		अन्यथा
			target_data[i >> 3] &= ~(u32)(1 << (i & 7));

	पूर्ण
पूर्ण

पूर्णांक altera_irscan(काष्ठा altera_state *astate,
				u32 count,
				u8 *tdi_data,
				u32 start_index)
/* Shअगरts data पूर्णांकo inकाष्ठाion रेजिस्टर */
अणु
	काष्ठा altera_jtag *js = &astate->js;
	पूर्णांक start_code = 0;
	u32 alloc_अक्षरs = 0;
	u32 shअगरt_count = js->ir_pre + count + js->ir_post;
	पूर्णांक status = 0;
	क्रमागत altera_jtag_state start_state = ILLEGAL_JTAG_STATE;

	चयन (js->jtag_state) अणु
	हाल ILLEGAL_JTAG_STATE:
	हाल RESET:
	हाल IDLE:
		start_code = 0;
		start_state = IDLE;
		अवरोध;

	हाल DRSELECT:
	हाल DRCAPTURE:
	हाल DRSHIFT:
	हाल DREXIT1:
	हाल DRPAUSE:
	हाल DREXIT2:
	हाल DRUPDATE:
		start_code = 1;
		start_state = DRPAUSE;
		अवरोध;

	हाल IRSELECT:
	हाल IRCAPTURE:
	हाल IRSHIFT:
	हाल IREXIT1:
	हाल IRPAUSE:
	हाल IREXIT2:
	हाल IRUPDATE:
		start_code = 2;
		start_state = IRPAUSE;
		अवरोध;

	शेष:
		status = -EREMOTEIO;
		अवरोध;
	पूर्ण

	अगर (status == 0)
		अगर (js->jtag_state != start_state)
			status = altera_जाओ_jstate(astate, start_state);

	अगर (status == 0) अणु
		अगर (shअगरt_count > js->ir_length) अणु
			alloc_अक्षरs = (shअगरt_count + 7) >> 3;
			kमुक्त(js->ir_buffer);
			js->ir_buffer = (u8 *)alt_दो_स्मृति(alloc_अक्षरs);
			अगर (js->ir_buffer == शून्य)
				status = -ENOMEM;
			अन्यथा
				js->ir_length = alloc_अक्षरs * 8;

		पूर्ण
	पूर्ण

	अगर (status == 0) अणु
		/*
		 * Copy preamble data, IR data,
		 * and postamble data पूर्णांकo a buffer
		 */
		altera_concatenate_data(js->ir_buffer,
					js->ir_pre_data,
					js->ir_pre,
					tdi_data,
					start_index,
					count,
					js->ir_post_data,
					js->ir_post);
		/* Do the IRSCAN */
		alt_jtag_irscan(astate,
				start_code,
				shअगरt_count,
				js->ir_buffer,
				शून्य);

		/* alt_jtag_irscan() always ends in IRPAUSE state */
		js->jtag_state = IRPAUSE;
	पूर्ण

	अगर (status == 0)
		अगर (js->irstop_state != IRPAUSE)
			status = altera_जाओ_jstate(astate, js->irstop_state);


	वापस status;
पूर्ण

पूर्णांक altera_swap_ir(काष्ठा altera_state *astate,
			    u32 count,
			    u8 *in_data,
			    u32 in_index,
			    u8 *out_data,
			    u32 out_index)
/* Shअगरts data पूर्णांकo inकाष्ठाion रेजिस्टर, capturing output data */
अणु
	काष्ठा altera_jtag *js = &astate->js;
	पूर्णांक start_code = 0;
	u32 alloc_अक्षरs = 0;
	u32 shअगरt_count = js->ir_pre + count + js->ir_post;
	पूर्णांक status = 0;
	क्रमागत altera_jtag_state start_state = ILLEGAL_JTAG_STATE;

	चयन (js->jtag_state) अणु
	हाल ILLEGAL_JTAG_STATE:
	हाल RESET:
	हाल IDLE:
		start_code = 0;
		start_state = IDLE;
		अवरोध;

	हाल DRSELECT:
	हाल DRCAPTURE:
	हाल DRSHIFT:
	हाल DREXIT1:
	हाल DRPAUSE:
	हाल DREXIT2:
	हाल DRUPDATE:
		start_code = 1;
		start_state = DRPAUSE;
		अवरोध;

	हाल IRSELECT:
	हाल IRCAPTURE:
	हाल IRSHIFT:
	हाल IREXIT1:
	हाल IRPAUSE:
	हाल IREXIT2:
	हाल IRUPDATE:
		start_code = 2;
		start_state = IRPAUSE;
		अवरोध;

	शेष:
		status = -EREMOTEIO;
		अवरोध;
	पूर्ण

	अगर (status == 0)
		अगर (js->jtag_state != start_state)
			status = altera_जाओ_jstate(astate, start_state);

	अगर (status == 0) अणु
		अगर (shअगरt_count > js->ir_length) अणु
			alloc_अक्षरs = (shअगरt_count + 7) >> 3;
			kमुक्त(js->ir_buffer);
			js->ir_buffer = (u8 *)alt_दो_स्मृति(alloc_अक्षरs);
			अगर (js->ir_buffer == शून्य)
				status = -ENOMEM;
			अन्यथा
				js->ir_length = alloc_अक्षरs * 8;

		पूर्ण
	पूर्ण

	अगर (status == 0) अणु
		/*
		 * Copy preamble data, IR data,
		 * and postamble data पूर्णांकo a buffer
		 */
		altera_concatenate_data(js->ir_buffer,
					js->ir_pre_data,
					js->ir_pre,
					in_data,
					in_index,
					count,
					js->ir_post_data,
					js->ir_post);

		/* Do the IRSCAN */
		alt_jtag_irscan(astate,
				start_code,
				shअगरt_count,
				js->ir_buffer,
				js->ir_buffer);

		/* alt_jtag_irscan() always ends in IRPAUSE state */
		js->jtag_state = IRPAUSE;
	पूर्ण

	अगर (status == 0)
		अगर (js->irstop_state != IRPAUSE)
			status = altera_जाओ_jstate(astate, js->irstop_state);


	अगर (status == 0)
		/* Now extract the वापसed data from the buffer */
		altera_extract_target_data(js->ir_buffer,
					out_data, out_index,
					js->ir_pre, count);

	वापस status;
पूर्ण

पूर्णांक altera_drscan(काष्ठा altera_state *astate,
				u32 count,
				u8 *tdi_data,
				u32 start_index)
/* Shअगरts data पूर्णांकo data रेजिस्टर (ignoring output data) */
अणु
	काष्ठा altera_jtag *js = &astate->js;
	पूर्णांक start_code = 0;
	u32 alloc_अक्षरs = 0;
	u32 shअगरt_count = js->dr_pre + count + js->dr_post;
	पूर्णांक status = 0;
	क्रमागत altera_jtag_state start_state = ILLEGAL_JTAG_STATE;

	चयन (js->jtag_state) अणु
	हाल ILLEGAL_JTAG_STATE:
	हाल RESET:
	हाल IDLE:
		start_code = 0;
		start_state = IDLE;
		अवरोध;

	हाल DRSELECT:
	हाल DRCAPTURE:
	हाल DRSHIFT:
	हाल DREXIT1:
	हाल DRPAUSE:
	हाल DREXIT2:
	हाल DRUPDATE:
		start_code = 1;
		start_state = DRPAUSE;
		अवरोध;

	हाल IRSELECT:
	हाल IRCAPTURE:
	हाल IRSHIFT:
	हाल IREXIT1:
	हाल IRPAUSE:
	हाल IREXIT2:
	हाल IRUPDATE:
		start_code = 2;
		start_state = IRPAUSE;
		अवरोध;

	शेष:
		status = -EREMOTEIO;
		अवरोध;
	पूर्ण

	अगर (status == 0)
		अगर (js->jtag_state != start_state)
			status = altera_जाओ_jstate(astate, start_state);

	अगर (status == 0) अणु
		अगर (shअगरt_count > js->dr_length) अणु
			alloc_अक्षरs = (shअगरt_count + 7) >> 3;
			kमुक्त(js->dr_buffer);
			js->dr_buffer = (u8 *)alt_दो_स्मृति(alloc_अक्षरs);
			अगर (js->dr_buffer == शून्य)
				status = -ENOMEM;
			अन्यथा
				js->dr_length = alloc_अक्षरs * 8;

		पूर्ण
	पूर्ण

	अगर (status == 0) अणु
		/*
		 * Copy preamble data, DR data,
		 * and postamble data पूर्णांकo a buffer
		 */
		altera_concatenate_data(js->dr_buffer,
					js->dr_pre_data,
					js->dr_pre,
					tdi_data,
					start_index,
					count,
					js->dr_post_data,
					js->dr_post);
		/* Do the DRSCAN */
		alt_jtag_drscan(astate, start_code, shअगरt_count,
				js->dr_buffer, शून्य);
		/* alt_jtag_drscan() always ends in DRPAUSE state */
		js->jtag_state = DRPAUSE;
	पूर्ण

	अगर (status == 0)
		अगर (js->drstop_state != DRPAUSE)
			status = altera_जाओ_jstate(astate, js->drstop_state);

	वापस status;
पूर्ण

पूर्णांक altera_swap_dr(काष्ठा altera_state *astate, u32 count,
				u8 *in_data, u32 in_index,
				u8 *out_data, u32 out_index)
/* Shअगरts data पूर्णांकo data रेजिस्टर, capturing output data */
अणु
	काष्ठा altera_jtag *js = &astate->js;
	पूर्णांक start_code = 0;
	u32 alloc_अक्षरs = 0;
	u32 shअगरt_count = js->dr_pre + count + js->dr_post;
	पूर्णांक status = 0;
	क्रमागत altera_jtag_state start_state = ILLEGAL_JTAG_STATE;

	चयन (js->jtag_state) अणु
	हाल ILLEGAL_JTAG_STATE:
	हाल RESET:
	हाल IDLE:
		start_code = 0;
		start_state = IDLE;
		अवरोध;

	हाल DRSELECT:
	हाल DRCAPTURE:
	हाल DRSHIFT:
	हाल DREXIT1:
	हाल DRPAUSE:
	हाल DREXIT2:
	हाल DRUPDATE:
		start_code = 1;
		start_state = DRPAUSE;
		अवरोध;

	हाल IRSELECT:
	हाल IRCAPTURE:
	हाल IRSHIFT:
	हाल IREXIT1:
	हाल IRPAUSE:
	हाल IREXIT2:
	हाल IRUPDATE:
		start_code = 2;
		start_state = IRPAUSE;
		अवरोध;

	शेष:
		status = -EREMOTEIO;
		अवरोध;
	पूर्ण

	अगर (status == 0)
		अगर (js->jtag_state != start_state)
			status = altera_जाओ_jstate(astate, start_state);

	अगर (status == 0) अणु
		अगर (shअगरt_count > js->dr_length) अणु
			alloc_अक्षरs = (shअगरt_count + 7) >> 3;
			kमुक्त(js->dr_buffer);
			js->dr_buffer = (u8 *)alt_दो_स्मृति(alloc_अक्षरs);

			अगर (js->dr_buffer == शून्य)
				status = -ENOMEM;
			अन्यथा
				js->dr_length = alloc_अक्षरs * 8;

		पूर्ण
	पूर्ण

	अगर (status == 0) अणु
		/*
		 * Copy preamble data, DR data,
		 * and postamble data पूर्णांकo a buffer
		 */
		altera_concatenate_data(js->dr_buffer,
				js->dr_pre_data,
				js->dr_pre,
				in_data,
				in_index,
				count,
				js->dr_post_data,
				js->dr_post);

		/* Do the DRSCAN */
		alt_jtag_drscan(astate,
				start_code,
				shअगरt_count,
				js->dr_buffer,
				js->dr_buffer);

		/* alt_jtag_drscan() always ends in DRPAUSE state */
		js->jtag_state = DRPAUSE;
	पूर्ण

	अगर (status == 0)
		अगर (js->drstop_state != DRPAUSE)
			status = altera_जाओ_jstate(astate, js->drstop_state);

	अगर (status == 0)
		/* Now extract the वापसed data from the buffer */
		altera_extract_target_data(js->dr_buffer,
					out_data,
					out_index,
					js->dr_pre,
					count);

	वापस status;
पूर्ण

व्योम altera_मुक्त_buffers(काष्ठा altera_state *astate)
अणु
	काष्ठा altera_jtag *js = &astate->js;
	/* If the JTAG पूर्णांकerface was used, reset it to TLR */
	अगर (js->jtag_state != ILLEGAL_JTAG_STATE)
		altera_jreset_idle(astate);

	kमुक्त(js->dr_pre_data);
	js->dr_pre_data = शून्य;

	kमुक्त(js->dr_post_data);
	js->dr_post_data = शून्य;

	kमुक्त(js->dr_buffer);
	js->dr_buffer = शून्य;

	kमुक्त(js->ir_pre_data);
	js->ir_pre_data = शून्य;

	kमुक्त(js->ir_post_data);
	js->ir_post_data = शून्य;

	kमुक्त(js->ir_buffer);
	js->ir_buffer = शून्य;
पूर्ण
