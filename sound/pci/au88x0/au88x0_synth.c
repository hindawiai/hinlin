<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 */

/*
 * Someday its supposed to make use of the WT DMA engine
 * क्रम a Wavetable synthesizer.
 */

#समावेश "au88x0.h"
#समावेश "au88x0_wt.h"

अटल व्योम vortex_fअगरo_setwtvalid(vortex_t * vortex, पूर्णांक fअगरo, पूर्णांक en);
अटल व्योम vortex_connection_adb_mixin(vortex_t * vortex, पूर्णांक en,
					अचिन्हित अक्षर channel,
					अचिन्हित अक्षर source,
					अचिन्हित अक्षर mixin);
अटल व्योम vortex_connection_mixin_mix(vortex_t * vortex, पूर्णांक en,
					अचिन्हित अक्षर mixin,
					अचिन्हित अक्षर mix, पूर्णांक a);
अटल व्योम vortex_fअगरo_wtinitialize(vortex_t * vortex, पूर्णांक fअगरo, पूर्णांक j);
अटल पूर्णांक vortex_wt_SetReg(vortex_t * vortex, अचिन्हित अक्षर reg, पूर्णांक wt,
			    u32 val);

/* WT */

/* Put 2 WT channels together क्रम one stereo पूर्णांकerlaced channel. */
अटल व्योम vortex_wt_setstereo(vortex_t * vortex, u32 wt, u32 stereo)
अणु
	पूर्णांक temp;

	//temp = hwपढ़ो(vortex->mmio, 0x80 + ((wt >> 0x5)<< 0xf) + (((wt & 0x1f) >> 1) << 2));
	temp = hwपढ़ो(vortex->mmio, WT_STEREO(wt));
	temp = (temp & 0xfe) | (stereo & 1);
	//hwग_लिखो(vortex->mmio, 0x80 + ((wt >> 0x5)<< 0xf) + (((wt & 0x1f) >> 1) << 2), temp);
	hwग_लिखो(vortex->mmio, WT_STEREO(wt), temp);
पूर्ण

/* Join to mixकरोwn route. */
अटल व्योम vortex_wt_setdsout(vortex_t * vortex, u32 wt, पूर्णांक en)
अणु
	पूर्णांक temp;

	/* There is one DSREG रेजिस्टर क्रम each bank (32 voices each). */
	temp = hwपढ़ो(vortex->mmio, WT_DSREG((wt >= 0x20) ? 1 : 0));
	अगर (en)
		temp |= (1 << (wt & 0x1f));
	अन्यथा
		temp &= ~(1 << (wt & 0x1f));
	hwग_लिखो(vortex->mmio, WT_DSREG((wt >= 0x20) ? 1 : 0), temp);
पूर्ण

/* Setup WT route. */
अटल पूर्णांक vortex_wt_allocroute(vortex_t * vortex, पूर्णांक wt, पूर्णांक nr_ch)
अणु
	wt_voice_t *voice = &(vortex->wt_voice[wt]);
	पूर्णांक temp;

	//FIXME: WT audio routing.
	अगर (nr_ch) अणु
		vortex_fअगरo_wtinitialize(vortex, wt, 1);
		vortex_fअगरo_setwtvalid(vortex, wt, 1);
		vortex_wt_setstereo(vortex, wt, nr_ch - 1);
	पूर्ण अन्यथा
		vortex_fअगरo_setwtvalid(vortex, wt, 0);
	
	/* Set mixकरोwn mode. */
	vortex_wt_setdsout(vortex, wt, 1);
	/* Set other parameter रेजिस्टरs. */
	hwग_लिखो(vortex->mmio, WT_SRAMP(0), 0x880000);
	//hwग_लिखो(vortex->mmio, WT_GMODE(0), 0xffffffff);
#अगर_घोषित CHIP_AU8830
	hwग_लिखो(vortex->mmio, WT_SRAMP(1), 0x880000);
	//hwग_लिखो(vortex->mmio, WT_GMODE(1), 0xffffffff);
#पूर्ण_अगर
	hwग_लिखो(vortex->mmio, WT_PARM(wt, 0), 0);
	hwग_लिखो(vortex->mmio, WT_PARM(wt, 1), 0);
	hwग_लिखो(vortex->mmio, WT_PARM(wt, 2), 0);

	temp = hwपढ़ो(vortex->mmio, WT_PARM(wt, 3));
	dev_dbg(vortex->card->dev, "WT PARM3: %x\n", temp);
	//hwग_लिखो(vortex->mmio, WT_PARM(wt, 3), temp);

	hwग_लिखो(vortex->mmio, WT_DELAY(wt, 0), 0);
	hwग_लिखो(vortex->mmio, WT_DELAY(wt, 1), 0);
	hwग_लिखो(vortex->mmio, WT_DELAY(wt, 2), 0);
	hwग_लिखो(vortex->mmio, WT_DELAY(wt, 3), 0);

	dev_dbg(vortex->card->dev, "WT GMODE: %x\n",
		hwपढ़ो(vortex->mmio, WT_GMODE(wt)));

	hwग_लिखो(vortex->mmio, WT_PARM(wt, 2), 0xffffffff);
	hwग_लिखो(vortex->mmio, WT_PARM(wt, 3), 0xcff1c810);

	voice->parm0 = voice->parm1 = 0xcfb23e2f;
	hwग_लिखो(vortex->mmio, WT_PARM(wt, 0), voice->parm0);
	hwग_लिखो(vortex->mmio, WT_PARM(wt, 1), voice->parm1);
	dev_dbg(vortex->card->dev, "WT GMODE 2 : %x\n",
		hwपढ़ो(vortex->mmio, WT_GMODE(wt)));
	वापस 0;
पूर्ण


अटल व्योम vortex_wt_connect(vortex_t * vortex, पूर्णांक en)
अणु
	पूर्णांक i, ii, mix;

#घोषणा NR_WTROUTES 6
#अगर_घोषित CHIP_AU8830
#घोषणा NR_WTBLOCKS 2
#अन्यथा
#घोषणा NR_WTBLOCKS 1
#पूर्ण_अगर

	क्रम (i = 0; i < NR_WTBLOCKS; i++) अणु
		क्रम (ii = 0; ii < NR_WTROUTES; ii++) अणु
			mix =
			    vortex_adb_checkinout(vortex,
						  vortex->fixed_res, en,
						  VORTEX_RESOURCE_MIXIN);
			vortex->mixwt[(i * NR_WTROUTES) + ii] = mix;

			vortex_route(vortex, en, 0x11,
				     ADB_WTOUT(i, ii + 0x20), ADB_MIXIN(mix));

			vortex_connection_mixin_mix(vortex, en, mix,
						    vortex->mixplayb[ii % 2], 0);
			अगर (VORTEX_IS_QUAD(vortex))
				vortex_connection_mixin_mix(vortex, en,
							    mix,
							    vortex->mixplayb[2 +
								     (ii % 2)], 0);
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < NR_WT; i++) अणु
		hwग_लिखो(vortex->mmio, WT_RUN(i), 1);
	पूर्ण
पूर्ण

/* Read WT Register */
#अगर 0
अटल पूर्णांक vortex_wt_GetReg(vortex_t * vortex, अक्षर reg, पूर्णांक wt)
अणु
	//पूर्णांक eax, esi;

	अगर (reg == 4) अणु
		वापस hwपढ़ो(vortex->mmio, WT_PARM(wt, 3));
	पूर्ण
	अगर (reg == 7) अणु
		वापस hwपढ़ो(vortex->mmio, WT_GMODE(wt));
	पूर्ण

	वापस 0;
पूर्ण

/* WT hardware असलtraction layer generic रेजिस्टर पूर्णांकerface. */
अटल पूर्णांक
vortex_wt_SetReg2(vortex_t * vortex, अचिन्हित अक्षर reg, पूर्णांक wt,
		  u16 val)
अणु
	/*
	   पूर्णांक eax, edx;

	   अगर (wt >= NR_WT)  // 0x40 -> NR_WT
	   वापस 0;

	   अगर ((reg - 0x20) > 0) अणु
	   अगर ((reg - 0x21) != 0) 
	   वापस 0;
	   eax = ((((b & 0xff) << 0xb) + (edx & 0xff)) << 4) + 0x208; // param 2
	   पूर्ण अन्यथा अणु
	   eax = ((((b & 0xff) << 0xb) + (edx & 0xff)) << 4) + 0x20a; // param 3
	   पूर्ण
	   hwग_लिखो(vortex->mmio, eax, c);
	 */
	वापस 1;
पूर्ण

/*खुला: अटल व्योम __thiscall CWTHal::SetReg(अचिन्हित अक्षर,पूर्णांक,अचिन्हित दीर्घ) */
#पूर्ण_अगर
अटल पूर्णांक
vortex_wt_SetReg(vortex_t * vortex, अचिन्हित अक्षर reg, पूर्णांक wt,
		 u32 val)
अणु
	पूर्णांक ecx;

	अगर ((reg == 5) || ((reg >= 7) && (reg <= 10)) || (reg == 0xc)) अणु
		अगर (wt >= (NR_WT / NR_WT_PB)) अणु
			dev_warn(vortex->card->dev,
				 "WT SetReg: bank out of range. reg=0x%x, wt=%d\n",
				 reg, wt);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (wt >= NR_WT) अणु
			dev_err(vortex->card->dev,
				"WT SetReg: voice out of range\n");
			वापस 0;
		पूर्ण
	पूर्ण
	अगर (reg > 0xc)
		वापस 0;

	चयन (reg) अणु
		/* Voice specअगरic parameters */
	हाल 0:		/* running */
		/*
		pr_debug( "vortex: WT SetReg(0x%x) = 0x%08x\n",
		       WT_RUN(wt), (पूर्णांक)val);
		*/
		hwग_लिखो(vortex->mmio, WT_RUN(wt), val);
		वापस 0xc;
	हाल 1:		/* param 0 */
		/*
		pr_debug( "vortex: WT SetReg(0x%x) = 0x%08x\n",
		       WT_PARM(wt,0), (पूर्णांक)val);
		*/
		hwग_लिखो(vortex->mmio, WT_PARM(wt, 0), val);
		वापस 0xc;
	हाल 2:		/* param 1 */
		/*
		pr_debug( "vortex: WT SetReg(0x%x) = 0x%08x\n",
		       WT_PARM(wt,1), (पूर्णांक)val);
		*/
		hwग_लिखो(vortex->mmio, WT_PARM(wt, 1), val);
		वापस 0xc;
	हाल 3:		/* param 2 */
		/*
		pr_debug( "vortex: WT SetReg(0x%x) = 0x%08x\n",
		       WT_PARM(wt,2), (पूर्णांक)val);
		*/
		hwग_लिखो(vortex->mmio, WT_PARM(wt, 2), val);
		वापस 0xc;
	हाल 4:		/* param 3 */
		/*
		pr_debug( "vortex: WT SetReg(0x%x) = 0x%08x\n",
		       WT_PARM(wt,3), (पूर्णांक)val);
		*/
		hwग_लिखो(vortex->mmio, WT_PARM(wt, 3), val);
		वापस 0xc;
	हाल 6:		/* mute */
		/*
		pr_debug( "vortex: WT SetReg(0x%x) = 0x%08x\n",
		       WT_MUTE(wt), (पूर्णांक)val);
		*/
		hwग_लिखो(vortex->mmio, WT_MUTE(wt), val);
		वापस 0xc;
	हाल 0xb:
			/* delay */
		/*
		pr_debug( "vortex: WT SetReg(0x%x) = 0x%08x\n",
		       WT_DELAY(wt,0), (पूर्णांक)val);
		*/
		hwग_लिखो(vortex->mmio, WT_DELAY(wt, 3), val);
		hwग_लिखो(vortex->mmio, WT_DELAY(wt, 2), val);
		hwग_लिखो(vortex->mmio, WT_DELAY(wt, 1), val);
		hwग_लिखो(vortex->mmio, WT_DELAY(wt, 0), val);
		वापस 0xc;
		/* Global WT block parameters */
	हाल 5:		/* sramp */
		ecx = WT_SRAMP(wt);
		अवरोध;
	हाल 8:		/* aramp */
		ecx = WT_ARAMP(wt);
		अवरोध;
	हाल 9:		/* mramp */
		ecx = WT_MRAMP(wt);
		अवरोध;
	हाल 0xa:		/* ctrl */
		ecx = WT_CTRL(wt);
		अवरोध;
	हाल 0xc:		/* ds_reg */
		ecx = WT_DSREG(wt);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	/*
	pr_debug( "vortex: WT SetReg(0x%x) = 0x%08x\n", ecx, (पूर्णांक)val);
	*/
	hwग_लिखो(vortex->mmio, ecx, val);
	वापस 1;
पूर्ण

अटल व्योम vortex_wt_init(vortex_t * vortex)
अणु
	u32 var4, var8, varc, var10 = 0, edi;

	var10 &= 0xFFFFFFE3;
	var10 |= 0x22;
	var10 &= 0xFFFFFEBF;
	var10 |= 0x80;
	var10 |= 0x200;
	var10 &= 0xfffffffe;
	var10 &= 0xfffffbff;
	var10 |= 0x1800;
	// var10 = 0x1AA2
	var4 = 0x10000000;
	varc = 0x00830000;
	var8 = 0x00830000;

	/* Init Bank रेजिस्टरs. */
	क्रम (edi = 0; edi < (NR_WT / NR_WT_PB); edi++) अणु
		vortex_wt_SetReg(vortex, 0xc, edi, 0);	/* ds_reg */
		vortex_wt_SetReg(vortex, 0xa, edi, var10);	/* ctrl  */
		vortex_wt_SetReg(vortex, 0x9, edi, var4);	/* mramp */
		vortex_wt_SetReg(vortex, 0x8, edi, varc);	/* aramp */
		vortex_wt_SetReg(vortex, 0x5, edi, var8);	/* sramp */
	पूर्ण
	/* Init Voice रेजिस्टरs. */
	क्रम (edi = 0; edi < NR_WT; edi++) अणु
		vortex_wt_SetReg(vortex, 0x4, edi, 0);	/* param 3 0x20c */
		vortex_wt_SetReg(vortex, 0x3, edi, 0);	/* param 2 0x208 */
		vortex_wt_SetReg(vortex, 0x2, edi, 0);	/* param 1 0x204 */
		vortex_wt_SetReg(vortex, 0x1, edi, 0);	/* param 0 0x200 */
		vortex_wt_SetReg(vortex, 0xb, edi, 0);	/* delay 0x400 - 0x40c */
	पूर्ण
	var10 |= 1;
	क्रम (edi = 0; edi < (NR_WT / NR_WT_PB); edi++)
		vortex_wt_SetReg(vortex, 0xa, edi, var10);	/* ctrl */
पूर्ण

/* Extract of CAdbTopology::SetVolume(काष्ठा _ASPVOLUME *) */
#अगर 0
अटल व्योम vortex_wt_SetVolume(vortex_t * vortex, पूर्णांक wt, पूर्णांक vol[])
अणु
	wt_voice_t *voice = &(vortex->wt_voice[wt]);
	पूर्णांक ecx = vol[1], eax = vol[0];

	/* This is pure guess */
	voice->parm0 &= 0xff00ffff;
	voice->parm0 |= (vol[0] & 0xff) << 0x10;
	voice->parm1 &= 0xff00ffff;
	voice->parm1 |= (vol[1] & 0xff) << 0x10;

	/* This is real */
	hwग_लिखो(vortex, WT_PARM(wt, 0), voice->parm0);
	hwग_लिखो(vortex, WT_PARM(wt, 1), voice->parm0);

	अगर (voice->this_1D0 & 4) अणु
		eax >>= 8;
		ecx = eax;
		अगर (ecx < 0x80)
			ecx = 0x7f;
		voice->parm3 &= 0xFFFFC07F;
		voice->parm3 |= (ecx & 0x7f) << 7;
		voice->parm3 &= 0xFFFFFF80;
		voice->parm3 |= (eax & 0x7f);
	पूर्ण अन्यथा अणु
		voice->parm3 &= 0xFFE03FFF;
		voice->parm3 |= (eax & 0xFE00) << 5;
	पूर्ण

	hwग_लिखो(vortex, WT_PARM(wt, 3), voice->parm3);
पूर्ण

/* Extract of CAdbTopology::SetFrequency(अचिन्हित दीर्घ arg_0) */
अटल व्योम vortex_wt_SetFrequency(vortex_t * vortex, पूर्णांक wt, अचिन्हित पूर्णांक sr)
अणु
	wt_voice_t *voice = &(vortex->wt_voice[wt]);
	u32 eax, edx;

	//FIXME: 64 bit operation.
	eax = ((sr << 0xf) * 0x57619F1) & 0xffffffff;
	edx = (((sr << 0xf) * 0x57619F1)) >> 0x20;

	edx >>= 0xa;
	edx <<= 1;
	अगर (edx) अणु
		अगर (edx & 0x0FFF80000)
			eax = 0x7fff;
		अन्यथा अणु
			edx <<= 0xd;
			eax = 7;
			जबतक ((edx & 0x80000000) == 0) अणु
				edx <<= 1;
				eax--;
				अगर (eax == 0)
					अवरोध;
			पूर्ण
			अगर (eax)
				edx <<= 1;
			eax <<= 0xc;
			edx >>= 0x14;
			eax |= edx;
		पूर्ण
	पूर्ण अन्यथा
		eax = 0;
	voice->parm0 &= 0xffff0001;
	voice->parm0 |= (eax & 0x7fff) << 1;
	voice->parm1 = voice->parm0 | 1;
	// Wt: this_1D4
	//AuWt::WriteReg((uदीर्घ)(this_1DC<<4)+0x200, (uदीर्घ)this_1E4);
	//AuWt::WriteReg((uदीर्घ)(this_1DC<<4)+0x204, (uदीर्घ)this_1E8);
	hwग_लिखो(vortex->mmio, WT_PARM(wt, 0), voice->parm0);
	hwग_लिखो(vortex->mmio, WT_PARM(wt, 1), voice->parm1);
पूर्ण
#पूर्ण_अगर

/* End of File */
