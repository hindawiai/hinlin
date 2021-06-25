<शैली गुरु>
 /***************************************************************************\
|*                                                                           *|
|*       Copyright 1993-2003 NVIDIA, Corporation.  All rights reserved.      *|
|*                                                                           *|
|*     NOTICE TO USER:   The source code  is copyrighted under  U.S. and     *|
|*     पूर्णांकernational laws.  Users and possessors of this source code are     *|
|*     hereby granted a nonexclusive,  royalty-मुक्त copyright license to     *|
|*     use this code in inभागidual and commercial software.                  *|
|*                                                                           *|
|*     Any use of this source code must include,  in the user करोcumenta-     *|
|*     tion and  पूर्णांकernal comments to the code,  notices to the end user     *|
|*     as follows:                                                           *|
|*                                                                           *|
|*       Copyright 1993-2003 NVIDIA, Corporation.  All rights reserved.      *|
|*                                                                           *|
|*     NVIDIA, CORPORATION MAKES NO REPRESENTATION ABOUT THE SUITABILITY     *|
|*     OF  THIS SOURCE  CODE  FOR ANY PURPOSE.  IT IS  PROVIDED  "AS IS"     *|
|*     WITHOUT EXPRESS OR IMPLIED WARRANTY OF ANY KIND.  NVIDIA, CORPOR-     *|
|*     ATION DISCLAIMS ALL WARRANTIES  WITH REGARD  TO THIS SOURCE CODE,     *|
|*     INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGE-     *|
|*     MENT,  AND FITNESS  FOR A PARTICULAR PURPOSE.   IN NO EVENT SHALL     *|
|*     NVIDIA, CORPORATION  BE LIABLE FOR ANY SPECIAL,  INसूचीECT,  INCI-     *|
|*     DENTAL, OR CONSEQUENTIAL DAMAGES,  OR ANY DAMAGES  WHATSOEVER RE-     *|
|*     SULTING FROM LOSS OF USE,  DATA OR PROFITS,  WHETHER IN AN ACTION     *|
|*     OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,  ARISING OUT OF     *|
|*     OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOURCE CODE.     *|
|*                                                                           *|
|*     U.S. Government  End  Users.   This source code  is a "commercial     *|
|*     item,"  as that  term is  defined at  48 C.F.R. 2.101 (OCT 1995),     *|
|*     consisting  of "commercial  computer  software"  and  "commercial     *|
|*     computer  software  करोcumentation,"  as such  terms  are  used in     *|
|*     48 C.F.R. 12.212 (SEPT 1995)  and is provided to the U.S. Govern-     *|
|*     ment only as  a commercial end item.   Consistent with  48 C.F.R.     *|
|*     12.212 and  48 C.F.R. 227.7202-1 through  227.7202-4 (JUNE 1995),     *|
|*     all U.S. Government End Users  acquire the source code  with only     *|
|*     those rights set क्रमth herein.                                        *|
|*                                                                           *|
 \***************************************************************************/

/*
 * GPL Licensing Note - According to Mark Vojkovich, author of the Xorg/
 * XFree86 'nv' driver, this source code is provided under MIT-style licensing
 * where the source code is provided "as is" without warranty of any kind.
 * The only usage restriction is क्रम the copyright notices to be retained
 * whenever code is used.
 *
 * Antonino Daplas <adaplas@pol.net> 2005-03-11
 */

/* $XFree86: xc/programs/Xserver/hw/xमुक्त86/drivers/nv/nv_hw.c,v 1.4 2003/11/03 05:11:25 tsi Exp $ */

#समावेश <linux/pci.h>
#समावेश "nv_type.h"
#समावेश "nv_local.h"
#समावेश "nv_proto.h"

व्योम NVLockUnlock(काष्ठा nvidia_par *par, पूर्णांक Lock)
अणु
	u8 cr11;

	VGA_WR08(par->PCIO, 0x3D4, 0x1F);
	VGA_WR08(par->PCIO, 0x3D5, Lock ? 0x99 : 0x57);

	VGA_WR08(par->PCIO, 0x3D4, 0x11);
	cr11 = VGA_RD08(par->PCIO, 0x3D5);
	अगर (Lock)
		cr11 |= 0x80;
	अन्यथा
		cr11 &= ~0x80;
	VGA_WR08(par->PCIO, 0x3D5, cr11);
पूर्ण

पूर्णांक NVShowHideCursor(काष्ठा nvidia_par *par, पूर्णांक ShowHide)
अणु
	पूर्णांक cur = par->CurrentState->cursor1;

	par->CurrentState->cursor1 = (par->CurrentState->cursor1 & 0xFE) |
	    (ShowHide & 0x01);
	VGA_WR08(par->PCIO, 0x3D4, 0x31);
	VGA_WR08(par->PCIO, 0x3D5, par->CurrentState->cursor1);

	अगर (par->Architecture == NV_ARCH_40)
		NV_WR32(par->PRAMDAC, 0x0300, NV_RD32(par->PRAMDAC, 0x0300));

	वापस (cur & 0x01);
पूर्ण

/****************************************************************************\
*                                                                            *
* The video arbitration routines calculate some "magic" numbers.  Fixes      *
* the snow seen when accessing the framebuffer without it.                   *
* It just works (I hope).                                                    *
*                                                                            *
\****************************************************************************/

प्रकार काष्ठा अणु
	पूर्णांक graphics_lwm;
	पूर्णांक video_lwm;
	पूर्णांक graphics_burst_size;
	पूर्णांक video_burst_size;
	पूर्णांक valid;
पूर्ण nv4_fअगरo_info;

प्रकार काष्ठा अणु
	पूर्णांक pclk_khz;
	पूर्णांक mclk_khz;
	पूर्णांक nvclk_khz;
	अक्षर mem_page_miss;
	अक्षर mem_latency;
	पूर्णांक memory_width;
	अक्षर enable_video;
	अक्षर gr_during_vid;
	अक्षर pix_bpp;
	अक्षर mem_aligned;
	अक्षर enable_mp;
पूर्ण nv4_sim_state;

प्रकार काष्ठा अणु
	पूर्णांक graphics_lwm;
	पूर्णांक video_lwm;
	पूर्णांक graphics_burst_size;
	पूर्णांक video_burst_size;
	पूर्णांक valid;
पूर्ण nv10_fअगरo_info;

प्रकार काष्ठा अणु
	पूर्णांक pclk_khz;
	पूर्णांक mclk_khz;
	पूर्णांक nvclk_khz;
	अक्षर mem_page_miss;
	अक्षर mem_latency;
	u32 memory_type;
	पूर्णांक memory_width;
	अक्षर enable_video;
	अक्षर gr_during_vid;
	अक्षर pix_bpp;
	अक्षर mem_aligned;
	अक्षर enable_mp;
पूर्ण nv10_sim_state;

अटल व्योम nvGetClocks(काष्ठा nvidia_par *par, अचिन्हित पूर्णांक *MClk,
			अचिन्हित पूर्णांक *NVClk)
अणु
	अचिन्हित पूर्णांक pll, N, M, MB, NB, P;

	अगर (par->Architecture >= NV_ARCH_40) अणु
		pll = NV_RD32(par->PMC, 0x4020);
		P = (pll >> 16) & 0x07;
		pll = NV_RD32(par->PMC, 0x4024);
		M = pll & 0xFF;
		N = (pll >> 8) & 0xFF;
		अगर (((par->Chipset & 0xfff0) == 0x0290) ||
		    ((par->Chipset & 0xfff0) == 0x0390)) अणु
			MB = 1;
			NB = 1;
		पूर्ण अन्यथा अणु
			MB = (pll >> 16) & 0xFF;
			NB = (pll >> 24) & 0xFF;
		पूर्ण
		*MClk = ((N * NB * par->CrystalFreqKHz) / (M * MB)) >> P;

		pll = NV_RD32(par->PMC, 0x4000);
		P = (pll >> 16) & 0x07;
		pll = NV_RD32(par->PMC, 0x4004);
		M = pll & 0xFF;
		N = (pll >> 8) & 0xFF;
		MB = (pll >> 16) & 0xFF;
		NB = (pll >> 24) & 0xFF;

		*NVClk = ((N * NB * par->CrystalFreqKHz) / (M * MB)) >> P;
	पूर्ण अन्यथा अगर (par->twoStagePLL) अणु
		pll = NV_RD32(par->PRAMDAC0, 0x0504);
		M = pll & 0xFF;
		N = (pll >> 8) & 0xFF;
		P = (pll >> 16) & 0x0F;
		pll = NV_RD32(par->PRAMDAC0, 0x0574);
		अगर (pll & 0x80000000) अणु
			MB = pll & 0xFF;
			NB = (pll >> 8) & 0xFF;
		पूर्ण अन्यथा अणु
			MB = 1;
			NB = 1;
		पूर्ण
		*MClk = ((N * NB * par->CrystalFreqKHz) / (M * MB)) >> P;

		pll = NV_RD32(par->PRAMDAC0, 0x0500);
		M = pll & 0xFF;
		N = (pll >> 8) & 0xFF;
		P = (pll >> 16) & 0x0F;
		pll = NV_RD32(par->PRAMDAC0, 0x0570);
		अगर (pll & 0x80000000) अणु
			MB = pll & 0xFF;
			NB = (pll >> 8) & 0xFF;
		पूर्ण अन्यथा अणु
			MB = 1;
			NB = 1;
		पूर्ण
		*NVClk = ((N * NB * par->CrystalFreqKHz) / (M * MB)) >> P;
	पूर्ण अन्यथा
	    अगर (((par->Chipset & 0x0ff0) == 0x0300) ||
		((par->Chipset & 0x0ff0) == 0x0330)) अणु
		pll = NV_RD32(par->PRAMDAC0, 0x0504);
		M = pll & 0x0F;
		N = (pll >> 8) & 0xFF;
		P = (pll >> 16) & 0x07;
		अगर (pll & 0x00000080) अणु
			MB = (pll >> 4) & 0x07;
			NB = (pll >> 19) & 0x1f;
		पूर्ण अन्यथा अणु
			MB = 1;
			NB = 1;
		पूर्ण
		*MClk = ((N * NB * par->CrystalFreqKHz) / (M * MB)) >> P;

		pll = NV_RD32(par->PRAMDAC0, 0x0500);
		M = pll & 0x0F;
		N = (pll >> 8) & 0xFF;
		P = (pll >> 16) & 0x07;
		अगर (pll & 0x00000080) अणु
			MB = (pll >> 4) & 0x07;
			NB = (pll >> 19) & 0x1f;
		पूर्ण अन्यथा अणु
			MB = 1;
			NB = 1;
		पूर्ण
		*NVClk = ((N * NB * par->CrystalFreqKHz) / (M * MB)) >> P;
	पूर्ण अन्यथा अणु
		pll = NV_RD32(par->PRAMDAC0, 0x0504);
		M = pll & 0xFF;
		N = (pll >> 8) & 0xFF;
		P = (pll >> 16) & 0x0F;
		*MClk = (N * par->CrystalFreqKHz / M) >> P;

		pll = NV_RD32(par->PRAMDAC0, 0x0500);
		M = pll & 0xFF;
		N = (pll >> 8) & 0xFF;
		P = (pll >> 16) & 0x0F;
		*NVClk = (N * par->CrystalFreqKHz / M) >> P;
	पूर्ण
पूर्ण

अटल व्योम nv4CalcArbitration(nv4_fअगरo_info * fअगरo, nv4_sim_state * arb)
अणु
	पूर्णांक data, pagemiss, cas, width, video_enable, bpp;
	पूर्णांक nvclks, mclks, pclks, vpagemiss, crtpagemiss, vbs;
	पूर्णांक found, mclk_extra, mclk_loop, cbs, m1, p1;
	पूर्णांक mclk_freq, pclk_freq, nvclk_freq, mp_enable;
	पूर्णांक us_m, us_n, us_p, video_drain_rate, crtc_drain_rate;
	पूर्णांक vpm_us, us_video, vlwm, video_fill_us, cpm_us, us_crt, clwm;

	fअगरo->valid = 1;
	pclk_freq = arb->pclk_khz;
	mclk_freq = arb->mclk_khz;
	nvclk_freq = arb->nvclk_khz;
	pagemiss = arb->mem_page_miss;
	cas = arb->mem_latency;
	width = arb->memory_width >> 6;
	video_enable = arb->enable_video;
	bpp = arb->pix_bpp;
	mp_enable = arb->enable_mp;
	clwm = 0;
	vlwm = 0;
	cbs = 128;
	pclks = 2;
	nvclks = 2;
	nvclks += 2;
	nvclks += 1;
	mclks = 5;
	mclks += 3;
	mclks += 1;
	mclks += cas;
	mclks += 1;
	mclks += 1;
	mclks += 1;
	mclks += 1;
	mclk_extra = 3;
	nvclks += 2;
	nvclks += 1;
	nvclks += 1;
	nvclks += 1;
	अगर (mp_enable)
		mclks += 4;
	nvclks += 0;
	pclks += 0;
	found = 0;
	vbs = 0;
	जबतक (found != 1) अणु
		fअगरo->valid = 1;
		found = 1;
		mclk_loop = mclks + mclk_extra;
		us_m = mclk_loop * 1000 * 1000 / mclk_freq;
		us_n = nvclks * 1000 * 1000 / nvclk_freq;
		us_p = nvclks * 1000 * 1000 / pclk_freq;
		अगर (video_enable) अणु
			video_drain_rate = pclk_freq * 2;
			crtc_drain_rate = pclk_freq * bpp / 8;
			vpagemiss = 2;
			vpagemiss += 1;
			crtpagemiss = 2;
			vpm_us =
			    (vpagemiss * pagemiss) * 1000 * 1000 / mclk_freq;
			अगर (nvclk_freq * 2 > mclk_freq * width)
				video_fill_us =
				    cbs * 1000 * 1000 / 16 / nvclk_freq;
			अन्यथा
				video_fill_us =
				    cbs * 1000 * 1000 / (8 * width) /
				    mclk_freq;
			us_video = vpm_us + us_m + us_n + us_p + video_fill_us;
			vlwm = us_video * video_drain_rate / (1000 * 1000);
			vlwm++;
			vbs = 128;
			अगर (vlwm > 128)
				vbs = 64;
			अगर (vlwm > (256 - 64))
				vbs = 32;
			अगर (nvclk_freq * 2 > mclk_freq * width)
				video_fill_us =
				    vbs * 1000 * 1000 / 16 / nvclk_freq;
			अन्यथा
				video_fill_us =
				    vbs * 1000 * 1000 / (8 * width) /
				    mclk_freq;
			cpm_us =
			    crtpagemiss * pagemiss * 1000 * 1000 / mclk_freq;
			us_crt =
			    us_video + video_fill_us + cpm_us + us_m + us_n +
			    us_p;
			clwm = us_crt * crtc_drain_rate / (1000 * 1000);
			clwm++;
		पूर्ण अन्यथा अणु
			crtc_drain_rate = pclk_freq * bpp / 8;
			crtpagemiss = 2;
			crtpagemiss += 1;
			cpm_us =
			    crtpagemiss * pagemiss * 1000 * 1000 / mclk_freq;
			us_crt = cpm_us + us_m + us_n + us_p;
			clwm = us_crt * crtc_drain_rate / (1000 * 1000);
			clwm++;
		पूर्ण
		m1 = clwm + cbs - 512;
		p1 = m1 * pclk_freq / mclk_freq;
		p1 = p1 * bpp / 8;
		अगर ((p1 < m1) && (m1 > 0)) अणु
			fअगरo->valid = 0;
			found = 0;
			अगर (mclk_extra == 0)
				found = 1;
			mclk_extra--;
		पूर्ण अन्यथा अगर (video_enable) अणु
			अगर ((clwm > 511) || (vlwm > 255)) अणु
				fअगरo->valid = 0;
				found = 0;
				अगर (mclk_extra == 0)
					found = 1;
				mclk_extra--;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (clwm > 519) अणु
				fअगरo->valid = 0;
				found = 0;
				अगर (mclk_extra == 0)
					found = 1;
				mclk_extra--;
			पूर्ण
		पूर्ण
		अगर (clwm < 384)
			clwm = 384;
		अगर (vlwm < 128)
			vlwm = 128;
		data = (पूर्णांक)(clwm);
		fअगरo->graphics_lwm = data;
		fअगरo->graphics_burst_size = 128;
		data = (पूर्णांक)((vlwm + 15));
		fअगरo->video_lwm = data;
		fअगरo->video_burst_size = vbs;
	पूर्ण
पूर्ण

अटल व्योम nv4UpdateArbitrationSettings(अचिन्हित VClk,
					 अचिन्हित pixelDepth,
					 अचिन्हित *burst,
					 अचिन्हित *lwm, काष्ठा nvidia_par *par)
अणु
	nv4_fअगरo_info fअगरo_data;
	nv4_sim_state sim_data;
	अचिन्हित पूर्णांक MClk, NVClk, cfg1;

	nvGetClocks(par, &MClk, &NVClk);

	cfg1 = NV_RD32(par->PFB, 0x00000204);
	sim_data.pix_bpp = (अक्षर)pixelDepth;
	sim_data.enable_video = 0;
	sim_data.enable_mp = 0;
	sim_data.memory_width = (NV_RD32(par->PEXTDEV, 0x0000) & 0x10) ?
	    128 : 64;
	sim_data.mem_latency = (अक्षर)cfg1 & 0x0F;
	sim_data.mem_aligned = 1;
	sim_data.mem_page_miss =
	    (अक्षर)(((cfg1 >> 4) & 0x0F) + ((cfg1 >> 31) & 0x01));
	sim_data.gr_during_vid = 0;
	sim_data.pclk_khz = VClk;
	sim_data.mclk_khz = MClk;
	sim_data.nvclk_khz = NVClk;
	nv4CalcArbitration(&fअगरo_data, &sim_data);
	अगर (fअगरo_data.valid) अणु
		पूर्णांक b = fअगरo_data.graphics_burst_size >> 4;
		*burst = 0;
		जबतक (b >>= 1)
			(*burst)++;
		*lwm = fअगरo_data.graphics_lwm >> 3;
	पूर्ण
पूर्ण

अटल व्योम nv10CalcArbitration(nv10_fअगरo_info * fअगरo, nv10_sim_state * arb)
अणु
	पूर्णांक data, pagemiss, width, video_enable, bpp;
	पूर्णांक nvclks, mclks, pclks, vpagemiss, crtpagemiss;
	पूर्णांक nvclk_fill;
	पूर्णांक found, mclk_extra, mclk_loop, cbs, m1;
	पूर्णांक mclk_freq, pclk_freq, nvclk_freq, mp_enable;
	पूर्णांक us_m, us_m_min, us_n, us_p, crtc_drain_rate;
	पूर्णांक vus_m;
	पूर्णांक vpm_us, us_video, cpm_us, us_crt, clwm;
	पूर्णांक clwm_rnd_करोwn;
	पूर्णांक m2us, us_pipe_min, p1clk, p2;
	पूर्णांक min_mclk_extra;
	पूर्णांक us_min_mclk_extra;

	fअगरo->valid = 1;
	pclk_freq = arb->pclk_khz;	/* freq in KHz */
	mclk_freq = arb->mclk_khz;
	nvclk_freq = arb->nvclk_khz;
	pagemiss = arb->mem_page_miss;
	width = arb->memory_width / 64;
	video_enable = arb->enable_video;
	bpp = arb->pix_bpp;
	mp_enable = arb->enable_mp;
	clwm = 0;

	cbs = 512;

	pclks = 4;	/* lwm detect. */

	nvclks = 3;	/* lwm -> sync. */
	nvclks += 2;	/* fbi bus cycles (1 req + 1 busy) */
	/* 2 edge sync.  may be very बंद to edge so just put one. */
	mclks = 1;
	mclks += 1;	/* arb_hp_req */
	mclks += 5;	/* ap_hp_req   tiling pipeline */

	mclks += 2;	/* tc_req     latency fअगरo */
	mclks += 2;	/* fb_cas_n_  memory request to fbio block */
	mclks += 7;	/* sm_d_rdv   data वापसed from fbio block */

	/* fb.rd.d.Put_gc   need to accumulate 256 bits क्रम पढ़ो */
	अगर (arb->memory_type == 0)
		अगर (arb->memory_width == 64)	/* 64 bit bus */
			mclks += 4;
		अन्यथा
			mclks += 2;
	अन्यथा अगर (arb->memory_width == 64)	/* 64 bit bus */
		mclks += 2;
	अन्यथा
		mclks += 1;

	अगर ((!video_enable) && (arb->memory_width == 128)) अणु
		mclk_extra = (bpp == 32) ? 31 : 42;	/* Margin of error */
		min_mclk_extra = 17;
	पूर्ण अन्यथा अणु
		mclk_extra = (bpp == 32) ? 8 : 4;	/* Margin of error */
		/* mclk_extra = 4; *//* Margin of error */
		min_mclk_extra = 18;
	पूर्ण

	/* 2 edge sync.  may be very बंद to edge so just put one. */
	nvclks += 1;
	nvclks += 1;		/* fbi_d_rdv_n */
	nvclks += 1;		/* Fbi_d_rdata */
	nvclks += 1;		/* crtfअगरo load */

	अगर (mp_enable)
		mclks += 4;	/* Mp can get in with a burst of 8. */
	/* Extra घड़ीs determined by heuristics */

	nvclks += 0;
	pclks += 0;
	found = 0;
	जबतक (found != 1) अणु
		fअगरo->valid = 1;
		found = 1;
		mclk_loop = mclks + mclk_extra;
		/* Mclk latency in us */
		us_m = mclk_loop * 1000 * 1000 / mclk_freq;
		/* Minimum Mclk latency in us */
		us_m_min = mclks * 1000 * 1000 / mclk_freq;
		us_min_mclk_extra = min_mclk_extra * 1000 * 1000 / mclk_freq;
		/* nvclk latency in us */
		us_n = nvclks * 1000 * 1000 / nvclk_freq;
		/* nvclk latency in us */
		us_p = pclks * 1000 * 1000 / pclk_freq;
		us_pipe_min = us_m_min + us_n + us_p;

		/* Mclk latency in us */
		vus_m = mclk_loop * 1000 * 1000 / mclk_freq;

		अगर (video_enable) अणु
			crtc_drain_rate = pclk_freq * bpp / 8;	/* MB/s */

			vpagemiss = 1;	/* self generating page miss */
			vpagemiss += 1;	/* One higher priority beक्रमe */

			crtpagemiss = 2;	/* self generating page miss */
			अगर (mp_enable)
				crtpagemiss += 1;	/* अगर MA0 conflict */

			vpm_us =
			    (vpagemiss * pagemiss) * 1000 * 1000 / mclk_freq;

			/* Video has separate पढ़ो वापस path */
			us_video = vpm_us + vus_m;

			cpm_us =
			    crtpagemiss * pagemiss * 1000 * 1000 / mclk_freq;
			/* Wait क्रम video */
			us_crt = us_video
			    + cpm_us	/* CRT Page miss */
			    + us_m + us_n + us_p	/* other latency */
			    ;

			clwm = us_crt * crtc_drain_rate / (1000 * 1000);
			/* fixed poपूर्णांक <= भग्न_poपूर्णांक - 1.  Fixes that */
			clwm++;
		पूर्ण अन्यथा अणु
		    /* bpp * pclk/8 */
			crtc_drain_rate = pclk_freq * bpp / 8;

			crtpagemiss = 1;	/* self generating page miss */
			crtpagemiss += 1;	/* MA0 page miss */
			अगर (mp_enable)
				crtpagemiss += 1;	/* अगर MA0 conflict */
			cpm_us =
			    crtpagemiss * pagemiss * 1000 * 1000 / mclk_freq;
			us_crt = cpm_us + us_m + us_n + us_p;
			clwm = us_crt * crtc_drain_rate / (1000 * 1000);
			/* fixed poपूर्णांक <= भग्न_poपूर्णांक - 1.  Fixes that */
			clwm++;

			/* Finally, a heuristic check when width == 64 bits */
			अगर (width == 1) अणु
				nvclk_fill = nvclk_freq * 8;
				अगर (crtc_drain_rate * 100 >= nvclk_fill * 102)
					/*Large number to fail */
					clwm = 0xfff;

				अन्यथा अगर (crtc_drain_rate * 100 >=
					 nvclk_fill * 98) अणु
					clwm = 1024;
					cbs = 512;
				पूर्ण
			पूर्ण
		पूर्ण

		/*
		   Overfill check:
		 */

		clwm_rnd_करोwn = ((पूर्णांक)clwm / 8) * 8;
		अगर (clwm_rnd_करोwn < clwm)
			clwm += 8;

		m1 = clwm + cbs - 1024;	/* Amount of overfill */
		m2us = us_pipe_min + us_min_mclk_extra;

		/* pclk cycles to drain */
		p1clk = m2us * pclk_freq / (1000 * 1000);
		p2 = p1clk * bpp / 8;	/* bytes drained. */

		अगर ((p2 < m1) && (m1 > 0)) अणु
			fअगरo->valid = 0;
			found = 0;
			अगर (min_mclk_extra == 0) अणु
				अगर (cbs <= 32) अणु
					/* Can't adjust anymore! */
					found = 1;
				पूर्ण अन्यथा अणु
					/* reduce the burst size */
					cbs = cbs / 2;
				पूर्ण
			पूर्ण अन्यथा अणु
				min_mclk_extra--;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (clwm > 1023) अणु	/* Have some margin */
				fअगरo->valid = 0;
				found = 0;
				अगर (min_mclk_extra == 0)
					/* Can't adjust anymore! */
					found = 1;
				अन्यथा
					min_mclk_extra--;
			पूर्ण
		पूर्ण

		अगर (clwm < (1024 - cbs + 8))
			clwm = 1024 - cbs + 8;
		data = (पूर्णांक)(clwm);
		/*  म_लिखो("CRT LWM: %f bytes, prog: 0x%x, bs: 256\n",
		    clwm, data ); */
		fअगरo->graphics_lwm = data;
		fअगरo->graphics_burst_size = cbs;

		fअगरo->video_lwm = 1024;
		fअगरo->video_burst_size = 512;
	पूर्ण
पूर्ण

अटल व्योम nv10UpdateArbitrationSettings(अचिन्हित VClk,
					  अचिन्हित pixelDepth,
					  अचिन्हित *burst,
					  अचिन्हित *lwm,
					  काष्ठा nvidia_par *par)
अणु
	nv10_fअगरo_info fअगरo_data;
	nv10_sim_state sim_data;
	अचिन्हित पूर्णांक MClk, NVClk, cfg1;

	nvGetClocks(par, &MClk, &NVClk);

	cfg1 = NV_RD32(par->PFB, 0x0204);
	sim_data.pix_bpp = (अक्षर)pixelDepth;
	sim_data.enable_video = 1;
	sim_data.enable_mp = 0;
	sim_data.memory_type = (NV_RD32(par->PFB, 0x0200) & 0x01) ? 1 : 0;
	sim_data.memory_width = (NV_RD32(par->PEXTDEV, 0x0000) & 0x10) ?
	    128 : 64;
	sim_data.mem_latency = (अक्षर)cfg1 & 0x0F;
	sim_data.mem_aligned = 1;
	sim_data.mem_page_miss =
	    (अक्षर)(((cfg1 >> 4) & 0x0F) + ((cfg1 >> 31) & 0x01));
	sim_data.gr_during_vid = 0;
	sim_data.pclk_khz = VClk;
	sim_data.mclk_khz = MClk;
	sim_data.nvclk_khz = NVClk;
	nv10CalcArbitration(&fअगरo_data, &sim_data);
	अगर (fअगरo_data.valid) अणु
		पूर्णांक b = fअगरo_data.graphics_burst_size >> 4;
		*burst = 0;
		जबतक (b >>= 1)
			(*burst)++;
		*lwm = fअगरo_data.graphics_lwm >> 3;
	पूर्ण
पूर्ण

अटल व्योम nv30UpdateArbitrationSettings (
    काष्ठा nvidia_par *par,
    अचिन्हित पूर्णांक      *burst,
    अचिन्हित पूर्णांक      *lwm
)
अणु
    अचिन्हित पूर्णांक MClk, NVClk;
    अचिन्हित पूर्णांक fअगरo_size, burst_size, graphics_lwm;

    fअगरo_size = 2048;
    burst_size = 512;
    graphics_lwm = fअगरo_size - burst_size;

    nvGetClocks(par, &MClk, &NVClk);

    *burst = 0;
    burst_size >>= 5;
    जबतक(burst_size >>= 1) (*burst)++;
    *lwm = graphics_lwm >> 3;
पूर्ण

अटल व्योम nForceUpdateArbitrationSettings(अचिन्हित VClk,
					    अचिन्हित pixelDepth,
					    अचिन्हित *burst,
					    अचिन्हित *lwm,
					    काष्ठा nvidia_par *par)
अणु
	nv10_fअगरo_info fअगरo_data;
	nv10_sim_state sim_data;
	अचिन्हित पूर्णांक M, N, P, pll, MClk, NVClk, memctrl;
	काष्ठा pci_dev *dev;
	पूर्णांक करोमुख्य = pci_करोमुख्य_nr(par->pci_dev->bus);

	अगर ((par->Chipset & 0x0FF0) == 0x01A0) अणु
		अचिन्हित पूर्णांक uMClkPostDiv;
		dev = pci_get_करोमुख्य_bus_and_slot(करोमुख्य, 0, 3);
		pci_पढ़ो_config_dword(dev, 0x6C, &uMClkPostDiv);
		uMClkPostDiv = (uMClkPostDiv >> 8) & 0xf;

		अगर (!uMClkPostDiv)
			uMClkPostDiv = 4;
		MClk = 400000 / uMClkPostDiv;
	पूर्ण अन्यथा अणु
		dev = pci_get_करोमुख्य_bus_and_slot(करोमुख्य, 0, 5);
		pci_पढ़ो_config_dword(dev, 0x4c, &MClk);
		MClk /= 1000;
	पूर्ण
	pci_dev_put(dev);
	pll = NV_RD32(par->PRAMDAC0, 0x0500);
	M = (pll >> 0) & 0xFF;
	N = (pll >> 8) & 0xFF;
	P = (pll >> 16) & 0x0F;
	NVClk = (N * par->CrystalFreqKHz / M) >> P;
	sim_data.pix_bpp = (अक्षर)pixelDepth;
	sim_data.enable_video = 0;
	sim_data.enable_mp = 0;
	dev = pci_get_करोमुख्य_bus_and_slot(करोमुख्य, 0, 1);
	pci_पढ़ो_config_dword(dev, 0x7C, &sim_data.memory_type);
	pci_dev_put(dev);
	sim_data.memory_type = (sim_data.memory_type >> 12) & 1;
	sim_data.memory_width = 64;

	dev = pci_get_करोमुख्य_bus_and_slot(करोमुख्य, 0, 3);
	pci_पढ़ो_config_dword(dev, 0, &memctrl);
	pci_dev_put(dev);
	memctrl >>= 16;

	अगर ((memctrl == 0x1A9) || (memctrl == 0x1AB) || (memctrl == 0x1ED)) अणु
		u32 dimm[3];

		dev = pci_get_करोमुख्य_bus_and_slot(करोमुख्य, 0, 2);
		pci_पढ़ो_config_dword(dev, 0x40, &dimm[0]);
		dimm[0] = (dimm[0] >> 8) & 0x4f;
		pci_पढ़ो_config_dword(dev, 0x44, &dimm[1]);
		dimm[1] = (dimm[1] >> 8) & 0x4f;
		pci_पढ़ो_config_dword(dev, 0x48, &dimm[2]);
		dimm[2] = (dimm[2] >> 8) & 0x4f;

		अगर ((dimm[0] + dimm[1]) != dimm[2]) अणु
			prपूर्णांकk("nvidiafb: your nForce DIMMs are not arranged "
			       "in optimal banks!\n");
		पूर्ण
		pci_dev_put(dev);
	पूर्ण

	sim_data.mem_latency = 3;
	sim_data.mem_aligned = 1;
	sim_data.mem_page_miss = 10;
	sim_data.gr_during_vid = 0;
	sim_data.pclk_khz = VClk;
	sim_data.mclk_khz = MClk;
	sim_data.nvclk_khz = NVClk;
	nv10CalcArbitration(&fअगरo_data, &sim_data);
	अगर (fअगरo_data.valid) अणु
		पूर्णांक b = fअगरo_data.graphics_burst_size >> 4;
		*burst = 0;
		जबतक (b >>= 1)
			(*burst)++;
		*lwm = fअगरo_data.graphics_lwm >> 3;
	पूर्ण
पूर्ण

/****************************************************************************\
*                                                                            *
*                          RIVA Mode State Routines                          *
*                                                                            *
\****************************************************************************/

/*
 * Calculate the Video Clock parameters क्रम the PLL.
 */
अटल व्योम CalcVClock(पूर्णांक घड़ीIn,
		       पूर्णांक *घड़ीOut, u32 * pllOut, काष्ठा nvidia_par *par)
अणु
	अचिन्हित lowM, highM;
	अचिन्हित DeltaNew, DeltaOld;
	अचिन्हित VClk, Freq;
	अचिन्हित M, N, P;

	DeltaOld = 0xFFFFFFFF;

	VClk = (अचिन्हित)घड़ीIn;

	अगर (par->CrystalFreqKHz == 13500) अणु
		lowM = 7;
		highM = 13;
	पूर्ण अन्यथा अणु
		lowM = 8;
		highM = 14;
	पूर्ण

	क्रम (P = 0; P <= 4; P++) अणु
		Freq = VClk << P;
		अगर ((Freq >= 128000) && (Freq <= 350000)) अणु
			क्रम (M = lowM; M <= highM; M++) अणु
				N = ((VClk << P) * M) / par->CrystalFreqKHz;
				अगर (N <= 255) अणु
					Freq =
					    ((par->CrystalFreqKHz * N) /
					     M) >> P;
					अगर (Freq > VClk)
						DeltaNew = Freq - VClk;
					अन्यथा
						DeltaNew = VClk - Freq;
					अगर (DeltaNew < DeltaOld) अणु
						*pllOut =
						    (P << 16) | (N << 8) | M;
						*घड़ीOut = Freq;
						DeltaOld = DeltaNew;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम CalcVClock2Stage(पूर्णांक घड़ीIn,
			     पूर्णांक *घड़ीOut,
			     u32 * pllOut,
			     u32 * pllBOut, काष्ठा nvidia_par *par)
अणु
	अचिन्हित DeltaNew, DeltaOld;
	अचिन्हित VClk, Freq;
	अचिन्हित M, N, P;

	DeltaOld = 0xFFFFFFFF;

	*pllBOut = 0x80000401;	/* fixed at x4 क्रम now */

	VClk = (अचिन्हित)घड़ीIn;

	क्रम (P = 0; P <= 6; P++) अणु
		Freq = VClk << P;
		अगर ((Freq >= 400000) && (Freq <= 1000000)) अणु
			क्रम (M = 1; M <= 13; M++) अणु
				N = ((VClk << P) * M) /
				    (par->CrystalFreqKHz << 2);
				अगर ((N >= 5) && (N <= 255)) अणु
					Freq =
					    (((par->CrystalFreqKHz << 2) * N) /
					     M) >> P;
					अगर (Freq > VClk)
						DeltaNew = Freq - VClk;
					अन्यथा
						DeltaNew = VClk - Freq;
					अगर (DeltaNew < DeltaOld) अणु
						*pllOut =
						    (P << 16) | (N << 8) | M;
						*घड़ीOut = Freq;
						DeltaOld = DeltaNew;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Calculate extended mode parameters (SVGA) and save in a
 * mode state काष्ठाure.
 */
व्योम NVCalcStateExt(काष्ठा nvidia_par *par,
		    RIVA_HW_STATE * state,
		    पूर्णांक bpp,
		    पूर्णांक width,
		    पूर्णांक hDisplaySize, पूर्णांक height, पूर्णांक करोtClock, पूर्णांक flags)
अणु
	पूर्णांक pixelDepth, VClk = 0;
	/*
	 * Save mode parameters.
	 */
	state->bpp = bpp;	/* this is not bitsPerPixel, it's 8,15,16,32 */
	state->width = width;
	state->height = height;
	/*
	 * Extended RIVA रेजिस्टरs.
	 */
	pixelDepth = (bpp + 1) / 8;
	अगर (par->twoStagePLL)
		CalcVClock2Stage(करोtClock, &VClk, &state->pll, &state->pllB,
				 par);
	अन्यथा
		CalcVClock(करोtClock, &VClk, &state->pll, par);

	चयन (par->Architecture) अणु
	हाल NV_ARCH_04:
		nv4UpdateArbitrationSettings(VClk,
					     pixelDepth * 8,
					     &(state->arbitration0),
					     &(state->arbitration1), par);
		state->cursor0 = 0x00;
		state->cursor1 = 0xbC;
		अगर (flags & FB_VMODE_DOUBLE)
			state->cursor1 |= 2;
		state->cursor2 = 0x00000000;
		state->pllsel = 0x10000700;
		state->config = 0x00001114;
		state->general = bpp == 16 ? 0x00101100 : 0x00100100;
		state->repaपूर्णांक1 = hDisplaySize < 1280 ? 0x04 : 0x00;
		अवरोध;
	हाल NV_ARCH_40:
		अगर (!par->FlatPanel)
			state->control = NV_RD32(par->PRAMDAC0, 0x0580) &
				0xeffffeff;
		fallthrough;
	हाल NV_ARCH_10:
	हाल NV_ARCH_20:
	हाल NV_ARCH_30:
	शेष:
		अगर ((par->Chipset & 0xfff0) == 0x0240 ||
		    (par->Chipset & 0xfff0) == 0x03d0) अणु
			state->arbitration0 = 256;
			state->arbitration1 = 0x0480;
		पूर्ण अन्यथा अगर (((par->Chipset & 0xffff) == 0x01A0) ||
		    ((par->Chipset & 0xffff) == 0x01f0)) अणु
			nForceUpdateArbitrationSettings(VClk,
							pixelDepth * 8,
							&(state->arbitration0),
							&(state->arbitration1),
							par);
		पूर्ण अन्यथा अगर (par->Architecture < NV_ARCH_30) अणु
			nv10UpdateArbitrationSettings(VClk,
						      pixelDepth * 8,
						      &(state->arbitration0),
						      &(state->arbitration1),
						      par);
		पूर्ण अन्यथा अणु
			nv30UpdateArbitrationSettings(par,
						      &(state->arbitration0),
						      &(state->arbitration1));
		पूर्ण

		state->cursor0 = 0x80 | (par->CursorStart >> 17);
		state->cursor1 = (par->CursorStart >> 11) << 2;
		state->cursor2 = par->CursorStart >> 24;
		अगर (flags & FB_VMODE_DOUBLE)
			state->cursor1 |= 2;
		state->pllsel = 0x10000700;
		state->config = NV_RD32(par->PFB, 0x00000200);
		state->general = bpp == 16 ? 0x00101100 : 0x00100100;
		state->repaपूर्णांक1 = hDisplaySize < 1280 ? 0x04 : 0x00;
		अवरोध;
	पूर्ण

	अगर (bpp != 8)		/* DirectColor */
		state->general |= 0x00000030;

	state->repaपूर्णांक0 = (((width / 8) * pixelDepth) & 0x700) >> 3;
	state->pixel = (pixelDepth > 2) ? 3 : pixelDepth;
पूर्ण

व्योम NVLoadStateExt(काष्ठा nvidia_par *par, RIVA_HW_STATE * state)
अणु
	पूर्णांक i, j;

	NV_WR32(par->PMC, 0x0140, 0x00000000);
	NV_WR32(par->PMC, 0x0200, 0xFFFF00FF);
	NV_WR32(par->PMC, 0x0200, 0xFFFFFFFF);

	NV_WR32(par->PTIMER, 0x0200 * 4, 0x00000008);
	NV_WR32(par->PTIMER, 0x0210 * 4, 0x00000003);
	NV_WR32(par->PTIMER, 0x0140 * 4, 0x00000000);
	NV_WR32(par->PTIMER, 0x0100 * 4, 0xFFFFFFFF);

	अगर (par->Architecture == NV_ARCH_04) अणु
		अगर (state)
			NV_WR32(par->PFB, 0x0200, state->config);
	पूर्ण अन्यथा अगर ((par->Architecture < NV_ARCH_40) ||
		   (par->Chipset & 0xfff0) == 0x0040) अणु
		क्रम (i = 0; i < 8; i++) अणु
			NV_WR32(par->PFB, 0x0240 + (i * 0x10), 0);
			NV_WR32(par->PFB, 0x0244 + (i * 0x10),
				par->FbMapSize - 1);
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक regions = 12;

		अगर (((par->Chipset & 0xfff0) == 0x0090) ||
		    ((par->Chipset & 0xfff0) == 0x01D0) ||
		    ((par->Chipset & 0xfff0) == 0x0290) ||
		    ((par->Chipset & 0xfff0) == 0x0390) ||
		    ((par->Chipset & 0xfff0) == 0x03D0))
			regions = 15;
		क्रम(i = 0; i < regions; i++) अणु
			NV_WR32(par->PFB, 0x0600 + (i * 0x10), 0);
			NV_WR32(par->PFB, 0x0604 + (i * 0x10),
				par->FbMapSize - 1);
		पूर्ण
	पूर्ण

	अगर (par->Architecture >= NV_ARCH_40) अणु
		NV_WR32(par->PRAMIN, 0x0000 * 4, 0x80000010);
		NV_WR32(par->PRAMIN, 0x0001 * 4, 0x00101202);
		NV_WR32(par->PRAMIN, 0x0002 * 4, 0x80000011);
		NV_WR32(par->PRAMIN, 0x0003 * 4, 0x00101204);
		NV_WR32(par->PRAMIN, 0x0004 * 4, 0x80000012);
		NV_WR32(par->PRAMIN, 0x0005 * 4, 0x00101206);
		NV_WR32(par->PRAMIN, 0x0006 * 4, 0x80000013);
		NV_WR32(par->PRAMIN, 0x0007 * 4, 0x00101208);
		NV_WR32(par->PRAMIN, 0x0008 * 4, 0x80000014);
		NV_WR32(par->PRAMIN, 0x0009 * 4, 0x0010120A);
		NV_WR32(par->PRAMIN, 0x000A * 4, 0x80000015);
		NV_WR32(par->PRAMIN, 0x000B * 4, 0x0010120C);
		NV_WR32(par->PRAMIN, 0x000C * 4, 0x80000016);
		NV_WR32(par->PRAMIN, 0x000D * 4, 0x0010120E);
		NV_WR32(par->PRAMIN, 0x000E * 4, 0x80000017);
		NV_WR32(par->PRAMIN, 0x000F * 4, 0x00101210);
		NV_WR32(par->PRAMIN, 0x0800 * 4, 0x00003000);
		NV_WR32(par->PRAMIN, 0x0801 * 4, par->FbMapSize - 1);
		NV_WR32(par->PRAMIN, 0x0802 * 4, 0x00000002);
		NV_WR32(par->PRAMIN, 0x0808 * 4, 0x02080062);
		NV_WR32(par->PRAMIN, 0x0809 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x080A * 4, 0x00001200);
		NV_WR32(par->PRAMIN, 0x080B * 4, 0x00001200);
		NV_WR32(par->PRAMIN, 0x080C * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x080D * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0810 * 4, 0x02080043);
		NV_WR32(par->PRAMIN, 0x0811 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0812 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0813 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0814 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0815 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0818 * 4, 0x02080044);
		NV_WR32(par->PRAMIN, 0x0819 * 4, 0x02000000);
		NV_WR32(par->PRAMIN, 0x081A * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x081B * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x081C * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x081D * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0820 * 4, 0x02080019);
		NV_WR32(par->PRAMIN, 0x0821 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0822 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0823 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0824 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0825 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0828 * 4, 0x020A005C);
		NV_WR32(par->PRAMIN, 0x0829 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x082A * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x082B * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x082C * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x082D * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0830 * 4, 0x0208009F);
		NV_WR32(par->PRAMIN, 0x0831 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0832 * 4, 0x00001200);
		NV_WR32(par->PRAMIN, 0x0833 * 4, 0x00001200);
		NV_WR32(par->PRAMIN, 0x0834 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0835 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0838 * 4, 0x0208004A);
		NV_WR32(par->PRAMIN, 0x0839 * 4, 0x02000000);
		NV_WR32(par->PRAMIN, 0x083A * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x083B * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x083C * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x083D * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0840 * 4, 0x02080077);
		NV_WR32(par->PRAMIN, 0x0841 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0842 * 4, 0x00001200);
		NV_WR32(par->PRAMIN, 0x0843 * 4, 0x00001200);
		NV_WR32(par->PRAMIN, 0x0844 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0845 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x084C * 4, 0x00003002);
		NV_WR32(par->PRAMIN, 0x084D * 4, 0x00007FFF);
		NV_WR32(par->PRAMIN, 0x084E * 4,
			par->FbUsableSize | 0x00000002);

#अगर_घोषित __BIG_ENDIAN
		NV_WR32(par->PRAMIN, 0x080A * 4,
			NV_RD32(par->PRAMIN, 0x080A * 4) | 0x01000000);
		NV_WR32(par->PRAMIN, 0x0812 * 4,
			NV_RD32(par->PRAMIN, 0x0812 * 4) | 0x01000000);
		NV_WR32(par->PRAMIN, 0x081A * 4,
			NV_RD32(par->PRAMIN, 0x081A * 4) | 0x01000000);
		NV_WR32(par->PRAMIN, 0x0822 * 4,
			NV_RD32(par->PRAMIN, 0x0822 * 4) | 0x01000000);
		NV_WR32(par->PRAMIN, 0x082A * 4,
			NV_RD32(par->PRAMIN, 0x082A * 4) | 0x01000000);
		NV_WR32(par->PRAMIN, 0x0832 * 4,
			NV_RD32(par->PRAMIN, 0x0832 * 4) | 0x01000000);
		NV_WR32(par->PRAMIN, 0x083A * 4,
			NV_RD32(par->PRAMIN, 0x083A * 4) | 0x01000000);
		NV_WR32(par->PRAMIN, 0x0842 * 4,
			NV_RD32(par->PRAMIN, 0x0842 * 4) | 0x01000000);
		NV_WR32(par->PRAMIN, 0x0819 * 4, 0x01000000);
		NV_WR32(par->PRAMIN, 0x0839 * 4, 0x01000000);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		NV_WR32(par->PRAMIN, 0x0000 * 4, 0x80000010);
		NV_WR32(par->PRAMIN, 0x0001 * 4, 0x80011201);
		NV_WR32(par->PRAMIN, 0x0002 * 4, 0x80000011);
		NV_WR32(par->PRAMIN, 0x0003 * 4, 0x80011202);
		NV_WR32(par->PRAMIN, 0x0004 * 4, 0x80000012);
		NV_WR32(par->PRAMIN, 0x0005 * 4, 0x80011203);
		NV_WR32(par->PRAMIN, 0x0006 * 4, 0x80000013);
		NV_WR32(par->PRAMIN, 0x0007 * 4, 0x80011204);
		NV_WR32(par->PRAMIN, 0x0008 * 4, 0x80000014);
		NV_WR32(par->PRAMIN, 0x0009 * 4, 0x80011205);
		NV_WR32(par->PRAMIN, 0x000A * 4, 0x80000015);
		NV_WR32(par->PRAMIN, 0x000B * 4, 0x80011206);
		NV_WR32(par->PRAMIN, 0x000C * 4, 0x80000016);
		NV_WR32(par->PRAMIN, 0x000D * 4, 0x80011207);
		NV_WR32(par->PRAMIN, 0x000E * 4, 0x80000017);
		NV_WR32(par->PRAMIN, 0x000F * 4, 0x80011208);
		NV_WR32(par->PRAMIN, 0x0800 * 4, 0x00003000);
		NV_WR32(par->PRAMIN, 0x0801 * 4, par->FbMapSize - 1);
		NV_WR32(par->PRAMIN, 0x0802 * 4, 0x00000002);
		NV_WR32(par->PRAMIN, 0x0803 * 4, 0x00000002);
		अगर (par->Architecture >= NV_ARCH_10)
			NV_WR32(par->PRAMIN, 0x0804 * 4, 0x01008062);
		अन्यथा
			NV_WR32(par->PRAMIN, 0x0804 * 4, 0x01008042);
		NV_WR32(par->PRAMIN, 0x0805 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0806 * 4, 0x12001200);
		NV_WR32(par->PRAMIN, 0x0807 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0808 * 4, 0x01008043);
		NV_WR32(par->PRAMIN, 0x0809 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x080A * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x080B * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x080C * 4, 0x01008044);
		NV_WR32(par->PRAMIN, 0x080D * 4, 0x00000002);
		NV_WR32(par->PRAMIN, 0x080E * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x080F * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0810 * 4, 0x01008019);
		NV_WR32(par->PRAMIN, 0x0811 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0812 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0813 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0814 * 4, 0x0100A05C);
		NV_WR32(par->PRAMIN, 0x0815 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0816 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0817 * 4, 0x00000000);
		अगर (par->WaitVSyncPossible)
			NV_WR32(par->PRAMIN, 0x0818 * 4, 0x0100809F);
		अन्यथा
			NV_WR32(par->PRAMIN, 0x0818 * 4, 0x0100805F);
		NV_WR32(par->PRAMIN, 0x0819 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x081A * 4, 0x12001200);
		NV_WR32(par->PRAMIN, 0x081B * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x081C * 4, 0x0100804A);
		NV_WR32(par->PRAMIN, 0x081D * 4, 0x00000002);
		NV_WR32(par->PRAMIN, 0x081E * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x081F * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0820 * 4, 0x01018077);
		NV_WR32(par->PRAMIN, 0x0821 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0822 * 4, 0x12001200);
		NV_WR32(par->PRAMIN, 0x0823 * 4, 0x00000000);
		NV_WR32(par->PRAMIN, 0x0824 * 4, 0x00003002);
		NV_WR32(par->PRAMIN, 0x0825 * 4, 0x00007FFF);
		NV_WR32(par->PRAMIN, 0x0826 * 4,
			par->FbUsableSize | 0x00000002);
		NV_WR32(par->PRAMIN, 0x0827 * 4, 0x00000002);
#अगर_घोषित __BIG_ENDIAN
		NV_WR32(par->PRAMIN, 0x0804 * 4,
			NV_RD32(par->PRAMIN, 0x0804 * 4) | 0x00080000);
		NV_WR32(par->PRAMIN, 0x0808 * 4,
			NV_RD32(par->PRAMIN, 0x0808 * 4) | 0x00080000);
		NV_WR32(par->PRAMIN, 0x080C * 4,
			NV_RD32(par->PRAMIN, 0x080C * 4) | 0x00080000);
		NV_WR32(par->PRAMIN, 0x0810 * 4,
			NV_RD32(par->PRAMIN, 0x0810 * 4) | 0x00080000);
		NV_WR32(par->PRAMIN, 0x0814 * 4,
			NV_RD32(par->PRAMIN, 0x0814 * 4) | 0x00080000);
		NV_WR32(par->PRAMIN, 0x0818 * 4,
			NV_RD32(par->PRAMIN, 0x0818 * 4) | 0x00080000);
		NV_WR32(par->PRAMIN, 0x081C * 4,
			NV_RD32(par->PRAMIN, 0x081C * 4) | 0x00080000);
		NV_WR32(par->PRAMIN, 0x0820 * 4,
			NV_RD32(par->PRAMIN, 0x0820 * 4) | 0x00080000);
		NV_WR32(par->PRAMIN, 0x080D * 4, 0x00000001);
		NV_WR32(par->PRAMIN, 0x081D * 4, 0x00000001);
#पूर्ण_अगर
	पूर्ण
	अगर (par->Architecture < NV_ARCH_10) अणु
		अगर ((par->Chipset & 0x0fff) == 0x0020) अणु
			NV_WR32(par->PRAMIN, 0x0824 * 4,
				NV_RD32(par->PRAMIN, 0x0824 * 4) | 0x00020000);
			NV_WR32(par->PRAMIN, 0x0826 * 4,
				NV_RD32(par->PRAMIN,
					0x0826 * 4) + par->FbAddress);
		पूर्ण
		NV_WR32(par->PGRAPH, 0x0080, 0x000001FF);
		NV_WR32(par->PGRAPH, 0x0080, 0x1230C000);
		NV_WR32(par->PGRAPH, 0x0084, 0x72111101);
		NV_WR32(par->PGRAPH, 0x0088, 0x11D5F071);
		NV_WR32(par->PGRAPH, 0x008C, 0x0004FF31);
		NV_WR32(par->PGRAPH, 0x008C, 0x4004FF31);
		NV_WR32(par->PGRAPH, 0x0140, 0x00000000);
		NV_WR32(par->PGRAPH, 0x0100, 0xFFFFFFFF);
		NV_WR32(par->PGRAPH, 0x0170, 0x10010100);
		NV_WR32(par->PGRAPH, 0x0710, 0xFFFFFFFF);
		NV_WR32(par->PGRAPH, 0x0720, 0x00000001);
		NV_WR32(par->PGRAPH, 0x0810, 0x00000000);
		NV_WR32(par->PGRAPH, 0x0608, 0xFFFFFFFF);
	पूर्ण अन्यथा अणु
		NV_WR32(par->PGRAPH, 0x0080, 0xFFFFFFFF);
		NV_WR32(par->PGRAPH, 0x0080, 0x00000000);

		NV_WR32(par->PGRAPH, 0x0140, 0x00000000);
		NV_WR32(par->PGRAPH, 0x0100, 0xFFFFFFFF);
		NV_WR32(par->PGRAPH, 0x0144, 0x10010100);
		NV_WR32(par->PGRAPH, 0x0714, 0xFFFFFFFF);
		NV_WR32(par->PGRAPH, 0x0720, 0x00000001);
		NV_WR32(par->PGRAPH, 0x0710,
			NV_RD32(par->PGRAPH, 0x0710) & 0x0007ff00);
		NV_WR32(par->PGRAPH, 0x0710,
			NV_RD32(par->PGRAPH, 0x0710) | 0x00020100);

		अगर (par->Architecture == NV_ARCH_10) अणु
			NV_WR32(par->PGRAPH, 0x0084, 0x00118700);
			NV_WR32(par->PGRAPH, 0x0088, 0x24E00810);
			NV_WR32(par->PGRAPH, 0x008C, 0x55DE0030);

			क्रम (i = 0; i < 32; i++)
				NV_WR32(&par->PGRAPH[(0x0B00 / 4) + i], 0,
					NV_RD32(&par->PFB[(0x0240 / 4) + i],
						0));

			NV_WR32(par->PGRAPH, 0x640, 0);
			NV_WR32(par->PGRAPH, 0x644, 0);
			NV_WR32(par->PGRAPH, 0x684, par->FbMapSize - 1);
			NV_WR32(par->PGRAPH, 0x688, par->FbMapSize - 1);

			NV_WR32(par->PGRAPH, 0x0810, 0x00000000);
			NV_WR32(par->PGRAPH, 0x0608, 0xFFFFFFFF);
		पूर्ण अन्यथा अणु
			अगर (par->Architecture >= NV_ARCH_40) अणु
				NV_WR32(par->PGRAPH, 0x0084, 0x401287c0);
				NV_WR32(par->PGRAPH, 0x008C, 0x60de8051);
				NV_WR32(par->PGRAPH, 0x0090, 0x00008000);
				NV_WR32(par->PGRAPH, 0x0610, 0x00be3c5f);
				NV_WR32(par->PGRAPH, 0x0bc4,
					NV_RD32(par->PGRAPH, 0x0bc4) |
					0x00008000);

				j = NV_RD32(par->REGS, 0x1540) & 0xff;

				अगर (j) अणु
					क्रम (i = 0; !(j & 1); j >>= 1, i++);
					NV_WR32(par->PGRAPH, 0x5000, i);
				पूर्ण

				अगर ((par->Chipset & 0xfff0) == 0x0040) अणु
					NV_WR32(par->PGRAPH, 0x09b0,
						0x83280fff);
					NV_WR32(par->PGRAPH, 0x09b4,
						0x000000a0);
				पूर्ण अन्यथा अणु
					NV_WR32(par->PGRAPH, 0x0820,
						0x83280eff);
					NV_WR32(par->PGRAPH, 0x0824,
						0x000000a0);
				पूर्ण

				चयन (par->Chipset & 0xfff0) अणु
				हाल 0x0040:
				हाल 0x0210:
					NV_WR32(par->PGRAPH, 0x09b8,
						0x0078e366);
					NV_WR32(par->PGRAPH, 0x09bc,
						0x0000014c);
					NV_WR32(par->PFB, 0x033C,
						NV_RD32(par->PFB, 0x33C) &
						0xffff7fff);
					अवरोध;
				हाल 0x00C0:
				हाल 0x0120:
					NV_WR32(par->PGRAPH, 0x0828,
						0x007596ff);
					NV_WR32(par->PGRAPH, 0x082C,
						0x00000108);
					अवरोध;
				हाल 0x0160:
				हाल 0x01D0:
				हाल 0x0240:
				हाल 0x03D0:
					NV_WR32(par->PMC, 0x1700,
						NV_RD32(par->PFB, 0x020C));
					NV_WR32(par->PMC, 0x1704, 0);
					NV_WR32(par->PMC, 0x1708, 0);
					NV_WR32(par->PMC, 0x170C,
						NV_RD32(par->PFB, 0x020C));
					NV_WR32(par->PGRAPH, 0x0860, 0);
					NV_WR32(par->PGRAPH, 0x0864, 0);
					NV_WR32(par->PRAMDAC, 0x0608,
						NV_RD32(par->PRAMDAC,
							0x0608) | 0x00100000);
					अवरोध;
				हाल 0x0140:
					NV_WR32(par->PGRAPH, 0x0828,
						0x0072cb77);
					NV_WR32(par->PGRAPH, 0x082C,
						0x00000108);
					अवरोध;
				हाल 0x0220:
					NV_WR32(par->PGRAPH, 0x0860, 0);
					NV_WR32(par->PGRAPH, 0x0864, 0);
					NV_WR32(par->PRAMDAC, 0x0608,
						NV_RD32(par->PRAMDAC, 0x0608) |
						0x00100000);
					अवरोध;
				हाल 0x0090:
				हाल 0x0290:
				हाल 0x0390:
					NV_WR32(par->PRAMDAC, 0x0608,
						NV_RD32(par->PRAMDAC, 0x0608) |
						0x00100000);
					NV_WR32(par->PGRAPH, 0x0828,
						0x07830610);
					NV_WR32(par->PGRAPH, 0x082C,
						0x0000016A);
					अवरोध;
				शेष:
					अवरोध;
				पूर्ण

				NV_WR32(par->PGRAPH, 0x0b38, 0x2ffff800);
				NV_WR32(par->PGRAPH, 0x0b3c, 0x00006000);
				NV_WR32(par->PGRAPH, 0x032C, 0x01000000);
				NV_WR32(par->PGRAPH, 0x0220, 0x00001200);
			पूर्ण अन्यथा अगर (par->Architecture == NV_ARCH_30) अणु
				NV_WR32(par->PGRAPH, 0x0084, 0x40108700);
				NV_WR32(par->PGRAPH, 0x0890, 0x00140000);
				NV_WR32(par->PGRAPH, 0x008C, 0xf00e0431);
				NV_WR32(par->PGRAPH, 0x0090, 0x00008000);
				NV_WR32(par->PGRAPH, 0x0610, 0xf04b1f36);
				NV_WR32(par->PGRAPH, 0x0B80, 0x1002d888);
				NV_WR32(par->PGRAPH, 0x0B88, 0x62ff007f);
			पूर्ण अन्यथा अणु
				NV_WR32(par->PGRAPH, 0x0084, 0x00118700);
				NV_WR32(par->PGRAPH, 0x008C, 0xF20E0431);
				NV_WR32(par->PGRAPH, 0x0090, 0x00000000);
				NV_WR32(par->PGRAPH, 0x009C, 0x00000040);

				अगर ((par->Chipset & 0x0ff0) >= 0x0250) अणु
					NV_WR32(par->PGRAPH, 0x0890,
						0x00080000);
					NV_WR32(par->PGRAPH, 0x0610,
						0x304B1FB6);
					NV_WR32(par->PGRAPH, 0x0B80,
						0x18B82880);
					NV_WR32(par->PGRAPH, 0x0B84,
						0x44000000);
					NV_WR32(par->PGRAPH, 0x0098,
						0x40000080);
					NV_WR32(par->PGRAPH, 0x0B88,
						0x000000ff);
				पूर्ण अन्यथा अणु
					NV_WR32(par->PGRAPH, 0x0880,
						0x00080000);
					NV_WR32(par->PGRAPH, 0x0094,
						0x00000005);
					NV_WR32(par->PGRAPH, 0x0B80,
						0x45CAA208);
					NV_WR32(par->PGRAPH, 0x0B84,
						0x24000000);
					NV_WR32(par->PGRAPH, 0x0098,
						0x00000040);
					NV_WR32(par->PGRAPH, 0x0750,
						0x00E00038);
					NV_WR32(par->PGRAPH, 0x0754,
						0x00000030);
					NV_WR32(par->PGRAPH, 0x0750,
						0x00E10038);
					NV_WR32(par->PGRAPH, 0x0754,
						0x00000030);
				पूर्ण
			पूर्ण

			अगर ((par->Architecture < NV_ARCH_40) ||
			    ((par->Chipset & 0xfff0) == 0x0040)) अणु
				क्रम (i = 0; i < 32; i++) अणु
					NV_WR32(par->PGRAPH, 0x0900 + i*4,
						NV_RD32(par->PFB, 0x0240 +i*4));
					NV_WR32(par->PGRAPH, 0x6900 + i*4,
						NV_RD32(par->PFB, 0x0240 +i*4));
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (((par->Chipset & 0xfff0) == 0x0090) ||
				    ((par->Chipset & 0xfff0) == 0x01D0) ||
				    ((par->Chipset & 0xfff0) == 0x0290) ||
				    ((par->Chipset & 0xfff0) == 0x0390) ||
				    ((par->Chipset & 0xfff0) == 0x03D0)) अणु
					क्रम (i = 0; i < 60; i++) अणु
						NV_WR32(par->PGRAPH,
							0x0D00 + i*4,
							NV_RD32(par->PFB,
								0x0600 + i*4));
						NV_WR32(par->PGRAPH,
							0x6900 + i*4,
							NV_RD32(par->PFB,
								0x0600 + i*4));
					पूर्ण
				पूर्ण अन्यथा अणु
					क्रम (i = 0; i < 48; i++) अणु
						NV_WR32(par->PGRAPH,
							0x0900 + i*4,
							NV_RD32(par->PFB,
								0x0600 + i*4));
						अगर(((par->Chipset & 0xfff0)
						    != 0x0160) &&
						   ((par->Chipset & 0xfff0)
						    != 0x0220) &&
						   ((par->Chipset & 0xfff0)
						    != 0x240))
							NV_WR32(par->PGRAPH,
								0x6900 + i*4,
								NV_RD32(par->PFB,
									0x0600 + i*4));
					पूर्ण
				पूर्ण
			पूर्ण

			अगर (par->Architecture >= NV_ARCH_40) अणु
				अगर ((par->Chipset & 0xfff0) == 0x0040) अणु
					NV_WR32(par->PGRAPH, 0x09A4,
						NV_RD32(par->PFB, 0x0200));
					NV_WR32(par->PGRAPH, 0x09A8,
						NV_RD32(par->PFB, 0x0204));
					NV_WR32(par->PGRAPH, 0x69A4,
						NV_RD32(par->PFB, 0x0200));
					NV_WR32(par->PGRAPH, 0x69A8,
						NV_RD32(par->PFB, 0x0204));

					NV_WR32(par->PGRAPH, 0x0820, 0);
					NV_WR32(par->PGRAPH, 0x0824, 0);
					NV_WR32(par->PGRAPH, 0x0864,
						par->FbMapSize - 1);
					NV_WR32(par->PGRAPH, 0x0868,
						par->FbMapSize - 1);
				पूर्ण अन्यथा अणु
					अगर ((par->Chipset & 0xfff0) == 0x0090 ||
					    (par->Chipset & 0xfff0) == 0x01D0 ||
					    (par->Chipset & 0xfff0) == 0x0290 ||
					    (par->Chipset & 0xfff0) == 0x0390) अणु
						NV_WR32(par->PGRAPH, 0x0DF0,
							NV_RD32(par->PFB, 0x0200));
						NV_WR32(par->PGRAPH, 0x0DF4,
							NV_RD32(par->PFB, 0x0204));
					पूर्ण अन्यथा अणु
						NV_WR32(par->PGRAPH, 0x09F0,
							NV_RD32(par->PFB, 0x0200));
						NV_WR32(par->PGRAPH, 0x09F4,
							NV_RD32(par->PFB, 0x0204));
					पूर्ण
					NV_WR32(par->PGRAPH, 0x69F0,
						NV_RD32(par->PFB, 0x0200));
					NV_WR32(par->PGRAPH, 0x69F4,
						NV_RD32(par->PFB, 0x0204));

					NV_WR32(par->PGRAPH, 0x0840, 0);
					NV_WR32(par->PGRAPH, 0x0844, 0);
					NV_WR32(par->PGRAPH, 0x08a0,
						par->FbMapSize - 1);
					NV_WR32(par->PGRAPH, 0x08a4,
						par->FbMapSize - 1);
				पूर्ण
			पूर्ण अन्यथा अणु
				NV_WR32(par->PGRAPH, 0x09A4,
					NV_RD32(par->PFB, 0x0200));
				NV_WR32(par->PGRAPH, 0x09A8,
					NV_RD32(par->PFB, 0x0204));
				NV_WR32(par->PGRAPH, 0x0750, 0x00EA0000);
				NV_WR32(par->PGRAPH, 0x0754,
					NV_RD32(par->PFB, 0x0200));
				NV_WR32(par->PGRAPH, 0x0750, 0x00EA0004);
				NV_WR32(par->PGRAPH, 0x0754,
					NV_RD32(par->PFB, 0x0204));

				NV_WR32(par->PGRAPH, 0x0820, 0);
				NV_WR32(par->PGRAPH, 0x0824, 0);
				NV_WR32(par->PGRAPH, 0x0864,
					par->FbMapSize - 1);
				NV_WR32(par->PGRAPH, 0x0868,
					par->FbMapSize - 1);
			पूर्ण
			NV_WR32(par->PGRAPH, 0x0B20, 0x00000000);
			NV_WR32(par->PGRAPH, 0x0B04, 0xFFFFFFFF);
		पूर्ण
	पूर्ण
	NV_WR32(par->PGRAPH, 0x053C, 0);
	NV_WR32(par->PGRAPH, 0x0540, 0);
	NV_WR32(par->PGRAPH, 0x0544, 0x00007FFF);
	NV_WR32(par->PGRAPH, 0x0548, 0x00007FFF);

	NV_WR32(par->PFIFO, 0x0140 * 4, 0x00000000);
	NV_WR32(par->PFIFO, 0x0141 * 4, 0x00000001);
	NV_WR32(par->PFIFO, 0x0480 * 4, 0x00000000);
	NV_WR32(par->PFIFO, 0x0494 * 4, 0x00000000);
	अगर (par->Architecture >= NV_ARCH_40)
		NV_WR32(par->PFIFO, 0x0481 * 4, 0x00010000);
	अन्यथा
		NV_WR32(par->PFIFO, 0x0481 * 4, 0x00000100);
	NV_WR32(par->PFIFO, 0x0490 * 4, 0x00000000);
	NV_WR32(par->PFIFO, 0x0491 * 4, 0x00000000);
	अगर (par->Architecture >= NV_ARCH_40)
		NV_WR32(par->PFIFO, 0x048B * 4, 0x00001213);
	अन्यथा
		NV_WR32(par->PFIFO, 0x048B * 4, 0x00001209);
	NV_WR32(par->PFIFO, 0x0400 * 4, 0x00000000);
	NV_WR32(par->PFIFO, 0x0414 * 4, 0x00000000);
	NV_WR32(par->PFIFO, 0x0084 * 4, 0x03000100);
	NV_WR32(par->PFIFO, 0x0085 * 4, 0x00000110);
	NV_WR32(par->PFIFO, 0x0086 * 4, 0x00000112);
	NV_WR32(par->PFIFO, 0x0143 * 4, 0x0000FFFF);
	NV_WR32(par->PFIFO, 0x0496 * 4, 0x0000FFFF);
	NV_WR32(par->PFIFO, 0x0050 * 4, 0x00000000);
	NV_WR32(par->PFIFO, 0x0040 * 4, 0xFFFFFFFF);
	NV_WR32(par->PFIFO, 0x0415 * 4, 0x00000001);
	NV_WR32(par->PFIFO, 0x048C * 4, 0x00000000);
	NV_WR32(par->PFIFO, 0x04A0 * 4, 0x00000000);
#अगर_घोषित __BIG_ENDIAN
	NV_WR32(par->PFIFO, 0x0489 * 4, 0x800F0078);
#अन्यथा
	NV_WR32(par->PFIFO, 0x0489 * 4, 0x000F0078);
#पूर्ण_अगर
	NV_WR32(par->PFIFO, 0x0488 * 4, 0x00000001);
	NV_WR32(par->PFIFO, 0x0480 * 4, 0x00000001);
	NV_WR32(par->PFIFO, 0x0494 * 4, 0x00000001);
	NV_WR32(par->PFIFO, 0x0495 * 4, 0x00000001);
	NV_WR32(par->PFIFO, 0x0140 * 4, 0x00000001);

    अगर (!state) अणु
	    par->CurrentState = शून्य;
	    वापस;
    पूर्ण

	अगर (par->Architecture >= NV_ARCH_10) अणु
		अगर (par->twoHeads) अणु
			NV_WR32(par->PCRTC0, 0x0860, state->head);
			NV_WR32(par->PCRTC0, 0x2860, state->head2);
		पूर्ण
		NV_WR32(par->PRAMDAC, 0x0404, NV_RD32(par->PRAMDAC, 0x0404) |
			(1 << 25));

		NV_WR32(par->PMC, 0x8704, 1);
		NV_WR32(par->PMC, 0x8140, 0);
		NV_WR32(par->PMC, 0x8920, 0);
		NV_WR32(par->PMC, 0x8924, 0);
		NV_WR32(par->PMC, 0x8908, par->FbMapSize - 1);
		NV_WR32(par->PMC, 0x890C, par->FbMapSize - 1);
		NV_WR32(par->PMC, 0x1588, 0);

		NV_WR32(par->PCRTC, 0x0810, state->cursorConfig);
		NV_WR32(par->PCRTC, 0x0830, state->displayV - 3);
		NV_WR32(par->PCRTC, 0x0834, state->displayV - 1);

		अगर (par->FlatPanel) अणु
			अगर ((par->Chipset & 0x0ff0) == 0x0110) अणु
				NV_WR32(par->PRAMDAC, 0x0528, state->dither);
			पूर्ण अन्यथा अगर (par->twoHeads) अणु
				NV_WR32(par->PRAMDAC, 0x083C, state->dither);
			पूर्ण

			VGA_WR08(par->PCIO, 0x03D4, 0x53);
			VGA_WR08(par->PCIO, 0x03D5, state->timingH);
			VGA_WR08(par->PCIO, 0x03D4, 0x54);
			VGA_WR08(par->PCIO, 0x03D5, state->timingV);
			VGA_WR08(par->PCIO, 0x03D4, 0x21);
			VGA_WR08(par->PCIO, 0x03D5, 0xfa);
		पूर्ण

		VGA_WR08(par->PCIO, 0x03D4, 0x41);
		VGA_WR08(par->PCIO, 0x03D5, state->extra);
	पूर्ण

	VGA_WR08(par->PCIO, 0x03D4, 0x19);
	VGA_WR08(par->PCIO, 0x03D5, state->repaपूर्णांक0);
	VGA_WR08(par->PCIO, 0x03D4, 0x1A);
	VGA_WR08(par->PCIO, 0x03D5, state->repaपूर्णांक1);
	VGA_WR08(par->PCIO, 0x03D4, 0x25);
	VGA_WR08(par->PCIO, 0x03D5, state->screen);
	VGA_WR08(par->PCIO, 0x03D4, 0x28);
	VGA_WR08(par->PCIO, 0x03D5, state->pixel);
	VGA_WR08(par->PCIO, 0x03D4, 0x2D);
	VGA_WR08(par->PCIO, 0x03D5, state->horiz);
	VGA_WR08(par->PCIO, 0x03D4, 0x1C);
	VGA_WR08(par->PCIO, 0x03D5, state->fअगरo);
	VGA_WR08(par->PCIO, 0x03D4, 0x1B);
	VGA_WR08(par->PCIO, 0x03D5, state->arbitration0);
	VGA_WR08(par->PCIO, 0x03D4, 0x20);
	VGA_WR08(par->PCIO, 0x03D5, state->arbitration1);

	अगर(par->Architecture >= NV_ARCH_30) अणु
		VGA_WR08(par->PCIO, 0x03D4, 0x47);
		VGA_WR08(par->PCIO, 0x03D5, state->arbitration1 >> 8);
	पूर्ण

	VGA_WR08(par->PCIO, 0x03D4, 0x30);
	VGA_WR08(par->PCIO, 0x03D5, state->cursor0);
	VGA_WR08(par->PCIO, 0x03D4, 0x31);
	VGA_WR08(par->PCIO, 0x03D5, state->cursor1);
	VGA_WR08(par->PCIO, 0x03D4, 0x2F);
	VGA_WR08(par->PCIO, 0x03D5, state->cursor2);
	VGA_WR08(par->PCIO, 0x03D4, 0x39);
	VGA_WR08(par->PCIO, 0x03D5, state->पूर्णांकerlace);

	अगर (!par->FlatPanel) अणु
		अगर (par->Architecture >= NV_ARCH_40)
			NV_WR32(par->PRAMDAC0, 0x0580, state->control);

		NV_WR32(par->PRAMDAC0, 0x050C, state->pllsel);
		NV_WR32(par->PRAMDAC0, 0x0508, state->vpll);
		अगर (par->twoHeads)
			NV_WR32(par->PRAMDAC0, 0x0520, state->vpll2);
		अगर (par->twoStagePLL) अणु
			NV_WR32(par->PRAMDAC0, 0x0578, state->vpllB);
			NV_WR32(par->PRAMDAC0, 0x057C, state->vpll2B);
		पूर्ण
	पूर्ण अन्यथा अणु
		NV_WR32(par->PRAMDAC, 0x0848, state->scale);
		NV_WR32(par->PRAMDAC, 0x0828, state->crtcSync +
			par->PanelTweak);
	पूर्ण

	NV_WR32(par->PRAMDAC, 0x0600, state->general);

	NV_WR32(par->PCRTC, 0x0140, 0);
	NV_WR32(par->PCRTC, 0x0100, 1);

	par->CurrentState = state;
पूर्ण

व्योम NVUnloadStateExt(काष्ठा nvidia_par *par, RIVA_HW_STATE * state) अणु
	VGA_WR08(par->PCIO, 0x03D4, 0x19);
	state->repaपूर्णांक0 = VGA_RD08(par->PCIO, 0x03D5);
	VGA_WR08(par->PCIO, 0x03D4, 0x1A);
	state->repaपूर्णांक1 = VGA_RD08(par->PCIO, 0x03D5);
	VGA_WR08(par->PCIO, 0x03D4, 0x25);
	state->screen = VGA_RD08(par->PCIO, 0x03D5);
	VGA_WR08(par->PCIO, 0x03D4, 0x28);
	state->pixel = VGA_RD08(par->PCIO, 0x03D5);
	VGA_WR08(par->PCIO, 0x03D4, 0x2D);
	state->horiz = VGA_RD08(par->PCIO, 0x03D5);
	VGA_WR08(par->PCIO, 0x03D4, 0x1C);
	state->fअगरo         = VGA_RD08(par->PCIO, 0x03D5);
	VGA_WR08(par->PCIO, 0x03D4, 0x1B);
	state->arbitration0 = VGA_RD08(par->PCIO, 0x03D5);
	VGA_WR08(par->PCIO, 0x03D4, 0x20);
	state->arbitration1 = VGA_RD08(par->PCIO, 0x03D5);

	अगर(par->Architecture >= NV_ARCH_30) अणु
		VGA_WR08(par->PCIO, 0x03D4, 0x47);
		state->arbitration1 |= (VGA_RD08(par->PCIO, 0x03D5) & 1) << 8;
	पूर्ण

	VGA_WR08(par->PCIO, 0x03D4, 0x30);
	state->cursor0 = VGA_RD08(par->PCIO, 0x03D5);
	VGA_WR08(par->PCIO, 0x03D4, 0x31);
	state->cursor1 = VGA_RD08(par->PCIO, 0x03D5);
	VGA_WR08(par->PCIO, 0x03D4, 0x2F);
	state->cursor2 = VGA_RD08(par->PCIO, 0x03D5);
	VGA_WR08(par->PCIO, 0x03D4, 0x39);
	state->पूर्णांकerlace = VGA_RD08(par->PCIO, 0x03D5);
	state->vpll = NV_RD32(par->PRAMDAC0, 0x0508);
	अगर (par->twoHeads)
		state->vpll2 = NV_RD32(par->PRAMDAC0, 0x0520);
	अगर (par->twoStagePLL) अणु
		state->vpllB = NV_RD32(par->PRAMDAC0, 0x0578);
		state->vpll2B = NV_RD32(par->PRAMDAC0, 0x057C);
	पूर्ण
	state->pllsel = NV_RD32(par->PRAMDAC0, 0x050C);
	state->general = NV_RD32(par->PRAMDAC, 0x0600);
	state->scale = NV_RD32(par->PRAMDAC, 0x0848);
	state->config = NV_RD32(par->PFB, 0x0200);

	अगर (par->Architecture >= NV_ARCH_40 && !par->FlatPanel)
		state->control  = NV_RD32(par->PRAMDAC0, 0x0580);

	अगर (par->Architecture >= NV_ARCH_10) अणु
		अगर (par->twoHeads) अणु
			state->head = NV_RD32(par->PCRTC0, 0x0860);
			state->head2 = NV_RD32(par->PCRTC0, 0x2860);
			VGA_WR08(par->PCIO, 0x03D4, 0x44);
			state->crtcOwner = VGA_RD08(par->PCIO, 0x03D5);
		पूर्ण
		VGA_WR08(par->PCIO, 0x03D4, 0x41);
		state->extra = VGA_RD08(par->PCIO, 0x03D5);
		state->cursorConfig = NV_RD32(par->PCRTC, 0x0810);

		अगर ((par->Chipset & 0x0ff0) == 0x0110) अणु
			state->dither = NV_RD32(par->PRAMDAC, 0x0528);
		पूर्ण अन्यथा अगर (par->twoHeads) अणु
			state->dither = NV_RD32(par->PRAMDAC, 0x083C);
		पूर्ण

		अगर (par->FlatPanel) अणु
			VGA_WR08(par->PCIO, 0x03D4, 0x53);
			state->timingH = VGA_RD08(par->PCIO, 0x03D5);
			VGA_WR08(par->PCIO, 0x03D4, 0x54);
			state->timingV = VGA_RD08(par->PCIO, 0x03D5);
		पूर्ण
	पूर्ण
पूर्ण

व्योम NVSetStartAddress(काष्ठा nvidia_par *par, u32 start)
अणु
	NV_WR32(par->PCRTC, 0x800, start);
पूर्ण
