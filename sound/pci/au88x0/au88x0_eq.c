<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/***************************************************************************
 *            au88x0_eq.c
 *  Aureal Vortex Hardware EQ control/access.
 *
 *  Sun Jun  8 18:19:19 2003
 *  2003  Manuel Jander (mjander@users.sourceक्रमge.net)
 *  
 *  02 July 2003: First समय something works :)
 *  November 2003: A3D Bypass code completed but untested.
 *
 *  TODO:
 *     - Debug (testing)
 *     - Test peak visualization support.
 *
 ****************************************************************************/

/*
 */

/*
 The Aureal Hardware EQ is found on AU8810 and AU8830 chips only.
 it has 4 inमाला_दो (2 क्रम general mix, 2 क्रम A3D) and 2 outमाला_दो (supposed 
 to be routed to the codec).
*/

#समावेश "au88x0.h"
#समावेश "au88x0_eq.h"
#समावेश "au88x0_eqdata.c"

#घोषणा VORTEX_EQ_BASE	 0x2b000
#घोषणा VORTEX_EQ_DEST   (VORTEX_EQ_BASE + 0x410)
#घोषणा VORTEX_EQ_SOURCE (VORTEX_EQ_BASE + 0x430)
#घोषणा VORTEX_EQ_CTRL   (VORTEX_EQ_BASE + 0x440)

#घोषणा VORTEX_BAND_COEFF_SIZE 0x30

/* CEqHw.s */
अटल व्योम vortex_EqHw_SetTimeConsts(vortex_t * vortex, u16 gain, u16 level)
अणु
	hwग_लिखो(vortex->mmio, 0x2b3c4, gain);
	hwग_लिखो(vortex->mmio, 0x2b3c8, level);
पूर्ण

अटल अंतरभूत u16 sign_invert(u16 a)
अणु
	/* -(-32768) -> -32768 so we करो -(-32768) -> 32767 to make the result positive */
	अगर (a == (u16)-32768)
		वापस 32767;
	अन्यथा
		वापस -a;
पूर्ण

अटल व्योम vortex_EqHw_SetLeftCoefs(vortex_t *vortex, स्थिर u16 coefs[])
अणु
	eqhw_t *eqhw = &(vortex->eq.this04);
	पूर्णांक i = 0, n /*esp2c */;

	क्रम (n = 0; n < eqhw->this04; n++) अणु
		hwग_लिखो(vortex->mmio, 0x2b000 + n * 0x30, coefs[i + 0]);
		hwग_लिखो(vortex->mmio, 0x2b004 + n * 0x30, coefs[i + 1]);

		अगर (eqhw->this08 == 0) अणु
			hwग_लिखो(vortex->mmio, 0x2b008 + n * 0x30, coefs[i + 2]);
			hwग_लिखो(vortex->mmio, 0x2b00c + n * 0x30, coefs[i + 3]);
			hwग_लिखो(vortex->mmio, 0x2b010 + n * 0x30, coefs[i + 4]);
		पूर्ण अन्यथा अणु
			hwग_लिखो(vortex->mmio, 0x2b008 + n * 0x30, sign_invert(coefs[2 + i]));
			hwग_लिखो(vortex->mmio, 0x2b00c + n * 0x30, sign_invert(coefs[3 + i]));
		        hwग_लिखो(vortex->mmio, 0x2b010 + n * 0x30, sign_invert(coefs[4 + i]));
		पूर्ण
		i += 5;
	पूर्ण
पूर्ण

अटल व्योम vortex_EqHw_SetRightCoefs(vortex_t *vortex, स्थिर u16 coefs[])
अणु
	eqhw_t *eqhw = &(vortex->eq.this04);
	पूर्णांक i = 0, n /*esp2c */;

	क्रम (n = 0; n < eqhw->this04; n++) अणु
		hwग_लिखो(vortex->mmio, 0x2b1e0 + n * 0x30, coefs[0 + i]);
		hwग_लिखो(vortex->mmio, 0x2b1e4 + n * 0x30, coefs[1 + i]);

		अगर (eqhw->this08 == 0) अणु
			hwग_लिखो(vortex->mmio, 0x2b1e8 + n * 0x30, coefs[2 + i]);
			hwग_लिखो(vortex->mmio, 0x2b1ec + n * 0x30, coefs[3 + i]);
			hwग_लिखो(vortex->mmio, 0x2b1f0 + n * 0x30, coefs[4 + i]);
		पूर्ण अन्यथा अणु
			hwग_लिखो(vortex->mmio, 0x2b1e8 + n * 0x30, sign_invert(coefs[2 + i]));
			hwग_लिखो(vortex->mmio, 0x2b1ec + n * 0x30, sign_invert(coefs[3 + i]));
			hwग_लिखो(vortex->mmio, 0x2b1f0 + n * 0x30, sign_invert(coefs[4 + i]));
		पूर्ण
		i += 5;
	पूर्ण

पूर्ण

अटल व्योम vortex_EqHw_SetLeftStates(vortex_t *vortex, स्थिर u16 a[], स्थिर u16 b[])
अणु
	eqhw_t *eqhw = &(vortex->eq.this04);
	पूर्णांक i = 0, ebx;

	hwग_लिखो(vortex->mmio, 0x2b3fc, a[0]);
	hwग_लिखो(vortex->mmio, 0x2b400, a[1]);

	क्रम (ebx = 0; ebx < eqhw->this04; ebx++) अणु
		hwग_लिखो(vortex->mmio, 0x2b014 + (i * 0xc), b[i]);
		hwग_लिखो(vortex->mmio, 0x2b018 + (i * 0xc), b[1 + i]);
		hwग_लिखो(vortex->mmio, 0x2b01c + (i * 0xc), b[2 + i]);
		hwग_लिखो(vortex->mmio, 0x2b020 + (i * 0xc), b[3 + i]);
		i += 4;
	पूर्ण
पूर्ण

अटल व्योम vortex_EqHw_SetRightStates(vortex_t *vortex, स्थिर u16 a[], स्थिर u16 b[])
अणु
	eqhw_t *eqhw = &(vortex->eq.this04);
	पूर्णांक i = 0, ebx;

	hwग_लिखो(vortex->mmio, 0x2b404, a[0]);
	hwग_लिखो(vortex->mmio, 0x2b408, a[1]);

	क्रम (ebx = 0; ebx < eqhw->this04; ebx++) अणु
		hwग_लिखो(vortex->mmio, 0x2b1f4 + (i * 0xc), b[i]);
		hwग_लिखो(vortex->mmio, 0x2b1f8 + (i * 0xc), b[1 + i]);
		hwग_लिखो(vortex->mmio, 0x2b1fc + (i * 0xc), b[2 + i]);
		hwग_लिखो(vortex->mmio, 0x2b200 + (i * 0xc), b[3 + i]);
		i += 4;
	पूर्ण
पूर्ण

#अगर 0
अटल व्योम vortex_EqHw_GetTimeConsts(vortex_t * vortex, u16 * a, u16 * b)
अणु
	*a = hwपढ़ो(vortex->mmio, 0x2b3c4);
	*b = hwपढ़ो(vortex->mmio, 0x2b3c8);
पूर्ण

अटल व्योम vortex_EqHw_GetLeftCoefs(vortex_t * vortex, u16 a[])
अणु

पूर्ण

अटल व्योम vortex_EqHw_GetRightCoefs(vortex_t * vortex, u16 a[])
अणु

पूर्ण

अटल व्योम vortex_EqHw_GetLeftStates(vortex_t * vortex, u16 * a, u16 b[])
अणु

पूर्ण

अटल व्योम vortex_EqHw_GetRightStates(vortex_t * vortex, u16 * a, u16 b[])
अणु

पूर्ण

#पूर्ण_अगर
/* Mix Gains */
अटल व्योम vortex_EqHw_SetBypassGain(vortex_t * vortex, u16 a, u16 b)
अणु
	eqhw_t *eqhw = &(vortex->eq.this04);
	अगर (eqhw->this08 == 0) अणु
		hwग_लिखो(vortex->mmio, 0x2b3d4, a);
		hwग_लिखो(vortex->mmio, 0x2b3ec, b);
	पूर्ण अन्यथा अणु
		hwग_लिखो(vortex->mmio, 0x2b3d4, sign_invert(a));
		hwग_लिखो(vortex->mmio, 0x2b3ec, sign_invert(b));
	पूर्ण
पूर्ण

अटल व्योम vortex_EqHw_SetA3DBypassGain(vortex_t * vortex, u16 a, u16 b)
अणु

	hwग_लिखो(vortex->mmio, 0x2b3e0, a);
	hwग_लिखो(vortex->mmio, 0x2b3f8, b);
पूर्ण

#अगर 0
अटल व्योम vortex_EqHw_SetCurrBypassGain(vortex_t * vortex, u16 a, u16 b)
अणु

	hwग_लिखो(vortex->mmio, 0x2b3d0, a);
	hwग_लिखो(vortex->mmio, 0x2b3e8, b);
पूर्ण

अटल व्योम vortex_EqHw_SetCurrA3DBypassGain(vortex_t * vortex, u16 a, u16 b)
अणु

	hwग_लिखो(vortex->mmio, 0x2b3dc, a);
	hwग_लिखो(vortex->mmio, 0x2b3f4, b);
पूर्ण

#पूर्ण_अगर
अटल व्योम
vortex_EqHw_SetLeftGainsSingleTarget(vortex_t * vortex, u16 index, u16 b)
अणु
	hwग_लिखो(vortex->mmio, 0x2b02c + (index * 0x30), b);
पूर्ण

अटल व्योम
vortex_EqHw_SetRightGainsSingleTarget(vortex_t * vortex, u16 index, u16 b)
अणु
	hwग_लिखो(vortex->mmio, 0x2b20c + (index * 0x30), b);
पूर्ण

अटल व्योम vortex_EqHw_SetLeftGainsTarget(vortex_t *vortex, स्थिर u16 a[])
अणु
	eqhw_t *eqhw = &(vortex->eq.this04);
	पूर्णांक ebx;

	क्रम (ebx = 0; ebx < eqhw->this04; ebx++) अणु
		hwग_लिखो(vortex->mmio, 0x2b02c + ebx * 0x30, a[ebx]);
	पूर्ण
पूर्ण

अटल व्योम vortex_EqHw_SetRightGainsTarget(vortex_t *vortex, स्थिर u16 a[])
अणु
	eqhw_t *eqhw = &(vortex->eq.this04);
	पूर्णांक ebx;

	क्रम (ebx = 0; ebx < eqhw->this04; ebx++) अणु
		hwग_लिखो(vortex->mmio, 0x2b20c + ebx * 0x30, a[ebx]);
	पूर्ण
पूर्ण

अटल व्योम vortex_EqHw_SetLeftGainsCurrent(vortex_t *vortex, स्थिर u16 a[])
अणु
	eqhw_t *eqhw = &(vortex->eq.this04);
	पूर्णांक ebx;

	क्रम (ebx = 0; ebx < eqhw->this04; ebx++) अणु
		hwग_लिखो(vortex->mmio, 0x2b028 + ebx * 0x30, a[ebx]);
	पूर्ण
पूर्ण

अटल व्योम vortex_EqHw_SetRightGainsCurrent(vortex_t *vortex, स्थिर u16 a[])
अणु
	eqhw_t *eqhw = &(vortex->eq.this04);
	पूर्णांक ebx;

	क्रम (ebx = 0; ebx < eqhw->this04; ebx++) अणु
		hwग_लिखो(vortex->mmio, 0x2b208 + ebx * 0x30, a[ebx]);
	पूर्ण
पूर्ण

#अगर 0
अटल व्योम vortex_EqHw_GetLeftGainsTarget(vortex_t * vortex, u16 a[])
अणु
	eqhw_t *eqhw = &(vortex->eq.this04);
	पूर्णांक ebx = 0;

	अगर (eqhw->this04 < 0)
		वापस;

	करो अणु
		a[ebx] = hwपढ़ो(vortex->mmio, 0x2b02c + ebx * 0x30);
		ebx++;
	पूर्ण
	जबतक (ebx < eqhw->this04);
पूर्ण

अटल व्योम vortex_EqHw_GetRightGainsTarget(vortex_t * vortex, u16 a[])
अणु
	eqhw_t *eqhw = &(vortex->eq.this04);
	पूर्णांक ebx = 0;

	अगर (eqhw->this04 < 0)
		वापस;

	करो अणु
		a[ebx] = hwपढ़ो(vortex->mmio, 0x2b20c + ebx * 0x30);
		ebx++;
	पूर्ण
	जबतक (ebx < eqhw->this04);
पूर्ण

अटल व्योम vortex_EqHw_GetLeftGainsCurrent(vortex_t * vortex, u16 a[])
अणु
	eqhw_t *eqhw = &(vortex->eq.this04);
	पूर्णांक ebx = 0;

	अगर (eqhw->this04 < 0)
		वापस;

	करो अणु
		a[ebx] = hwपढ़ो(vortex->mmio, 0x2b028 + ebx * 0x30);
		ebx++;
	पूर्ण
	जबतक (ebx < eqhw->this04);
पूर्ण

अटल व्योम vortex_EqHw_GetRightGainsCurrent(vortex_t * vortex, u16 a[])
अणु
	eqhw_t *eqhw = &(vortex->eq.this04);
	पूर्णांक ebx = 0;

	अगर (eqhw->this04 < 0)
		वापस;

	करो अणु
		a[ebx] = hwपढ़ो(vortex->mmio, 0x2b208 + ebx * 0x30);
		ebx++;
	पूर्ण
	जबतक (ebx < eqhw->this04);
पूर्ण

#पूर्ण_अगर
/* EQ band levels settings */
अटल व्योम vortex_EqHw_SetLevels(vortex_t *vortex, स्थिर u16 peaks[])
अणु
	eqhw_t *eqhw = &(vortex->eq.this04);
	पूर्णांक i;

	/* set left peaks */
	क्रम (i = 0; i < eqhw->this04; i++) अणु
		hwग_लिखो(vortex->mmio, 0x2b024 + i * VORTEX_BAND_COEFF_SIZE, peaks[i]);
	पूर्ण

	hwग_लिखो(vortex->mmio, 0x2b3cc, peaks[eqhw->this04]);
	hwग_लिखो(vortex->mmio, 0x2b3d8, peaks[eqhw->this04 + 1]);

	/* set right peaks */
	क्रम (i = 0; i < eqhw->this04; i++) अणु
		hwग_लिखो(vortex->mmio, 0x2b204 + i * VORTEX_BAND_COEFF_SIZE,
			peaks[i + (eqhw->this04 + 2)]);
	पूर्ण

	hwग_लिखो(vortex->mmio, 0x2b3e4, peaks[2 + (eqhw->this04 * 2)]);
	hwग_लिखो(vortex->mmio, 0x2b3f0, peaks[3 + (eqhw->this04 * 2)]);
पूर्ण

#अगर 0
अटल व्योम vortex_EqHw_GetLevels(vortex_t * vortex, u16 a[])
अणु
	eqhw_t *eqhw = &(vortex->eq.this04);
	पूर्णांक ebx;

	अगर (eqhw->this04 < 0)
		वापस;

	ebx = 0;
	करो अणु
		a[ebx] = hwपढ़ो(vortex->mmio, 0x2b024 + ebx * 0x30);
		ebx++;
	पूर्ण
	जबतक (ebx < eqhw->this04);

	a[eqhw->this04] = hwपढ़ो(vortex->mmio, 0x2b3cc);
	a[eqhw->this04 + 1] = hwपढ़ो(vortex->mmio, 0x2b3d8);

	ebx = 0;
	करो अणु
		a[ebx + (eqhw->this04 + 2)] =
		    hwपढ़ो(vortex->mmio, 0x2b204 + ebx * 0x30);
		ebx++;
	पूर्ण
	जबतक (ebx < eqhw->this04);

	a[2 + (eqhw->this04 * 2)] = hwपढ़ो(vortex->mmio, 0x2b3e4);
	a[3 + (eqhw->this04 * 2)] = hwपढ़ो(vortex->mmio, 0x2b3f0);
पूर्ण

#पूर्ण_अगर
/* Global Control */
अटल व्योम vortex_EqHw_SetControlReg(vortex_t * vortex, u32 reg)
अणु
	hwग_लिखो(vortex->mmio, 0x2b440, reg);
पूर्ण

अटल व्योम vortex_EqHw_SetSampleRate(vortex_t * vortex, u32 sr)
अणु
	hwग_लिखो(vortex->mmio, 0x2b440, ((sr & 0x1f) << 3) | 0xb800);
पूर्ण

#अगर 0
अटल व्योम vortex_EqHw_GetControlReg(vortex_t * vortex, u32 *reg)
अणु
	*reg = hwपढ़ो(vortex->mmio, 0x2b440);
पूर्ण

अटल व्योम vortex_EqHw_GetSampleRate(vortex_t * vortex, u32 *sr)
अणु
	*sr = (hwपढ़ो(vortex->mmio, 0x2b440) >> 3) & 0x1f;
पूर्ण

#पूर्ण_अगर
अटल व्योम vortex_EqHw_Enable(vortex_t * vortex)
अणु
	hwग_लिखो(vortex->mmio, VORTEX_EQ_CTRL, 0xf001);
पूर्ण

अटल व्योम vortex_EqHw_Disable(vortex_t * vortex)
अणु
	hwग_लिखो(vortex->mmio, VORTEX_EQ_CTRL, 0xf000);
पूर्ण

/* Reset (zero) buffers */
अटल व्योम vortex_EqHw_ZeroIO(vortex_t * vortex)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < 0x8; i++)
		hwग_लिखो(vortex->mmio, VORTEX_EQ_DEST + (i << 2), 0x0);
	क्रम (i = 0; i < 0x4; i++)
		hwग_लिखो(vortex->mmio, VORTEX_EQ_SOURCE + (i << 2), 0x0);
पूर्ण

अटल व्योम vortex_EqHw_ZeroA3DIO(vortex_t * vortex)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < 0x4; i++)
		hwग_लिखो(vortex->mmio, VORTEX_EQ_DEST + (i << 2), 0x0);
पूर्ण

अटल व्योम vortex_EqHw_ZeroState(vortex_t * vortex)
अणु

	vortex_EqHw_SetControlReg(vortex, 0);
	vortex_EqHw_ZeroIO(vortex);
	hwग_लिखो(vortex->mmio, 0x2b3c0, 0);

	vortex_EqHw_SetTimeConsts(vortex, 0, 0);

	vortex_EqHw_SetLeftCoefs(vortex, asEqCoefsZeros);
	vortex_EqHw_SetRightCoefs(vortex, asEqCoefsZeros);

	vortex_EqHw_SetLeftGainsCurrent(vortex, eq_gains_zero);
	vortex_EqHw_SetRightGainsCurrent(vortex, eq_gains_zero);
	vortex_EqHw_SetLeftGainsTarget(vortex, eq_gains_zero);
	vortex_EqHw_SetRightGainsTarget(vortex, eq_gains_zero);

	vortex_EqHw_SetBypassGain(vortex, 0, 0);
	//vortex_EqHw_SetCurrBypassGain(vortex, 0, 0);
	vortex_EqHw_SetA3DBypassGain(vortex, 0, 0);
	//vortex_EqHw_SetCurrA3DBypassGain(vortex, 0, 0);
	vortex_EqHw_SetLeftStates(vortex, eq_states_zero, asEqOutStateZeros);
	vortex_EqHw_SetRightStates(vortex, eq_states_zero, asEqOutStateZeros);
	vortex_EqHw_SetLevels(vortex, (u16 *) eq_levels);
पूर्ण

/* Program coeficients as pass through */
अटल व्योम vortex_EqHw_ProgramPipe(vortex_t * vortex)
अणु
	vortex_EqHw_SetTimeConsts(vortex, 0, 0);

	vortex_EqHw_SetLeftCoefs(vortex, asEqCoefsPipes);
	vortex_EqHw_SetRightCoefs(vortex, asEqCoefsPipes);

	vortex_EqHw_SetLeftGainsCurrent(vortex, eq_gains_current);
	vortex_EqHw_SetRightGainsCurrent(vortex, eq_gains_current);
	vortex_EqHw_SetLeftGainsTarget(vortex, eq_gains_current);
	vortex_EqHw_SetRightGainsTarget(vortex, eq_gains_current);
पूर्ण

/* Program EQ block as 10 band Equalizer */
अटल व्योम
vortex_EqHw_Program10Band(vortex_t * vortex, auxxEqCoeffSet_t * coefset)
अणु

	vortex_EqHw_SetTimeConsts(vortex, 0xc, 0x7fe0);

	vortex_EqHw_SetLeftCoefs(vortex, coefset->LeftCoefs);
	vortex_EqHw_SetRightCoefs(vortex, coefset->RightCoefs);

	vortex_EqHw_SetLeftGainsCurrent(vortex, coefset->LeftGains);

	vortex_EqHw_SetRightGainsTarget(vortex, coefset->RightGains);
	vortex_EqHw_SetLeftGainsTarget(vortex, coefset->LeftGains);

	vortex_EqHw_SetRightGainsCurrent(vortex, coefset->RightGains);
पूर्ण

/* Read all EQ peaks. (think VU meter) */
अटल व्योम vortex_EqHw_GetTenBandLevels(vortex_t * vortex, u16 peaks[])
अणु
	eqhw_t *eqhw = &(vortex->eq.this04);
	पूर्णांक i;

	अगर (eqhw->this04 <= 0)
		वापस;

	क्रम (i = 0; i < eqhw->this04; i++)
		peaks[i] = hwपढ़ो(vortex->mmio, 0x2B024 + i * 0x30);
	क्रम (i = 0; i < eqhw->this04; i++)
		peaks[i + eqhw->this04] =
		    hwपढ़ो(vortex->mmio, 0x2B204 + i * 0x30);
पूर्ण

/* CEqlzr.s */

अटल पूर्णांक vortex_Eqlzr_GetLeftGain(vortex_t * vortex, u16 index, u16 * gain)
अणु
	eqlzr_t *eq = &(vortex->eq);

	अगर (eq->this28) अणु
		*gain = eq->this130[index];
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल व्योम vortex_Eqlzr_SetLeftGain(vortex_t * vortex, u16 index, u16 gain)
अणु
	eqlzr_t *eq = &(vortex->eq);

	अगर (eq->this28 == 0)
		वापस;

	eq->this130[index] = gain;
	अगर (eq->this54)
		वापस;

	vortex_EqHw_SetLeftGainsSingleTarget(vortex, index, gain);
पूर्ण

अटल पूर्णांक vortex_Eqlzr_GetRightGain(vortex_t * vortex, u16 index, u16 * gain)
अणु
	eqlzr_t *eq = &(vortex->eq);

	अगर (eq->this28) अणु
		*gain = eq->this130[index + eq->this10];
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल व्योम vortex_Eqlzr_SetRightGain(vortex_t * vortex, u16 index, u16 gain)
अणु
	eqlzr_t *eq = &(vortex->eq);

	अगर (eq->this28 == 0)
		वापस;

	eq->this130[index + eq->this10] = gain;
	अगर (eq->this54)
		वापस;

	vortex_EqHw_SetRightGainsSingleTarget(vortex, index, gain);
पूर्ण

#अगर 0
अटल पूर्णांक
vortex_Eqlzr_GetAllBands(vortex_t * vortex, u16 * gains, s32 *cnt)
अणु
	eqlzr_t *eq = &(vortex->eq);
	पूर्णांक si = 0;

	अगर (eq->this10 == 0)
		वापस 1;

	अणु
		अगर (vortex_Eqlzr_GetLeftGain(vortex, si, &gains[si]))
			वापस 1;
		अगर (vortex_Eqlzr_GetRightGain
		    (vortex, si, &gains[si + eq->this10]))
			वापस 1;
		si++;
	पूर्ण
	जबतक (eq->this10 > si) ;
	*cnt = si * 2;
	वापस 0;
पूर्ण
#पूर्ण_अगर
अटल पूर्णांक vortex_Eqlzr_SetAllBandsFromActiveCoeffSet(vortex_t * vortex)
अणु
	eqlzr_t *eq = &(vortex->eq);

	vortex_EqHw_SetLeftGainsTarget(vortex, eq->this130);
	vortex_EqHw_SetRightGainsTarget(vortex, &(eq->this130[eq->this10]));

	वापस 0;
पूर्ण

अटल पूर्णांक
vortex_Eqlzr_SetAllBands(vortex_t *vortex, स्थिर u16 gains[], s32 count)
अणु
	eqlzr_t *eq = &(vortex->eq);
	पूर्णांक i;

	अगर (((eq->this10) * 2 != count) || (eq->this28 == 0))
		वापस 1;

	क्रम (i = 0; i < count; i++) अणु
		eq->this130[i] = gains[i];
	पूर्ण
	
	अगर (eq->this54)
		वापस 0;
	वापस vortex_Eqlzr_SetAllBandsFromActiveCoeffSet(vortex);
पूर्ण

अटल व्योम
vortex_Eqlzr_SetA3dBypassGain(vortex_t * vortex, u32 a, u32 b)
अणु
	eqlzr_t *eq = &(vortex->eq);
	u32 eax, ebx;

	eq->this58 = a;
	eq->this5c = b;
	अगर (eq->this54)
		eax = eq->this0e;
	अन्यथा
		eax = eq->this0a;
	ebx = (eax * eq->this58) >> 0x10;
	eax = (eax * eq->this5c) >> 0x10;
	vortex_EqHw_SetA3DBypassGain(vortex, ebx, eax);
पूर्ण

अटल व्योम vortex_Eqlzr_ProgramA3dBypassGain(vortex_t * vortex)
अणु
	eqlzr_t *eq = &(vortex->eq);
	u32 eax, ebx;

	अगर (eq->this54)
		eax = eq->this0e;
	अन्यथा
		eax = eq->this0a;
	ebx = (eax * eq->this58) >> 0x10;
	eax = (eax * eq->this5c) >> 0x10;
	vortex_EqHw_SetA3DBypassGain(vortex, ebx, eax);
पूर्ण

अटल व्योम vortex_Eqlzr_ShutDownA3d(vortex_t * vortex)
अणु
	अगर (vortex != शून्य)
		vortex_EqHw_ZeroA3DIO(vortex);
पूर्ण

अटल व्योम vortex_Eqlzr_SetBypass(vortex_t * vortex, u32 bp)
अणु
	eqlzr_t *eq = &(vortex->eq);
	
	अगर ((eq->this28) && (bp == 0)) अणु
		/* EQ enabled */
		vortex_Eqlzr_SetAllBandsFromActiveCoeffSet(vortex);
		vortex_EqHw_SetBypassGain(vortex, eq->this08, eq->this08);
	पूर्ण अन्यथा अणु
		/* EQ disabled. */
		vortex_EqHw_SetLeftGainsTarget(vortex, eq->this14_array);
		vortex_EqHw_SetRightGainsTarget(vortex, eq->this14_array);
		vortex_EqHw_SetBypassGain(vortex, eq->this0c, eq->this0c);
	पूर्ण
	vortex_Eqlzr_ProgramA3dBypassGain(vortex);
पूर्ण

अटल व्योम vortex_Eqlzr_ReadAndSetActiveCoefSet(vortex_t * vortex)
अणु
	eqlzr_t *eq = &(vortex->eq);

	/* Set EQ BiQuad filter coeficients */
	स_नकल(&(eq->coefset), &asEqCoefsNormal, माप(auxxEqCoeffSet_t));
	/* Set EQ Band gain levels and dump पूर्णांकo hardware रेजिस्टरs. */
	vortex_Eqlzr_SetAllBands(vortex, eq_gains_normal, eq->this10 * 2);
पूर्ण

अटल पूर्णांक vortex_Eqlzr_GetAllPeaks(vortex_t * vortex, u16 * peaks, पूर्णांक *count)
अणु
	eqlzr_t *eq = &(vortex->eq);

	अगर (eq->this10 == 0)
		वापस 1;
	*count = eq->this10 * 2;
	vortex_EqHw_GetTenBandLevels(vortex, peaks);
	वापस 0;
पूर्ण

#अगर 0
अटल auxxEqCoeffSet_t *vortex_Eqlzr_GetActiveCoefSet(vortex_t * vortex)
अणु
	eqlzr_t *eq = &(vortex->eq);

	वापस (&(eq->coefset));
पूर्ण
#पूर्ण_अगर
अटल व्योम vortex_Eqlzr_init(vortex_t * vortex)
अणु
	eqlzr_t *eq = &(vortex->eq);

	/* Object स्थिरructor */
	//eq->this04 = 0;
	eq->this08 = 0;		/* Bypass gain with EQ in use. */
	eq->this0a = 0x5999;
	eq->this0c = 0x5999;	/* Bypass gain with EQ disabled. */
	eq->this0e = 0x5999;

	eq->this10 = 0xa;	/* 10 eq frequency bands. */
	eq->this04.this04 = eq->this10;
	eq->this28 = 0x1;	/* अगर 1 => Allow पढ़ो access to this130 (gains) */
	eq->this54 = 0x0;	/* अगर 1 => Dont Allow access to hardware (gains) */
	eq->this58 = 0xffff;
	eq->this5c = 0xffff;

	/* Set gains. */
	स_रखो(eq->this14_array, 0, माप(eq->this14_array));

	/* Actual init. */
	vortex_EqHw_ZeroState(vortex);
	vortex_EqHw_SetSampleRate(vortex, 0x11);
	vortex_Eqlzr_ReadAndSetActiveCoefSet(vortex);

	vortex_EqHw_Program10Band(vortex, &(eq->coefset));
	vortex_Eqlzr_SetBypass(vortex, eq->this54);
	vortex_Eqlzr_SetA3dBypassGain(vortex, 0, 0);
	vortex_EqHw_Enable(vortex);
पूर्ण

अटल व्योम vortex_Eqlzr_shutकरोwn(vortex_t * vortex)
अणु
	vortex_Eqlzr_ShutDownA3d(vortex);
	vortex_EqHw_ProgramPipe(vortex);
	vortex_EqHw_Disable(vortex);
पूर्ण

/* ALSA पूर्णांकerface */

/* Control पूर्णांकerface */
#घोषणा snd_vortex_eqtoggle_info	snd_ctl_boolean_mono_info

अटल पूर्णांक
snd_vortex_eqtoggle_get(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	vortex_t *vortex = snd_kcontrol_chip(kcontrol);
	eqlzr_t *eq = &(vortex->eq);
	//पूर्णांक i = kcontrol->निजी_value;

	ucontrol->value.पूर्णांकeger.value[0] = eq->this54 ? 0 : 1;

	वापस 0;
पूर्ण

अटल पूर्णांक
snd_vortex_eqtoggle_put(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	vortex_t *vortex = snd_kcontrol_chip(kcontrol);
	eqlzr_t *eq = &(vortex->eq);
	//पूर्णांक i = kcontrol->निजी_value;

	eq->this54 = ucontrol->value.पूर्णांकeger.value[0] ? 0 : 1;
	vortex_Eqlzr_SetBypass(vortex, eq->this54);

	वापस 1;		/* Allways changes */
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new vortex_eqtoggle_kcontrol = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "EQ Enable",
	.index = 0,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.निजी_value = 0,
	.info = snd_vortex_eqtoggle_info,
	.get = snd_vortex_eqtoggle_get,
	.put = snd_vortex_eqtoggle_put
पूर्ण;

अटल पूर्णांक
snd_vortex_eq_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0x0000;
	uinfo->value.पूर्णांकeger.max = 0x7fff;
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_vortex_eq_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	vortex_t *vortex = snd_kcontrol_chip(kcontrol);
	पूर्णांक i = kcontrol->निजी_value;
	u16 gainL = 0, gainR = 0;

	vortex_Eqlzr_GetLeftGain(vortex, i, &gainL);
	vortex_Eqlzr_GetRightGain(vortex, i, &gainR);
	ucontrol->value.पूर्णांकeger.value[0] = gainL;
	ucontrol->value.पूर्णांकeger.value[1] = gainR;
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_vortex_eq_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	vortex_t *vortex = snd_kcontrol_chip(kcontrol);
	पूर्णांक changed = 0, i = kcontrol->निजी_value;
	u16 gainL = 0, gainR = 0;

	vortex_Eqlzr_GetLeftGain(vortex, i, &gainL);
	vortex_Eqlzr_GetRightGain(vortex, i, &gainR);

	अगर (gainL != ucontrol->value.पूर्णांकeger.value[0]) अणु
		vortex_Eqlzr_SetLeftGain(vortex, i,
					 ucontrol->value.पूर्णांकeger.value[0]);
		changed = 1;
	पूर्ण
	अगर (gainR != ucontrol->value.पूर्णांकeger.value[1]) अणु
		vortex_Eqlzr_SetRightGain(vortex, i,
					  ucontrol->value.पूर्णांकeger.value[1]);
		changed = 1;
	पूर्ण
	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new vortex_eq_kcontrol = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "                        .",
	.index = 0,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.निजी_value = 0,
	.info = snd_vortex_eq_info,
	.get = snd_vortex_eq_get,
	.put = snd_vortex_eq_put
पूर्ण;

अटल पूर्णांक
snd_vortex_peaks_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 20;
	uinfo->value.पूर्णांकeger.min = 0x0000;
	uinfo->value.पूर्णांकeger.max = 0x7fff;
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_vortex_peaks_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	vortex_t *vortex = snd_kcontrol_chip(kcontrol);
	पूर्णांक i, count = 0;
	u16 peaks[20];

	vortex_Eqlzr_GetAllPeaks(vortex, peaks, &count);
	अगर (count != 20) अणु
		dev_err(vortex->card->dev,
			"peak count error 20 != %d\n", count);
		वापस -1;
	पूर्ण
	क्रम (i = 0; i < 20; i++)
		ucontrol->value.पूर्णांकeger.value[i] = peaks[i];

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new vortex_levels_kcontrol = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "EQ Peaks",
	.access = SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info = snd_vortex_peaks_info,
	.get = snd_vortex_peaks_get,
पूर्ण;

/* EQ band gain labels. */
अटल स्थिर अक्षर * स्थिर EqBandLabels[10] = अणु
	"EQ0 31Hz\0",
	"EQ1 63Hz\0",
	"EQ2 125Hz\0",
	"EQ3 250Hz\0",
	"EQ4 500Hz\0",
	"EQ5 1KHz\0",
	"EQ6 2KHz\0",
	"EQ7 4KHz\0",
	"EQ8 8KHz\0",
	"EQ9 16KHz\0",
पूर्ण;

/* ALSA driver entry poपूर्णांकs. Init and निकास. */
अटल पूर्णांक vortex_eq_init(vortex_t *vortex)
अणु
	काष्ठा snd_kcontrol *kcontrol;
	पूर्णांक err, i;

	vortex_Eqlzr_init(vortex);

	अगर ((kcontrol =
	     snd_ctl_new1(&vortex_eqtoggle_kcontrol, vortex)) == शून्य)
		वापस -ENOMEM;
	kcontrol->निजी_value = 0;
	अगर ((err = snd_ctl_add(vortex->card, kcontrol)) < 0)
		वापस err;

	/* EQ gain controls */
	क्रम (i = 0; i < 10; i++) अणु
		अगर ((kcontrol =
		     snd_ctl_new1(&vortex_eq_kcontrol, vortex)) == शून्य)
			वापस -ENOMEM;
		snम_लिखो(kcontrol->id.name, माप(kcontrol->id.name),
			"%s Playback Volume", EqBandLabels[i]);
		kcontrol->निजी_value = i;
		अगर ((err = snd_ctl_add(vortex->card, kcontrol)) < 0)
			वापस err;
		//vortex->eqctrl[i] = kcontrol;
	पूर्ण
	/* EQ band levels */
	अगर ((kcontrol = snd_ctl_new1(&vortex_levels_kcontrol, vortex)) == शून्य)
		वापस -ENOMEM;
	अगर ((err = snd_ctl_add(vortex->card, kcontrol)) < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक vortex_eq_मुक्त(vortex_t * vortex)
अणु
	/*
	   //FIXME: segfault because vortex->eqctrl[i] == 4
	   पूर्णांक i;
	   क्रम (i=0; i<10; i++) अणु
	   अगर (vortex->eqctrl[i])
	   snd_ctl_हटाओ(vortex->card, vortex->eqctrl[i]);
	   पूर्ण
	 */
	vortex_Eqlzr_shutकरोwn(vortex);
	वापस 0;
पूर्ण

/* End */
