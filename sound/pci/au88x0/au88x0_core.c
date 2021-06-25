<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 */

/*
    Vortex core low level functions.
	
 Author: Manuel Jander (mjander@users.sourceक्रमge.cl)
 These functions are मुख्यly the result of translations made
 from the original disassembly of the au88x0 binary drivers,
 written by Aureal beक्रमe they went करोwn.
 Many thanks to the Jeff Muizelaar, Kester Madकरोck, and whoever
 contributed to the OpenVortex project.
 The author of this file, put the few available pieces together
 and translated the rest of the riddle (Mix, Src and connection stuff).
 Some things are still to be discovered, and their meanings are unclear.

 Some of these functions aren't पूर्णांकended to be really used, rather
 to help to understand how करोes the AU88X0 chips work. Keep them in, because
 they could be used somewhere in the future.

 This code hasn't been tested or proof पढ़ो thoroughly. If you wanna help,
 take a look at the AU88X0 assembly and check अगर this matches.
 Functions tested ok so far are (they show the desired effect
 at least):
   vortex_routes(); (1 bug fixed).
   vortex_adb_addroute();
   vortex_adb_addroutes();
   vortex_connect_codecplay();
   vortex_src_flushbuffers();
   vortex_adbdma_seपंचांगode();  note: still some unknown arguments!
   vortex_adbdma_startfअगरo();
   vortex_adbdma_stopfअगरo();
   vortex_fअगरo_setadbctrl(); note: still some unknown arguments!
   vortex_mix_setinputvolumebyte();
   vortex_mix_enableinput();
   vortex_mixer_addWTD(); (fixed)
   vortex_connection_adbdma_src_src();
   vortex_connection_adbdma_src();
   vortex_src_change_convratio();
   vortex_src_addWTD(); (fixed)

 History:

 01-03-2003 First revision.
 01-21-2003 Some bug fixes.
 17-02-2003 many bugfixes after a big versioning mess.
 18-02-2003 JAAAAAHHHUUUUUU!!!! The mixer works !! I'm just so happy !
			 (2 hours later...) I cant believe it! Im really lucky today.
			 Now the SRC is working too! Yeah! XMMS works !
 20-02-2003 First steps पूर्णांकo the ALSA world.
 28-02-2003 As my birthday present, i discovered how the DMA buffer pages really
            work :-). It was all wrong.
 12-03-2003 ALSA driver starts working (2 channels).
 16-03-2003 More srcblock_setupchannel discoveries.
 12-04-2003 AU8830 playback support. Recording in the works.
 17-04-2003 vortex_route() and vortex_routes() bug fixes. AU8830 recording
 			works now, but chipn' dale effect is still there.
 16-05-2003 SrcSetupChannel cleanup. Moved the Src setup stuff entirely
            पूर्णांकo au88x0_pcm.c .
 06-06-2003 Buffer shअगरter bugfix. Mixer volume fix.
 07-12-2003 A3D routing finally fixed. Believed to be OK.
 25-03-2004 Many thanks to Claudia, क्रम such valuable bug reports.
 
*/

#समावेश "au88x0.h"
#समावेश "au88x0_a3d.h"
#समावेश <linux/delay.h>

/*  MIXER (CAsp4Mix.s and CAsp4Mixer.s) */

// FIXME: get rid of this.
अटल पूर्णांक mchannels[NR_MIXIN];
अटल पूर्णांक rampchs[NR_MIXIN];

अटल व्योम vortex_mixer_en_sr(vortex_t * vortex, पूर्णांक channel)
अणु
	hwग_लिखो(vortex->mmio, VORTEX_MIXER_SR,
		hwपढ़ो(vortex->mmio, VORTEX_MIXER_SR) | (0x1 << channel));
पूर्ण
अटल व्योम vortex_mixer_dis_sr(vortex_t * vortex, पूर्णांक channel)
अणु
	hwग_लिखो(vortex->mmio, VORTEX_MIXER_SR,
		hwपढ़ो(vortex->mmio, VORTEX_MIXER_SR) & ~(0x1 << channel));
पूर्ण

#अगर 0
अटल व्योम
vortex_mix_muteinputgain(vortex_t * vortex, अचिन्हित अक्षर mix,
			 अचिन्हित अक्षर channel)
अणु
	hwग_लिखो(vortex->mmio, VORTEX_MIX_INVOL_A + ((mix << 5) + channel),
		0x80);
	hwग_लिखो(vortex->mmio, VORTEX_MIX_INVOL_B + ((mix << 5) + channel),
		0x80);
पूर्ण

अटल पूर्णांक vortex_mix_getvolume(vortex_t * vortex, अचिन्हित अक्षर mix)
अणु
	पूर्णांक a;
	a = hwपढ़ो(vortex->mmio, VORTEX_MIX_VOL_A + (mix << 2)) & 0xff;
	//FP2LinearFrac(a);
	वापस (a);
पूर्ण

अटल पूर्णांक
vortex_mix_getinputvolume(vortex_t * vortex, अचिन्हित अक्षर mix,
			  पूर्णांक channel, पूर्णांक *vol)
अणु
	पूर्णांक a;
	अगर (!(mchannels[mix] & (1 << channel)))
		वापस 0;
	a = hwपढ़ो(vortex->mmio,
		   VORTEX_MIX_INVOL_A + (((mix << 5) + channel) << 2));
	/*
	   अगर (rampchs[mix] == 0)
	   a = FP2LinearFrac(a);
	   अन्यथा
	   a = FP2LinearFracWT(a);
	 */
	*vol = a;
	वापस (0);
पूर्ण

अटल अचिन्हित पूर्णांक vortex_mix_boost6db(अचिन्हित अक्षर vol)
अणु
	वापस (vol + 8);	/* WOW! what a complex function! */
पूर्ण

अटल व्योम vortex_mix_rampvolume(vortex_t * vortex, पूर्णांक mix)
अणु
	पूर्णांक ch;
	अक्षर a;
	// This function is पूर्णांकended क्रम ramping करोwn only (see vortex_disableinput()).
	क्रम (ch = 0; ch < 0x20; ch++) अणु
		अगर (((1 << ch) & rampchs[mix]) == 0)
			जारी;
		a = hwपढ़ो(vortex->mmio,
			   VORTEX_MIX_INVOL_B + (((mix << 5) + ch) << 2));
		अगर (a > -126) अणु
			a -= 2;
			hwग_लिखो(vortex->mmio,
				VORTEX_MIX_INVOL_A +
				(((mix << 5) + ch) << 2), a);
			hwग_लिखो(vortex->mmio,
				VORTEX_MIX_INVOL_B +
				(((mix << 5) + ch) << 2), a);
		पूर्ण अन्यथा
			vortex_mix_समाप्तinput(vortex, mix, ch);
	पूर्ण
पूर्ण

अटल पूर्णांक
vortex_mix_getenablebit(vortex_t * vortex, अचिन्हित अक्षर mix, पूर्णांक mixin)
अणु
	पूर्णांक addr, temp;
	अगर (mixin >= 0)
		addr = mixin;
	अन्यथा
		addr = mixin + 3;
	addr = ((mix << 3) + (addr >> 2)) << 2;
	temp = hwपढ़ो(vortex->mmio, VORTEX_MIX_ENIN + addr);
	वापस ((temp >> (mixin & 3)) & 1);
पूर्ण
#पूर्ण_अगर
अटल व्योम
vortex_mix_setvolumebyte(vortex_t * vortex, अचिन्हित अक्षर mix,
			 अचिन्हित अक्षर vol)
अणु
	पूर्णांक temp;
	hwग_लिखो(vortex->mmio, VORTEX_MIX_VOL_A + (mix << 2), vol);
	अगर (1) अणु		/*अगर (this_10) */
		temp = hwपढ़ो(vortex->mmio, VORTEX_MIX_VOL_B + (mix << 2));
		अगर ((temp != 0x80) || (vol == 0x80))
			वापस;
	पूर्ण
	hwग_लिखो(vortex->mmio, VORTEX_MIX_VOL_B + (mix << 2), vol);
पूर्ण

अटल व्योम
vortex_mix_setinputvolumebyte(vortex_t * vortex, अचिन्हित अक्षर mix,
			      पूर्णांक mixin, अचिन्हित अक्षर vol)
अणु
	पूर्णांक temp;

	hwग_लिखो(vortex->mmio,
		VORTEX_MIX_INVOL_A + (((mix << 5) + mixin) << 2), vol);
	अगर (1) अणु		/* this_10, initialized to 1. */
		temp =
		    hwपढ़ो(vortex->mmio,
			   VORTEX_MIX_INVOL_B + (((mix << 5) + mixin) << 2));
		अगर ((temp != 0x80) || (vol == 0x80))
			वापस;
	पूर्ण
	hwग_लिखो(vortex->mmio,
		VORTEX_MIX_INVOL_B + (((mix << 5) + mixin) << 2), vol);
पूर्ण

अटल व्योम
vortex_mix_setenablebit(vortex_t * vortex, अचिन्हित अक्षर mix, पूर्णांक mixin, पूर्णांक en)
अणु
	पूर्णांक temp, addr;

	अगर (mixin < 0)
		addr = (mixin + 3);
	अन्यथा
		addr = mixin;
	addr = ((mix << 3) + (addr >> 2)) << 2;
	temp = hwपढ़ो(vortex->mmio, VORTEX_MIX_ENIN + addr);
	अगर (en)
		temp |= (1 << (mixin & 3));
	अन्यथा
		temp &= ~(1 << (mixin & 3));
	/* Mute input. Aअटल व्योम crackling? */
	hwग_लिखो(vortex->mmio,
		VORTEX_MIX_INVOL_B + (((mix << 5) + mixin) << 2), 0x80);
	/* Looks like clear buffer. */
	hwग_लिखो(vortex->mmio, VORTEX_MIX_SMP + (mixin << 2), 0x0);
	hwग_लिखो(vortex->mmio, VORTEX_MIX_SMP + 4 + (mixin << 2), 0x0);
	/* Write enable bit. */
	hwग_लिखो(vortex->mmio, VORTEX_MIX_ENIN + addr, temp);
पूर्ण

अटल व्योम
vortex_mix_समाप्तinput(vortex_t * vortex, अचिन्हित अक्षर mix, पूर्णांक mixin)
अणु
	rampchs[mix] &= ~(1 << mixin);
	vortex_mix_setinputvolumebyte(vortex, mix, mixin, 0x80);
	mchannels[mix] &= ~(1 << mixin);
	vortex_mix_setenablebit(vortex, mix, mixin, 0);
पूर्ण

अटल व्योम
vortex_mix_enableinput(vortex_t * vortex, अचिन्हित अक्षर mix, पूर्णांक mixin)
अणु
	vortex_mix_समाप्तinput(vortex, mix, mixin);
	अगर ((mchannels[mix] & (1 << mixin)) == 0) अणु
		vortex_mix_setinputvolumebyte(vortex, mix, mixin, 0x80);	/*0x80 : mute */
		mchannels[mix] |= (1 << mixin);
	पूर्ण
	vortex_mix_setenablebit(vortex, mix, mixin, 1);
पूर्ण

अटल व्योम
vortex_mix_disableinput(vortex_t * vortex, अचिन्हित अक्षर mix, पूर्णांक channel,
			पूर्णांक ramp)
अणु
	अगर (ramp) अणु
		rampchs[mix] |= (1 << channel);
		// Register callback.
		//vortex_mix_startrampvolume(vortex);
		vortex_mix_समाप्तinput(vortex, mix, channel);
	पूर्ण अन्यथा
		vortex_mix_समाप्तinput(vortex, mix, channel);
पूर्ण

अटल पूर्णांक
vortex_mixer_addWTD(vortex_t * vortex, अचिन्हित अक्षर mix, अचिन्हित अक्षर ch)
अणु
	पूर्णांक temp, lअगरeboat = 0, prev;

	temp = hwपढ़ो(vortex->mmio, VORTEX_MIXER_SR);
	अगर ((temp & (1 << ch)) == 0) अणु
		hwग_लिखो(vortex->mmio, VORTEX_MIXER_CHNBASE + (ch << 2), mix);
		vortex_mixer_en_sr(vortex, ch);
		वापस 1;
	पूर्ण
	prev = VORTEX_MIXER_CHNBASE + (ch << 2);
	temp = hwपढ़ो(vortex->mmio, prev);
	जबतक (temp & 0x10) अणु
		prev = VORTEX_MIXER_RTBASE + ((temp & 0xf) << 2);
		temp = hwपढ़ो(vortex->mmio, prev);
		//prपूर्णांकk(KERN_INFO "vortex: mixAddWTD: while addr=%x, val=%x\n", prev, temp);
		अगर ((++lअगरeboat) > 0xf) अणु
			dev_err(vortex->card->dev,
				"vortex_mixer_addWTD: lifeboat overflow\n");
			वापस 0;
		पूर्ण
	पूर्ण
	hwग_लिखो(vortex->mmio, VORTEX_MIXER_RTBASE + ((temp & 0xf) << 2), mix);
	hwग_लिखो(vortex->mmio, prev, (temp & 0xf) | 0x10);
	वापस 1;
पूर्ण

अटल पूर्णांक
vortex_mixer_delWTD(vortex_t * vortex, अचिन्हित अक्षर mix, अचिन्हित अक्षर ch)
अणु
	पूर्णांक esp14 = -1, esp18, eax, ebx, edx, ebp, esi = 0;
	//पूर्णांक esp1f=edi(जबतक)=src, esp10=ch;

	eax = hwपढ़ो(vortex->mmio, VORTEX_MIXER_SR);
	अगर (((1 << ch) & eax) == 0) अणु
		dev_err(vortex->card->dev, "mix ALARM %x\n", eax);
		वापस 0;
	पूर्ण
	ebp = VORTEX_MIXER_CHNBASE + (ch << 2);
	esp18 = hwपढ़ो(vortex->mmio, ebp);
	अगर (esp18 & 0x10) अणु
		ebx = (esp18 & 0xf);
		अगर (mix == ebx) अणु
			ebx = VORTEX_MIXER_RTBASE + (mix << 2);
			edx = hwपढ़ो(vortex->mmio, ebx);
			//7b60
			hwग_लिखो(vortex->mmio, ebp, edx);
			hwग_लिखो(vortex->mmio, ebx, 0);
		पूर्ण अन्यथा अणु
			//7ad3
			edx =
			    hwपढ़ो(vortex->mmio,
				   VORTEX_MIXER_RTBASE + (ebx << 2));
			//prपूर्णांकk(KERN_INFO "vortex: mixdelWTD: 1 addr=%x, val=%x, src=%x\n", ebx, edx, src);
			जबतक ((edx & 0xf) != mix) अणु
				अगर ((esi) > 0xf) अणु
					dev_err(vortex->card->dev,
						"mixdelWTD: error lifeboat overflow\n");
					वापस 0;
				पूर्ण
				esp14 = ebx;
				ebx = edx & 0xf;
				ebp = ebx << 2;
				edx =
				    hwपढ़ो(vortex->mmio,
					   VORTEX_MIXER_RTBASE + ebp);
				//prपूर्णांकk(KERN_INFO "vortex: mixdelWTD: while addr=%x, val=%x\n", ebp, edx);
				esi++;
			पूर्ण
			//7b30
			ebp = ebx << 2;
			अगर (edx & 0x10) अणु	/* Delete entry in between others */
				ebx = VORTEX_MIXER_RTBASE + ((edx & 0xf) << 2);
				edx = hwपढ़ो(vortex->mmio, ebx);
				//7b60
				hwग_लिखो(vortex->mmio,
					VORTEX_MIXER_RTBASE + ebp, edx);
				hwग_लिखो(vortex->mmio, ebx, 0);
				//prपूर्णांकk(KERN_INFO "vortex mixdelWTD between addr= 0x%x, val= 0x%x\n", ebp, edx);
			पूर्ण अन्यथा अणु	/* Delete last entry */
				//7b83
				अगर (esp14 == -1)
					hwग_लिखो(vortex->mmio,
						VORTEX_MIXER_CHNBASE +
						(ch << 2), esp18 & 0xef);
				अन्यथा अणु
					ebx = (0xffffffe0 & edx) | (0xf & ebx);
					hwग_लिखो(vortex->mmio,
						VORTEX_MIXER_RTBASE +
						(esp14 << 2), ebx);
					//prपूर्णांकk(KERN_INFO "vortex mixdelWTD last addr= 0x%x, val= 0x%x\n", esp14, ebx);
				पूर्ण
				hwग_लिखो(vortex->mmio,
					VORTEX_MIXER_RTBASE + ebp, 0);
				वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		//prपूर्णांकk(KERN_INFO "removed last mix\n");
		//7be0
		vortex_mixer_dis_sr(vortex, ch);
		hwग_लिखो(vortex->mmio, ebp, 0);
	पूर्ण
	वापस 1;
पूर्ण

अटल व्योम vortex_mixer_init(vortex_t * vortex)
अणु
	u32 addr;
	पूर्णांक x;

	// FIXME: get rid of this crap.
	स_रखो(mchannels, 0, NR_MIXOUT * माप(पूर्णांक));
	स_रखो(rampchs, 0, NR_MIXOUT * माप(पूर्णांक));

	addr = VORTEX_MIX_SMP + 0x17c;
	क्रम (x = 0x5f; x >= 0; x--) अणु
		hwग_लिखो(vortex->mmio, addr, 0);
		addr -= 4;
	पूर्ण
	addr = VORTEX_MIX_ENIN + 0x1fc;
	क्रम (x = 0x7f; x >= 0; x--) अणु
		hwग_लिखो(vortex->mmio, addr, 0);
		addr -= 4;
	पूर्ण
	addr = VORTEX_MIX_SMP + 0x17c;
	क्रम (x = 0x5f; x >= 0; x--) अणु
		hwग_लिखो(vortex->mmio, addr, 0);
		addr -= 4;
	पूर्ण
	addr = VORTEX_MIX_INVOL_A + 0x7fc;
	क्रम (x = 0x1ff; x >= 0; x--) अणु
		hwग_लिखो(vortex->mmio, addr, 0x80);
		addr -= 4;
	पूर्ण
	addr = VORTEX_MIX_VOL_A + 0x3c;
	क्रम (x = 0xf; x >= 0; x--) अणु
		hwग_लिखो(vortex->mmio, addr, 0x80);
		addr -= 4;
	पूर्ण
	addr = VORTEX_MIX_INVOL_B + 0x7fc;
	क्रम (x = 0x1ff; x >= 0; x--) अणु
		hwग_लिखो(vortex->mmio, addr, 0x80);
		addr -= 4;
	पूर्ण
	addr = VORTEX_MIX_VOL_B + 0x3c;
	क्रम (x = 0xf; x >= 0; x--) अणु
		hwग_लिखो(vortex->mmio, addr, 0x80);
		addr -= 4;
	पूर्ण
	addr = VORTEX_MIXER_RTBASE + (MIXER_RTBASE_SIZE - 1) * 4;
	क्रम (x = (MIXER_RTBASE_SIZE - 1); x >= 0; x--) अणु
		hwग_लिखो(vortex->mmio, addr, 0x0);
		addr -= 4;
	पूर्ण
	hwग_लिखो(vortex->mmio, VORTEX_MIXER_SR, 0);

	/* Set clipping उच्चमानing (this may be all wrong). */
	/*
	क्रम (x = 0; x < 0x80; x++) अणु
		hwग_लिखो(vortex->mmio, VORTEX_MIXER_CLIP + (x << 2), 0x3ffff);
	पूर्ण
	*/
	/*
	   call CAsp4Mix__Initialize_CAsp4HwIO____CAsp4Mixer____
	   Register ISR callback क्रम volume smooth fade out.
	   Maybe this aव्योमs clicks when press "stop" ?
	 */
पूर्ण

/*  SRC (CAsp4Src.s and CAsp4SrcBlock) */

अटल व्योम vortex_src_en_sr(vortex_t * vortex, पूर्णांक channel)
अणु
	hwग_लिखो(vortex->mmio, VORTEX_SRCBLOCK_SR,
		hwपढ़ो(vortex->mmio, VORTEX_SRCBLOCK_SR) | (0x1 << channel));
पूर्ण

अटल व्योम vortex_src_dis_sr(vortex_t * vortex, पूर्णांक channel)
अणु
	hwग_लिखो(vortex->mmio, VORTEX_SRCBLOCK_SR,
		hwपढ़ो(vortex->mmio, VORTEX_SRCBLOCK_SR) & ~(0x1 << channel));
पूर्ण

अटल व्योम vortex_src_flushbuffers(vortex_t * vortex, अचिन्हित अक्षर src)
अणु
	पूर्णांक i;

	क्रम (i = 0x1f; i >= 0; i--)
		hwग_लिखो(vortex->mmio,
			VORTEX_SRC_DATA0 + (src << 7) + (i << 2), 0);
	hwग_लिखो(vortex->mmio, VORTEX_SRC_DATA + (src << 3), 0);
	hwग_लिखो(vortex->mmio, VORTEX_SRC_DATA + (src << 3) + 4, 0);
पूर्ण

अटल व्योम vortex_src_cleardrअगरt(vortex_t * vortex, अचिन्हित अक्षर src)
अणु
	hwग_लिखो(vortex->mmio, VORTEX_SRC_DRIFT0 + (src << 2), 0);
	hwग_लिखो(vortex->mmio, VORTEX_SRC_DRIFT1 + (src << 2), 0);
	hwग_लिखो(vortex->mmio, VORTEX_SRC_DRIFT2 + (src << 2), 1);
पूर्ण

अटल व्योम
vortex_src_set_throttlesource(vortex_t * vortex, अचिन्हित अक्षर src, पूर्णांक en)
अणु
	पूर्णांक temp;

	temp = hwपढ़ो(vortex->mmio, VORTEX_SRC_SOURCE);
	अगर (en)
		temp |= 1 << src;
	अन्यथा
		temp &= ~(1 << src);
	hwग_लिखो(vortex->mmio, VORTEX_SRC_SOURCE, temp);
पूर्ण

अटल पूर्णांक
vortex_src_persist_convratio(vortex_t * vortex, अचिन्हित अक्षर src, पूर्णांक ratio)
अणु
	पूर्णांक temp, lअगरeboat = 0;

	करो अणु
		hwग_लिखो(vortex->mmio, VORTEX_SRC_CONVRATIO + (src << 2), ratio);
		temp = hwपढ़ो(vortex->mmio, VORTEX_SRC_CONVRATIO + (src << 2));
		अगर ((++lअगरeboat) > 0x9) अणु
			dev_err(vortex->card->dev, "Src cvr fail\n");
			अवरोध;
		पूर्ण
	पूर्ण
	जबतक (temp != ratio);
	वापस temp;
पूर्ण

#अगर 0
अटल व्योम vortex_src_slowlock(vortex_t * vortex, अचिन्हित अक्षर src)
अणु
	पूर्णांक temp;

	hwग_लिखो(vortex->mmio, VORTEX_SRC_DRIFT2 + (src << 2), 1);
	hwग_लिखो(vortex->mmio, VORTEX_SRC_DRIFT0 + (src << 2), 0);
	temp = hwपढ़ो(vortex->mmio, VORTEX_SRC_U0 + (src << 2));
	अगर (temp & 0x200)
		hwग_लिखो(vortex->mmio, VORTEX_SRC_U0 + (src << 2),
			temp & ~0x200L);
पूर्ण

अटल व्योम
vortex_src_change_convratio(vortex_t * vortex, अचिन्हित अक्षर src, पूर्णांक ratio)
अणु
	पूर्णांक temp, a;

	अगर ((ratio & 0x10000) && (ratio != 0x10000)) अणु
		अगर (ratio & 0x3fff)
			a = (0x11 - ((ratio >> 0xe) & 0x3)) - 1;
		अन्यथा
			a = (0x11 - ((ratio >> 0xe) & 0x3)) - 2;
	पूर्ण अन्यथा
		a = 0xc;
	temp = hwपढ़ो(vortex->mmio, VORTEX_SRC_U0 + (src << 2));
	अगर (((temp >> 4) & 0xf) != a)
		hwग_लिखो(vortex->mmio, VORTEX_SRC_U0 + (src << 2),
			(temp & 0xf) | ((a & 0xf) << 4));

	vortex_src_persist_convratio(vortex, src, ratio);
पूर्ण

अटल पूर्णांक
vortex_src_checkratio(vortex_t * vortex, अचिन्हित अक्षर src,
		      अचिन्हित पूर्णांक desired_ratio)
अणु
	पूर्णांक hw_ratio, lअगरeboat = 0;

	hw_ratio = hwपढ़ो(vortex->mmio, VORTEX_SRC_CONVRATIO + (src << 2));

	जबतक (hw_ratio != desired_ratio) अणु
		hwग_लिखो(vortex->mmio, VORTEX_SRC_CONVRATIO + (src << 2), desired_ratio);

		अगर ((lअगरeboat++) > 15) अणु
			pr_err( "Vortex: could not set src-%d from %d to %d\n",
			       src, hw_ratio, desired_ratio);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस hw_ratio;
पूर्ण

#पूर्ण_अगर
/*
 Objective: Set samplerate क्रम given SRC module.
 Arguments:
	card:	poपूर्णांकer to vortex_t strcut.
	src:	Integer index of the SRC module.
	cr:		Current sample rate conversion factor.
	b:		unknown 16 bit value.
	sweep:	Enable Samplerate fade from cr toward tr flag.
	dirplay: 1: playback, 0: recording.
	sl:		Slow Lock flag.
	tr:		Target samplerate conversion.
	thsource: Throttle source flag (no idea what that means).
*/
अटल व्योम vortex_src_setupchannel(vortex_t * card, अचिन्हित अक्षर src,
			अचिन्हित पूर्णांक cr, अचिन्हित पूर्णांक b, पूर्णांक sweep, पूर्णांक d,
			पूर्णांक dirplay, पूर्णांक sl, अचिन्हित पूर्णांक tr, पूर्णांक thsource)
अणु
	// noplayback: d=2,4,7,0xa,0xb when using first 2 src's.
	// c: enables pitch sweep.
	// looks like g is c related. Maybe g is a sweep parameter ?
	// g = cvr
	// dirplay: 0 = recording, 1 = playback
	// d = src hw index.

	पूर्णांक esi, ebp = 0, esp10;

	vortex_src_flushbuffers(card, src);

	अगर (sweep) अणु
		अगर ((tr & 0x10000) && (tr != 0x10000)) अणु
			tr = 0;
			esi = 0x7;
		पूर्ण अन्यथा अणु
			अगर ((((लघु)tr) < 0) && (tr != 0x8000)) अणु
				tr = 0;
				esi = 0x8;
			पूर्ण अन्यथा अणु
				tr = 1;
				esi = 0xc;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((cr & 0x10000) && (cr != 0x10000)) अणु
			tr = 0;	/*ebx = 0 */
			esi = 0x11 - ((cr >> 0xe) & 7);
			अगर (cr & 0x3fff)
				esi -= 1;
			अन्यथा
				esi -= 2;
		पूर्ण अन्यथा अणु
			tr = 1;
			esi = 0xc;
		पूर्ण
	पूर्ण
	vortex_src_cleardrअगरt(card, src);
	vortex_src_set_throttlesource(card, src, thsource);

	अगर ((dirplay == 0) && (sweep == 0)) अणु
		अगर (tr)
			esp10 = 0xf;
		अन्यथा
			esp10 = 0xc;
		ebp = 0;
	पूर्ण अन्यथा अणु
		अगर (tr)
			ebp = 0xf;
		अन्यथा
			ebp = 0xc;
		esp10 = 0;
	पूर्ण
	hwग_लिखो(card->mmio, VORTEX_SRC_U0 + (src << 2),
		(sl << 0x9) | (sweep << 0x8) | ((esi & 0xf) << 4) | d);
	/* 0xc0   esi=0xc c=f=0 d=0 */
	vortex_src_persist_convratio(card, src, cr);
	hwग_लिखो(card->mmio, VORTEX_SRC_U1 + (src << 2), b & 0xffff);
	/* 0   b=0 */
	hwग_लिखो(card->mmio, VORTEX_SRC_U2 + (src << 2),
		(tr << 0x11) | (dirplay << 0x10) | (ebp << 0x8) | esp10);
	/* 0x30f00 e=g=1 esp10=0 ebp=f */
	//prपूर्णांकk(KERN_INFO "vortex: SRC %d, d=0x%x, esi=0x%x, esp10=0x%x, ebp=0x%x\n", src, d, esi, esp10, ebp);
पूर्ण

अटल व्योम vortex_srcblock_init(vortex_t * vortex)
अणु
	u32 addr;
	पूर्णांक x;
	hwग_लिखो(vortex->mmio, VORTEX_SRC_SOURCESIZE, 0x1ff);
	/*
	   क्रम (x=0; x<0x10; x++) अणु
	   vortex_src_init(&vortex_src[x], x);
	   पूर्ण
	 */
	//addr = 0xcc3c;
	//addr = 0x26c3c;
	addr = VORTEX_SRC_RTBASE + 0x3c;
	क्रम (x = 0xf; x >= 0; x--) अणु
		hwग_लिखो(vortex->mmio, addr, 0);
		addr -= 4;
	पूर्ण
	//addr = 0xcc94;
	//addr = 0x26c94;
	addr = VORTEX_SRC_CHNBASE + 0x54;
	क्रम (x = 0x15; x >= 0; x--) अणु
		hwग_लिखो(vortex->mmio, addr, 0);
		addr -= 4;
	पूर्ण
पूर्ण

अटल पूर्णांक
vortex_src_addWTD(vortex_t * vortex, अचिन्हित अक्षर src, अचिन्हित अक्षर ch)
अणु
	पूर्णांक temp, lअगरeboat = 0, prev;
	// esp13 = src

	temp = hwपढ़ो(vortex->mmio, VORTEX_SRCBLOCK_SR);
	अगर ((temp & (1 << ch)) == 0) अणु
		hwग_लिखो(vortex->mmio, VORTEX_SRC_CHNBASE + (ch << 2), src);
		vortex_src_en_sr(vortex, ch);
		वापस 1;
	पूर्ण
	prev = VORTEX_SRC_CHNBASE + (ch << 2);	/*ebp */
	temp = hwपढ़ो(vortex->mmio, prev);
	//जबतक (temp & NR_SRC) अणु
	जबतक (temp & 0x10) अणु
		prev = VORTEX_SRC_RTBASE + ((temp & 0xf) << 2);	/*esp12 */
		//prev = VORTEX_SRC_RTBASE + ((temp & (NR_SRC-1)) << 2); /*esp12*/
		temp = hwपढ़ो(vortex->mmio, prev);
		//prपूर्णांकk(KERN_INFO "vortex: srcAddWTD: while addr=%x, val=%x\n", prev, temp);
		अगर ((++lअगरeboat) > 0xf) अणु
			dev_err(vortex->card->dev,
				"vortex_src_addWTD: lifeboat overflow\n");
			वापस 0;
		पूर्ण
	पूर्ण
	hwग_लिखो(vortex->mmio, VORTEX_SRC_RTBASE + ((temp & 0xf) << 2), src);
	//hwग_लिखो(vortex->mmio, prev, (temp & (NR_SRC-1)) | NR_SRC);
	hwग_लिखो(vortex->mmio, prev, (temp & 0xf) | 0x10);
	वापस 1;
पूर्ण

अटल पूर्णांक
vortex_src_delWTD(vortex_t * vortex, अचिन्हित अक्षर src, अचिन्हित अक्षर ch)
अणु
	पूर्णांक esp14 = -1, esp18, eax, ebx, edx, ebp, esi = 0;
	//पूर्णांक esp1f=edi(जबतक)=src, esp10=ch;

	eax = hwपढ़ो(vortex->mmio, VORTEX_SRCBLOCK_SR);
	अगर (((1 << ch) & eax) == 0) अणु
		dev_err(vortex->card->dev, "src alarm\n");
		वापस 0;
	पूर्ण
	ebp = VORTEX_SRC_CHNBASE + (ch << 2);
	esp18 = hwपढ़ो(vortex->mmio, ebp);
	अगर (esp18 & 0x10) अणु
		ebx = (esp18 & 0xf);
		अगर (src == ebx) अणु
			ebx = VORTEX_SRC_RTBASE + (src << 2);
			edx = hwपढ़ो(vortex->mmio, ebx);
			//7b60
			hwग_लिखो(vortex->mmio, ebp, edx);
			hwग_लिखो(vortex->mmio, ebx, 0);
		पूर्ण अन्यथा अणु
			//7ad3
			edx =
			    hwपढ़ो(vortex->mmio,
				   VORTEX_SRC_RTBASE + (ebx << 2));
			//prपूर्णांकk(KERN_INFO "vortex: srcdelWTD: 1 addr=%x, val=%x, src=%x\n", ebx, edx, src);
			जबतक ((edx & 0xf) != src) अणु
				अगर ((esi) > 0xf) अणु
					dev_warn(vortex->card->dev,
						 "srcdelWTD: error, lifeboat overflow\n");
					वापस 0;
				पूर्ण
				esp14 = ebx;
				ebx = edx & 0xf;
				ebp = ebx << 2;
				edx =
				    hwपढ़ो(vortex->mmio,
					   VORTEX_SRC_RTBASE + ebp);
				//prपूर्णांकk(KERN_INFO "vortex: srcdelWTD: while addr=%x, val=%x\n", ebp, edx);
				esi++;
			पूर्ण
			//7b30
			ebp = ebx << 2;
			अगर (edx & 0x10) अणु	/* Delete entry in between others */
				ebx = VORTEX_SRC_RTBASE + ((edx & 0xf) << 2);
				edx = hwपढ़ो(vortex->mmio, ebx);
				//7b60
				hwग_लिखो(vortex->mmio,
					VORTEX_SRC_RTBASE + ebp, edx);
				hwग_लिखो(vortex->mmio, ebx, 0);
				//prपूर्णांकk(KERN_INFO "vortex srcdelWTD between addr= 0x%x, val= 0x%x\n", ebp, edx);
			पूर्ण अन्यथा अणु	/* Delete last entry */
				//7b83
				अगर (esp14 == -1)
					hwग_लिखो(vortex->mmio,
						VORTEX_SRC_CHNBASE +
						(ch << 2), esp18 & 0xef);
				अन्यथा अणु
					ebx = (0xffffffe0 & edx) | (0xf & ebx);
					hwग_लिखो(vortex->mmio,
						VORTEX_SRC_RTBASE +
						(esp14 << 2), ebx);
					//prपूर्णांकk(KERN_INFO"vortex srcdelWTD last addr= 0x%x, val= 0x%x\n", esp14, ebx);
				पूर्ण
				hwग_लिखो(vortex->mmio,
					VORTEX_SRC_RTBASE + ebp, 0);
				वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		//7be0
		vortex_src_dis_sr(vortex, ch);
		hwग_लिखो(vortex->mmio, ebp, 0);
	पूर्ण
	वापस 1;
पूर्ण

 /*FIFO*/ 

अटल व्योम
vortex_fअगरo_clearadbdata(vortex_t * vortex, पूर्णांक fअगरo, पूर्णांक x)
अणु
	क्रम (x--; x >= 0; x--)
		hwग_लिखो(vortex->mmio,
			VORTEX_FIFO_ADBDATA +
			(((fअगरo << FIFO_SIZE_BITS) + x) << 2), 0);
पूर्ण

#अगर 0
अटल व्योम vortex_fअगरo_adbinitialize(vortex_t * vortex, पूर्णांक fअगरo, पूर्णांक j)
अणु
	vortex_fअगरo_clearadbdata(vortex, fअगरo, FIFO_SIZE);
#अगर_घोषित CHIP_AU8820
	hwग_लिखो(vortex->mmio, VORTEX_FIFO_ADBCTRL + (fअगरo << 2),
		(FIFO_U1 | ((j & FIFO_MASK) << 0xb)));
#अन्यथा
	hwग_लिखो(vortex->mmio, VORTEX_FIFO_ADBCTRL + (fअगरo << 2),
		(FIFO_U1 | ((j & FIFO_MASK) << 0xc)));
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर
अटल व्योम vortex_fअगरo_setadbvalid(vortex_t * vortex, पूर्णांक fअगरo, पूर्णांक en)
अणु
	hwग_लिखो(vortex->mmio, VORTEX_FIFO_ADBCTRL + (fअगरo << 2),
		(hwपढ़ो(vortex->mmio, VORTEX_FIFO_ADBCTRL + (fअगरo << 2)) &
		 0xffffffef) | ((1 & en) << 4) | FIFO_U1);
पूर्ण

अटल व्योम
vortex_fअगरo_setadbctrl(vortex_t * vortex, पूर्णांक fअगरo, पूर्णांक stereo, पूर्णांक priority,
		       पूर्णांक empty, पूर्णांक valid, पूर्णांक f)
अणु
	पूर्णांक temp, lअगरeboat = 0;
	//पूर्णांक this_8[NR_ADB] = अणु0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0पूर्ण; /* position */
	पूर्णांक this_4 = 0x2;
	/* f seems priority related.
	 * CAsp4AdbDma::SetPriority is the only place that calls SetAdbCtrl with f set to 1
	 * every where अन्यथा it is set to 0. It seems, however, that CAsp4AdbDma::SetPriority
	 * is never called, thus the f related bits reमुख्य a mystery क्रम now.
	 */
	करो अणु
		temp = hwपढ़ो(vortex->mmio, VORTEX_FIFO_ADBCTRL + (fअगरo << 2));
		अगर (lअगरeboat++ > 0xbb8) अणु
			dev_err(vortex->card->dev,
				"vortex_fifo_setadbctrl fail\n");
			अवरोध;
		पूर्ण
	पूर्ण
	जबतक (temp & FIFO_RDONLY);

	// AU8830 semes to take some special care about fअगरo content (data).
	// But i'm just to lazy to translate that :)
	अगर (valid) अणु
		अगर ((temp & FIFO_VALID) == 0) अणु
			//this_8[fअगरo] = 0;
			vortex_fअगरo_clearadbdata(vortex, fअगरo, FIFO_SIZE);	// this_4
#अगर_घोषित CHIP_AU8820
			temp = (this_4 & 0x1f) << 0xb;
#अन्यथा
			temp = (this_4 & 0x3f) << 0xc;
#पूर्ण_अगर
			temp = (temp & 0xfffffffd) | ((stereo & 1) << 1);
			temp = (temp & 0xfffffff3) | ((priority & 3) << 2);
			temp = (temp & 0xffffffef) | ((valid & 1) << 4);
			temp |= FIFO_U1;
			temp = (temp & 0xffffffdf) | ((empty & 1) << 5);
#अगर_घोषित CHIP_AU8820
			temp = (temp & 0xfffbffff) | ((f & 1) << 0x12);
#पूर्ण_अगर
#अगर_घोषित CHIP_AU8830
			temp = (temp & 0xf7ffffff) | ((f & 1) << 0x1b);
			temp = (temp & 0xefffffff) | ((f & 1) << 0x1c);
#पूर्ण_अगर
#अगर_घोषित CHIP_AU8810
			temp = (temp & 0xfeffffff) | ((f & 1) << 0x18);
			temp = (temp & 0xfdffffff) | ((f & 1) << 0x19);
#पूर्ण_अगर
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (temp & FIFO_VALID) अणु
#अगर_घोषित CHIP_AU8820
			temp = ((f & 1) << 0x12) | (temp & 0xfffbffef);
#पूर्ण_अगर
#अगर_घोषित CHIP_AU8830
			temp =
			    ((f & 1) << 0x1b) | (temp & 0xe7ffffef) | FIFO_BITS;
#पूर्ण_अगर
#अगर_घोषित CHIP_AU8810
			temp =
			    ((f & 1) << 0x18) | (temp & 0xfcffffef) | FIFO_BITS;
#पूर्ण_अगर
		पूर्ण अन्यथा
			/*अगर (this_8[fअगरo]) */
			vortex_fअगरo_clearadbdata(vortex, fअगरo, FIFO_SIZE);
	पूर्ण
	hwग_लिखो(vortex->mmio, VORTEX_FIFO_ADBCTRL + (fअगरo << 2), temp);
	hwपढ़ो(vortex->mmio, VORTEX_FIFO_ADBCTRL + (fअगरo << 2));
पूर्ण

#अगर_अघोषित CHIP_AU8810
अटल व्योम vortex_fअगरo_clearwtdata(vortex_t * vortex, पूर्णांक fअगरo, पूर्णांक x)
अणु
	अगर (x < 1)
		वापस;
	क्रम (x--; x >= 0; x--)
		hwग_लिखो(vortex->mmio,
			VORTEX_FIFO_WTDATA +
			(((fअगरo << FIFO_SIZE_BITS) + x) << 2), 0);
पूर्ण

अटल व्योम vortex_fअगरo_wtinitialize(vortex_t * vortex, पूर्णांक fअगरo, पूर्णांक j)
अणु
	vortex_fअगरo_clearwtdata(vortex, fअगरo, FIFO_SIZE);
#अगर_घोषित CHIP_AU8820
	hwग_लिखो(vortex->mmio, VORTEX_FIFO_WTCTRL + (fअगरo << 2),
		(FIFO_U1 | ((j & FIFO_MASK) << 0xb)));
#अन्यथा
	hwग_लिखो(vortex->mmio, VORTEX_FIFO_WTCTRL + (fअगरo << 2),
		(FIFO_U1 | ((j & FIFO_MASK) << 0xc)));
#पूर्ण_अगर
पूर्ण

अटल व्योम vortex_fअगरo_setwtvalid(vortex_t * vortex, पूर्णांक fअगरo, पूर्णांक en)
अणु
	hwग_लिखो(vortex->mmio, VORTEX_FIFO_WTCTRL + (fअगरo << 2),
		(hwपढ़ो(vortex->mmio, VORTEX_FIFO_WTCTRL + (fअगरo << 2)) &
		 0xffffffef) | ((en & 1) << 4) | FIFO_U1);
पूर्ण

अटल व्योम
vortex_fअगरo_setwtctrl(vortex_t * vortex, पूर्णांक fअगरo, पूर्णांक ctrl, पूर्णांक priority,
		      पूर्णांक empty, पूर्णांक valid, पूर्णांक f)
अणु
	पूर्णांक temp = 0, lअगरeboat = 0;
	पूर्णांक this_4 = 2;

	करो अणु
		temp = hwपढ़ो(vortex->mmio, VORTEX_FIFO_WTCTRL + (fअगरo << 2));
		अगर (lअगरeboat++ > 0xbb8) अणु
			dev_err(vortex->card->dev,
				"vortex_fifo_setwtctrl fail\n");
			अवरोध;
		पूर्ण
	पूर्ण
	जबतक (temp & FIFO_RDONLY);

	अगर (valid) अणु
		अगर ((temp & FIFO_VALID) == 0) अणु
			vortex_fअगरo_clearwtdata(vortex, fअगरo, FIFO_SIZE);	// this_4
#अगर_घोषित CHIP_AU8820
			temp = (this_4 & 0x1f) << 0xb;
#अन्यथा
			temp = (this_4 & 0x3f) << 0xc;
#पूर्ण_अगर
			temp = (temp & 0xfffffffd) | ((ctrl & 1) << 1);
			temp = (temp & 0xfffffff3) | ((priority & 3) << 2);
			temp = (temp & 0xffffffef) | ((valid & 1) << 4);
			temp |= FIFO_U1;
			temp = (temp & 0xffffffdf) | ((empty & 1) << 5);
#अगर_घोषित CHIP_AU8820
			temp = (temp & 0xfffbffff) | ((f & 1) << 0x12);
#पूर्ण_अगर
#अगर_घोषित CHIP_AU8830
			temp = (temp & 0xf7ffffff) | ((f & 1) << 0x1b);
			temp = (temp & 0xefffffff) | ((f & 1) << 0x1c);
#पूर्ण_अगर
#अगर_घोषित CHIP_AU8810
			temp = (temp & 0xfeffffff) | ((f & 1) << 0x18);
			temp = (temp & 0xfdffffff) | ((f & 1) << 0x19);
#पूर्ण_अगर
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (temp & FIFO_VALID) अणु
#अगर_घोषित CHIP_AU8820
			temp = ((f & 1) << 0x12) | (temp & 0xfffbffef);
#पूर्ण_अगर
#अगर_घोषित CHIP_AU8830
			temp =
			    ((f & 1) << 0x1b) | (temp & 0xe7ffffef) | FIFO_BITS;
#पूर्ण_अगर
#अगर_घोषित CHIP_AU8810
			temp =
			    ((f & 1) << 0x18) | (temp & 0xfcffffef) | FIFO_BITS;
#पूर्ण_अगर
		पूर्ण अन्यथा
			/*अगर (this_8[fअगरo]) */
			vortex_fअगरo_clearwtdata(vortex, fअगरo, FIFO_SIZE);
	पूर्ण
	hwग_लिखो(vortex->mmio, VORTEX_FIFO_WTCTRL + (fअगरo << 2), temp);
	hwपढ़ो(vortex->mmio, VORTEX_FIFO_WTCTRL + (fअगरo << 2));

/*	
    करो अणु
		temp = hwपढ़ो(vortex->mmio, VORTEX_FIFO_WTCTRL + (fअगरo << 2));
		अगर (lअगरeboat++ > 0xbb8) अणु
			pr_err( "Vortex: vortex_fifo_setwtctrl fail (hanging)\n");
			अवरोध;
		पूर्ण
    पूर्ण जबतक ((temp & FIFO_RDONLY)&&(temp & FIFO_VALID)&&(temp != 0xFFFFFFFF));
	
	
	अगर (valid) अणु
		अगर (temp & FIFO_VALID) अणु
			temp = 0x40000;
			//temp |= 0x08000000;
			//temp |= 0x10000000;
			//temp |= 0x04000000;
			//temp |= 0x00400000;
			temp |= 0x1c400000;
			temp &= 0xFFFFFFF3;
			temp &= 0xFFFFFFEF;
			temp |= (valid & 1) << 4;
			hwग_लिखो(vortex->mmio, VORTEX_FIFO_WTCTRL + (fअगरo << 2), temp);
			वापस;
		पूर्ण अन्यथा अणु
			vortex_fअगरo_clearwtdata(vortex, fअगरo, FIFO_SIZE);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		temp &= 0xffffffef;
		temp |= 0x08000000;
		temp |= 0x10000000;
		temp |= 0x04000000;
		temp |= 0x00400000;
		hwग_लिखो(vortex->mmio, VORTEX_FIFO_WTCTRL + (fअगरo << 2), temp);
		temp = hwपढ़ो(vortex->mmio, VORTEX_FIFO_WTCTRL + (fअगरo << 2));
		//((temp >> 6) & 0x3f) 
		
		priority = 0;
		अगर (((temp & 0x0fc0) ^ ((temp >> 6) & 0x0fc0)) & 0FFFFFFC0)
			vortex_fअगरo_clearwtdata(vortex, fअगरo, FIFO_SIZE);
		valid = 0xfb;
		temp = (temp & 0xfffffffd) | ((ctrl & 1) << 1);
		temp = (temp & 0xfffdffff) | ((f & 1) << 0x11);
		temp = (temp & 0xfffffff3) | ((priority & 3) << 2);
		temp = (temp & 0xffffffef) | ((valid & 1) << 4);
		temp = (temp & 0xffffffdf) | ((empty & 1) << 5);
		hwग_लिखो(vortex->mmio, VORTEX_FIFO_WTCTRL + (fअगरo << 2), temp);
	पूर्ण
	
	*/

	/*
	   temp = (temp & 0xfffffffd) | ((ctrl & 1) << 1);
	   temp = (temp & 0xfffdffff) | ((f & 1) << 0x11);
	   temp = (temp & 0xfffffff3) | ((priority & 3) << 2);
	   temp = (temp & 0xffffffef) | ((valid & 1) << 4);
	   temp = (temp & 0xffffffdf) | ((empty & 1) << 5);
	   #अगर_घोषित FIFO_BITS
	   temp = temp | FIFO_BITS | 40000;
	   #पूर्ण_अगर
	   // 0x1c440010, 0x1c400000
	   hwग_लिखो(vortex->mmio, VORTEX_FIFO_WTCTRL + (fअगरo << 2), temp);
	 */
पूर्ण

#पूर्ण_अगर
अटल व्योम vortex_fअगरo_init(vortex_t * vortex)
अणु
	पूर्णांक x;
	u32 addr;

	/* ADB DMA channels fअगरos. */
	addr = VORTEX_FIFO_ADBCTRL + ((NR_ADB - 1) * 4);
	क्रम (x = NR_ADB - 1; x >= 0; x--) अणु
		hwग_लिखो(vortex->mmio, addr, (FIFO_U0 | FIFO_U1));
		अगर (hwपढ़ो(vortex->mmio, addr) != (FIFO_U0 | FIFO_U1))
			dev_err(vortex->card->dev, "bad adb fifo reset!\n");
		vortex_fअगरo_clearadbdata(vortex, x, FIFO_SIZE);
		addr -= 4;
	पूर्ण

#अगर_अघोषित CHIP_AU8810
	/* WT DMA channels fअगरos. */
	addr = VORTEX_FIFO_WTCTRL + ((NR_WT - 1) * 4);
	क्रम (x = NR_WT - 1; x >= 0; x--) अणु
		hwग_लिखो(vortex->mmio, addr, FIFO_U0);
		अगर (hwपढ़ो(vortex->mmio, addr) != FIFO_U0)
			dev_err(vortex->card->dev,
				"bad wt fifo reset (0x%08x, 0x%08x)!\n",
				addr, hwपढ़ो(vortex->mmio, addr));
		vortex_fअगरo_clearwtdata(vortex, x, FIFO_SIZE);
		addr -= 4;
	पूर्ण
#पूर्ण_अगर
	/* trigger... */
#अगर_घोषित CHIP_AU8820
	hwग_लिखो(vortex->mmio, 0xf8c0, 0xd03);	//0x0843 0xd6b
#अन्यथा
#अगर_घोषित CHIP_AU8830
	hwग_लिखो(vortex->mmio, 0x17000, 0x61);	/* wt a */
	hwग_लिखो(vortex->mmio, 0x17004, 0x61);	/* wt b */
#पूर्ण_अगर
	hwग_लिखो(vortex->mmio, 0x17008, 0x61);	/* adb */
#पूर्ण_अगर
पूर्ण

/* ADBDMA */

अटल व्योम vortex_adbdma_init(vortex_t * vortex)
अणु
पूर्ण

अटल व्योम vortex_adbdma_setfirstbuffer(vortex_t * vortex, पूर्णांक adbdma)
अणु
	stream_t *dma = &vortex->dma_adb[adbdma];

	hwग_लिखो(vortex->mmio, VORTEX_ADBDMA_CTRL + (adbdma << 2),
		dma->dma_ctrl);
पूर्ण

अटल व्योम vortex_adbdma_setstartbuffer(vortex_t * vortex, पूर्णांक adbdma, पूर्णांक sb)
अणु
	stream_t *dma = &vortex->dma_adb[adbdma];
	//hwग_लिखो(vortex->mmio, VORTEX_ADBDMA_START + (adbdma << 2), sb << (((NR_ADB-1)-((adbdma&0xf)*2))));
	hwग_लिखो(vortex->mmio, VORTEX_ADBDMA_START + (adbdma << 2),
		sb << ((0xf - (adbdma & 0xf)) * 2));
	dma->period_real = dma->period_virt = sb;
पूर्ण

अटल व्योम
vortex_adbdma_रखो_बफfers(vortex_t * vortex, पूर्णांक adbdma,
			 पूर्णांक psize, पूर्णांक count)
अणु
	stream_t *dma = &vortex->dma_adb[adbdma];

	dma->period_bytes = psize;
	dma->nr_periods = count;

	dma->cfg0 = 0;
	dma->cfg1 = 0;
	चयन (count) अणु
		/* Four or more pages */
	शेष:
	हाल 4:
		dma->cfg1 |= 0x88000000 | 0x44000000 | 0x30000000 | (psize - 1);
		hwग_लिखो(vortex->mmio,
			VORTEX_ADBDMA_BUFBASE + (adbdma << 4) + 0xc,
			snd_pcm_sgbuf_get_addr(dma->substream, psize * 3));
		fallthrough;
		/* 3 pages */
	हाल 3:
		dma->cfg0 |= 0x12000000;
		dma->cfg1 |= 0x80000000 | 0x40000000 | ((psize - 1) << 0xc);
		hwग_लिखो(vortex->mmio,
			VORTEX_ADBDMA_BUFBASE + (adbdma << 4) + 0x8,
			snd_pcm_sgbuf_get_addr(dma->substream, psize * 2));
		fallthrough;
		/* 2 pages */
	हाल 2:
		dma->cfg0 |= 0x88000000 | 0x44000000 | 0x10000000 | (psize - 1);
		hwग_लिखो(vortex->mmio,
			VORTEX_ADBDMA_BUFBASE + (adbdma << 4) + 0x4,
			snd_pcm_sgbuf_get_addr(dma->substream, psize));
		fallthrough;
		/* 1 page */
	हाल 1:
		dma->cfg0 |= 0x80000000 | 0x40000000 | ((psize - 1) << 0xc);
		hwग_लिखो(vortex->mmio,
			VORTEX_ADBDMA_BUFBASE + (adbdma << 4),
			snd_pcm_sgbuf_get_addr(dma->substream, 0));
		अवरोध;
	पूर्ण
	/*
	pr_debug( "vortex: cfg0 = 0x%x\nvortex: cfg1=0x%x\n",
	       dma->cfg0, dma->cfg1);
	*/
	hwग_लिखो(vortex->mmio, VORTEX_ADBDMA_BUFCFG0 + (adbdma << 3), dma->cfg0);
	hwग_लिखो(vortex->mmio, VORTEX_ADBDMA_BUFCFG1 + (adbdma << 3), dma->cfg1);

	vortex_adbdma_setfirstbuffer(vortex, adbdma);
	vortex_adbdma_setstartbuffer(vortex, adbdma, 0);
पूर्ण

अटल व्योम
vortex_adbdma_seपंचांगode(vortex_t * vortex, पूर्णांक adbdma, पूर्णांक ie, पूर्णांक dir,
		      पूर्णांक fmt, पूर्णांक stereo, u32 offset)
अणु
	stream_t *dma = &vortex->dma_adb[adbdma];

	dma->dma_unknown = stereo;
	dma->dma_ctrl =
	    ((offset & OFFSET_MASK) | (dma->dma_ctrl & ~OFFSET_MASK));
	/* Enable PCMOUT पूर्णांकerrupts. */
	dma->dma_ctrl =
	    (dma->dma_ctrl & ~IE_MASK) | ((ie << IE_SHIFT) & IE_MASK);

	dma->dma_ctrl =
	    (dma->dma_ctrl & ~सूची_MASK) | ((dir << सूची_SHIFT) & सूची_MASK);
	dma->dma_ctrl =
	    (dma->dma_ctrl & ~FMT_MASK) | ((fmt << FMT_SHIFT) & FMT_MASK);

	hwग_लिखो(vortex->mmio, VORTEX_ADBDMA_CTRL + (adbdma << 2),
		dma->dma_ctrl);
	hwपढ़ो(vortex->mmio, VORTEX_ADBDMA_CTRL + (adbdma << 2));
पूर्ण

अटल पूर्णांक vortex_adbdma_bufshअगरt(vortex_t * vortex, पूर्णांक adbdma)
अणु
	stream_t *dma = &vortex->dma_adb[adbdma];
	पूर्णांक page, p, pp, delta, i;

	page =
	    (hwपढ़ो(vortex->mmio, VORTEX_ADBDMA_STAT + (adbdma << 2)) &
	     ADB_SUBBUF_MASK) >> ADB_SUBBUF_SHIFT;
	अगर (dma->nr_periods >= 4)
		delta = (page - dma->period_real) & 3;
	अन्यथा अणु
		delta = (page - dma->period_real);
		अगर (delta < 0)
			delta += dma->nr_periods;
	पूर्ण
	अगर (delta == 0)
		वापस 0;

	/* refresh hw page table */
	अगर (dma->nr_periods > 4) अणु
		क्रम (i = 0; i < delta; i++) अणु
			/* p: audio buffer page index */
			p = dma->period_virt + i + 4;
			अगर (p >= dma->nr_periods)
				p -= dma->nr_periods;
			/* pp: hardware DMA page index. */
			pp = dma->period_real + i;
			अगर (pp >= 4)
				pp -= 4;
			//hwग_लिखो(vortex->mmio, VORTEX_ADBDMA_BUFBASE+(((adbdma << 2)+pp) << 2), dma->table[p].addr);
			hwग_लिखो(vortex->mmio,
				VORTEX_ADBDMA_BUFBASE + (((adbdma << 2) + pp) << 2),
				snd_pcm_sgbuf_get_addr(dma->substream,
				dma->period_bytes * p));
			/* Force ग_लिखो thru cache. */
			hwपढ़ो(vortex->mmio, VORTEX_ADBDMA_BUFBASE +
			       (((adbdma << 2) + pp) << 2));
		पूर्ण
	पूर्ण
	dma->period_virt += delta;
	dma->period_real = page;
	अगर (dma->period_virt >= dma->nr_periods)
		dma->period_virt -= dma->nr_periods;
	अगर (delta != 1)
		dev_info(vortex->card->dev,
			 "%d virt=%d, real=%d, delta=%d\n",
			 adbdma, dma->period_virt, dma->period_real, delta);

	वापस delta;
पूर्ण


अटल व्योम vortex_adbdma_resetup(vortex_t *vortex, पूर्णांक adbdma) अणु
	stream_t *dma = &vortex->dma_adb[adbdma];
	पूर्णांक p, pp, i;

	/* refresh hw page table */
	क्रम (i=0 ; i < 4 && i < dma->nr_periods; i++) अणु
		/* p: audio buffer page index */
		p = dma->period_virt + i;
		अगर (p >= dma->nr_periods)
			p -= dma->nr_periods;
		/* pp: hardware DMA page index. */
		pp = dma->period_real + i;
		अगर (dma->nr_periods < 4) अणु
			अगर (pp >= dma->nr_periods)
				pp -= dma->nr_periods;
		पूर्ण
		अन्यथा अणु
			अगर (pp >= 4)
				pp -= 4;
		पूर्ण
		hwग_लिखो(vortex->mmio,
			VORTEX_ADBDMA_BUFBASE + (((adbdma << 2) + pp) << 2),
			snd_pcm_sgbuf_get_addr(dma->substream,
					       dma->period_bytes * p));
		/* Force ग_लिखो thru cache. */
		hwपढ़ो(vortex->mmio, VORTEX_ADBDMA_BUFBASE + (((adbdma << 2)+pp) << 2));
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक vortex_adbdma_getlinearpos(vortex_t * vortex, पूर्णांक adbdma)
अणु
	stream_t *dma = &vortex->dma_adb[adbdma];
	पूर्णांक temp, page, delta;

	temp = hwपढ़ो(vortex->mmio, VORTEX_ADBDMA_STAT + (adbdma << 2));
	page = (temp & ADB_SUBBUF_MASK) >> ADB_SUBBUF_SHIFT;
	अगर (dma->nr_periods >= 4)
		delta = (page - dma->period_real) & 3;
	अन्यथा अणु
		delta = (page - dma->period_real);
		अगर (delta < 0)
			delta += dma->nr_periods;
	पूर्ण
	वापस (dma->period_virt + delta) * dma->period_bytes
		+ (temp & (dma->period_bytes - 1));
पूर्ण

अटल व्योम vortex_adbdma_startfअगरo(vortex_t * vortex, पूर्णांक adbdma)
अणु
	पूर्णांक this_8 = 0 /*empty */ , this_4 = 0 /*priority */ ;
	stream_t *dma = &vortex->dma_adb[adbdma];

	चयन (dma->fअगरo_status) अणु
	हाल FIFO_START:
		vortex_fअगरo_setadbvalid(vortex, adbdma,
					dma->fअगरo_enabled ? 1 : 0);
		अवरोध;
	हाल FIFO_STOP:
		this_8 = 1;
		hwग_लिखो(vortex->mmio, VORTEX_ADBDMA_CTRL + (adbdma << 2),
			dma->dma_ctrl);
		vortex_fअगरo_setadbctrl(vortex, adbdma, dma->dma_unknown,
				       this_4, this_8,
				       dma->fअगरo_enabled ? 1 : 0, 0);
		अवरोध;
	हाल FIFO_PAUSE:
		vortex_fअगरo_setadbctrl(vortex, adbdma, dma->dma_unknown,
				       this_4, this_8,
				       dma->fअगरo_enabled ? 1 : 0, 0);
		अवरोध;
	पूर्ण
	dma->fअगरo_status = FIFO_START;
पूर्ण

अटल व्योम vortex_adbdma_resumefअगरo(vortex_t * vortex, पूर्णांक adbdma)
अणु
	stream_t *dma = &vortex->dma_adb[adbdma];

	पूर्णांक this_8 = 1, this_4 = 0;
	चयन (dma->fअगरo_status) अणु
	हाल FIFO_STOP:
		hwग_लिखो(vortex->mmio, VORTEX_ADBDMA_CTRL + (adbdma << 2),
			dma->dma_ctrl);
		vortex_fअगरo_setadbctrl(vortex, adbdma, dma->dma_unknown,
				       this_4, this_8,
				       dma->fअगरo_enabled ? 1 : 0, 0);
		अवरोध;
	हाल FIFO_PAUSE:
		vortex_fअगरo_setadbctrl(vortex, adbdma, dma->dma_unknown,
				       this_4, this_8,
				       dma->fअगरo_enabled ? 1 : 0, 0);
		अवरोध;
	पूर्ण
	dma->fअगरo_status = FIFO_START;
पूर्ण

अटल व्योम vortex_adbdma_छोड़ोfअगरo(vortex_t * vortex, पूर्णांक adbdma)
अणु
	stream_t *dma = &vortex->dma_adb[adbdma];

	पूर्णांक this_8 = 0, this_4 = 0;
	चयन (dma->fअगरo_status) अणु
	हाल FIFO_START:
		vortex_fअगरo_setadbctrl(vortex, adbdma, dma->dma_unknown,
				       this_4, this_8, 0, 0);
		अवरोध;
	हाल FIFO_STOP:
		hwग_लिखो(vortex->mmio, VORTEX_ADBDMA_CTRL + (adbdma << 2),
			dma->dma_ctrl);
		vortex_fअगरo_setadbctrl(vortex, adbdma, dma->dma_unknown,
				       this_4, this_8, 0, 0);
		अवरोध;
	पूर्ण
	dma->fअगरo_status = FIFO_PAUSE;
पूर्ण

अटल व्योम vortex_adbdma_stopfअगरo(vortex_t * vortex, पूर्णांक adbdma)
अणु
	stream_t *dma = &vortex->dma_adb[adbdma];

	पूर्णांक this_4 = 0, this_8 = 0;
	अगर (dma->fअगरo_status == FIFO_START)
		vortex_fअगरo_setadbctrl(vortex, adbdma, dma->dma_unknown,
				       this_4, this_8, 0, 0);
	अन्यथा अगर (dma->fअगरo_status == FIFO_STOP)
		वापस;
	dma->fअगरo_status = FIFO_STOP;
	dma->fअगरo_enabled = 0;
पूर्ण

/* WTDMA */

#अगर_अघोषित CHIP_AU8810
अटल व्योम vortex_wtdma_setfirstbuffer(vortex_t * vortex, पूर्णांक wtdma)
अणु
	//पूर्णांक this_7c=dma_ctrl;
	stream_t *dma = &vortex->dma_wt[wtdma];

	hwग_लिखो(vortex->mmio, VORTEX_WTDMA_CTRL + (wtdma << 2), dma->dma_ctrl);
पूर्ण

अटल व्योम vortex_wtdma_setstartbuffer(vortex_t * vortex, पूर्णांक wtdma, पूर्णांक sb)
अणु
	stream_t *dma = &vortex->dma_wt[wtdma];
	//hwग_लिखो(vortex->mmio, VORTEX_WTDMA_START + (wtdma << 2), sb << ((0x1f-(wtdma&0xf)*2)));
	hwग_लिखो(vortex->mmio, VORTEX_WTDMA_START + (wtdma << 2),
		sb << ((0xf - (wtdma & 0xf)) * 2));
	dma->period_real = dma->period_virt = sb;
पूर्ण

अटल व्योम
vortex_wtdma_रखो_बफfers(vortex_t * vortex, पूर्णांक wtdma,
			पूर्णांक psize, पूर्णांक count)
अणु
	stream_t *dma = &vortex->dma_wt[wtdma];

	dma->period_bytes = psize;
	dma->nr_periods = count;

	dma->cfg0 = 0;
	dma->cfg1 = 0;
	चयन (count) अणु
		/* Four or more pages */
	शेष:
	हाल 4:
		dma->cfg1 |= 0x88000000 | 0x44000000 | 0x30000000 | (psize-1);
		hwग_लिखो(vortex->mmio, VORTEX_WTDMA_BUFBASE + (wtdma << 4) + 0xc,
			snd_pcm_sgbuf_get_addr(dma->substream, psize * 3));
		fallthrough;
		/* 3 pages */
	हाल 3:
		dma->cfg0 |= 0x12000000;
		dma->cfg1 |= 0x80000000 | 0x40000000 | ((psize-1) << 0xc);
		hwग_लिखो(vortex->mmio, VORTEX_WTDMA_BUFBASE + (wtdma << 4)  + 0x8,
			snd_pcm_sgbuf_get_addr(dma->substream, psize * 2));
		fallthrough;
		/* 2 pages */
	हाल 2:
		dma->cfg0 |= 0x88000000 | 0x44000000 | 0x10000000 | (psize-1);
		hwग_लिखो(vortex->mmio, VORTEX_WTDMA_BUFBASE + (wtdma << 4) + 0x4,
			snd_pcm_sgbuf_get_addr(dma->substream, psize));
		fallthrough;
		/* 1 page */
	हाल 1:
		dma->cfg0 |= 0x80000000 | 0x40000000 | ((psize-1) << 0xc);
		hwग_लिखो(vortex->mmio, VORTEX_WTDMA_BUFBASE + (wtdma << 4),
			snd_pcm_sgbuf_get_addr(dma->substream, 0));
		अवरोध;
	पूर्ण
	hwग_लिखो(vortex->mmio, VORTEX_WTDMA_BUFCFG0 + (wtdma << 3), dma->cfg0);
	hwग_लिखो(vortex->mmio, VORTEX_WTDMA_BUFCFG1 + (wtdma << 3), dma->cfg1);

	vortex_wtdma_setfirstbuffer(vortex, wtdma);
	vortex_wtdma_setstartbuffer(vortex, wtdma, 0);
पूर्ण

अटल व्योम
vortex_wtdma_seपंचांगode(vortex_t * vortex, पूर्णांक wtdma, पूर्णांक ie, पूर्णांक fmt, पूर्णांक d,
		     /*पूर्णांक e, */ u32 offset)
अणु
	stream_t *dma = &vortex->dma_wt[wtdma];

	//dma->this_08 = e;
	dma->dma_unknown = d;
	dma->dma_ctrl = 0;
	dma->dma_ctrl =
	    ((offset & OFFSET_MASK) | (dma->dma_ctrl & ~OFFSET_MASK));
	/* PCMOUT पूर्णांकerrupt */
	dma->dma_ctrl =
	    (dma->dma_ctrl & ~IE_MASK) | ((ie << IE_SHIFT) & IE_MASK);
	/* Always playback. */
	dma->dma_ctrl |= (1 << सूची_SHIFT);
	/* Audio Format */
	dma->dma_ctrl =
	    (dma->dma_ctrl & FMT_MASK) | ((fmt << FMT_SHIFT) & FMT_MASK);
	/* Write पूर्णांकo hardware */
	hwग_लिखो(vortex->mmio, VORTEX_WTDMA_CTRL + (wtdma << 2), dma->dma_ctrl);
पूर्ण

अटल पूर्णांक vortex_wtdma_bufshअगरt(vortex_t * vortex, पूर्णांक wtdma)
अणु
	stream_t *dma = &vortex->dma_wt[wtdma];
	पूर्णांक page, p, pp, delta, i;

	page =
	    (hwपढ़ो(vortex->mmio, VORTEX_WTDMA_STAT + (wtdma << 2))
	     >> WT_SUBBUF_SHIFT) & WT_SUBBUF_MASK;
	अगर (dma->nr_periods >= 4)
		delta = (page - dma->period_real) & 3;
	अन्यथा अणु
		delta = (page - dma->period_real);
		अगर (delta < 0)
			delta += dma->nr_periods;
	पूर्ण
	अगर (delta == 0)
		वापस 0;

	/* refresh hw page table */
	अगर (dma->nr_periods > 4) अणु
		क्रम (i = 0; i < delta; i++) अणु
			/* p: audio buffer page index */
			p = dma->period_virt + i + 4;
			अगर (p >= dma->nr_periods)
				p -= dma->nr_periods;
			/* pp: hardware DMA page index. */
			pp = dma->period_real + i;
			अगर (pp >= 4)
				pp -= 4;
			hwग_लिखो(vortex->mmio,
				VORTEX_WTDMA_BUFBASE +
				(((wtdma << 2) + pp) << 2),
				snd_pcm_sgbuf_get_addr(dma->substream,
						       dma->period_bytes * p));
			/* Force ग_लिखो thru cache. */
			hwपढ़ो(vortex->mmio, VORTEX_WTDMA_BUFBASE +
			       (((wtdma << 2) + pp) << 2));
		पूर्ण
	पूर्ण
	dma->period_virt += delta;
	अगर (dma->period_virt >= dma->nr_periods)
		dma->period_virt -= dma->nr_periods;
	dma->period_real = page;

	अगर (delta != 1)
		dev_warn(vortex->card->dev, "wt virt = %d, delta = %d\n",
			 dma->period_virt, delta);

	वापस delta;
पूर्ण

#अगर 0
अटल व्योम
vortex_wtdma_getposition(vortex_t * vortex, पूर्णांक wtdma, पूर्णांक *subbuf, पूर्णांक *pos)
अणु
	पूर्णांक temp;
	temp = hwपढ़ो(vortex->mmio, VORTEX_WTDMA_STAT + (wtdma << 2));
	*subbuf = (temp >> WT_SUBBUF_SHIFT) & WT_SUBBUF_MASK;
	*pos = temp & POS_MASK;
पूर्ण

अटल पूर्णांक vortex_wtdma_अ_लोursubuffer(vortex_t * vortex, पूर्णांक wtdma)
अणु
	वापस ((hwपढ़ो(vortex->mmio, VORTEX_WTDMA_STAT + (wtdma << 2)) >>
		 POS_SHIFT) & POS_MASK);
पूर्ण
#पूर्ण_अगर
अटल अंतरभूत पूर्णांक vortex_wtdma_getlinearpos(vortex_t * vortex, पूर्णांक wtdma)
अणु
	stream_t *dma = &vortex->dma_wt[wtdma];
	पूर्णांक temp;

	temp = hwपढ़ो(vortex->mmio, VORTEX_WTDMA_STAT + (wtdma << 2));
	temp = (dma->period_virt * dma->period_bytes) + (temp & (dma->period_bytes - 1));
	वापस temp;
पूर्ण

अटल व्योम vortex_wtdma_startfअगरo(vortex_t * vortex, पूर्णांक wtdma)
अणु
	stream_t *dma = &vortex->dma_wt[wtdma];
	पूर्णांक this_8 = 0, this_4 = 0;

	चयन (dma->fअगरo_status) अणु
	हाल FIFO_START:
		vortex_fअगरo_setwtvalid(vortex, wtdma,
				       dma->fअगरo_enabled ? 1 : 0);
		अवरोध;
	हाल FIFO_STOP:
		this_8 = 1;
		hwग_लिखो(vortex->mmio, VORTEX_WTDMA_CTRL + (wtdma << 2),
			dma->dma_ctrl);
		vortex_fअगरo_setwtctrl(vortex, wtdma, dma->dma_unknown,
				      this_4, this_8,
				      dma->fअगरo_enabled ? 1 : 0, 0);
		अवरोध;
	हाल FIFO_PAUSE:
		vortex_fअगरo_setwtctrl(vortex, wtdma, dma->dma_unknown,
				      this_4, this_8,
				      dma->fअगरo_enabled ? 1 : 0, 0);
		अवरोध;
	पूर्ण
	dma->fअगरo_status = FIFO_START;
पूर्ण

अटल व्योम vortex_wtdma_resumefअगरo(vortex_t * vortex, पूर्णांक wtdma)
अणु
	stream_t *dma = &vortex->dma_wt[wtdma];

	पूर्णांक this_8 = 0, this_4 = 0;
	चयन (dma->fअगरo_status) अणु
	हाल FIFO_STOP:
		hwग_लिखो(vortex->mmio, VORTEX_WTDMA_CTRL + (wtdma << 2),
			dma->dma_ctrl);
		vortex_fअगरo_setwtctrl(vortex, wtdma, dma->dma_unknown,
				      this_4, this_8,
				      dma->fअगरo_enabled ? 1 : 0, 0);
		अवरोध;
	हाल FIFO_PAUSE:
		vortex_fअगरo_setwtctrl(vortex, wtdma, dma->dma_unknown,
				      this_4, this_8,
				      dma->fअगरo_enabled ? 1 : 0, 0);
		अवरोध;
	पूर्ण
	dma->fअगरo_status = FIFO_START;
पूर्ण

अटल व्योम vortex_wtdma_छोड़ोfअगरo(vortex_t * vortex, पूर्णांक wtdma)
अणु
	stream_t *dma = &vortex->dma_wt[wtdma];

	पूर्णांक this_8 = 0, this_4 = 0;
	चयन (dma->fअगरo_status) अणु
	हाल FIFO_START:
		vortex_fअगरo_setwtctrl(vortex, wtdma, dma->dma_unknown,
				      this_4, this_8, 0, 0);
		अवरोध;
	हाल FIFO_STOP:
		hwग_लिखो(vortex->mmio, VORTEX_WTDMA_CTRL + (wtdma << 2),
			dma->dma_ctrl);
		vortex_fअगरo_setwtctrl(vortex, wtdma, dma->dma_unknown,
				      this_4, this_8, 0, 0);
		अवरोध;
	पूर्ण
	dma->fअगरo_status = FIFO_PAUSE;
पूर्ण

अटल व्योम vortex_wtdma_stopfअगरo(vortex_t * vortex, पूर्णांक wtdma)
अणु
	stream_t *dma = &vortex->dma_wt[wtdma];

	पूर्णांक this_4 = 0, this_8 = 0;
	अगर (dma->fअगरo_status == FIFO_START)
		vortex_fअगरo_setwtctrl(vortex, wtdma, dma->dma_unknown,
				      this_4, this_8, 0, 0);
	अन्यथा अगर (dma->fअगरo_status == FIFO_STOP)
		वापस;
	dma->fअगरo_status = FIFO_STOP;
	dma->fअगरo_enabled = 0;
पूर्ण

#पूर्ण_अगर
/* ADB Routes */

प्रकार पूर्णांक ADBRamLink;
अटल व्योम vortex_adb_init(vortex_t * vortex)
अणु
	पूर्णांक i;
	/* it looks like we are writing more than we need to...
	 * अगर we ग_लिखो what we are supposed to it अवरोधs things... */
	hwग_लिखो(vortex->mmio, VORTEX_ADB_SR, 0);
	क्रम (i = 0; i < VORTEX_ADB_RTBASE_COUNT; i++)
		hwग_लिखो(vortex->mmio, VORTEX_ADB_RTBASE + (i << 2),
			hwपढ़ो(vortex->mmio,
			       VORTEX_ADB_RTBASE + (i << 2)) | ROUTE_MASK);
	क्रम (i = 0; i < VORTEX_ADB_CHNBASE_COUNT; i++) अणु
		hwग_लिखो(vortex->mmio, VORTEX_ADB_CHNBASE + (i << 2),
			hwपढ़ो(vortex->mmio,
			       VORTEX_ADB_CHNBASE + (i << 2)) | ROUTE_MASK);
	पूर्ण
पूर्ण

अटल व्योम vortex_adb_en_sr(vortex_t * vortex, पूर्णांक channel)
अणु
	hwग_लिखो(vortex->mmio, VORTEX_ADB_SR,
		hwपढ़ो(vortex->mmio, VORTEX_ADB_SR) | (0x1 << channel));
पूर्ण

अटल व्योम vortex_adb_dis_sr(vortex_t * vortex, पूर्णांक channel)
अणु
	hwग_लिखो(vortex->mmio, VORTEX_ADB_SR,
		hwपढ़ो(vortex->mmio, VORTEX_ADB_SR) & ~(0x1 << channel));
पूर्ण

अटल व्योम
vortex_adb_addroutes(vortex_t * vortex, अचिन्हित अक्षर channel,
		     ADBRamLink * route, पूर्णांक rnum)
अणु
	पूर्णांक temp, prev, lअगरeboat = 0;

	अगर ((rnum <= 0) || (route == शून्य))
		वापस;
	/* Write last routes. */
	rnum--;
	hwग_लिखो(vortex->mmio,
		VORTEX_ADB_RTBASE + ((route[rnum] & ADB_MASK) << 2),
		ROUTE_MASK);
	जबतक (rnum > 0) अणु
		hwग_लिखो(vortex->mmio,
			VORTEX_ADB_RTBASE +
			((route[rnum - 1] & ADB_MASK) << 2), route[rnum]);
		rnum--;
	पूर्ण
	/* Write first route. */
	temp =
	    hwपढ़ो(vortex->mmio,
		   VORTEX_ADB_CHNBASE + (channel << 2)) & ADB_MASK;
	अगर (temp == ADB_MASK) अणु
		/* First entry on this channel. */
		hwग_लिखो(vortex->mmio, VORTEX_ADB_CHNBASE + (channel << 2),
			route[0]);
		vortex_adb_en_sr(vortex, channel);
		वापस;
	पूर्ण
	/* Not first entry on this channel. Need to link. */
	करो अणु
		prev = temp;
		temp =
		    hwपढ़ो(vortex->mmio,
			   VORTEX_ADB_RTBASE + (temp << 2)) & ADB_MASK;
		अगर ((lअगरeboat++) > ADB_MASK) अणु
			dev_err(vortex->card->dev,
				"vortex_adb_addroutes: unending route! 0x%x\n",
				*route);
			वापस;
		पूर्ण
	पूर्ण
	जबतक (temp != ADB_MASK);
	hwग_लिखो(vortex->mmio, VORTEX_ADB_RTBASE + (prev << 2), route[0]);
पूर्ण

अटल व्योम
vortex_adb_delroutes(vortex_t * vortex, अचिन्हित अक्षर channel,
		     ADBRamLink route0, ADBRamLink route1)
अणु
	पूर्णांक temp, lअगरeboat = 0, prev;

	/* Find route. */
	temp =
	    hwपढ़ो(vortex->mmio,
		   VORTEX_ADB_CHNBASE + (channel << 2)) & ADB_MASK;
	अगर (temp == (route0 & ADB_MASK)) अणु
		temp =
		    hwपढ़ो(vortex->mmio,
			   VORTEX_ADB_RTBASE + ((route1 & ADB_MASK) << 2));
		अगर ((temp & ADB_MASK) == ADB_MASK)
			vortex_adb_dis_sr(vortex, channel);
		hwग_लिखो(vortex->mmio, VORTEX_ADB_CHNBASE + (channel << 2),
			temp);
		वापस;
	पूर्ण
	करो अणु
		prev = temp;
		temp =
		    hwपढ़ो(vortex->mmio,
			   VORTEX_ADB_RTBASE + (prev << 2)) & ADB_MASK;
		अगर (((lअगरeboat++) > ADB_MASK) || (temp == ADB_MASK)) अणु
			dev_err(vortex->card->dev,
				"vortex_adb_delroutes: route not found! 0x%x\n",
				route0);
			वापस;
		पूर्ण
	पूर्ण
	जबतक (temp != (route0 & ADB_MASK));
	temp = hwपढ़ो(vortex->mmio, VORTEX_ADB_RTBASE + (temp << 2));
	अगर ((temp & ADB_MASK) == route1)
		temp = hwपढ़ो(vortex->mmio, VORTEX_ADB_RTBASE + (temp << 2));
	/* Make bridge over deleted route. */
	hwग_लिखो(vortex->mmio, VORTEX_ADB_RTBASE + (prev << 2), temp);
पूर्ण

अटल व्योम
vortex_route(vortex_t * vortex, पूर्णांक en, अचिन्हित अक्षर channel,
	     अचिन्हित अक्षर source, अचिन्हित अक्षर dest)
अणु
	ADBRamLink route;

	route = ((source & ADB_MASK) << ADB_SHIFT) | (dest & ADB_MASK);
	अगर (en) अणु
		vortex_adb_addroutes(vortex, channel, &route, 1);
		अगर ((source < (OFFSET_SRCOUT + NR_SRC))
		    && (source >= OFFSET_SRCOUT))
			vortex_src_addWTD(vortex, (source - OFFSET_SRCOUT),
					  channel);
		अन्यथा अगर ((source < (OFFSET_MIXOUT + NR_MIXOUT))
			 && (source >= OFFSET_MIXOUT))
			vortex_mixer_addWTD(vortex,
					    (source - OFFSET_MIXOUT), channel);
	पूर्ण अन्यथा अणु
		vortex_adb_delroutes(vortex, channel, route, route);
		अगर ((source < (OFFSET_SRCOUT + NR_SRC))
		    && (source >= OFFSET_SRCOUT))
			vortex_src_delWTD(vortex, (source - OFFSET_SRCOUT),
					  channel);
		अन्यथा अगर ((source < (OFFSET_MIXOUT + NR_MIXOUT))
			 && (source >= OFFSET_MIXOUT))
			vortex_mixer_delWTD(vortex,
					    (source - OFFSET_MIXOUT), channel);
	पूर्ण
पूर्ण

#अगर 0
अटल व्योम
vortex_routes(vortex_t * vortex, पूर्णांक en, अचिन्हित अक्षर channel,
	      अचिन्हित अक्षर source, अचिन्हित अक्षर dest0, अचिन्हित अक्षर dest1)
अणु
	ADBRamLink route[2];

	route[0] = ((source & ADB_MASK) << ADB_SHIFT) | (dest0 & ADB_MASK);
	route[1] = ((source & ADB_MASK) << ADB_SHIFT) | (dest1 & ADB_MASK);

	अगर (en) अणु
		vortex_adb_addroutes(vortex, channel, route, 2);
		अगर ((source < (OFFSET_SRCOUT + NR_SRC))
		    && (source >= (OFFSET_SRCOUT)))
			vortex_src_addWTD(vortex, (source - OFFSET_SRCOUT),
					  channel);
		अन्यथा अगर ((source < (OFFSET_MIXOUT + NR_MIXOUT))
			 && (source >= (OFFSET_MIXOUT)))
			vortex_mixer_addWTD(vortex,
					    (source - OFFSET_MIXOUT), channel);
	पूर्ण अन्यथा अणु
		vortex_adb_delroutes(vortex, channel, route[0], route[1]);
		अगर ((source < (OFFSET_SRCOUT + NR_SRC))
		    && (source >= (OFFSET_SRCOUT)))
			vortex_src_delWTD(vortex, (source - OFFSET_SRCOUT),
					  channel);
		अन्यथा अगर ((source < (OFFSET_MIXOUT + NR_MIXOUT))
			 && (source >= (OFFSET_MIXOUT)))
			vortex_mixer_delWTD(vortex,
					    (source - OFFSET_MIXOUT), channel);
	पूर्ण
पूर्ण

#पूर्ण_अगर
/* Route two sources to same target. Sources must be of same class !!! */
अटल व्योम
vortex_routeLRT(vortex_t * vortex, पूर्णांक en, अचिन्हित अक्षर ch,
		अचिन्हित अक्षर source0, अचिन्हित अक्षर source1,
		अचिन्हित अक्षर dest)
अणु
	ADBRamLink route[2];

	route[0] = ((source0 & ADB_MASK) << ADB_SHIFT) | (dest & ADB_MASK);
	route[1] = ((source1 & ADB_MASK) << ADB_SHIFT) | (dest & ADB_MASK);

	अगर (dest < 0x10)
		route[1] = (route[1] & ~ADB_MASK) | (dest + 0x20);	/* fअगरo A */

	अगर (en) अणु
		vortex_adb_addroutes(vortex, ch, route, 2);
		अगर ((source0 < (OFFSET_SRCOUT + NR_SRC))
		    && (source0 >= OFFSET_SRCOUT)) अणु
			vortex_src_addWTD(vortex,
					  (source0 - OFFSET_SRCOUT), ch);
			vortex_src_addWTD(vortex,
					  (source1 - OFFSET_SRCOUT), ch);
		पूर्ण अन्यथा अगर ((source0 < (OFFSET_MIXOUT + NR_MIXOUT))
			   && (source0 >= OFFSET_MIXOUT)) अणु
			vortex_mixer_addWTD(vortex,
					    (source0 - OFFSET_MIXOUT), ch);
			vortex_mixer_addWTD(vortex,
					    (source1 - OFFSET_MIXOUT), ch);
		पूर्ण
	पूर्ण अन्यथा अणु
		vortex_adb_delroutes(vortex, ch, route[0], route[1]);
		अगर ((source0 < (OFFSET_SRCOUT + NR_SRC))
		    && (source0 >= OFFSET_SRCOUT)) अणु
			vortex_src_delWTD(vortex,
					  (source0 - OFFSET_SRCOUT), ch);
			vortex_src_delWTD(vortex,
					  (source1 - OFFSET_SRCOUT), ch);
		पूर्ण अन्यथा अगर ((source0 < (OFFSET_MIXOUT + NR_MIXOUT))
			   && (source0 >= OFFSET_MIXOUT)) अणु
			vortex_mixer_delWTD(vortex,
					    (source0 - OFFSET_MIXOUT), ch);
			vortex_mixer_delWTD(vortex,
					    (source1 - OFFSET_MIXOUT), ch);
		पूर्ण
	पूर्ण
पूर्ण

/* Connection stuff */

// Connect adbdma to src('s).
अटल व्योम
vortex_connection_adbdma_src(vortex_t * vortex, पूर्णांक en, अचिन्हित अक्षर ch,
			     अचिन्हित अक्षर adbdma, अचिन्हित अक्षर src)
अणु
	vortex_route(vortex, en, ch, ADB_DMA(adbdma), ADB_SRCIN(src));
पूर्ण

// Connect SRC to mixin.
अटल व्योम
vortex_connection_src_mixin(vortex_t * vortex, पूर्णांक en,
			    अचिन्हित अक्षर channel, अचिन्हित अक्षर src,
			    अचिन्हित अक्षर mixin)
अणु
	vortex_route(vortex, en, channel, ADB_SRCOUT(src), ADB_MIXIN(mixin));
पूर्ण

// Connect mixin with mix output.
अटल व्योम
vortex_connection_mixin_mix(vortex_t * vortex, पूर्णांक en, अचिन्हित अक्षर mixin,
			    अचिन्हित अक्षर mix, पूर्णांक a)
अणु
	अगर (en) अणु
		vortex_mix_enableinput(vortex, mix, mixin);
		vortex_mix_setinputvolumebyte(vortex, mix, mixin, MIX_DEFIGAIN);	// added to original code.
	पूर्ण अन्यथा
		vortex_mix_disableinput(vortex, mix, mixin, a);
पूर्ण

// Connect असलolut address to mixin.
अटल व्योम
vortex_connection_adb_mixin(vortex_t * vortex, पूर्णांक en,
			    अचिन्हित अक्षर channel, अचिन्हित अक्षर source,
			    अचिन्हित अक्षर mixin)
अणु
	vortex_route(vortex, en, channel, source, ADB_MIXIN(mixin));
पूर्ण

अटल व्योम
vortex_connection_src_adbdma(vortex_t * vortex, पूर्णांक en, अचिन्हित अक्षर ch,
			     अचिन्हित अक्षर src, अचिन्हित अक्षर adbdma)
अणु
	vortex_route(vortex, en, ch, ADB_SRCOUT(src), ADB_DMA(adbdma));
पूर्ण

अटल व्योम
vortex_connection_src_src_adbdma(vortex_t * vortex, पूर्णांक en,
				 अचिन्हित अक्षर ch, अचिन्हित अक्षर src0,
				 अचिन्हित अक्षर src1, अचिन्हित अक्षर adbdma)
अणु

	vortex_routeLRT(vortex, en, ch, ADB_SRCOUT(src0), ADB_SRCOUT(src1),
			ADB_DMA(adbdma));
पूर्ण

// mix to असलolut address.
अटल व्योम
vortex_connection_mix_adb(vortex_t * vortex, पूर्णांक en, अचिन्हित अक्षर ch,
			  अचिन्हित अक्षर mix, अचिन्हित अक्षर dest)
अणु
	vortex_route(vortex, en, ch, ADB_MIXOUT(mix), dest);
	vortex_mix_setvolumebyte(vortex, mix, MIX_DEFOGAIN);	// added to original code.
पूर्ण

// mixer to src.
अटल व्योम
vortex_connection_mix_src(vortex_t * vortex, पूर्णांक en, अचिन्हित अक्षर ch,
			  अचिन्हित अक्षर mix, अचिन्हित अक्षर src)
अणु
	vortex_route(vortex, en, ch, ADB_MIXOUT(mix), ADB_SRCIN(src));
	vortex_mix_setvolumebyte(vortex, mix, MIX_DEFOGAIN);	// added to original code.
पूर्ण

#अगर 0
अटल व्योम
vortex_connection_adbdma_src_src(vortex_t * vortex, पूर्णांक en,
				 अचिन्हित अक्षर channel,
				 अचिन्हित अक्षर adbdma, अचिन्हित अक्षर src0,
				 अचिन्हित अक्षर src1)
अणु
	vortex_routes(vortex, en, channel, ADB_DMA(adbdma),
		      ADB_SRCIN(src0), ADB_SRCIN(src1));
पूर्ण

// Connect two mix to AdbDma.
अटल व्योम
vortex_connection_mix_mix_adbdma(vortex_t * vortex, पूर्णांक en,
				 अचिन्हित अक्षर ch, अचिन्हित अक्षर mix0,
				 अचिन्हित अक्षर mix1, अचिन्हित अक्षर adbdma)
अणु

	ADBRamLink routes[2];
	routes[0] =
	    (((mix0 +
	       OFFSET_MIXOUT) & ADB_MASK) << ADB_SHIFT) | (adbdma & ADB_MASK);
	routes[1] =
	    (((mix1 + OFFSET_MIXOUT) & ADB_MASK) << ADB_SHIFT) | ((adbdma +
								   0x20) &
								  ADB_MASK);
	अगर (en) अणु
		vortex_adb_addroutes(vortex, ch, routes, 0x2);
		vortex_mixer_addWTD(vortex, mix0, ch);
		vortex_mixer_addWTD(vortex, mix1, ch);
	पूर्ण अन्यथा अणु
		vortex_adb_delroutes(vortex, ch, routes[0], routes[1]);
		vortex_mixer_delWTD(vortex, mix0, ch);
		vortex_mixer_delWTD(vortex, mix1, ch);
	पूर्ण
पूर्ण
#पूर्ण_अगर

/* CODEC connect. */

अटल व्योम
vortex_connect_codecplay(vortex_t * vortex, पूर्णांक en, अचिन्हित अक्षर mixers[])
अणु
#अगर_घोषित CHIP_AU8820
	vortex_connection_mix_adb(vortex, en, 0x11, mixers[0], ADB_CODECOUT(0));
	vortex_connection_mix_adb(vortex, en, 0x11, mixers[1], ADB_CODECOUT(1));
#अन्यथा
#अगर 1
	// Connect front channels through EQ.
	vortex_connection_mix_adb(vortex, en, 0x11, mixers[0], ADB_EQIN(0));
	vortex_connection_mix_adb(vortex, en, 0x11, mixers[1], ADB_EQIN(1));
	/* Lower volume, since EQ has some gain. */
	vortex_mix_setvolumebyte(vortex, mixers[0], 0);
	vortex_mix_setvolumebyte(vortex, mixers[1], 0);
	vortex_route(vortex, en, 0x11, ADB_EQOUT(0), ADB_CODECOUT(0));
	vortex_route(vortex, en, 0x11, ADB_EQOUT(1), ADB_CODECOUT(1));

	/* Check अगर reg 0x28 has SDAC bit set. */
	अगर (VORTEX_IS_QUAD(vortex)) अणु
		/* Rear channel. Note: ADB_CODECOUT(0+2) and (1+2) is क्रम AC97 modem */
		vortex_connection_mix_adb(vortex, en, 0x11, mixers[2],
					  ADB_CODECOUT(0 + 4));
		vortex_connection_mix_adb(vortex, en, 0x11, mixers[3],
					  ADB_CODECOUT(1 + 4));
		/* pr_debug( "SDAC detected "); */
	पूर्ण
#अन्यथा
	// Use plain direct output to codec.
	vortex_connection_mix_adb(vortex, en, 0x11, mixers[0], ADB_CODECOUT(0));
	vortex_connection_mix_adb(vortex, en, 0x11, mixers[1], ADB_CODECOUT(1));
#पूर्ण_अगर
#पूर्ण_अगर
पूर्ण

अटल व्योम
vortex_connect_codecrec(vortex_t * vortex, पूर्णांक en, अचिन्हित अक्षर mixin0,
			अचिन्हित अक्षर mixin1)
अणु
	/*
	   Enable: 0x1, 0x1
	   Channel: 0x11, 0x11
	   ADB Source address: 0x48, 0x49
	   Destination Asp4Topology_0x9c,0x98
	 */
	vortex_connection_adb_mixin(vortex, en, 0x11, ADB_CODECIN(0), mixin0);
	vortex_connection_adb_mixin(vortex, en, 0x11, ADB_CODECIN(1), mixin1);
पूर्ण

// Higher level ADB audio path (de)allocator.

/* Resource manager */
अटल स्थिर पूर्णांक resnum[VORTEX_RESOURCE_LAST] =
    अणु NR_ADB, NR_SRC, NR_MIXIN, NR_MIXOUT, NR_A3D पूर्ण;
/*
 Checkout/Checkin resource of given type. 
 resmap: resource map to be used. If शून्य means that we want to allocate
 a DMA resource (root of all other resources of a dma channel).
 out: Mean checkout अगर != 0. Else mean Checkin resource.
 restype: Indicates type of resource to be checked in or out.
*/
अटल अक्षर
vortex_adb_checkinout(vortex_t * vortex, पूर्णांक resmap[], पूर्णांक out, पूर्णांक restype)
अणु
	पूर्णांक i, qty = resnum[restype], resinuse = 0;

	अगर (out) अणु
		/* Gather used resources by all streams. */
		क्रम (i = 0; i < NR_ADB; i++) अणु
			resinuse |= vortex->dma_adb[i].resources[restype];
		पूर्ण
		resinuse |= vortex->fixed_res[restype];
		/* Find and take मुक्त resource. */
		क्रम (i = 0; i < qty; i++) अणु
			अगर ((resinuse & (1 << i)) == 0) अणु
				अगर (resmap != शून्य)
					resmap[restype] |= (1 << i);
				अन्यथा
					vortex->dma_adb[i].resources[restype] |= (1 << i);
				/*
				pr_debug(
				       "vortex: ResManager: type %d out %d\n",
				       restype, i);
				*/
				वापस i;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (resmap == शून्य)
			वापस -EINVAL;
		/* Checkin first resource of type restype. */
		क्रम (i = 0; i < qty; i++) अणु
			अगर (resmap[restype] & (1 << i)) अणु
				resmap[restype] &= ~(1 << i);
				/*
				pr_debug(
				       "vortex: ResManager: type %d in %d\n",
				       restype, i);
				*/
				वापस i;
			पूर्ण
		पूर्ण
	पूर्ण
	dev_err(vortex->card->dev,
		"FATAL: ResManager: resource type %d exhausted.\n",
		restype);
	वापस -ENOMEM;
पूर्ण

/* Default Connections  */

अटल व्योम vortex_connect_शेष(vortex_t * vortex, पूर्णांक en)
अणु
	// Connect AC97 codec.
	vortex->mixplayb[0] = vortex_adb_checkinout(vortex, vortex->fixed_res, en,
				  VORTEX_RESOURCE_MIXOUT);
	vortex->mixplayb[1] = vortex_adb_checkinout(vortex, vortex->fixed_res, en,
				  VORTEX_RESOURCE_MIXOUT);
	अगर (VORTEX_IS_QUAD(vortex)) अणु
		vortex->mixplayb[2] = vortex_adb_checkinout(vortex, vortex->fixed_res, en,
					  VORTEX_RESOURCE_MIXOUT);
		vortex->mixplayb[3] = vortex_adb_checkinout(vortex, vortex->fixed_res, en,
					  VORTEX_RESOURCE_MIXOUT);
	पूर्ण
	vortex_connect_codecplay(vortex, en, vortex->mixplayb);

	vortex->mixcapt[0] = vortex_adb_checkinout(vortex, vortex->fixed_res, en,
				  VORTEX_RESOURCE_MIXIN);
	vortex->mixcapt[1] = vortex_adb_checkinout(vortex, vortex->fixed_res, en,
				  VORTEX_RESOURCE_MIXIN);
	vortex_connect_codecrec(vortex, en, MIX_CAPT(0), MIX_CAPT(1));

	// Connect SPDIF
#अगर_अघोषित CHIP_AU8820
	vortex->mixspdअगर[0] = vortex_adb_checkinout(vortex, vortex->fixed_res, en,
				  VORTEX_RESOURCE_MIXOUT);
	vortex->mixspdअगर[1] = vortex_adb_checkinout(vortex, vortex->fixed_res, en,
				  VORTEX_RESOURCE_MIXOUT);
	vortex_connection_mix_adb(vortex, en, 0x14, vortex->mixspdअगर[0],
				  ADB_SPDIFOUT(0));
	vortex_connection_mix_adb(vortex, en, 0x14, vortex->mixspdअगर[1],
				  ADB_SPDIFOUT(1));
#पूर्ण_अगर
	// Connect WT
#अगर_अघोषित CHIP_AU8810
	vortex_wt_connect(vortex, en);
#पूर्ण_अगर
	// A3D (crosstalk canceler and A3D slices). AU8810 disabled क्रम now.
#अगर_अघोषित CHIP_AU8820
	vortex_Vort3D_connect(vortex, en);
#पूर्ण_अगर
	// Connect I2S

	// Connect DSP पूर्णांकerface क्रम SQ3500 turbo (not here i think...)

	// Connect AC98 modem codec
	
पूर्ण

/*
  Allocate nr_ch pcm audio routes अगर dma < 0. If dma >= 0, existing routes
  are deallocated.
  dma: DMA engine routes to be deallocated when dma >= 0.
  nr_ch: Number of channels to be de/allocated.
  dir: direction of stream. Uses same values as substream->stream.
  type: Type of audio output/source (codec, spdअगर, i2s, dsp, etc)
  Return: Return allocated DMA or same DMA passed as "dma" when dma >= 0.
*/
अटल पूर्णांक
vortex_adb_allocroute(vortex_t *vortex, पूर्णांक dma, पूर्णांक nr_ch, पूर्णांक dir,
			पूर्णांक type, पूर्णांक subdev)
अणु
	stream_t *stream;
	पूर्णांक i, en;
	काष्ठा pcm_vol *p;
	
	अगर (dma >= 0) अणु
		en = 0;
		vortex_adb_checkinout(vortex,
				      vortex->dma_adb[dma].resources, en,
				      VORTEX_RESOURCE_DMA);
	पूर्ण अन्यथा अणु
		en = 1;
		अगर ((dma =
		     vortex_adb_checkinout(vortex, शून्य, en,
					   VORTEX_RESOURCE_DMA)) < 0)
			वापस -EBUSY;
	पूर्ण

	stream = &vortex->dma_adb[dma];
	stream->dma = dma;
	stream->dir = dir;
	stream->type = type;

	/* PLAYBACK ROUTES. */
	अगर (dir == SNDRV_PCM_STREAM_PLAYBACK) अणु
		पूर्णांक src[4], mix[4], ch_top;
#अगर_अघोषित CHIP_AU8820
		पूर्णांक a3d = 0;
#पूर्ण_अगर
		/* Get SRC and MIXER hardware resources. */
		अगर (stream->type != VORTEX_PCM_SPDIF) अणु
			क्रम (i = 0; i < nr_ch; i++) अणु
				अगर ((src[i] = vortex_adb_checkinout(vortex,
							   stream->resources, en,
							   VORTEX_RESOURCE_SRC)) < 0) अणु
					स_रखो(stream->resources, 0,
					       माप(stream->resources));
					वापस -EBUSY;
				पूर्ण
				अगर (stream->type != VORTEX_PCM_A3D) अणु
					अगर ((mix[i] = vortex_adb_checkinout(vortex,
								   stream->resources,
								   en,
								   VORTEX_RESOURCE_MIXIN)) < 0) अणु
						स_रखो(stream->resources,
						       0,
						       माप(stream->resources));
						वापस -EBUSY;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
#अगर_अघोषित CHIP_AU8820
		अगर (stream->type == VORTEX_PCM_A3D) अणु
			अगर ((a3d =
			     vortex_adb_checkinout(vortex,
						   stream->resources, en,
						   VORTEX_RESOURCE_A3D)) < 0) अणु
				स_रखो(stream->resources, 0,
				       माप(stream->resources));
				dev_err(vortex->card->dev,
					"out of A3D sources. Sorry\n");
				वापस -EBUSY;
			पूर्ण
			/* (De)Initialize A3D hardware source. */
			vortex_Vort3D_InitializeSource(&vortex->a3d[a3d], en,
						       vortex);
		पूर्ण
		/* Make SPDIF out exclusive to "spdif" device when in use. */
		अगर ((stream->type == VORTEX_PCM_SPDIF) && (en)) अणु
			vortex_route(vortex, 0, 0x14,
				     ADB_MIXOUT(vortex->mixspdअगर[0]),
				     ADB_SPDIFOUT(0));
			vortex_route(vortex, 0, 0x14,
				     ADB_MIXOUT(vortex->mixspdअगर[1]),
				     ADB_SPDIFOUT(1));
		पूर्ण
#पूर्ण_अगर
		/* Make playback routes. */
		क्रम (i = 0; i < nr_ch; i++) अणु
			अगर (stream->type == VORTEX_PCM_ADB) अणु
				vortex_connection_adbdma_src(vortex, en,
							     src[nr_ch - 1],
							     dma,
							     src[i]);
				vortex_connection_src_mixin(vortex, en,
							    0x11, src[i],
							    mix[i]);
				vortex_connection_mixin_mix(vortex, en,
							    mix[i],
							    MIX_PLAYB(i), 0);
#अगर_अघोषित CHIP_AU8820
				vortex_connection_mixin_mix(vortex, en,
							    mix[i],
							    MIX_SPDIF(i % 2), 0);
				vortex_mix_setinputvolumebyte(vortex,
							      MIX_SPDIF(i % 2),
							      mix[i],
							      MIX_DEFIGAIN);
#पूर्ण_अगर
			पूर्ण
#अगर_अघोषित CHIP_AU8820
			अगर (stream->type == VORTEX_PCM_A3D) अणु
				vortex_connection_adbdma_src(vortex, en,
							     src[nr_ch - 1], 
								 dma,
							     src[i]);
				vortex_route(vortex, en, 0x11, ADB_SRCOUT(src[i]), ADB_A3DIN(a3d));
				/* XTalk test. */
				//vortex_route(vortex, en, 0x11, dma, ADB_XTALKIN(i?9:4));
				//vortex_route(vortex, en, 0x11, ADB_SRCOUT(src[i]), ADB_XTALKIN(i?4:9));
			पूर्ण
			अगर (stream->type == VORTEX_PCM_SPDIF)
				vortex_route(vortex, en, 0x14,
					     ADB_DMA(stream->dma),
					     ADB_SPDIFOUT(i));
#पूर्ण_अगर
		पूर्ण
		अगर (stream->type != VORTEX_PCM_SPDIF && stream->type != VORTEX_PCM_A3D) अणु
			ch_top = (VORTEX_IS_QUAD(vortex) ? 4 : 2);
			क्रम (i = nr_ch; i < ch_top; i++) अणु
				vortex_connection_mixin_mix(vortex, en,
							    mix[i % nr_ch],
							    MIX_PLAYB(i), 0);
#अगर_अघोषित CHIP_AU8820
				vortex_connection_mixin_mix(vortex, en,
							    mix[i % nr_ch],
							    MIX_SPDIF(i % 2),
								0);
				vortex_mix_setinputvolumebyte(vortex,
							      MIX_SPDIF(i % 2),
							      mix[i % nr_ch],
							      MIX_DEFIGAIN);
#पूर्ण_अगर
			पूर्ण
			अगर (stream->type == VORTEX_PCM_ADB && en) अणु
				p = &vortex->pcm_vol[subdev];
				p->dma = dma;
				क्रम (i = 0; i < nr_ch; i++)
					p->mixin[i] = mix[i];
				क्रम (i = 0; i < ch_top; i++)
					p->vol[i] = 0;
			पूर्ण
		पूर्ण
#अगर_अघोषित CHIP_AU8820
		अन्यथा अणु
			अगर (nr_ch == 1 && stream->type == VORTEX_PCM_SPDIF)
				vortex_route(vortex, en, 0x14,
					     ADB_DMA(stream->dma),
					     ADB_SPDIFOUT(1));
		पूर्ण
		/* Reconnect SPDIF out when "spdif" device is करोwn. */
		अगर ((stream->type == VORTEX_PCM_SPDIF) && (!en)) अणु
			vortex_route(vortex, 1, 0x14,
				     ADB_MIXOUT(vortex->mixspdअगर[0]),
				     ADB_SPDIFOUT(0));
			vortex_route(vortex, 1, 0x14,
				     ADB_MIXOUT(vortex->mixspdअगर[1]),
				     ADB_SPDIFOUT(1));
		पूर्ण
#पूर्ण_अगर
	/* CAPTURE ROUTES. */
	पूर्ण अन्यथा अणु
		पूर्णांक src[2], mix[2];

		अगर (nr_ch < 1)
			वापस -EINVAL;

		/* Get SRC and MIXER hardware resources. */
		क्रम (i = 0; i < nr_ch; i++) अणु
			अगर ((mix[i] =
			     vortex_adb_checkinout(vortex,
						   stream->resources, en,
						   VORTEX_RESOURCE_MIXOUT))
			    < 0) अणु
				स_रखो(stream->resources, 0,
				       माप(stream->resources));
				वापस -EBUSY;
			पूर्ण
			अगर ((src[i] =
			     vortex_adb_checkinout(vortex,
						   stream->resources, en,
						   VORTEX_RESOURCE_SRC)) < 0) अणु
				स_रखो(stream->resources, 0,
				       माप(stream->resources));
				वापस -EBUSY;
			पूर्ण
		पूर्ण

		/* Make capture routes. */
		vortex_connection_mixin_mix(vortex, en, MIX_CAPT(0), mix[0], 0);
		vortex_connection_mix_src(vortex, en, 0x11, mix[0], src[0]);
		अगर (nr_ch == 1) अणु
			vortex_connection_mixin_mix(vortex, en,
						    MIX_CAPT(1), mix[0], 0);
			vortex_connection_src_adbdma(vortex, en,
						     src[0],
						     src[0], dma);
		पूर्ण अन्यथा अणु
			vortex_connection_mixin_mix(vortex, en,
						    MIX_CAPT(1), mix[1], 0);
			vortex_connection_mix_src(vortex, en, 0x11, mix[1],
						  src[1]);
			vortex_connection_src_src_adbdma(vortex, en,
							 src[1], src[0],
							 src[1], dma);
		पूर्ण
	पूर्ण
	vortex->dma_adb[dma].nr_ch = nr_ch;

#अगर 0
	/* AC97 Codec channel setup. FIXME: this has no effect on some cards !! */
	अगर (nr_ch < 4) अणु
		/* Copy stereo to rear channel (surround) */
		snd_ac97_ग_लिखो_cache(vortex->codec,
				     AC97_SIGMATEL_DAC2INVERT,
				     snd_ac97_पढ़ो(vortex->codec,
						   AC97_SIGMATEL_DAC2INVERT)
				     | 4);
	पूर्ण अन्यथा अणु
		/* Allow separate front and rear channels. */
		snd_ac97_ग_लिखो_cache(vortex->codec,
				     AC97_SIGMATEL_DAC2INVERT,
				     snd_ac97_पढ़ो(vortex->codec,
						   AC97_SIGMATEL_DAC2INVERT)
				     & ~((u32)
					 4));
	पूर्ण
#पूर्ण_अगर
	वापस dma;
पूर्ण

/*
 Set the SampleRate of the SRC's attached to the given DMA engine.
 */
अटल व्योम
vortex_adb_setsrc(vortex_t * vortex, पूर्णांक adbdma, अचिन्हित पूर्णांक rate, पूर्णांक dir)
अणु
	stream_t *stream = &(vortex->dma_adb[adbdma]);
	पूर्णांक i, cvrt;

	/* dir=1:play ; dir=0:rec */
	अगर (dir)
		cvrt = SRC_RATIO(rate, 48000);
	अन्यथा
		cvrt = SRC_RATIO(48000, rate);

	/* Setup SRC's */
	क्रम (i = 0; i < NR_SRC; i++) अणु
		अगर (stream->resources[VORTEX_RESOURCE_SRC] & (1 << i))
			vortex_src_setupchannel(vortex, i, cvrt, 0, 0, i, dir, 1, cvrt, dir);
	पूर्ण
पूर्ण

// Timer and ISR functions.

अटल व्योम vortex_समय_रखोr(vortex_t * vortex, पूर्णांक period)
अणु
	//set the समयr period to <period> 48000ths of a second.
	hwग_लिखो(vortex->mmio, VORTEX_IRQ_STAT, period);
पूर्ण

#अगर 0
अटल व्योम vortex_enable_समयr_पूर्णांक(vortex_t * card)
अणु
	hwग_लिखो(card->mmio, VORTEX_IRQ_CTRL,
		hwपढ़ो(card->mmio, VORTEX_IRQ_CTRL) | IRQ_TIMER | 0x60);
पूर्ण

अटल व्योम vortex_disable_समयr_पूर्णांक(vortex_t * card)
अणु
	hwग_लिखो(card->mmio, VORTEX_IRQ_CTRL,
		hwपढ़ो(card->mmio, VORTEX_IRQ_CTRL) & ~IRQ_TIMER);
पूर्ण

#पूर्ण_अगर
अटल व्योम vortex_enable_पूर्णांक(vortex_t * card)
अणु
	// CAsp4ISR__EnableVortexInt_व्योम_
	hwग_लिखो(card->mmio, VORTEX_CTRL,
		hwपढ़ो(card->mmio, VORTEX_CTRL) | CTRL_IRQ_ENABLE);
	hwग_लिखो(card->mmio, VORTEX_IRQ_CTRL,
		(hwपढ़ो(card->mmio, VORTEX_IRQ_CTRL) & 0xffffefc0) | 0x24);
पूर्ण

अटल व्योम vortex_disable_पूर्णांक(vortex_t * card)
अणु
	hwग_लिखो(card->mmio, VORTEX_CTRL,
		hwपढ़ो(card->mmio, VORTEX_CTRL) & ~CTRL_IRQ_ENABLE);
पूर्ण

अटल irqवापस_t vortex_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	vortex_t *vortex = dev_id;
	पूर्णांक i, handled;
	u32 source;

	//check अगर the पूर्णांकerrupt is ours.
	अगर (!(hwपढ़ो(vortex->mmio, VORTEX_STAT) & 0x1))
		वापस IRQ_NONE;

	// This is the Interrupt Enable flag we set beक्रमe (consistency check).
	अगर (!(hwपढ़ो(vortex->mmio, VORTEX_CTRL) & CTRL_IRQ_ENABLE))
		वापस IRQ_NONE;

	source = hwपढ़ो(vortex->mmio, VORTEX_IRQ_SOURCE);
	// Reset IRQ flags.
	hwग_लिखो(vortex->mmio, VORTEX_IRQ_SOURCE, source);
	hwपढ़ो(vortex->mmio, VORTEX_IRQ_SOURCE);
	// Is at least one IRQ flag set?
	अगर (source == 0) अणु
		dev_err(vortex->card->dev, "missing irq source\n");
		वापस IRQ_NONE;
	पूर्ण

	handled = 0;
	// Attend every पूर्णांकerrupt source.
	अगर (unlikely(source & IRQ_ERR_MASK)) अणु
		अगर (source & IRQ_FATAL) अणु
			dev_err(vortex->card->dev, "IRQ fatal error\n");
		पूर्ण
		अगर (source & IRQ_PARITY) अणु
			dev_err(vortex->card->dev, "IRQ parity error\n");
		पूर्ण
		अगर (source & IRQ_REG) अणु
			dev_err(vortex->card->dev, "IRQ reg error\n");
		पूर्ण
		अगर (source & IRQ_FIFO) अणु
			dev_err(vortex->card->dev, "IRQ fifo error\n");
		पूर्ण
		अगर (source & IRQ_DMA) अणु
			dev_err(vortex->card->dev, "IRQ dma error\n");
		पूर्ण
		handled = 1;
	पूर्ण
	अगर (source & IRQ_PCMOUT) अणु
		/* ALSA period acknowledge. */
		spin_lock(&vortex->lock);
		क्रम (i = 0; i < NR_ADB; i++) अणु
			अगर (vortex->dma_adb[i].fअगरo_status == FIFO_START) अणु
				अगर (!vortex_adbdma_bufshअगरt(vortex, i))
					जारी;
				spin_unlock(&vortex->lock);
				snd_pcm_period_elapsed(vortex->dma_adb[i].
						       substream);
				spin_lock(&vortex->lock);
			पूर्ण
		पूर्ण
#अगर_अघोषित CHIP_AU8810
		क्रम (i = 0; i < NR_WT; i++) अणु
			अगर (vortex->dma_wt[i].fअगरo_status == FIFO_START) अणु
				/* FIXME: we ignore the वापस value from
				 * vortex_wtdma_bufshअगरt() below as the delta
				 * calculation seems not working क्रम wavetable
				 * by some reason
				 */
				vortex_wtdma_bufshअगरt(vortex, i);
				spin_unlock(&vortex->lock);
				snd_pcm_period_elapsed(vortex->dma_wt[i].
						       substream);
				spin_lock(&vortex->lock);
			पूर्ण
		पूर्ण
#पूर्ण_अगर
		spin_unlock(&vortex->lock);
		handled = 1;
	पूर्ण
	//Acknowledge the Timer पूर्णांकerrupt
	अगर (source & IRQ_TIMER) अणु
		hwपढ़ो(vortex->mmio, VORTEX_IRQ_STAT);
		handled = 1;
	पूर्ण
	अगर ((source & IRQ_MIDI) && vortex->rmidi) अणु
		snd_mpu401_uart_पूर्णांकerrupt(vortex->irq,
					  vortex->rmidi->निजी_data);
		handled = 1;
	पूर्ण

	अगर (!handled) अणु
		dev_err(vortex->card->dev, "unknown irq source %x\n", source);
	पूर्ण
	वापस IRQ_RETVAL(handled);
पूर्ण

/* Codec */

#घोषणा POLL_COUNT 1000
अटल व्योम vortex_codec_init(vortex_t * vortex)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 32; i++) अणु
		/* the winकरोws driver ग_लिखोs -i, so we ग_लिखो -i */
		hwग_लिखो(vortex->mmio, (VORTEX_CODEC_CHN + (i << 2)), -i);
		msleep(2);
	पूर्ण
	अगर (0) अणु
		hwग_लिखो(vortex->mmio, VORTEX_CODEC_CTRL, 0x8068);
		msleep(1);
		hwग_लिखो(vortex->mmio, VORTEX_CODEC_CTRL, 0x00e8);
		msleep(1);
	पूर्ण अन्यथा अणु
		hwग_लिखो(vortex->mmio, VORTEX_CODEC_CTRL, 0x00a8);
		msleep(2);
		hwग_लिखो(vortex->mmio, VORTEX_CODEC_CTRL, 0x80a8);
		msleep(2);
		hwग_लिखो(vortex->mmio, VORTEX_CODEC_CTRL, 0x80e8);
		msleep(2);
		hwग_लिखो(vortex->mmio, VORTEX_CODEC_CTRL, 0x80a8);
		msleep(2);
		hwग_लिखो(vortex->mmio, VORTEX_CODEC_CTRL, 0x00a8);
		msleep(2);
		hwग_लिखो(vortex->mmio, VORTEX_CODEC_CTRL, 0x00e8);
	पूर्ण
	क्रम (i = 0; i < 32; i++) अणु
		hwग_लिखो(vortex->mmio, (VORTEX_CODEC_CHN + (i << 2)), -i);
		msleep(5);
	पूर्ण
	hwग_लिखो(vortex->mmio, VORTEX_CODEC_CTRL, 0xe8);
	msleep(1);
	/* Enable codec channels 0 and 1. */
	hwग_लिखो(vortex->mmio, VORTEX_CODEC_EN,
		hwपढ़ो(vortex->mmio, VORTEX_CODEC_EN) | EN_CODEC);
पूर्ण

अटल व्योम
vortex_codec_ग_लिखो(काष्ठा snd_ac97 * codec, अचिन्हित लघु addr, अचिन्हित लघु data)
अणु

	vortex_t *card = (vortex_t *) codec->निजी_data;
	अचिन्हित पूर्णांक lअगरeboat = 0;

	/* रुको क्रम transactions to clear */
	जबतक (!(hwपढ़ो(card->mmio, VORTEX_CODEC_CTRL) & 0x100)) अणु
		udelay(100);
		अगर (lअगरeboat++ > POLL_COUNT) अणु
			dev_err(card->card->dev, "ac97 codec stuck busy\n");
			वापस;
		पूर्ण
	पूर्ण
	/* ग_लिखो रेजिस्टर */
	hwग_लिखो(card->mmio, VORTEX_CODEC_IO,
		((addr << VORTEX_CODEC_ADDSHIFT) & VORTEX_CODEC_ADDMASK) |
		((data << VORTEX_CODEC_DATSHIFT) & VORTEX_CODEC_DATMASK) |
		VORTEX_CODEC_WRITE |
		(codec->num << VORTEX_CODEC_ID_SHIFT) );

	/* Flush Caches. */
	hwपढ़ो(card->mmio, VORTEX_CODEC_IO);
पूर्ण

अटल अचिन्हित लघु vortex_codec_पढ़ो(काष्ठा snd_ac97 * codec, अचिन्हित लघु addr)
अणु

	vortex_t *card = (vortex_t *) codec->निजी_data;
	u32 पढ़ो_addr, data;
	अचिन्हित lअगरeboat = 0;

	/* रुको क्रम transactions to clear */
	जबतक (!(hwपढ़ो(card->mmio, VORTEX_CODEC_CTRL) & 0x100)) अणु
		udelay(100);
		अगर (lअगरeboat++ > POLL_COUNT) अणु
			dev_err(card->card->dev, "ac97 codec stuck busy\n");
			वापस 0xffff;
		पूर्ण
	पूर्ण
	/* set up पढ़ो address */
	पढ़ो_addr = ((addr << VORTEX_CODEC_ADDSHIFT) & VORTEX_CODEC_ADDMASK) |
		(codec->num << VORTEX_CODEC_ID_SHIFT) ;
	hwग_लिखो(card->mmio, VORTEX_CODEC_IO, पढ़ो_addr);

	/* रुको क्रम address */
	करो अणु
		udelay(100);
		data = hwपढ़ो(card->mmio, VORTEX_CODEC_IO);
		अगर (lअगरeboat++ > POLL_COUNT) अणु
			dev_err(card->card->dev,
				"ac97 address never arrived\n");
			वापस 0xffff;
		पूर्ण
	पूर्ण जबतक ((data & VORTEX_CODEC_ADDMASK) !=
		 (addr << VORTEX_CODEC_ADDSHIFT));

	/* वापस data. */
	वापस (u16) (data & VORTEX_CODEC_DATMASK);
पूर्ण

/* SPDIF support  */

अटल व्योम vortex_spdअगर_init(vortex_t * vortex, पूर्णांक spdअगर_sr, पूर्णांक spdअगर_mode)
अणु
	पूर्णांक i, this_38 = 0, this_04 = 0, this_08 = 0, this_0c = 0;

	/* CAsp4Spdअगर::InitializeSpdअगरHardware(व्योम) */
	hwग_लिखो(vortex->mmio, VORTEX_SPDIF_FLAGS,
		hwपढ़ो(vortex->mmio, VORTEX_SPDIF_FLAGS) & 0xfff3fffd);
	//क्रम (i=0x291D4; i<0x29200; i+=4)
	क्रम (i = 0; i < 11; i++)
		hwग_लिखो(vortex->mmio, VORTEX_SPDIF_CFG1 + (i << 2), 0);
	//hwग_लिखो(vortex->mmio, 0x29190, hwपढ़ो(vortex->mmio, 0x29190) | 0xc0000);
	hwग_लिखो(vortex->mmio, VORTEX_CODEC_EN,
		hwपढ़ो(vortex->mmio, VORTEX_CODEC_EN) | EN_SPDIF);

	/* CAsp4Spdअगर::ProgramSRCInHardware(क्रमागत  SPDIF_SR,क्रमागत  SPDIFMODE) */
	अगर (this_04 && this_08) अणु
		पूर्णांक edi;

		i = (((0x5DC00000 / spdअगर_sr) + 1) >> 1);
		अगर (i > 0x800) अणु
			अगर (i < 0x1ffff)
				edi = (i >> 1);
			अन्यथा
				edi = 0x1ffff;
		पूर्ण अन्यथा अणु
			edi = 0x800;
		पूर्ण
		/* this_04 and this_08 are the CASp4Src's (samplerate converters) */
		vortex_src_setupchannel(vortex, this_04, edi, 0, 1,
					this_0c, 1, 0, edi, 1);
		vortex_src_setupchannel(vortex, this_08, edi, 0, 1,
					this_0c, 1, 0, edi, 1);
	पूर्ण

	i = spdअगर_sr;
	spdअगर_sr |= 0x8c;
	चयन (i) अणु
	हाल 32000:
		this_38 &= 0xFFFFFFFE;
		this_38 &= 0xFFFFFFFD;
		this_38 &= 0xF3FFFFFF;
		this_38 |= 0x03000000;	/* set 32khz samplerate */
		this_38 &= 0xFFFFFF3F;
		spdअगर_sr &= 0xFFFFFFFD;
		spdअगर_sr |= 1;
		अवरोध;
	हाल 44100:
		this_38 &= 0xFFFFFFFE;
		this_38 &= 0xFFFFFFFD;
		this_38 &= 0xF0FFFFFF;
		this_38 |= 0x03000000;
		this_38 &= 0xFFFFFF3F;
		spdअगर_sr &= 0xFFFFFFFC;
		अवरोध;
	हाल 48000:
		अगर (spdअगर_mode == 1) अणु
			this_38 &= 0xFFFFFFFE;
			this_38 &= 0xFFFFFFFD;
			this_38 &= 0xF2FFFFFF;
			this_38 |= 0x02000000;	/* set 48khz samplerate */
			this_38 &= 0xFFFFFF3F;
		पूर्ण अन्यथा अणु
			/* J. Gorकरोn Wolfe: I think this stuff is क्रम AC3 */
			this_38 |= 0x00000003;
			this_38 &= 0xFFFFFFBF;
			this_38 |= 0x80;
		पूर्ण
		spdअगर_sr |= 2;
		spdअगर_sr &= 0xFFFFFFFE;
		अवरोध;

	पूर्ण
	/* looks like the next 2 lines transfer a 16-bit value पूर्णांकo 2 8-bit 
	   रेजिस्टरs. seems to be क्रम the standard IEC/SPDIF initialization 
	   stuff */
	hwग_लिखो(vortex->mmio, VORTEX_SPDIF_CFG0, this_38 & 0xffff);
	hwग_लिखो(vortex->mmio, VORTEX_SPDIF_CFG1, this_38 >> 0x10);
	hwग_लिखो(vortex->mmio, VORTEX_SPDIF_SMPRATE, spdअगर_sr);
पूर्ण

/* Initialization */

अटल पूर्णांक vortex_core_init(vortex_t *vortex)
अणु

	dev_info(vortex->card->dev, "init started\n");
	/* Hardware Init. */
	hwग_लिखो(vortex->mmio, VORTEX_CTRL, 0xffffffff);
	msleep(5);
	hwग_लिखो(vortex->mmio, VORTEX_CTRL,
		hwपढ़ो(vortex->mmio, VORTEX_CTRL) & 0xffdfffff);
	msleep(5);
	/* Reset IRQ flags */
	hwग_लिखो(vortex->mmio, VORTEX_IRQ_SOURCE, 0xffffffff);
	hwपढ़ो(vortex->mmio, VORTEX_IRQ_STAT);

	vortex_codec_init(vortex);

#अगर_घोषित CHIP_AU8830
	hwग_लिखो(vortex->mmio, VORTEX_CTRL,
		hwपढ़ो(vortex->mmio, VORTEX_CTRL) | 0x1000000);
#पूर्ण_अगर

	/* Init audio engine. */
	vortex_adbdma_init(vortex);
	hwग_लिखो(vortex->mmio, VORTEX_ENGINE_CTRL, 0x0);	//, 0xc83c7e58, 0xc5f93e58
	vortex_adb_init(vortex);
	/* Init processing blocks. */
	vortex_fअगरo_init(vortex);
	vortex_mixer_init(vortex);
	vortex_srcblock_init(vortex);
#अगर_अघोषित CHIP_AU8820
	vortex_eq_init(vortex);
	vortex_spdअगर_init(vortex, 48000, 1);
	vortex_Vort3D_enable(vortex);
#पूर्ण_अगर
#अगर_अघोषित CHIP_AU8810
	vortex_wt_init(vortex);
#पूर्ण_अगर
	// Moved to au88x0.c
	//vortex_connect_शेष(vortex, 1);

	vortex_समय_रखोr(vortex, 0x90);
	// Enable Interrupts.
	// vortex_enable_पूर्णांक() must be first !!
	//  hwग_लिखो(vortex->mmio, VORTEX_IRQ_CTRL, 0);
	// vortex_enable_पूर्णांक(vortex);
	//vortex_enable_समयr_पूर्णांक(vortex);
	//vortex_disable_समयr_पूर्णांक(vortex);

	dev_info(vortex->card->dev, "init.... done.\n");
	spin_lock_init(&vortex->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक vortex_core_shutकरोwn(vortex_t * vortex)
अणु

	dev_info(vortex->card->dev, "shutdown started\n");
#अगर_अघोषित CHIP_AU8820
	vortex_eq_मुक्त(vortex);
	vortex_Vort3D_disable(vortex);
#पूर्ण_अगर
	//vortex_disable_समयr_पूर्णांक(vortex);
	vortex_disable_पूर्णांक(vortex);
	vortex_connect_शेष(vortex, 0);
	/* Reset all DMA fअगरos. */
	vortex_fअगरo_init(vortex);
	/* Erase all audio routes. */
	vortex_adb_init(vortex);

	/* Disable MPU401 */
	//hwग_लिखो(vortex->mmio, VORTEX_IRQ_CTRL, hwपढ़ो(vortex->mmio, VORTEX_IRQ_CTRL) & ~IRQ_MIDI);
	//hwग_लिखो(vortex->mmio, VORTEX_CTRL, hwपढ़ो(vortex->mmio, VORTEX_CTRL) & ~CTRL_MIDI_EN);

	hwग_लिखो(vortex->mmio, VORTEX_IRQ_CTRL, 0);
	hwग_लिखो(vortex->mmio, VORTEX_CTRL, 0);
	msleep(5);
	hwग_लिखो(vortex->mmio, VORTEX_IRQ_SOURCE, 0xffff);

	dev_info(vortex->card->dev, "shutdown.... done.\n");
	वापस 0;
पूर्ण

/* Alsa support. */

अटल पूर्णांक vortex_alsafmt_aspfmt(snd_pcm_क्रमmat_t alsafmt, vortex_t *v)
अणु
	पूर्णांक fmt;

	चयन (alsafmt) अणु
	हाल SNDRV_PCM_FORMAT_U8:
		fmt = 0x1;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_MU_LAW:
		fmt = 0x2;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_A_LAW:
		fmt = 0x3;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_SPECIAL:
		fmt = 0x4;	/* guess. */
		अवरोध;
	हाल SNDRV_PCM_FORMAT_IEC958_SUBFRAME_LE:
		fmt = 0x5;	/* guess. */
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_LE:
		fmt = 0x8;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_BE:
		fmt = 0x9;	/* check this... */
		अवरोध;
	शेष:
		fmt = 0x8;
		dev_err(v->card->dev,
			"format unsupported %d\n", alsafmt);
		अवरोध;
	पूर्ण
	वापस fmt;
पूर्ण

/* Some not yet useful translations. */
#अगर 0
प्रकार क्रमागत अणु
	ASPFMTLINEAR16 = 0,	/* 0x8 */
	ASPFMTLINEAR8,		/* 0x1 */
	ASPFMTULAW,		/* 0x2 */
	ASPFMTALAW,		/* 0x3 */
	ASPFMTSPORT,		/* ? */
	ASPFMTSPDIF,		/* ? */
पूर्ण ASPENCODING;

अटल पूर्णांक
vortex_translateक्रमmat(vortex_t * vortex, अक्षर bits, अक्षर nch, पूर्णांक encod)
अणु
	पूर्णांक a, this_194;

	अगर ((bits != 8) && (bits != 16))
		वापस -1;

	चयन (encod) अणु
	हाल 0:
		अगर (bits == 0x10)
			a = 8;	// 16 bit
		अवरोध;
	हाल 1:
		अगर (bits == 8)
			a = 1;	// 8 bit
		अवरोध;
	हाल 2:
		a = 2;		// U_LAW
		अवरोध;
	हाल 3:
		a = 3;		// A_LAW
		अवरोध;
	पूर्ण
	चयन (nch) अणु
	हाल 1:
		this_194 = 0;
		अवरोध;
	हाल 2:
		this_194 = 1;
		अवरोध;
	हाल 4:
		this_194 = 1;
		अवरोध;
	हाल 6:
		this_194 = 1;
		अवरोध;
	पूर्ण
	वापस (a);
पूर्ण

अटल व्योम vortex_cdmacore_setक्रमmat(vortex_t * vortex, पूर्णांक bits, पूर्णांक nch)
अणु
	लघु पूर्णांक d, this_148;

	d = ((bits >> 3) * nch);
	this_148 = 0xbb80 / d;
पूर्ण
#पूर्ण_अगर
