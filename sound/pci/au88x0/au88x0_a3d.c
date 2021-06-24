<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/***************************************************************************
 *            au88x0_a3d.c
 *
 *  Fri Jul 18 14:16:22 2003
 *  Copyright  2003  mjander
 *  mjander@users.sourceक्रमge.net
 *
 * A3D. You may think i'm crazy, but this may work someday. Who knows...
 ****************************************************************************/

/*
 */

#समावेश "au88x0_a3d.h"
#समावेश "au88x0_a3ddata.c"
#समावेश "au88x0_xtalk.h"
#समावेश "au88x0.h"

अटल व्योम
a3dsrc_SetTimeConsts(a3dsrc_t * a, लघु HrtfTrack, लघु ItdTrack,
		     लघु GTrack, लघु CTrack)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);
	hwग_लिखो(vortex->mmio,
		a3d_addrA(a->slice, a->source, A3D_A_HrtfTrackTC), HrtfTrack);
	hwग_लिखो(vortex->mmio,
		a3d_addrA(a->slice, a->source, A3D_A_ITDTrackTC), ItdTrack);
	hwग_लिखो(vortex->mmio,
		a3d_addrA(a->slice, a->source, A3D_A_GainTrackTC), GTrack);
	hwग_लिखो(vortex->mmio,
		a3d_addrA(a->slice, a->source, A3D_A_CoeffTrackTC), CTrack);
पूर्ण

#अगर 0
अटल व्योम
a3dsrc_GetTimeConsts(a3dsrc_t * a, लघु *HrtfTrack, लघु *ItdTrack,
		     लघु *GTrack, लघु *CTrack)
अणु
	// stub!
पूर्ण

#पूर्ण_अगर
/* Aपंचांगospheric असलorption. */

अटल व्योम
a3dsrc_SetAपंचांगosTarget(a3dsrc_t * a, लघु aa, लघु b, लघु c, लघु d,
		      लघु e)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);
	hwग_लिखो(vortex->mmio,
		a3d_addrB(a->slice, a->source, A3D_B_A21Target),
		(e << 0x10) | d);
	hwग_लिखो(vortex->mmio,
		a3d_addrB(a->slice, a->source, A3D_B_B10Target),
		(b << 0x10) | aa);
	hwग_लिखो(vortex->mmio,
		a3d_addrB(a->slice, a->source, A3D_B_B2Target), c);
पूर्ण

अटल व्योम
a3dsrc_SetAपंचांगosCurrent(a3dsrc_t * a, लघु aa, लघु b, लघु c, लघु d,
		       लघु e)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);
	hwग_लिखो(vortex->mmio,
		a3d_addrB(a->slice, a->source, A3D_B_A12Current),
		(e << 0x10) | d);
	hwग_लिखो(vortex->mmio,
		a3d_addrB(a->slice, a->source, A3D_B_B01Current),
		(b << 0x10) | aa);
	hwग_लिखो(vortex->mmio,
		a3d_addrB(a->slice, a->source, A3D_B_B2Current), c);
पूर्ण

अटल व्योम
a3dsrc_SetAपंचांगosState(a3dsrc_t * a, लघु x1, लघु x2, लघु y1, लघु y2)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);
	hwग_लिखो(vortex->mmio, a3d_addrA(a->slice, a->source, A3D_A_x1), x1);
	hwग_लिखो(vortex->mmio, a3d_addrA(a->slice, a->source, A3D_A_x2), x2);
	hwग_लिखो(vortex->mmio, a3d_addrA(a->slice, a->source, A3D_A_y1), y1);
	hwग_लिखो(vortex->mmio, a3d_addrA(a->slice, a->source, A3D_A_y2), y2);
पूर्ण

#अगर 0
अटल व्योम
a3dsrc_GetAपंचांगosTarget(a3dsrc_t * a, लघु *aa, लघु *b, लघु *c,
		      लघु *d, लघु *e)
अणु
पूर्ण
अटल व्योम
a3dsrc_GetAपंचांगosCurrent(a3dsrc_t * a, लघु *bb01, लघु *ab01, लघु *b2,
		       लघु *aa12, लघु *ba12)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);
	*aa12 =
	    hwपढ़ो(vortex->mmio,
		   a3d_addrA(a->slice, a->source, A3D_A_A12Current));
	*ba12 =
	    hwपढ़ो(vortex->mmio,
		   a3d_addrB(a->slice, a->source, A3D_B_A12Current));
	*ab01 =
	    hwपढ़ो(vortex->mmio,
		   a3d_addrA(a->slice, a->source, A3D_A_B01Current));
	*bb01 =
	    hwपढ़ो(vortex->mmio,
		   a3d_addrB(a->slice, a->source, A3D_B_B01Current));
	*b2 =
	    hwपढ़ो(vortex->mmio,
		   a3d_addrA(a->slice, a->source, A3D_A_B2Current));
पूर्ण

अटल व्योम
a3dsrc_GetAपंचांगosState(a3dsrc_t * a, लघु *x1, लघु *x2, लघु *y1, लघु *y2)
अणु

पूर्ण

#पूर्ण_अगर
/* HRTF */

अटल व्योम
a3dsrc_SetHrtfTarget(a3dsrc_t * a, a3d_Hrtf_t स्थिर aa, a3d_Hrtf_t स्थिर b)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);
	पूर्णांक i;

	क्रम (i = 0; i < HRTF_SZ; i++)
		hwग_लिखो(vortex->mmio,
			a3d_addrB(a->slice, a->source,
				  A3D_B_HrtfTarget) + (i << 2),
			(b[i] << 0x10) | aa[i]);
पूर्ण

अटल व्योम
a3dsrc_SetHrtfCurrent(a3dsrc_t * a, a3d_Hrtf_t स्थिर aa, a3d_Hrtf_t स्थिर b)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);
	पूर्णांक i;

	क्रम (i = 0; i < HRTF_SZ; i++)
		hwग_लिखो(vortex->mmio,
			a3d_addrB(a->slice, a->source,
				  A3D_B_HrtfCurrent) + (i << 2),
			(b[i] << 0x10) | aa[i]);
पूर्ण

अटल व्योम
a3dsrc_SetHrtfState(a3dsrc_t * a, a3d_Hrtf_t स्थिर aa, a3d_Hrtf_t स्थिर b)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);
	पूर्णांक i;

	क्रम (i = 0; i < HRTF_SZ; i++)
		hwग_लिखो(vortex->mmio,
			a3d_addrB(a->slice, a->source,
				  A3D_B_HrtfDelayLine) + (i << 2),
			(b[i] << 0x10) | aa[i]);
पूर्ण

अटल व्योम a3dsrc_SetHrtfOutput(a3dsrc_t * a, लघु left, लघु right)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);
	hwग_लिखो(vortex->mmio,
		a3d_addrA(a->slice, a->source, A3D_A_HrtfOutL), left);
	hwग_लिखो(vortex->mmio,
		a3d_addrA(a->slice, a->source, A3D_A_HrtfOutR), right);
पूर्ण

#अगर 0
अटल व्योम a3dsrc_GetHrtfTarget(a3dsrc_t * a, a3d_Hrtf_t aa, a3d_Hrtf_t b)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);
	पूर्णांक i;

	क्रम (i = 0; i < HRTF_SZ; i++)
		aa[i] =
		    hwपढ़ो(vortex->mmio,
			   a3d_addrA(a->slice, a->source,
				     A3D_A_HrtfTarget + (i << 2)));
	क्रम (i = 0; i < HRTF_SZ; i++)
		b[i] =
		    hwपढ़ो(vortex->mmio,
			   a3d_addrB(a->slice, a->source,
				     A3D_B_HrtfTarget + (i << 2)));
पूर्ण

अटल व्योम a3dsrc_GetHrtfCurrent(a3dsrc_t * a, a3d_Hrtf_t aa, a3d_Hrtf_t b)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);
	पूर्णांक i;

	क्रम (i = 0; i < HRTF_SZ; i++)
		aa[i] =
		    hwपढ़ो(vortex->mmio,
			   a3d_addrA(a->slice, a->source,
				     A3D_A_HrtfCurrent + (i << 2)));
	क्रम (i = 0; i < HRTF_SZ; i++)
		b[i] =
		    hwपढ़ो(vortex->mmio,
			   a3d_addrB(a->slice, a->source,
				     A3D_B_HrtfCurrent + (i << 2)));
पूर्ण

अटल व्योम a3dsrc_GetHrtfState(a3dsrc_t * a, a3d_Hrtf_t aa, a3d_Hrtf_t b)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);
	पूर्णांक i;
	// FIXME: verअगरy this!
	क्रम (i = 0; i < HRTF_SZ; i++)
		aa[i] =
		    hwपढ़ो(vortex->mmio,
			   a3d_addrA(a->slice, a->source,
				     A3D_A_HrtfDelayLine + (i << 2)));
	क्रम (i = 0; i < HRTF_SZ; i++)
		b[i] =
		    hwपढ़ो(vortex->mmio,
			   a3d_addrB(a->slice, a->source,
				     A3D_B_HrtfDelayLine + (i << 2)));
पूर्ण

अटल व्योम a3dsrc_GetHrtfOutput(a3dsrc_t * a, लघु *left, लघु *right)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);
	*left =
	    hwपढ़ो(vortex->mmio,
		   a3d_addrA(a->slice, a->source, A3D_A_HrtfOutL));
	*right =
	    hwपढ़ो(vortex->mmio,
		   a3d_addrA(a->slice, a->source, A3D_A_HrtfOutR));
पूर्ण

#पूर्ण_अगर

/* Interaural Time Dअगरference. 
 * "The other मुख्य clue that humans use to locate sounds, is called 
 * Interaural Time Dअगरference (ITD). The dअगरferences in distance from 
 * the sound source to a listeners ears means  that the sound will 
 * reach one ear slightly beक्रमe the other....", found somewhere with google.*/
अटल व्योम a3dsrc_SetItdTarget(a3dsrc_t * a, लघु litd, लघु ritd)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);

	अगर (litd < 0)
		litd = 0;
	अगर (litd > 0x57FF)
		litd = 0x57FF;
	अगर (ritd < 0)
		ritd = 0;
	अगर (ritd > 0x57FF)
		ritd = 0x57FF;
	hwग_लिखो(vortex->mmio,
		a3d_addrB(a->slice, a->source, A3D_B_ITDTarget),
		(ritd << 0x10) | litd);
	//hwग_लिखो(vortex->mmio, addr(0x191DF+5, this04, this08), (ritd<<0x10)|litd);
पूर्ण

अटल व्योम a3dsrc_SetItdCurrent(a3dsrc_t * a, लघु litd, लघु ritd)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);

	अगर (litd < 0)
		litd = 0;
	अगर (litd > 0x57FF)
		litd = 0x57FF;
	अगर (ritd < 0)
		ritd = 0;
	अगर (ritd > 0x57FF)
		ritd = 0x57FF;
	hwग_लिखो(vortex->mmio,
		a3d_addrB(a->slice, a->source, A3D_B_ITDCurrent),
		(ritd << 0x10) | litd);
	//hwग_लिखो(vortex->mmio, addr(0x191DF+1, this04, this08), (ritd<<0x10)|litd);
पूर्ण

अटल व्योम a3dsrc_SetItdDline(a3dsrc_t * a, a3d_ItdDline_t स्थिर dline)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);
	पूर्णांक i;
	/* 45 != 40 -> Check this ! */
	क्रम (i = 0; i < DLINE_SZ; i++)
		hwग_लिखो(vortex->mmio,
			a3d_addrA(a->slice, a->source,
				  A3D_A_ITDDelayLine) + (i << 2), dline[i]);
पूर्ण

#अगर 0
अटल व्योम a3dsrc_GetItdTarget(a3dsrc_t * a, लघु *litd, लघु *ritd)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);
	*ritd =
	    hwपढ़ो(vortex->mmio,
		   a3d_addrA(a->slice, a->source, A3D_A_ITDTarget));
	*litd =
	    hwपढ़ो(vortex->mmio,
		   a3d_addrB(a->slice, a->source, A3D_B_ITDTarget));
पूर्ण

अटल व्योम a3dsrc_GetItdCurrent(a3dsrc_t * a, लघु *litd, लघु *ritd)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);

	*ritd =
	    hwपढ़ो(vortex->mmio,
		   a3d_addrA(a->slice, a->source, A3D_A_ITDCurrent));
	*litd =
	    hwपढ़ो(vortex->mmio,
		   a3d_addrB(a->slice, a->source, A3D_B_ITDCurrent));
पूर्ण

अटल व्योम a3dsrc_GetItdDline(a3dsrc_t * a, a3d_ItdDline_t dline)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);
	पूर्णांक i;

	क्रम (i = 0; i < DLINE_SZ; i++)
		dline[i] =
		    hwपढ़ो(vortex->mmio,
			   a3d_addrA(a->slice, a->source,
				     A3D_A_ITDDelayLine + (i << 2)));
पूर्ण

#पूर्ण_अगर
/* This is may be used क्रम ILD Interaural Level Dअगरference. */

अटल व्योम a3dsrc_SetGainTarget(a3dsrc_t * a, लघु left, लघु right)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);
	hwग_लिखो(vortex->mmio,
		a3d_addrB(a->slice, a->source, A3D_B_GainTarget),
		(right << 0x10) | left);
पूर्ण

अटल व्योम a3dsrc_SetGainCurrent(a3dsrc_t * a, लघु left, लघु right)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);
	hwग_लिखो(vortex->mmio,
		a3d_addrB(a->slice, a->source, A3D_B_GainCurrent),
		(right << 0x10) | left);
पूर्ण

#अगर 0
अटल व्योम a3dsrc_GetGainTarget(a3dsrc_t * a, लघु *left, लघु *right)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);
	*right =
	    hwपढ़ो(vortex->mmio,
		   a3d_addrA(a->slice, a->source, A3D_A_GainTarget));
	*left =
	    hwपढ़ो(vortex->mmio,
		   a3d_addrB(a->slice, a->source, A3D_B_GainTarget));
पूर्ण

अटल व्योम a3dsrc_GetGainCurrent(a3dsrc_t * a, लघु *left, लघु *right)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);
	*right =
	    hwपढ़ो(vortex->mmio,
		   a3d_addrA(a->slice, a->source, A3D_A_GainCurrent));
	*left =
	    hwपढ़ो(vortex->mmio,
		   a3d_addrB(a->slice, a->source, A3D_B_GainCurrent));
पूर्ण

/* CA3dIO this func seems to be अंतरभूतd all over this place. */
अटल व्योम CA3dIO_WriteReg(a3dsrc_t * a, अचिन्हित दीर्घ addr, लघु aa, लघु b)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);
	hwग_लिखो(vortex->mmio, addr, (aa << 0x10) | b);
पूर्ण

#पूर्ण_अगर
/* Generic A3D stuff */

अटल व्योम a3dsrc_SetA3DSampleRate(a3dsrc_t * a, पूर्णांक sr)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);
	पूर्णांक esp0 = 0;

	esp0 = (((esp0 & 0x7fffffff) | 0xB8000000) & 0x7) | ((sr & 0x1f) << 3);
	hwग_लिखो(vortex->mmio, A3D_SLICE_Control + ((a->slice) << 0xd), esp0);
	//hwग_लिखो(vortex->mmio, 0x19C38 + (this08<<0xd), esp0);
पूर्ण

अटल व्योम a3dsrc_EnableA3D(a3dsrc_t * a)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);
	hwग_लिखो(vortex->mmio, A3D_SLICE_Control + ((a->slice) << 0xd),
		0xF0000001);
	//hwग_लिखो(vortex->mmio, 0x19C38 + (this08<<0xd), 0xF0000001);
पूर्ण

अटल व्योम a3dsrc_DisableA3D(a3dsrc_t * a)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);
	hwग_लिखो(vortex->mmio, A3D_SLICE_Control + ((a->slice) << 0xd),
		0xF0000000);
पूर्ण

अटल व्योम a3dsrc_SetA3DControlReg(a3dsrc_t * a, अचिन्हित दीर्घ ctrl)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);
	hwग_लिखो(vortex->mmio, A3D_SLICE_Control + ((a->slice) << 0xd), ctrl);
पूर्ण

अटल व्योम a3dsrc_SetA3DPoपूर्णांकerReg(a3dsrc_t * a, अचिन्हित दीर्घ ptr)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);
	hwग_लिखो(vortex->mmio, A3D_SLICE_Poपूर्णांकers + ((a->slice) << 0xd), ptr);
पूर्ण

#अगर 0
अटल व्योम a3dsrc_GetA3DSampleRate(a3dsrc_t * a, पूर्णांक *sr)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);
	*sr = ((hwपढ़ो(vortex->mmio, A3D_SLICE_Control + (a->slice << 0xd))
		>> 3) & 0x1f);
	//*sr = ((hwपढ़ो(vortex->mmio, 0x19C38 + (this08<<0xd))>>3)&0x1f);
पूर्ण

अटल व्योम a3dsrc_GetA3DControlReg(a3dsrc_t * a, अचिन्हित दीर्घ *ctrl)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);
	*ctrl = hwपढ़ो(vortex->mmio, A3D_SLICE_Control + ((a->slice) << 0xd));
पूर्ण

अटल व्योम a3dsrc_GetA3DPoपूर्णांकerReg(a3dsrc_t * a, अचिन्हित दीर्घ *ptr)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);
	*ptr = hwपढ़ो(vortex->mmio, A3D_SLICE_Poपूर्णांकers + ((a->slice) << 0xd));
पूर्ण

#पूर्ण_अगर
अटल व्योम a3dsrc_ZeroSliceIO(a3dsrc_t * a)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++)
		hwग_लिखो(vortex->mmio,
			A3D_SLICE_VDBDest +
			((((a->slice) << 0xb) + i) << 2), 0);
	क्रम (i = 0; i < 4; i++)
		hwग_लिखो(vortex->mmio,
			A3D_SLICE_VDBSource +
			((((a->slice) << 0xb) + i) << 2), 0);
पूर्ण

/* Reset Single A3D source. */
अटल व्योम a3dsrc_ZeroState(a3dsrc_t * a)
अणु
	/*
	pr_debug( "vortex: ZeroState slice: %d, source %d\n",
	       a->slice, a->source);
	*/
	a3dsrc_SetAपंचांगosState(a, 0, 0, 0, 0);
	a3dsrc_SetHrtfState(a, A3dHrirZeros, A3dHrirZeros);
	a3dsrc_SetItdDline(a, A3dItdDlineZeros);
	a3dsrc_SetHrtfOutput(a, 0, 0);
	a3dsrc_SetTimeConsts(a, 0, 0, 0, 0);

	a3dsrc_SetAपंचांगosCurrent(a, 0, 0, 0, 0, 0);
	a3dsrc_SetAपंचांगosTarget(a, 0, 0, 0, 0, 0);
	a3dsrc_SetItdCurrent(a, 0, 0);
	a3dsrc_SetItdTarget(a, 0, 0);
	a3dsrc_SetGainCurrent(a, 0, 0);
	a3dsrc_SetGainTarget(a, 0, 0);

	a3dsrc_SetHrtfCurrent(a, A3dHrirZeros, A3dHrirZeros);
	a3dsrc_SetHrtfTarget(a, A3dHrirZeros, A3dHrirZeros);
पूर्ण

/* Reset entire A3D engine */
अटल व्योम a3dsrc_ZeroStateA3D(a3dsrc_t *a, vortex_t *v)
अणु
	पूर्णांक i, var, var2;

	अगर ((a->vortex) == शून्य) अणु
		dev_err(v->card->dev,
			"ZeroStateA3D: ERROR: a->vortex is NULL\n");
		वापस;
	पूर्ण

	a3dsrc_SetA3DControlReg(a, 0);
	a3dsrc_SetA3DPoपूर्णांकerReg(a, 0);

	var = a->slice;
	var2 = a->source;
	क्रम (i = 0; i < 4; i++) अणु
		a->slice = i;
		a3dsrc_ZeroSliceIO(a);
		//a3dsrc_ZeroState(a);
	पूर्ण
	a->source = var2;
	a->slice = var;
पूर्ण

/* Program A3D block as pass through */
अटल व्योम a3dsrc_ProgramPipe(a3dsrc_t * a)
अणु
	a3dsrc_SetTimeConsts(a, 0, 0, 0, 0);
	a3dsrc_SetAपंचांगosCurrent(a, 0, 0x4000, 0, 0, 0);
	a3dsrc_SetAपंचांगosTarget(a, 0x4000, 0, 0, 0, 0);
	a3dsrc_SetItdCurrent(a, 0, 0);
	a3dsrc_SetItdTarget(a, 0, 0);
	a3dsrc_SetGainCurrent(a, 0x7fff, 0x7fff);
	a3dsrc_SetGainTarget(a, 0x7fff, 0x7fff);

	/* SET HRTF HERE */

	/* Single spike leads to identity transfer function. */
	a3dsrc_SetHrtfCurrent(a, A3dHrirImpulse, A3dHrirImpulse);
	a3dsrc_SetHrtfTarget(a, A3dHrirImpulse, A3dHrirImpulse);

	/* Test: Sounds saturated. */
	//a3dsrc_SetHrtfCurrent(a, A3dHrirSatTest, A3dHrirSatTest);
	//a3dsrc_SetHrtfTarget(a, A3dHrirSatTest, A3dHrirSatTest);      
पूर्ण

/* VDB = Vortex audio Dataflow Bus */
#अगर 0
अटल व्योम a3dsrc_ClearVDBData(a3dsrc_t * a, अचिन्हित दीर्घ aa)
अणु
	vortex_t *vortex = (vortex_t *) (a->vortex);

	// ((aa >> 2) << 8) - (aa >> 2)
	hwग_लिखो(vortex->mmio,
		a3d_addrS(a->slice, A3D_SLICE_VDBDest) + (a->source << 2), 0);
	hwग_लिखो(vortex->mmio,
		a3d_addrS(a->slice,
			  A3D_SLICE_VDBDest + 4) + (a->source << 2), 0);
	/*
	   hwग_लिखो(vortex->mmio, 0x19c00 + (((aa>>2)*255*4)+aa)*8, 0);
	   hwग_लिखो(vortex->mmio, 0x19c04 + (((aa>>2)*255*4)+aa)*8, 0);
	 */
पूर्ण
#पूर्ण_अगर

/* A3D HwSource stuff. */

अटल व्योम vortex_A3dSourceHw_Initialize(vortex_t * v, पूर्णांक source, पूर्णांक slice)
अणु
	a3dsrc_t *a3dsrc = &(v->a3d[source + (slice * 4)]);
	//a3dsrc_t *a3dsrc = &(v->a3d[source + (slice*4)]);

	a3dsrc->vortex = (व्योम *)v;
	a3dsrc->source = source;	/* source */
	a3dsrc->slice = slice;	/* slice */
	a3dsrc_ZeroState(a3dsrc);
	/* Added by me. */
	a3dsrc_SetA3DSampleRate(a3dsrc, 0x11);
पूर्ण

अटल पूर्णांक Vort3DRend_Initialize(vortex_t * v, अचिन्हित लघु mode)
अणु
	v->xt_mode = mode;	/* this_14 */

	vortex_XtalkHw_init(v);
	vortex_XtalkHw_SetGainsAllChan(v);
	चयन (v->xt_mode) अणु
	हाल XT_SPEAKER0:
		vortex_XtalkHw_ProgramXtalkNarrow(v);
		अवरोध;
	हाल XT_SPEAKER1:
		vortex_XtalkHw_ProgramXtalkWide(v);
		अवरोध;
	शेष:
	हाल XT_HEADPHONE:
		vortex_XtalkHw_ProgramPipe(v);
		अवरोध;
	हाल XT_DIAMOND:
		vortex_XtalkHw_ProgramDiamondXtalk(v);
		अवरोध;
	पूर्ण
	vortex_XtalkHw_SetSampleRate(v, 0x11);
	vortex_XtalkHw_Enable(v);
	वापस 0;
पूर्ण

/* 3D Sound entry poपूर्णांकs. */

अटल पूर्णांक vortex_a3d_रेजिस्टर_controls(vortex_t * vortex);
अटल व्योम vortex_a3d_unरेजिस्टर_controls(vortex_t * vortex);
/* A3D base support init/shuकरोwn */
अटल व्योम vortex_Vort3D_enable(vortex_t *v)
अणु
	पूर्णांक i;

	Vort3DRend_Initialize(v, XT_HEADPHONE);
	क्रम (i = 0; i < NR_A3D; i++) अणु
		vortex_A3dSourceHw_Initialize(v, i % 4, i >> 2);
		a3dsrc_ZeroStateA3D(&v->a3d[0], v);
	पूर्ण
	/* Register ALSA controls */
	vortex_a3d_रेजिस्टर_controls(v);
पूर्ण

अटल व्योम vortex_Vort3D_disable(vortex_t * v)
अणु
	vortex_XtalkHw_Disable(v);
	vortex_a3d_unरेजिस्टर_controls(v);
पूर्ण

/* Make A3D subप्रणाली connections. */
अटल व्योम vortex_Vort3D_connect(vortex_t * v, पूर्णांक en)
अणु
	पूर्णांक i;
	
// Disable AU8810 routes, since they seem to be wrong (in au8810.h).
#अगर_घोषित CHIP_AU8810
	वापस;
#पूर्ण_अगर
	
#अगर 1
	/* Alloc Xtalk mixin resources */
	v->mixxtlk[0] =
	    vortex_adb_checkinout(v, v->fixed_res, en, VORTEX_RESOURCE_MIXIN);
	अगर (v->mixxtlk[0] < 0) अणु
		dev_warn(v->card->dev,
			 "vortex_Vort3D: ERROR: not enough free mixer resources.\n");
		वापस;
	पूर्ण
	v->mixxtlk[1] =
	    vortex_adb_checkinout(v, v->fixed_res, en, VORTEX_RESOURCE_MIXIN);
	अगर (v->mixxtlk[1] < 0) अणु
		dev_warn(v->card->dev,
			 "vortex_Vort3D: ERROR: not enough free mixer resources.\n");
		वापस;
	पूर्ण
#पूर्ण_अगर

	/* Connect A3D -> XTALK */
	क्रम (i = 0; i < 4; i++) अणु
		// 2 outमाला_दो per each A3D slice. 
		vortex_route(v, en, 0x11, ADB_A3DOUT(i * 2), ADB_XTALKIN(i));
		vortex_route(v, en, 0x11, ADB_A3DOUT(i * 2) + 1, ADB_XTALKIN(5 + i));
	पूर्ण
#अगर 0
	vortex_route(v, en, 0x11, ADB_XTALKOUT(0), ADB_EQIN(2));
	vortex_route(v, en, 0x11, ADB_XTALKOUT(1), ADB_EQIN(3));
#अन्यथा
	/* Connect XTalk -> mixer */
	vortex_route(v, en, 0x11, ADB_XTALKOUT(0), ADB_MIXIN(v->mixxtlk[0]));
	vortex_route(v, en, 0x11, ADB_XTALKOUT(1), ADB_MIXIN(v->mixxtlk[1]));
	vortex_connection_mixin_mix(v, en, v->mixxtlk[0], v->mixplayb[0], 0);
	vortex_connection_mixin_mix(v, en, v->mixxtlk[1], v->mixplayb[1], 0);
	vortex_mix_setinputvolumebyte(v, v->mixplayb[0], v->mixxtlk[0],
				      en ? MIX_DEFIGAIN : VOL_MIN);
	vortex_mix_setinputvolumebyte(v, v->mixplayb[1], v->mixxtlk[1],
				      en ? MIX_DEFIGAIN : VOL_MIN);
	अगर (VORTEX_IS_QUAD(v)) अणु
		vortex_connection_mixin_mix(v, en, v->mixxtlk[0],
					    v->mixplayb[2], 0);
		vortex_connection_mixin_mix(v, en, v->mixxtlk[1],
					    v->mixplayb[3], 0);
		vortex_mix_setinputvolumebyte(v, v->mixplayb[2],
					      v->mixxtlk[0],
					      en ? MIX_DEFIGAIN : VOL_MIN);
		vortex_mix_setinputvolumebyte(v, v->mixplayb[3],
					      v->mixxtlk[1],
					      en ? MIX_DEFIGAIN : VOL_MIN);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/* Initialize one single A3D source. */
अटल व्योम vortex_Vort3D_InitializeSource(a3dsrc_t *a, पूर्णांक en, vortex_t *v)
अणु
	अगर (a->vortex == शून्य) अणु
		dev_warn(v->card->dev,
			 "Vort3D_InitializeSource: A3D source not initialized\n");
		वापस;
	पूर्ण
	अगर (en) अणु
		a3dsrc_ProgramPipe(a);
		a3dsrc_SetA3DSampleRate(a, 0x11);
		a3dsrc_SetTimeConsts(a, HrtfTCDefault,
				     ItdTCDefault, GainTCDefault,
				     CoefTCDefault);
		/* Remark: zero gain is muted. */
		//a3dsrc_SetGainTarget(a,0,0);
		//a3dsrc_SetGainCurrent(a,0,0);
		a3dsrc_EnableA3D(a);
	पूर्ण अन्यथा अणु
		a3dsrc_DisableA3D(a);
		a3dsrc_ZeroState(a);
	पूर्ण
पूर्ण

/* Conversion of coordinates पूर्णांकo 3D parameters. */

अटल व्योम vortex_a3d_coord2hrtf(a3d_Hrtf_t hrtf, पूर्णांक *coord)
अणु
	/* FIXME: implement this. */

पूर्ण
अटल व्योम vortex_a3d_coord2itd(a3d_Itd_t itd, पूर्णांक *coord)
अणु
	/* FIXME: implement this. */

पूर्ण
अटल व्योम vortex_a3d_coord2ild(a3d_LRGains_t ild, पूर्णांक left, पूर्णांक right)
अणु
	/* FIXME: implement this. */

पूर्ण
अटल व्योम vortex_a3d_translate_filter(a3d_aपंचांगos_t filter, पूर्णांक *params)
अणु
	/* FIXME: implement this. */

पूर्ण

/* ALSA control पूर्णांकerface.  */

अटल पूर्णांक
snd_vortex_a3d_hrtf_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 6;
	uinfo->value.पूर्णांकeger.min = 0x00000000;
	uinfo->value.पूर्णांकeger.max = 0xffffffff;
	वापस 0;
पूर्ण
अटल पूर्णांक
snd_vortex_a3d_itd_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0x00000000;
	uinfo->value.पूर्णांकeger.max = 0xffffffff;
	वापस 0;
पूर्ण
अटल पूर्णांक
snd_vortex_a3d_ild_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0x00000000;
	uinfo->value.पूर्णांकeger.max = 0xffffffff;
	वापस 0;
पूर्ण
अटल पूर्णांक
snd_vortex_a3d_filter_info(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 4;
	uinfo->value.पूर्णांकeger.min = 0x00000000;
	uinfo->value.पूर्णांकeger.max = 0xffffffff;
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_vortex_a3d_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	//a3dsrc_t *a = kcontrol->निजी_data;
	/* No पढ़ो yet. Would this be really useable/needed ? */

	वापस 0;
पूर्ण

अटल पूर्णांक
snd_vortex_a3d_hrtf_put(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	a3dsrc_t *a = kcontrol->निजी_data;
	पूर्णांक i;
	पूर्णांक coord[6];
	क्रम (i = 0; i < 6; i++)
		coord[i] = ucontrol->value.पूर्णांकeger.value[i];
	/* Translate orientation coordinates to a3d params. */
	vortex_a3d_coord2hrtf(a->hrtf[0], coord);
	vortex_a3d_coord2hrtf(a->hrtf[1], coord);
	a3dsrc_SetHrtfTarget(a, a->hrtf[0], a->hrtf[1]);
	a3dsrc_SetHrtfCurrent(a, a->hrtf[0], a->hrtf[1]);
	वापस 1;
पूर्ण

अटल पूर्णांक
snd_vortex_a3d_itd_put(काष्ठा snd_kcontrol *kcontrol,
		       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	a3dsrc_t *a = kcontrol->निजी_data;
	पूर्णांक coord[6];
	पूर्णांक i;
	क्रम (i = 0; i < 6; i++)
		coord[i] = ucontrol->value.पूर्णांकeger.value[i];
	/* Translate orientation coordinates to a3d params. */
	vortex_a3d_coord2itd(a->hrtf[0], coord);
	vortex_a3d_coord2itd(a->hrtf[1], coord);
	/* Inter aural समय dअगरference. */
	a3dsrc_SetItdTarget(a, a->itd[0], a->itd[1]);
	a3dsrc_SetItdCurrent(a, a->itd[0], a->itd[1]);
	a3dsrc_SetItdDline(a, a->dline);
	वापस 1;
पूर्ण

अटल पूर्णांक
snd_vortex_a3d_ild_put(काष्ठा snd_kcontrol *kcontrol,
		       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	a3dsrc_t *a = kcontrol->निजी_data;
	पूर्णांक l, r;
	/* There may be some scale tranlation needed here. */
	l = ucontrol->value.पूर्णांकeger.value[0];
	r = ucontrol->value.पूर्णांकeger.value[1];
	vortex_a3d_coord2ild(a->ild, l, r);
	/* Left Right panning. */
	a3dsrc_SetGainTarget(a, l, r);
	a3dsrc_SetGainCurrent(a, l, r);
	वापस 1;
पूर्ण

अटल पूर्णांक
snd_vortex_a3d_filter_put(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	a3dsrc_t *a = kcontrol->निजी_data;
	पूर्णांक i;
	पूर्णांक params[6];
	क्रम (i = 0; i < 6; i++)
		params[i] = ucontrol->value.पूर्णांकeger.value[i];
	/* Translate generic filter params to a3d filter params. */
	vortex_a3d_translate_filter(a->filter, params);
	/* Aपंचांगospheric असलorption and filtering. */
	a3dsrc_SetAपंचांगosTarget(a, a->filter[0],
			      a->filter[1], a->filter[2],
			      a->filter[3], a->filter[4]);
	a3dsrc_SetAपंचांगosCurrent(a, a->filter[0],
			       a->filter[1], a->filter[2],
			       a->filter[3], a->filter[4]);
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new vortex_a3d_kcontrol = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
	.name = "Playback PCM advanced processing",
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.info = snd_vortex_a3d_hrtf_info,
	.get = snd_vortex_a3d_get,
	.put = snd_vortex_a3d_hrtf_put,
पूर्ण;

/* Control (un)registration. */
अटल पूर्णांक vortex_a3d_रेजिस्टर_controls(vortex_t *vortex)
अणु
	काष्ठा snd_kcontrol *kcontrol;
	पूर्णांक err, i;
	/* HRTF controls. */
	क्रम (i = 0; i < NR_A3D; i++) अणु
		अगर ((kcontrol =
		     snd_ctl_new1(&vortex_a3d_kcontrol, &vortex->a3d[i])) == शून्य)
			वापस -ENOMEM;
		kcontrol->id.numid = CTRLID_HRTF;
		kcontrol->info = snd_vortex_a3d_hrtf_info;
		kcontrol->put = snd_vortex_a3d_hrtf_put;
		अगर ((err = snd_ctl_add(vortex->card, kcontrol)) < 0)
			वापस err;
	पूर्ण
	/* ITD controls. */
	क्रम (i = 0; i < NR_A3D; i++) अणु
		अगर ((kcontrol =
		     snd_ctl_new1(&vortex_a3d_kcontrol, &vortex->a3d[i])) == शून्य)
			वापस -ENOMEM;
		kcontrol->id.numid = CTRLID_ITD;
		kcontrol->info = snd_vortex_a3d_itd_info;
		kcontrol->put = snd_vortex_a3d_itd_put;
		अगर ((err = snd_ctl_add(vortex->card, kcontrol)) < 0)
			वापस err;
	पूर्ण
	/* ILD (gains) controls. */
	क्रम (i = 0; i < NR_A3D; i++) अणु
		अगर ((kcontrol =
		     snd_ctl_new1(&vortex_a3d_kcontrol, &vortex->a3d[i])) == शून्य)
			वापस -ENOMEM;
		kcontrol->id.numid = CTRLID_GAINS;
		kcontrol->info = snd_vortex_a3d_ild_info;
		kcontrol->put = snd_vortex_a3d_ild_put;
		अगर ((err = snd_ctl_add(vortex->card, kcontrol)) < 0)
			वापस err;
	पूर्ण
	/* Filter controls. */
	क्रम (i = 0; i < NR_A3D; i++) अणु
		अगर ((kcontrol =
		     snd_ctl_new1(&vortex_a3d_kcontrol, &vortex->a3d[i])) == शून्य)
			वापस -ENOMEM;
		kcontrol->id.numid = CTRLID_FILTER;
		kcontrol->info = snd_vortex_a3d_filter_info;
		kcontrol->put = snd_vortex_a3d_filter_put;
		अगर ((err = snd_ctl_add(vortex->card, kcontrol)) < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम vortex_a3d_unरेजिस्टर_controls(vortex_t * vortex)
अणु

पूर्ण

/* End of File*/
